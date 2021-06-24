<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
    Driver क्रम Grundig 29504-491, a Philips TDA8083 based QPSK Frontend

    Copyright (C) 2001 Convergence Integrated Media GmbH

    written by Ralph Metzler <ralph@convergence.de>

    aकरोption to the new DVB frontend API and diagnostic ioctl's
    by Holger Waechtler <holger@convergence.de>


*/

#अगर_अघोषित TDA8083_H
#घोषणा TDA8083_H

#समावेश <linux/dvb/frontend.h>

काष्ठा tda8083_config
अणु
	/* the demodulator's i2c address */
	u8 demod_address;
पूर्ण;

#अगर IS_REACHABLE(CONFIG_DVB_TDA8083)
बाह्य काष्ठा dvb_frontend* tda8083_attach(स्थिर काष्ठा tda8083_config* config,
					   काष्ठा i2c_adapter* i2c);
#अन्यथा
अटल अंतरभूत काष्ठा dvb_frontend* tda8083_attach(स्थिर काष्ठा tda8083_config* config,
					   काष्ठा i2c_adapter* i2c)
अणु
	prपूर्णांकk(KERN_WARNING "%s: driver disabled by Kconfig\n", __func__);
	वापस शून्य;
पूर्ण
#पूर्ण_अगर // CONFIG_DVB_TDA8083

#पूर्ण_अगर // TDA8083_H
