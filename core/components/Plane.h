//
// Created by Bytedance on 2024/1/15.
//

#ifndef LEARN_OPENGL_PLANE_H
#define LEARN_OPENGL_PLANE_H

#include "MeshRenderer.h"

class Plane: public MeshRenderer{
public:
    Plane();

    void SetMaterial(Material* m);
};


#endif //LEARN_OPENGL_PLANE_H
