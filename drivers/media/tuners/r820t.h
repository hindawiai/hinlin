<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * Elonics R820T silicon tuner driver
 *
 * Copyright (C) 2012 Antti Palosaari <crope@iki.fi>
 */

#अगर_अघोषित R820T_H
#घोषणा R820T_H

#समावेश <media/dvb_frontend.h>

क्रमागत r820t_chip अणु
	CHIP_R820T,
	CHIP_R620D,
	CHIP_R828D,
	CHIP_R828,
	CHIP_R828S,
	CHIP_R820C,
पूर्ण;

काष्ठा r820t_config अणु
	u8 i2c_addr;		/* 0x34 */
	u32 xtal;
	क्रमागत r820t_chip rafael_chip;
	अचिन्हित max_i2c_msg_len;
	bool use_diplexer;
	bool use_predetect;
पूर्ण;

#अगर IS_REACHABLE(CONFIG_MEDIA_TUNER_R820T)
काष्ठा dvb_frontend *r820t_attach(काष्ठा dvb_frontend *fe,
				  काष्ठा i2c_adapter *i2c,
				  स्थिर काष्ठा r820t_config *cfg);
#अन्यथा
अटल अंतरभूत काष्ठा dvb_frontend *r820t_attach(काष्ठा dvb_frontend *fe,
						काष्ठा i2c_adapter *i2c,
						स्थिर काष्ठा r820t_config *cfg)
अणु
	pr_warn("%s: driver disabled by Kconfig\n", __func__);
	वापस शून्य;
पूर्ण
#पूर्ण_अगर

#पूर्ण_अगर
