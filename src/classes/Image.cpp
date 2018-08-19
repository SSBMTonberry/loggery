//
// Created by robin on 19.08.18.
//

#include "Image.h"

ly::Image::Image(void *data, int size, const ly::Image::ScaleSetting &scaleSetting)
{
    create(data, size, scaleSetting);
}

void ly::Image::initialize()
{

}

bool ly::Image::create(const std::string &path, const ScaleSetting &scaleSetting)
{
    m_image = cp_load_png(path.c_str());
    m_scaleSetting = scaleSetting;
    bool success = m_image.pix != nullptr;
    if(success)
        bindToOpenGL();

    return success;
}

bool ly::Image::create(void *data, int size, const ScaleSetting &scaleSetting)
{
    m_image = cp_load_png_mem(data, size);
    m_scaleSetting = scaleSetting;
    bool success = m_image.pix != nullptr;
    if(success)
        bindToOpenGL();

    return success;
}

void ly::Image::bindToOpenGL()
{
    glGenTextures(1, &m_textureID);
    glBindTexture(GL_TEXTURE_2D, m_textureID);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, static_cast<GLint>(m_scaleSetting)); //When scaling down to less than 100% size
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, static_cast<GLint>(m_scaleSetting)); //When scaling up
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1); //Not sure if necessary
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, m_image.w, m_image.h, 0, GL_RGBA, GL_UNSIGNED_BYTE, m_image.pix);
}

GLuint ly::Image::getTextureID() const
{
    return m_textureID;
}

ly::Vector2i ly::Image::getSize()
{
    return {m_image.w, m_image.h};
}