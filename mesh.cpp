#include "mesh.h"
#include <GL/glut.h>
#include <iostream>
#include <vector>
// #include "../armadillo/include/armadillo"


//using namespace arma;
using namespace std;

	
//=========================================	
Mesh::Mesh()	
{
    vector<HalfEdge> he(24, HalfEdge());
    this->hedges = he;

    vector<Vertex> ve(7, Vertex());
    this->vertices = ve;

    vector<Face> fe(6, Face());
    this->faces = fe;
}

Mesh::~Mesh()
{
}

void Mesh::constMesh(int tabHe[][5], int tabFace[], int tabVertex[][4])
{
    // cosntruct vertices
    for(int i=0; i<7; i++){
        string name = "v" + std::to_string(i);
        this->vertices[i] = Vertex(tabVertex[i][0], tabVertex[i][1], tabVertex[i][2], name);
    }

    // construct halfEdjed
    for (int i=0; i<24; i++){
        int heInitVertex = tabHe[i][0]-1;
        string name = "e" + std::to_string(i);
        this->hedges[i] = HalfEdge(&this->vertices[heInitVertex], name);
    }

    // construct faces
    for(int i=0; i<6; i++){
        int fhe = tabFace[i];
        string name = "f" + std::to_string(i);
        this->faces[i] = Face(&this->hedges[fhe], name);
    }

    // complete remaining data for halfedge
    for (int i=0; i<24; i++){
        this->hedges[i].face = &this->faces[ tabHe[i][2] ];
        this->hedges[i].heNext = &this->hedges[ tabHe[i][3] ];
        this->hedges[i].hePrev = &this->hedges[ tabHe[i][4] ];
    }
}
