<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (c) 2020 Francis Laniel <laniel_francis@privacyrequired.com>
 *
 * Add tests related to क्रमtअगरied functions in this file.
 */
#समावेश "lkdtm.h"
#समावेश <linux/माला.स>
#समावेश <linux/slab.h>


/*
 * Calls क्रमtअगरied strscpy to test that it वापसs the same result as vanilla
 * strscpy and generate a panic because there is a ग_लिखो overflow (i.e. src
 * length is greater than dst length).
 */
व्योम lkdपंचांग_FORTIFIED_STRSCPY(व्योम)
अणु
	अक्षर *src;
	अक्षर dst[5];

	काष्ठा अणु
		जोड़ अणु
			अक्षर big[10];
			अक्षर src[5];
		पूर्ण;
	पूर्ण weird = अणु .big = "hello!" पूर्ण;
	अक्षर weird_dst[माप(weird.src) + 1];

	src = kstrdup("foobar", GFP_KERNEL);

	अगर (src == शून्य)
		वापस;

	/* Vanilla strscpy वापसs -E2BIG अगर size is 0. */
	अगर (strscpy(dst, src, 0) != -E2BIG)
		pr_warn("FAIL: strscpy() of 0 length did not return -E2BIG\n");

	/* Vanilla strscpy वापसs -E2BIG अगर src is truncated. */
	अगर (strscpy(dst, src, माप(dst)) != -E2BIG)
		pr_warn("FAIL: strscpy() did not return -E2BIG while src is truncated\n");

	/* After above call, dst must contain "foob" because src was truncated. */
	अगर (म_भेदन(dst, "foob", माप(dst)) != 0)
		pr_warn("FAIL: after strscpy() dst does not contain \"foob\" but \"%s\"\n",
			dst);

	/* Shrink src so the strscpy() below succeeds. */
	src[3] = '\0';

	/*
	 * Vanilla strscpy वापसs number of अक्षरacter copied अगर everything goes
	 * well.
	 */
	अगर (strscpy(dst, src, माप(dst)) != 3)
		pr_warn("FAIL: strscpy() did not return 3 while src was copied entirely truncated\n");

	/* After above call, dst must contain "foo" because src was copied. */
	अगर (म_भेदन(dst, "foo", माप(dst)) != 0)
		pr_warn("FAIL: after strscpy() dst does not contain \"foo\" but \"%s\"\n",
			dst);

	/* Test when src is embedded inside a जोड़. */
	strscpy(weird_dst, weird.src, माप(weird_dst));

	अगर (म_भेद(weird_dst, "hello") != 0)
		pr_warn("FAIL: after strscpy() weird_dst does not contain \"hello\" but \"%s\"\n",
			weird_dst);

	/* Restore src to its initial value. */
	src[3] = 'b';

	/*
	 * Use म_माप here so size cannot be known at compile समय and there is
	 * a runसमय ग_लिखो overflow.
	 */
	strscpy(dst, src, म_माप(src));

	pr_warn("FAIL: No overflow in above strscpy()\n");

	kमुक्त(src);
पूर्ण
