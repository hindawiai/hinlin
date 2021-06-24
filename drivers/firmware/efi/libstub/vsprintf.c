<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/* -*- linux-c -*- ------------------------------------------------------- *
 *
 *   Copyright (C) 1991, 1992 Linus Torvalds
 *   Copyright 2007 rPath, Inc. - All Rights Reserved
 *
 * ----------------------------------------------------------------------- */

/*
 * Oh, it's a waste of space, but oh-so-yummy क्रम debugging.
 */

#समावेश <मानकतर्क.स>

#समावेश <linux/compiler.h>
#समावेश <linux/प्रकार.स>
#समावेश <linux/kernel.h>
#समावेश <linux/सीमा.स>
#समावेश <linux/माला.स>
#समावेश <linux/types.h>

अटल
पूर्णांक skip_म_से_प(स्थिर अक्षर **s)
अणु
	पूर्णांक i = 0;

	जबतक (है_अंक(**s))
		i = i * 10 + *((*s)++) - '0';
	वापस i;
पूर्ण

/*
 * put_dec_full4 handles numbers in the range 0 <= r < 10000.
 * The multiplier 0xccd is round(2^15/10), and the approximation
 * r/10 == (r * 0xccd) >> 15 is exact क्रम all r < 16389.
 */
अटल
व्योम put_dec_full4(अक्षर *end, अचिन्हित पूर्णांक r)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < 3; i++) अणु
		अचिन्हित पूर्णांक q = (r * 0xccd) >> 15;
		*--end = '0' + (r - q * 10);
		r = q;
	पूर्ण
	*--end = '0' + r;
पूर्ण

/* put_dec is copied from lib/भम_लिखो.c with small modअगरications */

/*
 * Call put_dec_full4 on x % 10000, वापस x / 10000.
 * The approximation x/10000 == (x * 0x346DC5D7) >> 43
 * holds क्रम all x < 1,128,869,999.  The largest value this
 * helper will ever be asked to convert is 1,125,520,955.
 * (second call in the put_dec code, assuming n is all-ones).
 */
अटल
अचिन्हित पूर्णांक put_dec_helper4(अक्षर *end, अचिन्हित पूर्णांक x)
अणु
	अचिन्हित पूर्णांक q = (x * 0x346DC5D7ULL) >> 43;

	put_dec_full4(end, x - q * 10000);
	वापस q;
पूर्ण

/* Based on code by Douglas W. Jones found at
 * <http://www.cs.uiowa.edu/~jones/bcd/decimal.hपंचांगl#sixtyfour>
 * (with permission from the author).
 * Perक्रमms no 64-bit भागision and hence should be fast on 32-bit machines.
 */
अटल
अक्षर *put_dec(अक्षर *end, अचिन्हित दीर्घ दीर्घ n)
अणु
	अचिन्हित पूर्णांक d3, d2, d1, q, h;
	अक्षर *p = end;

	d1  = ((अचिन्हित पूर्णांक)n >> 16); /* implicit "& 0xffff" */
	h   = (n >> 32);
	d2  = (h      ) & 0xffff;
	d3  = (h >> 16); /* implicit "& 0xffff" */

	/* n = 2^48 d3 + 2^32 d2 + 2^16 d1 + d0
	     = 281_4749_7671_0656 d3 + 42_9496_7296 d2 + 6_5536 d1 + d0 */
	q = 656 * d3 + 7296 * d2 + 5536 * d1 + ((अचिन्हित पूर्णांक)n & 0xffff);
	q = put_dec_helper4(p, q);
	p -= 4;

	q += 7671 * d3 + 9496 * d2 + 6 * d1;
	q = put_dec_helper4(p, q);
	p -= 4;

	q += 4749 * d3 + 42 * d2;
	q = put_dec_helper4(p, q);
	p -= 4;

	q += 281 * d3;
	q = put_dec_helper4(p, q);
	p -= 4;

	put_dec_full4(p, q);
	p -= 4;

	/* strip off the extra 0's we prपूर्णांकed */
	जबतक (p < end && *p == '0')
		++p;

	वापस p;
