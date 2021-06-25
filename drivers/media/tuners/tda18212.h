<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * NXP TDA18212HN silicon tuner driver
 *
 * Copyright (C) 2011 Antti Palosaari <crope@iki.fi>
 */

#अगर_अघोषित TDA18212_H
#घोषणा TDA18212_H

#समावेश <media/dvb_frontend.h>

काष्ठा tda18212_config अणु
	u16 अगर_dvbt_6;
	u16 अगर_dvbt_7;
	u16 अगर_dvbt_8;
	u16 अगर_dvbt2_5;
	u16 अगर_dvbt2_6;
	u16 अगर_dvbt2_7;
	u16 अगर_dvbt2_8;
	u16 अगर_dvbc;
	u16 अगर_atsc_vsb;
	u16 अगर_atsc_qam;

	/*
	 * poपूर्णांकer to DVB frontend
	 */
	काष्ठा dvb_frontend *fe;
पूर्ण;

#पूर्ण_अगर
