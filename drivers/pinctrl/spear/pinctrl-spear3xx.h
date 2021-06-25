<शैली गुरु>
/*
 * Header file क्रम the ST Microelectronics SPEAr3xx pinmux
 *
 * Copyright (C) 2012 ST Microelectronics
 * Viresh Kumar <vireshk@kernel.org>
 *
 * This file is licensed under the terms of the GNU General Public
 * License version 2. This program is licensed "as is" without any
 * warranty of any kind, whether express or implied.
 */

#अगर_अघोषित __PINMUX_SPEAR3XX_H__
#घोषणा __PINMUX_SPEAR3XX_H__

#समावेश "pinctrl-spear.h"

/* pad mux declarations */
#घोषणा PMX_PWM_MASK		(1 << 16)
#घोषणा PMX_FIRDA_MASK		(1 << 14)
#घोषणा PMX_I2C_MASK		(1 << 13)
#घोषणा PMX_SSP_CS_MASK		(1 << 12)
#घोषणा PMX_SSP_MASK		(1 << 11)
#घोषणा PMX_MII_MASK		(1 << 10)
#घोषणा PMX_GPIO_PIN0_MASK	(1 << 9)
#घोषणा PMX_GPIO_PIN1_MASK	(1 << 8)
#घोषणा PMX_GPIO_PIN2_MASK	(1 << 7)
#घोषणा PMX_GPIO_PIN3_MASK	(1 << 6)
#घोषणा PMX_GPIO_PIN4_MASK	(1 << 5)
#घोषणा PMX_GPIO_PIN5_MASK	(1 << 4)
#घोषणा PMX_UART0_MODEM_MASK	(1 << 3)
#घोषणा PMX_UART0_MASK		(1 << 2)
#घोषणा PMX_TIMER_2_3_MASK	(1 << 1)
#घोषणा PMX_TIMER_0_1_MASK	(1 << 0)

बाह्य काष्ठा spear_pingroup spear3xx_firda_pingroup;
बाह्य काष्ठा spear_pingroup spear3xx_gpio0_pin0_pingroup;
बाह्य काष्ठा spear_pingroup spear3xx_gpio0_pin1_pingroup;
बाह्य काष्ठा spear_pingroup spear3xx_gpio0_pin2_pingroup;
बाह्य काष्ठा spear_pingroup spear3xx_gpio0_pin3_pingroup;
बाह्य काष्ठा spear_pingroup spear3xx_gpio0_pin4_pingroup;
बाह्य काष्ठा spear_pingroup spear3xx_gpio0_pin5_pingroup;
बाह्य काष्ठा spear_pingroup spear3xx_i2c_pingroup;
बाह्य काष्ठा spear_pingroup spear3xx_mii_pingroup;
बाह्य काष्ठा spear_pingroup spear3xx_ssp_cs_pingroup;
बाह्य काष्ठा spear_pingroup spear3xx_ssp_pingroup;
बाह्य काष्ठा spear_pingroup spear3xx_समयr_0_1_pingroup;
बाह्य काष्ठा spear_pingroup spear3xx_समयr_2_3_pingroup;
बाह्य काष्ठा spear_pingroup spear3xx_uart0_ext_pingroup;
बाह्य काष्ठा spear_pingroup spear3xx_uart0_pingroup;

#घोषणा SPEAR3XX_COMMON_PINGROUPS		\
	&spear3xx_firda_pingroup,		\
	&spear3xx_gpio0_pin0_pingroup,		\
	&spear3xx_gpio0_pin1_pingroup,		\
	&spear3xx_gpio0_pin2_pingroup,		\
	&spear3xx_gpio0_pin3_pingroup,		\
	&spear3xx_gpio0_pin4_pingroup,		\
	&spear3xx_gpio0_pin5_pingroup,		\
	&spear3xx_i2c_pingroup,			\
	&spear3xx_mii_pingroup,			\
	&spear3xx_ssp_cs_pingroup,		\
	&spear3xx_ssp_pingroup,			\
	&spear3xx_समयr_0_1_pingroup,		\
	&spear3xx_समयr_2_3_pingroup,		\
	&spear3xx_uart0_ext_pingroup,		\
	&spear3xx_uart0_pingroup

बाह्य काष्ठा spear_function spear3xx_firda_function;
बाह्य काष्ठा spear_function spear3xx_gpio0_function;
बाह्य काष्ठा spear_function spear3xx_i2c_function;
बाह्य काष्ठा spear_function spear3xx_mii_function;
बाह्य काष्ठा spear_function spear3xx_ssp_cs_function;
बाह्य काष्ठा spear_function spear3xx_ssp_function;
बाह्य काष्ठा spear_function spear3xx_समयr_0_1_function;
बाह्य काष्ठा spear_function spear3xx_समयr_2_3_function;
बाह्य काष्ठा spear_function spear3xx_uart0_ext_function;
बाह्य काष्ठा spear_function spear3xx_uart0_function;

#घोषणा SPEAR3XX_COMMON_FUNCTIONS		\
	&spear3xx_firda_function,		\
	&spear3xx_gpio0_function,		\
	&spear3xx_i2c_function,			\
	&spear3xx_mii_function,			\
	&spear3xx_ssp_cs_function,		\
	&spear3xx_ssp_function,			\
	&spear3xx_समयr_0_1_function,		\
	&spear3xx_समयr_2_3_function,		\
	&spear3xx_uart0_ext_function,		\
	&spear3xx_uart0_function

बाह्य काष्ठा spear_pinctrl_machdata spear3xx_machdata;

#पूर्ण_अगर /* __PINMUX_SPEAR3XX_H__ */
