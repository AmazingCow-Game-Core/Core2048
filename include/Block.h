
#pragma once
// std
#include <memory> // shared_ptr
// AmazingCow Libs
#include "CoreCoord.h"
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
    Block(const CoreCoord::Coord &coord, int value);

    ///-------------------------------------------------------------------------
    /// @brief Destructs the Block instance.
    ~Block();


    //------------------------------------------------------------------------//
    // Public Methods                                                         //
    //------------------------------------------------------------------------//
public:
    ///-------------------------------------------------------------------------
    /// @brief Gets the current coord of block.
    /// @returns The current coord of block.
    /// @see get_value(), get_old_coord(), get_old_value().
    const CoreCoord::Coord get_coord() const;

    ///-------------------------------------------------------------------------
    /// @brief Gets the current value of block.
    /// @returns The current value of block.
    /// @see get_coord(), get_old_coord(), get_old_value().
    int get_value() const;

    ///-------------------------------------------------------------------------
    /// @brief Gets the previous coord of block.
    /// @returns
    ///   The previous coord of the block, if there's no
    ///   previous coord, this will return the current coord.
    /// @see get_coord(), get_old_coord(), get_old_value().
    const CoreCoord::Coord get_old_coord() const;

    ///-------------------------------------------------------------------------
    /// @brief Gets the previous value of block.
    /// @return
    ///   The previous value of block, if there's no
    ///   previous value, this will return the current value.
    /// @see get_coord(), get_old_coord(), get_value().
    int get_old_value() const;


    //------------------------------------------------------------------------//
    // Private Methods                                                        //
    //------------------------------------------------------------------------//
private:
    //--------------------------------------------------------------------------
    // Only accessible to CoreGame.
    void set_coord(const CoreCoord::Coord &coord);
    void set_value(int value);


    //------------------------------------------------------------------------//
    // iVars                                                                  //
    //------------------------------------------------------------------------//
private:
    CoreCoord::Coord m_coord;
    int              m_value;

    CoreCoord::Coord m_old_coord;
    int              m_old_value;
};

NS_CORE2048_END
