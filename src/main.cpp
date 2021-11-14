//
// main.cpp
//
// Created by Wei Chen on 11/11/21
//

#include <iostream>
#include <glm/glm.hpp>

#include "EulerOp.hpp"
#include "Sweep.hpp"
#include "Draw.hpp"

int displayEulerOp = 1; // 1: display each Euler Operation, 0: otherwise

Solid * cube(){
    std::cout << "construct cube:" << std::endl;
    Solid *solid;
    Vertex *v[4];
    solid = EulerOp::mvfs(v[0], glm::vec3(0.0, 0.0, 0.0));
    Face *face = solid->Sfaces;
    Loop *loop = face->Floops;

    EulerOp::mev(v[0], v[1], glm::vec3(1.0, 0.0, 0.0), loop);
    EulerOp::mev(v[1], v[2], glm::vec3(1.0, 0.0, 1.0), loop);
    EulerOp::mev(v[2], v[3], glm::vec3(0.0, 0.0, 1.0), loop);
    EulerOp::mef(v[3], v[0], loop);

    solid = Sweep::sweep(face, glm::vec3(0.0, 1.0, 0.0), 1.0);
    
    return solid;
}


void debug(Solid *solid){
    std::cout << "Number of faces: " << solid->faceNum << std::endl;
    std::cout << "Number of edges: " << solid->edgeNum << std::endl;
    std::cout << "--------------------" << std::endl;
    int faceID = 0;
    for(Face *faceI=solid->Sfaces; faceI!=nullptr; faceI=faceI->Fnext){
        std::cout << "Number of loops in Face#" << ++faceID << ": " 
            << faceI->LoopNum << std::endl;
    }
    std::cout << std::endl << std::endl;
    faceID = 0;
    std::cout << "Loop Information:" << std::endl;
    for(Face *faceI=solid->Sfaces; faceI!=nullptr; faceI=faceI->Fnext){
        std::cout << "Face#" << ++faceID << std::endl;
        int loopID = 0;
        for(Loop *loopI=faceI->Floops; loopI!=nullptr; loopI=loopI->Lnext){
            std::cout << "  Loop#" << ++loopID << ": ";
            loopI->debug();
        }
        std::cout << "-----------------" << std::endl;
    }
}

int main(int argc, char **argv){
    Solid *solid;
    solid = cube();
    debug(solid);

    Draw::init();
    Draw::draw(solid);
    Draw::end();

    return 0;
}