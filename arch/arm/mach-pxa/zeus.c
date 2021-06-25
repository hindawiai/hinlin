<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 *  Support क्रम the Arcom ZEUS.
 *
 *  Copyright (C) 2006 Arcom Control Systems Ltd.
 *
 *  Loosely based on Arcom's 2.6.16.28.
 *  Maपूर्णांकained by Marc Zyngier <maz@misterjones.org>
 */

#समावेश <linux/cpufreq.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/leds.h>
#समावेश <linux/irq.h>
#समावेश <linux/pm.h>
#समावेश <linux/property.h>
#समावेश <linux/gpपन.स>
#समावेश <linux/gpio/machine.h>
#समावेश <linux/serial_8250.h>
#समावेश <linux/dm9000.h>
#समावेश <linux/mmc/host.h>
#समावेश <linux/spi/spi.h>
#समावेश <linux/spi/pxa2xx_spi.h>
#समावेश <linux/mtd/mtd.h>
#समावेश <linux/mtd/partitions.h>
#समावेश <linux/mtd/physmap.h>
#समावेश <linux/i2c.h>
#समावेश <linux/platक्रमm_data/i2c-pxa.h>
#समावेश <linux/platक्रमm_data/pca953x.h>
#समावेश <linux/apm-emulation.h>
#समावेश <linux/regulator/fixed.h>
#समावेश <linux/regulator/machine.h>

#समावेश <यंत्र/mach-types.h>
#समावेश <यंत्र/suspend.h>
#समावेश <यंत्र/प्रणाली_info.h>
#समावेश <यंत्र/mach/arch.h>
#समावेश <यंत्र/mach/map.h>

#समावेश "pxa27x.h"
#समावेश "devices.h"
#समावेश <mach/regs-uart.h>
#समावेश <linux/platक्रमm_data/usb-ohci-pxa27x.h>
#समावेश <linux/platक्रमm_data/mmc-pxamci.h>
#समावेश "pxa27x-udc.h"
#समावेश "udc.h"
#समावेश <linux/platक्रमm_data/video-pxafb.h>
#समावेश "pm.h"
#समावेश <mach/audपन.स>
#समावेश <linux/platक्रमm_data/pcmcia-pxa2xx_viper.h>
#समावेश "zeus.h"
#समावेश <mach/smemc.h>

#समावेश "generic.h"

/*
 * Interrupt handling
 */

अटल अचिन्हित दीर्घ zeus_irq_enabled_mask;
अटल स्थिर पूर्णांक zeus_isa_irqs[] = अणु 3, 4, 5, 6, 7, 10, 11, 12, पूर्ण;
अटल स्थिर पूर्णांक zeus_isa_irq_map[] = अणु
	0,		/* ISA irq #0, invalid */
	0,		/* ISA irq #1, invalid */
	0,		/* ISA irq #2, invalid */
	1 << 0,		/* ISA irq #3 */
	1 << 1,		/* ISA irq #4 */
	1 << 2,		/* ISA irq #5 */
	1 << 3,		/* ISA irq #6 */
	1 << 4,		/* ISA irq #7 */
	0,		/* ISA irq #8, invalid */
	0,		/* ISA irq #9, invalid */
	1 << 5,		/* ISA irq #10 */
	1 << 6,		/* ISA irq #11 */
	1 << 7,		/* ISA irq #12 */
पूर्ण;

अटल अंतरभूत पूर्णांक zeus_irq_to_biपंचांगask(अचिन्हित पूर्णांक irq)
अणु
	वापस zeus_isa_irq_map[irq - PXA_ISA_IRQ(0)];
पूर्ण

अटल अंतरभूत पूर्णांक zeus_bit_to_irq(पूर्णांक bit)
अणु
	वापस zeus_isa_irqs[bit] + PXA_ISA_IRQ(0);
पूर्ण

अटल व्योम zeus_ack_irq(काष्ठा irq_data *d)
अणु
	__raw_ग_लिखोw(zeus_irq_to_biपंचांगask(d->irq), ZEUS_CPLD_ISA_IRQ);
पूर्ण

अटल व्योम zeus_mask_irq(काष्ठा irq_data *d)
अणु
	zeus_irq_enabled_mask &= ~(zeus_irq_to_biपंचांगask(d->irq));
पूर्ण

अटल व्योम zeus_unmask_irq(काष्ठा irq_data *d)
अणु
	zeus_irq_enabled_mask |= zeus_irq_to_biपंचांगask(d->irq);
पूर्ण

अटल अंतरभूत अचिन्हित दीर्घ zeus_irq_pending(व्योम)
अणु
	वापस __raw_पढ़ोw(ZEUS_CPLD_ISA_IRQ) & zeus_irq_enabled_mask;
पूर्ण

