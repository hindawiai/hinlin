<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Driver क्रम Sharp IX2505V (marked B0017) DVB-S silicon tuner
 *
 * Copyright (C) 2010 Malcolm Priestley
 */

#अगर_अघोषित DVB_IX2505V_H
#घोषणा DVB_IX2505V_H

#समावेश <linux/i2c.h>
#समावेश <media/dvb_frontend.h>

/**
 * काष्ठा ix2505v_config - ix2505 attachment configuration
 *
 * @tuner_address: tuner address
 * @tuner_gain: Baseband AMP gain control 0/1=0dB(शेष) 2=-2bB 3=-4dB
 * @tuner_अक्षरgepump: Charge pump output +/- 0=120 1=260 2=555 3=1200(शेष)
 * @min_delay_ms: delay after tune
 * @tuner_ग_लिखो_only: disables पढ़ोs
 */
काष्ठा ix2505v_config अणु
	u8 tuner_address;
	u8 tuner_gain;
	u8 tuner_अक्षरgepump;
	पूर्णांक min_delay_ms;
	u8 tuner_ग_लिखो_only;

पूर्ण;

#अगर IS_REACHABLE(CONFIG_DVB_IX2505V)
/**
 * ix2505v_attach - Attach a ix2505v tuner to the supplied frontend काष्ठाure.
 *
 * @fe: Frontend to attach to.
 * @config: poपूर्णांकer to &काष्ठा ix2505v_config
 * @i2c: poपूर्णांकer to &काष्ठा i2c_adapter.
 *
 * वापस: FE poपूर्णांकer on success, शून्य on failure.
 */
बाह्य काष्ठा dvb_frontend *ix2505v_attach(काष्ठा dvb_frontend *fe,
	स्थिर काष्ठा ix2505v_config *config, काष्ठा i2c_adapter *i2c);
#अन्यथा
अटल अंतरभूत काष्ठा dvb_frontend *ix2505v_attach(काष्ठा dvb_frontend *fe,
	स्थिर काष्ठा ix2505v_config *config, काष्ठा i2c_adapter *i2c)
अणु
	prपूर्णांकk(KERN_WARNING "%s: driver disabled by Kconfig\n", __func__);
	वापस शून्य;
पूर्ण
#पूर्ण_अगर

#पूर्ण_अगर /* DVB_IX2505V_H */
