#pragma once
// AmazingCow Libs.
#include "CoreRandom/CoreRandom.h"
// Core2048
#include "Core2048_Utils.h"


NS_CORE2048_BEGIN

class IValuesGenerator
{
    //COWTODO: We should disable the CTORs, copy / move operators, etc...

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
    virtual int  generate_value(CoreRandom::Random &rnd_gen) = 0;

    ///-------------------------------------------------------------------------
    /// @brief Set the max value on the current board.
    virtual void set_max_value(int v) = 0;
}; // IValuesGenerator

NS_CORE2048_END
