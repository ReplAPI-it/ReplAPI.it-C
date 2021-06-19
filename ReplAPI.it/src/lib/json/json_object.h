#pragma once

class JSONObject
{    
public:
	JSONObject(String data, Types _type);

private:
    /**
     * Parses an array from a given data between the two square brackets
     * 
     * @param   data    the data between the square brackets
     * @return          an ArrayList of all of the data in the array
     **/
	ArrayList<Object> parseArray(String data) {
        ArrayList<Object> result;

        // Arrays for storing characters to look for
        char openChars[] = { '{', '[' };
        char closeChars[] = { '}', ']' };
        char openAndClose[] = { '"' };
        
		// Arrays for storing data for parsing based on above characters
        int depths[] = { 0, 0 };
        int values[] = { 0 };

        // Content of a certain data type
        String currentContent = "";
        // Initial type is NONE, the equivalent of null in this parser
        Types currentType = Types.NONE;
        // Declare i outside of for loop so we can use it later on
        int i = 0;
        // Loop through data
        for (; i < data.length(); ++i)
		{
            // Get current character
            char thisChar = data.charAt(i);
            if (thisChar == '\\')
			{
                // Escape codes
                // - Currently only supports \n, \t, \\, and escaping single characters
                ++i;

                if (data.charAt(i) == 'n')
					currentContent += "\n";
                else if (data.charAt(i) == 't')
					currentContent += "\t";
                else if (data.charAt(i) == '\\')
					currentContent += "\\";
                else
                    currentContent += data.substring(i, i+1);
            }
			else if (includes(openAndClose, thisChar))
			{
                // If a quote is found
                
                // Toggle value
                values[getIndex(openAndClose, thisChar)] = 1 - 
                	values[getIndex(openAndClose, thisChar)];

                if (allZero(depths))
				{
                    // If not in array or object
                    if(values[getIndex(openAndClose, thisChar)] == 1)
					{
                        // If start, start string reading
                        currentType = Types::STRING;
                        currentContent = "";
                    }
					else
					{
                        // If end, add data to results
                        currentType = Types::NONE;
                        result.add(String(currentContent));
                        currentContent = "";
                    }
                }
				else
				{
                    // Add a quote if in an object/array
                    currentContent += "\"";
                }
            }
			else if (!allZero(values))
			{
                // If in quotes
                currentContent += data.substring(i, i+1);
            }
			else if (includes(openChars,thisChar))
			{
                // If opening bracket
                if(allZero(depths)) {
                    // Start if not in another array/object
                    if(thisChar == '{') currentType = Types.OBJECT;
                    if(thisChar == '[') currentType = Types.ARRAY;
                    currentContent = "";
                } else {
                    // Otherwise, just add to content
                    currentContent += data.substring(i, i+1);
                }

                // Increment depths as we go deeper into data
                depths[getIndex(openChars, thisChar)]++;
            } else if (includes(closeChars,thisChar)) {
                // Closing bracket
                
                // Going out of deeper part of data
                depths[getIndex(closeChars, thisChar)]--;

                if(allZero(depths)) {                    
                    // Add data to results
                    result.add(new JSONObject(currentContent.trim(),
                            currentType));
                    currentType = Types.NONE;
                    currentContent = "";
                } else {
                    currentContent += data.substring(i, i+1);
                }
            } else if (!allZero(depths)) {
                // If in object or array
                currentContent += data.substring(i, i+1);
            } else if (thisChar == ',') {
                // If at a comma
                if(!(currentContent.trim().length() > 0)) {
                    // If nothing, do nothing
                    continue;
                }
                
                // Trim whitespace
                currentContent = currentContent.trim();
                if(currentContent.equals("true")) {
                    // true
                    result.add(true);
                } else if(currentContent.equals("false")) {
                    // false
                    result.add(false);
                } else if(currentContent.equals("null")) {
                    // null
                    result.add(null);
                } else {
                    try {
                        // Try as int
                        result.add((int)Integer.parseInt(currentContent));
                    } catch (Exception e) {
                        try {
                            // Try as double
                            result.add((double)Double.parseDouble(currentContent));
                        } catch (Exception err) {
                            // Unknown type
                            System.out.println("Warning: Unknown type");
                            System.out.println(currentContent);
                        }

                    }
                }
                // Reset
                currentContent = "";
            } else {
                currentContent += data.substring(i, i+1);
            }
        }
        // Process last item in array
        if(currentContent.trim().length() > 0) {
            currentContent = currentContent.trim();
            if(currentContent.equals("true")) {
                result.add(true);
            } else if(currentContent.equals("false")) {
                result.add(false);
            } else if(currentContent.equals("null")) {
                result.add(null);
            } else {
                try {
                    result.add((int)Integer.parseInt(currentContent));
                } catch (Exception e) {
                    try {
                        result.add((double)Double.parseDouble(currentContent));
                    } catch (Exception err) {
                        System.out.println("Warning: Unknown type");
                        System.out.println(currentContent);
                    }

                }
            }
            currentContent = "";
        }
        return result;
    }

