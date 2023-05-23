#pragma once
#include <iostream>
#include <vector>
#include <math.h>

using namespace std;

class Node
{

public:
    int row;
    int col;
    Node* parent;
    bool visited = false;

    vector<Node*> neighbors;
    float g, h;

    Node(int row, int col, Node* parent = nullptr)
    {
        this->row = row;
        this->col = col;
        this->parent = parent;
        this->visited = false;

        g = 0;
        h = 0;
    }

    bool isEqual(Node* other)
    {
        return row == other->row && col == other->col;
    }
    float f()
    {
        return g + h;
    }

    float euclidean_distance(Node* node1, Node* node2)
    {
        return (float)sqrt((node2->row - node1->row) * (node2->row - node1->row) + (node2->col - node2->col) * (node2->col - node2->col));
    }

};