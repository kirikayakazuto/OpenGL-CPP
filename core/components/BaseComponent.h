//
// Created by Bytedance on 2024/1/15.
//

#ifndef LEARN_OPENGL_BASECOMPONENT_H
#define LEARN_OPENGL_BASECOMPONENT_H


class BaseComponent {
public:
    bool enable;
    void OnEnable();
    void OnStart();
    void OnDestroy();
};


#endif //LEARN_OPENGL_BASECOMPONENT_H
