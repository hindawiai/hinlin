<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#समावेश "string2.h"
#समावेश <linux/kernel.h>
#समावेश <linux/माला.स>
#समावेश <मानककोष.स>

#समावेश <linux/प्रकार.स>

स्थिर अक्षर *graph_करोtted_line =
	"---------------------------------------------------------------------"
	"---------------------------------------------------------------------"
	"---------------------------------------------------------------------";
स्थिर अक्षर *करोts =
	"....................................................................."
	"....................................................................."
	".....................................................................";

#घोषणा K 1024LL
/*
 * perf_म_से_दl()
 * Parse (\d+)(b|B|kb|KB|mb|MB|gb|GB|tb|TB) (e.g. "256MB")
 * and वापस its numeric value
 */
s64 perf_म_से_दl(स्थिर अक्षर *str)
अणु
	s64 length;
	अक्षर *p;
	अक्षर c;

	अगर (!है_अंक(str[0]))
		जाओ out_err;

	length = म_से_दीर्घl(str, &p, 10);
	चयन (c = *p++) अणु
		हाल 'b': case 'B':
			अगर (*p)
				जाओ out_err;

			__fallthrough;
		हाल '\0':
			वापस length;
		शेष:
			जाओ out_err;
		/* two-letter suffices */
		हाल 'k': case 'K':
			length <<= 10;
			अवरोध;
		हाल 'm': case 'M':
			length <<= 20;
			अवरोध;
		हाल 'g': case 'G':
			length <<= 30;
			अवरोध;
		हाल 't': case 'T':
			length <<= 40;
			अवरोध;
	पूर्ण
	/* we want the हालs to match */
	अगर (है_छोटा(c)) अणु
		अगर (म_भेद(p, "b") != 0)
			जाओ out_err;
	पूर्ण अन्यथा अणु
		अगर (म_भेद(p, "B") != 0)
			जाओ out_err;
	पूर्ण
	वापस length;

out_err:
	वापस -1;
पूर्ण

/* Character class matching */
अटल bool __match_अक्षरclass(स्थिर अक्षर *pat, अक्षर c, स्थिर अक्षर **npat)
अणु
	bool complement = false, ret = true;

	अगर (*pat == '!') अणु
		complement = true;
		pat++;
	पूर्ण
	अगर (*pat++ == c)	/* First अक्षरacter is special */
		जाओ end;

	जबतक (*pat && *pat != ']') अणु	/* Matching */
		अगर (*pat == '-' && *(pat + 1) != ']') अणु	/* Range */
			अगर (*(pat - 1) <= c && c <= *(pat + 1))
				जाओ end;
			अगर (*(pat - 1) > *(pat + 1))
				जाओ error;
			pat += 2;
		पूर्ण अन्यथा अगर (*pat++ == c)
			जाओ end;
	पूर्ण
	अगर (!*pat)
		जाओ error;
	ret = false;

end:
	जबतक (*pat && *pat != ']')	/* Searching closing */
		pat++;
	अगर (!*pat)
		जाओ error;
	*npat = pat + 1;
	वापस complement ? !ret : ret;

error:
	वापस false;
पूर्ण

/* Glob/lazy pattern matching */
अटल bool __match_glob(स्थिर अक्षर *str, स्थिर अक्षर *pat, bool ignore_space,
			bool हाल_ins)
अणु
	जबतक (*str && *pat && *pat != '*') अणु
		अगर (ignore_space) अणु
			/* Ignore spaces क्रम lazy matching */
			अगर (है_खाली(*str)) अणु
				str++;
				जारी;
			पूर्ण
			अगर (है_खाली(*pat)) अणु
				pat++;
				जारी;
			पूर्ण
		पूर्ण
		अगर (*pat == '?') अणु	/* Matches any single अक्षरacter */
			str++;
			pat++;
			जारी;
		पूर्ण अन्यथा अगर (*pat == '[')	/* Character classes/Ranges */
			अगर (__match_अक्षरclass(pat + 1, *str, &pat)) अणु
				str++;
				जारी;
			पूर्ण अन्यथा
				वापस false;
		अन्यथा अगर (*pat == '\\') /* Escaped अक्षर match as normal अक्षर */
			pat++;
		अगर (हाल_ins) अणु
			अगर (छोटे(*str) != छोटे(*pat))
				वापस false;
		पूर्ण अन्यथा अगर (*str != *pat)
			वापस false;
		str++;
		pat++;
	पूर्ण
	/* Check wild card */
	अगर (*pat == '*') अणु
		जबतक (*pat == '*')
			pat++;
		अगर (!*pat)	/* Tail wild card matches all */
			वापस true;
		जबतक (*str)
			अगर (__match_glob(str++, pat, ignore_space, हाल_ins))
				वापस true;
	पूर्ण
	वापस !*str && !*pat;
पूर्ण

