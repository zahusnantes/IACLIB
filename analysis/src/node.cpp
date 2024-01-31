#include "../inc/node.hpp"
#include <algorithm>
#include <iostream>

MemCopy::MemCopy()
{
}
MemCopy::~MemCopy()
{
}

MemCopy::MemCopy(int s_index_, int f_index_, enum MemCopyDirection direction_)
    : s_index(s_index_), f_index(f_index_), direction(direction_)
{
}

MemCopy MemCopy::merge(MemCopy other)
{

        int ss_index = std::min(s_index, other.s_index);
        int ff_index = std::max(f_index, other.f_index);        
        return MemCopy(ss_index, ff_index, direction);
}

int MemCopy::getSIndex() const
{
        return s_index;
}

int MemCopy::getFIndex() const
{
        return f_index;
}

std::string direction_to_string(enum MemCopyDirection direction)
{
        switch (direction)
        {
        case MM_TO_SM:
                return "MM->SM";
        case SM_TO_MM:
                return "SM->MM";
        case SM_TO_SM:
                return "SM->SM";
        }
        return "UNKNOWN_DIRECTION";
}

std::string operation_to_string(enum Operation op)
{
        switch (op)
        {
        case MULTIPLICATION:
                return "MUL";
        case ADDITION:
                return "ADD";
        case COMPARAISON:
                return "CMP";
        }
        return "UNKNOWN_OPERATION";
}

std::string MemCopy::to_string() const
{
        return direction_to_string(direction) + ":[" + std::to_string(s_index) + "," + std::to_string(f_index) + "]";
}

Node::Node()
{
        id = -1;
}
Node::Node(int id_) : id(id_)
{
}
Node::~Node()
{
}

int Node::totalMemorySize()
{

        std::cerr << "Not yet implemented" << std::endl;
        exit(-1);

        return 0;
}

int Node::computationTime()
{

        std::cerr << "Not yet implemented" << std::endl;
        exit(-1);

        return 0;
}

int Node::memCpyDuration()
{       

        std::cerr << "Not yet implemented" << std::endl;
        exit(-1);
        return 0;
}

void Node::setOperationCount(enum Operation op, int count)
{
        operations.insert(std::make_pair(op, count));
}

int Node::getOperationCount(enum Operation op)
{
        return operations[op];
}

void Node::addMemCpy(MemCopy &cpy)
{
        mem_copies.push_back(cpy);
}

void Node::display()
{
        std::cout << "[Node: " << id << " " << std::endl;
        std::cout << "\t"
                  << "[Operations" << std::endl;
        for (auto op : operations)
        {
                std::cout << "\t\t" << operation_to_string(op.first) << ":" << op.second << std::endl;
        }
        std::cout << "\t]" << std::endl;
        std::cout << "\t[Mem copies" << std::endl;
        for (auto mcp : mem_copies)
        {
                std::cout << "\t\t" << mcp.to_string() << std::endl;
        }
        std::cout << "\t]" << std::endl;
        std::cout << " ] " << std::endl;
}

void Node::addChild(Node &child)
{
        children.push_back(child);
}

void Node::printChildren()
{
        std::cout << "[Node" << id << ", Children->";
        for (auto child : children)
        {
                std::cout << child.getID() << ",";
        }
        std::cout << "]" << std::endl;
}

int Node::getID()
{
        return id;
}

std::vector<MemCopy>::iterator Node::mem_begin()
{
        return mem_copies.begin();
}
std::vector<MemCopy>::iterator Node::mem_end()
{
        return mem_copies.end();
}

int Node::getMemCopyCount()
{
        return mem_copies.size();
}

bool isInterleaving(const MemCopy cp1, const MemCopy cp2)
{
        std::cout<<cp1.to_string()<<" "<<cp2.to_string()<<std::endl;
        return (cp1.getSIndex() <= cp2.getFIndex() && cp2.getSIndex()-1 <= cp1.getFIndex());
}

Node Node::mergeTwoNodes(Node n1, Node n2)
{
        Node merged;
        merged.addChild(n1);
        merged.addChild(n2);
        merged.setOperationCount(MULTIPLICATION, n1.getOperationCount(MULTIPLICATION)+ n2.getOperationCount(MULTIPLICATION));
        merged.setOperationCount(ADDITION, n1.getOperationCount(ADDITION)+ n2.getOperationCount(ADDITION));

        std::vector<MemCopy> merged_memcopies;
        std::vector<MemCopy> final_merged;
        
        merged_memcopies.reserve(n1.getMemCopyCount() + n2.getMemCopyCount()); // Reserve memory for efficiency
        merged_memcopies.insert(merged_memcopies.end(), n1.mem_begin(), n1.mem_end());
        merged_memcopies.insert(merged_memcopies.end(), n2.mem_begin(), n2.mem_end());


        std::sort(merged_memcopies.begin(), merged_memcopies.end(), [](const MemCopy &a, const MemCopy &b)
                  { return a.getSIndex() < b.getSIndex(); });

        bool stop = false;
        int current_index = 0;
        auto current = merged_memcopies.begin();
        int gap =0;
        while (!stop)
        {
                if (current+gap+1 == merged_memcopies.end())
                {
                        stop = true;
                        final_merged.push_back(*current);

                }
                else
                {                        
                        if (isInterleaving(*current,*(current+1+gap) ))
                        {
                                *current = current->merge(*(current+1+gap));
                                gap++;
                        }
                        else {
                                final_merged.push_back(*current);
                                current+=gap+1;
                                gap=0;
                        }
                }
        }
        for (auto v: final_merged)
        {
                merged.addMemCpy(v);
        }
        return merged;
}

void Node::mergeChildren()
{


        Node n;
        for (auto v: children){
                n=n.mergeTwoNodes(n, v);
        }

        n.display();
        
}