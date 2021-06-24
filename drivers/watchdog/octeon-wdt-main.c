<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * Octeon Watchकरोg driver
 *
 * Copyright (C) 2007-2017 Cavium, Inc.
 *
 * Converted to use WATCHDOG_CORE by Aaro Koskinen <aaro.koskinen@iki.fi>.
 *
 * Some parts derived from wdt.c
 *
 *	(c) Copyright 1996-1997 Alan Cox <alan@lxorguk.ukuu.org.uk>,
 *						All Rights Reserved.
 *
 *	Neither Alan Cox nor CymruNet Ltd. admit liability nor provide
 *	warranty क्रम any of this software. This material is provided
 *	"AS-IS" and at no अक्षरge.
 *
 *	(c) Copyright 1995    Alan Cox <alan@lxorguk.ukuu.org.uk>
 *
 * The OCTEON watchकरोg has a maximum समयout of 2^32 * io_घड़ी.
 * For most प्रणालीs this is less than 10 seconds, so to allow क्रम
 * software to request दीर्घer watchकरोg heartbeats, we मुख्यtain software
 * counters to count multiples of the base rate.  If the प्रणाली locks
 * up in such a manner that we can not run the software counters, the
 * only result is a watchकरोg reset sooner than was requested.  But
 * that is OK, because in this हाल userspace would likely not be able
 * to करो anything anyhow.
 *
 * The hardware watchकरोg पूर्णांकerval we call the period.  The OCTEON
 * watchकरोg goes through several stages, after the first period an
 * irq is निश्चितed, then अगर it is not reset, after the next period NMI
 * is निश्चितed, then after an additional period a chip wide soft reset.
 * So क्रम the software counters, we reset watchकरोg after each period
 * and decrement the counter.  But क्रम the last two periods we need to
 * let the watchकरोg progress to the NMI stage so we disable the irq
 * and let it proceed.  Once in the NMI, we prपूर्णांक the रेजिस्टर state
 * to the serial port and then रुको क्रम the reset.
 *
 * A watchकरोg is मुख्यtained क्रम each CPU in the प्रणाली, that way अगर
 * one CPU suffers a lockup, we also get a रेजिस्टर dump and reset.
 * The userspace ping resets the watchकरोg on all CPUs.
 *
 * Beक्रमe userspace खोलोs the watchकरोg device, we still run the
 * watchकरोgs to catch any lockups that may be kernel related.
 *
 */

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/watchकरोg.h>
#समावेश <linux/cpumask.h>
#समावेश <linux/module.h>
#समावेश <linux/delay.h>
#समावेश <linux/cpu.h>
#समावेश <linux/irq.h>

#समावेश <यंत्र/mipsregs.h>
#समावेश <यंत्र/uयंत्र.h>

#समावेश <यंत्र/octeon/octeon.h>
#समावेश <यंत्र/octeon/cvmx-boot-vector.h>
#समावेश <यंत्र/octeon/cvmx-ciu2-defs.h>
#समावेश <यंत्र/octeon/cvmx-rst-defs.h>

/* Watchकरोg पूर्णांकerrupt major block number (8 MSBs of पूर्णांकsn) */
#घोषणा WD_BLOCK_NUMBER		0x01

अटल पूर्णांक भागisor;

/* The count needed to achieve समयout_sec. */
अटल अचिन्हित पूर्णांक समयout_cnt;

/* The maximum period supported. */
अटल अचिन्हित पूर्णांक max_समयout_sec;

/* The current period.  */
अटल अचिन्हित पूर्णांक समयout_sec;

/* Set to non-zero when userspace countकरोwn mode active */
अटल bool करो_countकरोwn;
अटल अचिन्हित पूर्णांक countकरोwn_reset;
अटल अचिन्हित पूर्णांक per_cpu_countकरोwn[NR_CPUS];

अटल cpumask_t irq_enabled_cpus;

#घोषणा WD_TIMO 60			/* Default heartbeat = 60 seconds */