पूर्ण

अटल
अक्षर *number(अक्षर *end, अचिन्हित दीर्घ दीर्घ num, पूर्णांक base, अक्षर loहाल)
अणु
	/*
	 * loहाल = 0 or 0x20. ORing digits or letters with 'locase'
	 * produces same digits or (maybe lowerहालd) letters
	 */

	/* we are called with base 8, 10 or 16, only, thus करोn't need "G..."  */
	अटल स्थिर अक्षर digits[16] = "0123456789ABCDEF"; /* "GHIJKLMNOPQRSTUVWXYZ"; */

	चयन (base) अणु
	हाल 10:
		अगर (num != 0)
			end = put_dec(end, num);
		अवरोध;
	हाल 8:
		क्रम (; num != 0; num >>= 3)
			*--end = '0' + (num & 07);
		अवरोध;
	हाल 16:
		क्रम (; num != 0; num >>= 4)
			*--end = digits[num & 0xf] | loहाल;
		अवरोध;
	शेष:
		unreachable();
	पूर्ण

	वापस end;
पूर्ण

#घोषणा ZEROPAD	1		/* pad with zero */
#घोषणा SIGN	2		/* अचिन्हित/चिन्हित दीर्घ */
#घोषणा PLUS	4		/* show plus */
#घोषणा SPACE	8		/* space अगर plus */
#घोषणा LEFT	16		/* left justअगरied */
#घोषणा SMALL	32		/* Must be 32 == 0x20 */
#घोषणा SPECIAL	64		/* 0x */
#घोषणा WIDE	128		/* UTF-16 string */

अटल
पूर्णांक get_flags(स्थिर अक्षर **fmt)
अणु
	पूर्णांक flags = 0;

	करो अणु
		चयन (**fmt) अणु
		हाल '-':
			flags |= LEFT;
			अवरोध;
		हाल '+':
			flags |= PLUS;
			अवरोध;
		हाल ' ':
			flags |= SPACE;
			अवरोध;
		हाल '#':
			flags |= SPECIAL;
			अवरोध;
		हाल '0':
			flags |= ZEROPAD;
			अवरोध;
		शेष:
			वापस flags;
		पूर्ण
		++(*fmt);
	पूर्ण जबतक (1);
पूर्ण

अटल
पूर्णांक get_पूर्णांक(स्थिर अक्षर **fmt, बहु_सूची *ap)
अणु
	अगर (है_अंक(**fmt))
		वापस skip_म_से_प(fmt);
	अगर (**fmt == '*') अणु
		++(*fmt);
		/* it's the next argument */
		वापस बहु_तर्क(*ap, पूर्णांक);
	पूर्ण
	वापस 0;
पूर्ण

अटल
अचिन्हित दीर्घ दीर्घ get_number(पूर्णांक sign, पूर्णांक qualअगरier, बहु_सूची *ap)
अणु
	अगर (sign) अणु
		चयन (qualअगरier) अणु
		हाल 'L':
			वापस बहु_तर्क(*ap, दीर्घ दीर्घ);
		हाल 'l':
			वापस बहु_तर्क(*ap, दीर्घ);
		हाल 'h':
			वापस (लघु)बहु_तर्क(*ap, पूर्णांक);
		हाल 'H':
			वापस (चिन्हित अक्षर)बहु_तर्क(*ap, पूर्णांक);
		शेष:
			वापस बहु_तर्क(*ap, पूर्णांक);
		पूर्ण;
	पूर्ण अन्यथा अणु
		चयन (qualअगरier) अणु
		हाल 'L':
			वापस बहु_तर्क(*ap, अचिन्हित दीर्घ दीर्घ);
		हाल 'l':
			वापस बहु_तर्क(*ap, अचिन्हित दीर्घ);
		हाल 'h':
			वापस (अचिन्हित लघु)बहु_तर्क(*ap, पूर्णांक);
		हाल 'H':
			वापस (अचिन्हित अक्षर)बहु_तर्क(*ap, पूर्णांक);
		शेष:
			वापस बहु_तर्क(*ap, अचिन्हित पूर्णांक);
		पूर्ण
	पूर्ण
