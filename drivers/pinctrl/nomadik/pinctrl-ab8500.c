<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (C) ST-Ericsson SA 2012
 *
 * Author: Patrice Chotard <patrice.chotard@stericsson.com> क्रम ST-Ericsson.
 */

#समावेश <linux/kernel.h>
#समावेश <linux/gpio/driver.h>
#समावेश <linux/pinctrl/pinctrl.h>
#समावेश <linux/mfd/abx500/ab8500.h>
#समावेश "pinctrl-abx500.h"

/* All the pins that can be used क्रम GPIO and some other functions */
#घोषणा ABX500_GPIO(offset)		(offset)

#घोषणा AB8500_PIN_T10		ABX500_GPIO(1)
#घोषणा AB8500_PIN_T9		ABX500_GPIO(2)
#घोषणा AB8500_PIN_U9		ABX500_GPIO(3)
#घोषणा AB8500_PIN_W2		ABX500_GPIO(4)
/* hole */
#घोषणा AB8500_PIN_Y18		ABX500_GPIO(6)
#घोषणा AB8500_PIN_AA20		ABX500_GPIO(7)
#घोषणा AB8500_PIN_W18		ABX500_GPIO(8)
#घोषणा AB8500_PIN_AA19		ABX500_GPIO(9)
#घोषणा AB8500_PIN_U17		ABX500_GPIO(10)
#घोषणा AB8500_PIN_AA18		ABX500_GPIO(11)
#घोषणा AB8500_PIN_U16		ABX500_GPIO(12)
#घोषणा AB8500_PIN_W17		ABX500_GPIO(13)
#घोषणा AB8500_PIN_F14		ABX500_GPIO(14)
#घोषणा AB8500_PIN_B17		ABX500_GPIO(15)
#घोषणा AB8500_PIN_F15		ABX500_GPIO(16)
#घोषणा AB8500_PIN_P5		ABX500_GPIO(17)
#घोषणा AB8500_PIN_R5		ABX500_GPIO(18)
#घोषणा AB8500_PIN_U5		ABX500_GPIO(19)
#घोषणा AB8500_PIN_T5		ABX500_GPIO(20)
#घोषणा AB8500_PIN_H19		ABX500_GPIO(21)
#घोषणा AB8500_PIN_G20		ABX500_GPIO(22)
#घोषणा AB8500_PIN_G19		ABX500_GPIO(23)
#घोषणा AB8500_PIN_T14		ABX500_GPIO(24)
#घोषणा AB8500_PIN_R16		ABX500_GPIO(25)
#घोषणा AB8500_PIN_M16		ABX500_GPIO(26)
#घोषणा AB8500_PIN_J6		ABX500_GPIO(27)
#घोषणा AB8500_PIN_K6		ABX500_GPIO(28)
#घोषणा AB8500_PIN_G6		ABX500_GPIO(29)
#घोषणा AB8500_PIN_H6		ABX500_GPIO(30)
#घोषणा AB8500_PIN_F5		ABX500_GPIO(31)
#घोषणा AB8500_PIN_G5		ABX500_GPIO(32)
/* hole */
#घोषणा AB8500_PIN_R17		ABX500_GPIO(34)
#घोषणा AB8500_PIN_W15		ABX500_GPIO(35)
#घोषणा AB8500_PIN_A17		ABX500_GPIO(36)
#घोषणा AB8500_PIN_E15		ABX500_GPIO(37)
#घोषणा AB8500_PIN_C17		ABX500_GPIO(38)
#घोषणा AB8500_PIN_E16		ABX500_GPIO(39)
#घोषणा AB8500_PIN_T19		ABX500_GPIO(40)
#घोषणा AB8500_PIN_U19		ABX500_GPIO(41)
#घोषणा AB8500_PIN_U2		ABX500_GPIO(42)

/* indicates the highest GPIO number */
#घोषणा AB8500_GPIO_MAX_NUMBER	42

/*
 * The names of the pins are denoted by GPIO number and ball name, even
 * though they can be used क्रम other things than GPIO, this is the first
 * column in the table of the data sheet and often used on schematics and
 * such.
 */
