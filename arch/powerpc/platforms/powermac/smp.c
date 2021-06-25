<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * SMP support क्रम घातer macपूर्णांकosh.
 *
 * We support both the old "powersurge" SMP architecture
 * and the current Core99 (G4 PowerMac) machines.
 *
 * Note that we करोn't support the very first rev. of
 * Apple/DayStar 2 CPUs board, the one with the funky
 * watchकरोg. Hopefully, none of these should be there except
 * maybe पूर्णांकernally to Apple. I should probably still add some
 * code to detect this card though and disable SMP. --BenH.
 *
 * Support Macपूर्णांकosh G4 SMP by Troy Benjegerdes (hozer@drgw.net)
 * and Ben Herrenschmidt <benh@kernel.crashing.org>.
 *
 * Support क्रम DayStar quad CPU cards
 * Copyright (C) XLR8, Inc. 1994-2000
 */
#समावेश <linux/kernel.h>
#समावेश <linux/sched.h>
#समावेश <linux/sched/hotplug.h>
#समावेश <linux/smp.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/kernel_स्थिति.स>
#समावेश <linux/delay.h>
#समावेश <linux/init.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/hardirq.h>
#समावेश <linux/cpu.h>
#समावेश <linux/compiler.h>
#समावेश <linux/pgtable.h>

#समावेश <यंत्र/ptrace.h>
#समावेश <linux/atomic.h>
#समावेश <यंत्र/code-patching.h>
#समावेश <यंत्र/irq.h>
#समावेश <यंत्र/page.h>
#समावेश <यंत्र/sections.h>
#समावेश <यंत्र/पन.स>
#समावेश <यंत्र/prom.h>
#समावेश <यंत्र/smp.h>
#समावेश <यंत्र/machdep.h>
#समावेश <यंत्र/pmac_feature.h>
#समावेश <यंत्र/समय.स>
#समावेश <यंत्र/mpic.h>
#समावेश <यंत्र/cacheflush.h>
#समावेश <यंत्र/keylargo.h>
#समावेश <यंत्र/pmac_low_i2c.h>
#समावेश <यंत्र/pmac_pfunc.h>
#समावेश <यंत्र/inst.h>

#समावेश "pmac.h"

#अघोषित DEBUG

#अगर_घोषित DEBUG
#घोषणा DBG(fmt...) udbg_म_लिखो(fmt)
#अन्यथा
#घोषणा DBG(fmt...)
#पूर्ण_अगर

बाह्य व्योम __secondary_start_pmac_0(व्योम);

अटल व्योम (*pmac_tb_मुक्तze)(पूर्णांक मुक्तze);
अटल u64 समयbase;
अटल पूर्णांक tb_req;

#अगर_घोषित CONFIG_PPC_PMAC32_PSURGE

/*
 * Powersurge (old घातermac SMP) support.
 */

/* Addresses क्रम घातersurge रेजिस्टरs */
#घोषणा HAMMERHEAD_BASE		0xf8000000
#घोषणा HHEAD_CONFIG		0x90
#घोषणा HHEAD_SEC_INTR		0xc0

/* रेजिस्टर क्रम पूर्णांकerrupting the primary processor on the घातersurge */
/* N.B. this is actually the ethernet ROM! */
#घोषणा PSURGE_PRI_INTR		0xf3019000

/* रेजिस्टर क्रम storing the start address क्रम the secondary processor */
/* N.B. this is the PCI config space address रेजिस्टर क्रम the 1st bridge */
#घोषणा PSURGE_START		0xf2800000

/* Daystar/XLR8 4-CPU card */
#घोषणा PSURGE_QUAD_REG_ADDR	0xf8800000

#घोषणा PSURGE_QUAD_IRQ_SET	0
#घोषणा PSURGE_QUAD_IRQ_CLR	1
#घोषणा PSURGE_QUAD_IRQ_PRIMARY	2
#घोषणा PSURGE_QUAD_CKSTOP_CTL	3
#घोषणा PSURGE_QUAD_PRIMARY_ARB	4
#घोषणा PSURGE_QUAD_BOARD_ID	6
#घोषणा PSURGE_QUAD_WHICH_CPU	7
#घोषणा PSURGE_QUAD_CKSTOP_RDBK	8
#घोषणा PSURGE_QUAD_RESET_CTL	11

#घोषणा PSURGE_QUAD_OUT(r, v)	(out_8(quad_base + ((r) << 4) + 4, (v)))
#घोषणा PSURGE_QUAD_IN(r)	(in_8(quad_base + ((r) << 4) + 4) & 0x0f)
#घोषणा PSURGE_QUAD_BIS(r, v)	(PSURGE_QUAD_OUT((r), PSURGE_QUAD_IN(r) | (v)))
#घोषणा PSURGE_QUAD_BIC(r, v)	(PSURGE_QUAD_OUT((r), PSURGE_QUAD_IN(r) & ~(v)))

/* भव addresses क्रम the above */
अटल अस्थिर u8 __iomem *hhead_base;
अटल अस्थिर u8 __iomem *quad_base;
अटल अस्थिर u32 __iomem *psurge_pri_पूर्णांकr;
अटल अस्थिर u8 __iomem *psurge_sec_पूर्णांकr;
अटल अस्थिर u32 __iomem *psurge_start;

