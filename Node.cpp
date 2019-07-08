#include "Node.h"



Node::Node()
{
	
}

Node::Node(Vector2f _min, Vector2f _max, Node* _parent, int _depth)
{
	boundingBox = AABBf(_min, _max);
	parent = _parent;
	depth = _depth;
}


Node::~Node()
{
}

void Node::AddObject(Tile* tile)
{
	if (children.size > 0)
	{
		for (auto child : children)
		{
			if (tile->bounds.Intersects(child->boundingBox))
			{
				child->AddObject(tile);
			}
		}
	}
	else
	{
		contents.push_back(tile);

		if (contents.size > objectsPerNode)
		{
			//Bottom Left
			Node* childNode = new Node(boundingBox.boxMin, boundingBox.boxMax/2, this, depth + 1);
			children.push_back(childNode);

			//Bottom Right
			Node* childNode2 = new Node(Vector2f(boundingBox.boxMax.X / 2, boundingBox.boxMin.Y),
				Vector2f(boundingBox.boxMax.X, boundingBox.boxMax.Y / 2), this, depth + 1);
			children.push_back(childNode2);

			//Top Right
			Node* childNode3 = new Node(boundingBox.boxMax / 2, boundingBox.boxMax, this, depth + 1);
			children.push_back(childNode3);

			//Top Left
			Node* childNode4 = new Node(Vector2f(boundingBox.boxMin.X, boundingBox.boxMax.Y / 2),
				Vector2f(boundingBox.boxMax.X / 2, boundingBox.boxMax.Y), this, depth + 1);
			children.push_back(childNode4);

			for (auto tile : contents)
			{
				for (auto child : children)
				{
					if (child->boundingBox.Intersects(tile->bounds))
					{
						child->AddObject(tile);
					}
				}
			}

			//DO I REMOVE THE OBJECTS FROM HERE???
		}
	}

}

std::vector<Tile*> Node::FindTiles(Vector2f target)
{
	if (children.size == 0)
	{
		return contents;
	}
	else
	{
		for (auto node : children)
		{
			if (node->boundingBox.Intersects(target))
			{
				return node->FindTiles(target);
			}
		}
	}
}
