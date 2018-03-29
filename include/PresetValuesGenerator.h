
#pragma once
// std
#include <string>
#include <map>
#include <utility>
#include <vector>
// Core2048
#include "Core2048_Utils.h"
#include "IValuesGenerator.h"


NS_CORE2048_BEGIN

class PresetValuesGenerator :
    public IValuesGenerator
{
    //------------------------------------------------------------------------//
    // Enums / Constants / Typedef                                            //
    //------------------------------------------------------------------------//
private:
    typedef std::map<int, std::vector<std::pair<int,int>>> ValuesMatrix;


    //------------------------------------------------------------------------//
    // CTOR                                                                   //
    //------------------------------------------------------------------------//
public:
    ///-------------------------------------------------------------------------
    /// @brief Constructs a ValueGenerator based on the specs found on file.
    /// @note An example of such file is found in ./resouces/values.txt
    PresetValuesGenerator(const std::string &filename);


    //------------------------------------------------------------------------//
    // IValuesGenerator Interface                                             //
    //------------------------------------------------------------------------//
public:
    virtual int  generate_value(CoreRandom::Random &rnd_gen) override;
    virtual void set_max_value(int value) override;


    //------------------------------------------------------------------------//
    // iVars                                                                  //
    //------------------------------------------------------------------------//
private:
    int          m_max_value;
    ValuesMatrix m_values_matrix;
};

NS_CORE2048_END
