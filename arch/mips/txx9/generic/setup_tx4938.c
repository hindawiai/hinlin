<शैली गुरु>
/*
 * TX4938/4937 setup routines
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
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/platक्रमm_data/txx9/ndfmc.h>
#समावेश <यंत्र/reboot.h>
#समावेश <यंत्र/traps.h>
#समावेश <यंत्र/txx9irq.h>
#समावेश <यंत्र/txx9पंचांगr.h>
#समावेश <यंत्र/txx9pपन.स>
#समावेश <यंत्र/txx9/generic.h>
#समावेश <यंत्र/txx9/dmac.h>
#समावेश <यंत्र/txx9/tx4938.h>

अटल व्योम __init tx4938_wdr_init(व्योम)
अणु
	/* report watchकरोg reset status */
	अगर (____raw_पढ़ोq(&tx4938_ccfgptr->ccfg) & TX4938_CCFG_WDRST)
		pr_warn("Watchdog reset detected at 0x%lx\n",
			पढ़ो_c0_errorepc());
	/* clear WatchDogReset (W1C) */
	tx4938_ccfg_set(TX4938_CCFG_WDRST);
	/* करो reset on watchकरोg */
	tx4938_ccfg_set(TX4938_CCFG_WR);
पूर्ण

व्योम __init tx4938_wdt_init(व्योम)
अणु
	txx9_wdt_init(TX4938_TMR_REG(2) & 0xfffffffffULL);
पूर्ण

अटल व्योम tx4938_machine_restart(अक्षर *command)
अणु
	local_irq_disable();
	pr_emerg("Rebooting (with %s watchdog reset)...\n",
		 (____raw_पढ़ोq(&tx4938_ccfgptr->ccfg) & TX4938_CCFG_WDREXEN) ?
		 "external" : "internal");
	/* clear watchकरोg status */
	tx4938_ccfg_set(TX4938_CCFG_WDRST);	/* W1C */
	txx9_wdt_now(TX4938_TMR_REG(2) & 0xfffffffffULL);
	जबतक (!(____raw_पढ़ोq(&tx4938_ccfgptr->ccfg) & TX4938_CCFG_WDRST))
		;
	mdelay(10);
	अगर (____raw_पढ़ोq(&tx4938_ccfgptr->ccfg) & TX4938_CCFG_WDREXEN) अणु
		pr_emerg("Rebooting (with internal watchdog reset)...\n");
		/* External WDRST failed.  Do पूर्णांकernal watchकरोg reset */
		tx4938_ccfg_clear(TX4938_CCFG_WDREXEN);
	पूर्ण
	/* fallback */
	(*_machine_halt)();
पूर्ण

व्योम show_रेजिस्टरs(काष्ठा pt_regs *regs);
अटल पूर्णांक tx4938_be_handler(काष्ठा pt_regs *regs, पूर्णांक is_fixup)
अणु
	पूर्णांक data = regs->cp0_cause & 4;
	console_verbose();
	pr_err("%cBE exception at %#lx\n", data ? 'D' : 'I', regs->cp0_epc);
	pr_err("ccfg:%llx, toea:%llx\n",
	       (अचिन्हित दीर्घ दीर्घ)____raw_पढ़ोq(&tx4938_ccfgptr->ccfg),
	       (अचिन्हित दीर्घ दीर्घ)____raw_पढ़ोq(&tx4938_ccfgptr->toea));
#अगर_घोषित CONFIG_PCI
	tx4927_report_pcic_status();
#पूर्ण_अगर
	show_रेजिस्टरs(regs);
	panic("BusError!");
पूर्ण
अटल व्योम __init tx4938_be_init(व्योम)
अणु
	board_be_handler = tx4938_be_handler;
पूर्ण

अटल काष्ठा resource tx4938_sdram_resource[4];
अटल काष्ठा resource tx4938_sram_resource;

#घोषणा TX4938_SRAM_SIZE 0x800

