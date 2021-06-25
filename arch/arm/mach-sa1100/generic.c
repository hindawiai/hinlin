<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * linux/arch/arm/mach-sa1100/generic.c
 *
 * Author: Nicolas Pitre
 *
 * Code common to all SA11x0 machines.
 */
#समावेश <linux/gpपन.स>
#समावेश <linux/gpio/machine.h>
#समावेश <linux/module.h>
#समावेश <linux/kernel.h>
#समावेश <linux/init.h>
#समावेश <linux/delay.h>
#समावेश <linux/dma-mapping.h>
#समावेश <linux/pm.h>
#समावेश <linux/cpufreq.h>
#समावेश <linux/ioport.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/reboot.h>
#समावेश <linux/regulator/fixed.h>
#समावेश <linux/regulator/machine.h>
#समावेश <linux/irqchip/irq-sa11x0.h>

#समावेश <video/sa1100fb.h>

#समावेश <soc/sa1100/pwer.h>

#समावेश <यंत्र/भाग64.h>
#समावेश <यंत्र/mach/map.h>
#समावेश <यंत्र/mach/flash.h>
#समावेश <यंत्र/irq.h>
#समावेश <यंत्र/प्रणाली_misc.h>

#समावेश <mach/hardware.h>
#समावेश <mach/irqs.h>
#समावेश <mach/reset.h>

#समावेश "generic.h"
#समावेश <घड़ीsource/pxa.h>

अचिन्हित पूर्णांक reset_status;
EXPORT_SYMBOL(reset_status);

#घोषणा NR_FREQS	16

/*
 * This table is setup क्रम a 3.6864MHz Crystal.
 */
काष्ठा cpufreq_frequency_table sa11x0_freq_table[NR_FREQS+1] = अणु
	अणु .frequency = 59000,	/*  59.0 MHz */पूर्ण,
	अणु .frequency = 73700,	/*  73.7 MHz */पूर्ण,
	अणु .frequency = 88500,	/*  88.5 MHz */पूर्ण,
	अणु .frequency = 103200,	/* 103.2 MHz */पूर्ण,
	अणु .frequency = 118000,	/* 118.0 MHz */पूर्ण,
	अणु .frequency = 132700,	/* 132.7 MHz */पूर्ण,
	अणु .frequency = 147500,	/* 147.5 MHz */पूर्ण,
	अणु .frequency = 162200,	/* 162.2 MHz */पूर्ण,
	अणु .frequency = 176900,	/* 176.9 MHz */पूर्ण,
	अणु .frequency = 191700,	/* 191.7 MHz */पूर्ण,
	अणु .frequency = 206400,	/* 206.4 MHz */पूर्ण,
	अणु .frequency = 221200,	/* 221.2 MHz */पूर्ण,
	अणु .frequency = 235900,	/* 235.9 MHz */पूर्ण,
	अणु .frequency = 250700,	/* 250.7 MHz */पूर्ण,
	अणु .frequency = 265400,	/* 265.4 MHz */पूर्ण,
	अणु .frequency = 280200,	/* 280.2 MHz */पूर्ण,
	अणु .frequency = CPUFREQ_TABLE_END, पूर्ण,
पूर्ण;

अचिन्हित पूर्णांक sa11x0_माला_लोpeed(अचिन्हित पूर्णांक cpu)
अणु
	अगर (cpu)
		वापस 0;
	वापस sa11x0_freq_table[PPCR & 0xf].frequency;
पूर्ण

/*
 * Default घातer-off क्रम SA1100
 */
अटल व्योम sa1100_घातer_off(व्योम)
अणु
	mdelay(100);
	local_irq_disable();
	/* disable पूर्णांकernal oscillator, भग्न CS lines */
	PCFR = (PCFR_OPDE | PCFR_FP | PCFR_FS);
	/* enable wake-up on GPIO0 (Assabet...) */
	PWER = GFER = GRER = 1;
	/*
	 * set scratchpad to zero, just in हाल it is used as a
	 * restart address by the bootloader.
	 */
	PSPR = 0;
	/* enter sleep mode */
	PMCR = PMCR_SF;
पूर्ण

