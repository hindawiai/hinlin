<शैली गुरु>
/*
 * Copyright (C) 2008-2009 Michal Simek <monstr@monstr.eu>
 * Copyright (C) 2008-2009 PetaLogix
 * Copyright (C) 2007 John Williams
 *
 * Reasonably optimised generic C-code क्रम स_नकल on Microblaze
 * This is generic C code to करो efficient, alignment-aware स_हटाओ.
 *
 * It is based on demo code originally Copyright 2001 by Intel Corp, taken from
 * http://www.embedded.com/showArticle.jhपंचांगl?articleID=19205567
 *
 * Attempts were made, unsuccessfully, to contact the original
 * author of this code (Michael Morrow, Intel).  Below is the original
 * copyright notice.
 *
 * This software has been developed by Intel Corporation.
 * Intel specअगरically disclaims all warranties, express or
 * implied, and all liability, including consequential and
 * other indirect damages, क्रम the use of this program, including
 * liability क्रम infringement of any proprietary rights,
 * and including the warranties of merchantability and fitness
 * क्रम a particular purpose. Intel करोes not assume any
 * responsibility क्रम and errors which may appear in this program
 * not any responsibility to update it.
 */

#समावेश <linux/export.h>
#समावेश <linux/types.h>
#समावेश <linux/मानकघोष.स>
#समावेश <linux/compiler.h>
#समावेश <linux/माला.स>

#अगर_घोषित __HAVE_ARCH_MEMMOVE
#अगर_अघोषित CONFIG_OPT_LIB_FUNCTION
व्योम *स_हटाओ(व्योम *v_dst, स्थिर व्योम *v_src, __kernel_माप_प्रकार c)
अणु
	स्थिर अक्षर *src = v_src;
	अक्षर *dst = v_dst;

	अगर (!c)
		वापस v_dst;

	/* Use स_नकल when source is higher than dest */
	अगर (v_dst <= v_src)
		वापस स_नकल(v_dst, v_src, c);

	/* copy backwards, from end to beginning */
	src += c;
	dst += c;

	/* Simple, byte oriented स_हटाओ. */
	जबतक (c--)
		*--dst = *--src;

	वापस v_dst;
पूर्ण
#अन्यथा /* CONFIG_OPT_LIB_FUNCTION */
व्योम *स_हटाओ(व्योम *v_dst, स्थिर व्योम *v_src, __kernel_माप_प्रकार c)
अणु
	स्थिर अक्षर *src = v_src;
	अक्षर *dst = v_dst;
	स्थिर uपूर्णांक32_t *i_src;
	uपूर्णांक32_t *i_dst;

	अगर (!c)
		वापस v_dst;

	/* Use स_नकल when source is higher than dest */
	अगर (v_dst <= v_src)
		वापस स_नकल(v_dst, v_src, c);

	/* The following code tries to optimize the copy by using अचिन्हित
	 * alignment. This will work fine अगर both source and destination are
	 * aligned on the same boundary. However, अगर they are aligned on
	 * dअगरferent boundaries shअगरts will be necessary. This might result in
	 * bad perक्रमmance on MicroBlaze प्रणालीs without a barrel shअगरter.
	 */
	/* FIXME this part needs more test */
	/* Do a descending copy - this is a bit trickier! */
	dst += c;
	src += c;

	अगर (c >= 4) अणु
		अचिन्हित  value, buf_hold;

		/* Align the destination to a word boundary. */
		/* This is करोne in an endian independent manner. */

		चयन ((अचिन्हित दीर्घ)dst & 3) अणु
		हाल 3:
			*--dst = *--src;
			--c;
			fallthrough;
		हाल 2:
			*--dst = *--src;
			--c;
			fallthrough;
		हाल 1:
			*--dst = *--src;
			--c;
		पूर्ण

		i_dst = (व्योम *)dst;
		/* Choose a copy scheme based on the source */
		/* alignment relative to dstination. */
		चयन ((अचिन्हित दीर्घ)src & 3) अणु
		हाल 0x0:	/* Both byte offsets are aligned */

			i_src  = (स्थिर व्योम *)src;

			क्रम (; c >= 4; c -= 4)
				*--i_dst = *--i_src;

			src  = (स्थिर व्योम *)i_src;
			अवरोध;
		हाल 0x1:	/* Unaligned - Off by 1 */
			/* Word align the source */
			i_src = (स्थिर व्योम *) (((अचिन्हित)src + 4) & ~3);
