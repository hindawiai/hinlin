<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * PGD allocation/मुक्तing
 *
 * Copyright (C) 2012 ARM Ltd.
 * Author: Catalin Marinas <catalin.marinas@arm.com>
 */

#समावेश <linux/mm.h>
#समावेश <linux/gfp.h>
#समावेश <linux/highस्मृति.स>
#समावेश <linux/slab.h>

#समावेश <यंत्र/pgभाग.स>
#समावेश <यंत्र/page.h>
#समावेश <यंत्र/tlbflush.h>

अटल काष्ठा kmem_cache *pgd_cache __ro_after_init;

pgd_t *pgd_alloc(काष्ठा mm_काष्ठा *mm)
अणु
	gfp_t gfp = GFP_PGTABLE_USER;

	अगर (PGD_SIZE == PAGE_SIZE)
		वापस (pgd_t *)__get_मुक्त_page(gfp);
	अन्यथा
		वापस kmem_cache_alloc(pgd_cache, gfp);
पूर्ण

व्योम pgd_मुक्त(काष्ठा mm_काष्ठा *mm, pgd_t *pgd)
अणु
	अगर (PGD_SIZE == PAGE_SIZE)
		मुक्त_page((अचिन्हित दीर्घ)pgd);
	अन्यथा
		kmem_cache_मुक्त(pgd_cache, pgd);
पूर्ण

व्योम __init pgtable_cache_init(व्योम)
अणु
	अगर (PGD_SIZE == PAGE_SIZE)
		वापस;

#अगर_घोषित CONFIG_ARM64_PA_BITS_52
	/*
	 * With 52-bit physical addresses, the architecture requires the
	 * top-level table to be aligned to at least 64 bytes.
	 */
	BUILD_BUG_ON(PGD_SIZE < 64);
#पूर्ण_अगर

	/*
	 * Naturally aligned pgds required by the architecture.
	 */
	pgd_cache = kmem_cache_create("pgd_cache", PGD_SIZE, PGD_SIZE,
				      SLAB_PANIC, शून्य);
पूर्ण
