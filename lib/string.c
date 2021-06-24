<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 *  linux/lib/string.c
 *
 *  Copyright (C) 1991, 1992  Linus Torvalds
 */

/*
 * stupid library routines.. The optimized versions should generally be found
 * as अंतरभूत code in <यंत्र-xx/माला.स>
 *
 * These are buggy as well..
 *
 * * Fri Jun 25 1999, Ingo Oeser <ioe@inक्रमmatik.tu-chemnitz.de>
 * -  Added strsep() which will replace म_मोहर() soon (because strsep() is
 *    reentrant and should be faster). Use only strsep() in new code, please.
 *
 * * Sat Feb 09 2002, Jason Thomas <jason@topic.com.au>,
 *                    Matthew Hawkins <matt@mh.dropbear.id.au>
 * -  Kissed म_मोहर() goodbye
 */

#समावेश <linux/types.h>
#समावेश <linux/माला.स>
#समावेश <linux/प्रकार.स>
#समावेश <linux/kernel.h>
#समावेश <linux/export.h>
#समावेश <linux/bug.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/slab.h>

#समावेश <यंत्र/byteorder.h>
#समावेश <यंत्र/word-at-a-समय.स>
#समावेश <यंत्र/page.h>

#अगर_अघोषित __HAVE_ARCH_STRNCASECMP
/**
 * strnहालcmp - Case insensitive, length-limited string comparison
 * @s1: One string
 * @s2: The other string
 * @len: the maximum number of अक्षरacters to compare
 */
पूर्णांक strnहालcmp(स्थिर अक्षर *s1, स्थिर अक्षर *s2, माप_प्रकार len)
अणु
	/* Yes, Virginia, it had better be अचिन्हित */
	अचिन्हित अक्षर c1, c2;

	अगर (!len)
		वापस 0;

	करो अणु
		c1 = *s1++;
		c2 = *s2++;
		अगर (!c1 || !c2)
			अवरोध;
		अगर (c1 == c2)
			जारी;
		c1 = छोटे(c1);
		c2 = छोटे(c2);
		अगर (c1 != c2)
			अवरोध;
	पूर्ण जबतक (--len);
	वापस (पूर्णांक)c1 - (पूर्णांक)c2;
पूर्ण
EXPORT_SYMBOL(strnहालcmp);
#पूर्ण_अगर

#अगर_अघोषित __HAVE_ARCH_STRCASECMP
पूर्णांक strहालcmp(स्थिर अक्षर *s1, स्थिर अक्षर *s2)
अणु
	पूर्णांक c1, c2;

	करो अणु
		c1 = छोटे(*s1++);
		c2 = छोटे(*s2++);
	पूर्ण जबतक (c1 == c2 && c1 != 0);
	वापस c1 - c2;
पूर्ण
EXPORT_SYMBOL(strहालcmp);
#पूर्ण_अगर

#अगर_अघोषित __HAVE_ARCH_STRCPY
/**
 * म_नकल - Copy a %NUL terminated string
 * @dest: Where to copy the string to
 * @src: Where to copy the string from
 */
अक्षर *म_नकल(अक्षर *dest, स्थिर अक्षर *src)
अणु
	अक्षर *पंचांगp = dest;

	जबतक ((*dest++ = *src++) != '\0')
		/* nothing */;
	वापस पंचांगp;
पूर्ण
EXPORT_SYMBOL(म_नकल);
#पूर्ण_अगर

#अगर_अघोषित __HAVE_ARCH_STRNCPY
/**
 * म_नकलन - Copy a length-limited, C-string
 * @dest: Where to copy the string to
 * @src: Where to copy the string from
 * @count: The maximum number of bytes to copy
 *
 * The result is not %NUL-terminated अगर the source exceeds
 * @count bytes.
 *
 * In the हाल where the length of @src is less than  that  of
 * count, the reमुख्यder of @dest will be padded with %NUL.
 *
 */
अक्षर *म_नकलन(अक्षर *dest, स्थिर अक्षर *src, माप_प्रकार count)
अणु
	अक्षर *पंचांगp = dest;

	जबतक (count) अणु
		अगर ((*पंचांगp = *src) != 0)
			src++;
		पंचांगp++;
		count--;
	पूर्ण
	वापस dest;
पूर्ण
EXPORT_SYMBOL(म_नकलन);
#पूर्ण_अगर

#अगर_अघोषित __HAVE_ARCH_STRLCPY
/**
 * strlcpy - Copy a C-string पूर्णांकo a sized buffer
 * @dest: Where to copy the string to
 * @src: Where to copy the string from
 * @size: size of destination buffer
 *
 * Compatible with ``*BSD``: the result is always a valid
 * NUL-terminated string that fits in the buffer (unless,
 * of course, the buffer size is zero). It करोes not pad
 * out the result like म_नकलन() करोes.
 */
माप_प्रकार strlcpy(अक्षर *dest, स्थिर अक्षर *src, माप_प्रकार size)
अणु
	माप_प्रकार ret = म_माप(src);

	अगर (size) अणु
		माप_प्रकार len = (ret >= size) ? size - 1 : ret;
		स_नकल(dest, src, len);
		dest[len] = '\0';
	पूर्ण
	वापस ret;
