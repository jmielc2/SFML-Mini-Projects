#pragma once

#ifndef NODE_HPP
#define NODE_HPP 1

class Node {
public:
    // Getters & Setters
    int getID() const;
    int getDistance() const;
    void setDistance(int distance);
    void setParent(Node* parent);
    Node* getParent() const;
    Node operator=(const Node& other) = delete;

    class NodeComparator {
    public:
        bool operator()(const Node* first, const Node* second) {
            return first->getDistance() > second->getDistance();
        }
    };

    class NodeHash {
    public:
        int operator()(const Node* node) {
            return node->getID();
        }
    };
protected:
    int id;
    int distance;
    Node* parent;
};

#endif