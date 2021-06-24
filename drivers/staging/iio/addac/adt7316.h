<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0+ */
/*
 * ADT7316 digital temperature sensor driver supporting ADT7316/7/8 ADT7516/7/9
 *
 * Copyright 2010 Analog Devices Inc.
 */

#अगर_अघोषित _ADT7316_H_
#घोषणा _ADT7316_H_

#समावेश <linux/types.h>
#समावेश <linux/pm.h>

#घोषणा ADT7316_REG_MAX_ADDR		0x3F

काष्ठा adt7316_bus अणु
	व्योम *client;
	पूर्णांक irq;
	पूर्णांक (*पढ़ो)(व्योम *client, u8 reg, u8 *data);
	पूर्णांक (*ग_लिखो)(व्योम *client, u8 reg, u8 val);
	पूर्णांक (*multi_पढ़ो)(व्योम *client, u8 first_reg, u8 count, u8 *data);
	पूर्णांक (*multi_ग_लिखो)(व्योम *client, u8 first_reg, u8 count, u8 *data);
पूर्ण;

#अगर_घोषित CONFIG_PM_SLEEP
बाह्य स्थिर काष्ठा dev_pm_ops adt7316_pm_ops;
#घोषणा ADT7316_PM_OPS (&adt7316_pm_ops)
#अन्यथा
#घोषणा ADT7316_PM_OPS शून्य
#पूर्ण_अगर
पूर्णांक adt7316_probe(काष्ठा device *dev, काष्ठा adt7316_bus *bus,
		  स्थिर अक्षर *name);

#पूर्ण_अगर
