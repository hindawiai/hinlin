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
#घोषणा ABX500_GPIO(offset)	(offset)

#घोषणा AB8505_PIN_N4		ABX500_GPIO(1)
#घोषणा AB8505_PIN_R5		ABX500_GPIO(2)
#घोषणा AB8505_PIN_P5		ABX500_GPIO(3)
/* hole */
#घोषणा AB8505_PIN_B16		ABX500_GPIO(10)
#घोषणा AB8505_PIN_B17		ABX500_GPIO(11)
/* hole */
#घोषणा AB8505_PIN_D17		ABX500_GPIO(13)
#घोषणा AB8505_PIN_C16		ABX500_GPIO(14)
/* hole */
#घोषणा AB8505_PIN_P2		ABX500_GPIO(17)
#घोषणा AB8505_PIN_N3		ABX500_GPIO(18)
#घोषणा AB8505_PIN_T1		ABX500_GPIO(19)
#घोषणा AB8505_PIN_P3		ABX500_GPIO(20)
/* hole */
#घोषणा AB8505_PIN_H14		ABX500_GPIO(34)
/* hole */
#घोषणा AB8505_PIN_J15		ABX500_GPIO(40)
#घोषणा AB8505_PIN_J14		ABX500_GPIO(41)
/* hole */
#घोषणा AB8505_PIN_L4		ABX500_GPIO(50)
/* hole */
#घोषणा AB8505_PIN_D16		ABX500_GPIO(52)
#घोषणा AB8505_PIN_D15		ABX500_GPIO(53)

/* indicates the higher GPIO number */
#घोषणा AB8505_GPIO_MAX_NUMBER	53

/*
 * The names of the pins are denoted by GPIO number and ball name, even
 * though they can be used क्रम other things than GPIO, this is the first
 * column in the table of the data sheet and often used on schematics and
 * such.
 */
अटल स्थिर काष्ठा pinctrl_pin_desc ab8505_pins[] = अणु
	PINCTRL_PIN(AB8505_PIN_N4, "GPIO1_N4"),
	PINCTRL_PIN(AB8505_PIN_R5, "GPIO2_R5"),
	PINCTRL_PIN(AB8505_PIN_P5, "GPIO3_P5"),
/* hole */
	PINCTRL_PIN(AB8505_PIN_B16, "GPIO10_B16"),
	PINCTRL_PIN(AB8505_PIN_B17, "GPIO11_B17"),
/* hole */
	PINCTRL_PIN(AB8505_PIN_D17, "GPIO13_D17"),
	PINCTRL_PIN(AB8505_PIN_C16, "GPIO14_C16"),
/* hole */
	PINCTRL_PIN(AB8505_PIN_P2, "GPIO17_P2"),
	PINCTRL_PIN(AB8505_PIN_N3, "GPIO18_N3"),
	PINCTRL_PIN(AB8505_PIN_T1, "GPIO19_T1"),
	PINCTRL_PIN(AB8505_PIN_P3, "GPIO20_P3"),
/* hole */
	PINCTRL_PIN(AB8505_PIN_H14, "GPIO34_H14"),
/* hole */
	PINCTRL_PIN(AB8505_PIN_J15, "GPIO40_J15"),
	PINCTRL_PIN(AB8505_PIN_J14, "GPIO41_J14"),
/* hole */
	PINCTRL_PIN(AB8505_PIN_L4, "GPIO50_L4"),
/* hole */
	PINCTRL_PIN(AB8505_PIN_D16, "GPIO52_D16"),
	PINCTRL_PIN(AB8505_PIN_D15, "GPIO53_D15"),
पूर्ण;

/*
 * Maps local GPIO offsets to local pin numbers
 */
