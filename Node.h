#pragma once
#include <vector>
#include "Tile.h"


class Node
{
public:
	std::vector<Node*> children;
	Node* parent;
	std::vector<Tile*> contents;
	int depth;
	AABBf boundingBox;

	Node();
	Node(Vector2f, Vector2f, Node*, int);
	~Node();

	void AddObject(Tile*);
	std::vector<Tile*> FindTiles(Vector2f);

protected:
	int objectsPerNode = 5;


	
};

