#pragma once
// std
#include <algorithm>
#include <vector>
// AmazingCow Libs
#include "acow/math_goodies.h"
#include "CoreGame/CoreGame.h"
#include "CoreAssert/CoreAssert.h"
// Core2048
#include "Core2048_Utils.h"
#include "Block.h"
#include "IValuesGenerator.h"


NS_CORE2048_BEGIN

class GameCore
{
    //------------------------------------------------------------------------//
    // Enums / Typedefs / Constants                                           //
    //------------------------------------------------------------------------//
private:
    typedef std::vector<Block::SPtr> Line;
public:
    ///-------------------------------------------------------------------------
    /// @brief
    ///    Just to make the code more "understandable",
    ///    since we want to see it as Board, not a simple vector of lines ;D
    typedef std::vector<Line> Board;

    ///-------------------------------------------------------------------------
    /// @brief the Direction that the movement can be.
    /// @see make_move().
    enum class Direction {
        Left, Up, Right, Down
    };


    //------------------------------------------------------------------------//
    // Inner Types                                                            //
    //------------------------------------------------------------------------//
public:
    ///-------------------------------------------------------------------------
    ///  @brief
    ///     Object that is returned when a move is performed.
    ///  @detail
    ///     It contains which blocks were moved, merged and removed.          \n
    ///     moved_blocks   - The blocks that only moved, i.e not got merged.  \n
    ///     merged_blocks  - The blocks that get merged when moved.           \n
    ///     removed_blocks - The blocks that should not be in game anymore
    ///                      because they got merged. So for example if two
    ///                      adjacent blocks with the same value are merged,
    ///                      one of them will be on the merged_blocks vector
    ///                      and the other on this vector.
    ///  @see make_move().
    struct MoveResult
    {
        std::vector<Block::SPtr> moved_blocks;
        std::vector<Block::SPtr> merged_blocks;
        std::vector<Block::SPtr> removed_blocks;

        bool move_valid;
    };


    //------------------------------------------------------------------------//
    // CTOR / DTOR                                                            //
    //------------------------------------------------------------------------//
public:
    ///-------------------------------------------------------------------------
    /// @brief Construct a new 2048 Game Core.
    /// @param p_values_generator
    ///    The object that will generate the value for the new block.
    /// @param width
    ///    The width of the game board.
    /// @param height
    ///    The height of the game board.
    /// @param seed
    ///    The seed of the CoreRandom numbers generator.
    ///    Default is CoreRandom::Random::kRandomSeed.
    /// @note
    ///    There is no valid check on the given arguments, is user
    ///    responsibility give meaningful values.
    GameCore(
        IValuesGenerator *p_values_generator,
        u32 width,
        u32 height,
        i32 seed = CoreRandom::Random::kRandomSeed) noexcept;

    ///-------------------------------------------------------------------------
    /// @brief Destructs the object.
    inline ~GameCore() noexcept = default;


    //------------------------------------------------------------------------//
    // Public Methods                                                         //
    //------------------------------------------------------------------------//
public:
    ///-------------------------------------------------------------------------
    /// @brief Generates the new game block.
    /// @returns A const shared pointer for the new game block.
    /// @see IValuesGenerator.
    const Block::SPtr generate_next_block() noexcept;

    ///-------------------------------------------------------------------------
    /// @brief Gets a block at given coord.
    /// @returns A const shared pointer for the block at coord.
    /// @note
    ///    There is no valid check on the given arguments, is user
    ///    responsibility give meaningful values.
    /// @see get_board(), is_valid_coord().
    inline const Block::SPtr
    get_block_at(const acow::math::Coord &coord) const noexcept
    {
        COREASSERT_ASSERT(
            is_valid_coord(coord),
            "Coord (%d,%d) is not valid",
            coord.y,
            coord.x
        );

        return m_board[coord.y][coord.x];
    }

    ///-------------------------------------------------------------------------
    /// @brief Gets the current state of game board.
    /// @returns A const reference of the game board.
    /// @see get_block_at(), Board.
    constexpr inline const Board&
    get_board() const noexcept
    {
        return m_board;
    }

    ///-------------------------------------------------------------------------
    /// @brief Makes a move towards the given direction.
    /// @detail
    ///    Player can pass any valid Direction value, if no movement is possible
    ///    for that direction a "empty" MoveResult will be returned and nothing
    ///    else will happens.
    ///    If a valid move is achievable, the blocks will be moved, merged and
    ///    removed and the chances will be placed on the MoveResult returned.
    ///    Moreover a valid move will increment the moves count and update
    ///    the status of the game, so users after call this method should check
    ///    the value of game_status() to see if game is over.
    /// @returns
    ///    A const reference for MoveResult containing all the changes
    ///    that this move performed in game state.
    /// @param direction
    ///    Any valid direction.
    /// @see
    ///    Direction, MoveResult, get_moves_count, get_status(), is_valid_move()
    const MoveResult& make_move(Direction direction) noexcept;

