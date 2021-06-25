<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * linux/arch/arm/mach-omap1/board-ams-delta.c
 *
 * Modअगरied from board-generic.c
 *
 * Board specअगरic inits क्रम the Amstrad E3 (codename Delta) videophone
 *
 * Copyright (C) 2006 Jonathan McDowell <noodles@earth.li>
 */
#समावेश <linux/gpio/driver.h>
#समावेश <linux/gpio/machine.h>
#समावेश <linux/gpio/consumer.h>
#समावेश <linux/gpपन.स>
#समावेश <linux/kernel.h>
#समावेश <linux/init.h>
#समावेश <linux/input.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/leds.h>
#समावेश <linux/mtd/nand-gpपन.स>
#समावेश <linux/mtd/partitions.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/regulator/consumer.h>
#समावेश <linux/regulator/fixed.h>
#समावेश <linux/regulator/machine.h>
#समावेश <linux/serial_8250.h>
#समावेश <linux/export.h>
#समावेश <linux/omapfb.h>
#समावेश <linux/पन.स>
#समावेश <linux/platक्रमm_data/gpio-omap.h>

#समावेश <यंत्र/serial.h>
#समावेश <यंत्र/mach-types.h>
#समावेश <यंत्र/mach/arch.h>
#समावेश <यंत्र/mach/map.h>

#समावेश <linux/platक्रमm_data/keypad-omap.h>
#समावेश <mach/mux.h>

#समावेश <mach/hardware.h>
#समावेश <mach/usb.h>

#समावेश "ams-delta-fiq.h"
#समावेश "board-ams-delta.h"
#समावेश "iomap.h"
#समावेश "common.h"

अटल स्थिर अचिन्हित पूर्णांक ams_delta_keymap[] = अणु
	KEY(0, 0, KEY_F1),		/* Advert    */

	KEY(0, 3, KEY_COFFEE),		/* Games     */
	KEY(0, 2, KEY_QUESTION),	/* Directory */
	KEY(2, 3, KEY_CONNECT),		/* Internet  */
	KEY(1, 2, KEY_SHOP),		/* Services  */
	KEY(1, 1, KEY_PHONE),		/* VoiceMail */

	KEY(0, 1, KEY_DELETE),		/* Delete    */
	KEY(2, 2, KEY_PLAY),		/* Play      */
	KEY(1, 0, KEY_PAGEUP),		/* Up        */
	KEY(1, 3, KEY_PAGEDOWN),	/* Down      */
	KEY(2, 0, KEY_EMAIL),		/* ReadEmail */
	KEY(2, 1, KEY_STOP),		/* Stop      */

	/* Numeric keypad portion */
	KEY(0, 7, KEY_KP1),
	KEY(0, 6, KEY_KP2),
	KEY(0, 5, KEY_KP3),
	KEY(1, 7, KEY_KP4),
	KEY(1, 6, KEY_KP5),
	KEY(1, 5, KEY_KP6),
	KEY(2, 7, KEY_KP7),
	KEY(2, 6, KEY_KP8),
	KEY(2, 5, KEY_KP9),
	KEY(3, 6, KEY_KP0),
	KEY(3, 7, KEY_KPASTERISK),
	KEY(3, 5, KEY_KPDOT),		/* # key     */
	KEY(7, 2, KEY_NUMLOCK),		/* Mute      */
	KEY(7, 1, KEY_KPMINUS),		/* Recall    */
	KEY(6, 1, KEY_KPPLUS),		/* Redial    */
	KEY(7, 6, KEY_KPSLASH),		/* Handsमुक्त */
	KEY(6, 0, KEY_ENTER),		/* Video     */

	KEY(7, 4, KEY_CAMERA),		/* Photo     */

	KEY(0, 4, KEY_F2),		/* Home      */
	KEY(1, 4, KEY_F3),		/* Office    */
	KEY(2, 4, KEY_F4),		/* Mobile    */
	KEY(7, 7, KEY_F5),		/* SMS       */
	KEY(7, 5, KEY_F6),		/* Email     */

	/* QWERTY portion of keypad */
	KEY(3, 4, KEY_Q),
	KEY(3, 3, KEY_W),
	KEY(3, 2, KEY_E),
	KEY(3, 1, KEY_R),
	KEY(3, 0, KEY_T),
	KEY(4, 7, KEY_Y),
	KEY(4, 6, KEY_U),
	KEY(4, 5, KEY_I),
	KEY(4, 4, KEY_O),
	KEY(4, 3, KEY_P),

	KEY(4, 2, KEY_A),
	KEY(4, 1, KEY_S),
	KEY(4, 0, KEY_D),
	KEY(5, 7, KEY_F),
	KEY(5, 6, KEY_G),
	KEY(5, 5, KEY_H),
	KEY(5, 4, KEY_J),
	KEY(5, 3, KEY_K),
	KEY(5, 2, KEY_L),

	KEY(5, 1, KEY_Z),
	KEY(5, 0, KEY_X),
	KEY(6, 7, KEY_C),
	KEY(6, 6, KEY_V),
	KEY(6, 5, KEY_B),
	KEY(6, 4, KEY_N),
	KEY(6, 3, KEY_M),
	KEY(6, 2, KEY_SPACE),

	KEY(7, 0, KEY_LEFTSHIFT),	/* Vol up    */
	KEY(7, 3, KEY_LEFTCTRL),	/* Vol करोwn  */
