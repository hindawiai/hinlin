<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित PINCTRL_PINCTRL_NOMADIK_H
#घोषणा PINCTRL_PINCTRL_NOMADIK_H

/* Package definitions */
#घोषणा PINCTRL_NMK_STN8815	0
#घोषणा PINCTRL_NMK_DB8500	1
#घोषणा PINCTRL_NMK_DB8540	2

/* Alternate functions: function C is set in hw by setting both A and B */
#घोषणा NMK_GPIO_ALT_GPIO	0
#घोषणा NMK_GPIO_ALT_A	1
#घोषणा NMK_GPIO_ALT_B	2
#घोषणा NMK_GPIO_ALT_C	(NMK_GPIO_ALT_A | NMK_GPIO_ALT_B)

#घोषणा NMK_GPIO_ALT_CX_SHIFT 2
#घोषणा NMK_GPIO_ALT_C1	((1<<NMK_GPIO_ALT_CX_SHIFT) | NMK_GPIO_ALT_C)
#घोषणा NMK_GPIO_ALT_C2	((2<<NMK_GPIO_ALT_CX_SHIFT) | NMK_GPIO_ALT_C)
#घोषणा NMK_GPIO_ALT_C3	((3<<NMK_GPIO_ALT_CX_SHIFT) | NMK_GPIO_ALT_C)
#घोषणा NMK_GPIO_ALT_C4	((4<<NMK_GPIO_ALT_CX_SHIFT) | NMK_GPIO_ALT_C)

#घोषणा PRCM_GPIOCR_ALTCX(pin_num,\
	altc1_used, altc1_ri, altc1_cb,\
	altc2_used, altc2_ri, altc2_cb,\
	altc3_used, altc3_ri, altc3_cb,\
	altc4_used, altc4_ri, altc4_cb)\
अणु\
	.pin = pin_num,\
	.altcx[PRCM_IDX_GPIOCR_ALTC1] = अणु\
		.used = altc1_used,\
		.reg_index = altc1_ri,\
		.control_bit = altc1_cb\
	पूर्ण,\
	.altcx[PRCM_IDX_GPIOCR_ALTC2] = अणु\
		.used = altc2_used,\
		.reg_index = altc2_ri,\
		.control_bit = altc2_cb\
	पूर्ण,\
	.altcx[PRCM_IDX_GPIOCR_ALTC3] = अणु\
		.used = altc3_used,\
		.reg_index = altc3_ri,\
		.control_bit = altc3_cb\
	पूर्ण,\
	.altcx[PRCM_IDX_GPIOCR_ALTC4] = अणु\
		.used = altc4_used,\
		.reg_index = altc4_ri,\
		.control_bit = altc4_cb\
	पूर्ण,\
पूर्ण

/**
 * क्रमागत prcm_gpiocr_reg_index
 * Used to reference an PRCM GPIOCR रेजिस्टर address.
 */
क्रमागत prcm_gpiocr_reg_index अणु
	PRCM_IDX_GPIOCR1,
	PRCM_IDX_GPIOCR2,
	PRCM_IDX_GPIOCR3
पूर्ण;
/**
 * क्रमागत prcm_gpiocr_altcx_index
 * Used to reference an Other alternate-C function.
 */
क्रमागत prcm_gpiocr_altcx_index अणु
	PRCM_IDX_GPIOCR_ALTC1,
	PRCM_IDX_GPIOCR_ALTC2,
	PRCM_IDX_GPIOCR_ALTC3,
	PRCM_IDX_GPIOCR_ALTC4,
	PRCM_IDX_GPIOCR_ALTC_MAX,
पूर्ण;

/**
 * काष्ठा prcm_gpio_altcx - Other alternate-C function
 * @used: other alternate-C function availability
 * @reg_index: PRCM GPIOCR रेजिस्टर index used to control the function
 * @control_bit: PRCM GPIOCR bit used to control the function
 */
काष्ठा prcm_gpiocr_altcx अणु
	bool used:1;
	u8 reg_index:2;
	u8 control_bit:5;
पूर्ण __packed;

/**
 * काष्ठा prcm_gpio_altcx_pin_desc - Other alternate-C pin
 * @pin: The pin number
 * @altcx: array of other alternate-C[1-4] functions
 */
