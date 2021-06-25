<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 *  mxl111sf-tuner.h - driver क्रम the MaxLinear MXL111SF CMOS tuner
 *
 *  Copyright (C) 2010-2014 Michael Krufky <mkrufky@linuxtv.org>
 */

#अगर_अघोषित __MXL111SF_TUNER_H__
#घोषणा __MXL111SF_TUNER_H__

#समावेश <media/dvb_frontend.h>
#समावेश "mxl111sf.h"

क्रमागत mxl_अगर_freq अणु
#अगर 0
	MXL_IF_LO    = 0x00, /* other IF < 9MHz */
#पूर्ण_अगर
	MXL_IF_4_0   = 0x01, /* 4.0   MHz */
	MXL_IF_4_5   = 0x02, /* 4.5   MHz */
	MXL_IF_4_57  = 0x03, /* 4.57  MHz */
	MXL_IF_5_0   = 0x04, /* 5.0   MHz */
	MXL_IF_5_38  = 0x05, /* 5.38  MHz */
	MXL_IF_6_0   = 0x06, /* 6.0   MHz */
	MXL_IF_6_28  = 0x07, /* 6.28  MHz */
	MXL_IF_7_2   = 0x08, /* 7.2   MHz */
	MXL_IF_35_25 = 0x09, /* 35.25 MHz */
	MXL_IF_36    = 0x0a, /* 36    MHz */
	MXL_IF_36_15 = 0x0b, /* 36.15 MHz */
	MXL_IF_44    = 0x0c, /* 44    MHz */
#अगर 0
	MXL_IF_HI    = 0x0f, /* other IF > 35 MHz and < 45 MHz */
#पूर्ण_अगर
पूर्ण;

काष्ठा mxl111sf_tuner_config अणु
	क्रमागत mxl_अगर_freq अगर_freq;
	अचिन्हित पूर्णांक invert_spectrum:1;

	पूर्णांक (*पढ़ो_reg)(काष्ठा mxl111sf_state *state, u8 addr, u8 *data);
	पूर्णांक (*ग_लिखो_reg)(काष्ठा mxl111sf_state *state, u8 addr, u8 data);
	पूर्णांक (*program_regs)(काष्ठा mxl111sf_state *state,
			    काष्ठा mxl111sf_reg_ctrl_info *ctrl_reg_info);
	पूर्णांक (*top_master_ctrl)(काष्ठा mxl111sf_state *state, पूर्णांक onoff);
	पूर्णांक (*ant_hunt)(काष्ठा dvb_frontend *fe);
पूर्ण;

/* ------------------------------------------------------------------------ */

#अगर IS_ENABLED(CONFIG_DVB_USB_MXL111SF)
बाह्य
काष्ठा dvb_frontend *mxl111sf_tuner_attach(काष्ठा dvb_frontend *fe,
				काष्ठा mxl111sf_state *mxl_state,
				स्थिर काष्ठा mxl111sf_tuner_config *cfg);
#अन्यथा
अटल अंतरभूत
काष्ठा dvb_frontend *mxl111sf_tuner_attach(काष्ठा dvb_frontend *fe,
				काष्ठा mxl111sf_state *mxl_state,
				स्थिर काष्ठा mxl111sf_tuner_config *cfg)
अणु
	prपूर्णांकk(KERN_WARNING "%s: driver disabled by Kconfig\n", __func__);
	वापस शून्य;
पूर्ण
#पूर्ण_अगर

#पूर्ण_अगर /* __MXL111SF_TUNER_H__ */