अटल व्योम zeus_irq_handler(काष्ठा irq_desc *desc)
अणु
	अचिन्हित पूर्णांक irq;
	अचिन्हित दीर्घ pending;

	pending = zeus_irq_pending();
	करो अणु
		/* we're in a chained irq handler,
		 * so ack the पूर्णांकerrupt by hand */
		desc->irq_data.chip->irq_ack(&desc->irq_data);

		अगर (likely(pending)) अणु
			irq = zeus_bit_to_irq(__ffs(pending));
			generic_handle_irq(irq);
		पूर्ण
		pending = zeus_irq_pending();
	पूर्ण जबतक (pending);
पूर्ण

अटल काष्ठा irq_chip zeus_irq_chip = अणु
	.name		= "ISA",
	.irq_ack	= zeus_ack_irq,
	.irq_mask	= zeus_mask_irq,
	.irq_unmask	= zeus_unmask_irq,
पूर्ण;

अटल व्योम __init zeus_init_irq(व्योम)
अणु
	पूर्णांक level;
	पूर्णांक isa_irq;

	pxa27x_init_irq();

	/* Peripheral IRQs. It would be nice to move those inside driver
	   configuration, but it is not supported at the moment. */
	irq_set_irq_type(gpio_to_irq(ZEUS_AC97_GPIO), IRQ_TYPE_EDGE_RISING);
	irq_set_irq_type(gpio_to_irq(ZEUS_WAKEUP_GPIO), IRQ_TYPE_EDGE_RISING);
	irq_set_irq_type(gpio_to_irq(ZEUS_PTT_GPIO), IRQ_TYPE_EDGE_RISING);
	irq_set_irq_type(gpio_to_irq(ZEUS_EXTGPIO_GPIO),
			 IRQ_TYPE_EDGE_FALLING);
	irq_set_irq_type(gpio_to_irq(ZEUS_CAN_GPIO), IRQ_TYPE_EDGE_FALLING);

	/* Setup ISA IRQs */
	क्रम (level = 0; level < ARRAY_SIZE(zeus_isa_irqs); level++) अणु
		isa_irq = zeus_bit_to_irq(level);
		irq_set_chip_and_handler(isa_irq, &zeus_irq_chip,
					 handle_edge_irq);
		irq_clear_status_flags(isa_irq, IRQ_NOREQUEST | IRQ_NOPROBE);
	पूर्ण

	irq_set_irq_type(gpio_to_irq(ZEUS_ISA_GPIO), IRQ_TYPE_EDGE_RISING);
	irq_set_chained_handler(gpio_to_irq(ZEUS_ISA_GPIO), zeus_irq_handler);
पूर्ण


/*
 * Platक्रमm devices
 */

/* Flash */
अटल काष्ठा resource zeus_mtd_resources[] = अणु
	[0] = अणु /* NOR Flash (up to 64MB) */
		.start	= ZEUS_FLASH_PHYS,
		.end	= ZEUS_FLASH_PHYS + SZ_64M - 1,
		.flags	= IORESOURCE_MEM,
	पूर्ण,
	[1] = अणु /* SRAM */
		.start	= ZEUS_SRAM_PHYS,
		.end	= ZEUS_SRAM_PHYS + SZ_512K - 1,
		.flags	= IORESOURCE_MEM,
	पूर्ण,
पूर्ण;

अटल काष्ठा physmap_flash_data zeus_flash_data[] = अणु
	[0] = अणु
		.width		= 2,
		.parts		= शून्य,
		.nr_parts	= 0,
	पूर्ण,
पूर्ण;

अटल काष्ठा platक्रमm_device zeus_mtd_devices[] = अणु
	[0] = अणु
		.name		= "physmap-flash",
		.id		= 0,
		.dev		= अणु
			.platक्रमm_data = &zeus_flash_data[0],
		पूर्ण,
		.resource	= &zeus_mtd_resources[0],
		.num_resources	= 1,
	पूर्ण,
पूर्ण;

/* Serial */
अटल काष्ठा resource zeus_serial_resources[] = अणु
	अणु
		.start	= 0x10000000,
		.end	= 0x1000000f,
		.flags	= IORESOURCE_MEM,
	पूर्ण,
	अणु
		.start	= 0x10800000,
		.end	= 0x1080000f,
		.flags	= IORESOURCE_MEM,
	पूर्ण,
	अणु
		.start	= 0x11000000,
		.end	= 0x1100000f,
		.flags	= IORESOURCE_MEM,
	पूर्ण,
	अणु
		.start	= 0x40100000,
		.end	= 0x4010001f,
		.flags	= IORESOURCE_MEM,
	पूर्ण,
	अणु
		.start	= 0x40200000,
		.end	= 0x4020001f,
		.flags	= IORESOURCE_MEM,
	पूर्ण,
	अणु
		.start	= 0x40700000,
		.end	= 0x4070001f,
		.flags	= IORESOURCE_MEM,
	पूर्ण,
पूर्ण;

