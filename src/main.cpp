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
    Face *topFace = solid->Sfaces;
    Loop *top = topFace->Floops;

    EulerOp::mev(v[0], v[1], glm::vec3(1.0, 0.0, 0.0), top);
    EulerOp::mev(v[1], v[2], glm::vec3(1.0, 0.0, 1.0), top);
    EulerOp::mev(v[2], v[3], glm::vec3(0.0, 0.0, 1.0), top);
    EulerOp::mef(v[3], v[0], top);

    solid = Sweep::sweep(topFace, glm::vec3(0.0, 1.0, 0.0), 1.0);
    
    return solid;
}

Solid * sixteen_hole(){
    std::cout << "construct sixteen_hole:" << std::endl;
    Solid *solid;
    Vertex *v0[4];
    solid = EulerOp::mvfs(v0[0], glm::vec3(0.0, 0.0, 0.0));
    Face *topFace = solid->Sfaces;
    Loop *top = topFace->Floops;

    EulerOp::mev(v0[0], v0[1], glm::vec3(2.0, 0.0, 0.0), top);
    EulerOp::mev(v0[1], v0[2], glm::vec3(2.0, 0.0, 2.0), top);
    EulerOp::mev(v0[2], v0[3], glm::vec3(0.0, 0.0, 2.0), top);
    Loop *bottom = EulerOp::mef(v0[3], v0[0], top);
    
    // 16 rings
    for(int i=0; i<4; ++i){
        for(int j=0; j<4; ++j){
            float xbase = 0.5 * i, zbase = 0.5 * j;
            Vertex *v1[4];
            HalfEdge *tempEdge = EulerOp::mev(v0[0], v1[0],
                glm::vec3(xbase+0.1, 0.0, zbase+0.1), top);
            
            EulerOp::mev(v1[0], v1[1], glm::vec3(xbase+0.1, 0.0, zbase+0.4), top);
            EulerOp::mev(v1[1], v1[2], glm::vec3(xbase+0.4, 0.0, zbase+0.4), top);
            EulerOp::mev(v1[2], v1[3], glm::vec3(xbase+0.4, 0.0, zbase+0.1), top);
            Loop *hole_bottom = EulerOp::mef(v1[3], v1[0], top);
            hole_bottom->inner = true;
            EulerOp::kfmrh(bottom, hole_bottom);

            Loop *hole_top = EulerOp::kemr(tempEdge->HEedge, top);
            hole_top->inner = true;
        }
    }

    solid = Sweep::sweep(topFace, glm::vec3(0.0, 1.0, 0.0), 0.5);
    return solid;
}

