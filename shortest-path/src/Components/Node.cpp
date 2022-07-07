#include "Node.hpp"

int Node::getID() const {
    return this->id;
}

Node::Type Node::getType() const {
    return this->type;
}

void Node::setType(Node::Type type) {
    this->type = type;
}

double Node::getDistance() const {
    return this->distance;
}

void Node::setDistance(double distance) {
    this->distance = distance;
}

Node* Node::getParent() const {
    return this->parent;
}

void Node::setParent(Node* parent) {
    this->parent = parent;
}

Node::~Node() {
    return;
}