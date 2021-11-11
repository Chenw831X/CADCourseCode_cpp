
//
// EulerOp.cpp
//
// Created by Wei Chen on 11/11/21
//

#include "EulerOp.hpp"

Solid * EulerOp::mvfs(Vertex *v, const glm::vec3 &P){
    v = new Vertex();
    v->cor = P;

    Solid *solid = new Solid();
    Face *face = new Face();
    Loop *loop = new Loop();
    face->add_Loop(loop);
    solid->add_Face(face);

    return solid;
}

HalfEdge * EulerOp::mev(Vertex *v1, Vertex *v2, const glm::vec3 &P, Loop *loop){
    assert(v1 != nullptr);
    assert(loop != nullptr);

    v2 = new Vertex();
    v2->cor = P;

    Edge *edge = new Edge();
    HalfEdge *he1 = new HalfEdge();
    HalfEdge *he2 = new HalfEdge();
    he1->v = v1;
    he2->v = v2;
    
    Solid *solid = loop->Lface->Fsolid;
    solid->add_Edge(edge);
    edge->connect(he1, he2);

    loop->add_HE(he1, he2);

    return he1;
}

Loop * EulerOp::mef(Vertex *v1, Vertex *v2, Loop *loop){
    assert(v1 != nullptr);
    assert(v2 != nullptr);
    assert(loop != nullptr);

    Edge *edge = new Edge();
    HalfEdge *he1 = new HalfEdge();
    HalfEdge *he2 = new HalfEdge();
    he1->v = v1;
    he2->v = v2;

    Solid *solid = loop->Lface->Fsolid;
    solid->add_Edge(edge);
    edge->connect(he1, he2);

    HalfEdge *phe1 = loop->findHE(v1);
    HalfEdge *phe2 = loop->findHE(v2);
    assert(phe1 != nullptr);
    assert(phe2 != nullptr);

    he1->HEprev = phe1->HEprev;
    he1->HEnext = phe2;
    he2->HEprev = phe2->HEprev;
    he2->HEnext = phe1;
    phe1->HEprev->HEnext = he1;
    phe1->HEprev = he2;
    phe2->HEprev->HEnext = he2;
    phe2->HEprev = he1;

    Face * newFace = new Face();
    Loop * newLoop = new Loop();
    loop->Lhe = he2;
    newLoop->Lhe = he1;

    newFace->add_Loop(newLoop);
    solid->add_Face(newFace);

    return newLoop;
}

Solid * EulerOp::sweep(Face *face, const glm::vec3 &dir, float dist){
    Solid *solid = face->Fsolid;

    for(Loop *loop=face->Floops; loop!=nullptr; loop=loop->Lnext){
        HalfEdge *he = loop->Lhe;
        Vertex *firstV = he->v, *firstV_up;
        glm::vec3 firstV_up_cor = firstV->cor + dir * dist;
        mev(firstV, firstV_up, firstV_up_cor, loop);
        Vertex *last_up = firstV_up;

        he = he->HEnext;
        Vertex *now = he->v, *now_up;
        while(now != firstV){
            glm::vec3 now_up_cor = now->cor + dir * dist;
            mev(now, now_up, now_up_cor, loop);
            mef(now_up, last_up, loop);
            last_up = now_up;
            he = he->HEnext;
            now = he->v;
        }
        mef(firstV_up, last_up, loop);
    }

    return solid;
}