पूर्ण;

#घोषणा LATCH1_PHYS	0x01000000
#घोषणा LATCH1_VIRT	0xEA000000
#घोषणा MODEM_PHYS	0x04000000
#घोषणा MODEM_VIRT	0xEB000000
#घोषणा LATCH2_PHYS	0x08000000
#घोषणा LATCH2_VIRT	0xEC000000

अटल काष्ठा map_desc ams_delta_io_desc[] __initdata = अणु
	/* AMS_DELTA_LATCH1 */
	अणु
		.भव	= LATCH1_VIRT,
		.pfn		= __phys_to_pfn(LATCH1_PHYS),
		.length		= 0x01000000,
		.type		= MT_DEVICE
	पूर्ण,
	/* AMS_DELTA_LATCH2 */
	अणु
		.भव	= LATCH2_VIRT,
		.pfn		= __phys_to_pfn(LATCH2_PHYS),
		.length		= 0x01000000,
		.type		= MT_DEVICE
	पूर्ण,
	/* AMS_DELTA_MODEM */
	अणु
		.भव	= MODEM_VIRT,
		.pfn		= __phys_to_pfn(MODEM_PHYS),
		.length		= 0x01000000,
		.type		= MT_DEVICE
	पूर्ण
पूर्ण;

अटल स्थिर काष्ठा omap_lcd_config ams_delta_lcd_config __initस्थिर = अणु
	.ctrl_name	= "internal",
पूर्ण;

अटल काष्ठा omap_usb_config ams_delta_usb_config __initdata = अणु
	.रेजिस्टर_host	= 1,
	.hmc_mode	= 16,
	.pins[0]	= 2,
पूर्ण;

#घोषणा LATCH1_NGPIO		8

अटल काष्ठा resource latch1_resources[] = अणु
	[0] = अणु
		.name	= "dat",
		.start	= LATCH1_PHYS,
		.end	= LATCH1_PHYS + (LATCH1_NGPIO - 1) / 8,
		.flags	= IORESOURCE_MEM,
	पूर्ण,
पूर्ण;

#घोषणा LATCH1_LABEL	"latch1"

अटल काष्ठा bgpio_pdata latch1_pdata = अणु
	.label	= LATCH1_LABEL,
	.base	= -1,
	.ngpio	= LATCH1_NGPIO,
पूर्ण;

अटल काष्ठा platक्रमm_device latch1_gpio_device = अणु
	.name		= "basic-mmio-gpio",
	.id		= 0,
	.resource	= latch1_resources,
	.num_resources	= ARRAY_SIZE(latch1_resources),
	.dev		= अणु
		.platक्रमm_data	= &latch1_pdata,
	पूर्ण,
पूर्ण;

#घोषणा LATCH1_PIN_LED_CAMERA		0
#घोषणा LATCH1_PIN_LED_ADVERT		1
#घोषणा LATCH1_PIN_LED_MAIL		2
#घोषणा LATCH1_PIN_LED_HANDSFREE	3
#घोषणा LATCH1_PIN_LED_VOICEMAIL	4
#घोषणा LATCH1_PIN_LED_VOICE		5
#घोषणा LATCH1_PIN_DOCKIT1		6
#घोषणा LATCH1_PIN_DOCKIT2		7

#घोषणा LATCH2_NGPIO			16

अटल काष्ठा resource latch2_resources[] = अणु
	[0] = अणु
		.name	= "dat",
		.start	= LATCH2_PHYS,
		.end	= LATCH2_PHYS + (LATCH2_NGPIO - 1) / 8,
		.flags	= IORESOURCE_MEM,
	पूर्ण,
पूर्ण;

#घोषणा LATCH2_LABEL	"latch2"

अटल काष्ठा bgpio_pdata latch2_pdata = अणु
	.label	= LATCH2_LABEL,
	.base	= -1,
	.ngpio	= LATCH2_NGPIO,
पूर्ण;

अटल काष्ठा platक्रमm_device latch2_gpio_device = अणु
	.name		= "basic-mmio-gpio",
	.id		= 1,
	.resource	= latch2_resources,
	.num_resources	= ARRAY_SIZE(latch2_resources),
	.dev		= अणु
		.platक्रमm_data	= &latch2_pdata,
	पूर्ण,
पूर्ण;

