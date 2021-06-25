<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#समावेश <linux/init.h>
#समावेश <linux/mm.h>
#समावेश <यंत्र/mtrr.h>
#समावेश <यंत्र/msr.h>

#समावेश "mtrr.h"

अटल व्योम
amd_get_mtrr(अचिन्हित पूर्णांक reg, अचिन्हित दीर्घ *base,
	     अचिन्हित दीर्घ *size, mtrr_type *type)
अणु
	अचिन्हित दीर्घ low, high;

	rdmsr(MSR_K6_UWCCR, low, high);
	/* Upper dword is region 1, lower is region 0 */
	अगर (reg == 1)
		low = high;
	/* The base masks off on the right alignment */
	*base = (low & 0xFFFE0000) >> PAGE_SHIFT;
	*type = 0;
	अगर (low & 1)
		*type = MTRR_TYPE_UNCACHABLE;
	अगर (low & 2)
		*type = MTRR_TYPE_WRCOMB;
	अगर (!(low & 3)) अणु
		*size = 0;
		वापस;
	पूर्ण
	/*
	 * This needs a little explaining. The size is stored as an
	 * inverted mask of bits of 128K granularity 15 bits दीर्घ offset
	 * 2 bits.
	 *
	 * So to get a size we करो invert the mask and add 1 to the lowest
	 * mask bit (4 as its 2 bits in). This gives us a size we then shअगरt
	 * to turn पूर्णांकo 128K blocks.
	 *
	 * eg              111 1111 1111 1100      is 512K
	 *
	 * invert          000 0000 0000 0011
	 * +1              000 0000 0000 0100
	 * *128K   ...
	 */
	low = (~low) & 0x1FFFC;
	*size = (low + 4) << (15 - PAGE_SHIFT);
पूर्ण

/**
 * amd_set_mtrr - Set variable MTRR रेजिस्टर on the local CPU.
 *
 * @reg The रेजिस्टर to set.
 * @base The base address of the region.
 * @size The size of the region. If this is 0 the region is disabled.
 * @type The type of the region.
 *
 * Returns nothing.
 */
अटल व्योम
amd_set_mtrr(अचिन्हित पूर्णांक reg, अचिन्हित दीर्घ base, अचिन्हित दीर्घ size, mtrr_type type)
अणु
	u32 regs[2];

	/*
	 * Low is MTRR0, High MTRR 1
	 */
	rdmsr(MSR_K6_UWCCR, regs[0], regs[1]);
	/*
	 * Blank to disable
	 */
	अगर (size == 0) अणु
		regs[reg] = 0;
	पूर्ण अन्यथा अणु
		/*
		 * Set the रेजिस्टर to the base, the type (off by one) and an
		 * inverted biपंचांगask of the size The size is the only odd
		 * bit. We are fed say 512K We invert this and we get 111 1111
		 * 1111 1011 but अगर you subtract one and invert you get the
		 * desired 111 1111 1111 1100 mask
		 *
		 *  But ~(x - 1) == ~x + 1 == -x. Two's complement rocks!
		 */
		regs[reg] = (-size >> (15 - PAGE_SHIFT) & 0x0001FFFC)
		    | (base << PAGE_SHIFT) | (type + 1);
	पूर्ण

	/*
	 * The ग_लिखोback rule is quite specअगरic. See the manual. Its
	 * disable local पूर्णांकerrupts, ग_लिखो back the cache, set the mtrr
	 */
	wbinvd();
	wrmsr(MSR_K6_UWCCR, regs[0], regs[1]);
पूर्ण

अटल पूर्णांक
amd_validate_add_page(अचिन्हित दीर्घ base, अचिन्हित दीर्घ size, अचिन्हित पूर्णांक type)
अणु
	/*
	 * Apply the K6 block alignment and size rules
	 * In order
	 * o Uncached or gathering only
	 * o 128K or bigger block
	 * o Power of 2 block
	 * o base suitably aligned to the घातer
	 */
	अगर (type > MTRR_TYPE_WRCOMB || size < (1 << (17 - PAGE_SHIFT))
	    || (size & ~(size - 1)) - size || (base & (size - 1)))
		वापस -EINVAL;
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा mtrr_ops amd_mtrr_ops = अणु
	.venकरोr            = X86_VENDOR_AMD,
	.set               = amd_set_mtrr,
	.get               = amd_get_mtrr,
	.get_मुक्त_region   = generic_get_मुक्त_region,
	.validate_add_page = amd_validate_add_page,
	.have_wrcomb       = positive_have_wrcomb,
पूर्ण;

पूर्णांक __init amd_init_mtrr(व्योम)
अणु
	set_mtrr_ops(&amd_mtrr_ops);
	वापस 0;
पूर्ण
