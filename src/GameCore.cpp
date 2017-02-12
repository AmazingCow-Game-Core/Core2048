//----------------------------------------------------------------------------//
//               █      █                                                     //
//               ████████                                                     //
//             ██        ██                                                   //
//            ███  █  █  ███        GameCore.cpp                              //
//            █ █        █ █        Core2048                                  //
//             ████████████                                                   //
//           █              █       Copyright (c) 2017                        //
//          █     █    █     █      AmazingCow - www.AmazingCow.com           //
//          █     █    █     █                                                //
//           █              █       N2OMatt - n2omatt@amazingcow.com          //
//             ████████████         www.amazingcow.com/n2omatt                //
//                                                                            //
//                  This software is licensed as GPLv3                        //
//                 CHECK THE COPYING FILE TO MORE DETAILS                     //
//                                                                            //
//    Permission is granted to anyone to use this software for any purpose,   //
//   including commercial applications, and to alter it and redistribute it   //
//               freely, subject to the following restrictions:               //
//                                                                            //
//     0. You **CANNOT** change the type of the license.                      //
//     1. The origin of this software must not be misrepresented;             //
//        you must not claim that you wrote the original software.            //
//     2. If you use this software in a product, an acknowledgment in the     //
//        product IS HIGHLY APPRECIATED, both in source and binary forms.     //
//        (See opensource.AmazingCow.com/acknowledgment.html for details).    //
//        If you will not acknowledge, just send us a email. We'll be         //
//        *VERY* happy to see our work being used by other people. :)         //
//        The email is: acknowledgment_opensource@AmazingCow.com              //
//     3. Altered source versions must be plainly marked as such,             //
//        and must not be misrepresented as being the original software.      //
//     4. This notice may not be removed or altered from any source           //
//        distribution.                                                       //
//     5. Most important, you must have fun. ;)                               //
//                                                                            //
//      Visit opensource.amazingcow.com for more open-source projects.        //
//                                                                            //
//                                  Enjoy :)                                  //
//----------------------------------------------------------------------------//
//Header
#include "../include/GameCore.h"
//std
#include <cmath>     //pow
#include <sstream>   //for ascii method
#include <algorithm> //find
#include <iterator>  //begin, end

//Usings
NS_CORE2048_BEGIN;


////////////////////////////////////////////////////////////////////////////////
// Constants                                                                  //
////////////////////////////////////////////////////////////////////////////////
constexpr auto k_lesser_value = 2;


////////////////////////////////////////////////////////////////////////////////
// Helper Functions                                                           //
////////////////////////////////////////////////////////////////////////////////
template <typename T>
std::tuple<int, int, int> for_values_helper(
    const T                &container,
    const CoreCoord::Coord &dir_coord)
{

    //Assume that we're moving to Left or Up.
    auto inclusive_begin = 0;
    auto exclusive_end   = container.size(); //One past the end.
    auto sum_value       = 1;

    //Adjust for Right or Down.
    if(dir_coord.y > 0 || dir_coord.x > 0)
    {
        inclusive_begin = container.size() -1;
        exclusive_end   = -1; //One past the end.
        sum_value       = -1; //Will drecrement the index...
    }

    return std::make_tuple(inclusive_begin, exclusive_end, sum_value);
}

CoreCoord::Coord direction_2_coord(GameCore::Direction dir)
{
    return (dir == GameCore::Direction::Up  ) ? CoreCoord::Coord::Up  () :
           (dir == GameCore::Direction::Down) ? CoreCoord::Coord::Down() :
           (dir == GameCore::Direction::Left) ? CoreCoord::Coord::Left() :
                                                CoreCoord::Coord::Right();
}


