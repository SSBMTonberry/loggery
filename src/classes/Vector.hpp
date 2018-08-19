//
// Created by robin on 19.08.18.
//

#ifndef LOGGERY_VECTOR_HPP
#define LOGGERY_VECTOR_HPP

namespace ly
{
    template <typename T>
    struct Vector2
    {
        T x;
        T y;
    };

    template <typename T>
    struct Vector3
    {
        T x;
        T y;
        T z;
    };

    template <typename T>
    struct Vector4
    {
        T x;
        T y;
        T z;
        T w;
    };

    typedef Vector2<int>          Vector2i;
    typedef Vector2<unsigned int> Vector2u;
    typedef Vector2<float>        Vector2f;

    typedef Vector3<int>          Vector3i;
    typedef Vector3<unsigned int> Vector3u;
    typedef Vector3<float>        Vector3f;

    typedef Vector4<int>          Vector4i;
    typedef Vector4<unsigned int> Vector4u;
    typedef Vector4<float>        Vector4f;
}

#endif //LOGGERY_VECTOR_HPP
