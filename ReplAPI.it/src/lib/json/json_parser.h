#include "json_object.h"

class JSONParser
{
public:
    static JSONObject parse(String data)
	{
        Types type = Types.NONE;
		
        if (data.charAt(0) == '[') type = Types.ARRAY;
        if (data.charAt(0) == '{') type = Types.OBJECT;
        // Parse JSON
        return new JSONObject(data.substring(1, data.length() - 1), type);
    }
}