अटल काष्ठा plat_serial8250_port serial_platक्रमm_data[] = अणु
	/* External UARTs */
	/* FIXME: Shared IRQs on COM1-COM4 will not work properly on v1i1 hardware. */
	अणु /* COM1 */
		.mapbase	= 0x10000000,
		.irq		= PXA_GPIO_TO_IRQ(ZEUS_UARTA_GPIO),
		.irqflags	= IRQF_TRIGGER_RISING,
		.uartclk	= 14745600,
		.regshअगरt	= 1,
		.flags		= UPF_IOREMAP | UPF_BOOT_AUTOCONF | UPF_SKIP_TEST,
		.iotype		= UPIO_MEM,
	पूर्ण,
	अणु /* COM2 */
		.mapbase	= 0x10800000,
		.irq		= PXA_GPIO_TO_IRQ(ZEUS_UARTB_GPIO),
		.irqflags	= IRQF_TRIGGER_RISING,
		.uartclk	= 14745600,
		.regshअगरt	= 1,
		.flags		= UPF_IOREMAP | UPF_BOOT_AUTOCONF | UPF_SKIP_TEST,
		.iotype		= UPIO_MEM,
	पूर्ण,
	अणु /* COM3 */
		.mapbase	= 0x11000000,
		.irq		= PXA_GPIO_TO_IRQ(ZEUS_UARTC_GPIO),
		.irqflags	= IRQF_TRIGGER_RISING,
		.uartclk	= 14745600,
		.regshअगरt	= 1,
		.flags		= UPF_IOREMAP | UPF_BOOT_AUTOCONF | UPF_SKIP_TEST,
		.iotype		= UPIO_MEM,
	पूर्ण,
	अणु /* COM4 */
		.mapbase	= 0x11800000,
		.irq		= PXA_GPIO_TO_IRQ(ZEUS_UARTD_GPIO),
		.irqflags	= IRQF_TRIGGER_RISING,
		.uartclk	= 14745600,
		.regshअगरt	= 1,
		.flags		= UPF_IOREMAP | UPF_BOOT_AUTOCONF | UPF_SKIP_TEST,
		.iotype		= UPIO_MEM,
	पूर्ण,
	/* Internal UARTs */
	अणु /* FFUART */
		.membase	= (व्योम *)&FFUART,
		.mapbase	= __PREG(FFUART),
		.irq		= IRQ_FFUART,
		.uartclk	= 921600 * 16,
		.regshअगरt	= 2,
		.flags		= UPF_BOOT_AUTOCONF | UPF_SKIP_TEST,
		.iotype		= UPIO_MEM,
	पूर्ण,
	अणु /* BTUART */
		.membase	= (व्योम *)&BTUART,
		.mapbase	= __PREG(BTUART),
		.irq		= IRQ_BTUART,
		.uartclk	= 921600 * 16,
		.regshअगरt	= 2,
		.flags		= UPF_BOOT_AUTOCONF | UPF_SKIP_TEST,
		.iotype		= UPIO_MEM,
	पूर्ण,
	अणु /* STUART */
		.membase	= (व्योम *)&STUART,
		.mapbase	= __PREG(STUART),
		.irq		= IRQ_STUART,
		.uartclk	= 921600 * 16,
		.regshअगरt	= 2,
		.flags		= UPF_BOOT_AUTOCONF | UPF_SKIP_TEST,
		.iotype		= UPIO_MEM,
	पूर्ण,
	अणु पूर्ण,
पूर्ण;

अटल काष्ठा platक्रमm_device zeus_serial_device = अणु
	.name = "serial8250",
	.id   = PLAT8250_DEV_PLATFORM,
	.dev  = अणु
		.platक्रमm_data = serial_platक्रमm_data,
	पूर्ण,
	.num_resources	= ARRAY_SIZE(zeus_serial_resources),
	.resource	= zeus_serial_resources,
पूर्ण;

/* Ethernet */
अटल काष्ठा resource zeus_dm9k0_resource[] = अणु
	[0] = अणु
		.start = ZEUS_ETH0_PHYS,
		.end   = ZEUS_ETH0_PHYS + 1,
		.flags = IORESOURCE_MEM
	पूर्ण,
	[1] = अणु
		.start = ZEUS_ETH0_PHYS + 2,
		.end   = ZEUS_ETH0_PHYS + 3,
		.flags = IORESOURCE_MEM
	पूर्ण,
	[2] = अणु
		.start = PXA_GPIO_TO_IRQ(ZEUS_ETH0_GPIO),
		.end   = PXA_GPIO_TO_IRQ(ZEUS_ETH0_GPIO),
		.flags = IORESOURCE_IRQ | IORESOURCE_IRQ_LOWEDGE,
	पूर्ण,
पूर्ण;

अटल काष्ठा resource zeus_dm9k1_resource[] = अणु
	[0] = अणु
		.start = ZEUS_ETH1_PHYS,
		.end   = ZEUS_ETH1_PHYS + 1,
		.flags = IORESOURCE_MEM
	पूर्ण,
	[1] = अणु
		.start = ZEUS_ETH1_PHYS + 2,
		.end   = ZEUS_ETH1_PHYS + 3,
		.flags = IORESOURCE_MEM,
	पूर्ण,
	[2] = अणु
		.start = PXA_GPIO_TO_IRQ(ZEUS_ETH1_GPIO),
		.end   = PXA_GPIO_TO_IRQ(ZEUS_ETH1_GPIO),
		.flags = IORESOURCE_IRQ | IORESOURCE_IRQ_LOWEDGE,
	पूर्ण,
