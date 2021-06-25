<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _VIDEO_ATAFB_UTILS_H
#घोषणा _VIDEO_ATAFB_UTILS_H

/* ================================================================= */
/*                      Utility Assembler Functions                  */
/* ================================================================= */

/* ====================================================================== */

/* Those of a delicate disposition might like to skip the next couple of
 * pages.
 *
 * These functions are drop in replacements क्रम स_हटाओ and
 * स_रखो(_, 0, _). However their five instances add at least a kilobyte
 * to the object file. You have been warned.
 *
 * Not a great fan of assembler क्रम the sake of it, but I think
 * that these routines are at least 10 बार faster than their C
 * equivalents क्रम large blits, and that's important to the lowest level of
 * a graphics driver. Question is whether some scheme with the blitter
 * would be faster. I suspect not क्रम simple text प्रणाली - not much
 * asynchrony.
 *
 * Code is very simple, just gruesome expansion. Basic strategy is to
 * increase data moved/cleared at each step to 16 bytes to reduce
 * inकाष्ठाion per data move overhead. movem might be faster still
 * For more than 15 bytes, we try to align the ग_लिखो direction on a
 * दीर्घword boundary to get maximum speed. This is even more gruesome.
 * Unaligned पढ़ो/ग_लिखो used requires 68020+ - think this is a problem?
 *
 * Sorry!
 */


/* ++roman: I've optimized Robert's original versions in some minor
 * aspects, e.g. moveq instead of movel, let gcc choose the रेजिस्टरs,
 * use movem in some places...
 * For other modes than 1 plane, lots of more such assembler functions
 * were needed (e.g. the ones using movep or expanding color values).
 */

/* ++andreas: more optimizations:
   subl #65536,d0 replaced by clrw d0; subql #1,d0 क्रम dbcc
   addal is faster than addaw
   movep is rather expensive compared to ordinary move's
   some functions rewritten in C क्रम clarity, no speed loss */

अटल अंतरभूत व्योम *fb_memclear_small(व्योम *s, माप_प्रकार count)
अणु
	अगर (!count)
		वापस 0;

	यंत्र अस्थिर ("\n"
		"	lsr.l	#1,%1 ; jcc 1f ; move.b %2,-(%0)\n"
		"1:	lsr.l	#1,%1 ; jcc 1f ; move.w %2,-(%0)\n"
		"1:	lsr.l	#1,%1 ; jcc 1f ; move.l %2,-(%0)\n"
		"1:	lsr.l	#1,%1 ; jcc 1f ; move.l %2,-(%0) ; move.l %2,-(%0)\n"
		"1:"
		: "=a" (s), "=d" (count)
		: "d" (0), "0" ((अक्षर *)s + count), "1" (count));
	यंत्र अस्थिर ("\n"
		"	subq.l  #1,%1\n"
		"	jcs	3f\n"
		"	move.l	%2,%%d4; move.l %2,%%d5; move.l %2,%%d6\n"
		"2:	movem.l	%2/%%d4/%%d5/%%d6,-(%0)\n"
		"	dbra	%1,2b\n"
		"3:"
		: "=a" (s), "=d" (count)
		: "d" (0), "0" (s), "1" (count)
		: "d4", "d5", "d6"
		);

	वापस 0;
पूर्ण


