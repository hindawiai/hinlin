<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * linux/lib/cmdline.c
 * Helper functions generally used क्रम parsing kernel command line
 * and module options.
 *
 * Code and copyrights come from init/मुख्य.c and arch/i386/kernel/setup.c.
 *
 * GNU Indent क्रमmatting options क्रम this file: -kr -i8 -npsl -pcs
 */

#समावेश <linux/export.h>
#समावेश <linux/kernel.h>
#समावेश <linux/माला.स>
#समावेश <linux/प्रकार.स>

/*
 *	If a hyphen was found in get_option, this will handle the
 *	range of numbers, M-N.  This will expand the range and insert
 *	the values[M, M+1, ..., N] पूर्णांकo the पूर्णांकs array in get_options.
 */

अटल पूर्णांक get_range(अक्षर **str, पूर्णांक *pपूर्णांक, पूर्णांक n)
अणु
	पूर्णांक x, inc_counter, upper_range;

	(*str)++;
	upper_range = simple_म_से_दीर्घ((*str), शून्य, 0);
	inc_counter = upper_range - *pपूर्णांक;
	क्रम (x = *pपूर्णांक; n && x < upper_range; x++, n--)
		*pपूर्णांक++ = x;
	वापस inc_counter;
पूर्ण

/**
 *	get_option - Parse पूर्णांकeger from an option string
 *	@str: option string
 *	@pपूर्णांक: (optional output) पूर्णांकeger value parsed from @str
 *
 *	Read an पूर्णांक from an option string; अगर available accept a subsequent
 *	comma as well.
 *
 *	When @pपूर्णांक is शून्य the function can be used as a validator of
 *	the current option in the string.
 *
 *	Return values:
 *	0 - no पूर्णांक in string
 *	1 - पूर्णांक found, no subsequent comma
 *	2 - पूर्णांक found including a subsequent comma
 *	3 - hyphen found to denote a range
 *
 *	Leading hyphen without पूर्णांकeger is no पूर्णांकeger हाल, but we consume it
 *	क्रम the sake of simplअगरication.
 */

पूर्णांक get_option(अक्षर **str, पूर्णांक *pपूर्णांक)
अणु
	अक्षर *cur = *str;
	पूर्णांक value;

	अगर (!cur || !(*cur))
		वापस 0;
	अगर (*cur == '-')
		value = -simple_म_से_अदीर्घl(++cur, str, 0);
	अन्यथा
		value = simple_म_से_अदीर्घl(cur, str, 0);
	अगर (pपूर्णांक)
		*pपूर्णांक = value;
	अगर (cur == *str)
		वापस 0;
	अगर (**str == ',') अणु
		(*str)++;
		वापस 2;
	पूर्ण
	अगर (**str == '-')
		वापस 3;

	वापस 1;
पूर्ण
EXPORT_SYMBOL(get_option);

/**
 *	get_options - Parse a string पूर्णांकo a list of पूर्णांकegers
 *	@str: String to be parsed
 *	@nपूर्णांकs: size of पूर्णांकeger array
 *	@पूर्णांकs: पूर्णांकeger array (must have room क्रम at least one element)
 *
 *	This function parses a string containing a comma-separated
 *	list of पूर्णांकegers, a hyphen-separated range of _positive_ पूर्णांकegers,
 *	or a combination of both.  The parse halts when the array is
 *	full, or when no more numbers can be retrieved from the
 *	string.
 *
 *	When @nपूर्णांकs is 0, the function just validates the given @str and
 *	वापसs the amount of parseable पूर्णांकegers as described below.
 *
 *	Returns:
 *
 *	The first element is filled by the number of collected पूर्णांकegers
 *	in the range. The rest is what was parsed from the @str.
 *
 *	Return value is the अक्षरacter in the string which caused
 *	the parse to end (typically a null terminator, अगर @str is
 *	completely parseable).
 */

अक्षर *get_options(स्थिर अक्षर *str, पूर्णांक nपूर्णांकs, पूर्णांक *पूर्णांकs)
अणु
	bool validate = (nपूर्णांकs == 0);
	पूर्णांक res, i = 1;

	जबतक (i < nपूर्णांकs || validate) अणु
		पूर्णांक *pपूर्णांक = validate ? पूर्णांकs : पूर्णांकs + i;

		res = get_option((अक्षर **)&str, pपूर्णांक);
		अगर (res == 0)
			अवरोध;
		अगर (res == 3) अणु
			पूर्णांक n = validate ? 0 : nपूर्णांकs - i;
			पूर्णांक range_nums;

			range_nums = get_range((अक्षर **)&str, pपूर्णांक, n);
			अगर (range_nums < 0)
				अवरोध;
			/*
			 * Decrement the result by one to leave out the
			 * last number in the range.  The next iteration
			 * will handle the upper number in the range
			 */
			i += (range_nums - 1);
		पूर्ण
		i++;
		अगर (res == 1)
			अवरोध;
	पूर्ण
	पूर्णांकs[0] = i - 1;
	वापस (अक्षर *)str;
