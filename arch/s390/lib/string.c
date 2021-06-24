<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 *    Optimized string functions
 *
 *  S390 version
 *    Copyright IBM Corp. 2004
 *    Author(s): Martin Schwidefsky (schwidefsky@de.ibm.com)
 */

#घोषणा IN_ARCH_STRING_C 1

#समावेश <linux/types.h>
#समावेश <linux/माला.स>
#समावेश <linux/export.h>

/*
 * Helper functions to find the end of a string
 */
अटल अंतरभूत अक्षर *__strend(स्थिर अक्षर *s)
अणु
	रेजिस्टर अचिन्हित दीर्घ r0 यंत्र("0") = 0;

	यंत्र अस्थिर ("0: srst  %0,%1\n"
		      "   jo    0b"
		      : "+d" (r0), "+a" (s) :  : "cc", "memory");
	वापस (अक्षर *) r0;
पूर्ण

अटल अंतरभूत अक्षर *__strnend(स्थिर अक्षर *s, माप_प्रकार n)
अणु
	रेजिस्टर अचिन्हित दीर्घ r0 यंत्र("0") = 0;
	स्थिर अक्षर *p = s + n;

	यंत्र अस्थिर ("0: srst  %0,%1\n"
		      "   jo    0b"
		      : "+d" (p), "+a" (s) : "d" (r0) : "cc", "memory");
	वापस (अक्षर *) p;
पूर्ण

/**
 * म_माप - Find the length of a string
 * @s: The string to be sized
 *
 * वापसs the length of @s
 */
#अगर_घोषित __HAVE_ARCH_STRLEN
माप_प्रकार म_माप(स्थिर अक्षर *s)
अणु
	वापस __strend(s) - s;
पूर्ण
EXPORT_SYMBOL(म_माप);
#पूर्ण_अगर

/**
 * strnlen - Find the length of a length-limited string
 * @s: The string to be sized
 * @n: The maximum number of bytes to search
 *
 * वापसs the minimum of the length of @s and @n
 */
#अगर_घोषित __HAVE_ARCH_STRNLEN
माप_प्रकार strnlen(स्थिर अक्षर *s, माप_प्रकार n)
अणु
	वापस __strnend(s, n) - s;
पूर्ण
EXPORT_SYMBOL(strnlen);
#पूर्ण_अगर

/**
 * म_नकल - Copy a %NUL terminated string
 * @dest: Where to copy the string to
 * @src: Where to copy the string from
 *
 * वापसs a poपूर्णांकer to @dest
 */
#अगर_घोषित __HAVE_ARCH_STRCPY
अक्षर *म_नकल(अक्षर *dest, स्थिर अक्षर *src)
अणु
	रेजिस्टर पूर्णांक r0 यंत्र("0") = 0;
	अक्षर *ret = dest;

	यंत्र अस्थिर ("0: mvst  %0,%1\n"
		      "   jo    0b"
		      : "+&a" (dest), "+&a" (src) : "d" (r0)
		      : "cc", "memory" );
	वापस ret;
पूर्ण
EXPORT_SYMBOL(म_नकल);
#पूर्ण_अगर

/**
 * strlcpy - Copy a %NUL terminated string पूर्णांकo a sized buffer
 * @dest: Where to copy the string to
 * @src: Where to copy the string from
 * @size: size of destination buffer
 *
 * Compatible with *BSD: the result is always a valid
 * NUL-terminated string that fits in the buffer (unless,
 * of course, the buffer size is zero). It करोes not pad
 * out the result like म_नकलन() करोes.
 */
#अगर_घोषित __HAVE_ARCH_STRLCPY
माप_प्रकार strlcpy(अक्षर *dest, स्थिर अक्षर *src, माप_प्रकार size)
अणु
	माप_प्रकार ret = __strend(src) - src;

	अगर (size) अणु
		माप_प्रकार len = (ret >= size) ? size-1 : ret;
		dest[len] = '\0';
		स_नकल(dest, src, len);
	पूर्ण
	वापस ret;
पूर्ण
EXPORT_SYMBOL(strlcpy);
#पूर्ण_अगर

/**
 * म_नकलन - Copy a length-limited, %NUL-terminated string
 * @dest: Where to copy the string to
 * @src: Where to copy the string from
 * @n: The maximum number of bytes to copy
 *
 * The result is not %NUL-terminated अगर the source exceeds
 * @n bytes.
 */
#अगर_घोषित __HAVE_ARCH_STRNCPY
अक्षर *म_नकलन(अक्षर *dest, स्थिर अक्षर *src, माप_प्रकार n)
अणु
	माप_प्रकार len = __strnend(src, n) - src;
	स_रखो(dest + len, 0, n - len);
	स_नकल(dest, src, len);
	वापस dest;
