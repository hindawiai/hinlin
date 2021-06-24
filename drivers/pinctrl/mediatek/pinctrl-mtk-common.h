<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Copyright (c) 2014 MediaTek Inc.
 * Author: Hongzhou.Yang <hongzhou.yang@mediatek.com>
 */

#अगर_अघोषित __PINCTRL_MTK_COMMON_H
#घोषणा __PINCTRL_MTK_COMMON_H

#समावेश <linux/pinctrl/pinctrl.h>
#समावेश <linux/regmap.h>
#समावेश <linux/pinctrl/pinconf-generic.h>

#समावेश "mtk-eint.h"

#घोषणा NO_EINT_SUPPORT    255
#घोषणा MT_EDGE_SENSITIVE           0
#घोषणा MT_LEVEL_SENSITIVE          1
#घोषणा EINT_DBNC_SET_DBNC_BITS     4
#घोषणा EINT_DBNC_RST_BIT           (0x1 << 1)
#घोषणा EINT_DBNC_SET_EN            (0x1 << 0)

#घोषणा MTK_PINCTRL_NOT_SUPPORT	(0xffff)

काष्ठा mtk_desc_function अणु
	स्थिर अक्षर *name;
	अचिन्हित अक्षर muxval;
पूर्ण;

काष्ठा mtk_desc_eपूर्णांक अणु
	अचिन्हित अक्षर eपूर्णांकmux;
	अचिन्हित अक्षर eपूर्णांकnum;
पूर्ण;

काष्ठा mtk_desc_pin अणु
	काष्ठा pinctrl_pin_desc	pin;
	स्थिर काष्ठा mtk_desc_eपूर्णांक eपूर्णांक;
	स्थिर काष्ठा mtk_desc_function	*functions;
पूर्ण;

#घोषणा MTK_PIN(_pin, _pad, _chip, _eपूर्णांक, ...)		\
	अणु							\
		.pin = _pin,					\
		.eपूर्णांक = _eपूर्णांक,					\
		.functions = (काष्ठा mtk_desc_function[])अणु	\
			__VA_ARGS__, अणु पूर्ण पूर्ण,			\
	पूर्ण

#घोषणा MTK_EINT_FUNCTION(_eपूर्णांकmux, _eपूर्णांकnum)				\
	अणु							\
		.eपूर्णांकmux = _eपूर्णांकmux,					\
		.eपूर्णांकnum = _eपूर्णांकnum,					\
	पूर्ण

#घोषणा MTK_FUNCTION(_val, _name)				\
	अणु							\
		.muxval = _val,					\
		.name = _name,					\
	पूर्ण

#घोषणा SET_ADDR(x, y)  (x + (y->devdata->port_align))
#घोषणा CLR_ADDR(x, y)  (x + (y->devdata->port_align << 1))

काष्ठा mtk_pinctrl_group अणु
	स्थिर अक्षर	*name;
	अचिन्हित दीर्घ	config;
	अचिन्हित	pin;
पूर्ण;

/**
 * काष्ठा mtk_drv_group_desc - Provide driving group data.
 * @max_drv: The maximum current of this group.
 * @min_drv: The minimum current of this group.
 * @low_bit: The lowest bit of this group.
 * @high_bit: The highest bit of this group.
 * @step: The step current of this group.
 */
काष्ठा mtk_drv_group_desc अणु
	अचिन्हित अक्षर min_drv;
	अचिन्हित अक्षर max_drv;
	अचिन्हित अक्षर low_bit;
	अचिन्हित अक्षर high_bit;
	अचिन्हित अक्षर step;
पूर्ण;

#घोषणा MTK_DRV_GRP(_min, _max, _low, _high, _step)	\
	अणु	\
		.min_drv = _min,	\
		.max_drv = _max,	\
		.low_bit = _low,	\
		.high_bit = _high,	\
		.step = _step,		\
	पूर्ण

/**
 * काष्ठा mtk_pin_drv_grp - Provide each pin driving info.
 * @pin: The pin number.
 * @offset: The offset of driving रेजिस्टर क्रम this pin.
 * @bit: The bit of driving रेजिस्टर क्रम this pin.
 * @grp: The group क्रम this pin beदीर्घs to.
 */
काष्ठा mtk_pin_drv_grp अणु
	अचिन्हित लघु pin;
	अचिन्हित लघु offset;
	अचिन्हित अक्षर bit;
	अचिन्हित अक्षर grp;
पूर्ण;

#घोषणा MTK_PIN_DRV_GRP(_pin, _offset, _bit, _grp)	\
	अणु	\
		.pin = _pin,	\
		.offset = _offset,	\
		.bit = _bit,	\
		.grp = _grp,	\
	पूर्ण

