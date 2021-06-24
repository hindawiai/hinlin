<शैली गुरु>
/*
 * TX4927 setup routines
 * Based on linux/arch/mips/txx9/rbtx4938/setup.c,
 *	    and RBTX49xx patch from CELF patch archive.
 *
 * 2003-2005 (c) MontaVista Software, Inc.
 * (C) Copyright TOSHIBA CORPORATION 2000-2001, 2004-2007
 *
 * This file is subject to the terms and conditions of the GNU General Public
 * License.  See the file "COPYING" in the मुख्य directory of this archive
 * क्रम more details.
 */
#समावेश <linux/init.h>
#समावेश <linux/ioport.h>
#समावेश <linux/delay.h>
#समावेश <linux/param.h>
#समावेश <linux/ptrace.h>
#समावेश <linux/mtd/physmap.h>
#समावेश <यंत्र/reboot.h>
#समावेश <यंत्र/traps.h>
#समावेश <यंत्र/txx9irq.h>
#समावेश <यंत्र/txx9पंचांगr.h>
#समावेश <यंत्र/txx9pपन.स>
#समावेश <यंत्र/txx9/generic.h>
#समावेश <यंत्र/txx9/dmac.h>
#समावेश <यंत्र/txx9/tx4927.h>

अटल व्योम __init tx4927_wdr_init(व्योम)
अणु
	/* report watchकरोg reset status */
	अगर (____raw_पढ़ोq(&tx4927_ccfgptr->ccfg) & TX4927_CCFG_WDRST)
		pr_warn("Watchdog reset detected at 0x%lx\n",
			पढ़ो_c0_errorepc());
	/* clear WatchDogReset (W1C) */
	tx4927_ccfg_set(TX4927_CCFG_WDRST);
	/* करो reset on watchकरोg */
	tx4927_ccfg_set(TX4927_CCFG_WR);
पूर्ण

व्योम __init tx4927_wdt_init(व्योम)
अणु
	txx9_wdt_init(TX4927_TMR_REG(2) & 0xfffffffffULL);
पूर्ण

अटल व्योम tx4927_machine_restart(अक्षर *command)
अणु
	local_irq_disable();
	pr_emerg("Rebooting (with %s watchdog reset)...\n",
		 (____raw_पढ़ोq(&tx4927_ccfgptr->ccfg) & TX4927_CCFG_WDREXEN) ?
		 "external" : "internal");
	/* clear watchकरोg status */
	tx4927_ccfg_set(TX4927_CCFG_WDRST);	/* W1C */
	txx9_wdt_now(TX4927_TMR_REG(2) & 0xfffffffffULL);
	जबतक (!(____raw_पढ़ोq(&tx4927_ccfgptr->ccfg) & TX4927_CCFG_WDRST))
		;
	mdelay(10);
	अगर (____raw_पढ़ोq(&tx4927_ccfgptr->ccfg) & TX4927_CCFG_WDREXEN) अणु
		pr_emerg("Rebooting (with internal watchdog reset)...\n");
		/* External WDRST failed.  Do पूर्णांकernal watchकरोg reset */
		tx4927_ccfg_clear(TX4927_CCFG_WDREXEN);
	पूर्ण
	/* fallback */
	(*_machine_halt)();
पूर्ण

व्योम show_रेजिस्टरs(काष्ठा pt_regs *regs);
अटल पूर्णांक tx4927_be_handler(काष्ठा pt_regs *regs, पूर्णांक is_fixup)
अणु
	पूर्णांक data = regs->cp0_cause & 4;
	console_verbose();
	pr_err("%cBE exception at %#lx\n", data ? 'D' : 'I', regs->cp0_epc);
	pr_err("ccfg:%llx, toea:%llx\n",
	       (अचिन्हित दीर्घ दीर्घ)____raw_पढ़ोq(&tx4927_ccfgptr->ccfg),
	       (अचिन्हित दीर्घ दीर्घ)____raw_पढ़ोq(&tx4927_ccfgptr->toea));
#अगर_घोषित CONFIG_PCI
	tx4927_report_pcic_status();
#पूर्ण_अगर
	show_रेजिस्टरs(regs);
	panic("BusError!");
पूर्ण
अटल व्योम __init tx4927_be_init(व्योम)
अणु
	board_be_handler = tx4927_be_handler;
