<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 *  Driver क्रम Microtune MT2060 "Single chip dual conversion broadband tuner"
 *
 *  Copyright (c) 2006 Olivier DANET <odanet@caramail.com>
 */

#अगर_अघोषित MT2060_H
#घोषणा MT2060_H

काष्ठा dvb_frontend;
काष्ठा i2c_adapter;

/*
 * I2C address
 * 0x60, ...
 */

/**
 * काष्ठा mt2060_platक्रमm_data - Platक्रमm data क्रम the mt2060 driver
 * @घड़ी_out: Clock output setting. 0 = off, 1 = CLK/4, 2 = CLK/2, 3 = CLK/1.
 * @अगर1: First IF used [MHz]. 0 शेषs to 1220.
 * @i2c_ग_लिखो_max: Maximum number of bytes I2C adapter can ग_लिखो at once.
 *  0 शेषs to maximum.
 * @dvb_frontend: DVB frontend.
 */

काष्ठा mt2060_platक्रमm_data अणु
	u8 घड़ी_out;
	u16 अगर1;
	अचिन्हित पूर्णांक i2c_ग_लिखो_max:5;
	काष्ठा dvb_frontend *dvb_frontend;
पूर्ण;


/* configuration काष्ठा क्रम mt2060_attach() */
काष्ठा mt2060_config अणु
	u8 i2c_address;
	u8 घड़ी_out; /* 0 = off, 1 = CLK/4, 2 = CLK/2, 3 = CLK/1 */
पूर्ण;

#अगर IS_REACHABLE(CONFIG_MEDIA_TUNER_MT2060)
बाह्य काष्ठा dvb_frontend * mt2060_attach(काष्ठा dvb_frontend *fe, काष्ठा i2c_adapter *i2c, काष्ठा mt2060_config *cfg, u16 अगर1);
#अन्यथा
अटल अंतरभूत काष्ठा dvb_frontend * mt2060_attach(काष्ठा dvb_frontend *fe, काष्ठा i2c_adapter *i2c, काष्ठा mt2060_config *cfg, u16 अगर1)
अणु
	prपूर्णांकk(KERN_WARNING "%s: driver disabled by Kconfig\n", __func__);
	वापस शून्य;
पूर्ण
#पूर्ण_अगर // CONFIG_MEDIA_TUNER_MT2060

#पूर्ण_अगर
