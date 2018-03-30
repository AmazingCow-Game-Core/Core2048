//~---------------------------------------------------------------------------//
//                     _______  _______  _______  _     _                     //
//                    |   _   ||       ||       || | _ | |                    //
//                    |  |_|  ||       ||   _   || || || |                    //
//                    |       ||       ||  | |  ||       |                    //
//                    |       ||      _||  |_|  ||       |                    //
//                    |   _   ||     |_ |       ||   _   |                    //
//                    |__| |__||_______||_______||__| |__|                    //
//                             www.amazingcow.com                             //
//  File      : main.cpp                                                      //
//  Project   : Core2048                                                      //
//  Date      : Feb 12, 2017                                                  //
//  License   : GPLv3                                                         //
//  Author    : n2omatt <n2omatt@amazingcow.com>                              //
//  Copyright : AmazingCow - 2017, 2018                                       //
//                                                                            //
//  Description :                                                             //
//                                                                            //
//---------------------------------------------------------------------------~//

// std
#include <iostream>
#include <sstream>
#include <cstdlib>
#include <sstream>
#include <cmath>
#include <cstdlib>
// AmazingCow Libs
#include "termcolor/termcolor.h"
// Core2048
#include "Core2048/Core2048.h"
// using namespace std;
// USING_NS_CORE2048;

void
print_board(
    const Core2048::GameCore::Board &board,
    Core2048::Block::SPtr           p_gen_block) noexcept
{
    //    system("tput clear");
    for(auto &line : board)
    {
        for(auto p_block : line)
        {
            if(p_block)
            {
                std::stringstream ss;
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

                std::cout << "[";

                if(p_block->get_value() < 100)
                    std::cout << " ";
                if(p_block->get_value() < 10)
                    std::cout << " ";

                std::cout << str;

                std::cout << "]";
            }
            else
                std::cout << "[   ]";
        }
        std::cout << std::endl;
    }
}


//----------------------------------------------------------------------------//
// Entry Point                                                                //
//----------------------------------------------------------------------------//
int
main()
{
    auto values_gen = Core2048::PresetValuesGenerator("./resources/values.txt");
    auto core       = Core2048::GameCore(&values_gen, 4, 4, 150);

    std::stringstream ss;
    std::string input = "";
    int input_i = 0;

    auto p_block = core.generate_next_block();
    while(1)
    {
        print_board(core.get_board(), p_block);
        std::cout << ss.str() << std::endl;
        std::cout << "Dir: ";

        char a;
        if(input_i < input.size())
            a = input[input_i++];
        else
            std::cin >> a;

        ss << a;

        auto dir = Core2048::GameCore::Direction::Up;

        if(a == 'w') dir = Core2048::GameCore::Direction::Up;
        if(a == 's') dir = Core2048::GameCore::Direction::Down;
        if(a == 'a') dir = Core2048::GameCore::Direction::Left;
        if(a == 'd') dir = Core2048::GameCore::Direction::Right;

        if(core.is_valid_move(dir))
        {
            auto a = core.make_move(dir);
            if(a.moved_blocks.size() != 0)
            {
                auto old_coord = a.moved_blocks[0]->get_old_coord();
                auto coord     = a.moved_blocks[0]->get_coord    ();

                printf(
                    "(%d,%d)\n(%d,%d)\n",
                    old_coord.y,
                    old_coord.x,
                    coord.y,
                    coord.x
                );
            }

            p_block = core.generate_next_block();
        }
    }
}
