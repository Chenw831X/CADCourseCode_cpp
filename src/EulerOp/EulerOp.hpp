//
// EulerOp.hpp
//
// Created by Wei Chen on 11/11/21
//

#ifndef EULEROP_HPP
#define EULEROP_HPP

#include "HalfEdgeDS.hpp"

class EulerOp{
public:
    static Solid * mvfs(Vertex *v, const glm::vec3 &P);
    static HalfEdge * mev(Vertex *v1, Vertex *v2, const glm::vec3 &P, Loop *loop);
    static Loop * mef(Vertex *v1, Vertex *v2, Loop *loop);

    static Solid * sweep(Face *face, const glm::vec3 &dir, float dist);
};

#endif