व्योम sa11x0_restart(क्रमागत reboot_mode mode, स्थिर अक्षर *cmd)
अणु
	clear_reset_status(RESET_STATUS_ALL);

	अगर (mode == REBOOT_SOFT) अणु
		/* Jump पूर्णांकo ROM at address 0 */
		soft_restart(0);
	पूर्ण अन्यथा अणु
		/* Use on-chip reset capability */
		RSRR = RSRR_SWR;
	पूर्ण
पूर्ण

अटल व्योम sa11x0_रेजिस्टर_device(काष्ठा platक्रमm_device *dev, व्योम *data)
अणु
	पूर्णांक err;
	dev->dev.platक्रमm_data = data;
	err = platक्रमm_device_रेजिस्टर(dev);
	अगर (err)
		prपूर्णांकk(KERN_ERR "Unable to register device %s: %d\n",
			dev->name, err);
पूर्ण


अटल काष्ठा resource sa11x0udc_resources[] = अणु
	[0] = DEFINE_RES_MEM(__PREG(Ser0UDCCR), SZ_64K),
	[1] = DEFINE_RES_IRQ(IRQ_Ser0UDC),
पूर्ण;

अटल u64 sa11x0udc_dma_mask = 0xffffffffUL;

अटल काष्ठा platक्रमm_device sa11x0udc_device = अणु
	.name		= "sa11x0-udc",
	.id		= -1,
	.dev		= अणु
		.dma_mask = &sa11x0udc_dma_mask,
		.coherent_dma_mask = 0xffffffff,
	पूर्ण,
	.num_resources	= ARRAY_SIZE(sa11x0udc_resources),
	.resource	= sa11x0udc_resources,
पूर्ण;

अटल काष्ठा resource sa11x0uart1_resources[] = अणु
	[0] = DEFINE_RES_MEM(__PREG(Ser1UTCR0), SZ_64K),
	[1] = DEFINE_RES_IRQ(IRQ_Ser1UART),
पूर्ण;

अटल काष्ठा platक्रमm_device sa11x0uart1_device = अणु
	.name		= "sa11x0-uart",
	.id		= 1,
	.num_resources	= ARRAY_SIZE(sa11x0uart1_resources),
	.resource	= sa11x0uart1_resources,
पूर्ण;

अटल काष्ठा resource sa11x0uart3_resources[] = अणु
	[0] = DEFINE_RES_MEM(__PREG(Ser3UTCR0), SZ_64K),
	[1] = DEFINE_RES_IRQ(IRQ_Ser3UART),
पूर्ण;

अटल काष्ठा platक्रमm_device sa11x0uart3_device = अणु
	.name		= "sa11x0-uart",
	.id		= 3,
	.num_resources	= ARRAY_SIZE(sa11x0uart3_resources),
	.resource	= sa11x0uart3_resources,
पूर्ण;

अटल काष्ठा resource sa11x0mcp_resources[] = अणु
	[0] = DEFINE_RES_MEM(__PREG(Ser4MCCR0), SZ_64K),
	[1] = DEFINE_RES_MEM(__PREG(Ser4MCCR1), 4),
	[2] = DEFINE_RES_IRQ(IRQ_Ser4MCP),
पूर्ण;

अटल u64 sa11x0mcp_dma_mask = 0xffffffffUL;

अटल काष्ठा platक्रमm_device sa11x0mcp_device = अणु
	.name		= "sa11x0-mcp",
	.id		= -1,
	.dev = अणु
		.dma_mask = &sa11x0mcp_dma_mask,
		.coherent_dma_mask = 0xffffffff,
	पूर्ण,
	.num_resources	= ARRAY_SIZE(sa11x0mcp_resources),
	.resource	= sa11x0mcp_resources,
पूर्ण;

व्योम __init sa11x0_ppc_configure_mcp(व्योम)
अणु
	/* Setup the PPC unit क्रम the MCP */
	PPDR &= ~PPC_RXD4;
	PPDR |= PPC_TXD4 | PPC_SCLK | PPC_SFRM;
	PSDR |= PPC_RXD4;
	PSDR &= ~(PPC_TXD4 | PPC_SCLK | PPC_SFRM);
	PPSR &= ~(PPC_TXD4 | PPC_SCLK | PPC_SFRM);