#घोषणा LATCH2_PIN_LCD_VBLEN		0
#घोषणा LATCH2_PIN_LCD_NDISP		1
#घोषणा LATCH2_PIN_न_अंकD_NCE		2
#घोषणा LATCH2_PIN_न_अंकD_NRE		3
#घोषणा LATCH2_PIN_न_अंकD_NWP		4
#घोषणा LATCH2_PIN_न_अंकD_NWE		5
#घोषणा LATCH2_PIN_न_अंकD_ALE		6
#घोषणा LATCH2_PIN_न_अंकD_CLE		7
#घोषणा LATCH2_PIN_KEYBRD_PWR		8
#घोषणा LATCH2_PIN_KEYBRD_DATAOUT	9
#घोषणा LATCH2_PIN_SCARD_RSTIN		10
#घोषणा LATCH2_PIN_SCARD_CMDVCC		11
#घोषणा LATCH2_PIN_MODEM_NRESET		12
#घोषणा LATCH2_PIN_MODEM_CODEC		13
#घोषणा LATCH2_PIN_HANDSFREE_MUTE	14
#घोषणा LATCH2_PIN_HANDSET_MUTE		15

अटल काष्ठा regulator_consumer_supply modem_nreset_consumers[] = अणु
	REGULATOR_SUPPLY("RESET#", "serial8250.1"),
	REGULATOR_SUPPLY("POR", "cx20442-codec"),
पूर्ण;

अटल काष्ठा regulator_init_data modem_nreset_data = अणु
	.स्थिरraपूर्णांकs		= अणु
		.valid_ops_mask		= REGULATOR_CHANGE_STATUS,
		.boot_on		= 1,
	पूर्ण,
	.num_consumer_supplies	= ARRAY_SIZE(modem_nreset_consumers),
	.consumer_supplies	= modem_nreset_consumers,
पूर्ण;

अटल काष्ठा fixed_voltage_config modem_nreset_config = अणु
	.supply_name		= "modem_nreset",
	.microvolts		= 3300000,
	.startup_delay		= 25000,
	.enabled_at_boot	= 1,
	.init_data		= &modem_nreset_data,
पूर्ण;

अटल काष्ठा platक्रमm_device modem_nreset_device = अणु
	.name	= "reg-fixed-voltage",
	.id	= -1,
	.dev	= अणु
		.platक्रमm_data	= &modem_nreset_config,
	पूर्ण,
पूर्ण;

अटल काष्ठा gpiod_lookup_table ams_delta_nreset_gpiod_table = अणु
	.dev_id = "reg-fixed-voltage",
	.table = अणु
		GPIO_LOOKUP(LATCH2_LABEL, LATCH2_PIN_MODEM_NRESET,
			    शून्य, GPIO_ACTIVE_HIGH),
		अणु पूर्ण,
	पूर्ण,
पूर्ण;

काष्ठा modem_निजी_data अणु
	काष्ठा regulator *regulator;
पूर्ण;

अटल काष्ठा modem_निजी_data modem_priv;

/*
 * Define partitions क्रम flash device
 */

अटल काष्ठा mtd_partition partition_info[] = अणु
	अणु .name		= "Kernel",
	  .offset	= 0,
	  .size		= 3 * SZ_1M + SZ_512K पूर्ण,
	अणु .name		= "u-boot",
	  .offset	= 3 * SZ_1M + SZ_512K,
	  .size		= SZ_256K पूर्ण,
	अणु .name		= "u-boot params",
	  .offset	= 3 * SZ_1M + SZ_512K + SZ_256K,
	  .size		= SZ_256K पूर्ण,
	अणु .name		= "Amstrad LDR",
	  .offset	= 4 * SZ_1M,
	  .size		= SZ_256K पूर्ण,
	अणु .name		= "File system",
	  .offset	= 4 * SZ_1M + 1 * SZ_256K,
	  .size		= 27 * SZ_1M पूर्ण,
	अणु .name		= "PBL reserved",
	  .offset	= 32 * SZ_1M - 3 * SZ_256K,
	  .size		=  3 * SZ_256K पूर्ण,
पूर्ण;

अटल काष्ठा gpio_nand_platdata nand_platdata = अणु
	.parts		= partition_info,
	.num_parts	= ARRAY_SIZE(partition_info),
पूर्ण;

अटल काष्ठा platक्रमm_device ams_delta_nand_device = अणु
	.name	= "ams-delta-nand",
	.id	= -1,
	.dev	= अणु
		.platक्रमm_data = &nand_platdata,
	पूर्ण,
पूर्ण;

#घोषणा OMAP_GPIO_LABEL		"gpio-0-15"
#घोषणा OMAP_MPUIO_LABEL	"mpuio"

