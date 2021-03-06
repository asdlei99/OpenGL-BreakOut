#include "ResourceManager.h"
#include <fstream>
#include <iostream>

#define STB_IMAGE_IMPLEMENTATION
#include <Common/stb_image.h>

std::unordered_map<std::string, Shader> ResourceManager::shaders = {};
std::unordered_map<std::string, Texture2D> ResourceManager::textures = {};

ResourceManager::ResourceManager() {

}

Shader ResourceManager::LoadShaderFromFile(const GLchar* vShaderFile, const GLchar* fShaderFile,
	const GLchar* gShaderFile) {
	std::string vShaderCode, fShaderCode, gShaderCode;
	std::ifstream ifs(vShaderFile);
	if (!ifs.is_open()) std::cout << "ERROR::ResourceManager::LoadShaderFromFile::vShaderFile::FILE_OPEN_REEOR";
	std::string tmp;
	while (std::getline(ifs, tmp)) {
		vShaderCode += tmp + "\n";
	}
	ifs.close();
	ifs.open(fShaderFile);
	if (!ifs.is_open()) std::cout << "ERROR::ResourceManager::LoadShaderFromFile::fShaderFile::FILE_OPEN_REEOR";
	while (std::getline(ifs, tmp)) {
		fShaderCode += tmp + "\n";
	}
	ifs.close();
	if (gShaderFile) {
		ifs.open(gShaderFile);
		if (!ifs.is_open()) std::cout << "ERROR::ResourceManager::LoadShaderFromFile::gShaderFile::FILE_OPEN_REEOR";
		while (std::getline(ifs, tmp)) {
			gShaderCode += tmp + "\n";
		}
	}

	Shader shader;
	shader.Compile(vShaderCode.c_str(), fShaderCode.c_str(), gShaderCode.empty() ? nullptr : gShaderCode.c_str());
	return shader;
}

Texture2D ResourceManager::LoadTextureFromFile(const GLchar* file, GLboolean alpha) {
	Texture2D texture;
	int width, height, channel;
	if (alpha) {
		texture.imageFormat = GL_RGBA;
		texture.internalFormat = GL_RGBA;
	}
	const auto data = stbi_load(file, &width, &height, &channel, 0);
	texture.Generate(width, height, data);
	
	return texture;
}

Shader ResourceManager::LoadShader(const GLchar* vertexShaderFile, const GLchar* fragmentShaderFile,
	const GLchar* geometryShaderFile, const std::string name) {
	const auto shader = LoadShaderFromFile(vertexShaderFile, fragmentShaderFile, geometryShaderFile);
	shaders[name] = shader;
	return shader;
}

Shader ResourceManager::GetShader(const std::string name) {
	return shaders[name];
}

Texture2D ResourceManager::LoadTexture2D(const GLchar* file, const GLboolean alpha, const std::string name) {
	const auto texture = LoadTextureFromFile(file, alpha);
	textures[name] = texture;
	return texture;
}

Texture2D ResourceManager::GetTexture2D(const std::string name) {
	return textures[name];
}
