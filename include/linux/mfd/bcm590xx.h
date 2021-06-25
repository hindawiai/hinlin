<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * Broadcom BCM590xx PMU
 *
 * Copyright 2014 Linaro Limited
 * Author: Matt Porter <mporter@linaro.org>
 */

#अगर_अघोषित __LINUX_MFD_BCM590XX_H
#घोषणा __LINUX_MFD_BCM590XX_H

#समावेश <linux/device.h>
#समावेश <linux/i2c.h>
#समावेश <linux/regmap.h>

/* max रेजिस्टर address */
#घोषणा BCM590XX_MAX_REGISTER_PRI	0xe7
#घोषणा BCM590XX_MAX_REGISTER_SEC	0xf0

काष्ठा bcm590xx अणु
	काष्ठा device *dev;
	काष्ठा i2c_client *i2c_pri;
	काष्ठा i2c_client *i2c_sec;
	काष्ठा regmap *regmap_pri;
	काष्ठा regmap *regmap_sec;
	अचिन्हित पूर्णांक id;
पूर्ण;

#पूर्ण_अगर /*  __LINUX_MFD_BCM590XX_H */
