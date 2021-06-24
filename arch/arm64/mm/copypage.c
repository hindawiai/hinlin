<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Based on arch/arm/mm/copypage.c
 *
 * Copyright (C) 2002 Deep Blue Solutions Ltd, All Rights Reserved.
 * Copyright (C) 2012 ARM Ltd.
 */

#समावेश <linux/bitops.h>
#समावेश <linux/mm.h>

#समावेश <यंत्र/page.h>
#समावेश <यंत्र/cacheflush.h>
#समावेश <यंत्र/cpufeature.h>
#समावेश <यंत्र/mte.h>

व्योम copy_highpage(काष्ठा page *to, काष्ठा page *from)
अणु
	काष्ठा page *kto = page_address(to);
	काष्ठा page *kfrom = page_address(from);

	copy_page(kto, kfrom);

	अगर (प्रणाली_supports_mte() && test_bit(PG_mte_tagged, &from->flags)) अणु
		set_bit(PG_mte_tagged, &to->flags);
		page_kasan_tag_reset(to);
		/*
		 * We need smp_wmb() in between setting the flags and clearing the
		 * tags because अगर another thपढ़ो पढ़ोs page->flags and builds a
		 * tagged address out of it, there is an actual dependency to the
		 * memory access, but on the current thपढ़ो we करो not guarantee that
		 * the new page->flags are visible beक्रमe the tags were updated.
		 */
		smp_wmb();
		mte_copy_page_tags(kto, kfrom);
	पूर्ण
पूर्ण
EXPORT_SYMBOL(copy_highpage);

व्योम copy_user_highpage(काष्ठा page *to, काष्ठा page *from,
			अचिन्हित दीर्घ vaddr, काष्ठा vm_area_काष्ठा *vma)
अणु
	copy_highpage(to, from);
	flush_dcache_page(to);
पूर्ण
EXPORT_SYMBOL_GPL(copy_user_highpage);
