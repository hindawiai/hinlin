<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * linux/arch/arm/mach-omap1/board-innovator.c
 *
 * Board specअगरic inits क्रम OMAP-1510 and OMAP-1610 Innovator
 *
 * Copyright (C) 2001 RidgeRun, Inc.
 * Author: Greg Lonnon <glonnon@ridgerun.com>
 *
 * Copyright (C) 2002 MontaVista Software, Inc.
 *
 * Separated FPGA पूर्णांकerrupts from innovator1510.c and cleaned up क्रम 2.6
 * Copyright (C) 2004 Nokia Corporation by Tony Lindrgen <tony@atomide.com>
 */
#समावेश <linux/gpपन.स>
#समावेश <linux/kernel.h>
#समावेश <linux/init.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/delay.h>
#समावेश <linux/mtd/mtd.h>
#समावेश <linux/mtd/partitions.h>
#समावेश <linux/mtd/physmap.h>
#समावेश <linux/input.h>
#समावेश <linux/smc91x.h>
#समावेश <linux/omapfb.h>

#समावेश <यंत्र/mach-types.h>
#समावेश <यंत्र/mach/arch.h>
#समावेश <यंत्र/mach/map.h>

#समावेश <mach/mux.h>
#समावेश "flash.h"
#समावेश <mach/tc.h>
#समावेश <linux/platक्रमm_data/keypad-omap.h>

#समावेश <mach/hardware.h>
#समावेश <mach/usb.h>

#समावेश "iomap.h"
#समावेश "common.h"
#समावेश "mmc.h"

/* At OMAP1610 Innovator the Ethernet is directly connected to CS1 */
#घोषणा INNOVATOR1610_ETHR_START	0x04000300

अटल स्थिर अचिन्हित पूर्णांक innovator_keymap[] = अणु
	KEY(0, 0, KEY_F1),
	KEY(3, 0, KEY_DOWN),
	KEY(1, 1, KEY_F2),
	KEY(2, 1, KEY_RIGHT),
	KEY(0, 2, KEY_F3),
	KEY(1, 2, KEY_F4),
	KEY(2, 2, KEY_UP),
	KEY(2, 3, KEY_ENTER),
	KEY(3, 3, KEY_LEFT),
पूर्ण;

अटल काष्ठा mtd_partition innovator_partitions[] = अणु
	/* bootloader (U-Boot, etc) in first sector */
	अणु
	      .name		= "bootloader",
	      .offset		= 0,
	      .size		= SZ_128K,
	      .mask_flags	= MTD_WRITEABLE, /* क्रमce पढ़ो-only */
	पूर्ण,
	/* bootloader params in the next sector */
	अणु
	      .name		= "params",
	      .offset		= MTDPART_OFS_APPEND,
	      .size		= SZ_128K,
	      .mask_flags	= 0,
	पूर्ण,
	/* kernel */
	अणु
	      .name		= "kernel",
	      .offset		= MTDPART_OFS_APPEND,
	      .size		= SZ_2M,
	      .mask_flags	= 0
	पूर्ण,
	/* rest of flash1 is a file प्रणाली */
	अणु
	      .name		= "rootfs",
	      .offset		= MTDPART_OFS_APPEND,
	      .size		= SZ_16M - SZ_2M - 2 * SZ_128K,
	      .mask_flags	= 0
	पूर्ण,
	/* file प्रणाली */
	अणु
	      .name		= "filesystem",
	      .offset		= MTDPART_OFS_APPEND,
	      .size		= MTDPART_SIZ_FULL,
	      .mask_flags	= 0
	पूर्ण
पूर्ण;

अटल काष्ठा physmap_flash_data innovator_flash_data = अणु
	.width		= 2,
	.set_vpp	= omap1_set_vpp,
	.parts		= innovator_partitions,
	.nr_parts	= ARRAY_SIZE(innovator_partitions),
पूर्ण;

अटल काष्ठा resource innovator_flash_resource = अणु
	.start		= OMAP_CS0_PHYS,
	.end		= OMAP_CS0_PHYS + SZ_32M - 1,
	.flags		= IORESOURCE_MEM,
पूर्ण;

अटल काष्ठा platक्रमm_device innovator_flash_device = अणु
	.name		= "physmap-flash",
	.id		= 0,
	.dev		= अणु
		.platक्रमm_data	= &innovator_flash_data,
	पूर्ण,
	.num_resources	= 1,
	.resource	= &innovator_flash_resource,
पूर्ण;

अटल काष्ठा resource innovator_kp_resources[] = अणु
	[0] = अणु
		.start	= INT_KEYBOARD,
		.end	= INT_KEYBOARD,
		.flags	= IORESOURCE_IRQ,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा matrix_keymap_data innovator_keymap_data = अणु
	.keymap		= innovator_keymap,
	.keymap_size	= ARRAY_SIZE(innovator_keymap),