#घोषणा CVMX_GSERX_SCRATCH(offset) (CVMX_ADD_IO_SEG(0x0001180090000020ull) + ((offset) & 15) * 0x1000000ull)

अटल पूर्णांक heartbeat = WD_TIMO;
module_param(heartbeat, पूर्णांक, 0444);
MODULE_PARM_DESC(heartbeat,
	"Watchdog heartbeat in seconds. (0 < heartbeat, default="
				__MODULE_STRING(WD_TIMO) ")");

अटल bool nowayout = WATCHDOG_NOWAYOUT;
module_param(nowayout, bool, 0444);
MODULE_PARM_DESC(nowayout,
	"Watchdog cannot be stopped once started (default="
				__MODULE_STRING(WATCHDOG_NOWAYOUT) ")");

अटल पूर्णांक disable;
module_param(disable, पूर्णांक, 0444);
MODULE_PARM_DESC(disable,
	"Disable the watchdog entirely (default=0)");

अटल काष्ठा cvmx_boot_vector_element *octeon_wdt_bootvector;

व्योम octeon_wdt_nmi_stage2(व्योम);

अटल पूर्णांक cpu2core(पूर्णांक cpu)
अणु
#अगर_घोषित CONFIG_SMP
	वापस cpu_logical_map(cpu) & 0x3f;
#अन्यथा
	वापस cvmx_get_core_num();
#पूर्ण_अगर
पूर्ण

/**
 * Poke the watchकरोg when an पूर्णांकerrupt is received
 *
 * @cpl:
 * @dev_id:
 *
 * Returns
 */
अटल irqवापस_t octeon_wdt_poke_irq(पूर्णांक cpl, व्योम *dev_id)
अणु
	पूर्णांक cpu = raw_smp_processor_id();
	अचिन्हित पूर्णांक core = cpu2core(cpu);
	पूर्णांक node = cpu_to_node(cpu);

	अगर (करो_countकरोwn) अणु
		अगर (per_cpu_countकरोwn[cpu] > 0) अणु
			/* We're alive, poke the watchकरोg */
			cvmx_ग_लिखो_csr_node(node, CVMX_CIU_PP_POKEX(core), 1);
			per_cpu_countकरोwn[cpu]--;
		पूर्ण अन्यथा अणु
			/* Bad news, you are about to reboot. */
			disable_irq_nosync(cpl);
			cpumask_clear_cpu(cpu, &irq_enabled_cpus);
		पूर्ण
	पूर्ण अन्यथा अणु
		/* Not खोलो, just ping away... */
		cvmx_ग_लिखो_csr_node(node, CVMX_CIU_PP_POKEX(core), 1);
	पूर्ण
	वापस IRQ_HANDLED;
पूर्ण

/* From setup.c */
बाह्य पूर्णांक prom_अक्षर_दो(अक्षर c);

/**
 * Write a string to the uart
 *
 * @str:        String to ग_लिखो
 */
अटल व्योम octeon_wdt_ग_लिखो_string(स्थिर अक्षर *str)
अणु
	/* Just loop writing one byte at a समय */
	जबतक (*str)
		prom_अक्षर_दो(*str++);
पूर्ण

/**
 * Write a hex number out of the uart
 *
 * @value:      Number to display
 * @digits:     Number of digits to prपूर्णांक (1 to 16)
 */
अटल व्योम octeon_wdt_ग_लिखो_hex(u64 value, पूर्णांक digits)
अणु
	पूर्णांक d;
	पूर्णांक v;

	क्रम (d = 0; d < digits; d++) अणु
		v = (value >> ((digits - d - 1) * 4)) & 0xf;
		अगर (v >= 10)
			prom_अक्षर_दो('a' + v - 10);
		अन्यथा
			prom_अक्षर_दो('0' + v);
	पूर्ण
पूर्ण

