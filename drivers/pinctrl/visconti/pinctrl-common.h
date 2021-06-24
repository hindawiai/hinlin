<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Copyright (c) 2020 TOSHIBA CORPORATION
 * Copyright (c) 2020 Toshiba Electronic Devices & Storage Corporation
 * Copyright (c) 2020 Nobuhiro Iwamatsu <nobuhiro1.iwamatsu@toshiba.co.jp>
 */

#अगर_अघोषित __VISCONTI_PINCTRL_COMMON_H__
#घोषणा __VISCONTI_PINCTRL_COMMON_H__

काष्ठा pinctrl_pin_desc;

/* PIN */
#घोषणा VISCONTI_PINS(pins_name, ...)  \
	अटल स्थिर अचिन्हित पूर्णांक pins_name ## _pins[] = अणु __VA_ARGS__ पूर्ण

काष्ठा visconti_desc_pin अणु
	काष्ठा pinctrl_pin_desc pin;
	अचिन्हित पूर्णांक dsel_offset;
	अचिन्हित पूर्णांक dsel_shअगरt;
	अचिन्हित पूर्णांक pude_offset;
	अचिन्हित पूर्णांक pudsel_offset;
	अचिन्हित पूर्णांक pud_shअगरt;
पूर्ण;

#घोषणा VISCONTI_PIN(_pin, dsel, d_sh, pude, pudsel, p_sh)	\
अणु								\
	.pin = _pin,						\
	.dsel_offset = dsel,					\
	.dsel_shअगरt = d_sh,					\
	.pude_offset = pude,					\
	.pudsel_offset = pudsel,				\
	.pud_shअगरt = p_sh,					\
पूर्ण

/* Group */
#घोषणा VISCONTI_GROUPS(groups_name, ...)	\
	अटल स्थिर अक्षर * स्थिर groups_name ## _grps[] = अणु __VA_ARGS__ पूर्ण

काष्ठा visconti_mux अणु
	अचिन्हित पूर्णांक offset;
	अचिन्हित पूर्णांक mask;
	अचिन्हित पूर्णांक val;
पूर्ण;

काष्ठा visconti_pin_group अणु
	स्थिर अक्षर *name;
	स्थिर अचिन्हित पूर्णांक *pins;
	अचिन्हित पूर्णांक nr_pins;
	काष्ठा visconti_mux mux;
पूर्ण;

#घोषणा VISCONTI_PIN_GROUP(group_name, off, msk, v)	\
अणु							\
	.name = __stringअगरy(group_name) "_grp",		\
	.pins = group_name ## _pins,			\
	.nr_pins = ARRAY_SIZE(group_name ## _pins),	\
	.mux = अणु					\
		.offset = off,				\
		.mask = msk,				\
		.val = v,				\
	पूर्ण						\
पूर्ण

/* MUX */
काष्ठा visconti_pin_function अणु
	स्थिर अक्षर *name;
	स्थिर अक्षर * स्थिर *groups;
	अचिन्हित पूर्णांक nr_groups;
पूर्ण;

#घोषणा VISCONTI_PIN_FUNCTION(func)		\
अणु						\
	.name = #func,				\
	.groups = func ## _grps,		\
	.nr_groups = ARRAY_SIZE(func ## _grps),	\
पूर्ण

/* chip dependent data */
काष्ठा visconti_pinctrl_devdata अणु
	स्थिर काष्ठा visconti_desc_pin *pins;
	अचिन्हित पूर्णांक nr_pins;
	स्थिर काष्ठा visconti_pin_group *groups;
	अचिन्हित पूर्णांक nr_groups;
	स्थिर काष्ठा visconti_pin_function *functions;
	अचिन्हित पूर्णांक nr_functions;

	स्थिर काष्ठा visconti_mux *gpio_mux;

	व्योम (*unlock)(व्योम __iomem *base);
पूर्ण;

पूर्णांक visconti_pinctrl_probe(काष्ठा platक्रमm_device *pdev,
			   स्थिर काष्ठा visconti_pinctrl_devdata *devdata);

#पूर्ण_अगर /* __VISCONTI_PINCTRL_COMMON_H__ */
