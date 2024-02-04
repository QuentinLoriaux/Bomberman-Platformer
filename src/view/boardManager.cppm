module;

import game;
#include <iostream>
#include <vector>
#include <string>
#include <memory>
#include <rapidxml.hpp>
#include <rapidxml_utils.hpp>


export module boardManager;

using namespace rapidxml;


export class Board{
    private:
        int width;
        int height;
        std::vector<std::unique_ptr<Bloc>> cases;

    public:
        Board(){parseXML("./game_files/boards/default.xml");}
        Board(const std::string& xmlFilePath){
            parseXML(xmlFilePath);
        }


        void parseXML(const std::string& xmlFilePath){
            // Read the XML file
            file<> xmlFile(xmlFilePath.c_str());
            xml_document<> doc;
            doc.parse<0>(xmlFile.data());

            // Access the root node
            xml_node<>* rootNode = doc.first_node();
            if (!rootNode) {
                std::cerr << "Error: Root node not found." << std::endl;
                return;
            }

            // Access the height node
            xml_node<>* heightNode = rootNode->first_node("height");
            if (!heightNode) {
                std::cerr << "Error: 'height' node not found." << std::endl;
                return;
            }
            height = std::stoi(heightNode->value());

            width = std::stoi(rootNode->first_node("width")->value());

            // Iterate through <Bloc> nodes
            for (xml_node<>* blocNode = rootNode->first_node("Bloc"); blocNode; blocNode = blocNode->next_sibling("Bloc")) {
                std::string blocType = blocNode->value();
                if (blocType == "Wall"){cases.push_back(std::make_unique<Wall>());}
                else if (blocType == "Air"){cases.push_back(std::make_unique<Air>());}
            }
        }

        void displayBoard() const {
            for (const auto& bloc : cases) {
                bloc->printInfo();
            }
        }
};
