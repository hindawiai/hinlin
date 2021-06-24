<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright 1999 - 2003 ARM Limited
 * Copyright 2000 Deep Blue Solutions Ltd
 * Copyright 2008 Cavium Networks
 */

#समावेश <linux/init.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/घड़ीchips.h>
#समावेश <linux/पन.स>
#समावेश <linux/irqchip/arm-gic.h>
#समावेश <linux/of_platक्रमm.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/usb/ehci_pdriver.h>
#समावेश <linux/usb/ohci_pdriver.h>
#समावेश <यंत्र/mach/arch.h>
#समावेश <यंत्र/mach/map.h>
#समावेश <यंत्र/mach/समय.स>
#समावेश <यंत्र/mach/irq.h>
#समावेश <यंत्र/hardware/cache-l2x0.h>
#समावेश "cns3xxx.h"
#समावेश "core.h"
#समावेश "pm.h"

अटल काष्ठा map_desc cns3xxx_io_desc[] __initdata = अणु
	अणु
		.भव	= CNS3XXX_TC11MP_SCU_BASE_VIRT,
		.pfn		= __phys_to_pfn(CNS3XXX_TC11MP_SCU_BASE),
		.length		= SZ_8K,
		.type		= MT_DEVICE,
	पूर्ण, अणु
		.भव	= CNS3XXX_TIMER1_2_3_BASE_VIRT,
		.pfn		= __phys_to_pfn(CNS3XXX_TIMER1_2_3_BASE),
		.length		= SZ_4K,
		.type		= MT_DEVICE,
	पूर्ण, अणु
		.भव	= CNS3XXX_MISC_BASE_VIRT,
		.pfn		= __phys_to_pfn(CNS3XXX_MISC_BASE),
		.length		= SZ_4K,
		.type		= MT_DEVICE,
	पूर्ण, अणु
		.भव	= CNS3XXX_PM_BASE_VIRT,
		.pfn		= __phys_to_pfn(CNS3XXX_PM_BASE),
		.length		= SZ_4K,
		.type		= MT_DEVICE,
#अगर_घोषित CONFIG_PCI
	पूर्ण, अणु
		.भव	= CNS3XXX_PCIE0_HOST_BASE_VIRT,
		.pfn		= __phys_to_pfn(CNS3XXX_PCIE0_HOST_BASE),
		.length		= SZ_4K,
		.type		= MT_DEVICE,
	पूर्ण, अणु
		.भव	= CNS3XXX_PCIE0_CFG0_BASE_VIRT,
		.pfn		= __phys_to_pfn(CNS3XXX_PCIE0_CFG0_BASE),
		.length		= SZ_64K, /* really 4 KiB at offset 32 KiB */
		.type		= MT_DEVICE,
	पूर्ण, अणु
		.भव	= CNS3XXX_PCIE0_CFG1_BASE_VIRT,
		.pfn		= __phys_to_pfn(CNS3XXX_PCIE0_CFG1_BASE),
		.length		= SZ_16M,
		.type		= MT_DEVICE,
	पूर्ण, अणु
		.भव	= CNS3XXX_PCIE1_HOST_BASE_VIRT,
		.pfn		= __phys_to_pfn(CNS3XXX_PCIE1_HOST_BASE),
		.length		= SZ_4K,
		.type		= MT_DEVICE,
	पूर्ण, अणु
		.भव	= CNS3XXX_PCIE1_CFG0_BASE_VIRT,
		.pfn		= __phys_to_pfn(CNS3XXX_PCIE1_CFG0_BASE),
		.length		= SZ_64K, /* really 4 KiB at offset 32 KiB */
		.type		= MT_DEVICE,
	पूर्ण, अणु
		.भव	= CNS3XXX_PCIE1_CFG1_BASE_VIRT,
		.pfn		= __phys_to_pfn(CNS3XXX_PCIE1_CFG1_BASE),
		.length		= SZ_16M,
		.type		= MT_DEVICE,
#पूर्ण_अगर
	पूर्ण,
पूर्ण;

व्योम __init cns3xxx_map_io(व्योम)
अणु
	iotable_init(cns3xxx_io_desc, ARRAY_SIZE(cns3xxx_io_desc));