पूर्ण;

अटल काष्ठा dm9000_plat_data zeus_dm9k_platdata = अणु
	.flags		= DM9000_PLATF_16BITONLY,
पूर्ण;

अटल काष्ठा platक्रमm_device zeus_dm9k0_device = अणु
	.name		= "dm9000",
	.id		= 0,
	.num_resources	= ARRAY_SIZE(zeus_dm9k0_resource),
	.resource	= zeus_dm9k0_resource,
	.dev		= अणु
		.platक्रमm_data = &zeus_dm9k_platdata,
	पूर्ण
पूर्ण;

अटल काष्ठा platक्रमm_device zeus_dm9k1_device = अणु
	.name		= "dm9000",
	.id		= 1,
	.num_resources	= ARRAY_SIZE(zeus_dm9k1_resource),
	.resource	= zeus_dm9k1_resource,
	.dev		= अणु
		.platक्रमm_data = &zeus_dm9k_platdata,
	पूर्ण
पूर्ण;

/* External SRAM */
अटल काष्ठा resource zeus_sram_resource = अणु
	.start		= ZEUS_SRAM_PHYS,
	.end		= ZEUS_SRAM_PHYS + ZEUS_SRAM_SIZE * 2 - 1,
	.flags		= IORESOURCE_MEM,
पूर्ण;

अटल काष्ठा platक्रमm_device zeus_sram_device = अणु
	.name		= "pxa2xx-8bit-sram",
	.id		= 0,
	.num_resources	= 1,
	.resource	= &zeus_sram_resource,
पूर्ण;

/* SPI पूर्णांकerface on SSP3 */
अटल काष्ठा pxa2xx_spi_controller pxa2xx_spi_ssp3_master_info = अणु
	.num_chipselect = 1,
	.enable_dma     = 1,
पूर्ण;

/* CAN bus on SPI */
अटल काष्ठा regulator_consumer_supply can_regulator_consumer =
	REGULATOR_SUPPLY("vdd", "spi3.0");

अटल काष्ठा regulator_init_data can_regulator_init_data = अणु
	.स्थिरraपूर्णांकs	= अणु
		.valid_ops_mask	= REGULATOR_CHANGE_STATUS,
	पूर्ण,
	.consumer_supplies	= &can_regulator_consumer,
	.num_consumer_supplies	= 1,
पूर्ण;

अटल काष्ठा fixed_voltage_config can_regulator_pdata = अणु
	.supply_name	= "CAN_SHDN",
	.microvolts	= 3300000,
	.init_data	= &can_regulator_init_data,
पूर्ण;

अटल काष्ठा platक्रमm_device can_regulator_device = अणु
	.name	= "reg-fixed-voltage",
	.id	= 0,
	.dev	= अणु
		.platक्रमm_data	= &can_regulator_pdata,
	पूर्ण,
पूर्ण;

अटल काष्ठा gpiod_lookup_table can_regulator_gpiod_table = अणु
	.dev_id = "reg-fixed-voltage.0",
	.table = अणु
		GPIO_LOOKUP("gpio-pxa", ZEUS_CAN_SHDN_GPIO,
			    शून्य, GPIO_ACTIVE_LOW),
		अणु पूर्ण,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा property_entry mcp251x_properties[] = अणु
	PROPERTY_ENTRY_U32("clock-frequency", 16000000),
	अणुपूर्ण
पूर्ण;

अटल स्थिर काष्ठा software_node mcp251x_node = अणु
	.properties = mcp251x_properties,
पूर्ण;

अटल काष्ठा spi_board_info zeus_spi_board_info[] = अणु
	[0] = अणु
		.modalias	= "mcp2515",
		.swnode		= &mcp251x_node,
		.irq		= PXA_GPIO_TO_IRQ(ZEUS_CAN_GPIO),
		.max_speed_hz	= 1*1000*1000,
		.bus_num	= 3,
		.mode		= SPI_MODE_0,
		.chip_select	= 0,
	पूर्ण,
पूर्ण;

/* Leds */
अटल काष्ठा gpio_led zeus_leds[] = अणु
	[0] = अणु
		.name		 = "zeus:yellow:1",
		.शेष_trigger = "heartbeat",
		.gpio		 = ZEUS_EXT0_GPIO(3),
		.active_low	 = 1,
	पूर्ण,
	[1] = अणु
		.name		 = "zeus:yellow:2",
		.शेष_trigger = "default-on",
		.gpio		 = ZEUS_EXT0_GPIO(4),
		.active_low	 = 1,
	पूर्ण,
	[2] = अणु
		.name		 = "zeus:yellow:3",
		.शेष_trigger = "default-on",
		.gpio		 = ZEUS_EXT0_GPIO(5),
		.active_low	 = 1,
	पूर्ण,
