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
                    coordinates p(coord["lat"].get<float>(), coord["lon"].get<float>());
                    points.push_back(p);
                }

                // sklej ze sobą fragmenty i kordynaty drogi
                std::vector<fragment> fragments;
                for (int i = 0; i < nodes.size(); i++)
                {
                    fragment frag(nodes[i], points[i]);
                    fragments.push_back(frag);
                }

                // Wpierdol dane do vectora
                road current_road(id, fragments);
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

void print_roads(const std::vector<road>& roads) {
    for (auto road : roads) {
        std::cout << "Node_ID: " << road.node_ID << std::endl;
        std::cout << "Fragmenty: " << std::endl;
        for (auto fragment : road.fragments) {
            std::cout << "node_id: " << fragment.node_id << " koordynaty: lan: "
                << fragment.p.latitude << ", lon: " << fragment.p.longitude << std::endl;
        }
        std::cout << std::endl;
    }
}

std::vector<road> get_connections_with_node(const std::vector<road>& roads, const unsigned int& fragment_id) {
    std::vector<road> roads_output;
    for (auto road : roads) {
        for (auto fragment : road.fragments) {
            if (fragment.node_id == fragment_id) {
                roads_output.push_back(road);
                break;
            }
        }
    }
    return roads_output;
}

std::vector<road> get_connections_with_node(const std::vector<road>& roads, const unsigned int& start_fragment_id, const unsigned int& end_fragment_id) {
    // cmon... do the thing
}