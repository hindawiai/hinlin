<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#समावेश <linux/bug.h>
#समावेश <linux/export.h>
#समावेश <linux/types.h>
#समावेश <linux/mmdebug.h>
#समावेश <linux/mm.h>

#समावेश <यंत्र/sections.h>
#समावेश <यंत्र/पन.स>
#समावेश <यंत्र/page.h>
#समावेश <यंत्र/dma.h>

अटल अंतरभूत bool __debug_virt_addr_valid(अचिन्हित दीर्घ x)
अणु
	/* high_memory करोes not get immediately defined, and there
	 * are early callers of __pa() against PAGE_OFFSET
	 */
	अगर (!high_memory && x >= PAGE_OFFSET)
		वापस true;

	अगर (high_memory && x >= PAGE_OFFSET && x < (अचिन्हित दीर्घ)high_memory)
		वापस true;

	/*
	 * MAX_DMA_ADDRESS is a भव address that may not correspond to an
	 * actual physical address. Enough code relies on
	 * virt_to_phys(MAX_DMA_ADDRESS) that we just need to work around it
	 * and always वापस true.
	 */
	अगर (x == MAX_DMA_ADDRESS)
		वापस true;

	वापस false;
पूर्ण

phys_addr_t __virt_to_phys(अस्थिर स्थिर व्योम *x)
अणु
	WARN(!__debug_virt_addr_valid((अचिन्हित दीर्घ)x),
	     "virt_to_phys used for non-linear address: %pK (%pS)\n",
	     x, x);

	वापस __virt_to_phys_nodebug(x);
पूर्ण
EXPORT_SYMBOL(__virt_to_phys);

phys_addr_t __phys_addr_symbol(अचिन्हित दीर्घ x)
अणु
	/* This is bounds checking against the kernel image only.
	 * __pa_symbol should only be used on kernel symbol addresses.
	 */
	VIRTUAL_BUG_ON(x < (अचिन्हित दीर्घ)_text ||
		       x > (अचिन्हित दीर्घ)_end);

	वापस __pa_symbol_nodebug(x);
पूर्ण
EXPORT_SYMBOL(__phys_addr_symbol);
