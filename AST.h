#pragma once

#include "CPos.h"
#include "hash_pair.h"

using CValue = std::variant<std::monostate, double, std::string>;

/**
 * @brief Represents a node in the abstract syntax tree (AST).
 */
class ASTNode {
public:
    /**
     * @brief Destructor for the ASTNode class.
     */
    virtual ~ASTNode() = default;

    /**
     * @brief Moves the relative node to its new position by the specified offset.
     * @param offset The offset by which to move the node.
     */
    virtual void moveRelative(std::pair<size_t, size_t> offset) = 0;

    /**
     * @brief Evaluates the value of the node, called recursively to get value of the whole AST.
     * @param sheet Map of all nodes, used to get value of reference nodes.
     * @return The evaluated value of the node.
     */
    virtual CValue
    evaluate(const std::unordered_map<std::pair<size_t, size_t>, std::shared_ptr<ASTNode>, hash_pair> &sheet) const = 0;

    /**
     * @brief Returns string representation of a node, gets the string representation of a whole tree when used recursively
     * @return string representation of AST
     */
    virtual std::string toString() const = 0;

    /**
    * @brief Creates a deep copy of the node.
    * @return A shared pointer to the cloned node.
    */
    virtual std::shared_ptr<ASTNode> clone() const = 0;

    /**
    * @brief Checks for cycles in the AST starting from this node. Uses DFS algorithm.
    * @param openNodes Set of open nodes being traversed to detect cycles.
    * @param map Map of all nodes in the sheet.
    * @return True if a cycle is detected, otherwise false.
    */
    virtual bool checkCycle(std::unordered_set<std::pair<size_t, size_t>, hash_pair> &openNodes,
                            std::unordered_map<std::pair<size_t, size_t>, std::shared_ptr<ASTNode>, hash_pair> &map) const = 0;

protected:
private:
};

using ANode = std::shared_ptr<ASTNode>;