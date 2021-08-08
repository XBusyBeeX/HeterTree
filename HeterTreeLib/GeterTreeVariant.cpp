#include "GeterTreeVariant.h"
#include <memory>

static int GetDataSize(const char* data)
{
	int i = 0;
	while (data[++i] != '\0');
	return i;
}

GeterTreeVariant::GeterTreeVariant(const GeterTreeVariant& value) :
	m_data(nullptr), m_size(0), m_dataType(GeterTreeVariant::GTN_DataType::GTN_undefined),
	m_allocated(false)
{
	setValue(value.data(), value.size());
	m_dataType = value.type();
}

GeterTreeVariant::GeterTreeVariant(void* data, int sz) :
	m_data(data), m_size(sz), m_dataType(GeterTreeVariant::GTN_DataType::GTN_undefined),
	m_allocated(false)
{
	if (data)
	{
		m_dataType = GeterTreeVariant::GTN_DataType::GTN_byte_array;
	
		if (sz < 0)
			m_size = GetDataSize(static_cast<const char*>(data));
	}

	if(m_size < 0)
		m_size = 0;

}

GeterTreeVariant::~GeterTreeVariant()
{
	clear();
}

void GeterTreeVariant::setValue(const void* data, int sz)
{

	clear();

	if (sz < 0)
		sz = GetDataSize(static_cast<const char*>(data));

	if (sz <= 0)
		return;

	if (
			(m_allocated = m_data = malloc(sz))
		)
	{
		memcpy(m_data, data, sz);
		m_size = sz;
		m_dataType = GeterTreeVariant::GTN_DataType::GTN_byte_array;
	}
	

}

void GeterTreeVariant::clear()
{
	if (m_data && m_allocated)
		free(m_data);

	m_data = nullptr;
	m_size = 0;
	m_dataType = GeterTreeVariant::GTN_DataType::GTN_undefined;
	m_allocated = false;
}