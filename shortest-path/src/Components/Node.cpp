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

void Node::update(Node::Type type) {
    return;
}

void Node::mouseUpdate(sf::Vector2i &pos, MouseState state) {
    return;
}

Node::~Node() {
    return;
}