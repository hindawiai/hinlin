<शैली गुरु>
/*
 * TX4939 setup routines
 * Based on linux/arch/mips/txx9/generic/setup_tx4938.c,
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
#समावेश <linux/netdevice.h>
#समावेश <linux/notअगरier.h>
#समावेश <linux/device.h>
#समावेश <linux/ethtool.h>
#समावेश <linux/param.h>
#समावेश <linux/ptrace.h>
#समावेश <linux/mtd/physmap.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/platक्रमm_data/txx9/ndfmc.h>
#समावेश <यंत्र/reboot.h>
#समावेश <यंत्र/traps.h>
#समावेश <यंत्र/txx9irq.h>
#समावेश <यंत्र/txx9पंचांगr.h>
#समावेश <यंत्र/txx9/generic.h>
#समावेश <यंत्र/txx9/dmac.h>
#समावेश <यंत्र/txx9/tx4939.h>

अटल व्योम __init tx4939_wdr_init(व्योम)
अणु
	/* report watchकरोg reset status */
	अगर (____raw_पढ़ोq(&tx4939_ccfgptr->ccfg) & TX4939_CCFG_WDRST)
		pr_warn("Watchdog reset detected at 0x%lx\n",
			पढ़ो_c0_errorepc());
	/* clear WatchDogReset (W1C) */
	tx4939_ccfg_set(TX4939_CCFG_WDRST);
	/* करो reset on watchकरोg */
	tx4939_ccfg_set(TX4939_CCFG_WR);
पूर्ण

व्योम __init tx4939_wdt_init(व्योम)
अणु
	txx9_wdt_init(TX4939_TMR_REG(2) & 0xfffffffffULL);
पूर्ण

अटल व्योम tx4939_machine_restart(अक्षर *command)
अणु
	local_irq_disable();
	pr_emerg("Rebooting (with %s watchdog reset)...\n",
		 (____raw_पढ़ोq(&tx4939_ccfgptr->ccfg) & TX4939_CCFG_WDREXEN) ?
		 "external" : "internal");
	/* clear watchकरोg status */
	tx4939_ccfg_set(TX4939_CCFG_WDRST);	/* W1C */
	txx9_wdt_now(TX4939_TMR_REG(2) & 0xfffffffffULL);
	जबतक (!(____raw_पढ़ोq(&tx4939_ccfgptr->ccfg) & TX4939_CCFG_WDRST))
		;
	mdelay(10);
	अगर (____raw_पढ़ोq(&tx4939_ccfgptr->ccfg) & TX4939_CCFG_WDREXEN) अणु
		pr_emerg("Rebooting (with internal watchdog reset)...\n");
		/* External WDRST failed.  Do पूर्णांकernal watchकरोg reset */
		tx4939_ccfg_clear(TX4939_CCFG_WDREXEN);
	पूर्ण
	/* fallback */
	(*_machine_halt)();
पूर्ण

व्योम show_रेजिस्टरs(काष्ठा pt_regs *regs);
अटल पूर्णांक tx4939_be_handler(काष्ठा pt_regs *regs, पूर्णांक is_fixup)
अणु
	पूर्णांक data = regs->cp0_cause & 4;
	console_verbose();
	pr_err("%cBE exception at %#lx\n",
	       data ? 'D' : 'I', regs->cp0_epc);
	pr_err("ccfg:%llx, toea:%llx\n",
	       (अचिन्हित दीर्घ दीर्घ)____raw_पढ़ोq(&tx4939_ccfgptr->ccfg),
	       (अचिन्हित दीर्घ दीर्घ)____raw_पढ़ोq(&tx4939_ccfgptr->toea));
#अगर_घोषित CONFIG_PCI
	tx4927_report_pcic_status();
#पूर्ण_अगर
	show_रेजिस्टरs(regs);
	panic("BusError!");
पूर्ण
अटल व्योम __init tx4939_be_init(व्योम)
अणु
	board_be_handler = tx4939_be_handler;
पूर्ण

अटल काष्ठा resource tx4939_sdram_resource[4];
अटल काष्ठा resource tx4939_sram_resource;
#घोषणा TX4939_SRAM_SIZE 0x800

