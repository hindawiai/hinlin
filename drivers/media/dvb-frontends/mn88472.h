<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * Panasonic MN88472 DVB-T/T2/C demodulator driver
 *
 * Copyright (C) 2013 Antti Palosaari <crope@iki.fi>
 */

#अगर_अघोषित MN88472_H
#घोषणा MN88472_H

#समावेश <linux/dvb/frontend.h>

/* Define old names क्रम backward compatibility */
#घोषणा VARIABLE_TS_CLOCK   MN88472_TS_CLK_VARIABLE
#घोषणा FIXED_TS_CLOCK      MN88472_TS_CLK_FIXED
#घोषणा SERIAL_TS_MODE      MN88472_TS_MODE_SERIAL
#घोषणा PARALLEL_TS_MODE    MN88472_TS_MODE_PARALLEL

/**
 * काष्ठा mn88472_config - Platक्रमm data क्रम the mn88472 driver
 * @xtal: Clock frequency.
 * @ts_mode: TS mode.
 * @ts_घड़ी: TS घड़ी config.
 * @i2c_wr_max: Max number of bytes driver ग_लिखोs to I2C at once.
 * @fe: poपूर्णांकer to a frontend poपूर्णांकer
 * @get_dvb_frontend: Get DVB frontend callback.
 */
काष्ठा mn88472_config अणु
	अचिन्हित पूर्णांक xtal;

#घोषणा MN88472_TS_MODE_SERIAL      0
#घोषणा MN88472_TS_MODE_PARALLEL    1
	पूर्णांक ts_mode;

#घोषणा MN88472_TS_CLK_FIXED        0
#घोषणा MN88472_TS_CLK_VARIABLE     1
	पूर्णांक ts_घड़ी;

	u16 i2c_wr_max;

	/* Everything after that is वापसed by the driver. */

	/*
	 * DVB frontend.
	 */
	काष्ठा dvb_frontend **fe;
	काष्ठा dvb_frontend* (*get_dvb_frontend)(काष्ठा i2c_client *);
पूर्ण;

#पूर्ण_अगर