पूर्ण

व्योम sa11x0_रेजिस्टर_mcp(काष्ठा mcp_plat_data *data)
अणु
	sa11x0_रेजिस्टर_device(&sa11x0mcp_device, data);
पूर्ण

अटल काष्ठा resource sa11x0ssp_resources[] = अणु
	[0] = DEFINE_RES_MEM(0x80070000, SZ_64K),
	[1] = DEFINE_RES_IRQ(IRQ_Ser4SSP),
पूर्ण;

अटल u64 sa11x0ssp_dma_mask = 0xffffffffUL;

अटल काष्ठा platक्रमm_device sa11x0ssp_device = अणु
	.name		= "sa11x0-ssp",
	.id		= -1,
	.dev = अणु
		.dma_mask = &sa11x0ssp_dma_mask,
		.coherent_dma_mask = 0xffffffff,
	पूर्ण,
	.num_resources	= ARRAY_SIZE(sa11x0ssp_resources),
	.resource	= sa11x0ssp_resources,
पूर्ण;

अटल काष्ठा resource sa11x0fb_resources[] = अणु
	[0] = DEFINE_RES_MEM(0xb0100000, SZ_64K),
	[1] = DEFINE_RES_IRQ(IRQ_LCD),
पूर्ण;

अटल काष्ठा platक्रमm_device sa11x0fb_device = अणु
	.name		= "sa11x0-fb",
	.id		= -1,
	.dev = अणु
		.coherent_dma_mask = 0xffffffff,
	पूर्ण,
	.num_resources	= ARRAY_SIZE(sa11x0fb_resources),
	.resource	= sa11x0fb_resources,
पूर्ण;

व्योम sa11x0_रेजिस्टर_lcd(काष्ठा sa1100fb_mach_info *inf)
अणु
	sa11x0_रेजिस्टर_device(&sa11x0fb_device, inf);
पूर्ण

व्योम sa11x0_रेजिस्टर_pcmcia(पूर्णांक socket, काष्ठा gpiod_lookup_table *table)
अणु
	अगर (table)
		gpiod_add_lookup_table(table);
	platक्रमm_device_रेजिस्टर_simple("sa11x0-pcmcia", socket, शून्य, 0);
पूर्ण

अटल काष्ठा platक्रमm_device sa11x0mtd_device = अणु
	.name		= "sa1100-mtd",
	.id		= -1,
पूर्ण;

व्योम sa11x0_रेजिस्टर_mtd(काष्ठा flash_platक्रमm_data *flash,
			 काष्ठा resource *res, पूर्णांक nr)
अणु
	flash->name = "sa1100";
	sa11x0mtd_device.resource = res;
	sa11x0mtd_device.num_resources = nr;
	sa11x0_रेजिस्टर_device(&sa11x0mtd_device, flash);
पूर्ण

अटल काष्ठा resource sa11x0ir_resources[] = अणु
	DEFINE_RES_MEM(__PREG(Ser2UTCR0), 0x24),
	DEFINE_RES_MEM(__PREG(Ser2HSCR0), 0x1c),
	DEFINE_RES_MEM(__PREG(Ser2HSCR2), 0x04),
	DEFINE_RES_IRQ(IRQ_Ser2ICP),
पूर्ण;

अटल काष्ठा platक्रमm_device sa11x0ir_device = अणु
	.name		= "sa11x0-ir",
	.id		= -1,
	.num_resources	= ARRAY_SIZE(sa11x0ir_resources),
	.resource	= sa11x0ir_resources,
पूर्ण;

व्योम sa11x0_रेजिस्टर_irda(काष्ठा irda_platक्रमm_data *irda)
अणु
	sa11x0_रेजिस्टर_device(&sa11x0ir_device, irda);
पूर्ण

अटल काष्ठा resource sa1100_rtc_resources[] = अणु
	DEFINE_RES_MEM(0x90010000, 0x40),
	DEFINE_RES_IRQ_NAMED(IRQ_RTC1Hz, "rtc 1Hz"),
	DEFINE_RES_IRQ_NAMED(IRQ_RTCAlrm, "rtc alarm"),
