<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0+ */
/*
 * Copyright (C) 2015-2017 Socionext Inc.
 *   Author: Masahiro Yamada <yamada.masahiro@socionext.com>
 */

#अगर_अघोषित __PINCTRL_UNIPHIER_H__
#घोषणा __PINCTRL_UNIPHIER_H__

#समावेश <linux/bits.h>
#समावेश <linux/build_bug.h>
#समावेश <linux/kernel.h>
#समावेश <linux/types.h>

काष्ठा platक्रमm_device;

/* input enable control रेजिस्टर bit */
#घोषणा UNIPHIER_PIN_IECTRL_SHIFT	0
#घोषणा UNIPHIER_PIN_IECTRL_BITS	3
#घोषणा UNIPHIER_PIN_IECTRL_MASK	((1UL << (UNIPHIER_PIN_IECTRL_BITS)) \
					 - 1)

/* drive strength control रेजिस्टर number */
#घोषणा UNIPHIER_PIN_DRVCTRL_SHIFT	((UNIPHIER_PIN_IECTRL_SHIFT) + \
					(UNIPHIER_PIN_IECTRL_BITS))
#घोषणा UNIPHIER_PIN_DRVCTRL_BITS	9
#घोषणा UNIPHIER_PIN_DRVCTRL_MASK	((1UL << (UNIPHIER_PIN_DRVCTRL_BITS)) \
					 - 1)

/* drive control type */
#घोषणा UNIPHIER_PIN_DRV_TYPE_SHIFT	((UNIPHIER_PIN_DRVCTRL_SHIFT) + \
					 (UNIPHIER_PIN_DRVCTRL_BITS))
#घोषणा UNIPHIER_PIN_DRV_TYPE_BITS	3
#घोषणा UNIPHIER_PIN_DRV_TYPE_MASK	((1UL << (UNIPHIER_PIN_DRV_TYPE_BITS)) \
					 - 1)

/* pull-up / pull-करोwn रेजिस्टर number */
#घोषणा UNIPHIER_PIN_PUPDCTRL_SHIFT	((UNIPHIER_PIN_DRV_TYPE_SHIFT) + \
					 (UNIPHIER_PIN_DRV_TYPE_BITS))
#घोषणा UNIPHIER_PIN_PUPDCTRL_BITS	9
#घोषणा UNIPHIER_PIN_PUPDCTRL_MASK	((1UL << (UNIPHIER_PIN_PUPDCTRL_BITS))\
					 - 1)

/* direction of pull रेजिस्टर */
#घोषणा UNIPHIER_PIN_PULL_सूची_SHIFT	((UNIPHIER_PIN_PUPDCTRL_SHIFT) + \
					 (UNIPHIER_PIN_PUPDCTRL_BITS))
#घोषणा UNIPHIER_PIN_PULL_सूची_BITS	3
#घोषणा UNIPHIER_PIN_PULL_सूची_MASK	((1UL << (UNIPHIER_PIN_PULL_सूची_BITS))\
					 - 1)

#अगर UNIPHIER_PIN_PULL_सूची_SHIFT + UNIPHIER_PIN_PULL_सूची_BITS > BITS_PER_LONG
#त्रुटि "unable to pack pin attributes."
#पूर्ण_अगर

#घोषणा UNIPHIER_PIN_IECTRL_NONE	(UNIPHIER_PIN_IECTRL_MASK)
#घोषणा UNIPHIER_PIN_IECTRL_EXIST	0

/* drive control type */
क्रमागत uniphier_pin_drv_type अणु
	UNIPHIER_PIN_DRV_1BIT,		/* 2 level control: 4/8 mA */
	UNIPHIER_PIN_DRV_2BIT,		/* 4 level control: 8/12/16/20 mA */
	UNIPHIER_PIN_DRV_3BIT,		/* 8 level control: 4/5/7/9/11/12/14/16 mA */
	UNIPHIER_PIN_DRV_FIXED4,	/* fixed to 4mA */
	UNIPHIER_PIN_DRV_FIXED5,	/* fixed to 5mA */
	UNIPHIER_PIN_DRV_FIXED8,	/* fixed to 8mA */
	UNIPHIER_PIN_DRV_NONE,		/* no support (input only pin) */
पूर्ण;

/* direction of pull रेजिस्टर (no pin supports bi-directional pull biasing) */
क्रमागत uniphier_pin_pull_dir अणु
	UNIPHIER_PIN_PULL_UP,		/* pull-up or disabled */
	UNIPHIER_PIN_PULL_DOWN,		/* pull-करोwn or disabled */
	UNIPHIER_PIN_PULL_UP_FIXED,	/* always pull-up */
	UNIPHIER_PIN_PULL_DOWN_FIXED,	/* always pull-करोwn */
	UNIPHIER_PIN_PULL_NONE,		/* no pull रेजिस्टर */
पूर्ण;

#घोषणा UNIPHIER_PIN_IECTRL(x) \
	(((x) & (UNIPHIER_PIN_IECTRL_MASK)) << (UNIPHIER_PIN_IECTRL_SHIFT))
#घोषणा UNIPHIER_PIN_DRVCTRL(x) \
	(((x) & (UNIPHIER_PIN_DRVCTRL_MASK)) << (UNIPHIER_PIN_DRVCTRL_SHIFT))
#घोषणा UNIPHIER_PIN_DRV_TYPE(x) \
	(((x) & (UNIPHIER_PIN_DRV_TYPE_MASK)) << (UNIPHIER_PIN_DRV_TYPE_SHIFT))
#घोषणा UNIPHIER_PIN_PUPDCTRL(x) \
	(((x) & (UNIPHIER_PIN_PUPDCTRL_MASK)) << (UNIPHIER_PIN_PUPDCTRL_SHIFT))
