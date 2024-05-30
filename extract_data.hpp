#ifndef EXTRACT_DATA_HPP
#define EXTRACT_DATA_HPP
#include <vector>

struct coordinates {
    float latitude;
    float longitude;
    coordinates(float lat, float lon) : latitude(lat), longitude(lon) {}
};

struct fragment {
    unsigned int node_id;
    coordinates p;
    fragment(unsigned int id, coordinates coords) : node_id(id), p(coords) {}
};

struct road
{
    road(unsigned int id, std::vector<fragment> frags) {
        node_ID = id;
        fragments = frags;
    }
    // Unique Id of road
    unsigned int node_ID;
    // nodes_id and points in space that this road is made of
    std::vector<fragment> fragments;
};

// Phrases data from roads.json downloaded from www.openstreetmap.org
std::vector<road> convert_json_data_to_my_vector(const std::string& filename);

// Print all roads
void print_roads(const std::vector<road>& roads);

// returns IDs of roads that this fragment is in
std::vector<road> get_connections_with_node(const std::vector<road>& roads, const unsigned int& fragment_id);

// find path... i want to kill myself
std::vector<road> get_connections_with_node(const std::vector<road>& roads, const unsigned int& start_fragment_id, const unsigned int& end_fragment_id);




#endif