/* values क्रम psurge_type */
#घोषणा PSURGE_NONE		-1
#घोषणा PSURGE_DUAL		0
#घोषणा PSURGE_QUAD_OKEE	1
#घोषणा PSURGE_QUAD_COTTON	2
#घोषणा PSURGE_QUAD_ICEGRASS	3

/* what sort of घातersurge board we have */
अटल पूर्णांक psurge_type = PSURGE_NONE;

/* irq क्रम secondary cpus to report */
अटल काष्ठा irq_करोमुख्य *psurge_host;
पूर्णांक psurge_secondary_virq;

/*
 * Set and clear IPIs क्रम घातersurge.
 */
अटल अंतरभूत व्योम psurge_set_ipi(पूर्णांक cpu)
अणु
	अगर (psurge_type == PSURGE_NONE)
		वापस;
	अगर (cpu == 0)
		in_be32(psurge_pri_पूर्णांकr);
	अन्यथा अगर (psurge_type == PSURGE_DUAL)
		out_8(psurge_sec_पूर्णांकr, 0);
	अन्यथा
		PSURGE_QUAD_OUT(PSURGE_QUAD_IRQ_SET, 1 << cpu);
पूर्ण

अटल अंतरभूत व्योम psurge_clr_ipi(पूर्णांक cpu)
अणु
	अगर (cpu > 0) अणु
		चयन(psurge_type) अणु
		हाल PSURGE_DUAL:
			out_8(psurge_sec_पूर्णांकr, ~0);
		हाल PSURGE_NONE:
			अवरोध;
		शेष:
			PSURGE_QUAD_OUT(PSURGE_QUAD_IRQ_CLR, 1 << cpu);
		पूर्ण
	पूर्ण
पूर्ण

/*
 * On घातersurge (old SMP घातermac architecture) we करोn't have
 * separate IPIs क्रम separate messages like खोलोpic करोes.  Instead
 * use the generic demux helpers
 *  -- paulus.
 */
अटल irqवापस_t psurge_ipi_पूर्णांकr(पूर्णांक irq, व्योम *d)
अणु
	psurge_clr_ipi(smp_processor_id());
	smp_ipi_demux();

	वापस IRQ_HANDLED;
पूर्ण

अटल व्योम smp_psurge_cause_ipi(पूर्णांक cpu)
अणु
	psurge_set_ipi(cpu);
पूर्ण

अटल पूर्णांक psurge_host_map(काष्ठा irq_करोमुख्य *h, अचिन्हित पूर्णांक virq,
			 irq_hw_number_t hw)
अणु
	irq_set_chip_and_handler(virq, &dummy_irq_chip, handle_percpu_irq);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा irq_करोमुख्य_ops psurge_host_ops = अणु
	.map	= psurge_host_map,
पूर्ण;

अटल पूर्णांक psurge_secondary_ipi_init(व्योम)
अणु
	पूर्णांक rc = -ENOMEM;

	psurge_host = irq_करोमुख्य_add_nomap(शून्य, ~0, &psurge_host_ops, शून्य);

	अगर (psurge_host)
		psurge_secondary_virq = irq_create_direct_mapping(psurge_host);

	अगर (psurge_secondary_virq)
		rc = request_irq(psurge_secondary_virq, psurge_ipi_पूर्णांकr,
			IRQF_PERCPU | IRQF_NO_THREAD, "IPI", शून्य);

	अगर (rc)
		pr_err("Failed to setup secondary cpu IPI\n");

	वापस rc;
पूर्ण

/*
 * Determine a quad card presence. We पढ़ो the board ID रेजिस्टर, we
 * क्रमce the data bus to change to something अन्यथा, and we पढ़ो it again.
 * It it's stable, then the रेजिस्टर probably exist (ugh !)
 */
अटल पूर्णांक __init psurge_quad_probe(व्योम)
अणु
	पूर्णांक type;
	अचिन्हित पूर्णांक i;

	type = PSURGE_QUAD_IN(PSURGE_QUAD_BOARD_ID);
	अगर (type < PSURGE_QUAD_OKEE || type > PSURGE_QUAD_ICEGRASS
	    || type != PSURGE_QUAD_IN(PSURGE_QUAD_BOARD_ID))
		वापस PSURGE_DUAL;

	/* looks OK, try a slightly more rigorous test */
	/* bogus is not necessarily cacheline-aligned,
	   though I करोn't suppose that really matters.  -- paulus */
	क्रम (i = 0; i < 100; i++) अणु
		अस्थिर u32 bogus[8];
		bogus[(0+i)%8] = 0x00000000;
		bogus[(1+i)%8] = 0x55555555;
		bogus[(2+i)%8] = 0xFFFFFFFF;
		bogus[(3+i)%8] = 0xAAAAAAAA;
		bogus[(4+i)%8] = 0x33333333;
		bogus[(5+i)%8] = 0xCCCCCCCC;
		bogus[(6+i)%8] = 0xCCCCCCCC;
		bogus[(7+i)%8] = 0x33333333;
		wmb();
		यंत्र अस्थिर("dcbf 0,%0" : : "r" (bogus) : "memory");
		mb();
		अगर (type != PSURGE_QUAD_IN(PSURGE_QUAD_BOARD_ID))
			वापस PSURGE_DUAL;
	पूर्ण
	वापस type;
