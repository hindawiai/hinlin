<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
    tda18271.h - header क्रम the Philips / NXP TDA18271 silicon tuner

    Copyright (C) 2007, 2008 Michael Krufky <mkrufky@linuxtv.org>

*/

#अगर_अघोषित __TDA18271_H__
#घोषणा __TDA18271_H__

#समावेश <linux/i2c.h>
#समावेश <media/dvb_frontend.h>

काष्ठा tda18271_std_map_item अणु
	u16 अगर_freq;

	/* EP3[4:3] */
	अचिन्हित पूर्णांक agc_mode:2;
	/* EP3[2:0] */
	अचिन्हित पूर्णांक std:3;
	/* EP4[7] */
	अचिन्हित पूर्णांक fm_rfn:1;
	/* EP4[4:2] */
	अचिन्हित पूर्णांक अगर_lvl:3;
	/* EB22[6:0] */
	अचिन्हित पूर्णांक rfagc_top:7;
पूर्ण;

काष्ठा tda18271_std_map अणु
	काष्ठा tda18271_std_map_item fm_radio;
	काष्ठा tda18271_std_map_item atv_b;
	काष्ठा tda18271_std_map_item atv_dk;
	काष्ठा tda18271_std_map_item atv_gh;
	काष्ठा tda18271_std_map_item atv_i;
	काष्ठा tda18271_std_map_item atv_l;
	काष्ठा tda18271_std_map_item atv_lc;
	काष्ठा tda18271_std_map_item atv_mn;
	काष्ठा tda18271_std_map_item atsc_6;
	काष्ठा tda18271_std_map_item dvbt_6;
	काष्ठा tda18271_std_map_item dvbt_7;
	काष्ठा tda18271_std_map_item dvbt_8;
	काष्ठा tda18271_std_map_item qam_6;
	काष्ठा tda18271_std_map_item qam_7;
	काष्ठा tda18271_std_map_item qam_8;
पूर्ण;

क्रमागत tda18271_role अणु
	TDA18271_MASTER = 0,
	TDA18271_SLAVE,
पूर्ण;

क्रमागत tda18271_i2c_gate अणु
	TDA18271_GATE_AUTO = 0,
	TDA18271_GATE_ANALOG,
	TDA18271_GATE_DIGITAL,
पूर्ण;

क्रमागत tda18271_output_options अणु
	/* slave tuner output & loop through & xtal oscillator always on */
	TDA18271_OUTPUT_LT_XT_ON = 0,

	/* slave tuner output loop through off */
	TDA18271_OUTPUT_LT_OFF = 1,

	/* xtal oscillator off */
	TDA18271_OUTPUT_XT_OFF = 2,
पूर्ण;

क्रमागत tda18271_small_i2c अणु
	TDA18271_39_BYTE_CHUNK_INIT = 0,
	TDA18271_16_BYTE_CHUNK_INIT = 16,
	TDA18271_08_BYTE_CHUNK_INIT = 8,
	TDA18271_03_BYTE_CHUNK_INIT = 3,
पूर्ण;

काष्ठा tda18271_config अणु
	/* override शेष अगर freq / std settings (optional) */
	काष्ठा tda18271_std_map *std_map;

	/* master / slave tuner: master uses मुख्य pll, slave uses cal pll */
	क्रमागत tda18271_role role;

	/* use i2c gate provided by analog or digital demod */
	क्रमागत tda18271_i2c_gate gate;

	/* output options that can be disabled */
	क्रमागत tda18271_output_options output_opt;

	/* some i2c providers can't ग_लिखो all 39 रेजिस्टरs at once */
	क्रमागत tda18271_small_i2c small_i2c;

	/* क्रमce rf tracking filter calibration on startup */
	अचिन्हित पूर्णांक rf_cal_on_startup:1;

	/* prevent any रेजिस्टर access during attach(),
	 * delaying both IR & RF calibration until init()
	 * module option 'cal' overrides this delay */
	अचिन्हित पूर्णांक delay_cal:1;

	/* पूर्णांकerface to saa713x / tda829x */
	अचिन्हित पूर्णांक config;
पूर्ण;

#घोषणा TDA18271_CALLBACK_CMD_AGC_ENABLE 0

क्रमागत tda18271_mode अणु
	TDA18271_ANALOG = 0,
	TDA18271_DIGITAL,
पूर्ण;

#अगर IS_REACHABLE(CONFIG_MEDIA_TUNER_TDA18271)
बाह्य काष्ठा dvb_frontend *tda18271_attach(काष्ठा dvb_frontend *fe, u8 addr,
					    काष्ठा i2c_adapter *i2c,
					    काष्ठा tda18271_config *cfg);
#अन्यथा
अटल अंतरभूत काष्ठा dvb_frontend *tda18271_attach(काष्ठा dvb_frontend *fe,
						   u8 addr,
						   काष्ठा i2c_adapter *i2c,
						   काष्ठा tda18271_config *cfg)
अणु
	prपूर्णांकk(KERN_WARNING "%s: driver disabled by Kconfig\n", __func__);
	वापस शून्य;
पूर्ण
#पूर्ण_अगर

#पूर्ण_अगर /* __TDA18271_H__ */
