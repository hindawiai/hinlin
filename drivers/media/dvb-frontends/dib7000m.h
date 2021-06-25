<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित DIB7000M_H
#घोषणा DIB7000M_H

#समावेश "dibx000_common.h"

काष्ठा dib7000m_config अणु
	u8 dvbt_mode;
	u8 output_mpeg2_in_188_bytes;
	u8 hostbus_भागersity;
	u8 tuner_is_baseband;
	u8 mobile_mode;
	पूर्णांक (*update_lna) (काष्ठा dvb_frontend *, u16 agc_global);

	u8 agc_config_count;
	काष्ठा dibx000_agc_config *agc;

	काष्ठा dibx000_bandwidth_config *bw;

#घोषणा DIB7000M_GPIO_DEFAULT_सूचीECTIONS 0xffff
	u16 gpio_dir;
#घोषणा DIB7000M_GPIO_DEFAULT_VALUES     0x0000
	u16 gpio_val;
#घोषणा DIB7000M_GPIO_PWM_POS0(v)        ((v & 0xf) << 12)
#घोषणा DIB7000M_GPIO_PWM_POS1(v)        ((v & 0xf) << 8 )
#घोषणा DIB7000M_GPIO_PWM_POS2(v)        ((v & 0xf) << 4 )
#घोषणा DIB7000M_GPIO_PWM_POS3(v)         (v & 0xf)
#घोषणा DIB7000M_GPIO_DEFAULT_PWM_POS    0xffff
	u16 gpio_pwm_pos;

	u16 pwm_freq_भाग;

	u8 quartz_direct;

	u8 input_clk_is_भाग_2;

	पूर्णांक (*agc_control) (काष्ठा dvb_frontend *, u8 beक्रमe);
पूर्ण;

#घोषणा DEFAULT_DIB7000M_I2C_ADDRESS 18

#अगर IS_REACHABLE(CONFIG_DVB_DIB7000M)
बाह्य काष्ठा dvb_frontend *dib7000m_attach(काष्ठा i2c_adapter *i2c_adap,
					    u8 i2c_addr,
					    काष्ठा dib7000m_config *cfg);
बाह्य काष्ठा i2c_adapter *dib7000m_get_i2c_master(काष्ठा dvb_frontend *,
						   क्रमागत dibx000_i2c_पूर्णांकerface,
						   पूर्णांक);
बाह्य पूर्णांक dib7000m_pid_filter(काष्ठा dvb_frontend *, u8 id, u16 pid, u8 onoff);
बाह्य पूर्णांक dib7000m_pid_filter_ctrl(काष्ठा dvb_frontend *fe, u8 onoff);
#अन्यथा
अटल अंतरभूत
काष्ठा dvb_frontend *dib7000m_attach(काष्ठा i2c_adapter *i2c_adap,
				     u8 i2c_addr, काष्ठा dib7000m_config *cfg)
अणु
	prपूर्णांकk(KERN_WARNING "%s: driver disabled by Kconfig\n", __func__);
	वापस शून्य;
पूर्ण

अटल अंतरभूत
काष्ठा i2c_adapter *dib7000m_get_i2c_master(काष्ठा dvb_frontend *demod,
					    क्रमागत dibx000_i2c_पूर्णांकerface पूर्णांकf,
					    पूर्णांक gating)
अणु
	prपूर्णांकk(KERN_WARNING "%s: driver disabled by Kconfig\n", __func__);
	वापस शून्य;
पूर्ण
अटल अंतरभूत पूर्णांक dib7000m_pid_filter(काष्ठा dvb_frontend *fe, u8 id,
						u16 pid, u8 onoff)
अणु
	prपूर्णांकk(KERN_WARNING "%s: driver disabled by Kconfig\n", __func__);
	वापस -ENODEV;
पूर्ण

अटल अंतरभूत पूर्णांक dib7000m_pid_filter_ctrl(काष्ठा dvb_frontend *fe,
						uपूर्णांक8_t onoff)
अणु
	prपूर्णांकk(KERN_WARNING "%s: driver disabled by Kconfig\n", __func__);
	वापस -ENODEV;
पूर्ण
#पूर्ण_अगर

/* TODO
बाह्य INT dib7000m_set_gpio(काष्ठा dibDemod *demod, UCHAR num, UCHAR dir, UCHAR val);
बाह्य INT dib7000m_enable_vbg_voltage(काष्ठा dibDemod *demod);
बाह्य व्योम dib7000m_set_hostbus_भागersity(काष्ठा dibDemod *demod, UCHAR onoff);
बाह्य USHORT dib7000m_get_current_agc_global(काष्ठा dibDemod *demod);
*/

#पूर्ण_अगर