पूर्ण
EXPORT_SYMBOL(म_नकलन);
#पूर्ण_अगर

/**
 * म_जोड़ो - Append one %NUL-terminated string to another
 * @dest: The string to be appended to
 * @src: The string to append to it
 *
 * वापसs a poपूर्णांकer to @dest
 */
#अगर_घोषित __HAVE_ARCH_STRCAT
अक्षर *म_जोड़ो(अक्षर *dest, स्थिर अक्षर *src)
अणु
	रेजिस्टर पूर्णांक r0 यंत्र("0") = 0;
	अचिन्हित दीर्घ dummy;
	अक्षर *ret = dest;

	यंत्र अस्थिर ("0: srst  %0,%1\n"
		      "   jo    0b\n"
		      "1: mvst  %0,%2\n"
		      "   jo    1b"
		      : "=&a" (dummy), "+a" (dest), "+a" (src)
		      : "d" (r0), "0" (0UL) : "cc", "memory" );
	वापस ret;
पूर्ण
EXPORT_SYMBOL(म_जोड़ो);
#पूर्ण_अगर

/**
 * strlcat - Append a length-limited, %NUL-terminated string to another
 * @dest: The string to be appended to
 * @src: The string to append to it
 * @n: The size of the destination buffer.
 */
#अगर_घोषित __HAVE_ARCH_STRLCAT
माप_प्रकार strlcat(अक्षर *dest, स्थिर अक्षर *src, माप_प्रकार n)
अणु
	माप_प्रकार dsize = __strend(dest) - dest;
	माप_प्रकार len = __strend(src) - src;
	माप_प्रकार res = dsize + len;

	अगर (dsize < n) अणु
		dest += dsize;
		n -= dsize;
		अगर (len >= n)
			len = n - 1;
		dest[len] = '\0';
		स_नकल(dest, src, len);
	पूर्ण
	वापस res;
पूर्ण
EXPORT_SYMBOL(strlcat);
#पूर्ण_अगर

/**
 * म_जोड़न - Append a length-limited, %NUL-terminated string to another
 * @dest: The string to be appended to
 * @src: The string to append to it
 * @n: The maximum numbers of bytes to copy
 *
 * वापसs a poपूर्णांकer to @dest
 *
 * Note that in contrast to म_नकलन, म_जोड़न ensures the result is
 * terminated.
 */
#अगर_घोषित __HAVE_ARCH_STRNCAT
अक्षर *म_जोड़न(अक्षर *dest, स्थिर अक्षर *src, माप_प्रकार n)
अणु
	माप_प्रकार len = __strnend(src, n) - src;
	अक्षर *p = __strend(dest);

	p[len] = '\0';
	स_नकल(p, src, len);
	वापस dest;
पूर्ण
EXPORT_SYMBOL(म_जोड़न);
#पूर्ण_अगर

/**
 * म_भेद - Compare two strings
 * @s1: One string
 * @s2: Another string
 *
 * वापसs   0 अगर @s1 and @s2 are equal,
 *	   < 0 अगर @s1 is less than @s2
 *	   > 0 अगर @s1 is greater than @s2
 */
#अगर_घोषित __HAVE_ARCH_STRCMP
पूर्णांक म_भेद(स्थिर अक्षर *s1, स्थिर अक्षर *s2)
अणु
	रेजिस्टर पूर्णांक r0 यंत्र("0") = 0;
	पूर्णांक ret = 0;

	यंत्र अस्थिर ("0: clst %2,%3\n"
		      "   jo   0b\n"
		      "   je   1f\n"
		      "   ic   %0,0(%2)\n"
		      "   ic   %1,0(%3)\n"
		      "   sr   %0,%1\n"
		      "1:"
		      : "+d" (ret), "+d" (r0), "+a" (s1), "+a" (s2)
		      : : "cc", "memory");
	वापस ret;
पूर्ण
EXPORT_SYMBOL(म_भेद);
#पूर्ण_अगर

/**
 * म_खोजप - Find the last occurrence of a अक्षरacter in a string
 * @s: The string to be searched
 * @c: The अक्षरacter to search क्रम
 */
#अगर_घोषित __HAVE_ARCH_STRRCHR
अक्षर *म_खोजप(स्थिर अक्षर *s, पूर्णांक c)
अणु
       माप_प्रकार len = __strend(s) - s;

       अगर (len)
	       करो अणु
		       अगर (s[len] == (अक्षर) c)
			       वापस (अक्षर *) s + len;
	       पूर्ण जबतक (--len > 0);
       वापस शून्य;