अटल अंतरभूत व्योम *fb_memclear(व्योम *s, माप_प्रकार count)
अणु
	अगर (!count)
		वापस 0;

	अगर (count < 16) अणु
		यंत्र अस्थिर ("\n"
			"	lsr.l	#1,%1 ; jcc 1f ; clr.b (%0)+\n"
			"1:	lsr.l	#1,%1 ; jcc 1f ; clr.w (%0)+\n"
			"1:	lsr.l	#1,%1 ; jcc 1f ; clr.l (%0)+\n"
			"1:	lsr.l	#1,%1 ; jcc 1f ; clr.l (%0)+ ; clr.l (%0)+\n"
			"1:"
			: "=a" (s), "=d" (count)
			: "0" (s), "1" (count));
	पूर्ण अन्यथा अणु
		दीर्घ पंचांगp;
		यंत्र अस्थिर ("\n"
			"	move.l	%1,%2\n"
			"	lsr.l	#1,%2 ; jcc 1f ; clr.b (%0)+ ; subq.w #1,%1\n"
			"	lsr.l	#1,%2 ; jcs 2f\n"  /* %0 increased=>bit 2 चयनed*/
			"	clr.w	(%0)+  ; subq.w  #2,%1 ; jra 2f\n"
			"1:	lsr.l	#1,%2 ; jcc 2f\n"
			"	clr.w	(%0)+  ; subq.w  #2,%1\n"
			"2:	move.w	%1,%2; lsr.l #2,%1 ; jeq 6f\n"
			"	lsr.l	#1,%1 ; jcc 3f ; clr.l (%0)+\n"
			"3:	lsr.l	#1,%1 ; jcc 4f ; clr.l (%0)+ ; clr.l (%0)+\n"
			"4:	subq.l	#1,%1 ; jcs 6f\n"
			"5:	clr.l	(%0)+; clr.l (%0)+ ; clr.l (%0)+ ; clr.l (%0)+\n"
			"	dbra	%1,5b ; clr.w %1; subq.l #1,%1; jcc 5b\n"
			"6:	move.w	%2,%1; btst #1,%1 ; jeq 7f ; clr.w (%0)+\n"
			"7:	btst	#0,%1 ; jeq 8f ; clr.b (%0)+\n"
			"8:"
			: "=a" (s), "=d" (count), "=d" (पंचांगp)
			: "0" (s), "1" (count));
	पूर्ण

	वापस 0;
पूर्ण


अटल अंतरभूत व्योम *fb_स_रखो255(व्योम *s, माप_प्रकार count)
अणु
	अगर (!count)
		वापस 0;

	यंत्र अस्थिर ("\n"
		"	lsr.l	#1,%1 ; jcc 1f ; move.b %2,-(%0)\n"
		"1:	lsr.l	#1,%1 ; jcc 1f ; move.w %2,-(%0)\n"
		"1:	lsr.l	#1,%1 ; jcc 1f ; move.l %2,-(%0)\n"
		"1:	lsr.l	#1,%1 ; jcc 1f ; move.l %2,-(%0) ; move.l %2,-(%0)\n"
		"1:"
		: "=a" (s), "=d" (count)
		: "d" (-1), "0" ((अक्षर *)s+count), "1" (count));
	यंत्र अस्थिर ("\n"
		"	subq.l	#1,%1 ; jcs 3f\n"
		"	move.l	%2,%%d4; move.l %2,%%d5; move.l %2,%%d6\n"
		"2:	movem.l	%2/%%d4/%%d5/%%d6,-(%0)\n"
		"	dbra	%1,2b\n"
		"3:"
		: "=a" (s), "=d" (count)
		: "d" (-1), "0" (s), "1" (count)
		: "d4", "d5", "d6");

	वापस 0;
पूर्ण


