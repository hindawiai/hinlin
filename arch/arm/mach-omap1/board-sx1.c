<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
* linux/arch/arm/mach-omap1/board-sx1.c
*
* Modअगरied from board-generic.c
*
* Support क्रम the Siemens SX1 mobile phone.
*
* Original version : Vladimir Ananiev (Vovan888-at-gmail com)
*
* Maपूर्णांकaपूर्णांकers : Vladimir Ananiev (aka Vovan888), Sergge
*		oslik.ru
*/
#समावेश <linux/gpपन.स>
#समावेश <linux/kernel.h>
#समावेश <linux/init.h>
#समावेश <linux/input.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/notअगरier.h>
#समावेश <linux/mtd/mtd.h>
#समावेश <linux/mtd/partitions.h>
#समावेश <linux/mtd/physmap.h>
#समावेश <linux/types.h>
#समावेश <linux/i2c.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/export.h>
#समावेश <linux/omapfb.h>
#समावेश <linux/platक्रमm_data/keypad-omap.h>

#समावेश <यंत्र/mach-types.h>
#समावेश <यंत्र/mach/arch.h>
#समावेश <यंत्र/mach/map.h>

#समावेश "flash.h"
#समावेश <mach/mux.h>
#समावेश <linux/omap-dma.h>
#समावेश <mach/tc.h>
#समावेश "board-sx1.h"

#समावेश <mach/hardware.h>
#समावेश <mach/usb.h>

#समावेश "common.h"

/* Write to I2C device */
पूर्णांक sx1_i2c_ग_लिखो_byte(u8 devaddr, u8 regoffset, u8 value)
अणु
	काष्ठा i2c_adapter *adap;
	पूर्णांक err;
	काष्ठा i2c_msg msg[1];
	अचिन्हित अक्षर data[2];

	adap = i2c_get_adapter(0);
	अगर (!adap)
		वापस -ENODEV;
	msg->addr = devaddr;	/* I2C address of chip */
	msg->flags = 0;
	msg->len = 2;
	msg->buf = data;
	data[0] = regoffset;	/* रेजिस्टर num */
	data[1] = value;		/* रेजिस्टर data */
	err = i2c_transfer(adap, msg, 1);
	i2c_put_adapter(adap);
	अगर (err >= 0)
		वापस 0;
	वापस err;
पूर्ण

/* Read from I2C device */
पूर्णांक sx1_i2c_पढ़ो_byte(u8 devaddr, u8 regoffset, u8 *value)
अणु
	काष्ठा i2c_adapter *adap;
	पूर्णांक err;
	काष्ठा i2c_msg msg[1];
	अचिन्हित अक्षर data[2];

	adap = i2c_get_adapter(0);
	अगर (!adap)
		वापस -ENODEV;

	msg->addr = devaddr;	/* I2C address of chip */
	msg->flags = 0;
	msg->len = 1;
	msg->buf = data;
	data[0] = regoffset;	/* रेजिस्टर num */
	err = i2c_transfer(adap, msg, 1);

	msg->addr = devaddr;	/* I2C address */
	msg->flags = I2C_M_RD;
	msg->len = 1;
	msg->buf = data;
	err = i2c_transfer(adap, msg, 1);
	*value = data[0];
	i2c_put_adapter(adap);

	अगर (err >= 0)
		वापस 0;
	वापस err;
पूर्ण
/* set keyboard backlight पूर्णांकensity */
पूर्णांक sx1_setkeylight(u8 keylight)
अणु
	अगर (keylight > SOFIA_MAX_LIGHT_VAL)
		keylight = SOFIA_MAX_LIGHT_VAL;
	वापस sx1_i2c_ग_लिखो_byte(SOFIA_I2C_ADDR, SOFIA_KEYLIGHT_REG, keylight);
पूर्ण
/* get current keylight पूर्णांकensity */
पूर्णांक sx1_getkeylight(u8 * keylight)
अणु
	वापस sx1_i2c_पढ़ो_byte(SOFIA_I2C_ADDR, SOFIA_KEYLIGHT_REG, keylight);
पूर्ण
/* set LCD backlight पूर्णांकensity */
पूर्णांक sx1_setbacklight(u8 backlight)
अणु
	अगर (backlight > SOFIA_MAX_LIGHT_VAL)
		backlight = SOFIA_MAX_LIGHT_VAL;
	वापस sx1_i2c_ग_लिखो_byte(SOFIA_I2C_ADDR, SOFIA_BACKLIGHT_REG,
				  backlight);
