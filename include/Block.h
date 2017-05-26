//----------------------------------------------------------------------------//
//               █      █                                                     //
//               ████████                                                     //
//             ██        ██                                                   //
//            ███  █  █  ███        Block.h                                   //
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
#include <memory> //shared_ptr
//AmazingCow Libs
#include "CoreCoord.h"
//Core2048
#include "Core2048_Utils.h"


NS_CORE2048_BEGIN

class Block
{
    // Friends //
public:
    friend class GameCore;

    // Enums / Constants / Typedefs //
public:
    typedef std::shared_ptr<Block> SPtr;



    // CTOR / DTOR //
public:
    Block(const CoreCoord::Coord &coord, int value);
    ~Block();


    // Public Methods //
public:
    const CoreCoord::Coord get_coord() const;
    int                    get_value() const;

    const CoreCoord::Coord get_old_coord() const;
    int                    get_old_value() const;


    // Private Methods //
private:
    //Only accessible to CoreGame.
    void set_coord(const CoreCoord::Coord &coord);
    void set_value(int value);


    // iVars //
private:
    CoreCoord::Coord m_coord;
    int              m_value;

    CoreCoord::Coord m_old_coord;
    int              m_old_value;
};

NS_CORE2048_END