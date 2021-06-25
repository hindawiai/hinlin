<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 *  linux/lib/भम_लिखो.c
 *
 *  Copyright (C) 1991, 1992  Linus Torvalds
 */

/* भम_लिखो.c -- Lars Wirzenius & Linus Torvalds. */
/*
 * Wirzenius wrote this portably, Torvalds fucked it up :-)
 */

/*
 * Fri Jul 13 2001 Crutcher Dunnavant <crutcher+kernel@datastacks.com>
 * - changed to provide snम_लिखो and vsnम_लिखो functions
 * So Feb  1 16:51:32 CET 2004 Juergen Quade <quade@hsnr.de>
 * - scnम_लिखो and vscnम_लिखो
 */

#समावेश <मानकतर्क.स>
#समावेश <linux/build_bug.h>
#समावेश <linux/clk.h>
#समावेश <linux/clk-provider.h>
#समावेश <linux/errname.h>
#समावेश <linux/module.h>	/* क्रम KSYM_SYMBOL_LEN */
#समावेश <linux/types.h>
#समावेश <linux/माला.स>
#समावेश <linux/प्रकार.स>
#समावेश <linux/kernel.h>
#समावेश <linux/kallsyms.h>
#समावेश <linux/math64.h>
#समावेश <linux/uaccess.h>
#समावेश <linux/ioport.h>
#समावेश <linux/dcache.h>
#समावेश <linux/cred.h>
#समावेश <linux/rtc.h>
#समावेश <linux/समय.स>
#समावेश <linux/uuid.h>
#समावेश <linux/of.h>
#समावेश <net/addrconf.h>
#समावेश <linux/siphash.h>
#समावेश <linux/compiler.h>
#समावेश <linux/property.h>
#अगर_घोषित CONFIG_BLOCK
#समावेश <linux/blkdev.h>
#पूर्ण_अगर

#समावेश "../mm/internal.h"	/* For the trace_prपूर्णांक_flags arrays */

#समावेश <यंत्र/page.h>		/* क्रम PAGE_SIZE */
#समावेश <यंत्र/byteorder.h>	/* cpu_to_le16 */

#समावेश <linux/string_helpers.h>
#समावेश "kstrtox.h"

/**
 * simple_म_से_अदीर्घl - convert a string to an अचिन्हित दीर्घ दीर्घ
 * @cp: The start of the string
 * @endp: A poपूर्णांकer to the end of the parsed string will be placed here
 * @base: The number base to use
 *
 * This function has caveats. Please use kम_से_अदीर्घl instead.
 */
अचिन्हित दीर्घ दीर्घ simple_म_से_अदीर्घl(स्थिर अक्षर *cp, अक्षर **endp, अचिन्हित पूर्णांक base)
अणु
	अचिन्हित दीर्घ दीर्घ result;
	अचिन्हित पूर्णांक rv;

	cp = _parse_पूर्णांकeger_fixup_radix(cp, &base);
	rv = _parse_पूर्णांकeger(cp, base, &result);
	/* FIXME */
	cp += (rv & ~KSTRTOX_OVERFLOW);

	अगर (endp)
		*endp = (अक्षर *)cp;

	वापस result;
पूर्ण
EXPORT_SYMBOL(simple_म_से_अदीर्घl);

/**
 * simple_म_से_अदीर्घ - convert a string to an अचिन्हित दीर्घ
 * @cp: The start of the string
 * @endp: A poपूर्णांकer to the end of the parsed string will be placed here
 * @base: The number base to use
 *
 * This function has caveats. Please use kम_से_अदीर्घ instead.
 */
अचिन्हित दीर्घ simple_म_से_अदीर्घ(स्थिर अक्षर *cp, अक्षर **endp, अचिन्हित पूर्णांक base)
अणु
	वापस simple_म_से_अदीर्घl(cp, endp, base);
पूर्ण
EXPORT_SYMBOL(simple_म_से_अदीर्घ);

/**
 * simple_म_से_दीर्घ - convert a string to a चिन्हित दीर्घ
 * @cp: The start of the string
 * @endp: A poपूर्णांकer to the end of the parsed string will be placed here
 * @base: The number base to use
 *
 * This function has caveats. Please use kम_से_दीर्घ instead.
 */
दीर्घ simple_म_से_दीर्घ(स्थिर अक्षर *cp, अक्षर **endp, अचिन्हित पूर्णांक base)
अणु
	अगर (*cp == '-')
		वापस -simple_म_से_अदीर्घ(cp + 1, endp, base);

	वापस simple_म_से_अदीर्घ(cp, endp, base);
पूर्ण
EXPORT_SYMBOL(simple_म_से_दीर्घ);

/**
 * simple_म_से_दीर्घl - convert a string to a चिन्हित दीर्घ दीर्घ
 * @cp: The start of the string
 * @endp: A poपूर्णांकer to the end of the parsed string will be placed here
 * @base: The number base to use
 *
 * This function has caveats. Please use kम_से_दीर्घl instead.
 */
दीर्घ दीर्घ simple_म_से_दीर्घl(स्थिर अक्षर *cp, अक्षर **endp, अचिन्हित पूर्णांक base)
अणु
	अगर (*cp == '-')
		वापस -simple_म_से_अदीर्घl(cp + 1, endp, base);

	वापस simple_म_से_अदीर्घl(cp, endp, base);
पूर्ण
EXPORT_SYMBOL(simple_म_से_दीर्घl);

अटल noअंतरभूत_क्रम_stack
पूर्णांक skip_म_से_प(स्थिर अक्षर **s)
अणु
	पूर्णांक i = 0;

	करो अणु
		i = i*10 + *((*s)++) - '0';
	पूर्ण जबतक (है_अंक(**s));

	वापस i;
पूर्ण

/*
 * Decimal conversion is by far the most typical, and is used क्रम
 * /proc and /sys data. This directly impacts e.g. top perक्रमmance
 * with many processes running. We optimize it क्रम speed by emitting
 * two अक्षरacters at a समय, using a 200 byte lookup table. This
 * roughly halves the number of multiplications compared to computing
 * the digits one at a समय. Implementation strongly inspired by the
 * previous version, which in turn used ideas described at
 * <http://www.cs.uiowa.edu/~jones/bcd/भागide.hपंचांगl> (with permission
 * from the author, Douglas W. Jones).
 *
 * It turns out there is precisely one 26 bit fixed-poपूर्णांक
 * approximation a of 64/100 क्रम which x/100 == (x * (u64)a) >> 32
 * holds क्रम all x in [0, 10^8-1], namely a = 0x28f5c29. The actual
 * range happens to be somewhat larger (x <= 1073741898), but that's
 * irrelevant क्रम our purpose.
 *
 * For भागiding a number in the range [10^4, 10^6-1] by 100, we still
 * need a 32x32->64 bit multiply, so we simply use the same स्थिरant.
 *
 * For भागiding a number in the range [100, 10^4-1] by 100, there are
 * several options. The simplest is (x * 0x147b) >> 19, which is valid
 * क्रम all x <= 43698.
 */

अटल स्थिर u16 decpair[100] = अणु
#घोषणा _(x) (__क्रमce u16) cpu_to_le16(((x % 10) | ((x / 10) << 8)) + 0x3030)
	_( 0), _( 1), _( 2), _( 3), _( 4), _( 5), _( 6), _( 7), _( 8), _( 9),
	_(10), _(11), _(12), _(13), _(14), _(15), _(16), _(17), _(18), _(19),
	_(20), _(21), _(22), _(23), _(24), _(25), _(26), _(27), _(28), _(29),
	_(30), _(31), _(32), _(33), _(34), _(35), _(36), _(37), _(38), _(39),
	_(40), _(41), _(42), _(43), _(44), _(45), _(46), _(47), _(48), _(49),
	_(50), _(51), _(52), _(53), _(54), _(55), _(56), _(57), _(58), _(59),
	_(60), _(61), _(62), _(63), _(64), _(65), _(66), _(67), _(68), _(69),
	_(70), _(71), _(72), _(73), _(74), _(75), _(76), _(77), _(78), _(79),
	_(80), _(81), _(82), _(83), _(84), _(85), _(86), _(87), _(88), _(89),
	_(90), _(91), _(92), _(93), _(94), _(95), _(96), _(97), _(98), _(99),
#अघोषित _
पूर्ण;

/*
 * This will prपूर्णांक a single '0' even अगर r == 0, since we would
 * immediately jump to out_r where two 0s would be written but only
 * one of them accounted क्रम in buf. This is needed by ip4_string
 * below. All other callers pass a non-zero value of r.
*/
अटल noअंतरभूत_क्रम_stack
अक्षर *put_dec_trunc8(अक्षर *buf, अचिन्हित r)
अणु
	अचिन्हित q;

	/* 1 <= r < 10^8 */
	अगर (r < 100)
		जाओ out_r;

	/* 100 <= r < 10^8 */
	q = (r * (u64)0x28f5c29) >> 32;
	*((u16 *)buf) = decpair[r - 100*q];
	buf += 2;

	/* 1 <= q < 10^6 */
	अगर (q < 100)
		जाओ out_q;

	/*  100 <= q < 10^6 */
	r = (q * (u64)0x28f5c29) >> 32;
	*((u16 *)buf) = decpair[q - 100*r];
	buf += 2;

	/* 1 <= r < 10^4 */
	अगर (r < 100)
		जाओ out_r;

	/* 100 <= r < 10^4 */
	q = (r * 0x147b) >> 19;
	*((u16 *)buf) = decpair[r - 100*q];
	buf += 2;
out_q:
	/* 1 <= q < 100 */
	r = q;
out_r:
	/* 1 <= r < 100 */
	*((u16 *)buf) = decpair[r];
	buf += r < 10 ? 1 : 2;
	वापस buf;
पूर्ण

#अगर BITS_PER_LONG == 64 && BITS_PER_LONG_LONG == 64
अटल noअंतरभूत_क्रम_stack
अक्षर *put_dec_full8(अक्षर *buf, अचिन्हित r)
अणु
	अचिन्हित q;

	/* 0 <= r < 10^8 */
	q = (r * (u64)0x28f5c29) >> 32;
	*((u16 *)buf) = decpair[r - 100*q];
	buf += 2;

	/* 0 <= q < 10^6 */
	r = (q * (u64)0x28f5c29) >> 32;
	*((u16 *)buf) = decpair[q - 100*r];
	buf += 2;

	/* 0 <= r < 10^4 */
	q = (r * 0x147b) >> 19;
	*((u16 *)buf) = decpair[r - 100*q];
	buf += 2;

	/* 0 <= q < 100 */
	*((u16 *)buf) = decpair[q];
	buf += 2;
	वापस buf;
पूर्ण

अटल noअंतरभूत_क्रम_stack
अक्षर *put_dec(अक्षर *buf, अचिन्हित दीर्घ दीर्घ n)
अणु
	अगर (n >= 100*1000*1000)
		buf = put_dec_full8(buf, करो_भाग(n, 100*1000*1000));
	/* 1 <= n <= 1.6e11 */
	अगर (n >= 100*1000*1000)
		buf = put_dec_full8(buf, करो_भाग(n, 100*1000*1000));
	/* 1 <= n < 1e8 */
	वापस put_dec_trunc8(buf, n);
पूर्ण

#या_अगर BITS_PER_LONG == 32 && BITS_PER_LONG_LONG == 64

अटल व्योम
put_dec_full4(अक्षर *buf, अचिन्हित r)
अणु
	अचिन्हित q;

	/* 0 <= r < 10^4 */
	q = (r * 0x147b) >> 19;
	*((u16 *)buf) = decpair[r - 100*q];
	buf += 2;
	/* 0 <= q < 100 */
	*((u16 *)buf) = decpair[q];
पूर्ण

/*
 * Call put_dec_full4 on x % 10000, वापस x / 10000.
 * The approximation x/10000 == (x * 0x346DC5D7) >> 43
 * holds क्रम all x < 1,128,869,999.  The largest value this
 * helper will ever be asked to convert is 1,125,520,955.
 * (second call in the put_dec code, assuming n is all-ones).
 */
अटल noअंतरभूत_क्रम_stack
अचिन्हित put_dec_helper4(अक्षर *buf, अचिन्हित x)
अणु
        uपूर्णांक32_t q = (x * (uपूर्णांक64_t)0x346DC5D7) >> 43;

        put_dec_full4(buf, x - q * 10000);
        वापस q;
पूर्ण

/* Based on code by Douglas W. Jones found at
 * <http://www.cs.uiowa.edu/~jones/bcd/decimal.hपंचांगl#sixtyfour>
 * (with permission from the author).
 * Perक्रमms no 64-bit भागision and hence should be fast on 32-bit machines.
 */
अटल
अक्षर *put_dec(अक्षर *buf, अचिन्हित दीर्घ दीर्घ n)
अणु
	uपूर्णांक32_t d3, d2, d1, q, h;

	अगर (n < 100*1000*1000)
		वापस put_dec_trunc8(buf, n);

	d1  = ((uपूर्णांक32_t)n >> 16); /* implicit "& 0xffff" */
	h   = (n >> 32);
	d2  = (h      ) & 0xffff;
	d3  = (h >> 16); /* implicit "& 0xffff" */

	/* n = 2^48 d3 + 2^32 d2 + 2^16 d1 + d0
	     = 281_4749_7671_0656 d3 + 42_9496_7296 d2 + 6_5536 d1 + d0 */
	q   = 656 * d3 + 7296 * d2 + 5536 * d1 + ((uपूर्णांक32_t)n & 0xffff);
	q = put_dec_helper4(buf, q);

	q += 7671 * d3 + 9496 * d2 + 6 * d1;
	q = put_dec_helper4(buf+4, q);

	q += 4749 * d3 + 42 * d2;
	q = put_dec_helper4(buf+8, q);

	q += 281 * d3;
	buf += 12;
	अगर (q)
		buf = put_dec_trunc8(buf, q);
	अन्यथा जबतक (buf[-1] == '0')
		--buf;

	वापस buf;
पूर्ण

#पूर्ण_अगर

/*
 * Convert passed number to decimal string.
 * Returns the length of string.  On buffer overflow, वापसs 0.
 *
 * If speed is not important, use snम_लिखो(). It's easy to पढ़ो the code.
 */
पूर्णांक num_to_str(अक्षर *buf, पूर्णांक size, अचिन्हित दीर्घ दीर्घ num, अचिन्हित पूर्णांक width)
अणु
	/* put_dec requires 2-byte alignment of the buffer. */
	अक्षर पंचांगp[माप(num) * 3] __aligned(2);
	पूर्णांक idx, len;

	/* put_dec() may work incorrectly क्रम num = 0 (generate "", not "0") */
	अगर (num <= 9) अणु
		पंचांगp[0] = '0' + num;
		len = 1;
	पूर्ण अन्यथा अणु
		len = put_dec(पंचांगp, num) - पंचांगp;
	पूर्ण

	अगर (len > size || width > size)
		वापस 0;

	अगर (width > len) अणु
		width = width - len;
		क्रम (idx = 0; idx < width; idx++)
			buf[idx] = ' ';
	पूर्ण अन्यथा अणु
		width = 0;
	पूर्ण

	क्रम (idx = 0; idx < len; ++idx)
		buf[idx + width] = पंचांगp[len - idx - 1];

	वापस len + width;
पूर्ण

#घोषणा SIGN	1		/* अचिन्हित/चिन्हित, must be 1 */
#घोषणा LEFT	2		/* left justअगरied */
#घोषणा PLUS	4		/* show plus */
#घोषणा SPACE	8		/* space अगर plus */
#घोषणा ZEROPAD	16		/* pad with zero, must be 16 == '0' - ' ' */
#घोषणा SMALL	32		/* use lowerहाल in hex (must be 32 == 0x20) */
#घोषणा SPECIAL	64		/* prefix hex with "0x", octal with "0" */

अटल_निश्चित(ZEROPAD == ('0' - ' '));
अटल_निश्चित(SMALL == ' ');

क्रमागत क्रमmat_type अणु
	FORMAT_TYPE_NONE, /* Just a string part */
	FORMAT_TYPE_WIDTH,
	FORMAT_TYPE_PRECISION,
	FORMAT_TYPE_CHAR,
	FORMAT_TYPE_STR,
	FORMAT_TYPE_PTR,
	FORMAT_TYPE_PERCENT_CHAR,
	FORMAT_TYPE_INVALID,
	FORMAT_TYPE_LONG_LONG,
	FORMAT_TYPE_ULONG,
	FORMAT_TYPE_LONG,
	FORMAT_TYPE_UBYTE,
	FORMAT_TYPE_BYTE,
	FORMAT_TYPE_USHORT,
	FORMAT_TYPE_SHORT,
	FORMAT_TYPE_UINT,
	FORMAT_TYPE_INT,
	FORMAT_TYPE_SIZE_T,
	FORMAT_TYPE_PTRDIFF
पूर्ण;

काष्ठा म_लिखो_spec अणु
	अचिन्हित पूर्णांक	type:8;		/* क्रमmat_type क्रमागत */
	चिन्हित पूर्णांक	field_width:24;	/* width of output field */
	अचिन्हित पूर्णांक	flags:8;	/* flags to number() */
	अचिन्हित पूर्णांक	base:8;		/* number base, 8, 10 or 16 only */
	चिन्हित पूर्णांक	precision:16;	/* # of digits/अक्षरs */
