<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 *  mxl111sf-demod.h - driver क्रम the MaxLinear MXL111SF DVB-T demodulator
 *
 *  Copyright (C) 2010-2014 Michael Krufky <mkrufky@linuxtv.org>
 */

#अगर_अघोषित __MXL111SF_DEMOD_H__
#घोषणा __MXL111SF_DEMOD_H__

#समावेश <media/dvb_frontend.h>
#समावेश "mxl111sf.h"

काष्ठा mxl111sf_demod_config अणु
	पूर्णांक (*पढ़ो_reg)(काष्ठा mxl111sf_state *state, u8 addr, u8 *data);
	पूर्णांक (*ग_लिखो_reg)(काष्ठा mxl111sf_state *state, u8 addr, u8 data);
	पूर्णांक (*program_regs)(काष्ठा mxl111sf_state *state,
			    काष्ठा mxl111sf_reg_ctrl_info *ctrl_reg_info);
पूर्ण;

#अगर IS_ENABLED(CONFIG_DVB_USB_MXL111SF)
बाह्य
काष्ठा dvb_frontend *mxl111sf_demod_attach(काष्ठा mxl111sf_state *mxl_state,
				   स्थिर काष्ठा mxl111sf_demod_config *cfg);
#अन्यथा
अटल अंतरभूत
काष्ठा dvb_frontend *mxl111sf_demod_attach(काष्ठा mxl111sf_state *mxl_state,
				   स्थिर काष्ठा mxl111sf_demod_config *cfg)
अणु
	prपूर्णांकk(KERN_WARNING "%s: driver disabled by Kconfig\n", __func__);
	वापस शून्य;
पूर्ण
#पूर्ण_अगर /* CONFIG_DVB_USB_MXL111SF */

#पूर्ण_अगर /* __MXL111SF_DEMOD_H__ */
