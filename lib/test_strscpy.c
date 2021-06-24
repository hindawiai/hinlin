<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#समावेश <linux/माला.स>

#समावेश "../tools/testing/selftests/kselftest_module.h"

/*
 * Kernel module क्रम testing 'strscpy' family of functions.
 */

KSTM_MODULE_GLOBALS();

/*
 * tc() - Run a specअगरic test हाल.
 * @src: Source string, argument to strscpy_pad()
 * @count: Size of destination buffer, argument to strscpy_pad()
 * @expected: Expected वापस value from call to strscpy_pad()
 * @terminator: 1 अगर there should be a terminating null byte 0 otherwise.
 * @अक्षरs: Number of अक्षरacters from the src string expected to be
 *         written to the dst buffer.
 * @pad: Number of pad अक्षरacters expected (in the tail of dst buffer).
 *       (@pad करोes not include the null terminator byte.)
 *
 * Calls strscpy_pad() and verअगरies the वापस value and state of the
 * destination buffer after the call वापसs.
 */
अटल पूर्णांक __init tc(अक्षर *src, पूर्णांक count, पूर्णांक expected,
		     पूर्णांक अक्षरs, पूर्णांक terminator, पूर्णांक pad)
अणु
	पूर्णांक nr_bytes_poison;
	पूर्णांक max_expected;
	पूर्णांक max_count;
	पूर्णांक written;
	अक्षर buf[6];
	पूर्णांक index, i;
	स्थिर अक्षर POISON = 'z';

	total_tests++;

	अगर (!src) अणु
		pr_err("null source string not supported\n");
		वापस -1;
	पूर्ण

	स_रखो(buf, POISON, माप(buf));
	/* Future proofing test suite, validate args */
	max_count = माप(buf) - 2; /* Space क्रम null and to verअगरy overflow */
	max_expected = count - 1;    /* Space क्रम the null */
	अगर (count > max_count) अणु
		pr_err("count (%d) is too big (%d) ... aborting", count, max_count);
		वापस -1;
	पूर्ण
	अगर (expected > max_expected) अणु
		pr_warn("expected (%d) is bigger than can possibly be returned (%d)",
			expected, max_expected);
	पूर्ण

	written = strscpy_pad(buf, src, count);
	अगर ((written) != (expected)) अणु
		pr_err("%d != %d (written, expected)\n", written, expected);
		जाओ fail;
	पूर्ण

	अगर (count && written == -E2BIG) अणु
		अगर (म_भेदन(buf, src, count - 1) != 0) अणु
			pr_err("buffer state invalid for -E2BIG\n");
			जाओ fail;
		पूर्ण
		अगर (buf[count - 1] != '\0') अणु
			pr_err("too big string is not null terminated correctly\n");
			जाओ fail;
		पूर्ण
	पूर्ण

	क्रम (i = 0; i < अक्षरs; i++) अणु
		अगर (buf[i] != src[i]) अणु
			pr_err("buf[i]==%c != src[i]==%c\n", buf[i], src[i]);
			जाओ fail;
		पूर्ण
	पूर्ण

	अगर (terminator) अणु
		अगर (buf[count - 1] != '\0') अणु
			pr_err("string is not null terminated correctly\n");
			जाओ fail;
		पूर्ण
	पूर्ण

	क्रम (i = 0; i < pad; i++) अणु
		index = अक्षरs + terminator + i;
		अगर (buf[index] != '\0') अणु
			pr_err("padding missing at index: %d\n", i);
			जाओ fail;
		पूर्ण
	पूर्ण

	nr_bytes_poison = माप(buf) - अक्षरs - terminator - pad;
	क्रम (i = 0; i < nr_bytes_poison; i++) अणु
		index = माप(buf) - 1 - i; /* Check from the end back */
		अगर (buf[index] != POISON) अणु
			pr_err("poison value missing at index: %d\n", i);
			जाओ fail;
		पूर्ण
	पूर्ण

	वापस 0;
fail:
	failed_tests++;
	वापस -1;
पूर्ण

अटल व्योम __init selftest(व्योम)
अणु
	/*
	 * tc() uses a destination buffer of size 6 and needs at
	 * least 2 अक्षरacters spare (one क्रम null and one to check क्रम
	 * overflow).  This means we should only call tc() with
	 * strings up to a maximum of 4 अक्षरacters दीर्घ and 'count'
	 * should not exceed 4.  To test with दीर्घer strings increase
	 * the buffer size in tc().
	 */

	/* tc(src, count, expected, अक्षरs, terminator, pad) */
	KSTM_CHECK_ZERO(tc("a", 0, -E2BIG, 0, 0, 0));
	KSTM_CHECK_ZERO(tc("", 0, -E2BIG, 0, 0, 0));

	KSTM_CHECK_ZERO(tc("a", 1, -E2BIG, 0, 1, 0));
	KSTM_CHECK_ZERO(tc("", 1, 0, 0, 1, 0));

	KSTM_CHECK_ZERO(tc("ab", 2, -E2BIG, 1, 1, 0));
	KSTM_CHECK_ZERO(tc("a", 2, 1, 1, 1, 0));
	KSTM_CHECK_ZERO(tc("", 2, 0, 0, 1, 1));

	KSTM_CHECK_ZERO(tc("abc", 3, -E2BIG, 2, 1, 0));
	KSTM_CHECK_ZERO(tc("ab", 3, 2, 2, 1, 0));
	KSTM_CHECK_ZERO(tc("a", 3, 1, 1, 1, 1));
	KSTM_CHECK_ZERO(tc("", 3, 0, 0, 1, 2));

	KSTM_CHECK_ZERO(tc("abcd", 4, -E2BIG, 3, 1, 0));
	KSTM_CHECK_ZERO(tc("abc", 4, 3, 3, 1, 0));
	KSTM_CHECK_ZERO(tc("ab", 4, 2, 2, 1, 1));
	KSTM_CHECK_ZERO(tc("a", 4, 1, 1, 1, 2));
	KSTM_CHECK_ZERO(tc("", 4, 0, 0, 1, 3));
पूर्ण

KSTM_MODULE_LOADERS(test_strscpy);
MODULE_AUTHOR("Tobin C. Harding <tobin@kernel.org>");
MODULE_LICENSE("GPL");