व्योम __init tx4938_setup(व्योम)
अणु
	पूर्णांक i;
	__u32 भागmode;
	अचिन्हित पूर्णांक cpuclk = 0;
	u64 ccfg;

	txx9_reg_res_init(TX4938_REV_PCODE(), TX4938_REG_BASE,
			  TX4938_REG_SIZE);
	set_c0_config(TX49_CONF_CWFON);

	/* SDRAMC,EBUSC are configured by PROM */
	क्रम (i = 0; i < 8; i++) अणु
		अगर (!(TX4938_EBUSC_CR(i) & 0x8))
			जारी;	/* disabled */
		txx9_ce_res[i].start = (अचिन्हित दीर्घ)TX4938_EBUSC_BA(i);
		txx9_ce_res[i].end =
			txx9_ce_res[i].start + TX4938_EBUSC_SIZE(i) - 1;
		request_resource(&iomem_resource, &txx9_ce_res[i]);
	पूर्ण

	/* घड़ीs */
	ccfg = ____raw_पढ़ोq(&tx4938_ccfgptr->ccfg);
	अगर (txx9_master_घड़ी) अणु
		/* calculate gbus_घड़ी and cpu_घड़ी from master_घड़ी */
		भागmode = (__u32)ccfg & TX4938_CCFG_DIVMODE_MASK;
		चयन (भागmode) अणु
		हाल TX4938_CCFG_DIVMODE_8:
		हाल TX4938_CCFG_DIVMODE_10:
		हाल TX4938_CCFG_DIVMODE_12:
		हाल TX4938_CCFG_DIVMODE_16:
		हाल TX4938_CCFG_DIVMODE_18:
			txx9_gbus_घड़ी = txx9_master_घड़ी * 4; अवरोध;
		शेष:
			txx9_gbus_घड़ी = txx9_master_घड़ी;
		पूर्ण
		चयन (भागmode) अणु
		हाल TX4938_CCFG_DIVMODE_2:
		हाल TX4938_CCFG_DIVMODE_8:
			cpuclk = txx9_gbus_घड़ी * 2; अवरोध;
		हाल TX4938_CCFG_DIVMODE_2_5:
		हाल TX4938_CCFG_DIVMODE_10:
			cpuclk = txx9_gbus_घड़ी * 5 / 2; अवरोध;
		हाल TX4938_CCFG_DIVMODE_3:
		हाल TX4938_CCFG_DIVMODE_12:
			cpuclk = txx9_gbus_घड़ी * 3; अवरोध;
		हाल TX4938_CCFG_DIVMODE_4:
		हाल TX4938_CCFG_DIVMODE_16:
			cpuclk = txx9_gbus_घड़ी * 4; अवरोध;
		हाल TX4938_CCFG_DIVMODE_4_5:
		हाल TX4938_CCFG_DIVMODE_18:
			cpuclk = txx9_gbus_घड़ी * 9 / 2; अवरोध;
		पूर्ण
		txx9_cpu_घड़ी = cpuclk;
	पूर्ण अन्यथा अणु
		अगर (txx9_cpu_घड़ी == 0)
			txx9_cpu_घड़ी = 300000000;	/* 300MHz */
		/* calculate gbus_घड़ी and master_घड़ी from cpu_घड़ी */
		cpuclk = txx9_cpu_घड़ी;
		भागmode = (__u32)ccfg & TX4938_CCFG_DIVMODE_MASK;
		चयन (भागmode) अणु
		हाल TX4938_CCFG_DIVMODE_2:
		हाल TX4938_CCFG_DIVMODE_8:
			txx9_gbus_घड़ी = cpuclk / 2; अवरोध;
		हाल TX4938_CCFG_DIVMODE_2_5:
		हाल TX4938_CCFG_DIVMODE_10:
			txx9_gbus_घड़ी = cpuclk * 2 / 5; अवरोध;
		हाल TX4938_CCFG_DIVMODE_3:
		हाल TX4938_CCFG_DIVMODE_12:
			txx9_gbus_घड़ी = cpuclk / 3; अवरोध;
		हाल TX4938_CCFG_DIVMODE_4:
		हाल TX4938_CCFG_DIVMODE_16:
			txx9_gbus_घड़ी = cpuclk / 4; अवरोध;
		हाल TX4938_CCFG_DIVMODE_4_5:
		हाल TX4938_CCFG_DIVMODE_18:
			txx9_gbus_घड़ी = cpuclk * 2 / 9; अवरोध;
		पूर्ण
		चयन (भागmode) अणु
		हाल TX4938_CCFG_DIVMODE_8:
		हाल TX4938_CCFG_DIVMODE_10:
		हाल TX4938_CCFG_DIVMODE_12:
		हाल TX4938_CCFG_DIVMODE_16:
		हाल TX4938_CCFG_DIVMODE_18:
			txx9_master_घड़ी = txx9_gbus_घड़ी / 4; अवरोध;
		शेष:
			txx9_master_घड़ी = txx9_gbus_घड़ी;
		पूर्ण
	पूर्ण
	/* change शेष value to udelay/mdelay take reasonable समय */
	loops_per_jअगरfy = txx9_cpu_घड़ी / HZ / 2;

	/* CCFG */
	tx4938_wdr_init();
	/* clear BusErrorOnWrite flag (W1C) */
	tx4938_ccfg_set(TX4938_CCFG_BEOW);
	/* enable Timeout BusError */
	अगर (txx9_ccfg_toeon)
		tx4938_ccfg_set(TX4938_CCFG_TOE);

	/* DMA selection */
	txx9_clear64(&tx4938_ccfgptr->pcfg, TX4938_PCFG_DMASEL_ALL);

	/* Use बाह्यal घड़ी क्रम बाह्यal arbiter */
	अगर (!(____raw_पढ़ोq(&tx4938_ccfgptr->ccfg) & TX4938_CCFG_PCIARB))
		txx9_clear64(&tx4938_ccfgptr->pcfg, TX4938_PCFG_PCICLKEN_ALL);

	pr_info("%s -- %dMHz(M%dMHz) CRIR:%08x CCFG:%llx PCFG:%llx\n",
		txx9_pcode_str, (cpuclk + 500000) / 1000000,
		(txx9_master_घड़ी + 500000) / 1000000,
		(__u32)____raw_पढ़ोq(&tx4938_ccfgptr->crir),
		____raw_पढ़ोq(&tx4938_ccfgptr->ccfg),
		____raw_पढ़ोq(&tx4938_ccfgptr->pcfg));

	pr_info("%s SDRAMC --", txx9_pcode_str);
	क्रम (i = 0; i < 4; i++) अणु
		__u64 cr = TX4938_SDRAMC_CR(i);
		अचिन्हित दीर्घ base, size;
		अगर (!((__u32)cr & 0x00000400))
			जारी;	/* disabled */
		base = (अचिन्हित दीर्घ)(cr >> 49) << 21;
		size = (((अचिन्हित दीर्घ)(cr >> 33) & 0x7fff) + 1) << 21;
		pr_cont(" CR%d:%016llx", i, cr);
		tx4938_sdram_resource[i].name = "SDRAM";
		tx4938_sdram_resource[i].start = base;
		tx4938_sdram_resource[i].end = base + size - 1;
		tx4938_sdram_resource[i].flags = IORESOURCE_MEM;
		request_resource(&iomem_resource, &tx4938_sdram_resource[i]);
	पूर्ण
	pr_cont(" TR:%09llx\n", ____raw_पढ़ोq(&tx4938_sdramcptr->tr));

	/* SRAM */
	अगर (txx9_pcode == 0x4938 && ____raw_पढ़ोq(&tx4938_sramcptr->cr) & 1) अणु
		अचिन्हित पूर्णांक size = TX4938_SRAM_SIZE;
		tx4938_sram_resource.name = "SRAM";
		tx4938_sram_resource.start =
			(____raw_पढ़ोq(&tx4938_sramcptr->cr) >> (39-11))
			& ~(size - 1);
		tx4938_sram_resource.end =
			tx4938_sram_resource.start + TX4938_SRAM_SIZE - 1;
		tx4938_sram_resource.flags = IORESOURCE_MEM;
		request_resource(&iomem_resource, &tx4938_sram_resource);
	पूर्ण

	/* TMR */
	/* disable all समयrs */
	क्रम (i = 0; i < TX4938_NR_TMR; i++)
		txx9_पंचांगr_init(TX4938_TMR_REG(i) & 0xfffffffffULL);

	/* PIO */
	__raw_ग_लिखोl(0, &tx4938_pioptr->maskcpu);
	__raw_ग_लिखोl(0, &tx4938_pioptr->maskext);

	अगर (txx9_pcode == 0x4938) अणु
		__u64 pcfg = ____raw_पढ़ोq(&tx4938_ccfgptr->pcfg);
		/* set PCIC1 reset */
		txx9_set64(&tx4938_ccfgptr->clkctr, TX4938_CLKCTR_PCIC1RST);
		अगर (pcfg & (TX4938_PCFG_ETH0_SEL | TX4938_PCFG_ETH1_SEL)) अणु
			mdelay(1);	/* at least 128 cpu घड़ी */
			/* clear PCIC1 reset */
			txx9_clear64(&tx4938_ccfgptr->clkctr,
				     TX4938_CLKCTR_PCIC1RST);
		पूर्ण अन्यथा अणु
			pr_info("%s: stop PCIC1\n", txx9_pcode_str);
			/* stop PCIC1 */
			txx9_set64(&tx4938_ccfgptr->clkctr,
				   TX4938_CLKCTR_PCIC1CKD);
		पूर्ण
		अगर (!(pcfg & TX4938_PCFG_ETH0_SEL)) अणु
			pr_info("%s: stop ETH0\n", txx9_pcode_str);
			txx9_set64(&tx4938_ccfgptr->clkctr,
				   TX4938_CLKCTR_ETH0RST);
			txx9_set64(&tx4938_ccfgptr->clkctr,
				   TX4938_CLKCTR_ETH0CKD);
		पूर्ण
		अगर (!(pcfg & TX4938_PCFG_ETH1_SEL)) अणु
			pr_info("%s: stop ETH1\n", txx9_pcode_str);
			txx9_set64(&tx4938_ccfgptr->clkctr,
				   TX4938_CLKCTR_ETH1RST);
			txx9_set64(&tx4938_ccfgptr->clkctr,
				   TX4938_CLKCTR_ETH1CKD);
		पूर्ण
	पूर्ण

	_machine_restart = tx4938_machine_restart;
	board_be_init = tx4938_be_init;
