module;

#include <iostream>
#include <vector>
#include <string>
#include <rapidxml.hpp>
#include <rapidxml_utils.hpp>


export module parser;

using namespace rapidxml;

export class parsedXML{
    public :
        int width;
        int height;
        std::vector<std::string> cases;

        parsedXML(const std::string &xmlFilePath){
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
                cases.push_back(blocNode->value());
            }
        }

};

