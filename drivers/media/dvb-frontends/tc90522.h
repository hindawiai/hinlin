<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Toshiba TC90522 Demodulator
 *
 * Copyright (C) 2014 Akihiro Tsukada <tskd08@gmail.com>
 */

/*
 * The demod has 4 input (2xISDB-T and 2xISDB-S),
 * and provides independent sub modules क्रम each input.
 * As the sub modules work in parallel and have the separate i2c addr's,
 * this driver treats each sub module as one demod device.
 */

#अगर_अघोषित TC90522_H
#घोषणा TC90522_H

#समावेश <linux/i2c.h>
#समावेश <media/dvb_frontend.h>

/* I2C device types */
#घोषणा TC90522_I2C_DEV_SAT "tc90522sat"
#घोषणा TC90522_I2C_DEV_TER "tc90522ter"

काष्ठा tc90522_config अणु
	/* [OUT] frontend वापसed by driver */
	काष्ठा dvb_frontend *fe;

	/* [OUT] tuner I2C adapter वापसed by driver */
	काष्ठा i2c_adapter *tuner_i2c;

	/* [IN] use two separate I2C transactions क्रम one tuner पढ़ो */
	bool split_tuner_पढ़ो_i2c;
पूर्ण;

#पूर्ण_अगर /* TC90522_H */
