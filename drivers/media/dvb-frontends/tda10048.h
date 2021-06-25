<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
    NXP TDA10048HN DVB OFDM demodulator driver

    Copyright (C) 2009 Steven Toth <stoth@kernelद_असल.com>


*/

#अगर_अघोषित TDA10048_H
#घोषणा TDA10048_H

#समावेश <linux/dvb/frontend.h>
#समावेश <linux/firmware.h>

काष्ठा tda10048_config अणु

	/* the demodulator's i2c address */
	u8 demod_address;

	/* serial/parallel output */
#घोषणा TDA10048_PARALLEL_OUTPUT 0
#घोषणा TDA10048_SERIAL_OUTPUT   1
	u8 output_mode;

#घोषणा TDA10048_BULKWRITE_200	200
#घोषणा TDA10048_BULKWRITE_50	50
	u8 fwbulkग_लिखोlen;

	/* Spectral Inversion */
#घोषणा TDA10048_INVERSION_OFF 0
#घोषणा TDA10048_INVERSION_ON  1
	u8 inversion;

#घोषणा TDA10048_IF_3300  3300
#घोषणा TDA10048_IF_3500  3500
#घोषणा TDA10048_IF_3800  3800
#घोषणा TDA10048_IF_4000  4000
#घोषणा TDA10048_IF_4300  4300
#घोषणा TDA10048_IF_4500  4500
#घोषणा TDA10048_IF_4750  4750
#घोषणा TDA10048_IF_5000  5000
#घोषणा TDA10048_IF_36130 36130
	u16 dtv6_अगर_freq_khz;
	u16 dtv7_अगर_freq_khz;
	u16 dtv8_अगर_freq_khz;

#घोषणा TDA10048_CLK_4000  4000
#घोषणा TDA10048_CLK_16000 16000
	u16 clk_freq_khz;

	/* Disable I2C gate access */
	u8 disable_gate_access;

	bool no_firmware;

	bool set_pll;
	u8 pll_m;
	u8 pll_p;
	u8 pll_n;
पूर्ण;

#अगर IS_REACHABLE(CONFIG_DVB_TDA10048)
बाह्य काष्ठा dvb_frontend *tda10048_attach(
	स्थिर काष्ठा tda10048_config *config,
	काष्ठा i2c_adapter *i2c);
#अन्यथा
अटल अंतरभूत काष्ठा dvb_frontend *tda10048_attach(
	स्थिर काष्ठा tda10048_config *config,
	काष्ठा i2c_adapter *i2c)
अणु
	prपूर्णांकk(KERN_WARNING "%s: driver disabled by Kconfig\n", __func__);
	वापस शून्य;
पूर्ण
#पूर्ण_अगर /* CONFIG_DVB_TDA10048 */

#पूर्ण_अगर /* TDA10048_H */
