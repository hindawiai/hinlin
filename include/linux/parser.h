<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * linux/include/linux/parser.h
 *
 * Header क्रम lib/parser.c
 * Intended use of these functions is parsing fileप्रणाली argument lists,
 * but could potentially be used anywhere अन्यथा that simple option=arg
 * parsing is required.
 */
#अगर_अघोषित _LINUX_PARSER_H
#घोषणा _LINUX_PARSER_H

/* associates an पूर्णांकeger क्रमागतerator with a pattern string. */
काष्ठा match_token अणु
	पूर्णांक token;
	स्थिर अक्षर *pattern;
पूर्ण;

प्रकार काष्ठा match_token match_table_t[];

/* Maximum number of arguments that match_token will find in a pattern */
क्रमागत अणुMAX_OPT_ARGS = 3पूर्ण;

/* Describe the location within a string of a substring */
प्रकार काष्ठा अणु
	अक्षर *from;
	अक्षर *to;
पूर्ण substring_t;

पूर्णांक match_token(अक्षर *, स्थिर match_table_t table, substring_t args[]);
पूर्णांक match_पूर्णांक(substring_t *, पूर्णांक *result);
पूर्णांक match_uपूर्णांक(substring_t *s, अचिन्हित पूर्णांक *result);
पूर्णांक match_u64(substring_t *, u64 *result);
पूर्णांक match_octal(substring_t *, पूर्णांक *result);
पूर्णांक match_hex(substring_t *, पूर्णांक *result);
bool match_wildcard(स्थिर अक्षर *pattern, स्थिर अक्षर *str);
माप_प्रकार match_strlcpy(अक्षर *, स्थिर substring_t *, माप_प्रकार);
अक्षर *match_strdup(स्थिर substring_t *);

#पूर्ण_अगर /* _LINUX_PARSER_H */
