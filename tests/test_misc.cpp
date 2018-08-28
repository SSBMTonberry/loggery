//
// Created by robin on 28.08.18.
//

#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include <iostream>
#include <fstream>
#include <sstream>
#include <iterator>
#include <vector>

#include "../src/classes/Timer.h"

TEST_CASE( "Simple timer - test 1 fps", "[timer]" ) {
    ly::Timer timer;

    bool run = true;
    int i = 0;
    while(run)
    {
        if(timer.update(10))
        {
            ++i;
            printf("Well yo %d\n", i);
        }

        if(i > 9)
            run = false;
    }
    std::cout << "Time elapsed " << timer.getTotalDuration().count() << " seconds.";
    REQUIRE( true );
}

TEST_CASE("Simple timer - Time to read log-file", "[timer]" )
{
    ly::Timer timer;
    std::ifstream ifs("../test_logs/test.log");
    if (  !ifs )
    {
        throw std::runtime_error("Error opening file.");
    }

    std::vector<std::string> table;
    std::string line;
    while (std::getline(ifs, line))
    {
        //std::istringstream iss(line);
        table.emplace_back(line);
        //table.emplace_back(std::istream_iterator<std::string>(iss));
    }
    std::cout << "Time elapsed " << timer.getTotalDuration().count() << " seconds.";
}