अटल स्थिर अक्षर reg_name[][3] = अणु
	"$0", "at", "v0", "v1", "a0", "a1", "a2", "a3",
	"a4", "a5", "a6", "a7", "t0", "t1", "t2", "t3",
	"s0", "s1", "s2", "s3", "s4", "s5", "s6", "s7",
	"t8", "t9", "k0", "k1", "gp", "sp", "s8", "ra"
पूर्ण;

/**
 * NMI stage 3 handler. NMIs are handled in the following manner:
 * 1) The first NMI handler enables CVMSEG and transfers from
 * the bootbus region पूर्णांकo normal memory. It is careful to not
 * destroy any रेजिस्टरs.
 * 2) The second stage handler uses CVMSEG to save the रेजिस्टरs
 * and create a stack क्रम C code. It then calls the third level
 * handler with one argument, a poपूर्णांकer to the रेजिस्टर values.
 * 3) The third, and final, level handler is the following C
 * function that prपूर्णांकs out some useful infomration.
 *
 * @reg:    Poपूर्णांकer to रेजिस्टर state beक्रमe the NMI
 */
व्योम octeon_wdt_nmi_stage3(u64 reg[32])
अणु
	u64 i;

	अचिन्हित पूर्णांक coreid = cvmx_get_core_num();
	/*
	 * Save status and cause early to get them beक्रमe any changes
	 * might happen.
	 */
	u64 cp0_cause = पढ़ो_c0_cause();
	u64 cp0_status = पढ़ो_c0_status();
	u64 cp0_error_epc = पढ़ो_c0_errorepc();
	u64 cp0_epc = पढ़ो_c0_epc();

	/* Delay so output from all cores output is not jumbled together. */
	udelay(85000 * coreid);

	octeon_wdt_ग_लिखो_string("\r\n*** NMI Watchdog interrupt on Core 0x");
	octeon_wdt_ग_लिखो_hex(coreid, 2);
	octeon_wdt_ग_लिखो_string(" ***\r\n");
	क्रम (i = 0; i < 32; i++) अणु
		octeon_wdt_ग_लिखो_string("\t");
		octeon_wdt_ग_लिखो_string(reg_name[i]);
		octeon_wdt_ग_लिखो_string("\t0x");
		octeon_wdt_ग_लिखो_hex(reg[i], 16);
		अगर (i & 1)
			octeon_wdt_ग_लिखो_string("\r\n");
	पूर्ण
	octeon_wdt_ग_लिखो_string("\terr_epc\t0x");
	octeon_wdt_ग_लिखो_hex(cp0_error_epc, 16);

	octeon_wdt_ग_लिखो_string("\tepc\t0x");
	octeon_wdt_ग_लिखो_hex(cp0_epc, 16);
	octeon_wdt_ग_लिखो_string("\r\n");

	octeon_wdt_ग_लिखो_string("\tstatus\t0x");
	octeon_wdt_ग_लिखो_hex(cp0_status, 16);
	octeon_wdt_ग_लिखो_string("\tcause\t0x");
	octeon_wdt_ग_लिखो_hex(cp0_cause, 16);
	octeon_wdt_ग_लिखो_string("\r\n");

	/* The CIU रेजिस्टर is dअगरferent क्रम each Octeon model. */
	अगर (OCTEON_IS_MODEL(OCTEON_CN68XX)) अणु
		octeon_wdt_ग_लिखो_string("\tsrc_wd\t0x");
		octeon_wdt_ग_लिखो_hex(cvmx_पढ़ो_csr(CVMX_CIU2_SRC_PPX_IP2_WDOG(coreid)), 16);
		octeon_wdt_ग_लिखो_string("\ten_wd\t0x");
		octeon_wdt_ग_लिखो_hex(cvmx_पढ़ो_csr(CVMX_CIU2_EN_PPX_IP2_WDOG(coreid)), 16);
		octeon_wdt_ग_लिखो_string("\r\n");
		octeon_wdt_ग_लिखो_string("\tsrc_rml\t0x");
		octeon_wdt_ग_लिखो_hex(cvmx_पढ़ो_csr(CVMX_CIU2_SRC_PPX_IP2_RML(coreid)), 16);
		octeon_wdt_ग_लिखो_string("\ten_rml\t0x");
		octeon_wdt_ग_लिखो_hex(cvmx_पढ़ो_csr(CVMX_CIU2_EN_PPX_IP2_RML(coreid)), 16);
		octeon_wdt_ग_लिखो_string("\r\n");
		octeon_wdt_ग_लिखो_string("\tsum\t0x");
		octeon_wdt_ग_लिखो_hex(cvmx_पढ़ो_csr(CVMX_CIU2_SUM_PPX_IP2(coreid)), 16);
		octeon_wdt_ग_लिखो_string("\r\n");
	पूर्ण अन्यथा अगर (!octeon_has_feature(OCTEON_FEATURE_CIU3)) अणु
		octeon_wdt_ग_लिखो_string("\tsum0\t0x");
		octeon_wdt_ग_लिखो_hex(cvmx_पढ़ो_csr(CVMX_CIU_INTX_SUM0(coreid * 2)), 16);
		octeon_wdt_ग_लिखो_string("\ten0\t0x");
		octeon_wdt_ग_लिखो_hex(cvmx_पढ़ो_csr(CVMX_CIU_INTX_EN0(coreid * 2)), 16);
		octeon_wdt_ग_लिखो_string("\r\n");
	पूर्ण

	octeon_wdt_ग_लिखो_string("*** Chip soft reset soon ***\r\n");

	/*
	 * G-30204: We must trigger a soft reset beक्रमe watchकरोg
	 * करोes an incomplete job of करोing it.
	 */
	अगर (OCTEON_IS_OCTEON3() && !OCTEON_IS_MODEL(OCTEON_CN70XX)) अणु
		u64 scr;
		अचिन्हित पूर्णांक node = cvmx_get_node_num();
		अचिन्हित पूर्णांक lcore = cvmx_get_local_core_num();
		जोड़ cvmx_ciu_wकरोgx ciu_wकरोg;

		/*
		 * Wait क्रम other cores to prपूर्णांक out inक्रमmation, but
		 * not too दीर्घ.  Do the soft reset beक्रमe watchकरोg
		 * can trigger it.
		 */
		करो अणु
			ciu_wकरोg.u64 = cvmx_पढ़ो_csr_node(node, CVMX_CIU_WDOGX(lcore));
		पूर्ण जबतक (ciu_wकरोg.s.cnt > 0x10000);

		scr = cvmx_पढ़ो_csr_node(0, CVMX_GSERX_SCRATCH(0));
		scr |= 1 << 11; /* Indicate watchकरोg in bit 11 */
		cvmx_ग_लिखो_csr_node(0, CVMX_GSERX_SCRATCH(0), scr);
		cvmx_ग_लिखो_csr_node(0, CVMX_RST_SOFT_RST, 1);
	पूर्ण
