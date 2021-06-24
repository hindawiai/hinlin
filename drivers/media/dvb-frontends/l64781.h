<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
    driver क्रम LSI L64781 COFDM demodulator

    Copyright (C) 2001 Holger Waechtler क्रम Convergence Integrated Media GmbH
		       Marko Kohtala <marko.kohtala@luukku.com>


*/

#अगर_अघोषित L64781_H
#घोषणा L64781_H

#समावेश <linux/dvb/frontend.h>

काष्ठा l64781_config
अणु
	/* the demodulator's i2c address */
	u8 demod_address;
पूर्ण;

#अगर IS_REACHABLE(CONFIG_DVB_L64781)
बाह्य काष्ठा dvb_frontend* l64781_attach(स्थिर काष्ठा l64781_config* config,
					  काष्ठा i2c_adapter* i2c);
#अन्यथा
अटल अंतरभूत काष्ठा dvb_frontend* l64781_attach(स्थिर काष्ठा l64781_config* config,
					  काष्ठा i2c_adapter* i2c)
अणु
	prपूर्णांकk(KERN_WARNING "%s: driver disabled by Kconfig\n", __func__);
	वापस शून्य;
पूर्ण
#पूर्ण_अगर // CONFIG_DVB_L64781

#पूर्ण_अगर // L64781_H
