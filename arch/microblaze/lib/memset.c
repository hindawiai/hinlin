<शैली गुरु>
/*
 * Copyright (C) 2008-2009 Michal Simek <monstr@monstr.eu>
 * Copyright (C) 2008-2009 PetaLogix
 * Copyright (C) 2007 John Williams
 *
 * Reasonably optimised generic C-code क्रम स_रखो on Microblaze
 * This is generic C code to करो efficient, alignment-aware स_नकल.
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

#अगर_घोषित __HAVE_ARCH_MEMSET
#अगर_अघोषित CONFIG_OPT_LIB_FUNCTION
व्योम *स_रखो(व्योम *v_src, पूर्णांक c, __kernel_माप_प्रकार n)
अणु
	अक्षर *src = v_src;

	/* Truncate c to 8 bits */
	c = (c & 0xFF);

	/* Simple, byte oriented स_रखो or the rest of count. */
	जबतक (n--)
		*src++ = c;

	वापस v_src;
पूर्ण
#अन्यथा /* CONFIG_OPT_LIB_FUNCTION */
व्योम *स_रखो(व्योम *v_src, पूर्णांक c, __kernel_माप_प्रकार n)
अणु
	अक्षर *src = v_src;
	uपूर्णांक32_t *i_src;
	uपूर्णांक32_t w32 = 0;

	/* Truncate c to 8 bits */
	c = (c & 0xFF);

	अगर (unlikely(c)) अणु
		/* Make a repeating word out of it */
		w32 = c;
		w32 |= w32 << 8;
		w32 |= w32 << 16;
	पूर्ण

	अगर (likely(n >= 4)) अणु
		/* Align the destination to a word boundary */
		/* This is करोne in an endian independent manner */
		चयन ((अचिन्हित) src & 3) अणु
		हाल 1:
			*src++ = c;
			--n;
			fallthrough;
		हाल 2:
			*src++ = c;
			--n;
			fallthrough;
		हाल 3:
			*src++ = c;
			--n;
		पूर्ण

		i_src  = (व्योम *)src;

		/* Do as many full-word copies as we can */
		क्रम (; n >= 4; n -= 4)
			*i_src++ = w32;

		src  = (व्योम *)i_src;
	पूर्ण

	/* Simple, byte oriented स_रखो or the rest of count. */
	जबतक (n--)
		*src++ = c;

	वापस v_src;
पूर्ण
#पूर्ण_अगर /* CONFIG_OPT_LIB_FUNCTION */
EXPORT_SYMBOL(स_रखो);
#पूर्ण_अगर /* __HAVE_ARCH_MEMSET */
