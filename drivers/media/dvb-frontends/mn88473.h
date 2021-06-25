<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * Panasonic MN88473 DVB-T/T2/C demodulator driver
 *
 * Copyright (C) 2014 Antti Palosaari <crope@iki.fi>
 */

#अगर_अघोषित MN88473_H
#घोषणा MN88473_H

#समावेश <linux/dvb/frontend.h>

काष्ठा mn88473_config अणु
	/*
	 * Max num of bytes given I2C adapter could ग_लिखो at once.
	 * Default: unlimited
	 */
	u16 i2c_wr_max;

	/*
	 * Xtal frequency Hz.
	 * Default: 25000000
	 */
	u32 xtal;


	/* Everything after that is वापसed by the driver. */

	/*
	 * DVB frontend.
	 */
	काष्ठा dvb_frontend **fe;
पूर्ण;

#पूर्ण_अगर