पूर्ण;

अटल काष्ठा gpio_led_platक्रमm_data zeus_leds_info = अणु
	.leds		= zeus_leds,
	.num_leds	= ARRAY_SIZE(zeus_leds),
पूर्ण;

अटल काष्ठा platक्रमm_device zeus_leds_device = अणु
	.name		= "leds-gpio",
	.id		= -1,
	.dev		= अणु
		.platक्रमm_data	= &zeus_leds_info,
	पूर्ण,
पूर्ण;

अटल व्योम zeus_cf_reset(पूर्णांक state)
अणु
	u16 cpld_state = __raw_पढ़ोw(ZEUS_CPLD_CONTROL);

	अगर (state)
		cpld_state |= ZEUS_CPLD_CONTROL_CF_RST;
	अन्यथा
		cpld_state &= ~ZEUS_CPLD_CONTROL_CF_RST;

	__raw_ग_लिखोw(cpld_state, ZEUS_CPLD_CONTROL);
पूर्ण

अटल काष्ठा arcom_pcmcia_pdata zeus_pcmcia_info = अणु
	.cd_gpio	= ZEUS_CF_CD_GPIO,
	.rdy_gpio	= ZEUS_CF_RDY_GPIO,
	.pwr_gpio	= ZEUS_CF_PWEN_GPIO,
	.reset		= zeus_cf_reset,
पूर्ण;

अटल काष्ठा platक्रमm_device zeus_pcmcia_device = अणु
	.name		= "zeus-pcmcia",
	.id		= -1,
	.dev		= अणु
		.platक्रमm_data	= &zeus_pcmcia_info,
	पूर्ण,
पूर्ण;

अटल काष्ठा resource zeus_max6369_resource = अणु
	.start		= ZEUS_CPLD_EXTWDOG_PHYS,
	.end		= ZEUS_CPLD_EXTWDOG_PHYS,
	.flags		= IORESOURCE_MEM,
पूर्ण;

काष्ठा platक्रमm_device zeus_max6369_device = अणु
	.name		= "max6369_wdt",
	.id		= -1,
	.resource	= &zeus_max6369_resource,
	.num_resources	= 1,
पूर्ण;

/* AC'97 */
अटल pxa2xx_audio_ops_t zeus_ac97_info = अणु
	.reset_gpio = 95,
पूर्ण;


/*
 * USB host
 */

अटल काष्ठा regulator_consumer_supply zeus_ohci_regulator_supplies[] = अणु
	REGULATOR_SUPPLY("vbus2", "pxa27x-ohci"),
पूर्ण;

अटल काष्ठा regulator_init_data zeus_ohci_regulator_data = अणु
	.स्थिरraपूर्णांकs = अणु
		.valid_ops_mask		= REGULATOR_CHANGE_STATUS,
	पूर्ण,
	.num_consumer_supplies	= ARRAY_SIZE(zeus_ohci_regulator_supplies),
	.consumer_supplies	= zeus_ohci_regulator_supplies,
पूर्ण;

अटल काष्ठा fixed_voltage_config zeus_ohci_regulator_config = अणु
	.supply_name		= "vbus2",
	.microvolts		= 5000000, /* 5.0V */
	.startup_delay		= 0,
	.init_data		= &zeus_ohci_regulator_data,
पूर्ण;

अटल काष्ठा platक्रमm_device zeus_ohci_regulator_device = अणु
	.name		= "reg-fixed-voltage",
	.id		= 1,
	.dev = अणु
		.platक्रमm_data = &zeus_ohci_regulator_config,
	पूर्ण,
पूर्ण;

अटल काष्ठा gpiod_lookup_table zeus_ohci_regulator_gpiod_table = अणु
	.dev_id = "reg-fixed-voltage.0",
	.table = अणु
		GPIO_LOOKUP("gpio-pxa", ZEUS_USB2_PWREN_GPIO,
			    शून्य, GPIO_ACTIVE_HIGH),
		अणु पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा pxaohci_platक्रमm_data zeus_ohci_platक्रमm_data = अणु
	.port_mode	= PMM_NPS_MODE,
	/* Clear Power Control Polarity Low and set Power Sense
	 * Polarity Low. Supply घातer to USB ports. */
	.flags		= ENABLE_PORT_ALL | POWER_SENSE_LOW,
पूर्ण;

अटल व्योम __init zeus_रेजिस्टर_ohci(व्योम)
अणु
	/* Port 2 is shared between host and client पूर्णांकerface. */
	UP2OCR = UP2OCR_HXOE | UP2OCR_HXS | UP2OCR_DMPDE | UP2OCR_DPPDE;

	pxa_set_ohci_info(&zeus_ohci_platक्रमm_data);
पूर्ण

/*
 * Flat Panel
 */

अटल व्योम zeus_lcd_घातer(पूर्णांक on, काष्ठा fb_var_screeninfo *si)
अणु
	gpio_set_value(ZEUS_LCD_EN_GPIO, on);
पूर्ण