पूर्ण __packed;
अटल_निश्चित(माप(काष्ठा म_लिखो_spec) == 8);

#घोषणा FIELD_WIDTH_MAX ((1 << 23) - 1)
#घोषणा PRECISION_MAX ((1 << 15) - 1)

अटल noअंतरभूत_क्रम_stack
अक्षर *number(अक्षर *buf, अक्षर *end, अचिन्हित दीर्घ दीर्घ num,
	     काष्ठा म_लिखो_spec spec)
अणु
	/* put_dec requires 2-byte alignment of the buffer. */
	अक्षर पंचांगp[3 * माप(num)] __aligned(2);
	अक्षर sign;
	अक्षर loहाल;
	पूर्णांक need_pfx = ((spec.flags & SPECIAL) && spec.base != 10);
	पूर्णांक i;
	bool is_zero = num == 0LL;
	पूर्णांक field_width = spec.field_width;
	पूर्णांक precision = spec.precision;

	/* loहाल = 0 or 0x20. ORing digits or letters with 'locase'
	 * produces same digits or (maybe lowerहालd) letters */
	loहाल = (spec.flags & SMALL);
	अगर (spec.flags & LEFT)
		spec.flags &= ~ZEROPAD;
	sign = 0;
	अगर (spec.flags & SIGN) अणु
		अगर ((चिन्हित दीर्घ दीर्घ)num < 0) अणु
			sign = '-';
			num = -(चिन्हित दीर्घ दीर्घ)num;
			field_width--;
		पूर्ण अन्यथा अगर (spec.flags & PLUS) अणु
			sign = '+';
			field_width--;
		पूर्ण अन्यथा अगर (spec.flags & SPACE) अणु
			sign = ' ';
			field_width--;
		पूर्ण
	पूर्ण
	अगर (need_pfx) अणु
		अगर (spec.base == 16)
			field_width -= 2;
		अन्यथा अगर (!is_zero)
			field_width--;
	पूर्ण

	/* generate full string in पंचांगp[], in reverse order */
	i = 0;
	अगर (num < spec.base)
		पंचांगp[i++] = hex_asc_upper[num] | loहाल;
	अन्यथा अगर (spec.base != 10) अणु /* 8 or 16 */
		पूर्णांक mask = spec.base - 1;
		पूर्णांक shअगरt = 3;

		अगर (spec.base == 16)
			shअगरt = 4;
		करो अणु
			पंचांगp[i++] = (hex_asc_upper[((अचिन्हित अक्षर)num) & mask] | loहाल);
			num >>= shअगरt;
		पूर्ण जबतक (num);
	पूर्ण अन्यथा अणु /* base 10 */
		i = put_dec(पंचांगp, num) - पंचांगp;
	पूर्ण

	/* prपूर्णांकing 100 using %2d gives "100", not "00" */
	अगर (i > precision)
		precision = i;
	/* leading space padding */
	field_width -= precision;
	अगर (!(spec.flags & (ZEROPAD | LEFT))) अणु
		जबतक (--field_width >= 0) अणु
			अगर (buf < end)
				*buf = ' ';
			++buf;
		पूर्ण
	पूर्ण
	/* sign */
	अगर (sign) अणु
		अगर (buf < end)
			*buf = sign;
		++buf;
	पूर्ण
	/* "0x" / "0" prefix */
	अगर (need_pfx) अणु
		अगर (spec.base == 16 || !is_zero) अणु
			अगर (buf < end)
				*buf = '0';
			++buf;
		पूर्ण
		अगर (spec.base == 16) अणु
			अगर (buf < end)
				*buf = ('X' | loहाल);
			++buf;
		पूर्ण
	पूर्ण
	/* zero or space padding */
	अगर (!(spec.flags & LEFT)) अणु
		अक्षर c = ' ' + (spec.flags & ZEROPAD);

		जबतक (--field_width >= 0) अणु
			अगर (buf < end)
				*buf = c;
			++buf;
		पूर्ण
	पूर्ण
	/* hmm even more zero padding? */
	जबतक (i <= --precision) अणु
		अगर (buf < end)
			*buf = '0';
		++buf;
	पूर्ण
	/* actual digits of result */
	जबतक (--i >= 0) अणु
		अगर (buf < end)
			*buf = पंचांगp[i];
		++buf;
	पूर्ण
	/* trailing space padding */
	जबतक (--field_width >= 0) अणु
		अगर (buf < end)
			*buf = ' ';
		++buf;
	पूर्ण

	वापस buf;
पूर्ण

अटल noअंतरभूत_क्रम_stack
अक्षर *special_hex_number(अक्षर *buf, अक्षर *end, अचिन्हित दीर्घ दीर्घ num, पूर्णांक size)
अणु
	काष्ठा म_लिखो_spec spec;

	spec.type = FORMAT_TYPE_PTR;
	spec.field_width = 2 + 2 * size;	/* 0x + hex */
	spec.flags = SPECIAL | SMALL | ZEROPAD;
	spec.base = 16;
	spec.precision = -1;

	वापस number(buf, end, num, spec);
पूर्ण

अटल व्योम move_right(अक्षर *buf, अक्षर *end, अचिन्हित len, अचिन्हित spaces)
अणु
	माप_प्रकार size;
	अगर (buf >= end)	/* nowhere to put anything */
		वापस;
	size = end - buf;
	अगर (size <= spaces) अणु
		स_रखो(buf, ' ', size);
		वापस;
	पूर्ण
	अगर (len) अणु
		अगर (len > size - spaces)
			len = size - spaces;
		स_हटाओ(buf + spaces, buf, len);
	पूर्ण
	स_रखो(buf, ' ', spaces);
पूर्ण

/*
 * Handle field width padding क्रम a string.
 * @buf: current buffer position
 * @n: length of string
 * @end: end of output buffer
 * @spec: क्रम field width and flags
 * Returns: new buffer position after padding.
 */
अटल noअंतरभूत_क्रम_stack
अक्षर *widen_string(अक्षर *buf, पूर्णांक n, अक्षर *end, काष्ठा म_लिखो_spec spec)
अणु
	अचिन्हित spaces;

	अगर (likely(n >= spec.field_width))
		वापस buf;
	/* we want to pad the sucker */
	spaces = spec.field_width - n;
	अगर (!(spec.flags & LEFT)) अणु
		move_right(buf - n, end, n, spaces);
		वापस buf + spaces;
	पूर्ण
	जबतक (spaces--) अणु
		अगर (buf < end)
			*buf = ' ';
		++buf;
	पूर्ण
	वापस buf;
पूर्ण

/* Handle string from a well known address. */
अटल अक्षर *string_nocheck(अक्षर *buf, अक्षर *end, स्थिर अक्षर *s,
			    काष्ठा म_लिखो_spec spec)
अणु
	पूर्णांक len = 0;
	पूर्णांक lim = spec.precision;

	जबतक (lim--) अणु
		अक्षर c = *s++;
		अगर (!c)
			अवरोध;
		अगर (buf < end)
			*buf = c;
		++buf;
		++len;
	पूर्ण
	वापस widen_string(buf, len, end, spec);
पूर्ण

अटल अक्षर *err_ptr(अक्षर *buf, अक्षर *end, व्योम *ptr,
		     काष्ठा म_लिखो_spec spec)
अणु
	पूर्णांक err = PTR_ERR(ptr);
	स्थिर अक्षर *sym = errname(err);

	अगर (sym)
		वापस string_nocheck(buf, end, sym, spec);

	/*
	 * Somebody passed ERR_PTR(-1234) or some other non-existing
	 * Efoo - or perhaps CONFIG_SYMBOLIC_ERRNAME=n. Fall back to
	 * prपूर्णांकing it as its decimal representation.
	 */
	spec.flags |= SIGN;
	spec.base = 10;
	वापस number(buf, end, err, spec);
पूर्ण

/* Be careful: error messages must fit पूर्णांकo the given buffer. */
अटल अक्षर *error_string(अक्षर *buf, अक्षर *end, स्थिर अक्षर *s,
			  काष्ठा म_लिखो_spec spec)
अणु
	/*
	 * Hard limit to aव्योम a completely insane messages. It actually
	 * works pretty well because most error messages are in
	 * the many poपूर्णांकer क्रमmat modअगरiers.
	 */
	अगर (spec.precision == -1)
		spec.precision = 2 * माप(व्योम *);

	वापस string_nocheck(buf, end, s, spec);
पूर्ण

/*
 * Do not call any complex बाह्यal code here. Nested prपूर्णांकk()/भम_लिखो()
 * might cause infinite loops. Failures might अवरोध prपूर्णांकk() and would
 * be hard to debug.
 */
अटल स्थिर अक्षर *check_poपूर्णांकer_msg(स्थिर व्योम *ptr)
अणु
	अगर (!ptr)
		वापस "(null)";

	अगर ((अचिन्हित दीर्घ)ptr < PAGE_SIZE || IS_ERR_VALUE(ptr))
		वापस "(efault)";

	वापस शून्य;
पूर्ण

अटल पूर्णांक check_poपूर्णांकer(अक्षर **buf, अक्षर *end, स्थिर व्योम *ptr,
			 काष्ठा म_लिखो_spec spec)
अणु
	स्थिर अक्षर *err_msg;

	err_msg = check_poपूर्णांकer_msg(ptr);
	अगर (err_msg) अणु
		*buf = error_string(*buf, end, err_msg, spec);
		वापस -EFAULT;
	पूर्ण

	वापस 0;
पूर्ण

अटल noअंतरभूत_क्रम_stack
अक्षर *string(अक्षर *buf, अक्षर *end, स्थिर अक्षर *s,
	     काष्ठा म_लिखो_spec spec)
अणु
	अगर (check_poपूर्णांकer(&buf, end, s, spec))
		वापस buf;

	वापस string_nocheck(buf, end, s, spec);
पूर्ण

अटल अक्षर *poपूर्णांकer_string(अक्षर *buf, अक्षर *end,
			    स्थिर व्योम *ptr,
			    काष्ठा म_लिखो_spec spec)
अणु
	spec.base = 16;
	spec.flags |= SMALL;
	अगर (spec.field_width == -1) अणु
		spec.field_width = 2 * माप(ptr);
		spec.flags |= ZEROPAD;
	पूर्ण

	वापस number(buf, end, (अचिन्हित दीर्घ पूर्णांक)ptr, spec);
पूर्ण

/* Make poपूर्णांकers available क्रम prपूर्णांकing early in the boot sequence. */
अटल पूर्णांक debug_boot_weak_hash __ro_after_init;

अटल पूर्णांक __init debug_boot_weak_hash_enable(अक्षर *str)
अणु
	debug_boot_weak_hash = 1;
	pr_info("debug_boot_weak_hash enabled\n");
	वापस 0;
पूर्ण
early_param("debug_boot_weak_hash", debug_boot_weak_hash_enable);

अटल DEFINE_STATIC_KEY_TRUE(not_filled_अक्रमom_ptr_key);
अटल siphash_key_t ptr_key __पढ़ो_mostly;

अटल व्योम enable_ptr_key_workfn(काष्ठा work_काष्ठा *work)
अणु
	get_अक्रमom_bytes(&ptr_key, माप(ptr_key));
	/* Needs to run from preemptible context */
	अटल_branch_disable(&not_filled_अक्रमom_ptr_key);
पूर्ण

अटल DECLARE_WORK(enable_ptr_key_work, enable_ptr_key_workfn);

अटल व्योम fill_अक्रमom_ptr_key(काष्ठा अक्रमom_पढ़ोy_callback *unused)
अणु
	/* This may be in an पूर्णांकerrupt handler. */
	queue_work(प्रणाली_unbound_wq, &enable_ptr_key_work);
पूर्ण

अटल काष्ठा अक्रमom_पढ़ोy_callback अक्रमom_पढ़ोy = अणु
	.func = fill_अक्रमom_ptr_key
पूर्ण;

अटल पूर्णांक __init initialize_ptr_अक्रमom(व्योम)
अणु
	पूर्णांक key_size = माप(ptr_key);
	पूर्णांक ret;

	/* Use hw RNG अगर available. */
	अगर (get_अक्रमom_bytes_arch(&ptr_key, key_size) == key_size) अणु
		अटल_branch_disable(&not_filled_अक्रमom_ptr_key);
		वापस 0;
	पूर्ण

	ret = add_अक्रमom_पढ़ोy_callback(&अक्रमom_पढ़ोy);
	अगर (!ret) अणु
		वापस 0;
	पूर्ण अन्यथा अगर (ret == -EALREADY) अणु
		/* This is in preemptible context */
		enable_ptr_key_workfn(&enable_ptr_key_work);
		वापस 0;
	पूर्ण

	वापस ret;
पूर्ण
early_initcall(initialize_ptr_अक्रमom);

/* Maps a poपूर्णांकer to a 32 bit unique identअगरier. */
अटल अंतरभूत पूर्णांक __ptr_to_hashval(स्थिर व्योम *ptr, अचिन्हित दीर्घ *hashval_out)
अणु
	अचिन्हित दीर्घ hashval;

	अगर (अटल_branch_unlikely(&not_filled_अक्रमom_ptr_key))
		वापस -EAGAIN;

#अगर_घोषित CONFIG_64BIT
	hashval = (अचिन्हित दीर्घ)siphash_1u64((u64)ptr, &ptr_key);
	/*
	 * Mask off the first 32 bits, this makes explicit that we have
	 * modअगरied the address (and 32 bits is plenty क्रम a unique ID).
	 */
	hashval = hashval & 0xffffffff;
#अन्यथा
	hashval = (अचिन्हित दीर्घ)siphash_1u32((u32)ptr, &ptr_key);
#पूर्ण_अगर
	*hashval_out = hashval;
	वापस 0;
पूर्ण

पूर्णांक ptr_to_hashval(स्थिर व्योम *ptr, अचिन्हित दीर्घ *hashval_out)
अणु
	वापस __ptr_to_hashval(ptr, hashval_out);
पूर्ण

अटल अक्षर *ptr_to_id(अक्षर *buf, अक्षर *end, स्थिर व्योम *ptr,
		       काष्ठा म_लिखो_spec spec)
अणु
	स्थिर अक्षर *str = माप(ptr) == 8 ? "(____ptrval____)" : "(ptrval)";
	अचिन्हित दीर्घ hashval;
	पूर्णांक ret;

	/*
	 * Prपूर्णांक the real poपूर्णांकer value क्रम शून्य and error poपूर्णांकers,
	 * as they are not actual addresses.
	 */
	अगर (IS_ERR_OR_शून्य(ptr))
		वापस poपूर्णांकer_string(buf, end, ptr, spec);

	/* When debugging early boot use non-cryptographically secure hash. */
	अगर (unlikely(debug_boot_weak_hash)) अणु
		hashval = hash_दीर्घ((अचिन्हित दीर्घ)ptr, 32);
		वापस poपूर्णांकer_string(buf, end, (स्थिर व्योम *)hashval, spec);
	पूर्ण

	ret = __ptr_to_hashval(ptr, &hashval);
	अगर (ret) अणु
		spec.field_width = 2 * माप(ptr);
		/* string length must be less than शेष_width */
		वापस error_string(buf, end, str, spec);
	पूर्ण

	वापस poपूर्णांकer_string(buf, end, (स्थिर व्योम *)hashval, spec);
पूर्ण

पूर्णांक kptr_restrict __पढ़ो_mostly;

अटल noअंतरभूत_क्रम_stack
अक्षर *restricted_poपूर्णांकer(अक्षर *buf, अक्षर *end, स्थिर व्योम *ptr,
			 काष्ठा म_लिखो_spec spec)
अणु
	चयन (kptr_restrict) अणु
	हाल 0:
		/* Handle as %p, hash and करो _not_ leak addresses. */
		वापस ptr_to_id(buf, end, ptr, spec);
	हाल 1: अणु
		स्थिर काष्ठा cred *cred;

		/*
		 * kptr_restrict==1 cannot be used in IRQ context
		 * because its test क्रम CAP_SYSLOG would be meaningless.
		 */
		अगर (in_irq() || in_serving_softirq() || in_nmi()) अणु
			अगर (spec.field_width == -1)
				spec.field_width = 2 * माप(ptr);
			वापस error_string(buf, end, "pK-error", spec);
		पूर्ण

		/*
		 * Only prपूर्णांक the real poपूर्णांकer value अगर the current
		 * process has CAP_SYSLOG and is running with the
		 * same credentials it started with. This is because
		 * access to files is checked at खोलो() समय, but %pK
		 * checks permission at पढ़ो() समय. We करोn't want to
		 * leak poपूर्णांकer values अगर a binary खोलोs a file using
		 * %pK and then elevates privileges beक्रमe पढ़ोing it.
		 */
		cred = current_cred();
		अगर (!has_capability_noaudit(current, CAP_SYSLOG) ||
		    !uid_eq(cred->euid, cred->uid) ||
		    !gid_eq(cred->egid, cred->gid))
			ptr = शून्य;
		अवरोध;
	पूर्ण
	हाल 2:
	शेष:
		/* Always prपूर्णांक 0's क्रम %pK */
		ptr = शून्य;
		अवरोध;
	पूर्ण

	वापस poपूर्णांकer_string(buf, end, ptr, spec);
