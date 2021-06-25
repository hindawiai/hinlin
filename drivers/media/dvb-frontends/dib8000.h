<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित DIB8000_H
#घोषणा DIB8000_H

#समावेश "dibx000_common.h"

काष्ठा dib8000_config अणु
	u8 output_mpeg2_in_188_bytes;
	u8 hostbus_भागersity;
	u8 tuner_is_baseband;
	पूर्णांक (*update_lna) (काष्ठा dvb_frontend *, u16 agc_global);

	u8 agc_config_count;
	काष्ठा dibx000_agc_config *agc;
	काष्ठा dibx000_bandwidth_config *pll;

#घोषणा DIB8000_GPIO_DEFAULT_सूचीECTIONS 0xffff
	u16 gpio_dir;
#घोषणा DIB8000_GPIO_DEFAULT_VALUES     0x0000
	u16 gpio_val;
#घोषणा DIB8000_GPIO_PWM_POS0(v)        ((v & 0xf) << 12)
#घोषणा DIB8000_GPIO_PWM_POS1(v)        ((v & 0xf) << 8 )
#घोषणा DIB8000_GPIO_PWM_POS2(v)        ((v & 0xf) << 4 )
#घोषणा DIB8000_GPIO_PWM_POS3(v)         (v & 0xf)
#घोषणा DIB8000_GPIO_DEFAULT_PWM_POS    0xffff
	u16 gpio_pwm_pos;
	u16 pwm_freq_भाग;

	व्योम (*agc_control) (काष्ठा dvb_frontend *, u8 beक्रमe);

	u16 drives;
	u16 भागersity_delay;
	u8 भाग_cfg;
	u8 output_mode;
	u8 refclksel;
	u8 enMpegOutput:1;

	काष्ठा dibx000_bandwidth_config *plltable;
पूर्ण;

#घोषणा DEFAULT_DIB8000_I2C_ADDRESS 18

काष्ठा dib8000_ops अणु
	पूर्णांक (*set_wbd_ref)(काष्ठा dvb_frontend *fe, u16 value);
	पूर्णांक (*update_pll)(काष्ठा dvb_frontend *fe,
		काष्ठा dibx000_bandwidth_config *pll, u32 bw, u8 ratio);
	पूर्णांक (*set_gpio)(काष्ठा dvb_frontend *fe, u8 num, u8 dir, u8 val);
	व्योम (*pwm_agc_reset)(काष्ठा dvb_frontend *fe);
	काष्ठा i2c_adapter *(*get_i2c_tuner)(काष्ठा dvb_frontend *fe);
	पूर्णांक (*tuner_sleep)(काष्ठा dvb_frontend *fe, पूर्णांक onoff);
	s32 (*get_adc_घातer)(काष्ठा dvb_frontend *fe, u8 mode);
	पूर्णांक (*get_dc_घातer)(काष्ठा dvb_frontend *fe, u8 IQ);
	u32 (*ctrl_timf)(काष्ठा dvb_frontend *fe, uपूर्णांक8_t op, uपूर्णांक32_t timf);
	क्रमागत frontend_tune_state (*get_tune_state)(काष्ठा dvb_frontend *fe);
	पूर्णांक (*set_tune_state)(काष्ठा dvb_frontend *fe, क्रमागत frontend_tune_state tune_state);
	पूर्णांक (*set_slave_frontend)(काष्ठा dvb_frontend *fe, काष्ठा dvb_frontend *fe_slave);
	काष्ठा dvb_frontend *(*get_slave_frontend)(काष्ठा dvb_frontend *fe, पूर्णांक slave_index);
	पूर्णांक (*i2c_क्रमागतeration)(काष्ठा i2c_adapter *host, पूर्णांक no_of_demods,
		u8 शेष_addr, u8 first_addr, u8 is_dib8096p);
	काष्ठा i2c_adapter *(*get_i2c_master)(काष्ठा dvb_frontend *fe, क्रमागत dibx000_i2c_पूर्णांकerface पूर्णांकf, पूर्णांक gating);
	पूर्णांक (*pid_filter_ctrl)(काष्ठा dvb_frontend *fe, u8 onoff);
	पूर्णांक (*pid_filter)(काष्ठा dvb_frontend *fe, u8 id, u16 pid, u8 onoff);
	काष्ठा dvb_frontend *(*init)(काष्ठा i2c_adapter *i2c_adap, u8 i2c_addr, काष्ठा dib8000_config *cfg);
पूर्ण;

#अगर IS_REACHABLE(CONFIG_DVB_DIB8000)
व्योम *dib8000_attach(काष्ठा dib8000_ops *ops);
#अन्यथा
अटल अंतरभूत व्योम *dib8000_attach(काष्ठा dib8000_ops *ops)
अणु
	prपूर्णांकk(KERN_WARNING "%s: driver disabled by Kconfig\n", __func__);
	वापस शून्य;
पूर्ण
#पूर्ण_अगर

#पूर्ण_अगर
