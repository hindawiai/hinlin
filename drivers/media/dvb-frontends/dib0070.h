<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Linux-DVB Driver क्रम DiBcom's DiB0070 base-band RF Tuner.
 *
 * Copyright (C) 2005-7 DiBcom (http://www.dibcom.fr/)
 */
#अगर_अघोषित DIB0070_H
#घोषणा DIB0070_H

काष्ठा dvb_frontend;
काष्ठा i2c_adapter;

#घोषणा DEFAULT_DIB0070_I2C_ADDRESS 0x60

काष्ठा dib0070_wbd_gain_cfg अणु
	u16 freq;
	u16 wbd_gain_val;
पूर्ण;

काष्ठा dib0070_config अणु
	u8 i2c_address;

	/* tuner pins controlled बाह्यally */
	पूर्णांक (*reset) (काष्ठा dvb_frontend *, पूर्णांक);
	पूर्णांक (*sleep) (काष्ठा dvb_frontend *, पूर्णांक);

	/*  offset in kHz */
	पूर्णांक freq_offset_khz_uhf;
	पूर्णांक freq_offset_khz_vhf;

	u8 osc_buffer_state;	/* 0= normal, 1= tri-state */
	u32 घड़ी_khz;
	u8 घड़ी_pad_drive;	/* (Drive + 1) * 2mA */

	u8 invert_iq;		/* invert Q - in हाल I or Q is inverted on the board */

	u8 क्रमce_crystal_mode;	/* अगर == 0 -> decision is made in the driver शेष: <24 -> 2, >=24 -> 1 */

	u8 flip_chip;
	u8 enable_third_order_filter;
	u8 अक्षरge_pump;

	स्थिर काष्ठा dib0070_wbd_gain_cfg *wbd_gain;

	u8 vga_filter;
पूर्ण;

#अगर IS_REACHABLE(CONFIG_DVB_TUNER_DIB0070)
बाह्य काष्ठा dvb_frontend *dib0070_attach(काष्ठा dvb_frontend *fe, काष्ठा i2c_adapter *i2c, काष्ठा dib0070_config *cfg);
बाह्य u16 dib0070_wbd_offset(काष्ठा dvb_frontend *);
बाह्य व्योम dib0070_ctrl_agc_filter(काष्ठा dvb_frontend *, u8 खोलो);
बाह्य u8 dib0070_get_rf_output(काष्ठा dvb_frontend *fe);
बाह्य पूर्णांक dib0070_set_rf_output(काष्ठा dvb_frontend *fe, u8 no);
#अन्यथा
अटल अंतरभूत काष्ठा dvb_frontend *dib0070_attach(काष्ठा dvb_frontend *fe, काष्ठा i2c_adapter *i2c, काष्ठा dib0070_config *cfg)
अणु
	prपूर्णांकk(KERN_WARNING "%s: driver disabled by Kconfig\n", __func__);
	वापस शून्य;
पूर्ण

अटल अंतरभूत u16 dib0070_wbd_offset(काष्ठा dvb_frontend *fe)
अणु
	prपूर्णांकk(KERN_WARNING "%s: driver disabled by Kconfig\n", __func__);
	वापस 0;
पूर्ण

अटल अंतरभूत व्योम dib0070_ctrl_agc_filter(काष्ठा dvb_frontend *fe, u8 खोलो)
अणु
	prपूर्णांकk(KERN_WARNING "%s: driver disabled by Kconfig\n", __func__);
पूर्ण
#पूर्ण_अगर

#पूर्ण_अगर