अटल अंतरभूत व्योम *fb_स_हटाओ(व्योम *d, स्थिर व्योम *s, माप_प्रकार count)
अणु
	अगर (d < s) अणु
		अगर (count < 16) अणु
			यंत्र अस्थिर ("\n"
				"	lsr.l	#1,%2 ; jcc 1f ; move.b (%1)+,(%0)+\n"
				"1:	lsr.l	#1,%2 ; jcc 1f ; move.w (%1)+,(%0)+\n"
				"1:	lsr.l	#1,%2 ; jcc 1f ; move.l (%1)+,(%0)+\n"
				"1:	lsr.l	#1,%2 ; jcc 1f ; move.l (%1)+,(%0)+ ; move.l (%1)+,(%0)+\n"
				"1:"
				: "=a" (d), "=a" (s), "=d" (count)
				: "0" (d), "1" (s), "2" (count));
		पूर्ण अन्यथा अणु
			दीर्घ पंचांगp;
			यंत्र अस्थिर ("\n"
				"	move.l	%0,%3\n"
				"	lsr.l	#1,%3 ; jcc 1f ; move.b (%1)+,(%0)+ ; subqw #1,%2\n"
				"	lsr.l	#1,%3 ; jcs 2f\n"  /* %0 increased=>bit 2 चयनed*/
				"	move.w	(%1)+,(%0)+  ; subqw  #2,%2 ; jra 2f\n"
				"1:	lsr.l   #1,%3 ; jcc 2f\n"
				"	move.w	(%1)+,(%0)+  ; subqw  #2,%2\n"
				"2:	move.w	%2,%-; lsr.l #2,%2 ; jeq 6f\n"
				"	lsr.l	#1,%2 ; jcc 3f ; move.l (%1)+,(%0)+\n"
				"3:	lsr.l	#1,%2 ; jcc 4f ; move.l (%1)+,(%0)+ ; move.l (%1)+,(%0)+\n"
				"4:	subq.l	#1,%2 ; jcs 6f\n"
				"5:	move.l	(%1)+,(%0)+; move.l (%1)+,(%0)+\n"
				"	move.l	(%1)+,(%0)+; move.l (%1)+,(%0)+\n"
				"	dbra	%2,5b ; clr.w %2; subq.l #1,%2; jcc 5b\n"
				"6:	move.w	%+,%2; btst #1,%2 ; jeq 7f ; move.w (%1)+,(%0)+\n"
				"7:	btst	#0,%2 ; jeq 8f ; move.b (%1)+,(%0)+\n"
				"8:"
				: "=a" (d), "=a" (s), "=d" (count), "=d" (पंचांगp)
				: "0" (d), "1" (s), "2" (count));
		पूर्ण
	पूर्ण अन्यथा अणु
		अगर (count < 16) अणु
			यंत्र अस्थिर ("\n"
				"	lsr.l	#1,%2 ; jcc 1f ; move.b -(%1),-(%0)\n"
				"1:	lsr.l	#1,%2 ; jcc 1f ; move.w -(%1),-(%0)\n"
				"1:	lsr.l	#1,%2 ; jcc 1f ; move.l -(%1),-(%0)\n"
				"1:	lsr.l	#1,%2 ; jcc 1f ; move.l -(%1),-(%0) ; move.l -(%1),-(%0)\n"
				"1:"
				: "=a" (d), "=a" (s), "=d" (count)
				: "0" ((अक्षर *) d + count), "1" ((अक्षर *) s + count), "2" (count));
		पूर्ण अन्यथा अणु
			दीर्घ पंचांगp;

			यंत्र अस्थिर ("\n"
				"	move.l	%0,%3\n"
				"	lsr.l	#1,%3 ; jcc 1f ; move.b -(%1),-(%0) ; subqw #1,%2\n"
				"	lsr.l	#1,%3 ; jcs 2f\n"  /* %0 increased=>bit 2 चयनed*/
				"	move.w	-(%1),-(%0) ; subqw  #2,%2 ; jra 2f\n"
				"1:	lsr.l	#1,%3 ; jcc 2f\n"
				"	move.w	-(%1),-(%0) ; subqw  #2,%2\n"
				"2:	move.w	%2,%-; lsr.l #2,%2 ; jeq 6f\n"
				"	lsr.l	#1,%2 ; jcc 3f ; move.l -(%1),-(%0)\n"
				"3:	lsr.l	#1,%2 ; jcc 4f ; move.l -(%1),-(%0) ; move.l -(%1),-(%0)\n"
				"4:	subq.l	#1,%2 ; jcs 6f\n"
				"5:	move.l	-(%1),-(%0); move.l -(%1),-(%0)\n"
				"	move.l	-(%1),-(%0); move.l -(%1),-(%0)\n"
				"	dbra	%2,5b ; clr.w %2; subq.l #1,%2; jcc 5b\n"
				"6:	move.w	%+,%2; btst #1,%2 ; jeq 7f ; move.w -(%1),-(%0)\n"
				"7:	btst	#0,%2 ; jeq 8f ; move.b -(%1),-(%0)\n"
				"8:"
				: "=a" (d), "=a" (s), "=d" (count), "=d" (पंचांगp)
				: "0" ((अक्षर *) d + count), "1" ((अक्षर *) s + count), "2" (count));
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण


