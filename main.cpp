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
        std::vector<fragment> f1 = find_next_moves(roads, 5087028, 1388325005);
        print_fragments(f1);
        std::cout << "find_connected_roads" << std::endl;
        std::vector<road> r1 = find_connected_roads(roads, 5087028, 1388325005);
        print_roads(r1);
    }
    return 0;
}

// g++ main.cpp ExtractData.cpp && a