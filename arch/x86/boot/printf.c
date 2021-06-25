<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/* -*- linux-c -*- ------------------------------------------------------- *
 *
 *   Copyright (C) 1991, 1992 Linus Torvalds
 *   Copyright 2007 rPath, Inc. - All Rights Reserved
 *
 * ----------------------------------------------------------------------- */

/*
 * Oh, it's a waste of space, but oh-so-yummy क्रम debugging.  This
 * version of म_लिखो() करोes not include 64-bit support.  "Live with
 * it."
 *
 */

#समावेश "boot.h"

अटल पूर्णांक skip_म_से_प(स्थिर अक्षर **s)
अणु
	पूर्णांक i = 0;

	जबतक (है_अंक(**s))
		i = i * 10 + *((*s)++) - '0';
	वापस i;
पूर्ण

#घोषणा ZEROPAD	1		/* pad with zero */
#घोषणा SIGN	2		/* अचिन्हित/चिन्हित दीर्घ */
#घोषणा PLUS	4		/* show plus */
#घोषणा SPACE	8		/* space अगर plus */
#घोषणा LEFT	16		/* left justअगरied */
#घोषणा SMALL	32		/* Must be 32 == 0x20 */
#घोषणा SPECIAL	64		/* 0x */

#घोषणा __करो_भाग(n, base) (अणु \
पूर्णांक __res; \
__res = ((अचिन्हित दीर्घ) n) % (अचिन्हित) base; \
n = ((अचिन्हित दीर्घ) n) / (अचिन्हित) base; \
__res; पूर्ण)

अटल अक्षर *number(अक्षर *str, दीर्घ num, पूर्णांक base, पूर्णांक size, पूर्णांक precision,
		    पूर्णांक type)
अणु
	/* we are called with base 8, 10 or 16, only, thus करोn't need "G..."  */
	अटल स्थिर अक्षर digits[16] = "0123456789ABCDEF"; /* "GHIJKLMNOPQRSTUVWXYZ"; */

	अक्षर पंचांगp[66];
	अक्षर c, sign, loहाल;
	पूर्णांक i;

	/* loहाल = 0 or 0x20. ORing digits or letters with 'locase'
	 * produces same digits or (maybe lowerहालd) letters */
	loहाल = (type & SMALL);
	अगर (type & LEFT)
		type &= ~ZEROPAD;
	अगर (base < 2 || base > 16)
		वापस शून्य;
	c = (type & ZEROPAD) ? '0' : ' ';
	sign = 0;
	अगर (type & SIGN) अणु
		अगर (num < 0) अणु
			sign = '-';
			num = -num;
			size--;
		पूर्ण अन्यथा अगर (type & PLUS) अणु
			sign = '+';
			size--;
		पूर्ण अन्यथा अगर (type & SPACE) अणु
			sign = ' ';
			size--;
		पूर्ण
	पूर्ण
	अगर (type & SPECIAL) अणु
		अगर (base == 16)
			size -= 2;
		अन्यथा अगर (base == 8)
			size--;
	पूर्ण
	i = 0;
	अगर (num == 0)
		पंचांगp[i++] = '0';
	अन्यथा
		जबतक (num != 0)
			पंचांगp[i++] = (digits[__करो_भाग(num, base)] | loहाल);
	अगर (i > precision)
		precision = i;
	size -= precision;
	अगर (!(type & (ZEROPAD + LEFT)))
		जबतक (size-- > 0)
			*str++ = ' ';
	अगर (sign)
		*str++ = sign;
	अगर (type & SPECIAL) अणु
		अगर (base == 8)
			*str++ = '0';
		अन्यथा अगर (base == 16) अणु
			*str++ = '0';
			*str++ = ('X' | loहाल);
		पूर्ण
	पूर्ण
	अगर (!(type & LEFT))
		जबतक (size-- > 0)
			*str++ = c;
	जबतक (i < precision--)
		*str++ = '0';
	जबतक (i-- > 0)
		*str++ = पंचांगp[i];
	जबतक (size-- > 0)
		*str++ = ' ';
	वापस str;
पूर्ण