अटल काष्ठा gpiod_lookup_table ams_delta_nand_gpio_table = अणु
	.table = अणु
		GPIO_LOOKUP(OMAP_GPIO_LABEL, AMS_DELTA_GPIO_PIN_न_अंकD_RB, "rdy",
			    0),
		GPIO_LOOKUP(LATCH2_LABEL, LATCH2_PIN_न_अंकD_NCE, "nce",
			    GPIO_ACTIVE_LOW),
		GPIO_LOOKUP(LATCH2_LABEL, LATCH2_PIN_न_अंकD_NRE, "nre",
			    GPIO_ACTIVE_LOW),
		GPIO_LOOKUP(LATCH2_LABEL, LATCH2_PIN_न_अंकD_NWP, "nwp",
			    GPIO_ACTIVE_LOW),
		GPIO_LOOKUP(LATCH2_LABEL, LATCH2_PIN_न_अंकD_NWE, "nwe",
			    GPIO_ACTIVE_LOW),
		GPIO_LOOKUP(LATCH2_LABEL, LATCH2_PIN_न_अंकD_ALE, "ale", 0),
		GPIO_LOOKUP(LATCH2_LABEL, LATCH2_PIN_न_अंकD_CLE, "cle", 0),
		GPIO_LOOKUP_IDX(OMAP_MPUIO_LABEL, 0, "data", 0, 0),
		GPIO_LOOKUP_IDX(OMAP_MPUIO_LABEL, 1, "data", 1, 0),
		GPIO_LOOKUP_IDX(OMAP_MPUIO_LABEL, 2, "data", 2, 0),
		GPIO_LOOKUP_IDX(OMAP_MPUIO_LABEL, 3, "data", 3, 0),
		GPIO_LOOKUP_IDX(OMAP_MPUIO_LABEL, 4, "data", 4, 0),
		GPIO_LOOKUP_IDX(OMAP_MPUIO_LABEL, 5, "data", 5, 0),
		GPIO_LOOKUP_IDX(OMAP_MPUIO_LABEL, 6, "data", 6, 0),
		GPIO_LOOKUP_IDX(OMAP_MPUIO_LABEL, 7, "data", 7, 0),
		अणु पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा resource ams_delta_kp_resources[] = अणु
	[0] = अणु
		.start	= INT_KEYBOARD,
		.end	= INT_KEYBOARD,
		.flags	= IORESOURCE_IRQ,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा matrix_keymap_data ams_delta_keymap_data = अणु
	.keymap		= ams_delta_keymap,
	.keymap_size	= ARRAY_SIZE(ams_delta_keymap),
पूर्ण;

अटल काष्ठा omap_kp_platक्रमm_data ams_delta_kp_data = अणु
	.rows		= 8,
	.cols		= 8,
	.keymap_data	= &ams_delta_keymap_data,
	.delay		= 9,
पूर्ण;

अटल काष्ठा platक्रमm_device ams_delta_kp_device = अणु
	.name		= "omap-keypad",
	.id		= -1,
	.dev		= अणु
		.platक्रमm_data = &ams_delta_kp_data,
	पूर्ण,
	.num_resources	= ARRAY_SIZE(ams_delta_kp_resources),
	.resource	= ams_delta_kp_resources,
पूर्ण;

अटल काष्ठा platक्रमm_device ams_delta_lcd_device = अणु
	.name	= "lcd_ams_delta",
	.id	= -1,
पूर्ण;

अटल काष्ठा gpiod_lookup_table ams_delta_lcd_gpio_table = अणु
	.table = अणु
		GPIO_LOOKUP(LATCH2_LABEL, LATCH2_PIN_LCD_VBLEN, "vblen", 0),
		GPIO_LOOKUP(LATCH2_LABEL, LATCH2_PIN_LCD_NDISP, "ndisp", 0),
		अणु पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा gpio_led gpio_leds[] __initdata = अणु
	[LATCH1_PIN_LED_CAMERA] = अणु
		.name		 = "camera",
		.शेष_state	 = LEDS_GPIO_DEFSTATE_OFF,
#अगर_घोषित CONFIG_LEDS_TRIGGERS
		.शेष_trigger = "ams_delta_camera",
#पूर्ण_अगर
	पूर्ण,
	[LATCH1_PIN_LED_ADVERT] = अणु
		.name		 = "advert",
		.शेष_state	 = LEDS_GPIO_DEFSTATE_OFF,
	पूर्ण,
	[LATCH1_PIN_LED_MAIL] = अणु
		.name		 = "email",
		.शेष_state	 = LEDS_GPIO_DEFSTATE_OFF,
	पूर्ण,
	[LATCH1_PIN_LED_HANDSFREE] = अणु
		.name		 = "handsfree",
		.शेष_state	 = LEDS_GPIO_DEFSTATE_OFF,
	पूर्ण,
	[LATCH1_PIN_LED_VOICEMAIL] = अणु
		.name		 = "voicemail",
		.शेष_state	 = LEDS_GPIO_DEFSTATE_OFF,
	पूर्ण,
	[LATCH1_PIN_LED_VOICE] = अणु
		.name		 = "voice",
		.शेष_state	 = LEDS_GPIO_DEFSTATE_OFF,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा gpio_led_platक्रमm_data leds_pdata __initस्थिर = अणु
	.leds		= gpio_leds,
	.num_leds	= ARRAY_SIZE(gpio_leds),
पूर्ण;

