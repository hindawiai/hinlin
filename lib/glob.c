<शैली गुरु>
#समावेश <linux/module.h>
#समावेश <linux/glob.h>

/*
 * The only reason this code can be compiled as a module is because the
 * ATA code that depends on it can be as well.  In practice, they're
 * both usually compiled in and the module overhead goes away.
 */
MODULE_DESCRIPTION("glob(7) matching");
MODULE_LICENSE("Dual MIT/GPL");

/**
 * glob_match - Shell-style pattern matching, like !fnmatch(pat, str, 0)
 * @pat: Shell-style pattern to match, e.g. "*.[ch]".
 * @str: String to match.  The pattern must match the entire string.
 *
 * Perक्रमm shell-style glob matching, वापसing true (1) अगर the match
 * succeeds, or false (0) अगर it fails.  Equivalent to !fnmatch(@pat, @str, 0).
 *
 * Pattern metaअक्षरacters are ?, *, [ and \.
 * (And, inside अक्षरacter classes, !, - and ].)
 *
 * This is small and simple implementation पूर्णांकended क्रम device blacklists
 * where a string is matched against a number of patterns.  Thus, it
 * करोes not preprocess the patterns.  It is non-recursive, and run-समय
 * is at most quadratic: म_माप(@str)*म_माप(@pat).
 *
 * An example of the worst हाल is glob_match("*aaaaa", "aaaaaaaaaa");
 * it takes 6 passes over the pattern beक्रमe matching the string.
 *
 * Like !fnmatch(@pat, @str, 0) and unlike the shell, this करोes NOT
 * treat / or leading . specially; it isn't actually used क्रम pathnames.
 *
 * Note that according to glob(7) (and unlike bash), अक्षरacter classes
 * are complemented by a leading !; this करोes not support the regex-style
 * [^a-z] syntax.
 *
 * An खोलोing bracket without a matching बंद is matched literally.
 */
bool __pure glob_match(अक्षर स्थिर *pat, अक्षर स्थिर *str)
अणु
	/*
	 * Backtrack to previous * on mismatch and retry starting one
	 * अक्षरacter later in the string.  Because * matches all अक्षरacters
	 * (no exception क्रम /), it can be easily proved that there's
	 * never a need to backtrack multiple levels.
	 */
	अक्षर स्थिर *back_pat = शून्य, *back_str = back_str;

	/*
	 * Loop over each token (अक्षरacter or class) in pat, matching
	 * it against the reमुख्यing unmatched tail of str.  Return false
	 * on mismatch, or true after matching the trailing nul bytes.
	 */
	क्रम (;;) अणु
		अचिन्हित अक्षर c = *str++;
		अचिन्हित अक्षर d = *pat++;

		चयन (d) अणु
		हाल '?':	/* Wildcard: anything but nul */
			अगर (c == '\0')
				वापस false;
			अवरोध;
		हाल '*':	/* Any-length wildcard */
			अगर (*pat == '\0')	/* Optimize trailing * हाल */
				वापस true;
			back_pat = pat;
			back_str = --str;	/* Allow zero-length match */
			अवरोध;
		हाल '[': अणु	/* Character class */
			bool match = false, inverted = (*pat == '!');
			अक्षर स्थिर *class = pat + inverted;
			अचिन्हित अक्षर a = *class++;

			/*
			 * Iterate over each span in the अक्षरacter class.
			 * A span is either a single अक्षरacter a, or a
			 * range a-b.  The first span may begin with ']'.
			 */
			करो अणु
				अचिन्हित अक्षर b = a;

				अगर (a == '\0')	/* Malक्रमmed */
					जाओ literal;

				अगर (class[0] == '-' && class[1] != ']') अणु
					b = class[1];

					अगर (b == '\0')
						जाओ literal;

					class += 2;
					/* Any special action अगर a > b? */
				पूर्ण
				match |= (a <= c && c <= b);
			पूर्ण जबतक ((a = *class++) != ']');

			अगर (match == inverted)
				जाओ backtrack;
			pat = class;
			पूर्ण
			अवरोध;
		हाल '\\':
			d = *pat++;
			fallthrough;
		शेष:	/* Literal अक्षरacter */
literal:
			अगर (c == d) अणु
				अगर (d == '\0')
					वापस true;
				अवरोध;
			पूर्ण
backtrack:
			अगर (c == '\0' || !back_pat)
				वापस false;	/* No poपूर्णांक continuing */
			/* Try again from last *, one अक्षरacter later in str. */
			pat = back_pat;
			str = ++back_str;
			अवरोध;
		पूर्ण
	पूर्ण
पूर्ण
EXPORT_SYMBOL(glob_match);
