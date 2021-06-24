<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/* -*- linux-c -*- ------------------------------------------------------- *
 *
 *   Copyright (C) 1991, 1992 Linus Torvalds
 *   Copyright 2007 rPath, Inc. - All Rights Reserved
 *
 * ----------------------------------------------------------------------- */

/*
 * Very basic string functions
 */

#समावेश <linux/types.h>
#समावेश <linux/compiler.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/सीमा.स>
#समावेश <यंत्र/यंत्र.h>
#समावेश "ctype.h"
#समावेश "string.h"

#घोषणा KSTRTOX_OVERFLOW       (1U << 31)

/*
 * Undef these macros so that the functions that we provide
 * here will have the correct names regardless of how माला.स
 * may have chosen to #घोषणा them.
 */
#अघोषित स_नकल
#अघोषित स_रखो
#अघोषित स_भेद

पूर्णांक स_भेद(स्थिर व्योम *s1, स्थिर व्योम *s2, माप_प्रकार len)
अणु
	bool dअगरf;
	यंत्र("repe; cmpsb" CC_SET(nz)
	    : CC_OUT(nz) (dअगरf), "+D" (s1), "+S" (s2), "+c" (len));
	वापस dअगरf;
पूर्ण

/*
 * Clang may lower `स_भेद == 0` to `bcmp == 0`.
 */
पूर्णांक bcmp(स्थिर व्योम *s1, स्थिर व्योम *s2, माप_प्रकार len)
अणु
	वापस स_भेद(s1, s2, len);
पूर्ण

पूर्णांक म_भेद(स्थिर अक्षर *str1, स्थिर अक्षर *str2)
अणु
	स्थिर अचिन्हित अक्षर *s1 = (स्थिर अचिन्हित अक्षर *)str1;
	स्थिर अचिन्हित अक्षर *s2 = (स्थिर अचिन्हित अक्षर *)str2;
	पूर्णांक delta = 0;

	जबतक (*s1 || *s2) अणु
		delta = *s1 - *s2;
		अगर (delta)
			वापस delta;
		s1++;
		s2++;
	पूर्ण
	वापस 0;
पूर्ण

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

माप_प्रकार strnlen(स्थिर अक्षर *s, माप_प्रकार maxlen)
अणु
	स्थिर अक्षर *es = s;
	जबतक (*es && maxlen) अणु
		es++;
		maxlen--;
	पूर्ण

	वापस (es - s);
पूर्ण

अचिन्हित पूर्णांक atou(स्थिर अक्षर *s)
अणु
	अचिन्हित पूर्णांक i = 0;
	जबतक (है_अंक(*s))
		i = i * 10 + (*s++ - '0');
	वापस i;
पूर्ण

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

/**
 * म_अक्षर - Find the first occurrence of the अक्षरacter c in the string s.
 * @s: the string to be searched
 * @c: the अक्षरacter to search क्रम
 */
अक्षर *म_अक्षर(स्थिर अक्षर *s, पूर्णांक c)
अणु
	जबतक (*s != (अक्षर)c)
		अगर (*s++ == '\0')
			वापस शून्य;
	वापस (अक्षर *)s;
पूर्ण

अटल अंतरभूत u64 __भाग_u64_rem(u64 भागidend, u32 भागisor, u32 *reमुख्यder)
अणु
	जोड़ अणु
		u64 v64;
		u32 v32[2];
	पूर्ण d = अणु भागidend पूर्ण;
	u32 upper;

	upper = d.v32[1];
	d.v32[1] = 0;
	अगर (upper >= भागisor) अणु
		d.v32[1] = upper / भागisor;
		upper %= भागisor;
	पूर्ण
	यंत्र ("divl %2" : "=a" (d.v32[0]), "=d" (*reमुख्यder) :
		"rm" (भागisor), "0" (d.v32[0]), "1" (upper));
	वापस d.v64;
पूर्ण

अटल अंतरभूत u64 __भाग_u64(u64 भागidend, u32 भागisor)
अणु
	u32 reमुख्यder;

	वापस __भाग_u64_rem(भागidend, भागisor, &reमुख्यder);
पूर्ण

अटल अंतरभूत अक्षर _छोटे(स्थिर अक्षर c)
अणु
	वापस c | 0x20;
पूर्ण

अटल स्थिर अक्षर *_parse_पूर्णांकeger_fixup_radix(स्थिर अक्षर *s, अचिन्हित पूर्णांक *base)
अणु
	अगर (*base == 0) अणु
		अगर (s[0] == '0') अणु
			अगर (_छोटे(s[1]) == 'x' && है_षष्ठादशक(s[2]))
				*base = 16;
			अन्यथा
				*base = 8;
		पूर्ण अन्यथा
			*base = 10;
	पूर्ण
	अगर (*base == 16 && s[0] == '0' && _tolower(s[1]) == 'x')
		s += 2;
	वापस s;
पूर्ण

/*
 * Convert non-negative पूर्णांकeger string representation in explicitly given radix
 * to an पूर्णांकeger.
 * Return number of अक्षरacters consumed maybe or-ed with overflow bit.
 * If overflow occurs, result पूर्णांकeger (incorrect) is still वापसed.
 *
 * Don't you dare use this function.
 */
अटल अचिन्हित पूर्णांक _parse_पूर्णांकeger(स्थिर अक्षर *s,
				   अचिन्हित पूर्णांक base,
				   अचिन्हित दीर्घ दीर्घ *p)
