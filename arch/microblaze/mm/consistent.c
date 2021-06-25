<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Microblaze support क्रम cache consistent memory.
 * Copyright (C) 2010 Michal Simek <monstr@monstr.eu>
 * Copyright (C) 2010 PetaLogix
 * Copyright (C) 2005 John Williams <jwilliams@itee.uq.edu.au>
 */

#समावेश <linux/kernel.h>
#समावेश <linux/माला.स>
#समावेश <linux/types.h>
#समावेश <linux/mm.h>
#समावेश <linux/init.h>
#समावेश <linux/dma-map-ops.h>
#समावेश <यंत्र/cpuinfo.h>
#समावेश <यंत्र/cacheflush.h>

व्योम arch_dma_prep_coherent(काष्ठा page *page, माप_प्रकार size)
अणु
	phys_addr_t paddr = page_to_phys(page);

	flush_dcache_range(paddr, paddr + size);
पूर्ण