पूर्ण
EXPORT_SYMBOL(strlcpy);
#पूर्ण_अगर

#अगर_अघोषित __HAVE_ARCH_STRSCPY
/**
 * strscpy - Copy a C-string पूर्णांकo a sized buffer
 * @dest: Where to copy the string to
 * @src: Where to copy the string from
 * @count: Size of destination buffer
 *
 * Copy the string, or as much of it as fits, पूर्णांकo the dest buffer.  The
 * behavior is undefined अगर the string buffers overlap.  The destination
 * buffer is always NUL terminated, unless it's zero-sized.
 *
 * Preferred to strlcpy() since the API करोesn't require पढ़ोing memory
 * from the src string beyond the specअगरied "count" bytes, and since
 * the वापस value is easier to error-check than strlcpy()'s.
 * In addition, the implementation is robust to the string changing out
 * from underneath it, unlike the current strlcpy() implementation.
 *
 * Preferred to म_नकलन() since it always वापसs a valid string, and
 * करोesn't unnecessarily क्रमce the tail of the destination buffer to be
 * zeroed.  If zeroing is desired please use strscpy_pad().
 *
 * Returns:
 * * The number of अक्षरacters copied (not including the trailing %NUL)
 * * -E2BIG अगर count is 0 or @src was truncated.
 */
sमाप_प्रकार strscpy(अक्षर *dest, स्थिर अक्षर *src, माप_प्रकार count)
अणु
	स्थिर काष्ठा word_at_a_समय स्थिरants = WORD_AT_A_TIME_CONSTANTS;
	माप_प्रकार max = count;
	दीर्घ res = 0;

	अगर (count == 0 || WARN_ON_ONCE(count > पूर्णांक_उच्च))
		वापस -E2BIG;

#अगर_घोषित CONFIG_HAVE_EFFICIENT_UNALIGNED_ACCESS
	/*
	 * If src is unaligned, करोn't cross a page boundary,
	 * since we करोn't know अगर the next page is mapped.
	 */
	अगर ((दीर्घ)src & (माप(दीर्घ) - 1)) अणु
		माप_प्रकार limit = PAGE_SIZE - ((दीर्घ)src & (PAGE_SIZE - 1));
		अगर (limit < max)
			max = limit;
	पूर्ण
#अन्यथा
	/* If src or dest is unaligned, करोn't करो word-at-a-समय. */
	अगर (((दीर्घ) dest | (दीर्घ) src) & (माप(दीर्घ) - 1))
		max = 0;
#पूर्ण_अगर

	जबतक (max >= माप(अचिन्हित दीर्घ)) अणु
		अचिन्हित दीर्घ c, data;

		c = पढ़ो_word_at_a_समय(src+res);
		अगर (has_zero(c, &data, &स्थिरants)) अणु
			data = prep_zero_mask(c, data, &स्थिरants);
			data = create_zero_mask(data);
			*(अचिन्हित दीर्घ *)(dest+res) = c & zero_bytemask(data);
			वापस res + find_zero(data);
		पूर्ण
		*(अचिन्हित दीर्घ *)(dest+res) = c;
		res += माप(अचिन्हित दीर्घ);
		count -= माप(अचिन्हित दीर्घ);
		max -= माप(अचिन्हित दीर्घ);
	पूर्ण

	जबतक (count) अणु
		अक्षर c;

		c = src[res];
		dest[res] = c;
		अगर (!c)
			वापस res;
		res++;
		count--;
	पूर्ण

	/* Hit buffer length without finding a NUL; क्रमce NUL-termination. */
	अगर (res)
		dest[res-1] = '\0';

	वापस -E2BIG;
पूर्ण
EXPORT_SYMBOL(strscpy);
#पूर्ण_अगर

/**
 * strscpy_pad() - Copy a C-string पूर्णांकo a sized buffer
 * @dest: Where to copy the string to
 * @src: Where to copy the string from
 * @count: Size of destination buffer
 *
 * Copy the string, or as much of it as fits, पूर्णांकo the dest buffer.  The
 * behavior is undefined अगर the string buffers overlap.  The destination
 * buffer is always %NUL terminated, unless it's zero-sized.
 *
 * If the source string is लघुer than the destination buffer, zeros
 * the tail of the destination buffer.
 *
 * For full explanation of why you may want to consider using the
 * 'strscpy' functions please see the function करोcstring क्रम strscpy().
 *
 * Returns:
 * * The number of अक्षरacters copied (not including the trailing %NUL)
 * * -E2BIG अगर count is 0 or @src was truncated.
 */
sमाप_प्रकार strscpy_pad(अक्षर *dest, स्थिर अक्षर *src, माप_प्रकार count)
अणु
	sमाप_प्रकार written;

	written = strscpy(dest, src, count);
	अगर (written < 0 || written == count - 1)
		वापस written;

	स_रखो(dest + written + 1, 0, count - written - 1);

	वापस written;
पूर्ण
EXPORT_SYMBOL(strscpy_pad);

