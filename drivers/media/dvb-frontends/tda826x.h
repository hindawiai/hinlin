<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
  /*
     Driver क्रम Philips tda8262/tda8263 DVBS Silicon tuners

     (c) 2006 Andrew de Quincey


  */

#अगर_अघोषित __DVB_TDA826X_H__
#घोषणा __DVB_TDA826X_H__

#समावेश <linux/i2c.h>
#समावेश <media/dvb_frontend.h>

/**
 * tda826x_attach - Attach a tda826x tuner to the supplied frontend काष्ठाure.
 *
 * @fe: Frontend to attach to.
 * @addr: i2c address of the tuner.
 * @i2c: i2c adapter to use.
 * @has_loopthrough: Set to 1 अगर the card has a loopthrough RF connector.
 *
 * वापस: FE poपूर्णांकer on success, शून्य on failure.
 */
#अगर IS_REACHABLE(CONFIG_DVB_TDA826X)
बाह्य काष्ठा dvb_frontend* tda826x_attach(काष्ठा dvb_frontend *fe, पूर्णांक addr,
					   काष्ठा i2c_adapter *i2c,
					   पूर्णांक has_loopthrough);
#अन्यथा
अटल अंतरभूत काष्ठा dvb_frontend* tda826x_attach(काष्ठा dvb_frontend *fe,
						  पूर्णांक addr,
						  काष्ठा i2c_adapter *i2c,
						  पूर्णांक has_loopthrough)
अणु
	prपूर्णांकk(KERN_WARNING "%s: driver disabled by Kconfig\n", __func__);
	वापस शून्य;
पूर्ण
#पूर्ण_अगर // CONFIG_DVB_TDA826X

#पूर्ण_अगर // __DVB_TDA826X_H__
