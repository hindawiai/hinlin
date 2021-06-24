<शैली गुरु>
/*
 * pinctrl-palmas.c -- TI PALMAS series pin control driver.
 *
 * Copyright (c) 2013, NVIDIA Corporation.
 *
 * Author: Laxman Dewangan <ldewangan@nvidia.com>
 *
 * This program is मुक्त software; you can redistribute it and/or
 * modअगरy it under the terms of the GNU General Public License as
 * published by the Free Software Foundation version 2.
 *
 * This program is distributed "as is" WITHOUT ANY WARRANTY of any kind,
 * whether express or implied; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * General Public License क्रम more details.
 *
 * You should have received a copy of the GNU General Public License
 * aदीर्घ with this program; अगर not, ग_लिखो to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA
 * 02111-1307, USA
 */

#समावेश <linux/delay.h>
#समावेश <linux/module.h>
#समावेश <linux/mfd/palmas.h>
#समावेश <linux/of.h>
#समावेश <linux/of_device.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/pinctrl/machine.h>
#समावेश <linux/pinctrl/pinctrl.h>
#समावेश <linux/pinctrl/pinconf-generic.h>
#समावेश <linux/pinctrl/pinconf.h>
#समावेश <linux/pinctrl/pinmux.h>
#समावेश <linux/pm.h>
#समावेश <linux/slab.h>

#समावेश "core.h"
#समावेश "pinconf.h"
#समावेश "pinctrl-utils.h"

#घोषणा PALMAS_PIN_GPIO0_ID				0
#घोषणा PALMAS_PIN_GPIO1_VBUS_LED1_PWM1			1
#घोषणा PALMAS_PIN_GPIO2_REGEN_LED2_PWM2		2
#घोषणा PALMAS_PIN_GPIO3_CHRG_DET			3
#घोषणा PALMAS_PIN_GPIO4_SYSEN1				4
#घोषणा PALMAS_PIN_GPIO5_CLK32KGAUDIO_USB_PSEL		5
#घोषणा PALMAS_PIN_GPIO6_SYSEN2				6
#घोषणा PALMAS_PIN_GPIO7_MSECURE_PWRHOLD		7
#घोषणा PALMAS_PIN_GPIO8_SIM1RSTI			8
#घोषणा PALMAS_PIN_GPIO9_LOW_VBAT			9
#घोषणा PALMAS_PIN_GPIO10_WIRELESS_CHRG1		10
#घोषणा PALMAS_PIN_GPIO11_RCM				11
#घोषणा PALMAS_PIN_GPIO12_SIM2RSTO			12
#घोषणा PALMAS_PIN_GPIO13				13
#घोषणा PALMAS_PIN_GPIO14				14
#घोषणा PALMAS_PIN_GPIO15_SIM2RSTI			15
#घोषणा PALMAS_PIN_VAC					16
#घोषणा PALMAS_PIN_POWERGOOD_USB_PSEL			17
#घोषणा PALMAS_PIN_NRESWARM				18
#घोषणा PALMAS_PIN_PWRDOWN				19
#घोषणा PALMAS_PIN_GPADC_START				20
#घोषणा PALMAS_PIN_RESET_IN				21
#घोषणा PALMAS_PIN_NSLEEP				22
#घोषणा PALMAS_PIN_ENABLE1				23
#घोषणा PALMAS_PIN_ENABLE2				24
#घोषणा PALMAS_PIN_INT					25
#घोषणा PALMAS_PIN_NUM					(PALMAS_PIN_INT + 1)

काष्ठा palmas_pin_function अणु
	स्थिर अक्षर *name;
	स्थिर अक्षर * स्थिर *groups;
	अचिन्हित ngroups;
पूर्ण;

काष्ठा palmas_pctrl_chip_info अणु
	काष्ठा device *dev;
	काष्ठा pinctrl_dev *pctl;
	काष्ठा palmas *palmas;
	पूर्णांक pins_current_opt[PALMAS_PIN_NUM];
	स्थिर काष्ठा palmas_pin_function *functions;
	अचिन्हित num_functions;
	स्थिर काष्ठा palmas_pingroup *pin_groups;
	पूर्णांक num_pin_groups;
	स्थिर काष्ठा pinctrl_pin_desc *pins;
	अचिन्हित num_pins;
पूर्ण;

अटल स्थिर काष्ठा pinctrl_pin_desc palmas_pins_desc[] = अणु
	PINCTRL_PIN(PALMAS_PIN_GPIO0_ID, "gpio0"),
	PINCTRL_PIN(PALMAS_PIN_GPIO1_VBUS_LED1_PWM1, "gpio1"),
	PINCTRL_PIN(PALMAS_PIN_GPIO2_REGEN_LED2_PWM2, "gpio2"),
	PINCTRL_PIN(PALMAS_PIN_GPIO3_CHRG_DET, "gpio3"),
	PINCTRL_PIN(PALMAS_PIN_GPIO4_SYSEN1, "gpio4"),
	PINCTRL_PIN(PALMAS_PIN_GPIO5_CLK32KGAUDIO_USB_PSEL, "gpio5"),
	PINCTRL_PIN(PALMAS_PIN_GPIO6_SYSEN2, "gpio6"),
	PINCTRL_PIN(PALMAS_PIN_GPIO7_MSECURE_PWRHOLD, "gpio7"),
	PINCTRL_PIN(PALMAS_PIN_GPIO8_SIM1RSTI, "gpio8"),
	PINCTRL_PIN(PALMAS_PIN_GPIO9_LOW_VBAT, "gpio9"),
	PINCTRL_PIN(PALMAS_PIN_GPIO10_WIRELESS_CHRG1, "gpio10"),
	PINCTRL_PIN(PALMAS_PIN_GPIO11_RCM, "gpio11"),
	PINCTRL_PIN(PALMAS_PIN_GPIO12_SIM2RSTO, "gpio12"),
	PINCTRL_PIN(PALMAS_PIN_GPIO13, "gpio13"),
	PINCTRL_PIN(PALMAS_PIN_GPIO14, "gpio14"),
	PINCTRL_PIN(PALMAS_PIN_GPIO15_SIM2RSTI, "gpio15"),
	PINCTRL_PIN(PALMAS_PIN_VAC, "vac"),
	PINCTRL_PIN(PALMAS_PIN_POWERGOOD_USB_PSEL, "powergood"),
	PINCTRL_PIN(PALMAS_PIN_NRESWARM, "nreswarm"),
	PINCTRL_PIN(PALMAS_PIN_PWRDOWN, "pwrdown"),
	PINCTRL_PIN(PALMAS_PIN_GPADC_START, "gpadc_start"),
	PINCTRL_PIN(PALMAS_PIN_RESET_IN, "reset_in"),
	PINCTRL_PIN(PALMAS_PIN_NSLEEP, "nsleep"),
	PINCTRL_PIN(PALMAS_PIN_ENABLE1, "enable1"),
	PINCTRL_PIN(PALMAS_PIN_ENABLE2, "enable2"),
	PINCTRL_PIN(PALMAS_PIN_INT, "int"),
पूर्ण;

अटल स्थिर अक्षर * स्थिर opt0_groups[] = अणु
	"gpio0",
	"gpio1",
	"gpio2",
	"gpio3",
	"gpio4",
	"gpio5",
	"gpio6",
	"gpio7",
	"gpio8",
	"gpio9",
	"gpio10",
	"gpio11",
	"gpio12",
	"gpio13",
	"gpio14",
	"gpio15",
	"vac",
	"powergood",
	"nreswarm",
	"pwrdown",
	"gpadc_start",
	"reset_in",
	"nsleep",
	"enable1",
	"enable2",
	"int",