अटल व्योम zeus_backlight_घातer(पूर्णांक on)
अणु
	gpio_set_value(ZEUS_BKLEN_GPIO, on);
पूर्ण

अटल पूर्णांक zeus_setup_fb_gpios(व्योम)
अणु
	पूर्णांक err;

	अगर ((err = gpio_request(ZEUS_LCD_EN_GPIO, "LCD_EN")))
		जाओ out_err;

	अगर ((err = gpio_direction_output(ZEUS_LCD_EN_GPIO, 0)))
		जाओ out_err_lcd;

	अगर ((err = gpio_request(ZEUS_BKLEN_GPIO, "BKLEN")))
		जाओ out_err_lcd;

	अगर ((err = gpio_direction_output(ZEUS_BKLEN_GPIO, 0)))
		जाओ out_err_bkl;

	वापस 0;

out_err_bkl:
	gpio_मुक्त(ZEUS_BKLEN_GPIO);
out_err_lcd:
	gpio_मुक्त(ZEUS_LCD_EN_GPIO);
out_err:
	वापस err;
पूर्ण

अटल काष्ठा pxafb_mode_info zeus_fb_mode_info[] = अणु
	अणु
		.pixघड़ी       = 39722,

		.xres           = 640,
		.yres           = 480,

		.bpp            = 16,

		.hsync_len      = 63,
		.left_margin    = 16,
		.right_margin   = 81,

		.vsync_len      = 2,
		.upper_margin   = 12,
		.lower_margin   = 31,

		.sync		= 0,
	पूर्ण,
पूर्ण;

अटल काष्ठा pxafb_mach_info zeus_fb_info = अणु
	.modes			= zeus_fb_mode_info,
	.num_modes		= 1,
	.lcd_conn		= LCD_COLOR_TFT_16BPP | LCD_PCLK_EDGE_FALL,
	.pxafb_lcd_घातer	= zeus_lcd_घातer,
	.pxafb_backlight_घातer	= zeus_backlight_घातer,
पूर्ण;

/*
 * MMC/SD Device
 *
 * The card detect पूर्णांकerrupt isn't debounced so we delay it by 250ms
 * to give the card a chance to fully insert/eject.
 */

अटल काष्ठा pxamci_platक्रमm_data zeus_mci_platक्रमm_data = अणु
	.ocr_mask		= MMC_VDD_32_33|MMC_VDD_33_34,
	.detect_delay_ms	= 250,
	.gpio_card_ro_invert	= 1,
पूर्ण;

अटल काष्ठा gpiod_lookup_table zeus_mci_gpio_table = अणु
	.dev_id = "pxa2xx-mci.0",
	.table = अणु
		GPIO_LOOKUP("gpio-pxa", ZEUS_MMC_CD_GPIO,
			    "cd", GPIO_ACTIVE_LOW),
		GPIO_LOOKUP("gpio-pxa", ZEUS_MMC_WP_GPIO,
			    "wp", GPIO_ACTIVE_HIGH),
		अणु पूर्ण,
	पूर्ण,
पूर्ण;

/*
 * USB Device Controller
 */
अटल व्योम zeus_udc_command(पूर्णांक cmd)
अणु
	चयन (cmd) अणु
	हाल PXA2XX_UDC_CMD_DISCONNECT:
		pr_info("zeus: disconnecting USB client\n");
		UP2OCR = UP2OCR_HXOE | UP2OCR_HXS | UP2OCR_DMPDE | UP2OCR_DPPDE;
		अवरोध;

	हाल PXA2XX_UDC_CMD_CONNECT:
		pr_info("zeus: connecting USB client\n");
		UP2OCR = UP2OCR_HXOE | UP2OCR_DPPUE;
		अवरोध;
	पूर्ण
पूर्ण

अटल काष्ठा pxa2xx_udc_mach_info zeus_udc_info = अणु
	.udc_command = zeus_udc_command,
पूर्ण;

अटल काष्ठा platक्रमm_device *zeus_devices[] __initdata = अणु
	&zeus_serial_device,
	&zeus_mtd_devices[0],
	&zeus_dm9k0_device,
	&zeus_dm9k1_device,
	&zeus_sram_device,
	&zeus_leds_device,
	&zeus_pcmcia_device,
	&zeus_max6369_device,
	&can_regulator_device,
	&zeus_ohci_regulator_device,
पूर्ण;

#अगर_घोषित CONFIG_PM
अटल व्योम zeus_घातer_off(व्योम)
अणु
	local_irq_disable();
	cpu_suspend(PWRMODE_DEEPSLEEP, pxa27x_finish_suspend);
पूर्ण
#अन्यथा
#घोषणा zeus_घातer_off   शून्य
#पूर्ण_अगर

#अगर_घोषित CONFIG_APM_EMULATION
अटल व्योम zeus_get_घातer_status(काष्ठा apm_घातer_info *info)
अणु
	/* Power supply is always present */
	info->ac_line_status	= APM_AC_ONLINE;
	info->battery_status	= APM_BATTERY_STATUS_NOT_PRESENT;
	info->battery_flag	= APM_BATTERY_FLAG_NOT_PRESENT;
