#pragma once

#ifndef NODE_HPP
#define NODE_HPP 1

#include "../stdafx.hpp"

class Node {
public:
    // General
    enum Type {START, END, NONE, PATH, WALL};

    // Getters & Setters
    Node::Type getType() const;
    void setType(Node::Type type);
    int getID() const;
    int getDistance() const;
    void setDistance(int distance);
    void setParent(Node* parent);
    Node* getParent() const;
    
    Node operator=(const Node& other) = delete;
    
    virtual void draw(sf::RenderWindow* window);
    virtual void reset();
    virtual void update(Node::Type type);

    virtual ~Node();

    class NodeComparator {
    public:
        bool operator()(const Node* first, const Node* second) {
            return first->getDistance() >= second->getDistance();
        }
    };
protected:
    int id;
    int distance;
    Node* parent;
    Node::Type type;
};

#endif