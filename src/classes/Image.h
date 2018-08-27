//
// Created by robin on 19.08.18.
//

#ifndef LOGGERY_IMAGE_H
#define LOGGERY_IMAGE_H

#include "glad/glad.h"
#include "cute_png.h"
#include "imgui/imgui.h"
#include <string>
#include "Vector.hpp"

namespace ly
{
    class Image
    {

        public:
            enum class ScaleSetting : GLint
            {
                NearestNeighbor = GL_NEAREST, //Pixelated scaling
                Linear = GL_LINEAR //Stretching
            };
            Image() = default;
            Image(void * data, int size, const ScaleSetting &scaleSetting = ScaleSetting::NearestNeighbor);
            bool create(const std::string &path, const ScaleSetting &scaleSetting = ScaleSetting::NearestNeighbor);
            bool create(void * data, int size, const ScaleSetting &scaleSetting = ScaleSetting::NearestNeighbor);

            GLuint getTextureID() const;
            Vector2i getSize();

        private:
            void initialize();
            void bindToOpenGL();

            cp_image_t m_image;
            ScaleSetting m_scaleSetting = ScaleSetting::NearestNeighbor;
            GLuint m_textureID = 0;

    };
}

#endif //LOGGERY_IMAGE_H
