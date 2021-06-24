<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * Silicon Lअसल Si2168 DVB-T/T2/C demodulator driver
 *
 * Copyright (C) 2014 Antti Palosaari <crope@iki.fi>
 */

#अगर_अघोषित SI2168_H
#घोषणा SI2168_H

#समावेश <linux/dvb/frontend.h>
/**
 * काष्ठा si2168_config - configuration parameters क्रम si2168
 *
 * @fe:
 *	frontend वापसed by driver
 * @i2c_adapter:
 *	tuner I2C adapter वापसed by driver
 * @ts_mode:
 *	Transport Stream mode. Can be:
 *	- %SI2168_TS_PARALLEL
 *	- %SI2168_TS_SERIAL
 *	- %SI2168_TS_TRISTATE
 *	- %SI2168_TS_CLK_MANUAL
 * @ts_घड़ी_inv:
 *	TS घड़ी inverted
 * @ts_घड़ी_gapped:
 *	TS घड़ी gapped
 * @spectral_inversion:
 *	Inverted spectrum
 *
 * Note:
 *	The I2C address of this demod is 0x64.
 */
काष्ठा si2168_config अणु
	काष्ठा dvb_frontend **fe;
	काष्ठा i2c_adapter **i2c_adapter;

#घोषणा SI2168_TS_PARALLEL	0x06
#घोषणा SI2168_TS_SERIAL	0x03
#घोषणा SI2168_TS_TRISTATE	0x00
#घोषणा SI2168_TS_CLK_MANUAL	0x20
	u8 ts_mode;

	/* Flags */
	अचिन्हित पूर्णांक ts_घड़ी_inv:1;
	अचिन्हित पूर्णांक ts_घड़ी_gapped:1;
	अचिन्हित पूर्णांक spectral_inversion:1;
पूर्ण;

#पूर्ण_अगर