पूर्ण
/* get current LCD backlight पूर्णांकensity */
पूर्णांक sx1_getbacklight (u8 * backlight)
अणु
	वापस sx1_i2c_पढ़ो_byte(SOFIA_I2C_ADDR, SOFIA_BACKLIGHT_REG,
				 backlight);
पूर्ण
/* set LCD backlight घातer on/off */
पूर्णांक sx1_seपंचांगmiघातer(u8 onoff)
अणु
	पूर्णांक err;
	u8 dat = 0;
	err = sx1_i2c_पढ़ो_byte(SOFIA_I2C_ADDR, SOFIA_POWER1_REG, &dat);
	अगर (err < 0)
		वापस err;
	अगर (onoff)
		dat |= SOFIA_MMILIGHT_POWER;
	अन्यथा
		dat &= ~SOFIA_MMILIGHT_POWER;
	वापस sx1_i2c_ग_लिखो_byte(SOFIA_I2C_ADDR, SOFIA_POWER1_REG, dat);
पूर्ण

/* set USB घातer on/off */
पूर्णांक sx1_setusbघातer(u8 onoff)
अणु
	पूर्णांक err;
	u8 dat = 0;
	err = sx1_i2c_पढ़ो_byte(SOFIA_I2C_ADDR, SOFIA_POWER1_REG, &dat);
	अगर (err < 0)
		वापस err;
	अगर (onoff)
		dat |= SOFIA_USB_POWER;
	अन्यथा
		dat &= ~SOFIA_USB_POWER;
	वापस sx1_i2c_ग_लिखो_byte(SOFIA_I2C_ADDR, SOFIA_POWER1_REG, dat);
पूर्ण

EXPORT_SYMBOL(sx1_setkeylight);
EXPORT_SYMBOL(sx1_getkeylight);
EXPORT_SYMBOL(sx1_setbacklight);
EXPORT_SYMBOL(sx1_getbacklight);
EXPORT_SYMBOL(sx1_seपंचांगmiघातer);
EXPORT_SYMBOL(sx1_setusbघातer);

/*----------- Keypad -------------------------*/

अटल स्थिर अचिन्हित पूर्णांक sx1_keymap[] = अणु
	KEY(3, 5, GROUP_0 | 117), /* camera Qt::Key_F17 */
	KEY(4, 0, GROUP_0 | 114), /* voice memo Qt::Key_F14 */
	KEY(4, 1, GROUP_2 | 114), /* voice memo */
	KEY(4, 2, GROUP_3 | 114), /* voice memo */
	KEY(0, 0, GROUP_1 | KEY_F12),	/* red button Qt::Key_Hangup */
	KEY(3, 4, GROUP_1 | KEY_LEFT),
	KEY(3, 2, GROUP_1 | KEY_DOWN),
	KEY(3, 1, GROUP_1 | KEY_RIGHT),
	KEY(3, 0, GROUP_1 | KEY_UP),
	KEY(3, 3, GROUP_1 | KEY_POWER), /* joystick press or Qt::Key_Select */
	KEY(0, 5, GROUP_1 | KEY_1),
	KEY(0, 4, GROUP_1 | KEY_2),
	KEY(0, 3, GROUP_1 | KEY_3),
	KEY(4, 3, GROUP_1 | KEY_4),
	KEY(4, 4, GROUP_1 | KEY_5),
	KEY(4, 5, GROUP_1 | KEY_KPASTERISK),/* "*" */
	KEY(1, 4, GROUP_1 | KEY_6),
	KEY(1, 5, GROUP_1 | KEY_7),
	KEY(1, 3, GROUP_1 | KEY_8),
	KEY(2, 3, GROUP_1 | KEY_9),
	KEY(2, 5, GROUP_1 | KEY_0),
	KEY(2, 4, GROUP_1 | 113), /* # F13 Toggle input method Qt::Key_F13 */
	KEY(1, 0, GROUP_1 | KEY_F11),	/* green button Qt::Key_Call */
	KEY(2, 1, GROUP_1 | KEY_YEN),	/* left soft Qt::Key_Context1 */
	KEY(2, 2, GROUP_1 | KEY_F8),	/* right soft Qt::Key_Back */
	KEY(1, 2, GROUP_1 | KEY_LEFTSHIFT), /* shअगरt */
	KEY(1, 1, GROUP_1 | KEY_BACKSPACE), /* C (clear) */
	KEY(2, 0, GROUP_1 | KEY_F7),	/* menu Qt::Key_Menu */
पूर्ण;

अटल काष्ठा resource sx1_kp_resources[] = अणु
	[0] = अणु
		.start	= INT_KEYBOARD,
		.end	= INT_KEYBOARD,
		.flags	= IORESOURCE_IRQ,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा matrix_keymap_data sx1_keymap_data = अणु
	.keymap		= sx1_keymap,
	.keymap_size	= ARRAY_SIZE(sx1_keymap),
