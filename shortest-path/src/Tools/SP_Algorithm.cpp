#include "SP_Algorithm.hpp"

std::priority_queue<Node, std::vector<Node>, Node> SP_Algorithm::queue;
std::unordered_set<Node, Node::NodeHash> SP_Algorithm::visited;

void SP_Algorithm::init() {

}