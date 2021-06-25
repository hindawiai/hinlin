<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Header file क्रम device driver Hi6421 PMIC
 *
 * Copyright (c) 2013 Linaro Ltd.
 * Copyright (C) 2011 Hisilicon.
 * Copyright (c) 2020-2021 Huawei Technologies Co., Ltd
 *
 * Guoकरोng Xu <guoकरोng.xu@linaro.org>
 */

#अगर_अघोषित	__HISI_PMIC_H
#घोषणा	__HISI_PMIC_H

#समावेश <linux/irqकरोमुख्य.h>
#समावेश <linux/regmap.h>

काष्ठा hi6421_spmi_pmic अणु
	काष्ठा resource				*res;
	काष्ठा device				*dev;
	व्योम __iomem				*regs;
	spinlock_t				lock;
	काष्ठा irq_करोमुख्य			*करोमुख्य;
	पूर्णांक					irq;
	पूर्णांक					gpio;
	अचिन्हित पूर्णांक				*irqs;
	काष्ठा regmap				*regmap;
पूर्ण;

#पूर्ण_अगर		/* __HISI_PMIC_H */
