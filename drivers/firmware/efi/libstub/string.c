<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Taken from:
 *  linux/lib/string.c
 *
 *  Copyright (C) 1991, 1992  Linus Torvalds
 */

#समावेश <linux/प्रकार.स>
#समावेश <linux/kernel.h>
#समावेश <linux/types.h>
#समावेश <linux/माला.स>

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
#पूर्ण_अगर

/* Works only क्रम digits and letters, but small and fast */
#घोषणा TOLOWER(x) ((x) | 0x20)

अटल अचिन्हित पूर्णांक simple_guess_base(स्थिर अक्षर *cp)
अणु
	अगर (cp[0] == '0') अणु
		अगर (TOLOWER(cp[1]) == 'x' && है_षष्ठादशक(cp[2]))
			वापस 16;
		अन्यथा
			वापस 8;
	पूर्ण अन्यथा अणु
		वापस 10;
	पूर्ण
पूर्ण

/**
 * simple_म_से_अदीर्घl - convert a string to an अचिन्हित दीर्घ दीर्घ
 * @cp: The start of the string
 * @endp: A poपूर्णांकer to the end of the parsed string will be placed here
 * @base: The number base to use
 */

अचिन्हित दीर्घ दीर्घ simple_म_से_अदीर्घl(स्थिर अक्षर *cp, अक्षर **endp, अचिन्हित पूर्णांक base)
अणु
	अचिन्हित दीर्घ दीर्घ result = 0;

	अगर (!base)
		base = simple_guess_base(cp);

	अगर (base == 16 && cp[0] == '0' && TOLOWER(cp[1]) == 'x')
		cp += 2;

	जबतक (है_षष्ठादशक(*cp)) अणु
		अचिन्हित पूर्णांक value;

		value = है_अंक(*cp) ? *cp - '0' : TOLOWER(*cp) - 'a' + 10;
		अगर (value >= base)
			अवरोध;
		result = result * base + value;
		cp++;
	पूर्ण
	अगर (endp)
		*endp = (अक्षर *)cp;

	वापस result;
पूर्ण

दीर्घ simple_म_से_दीर्घ(स्थिर अक्षर *cp, अक्षर **endp, अचिन्हित पूर्णांक base)
अणु
	अगर (*cp == '-')
		वापस -simple_म_से_अदीर्घl(cp + 1, endp, base);

	वापस simple_म_से_अदीर्घl(cp, endp, base);
पूर्ण