पूर्ण

अटल
अक्षर get_sign(दीर्घ दीर्घ *num, पूर्णांक flags)
अणु
	अगर (!(flags & SIGN))
		वापस 0;
	अगर (*num < 0) अणु
		*num = -(*num);
		वापस '-';
	पूर्ण
	अगर (flags & PLUS)
		वापस '+';
	अगर (flags & SPACE)
		वापस ' ';
	वापस 0;
पूर्ण

अटल
माप_प्रकार utf16s_utf8nlen(स्थिर u16 *s16, माप_प्रकार maxlen)
अणु
	माप_प्रकार len, clen;

	क्रम (len = 0; len < maxlen && *s16; len += clen) अणु
		u16 c0 = *s16++;

		/* First, get the length क्रम a BMP अक्षरacter */
		clen = 1 + (c0 >= 0x80) + (c0 >= 0x800);
		अगर (len + clen > maxlen)
			अवरोध;
		/*
		 * If this is a high surrogate, and we're alपढ़ोy at maxlen, we
		 * can't include the character if it's a valid surrogate pair.
		 * Aव्योम accessing one extra word just to check अगर it's valid
		 * or not.
		 */
		अगर ((c0 & 0xfc00) == 0xd800) अणु
			अगर (len + clen == maxlen)
				अवरोध;
			अगर ((*s16 & 0xfc00) == 0xdc00) अणु
				++s16;
				++clen;
			पूर्ण
		पूर्ण
	पूर्ण

	वापस len;
पूर्ण

अटल
u32 utf16_to_utf32(स्थिर u16 **s16)
अणु
	u16 c0, c1;

	c0 = *(*s16)++;
	/* not a surrogate */
	अगर ((c0 & 0xf800) != 0xd800)
		वापस c0;
	/* invalid: low surrogate instead of high */
	अगर (c0 & 0x0400)
		वापस 0xfffd;
	c1 = **s16;
	/* invalid: missing low surrogate */
	अगर ((c1 & 0xfc00) != 0xdc00)
		वापस 0xfffd;
	/* valid surrogate pair */
	++(*s16);
	वापस (0x10000 - (0xd800 << 10) - 0xdc00) + (c0 << 10) + c1;
पूर्ण

#घोषणा PUTC(c) \
करो अणु				\
	अगर (pos < size)		\
		buf[pos] = (c);	\
	++pos;			\
पूर्ण जबतक (0);

