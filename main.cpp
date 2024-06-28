#include <iostream>
#include <vector>
#include <iomanip> // For precision
#include "extract_data.hpp"

// DISCLAIMER:
// Is is not considering roadtype maxspeed, surface, onewayness, access or elevation for now

int main()
{
    std::cout << std::setprecision(8);

    std::vector<road> roads = convert_json_data_to_my_vector("roads.json");
    //print_roads(roads);
    if (roads.size() > 0)
    {
        std::vector<fragment> roadspath = find_path(roads, 34662243, 1388325005);
        print_fragments(roadspath);
    }
    return 0;
}

// g++ main.cpp extract_data.cpp && a