/**
 * stpcpy - copy a string from src to dest वापसing a poपूर्णांकer to the new end
 *          of dest, including src's %NUL-terminator. May overrun dest.
 * @dest: poपूर्णांकer to end of string being copied पूर्णांकo. Must be large enough
 *        to receive copy.
 * @src: poपूर्णांकer to the beginning of string being copied from. Must not overlap
 *       dest.
 *
 * stpcpy dअगरfers from म_नकल in a key way: the वापस value is a poपूर्णांकer
 * to the new %NUL-terminating अक्षरacter in @dest. (For म_नकल, the वापस
 * value is a poपूर्णांकer to the start of @dest). This पूर्णांकerface is considered
 * unsafe as it करोesn't perform bounds checking of the inputs. As such it's
 * not recommended क्रम usage. Instead, its definition is provided in हाल
 * the compiler lowers other libcalls to stpcpy.
 */
अक्षर *stpcpy(अक्षर *__restrict__ dest, स्थिर अक्षर *__restrict__ src);
अक्षर *stpcpy(अक्षर *__restrict__ dest, स्थिर अक्षर *__restrict__ src)
अणु
	जबतक ((*dest++ = *src++) != '\0')
		/* nothing */;
	वापस --dest;
पूर्ण
EXPORT_SYMBOL(stpcpy);

#अगर_अघोषित __HAVE_ARCH_STRCAT
/**
 * म_जोड़ो - Append one %NUL-terminated string to another
 * @dest: The string to be appended to
 * @src: The string to append to it
 */
अक्षर *म_जोड़ो(अक्षर *dest, स्थिर अक्षर *src)
अणु
	अक्षर *पंचांगp = dest;

	जबतक (*dest)
		dest++;
	जबतक ((*dest++ = *src++) != '\0')
		;
	वापस पंचांगp;
पूर्ण
EXPORT_SYMBOL(म_जोड़ो);
#पूर्ण_अगर

#अगर_अघोषित __HAVE_ARCH_STRNCAT
/**
 * म_जोड़न - Append a length-limited, C-string to another
 * @dest: The string to be appended to
 * @src: The string to append to it
 * @count: The maximum numbers of bytes to copy
 *
 * Note that in contrast to म_नकलन(), म_जोड़न() ensures the result is
 * terminated.
 */
अक्षर *म_जोड़न(अक्षर *dest, स्थिर अक्षर *src, माप_प्रकार count)
अणु
	अक्षर *पंचांगp = dest;

	अगर (count) अणु
		जबतक (*dest)
			dest++;
		जबतक ((*dest++ = *src++) != 0) अणु
			अगर (--count == 0) अणु
				*dest = '\0';
				अवरोध;
			पूर्ण
		पूर्ण
	पूर्ण
	वापस पंचांगp;
पूर्ण
EXPORT_SYMBOL(म_जोड़न);
#पूर्ण_अगर

#अगर_अघोषित __HAVE_ARCH_STRLCAT
/**
 * strlcat - Append a length-limited, C-string to another
 * @dest: The string to be appended to
 * @src: The string to append to it
 * @count: The size of the destination buffer.
 */
माप_प्रकार strlcat(अक्षर *dest, स्थिर अक्षर *src, माप_प्रकार count)
अणु
	माप_प्रकार dsize = म_माप(dest);
	माप_प्रकार len = म_माप(src);
	माप_प्रकार res = dsize + len;

	/* This would be a bug */
	BUG_ON(dsize >= count);

	dest += dsize;
	count -= dsize;
	अगर (len >= count)
		len = count-1;
	स_नकल(dest, src, len);
	dest[len] = 0;
	वापस res;
पूर्ण
EXPORT_SYMBOL(strlcat);
#पूर्ण_अगर

#अगर_अघोषित __HAVE_ARCH_STRCMP
/**
 * म_भेद - Compare two strings
 * @cs: One string
 * @ct: Another string
 */
पूर्णांक म_भेद(स्थिर अक्षर *cs, स्थिर अक्षर *ct)
अणु
	अचिन्हित अक्षर c1, c2;

	जबतक (1) अणु
		c1 = *cs++;
		c2 = *ct++;
		अगर (c1 != c2)
			वापस c1 < c2 ? -1 : 1;
		अगर (!c1)
			अवरोध;
	पूर्ण
	वापस 0;
पूर्ण
EXPORT_SYMBOL(म_भेद);
#पूर्ण_अगर

#अगर_अघोषित __HAVE_ARCH_STRNCMP
/**
 * म_भेदन - Compare two length-limited strings
 * @cs: One string
 * @ct: Another string
 * @count: The maximum number of bytes to compare
 */
पूर्णांक म_भेदन(स्थिर अक्षर *cs, स्थिर अक्षर *ct, माप_प्रकार count)
अणु
	अचिन्हित अक्षर c1, c2;

	जबतक (count) अणु
		c1 = *cs++;
		c2 = *ct++;
		अगर (c1 != c2)
			वापस c1 < c2 ? -1 : 1;
		अगर (!c1)
			अवरोध;
		count--;
	पूर्ण
	वापस 0;
