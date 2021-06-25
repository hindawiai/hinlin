<शैली गुरु>
/* SPDX-License-Identअगरier: MIT */
#अगर_अघोषित __JSMN_H_
#घोषणा __JSMN_H_

/*
 * JSON type identअगरier. Basic types are:
 *	o Object
 *	o Array
 *	o String
 *	o Other primitive: number, boolean (true/false) or null
 */
प्रकार क्रमागत अणु
	JSMN_PRIMITIVE = 0,
	JSMN_OBJECT = 1,
	JSMN_ARRAY = 2,
	JSMN_STRING = 3
पूर्ण jsmntype_t;

प्रकार क्रमागत अणु
	/* Not enough tokens were provided */
	JSMN_ERROR_NOMEM = -1,
	/* Invalid अक्षरacter inside JSON string */
	JSMN_ERROR_INVAL = -2,
	/* The string is not a full JSON packet, more bytes expected */
	JSMN_ERROR_PART = -3,
	/* Everything was fine */
	JSMN_SUCCESS = 0
पूर्ण jsmnerr_t;

/*
 * JSON token description.
 * @param		type	type (object, array, string etc.)
 * @param		start	start position in JSON data string
 * @param		end		end position in JSON data string
 */
प्रकार काष्ठा अणु
	jsmntype_t type;
	पूर्णांक start;
	पूर्णांक end;
	पूर्णांक size;
पूर्ण jsmntok_t;

/*
 * JSON parser. Contains an array of token blocks available. Also stores
 * the string being parsed now and current position in that string
 */
प्रकार काष्ठा अणु
	अचिन्हित पूर्णांक pos; /* offset in the JSON string */
	पूर्णांक toknext; /* next token to allocate */
	पूर्णांक toksuper; /* superior token node, e.g parent object or array */
पूर्ण jsmn_parser;

/*
 * Create JSON parser over an array of tokens
 */
व्योम jsmn_init(jsmn_parser *parser);

/*
 * Run JSON parser. It parses a JSON data string पूर्णांकo and array of tokens,
 * each describing a single JSON object.
 */
jsmnerr_t jsmn_parse(jsmn_parser *parser, स्थिर अक्षर *js,
		     माप_प्रकार len,
		     jsmntok_t *tokens, अचिन्हित पूर्णांक num_tokens);

स्थिर अक्षर *jsmn_म_त्रुटि(jsmnerr_t err);

#पूर्ण_अगर /* __JSMN_H_ */
