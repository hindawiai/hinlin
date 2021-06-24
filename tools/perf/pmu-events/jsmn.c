<शैली गुरु>
/*
 * Copyright (c) 2010 Serge A. Zaitsev
 *
 * Permission is hereby granted, मुक्त of अक्षरge, to any person obtaining a copy
 * of this software and associated करोcumentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modअगरy, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to करो so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 *
 * Slightly modअगरied by AK to not assume 0 terminated input.
 */

#समावेश <मानककोष.स>
#समावेश "jsmn.h"

/*
 * Allocates a fresh unused token from the token pool.
 */
अटल jsmntok_t *jsmn_alloc_token(jsmn_parser *parser,
				   jsmntok_t *tokens, माप_प्रकार num_tokens)
अणु
	jsmntok_t *tok;

	अगर ((अचिन्हित)parser->toknext >= num_tokens)
		वापस शून्य;
	tok = &tokens[parser->toknext++];
	tok->start = tok->end = -1;
	tok->size = 0;
	वापस tok;
पूर्ण

/*
 * Fills token type and boundaries.
 */
अटल व्योम jsmn_fill_token(jsmntok_t *token, jsmntype_t type,
			    पूर्णांक start, पूर्णांक end)
अणु
	token->type = type;
	token->start = start;
	token->end = end;
	token->size = 0;
पूर्ण

/*
 * Fills next available token with JSON primitive.
 */
अटल jsmnerr_t jsmn_parse_primitive(jsmn_parser *parser, स्थिर अक्षर *js,
				      माप_प्रकार len,
				      jsmntok_t *tokens, माप_प्रकार num_tokens)
अणु
	jsmntok_t *token;
	पूर्णांक start;

	start = parser->pos;

	क्रम (; parser->pos < len; parser->pos++) अणु
		चयन (js[parser->pos]) अणु
#अगर_अघोषित JSMN_STRICT
		/*
		 * In strict mode primitive must be followed by ","
		 * or "}" or "]"
		 */
		हाल ':':
#पूर्ण_अगर
		हाल '\t':
		हाल '\r':
		हाल '\n':
		हाल ' ':
		हाल ',':
		हाल ']':
		हाल '}':
			जाओ found;
		शेष:
			अवरोध;
		पूर्ण
		अगर (js[parser->pos] < 32 || js[parser->pos] >= 127) अणु
			parser->pos = start;
			वापस JSMN_ERROR_INVAL;
		पूर्ण
	पूर्ण
#अगर_घोषित JSMN_STRICT
	/*
	 * In strict mode primitive must be followed by a
	 * comma/object/array.
	 */
	parser->pos = start;
	वापस JSMN_ERROR_PART;
#पूर्ण_अगर

found:
	token = jsmn_alloc_token(parser, tokens, num_tokens);
	अगर (token == शून्य) अणु
		parser->pos = start;
		वापस JSMN_ERROR_NOMEM;
	पूर्ण
	jsmn_fill_token(token, JSMN_PRIMITIVE, start, parser->pos);
	parser->pos--; /* parent sees closing brackets */
	वापस JSMN_SUCCESS;
पूर्ण

/*
 * Fills next token with JSON string.
 */
अटल jsmnerr_t jsmn_parse_string(jsmn_parser *parser, स्थिर अक्षर *js,
				   माप_प्रकार len,
				   jsmntok_t *tokens, माप_प्रकार num_tokens)
अणु
	jsmntok_t *token;
	पूर्णांक start = parser->pos;

	/* Skip starting quote */
	parser->pos++;

	क्रम (; parser->pos < len; parser->pos++) अणु
		अक्षर c = js[parser->pos];

		/* Quote: end of string */
		अगर (c == '\"') अणु
			token = jsmn_alloc_token(parser, tokens, num_tokens);
			अगर (token == शून्य) अणु
				parser->pos = start;
				वापस JSMN_ERROR_NOMEM;
			पूर्ण
			jsmn_fill_token(token, JSMN_STRING, start+1,
					parser->pos);
			वापस JSMN_SUCCESS;
		पूर्ण

		/* Backslash: Quoted symbol expected */
		अगर (c == '\\') अणु
			parser->pos++;
			चयन (js[parser->pos]) अणु
				/* Allowed escaped symbols */
			हाल '\"':
			हाल '/':
			हाल '\\':
			हाल 'b':
			हाल 'f':
			हाल 'r':
			हाल 'n':
			हाल 't':
				अवरोध;
				/* Allows escaped symbol \uXXXX */
			हाल 'u':
				/* TODO */
				अवरोध;
				/* Unexpected symbol */
			शेष:
				parser->pos = start;
				वापस JSMN_ERROR_INVAL;
			पूर्ण
		पूर्ण
	पूर्ण
	parser->pos = start;
	वापस JSMN_ERROR_PART;