पूर्ण
EXPORT_SYMBOL(म_भेदन);
#पूर्ण_अगर

#अगर_अघोषित __HAVE_ARCH_STRCHR
/**
 * म_अक्षर - Find the first occurrence of a अक्षरacter in a string
 * @s: The string to be searched
 * @c: The अक्षरacter to search क्रम
 *
 * Note that the %NUL-terminator is considered part of the string, and can
 * be searched क्रम.
 */
अक्षर *म_अक्षर(स्थिर अक्षर *s, पूर्णांक c)
अणु
	क्रम (; *s != (अक्षर)c; ++s)
		अगर (*s == '\0')
			वापस शून्य;
	वापस (अक्षर *)s;
पूर्ण
EXPORT_SYMBOL(म_अक्षर);
#पूर्ण_अगर

#अगर_अघोषित __HAVE_ARCH_STRCHRNUL
/**
 * म_अक्षरnul - Find and वापस a अक्षरacter in a string, or end of string
 * @s: The string to be searched
 * @c: The अक्षरacter to search क्रम
 *
 * Returns poपूर्णांकer to first occurrence of 'c' in s. If c is not found, then
 * वापस a poपूर्णांकer to the null byte at the end of s.
 */
अक्षर *म_अक्षरnul(स्थिर अक्षर *s, पूर्णांक c)
अणु
	जबतक (*s && *s != (अक्षर)c)
		s++;
	वापस (अक्षर *)s;
पूर्ण
EXPORT_SYMBOL(म_अक्षरnul);
#पूर्ण_अगर

/**
 * strnchrnul - Find and वापस a अक्षरacter in a length limited string,
 * or end of string
 * @s: The string to be searched
 * @count: The number of अक्षरacters to be searched
 * @c: The अक्षरacter to search क्रम
 *
 * Returns poपूर्णांकer to the first occurrence of 'c' in s. If c is not found,
 * then वापस a poपूर्णांकer to the last अक्षरacter of the string.
 */
अक्षर *strnchrnul(स्थिर अक्षर *s, माप_प्रकार count, पूर्णांक c)
अणु
	जबतक (count-- && *s && *s != (अक्षर)c)
		s++;
	वापस (अक्षर *)s;
पूर्ण

#अगर_अघोषित __HAVE_ARCH_STRRCHR
/**
 * म_खोजप - Find the last occurrence of a अक्षरacter in a string
 * @s: The string to be searched
 * @c: The अक्षरacter to search क्रम
 */
अक्षर *म_खोजप(स्थिर अक्षर *s, पूर्णांक c)
अणु
	स्थिर अक्षर *last = शून्य;
	करो अणु
		अगर (*s == (अक्षर)c)
			last = s;
	पूर्ण जबतक (*s++);
	वापस (अक्षर *)last;
पूर्ण
EXPORT_SYMBOL(म_खोजप);
#पूर्ण_अगर

#अगर_अघोषित __HAVE_ARCH_STRNCHR
/**
 * strnchr - Find a अक्षरacter in a length limited string
 * @s: The string to be searched
 * @count: The number of अक्षरacters to be searched
 * @c: The अक्षरacter to search क्रम
 *
 * Note that the %NUL-terminator is considered part of the string, and can
 * be searched क्रम.
 */
अक्षर *strnchr(स्थिर अक्षर *s, माप_प्रकार count, पूर्णांक c)
अणु
	जबतक (count--) अणु
		अगर (*s == (अक्षर)c)
			वापस (अक्षर *)s;
		अगर (*s++ == '\0')
			अवरोध;
	पूर्ण
	वापस शून्य;
पूर्ण
EXPORT_SYMBOL(strnchr);
#पूर्ण_अगर

/**
 * skip_spaces - Removes leading whitespace from @str.
 * @str: The string to be stripped.
 *
 * Returns a poपूर्णांकer to the first non-whitespace अक्षरacter in @str.
 */
अक्षर *skip_spaces(स्थिर अक्षर *str)
अणु
	जबतक (है_खाली(*str))
		++str;
	वापस (अक्षर *)str;
पूर्ण
EXPORT_SYMBOL(skip_spaces);

/**
 * strim - Removes leading and trailing whitespace from @s.
 * @s: The string to be stripped.
 *
 * Note that the first trailing whitespace is replaced with a %NUL-terminator
 * in the given string @s. Returns a poपूर्णांकer to the first non-whitespace
 * अक्षरacter in @s.
 */
अक्षर *strim(अक्षर *s)
अणु
	माप_प्रकार size;
	अक्षर *end;

	size = म_माप(s);
	अगर (!size)
		वापस s;

	end = s + size - 1;
	जबतक (end >= s && है_खाली(*end))
		end--;
	*(end + 1) = '\0';

	वापस skip_spaces(s);
पूर्ण
EXPORT_SYMBOL(strim);

#अगर_अघोषित __HAVE_ARCH_STRLEN
/**
 * म_माप - Find the length of a string
 * @s: The string to be sized
 */