    ///-------------------------------------------------------------------------
    /// @brief Gets how many moves player did so far.
    /// @returns The count of moves that player did.
    constexpr inline u32
    get_moves_count() const noexcept
    {
        return m_moves_count;
    }


    ///-------------------------------------------------------------------------
    /// @brief Checks if a move / merge is possible for that Direction.
    /// @returns
    ///    True, if a move / merge is possible of that Direction,
    ///    false otherwise.
    /// @param direction - The direction that player wants to move.
    /// @see make_move(), is_valid_coord().
    bool is_valid_move(Direction direction) const noexcept;

    ///-------------------------------------------------------------------------
    /// @brief Checks if a coord is in range of the game board bounds.
    /// @returns
    ///    True, if coord is in board bounds, false otherwise.
    /// @param coord - The coord to test.
    /// @see get_block_at(), is_valid_coord().
    constexpr inline bool
    is_valid_coord(const acow::math::Coord &coord) const noexcept
    {
        return coord.y >= 0 && coord.y < m_board.size   ()
            && coord.x >= 0 && coord.x < m_board[0].size();
    }


    ///-------------------------------------------------------------------------
    /// @brief
    ///    Gets the current game status.
    ///    User should call this after each make_move call.
    /// @returns The current game status.
    /// @see make_move().
    constexpr inline CoreGame::Status
    get_status() const noexcept
    {
        return m_status;
    }

    ///-------------------------------------------------------------------------
    /// @brief Gets the summation of all current blocks.
    /// @returns The summation of all current blocks.
    /// @see get_max_value().
    constexpr inline u32
    get_score() const noexcept
    {
        return m_score;
    }

    ///-------------------------------------------------------------------------
    /// @brief Gets the higher value of the current blocks.
    /// @returns The higher current blocks.
    /// @see get_score().
    constexpr inline u32
    get_max_value() const noexcept
    {
        return m_max_value;
    }


    ///-------------------------------------------------------------------------
    /// @brief Gets the actual seed that game is using
    inline i32
    get_seed() const noexcept
    {
        return m_random.getSeed();
    }

    ///-------------------------------------------------------------------------
    /// @brief Gets if CoreRandom is actually using a random seed.
    inline bool
    is_using_random_seed() const noexcept
    {
        return m_random.isUsingRandomSeed();
    }

    ///-------------------------------------------------------------------------
    ///@brief
    ///  Just for debug purposes... get a nice formated representation of game.
    std::string ascii() const noexcept;


    //------------------------------------------------------------------------//
    // Private Methods                                                        //
    //------------------------------------------------------------------------//
private:
    void merge(const Line &line, const acow::math::Coord &dir_coord) noexcept;
    bool move (const Line &line, const acow::math::Coord &dir_coord) noexcept;

    bool can_merge_line(
        const Line             &line,
        const acow::math::Coord &dir_coord) const noexcept;

    bool can_move_line(
        const Line             &line,
        const acow::math::Coord &dir_coord) const noexcept;


    Block::SPtr find_first_same_value_block(
        Block::SPtr            p_src_block,
        const acow::math::Coord &dir_coord) const noexcept;

    acow::math::Coord find_last_empty_coord(
        Block::SPtr            p_src_block,
        const acow::math::Coord &dir_coord) const noexcept;

    inline bool
    is_already_merged(Block::SPtr p_block) const noexcept
    {
         return std::find(
             std::begin(m_move_result.merged_blocks),
             std::end  (m_move_result.merged_blocks),
             p_block
         ) != std::end(m_move_result.merged_blocks);
    }

    inline void
    put_block_at(
        const acow::math::Coord &coord,
        const Block::SPtr      p_block) noexcept
    {
        COREASSERT_ASSERT(
            is_valid_coord(coord),
            "Coord(%d, %d) is not valid",
            coord.y, coord.x
        );

        p_block->set_coord(coord);
        m_board[coord.y][coord.x] = p_block;
    }

    inline void
    reset_block_at(const acow::math::Coord &coord) noexcept
    {
        m_board[coord.y][coord.x] = nullptr;
    }

    void calculate_score_and_max_value() noexcept;
    void check_status                 () noexcept;


    //------------------------------------------------------------------------//
    // iVars                                                                  //
    //------------------------------------------------------------------------//
private:
    IValuesGenerator *mp_values_generator;

    Board m_board;
    int   m_moves_count;

    int m_max_value;
    int m_score;

    CoreGame::Status   m_status;
    CoreRandom::Random m_random;

    MoveResult m_move_result;

}; // class GameCore
NS_CORE2048_END
