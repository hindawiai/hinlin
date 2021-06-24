<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 *	arch/alpha/lib/srm_prपूर्णांकk.c
 */

#समावेश <linux/kernel.h>
#समावेश <यंत्र/console.h>

दीर्घ
srm_prपूर्णांकk(स्थिर अक्षर *fmt, ...)
अणु
	अटल अक्षर buf[1024];
	बहु_सूची args;
	दीर्घ len, num_lf;
	अक्षर *src, *dst;

	बहु_शुरू(args, fmt);
	len = भम_लिखो(buf, fmt, args);
	बहु_पूर्ण(args);

	/* count number of linefeeds in string: */

	num_lf = 0;
	क्रम (src = buf; *src; ++src) अणु
		अगर (*src == '\n') अणु
			++num_lf;
		पूर्ण
	पूर्ण

	अगर (num_lf) अणु
		/* expand each linefeed पूर्णांकo carriage-वापस/linefeed: */
		क्रम (dst = src + num_lf; src >= buf; ) अणु
			अगर (*src == '\n') अणु
				*dst-- = '\r';
			पूर्ण
			*dst-- = *src--;
		पूर्ण
	पूर्ण

	srm_माला_दो(buf, num_lf+len);	
        वापस len;
पूर्ण