अटल काष्ठा gpiod_lookup_table leds_gpio_table = अणु
	.table = अणु
		GPIO_LOOKUP_IDX(LATCH1_LABEL, LATCH1_PIN_LED_CAMERA, शून्य,
				LATCH1_PIN_LED_CAMERA, 0),
		GPIO_LOOKUP_IDX(LATCH1_LABEL, LATCH1_PIN_LED_ADVERT, शून्य,
				LATCH1_PIN_LED_ADVERT, 0),
		GPIO_LOOKUP_IDX(LATCH1_LABEL, LATCH1_PIN_LED_MAIL, शून्य,
				LATCH1_PIN_LED_MAIL, 0),
		GPIO_LOOKUP_IDX(LATCH1_LABEL, LATCH1_PIN_LED_HANDSFREE, शून्य,
				LATCH1_PIN_LED_HANDSFREE, 0),
		GPIO_LOOKUP_IDX(LATCH1_LABEL, LATCH1_PIN_LED_VOICEMAIL, शून्य,
				LATCH1_PIN_LED_VOICEMAIL, 0),
		GPIO_LOOKUP_IDX(LATCH1_LABEL, LATCH1_PIN_LED_VOICE, शून्य,
				LATCH1_PIN_LED_VOICE, 0),
		अणु पूर्ण,
	पूर्ण,
पूर्ण;

#अगर_घोषित CONFIG_LEDS_TRIGGERS
DEFINE_LED_TRIGGER(ams_delta_camera_led_trigger);
#पूर्ण_अगर

अटल काष्ठा platक्रमm_device ams_delta_audio_device = अणु
	.name   = "ams-delta-audio",
	.id     = -1,
पूर्ण;

अटल काष्ठा gpiod_lookup_table ams_delta_audio_gpio_table = अणु
	.table = अणु
		GPIO_LOOKUP(OMAP_GPIO_LABEL, AMS_DELTA_GPIO_PIN_HOOK_SWITCH,
			    "hook_switch", 0),
		GPIO_LOOKUP(LATCH2_LABEL, LATCH2_PIN_MODEM_CODEC,
			    "modem_codec", 0),
		GPIO_LOOKUP(LATCH2_LABEL, LATCH2_PIN_HANDSFREE_MUTE,
			    "handsfree_mute", 0),
		GPIO_LOOKUP(LATCH2_LABEL, LATCH2_PIN_HANDSET_MUTE,
			    "handset_mute", 0),
		अणु पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा platक्रमm_device cx20442_codec_device = अणु
	.name   = "cx20442-codec",
	.id     = -1,
पूर्ण;

अटल काष्ठा resource ams_delta_serio_resources[] = अणु
	अणु
		.flags	= IORESOURCE_IRQ,
		/*
		 * Initialize IRQ resource with invalid IRQ number.
		 * It will be replaced with dynamically allocated GPIO IRQ
		 * obtained from GPIO chip as soon as the chip is available.
		 */
		.start	= -EINVAL,
		.end	= -EINVAL,
	पूर्ण,
पूर्ण;

अटल काष्ठा platक्रमm_device ams_delta_serio_device = अणु
	.name		= "ams-delta-serio",
	.id		= PLATFORM_DEVID_NONE,
	.dev		= अणु
		/*
		 * Initialize .platक्रमm_data explicitly with शून्य to
		 * indicate it is going to be used.  It will be replaced
		 * with FIQ buffer address as soon as FIQ is initialized.
		 */
		.platक्रमm_data = शून्य,
	पूर्ण,
	.num_resources	= ARRAY_SIZE(ams_delta_serio_resources),
	.resource	= ams_delta_serio_resources,
पूर्ण;

अटल काष्ठा regulator_consumer_supply keybrd_pwr_consumers[] = अणु
	/*
	 * Initialize supply .dev_name with शून्य.  It will be replaced
	 * with serio dev_name() as soon as the serio device is रेजिस्टरed.
	 */
	REGULATOR_SUPPLY("vcc", शून्य),
पूर्ण;

अटल काष्ठा regulator_init_data keybrd_pwr_initdata = अणु
	.स्थिरraपूर्णांकs		= अणु
		.valid_ops_mask		= REGULATOR_CHANGE_STATUS,
	पूर्ण,
	.num_consumer_supplies	= ARRAY_SIZE(keybrd_pwr_consumers),
	.consumer_supplies	= keybrd_pwr_consumers,
पूर्ण;

अटल काष्ठा fixed_voltage_config keybrd_pwr_config = अणु
	.supply_name		= "keybrd_pwr",
	.microvolts		= 5000000,
	.init_data		= &keybrd_pwr_initdata,
पूर्ण;

अटल काष्ठा platक्रमm_device keybrd_pwr_device = अणु
	.name	= "reg-fixed-voltage",
	.id	= PLATFORM_DEVID_AUTO,
	.dev	= अणु
		.platक्रमm_data	= &keybrd_pwr_config,
	पूर्ण,
पूर्ण;

