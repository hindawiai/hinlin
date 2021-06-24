<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#समावेश <linux/memblock.h>
#समावेश <linux/mmdebug.h>
#समावेश <linux/export.h>
#समावेश <linux/mm.h>

#समावेश <यंत्र/page.h>
#समावेश <linux/vदो_स्मृति.h>

#समावेश "physaddr.h"

#अगर_घोषित CONFIG_X86_64

#अगर_घोषित CONFIG_DEBUG_VIRTUAL
अचिन्हित दीर्घ __phys_addr(अचिन्हित दीर्घ x)
अणु
	अचिन्हित दीर्घ y = x - __START_KERNEL_map;

	/* use the carry flag to determine अगर x was < __START_KERNEL_map */
	अगर (unlikely(x > y)) अणु
		x = y + phys_base;

		VIRTUAL_BUG_ON(y >= KERNEL_IMAGE_SIZE);
	पूर्ण अन्यथा अणु
		x = y + (__START_KERNEL_map - PAGE_OFFSET);

		/* carry flag will be set अगर starting x was >= PAGE_OFFSET */
		VIRTUAL_BUG_ON((x > y) || !phys_addr_valid(x));
	पूर्ण

	वापस x;
पूर्ण
EXPORT_SYMBOL(__phys_addr);

अचिन्हित दीर्घ __phys_addr_symbol(अचिन्हित दीर्घ x)
अणु
	अचिन्हित दीर्घ y = x - __START_KERNEL_map;

	/* only check upper bounds since lower bounds will trigger carry */
	VIRTUAL_BUG_ON(y >= KERNEL_IMAGE_SIZE);

	वापस y + phys_base;
पूर्ण
EXPORT_SYMBOL(__phys_addr_symbol);
#पूर्ण_अगर

bool __virt_addr_valid(अचिन्हित दीर्घ x)
अणु
	अचिन्हित दीर्घ y = x - __START_KERNEL_map;

	/* use the carry flag to determine अगर x was < __START_KERNEL_map */
	अगर (unlikely(x > y)) अणु
		x = y + phys_base;

		अगर (y >= KERNEL_IMAGE_SIZE)
			वापस false;
	पूर्ण अन्यथा अणु
		x = y + (__START_KERNEL_map - PAGE_OFFSET);

		/* carry flag will be set अगर starting x was >= PAGE_OFFSET */
		अगर ((x > y) || !phys_addr_valid(x))
			वापस false;
	पूर्ण

	वापस pfn_valid(x >> PAGE_SHIFT);
पूर्ण
EXPORT_SYMBOL(__virt_addr_valid);

#अन्यथा

#अगर_घोषित CONFIG_DEBUG_VIRTUAL
अचिन्हित दीर्घ __phys_addr(अचिन्हित दीर्घ x)
अणु
	अचिन्हित दीर्घ phys_addr = x - PAGE_OFFSET;
	/* VMALLOC_* aren't स्थिरants  */
	VIRTUAL_BUG_ON(x < PAGE_OFFSET);
	VIRTUAL_BUG_ON(__vदो_स्मृति_start_set && is_vदो_स्मृति_addr((व्योम *) x));
	/* max_low_pfn is set early, but not _that_ early */
	अगर (max_low_pfn) अणु
		VIRTUAL_BUG_ON((phys_addr >> PAGE_SHIFT) > max_low_pfn);
		BUG_ON(slow_virt_to_phys((व्योम *)x) != phys_addr);
	पूर्ण
	वापस phys_addr;
पूर्ण
EXPORT_SYMBOL(__phys_addr);
#पूर्ण_अगर

bool __virt_addr_valid(अचिन्हित दीर्घ x)
अणु
	अगर (x < PAGE_OFFSET)
		वापस false;
	अगर (__vदो_स्मृति_start_set && is_vदो_स्मृति_addr((व्योम *) x))
		वापस false;
	अगर (x >= FIXADDR_START)
		वापस false;
	वापस pfn_valid((x - PAGE_OFFSET) >> PAGE_SHIFT);
पूर्ण
EXPORT_SYMBOL(__virt_addr_valid);

#पूर्ण_अगर	/* CONFIG_X86_64 */
