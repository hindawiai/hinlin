<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * linux/arch/arm/mach-omap1/board-palmz71.c
 *
 * Modअगरied from board-generic.c
 *
 * Support क्रम the Palm Zire71 PDA.
 *
 * Original version : Laurent Gonzalez
 *
 * Modअगरied क्रम zire71 : Marek Vasut
 */

#समावेश <linux/delay.h>
#समावेश <linux/gpपन.स>
#समावेश <linux/kernel.h>
#समावेश <linux/init.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/notअगरier.h>
#समावेश <linux/clk.h>
#समावेश <linux/irq.h>
#समावेश <linux/input.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/mtd/mtd.h>
#समावेश <linux/mtd/partitions.h>
#समावेश <linux/mtd/physmap.h>
#समावेश <linux/omapfb.h>
#समावेश <linux/spi/spi.h>
#समावेश <linux/spi/ads7846.h>
#समावेश <linux/platक्रमm_data/omap1_bl.h>

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

#घोषणा PALMZ71_USBDETECT_GPIO	0
#घोषणा PALMZ71_PENIRQ_GPIO	6
#घोषणा PALMZ71_MMC_WP_GPIO	8
#घोषणा PALMZ71_HDQ_GPIO 	11

#घोषणा PALMZ71_HOTSYNC_GPIO	OMAP_MPUIO(1)
#घोषणा PALMZ71_CABLE_GPIO	OMAP_MPUIO(2)
#घोषणा PALMZ71_SLIDER_GPIO	OMAP_MPUIO(3)
#घोषणा PALMZ71_MMC_IN_GPIO	OMAP_MPUIO(4)

अटल स्थिर अचिन्हित पूर्णांक palmz71_keymap[] = अणु
	KEY(0, 0, KEY_F1),
	KEY(1, 0, KEY_F2),
	KEY(2, 0, KEY_F3),
	KEY(3, 0, KEY_F4),
	KEY(4, 0, KEY_POWER),
	KEY(0, 1, KEY_LEFT),
	KEY(1, 1, KEY_DOWN),
	KEY(2, 1, KEY_UP),
	KEY(3, 1, KEY_RIGHT),
	KEY(4, 1, KEY_ENTER),
	KEY(0, 2, KEY_CAMERA),
पूर्ण;

अटल स्थिर काष्ठा matrix_keymap_data palmz71_keymap_data = अणु
	.keymap		= palmz71_keymap,
	.keymap_size	= ARRAY_SIZE(palmz71_keymap),
पूर्ण;

अटल काष्ठा omap_kp_platक्रमm_data palmz71_kp_data = अणु
	.rows	= 8,
	.cols	= 8,
	.keymap_data	= &palmz71_keymap_data,
	.rep	= true,
	.delay	= 80,
पूर्ण;

अटल काष्ठा resource palmz71_kp_resources[] = अणु
	[0] = अणु
		.start	= INT_KEYBOARD,
		.end	= INT_KEYBOARD,
		.flags	= IORESOURCE_IRQ,
	पूर्ण,
पूर्ण;

अटल काष्ठा platक्रमm_device palmz71_kp_device = अणु
	.name	= "omap-keypad",
	.id	= -1,
	.dev	= अणु
		.platक्रमm_data = &palmz71_kp_data,
	पूर्ण,
	.num_resources	= ARRAY_SIZE(palmz71_kp_resources),
	.resource	= palmz71_kp_resources,
पूर्ण;

अटल काष्ठा mtd_partition palmz71_rom_partitions[] = अणु
	/* PalmOS "Small ROM", contains the bootloader and the debugger */
	अणु
		.name		= "smallrom",
		.offset		= 0,
		.size		= 0xa000,
		.mask_flags	= MTD_WRITEABLE,
	पूर्ण,
	/* PalmOS "Big ROM", a fileप्रणाली with all the OS code and data */
	अणु
		.name	= "bigrom",
		.offset	= SZ_128K,
		/*
		 * 0x5f0000 bytes big in the multi-language ("EFIGS") version,
		 * 0x7b0000 bytes in the English-only ("enUS") version.
		 */
		.size		= 0x7b0000,
		.mask_flags	= MTD_WRITEABLE,
	पूर्ण,