व्योम __init tx4939_setup(व्योम)
अणु
	पूर्णांक i;
	__u32 भागmode;
	__u64 pcfg;
	अचिन्हित पूर्णांक cpuclk = 0;

	txx9_reg_res_init(TX4939_REV_PCODE(), TX4939_REG_BASE,
			  TX4939_REG_SIZE);
	set_c0_config(TX49_CONF_CWFON);

	/* SDRAMC,EBUSC are configured by PROM */
	क्रम (i = 0; i < 4; i++) अणु
		अगर (!(TX4939_EBUSC_CR(i) & 0x8))
			जारी;	/* disabled */
		txx9_ce_res[i].start = (अचिन्हित दीर्घ)TX4939_EBUSC_BA(i);
		txx9_ce_res[i].end =
			txx9_ce_res[i].start + TX4939_EBUSC_SIZE(i) - 1;
		request_resource(&iomem_resource, &txx9_ce_res[i]);
	पूर्ण

	/* घड़ीs */
	अगर (txx9_master_घड़ी) अणु
		/* calculate cpu_घड़ी from master_घड़ी */
		भागmode = (__u32)____raw_पढ़ोq(&tx4939_ccfgptr->ccfg) &
			TX4939_CCFG_MULCLK_MASK;
		cpuclk = txx9_master_घड़ी * 20 / 2;
		चयन (भागmode) अणु
		हाल TX4939_CCFG_MULCLK_8:
			cpuclk = cpuclk / 3 * 4 /* / 6 *  8 */; अवरोध;
		हाल TX4939_CCFG_MULCLK_9:
			cpuclk = cpuclk / 2 * 3 /* / 6 *  9 */; अवरोध;
		हाल TX4939_CCFG_MULCLK_10:
			cpuclk = cpuclk / 3 * 5 /* / 6 * 10 */; अवरोध;
		हाल TX4939_CCFG_MULCLK_11:
			cpuclk = cpuclk / 6 * 11; अवरोध;
		हाल TX4939_CCFG_MULCLK_12:
			cpuclk = cpuclk * 2 /* / 6 * 12 */; अवरोध;
		हाल TX4939_CCFG_MULCLK_13:
			cpuclk = cpuclk / 6 * 13; अवरोध;
		हाल TX4939_CCFG_MULCLK_14:
			cpuclk = cpuclk / 3 * 7 /* / 6 * 14 */; अवरोध;
		हाल TX4939_CCFG_MULCLK_15:
			cpuclk = cpuclk / 2 * 5 /* / 6 * 15 */; अवरोध;
		पूर्ण
		txx9_cpu_घड़ी = cpuclk;
	पूर्ण अन्यथा अणु
		अगर (txx9_cpu_घड़ी == 0)
			txx9_cpu_घड़ी = 400000000;	/* 400MHz */
		/* calculate master_घड़ी from cpu_घड़ी */
		cpuclk = txx9_cpu_घड़ी;
		भागmode = (__u32)____raw_पढ़ोq(&tx4939_ccfgptr->ccfg) &
			TX4939_CCFG_MULCLK_MASK;
		चयन (भागmode) अणु
		हाल TX4939_CCFG_MULCLK_8:
			txx9_master_घड़ी = cpuclk * 6 / 8; अवरोध;
		हाल TX4939_CCFG_MULCLK_9:
			txx9_master_घड़ी = cpuclk * 6 / 9; अवरोध;
		हाल TX4939_CCFG_MULCLK_10:
			txx9_master_घड़ी = cpuclk * 6 / 10; अवरोध;
		हाल TX4939_CCFG_MULCLK_11:
			txx9_master_घड़ी = cpuclk * 6 / 11; अवरोध;
		हाल TX4939_CCFG_MULCLK_12:
			txx9_master_घड़ी = cpuclk * 6 / 12; अवरोध;
		हाल TX4939_CCFG_MULCLK_13:
			txx9_master_घड़ी = cpuclk * 6 / 13; अवरोध;
		हाल TX4939_CCFG_MULCLK_14:
			txx9_master_घड़ी = cpuclk * 6 / 14; अवरोध;
		हाल TX4939_CCFG_MULCLK_15:
			txx9_master_घड़ी = cpuclk * 6 / 15; अवरोध;
		पूर्ण
		txx9_master_घड़ी /= 10; /* * 2 / 20 */
	पूर्ण
	/* calculate gbus_घड़ी from cpu_घड़ी */
	भागmode = (__u32)____raw_पढ़ोq(&tx4939_ccfgptr->ccfg) &
		TX4939_CCFG_YDIVMODE_MASK;
	txx9_gbus_घड़ी = txx9_cpu_घड़ी;
	चयन (भागmode) अणु
	हाल TX4939_CCFG_YDIVMODE_2:
		txx9_gbus_घड़ी /= 2; अवरोध;
	हाल TX4939_CCFG_YDIVMODE_3:
		txx9_gbus_घड़ी /= 3; अवरोध;
	हाल TX4939_CCFG_YDIVMODE_5:
		txx9_gbus_घड़ी /= 5; अवरोध;
	हाल TX4939_CCFG_YDIVMODE_6:
		txx9_gbus_घड़ी /= 6; अवरोध;
	पूर्ण
	/* change शेष value to udelay/mdelay take reasonable समय */
	loops_per_jअगरfy = txx9_cpu_घड़ी / HZ / 2;

	/* CCFG */
	tx4939_wdr_init();
	/* clear BusErrorOnWrite flag (W1C) */
	tx4939_ccfg_set(TX4939_CCFG_WDRST | TX4939_CCFG_BEOW);
	/* enable Timeout BusError */
	अगर (txx9_ccfg_toeon)
		tx4939_ccfg_set(TX4939_CCFG_TOE);

	/* DMA selection */
	txx9_clear64(&tx4939_ccfgptr->pcfg, TX4939_PCFG_DMASEL_ALL);

	/* Use बाह्यal घड़ी क्रम बाह्यal arbiter */
	अगर (!(____raw_पढ़ोq(&tx4939_ccfgptr->ccfg) & TX4939_CCFG_PCIARB))
		txx9_clear64(&tx4939_ccfgptr->pcfg, TX4939_PCFG_PCICLKEN_ALL);

	pr_info("%s -- %dMHz(M%dMHz,G%dMHz) CRIR:%08x CCFG:%llx PCFG:%llx\n",
		txx9_pcode_str,
		(cpuclk + 500000) / 1000000,
		(txx9_master_घड़ी + 500000) / 1000000,
		(txx9_gbus_घड़ी + 500000) / 1000000,
		(__u32)____raw_पढ़ोq(&tx4939_ccfgptr->crir),
		____raw_पढ़ोq(&tx4939_ccfgptr->ccfg),
		____raw_पढ़ोq(&tx4939_ccfgptr->pcfg));

	pr_info("%s DDRC -- EN:%08x", txx9_pcode_str,
		(__u32)____raw_पढ़ोq(&tx4939_ddrcptr->winen));
	क्रम (i = 0; i < 4; i++) अणु
		__u64 win = ____raw_पढ़ोq(&tx4939_ddrcptr->win[i]);
		अगर (!((__u32)____raw_पढ़ोq(&tx4939_ddrcptr->winen) & (1 << i)))
			जारी;	/* disabled */
		pr_cont(" #%d:%016llx", i, win);
		tx4939_sdram_resource[i].name = "DDR SDRAM";
		tx4939_sdram_resource[i].start =
			(अचिन्हित दीर्घ)(win >> 48) << 20;
		tx4939_sdram_resource[i].end =
			((((अचिन्हित दीर्घ)(win >> 32) & 0xffff) + 1) <<
			 20) - 1;
		tx4939_sdram_resource[i].flags = IORESOURCE_MEM;
		request_resource(&iomem_resource, &tx4939_sdram_resource[i]);
	पूर्ण
	pr_cont("\n");

	/* SRAM */
	अगर (____raw_पढ़ोq(&tx4939_sramcptr->cr) & 1) अणु
		अचिन्हित पूर्णांक size = TX4939_SRAM_SIZE;
		tx4939_sram_resource.name = "SRAM";
		tx4939_sram_resource.start =
			(____raw_पढ़ोq(&tx4939_sramcptr->cr) >> (39-11))
			& ~(size - 1);
		tx4939_sram_resource.end =
			tx4939_sram_resource.start + TX4939_SRAM_SIZE - 1;
		tx4939_sram_resource.flags = IORESOURCE_MEM;
		request_resource(&iomem_resource, &tx4939_sram_resource);
	पूर्ण

	/* TMR */
	/* disable all समयrs */
	क्रम (i = 0; i < TX4939_NR_TMR; i++)
		txx9_पंचांगr_init(TX4939_TMR_REG(i) & 0xfffffffffULL);

	/* set PCIC1 reset (required to prevent hangup on BIST) */
	txx9_set64(&tx4939_ccfgptr->clkctr, TX4939_CLKCTR_PCI1RST);
	pcfg = ____raw_पढ़ोq(&tx4939_ccfgptr->pcfg);
	अगर (pcfg & (TX4939_PCFG_ET0MODE | TX4939_PCFG_ET1MODE)) अणु
		mdelay(1);	/* at least 128 cpu घड़ी */
		/* clear PCIC1 reset */
		txx9_clear64(&tx4939_ccfgptr->clkctr, TX4939_CLKCTR_PCI1RST);
	पूर्ण अन्यथा अणु
		pr_info("%s: stop PCIC1\n", txx9_pcode_str);
		/* stop PCIC1 */
		txx9_set64(&tx4939_ccfgptr->clkctr, TX4939_CLKCTR_PCI1CKD);
	पूर्ण
	अगर (!(pcfg & TX4939_PCFG_ET0MODE)) अणु
		pr_info("%s: stop ETH0\n", txx9_pcode_str);
		txx9_set64(&tx4939_ccfgptr->clkctr, TX4939_CLKCTR_ETH0RST);
		txx9_set64(&tx4939_ccfgptr->clkctr, TX4939_CLKCTR_ETH0CKD);
	पूर्ण
	अगर (!(pcfg & TX4939_PCFG_ET1MODE)) अणु
		pr_info("%s: stop ETH1\n", txx9_pcode_str);
		txx9_set64(&tx4939_ccfgptr->clkctr, TX4939_CLKCTR_ETH1RST);
		txx9_set64(&tx4939_ccfgptr->clkctr, TX4939_CLKCTR_ETH1CKD);
	पूर्ण

	_machine_restart = tx4939_machine_restart;
	board_be_init = tx4939_be_init;
