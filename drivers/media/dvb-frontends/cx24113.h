<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 *  Driver क्रम Conexant CX24113/CX24128 Tuner (Satellite)
 *
 *  Copyright (C) 2007-8 Patrick Boettcher <pb@linuxtv.org>
 */

#अगर_अघोषित CX24113_H
#घोषणा CX24113_H

काष्ठा dvb_frontend;

काष्ठा cx24113_config अणु
	u8 i2c_addr; /* 0x14 or 0x54 */

	u32 xtal_khz;
पूर्ण;

#अगर IS_REACHABLE(CONFIG_DVB_TUNER_CX24113)
बाह्य काष्ठा dvb_frontend *cx24113_attach(काष्ठा dvb_frontend *,
	स्थिर काष्ठा cx24113_config *config, काष्ठा i2c_adapter *i2c);

बाह्य व्योम cx24113_agc_callback(काष्ठा dvb_frontend *fe);
#अन्यथा
अटल अंतरभूत काष्ठा dvb_frontend *cx24113_attach(काष्ठा dvb_frontend *fe,
	स्थिर काष्ठा cx24113_config *config, काष्ठा i2c_adapter *i2c)
अणु
	prपूर्णांकk(KERN_WARNING "%s: driver disabled by Kconfig\n", __func__);
	वापस शून्य;
पूर्ण

अटल अंतरभूत व्योम cx24113_agc_callback(काष्ठा dvb_frontend *fe)
अणु
	prपूर्णांकk(KERN_WARNING "%s: driver disabled by Kconfig\n", __func__);
पूर्ण
#पूर्ण_अगर

#पूर्ण_अगर /* CX24113_H */
