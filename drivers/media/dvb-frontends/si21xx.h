<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित SI21XX_H
#घोषणा SI21XX_H

#समावेश <linux/dvb/frontend.h>
#समावेश <media/dvb_frontend.h>

काष्ठा si21xx_config अणु
	/* the demodulator's i2c address */
	u8 demod_address;

	/* minimum delay beक्रमe retuning */
	पूर्णांक min_delay_ms;
पूर्ण;

#अगर IS_REACHABLE(CONFIG_DVB_SI21XX)
बाह्य काष्ठा dvb_frontend *si21xx_attach(स्थिर काष्ठा si21xx_config *config,
						काष्ठा i2c_adapter *i2c);
#अन्यथा
अटल अंतरभूत काष्ठा dvb_frontend *si21xx_attach(
		स्थिर काष्ठा si21xx_config *config, काष्ठा i2c_adapter *i2c)
अणु
	prपूर्णांकk(KERN_WARNING "%s: driver disabled by Kconfig\n", __func__);
	वापस शून्य;
पूर्ण
#पूर्ण_अगर

अटल अंतरभूत पूर्णांक si21xx_ग_लिखोरेजिस्टर(काष्ठा dvb_frontend *fe, u8 reg, u8 val)
अणु
	पूर्णांक r = 0;
	u8 buf[] = अणुreg, valपूर्ण;
	अगर (fe->ops.ग_लिखो)
		r = fe->ops.ग_लिखो(fe, buf, 2);
	वापस r;
पूर्ण

#पूर्ण_अगर
