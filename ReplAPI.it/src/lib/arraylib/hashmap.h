#pragma once

#include "./array.h"

namespace adaptX {

template <class T1, class T2>
class HashMap
{
public:
	void put(const T1& key, const T2& value)
	{
		if (keys.indexOf(key) != -1)
		{
			values.set(keys.indexOf(key), value);
		}
		else
		{
			keys.push(key);
			values.push(value);
		}
	}

	// added const ref param and cosnt modifier
    // Later removed because of errors thrown because of it
	T2 get(T1 key)
	{
		if (keys.indexOf(key) != -1)
			return values.get(keys.indexOf(key));
		else
			return (T2)0;
	}

private:
	Array<T1> keys;
	Array<T2> values;
};

} //namespace adaptX