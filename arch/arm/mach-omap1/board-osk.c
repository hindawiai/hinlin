<शैली गुरु>
/*
 * linux/arch/arm/mach-omap1/board-osk.c
 *
 * Board specअगरic init क्रम OMAP5912 OSK
 *
 * Written by Dirk Behme <dirk.behme@de.bosch.com>
 *
 * This program is मुक्त software; you can redistribute it and/or modअगरy it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation; either version 2 of the License, or (at your
 * option) any later version.
 *
 * THIS SOFTWARE IS PROVIDED ``AS IS'' AND ANY EXPRESS OR IMPLIED
 * WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN
 * NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY सूचीECT, INसूचीECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT
 * NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF
 * USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
 * ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF
 * THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 * You should have received a copy of the  GNU General Public License aदीर्घ
 * with this program; अगर not, ग_लिखो  to the Free Software Foundation, Inc.,
 * 675 Mass Ave, Cambridge, MA 02139, USA.
 */
#समावेश <linux/gpपन.स>
#समावेश <linux/gpio/machine.h>
#समावेश <linux/kernel.h>
#समावेश <linux/init.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/irq.h>
#समावेश <linux/i2c.h>
#समावेश <linux/leds.h>
#समावेश <linux/smc91x.h>
#समावेश <linux/omapfb.h>
#समावेश <linux/mtd/mtd.h>
#समावेश <linux/mtd/partitions.h>
#समावेश <linux/mtd/physmap.h>
#समावेश <linux/mfd/tps65010.h>
#समावेश <linux/platक्रमm_data/gpio-omap.h>
#समावेश <linux/platक्रमm_data/omap1_bl.h>

#समावेश <यंत्र/mach-types.h>
#समावेश <यंत्र/mach/arch.h>
#समावेश <यंत्र/mach/map.h>

#समावेश "flash.h"
#समावेश <mach/mux.h>
#समावेश <mach/tc.h>

#समावेश <mach/hardware.h>
#समावेश <mach/usb.h>

#समावेश "common.h"

/* Name of the GPIO chip used by the OMAP क्रम GPIOs 0..15 */
#घोषणा OMAP_GPIO_LABEL		"gpio-0-15"

/* At OMAP5912 OSK the Ethernet is directly connected to CS1 */
#घोषणा OMAP_OSK_ETHR_START		0x04800300

/* TPS65010 has four GPIOs.  nPG and LED2 can be treated like GPIOs with
 * alternate pin configurations क्रम hardware-controlled blinking.
 */
#घोषणा OSK_TPS_GPIO_BASE		(OMAP_MAX_GPIO_LINES + 16 /* MPUIO */)
#	define OSK_TPS_GPIO_USB_PWR_EN	(OSK_TPS_GPIO_BASE + 0)
#	define OSK_TPS_GPIO_LED_D3	(OSK_TPS_GPIO_BASE + 1)
#	define OSK_TPS_GPIO_LAN_RESET	(OSK_TPS_GPIO_BASE + 2)
#	define OSK_TPS_GPIO_DSP_PWR_EN	(OSK_TPS_GPIO_BASE + 3)
#	define OSK_TPS_GPIO_LED_D9	(OSK_TPS_GPIO_BASE + 4)
#	define OSK_TPS_GPIO_LED_D2	(OSK_TPS_GPIO_BASE + 5)

अटल काष्ठा mtd_partition osk_partitions[] = अणु
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
	पूर्ण, अणु
	      .name		= "kernel",
	      .offset		= MTDPART_OFS_APPEND,
	      .size		= SZ_2M,
	      .mask_flags	= 0
	पूर्ण, अणु
	      .name		= "filesystem",
	      .offset		= MTDPART_OFS_APPEND,
	      .size		= MTDPART_SIZ_FULL,
	      .mask_flags	= 0
	पूर्ण
पूर्ण;

अटल काष्ठा physmap_flash_data osk_flash_data = अणु
	.width		= 2,
	.set_vpp	= omap1_set_vpp,
	.parts		= osk_partitions,
	.nr_parts	= ARRAY_SIZE(osk_partitions),
पूर्ण;

अटल काष्ठा resource osk_flash_resource = अणु
	/* this is on CS3, wherever it's mapped */
	.flags		= IORESOURCE_MEM,
पूर्ण;

अटल काष्ठा platक्रमm_device osk5912_flash_device = अणु
	.name		= "physmap-flash",
	.id		= 0,
	.dev		= अणु
		.platक्रमm_data	= &osk_flash_data,
	पूर्ण,
	.num_resources	= 1,
	.resource	= &osk_flash_resource,