पूर्ण
EXPORT_SYMBOL(get_options);

/**
 *	memparse - parse a string with mem suffixes पूर्णांकo a number
 *	@ptr: Where parse begins
 *	@retptr: (output) Optional poपूर्णांकer to next अक्षर after parse completes
 *
 *	Parses a string पूर्णांकo a number.  The number stored at @ptr is
 *	potentially suffixed with K, M, G, T, P, E.
 */

अचिन्हित दीर्घ दीर्घ memparse(स्थिर अक्षर *ptr, अक्षर **retptr)
अणु
	अक्षर *endptr;	/* local poपूर्णांकer to end of parsed string */

	अचिन्हित दीर्घ दीर्घ ret = simple_म_से_अदीर्घl(ptr, &endptr, 0);

	चयन (*endptr) अणु
	हाल 'E':
	हाल 'e':
		ret <<= 10;
		fallthrough;
	हाल 'P':
	हाल 'p':
		ret <<= 10;
		fallthrough;
	हाल 'T':
	हाल 't':
		ret <<= 10;
		fallthrough;
	हाल 'G':
	हाल 'g':
		ret <<= 10;
		fallthrough;
	हाल 'M':
	हाल 'm':
		ret <<= 10;
		fallthrough;
	हाल 'K':
	हाल 'k':
		ret <<= 10;
		endptr++;
		fallthrough;
	शेष:
		अवरोध;
	पूर्ण

	अगर (retptr)
		*retptr = endptr;

	वापस ret;
पूर्ण
EXPORT_SYMBOL(memparse);

/**
 *	parse_option_str - Parse a string and check an option is set or not
 *	@str: String to be parsed
 *	@option: option name
 *
 *	This function parses a string containing a comma-separated list of
 *	strings like a=b,c.
 *
 *	Return true अगर there's such option in the string, or वापस false.
 */
bool parse_option_str(स्थिर अक्षर *str, स्थिर अक्षर *option)
अणु
	जबतक (*str) अणु
		अगर (!म_भेदन(str, option, म_माप(option))) अणु
			str += म_माप(option);
			अगर (!*str || *str == ',')
				वापस true;
		पूर्ण

		जबतक (*str && *str != ',')
			str++;

		अगर (*str == ',')
			str++;
	पूर्ण

	वापस false;
पूर्ण

/*
 * Parse a string to get a param value pair.
 * You can use " around spaces, but can't escape ".
 * Hyphens and underscores equivalent in parameter names.
 */
अक्षर *next_arg(अक्षर *args, अक्षर **param, अक्षर **val)
अणु
	अचिन्हित पूर्णांक i, equals = 0;
	पूर्णांक in_quote = 0, quoted = 0;

	अगर (*args == '"') अणु
		args++;
		in_quote = 1;
		quoted = 1;
	पूर्ण

	क्रम (i = 0; args[i]; i++) अणु
		अगर (है_खाली(args[i]) && !in_quote)
			अवरोध;
		अगर (equals == 0) अणु
			अगर (args[i] == '=')
				equals = i;
		पूर्ण
		अगर (args[i] == '"')
			in_quote = !in_quote;
	पूर्ण

	*param = args;
	अगर (!equals)
		*val = शून्य;
	अन्यथा अणु
		args[equals] = '\0';
		*val = args + equals + 1;

		/* Don't include quotes in value. */
		अगर (**val == '"') अणु
			(*val)++;
			अगर (args[i-1] == '"')
				args[i-1] = '\0';
		पूर्ण
	पूर्ण
	अगर (quoted && args[i-1] == '"')
		args[i-1] = '\0';

	अगर (args[i]) अणु
		args[i] = '\0';
		args += i + 1;
	पूर्ण अन्यथा
		args += i;

	/* Chew up trailing spaces. */
	वापस skip_spaces(args);
पूर्ण
EXPORT_SYMBOL(next_arg);
