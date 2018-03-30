//~---------------------------------------------------------------------------//
//                     _______  _______  _______  _     _                     //
//                    |   _   ||       ||       || | _ | |                    //
//                    |  |_|  ||       ||   _   || || || |                    //
//                    |       ||       ||  | |  ||       |                    //
//                    |       ||      _||  |_|  ||       |                    //
//                    |   _   ||     |_ |       ||   _   |                    //
//                    |__| |__||_______||_______||__| |__|                    //
//                             www.amazingcow.com                             //
//  File      : GameCore.cpp                                                  //
//  Project   : Core2048                                                      //
//  Date      : Feb 12, 2017                                                  //
//  License   : GPLv3                                                         //
//  Author    : n2omatt <n2omatt@amazingcow.com>                              //
//  Copyright : AmazingCow - 2017, 2018                                       //
//                                                                            //
//  Description :                                                             //
//                                                                            //
//---------------------------------------------------------------------------~//

// Header
#include "../include/GameCore.h"
// std
#include <cmath>     //pow
#include <sstream>   //for ascii method
#include <algorithm> //find
#include <iterator>  //begin, end

// Usings
USING_NS_CORE2048;


//----------------------------------------------------------------------------//
// Constants                                                                  //
//----------------------------------------------------------------------------//
constexpr auto k_lesser_value  = 2;
constexpr auto k_victory_value = 2048;


//----------------------------------------------------------------------------//
// Helper Functions                                                           //
//----------------------------------------------------------------------------//
template <typename T>
std::tuple<int, int, int>
for_values_helper(
    const T                &container,
    const acow::math::Coord &dir_coord)
{
    //--------------------------------------------------------------------------
    // Assume that we're moving to Left or Up.
    auto inclusive_begin = 0;
    auto exclusive_end   = container.size(); // One past the end.
    auto sum_value       = 1;

    //--------------------------------------------------------------------------
    // Adjust for Right or Down.
    if(dir_coord.y > 0 || dir_coord.x > 0)
    {
        inclusive_begin = container.size() -1;
        exclusive_end   = -1; //One past the end.
        sum_value       = -1; //Will decrement the index...
    }

    return std::make_tuple(inclusive_begin, exclusive_end, sum_value);
}

acow::math::Coord
direction_2_coord(GameCore::Direction dir) noexcept
{
    return (dir == GameCore::Direction::Up  ) ? acow::math::Coord::Up  () :
           (dir == GameCore::Direction::Down) ? acow::math::Coord::Down() :
           (dir == GameCore::Direction::Left) ? acow::math::Coord::Left() :
                                                acow::math::Coord::Right();
}


//----------------------------------------------------------------------------//
// CTOR / DTOR                                                                //
//----------------------------------------------------------------------------//
GameCore::GameCore(
    IValuesGenerator *p_values_generator,
    u32 width,
    u32 height,
    i32 seed) noexcept
    : mp_values_generator(p_values_generator)
    , m_max_value(k_lesser_value)
    , m_score    (0)
    , m_status   (CoreGame::Status::Continue)
    , m_random   (seed)
{
    COREASSERT_ASSERT(
        (width > 0 && height > 0),
        "Width(%d) and Height(%d) must be positive.",
        width,
        height
    );

    //Init board.
    m_board.resize(height);
    for(auto &line : m_board)
        line.resize(width);

    calculate_score_and_max_value();
    generate_next_block          ();
}


//----------------------------------------------------------------------------//
// Public Methods                                                             //
//----------------------------------------------------------------------------//
const Block::SPtr
GameCore::generate_next_block() noexcept
{
    auto coord = acow::math::Coord();
    // COWTODO(n2omatt): Check if has empty blocks first...
    while(1)
    {
        coord.y = m_random.next(m_board.size   () -1);
        coord.x = m_random.next(m_board[0].size() -1);

        // Empty block.
        if(!get_block_at(coord))
            break;
    }

    auto value   = mp_values_generator->generate_value(m_random);
    auto p_block = std::make_shared<Block>(coord, value);

    put_block_at(p_block->get_coord(), p_block);

    return p_block;
}