पूर्ण;

अटल स्थिर अक्षर * स्थिर opt1_groups[] = अणु
	"gpio0",
	"gpio1",
	"gpio2",
	"gpio3",
	"gpio4",
	"gpio5",
	"gpio6",
	"gpio7",
	"gpio8",
	"gpio9",
	"gpio10",
	"gpio11",
	"gpio12",
	"gpio15",
	"vac",
	"powergood",
पूर्ण;

अटल स्थिर अक्षर * स्थिर opt2_groups[] = अणु
	"gpio1",
	"gpio2",
	"gpio5",
	"gpio7",
पूर्ण;

अटल स्थिर अक्षर * स्थिर opt3_groups[] = अणु
	"gpio1",
	"gpio2",
पूर्ण;

अटल स्थिर अक्षर * स्थिर gpio_groups[] = अणु
	"gpio0",
	"gpio1",
	"gpio2",
	"gpio3",
	"gpio4",
	"gpio5",
	"gpio6",
	"gpio7",
	"gpio8",
	"gpio9",
	"gpio10",
	"gpio11",
	"gpio12",
	"gpio13",
	"gpio14",
	"gpio15",
पूर्ण;

अटल स्थिर अक्षर * स्थिर led_groups[] = अणु
	"gpio1",
	"gpio2",
पूर्ण;

अटल स्थिर अक्षर * स्थिर pwm_groups[] = अणु
	"gpio1",
	"gpio2",
पूर्ण;

अटल स्थिर अक्षर * स्थिर regen_groups[] = अणु
	"gpio2",
पूर्ण;

अटल स्थिर अक्षर * स्थिर sysen_groups[] = अणु
	"gpio4",
	"gpio6",
पूर्ण;

अटल स्थिर अक्षर * स्थिर clk32kgaudio_groups[] = अणु
	"gpio5",
पूर्ण;

अटल स्थिर अक्षर * स्थिर id_groups[] = अणु
	"gpio0",
पूर्ण;

अटल स्थिर अक्षर * स्थिर vbus_det_groups[] = अणु
	"gpio1",
पूर्ण;

अटल स्थिर अक्षर * स्थिर chrg_det_groups[] = अणु
	"gpio3",
पूर्ण;

अटल स्थिर अक्षर * स्थिर vac_groups[] = अणु
	"vac",
पूर्ण;

अटल स्थिर अक्षर * स्थिर vacok_groups[] = अणु
	"vac",
पूर्ण;

अटल स्थिर अक्षर * स्थिर घातergood_groups[] = अणु
	"powergood",
पूर्ण;

अटल स्थिर अक्षर * स्थिर usb_psel_groups[] = अणु
	"gpio5",
	"powergood",
पूर्ण;

अटल स्थिर अक्षर * स्थिर msecure_groups[] = अणु
	"gpio7",
पूर्ण;

अटल स्थिर अक्षर * स्थिर pwrhold_groups[] = अणु
	"gpio7",
पूर्ण;

अटल स्थिर अक्षर * स्थिर पूर्णांक_groups[] = अणु
	"int",
पूर्ण;

अटल स्थिर अक्षर * स्थिर nreswarm_groups[] = अणु
	"nreswarm",
पूर्ण;

अटल स्थिर अक्षर * स्थिर simrsto_groups[] = अणु
	"gpio12",
पूर्ण;

अटल स्थिर अक्षर * स्थिर simrsti_groups[] = अणु
	"gpio8",
	"gpio15",
पूर्ण;

अटल स्थिर अक्षर * स्थिर low_vbat_groups[] = अणु
	"gpio9",
पूर्ण;

अटल स्थिर अक्षर * स्थिर wireless_chrg1_groups[] = अणु
	"gpio10",
पूर्ण;

अटल स्थिर अक्षर * स्थिर rcm_groups[] = अणु
	"gpio11",
पूर्ण;

अटल स्थिर अक्षर * स्थिर pwrकरोwn_groups[] = अणु
	"pwrdown",
पूर्ण;

अटल स्थिर अक्षर * स्थिर gpadc_start_groups[] = अणु
	"gpadc_start",
पूर्ण;

अटल स्थिर अक्षर * स्थिर reset_in_groups[] = अणु
	"reset_in",
पूर्ण;

अटल स्थिर अक्षर * स्थिर nsleep_groups[] = अणु
	"nsleep",
पूर्ण;

अटल स्थिर अक्षर * स्थिर enable_groups[] = अणु
	"enable1",
	"enable2",
पूर्ण;

#घोषणा FUNCTION_GROUPS					\
	FUNCTION_GROUP(opt0, OPTION0),			\
	FUNCTION_GROUP(opt1, OPTION1),			\
	FUNCTION_GROUP(opt2, OPTION2),			\
	FUNCTION_GROUP(opt3, OPTION3),			\
	FUNCTION_GROUP(gpio, GPIO),			\
	FUNCTION_GROUP(led, LED),			\
	FUNCTION_GROUP(pwm, PWM),			\
	FUNCTION_GROUP(regen, REGEN),			\
	FUNCTION_GROUP(sysen, SYSEN),			\
	FUNCTION_GROUP(clk32kgaudio, CLK32KGAUDIO),	\
	FUNCTION_GROUP(id, ID),				\
	FUNCTION_GROUP(vbus_det, VBUS_DET),		\
	FUNCTION_GROUP(chrg_det, CHRG_DET),		\
	FUNCTION_GROUP(vac, VAC),			\
	FUNCTION_GROUP(vacok, VACOK),			\
	FUNCTION_GROUP(घातergood, POWERGOOD),		\
	FUNCTION_GROUP(usb_psel, USB_PSEL),		\
	FUNCTION_GROUP(msecure, MSECURE),		\
	FUNCTION_GROUP(pwrhold, PWRHOLD),		\
	FUNCTION_GROUP(पूर्णांक, INT),			\
	FUNCTION_GROUP(nreswarm, NRESWARM),		\
	FUNCTION_GROUP(simrsto, SIMRSTO),		\
	FUNCTION_GROUP(simrsti, SIMRSTI),		\
	FUNCTION_GROUP(low_vbat, LOW_VBAT),		\
	FUNCTION_GROUP(wireless_chrg1, WIRELESS_CHRG1),	\
	FUNCTION_GROUP(rcm, RCM),			\
	FUNCTION_GROUP(pwrकरोwn, PWRDOWN),		\
	FUNCTION_GROUP(gpadc_start, GPADC_START),	\
	FUNCTION_GROUP(reset_in, RESET_IN),		\
	FUNCTION_GROUP(nsleep, NSLEEP),			\
	FUNCTION_GROUP(enable, ENABLE)