Solid * two_rods(){
    std::cout << "construct two_rods:" << std::endl;
    Solid *solid;

    // medium cube:
    Vertex *v[4];
    solid = EulerOp::mvfs(v[0], glm::vec3(0.0, 0.0, 0.0));
    Face *topFace = solid->Sfaces;
    Loop *top = topFace->Floops;

    EulerOp::mev(v[0], v[1], glm::vec3(1.0, 0.0, 0.0), top);
    EulerOp::mev(v[1], v[2], glm::vec3(1.0, 0.0, 1.0), top);
    EulerOp::mev(v[2], v[3], glm::vec3(0.0, 0.0, 1.0), top);
    Loop *bottom = EulerOp::mef(v[3], v[0], top);
    solid = Sweep::sweep(topFace, glm::vec3(0.0, 1.0, 0.0), 0.3);

    // find Vertex topV whose coordinate is (0.0, 0.3, 0.0)
    Vertex *topV;
    glm::vec3 tmp1(0.0, 0.0, 0.0);
    glm::vec3 tmp2(0.0, 0.3, 0.0);
    Edge *ptr = solid->Sedges;
    while(ptr != nullptr){
        HalfEdge *he1 = ptr->he1, *he2 = ptr->he2;
        glm::vec3 cor1 = he1->v->cor, cor2 = he2->v->cor;
        if(cor1==tmp1 && cor2==tmp2){
            topV = he2->v;
            break;
        }
        else if(cor1==tmp2 && cor2==tmp1){
            topV = he1->v;
            break;
        }
        ptr = ptr->Enext;
    }
    if(ptr == nullptr){
        std::cout << "error: can't find topV" << std::endl;
        exit(-1);
    }

    // top rod:
    Vertex *v1[4];
    HalfEdge *tempEdge1 = EulerOp::mev(topV, v1[0], glm::vec3(0.4, 0.3, 0.4), top);

    EulerOp::mev(v1[0], v1[1], glm::vec3(0.4, 0.3, 0.6), top);
    EulerOp::mev(v1[1], v1[2], glm::vec3(0.6, 0.3, 0.6), top);
    EulerOp::mev(v1[2], v1[3], glm::vec3(0.6, 0.3, 0.4), top);
    Loop *rod1Top = EulerOp::mef(v1[3], v1[0], top);
    Face *rod1TopFace = rod1Top->Lface;
    Loop *rod1Bottom = EulerOp::kemr(tempEdge1->HEedge, top);

    Sweep::sweep(rod1TopFace, glm::vec3(0.0, 1.0, 0.0), 1.0);

    // bottom rod:
    Vertex *v2[4];
    HalfEdge *tempEdge2 = EulerOp::mev(v[0], v2[0], glm::vec3(0.4, 0.0, 0.4), bottom);

    EulerOp::mev(v2[0], v2[1], glm::vec3(0.6, 0.0, 0.4), bottom);
    EulerOp::mev(v2[1], v2[2], glm::vec3(0.6, 0.0, 0.6), bottom);
    EulerOp::mev(v2[2], v2[3], glm::vec3(0.4, 0.0, 0.6), bottom);
    Loop *rod2Bottom = EulerOp::mef(v2[3], v2[0], bottom);
    Face *rod2BottomFace = rod2Bottom->Lface;
    Loop *rod2Top = EulerOp::kemr(tempEdge2->HEedge, bottom);

    Sweep::sweep(rod2BottomFace, glm::vec3(0.0, -1.0, 0.0), 1.0);
    
    return solid;
}

void debug(Solid *solid){
    Solid *ptr = solid;
    int solidID = 0;
    while(ptr != nullptr){
        std::cout << "********************" << std::endl;
        std::cout << "Solid#" << ++solidID << std::endl;

        std::cout << "Number of faces: " << ptr->faceNum << std::endl;
        std::cout << "Number of edges: " << ptr->edgeNum << std::endl;
        std::cout << "--------------------" << std::endl;
        int faceID = 0;
        for(Face *faceI=ptr->Sfaces; faceI!=nullptr; faceI=faceI->Fnext){
            std::cout << "Number of loops in Face#" << ++faceID << ": " 
                << faceI->LoopNum << std::endl;
        }
        std::cout << std::endl;
        faceID = 0;
        std::cout << "Loop Information:" << std::endl;
        for(Face *faceI=ptr->Sfaces; faceI!=nullptr; faceI=faceI->Fnext){
            std::cout << "Face#" << ++faceID << std::endl;
            int loopID = 0;
            for(Loop *loopI=faceI->Floops; loopI!=nullptr; loopI=loopI->Lnext){
                std::cout << "  Loop#" << ++loopID << ": ";
                loopI->debug();
            }
            std::cout << "-----------------" << std::endl;
        }

        std::cout << "*******************" << std::endl << std::endl;
        ptr = ptr->Snext;
    }
}

int main(int argc, char **argv){
    int opt = 2;
    if(argc > 1){
        opt = (int)(argv[1][0] - '0');
    }
    Solid *solid;

    switch (opt){
    case 1:
        solid = cube();
        break;

    case 2:
        solid = sixteen_hole();
        break;

    case 3:
        solid = two_rods();
        break;
    
    default:
        std::cout << "Please input right choice:" << std::endl;
        std::cout << "  1: cube" << std::endl;
        std::cout << "  2: sixteen_hole" << std::endl;
        std::cout << "  3: two_rods" << std::endl;
        exit(-1);
    }

    // debug(solid);

    // shading
    Draw::init();
    Draw::draw(solid);
    Draw::end();

    return 0;
}