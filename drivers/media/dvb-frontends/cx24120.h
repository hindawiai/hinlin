<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * Conexant CX24120/CX24118 - DVB-S/S2 demod/tuner driver
 *
 * Copyright (C) 2008 Patrick Boettcher <pb@linuxtv.org>
 * Copyright (C) 2009 Sergey Tyurin <क्रमum.मुक्त-x.de>
 * Updated 2012 by Jannis Achstetter <jannis_achstetter@web.de>
 * Copyright (C) 2015 Jemma Denson <jdenson@gmail.com>
 */

#अगर_अघोषित CX24120_H
#घोषणा CX24120_H

#समावेश <linux/dvb/frontend.h>
#समावेश <linux/firmware.h>

काष्ठा cx24120_initial_mpeg_config अणु
	u8 x1;
	u8 x2;
	u8 x3;
पूर्ण;

काष्ठा cx24120_config अणु
	u8 i2c_addr;
	u32 xtal_khz;
	काष्ठा cx24120_initial_mpeg_config initial_mpeg_config;

	पूर्णांक (*request_firmware)(काष्ठा dvb_frontend *fe,
				स्थिर काष्ठा firmware **fw, अक्षर *name);

	/* max bytes I2C provider can ग_लिखो at once */
	u16 i2c_wr_max;
पूर्ण;

#अगर IS_REACHABLE(CONFIG_DVB_CX24120)
काष्ठा dvb_frontend *cx24120_attach(स्थिर काष्ठा cx24120_config *config,
				    काष्ठा i2c_adapter *i2c);
#अन्यथा
अटल अंतरभूत
काष्ठा dvb_frontend *cx24120_attach(स्थिर काष्ठा cx24120_config *config,
				    काष्ठा i2c_adapter *i2c)
अणु
	pr_warn("%s: driver disabled by Kconfig\n", __func__);
	वापस शून्य;
पूर्ण
#पूर्ण_अगर

#पूर्ण_अगर /* CX24120_H */
