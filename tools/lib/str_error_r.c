<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#अघोषित _GNU_SOURCE
#समावेश <माला.स>
#समावेश <मानकपन.स>
#समावेश <linux/माला.स>

/*
 * The tools so far have been using the म_त्रुटि_r() GNU variant, that वापसs
 * a string, be it the buffer passed or something अन्यथा.
 *
 * But that, besides being tricky in हालs where we expect that the function
 * using म_त्रुटि_r() वापसs the error क्रमmatted in a provided buffer (we have
 * to check अगर it वापसed something अन्यथा and copy that instead), अवरोधs the
 * build on प्रणालीs not using glibc, like Alpine Linux, where musl libc is
 * used.
 *
 * So, पूर्णांकroduce yet another wrapper, str_error_r(), that has the GNU
 * पूर्णांकerface, but uses the portable XSI variant of म_त्रुटि_r(), so that users
 * rest asured that the provided buffer is used and it is what is वापसed.
 */
अक्षर *str_error_r(पूर्णांक errnum, अक्षर *buf, माप_प्रकार buflen)
अणु
	पूर्णांक err = म_त्रुटि_r(errnum, buf, buflen);
	अगर (err)
		snम_लिखो(buf, buflen, "INTERNAL ERROR: strerror_r(%d, [buf], %zd)=%d", errnum, buflen, err);
	वापस buf;
पूर्ण
