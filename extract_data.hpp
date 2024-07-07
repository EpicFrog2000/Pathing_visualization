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

// Print fragments
void print_fragments(const std::vector<fragment>& fragments);

// Print roads
void print_roads(const std::vector<road>& roads);

// Returns other roads connected to that node
std::vector<road> find_connected_roads(const std::vector<road>& roads, const unsigned int& current_fragment_ID);

// Returns ID of fragments in neighbouring to passed fragment
std::vector<fragment> find_next_moves(const std::vector<road>& roads, const unsigned int& current_fragment_ID);

// Returns distance between fragments
float calculate_distance_between_fragments(const struct fragment& first_fragment, const struct fragment& second_fragment);

fragment get_fragment_from_id(const std::vector<road>& roads, const unsigned int& fragment_ID);

// find path... i want to kill myself
std::vector<fragment> find_path(const std::vector<road>& roads, const unsigned int& start_fragment_id, const unsigned int& destination_fragment_id);

std::vector<float> get_verts_for_buffers(const std::vector<fragment>& fragments);

std::vector<unsigned short int> get_indices_for_buffers(const std::vector<fragment>& fragments);

#endif