#अगर_अघोषित __MICROBLAZEEL__
			/* Load the holding buffer */
			buf_hold = *--i_src >> 24;

			क्रम (; c >= 4; c -= 4) अणु
				value = *--i_src;
				*--i_dst = buf_hold << 8 | value;
				buf_hold = value >> 24;
			पूर्ण
#अन्यथा
			/* Load the holding buffer */
			buf_hold = (*--i_src & 0xFF) << 24;

			क्रम (; c >= 4; c -= 4) अणु
				value = *--i_src;
				*--i_dst = buf_hold |
						((value & 0xFFFFFF00) >> 8);
				buf_hold = (value  & 0xFF) << 24;
			पूर्ण
#पूर्ण_अगर
			/* Realign the source */
			src = (स्थिर व्योम *)i_src;
			src += 1;
			अवरोध;
		हाल 0x2:	/* Unaligned - Off by 2 */
			/* Word align the source */
			i_src = (स्थिर व्योम *) (((अचिन्हित)src + 4) & ~3);
#अगर_अघोषित __MICROBLAZEEL__
			/* Load the holding buffer */
			buf_hold = *--i_src >> 16;

			क्रम (; c >= 4; c -= 4) अणु
				value = *--i_src;
				*--i_dst = buf_hold << 16 | value;
				buf_hold = value >> 16;
			पूर्ण
#अन्यथा
			/* Load the holding buffer */
			buf_hold = (*--i_src & 0xFFFF) << 16;

			क्रम (; c >= 4; c -= 4) अणु
				value = *--i_src;
				*--i_dst = buf_hold |
						((value & 0xFFFF0000) >> 16);
				buf_hold = (value & 0xFFFF) << 16;
			पूर्ण
#पूर्ण_अगर
			/* Realign the source */
			src = (स्थिर व्योम *)i_src;
			src += 2;
			अवरोध;
		हाल 0x3:	/* Unaligned - Off by 3 */
			/* Word align the source */
			i_src = (स्थिर व्योम *) (((अचिन्हित)src + 4) & ~3);
#अगर_अघोषित __MICROBLAZEEL__
			/* Load the holding buffer */
			buf_hold = *--i_src >> 8;

			क्रम (; c >= 4; c -= 4) अणु
				value = *--i_src;
				*--i_dst = buf_hold << 24 | value;
				buf_hold = value >> 8;
			पूर्ण
#अन्यथा
			/* Load the holding buffer */
			buf_hold = (*--i_src & 0xFFFFFF) << 8;

			क्रम (; c >= 4; c -= 4) अणु
				value = *--i_src;
				*--i_dst = buf_hold |
						((value & 0xFF000000) >> 24);
				buf_hold = (value & 0xFFFFFF) << 8;
			पूर्ण
#पूर्ण_अगर
			/* Realign the source */
			src = (स्थिर व्योम *)i_src;
			src += 3;
			अवरोध;
		पूर्ण
		dst = (व्योम *)i_dst;
	पूर्ण

	/* simple fast copy, ... unless a cache boundary is crossed */
	/* Finish off any reमुख्यing bytes */
	चयन (c) अणु
	हाल 4:
		*--dst = *--src;
		fallthrough;
	हाल 3:
		*--dst = *--src;
		fallthrough;
	हाल 2:
		*--dst = *--src;
		fallthrough;
	हाल 1:
		*--dst = *--src;
	पूर्ण
	वापस v_dst;
पूर्ण
#पूर्ण_अगर /* CONFIG_OPT_LIB_FUNCTION */
EXPORT_SYMBOL(स_हटाओ);
#पूर्ण_अगर /* __HAVE_ARCH_MEMMOVE */
