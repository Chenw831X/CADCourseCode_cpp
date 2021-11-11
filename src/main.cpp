//
// main.cpp
//
// Created by Wei Chen on 11/11/21
//

#include <iostream>
#include <glm/glm.hpp>

#include "EulerOp.hpp"

void cube(){
    Solid *solid;
    Vertex *v[4];
    solid = EulerOp::mvfs(v[0], glm::vec3(0.0, 0.0, 0.0));
    Face *face = solid->Sfaces;
    Loop *loop = face->Floops;

    EulerOp::mev(v[0], v[1], glm::vec3(1.0, 0.0, 0.0), loop);
    EulerOp::mev(v[1], v[2], glm::vec3(1.0, 0.0, 1.0), loop);
    EulerOp::mev(v[2], v[3], glm::vec3(0.0, 0.0, 1.0), loop);
    EulerOp::mef(v[3], v[0], loop);

    solid = EulerOp::sweep(face, glm::vec3(0.0, 1.0, 0.0), 1.0);
}

int main(int argc, char **argv){
    cube();

    return 0;
}