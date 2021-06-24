<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (C) 2006 Chris Dearman (chris@mips.com),
 */
#समावेश <linux/init.h>
#समावेश <linux/kernel.h>
#समावेश <linux/sched.h>
#समावेश <linux/mm.h>

#समावेश <यंत्र/cpu-type.h>
#समावेश <यंत्र/mipsregs.h>
#समावेश <यंत्र/bcache.h>
#समावेश <यंत्र/cacheops.h>
#समावेश <यंत्र/page.h>
#समावेश <यंत्र/mmu_context.h>
#समावेश <यंत्र/r4kcache.h>
#समावेश <यंत्र/mips-cps.h>
#समावेश <यंत्र/bootinfo.h>

/*
 * MIPS32/MIPS64 L2 cache handling
 */

/*
 * Writeback and invalidate the secondary cache beक्रमe DMA.
 */
अटल व्योम mips_sc_wback_inv(अचिन्हित दीर्घ addr, अचिन्हित दीर्घ size)
अणु
	blast_scache_range(addr, addr + size);
पूर्ण

/*
 * Invalidate the secondary cache beक्रमe DMA.
 */
अटल व्योम mips_sc_inv(अचिन्हित दीर्घ addr, अचिन्हित दीर्घ size)
अणु
	अचिन्हित दीर्घ lsize = cpu_scache_line_size();
	अचिन्हित दीर्घ almask = ~(lsize - 1);

	cache_op(Hit_Writeback_Inv_SD, addr & almask);
	cache_op(Hit_Writeback_Inv_SD, (addr + size - 1) & almask);
	blast_inv_scache_range(addr, addr + size);
पूर्ण

अटल व्योम mips_sc_enable(व्योम)
अणु
	/* L2 cache is permanently enabled */
पूर्ण

अटल व्योम mips_sc_disable(व्योम)
अणु
	/* L2 cache is permanently enabled */
पूर्ण

अटल व्योम mips_sc_prefetch_enable(व्योम)
अणु
	अचिन्हित दीर्घ pftctl;

	अगर (mips_cm_revision() < CM_REV_CM2_5)
		वापस;

	/*
	 * If there is one or more L2 prefetch unit present then enable
	 * prefetching क्रम both code & data, क्रम all ports.
	 */
	pftctl = पढ़ो_gcr_l2_pft_control();
	अगर (pftctl & CM_GCR_L2_PFT_CONTROL_NPFT) अणु
		pftctl &= ~CM_GCR_L2_PFT_CONTROL_PAGEMASK;
		pftctl |= PAGE_MASK & CM_GCR_L2_PFT_CONTROL_PAGEMASK;
		pftctl |= CM_GCR_L2_PFT_CONTROL_PFTEN;
		ग_लिखो_gcr_l2_pft_control(pftctl);

		set_gcr_l2_pft_control_b(CM_GCR_L2_PFT_CONTROL_B_PORTID |
					 CM_GCR_L2_PFT_CONTROL_B_CEN);
	पूर्ण
पूर्ण

अटल व्योम mips_sc_prefetch_disable(व्योम)
अणु
	अगर (mips_cm_revision() < CM_REV_CM2_5)
		वापस;

	clear_gcr_l2_pft_control(CM_GCR_L2_PFT_CONTROL_PFTEN);
	clear_gcr_l2_pft_control_b(CM_GCR_L2_PFT_CONTROL_B_PORTID |
				   CM_GCR_L2_PFT_CONTROL_B_CEN);
पूर्ण

अटल bool mips_sc_prefetch_is_enabled(व्योम)
अणु
	अचिन्हित दीर्घ pftctl;

	अगर (mips_cm_revision() < CM_REV_CM2_5)
		वापस false;

	pftctl = पढ़ो_gcr_l2_pft_control();
	अगर (!(pftctl & CM_GCR_L2_PFT_CONTROL_NPFT))
		वापस false;
	वापस !!(pftctl & CM_GCR_L2_PFT_CONTROL_PFTEN);
पूर्ण

अटल काष्ठा bcache_ops mips_sc_ops = अणु
	.bc_enable = mips_sc_enable,
	.bc_disable = mips_sc_disable,
	.bc_wback_inv = mips_sc_wback_inv,
	.bc_inv = mips_sc_inv,
	.bc_prefetch_enable = mips_sc_prefetch_enable,
	.bc_prefetch_disable = mips_sc_prefetch_disable,
	.bc_prefetch_is_enabled = mips_sc_prefetch_is_enabled,
पूर्ण;

/*
 * Check अगर the L2 cache controller is activated on a particular platक्रमm.
 * MTI's L2 controller and the L2 cache controller of Broadcom's BMIPS
 * cores both use c0_config2's bit 12 as "L2 Bypass" bit, that is the
 * cache being disabled.  However there is no guarantee क्रम this to be
 * true on all platक्रमms.  In an act of stupidity the spec defined bits
 * 12..15 as implementation defined so below function will eventually have
 * to be replaced by a platक्रमm specअगरic probe.
 */
