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
        
        if (FindEdge(first, second) != nullptr)
            return;
        

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
        
        Edge * edge = new Edge(f,s);
        f->edges.push_back(edge);
        s->edges.push_back(edge);
        edges.push_back(edge);

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
            numbers.push_back(std::atoi(item.c_str()));
        }
        
        g->AddVertex(numbers[0]);
        
        for (int i = 1; i < numbers.size(); i++)
        {
            g->AddVertex(numbers[i]);
            g->AddEdge(numbers[0], numbers[i]);
        }
    }
    
    return g;
}

void write_graph_to_file(Graph& g)
{
    
}

int main(int argc, const char * argv[])
{
    Graph *g = load_graph_from_file("kargerMinCut.txt");
    // insert code here...
    std::cout << "Hello, World!\n";
    delete g;
    return 0;
}
