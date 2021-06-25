<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * FCI FC2580 silicon tuner driver
 *
 * Copyright (C) 2012 Antti Palosaari <crope@iki.fi>
 */

#अगर_अघोषित FC2580_H
#घोषणा FC2580_H

#समावेश <media/dvb_frontend.h>
#समावेश <media/v4l2-subdev.h>
#समावेश <linux/i2c.h>

/*
 * I2C address
 * 0x56, ...
 */

/**
 * काष्ठा fc2580_platक्रमm_data - Platक्रमm data क्रम the fc2580 driver
 * @clk: Clock frequency (0 = पूर्णांकernal घड़ी).
 * @dvb_frontend: DVB frontend.
 * @get_v4l2_subdev: Get V4L2 subdev.
 */
काष्ठा fc2580_platक्रमm_data अणु
	u32 clk;
	काष्ठा dvb_frontend *dvb_frontend;

	काष्ठा v4l2_subdev* (*get_v4l2_subdev)(काष्ठा i2c_client *);
पूर्ण;

#पूर्ण_अगर
