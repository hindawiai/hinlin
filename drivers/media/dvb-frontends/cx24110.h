<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
    cx24110 - Single Chip Satellite Channel Receiver driver module

    Copyright (C) 2002 Peter Hettkamp <peter.hettkamp@htp-tel.de> based on
    work
    Copyright (C) 1999 Convergence Integrated Media GmbH <ralph@convergence.de>


*/

#अगर_अघोषित CX24110_H
#घोषणा CX24110_H

#समावेश <linux/dvb/frontend.h>

काष्ठा cx24110_config
अणु
	/* the demodulator's i2c address */
	u8 demod_address;
पूर्ण;

अटल अंतरभूत पूर्णांक cx24110_pll_ग_लिखो(काष्ठा dvb_frontend *fe, u32 val)
अणु
	u8 buf[] = अणु
		(u8)((val >> 24) & 0xff),
		(u8)((val >> 16) & 0xff),
		(u8)((val >> 8) & 0xff)
	पूर्ण;

	अगर (fe->ops.ग_लिखो)
		वापस fe->ops.ग_लिखो(fe, buf, 3);
	वापस 0;
पूर्ण

#अगर IS_REACHABLE(CONFIG_DVB_CX24110)
बाह्य काष्ठा dvb_frontend* cx24110_attach(स्थिर काष्ठा cx24110_config* config,
					   काष्ठा i2c_adapter* i2c);
#अन्यथा
अटल अंतरभूत काष्ठा dvb_frontend* cx24110_attach(स्थिर काष्ठा cx24110_config* config,
						  काष्ठा i2c_adapter* i2c)
अणु
	prपूर्णांकk(KERN_WARNING "%s: driver disabled by Kconfig\n", __func__);
	वापस शून्य;
पूर्ण
#पूर्ण_अगर // CONFIG_DVB_CX24110

#पूर्ण_अगर // CX24110_H