#घोषणा UNIPHIER_PIN_PULL_सूची(x) \
	(((x) & (UNIPHIER_PIN_PULL_सूची_MASK)) << (UNIPHIER_PIN_PULL_सूची_SHIFT))

#घोषणा UNIPHIER_PIN_ATTR_PACKED(iectrl, drvctrl, drv_type, pupdctrl, pull_dir)\
				(UNIPHIER_PIN_IECTRL(iectrl) |		\
				 UNIPHIER_PIN_DRVCTRL(drvctrl) |	\
				 UNIPHIER_PIN_DRV_TYPE(drv_type) |	\
				 UNIPHIER_PIN_PUPDCTRL(pupdctrl) |	\
				 UNIPHIER_PIN_PULL_सूची(pull_dir))

अटल अंतरभूत अचिन्हित पूर्णांक uniphier_pin_get_iectrl(व्योम *drv_data)
अणु
	वापस ((अचिन्हित दीर्घ)drv_data >> UNIPHIER_PIN_IECTRL_SHIFT) &
						UNIPHIER_PIN_IECTRL_MASK;
पूर्ण

अटल अंतरभूत अचिन्हित पूर्णांक uniphier_pin_get_drvctrl(व्योम *drv_data)
अणु
	वापस ((अचिन्हित दीर्घ)drv_data >> UNIPHIER_PIN_DRVCTRL_SHIFT) &
						UNIPHIER_PIN_DRVCTRL_MASK;
पूर्ण

अटल अंतरभूत अचिन्हित पूर्णांक uniphier_pin_get_drv_type(व्योम *drv_data)
अणु
	वापस ((अचिन्हित दीर्घ)drv_data >> UNIPHIER_PIN_DRV_TYPE_SHIFT) &
						UNIPHIER_PIN_DRV_TYPE_MASK;
पूर्ण

अटल अंतरभूत अचिन्हित पूर्णांक uniphier_pin_get_pupdctrl(व्योम *drv_data)
अणु
	वापस ((अचिन्हित दीर्घ)drv_data >> UNIPHIER_PIN_PUPDCTRL_SHIFT) &
						UNIPHIER_PIN_PUPDCTRL_MASK;
पूर्ण

अटल अंतरभूत अचिन्हित पूर्णांक uniphier_pin_get_pull_dir(व्योम *drv_data)
अणु
	वापस ((अचिन्हित दीर्घ)drv_data >> UNIPHIER_PIN_PULL_सूची_SHIFT) &
						UNIPHIER_PIN_PULL_सूची_MASK;
पूर्ण

काष्ठा uniphier_pinctrl_group अणु
	स्थिर अक्षर *name;
	स्थिर अचिन्हित *pins;
	अचिन्हित num_pins;
	स्थिर पूर्णांक *muxvals;
पूर्ण;

काष्ठा uniphier_pinmux_function अणु
	स्थिर अक्षर *name;
	स्थिर अक्षर * स्थिर *groups;
	अचिन्हित num_groups;
पूर्ण;

काष्ठा uniphier_pinctrl_socdata अणु
	स्थिर काष्ठा pinctrl_pin_desc *pins;
	अचिन्हित पूर्णांक npins;
	स्थिर काष्ठा uniphier_pinctrl_group *groups;
	पूर्णांक groups_count;
	स्थिर काष्ठा uniphier_pinmux_function *functions;
	पूर्णांक functions_count;
	पूर्णांक (*get_gpio_muxval)(अचिन्हित पूर्णांक pin, अचिन्हित पूर्णांक gpio_offset);
	अचिन्हित पूर्णांक caps;
#घोषणा UNIPHIER_PINCTRL_CAPS_PERPIN_IECTRL	BIT(1)
#घोषणा UNIPHIER_PINCTRL_CAPS_DBGMUX_SEPARATE	BIT(0)
पूर्ण;

#घोषणा UNIPHIER_PINCTRL_PIN(a, b, c, d, e, f, g)			\
अणु									\
	.number = a,							\
	.name = b,							\
	.drv_data = (व्योम *)UNIPHIER_PIN_ATTR_PACKED(c, d, e, f, g),	\
पूर्ण

#घोषणा __UNIPHIER_PINCTRL_GROUP(grp, mux)				\
	अणु								\
		.name = #grp,						\
		.pins = grp##_pins,					\
		.num_pins = ARRAY_SIZE(grp##_pins),			\
		.muxvals = mux,						\
	पूर्ण

#घोषणा UNIPHIER_PINCTRL_GROUP(grp)					\
	__UNIPHIER_PINCTRL_GROUP(grp,					\
			grp##_muxvals +					\
			BUILD_BUG_ON_ZERO(ARRAY_SIZE(grp##_pins) !=	\
					  ARRAY_SIZE(grp##_muxvals)))

#घोषणा UNIPHIER_PINCTRL_GROUP_GPIO(grp)				\
	__UNIPHIER_PINCTRL_GROUP(grp, शून्य)

#घोषणा UNIPHIER_PINMUX_FUNCTION(func)					\
	अणु								\
		.name = #func,						\
		.groups = func##_groups,				\
		.num_groups = ARRAY_SIZE(func##_groups),		\
	पूर्ण

पूर्णांक uniphier_pinctrl_probe(काष्ठा platक्रमm_device *pdev,
			   स्थिर काष्ठा uniphier_pinctrl_socdata *socdata);

बाह्य स्थिर काष्ठा dev_pm_ops uniphier_pinctrl_pm_ops;

#पूर्ण_अगर /* __PINCTRL_UNIPHIER_H__ */
