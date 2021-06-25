<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#समावेश <linux/init.h>
#समावेश <linux/पन.स>
#समावेश <linux/mm.h>

#समावेश <यंत्र/processor-cyrix.h>
#समावेश <यंत्र/processor-flags.h>
#समावेश <यंत्र/mtrr.h>
#समावेश <यंत्र/msr.h>

#समावेश "mtrr.h"

अटल व्योम
cyrix_get_arr(अचिन्हित पूर्णांक reg, अचिन्हित दीर्घ *base,
	      अचिन्हित दीर्घ *size, mtrr_type * type)
अणु
	अचिन्हित अक्षर arr, ccr3, rcr, shअगरt;
	अचिन्हित दीर्घ flags;

	arr = CX86_ARR_BASE + (reg << 1) + reg;	/* aव्योम multiplication by 3 */

	local_irq_save(flags);

	ccr3 = getCx86(CX86_CCR3);
	setCx86(CX86_CCR3, (ccr3 & 0x0f) | 0x10);	/* enable MAPEN */
	((अचिन्हित अक्षर *)base)[3] = getCx86(arr);
	((अचिन्हित अक्षर *)base)[2] = getCx86(arr + 1);
	((अचिन्हित अक्षर *)base)[1] = getCx86(arr + 2);
	rcr = getCx86(CX86_RCR_BASE + reg);
	setCx86(CX86_CCR3, ccr3);			/* disable MAPEN */

	local_irq_restore(flags);

	shअगरt = ((अचिन्हित अक्षर *) base)[1] & 0x0f;
	*base >>= PAGE_SHIFT;

	/*
	 * Power of two, at least 4K on ARR0-ARR6, 256K on ARR7
	 * Note: shअगरt==0xf means 4G, this is unsupported.
	 */
	अगर (shअगरt)
		*size = (reg < 7 ? 0x1UL : 0x40UL) << (shअगरt - 1);
	अन्यथा
		*size = 0;

	/* Bit 0 is Cache Enable on ARR7, Cache Disable on ARR0-ARR6 */
	अगर (reg < 7) अणु
		चयन (rcr) अणु
		हाल 1:
			*type = MTRR_TYPE_UNCACHABLE;
			अवरोध;
		हाल 8:
			*type = MTRR_TYPE_WRBACK;
			अवरोध;
		हाल 9:
			*type = MTRR_TYPE_WRCOMB;
			अवरोध;
		हाल 24:
		शेष:
			*type = MTRR_TYPE_WRTHROUGH;
			अवरोध;
		पूर्ण
	पूर्ण अन्यथा अणु
		चयन (rcr) अणु
		हाल 0:
			*type = MTRR_TYPE_UNCACHABLE;
			अवरोध;
		हाल 8:
			*type = MTRR_TYPE_WRCOMB;
			अवरोध;
		हाल 9:
			*type = MTRR_TYPE_WRBACK;
			अवरोध;
		हाल 25:
		शेष:
			*type = MTRR_TYPE_WRTHROUGH;
			अवरोध;
		पूर्ण
	पूर्ण
पूर्ण

/*
 * cyrix_get_मुक्त_region - get a मुक्त ARR.
 *
 * @base: the starting (base) address of the region.
 * @size: the size (in bytes) of the region.
 *
 * Returns: the index of the region on success, अन्यथा -1 on error.
*/
अटल पूर्णांक
cyrix_get_मुक्त_region(अचिन्हित दीर्घ base, अचिन्हित दीर्घ size, पूर्णांक replace_reg)
अणु
	अचिन्हित दीर्घ lbase, lsize;
	mtrr_type ltype;
	पूर्णांक i;

	चयन (replace_reg) अणु
	हाल 7:
		अगर (size < 0x40)
			अवरोध;
		fallthrough;
	हाल 6:
	हाल 5:
	हाल 4:
		वापस replace_reg;
	हाल 3:
	हाल 2:
	हाल 1:
	हाल 0:
		वापस replace_reg;
	पूर्ण
	/* If we are to set up a region >32M then look at ARR7 immediately */
	अगर (size > 0x2000) अणु
		cyrix_get_arr(7, &lbase, &lsize, &ltype);
		अगर (lsize == 0)
			वापस 7;
		/* Else try ARR0-ARR6 first  */
	पूर्ण अन्यथा अणु
		क्रम (i = 0; i < 7; i++) अणु
			cyrix_get_arr(i, &lbase, &lsize, &ltype);
			अगर (lsize == 0)
				वापस i;
		पूर्ण
		/*
		 * ARR0-ARR6 isn't मुक्त
		 * try ARR7 but its size must be at least 256K
		 */
		cyrix_get_arr(i, &lbase, &lsize, &ltype);
		अगर ((lsize == 0) && (size >= 0x40))
			वापस i;
	पूर्ण
	वापस -ENOSPC;
पूर्ण

अटल u32 cr4, ccr3;