पूर्ण;

अटल काष्ठा smc91x_platdata osk5912_smc91x_info = अणु
	.flags	= SMC91X_USE_16BIT | SMC91X_NOWAIT,
	.leda	= RPC_LED_100_10,
	.ledb	= RPC_LED_TX_RX,
पूर्ण;

अटल काष्ठा resource osk5912_smc91x_resources[] = अणु
	[0] = अणु
		.start	= OMAP_OSK_ETHR_START,		/* Physical */
		.end	= OMAP_OSK_ETHR_START + 0xf,
		.flags	= IORESOURCE_MEM,
	पूर्ण,
	[1] = अणु
		.flags	= IORESOURCE_IRQ | IORESOURCE_IRQ_HIGHEDGE,
	पूर्ण,
पूर्ण;

अटल काष्ठा platक्रमm_device osk5912_smc91x_device = अणु
	.name		= "smc91x",
	.id		= -1,
	.dev	= अणु
		.platक्रमm_data	= &osk5912_smc91x_info,
	पूर्ण,
	.num_resources	= ARRAY_SIZE(osk5912_smc91x_resources),
	.resource	= osk5912_smc91x_resources,
पूर्ण;

अटल काष्ठा resource osk5912_cf_resources[] = अणु
	[0] = अणु
		.flags	= IORESOURCE_IRQ,
	पूर्ण,
पूर्ण;

अटल काष्ठा platक्रमm_device osk5912_cf_device = अणु
	.name		= "omap_cf",
	.id		= -1,
	.dev = अणु
		.platक्रमm_data	= (व्योम *) 2 /* CS2 */,
	पूर्ण,
	.num_resources	= ARRAY_SIZE(osk5912_cf_resources),
	.resource	= osk5912_cf_resources,
पूर्ण;

अटल काष्ठा platक्रमm_device *osk5912_devices[] __initdata = अणु
	&osk5912_flash_device,
	&osk5912_smc91x_device,
	&osk5912_cf_device,
पूर्ण;

अटल स्थिर काष्ठा gpio_led tps_leds[] = अणु
	/* NOTE:  D9 and D2 have hardware blink support.
	 * Also, D9 requires non-battery घातer.
	 */
	अणु .gpio = OSK_TPS_GPIO_LED_D9, .name = "d9",
			.शेष_trigger = "disk-activity", पूर्ण,
	अणु .gpio = OSK_TPS_GPIO_LED_D2, .name = "d2", पूर्ण,
	अणु .gpio = OSK_TPS_GPIO_LED_D3, .name = "d3", .active_low = 1,
			.शेष_trigger = "heartbeat", पूर्ण,
पूर्ण;

अटल काष्ठा gpio_led_platक्रमm_data tps_leds_data = अणु
	.num_leds	= 3,
	.leds		= tps_leds,
पूर्ण;

अटल काष्ठा platक्रमm_device osk5912_tps_leds = अणु
	.name			= "leds-gpio",
	.id			= 0,
	.dev.platक्रमm_data	= &tps_leds_data,
पूर्ण;

अटल पूर्णांक osk_tps_setup(काष्ठा i2c_client *client, व्योम *context)
अणु
	अगर (!IS_BUILTIN(CONFIG_TPS65010))
		वापस -ENOSYS;

	/* Set GPIO 1 HIGH to disable VBUS घातer supply;
	 * OHCI driver घातers it up/करोwn as needed.
	 */
	gpio_request(OSK_TPS_GPIO_USB_PWR_EN, "n_vbus_en");
	gpio_direction_output(OSK_TPS_GPIO_USB_PWR_EN, 1);
	/* Free the GPIO again as the driver will request it */
	gpio_मुक्त(OSK_TPS_GPIO_USB_PWR_EN);

	/* Set GPIO 2 high so LED D3 is off by शेष */
	tps65010_set_gpio_out_value(GPIO2, HIGH);

	/* Set GPIO 3 low to take ethernet out of reset */
	gpio_request(OSK_TPS_GPIO_LAN_RESET, "smc_reset");
	gpio_direction_output(OSK_TPS_GPIO_LAN_RESET, 0);

	/* GPIO4 is VDD_DSP */
	gpio_request(OSK_TPS_GPIO_DSP_PWR_EN, "dsp_power");
	gpio_direction_output(OSK_TPS_GPIO_DSP_PWR_EN, 1);
	/* REVISIT अगर DSP support isn't configured, घातer it off ... */

	/* Let LED1 (D9) blink; leds-gpio may override it */
	tps65010_set_led(LED1, BLINK);

	/* Set LED2 off by शेष */
	tps65010_set_led(LED2, OFF);

	/* Enable LOW_PWR handshake */
	tps65010_set_low_pwr(ON);

	/* Switch VLDO2 to 3.0V क्रम AIC23 */
	tps65010_config_vregs1(TPS_LDO2_ENABLE | TPS_VLDO2_3_0V
			| TPS_LDO1_ENABLE);

	/* रेजिस्टर these three LEDs */
	osk5912_tps_leds.dev.parent = &client->dev;
	platक्रमm_device_रेजिस्टर(&osk5912_tps_leds);

	वापस 0;