पूर्ण

व्योम __init tx4938_समय_init(अचिन्हित पूर्णांक पंचांगrnr)
अणु
	अगर (____raw_पढ़ोq(&tx4938_ccfgptr->ccfg) & TX4938_CCFG_TINTDIS)
		txx9_घड़ीevent_init(TX4938_TMR_REG(पंचांगrnr) & 0xfffffffffULL,
				     TXX9_IRQ_BASE + TX4938_IR_TMR(पंचांगrnr),
				     TXX9_IMCLK);
पूर्ण

व्योम __init tx4938_sio_init(अचिन्हित पूर्णांक sclk, अचिन्हित पूर्णांक cts_mask)
अणु
	पूर्णांक i;
	अचिन्हित पूर्णांक ch_mask = 0;

	अगर (__raw_पढ़ोq(&tx4938_ccfgptr->pcfg) & TX4938_PCFG_ETH0_SEL)
		ch_mask |= 1 << 1; /* disable SIO1 by PCFG setting */
	क्रम (i = 0; i < 2; i++) अणु
		अगर ((1 << i) & ch_mask)
			जारी;
		txx9_sio_init(TX4938_SIO_REG(i) & 0xfffffffffULL,
			      TXX9_IRQ_BASE + TX4938_IR_SIO(i),
			      i, sclk, (1 << i) & cts_mask);
	पूर्ण