पूर्ण;

अटल काष्ठा physmap_flash_data palmz71_rom_data = अणु
	.width		= 2,
	.set_vpp	= omap1_set_vpp,
	.parts		= palmz71_rom_partitions,
	.nr_parts	= ARRAY_SIZE(palmz71_rom_partitions),
पूर्ण;

अटल काष्ठा resource palmz71_rom_resource = अणु
	.start	= OMAP_CS0_PHYS,
	.end	= OMAP_CS0_PHYS + SZ_8M - 1,
	.flags	= IORESOURCE_MEM,
पूर्ण;

अटल काष्ठा platक्रमm_device palmz71_rom_device = अणु
	.name	= "physmap-flash",
	.id	= -1,
	.dev = अणु
		.platक्रमm_data = &palmz71_rom_data,
	पूर्ण,
	.num_resources	= 1,
	.resource	= &palmz71_rom_resource,
पूर्ण;

अटल काष्ठा platक्रमm_device palmz71_lcd_device = अणु
	.name	= "lcd_palmz71",
	.id	= -1,
पूर्ण;

अटल काष्ठा platक्रमm_device palmz71_spi_device = अणु
	.name	= "spi_palmz71",
	.id	= -1,
पूर्ण;

अटल काष्ठा omap_backlight_config palmz71_backlight_config = अणु
	.शेष_पूर्णांकensity	= 0xa0,
पूर्ण;

अटल काष्ठा platक्रमm_device palmz71_backlight_device = अणु
	.name	= "omap-bl",
	.id	= -1,
	.dev	= अणु
		.platक्रमm_data = &palmz71_backlight_config,
	पूर्ण,
पूर्ण;

अटल काष्ठा platक्रमm_device *devices[] __initdata = अणु
	&palmz71_rom_device,
	&palmz71_kp_device,
	&palmz71_lcd_device,
	&palmz71_spi_device,
	&palmz71_backlight_device,
पूर्ण;

अटल पूर्णांक
palmz71_get_penकरोwn_state(व्योम)
अणु
	वापस !gpio_get_value(PALMZ71_PENIRQ_GPIO);
पूर्ण

अटल स्थिर काष्ठा ads7846_platक्रमm_data palmz71_ts_info = अणु
	.model			= 7846,
	.vref_delay_usecs	= 100,	/* पूर्णांकernal, no capacitor */
	.x_plate_ohms		= 419,
	.y_plate_ohms		= 486,
	.get_penकरोwn_state	= palmz71_get_penकरोwn_state,
पूर्ण;

अटल काष्ठा spi_board_info __initdata palmz71_boardinfo[] = अणु अणु
	/* MicroWire (bus 2) CS0 has an ads7846e */
	.modalias	= "ads7846",
	.platक्रमm_data	= &palmz71_ts_info,
	.max_speed_hz	= 120000	/* max sample rate at 3V */
				* 26	/* command + data + overhead */,
	.bus_num	= 2,
	.chip_select	= 0,
पूर्ण पूर्ण;

अटल काष्ठा omap_usb_config palmz71_usb_config __initdata = अणु
	.रेजिस्टर_dev	= 1,	/* Mini-B only receptacle */
	.hmc_mode	= 0,
	.pins[0]	= 2,
पूर्ण;

अटल स्थिर काष्ठा omap_lcd_config palmz71_lcd_config __initस्थिर = अणु
	.ctrl_name = "internal",
पूर्ण;

