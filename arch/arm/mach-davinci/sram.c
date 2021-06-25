<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * mach-davinci/sram.c - DaVinci simple SRAM allocator
 *
 * Copyright (C) 2009 David Brownell
 */
#समावेश <linux/module.h>
#समावेश <linux/init.h>
#समावेश <linux/पन.स>
#समावेश <linux/genभाग.स>

#समावेश <mach/common.h>
#समावेश "sram.h"

अटल काष्ठा gen_pool *sram_pool;

काष्ठा gen_pool *sram_get_gen_pool(व्योम)
अणु
	वापस sram_pool;
पूर्ण

व्योम *sram_alloc(माप_प्रकार len, dma_addr_t *dma)
अणु
	dma_addr_t dma_base = davinci_soc_info.sram_dma;

	अगर (dma)
		*dma = 0;
	अगर (!sram_pool || (dma && !dma_base))
		वापस शून्य;

	वापस gen_pool_dma_alloc(sram_pool, len, dma);

पूर्ण
EXPORT_SYMBOL(sram_alloc);

व्योम sram_मुक्त(व्योम *addr, माप_प्रकार len)
अणु
	gen_pool_मुक्त(sram_pool, (अचिन्हित दीर्घ) addr, len);
पूर्ण
EXPORT_SYMBOL(sram_मुक्त);


/*
 * REVISIT This supports CPU and DMA access to/from SRAM, but it
 * करोesn't (yet?) support some other notable uses of SRAM:  as TCM
 * क्रम data and/or inकाष्ठाions; and holding code needed to enter
 * and निकास suspend states (जबतक DRAM can't be used).
 */
अटल पूर्णांक __init sram_init(व्योम)
अणु
	phys_addr_t phys = davinci_soc_info.sram_dma;
	अचिन्हित len = davinci_soc_info.sram_len;
	पूर्णांक status = 0;
	व्योम __iomem *addr;

	अगर (len) अणु
		len = min_t(अचिन्हित, len, SRAM_SIZE);
		sram_pool = gen_pool_create(ilog2(SRAM_GRANULARITY), -1);
		अगर (!sram_pool)
			status = -ENOMEM;
	पूर्ण

	अगर (sram_pool) अणु
		addr = ioremap(phys, len);
		अगर (!addr)
			वापस -ENOMEM;
		status = gen_pool_add_virt(sram_pool, (अचिन्हित दीर्घ) addr,
					   phys, len, -1);
		अगर (status < 0)
			iounmap(addr);
	पूर्ण

	WARN_ON(status < 0);
	वापस status;
पूर्ण
core_initcall(sram_init);

