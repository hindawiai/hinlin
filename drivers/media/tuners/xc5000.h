<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 *  Driver क्रम Xceive XC5000 "QAM/8VSB single chip tuner"
 *
 *  Copyright (c) 2007 Steven Toth <stoth@linuxtv.org>
 */

#अगर_अघोषित __XC5000_H__
#घोषणा __XC5000_H__

#समावेश <linux/firmware.h>

काष्ठा dvb_frontend;
काष्ठा i2c_adapter;

#घोषणा XC5000A 1
#घोषणा XC5000C 2

काष्ठा xc5000_config अणु
	u8   i2c_address;
	u32  अगर_khz;
	u8   radio_input;
	u16  xtal_khz;
	u16  output_amp;

	पूर्णांक chip_id;
पूर्ण;

/* xc5000 callback command */
#घोषणा XC5000_TUNER_RESET		0

/* Possible Radio inमाला_दो */
#घोषणा XC5000_RADIO_NOT_CONFIGURED		0
#घोषणा XC5000_RADIO_FM1			1
#घोषणा XC5000_RADIO_FM2			2
#घोषणा XC5000_RADIO_FM1_MONO			3

/* For each bridge framework, when it attaches either analog or digital,
 * it has to store a reference back to its _core equivalent काष्ठाure,
 * so that it can service the hardware by steering gpio's etc.
 * Each bridge implementation is dअगरferent so cast devptr accordingly.
 * The xc5000 driver cares not क्रम this value, other than ensuring
 * it's passed back to a bridge during tuner_callback().
 */

#अगर IS_REACHABLE(CONFIG_MEDIA_TUNER_XC5000)
बाह्य काष्ठा dvb_frontend *xc5000_attach(काष्ठा dvb_frontend *fe,
					  काष्ठा i2c_adapter *i2c,
					  स्थिर काष्ठा xc5000_config *cfg);
#अन्यथा
अटल अंतरभूत काष्ठा dvb_frontend *xc5000_attach(काष्ठा dvb_frontend *fe,
						 काष्ठा i2c_adapter *i2c,
						 स्थिर काष्ठा xc5000_config *cfg)
अणु
	prपूर्णांकk(KERN_WARNING "%s: driver disabled by Kconfig\n", __func__);
	वापस शून्य;
पूर्ण
#पूर्ण_अगर

#पूर्ण_अगर