पूर्ण

अटल व्योम __init psurge_quad_init(व्योम)
अणु
	पूर्णांक procbits;

	अगर (ppc_md.progress) ppc_md.progress("psurge_quad_init", 0x351);
	procbits = ~PSURGE_QUAD_IN(PSURGE_QUAD_WHICH_CPU);
	अगर (psurge_type == PSURGE_QUAD_ICEGRASS)
		PSURGE_QUAD_BIS(PSURGE_QUAD_RESET_CTL, procbits);
	अन्यथा
		PSURGE_QUAD_BIC(PSURGE_QUAD_CKSTOP_CTL, procbits);
	mdelay(33);
	out_8(psurge_sec_पूर्णांकr, ~0);
	PSURGE_QUAD_OUT(PSURGE_QUAD_IRQ_CLR, procbits);
	PSURGE_QUAD_BIS(PSURGE_QUAD_RESET_CTL, procbits);
	अगर (psurge_type != PSURGE_QUAD_ICEGRASS)
		PSURGE_QUAD_BIS(PSURGE_QUAD_CKSTOP_CTL, procbits);
	PSURGE_QUAD_BIC(PSURGE_QUAD_PRIMARY_ARB, procbits);
	mdelay(33);
	PSURGE_QUAD_BIC(PSURGE_QUAD_RESET_CTL, procbits);
	mdelay(33);
	PSURGE_QUAD_BIS(PSURGE_QUAD_PRIMARY_ARB, procbits);
	mdelay(33);
पूर्ण

अटल व्योम __init smp_psurge_probe(व्योम)
अणु
	पूर्णांक i, ncpus;
	काष्ठा device_node *dn;

	/*
	 * The घातersurge cpu board can be used in the generation
	 * of घातermacs that have a socket क्रम an upgradeable cpu card,
	 * including the 7500, 8500, 9500, 9600.
	 * The device tree करोesn't tell you अगर you have 2 cpus because
	 * OF करोesn't know anything about the 2nd processor.
	 * Instead we look क्रम magic bits in magic रेजिस्टरs,
	 * in the hammerhead memory controller in the हाल of the
	 * dual-cpu घातersurge board.  -- paulus.
	 */
	dn = of_find_node_by_name(शून्य, "hammerhead");
	अगर (dn == शून्य)
		वापस;
	of_node_put(dn);

	hhead_base = ioremap(HAMMERHEAD_BASE, 0x800);
	quad_base = ioremap(PSURGE_QUAD_REG_ADDR, 1024);
	psurge_sec_पूर्णांकr = hhead_base + HHEAD_SEC_INTR;

	psurge_type = psurge_quad_probe();
	अगर (psurge_type != PSURGE_DUAL) अणु
		psurge_quad_init();
		/* All released cards using this HW design have 4 CPUs */
		ncpus = 4;
		/* No sure how समयbase sync works on those, let's use SW */
		smp_ops->give_समयbase = smp_generic_give_समयbase;
		smp_ops->take_समयbase = smp_generic_take_समयbase;
	पूर्ण अन्यथा अणु
		iounmap(quad_base);
		अगर ((in_8(hhead_base + HHEAD_CONFIG) & 0x02) == 0) अणु
			/* not a dual-cpu card */
			iounmap(hhead_base);
			psurge_type = PSURGE_NONE;
			वापस;
		पूर्ण
		ncpus = 2;
	पूर्ण

	अगर (psurge_secondary_ipi_init())
		वापस;

	psurge_start = ioremap(PSURGE_START, 4);
	psurge_pri_पूर्णांकr = ioremap(PSURGE_PRI_INTR, 4);

	/* This is necessary because OF करोesn't know about the
	 * secondary cpu(s), and thus there aren't nodes in the
	 * device tree क्रम them, and smp_setup_cpu_maps hasn't
	 * set their bits in cpu_present_mask.
	 */
	अगर (ncpus > NR_CPUS)
		ncpus = NR_CPUS;
	क्रम (i = 1; i < ncpus ; ++i)
		set_cpu_present(i, true);

	अगर (ppc_md.progress) ppc_md.progress("smp_psurge_probe - done", 0x352);
पूर्ण

