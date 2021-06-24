<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 *  Driver क्रम Xceive XC4000 "QAM/8VSB single chip tuner"
 *
 *  Copyright (c) 2007 Steven Toth <stoth@linuxtv.org>
 */

#अगर_अघोषित __XC4000_H__
#घोषणा __XC4000_H__

#समावेश <linux/firmware.h>

काष्ठा dvb_frontend;
काष्ठा i2c_adapter;

काष्ठा xc4000_config अणु
	u8	i2c_address;
	/* अगर non-zero, घातer management is enabled by शेष */
	u8	शेष_pm;
	/* value to be written to XREG_AMPLITUDE in DVB-T mode (0: no ग_लिखो) */
	u8	dvb_amplitude;
	/* अगर non-zero, रेजिस्टर 0x0E is set to filter analog TV video output */
	u8	set_smoothedcvbs;
	/* IF क्रम DVB-T */
	u32	अगर_khz;
पूर्ण;

/* xc4000 callback command */
#घोषणा XC4000_TUNER_RESET		0

/* For each bridge framework, when it attaches either analog or digital,
 * it has to store a reference back to its _core equivalent काष्ठाure,
 * so that it can service the hardware by steering gpio's etc.
 * Each bridge implementation is dअगरferent so cast devptr accordingly.
 * The xc4000 driver cares not क्रम this value, other than ensuring
 * it's passed back to a bridge during tuner_callback().
 */

#अगर IS_REACHABLE(CONFIG_MEDIA_TUNER_XC4000)
बाह्य काष्ठा dvb_frontend *xc4000_attach(काष्ठा dvb_frontend *fe,
					  काष्ठा i2c_adapter *i2c,
					  काष्ठा xc4000_config *cfg);
#अन्यथा
अटल अंतरभूत काष्ठा dvb_frontend *xc4000_attach(काष्ठा dvb_frontend *fe,
						 काष्ठा i2c_adapter *i2c,
						 काष्ठा xc4000_config *cfg)
अणु
	prपूर्णांकk(KERN_WARNING "%s: driver disabled by Kconfig\n", __func__);
	वापस शून्य;
पूर्ण
#पूर्ण_अगर

#पूर्ण_अगर