अटल स्थिर काष्ठा pinctrl_pin_desc ab8500_pins[] = अणु
	PINCTRL_PIN(AB8500_PIN_T10, "GPIO1_T10"),
	PINCTRL_PIN(AB8500_PIN_T9, "GPIO2_T9"),
	PINCTRL_PIN(AB8500_PIN_U9, "GPIO3_U9"),
	PINCTRL_PIN(AB8500_PIN_W2, "GPIO4_W2"),
	/* hole */
	PINCTRL_PIN(AB8500_PIN_Y18, "GPIO6_Y18"),
	PINCTRL_PIN(AB8500_PIN_AA20, "GPIO7_AA20"),
	PINCTRL_PIN(AB8500_PIN_W18, "GPIO8_W18"),
	PINCTRL_PIN(AB8500_PIN_AA19, "GPIO9_AA19"),
	PINCTRL_PIN(AB8500_PIN_U17, "GPIO10_U17"),
	PINCTRL_PIN(AB8500_PIN_AA18, "GPIO11_AA18"),
	PINCTRL_PIN(AB8500_PIN_U16, "GPIO12_U16"),
	PINCTRL_PIN(AB8500_PIN_W17, "GPIO13_W17"),
	PINCTRL_PIN(AB8500_PIN_F14, "GPIO14_F14"),
	PINCTRL_PIN(AB8500_PIN_B17, "GPIO15_B17"),
	PINCTRL_PIN(AB8500_PIN_F15, "GPIO16_F15"),
	PINCTRL_PIN(AB8500_PIN_P5, "GPIO17_P5"),
	PINCTRL_PIN(AB8500_PIN_R5, "GPIO18_R5"),
	PINCTRL_PIN(AB8500_PIN_U5, "GPIO19_U5"),
	PINCTRL_PIN(AB8500_PIN_T5, "GPIO20_T5"),
	PINCTRL_PIN(AB8500_PIN_H19, "GPIO21_H19"),
	PINCTRL_PIN(AB8500_PIN_G20, "GPIO22_G20"),
	PINCTRL_PIN(AB8500_PIN_G19, "GPIO23_G19"),
	PINCTRL_PIN(AB8500_PIN_T14, "GPIO24_T14"),
	PINCTRL_PIN(AB8500_PIN_R16, "GPIO25_R16"),
	PINCTRL_PIN(AB8500_PIN_M16, "GPIO26_M16"),
	PINCTRL_PIN(AB8500_PIN_J6, "GPIO27_J6"),
	PINCTRL_PIN(AB8500_PIN_K6, "GPIO28_K6"),
	PINCTRL_PIN(AB8500_PIN_G6, "GPIO29_G6"),
	PINCTRL_PIN(AB8500_PIN_H6, "GPIO30_H6"),
	PINCTRL_PIN(AB8500_PIN_F5, "GPIO31_F5"),
	PINCTRL_PIN(AB8500_PIN_G5, "GPIO32_G5"),
	/* hole */
	PINCTRL_PIN(AB8500_PIN_R17, "GPIO34_R17"),
	PINCTRL_PIN(AB8500_PIN_W15, "GPIO35_W15"),
	PINCTRL_PIN(AB8500_PIN_A17, "GPIO36_A17"),
	PINCTRL_PIN(AB8500_PIN_E15, "GPIO37_E15"),
	PINCTRL_PIN(AB8500_PIN_C17, "GPIO38_C17"),
	PINCTRL_PIN(AB8500_PIN_E16, "GPIO39_E16"),
	PINCTRL_PIN(AB8500_PIN_T19, "GPIO40_T19"),
	PINCTRL_PIN(AB8500_PIN_U19, "GPIO41_U19"),
	PINCTRL_PIN(AB8500_PIN_U2, "GPIO42_U2"),
पूर्ण;

/*
 * Maps local GPIO offsets to local pin numbers
 */
अटल स्थिर काष्ठा abx500_pinrange ab8500_pinranges[] = अणु
	ABX500_PINRANGE(1, 4, ABX500_ALT_A),
	ABX500_PINRANGE(6, 4, ABX500_ALT_A),
	ABX500_PINRANGE(10, 4, ABX500_DEFAULT),
	ABX500_PINRANGE(14, 12, ABX500_ALT_A),
	ABX500_PINRANGE(26, 1, ABX500_DEFAULT),
	ABX500_PINRANGE(27, 6, ABX500_ALT_A),
	ABX500_PINRANGE(34, 1, ABX500_ALT_A),
	ABX500_PINRANGE(35, 1, ABX500_DEFAULT),
	ABX500_PINRANGE(36, 7, ABX500_ALT_A),
पूर्ण;

/*
 * Read the pin group names like this:
 * sysclkreq2_d_1 = first groups of pins क्रम sysclkreq2 on शेष function
 *
 * The groups are arranged as sets per altfunction column, so we can
 * mux in one group at a समय by selecting the same altfunction क्रम them
 * all. When functions require pins on dअगरferent altfunctions, you need
 * to combine several groups.
 */

/* शेष column */
अटल स्थिर अचिन्हित sysclkreq2_d_1_pins[] = अणु AB8500_PIN_T10 पूर्ण;
अटल स्थिर अचिन्हित sysclkreq3_d_1_pins[] = अणु AB8500_PIN_T9 पूर्ण;
अटल स्थिर अचिन्हित sysclkreq4_d_1_pins[] = अणु AB8500_PIN_U9 पूर्ण;
अटल स्थिर अचिन्हित sysclkreq6_d_1_pins[] = अणु AB8500_PIN_W2 पूर्ण;
अटल स्थिर अचिन्हित ycbcr0123_d_1_pins[] = अणु AB8500_PIN_Y18, AB8500_PIN_AA20,
					AB8500_PIN_W18, AB8500_PIN_AA19पूर्ण;