/**
 * काष्ठा mtk_pin_spec_pupd_set_samereg
 * - For special pins' pull up/करोwn setting which resides in same रेजिस्टर
 * @pin: The pin number.
 * @offset: The offset of special pull up/करोwn setting रेजिस्टर.
 * @pupd_bit: The pull up/करोwn bit in this रेजिस्टर.
 * @r0_bit: The r0 bit of pull resistor.
 * @r1_bit: The r1 bit of pull resistor.
 */
काष्ठा mtk_pin_spec_pupd_set_samereg अणु
	अचिन्हित लघु pin;
	अचिन्हित लघु offset;
	अचिन्हित अक्षर pupd_bit;
	अचिन्हित अक्षर r1_bit;
	अचिन्हित अक्षर r0_bit;
पूर्ण;

#घोषणा MTK_PIN_PUPD_SPEC_SR(_pin, _offset, _pupd, _r1, _r0)	\
	अणु	\
		.pin = _pin,	\
		.offset = _offset,	\
		.pupd_bit = _pupd,	\
		.r1_bit = _r1,		\
		.r0_bit = _r0,		\
	पूर्ण

/**
 * काष्ठा mtk_pin_ies_set - For special pins' ies and smt setting.
 * @start: The start pin number of those special pins.
 * @end: The end pin number of those special pins.
 * @offset: The offset of special setting रेजिस्टर.
 * @bit: The bit of special setting रेजिस्टर.
 */
काष्ठा mtk_pin_ies_smt_set अणु
	अचिन्हित लघु start;
	अचिन्हित लघु end;
	अचिन्हित लघु offset;
	अचिन्हित अक्षर bit;
पूर्ण;

#घोषणा MTK_PIN_IES_SMT_SPEC(_start, _end, _offset, _bit)	\
	अणु	\
		.start = _start,	\
		.end = _end,	\
		.bit = _bit,	\
		.offset = _offset,	\
	पूर्ण

काष्ठा mtk_eपूर्णांक_offsets अणु
	स्थिर अक्षर *name;
	अचिन्हित पूर्णांक  stat;
	अचिन्हित पूर्णांक  ack;
	अचिन्हित पूर्णांक  mask;
	अचिन्हित पूर्णांक  mask_set;
	अचिन्हित पूर्णांक  mask_clr;
	अचिन्हित पूर्णांक  sens;
	अचिन्हित पूर्णांक  sens_set;
	अचिन्हित पूर्णांक  sens_clr;
	अचिन्हित पूर्णांक  soft;
	अचिन्हित पूर्णांक  soft_set;
	अचिन्हित पूर्णांक  soft_clr;
	अचिन्हित पूर्णांक  pol;
	अचिन्हित पूर्णांक  pol_set;
	अचिन्हित पूर्णांक  pol_clr;
	अचिन्हित पूर्णांक  करोm_en;
	अचिन्हित पूर्णांक  dbnc_ctrl;
	अचिन्हित पूर्णांक  dbnc_set;
	अचिन्हित पूर्णांक  dbnc_clr;
	u8  port_mask;
	u8  ports;
पूर्ण;

/**
 * काष्ठा mtk_pinctrl_devdata - Provide HW GPIO related data.
 * @pins: An array describing all pins the pin controller affects.
 * @npins: The number of entries in @pins.
 *
 * @grp_desc: The driving group info.
 * @pin_drv_grp: The driving group क्रम all pins.
 * @spec_pull_set: Each SoC may have special pins क्रम pull up/करोwn setting,
 *  these pins' pull setting are very dअगरferent, they have separate pull
 *  up/करोwn bit, R0 and R1 resistor bit, so they need special pull setting.
 *  If special setting is success, this should वापस 0, otherwise it should
 *  वापस non-zero value.
 * @spec_ies_smt_set: Some pins are irregular, their input enable and smt
 * control रेजिस्टर are discontinuous, but they are mapping together. That
 * means when user set smt, input enable is set at the same समय. So they
 * also need special control. If special control is success, this should
 * वापस 0, otherwise वापस non-zero value.
 * @spec_pinmux_set: In some हालs, there are two pinmux functions share
 * the same value in the same segment of pinmux control रेजिस्टर. If user
 * want to use one of the two functions, they need an extra bit setting to
 * select the right one.
 * @spec_dir_set: In very few SoCs, direction control रेजिस्टरs are not
 * arranged continuously, they may be cut to parts. So they need special
 * dir setting.

 * @dir_offset: The direction रेजिस्टर offset.
 * @pullen_offset: The pull-up/pull-करोwn enable रेजिस्टर offset.
 * @pinmux_offset: The pinmux रेजिस्टर offset.
 *
 * @type1_start: Some chips have two base addresses क्रम pull select रेजिस्टर,
 *  that means some pins use the first address and others use the second. This
 *  member record the start of pin number to use the second address.
 * @type1_end: The end of pin number to use the second address.
 *
 * @port_shf: The shअगरt between two रेजिस्टरs.
 * @port_mask: The mask of रेजिस्टर.
 * @port_align: Provide clear रेजिस्टर and set रेजिस्टर step.
 */
