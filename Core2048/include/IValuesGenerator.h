//~---------------------------------------------------------------------------//
//                     _______  _______  _______  _     _                     //
//                    |   _   ||       ||       || | _ | |                    //
//                    |  |_|  ||       ||   _   || || || |                    //
//                    |       ||       ||  | |  ||       |                    //
//                    |       ||      _||  |_|  ||       |                    //
//                    |   _   ||     |_ |       ||   _   |                    //
//                    |__| |__||_______||_______||__| |__|                    //
//                             www.amazingcow.com                             //
//  File      : IValuesGenerator.h                                            //
//  Project   : Core2048                                                      //
//  Date      : Feb 12, 2017                                                  //
//  License   : GPLv3                                                         //
//  Author    : n2omatt <n2omatt@amazingcow.com>                              //
//  Copyright : AmazingCow - 2017, 2018                                       //
//                                                                            //
//  Description :                                                             //
//                                                                            //
//---------------------------------------------------------------------------~//

#pragma once
// AmazingCow Libs.
#include "CoreRandom/CoreRandom.h"
#include "acow/cpp_goodies.h"
// Core2048
#include "Core2048_Utils.h"

NS_CORE2048_BEGIN

class IValuesGenerator
{
    //------------------------------------------------------------------------//
    // CTOR / DTOR                                                            //
    //------------------------------------------------------------------------//
protected:
    inline   IValuesGenerator() noexcept = default;
    virtual ~IValuesGenerator() noexcept = default;


    //------------------------------------------------------------------------//
    // Interface Methods                                                      //
    //------------------------------------------------------------------------//
public:
    ///-------------------------------------------------------------------------
    /// @brief Generates a new value for the block.
    /// @detail
    ///    This method is called every time that a new block
    ///    will enter in game, but is up to the implementor decide which
    ///    value will actually be generate.
    ///    Implementors might want take a look on the set_max_value() method
    ///    that is called to give a hint of the max value of the current board.
    /// @param rnd_gen
    ///    The current CoreRandom::Random object that GameCore
    ///    is using to generate random numbers.
    /// @see set_max_value(), GameCore.
    virtual u32 generate_value(CoreRandom::Random &rnd_gen) noexcept = 0;

    ///-------------------------------------------------------------------------
    /// @brief Set the max value on the current board.
    virtual void set_max_value(u32 v) noexcept  = 0;

}; // IValuesGenerator

NS_CORE2048_END
