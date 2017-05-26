//----------------------------------------------------------------------------//
//               █      █                                                     //
//               ████████                                                     //
//             ██        ██                                                   //
//            ███  █  █  ███        GameCore.h                                //
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
#pragma once
//std
#include <vector>
//AmazingCow Libs
#include "CoreGame.h"
#include "CoreCoord.h"
//Core2048
#include "Core2048_Utils.h"
#include "Block.h"
#include "IValuesGenerator.h"


NS_CORE2048_BEGIN

class GameCore
{
    // Enums / Typedefs / Constants //
private:
    typedef std::vector<Block::SPtr> Line;
public:
    ///@brief just to make the code more "understandable",
    ///since we want to see it as Board, not a simple vector of lines ;D
    typedef std::vector<Line> Board;

    ///@brief the Direction that the movement can be.
    ///@see make_move().
    enum class Direction {
        Left, Up, Right, Down
    };

    // Inner Types //
public:
    ///@brief
    ///  Object that is returned when a move is performed.
    ///@detail
    ///  It contains which blocks were moved, merged and removed.             \n
    ///  moved_blocks   - The blocks that only moved, i.e not got merged.     \n
    ///  merged_blocks  - The blocks that get merged when moved.              \n
    ///  removed_blocks - The blocks that should not be in game anymore
    ///                   because they got merged. So for example if two
    ///                   adjacent blocks with the same value are merged,
    ///                   one of them will be on the merged_blocks vector
    ///                   and the other on this vector.
    ///@see make_move().
    struct MoveResult
    {
        std::vector<Block::SPtr> moved_blocks;
        std::vector<Block::SPtr> merged_blocks;
        std::vector<Block::SPtr> removed_blocks;
    };

    // CTOR / DTOR //
public:
    ///@brief Construct a new 2048 Game Core.
    ///@param p_values_generator
    ///  The object that will generate the value for the new block.
    ///@param width
    ///  The width of the game board.
    ///@param height
    ///  The height of the game board.
    ///@param seed
    ///  The seed of the CoreRandom numbers generator.
    ///  Default is CoreRandom::Random::kRandomSeed.
    ///@note
    ///  There is no valid check on the given arguments, is user responsibility
    ///  give meaningful values.
    GameCore(
        IValuesGenerator *p_values_generator,
        int width,
        int height,
        int seed = CoreRandom::Random::kRandomSeed);

    ///@brief Destructs the object.
    ~GameCore();


    // Public Methods //
public:
    ///@brief Generates the new game block.
    ///@returns A const shared pointer for the new game block.
    ///@see IValuesGenerator.
    const Block::SPtr generate_next_block();

    ///@brief Gets a block at given coord.
    ///@returns A const shared pointer for the block at coord.
    ///@note
    ///  There is no valid check on the given arguments, is user responsibility
    ///  give meaningful values.
    ///@see get_board(), is_valid_coord().
    const Block::SPtr get_block_at(const CoreCoord::Coord &coord) const;

    ///@brief Gets the current state of game board.
    ///@returns A const reference of the game board.
    ///@note
    ///@see get_block_at(), Board.
    const Board& get_board() const;


    ///@brief Makes a move towards the given direction.
    ///@detail
    ///  Player can pass any valid Direction value, if no movement is possible
    ///  for that direction a "empty" MoveResult will be returned and nothing
    ///  else will happens.
    ///  If a valid move is achievable, the blocks will be moved, merged and
    ///  removed and the chances will be placed on the MoveResult returned.
    ///  Moreover a valid move will increment the moves count and update
    ///  the status of the game, so users after call this method should check
    ///  the value of game_status() to see if game is over.
    ///@returns
    ///  A const reference for MoveResult containing all the changes
    ///  that this move performed in game state.
    ///@param direction
    ///  Any valid direction.
    ///@see Direction, MoveResult, get_moves_count, get_status(), is_valid_move().
    const MoveResult& make_move(Direction direction);

    ///@brief Gets how many moves player did so far.
    //@returns The count of moves that player did.
    int get_moves_count() const;


    ///@brief Checks if a move / merge is possible for that Direction.
    ///@returns
    ///  True, if a move / merge is possible of that Direction, false otherwise.
    ///@param direction - The direction that player wants to move.
    ///@see make_move(), is_valid_coord().
    bool is_valid_move(Direction direction) const;

    ///@brief Checks if a coord is in range of the game board bounds.
    ///@returns
    ///  True, if coord is in board bounds, false otherwise.
    ///@param coord - The coord to test.
    ///@see get_block_at(), is_valid_coord().
    bool is_valid_coord(const CoreCoord::Coord &coord) const;


    ///@brief
    /// Gets the current game status.
    /// User should call this after each make_move call.
    ///@returns The current game status.
    ///@see make_move().
    CoreGame::Status get_status() const;

    ///@brief Gets the summation of all current blocks.
    ///@returns The summation of all current blocks.
    ///@see get_max_value().
    int get_score() const;

    ///@brief Gets the higher value of the current blocks.
    ///@returns The higher current blocks.
    ///@see get_score().
    int get_max_value() const;


    ///@brief Gets the actual seed that game is using
    int get_seed() const;

    ///@brief Gets if CoreRandom is actually using a random seed.
    bool is_using_random_seed() const;

    ///@brief
    ///  Just for debug purposes... get a nice formated representation of game.
    std::string ascii() const;


    // Private Methods //
private:
    void merge(const Line &line, const CoreCoord::Coord &dir_coord);
    bool move (const Line &line, const CoreCoord::Coord &dir_coord);

    bool can_merge_line(const Line &line, const CoreCoord::Coord &dir_coord) const;
    bool can_move_line (const Line &line, const CoreCoord::Coord &dir_coord) const;

    Block::SPtr find_first_same_value_block(
        Block::SPtr            p_src_block,
        const CoreCoord::Coord &dir_coord) const;

    CoreCoord::Coord find_last_empty_coord(
        Block::SPtr            p_src_block,
        const CoreCoord::Coord &dir_coord) const;

    bool is_already_merged(Block::SPtr p_block) const;

    void put_block_at  (const CoreCoord::Coord &coord, const Block::SPtr p_block);
    void reset_block_at(const CoreCoord::Coord &coord);

    void calculate_score_and_max_value();
    void check_status                 ();


    // iVars //
private:
    IValuesGenerator *mp_values_generator;

    Board m_board;
    int   m_moves_count;

    int m_max_value;
    int m_score;

    CoreGame::Status   m_status;
    CoreRandom::Random m_random;

    MoveResult m_move_result;
};
NS_CORE2048_END