माप_प्रकार म_माप(स्थिर अक्षर *s)
अणु
	स्थिर अक्षर *sc;

	क्रम (sc = s; *sc != '\0'; ++sc)
		/* nothing */;
	वापस sc - s;
पूर्ण
EXPORT_SYMBOL(म_माप);
#पूर्ण_अगर

#अगर_अघोषित __HAVE_ARCH_STRNLEN
/**
 * strnlen - Find the length of a length-limited string
 * @s: The string to be sized
 * @count: The maximum number of bytes to search
 */
माप_प्रकार strnlen(स्थिर अक्षर *s, माप_प्रकार count)
अणु
	स्थिर अक्षर *sc;

	क्रम (sc = s; count-- && *sc != '\0'; ++sc)
		/* nothing */;
	वापस sc - s;
पूर्ण
EXPORT_SYMBOL(strnlen);
#पूर्ण_अगर

#अगर_अघोषित __HAVE_ARCH_STRSPN
/**
 * म_अखोज - Calculate the length of the initial substring of @s which only contain letters in @accept
 * @s: The string to be searched
 * @accept: The string to search क्रम
 */
माप_प्रकार म_अखोज(स्थिर अक्षर *s, स्थिर अक्षर *accept)
अणु
	स्थिर अक्षर *p;
	स्थिर अक्षर *a;
	माप_प्रकार count = 0;

	क्रम (p = s; *p != '\0'; ++p) अणु
		क्रम (a = accept; *a != '\0'; ++a) अणु
			अगर (*p == *a)
				अवरोध;
		पूर्ण
		अगर (*a == '\0')
			वापस count;
		++count;
	पूर्ण
	वापस count;
पूर्ण

EXPORT_SYMBOL(म_अखोज);
#पूर्ण_अगर

#अगर_अघोषित __HAVE_ARCH_STRCSPN
/**
 * म_खोज - Calculate the length of the initial substring of @s which करोes not contain letters in @reject
 * @s: The string to be searched
 * @reject: The string to aव्योम
 */
माप_प्रकार म_खोज(स्थिर अक्षर *s, स्थिर अक्षर *reject)
अणु
	स्थिर अक्षर *p;
	स्थिर अक्षर *r;
	माप_प्रकार count = 0;

	क्रम (p = s; *p != '\0'; ++p) अणु
		क्रम (r = reject; *r != '\0'; ++r) अणु
			अगर (*p == *r)
				वापस count;
		पूर्ण
		++count;
	पूर्ण
	वापस count;
पूर्ण
EXPORT_SYMBOL(म_खोज);
#पूर्ण_अगर

#अगर_अघोषित __HAVE_ARCH_STRPBRK
/**
 * strpbrk - Find the first occurrence of a set of अक्षरacters
 * @cs: The string to be searched
 * @ct: The अक्षरacters to search क्रम
 */
अक्षर *strpbrk(स्थिर अक्षर *cs, स्थिर अक्षर *ct)
अणु
	स्थिर अक्षर *sc1, *sc2;

	क्रम (sc1 = cs; *sc1 != '\0'; ++sc1) अणु
		क्रम (sc2 = ct; *sc2 != '\0'; ++sc2) अणु
			अगर (*sc1 == *sc2)
				वापस (अक्षर *)sc1;
		पूर्ण
	पूर्ण
	वापस शून्य;
पूर्ण
EXPORT_SYMBOL(strpbrk);
#पूर्ण_अगर

#अगर_अघोषित __HAVE_ARCH_STRSEP
/**
 * strsep - Split a string पूर्णांकo tokens
 * @s: The string to be searched
 * @ct: The अक्षरacters to search क्रम
 *
 * strsep() updates @s to poपूर्णांक after the token, पढ़ोy क्रम the next call.
 *
 * It वापसs empty tokens, too, behaving exactly like the libc function
 * of that name. In fact, it was stolen from glibc2 and de-fancy-fied.
 * Same semantics, slimmer shape. ;)
 */
अक्षर *strsep(अक्षर **s, स्थिर अक्षर *ct)
अणु
	अक्षर *sbegin = *s;
	अक्षर *end;

	अगर (sbegin == शून्य)
		वापस शून्य;

	end = strpbrk(sbegin, ct);
	अगर (end)
		*end++ = '\0';
	*s = end;
	वापस sbegin;
पूर्ण
EXPORT_SYMBOL(strsep);
#पूर्ण_अगर

/**
 * sysfs_streq - वापस true अगर strings are equal, modulo trailing newline
 * @s1: one string
 * @s2: another string
 *
 * This routine वापसs true अगरf two strings are equal, treating both
 * NUL and newline-then-NUL as equivalent string terminations.  It's
 * geared क्रम use with sysfs input strings, which generally terminate
 * with newlines but are compared against values without newlines.
 */
bool sysfs_streq(स्थिर अक्षर *s1, स्थिर अक्षर *s2)
अणु
	जबतक (*s1 && *s1 == *s2) अणु
		s1++;
		s2++;
	पूर्ण

	अगर (*s1 == *s2)
		वापस true;
	अगर (!*s1 && *s2 == '\n' && !s2[1])
		वापस true;
	अगर (*s1 == '\n' && !s1[1] && !*s2)
		वापस true;
	वापस false;