//
const GameCore::MoveResult&
GameCore::make_move(Direction direction) noexcept
{
    //--------------------------------------------------------------------------
    // Clear the previous data.
    m_move_result.moved_blocks.clear  ();
    m_move_result.merged_blocks.clear ();
    m_move_result.removed_blocks.clear();
    m_move_result.move_valid = false;

    //--------------------------------------------------------------------------
    // Check if move is valid.
    if(m_status == CoreGame::Status::Defeat || !is_valid_move(direction))
        return m_move_result;

    //--------------------------------------------------------------------------
    // Merge the blocks and move them.
    auto dir_coord  = direction_2_coord(direction);
    auto for_values = for_values_helper(m_board, dir_coord);

    for(int i  = std::get<0>(for_values);
            i != std::get<1>(for_values);
            i += std::get<2>(for_values))
    {
        auto &line = m_board[i];

        merge(line, dir_coord);
        move (line, dir_coord);
    }

    ++m_moves_count;

    calculate_score_and_max_value();
    check_status                 ();

    m_move_result.move_valid = true;
    return m_move_result;
}



//
bool
GameCore::is_valid_move(Direction direction) const noexcept
{
    auto dir_coord = direction_2_coord(direction);
    for(auto &line : m_board)
    {
        if(can_move_line (line, dir_coord) ||
           can_merge_line(line, dir_coord))
        {
            return true;
        }
    }

    return false;
}


//
std::string
GameCore::ascii() const noexcept
{
    std::stringstream ss;
    for(auto &line : m_board)
    {
        for(auto p_block : line)
        {
            if(p_block)
            {
                ss << "[";

                if(p_block->get_value() < 100)
                    ss << " ";
                if(p_block->get_value() < 10)
                    ss << " ";

                ss << p_block->get_value() << "]";
            }
            else
                ss << "[  ]";
        }

        ss << std::endl;
    }

    return ss.str();
}


//----------------------------------------------------------------------------//
// Private Methods                                                            //
//----------------------------------------------------------------------------//
void
GameCore::merge(const Line &line, const acow::math::Coord &dir_coord) noexcept
{
    auto for_values = for_values_helper(line, dir_coord);
    for(int i  = std::get<0>(for_values);
            i != std::get<1>(for_values);
            i += std::get<2>(for_values))
    {
        auto p_block = line[i];

        //----------------------------------------------------------------------
        // Empty block.
        if(!p_block)
            continue;

        //----------------------------------------------------------------------
        // Already merged at this turn
        //   Cannot merge twice...
        if(is_already_merged(p_block))
            continue;

        auto p_target_block = find_first_same_value_block(p_block, dir_coord);

        //----------------------------------------------------------------------
        // No blocks with same value at this line.
        if(p_target_block == nullptr)
            continue;

        //----------------------------------------------------------------------
        // Trying to merge with a block that is already merged
        //   But then again, blocks can only merge once per turn.
        if(is_already_merged(p_target_block))
            continue;

        //----------------------------------------------------------------------
        // Resetting the src block and doubling the target block
        // has the effect of merging them.
        reset_block_at(p_block->get_coord());
        p_target_block->set_value(p_target_block->get_value() * 2);

        m_move_result.merged_blocks.push_back (p_target_block);
        m_move_result.removed_blocks.push_back(p_block);
    }
}

bool
GameCore::move(const Line &line, const acow::math::Coord &dir_coord) noexcept
{
    bool moved = false;

    auto for_values = for_values_helper(line, dir_coord);
    for(int i  = std::get<0>(for_values);
            i != std::get<1>(for_values);
            i += std::get<2>(for_values))
    {
        auto p_block = line[i];

        //----------------------------------------------------------------------
        // Empty block.
        if(!p_block)
            continue;

        auto target_coord = find_last_empty_coord(p_block, dir_coord);

        //----------------------------------------------------------------------
        // No empty blocks.
        if(target_coord == p_block->get_coord())
            continue;

        reset_block_at(p_block->get_coord());
        put_block_at  (target_coord, p_block);

        m_move_result.moved_blocks.push_back(p_block);
        moved = true;
    }

    return moved;
}