पूर्ण;

अटल काष्ठा omap_kp_platक्रमm_data innovator_kp_data = अणु
	.rows		= 8,
	.cols		= 8,
	.keymap_data	= &innovator_keymap_data,
	.delay		= 4,
पूर्ण;

अटल काष्ठा platक्रमm_device innovator_kp_device = अणु
	.name		= "omap-keypad",
	.id		= -1,
	.dev		= अणु
		.platक्रमm_data = &innovator_kp_data,
	पूर्ण,
	.num_resources	= ARRAY_SIZE(innovator_kp_resources),
	.resource	= innovator_kp_resources,
पूर्ण;

अटल काष्ठा smc91x_platdata innovator_smc91x_info = अणु
	.flags	= SMC91X_USE_16BIT | SMC91X_NOWAIT,
	.leda	= RPC_LED_100_10,
	.ledb	= RPC_LED_TX_RX,
पूर्ण;

#अगर_घोषित CONFIG_ARCH_OMAP15XX

#समावेश <linux/spi/spi.h>
#समावेश <linux/spi/ads7846.h>


/* Only FPGA needs to be mapped here. All others are करोne with ioremap */
अटल काष्ठा map_desc innovator1510_io_desc[] __initdata = अणु
	अणु
		.भव	= OMAP1510_FPGA_BASE,
		.pfn		= __phys_to_pfn(OMAP1510_FPGA_START),
		.length		= OMAP1510_FPGA_SIZE,
		.type		= MT_DEVICE
	पूर्ण
पूर्ण;

अटल काष्ठा resource innovator1510_smc91x_resources[] = अणु
	[0] = अणु
		.start	= OMAP1510_FPGA_ETHR_START,	/* Physical */
		.end	= OMAP1510_FPGA_ETHR_START + 0xf,
		.flags	= IORESOURCE_MEM,
	पूर्ण,
	[1] = अणु
		.start	= OMAP1510_INT_ETHER,
		.end	= OMAP1510_INT_ETHER,
		.flags	= IORESOURCE_IRQ | IORESOURCE_IRQ_HIGHEDGE,
	पूर्ण,
पूर्ण;

अटल काष्ठा platक्रमm_device innovator1510_smc91x_device = अणु
	.name		= "smc91x",
	.id		= 0,
	.dev	= अणु
		.platक्रमm_data	= &innovator_smc91x_info,
	पूर्ण,
	.num_resources	= ARRAY_SIZE(innovator1510_smc91x_resources),
	.resource	= innovator1510_smc91x_resources,
पूर्ण;

अटल काष्ठा platक्रमm_device innovator1510_lcd_device = अणु
	.name		= "lcd_inn1510",
	.id		= -1,
पूर्ण;

अटल काष्ठा platक्रमm_device innovator1510_spi_device = अणु
	.name		= "spi_inn1510",
	.id		= -1,
पूर्ण;

अटल काष्ठा platक्रमm_device *innovator1510_devices[] __initdata = अणु
	&innovator_flash_device,
	&innovator1510_smc91x_device,
	&innovator_kp_device,
	&innovator1510_lcd_device,
	&innovator1510_spi_device,
पूर्ण;

अटल पूर्णांक innovator_get_penकरोwn_state(व्योम)
अणु
	वापस !(__raw_पढ़ोb(OMAP1510_FPGA_TOUCHSCREEN) & (1 << 5));
पूर्ण

अटल स्थिर काष्ठा ads7846_platक्रमm_data innovator1510_ts_info = अणु
	.model			= 7846,
	.vref_delay_usecs	= 100,	/* पूर्णांकernal, no capacitor */
	.x_plate_ohms		= 419,
	.y_plate_ohms		= 486,
	.get_penकरोwn_state	= innovator_get_penकरोwn_state,
पूर्ण;

अटल काष्ठा spi_board_info __initdata innovator1510_boardinfo[] = अणु अणु
	/* FPGA (bus "10") CS0 has an ads7846e */
	.modalias		= "ads7846",
	.platक्रमm_data		= &innovator1510_ts_info,
	.irq			= OMAP1510_INT_FPGA_TS,
	.max_speed_hz		= 120000 /* max sample rate at 3V */
					* 26 /* command + data + overhead */,
	.bus_num		= 10,
	.chip_select		= 0,
पूर्ण पूर्ण;

#पूर्ण_अगर /* CONFIG_ARCH_OMAP15XX */

#अगर_घोषित CONFIG_ARCH_OMAP16XX

