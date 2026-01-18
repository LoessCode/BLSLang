//
// Created by Sid B on 06/01/26.
//

#include "../../headers/intermediate/astnodes.h"
#include <iostream>

std::ostream & BLSL::ASTNode::PrintVisitor::_out()
{
    if (_outFile)
    {
        for (unsigned i = 0; i < _tabLevel; i++)
        {
            _outFile << '\t';
        }
        return _outFile;
    }
    for (unsigned i = 0; i < _tabLevel; i++)
    {
        std::cout << '\t';
    }
    return std::cout;
}

BLSL::ASTNode::PrintVisitor::PrintVisitor(std::string outPath)
: _outPath(std::move(outPath))
{
    _outFile.open(_outPath);
    //TODO: EXCEPTION
}

BLSL::ASTNode::PrintVisitor::~PrintVisitor()
{
    _outFile.close();
}

void BLSL::ASTNode::PrintVisitor::visit(BodyNode *node)
{
    _out() << "{\n";
    _indent();
    for (auto& subNode : node->nodes)
    {
        subNode->invite(*this);
    }
    _unindent();
    _out() << "}\n";
}

void BLSL::ASTNode::PrintVisitor::visit(BinaryOperator *node)
{
    _out() << "Binary Operator: " << static_cast<int>(node->type) << "\n";

    _out() << "(\n";

    _indent();

    node->left->invite(*this);
    node->right->invite(*this);

    _unindent();

    _out() << ")" << std::endl;
}

void BLSL::ASTNode::PrintVisitor::visit(UnaryOperator *node)
{
    _out() << "Unary Operator: " << static_cast<int>(node->type) << "\n";

    _out() << "(\n";

    _indent();
    node->right->invite(*this);
    _unindent();

    _out() << ")" << std::endl;
}

void BLSL::ASTNode::PrintVisitor::visit(Literal *node)
{
    _out() << "Literal: <" << static_cast<int>(node->type) << "> " << node->value << std::endl;
}

void BLSL::ASTNode::PrintVisitor::visit(Variable *node)
{
    _out() << "Variable: " << node->identifier << std::endl;
}

void BLSL::ASTNode::PrintVisitor::visit(Func *node) {}
void BLSL::ASTNode::PrintVisitor::visit(For *node) {}
void BLSL::ASTNode::PrintVisitor::visit(While *node) {}

void BLSL::ASTNode::PrintVisitor::visit(If *node)
{
    _out() << "if (\n";
    node->condition->invite(*this);
    _out() << ")\n";
    node->body->invite(*this);

    if (node->elseBranch.has_value())
    {
        _out() << "else\n";
        node->elseBranch.value()->invite(*this);
    }
}

void BLSL::ASTNode::BodyNode::invite(Visitor &visitor)
{
    visitor.visit(this);
}

void BLSL::ASTNode::Literal::invite(Visitor &visitor)
{
    visitor.visit(this);
}

void BLSL::ASTNode::Variable::invite(Visitor &visitor)
{
    visitor.visit(this);
}

void BLSL::ASTNode::UnaryOperator::invite(Visitor &visitor)
{
    visitor.visit(this);
}

void BLSL::ASTNode::BinaryOperator::invite(Visitor &visitor)
{
    visitor.visit(this);
}

void BLSL::ASTNode::Func::invite(Visitor &visitor)
{
    visitor.visit(this);
}

void BLSL::ASTNode::If::invite(Visitor &visitor)
{
    visitor.visit(this);
}

void BLSL::ASTNode::For::invite(Visitor &visitor)
{
    visitor.visit(this);
}

void BLSL::ASTNode::While::invite(Visitor &visitor)
{
    visitor.visit(this);
}

