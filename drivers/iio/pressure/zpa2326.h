<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Murata ZPA2326 pressure and temperature sensor IIO driver
 *
 * Copyright (c) 2016 Parrot S.A.
 *
 * Author: Gregor Boirie <gregor.boirie@parrot.com>
 */

#अगर_अघोषित _ZPA2326_H
#घोषणा _ZPA2326_H

/* Register map. */
#घोषणा ZPA2326_REF_P_XL_REG              (0x8)
#घोषणा ZPA2326_REF_P_L_REG               (0x9)
#घोषणा ZPA2326_REF_P_H_REG               (0xa)
#घोषणा ZPA2326_DEVICE_ID_REG             (0xf)
#घोषणा ZPA2326_DEVICE_ID                 (0xb9)
#घोषणा ZPA2326_RES_CONF_REG              (0x10)
#घोषणा ZPA2326_CTRL_REG0_REG             (0x20)
#घोषणा ZPA2326_CTRL_REG0_ONE_SHOT        BIT(0)
#घोषणा ZPA2326_CTRL_REG0_ENABLE          BIT(1)
#घोषणा ZPA2326_CTRL_REG1_REG             (0x21)
#घोषणा ZPA2326_CTRL_REG1_MASK_DATA_READY BIT(2)
#घोषणा ZPA2326_CTRL_REG2_REG             (0x22)
#घोषणा ZPA2326_CTRL_REG2_SWRESET         BIT(2)
#घोषणा ZPA2326_CTRL_REG3_REG             (0x23)
#घोषणा ZPA2326_CTRL_REG3_ODR_SHIFT       (4)
#घोषणा ZPA2326_CTRL_REG3_ENABLE_MEAS     BIT(7)
#घोषणा ZPA2326_INT_SOURCE_REG            (0x24)
#घोषणा ZPA2326_INT_SOURCE_DATA_READY     BIT(2)
#घोषणा ZPA2326_THS_P_LOW_REG             (0x25)
#घोषणा ZPA2326_THS_P_HIGH_REG            (0x26)
#घोषणा ZPA2326_STATUS_REG                (0x27)
#घोषणा ZPA2326_STATUS_P_DA               BIT(1)
#घोषणा ZPA2326_STATUS_FIFO_E             BIT(2)
#घोषणा ZPA2326_STATUS_P_OR               BIT(5)
#घोषणा ZPA2326_PRESS_OUT_XL_REG          (0x28)
#घोषणा ZPA2326_PRESS_OUT_L_REG           (0x29)
#घोषणा ZPA2326_PRESS_OUT_H_REG           (0x2a)
#घोषणा ZPA2326_TEMP_OUT_L_REG            (0x2b)
#घोषणा ZPA2326_TEMP_OUT_H_REG            (0x2c)

काष्ठा device;
काष्ठा regmap;

bool zpa2326_isreg_ग_लिखोable(काष्ठा device *dev, अचिन्हित पूर्णांक reg);
bool zpa2326_isreg_पढ़ोable(काष्ठा device *dev, अचिन्हित पूर्णांक reg);
bool zpa2326_isreg_precious(काष्ठा device *dev, अचिन्हित पूर्णांक reg);

/**
 * zpa2326_probe() - Instantiate and रेजिस्टर core ZPA2326 IIO device
 * @parent: Hardware sampling device the created IIO device will be a child of.
 * @name:   Arbitrary name to identअगरy the device.
 * @irq:    Interrupt line, negative अगर none.
 * @hwid:   Expected device hardware id.
 * @regmap: Registers map used to असलtract underlying bus accesses.
 *
 * Return: Zero when successful, a negative error code otherwise.
 */
पूर्णांक zpa2326_probe(काष्ठा device        *parent,
		  स्थिर अक्षर           *name,
		  पूर्णांक                   irq,
		  अचिन्हित पूर्णांक          hwid,
		  काष्ठा regmap        *regmap);

/**
 * zpa2326_हटाओ() - Unरेजिस्टर and destroy core ZPA2326 IIO device.
 * @parent: Hardware sampling device the IIO device to हटाओ is a child of.
 */
व्योम zpa2326_हटाओ(स्थिर काष्ठा device *parent);

#अगर_घोषित CONFIG_PM
#समावेश <linux/pm.h>
बाह्य स्थिर काष्ठा dev_pm_ops zpa2326_pm_ops;
#घोषणा ZPA2326_PM_OPS (&zpa2326_pm_ops)
#अन्यथा
#घोषणा ZPA2326_PM_OPS (शून्य)
#पूर्ण_अगर

#पूर्ण_अगर