अटल काष्ठा resource innovator1610_smc91x_resources[] = अणु
	[0] = अणु
		.start	= INNOVATOR1610_ETHR_START,		/* Physical */
		.end	= INNOVATOR1610_ETHR_START + 0xf,
		.flags	= IORESOURCE_MEM,
	पूर्ण,
	[1] = अणु
		.flags	= IORESOURCE_IRQ | IORESOURCE_IRQ_LOWEDGE,
	पूर्ण,
पूर्ण;

अटल काष्ठा platक्रमm_device innovator1610_smc91x_device = अणु
	.name		= "smc91x",
	.id		= 0,
	.dev	= अणु
		.platक्रमm_data	= &innovator_smc91x_info,
	पूर्ण,
	.num_resources	= ARRAY_SIZE(innovator1610_smc91x_resources),
	.resource	= innovator1610_smc91x_resources,
पूर्ण;

अटल काष्ठा platक्रमm_device innovator1610_lcd_device = अणु
	.name		= "inn1610_lcd",
	.id		= -1,
पूर्ण;

अटल काष्ठा platक्रमm_device *innovator1610_devices[] __initdata = अणु
	&innovator_flash_device,
	&innovator1610_smc91x_device,
	&innovator_kp_device,
	&innovator1610_lcd_device,
पूर्ण;

#पूर्ण_अगर /* CONFIG_ARCH_OMAP16XX */

अटल व्योम __init innovator_init_smc91x(व्योम)
अणु
	अगर (cpu_is_omap1510()) अणु
		__raw_ग_लिखोb(__raw_पढ़ोb(OMAP1510_FPGA_RST) & ~1,
			   OMAP1510_FPGA_RST);
		udelay(750);
	पूर्ण अन्यथा अणु
		अगर (gpio_request(0, "SMC91x irq") < 0) अणु
			prपूर्णांकk("Error requesting gpio 0 for smc91x irq\n");
			वापस;
		पूर्ण
	पूर्ण
पूर्ण

#अगर_घोषित CONFIG_ARCH_OMAP15XX
अटल काष्ठा omap_usb_config innovator1510_usb_config __initdata = अणु
	/* क्रम bundled non-standard host and peripheral cables */
	.hmc_mode	= 4,

	.रेजिस्टर_host	= 1,
	.pins[1]	= 6,
	.pins[2]	= 6,		/* Conflicts with UART2 */

	.रेजिस्टर_dev	= 1,
	.pins[0]	= 2,
पूर्ण;

अटल स्थिर काष्ठा omap_lcd_config innovator1510_lcd_config __initस्थिर = अणु
	.ctrl_name	= "internal",
पूर्ण;
#पूर्ण_अगर

#अगर_घोषित CONFIG_ARCH_OMAP16XX
अटल काष्ठा omap_usb_config h2_usb_config __initdata = अणु
	/* usb1 has a Mini-AB port and बाह्यal isp1301 transceiver */
	.otg		= 2,

#अगर IS_ENABLED(CONFIG_USB_OMAP)
	.hmc_mode	= 19,	/* 0:host(off) 1:dev|otg 2:disabled */
	/* .hmc_mode	= 21,*/	/* 0:host(off) 1:dev(loopback) 2:host(loopback) */
#या_अगर	IS_ENABLED(CONFIG_USB_OHCI_HCD)
	/* NONSTANDARD CABLE NEEDED (B-to-Mini-B) */
	.hmc_mode	= 20,	/* 1:dev|otg(off) 1:host 2:disabled */
#पूर्ण_अगर

	.pins[1]	= 3,
पूर्ण;

अटल स्थिर काष्ठा omap_lcd_config innovator1610_lcd_config __initस्थिर = अणु
	.ctrl_name	= "internal",
पूर्ण;
#पूर्ण_अगर

#अगर IS_ENABLED(CONFIG_MMC_OMAP)

अटल पूर्णांक mmc_set_घातer(काष्ठा device *dev, पूर्णांक slot, पूर्णांक घातer_on,
				पूर्णांक vdd)
अणु
	अगर (घातer_on)
		__raw_ग_लिखोb(__raw_पढ़ोb(OMAP1510_FPGA_POWER) | (1 << 3),
				OMAP1510_FPGA_POWER);
	अन्यथा
		__raw_ग_लिखोb(__raw_पढ़ोb(OMAP1510_FPGA_POWER) & ~(1 << 3),
				OMAP1510_FPGA_POWER);

	वापस 0;
पूर्ण

/*
 * Innovator could use the following functions tested:
 * - mmc_get_wp that uses OMAP_MPUIO(3)
 * - mmc_get_cover_state that uses FPGA F4 UIO43
 */
अटल काष्ठा omap_mmc_platक्रमm_data mmc1_data = अणु
	.nr_slots                       = 1,
	.slots[0]       = अणु
		.set_घातer		= mmc_set_घातer,
		.wires			= 4,
		.name                   = "mmcblk",
	पूर्ण,
