<शैली गुरु>
/*
 * Copyright (C) 2015 Texas Instruments Incorporated - https://www.ti.com/
 *	Andrew F. Davis <afd@ti.com>
 *
 * This program is मुक्त software; you can redistribute it and/or
 * modअगरy it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 *
 * This program is distributed "as is" WITHOUT ANY WARRANTY of any
 * kind, whether expressed or implied; without even the implied warranty
 * of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License version 2 क्रम more details.
 *
 * Based on the TPS65912 driver
 */

#अगर_अघोषित __LINUX_MFD_TPS65086_H
#घोषणा __LINUX_MFD_TPS65086_H

#समावेश <linux/device.h>
#समावेश <linux/regmap.h>

/* List of रेजिस्टरs क्रम TPS65086 */
#घोषणा TPS65086_DEVICEID		0x01
#घोषणा TPS65086_IRQ			0x02
#घोषणा TPS65086_IRQ_MASK		0x03
#घोषणा TPS65086_PMICSTAT		0x04
#घोषणा TPS65086_SHUTDNSRC		0x05
#घोषणा TPS65086_BUCK1CTRL		0x20
#घोषणा TPS65086_BUCK2CTRL		0x21
#घोषणा TPS65086_BUCK3DECAY		0x22
#घोषणा TPS65086_BUCK3VID		0x23
#घोषणा TPS65086_BUCK3SLPCTRL		0x24
#घोषणा TPS65086_BUCK4CTRL		0x25
#घोषणा TPS65086_BUCK5CTRL		0x26
#घोषणा TPS65086_BUCK6CTRL		0x27
#घोषणा TPS65086_LDOA2CTRL		0x28
#घोषणा TPS65086_LDOA3CTRL		0x29
#घोषणा TPS65086_DISCHCTRL1		0x40
#घोषणा TPS65086_DISCHCTRL2		0x41
#घोषणा TPS65086_DISCHCTRL3		0x42
#घोषणा TPS65086_PG_DELAY1		0x43
#घोषणा TPS65086_FORCESHUTDN		0x91
#घोषणा TPS65086_BUCK1SLPCTRL		0x92
#घोषणा TPS65086_BUCK2SLPCTRL		0x93
#घोषणा TPS65086_BUCK4VID		0x94
#घोषणा TPS65086_BUCK4SLPVID		0x95
#घोषणा TPS65086_BUCK5VID		0x96
#घोषणा TPS65086_BUCK5SLPVID		0x97
#घोषणा TPS65086_BUCK6VID		0x98
#घोषणा TPS65086_BUCK6SLPVID		0x99
#घोषणा TPS65086_LDOA2VID		0x9A
#घोषणा TPS65086_LDOA3VID		0x9B
#घोषणा TPS65086_BUCK123CTRL		0x9C
#घोषणा TPS65086_PG_DELAY2		0x9D
#घोषणा TPS65086_PIN_EN_MASK1		0x9E
#घोषणा TPS65086_PIN_EN_MASK2		0x9F
#घोषणा TPS65086_SWVTT_EN		0x9F
#घोषणा TPS65086_PIN_EN_OVR1		0xA0
#घोषणा TPS65086_PIN_EN_OVR2		0xA1
#घोषणा TPS65086_GPOCTRL		0xA1
#घोषणा TPS65086_PWR_FAULT_MASK1	0xA2
#घोषणा TPS65086_PWR_FAULT_MASK2	0xA3
#घोषणा TPS65086_GPO1PG_CTRL1		0xA4
#घोषणा TPS65086_GPO1PG_CTRL2		0xA5
#घोषणा TPS65086_GPO4PG_CTRL1		0xA6
#घोषणा TPS65086_GPO4PG_CTRL2		0xA7
#घोषणा TPS65086_GPO2PG_CTRL1		0xA8
#घोषणा TPS65086_GPO2PG_CTRL2		0xA9
#घोषणा TPS65086_GPO3PG_CTRL1		0xAA
#घोषणा TPS65086_GPO3PG_CTRL2		0xAB
#घोषणा TPS65086_LDOA1CTRL		0xAE
#घोषणा TPS65086_PG_STATUS1		0xB0
#घोषणा TPS65086_PG_STATUS2		0xB1
#घोषणा TPS65086_PWR_FAULT_STATUS1	0xB2
#घोषणा TPS65086_PWR_FAULT_STATUS2	0xB3
#घोषणा TPS65086_TEMPCRIT		0xB4
#घोषणा TPS65086_TEMPHOT		0xB5
#घोषणा TPS65086_OC_STATUS		0xB6

/* IRQ Register field definitions */
#घोषणा TPS65086_IRQ_DIETEMP_MASK	BIT(0)
#घोषणा TPS65086_IRQ_SHUTDN_MASK	BIT(3)
#घोषणा TPS65086_IRQ_FAULT_MASK		BIT(7)

/* DEVICEID Register field definitions */
#घोषणा TPS65086_DEVICEID_PART_MASK	GENMASK(3, 0)
#घोषणा TPS65086_DEVICEID_OTP_MASK	GENMASK(5, 4)
#घोषणा TPS65086_DEVICEID_REV_MASK	GENMASK(7, 6)

/* VID Masks */
#घोषणा BUCK_VID_MASK			GENMASK(7, 1)
#घोषणा VDOA1_VID_MASK			GENMASK(4, 1)
#घोषणा VDOA23_VID_MASK			GENMASK(3, 0)

/* Define the TPS65086 IRQ numbers */
क्रमागत tps65086_irqs अणु
	TPS65086_IRQ_DIETEMP,
	TPS65086_IRQ_SHUTDN,
	TPS65086_IRQ_FAULT,
पूर्ण;

/**
 * काष्ठा tps65086 - state holder क्रम the tps65086 driver
 *
 * Device data may be used to access the TPS65086 chip
 */
काष्ठा tps65086 अणु
	काष्ठा device *dev;
	काष्ठा regmap *regmap;

	/* IRQ Data */
	पूर्णांक irq;
	काष्ठा regmap_irq_chip_data *irq_data;
पूर्ण;

#पूर्ण_अगर /* __LINUX_MFD_TPS65086_H */
