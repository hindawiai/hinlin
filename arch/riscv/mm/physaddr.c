<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0

#समावेश <linux/types.h>
#समावेश <linux/mmdebug.h>
#समावेश <linux/mm.h>
#समावेश <यंत्र/page.h>
#समावेश <यंत्र/sections.h>

phys_addr_t __virt_to_phys(अचिन्हित दीर्घ x)
अणु
	phys_addr_t y = x - PAGE_OFFSET;

	/*
	 * Boundary checking aginst the kernel linear mapping space.
	 */
	WARN(y >= KERN_VIRT_SIZE,
	     "virt_to_phys used for non-linear address: %pK (%pS)\n",
	     (व्योम *)x, (व्योम *)x);

	वापस __va_to_pa_nodebug(x);
पूर्ण
EXPORT_SYMBOL(__virt_to_phys);

phys_addr_t __phys_addr_symbol(अचिन्हित दीर्घ x)
अणु
	अचिन्हित दीर्घ kernel_start = (अचिन्हित दीर्घ)kernel_virt_addr;
	अचिन्हित दीर्घ kernel_end = (अचिन्हित दीर्घ)_end;

	/*
	 * Boundary checking aginst the kernel image mapping.
	 * __pa_symbol should only be used on kernel symbol addresses.
	 */
	VIRTUAL_BUG_ON(x < kernel_start || x > kernel_end);

	वापस __va_to_pa_nodebug(x);
पूर्ण
EXPORT_SYMBOL(__phys_addr_symbol);
