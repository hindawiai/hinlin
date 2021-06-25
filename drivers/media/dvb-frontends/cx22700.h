<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
    Conexant CX22700 DVB OFDM demodulator driver

    Copyright (C) 2001-2002 Convergence Integrated Media GmbH
	Holger Waechtler <holger@convergence.de>


*/

#अगर_अघोषित CX22700_H
#घोषणा CX22700_H

#समावेश <linux/dvb/frontend.h>

काष्ठा cx22700_config
अणु
	/* the demodulator's i2c address */
	u8 demod_address;
पूर्ण;

#अगर IS_REACHABLE(CONFIG_DVB_CX22700)
बाह्य काष्ठा dvb_frontend* cx22700_attach(स्थिर काष्ठा cx22700_config* config,
					   काष्ठा i2c_adapter* i2c);
#अन्यथा
अटल अंतरभूत काष्ठा dvb_frontend* cx22700_attach(स्थिर काष्ठा cx22700_config* config,
					   काष्ठा i2c_adapter* i2c)
अणु
	prपूर्णांकk(KERN_WARNING "%s: driver disabled by Kconfig\n", __func__);
	वापस शून्य;
पूर्ण
#पूर्ण_अगर // CONFIG_DVB_CX22700

#पूर्ण_अगर // CX22700_H