पूर्ण

अटल noअंतरभूत_क्रम_stack
अक्षर *dentry_name(अक्षर *buf, अक्षर *end, स्थिर काष्ठा dentry *d, काष्ठा म_लिखो_spec spec,
		  स्थिर अक्षर *fmt)
अणु
	स्थिर अक्षर *array[4], *s;
	स्थिर काष्ठा dentry *p;
	पूर्णांक depth;
	पूर्णांक i, n;

	चयन (fmt[1]) अणु
		हाल '2': case '3': case '4':
			depth = fmt[1] - '0';
			अवरोध;
		शेष:
			depth = 1;
	पूर्ण

	rcu_पढ़ो_lock();
	क्रम (i = 0; i < depth; i++, d = p) अणु
		अगर (check_poपूर्णांकer(&buf, end, d, spec)) अणु
			rcu_पढ़ो_unlock();
			वापस buf;
		पूर्ण

		p = READ_ONCE(d->d_parent);
		array[i] = READ_ONCE(d->d_name.name);
		अगर (p == d) अणु
			अगर (i)
				array[i] = "";
			i++;
			अवरोध;
		पूर्ण
	पूर्ण
	s = array[--i];
	क्रम (n = 0; n != spec.precision; n++, buf++) अणु
		अक्षर c = *s++;
		अगर (!c) अणु
			अगर (!i)
				अवरोध;
			c = '/';
			s = array[--i];
		पूर्ण
		अगर (buf < end)
			*buf = c;
	पूर्ण
	rcu_पढ़ो_unlock();
	वापस widen_string(buf, n, end, spec);
पूर्ण

अटल noअंतरभूत_क्रम_stack
अक्षर *file_dentry_name(अक्षर *buf, अक्षर *end, स्थिर काष्ठा file *f,
			काष्ठा म_लिखो_spec spec, स्थिर अक्षर *fmt)
अणु
	अगर (check_poपूर्णांकer(&buf, end, f, spec))
		वापस buf;

	वापस dentry_name(buf, end, f->f_path.dentry, spec, fmt);
पूर्ण
#अगर_घोषित CONFIG_BLOCK
अटल noअंतरभूत_क्रम_stack
अक्षर *bdev_name(अक्षर *buf, अक्षर *end, काष्ठा block_device *bdev,
		काष्ठा म_लिखो_spec spec, स्थिर अक्षर *fmt)
अणु
	काष्ठा gendisk *hd;

	अगर (check_poपूर्णांकer(&buf, end, bdev, spec))
		वापस buf;

	hd = bdev->bd_disk;
	buf = string(buf, end, hd->disk_name, spec);
	अगर (bdev->bd_partno) अणु
		अगर (है_अंक(hd->disk_name[म_माप(hd->disk_name)-1])) अणु
			अगर (buf < end)
				*buf = 'p';
			buf++;
		पूर्ण
		buf = number(buf, end, bdev->bd_partno, spec);
	पूर्ण
	वापस buf;
पूर्ण
#पूर्ण_अगर

अटल noअंतरभूत_क्रम_stack
अक्षर *symbol_string(अक्षर *buf, अक्षर *end, व्योम *ptr,
		    काष्ठा म_लिखो_spec spec, स्थिर अक्षर *fmt)
अणु
	अचिन्हित दीर्घ value;
#अगर_घोषित CONFIG_KALLSYMS
	अक्षर sym[KSYM_SYMBOL_LEN];
#पूर्ण_अगर

	अगर (fmt[1] == 'R')
		ptr = __builtin_extract_वापस_addr(ptr);
	value = (अचिन्हित दीर्घ)ptr;

#अगर_घोषित CONFIG_KALLSYMS
	अगर (*fmt == 'B')
		sprपूर्णांक_backtrace(sym, value);
	अन्यथा अगर (*fmt != 's')
		sprपूर्णांक_symbol(sym, value);
	अन्यथा
		sprपूर्णांक_symbol_no_offset(sym, value);

	वापस string_nocheck(buf, end, sym, spec);
#अन्यथा
	वापस special_hex_number(buf, end, value, माप(व्योम *));
#पूर्ण_अगर
पूर्ण

अटल स्थिर काष्ठा म_लिखो_spec शेष_str_spec = अणु
	.field_width = -1,
	.precision = -1,
पूर्ण;

अटल स्थिर काष्ठा म_लिखो_spec शेष_flag_spec = अणु
	.base = 16,
	.precision = -1,
	.flags = SPECIAL | SMALL,
पूर्ण;

अटल स्थिर काष्ठा म_लिखो_spec शेष_dec_spec = अणु
	.base = 10,
	.precision = -1,
पूर्ण;

अटल स्थिर काष्ठा म_लिखो_spec शेष_dec02_spec = अणु
	.base = 10,
	.field_width = 2,
	.precision = -1,
	.flags = ZEROPAD,
पूर्ण;

अटल स्थिर काष्ठा म_लिखो_spec शेष_dec04_spec = अणु
	.base = 10,
	.field_width = 4,
	.precision = -1,
	.flags = ZEROPAD,
पूर्ण;

अटल noअंतरभूत_क्रम_stack
अक्षर *resource_string(अक्षर *buf, अक्षर *end, काष्ठा resource *res,
		      काष्ठा म_लिखो_spec spec, स्थिर अक्षर *fmt)
अणु
#अगर_अघोषित IO_RSRC_PRINTK_SIZE
#घोषणा IO_RSRC_PRINTK_SIZE	6
#पूर्ण_अगर

#अगर_अघोषित MEM_RSRC_PRINTK_SIZE
#घोषणा MEM_RSRC_PRINTK_SIZE	10
#पूर्ण_अगर
	अटल स्थिर काष्ठा म_लिखो_spec io_spec = अणु
		.base = 16,
		.field_width = IO_RSRC_PRINTK_SIZE,
		.precision = -1,
		.flags = SPECIAL | SMALL | ZEROPAD,
	पूर्ण;
	अटल स्थिर काष्ठा म_लिखो_spec mem_spec = अणु
		.base = 16,
		.field_width = MEM_RSRC_PRINTK_SIZE,
		.precision = -1,
		.flags = SPECIAL | SMALL | ZEROPAD,
	पूर्ण;
	अटल स्थिर काष्ठा म_लिखो_spec bus_spec = अणु
		.base = 16,
		.field_width = 2,
		.precision = -1,
		.flags = SMALL | ZEROPAD,
	पूर्ण;
	अटल स्थिर काष्ठा म_लिखो_spec str_spec = अणु
		.field_width = -1,
		.precision = 10,
		.flags = LEFT,
	पूर्ण;

	/* 32-bit res (माप==4): 10 अक्षरs in dec, 10 in hex ("0x" + 8)
	 * 64-bit res (माप==8): 20 अक्षरs in dec, 18 in hex ("0x" + 16) */
#घोषणा RSRC_BUF_SIZE		((2 * माप(resource_माप_प्रकार)) + 4)
#घोषणा FLAG_BUF_SIZE		(2 * माप(res->flags))
#घोषणा DECODED_BUF_SIZE	माप("[mem - 64bit pref window disabled]")
#घोषणा RAW_BUF_SIZE		माप("[mem - flags 0x]")
	अक्षर sym[max(2*RSRC_BUF_SIZE + DECODED_BUF_SIZE,
		     2*RSRC_BUF_SIZE + FLAG_BUF_SIZE + RAW_BUF_SIZE)];

	अक्षर *p = sym, *pend = sym + माप(sym);
	पूर्णांक decode = (fmt[0] == 'R') ? 1 : 0;
	स्थिर काष्ठा म_लिखो_spec *specp;

	अगर (check_poपूर्णांकer(&buf, end, res, spec))
		वापस buf;

	*p++ = '[';
	अगर (res->flags & IORESOURCE_IO) अणु
		p = string_nocheck(p, pend, "io  ", str_spec);
		specp = &io_spec;
	पूर्ण अन्यथा अगर (res->flags & IORESOURCE_MEM) अणु
		p = string_nocheck(p, pend, "mem ", str_spec);
		specp = &mem_spec;
	पूर्ण अन्यथा अगर (res->flags & IORESOURCE_IRQ) अणु
		p = string_nocheck(p, pend, "irq ", str_spec);
		specp = &शेष_dec_spec;
	पूर्ण अन्यथा अगर (res->flags & IORESOURCE_DMA) अणु
		p = string_nocheck(p, pend, "dma ", str_spec);
		specp = &शेष_dec_spec;
	पूर्ण अन्यथा अगर (res->flags & IORESOURCE_BUS) अणु
		p = string_nocheck(p, pend, "bus ", str_spec);
		specp = &bus_spec;
	पूर्ण अन्यथा अणु
		p = string_nocheck(p, pend, "??? ", str_spec);
		specp = &mem_spec;
		decode = 0;
	पूर्ण
	अगर (decode && res->flags & IORESOURCE_UNSET) अणु
		p = string_nocheck(p, pend, "size ", str_spec);
		p = number(p, pend, resource_size(res), *specp);
	पूर्ण अन्यथा अणु
		p = number(p, pend, res->start, *specp);
		अगर (res->start != res->end) अणु
			*p++ = '-';
			p = number(p, pend, res->end, *specp);
		पूर्ण
	पूर्ण
	अगर (decode) अणु
		अगर (res->flags & IORESOURCE_MEM_64)
			p = string_nocheck(p, pend, " 64bit", str_spec);
		अगर (res->flags & IORESOURCE_PREFETCH)
			p = string_nocheck(p, pend, " pref", str_spec);
		अगर (res->flags & IORESOURCE_WINDOW)
			p = string_nocheck(p, pend, " window", str_spec);
		अगर (res->flags & IORESOURCE_DISABLED)
			p = string_nocheck(p, pend, " disabled", str_spec);
	पूर्ण अन्यथा अणु
		p = string_nocheck(p, pend, " flags ", str_spec);
		p = number(p, pend, res->flags, शेष_flag_spec);
	पूर्ण
	*p++ = ']';
	*p = '\0';

	वापस string_nocheck(buf, end, sym, spec);
पूर्ण

अटल noअंतरभूत_क्रम_stack
अक्षर *hex_string(अक्षर *buf, अक्षर *end, u8 *addr, काष्ठा म_लिखो_spec spec,
		 स्थिर अक्षर *fmt)
अणु
	पूर्णांक i, len = 1;		/* अगर we pass '%ph[CDN]', field width reमुख्यs
				   negative value, fallback to the शेष */
	अक्षर separator;

	अगर (spec.field_width == 0)
		/* nothing to prपूर्णांक */
		वापस buf;

	अगर (check_poपूर्णांकer(&buf, end, addr, spec))
		वापस buf;

	चयन (fmt[1]) अणु
	हाल 'C':
		separator = ':';
		अवरोध;
	हाल 'D':
		separator = '-';
		अवरोध;
	हाल 'N':
		separator = 0;
		अवरोध;
	शेष:
		separator = ' ';
		अवरोध;
	पूर्ण

	अगर (spec.field_width > 0)
		len = min_t(पूर्णांक, spec.field_width, 64);

	क्रम (i = 0; i < len; ++i) अणु
		अगर (buf < end)
			*buf = hex_asc_hi(addr[i]);
		++buf;
		अगर (buf < end)
			*buf = hex_asc_lo(addr[i]);
		++buf;

		अगर (separator && i != len - 1) अणु
			अगर (buf < end)
				*buf = separator;
			++buf;
		पूर्ण
	पूर्ण

	वापस buf;
पूर्ण

अटल noअंतरभूत_क्रम_stack
अक्षर *biपंचांगap_string(अक्षर *buf, अक्षर *end, अचिन्हित दीर्घ *biपंचांगap,
		    काष्ठा म_लिखो_spec spec, स्थिर अक्षर *fmt)
अणु
	स्थिर पूर्णांक CHUNKSZ = 32;
	पूर्णांक nr_bits = max_t(पूर्णांक, spec.field_width, 0);
	पूर्णांक i, chunksz;
	bool first = true;

	अगर (check_poपूर्णांकer(&buf, end, biपंचांगap, spec))
		वापस buf;

	/* reused to prपूर्णांक numbers */
	spec = (काष्ठा म_लिखो_spec)अणु .flags = SMALL | ZEROPAD, .base = 16 पूर्ण;

	chunksz = nr_bits & (CHUNKSZ - 1);
	अगर (chunksz == 0)
		chunksz = CHUNKSZ;

	i = ALIGN(nr_bits, CHUNKSZ) - CHUNKSZ;
	क्रम (; i >= 0; i -= CHUNKSZ) अणु
		u32 chunkmask, val;
		पूर्णांक word, bit;

		chunkmask = ((1ULL << chunksz) - 1);
		word = i / BITS_PER_LONG;
		bit = i % BITS_PER_LONG;
		val = (biपंचांगap[word] >> bit) & chunkmask;

		अगर (!first) अणु
			अगर (buf < end)
				*buf = ',';
			buf++;
		पूर्ण
		first = false;

		spec.field_width = DIV_ROUND_UP(chunksz, 4);
		buf = number(buf, end, val, spec);

		chunksz = CHUNKSZ;
	पूर्ण
	वापस buf;
पूर्ण

अटल noअंतरभूत_क्रम_stack
अक्षर *biपंचांगap_list_string(अक्षर *buf, अक्षर *end, अचिन्हित दीर्घ *biपंचांगap,
			 काष्ठा म_लिखो_spec spec, स्थिर अक्षर *fmt)
अणु
	पूर्णांक nr_bits = max_t(पूर्णांक, spec.field_width, 0);
	/* current bit is 'cur', most recently seen range is [rbot, rtop] */
	पूर्णांक cur, rbot, rtop;
	bool first = true;

	अगर (check_poपूर्णांकer(&buf, end, biपंचांगap, spec))
		वापस buf;

	rbot = cur = find_first_bit(biपंचांगap, nr_bits);
	जबतक (cur < nr_bits) अणु
		rtop = cur;
		cur = find_next_bit(biपंचांगap, nr_bits, cur + 1);
		अगर (cur < nr_bits && cur <= rtop + 1)
			जारी;

		अगर (!first) अणु
			अगर (buf < end)
				*buf = ',';
			buf++;
		पूर्ण
		first = false;

		buf = number(buf, end, rbot, शेष_dec_spec);
		अगर (rbot < rtop) अणु
			अगर (buf < end)
				*buf = '-';
			buf++;

			buf = number(buf, end, rtop, शेष_dec_spec);
		पूर्ण

		rbot = cur;
	पूर्ण
	वापस buf;
पूर्ण

अटल noअंतरभूत_क्रम_stack
अक्षर *mac_address_string(अक्षर *buf, अक्षर *end, u8 *addr,
			 काष्ठा म_लिखो_spec spec, स्थिर अक्षर *fmt)
अणु
	अक्षर mac_addr[माप("xx:xx:xx:xx:xx:xx")];
	अक्षर *p = mac_addr;
	पूर्णांक i;
	अक्षर separator;
	bool reversed = false;

	अगर (check_poपूर्णांकer(&buf, end, addr, spec))
		वापस buf;

	चयन (fmt[1]) अणु
	हाल 'F':
		separator = '-';
		अवरोध;

	हाल 'R':
		reversed = true;
		fallthrough;

	शेष:
		separator = ':';
		अवरोध;
	पूर्ण

	क्रम (i = 0; i < 6; i++) अणु
		अगर (reversed)
			p = hex_byte_pack(p, addr[5 - i]);
		अन्यथा
			p = hex_byte_pack(p, addr[i]);

		अगर (fmt[0] == 'M' && i != 5)
			*p++ = separator;
	पूर्ण
	*p = '\0';

	वापस string_nocheck(buf, end, mac_addr, spec);
पूर्ण

अटल noअंतरभूत_क्रम_stack
अक्षर *ip4_string(अक्षर *p, स्थिर u8 *addr, स्थिर अक्षर *fmt)
अणु
	पूर्णांक i;
	bool leading_zeros = (fmt[0] == 'i');
	पूर्णांक index;
	पूर्णांक step;

	चयन (fmt[2]) अणु
	हाल 'h':
#अगर_घोषित __BIG_ENDIAN
		index = 0;
		step = 1;
#अन्यथा
		index = 3;
		step = -1;
#पूर्ण_अगर
		अवरोध;
	हाल 'l':
		index = 3;
		step = -1;
		अवरोध;
	हाल 'n':
	हाल 'b':
	शेष:
		index = 0;
		step = 1;
		अवरोध;
	पूर्ण
	क्रम (i = 0; i < 4; i++) अणु
		अक्षर temp[4] __aligned(2);	/* hold each IP quad in reverse order */
		पूर्णांक digits = put_dec_trunc8(temp, addr[index]) - temp;
		अगर (leading_zeros) अणु
			अगर (digits < 3)
				*p++ = '0';
			अगर (digits < 2)
				*p++ = '0';
		पूर्ण
		/* reverse the digits in the quad */
		जबतक (digits--)
			*p++ = temp[digits];
		अगर (i < 3)
			*p++ = '.';
		index += step;
	पूर्ण
	*p = '\0';

	वापस p;
पूर्ण