पूर्ण

व्योम __init tx4938_spi_init(पूर्णांक busid)
अणु
	txx9_spi_init(busid, TX4938_SPI_REG & 0xfffffffffULL,
		      TXX9_IRQ_BASE + TX4938_IR_SPI);
पूर्ण

व्योम __init tx4938_ethaddr_init(अचिन्हित अक्षर *addr0, अचिन्हित अक्षर *addr1)
अणु
	u64 pcfg = __raw_पढ़ोq(&tx4938_ccfgptr->pcfg);

	अगर (addr0 && (pcfg & TX4938_PCFG_ETH0_SEL))
		txx9_ethaddr_init(TXX9_IRQ_BASE + TX4938_IR_ETH0, addr0);
	अगर (addr1 && (pcfg & TX4938_PCFG_ETH1_SEL))
		txx9_ethaddr_init(TXX9_IRQ_BASE + TX4938_IR_ETH1, addr1);
पूर्ण

व्योम __init tx4938_mtd_init(पूर्णांक ch)
अणु
	काष्ठा physmap_flash_data pdata = अणु
		.width = TX4938_EBUSC_WIDTH(ch) / 8,
	पूर्ण;
	अचिन्हित दीर्घ start = txx9_ce_res[ch].start;
	अचिन्हित दीर्घ size = txx9_ce_res[ch].end - start + 1;

	अगर (!(TX4938_EBUSC_CR(ch) & 0x8))
		वापस; /* disabled */
	txx9_physmap_flash_init(ch, start, size, &pdata);
