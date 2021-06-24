<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * Copyright (C) 2021 थlvaro Fernथँndez Rojas <noltari@gmail.com>
 * Copyright (C) 2016 Jonas Gorski <jonas.gorski@gmail.com>
 */

#अगर_अघोषित __PINCTRL_BCM63XX_H__
#घोषणा __PINCTRL_BCM63XX_H__

#समावेश <linux/pinctrl/pinctrl.h>

#घोषणा BCM63XX_BANK_GPIOS 32

काष्ठा bcm63xx_pinctrl_soc अणु
	काष्ठा pinctrl_ops *pctl_ops;
	काष्ठा pinmux_ops *pmx_ops;

	स्थिर काष्ठा pinctrl_pin_desc *pins;
	अचिन्हित npins;

	अचिन्हित पूर्णांक ngpios;
पूर्ण;

काष्ठा bcm63xx_pinctrl अणु
	काष्ठा device *dev;
	काष्ठा regmap *regs;

	काष्ठा pinctrl_desc pctl_desc;
	काष्ठा pinctrl_dev *pctl_dev;

	व्योम *driver_data;
पूर्ण;

अटल अंतरभूत अचिन्हित पूर्णांक bcm63xx_bank_pin(अचिन्हित पूर्णांक pin)
अणु
	वापस pin % BCM63XX_BANK_GPIOS;
पूर्ण

पूर्णांक bcm63xx_pinctrl_probe(काष्ठा platक्रमm_device *pdev,
			  स्थिर काष्ठा bcm63xx_pinctrl_soc *soc,
			  व्योम *driver_data);

#पूर्ण_अगर /* __PINCTRL_BCM63XX_H__ */