पूर्ण

अटल काष्ठा tps65010_board tps_board = अणु
	.base		= OSK_TPS_GPIO_BASE,
	.ouपंचांगask	= 0x0f,
	.setup		= osk_tps_setup,
पूर्ण;

अटल काष्ठा i2c_board_info __initdata osk_i2c_board_info[] = अणु
	अणु
		/* This device will get the name "i2c-tps65010" */
		I2C_BOARD_INFO("tps65010", 0x48),
		.dev_name = "tps65010",
		.platक्रमm_data	= &tps_board,

	पूर्ण,
	अणु
		I2C_BOARD_INFO("tlv320aic23", 0x1B),
	पूर्ण,
	/* TODO when driver support is पढ़ोy:
	 *  - optionally on Mistral, ov9640 camera sensor at 0x30
	 */
पूर्ण;

अटल व्योम __init osk_init_smc91x(व्योम)
अणु
	u32 l;

	अगर ((gpio_request(0, "smc_irq")) < 0) अणु
		prपूर्णांकk("Error requesting gpio 0 for smc91x irq\n");
		वापस;
	पूर्ण

	/* Check EMIFS रुको states to fix errors with SMC_GET_PKT_HDR */
	l = omap_पढ़ोl(EMIFS_CCS(1));
	l |= 0x3;
	omap_ग_लिखोl(l, EMIFS_CCS(1));
पूर्ण

अटल व्योम __init osk_init_cf(व्योम)
अणु
	omap_cfg_reg(M7_1610_GPIO62);
	अगर ((gpio_request(62, "cf_irq")) < 0) अणु
		prपूर्णांकk("Error requesting gpio 62 for CF irq\n");
		वापस;
	पूर्ण
	/* the CF I/O IRQ is really active-low */
	irq_set_irq_type(gpio_to_irq(62), IRQ_TYPE_EDGE_FALLING);
पूर्ण

अटल काष्ठा gpiod_lookup_table osk_usb_gpio_table = अणु
	.dev_id = "ohci",
	.table = अणु
		/* Power GPIO on the I2C-attached TPS65010 */
		GPIO_LOOKUP("tps65010", 0, "power", GPIO_ACTIVE_HIGH),
		GPIO_LOOKUP(OMAP_GPIO_LABEL, 9, "overcurrent",
			    GPIO_ACTIVE_HIGH),
	पूर्ण,
पूर्ण;

अटल काष्ठा omap_usb_config osk_usb_config __initdata = अणु
	/* has usb host connector (A) ... क्रम development it can also
	 * be used, with a NONSTANDARD gender-bending cable/करोngle, as
	 * a peripheral.
	 */
#अगर IS_ENABLED(CONFIG_USB_OMAP)
	.रेजिस्टर_dev	= 1,
	.hmc_mode	= 0,
#अन्यथा
	.रेजिस्टर_host	= 1,
	.hmc_mode	= 16,
	.rwc		= 1,
#पूर्ण_अगर
	.pins[0]	= 2,
पूर्ण;

#अगर_घोषित	CONFIG_OMAP_OSK_MISTRAL
अटल स्थिर काष्ठा omap_lcd_config osk_lcd_config __initस्थिर = अणु
	.ctrl_name	= "internal",
पूर्ण;
#पूर्ण_अगर

#अगर_घोषित	CONFIG_OMAP_OSK_MISTRAL

#समावेश <linux/input.h>
#समावेश <linux/property.h>
#समावेश <linux/spi/spi.h>
#समावेश <linux/spi/ads7846.h>

#समावेश <linux/platक्रमm_data/keypad-omap.h>

अटल स्थिर काष्ठा property_entry mistral_at24_properties[] = अणु
	PROPERTY_ENTRY_U32("pagesize", 16),
	अणु पूर्ण