अटल noअंतरभूत_क्रम_stack
अक्षर *ip6_compressed_string(अक्षर *p, स्थिर अक्षर *addr)
अणु
	पूर्णांक i, j, range;
	अचिन्हित अक्षर zerolength[8];
	पूर्णांक दीर्घest = 1;
	पूर्णांक colonpos = -1;
	u16 word;
	u8 hi, lo;
	bool needcolon = false;
	bool useIPv4;
	काष्ठा in6_addr in6;

	स_नकल(&in6, addr, माप(काष्ठा in6_addr));

	useIPv4 = ipv6_addr_v4mapped(&in6) || ipv6_addr_is_isatap(&in6);

	स_रखो(zerolength, 0, माप(zerolength));

	अगर (useIPv4)
		range = 6;
	अन्यथा
		range = 8;

	/* find position of दीर्घest 0 run */
	क्रम (i = 0; i < range; i++) अणु
		क्रम (j = i; j < range; j++) अणु
			अगर (in6.s6_addr16[j] != 0)
				अवरोध;
			zerolength[i]++;
		पूर्ण
	पूर्ण
	क्रम (i = 0; i < range; i++) अणु
		अगर (zerolength[i] > दीर्घest) अणु
			दीर्घest = zerolength[i];
			colonpos = i;
		पूर्ण
	पूर्ण
	अगर (दीर्घest == 1)		/* करोn't compress a single 0 */
		colonpos = -1;

	/* emit address */
	क्रम (i = 0; i < range; i++) अणु
		अगर (i == colonpos) अणु
			अगर (needcolon || i == 0)
				*p++ = ':';
			*p++ = ':';
			needcolon = false;
			i += दीर्घest - 1;
			जारी;
		पूर्ण
		अगर (needcolon) अणु
			*p++ = ':';
			needcolon = false;
		पूर्ण
		/* hex u16 without leading 0s */
		word = ntohs(in6.s6_addr16[i]);
		hi = word >> 8;
		lo = word & 0xff;
		अगर (hi) अणु
			अगर (hi > 0x0f)
				p = hex_byte_pack(p, hi);
			अन्यथा
				*p++ = hex_asc_lo(hi);
			p = hex_byte_pack(p, lo);
		पूर्ण
		अन्यथा अगर (lo > 0x0f)
			p = hex_byte_pack(p, lo);
		अन्यथा
			*p++ = hex_asc_lo(lo);
		needcolon = true;
	पूर्ण

	अगर (useIPv4) अणु
		अगर (needcolon)
			*p++ = ':';
		p = ip4_string(p, &in6.s6_addr[12], "I4");
	पूर्ण
	*p = '\0';

	वापस p;
पूर्ण

अटल noअंतरभूत_क्रम_stack
अक्षर *ip6_string(अक्षर *p, स्थिर अक्षर *addr, स्थिर अक्षर *fmt)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < 8; i++) अणु
		p = hex_byte_pack(p, *addr++);
		p = hex_byte_pack(p, *addr++);
		अगर (fmt[0] == 'I' && i != 7)
			*p++ = ':';
	पूर्ण
	*p = '\0';

	वापस p;
पूर्ण

अटल noअंतरभूत_क्रम_stack
अक्षर *ip6_addr_string(अक्षर *buf, अक्षर *end, स्थिर u8 *addr,
		      काष्ठा म_लिखो_spec spec, स्थिर अक्षर *fmt)
अणु
	अक्षर ip6_addr[माप("xxxx:xxxx:xxxx:xxxx:xxxx:xxxx:255.255.255.255")];

	अगर (fmt[0] == 'I' && fmt[2] == 'c')
		ip6_compressed_string(ip6_addr, addr);
	अन्यथा
		ip6_string(ip6_addr, addr, fmt);

	वापस string_nocheck(buf, end, ip6_addr, spec);
पूर्ण

अटल noअंतरभूत_क्रम_stack
अक्षर *ip4_addr_string(अक्षर *buf, अक्षर *end, स्थिर u8 *addr,
		      काष्ठा म_लिखो_spec spec, स्थिर अक्षर *fmt)
अणु
	अक्षर ip4_addr[माप("255.255.255.255")];

	ip4_string(ip4_addr, addr, fmt);

	वापस string_nocheck(buf, end, ip4_addr, spec);
पूर्ण

अटल noअंतरभूत_क्रम_stack
अक्षर *ip6_addr_string_sa(अक्षर *buf, अक्षर *end, स्थिर काष्ठा sockaddr_in6 *sa,
			 काष्ठा म_लिखो_spec spec, स्थिर अक्षर *fmt)
अणु
	bool have_p = false, have_s = false, have_f = false, have_c = false;
	अक्षर ip6_addr[माप("[xxxx:xxxx:xxxx:xxxx:xxxx:xxxx:255.255.255.255]") +
		      माप(":12345") + माप("/123456789") +
		      माप("%1234567890")];
	अक्षर *p = ip6_addr, *pend = ip6_addr + माप(ip6_addr);
	स्थिर u8 *addr = (स्थिर u8 *) &sa->sin6_addr;
	अक्षर fmt6[2] = अणु fmt[0], '6' पूर्ण;
	u8 off = 0;

	fmt++;
	जबतक (है_अक्षर(*++fmt)) अणु
		चयन (*fmt) अणु
		हाल 'p':
			have_p = true;
			अवरोध;
		हाल 'f':
			have_f = true;
			अवरोध;
		हाल 's':
			have_s = true;
			अवरोध;
		हाल 'c':
			have_c = true;
			अवरोध;
		पूर्ण
	पूर्ण

	अगर (have_p || have_s || have_f) अणु
		*p = '[';
		off = 1;
	पूर्ण

	अगर (fmt6[0] == 'I' && have_c)
		p = ip6_compressed_string(ip6_addr + off, addr);
	अन्यथा
		p = ip6_string(ip6_addr + off, addr, fmt6);

	अगर (have_p || have_s || have_f)
		*p++ = ']';

	अगर (have_p) अणु
		*p++ = ':';
		p = number(p, pend, ntohs(sa->sin6_port), spec);
	पूर्ण
	अगर (have_f) अणु
		*p++ = '/';
		p = number(p, pend, ntohl(sa->sin6_flowinfo &
					  IPV6_FLOWINFO_MASK), spec);
	पूर्ण
	अगर (have_s) अणु
		*p++ = '%';
		p = number(p, pend, sa->sin6_scope_id, spec);
	पूर्ण
	*p = '\0';

	वापस string_nocheck(buf, end, ip6_addr, spec);
पूर्ण

अटल noअंतरभूत_क्रम_stack
अक्षर *ip4_addr_string_sa(अक्षर *buf, अक्षर *end, स्थिर काष्ठा sockaddr_in *sa,
			 काष्ठा म_लिखो_spec spec, स्थिर अक्षर *fmt)
अणु
	bool have_p = false;
	अक्षर *p, ip4_addr[माप("255.255.255.255") + माप(":12345")];
	अक्षर *pend = ip4_addr + माप(ip4_addr);
	स्थिर u8 *addr = (स्थिर u8 *) &sa->sin_addr.s_addr;
	अक्षर fmt4[3] = अणु fmt[0], '4', 0 पूर्ण;

	fmt++;
	जबतक (है_अक्षर(*++fmt)) अणु
		चयन (*fmt) अणु
		हाल 'p':
			have_p = true;
			अवरोध;
		हाल 'h':
		हाल 'l':
		हाल 'n':
		हाल 'b':
			fmt4[2] = *fmt;
			अवरोध;
		पूर्ण
	पूर्ण

	p = ip4_string(ip4_addr, addr, fmt4);
	अगर (have_p) अणु
		*p++ = ':';
		p = number(p, pend, ntohs(sa->sin_port), spec);
	पूर्ण
	*p = '\0';

	वापस string_nocheck(buf, end, ip4_addr, spec);
पूर्ण

अटल noअंतरभूत_क्रम_stack
अक्षर *ip_addr_string(अक्षर *buf, अक्षर *end, स्थिर व्योम *ptr,
		     काष्ठा म_लिखो_spec spec, स्थिर अक्षर *fmt)
अणु
	अक्षर *err_fmt_msg;

	अगर (check_poपूर्णांकer(&buf, end, ptr, spec))
		वापस buf;

	चयन (fmt[1]) अणु
	हाल '6':
		वापस ip6_addr_string(buf, end, ptr, spec, fmt);
	हाल '4':
		वापस ip4_addr_string(buf, end, ptr, spec, fmt);
	हाल 'S': अणु
		स्थिर जोड़ अणु
			काष्ठा sockaddr		raw;
			काष्ठा sockaddr_in	v4;
			काष्ठा sockaddr_in6	v6;
		पूर्ण *sa = ptr;

		चयन (sa->raw.sa_family) अणु
		हाल AF_INET:
			वापस ip4_addr_string_sa(buf, end, &sa->v4, spec, fmt);
		हाल AF_INET6:
			वापस ip6_addr_string_sa(buf, end, &sa->v6, spec, fmt);
		शेष:
			वापस error_string(buf, end, "(einval)", spec);
		पूर्णपूर्ण
	पूर्ण

	err_fmt_msg = fmt[0] == 'i' ? "(%pi?)" : "(%pI?)";
	वापस error_string(buf, end, err_fmt_msg, spec);
पूर्ण

अटल noअंतरभूत_क्रम_stack
अक्षर *escaped_string(अक्षर *buf, अक्षर *end, u8 *addr, काष्ठा म_लिखो_spec spec,
		     स्थिर अक्षर *fmt)
अणु
	bool found = true;
	पूर्णांक count = 1;
	अचिन्हित पूर्णांक flags = 0;
	पूर्णांक len;

	अगर (spec.field_width == 0)
		वापस buf;				/* nothing to prपूर्णांक */

	अगर (check_poपूर्णांकer(&buf, end, addr, spec))
		वापस buf;

	करो अणु
		चयन (fmt[count++]) अणु
		हाल 'a':
			flags |= ESCAPE_ANY;
			अवरोध;
		हाल 'c':
			flags |= ESCAPE_SPECIAL;
			अवरोध;
		हाल 'h':
			flags |= ESCAPE_HEX;
			अवरोध;
		हाल 'n':
			flags |= ESCAPE_शून्य;
			अवरोध;
		हाल 'o':
			flags |= ESCAPE_OCTAL;
			अवरोध;
		हाल 'p':
			flags |= ESCAPE_NP;
			अवरोध;
		हाल 's':
			flags |= ESCAPE_SPACE;
			अवरोध;
		शेष:
			found = false;
			अवरोध;
		पूर्ण
	पूर्ण जबतक (found);

	अगर (!flags)
		flags = ESCAPE_ANY_NP;

	len = spec.field_width < 0 ? 1 : spec.field_width;

	/*
	 * string_escape_mem() ग_लिखोs as many अक्षरacters as it can to
	 * the given buffer, and वापसs the total size of the output
	 * had the buffer been big enough.
	 */
	buf += string_escape_mem(addr, len, buf, buf < end ? end - buf : 0, flags, शून्य);

	वापस buf;
पूर्ण

अटल अक्षर *va_क्रमmat(अक्षर *buf, अक्षर *end, काष्ठा va_क्रमmat *va_fmt,
		       काष्ठा म_लिखो_spec spec, स्थिर अक्षर *fmt)
अणु
	बहु_सूची va;

	अगर (check_poपूर्णांकer(&buf, end, va_fmt, spec))
		वापस buf;

	va_copy(va, *va_fmt->va);
	buf += vsnम_लिखो(buf, end > buf ? end - buf : 0, va_fmt->fmt, va);
	बहु_पूर्ण(va);

	वापस buf;
पूर्ण

अटल noअंतरभूत_क्रम_stack
अक्षर *uuid_string(अक्षर *buf, अक्षर *end, स्थिर u8 *addr,
		  काष्ठा म_लिखो_spec spec, स्थिर अक्षर *fmt)
अणु
	अक्षर uuid[UUID_STRING_LEN + 1];
	अक्षर *p = uuid;
	पूर्णांक i;
	स्थिर u8 *index = uuid_index;
	bool uc = false;

	अगर (check_poपूर्णांकer(&buf, end, addr, spec))
		वापस buf;

	चयन (*(++fmt)) अणु
	हाल 'L':
		uc = true;
		fallthrough;
	हाल 'l':
		index = guid_index;
		अवरोध;
	हाल 'B':
		uc = true;
		अवरोध;
	पूर्ण

	क्रम (i = 0; i < 16; i++) अणु
		अगर (uc)
			p = hex_byte_pack_upper(p, addr[index[i]]);
		अन्यथा
			p = hex_byte_pack(p, addr[index[i]]);
		चयन (i) अणु
		हाल 3:
		हाल 5:
		हाल 7:
		हाल 9:
			*p++ = '-';
			अवरोध;
		पूर्ण
	पूर्ण

	*p = 0;

	वापस string_nocheck(buf, end, uuid, spec);
पूर्ण

अटल noअंतरभूत_क्रम_stack
अक्षर *netdev_bits(अक्षर *buf, अक्षर *end, स्थिर व्योम *addr,
		  काष्ठा म_लिखो_spec spec,  स्थिर अक्षर *fmt)
अणु
	अचिन्हित दीर्घ दीर्घ num;
	पूर्णांक size;

	अगर (check_poपूर्णांकer(&buf, end, addr, spec))
		वापस buf;

	चयन (fmt[1]) अणु
	हाल 'F':
		num = *(स्थिर netdev_features_t *)addr;
		size = माप(netdev_features_t);
		अवरोध;
	शेष:
		वापस error_string(buf, end, "(%pN?)", spec);
	पूर्ण

	वापस special_hex_number(buf, end, num, size);
पूर्ण

अटल noअंतरभूत_क्रम_stack
अक्षर *fourcc_string(अक्षर *buf, अक्षर *end, स्थिर u32 *fourcc,
		    काष्ठा म_लिखो_spec spec, स्थिर अक्षर *fmt)
अणु
	अक्षर output[माप("0123 little-endian (0x01234567)")];
	अक्षर *p = output;
	अचिन्हित पूर्णांक i;
	u32 val;

	अगर (fmt[1] != 'c' || fmt[2] != 'c')
		वापस error_string(buf, end, "(%p4?)", spec);

	अगर (check_poपूर्णांकer(&buf, end, fourcc, spec))
		वापस buf;

	val = *fourcc & ~BIT(31);

	क्रम (i = 0; i < माप(*fourcc); i++) अणु
		अचिन्हित अक्षर c = val >> (i * 8);

		/* Prपूर्णांक non-control ASCII अक्षरacters as-is, करोt otherwise */
		*p++ = isascii(c) && है_छाप(c) ? c : '.';
	पूर्ण

	म_नकल(p, *fourcc & BIT(31) ? " big-endian" : " little-endian");
	p += म_माप(p);

	*p++ = ' ';
	*p++ = '(';
	p = special_hex_number(p, output + माप(output) - 2, *fourcc, माप(u32));
	*p++ = ')';
	*p = '\0';

	वापस string(buf, end, output, spec);
पूर्ण

अटल noअंतरभूत_क्रम_stack
अक्षर *address_val(अक्षर *buf, अक्षर *end, स्थिर व्योम *addr,
		  काष्ठा म_लिखो_spec spec, स्थिर अक्षर *fmt)
अणु
	अचिन्हित दीर्घ दीर्घ num;
	पूर्णांक size;

	अगर (check_poपूर्णांकer(&buf, end, addr, spec))
		वापस buf;

	चयन (fmt[1]) अणु
	हाल 'd':
		num = *(स्थिर dma_addr_t *)addr;
		size = माप(dma_addr_t);
		अवरोध;
	हाल 'p':
	शेष:
		num = *(स्थिर phys_addr_t *)addr;
		size = माप(phys_addr_t);
		अवरोध;
	पूर्ण

	वापस special_hex_number(buf, end, num, size);
पूर्ण

अटल noअंतरभूत_क्रम_stack
अक्षर *date_str(अक्षर *buf, अक्षर *end, स्थिर काष्ठा rtc_समय *पंचांग, bool r)
अणु
	पूर्णांक year = पंचांग->पंचांग_year + (r ? 0 : 1900);
	पूर्णांक mon = पंचांग->पंचांग_mon + (r ? 0 : 1);

	buf = number(buf, end, year, शेष_dec04_spec);
	अगर (buf < end)
		*buf = '-';
	buf++;

	buf = number(buf, end, mon, शेष_dec02_spec);
	अगर (buf < end)
		*buf = '-';
	buf++;

	वापस number(buf, end, पंचांग->पंचांग_mday, शेष_dec02_spec);
पूर्ण

अटल noअंतरभूत_क्रम_stack
अक्षर *समय_str(अक्षर *buf, अक्षर *end, स्थिर काष्ठा rtc_समय *पंचांग, bool r)
अणु
	buf = number(buf, end, पंचांग->पंचांग_hour, शेष_dec02_spec);
	अगर (buf < end)
		*buf = ':';
	buf++;

	buf = number(buf, end, पंचांग->पंचांग_min, शेष_dec02_spec);
	अगर (buf < end)
		*buf = ':';
	buf++;

	वापस number(buf, end, पंचांग->पंचांग_sec, शेष_dec02_spec);
पूर्ण

अटल noअंतरभूत_क्रम_stack
अक्षर *rtc_str(अक्षर *buf, अक्षर *end, स्थिर काष्ठा rtc_समय *पंचांग,
	      काष्ठा म_लिखो_spec spec, स्थिर अक्षर *fmt)