पूर्ण
EXPORT_SYMBOL(म_खोजप);
#पूर्ण_अगर

अटल अंतरभूत पूर्णांक clcle(स्थिर अक्षर *s1, अचिन्हित दीर्घ l1,
			स्थिर अक्षर *s2, अचिन्हित दीर्घ l2)
अणु
	रेजिस्टर अचिन्हित दीर्घ r2 यंत्र("2") = (अचिन्हित दीर्घ) s1;
	रेजिस्टर अचिन्हित दीर्घ r3 यंत्र("3") = (अचिन्हित दीर्घ) l1;
	रेजिस्टर अचिन्हित दीर्घ r4 यंत्र("4") = (अचिन्हित दीर्घ) s2;
	रेजिस्टर अचिन्हित दीर्घ r5 यंत्र("5") = (अचिन्हित दीर्घ) l2;
	पूर्णांक cc;

	यंत्र अस्थिर ("0: clcle %1,%3,0\n"
		      "   jo    0b\n"
		      "   ipm   %0\n"
		      "   srl   %0,28"
		      : "=&d" (cc), "+a" (r2), "+a" (r3),
			"+a" (r4), "+a" (r5) : : "cc", "memory");
	वापस cc;
पूर्ण

/**
 * म_माला - Find the first substring in a %NUL terminated string
 * @s1: The string to be searched
 * @s2: The string to search क्रम
 */
#अगर_घोषित __HAVE_ARCH_STRSTR
अक्षर *म_माला(स्थिर अक्षर *s1, स्थिर अक्षर *s2)
अणु
	पूर्णांक l1, l2;

	l2 = __strend(s2) - s2;
	अगर (!l2)
		वापस (अक्षर *) s1;
	l1 = __strend(s1) - s1;
	जबतक (l1-- >= l2) अणु
		पूर्णांक cc;

		cc = clcle(s1, l2, s2, l2);
		अगर (!cc)
			वापस (अक्षर *) s1;
		s1++;
	पूर्ण
	वापस शून्य;
पूर्ण
EXPORT_SYMBOL(म_माला);
#पूर्ण_अगर

/**
 * स_प्रथम - Find a अक्षरacter in an area of memory.
 * @s: The memory area
 * @c: The byte to search क्रम
 * @n: The size of the area.
 *
 * वापसs the address of the first occurrence of @c, or %शून्य
 * अगर @c is not found
 */
#अगर_घोषित __HAVE_ARCH_MEMCHR
व्योम *स_प्रथम(स्थिर व्योम *s, पूर्णांक c, माप_प्रकार n)
अणु
	रेजिस्टर पूर्णांक r0 यंत्र("0") = (अक्षर) c;
	स्थिर व्योम *ret = s + n;

	यंत्र अस्थिर ("0: srst  %0,%1\n"
		      "   jo    0b\n"
		      "   jl	1f\n"
		      "   la    %0,0\n"
		      "1:"
		      : "+a" (ret), "+&a" (s) : "d" (r0) : "cc", "memory");
	वापस (व्योम *) ret;
पूर्ण
EXPORT_SYMBOL(स_प्रथम);
#पूर्ण_अगर

/**
 * स_भेद - Compare two areas of memory
 * @s1: One area of memory
 * @s2: Another area of memory
 * @n: The size of the area.
 */
#अगर_घोषित __HAVE_ARCH_MEMCMP
पूर्णांक स_भेद(स्थिर व्योम *s1, स्थिर व्योम *s2, माप_प्रकार n)
अणु
	पूर्णांक ret;

	ret = clcle(s1, n, s2, n);
	अगर (ret)
		ret = ret == 1 ? -1 : 1;
	वापस ret;
पूर्ण
EXPORT_SYMBOL(स_भेद);
#पूर्ण_अगर

/**
 * memscan - Find a अक्षरacter in an area of memory.
 * @s: The memory area
 * @c: The byte to search क्रम
 * @n: The size of the area.
 *
 * वापसs the address of the first occurrence of @c, or 1 byte past
 * the area अगर @c is not found
 */
#अगर_घोषित __HAVE_ARCH_MEMSCAN
व्योम *memscan(व्योम *s, पूर्णांक c, माप_प्रकार n)
अणु
	रेजिस्टर पूर्णांक r0 यंत्र("0") = (अक्षर) c;
	स्थिर व्योम *ret = s + n;

	यंत्र अस्थिर ("0: srst  %0,%1\n"
		      "   jo    0b\n"
		      : "+a" (ret), "+&a" (s) : "d" (r0) : "cc", "memory");
	वापस (व्योम *) ret;
पूर्ण
EXPORT_SYMBOL(memscan);
#पूर्ण_अगर