पूर्ण

व्योम __init tx4939_समय_init(अचिन्हित पूर्णांक पंचांगrnr)
अणु
	अगर (____raw_पढ़ोq(&tx4939_ccfgptr->ccfg) & TX4939_CCFG_TINTDIS)
		txx9_घड़ीevent_init(TX4939_TMR_REG(पंचांगrnr) & 0xfffffffffULL,
				     TXX9_IRQ_BASE + TX4939_IR_TMR(पंचांगrnr),
				     TXX9_IMCLK);
पूर्ण

व्योम __init tx4939_sio_init(अचिन्हित पूर्णांक sclk, अचिन्हित पूर्णांक cts_mask)
अणु
	पूर्णांक i;
	अचिन्हित पूर्णांक ch_mask = 0;
	__u64 pcfg = __raw_पढ़ोq(&tx4939_ccfgptr->pcfg);

	cts_mask |= ~1; /* only SIO0 have RTS/CTS */
	अगर ((pcfg & TX4939_PCFG_SIO2MODE_MASK) != TX4939_PCFG_SIO2MODE_SIO0)
		cts_mask |= 1 << 0; /* disable SIO0 RTS/CTS by PCFG setting */
	अगर ((pcfg & TX4939_PCFG_SIO2MODE_MASK) != TX4939_PCFG_SIO2MODE_SIO2)
		ch_mask |= 1 << 2; /* disable SIO2 by PCFG setting */
	अगर (pcfg & TX4939_PCFG_SIO3MODE)
		ch_mask |= 1 << 3; /* disable SIO3 by PCFG setting */
	क्रम (i = 0; i < 4; i++) अणु
		अगर ((1 << i) & ch_mask)
			जारी;
		txx9_sio_init(TX4939_SIO_REG(i) & 0xfffffffffULL,
			      TXX9_IRQ_BASE + TX4939_IR_SIO(i),
			      i, sclk, (1 << i) & cts_mask);
	पूर्ण
