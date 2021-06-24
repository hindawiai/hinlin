<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * lib/parser.c - simple parser क्रम mount, etc. options.
 */

#समावेश <linux/प्रकार.स>
#समावेश <linux/types.h>
#समावेश <linux/export.h>
#समावेश <linux/parser.h>
#समावेश <linux/slab.h>
#समावेश <linux/माला.स>

/**
 * match_one - Determines अगर a string matches a simple pattern
 * @s: the string to examine क्रम presence of the pattern
 * @p: the string containing the pattern
 * @args: array of %MAX_OPT_ARGS &substring_t elements. Used to वापस match
 * locations.
 *
 * Description: Determines अगर the pattern @p is present in string @s. Can only
 * match extremely simple token=arg style patterns. If the pattern is found,
 * the location(s) of the arguments will be वापसed in the @args array.
 */
अटल पूर्णांक match_one(अक्षर *s, स्थिर अक्षर *p, substring_t args[])
अणु
	अक्षर *meta;
	पूर्णांक argc = 0;

	अगर (!p)
		वापस 1;

	जबतक(1) अणु
		पूर्णांक len = -1;
		meta = म_अक्षर(p, '%');
		अगर (!meta)
			वापस म_भेद(p, s) == 0;

		अगर (म_भेदन(p, s, meta-p))
			वापस 0;

		s += meta - p;
		p = meta + 1;

		अगर (है_अंक(*p))
			len = simple_म_से_अदीर्घ(p, (अक्षर **) &p, 10);
		अन्यथा अगर (*p == '%') अणु
			अगर (*s++ != '%')
				वापस 0;
			p++;
			जारी;
		पूर्ण

		अगर (argc >= MAX_OPT_ARGS)
			वापस 0;

		args[argc].from = s;
		चयन (*p++) अणु
		हाल 's': अणु
			माप_प्रकार str_len = म_माप(s);

			अगर (str_len == 0)
				वापस 0;
			अगर (len == -1 || len > str_len)
				len = str_len;
			args[argc].to = s + len;
			अवरोध;
		पूर्ण
		हाल 'd':
			simple_म_से_दीर्घ(s, &args[argc].to, 0);
			जाओ num;
		हाल 'u':
			simple_म_से_अदीर्घ(s, &args[argc].to, 0);
			जाओ num;
		हाल 'o':
			simple_म_से_अदीर्घ(s, &args[argc].to, 8);
			जाओ num;
		हाल 'x':
			simple_म_से_अदीर्घ(s, &args[argc].to, 16);
		num:
			अगर (args[argc].to == args[argc].from)
				वापस 0;
			अवरोध;
		शेष:
			वापस 0;
		पूर्ण
		s = args[argc].to;
		argc++;
	पूर्ण
पूर्ण

/**
 * match_token - Find a token (and optional args) in a string
 * @s: the string to examine क्रम token/argument pairs
 * @table: match_table_t describing the set of allowed option tokens and the
 * arguments that may be associated with them. Must be terminated with a
 * &काष्ठा match_token whose pattern is set to the शून्य poपूर्णांकer.
 * @args: array of %MAX_OPT_ARGS &substring_t elements. Used to वापस match
 * locations.
 *
 * Description: Detects which अगर any of a set of token strings has been passed
 * to it. Tokens can include up to %MAX_OPT_ARGS instances of basic c-style
 * क्रमmat identअगरiers which will be taken पूर्णांकo account when matching the
 * tokens, and whose locations will be वापसed in the @args array.
 */
पूर्णांक match_token(अक्षर *s, स्थिर match_table_t table, substring_t args[])
अणु
	स्थिर काष्ठा match_token *p;

	क्रम (p = table; !match_one(s, p->pattern, args) ; p++)
		;

	वापस p->token;
पूर्ण
EXPORT_SYMBOL(match_token);

/**
 * match_number - scan a number in the given base from a substring_t
 * @s: substring to be scanned
 * @result: resulting पूर्णांकeger on success
 * @base: base to use when converting string
 *
 * Description: Given a &substring_t and a base, attempts to parse the substring
 * as a number in that base.
 *
 * Return: On success, sets @result to the पूर्णांकeger represented by the
 * string and वापसs 0. Returns -ENOMEM, -EINVAL, or -दुस्फल on failure.
 */