काष्ठा prcm_gpiocr_altcx_pin_desc अणु
	अचिन्हित लघु pin;
	काष्ठा prcm_gpiocr_altcx altcx[PRCM_IDX_GPIOCR_ALTC_MAX];
पूर्ण;

/**
 * काष्ठा nmk_function - Nomadik pinctrl mux function
 * @name: The name of the function, exported to pinctrl core.
 * @groups: An array of pin groups that may select this function.
 * @ngroups: The number of entries in @groups.
 */
काष्ठा nmk_function अणु
	स्थिर अक्षर *name;
	स्थिर अक्षर * स्थिर *groups;
	अचिन्हित ngroups;
पूर्ण;

/**
 * काष्ठा nmk_pingroup - describes a Nomadik pin group
 * @name: the name of this specअगरic pin group
 * @pins: an array of discrete physical pins used in this group, taken
 *	from the driver-local pin क्रमागतeration space
 * @num_pins: the number of pins in this group array, i.e. the number of
 *	elements in .pins so we can iterate over that array
 * @altsetting: the altsetting to apply to all pins in this group to
 *	configure them to be used by a function
 */
काष्ठा nmk_pingroup अणु
	स्थिर अक्षर *name;
	स्थिर अचिन्हित पूर्णांक *pins;
	स्थिर अचिन्हित npins;
	पूर्णांक altsetting;
पूर्ण;

/**
 * काष्ठा nmk_pinctrl_soc_data - Nomadik pin controller per-SoC configuration
 * @pins:	An array describing all pins the pin controller affects.
 *		All pins which are also GPIOs must be listed first within the
 *		array, and be numbered identically to the GPIO controller's
 *		numbering.
 * @npins:	The number of entries in @pins.
 * @functions:	The functions supported on this SoC.
 * @nfunction:	The number of entries in @functions.
 * @groups:	An array describing all pin groups the pin SoC supports.
 * @ngroups:	The number of entries in @groups.
 * @altcx_pins:	The pins that support Other alternate-C function on this SoC
 * @npins_altcx: The number of Other alternate-C pins
 * @prcm_gpiocr_रेजिस्टरs: The array of PRCM GPIOCR रेजिस्टरs on this SoC
 */
काष्ठा nmk_pinctrl_soc_data अणु
	स्थिर काष्ठा pinctrl_pin_desc *pins;
	अचिन्हित npins;
	स्थिर काष्ठा nmk_function *functions;
	अचिन्हित nfunctions;
	स्थिर काष्ठा nmk_pingroup *groups;
	अचिन्हित ngroups;
	स्थिर काष्ठा prcm_gpiocr_altcx_pin_desc *altcx_pins;
	अचिन्हित npins_altcx;
	स्थिर u16 *prcm_gpiocr_रेजिस्टरs;
पूर्ण;

#अगर_घोषित CONFIG_PINCTRL_STN8815

व्योम nmk_pinctrl_stn8815_init(स्थिर काष्ठा nmk_pinctrl_soc_data **soc);

#अन्यथा

अटल अंतरभूत व्योम
nmk_pinctrl_stn8815_init(स्थिर काष्ठा nmk_pinctrl_soc_data **soc)
अणु
पूर्ण

#पूर्ण_अगर

#अगर_घोषित CONFIG_PINCTRL_DB8500

व्योम nmk_pinctrl_db8500_init(स्थिर काष्ठा nmk_pinctrl_soc_data **soc);

#अन्यथा

अटल अंतरभूत व्योम
nmk_pinctrl_db8500_init(स्थिर काष्ठा nmk_pinctrl_soc_data **soc)
अणु
पूर्ण

#पूर्ण_अगर

#अगर_घोषित CONFIG_PINCTRL_DB8540

व्योम nmk_pinctrl_db8540_init(स्थिर काष्ठा nmk_pinctrl_soc_data **soc);

#अन्यथा

अटल अंतरभूत व्योम
nmk_pinctrl_db8540_init(स्थिर काष्ठा nmk_pinctrl_soc_data **soc)
अणु
पूर्ण

#पूर्ण_अगर

#पूर्ण_अगर /* PINCTRL_PINCTRL_NOMADIK_H */