पूर्ण

अटल काष्ठा resource tx4927_sdram_resource[4];

व्योम __init tx4927_setup(व्योम)
अणु
	पूर्णांक i;
	__u32 भागmode;
	अचिन्हित पूर्णांक cpuclk = 0;
	u64 ccfg;

	txx9_reg_res_init(TX4927_REV_PCODE(), TX4927_REG_BASE,
			  TX4927_REG_SIZE);
	set_c0_config(TX49_CONF_CWFON);

	/* SDRAMC,EBUSC are configured by PROM */
	क्रम (i = 0; i < 8; i++) अणु
		अगर (!(TX4927_EBUSC_CR(i) & 0x8))
			जारी;	/* disabled */
		txx9_ce_res[i].start = (अचिन्हित दीर्घ)TX4927_EBUSC_BA(i);
		txx9_ce_res[i].end =
			txx9_ce_res[i].start + TX4927_EBUSC_SIZE(i) - 1;
		request_resource(&iomem_resource, &txx9_ce_res[i]);
	पूर्ण

	/* घड़ीs */
	ccfg = ____raw_पढ़ोq(&tx4927_ccfgptr->ccfg);
	अगर (txx9_master_घड़ी) अणु
		/* calculate gbus_घड़ी and cpu_घड़ी from master_घड़ी */
		भागmode = (__u32)ccfg & TX4927_CCFG_DIVMODE_MASK;
		चयन (भागmode) अणु
		हाल TX4927_CCFG_DIVMODE_8:
		हाल TX4927_CCFG_DIVMODE_10:
		हाल TX4927_CCFG_DIVMODE_12:
		हाल TX4927_CCFG_DIVMODE_16:
			txx9_gbus_घड़ी = txx9_master_घड़ी * 4; अवरोध;
		शेष:
			txx9_gbus_घड़ी = txx9_master_घड़ी;
		पूर्ण
		चयन (भागmode) अणु
		हाल TX4927_CCFG_DIVMODE_2:
		हाल TX4927_CCFG_DIVMODE_8:
			cpuclk = txx9_gbus_घड़ी * 2; अवरोध;
		हाल TX4927_CCFG_DIVMODE_2_5:
		हाल TX4927_CCFG_DIVMODE_10:
			cpuclk = txx9_gbus_घड़ी * 5 / 2; अवरोध;
		हाल TX4927_CCFG_DIVMODE_3:
		हाल TX4927_CCFG_DIVMODE_12:
			cpuclk = txx9_gbus_घड़ी * 3; अवरोध;
		हाल TX4927_CCFG_DIVMODE_4:
		हाल TX4927_CCFG_DIVMODE_16:
			cpuclk = txx9_gbus_घड़ी * 4; अवरोध;
		पूर्ण
		txx9_cpu_घड़ी = cpuclk;
	पूर्ण अन्यथा अणु
		अगर (txx9_cpu_घड़ी == 0)
			txx9_cpu_घड़ी = 200000000;	/* 200MHz */
		/* calculate gbus_घड़ी and master_घड़ी from cpu_घड़ी */
		cpuclk = txx9_cpu_घड़ी;
		भागmode = (__u32)ccfg & TX4927_CCFG_DIVMODE_MASK;
		चयन (भागmode) अणु
		हाल TX4927_CCFG_DIVMODE_2:
		हाल TX4927_CCFG_DIVMODE_8:
			txx9_gbus_घड़ी = cpuclk / 2; अवरोध;
		हाल TX4927_CCFG_DIVMODE_2_5:
		हाल TX4927_CCFG_DIVMODE_10:
			txx9_gbus_घड़ी = cpuclk * 2 / 5; अवरोध;
		हाल TX4927_CCFG_DIVMODE_3:
		हाल TX4927_CCFG_DIVMODE_12:
			txx9_gbus_घड़ी = cpuclk / 3; अवरोध;
		हाल TX4927_CCFG_DIVMODE_4:
		हाल TX4927_CCFG_DIVMODE_16:
			txx9_gbus_घड़ी = cpuclk / 4; अवरोध;
		पूर्ण
		चयन (भागmode) अणु
		हाल TX4927_CCFG_DIVMODE_8:
		हाल TX4927_CCFG_DIVMODE_10:
		हाल TX4927_CCFG_DIVMODE_12:
		हाल TX4927_CCFG_DIVMODE_16:
			txx9_master_घड़ी = txx9_gbus_घड़ी / 4; अवरोध;
		शेष:
			txx9_master_घड़ी = txx9_gbus_घड़ी;
		पूर्ण
	पूर्ण
	/* change शेष value to udelay/mdelay take reasonable समय */
	loops_per_jअगरfy = txx9_cpu_घड़ी / HZ / 2;

	/* CCFG */
	tx4927_wdr_init();
	/* clear BusErrorOnWrite flag (W1C) */
	tx4927_ccfg_set(TX4927_CCFG_BEOW);
	/* enable Timeout BusError */
	अगर (txx9_ccfg_toeon)
		tx4927_ccfg_set(TX4927_CCFG_TOE);

	/* DMA selection */
	txx9_clear64(&tx4927_ccfgptr->pcfg, TX4927_PCFG_DMASEL_ALL);

	/* Use बाह्यal घड़ी क्रम बाह्यal arbiter */
	अगर (!(____raw_पढ़ोq(&tx4927_ccfgptr->ccfg) & TX4927_CCFG_PCIARB))
		txx9_clear64(&tx4927_ccfgptr->pcfg, TX4927_PCFG_PCICLKEN_ALL);

	pr_info("%s -- %dMHz(M%dMHz) CRIR:%08x CCFG:%llx PCFG:%llx\n",
		txx9_pcode_str, (cpuclk + 500000) / 1000000,
		(txx9_master_घड़ी + 500000) / 1000000,
		(__u32)____raw_पढ़ोq(&tx4927_ccfgptr->crir),
		____raw_पढ़ोq(&tx4927_ccfgptr->ccfg),
		____raw_पढ़ोq(&tx4927_ccfgptr->pcfg));

	pr_info("%s SDRAMC --", txx9_pcode_str);
	क्रम (i = 0; i < 4; i++) अणु
		__u64 cr = TX4927_SDRAMC_CR(i);
		अचिन्हित दीर्घ base, size;
		अगर (!((__u32)cr & 0x00000400))
			जारी;	/* disabled */
		base = (अचिन्हित दीर्घ)(cr >> 49) << 21;
		size = (((अचिन्हित दीर्घ)(cr >> 33) & 0x7fff) + 1) << 21;
		pr_cont(" CR%d:%016llx", i, cr);
		tx4927_sdram_resource[i].name = "SDRAM";
		tx4927_sdram_resource[i].start = base;
		tx4927_sdram_resource[i].end = base + size - 1;
		tx4927_sdram_resource[i].flags = IORESOURCE_MEM;
		request_resource(&iomem_resource, &tx4927_sdram_resource[i]);
	पूर्ण
	pr_cont(" TR:%09llx\n", ____raw_पढ़ोq(&tx4927_sdramcptr->tr));

	/* TMR */
	/* disable all समयrs */
	क्रम (i = 0; i < TX4927_NR_TMR; i++)
		txx9_पंचांगr_init(TX4927_TMR_REG(i) & 0xfffffffffULL);

	/* PIO */
	__raw_ग_लिखोl(0, &tx4927_pioptr->maskcpu);
	__raw_ग_लिखोl(0, &tx4927_pioptr->maskext);

	_machine_restart = tx4927_machine_restart;
	board_be_init = tx4927_be_init;