पूर्ण

अटल पूर्णांक octeon_wdt_cpu_to_irq(पूर्णांक cpu)
अणु
	अचिन्हित पूर्णांक coreid;
	पूर्णांक node;
	पूर्णांक irq;

	coreid = cpu2core(cpu);
	node = cpu_to_node(cpu);

	अगर (octeon_has_feature(OCTEON_FEATURE_CIU3)) अणु
		काष्ठा irq_करोमुख्य *करोमुख्य;
		पूर्णांक hwirq;

		करोमुख्य = octeon_irq_get_block_करोमुख्य(node,
						     WD_BLOCK_NUMBER);
		hwirq = WD_BLOCK_NUMBER << 12 | 0x200 | coreid;
		irq = irq_find_mapping(करोमुख्य, hwirq);
	पूर्ण अन्यथा अणु
		irq = OCTEON_IRQ_WDOG0 + coreid;
	पूर्ण
	वापस irq;
पूर्ण

अटल पूर्णांक octeon_wdt_cpu_pre_करोwn(अचिन्हित पूर्णांक cpu)
अणु
	अचिन्हित पूर्णांक core;
	पूर्णांक node;
	जोड़ cvmx_ciu_wकरोgx ciu_wकरोg;

	core = cpu2core(cpu);

	node = cpu_to_node(cpu);

	/* Poke the watchकरोg to clear out its state */
	cvmx_ग_लिखो_csr_node(node, CVMX_CIU_PP_POKEX(core), 1);

	/* Disable the hardware. */
	ciu_wकरोg.u64 = 0;
	cvmx_ग_लिखो_csr_node(node, CVMX_CIU_WDOGX(core), ciu_wकरोg.u64);

	मुक्त_irq(octeon_wdt_cpu_to_irq(cpu), octeon_wdt_poke_irq);
	वापस 0;