पूर्ण;

अटल काष्ठा platक्रमm_device sa11x0rtc_device = अणु
	.name		= "sa1100-rtc",
	.id		= -1,
	.num_resources	= ARRAY_SIZE(sa1100_rtc_resources),
	.resource	= sa1100_rtc_resources,
पूर्ण;

अटल काष्ठा resource sa11x0dma_resources[] = अणु
	DEFINE_RES_MEM(DMA_PHYS, DMA_SIZE),
	DEFINE_RES_IRQ(IRQ_DMA0),
	DEFINE_RES_IRQ(IRQ_DMA1),
	DEFINE_RES_IRQ(IRQ_DMA2),
	DEFINE_RES_IRQ(IRQ_DMA3),
	DEFINE_RES_IRQ(IRQ_DMA4),
	DEFINE_RES_IRQ(IRQ_DMA5),
पूर्ण;

अटल u64 sa11x0dma_dma_mask = DMA_BIT_MASK(32);

अटल काष्ठा platक्रमm_device sa11x0dma_device = अणु
	.name		= "sa11x0-dma",
	.id		= -1,
	.dev = अणु
		.dma_mask = &sa11x0dma_dma_mask,
		.coherent_dma_mask = 0xffffffff,
	पूर्ण,
	.num_resources	= ARRAY_SIZE(sa11x0dma_resources),
	.resource	= sa11x0dma_resources,
पूर्ण;

अटल काष्ठा platक्रमm_device *sa11x0_devices[] __initdata = अणु
	&sa11x0udc_device,
	&sa11x0uart1_device,
	&sa11x0uart3_device,
	&sa11x0ssp_device,
	&sa11x0rtc_device,
	&sa11x0dma_device,
पूर्ण;

अटल पूर्णांक __init sa1100_init(व्योम)
अणु
	pm_घातer_off = sa1100_घातer_off;

	regulator_has_full_स्थिरraपूर्णांकs();

	वापस platक्रमm_add_devices(sa11x0_devices, ARRAY_SIZE(sa11x0_devices));
पूर्ण

arch_initcall(sa1100_init);

व्योम __init sa11x0_init_late(व्योम)
अणु
	sa11x0_pm_init();
पूर्ण

पूर्णांक __init sa11x0_रेजिस्टर_fixed_regulator(पूर्णांक n,
	काष्ठा fixed_voltage_config *cfg,
	काष्ठा regulator_consumer_supply *supplies, अचिन्हित num_supplies,
	bool uses_gpio)
अणु
	काष्ठा regulator_init_data *id;

	cfg->init_data = id = kzalloc(माप(*cfg->init_data), GFP_KERNEL);
	अगर (!cfg->init_data)
		वापस -ENOMEM;

	अगर (!uses_gpio)
		id->स्थिरraपूर्णांकs.always_on = 1;
	id->स्थिरraपूर्णांकs.name = cfg->supply_name;
	id->स्थिरraपूर्णांकs.min_uV = cfg->microvolts;
	id->स्थिरraपूर्णांकs.max_uV = cfg->microvolts;
	id->स्थिरraपूर्णांकs.valid_modes_mask = REGULATOR_MODE_NORMAL;
	id->स्थिरraपूर्णांकs.valid_ops_mask = REGULATOR_CHANGE_STATUS;
	id->consumer_supplies = supplies;
	id->num_consumer_supplies = num_supplies;

	platक्रमm_device_रेजिस्टर_resndata(शून्य, "reg-fixed-voltage", n,
					  शून्य, 0, cfg, माप(*cfg));
	वापस 0;
पूर्ण

/*
 * Common I/O mapping:
 *
 * Typically, अटल भव address mappings are as follow:
 *
 * 0xf0000000-0xf3ffffff:	miscellaneous stuff (CPLDs, etc.)
 * 0xf4000000-0xf4ffffff:	SA-1111
 * 0xf5000000-0xf5ffffff:	reserved (used by cache flushing area)
 * 0xf6000000-0xfffeffff:	reserved (पूर्णांकernal SA1100 IO defined above)
 * 0xffff0000-0xffff0fff:	SA1100 exception vectors
 * 0xffff2000-0xffff2fff:	Minicache copy_user_page area
 *
 * Below 0xe8000000 is reserved क्रम vm allocation.
 *
 * The machine specअगरic code must provide the extra mapping beside the
 * शेष mapping provided here.
 */

