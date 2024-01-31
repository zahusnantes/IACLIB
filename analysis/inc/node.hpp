#ifndef NODE_HPP
#define NODE_HPP

#include <vector>
#include <map>
#include <string>

enum Operation
{
    MULTIPLICATION = 0,
    ADDITION = 1,
    COMPARAISON = 2,
};

enum MemCopyDirection
{
    MM_TO_SM = 0,
    SM_TO_MM = 1,
    SM_TO_SM = 2,
};

std::string direction_to_string(enum MemCopyDirection direction_);
std::string operation_to_string(enum Operation op);

class MemCopy
{
private:
    int s_index, f_index;
    enum MemCopyDirection direction;

public:
    MemCopy();
    ~MemCopy();
    MemCopy(int s_index_, int f_index_, enum MemCopyDirection direction_);
    std::string to_string() const;
    int getSIndex() const;
    int getFIndex() const;
    MemCopy merge(MemCopy other);
};

class Node
{
private:
    int id;
    std::map<enum ::Operation, int> operations;
    std::vector<MemCopy> mem_copies;
    std::vector<Node> children;

public:
    Node(int id_);
    Node();
    ~Node();
    int getID();
    int totalMemorySize();
    int computationTime();
    int memCpyDuration();
    int getMemCopyCount();
    void setOperationCount(enum Operation op, int count);
    int getOperationCount(enum Operation op);
    void addMemCpy(MemCopy &cpy);
    void display();
    void printChildren();
    void addChild(Node &child);
    void mergeChildren();
    Node mergeTwoNodes();
    Node mergeTwoNodes(Node n1, Node n2);

    std::vector<MemCopy>::iterator mem_begin();
    std::vector<MemCopy>::iterator mem_end();
};

#endif