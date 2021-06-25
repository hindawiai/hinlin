<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * include/media/i2c/adp1653.h
 *
 * Copyright (C) 2008--2011 Nokia Corporation
 *
 * Contact: Sakari Ailus <sakari.ailus@iki.fi>
 *
 * Contributors:
 *	Sakari Ailus <sakari.ailus@iki.fi>
 *	Tuukka Toivonen <tuukkat76@gmail.com>
 */

#अगर_अघोषित ADP1653_H
#घोषणा ADP1653_H

#समावेश <linux/i2c.h>
#समावेश <linux/mutex.h>
#समावेश <linux/videodev2.h>
#समावेश <media/v4l2-ctrls.h>
#समावेश <media/v4l2-subdev.h>

#घोषणा ADP1653_NAME				"adp1653"
#घोषणा ADP1653_I2C_ADDR			(0x60 >> 1)

/* Register definitions */
#घोषणा ADP1653_REG_OUT_SEL			0x00
#घोषणा ADP1653_REG_OUT_SEL_HPLED_TORCH_MIN	0x01
#घोषणा ADP1653_REG_OUT_SEL_HPLED_TORCH_MAX	0x0b
#घोषणा ADP1653_REG_OUT_SEL_HPLED_FLASH_MIN	0x0c
#घोषणा ADP1653_REG_OUT_SEL_HPLED_FLASH_MAX	0x1f
#घोषणा ADP1653_REG_OUT_SEL_HPLED_SHIFT		3
#घोषणा ADP1653_REG_OUT_SEL_ILED_MAX		0x07
#घोषणा ADP1653_REG_OUT_SEL_ILED_SHIFT		0

#घोषणा ADP1653_REG_CONFIG			0x01
#घोषणा ADP1653_REG_CONFIG_TMR_CFG		(1 << 4)
#घोषणा ADP1653_REG_CONFIG_TMR_SET_MAX		0x0f
#घोषणा ADP1653_REG_CONFIG_TMR_SET_SHIFT	0

#घोषणा ADP1653_REG_SW_STROBE			0x02
#घोषणा ADP1653_REG_SW_STROBE_SW_STROBE		(1 << 0)

#घोषणा ADP1653_REG_FAULT			0x03
#घोषणा ADP1653_REG_FAULT_FLT_SCP		(1 << 3)
#घोषणा ADP1653_REG_FAULT_FLT_OT		(1 << 2)
#घोषणा ADP1653_REG_FAULT_FLT_TMR		(1 << 1)
#घोषणा ADP1653_REG_FAULT_FLT_OV		(1 << 0)

#घोषणा ADP1653_INDICATOR_INTENSITY_MIN		0
#घोषणा ADP1653_INDICATOR_INTENSITY_STEP	2500
#घोषणा ADP1653_INDICATOR_INTENSITY_MAX		\
	(ADP1653_REG_OUT_SEL_ILED_MAX * ADP1653_INDICATOR_INTENSITY_STEP)
#घोषणा ADP1653_INDICATOR_INTENSITY_uA_TO_REG(a) \
	((a) / ADP1653_INDICATOR_INTENSITY_STEP)
#घोषणा ADP1653_INDICATOR_INTENSITY_REG_TO_uA(a) \
	((a) * ADP1653_INDICATOR_INTENSITY_STEP)

#घोषणा ADP1653_FLASH_INTENSITY_BASE		35
#घोषणा ADP1653_FLASH_INTENSITY_STEP		15
#घोषणा ADP1653_FLASH_INTENSITY_MIN					\
	(ADP1653_FLASH_INTENSITY_BASE					\
	 + ADP1653_REG_OUT_SEL_HPLED_FLASH_MIN * ADP1653_FLASH_INTENSITY_STEP)
#घोषणा ADP1653_FLASH_INTENSITY_MAX			\
	(ADP1653_FLASH_INTENSITY_MIN +			\
	 (ADP1653_REG_OUT_SEL_HPLED_FLASH_MAX -		\
	  ADP1653_REG_OUT_SEL_HPLED_FLASH_MIN + 1) *	\
	 ADP1653_FLASH_INTENSITY_STEP)

#घोषणा ADP1653_FLASH_INTENSITY_mA_TO_REG(a)				\
	((a) < ADP1653_FLASH_INTENSITY_BASE ? 0 :			\
	 (((a) - ADP1653_FLASH_INTENSITY_BASE) / ADP1653_FLASH_INTENSITY_STEP))
#घोषणा ADP1653_FLASH_INTENSITY_REG_TO_mA(a)		\
	((a) * ADP1653_FLASH_INTENSITY_STEP + ADP1653_FLASH_INTENSITY_BASE)

#घोषणा ADP1653_TORCH_INTENSITY_MIN					\
	(ADP1653_FLASH_INTENSITY_BASE					\
	 + ADP1653_REG_OUT_SEL_HPLED_TORCH_MIN * ADP1653_FLASH_INTENSITY_STEP)
#घोषणा ADP1653_TORCH_INTENSITY_MAX			\
	(ADP1653_TORCH_INTENSITY_MIN +			\
	 (ADP1653_REG_OUT_SEL_HPLED_TORCH_MAX -		\
	  ADP1653_REG_OUT_SEL_HPLED_TORCH_MIN + 1) *	\
	 ADP1653_FLASH_INTENSITY_STEP)

काष्ठा adp1653_platक्रमm_data अणु
	पूर्णांक (*घातer)(काष्ठा v4l2_subdev *sd, पूर्णांक on);

	u32 max_flash_समयout;		/* flash light समयout in us */
	u32 max_flash_पूर्णांकensity;	/* led पूर्णांकensity, flash mode, mA */
	u32 max_torch_पूर्णांकensity;	/* led पूर्णांकensity, torch mode, mA */
	u32 max_indicator_पूर्णांकensity;	/* indicator led पूर्णांकensity, uA */

	काष्ठा gpio_desc *enable_gpio;	/* क्रम device-tree based boot */
पूर्ण;

#घोषणा to_adp1653_flash(sd)	container_of(sd, काष्ठा adp1653_flash, subdev)

काष्ठा adp1653_flash अणु
	काष्ठा v4l2_subdev subdev;
	काष्ठा adp1653_platक्रमm_data *platक्रमm_data;

	काष्ठा v4l2_ctrl_handler ctrls;
	काष्ठा v4l2_ctrl *led_mode;
	काष्ठा v4l2_ctrl *flash_समयout;
	काष्ठा v4l2_ctrl *flash_पूर्णांकensity;
	काष्ठा v4l2_ctrl *torch_पूर्णांकensity;
	काष्ठा v4l2_ctrl *indicator_पूर्णांकensity;

	काष्ठा mutex घातer_lock;
	पूर्णांक घातer_count;
	पूर्णांक fault;
पूर्ण;

#पूर्ण_अगर /* ADP1653_H */
