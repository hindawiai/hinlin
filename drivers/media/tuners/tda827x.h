<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
  /*
     DVB Driver क्रम Philips tda827x / tda827xa Silicon tuners

     (c) 2005 Harपंचांगut Hackmann
     (c) 2007 Michael Krufky


  */

#अगर_अघोषित __DVB_TDA827X_H__
#घोषणा __DVB_TDA827X_H__

#समावेश <linux/i2c.h>
#समावेश <media/dvb_frontend.h>
#समावेश "tda8290.h"

काष्ठा tda827x_config
अणु
	/* saa7134 - provided callbacks */
	पूर्णांक (*init) (काष्ठा dvb_frontend *fe);
	पूर्णांक (*sleep) (काष्ठा dvb_frontend *fe);

	/* पूर्णांकerface to tda829x driver */
	क्रमागत tda8290_lna config;
	पूर्णांक	     चयन_addr;

	व्योम (*agcf)(काष्ठा dvb_frontend *fe);
पूर्ण;


/**
 * tda827x_attach() - Attach a tda827x tuner to the supplied frontend काष्ठाure
 *
 * @fe: Frontend to attach to.
 * @addr: i2c address of the tuner.
 * @i2c: i2c adapter to use.
 * @cfg: optional callback function poपूर्णांकers.
 * @वापस FE poपूर्णांकer on success, शून्य on failure.
 */
#अगर IS_REACHABLE(CONFIG_MEDIA_TUNER_TDA827X)
बाह्य काष्ठा dvb_frontend* tda827x_attach(काष्ठा dvb_frontend *fe, पूर्णांक addr,
					   काष्ठा i2c_adapter *i2c,
					   काष्ठा tda827x_config *cfg);
#अन्यथा
अटल अंतरभूत काष्ठा dvb_frontend* tda827x_attach(काष्ठा dvb_frontend *fe,
						  पूर्णांक addr,
						  काष्ठा i2c_adapter *i2c,
						  काष्ठा tda827x_config *cfg)
अणु
	prपूर्णांकk(KERN_WARNING "%s: driver disabled by Kconfig\n", __func__);
	वापस शून्य;
पूर्ण
#पूर्ण_अगर // CONFIG_MEDIA_TUNER_TDA827X

#पूर्ण_अगर // __DVB_TDA827X_H__
