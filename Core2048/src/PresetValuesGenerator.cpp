// Header
#include "../include/PresetValuesGenerator.h"
// std
#include <fstream>
#include <sstream>
// AmazingCow Libs.
#include "CoreAssert/CoreAssert.h"
#include "CoreGame/CoreGame.h"

// Usings
USING_NS_CORE2048;


//----------------------------------------------------------------------------//
// CTOR                                                                       //
//----------------------------------------------------------------------------//
PresetValuesGenerator::PresetValuesGenerator(const std::string &filename)
{
    //Open File.
    std::ifstream in_stream;
    in_stream.open(filename);

    COREASSERT_ASSERT(
        in_stream.is_open(),
        "Cannot open file: (%s)",
        filename.c_str()
    );

    // Parse File.
    // Data is this format:
    //    Max Curr Value | GenMax (chance percent)
    //    int() char('|') int() char('(') (int) char(')')
    // Lines starting with # are ignored.
    // Whitespace are ignored.
    while(!in_stream.eof())
    {
        std::string line;
        std::getline(in_stream, line);

        // Comments - Ignore.
        if(line.size() != 0 && line[0] == '#')
            continue;

        int  MaxCurrValue, GenMax, ChangePercent;
        char dummy;

        std::stringstream ss(line);
        ss >> MaxCurrValue >> dummy;


        std::vector<std::pair<int, int>> gen_percent_vec;
        while(!ss.eof())
        {
            std::string gen_per_token;
            ss >> gen_per_token;

            sscanf(gen_per_token.c_str(), "%d(%d)", &GenMax, &ChangePercent);

            gen_percent_vec.push_back(
                std::make_pair(GenMax, ChangePercent)
            );
        }

        m_values_matrix[MaxCurrValue] = gen_percent_vec;
    }
}


//----------------------------------------------------------------------------//
// IValuesGenerator Interface                                                 //
//----------------------------------------------------------------------------//
int PresetValuesGenerator::generate_value(CoreRandom::Random &rnd_gen)
{
    COREASSERT_ASSERT(
        (m_max_value >= 2),
        "m_max_value(%d) must be >= 2.",
        m_max_value
    );

    COREASSERT_ASSERT(
        m_values_matrix.find(m_max_value) != m_values_matrix.end(),
        "m_max_value(%d) don't exists... check your input data.",
        m_max_value
    );

    auto &gen_per_vec = m_values_matrix[m_max_value];
    auto rnd_value    = rnd_gen.next(0, 100);

    // The random value generated is in range of (0,100)
    // and the data is in format of ValueToBeGenerated - Percentage
    // So we sum the previous percentages to make the random value
    // in map to the percentage.
    auto sum = 0;
    for(int i = 0; i < gen_per_vec.size(); ++i)
    {
        sum += gen_per_vec[i].second;

        if(rnd_value <= sum)
            return gen_per_vec[i].first;
    }

    COREASSERT_ASSERT(false, "Cannot be here...");
    return -1; //Makes compiler happy...
}

void PresetValuesGenerator::set_max_value(int value)
{
    COREASSERT_ASSERT(
        (value >= 2),
        "value(%d) must be >= 2.",
        value
    );

    m_max_value = value;
}
