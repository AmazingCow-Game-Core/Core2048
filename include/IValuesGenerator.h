//----------------------------------------------------------------------------//
//               █      █                                                     //
//               ████████                                                     //
//             ██        ██                                                   //
//            ███  █  █  ███        IValuesGenerator.h                        //
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
//AmazingCow Libs.
#include "CoreRandom.h"
//Core2048
#include "Core2048_Utils.h"


NS_CORE2048_BEGIN

class IValuesGenerator
{
    //COWTODO: We should disable the CTORs, copy / move operators, etc...

    // Interface Methods //
public:
    ///@brief Generates a new value for the block.
    ///@detail
    ///  This method is called every time that a new block
    ///  will enter in game, but is up to the implementor decide which
    ///  value will actually be generate.
    ///  Implementors might want take a look on the set_max_value() method
    ///  that is called to give a hint of the max value of the current board.
    ///@param rnd_gen
    ///  The current CoreRandom::Random object that GameCore
    ///  is using to generate random numbers.
    ///@see set_max_value(), GameCore.
    virtual int  generate_value(CoreRandom::Random &rnd_gen) = 0;

    ///@brief Set the max value on the current board.
    virtual void set_max_value(int v) = 0;
};

NS_CORE2048_END
