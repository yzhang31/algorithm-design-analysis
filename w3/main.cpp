//
//  main.cpp
//  w3
//
//  Created by ZhangYanhua on 1/13/15.
//  Copyright (c) 2015 ZhangYanhua. All rights reserved.
//

#include <iostream>
#include <list>
#include <fstream>
#include <sstream>
#include <vector>
#include <stdexcept>
#include <stdlib.h>

using namespace std;

struct Edge;

struct Vertex
{
    Vertex(int label):label(label)
    {}

    int label;
    list<Edge*> edges;
};

struct Edge
{
    Edge(Vertex* firstVertex, Vertex* secondVertex)
    {
        vertexes.first = firstVertex;
        vertexes.second = secondVertex;
    }
    pair<Vertex*, Vertex*> vertexes;
};


class Graph
{
public:
    list<Edge*> edges;
    list<Vertex*> vertices;

    void AddVertex(int label)
    {
        if (FindVetex(label) == nullptr)
        {
            CreateVetex(label);
        }
    }

    void AddEdge(int first, int second)
    {

        Vertex *f = FindVetex(first);
        if (f == nullptr) {
            stringstream ss;
            ss << "first:" << first << " vetex is not created.";
            throw std::invalid_argument(ss.str());
        }

        Vertex *s = FindVetex(second);
        if (f == nullptr) {
            stringstream ss;
            ss << "second:" << second << " vetex is not created.";
            throw std::invalid_argument(ss.str());
        }

        Edge * edge = FindEdge(first, second);

        if (edge == nullptr)
        {
            edge = new Edge(f,s);
            f->edges.push_back(edge);
            edges.push_back(edge);
        }
        else
        {
            f->edges.push_back(edge);
        }
    }

    ~Graph()
    {
        for (auto e: edges)
        {
            delete e;
        }

        for (auto v : vertices) {
            delete  v;
        }
    }
private:
    Vertex* CreateVetex(int label)
    {
        Vertex *v = new Vertex(label);
        list<Vertex*>::iterator insertPos = vertices.begin();

        for (auto itor = vertices.begin(); itor != vertices.end(); itor++) {
            if (v->label > (*itor)->label ) {
                insertPos = itor;
            }
        }
        vertices.insert(++insertPos, v);
        return v;
    }

    Vertex* FindVetex(int label)
    {
        for(auto aVetex: vertices)
        {
            if (aVetex->label == label)
                return  aVetex;
        }
        return nullptr;
    }

    Edge* FindEdge(int first, int second)
    {
        Vertex *f = FindVetex(first);

        if (f != nullptr)
        {
            for (auto aEdge: f->edges)
            {
                if (aEdge->vertexes.first->label == second
                    || aEdge->vertexes.second->label == second )
                {
                    return aEdge;
                }
            }
        }

        return nullptr;
    }
};

Graph* load_graph_from_file(const string& file_name)
{
    Graph *g = new Graph();

    ifstream ifs(file_name, ios::in);

    for (string line; std::getline(ifs,line);)
    {
        std::stringstream ss(line);
        std::string item;
        vector<int> numbers;
        while (std::getline(ss, item, '\t') && item != "\r")
        {
            numbers.push_back(atoi(item.c_str()));
        }

        g->AddVertex(numbers[0]);

        for (size_t i = 1; i < numbers.size(); i++)
        {
            g->AddVertex(numbers[i]);
            g->AddEdge(numbers[0], numbers[i]);
        }
    }

    return g;
}

void write_graph_to_file(Graph& g)
{
    ofstream output("verify_graph.txt");
    for(auto v : g.vertices)
    {
        output << v->label << "\t";

        for(auto edge : v->edges)
        {

            if (edge->vertexes.first->label != v->label)
            {
                output << edge->vertexes.first->label << "\t";
            }
            else
            {
                output << edge->vertexes.second->label << "\t";
            }

        }
        output << "\n";
    }
    output.close();
}

int main(int argc, const char * argv[])
{
    Graph *g = load_graph_from_file("kargerMinCut.txt");



    write_graph_to_file(*g);
    delete g;
    return 0;
}
