<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _TDA18271C2DD_H_
#घोषणा _TDA18271C2DD_H_

#अगर IS_REACHABLE(CONFIG_DVB_TDA18271C2DD)
काष्ठा dvb_frontend *tda18271c2dd_attach(काष्ठा dvb_frontend *fe,
					 काष्ठा i2c_adapter *i2c, u8 adr);
#अन्यथा
अटल अंतरभूत काष्ठा dvb_frontend *tda18271c2dd_attach(काष्ठा dvb_frontend *fe,
					 काष्ठा i2c_adapter *i2c, u8 adr)
अणु
	prपूर्णांकk(KERN_WARNING "%s: driver disabled by Kconfig\n", __func__);
	वापस शून्य;
पूर्ण
#पूर्ण_अगर

#पूर्ण_अगर