पूर्ण

व्योम __init tx4927_समय_init(अचिन्हित पूर्णांक पंचांगrnr)
अणु
	अगर (____raw_पढ़ोq(&tx4927_ccfgptr->ccfg) & TX4927_CCFG_TINTDIS)
		txx9_घड़ीevent_init(TX4927_TMR_REG(पंचांगrnr) & 0xfffffffffULL,
				     TXX9_IRQ_BASE + TX4927_IR_TMR(पंचांगrnr),
				     TXX9_IMCLK);
पूर्ण

व्योम __init tx4927_sio_init(अचिन्हित पूर्णांक sclk, अचिन्हित पूर्णांक cts_mask)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < 2; i++)
		txx9_sio_init(TX4927_SIO_REG(i) & 0xfffffffffULL,
			      TXX9_IRQ_BASE + TX4927_IR_SIO(i),
			      i, sclk, (1 << i) & cts_mask);
पूर्ण

व्योम __init tx4927_mtd_init(पूर्णांक ch)
अणु
	काष्ठा physmap_flash_data pdata = अणु
		.width = TX4927_EBUSC_WIDTH(ch) / 8,
	पूर्ण;
	अचिन्हित दीर्घ start = txx9_ce_res[ch].start;
	अचिन्हित दीर्घ size = txx9_ce_res[ch].end - start + 1;

	अगर (!(TX4927_EBUSC_CR(ch) & 0x8))
		वापस; /* disabled */
	txx9_physmap_flash_init(ch, start, size, &pdata);
