//#include "Market.h"
//#include "json.hpp"
//#include <iostream>
//#include <iomanip>
//#include <fstream>
//
//using json = nlohmann::json;
//
//Market::Market(const std::string& jsonPath) {
//    std::ifstream file(jsonPath);
//    if (!file.is_open()) {
//        std::cerr << "Failed to open market JSON.\n";
//        return;
//    }
//
//    json data;
//    file >> data;
//
//    for (const auto& entry : data["Items"]) {
//        stock.emplace_back(entry);
//    }
//}
//
//void Market::DisplayItems() const {
//    if (stock.empty()) {
//        std::cout << "Market is empty.\n";
//        return;
//    }
//
//    std::cout << std::left
//        << std::setw(3) << "#"
//        << std::setw(15) << "Name"
//        << std::setw(10) << "Type"
//        << std::setw(10) << "Strength"
//        << std::setw(6) << "Price\n";
//
//    int i = 1;
//    for (const auto& item : stock) {
//        std::cout << std::setw(3) << i++
//            << std::setw(15) << item.GetName()
//            << std::setw(10) << item.GetType()
//            << std::setw(10) << item.GetStrength()
//            << std::setw(6) << item.GetPrice() << "\n";
//    }
//}
//
//void Market::DisplayTypeItems(const std::string& type) const {
//    int i = 1;
//    for (const auto& item : stock) {
//        if (item.GetType() == type) {
//            std::cout << i << ". " << item.GetName()
//                << " (Strength: " << item.GetStrength()
//                << ", Price: " << item.GetPrice() << ")\n";
//        }
//        ++i;
//    }
//}