अटल स्थिर काष्ठा abx500_pinrange ab8505_pinranges[] = अणु
	ABX500_PINRANGE(1, 3, ABX500_ALT_A),
	ABX500_PINRANGE(10, 2, ABX500_DEFAULT),
	ABX500_PINRANGE(13, 1, ABX500_DEFAULT),
	ABX500_PINRANGE(14, 1, ABX500_ALT_A),
	ABX500_PINRANGE(17, 4, ABX500_ALT_A),
	ABX500_PINRANGE(34, 1, ABX500_ALT_A),
	ABX500_PINRANGE(40, 2, ABX500_ALT_A),
	ABX500_PINRANGE(50, 1, ABX500_DEFAULT),
	ABX500_PINRANGE(52, 2, ABX500_ALT_A),
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
अटल स्थिर अचिन्हित sysclkreq2_d_1_pins[] = अणु AB8505_PIN_N4 पूर्ण;
अटल स्थिर अचिन्हित sysclkreq3_d_1_pins[] = अणु AB8505_PIN_R5 पूर्ण;
अटल स्थिर अचिन्हित sysclkreq4_d_1_pins[] = अणु AB8505_PIN_P5 पूर्ण;
अटल स्थिर अचिन्हित gpio10_d_1_pins[] = अणु AB8505_PIN_B16 पूर्ण;
अटल स्थिर अचिन्हित gpio11_d_1_pins[] = अणु AB8505_PIN_B17 पूर्ण;
अटल स्थिर अचिन्हित gpio13_d_1_pins[] = अणु AB8505_PIN_D17 पूर्ण;
अटल स्थिर अचिन्हित pwmout1_d_1_pins[] = अणु AB8505_PIN_C16 पूर्ण;
/* audio data पूर्णांकerface 2*/
अटल स्थिर अचिन्हित adi2_d_1_pins[] = अणु AB8505_PIN_P2, AB8505_PIN_N3,
					AB8505_PIN_T1, AB8505_PIN_P3 पूर्ण;
अटल स्थिर अचिन्हित extcpena_d_1_pins[] = अणु AB8505_PIN_H14 पूर्ण;
/* modem SDA/SCL */
अटल स्थिर अचिन्हित modsclsda_d_1_pins[] = अणु AB8505_PIN_J15, AB8505_PIN_J14 पूर्ण;
अटल स्थिर अचिन्हित gpio50_d_1_pins[] = अणु AB8505_PIN_L4 पूर्ण;
अटल स्थिर अचिन्हित resethw_d_1_pins[] = अणु AB8505_PIN_D16 पूर्ण;
अटल स्थिर अचिन्हित service_d_1_pins[] = अणु AB8505_PIN_D15 पूर्ण;

/* Altfunction A column */
अटल स्थिर अचिन्हित gpio1_a_1_pins[] = अणु AB8505_PIN_N4 पूर्ण;
अटल स्थिर अचिन्हित gpio2_a_1_pins[] = अणु AB8505_PIN_R5 पूर्ण;
अटल स्थिर अचिन्हित gpio3_a_1_pins[] = अणु AB8505_PIN_P5 पूर्ण;
अटल स्थिर अचिन्हित hiqclkena_a_1_pins[] = अणु AB8505_PIN_B16 पूर्ण;
अटल स्थिर अचिन्हित pdmclk_a_1_pins[] = अणु AB8505_PIN_B17 पूर्ण;
अटल स्थिर अचिन्हित uarttxdata_a_1_pins[] = अणु AB8505_PIN_D17 पूर्ण;
अटल स्थिर अचिन्हित gpio14_a_1_pins[] = अणु AB8505_PIN_C16 पूर्ण;
अटल स्थिर अचिन्हित gpio17_a_1_pins[] = अणु AB8505_PIN_P2 पूर्ण;
अटल स्थिर अचिन्हित gpio18_a_1_pins[] = अणु AB8505_PIN_N3 पूर्ण;
अटल स्थिर अचिन्हित gpio19_a_1_pins[] = अणु AB8505_PIN_T1 पूर्ण;
अटल स्थिर अचिन्हित gpio20_a_1_pins[] = अणु AB8505_PIN_P3 पूर्ण;
अटल स्थिर अचिन्हित gpio34_a_1_pins[] = अणु AB8505_PIN_H14 पूर्ण;
अटल स्थिर अचिन्हित gpio40_a_1_pins[] = अणु AB8505_PIN_J15 पूर्ण;
अटल स्थिर अचिन्हित gpio41_a_1_pins[] = अणु AB8505_PIN_J14 पूर्ण;
अटल स्थिर अचिन्हित uartrxdata_a_1_pins[] = अणु AB8505_PIN_J14 पूर्ण;
अटल स्थिर अचिन्हित gpio50_a_1_pins[] = अणु AB8505_PIN_L4 पूर्ण;
अटल स्थिर अचिन्हित gpio52_a_1_pins[] = अणु AB8505_PIN_D16 पूर्ण;
अटल स्थिर अचिन्हित gpio53_a_1_pins[] = अणु AB8505_PIN_D15 पूर्ण;