पूर्ण
EXPORT_SYMBOL(sysfs_streq);

/**
 * match_string - matches given string in an array
 * @array:	array of strings
 * @n:		number of strings in the array or -1 क्रम शून्य terminated arrays
 * @string:	string to match with
 *
 * This routine will look क्रम a string in an array of strings up to the
 * n-th element in the array or until the first शून्य element.
 *
 * Historically the value of -1 क्रम @n, was used to search in arrays that
 * are शून्य terminated. However, the function करोes not make a distinction
 * when finishing the search: either @n elements have been compared OR
 * the first शून्य element was found.
 *
 * Return:
 * index of a @string in the @array अगर matches, or %-EINVAL otherwise.
 */
पूर्णांक match_string(स्थिर अक्षर * स्थिर *array, माप_प्रकार n, स्थिर अक्षर *string)
अणु
	पूर्णांक index;
	स्थिर अक्षर *item;

	क्रम (index = 0; index < n; index++) अणु
		item = array[index];
		अगर (!item)
			अवरोध;
		अगर (!म_भेद(item, string))
			वापस index;
	पूर्ण

	वापस -EINVAL;
पूर्ण
EXPORT_SYMBOL(match_string);

/**
 * __sysfs_match_string - matches given string in an array
 * @array: array of strings
 * @n: number of strings in the array or -1 क्रम शून्य terminated arrays
 * @str: string to match with
 *
 * Returns index of @str in the @array or -EINVAL, just like match_string().
 * Uses sysfs_streq instead of म_भेद क्रम matching.
 *
 * This routine will look क्रम a string in an array of strings up to the
 * n-th element in the array or until the first शून्य element.
 *
 * Historically the value of -1 क्रम @n, was used to search in arrays that
 * are शून्य terminated. However, the function करोes not make a distinction
 * when finishing the search: either @n elements have been compared OR
 * the first शून्य element was found.
 */
पूर्णांक __sysfs_match_string(स्थिर अक्षर * स्थिर *array, माप_प्रकार n, स्थिर अक्षर *str)
अणु
	स्थिर अक्षर *item;
	पूर्णांक index;

	क्रम (index = 0; index < n; index++) अणु
		item = array[index];
		अगर (!item)
			अवरोध;
		अगर (sysfs_streq(item, str))
			वापस index;
	पूर्ण

	वापस -EINVAL;
पूर्ण
EXPORT_SYMBOL(__sysfs_match_string);

#अगर_अघोषित __HAVE_ARCH_MEMSET
/**
 * स_रखो - Fill a region of memory with the given value
 * @s: Poपूर्णांकer to the start of the area.
 * @c: The byte to fill the area with
 * @count: The size of the area.
 *
 * Do not use स_रखो() to access IO space, use स_रखो_io() instead.
 */
व्योम *स_रखो(व्योम *s, पूर्णांक c, माप_प्रकार count)
अणु
	अक्षर *xs = s;

	जबतक (count--)
		*xs++ = c;
	वापस s;
पूर्ण
EXPORT_SYMBOL(स_रखो);
#पूर्ण_अगर

#अगर_अघोषित __HAVE_ARCH_MEMSET16
/**
 * स_रखो16() - Fill a memory area with a uपूर्णांक16_t
 * @s: Poपूर्णांकer to the start of the area.
 * @v: The value to fill the area with
 * @count: The number of values to store
 *
 * Dअगरfers from स_रखो() in that it fills with a uपूर्णांक16_t instead
 * of a byte.  Remember that @count is the number of uपूर्णांक16_ts to
 * store, not the number of bytes.
 */
व्योम *स_रखो16(uपूर्णांक16_t *s, uपूर्णांक16_t v, माप_प्रकार count)
अणु
	uपूर्णांक16_t *xs = s;

	जबतक (count--)
		*xs++ = v;
	वापस s;
पूर्ण
EXPORT_SYMBOL(स_रखो16);
#पूर्ण_अगर

#अगर_अघोषित __HAVE_ARCH_MEMSET32
/**
 * स_रखो32() - Fill a memory area with a uपूर्णांक32_t
 * @s: Poपूर्णांकer to the start of the area.
 * @v: The value to fill the area with
 * @count: The number of values to store
 *
 * Dअगरfers from स_रखो() in that it fills with a uपूर्णांक32_t instead
 * of a byte.  Remember that @count is the number of uपूर्णांक32_ts to
 * store, not the number of bytes.
 */
व्योम *स_रखो32(uपूर्णांक32_t *s, uपूर्णांक32_t v, माप_प्रकार count)
अणु
	uपूर्णांक32_t *xs = s;

	जबतक (count--)
		*xs++ = v;
	वापस s;
पूर्ण
EXPORT_SYMBOL(स_रखो32);
#पूर्ण_अगर

#अगर_अघोषित __HAVE_ARCH_MEMSET64
/**
 * स_रखो64() - Fill a memory area with a uपूर्णांक64_t
 * @s: Poपूर्णांकer to the start of the area.
 * @v: The value to fill the area with
 * @count: The number of values to store
 *
 * Dअगरfers from स_रखो() in that it fills with a uपूर्णांक64_t instead
 * of a byte.  Remember that @count is the number of uपूर्णांक64_ts to
 * store, not the number of bytes.
 */
