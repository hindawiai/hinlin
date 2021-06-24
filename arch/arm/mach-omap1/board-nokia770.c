<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * linux/arch/arm/mach-omap1/board-nokia770.c
 *
 * Modअगरied from board-generic.c
 */
#समावेश <linux/clkdev.h>
#समावेश <linux/irq.h>
#समावेश <linux/gpपन.स>
#समावेश <linux/gpio/machine.h>
#समावेश <linux/kernel.h>
#समावेश <linux/init.h>
#समावेश <linux/mutex.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/input.h>
#समावेश <linux/omapfb.h>

#समावेश <linux/spi/spi.h>
#समावेश <linux/spi/ads7846.h>
#समावेश <linux/workqueue.h>
#समावेश <linux/delay.h>

#समावेश <linux/platक्रमm_data/keypad-omap.h>
#समावेश <linux/platक्रमm_data/lcd-mipid.h>
#समावेश <linux/platक्रमm_data/gpio-omap.h>

#समावेश <यंत्र/mach-types.h>
#समावेश <यंत्र/mach/arch.h>
#समावेश <यंत्र/mach/map.h>

#समावेश <mach/mux.h>

#समावेश <mach/hardware.h>
#समावेश <mach/usb.h>

#समावेश "common.h"
#समावेश "clock.h"
#समावेश "mmc.h"

#घोषणा ADS7846_PENDOWN_GPIO	15

अटल स्थिर अचिन्हित पूर्णांक nokia770_keymap[] = अणु
	KEY(1, 0, GROUP_0 | KEY_UP),
	KEY(2, 0, GROUP_1 | KEY_F5),
	KEY(0, 1, GROUP_0 | KEY_LEFT),
	KEY(1, 1, GROUP_0 | KEY_ENTER),
	KEY(2, 1, GROUP_0 | KEY_RIGHT),
	KEY(0, 2, GROUP_1 | KEY_ESC),
	KEY(1, 2, GROUP_0 | KEY_DOWN),
	KEY(2, 2, GROUP_1 | KEY_F4),
	KEY(0, 3, GROUP_2 | KEY_F7),
	KEY(1, 3, GROUP_2 | KEY_F8),
	KEY(2, 3, GROUP_2 | KEY_F6),
पूर्ण;

अटल काष्ठा resource nokia770_kp_resources[] = अणु
	[0] = अणु
		.start	= INT_KEYBOARD,
		.end	= INT_KEYBOARD,
		.flags	= IORESOURCE_IRQ,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा matrix_keymap_data nokia770_keymap_data = अणु
	.keymap		= nokia770_keymap,
	.keymap_size	= ARRAY_SIZE(nokia770_keymap),
पूर्ण;

अटल काष्ठा omap_kp_platक्रमm_data nokia770_kp_data = अणु
	.rows		= 8,
	.cols		= 8,
	.keymap_data	= &nokia770_keymap_data,
	.delay		= 4,
पूर्ण;

अटल काष्ठा platक्रमm_device nokia770_kp_device = अणु
	.name		= "omap-keypad",
	.id		= -1,
	.dev		= अणु
		.platक्रमm_data = &nokia770_kp_data,
	पूर्ण,
	.num_resources	= ARRAY_SIZE(nokia770_kp_resources),
	.resource	= nokia770_kp_resources,
पूर्ण;

अटल काष्ठा platक्रमm_device *nokia770_devices[] __initdata = अणु
	&nokia770_kp_device,
पूर्ण;

अटल व्योम mipid_shutकरोwn(काष्ठा mipid_platक्रमm_data *pdata)
अणु
	अगर (pdata->nreset_gpio != -1) अणु
		prपूर्णांकk(KERN_INFO "shutdown LCD\n");
		gpio_set_value(pdata->nreset_gpio, 0);
		msleep(120);
	पूर्ण
पूर्ण

अटल काष्ठा mipid_platक्रमm_data nokia770_mipid_platक्रमm_data = अणु
	.shutकरोwn = mipid_shutकरोwn,
पूर्ण;

अटल स्थिर काष्ठा omap_lcd_config nokia770_lcd_config __initस्थिर = अणु
	.ctrl_name	= "hwa742",
पूर्ण;

