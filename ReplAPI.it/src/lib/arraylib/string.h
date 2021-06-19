#pragma once

#include <string.h> // strlen, strncmp

namespace adaptX {

class String
{
private:
	int getLength(char* str) const
	{
		for (int i = 0; true; ++i)
		{
			if (str[i] == '\0')
				return i;
		}
		/*
		int i = 0;
		while (true)
		{
			if (str[i] == '\0')
				return i;

			++i;
		}
		*/
	};

public:
	// const char* initializer  ??
	String(char* initializer)
		: _value(initializer), _length(getLength(initializer))
	{
		//_value = initializer;
		//_length = getLength(initializer);
	};

	int length() const
	{
		return _length;
	}

	char get(int index) const
	{
		return _value[index];
	}

	// const char* string
	void operator=(char* str)
	{
		_value = str;
		_length = getLength(str);
	}

	// const char* str
	void operator+=(char* str)
	{
		int _len = getLength(str);

		char* temp = _value;
		_value = (char*)malloc((_length+_len) * sizeof(char*));

		int i;

		for (i = 0; i < _length; ++i)
			_value[i] = temp[i];
		
		for (int j = 0; j < _len; ++i, ++j)
			_value[i] = str[j];

		//_value[i] = '\0';
		_length += _len;
	}

	void operator+=(char str)
	{
		char* temp = _value;
		_value = (char*)malloc((_length+1) * sizeof(char*));

		int i;

		for (i = 0; i < _length; ++i)
			_value[i] = temp[i];

		for (int j = 0; j < 1; ++i, ++j)
			_value[i] = str;

		_length += 1;
	}

	// added this
	bool operator==(const char* str) const
	{
		return !strncmp(_value, str, strlen(str));
	}

    
	bool operator==(adaptX::String str) const
	{
		return !strncmp(_value, str.valueOf(), strlen(str.valueOf()));
	}

	char* valueOf()
	{
		return _value;
	}

private:
	char* _value;
	int _length;
};

} //namespace adaptX