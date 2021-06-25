<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * linux/include/linux/mfd/aat2870.h
 *
 * Copyright (c) 2011, NVIDIA Corporation.
 * Author: Jin Park <jinyoungp@nvidia.com>
 */

#अगर_अघोषित __LINUX_MFD_AAT2870_H
#घोषणा __LINUX_MFD_AAT2870_H

#समावेश <linux/debugfs.h>
#समावेश <linux/i2c.h>

/* Register offsets */
#घोषणा AAT2870_BL_CH_EN	0x00
#घोषणा AAT2870_BLM		0x01
#घोषणा AAT2870_BLS		0x02
#घोषणा AAT2870_BL1		0x03
#घोषणा AAT2870_BL2		0x04
#घोषणा AAT2870_BL3		0x05
#घोषणा AAT2870_BL4		0x06
#घोषणा AAT2870_BL5		0x07
#घोषणा AAT2870_BL6		0x08
#घोषणा AAT2870_BL7		0x09
#घोषणा AAT2870_BL8		0x0A
#घोषणा AAT2870_FLR		0x0B
#घोषणा AAT2870_FM		0x0C
#घोषणा AAT2870_FS		0x0D
#घोषणा AAT2870_ALS_CFG0	0x0E
#घोषणा AAT2870_ALS_CFG1	0x0F
#घोषणा AAT2870_ALS_CFG2	0x10
#घोषणा AAT2870_AMB		0x11
#घोषणा AAT2870_ALS0		0x12
#घोषणा AAT2870_ALS1		0x13
#घोषणा AAT2870_ALS2		0x14
#घोषणा AAT2870_ALS3		0x15
#घोषणा AAT2870_ALS4		0x16
#घोषणा AAT2870_ALS5		0x17
#घोषणा AAT2870_ALS6		0x18
#घोषणा AAT2870_ALS7		0x19
#घोषणा AAT2870_ALS8		0x1A
#घोषणा AAT2870_ALS9		0x1B
#घोषणा AAT2870_ALSA		0x1C
#घोषणा AAT2870_ALSB		0x1D
#घोषणा AAT2870_ALSC		0x1E
#घोषणा AAT2870_ALSD		0x1F
#घोषणा AAT2870_ALSE		0x20
#घोषणा AAT2870_ALSF		0x21
#घोषणा AAT2870_SUB_SET		0x22
#घोषणा AAT2870_SUB_CTRL	0x23
#घोषणा AAT2870_LDO_AB		0x24
#घोषणा AAT2870_LDO_CD		0x25
#घोषणा AAT2870_LDO_EN		0x26
#घोषणा AAT2870_REG_NUM		0x27

/* Device IDs */
क्रमागत aat2870_id अणु
	AAT2870_ID_BL,
	AAT2870_ID_LDOA,
	AAT2870_ID_LDOB,
	AAT2870_ID_LDOC,
	AAT2870_ID_LDOD
पूर्ण;

/* Backlight channels */
#घोषणा AAT2870_BL_CH1		0x01
#घोषणा AAT2870_BL_CH2		0x02
#घोषणा AAT2870_BL_CH3		0x04
#घोषणा AAT2870_BL_CH4		0x08
#घोषणा AAT2870_BL_CH5		0x10
#घोषणा AAT2870_BL_CH6		0x20
#घोषणा AAT2870_BL_CH7		0x40
#घोषणा AAT2870_BL_CH8		0x80
#घोषणा AAT2870_BL_CH_ALL	0xFF

/* Backlight current magnitude (mA) */
क्रमागत aat2870_current अणु
	AAT2870_CURRENT_0_45 = 1,
	AAT2870_CURRENT_0_90,
	AAT2870_CURRENT_1_80,
	AAT2870_CURRENT_2_70,
	AAT2870_CURRENT_3_60,
	AAT2870_CURRENT_4_50,
	AAT2870_CURRENT_5_40,
	AAT2870_CURRENT_6_30,
	AAT2870_CURRENT_7_20,
	AAT2870_CURRENT_8_10,
	AAT2870_CURRENT_9_00,
	AAT2870_CURRENT_9_90,
	AAT2870_CURRENT_10_8,
	AAT2870_CURRENT_11_7,
	AAT2870_CURRENT_12_6,
	AAT2870_CURRENT_13_5,
	AAT2870_CURRENT_14_4,
	AAT2870_CURRENT_15_3,
	AAT2870_CURRENT_16_2,
	AAT2870_CURRENT_17_1,
	AAT2870_CURRENT_18_0,
	AAT2870_CURRENT_18_9,
	AAT2870_CURRENT_19_8,
	AAT2870_CURRENT_20_7,
	AAT2870_CURRENT_21_6,
	AAT2870_CURRENT_22_5,
	AAT2870_CURRENT_23_4,
	AAT2870_CURRENT_24_3,
	AAT2870_CURRENT_25_2,
	AAT2870_CURRENT_26_1,
	AAT2870_CURRENT_27_0,
	AAT2870_CURRENT_27_9
पूर्ण;

काष्ठा aat2870_रेजिस्टर अणु
	bool पढ़ोable;
	bool ग_लिखोable;
	u8 value;
पूर्ण;

काष्ठा aat2870_data अणु
	काष्ठा device *dev;
	काष्ठा i2c_client *client;

	काष्ठा mutex io_lock;
	काष्ठा aat2870_रेजिस्टर *reg_cache; /* रेजिस्टर cache */
	पूर्णांक en_pin; /* enable GPIO pin (अगर < 0, ignore this value) */
	bool is_enable;

	/* init and uninit क्रम platक्रमm specअगरied */
	पूर्णांक (*init)(काष्ठा aat2870_data *aat2870);
	व्योम (*uninit)(काष्ठा aat2870_data *aat2870);

	/* i2c io funcntions */
	पूर्णांक (*पढ़ो)(काष्ठा aat2870_data *aat2870, u8 addr, u8 *val);
	पूर्णांक (*ग_लिखो)(काष्ठा aat2870_data *aat2870, u8 addr, u8 val);
	पूर्णांक (*update)(काष्ठा aat2870_data *aat2870, u8 addr, u8 mask, u8 val);

	/* क्रम debugfs */
	काष्ठा dentry *dentry_root;
पूर्ण;

काष्ठा aat2870_subdev_info अणु
	पूर्णांक id;
	स्थिर अक्षर *name;
	व्योम *platक्रमm_data;
पूर्ण;

काष्ठा aat2870_platक्रमm_data अणु
	पूर्णांक en_pin; /* enable GPIO pin (अगर < 0, ignore this value) */

	काष्ठा aat2870_subdev_info *subdevs;
	पूर्णांक num_subdevs;

	/* init and uninit क्रम platक्रमm specअगरied */
	पूर्णांक (*init)(काष्ठा aat2870_data *aat2870);
	व्योम (*uninit)(काष्ठा aat2870_data *aat2870);
पूर्ण;

काष्ठा aat2870_bl_platक्रमm_data अणु
	/* backlight channels, शेष is AAT2870_BL_CH_ALL */
	पूर्णांक channels;
	/* backlight current magnitude, शेष is AAT2870_CURRENT_27_9 */
	पूर्णांक max_current;
	/* maximum brightness, शेष is 255 */
	पूर्णांक max_brightness;
पूर्ण;

#पूर्ण_अगर /* __LINUX_MFD_AAT2870_H */