पूर्ण

व्योम __init tx4927_dmac_init(पूर्णांक स_नकल_chan)
अणु
	काष्ठा txx9dmac_platक्रमm_data plat_data = अणु
		.स_नकल_chan = स_नकल_chan,
		.have_64bit_regs = true,
	पूर्ण;

	txx9_dmac_init(0, TX4927_DMA_REG & 0xfffffffffULL,
		       TXX9_IRQ_BASE + TX4927_IR_DMA(0), &plat_data);
पूर्ण

व्योम __init tx4927_aclc_init(अचिन्हित पूर्णांक dma_chan_out,
			     अचिन्हित पूर्णांक dma_chan_in)
अणु
	u64 pcfg = __raw_पढ़ोq(&tx4927_ccfgptr->pcfg);
	__u64 dmasel_mask = 0, dmasel = 0;
	अचिन्हित दीर्घ flags;

	अगर (!(pcfg & TX4927_PCFG_SEL2))
		वापस;
	/* setup DMASEL (playback:ACLC ch0, capture:ACLC ch1) */
	चयन (dma_chan_out) अणु
	हाल 0:
		dmasel_mask |= TX4927_PCFG_DMASEL0_MASK;
		dmasel |= TX4927_PCFG_DMASEL0_ACL0;
		अवरोध;
	हाल 2:
		dmasel_mask |= TX4927_PCFG_DMASEL2_MASK;
		dmasel |= TX4927_PCFG_DMASEL2_ACL0;
		अवरोध;
	शेष:
		वापस;
	पूर्ण
	चयन (dma_chan_in) अणु
	हाल 1:
		dmasel_mask |= TX4927_PCFG_DMASEL1_MASK;
		dmasel |= TX4927_PCFG_DMASEL1_ACL1;
		अवरोध;
	हाल 3:
		dmasel_mask |= TX4927_PCFG_DMASEL3_MASK;
		dmasel |= TX4927_PCFG_DMASEL3_ACL1;
		अवरोध;
	शेष:
		वापस;
	पूर्ण
	local_irq_save(flags);
	txx9_clear64(&tx4927_ccfgptr->pcfg, dmasel_mask);
	txx9_set64(&tx4927_ccfgptr->pcfg, dmasel);
	local_irq_restore(flags);
	txx9_aclc_init(TX4927_ACLC_REG & 0xfffffffffULL,
		       TXX9_IRQ_BASE + TX4927_IR_ACLC,
		       0, dma_chan_out, dma_chan_in);
पूर्ण

अटल व्योम __init tx4927_stop_unused_modules(व्योम)
अणु
	__u64 pcfg, rst = 0, ckd = 0;
	अक्षर buf[128];

	buf[0] = '\0';
	local_irq_disable();
	pcfg = ____raw_पढ़ोq(&tx4927_ccfgptr->pcfg);
	अगर (!(pcfg & TX4927_PCFG_SEL2)) अणु
		rst |= TX4927_CLKCTR_ACLRST;
		ckd |= TX4927_CLKCTR_ACLCKD;
		म_जोड़ो(buf, " ACLC");
	पूर्ण
	अगर (rst | ckd) अणु
		txx9_set64(&tx4927_ccfgptr->clkctr, rst);
		txx9_set64(&tx4927_ccfgptr->clkctr, ckd);
	पूर्ण
	local_irq_enable();
	अगर (buf[0])
		pr_info("%s: stop%s\n", txx9_pcode_str, buf);
पूर्ण

अटल पूर्णांक __init tx4927_late_init(व्योम)
अणु
	अगर (txx9_pcode != 0x4927)
		वापस -ENODEV;
	tx4927_stop_unused_modules();
	वापस 0;
पूर्ण
late_initcall(tx4927_late_init);
