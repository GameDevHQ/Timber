#include "stdafx.h"
#include "Object.h"


Object::Object():
pathToTexture("")
{
}


Object::Object(std::string pathToTexture):
pathToTexture(std::move(pathToTexture))
{}
