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
    // Enums / Typdefs / Constants //
private:
    typedef std::vector<Block::SPtr> Line;
public:
    typedef std::vector<Line> Board;

    enum class Direction {
        Left, Up, Right, Down
    };


    // CTOR / DTOR //
public:
     GameCore(
        IValuesGenerator *p_values_generator,
        int width,
        int height,
        int seed = CoreRandom::Random::kRandomSeed);

    ~GameCore();


    // Public Methods //
public:
    const Block::SPtr generate_next_block();
    const Block::SPtr get_block_at(const CoreCoord::Coord &coord) const;
    const Board&      get_board() const;

    const std::vector<Block::SPtr>& make_move(Direction direction);
    int  get_moves_count() const;

    bool is_valid_move  (Direction direction) const;
    bool has_valid_moves() const;

    bool             is_valid_coord(const CoreCoord::Coord &coord) const;
    CoreGame::Status get_status    () const;
    int              get_score     () const;

    int  get_seed() const;
    bool is_using_random_seed() const;

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


    // iVars //
private:
    IValuesGenerator *mp_values_generator;

    Board m_board;
    int   m_moves_count;

    int m_max_value;
    int m_score;

    CoreGame::Status   m_status;
    CoreRandom::Random m_random;

    std::vector<Block::SPtr> m_moved_blocks;
    std::vector<Block::SPtr> m_merged_blocks;
    std::vector<Block::SPtr> m_removed_blocks;
};
NS_CORE2048_END
