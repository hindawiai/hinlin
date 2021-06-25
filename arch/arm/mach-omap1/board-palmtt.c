<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * linux/arch/arm/mach-omap1/board-palmtt.c
 *
 * Modअगरied from board-palmtt2.c
 *
 * Modअगरied and amended क्रम Palm Tungsten|T
 * by Marek Vasut <marek.vasut@gmail.com>
 */

#समावेश <linux/delay.h>
#समावेश <linux/gpपन.स>
#समावेश <linux/kernel.h>
#समावेश <linux/init.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/notअगरier.h>
#समावेश <linux/clk.h>
#समावेश <linux/input.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/mtd/mtd.h>
#समावेश <linux/mtd/partitions.h>
#समावेश <linux/mtd/physmap.h>
#समावेश <linux/leds.h>
#समावेश <linux/omapfb.h>
#समावेश <linux/spi/spi.h>
#समावेश <linux/spi/ads7846.h>
#समावेश <linux/platक्रमm_data/omap1_bl.h>
#समावेश <linux/platक्रमm_data/leds-omap.h>

#समावेश <यंत्र/mach-types.h>
#समावेश <यंत्र/mach/arch.h>
#समावेश <यंत्र/mach/map.h>

#समावेश "flash.h"
#समावेश <mach/mux.h>
#समावेश <linux/omap-dma.h>
#समावेश <mach/tc.h>
#समावेश <linux/platक्रमm_data/keypad-omap.h>

#समावेश <mach/hardware.h>
#समावेश <mach/usb.h>

#समावेश "common.h"

#घोषणा PALMTT_USBDETECT_GPIO	0
#घोषणा PALMTT_CABLE_GPIO	1
#घोषणा PALMTT_LED_GPIO		3
#घोषणा PALMTT_PENIRQ_GPIO	6
#घोषणा PALMTT_MMC_WP_GPIO	8
#घोषणा PALMTT_HDQ_GPIO		11

अटल स्थिर अचिन्हित पूर्णांक palmtt_keymap[] = अणु
	KEY(0, 0, KEY_ESC),
	KEY(1, 0, KEY_SPACE),
	KEY(2, 0, KEY_LEFTCTRL),
	KEY(3, 0, KEY_TAB),
	KEY(4, 0, KEY_ENTER),
	KEY(0, 1, KEY_LEFT),
	KEY(1, 1, KEY_DOWN),
	KEY(2, 1, KEY_UP),
	KEY(3, 1, KEY_RIGHT),
	KEY(0, 2, KEY_SLEEP),
	KEY(4, 2, KEY_Y),
पूर्ण;

अटल काष्ठा mtd_partition palmtt_partitions[] = अणु
	अणु
		.name		= "write8k",
		.offset		= 0,
		.size		= SZ_8K,
		.mask_flags	= 0,
	पूर्ण,
	अणु
		.name		= "PalmOS-BootLoader(ro)",
		.offset		= SZ_8K,
		.size		= 7 * SZ_8K,
		.mask_flags	= MTD_WRITEABLE,
	पूर्ण,
	अणु
		.name		= "u-boot",
		.offset		= MTDPART_OFS_APPEND,
		.size		= 8 * SZ_8K,
		.mask_flags	= 0,
	पूर्ण,
	अणु
		.name		= "PalmOS-FS(ro)",
		.offset		= MTDPART_OFS_APPEND,
		.size		= 7 * SZ_1M + 4 * SZ_64K - 16 * SZ_8K,
		.mask_flags	= MTD_WRITEABLE,
	पूर्ण,
	अणु
		.name		= "u-boot(rez)",
		.offset		= MTDPART_OFS_APPEND,
		.size		= SZ_128K,
		.mask_flags	= 0
	पूर्ण,
	अणु
		.name		= "empty",
		.offset		= MTDPART_OFS_APPEND,
		.size		= MTDPART_SIZ_FULL,
		.mask_flags	= 0
	पूर्ण
पूर्ण;

अटल काष्ठा physmap_flash_data palmtt_flash_data = अणु
	.width		= 2,
	.set_vpp	= omap1_set_vpp,
	.parts		= palmtt_partitions,
	.nr_parts	= ARRAY_SIZE(palmtt_partitions),
पूर्ण;

अटल काष्ठा resource palmtt_flash_resource = अणु
	.start		= OMAP_CS0_PHYS,
	.end		= OMAP_CS0_PHYS + SZ_8M - 1,
	.flags		= IORESOURCE_MEM,
पूर्ण;

अटल काष्ठा platक्रमm_device palmtt_flash_device = अणु
	.name		= "physmap-flash",
	.id		= 0,
	.dev		= अणु
		.platक्रमm_data	= &palmtt_flash_data,
	पूर्ण,
	.num_resources	= 1,
	.resource	= &palmtt_flash_resource,
पूर्ण;

अटल काष्ठा resource palmtt_kp_resources[] = अणु
	[0] = अणु
		.start	= INT_KEYBOARD,
		.end	= INT_KEYBOARD,
		.flags	= IORESOURCE_IRQ,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा matrix_keymap_data palmtt_keymap_data = अणु
	.keymap		= palmtt_keymap,
	.keymap_size	= ARRAY_SIZE(palmtt_keymap),
पूर्ण;

अटल काष्ठा omap_kp_platक्रमm_data palmtt_kp_data = अणु
	.rows	= 6,
	.cols	= 3,
	.keymap_data = &palmtt_keymap_data,
पूर्ण;

