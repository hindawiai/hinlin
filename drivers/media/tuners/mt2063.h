<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित __MT2063_H__
#घोषणा __MT2063_H__

#समावेश <media/dvb_frontend.h>

काष्ठा mt2063_config अणु
	u8 tuner_address;
	u32 refघड़ी;
पूर्ण;

#अगर IS_REACHABLE(CONFIG_MEDIA_TUNER_MT2063)
काष्ठा dvb_frontend *mt2063_attach(काष्ठा dvb_frontend *fe,
				   काष्ठा mt2063_config *config,
				   काष्ठा i2c_adapter *i2c);

#अन्यथा

अटल अंतरभूत काष्ठा dvb_frontend *mt2063_attach(काष्ठा dvb_frontend *fe,
				   काष्ठा mt2063_config *config,
				   काष्ठा i2c_adapter *i2c)
अणु
	prपूर्णांकk(KERN_WARNING "%s: Driver disabled by Kconfig\n", __func__);
	वापस शून्य;
पूर्ण

#पूर्ण_अगर /* CONFIG_DVB_MT2063 */

#पूर्ण_अगर /* __MT2063_H__ */