////////////////////////////////////////////////////////////////////////////////
// CTOR / DTOR                                                                //
////////////////////////////////////////////////////////////////////////////////
GameCore::GameCore(
    IValuesGenerator *p_values_generator,
    int width,
    int height,
    int seed
) :
    mp_values_generator(p_values_generator),
    m_max_value(k_lesser_value),
    m_score    (0),
    m_status   (CoreGame::Status::Continue),
    m_random   (seed)
{
    COREGAME_ASSERT_ARGS(
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

GameCore::~GameCore()
{

}


////////////////////////////////////////////////////////////////////////////////
// Public Methods                                                             //
////////////////////////////////////////////////////////////////////////////////
const Block::SPtr GameCore::generate_next_block()
{
    auto coord = CoreCoord::Coord();
    while(1)
    {
        coord.y = m_random.next(m_board.size   () -1);
        coord.x = m_random.next(m_board[0].size() -1);

        //Empty block.
        if(!get_block_at(coord))
            break;
    }

    auto value   = mp_values_generator->generate_value(m_random);
    auto p_block = std::make_shared<Block>(coord, value);

    put_block_at(p_block->get_coord(), p_block);

    return p_block;
}

const Block::SPtr GameCore::get_block_at(const CoreCoord::Coord &coord) const
{
    COREGAME_ASSERT_ARGS(
        is_valid_coord(coord),
        "Coord (%d,%d) is not valid",
        coord.y,
        coord.x
    );

    return m_board[coord.y][coord.x];
}

const GameCore::Board& GameCore::get_board() const
{
    return m_board;
}


const std::vector<Block::SPtr>& GameCore::make_move(Direction direction)
{
    if(!is_valid_move(direction))
        return m_moved_blocks;

    auto dir_coord = direction_2_coord(direction);

    m_moved_blocks.clear  ();
    m_merged_blocks.clear ();
    m_removed_blocks.clear();

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

    return m_moved_blocks;
}

int GameCore::get_moves_count() const
{
    return m_moves_count;
}


bool GameCore::has_valid_moves() const
{
    return is_valid_move(Direction::Left ) ||
           is_valid_move(Direction::Up   ) ||
           is_valid_move(Direction::Right) ||
           is_valid_move(Direction::Down );
}

bool GameCore::is_valid_move(Direction direction) const
{
    auto dir_coord = direction_2_coord(direction);
    for(auto &line : m_board)
    {
        if(can_move_line(line, dir_coord) ||
           can_merge_line(line, dir_coord))
        {
            return true;
        }
    }

    return false;
}


bool GameCore::is_valid_coord(const CoreCoord::Coord &coord) const
{
    return coord.y >= 0 && coord.y < m_board.size   ()
        && coord.x >= 0 && coord.x < m_board[0].size();
}

CoreGame::Status GameCore::get_status() const
{
    return m_status;
}

int GameCore::get_score() const
{
    return m_score;
}


int GameCore::get_seed() const
{
    return m_random.getSeed();
}

bool GameCore::is_using_random_seed() const
{
    return m_random.isUsingRandomSeed();
}


std::string GameCore::ascii() const
{
    std::stringstream ss;
    for(auto &line : m_board)
    {
        for(auto p_block : line)
        {
            if(p_block)
            {
                ss << "[";

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


////////////////////////////////////////////////////////////////////////////////
// Private Methods                                                            //
////////////////////////////////////////////////////////////////////////////////
void GameCore::merge(const Line &line, const CoreCoord::Coord &dir_coord)
{
    auto for_values = for_values_helper(line, dir_coord);
    for(int i  = std::get<0>(for_values);
            i != std::get<1>(for_values);
            i += std::get<2>(for_values))
    {
        auto p_block = line[i];

        //Empty block.
        if(!p_block)
            continue;

        //Already merged at this turn
        //  Cannot merge twice...
        if(is_already_merged(p_block))
            continue;

        auto p_target_block = find_first_same_value_block(p_block, dir_coord);

        //No blocks with same value at this line.
        if(p_target_block == nullptr)
            continue;

        //Trying to merge with a block that is already merged
        //  But then again, blocks can only merge once per turn.
        if(is_already_merged(p_target_block))
            continue;

        //Resetting the src block and doubling the target block
        //has the effect of merging them.
        reset_block_at(p_block->get_coord());
        p_target_block->set_value(p_target_block->get_value() * 2);

        m_merged_blocks.push_back (p_target_block);
        m_removed_blocks.push_back(p_block);

        cout << ascii() << endl;
    }
}

bool GameCore::move(const Line &line, const CoreCoord::Coord &dir_coord)
{
    bool moved = false;

    auto for_values = for_values_helper(line, dir_coord);
    for(int i  = std::get<0>(for_values);
            i != std::get<1>(for_values);
            i += std::get<2>(for_values))
    {
        auto p_block = line[i];

        //Empty block.
        if(!p_block)
            continue;

        auto target_coord = find_last_empty_coord(p_block, dir_coord);

        //No empty blocks.
        if(target_coord == p_block->get_coord())
            continue;

        reset_block_at(p_block->get_coord());
        put_block_at  (target_coord, p_block);

        m_moved_blocks.push_back(p_block);
        moved = true;

        cout << ascii() << endl;
    }

    return moved;
}


bool GameCore::can_merge_line(
    const Line             &line,
    const CoreCoord::Coord &dir_coord) const
{

    for(auto p_block : line)
    {
        //Empty block.
        if(!p_block)
            continue;

        //Check if can merge.
        auto p_target_block = find_first_same_value_block(p_block, dir_coord);
        if(p_target_block)
            return true;
    }

    return false;
}

bool GameCore::can_move_line(
    const Line             &line,
    const CoreCoord::Coord &dir_coord) const
{
    for(auto p_block : line)
    {
        //Empty block.
        if(!p_block)
            continue;

        //Check if can move.
        auto target_coord = find_last_empty_coord(p_block, dir_coord);
        if(target_coord != p_block->get_coord())
            return true;
    }

    return false;
}


Block::SPtr GameCore::find_first_same_value_block(
    Block::SPtr            p_src_block,
    const CoreCoord::Coord &dir_coord) const
{
    COREGAME_ASSERT(
        p_src_block != nullptr,
        "p_src_block cannot be nullptr"
    );

    auto curr_coord = p_src_block->get_coord();

    while(1)
    {
        curr_coord += dir_coord;

        //Outside board bounds.
        if(!is_valid_coord(curr_coord))
            return nullptr;

        auto p_curr_block = get_block_at(curr_coord);

        //Empty block.
        if(!p_curr_block)
            continue;

        //Same value blocks.
        if(p_curr_block->get_value() == p_src_block->get_value())
            return p_curr_block;
        //Found a block with different value.
        //  Don't need to keep searching...
        else
            return nullptr;
    }

    return nullptr;
}


CoreCoord::Coord GameCore::find_last_empty_coord(
    Block::SPtr            p_src_block,
    const CoreCoord::Coord &dir_coord) const
{
    COREGAME_ASSERT(
        p_src_block != nullptr,
        "p_src_block cannot be nullptr"
    );

    auto curr_coord = p_src_block->get_coord();
    while(1)
    {
        curr_coord += dir_coord;

        //At edge of Board.
        if(!is_valid_coord(curr_coord))
            return curr_coord + (dir_coord * -1);

        auto p_curr_block = get_block_at(curr_coord);

        if(p_curr_block)
            return curr_coord + (dir_coord * -1);
    }

    COREGAME_ASSERT(false, "Cannot be here");
}


bool GameCore::is_already_merged(Block::SPtr p_block) const
{
    return std::find(
        std::begin(m_merged_blocks),
        std::end  (m_merged_blocks),
        p_block
    ) != std::end(m_merged_blocks);
}


void GameCore::put_block_at(
    const CoreCoord::Coord &coord,
    const Block::SPtr      p_block)
{
    COREGAME_ASSERT_ARGS(
        is_valid_coord(coord),
        "Coord(%d, %d) is not valid",
        coord.y, coord.x
    );

    p_block->set_coord(coord);
    m_board[coord.y][coord.x] = p_block;
}

void GameCore::reset_block_at(const CoreCoord::Coord &coord)
{
    m_board[coord.y][coord.x] = nullptr;
}


void GameCore::calculate_score_and_max_value()
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
            m_max_value  = std::max(m_max_value, value);
        }
    }

    mp_values_generator->set_max_value(m_max_value);
}