/* ++andreas: Simple and fast version of स_हटाओ, assumes size is
   भागisible by 16, suitable क्रम moving the whole screen bitplane */
अटल अंतरभूत व्योम fast_स_हटाओ(अक्षर *dst, स्थिर अक्षर *src, माप_प्रकार size)
अणु
	अगर (!size)
		वापस;
	अगर (dst < src)
		यंत्र अस्थिर ("\n"
			"1:	movem.l	(%0)+,%%d0/%%d1/%%a0/%%a1\n"
			"	movem.l	%%d0/%%d1/%%a0/%%a1,%1@\n"
			"	addq.l	#8,%1; addq.l #8,%1\n"
			"	dbra	%2,1b\n"
			"	clr.w	%2; subq.l #1,%2\n"
			"	jcc	1b"
			: "=a" (src), "=a" (dst), "=d" (size)
			: "0" (src), "1" (dst), "2" (size / 16 - 1)
			: "d0", "d1", "a0", "a1", "memory");
	अन्यथा
		यंत्र अस्थिर ("\n"
			"1:	subq.l	#8,%0; subq.l #8,%0\n"
			"	movem.l	%0@,%%d0/%%d1/%%a0/%%a1\n"
			"	movem.l	%%d0/%%d1/%%a0/%%a1,-(%1)\n"
			"	dbra	%2,1b\n"
			"	clr.w	%2; subq.l #1,%2\n"
			"	jcc 1b"
			: "=a" (src), "=a" (dst), "=d" (size)
			: "0" (src + size), "1" (dst + size), "2" (size / 16 - 1)
			: "d0", "d1", "a0", "a1", "memory");
पूर्ण

#अगर_घोषित BPL

/*
 * This expands a up to 8 bit color पूर्णांकo two दीर्घs
 * क्रम movel operations.
 */
अटल स्थिर u32 four2दीर्घ[] = अणु
	0x00000000, 0x000000ff, 0x0000ff00, 0x0000ffff,
	0x00ff0000, 0x00ff00ff, 0x00ffff00, 0x00ffffff,
	0xff000000, 0xff0000ff, 0xff00ff00, 0xff00ffff,
	0xffff0000, 0xffff00ff, 0xffffff00, 0xffffffff,
पूर्ण;

अटल अंतरभूत व्योम expand8_col2mask(u8 c, u32 m[])
अणु
	m[0] = four2दीर्घ[c & 15];
#अगर BPL > 4
	m[1] = four2दीर्घ[c >> 4];
#पूर्ण_अगर
पूर्ण

अटल अंतरभूत व्योम expand8_2col2mask(u8 fg, u8 bg, u32 fgm[], u32 bgm[])
अणु
	fgm[0] = four2दीर्घ[fg & 15] ^ (bgm[0] = four2दीर्घ[bg & 15]);
#अगर BPL > 4
	fgm[1] = four2दीर्घ[fg >> 4] ^ (bgm[1] = four2दीर्घ[bg >> 4]);
#पूर्ण_अगर
पूर्ण

/*
 * set an 8bit value to a color
 */
अटल अंतरभूत व्योम fill8_col(u8 *dst, u32 m[])
अणु
	u32 पंचांगp = m[0];
	dst[0] = पंचांगp;
	dst[2] = (पंचांगp >>= 8);
#अगर BPL > 2
	dst[4] = (पंचांगp >>= 8);
	dst[6] = पंचांगp >> 8;
#पूर्ण_अगर
#अगर BPL > 4
	पंचांगp = m[1];
	dst[8] = पंचांगp;
	dst[10] = (पंचांगp >>= 8);
	dst[12] = (पंचांगp >>= 8);
	dst[14] = पंचांगp >> 8;