पूर्ण

अटल पूर्णांक octeon_wdt_cpu_online(अचिन्हित पूर्णांक cpu)
अणु
	अचिन्हित पूर्णांक core;
	अचिन्हित पूर्णांक irq;
	जोड़ cvmx_ciu_wकरोgx ciu_wकरोg;
	पूर्णांक node;
	काष्ठा irq_करोमुख्य *करोमुख्य;
	पूर्णांक hwirq;

	core = cpu2core(cpu);
	node = cpu_to_node(cpu);

	octeon_wdt_bootvector[core].target_ptr = (u64)octeon_wdt_nmi_stage2;

	/* Disable it beक्रमe करोing anything with the पूर्णांकerrupts. */
	ciu_wकरोg.u64 = 0;
	cvmx_ग_लिखो_csr_node(node, CVMX_CIU_WDOGX(core), ciu_wकरोg.u64);

	per_cpu_countकरोwn[cpu] = countकरोwn_reset;

	अगर (octeon_has_feature(OCTEON_FEATURE_CIU3)) अणु
		/* Must get the करोमुख्य क्रम the watchकरोg block */
		करोमुख्य = octeon_irq_get_block_करोमुख्य(node, WD_BLOCK_NUMBER);

		/* Get a irq क्रम the wd पूर्णांकsn (hardware पूर्णांकerrupt) */
		hwirq = WD_BLOCK_NUMBER << 12 | 0x200 | core;
		irq = irq_create_mapping(करोमुख्य, hwirq);
		irqd_set_trigger_type(irq_get_irq_data(irq),
				      IRQ_TYPE_EDGE_RISING);
	पूर्ण अन्यथा
		irq = OCTEON_IRQ_WDOG0 + core;

	अगर (request_irq(irq, octeon_wdt_poke_irq,
			IRQF_NO_THREAD, "octeon_wdt", octeon_wdt_poke_irq))
		panic("octeon_wdt: Couldn't obtain irq %d", irq);

	/* Must set the irq affinity here */
	अगर (octeon_has_feature(OCTEON_FEATURE_CIU3)) अणु
		cpumask_t mask;

		cpumask_clear(&mask);
		cpumask_set_cpu(cpu, &mask);
		irq_set_affinity(irq, &mask);
	पूर्ण

	cpumask_set_cpu(cpu, &irq_enabled_cpus);

	/* Poke the watchकरोg to clear out its state */
	cvmx_ग_लिखो_csr_node(node, CVMX_CIU_PP_POKEX(core), 1);

	/* Finally enable the watchकरोg now that all handlers are installed */
	ciu_wकरोg.u64 = 0;
	ciu_wकरोg.s.len = समयout_cnt;
	ciu_wकरोg.s.mode = 3;	/* 3 = Interrupt + NMI + Soft-Reset */
	cvmx_ग_लिखो_csr_node(node, CVMX_CIU_WDOGX(core), ciu_wकरोg.u64);

	वापस 0;
पूर्ण