अटल पूर्णांक __init smp_psurge_kick_cpu(पूर्णांक nr)
अणु
	अचिन्हित दीर्घ start = __pa(__secondary_start_pmac_0) + nr * 8;
	अचिन्हित दीर्घ a, flags;
	पूर्णांक i, j;

	/* Defining this here is evil ... but I prefer hiding that
	 * crap to aव्योम giving people ideas that they can करो the
	 * same.
	 */
	बाह्य अस्थिर अचिन्हित पूर्णांक cpu_callin_map[NR_CPUS];

	/* may need to flush here अगर secondary bats aren't setup */
	क्रम (a = KERNELBASE; a < KERNELBASE + 0x800000; a += 32)
		यंत्र अस्थिर("dcbf 0,%0" : : "r" (a) : "memory");
	यंत्र अस्थिर("sync");

	अगर (ppc_md.progress) ppc_md.progress("smp_psurge_kick_cpu", 0x353);

	/* This is going to मुक्तze the समयebase, we disable पूर्णांकerrupts */
	local_irq_save(flags);

	out_be32(psurge_start, start);
	mb();

	psurge_set_ipi(nr);

	/*
	 * We can't use udelay here because the समयbase is now frozen.
	 */
	क्रम (i = 0; i < 2000; ++i)
		यंत्र अस्थिर("nop" : : : "memory");
	psurge_clr_ipi(nr);

	/*
	 * Also, because the समयbase is frozen, we must not वापस to the
	 * caller which will try to करो udelay's etc... Instead, we रुको -here-
	 * क्रम the CPU to callin.
	 */
	क्रम (i = 0; i < 100000 && !cpu_callin_map[nr]; ++i) अणु
		क्रम (j = 1; j < 10000; j++)
			यंत्र अस्थिर("nop" : : : "memory");
		यंत्र अस्थिर("sync" : : : "memory");
	पूर्ण
	अगर (!cpu_callin_map[nr])
		जाओ stuck;

	/* And we करो the TB sync here too क्रम standard dual CPU cards */
	अगर (psurge_type == PSURGE_DUAL) अणु
		जबतक(!tb_req)
			barrier();
		tb_req = 0;
		mb();
		समयbase = get_tb();
		mb();
		जबतक (समयbase)
			barrier();
		mb();
	पूर्ण
 stuck:
	/* now पूर्णांकerrupt the secondary, restarting both TBs */
	अगर (psurge_type == PSURGE_DUAL)
		psurge_set_ipi(1);

	अगर (ppc_md.progress) ppc_md.progress("smp_psurge_kick_cpu - done", 0x354);

	वापस 0;
पूर्ण

अटल व्योम __init smp_psurge_setup_cpu(पूर्णांक cpu_nr)
अणु
	अचिन्हित दीर्घ flags = IRQF_PERCPU | IRQF_NO_THREAD;
	पूर्णांक irq;

	अगर (cpu_nr != 0 || !psurge_start)
		वापस;

	/* reset the entry poपूर्णांक so अगर we get another पूर्णांकr we won't
	 * try to startup again */
	out_be32(psurge_start, 0x100);
	irq = irq_create_mapping(शून्य, 30);
	अगर (request_irq(irq, psurge_ipi_पूर्णांकr, flags, "primary IPI", शून्य))
		prपूर्णांकk(KERN_ERR "Couldn't get primary IPI interrupt");
पूर्ण

व्योम __init smp_psurge_take_समयbase(व्योम)
अणु
	अगर (psurge_type != PSURGE_DUAL)
		वापस;

	tb_req = 1;
	mb();
	जबतक (!समयbase)
		barrier();
	mb();
	set_tb(समयbase >> 32, समयbase & 0xffffffff);
	समयbase = 0;
	mb();
	set_dec(tb_ticks_per_jअगरfy/2);
पूर्ण

व्योम __init smp_psurge_give_समयbase(व्योम)
अणु
	/* Nothing to करो here */
पूर्ण

/* PowerSurge-style Macs */
काष्ठा smp_ops_t psurge_smp_ops = अणु
	.message_pass	= शून्य,	/* Use smp_muxed_ipi_message_pass */
	.cause_ipi	= smp_psurge_cause_ipi,
	.cause_nmi_ipi	= शून्य,
	.probe		= smp_psurge_probe,
	.kick_cpu	= smp_psurge_kick_cpu,
	.setup_cpu	= smp_psurge_setup_cpu,
	.give_समयbase	= smp_psurge_give_समयbase,
	.take_समयbase	= smp_psurge_take_समयbase,
पूर्ण;
#पूर्ण_अगर /* CONFIG_PPC_PMAC32_PSURGE */

/*
 * Core 99 and later support
 */


अटल व्योम smp_core99_give_समयbase(व्योम)
अणु
	अचिन्हित दीर्घ flags;

	local_irq_save(flags);

	जबतक(!tb_req)
		barrier();
	tb_req = 0;
	(*pmac_tb_मुक्तze)(1);
	mb();
	समयbase = get_tb();
	mb();
	जबतक (समयbase)
		barrier();
	mb();
	(*pmac_tb_मुक्तze)(0);
	mb();

	local_irq_restore(flags);
पूर्ण


अटल व्योम smp_core99_take_समयbase(व्योम)
अणु
	अचिन्हित दीर्घ flags;

	local_irq_save(flags);

	tb_req = 1;
	mb();
	जबतक (!समयbase)
		barrier();
	mb();
	set_tb(समयbase >> 32, समयbase & 0xffffffff);
	समयbase = 0;
	mb();

	local_irq_restore(flags);
पूर्ण

#अगर_घोषित CONFIG_PPC64
/*
 * G5s enable/disable the समयbase via an i2c-connected घड़ी chip.
 */
अटल काष्ठा pmac_i2c_bus *pmac_tb_घड़ी_chip_host;
अटल u8 pmac_tb_pulsar_addr;

