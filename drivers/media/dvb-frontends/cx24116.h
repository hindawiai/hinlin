<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
    Conexant cx24116/cx24118 - DVBS/S2 Satellite demod/tuner driver

    Copyright (C) 2006 Steven Toth <stoth@linuxtv.com>

*/

#अगर_अघोषित CX24116_H
#घोषणा CX24116_H

#समावेश <linux/dvb/frontend.h>

काष्ठा cx24116_config अणु
	/* the demodulator's i2c address */
	u8 demod_address;

	/* Need to set device param क्रम start_dma */
	पूर्णांक (*set_ts_params)(काष्ठा dvb_frontend *fe, पूर्णांक is_punctured);

	/* Need to reset device during firmware loading */
	पूर्णांक (*reset_device)(काष्ठा dvb_frontend *fe);

	/* Need to set MPEG parameters */
	u8 mpg_clk_pos_pol:0x02;

	/* max bytes I2C provider can ग_लिखो at once */
	u16 i2c_wr_max;
पूर्ण;

#अगर IS_REACHABLE(CONFIG_DVB_CX24116)
बाह्य काष्ठा dvb_frontend *cx24116_attach(
	स्थिर काष्ठा cx24116_config *config,
	काष्ठा i2c_adapter *i2c);
#अन्यथा
अटल अंतरभूत काष्ठा dvb_frontend *cx24116_attach(
	स्थिर काष्ठा cx24116_config *config,
	काष्ठा i2c_adapter *i2c)
अणु
	prपूर्णांकk(KERN_WARNING "%s: driver disabled by Kconfig\n", __func__);
	वापस शून्य;
पूर्ण
#पूर्ण_अगर

#पूर्ण_अगर /* CX24116_H */
