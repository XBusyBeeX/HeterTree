#ifndef GETERTREESERIALIZE_H
#define GETERTREESERIALIZE_H

#include <string>
#include "GeterTree.h"

class IGeterSerialize
{
public:
	IGeterSerialize(GeterTree* ptr) : m_ptr(ptr) {}
	
	virtual void save(const std::string& filename) = 0;
	virtual void load(const std::string & filename) = 0;

protected:
	GeterTree* m_ptr;
};


class GeterSerializeBinary : IGeterSerialize
{
private:
	struct GeterSerializeBinaryStruct
	{
		long		  type;
		unsigned long size;
		unsigned long offset_data;
		unsigned long offset_next;
		unsigned long offset_child;
	};

public:

	GeterSerializeBinary(GeterTree* ptr) : IGeterSerialize(ptr) {}


	void save(const std::string& filename) override;
	void load(const std::string& filename) override;

private:
	static void fill(GeterTreeNode* node, char* buffer, unsigned long& index);
	void fill(GeterTreeNode* node, const char *buffer, const GeterSerializeBinaryStruct* nodeBuffer);
};

#endif //GETERTREESERIALIZE_H