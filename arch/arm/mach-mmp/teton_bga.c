<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 *  linux/arch/arm/mach-mmp/teton_bga.c
 *
 *  Support क्रम the Marvell PXA168 Teton BGA Development Platक्रमm.
 *
 *  Author: Mark F. Brown <mark.brown314@gmail.com>
 *
 *  This code is based on aspenite.c
 */

#समावेश <linux/init.h>
#समावेश <linux/kernel.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/gpपन.स>
#समावेश <linux/gpio-pxa.h>
#समावेश <linux/input.h>
#समावेश <linux/platक्रमm_data/keypad-pxa27x.h>
#समावेश <linux/i2c.h>

#समावेश <यंत्र/mach-types.h>
#समावेश <यंत्र/mach/arch.h>
#समावेश "addr-map.h"
#समावेश "mfp-pxa168.h"
#समावेश "pxa168.h"
#समावेश "teton_bga.h"
#समावेश "irqs.h"

#समावेश "common.h"

अटल अचिन्हित दीर्घ teton_bga_pin_config[] __initdata = अणु
	/* UART1 */
	GPIO107_UART1_TXD,
	GPIO108_UART1_RXD,

	/* Keypad */
	GPIO109_KP_MKIN1,
	GPIO110_KP_MKIN0,
	GPIO111_KP_MKOUT7,
	GPIO112_KP_MKOUT6,

	/* I2C Bus */
	GPIO105_CI2C_SDA,
	GPIO106_CI2C_SCL,

	/* RTC */
	GPIO78_GPIO,
पूर्ण;

अटल काष्ठा pxa_gpio_platक्रमm_data pxa168_gpio_pdata = अणु
	.irq_base	= MMP_GPIO_TO_IRQ(0),
पूर्ण;

अटल अचिन्हित पूर्णांक teton_bga_matrix_key_map[] = अणु
	KEY(0, 6, KEY_ESC),
	KEY(0, 7, KEY_ENTER),
	KEY(1, 6, KEY_LEFT),
	KEY(1, 7, KEY_RIGHT),
पूर्ण;

अटल काष्ठा matrix_keymap_data teton_bga_matrix_keymap_data = अणु
	.keymap			= teton_bga_matrix_key_map,
	.keymap_size		= ARRAY_SIZE(teton_bga_matrix_key_map),
पूर्ण;

अटल काष्ठा pxa27x_keypad_platक्रमm_data teton_bga_keypad_info __initdata = अणु
	.matrix_key_rows        = 2,
	.matrix_key_cols        = 8,
	.matrix_keymap_data	= &teton_bga_matrix_keymap_data,
	.debounce_पूर्णांकerval      = 30,
पूर्ण;

अटल काष्ठा i2c_board_info teton_bga_i2c_info[] __initdata = अणु
	अणु
		I2C_BOARD_INFO("ds1337", 0x68),
		.irq = MMP_GPIO_TO_IRQ(RTC_INT_GPIO)
	पूर्ण,
पूर्ण;

अटल व्योम __init teton_bga_init(व्योम)
अणु
	mfp_config(ARRAY_AND_SIZE(teton_bga_pin_config));

	/* on-chip devices */
	pxa168_add_uart(1);
	pxa168_add_keypad(&teton_bga_keypad_info);
	pxa168_add_twsi(0, शून्य, ARRAY_AND_SIZE(teton_bga_i2c_info));
	platक्रमm_device_add_data(&pxa168_device_gpio, &pxa168_gpio_pdata,
				 माप(काष्ठा pxa_gpio_platक्रमm_data));
	platक्रमm_device_रेजिस्टर(&pxa168_device_gpio);
पूर्ण

MACHINE_START(TETON_BGA, "PXA168-based Teton BGA Development Platform")
	.map_io		= mmp_map_io,
	.nr_irqs	= MMP_NR_IRQS,
	.init_irq       = pxa168_init_irq,
	.init_समय	= pxa168_समयr_init,
	.init_machine   = teton_bga_init,
	.restart	= pxa168_restart,
MACHINE_END
