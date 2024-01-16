//
// Created by Bytedance on 2024/1/15.
//

#ifndef LEARN_OPENGL_COMPONENT_H
#define LEARN_OPENGL_COMPONENT_H

class Component {
public:
    bool enable{};
    virtual void OnEnable() {}
    virtual void OnStart() {}
    virtual void OnDestroy() {}
};


#endif //LEARN_OPENGL_COMPONENT_H