पूर्ण

व्योम __init tx4938_ata_init(अचिन्हित पूर्णांक irq, अचिन्हित पूर्णांक shअगरt, पूर्णांक tune)
अणु
	काष्ठा platक्रमm_device *pdev;
	काष्ठा resource res[] = अणु
		अणु
			/* .start and .end are filled in later */
			.flags = IORESOURCE_MEM,
		पूर्ण, अणु
			.start = irq,
			.flags = IORESOURCE_IRQ,
		पूर्ण,
	पूर्ण;
	काष्ठा tx4938ide_platक्रमm_info pdata = अणु
		.ioport_shअगरt = shअगरt,
		/*
		 * The IDE driver should not change bus timings अगर other ISA
		 * devices existed.
		 */
		.gbus_घड़ी = tune ? txx9_gbus_घड़ी : 0,
	पूर्ण;
	u64 ebccr;
	पूर्णांक i;

	अगर ((__raw_पढ़ोq(&tx4938_ccfgptr->pcfg) &
	     (TX4938_PCFG_ATA_SEL | TX4938_PCFG_NDF_SEL))
	    != TX4938_PCFG_ATA_SEL)
		वापस;
	क्रम (i = 0; i < 8; i++) अणु
		/* check EBCCRn.ISA, EBCCRn.BSZ, EBCCRn.ME */
		ebccr = __raw_पढ़ोq(&tx4938_ebuscptr->cr[i]);
		अगर ((ebccr & 0x00f00008) == 0x00e00008)
			अवरोध;
	पूर्ण
	अगर (i == 8)
		वापस;
	pdata.ebus_ch = i;
	res[0].start = ((ebccr >> 48) << 20) + 0x10000;
	res[0].end = res[0].start + 0x20000 - 1;
	pdev = platक्रमm_device_alloc("tx4938ide", -1);
	अगर (!pdev ||
	    platक्रमm_device_add_resources(pdev, res, ARRAY_SIZE(res)) ||
	    platक्रमm_device_add_data(pdev, &pdata, माप(pdata)) ||
	    platक्रमm_device_add(pdev))
		platक्रमm_device_put(pdev);
पूर्ण

व्योम __init tx4938_ndfmc_init(अचिन्हित पूर्णांक hold, अचिन्हित पूर्णांक spw)
अणु
	काष्ठा txx9ndfmc_platक्रमm_data plat_data = अणु
		.shअगरt = 1,
		.gbus_घड़ी = txx9_gbus_घड़ी,
		.hold = hold,
		.spw = spw,
		.ch_mask = 1,
	पूर्ण;
	अचिन्हित दीर्घ baseaddr = TX4938_NDFMC_REG & 0xfffffffffULL;

#अगर_घोषित __BIG_ENDIAN
	baseaddr += 4;
#पूर्ण_अगर
	अगर ((__raw_पढ़ोq(&tx4938_ccfgptr->pcfg) &
	     (TX4938_PCFG_ATA_SEL|TX4938_PCFG_ISA_SEL|TX4938_PCFG_NDF_SEL)) ==
	    TX4938_PCFG_NDF_SEL)
		txx9_ndfmc_init(baseaddr, &plat_data);