अटल स्थिर अचिन्हित gpio10_d_1_pins[] = अणु AB8500_PIN_U17 पूर्ण;
अटल स्थिर अचिन्हित gpio11_d_1_pins[] = अणु AB8500_PIN_AA18 पूर्ण;
अटल स्थिर अचिन्हित gpio12_d_1_pins[] = अणु AB8500_PIN_U16 पूर्ण;
अटल स्थिर अचिन्हित gpio13_d_1_pins[] = अणु AB8500_PIN_W17 पूर्ण;
अटल स्थिर अचिन्हित pwmout1_d_1_pins[] = अणु AB8500_PIN_F14 पूर्ण;
अटल स्थिर अचिन्हित pwmout2_d_1_pins[] = अणु AB8500_PIN_B17 पूर्ण;
अटल स्थिर अचिन्हित pwmout3_d_1_pins[] = अणु AB8500_PIN_F15 पूर्ण;

/* audio data पूर्णांकerface 1*/
अटल स्थिर अचिन्हित adi1_d_1_pins[] = अणु AB8500_PIN_P5, AB8500_PIN_R5,
					AB8500_PIN_U5, AB8500_PIN_T5 पूर्ण;
/* USBUICC */
अटल स्थिर अचिन्हित usbuicc_d_1_pins[] = अणु AB8500_PIN_H19, AB8500_PIN_G20,
					AB8500_PIN_G19 पूर्ण;
अटल स्थिर अचिन्हित sysclkreq7_d_1_pins[] = अणु AB8500_PIN_T14 पूर्ण;
अटल स्थिर अचिन्हित sysclkreq8_d_1_pins[] = अणु AB8500_PIN_R16 पूर्ण;
अटल स्थिर अचिन्हित gpio26_d_1_pins[] = अणु AB8500_PIN_M16 पूर्ण;
/* Digital microphone 1 and 2 */
अटल स्थिर अचिन्हित dmic12_d_1_pins[] = अणु AB8500_PIN_J6, AB8500_PIN_K6 पूर्ण;
/* Digital microphone 3 and 4 */
अटल स्थिर अचिन्हित dmic34_d_1_pins[] = अणु AB8500_PIN_G6, AB8500_PIN_H6 पूर्ण;
/* Digital microphone 5 and 6 */
अटल स्थिर अचिन्हित dmic56_d_1_pins[] = अणु AB8500_PIN_F5, AB8500_PIN_G5 पूर्ण;
अटल स्थिर अचिन्हित extcpena_d_1_pins[] = अणु AB8500_PIN_R17 पूर्ण;
अटल स्थिर अचिन्हित gpio35_d_1_pins[] = अणु AB8500_PIN_W15 पूर्ण;
/* APE SPI */
अटल स्थिर अचिन्हित apespi_d_1_pins[] = अणु AB8500_PIN_A17, AB8500_PIN_E15,
					AB8500_PIN_C17, AB8500_PIN_E16पूर्ण;
/* modem SDA/SCL */
अटल स्थिर अचिन्हित modsclsda_d_1_pins[] = अणु AB8500_PIN_T19, AB8500_PIN_U19 पूर्ण;
अटल स्थिर अचिन्हित sysclkreq5_d_1_pins[] = अणु AB8500_PIN_U2 पूर्ण;

/* Altfunction A column */
अटल स्थिर अचिन्हित gpio1_a_1_pins[] = अणु AB8500_PIN_T10 पूर्ण;
अटल स्थिर अचिन्हित gpio2_a_1_pins[] = अणु AB8500_PIN_T9 पूर्ण;
अटल स्थिर अचिन्हित gpio3_a_1_pins[] = अणु AB8500_PIN_U9 पूर्ण;
अटल स्थिर अचिन्हित gpio4_a_1_pins[] = अणु AB8500_PIN_W2 पूर्ण;
अटल स्थिर अचिन्हित gpio6_a_1_pins[] = अणु AB8500_PIN_Y18 पूर्ण;
अटल स्थिर अचिन्हित gpio7_a_1_pins[] = अणु AB8500_PIN_AA20 पूर्ण;
अटल स्थिर अचिन्हित gpio8_a_1_pins[] = अणु AB8500_PIN_W18 पूर्ण;
अटल स्थिर अचिन्हित gpio9_a_1_pins[] = अणु AB8500_PIN_AA19 पूर्ण;
/* YCbCr4 YCbCr5 YCbCr6 YCbCr7*/
अटल स्थिर अचिन्हित ycbcr4567_a_1_pins[] = अणु AB8500_PIN_U17, AB8500_PIN_AA18,
					AB8500_PIN_U16, AB8500_PIN_W17पूर्ण;