व्योम *स_रखो64(uपूर्णांक64_t *s, uपूर्णांक64_t v, माप_प्रकार count)
अणु
	uपूर्णांक64_t *xs = s;

	जबतक (count--)
		*xs++ = v;
	वापस s;
पूर्ण
EXPORT_SYMBOL(स_रखो64);
#पूर्ण_अगर

#अगर_अघोषित __HAVE_ARCH_MEMCPY
/**
 * स_नकल - Copy one area of memory to another
 * @dest: Where to copy to
 * @src: Where to copy from
 * @count: The size of the area.
 *
 * You should not use this function to access IO space, use स_नकल_toio()
 * or स_नकल_fromio() instead.
 */
व्योम *स_नकल(व्योम *dest, स्थिर व्योम *src, माप_प्रकार count)
अणु
	अक्षर *पंचांगp = dest;
	स्थिर अक्षर *s = src;

	जबतक (count--)
		*पंचांगp++ = *s++;
	वापस dest;
पूर्ण
EXPORT_SYMBOL(स_नकल);
#पूर्ण_अगर

#अगर_अघोषित __HAVE_ARCH_MEMMOVE
/**
 * स_हटाओ - Copy one area of memory to another
 * @dest: Where to copy to
 * @src: Where to copy from
 * @count: The size of the area.
 *
 * Unlike स_नकल(), स_हटाओ() copes with overlapping areas.
 */
व्योम *स_हटाओ(व्योम *dest, स्थिर व्योम *src, माप_प्रकार count)
अणु
	अक्षर *पंचांगp;
	स्थिर अक्षर *s;

	अगर (dest <= src) अणु
		पंचांगp = dest;
		s = src;
		जबतक (count--)
			*पंचांगp++ = *s++;
	पूर्ण अन्यथा अणु
		पंचांगp = dest;
		पंचांगp += count;
		s = src;
		s += count;
		जबतक (count--)
			*--पंचांगp = *--s;
	पूर्ण
	वापस dest;
पूर्ण
EXPORT_SYMBOL(स_हटाओ);
#पूर्ण_अगर

#अगर_अघोषित __HAVE_ARCH_MEMCMP
/**
 * स_भेद - Compare two areas of memory
 * @cs: One area of memory
 * @ct: Another area of memory
 * @count: The size of the area.
 */
#अघोषित स_भेद
__visible पूर्णांक स_भेद(स्थिर व्योम *cs, स्थिर व्योम *ct, माप_प्रकार count)
अणु
	स्थिर अचिन्हित अक्षर *su1, *su2;
	पूर्णांक res = 0;

	क्रम (su1 = cs, su2 = ct; 0 < count; ++su1, ++su2, count--)
		अगर ((res = *su1 - *su2) != 0)
			अवरोध;
	वापस res;
पूर्ण
EXPORT_SYMBOL(स_भेद);
#पूर्ण_अगर

#अगर_अघोषित __HAVE_ARCH_BCMP
/**
 * bcmp - वापसs 0 अगर and only अगर the buffers have identical contents.
 * @a: poपूर्णांकer to first buffer.
 * @b: poपूर्णांकer to second buffer.
 * @len: size of buffers.
 *
 * The sign or magnitude of a non-zero वापस value has no particular
 * meaning, and architectures may implement their own more efficient bcmp(). So
 * जबतक this particular implementation is a simple (tail) call to स_भेद, करो
 * not rely on anything but whether the वापस value is zero or non-zero.
 */
पूर्णांक bcmp(स्थिर व्योम *a, स्थिर व्योम *b, माप_प्रकार len)
अणु
	वापस स_भेद(a, b, len);
पूर्ण
EXPORT_SYMBOL(bcmp);
#पूर्ण_अगर

#अगर_अघोषित __HAVE_ARCH_MEMSCAN
/**
 * memscan - Find a अक्षरacter in an area of memory.
 * @addr: The memory area
 * @c: The byte to search क्रम
 * @size: The size of the area.
 *
 * वापसs the address of the first occurrence of @c, or 1 byte past
 * the area अगर @c is not found
 */
व्योम *memscan(व्योम *addr, पूर्णांक c, माप_प्रकार size)
अणु
	अचिन्हित अक्षर *p = addr;

	जबतक (size) अणु
		अगर (*p == c)
			वापस (व्योम *)p;
		p++;
		size--;
	पूर्ण
  	वापस (व्योम *)p;
पूर्ण
EXPORT_SYMBOL(memscan);
#पूर्ण_अगर

#अगर_अघोषित __HAVE_ARCH_STRSTR
/**
 * म_माला - Find the first substring in a %NUL terminated string
 * @s1: The string to be searched
 * @s2: The string to search क्रम
 */