अटल अंतरभूत पूर्णांक mips_sc_is_activated(काष्ठा cpuinfo_mips *c)
अणु
	अचिन्हित पूर्णांक config2 = पढ़ो_c0_config2();
	अचिन्हित पूर्णांक पंचांगp;

	/* Check the bypass bit (L2B) */
	चयन (current_cpu_type()) अणु
	हाल CPU_34K:
	हाल CPU_74K:
	हाल CPU_1004K:
	हाल CPU_1074K:
	हाल CPU_INTERAPTIV:
	हाल CPU_PROAPTIV:
	हाल CPU_P5600:
	हाल CPU_BMIPS5000:
	हाल CPU_QEMU_GENERIC:
	हाल CPU_P6600:
		अगर (config2 & (1 << 12))
			वापस 0;
	पूर्ण

	पंचांगp = (config2 >> 4) & 0x0f;
	अगर (0 < पंचांगp && पंचांगp <= 7)
		c->scache.linesz = 2 << पंचांगp;
	अन्यथा
		वापस 0;
	वापस 1;
पूर्ण

अटल पूर्णांक mips_sc_probe_cm3(व्योम)
अणु
	काष्ठा cpuinfo_mips *c = &current_cpu_data;
	अचिन्हित दीर्घ cfg = पढ़ो_gcr_l2_config();
	अचिन्हित दीर्घ sets, line_sz, assoc;

	अगर (cfg & CM_GCR_L2_CONFIG_BYPASS)
		वापस 0;

	sets = cfg & CM_GCR_L2_CONFIG_SET_SIZE;
	sets >>= __ffs(CM_GCR_L2_CONFIG_SET_SIZE);
	अगर (sets)
		c->scache.sets = 64 << sets;

	line_sz = cfg & CM_GCR_L2_CONFIG_LINE_SIZE;
	line_sz >>= __ffs(CM_GCR_L2_CONFIG_LINE_SIZE);
	अगर (line_sz)
		c->scache.linesz = 2 << line_sz;

	assoc = cfg & CM_GCR_L2_CONFIG_ASSOC;
	assoc >>= __ffs(CM_GCR_L2_CONFIG_ASSOC);
	c->scache.ways = assoc + 1;
	c->scache.waysize = c->scache.sets * c->scache.linesz;
	c->scache.waybit = __ffs(c->scache.waysize);

	अगर (c->scache.linesz) अणु
		c->scache.flags &= ~MIPS_CACHE_NOT_PRESENT;
		c->options |= MIPS_CPU_INCLUSIVE_CACHES;
		वापस 1;
	पूर्ण

	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक mips_sc_probe(व्योम)
अणु
	काष्ठा cpuinfo_mips *c = &current_cpu_data;
	अचिन्हित पूर्णांक config1, config2;
	अचिन्हित पूर्णांक पंचांगp;

	/* Mark as not present until probe completed */
	c->scache.flags |= MIPS_CACHE_NOT_PRESENT;

	अगर (mips_cm_revision() >= CM_REV_CM3)
		वापस mips_sc_probe_cm3();

	/* Ignore anything but MIPSxx processors */
	अगर (!(c->isa_level & (MIPS_CPU_ISA_M32R1 | MIPS_CPU_ISA_M64R1 |
			      MIPS_CPU_ISA_M32R2 | MIPS_CPU_ISA_M64R2 |
			      MIPS_CPU_ISA_M32R5 | MIPS_CPU_ISA_M64R5 |
			      MIPS_CPU_ISA_M32R6 | MIPS_CPU_ISA_M64R6)))
		वापस 0;

	/* Does this MIPS32/MIPS64 CPU have a config2 रेजिस्टर? */
	config1 = पढ़ो_c0_config1();
	अगर (!(config1 & MIPS_CONF_M))
		वापस 0;

	config2 = पढ़ो_c0_config2();

	अगर (!mips_sc_is_activated(c))
		वापस 0;

	पंचांगp = (config2 >> 8) & 0x0f;
	अगर (पंचांगp <= 7)
		c->scache.sets = 64 << पंचांगp;
	अन्यथा
		वापस 0;

	पंचांगp = (config2 >> 0) & 0x0f;
	अगर (पंचांगp <= 7)
		c->scache.ways = पंचांगp + 1;
	अन्यथा
		वापस 0;

	अगर (current_cpu_type() == CPU_XBURST) अणु
		चयन (mips_machtype) अणु
		/*
		 * According to config2 it would be 5-ways, but that is
		 * contradicted by all करोcumentation.
		 */
		हाल MACH_INGENIC_JZ4770:
		हाल MACH_INGENIC_JZ4775:
			c->scache.ways = 4;
			अवरोध;

		/*
		 * According to config2 it would be 5-ways and 512-sets,
		 * but that is contradicted by all करोcumentation.
		 */
		हाल MACH_INGENIC_X1000:
		हाल MACH_INGENIC_X1000E:
			c->scache.sets = 256;
			c->scache.ways = 4;
			अवरोध;
		पूर्ण
	पूर्ण

	c->scache.waysize = c->scache.sets * c->scache.linesz;
	c->scache.waybit = __ffs(c->scache.waysize);

	c->scache.flags &= ~MIPS_CACHE_NOT_PRESENT;

	वापस 1;
पूर्ण

पूर्णांक mips_sc_init(व्योम)
अणु
	पूर्णांक found = mips_sc_probe();
	अगर (found) अणु
		mips_sc_enable();
		mips_sc_prefetch_enable();
		bcops = &mips_sc_ops;
	पूर्ण
	वापस found;
पूर्ण
