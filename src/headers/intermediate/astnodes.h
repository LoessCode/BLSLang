//
// Created by Sid B on 06/01/26.
//

#ifndef BLSLANG_ASTNODES_H
#define BLSLANG_ASTNODES_H

#include "../core/blsl.h"

namespace BLSL
{
    namespace ASTNode {
        struct Node;
        struct BodyNode;
    }

    struct FormalParameter
    {
        size_t size;
        std::string identifier;
    };

    typedef std::vector<FormalParameter> FormalParameterDeclaration_t;
    typedef std::unique_ptr<ASTNode::Node> Node_t;
    typedef std::unique_ptr<ASTNode::BodyNode> BodyNode_t;

    namespace ASTNode
    {

        struct Node
        {
            virtual ~Node() = default;
            DebugPosition debugPos;
        };

        struct BodyNode
        {
            virtual ~BodyNode() = default;
            std::vector<Node_t> nodes;
        };

        /*
         *  ATOMS
         */

        struct Literal : public Node
        {
            LiteralType type;
            std::string value;
        };

        struct Variable : public Node
        {
            std::string identifier;
        };

        /*
         *  OPERATORS
         */

        struct Operator : public Node
        {
            OperatorType type;
        };

        struct UnaryOperator : public Operator
        {
            Node_t right;
        };

        struct BinaryOperator : public Operator
        {
            Node_t left;
            Node_t right;
        };


        /*
         *  STATEMENTS
         */

        struct MemInit : public Node
        {
            size_t size;
        };

        struct Alloc : public Node
        {
            size_t size;
            std::string identifier;
        };

        struct Func : public Node
        {
            std::string identifier;
            FormalParameterDeclaration_t parameters;
            BodyNode_t body;
        };

        struct If : public Node
        {
            Node_t condition;
            BodyNode_t body;
            std::optional<Node_t> elseBranch;
        };

        struct For : public Node
        {
            std::optional<Node_t> initialize;
            std::optional<Node_t> condition;
            std::optional<Node_t> update;

            BodyNode_t body;
        };

        struct While : public Node
        {
            Node_t condition;
            BodyNode_t body;
        };

        /*
         * EXPRESSIONS
         */

        struct Call : public Node
        {
            Node_t callee;
            std::vector<Node_t> arguments;
        };
    }

}

#endif //BLSLANG_ASTNODES_H