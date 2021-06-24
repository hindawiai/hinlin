<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Copyright (c) 2019 MediaTek Inc.
 */

#अगर_अघोषित __SND_SOC_MT6660_H
#घोषणा __SND_SOC_MT6660_H

#समावेश <linux/mutex.h>
#समावेश <linux/regmap.h>

#आशय pack(push, 1)
काष्ठा mt6660_platक्रमm_data अणु
	u8 init_setting_num;
	u32 *init_setting_addr;
	u32 *init_setting_mask;
	u32 *init_setting_val;
पूर्ण;

काष्ठा mt6660_chip अणु
	काष्ठा i2c_client *i2c;
	काष्ठा device *dev;
	काष्ठा platक्रमm_device *param_dev;
	काष्ठा mt6660_platक्रमm_data plat_data;
	काष्ठा mutex io_lock;
	काष्ठा regmap *regmap;
	u16 chip_rev;
पूर्ण;
#आशय pack(pop)

#घोषणा MT6660_REG_DEVID		(0x00)
#घोषणा MT6660_REG_SYSTEM_CTRL		(0x03)
#घोषणा MT6660_REG_IRQ_STATUS1		(0x05)
#घोषणा MT6660_REG_ADDA_CLOCK		(0x07)
#घोषणा MT6660_REG_SERIAL_CFG1		(0x10)
#घोषणा MT6660_REG_DATAO_SEL		(0x12)
#घोषणा MT6660_REG_TDM_CFG3		(0x15)
#घोषणा MT6660_REG_HPF_CTRL		(0x18)
#घोषणा MT6660_REG_HPF1_COEF		(0x1A)
#घोषणा MT6660_REG_HPF2_COEF		(0x1B)
#घोषणा MT6660_REG_PATH_BYPASS		(0x1E)
#घोषणा MT6660_REG_WDT_CTRL		(0x20)
#घोषणा MT6660_REG_HCLIP_CTRL		(0x24)
#घोषणा MT6660_REG_VOL_CTRL		(0x29)
#घोषणा MT6660_REG_SPS_CTRL		(0x30)
#घोषणा MT6660_REG_SIGMAX		(0x33)
#घोषणा MT6660_REG_CALI_T0		(0x3F)
#घोषणा MT6660_REG_BST_CTRL		(0x40)
#घोषणा MT6660_REG_PROTECTION_CFG	(0x46)
#घोषणा MT6660_REG_DA_GAIN		(0x4c)
#घोषणा MT6660_REG_AUDIO_IN2_SEL	(0x50)
#घोषणा MT6660_REG_SIG_GAIN		(0x51)
#घोषणा MT6660_REG_PLL_CFG1		(0x60)
#घोषणा MT6660_REG_DRE_CTRL		(0x68)
#घोषणा MT6660_REG_DRE_THDMODE		(0x69)
#घोषणा MT6660_REG_DRE_CORASE		(0x6B)
#घोषणा MT6660_REG_PWM_CTRL		(0x70)
#घोषणा MT6660_REG_DC_PROTECT_CTRL	(0x74)
#घोषणा MT6660_REG_ADC_USB_MODE		(0x7c)
#घोषणा MT6660_REG_INTERNAL_CFG		(0x88)
#घोषणा MT6660_REG_RESV0		(0x98)
#घोषणा MT6660_REG_RESV1		(0x99)
#घोषणा MT6660_REG_RESV2		(0x9A)
#घोषणा MT6660_REG_RESV3		(0x9B)
#घोषणा MT6660_REG_RESV6		(0xA2)
#घोषणा MT6660_REG_RESV7		(0xA3)
#घोषणा MT6660_REG_RESV10		(0xB0)
#घोषणा MT6660_REG_RESV11		(0xB1)
#घोषणा MT6660_REG_RESV16		(0xB6)
#घोषणा MT6660_REG_RESV17		(0xB7)
#घोषणा MT6660_REG_RESV19		(0xB9)
#घोषणा MT6660_REG_RESV21		(0xBB)
#घोषणा MT6660_REG_RESV23		(0xBD)
#घोषणा MT6660_REG_RESV31		(0xD3)
#घोषणा MT6660_REG_RESV40		(0xE0)

#पूर्ण_अगर /* __SND_SOC_MT6660_H */
