<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 *  linux/tools/lib/string.c
 *
 *  Copied from linux/lib/string.c, where it is:
 *
 *  Copyright (C) 1991, 1992  Linus Torvalds
 *
 *  More specअगरically, the first copied function was strtobool, which
 *  was पूर्णांकroduced by:
 *
 *  d0f1fed29e6e ("Add a strtobool function matching semantics of existing in kernel equivalents")
 *  Author: Jonathan Cameron <jic23@cam.ac.uk>
 */

#समावेश <मानककोष.स>
#समावेश <माला.स>
#समावेश <त्रुटिसं.स>
#समावेश <linux/माला.स>
#समावेश <linux/प्रकार.स>
#समावेश <linux/compiler.h>

/**
 * memdup - duplicate region of memory
 *
 * @src: memory region to duplicate
 * @len: memory region length
 */
व्योम *memdup(स्थिर व्योम *src, माप_प्रकार len)
अणु
	व्योम *p = दो_स्मृति(len);

	अगर (p)
		स_नकल(p, src, len);

	वापस p;
पूर्ण

/**
 * strtobool - convert common user inमाला_दो पूर्णांकo boolean values
 * @s: input string
 * @res: result
 *
 * This routine वापसs 0 अगरf the first अक्षरacter is one of 'Yy1Nn0', or
 * [oO][NnFf] क्रम "on" and "off". Otherwise it will वापस -EINVAL.  Value
 * poपूर्णांकed to by res is updated upon finding a match.
 */
पूर्णांक strtobool(स्थिर अक्षर *s, bool *res)
अणु
	अगर (!s)
		वापस -EINVAL;

	चयन (s[0]) अणु
	हाल 'y':
	हाल 'Y':
	हाल '1':
		*res = true;
		वापस 0;
	हाल 'n':
	हाल 'N':
	हाल '0':
		*res = false;
		वापस 0;
	हाल 'o':
	हाल 'O':
		चयन (s[1]) अणु
		हाल 'n':
		हाल 'N':
			*res = true;
			वापस 0;
		हाल 'f':
		हाल 'F':
			*res = false;
			वापस 0;
		शेष:
			अवरोध;
		पूर्ण
	शेष:
		अवरोध;
	पूर्ण

	वापस -EINVAL;
पूर्ण

/**
 * strlcpy - Copy a C-string पूर्णांकo a sized buffer
 * @dest: Where to copy the string to
 * @src: Where to copy the string from
 * @size: size of destination buffer
 *
 * Compatible with *BSD: the result is always a valid
 * NUL-terminated string that fits in the buffer (unless,
 * of course, the buffer size is zero). It करोes not pad
 * out the result like म_नकलन() करोes.
 *
 * If libc has strlcpy() then that version will override this
 * implementation:
 */
#अगर_घोषित __clang__
#आशय clang diagnostic push
#आशय clang diagnostic ignored "-Wignored-attributes"
#पूर्ण_अगर
माप_प्रकार __weak strlcpy(अक्षर *dest, स्थिर अक्षर *src, माप_प्रकार size)
अणु
	माप_प्रकार ret = म_माप(src);

	अगर (size) अणु
		माप_प्रकार len = (ret >= size) ? size - 1 : ret;
		स_नकल(dest, src, len);
		dest[len] = '\0';
	पूर्ण
	वापस ret;
पूर्ण
#अगर_घोषित __clang__
#आशय clang diagnostic pop
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
	value64 |= value64 << 8;
	value64 |= value64 << 16;
	value64 |= value64 << 32;

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
