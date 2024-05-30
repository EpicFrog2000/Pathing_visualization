#include <iostream>
#include <vector>
#include <iomanip> // For precision
#include "extract_data.hpp"

int main()
{
    std::cout << std::setprecision(8);

    std::vector<road> roads = convert_json_data_to_my_vector("roadss.json");
    //print_roads(roads);
    if (roads.size() > 0)
    {
        std::vector<road> r2 = get_connections_with_node(roads, 1388325005);
        print_roads(r2);
    }



    return 0;
}

// g++ main.cpp ExtractData.cpp && a