पूर्णांक भम_लिखो(अक्षर *buf, स्थिर अक्षर *fmt, बहु_सूची args)
अणु
	पूर्णांक len;
	अचिन्हित दीर्घ num;
	पूर्णांक i, base;
	अक्षर *str;
	स्थिर अक्षर *s;

	पूर्णांक flags;		/* flags to number() */

	पूर्णांक field_width;	/* width of output field */
	पूर्णांक precision;		/* min. # of digits क्रम पूर्णांकegers; max
				   number of अक्षरs क्रम from string */
	पूर्णांक qualअगरier;		/* 'h', 'l', or 'L' क्रम पूर्णांकeger fields */

	क्रम (str = buf; *fmt; ++fmt) अणु
		अगर (*fmt != '%') अणु
			*str++ = *fmt;
			जारी;
		पूर्ण

		/* process flags */
		flags = 0;
	      repeat:
		++fmt;		/* this also skips first '%' */
		चयन (*fmt) अणु
		हाल '-':
			flags |= LEFT;
			जाओ repeat;
		हाल '+':
			flags |= PLUS;
			जाओ repeat;
		हाल ' ':
			flags |= SPACE;
			जाओ repeat;
		हाल '#':
			flags |= SPECIAL;
			जाओ repeat;
		हाल '0':
			flags |= ZEROPAD;
			जाओ repeat;
		पूर्ण

		/* get field width */
		field_width = -1;
		अगर (है_अंक(*fmt))
			field_width = skip_म_से_प(&fmt);
		अन्यथा अगर (*fmt == '*') अणु
			++fmt;
			/* it's the next argument */
			field_width = बहु_तर्क(args, पूर्णांक);
			अगर (field_width < 0) अणु
				field_width = -field_width;
				flags |= LEFT;
			पूर्ण
		पूर्ण

		/* get the precision */
		precision = -1;
		अगर (*fmt == '.') अणु
			++fmt;
			अगर (है_अंक(*fmt))
				precision = skip_म_से_प(&fmt);
			अन्यथा अगर (*fmt == '*') अणु
				++fmt;
				/* it's the next argument */
				precision = बहु_तर्क(args, पूर्णांक);
			पूर्ण
			अगर (precision < 0)
				precision = 0;
		पूर्ण

		/* get the conversion qualअगरier */
		qualअगरier = -1;
		अगर (*fmt == 'h' || *fmt == 'l' || *fmt == 'L') अणु
			qualअगरier = *fmt;
			++fmt;
		पूर्ण

		/* शेष base */
		base = 10;

		चयन (*fmt) अणु
		हाल 'c':
			अगर (!(flags & LEFT))
				जबतक (--field_width > 0)
					*str++ = ' ';
			*str++ = (अचिन्हित अक्षर)बहु_तर्क(args, पूर्णांक);
			जबतक (--field_width > 0)
				*str++ = ' ';
			जारी;

		हाल 's':
			s = बहु_तर्क(args, अक्षर *);
			len = strnlen(s, precision);

			अगर (!(flags & LEFT))
				जबतक (len < field_width--)
					*str++ = ' ';
			क्रम (i = 0; i < len; ++i)
				*str++ = *s++;
			जबतक (len < field_width--)
				*str++ = ' ';
			जारी;

		हाल 'p':
			अगर (field_width == -1) अणु
				field_width = 2 * माप(व्योम *);
				flags |= ZEROPAD;
			पूर्ण
			str = number(str,
				     (अचिन्हित दीर्घ)बहु_तर्क(args, व्योम *), 16,
				     field_width, precision, flags);
			जारी;

		हाल 'n':
			अगर (qualअगरier == 'l') अणु
				दीर्घ *ip = बहु_तर्क(args, दीर्घ *);
				*ip = (str - buf);
			पूर्ण अन्यथा अणु
				पूर्णांक *ip = बहु_तर्क(args, पूर्णांक *);
				*ip = (str - buf);
			पूर्ण
			जारी;

		हाल '%':
			*str++ = '%';
			जारी;

			/* पूर्णांकeger number क्रमmats - set up the flags and "break" */
		हाल 'o':
			base = 8;
			अवरोध;

		हाल 'x':
			flags |= SMALL;
		हाल 'X':
			base = 16;
			अवरोध;

		हाल 'd':
		हाल 'i':
			flags |= SIGN;
		हाल 'u':
			अवरोध;

		शेष:
			*str++ = '%';
			अगर (*fmt)
				*str++ = *fmt;
			अन्यथा
				--fmt;
			जारी;
		पूर्ण
		अगर (qualअगरier == 'l')
			num = बहु_तर्क(args, अचिन्हित दीर्घ);
		अन्यथा अगर (qualअगरier == 'h') अणु
			num = (अचिन्हित लघु)बहु_तर्क(args, पूर्णांक);
			अगर (flags & SIGN)
				num = (लघु)num;
		पूर्ण अन्यथा अगर (flags & SIGN)
			num = बहु_तर्क(args, पूर्णांक);
		अन्यथा
			num = बहु_तर्क(args, अचिन्हित पूर्णांक);
		str = number(str, num, base, field_width, precision, flags);
	पूर्ण
	*str = '\0';
	वापस str - buf;
पूर्ण

पूर्णांक प्र_लिखो(अक्षर *buf, स्थिर अक्षर *fmt, ...)
अणु
	बहु_सूची args;
	पूर्णांक i;

	बहु_शुरू(args, fmt);
	i = भम_लिखो(buf, fmt, args);
	बहु_पूर्ण(args);
	वापस i;
पूर्ण

पूर्णांक म_लिखो(स्थिर अक्षर *fmt, ...)
अणु
	अक्षर म_लिखो_buf[1024];
	बहु_सूची args;
	पूर्णांक prपूर्णांकed;

	बहु_शुरू(args, fmt);
	prपूर्णांकed = भम_लिखो(म_लिखो_buf, fmt, args);
	बहु_पूर्ण(args);

	माला_दो(म_लिखो_buf);

	वापस prपूर्णांकed;
पूर्ण
