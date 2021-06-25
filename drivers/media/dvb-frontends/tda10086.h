<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
  /*
     Driver क्रम Philips tda10086 DVBS Frontend

     (c) 2006 Andrew de Quincey


   */

#अगर_अघोषित TDA10086_H
#घोषणा TDA10086_H

#समावेश <linux/dvb/frontend.h>
#समावेश <linux/firmware.h>

क्रमागत tda10086_xtal अणु
	TDA10086_XTAL_16M,
	TDA10086_XTAL_4M
पूर्ण;

काष्ठा tda10086_config
अणु
	/* the demodulator's i2c address */
	u8 demod_address;

	/* करोes the "inversion" need inverted? */
	u8 invert;

	/* करो we need the diseqc संकेत with carrier? */
	u8 diseqc_tone;

	/* frequency of the reference xtal */
	क्रमागत tda10086_xtal xtal_freq;
पूर्ण;

#अगर IS_REACHABLE(CONFIG_DVB_TDA10086)
बाह्य काष्ठा dvb_frontend* tda10086_attach(स्थिर काष्ठा tda10086_config* config,
					    काष्ठा i2c_adapter* i2c);
#अन्यथा
अटल अंतरभूत काष्ठा dvb_frontend* tda10086_attach(स्थिर काष्ठा tda10086_config* config,
						   काष्ठा i2c_adapter* i2c)
अणु
	prपूर्णांकk(KERN_WARNING "%s: driver disabled by Kconfig\n", __func__);
	वापस शून्य;
पूर्ण
#पूर्ण_अगर /* CONFIG_DVB_TDA10086 */

#पूर्ण_अगर /* TDA10086_H */