अटल व्योम smp_core99_cypress_tb_मुक्तze(पूर्णांक मुक्तze)
अणु
	u8 data;
	पूर्णांक rc;

	/* Strangely, the device-tree says address is 0xd2, but darwin
	 * accesses 0xd0 ...
	 */
	pmac_i2c_seपंचांगode(pmac_tb_घड़ी_chip_host,
			 pmac_i2c_mode_combined);
	rc = pmac_i2c_xfer(pmac_tb_घड़ी_chip_host,
			   0xd0 | pmac_i2c_पढ़ो,
			   1, 0x81, &data, 1);
	अगर (rc != 0)
		जाओ bail;

	data = (data & 0xf3) | (मुक्तze ? 0x00 : 0x0c);

       	pmac_i2c_seपंचांगode(pmac_tb_घड़ी_chip_host, pmac_i2c_mode_stdsub);
	rc = pmac_i2c_xfer(pmac_tb_घड़ी_chip_host,
			   0xd0 | pmac_i2c_ग_लिखो,
			   1, 0x81, &data, 1);

 bail:
	अगर (rc != 0) अणु
		prपूर्णांकk("Cypress Timebase %s rc: %d\n",
		       मुक्तze ? "freeze" : "unfreeze", rc);
		panic("Timebase freeze failed !\n");
	पूर्ण
पूर्ण


अटल व्योम smp_core99_pulsar_tb_मुक्तze(पूर्णांक मुक्तze)
अणु
	u8 data;
	पूर्णांक rc;

	pmac_i2c_seपंचांगode(pmac_tb_घड़ी_chip_host,
			 pmac_i2c_mode_combined);
	rc = pmac_i2c_xfer(pmac_tb_घड़ी_chip_host,
			   pmac_tb_pulsar_addr | pmac_i2c_पढ़ो,
			   1, 0x2e, &data, 1);
	अगर (rc != 0)
		जाओ bail;

	data = (data & 0x88) | (मुक्तze ? 0x11 : 0x22);

	pmac_i2c_seपंचांगode(pmac_tb_घड़ी_chip_host, pmac_i2c_mode_stdsub);
	rc = pmac_i2c_xfer(pmac_tb_घड़ी_chip_host,
			   pmac_tb_pulsar_addr | pmac_i2c_ग_लिखो,
			   1, 0x2e, &data, 1);
 bail:
	अगर (rc != 0) अणु
		prपूर्णांकk(KERN_ERR "Pulsar Timebase %s rc: %d\n",
		       मुक्तze ? "freeze" : "unfreeze", rc);
		panic("Timebase freeze failed !\n");
	पूर्ण
पूर्ण

अटल व्योम __init smp_core99_setup_i2c_hwsync(पूर्णांक ncpus)
अणु
	काष्ठा device_node *cc = शून्य;	
	काष्ठा device_node *p;
	स्थिर अक्षर *name = शून्य;
	स्थिर u32 *reg;
	पूर्णांक ok;

	/* Look क्रम the घड़ी chip */
	क्रम_each_node_by_name(cc, "i2c-hwclock") अणु
		p = of_get_parent(cc);
		ok = p && of_device_is_compatible(p, "uni-n-i2c");
		of_node_put(p);
		अगर (!ok)
			जारी;

		pmac_tb_घड़ी_chip_host = pmac_i2c_find_bus(cc);
		अगर (pmac_tb_घड़ी_chip_host == शून्य)
			जारी;
		reg = of_get_property(cc, "reg", शून्य);
		अगर (reg == शून्य)
			जारी;
		चयन (*reg) अणु
		हाल 0xd2:
			अगर (of_device_is_compatible(cc,"pulsar-legacy-slewing")) अणु
				pmac_tb_मुक्तze = smp_core99_pulsar_tb_मुक्तze;
				pmac_tb_pulsar_addr = 0xd2;
				name = "Pulsar";
			पूर्ण अन्यथा अगर (of_device_is_compatible(cc, "cy28508")) अणु
				pmac_tb_मुक्तze = smp_core99_cypress_tb_मुक्तze;
				name = "Cypress";
			पूर्ण
			अवरोध;
		हाल 0xd4:
			pmac_tb_मुक्तze = smp_core99_pulsar_tb_मुक्तze;
			pmac_tb_pulsar_addr = 0xd4;
			name = "Pulsar";
			अवरोध;
		पूर्ण
		अगर (pmac_tb_मुक्तze != शून्य)
			अवरोध;
	पूर्ण
	अगर (pmac_tb_मुक्तze != शून्य) अणु
		/* Open i2c bus क्रम synchronous access */
		अगर (pmac_i2c_खोलो(pmac_tb_घड़ी_chip_host, 1)) अणु
			prपूर्णांकk(KERN_ERR "Failed top open i2c bus for clock"
			       " sync, fallback to software sync !\n");
			जाओ no_i2c_sync;
		पूर्ण
		prपूर्णांकk(KERN_INFO "Processor timebase sync using %s i2c clock\n",
		       name);
		वापस;
	पूर्ण
 no_i2c_sync:
	pmac_tb_मुक्तze = शून्य;
	pmac_tb_घड़ी_chip_host = शून्य;
पूर्ण



/*
 * Newer G5s uses a platक्रमm function
 */