पूर्ण

#अगर IS_ENABLED(CONFIG_TC35815)
अटल u32 tx4939_get_eth_speed(काष्ठा net_device *dev)
अणु
	काष्ठा ethtool_link_ksettings cmd;

	अगर (__ethtool_get_link_ksettings(dev, &cmd))
		वापस 100;	/* शेष 100Mbps */

	वापस cmd.base.speed;
पूर्ण

अटल पूर्णांक tx4939_netdev_event(काष्ठा notअगरier_block *this,
			       अचिन्हित दीर्घ event,
			       व्योम *ptr)
अणु
	काष्ठा net_device *dev = netdev_notअगरier_info_to_dev(ptr);

	अगर (event == NETDEV_CHANGE && netअगर_carrier_ok(dev)) अणु
		__u64 bit = 0;
		अगर (dev->irq == TXX9_IRQ_BASE + TX4939_IR_ETH(0))
			bit = TX4939_PCFG_SPEED0;
		अन्यथा अगर (dev->irq == TXX9_IRQ_BASE + TX4939_IR_ETH(1))
			bit = TX4939_PCFG_SPEED1;
		अगर (bit) अणु
			अगर (tx4939_get_eth_speed(dev) == 100)
				txx9_set64(&tx4939_ccfgptr->pcfg, bit);
			अन्यथा
				txx9_clear64(&tx4939_ccfgptr->pcfg, bit);
		पूर्ण
	पूर्ण
	वापस NOTIFY_DONE;
