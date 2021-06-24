<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#समावेश <linux/bug.h>
#समावेश <linux/export.h>
#समावेश <linux/types.h>
#समावेश <linux/mmdebug.h>
#समावेश <linux/mm.h>

#समावेश <यंत्र/memory.h>

phys_addr_t __virt_to_phys(अचिन्हित दीर्घ x)
अणु
	WARN(!__is_lm_address(__tag_reset(x)),
	     "virt_to_phys used for non-linear address: %pK (%pS)\n",
	      (व्योम *)x,
	      (व्योम *)x);

	वापस __virt_to_phys_nodebug(x);
पूर्ण
EXPORT_SYMBOL(__virt_to_phys);

phys_addr_t __phys_addr_symbol(अचिन्हित दीर्घ x)
अणु
	/*
	 * This is bounds checking against the kernel image only.
	 * __pa_symbol should only be used on kernel symbol addresses.
	 */
	VIRTUAL_BUG_ON(x < (अचिन्हित दीर्घ) KERNEL_START ||
		       x > (अचिन्हित दीर्घ) KERNEL_END);
	वापस __pa_symbol_nodebug(x);
पूर्ण
EXPORT_SYMBOL(__phys_addr_symbol);
