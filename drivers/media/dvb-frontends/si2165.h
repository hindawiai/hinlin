<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * Driver क्रम Silicon Lअसल SI2165 DVB-C/-T Demodulator
 *
 * Copyright (C) 2013-2017 Matthias Schwarzott <zzam@gentoo.org>
 *
 * References:
 *   https://www.siद_असल.com/Support%20Documents/TechnicalDocs/Si2165-लघु.pdf
 */

#अगर_अघोषित _DVB_SI2165_H
#घोषणा _DVB_SI2165_H

#समावेश <linux/dvb/frontend.h>

क्रमागत अणु
	SI2165_MODE_OFF = 0x00,
	SI2165_MODE_PLL_EXT = 0x20,
	SI2165_MODE_PLL_XTAL = 0x21
पूर्ण;

/* I2C addresses
 * possible values: 0x64,0x65,0x66,0x67
 */
काष्ठा si2165_platक्रमm_data अणु
	/*
	 * frontend
	 * वापसed by driver
	 */
	काष्ठा dvb_frontend **fe;

	/* बाह्यal घड़ी or XTAL */
	u8 chip_mode;

	/* frequency of बाह्यal घड़ी or xtal in Hz
	 * possible values: 4000000, 16000000, 20000000, 240000000, 27000000
	 */
	u32 ref_freq_hz;

	/* invert the spectrum */
	bool inversion;
पूर्ण;

#पूर्ण_अगर /* _DVB_SI2165_H */