अणु
	bool have_t = true, have_d = true;
	bool raw = false;
	पूर्णांक count = 2;

	अगर (check_poपूर्णांकer(&buf, end, पंचांग, spec))
		वापस buf;

	चयन (fmt[count]) अणु
	हाल 'd':
		have_t = false;
		count++;
		अवरोध;
	हाल 't':
		have_d = false;
		count++;
		अवरोध;
	पूर्ण

	raw = fmt[count] == 'r';

	अगर (have_d)
		buf = date_str(buf, end, पंचांग, raw);
	अगर (have_d && have_t) अणु
		/* Respect ISO 8601 */
		अगर (buf < end)
			*buf = 'T';
		buf++;
	पूर्ण
	अगर (have_t)
		buf = समय_str(buf, end, पंचांग, raw);

	वापस buf;
पूर्ण

अटल noअंतरभूत_क्रम_stack
अक्षर *समय64_str(अक्षर *buf, अक्षर *end, स्थिर समय64_t समय,
		 काष्ठा म_लिखो_spec spec, स्थिर अक्षर *fmt)
अणु
	काष्ठा rtc_समय rtc_समय;
	काष्ठा पंचांग पंचांग;

	समय64_to_पंचांग(समय, 0, &पंचांग);

	rtc_समय.पंचांग_sec = पंचांग.पंचांग_sec;
	rtc_समय.पंचांग_min = पंचांग.पंचांग_min;
	rtc_समय.पंचांग_hour = पंचांग.पंचांग_hour;
	rtc_समय.पंचांग_mday = पंचांग.पंचांग_mday;
	rtc_समय.पंचांग_mon = पंचांग.पंचांग_mon;
	rtc_समय.पंचांग_year = पंचांग.पंचांग_year;
	rtc_समय.पंचांग_wday = पंचांग.पंचांग_wday;
	rtc_समय.पंचांग_yday = पंचांग.पंचांग_yday;

	rtc_समय.पंचांग_isdst = 0;

	वापस rtc_str(buf, end, &rtc_समय, spec, fmt);
पूर्ण

अटल noअंतरभूत_क्रम_stack
अक्षर *समय_and_date(अक्षर *buf, अक्षर *end, व्योम *ptr, काष्ठा म_लिखो_spec spec,
		    स्थिर अक्षर *fmt)
अणु
	चयन (fmt[1]) अणु
	हाल 'R':
		वापस rtc_str(buf, end, (स्थिर काष्ठा rtc_समय *)ptr, spec, fmt);
	हाल 'T':
		वापस समय64_str(buf, end, *(स्थिर समय64_t *)ptr, spec, fmt);
	शेष:
		वापस error_string(buf, end, "(%pt?)", spec);
	पूर्ण
पूर्ण

अटल noअंतरभूत_क्रम_stack
अक्षर *घड़ी(अक्षर *buf, अक्षर *end, काष्ठा clk *clk, काष्ठा म_लिखो_spec spec,
	    स्थिर अक्षर *fmt)
अणु
	अगर (!IS_ENABLED(CONFIG_HAVE_CLK))
		वापस error_string(buf, end, "(%pC?)", spec);

	अगर (check_poपूर्णांकer(&buf, end, clk, spec))
		वापस buf;

	चयन (fmt[1]) अणु
	हाल 'n':
	शेष:
#अगर_घोषित CONFIG_COMMON_CLK
		वापस string(buf, end, __clk_get_name(clk), spec);
#अन्यथा
		वापस ptr_to_id(buf, end, clk, spec);
#पूर्ण_अगर
	पूर्ण
पूर्ण

अटल
अक्षर *क्रमmat_flags(अक्षर *buf, अक्षर *end, अचिन्हित दीर्घ flags,
					स्थिर काष्ठा trace_prपूर्णांक_flags *names)
अणु
	अचिन्हित दीर्घ mask;

	क्रम ( ; flags && names->name; names++) अणु
		mask = names->mask;
		अगर ((flags & mask) != mask)
			जारी;

		buf = string(buf, end, names->name, शेष_str_spec);

		flags &= ~mask;
		अगर (flags) अणु
			अगर (buf < end)
				*buf = '|';
			buf++;
		पूर्ण
	पूर्ण

	अगर (flags)
		buf = number(buf, end, flags, शेष_flag_spec);

	वापस buf;
पूर्ण

काष्ठा page_flags_fields अणु
	पूर्णांक width;
	पूर्णांक shअगरt;
	पूर्णांक mask;
	स्थिर काष्ठा म_लिखो_spec *spec;
	स्थिर अक्षर *name;
पूर्ण;

अटल स्थिर काष्ठा page_flags_fields pff[] = अणु
	अणुSECTIONS_WIDTH, SECTIONS_PGSHIFT, SECTIONS_MASK,
	 &शेष_dec_spec, "section"पूर्ण,
	अणुNODES_WIDTH, NODES_PGSHIFT, NODES_MASK,
	 &शेष_dec_spec, "node"पूर्ण,
	अणुZONES_WIDTH, ZONES_PGSHIFT, ZONES_MASK,
	 &शेष_dec_spec, "zone"पूर्ण,
	अणुLAST_CPUPID_WIDTH, LAST_CPUPID_PGSHIFT, LAST_CPUPID_MASK,
	 &शेष_flag_spec, "lastcpupid"पूर्ण,
	अणुKASAN_TAG_WIDTH, KASAN_TAG_PGSHIFT, KASAN_TAG_MASK,
	 &शेष_flag_spec, "kasantag"पूर्ण,
पूर्ण;

अटल
अक्षर *क्रमmat_page_flags(अक्षर *buf, अक्षर *end, अचिन्हित दीर्घ flags)
अणु
	अचिन्हित दीर्घ मुख्य_flags = flags & (BIT(NR_PAGEFLAGS) - 1);
	bool append = false;
	पूर्णांक i;

	/* Page flags from the मुख्य area. */
	अगर (मुख्य_flags) अणु
		buf = क्रमmat_flags(buf, end, मुख्य_flags, pageflag_names);
		append = true;
	पूर्ण

	/* Page flags from the fields area */
	क्रम (i = 0; i < ARRAY_SIZE(pff); i++) अणु
		/* Skip undefined fields. */
		अगर (!pff[i].width)
			जारी;

		/* Format: Flag Name + '=' (equals sign) + Number + '|' (separator) */
		अगर (append) अणु
			अगर (buf < end)
				*buf = '|';
			buf++;
		पूर्ण

		buf = string(buf, end, pff[i].name, शेष_str_spec);
		अगर (buf < end)
			*buf = '=';
		buf++;
		buf = number(buf, end, (flags >> pff[i].shअगरt) & pff[i].mask,
			     *pff[i].spec);

		append = true;
	पूर्ण

	वापस buf;
पूर्ण

अटल noअंतरभूत_क्रम_stack
अक्षर *flags_string(अक्षर *buf, अक्षर *end, व्योम *flags_ptr,
		   काष्ठा म_लिखो_spec spec, स्थिर अक्षर *fmt)
अणु
	अचिन्हित दीर्घ flags;
	स्थिर काष्ठा trace_prपूर्णांक_flags *names;

	अगर (check_poपूर्णांकer(&buf, end, flags_ptr, spec))
		वापस buf;

	चयन (fmt[1]) अणु
	हाल 'p':
		वापस क्रमmat_page_flags(buf, end, *(अचिन्हित दीर्घ *)flags_ptr);
	हाल 'v':
		flags = *(अचिन्हित दीर्घ *)flags_ptr;
		names = vmaflag_names;
		अवरोध;
	हाल 'g':
		flags = (__क्रमce अचिन्हित दीर्घ)(*(gfp_t *)flags_ptr);
		names = gfpflag_names;
		अवरोध;
	शेष:
		वापस error_string(buf, end, "(%pG?)", spec);
	पूर्ण

	वापस क्रमmat_flags(buf, end, flags, names);
पूर्ण

अटल noअंतरभूत_क्रम_stack
अक्षर *fwnode_full_name_string(काष्ठा fwnode_handle *fwnode, अक्षर *buf,
			      अक्षर *end)
अणु
	पूर्णांक depth;

	/* Loop starting from the root node to the current node. */
	क्रम (depth = fwnode_count_parents(fwnode); depth >= 0; depth--) अणु
		काष्ठा fwnode_handle *__fwnode =
			fwnode_get_nth_parent(fwnode, depth);

		buf = string(buf, end, fwnode_get_name_prefix(__fwnode),
			     शेष_str_spec);
		buf = string(buf, end, fwnode_get_name(__fwnode),
			     शेष_str_spec);

		fwnode_handle_put(__fwnode);
	पूर्ण

	वापस buf;
पूर्ण

अटल noअंतरभूत_क्रम_stack
अक्षर *device_node_string(अक्षर *buf, अक्षर *end, काष्ठा device_node *dn,
			 काष्ठा म_लिखो_spec spec, स्थिर अक्षर *fmt)
अणु
	अक्षर tbuf[माप("xxxx") + 1];
	स्थिर अक्षर *p;
	पूर्णांक ret;
	अक्षर *buf_start = buf;
	काष्ठा property *prop;
	bool has_mult, pass;

	काष्ठा म_लिखो_spec str_spec = spec;
	str_spec.field_width = -1;

	अगर (fmt[0] != 'F')
		वापस error_string(buf, end, "(%pO?)", spec);

	अगर (!IS_ENABLED(CONFIG_OF))
		वापस error_string(buf, end, "(%pOF?)", spec);

	अगर (check_poपूर्णांकer(&buf, end, dn, spec))
		वापस buf;

	/* simple हाल without anything any more क्रमmat specअगरiers */
	fmt++;
	अगर (fmt[0] == '\0' || म_खोज(fmt,"fnpPFcC") > 0)
		fmt = "f";

	क्रम (pass = false; म_अखोज(fmt,"fnpPFcC"); fmt++, pass = true) अणु
		पूर्णांक precision;
		अगर (pass) अणु
			अगर (buf < end)
				*buf = ':';
			buf++;
		पूर्ण

		चयन (*fmt) अणु
		हाल 'f':	/* full_name */
			buf = fwnode_full_name_string(of_fwnode_handle(dn), buf,
						      end);
			अवरोध;
		हाल 'n':	/* name */
			p = fwnode_get_name(of_fwnode_handle(dn));
			precision = str_spec.precision;
			str_spec.precision = म_अक्षरnul(p, '@') - p;
			buf = string(buf, end, p, str_spec);
			str_spec.precision = precision;
			अवरोध;
		हाल 'p':	/* phandle */
			buf = number(buf, end, (अचिन्हित पूर्णांक)dn->phandle, शेष_dec_spec);
			अवरोध;
		हाल 'P':	/* path-spec */
			p = fwnode_get_name(of_fwnode_handle(dn));
			अगर (!p[1])
				p = "/";
			buf = string(buf, end, p, str_spec);
			अवरोध;
		हाल 'F':	/* flags */
			tbuf[0] = of_node_check_flag(dn, OF_DYNAMIC) ? 'D' : '-';
			tbuf[1] = of_node_check_flag(dn, OF_DETACHED) ? 'd' : '-';
			tbuf[2] = of_node_check_flag(dn, OF_POPULATED) ? 'P' : '-';
			tbuf[3] = of_node_check_flag(dn, OF_POPULATED_BUS) ? 'B' : '-';
			tbuf[4] = 0;
			buf = string_nocheck(buf, end, tbuf, str_spec);
			अवरोध;
		हाल 'c':	/* major compatible string */
			ret = of_property_पढ़ो_string(dn, "compatible", &p);
			अगर (!ret)
				buf = string(buf, end, p, str_spec);
			अवरोध;
		हाल 'C':	/* full compatible string */
			has_mult = false;
			of_property_क्रम_each_string(dn, "compatible", prop, p) अणु
				अगर (has_mult)
					buf = string_nocheck(buf, end, ",", str_spec);
				buf = string_nocheck(buf, end, "\"", str_spec);
				buf = string(buf, end, p, str_spec);
				buf = string_nocheck(buf, end, "\"", str_spec);

				has_mult = true;
			पूर्ण
			अवरोध;
		शेष:
			अवरोध;
		पूर्ण
	पूर्ण

	वापस widen_string(buf, buf - buf_start, end, spec);
पूर्ण

अटल noअंतरभूत_क्रम_stack
अक्षर *fwnode_string(अक्षर *buf, अक्षर *end, काष्ठा fwnode_handle *fwnode,
		    काष्ठा म_लिखो_spec spec, स्थिर अक्षर *fmt)
अणु
	काष्ठा म_लिखो_spec str_spec = spec;
	अक्षर *buf_start = buf;

	str_spec.field_width = -1;

	अगर (*fmt != 'w')
		वापस error_string(buf, end, "(%pf?)", spec);

	अगर (check_poपूर्णांकer(&buf, end, fwnode, spec))
		वापस buf;

	fmt++;

	चयन (*fmt) अणु
	हाल 'P':	/* name */
		buf = string(buf, end, fwnode_get_name(fwnode), str_spec);
		अवरोध;
	हाल 'f':	/* full_name */
	शेष:
		buf = fwnode_full_name_string(fwnode, buf, end);
		अवरोध;
	पूर्ण

	वापस widen_string(buf, buf - buf_start, end, spec);
पूर्ण

/* Disable poपूर्णांकer hashing अगर requested */
bool no_hash_poपूर्णांकers __ro_after_init;
EXPORT_SYMBOL_GPL(no_hash_poपूर्णांकers);

अटल पूर्णांक __init no_hash_poपूर्णांकers_enable(अक्षर *str)
अणु
	अगर (no_hash_poपूर्णांकers)
		वापस 0;

	no_hash_poपूर्णांकers = true;

	pr_warn("**********************************************************\n");
	pr_warn("**   NOTICE NOTICE NOTICE NOTICE NOTICE NOTICE NOTICE   **\n");
	pr_warn("**                                                      **\n");
	pr_warn("** This system shows unhashed kernel memory addresses   **\n");
	pr_warn("** via the console, logs, and other interfaces. This    **\n");
	pr_warn("** might reduce the security of your system.            **\n");
	pr_warn("**                                                      **\n");
	pr_warn("** If you see this message and you are not debugging    **\n");
	pr_warn("** the kernel, report this immediately to your system   **\n");
	pr_warn("** administrator!                                       **\n");
	pr_warn("**                                                      **\n");
	pr_warn("**   NOTICE NOTICE NOTICE NOTICE NOTICE NOTICE NOTICE   **\n");
	pr_warn("**********************************************************\n");

	वापस 0;
पूर्ण
early_param("no_hash_pointers", no_hash_poपूर्णांकers_enable);

