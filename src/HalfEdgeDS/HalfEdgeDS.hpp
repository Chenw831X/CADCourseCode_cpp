//
// HalfEdgeDS.hpp
//
// Created by Wei Chen on 11/11/21
//

#ifndef HALFEDGEDS_HPP
#define HALFEDGEDS_HPP

#include <glm/glm.hpp>

class Solid;
class Face;
class Loop;
class Edge;
class HalfEdge;
class Vertex;

class Solid{
public:
    Solid *Sprev, *Snext;
    Face *Sfaces;
    Edge *Sedges;

public:
    Solid();
    void add_Face(Face *newFace);
    void add_Edge(Edge *newEdge);
};

class Face{
public:
    Face *Fprev, *Fnext;
    Solid *Fsolid;
    Loop *Floops;

public:
    Face();
    void add_Loop(Loop *newLoop);
};

class Loop{
public:
    Loop *Lprev, *Lnext;
    Face *Lface;
    HalfEdge *Lhe;

public:
    Loop();
    void add_HE(HalfEdge *he1, HalfEdge *he2);
    HalfEdge * findHE(Vertex *v);
    void debug();
};

class Edge{
public:
    Edge *Eprev, *Enext;
    HalfEdge *he1, *he2;

public:
    Edge();
    void connect(HalfEdge *he1, HalfEdge *he2);
};

class HalfEdge{
public:
    HalfEdge *HEprev, *HEnext;
    Loop *HEloop;
    HalfEdge *couple;
    Edge *HEedge;
    Vertex* v;

public:
    HalfEdge();
};

class Vertex{
public:
    glm::vec3 cor;

public:
    Vertex();
};

#endif