#include <iostream>
#include <fstream>
#include <vector>
#include "nlohmann/json.hpp"
#include "extract_data.hpp"
using json = nlohmann::json;

std::vector<road> convert_json_data_to_my_vector(const std::string& filename)
{
    // Open json
    std::ifstream file(filename);
    // Init structures for keeping temp data about roads
    std::vector<road> roads;
    if (file.is_open()) {
        nlohmann::json json_data;
        file >> json_data;
        if (json_data.contains("elements") && json_data["elements"].is_array())
        {
            for (const auto& element : json_data["elements"])
            {
                // get ID drogi
                unsigned int id = element["id"].get<unsigned int>();

                // get ID fragmentów należące do tej drogi
                std::vector<unsigned int> nodes = element["nodes"];

                // get koordynaty fragmentów  należące do tej drogi
                std::vector<json> coords = element["geometry"].get<std::vector<json>>();
                std::vector<coordinates> points;
                for (const auto& coord : coords) {
                    struct coordinates p(coord["lat"].get<float>(), coord["lon"].get<float>());
                    points.push_back(p);
                }

                // sklej ze sobą fragmenty i kordynaty drogi
                std::vector<fragment> fragments;
                for (int i = 0; i < nodes.size(); i++)
                {
                    struct fragment frag(nodes[i], points[i]);
                    fragments.push_back(frag);
                }

                // Wpierdol dane do vectora
                struct road current_road(id, fragments);
                roads.push_back(current_road);
            }
        }
        else
        {
            std::cout << "Invalid JSON format. 'elements' array not found or not an array." << std::endl;
        }
    }
    else {
        std::cout << "Couldn't open file." << std::endl;
    }
    return roads;
}

void print_fragments(const std::vector<fragment>& fragments) {
    std::cout << "Fragmenty: " << std::endl;
    for (const auto& frag : fragments) {
        std::cout << "node_id: " << frag.node_id << " koordynaty: lan: " << frag.p.latitude << ", lon: " << frag.p.longitude << std::endl;
    }
}


void print_roads(const std::vector<road>& roads) {
    for (const auto& r : roads) {
        std::cout << "Node_ID: " << r.node_ID << std::endl;
        print_fragments(r.fragments);
        std::cout << std::endl;
    }
}

std::vector<road> find_connected_roads(const std::vector<road>& roads, const unsigned int& current_road_ID, const unsigned int& current_fragment_ID) {
    std::vector<road> connected;
    for (const auto& r : roads) {
        for (const auto& frag : r.fragments) {
            if (frag.node_id == current_fragment_ID && current_road_ID != r.node_ID)
            {
                connected.push_back(r);
                break;
            }
        }
    }
    return connected;
}
std::vector<fragment> find_next_moves(const std::vector<road>& roads, const unsigned int& current_road_ID, const unsigned int& current_fragment_ID) {
    std::vector<fragment> next_moves;
    std::vector<road> connected = find_connected_roads(roads, current_road_ID, current_fragment_ID);
    for (const auto& r : roads) {
        struct fragment prev_frag(-1, { -1,-1 });
        for (const auto& frag : r.fragments) {
            if (prev_frag.node_id != -1 && prev_frag.p.latitude != -1 && prev_frag.p.longitude != -1)
            {
                if (frag.node_id == current_fragment_ID)
                {
                    next_moves.push_back(prev_frag);
                }
                else if (prev_frag.node_id == current_fragment_ID)
                {
                    next_moves.push_back(frag);
                }
            }
            prev_frag = frag;
        }
    }
    return next_moves;
}

float calculate_distance_between_fragments(const struct fragment& first_fragment, const struct fragment& second_fragment) {
    float dx = second_fragment.p.latitude - first_fragment.p.latitude;
    float dy = second_fragment.p.longitude - first_fragment.p.longitude;
    return std::sqrt(dx * dx + dy * dy);
}



std::vector<road> find_path(const std::vector<road>& roads, const unsigned int& start_fragment_id, const unsigned int& end_fragment_id) {
    // cmon... do the thing
    std::vector<unsigned int> visited;
    unsigned int current = start_fragment_id;
    visited.push_back(start_fragment_id);

    return {};
}