अटल व्योम __init mipid_dev_init(व्योम)
अणु
	nokia770_mipid_platक्रमm_data.nreset_gpio = 13;
	nokia770_mipid_platक्रमm_data.data_lines = 16;

	omapfb_set_lcd_config(&nokia770_lcd_config);
पूर्ण

अटल काष्ठा ads7846_platक्रमm_data nokia770_ads7846_platक्रमm_data __initdata = अणु
	.x_max		= 0x0fff,
	.y_max		= 0x0fff,
	.x_plate_ohms	= 180,
	.pressure_max	= 255,
	.debounce_max	= 10,
	.debounce_tol	= 3,
	.debounce_rep	= 1,
	.gpio_penकरोwn	= ADS7846_PENDOWN_GPIO,
पूर्ण;

अटल काष्ठा spi_board_info nokia770_spi_board_info[] __initdata = अणु
	[0] = अणु
		.modalias       = "lcd_mipid",
		.bus_num        = 2,
		.chip_select    = 3,
		.max_speed_hz   = 12000000,
		.platक्रमm_data	= &nokia770_mipid_platक्रमm_data,
	पूर्ण,
	[1] = अणु
		.modalias       = "ads7846",
		.bus_num        = 2,
		.chip_select    = 0,
		.max_speed_hz   = 2500000,
		.platक्रमm_data	= &nokia770_ads7846_platक्रमm_data,
	पूर्ण,
पूर्ण;

अटल व्योम __init hwa742_dev_init(व्योम)
अणु
	clk_add_alias("hwa_sys_ck", शून्य, "bclk", शून्य);
पूर्ण

/* assume no Mini-AB port */

अटल काष्ठा omap_usb_config nokia770_usb_config __initdata = अणु
	.otg		= 1,
	.रेजिस्टर_host	= 1,
	.रेजिस्टर_dev	= 1,
	.hmc_mode	= 16,
	.pins[0]	= 6,
	.extcon		= "tahvo-usb",
पूर्ण;

#अगर IS_ENABLED(CONFIG_MMC_OMAP)

#घोषणा NOKIA770_GPIO_MMC_POWER		41
#घोषणा NOKIA770_GPIO_MMC_SWITCH	23

अटल पूर्णांक nokia770_mmc_set_घातer(काष्ठा device *dev, पूर्णांक slot, पूर्णांक घातer_on,
				पूर्णांक vdd)
अणु
	gpio_set_value(NOKIA770_GPIO_MMC_POWER, घातer_on);
	वापस 0;
पूर्ण

अटल पूर्णांक nokia770_mmc_get_cover_state(काष्ठा device *dev, पूर्णांक slot)
अणु
	वापस gpio_get_value(NOKIA770_GPIO_MMC_SWITCH);
पूर्ण

अटल काष्ठा omap_mmc_platक्रमm_data nokia770_mmc2_data = अणु
	.nr_slots                       = 1,
	.max_freq                       = 12000000,
	.slots[0]       = अणु
		.set_घातer		= nokia770_mmc_set_घातer,
		.get_cover_state	= nokia770_mmc_get_cover_state,
		.ocr_mask               = MMC_VDD_32_33|MMC_VDD_33_34,
		.name                   = "mmcblk",
	पूर्ण,
पूर्ण;

अटल काष्ठा omap_mmc_platक्रमm_data *nokia770_mmc_data[OMAP16XX_NR_MMC];

अटल व्योम __init nokia770_mmc_init(व्योम)
अणु
	पूर्णांक ret;

	ret = gpio_request(NOKIA770_GPIO_MMC_POWER, "MMC power");
	अगर (ret < 0)
		वापस;
	gpio_direction_output(NOKIA770_GPIO_MMC_POWER, 0);

	ret = gpio_request(NOKIA770_GPIO_MMC_SWITCH, "MMC cover");
	अगर (ret < 0) अणु
		gpio_मुक्त(NOKIA770_GPIO_MMC_POWER);
		वापस;
	पूर्ण
	gpio_direction_input(NOKIA770_GPIO_MMC_SWITCH);

	/* Only the second MMC controller is used */
	nokia770_mmc_data[1] = &nokia770_mmc2_data;
	omap1_init_mmc(nokia770_mmc_data, OMAP16XX_NR_MMC);
पूर्ण

#अन्यथा
अटल अंतरभूत व्योम nokia770_mmc_init(व्योम)
अणु
पूर्ण
#पूर्ण_अगर

