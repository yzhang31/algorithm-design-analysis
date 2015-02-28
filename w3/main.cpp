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
#include <iterator>
#include <random>
#include <iterator>
#include <map>

using namespace std;

class Edge;

class Vertex
{
public:
	Vertex(int label) :label(label)
	{}

	int label;
	list<Edge*> edges;
};

class Edge
{
public:
	Edge(Vertex* firstVertex, Vertex* secondVertex)
	{
		vertexes.first = firstVertex;
		vertexes.second = secondVertex;
	}
	pair<Vertex*, Vertex*> vertexes;
};


class Graph
{
private:
	map<int, Vertex*> cache_vertices;
	map<pair<int, int>, Edge*> cache_edges;
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
			edge = new Edge(f, s);
			cache_edges[std::make_pair(first, second)] = edge;
			f->edges.push_back(edge);
			edges.push_back(edge);
		}
		else
		{
			f->edges.push_back(edge);
		}
	}

	void Mergedge()
	{
		int randomPos = GetRandomInRange(0, edges.size() - 1);
		list<Edge*>::iterator delEdge = edges.begin();
		std::advance(delEdge, randomPos);

		Vertex* deleteNode = (*delEdge)->vertexes.first;
		Vertex* keptNode = (*delEdge)->vertexes.second;
		vertices.remove(deleteNode);

		// All the edges which point to deleted vertex should point to the kept vertex.
		// And add into keptNode.
		for (auto e : deleteNode->edges)
		{
			if (e->vertexes.first->label == deleteNode->label)
			{
				e->vertexes.first = keptNode;
			}
			else
			{
				e->vertexes.second = keptNode;
			}
			if (e->vertexes.first != e->vertexes.second)
				keptNode->edges.push_back(e);
		}

		delete deleteNode;

		// Remove second vertex self loop edge
		auto itorEdge = keptNode->edges.begin();
		while (itorEdge != keptNode->edges.end())
		{
			if ((*itorEdge)->vertexes.first->label == (*itorEdge)->vertexes.second->label)
				itorEdge = keptNode->edges.erase(itorEdge);
			else
				++itorEdge;
		}

		// Remove self loop edge from all edges.
		itorEdge = edges.begin();
		while (itorEdge != edges.end())
		{
			if ((*itorEdge)->vertexes.first->label == (*itorEdge)->vertexes.second->label)
			{
				delete *itorEdge;
				itorEdge = edges.erase(itorEdge);
				
			}
			else
				++itorEdge;
		}

	}


	~Graph()
	{
		for (auto e : edges)
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
		cache_vertices[label] = v;

		if (vertices.size() == 0)
		{
			vertices.push_back(v);
			return v;
		}

		list<Vertex*>::iterator insertPos = vertices.begin();
		for (auto itor = vertices.begin(); itor != vertices.end(); itor++) {
			if (v->label > (*itor)->label) {
				insertPos = itor;
			}
		}
		vertices.insert(++insertPos, v);
		return v;
	}

	Vertex* FindVetex(int label)
	{
		auto result = cache_vertices.find(label);
		if (result != cache_vertices.end())
		{
			return (*result).second;
		}
		return nullptr;
	}

	Edge* FindEdge(int first, int second)
	{
		auto result = cache_edges.find(std::make_pair(first, second));
		if (result != cache_edges.end())
		{
			return (*result).second;
		}
		result = cache_edges.find(std::make_pair(second, first));
		if (result != cache_edges.end())
		{
			return (*result).second;
		}
		return nullptr;

	}

	int GetRandomInRange(int range_from, int range_to)
	{
		std::random_device                  rand_dev;
		std::mt19937                        generator(rand_dev());
		std::uniform_int_distribution<int>  distr(range_from, range_to);
		return distr(generator);
	}
};

Graph* load_graph_from_file(const string& file_name)
{
	Graph *g = new Graph();

	ifstream ifs(file_name, ios::in);

	for (string line; std::getline(ifs, line);)
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
	for (auto v : g.vertices)
	{
		output << v->label << "\t";

		for (auto edge : v->edges)
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

int CalculateMincut()
{
	Graph *g = load_graph_from_file("kargerMinCut.txt");

	while (g->vertices.size() > 2)
	{
		g->Mergedge();
	}
	int mincut = g->edges.size();
	//write_graph_to_file(*g);
	delete g;
	return mincut;
}

int main(int argc, const char * argv[])
{
	int minCut = 10000000;

	for (size_t i = 0; i < 400; i++)
	{
		int result = CalculateMincut();
		if (result < minCut)
		{
			minCut = result;
		}
		cout << "Iteration: " << i << " Result: " << result << " Mincut: " << minCut << endl;
	}
	cout << "Min cut :" << minCut << endl;
	return 0;
}