पूर्ण

/* used by entry-macro.S */
व्योम __init cns3xxx_init_irq(व्योम)
अणु
	gic_init(IOMEM(CNS3XXX_TC11MP_GIC_DIST_BASE_VIRT),
		 IOMEM(CNS3XXX_TC11MP_GIC_CPU_BASE_VIRT));
पूर्ण

व्योम cns3xxx_घातer_off(व्योम)
अणु
	u32 __iomem *pm_base = IOMEM(CNS3XXX_PM_BASE_VIRT);
	u32 clkctrl;

	prपूर्णांकk(KERN_INFO "powering system down...\n");

	clkctrl = पढ़ोl(pm_base + PM_SYS_CLK_CTRL_OFFSET);
	clkctrl &= 0xfffff1ff;
	clkctrl |= (0x5 << 9);		/* Hibernate */
	ग_लिखोl(clkctrl, pm_base + PM_SYS_CLK_CTRL_OFFSET);

पूर्ण

/*
 * Timer
 */
अटल व्योम __iomem *cns3xxx_पंचांगr1;

अटल पूर्णांक cns3xxx_shutकरोwn(काष्ठा घड़ी_event_device *clk)
अणु
	ग_लिखोl(0, cns3xxx_पंचांगr1 + TIMER1_2_CONTROL_OFFSET);
	वापस 0;
पूर्ण

अटल पूर्णांक cns3xxx_set_oneshot(काष्ठा घड़ी_event_device *clk)
अणु
	अचिन्हित दीर्घ ctrl = पढ़ोl(cns3xxx_पंचांगr1 + TIMER1_2_CONTROL_OFFSET);

	/* period set, and समयr enabled in 'next_event' hook */
	ctrl |= (1 << 2) | (1 << 9);
	ग_लिखोl(ctrl, cns3xxx_पंचांगr1 + TIMER1_2_CONTROL_OFFSET);
	वापस 0;
पूर्ण

अटल पूर्णांक cns3xxx_set_periodic(काष्ठा घड़ी_event_device *clk)
अणु
	अचिन्हित दीर्घ ctrl = पढ़ोl(cns3xxx_पंचांगr1 + TIMER1_2_CONTROL_OFFSET);
	पूर्णांक pclk = cns3xxx_cpu_घड़ी() / 8;
	पूर्णांक reload;

	reload = pclk * 20 / (3 * HZ) * 0x25000;
	ग_लिखोl(reload, cns3xxx_पंचांगr1 + TIMER1_AUTO_RELOAD_OFFSET);
	ctrl |= (1 << 0) | (1 << 2) | (1 << 9);
	ग_लिखोl(ctrl, cns3xxx_पंचांगr1 + TIMER1_2_CONTROL_OFFSET);
	वापस 0;
पूर्ण

अटल पूर्णांक cns3xxx_समयr_set_next_event(अचिन्हित दीर्घ evt,
					काष्ठा घड़ी_event_device *unused)
अणु
	अचिन्हित दीर्घ ctrl = पढ़ोl(cns3xxx_पंचांगr1 + TIMER1_2_CONTROL_OFFSET);

	ग_लिखोl(evt, cns3xxx_पंचांगr1 + TIMER1_AUTO_RELOAD_OFFSET);
	ग_लिखोl(ctrl | (1 << 0), cns3xxx_पंचांगr1 + TIMER1_2_CONTROL_OFFSET);

	वापस 0;
पूर्ण

अटल काष्ठा घड़ी_event_device cns3xxx_पंचांगr1_घड़ीevent = अणु
	.name			= "cns3xxx timer1",
	.features		= CLOCK_EVT_FEAT_PERIODIC |
				  CLOCK_EVT_FEAT_ONESHOT,
	.set_state_shutकरोwn	= cns3xxx_shutकरोwn,
	.set_state_periodic	= cns3xxx_set_periodic,
	.set_state_oneshot	= cns3xxx_set_oneshot,
	.tick_resume		= cns3xxx_shutकरोwn,
	.set_next_event		= cns3xxx_समयr_set_next_event,
	.rating			= 350,
	.cpumask		= cpu_all_mask,
पूर्ण;

