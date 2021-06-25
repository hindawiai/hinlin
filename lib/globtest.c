<शैली गुरु>
/*
 * Extracted fronm glob.c
 */

#समावेश <linux/module.h>
#समावेश <linux/moduleparam.h>
#समावेश <linux/glob.h>
#समावेश <linux/prपूर्णांकk.h>

/* Boot with "glob.verbose=1" to show successful tests, too */
अटल bool verbose = false;
module_param(verbose, bool, 0);

काष्ठा glob_test अणु
	अक्षर स्थिर *pat, *str;
	bool expected;
पूर्ण;

अटल bool __pure __init test(अक्षर स्थिर *pat, अक्षर स्थिर *str, bool expected)
अणु
	bool match = glob_match(pat, str);
	bool success = match == expected;

	/* Can't get string literals पूर्णांकo a particular section, so... */
	अटल अक्षर स्थिर msg_error[] __initस्थिर =
		KERN_ERR "glob: \"%s\" vs. \"%s\": %s *** ERROR ***\n";
	अटल अक्षर स्थिर msg_ok[] __initस्थिर =
		KERN_DEBUG "glob: \"%s\" vs. \"%s\": %s OK\n";
	अटल अक्षर स्थिर mismatch[] __initस्थिर = "mismatch";
	अक्षर स्थिर *message;

	अगर (!success)
		message = msg_error;
	अन्यथा अगर (verbose)
		message = msg_ok;
	अन्यथा
		वापस success;

	prपूर्णांकk(message, pat, str, mismatch + 3*match);
	वापस success;
पूर्ण

/*
 * The tests are all jammed together in one array to make it simpler
 * to place that array in the .init.rodata section.  The obvious
 * "array of structures containing char *" has no way to क्रमce the
 * poपूर्णांकed-to strings to be in a particular section.
 *
 * Anyway, a test consists of:
 * 1. Expected glob_match result: '1' or '0'.
 * 2. Pattern to match: null-terminated string
 * 3. String to match against: null-terminated string
 *
 * The list of tests is terminated with a final '\0' instead of
 * a glob_match result अक्षरacter.
 */
अटल अक्षर स्थिर glob_tests[] __initस्थिर =
	/* Some basic tests */
	"1" "a\0" "a\0"
	"0" "a\0" "b\0"
	"0" "a\0" "aa\0"
	"0" "a\0" "\0"
	"1" "\0" "\0"
	"0" "\0" "a\0"
	/* Simple अक्षरacter class tests */
	"1" "[a]\0" "a\0"
	"0" "[a]\0" "b\0"
	"0" "[!a]\0" "a\0"
	"1" "[!a]\0" "b\0"
	"1" "[ab]\0" "a\0"
	"1" "[ab]\0" "b\0"
	"0" "[ab]\0" "c\0"
	"1" "[!ab]\0" "c\0"
	"1" "[a-c]\0" "b\0"
	"0" "[a-c]\0" "d\0"
	/* Corner हालs in अक्षरacter class parsing */
	"1" "[a-c-e-g]\0" "-\0"
	"0" "[a-c-e-g]\0" "d\0"
	"1" "[a-c-e-g]\0" "f\0"
	"1" "[]a-ceg-ik[]\0" "a\0"
	"1" "[]a-ceg-ik[]\0" "]\0"
	"1" "[]a-ceg-ik[]\0" "[\0"
	"1" "[]a-ceg-ik[]\0" "h\0"
	"0" "[]a-ceg-ik[]\0" "f\0"
	"0" "[!]a-ceg-ik[]\0" "h\0"
	"0" "[!]a-ceg-ik[]\0" "]\0"
	"1" "[!]a-ceg-ik[]\0" "f\0"
	/* Simple wild cards */
	"1" "?\0" "a\0"
	"0" "?\0" "aa\0"
	"0" "??\0" "a\0"
	"1" "?x?\0" "axb\0"
	"0" "?x?\0" "abx\0"
	"0" "?x?\0" "xab\0"
	/* Asterisk wild cards (backtracking) */
	"0" "*??\0" "a\0"
	"1" "*??\0" "ab\0"
	"1" "*??\0" "abc\0"
	"1" "*??\0" "abcd\0"
	"0" "??*\0" "a\0"
	"1" "??*\0" "ab\0"
	"1" "??*\0" "abc\0"
	"1" "??*\0" "abcd\0"
	"0" "?*?\0" "a\0"
	"1" "?*?\0" "ab\0"
	"1" "?*?\0" "abc\0"
	"1" "?*?\0" "abcd\0"
	"1" "*b\0" "b\0"
	"1" "*b\0" "ab\0"
	"0" "*b\0" "ba\0"
	"1" "*b\0" "bb\0"
	"1" "*b\0" "abb\0"
	"1" "*b\0" "bab\0"
	"1" "*bc\0" "abbc\0"
	"1" "*bc\0" "bc\0"
	"1" "*bc\0" "bbc\0"
	"1" "*bc\0" "bcbc\0"
	/* Multiple asterisks (complex backtracking) */
	"1" "*ac*\0" "abacadaeafag\0"
	"1" "*ac*ae*ag*\0" "abacadaeafag\0"
	"1" "*a*b*[bc]*[ef]*g*\0" "abacadaeafag\0"
	"0" "*a*b*[ef]*[cd]*g*\0" "abacadaeafag\0"
	"1" "*abcd*\0" "abcabcabcabcdefg\0"
	"1" "*ab*cd*\0" "abcabcabcabcdefg\0"
	"1" "*abcd*abcdef*\0" "abcabcdabcdeabcdefg\0"
	"0" "*abcd*\0" "abcabcabcabcefg\0"
	"0" "*ab*cd*\0" "abcabcabcabcefg\0";

अटल पूर्णांक __init glob_init(व्योम)
अणु
	अचिन्हित successes = 0;
	अचिन्हित n = 0;
	अक्षर स्थिर *p = glob_tests;
	अटल अक्षर स्थिर message[] __initस्थिर =
		KERN_INFO "glob: %u self-tests passed, %u failed\n";

	/*
	 * Tests are jammed together in a string.  The first byte is '1'
	 * or '0' to indicate the expected outcome, or '\0' to indicate the
	 * end of the tests.  Then come two null-terminated strings: the
	 * pattern and the string to match it against.
	 */
	जबतक (*p) अणु
		bool expected = *p++ & 1;
		अक्षर स्थिर *pat = p;

		p += म_माप(p) + 1;
		successes += test(pat, p, expected);
		p += म_माप(p) + 1;
		n++;
	पूर्ण

	n -= successes;
	prपूर्णांकk(message, successes, n);

	/* What's the त्रुटि_सं क्रम "kernel bug detected"?  Guess... */
	वापस n ? -ECANCELED : 0;
पूर्ण

/* We need a dummy निकास function to allow unload */
अटल व्योम __निकास glob_fini(व्योम) अणु पूर्ण

module_init(glob_init);
module_निकास(glob_fini);

MODULE_DESCRIPTION("glob(7) matching tests");
MODULE_LICENSE("Dual MIT/GPL");