अटल व्योम prepare_set(व्योम)
अणु
	u32 cr0;

	/*  Save value of CR4 and clear Page Global Enable (bit 7)  */
	अगर (boot_cpu_has(X86_FEATURE_PGE)) अणु
		cr4 = __पढ़ो_cr4();
		__ग_लिखो_cr4(cr4 & ~X86_CR4_PGE);
	पूर्ण

	/*
	 * Disable and flush caches.
	 * Note that wbinvd flushes the TLBs as a side-effect
	 */
	cr0 = पढ़ो_cr0() | X86_CR0_CD;
	wbinvd();
	ग_लिखो_cr0(cr0);
	wbinvd();

	/* Cyrix ARRs - everything अन्यथा was excluded at the top */
	ccr3 = getCx86(CX86_CCR3);

	/* Cyrix ARRs - everything अन्यथा was excluded at the top */
	setCx86(CX86_CCR3, (ccr3 & 0x0f) | 0x10);
पूर्ण

अटल व्योम post_set(व्योम)
अणु
	/* Flush caches and TLBs */
	wbinvd();

	/* Cyrix ARRs - everything अन्यथा was excluded at the top */
	setCx86(CX86_CCR3, ccr3);

	/* Enable caches */
	ग_लिखो_cr0(पढ़ो_cr0() & ~X86_CR0_CD);

	/* Restore value of CR4 */
	अगर (boot_cpu_has(X86_FEATURE_PGE))
		__ग_लिखो_cr4(cr4);
पूर्ण

अटल व्योम cyrix_set_arr(अचिन्हित पूर्णांक reg, अचिन्हित दीर्घ base,
			  अचिन्हित दीर्घ size, mtrr_type type)
अणु
	अचिन्हित अक्षर arr, arr_type, arr_size;

	arr = CX86_ARR_BASE + (reg << 1) + reg;	/* aव्योम multiplication by 3 */

	/* count करोwn from 32M (ARR0-ARR6) or from 2G (ARR7) */
	अगर (reg >= 7)
		size >>= 6;

	size &= 0x7fff;		/* make sure arr_size <= 14 */
	क्रम (arr_size = 0; size; arr_size++, size >>= 1)
		;

	अगर (reg < 7) अणु
		चयन (type) अणु
		हाल MTRR_TYPE_UNCACHABLE:
			arr_type = 1;
			अवरोध;
		हाल MTRR_TYPE_WRCOMB:
			arr_type = 9;
			अवरोध;
		हाल MTRR_TYPE_WRTHROUGH:
			arr_type = 24;
			अवरोध;
		शेष:
			arr_type = 8;
			अवरोध;
		पूर्ण
	पूर्ण अन्यथा अणु
		चयन (type) अणु
		हाल MTRR_TYPE_UNCACHABLE:
			arr_type = 0;
			अवरोध;
		हाल MTRR_TYPE_WRCOMB:
			arr_type = 8;
			अवरोध;
		हाल MTRR_TYPE_WRTHROUGH:
			arr_type = 25;
			अवरोध;
		शेष:
			arr_type = 9;
			अवरोध;
		पूर्ण
	पूर्ण

	prepare_set();

	base <<= PAGE_SHIFT;
	setCx86(arr + 0,  ((अचिन्हित अक्षर *)&base)[3]);
	setCx86(arr + 1,  ((अचिन्हित अक्षर *)&base)[2]);
	setCx86(arr + 2, (((अचिन्हित अक्षर *)&base)[1]) | arr_size);
	setCx86(CX86_RCR_BASE + reg, arr_type);

	post_set();
पूर्ण

प्रकार काष्ठा अणु
	अचिन्हित दीर्घ	base;
	अचिन्हित दीर्घ	size;
	mtrr_type	type;
पूर्ण arr_state_t;

अटल arr_state_t arr_state[8] = अणु
	अणु0UL, 0UL, 0ULपूर्ण, अणु0UL, 0UL, 0ULपूर्ण, अणु0UL, 0UL, 0ULपूर्ण, अणु0UL, 0UL, 0ULपूर्ण,
	अणु0UL, 0UL, 0ULपूर्ण, अणु0UL, 0UL, 0ULपूर्ण, अणु0UL, 0UL, 0ULपूर्ण, अणु0UL, 0UL, 0ULपूर्ण
पूर्ण;

अटल अचिन्हित अक्षर ccr_state[7] = अणु 0, 0, 0, 0, 0, 0, 0 पूर्ण;

अटल व्योम cyrix_set_all(व्योम)
अणु
	पूर्णांक i;

	prepare_set();

	/* the CCRs are not contiguous */
	क्रम (i = 0; i < 4; i++)
		setCx86(CX86_CCR0 + i, ccr_state[i]);
	क्रम (; i < 7; i++)
		setCx86(CX86_CCR4 + i, ccr_state[i]);

	क्रम (i = 0; i < 8; i++) अणु
		cyrix_set_arr(i, arr_state[i].base,
			      arr_state[i].size, arr_state[i].type);
	पूर्ण

	post_set();
पूर्ण

अटल स्थिर काष्ठा mtrr_ops cyrix_mtrr_ops = अणु
	.venकरोr            = X86_VENDOR_CYRIX,
	.set_all	   = cyrix_set_all,
	.set               = cyrix_set_arr,
	.get               = cyrix_get_arr,
	.get_मुक्त_region   = cyrix_get_मुक्त_region,
	.validate_add_page = generic_validate_add_page,
	.have_wrcomb       = positive_have_wrcomb,
पूर्ण;

पूर्णांक __init cyrix_init_mtrr(व्योम)
अणु
	set_mtrr_ops(&cyrix_mtrr_ops);
	वापस 0;
पूर्ण
