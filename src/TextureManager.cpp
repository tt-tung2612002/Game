#include "TextureManager.hpp"

SDL_Texture *TextureManager::loadTexture(const char *texture)
{
    SDL_Surface *tempSurface = IMG_Load(texture);
    SDL_Texture *tex = SDL_CreateTextureFromSurface(Application::renderer, tempSurface);
    SDL_FreeSurface(tempSurface);
    return tex;
}
void TextureManager:: Draw(SDL_Texture* tex, SDL_Rect src, SDL_Rect dest){
    SDL_RenderCopy(Application::renderer,tex,&src,&dest);
}