<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Copyright (C) Maxime Coquelin 2015
 * Copyright (C) STMicroelectronics 2017
 * Author:  Maxime Coquelin <mcoquelin.sपंचांग32@gmail.com>
 */
#अगर_अघोषित __PINCTRL_STM32_H
#घोषणा __PINCTRL_STM32_H

#समावेश <linux/pinctrl/pinctrl.h>
#समावेश <linux/pinctrl/pinconf-generic.h>

#घोषणा STM32_PIN_NO(x) ((x) << 8)
#घोषणा STM32_GET_PIN_NO(x) ((x) >> 8)
#घोषणा STM32_GET_PIN_FUNC(x) ((x) & 0xff)

#घोषणा STM32_PIN_GPIO		0
#घोषणा STM32_PIN_AF(x)		((x) + 1)
#घोषणा STM32_PIN_ANALOG	(STM32_PIN_AF(15) + 1)

/*  package inक्रमmation */
#घोषणा STM32MP_PKG_AA		BIT(0)
#घोषणा STM32MP_PKG_AB		BIT(1)
#घोषणा STM32MP_PKG_AC		BIT(2)
#घोषणा STM32MP_PKG_AD		BIT(3)

काष्ठा sपंचांग32_desc_function अणु
	स्थिर अक्षर *name;
	स्थिर अचिन्हित अक्षर num;
पूर्ण;

काष्ठा sपंचांग32_desc_pin अणु
	काष्ठा pinctrl_pin_desc pin;
	स्थिर काष्ठा sपंचांग32_desc_function *functions;
	स्थिर अचिन्हित पूर्णांक pkg;
पूर्ण;

#घोषणा STM32_PIN(_pin, ...)					\
	अणु							\
		.pin = _pin,					\
		.functions = (काष्ठा sपंचांग32_desc_function[])अणु	\
			__VA_ARGS__, अणु पूर्ण पूर्ण,			\
	पूर्ण

#घोषणा STM32_PIN_PKG(_pin, _pkg, ...)					\
	अणु							\
		.pin = _pin,					\
		.pkg  = _pkg,				\
		.functions = (काष्ठा sपंचांग32_desc_function[])अणु	\
			__VA_ARGS__, अणु पूर्ण पूर्ण,			\
	पूर्ण
#घोषणा STM32_FUNCTION(_num, _name)		\
	अणु							\
		.num = _num,					\
		.name = _name,					\
	पूर्ण

काष्ठा sपंचांग32_pinctrl_match_data अणु
	स्थिर काष्ठा sपंचांग32_desc_pin *pins;
	स्थिर अचिन्हित पूर्णांक npins;
पूर्ण;

काष्ठा sपंचांग32_gpio_bank;

पूर्णांक sपंचांग32_pctl_probe(काष्ठा platक्रमm_device *pdev);
व्योम sपंचांग32_pmx_get_mode(काष्ठा sपंचांग32_gpio_bank *bank,
			पूर्णांक pin, u32 *mode, u32 *alt);
पूर्णांक sपंचांग32_pinctrl_resume(काष्ठा device *dev);

#पूर्ण_अगर /* __PINCTRL_STM32_H */

