<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित __I2C_OMAP_H__
#घोषणा __I2C_OMAP_H__

#समावेश <linux/platक्रमm_device.h>

/*
 * Version 2 of the I2C peripheral unit has a dअगरferent रेजिस्टर
 * layout and extra रेजिस्टरs.  The ID रेजिस्टर in the V2 peripheral
 * unit on the OMAP4430 reports the same ID as the V1 peripheral
 * unit on the OMAP3530, so we must inक्रमm the driver which IP
 * version we know it is running on from platक्रमm / cpu-specअगरic
 * code using these स्थिरants in the hwmod class definition.
 */

#घोषणा OMAP_I2C_IP_VERSION_1 1
#घोषणा OMAP_I2C_IP_VERSION_2 2

/* काष्ठा omap_i2c_bus_platक्रमm_data .flags meanings */

#घोषणा OMAP_I2C_FLAG_NO_FIFO			BIT(0)
#घोषणा OMAP_I2C_FLAG_SIMPLE_CLOCK		BIT(1)
#घोषणा OMAP_I2C_FLAG_16BIT_DATA_REG		BIT(2)
#घोषणा OMAP_I2C_FLAG_ALWAYS_ARMXOR_CLK	BIT(5)
#घोषणा OMAP_I2C_FLAG_FORCE_19200_INT_CLK	BIT(6)
/* how the CPU address bus must be translated क्रम I2C unit access */
#घोषणा OMAP_I2C_FLAG_BUS_SHIFT_NONE 0
#घोषणा OMAP_I2C_FLAG_BUS_SHIFT_1		BIT(7)
#घोषणा OMAP_I2C_FLAG_BUS_SHIFT_2		BIT(8)
#घोषणा OMAP_I2C_FLAG_BUS_SHIFT__SHIFT 7

काष्ठा omap_i2c_bus_platक्रमm_data अणु
	u32		clkrate;
	u32		rev;
	u32		flags;
	व्योम		(*set_mpu_wkup_lat)(काष्ठा device *dev, दीर्घ set);
पूर्ण;

#पूर्ण_अगर