पूर्ण;

अटल स्थिर काष्ठा software_node mistral_at24_node = अणु
	.properties = mistral_at24_properties,
पूर्ण;

अटल काष्ठा i2c_board_info __initdata mistral_i2c_board_info[] = अणु
	अणु
		/* NOTE:  घातered from LCD supply */
		I2C_BOARD_INFO("24c04", 0x50),
		.swnode = &mistral_at24_node,
	पूर्ण,
	/* TODO when driver support is पढ़ोy:
	 *  - optionally ov9640 camera sensor at 0x30
	 */
पूर्ण;

अटल स्थिर अचिन्हित पूर्णांक osk_keymap[] = अणु
	/* KEY(col, row, code) */
	KEY(0, 0, KEY_F1),		/* SW4 */
	KEY(3, 0, KEY_UP),		/* (sw2/up) */
	KEY(1, 1, KEY_LEFTCTRL),	/* SW5 */
	KEY(2, 1, KEY_LEFT),		/* (sw2/left) */
	KEY(0, 2, KEY_SPACE),		/* SW3 */
	KEY(1, 2, KEY_ESC),		/* SW6 */
	KEY(2, 2, KEY_DOWN),		/* (sw2/करोwn) */
	KEY(2, 3, KEY_ENTER),		/* (sw2/select) */
	KEY(3, 3, KEY_RIGHT),		/* (sw2/right) */
पूर्ण;

अटल स्थिर काष्ठा matrix_keymap_data osk_keymap_data = अणु
	.keymap		= osk_keymap,
	.keymap_size	= ARRAY_SIZE(osk_keymap),
पूर्ण;

अटल काष्ठा omap_kp_platक्रमm_data osk_kp_data = अणु
	.rows		= 8,
	.cols		= 8,
	.keymap_data	= &osk_keymap_data,
	.delay		= 9,
पूर्ण;

अटल काष्ठा resource osk5912_kp_resources[] = अणु
	[0] = अणु
		.start	= INT_KEYBOARD,
		.end	= INT_KEYBOARD,
		.flags	= IORESOURCE_IRQ,
	पूर्ण,
पूर्ण;

अटल काष्ठा platक्रमm_device osk5912_kp_device = अणु
	.name		= "omap-keypad",
	.id		= -1,
	.dev		= अणु
		.platक्रमm_data = &osk_kp_data,
	पूर्ण,
	.num_resources	= ARRAY_SIZE(osk5912_kp_resources),
	.resource	= osk5912_kp_resources,
पूर्ण;

अटल काष्ठा omap_backlight_config mistral_bl_data = अणु
	.शेष_पूर्णांकensity	= 0xa0,
पूर्ण;

अटल काष्ठा platक्रमm_device mistral_bl_device = अणु
	.name		= "omap-bl",
	.id		= -1,
	.dev		= अणु
		.platक्रमm_data = &mistral_bl_data,
	पूर्ण,
पूर्ण;

अटल काष्ठा platक्रमm_device osk5912_lcd_device = अणु
	.name		= "lcd_osk",
	.id		= -1,
पूर्ण;

अटल स्थिर काष्ठा gpio_led mistral_gpio_led_pins[] = अणु
	अणु
		.name		= "mistral:red",
		.शेष_trigger = "heartbeat",
		.gpio		= 3,
	पूर्ण,
	अणु
		.name		= "mistral:green",
		.शेष_trigger = "cpu0",
		.gpio		= OMAP_MPUIO(4),
	पूर्ण,
पूर्ण;

अटल काष्ठा gpio_led_platक्रमm_data mistral_gpio_led_data = अणु
	.leds		= mistral_gpio_led_pins,
	.num_leds	= ARRAY_SIZE(mistral_gpio_led_pins),
पूर्ण;

अटल काष्ठा platक्रमm_device mistral_gpio_leds = अणु
	.name	= "leds-gpio",
	.id	= -1,
	.dev	= अणु
		.platक्रमm_data = &mistral_gpio_led_data,
	पूर्ण,
पूर्ण;

अटल काष्ठा platक्रमm_device *mistral_devices[] __initdata = अणु
	&osk5912_kp_device,
	&mistral_bl_device,
	&osk5912_lcd_device,
	&mistral_gpio_leds,
पूर्ण;

अटल पूर्णांक mistral_get_penकरोwn_state(व्योम)
अणु
	वापस !gpio_get_value(4);
पूर्ण