पूर्णांक vsnम_लिखो(अक्षर *buf, माप_प्रकार size, स्थिर अक्षर *fmt, बहु_सूची ap)
अणु
	/* The maximum space required is to prपूर्णांक a 64-bit number in octal */
	अक्षर पंचांगp[(माप(अचिन्हित दीर्घ दीर्घ) * 8 + 2) / 3];
	अक्षर *पंचांगp_end = &पंचांगp[ARRAY_SIZE(पंचांगp)];
	दीर्घ दीर्घ num;
	पूर्णांक base;
	स्थिर अक्षर *s;
	माप_प्रकार len, pos;
	अक्षर sign;

	पूर्णांक flags;		/* flags to number() */

	पूर्णांक field_width;	/* width of output field */
	पूर्णांक precision;		/* min. # of digits क्रम पूर्णांकegers; max
				   number of अक्षरs क्रम from string */
	पूर्णांक qualअगरier;		/* 'h', 'hh', 'l' or 'll' क्रम पूर्णांकeger fields */

	बहु_सूची args;

	/*
	 * We want to pass our input बहु_सूची to helper functions by reference,
	 * but there's an annoying edge हाल. If बहु_सूची was originally passed
	 * to us by value, we could just pass &ap करोwn to the helpers. This is
	 * the हाल on, क्रम example, X86_32.
	 * However, on X86_64 (and possibly others), बहु_सूची is actually a
	 * size-1 array containing a काष्ठाure. Our function parameter ap has
	 * decayed from T[1] to T*, and &ap has type T** rather than T(*)[1],
	 * which is what will be expected by a function taking a बहु_सूची *
	 * parameter.
	 * One standard way to solve this mess is by creating a copy in a local
	 * variable of type बहु_सूची and then passing a poपूर्णांकer to that local
	 * copy instead, which is what we करो here.
	 */
	va_copy(args, ap);

	क्रम (pos = 0; *fmt; ++fmt) अणु
		अगर (*fmt != '%' || *++fmt == '%') अणु
			PUTC(*fmt);
			जारी;
		पूर्ण

		/* process flags */
		flags = get_flags(&fmt);

		/* get field width */
		field_width = get_पूर्णांक(&fmt, &args);
		अगर (field_width < 0) अणु
			field_width = -field_width;
			flags |= LEFT;
		पूर्ण

		अगर (flags & LEFT)
			flags &= ~ZEROPAD;

		/* get the precision */
		precision = -1;
		अगर (*fmt == '.') अणु
			++fmt;
			precision = get_पूर्णांक(&fmt, &args);
			अगर (precision >= 0)
				flags &= ~ZEROPAD;
		पूर्ण

		/* get the conversion qualअगरier */
		qualअगरier = -1;
		अगर (*fmt == 'h' || *fmt == 'l') अणु
			qualअगरier = *fmt;
			++fmt;
			अगर (qualअगरier == *fmt) अणु
				qualअगरier -= 'a'-'A';
				++fmt;
			पूर्ण
		पूर्ण

		sign = 0;

		चयन (*fmt) अणु
		हाल 'c':
			flags &= LEFT;
			s = पंचांगp;
			अगर (qualअगरier == 'l') अणु
				((u16 *)पंचांगp)[0] = (u16)बहु_तर्क(args, अचिन्हित पूर्णांक);
				((u16 *)पंचांगp)[1] = L'\0';
				precision = पूर्णांक_उच्च;
				जाओ wstring;
			पूर्ण अन्यथा अणु
				पंचांगp[0] = (अचिन्हित अक्षर)बहु_तर्क(args, पूर्णांक);
				precision = len = 1;
			पूर्ण
			जाओ output;

		हाल 's':
			flags &= LEFT;
			अगर (precision < 0)
				precision = पूर्णांक_उच्च;
			s = बहु_तर्क(args, व्योम *);
			अगर (!s)
				s = precision < 6 ? "" : "(null)";
			अन्यथा अगर (qualअगरier == 'l') अणु
		wstring:
				flags |= WIDE;
				precision = len = utf16s_utf8nlen((स्थिर u16 *)s, precision);
				जाओ output;
			पूर्ण
			precision = len = strnlen(s, precision);
			जाओ output;

			/* पूर्णांकeger number क्रमmats - set up the flags and "break" */
		हाल 'o':
			base = 8;
			अवरोध;

		हाल 'p':
			अगर (precision < 0)
				precision = 2 * माप(व्योम *);
			fallthrough;
		हाल 'x':
			flags |= SMALL;
			fallthrough;
		हाल 'X':
			base = 16;
			अवरोध;

		हाल 'd':
		हाल 'i':
			flags |= SIGN;
			fallthrough;
		हाल 'u':
			flags &= ~SPECIAL;
			base = 10;
			अवरोध;

		शेष:
			/*
			 * Bail out अगर the conversion specअगरier is invalid.
			 * There's probably a typo in the क्रमmat string and the
			 * reमुख्यing specअगरiers are unlikely to match up with
			 * the arguments.
			 */
			जाओ fail;
		पूर्ण
		अगर (*fmt == 'p') अणु
			num = (अचिन्हित दीर्घ)बहु_तर्क(args, व्योम *);
		पूर्ण अन्यथा अणु
			num = get_number(flags & SIGN, qualअगरier, &args);
		पूर्ण

		sign = get_sign(&num, flags);
		अगर (sign)
			--field_width;

		s = number(पंचांगp_end, num, base, flags & SMALL);
		len = पंचांगp_end - s;
		/* शेष precision is 1 */
		अगर (precision < 0)
			precision = 1;
		/* precision is minimum number of digits to prपूर्णांक */
		अगर (precision < len)
			precision = len;
		अगर (flags & SPECIAL) अणु
			/*
			 * For octal, a leading 0 is prपूर्णांकed only अगर necessary,
			 * i.e. अगर it's not alपढ़ोy there because of the
			 * precision.
			 */
			अगर (base == 8 && precision == len)
				++precision;
			/*
			 * For hexadecimal, the leading 0x is skipped अगर the
			 * output is empty, i.e. both the number and the
			 * precision are 0.
			 */
			अगर (base == 16 && precision > 0)
				field_width -= 2;
			अन्यथा
				flags &= ~SPECIAL;
		पूर्ण
		/*
		 * For zero padding, increase the precision to fill the field
		 * width.
		 */
		अगर ((flags & ZEROPAD) && field_width > precision)
			precision = field_width;

