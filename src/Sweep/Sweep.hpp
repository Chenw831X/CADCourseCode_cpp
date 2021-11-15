//
// Sweep.hpp
//
// Created by Wei Chen on 11/13/21
//

// implement sweep operation based on Euler Operation

#ifndef SWEEP_HPP
#define SWEEP_HPP

#include "EulerOp.hpp"

class Sweep{
public:
    static Solid * sweep(Face *face, const glm::vec3 &dir, float dist);
};

#endif