काष्ठा mtk_pinctrl_devdata अणु
	स्थिर काष्ठा mtk_desc_pin	*pins;
	अचिन्हित पूर्णांक				npins;
	स्थिर काष्ठा mtk_drv_group_desc	*grp_desc;
	अचिन्हित पूर्णांक	n_grp_cls;
	स्थिर काष्ठा mtk_pin_drv_grp	*pin_drv_grp;
	अचिन्हित पूर्णांक	n_pin_drv_grps;
	पूर्णांक (*spec_pull_set)(काष्ठा regmap *reg, अचिन्हित पूर्णांक pin,
			अचिन्हित अक्षर align, bool isup, अचिन्हित पूर्णांक arg);
	पूर्णांक (*spec_ies_smt_set)(काष्ठा regmap *reg, अचिन्हित पूर्णांक pin,
			अचिन्हित अक्षर align, पूर्णांक value, क्रमागत pin_config_param arg);
	व्योम (*spec_pinmux_set)(काष्ठा regmap *reg, अचिन्हित पूर्णांक pin,
			अचिन्हित पूर्णांक mode);
	व्योम (*spec_dir_set)(अचिन्हित पूर्णांक *reg_addr, अचिन्हित पूर्णांक pin);
	अचिन्हित पूर्णांक dir_offset;
	अचिन्हित पूर्णांक ies_offset;
	अचिन्हित पूर्णांक smt_offset;
	अचिन्हित पूर्णांक pullen_offset;
	अचिन्हित पूर्णांक pullsel_offset;
	अचिन्हित पूर्णांक drv_offset;
	अचिन्हित पूर्णांक करोut_offset;
	अचिन्हित पूर्णांक din_offset;
	अचिन्हित पूर्णांक pinmux_offset;
	अचिन्हित लघु type1_start;
	अचिन्हित लघु type1_end;
	अचिन्हित अक्षर  port_shf;
	अचिन्हित अक्षर  port_mask;
	अचिन्हित अक्षर  port_align;
	काष्ठा mtk_eपूर्णांक_hw eपूर्णांक_hw;
	काष्ठा mtk_eपूर्णांक_regs *eपूर्णांक_regs;
पूर्ण;

काष्ठा mtk_pinctrl अणु
	काष्ठा regmap	*regmap1;
	काष्ठा regmap	*regmap2;
	काष्ठा pinctrl_desc pctl_desc;
	काष्ठा device           *dev;
	काष्ठा gpio_chip	*chip;
	काष्ठा mtk_pinctrl_group	*groups;
	अचिन्हित			ngroups;
	स्थिर अक्षर          **grp_names;
	काष्ठा pinctrl_dev      *pctl_dev;
	स्थिर काष्ठा mtk_pinctrl_devdata  *devdata;
	काष्ठा mtk_eपूर्णांक *eपूर्णांक;
पूर्ण;

पूर्णांक mtk_pctrl_init(काष्ठा platक्रमm_device *pdev,
		स्थिर काष्ठा mtk_pinctrl_devdata *data,
		काष्ठा regmap *regmap);

पूर्णांक mtk_pctrl_spec_pull_set_samereg(काष्ठा regmap *regmap,
		स्थिर काष्ठा mtk_pin_spec_pupd_set_samereg *pupd_infos,
		अचिन्हित पूर्णांक info_num, अचिन्हित पूर्णांक pin,
		अचिन्हित अक्षर align, bool isup, अचिन्हित पूर्णांक r1r0);

पूर्णांक mtk_pconf_spec_set_ies_smt_range(काष्ठा regmap *regmap,
		स्थिर काष्ठा mtk_pin_ies_smt_set *ies_smt_infos, अचिन्हित पूर्णांक info_num,
		अचिन्हित पूर्णांक pin, अचिन्हित अक्षर align, पूर्णांक value);

बाह्य स्थिर काष्ठा dev_pm_ops mtk_eपूर्णांक_pm_ops;

#पूर्ण_अगर /* __PINCTRL_MTK_COMMON_H */