output:
		/* Calculate the padding necessary */
		field_width -= precision;
		/* Leading padding with ' ' */
		अगर (!(flags & LEFT))
			जबतक (field_width-- > 0)
				PUTC(' ');
		/* sign */
		अगर (sign)
			PUTC(sign);
		/* 0x/0X क्रम hexadecimal */
		अगर (flags & SPECIAL) अणु
			PUTC('0');
			PUTC( 'X' | (flags & SMALL));
		पूर्ण
		/* Zero padding and excess precision */
		जबतक (precision-- > len)
			PUTC('0');
		/* Actual output */
		अगर (flags & WIDE) अणु
			स्थिर u16 *ws = (स्थिर u16 *)s;

			जबतक (len-- > 0) अणु
				u32 c32 = utf16_to_utf32(&ws);
				u8 *s8;
				माप_प्रकार clen;

				अगर (c32 < 0x80) अणु
					PUTC(c32);
					जारी;
				पूर्ण

				/* Number of trailing octets */
				clen = 1 + (c32 >= 0x800) + (c32 >= 0x10000);

				len -= clen;
				s8 = (u8 *)&buf[pos];

				/* Aव्योम writing partial अक्षरacter */
				PUTC('\0');
				pos += clen;
				अगर (pos >= size)
					जारी;

				/* Set high bits of leading octet */
				*s8 = (0xf00 >> 1) >> clen;
				/* Write trailing octets in reverse order */
				क्रम (s8 += clen; clen; --clen, c32 >>= 6)
					*s8-- = 0x80 | (c32 & 0x3f);
				/* Set low bits of leading octet */
				*s8 |= c32;
			पूर्ण
		पूर्ण अन्यथा अणु
			जबतक (len-- > 0)
				PUTC(*s++);
		पूर्ण
		/* Trailing padding with ' ' */
		जबतक (field_width-- > 0)
			PUTC(' ');
	पूर्ण
fail:
	बहु_पूर्ण(args);

	अगर (size)
		buf[min(pos, size-1)] = '\0';

	वापस pos;
पूर्ण

पूर्णांक snम_लिखो(अक्षर *buf, माप_प्रकार size, स्थिर अक्षर *fmt, ...)
अणु
	बहु_सूची args;
	पूर्णांक i;

	बहु_शुरू(args, fmt);
	i = vsnम_लिखो(buf, size, fmt, args);
	बहु_पूर्ण(args);
	वापस i;
पूर्ण
