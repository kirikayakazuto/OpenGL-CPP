//
// Created by Bytedance on 2024/1/15.
//

#ifndef LEARN_OPENGL_COMPONENT_H
#define LEARN_OPENGL_COMPONENT_H

class Component {
private:
    bool inited = false;
public:
    virtual void OnInit() {
        if(this->inited) return;
        this->inited = true;
    }
    virtual void OnDestroy() {}
    virtual void OnUpdate(double dt) {}
};


#endif //LEARN_OPENGL_COMPONENT_H