अटल स्थिर काष्ठा palmas_pin_function palmas_pin_function[] = अणु
#अघोषित FUNCTION_GROUP
#घोषणा FUNCTION_GROUP(fname, mux)			\
	अणु						\
		.name = #fname,				\
		.groups = fname##_groups,		\
		.ngroups = ARRAY_SIZE(fname##_groups),	\
	पूर्ण

	FUNCTION_GROUPS,
पूर्ण;

क्रमागत palmas_pinmux अणु
#अघोषित FUNCTION_GROUP
#घोषणा FUNCTION_GROUP(fname, mux)	PALMAS_PINMUX_##mux
	FUNCTION_GROUPS,
	PALMAS_PINMUX_NA = 0xFFFF,
पूर्ण;

काष्ठा palmas_pins_pullup_dn_info अणु
	पूर्णांक pullup_dn_reg_base;
	पूर्णांक pullup_dn_reg_add;
	पूर्णांक pullup_dn_mask;
	पूर्णांक normal_val;
	पूर्णांक pull_up_val;
	पूर्णांक pull_dn_val;
पूर्ण;

काष्ठा palmas_pins_od_info अणु
	पूर्णांक od_reg_base;
	पूर्णांक od_reg_add;
	पूर्णांक od_mask;
	पूर्णांक od_enable;
	पूर्णांक od_disable;
पूर्ण;

काष्ठा palmas_pin_info अणु
	क्रमागत palmas_pinmux mux_opt;
	स्थिर काष्ठा palmas_pins_pullup_dn_info *pud_info;
	स्थिर काष्ठा palmas_pins_od_info *od_info;
पूर्ण;

काष्ठा palmas_pingroup अणु
	स्थिर अक्षर *name;
	स्थिर अचिन्हित pins[1];
	अचिन्हित npins;
	अचिन्हित mux_reg_base;
	अचिन्हित mux_reg_add;
	अचिन्हित mux_reg_mask;
	अचिन्हित mux_bit_shअगरt;
	स्थिर काष्ठा palmas_pin_info *opt[4];
पूर्ण;

#घोषणा PULL_UP_DN(_name, _rbase, _add, _mask, _nv, _uv, _dv)		\
अटल स्थिर काष्ठा palmas_pins_pullup_dn_info pud_##_name##_info = अणु	\
	.pullup_dn_reg_base = PALMAS_##_rbase##_BASE,			\
	.pullup_dn_reg_add = _add,					\
	.pullup_dn_mask = _mask,					\
	.normal_val = _nv,						\
	.pull_up_val = _uv,						\
	.pull_dn_val = _dv,						\
पूर्ण

PULL_UP_DN(nreswarm,	PU_PD_OD,	PALMAS_PU_PD_INPUT_CTRL1,	0x2,	0x0,	0x2,	-1);
PULL_UP_DN(pwrकरोwn,	PU_PD_OD,	PALMAS_PU_PD_INPUT_CTRL1,	0x4,	0x0,	-1,	0x4);
PULL_UP_DN(gpadc_start,	PU_PD_OD,	PALMAS_PU_PD_INPUT_CTRL1,	0x30,	0x0,	0x20,	0x10);
PULL_UP_DN(reset_in,	PU_PD_OD,	PALMAS_PU_PD_INPUT_CTRL1,	0x40,	0x0,	-1,	0x40);
PULL_UP_DN(nsleep,	PU_PD_OD,	PALMAS_PU_PD_INPUT_CTRL2,	0x3,	0x0,	0x2,	0x1);
PULL_UP_DN(enable1,	PU_PD_OD,	PALMAS_PU_PD_INPUT_CTRL2,	0xC,	0x0,	0x8,	0x4);
PULL_UP_DN(enable2,	PU_PD_OD,	PALMAS_PU_PD_INPUT_CTRL2,	0x30,	0x0,	0x20,	0x10);
PULL_UP_DN(vacok,	PU_PD_OD,	PALMAS_PU_PD_INPUT_CTRL3,	0x40,	0x0,	-1,	0x40);
PULL_UP_DN(chrg_det,	PU_PD_OD,	PALMAS_PU_PD_INPUT_CTRL3,	0x10,	0x0,	-1,	0x10);
PULL_UP_DN(pwrhold,	PU_PD_OD,	PALMAS_PU_PD_INPUT_CTRL3,	0x4,	0x0,	-1,	0x4);
PULL_UP_DN(msecure,	PU_PD_OD,	PALMAS_PU_PD_INPUT_CTRL3,	0x1,	0x0,	-1,	0x1);
PULL_UP_DN(id,		USB_OTG,	PALMAS_USB_ID_CTRL_SET,		0x40,	0x0,	0x40,	-1);
PULL_UP_DN(gpio0,	GPIO,		PALMAS_PU_PD_GPIO_CTRL1,	0x04,	0,	-1,	1);
PULL_UP_DN(gpio1,	GPIO,		PALMAS_PU_PD_GPIO_CTRL1,	0x0C,	0,	0x8,	0x4);
PULL_UP_DN(gpio2,	GPIO,		PALMAS_PU_PD_GPIO_CTRL1,	0x30,	0x0,	0x20,	0x10);
PULL_UP_DN(gpio3,	GPIO,		PALMAS_PU_PD_GPIO_CTRL1,	0x40,	0x0,	-1,	0x40);
PULL_UP_DN(gpio4,	GPIO,		PALMAS_PU_PD_GPIO_CTRL2,	0x03,	0x0,	0x2,	0x1);
PULL_UP_DN(gpio5,	GPIO,		PALMAS_PU_PD_GPIO_CTRL2,	0x0c,	0x0,	0x8,	0x4);
PULL_UP_DN(gpio6,	GPIO,		PALMAS_PU_PD_GPIO_CTRL2,	0x30,	0x0,	0x20,	0x10);
PULL_UP_DN(gpio7,	GPIO,		PALMAS_PU_PD_GPIO_CTRL2,	0x40,	0x0,	-1,	0x40);
PULL_UP_DN(gpio9,	GPIO,		PALMAS_PU_PD_GPIO_CTRL3,	0x0C,	0x0,	0x8,	0x4);
PULL_UP_DN(gpio10,	GPIO,		PALMAS_PU_PD_GPIO_CTRL3,	0x30,	0x0,	0x20,	0x10);
PULL_UP_DN(gpio11,	GPIO,		PALMAS_PU_PD_GPIO_CTRL3,	0xC0,	0x0,	0x80,	0x40);
PULL_UP_DN(gpio13,	GPIO,		PALMAS_PU_PD_GPIO_CTRL4,	0x04,	0x0,	-1,	0x04);
PULL_UP_DN(gpio14,	GPIO,		PALMAS_PU_PD_GPIO_CTRL4,	0x30,	0x0,	0x20,	0x10);

#घोषणा OD_INFO(_name, _rbase, _add, _mask, _ev, _dv)		\
अटल स्थिर काष्ठा palmas_pins_od_info od_##_name##_info = अणु	\
	.od_reg_base = PALMAS_##_rbase##_BASE,			\
	.od_reg_add = _add,					\
	.od_mask = _mask,					\
	.od_enable = _ev,					\
	.od_disable = _dv,					\
पूर्ण

OD_INFO(gpio1,	GPIO,	PALMAS_OD_OUTPUT_GPIO_CTRL,	0x1,	0x1,	0x0);
OD_INFO(gpio2,	GPIO,	PALMAS_OD_OUTPUT_GPIO_CTRL,	0x2,	0x2,	0x0);
OD_INFO(gpio5,	GPIO,	PALMAS_OD_OUTPUT_GPIO_CTRL,	0x20,	0x20,	0x0);
OD_INFO(gpio10,	GPIO,	PALMAS_OD_OUTPUT_GPIO_CTRL2,	0x04,	0x04,	0x0);
OD_INFO(gpio13,	GPIO,	PALMAS_OD_OUTPUT_GPIO_CTRL2,	0x20,	0x20,	0x0);
OD_INFO(पूर्णांक,		PU_PD_OD,	PALMAS_OD_OUTPUT_CTRL,	0x8,	0x8,	0x0);
OD_INFO(pwm1,		PU_PD_OD,	PALMAS_OD_OUTPUT_CTRL,	0x20,	0x20,	0x0);
OD_INFO(pwm2,		PU_PD_OD,	PALMAS_OD_OUTPUT_CTRL,	0x80,	0x80,	0x0);
OD_INFO(vbus_det,	PU_PD_OD,	PALMAS_OD_OUTPUT_CTRL,	0x40,	0x40,	0x0);

#घोषणा PIN_INFO(_name, _id, _pud_info, _od_info)		\
अटल स्थिर काष्ठा palmas_pin_info pin_##_name##_info = अणु	\
	.mux_opt = PALMAS_PINMUX_##_id,				\
	.pud_info = _pud_info,					\
	.od_info = _od_info					\
पूर्ण

PIN_INFO(gpio0,		GPIO,		&pud_gpio0_info,	शून्य);
PIN_INFO(gpio1,		GPIO,		&pud_gpio1_info,	&od_gpio1_info);
PIN_INFO(gpio2,		GPIO,		&pud_gpio2_info,	&od_gpio2_info);
PIN_INFO(gpio3,		GPIO,		&pud_gpio3_info,	शून्य);
PIN_INFO(gpio4,		GPIO,		&pud_gpio4_info,	शून्य);
PIN_INFO(gpio5,		GPIO,		&pud_gpio5_info,	&od_gpio5_info);
PIN_INFO(gpio6,		GPIO,		&pud_gpio6_info,	शून्य);
PIN_INFO(gpio7,		GPIO,		&pud_gpio7_info,	शून्य);
PIN_INFO(gpio8,		GPIO,		शून्य,			शून्य);
PIN_INFO(gpio9,		GPIO,		&pud_gpio9_info,	शून्य);
PIN_INFO(gpio10,	GPIO,		&pud_gpio10_info,	&od_gpio10_info);
PIN_INFO(gpio11,	GPIO,		&pud_gpio11_info,	शून्य);
PIN_INFO(gpio12,	GPIO,		शून्य,			शून्य);
PIN_INFO(gpio13,	GPIO,		&pud_gpio13_info,	&od_gpio13_info);
PIN_INFO(gpio14,	GPIO,		&pud_gpio14_info,	शून्य);
PIN_INFO(gpio15,	GPIO,		शून्य,			शून्य);
PIN_INFO(id,		ID,		&pud_id_info,		शून्य);
PIN_INFO(led1,		LED,		शून्य,			शून्य);
PIN_INFO(led2,		LED,		शून्य,			शून्य);
PIN_INFO(regen,		REGEN,		शून्य,			शून्य);
PIN_INFO(sysen1,	SYSEN,		शून्य,			शून्य);
PIN_INFO(sysen2,	SYSEN,		शून्य,			शून्य);
PIN_INFO(पूर्णांक,		INT,		शून्य,			&od_पूर्णांक_info);
PIN_INFO(pwm1,		PWM,		शून्य,			&od_pwm1_info);
PIN_INFO(pwm2,		PWM,		शून्य,			&od_pwm2_info);
PIN_INFO(vacok,		VACOK,		&pud_vacok_info,	शून्य);
PIN_INFO(chrg_det,	CHRG_DET,	&pud_chrg_det_info,	शून्य);
PIN_INFO(pwrhold,	PWRHOLD,	&pud_pwrhold_info,	शून्य);
PIN_INFO(msecure,	MSECURE,	&pud_msecure_info,	शून्य);
PIN_INFO(nreswarm,	NA,		&pud_nreswarm_info,	शून्य);
PIN_INFO(pwrकरोwn,	NA,		&pud_pwrकरोwn_info,	शून्य);
PIN_INFO(gpadc_start,	NA,		&pud_gpadc_start_info,	शून्य);
PIN_INFO(reset_in,	NA,		&pud_reset_in_info,	शून्य);
PIN_INFO(nsleep,	NA,		&pud_nsleep_info,	शून्य);
PIN_INFO(enable1,	NA,		&pud_enable1_info,	शून्य);
PIN_INFO(enable2,	NA,		&pud_enable2_info,	शून्य);
PIN_INFO(clk32kgaudio,	CLK32KGAUDIO,	शून्य,			शून्य);
PIN_INFO(usb_psel,	USB_PSEL,	शून्य,			शून्य);
PIN_INFO(vac,		VAC,		शून्य,			शून्य);
PIN_INFO(घातergood,	POWERGOOD,	शून्य,			शून्य);
PIN_INFO(vbus_det,	VBUS_DET,	शून्य,			&od_vbus_det_info);
PIN_INFO(sim1rsti,	SIMRSTI,	शून्य,			शून्य);
PIN_INFO(low_vbat,	LOW_VBAT,	शून्य,			शून्य);
PIN_INFO(rcm,		RCM,		शून्य,			शून्य);
PIN_INFO(sim2rsto,	SIMRSTO,	शून्य,			शून्य);
PIN_INFO(sim2rsti,	SIMRSTI,	शून्य,			शून्य);
PIN_INFO(wireless_chrg1,	WIRELESS_CHRG1,	शून्य,		शून्य);

#घोषणा PALMAS_PRIMARY_SECONDARY_NONE	0
#घोषणा PALMAS_NONE_BASE		0
#घोषणा PALMAS_PRIMARY_SECONDARY_INPUT3 PALMAS_PU_PD_INPUT_CTRL3

#घोषणा PALMAS_PINGROUP(pg_name, pin_id, base, reg, _mask, _bshअगरt, o0, o1, o2, o3)  \
	अणु								\
		.name = #pg_name,					\
		.pins = अणुPALMAS_PIN_##pin_idपूर्ण,				\
		.npins = 1,						\
		.mux_reg_base = PALMAS_##base##_BASE,			\
		.mux_reg_add = PALMAS_PRIMARY_SECONDARY_##reg,		\
		.mux_reg_mask = _mask,					\
		.mux_bit_shअगरt = _bshअगरt,				\
		.opt = अणु						\
			o0,						\
			o1,						\
			o2,						\
			o3,						\
		पूर्ण,							\
	पूर्ण

अटल स्थिर काष्ठा palmas_pingroup tps65913_pingroups[] = अणु
	PALMAS_PINGROUP(gpio0,	GPIO0_ID,			PU_PD_OD,	PAD1,	0x4,	0x2,	&pin_gpio0_info,	&pin_id_info,		शून्य,		शून्य),
	PALMAS_PINGROUP(gpio1,	GPIO1_VBUS_LED1_PWM1,		PU_PD_OD,	PAD1,	0x18,	0x3,	&pin_gpio1_info,	&pin_vbus_det_info,	&pin_led1_info,	&pin_pwm1_info),
	PALMAS_PINGROUP(gpio2,	GPIO2_REGEN_LED2_PWM2,		PU_PD_OD,	PAD1,	0x60,	0x5,	&pin_gpio2_info,	&pin_regen_info,	&pin_led2_info,	&pin_pwm2_info),
	PALMAS_PINGROUP(gpio3,	GPIO3_CHRG_DET,			PU_PD_OD,	PAD1,	0x80,	0x7,	&pin_gpio3_info,	&pin_chrg_det_info,	शून्य,		शून्य),
	PALMAS_PINGROUP(gpio4,	GPIO4_SYSEN1,			PU_PD_OD,	PAD1,	0x01,	0x0,	&pin_gpio4_info,	&pin_sysen1_info,	शून्य,		शून्य),
	PALMAS_PINGROUP(gpio5,	GPIO5_CLK32KGAUDIO_USB_PSEL,	PU_PD_OD,	PAD2,	0x6,	0x1,	&pin_gpio5_info,	&pin_clk32kgaudio_info,	&pin_usb_psel_info,	शून्य),
	PALMAS_PINGROUP(gpio6,	GPIO6_SYSEN2,			PU_PD_OD,	PAD2,	0x08,	0x3,	&pin_gpio6_info,	&pin_sysen2_info,	शून्य,		शून्य),
	PALMAS_PINGROUP(gpio7,	GPIO7_MSECURE_PWRHOLD,		PU_PD_OD,	PAD2,	0x30,	0x4,	&pin_gpio7_info,	&pin_msecure_info,	&pin_pwrhold_info,	शून्य),
	PALMAS_PINGROUP(vac,	VAC,				PU_PD_OD,	PAD1,	0x02,	0x1,	&pin_vac_info,		&pin_vacok_info,	शून्य,		शून्य),
	PALMAS_PINGROUP(घातergood,	POWERGOOD_USB_PSEL,	PU_PD_OD,	PAD1,	0x01,	0x0,	&pin_घातergood_info,	&pin_usb_psel_info,	शून्य,	शून्य),
	PALMAS_PINGROUP(nreswarm,	NRESWARM,		NONE,		NONE,	0x0,	0x0,	&pin_nreswarm_info,	शून्य,			शून्य,		शून्य),
	PALMAS_PINGROUP(pwrकरोwn,	PWRDOWN,		NONE,		NONE,	0x0,	0x0,	&pin_pwrकरोwn_info,	शून्य,			शून्य,		शून्य),
	PALMAS_PINGROUP(gpadc_start,	GPADC_START,		NONE,		NONE,	0x0,	0x0,	&pin_gpadc_start_info,	शून्य,			शून्य,		शून्य),
	PALMAS_PINGROUP(reset_in,	RESET_IN,		NONE,		NONE,	0x0,	0x0,	&pin_reset_in_info,	शून्य,			शून्य,		शून्य),
	PALMAS_PINGROUP(nsleep,		NSLEEP,			NONE,		NONE,	0x0,	0x0,	&pin_nsleep_info,	शून्य,			शून्य,		शून्य),
	PALMAS_PINGROUP(enable1,	ENABLE1,		NONE,		NONE,	0x0,	0x0,	&pin_enable1_info,	शून्य,			शून्य,		शून्य),
	PALMAS_PINGROUP(enable2,	ENABLE2,		NONE,		NONE,	0x0,	0x0,	&pin_enable2_info,	शून्य,			शून्य,		शून्य),
	PALMAS_PINGROUP(पूर्णांक,		INT,			NONE,		NONE,	0x0,	0x0,	&pin_पूर्णांक_info,		शून्य,			शून्य,		शून्य),
पूर्ण;

अटल स्थिर काष्ठा palmas_pingroup tps80036_pingroups[] = अणु
	PALMAS_PINGROUP(gpio0,	GPIO0_ID,			PU_PD_OD,	PAD1,	0x4,	0x2,	&pin_gpio0_info,	&pin_id_info,		शून्य,		शून्य),
	PALMAS_PINGROUP(gpio1,	GPIO1_VBUS_LED1_PWM1,		PU_PD_OD,	PAD1,	0x18,	0x3,	&pin_gpio1_info,	&pin_vbus_det_info,	&pin_led1_info,	&pin_pwm1_info),
	PALMAS_PINGROUP(gpio2,	GPIO2_REGEN_LED2_PWM2,		PU_PD_OD,	PAD1,	0x60,	0x5,	&pin_gpio2_info,	&pin_regen_info,	&pin_led2_info,	&pin_pwm2_info),
	PALMAS_PINGROUP(gpio3,	GPIO3_CHRG_DET,			PU_PD_OD,	PAD1,	0x80,	0x7,	&pin_gpio3_info,	&pin_chrg_det_info,	शून्य,		शून्य),
	PALMAS_PINGROUP(gpio4,	GPIO4_SYSEN1,			PU_PD_OD,	PAD1,	0x01,	0x0,	&pin_gpio4_info,	&pin_sysen1_info,	शून्य,		शून्य),
	PALMAS_PINGROUP(gpio5,	GPIO5_CLK32KGAUDIO_USB_PSEL,	PU_PD_OD,	PAD2,	0x6,	0x1,	&pin_gpio5_info,	&pin_clk32kgaudio_info,	&pin_usb_psel_info,	शून्य),
	PALMAS_PINGROUP(gpio6,	GPIO6_SYSEN2,			PU_PD_OD,	PAD2,	0x08,	0x3,	&pin_gpio6_info,	&pin_sysen2_info,	शून्य,		शून्य),
	PALMAS_PINGROUP(gpio7,	GPIO7_MSECURE_PWRHOLD,		PU_PD_OD,	PAD2,	0x30,	0x4,	&pin_gpio7_info,	&pin_msecure_info,	&pin_pwrhold_info,	शून्य),
	PALMAS_PINGROUP(gpio8,	GPIO8_SIM1RSTI,			PU_PD_OD,	PAD4,	0x01,	0x0,	&pin_gpio8_info,	&pin_sim1rsti_info,	शून्य,		शून्य),
	PALMAS_PINGROUP(gpio9,	GPIO9_LOW_VBAT,			PU_PD_OD,	PAD4,	0x02,	0x1,	&pin_gpio9_info,	&pin_low_vbat_info,	शून्य,		शून्य),
	PALMAS_PINGROUP(gpio10,	GPIO10_WIRELESS_CHRG1,		PU_PD_OD,	PAD4,	0x04,	0x2,	&pin_gpio10_info,	&pin_wireless_chrg1_info,	शून्य,	शून्य),
	PALMAS_PINGROUP(gpio11,	GPIO11_RCM,			PU_PD_OD,	PAD4,	0x08,	0x3,	&pin_gpio11_info,	&pin_rcm_info,		शून्य,		शून्य),
	PALMAS_PINGROUP(gpio12,	GPIO12_SIM2RSTO,		PU_PD_OD,	PAD4,	0x10,	0x4,	&pin_gpio12_info,	&pin_sim2rsto_info,	शून्य,		शून्य),
	PALMAS_PINGROUP(gpio13,	GPIO13,				NONE,		NONE,	0x00,	0x0,	&pin_gpio13_info,	शून्य,			शून्य,		शून्य),
	PALMAS_PINGROUP(gpio14,	GPIO14,				NONE,		NONE,	0x00,	0x0,	&pin_gpio14_info,	शून्य,			शून्य,		शून्य),
	PALMAS_PINGROUP(gpio15,	GPIO15_SIM2RSTI,		PU_PD_OD,	PAD4,	0x80,	0x7,	&pin_gpio15_info,	&pin_sim2rsti_info,	शून्य,		शून्य),
	PALMAS_PINGROUP(vac,	VAC,				PU_PD_OD,	PAD1,	0x02,	0x1,	&pin_vac_info,		&pin_vacok_info,	शून्य,		शून्य),
	PALMAS_PINGROUP(घातergood,	POWERGOOD_USB_PSEL,	PU_PD_OD,	PAD1,	0x01,	0x0,	&pin_घातergood_info,	&pin_usb_psel_info,	शून्य,	शून्य),
	PALMAS_PINGROUP(nreswarm,	NRESWARM,		NONE,		NONE,	0x0,	0x0,	&pin_nreswarm_info,	शून्य,			शून्य,		शून्य),
	PALMAS_PINGROUP(pwrकरोwn,	PWRDOWN,		NONE,		NONE,	0x0,	0x0,	&pin_pwrकरोwn_info,	शून्य,			शून्य,		शून्य),
	PALMAS_PINGROUP(gpadc_start,	GPADC_START,		NONE,		NONE,	0x0,	0x0,	&pin_gpadc_start_info,	शून्य,			शून्य,		शून्य),
	PALMAS_PINGROUP(reset_in,	RESET_IN,		NONE,		NONE,	0x0,	0x0,	&pin_reset_in_info,	शून्य,			शून्य,		शून्य),
	PALMAS_PINGROUP(nsleep,		NSLEEP,			NONE,		NONE,	0x0,	0x0,	&pin_nsleep_info,	शून्य,			शून्य,		शून्य),
	PALMAS_PINGROUP(enable1,	ENABLE1,		NONE,		NONE,	0x0,	0x0,	&pin_enable1_info,	शून्य,			शून्य,		शून्य),
	PALMAS_PINGROUP(enable2,	ENABLE2,		NONE,		NONE,	0x0,	0x0,	&pin_enable2_info,	शून्य,			शून्य,		शून्य),
	PALMAS_PINGROUP(पूर्णांक,		INT,			NONE,		NONE,	0x0,	0x0,	&pin_पूर्णांक_info,		शून्य,			शून्य,		शून्य),
पूर्ण;

अटल पूर्णांक palmas_pinctrl_get_pin_mux(काष्ठा palmas_pctrl_chip_info *pci)
अणु
	स्थिर काष्ठा palmas_pingroup *g;
	अचिन्हित पूर्णांक val;
	पूर्णांक ret;
	पूर्णांक i;

	क्रम (i = 0; i < pci->num_pin_groups; ++i) अणु
		g = &pci->pin_groups[i];
		अगर (g->mux_reg_base == PALMAS_NONE_BASE) अणु
			pci->pins_current_opt[i] = 0;
			जारी;
		पूर्ण
		ret = palmas_पढ़ो(pci->palmas, g->mux_reg_base,
				g->mux_reg_add, &val);
		अगर (ret < 0) अणु
			dev_err(pci->dev, "mux_reg 0x%02x read failed: %d\n",
					g->mux_reg_add, ret);
			वापस ret;
		पूर्ण
		val &= g->mux_reg_mask;
		pci->pins_current_opt[i] = val >> g->mux_bit_shअगरt;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक palmas_pinctrl_set_dvfs1(काष्ठा palmas_pctrl_chip_info *pci,
		bool enable)
अणु
	पूर्णांक ret;
	पूर्णांक val;

	val = enable ? PALMAS_PRIMARY_SECONDARY_PAD3_DVFS1 : 0;
	ret = palmas_update_bits(pci->palmas, PALMAS_PU_PD_OD_BASE,
			PALMAS_PRIMARY_SECONDARY_PAD3,
			PALMAS_PRIMARY_SECONDARY_PAD3_DVFS1, val);
	अगर (ret < 0)
		dev_err(pci->dev, "SECONDARY_PAD3 update failed %d\n", ret);
	वापस ret;
पूर्ण

अटल पूर्णांक palmas_pinctrl_set_dvfs2(काष्ठा palmas_pctrl_chip_info *pci,
		bool enable)
अणु
	पूर्णांक ret;
	पूर्णांक val;

	val = enable ? PALMAS_PRIMARY_SECONDARY_PAD3_DVFS2 : 0;
	ret = palmas_update_bits(pci->palmas, PALMAS_PU_PD_OD_BASE,
			PALMAS_PRIMARY_SECONDARY_PAD3,
			PALMAS_PRIMARY_SECONDARY_PAD3_DVFS2, val);
	अगर (ret < 0)
		dev_err(pci->dev, "SECONDARY_PAD3 update failed %d\n", ret);
	वापस ret;
पूर्ण

अटल पूर्णांक palmas_pinctrl_get_groups_count(काष्ठा pinctrl_dev *pctldev)
अणु
	काष्ठा palmas_pctrl_chip_info *pci = pinctrl_dev_get_drvdata(pctldev);

	वापस pci->num_pin_groups;
पूर्ण

अटल स्थिर अक्षर *palmas_pinctrl_get_group_name(काष्ठा pinctrl_dev *pctldev,
		अचिन्हित group)
अणु
	काष्ठा palmas_pctrl_chip_info *pci = pinctrl_dev_get_drvdata(pctldev);

	वापस pci->pin_groups[group].name;
पूर्ण

अटल पूर्णांक palmas_pinctrl_get_group_pins(काष्ठा pinctrl_dev *pctldev,
		अचिन्हित group, स्थिर अचिन्हित **pins, अचिन्हित *num_pins)
अणु
	काष्ठा palmas_pctrl_chip_info *pci = pinctrl_dev_get_drvdata(pctldev);

	*pins = pci->pin_groups[group].pins;
	*num_pins = pci->pin_groups[group].npins;
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा pinctrl_ops palmas_pinctrl_ops = अणु
	.get_groups_count = palmas_pinctrl_get_groups_count,
	.get_group_name = palmas_pinctrl_get_group_name,
	.get_group_pins = palmas_pinctrl_get_group_pins,
	.dt_node_to_map = pinconf_generic_dt_node_to_map_pin,
	.dt_मुक्त_map = pinctrl_utils_मुक्त_map,
पूर्ण;

अटल पूर्णांक palmas_pinctrl_get_funcs_count(काष्ठा pinctrl_dev *pctldev)
अणु
	काष्ठा palmas_pctrl_chip_info *pci = pinctrl_dev_get_drvdata(pctldev);

	वापस pci->num_functions;
पूर्ण

अटल स्थिर अक्षर *palmas_pinctrl_get_func_name(काष्ठा pinctrl_dev *pctldev,
			अचिन्हित function)
अणु
	काष्ठा palmas_pctrl_chip_info *pci = pinctrl_dev_get_drvdata(pctldev);

	वापस pci->functions[function].name;
पूर्ण

अटल पूर्णांक palmas_pinctrl_get_func_groups(काष्ठा pinctrl_dev *pctldev,
		अचिन्हित function, स्थिर अक्षर * स्थिर **groups,
		अचिन्हित * स्थिर num_groups)
अणु
	काष्ठा palmas_pctrl_chip_info *pci = pinctrl_dev_get_drvdata(pctldev);

	*groups = pci->functions[function].groups;
	*num_groups = pci->functions[function].ngroups;
	वापस 0;
पूर्ण

अटल पूर्णांक palmas_pinctrl_set_mux(काष्ठा pinctrl_dev *pctldev,
		अचिन्हित function,
		अचिन्हित group)
अणु
	काष्ठा palmas_pctrl_chip_info *pci = pinctrl_dev_get_drvdata(pctldev);
	स्थिर काष्ठा palmas_pingroup *g;
	पूर्णांक i;
	पूर्णांक ret;

	g = &pci->pin_groups[group];

	/* If direct option is provided here */
	अगर (function <= PALMAS_PINMUX_OPTION3) अणु
		अगर (!g->opt[function]) अणु
			dev_err(pci->dev, "Pin %s does not support option %d\n",
				g->name, function);
			वापस -EINVAL;
		पूर्ण
		i = function;
	पूर्ण अन्यथा अणु
		क्रम (i = 0; i < ARRAY_SIZE(g->opt); i++) अणु
			अगर (!g->opt[i])
				जारी;
			अगर (g->opt[i]->mux_opt == function)
				अवरोध;
		पूर्ण
		अगर (WARN_ON(i == ARRAY_SIZE(g->opt))) अणु
			dev_err(pci->dev, "Pin %s does not support option %d\n",
				g->name, function);
			वापस -EINVAL;
		पूर्ण
	पूर्ण

	अगर (g->mux_reg_base == PALMAS_NONE_BASE) अणु
		अगर (WARN_ON(i != 0))
			वापस -EINVAL;
		वापस 0;
	पूर्ण

	dev_dbg(pci->dev, "%s(): Base0x%02x:0x%02x:0x%02x:0x%02x\n",
			__func__, g->mux_reg_base, g->mux_reg_add,
			g->mux_reg_mask, i << g->mux_bit_shअगरt);

	ret = palmas_update_bits(pci->palmas, g->mux_reg_base, g->mux_reg_add,
			g->mux_reg_mask, i << g->mux_bit_shअगरt);
	अगर (ret < 0) अणु
		dev_err(pci->dev, "Reg 0x%02x update failed: %d\n",
				g->mux_reg_add, ret);
		वापस ret;
	पूर्ण
	pci->pins_current_opt[group] = i;
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा pinmux_ops palmas_pinmux_ops = अणु
	.get_functions_count = palmas_pinctrl_get_funcs_count,
	.get_function_name = palmas_pinctrl_get_func_name,
	.get_function_groups = palmas_pinctrl_get_func_groups,
	.set_mux = palmas_pinctrl_set_mux,
पूर्ण;

अटल पूर्णांक palmas_pinconf_get(काष्ठा pinctrl_dev *pctldev,
			अचिन्हित pin, अचिन्हित दीर्घ *config)
अणु
	काष्ठा palmas_pctrl_chip_info *pci = pinctrl_dev_get_drvdata(pctldev);
	क्रमागत pin_config_param param = pinconf_to_config_param(*config);
	स्थिर काष्ठा palmas_pingroup *g;
	स्थिर काष्ठा palmas_pin_info *opt;
	अचिन्हित पूर्णांक val;
	पूर्णांक ret;
	पूर्णांक base, add;
	पूर्णांक rval;
	पूर्णांक arg;
	पूर्णांक group_nr;

	क्रम (group_nr = 0; group_nr < pci->num_pin_groups; ++group_nr) अणु
		अगर (pci->pin_groups[group_nr].pins[0] == pin)
			अवरोध;
	पूर्ण

	अगर (group_nr == pci->num_pin_groups) अणु
		dev_err(pci->dev,
			"Pinconf is not supported for pin-id %d\n", pin);
		वापस -ENOTSUPP;
	पूर्ण

	g = &pci->pin_groups[group_nr];
	opt = g->opt[pci->pins_current_opt[group_nr]];
	अगर (!opt) अणु
		dev_err(pci->dev,
			"Pinconf is not supported for pin %s\n", g->name);
		वापस -ENOTSUPP;
	पूर्ण

	चयन (param) अणु
	हाल PIN_CONFIG_BIAS_DISABLE:
	हाल PIN_CONFIG_BIAS_PULL_UP:
	हाल PIN_CONFIG_BIAS_PULL_DOWN:
		अगर (!opt->pud_info) अणु
			dev_err(pci->dev,
				"PULL control not supported for pin %s\n",
				g->name);
			वापस -ENOTSUPP;
		पूर्ण
		base = opt->pud_info->pullup_dn_reg_base;
		add = opt->pud_info->pullup_dn_reg_add;
		ret = palmas_पढ़ो(pci->palmas, base, add, &val);
		अगर (ret < 0) अणु
			dev_err(pci->dev, "Reg 0x%02x read failed: %d\n",
				add, ret);
			वापस ret;
		पूर्ण

		rval = val & opt->pud_info->pullup_dn_mask;
		arg = 0;
		अगर ((opt->pud_info->normal_val >= 0) &&
				(opt->pud_info->normal_val == rval) &&
				(param == PIN_CONFIG_BIAS_DISABLE))
			arg = 1;
		अन्यथा अगर ((opt->pud_info->pull_up_val >= 0) &&
				(opt->pud_info->pull_up_val == rval) &&
				(param == PIN_CONFIG_BIAS_PULL_UP))
			arg = 1;
		अन्यथा अगर ((opt->pud_info->pull_dn_val >= 0) &&
				(opt->pud_info->pull_dn_val == rval) &&
				(param == PIN_CONFIG_BIAS_PULL_DOWN))
			arg = 1;
		अवरोध;

	हाल PIN_CONFIG_DRIVE_OPEN_DRAIN:
		अगर (!opt->od_info) अणु
			dev_err(pci->dev,
				"OD control not supported for pin %s\n",
				g->name);
			वापस -ENOTSUPP;
		पूर्ण
		base = opt->od_info->od_reg_base;
		add = opt->od_info->od_reg_add;
		ret = palmas_पढ़ो(pci->palmas, base, add, &val);
		अगर (ret < 0) अणु
			dev_err(pci->dev, "Reg 0x%02x read failed: %d\n",
				add, ret);
			वापस ret;
		पूर्ण
		rval = val & opt->od_info->od_mask;
		arg = -1;
		अगर ((opt->od_info->od_disable >= 0) &&
				(opt->od_info->od_disable == rval))
			arg = 0;
		अन्यथा अगर ((opt->od_info->od_enable >= 0) &&
					(opt->od_info->od_enable == rval))
			arg = 1;
		अगर (arg < 0) अणु
			dev_err(pci->dev,
				"OD control not supported for pin %s\n",
				g->name);
			वापस -ENOTSUPP;
		पूर्ण
		अवरोध;

	शेष:
		dev_err(pci->dev, "Properties not supported\n");
		वापस -ENOTSUPP;
	पूर्ण

	*config = pinconf_to_config_packed(param, (u16)arg);
	वापस 0;
पूर्ण

अटल पूर्णांक palmas_pinconf_set(काष्ठा pinctrl_dev *pctldev,
			अचिन्हित pin, अचिन्हित दीर्घ *configs,
			अचिन्हित num_configs)
अणु
	काष्ठा palmas_pctrl_chip_info *pci = pinctrl_dev_get_drvdata(pctldev);
	क्रमागत pin_config_param param;
	u32 param_val;
	स्थिर काष्ठा palmas_pingroup *g;
	स्थिर काष्ठा palmas_pin_info *opt;
	पूर्णांक ret;
	पूर्णांक base, add, mask;
	पूर्णांक rval;
	पूर्णांक group_nr;
	पूर्णांक i;

	क्रम (group_nr = 0; group_nr < pci->num_pin_groups; ++group_nr) अणु
		अगर (pci->pin_groups[group_nr].pins[0] == pin)
			अवरोध;
	पूर्ण

	अगर (group_nr == pci->num_pin_groups) अणु
		dev_err(pci->dev,
			"Pinconf is not supported for pin-id %d\n", pin);
		वापस -ENOTSUPP;
	पूर्ण

	g = &pci->pin_groups[group_nr];
	opt = g->opt[pci->pins_current_opt[group_nr]];
	अगर (!opt) अणु
		dev_err(pci->dev,
			"Pinconf is not supported for pin %s\n", g->name);
		वापस -ENOTSUPP;
	पूर्ण

	क्रम (i = 0; i < num_configs; i++) अणु
		param = pinconf_to_config_param(configs[i]);
		param_val = pinconf_to_config_argument(configs[i]);

		चयन (param) अणु
		हाल PIN_CONFIG_BIAS_DISABLE:
		हाल PIN_CONFIG_BIAS_PULL_UP:
		हाल PIN_CONFIG_BIAS_PULL_DOWN:
			अगर (!opt->pud_info) अणु
				dev_err(pci->dev,
					"PULL control not supported for pin %s\n",
					g->name);
				वापस -ENOTSUPP;
			पूर्ण
			base = opt->pud_info->pullup_dn_reg_base;
			add = opt->pud_info->pullup_dn_reg_add;
			mask = opt->pud_info->pullup_dn_mask;

			अगर (param == PIN_CONFIG_BIAS_DISABLE)
				rval = opt->pud_info->normal_val;
			अन्यथा अगर (param == PIN_CONFIG_BIAS_PULL_UP)
				rval = opt->pud_info->pull_up_val;
			अन्यथा
				rval = opt->pud_info->pull_dn_val;

			अगर (rval < 0) अणु
				dev_err(pci->dev,
					"PULL control not supported for pin %s\n",
					g->name);
				वापस -ENOTSUPP;
			पूर्ण
			अवरोध;

		हाल PIN_CONFIG_DRIVE_OPEN_DRAIN:
			अगर (!opt->od_info) अणु
				dev_err(pci->dev,
					"OD control not supported for pin %s\n",
					g->name);
				वापस -ENOTSUPP;
			पूर्ण
			base = opt->od_info->od_reg_base;
			add = opt->od_info->od_reg_add;
			mask = opt->od_info->od_mask;
			अगर (param_val == 0)
				rval = opt->od_info->od_disable;
			अन्यथा
				rval = opt->od_info->od_enable;
			अगर (rval < 0) अणु
				dev_err(pci->dev,
					"OD control not supported for pin %s\n",
					g->name);
				वापस -ENOTSUPP;
			पूर्ण
			अवरोध;
		शेष:
			dev_err(pci->dev, "Properties not supported\n");
			वापस -ENOTSUPP;
		पूर्ण

		dev_dbg(pci->dev, "%s(): Add0x%02x:0x%02x:0x%02x:0x%02x\n",
				__func__, base, add, mask, rval);
		ret = palmas_update_bits(pci->palmas, base, add, mask, rval);
		अगर (ret < 0) अणु
			dev_err(pci->dev, "Reg 0x%02x update failed: %d\n",
				add, ret);
			वापस ret;
		पूर्ण
	पूर्ण /* क्रम each config */

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा pinconf_ops palmas_pinconf_ops = अणु
	.pin_config_get = palmas_pinconf_get,
	.pin_config_set = palmas_pinconf_set,
पूर्ण;

अटल काष्ठा pinctrl_desc palmas_pinctrl_desc = अणु
	.pctlops = &palmas_pinctrl_ops,
	.pmxops = &palmas_pinmux_ops,
	.confops = &palmas_pinconf_ops,
	.owner = THIS_MODULE,
पूर्ण;

काष्ठा palmas_pinctrl_data अणु
	स्थिर काष्ठा palmas_pingroup *pin_groups;
	पूर्णांक num_pin_groups;
पूर्ण;

अटल काष्ठा palmas_pinctrl_data tps65913_pinctrl_data = अणु
	.pin_groups = tps65913_pingroups,
	.num_pin_groups = ARRAY_SIZE(tps65913_pingroups),
पूर्ण;

अटल काष्ठा palmas_pinctrl_data tps80036_pinctrl_data = अणु
	.pin_groups = tps80036_pingroups,
	.num_pin_groups = ARRAY_SIZE(tps80036_pingroups),
पूर्ण;

अटल स्थिर काष्ठा of_device_id palmas_pinctrl_of_match[] = अणु
	अणु .compatible = "ti,palmas-pinctrl", .data = &tps65913_pinctrl_dataपूर्ण,
	अणु .compatible = "ti,tps65913-pinctrl", .data = &tps65913_pinctrl_dataपूर्ण,
	अणु .compatible = "ti,tps80036-pinctrl", .data = &tps80036_pinctrl_dataपूर्ण,
	अणु पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, palmas_pinctrl_of_match);

