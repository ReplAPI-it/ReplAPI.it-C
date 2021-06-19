#include "json_object.h"

JSONObject::JSONObject(String data, Types _type) {
	type = _type;

	switch (type)
	{
	case Types::OBJECT:
		objData = parseObj(data);
		break;
	case Types::ARRAY:
		objData = parseArray(data);
		break;
	}
}