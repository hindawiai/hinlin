<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Copyright (C) Paul Mackerras 1997.
 */
#समावेश <मानकतर्क.स>
#समावेश <मानकघोष.स>

माप_प्रकार strnlen(स्थिर अक्षर * s, माप_प्रकार count)
अणु
	स्थिर अक्षर *sc;

	क्रम (sc = s; count-- && *sc != '\0'; ++sc)
		/* nothing */;
	वापस sc - s;
पूर्ण

# define करो_भाग(n, base) (अणु						\
	अचिन्हित पूर्णांक __base = (base);					\
	अचिन्हित पूर्णांक __rem;						\
	__rem = ((अचिन्हित दीर्घ दीर्घ)(n)) % __base;			\
	(n) = ((अचिन्हित दीर्घ दीर्घ)(n)) / __base;			\
	__rem;								\
पूर्ण)


अटल पूर्णांक skip_म_से_प(स्थिर अक्षर **s)
अणु
	पूर्णांक i, c;

	क्रम (i = 0; '0' <= (c = **s) && c <= '9'; ++*s)
		i = i*10 + c - '0';
	वापस i;
पूर्ण

#घोषणा ZEROPAD	1		/* pad with zero */
#घोषणा SIGN	2		/* अचिन्हित/चिन्हित दीर्घ */
#घोषणा PLUS	4		/* show plus */
#घोषणा SPACE	8		/* space अगर plus */
#घोषणा LEFT	16		/* left justअगरied */
#घोषणा SPECIAL	32		/* 0x */
#घोषणा LARGE	64		/* use 'ABCDEF' instead of 'abcdef' */

अटल अक्षर * number(अक्षर * str, अचिन्हित दीर्घ दीर्घ num, पूर्णांक base, पूर्णांक size, पूर्णांक precision, पूर्णांक type)
अणु
	अक्षर c,sign,पंचांगp[66];
	स्थिर अक्षर *digits="0123456789abcdefghijklmnopqrstuvwxyz";
	पूर्णांक i;

	अगर (type & LARGE)
		digits = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";
	अगर (type & LEFT)
		type &= ~ZEROPAD;
	अगर (base < 2 || base > 36)
		वापस 0;
	c = (type & ZEROPAD) ? '0' : ' ';
	sign = 0;
	अगर (type & SIGN) अणु
		अगर ((चिन्हित दीर्घ दीर्घ)num < 0) अणु
			sign = '-';
			num = - (चिन्हित दीर्घ दीर्घ)num;
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
		पंचांगp[i++]='0';
	अन्यथा जबतक (num != 0) अणु
		पंचांगp[i++] = digits[करो_भाग(num, base)];
	पूर्ण
	अगर (i > precision)
		precision = i;
	size -= precision;
	अगर (!(type&(ZEROPAD+LEFT)))
		जबतक(size-->0)
			*str++ = ' ';
	अगर (sign)
		*str++ = sign;
	अगर (type & SPECIAL) अणु
		अगर (base==8)
			*str++ = '0';
		अन्यथा अगर (base==16) अणु
			*str++ = '0';
			*str++ = digits[33];
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
	अचिन्हित दीर्घ दीर्घ num;
	पूर्णांक i, base;
	अक्षर * str;
	स्थिर अक्षर *s;

	पूर्णांक flags;		/* flags to number() */

	पूर्णांक field_width;	/* width of output field */
	पूर्णांक precision;		/* min. # of digits क्रम पूर्णांकegers; max
				   number of अक्षरs क्रम from string */
	पूर्णांक qualअगरier;		/* 'h', 'l', or 'L' क्रम पूर्णांकeger fields */
	                        /* 'z' support added 23/7/1999 S.H.    */
				/* 'z' changed to 'Z' --davidm 1/25/99 */


	क्रम (str=buf ; *fmt ; ++fmt) अणु
		अगर (*fmt != '%') अणु
			*str++ = *fmt;
			जारी;
		पूर्ण

		/* process flags */
		flags = 0;
		repeat:
			++fmt;		/* this also skips first '%' */
			चयन (*fmt) अणु
				हाल '-': flags |= LEFT; जाओ repeat;
				हाल '+': flags |= PLUS; जाओ repeat;
				हाल ' ': flags |= SPACE; जाओ repeat;
				हाल '#': flags |= SPECIAL; जाओ repeat;
				हाल '0': flags |= ZEROPAD; जाओ repeat;
				पूर्ण

		/* get field width */
		field_width = -1;
		अगर ('0' <= *fmt && *fmt <= '9')
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
			अगर ('0' <= *fmt && *fmt <= '9')
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
		अगर (*fmt == 'l' && *(fmt + 1) == 'l') अणु
			qualअगरier = 'q';
			fmt += 2;
		पूर्ण अन्यथा अगर (*fmt == 'h' || *fmt == 'l' || *fmt == 'L'
			|| *fmt == 'Z') अणु
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
			*str++ = (अचिन्हित अक्षर) बहु_तर्क(args, पूर्णांक);
			जबतक (--field_width > 0)
				*str++ = ' ';
			जारी;

		हाल 's':
			s = बहु_तर्क(args, अक्षर *);
			अगर (!s)
				s = "<NULL>";

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
				field_width = 2*माप(व्योम *);
				flags |= ZEROPAD;
			पूर्ण
			str = number(str,
				(अचिन्हित दीर्घ) बहु_तर्क(args, व्योम *), 16,
				field_width, precision, flags);
			जारी;


		हाल 'n':
			अगर (qualअगरier == 'l') अणु
				दीर्घ * ip = बहु_तर्क(args, दीर्घ *);
				*ip = (str - buf);
			पूर्ण अन्यथा अगर (qualअगरier == 'Z') अणु
				माप_प्रकार * ip = बहु_तर्क(args, माप_प्रकार *);
				*ip = (str - buf);
			पूर्ण अन्यथा अणु
				पूर्णांक * ip = बहु_तर्क(args, पूर्णांक *);
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

		हाल 'X':
			flags |= LARGE;
		हाल 'x':
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
		अगर (qualअगरier == 'l') अणु
			num = बहु_तर्क(args, अचिन्हित दीर्घ);
			अगर (flags & SIGN)
				num = (चिन्हित दीर्घ) num;
		पूर्ण अन्यथा अगर (qualअगरier == 'q') अणु
			num = बहु_तर्क(args, अचिन्हित दीर्घ दीर्घ);
			अगर (flags & SIGN)
				num = (चिन्हित दीर्घ दीर्घ) num;
		पूर्ण अन्यथा अगर (qualअगरier == 'Z') अणु
			num = बहु_तर्क(args, माप_प्रकार);
		पूर्ण अन्यथा अगर (qualअगरier == 'h') अणु
			num = (अचिन्हित लघु) बहु_तर्क(args, पूर्णांक);
			अगर (flags & SIGN)
				num = (चिन्हित लघु) num;
		पूर्ण अन्यथा अणु
			num = बहु_तर्क(args, अचिन्हित पूर्णांक);
			अगर (flags & SIGN)
				num = (चिन्हित पूर्णांक) num;
		पूर्ण
		str = number(str, num, base, field_width, precision, flags);
	पूर्ण
	*str = '\0';
	वापस str-buf;
पूर्ण

पूर्णांक प्र_लिखो(अक्षर * buf, स्थिर अक्षर *fmt, ...)
अणु
	बहु_सूची args;
	पूर्णांक i;

	बहु_शुरू(args, fmt);
	i=भम_लिखो(buf,fmt,args);
	बहु_पूर्ण(args);
	वापस i;
पूर्ण