पूर्ण

व्योम __init tx4938_dmac_init(पूर्णांक स_नकल_chan0, पूर्णांक स_नकल_chan1)
अणु
	काष्ठा txx9dmac_platक्रमm_data plat_data = अणु
		.have_64bit_regs = true,
	पूर्ण;
	पूर्णांक i;

	क्रम (i = 0; i < 2; i++) अणु
		plat_data.स_नकल_chan = i ? स_नकल_chan1 : स_नकल_chan0;
		txx9_dmac_init(i, TX4938_DMA_REG(i) & 0xfffffffffULL,
			       TXX9_IRQ_BASE + TX4938_IR_DMA(i, 0),
			       &plat_data);
	पूर्ण
पूर्ण

व्योम __init tx4938_aclc_init(व्योम)
अणु
	u64 pcfg = __raw_पढ़ोq(&tx4938_ccfgptr->pcfg);

	अगर ((pcfg & TX4938_PCFG_SEL2) &&
	    !(pcfg & TX4938_PCFG_ETH0_SEL))
		txx9_aclc_init(TX4938_ACLC_REG & 0xfffffffffULL,
			       TXX9_IRQ_BASE + TX4938_IR_ACLC,
			       1, 0, 1);
पूर्ण

व्योम __init tx4938_sramc_init(व्योम)
अणु
	अगर (tx4938_sram_resource.start)
		txx9_sramc_init(&tx4938_sram_resource);
पूर्ण

अटल व्योम __init tx4938_stop_unused_modules(व्योम)
अणु
	__u64 pcfg, rst = 0, ckd = 0;
	अक्षर buf[128];

	buf[0] = '\0';
	local_irq_disable();
	pcfg = ____raw_पढ़ोq(&tx4938_ccfgptr->pcfg);
	चयन (txx9_pcode) अणु
	हाल 0x4937:
		अगर (!(pcfg & TX4938_PCFG_SEL2)) अणु
			rst |= TX4938_CLKCTR_ACLRST;
			ckd |= TX4938_CLKCTR_ACLCKD;
			म_जोड़ो(buf, " ACLC");
		पूर्ण
		अवरोध;
	हाल 0x4938:
		अगर (!(pcfg & TX4938_PCFG_SEL2) ||
		    (pcfg & TX4938_PCFG_ETH0_SEL)) अणु
			rst |= TX4938_CLKCTR_ACLRST;
			ckd |= TX4938_CLKCTR_ACLCKD;
			म_जोड़ो(buf, " ACLC");
		पूर्ण
		अगर ((pcfg &
		     (TX4938_PCFG_ATA_SEL | TX4938_PCFG_ISA_SEL |
		      TX4938_PCFG_NDF_SEL))
		    != TX4938_PCFG_NDF_SEL) अणु
			rst |= TX4938_CLKCTR_NDFRST;
			ckd |= TX4938_CLKCTR_NDFCKD;
			म_जोड़ो(buf, " NDFMC");
		पूर्ण
		अगर (!(pcfg & TX4938_PCFG_SPI_SEL)) अणु
			rst |= TX4938_CLKCTR_SPIRST;
			ckd |= TX4938_CLKCTR_SPICKD;
			म_जोड़ो(buf, " SPI");
		पूर्ण
		अवरोध;
	पूर्ण
	अगर (rst | ckd) अणु
		txx9_set64(&tx4938_ccfgptr->clkctr, rst);
		txx9_set64(&tx4938_ccfgptr->clkctr, ckd);
	पूर्ण
	local_irq_enable();
	अगर (buf[0])
		pr_info("%s: stop%s\n", txx9_pcode_str, buf);
पूर्ण

अटल पूर्णांक __init tx4938_late_init(व्योम)
अणु
	अगर (txx9_pcode != 0x4937 && txx9_pcode != 0x4938)
		वापस -ENODEV;
	tx4938_stop_unused_modules();
	वापस 0;
पूर्ण
late_initcall(tx4938_late_init);