    /**
     * Parses an object from a given data between the two curly brackets
     * 
     * @param   data    the data between the curly brackets
     * @return          a HashMap of all of the data in the object
     **/
    private HashMap<String, Object> parseObj(String data) {
        /*
         * Almost everything is the same as parseArray, so I am not going to
         * re-document everything here.
         */
        
        // HashMap instead of ArrayList
        HashMap<String, Object> result = new HashMap<String, Object>();

        char[] openChars = {'{', '['};
        char[] closeChars = {'}', ']'};
        char[] openAndClose = {'"'};
        int[] depths = {0, 0};
        int[] values = {0};
        int i = 0;
        // We need a key for each parameter of the object

        if(data.indexOf(":") == -1) {
            return result;
        } 

        String currentKey = data.substring(i, data.indexOf(":", i)).trim();
        currentKey = currentKey.substring(1, currentKey.length() - 1);
        // Move i to after key
        i = data.indexOf(":", i) + 1;
        
        String currentContent = "";
        Types currentType = Types.NONE;
        for(; i < data.length(); i++) {
            char thisChar = data.charAt(i);
            if(thisChar == '\\') {
                i++;
                if(data.charAt(i) == 'n') currentContent += "\n";
                else
                    currentContent += data.substring(i, i+1);
            } else if(includes(openAndClose, thisChar)) {
                values[getIndex(openAndClose, thisChar)] = 1 - 
                values[getIndex(openAndClose, thisChar)];
                if(allZero(depths)) {
                    if(values[getIndex(openAndClose, thisChar)] == 1) {
                        currentType = Types.STRING;
                        currentContent = "";
                    } else {
                        currentType = Types.NONE;
                        // Notice this is different since we are using 
                        // HashMap instead of ArrayList...
                        result.put(currentKey, new String(currentContent));
                        currentContent = "";
                    }
                } else {
                    currentContent += "\"";
                }
            } else if (!allZero(values)) {
                currentContent += data.substring(i, i+1);
            } else if (includes(openChars,thisChar)) {
                if(allZero(depths)) {
                    if(thisChar == '{') currentType = Types.OBJECT;
                    if(thisChar == '[') currentType = Types.ARRAY;
                    currentContent = "";
                } else {
                    currentContent += data.substring(i, i+1);
                }

                depths[getIndex(openChars, thisChar)]++;
            } else if (includes(closeChars,thisChar)) {
                depths[getIndex(closeChars, thisChar)]--;

                if(allZero(depths)) {                    
                    result.put(currentKey, new JSONObject(currentContent.trim(),
                            currentType));
                    currentType = Types.NONE;
                    currentContent = "";
                } else {
                    currentContent += data.substring(i, i+1);
                }
            } else if (!allZero(depths)) {
                currentContent += data.substring(i, i+1);
            } else if (thisChar == ',') {
                if(!(currentContent.trim().length() > 0)) {
                    // Even if nothing is found in this item, we need a new
                    // key.
                    i++;
                    currentKey = data.substring(i, data.indexOf(":", i)).trim();
                    currentKey = currentKey.substring(1, currentKey.length() - 1);
                    i = data.indexOf(":", i);
                    //System.out.println("New Key: " + currentKey);
                    currentContent = "";
                    continue;
                }
                currentContent = currentContent.trim();
                if(currentContent.equals("true")) {
                    result.put(currentKey, true);
                } else if(currentContent.equals("false")) {
                    result.put(currentKey, false);
                } else if(currentContent.equals("null")) {
                    result.put(currentKey, null);
                } else {
                    try {
                        result.put(currentKey, (int)Integer.parseInt(currentContent));
                    } catch (Exception e) {
                        try {
                            result.put(currentKey, (double)Double.parseDouble(currentContent));
                        } catch (Exception err) {
                            System.out.println("Warning: Unknown type");
                            System.out.println(currentContent);
                        }

                    }
                }
                // Get new key
                i++;
                currentKey = data.substring(i, data.indexOf(":", i)).trim();
                currentKey = currentKey.substring(1, currentKey.length() - 1);
                i = data.indexOf(":", i);
                //System.out.println("New Key: " + currentKey);
                currentContent = "";
            } else {
                currentContent += data.substring(i, i+1);
            }
        }
        if(currentContent.trim().length() > 0) {
            currentContent = currentContent.trim();
            if(currentContent.equals("true")) {
                result.put(currentKey, true);
            } else if(currentContent.equals("false")) {
                result.put(currentKey, false);
            } else if(currentContent.equals("null")) {
                result.put(currentKey, null);
            } else {
                try {
                    result.put(currentKey, (int)Integer.parseInt(currentContent));
                } catch (Exception e) {
                    try {
                        result.put(currentKey, (double)Double.parseDouble(currentContent));
                    } catch (Exception err) {
                        System.out.println("Warning: Unknown type");
                        System.out.println(currentContent);
                    }

                }
            }
        }
        return result;
    }

