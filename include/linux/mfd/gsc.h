<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0
 *
 * Copyright (C) 2020 Gateworks Corporation
 */
#अगर_अघोषित __LINUX_MFD_GSC_H_
#घोषणा __LINUX_MFD_GSC_H_

#समावेश <linux/regmap.h>

/* Device Addresses */
#घोषणा GSC_MISC	0x20
#घोषणा GSC_UPDATE	0x21
#घोषणा GSC_GPIO	0x23
#घोषणा GSC_HWMON	0x29
#घोषणा GSC_EEPROM0	0x50
#घोषणा GSC_EEPROM1	0x51
#घोषणा GSC_EEPROM2	0x52
#घोषणा GSC_EEPROM3	0x53
#घोषणा GSC_RTC		0x68

/* Register offsets */
क्रमागत अणु
	GSC_CTRL_0	= 0x00,
	GSC_CTRL_1	= 0x01,
	GSC_TIME	= 0x02,
	GSC_TIME_ADD	= 0x06,
	GSC_IRQ_STATUS	= 0x0A,
	GSC_IRQ_ENABLE	= 0x0B,
	GSC_FW_CRC	= 0x0C,
	GSC_FW_VER	= 0x0E,
	GSC_WP		= 0x0F,
पूर्ण;

/* Bit definitions */
#घोषणा GSC_CTRL_0_PB_HARD_RESET	0
#घोषणा GSC_CTRL_0_PB_CLEAR_SECURE_KEY	1
#घोषणा GSC_CTRL_0_PB_SOFT_POWER_DOWN	2
#घोषणा GSC_CTRL_0_PB_BOOT_ALTERNATE	3
#घोषणा GSC_CTRL_0_PERFORM_CRC		4
#घोषणा GSC_CTRL_0_TAMPER_DETECT	5
#घोषणा GSC_CTRL_0_SWITCH_HOLD		6

#घोषणा GSC_CTRL_1_SLEEP_ENABLE		0
#घोषणा GSC_CTRL_1_SLEEP_ACTIVATE	1
#घोषणा GSC_CTRL_1_SLEEP_ADD		2
#घोषणा GSC_CTRL_1_SLEEP_NOWAKEPB	3
#घोषणा GSC_CTRL_1_WDT_TIME		4
#घोषणा GSC_CTRL_1_WDT_ENABLE		5
#घोषणा GSC_CTRL_1_SWITCH_BOOT_ENABLE	6
#घोषणा GSC_CTRL_1_SWITCH_BOOT_CLEAR	7

#घोषणा GSC_IRQ_PB			0
#घोषणा GSC_IRQ_KEY_ERASED		1
#घोषणा GSC_IRQ_EEPROM_WP		2
#घोषणा GSC_IRQ_RESV			3
#घोषणा GSC_IRQ_GPIO			4
#घोषणा GSC_IRQ_TAMPER			5
#घोषणा GSC_IRQ_WDT_TIMEOUT		6
#घोषणा GSC_IRQ_SWITCH_HOLD		7

पूर्णांक gsc_पढ़ो(व्योम *context, अचिन्हित पूर्णांक reg, अचिन्हित पूर्णांक *val);
पूर्णांक gsc_ग_लिखो(व्योम *context, अचिन्हित पूर्णांक reg, अचिन्हित पूर्णांक val);

काष्ठा gsc_dev अणु
	काष्ठा device *dev;

	काष्ठा i2c_client *i2c;		/* 0x20: पूर्णांकerrupt controller, WDT */
	काष्ठा i2c_client *i2c_hwmon;	/* 0x29: hwmon, fan controller */

	काष्ठा regmap *regmap;

	अचिन्हित पूर्णांक fwver;
	अचिन्हित लघु fwcrc;
पूर्ण;

#पूर्ण_अगर /* __LINUX_MFD_GSC_H_ */
