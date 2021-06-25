<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * AD7879/AD7889 touchscreen (bus पूर्णांकerfaces)
 *
 * Copyright (C) 2008-2010 Michael Hennerich, Analog Devices Inc.
 */

#अगर_अघोषित _AD7879_H_
#घोषणा _AD7879_H_

#समावेश <linux/types.h>

काष्ठा device;
काष्ठा regmap;

बाह्य स्थिर काष्ठा dev_pm_ops ad7879_pm_ops;

पूर्णांक ad7879_probe(काष्ठा device *dev, काष्ठा regmap *regmap,
		 पूर्णांक irq, u16 bustype, u8 devid);

#पूर्ण_अगर