अटल व्योम smp_core99_pfunc_tb_मुक्तze(पूर्णांक मुक्तze)
अणु
	काष्ठा device_node *cpus;
	काष्ठा pmf_args args;

	cpus = of_find_node_by_path("/cpus");
	BUG_ON(cpus == शून्य);
	args.count = 1;
	args.u[0].v = !मुक्तze;
	pmf_call_function(cpus, "cpu-timebase", &args);
	of_node_put(cpus);
पूर्ण

#अन्यथा /* CONFIG_PPC64 */

/*
 * SMP G4 use a GPIO to enable/disable the समयbase.
 */

अटल अचिन्हित पूर्णांक core99_tb_gpio;	/* Timebase मुक्तze GPIO */

अटल व्योम smp_core99_gpio_tb_मुक्तze(पूर्णांक मुक्तze)
अणु
	अगर (मुक्तze)
		pmac_call_feature(PMAC_FTR_WRITE_GPIO, शून्य, core99_tb_gpio, 4);
	अन्यथा
		pmac_call_feature(PMAC_FTR_WRITE_GPIO, शून्य, core99_tb_gpio, 0);
	pmac_call_feature(PMAC_FTR_READ_GPIO, शून्य, core99_tb_gpio, 0);
पूर्ण


#पूर्ण_अगर /* !CONFIG_PPC64 */

अटल व्योम core99_init_caches(पूर्णांक cpu)
अणु
#अगर_अघोषित CONFIG_PPC64
	/* L2 and L3 cache settings to pass from CPU0 to CPU1 on G4 cpus */
	अटल दीर्घ पूर्णांक core99_l2_cache;
	अटल दीर्घ पूर्णांक core99_l3_cache;

	अगर (!cpu_has_feature(CPU_FTR_L2CR))
		वापस;

	अगर (cpu == 0) अणु
		core99_l2_cache = _get_L2CR();
		prपूर्णांकk("CPU0: L2CR is %lx\n", core99_l2_cache);
	पूर्ण अन्यथा अणु
		prपूर्णांकk("CPU%d: L2CR was %lx\n", cpu, _get_L2CR());
		_set_L2CR(0);
		_set_L2CR(core99_l2_cache);
		prपूर्णांकk("CPU%d: L2CR set to %lx\n", cpu, core99_l2_cache);
	पूर्ण

	अगर (!cpu_has_feature(CPU_FTR_L3CR))
		वापस;

	अगर (cpu == 0)अणु
		core99_l3_cache = _get_L3CR();
		prपूर्णांकk("CPU0: L3CR is %lx\n", core99_l3_cache);
	पूर्ण अन्यथा अणु
		prपूर्णांकk("CPU%d: L3CR was %lx\n", cpu, _get_L3CR());
		_set_L3CR(0);
		_set_L3CR(core99_l3_cache);
		prपूर्णांकk("CPU%d: L3CR set to %lx\n", cpu, core99_l3_cache);
	पूर्ण
#पूर्ण_अगर /* !CONFIG_PPC64 */
पूर्ण

अटल व्योम __init smp_core99_setup(पूर्णांक ncpus)
अणु
#अगर_घोषित CONFIG_PPC64

	/* i2c based HW sync on some G5s */
	अगर (of_machine_is_compatible("PowerMac7,2") ||
	    of_machine_is_compatible("PowerMac7,3") ||
	    of_machine_is_compatible("RackMac3,1"))
		smp_core99_setup_i2c_hwsync(ncpus);

	/* pfunc based HW sync on recent G5s */
	अगर (pmac_tb_मुक्तze == शून्य) अणु
		काष्ठा device_node *cpus =
			of_find_node_by_path("/cpus");
		अगर (cpus &&
		    of_get_property(cpus, "platform-cpu-timebase", शून्य)) अणु
			pmac_tb_मुक्तze = smp_core99_pfunc_tb_मुक्तze;
			prपूर्णांकk(KERN_INFO "Processor timebase sync using"
			       " platform function\n");
		पूर्ण
	पूर्ण

#अन्यथा /* CONFIG_PPC64 */

	/* GPIO based HW sync on ppc32 Core99 */
	अगर (pmac_tb_मुक्तze == शून्य && !of_machine_is_compatible("MacRISC4")) अणु
		काष्ठा device_node *cpu;
		स्थिर u32 *tbprop = शून्य;

		core99_tb_gpio = KL_GPIO_TB_ENABLE;	/* शेष value */
		cpu = of_find_node_by_type(शून्य, "cpu");
		अगर (cpu != शून्य) अणु
			tbprop = of_get_property(cpu, "timebase-enable", शून्य);
			अगर (tbprop)
				core99_tb_gpio = *tbprop;
			of_node_put(cpu);
		पूर्ण
		pmac_tb_मुक्तze = smp_core99_gpio_tb_मुक्तze;
		prपूर्णांकk(KERN_INFO "Processor timebase sync using"
		       " GPIO 0x%02x\n", core99_tb_gpio);
	पूर्ण

#पूर्ण_अगर /* CONFIG_PPC64 */

	/* No समयbase sync, fallback to software */
	अगर (pmac_tb_मुक्तze == शून्य) अणु
		smp_ops->give_समयbase = smp_generic_give_समयbase;
		smp_ops->take_समयbase = smp_generic_take_समयbase;
		prपूर्णांकk(KERN_INFO "Processor timebase sync using software\n");
	पूर्ण