/* Altfunction B colum */
अटल स्थिर अचिन्हित pdmdata_b_1_pins[] = अणु AB8505_PIN_B16 पूर्ण;
अटल स्थिर अचिन्हित extvibrapwm1_b_1_pins[] = अणु AB8505_PIN_D17 पूर्ण;
अटल स्थिर अचिन्हित extvibrapwm2_b_1_pins[] = अणु AB8505_PIN_L4 पूर्ण;

/* Altfunction C column */
अटल स्थिर अचिन्हित usbvdat_c_1_pins[] = अणु AB8505_PIN_D17 पूर्ण;

#घोषणा AB8505_PIN_GROUP(a, b) अणु .name = #a, .pins = a##_pins,		\
			.npins = ARRAY_SIZE(a##_pins), .altsetting = b पूर्ण

अटल स्थिर काष्ठा abx500_pingroup ab8505_groups[] = अणु
	AB8505_PIN_GROUP(sysclkreq2_d_1, ABX500_DEFAULT),
	AB8505_PIN_GROUP(sysclkreq3_d_1, ABX500_DEFAULT),
	AB8505_PIN_GROUP(sysclkreq4_d_1, ABX500_DEFAULT),
	AB8505_PIN_GROUP(gpio10_d_1, ABX500_DEFAULT),
	AB8505_PIN_GROUP(gpio11_d_1, ABX500_DEFAULT),
	AB8505_PIN_GROUP(gpio13_d_1, ABX500_DEFAULT),
	AB8505_PIN_GROUP(pwmout1_d_1, ABX500_DEFAULT),
	AB8505_PIN_GROUP(adi2_d_1, ABX500_DEFAULT),
	AB8505_PIN_GROUP(extcpena_d_1, ABX500_DEFAULT),
	AB8505_PIN_GROUP(modsclsda_d_1, ABX500_DEFAULT),
	AB8505_PIN_GROUP(gpio50_d_1, ABX500_DEFAULT),
	AB8505_PIN_GROUP(resethw_d_1, ABX500_DEFAULT),
	AB8505_PIN_GROUP(service_d_1, ABX500_DEFAULT),
	AB8505_PIN_GROUP(gpio1_a_1, ABX500_ALT_A),
	AB8505_PIN_GROUP(gpio2_a_1, ABX500_ALT_A),
	AB8505_PIN_GROUP(gpio3_a_1, ABX500_ALT_A),
	AB8505_PIN_GROUP(hiqclkena_a_1, ABX500_ALT_A),
	AB8505_PIN_GROUP(pdmclk_a_1, ABX500_ALT_A),
	AB8505_PIN_GROUP(uarttxdata_a_1, ABX500_ALT_A),
	AB8505_PIN_GROUP(gpio14_a_1, ABX500_ALT_A),
	AB8505_PIN_GROUP(gpio17_a_1, ABX500_ALT_A),
	AB8505_PIN_GROUP(gpio18_a_1, ABX500_ALT_A),
	AB8505_PIN_GROUP(gpio19_a_1, ABX500_ALT_A),
	AB8505_PIN_GROUP(gpio20_a_1, ABX500_ALT_A),
	AB8505_PIN_GROUP(gpio34_a_1, ABX500_ALT_A),
	AB8505_PIN_GROUP(gpio40_a_1, ABX500_ALT_A),
	AB8505_PIN_GROUP(gpio41_a_1, ABX500_ALT_A),
	AB8505_PIN_GROUP(uartrxdata_a_1, ABX500_ALT_A),
	AB8505_PIN_GROUP(gpio50_a_1, ABX500_ALT_A),
	AB8505_PIN_GROUP(gpio52_a_1, ABX500_ALT_A),
	AB8505_PIN_GROUP(gpio53_a_1, ABX500_ALT_A),
	AB8505_PIN_GROUP(pdmdata_b_1, ABX500_ALT_B),
	AB8505_PIN_GROUP(extvibrapwm1_b_1, ABX500_ALT_B),
	AB8505_PIN_GROUP(extvibrapwm2_b_1, ABX500_ALT_B),
	AB8505_PIN_GROUP(usbvdat_c_1, ABX500_ALT_C),
पूर्ण;

/* We use this macro to define the groups applicable to a function */
#घोषणा AB8505_FUNC_GROUPS(a, b...)	   \
अटल स्थिर अक्षर * स्थिर a##_groups[] = अणु b पूर्ण;

AB8505_FUNC_GROUPS(sysclkreq, "sysclkreq2_d_1", "sysclkreq3_d_1",
		"sysclkreq4_d_1");
AB8505_FUNC_GROUPS(gpio, "gpio1_a_1", "gpio2_a_1", "gpio3_a_1",
		"gpio10_d_1", "gpio11_d_1", "gpio13_d_1", "gpio14_a_1",
		"gpio17_a_1", "gpio18_a_1", "gpio19_a_1", "gpio20_a_1",
		"gpio34_a_1", "gpio40_a_1", "gpio41_a_1", "gpio50_d_1",
		"gpio52_a_1", "gpio53_a_1");
AB8505_FUNC_GROUPS(pwmout, "pwmout1_d_1");
AB8505_FUNC_GROUPS(adi2, "adi2_d_1");
AB8505_FUNC_GROUPS(extcpena, "extcpena_d_1");
AB8505_FUNC_GROUPS(modsclsda, "modsclsda_d_1");
AB8505_FUNC_GROUPS(resethw, "resethw_d_1");
AB8505_FUNC_GROUPS(service, "service_d_1");
AB8505_FUNC_GROUPS(hiqclkena, "hiqclkena_a_1");
AB8505_FUNC_GROUPS(pdm, "pdmclk_a_1", "pdmdata_b_1");
AB8505_FUNC_GROUPS(uartdata, "uarttxdata_a_1", "uartrxdata_a_1");
AB8505_FUNC_GROUPS(extvibra, "extvibrapwm1_b_1", "extvibrapwm2_b_1");
AB8505_FUNC_GROUPS(usbvdat, "usbvdat_c_1");

#घोषणा FUNCTION(fname)					\
	अणु						\
		.name = #fname,				\
		.groups = fname##_groups,		\
		.ngroups = ARRAY_SIZE(fname##_groups),	\
	पूर्ण

अटल स्थिर काष्ठा abx500_function ab8505_functions[] = अणु
	FUNCTION(sysclkreq),
	FUNCTION(gpio),
	FUNCTION(pwmout),
	FUNCTION(adi2),
	FUNCTION(extcpena),
	FUNCTION(modsclsda),
	FUNCTION(resethw),
	FUNCTION(service),
	FUNCTION(hiqclkena),
	FUNCTION(pdm),
	FUNCTION(uartdata),
	FUNCTION(extvibra),
	FUNCTION(extvibra),
	FUNCTION(usbvdat),
पूर्ण;

/*
 * this table translates what's is in the AB8505 specअगरication regarding the
 * balls alternate functions (as क्रम DB, शेष, ALT_A, ALT_B and ALT_C).
 * ALTERNATE_FUNCTIONS(GPIO_NUMBER, GPIOSEL bit, ALTERNATFUNC bit1,
 * ALTERNATEFUNC bit2, ALTA val, ALTB val, ALTC val),
 *
 * example :
 *
 *	ALTERNATE_FUNCTIONS(13,     4,      3,      4, 1, 0, 2),
 *	means that pin AB8505_PIN_D18 (pin 13) supports 4 mux (शेष/ALT_A,
 *	ALT_B and ALT_C), so GPIOSEL and ALTERNATFUNC रेजिस्टरs are used to
 *	select the mux. ALTA, ALTB and ALTC val indicates values to ग_लिखो in
 *	ALTERNATFUNC रेजिस्टर. We need to specअगरies these values as SOC
 *	designers didn't apply the same logic on how to select mux in the
 *	ABx500 family.
 *
 *	As this pins supports at least ALT_B mux, शेष mux is
 *	selected by writing 1 in GPIOSEL bit :
 *
 *		| GPIOSEL bit=4 | alternatfunc bit2=4 | alternatfunc bit1=3
 *	शेष	|       1       |          0          |          0
 *	alt_A	|       0       |          0          |          1
 *	alt_B	|       0       |          0          |          0
 *	alt_C	|       0       |          1          |          0
 *
 *	ALTERNATE_FUNCTIONS(1,      0, UNUSED, UNUSED),
 *	means that pin AB9540_PIN_R4 (pin 1) supports 2 mux, so only GPIOSEL
 *	रेजिस्टर is used to select the mux. As this pins करोesn't support at
 *	least ALT_B mux, शेष mux is by writing 0 in GPIOSEL bit :
 *
 *		| GPIOSEL bit=0 | alternatfunc bit2=  | alternatfunc bit1=
 *	शेष	|       0       |          0          |          0
 *	alt_A	|       1       |          0          |          0
 */

अटल काष्ठा
alternate_functions ab8505_alternate_functions[AB8505_GPIO_MAX_NUMBER + 1] = अणु
	ALTERNATE_FUNCTIONS(0, UNUSED, UNUSED, UNUSED, 0, 0, 0), /* no GPIO0 */
	ALTERNATE_FUNCTIONS(1,      0, UNUSED, UNUSED, 0, 0, 0), /* GPIO1, altA controlled by bit 0 */
	ALTERNATE_FUNCTIONS(2,      1, UNUSED, UNUSED, 0, 0, 0), /* GPIO2, altA controlled by bit 1 */
	ALTERNATE_FUNCTIONS(3,      2, UNUSED, UNUSED, 0, 0, 0), /* GPIO3, altA controlled by bit 2*/
	ALTERNATE_FUNCTIONS(4, UNUSED, UNUSED, UNUSED, 0, 0, 0), /* no GPIO4, bit 3 reserved */
	ALTERNATE_FUNCTIONS(5, UNUSED, UNUSED, UNUSED, 0, 0, 0), /* no GPIO5, bit 4 reserved */
	ALTERNATE_FUNCTIONS(6, UNUSED, UNUSED, UNUSED, 0, 0, 0), /* no GPIO6, bit 5 reserved */
	ALTERNATE_FUNCTIONS(7, UNUSED, UNUSED, UNUSED, 0, 0, 0), /* no GPIO7, bit 6 reserved */
	ALTERNATE_FUNCTIONS(8, UNUSED, UNUSED, UNUSED, 0, 0, 0), /* no GPIO8, bit 7 reserved */

	ALTERNATE_FUNCTIONS(9, UNUSED, UNUSED, UNUSED, 0, 0, 0), /* no GPIO9, bit 0 reserved */
	ALTERNATE_FUNCTIONS(10,      1,      0, UNUSED, 1, 0, 0), /* GPIO10, altA and altB controlled by bit 0 */
	ALTERNATE_FUNCTIONS(11,      2,      1, UNUSED, 0, 0, 0), /* GPIO11, altA controlled by bit 2 */
	ALTERNATE_FUNCTIONS(12, UNUSED, UNUSED, UNUSED, 0, 0, 0), /* no GPIO12, bit3 reserved */
	ALTERNATE_FUNCTIONS(13,      4,      3,      4, 1, 0, 2), /* GPIO13, altA altB and altC controlled by bit 3 and 4 */
	ALTERNATE_FUNCTIONS(14,      5, UNUSED, UNUSED, 0, 0, 0), /* GPIO14, altA controlled by bit 5 */
	ALTERNATE_FUNCTIONS(15, UNUSED, UNUSED, UNUSED, 0, 0, 0), /* no GPIO15, bit 6 reserved */
	ALTERNATE_FUNCTIONS(16, UNUSED, UNUSED, UNUSED, 0, 0, 0), /* no GPIO15, bit 7 reserved  */
	/*
	 * pins 17 to 20 are special हाल, only bit 0 is used to select
	 * alternate function क्रम these 4 pins.
	 * bits 1 to 3 are reserved
	 */
	ALTERNATE_FUNCTIONS(17,      0, UNUSED, UNUSED, 0, 0, 0), /* GPIO17, altA controlled by bit 0 */
	ALTERNATE_FUNCTIONS(18,      0, UNUSED, UNUSED, 0, 0, 0), /* GPIO18, altA controlled by bit 0 */
	ALTERNATE_FUNCTIONS(19,      0, UNUSED, UNUSED, 0, 0, 0), /* GPIO19, altA controlled by bit 0 */
	ALTERNATE_FUNCTIONS(20,      0, UNUSED, UNUSED, 0, 0, 0), /* GPIO20, altA controlled by bit 0 */
	ALTERNATE_FUNCTIONS(21, UNUSED, UNUSED, UNUSED, 0, 0, 0), /* no GPIO21, bit 4 reserved */
	ALTERNATE_FUNCTIONS(22, UNUSED, UNUSED, UNUSED, 0, 0, 0), /* no GPIO22, bit 5 reserved */
	ALTERNATE_FUNCTIONS(23, UNUSED, UNUSED, UNUSED, 0, 0, 0), /* no GPIO23, bit 6 reserved */
	ALTERNATE_FUNCTIONS(24, UNUSED, UNUSED, UNUSED, 0, 0, 0), /* no GPIO24, bit 7 reserved */

	ALTERNATE_FUNCTIONS(25, UNUSED, UNUSED, UNUSED, 0, 0, 0), /* no GPIO25, bit 0 reserved */
	ALTERNATE_FUNCTIONS(26, UNUSED, UNUSED, UNUSED, 0, 0, 0), /* no GPIO26, bit 1 reserved */
	ALTERNATE_FUNCTIONS(27, UNUSED, UNUSED, UNUSED, 0, 0, 0), /* no GPIO27, bit 2 reserved */
	ALTERNATE_FUNCTIONS(28, UNUSED, UNUSED, UNUSED, 0, 0, 0), /* no GPIO28, bit 3 reserved */
	ALTERNATE_FUNCTIONS(29, UNUSED, UNUSED, UNUSED, 0, 0, 0), /* no GPIO29, bit 4 reserved */
	ALTERNATE_FUNCTIONS(30, UNUSED, UNUSED, UNUSED, 0, 0, 0), /* no GPIO30, bit 5 reserved */
	ALTERNATE_FUNCTIONS(31, UNUSED, UNUSED, UNUSED, 0, 0, 0), /* no GPIO31, bit 6 reserved */
	ALTERNATE_FUNCTIONS(32, UNUSED, UNUSED, UNUSED, 0, 0, 0), /* no GPIO32, bit 7 reserved */

	ALTERNATE_FUNCTIONS(33, UNUSED, UNUSED, UNUSED, 0, 0, 0), /* no GPIO33, bit 0 reserved */
	ALTERNATE_FUNCTIONS(34,      1, UNUSED, UNUSED, 0, 0, 0), /* GPIO34, altA controlled by bit 1 */
	ALTERNATE_FUNCTIONS(35, UNUSED, UNUSED, UNUSED, 0, 0, 0), /* no GPIO35, bit 2 reserved */
	ALTERNATE_FUNCTIONS(36, UNUSED, UNUSED, UNUSED, 0, 0, 0), /* no GPIO36, bit 2 reserved */
	ALTERNATE_FUNCTIONS(37, UNUSED, UNUSED, UNUSED, 0, 0, 0), /* no GPIO37, bit 2 reserved */
	ALTERNATE_FUNCTIONS(38, UNUSED, UNUSED, UNUSED, 0, 0, 0), /* no GPIO38, bit 2 reserved */
	ALTERNATE_FUNCTIONS(39, UNUSED, UNUSED, UNUSED, 0, 0, 0), /* no GPIO39, bit 2 reserved */
	ALTERNATE_FUNCTIONS(40,      7, UNUSED, UNUSED, 0, 0, 0), /* GPIO40, altA controlled by bit 7*/

	ALTERNATE_FUNCTIONS(41,      0, UNUSED, UNUSED, 0, 0, 0), /* GPIO41, altA controlled by bit 0 */
	ALTERNATE_FUNCTIONS(42, UNUSED, UNUSED, UNUSED, 0, 0, 0), /* no GPIO42, bit 1 reserved */
	ALTERNATE_FUNCTIONS(43, UNUSED, UNUSED, UNUSED, 0, 0, 0), /* no GPIO43, bit 2 reserved */
	ALTERNATE_FUNCTIONS(44, UNUSED, UNUSED, UNUSED, 0, 0, 0), /* no GPIO44, bit 3 reserved */
	ALTERNATE_FUNCTIONS(45, UNUSED, UNUSED, UNUSED, 0, 0, 0), /* no GPIO45, bit 4 reserved */
	ALTERNATE_FUNCTIONS(46, UNUSED, UNUSED, UNUSED, 0, 0, 0), /* no GPIO46, bit 5 reserved */
	ALTERNATE_FUNCTIONS(47, UNUSED, UNUSED, UNUSED, 0, 0, 0), /* no GPIO47, bit 6 reserved */
	ALTERNATE_FUNCTIONS(48, UNUSED, UNUSED, UNUSED, 0, 0, 0), /* no GPIO48, bit 7 reserved */

	ALTERNATE_FUNCTIONS(49, UNUSED, UNUSED, UNUSED, 0, 0, 0), /* no GPIO49, bit 0 reserved */
	ALTERNATE_FUNCTIONS(50,	     1,      2, UNUSED, 1, 0, 0), /* GPIO50, altA controlled by bit 1 */
	ALTERNATE_FUNCTIONS(51, UNUSED, UNUSED, UNUSED, 0, 0, 0), /* no GPIO49, bit 0 reserved */
	ALTERNATE_FUNCTIONS(52,	     3, UNUSED, UNUSED, 0, 0, 0), /* GPIO52, altA controlled by bit 3 */
	ALTERNATE_FUNCTIONS(53,	     4, UNUSED, UNUSED, 0, 0, 0), /* GPIO53, altA controlled by bit 4 */
पूर्ण;

/*
 * For AB8505 Only some GPIOs are पूर्णांकerrupt capable, and they are
 * organized in discontiguous clusters:
 *
 *	GPIO10 to GPIO11
 *	GPIO13
 *	GPIO40 and GPIO41
 *	GPIO50
 *	GPIO52 to GPIO53
 */
अटल काष्ठा abx500_gpio_irq_cluster ab8505_gpio_irq_cluster[] = अणु
	GPIO_IRQ_CLUSTER(10, 11, AB8500_INT_GPIO10R),
	GPIO_IRQ_CLUSTER(13, 13, AB8500_INT_GPIO13R),
	GPIO_IRQ_CLUSTER(40, 41, AB8500_INT_GPIO40R),
	GPIO_IRQ_CLUSTER(50, 50, AB9540_INT_GPIO50R),
	GPIO_IRQ_CLUSTER(52, 53, AB9540_INT_GPIO52R),
पूर्ण;

अटल काष्ठा abx500_pinctrl_soc_data ab8505_soc = अणु
	.gpio_ranges = ab8505_pinranges,
	.gpio_num_ranges = ARRAY_SIZE(ab8505_pinranges),
	.pins = ab8505_pins,
	.npins = ARRAY_SIZE(ab8505_pins),
	.functions = ab8505_functions,
	.nfunctions = ARRAY_SIZE(ab8505_functions),
	.groups = ab8505_groups,
	.ngroups = ARRAY_SIZE(ab8505_groups),
	.alternate_functions = ab8505_alternate_functions,
	.gpio_irq_cluster = ab8505_gpio_irq_cluster,
	.ngpio_irq_cluster = ARRAY_SIZE(ab8505_gpio_irq_cluster),
	.irq_gpio_rising_offset = AB8500_INT_GPIO6R,
	.irq_gpio_falling_offset = AB8500_INT_GPIO6F,
	.irq_gpio_factor = 1,
पूर्ण;

व्योम
abx500_pinctrl_ab8505_init(काष्ठा abx500_pinctrl_soc_data **soc)
अणु
	*soc = &ab8505_soc;
पूर्ण