अटल काष्ठा gpiod_lookup_table keybrd_pwr_gpio_table = अणु
	.table = अणु
		GPIO_LOOKUP(LATCH2_LABEL, LATCH2_PIN_KEYBRD_PWR, शून्य,
			    GPIO_ACTIVE_HIGH),
		अणु पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा platक्रमm_device *ams_delta_devices[] __initdata = अणु
	&latch1_gpio_device,
	&latch2_gpio_device,
	&ams_delta_kp_device,
	&ams_delta_audio_device,
	&ams_delta_serio_device,
	&ams_delta_nand_device,
	&ams_delta_lcd_device,
	&cx20442_codec_device,
पूर्ण;

अटल काष्ठा gpiod_lookup_table *ams_delta_gpio_tables[] __initdata = अणु
	&ams_delta_nreset_gpiod_table,
	&ams_delta_audio_gpio_table,
	&keybrd_pwr_gpio_table,
	&ams_delta_lcd_gpio_table,
	&ams_delta_nand_gpio_table,
पूर्ण;

/*
 * Some drivers may not use GPIO lookup tables but need to be provided
 * with GPIO numbers.  The same applies to GPIO based IRQ lines - some
 * drivers may even not use GPIO layer but expect just IRQ numbers.
 * We could either define GPIO lookup tables then use them on behalf
 * of those devices, or we can use GPIO driver level methods क्रम
 * identअगरication of GPIO and IRQ numbers. For the purpose of the latter,
 * defina a helper function which identअगरies GPIO chips by their labels.
 */
अटल पूर्णांक gpiochip_match_by_label(काष्ठा gpio_chip *chip, व्योम *data)
अणु
	अक्षर *label = data;

	वापस !म_भेद(label, chip->label);
पूर्ण

अटल काष्ठा gpiod_hog ams_delta_gpio_hogs[] = अणु
	GPIO_HOG(LATCH2_LABEL, LATCH2_PIN_KEYBRD_DATAOUT, "keybrd_dataout",
		 GPIO_ACTIVE_HIGH, GPIOD_OUT_LOW),
	अणुपूर्ण,
पूर्ण;

अटल काष्ठा plat_serial8250_port ams_delta_modem_ports[];

/*
 * Obtain MODEM IRQ GPIO descriptor using its hardware pin
 * number and assign related IRQ number to the MODEM port.
 * Keep the GPIO descriptor खोलो so nobody steps in.
 */
अटल व्योम __init modem_assign_irq(काष्ठा gpio_chip *chip)
अणु
	काष्ठा gpio_desc *gpiod;

	gpiod = gpiochip_request_own_desc(chip, AMS_DELTA_GPIO_PIN_MODEM_IRQ,
					  "modem_irq", GPIO_ACTIVE_HIGH,
					  GPIOD_IN);
	अगर (IS_ERR(gpiod)) अणु
		pr_err("%s: modem IRQ GPIO request failed (%ld)\n", __func__,
		       PTR_ERR(gpiod));
	पूर्ण अन्यथा अणु
		ams_delta_modem_ports[0].irq = gpiod_to_irq(gpiod);
	पूर्ण
पूर्ण

/*
 * The purpose of this function is to take care of proper initialization of
 * devices and data काष्ठाures which depend on GPIO lines provided by OMAP GPIO
 * banks but their drivers करोn't use GPIO lookup tables or GPIO layer at all.
 * The function may be called as soon as OMAP GPIO devices are probed.
 * Since that happens at postcore_initcall, it can be called successfully
 * from init_machine or later.
 * Dependent devices may be रेजिस्टरed from within this function or later.
 */
अटल व्योम __init omap_gpio_deps_init(व्योम)
अणु
	काष्ठा gpio_chip *chip;

	chip = gpiochip_find(OMAP_GPIO_LABEL, gpiochip_match_by_label);
	अगर (!chip) अणु
		pr_err("%s: OMAP GPIO chip not found\n", __func__);
		वापस;
	पूर्ण

	/*
	 * Start with FIQ initialization as it may have to request
	 * and release successfully each OMAP GPIO pin in turn.
	 */
	ams_delta_init_fiq(chip, &ams_delta_serio_device);

	modem_assign_irq(chip);
पूर्ण

/*
 * Initialize latch2 pins with values which are safe क्रम dependent on-board
 * devices or useful क्रम their successull initialization even beक्रमe GPIO
 * driver takes control over the latch pins:
 * - LATCH2_PIN_LCD_VBLEN	= 0
 * - LATCH2_PIN_LCD_NDISP	= 0	Keep LCD device घातered off beक्रमe its
 *					driver takes control over it.
 * - LATCH2_PIN_न_अंकD_NCE	= 0
 * - LATCH2_PIN_न_अंकD_NWP	= 0	Keep न_अंकD device करोwn and ग_लिखो-
 *					रक्षित beक्रमe its driver takes
 *					control over it.
 * - LATCH2_PIN_KEYBRD_PWR	= 0	Keep keyboard घातered off beक्रमe serio
 *					driver takes control over it.
 * - LATCH2_PIN_KEYBRD_DATAOUT	= 0	Keep low to aव्योम corruption of first
 *					byte of data received from attached
 *					keyboard when serio device is probed;
 *					the pin is also hogged low by the latch2
 *					GPIO driver as soon as it is पढ़ोy.
 * - LATCH2_PIN_MODEM_NRESET	= 1	Enable voice MODEM device, allowing क्रम
 *					its successful probe even beक्रमe a
 *					regulator it depends on, which in turn
 *					takes control over the pin, is set up.
 * - LATCH2_PIN_MODEM_CODEC	= 1	Attach voice MODEM CODEC data port
 *					to the MODEM so the CODEC is under
 *					control even अगर audio driver करोesn't
 *					take it over.
 */
