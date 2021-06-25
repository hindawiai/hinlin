<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Linux-DVB Driver क्रम DiBcom's DiB0090 base-band RF Tuner.
 *
 * Copyright (C) 2005-7 DiBcom (http://www.dibcom.fr/)
 */
#अगर_अघोषित DIB0090_H
#घोषणा DIB0090_H

काष्ठा dvb_frontend;
काष्ठा i2c_adapter;

#घोषणा DEFAULT_DIB0090_I2C_ADDRESS 0x60

काष्ठा dib0090_io_config अणु
	u32 घड़ी_khz;

	u8 pll_bypass:1;
	u8 pll_range:1;
	u8 pll_preभाग:6;
	u8 pll_loopभाग:6;

	u8 adc_घड़ी_ratio;	/* valid is 8, 7 ,6 */
	u16 pll_पूर्णांक_loop_filt;
पूर्ण;

काष्ठा dib0090_wbd_slope अणु
	u16 max_freq;		/* क्रम every frequency less than or equal to that field: this inक्रमmation is correct */
	u16 slope_cold;
	u16 offset_cold;
	u16 slope_hot;
	u16 offset_hot;
	u8 wbd_gain;
पूर्ण;

काष्ठा dib0090_low_अगर_offset_table अणु
	पूर्णांक std;
	u32 RF_freq;
	s32 offset_khz;
पूर्ण;

काष्ठा dib0090_config अणु
	काष्ठा dib0090_io_config io;
	पूर्णांक (*reset) (काष्ठा dvb_frontend *, पूर्णांक);
	पूर्णांक (*sleep) (काष्ठा dvb_frontend *, पूर्णांक);

	/*  offset in kHz */
	पूर्णांक freq_offset_khz_uhf;
	पूर्णांक freq_offset_khz_vhf;

	पूर्णांक (*get_adc_घातer) (काष्ठा dvb_frontend *);

	u8 clkouttobamse:1;	/* activate or deactivate घड़ी output */
	u8 analog_output;

	u8 i2c_address;
	/* add drives and other things अगर necessary */
	u16 wbd_vhf_offset;
	u16 wbd_cband_offset;
	u8 use_pwm_agc;
	u8 clkoutdrive;

	u8 ls_cfg_pad_drv;
	u8 data_tx_drv;

	u8 in_soc;
	स्थिर काष्ठा dib0090_low_अगर_offset_table *low_अगर;
	u8 fref_घड़ी_ratio;
	u16 क्रमce_cband_input;
	काष्ठा dib0090_wbd_slope *wbd;
	u8 is_dib7090e;
	u8 क्रमce_crystal_mode;
पूर्ण;

#अगर IS_REACHABLE(CONFIG_DVB_TUNER_DIB0090)
बाह्य काष्ठा dvb_frontend *dib0090_रेजिस्टर(काष्ठा dvb_frontend *fe, काष्ठा i2c_adapter *i2c, स्थिर काष्ठा dib0090_config *config);
बाह्य काष्ठा dvb_frontend *dib0090_fw_रेजिस्टर(काष्ठा dvb_frontend *fe, काष्ठा i2c_adapter *i2c, स्थिर काष्ठा dib0090_config *config);
बाह्य व्योम dib0090_dcc_freq(काष्ठा dvb_frontend *fe, u8 fast);
बाह्य व्योम dib0090_pwm_gain_reset(काष्ठा dvb_frontend *fe);
बाह्य u16 dib0090_get_wbd_target(काष्ठा dvb_frontend *tuner);
बाह्य u16 dib0090_get_wbd_offset(काष्ठा dvb_frontend *fe);
बाह्य पूर्णांक dib0090_gain_control(काष्ठा dvb_frontend *fe);
बाह्य क्रमागत frontend_tune_state dib0090_get_tune_state(काष्ठा dvb_frontend *fe);
बाह्य पूर्णांक dib0090_set_tune_state(काष्ठा dvb_frontend *fe, क्रमागत frontend_tune_state tune_state);
बाह्य व्योम dib0090_get_current_gain(काष्ठा dvb_frontend *fe, u16 * rf, u16 * bb, u16 * rf_gain_limit, u16 * rflt);
बाह्य व्योम dib0090_set_dc_servo(काष्ठा dvb_frontend *fe, u8 DC_servo_cutoff);
बाह्य पूर्णांक dib0090_set_चयन(काष्ठा dvb_frontend *fe, u8 sw1, u8 sw2, u8 sw3);
बाह्य पूर्णांक dib0090_set_vga(काष्ठा dvb_frontend *fe, u8 onoff);
बाह्य पूर्णांक dib0090_update_rframp_7090(काष्ठा dvb_frontend *fe,
		u8 cfg_sensitivity);
बाह्य पूर्णांक dib0090_update_tuning_table_7090(काष्ठा dvb_frontend *fe,
		u8 cfg_sensitivity);
#अन्यथा
अटल अंतरभूत काष्ठा dvb_frontend *dib0090_रेजिस्टर(काष्ठा dvb_frontend *fe, काष्ठा i2c_adapter *i2c, स्थिर काष्ठा dib0090_config *config)
अणु
	prपूर्णांकk(KERN_WARNING "%s: driver disabled by Kconfig\n", __func__);
	वापस शून्य;
पूर्ण

अटल अंतरभूत काष्ठा dvb_frontend *dib0090_fw_रेजिस्टर(काष्ठा dvb_frontend *fe, काष्ठा i2c_adapter *i2c, काष्ठा dib0090_config *config)
अणु
	prपूर्णांकk(KERN_WARNING "%s: driver disabled by Kconfig\n", __func__);
	वापस शून्य;
पूर्ण

अटल अंतरभूत व्योम dib0090_dcc_freq(काष्ठा dvb_frontend *fe, u8 fast)
अणु
	prपूर्णांकk(KERN_WARNING "%s: driver disabled by Kconfig\n", __func__);
पूर्ण

अटल अंतरभूत व्योम dib0090_pwm_gain_reset(काष्ठा dvb_frontend *fe)
अणु
	prपूर्णांकk(KERN_WARNING "%s: driver disabled by Kconfig\n", __func__);
पूर्ण

अटल अंतरभूत u16 dib0090_get_wbd_target(काष्ठा dvb_frontend *tuner)
अणु
	prपूर्णांकk(KERN_WARNING "%s: driver disabled by Kconfig\n", __func__);
	वापस 0;
पूर्ण

अटल अंतरभूत u16 dib0090_get_wbd_offset(काष्ठा dvb_frontend *fe)
अणु
	prपूर्णांकk(KERN_WARNING "%s: driver disabled by Kconfig\n", __func__);
	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक dib0090_gain_control(काष्ठा dvb_frontend *fe)
अणु
	prपूर्णांकk(KERN_WARNING "%s: driver disabled by Kconfig\n", __func__);
	वापस -ENODEV;
पूर्ण

अटल अंतरभूत क्रमागत frontend_tune_state dib0090_get_tune_state(काष्ठा dvb_frontend *fe)
अणु
	prपूर्णांकk(KERN_WARNING "%s: driver disabled by Kconfig\n", __func__);
	वापस CT_DONE;
पूर्ण

अटल अंतरभूत पूर्णांक dib0090_set_tune_state(काष्ठा dvb_frontend *fe, क्रमागत frontend_tune_state tune_state)
अणु
	prपूर्णांकk(KERN_WARNING "%s: driver disabled by Kconfig\n", __func__);
	वापस -ENODEV;
पूर्ण

अटल अंतरभूत व्योम dib0090_get_current_gain(काष्ठा dvb_frontend *fe, u16 * rf, u16 * bb, u16 * rf_gain_limit, u16 * rflt)
अणु
	prपूर्णांकk(KERN_WARNING "%s: driver disabled by Kconfig\n", __func__);
पूर्ण

अटल अंतरभूत व्योम dib0090_set_dc_servo(काष्ठा dvb_frontend *fe, u8 DC_servo_cutoff)
अणु
	prपूर्णांकk(KERN_WARNING "%s: driver disabled by Kconfig\n", __func__);
पूर्ण

अटल अंतरभूत पूर्णांक dib0090_set_चयन(काष्ठा dvb_frontend *fe,
		u8 sw1, u8 sw2, u8 sw3)
अणु
	prपूर्णांकk(KERN_WARNING "%s: driver disabled by Kconfig\n", __func__);
	वापस -ENODEV;
पूर्ण

अटल अंतरभूत पूर्णांक dib0090_set_vga(काष्ठा dvb_frontend *fe, u8 onoff)
अणु
	prपूर्णांकk(KERN_WARNING "%s: driver disabled by Kconfig\n", __func__);
	वापस -ENODEV;
पूर्ण

अटल अंतरभूत पूर्णांक dib0090_update_rframp_7090(काष्ठा dvb_frontend *fe,
		u8 cfg_sensitivity)
अणु
	prपूर्णांकk(KERN_WARNING "%s: driver disabled by Kconfig\n", __func__);
	वापस -ENODEV;
पूर्ण

अटल अंतरभूत पूर्णांक dib0090_update_tuning_table_7090(काष्ठा dvb_frontend *fe,
		u8 cfg_sensitivity)
अणु
	prपूर्णांकk(KERN_WARNING "%s: driver disabled by Kconfig\n", __func__);
	वापस -ENODEV;
पूर्ण
#पूर्ण_अगर

#पूर्ण_अगर