अटल irqवापस_t
palmz71_घातercable(पूर्णांक irq, व्योम *dev_id)
अणु
	अगर (gpio_get_value(PALMZ71_USBDETECT_GPIO)) अणु
		prपूर्णांकk(KERN_INFO "PM: Power cable connected\n");
		irq_set_irq_type(gpio_to_irq(PALMZ71_USBDETECT_GPIO),
				 IRQ_TYPE_EDGE_FALLING);
	पूर्ण अन्यथा अणु
		prपूर्णांकk(KERN_INFO "PM: Power cable disconnected\n");
		irq_set_irq_type(gpio_to_irq(PALMZ71_USBDETECT_GPIO),
				 IRQ_TYPE_EDGE_RISING);
	पूर्ण
	वापस IRQ_HANDLED;
पूर्ण

अटल व्योम __init
omap_mpu_wdt_mode(पूर्णांक mode)
अणु
	अगर (mode)
		omap_ग_लिखोw(0x8000, OMAP_WDT_TIMER_MODE);
	अन्यथा अणु
		omap_ग_लिखोw(0x00f5, OMAP_WDT_TIMER_MODE);
		omap_ग_लिखोw(0x00a0, OMAP_WDT_TIMER_MODE);
	पूर्ण
पूर्ण

अटल व्योम __init
palmz71_gpio_setup(पूर्णांक early)
अणु
	अगर (early) अणु
		/* Only set GPIO1 so we have a working serial */
		gpio_direction_output(1, 1);
	पूर्ण अन्यथा अणु
		/* Set MMC/SD host WP pin as input */
		अगर (gpio_request(PALMZ71_MMC_WP_GPIO, "MMC WP") < 0) अणु
			prपूर्णांकk(KERN_ERR "Could not reserve WP GPIO!\n");
			वापस;
		पूर्ण
		gpio_direction_input(PALMZ71_MMC_WP_GPIO);

		/* Monitor the Power-cable-connected संकेत */
		अगर (gpio_request(PALMZ71_USBDETECT_GPIO, "USB detect") < 0) अणु
			prपूर्णांकk(KERN_ERR
				"Could not reserve cable signal GPIO!\n");
			वापस;
		पूर्ण
		gpio_direction_input(PALMZ71_USBDETECT_GPIO);
		अगर (request_irq(gpio_to_irq(PALMZ71_USBDETECT_GPIO),
				palmz71_घातercable, 0, "palmz71-cable", शून्य))
			prपूर्णांकk(KERN_ERR
					"IRQ request for power cable failed!\n");
		palmz71_घातercable(gpio_to_irq(PALMZ71_USBDETECT_GPIO), शून्य);
	पूर्ण
पूर्ण

अटल व्योम __init
omap_palmz71_init(व्योम)
अणु
	/* mux pins क्रम uarts */
	omap_cfg_reg(UART1_TX);
	omap_cfg_reg(UART1_RTS);
	omap_cfg_reg(UART2_TX);
	omap_cfg_reg(UART2_RTS);
	omap_cfg_reg(UART3_TX);
	omap_cfg_reg(UART3_RX);

	palmz71_gpio_setup(1);
	omap_mpu_wdt_mode(0);

	platक्रमm_add_devices(devices, ARRAY_SIZE(devices));

	palmz71_boardinfo[0].irq = gpio_to_irq(PALMZ71_PENIRQ_GPIO);
	spi_रेजिस्टर_board_info(palmz71_boardinfo,
				ARRAY_SIZE(palmz71_boardinfo));
	omap1_usb_init(&palmz71_usb_config);
	omap_serial_init();
	omap_रेजिस्टर_i2c_bus(1, 100, शून्य, 0);
	palmz71_gpio_setup(0);

	omapfb_set_lcd_config(&palmz71_lcd_config);
पूर्ण

MACHINE_START(OMAP_PALMZ71, "OMAP310 based Palm Zire71")
	.atag_offset	= 0x100,
	.map_io		= omap15xx_map_io,
	.init_early     = omap1_init_early,
	.init_irq	= omap1_init_irq,
	.handle_irq	= omap1_handle_irq,
	.init_machine	= omap_palmz71_init,
	.init_late	= omap1_init_late,
	.init_समय	= omap1_समयr_init,
	.restart	= omap1_restart,
MACHINE_END
