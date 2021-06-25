<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * arch/mips/boot/compressed/string.c
 *
 * Very small subset of simple string routines
 */

#समावेश <linux/compiler_attributes.h>
#समावेश <linux/types.h>

व्योम *स_नकल(व्योम *dest, स्थिर व्योम *src, माप_प्रकार n)
अणु
	पूर्णांक i;
	स्थिर अक्षर *s = src;
	अक्षर *d = dest;

	क्रम (i = 0; i < n; i++)
		d[i] = s[i];
	वापस dest;
पूर्ण

व्योम *स_रखो(व्योम *s, पूर्णांक c, माप_प्रकार n)
अणु
	पूर्णांक i;
	अक्षर *ss = s;

	क्रम (i = 0; i < n; i++)
		ss[i] = c;
	वापस s;
पूर्ण

व्योम * __weak स_हटाओ(व्योम *dest, स्थिर व्योम *src, माप_प्रकार n)
अणु
	अचिन्हित पूर्णांक i;
	स्थिर अक्षर *s = src;
	अक्षर *d = dest;

	अगर ((uपूर्णांकptr_t)dest < (uपूर्णांकptr_t)src) अणु
		क्रम (i = 0; i < n; i++)
			d[i] = s[i];
	पूर्ण अन्यथा अणु
		क्रम (i = n; i > 0; i--)
			d[i - 1] = s[i - 1];
	पूर्ण
	वापस dest;
पूर्ण
