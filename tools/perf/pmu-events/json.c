<शैली गुरु>
/* Parse JSON files using the JSMN parser. */

/*
 * Copyright (c) 2014, Intel Corporation
 * All rights reserved.
 *
 * Redistribution and use in source and binary क्रमms, with or without
 * modअगरication, are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice,
 * this list of conditions and the following disclaimer.
 *
 * 2. Redistributions in binary क्रमm must reproduce the above copyright
 * notice, this list of conditions and the following disclaimer in the
 * करोcumentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
 * FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE
 * COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY सूचीECT,
 * INसूचीECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT,
 * STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED
 * OF THE POSSIBILITY OF SUCH DAMAGE.
*/

#समावेश <मानककोष.स>
#समावेश <माला.स>
#समावेश <sys/mman.h>
#समावेश <sys/स्थिति.स>
#समावेश <fcntl.h>
#समावेश <मानकपन.स>
#समावेश <त्रुटिसं.स>
#समावेश <unistd.h>
#समावेश "jsmn.h"
#समावेश "json.h"
#समावेश <linux/kernel.h>


अटल अक्षर *mapfile(स्थिर अक्षर *fn, माप_प्रकार *size)
अणु
	अचिन्हित ps = sysconf(_SC_PAGESIZE);
	काष्ठा stat st;
	अक्षर *map = शून्य;
	पूर्णांक err;
	पूर्णांक fd = खोलो(fn, O_RDONLY);

	अगर (fd < 0 && verbose > 0 && fn) अणु
		pr_err("Error opening events file '%s': %s\n", fn,
				म_त्रुटि(त्रुटि_सं));
	पूर्ण

	अगर (fd < 0)
		वापस शून्य;
	err = ख_स्थिति(fd, &st);
	अगर (err < 0)
		जाओ out;
	*size = st.st_size;
	map = mmap(शून्य,
		   (st.st_size + ps - 1) & ~(ps - 1),
		   PROT_READ|PROT_WRITE, MAP_PRIVATE, fd, 0);
	अगर (map == MAP_FAILED)
		map = शून्य;
out:
	बंद(fd);
	वापस map;
पूर्ण

अटल व्योम unmapfile(अक्षर *map, माप_प्रकार size)
अणु
	अचिन्हित ps = sysconf(_SC_PAGESIZE);
	munmap(map, roundup(size, ps));
पूर्ण

/*
 * Parse json file using jsmn. Return array of tokens,
 * and mapped file. Caller needs to मुक्त array.
 */
jsmntok_t *parse_json(स्थिर अक्षर *fn, अक्षर **map, माप_प्रकार *size, पूर्णांक *len)
अणु
	jsmn_parser parser;
	jsmntok_t *tokens;
	jsmnerr_t res;
	अचिन्हित sz;

	*map = mapfile(fn, size);
	अगर (!*map)
		वापस शून्य;
	/* Heuristic */
	sz = *size * 16;
	tokens = दो_स्मृति(sz);
	अगर (!tokens)
		जाओ error;
	jsmn_init(&parser);
	res = jsmn_parse(&parser, *map, *size, tokens,
			 sz / माप(jsmntok_t));
	अगर (res != JSMN_SUCCESS) अणु
		pr_err("%s: json error %s\n", fn, jsmn_म_त्रुटि(res));
		जाओ error_मुक्त;
	पूर्ण
	अगर (len)
		*len = parser.toknext;
	वापस tokens;
error_मुक्त:
	मुक्त(tokens);
error:
	unmapfile(*map, *size);
	वापस शून्य;
पूर्ण

व्योम मुक्त_json(अक्षर *map, माप_प्रकार size, jsmntok_t *tokens)
अणु
	मुक्त(tokens);
	unmapfile(map, size);
पूर्ण

अटल पूर्णांक countअक्षर(अक्षर *map, अक्षर c, पूर्णांक end)
अणु
	पूर्णांक i;
	पूर्णांक count = 0;
	क्रम (i = 0; i < end; i++)
		अगर (map[i] == c)
			count++;
	वापस count;
पूर्ण

/* Return line number of a jsmn token */
पूर्णांक json_line(अक्षर *map, jsmntok_t *t)
अणु
	वापस countअक्षर(map, '\n', t->start) + 1;
पूर्ण

अटल स्थिर अक्षर * स्थिर jsmn_types[] = अणु
	[JSMN_PRIMITIVE] = "primitive",
	[JSMN_ARRAY] = "array",
	[JSMN_OBJECT] = "object",
	[JSMN_STRING] = "string"
पूर्ण;

#घोषणा LOOKUP(a, i) ((i) < (माप(a)/माप(*(a))) ? ((a)[i]) : "?")

/* Return type name of a jsmn token */
स्थिर अक्षर *json_name(jsmntok_t *t)
अणु
	वापस LOOKUP(jsmn_types, t->type);
पूर्ण

पूर्णांक json_len(jsmntok_t *t)
अणु
	वापस t->end - t->start;
पूर्ण

/* Is string t equal to s? */
पूर्णांक json_streq(अक्षर *map, jsmntok_t *t, स्थिर अक्षर *s)
अणु
	अचिन्हित len = json_len(t);
	वापस len == म_माप(s) && !strnहालcmp(map + t->start, s, len);
पूर्ण
