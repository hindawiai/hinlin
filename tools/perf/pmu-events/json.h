<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित JSON_H
#घोषणा JSON_H 1

#समावेश "jsmn.h"

jsmntok_t *parse_json(स्थिर अक्षर *fn, अक्षर **map, माप_प्रकार *size, पूर्णांक *len);
व्योम मुक्त_json(अक्षर *map, माप_प्रकार size, jsmntok_t *tokens);
पूर्णांक json_line(अक्षर *map, jsmntok_t *t);
स्थिर अक्षर *json_name(jsmntok_t *t);
पूर्णांक json_streq(अक्षर *map, jsmntok_t *t, स्थिर अक्षर *s);
पूर्णांक json_len(jsmntok_t *t);

बाह्य पूर्णांक verbose;

#समावेश <stdbool.h>

बाह्य पूर्णांक eम_लिखो(पूर्णांक level, पूर्णांक var, स्थिर अक्षर *fmt, ...);
#घोषणा pr_fmt(fmt)	fmt

#घोषणा pr_err(fmt, ...) \
	eम_लिखो(0, verbose, pr_fmt(fmt), ##__VA_ARGS__)

#घोषणा pr_info(fmt, ...) \
	eम_लिखो(1, verbose, pr_fmt(fmt), ##__VA_ARGS__)

#घोषणा pr_debug(fmt, ...) \
	eम_लिखो(2, verbose, pr_fmt(fmt), ##__VA_ARGS__)

#अगर_अघोषित roundup
#घोषणा roundup(x, y) (                                \
अणु                                                      \
        स्थिर typeof(y) __y = y;                       \
        (((x) + (__y - 1)) / __y) * __y;               \
पूर्ण                                                      \
)
#पूर्ण_अगर

#पूर्ण_अगर