bool
GameCore::can_merge_line(
    const Line             &line,
    const acow::math::Coord &dir_coord) const noexcept
{

    for(auto p_block : line)
    {
        //----------------------------------------------------------------------
        // Empty block.
        if(!p_block)
            continue;

        //----------------------------------------------------------------------
        // Check if can merge.
        auto p_target_block = find_first_same_value_block(p_block, dir_coord);
        if(p_target_block)
            return true;
    }

    return false;
}


bool
GameCore::can_move_line(
    const Line              &line,
    const acow::math::Coord &dir_coord) const noexcept
{
    for(auto p_block : line)
    {
        //----------------------------------------------------------------------
        // Empty block.
        if(!p_block)
            continue;

        //----------------------------------------------------------------------
        // Check if can move.
        auto target_coord = find_last_empty_coord(p_block, dir_coord);
        if(target_coord != p_block->get_coord())
            return true;
    }

    return false;
}


//
Block::SPtr
GameCore::find_first_same_value_block(
    Block::SPtr            p_src_block,
    const acow::math::Coord &dir_coord) const noexcept
{
    COREASSERT_ASSERT(
        p_src_block != nullptr,
        "p_src_block cannot be nullptr"
    );

    auto curr_coord = p_src_block->get_coord();

    while(1)
    {
        curr_coord += dir_coord;

        //----------------------------------------------------------------------
        // Outside board bounds.
        if(!is_valid_coord(curr_coord))
            return nullptr;

        auto p_curr_block = get_block_at(curr_coord);

        //----------------------------------------------------------------------
        // Empty block.
        if(!p_curr_block)
            continue;

        //----------------------------------------------------------------------
        // Same value blocks.
        if(p_curr_block->get_value() == p_src_block->get_value())
        {
            return p_curr_block;
        }
        //----------------------------------------------------------------------
        // Found a block with different value.
        //   Don't need to keep searching...
        else
        {
            return nullptr;
        }
    }

    return nullptr;
}

acow::math::Coord
GameCore::find_last_empty_coord(
    Block::SPtr            p_src_block,
    const acow::math::Coord &dir_coord) const noexcept
{
    COREASSERT_ASSERT(
        p_src_block != nullptr,
        "p_src_block cannot be nullptr"
    );

    auto curr_coord = p_src_block->get_coord();
    while(1)
    {
        curr_coord += dir_coord;

        //----------------------------------------------------------------------
        // At edge of Board.
        if(!is_valid_coord(curr_coord))
            return curr_coord + (dir_coord * -1);

        auto p_curr_block = get_block_at(curr_coord);

        if(p_curr_block)
            return curr_coord + (dir_coord * -1);
    }

    COREASSERT_ASSERT(false, "Cannot be here");
}



//
void
GameCore::calculate_score_and_max_value() noexcept
{
    m_score     = 0;
    m_max_value = k_lesser_value;

    for(auto &line : m_board)
    {
        for(auto p_block : line)
        {
            if(!p_block)
                continue;

            auto value = p_block->get_value();

            m_score     += value;
            m_max_value  = acow::math::Max(m_max_value, value);
        }
    }

    mp_values_generator->set_max_value(m_max_value);
}

void
GameCore::check_status() noexcept
{
    if(m_max_value >= k_victory_value)
    {
        m_status = CoreGame::Status::Victory;
    }
    else if(is_valid_move(Direction::Up   ) ||
            is_valid_move(Direction::Down ) ||
            is_valid_move(Direction::Left ) ||
            is_valid_move(Direction::Right))
    {
        m_status = CoreGame::Status::Continue;
    }
    else
    {
        m_status = CoreGame::Status::Defeat;
    }
}