अटल काष्ठा platक्रमm_device palmtt_kp_device = अणु
	.name		= "omap-keypad",
	.id		= -1,
	.dev		= अणु
		.platक्रमm_data = &palmtt_kp_data,
	पूर्ण,
	.num_resources	= ARRAY_SIZE(palmtt_kp_resources),
	.resource	= palmtt_kp_resources,
पूर्ण;

अटल काष्ठा platक्रमm_device palmtt_lcd_device = अणु
	.name		= "lcd_palmtt",
	.id		= -1,
पूर्ण;

अटल काष्ठा platक्रमm_device palmtt_spi_device = अणु
	.name		= "spi_palmtt",
	.id		= -1,
पूर्ण;

अटल काष्ठा omap_backlight_config palmtt_backlight_config = अणु
	.शेष_पूर्णांकensity	= 0xa0,
पूर्ण;

अटल काष्ठा platक्रमm_device palmtt_backlight_device = अणु
	.name		= "omap-bl",
	.id		= -1,
	.dev		= अणु
		.platक्रमm_data= &palmtt_backlight_config,
	पूर्ण,
पूर्ण;

अटल काष्ठा omap_led_config palmtt_led_config[] = अणु
	अणु
		.cdev	= अणु
			.name	= "palmtt:led0",
		पूर्ण,
		.gpio	= PALMTT_LED_GPIO,
	पूर्ण,
पूर्ण;

अटल काष्ठा omap_led_platक्रमm_data palmtt_led_data = अणु
	.nr_leds	= ARRAY_SIZE(palmtt_led_config),
	.leds		= palmtt_led_config,
पूर्ण;

अटल काष्ठा platक्रमm_device palmtt_led_device = अणु
	.name	= "omap-led",
	.id	= -1,
	.dev	= अणु
		.platक्रमm_data	= &palmtt_led_data,
	पूर्ण,
पूर्ण;

अटल काष्ठा platक्रमm_device *palmtt_devices[] __initdata = अणु
	&palmtt_flash_device,
	&palmtt_kp_device,
	&palmtt_lcd_device,
	&palmtt_spi_device,
	&palmtt_backlight_device,
	&palmtt_led_device,
पूर्ण;

अटल पूर्णांक palmtt_get_penकरोwn_state(व्योम)
अणु
	वापस !gpio_get_value(6);
पूर्ण

अटल स्थिर काष्ठा ads7846_platक्रमm_data palmtt_ts_info = अणु
	.model			= 7846,
	.vref_delay_usecs	= 100,	/* पूर्णांकernal, no capacitor */
	.x_plate_ohms		= 419,
	.y_plate_ohms		= 486,
	.get_penकरोwn_state	= palmtt_get_penकरोwn_state,
पूर्ण;

अटल काष्ठा spi_board_info __initdata palmtt_boardinfo[] = अणु
	अणु
		/* MicroWire (bus 2) CS0 has an ads7846e */
		.modalias	= "ads7846",
		.platक्रमm_data	= &palmtt_ts_info,
		.max_speed_hz	= 120000	/* max sample rate at 3V */
					* 26	/* command + data + overhead */,
		.bus_num	= 2,
		.chip_select	= 0,
	पूर्ण
पूर्ण;

अटल काष्ठा omap_usb_config palmtt_usb_config __initdata = अणु
	.रेजिस्टर_dev	= 1,
	.hmc_mode	= 0,
	.pins[0]	= 2,
पूर्ण;

अटल स्थिर काष्ठा omap_lcd_config palmtt_lcd_config __initस्थिर = अणु
	.ctrl_name	= "internal",
पूर्ण;

अटल व्योम __init omap_mpu_wdt_mode(पूर्णांक mode) अणु
	अगर (mode)
		omap_ग_लिखोw(0x8000, OMAP_WDT_TIMER_MODE);
	अन्यथा अणु
		omap_ग_लिखोw(0x00f5, OMAP_WDT_TIMER_MODE);
		omap_ग_लिखोw(0x00a0, OMAP_WDT_TIMER_MODE);
	पूर्ण
पूर्ण

अटल व्योम __init omap_palmtt_init(व्योम)
अणु
	/* mux pins क्रम uarts */
	omap_cfg_reg(UART1_TX);
	omap_cfg_reg(UART1_RTS);
	omap_cfg_reg(UART2_TX);
	omap_cfg_reg(UART2_RTS);
	omap_cfg_reg(UART3_TX);
	omap_cfg_reg(UART3_RX);

	omap_mpu_wdt_mode(0);

	platक्रमm_add_devices(palmtt_devices, ARRAY_SIZE(palmtt_devices));

	palmtt_boardinfo[0].irq = gpio_to_irq(6);
	spi_रेजिस्टर_board_info(palmtt_boardinfo,ARRAY_SIZE(palmtt_boardinfo));
	omap_serial_init();
	omap1_usb_init(&palmtt_usb_config);
	omap_रेजिस्टर_i2c_bus(1, 100, शून्य, 0);

	omapfb_set_lcd_config(&palmtt_lcd_config);
पूर्ण

MACHINE_START(OMAP_PALMTT, "OMAP1510 based Palm Tungsten|T")
	.atag_offset	= 0x100,
	.map_io		= omap15xx_map_io,
	.init_early     = omap1_init_early,
	.init_irq	= omap1_init_irq,
	.handle_irq	= omap1_handle_irq,
	.init_machine	= omap_palmtt_init,
	.init_late	= omap1_init_late,
	.init_समय	= omap1_समयr_init,
	.restart	= omap1_restart,
MACHINE_END