पूर्ण

अटल अंतरभूत व्योम zeus_setup_apm(व्योम)
अणु
	apm_get_घातer_status = zeus_get_घातer_status;
पूर्ण
#अन्यथा
अटल अंतरभूत व्योम zeus_setup_apm(व्योम)
अणु
पूर्ण
#पूर्ण_अगर

अटल पूर्णांक zeus_get_pcb_info(काष्ठा i2c_client *client, अचिन्हित gpio,
			     अचिन्हित ngpio, व्योम *context)
अणु
	पूर्णांक i;
	u8 pcb_info = 0;

	क्रम (i = 0; i < 8; i++) अणु
		पूर्णांक pcb_bit = gpio + i + 8;

		अगर (gpio_request(pcb_bit, "pcb info")) अणु
			dev_err(&client->dev, "Can't request pcb info %d\n", i);
			जारी;
		पूर्ण

		अगर (gpio_direction_input(pcb_bit)) अणु
			dev_err(&client->dev, "Can't read pcb info %d\n", i);
			gpio_मुक्त(pcb_bit);
			जारी;
		पूर्ण

		pcb_info |= !!gpio_get_value(pcb_bit) << i;

		gpio_मुक्त(pcb_bit);
	पूर्ण

	dev_info(&client->dev, "Zeus PCB version %d issue %d\n",
		 pcb_info >> 4, pcb_info & 0xf);

	वापस 0;
पूर्ण

अटल काष्ठा pca953x_platक्रमm_data zeus_pca953x_pdata[] = अणु
	[0] = अणु .gpio_base	= ZEUS_EXT0_GPIO_BASE, पूर्ण,
	[1] = अणु
		.gpio_base	= ZEUS_EXT1_GPIO_BASE,
		.setup		= zeus_get_pcb_info,
	पूर्ण,
	[2] = अणु .gpio_base = ZEUS_USER_GPIO_BASE, पूर्ण,
पूर्ण;

अटल काष्ठा i2c_board_info __initdata zeus_i2c_devices[] = अणु
	अणु
		I2C_BOARD_INFO("pca9535",	0x21),
		.platक्रमm_data	= &zeus_pca953x_pdata[0],
	पूर्ण,
	अणु
		I2C_BOARD_INFO("pca9535",	0x22),
		.platक्रमm_data	= &zeus_pca953x_pdata[1],
	पूर्ण,
	अणु
		I2C_BOARD_INFO("pca9535",	0x20),
		.platक्रमm_data	= &zeus_pca953x_pdata[2],
		.irq		= PXA_GPIO_TO_IRQ(ZEUS_EXTGPIO_GPIO),
	पूर्ण,
	अणु I2C_BOARD_INFO("lm75a",	0x48) पूर्ण,
	अणु I2C_BOARD_INFO("24c01",	0x50) पूर्ण,
	अणु I2C_BOARD_INFO("isl1208",	0x6f) पूर्ण,
पूर्ण;

अटल mfp_cfg_t zeus_pin_config[] __initdata = अणु
	/* AC97 */
	GPIO28_AC97_BITCLK,
	GPIO29_AC97_SDATA_IN_0,
	GPIO30_AC97_SDATA_OUT,
	GPIO31_AC97_SYNC,

	GPIO15_nCS_1,
	GPIO78_nCS_2,
	GPIO80_nCS_4,
	GPIO33_nCS_5,

	GPIO22_GPIO,
	GPIO32_MMC_CLK,
	GPIO92_MMC_DAT_0,
	GPIO109_MMC_DAT_1,
	GPIO110_MMC_DAT_2,
	GPIO111_MMC_DAT_3,
	GPIO112_MMC_CMD,

	GPIO88_USBH1_PWR,
	GPIO89_USBH1_PEN,
	GPIO119_USBH2_PWR,
	GPIO120_USBH2_PEN,

	GPIO86_LCD_LDD_16,
	GPIO87_LCD_LDD_17,

	GPIO102_GPIO,
	GPIO104_CIF_DD_2,
	GPIO105_CIF_DD_1,

	GPIO81_SSP3_TXD,
	GPIO82_SSP3_RXD,
	GPIO83_SSP3_SFRM,
	GPIO84_SSP3_SCLK,

	GPIO48_nPOE,
	GPIO49_nPWE,
	GPIO50_nPIOR,
	GPIO51_nPIOW,
	GPIO85_nPCE_1,
	GPIO54_nPCE_2,
	GPIO79_PSKTSEL,
	GPIO55_nPREG,
	GPIO56_nPWAIT,
	GPIO57_nIOIS16,
	GPIO36_GPIO,		/* CF CD */
	GPIO97_GPIO,		/* CF PWREN */
	GPIO99_GPIO,		/* CF RDY */
पूर्ण;

/*
 * DM9k MSCx settings:	SRAM, 16 bits
 *			17 cycles delay first access
 *			 5 cycles delay next access
 *			13 cycles recovery समय
 *			faster device
 */