/*
 * Show a '%p' thing.  A kernel extension is that the '%p' is followed
 * by an extra set of alphanumeric अक्षरacters that are extended क्रमmat
 * specअगरiers.
 *
 * Please update scripts/checkpatch.pl when adding/removing conversion
 * अक्षरacters.  (Search क्रम "check for vsprintf extension").
 *
 * Right now we handle:
 *
 * - 'S' For symbolic direct poपूर्णांकers (or function descriptors) with offset
 * - 's' For symbolic direct poपूर्णांकers (or function descriptors) without offset
 * - '[Ss]R' as above with __builtin_extract_वापस_addr() translation
 * - '[Ff]' %pf and %pF were obsoleted and later हटाओd in favor of
 *	    %ps and %pS. Be careful when re-using these specअगरiers.
 * - 'B' For backtraced symbolic direct poपूर्णांकers with offset
 * - 'R' For decoded काष्ठा resource, e.g., [mem 0x0-0x1f 64bit pref]
 * - 'r' For raw काष्ठा resource, e.g., [mem 0x0-0x1f flags 0x201]
 * - 'b[l]' For a biपंचांगap, the number of bits is determined by the field
 *       width which must be explicitly specअगरied either as part of the
 *       क्रमmat string '%32b[l]' or through '%*b[l]', [l] selects
 *       range-list क्रमmat instead of hex क्रमmat
 * - 'M' For a 6-byte MAC address, it prपूर्णांकs the address in the
 *       usual colon-separated hex notation
 * - 'm' For a 6-byte MAC address, it prपूर्णांकs the hex address without colons
 * - 'MF' For a 6-byte MAC FDDI address, it prपूर्णांकs the address
 *       with a dash-separated hex notation
 * - '[mM]R' For a 6-byte MAC address, Reverse order (Bluetooth)
 * - 'I' [46] क्रम IPv4/IPv6 addresses prपूर्णांकed in the usual way
 *       IPv4 uses करोt-separated decimal without leading 0's (1.2.3.4)
 *       IPv6 uses colon separated network-order 16 bit hex with leading 0's
 *       [S][pfs]
 *       Generic IPv4/IPv6 address (काष्ठा sockaddr *) that falls back to
 *       [4] or [6] and is able to prपूर्णांक port [p], flowinfo [f], scope [s]
 * - 'i' [46] for 'raw' IPv4/IPv6 addresses
 *       IPv6 omits the colons (01020304...0f)
 *       IPv4 uses करोt-separated decimal with leading 0's (010.123.045.006)
 *       [S][pfs]
 *       Generic IPv4/IPv6 address (काष्ठा sockaddr *) that falls back to
 *       [4] or [6] and is able to prपूर्णांक port [p], flowinfo [f], scope [s]
 * - '[Ii][4S][hnbl]' IPv4 addresses in host, network, big or little endian order
 * - 'I[6S]c' क्रम IPv6 addresses prपूर्णांकed as specअगरied by
 *       https://tools.ietf.org/hपंचांगl/rfc5952
 * - 'E[achnops]' For an escaped buffer, where rules are defined by combination
 *                of the following flags (see string_escape_mem() क्रम the
 *                details):
 *                  a - ESCAPE_ANY
 *                  c - ESCAPE_SPECIAL
 *                  h - ESCAPE_HEX
 *                  n - ESCAPE_शून्य
 *                  o - ESCAPE_OCTAL
 *                  p - ESCAPE_NP
 *                  s - ESCAPE_SPACE
 *                By शेष ESCAPE_ANY_NP is used.
 * - 'U' For a 16 byte UUID/GUID, it prपूर्णांकs the UUID/GUID in the क्रमm
 *       "xxxxxxxx-xxxx-xxxx-xxxx-xxxxxxxxxxxx"
 *       Options क्रम %pU are:
 *         b big endian lower हाल hex (शेष)
 *         B big endian UPPER हाल hex
 *         l little endian lower हाल hex
 *         L little endian UPPER हाल hex
 *           big endian output byte order is:
 *             [0][1][2][3]-[4][5]-[6][7]-[8][9]-[10][11][12][13][14][15]
 *           little endian output byte order is:
 *             [3][2][1][0]-[5][4]-[7][6]-[8][9]-[10][11][12][13][14][15]
 * - 'V' For a काष्ठा va_क्रमmat which contains a क्रमmat string * and बहु_सूची *,
 *       call vsnम_लिखो(->क्रमmat, *->बहु_सूची).
 *       Implements a "recursive vsnprintf".
 *       Do not use this feature without some mechanism to verअगरy the
 *       correctness of the क्रमmat string and बहु_सूची arguments.
 * - 'K' For a kernel poपूर्णांकer that should be hidden from unprivileged users.
 *       Use only क्रम procfs, sysfs and similar files, not prपूर्णांकk(); please
 *       पढ़ो the करोcumentation (path below) first.
 * - 'NF' For a netdev_features_t
 * - '4cc' V4L2 or DRM FourCC code, with endianness and raw numerical value.
 * - 'h[CDN]' For a variable-length buffer, it prपूर्णांकs it as a hex string with
 *            a certain separator (' ' by शेष):
 *              C colon
 *              D dash
 *              N no separator
 *            The maximum supported length is 64 bytes of the input. Consider
 *            to use prपूर्णांक_hex_dump() क्रम the larger input.
 * - 'a[pd]' For address types [p] phys_addr_t, [d] dma_addr_t and derivatives
 *           (शेष assumed to be phys_addr_t, passed by reference)
 * - 'd[234]' For a dentry name (optionally 2-4 last components)
 * - 'D[234]' Same as 'd' but क्रम a काष्ठा file
 * - 'g' For block_device name (gendisk + partition number)
 * - 't[RT][dt][r]' For समय and date as represented by:
 *      R    काष्ठा rtc_समय
 *      T    समय64_t
 * - 'C' For a घड़ी, it prपूर्णांकs the name (Common Clock Framework) or address
 *       (legacy घड़ी framework) of the घड़ी
 * - 'Cn' For a घड़ी, it prपूर्णांकs the name (Common Clock Framework) or address
 *        (legacy घड़ी framework) of the घड़ी
 * - 'G' For flags to be prपूर्णांकed as a collection of symbolic strings that would
 *       स्थिरruct the specअगरic value. Supported flags given by option:
 *       p page flags (see काष्ठा page) given as poपूर्णांकer to अचिन्हित दीर्घ
 *       g gfp flags (GFP_* and __GFP_*) given as poपूर्णांकer to gfp_t
 *       v vma flags (VM_*) given as poपूर्णांकer to अचिन्हित दीर्घ
 * - 'OF[fnpPcCF]'  For a device tree object
 *                  Without any optional arguments prपूर्णांकs the full_name
 *                  f device node full_name
 *                  n device node name
 *                  p device node phandle
 *                  P device node path spec (name + @unit)
 *                  F device node flags
 *                  c major compatible string
 *                  C full compatible string
 * - 'fw[fP]'	For a firmware node (काष्ठा fwnode_handle) poपूर्णांकer
 *		Without an option prपूर्णांकs the full name of the node
 *		f full name
 *		P node name, including a possible unit address
 * - 'x' For prपूर्णांकing the address unmodअगरied. Equivalent to "%lx".
 *       Please पढ़ो the करोcumentation (path below) beक्रमe using!
 * - '[ku]s' For a BPF/tracing related क्रमmat specअगरier, e.g. used out of
 *           bpf_trace_prपूर्णांकk() where [ku] prefix specअगरies either kernel (k)
 *           or user (u) memory to probe, and:
 *              s a string, equivalent to "%s" on direct vsnम_लिखो() use
 *
 * ** When making changes please also update:
 *	Documentation/core-api/prपूर्णांकk-क्रमmats.rst
 *
 * Note: The शेष behaviour (unaकरोrned %p) is to hash the address,
 * rendering it useful as a unique identअगरier.
 */
अटल noअंतरभूत_क्रम_stack
अक्षर *poपूर्णांकer(स्थिर अक्षर *fmt, अक्षर *buf, अक्षर *end, व्योम *ptr,
	      काष्ठा म_लिखो_spec spec)
अणु
	चयन (*fmt) अणु
	हाल 'S':
	हाल 's':
		ptr = dereference_symbol_descriptor(ptr);
		fallthrough;
	हाल 'B':
		वापस symbol_string(buf, end, ptr, spec, fmt);
	हाल 'R':
	हाल 'r':
		वापस resource_string(buf, end, ptr, spec, fmt);
	हाल 'h':
		वापस hex_string(buf, end, ptr, spec, fmt);
	हाल 'b':
		चयन (fmt[1]) अणु
		हाल 'l':
			वापस biपंचांगap_list_string(buf, end, ptr, spec, fmt);
		शेष:
			वापस biपंचांगap_string(buf, end, ptr, spec, fmt);
		पूर्ण
	हाल 'M':			/* Colon separated: 00:01:02:03:04:05 */
	हाल 'm':			/* Contiguous: 000102030405 */
					/* [mM]F (FDDI) */
					/* [mM]R (Reverse order; Bluetooth) */
		वापस mac_address_string(buf, end, ptr, spec, fmt);
	हाल 'I':			/* Formatted IP supported
					 * 4:	1.2.3.4
					 * 6:	0001:0203:...:0708
					 * 6c:	1::708 or 1::1.2.3.4
					 */
	हाल 'i':			/* Contiguous:
					 * 4:	001.002.003.004
					 * 6:   000102...0f
					 */
		वापस ip_addr_string(buf, end, ptr, spec, fmt);
	हाल 'E':
		वापस escaped_string(buf, end, ptr, spec, fmt);
	हाल 'U':
		वापस uuid_string(buf, end, ptr, spec, fmt);
	हाल 'V':
		वापस va_क्रमmat(buf, end, ptr, spec, fmt);
	हाल 'K':
		वापस restricted_poपूर्णांकer(buf, end, ptr, spec);
	हाल 'N':
		वापस netdev_bits(buf, end, ptr, spec, fmt);
	हाल '4':
		वापस fourcc_string(buf, end, ptr, spec, fmt);
	हाल 'a':
		वापस address_val(buf, end, ptr, spec, fmt);
	हाल 'd':
		वापस dentry_name(buf, end, ptr, spec, fmt);
	हाल 't':
		वापस समय_and_date(buf, end, ptr, spec, fmt);
	हाल 'C':
		वापस घड़ी(buf, end, ptr, spec, fmt);
	हाल 'D':
		वापस file_dentry_name(buf, end, ptr, spec, fmt);
#अगर_घोषित CONFIG_BLOCK
	हाल 'g':
		वापस bdev_name(buf, end, ptr, spec, fmt);
#पूर्ण_अगर

	हाल 'G':
		वापस flags_string(buf, end, ptr, spec, fmt);
	हाल 'O':
		वापस device_node_string(buf, end, ptr, spec, fmt + 1);
	हाल 'f':
		वापस fwnode_string(buf, end, ptr, spec, fmt + 1);
	हाल 'x':
		वापस poपूर्णांकer_string(buf, end, ptr, spec);
	हाल 'e':
		/* %pe with a non-ERR_PTR माला_लो treated as plain %p */
		अगर (!IS_ERR(ptr))
			अवरोध;
		वापस err_ptr(buf, end, ptr, spec);
	हाल 'u':
	हाल 'k':
		चयन (fmt[1]) अणु
		हाल 's':
			वापस string(buf, end, ptr, spec);
		शेष:
			वापस error_string(buf, end, "(einval)", spec);
		पूर्ण
	पूर्ण

	/*
	 * शेष is to _not_ leak addresses, so hash beक्रमe prपूर्णांकing,
	 * unless no_hash_poपूर्णांकers is specअगरied on the command line.
	 */
	अगर (unlikely(no_hash_poपूर्णांकers))
		वापस poपूर्णांकer_string(buf, end, ptr, spec);
	अन्यथा
		वापस ptr_to_id(buf, end, ptr, spec);
पूर्ण

/*
 * Helper function to decode म_लिखो style क्रमmat.
 * Each call decode a token from the क्रमmat and वापस the
 * number of अक्षरacters पढ़ो (or likely the delta where it wants
 * to go on the next call).
 * The decoded token is वापसed through the parameters
 *
 * 'h', 'l', or 'L' क्रम पूर्णांकeger fields
 * 'z' support added 23/7/1999 S.H.
 * 'z' changed to 'Z' --davidm 1/25/99
 * 'Z' changed to 'z' --aकरोbriyan 2017-01-25
 * 't' added क्रम सूचक_भेद_प्रकार
 *
 * @fmt: the क्रमmat string
 * @type of the token वापसed
 * @flags: various flags such as +, -, # tokens..
 * @field_width: overwritten width
 * @base: base of the number (octal, hex, ...)
 * @precision: precision of a number
 * @qualअगरier: qualअगरier of a number (दीर्घ, माप_प्रकार, ...)
 */
अटल noअंतरभूत_क्रम_stack
पूर्णांक क्रमmat_decode(स्थिर अक्षर *fmt, काष्ठा म_लिखो_spec *spec)
अणु
	स्थिर अक्षर *start = fmt;
	अक्षर qualअगरier;

	/* we finished early by पढ़ोing the field width */
	अगर (spec->type == FORMAT_TYPE_WIDTH) अणु
		अगर (spec->field_width < 0) अणु
			spec->field_width = -spec->field_width;
			spec->flags |= LEFT;
		पूर्ण
		spec->type = FORMAT_TYPE_NONE;
		जाओ precision;
	पूर्ण

	/* we finished early by पढ़ोing the precision */
	अगर (spec->type == FORMAT_TYPE_PRECISION) अणु
		अगर (spec->precision < 0)
			spec->precision = 0;

		spec->type = FORMAT_TYPE_NONE;
		जाओ qualअगरier;
	पूर्ण

	/* By शेष */
	spec->type = FORMAT_TYPE_NONE;

	क्रम (; *fmt ; ++fmt) अणु
		अगर (*fmt == '%')
			अवरोध;
	पूर्ण

	/* Return the current non-क्रमmat string */
	अगर (fmt != start || !*fmt)
		वापस fmt - start;

	/* Process flags */
	spec->flags = 0;

	जबतक (1) अणु /* this also skips first '%' */
		bool found = true;

		++fmt;

		चयन (*fmt) अणु
		हाल '-': spec->flags |= LEFT;    अवरोध;
		हाल '+': spec->flags |= PLUS;    अवरोध;
		हाल ' ': spec->flags |= SPACE;   अवरोध;
		हाल '#': spec->flags |= SPECIAL; अवरोध;
		हाल '0': spec->flags |= ZEROPAD; अवरोध;
		शेष:  found = false;
		पूर्ण

		अगर (!found)
			अवरोध;
	पूर्ण

	/* get field width */
	spec->field_width = -1;

	अगर (है_अंक(*fmt))
		spec->field_width = skip_म_से_प(&fmt);
	अन्यथा अगर (*fmt == '*') अणु
		/* it's the next argument */
		spec->type = FORMAT_TYPE_WIDTH;
		वापस ++fmt - start;
	पूर्ण

precision:
	/* get the precision */
	spec->precision = -1;
	अगर (*fmt == '.') अणु
		++fmt;
		अगर (है_अंक(*fmt)) अणु
			spec->precision = skip_म_से_प(&fmt);
			अगर (spec->precision < 0)
				spec->precision = 0;
		पूर्ण अन्यथा अगर (*fmt == '*') अणु
			/* it's the next argument */
			spec->type = FORMAT_TYPE_PRECISION;
			वापस ++fmt - start;
		पूर्ण
	पूर्ण

qualअगरier:
	/* get the conversion qualअगरier */
	qualअगरier = 0;
	अगर (*fmt == 'h' || _tolower(*fmt) == 'l' ||
	    *fmt == 'z' || *fmt == 't') अणु
		qualअगरier = *fmt++;
		अगर (unlikely(qualअगरier == *fmt)) अणु
			अगर (qualअगरier == 'l') अणु
				qualअगरier = 'L';
				++fmt;
			पूर्ण अन्यथा अगर (qualअगरier == 'h') अणु
				qualअगरier = 'H';
				++fmt;
			पूर्ण
		पूर्ण
	पूर्ण

	/* शेष base */
	spec->base = 10;
	चयन (*fmt) अणु
	हाल 'c':
		spec->type = FORMAT_TYPE_CHAR;
		वापस ++fmt - start;

	हाल 's':
		spec->type = FORMAT_TYPE_STR;
		वापस ++fmt - start;

	हाल 'p':
		spec->type = FORMAT_TYPE_PTR;
		वापस ++fmt - start;

	हाल '%':
		spec->type = FORMAT_TYPE_PERCENT_CHAR;
		वापस ++fmt - start;

	/* पूर्णांकeger number क्रमmats - set up the flags and "break" */
	हाल 'o':
		spec->base = 8;
		अवरोध;

	हाल 'x':
		spec->flags |= SMALL;
		fallthrough;

	हाल 'X':
		spec->base = 16;
		अवरोध;

	हाल 'd':
	हाल 'i':
		spec->flags |= SIGN;
		अवरोध;
	हाल 'u':
		अवरोध;

	हाल 'n':
		/*
		 * Since %n poses a greater security risk than
		 * utility, treat it as any other invalid or
		 * unsupported क्रमmat specअगरier.
		 */
		fallthrough;

	शेष:
		WARN_ONCE(1, "Please remove unsupported %%%c in format string\n", *fmt);
		spec->type = FORMAT_TYPE_INVALID;
		वापस fmt - start;
	पूर्ण

	अगर (qualअगरier == 'L')
		spec->type = FORMAT_TYPE_LONG_LONG;
	अन्यथा अगर (qualअगरier == 'l') अणु
		BUILD_BUG_ON(FORMAT_TYPE_ULONG + SIGN != FORMAT_TYPE_LONG);
		spec->type = FORMAT_TYPE_ULONG + (spec->flags & SIGN);
	पूर्ण अन्यथा अगर (qualअगरier == 'z') अणु
		spec->type = FORMAT_TYPE_SIZE_T;
	पूर्ण अन्यथा अगर (qualअगरier == 't') अणु
		spec->type = FORMAT_TYPE_PTRDIFF;
	पूर्ण अन्यथा अगर (qualअगरier == 'H') अणु
		BUILD_BUG_ON(FORMAT_TYPE_UBYTE + SIGN != FORMAT_TYPE_BYTE);
		spec->type = FORMAT_TYPE_UBYTE + (spec->flags & SIGN);
	पूर्ण अन्यथा अगर (qualअगरier == 'h') अणु
		BUILD_BUG_ON(FORMAT_TYPE_USHORT + SIGN != FORMAT_TYPE_SHORT);
		spec->type = FORMAT_TYPE_USHORT + (spec->flags & SIGN);
	पूर्ण अन्यथा अणु
		BUILD_BUG_ON(FORMAT_TYPE_UINT + SIGN != FORMAT_TYPE_INT);
		spec->type = FORMAT_TYPE_UINT + (spec->flags & SIGN);
	पूर्ण

	वापस ++fmt - start;
पूर्ण

अटल व्योम
set_field_width(काष्ठा म_लिखो_spec *spec, पूर्णांक width)
अणु
	spec->field_width = width;
	अगर (WARN_ONCE(spec->field_width != width, "field width %d too large", width)) अणु
		spec->field_width = clamp(width, -FIELD_WIDTH_MAX, FIELD_WIDTH_MAX);
	पूर्ण
पूर्ण

अटल व्योम
set_precision(काष्ठा म_लिखो_spec *spec, पूर्णांक prec)
अणु
	spec->precision = prec;
	अगर (WARN_ONCE(spec->precision != prec, "precision %d too large", prec)) अणु
		spec->precision = clamp(prec, 0, PRECISION_MAX);
	पूर्ण
पूर्ण

