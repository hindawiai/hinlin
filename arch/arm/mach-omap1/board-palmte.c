<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * linux/arch/arm/mach-omap1/board-palmte.c
 *
 * Modअगरied from board-generic.c
 *
 * Support क्रम the Palm Tungsten E PDA.
 *
 * Original version : Laurent Gonzalez
 *
 * Maपूर्णांकainers : http://palmtelinux.sf.net
 *                palmtelinux-developpers@lists.sf.net
 *
 * Copyright (c) 2006 Andrzej Zaborowski  <balrog@zabor.org>
 */
#समावेश <linux/gpपन.स>
#समावेश <linux/kernel.h>
#समावेश <linux/init.h>
#समावेश <linux/input.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/mtd/mtd.h>
#समावेश <linux/mtd/partitions.h>
#समावेश <linux/mtd/physmap.h>
#समावेश <linux/spi/spi.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/apm-emulation.h>
#समावेश <linux/omapfb.h>
#समावेश <linux/platक्रमm_data/omap1_bl.h>

#समावेश <यंत्र/mach-types.h>
#समावेश <यंत्र/mach/arch.h>
#समावेश <यंत्र/mach/map.h>

#समावेश "flash.h"
#समावेश <mach/mux.h>
#समावेश <mach/tc.h>
#समावेश <linux/omap-dma.h>
#समावेश <linux/platक्रमm_data/keypad-omap.h>

#समावेश <mach/hardware.h>
#समावेश <mach/usb.h>

#समावेश "mmc.h"
#समावेश "common.h"

#घोषणा PALMTE_USBDETECT_GPIO	0
#घोषणा PALMTE_USB_OR_DC_GPIO	1
#घोषणा PALMTE_TSC_GPIO		4
#घोषणा PALMTE_PINTDAV_GPIO	6
#घोषणा PALMTE_MMC_WP_GPIO	8
#घोषणा PALMTE_MMC_POWER_GPIO	9
#घोषणा PALMTE_HDQ_GPIO		11
#घोषणा PALMTE_HEADPHONES_GPIO	14
#घोषणा PALMTE_SPEAKER_GPIO	15
#घोषणा PALMTE_DC_GPIO		OMAP_MPUIO(2)
#घोषणा PALMTE_MMC_SWITCH_GPIO	OMAP_MPUIO(4)
#घोषणा PALMTE_MMC1_GPIO	OMAP_MPUIO(6)
#घोषणा PALMTE_MMC2_GPIO	OMAP_MPUIO(7)
#घोषणा PALMTE_MMC3_GPIO	OMAP_MPUIO(11)

अटल स्थिर अचिन्हित पूर्णांक palmte_keymap[] = अणु
	KEY(0, 0, KEY_F1),		/* Calendar */
	KEY(1, 0, KEY_F2),		/* Contacts */
	KEY(2, 0, KEY_F3),		/* Tasks List */
	KEY(3, 0, KEY_F4),		/* Note Pad */
	KEY(4, 0, KEY_POWER),
	KEY(0, 1, KEY_LEFT),
	KEY(1, 1, KEY_DOWN),
	KEY(2, 1, KEY_UP),
	KEY(3, 1, KEY_RIGHT),
	KEY(4, 1, KEY_ENTER),
पूर्ण;

अटल स्थिर काष्ठा matrix_keymap_data palmte_keymap_data = अणु
	.keymap		= palmte_keymap,
	.keymap_size	= ARRAY_SIZE(palmte_keymap),
पूर्ण;

अटल काष्ठा omap_kp_platक्रमm_data palmte_kp_data = अणु
	.rows	= 8,
	.cols	= 8,
	.keymap_data = &palmte_keymap_data,
	.rep	= true,
	.delay	= 12,
पूर्ण;

अटल काष्ठा resource palmte_kp_resources[] = अणु
	[0]	= अणु
		.start	= INT_KEYBOARD,
		.end	= INT_KEYBOARD,
		.flags	= IORESOURCE_IRQ,
	पूर्ण,
पूर्ण;

अटल काष्ठा platक्रमm_device palmte_kp_device = अणु
	.name		= "omap-keypad",
	.id		= -1,
	.dev		= अणु
		.platक्रमm_data	= &palmte_kp_data,
	पूर्ण,
	.num_resources	= ARRAY_SIZE(palmte_kp_resources),
	.resource	= palmte_kp_resources,
पूर्ण;

अटल काष्ठा mtd_partition palmte_rom_partitions[] = अणु
	/* PalmOS "Small ROM", contains the bootloader and the debugger */
	अणु
		.name		= "smallrom",
		.offset		= 0,
		.size		= 0xa000,
		.mask_flags	= MTD_WRITEABLE,
	पूर्ण,
	/* PalmOS "Big ROM", a fileप्रणाली with all the OS code and data */
	अणु
		.name		= "bigrom",
		.offset		= SZ_128K,
		/*
		 * 0x5f0000 bytes big in the multi-language ("EFIGS") version,
		 * 0x7b0000 bytes in the English-only ("enUS") version.
		 */
		.size		= 0x7b0000,
		.mask_flags	= MTD_WRITEABLE,
	पूर्ण,
पूर्ण;

अटल काष्ठा physmap_flash_data palmte_rom_data = अणु
	.width		= 2,
	.set_vpp	= omap1_set_vpp,
	.parts		= palmte_rom_partitions,
	.nr_parts	= ARRAY_SIZE(palmte_rom_partitions),
पूर्ण;

