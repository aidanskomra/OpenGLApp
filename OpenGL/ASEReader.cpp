#include "ASEReader.h"
#include <algorithm>
#include <sstream>
#include <iostream>

void ASEReader::ParseASEFile(const char* _fileName)
{
	std::vector<std::string> ASEFile;
	ReadFile(_fileName, ASEFile);

	ParseMaterials(ASEFile);
	ParseGeoObjects(ASEFile);
}

void ASEReader::ReadFile(const char* _fileName, std::vector<std::string>& _file)
{
	std::string line;
	std::ifstream file(_fileName);
	while (getline(file, line))
	{
		_file.push_back(line);
	}
	file.close();
}

void ASEReader::ParseMaterials(std::vector<std::string>& _file) {
	std::vector<std::string> _materials;

	// Locate the MATERIAL_LIST block
	if (GetBlock("*MATERIAL_LIST", _file, _materials) == -1) {
		std::cerr << "Error: MATERIAL_LIST block not found." << std::endl;
		return;
	}

	// Debug: Output MATERIAL_LIST block size
	std::cerr << "Debug: MATERIAL_LIST block size: " << _materials.size() << std::endl;

	// Extract MATERIAL_COUNT
	std::string materialCountStr = ExtractValue(_materials, "*MATERIAL_COUNT");
	if (materialCountStr.empty()) {
		std::cerr << "Error: MATERIAL_COUNT not found in MATERIAL_LIST." << std::endl;
		return;
	}

	int materialCount = 0;
	try {
		materialCount = std::stoi(materialCountStr);
	}
	catch (const std::exception& e) {
		std::cerr << "Error: Invalid MATERIAL_COUNT value: " << materialCountStr << " (" << e.what() << ")" << std::endl;
		return;
	}

	std::cerr << "Debug: MATERIAL_COUNT = " << materialCount << std::endl;

	// Parse each MATERIAL block
	for (int count = 0; count < materialCount; count++) {
		std::string materialTag = "*MATERIAL " + std::to_string(count);
		std::vector<std::string> _materialBlock;

		if (GetBlock(materialTag.c_str(), _materials, _materialBlock) == -1) {
			std::cerr << "Error: MATERIAL " << count << " block not found." << std::endl;
			continue;
		}

		std::cerr << "Debug: MATERIAL " << count << " block size: " << _materialBlock.size() << std::endl;

		// Create a new Material object
		Material* material = new Material();
		material->Index = count;

		// Parse Material properties
		material->Name = ExtractValue(_materialBlock, "*MATERIAL_NAME");
		material->Class = ExtractValue(_materialBlock, "*MATERIAL_CLASS");
		material->AmbientColor = ParseStringToVec3(ExtractValue(_materialBlock, "*MATERIAL_AMBIENT"));
		material->DiffuseColor = ParseStringToVec3(ExtractValue(_materialBlock, "*MATERIAL_DIFFUSE"));
		material->SpecularColor = ParseStringToVec3(ExtractValue(_materialBlock, "*MATERIAL_SPECULAR"));

		try {
			material->Shine = std::stof(ExtractValue(_materialBlock, "*MATERIAL_SHINE"));
			material->ShineStrength = std::stof(ExtractValue(_materialBlock, "*MATERIAL_SHINESTRENGTH"));
			material->Transparancy = std::stof(ExtractValue(_materialBlock, "*MATERIAL_TRANSPARENCY"));
			material->WireSize = std::stof(ExtractValue(_materialBlock, "*MATERIAL_WIRESIZE"));
		}
		catch (const std::exception& e) {
			std::cerr << "Error parsing float property for MATERIAL " << count << ": " << e.what() << std::endl;
		}

		material->Shading = ExtractValue(_materialBlock, "*MATERIAL_SHADING");

		// Debug output parsed material properties
		std::cerr << "Debug: Parsed material " << count << " - Name: " << material->Name
			<< ", Class: " << material->Class << std::endl;

		// Parse Maps
		ParseMap("*MAP_DIFFUSE", "DIFFUSE", _materialBlock, material);
		ParseMap("*MAP_SPECULAR", "SPECULAR", _materialBlock, material);
		ParseMap("*MAP_BUMP", "BUMP", _materialBlock, material);

		// Add to the Materials list
		Materials.push_back(material);
	}

	std::cerr << "Debug: Finished parsing MATERIAL_LIST." << std::endl;
}


void ASEReader::ParseGeoObjects(std::vector<std::string>& _file) {
	std::vector<std::string> _geomObject;
	int index = GetBlock("*GEOMOBJECT", _file, _geomObject);

	while (index != -1) {
		if (_geomObject.empty()) {
			std::cerr << "Error: GEOMOBJECT block is empty." << std::endl;
			break; // Exit loop if block is empty
		}

		std::cerr << "Debug: Found GEOMOBJECT block with size: " << _geomObject.size() << std::endl;

		GeoObject* g = new GeoObject();

		// Parse Node Name
		g->Name = ExtractValue(_geomObject, "*NODE_NAME");
		if (g->Name.empty()) {
			std::cerr << "Error: NODE_NAME not found for GEOMOBJECT." << std::endl;
			delete g;
			break;
		}

		// Parse Material Reference
		std::string materialRefStr = ExtractValue(_geomObject, "*MATERIAL_REF");
		if (materialRefStr.empty()) {
			std::cerr << "Error: MATERIAL_REF not found for GEOMOBJECT: " << g->Name << std::endl;
			delete g;
			break;
		}
		g->MaterialID = std::stoi(materialRefStr);

		// Debug: Output parsed GEOMOBJECT properties
		std::cerr << "Debug: Parsed GEOMOBJECT - Name: " << g->Name
			<< ", Material ID: " << g->MaterialID << std::endl;

		GeoObjects.push_back(g);

		// Move to the next GEOMOBJECT
		index = GetBlock("*GEOMOBJECT", _file, _geomObject, index + 1);
	}

	// Final Debug Output
	std::cerr << "Debug: Total GeoObjects parsed: " << GeoObjects.size() << std::endl;
}


