<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित DIB7000P_H
#घोषणा DIB7000P_H

#समावेश "dibx000_common.h"

काष्ठा dib7000p_config अणु
	u8 output_mpeg2_in_188_bytes;
	u8 hostbus_भागersity;
	u8 tuner_is_baseband;
	पूर्णांक (*update_lna) (काष्ठा dvb_frontend *, u16 agc_global);

	u8 agc_config_count;
	काष्ठा dibx000_agc_config *agc;
	काष्ठा dibx000_bandwidth_config *bw;

#घोषणा DIB7000P_GPIO_DEFAULT_सूचीECTIONS 0xffff
	u16 gpio_dir;
#घोषणा DIB7000P_GPIO_DEFAULT_VALUES     0x0000
	u16 gpio_val;
#घोषणा DIB7000P_GPIO_PWM_POS0(v)        ((v & 0xf) << 12)
#घोषणा DIB7000P_GPIO_PWM_POS1(v)        ((v & 0xf) << 8 )
#घोषणा DIB7000P_GPIO_PWM_POS2(v)        ((v & 0xf) << 4 )
#घोषणा DIB7000P_GPIO_PWM_POS3(v)         (v & 0xf)
#घोषणा DIB7000P_GPIO_DEFAULT_PWM_POS    0xffff
	u16 gpio_pwm_pos;

	u16 pwm_freq_भाग;

	u8 quartz_direct;

	u8 spur_protect;

	पूर्णांक (*agc_control) (काष्ठा dvb_frontend *, u8 beक्रमe);

	u8 output_mode;
	u8 disable_sample_and_hold:1;

	u8 enable_current_mirror:1;
	u16 भागersity_delay;

	u8 शेष_i2c_addr;
	u8 enMpegOutput:1;
पूर्ण;

#घोषणा DEFAULT_DIB7000P_I2C_ADDRESS 18

काष्ठा dib7000p_ops अणु
	पूर्णांक (*set_wbd_ref)(काष्ठा dvb_frontend *demod, u16 value);
	पूर्णांक (*get_agc_values)(काष्ठा dvb_frontend *fe,
		u16 *agc_global, u16 *agc1, u16 *agc2, u16 *wbd);
	पूर्णांक (*set_agc1_min)(काष्ठा dvb_frontend *fe, u16 v);
	पूर्णांक (*update_pll)(काष्ठा dvb_frontend *fe, काष्ठा dibx000_bandwidth_config *bw);
	पूर्णांक (*set_gpio)(काष्ठा dvb_frontend *demod, u8 num, u8 dir, u8 val);
	u32 (*ctrl_timf)(काष्ठा dvb_frontend *fe, u8 op, u32 timf);
	पूर्णांक (*dib7000pc_detection)(काष्ठा i2c_adapter *i2c_adap);
	काष्ठा i2c_adapter *(*get_i2c_master)(काष्ठा dvb_frontend *demod, क्रमागत dibx000_i2c_पूर्णांकerface पूर्णांकf, पूर्णांक gating);
	पूर्णांक (*pid_filter_ctrl)(काष्ठा dvb_frontend *fe, u8 onoff);
	पूर्णांक (*pid_filter)(काष्ठा dvb_frontend *fe, u8 id, u16 pid, u8 onoff);
	पूर्णांक (*i2c_क्रमागतeration)(काष्ठा i2c_adapter *i2c, पूर्णांक no_of_demods, u8 शेष_addr, काष्ठा dib7000p_config cfg[]);
	काष्ठा i2c_adapter *(*get_i2c_tuner)(काष्ठा dvb_frontend *fe);
	पूर्णांक (*tuner_sleep)(काष्ठा dvb_frontend *fe, पूर्णांक onoff);
	पूर्णांक (*get_adc_घातer)(काष्ठा dvb_frontend *fe);
	पूर्णांक (*slave_reset)(काष्ठा dvb_frontend *fe);
	काष्ठा dvb_frontend *(*init)(काष्ठा i2c_adapter *i2c_adap, u8 i2c_addr, काष्ठा dib7000p_config *cfg);
पूर्ण;

#अगर IS_REACHABLE(CONFIG_DVB_DIB7000P)
व्योम *dib7000p_attach(काष्ठा dib7000p_ops *ops);
#अन्यथा
अटल अंतरभूत व्योम *dib7000p_attach(काष्ठा dib7000p_ops *ops)
अणु
	prपूर्णांकk(KERN_WARNING "%s: driver disabled by Kconfig\n", __func__);
	वापस शून्य;
पूर्ण
#पूर्ण_अगर

#पूर्ण_अगर
