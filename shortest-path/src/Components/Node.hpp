#pragma once

#ifndef NODE_HPP
#define NODE_HPP 1

#include "../stdafx.hpp"

class Node {
public:
    // General
    enum Type {START, END, NONE, HOVER, PATH, WALL, VISITED};

    // Getters & Setters
    Node::Type getType() const;
    void setType(Node::Type type);
    int getID() const;
    double getDistance() const;
    void setDistance(double distance);
    void setParent(Node* parent);
    Node* getParent() const;
    
    Node operator=(const Node& other) = delete;
    
    virtual void draw(sf::RenderWindow* window) = 0;
    virtual void reset() = 0;
    virtual void update(Node::Type type) = 0;

    template <typename E>
    class NodeComparator {
    public:
        bool operator()(const E* first, const E* second) {
            return first->getDistance() >= second->getDistance();
        }
    };

    virtual ~Node();
protected:
    int id;
    double distance;
    Node* parent;
    Node::Type type;
};

#endif