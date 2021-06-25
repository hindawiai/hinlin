<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Driver क्रम DiBcom DiB3000MC/P-demodulator.
 *
 * Copyright (C) 2004-6 DiBcom (http://www.dibcom.fr/)
 * Copyright (C) 2004-5 Patrick Boettcher (patrick.boettcher@posteo.de)
 *
 * This code is partially based on the previous dib3000mc.c .
 */
#अगर_अघोषित DIB3000MC_H
#घोषणा DIB3000MC_H

#समावेश "dibx000_common.h"

काष्ठा dib3000mc_config अणु
	काष्ठा dibx000_agc_config *agc;

	u8 phase_noise_mode;
	u8 impulse_noise_mode;

	u8  pwm3_inversion;
	u8  use_pwm3;
	u16 pwm3_value;

	u16 max_समय;
	u16 ln_adc_level;

	u8 agc_command1 :1;
	u8 agc_command2 :1;

	u8 mobile_mode;

	u8 output_mpeg2_in_188_bytes;
पूर्ण;

#घोषणा DEFAULT_DIB3000MC_I2C_ADDRESS 16
#घोषणा DEFAULT_DIB3000P_I2C_ADDRESS  24

#अगर IS_REACHABLE(CONFIG_DVB_DIB3000MC)
बाह्य काष्ठा dvb_frontend *dib3000mc_attach(काष्ठा i2c_adapter *i2c_adap,
					     u8 i2c_addr,
					     काष्ठा dib3000mc_config *cfg);
बाह्य पूर्णांक dib3000mc_i2c_क्रमागतeration(काष्ठा i2c_adapter *i2c,
				     पूर्णांक no_of_demods, u8 शेष_addr,
				     काष्ठा dib3000mc_config cfg[]);
बाह्य
काष्ठा i2c_adapter *dib3000mc_get_tuner_i2c_master(काष्ठा dvb_frontend *demod,
						   पूर्णांक gating);
#अन्यथा
अटल अंतरभूत
काष्ठा dvb_frontend *dib3000mc_attach(काष्ठा i2c_adapter *i2c_adap, u8 i2c_addr,
				      काष्ठा dib3000mc_config *cfg)
अणु
	prपूर्णांकk(KERN_WARNING "%s: driver disabled by Kconfig\n", __func__);
	वापस शून्य;
पूर्ण

अटल अंतरभूत
पूर्णांक dib3000mc_i2c_क्रमागतeration(काष्ठा i2c_adapter *i2c,
			      पूर्णांक no_of_demods, u8 शेष_addr,
			      काष्ठा dib3000mc_config cfg[])
अणु
	prपूर्णांकk(KERN_WARNING "%s: driver disabled by Kconfig\n", __func__);
	वापस -ENODEV;
पूर्ण

अटल अंतरभूत
काष्ठा i2c_adapter *dib3000mc_get_tuner_i2c_master(काष्ठा dvb_frontend *demod,
						   पूर्णांक gating)
अणु
	prपूर्णांकk(KERN_WARNING "%s: driver disabled by Kconfig\n", __func__);
	वापस शून्य;
पूर्ण
#पूर्ण_अगर // CONFIG_DVB_DIB3000MC

बाह्य पूर्णांक dib3000mc_pid_control(काष्ठा dvb_frontend *fe, पूर्णांक index, पूर्णांक pid,पूर्णांक onoff);
बाह्य पूर्णांक dib3000mc_pid_parse(काष्ठा dvb_frontend *fe, पूर्णांक onoff);

बाह्य व्योम dib3000mc_set_config(काष्ठा dvb_frontend *, काष्ठा dib3000mc_config *);

#पूर्ण_अगर