#अगर_अघोषित CONFIG_PPC64
	अणु
		पूर्णांक i;

		/* XXX should get this from reg properties */
		क्रम (i = 1; i < ncpus; ++i)
			set_hard_smp_processor_id(i, i);
	पूर्ण
#पूर्ण_अगर

	/* 32 bits SMP can't NAP */
	अगर (!of_machine_is_compatible("MacRISC4"))
		घातersave_nap = 0;
पूर्ण

अटल व्योम __init smp_core99_probe(व्योम)
अणु
	काष्ठा device_node *cpus;
	पूर्णांक ncpus = 0;

	अगर (ppc_md.progress) ppc_md.progress("smp_core99_probe", 0x345);

	/* Count CPUs in the device-tree */
	क्रम_each_node_by_type(cpus, "cpu")
		++ncpus;

	prपूर्णांकk(KERN_INFO "PowerMac SMP probe found %d cpus\n", ncpus);

	/* Nothing more to करो अगर less than 2 of them */
	अगर (ncpus <= 1)
		वापस;

	/* We need to perक्रमm some early initialisations beक्रमe we can start
	 * setting up SMP as we are running beक्रमe initcalls
	 */
	pmac_pfunc_base_install();
	pmac_i2c_init();

	/* Setup various bits like समयbase sync method, ability to nap, ... */
	smp_core99_setup(ncpus);

	/* Install IPIs */
	mpic_request_ipis();

	/* Collect l2cr and l3cr values from CPU 0 */
	core99_init_caches(0);
पूर्ण

अटल पूर्णांक smp_core99_kick_cpu(पूर्णांक nr)
अणु
	अचिन्हित पूर्णांक save_vector;
	अचिन्हित दीर्घ target, flags;
	अचिन्हित पूर्णांक *vector = (अचिन्हित पूर्णांक *)(PAGE_OFFSET+0x100);

	अगर (nr < 0 || nr > 3)
		वापस -ENOENT;

	अगर (ppc_md.progress)
		ppc_md.progress("smp_core99_kick_cpu", 0x346);

	local_irq_save(flags);

	/* Save reset vector */
	save_vector = *vector;

	/* Setup fake reset vector that करोes
	 *   b __secondary_start_pmac_0 + nr*8
	 */
	target = (अचिन्हित दीर्घ) __secondary_start_pmac_0 + nr * 8;
	patch_branch((काष्ठा ppc_inst *)vector, target, BRANCH_SET_LINK);

	/* Put some lअगरe in our मित्र */
	pmac_call_feature(PMAC_FTR_RESET_CPU, शून्य, nr, 0);

	/* FIXME: We रुको a bit क्रम the CPU to take the exception, I should
	 * instead रुको क्रम the entry code to set something क्रम me. Well,
	 * ideally, all that crap will be करोne in prom.c and the CPU left
	 * in a RAM-based रुको loop like CHRP.
	 */
	mdelay(1);

	/* Restore our exception vector */
	patch_inकाष्ठाion((काष्ठा ppc_inst *)vector, ppc_inst(save_vector));

	local_irq_restore(flags);
	अगर (ppc_md.progress) ppc_md.progress("smp_core99_kick_cpu done", 0x347);

	वापस 0;
पूर्ण

अटल व्योम smp_core99_setup_cpu(पूर्णांक cpu_nr)
अणु
	/* Setup L2/L3 */
	अगर (cpu_nr != 0)
		core99_init_caches(cpu_nr);

	/* Setup खोलोpic */
	mpic_setup_this_cpu();
पूर्ण

#अगर_घोषित CONFIG_PPC64
#अगर_घोषित CONFIG_HOTPLUG_CPU
अटल अचिन्हित पूर्णांक smp_core99_host_खोलो;

अटल पूर्णांक smp_core99_cpu_prepare(अचिन्हित पूर्णांक cpu)
अणु
	पूर्णांक rc;

	/* Open i2c bus अगर it was used क्रम tb sync */
	अगर (pmac_tb_घड़ी_chip_host && !smp_core99_host_खोलो) अणु
		rc = pmac_i2c_खोलो(pmac_tb_घड़ी_chip_host, 1);
		अगर (rc) अणु
			pr_err("Failed to open i2c bus for time sync\n");
			वापस notअगरier_from_त्रुटि_सं(rc);
		पूर्ण
		smp_core99_host_खोलो = 1;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक smp_core99_cpu_online(अचिन्हित पूर्णांक cpu)
अणु
	/* Close i2c bus अगर it was used क्रम tb sync */
	अगर (pmac_tb_घड़ी_chip_host && smp_core99_host_खोलो) अणु
		pmac_i2c_बंद(pmac_tb_घड़ी_chip_host);
		smp_core99_host_खोलो = 0;
	पूर्ण
	वापस 0;
पूर्ण
#पूर्ण_अगर /* CONFIG_HOTPLUG_CPU */

अटल व्योम __init smp_core99_bringup_करोne(व्योम)
अणु
	बाह्य व्योम g5_phy_disable_cpu1(व्योम);

	/* Close i2c bus अगर it was used क्रम tb sync */
	अगर (pmac_tb_घड़ी_chip_host)
		pmac_i2c_बंद(pmac_tb_घड़ी_chip_host);

	/* If we didn't start the second CPU, we must take
	 * it off the bus.
	 */
	अगर (of_machine_is_compatible("MacRISC4") &&
	    num_online_cpus() < 2) अणु
		set_cpu_present(1, false);
		g5_phy_disable_cpu1();
	पूर्ण