अटल काष्ठा resource palmte_rom_resource = अणु
	.start		= OMAP_CS0_PHYS,
	.end		= OMAP_CS0_PHYS + SZ_8M - 1,
	.flags		= IORESOURCE_MEM,
पूर्ण;

अटल काष्ठा platक्रमm_device palmte_rom_device = अणु
	.name		= "physmap-flash",
	.id		= -1,
	.dev		= अणु
		.platक्रमm_data	= &palmte_rom_data,
	पूर्ण,
	.num_resources	= 1,
	.resource	= &palmte_rom_resource,
पूर्ण;

अटल काष्ठा platक्रमm_device palmte_lcd_device = अणु
	.name		= "lcd_palmte",
	.id		= -1,
पूर्ण;

अटल काष्ठा omap_backlight_config palmte_backlight_config = अणु
	.शेष_पूर्णांकensity	= 0xa0,
पूर्ण;

अटल काष्ठा platक्रमm_device palmte_backlight_device = अणु
	.name		= "omap-bl",
	.id		= -1,
	.dev		= अणु
		.platक्रमm_data	= &palmte_backlight_config,
	पूर्ण,
पूर्ण;

अटल काष्ठा platक्रमm_device *palmte_devices[] __initdata = अणु
	&palmte_rom_device,
	&palmte_kp_device,
	&palmte_lcd_device,
	&palmte_backlight_device,
पूर्ण;

अटल काष्ठा omap_usb_config palmte_usb_config __initdata = अणु
	.रेजिस्टर_dev	= 1,	/* Mini-B only receptacle */
	.hmc_mode	= 0,
	.pins[0]	= 2,
पूर्ण;

अटल स्थिर काष्ठा omap_lcd_config palmte_lcd_config __initस्थिर = अणु
	.ctrl_name	= "internal",
पूर्ण;

अटल काष्ठा spi_board_info palmte_spi_info[] __initdata = अणु
	अणु
		.modalias	= "tsc2102",
		.bus_num	= 2,	/* uWire (officially) */
		.chip_select	= 0,	/* As opposed to 3 */
		.max_speed_hz	= 8000000,
	पूर्ण,
पूर्ण;

अटल व्योम __init palmte_misc_gpio_setup(व्योम)
अणु
	/* Set TSC2102 PINTDAV pin as input (used by TSC2102 driver) */
	अगर (gpio_request(PALMTE_PINTDAV_GPIO, "TSC2102 PINTDAV") < 0) अणु
		prपूर्णांकk(KERN_ERR "Could not reserve PINTDAV GPIO!\n");
		वापस;
	पूर्ण
	gpio_direction_input(PALMTE_PINTDAV_GPIO);

	/* Set USB-or-DC-IN pin as input (unused) */
	अगर (gpio_request(PALMTE_USB_OR_DC_GPIO, "USB/DC-IN") < 0) अणु
		prपूर्णांकk(KERN_ERR "Could not reserve cable signal GPIO!\n");
		वापस;
	पूर्ण
	gpio_direction_input(PALMTE_USB_OR_DC_GPIO);
पूर्ण

#अगर IS_ENABLED(CONFIG_MMC_OMAP)

अटल काष्ठा omap_mmc_platक्रमm_data _palmte_mmc_config = अणु
	.nr_slots			= 1,
	.slots[0]			= अणु
		.ocr_mask		= MMC_VDD_32_33|MMC_VDD_33_34,
		.name			= "mmcblk",
	पूर्ण,
पूर्ण;

अटल काष्ठा omap_mmc_platक्रमm_data *palmte_mmc_config[OMAP15XX_NR_MMC] = अणु
	[0] = &_palmte_mmc_config,
पूर्ण;

अटल व्योम palmte_mmc_init(व्योम)
अणु
	omap1_init_mmc(palmte_mmc_config, OMAP15XX_NR_MMC);
पूर्ण

#अन्यथा /* CONFIG_MMC_OMAP */

अटल व्योम palmte_mmc_init(व्योम)
अणु
पूर्ण

#पूर्ण_अगर /* CONFIG_MMC_OMAP */

अटल व्योम __init omap_palmte_init(व्योम)
अणु
	/* mux pins क्रम uarts */
	omap_cfg_reg(UART1_TX);
	omap_cfg_reg(UART1_RTS);
	omap_cfg_reg(UART2_TX);
	omap_cfg_reg(UART2_RTS);
	omap_cfg_reg(UART3_TX);
	omap_cfg_reg(UART3_RX);

	platक्रमm_add_devices(palmte_devices, ARRAY_SIZE(palmte_devices));

	palmte_spi_info[0].irq = gpio_to_irq(PALMTE_PINTDAV_GPIO);
	spi_रेजिस्टर_board_info(palmte_spi_info, ARRAY_SIZE(palmte_spi_info));
	palmte_misc_gpio_setup();
	omap_serial_init();
	omap1_usb_init(&palmte_usb_config);
	omap_रेजिस्टर_i2c_bus(1, 100, शून्य, 0);

	omapfb_set_lcd_config(&palmte_lcd_config);
	palmte_mmc_init();
पूर्ण

MACHINE_START(OMAP_PALMTE, "OMAP310 based Palm Tungsten E")
	.atag_offset	= 0x100,
	.map_io		= omap15xx_map_io,
	.init_early     = omap1_init_early,
	.init_irq	= omap1_init_irq,
	.handle_irq	= omap1_handle_irq,
	.init_machine	= omap_palmte_init,
	.init_late	= omap1_init_late,
	.init_समय	= omap1_समयr_init,
	.restart	= omap1_restart,
MACHINE_END