अटल पूर्णांक palmas_pinctrl_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा palmas_pctrl_chip_info *pci;
	स्थिर काष्ठा palmas_pinctrl_data *pinctrl_data = &tps65913_pinctrl_data;
	पूर्णांक ret;
	bool enable_dvfs1 = false;
	bool enable_dvfs2 = false;

	अगर (pdev->dev.of_node) अणु
		pinctrl_data = of_device_get_match_data(&pdev->dev);
		enable_dvfs1 = of_property_पढ़ो_bool(pdev->dev.of_node,
					"ti,palmas-enable-dvfs1");
		enable_dvfs2 = of_property_पढ़ो_bool(pdev->dev.of_node,
					"ti,palmas-enable-dvfs2");
	पूर्ण

	pci = devm_kzalloc(&pdev->dev, माप(*pci), GFP_KERNEL);
	अगर (!pci)
		वापस -ENOMEM;

	pci->dev = &pdev->dev;
	pci->palmas = dev_get_drvdata(pdev->dev.parent);

	pci->pins = palmas_pins_desc;
	pci->num_pins = ARRAY_SIZE(palmas_pins_desc);
	pci->functions = palmas_pin_function;
	pci->num_functions = ARRAY_SIZE(palmas_pin_function);
	pci->pin_groups = pinctrl_data->pin_groups;
	pci->num_pin_groups = pinctrl_data->num_pin_groups;

	platक्रमm_set_drvdata(pdev, pci);

	palmas_pinctrl_set_dvfs1(pci, enable_dvfs1);
	palmas_pinctrl_set_dvfs2(pci, enable_dvfs2);
	ret = palmas_pinctrl_get_pin_mux(pci);
	अगर (ret < 0) अणु
		dev_err(&pdev->dev,
			"Reading pinctrol option register failed: %d\n", ret);
		वापस ret;
	पूर्ण

	palmas_pinctrl_desc.name = dev_name(&pdev->dev);
	palmas_pinctrl_desc.pins = palmas_pins_desc;
	palmas_pinctrl_desc.npins = ARRAY_SIZE(palmas_pins_desc);
	pci->pctl = devm_pinctrl_रेजिस्टर(&pdev->dev, &palmas_pinctrl_desc,
					  pci);
	अगर (IS_ERR(pci->pctl)) अणु
		dev_err(&pdev->dev, "Couldn't register pinctrl driver\n");
		वापस PTR_ERR(pci->pctl);
	पूर्ण
	वापस 0;
पूर्ण

अटल काष्ठा platक्रमm_driver palmas_pinctrl_driver = अणु
	.driver = अणु
		.name = "palmas-pinctrl",
		.of_match_table = palmas_pinctrl_of_match,
	पूर्ण,
	.probe = palmas_pinctrl_probe,
पूर्ण;

module_platक्रमm_driver(palmas_pinctrl_driver);

MODULE_DESCRIPTION("Palmas pin control driver");
MODULE_AUTHOR("Laxman Dewangan<ldewangan@nvidia.com>");
MODULE_ALIAS("platform:palmas-pinctrl");
MODULE_LICENSE("GPL v2");
