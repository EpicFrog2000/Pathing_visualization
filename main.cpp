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
        std::vector<fragment> roadspath = find_path(roads, 568938202, 2924652312);
        print_fragments(roadspath);
        std::vector<float> verts = fragments_to_vertices(roadspath, roadspath);
        for (int i = 0; i < verts.size(); i+=6)
        {
            std::cout << verts[i] << ", "<< verts[i+1] << ", "<< verts[i+2] << ", "<< verts[i+3] << ", "<< verts[i+4] << ", "<< verts[i+5] << std::endl;
        }
        
        std::vector<unsigned short int> inds = fragments_to_indices(roadspath);
        for (int i = 0; i < inds.size()-1; i++)
        {
            std::cout << inds[i] << ", " << inds[i+1] << std::endl;
        }
        

    }
    return 0;
}

// g++ main.cpp extract_data.cpp && a