अटल स्थिर काष्ठा ads7846_platक्रमm_data mistral_ts_info = अणु
	.model			= 7846,
	.vref_delay_usecs	= 100,	/* पूर्णांकernal, no capacitor */
	.x_plate_ohms		= 419,
	.y_plate_ohms		= 486,
	.get_penकरोwn_state	= mistral_get_penकरोwn_state,
पूर्ण;

अटल काष्ठा spi_board_info __initdata mistral_boardinfo[] = अणु अणु
	/* MicroWire (bus 2) CS0 has an ads7846e */
	.modalias		= "ads7846",
	.platक्रमm_data		= &mistral_ts_info,
	.max_speed_hz		= 120000 /* max sample rate at 3V */
					* 26 /* command + data + overhead */,
	.bus_num		= 2,
	.chip_select		= 0,
पूर्ण पूर्ण;

अटल irqवापस_t
osk_mistral_wake_पूर्णांकerrupt(पूर्णांक irq, व्योम *ignored)
अणु
	वापस IRQ_HANDLED;
पूर्ण

अटल व्योम __init osk_mistral_init(व्योम)
अणु
	/* NOTE:  we could actually tell अगर there's a Mistral board
	 * attached, e.g. by trying to पढ़ो something from the ads7846.
	 * But this arch_init() code is too early क्रम that, since we
	 * can't talk to the ads or even the i2c eeprom.
	 */

	/* parallel camera पूर्णांकerface */
	omap_cfg_reg(J15_1610_CAM_LCLK);
	omap_cfg_reg(J18_1610_CAM_D7);
	omap_cfg_reg(J19_1610_CAM_D6);
	omap_cfg_reg(J14_1610_CAM_D5);
	omap_cfg_reg(K18_1610_CAM_D4);
	omap_cfg_reg(K19_1610_CAM_D3);
	omap_cfg_reg(K15_1610_CAM_D2);
	omap_cfg_reg(K14_1610_CAM_D1);
	omap_cfg_reg(L19_1610_CAM_D0);
	omap_cfg_reg(L18_1610_CAM_VS);
	omap_cfg_reg(L15_1610_CAM_HS);
	omap_cfg_reg(M19_1610_CAM_RSTZ);
	omap_cfg_reg(Y15_1610_CAM_OUTCLK);

	/* serial camera पूर्णांकerface */
	omap_cfg_reg(H19_1610_CAM_EXCLK);
	omap_cfg_reg(W13_1610_CCP_CLKM);
	omap_cfg_reg(Y12_1610_CCP_CLKP);
	/* CCP_DATAM CONFLICTS WITH UART1.TX (and serial console) */
	/* omap_cfg_reg(Y14_1610_CCP_DATAM); */
	omap_cfg_reg(W14_1610_CCP_DATAP);

	/* CAM_PWDN */
	अगर (gpio_request(11, "cam_pwdn") == 0) अणु
		omap_cfg_reg(N20_1610_GPIO11);
		gpio_direction_output(11, 0);
	पूर्ण अन्यथा
		pr_debug("OSK+Mistral: CAM_PWDN is awol\n");


	/* omap_cfg_reg(P19_1610_GPIO6); */	/* BUSY */
	gpio_request(6, "ts_busy");
	gpio_direction_input(6);

	omap_cfg_reg(P20_1610_GPIO4);	/* PENIRQ */
	gpio_request(4, "ts_int");
	gpio_direction_input(4);
	irq_set_irq_type(gpio_to_irq(4), IRQ_TYPE_EDGE_FALLING);

	mistral_boardinfo[0].irq = gpio_to_irq(4);
	spi_रेजिस्टर_board_info(mistral_boardinfo,
			ARRAY_SIZE(mistral_boardinfo));

	/* the sideways button (SW1) is क्रम use as a "wakeup" button
	 *
	 * NOTE:  The Mistral board has the wakeup button (SW1) wired
	 * to the LCD 3.3V rail, which is घातered करोwn during suspend.
	 * To allow this button to wake up the omap, work around this
	 * HW bug by rewiring SW1 to use the मुख्य 3.3V rail.
	 */
	omap_cfg_reg(N15_1610_MPUIO2);
	अगर (gpio_request(OMAP_MPUIO(2), "wakeup") == 0) अणु
		पूर्णांक ret = 0;
		पूर्णांक irq = gpio_to_irq(OMAP_MPUIO(2));

		gpio_direction_input(OMAP_MPUIO(2));
		irq_set_irq_type(irq, IRQ_TYPE_EDGE_RISING);
		/* share the IRQ in हाल someone wants to use the
		 * button क्रम more than wakeup from प्रणाली sleep.
		 */
		ret = request_irq(irq,
				&osk_mistral_wake_पूर्णांकerrupt,
				IRQF_SHARED, "mistral_wakeup",
				&osk_mistral_wake_पूर्णांकerrupt);
		अगर (ret != 0) अणु
			gpio_मुक्त(OMAP_MPUIO(2));
			prपूर्णांकk(KERN_ERR "OSK+Mistral: no wakeup irq, %d?\n",
				ret);
		पूर्ण अन्यथा
			enable_irq_wake(irq);
	पूर्ण अन्यथा
		prपूर्णांकk(KERN_ERR "OSK+Mistral: wakeup button is awol\n");

	/* LCD:  backlight, and घातer; घातer controls other devices on the
	 * board, like the touchscreen, EEPROM, and wakeup (!) चयन.
	 */
	omap_cfg_reg(PWL);
	अगर (gpio_request(2, "lcd_pwr") == 0)
		gpio_direction_output(2, 1);

	/*
	 * GPIO based LEDs
	 */
	omap_cfg_reg(P18_1610_GPIO3);
	omap_cfg_reg(MPUIO4);

	i2c_रेजिस्टर_board_info(1, mistral_i2c_board_info,
			ARRAY_SIZE(mistral_i2c_board_info));

	platक्रमm_add_devices(mistral_devices, ARRAY_SIZE(mistral_devices));