अटल व्योम __init ams_delta_latch2_init(व्योम)
अणु
	u16 latch2 = 1 << LATCH2_PIN_MODEM_NRESET | 1 << LATCH2_PIN_MODEM_CODEC;

	__raw_ग_लिखोw(latch2, LATCH2_VIRT);
पूर्ण

अटल व्योम __init ams_delta_init(व्योम)
अणु
	काष्ठा platक्रमm_device *leds_pdev;

	/* mux pins क्रम uarts */
	omap_cfg_reg(UART1_TX);
	omap_cfg_reg(UART1_RTS);

	/* parallel camera पूर्णांकerface */
	omap_cfg_reg(H19_1610_CAM_EXCLK);
	omap_cfg_reg(J15_1610_CAM_LCLK);
	omap_cfg_reg(L18_1610_CAM_VS);
	omap_cfg_reg(L15_1610_CAM_HS);
	omap_cfg_reg(L19_1610_CAM_D0);
	omap_cfg_reg(K14_1610_CAM_D1);
	omap_cfg_reg(K15_1610_CAM_D2);
	omap_cfg_reg(K19_1610_CAM_D3);
	omap_cfg_reg(K18_1610_CAM_D4);
	omap_cfg_reg(J14_1610_CAM_D5);
	omap_cfg_reg(J19_1610_CAM_D6);
	omap_cfg_reg(J18_1610_CAM_D7);

	omap_gpio_deps_init();
	ams_delta_latch2_init();
	gpiod_add_hogs(ams_delta_gpio_hogs);

	omap_serial_init();
	omap_रेजिस्टर_i2c_bus(1, 100, शून्य, 0);

	omap1_usb_init(&ams_delta_usb_config);
#अगर_घोषित CONFIG_LEDS_TRIGGERS
	led_trigger_रेजिस्टर_simple("ams_delta_camera",
			&ams_delta_camera_led_trigger);
#पूर्ण_अगर
	platक्रमm_add_devices(ams_delta_devices, ARRAY_SIZE(ams_delta_devices));

	/*
	 * As soon as regulator consumers have been रेजिस्टरed, assign their
	 * dev_names to consumer supply entries of respective regulators.
	 */
	keybrd_pwr_consumers[0].dev_name =
			dev_name(&ams_delta_serio_device.dev);

	/*
	 * Once consumer supply entries are populated with dev_names,
	 * रेजिस्टर regulator devices.  At this stage only the keyboard
	 * घातer regulator has its consumer supply table fully populated.
	 */
	platक्रमm_device_रेजिस्टर(&keybrd_pwr_device);

	/*
	 * As soon as GPIO consumers have been रेजिस्टरed, assign
	 * their dev_names to respective GPIO lookup tables.
	 */
	ams_delta_audio_gpio_table.dev_id =
			dev_name(&ams_delta_audio_device.dev);
	keybrd_pwr_gpio_table.dev_id = dev_name(&keybrd_pwr_device.dev);
	ams_delta_nand_gpio_table.dev_id = dev_name(&ams_delta_nand_device.dev);
	ams_delta_lcd_gpio_table.dev_id = dev_name(&ams_delta_lcd_device.dev);

	/*
	 * Once GPIO lookup tables are populated with dev_names, रेजिस्टर them.
	 */
	gpiod_add_lookup_tables(ams_delta_gpio_tables,
				ARRAY_SIZE(ams_delta_gpio_tables));

	leds_pdev = gpio_led_रेजिस्टर_device(PLATFORM_DEVID_NONE, &leds_pdata);
	अगर (!IS_ERR_OR_शून्य(leds_pdev)) अणु
		leds_gpio_table.dev_id = dev_name(&leds_pdev->dev);
		gpiod_add_lookup_table(&leds_gpio_table);
	पूर्ण

	omap_ग_लिखोw(omap_पढ़ोw(ARM_RSTCT1) | 0x0004, ARM_RSTCT1);

	omapfb_set_lcd_config(&ams_delta_lcd_config);
पूर्ण

