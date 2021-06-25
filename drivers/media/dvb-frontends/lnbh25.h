<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * lnbh25.c
 *
 * Driver क्रम LNB supply and control IC LNBH25
 *
 * Copyright (C) 2014 NetUP Inc.
 * Copyright (C) 2014 Sergey Kozlov <serjk@netup.ru>
 * Copyright (C) 2014 Abylay Ospan <aospan@netup.ru>
 */

#अगर_अघोषित LNBH25_H
#घोषणा LNBH25_H

#समावेश <linux/i2c.h>
#समावेश <linux/dvb/frontend.h>

/* 22 kHz tone enabled. Tone output controlled by DSQIN pin */
#घोषणा	LNBH25_TEN	0x01
/* Low घातer mode activated (used only with 22 kHz tone output disabled) */
#घोषणा LNBH25_LPM	0x02
/* DSQIN input pin is set to receive बाह्यal 22 kHz TTL संकेत source */
#घोषणा LNBH25_EXTM	0x04

काष्ठा lnbh25_config अणु
	u8	i2c_address;
	u8	data2_config;
पूर्ण;

#अगर IS_REACHABLE(CONFIG_DVB_LNBH25)
काष्ठा dvb_frontend *lnbh25_attach(
	काष्ठा dvb_frontend *fe,
	काष्ठा lnbh25_config *cfg,
	काष्ठा i2c_adapter *i2c);
#अन्यथा
अटल अंतरभूत काष्ठा dvb_frontend *lnbh25_attach(
	काष्ठा dvb_frontend *fe,
	काष्ठा lnbh25_config *cfg,
	काष्ठा i2c_adapter *i2c)
अणु
	prपूर्णांकk(KERN_WARNING "%s: driver disabled by Kconfig\n", __func__);
	वापस शून्य;
पूर्ण
#पूर्ण_अगर

#पूर्ण_अगर
