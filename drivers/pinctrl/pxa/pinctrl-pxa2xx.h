<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Marvell PXA2xx family pin control
 *
 * Copyright (C) 2015 Robert Jarzmik
 */

#अगर_अघोषित __PINCTRL_PXA_H
#घोषणा __PINCTRL_PXA_H

#घोषणा PXA_FUNCTION(_dir, _af, _name)				\
	अणु							\
		.name = _name,					\
		.muxval = (_dir | (_af << 1)),			\
	पूर्ण

#घोषणा PXA_PIN(_pin, funcs...)					\
	अणु							\
		.pin = _pin,					\
		.functions = (काष्ठा pxa_desc_function[])अणु	\
			funcs, अणु पूर्ण पूर्ण,				\
	पूर्ण

#घोषणा PXA_GPIO_PIN(_pin, funcs...)				\
	अणु							\
		.pin = _pin,					\
		.functions = (काष्ठा pxa_desc_function[])अणु	\
			PXA_FUNCTION(0, 0, "gpio_in"),		\
			PXA_FUNCTION(1, 0, "gpio_out"),		\
			funcs, अणु पूर्ण पूर्ण,				\
	पूर्ण

#घोषणा PXA_GPIO_ONLY_PIN(_pin)					\
	अणु							\
		.pin = _pin,					\
		.functions = (काष्ठा pxa_desc_function[])अणु	\
			PXA_FUNCTION(0, 0, "gpio_in"),		\
			PXA_FUNCTION(1, 0, "gpio_out"),		\
			अणु पूर्ण पूर्ण,					\
	पूर्ण

#घोषणा PXA_PINCTRL_PIN(pin)		\
	PINCTRL_PIN(pin, "P" #pin)

काष्ठा pxa_desc_function अणु
	स्थिर अक्षर	*name;
	u8		muxval;
पूर्ण;

काष्ठा pxa_desc_pin अणु
	काष्ठा pinctrl_pin_desc		pin;
	काष्ठा pxa_desc_function	*functions;
पूर्ण;

काष्ठा pxa_pinctrl_group अणु
	स्थिर अक्षर	*name;
	अचिन्हित	pin;
पूर्ण;

काष्ठा pxa_pinctrl_function अणु
	स्थिर अक्षर	*name;
	स्थिर अक्षर	**groups;
	अचिन्हित	ngroups;
पूर्ण;

काष्ठा pxa_pinctrl अणु
	spinlock_t			lock;
	व्योम __iomem			**base_gafr;
	व्योम __iomem			**base_gpdr;
	व्योम __iomem			**base_pgsr;
	काष्ठा device			*dev;
	काष्ठा pinctrl_desc		desc;
	काष्ठा pinctrl_dev		*pctl_dev;
	अचिन्हित			npins;
	स्थिर काष्ठा pxa_desc_pin	*ppins;
	अचिन्हित			ngroups;
	काष्ठा pxa_pinctrl_group	*groups;
	अचिन्हित			nfuncs;
	काष्ठा pxa_pinctrl_function	*functions;
	अक्षर				*name;
पूर्ण;

पूर्णांक pxa2xx_pinctrl_init(काष्ठा platक्रमm_device *pdev,
			स्थिर काष्ठा pxa_desc_pin *ppins, पूर्णांक npins,
			व्योम __iomem *base_gafr[], व्योम __iomem *base_gpdr[],
			व्योम __iomem *base_gpsr[]);

#पूर्ण_अगर /* __PINCTRL_PXA_H */
