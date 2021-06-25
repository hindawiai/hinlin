<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
    Auvitek AU8522 QAM/8VSB demodulator driver

    Copyright (C) 2008 Steven Toth <stoth@linuxtv.org>


*/

#अगर_अघोषित __AU8522_H__
#घोषणा __AU8522_H__

#समावेश <linux/dvb/frontend.h>

क्रमागत au8522_अगर_freq अणु
	AU8522_IF_6MHZ = 0,
	AU8522_IF_4MHZ,
	AU8522_IF_3_25MHZ,
पूर्ण;

काष्ठा au8522_led_config अणु
	u16 vsb8_strong;
	u16 qam64_strong;
	u16 qam256_strong;

	u16 gpio_output;
	/* unset hi bits, set low bits */
	u16 gpio_output_enable;
	u16 gpio_output_disable;

	u16 gpio_leds;
	u8 *led_states;
	अचिन्हित पूर्णांक num_led_states;
पूर्ण;

काष्ठा au8522_config अणु
	/* the demodulator's i2c address */
	u8 demod_address;

	/* Return lock status based on tuner lock, or demod lock */
#घोषणा AU8522_TUNERLOCKING 0
#घोषणा AU8522_DEMODLOCKING 1
	u8 status_mode;

	काष्ठा au8522_led_config *led_cfg;

	क्रमागत au8522_अगर_freq vsb_अगर;
	क्रमागत au8522_अगर_freq qam_अगर;
पूर्ण;

#अगर IS_REACHABLE(CONFIG_DVB_AU8522_DTV)
बाह्य काष्ठा dvb_frontend *au8522_attach(स्थिर काष्ठा au8522_config *config,
					  काष्ठा i2c_adapter *i2c);
#अन्यथा
अटल अंतरभूत
काष्ठा dvb_frontend *au8522_attach(स्थिर काष्ठा au8522_config *config,
				   काष्ठा i2c_adapter *i2c)
अणु
	prपूर्णांकk(KERN_WARNING "%s: driver disabled by Kconfig\n", __func__);
	वापस शून्य;
पूर्ण
#पूर्ण_अगर /* CONFIG_DVB_AU8522 */

/* Other modes may need to be added later */
क्रमागत au8522_video_input अणु
	AU8522_COMPOSITE_CH1 = 1,
	AU8522_COMPOSITE_CH2,
	AU8522_COMPOSITE_CH3,
	AU8522_COMPOSITE_CH4,
	AU8522_COMPOSITE_CH4_SIF,
	AU8522_SVIDEO_CH13,
	AU8522_SVIDEO_CH24,
पूर्ण;

क्रमागत au8522_audio_input अणु
	AU8522_AUDIO_NONE,
	AU8522_AUDIO_SIF,
पूर्ण;
#पूर्ण_अगर /* __AU8522_H__ */
