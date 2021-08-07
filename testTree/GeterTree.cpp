#include "GeterTree.h"

GeterTreeNode::~GeterTreeNode()
{

}

GeterTree::GeterTreeNodePrivate* GeterTree::GeterTreeNodePrivate::appendChild(GeterTreeNodePrivate* node)
{
	GeterTree::GeterTreeNodePrivate* ptr = nullptr;

	if (!node)
		return ptr;

	if (this->child() == nullptr)
		this->m_child = ptr = node;
	else
		ptr = this->child()->appendNext(node);

	return ptr;
}

GeterTree::GeterTreeNodePrivate* GeterTree::GeterTreeNodePrivate::appendNext(GeterTreeNodePrivate* node)
{
	GeterTree::GeterTreeNodePrivate* ptr = nullptr;

	if (!node)
		return nullptr;

	for (ptr = this; ptr->next(); ptr = ptr->next());

	

	if (this->next() == nullptr)
		this->m_next = ptr = node;
	else
		ptr = ptr->appendNext(node);

	return ptr;
}

//GeterTree

GeterTree::GeterTree()
{
}

GeterTree::~GeterTree()
{
}

GeterTreeNode* GeterTree::append(GeterTreeNode* node, const GeterTreeVariant& value)
{
	GeterTreeNodePrivate* n = new GeterTreeNodePrivate(value);

	if (!node)
	{
		m_node = n;
	}
	else
		n = static_cast<GeterTreeNodePrivate*>(node)->
											appendChild(n);

	m_count++;
	m_binarySize += value.size();

	return n;
}

void GeterTree::clear()
{
	removeRecursive(m_node);
	m_node			= nullptr;
	m_count			= 0;
	m_binarySize	= 0;
}

void GeterTree::removeRecursive(GeterTreeNode* node)
{
	if (!node)
		return;

	removeRecursive(node->child());
	removeRecursive(node->next());
	delete node;
}