पूर्ण

अटल काष्ठा notअगरier_block tx4939_netdev_notअगरier = अणु
	.notअगरier_call = tx4939_netdev_event,
	.priority = 1,
पूर्ण;

व्योम __init tx4939_ethaddr_init(अचिन्हित अक्षर *addr0, अचिन्हित अक्षर *addr1)
अणु
	u64 pcfg = __raw_पढ़ोq(&tx4939_ccfgptr->pcfg);

	अगर (addr0 && (pcfg & TX4939_PCFG_ET0MODE))
		txx9_ethaddr_init(TXX9_IRQ_BASE + TX4939_IR_ETH(0), addr0);
	अगर (addr1 && (pcfg & TX4939_PCFG_ET1MODE))
		txx9_ethaddr_init(TXX9_IRQ_BASE + TX4939_IR_ETH(1), addr1);
	रेजिस्टर_netdevice_notअगरier(&tx4939_netdev_notअगरier);
पूर्ण
#अन्यथा
व्योम __init tx4939_ethaddr_init(अचिन्हित अक्षर *addr0, अचिन्हित अक्षर *addr1)
अणु
पूर्ण
#पूर्ण_अगर

व्योम __init tx4939_mtd_init(पूर्णांक ch)
अणु
	काष्ठा physmap_flash_data pdata = अणु
		.width = TX4939_EBUSC_WIDTH(ch) / 8,
	पूर्ण;
	अचिन्हित दीर्घ start = txx9_ce_res[ch].start;
	अचिन्हित दीर्घ size = txx9_ce_res[ch].end - start + 1;

	अगर (!(TX4939_EBUSC_CR(ch) & 0x8))
		वापस; /* disabled */
	txx9_physmap_flash_init(ch, start, size, &pdata);
पूर्ण

#घोषणा TX4939_ATA_REG_PHYS(ch) (TX4939_ATA_REG(ch) & 0xfffffffffULL)
व्योम __init tx4939_ata_init(व्योम)
अणु
	अटल काष्ठा resource ata0_res[] = अणु
		अणु
			.start = TX4939_ATA_REG_PHYS(0),
			.end = TX4939_ATA_REG_PHYS(0) + 0x1000 - 1,
			.flags = IORESOURCE_MEM,
		पूर्ण, अणु
			.start = TXX9_IRQ_BASE + TX4939_IR_ATA(0),
			.flags = IORESOURCE_IRQ,
		पूर्ण,
	पूर्ण;
	अटल काष्ठा resource ata1_res[] = अणु
		अणु
			.start = TX4939_ATA_REG_PHYS(1),
			.end = TX4939_ATA_REG_PHYS(1) + 0x1000 - 1,
			.flags = IORESOURCE_MEM,
		पूर्ण, अणु
			.start = TXX9_IRQ_BASE + TX4939_IR_ATA(1),
			.flags = IORESOURCE_IRQ,
		पूर्ण,
	पूर्ण;
	अटल काष्ठा platक्रमm_device ata0_dev = अणु
		.name = "tx4939ide",
		.id = 0,
		.num_resources = ARRAY_SIZE(ata0_res),
		.resource = ata0_res,
	पूर्ण;
	अटल काष्ठा platक्रमm_device ata1_dev = अणु
		.name = "tx4939ide",
		.id = 1,
		.num_resources = ARRAY_SIZE(ata1_res),
		.resource = ata1_res,
	पूर्ण;
	__u64 pcfg = __raw_पढ़ोq(&tx4939_ccfgptr->pcfg);

	अगर (pcfg & TX4939_PCFG_ATA0MODE)
		platक्रमm_device_रेजिस्टर(&ata0_dev);
	अगर ((pcfg & (TX4939_PCFG_ATA1MODE |
		     TX4939_PCFG_ET1MODE |
		     TX4939_PCFG_ET0MODE)) == TX4939_PCFG_ATA1MODE)
		platक्रमm_device_रेजिस्टर(&ata1_dev);