#पूर्ण_अगर
पूर्ण

/*
 * set an 8bit value according to क्रमeground/background color
 */
अटल अंतरभूत व्योम fill8_2col(u8 *dst, u8 fg, u8 bg, u32 mask)
अणु
	u32 fgm[2], bgm[2], पंचांगp;

	expand8_2col2mask(fg, bg, fgm, bgm);

	mask |= mask << 8;
#अगर BPL > 2
	mask |= mask << 16;
#पूर्ण_अगर
	पंचांगp = (mask & fgm[0]) ^ bgm[0];
	dst[0] = पंचांगp;
	dst[2] = (पंचांगp >>= 8);
#अगर BPL > 2
	dst[4] = (पंचांगp >>= 8);
	dst[6] = पंचांगp >> 8;
#पूर्ण_अगर
#अगर BPL > 4
	पंचांगp = (mask & fgm[1]) ^ bgm[1];
	dst[8] = पंचांगp;
	dst[10] = (पंचांगp >>= 8);
	dst[12] = (पंचांगp >>= 8);
	dst[14] = पंचांगp >> 8;
#पूर्ण_अगर
पूर्ण

अटल स्थिर u32 two2word[] = अणु
	0x00000000, 0xffff0000, 0x0000ffff, 0xffffffff
पूर्ण;

अटल अंतरभूत व्योम expand16_col2mask(u8 c, u32 m[])
अणु
	m[0] = two2word[c & 3];
#अगर BPL > 2
	m[1] = two2word[(c >> 2) & 3];
#पूर्ण_अगर
#अगर BPL > 4
	m[2] = two2word[(c >> 4) & 3];
	m[3] = two2word[c >> 6];
#पूर्ण_अगर
पूर्ण

अटल अंतरभूत व्योम expand16_2col2mask(u8 fg, u8 bg, u32 fgm[], u32 bgm[])
अणु
	bgm[0] = two2word[bg & 3];
	fgm[0] = two2word[fg & 3] ^ bgm[0];
#अगर BPL > 2
	bgm[1] = two2word[(bg >> 2) & 3];
	fgm[1] = two2word[(fg >> 2) & 3] ^ bgm[1];
#पूर्ण_अगर
#अगर BPL > 4
	bgm[2] = two2word[(bg >> 4) & 3];
	fgm[2] = two2word[(fg >> 4) & 3] ^ bgm[2];
	bgm[3] = two2word[bg >> 6];
	fgm[3] = two2word[fg >> 6] ^ bgm[3];
#पूर्ण_अगर
पूर्ण

अटल अंतरभूत u32 *fill16_col(u32 *dst, पूर्णांक rows, u32 m[])
अणु
	जबतक (rows) अणु
		*dst++ = m[0];
#अगर BPL > 2
		*dst++ = m[1];
#पूर्ण_अगर
#अगर BPL > 4
		*dst++ = m[2];
		*dst++ = m[3];
#पूर्ण_अगर
		rows--;
	पूर्ण
	वापस dst;
पूर्ण

अटल अंतरभूत व्योम स_हटाओ32_col(व्योम *dst, व्योम *src, u32 mask, u32 h, u32 bytes)
अणु
	u32 *s, *d, v;

        s = src;
        d = dst;
        करो अणु
                v = (*s++ & mask) | (*d  & ~mask);
                *d++ = v;
#अगर BPL > 2
                v = (*s++ & mask) | (*d  & ~mask);
                *d++ = v;
#पूर्ण_अगर
#अगर BPL > 4
                v = (*s++ & mask) | (*d  & ~mask);
                *d++ = v;
                v = (*s++ & mask) | (*d  & ~mask);
                *d++ = v;
#पूर्ण_अगर
                d = (u32 *)((u8 *)d + bytes);
                s = (u32 *)((u8 *)s + bytes);
        पूर्ण जबतक (--h);
पूर्ण

#पूर्ण_अगर

#पूर्ण_अगर /* _VIDEO_ATAFB_UTILS_H */