/**
 * strglobmatch - glob expression pattern matching
 * @str: the target string to match
 * @pat: the pattern string to match
 *
 * This वापसs true अगर the @str matches @pat. @pat can includes wildcards
 * ('*','?') and अक्षरacter classes ([CHARS], complementation and ranges are
 * also supported). Also, this supports escape अक्षरacter ('\') to use special
 * अक्षरacters as normal अक्षरacter.
 *
 * Note: अगर @pat syntax is broken, this always वापसs false.
 */
bool strglobmatch(स्थिर अक्षर *str, स्थिर अक्षर *pat)
अणु
	वापस __match_glob(str, pat, false, false);
पूर्ण

bool strglobmatch_noहाल(स्थिर अक्षर *str, स्थिर अक्षर *pat)
अणु
	वापस __match_glob(str, pat, false, true);
पूर्ण

/**
 * strlazymatch - matching pattern strings lazily with glob pattern
 * @str: the target string to match
 * @pat: the pattern string to match
 *
 * This is similar to strglobmatch, except this ignores spaces in
 * the target string.
 */
bool strlazymatch(स्थिर अक्षर *str, स्थिर अक्षर *pat)
अणु
	वापस __match_glob(str, pat, true, false);
पूर्ण

/**
 * strtailcmp - Compare the tail of two strings
 * @s1: 1st string to be compared
 * @s2: 2nd string to be compared
 *
 * Return 0 अगर whole of either string is same as another's tail part.
 */
पूर्णांक strtailcmp(स्थिर अक्षर *s1, स्थिर अक्षर *s2)
अणु
	पूर्णांक i1 = म_माप(s1);
	पूर्णांक i2 = म_माप(s2);
	जबतक (--i1 >= 0 && --i2 >= 0) अणु
		अगर (s1[i1] != s2[i2])
			वापस s1[i1] - s2[i2];
	पूर्ण
	वापस 0;
पूर्ण

अक्षर *aप्र_लिखो_expr_inout_पूर्णांकs(स्थिर अक्षर *var, bool in, माप_प्रकार nपूर्णांकs, पूर्णांक *पूर्णांकs)
अणु
	/*
	 * FIXME: replace this with an expression using log10() when we
	 * find a suitable implementation, maybe the one in the dvb drivers...
	 *
	 * "%s == %d || " = log10(MAXINT) * 2 + 8 अक्षरs क्रम the चालकs
	 */
	माप_प्रकार size = nपूर्णांकs * 28 + 1; /* \0 */
	माप_प्रकार i, prपूर्णांकed = 0;
	अक्षर *expr = दो_स्मृति(size);

	अगर (expr) अणु
		स्थिर अक्षर *or_and = "||", *eq_neq = "==";
		अक्षर *e = expr;

		अगर (!in) अणु
			or_and = "&&";
			eq_neq = "!=";
		पूर्ण

		क्रम (i = 0; i < nपूर्णांकs; ++i) अणु
			अगर (prपूर्णांकed == size)
				जाओ out_err_overflow;

			अगर (i > 0)
				prपूर्णांकed += scnम_लिखो(e + prपूर्णांकed, size - prपूर्णांकed, " %s ", or_and);
			prपूर्णांकed += scnम_लिखो(e + prपूर्णांकed, size - prपूर्णांकed,
					     "%s %s %d", var, eq_neq, पूर्णांकs[i]);
		पूर्ण
	पूर्ण

	वापस expr;

out_err_overflow:
	मुक्त(expr);
	वापस शून्य;
पूर्ण

/* Like strpbrk(), but not अवरोध अगर it is right after a backslash (escaped) */
अक्षर *strpbrk_esc(अक्षर *str, स्थिर अक्षर *stopset)
अणु
	अक्षर *ptr;

	करो अणु
		ptr = strpbrk(str, stopset);
		अगर (ptr == str ||
		    (ptr == str + 1 && *(ptr - 1) != '\\'))
			अवरोध;
		str = ptr + 1;
	पूर्ण जबतक (ptr && *(ptr - 1) == '\\' && *(ptr - 2) != '\\');

	वापस ptr;
पूर्ण

/* Like strdup, but करो not copy a single backslash */
अक्षर *strdup_esc(स्थिर अक्षर *str)
अणु
	अक्षर *s, *d, *p, *ret = strdup(str);

	अगर (!ret)
		वापस शून्य;

	d = म_अक्षर(ret, '\\');
	अगर (!d)
		वापस ret;

	s = d + 1;
	करो अणु
		अगर (*s == '\0') अणु
			*d = '\0';
			अवरोध;
		पूर्ण
		p = म_अक्षर(s + 1, '\\');
		अगर (p) अणु
			स_हटाओ(d, s, p - s);
			d += p - s;
			s = p + 1;
		पूर्ण अन्यथा
			स_हटाओ(d, s, म_माप(s) + 1);
	पूर्ण जबतक (p);

	वापस ret;
पूर्ण

अचिन्हित पूर्णांक hex(अक्षर c)
अणु
	अगर (c >= '0' && c <= '9')
		वापस c - '0';
	अगर (c >= 'a' && c <= 'f')
		वापस c - 'a' + 10;
	वापस c - 'A' + 10;
पूर्ण