पूर्ण;

अटल काष्ठा omap_mmc_platक्रमm_data *mmc_data[OMAP16XX_NR_MMC];

अटल व्योम __init innovator_mmc_init(व्योम)
अणु
	mmc_data[0] = &mmc1_data;
	omap1_init_mmc(mmc_data, OMAP15XX_NR_MMC);
पूर्ण

#अन्यथा
अटल अंतरभूत व्योम innovator_mmc_init(व्योम)
अणु
पूर्ण
#पूर्ण_अगर

अटल व्योम __init innovator_init(व्योम)
अणु
	अगर (cpu_is_omap1510())
		omap1510_fpga_init_irq();
	innovator_init_smc91x();

#अगर_घोषित CONFIG_ARCH_OMAP15XX
	अगर (cpu_is_omap1510()) अणु
		अचिन्हित अक्षर reg;

		/* mux pins क्रम uarts */
		omap_cfg_reg(UART1_TX);
		omap_cfg_reg(UART1_RTS);
		omap_cfg_reg(UART2_TX);
		omap_cfg_reg(UART2_RTS);
		omap_cfg_reg(UART3_TX);
		omap_cfg_reg(UART3_RX);

		reg = __raw_पढ़ोb(OMAP1510_FPGA_POWER);
		reg |= OMAP1510_FPGA_PCR_COM1_EN;
		__raw_ग_लिखोb(reg, OMAP1510_FPGA_POWER);
		udelay(10);

		reg = __raw_पढ़ोb(OMAP1510_FPGA_POWER);
		reg |= OMAP1510_FPGA_PCR_COM2_EN;
		__raw_ग_लिखोb(reg, OMAP1510_FPGA_POWER);
		udelay(10);

		platक्रमm_add_devices(innovator1510_devices, ARRAY_SIZE(innovator1510_devices));
		spi_रेजिस्टर_board_info(innovator1510_boardinfo,
				ARRAY_SIZE(innovator1510_boardinfo));
	पूर्ण
#पूर्ण_अगर
#अगर_घोषित CONFIG_ARCH_OMAP16XX
	अगर (!cpu_is_omap1510()) अणु
		innovator1610_smc91x_resources[1].start = gpio_to_irq(0);
		innovator1610_smc91x_resources[1].end = gpio_to_irq(0);
		platक्रमm_add_devices(innovator1610_devices, ARRAY_SIZE(innovator1610_devices));
	पूर्ण
#पूर्ण_अगर

#अगर_घोषित CONFIG_ARCH_OMAP15XX
	अगर (cpu_is_omap1510()) अणु
		omap1_usb_init(&innovator1510_usb_config);
		omapfb_set_lcd_config(&innovator1510_lcd_config);
	पूर्ण
#पूर्ण_अगर
#अगर_घोषित CONFIG_ARCH_OMAP16XX
	अगर (cpu_is_omap1610()) अणु
		omap1_usb_init(&h2_usb_config);
		omapfb_set_lcd_config(&innovator1610_lcd_config);
	पूर्ण
#पूर्ण_अगर
	omap_serial_init();
	omap_रेजिस्टर_i2c_bus(1, 100, शून्य, 0);
	innovator_mmc_init();
पूर्ण

/*
 * REVISIT: Assume 15xx क्रम now, we करोn't want to करो revision check
 * until later on. The right way to fix this is to set up a dअगरferent
 * machine_id क्रम 16xx Innovator, or use device tree.
 */
अटल व्योम __init innovator_map_io(व्योम)
अणु
#अगर_घोषित CONFIG_ARCH_OMAP15XX
	omap15xx_map_io();

	iotable_init(innovator1510_io_desc, ARRAY_SIZE(innovator1510_io_desc));
	udelay(10);	/* Delay needed क्रम FPGA */

	/* Dump the Innovator FPGA rev early - useful info क्रम support. */
	pr_debug("Innovator FPGA Rev %d.%d Board Rev %d\n",
			__raw_पढ़ोb(OMAP1510_FPGA_REV_HIGH),
			__raw_पढ़ोb(OMAP1510_FPGA_REV_LOW),
			__raw_पढ़ोb(OMAP1510_FPGA_BOARD_REV));
#पूर्ण_अगर
पूर्ण

MACHINE_START(OMAP_INNOVATOR, "TI-Innovator")
	/* Maपूर्णांकainer: MontaVista Software, Inc. */
	.atag_offset	= 0x100,
	.map_io		= innovator_map_io,
	.init_early     = omap1_init_early,
	.init_irq	= omap1_init_irq,
	.handle_irq	= omap1_handle_irq,
	.init_machine	= innovator_init,
	.init_late	= omap1_init_late,
	.init_समय	= omap1_समयr_init,
	.restart	= omap1_restart,
MACHINE_END
