#ifndef GETERTREE_H
#define GETERTREE_H

#include "GeterTreeVariant.h"



class GeterTreeNode : public GeterTreeVariant
{
public:
	GeterTreeNode(const GeterTreeVariant& val) : GeterTreeVariant(val),
		m_next(nullptr), m_child(nullptr) {}

	GeterTreeNode() : GeterTreeVariant(),
		m_next(nullptr), m_child(nullptr) {}

	GeterTreeNode* next() { 
		return static_cast<GeterTreeNode*>(m_next);
	}

	GeterTreeNode* child() {
		return static_cast<GeterTreeNode*>(m_child);
	}

	~GeterTreeNode();
protected:
	void* m_next	= nullptr;
	void* m_child	= nullptr;
};

class GeterTree
{
private:
	class GeterTreeNodePrivate : public GeterTreeNode {
	public:
		GeterTreeNodePrivate(const GeterTreeVariant& val) : GeterTreeNode(val) {}
		GeterTreeNodePrivate() : GeterTreeNode() {}


		GeterTree::GeterTreeNodePrivate* appendChild(GeterTreeNodePrivate* node);
		GeterTree::GeterTreeNodePrivate* appendNext(GeterTreeNodePrivate* node);

		GeterTreeNodePrivate* next() const {
			return static_cast<GeterTreeNodePrivate*>(m_next);
		}
		GeterTreeNodePrivate* child() const {
			return static_cast<GeterTreeNodePrivate*>(m_child);
		}
	};

public:
	GeterTree();
	~GeterTree();

	GeterTreeNode* append(GeterTreeNode* node, const GeterTreeVariant &value);
	

	
	void clear();


	GeterTreeNode* node() {
		return static_cast<GeterTreeNode*>(m_node);
	}

	int count() const { return m_count; }
	unsigned long binarySize() const { return m_binarySize; }

private:
	void removeRecursive(GeterTreeNode* node);


private:
	GeterTreeNodePrivate* m_node;
	int					  m_count = 0;
	unsigned long		  m_binarySize = 0;
};

#endif //GETERTREE_H
