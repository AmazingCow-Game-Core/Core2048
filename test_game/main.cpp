//----------------------------------------------------------------------------//
//               █      █                                                     //
//               ████████                                                     //
//             ██        ██                                                   //
//            ███  █  █  ███        main.cpp                                  //
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
#include "../include/GameCore.h"
#include <iostream>
#include <sstream>
#include <cstdlib>
#include "termcolor.h"
#include <sstream>
#include <cmath>
#include <cstdlib>
#include "../include/PresetValuesGenerator.h"

using namespace std;
USING_NS_CORE2048;

void print_board(const GameCore::Board &board, Block::SPtr p_gen_block)
{
//    system("tput clear");
    for(auto &line : board)
    {
        for(auto p_block : line)
        {
            if(p_block)
            {
                stringstream ss;
                ss << p_block->get_value();

                std::string str = "";
                if(p_block == p_gen_block)
                {
                     str = termcolor::colored(
                        ss.str(),
                        30 + log2(p_block->get_value()),
                        termcolor::ON_MAGENTA
                    );
                }
                else
                {
                    str = termcolor::colored(
                        ss.str(),
                        30 + log2(p_block->get_value())
                    );
                }

                cout << "[";

                if(p_block->get_value() < 100)
                    cout << " ";
                if(p_block->get_value() < 10)
                    cout << " ";

                cout << str;

                cout << "]";
            }
            else
                cout << "[   ]";
        }
        cout << endl;
    }
}

int main()
{
    auto values_gen = PresetValuesGenerator("values.txt");
    auto core       = GameCore(&values_gen, 4, 4, 150);

    std::stringstream ss;
    std::string input = "";
    int input_i = 0;

    auto p_block = core.generate_next_block();
    while(1)
    {
        print_board(core.get_board(), p_block);
        cout << ss.str() << endl;
        std::cout << "Dir: ";

        char a;
        if(input_i < input.size())
            a = input[input_i++];
        else
            std::cin >> a;

        ss << a;

        auto dir = GameCore::Direction::Up;

        if(a == 'w') dir = GameCore::Direction::Up;
        if(a == 's') dir = GameCore::Direction::Down;
        if(a == 'a') dir = GameCore::Direction::Left;
        if(a == 'd') dir = GameCore::Direction::Right;

        if(core.is_valid_move(dir))
        {
            auto a = core.make_move(dir);
            cout << a.moved_blocks[0]->get_old_coord() << endl;
            cout << a.moved_blocks[0]->get_coord() << endl;

            p_block = core.generate_next_block();
        }


    }
}