पूर्ण

व्योम __init tx4939_rtc_init(व्योम)
अणु
	अटल काष्ठा resource res[] = अणु
		अणु
			.start = TX4939_RTC_REG & 0xfffffffffULL,
			.end = (TX4939_RTC_REG & 0xfffffffffULL) + 0x100 - 1,
			.flags = IORESOURCE_MEM,
		पूर्ण, अणु
			.start = TXX9_IRQ_BASE + TX4939_IR_RTC,
			.flags = IORESOURCE_IRQ,
		पूर्ण,
	पूर्ण;
	अटल काष्ठा platक्रमm_device rtc_dev = अणु
		.name = "tx4939rtc",
		.id = -1,
		.num_resources = ARRAY_SIZE(res),
		.resource = res,
	पूर्ण;

	platक्रमm_device_रेजिस्टर(&rtc_dev);
पूर्ण

व्योम __init tx4939_ndfmc_init(अचिन्हित पूर्णांक hold, अचिन्हित पूर्णांक spw,
			      अचिन्हित अक्षर ch_mask, अचिन्हित अक्षर wide_mask)
अणु
	काष्ठा txx9ndfmc_platक्रमm_data plat_data = अणु
		.shअगरt = 1,
		.gbus_घड़ी = txx9_gbus_घड़ी,
		.hold = hold,
		.spw = spw,
		.flags = NDFMC_PLAT_FLAG_NO_RSTR | NDFMC_PLAT_FLAG_HOLDADD |
			 NDFMC_PLAT_FLAG_DUMMYWRITE,
		.ch_mask = ch_mask,
		.wide_mask = wide_mask,
	पूर्ण;
	txx9_ndfmc_init(TX4939_NDFMC_REG & 0xfffffffffULL, &plat_data);
पूर्ण

व्योम __init tx4939_dmac_init(पूर्णांक स_नकल_chan0, पूर्णांक स_नकल_chan1)
अणु
	काष्ठा txx9dmac_platक्रमm_data plat_data = अणु
		.have_64bit_regs = true,
	पूर्ण;
	पूर्णांक i;

	क्रम (i = 0; i < 2; i++) अणु
		plat_data.स_नकल_chan = i ? स_नकल_chan1 : स_नकल_chan0;
		txx9_dmac_init(i, TX4939_DMA_REG(i) & 0xfffffffffULL,
			       TXX9_IRQ_BASE + TX4939_IR_DMA(i, 0),
			       &plat_data);
	पूर्ण
पूर्ण

व्योम __init tx4939_aclc_init(व्योम)
अणु
	u64 pcfg = __raw_पढ़ोq(&tx4939_ccfgptr->pcfg);

	अगर ((pcfg & TX4939_PCFG_I2SMODE_MASK) == TX4939_PCFG_I2SMODE_ACLC)
		txx9_aclc_init(TX4939_ACLC_REG & 0xfffffffffULL,
			       TXX9_IRQ_BASE + TX4939_IR_ACLC, 1, 0, 1);
पूर्ण

व्योम __init tx4939_sramc_init(व्योम)
अणु
	अगर (tx4939_sram_resource.start)
		txx9_sramc_init(&tx4939_sram_resource);
पूर्ण

