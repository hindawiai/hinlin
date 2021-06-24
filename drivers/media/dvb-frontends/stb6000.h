<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
  /*
     Driver क्रम ST stb6000 DVBS Silicon tuner

     Copyright (C) 2008 Igor M. Liplianin (liplianin@me.by)


  */

#अगर_अघोषित __DVB_STB6000_H__
#घोषणा __DVB_STB6000_H__

#समावेश <linux/i2c.h>
#समावेश <media/dvb_frontend.h>

#अगर IS_REACHABLE(CONFIG_DVB_STB6000)
/**
 * stb6000_attach - Attach a stb6000 tuner to the supplied frontend काष्ठाure.
 *
 * @fe: Frontend to attach to.
 * @addr: i2c address of the tuner.
 * @i2c: i2c adapter to use.
 *
 * वापस: FE poपूर्णांकer on success, शून्य on failure.
 */
बाह्य काष्ठा dvb_frontend *stb6000_attach(काष्ठा dvb_frontend *fe, पूर्णांक addr,
					   काष्ठा i2c_adapter *i2c);
#अन्यथा
अटल अंतरभूत काष्ठा dvb_frontend *stb6000_attach(काष्ठा dvb_frontend *fe,
						  पूर्णांक addr,
						  काष्ठा i2c_adapter *i2c)
अणु
	prपूर्णांकk(KERN_WARNING "%s: driver disabled by Kconfig\n", __func__);
	वापस शून्य;
पूर्ण
#पूर्ण_अगर /* CONFIG_DVB_STB6000 */

#पूर्ण_अगर /* __DVB_STB6000_H__ */