अटल काष्ठा map_desc standard_io_desc[] __initdata = अणु
	अणु	/* PCM */
		.भव	=  0xf8000000,
		.pfn		= __phys_to_pfn(0x80000000),
		.length		= 0x00100000,
		.type		= MT_DEVICE
	पूर्ण, अणु	/* SCM */
		.भव	=  0xfa000000,
		.pfn		= __phys_to_pfn(0x90000000),
		.length		= 0x00100000,
		.type		= MT_DEVICE
	पूर्ण, अणु	/* MER */
		.भव	=  0xfc000000,
		.pfn		= __phys_to_pfn(0xa0000000),
		.length		= 0x00100000,
		.type		= MT_DEVICE
	पूर्ण, अणु	/* LCD + DMA */
		.भव	=  0xfe000000,
		.pfn		= __phys_to_pfn(0xb0000000),
		.length		= 0x00200000,
		.type		= MT_DEVICE
	पूर्ण,
पूर्ण;

व्योम __init sa1100_map_io(व्योम)
अणु
	iotable_init(standard_io_desc, ARRAY_SIZE(standard_io_desc));
पूर्ण

व्योम __init sa1100_समयr_init(व्योम)
अणु
	pxa_समयr_nodt_init(IRQ_OST0, io_p2v(0x90000000));
पूर्ण

अटल काष्ठा resource irq_resource =
	DEFINE_RES_MEM_NAMED(0x90050000, SZ_64K, "irqs");

व्योम __init sa1100_init_irq(व्योम)
अणु
	request_resource(&iomem_resource, &irq_resource);

	sa11x0_init_irq_nodt(IRQ_GPIO0_SC, irq_resource.start);

	sa1100_init_gpio();
	sa11xx_clk_init();
पूर्ण

/*
 * Disable the memory bus request/grant संकेतs on the SA1110 to
 * ensure that we करोn't receive spurious memory requests.  We set
 * the MBGNT संकेत false to ensure the SA1111 करोesn't own the
 * SDRAM bus.
 */
व्योम sa1110_mb_disable(व्योम)
अणु
	अचिन्हित दीर्घ flags;

	local_irq_save(flags);
	
	PGSR &= ~GPIO_MBGNT;
	GPCR = GPIO_MBGNT;
	GPDR = (GPDR & ~GPIO_MBREQ) | GPIO_MBGNT;

	GAFR &= ~(GPIO_MBGNT | GPIO_MBREQ);

	local_irq_restore(flags);
पूर्ण

/*
 * If the प्रणाली is going to use the SA-1111 DMA engines, set up
 * the memory bus request/grant pins.
 */
व्योम sa1110_mb_enable(व्योम)
अणु
	अचिन्हित दीर्घ flags;

	local_irq_save(flags);

	PGSR &= ~GPIO_MBGNT;
	GPCR = GPIO_MBGNT;
	GPDR = (GPDR & ~GPIO_MBREQ) | GPIO_MBGNT;

	GAFR |= (GPIO_MBGNT | GPIO_MBREQ);
	TUCR |= TUCR_MR;

	local_irq_restore(flags);
पूर्ण

पूर्णांक sa11x0_gpio_set_wake(अचिन्हित पूर्णांक gpio, अचिन्हित पूर्णांक on)
अणु
	अगर (on)
		PWER |= BIT(gpio);
	अन्यथा
		PWER &= ~BIT(gpio);

	वापस 0;
पूर्ण

पूर्णांक sa11x0_sc_set_wake(अचिन्हित पूर्णांक irq, अचिन्हित पूर्णांक on)
अणु
	अगर (BIT(irq) != IC_RTCAlrm)
		वापस -EINVAL;

	अगर (on)
		PWER |= PWER_RTC;
	अन्यथा
		PWER &= ~PWER_RTC;

	वापस 0;
पूर्ण
