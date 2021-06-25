<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#समावेश <sys/types.h>
#समावेश <linux/kernel.h>
#समावेश <मानकपन.स>

पूर्णांक vscnम_लिखो(अक्षर *buf, माप_प्रकार size, स्थिर अक्षर *fmt, बहु_सूची args)
अणु
       पूर्णांक i = vsnम_लिखो(buf, size, fmt, args);
       sमाप_प्रकार ssize = size;

       वापस (i >= ssize) ? (ssize - 1) : i;
पूर्ण

पूर्णांक scnम_लिखो(अक्षर * buf, माप_प्रकार size, स्थिर अक्षर * fmt, ...)
अणु
       sमाप_प्रकार ssize = size;
       बहु_सूची args;
       पूर्णांक i;

       बहु_शुरू(args, fmt);
       i = vsnम_लिखो(buf, size, fmt, args);
       बहु_पूर्ण(args);

       वापस (i >= ssize) ? (ssize - 1) : i;
पूर्ण

पूर्णांक scnम_लिखो_pad(अक्षर * buf, माप_प्रकार size, स्थिर अक्षर * fmt, ...)
अणु
	sमाप_प्रकार ssize = size;
	बहु_सूची args;
	पूर्णांक i;

	बहु_शुरू(args, fmt);
	i = vscnम_लिखो(buf, size, fmt, args);
	बहु_पूर्ण(args);

	अगर (i < (पूर्णांक) size) अणु
		क्रम (; i < (पूर्णांक) size; i++)
			buf[i] = ' ';
		buf[i] = 0x0;
	पूर्ण

	वापस (i >= ssize) ? (ssize - 1) : i;
पूर्ण
