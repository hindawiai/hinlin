<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * NXP ISP1301 USB transceiver driver
 *
 * Copyright (C) 2012 Roland Stigge <stigge@antcom.de>
 *
 * This program is मुक्त software; you can redistribute it and/or modअगरy
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; version 2 of the License.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License क्रम more details.
 *
 */

#अगर_अघोषित __LINUX_USB_ISP1301_H
#घोषणा __LINUX_USB_ISP1301_H

#समावेश <linux/of.h>

/* I2C Register definitions: */

#घोषणा ISP1301_I2C_MODE_CONTROL_1	0x04	/* u8 पढ़ो, set, +1 clear */

#घोषणा MC1_SPEED_REG			(1 << 0)
#घोषणा MC1_SUSPEND_REG			(1 << 1)
#घोषणा MC1_DAT_SE0			(1 << 2)
#घोषणा MC1_TRANSPARENT			(1 << 3)
#घोषणा MC1_BDIS_ACON_EN		(1 << 4)
#घोषणा MC1_OE_INT_EN			(1 << 5)
#घोषणा MC1_UART_EN			(1 << 6)
#घोषणा MC1_MASK			0x7f

#घोषणा ISP1301_I2C_MODE_CONTROL_2	0x12	/* u8 पढ़ो, set, +1 clear */

#घोषणा MC2_GLOBAL_PWR_DN		(1 << 0)
#घोषणा MC2_SPD_SUSP_CTRL		(1 << 1)
#घोषणा MC2_BI_DI			(1 << 2)
#घोषणा MC2_TRANSP_Bसूची0		(1 << 3)
#घोषणा MC2_TRANSP_Bसूची1		(1 << 4)
#घोषणा MC2_AUDIO_EN			(1 << 5)
#घोषणा MC2_PSW_EN			(1 << 6)
#घोषणा MC2_EN2V7			(1 << 7)

#घोषणा ISP1301_I2C_OTG_CONTROL_1	0x06	/* u8 पढ़ो, set, +1 clear */

#घोषणा OTG1_DP_PULLUP			(1 << 0)
#घोषणा OTG1_DM_PULLUP			(1 << 1)
#घोषणा OTG1_DP_PULLDOWN		(1 << 2)
#घोषणा OTG1_DM_PULLDOWN		(1 << 3)
#घोषणा OTG1_ID_PULLDOWN		(1 << 4)
#घोषणा OTG1_VBUS_DRV			(1 << 5)
#घोषणा OTG1_VBUS_DISCHRG		(1 << 6)
#घोषणा OTG1_VBUS_CHRG			(1 << 7)

#घोषणा ISP1301_I2C_OTG_CONTROL_2	0x10	/* u8 पढ़ोonly */

#घोषणा OTG_B_SESS_END			(1 << 6)
#घोषणा OTG_B_SESS_VLD			(1 << 7)

#घोषणा ISP1301_I2C_INTERRUPT_SOURCE	0x8
#घोषणा ISP1301_I2C_INTERRUPT_LATCH	0xA
#घोषणा ISP1301_I2C_INTERRUPT_FALLING	0xC
#घोषणा ISP1301_I2C_INTERRUPT_RISING	0xE

#घोषणा INT_VBUS_VLD			(1 << 0)
#घोषणा INT_SESS_VLD			(1 << 1)
#घोषणा INT_DP_HI			(1 << 2)
#घोषणा INT_ID_GND			(1 << 3)
#घोषणा INT_DM_HI			(1 << 4)
#घोषणा INT_ID_FLOAT			(1 << 5)
#घोषणा INT_BDIS_ACON			(1 << 6)
#घोषणा INT_CR_INT			(1 << 7)

#घोषणा ISP1301_I2C_REG_CLEAR_ADDR	1	/* Register Address Modअगरier */

काष्ठा i2c_client *isp1301_get_client(काष्ठा device_node *node);

#पूर्ण_अगर /* __LINUX_USB_ISP1301_H */
