<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * et8ek8_reg.h
 *
 * Copyright (C) 2008 Nokia Corporation
 *
 * Contact: Sakari Ailus <sakari.ailus@iki.fi>
 *          Tuukka Toivonen <tuukkat76@gmail.com>
 */

#अगर_अघोषित ET8EK8REGS_H
#घोषणा ET8EK8REGS_H

#समावेश <linux/i2c.h>
#समावेश <linux/types.h>
#समावेश <linux/videodev2.h>
#समावेश <linux/v4l2-subdev.h>

काष्ठा v4l2_mbus_framefmt;
काष्ठा v4l2_subdev_pad_mbus_code_क्रमागत;

काष्ठा et8ek8_mode अणु
	/* Physical sensor resolution and current image winकरोw */
	u16 sensor_width;
	u16 sensor_height;
	u16 sensor_winकरोw_origin_x;
	u16 sensor_winकरोw_origin_y;
	u16 sensor_winकरोw_width;
	u16 sensor_winकरोw_height;

	/* Image data coming from sensor (after scaling) */
	u16 width;
	u16 height;
	u16 winकरोw_origin_x;
	u16 winकरोw_origin_y;
	u16 winकरोw_width;
	u16 winकरोw_height;

	u32 pixel_घड़ी;		/* in Hz */
	u32 ext_घड़ी;			/* in Hz */
	काष्ठा v4l2_fract समयperframe;
	u32 max_exp;			/* Maximum exposure value */
	u32 bus_क्रमmat;			/* MEDIA_BUS_FMT_ */
	u32 sensitivity;		/* 16.16 fixed poपूर्णांक */
पूर्ण;

#घोषणा ET8EK8_REG_8BIT			1
#घोषणा ET8EK8_REG_16BIT		2
#घोषणा ET8EK8_REG_DELAY		100
#घोषणा ET8EK8_REG_TERM			0xff
काष्ठा et8ek8_reg अणु
	u16 type;
	u16 reg;			/* 16-bit offset */
	u32 val;			/* 8/16/32-bit value */
पूर्ण;

/* Possible काष्ठा smia_reglist types. */
#घोषणा ET8EK8_REGLIST_STANDBY		0
#घोषणा ET8EK8_REGLIST_POWERON		1
#घोषणा ET8EK8_REGLIST_RESUME		2
#घोषणा ET8EK8_REGLIST_STREAMON		3
#घोषणा ET8EK8_REGLIST_STREAMOFF	4
#घोषणा ET8EK8_REGLIST_DISABLED		5

#घोषणा ET8EK8_REGLIST_MODE		10

#घोषणा ET8EK8_REGLIST_LSC_ENABLE	100
#घोषणा ET8EK8_REGLIST_LSC_DISABLE	101
#घोषणा ET8EK8_REGLIST_ANR_ENABLE	102
#घोषणा ET8EK8_REGLIST_ANR_DISABLE	103

काष्ठा et8ek8_reglist अणु
	u32 type;
	काष्ठा et8ek8_mode mode;
	काष्ठा et8ek8_reg regs[];
पूर्ण;

#घोषणा ET8EK8_MAX_LEN			32
काष्ठा et8ek8_meta_reglist अणु
	अक्षर version[ET8EK8_MAX_LEN];
	जोड़ अणु
		काष्ठा et8ek8_reglist *ptr;
	पूर्ण reglist[];
पूर्ण;

बाह्य काष्ठा et8ek8_meta_reglist meta_reglist;

#पूर्ण_अगर /* ET8EK8REGS */