अटल स्थिर अचिन्हित gpio14_a_1_pins[] = अणु AB8500_PIN_F14 पूर्ण;
अटल स्थिर अचिन्हित gpio15_a_1_pins[] = अणु AB8500_PIN_B17 पूर्ण;
अटल स्थिर अचिन्हित gpio16_a_1_pins[] = अणु AB8500_PIN_F15 पूर्ण;
अटल स्थिर अचिन्हित gpio17_a_1_pins[] = अणु AB8500_PIN_P5 पूर्ण;
अटल स्थिर अचिन्हित gpio18_a_1_pins[] = अणु AB8500_PIN_R5 पूर्ण;
अटल स्थिर अचिन्हित gpio19_a_1_pins[] = अणु AB8500_PIN_U5 पूर्ण;
अटल स्थिर अचिन्हित gpio20_a_1_pins[] = अणु AB8500_PIN_T5 पूर्ण;
अटल स्थिर अचिन्हित gpio21_a_1_pins[] = अणु AB8500_PIN_H19 पूर्ण;
अटल स्थिर अचिन्हित gpio22_a_1_pins[] = अणु AB8500_PIN_G20 पूर्ण;
अटल स्थिर अचिन्हित gpio23_a_1_pins[] = अणु AB8500_PIN_G19 पूर्ण;
अटल स्थिर अचिन्हित gpio24_a_1_pins[] = अणु AB8500_PIN_T14 पूर्ण;
अटल स्थिर अचिन्हित gpio25_a_1_pins[] = अणु AB8500_PIN_R16 पूर्ण;
अटल स्थिर अचिन्हित gpio27_a_1_pins[] = अणु AB8500_PIN_J6 पूर्ण;
अटल स्थिर अचिन्हित gpio28_a_1_pins[] = अणु AB8500_PIN_K6 पूर्ण;
अटल स्थिर अचिन्हित gpio29_a_1_pins[] = अणु AB8500_PIN_G6 पूर्ण;
अटल स्थिर अचिन्हित gpio30_a_1_pins[] = अणु AB8500_PIN_H6 पूर्ण;
अटल स्थिर अचिन्हित gpio31_a_1_pins[] = अणु AB8500_PIN_F5 पूर्ण;
अटल स्थिर अचिन्हित gpio32_a_1_pins[] = अणु AB8500_PIN_G5 पूर्ण;
अटल स्थिर अचिन्हित gpio34_a_1_pins[] = अणु AB8500_PIN_R17 पूर्ण;
अटल स्थिर अचिन्हित gpio36_a_1_pins[] = अणु AB8500_PIN_A17 पूर्ण;
अटल स्थिर अचिन्हित gpio37_a_1_pins[] = अणु AB8500_PIN_E15 पूर्ण;
अटल स्थिर अचिन्हित gpio38_a_1_pins[] = अणु AB8500_PIN_C17 पूर्ण;
अटल स्थिर अचिन्हित gpio39_a_1_pins[] = अणु AB8500_PIN_E16 पूर्ण;
अटल स्थिर अचिन्हित gpio40_a_1_pins[] = अणु AB8500_PIN_T19 पूर्ण;
अटल स्थिर अचिन्हित gpio41_a_1_pins[] = अणु AB8500_PIN_U19 पूर्ण;
अटल स्थिर अचिन्हित gpio42_a_1_pins[] = अणु AB8500_PIN_U2 पूर्ण;

/* Altfunction B colum */
अटल स्थिर अचिन्हित hiqclkena_b_1_pins[] = अणु AB8500_PIN_U17 पूर्ण;
अटल स्थिर अचिन्हित usbuiccpd_b_1_pins[] = अणु AB8500_PIN_AA18 पूर्ण;
अटल स्थिर अचिन्हित i2ctrig1_b_1_pins[] = अणु AB8500_PIN_U16 पूर्ण;
अटल स्थिर अचिन्हित i2ctrig2_b_1_pins[] = अणु AB8500_PIN_W17 पूर्ण;

/* Altfunction C column */
अटल स्थिर अचिन्हित usbvdat_c_1_pins[] = अणु AB8500_PIN_W17 पूर्ण;


