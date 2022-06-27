#pragma once

#ifndef NODE_HPP
#define NODE_HPP 1

class Node {
public:
    // Getters & Setters
    int getID() const;
    int getDistance() const;
    void setDistance(int distance);
    bool operator()(const Node& other);

    class NodeHash {
        int operator()(const Node& node) {
            return node.getID();
        }
    };
protected:
    int id;
    int distance;
};

#endif