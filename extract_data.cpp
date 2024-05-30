#include <iostream>
#include <fstream>
#include <vector>
#include <utility>
#include <set>
#include <iomanip>
#include "nlohmann/json.hpp"
#include "extract_data.hpp"
using json = nlohmann::json;

std::vector<road> convert_json_data_to_my_vector(const std::string& filename)
{
    // Open json
    std::ifstream file(filename);
    nlohmann::json json_data;
    file >> json_data;

    // Init structures for keeping temp data about roads
    std::vector<road> roads;

    if (json_data.contains("elements") && json_data["elements"].is_array())
    {
        for (const auto& element : json_data["elements"])
        {
            // ID drogi
            unsigned int id = element["id"].get<unsigned int>();

            // ID fragmentów należące do tej drogi
            std::vector<unsigned int> nodes = element["nodes"];

            // koordynaty fragmentów  należące do tej drogi
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
        std::cerr << "Invalid JSON format. 'elements' array not found or not an array." << std::endl;
    }
    return roads;
}

void print_all_roads(const std::vector<road>roads) {
    for (auto road : roads) {
        std::cout << "Node_ID: " << road.node_ID << std::endl;
        std::cout << "Fragmenty: " << std::endl;
        for (auto fragment : road.fragments) {
            std::cout << "node_id: " << fragment.node_id << " koordynaty: lan: "
                << fragment.p.latitude << ", lon: " << fragment.p.longitude << std::endl;
        }
    }
}