<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
	STV0900/0903 Multistandard Broadcast Frontend driver
	Copyright (C) Manu Abraham <abraham.manu@gmail.com>

	Copyright (C) ST Microelectronics

*/

#अगर_अघोषित __STV090x_H
#घोषणा __STV090x_H

क्रमागत stv090x_demodulator अणु
	STV090x_DEMODULATOR_0 = 1,
	STV090x_DEMODULATOR_1
पूर्ण;

क्रमागत stv090x_device अणु
	STV0903	=  0,
	STV0900,
पूर्ण;

क्रमागत stv090x_mode अणु
	STV090x_DUAL = 0,
	STV090x_SINGLE
पूर्ण;

क्रमागत stv090x_tsmode अणु
	STV090x_TSMODE_SERIAL_PUNCTURED	= 1,
	STV090x_TSMODE_SERIAL_CONTINUOUS,
	STV090x_TSMODE_PARALLEL_PUNCTURED,
	STV090x_TSMODE_DVBCI
पूर्ण;

क्रमागत stv090x_clkmode अणु
	STV090x_CLK_INT = 0, /* Clk i/p = CLKI */
	STV090x_CLK_EXT = 2 /* Clk i/p = XTALI */
पूर्ण;

क्रमागत stv090x_i2crpt अणु
	STV090x_RPTLEVEL_256	= 0,
	STV090x_RPTLEVEL_128	= 1,
	STV090x_RPTLEVEL_64	= 2,
	STV090x_RPTLEVEL_32	= 3,
	STV090x_RPTLEVEL_16	= 4,
	STV090x_RPTLEVEL_8	= 5,
	STV090x_RPTLEVEL_4	= 6,
	STV090x_RPTLEVEL_2	= 7,
पूर्ण;

क्रमागत stv090x_adc_range अणु
	STV090x_ADC_2Vpp	= 0,
	STV090x_ADC_1Vpp	= 1
पूर्ण;

काष्ठा stv090x_config अणु
	क्रमागत stv090x_device	device;
	क्रमागत stv090x_mode	demod_mode;
	क्रमागत stv090x_clkmode	clk_mode;
	क्रमागत stv090x_demodulator demod;

	u32 xtal; /* शेष: 8000000 */
	u8 address; /* शेष: 0x68 */

	u8 ts1_mode;
	u8 ts2_mode;
	u32 ts1_clk;
	u32 ts2_clk;

	u8 ts1_tei : 1;
	u8 ts2_tei : 1;

	क्रमागत stv090x_i2crpt	repeater_level;

	u8			tuner_bbgain; /* शेष: 10db */
	क्रमागत stv090x_adc_range	adc1_range; /* शेष: 2Vpp */
	क्रमागत stv090x_adc_range	adc2_range; /* शेष: 2Vpp */

	bool diseqc_envelope_mode;

	पूर्णांक (*tuner_init)(काष्ठा dvb_frontend *fe);
	पूर्णांक (*tuner_sleep)(काष्ठा dvb_frontend *fe);
	पूर्णांक (*tuner_set_mode)(काष्ठा dvb_frontend *fe, क्रमागत tuner_mode mode);
	पूर्णांक (*tuner_set_frequency)(काष्ठा dvb_frontend *fe, u32 frequency);
	पूर्णांक (*tuner_get_frequency)(काष्ठा dvb_frontend *fe, u32 *frequency);
	पूर्णांक (*tuner_set_bandwidth)(काष्ठा dvb_frontend *fe, u32 bandwidth);
	पूर्णांक (*tuner_get_bandwidth)(काष्ठा dvb_frontend *fe, u32 *bandwidth);
	पूर्णांक (*tuner_set_bbgain)(काष्ठा dvb_frontend *fe, u32 gain);
	पूर्णांक (*tuner_get_bbgain)(काष्ठा dvb_frontend *fe, u32 *gain);
	पूर्णांक (*tuner_set_refclk)(काष्ठा dvb_frontend *fe, u32 refclk);
	पूर्णांक (*tuner_get_status)(काष्ठा dvb_frontend *fe, u32 *status);
	व्योम (*tuner_i2c_lock)(काष्ठा dvb_frontend *fe, पूर्णांक lock);

	/* dir = 0 -> output, dir = 1 -> input/खोलो-drain */
	पूर्णांक (*set_gpio)(काष्ठा dvb_frontend *fe, u8 gpio, u8 dir, u8 value,
			u8 xor_value);

	काष्ठा dvb_frontend* (*get_dvb_frontend)(काष्ठा i2c_client *i2c);
पूर्ण;

#अगर IS_REACHABLE(CONFIG_DVB_STV090x)

काष्ठा dvb_frontend *stv090x_attach(काष्ठा stv090x_config *config,
				    काष्ठा i2c_adapter *i2c,
				    क्रमागत stv090x_demodulator demod);

#अन्यथा

अटल अंतरभूत काष्ठा dvb_frontend *stv090x_attach(स्थिर काष्ठा stv090x_config *config,
						  काष्ठा i2c_adapter *i2c,
						  क्रमागत stv090x_demodulator demod)
अणु
	prपूर्णांकk(KERN_WARNING "%s: driver disabled by Kconfig\n", __func__);
	वापस शून्य;
पूर्ण

#पूर्ण_अगर /* CONFIG_DVB_STV090x */

#पूर्ण_अगर /* __STV090x_H */
