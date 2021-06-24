<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * MFD core driver क्रम the RT5033
 *
 * Copyright (C) 2014 Samsung Electronics
 * Author: Beomho Seo <beomho.seo@samsung.com>
 */

#अगर_अघोषित __RT5033_H__
#घोषणा __RT5033_H__

#समावेश <linux/regulator/consumer.h>
#समावेश <linux/i2c.h>
#समावेश <linux/regmap.h>
#समावेश <linux/घातer_supply.h>

/* RT5033 regulator IDs */
क्रमागत rt5033_regulators अणु
	RT5033_BUCK = 0,
	RT5033_LDO,
	RT5033_SAFE_LDO,

	RT5033_REGULATOR_NUM,
पूर्ण;

काष्ठा rt5033_dev अणु
	काष्ठा device *dev;

	काष्ठा regmap *regmap;
	काष्ठा regmap_irq_chip_data *irq_data;
	पूर्णांक irq;
	bool wakeup;
पूर्ण;

काष्ठा rt5033_battery अणु
	काष्ठा i2c_client	*client;
	काष्ठा rt5033_dev	*rt5033;
	काष्ठा regmap		*regmap;
	काष्ठा घातer_supply	*psy;
पूर्ण;

/* RT5033 अक्षरger platक्रमm data */
काष्ठा rt5033_अक्षरger_data अणु
	अचिन्हित पूर्णांक pre_uamp;
	अचिन्हित पूर्णांक pre_uvolt;
	अचिन्हित पूर्णांक स्थिर_uvolt;
	अचिन्हित पूर्णांक eoc_uamp;
	अचिन्हित पूर्णांक fast_uamp;
पूर्ण;

काष्ठा rt5033_अक्षरger अणु
	काष्ठा device		*dev;
	काष्ठा rt5033_dev	*rt5033;
	काष्ठा घातer_supply	psy;

	काष्ठा rt5033_अक्षरger_data	*chg;
पूर्ण;

#पूर्ण_अगर /* __RT5033_H__ */
