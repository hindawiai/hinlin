<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Header file क्रम device driver Hi6421 PMIC
 *
 * Copyright (c) <2011-2014> HiSilicon Technologies Co., Ltd.
 *              http://www.hisilicon.com
 * Copyright (c) <2013-2014> Linaro Ltd.
 *              https://www.linaro.org
 *
 * Author: Guoकरोng Xu <guoकरोng.xu@linaro.org>
 */

#अगर_अघोषित	__HI6421_PMIC_H
#घोषणा	__HI6421_PMIC_H

/* Hi6421 रेजिस्टरs are mapped to memory bus in 4 bytes stride */
#घोषणा HI6421_REG_TO_BUS_ADDR(x)	(x << 2)

/* Hi6421 maximum रेजिस्टर number */
#घोषणा HI6421_REG_MAX			0xFF

/* Hi6421 OCP (over current protection) and DEB (debounce) control रेजिस्टर */
#घोषणा	HI6421_OCP_DEB_CTRL_REG		HI6421_REG_TO_BUS_ADDR(0x51)
#घोषणा	HI6421_OCP_DEB_SEL_MASK		0x0C
#घोषणा HI6421_OCP_DEB_SEL_8MS		0x00
#घोषणा HI6421_OCP_DEB_SEL_16MS		0x04
#घोषणा HI6421_OCP_DEB_SEL_32MS		0x08
#घोषणा HI6421_OCP_DEB_SEL_64MS		0x0C
#घोषणा HI6421_OCP_EN_DEBOUNCE_MASK	0x02
#घोषणा HI6421_OCP_EN_DEBOUNCE_ENABLE	0x02
#घोषणा HI6421_OCP_AUTO_STOP_MASK	0x01
#घोषणा HI6421_OCP_AUTO_STOP_ENABLE	0x01

काष्ठा hi6421_pmic अणु
	काष्ठा regmap		*regmap;
पूर्ण;

क्रमागत hi6421_type अणु
	HI6421 = 0,
	HI6421_V530,
पूर्ण;

#पूर्ण_अगर		/* __HI6421_PMIC_H */