अणु
	अचिन्हित दीर्घ दीर्घ res;
	अचिन्हित पूर्णांक rv;

	res = 0;
	rv = 0;
	जबतक (1) अणु
		अचिन्हित पूर्णांक c = *s;
		अचिन्हित पूर्णांक lc = c | 0x20; /* करोn't छोटे() this line */
		अचिन्हित पूर्णांक val;

		अगर ('0' <= c && c <= '9')
			val = c - '0';
		अन्यथा अगर ('a' <= lc && lc <= 'f')
			val = lc - 'a' + 10;
		अन्यथा
			अवरोध;

		अगर (val >= base)
			अवरोध;
		/*
		 * Check क्रम overflow only अगर we are within range of
		 * it in the max base we support (16)
		 */
		अगर (unlikely(res & (~0ull << 60))) अणु
			अगर (res > __भाग_u64(ULदीर्घ_उच्च - val, base))
				rv |= KSTRTOX_OVERFLOW;
		पूर्ण
		res = res * base + val;
		rv++;
		s++;
	पूर्ण
	*p = res;
	वापस rv;
पूर्ण

अटल पूर्णांक _kम_से_अदीर्घl(स्थिर अक्षर *s, अचिन्हित पूर्णांक base, अचिन्हित दीर्घ दीर्घ *res)
अणु
	अचिन्हित दीर्घ दीर्घ _res;
	अचिन्हित पूर्णांक rv;

	s = _parse_पूर्णांकeger_fixup_radix(s, &base);
	rv = _parse_पूर्णांकeger(s, base, &_res);
	अगर (rv & KSTRTOX_OVERFLOW)
		वापस -दुस्फल;
	अगर (rv == 0)
		वापस -EINVAL;
	s += rv;
	अगर (*s == '\n')
		s++;
	अगर (*s)
		वापस -EINVAL;
	*res = _res;
	वापस 0;
पूर्ण

/**
 * kम_से_अदीर्घl - convert a string to an अचिन्हित दीर्घ दीर्घ
 * @s: The start of the string. The string must be null-terminated, and may also
 *  include a single newline beक्रमe its terminating null. The first अक्षरacter
 *  may also be a plus sign, but not a minus sign.
 * @base: The number base to use. The maximum supported base is 16. If base is
 *  given as 0, then the base of the string is स्वतःmatically detected with the
 *  conventional semantics - If it begins with 0x the number will be parsed as a
 *  hexadecimal (हाल insensitive), अगर it otherwise begins with 0, it will be
 *  parsed as an octal number. Otherwise it will be parsed as a decimal.
 * @res: Where to ग_लिखो the result of the conversion on success.
 *
 * Returns 0 on success, -दुस्फल on overflow and -EINVAL on parsing error.
 * Used as a replacement क्रम the obsolete simple_म_से_अदीर्घl. Return code must
 * be checked.
 */
पूर्णांक kम_से_अदीर्घl(स्थिर अक्षर *s, अचिन्हित पूर्णांक base, अचिन्हित दीर्घ दीर्घ *res)
अणु
	अगर (s[0] == '+')
		s++;
	वापस _kम_से_अदीर्घl(s, base, res);
पूर्ण

अटल पूर्णांक _kम_से_अदीर्घ(स्थिर अक्षर *s, अचिन्हित पूर्णांक base, अचिन्हित दीर्घ *res)
अणु
	अचिन्हित दीर्घ दीर्घ पंचांगp;
	पूर्णांक rv;

	rv = kम_से_अदीर्घl(s, base, &पंचांगp);
	अगर (rv < 0)
		वापस rv;
	अगर (पंचांगp != (अचिन्हित दीर्घ)पंचांगp)
		वापस -दुस्फल;
	*res = पंचांगp;
	वापस 0;
पूर्ण

/**
 * kम_से_अदीर्घ - convert a string to an अचिन्हित दीर्घ
 * @s: The start of the string. The string must be null-terminated, and may also
 *  include a single newline beक्रमe its terminating null. The first अक्षरacter
 *  may also be a plus sign, but not a minus sign.
 * @base: The number base to use. The maximum supported base is 16. If base is
 *  given as 0, then the base of the string is स्वतःmatically detected with the
 *  conventional semantics - If it begins with 0x the number will be parsed as a
 *  hexadecimal (हाल insensitive), अगर it otherwise begins with 0, it will be
 *  parsed as an octal number. Otherwise it will be parsed as a decimal.
 * @res: Where to ग_लिखो the result of the conversion on success.
 *
 * Returns 0 on success, -दुस्फल on overflow and -EINVAL on parsing error.
 * Used as a replacement क्रम the simple_म_से_अदीर्घl.
 */
पूर्णांक boot_kम_से_अदीर्घ(स्थिर अक्षर *s, अचिन्हित पूर्णांक base, अचिन्हित दीर्घ *res)
अणु
	/*
	 * We want to लघुcut function call, but
	 * __builtin_types_compatible_p(अचिन्हित दीर्घ, अचिन्हित दीर्घ दीर्घ) = 0.
	 */
	अगर (माप(अचिन्हित दीर्घ) == माप(अचिन्हित दीर्घ दीर्घ) &&
	    __alignof__(अचिन्हित दीर्घ) == __alignof__(अचिन्हित दीर्घ दीर्घ))
		वापस kम_से_अदीर्घl(s, base, (अचिन्हित दीर्घ दीर्घ *)res);
	अन्यथा
		वापस _kम_से_अदीर्घ(s, base, res);
पूर्ण
