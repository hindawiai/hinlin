<शैली गुरु>
// SPDX-License-Identअगरier: LGPL-2.1
#अघोषित _GNU_SOURCE
#समावेश <माला.स>
#समावेश <मानकपन.स>

#समावेश "event-parse.h"

#अघोषित _PE
#घोषणा _PE(code, str) str
अटल स्थिर अक्षर * स्थिर tep_error_str[] = अणु
	TEP_ERRORS
पूर्ण;
#अघोषित _PE

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
पूर्णांक tep_म_त्रुटि(काष्ठा tep_handle *tep __maybe_unused,
		 क्रमागत tep_त्रुटि_सं errnum, अक्षर *buf, माप_प्रकार buflen)
अणु
	स्थिर अक्षर *msg;
	पूर्णांक idx;

	अगर (!buflen)
		वापस 0;

	अगर (errnum >= 0) अणु
		पूर्णांक err = म_त्रुटि_r(errnum, buf, buflen);
		buf[buflen - 1] = 0;
		वापस err;
	पूर्ण

	अगर (errnum <= __TEP_ERRNO__START ||
	    errnum >= __TEP_ERRNO__END)
		वापस -1;

	idx = errnum - __TEP_ERRNO__START - 1;
	msg = tep_error_str[idx];
	snम_लिखो(buf, buflen, "%s", msg);

	वापस 0;
पूर्ण
