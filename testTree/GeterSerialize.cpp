#include "GeterSerialize.h"
#include <fstream>
#include <filesystem>




void GeterSerializeBinary::fill(GeterTreeNode* node, char* buffer, unsigned long& index)
{
	if (!node)
		return;

	GeterSerializeBinary::GeterSerializeBinaryStruct* _node = reinterpret_cast<GeterSerializeBinary::GeterSerializeBinaryStruct *>( buffer + index);

	_node->size = node->size();
	_node->type = long(node->type());
	
	index += sizeof(GeterSerializeBinary::GeterSerializeBinaryStruct);

	_node->offset_data = index;
	memcpy(buffer + _node->offset_data, node->data(), node->size());

	index += _node->size;



	if (node->next())
		_node->offset_next = index;
	else
		_node->offset_next = 0;


	fill(node->next(), buffer, index);

	if (node->child())
		_node->offset_child = index;
	else
		_node->offset_child = 0;

	fill(node->child(), buffer, index);
}

void GeterSerializeBinary::fill(GeterTreeNode* node, const char* buffer, const GeterSerializeBinaryStruct* nodeBuffer)
{
	if (!nodeBuffer)
		return;



	node = m_ptr->append(
				node, 
				GeterTreeVariant(static_cast<const void*>(buffer+nodeBuffer->offset_data),
								nodeBuffer->size,
								GeterTreeVariant::GTN_DataType(nodeBuffer->type))
				);



	if(nodeBuffer->offset_next)
		fill(node, buffer, reinterpret_cast<const GeterSerializeBinaryStruct*>(buffer + nodeBuffer->offset_next));

	if(nodeBuffer->offset_child)
		fill(node, buffer, reinterpret_cast<const GeterSerializeBinaryStruct*>( buffer + nodeBuffer->offset_child));
	
}

void GeterSerializeBinary::save(const std::string& filename)
{
	if (!m_ptr)
		return;

	unsigned long sz =
		m_ptr->binarySize() +
		m_ptr->count() * sizeof(GeterSerializeBinary::GeterSerializeBinaryStruct);
	
	char* buffer = static_cast<char*>(malloc(sz));

	unsigned long index = 0;
	fill(m_ptr->node(), buffer, index);

	std::ofstream f(filename, std::ofstream::binary);

	f.write(buffer, sz);

	free(buffer);
}

void GeterSerializeBinary::load(const std::string& filename)
{
	if (!m_ptr)
		return;

	std::ifstream f(filename, std::ifstream::binary);
	

	f.seekg(0, std::ifstream::end);

	if (!f.is_open())
		return;

	char* buffer;
	int sz = f.tellg();

	buffer = static_cast<char*>( malloc(sz));

	f.seekg(0, std::ifstream::beg);
	f.read(buffer, sz);

	GeterSerializeBinaryStruct *d = reinterpret_cast<GeterSerializeBinaryStruct*>( buffer);

	fill(nullptr, buffer, d);
	
	free(buffer);
}