पूर्ण;

अटल काष्ठा omap_kp_platक्रमm_data sx1_kp_data = अणु
	.rows		= 6,
	.cols		= 6,
	.keymap_data	= &sx1_keymap_data,
	.delay	= 80,
पूर्ण;

अटल काष्ठा platक्रमm_device sx1_kp_device = अणु
	.name		= "omap-keypad",
	.id		= -1,
	.dev		= अणु
		.platक्रमm_data = &sx1_kp_data,
	पूर्ण,
	.num_resources	= ARRAY_SIZE(sx1_kp_resources),
	.resource	= sx1_kp_resources,
पूर्ण;

/*----------- MTD -------------------------*/

अटल काष्ठा mtd_partition sx1_partitions[] = अणु
	/* bootloader (U-Boot, etc) in first sector */
	अणु
		.name		= "bootloader",
		.offset		= 0x01800000,
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
		.size		= SZ_2M - 2 * SZ_128K,
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

अटल काष्ठा physmap_flash_data sx1_flash_data = अणु
	.width		= 2,
	.set_vpp	= omap1_set_vpp,
	.parts		= sx1_partitions,
	.nr_parts	= ARRAY_SIZE(sx1_partitions),
पूर्ण;

/* MTD Intel 4000 flash - new flashes */
अटल काष्ठा resource sx1_new_flash_resource = अणु
	.start		= OMAP_CS0_PHYS,
	.end		= OMAP_CS0_PHYS + SZ_32M - 1,
	.flags		= IORESOURCE_MEM,
पूर्ण;

अटल काष्ठा platक्रमm_device sx1_flash_device = अणु
	.name		= "physmap-flash",
	.id		= 0,
	.dev		= अणु
		.platक्रमm_data	= &sx1_flash_data,
	पूर्ण,
	.num_resources	= 1,
	.resource	= &sx1_new_flash_resource,
पूर्ण;

/*----------- USB -------------------------*/

अटल काष्ठा omap_usb_config sx1_usb_config __initdata = अणु
	.otg		= 0,
	.रेजिस्टर_dev	= 1,
	.रेजिस्टर_host	= 0,
	.hmc_mode	= 0,
	.pins[0]	= 2,
	.pins[1]	= 0,
	.pins[2]	= 0,
पूर्ण;

/*----------- LCD -------------------------*/

अटल स्थिर काष्ठा omap_lcd_config sx1_lcd_config __initस्थिर = अणु
	.ctrl_name	= "internal",
पूर्ण;

/*-----------------------------------------*/
अटल काष्ठा platक्रमm_device *sx1_devices[] __initdata = अणु
	&sx1_flash_device,
	&sx1_kp_device,
पूर्ण;

/*-----------------------------------------*/

अटल व्योम __init omap_sx1_init(व्योम)
अणु
	/* mux pins क्रम uarts */
	omap_cfg_reg(UART1_TX);
	omap_cfg_reg(UART1_RTS);
	omap_cfg_reg(UART2_TX);
	omap_cfg_reg(UART2_RTS);
	omap_cfg_reg(UART3_TX);
	omap_cfg_reg(UART3_RX);

	platक्रमm_add_devices(sx1_devices, ARRAY_SIZE(sx1_devices));

	omap_serial_init();
	omap_रेजिस्टर_i2c_bus(1, 100, शून्य, 0);
	omap1_usb_init(&sx1_usb_config);
	sx1_mmc_init();

	/* turn on USB घातer */
	/* sx1_setusbघातer(1); can't करो it here because i2c is not पढ़ोy */
	gpio_request(1, "A_IRDA_OFF");
	gpio_request(11, "A_SWITCH");
	gpio_request(15, "A_USB_ON");
	gpio_direction_output(1, 1);	/*A_IRDA_OFF = 1 */
	gpio_direction_output(11, 0);	/*A_SWITCH = 0 */
	gpio_direction_output(15, 0);	/*A_USB_ON = 0 */

	omapfb_set_lcd_config(&sx1_lcd_config);
पूर्ण

MACHINE_START(SX1, "OMAP310 based Siemens SX1")
	.atag_offset	= 0x100,
	.map_io		= omap15xx_map_io,
	.init_early     = omap1_init_early,
	.init_irq	= omap1_init_irq,
	.handle_irq	= omap1_handle_irq,
	.init_machine	= omap_sx1_init,
	.init_late	= omap1_init_late,
	.init_समय	= omap1_समयr_init,
	.restart	= omap1_restart,
MACHINE_END
