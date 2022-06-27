#pragma once

#ifndef NODE_HPP
#define NODE_HPP 1

class Node {
public:
    // Getters & Setters
    int getID() const;
    int getDistance() const;
    void setDistance(int distance);
private:
    int id;
    int distance;
};

#endif