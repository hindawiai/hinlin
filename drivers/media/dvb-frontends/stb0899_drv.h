<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
	STB0899 Multistandard Frontend driver
	Copyright (C) Manu Abraham (abraham.manu@gmail.com)

	Copyright (C) ST Microelectronics

*/

#अगर_अघोषित __STB0899_DRV_H
#घोषणा __STB0899_DRV_H

#समावेश <linux/kernel.h>
#समावेश <linux/module.h>

#समावेश <media/dvb_frontend.h>

#घोषणा STB0899_TSMODE_SERIAL		1
#घोषणा STB0899_CLKPOL_FALLING		2
#घोषणा STB0899_CLKशून्य_PARITY		3
#घोषणा STB0899_SYNC_FORCED		4
#घोषणा STB0899_FECMODE_DSS		5

काष्ठा stb0899_s1_reg अणु
	u16	address;
	u8	data;
पूर्ण;

काष्ठा stb0899_s2_reg अणु
	u16	offset;
	u32	base_address;
	u32	data;
पूर्ण;

क्रमागत stb0899_inversion अणु
	IQ_SWAP_OFF	= +1, /* inversion affects the sign of e. g. */
	IQ_SWAP_ON	= -1, /* the derotator frequency रेजिस्टर    */
पूर्ण;

#घोषणा STB0899_GPIO00				0xf140
#घोषणा STB0899_GPIO01				0xf141
#घोषणा STB0899_GPIO02				0xf142
#घोषणा STB0899_GPIO03				0xf143
#घोषणा STB0899_GPIO04				0xf144
#घोषणा STB0899_GPIO05				0xf145
#घोषणा STB0899_GPIO06				0xf146
#घोषणा STB0899_GPIO07				0xf147
#घोषणा STB0899_GPIO08				0xf148
#घोषणा STB0899_GPIO09				0xf149
#घोषणा STB0899_GPIO10				0xf14a
#घोषणा STB0899_GPIO11				0xf14b
#घोषणा STB0899_GPIO12				0xf14c
#घोषणा STB0899_GPIO13				0xf14d
#घोषणा STB0899_GPIO14				0xf14e
#घोषणा STB0899_GPIO15				0xf14f
#घोषणा STB0899_GPIO16				0xf150
#घोषणा STB0899_GPIO17				0xf151
#घोषणा STB0899_GPIO18				0xf152
#घोषणा STB0899_GPIO19				0xf153
#घोषणा STB0899_GPIO20				0xf154

#घोषणा STB0899_GPIOPULLUP			0x01 /* Output device is connected to Vdd */
#घोषणा STB0899_GPIOPULLDN			0x00 /* Output device is connected to Vss */

#घोषणा STB0899_POSTPROC_GPIO_POWER		0x00
#घोषणा STB0899_POSTPROC_GPIO_LOCK		0x01

/*
 * Post process output configuration control
 * 1. POWER ON/OFF		(index 0)
 * 2. FE_HAS_LOCK/LOCK_LOSS	(index 1)
 *
 * @gpio	= one of the above listed GPIO's
 * @level	= output state: pulled up or low
 */
काष्ठा stb0899_postproc अणु
	u16	gpio;
	u8	level;
पूर्ण;

काष्ठा stb0899_config अणु
	स्थिर काष्ठा stb0899_s1_reg	*init_dev;
	स्थिर काष्ठा stb0899_s2_reg	*init_s2_demod;
	स्थिर काष्ठा stb0899_s1_reg	*init_s1_demod;
	स्थिर काष्ठा stb0899_s2_reg	*init_s2_fec;
	स्थिर काष्ठा stb0899_s1_reg	*init_tst;

	स्थिर काष्ठा stb0899_postproc	*postproc;

	क्रमागत stb0899_inversion		inversion;

	u32	xtal_freq;

	u8	demod_address;
	u8	ts_output_mode;
	u8	block_sync_mode;
	u8	ts_pfbit_toggle;

	u8	घड़ी_polarity;
	u8	data_clk_parity;
	u8	fec_mode;
	u8	data_output_ctl;
	u8	data_fअगरo_mode;
	u8	out_rate_comp;
	u8	i2c_repeater;
//	पूर्णांक	inversion;
	पूर्णांक	lo_clk;
	पूर्णांक	hi_clk;

	u32	esno_ave;
	u32	esno_quant;
	u32	avframes_coarse;
	u32	avframes_fine;
	u32	miss_threshold;
	u32	uwp_threshold_acq;
	u32	uwp_threshold_track;
	u32	uwp_threshold_sof;
	u32	sof_search_समयout;

	u32	btr_nco_bits;
	u32	btr_gain_shअगरt_offset;
	u32	crl_nco_bits;
	u32	ldpc_max_iter;

	पूर्णांक (*tuner_set_frequency)(काष्ठा dvb_frontend *fe, u32 frequency);
	पूर्णांक (*tuner_get_frequency)(काष्ठा dvb_frontend *fe, u32 *frequency);
	पूर्णांक (*tuner_set_bandwidth)(काष्ठा dvb_frontend *fe, u32 bandwidth);
	पूर्णांक (*tuner_get_bandwidth)(काष्ठा dvb_frontend *fe, u32 *bandwidth);
	पूर्णांक (*tuner_set_rfsiggain)(काष्ठा dvb_frontend *fe, u32 rf_gain);
पूर्ण;

#अगर IS_REACHABLE(CONFIG_DVB_STB0899)

बाह्य काष्ठा dvb_frontend *stb0899_attach(काष्ठा stb0899_config *config,
					   काष्ठा i2c_adapter *i2c);

#अन्यथा

अटल अंतरभूत काष्ठा dvb_frontend *stb0899_attach(काष्ठा stb0899_config *config,
						  काष्ठा i2c_adapter *i2c)
अणु
	prपूर्णांकk(KERN_WARNING "%s: Driver disabled by Kconfig\n", __func__);
	वापस शून्य;
पूर्ण

#पूर्ण_अगर //CONFIG_DVB_STB0899


#पूर्ण_अगर