#घोषणा AB8500_PIN_GROUP(a, b) अणु .name = #a, .pins = a##_pins,		\
			.npins = ARRAY_SIZE(a##_pins), .altsetting = b पूर्ण

अटल स्थिर काष्ठा abx500_pingroup ab8500_groups[] = अणु
	/* शेष column */
	AB8500_PIN_GROUP(sysclkreq2_d_1, ABX500_DEFAULT),
	AB8500_PIN_GROUP(sysclkreq3_d_1, ABX500_DEFAULT),
	AB8500_PIN_GROUP(sysclkreq4_d_1, ABX500_DEFAULT),
	AB8500_PIN_GROUP(sysclkreq6_d_1, ABX500_DEFAULT),
	AB8500_PIN_GROUP(ycbcr0123_d_1, ABX500_DEFAULT),
	AB8500_PIN_GROUP(gpio10_d_1, ABX500_DEFAULT),
	AB8500_PIN_GROUP(gpio11_d_1, ABX500_DEFAULT),
	AB8500_PIN_GROUP(gpio12_d_1, ABX500_DEFAULT),
	AB8500_PIN_GROUP(gpio13_d_1, ABX500_DEFAULT),
	AB8500_PIN_GROUP(pwmout1_d_1, ABX500_DEFAULT),
	AB8500_PIN_GROUP(pwmout2_d_1, ABX500_DEFAULT),
	AB8500_PIN_GROUP(pwmout3_d_1, ABX500_DEFAULT),
	AB8500_PIN_GROUP(adi1_d_1, ABX500_DEFAULT),
	AB8500_PIN_GROUP(usbuicc_d_1, ABX500_DEFAULT),
	AB8500_PIN_GROUP(sysclkreq7_d_1, ABX500_DEFAULT),
	AB8500_PIN_GROUP(sysclkreq8_d_1, ABX500_DEFAULT),
	AB8500_PIN_GROUP(gpio26_d_1, ABX500_DEFAULT),
	AB8500_PIN_GROUP(dmic12_d_1, ABX500_DEFAULT),
	AB8500_PIN_GROUP(dmic34_d_1, ABX500_DEFAULT),
	AB8500_PIN_GROUP(dmic56_d_1, ABX500_DEFAULT),
	AB8500_PIN_GROUP(extcpena_d_1, ABX500_DEFAULT),
	AB8500_PIN_GROUP(gpio35_d_1, ABX500_DEFAULT),
	AB8500_PIN_GROUP(apespi_d_1, ABX500_DEFAULT),
	AB8500_PIN_GROUP(modsclsda_d_1, ABX500_DEFAULT),
	AB8500_PIN_GROUP(sysclkreq5_d_1, ABX500_DEFAULT),
	/* Altfunction A column */
	AB8500_PIN_GROUP(gpio1_a_1, ABX500_ALT_A),
	AB8500_PIN_GROUP(gpio2_a_1, ABX500_ALT_A),
	AB8500_PIN_GROUP(gpio3_a_1, ABX500_ALT_A),
	AB8500_PIN_GROUP(gpio4_a_1, ABX500_ALT_A),
	AB8500_PIN_GROUP(gpio6_a_1, ABX500_ALT_A),
	AB8500_PIN_GROUP(gpio7_a_1, ABX500_ALT_A),
	AB8500_PIN_GROUP(gpio8_a_1, ABX500_ALT_A),
	AB8500_PIN_GROUP(gpio9_a_1, ABX500_ALT_A),
	AB8500_PIN_GROUP(ycbcr4567_a_1, ABX500_ALT_A),
	AB8500_PIN_GROUP(gpio14_a_1, ABX500_ALT_A),
	AB8500_PIN_GROUP(gpio15_a_1, ABX500_ALT_A),
	AB8500_PIN_GROUP(gpio16_a_1, ABX500_ALT_A),
	AB8500_PIN_GROUP(gpio17_a_1, ABX500_ALT_A),
	AB8500_PIN_GROUP(gpio18_a_1, ABX500_ALT_A),
	AB8500_PIN_GROUP(gpio19_a_1, ABX500_ALT_A),
	AB8500_PIN_GROUP(gpio20_a_1, ABX500_ALT_A),
	AB8500_PIN_GROUP(gpio21_a_1, ABX500_ALT_A),
	AB8500_PIN_GROUP(gpio22_a_1, ABX500_ALT_A),
	AB8500_PIN_GROUP(gpio23_a_1, ABX500_ALT_A),
	AB8500_PIN_GROUP(gpio24_a_1, ABX500_ALT_A),
	AB8500_PIN_GROUP(gpio25_a_1, ABX500_ALT_A),
	AB8500_PIN_GROUP(gpio27_a_1, ABX500_ALT_A),
	AB8500_PIN_GROUP(gpio28_a_1, ABX500_ALT_A),
	AB8500_PIN_GROUP(gpio29_a_1, ABX500_ALT_A),
	AB8500_PIN_GROUP(gpio30_a_1, ABX500_ALT_A),
	AB8500_PIN_GROUP(gpio31_a_1, ABX500_ALT_A),
	AB8500_PIN_GROUP(gpio32_a_1, ABX500_ALT_A),
	AB8500_PIN_GROUP(gpio34_a_1, ABX500_ALT_A),
	AB8500_PIN_GROUP(gpio36_a_1, ABX500_ALT_A),
	AB8500_PIN_GROUP(gpio37_a_1, ABX500_ALT_A),
	AB8500_PIN_GROUP(gpio38_a_1, ABX500_ALT_A),
	AB8500_PIN_GROUP(gpio39_a_1, ABX500_ALT_A),
	AB8500_PIN_GROUP(gpio40_a_1, ABX500_ALT_A),
	AB8500_PIN_GROUP(gpio41_a_1, ABX500_ALT_A),
	AB8500_PIN_GROUP(gpio42_a_1, ABX500_ALT_A),
	/* Altfunction B column */
	AB8500_PIN_GROUP(hiqclkena_b_1, ABX500_ALT_B),
	AB8500_PIN_GROUP(usbuiccpd_b_1, ABX500_ALT_B),
	AB8500_PIN_GROUP(i2ctrig1_b_1, ABX500_ALT_B),
	AB8500_PIN_GROUP(i2ctrig2_b_1, ABX500_ALT_B),
	/* Altfunction C column */
	AB8500_PIN_GROUP(usbvdat_c_1, ABX500_ALT_C),
पूर्ण;

/* We use this macro to define the groups applicable to a function */
#घोषणा AB8500_FUNC_GROUPS(a, b...)	   \
अटल स्थिर अक्षर * स्थिर a##_groups[] = अणु b पूर्ण;

AB8500_FUNC_GROUPS(sysclkreq, "sysclkreq2_d_1", "sysclkreq3_d_1",
		"sysclkreq4_d_1", "sysclkreq5_d_1", "sysclkreq6_d_1",
		"sysclkreq7_d_1", "sysclkreq8_d_1");
AB8500_FUNC_GROUPS(ycbcr, "ycbcr0123_d_1", "ycbcr4567_a_1");
AB8500_FUNC_GROUPS(gpio, "gpio1_a_1", "gpio2_a_1", "gpio3_a_1", "gpio4_a_1",
		"gpio6_a_1", "gpio7_a_1", "gpio8_a_1", "gpio9_a_1",
		"gpio10_d_1", "gpio11_d_1", "gpio12_d_1", "gpio13_d_1",
		"gpio14_a_1", "gpio15_a_1", "gpio16_a_1", "gpio17_a_1",
		"gpio18_a_1", "gpio19_a_1", "gpio20_a_1", "gpio21_a_1",
		"gpio22_a_1", "gpio23_a_1", "gpio24_a_1", "gpio25_a_1",
		"gpio26_d_1", "gpio27_a_1", "gpio28_a_1", "gpio29_a_1",
		"gpio30_a_1", "gpio31_a_1", "gpio32_a_1", "gpio34_a_1",
		"gpio35_d_1", "gpio36_a_1", "gpio37_a_1", "gpio38_a_1",
		"gpio39_a_1", "gpio40_a_1", "gpio41_a_1", "gpio42_a_1");
AB8500_FUNC_GROUPS(pwmout, "pwmout1_d_1", "pwmout2_d_1", "pwmout3_d_1");
AB8500_FUNC_GROUPS(adi1, "adi1_d_1");
AB8500_FUNC_GROUPS(usbuicc, "usbuicc_d_1", "usbuiccpd_b_1");
AB8500_FUNC_GROUPS(dmic, "dmic12_d_1", "dmic34_d_1", "dmic56_d_1");
AB8500_FUNC_GROUPS(extcpena, "extcpena_d_1");
AB8500_FUNC_GROUPS(apespi, "apespi_d_1");
AB8500_FUNC_GROUPS(modsclsda, "modsclsda_d_1");
AB8500_FUNC_GROUPS(hiqclkena, "hiqclkena_b_1");
AB8500_FUNC_GROUPS(i2ctrig, "i2ctrig1_b_1", "i2ctrig2_b_1");
AB8500_FUNC_GROUPS(usbvdat, "usbvdat_c_1");

#घोषणा FUNCTION(fname)					\
	अणु						\
		.name = #fname,				\
		.groups = fname##_groups,		\
		.ngroups = ARRAY_SIZE(fname##_groups),	\
	पूर्ण

अटल स्थिर काष्ठा abx500_function ab8500_functions[] = अणु
	FUNCTION(sysclkreq),
	FUNCTION(ycbcr),
	FUNCTION(gpio),
	FUNCTION(pwmout),
	FUNCTION(adi1),
	FUNCTION(usbuicc),
	FUNCTION(dmic),
	FUNCTION(extcpena),
	FUNCTION(apespi),
	FUNCTION(modsclsda),
	FUNCTION(hiqclkena),
	FUNCTION(i2ctrig),
	FUNCTION(usbvdat),
पूर्ण;

/*
 * this table translates what's is in the AB8500 specअगरication regarding the
 * balls alternate functions (as क्रम DB, शेष, ALT_A, ALT_B and ALT_C).
 * ALTERNATE_FUNCTIONS(GPIO_NUMBER, GPIOSEL bit, ALTERNATFUNC bit1,
 * ALTERNATEFUNC bit2, ALTA val, ALTB val, ALTC val),
 *
 * example :
 *
 *	ALTERNATE_FUNCTIONS(13,     4,      3,      4, 0, 1 ,2),
 *	means that pin AB8500_PIN_W17 (pin 13) supports 4 mux (शेष/ALT_A,
 *	ALT_B and ALT_C), so GPIOSEL and ALTERNATFUNC रेजिस्टरs are used to
 *	select the mux.  ALTA, ALTB and ALTC val indicates values to ग_लिखो in
 *	ALTERNATFUNC रेजिस्टर. We need to specअगरies these values as SOC
 *	designers didn't apply the same logic on how to select mux in the
 *	ABx500 family.
 *
 *	As this pins supports at least ALT_B mux, शेष mux is
 *	selected by writing 1 in GPIOSEL bit :
 *
 *		| GPIOSEL bit=4 | alternatfunc bit2=4 | alternatfunc bit1=3
 *	शेष	|       1       |          0          |          0
 *	alt_A	|       0       |          0          |          0
 *	alt_B	|       0       |          0          |          1
 *	alt_C	|       0       |          1          |          0
 *
 *	ALTERNATE_FUNCTIONS(8,      7, UNUSED, UNUSED),
 *	means that pin AB8500_PIN_W18 (pin 8) supports 2 mux, so only GPIOSEL
 *	रेजिस्टर is used to select the mux. As this pins करोesn't support at
 *	least ALT_B mux, शेष mux is by writing 0 in GPIOSEL bit :
 *
 *		| GPIOSEL bit=7 | alternatfunc bit2=  | alternatfunc bit1=
 *	शेष	|       0       |          0          |          0
 *	alt_A	|       1       |          0          |          0
 */

अटल काष्ठा
alternate_functions ab8500_alternate_functions[AB8500_GPIO_MAX_NUMBER + 1] = अणु
	ALTERNATE_FUNCTIONS(0, UNUSED, UNUSED, UNUSED, 0, 0, 0), /* no GPIO0 */
	ALTERNATE_FUNCTIONS(1,	    0, UNUSED, UNUSED, 0, 0, 0), /* GPIO1, altA controlled by bit 0 */
	ALTERNATE_FUNCTIONS(2,      1, UNUSED, UNUSED, 0, 0, 0), /* GPIO2, altA controlled by bit 1 */
	ALTERNATE_FUNCTIONS(3,      2, UNUSED, UNUSED, 0, 0, 0), /* GPIO3, altA controlled by bit 2*/
	ALTERNATE_FUNCTIONS(4,      3, UNUSED, UNUSED, 0, 0, 0), /* GPIO4, altA controlled by bit 3*/
	/* bit 4 reserved */
	ALTERNATE_FUNCTIONS(5, UNUSED, UNUSED, UNUSED, 0, 0, 0), /* no GPIO5 */
	ALTERNATE_FUNCTIONS(6,      5, UNUSED, UNUSED, 0, 0, 0), /* GPIO6, altA controlled by bit 5*/
	ALTERNATE_FUNCTIONS(7,      6, UNUSED, UNUSED, 0, 0, 0), /* GPIO7, altA controlled by bit 6*/
	ALTERNATE_FUNCTIONS(8,      7, UNUSED, UNUSED, 0, 0, 0), /* GPIO8, altA controlled by bit 7*/

	ALTERNATE_FUNCTIONS(9,      0, UNUSED, UNUSED, 0, 0, 0), /* GPIO9, altA controlled by bit 0*/
	ALTERNATE_FUNCTIONS(10,     1,      0, UNUSED, 0, 1, 0), /* GPIO10, altA and altB controlled by bit 0 */
	ALTERNATE_FUNCTIONS(11,     2,      1, UNUSED, 0, 1, 0), /* GPIO11, altA and altB controlled by bit 1 */
	ALTERNATE_FUNCTIONS(12,     3,      2, UNUSED, 0, 1, 0), /* GPIO12, altA and altB controlled by bit 2 */
	ALTERNATE_FUNCTIONS(13,     4,      3,      4, 0, 1, 2), /* GPIO13, altA altB and altC controlled by bit 3 and 4 */
	ALTERNATE_FUNCTIONS(14,     5, UNUSED, UNUSED, 0, 0, 0), /* GPIO14, altA controlled by bit 5 */
	ALTERNATE_FUNCTIONS(15,     6, UNUSED, UNUSED, 0, 0, 0), /* GPIO15, altA controlled by bit 6 */
	ALTERNATE_FUNCTIONS(16,     7, UNUSED, UNUSED, 0, 0, 0), /* GPIO16, altA controlled by bit 7 */
	/*
	 * pins 17 to 20 are special हाल, only bit 0 is used to select
	 * alternate function क्रम these 4 pins.
	 * bits 1 to 3 are reserved
	 */
	ALTERNATE_FUNCTIONS(17,      0, UNUSED, UNUSED, 0, 0, 0), /* GPIO17, altA controlled by bit 0 */
	ALTERNATE_FUNCTIONS(18,      0, UNUSED, UNUSED, 0, 0, 0), /* GPIO18, altA controlled by bit 0 */
	ALTERNATE_FUNCTIONS(19,      0, UNUSED, UNUSED, 0, 0, 0), /* GPIO19, altA controlled by bit 0 */
	ALTERNATE_FUNCTIONS(20,      0, UNUSED, UNUSED, 0, 0, 0), /* GPIO20, altA controlled by bit 0 */
	ALTERNATE_FUNCTIONS(21,      4, UNUSED, UNUSED, 0, 0, 0), /* GPIO21, altA controlled by bit 4 */
	ALTERNATE_FUNCTIONS(22,      5, UNUSED, UNUSED, 0, 0, 0), /* GPIO22, altA controlled by bit 5 */
	ALTERNATE_FUNCTIONS(23,      6, UNUSED, UNUSED, 0, 0, 0), /* GPIO23, altA controlled by bit 6 */
	ALTERNATE_FUNCTIONS(24,      7, UNUSED, UNUSED, 0, 0, 0), /* GPIO24, altA controlled by bit 7 */

	ALTERNATE_FUNCTIONS(25,      0, UNUSED, UNUSED, 0, 0, 0), /* GPIO25, altA controlled by bit 0 */
	/* pin 26 special हाल, no alternate function, bit 1 reserved */
	ALTERNATE_FUNCTIONS(26, UNUSED, UNUSED, UNUSED, 0, 0, 0), /* GPIO26 */
	ALTERNATE_FUNCTIONS(27,      2, UNUSED, UNUSED, 0, 0, 0), /* GPIO27, altA controlled by bit 2 */
	ALTERNATE_FUNCTIONS(28,      3, UNUSED, UNUSED, 0, 0, 0), /* GPIO28, altA controlled by bit 3 */
	ALTERNATE_FUNCTIONS(29,      4, UNUSED, UNUSED, 0, 0, 0), /* GPIO29, altA controlled by bit 4 */
	ALTERNATE_FUNCTIONS(30,      5, UNUSED, UNUSED, 0, 0, 0), /* GPIO30, altA controlled by bit 5 */
	ALTERNATE_FUNCTIONS(31,      6, UNUSED, UNUSED, 0, 0, 0), /* GPIO31, altA controlled by bit 6 */
	ALTERNATE_FUNCTIONS(32,      7, UNUSED, UNUSED, 0, 0, 0), /* GPIO32, altA controlled by bit 7 */

	ALTERNATE_FUNCTIONS(33, UNUSED, UNUSED, UNUSED, 0, 0, 0), /* no GPIO33 */
	ALTERNATE_FUNCTIONS(34,      1, UNUSED, UNUSED, 0, 0, 0), /* GPIO34, altA controlled by bit 1 */
	/* pin 35 special हाल, no alternate function, bit 2 reserved */
	ALTERNATE_FUNCTIONS(35, UNUSED, UNUSED, UNUSED, 0, 0, 0), /* GPIO35 */
	ALTERNATE_FUNCTIONS(36,      3, UNUSED, UNUSED, 0, 0, 0), /* GPIO36, altA controlled by bit 3 */
	ALTERNATE_FUNCTIONS(37,      4, UNUSED, UNUSED, 0, 0, 0), /* GPIO37, altA controlled by bit 4 */
	ALTERNATE_FUNCTIONS(38,      5, UNUSED, UNUSED, 0, 0, 0), /* GPIO38, altA controlled by bit 5 */
	ALTERNATE_FUNCTIONS(39,      6, UNUSED, UNUSED, 0, 0, 0), /* GPIO39, altA controlled by bit 6 */
	ALTERNATE_FUNCTIONS(40,      7, UNUSED, UNUSED, 0, 0, 0), /* GPIO40, altA controlled by bit 7 */

	ALTERNATE_FUNCTIONS(41,      0, UNUSED, UNUSED, 0, 0, 0), /* GPIO41, altA controlled by bit 0 */
	ALTERNATE_FUNCTIONS(42,      1, UNUSED, UNUSED, 0, 0, 0), /* GPIO42, altA controlled by bit 1 */
पूर्ण;

/*
 * Only some GPIOs are पूर्णांकerrupt capable, and they are
 * organized in discontiguous clusters:
 *
 *	GPIO6 to GPIO13
 *	GPIO24 and GPIO25
 *	GPIO36 to GPIO41
 */
अटल काष्ठा abx500_gpio_irq_cluster ab8500_gpio_irq_cluster[] = अणु
	GPIO_IRQ_CLUSTER(6,  13, AB8500_INT_GPIO6R),
	GPIO_IRQ_CLUSTER(24, 25, AB8500_INT_GPIO24R),
	GPIO_IRQ_CLUSTER(36, 41, AB8500_INT_GPIO36R),
पूर्ण;

अटल काष्ठा abx500_pinctrl_soc_data ab8500_soc = अणु
	.gpio_ranges = ab8500_pinranges,
	.gpio_num_ranges = ARRAY_SIZE(ab8500_pinranges),
	.pins = ab8500_pins,
	.npins = ARRAY_SIZE(ab8500_pins),
	.functions = ab8500_functions,
	.nfunctions = ARRAY_SIZE(ab8500_functions),
	.groups = ab8500_groups,
	.ngroups = ARRAY_SIZE(ab8500_groups),
	.alternate_functions = ab8500_alternate_functions,
	.gpio_irq_cluster = ab8500_gpio_irq_cluster,
	.ngpio_irq_cluster = ARRAY_SIZE(ab8500_gpio_irq_cluster),
	.irq_gpio_rising_offset = AB8500_INT_GPIO6R,
	.irq_gpio_falling_offset = AB8500_INT_GPIO6F,
	.irq_gpio_factor = 1,
पूर्ण;

व्योम abx500_pinctrl_ab8500_init(काष्ठा abx500_pinctrl_soc_data **soc)
अणु
	*soc = &ab8500_soc;
पूर्ण