#अगर_घोषित CONFIG_HOTPLUG_CPU
	cpuhp_setup_state_nocalls(CPUHP_POWERPC_PMAC_PREPARE,
				  "powerpc/pmac:prepare", smp_core99_cpu_prepare,
				  शून्य);
	cpuhp_setup_state_nocalls(CPUHP_AP_ONLINE_DYN, "powerpc/pmac:online",
				  smp_core99_cpu_online, शून्य);
#पूर्ण_अगर

	अगर (ppc_md.progress)
		ppc_md.progress("smp_core99_bringup_done", 0x349);
पूर्ण
#पूर्ण_अगर /* CONFIG_PPC64 */

#अगर_घोषित CONFIG_HOTPLUG_CPU

अटल पूर्णांक smp_core99_cpu_disable(व्योम)
अणु
	पूर्णांक rc = generic_cpu_disable();
	अगर (rc)
		वापस rc;

	mpic_cpu_set_priority(0xf);

	cleanup_cpu_mmu_context();

	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_PPC32

अटल व्योम pmac_cpu_offline_self(व्योम)
अणु
	पूर्णांक cpu = smp_processor_id();

	local_irq_disable();
	idle_task_निकास();
	pr_debug("CPU%d offline\n", cpu);
	generic_set_cpu_dead(cpu);
	smp_wmb();
	mb();
	low_cpu_offline_self();
पूर्ण

#अन्यथा /* CONFIG_PPC32 */

अटल व्योम pmac_cpu_offline_self(व्योम)
अणु
	पूर्णांक cpu = smp_processor_id();

	local_irq_disable();
	idle_task_निकास();

	/*
	 * turn off as much as possible, we'll be
	 * kicked out as this will only be invoked
	 * on core99 platक्रमms क्रम now ...
	 */

	prपूर्णांकk(KERN_INFO "CPU#%d offline\n", cpu);
	generic_set_cpu_dead(cpu);
	smp_wmb();

	/*
	 * Re-enable पूर्णांकerrupts. The NAP code needs to enable them
	 * anyways, करो it now so we deal with the हाल where one alपढ़ोy
	 * happened जबतक soft-disabled.
	 * We shouldn't get any बाह्यal पूर्णांकerrupts, only decrementer, and the
	 * decrementer handler is safe क्रम use on offline CPUs
	 */
	local_irq_enable();

	जबतक (1) अणु
		/* let's not take समयr पूर्णांकerrupts too often ... */
		set_dec(0x7fffffff);

		/* Enter NAP mode */
		घातer4_idle();
	पूर्ण
पूर्ण

#पूर्ण_अगर /* अन्यथा CONFIG_PPC32 */
#पूर्ण_अगर /* CONFIG_HOTPLUG_CPU */

/* Core99 Macs (dual G4s and G5s) */
अटल काष्ठा smp_ops_t core99_smp_ops = अणु
	.message_pass	= smp_mpic_message_pass,
	.probe		= smp_core99_probe,
#अगर_घोषित CONFIG_PPC64
	.bringup_करोne	= smp_core99_bringup_करोne,
#पूर्ण_अगर
	.kick_cpu	= smp_core99_kick_cpu,
	.setup_cpu	= smp_core99_setup_cpu,
	.give_समयbase	= smp_core99_give_समयbase,
	.take_समयbase	= smp_core99_take_समयbase,
#अगर defined(CONFIG_HOTPLUG_CPU)
	.cpu_disable	= smp_core99_cpu_disable,
	.cpu_die	= generic_cpu_die,
#पूर्ण_अगर
पूर्ण;

व्योम __init pmac_setup_smp(व्योम)
अणु
	काष्ठा device_node *np;

	/* Check क्रम Core99 */
	np = of_find_node_by_name(शून्य, "uni-n");
	अगर (!np)
		np = of_find_node_by_name(शून्य, "u3");
	अगर (!np)
		np = of_find_node_by_name(शून्य, "u4");
	अगर (np) अणु
		of_node_put(np);
		smp_ops = &core99_smp_ops;
	पूर्ण
#अगर_घोषित CONFIG_PPC_PMAC32_PSURGE
	अन्यथा अणु
		/* We have to set bits in cpu_possible_mask here since the
		 * secondary CPU(s) aren't in the device tree. Various
		 * things won't be initialized क्रम CPUs not in the possible
		 * map, so we really need to fix it up here.
		 */
		पूर्णांक cpu;

		क्रम (cpu = 1; cpu < 4 && cpu < NR_CPUS; ++cpu)
			set_cpu_possible(cpu, true);
		smp_ops = &psurge_smp_ops;
	पूर्ण
#पूर्ण_अगर /* CONFIG_PPC_PMAC32_PSURGE */

#अगर_घोषित CONFIG_HOTPLUG_CPU
	smp_ops->cpu_offline_self = pmac_cpu_offline_self;
#पूर्ण_अगर
पूर्ण


