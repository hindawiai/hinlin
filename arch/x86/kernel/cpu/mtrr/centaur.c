<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#समावेश <linux/init.h>
#समावेश <linux/mm.h>

#समावेश <यंत्र/mtrr.h>
#समावेश <यंत्र/msr.h>

#समावेश "mtrr.h"

अटल काष्ठा अणु
	अचिन्हित दीर्घ high;
	अचिन्हित दीर्घ low;
पूर्ण centaur_mcr[8];

अटल u8 centaur_mcr_reserved;
अटल u8 centaur_mcr_type;	/* 0 क्रम winchip, 1 क्रम winchip2 */

/**
 * centaur_get_मुक्त_region - Get a मुक्त MTRR.
 *
 * @base: The starting (base) address of the region.
 * @size: The size (in bytes) of the region.
 *
 * Returns: the index of the region on success, अन्यथा -1 on error.
 */
अटल पूर्णांक
centaur_get_मुक्त_region(अचिन्हित दीर्घ base, अचिन्हित दीर्घ size, पूर्णांक replace_reg)
अणु
	अचिन्हित दीर्घ lbase, lsize;
	mtrr_type ltype;
	पूर्णांक i, max;

	max = num_var_ranges;
	अगर (replace_reg >= 0 && replace_reg < max)
		वापस replace_reg;

	क्रम (i = 0; i < max; ++i) अणु
		अगर (centaur_mcr_reserved & (1 << i))
			जारी;
		mtrr_अगर->get(i, &lbase, &lsize, &ltype);
		अगर (lsize == 0)
			वापस i;
	पूर्ण

	वापस -ENOSPC;
पूर्ण

/*
 * Report boot समय MCR setups
 */
व्योम mtrr_centaur_report_mcr(पूर्णांक mcr, u32 lo, u32 hi)
अणु
	centaur_mcr[mcr].low = lo;
	centaur_mcr[mcr].high = hi;
पूर्ण

अटल व्योम
centaur_get_mcr(अचिन्हित पूर्णांक reg, अचिन्हित दीर्घ *base,
		अचिन्हित दीर्घ *size, mtrr_type * type)
अणु
	*base = centaur_mcr[reg].high >> PAGE_SHIFT;
	*size = -(centaur_mcr[reg].low & 0xfffff000) >> PAGE_SHIFT;
	*type = MTRR_TYPE_WRCOMB;		/* ग_लिखो-combining  */

	अगर (centaur_mcr_type == 1 && ((centaur_mcr[reg].low & 31) & 2))
		*type = MTRR_TYPE_UNCACHABLE;
	अगर (centaur_mcr_type == 1 && (centaur_mcr[reg].low & 31) == 25)
		*type = MTRR_TYPE_WRBACK;
	अगर (centaur_mcr_type == 0 && (centaur_mcr[reg].low & 31) == 31)
		*type = MTRR_TYPE_WRBACK;
पूर्ण

अटल व्योम
centaur_set_mcr(अचिन्हित पूर्णांक reg, अचिन्हित दीर्घ base,
		अचिन्हित दीर्घ size, mtrr_type type)
अणु
	अचिन्हित दीर्घ low, high;

	अगर (size == 0) अणु
		/* Disable */
		high = low = 0;
	पूर्ण अन्यथा अणु
		high = base << PAGE_SHIFT;
		अगर (centaur_mcr_type == 0) अणु
			/* Only support ग_लिखो-combining... */
			low = -size << PAGE_SHIFT | 0x1f;
		पूर्ण अन्यथा अणु
			अगर (type == MTRR_TYPE_UNCACHABLE)
				low = -size << PAGE_SHIFT | 0x02; /* NC */
			अन्यथा
				low = -size << PAGE_SHIFT | 0x09; /* WWO, WC */
		पूर्ण
	पूर्ण
	centaur_mcr[reg].high = high;
	centaur_mcr[reg].low = low;
	wrmsr(MSR_IDT_MCR0 + reg, low, high);
पूर्ण

अटल पूर्णांक
centaur_validate_add_page(अचिन्हित दीर्घ base, अचिन्हित दीर्घ size, अचिन्हित पूर्णांक type)
अणु
	/*
	 * FIXME: Winchip2 supports uncached
	 */
	अगर (type != MTRR_TYPE_WRCOMB &&
	    (centaur_mcr_type == 0 || type != MTRR_TYPE_UNCACHABLE)) अणु
		pr_warn("mtrr: only write-combining%s supported\n",
			   centaur_mcr_type ? " and uncacheable are" : " is");
		वापस -EINVAL;
	पूर्ण
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा mtrr_ops centaur_mtrr_ops = अणु
	.venकरोr            = X86_VENDOR_CENTAUR,
	.set               = centaur_set_mcr,
	.get               = centaur_get_mcr,
	.get_मुक्त_region   = centaur_get_मुक्त_region,
	.validate_add_page = centaur_validate_add_page,
	.have_wrcomb       = positive_have_wrcomb,
पूर्ण;

पूर्णांक __init centaur_init_mtrr(व्योम)
अणु
	set_mtrr_ops(&centaur_mtrr_ops);
	वापस 0;
पूर्ण
