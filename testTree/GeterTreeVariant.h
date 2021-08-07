#ifndef GETERTREEVARIANT_H
#define GETERTREEVARIANT_H

#include <string>

class GeterTreeVariant
{
public:
	enum class GTN_DataType
	{
		GTN_undefined,
		GTN_byte_array,
		GTN_int,
		GTN_int64,
		GTN_float,
		GTN_double,
		GTN_string,
		GTN_wstring
	};

	explicit GeterTreeVariant(const GeterTreeVariant& value);
	GeterTreeVariant(const void* data, unsigned long sz, GTN_DataType type)  :
		m_data(nullptr), m_size(0), m_dataType(GeterTreeVariant::GTN_DataType::GTN_undefined),
		m_allocated(false)
	{
		setValue(data, sz);
		m_dataType = type;
	}
	GeterTreeVariant(void* data = nullptr, int sz = -1);
	
	GeterTreeVariant(const int &val) {
		setValue(val);
	}

	GeterTreeVariant(const long long& val) {
		setValue(val);
	}

	GeterTreeVariant(const float& val) {
		setValue(val);
	}

	GeterTreeVariant(const double& val) {
		setValue(val);
	}

	GeterTreeVariant(const std::string& val) {
		setValue(val);
	}

	GeterTreeVariant(const std::wstring& val) {
		setValue(val);
	}



	~GeterTreeVariant();


	//operators

	bool operator==(const GeterTreeVariant& var) {
		return
			!(
				this->type() != var.type() ||
				this->size() != var.size() ||
				memcmp(this->data(), var.data(), var.size()) != 0);
	}
	

	//kit set methods

	void setValue(const void* data, int sz = -1);

	//set value int
	void setValue(const int &val) {
		setValue(&val, sizeof(val));
		m_dataType = GeterTreeVariant::GTN_DataType::GTN_int;
	}
	//set value int64
	void setValue(const long long &val) {
		setValue(&val, sizeof(val));
		m_dataType = GeterTreeVariant::GTN_DataType::GTN_int64;
	}
	//set value float
	void setValue(const float& val) {
		setValue(&val, sizeof(val));
		m_dataType = GeterTreeVariant::GTN_DataType::GTN_float;
	}
	//set value double
	void setValue(const double& val) {
		setValue(&val, sizeof(val));
		m_dataType = GeterTreeVariant::GTN_DataType::GTN_double;
	}
	//set value std::string
	void setValue(const std::string& val) {
		setValue(val.data(), sizeof(val.size() * sizeof(char)));
		m_dataType = GeterTreeVariant::GTN_DataType::GTN_string;
	}
	//set value std::wstring
	void setValue(const std::wstring& val) {
		setValue(val.data(), sizeof(val.size() * sizeof(wchar_t)));
		m_dataType = GeterTreeVariant::GTN_DataType::GTN_wstring;
	}

	//kit get methods
	const void*	 data()	const { return m_data; }
	int			 size()	const { return m_size; }
	GTN_DataType type() const { return m_dataType; }

	int		  toInt()		  { return static_cast<int>(*static_cast<const char*>(data())); }
	long long toInt64()       { return static_cast<long long>(*static_cast<const char*>(data())); }
	float	  toFloat()	      { return static_cast<float>(*static_cast<const char*>(data())); }
	double	  toDouble()      { return static_cast<double>(*static_cast<const char*>(data())); }
	std::string toString() {
		return std::string(static_cast<const char*>(data()));
	}
	std::wstring toWString() {
		return std::wstring(static_cast<const wchar_t*>(data()));
	}


	void clear();

private:
	void*		 m_data = nullptr;
	int			 m_size	= 0;
	GTN_DataType m_dataType = GTN_DataType::GTN_undefined;

	bool m_allocated	= false;
};

#endif //GETERTREENODE_H

