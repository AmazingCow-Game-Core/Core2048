//----------------------------------------------------------------------------//
//               █      █                                                     //
//               ████████                                                     //
//             ██        ██                                                   //
//            ███  █  █  ███        PresetValuesGenerator.h                   //
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
#include <string>
#include <map>
#include <utility>
#include <vector>
//Core2048
#include "Core2048_Utils.h"
#include "IValuesGenerator.h"


NS_CORE2048_BEGIN

class PresetValuesGenerator :
    public IValuesGenerator
{
    // Enums / Constants / Typedef //
private:
    typedef std::map<int, std::vector<std::pair<int,int>>> ValuesMatrix;


    // CTOR //
public:
    PresetValuesGenerator(const std::string &filename);


    // IValuesGenerator Interface //
public:
    virtual int  generate_value(CoreRandom::Random &rnd_gen) override;
    virtual void set_max_value(int value) override;

    // iVars //
private:
    int m_max_value;
    ValuesMatrix m_values_matrix;
};

NS_CORE2048_END
