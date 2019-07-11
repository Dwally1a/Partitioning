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

void Node::AddObject(Tile* _tile)
{
	if (children.size() > 0)
	{
		for (auto child : children)
		{
			if (_tile->bounds.Intersects(child->boundingBox))
			{
				child->AddObject(_tile);
			}
		}
	}
	else
	{
		contents.push_back(_tile);

		if (boundingBox.Width() > minNodeWidth)
		{

			if (contents.size() > objectsPerNode)
			{
				//Bottom Left
				Node* childNode = new Node(boundingBox.boxMin, boundingBox.Centre(), this, depth + 1);
				children.push_back(childNode);

				//Bottom Right
				Node* childNode2 = new Node(Vector2f(boundingBox.Centre().X, boundingBox.boxMin.Y),
					Vector2f(boundingBox.boxMax.X, boundingBox.Centre().Y), this, depth + 1);
				children.push_back(childNode2);

				//Top Right
				Node* childNode3 = new Node(boundingBox.Centre(), boundingBox.boxMax, this, depth + 1);
				children.push_back(childNode3);

				//Top Left
				Node* childNode4 = new Node(Vector2f(boundingBox.boxMin.X, boundingBox.Centre().Y),
					Vector2f(boundingBox.Centre().X, boundingBox.boxMax.Y), this, depth + 1);
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

				//What do I need to do to clean up?
				contents.clear();
			}
		}
	}

}

std::vector<Tile*> Node::FindTiles(Vector2f target)
{
	if (children.size() != 0)
	{
		for (auto node : children)
		{
			if (node->boundingBox.Contains(target))
			{
				return node->FindTiles(target);
			}
		}

	}
	return contents;
}