    /**
     * Gets if a char array includes a value
     * 
     * @param   arr     the array
     * @param   value   the value
     * @return          if value is in array
     **/
    private boolean includes(char[] arr, char value) {
        for(char val : arr) {
            if(val == value) return true;
        }
        return false;
    }

    /**
     * Gets index of value in char array
     * 
     * @param   arr     the array
     * @param   value   the value
     * @return          index
     **/
    private int getIndex(char[] arr, char value) {
        for(int i = 0; i < arr.length; i++) {
            char val = arr[i];
            if(val == value) return i;
        }
        return -1;
    }

    /**
     * Gets first non-zero index of an int array
     * 
     * @param   arr     the array
     * @return          index
     **/
    private int getNonZeroIndex(int[] arr) {
        for(int i = 0; i < arr.length; i++) {
            if(arr[i] != 0) return i;
        }
        return -1;
    }

    /**
     * Gets if an int array is all 0
     * 
     * @param   arr     the array
     * @return          if all zero
     **/
    private boolean allZero(int[] arr) {
        for(int i : arr) if(i != 0) return false;
        return true;
    }

    /**
     * toString() method
     * 
     * @return    data as a String
     **/
    public String toString() {
        if(type == Types.ARRAY) {
            String building = "[";
            for(Object item : arrData) {
                if(!building.equals("[")) {
                    building += ", ";
                }
                if(item instanceof String) {
                    building += "\"" + ((String)item).replace("\\", "\\\\").replace("\n", "\\n").replace("\t", "\\t").replace("\"", "\\\"") + "\"";
                } else {
                    building += item + "";
                }
            }
            building += "]";
            return building;
        } else {
            String building = "{";
            for(String key : objData.keySet()) {
                if(!building.equals("{")) {
                    building += ", ";
                }
                building += "\"" + ((String)key).replace("\\", "\\\\").replace("\n", "\\n").replace("\t", "\\t").replace("\"", "\\\"") + "\": ";

                Object item = objData.get(key);

                if(item instanceof String) {
                    building += "\"" + ((String)item).replace("\\", "\\\\").replace("\n", "\\n").replace("\t", "\\t").replace("\"", "\\\"") + "\"";
                } else {
                    building += item + "";
                }
            }
            building += "}";
            return building;
        }
    }
    
    /**
     * Gets a key from an object
     * 
     * @param   key   the key
     * @return        the value
     **/
    public Object get(String key) {
        if(type == Types.ARRAY) return null;
        return objData.get(key);
    }

    /**
     * Sets a key in the object
     * 
     * @param   key   the key
     * @param   val   the value
     **/
    public void set(String key, Object val) {
        if(type == Types.ARRAY) return;
        objData.put(key, val);
    }

    /**
     * Sets an index in the array
     * 
     * @param   index   the index
     * @param   val     the value
     **/
    public void set(int index, Object val) {
        if(type == Types.OBJECT) return;
        arrData.set(index, val);
    }

    /**
     * Adds to the array
     * 
     * @param   val     the value
     **/
    public void add(Object val) {
        if(type == Types.OBJECT) return;
        arrData.add(val);
    }

    /**
     * Adds to the array
     * 
     * @param   index   the index 
     * @param   val     the value
     **/
    public void add(int index, Object val) {
        if(type == Types.OBJECT) return;
        arrData.add(index, val);
    }
    
    /**
     * Gets an index from an array
     * 
     * @param   index   the index
     * @return          the value
     **/
    public Object get(int index) {
        if(type == Types.OBJECT) return null;
        return arrData.get(index);
    }
    
    /**
     * Accessor for ArrayList
     * 
     * @return   the ArrayList
     **/
    public ArrayList<Object> getArrayList() {
        return arrData;
    }
    
    /**
     * Accessor for HashMap
     * 
     * @return   the HashMap
     **/
    public HashMap<String, Object> getHashMap() {
        return objData;
    }
    
    /**
     * Create an object of a given class using this data
     * 
     * @param   classA   the class
     * @return           the object
     **/
    public <T> T toObject(Class<T> classA) throws Exception {
        // Get constructor
        Constructor thisConstructor = getConstructor(1, classA);

        // Make constructor accesible - otherwise error
        thisConstructor.setAccessible(true);
        
        Object[] params = new Object[0];
        if(type == Types.OBJECT) params = new Object[]{objData};
        if(type == Types.ARRAY) params = new Object[]{arrData};
        
        return (T)(thisConstructor.newInstance(params));
    }

    /**
     * Get a constructor given a length and a class
     * 
     * @param   length   the length
     * @param   classA   the class
     * @return           the constructor
     **/
    private Constructor getConstructor(int length, Class<?> classA) {
        // Get list
        Constructor[] list = classA.getDeclaredConstructors();
        // Loop through list
        for(Constructor current : list) {
            // If length matches, return
            if(current.getParameterCount() == length) {
                return current;
            }
        }
        // No value = null
        return null;
    }

private:
    HashMap<String, Object> objData;
    ArrayList<Object> arrData;

    Types type;
}