अटल पूर्णांक match_number(substring_t *s, पूर्णांक *result, पूर्णांक base)
अणु
	अक्षर *endp;
	अक्षर *buf;
	पूर्णांक ret;
	दीर्घ val;

	buf = match_strdup(s);
	अगर (!buf)
		वापस -ENOMEM;

	ret = 0;
	val = simple_म_से_दीर्घ(buf, &endp, base);
	अगर (endp == buf)
		ret = -EINVAL;
	अन्यथा अगर (val < (दीर्घ)पूर्णांक_न्यून || val > (दीर्घ)पूर्णांक_उच्च)
		ret = -दुस्फल;
	अन्यथा
		*result = (पूर्णांक) val;
	kमुक्त(buf);
	वापस ret;
पूर्ण

/**
 * match_u64पूर्णांक - scan a number in the given base from a substring_t
 * @s: substring to be scanned
 * @result: resulting u64 on success
 * @base: base to use when converting string
 *
 * Description: Given a &substring_t and a base, attempts to parse the substring
 * as a number in that base.
 *
 * Return: On success, sets @result to the पूर्णांकeger represented by the
 * string and वापसs 0. Returns -ENOMEM, -EINVAL, or -दुस्फल on failure.
 */
अटल पूर्णांक match_u64पूर्णांक(substring_t *s, u64 *result, पूर्णांक base)
अणु
	अक्षर *buf;
	पूर्णांक ret;
	u64 val;

	buf = match_strdup(s);
	अगर (!buf)
		वापस -ENOMEM;

	ret = kम_से_अदीर्घl(buf, base, &val);
	अगर (!ret)
		*result = val;
	kमुक्त(buf);
	वापस ret;
पूर्ण

/**
 * match_पूर्णांक - scan a decimal representation of an पूर्णांकeger from a substring_t
 * @s: substring_t to be scanned
 * @result: resulting पूर्णांकeger on success
 *
 * Description: Attempts to parse the &substring_t @s as a decimal पूर्णांकeger.
 *
 * Return: On success, sets @result to the पूर्णांकeger represented by the string
 * and वापसs 0. Returns -ENOMEM, -EINVAL, or -दुस्फल on failure.
 */
पूर्णांक match_पूर्णांक(substring_t *s, पूर्णांक *result)
अणु
	वापस match_number(s, result, 0);
पूर्ण
EXPORT_SYMBOL(match_पूर्णांक);

/**
 * match_uपूर्णांक - scan a decimal representation of an पूर्णांकeger from a substring_t
 * @s: substring_t to be scanned
 * @result: resulting पूर्णांकeger on success
 *
 * Description: Attempts to parse the &substring_t @s as a decimal पूर्णांकeger.
 *
 * Return: On success, sets @result to the पूर्णांकeger represented by the string
 * and वापसs 0. Returns -ENOMEM, -EINVAL, or -दुस्फल on failure.
 */
पूर्णांक match_uपूर्णांक(substring_t *s, अचिन्हित पूर्णांक *result)
अणु
	पूर्णांक err = -ENOMEM;
	अक्षर *buf = match_strdup(s);

	अगर (buf) अणु
		err = kstrtouपूर्णांक(buf, 10, result);
		kमुक्त(buf);
	पूर्ण
	वापस err;
पूर्ण
EXPORT_SYMBOL(match_uपूर्णांक);

/**
 * match_u64 - scan a decimal representation of a u64 from
 *                  a substring_t
 * @s: substring_t to be scanned
 * @result: resulting अचिन्हित दीर्घ दीर्घ on success
 *
 * Description: Attempts to parse the &substring_t @s as a दीर्घ decimal
 * पूर्णांकeger.
 *
 * Return: On success, sets @result to the पूर्णांकeger represented by the string
 * and वापसs 0. Returns -ENOMEM, -EINVAL, or -दुस्फल on failure.
 */
पूर्णांक match_u64(substring_t *s, u64 *result)
अणु
	वापस match_u64पूर्णांक(s, result, 0);
पूर्ण
EXPORT_SYMBOL(match_u64);

