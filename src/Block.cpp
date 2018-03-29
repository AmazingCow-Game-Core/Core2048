// Header
#include "include/Block.h"

// Usings
USING_NS_CORE2048;

//----------------------------------------------------------------------------//
// CTOR / DTOR                                                                //
//----------------------------------------------------------------------------//
Block::Block(const CoreCoord::Coord &coord, int value) :
    m_coord    (coord),
    m_value    (value),
    m_old_coord(coord),
    m_old_value(value)
{
    // Empty...
}


//----------------------------------------------------------------------------//
// Public Methods                                                             //
//----------------------------------------------------------------------------//
const CoreCoord::Coord Block::get_coord() const
{
    return m_coord;
}

int Block::get_value() const
{
    return m_value;
}

const CoreCoord::Coord Block::get_old_coord() const
{
    return m_old_coord;
}

int Block::get_old_value() const
{
    return m_old_value;
}


//----------------------------------------------------------------------------//
// Private Methods                                                            //
//----------------------------------------------------------------------------//
// Only accessible to CoreGame.
void Block::set_coord(const CoreCoord::Coord &coord)
{
    m_old_coord = m_coord;
    m_coord     = coord;
}

void Block::set_value(int value)
{
    m_old_value = m_value;
    m_value     = value;
}