/**
 * vsnम_लिखो - Format a string and place it in a buffer
 * @buf: The buffer to place the result पूर्णांकo
 * @size: The size of the buffer, including the trailing null space
 * @fmt: The क्रमmat string to use
 * @args: Arguments क्रम the क्रमmat string
 *
 * This function generally follows C99 vsnम_लिखो, but has some
 * extensions and a few limitations:
 *
 *  - ``%n`` is unsupported
 *  - ``%p*`` is handled by poपूर्णांकer()
 *
 * See poपूर्णांकer() or Documentation/core-api/prपूर्णांकk-क्रमmats.rst क्रम more
 * extensive description.
 *
 * **Please update the करोcumentation in both places when making changes**
 *
 * The वापस value is the number of अक्षरacters which would
 * be generated क्रम the given input, excluding the trailing
 * '\0', as per ISO C99. If you want to have the exact
 * number of अक्षरacters written पूर्णांकo @buf as वापस value
 * (not including the trailing '\0'), use vscnम_लिखो(). If the
 * वापस is greater than or equal to @size, the resulting
 * string is truncated.
 *
 * If you're not alपढ़ोy dealing with a बहु_सूची consider using snम_लिखो().
 */
पूर्णांक vsnम_लिखो(अक्षर *buf, माप_प्रकार size, स्थिर अक्षर *fmt, बहु_सूची args)
अणु
	अचिन्हित दीर्घ दीर्घ num;
	अक्षर *str, *end;
	काष्ठा म_लिखो_spec spec = अणु0पूर्ण;

	/* Reject out-of-range values early.  Large positive sizes are
	   used क्रम unknown buffer sizes. */
	अगर (WARN_ON_ONCE(size > पूर्णांक_उच्च))
		वापस 0;

	str = buf;
	end = buf + size;

	/* Make sure end is always >= buf */
	अगर (end < buf) अणु
		end = ((व्योम *)-1);
		size = end - buf;
	पूर्ण

	जबतक (*fmt) अणु
		स्थिर अक्षर *old_fmt = fmt;
		पूर्णांक पढ़ो = क्रमmat_decode(fmt, &spec);

		fmt += पढ़ो;

		चयन (spec.type) अणु
		हाल FORMAT_TYPE_NONE: अणु
			पूर्णांक copy = पढ़ो;
			अगर (str < end) अणु
				अगर (copy > end - str)
					copy = end - str;
				स_नकल(str, old_fmt, copy);
			पूर्ण
			str += पढ़ो;
			अवरोध;
		पूर्ण

		हाल FORMAT_TYPE_WIDTH:
			set_field_width(&spec, बहु_तर्क(args, पूर्णांक));
			अवरोध;

		हाल FORMAT_TYPE_PRECISION:
			set_precision(&spec, बहु_तर्क(args, पूर्णांक));
			अवरोध;

		हाल FORMAT_TYPE_CHAR: अणु
			अक्षर c;

			अगर (!(spec.flags & LEFT)) अणु
				जबतक (--spec.field_width > 0) अणु
					अगर (str < end)
						*str = ' ';
					++str;

				पूर्ण
			पूर्ण
			c = (अचिन्हित अक्षर) बहु_तर्क(args, पूर्णांक);
			अगर (str < end)
				*str = c;
			++str;
			जबतक (--spec.field_width > 0) अणु
				अगर (str < end)
					*str = ' ';
				++str;
			पूर्ण
			अवरोध;
		पूर्ण

		हाल FORMAT_TYPE_STR:
			str = string(str, end, बहु_तर्क(args, अक्षर *), spec);
			अवरोध;

		हाल FORMAT_TYPE_PTR:
			str = poपूर्णांकer(fmt, str, end, बहु_तर्क(args, व्योम *),
				      spec);
			जबतक (है_अक्षर_अंक(*fmt))
				fmt++;
			अवरोध;

		हाल FORMAT_TYPE_PERCENT_CHAR:
			अगर (str < end)
				*str = '%';
			++str;
			अवरोध;

		हाल FORMAT_TYPE_INVALID:
			/*
			 * Presumably the arguments passed gcc's type
			 * checking, but there is no safe or sane way
			 * क्रम us to जारी parsing the क्रमmat and
			 * fetching from the बहु_सूची; the reमुख्यing
			 * specअगरiers and arguments would be out of
			 * sync.
			 */
			जाओ out;

		शेष:
			चयन (spec.type) अणु
			हाल FORMAT_TYPE_LONG_LONG:
				num = बहु_तर्क(args, दीर्घ दीर्घ);
				अवरोध;
			हाल FORMAT_TYPE_ULONG:
				num = बहु_तर्क(args, अचिन्हित दीर्घ);
				अवरोध;
			हाल FORMAT_TYPE_LONG:
				num = बहु_तर्क(args, दीर्घ);
				अवरोध;
			हाल FORMAT_TYPE_SIZE_T:
				अगर (spec.flags & SIGN)
					num = बहु_तर्क(args, sमाप_प्रकार);
				अन्यथा
					num = बहु_तर्क(args, माप_प्रकार);
				अवरोध;
			हाल FORMAT_TYPE_PTRDIFF:
				num = बहु_तर्क(args, सूचक_भेद_प्रकार);
				अवरोध;
			हाल FORMAT_TYPE_UBYTE:
				num = (अचिन्हित अक्षर) बहु_तर्क(args, पूर्णांक);
				अवरोध;
			हाल FORMAT_TYPE_BYTE:
				num = (चिन्हित अक्षर) बहु_तर्क(args, पूर्णांक);
				अवरोध;
			हाल FORMAT_TYPE_USHORT:
				num = (अचिन्हित लघु) बहु_तर्क(args, पूर्णांक);
				अवरोध;
			हाल FORMAT_TYPE_SHORT:
				num = (लघु) बहु_तर्क(args, पूर्णांक);
				अवरोध;
			हाल FORMAT_TYPE_INT:
				num = (पूर्णांक) बहु_तर्क(args, पूर्णांक);
				अवरोध;
			शेष:
				num = बहु_तर्क(args, अचिन्हित पूर्णांक);
			पूर्ण

			str = number(str, end, num, spec);
		पूर्ण
	पूर्ण

out:
	अगर (size > 0) अणु
		अगर (str < end)
			*str = '\0';
		अन्यथा
			end[-1] = '\0';
	पूर्ण

	/* the trailing null byte करोesn't count towards the total */
	वापस str-buf;

पूर्ण
EXPORT_SYMBOL(vsnम_लिखो);

/**
 * vscnम_लिखो - Format a string and place it in a buffer
 * @buf: The buffer to place the result पूर्णांकo
 * @size: The size of the buffer, including the trailing null space
 * @fmt: The क्रमmat string to use
 * @args: Arguments क्रम the क्रमmat string
 *
 * The वापस value is the number of अक्षरacters which have been written पूर्णांकo
 * the @buf not including the trailing '\0'. If @size is == 0 the function
 * वापसs 0.
 *
 * If you're not alपढ़ोy dealing with a बहु_सूची consider using scnम_लिखो().
 *
 * See the vsnम_लिखो() करोcumentation क्रम क्रमmat string extensions over C99.
 */
पूर्णांक vscnम_लिखो(अक्षर *buf, माप_प्रकार size, स्थिर अक्षर *fmt, बहु_सूची args)
अणु
	पूर्णांक i;

	i = vsnम_लिखो(buf, size, fmt, args);

	अगर (likely(i < size))
		वापस i;
	अगर (size != 0)
		वापस size - 1;
	वापस 0;
पूर्ण
EXPORT_SYMBOL(vscnम_लिखो);

/**
 * snम_लिखो - Format a string and place it in a buffer
 * @buf: The buffer to place the result पूर्णांकo
 * @size: The size of the buffer, including the trailing null space
 * @fmt: The क्रमmat string to use
 * @...: Arguments क्रम the क्रमmat string
 *
 * The वापस value is the number of अक्षरacters which would be
 * generated क्रम the given input, excluding the trailing null,
 * as per ISO C99.  If the वापस is greater than or equal to
 * @size, the resulting string is truncated.
 *
 * See the vsnम_लिखो() करोcumentation क्रम क्रमmat string extensions over C99.
 */
पूर्णांक snम_लिखो(अक्षर *buf, माप_प्रकार size, स्थिर अक्षर *fmt, ...)
अणु
	बहु_सूची args;
	पूर्णांक i;

	बहु_शुरू(args, fmt);
	i = vsnम_लिखो(buf, size, fmt, args);
	बहु_पूर्ण(args);

	वापस i;
पूर्ण
EXPORT_SYMBOL(snम_लिखो);

/**
 * scnम_लिखो - Format a string and place it in a buffer
 * @buf: The buffer to place the result पूर्णांकo
 * @size: The size of the buffer, including the trailing null space
 * @fmt: The क्रमmat string to use
 * @...: Arguments क्रम the क्रमmat string
 *
 * The वापस value is the number of अक्षरacters written पूर्णांकo @buf not including
 * the trailing '\0'. If @size is == 0 the function वापसs 0.
 */

पूर्णांक scnम_लिखो(अक्षर *buf, माप_प्रकार size, स्थिर अक्षर *fmt, ...)
अणु
	बहु_सूची args;
	पूर्णांक i;

	बहु_शुरू(args, fmt);
	i = vscnम_लिखो(buf, size, fmt, args);
	बहु_पूर्ण(args);

	वापस i;
पूर्ण
EXPORT_SYMBOL(scnम_लिखो);

/**
 * भम_लिखो - Format a string and place it in a buffer
 * @buf: The buffer to place the result पूर्णांकo
 * @fmt: The क्रमmat string to use
 * @args: Arguments क्रम the क्रमmat string
 *
 * The function वापसs the number of अक्षरacters written
 * पूर्णांकo @buf. Use vsnम_लिखो() or vscnम_लिखो() in order to aव्योम
 * buffer overflows.
 *
 * If you're not alपढ़ोy dealing with a बहु_सूची consider using प्र_लिखो().
 *
 * See the vsnम_लिखो() करोcumentation क्रम क्रमmat string extensions over C99.
 */
पूर्णांक भम_लिखो(अक्षर *buf, स्थिर अक्षर *fmt, बहु_सूची args)
अणु
	वापस vsnम_लिखो(buf, पूर्णांक_उच्च, fmt, args);
पूर्ण
EXPORT_SYMBOL(भम_लिखो);

/**
 * प्र_लिखो - Format a string and place it in a buffer
 * @buf: The buffer to place the result पूर्णांकo
 * @fmt: The क्रमmat string to use
 * @...: Arguments क्रम the क्रमmat string
 *
 * The function वापसs the number of अक्षरacters written
 * पूर्णांकo @buf. Use snम_लिखो() or scnम_लिखो() in order to aव्योम
 * buffer overflows.
 *
 * See the vsnम_लिखो() करोcumentation क्रम क्रमmat string extensions over C99.
 */
पूर्णांक प्र_लिखो(अक्षर *buf, स्थिर अक्षर *fmt, ...)
अणु
	बहु_सूची args;
	पूर्णांक i;

	बहु_शुरू(args, fmt);
	i = vsnम_लिखो(buf, पूर्णांक_उच्च, fmt, args);
	बहु_पूर्ण(args);

	वापस i;
पूर्ण
EXPORT_SYMBOL(प्र_लिखो);

#अगर_घोषित CONFIG_BINARY_PRINTF
/*
 * bम_लिखो service:
 * vbin_म_लिखो() - VA arguments to binary data
 * bstr_म_लिखो() - Binary data to text string
 */

/**
 * vbin_म_लिखो - Parse a क्रमmat string and place args' binary value in a buffer
 * @bin_buf: The buffer to place args' binary value
 * @size: The size of the buffer(by words(32bits), not अक्षरacters)
 * @fmt: The क्रमmat string to use
 * @args: Arguments क्रम the क्रमmat string
 *
 * The क्रमmat follows C99 vsnम_लिखो, except %n is ignored, and its argument
 * is skipped.
 *
 * The वापस value is the number of words(32bits) which would be generated क्रम
 * the given input.
 *
 * NOTE:
 * If the वापस value is greater than @size, the resulting bin_buf is NOT
 * valid क्रम bstr_म_लिखो().
 */
पूर्णांक vbin_म_लिखो(u32 *bin_buf, माप_प्रकार size, स्थिर अक्षर *fmt, बहु_सूची args)
अणु
	काष्ठा म_लिखो_spec spec = अणु0पूर्ण;
	अक्षर *str, *end;
	पूर्णांक width;

	str = (अक्षर *)bin_buf;
	end = (अक्षर *)(bin_buf + size);

#घोषणा save_arg(type)							\
(अणु									\
	अचिन्हित दीर्घ दीर्घ value;					\
	अगर (माप(type) == 8) अणु					\
		अचिन्हित दीर्घ दीर्घ val8;				\
		str = PTR_ALIGN(str, माप(u32));			\
		val8 = बहु_तर्क(args, अचिन्हित दीर्घ दीर्घ);		\
		अगर (str + माप(type) <= end) अणु			\
			*(u32 *)str = *(u32 *)&val8;			\
			*(u32 *)(str + 4) = *((u32 *)&val8 + 1);	\
		पूर्ण							\
		value = val8;						\
	पूर्ण अन्यथा अणु							\
		अचिन्हित पूर्णांक val4;					\
		str = PTR_ALIGN(str, माप(type));			\
		val4 = बहु_तर्क(args, पूर्णांक);				\
		अगर (str + माप(type) <= end)				\
			*(typeof(type) *)str = (type)(दीर्घ)val4;	\
		value = (अचिन्हित दीर्घ दीर्घ)val4;			\
	पूर्ण								\
	str += माप(type);						\
	value;								\
पूर्ण)

	जबतक (*fmt) अणु
		पूर्णांक पढ़ो = क्रमmat_decode(fmt, &spec);

		fmt += पढ़ो;

		चयन (spec.type) अणु
		हाल FORMAT_TYPE_NONE:
		हाल FORMAT_TYPE_PERCENT_CHAR:
			अवरोध;
		हाल FORMAT_TYPE_INVALID:
			जाओ out;

		हाल FORMAT_TYPE_WIDTH:
		हाल FORMAT_TYPE_PRECISION:
			width = (पूर्णांक)save_arg(पूर्णांक);
			/* Poपूर्णांकers may require the width */
			अगर (*fmt == 'p')
				set_field_width(&spec, width);
			अवरोध;

		हाल FORMAT_TYPE_CHAR:
			save_arg(अक्षर);
			अवरोध;

		हाल FORMAT_TYPE_STR: अणु
			स्थिर अक्षर *save_str = बहु_तर्क(args, अक्षर *);
			स्थिर अक्षर *err_msg;
			माप_प्रकार len;

			err_msg = check_poपूर्णांकer_msg(save_str);
			अगर (err_msg)
				save_str = err_msg;

			len = म_माप(save_str) + 1;
			अगर (str + len < end)
				स_नकल(str, save_str, len);
			str += len;
			अवरोध;
		पूर्ण

		हाल FORMAT_TYPE_PTR:
			/* Dereferenced poपूर्णांकers must be करोne now */
			चयन (*fmt) अणु
			/* Dereference of functions is still OK */
			हाल 'S':
			हाल 's':
			हाल 'x':
			हाल 'K':
			हाल 'e':
				save_arg(व्योम *);
				अवरोध;
			शेष:
				अगर (!है_अक्षर_अंक(*fmt)) अणु
					save_arg(व्योम *);
					अवरोध;
				पूर्ण
				str = poपूर्णांकer(fmt, str, end, बहु_तर्क(args, व्योम *),
					      spec);
				अगर (str + 1 < end)
					*str++ = '\0';
				अन्यथा
					end[-1] = '\0'; /* Must be nul terminated */
			पूर्ण
			/* skip all alphanumeric poपूर्णांकer suffixes */
			जबतक (है_अक्षर_अंक(*fmt))
				fmt++;
			अवरोध;

		शेष:
			चयन (spec.type) अणु

			हाल FORMAT_TYPE_LONG_LONG:
				save_arg(दीर्घ दीर्घ);
				अवरोध;
			हाल FORMAT_TYPE_ULONG:
			हाल FORMAT_TYPE_LONG:
				save_arg(अचिन्हित दीर्घ);
				अवरोध;
			हाल FORMAT_TYPE_SIZE_T:
				save_arg(माप_प्रकार);
				अवरोध;
			हाल FORMAT_TYPE_PTRDIFF:
				save_arg(सूचक_भेद_प्रकार);
				अवरोध;
			हाल FORMAT_TYPE_UBYTE:
			हाल FORMAT_TYPE_BYTE:
				save_arg(अक्षर);
				अवरोध;
			हाल FORMAT_TYPE_USHORT:
			हाल FORMAT_TYPE_SHORT:
				save_arg(लघु);
				अवरोध;
			शेष:
				save_arg(पूर्णांक);
			पूर्ण
		पूर्ण
	पूर्ण

out:
	वापस (u32 *)(PTR_ALIGN(str, माप(u32))) - bin_buf;
#अघोषित save_arg
पूर्ण
EXPORT_SYMBOL_GPL(vbin_म_लिखो);