पूर्ण

/*
 * Parse JSON string and fill tokens.
 */
jsmnerr_t jsmn_parse(jsmn_parser *parser, स्थिर अक्षर *js, माप_प्रकार len,
		     jsmntok_t *tokens, अचिन्हित पूर्णांक num_tokens)
अणु
	jsmnerr_t r;
	पूर्णांक i;
	jsmntok_t *token;

	क्रम (; parser->pos < len; parser->pos++) अणु
		अक्षर c;
		jsmntype_t type;

		c = js[parser->pos];
		चयन (c) अणु
		हाल '{':
		हाल '[':
			token = jsmn_alloc_token(parser, tokens, num_tokens);
			अगर (token == शून्य)
				वापस JSMN_ERROR_NOMEM;
			अगर (parser->toksuper != -1)
				tokens[parser->toksuper].size++;
			token->type = (c == '{' ? JSMN_OBJECT : JSMN_ARRAY);
			token->start = parser->pos;
			parser->toksuper = parser->toknext - 1;
			अवरोध;
		हाल '}':
		हाल ']':
			type = (c == '}' ? JSMN_OBJECT : JSMN_ARRAY);
			क्रम (i = parser->toknext - 1; i >= 0; i--) अणु
				token = &tokens[i];
				अगर (token->start != -1 && token->end == -1) अणु
					अगर (token->type != type)
						वापस JSMN_ERROR_INVAL;
					parser->toksuper = -1;
					token->end = parser->pos + 1;
					अवरोध;
				पूर्ण
			पूर्ण
			/* Error अगर unmatched closing bracket */
			अगर (i == -1)
				वापस JSMN_ERROR_INVAL;
			क्रम (; i >= 0; i--) अणु
				token = &tokens[i];
				अगर (token->start != -1 && token->end == -1) अणु
					parser->toksuper = i;
					अवरोध;
				पूर्ण
			पूर्ण
			अवरोध;
		हाल '\"':
			r = jsmn_parse_string(parser, js, len, tokens,
					      num_tokens);
			अगर (r < 0)
				वापस r;
			अगर (parser->toksuper != -1)
				tokens[parser->toksuper].size++;
			अवरोध;
		हाल '\t':
		हाल '\r':
		हाल '\n':
		हाल ':':
		हाल ',':
		हाल ' ':
			अवरोध;
#अगर_घोषित JSMN_STRICT
			/*
			 * In strict mode primitives are:
			 * numbers and booleans.
			 */
		हाल '-':
		हाल '0':
		हाल '1':
		हाल '2':
		हाल '3':
		हाल '4':
		हाल '5':
		हाल '6':
		हाल '7':
		हाल '8':
		हाल '9':
		हाल 't':
		हाल 'f':
		हाल 'n':
#अन्यथा
			/*
			 * In non-strict mode every unquoted value
			 * is a primitive.
			 */
			/*FALL THROUGH */
		शेष:
#पूर्ण_अगर
			r = jsmn_parse_primitive(parser, js, len, tokens,
						 num_tokens);
			अगर (r < 0)
				वापस r;
			अगर (parser->toksuper != -1)
				tokens[parser->toksuper].size++;
			अवरोध;

#अगर_घोषित JSMN_STRICT
			/* Unexpected अक्षर in strict mode */
		शेष:
			वापस JSMN_ERROR_INVAL;
#पूर्ण_अगर
		पूर्ण
	पूर्ण

	क्रम (i = parser->toknext - 1; i >= 0; i--) अणु
		/* Unmatched खोलोed object or array */
		अगर (tokens[i].start != -1 && tokens[i].end == -1)
			वापस JSMN_ERROR_PART;
	पूर्ण

	वापस JSMN_SUCCESS;
पूर्ण

/*
 * Creates a new parser based over a given  buffer with an array of tokens
 * available.
 */
व्योम jsmn_init(jsmn_parser *parser)
अणु
	parser->pos = 0;
	parser->toknext = 0;
	parser->toksuper = -1;
पूर्ण

स्थिर अक्षर *jsmn_म_त्रुटि(jsmnerr_t err)
अणु
	चयन (err) अणु
	हाल JSMN_ERROR_NOMEM:
		वापस "No enough tokens";
	हाल JSMN_ERROR_INVAL:
		वापस "Invalid character inside JSON string";
	हाल JSMN_ERROR_PART:
		वापस "The string is not a full JSON packet, more bytes expected";
	हाल JSMN_SUCCESS:
		वापस "Success";
	शेष:
		वापस "Unknown json error";
	पूर्ण
पूर्ण