/**
 * match_octal - scan an octal representation of an पूर्णांकeger from a substring_t
 * @s: substring_t to be scanned
 * @result: resulting पूर्णांकeger on success
 *
 * Description: Attempts to parse the &substring_t @s as an octal पूर्णांकeger.
 *
 * Return: On success, sets @result to the पूर्णांकeger represented by the string
 * and वापसs 0. Returns -ENOMEM, -EINVAL, or -दुस्फल on failure.
 */
पूर्णांक match_octal(substring_t *s, पूर्णांक *result)
अणु
	वापस match_number(s, result, 8);
पूर्ण
EXPORT_SYMBOL(match_octal);

/**
 * match_hex - scan a hex representation of an पूर्णांकeger from a substring_t
 * @s: substring_t to be scanned
 * @result: resulting पूर्णांकeger on success
 *
 * Description: Attempts to parse the &substring_t @s as a hexadecimal पूर्णांकeger.
 *
 * Return: On success, sets @result to the पूर्णांकeger represented by the string
 * and वापसs 0. Returns -ENOMEM, -EINVAL, or -दुस्फल on failure.
 */
पूर्णांक match_hex(substring_t *s, पूर्णांक *result)
अणु
	वापस match_number(s, result, 16);
पूर्ण
EXPORT_SYMBOL(match_hex);

/**
 * match_wildcard - parse अगर a string matches given wildcard pattern
 * @pattern: wildcard pattern
 * @str: the string to be parsed
 *
 * Description: Parse the string @str to check अगर matches wildcard
 * pattern @pattern. The pattern may contain two types of wildcards:
 *   '*' - matches zero or more अक्षरacters
 *   '?' - matches one अक्षरacter
 *
 * Return: If the @str matches the @pattern, वापस true, अन्यथा वापस false.
 */
bool match_wildcard(स्थिर अक्षर *pattern, स्थिर अक्षर *str)
अणु
	स्थिर अक्षर *s = str;
	स्थिर अक्षर *p = pattern;
	bool star = false;

	जबतक (*s) अणु
		चयन (*p) अणु
		हाल '?':
			s++;
			p++;
			अवरोध;
		हाल '*':
			star = true;
			str = s;
			अगर (!*++p)
				वापस true;
			pattern = p;
			अवरोध;
		शेष:
			अगर (*s == *p) अणु
				s++;
				p++;
			पूर्ण अन्यथा अणु
				अगर (!star)
					वापस false;
				str++;
				s = str;
				p = pattern;
			पूर्ण
			अवरोध;
		पूर्ण
	पूर्ण

	अगर (*p == '*')
		++p;
	वापस !*p;
पूर्ण
EXPORT_SYMBOL(match_wildcard);

/**
 * match_strlcpy - Copy the अक्षरacters from a substring_t to a sized buffer
 * @dest: where to copy to
 * @src: &substring_t to copy
 * @size: size of destination buffer
 *
 * Description: Copy the अक्षरacters in &substring_t @src to the
 * c-style string @dest.  Copy no more than @size - 1 अक्षरacters, plus
 * the terminating NUL.
 *
 * Return: length of @src.
 */
माप_प्रकार match_strlcpy(अक्षर *dest, स्थिर substring_t *src, माप_प्रकार size)
अणु
	माप_प्रकार ret = src->to - src->from;

	अगर (size) अणु
		माप_प्रकार len = ret >= size ? size - 1 : ret;
		स_नकल(dest, src->from, len);
		dest[len] = '\0';
	पूर्ण
	वापस ret;
पूर्ण
EXPORT_SYMBOL(match_strlcpy);

/**
 * match_strdup - allocate a new string with the contents of a substring_t
 * @s: &substring_t to copy
 *
 * Description: Allocates and वापसs a string filled with the contents of
 * the &substring_t @s. The caller is responsible क्रम मुक्तing the वापसed
 * string with kमुक्त().
 *
 * Return: the address of the newly allocated NUL-terminated string or
 * %शून्य on error.
 */
अक्षर *match_strdup(स्थिर substring_t *s)
अणु
	वापस kmemdup_nul(s->from, s->to - s->from, GFP_KERNEL);
पूर्ण
EXPORT_SYMBOL(match_strdup);