/**
 * bstr_म_लिखो - Format a string from binary arguments and place it in a buffer
 * @buf: The buffer to place the result पूर्णांकo
 * @size: The size of the buffer, including the trailing null space
 * @fmt: The क्रमmat string to use
 * @bin_buf: Binary arguments क्रम the क्रमmat string
 *
 * This function like C99 vsnम_लिखो, but the dअगरference is that vsnम_लिखो माला_लो
 * arguments from stack, and bstr_म_लिखो माला_लो arguments from @bin_buf which is
 * a binary buffer that generated by vbin_म_लिखो.
 *
 * The क्रमmat follows C99 vsnम_लिखो, but has some extensions:
 *  see vsnम_लिखो comment क्रम details.
 *
 * The वापस value is the number of अक्षरacters which would
 * be generated क्रम the given input, excluding the trailing
 * '\0', as per ISO C99. If you want to have the exact
 * number of अक्षरacters written पूर्णांकo @buf as वापस value
 * (not including the trailing '\0'), use vscnम_लिखो(). If the
 * वापस is greater than or equal to @size, the resulting
 * string is truncated.
 */
पूर्णांक bstr_म_लिखो(अक्षर *buf, माप_प्रकार size, स्थिर अक्षर *fmt, स्थिर u32 *bin_buf)
अणु
	काष्ठा म_लिखो_spec spec = अणु0पूर्ण;
	अक्षर *str, *end;
	स्थिर अक्षर *args = (स्थिर अक्षर *)bin_buf;

	अगर (WARN_ON_ONCE(size > पूर्णांक_उच्च))
		वापस 0;

	str = buf;
	end = buf + size;

#घोषणा get_arg(type)							\
(अणु									\
	typeof(type) value;						\
	अगर (माप(type) == 8) अणु					\
		args = PTR_ALIGN(args, माप(u32));			\
		*(u32 *)&value = *(u32 *)args;				\
		*((u32 *)&value + 1) = *(u32 *)(args + 4);		\
	पूर्ण अन्यथा अणु							\
		args = PTR_ALIGN(args, माप(type));			\
		value = *(typeof(type) *)args;				\
	पूर्ण								\
	args += माप(type);						\
	value;								\
पूर्ण)

	/* Make sure end is always >= buf */
	अगर (end < buf) अणु
		end = ((व्योम *)-1);
		size = end - buf;
	पूर्ण

	जबतक (*fmt) अणु
		स्थिर अक्षर *old_fmt = fmt;
		पूर्णांक पढ़ो = क्रमmat_decode(fmt, &spec);

		fmt += पढ़ो;

		चयन (spec.type) अणु
		हाल FORMAT_TYPE_NONE: अणु
			पूर्णांक copy = पढ़ो;
			अगर (str < end) अणु
				अगर (copy > end - str)
					copy = end - str;
				स_नकल(str, old_fmt, copy);
			पूर्ण
			str += पढ़ो;
			अवरोध;
		पूर्ण

		हाल FORMAT_TYPE_WIDTH:
			set_field_width(&spec, get_arg(पूर्णांक));
			अवरोध;

		हाल FORMAT_TYPE_PRECISION:
			set_precision(&spec, get_arg(पूर्णांक));
			अवरोध;

		हाल FORMAT_TYPE_CHAR: अणु
			अक्षर c;

			अगर (!(spec.flags & LEFT)) अणु
				जबतक (--spec.field_width > 0) अणु
					अगर (str < end)
						*str = ' ';
					++str;
				पूर्ण
			पूर्ण
			c = (अचिन्हित अक्षर) get_arg(अक्षर);
			अगर (str < end)
				*str = c;
			++str;
			जबतक (--spec.field_width > 0) अणु
				अगर (str < end)
					*str = ' ';
				++str;
			पूर्ण
			अवरोध;
		पूर्ण

		हाल FORMAT_TYPE_STR: अणु
			स्थिर अक्षर *str_arg = args;
			args += म_माप(str_arg) + 1;
			str = string(str, end, (अक्षर *)str_arg, spec);
			अवरोध;
		पूर्ण

		हाल FORMAT_TYPE_PTR: अणु
			bool process = false;
			पूर्णांक copy, len;
			/* Non function dereferences were alपढ़ोy करोne */
			चयन (*fmt) अणु
			हाल 'S':
			हाल 's':
			हाल 'x':
			हाल 'K':
			हाल 'e':
				process = true;
				अवरोध;
			शेष:
				अगर (!है_अक्षर_अंक(*fmt)) अणु
					process = true;
					अवरोध;
				पूर्ण
				/* Poपूर्णांकer dereference was alपढ़ोy processed */
				अगर (str < end) अणु
					len = copy = म_माप(args);
					अगर (copy > end - str)
						copy = end - str;
					स_नकल(str, args, copy);
					str += len;
					args += len + 1;
				पूर्ण
			पूर्ण
			अगर (process)
				str = poपूर्णांकer(fmt, str, end, get_arg(व्योम *), spec);

			जबतक (है_अक्षर_अंक(*fmt))
				fmt++;
			अवरोध;
		पूर्ण

		हाल FORMAT_TYPE_PERCENT_CHAR:
			अगर (str < end)
				*str = '%';
			++str;
			अवरोध;

		हाल FORMAT_TYPE_INVALID:
			जाओ out;

		शेष: अणु
			अचिन्हित दीर्घ दीर्घ num;

			चयन (spec.type) अणु

			हाल FORMAT_TYPE_LONG_LONG:
				num = get_arg(दीर्घ दीर्घ);
				अवरोध;
			हाल FORMAT_TYPE_ULONG:
			हाल FORMAT_TYPE_LONG:
				num = get_arg(अचिन्हित दीर्घ);
				अवरोध;
			हाल FORMAT_TYPE_SIZE_T:
				num = get_arg(माप_प्रकार);
				अवरोध;
			हाल FORMAT_TYPE_PTRDIFF:
				num = get_arg(सूचक_भेद_प्रकार);
				अवरोध;
			हाल FORMAT_TYPE_UBYTE:
				num = get_arg(अचिन्हित अक्षर);
				अवरोध;
			हाल FORMAT_TYPE_BYTE:
				num = get_arg(चिन्हित अक्षर);
				अवरोध;
			हाल FORMAT_TYPE_USHORT:
				num = get_arg(अचिन्हित लघु);
				अवरोध;
			हाल FORMAT_TYPE_SHORT:
				num = get_arg(लघु);
				अवरोध;
			हाल FORMAT_TYPE_UINT:
				num = get_arg(अचिन्हित पूर्णांक);
				अवरोध;
			शेष:
				num = get_arg(पूर्णांक);
			पूर्ण

			str = number(str, end, num, spec);
		पूर्ण /* शेष: */
		पूर्ण /* चयन(spec.type) */
	पूर्ण /* जबतक(*fmt) */

out:
	अगर (size > 0) अणु
		अगर (str < end)
			*str = '\0';
		अन्यथा
			end[-1] = '\0';
	पूर्ण

#अघोषित get_arg

	/* the trailing null byte करोesn't count towards the total */
	वापस str - buf;
पूर्ण
EXPORT_SYMBOL_GPL(bstr_म_लिखो);

/**
 * bम_लिखो - Parse a क्रमmat string and place args' binary value in a buffer
 * @bin_buf: The buffer to place args' binary value
 * @size: The size of the buffer(by words(32bits), not अक्षरacters)
 * @fmt: The क्रमmat string to use
 * @...: Arguments क्रम the क्रमmat string
 *
 * The function वापसs the number of words(u32) written
 * पूर्णांकo @bin_buf.
 */
पूर्णांक bम_लिखो(u32 *bin_buf, माप_प्रकार size, स्थिर अक्षर *fmt, ...)
अणु
	बहु_सूची args;
	पूर्णांक ret;

	बहु_शुरू(args, fmt);
	ret = vbin_म_लिखो(bin_buf, size, fmt, args);
	बहु_पूर्ण(args);

	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(bम_लिखो);

#पूर्ण_अगर /* CONFIG_BINARY_PRINTF */

/**
 * vमाला_पूछो - Unक्रमmat a buffer पूर्णांकo a list of arguments
 * @buf:	input buffer
 * @fmt:	क्रमmat of buffer
 * @args:	arguments
 */
पूर्णांक vमाला_पूछो(स्थिर अक्षर *buf, स्थिर अक्षर *fmt, बहु_सूची args)
अणु
	स्थिर अक्षर *str = buf;
	अक्षर *next;
	अक्षर digit;
	पूर्णांक num = 0;
	u8 qualअगरier;
	अचिन्हित पूर्णांक base;
	जोड़ अणु
		दीर्घ दीर्घ s;
		अचिन्हित दीर्घ दीर्घ u;
	पूर्ण val;
	s16 field_width;
	bool is_sign;

	जबतक (*fmt) अणु
		/* skip any white space in क्रमmat */
		/* white space in क्रमmat matchs any amount of
		 * white space, including none, in the input.
		 */
		अगर (है_खाली(*fmt)) अणु
			fmt = skip_spaces(++fmt);
			str = skip_spaces(str);
		पूर्ण

		/* anything that is not a conversion must match exactly */
		अगर (*fmt != '%' && *fmt) अणु
			अगर (*fmt++ != *str++)
				अवरोध;
			जारी;
		पूर्ण

		अगर (!*fmt)
			अवरोध;
		++fmt;

		/* skip this conversion.
		 * advance both strings to next white space
		 */
		अगर (*fmt == '*') अणु
			अगर (!*str)
				अवरोध;
			जबतक (!है_खाली(*fmt) && *fmt != '%' && *fmt) अणु
				/* '%*[' not yet supported, invalid क्रमmat */
				अगर (*fmt == '[')
					वापस num;
				fmt++;
			पूर्ण
			जबतक (!है_खाली(*str) && *str)
				str++;
			जारी;
		पूर्ण

		/* get field width */
		field_width = -1;
		अगर (है_अंक(*fmt)) अणु
			field_width = skip_म_से_प(&fmt);
			अगर (field_width <= 0)
				अवरोध;
		पूर्ण

		/* get conversion qualअगरier */
		qualअगरier = -1;
		अगर (*fmt == 'h' || _tolower(*fmt) == 'l' ||
		    *fmt == 'z') अणु
			qualअगरier = *fmt++;
			अगर (unlikely(qualअगरier == *fmt)) अणु
				अगर (qualअगरier == 'h') अणु
					qualअगरier = 'H';
					fmt++;
				पूर्ण अन्यथा अगर (qualअगरier == 'l') अणु
					qualअगरier = 'L';
					fmt++;
				पूर्ण
			पूर्ण
		पूर्ण

		अगर (!*fmt)
			अवरोध;

		अगर (*fmt == 'n') अणु
			/* वापस number of अक्षरacters पढ़ो so far */
			*बहु_तर्क(args, पूर्णांक *) = str - buf;
			++fmt;
			जारी;
		पूर्ण

		अगर (!*str)
			अवरोध;

		base = 10;
		is_sign = false;

		चयन (*fmt++) अणु
		हाल 'c':
		अणु
			अक्षर *s = (अक्षर *)बहु_तर्क(args, अक्षर*);
			अगर (field_width == -1)
				field_width = 1;
			करो अणु
				*s++ = *str++;
			पूर्ण जबतक (--field_width > 0 && *str);
			num++;
		पूर्ण
		जारी;
		हाल 's':
		अणु
			अक्षर *s = (अक्षर *)बहु_तर्क(args, अक्षर *);
			अगर (field_width == -1)
				field_width = लघु_उच्च;
			/* first, skip leading white space in buffer */
			str = skip_spaces(str);

			/* now copy until next white space */
			जबतक (*str && !है_खाली(*str) && field_width--)
				*s++ = *str++;
			*s = '\0';
			num++;
		पूर्ण
		जारी;
		/*
		 * Warning: This implementation of the '[' conversion specअगरier
		 * deviates from its glibc counterpart in the following ways:
		 * (1) It करोes NOT support ranges i.e. '-' is NOT a special
		 *     अक्षरacter
		 * (2) It cannot match the closing bracket ']' itself
		 * (3) A field width is required
		 * (4) '%*[' (discard matching input) is currently not supported
		 *
		 * Example usage:
		 * ret = माला_पूछो("00:0a:95","%2[^:]:%2[^:]:%2[^:]",
		 *		buf1, buf2, buf3);
		 * अगर (ret < 3)
		 *    // etc..
		 */
		हाल '[':
		अणु
			अक्षर *s = (अक्षर *)बहु_तर्क(args, अक्षर *);
			DECLARE_BITMAP(set, 256) = अणु0पूर्ण;
			अचिन्हित पूर्णांक len = 0;
			bool negate = (*fmt == '^');

			/* field width is required */
			अगर (field_width == -1)
				वापस num;

			अगर (negate)
				++fmt;

			क्रम ( ; *fmt && *fmt != ']'; ++fmt, ++len)
				set_bit((u8)*fmt, set);

			/* no ']' or no अक्षरacter set found */
			अगर (!*fmt || !len)
				वापस num;
			++fmt;

			अगर (negate) अणु
				biपंचांगap_complement(set, set, 256);
				/* exclude null '\0' byte */
				clear_bit(0, set);
			पूर्ण

			/* match must be non-empty */
			अगर (!test_bit((u8)*str, set))
				वापस num;

			जबतक (test_bit((u8)*str, set) && field_width--)
				*s++ = *str++;
			*s = '\0';
			++num;
		पूर्ण
		जारी;
		हाल 'o':
			base = 8;
			अवरोध;
		हाल 'x':
		हाल 'X':
			base = 16;
			अवरोध;
		हाल 'i':
			base = 0;
			fallthrough;
		हाल 'd':
			is_sign = true;
			fallthrough;
		हाल 'u':
			अवरोध;
		हाल '%':
			/* looking क्रम '%' in str */
			अगर (*str++ != '%')
				वापस num;
			जारी;
		शेष:
			/* invalid क्रमmat; stop here */
			वापस num;
		पूर्ण

		/* have some sort of पूर्णांकeger conversion.
		 * first, skip white space in buffer.
		 */
		str = skip_spaces(str);

		digit = *str;
		अगर (is_sign && digit == '-')
			digit = *(str + 1);

		अगर (!digit
		    || (base == 16 && !है_षष्ठादशक(digit))
		    || (base == 10 && !है_अंक(digit))
		    || (base == 8 && (!है_अंक(digit) || digit > '7'))
		    || (base == 0 && !है_अंक(digit)))
			अवरोध;

		अगर (is_sign)
			val.s = qualअगरier != 'L' ?
				simple_म_से_दीर्घ(str, &next, base) :
				simple_म_से_दीर्घl(str, &next, base);
		अन्यथा
			val.u = qualअगरier != 'L' ?
				simple_म_से_अदीर्घ(str, &next, base) :
				simple_म_से_अदीर्घl(str, &next, base);

		अगर (field_width > 0 && next - str > field_width) अणु
			अगर (base == 0)
				_parse_पूर्णांकeger_fixup_radix(str, &base);
			जबतक (next - str > field_width) अणु
				अगर (is_sign)
					val.s = भाग_s64(val.s, base);
				अन्यथा
					val.u = भाग_u64(val.u, base);
				--next;
			पूर्ण
		पूर्ण

		चयन (qualअगरier) अणु
		हाल 'H':	/* that's 'hh' in क्रमmat */
			अगर (is_sign)
				*बहु_तर्क(args, चिन्हित अक्षर *) = val.s;
			अन्यथा
				*बहु_तर्क(args, अचिन्हित अक्षर *) = val.u;
			अवरोध;
		हाल 'h':
			अगर (is_sign)
				*बहु_तर्क(args, लघु *) = val.s;
			अन्यथा
				*बहु_तर्क(args, अचिन्हित लघु *) = val.u;
			अवरोध;
		हाल 'l':
			अगर (is_sign)
				*बहु_तर्क(args, दीर्घ *) = val.s;
			अन्यथा
				*बहु_तर्क(args, अचिन्हित दीर्घ *) = val.u;
			अवरोध;
		हाल 'L':
			अगर (is_sign)
				*बहु_तर्क(args, दीर्घ दीर्घ *) = val.s;
			अन्यथा
				*बहु_तर्क(args, अचिन्हित दीर्घ दीर्घ *) = val.u;
			अवरोध;
		हाल 'z':
			*बहु_तर्क(args, माप_प्रकार *) = val.u;
			अवरोध;
		शेष:
			अगर (is_sign)
				*बहु_तर्क(args, पूर्णांक *) = val.s;
			अन्यथा
				*बहु_तर्क(args, अचिन्हित पूर्णांक *) = val.u;
			अवरोध;
		पूर्ण
		num++;

		अगर (!next)
			अवरोध;
		str = next;
	पूर्ण

	वापस num;
पूर्ण
EXPORT_SYMBOL(vमाला_पूछो);

/**
 * माला_पूछो - Unक्रमmat a buffer पूर्णांकo a list of arguments
 * @buf:	input buffer
 * @fmt:	क्रमmatting of buffer
 * @...:	resulting arguments
 */
पूर्णांक माला_पूछो(स्थिर अक्षर *buf, स्थिर अक्षर *fmt, ...)
अणु
	बहु_सूची args;
	पूर्णांक i;

	बहु_शुरू(args, fmt);
	i = vमाला_पूछो(buf, fmt, args);
	बहु_पूर्ण(args);

	वापस i;
पूर्ण
EXPORT_SYMBOL(माला_पूछो);
