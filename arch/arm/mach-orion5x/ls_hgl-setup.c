<शैली गुरु>
/*
 * arch/arm/mach-orion5x/ls_hgl-setup.c
 *
 * Maपूर्णांकainer: Zhu Qingsen <zhuqs@cn.fujitsu.com>
 *
 * This file is licensed under the terms of the GNU General Public
 * License version 2.  This program is licensed "as is" without any
 * warranty of any kind, whether express or implied.
 */

#समावेश <linux/kernel.h>
#समावेश <linux/init.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/mtd/physmap.h>
#समावेश <linux/mv643xx_eth.h>
#समावेश <linux/leds.h>
#समावेश <linux/gpio_keys.h>
#समावेश <linux/input.h>
#समावेश <linux/i2c.h>
#समावेश <linux/ata_platक्रमm.h>
#समावेश <linux/gpपन.स>
#समावेश <यंत्र/mach-types.h>
#समावेश <यंत्र/mach/arch.h>
#समावेश "common.h"
#समावेश "mpp.h"
#समावेश "orion5x.h"

/*****************************************************************************
 * Linkstation LS-HGL Info
 ****************************************************************************/

/*
 * 256K NOR flash Device bus boot chip select
 */

#घोषणा LS_HGL_NOR_BOOT_BASE	0xf4000000
#घोषणा LS_HGL_NOR_BOOT_SIZE	SZ_256K

/*****************************************************************************
 * 256KB NOR Flash on BOOT Device
 ****************************************************************************/

अटल काष्ठा physmap_flash_data ls_hgl_nor_flash_data = अणु
	.width		= 1,
पूर्ण;

अटल काष्ठा resource ls_hgl_nor_flash_resource = अणु
	.flags	= IORESOURCE_MEM,
	.start	= LS_HGL_NOR_BOOT_BASE,
	.end	= LS_HGL_NOR_BOOT_BASE + LS_HGL_NOR_BOOT_SIZE - 1,
पूर्ण;

अटल काष्ठा platक्रमm_device ls_hgl_nor_flash = अणु
	.name			= "physmap-flash",
	.id			= 0,
	.dev		= अणु
		.platक्रमm_data	= &ls_hgl_nor_flash_data,
	पूर्ण,
	.num_resources		= 1,
	.resource		= &ls_hgl_nor_flash_resource,
पूर्ण;

/*****************************************************************************
 * Ethernet
 ****************************************************************************/

अटल काष्ठा mv643xx_eth_platक्रमm_data ls_hgl_eth_data = अणु
	.phy_addr	= 8,
पूर्ण;

/*****************************************************************************
 * RTC 5C372a on I2C bus
 ****************************************************************************/

अटल काष्ठा i2c_board_info __initdata ls_hgl_i2c_rtc = अणु
	I2C_BOARD_INFO("rs5c372a", 0x32),
पूर्ण;

/*****************************************************************************
 * LEDs attached to GPIO
 ****************************************************************************/

#घोषणा LS_HGL_GPIO_LED_ALARM   2
#घोषणा LS_HGL_GPIO_LED_INFO    3
#घोषणा LS_HGL_GPIO_LED_FUNC    17
#घोषणा LS_HGL_GPIO_LED_PWR     0


अटल काष्ठा gpio_led ls_hgl_led_pins[] = अणु
	अणु
		.name	   = "alarm:red",
		.gpio	   = LS_HGL_GPIO_LED_ALARM,
		.active_low     = 1,
	पूर्ण, अणु
		.name	   = "info:amber",
		.gpio	   = LS_HGL_GPIO_LED_INFO,
		.active_low     = 1,
	पूर्ण, अणु
		.name	   = "func:blue:top",
		.gpio	   = LS_HGL_GPIO_LED_FUNC,
		.active_low     = 1,
	पूर्ण, अणु
		.name	   = "power:blue:bottom",
		.gpio	   = LS_HGL_GPIO_LED_PWR,
	पूर्ण,
पूर्ण;

अटल काष्ठा gpio_led_platक्रमm_data ls_hgl_led_data = अणु
	.leds	   = ls_hgl_led_pins,
	.num_leds       = ARRAY_SIZE(ls_hgl_led_pins),
पूर्ण;

अटल काष्ठा platक्रमm_device ls_hgl_leds = अणु
	.name   = "leds-gpio",
	.id     = -1,
	.dev    = अणु
		.platक्रमm_data  = &ls_hgl_led_data,
	पूर्ण,
पूर्ण;

/****************************************************************************
 * GPIO Attached Keys
 ****************************************************************************/
#घोषणा LS_HGL_GPIO_KEY_FUNC       15
#घोषणा LS_HGL_GPIO_KEY_POWER      8
#घोषणा LS_HGL_GPIO_KEY_AUTOPOWER  10

#घोषणा LS_HGL_SW_POWER     0x00
#घोषणा LS_HGL_SW_AUTOPOWER 0x01

अटल काष्ठा gpio_keys_button ls_hgl_buttons[] = अणु
	अणु
		.code	   = KEY_OPTION,
		.gpio	   = LS_HGL_GPIO_KEY_FUNC,
		.desc	   = "Function Button",
		.active_low     = 1,
	पूर्ण, अणु
		.type		= EV_SW,
		.code	   = LS_HGL_SW_POWER,
		.gpio	   = LS_HGL_GPIO_KEY_POWER,
		.desc	   = "Power-on Switch",
		.active_low     = 1,
	पूर्ण, अणु
		.type		= EV_SW,
		.code	   = LS_HGL_SW_AUTOPOWER,
		.gpio	   = LS_HGL_GPIO_KEY_AUTOPOWER,
		.desc	   = "Power-auto Switch",
		.active_low     = 1,
	पूर्ण,