#अगर IS_ENABLED(CONFIG_I2C_CBUS_GPIO)
अटल काष्ठा gpiod_lookup_table nokia770_cbus_gpio_table = अणु
	.dev_id = "i2c-cbus-gpio.2",
	.table = अणु
		GPIO_LOOKUP_IDX("mpuio", 9, शून्य, 0, 0), /* clk */
		GPIO_LOOKUP_IDX("mpuio", 10, शून्य, 1, 0), /* dat */
		GPIO_LOOKUP_IDX("mpuio", 11, शून्य, 2, 0), /* sel */
		अणु पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा platक्रमm_device nokia770_cbus_device = अणु
	.name   = "i2c-cbus-gpio",
	.id     = 2,
पूर्ण;

अटल काष्ठा i2c_board_info nokia770_i2c_board_info_2[] __initdata = अणु
	अणु
		I2C_BOARD_INFO("retu", 0x01),
	पूर्ण,
	अणु
		I2C_BOARD_INFO("tahvo", 0x02),
	पूर्ण,
पूर्ण;

अटल व्योम __init nokia770_cbus_init(व्योम)
अणु
	स्थिर पूर्णांक retu_irq_gpio = 62;
	स्थिर पूर्णांक tahvo_irq_gpio = 40;

	अगर (gpio_request_one(retu_irq_gpio, GPIOF_IN, "Retu IRQ"))
		वापस;
	अगर (gpio_request_one(tahvo_irq_gpio, GPIOF_IN, "Tahvo IRQ")) अणु
		gpio_मुक्त(retu_irq_gpio);
		वापस;
	पूर्ण
	irq_set_irq_type(gpio_to_irq(retu_irq_gpio), IRQ_TYPE_EDGE_RISING);
	irq_set_irq_type(gpio_to_irq(tahvo_irq_gpio), IRQ_TYPE_EDGE_RISING);
	nokia770_i2c_board_info_2[0].irq = gpio_to_irq(retu_irq_gpio);
	nokia770_i2c_board_info_2[1].irq = gpio_to_irq(tahvo_irq_gpio);
	i2c_रेजिस्टर_board_info(2, nokia770_i2c_board_info_2,
				ARRAY_SIZE(nokia770_i2c_board_info_2));
	gpiod_add_lookup_table(&nokia770_cbus_gpio_table);
	platक्रमm_device_रेजिस्टर(&nokia770_cbus_device);
पूर्ण
#अन्यथा /* CONFIG_I2C_CBUS_GPIO */
अटल व्योम __init nokia770_cbus_init(व्योम)
अणु
पूर्ण
#पूर्ण_अगर /* CONFIG_I2C_CBUS_GPIO */

अटल व्योम __init omap_nokia770_init(व्योम)
अणु
	/* On Nokia 770, the SleepX संकेत is masked with an
	 * MPUIO line by शेष.  It has to be unmasked क्रम it
	 * to become functional */

	/* SleepX mask direction */
	omap_ग_लिखोw((omap_पढ़ोw(0xfffb5008) & ~2), 0xfffb5008);
	/* Unmask SleepX संकेत */
	omap_ग_लिखोw((omap_पढ़ोw(0xfffb5004) & ~2), 0xfffb5004);

	platक्रमm_add_devices(nokia770_devices, ARRAY_SIZE(nokia770_devices));
	nokia770_spi_board_info[1].irq = gpio_to_irq(15);
	spi_रेजिस्टर_board_info(nokia770_spi_board_info,
				ARRAY_SIZE(nokia770_spi_board_info));
	omap_serial_init();
	omap_रेजिस्टर_i2c_bus(1, 100, शून्य, 0);
	hwa742_dev_init();
	mipid_dev_init();
	omap1_usb_init(&nokia770_usb_config);
	nokia770_mmc_init();
	nokia770_cbus_init();
पूर्ण

MACHINE_START(NOKIA770, "Nokia 770")
	.atag_offset	= 0x100,
	.map_io		= omap16xx_map_io,
	.init_early     = omap1_init_early,
	.init_irq	= omap1_init_irq,
	.handle_irq	= omap1_handle_irq,
	.init_machine	= omap_nokia770_init,
	.init_late	= omap1_init_late,
	.init_समय	= omap1_समयr_init,
	.restart	= omap1_restart,
MACHINE_END
