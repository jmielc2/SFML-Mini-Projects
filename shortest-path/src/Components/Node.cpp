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