अक्षर *म_माला(स्थिर अक्षर *s1, स्थिर अक्षर *s2)
अणु
	माप_प्रकार l1, l2;

	l2 = म_माप(s2);
	अगर (!l2)
		वापस (अक्षर *)s1;
	l1 = म_माप(s1);
	जबतक (l1 >= l2) अणु
		l1--;
		अगर (!स_भेद(s1, s2, l2))
			वापस (अक्षर *)s1;
		s1++;
	पूर्ण
	वापस शून्य;
पूर्ण
EXPORT_SYMBOL(म_माला);
#पूर्ण_अगर

#अगर_अघोषित __HAVE_ARCH_STRNSTR
/**
 * strnstr - Find the first substring in a length-limited string
 * @s1: The string to be searched
 * @s2: The string to search क्रम
 * @len: the maximum number of अक्षरacters to search
 */
अक्षर *strnstr(स्थिर अक्षर *s1, स्थिर अक्षर *s2, माप_प्रकार len)
अणु
	माप_प्रकार l2;

	l2 = म_माप(s2);
	अगर (!l2)
		वापस (अक्षर *)s1;
	जबतक (len >= l2) अणु
		len--;
		अगर (!स_भेद(s1, s2, l2))
			वापस (अक्षर *)s1;
		s1++;
	पूर्ण
	वापस शून्य;
पूर्ण
EXPORT_SYMBOL(strnstr);
#पूर्ण_अगर

#अगर_अघोषित __HAVE_ARCH_MEMCHR
/**
 * स_प्रथम - Find a अक्षरacter in an area of memory.
 * @s: The memory area
 * @c: The byte to search क्रम
 * @n: The size of the area.
 *
 * वापसs the address of the first occurrence of @c, or %शून्य
 * अगर @c is not found
 */
व्योम *स_प्रथम(स्थिर व्योम *s, पूर्णांक c, माप_प्रकार n)
अणु
	स्थिर अचिन्हित अक्षर *p = s;
	जबतक (n-- != 0) अणु
        	अगर ((अचिन्हित अक्षर)c == *p++) अणु
			वापस (व्योम *)(p - 1);
		पूर्ण
	पूर्ण
	वापस शून्य;
पूर्ण
EXPORT_SYMBOL(स_प्रथम);
#पूर्ण_अगर

अटल व्योम *check_bytes8(स्थिर u8 *start, u8 value, अचिन्हित पूर्णांक bytes)
अणु
	जबतक (bytes) अणु
		अगर (*start != value)
			वापस (व्योम *)start;
		start++;
		bytes--;
	पूर्ण
	वापस शून्य;
पूर्ण

/**
 * स_प्रथम_inv - Find an unmatching अक्षरacter in an area of memory.
 * @start: The memory area
 * @c: Find a अक्षरacter other than c
 * @bytes: The size of the area.
 *
 * वापसs the address of the first अक्षरacter other than @c, or %शून्य
 * अगर the whole buffer contains just @c.
 */
व्योम *स_प्रथम_inv(स्थिर व्योम *start, पूर्णांक c, माप_प्रकार bytes)
अणु
	u8 value = c;
	u64 value64;
	अचिन्हित पूर्णांक words, prefix;

	अगर (bytes <= 16)
		वापस check_bytes8(start, value, bytes);

	value64 = value;
#अगर defined(CONFIG_ARCH_HAS_FAST_MULTIPLIER) && BITS_PER_LONG == 64
	value64 *= 0x0101010101010101ULL;
#या_अगर defined(CONFIG_ARCH_HAS_FAST_MULTIPLIER)
	value64 *= 0x01010101;
	value64 |= value64 << 32;
#अन्यथा
	value64 |= value64 << 8;
	value64 |= value64 << 16;
	value64 |= value64 << 32;
#पूर्ण_अगर

	prefix = (अचिन्हित दीर्घ)start % 8;
	अगर (prefix) अणु
		u8 *r;

		prefix = 8 - prefix;
		r = check_bytes8(start, value, prefix);
		अगर (r)
			वापस r;
		start += prefix;
		bytes -= prefix;
	पूर्ण

	words = bytes / 8;

	जबतक (words) अणु
		अगर (*(u64 *)start != value64)
			वापस check_bytes8(start, value, 8);
		start += 8;
		words--;
	पूर्ण

	वापस check_bytes8(start, value, bytes % 8);
पूर्ण
EXPORT_SYMBOL(स_प्रथम_inv);

/**
 * strreplace - Replace all occurrences of अक्षरacter in string.
 * @s: The string to operate on.
 * @old: The अक्षरacter being replaced.
 * @new: The अक्षरacter @old is replaced with.
 *
 * Returns poपूर्णांकer to the nul byte at the end of @s.
 */
अक्षर *strreplace(अक्षर *s, अक्षर old, अक्षर new)
अणु
	क्रम (; *s; ++s)
		अगर (*s == old)
			*s = new;
	वापस s;
पूर्ण
EXPORT_SYMBOL(strreplace);

व्योम क्रमtअगरy_panic(स्थिर अक्षर *name)
अणु
	pr_emerg("detected buffer overflow in %s\n", name);
	BUG();
पूर्ण
EXPORT_SYMBOL(क्रमtअगरy_panic);
