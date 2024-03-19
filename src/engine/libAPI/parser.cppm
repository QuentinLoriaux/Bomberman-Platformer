module;

#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <rapidxml.hpp>
#include <rapidxml_utils.hpp>
#include <rapidxml_print.hpp>



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




export void saveXML(int width, int height, std::vector<std::string> cases){
    xml_document<> doc; // create XML document object

    
    xml_node<>* root = doc.allocate_node(node_element, "Board");
    xml_node<>* child = doc.allocate_node(node_element, "height");child->value(std::to_string(height).c_str());
    root->append_node(child);
    child = doc.allocate_node(node_element, "width");child->value(std::to_string(width).c_str());
    root->append_node(child);
    for (auto& bloc : cases) {
        child = doc.allocate_node(node_element, "Bloc");child->value(bloc.c_str());
        root->append_node(child);
    }
    doc.append_node(root);
    
    
    

    int cpt = 0;
    bool exists = true;
    // while (exists){
    //     std::string filename = "./game_files/boards/map"+std::to_string(cpt)+".xml";
    //     std::ifstream file(filename);
    //     if (!file){
    //         std::ofstream outFile(filename); 
    //         outFile << doc; 
    //         outFile.close(); 
    //         exists = false;
    //     }
    //     cpt++;
    // }
    std::string filename = "./game_files/boards/map"+std::to_string(cpt)+".xml";
    std::ifstream file(filename);
    std::ofstream outFile(filename); 
    outFile << doc; 
    outFile.close(); 
    doc.clear();

}