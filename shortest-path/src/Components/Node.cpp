#include "Node.hpp"

int Node::getID() const {
    return this->id;
}

int Node::getDistance() const {
    return this->distance;
}

void Node::setDistance(int distance) {
    this->distance = distance;
}

Node* Node::getParent() const {
    return this->parent;
}

void Node::setParent(Node* parent) {
    this->parent = parent;
}

void Node::draw(sf::RenderWindow *window) {
    return;
}

void Node::reset() {
    return;
}

Node::~Node() {
    return;
}