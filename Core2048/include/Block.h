//~---------------------------------------------------------------------------//
//                     _______  _______  _______  _     _                     //
//                    |   _   ||       ||       || | _ | |                    //
//                    |  |_|  ||       ||   _   || || || |                    //
//                    |       ||       ||  | |  ||       |                    //
//                    |       ||      _||  |_|  ||       |                    //
//                    |   _   ||     |_ |       ||   _   |                    //
//                    |__| |__||_______||_______||__| |__|                    //
//                             www.amazingcow.com                             //
//  File      : Block.h                                                       //
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
// std
#include <memory> // shared_ptr
// AmazingCow Libs
#include "acow/math_goodies.h"
// Core2048
#include "Core2048_Utils.h"


NS_CORE2048_BEGIN

class Block
{
    //------------------------------------------------------------------------//
    // Friends                                                                //
    //------------------------------------------------------------------------//
public:
    friend class GameCore;


    //------------------------------------------------------------------------//
    // Enums / Constants / Typedefs                                           //
    //------------------------------------------------------------------------//
public:
    ///-------------------------------------------------------------------------
    /// @brief
    ///   Just to reduce verbosity, so instead of
    ///   std::shared_ptr<Core2048::Block> pBlock we can type
    ///   Core2048::Block::SPtr.
    typedef std::shared_ptr<Block> SPtr;

    //------------------------------------------------------------------------//
    // CTOR / DTOR                                                            //
    //------------------------------------------------------------------------//
public:
    ///-------------------------------------------------------------------------
    /// @brief Constructs a Block instance.
    /// @param coord - The Coord that block will be "placed".
    /// @param value - The Block's value.
    /// @note
    ///    There's no checking to ensure that the values are
    ///    valid, is user responsibility to give meaningful values.
    inline
    Block(const acow::math::Coord &coord, u32 value) noexcept
        : m_coord    (coord)
        , m_value    (value)
        , m_old_coord(coord)
        , m_old_value(value)
    {
        // Empty...
    }

    ///-------------------------------------------------------------------------
    /// @brief Destructs the Block instance.
    inline ~Block() noexcept = default;


    //------------------------------------------------------------------------//
    // Public Methods                                                         //
    //------------------------------------------------------------------------//
public:
    ///-------------------------------------------------------------------------
    /// @brief Gets the current coord of block.
    /// @returns The current coord of block.
    /// @see get_value(), get_old_coord(), get_old_value().
    constexpr inline const acow::math::Coord
    get_coord() const noexcept
    {
        return m_coord;
    }

    ///-------------------------------------------------------------------------
    /// @brief Gets the current value of block.
    /// @returns The current value of block.
    /// @see get_coord(), get_old_coord(), get_old_value().
    constexpr inline u32
    get_value() const noexcept
    {
        return m_value;
    }


    ///-------------------------------------------------------------------------
    /// @brief Gets the previous coord of block.
    /// @returns
    ///   The previous coord of the block, if there's no
    ///   previous coord, this will return the current coord.
    /// @see get_coord(), get_old_coord(), get_old_value().
    constexpr inline const acow::math::Coord
    get_old_coord() const noexcept
    {
        return m_old_coord;
    }

    ///-------------------------------------------------------------------------
    /// @brief Gets the previous value of block.
    /// @return
    ///   The previous value of block, if there's no
    ///   previous value, this will return the current value.
    /// @see get_coord(), get_old_coord(), get_value().
    constexpr inline u32
    get_old_value() const noexcept
    {
        return m_old_value;
    }


    //------------------------------------------------------------------------//
    // Private Methods                                                        //
    //------------------------------------------------------------------------//
private:
    //--------------------------------------------------------------------------
    // Only accessible to CoreGame.
    inline void
    set_coord(const acow::math::Coord &coord) noexcept
    {
        m_old_coord = m_coord;
        m_coord     = coord;
    }

    inline void
    set_value(u32 value) noexcept
    {
        m_old_value = m_value;
        m_value     = value;
    }


    //------------------------------------------------------------------------//
    // iVars                                                                  //
    //------------------------------------------------------------------------//
private:
    acow::math::Coord m_coord;
    u32               m_value;

    acow::math::Coord m_old_coord;
    u32               m_old_value;
}; // class Block

NS_CORE2048_END