अटल व्योम __init cns3xxx_घड़ीevents_init(अचिन्हित पूर्णांक समयr_irq)
अणु
	cns3xxx_पंचांगr1_घड़ीevent.irq = समयr_irq;
	घड़ीevents_config_and_रेजिस्टर(&cns3xxx_पंचांगr1_घड़ीevent,
					(cns3xxx_cpu_घड़ी() >> 3) * 1000000,
					0xf, 0xffffffff);
पूर्ण

/*
 * IRQ handler क्रम the समयr
 */
अटल irqवापस_t cns3xxx_समयr_पूर्णांकerrupt(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा घड़ी_event_device *evt = &cns3xxx_पंचांगr1_घड़ीevent;
	u32 __iomem *stat = cns3xxx_पंचांगr1 + TIMER1_2_INTERRUPT_STATUS_OFFSET;
	u32 val;

	/* Clear the पूर्णांकerrupt */
	val = पढ़ोl(stat);
	ग_लिखोl(val & ~(1 << 2), stat);

	evt->event_handler(evt);

	वापस IRQ_HANDLED;
पूर्ण

/*
 * Set up the घड़ी source and घड़ी events devices
 */
अटल व्योम __init __cns3xxx_समयr_init(अचिन्हित पूर्णांक समयr_irq)
अणु
	u32 val;
	u32 irq_mask;

	/*
	 * Initialise to a known state (all समयrs off)
	 */

	/* disable समयr1 and समयr2 */
	ग_लिखोl(0, cns3xxx_पंचांगr1 + TIMER1_2_CONTROL_OFFSET);
	/* stop मुक्त running समयr3 */
	ग_लिखोl(0, cns3xxx_पंचांगr1 + TIMER_FREERUN_CONTROL_OFFSET);

	/* समयr1 */
	ग_लिखोl(0x5C800, cns3xxx_पंचांगr1 + TIMER1_COUNTER_OFFSET);
	ग_लिखोl(0x5C800, cns3xxx_पंचांगr1 + TIMER1_AUTO_RELOAD_OFFSET);

	ग_लिखोl(0, cns3xxx_पंचांगr1 + TIMER1_MATCH_V1_OFFSET);
	ग_लिखोl(0, cns3xxx_पंचांगr1 + TIMER1_MATCH_V2_OFFSET);

	/* mask irq, non-mask समयr1 overflow */
	irq_mask = पढ़ोl(cns3xxx_पंचांगr1 + TIMER1_2_INTERRUPT_MASK_OFFSET);
	irq_mask &= ~(1 << 2);
	irq_mask |= 0x03;
	ग_लिखोl(irq_mask, cns3xxx_पंचांगr1 + TIMER1_2_INTERRUPT_MASK_OFFSET);

	/* करोwn counter */
	val = पढ़ोl(cns3xxx_पंचांगr1 + TIMER1_2_CONTROL_OFFSET);
	val |= (1 << 9);
	ग_लिखोl(val, cns3xxx_पंचांगr1 + TIMER1_2_CONTROL_OFFSET);

	/* समयr2 */
	ग_लिखोl(0, cns3xxx_पंचांगr1 + TIMER2_MATCH_V1_OFFSET);
	ग_लिखोl(0, cns3xxx_पंचांगr1 + TIMER2_MATCH_V2_OFFSET);

	/* mask irq */
	irq_mask = पढ़ोl(cns3xxx_पंचांगr1 + TIMER1_2_INTERRUPT_MASK_OFFSET);
	irq_mask |= ((1 << 3) | (1 << 4) | (1 << 5));
	ग_लिखोl(irq_mask, cns3xxx_पंचांगr1 + TIMER1_2_INTERRUPT_MASK_OFFSET);

	/* करोwn counter */
	val = पढ़ोl(cns3xxx_पंचांगr1 + TIMER1_2_CONTROL_OFFSET);
	val |= (1 << 10);
	ग_लिखोl(val, cns3xxx_पंचांगr1 + TIMER1_2_CONTROL_OFFSET);

	/* Make irqs happen क्रम the प्रणाली समयr */
	अगर (request_irq(समयr_irq, cns3xxx_समयr_पूर्णांकerrupt,
			IRQF_TIMER | IRQF_IRQPOLL, "timer", शून्य))
		pr_err("Failed to request irq %d (timer)\n", समयr_irq);

	cns3xxx_घड़ीevents_init(समयr_irq);
पूर्ण

व्योम __init cns3xxx_समयr_init(व्योम)
अणु
	cns3xxx_पंचांगr1 = IOMEM(CNS3XXX_TIMER1_2_3_BASE_VIRT);

	__cns3xxx_समयr_init(IRQ_CNS3XXX_TIMER0);
पूर्ण

#अगर_घोषित CONFIG_CACHE_L2X0

व्योम __init cns3xxx_l2x0_init(व्योम)
अणु
	व्योम __iomem *base = ioremap(CNS3XXX_L2C_BASE, SZ_4K);
	u32 val;

	अगर (WARN_ON(!base))
		वापस;

	/*
	 * Tag RAM Control रेजिस्टर
	 *
	 * bit[10:8]	- 1 cycle of ग_लिखो accesses latency
	 * bit[6:4]	- 1 cycle of पढ़ो accesses latency
	 * bit[3:0]	- 1 cycle of setup latency
	 *
	 * 1 cycle of latency क्रम setup, पढ़ो and ग_लिखो accesses
	 */
	val = पढ़ोl(base + L310_TAG_LATENCY_CTRL);
	val &= 0xfffff888;
	ग_लिखोl(val, base + L310_TAG_LATENCY_CTRL);

	/*
	 * Data RAM Control रेजिस्टर
	 *
	 * bit[10:8]	- 1 cycles of ग_लिखो accesses latency
	 * bit[6:4]	- 1 cycles of पढ़ो accesses latency
	 * bit[3:0]	- 1 cycle of setup latency
	 *
	 * 1 cycle of latency क्रम setup, पढ़ो and ग_लिखो accesses
	 */
	val = पढ़ोl(base + L310_DATA_LATENCY_CTRL);
	val &= 0xfffff888;
	ग_लिखोl(val, base + L310_DATA_LATENCY_CTRL);

	/* 32 KiB, 8-way, parity disable */
	l2x0_init(base, 0x00500000, 0xfe0f0fff);
पूर्ण

#पूर्ण_अगर /* CONFIG_CACHE_L2X0 */

अटल पूर्णांक csn3xxx_usb_घातer_on(काष्ठा platक्रमm_device *pdev)
अणु
	/*
	 * EHCI and OHCI share the same घड़ी and घातer,
	 * resetting twice would cause the 1st controller been reset.
	 * Thereक्रमe only करो घातer up  at the first up device, and
	 * घातer करोwn at the last करोwn device.
	 *
	 * Set USB AHB INCR length to 16
	 */
	अगर (atomic_inc_वापस(&usb_pwr_ref) == 1) अणु
		cns3xxx_pwr_घातer_up(1 << PM_PLL_HM_PD_CTRL_REG_OFFSET_PLL_USB);
		cns3xxx_pwr_clk_en(1 << PM_CLK_GATE_REG_OFFSET_USB_HOST);
		cns3xxx_pwr_soft_rst(1 << PM_SOFT_RST_REG_OFFST_USB_HOST);
		__raw_ग_लिखोl((__raw_पढ़ोl(MISC_CHIP_CONFIG_REG) | (0X2 << 24)),
			MISC_CHIP_CONFIG_REG);
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम csn3xxx_usb_घातer_off(काष्ठा platक्रमm_device *pdev)
अणु
	/*
	 * EHCI and OHCI share the same घड़ी and घातer,
	 * resetting twice would cause the 1st controller been reset.
	 * Thereक्रमe only करो घातer up  at the first up device, and
	 * घातer करोwn at the last करोwn device.
	 */
	अगर (atomic_dec_वापस(&usb_pwr_ref) == 0)
		cns3xxx_pwr_clk_dis(1 << PM_CLK_GATE_REG_OFFSET_USB_HOST);
पूर्ण

अटल काष्ठा usb_ehci_pdata cns3xxx_usb_ehci_pdata = अणु
	.घातer_on	= csn3xxx_usb_घातer_on,
	.घातer_off	= csn3xxx_usb_घातer_off,
पूर्ण;

अटल काष्ठा usb_ohci_pdata cns3xxx_usb_ohci_pdata = अणु
	.num_ports	= 1,
	.घातer_on	= csn3xxx_usb_घातer_on,
	.घातer_off	= csn3xxx_usb_घातer_off,
पूर्ण;

अटल स्थिर काष्ठा of_dev_auxdata cns3xxx_auxdata[] __initस्थिर = अणु
	अणु "intel,usb-ehci", CNS3XXX_USB_BASE, "ehci-platform", &cns3xxx_usb_ehci_pdata पूर्ण,
	अणु "intel,usb-ohci", CNS3XXX_USB_OHCI_BASE, "ohci-platform", &cns3xxx_usb_ohci_pdata पूर्ण,
	अणु "cavium,cns3420-ahci", CNS3XXX_SATA2_BASE, "ahci", शून्य पूर्ण,
	अणु "cavium,cns3420-sdhci", CNS3XXX_SDIO_BASE, "ahci", शून्य पूर्ण,
	अणुपूर्ण,
पूर्ण;

अटल व्योम __init cns3xxx_init(व्योम)
अणु
	काष्ठा device_node *dn;

	cns3xxx_l2x0_init();

	dn = of_find_compatible_node(शून्य, शून्य, "cavium,cns3420-ahci");
	अगर (of_device_is_available(dn)) अणु
		u32 पंचांगp;
	
		पंचांगp = __raw_पढ़ोl(MISC_SATA_POWER_MODE);
		पंचांगp |= 0x1 << 16; /* Disable SATA PHY 0 from SLUMBER Mode */
		पंचांगp |= 0x1 << 17; /* Disable SATA PHY 1 from SLUMBER Mode */
		__raw_ग_लिखोl(पंचांगp, MISC_SATA_POWER_MODE);
	
		/* Enable SATA PHY */
		cns3xxx_pwr_घातer_up(0x1 << PM_PLL_HM_PD_CTRL_REG_OFFSET_SATA_PHY0);
		cns3xxx_pwr_घातer_up(0x1 << PM_PLL_HM_PD_CTRL_REG_OFFSET_SATA_PHY1);
	
		/* Enable SATA Clock */
		cns3xxx_pwr_clk_en(0x1 << PM_CLK_GATE_REG_OFFSET_SATA);
	
		/* De-Asscer SATA Reset */
		cns3xxx_pwr_soft_rst(CNS3XXX_PWR_SOFTWARE_RST(SATA));
	पूर्ण

	dn = of_find_compatible_node(शून्य, शून्य, "cavium,cns3420-sdhci");
	अगर (of_device_is_available(dn)) अणु
		u32 __iomem *gpioa = IOMEM(CNS3XXX_MISC_BASE_VIRT + 0x0014);
		u32 gpioa_pins = __raw_पढ़ोl(gpioa);
	
		/* MMC/SD pins share with GPIOA */
		gpioa_pins |= 0x1fff0004;
		__raw_ग_लिखोl(gpioa_pins, gpioa);
	
		cns3xxx_pwr_clk_en(CNS3XXX_PWR_CLK_EN(SDIO));
		cns3xxx_pwr_soft_rst(CNS3XXX_PWR_SOFTWARE_RST(SDIO));
	पूर्ण

	pm_घातer_off = cns3xxx_घातer_off;

	of_platक्रमm_शेष_populate(शून्य, cns3xxx_auxdata, शून्य);
पूर्ण

अटल स्थिर अक्षर *स्थिर cns3xxx_dt_compat[] __initस्थिर = अणु
	"cavium,cns3410",
	"cavium,cns3420",
	शून्य,
पूर्ण;

DT_MACHINE_START(CNS3XXX_DT, "Cavium Networks CNS3xxx")
	.dt_compat	= cns3xxx_dt_compat,
	.map_io		= cns3xxx_map_io,
	.init_irq	= cns3xxx_init_irq,
	.init_समय	= cns3xxx_समयr_init,
	.init_machine	= cns3xxx_init,
	.init_late	= cns3xxx_pcie_init_late,
	.restart	= cns3xxx_restart,
MACHINE_END