अटल पूर्णांक octeon_wdt_ping(काष्ठा watchकरोg_device __always_unused *wकरोg)
अणु
	पूर्णांक cpu;
	पूर्णांक coreid;
	पूर्णांक node;

	अगर (disable)
		वापस 0;

	क्रम_each_online_cpu(cpu) अणु
		coreid = cpu2core(cpu);
		node = cpu_to_node(cpu);
		cvmx_ग_लिखो_csr_node(node, CVMX_CIU_PP_POKEX(coreid), 1);
		per_cpu_countकरोwn[cpu] = countकरोwn_reset;
		अगर ((countकरोwn_reset || !करो_countकरोwn) &&
		    !cpumask_test_cpu(cpu, &irq_enabled_cpus)) अणु
			/* We have to enable the irq */
			enable_irq(octeon_wdt_cpu_to_irq(cpu));
			cpumask_set_cpu(cpu, &irq_enabled_cpus);
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण

अटल व्योम octeon_wdt_calc_parameters(पूर्णांक t)
अणु
	अचिन्हित पूर्णांक periods;

	समयout_sec = max_समयout_sec;


	/*
	 * Find the largest पूर्णांकerrupt period, that can evenly भागide
	 * the requested heartbeat समय.
	 */
	जबतक ((t % समयout_sec) != 0)
		समयout_sec--;

	periods = t / समयout_sec;

	/*
	 * The last two periods are after the irq is disabled, and
	 * then to the nmi, so we subtract them off.
	 */

	countकरोwn_reset = periods > 2 ? periods - 2 : 0;
	heartbeat = t;
	समयout_cnt = ((octeon_get_io_घड़ी_rate() / भागisor) * समयout_sec) >> 8;
पूर्ण

अटल पूर्णांक octeon_wdt_set_समयout(काष्ठा watchकरोg_device *wकरोg,
				  अचिन्हित पूर्णांक t)
अणु
	पूर्णांक cpu;
	पूर्णांक coreid;
	जोड़ cvmx_ciu_wकरोgx ciu_wकरोg;
	पूर्णांक node;

	अगर (t <= 0)
		वापस -1;

	octeon_wdt_calc_parameters(t);

	अगर (disable)
		वापस 0;

	क्रम_each_online_cpu(cpu) अणु
		coreid = cpu2core(cpu);
		node = cpu_to_node(cpu);
		cvmx_ग_लिखो_csr_node(node, CVMX_CIU_PP_POKEX(coreid), 1);
		ciu_wकरोg.u64 = 0;
		ciu_wकरोg.s.len = समयout_cnt;
		ciu_wकरोg.s.mode = 3;	/* 3 = Interrupt + NMI + Soft-Reset */
		cvmx_ग_लिखो_csr_node(node, CVMX_CIU_WDOGX(coreid), ciu_wकरोg.u64);
		cvmx_ग_लिखो_csr_node(node, CVMX_CIU_PP_POKEX(coreid), 1);
	पूर्ण
	octeon_wdt_ping(wकरोg); /* Get the irqs back on. */
	वापस 0;
पूर्ण

अटल पूर्णांक octeon_wdt_start(काष्ठा watchकरोg_device *wकरोg)
अणु
	octeon_wdt_ping(wकरोg);
	करो_countकरोwn = 1;
	वापस 0;
पूर्ण

अटल पूर्णांक octeon_wdt_stop(काष्ठा watchकरोg_device *wकरोg)
अणु
	करो_countकरोwn = 0;
	octeon_wdt_ping(wकरोg);
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा watchकरोg_info octeon_wdt_info = अणु
	.options = WDIOF_SETTIMEOUT | WDIOF_MAGICCLOSE | WDIOF_KEEPALIVEPING,
	.identity = "OCTEON",
पूर्ण;

