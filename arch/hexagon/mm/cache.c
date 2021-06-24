<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Cache management functions क्रम Hexagon
 *
 * Copyright (c) 2010-2011, The Linux Foundation. All rights reserved.
 */

#समावेश <linux/mm.h>
#समावेश <यंत्र/cacheflush.h>
#समावेश <यंत्र/hexagon_vm.h>

#घोषणा spanlines(start, end) \
	(((end - (start & ~(LINESIZE - 1))) >> LINEBITS) + 1)

व्योम flush_dcache_range(अचिन्हित दीर्घ start, अचिन्हित दीर्घ end)
अणु
	अचिन्हित दीर्घ lines = spanlines(start, end-1);
	अचिन्हित दीर्घ i, flags;

	start &= ~(LINESIZE - 1);

	local_irq_save(flags);

	क्रम (i = 0; i < lines; i++) अणु
		__यंत्र__ __अस्थिर__ (
		"	dccleaninva(%0);	"
		:
		: "r" (start)
		);
		start += LINESIZE;
	पूर्ण
	local_irq_restore(flags);
पूर्ण

व्योम flush_icache_range(अचिन्हित दीर्घ start, अचिन्हित दीर्घ end)
अणु
	अचिन्हित दीर्घ lines = spanlines(start, end-1);
	अचिन्हित दीर्घ i, flags;

	start &= ~(LINESIZE - 1);

	local_irq_save(flags);

	क्रम (i = 0; i < lines; i++) अणु
		__यंत्र__ __अस्थिर__ (
			"	dccleana(%0); "
			"	icinva(%0);	"
			:
			: "r" (start)
		);
		start += LINESIZE;
	पूर्ण
	__यंत्र__ __अस्थिर__ (
		"isync"
	);
	local_irq_restore(flags);
पूर्ण
EXPORT_SYMBOL(flush_icache_range);

व्योम hexagon_clean_dcache_range(अचिन्हित दीर्घ start, अचिन्हित दीर्घ end)
अणु
	अचिन्हित दीर्घ lines = spanlines(start, end-1);
	अचिन्हित दीर्घ i, flags;

	start &= ~(LINESIZE - 1);

	local_irq_save(flags);

	क्रम (i = 0; i < lines; i++) अणु
		__यंत्र__ __अस्थिर__ (
		"	dccleana(%0);	"
		:
		: "r" (start)
		);
		start += LINESIZE;
	पूर्ण
	local_irq_restore(flags);
पूर्ण

व्योम hexagon_inv_dcache_range(अचिन्हित दीर्घ start, अचिन्हित दीर्घ end)
अणु
	अचिन्हित दीर्घ lines = spanlines(start, end-1);
	अचिन्हित दीर्घ i, flags;

	start &= ~(LINESIZE - 1);

	local_irq_save(flags);

	क्रम (i = 0; i < lines; i++) अणु
		__यंत्र__ __अस्थिर__ (
		"	dcinva(%0);	"
		:
		: "r" (start)
		);
		start += LINESIZE;
	पूर्ण
	local_irq_restore(flags);
पूर्ण




/*
 * This is just really brutal and shouldn't be used anyways,
 * especially on V2.  Left here just in हाल.
 */
व्योम flush_cache_all_hexagon(व्योम)
अणु
	अचिन्हित दीर्घ flags;
	local_irq_save(flags);
	__vmcache_icसमाप्त();
	__vmcache_dcसमाप्त();
	__vmcache_l2समाप्त();
	local_irq_restore(flags);
	mb();
पूर्ण

व्योम copy_to_user_page(काष्ठा vm_area_काष्ठा *vma, काष्ठा page *page,
		       अचिन्हित दीर्घ vaddr, व्योम *dst, व्योम *src, पूर्णांक len)
अणु
	स_नकल(dst, src, len);
	अगर (vma->vm_flags & VM_EXEC) अणु
		flush_icache_range((अचिन्हित दीर्घ) dst,
		(अचिन्हित दीर्घ) dst + len);
	पूर्ण
पूर्ण
