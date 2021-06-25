<शैली गुरु>
/*
 * This file is subject to the terms and conditions of the GNU General Public
 * License.  See the file "COPYING" in the मुख्य directory of this archive
 * क्रम more details.
 *
 * Copyright (C) 2005 Thiemo Seufer
 * Copyright (C) 2005  MIPS Technologies, Inc.	All rights reserved.
 *	Author: Maciej W. Rozycki <macro@mips.com>
 */


#समावेश <यंत्र/addrspace.h>
#समावेश <यंत्र/bug.h>
#समावेश <यंत्र/cacheflush.h>

#अगर_अघोषित CKSEG2
#घोषणा CKSEG2 CKSSEG
#पूर्ण_अगर
#अगर_अघोषित TO_PHYS_MASK
#घोषणा TO_PHYS_MASK -1
#पूर्ण_अगर

/*
 * FUNC is executed in one of the uncached segments, depending on its
 * original address as follows:
 *
 * 1. If the original address is in CKSEG0 or CKSEG1, then the uncached
 *    segment used is CKSEG1.
 * 2. If the original address is in XKPHYS, then the uncached segment
 *    used is XKPHYS(2).
 * 3. Otherwise it's a bug.
 *
 * The same remapping is करोne with the stack poपूर्णांकer.  Stack handling
 * works because we करोn't handle stack arguments or more complex वापस
 * values, so we can aव्योम sharing the same stack area between a cached
 * and the uncached mode.
 */
अचिन्हित दीर्घ run_uncached(व्योम *func)
अणु
	रेजिस्टर दीर्घ ret __यंत्र__("$2");
	दीर्घ lfunc = (दीर्घ)func, ufunc;
	दीर्घ usp;
	दीर्घ sp;

	__यंत्र__("move %0, $sp" : "=r" (sp));

	अगर (sp >= (दीर्घ)CKSEG0 && sp < (दीर्घ)CKSEG2)
		usp = CKSEG1ADDR(sp);
#अगर_घोषित CONFIG_64BIT
	अन्यथा अगर ((दीर्घ दीर्घ)sp >= (दीर्घ दीर्घ)PHYS_TO_XKPHYS(0, 0) &&
		 (दीर्घ दीर्घ)sp < (दीर्घ दीर्घ)PHYS_TO_XKPHYS(8, 0))
		usp = PHYS_TO_XKPHYS(K_CALG_UNCACHED,
				     XKPHYS_TO_PHYS((दीर्घ दीर्घ)sp));
#पूर्ण_अगर
	अन्यथा अणु
		BUG();
		usp = sp;
	पूर्ण
	अगर (lfunc >= (दीर्घ)CKSEG0 && lfunc < (दीर्घ)CKSEG2)
		ufunc = CKSEG1ADDR(lfunc);
#अगर_घोषित CONFIG_64BIT
	अन्यथा अगर ((दीर्घ दीर्घ)lfunc >= (दीर्घ दीर्घ)PHYS_TO_XKPHYS(0, 0) &&
		 (दीर्घ दीर्घ)lfunc < (दीर्घ दीर्घ)PHYS_TO_XKPHYS(8, 0))
		ufunc = PHYS_TO_XKPHYS(K_CALG_UNCACHED,
				       XKPHYS_TO_PHYS((दीर्घ दीर्घ)lfunc));
#पूर्ण_अगर
	अन्यथा अणु
		BUG();
		ufunc = lfunc;
	पूर्ण

	__यंत्र__ __अस्थिर__ (
		"	move	$16, $sp\n"
		"	move	$sp, %1\n"
		"	jalr	%2\n"
		"	move	$sp, $16"
		: "=r" (ret)
		: "r" (usp), "r" (ufunc)
		: "$16", "$31");

	वापस ret;
पूर्ण