अटल स्थिर काष्ठा watchकरोg_ops octeon_wdt_ops = अणु
	.owner		= THIS_MODULE,
	.start		= octeon_wdt_start,
	.stop		= octeon_wdt_stop,
	.ping		= octeon_wdt_ping,
	.set_समयout	= octeon_wdt_set_समयout,
पूर्ण;

अटल काष्ठा watchकरोg_device octeon_wdt = अणु
	.info	= &octeon_wdt_info,
	.ops	= &octeon_wdt_ops,
पूर्ण;

अटल क्रमागत cpuhp_state octeon_wdt_online;
/**
 * Module/ driver initialization.
 *
 * Returns Zero on success
 */
अटल पूर्णांक __init octeon_wdt_init(व्योम)
अणु
	पूर्णांक ret;

	octeon_wdt_bootvector = cvmx_boot_vector_get();
	अगर (!octeon_wdt_bootvector) अणु
		pr_err("Error: Cannot allocate boot vector.\n");
		वापस -ENOMEM;
	पूर्ण

	अगर (OCTEON_IS_MODEL(OCTEON_CN68XX))
		भागisor = 0x200;
	अन्यथा अगर (OCTEON_IS_MODEL(OCTEON_CN78XX))
		भागisor = 0x400;
	अन्यथा
		भागisor = 0x100;

	/*
	 * Watchकरोg समय expiration length = The 16 bits of LEN
	 * represent the most signअगरicant bits of a 24 bit decrementer
	 * that decrements every भागisor cycle.
	 *
	 * Try क्रम a समयout of 5 sec, अगर that fails a smaller number
	 * of even seconds,
	 */
	max_समयout_sec = 6;
	करो अणु
		max_समयout_sec--;
		समयout_cnt = ((octeon_get_io_घड़ी_rate() / भागisor) * max_समयout_sec) >> 8;
	पूर्ण जबतक (समयout_cnt > 65535);

	BUG_ON(समयout_cnt == 0);

	octeon_wdt_calc_parameters(heartbeat);

	pr_info("Initial granularity %d Sec\n", समयout_sec);

	octeon_wdt.समयout	= समयout_sec;
	octeon_wdt.max_समयout	= अच_पूर्णांक_उच्च;

	watchकरोg_set_nowayout(&octeon_wdt, nowayout);

	ret = watchकरोg_रेजिस्टर_device(&octeon_wdt);
	अगर (ret) अणु
		pr_err("watchdog_register_device() failed: %d\n", ret);
		वापस ret;
	पूर्ण

	अगर (disable) अणु
		pr_notice("disabled\n");
		वापस 0;
	पूर्ण

	cpumask_clear(&irq_enabled_cpus);

	ret = cpuhp_setup_state(CPUHP_AP_ONLINE_DYN, "watchdog/octeon:online",
				octeon_wdt_cpu_online, octeon_wdt_cpu_pre_करोwn);
	अगर (ret < 0)
		जाओ err;
	octeon_wdt_online = ret;
	वापस 0;
err:
	cvmx_ग_लिखो_csr(CVMX_MIO_BOOT_LOC_CFGX(0), 0);
	watchकरोg_unरेजिस्टर_device(&octeon_wdt);
	वापस ret;
पूर्ण

/**
 * Module / driver shutकरोwn
 */
अटल व्योम __निकास octeon_wdt_cleanup(व्योम)
अणु
	watchकरोg_unरेजिस्टर_device(&octeon_wdt);

	अगर (disable)
		वापस;

	cpuhp_हटाओ_state(octeon_wdt_online);

	/*
	 * Disable the boot-bus memory, the code it poपूर्णांकs to is soon
	 * to go missing.
	 */
	cvmx_ग_लिखो_csr(CVMX_MIO_BOOT_LOC_CFGX(0), 0);
पूर्ण

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Cavium Inc. <support@cavium.com>");
MODULE_DESCRIPTION("Cavium Inc. OCTEON Watchdog driver.");
module_init(octeon_wdt_init);
module_निकास(octeon_wdt_cleanup);