पूर्ण
#अन्यथा
अटल व्योम __init osk_mistral_init(व्योम) अणु पूर्ण
#पूर्ण_अगर

#घोषणा EMIFS_CS3_VAL	(0x88013141)

अटल व्योम __init osk_init(व्योम)
अणु
	u32 l;

	osk_init_smc91x();
	osk_init_cf();

	/* Workaround क्रम wrong CS3 (NOR flash) timing
	 * There are some U-Boot versions out there which configure
	 * wrong CS3 memory timings. This मुख्यly leads to CRC
	 * or similar errors अगर you use NOR flash (e.g. with JFFS2)
	 */
	l = omap_पढ़ोl(EMIFS_CCS(3));
	अगर (l != EMIFS_CS3_VAL)
		omap_ग_लिखोl(EMIFS_CS3_VAL, EMIFS_CCS(3));

	osk_flash_resource.end = osk_flash_resource.start = omap_cs3_phys();
	osk_flash_resource.end += SZ_32M - 1;
	osk5912_smc91x_resources[1].start = gpio_to_irq(0);
	osk5912_smc91x_resources[1].end = gpio_to_irq(0);
	osk5912_cf_resources[0].start = gpio_to_irq(62);
	osk5912_cf_resources[0].end = gpio_to_irq(62);
	platक्रमm_add_devices(osk5912_devices, ARRAY_SIZE(osk5912_devices));

	l = omap_पढ़ोl(USB_TRANSCEIVER_CTRL);
	l |= (3 << 1);
	omap_ग_लिखोl(l, USB_TRANSCEIVER_CTRL);

	gpiod_add_lookup_table(&osk_usb_gpio_table);
	omap1_usb_init(&osk_usb_config);

	/* irq क्रम tps65010 chip */
	/* bootloader effectively करोes:  omap_cfg_reg(U19_1610_MPUIO1); */
	अगर (gpio_request(OMAP_MPUIO(1), "tps65010") == 0)
		gpio_direction_input(OMAP_MPUIO(1));

	omap_serial_init();
	osk_i2c_board_info[0].irq = gpio_to_irq(OMAP_MPUIO(1));
	omap_रेजिस्टर_i2c_bus(1, 400, osk_i2c_board_info,
			      ARRAY_SIZE(osk_i2c_board_info));
	osk_mistral_init();

#अगर_घोषित	CONFIG_OMAP_OSK_MISTRAL
	omapfb_set_lcd_config(&osk_lcd_config);
#पूर्ण_अगर

पूर्ण

MACHINE_START(OMAP_OSK, "TI-OSK")
	/* Maपूर्णांकainer: Dirk Behme <dirk.behme@de.bosch.com> */
	.atag_offset	= 0x100,
	.map_io		= omap16xx_map_io,
	.init_early	= omap1_init_early,
	.init_irq	= omap1_init_irq,
	.handle_irq	= omap1_handle_irq,
	.init_machine	= osk_init,
	.init_late	= omap1_init_late,
	.init_समय	= omap1_समयr_init,
	.restart	= omap1_restart,
MACHINE_END
