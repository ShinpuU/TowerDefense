#pragma once
#include "Utils.h"
#include "Node.h"
#include <algorithm>


class PathGenerator
{
    int** grid;
    Node* start = nullptr;
    Node* end = nullptr;

    vector<Node*> openList;
    vector<Node*> closeList;
    int rows = 45;
    int cols = 80;

public:

    PathGenerator(int** grid)
    {
        this->grid = grid;
    }

    bool isInCloseList(Node* node)
    {
        for(Node* n : closeList) {
            if (node->isEqual(n))
            {
                return true;
            }
        }
        return false;
    }

    bool isInOpenList(Node* node)
    {
        for(Node* n : openList)
        {
            if (node->isEqual(n))
            {
                return true;
            }
        }
        return false;
    }

    int getFNode()
    {
        return rand() % openList.size();

        //float min = 999999999;
        //// Node* minF_node = nullptr;
        //int index = 0;
        //int i = 0;
        //foreach (Node n in openList)
        //{
        //    if (n.f() < min)
        //    {
        //        min = n.f();
        //        index = i;
        //    }
        //    i++;
        //}
        //return index;
    }

    void exploreNeightbour(Node* node)
    {
        int dirRow4[4] = {1, -1, 0, 0};
        int dirCol4[4] = {0, 0, 1, -1};
        int border = 0;

        for (int i = 0; i < 4; i++)
        {

            int nextRow = node->row + dirRow4[i];
            int nextCol = node->col + dirCol4[i];

            if (nextRow < border || nextRow > rows - border - 1)
            {
                //Debug.WriteLine("cc");
                continue;
            }
            if (nextCol < border || nextCol > cols - border - 1)
            {
                // Debug.WriteLine("cc");
                continue;
            }

            Node* newNode = new Node(nextRow, nextCol, node);

            if (newNode->isEqual(end))
            {
                openList.push_back(newNode);
            }

            //if (isInOpenList(new Node(nextRow, nextCol))) continue;
            if (isInCloseList(newNode)) continue;
            if (grid[nextRow][nextCol] == 3) continue; // skip plant


            if (grid[nextRow][nextCol] == 1) continue; // skip 


            float path_to_this_neightbour = node->g + 1;

            if (path_to_this_neightbour < newNode->g || !isInOpenList(newNode))
            {
                newNode->g = path_to_this_neightbour;
                newNode->h = node->euclidean_distance(newNode,end);
                if (!isInOpenList(newNode))
                {
                    openList.push_back(newNode);
                }
            }

        }

    }

    vector<Node*> tracePath(Node* node)
    {
        vector<Node*> path;
        path.push_back(node);
        Node* n = node;
        while (n->parent != nullptr)
        {
            path.push_back(n->parent);
            n = n->parent;
        }
        std::reverse(path.begin(), path.end());
        return path;
    }


    vector<Node*> getPath(Node* start,Node* end)
    {
        openList.clear();
        closeList.clear();
        this->start = start;
        this->end = end;
        openList.push_back(start);


        while (openList.size() != 0)
        {

            int fNodeIndex = getFNode();
            Node* currentNode = openList[fNodeIndex];
            closeList.push_back(currentNode);
            if (currentNode->isEqual(end))
            {
                return tracePath(currentNode);
            }

            openList.erase(openList.begin() + fNodeIndex);
            exploreNeightbour(currentNode);
        }

        return vector<Node*>();

    }

    vector<Node*> getRandomPath()
    {
        Node* path1Dest = new Node(Utils::randomInt(3,41), Utils::randomInt(3,20));
        vector<Node*> path1 =  PathGenerator(grid).getPath(new Node(0, 0), path1Dest);

        for(Node* node : path1)
        {
            grid[node->row] [node->col] = 1;
        }

        Node* path2Dest = new Node(Utils::randomInt(3, 41), Utils::randomInt(20, 50));
        vector<Node*> path2 = PathGenerator(grid).getPath(new Node(path1Dest->row, path1Dest->col), path2Dest);

        for(Node* node : path2)
        {
            grid[node->row][node->col] = 1;
        }

        vector<Node*> path3 = PathGenerator(grid).getPath(new Node(path2Dest->row,path2Dest->col), new Node(44,79));

        for(Node* node : path3)
        {
            grid[node->row][node->col] = 1;
        }

        for (Node* n : path2) {
            path1.push_back(n);
        }
        for (Node* n : path3) {
            path1.push_back(n);
        }

        return path1;
    }

};