अटल व्योम modem_pm(काष्ठा uart_port *port, अचिन्हित पूर्णांक state, अचिन्हित old)
अणु
	काष्ठा modem_निजी_data *priv = port->निजी_data;
	पूर्णांक ret;

	अगर (!priv)
		वापस;

	अगर (IS_ERR(priv->regulator))
		वापस;

	अगर (state == old)
		वापस;

	अगर (state == 0)
		ret = regulator_enable(priv->regulator);
	अन्यथा अगर (old == 0)
		ret = regulator_disable(priv->regulator);
	अन्यथा
		ret = 0;

	अगर (ret)
		dev_warn(port->dev,
			 "ams_delta modem_pm: failed to %sable regulator: %d\n",
			 state ? "dis" : "en", ret);
पूर्ण

अटल काष्ठा plat_serial8250_port ams_delta_modem_ports[] = अणु
	अणु
		.membase	= IOMEM(MODEM_VIRT),
		.mapbase	= MODEM_PHYS,
		.irq		= IRQ_NOTCONNECTED, /* changed later */
		.flags		= UPF_BOOT_AUTOCONF,
		.irqflags	= IRQF_TRIGGER_RISING,
		.iotype		= UPIO_MEM,
		.regshअगरt	= 1,
		.uartclk	= BASE_BAUD * 16,
		.pm		= modem_pm,
		.निजी_data	= &modem_priv,
	पूर्ण,
	अणु पूर्ण,
पूर्ण;

अटल काष्ठा platक्रमm_device ams_delta_modem_device = अणु
	.name	= "serial8250",
	.id	= PLAT8250_DEV_PLATFORM1,
	.dev		= अणु
		.platक्रमm_data = ams_delta_modem_ports,
	पूर्ण,
पूर्ण;

अटल पूर्णांक __init modem_nreset_init(व्योम)
अणु
	पूर्णांक err;

	err = platक्रमm_device_रेजिस्टर(&modem_nreset_device);
	अगर (err)
		pr_err("Couldn't register the modem regulator device\n");

	वापस err;
पूर्ण


/*
 * This function expects MODEM IRQ number alपढ़ोy asचिन्हित to the port.
 * The MODEM device requires its RESET# pin kept high during probe.
 * That requirement can be fulfilled in several ways:
 * - with a descriptor of alपढ़ोy functional modem_nreset regulator
 *   asचिन्हित to the MODEM निजी data,
 * - with the regulator not yet controlled by modem_pm function but
 *   alपढ़ोy enabled by शेष on probe,
 * - beक्रमe the modem_nreset regulator is probed, with the pin alपढ़ोy
 *   set high explicitly.
 * The last one is alपढ़ोy guaranteed by ams_delta_latch2_init() called
 * from machine_init.
 * In order to aव्योम taking over ttyS0 device slot, the MODEM device
 * should be रेजिस्टरed after OMAP serial ports.  Since those ports
 * are रेजिस्टरed at arch_initcall, this function can be called safely
 * at arch_initcall_sync earliest.
 */
अटल पूर्णांक __init ams_delta_modem_init(व्योम)
अणु
	पूर्णांक err;

	अगर (!machine_is_ams_delta())
		वापस -ENODEV;

	omap_cfg_reg(M14_1510_GPIO2);

	/* Initialize the modem_nreset regulator consumer beक्रमe use */
	modem_priv.regulator = ERR_PTR(-ENODEV);

	err = platक्रमm_device_रेजिस्टर(&ams_delta_modem_device);

	वापस err;
पूर्ण
arch_initcall_sync(ams_delta_modem_init);

अटल पूर्णांक __init late_init(व्योम)
अणु
	पूर्णांक err;

	err = modem_nreset_init();
	अगर (err)
		वापस err;

	/*
	 * Once the modem device is रेजिस्टरed, the modem_nreset
	 * regulator can be requested on behalf of that device.
	 */
	modem_priv.regulator = regulator_get(&ams_delta_modem_device.dev,
			"RESET#");
	अगर (IS_ERR(modem_priv.regulator)) अणु
		err = PTR_ERR(modem_priv.regulator);
		जाओ unरेजिस्टर;
	पूर्ण
	वापस 0;

unरेजिस्टर:
	platक्रमm_device_unरेजिस्टर(&ams_delta_modem_device);
	वापस err;
पूर्ण

अटल व्योम __init ams_delta_init_late(व्योम)
अणु
	omap1_init_late();
	late_init();
पूर्ण

अटल व्योम __init ams_delta_map_io(व्योम)
अणु
	omap15xx_map_io();
	iotable_init(ams_delta_io_desc, ARRAY_SIZE(ams_delta_io_desc));
पूर्ण

MACHINE_START(AMS_DELTA, "Amstrad E3 (Delta)")
	/* Maपूर्णांकainer: Jonathan McDowell <noodles@earth.li> */
	.atag_offset	= 0x100,
	.map_io		= ams_delta_map_io,
	.init_early	= omap1_init_early,
	.init_irq	= omap1_init_irq,
	.handle_irq	= omap1_handle_irq,
	.init_machine	= ams_delta_init,
	.init_late	= ams_delta_init_late,
	.init_समय	= omap1_समयr_init,
	.restart	= omap1_restart,
MACHINE_END
