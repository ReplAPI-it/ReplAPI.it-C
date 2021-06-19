#include "array.h"

lib::Array()
	: length(0)
{
	_array = (Type*)malloc(length * sizeof(Type));
}