पूर्ण;

अटल काष्ठा gpio_keys_platक्रमm_data ls_hgl_button_data = अणु
	.buttons	= ls_hgl_buttons,
	.nbuttons       = ARRAY_SIZE(ls_hgl_buttons),
पूर्ण;

अटल काष्ठा platक्रमm_device ls_hgl_button_device = अणु
	.name	   = "gpio-keys",
	.id	     = -1,
	.num_resources  = 0,
	.dev	    = अणु
		.platक्रमm_data  = &ls_hgl_button_data,
	पूर्ण,
पूर्ण;


/*****************************************************************************
 * SATA
 ****************************************************************************/
अटल काष्ठा mv_sata_platक्रमm_data ls_hgl_sata_data = अणु
	.n_ports	= 2,
पूर्ण;


/*****************************************************************************
 * Linkstation LS-HGL specअगरic घातer off method: reboot
 ****************************************************************************/
/*
 * On the Linkstation LS-HGL, the shutकरोwn process is following:
 * - Userland monitors key events until the घातer चयन goes to off position
 * - The board reboots
 * - U-boot starts and goes पूर्णांकo an idle mode रुकोing क्रम the user
 *   to move the चयन to ON position
 */

अटल व्योम ls_hgl_घातer_off(व्योम)
अणु
	orion5x_restart(REBOOT_HARD, शून्य);
पूर्ण


/*****************************************************************************
 * General Setup
 ****************************************************************************/

#घोषणा LS_HGL_GPIO_USB_POWER	9
#घोषणा LS_HGL_GPIO_AUTO_POWER	10
#घोषणा LS_HGL_GPIO_POWER	    8

#घोषणा LS_HGL_GPIO_HDD_POWER	1

अटल अचिन्हित पूर्णांक ls_hgl_mpp_modes[] __initdata = अणु
	MPP0_GPIO, /* LED_PWR */
	MPP1_GPIO, /* HDD_PWR */
	MPP2_GPIO, /* LED_ALARM */
	MPP3_GPIO, /* LED_INFO */
	MPP4_UNUSED,
	MPP5_UNUSED,
	MPP6_GPIO, /* FAN_LCK */
	MPP7_GPIO, /* INIT */
	MPP8_GPIO, /* POWER */
	MPP9_GPIO, /* USB_PWR */
	MPP10_GPIO, /* AUTO_POWER */
	MPP11_UNUSED, /* LED_ETH (dummy) */
	MPP12_UNUSED,
	MPP13_UNUSED,
	MPP14_UNUSED,
	MPP15_GPIO, /* FUNC */
	MPP16_UNUSED,
	MPP17_GPIO, /* LED_FUNC */
	MPP18_UNUSED,
	MPP19_UNUSED,
	0,
पूर्ण;

अटल व्योम __init ls_hgl_init(व्योम)
अणु
	/*
	 * Setup basic Orion functions. Need to be called early.
	 */
	orion5x_init();

	orion5x_mpp_conf(ls_hgl_mpp_modes);

	/*
	 * Configure peripherals.
	 */
	orion5x_ehci0_init();
	orion5x_ehci1_init();
	orion5x_eth_init(&ls_hgl_eth_data);
	orion5x_i2c_init();
	orion5x_sata_init(&ls_hgl_sata_data);
	orion5x_uart0_init();
	orion5x_xor_init();

	mvebu_mbus_add_winकरोw_by_id(ORION_MBUS_DEVBUS_BOOT_TARGET,
				    ORION_MBUS_DEVBUS_BOOT_ATTR,
				    LS_HGL_NOR_BOOT_BASE,
				    LS_HGL_NOR_BOOT_SIZE);
	platक्रमm_device_रेजिस्टर(&ls_hgl_nor_flash);

	platक्रमm_device_रेजिस्टर(&ls_hgl_button_device);

	platक्रमm_device_रेजिस्टर(&ls_hgl_leds);

	i2c_रेजिस्टर_board_info(0, &ls_hgl_i2c_rtc, 1);

	/* enable USB घातer */
	gpio_set_value(LS_HGL_GPIO_USB_POWER, 1);

	/* रेजिस्टर घातer-off method */
	pm_घातer_off = ls_hgl_घातer_off;

	pr_info("%s: finished\n", __func__);
पूर्ण

MACHINE_START(LINKSTATION_LS_HGL, "Buffalo Linkstation LS-HGL")
	/* Maपूर्णांकainer: Zhu Qingsen <zhuqs@cn.fujistu.com> */
	.atag_offset	= 0x100,
	.nr_irqs	= ORION5X_NR_IRQS,
	.init_machine	= ls_hgl_init,
	.map_io		= orion5x_map_io,
	.init_early	= orion5x_init_early,
	.init_irq	= orion5x_init_irq,
	.init_समय	= orion5x_समयr_init,
	.fixup		= tag_fixup_mem32,
	.restart	= orion5x_restart,
MACHINE_END
