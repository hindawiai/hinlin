<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * arch/arm/boot/compressed/string.c
 *
 * Small subset of simple string routines
 */

#समावेश <linux/माला.स>

/*
 * The decompressor is built without KASan but uses the same redirects as the
 * rest of the kernel when CONFIG_KASAN is enabled, defining e.g. स_नकल()
 * to __स_नकल() but since we are not linking with the मुख्य kernel string
 * library in the decompressor, that will lead to link failures.
 *
 * Undefine KASan's versions, define the wrapped functions and alias them to
 * the right names so that when e.g. __स_नकल() appear in the code, it will
 * still be linked to this local version of स_नकल().
 */
#अगर_घोषित CONFIG_KASAN
#अघोषित स_नकल
#अघोषित स_हटाओ
#अघोषित स_रखो
व्योम *__स_नकल(व्योम *__dest, __स्थिर व्योम *__src, माप_प्रकार __n) __alias(स_नकल);
व्योम *__स_हटाओ(व्योम *__dest, __स्थिर व्योम *__src, माप_प्रकार count) __alias(स_हटाओ);
व्योम *__स_रखो(व्योम *s, पूर्णांक c, माप_प्रकार count) __alias(स_रखो);
#पूर्ण_अगर

व्योम *स_नकल(व्योम *__dest, __स्थिर व्योम *__src, माप_प्रकार __n)
अणु
	पूर्णांक i = 0;
	अचिन्हित अक्षर *d = (अचिन्हित अक्षर *)__dest, *s = (अचिन्हित अक्षर *)__src;

	क्रम (i = __n >> 3; i > 0; i--) अणु
		*d++ = *s++;
		*d++ = *s++;
		*d++ = *s++;
		*d++ = *s++;
		*d++ = *s++;
		*d++ = *s++;
		*d++ = *s++;
		*d++ = *s++;
	पूर्ण

	अगर (__n & 1 << 2) अणु
		*d++ = *s++;
		*d++ = *s++;
		*d++ = *s++;
		*d++ = *s++;
	पूर्ण

	अगर (__n & 1 << 1) अणु
		*d++ = *s++;
		*d++ = *s++;
	पूर्ण

	अगर (__n & 1)
		*d++ = *s++;

	वापस __dest;
पूर्ण

व्योम *स_हटाओ(व्योम *__dest, __स्थिर व्योम *__src, माप_प्रकार count)
अणु
	अचिन्हित अक्षर *d = __dest;
	स्थिर अचिन्हित अक्षर *s = __src;

	अगर (__dest == __src)
		वापस __dest;

	अगर (__dest < __src)
		वापस स_नकल(__dest, __src, count);

	जबतक (count--)
		d[count] = s[count];
	वापस __dest;
पूर्ण

माप_प्रकार म_माप(स्थिर अक्षर *s)
अणु
	स्थिर अक्षर *sc = s;

	जबतक (*sc != '\0')
		sc++;
	वापस sc - s;
पूर्ण

माप_प्रकार strnlen(स्थिर अक्षर *s, माप_प्रकार count)
अणु
	स्थिर अक्षर *sc;

	क्रम (sc = s; count-- && *sc != '\0'; ++sc)
		/* nothing */;
	वापस sc - s;
पूर्ण

पूर्णांक स_भेद(स्थिर व्योम *cs, स्थिर व्योम *ct, माप_प्रकार count)
अणु
	स्थिर अचिन्हित अक्षर *su1 = cs, *su2 = ct, *end = su1 + count;
	पूर्णांक res = 0;

	जबतक (su1 < end) अणु
		res = *su1++ - *su2++;
		अगर (res)
			अवरोध;
	पूर्ण
	वापस res;
पूर्ण

पूर्णांक म_भेद(स्थिर अक्षर *cs, स्थिर अक्षर *ct)
अणु
	अचिन्हित अक्षर c1, c2;
	पूर्णांक res = 0;

	करो अणु
		c1 = *cs++;
		c2 = *ct++;
		res = c1 - c2;
		अगर (res)
			अवरोध;
	पूर्ण जबतक (c1);
	वापस res;
पूर्ण

व्योम *स_प्रथम(स्थिर व्योम *s, पूर्णांक c, माप_प्रकार count)
अणु
	स्थिर अचिन्हित अक्षर *p = s;

	जबतक (count--)
		अगर ((अचिन्हित अक्षर)c == *p++)
			वापस (व्योम *)(p - 1);
	वापस शून्य;
पूर्ण

अक्षर *म_अक्षर(स्थिर अक्षर *s, पूर्णांक c)
अणु
	जबतक (*s != (अक्षर)c)
		अगर (*s++ == '\0')
			वापस शून्य;
	वापस (अक्षर *)s;
पूर्ण

अक्षर *म_खोजप(स्थिर अक्षर *s, पूर्णांक c)
अणु
	स्थिर अक्षर *last = शून्य;
	करो अणु
		अगर (*s == (अक्षर)c)
			last = s;
	पूर्ण जबतक (*s++);
	वापस (अक्षर *)last;
पूर्ण

#अघोषित स_रखो

व्योम *स_रखो(व्योम *s, पूर्णांक c, माप_प्रकार count)
अणु
	अक्षर *xs = s;
	जबतक (count--)
		*xs++ = c;
	वापस s;
पूर्ण
