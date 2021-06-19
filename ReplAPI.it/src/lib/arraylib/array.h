#pragma once

namespace lib {

template <typename Type>
class Array
{
public:
	Array();

public:
	void push(const Type& value)
	{
		++length;

		Type* temp = _array;

		_array = (Type*)malloc(length * sizeof(Type));
		arrcpy(_array, temp, length - 1);
		_array[length - 1] = value;
	}

	Type get(int index)
	{
		return _array[index];
	}

	void set(int index, Type value)
	{
		_array[index] = value;
	}

	void remove(int index)
	{
		--length;

		Type* temp = _array;
		_array = (Type*) malloc(length * sizeof(Type));

		//int j = 0;
		for (int i = 0, j = 0; i < length + 1; ++i)
		{
			if (i != index)
			{
				_array[j] = temp[i];
				++j;
			}
		}
	}

	Type pop()
	{
		--length;

		Type* temp = _array;
		_array = (Type*)malloc(length * sizeof(Type));

		//int j = 0;
		for (int i = 0, j = 0; i < length; ++i)
		{
			_array[j] = temp[i];
			++j;
		}

		return temp[length];
	}

	void clear()
	{
		_array = (Type*)malloc(0);
		length = 0;
	}

	// added const modifier
	int size() const
	{
		return length;
	}

	// added const ref param and const modifier
	int indexOf(const Type& value) const
	{
		for (int i = 0; i < length; ++i)
		{
			if (value == _array[i])
				return i;
		}

		return -1;
	}

private:
	Type* _array;
	int length;// = 0;

private:
	// added const param
	void arrcpy(Type* value1, const Type* value2, int l)
	{
		for (int i = 0; i < l; ++i)
			value1[i] = value2[i];
	};
};

} // namespace lib