int ASEReader::GetBlock(const char* _tag, std::vector<std::string>& _lines, std::vector<std::string>& _block, int _start) {
	_block.clear();
	bool foundTag = false;

	for (int i = _start; i < _lines.size(); i++) {
		std::string line = _lines[i];
		line.erase(0, line.find_first_not_of(" \t")); // Trim leading spaces

		// Check if the tag matches
		if (line.find(_tag) != std::string::npos) {
			std::cerr << "Debug: Found tag: " << _tag << " at line " << i << std::endl; // Debug line number
			foundTag = true;

			int indent = 0;
			for (int j = i + 1; j < _lines.size(); j++) {
				std::string nestedLine = _lines[j];
				nestedLine.erase(0, nestedLine.find_first_not_of(" \t")); // Trim spaces

				if (nestedLine.find('{') != std::string::npos) indent++;
				if (nestedLine.find('}') != std::string::npos) {
					if (indent == 0) {
						return j; // End of the block
					}
					indent--;
				}

				_block.push_back(nestedLine);
			}
			break; // Exit once the block is found
		}
	}

	if (!foundTag) {
		std::cerr << "Error: Tag not found: " << _tag << std::endl;
	}

	return -1; // Return -1 if the tag wasn't found
}



std::string ASEReader::ExtractValue(std::vector<std::string>& _lines, const char* _tag)
{
	for (int i = 0; i < _lines.size(); i++)
	{
		if (_lines[i].find(_tag) != std::string::npos)
		{
			std::string line = _lines[i];
			std::replace(line.begin(), line.end(), '\t', ' ');
			line.erase(0, line.find_first_not_of(" \n\r\t"));
			line.erase(0, line.find(" ") + 1);
			line.erase(std::remove(line.begin(), line.end(), '\"'), line.end());
			line.erase(0, line.find_first_not_of(" \n\r\t"));

			return line;
		}
	}
	
	return std::string();
}

void ASEReader::FindAllTags(const char* _tag, std::vector<std::string>& _lines, std::vector<std::string>& _block)
{
	_block.clear();
	for (int i = 0; i < _lines.size(); i++)
	{
		if (_lines[i].find(_tag) != std::string::npos)
		{
			_block.push_back(_lines[i]);
		}
	}
}

glm::vec3 ASEReader::ParseStringToVec3(std::string _values)
{
	std::vector<std::string> result;
	std::stringstream ss(_values);
	std::string item = "";

	while (getline(ss, item, ' '))
	{
		result.push_back(item);
	}
	return glm::vec3{ std::stof(result[0]), std::stof(result[1]), std::stof(result[2]) };
}

void ASEReader::ParseMap(const char* _mapName, const char* _name, std::vector<std::string>& _materialBlock, ASEReader::Material* _material) {
	std::vector<std::string> _mapBlock;
	if (GetBlock(_mapName, _materialBlock, _mapBlock) == -1) {
		std::cerr << "Warning: Map " << _mapName << " not found." << std::endl;
		return;
	}

	ASEReader::Map map;
	map.Name = _name;
	map.TextureFileName = ExtractValue(_mapBlock, "*BITMAP");
	map.UVW_U_Offset = std::stof(ExtractValue(_mapBlock, "*UVW_U_OFFSET"));
	map.UVW_V_Offset = std::stof(ExtractValue(_mapBlock, "*UVW_V_OFFSET"));
	map.UVW_U_Tiling = std::stof(ExtractValue(_mapBlock, "*UVW_U_TILING"));
	map.UVW_V_Tiling = std::stof(ExtractValue(_mapBlock, "*UVW_V_TILING"));

	// Debug output
	std::cerr << "Debug: Parsed " << _name << " Map - Texture File: " << map.TextureFileName
		<< ", UV Offset: (" << map.UVW_U_Offset << ", " << map.UVW_V_Offset << ")"
		<< ", UV Tiling: (" << map.UVW_U_Tiling << ", " << map.UVW_V_Tiling << ")" << std::endl;

	_material->Maps.push_back(map);
}

void ASEReader::ExtractVectorList(std::vector<glm::vec3>& _list, std::vector<std::string>& _vertexList)
{
	for (auto& vertex : _vertexList)
	{
		std::replace(vertex.begin(), vertex.end(), '\t', ' ');
		vertex.erase(0, vertex.find_first_not_of(' '));

		std::vector<std::string> result;
		std::stringstream ss(vertex);
		std::string item = "";

		while (getline(ss, item, ' '))
		{
			if (item != "")
			{
				result.push_back(item);
			}
		}
		_list.push_back(glm::vec3{ std::stof(result[2]), std::stof(result[3]), std::stof(result[4]) });
	}
}