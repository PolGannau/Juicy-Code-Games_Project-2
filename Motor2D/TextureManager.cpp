#include "TextureManager.h"

#include "Application.h"
#include "Render.h"
#include "Defs.h"
#include "Log.h"

#include "SDL_image/include/SDL_image.h"

void TextureManager::CleanUp()
{
	LOG("Freeing textures");

	texture_data.clear();

	for (std::vector<SDL_Texture*>::iterator it = textures.begin(); it != textures.end(); ++it)
		SDL_DestroyTexture(*it);

	textures.clear();
}

// Load texture from file path
int TextureManager::Load(const char* path)
{
	int ret = -1;

	for (std::vector<TextureData>::iterator it = texture_data.begin(); it != texture_data.end(); ++it)
	{
		if (it->source == path)
		{
			ret = it->id;
			LOG("Texture already loaded: %s", it->source);
		}
	}

	if (ret < 0)
	{
		SDL_Surface* surface = IMG_Load(path);

		if (surface)
		{
			SDL_Texture* texture = SDL_CreateTextureFromSurface(App->render->renderer, surface);

			if (texture)
			{
				TextureData data;
				SDL_QueryTexture(texture, 0, 0, &data.width, &data.height);
				data.source = path;
				data.id = textures.size();

				ret = data.id;
				texture_data.push_back(data);
				textures.push_back(texture);

				SDL_FreeSurface(surface);

				LOG("     Loaded surface with path: %s", path);
			}
			else
				LOG("Unable to create texture from surface! SDL Error: %s\n", SDL_GetError());
		}
		else
			LOG("Could not load surface with path: %s. IMG_Load: %s", path, IMG_GetError());
	}

	return ret;
}

bool TextureManager::GetTextureData(int id, TextureData& data) const
{
	bool ret;

	if (ret = (id >= 0 && id < textures.size()))
		data = texture_data[id];

	return ret;
}

SDL_Texture * TextureManager::GetTexture(int id) const
{
	SDL_Texture* ret = nullptr;

	if (id >= 0 && id < textures.size())
		ret = textures[id];

	return ret;
}

TextureData::TextureData() :
	id(0),
	width(0),
	height(0),
	source("none")
{}

TextureData::TextureData(const TextureData& copy) :
	id(copy.id),
	width(copy.width),
	height(copy.height),
	source(copy.source)
{}