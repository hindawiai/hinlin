<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * SGI IP30 miscellaneous setup bits.
 *
 * Copyright (C) 2004-2007 Stanislaw Skowronek <skylark@unaligned.org>
 *               2007 Joshua Kinard <kumba@gentoo.org>
 *               2009 Johannes Dickgreber <tanzy@gmx.de>
 */

#समावेश <linux/init.h>
#समावेश <linux/पन.स>
#समावेश <linux/kernel.h>
#समावेश <linux/types.h>
#समावेश <linux/percpu.h>
#समावेश <linux/memblock.h>

#समावेश <यंत्र/smp-ops.h>
#समावेश <यंत्र/sgialib.h>
#समावेश <यंत्र/समय.स>
#समावेश <यंत्र/sgi/heart.h>

#समावेश "ip30-common.h"

/* Structure of accessible HEART रेजिस्टरs located in XKPHYS space. */
काष्ठा ip30_heart_regs __iomem *heart_regs = HEART_XKPHYS_BASE;

/*
 * ARCS will report up to the first 1GB of
 * memory अगर queried.  Anything beyond that
 * is marked as reserved.
 */
#घोषणा IP30_MAX_PROM_MEMORY	_AC(0x40000000, UL)

/*
 * Memory in the Octane starts at 512MB
 */
#घोषणा IP30_MEMORY_BASE	_AC(0x20000000, UL)

/*
 * If using ARCS to probe क्रम memory, then
 * reमुख्यing memory will start at this offset.
 */
#घोषणा IP30_REAL_MEMORY_START  (IP30_MEMORY_BASE + IP30_MAX_PROM_MEMORY)

#घोषणा MEM_SHIFT(x) ((x) >> 20)

अटल व्योम __init ip30_mem_init(व्योम)
अणु
	अचिन्हित दीर्घ total_mem;
	phys_addr_t addr;
	phys_addr_t size;
	u32 memcfg;
	पूर्णांक i;

	total_mem = 0;
	क्रम (i = 0; i < HEART_MEMORY_BANKS; i++) अणु
		memcfg = __raw_पढ़ोl(&heart_regs->mem_cfg.l[i]);
		अगर (!(memcfg & HEART_MEMCFG_VALID))
			जारी;

		addr = memcfg & HEART_MEMCFG_ADDR_MASK;
		addr <<= HEART_MEMCFG_UNIT_SHIFT;
		addr += IP30_MEMORY_BASE;
		size = memcfg & HEART_MEMCFG_SIZE_MASK;
		size >>= HEART_MEMCFG_SIZE_SHIFT;
		size += 1;
		size <<= HEART_MEMCFG_UNIT_SHIFT;

		total_mem += size;

		अगर (addr >= IP30_REAL_MEMORY_START)
			memblock_मुक्त(addr, size);
		अन्यथा अगर ((addr + size) > IP30_REAL_MEMORY_START)
			memblock_मुक्त(IP30_REAL_MEMORY_START,
				     size - IP30_MAX_PROM_MEMORY);
	पूर्ण
	pr_info("Detected %luMB of physical memory.\n", MEM_SHIFT(total_mem));
पूर्ण

/**
 * ip30_cpu_समय_init - platक्रमm समय initialization.
 */
अटल व्योम __init ip30_cpu_समय_init(व्योम)
अणु
	पूर्णांक cpu = smp_processor_id();
	u64 heart_compare;
	अचिन्हित पूर्णांक start, end;
	पूर्णांक समय_dअगरf;

	heart_compare = (heart_पढ़ो(&heart_regs->count) +
			 (HEART_CYCLES_PER_SEC / 10));
	start = पढ़ो_c0_count();
	जबतक ((heart_पढ़ो(&heart_regs->count) - heart_compare) & 0x800000)
		cpu_relax();

	end = पढ़ो_c0_count();
	समय_dअगरf = (पूर्णांक)end - (पूर्णांक)start;
	mips_hpt_frequency = समय_dअगरf * 10;
	pr_info("IP30: CPU%d: %d MHz CPU detected.\n", cpu,
		(mips_hpt_frequency * 2) / 1000000);
पूर्ण

व्योम __init ip30_per_cpu_init(व्योम)
अणु
	/* Disable all पूर्णांकerrupts. */
	clear_c0_status(ST0_IM);

	ip30_cpu_समय_init();
#अगर_घोषित CONFIG_SMP
	ip30_install_ipi();
#पूर्ण_अगर

	enable_percpu_irq(IP30_HEART_L0_IRQ, IRQ_TYPE_NONE);
	enable_percpu_irq(IP30_HEART_L1_IRQ, IRQ_TYPE_NONE);
	enable_percpu_irq(IP30_HEART_L2_IRQ, IRQ_TYPE_NONE);
	enable_percpu_irq(IP30_HEART_ERR_IRQ, IRQ_TYPE_NONE);
पूर्ण

/**
 * plat_mem_setup - despite the name, misc setup happens here.
 */
व्योम __init plat_mem_setup(व्योम)
अणु
	ip30_mem_init();

	/* XXX: Hard lock on /sbin/init अगर this flag isn't specअगरied. */
	prom_flags |= PROM_FLAG_DONT_FREE_TEMP;

#अगर_घोषित CONFIG_SMP
	रेजिस्टर_smp_ops(&ip30_smp_ops);
#अन्यथा
	ip30_per_cpu_init();
#पूर्ण_अगर

	ioport_resource.start = 0;
	ioport_resource.end = ~0UL;
	set_io_port_base(IO_BASE);
पूर्ण
