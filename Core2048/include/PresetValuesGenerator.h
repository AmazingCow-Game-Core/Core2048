
#pragma once
// std
#include <string>
#include <map>
#include <utility>
#include <vector>
// AmazingCow Libs
#include "acow/cpp_goodies.h"
// Core2048
#include "Core2048_Utils.h"
#include "IValuesGenerator.h"


NS_CORE2048_BEGIN

class PresetValuesGenerator
    : public IValuesGenerator
{
    //------------------------------------------------------------------------//
    // Enums / Constants / Typedef                                            //
    //------------------------------------------------------------------------//
private:
    typedef std::map<u32, std::vector<std::pair<u32,u32>>> ValuesMatrix;


    //------------------------------------------------------------------------//
    // CTOR                                                                   //
    //------------------------------------------------------------------------//
public:
    ///-------------------------------------------------------------------------
    /// @brief Constructs a ValueGenerator based on the specs found on file.
    /// @note An example of such file is found in resouces/values.txt
    PresetValuesGenerator(const std::string &filename) noexcept;


    //------------------------------------------------------------------------//
    // IValuesGenerator Interface                                             //
    //------------------------------------------------------------------------//
public:
    virtual u32  generate_value(CoreRandom::Random &rnd_gen) noexcept override;
    virtual void set_max_value(u32 value) noexcept override;


    //------------------------------------------------------------------------//
    // iVars                                                                  //
    //------------------------------------------------------------------------//
private:
    u32          m_max_value;
    ValuesMatrix m_values_matrix;
};

NS_CORE2048_END