#घोषणा DM9K_MSC_VALUE		0xe4c9

अटल व्योम __init zeus_init(व्योम)
अणु
	u16 dm9000_msc = DM9K_MSC_VALUE;
	u32 msc0, msc1;

	प्रणाली_rev = __raw_पढ़ोw(ZEUS_CPLD_VERSION);
	pr_info("Zeus CPLD V%dI%d\n", (प्रणाली_rev & 0xf0) >> 4, (प्रणाली_rev & 0x0f));

	/* Fix timings क्रम dm9000s (CS1/CS2)*/
	msc0 = (__raw_पढ़ोl(MSC0) & 0x0000ffff) | (dm9000_msc << 16);
	msc1 = (__raw_पढ़ोl(MSC1) & 0xffff0000) | dm9000_msc;
	__raw_ग_लिखोl(msc0, MSC0);
	__raw_ग_लिखोl(msc1, MSC1);

	pm_घातer_off = zeus_घातer_off;
	zeus_setup_apm();

	pxa2xx_mfp_config(ARRAY_AND_SIZE(zeus_pin_config));

	gpiod_add_lookup_table(&can_regulator_gpiod_table);
	gpiod_add_lookup_table(&zeus_ohci_regulator_gpiod_table);
	platक्रमm_add_devices(zeus_devices, ARRAY_SIZE(zeus_devices));

	zeus_रेजिस्टर_ohci();

	अगर (zeus_setup_fb_gpios())
		pr_err("Failed to setup fb gpios\n");
	अन्यथा
		pxa_set_fb_info(शून्य, &zeus_fb_info);

	gpiod_add_lookup_table(&zeus_mci_gpio_table);
	pxa_set_mci_info(&zeus_mci_platक्रमm_data);
	pxa_set_udc_info(&zeus_udc_info);
	pxa_set_ac97_info(&zeus_ac97_info);
	pxa_set_i2c_info(शून्य);
	i2c_रेजिस्टर_board_info(0, ARRAY_AND_SIZE(zeus_i2c_devices));
	pxa2xx_set_spi_info(3, &pxa2xx_spi_ssp3_master_info);
	spi_रेजिस्टर_board_info(zeus_spi_board_info, ARRAY_SIZE(zeus_spi_board_info));

	regulator_has_full_स्थिरraपूर्णांकs();
पूर्ण

अटल काष्ठा map_desc zeus_io_desc[] __initdata = अणु
	अणु
		.भव = (अचिन्हित दीर्घ)ZEUS_CPLD_VERSION,
		.pfn     = __phys_to_pfn(ZEUS_CPLD_VERSION_PHYS),
		.length  = 0x1000,
		.type    = MT_DEVICE,
	पूर्ण,
	अणु
		.भव = (अचिन्हित दीर्घ)ZEUS_CPLD_ISA_IRQ,
		.pfn     = __phys_to_pfn(ZEUS_CPLD_ISA_IRQ_PHYS),
		.length  = 0x1000,
		.type    = MT_DEVICE,
	पूर्ण,
	अणु
		.भव = (अचिन्हित दीर्घ)ZEUS_CPLD_CONTROL,
		.pfn     = __phys_to_pfn(ZEUS_CPLD_CONTROL_PHYS),
		.length  = 0x1000,
		.type    = MT_DEVICE,
	पूर्ण,
	अणु
		.भव = (अचिन्हित दीर्घ)ZEUS_PC104IO,
		.pfn     = __phys_to_pfn(ZEUS_PC104IO_PHYS),
		.length  = 0x00800000,
		.type    = MT_DEVICE,
	पूर्ण,
पूर्ण;

अटल व्योम __init zeus_map_io(व्योम)
अणु
	pxa27x_map_io();

	iotable_init(zeus_io_desc, ARRAY_SIZE(zeus_io_desc));

	/* Clear PSPR to ensure a full restart on wake-up. */
	PMCR = PSPR = 0;

	/* enable पूर्णांकernal 32.768Khz oscillator (ignore OSCC_OOK) */
	ग_लिखोl(पढ़ोl(OSCC) | OSCC_OON, OSCC);

	/* Some घड़ी cycles later (from OSCC_ON), programme PCFR (OPDE...).
	 * भग्न chip selects and PCMCIA */
	PCFR = PCFR_OPDE | PCFR_DC_EN | PCFR_FS | PCFR_FP;
पूर्ण

MACHINE_START(ARCOM_ZEUS, "Arcom/Eurotech ZEUS")
	/* Maपूर्णांकainer: Marc Zyngier <maz@misterjones.org> */
	.atag_offset	= 0x100,
	.map_io		= zeus_map_io,
	.nr_irqs	= ZEUS_NR_IRQS,
	.init_irq	= zeus_init_irq,
	.handle_irq	= pxa27x_handle_irq,
	.init_समय	= pxa_समयr_init,
	.init_machine	= zeus_init,
	.restart	= pxa_restart,
MACHINE_END