व्योम __init tx4939_rng_init(व्योम)
अणु
	अटल काष्ठा resource res = अणु
		.start = TX4939_RNG_REG & 0xfffffffffULL,
		.end = (TX4939_RNG_REG & 0xfffffffffULL) + 0x30 - 1,
		.flags = IORESOURCE_MEM,
	पूर्ण;
	अटल काष्ठा platक्रमm_device pdev = अणु
		.name = "tx4939-rng",
		.id = -1,
		.num_resources = 1,
		.resource = &res,
	पूर्ण;

	platक्रमm_device_रेजिस्टर(&pdev);
पूर्ण

अटल व्योम __init tx4939_stop_unused_modules(व्योम)
अणु
	__u64 pcfg, rst = 0, ckd = 0;
	अक्षर buf[128];

	buf[0] = '\0';
	local_irq_disable();
	pcfg = ____raw_पढ़ोq(&tx4939_ccfgptr->pcfg);
	अगर ((pcfg & TX4939_PCFG_I2SMODE_MASK) !=
	    TX4939_PCFG_I2SMODE_ACLC) अणु
		rst |= TX4939_CLKCTR_ACLRST;
		ckd |= TX4939_CLKCTR_ACLCKD;
		म_जोड़ो(buf, " ACLC");
	पूर्ण
	अगर ((pcfg & TX4939_PCFG_I2SMODE_MASK) !=
	    TX4939_PCFG_I2SMODE_I2S &&
	    (pcfg & TX4939_PCFG_I2SMODE_MASK) !=
	    TX4939_PCFG_I2SMODE_I2S_ALT) अणु
		rst |= TX4939_CLKCTR_I2SRST;
		ckd |= TX4939_CLKCTR_I2SCKD;
		म_जोड़ो(buf, " I2S");
	पूर्ण
	अगर (!(pcfg & TX4939_PCFG_ATA0MODE)) अणु
		rst |= TX4939_CLKCTR_ATA0RST;
		ckd |= TX4939_CLKCTR_ATA0CKD;
		म_जोड़ो(buf, " ATA0");
	पूर्ण
	अगर (!(pcfg & TX4939_PCFG_ATA1MODE)) अणु
		rst |= TX4939_CLKCTR_ATA1RST;
		ckd |= TX4939_CLKCTR_ATA1CKD;
		म_जोड़ो(buf, " ATA1");
	पूर्ण
	अगर (pcfg & TX4939_PCFG_SPIMODE) अणु
		rst |= TX4939_CLKCTR_SPIRST;
		ckd |= TX4939_CLKCTR_SPICKD;
		म_जोड़ो(buf, " SPI");
	पूर्ण
	अगर (!(pcfg & (TX4939_PCFG_VSSMODE | TX4939_PCFG_VPSMODE))) अणु
		rst |= TX4939_CLKCTR_VPCRST;
		ckd |= TX4939_CLKCTR_VPCCKD;
		म_जोड़ो(buf, " VPC");
	पूर्ण
	अगर ((pcfg & TX4939_PCFG_SIO2MODE_MASK) != TX4939_PCFG_SIO2MODE_SIO2) अणु
		rst |= TX4939_CLKCTR_SIO2RST;
		ckd |= TX4939_CLKCTR_SIO2CKD;
		म_जोड़ो(buf, " SIO2");
	पूर्ण
	अगर (pcfg & TX4939_PCFG_SIO3MODE) अणु
		rst |= TX4939_CLKCTR_SIO3RST;
		ckd |= TX4939_CLKCTR_SIO3CKD;
		म_जोड़ो(buf, " SIO3");
	पूर्ण
	अगर (rst | ckd) अणु
		txx9_set64(&tx4939_ccfgptr->clkctr, rst);
		txx9_set64(&tx4939_ccfgptr->clkctr, ckd);
	पूर्ण
	local_irq_enable();
	अगर (buf[0])
		pr_info("%s: stop%s\n", txx9_pcode_str, buf);
पूर्ण

अटल पूर्णांक __init tx4939_late_init(व्योम)
अणु
	अगर (txx9_pcode != 0x4939)
		वापस -ENODEV;
	tx4939_stop_unused_modules();
	वापस 0;
पूर्ण
late_initcall(tx4939_late_init);
