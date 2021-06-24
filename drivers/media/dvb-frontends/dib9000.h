<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित DIB9000_H
#घोषणा DIB9000_H

#समावेश "dibx000_common.h"

काष्ठा dib9000_config अणु
	u8 dvbt_mode;
	u8 output_mpeg2_in_188_bytes;
	u8 hostbus_भागersity;
	काष्ठा dibx000_bandwidth_config *bw;

	u16 अगर_drives;

	u32 timing_frequency;
	u32 xtal_घड़ी_khz;
	u32 vcxo_समयr;
	u32 demod_घड़ी_khz;

	स्थिर u8 *microcode_B_fe_buffer;
	u32 microcode_B_fe_size;

	काष्ठा dibGPIOFunction gpio_function[2];
	काष्ठा dibSubbandSelection subband;

	u8 output_mode;
पूर्ण;

#घोषणा DEFAULT_DIB9000_I2C_ADDRESS 18

#अगर IS_REACHABLE(CONFIG_DVB_DIB9000)
बाह्य काष्ठा dvb_frontend *dib9000_attach(काष्ठा i2c_adapter *i2c_adap, u8 i2c_addr, स्थिर काष्ठा dib9000_config *cfg);
बाह्य पूर्णांक dib9000_i2c_क्रमागतeration(काष्ठा i2c_adapter *host, पूर्णांक no_of_demods, u8 शेष_addr, u8 first_addr);
बाह्य काष्ठा i2c_adapter *dib9000_get_tuner_पूर्णांकerface(काष्ठा dvb_frontend *fe);
बाह्य काष्ठा i2c_adapter *dib9000_get_i2c_master(काष्ठा dvb_frontend *fe, क्रमागत dibx000_i2c_पूर्णांकerface पूर्णांकf, पूर्णांक gating);
बाह्य पूर्णांक dib9000_set_gpio(काष्ठा dvb_frontend *fe, u8 num, u8 dir, u8 val);
बाह्य पूर्णांक dib9000_fw_pid_filter_ctrl(काष्ठा dvb_frontend *fe, u8 onoff);
बाह्य पूर्णांक dib9000_fw_pid_filter(काष्ठा dvb_frontend *fe, u8 id, u16 pid, u8 onoff);
बाह्य पूर्णांक dib9000_firmware_post_pll_init(काष्ठा dvb_frontend *fe);
बाह्य पूर्णांक dib9000_set_slave_frontend(काष्ठा dvb_frontend *fe, काष्ठा dvb_frontend *fe_slave);
बाह्य काष्ठा dvb_frontend *dib9000_get_slave_frontend(काष्ठा dvb_frontend *fe, पूर्णांक slave_index);
बाह्य काष्ठा i2c_adapter *dib9000_get_component_bus_पूर्णांकerface(काष्ठा dvb_frontend *fe);
बाह्य पूर्णांक dib9000_set_i2c_adapter(काष्ठा dvb_frontend *fe, काष्ठा i2c_adapter *i2c);
बाह्य पूर्णांक dib9000_fw_set_component_bus_speed(काष्ठा dvb_frontend *fe, u16 speed);
#अन्यथा
अटल अंतरभूत काष्ठा dvb_frontend *dib9000_attach(काष्ठा i2c_adapter *i2c_adap, u8 i2c_addr, काष्ठा dib9000_config *cfg)
अणु
	prपूर्णांकk(KERN_WARNING "%s: driver disabled by Kconfig\n", __func__);
	वापस शून्य;
पूर्ण

अटल अंतरभूत काष्ठा i2c_adapter *dib9000_get_i2c_master(काष्ठा dvb_frontend *fe, क्रमागत dibx000_i2c_पूर्णांकerface पूर्णांकf, पूर्णांक gating)
अणु
	prपूर्णांकk(KERN_WARNING "%s: driver disabled by Kconfig\n", __func__);
	वापस शून्य;
पूर्ण

अटल अंतरभूत पूर्णांक dib9000_i2c_क्रमागतeration(काष्ठा i2c_adapter *host, पूर्णांक no_of_demods, u8 शेष_addr, u8 first_addr)
अणु
	prपूर्णांकk(KERN_WARNING "%s: driver disabled by Kconfig\n", __func__);
	वापस -ENODEV;
पूर्ण

अटल अंतरभूत काष्ठा i2c_adapter *dib9000_get_tuner_पूर्णांकerface(काष्ठा dvb_frontend *fe)
अणु
	prपूर्णांकk(KERN_WARNING "%s: driver disabled by Kconfig\n", __func__);
	वापस शून्य;
पूर्ण

अटल अंतरभूत पूर्णांक dib9000_set_gpio(काष्ठा dvb_frontend *fe, u8 num, u8 dir, u8 val)
अणु
	prपूर्णांकk(KERN_WARNING "%s: driver disabled by Kconfig\n", __func__);
	वापस -ENODEV;
पूर्ण

अटल अंतरभूत पूर्णांक dib9000_fw_pid_filter_ctrl(काष्ठा dvb_frontend *fe, u8 onoff)
अणु
	prपूर्णांकk(KERN_WARNING "%s: driver disabled by Kconfig\n", __func__);
	वापस -ENODEV;
पूर्ण

अटल अंतरभूत पूर्णांक dib9000_fw_pid_filter(काष्ठा dvb_frontend *fe, u8 id, u16 pid, u8 onoff)
अणु
	prपूर्णांकk(KERN_WARNING "%s: driver disabled by Kconfig\n", __func__);
	वापस -ENODEV;
पूर्ण

अटल अंतरभूत पूर्णांक dib9000_firmware_post_pll_init(काष्ठा dvb_frontend *fe)
अणु
	prपूर्णांकk(KERN_WARNING "%s: driver disabled by Kconfig\n", __func__);
	वापस -ENODEV;
पूर्ण

अटल अंतरभूत पूर्णांक dib9000_set_slave_frontend(काष्ठा dvb_frontend *fe, काष्ठा dvb_frontend *fe_slave)
अणु
	prपूर्णांकk(KERN_WARNING "%s: driver disabled by Kconfig\n", __func__);
	वापस -ENODEV;
पूर्ण

अटल अंतरभूत काष्ठा dvb_frontend *dib9000_get_slave_frontend(काष्ठा dvb_frontend *fe, पूर्णांक slave_index)
अणु
	prपूर्णांकk(KERN_WARNING "%s: driver disabled by Kconfig\n", __func__);
	वापस शून्य;
पूर्ण

अटल अंतरभूत काष्ठा i2c_adapter *dib9000_get_component_bus_पूर्णांकerface(काष्ठा dvb_frontend *fe)
अणु
	prपूर्णांकk(KERN_WARNING "%s: driver disabled by Kconfig\n", __func__);
	वापस शून्य;
पूर्ण

अटल अंतरभूत पूर्णांक dib9000_set_i2c_adapter(काष्ठा dvb_frontend *fe, काष्ठा i2c_adapter *i2c)
अणु
	prपूर्णांकk(KERN_WARNING "%s: driver disabled by Kconfig\n", __func__);
	वापस -ENODEV;
पूर्ण

अटल अंतरभूत पूर्णांक dib9000_fw_set_component_bus_speed(काष्ठा dvb_frontend *fe, u16 speed)
अणु
	prपूर्णांकk(KERN_WARNING "%s: driver disabled by Kconfig\n", __func__);
	वापस -ENODEV;
पूर्ण
#पूर्ण_अगर

#पूर्ण_अगर
