<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * NXP TDA18250BHN silicon tuner driver
 *
 * Copyright (C) 2017 Olli Salonen <olli.salonen@iki.fi>
 */

#अगर_अघोषित TDA18250_H
#घोषणा TDA18250_H

#समावेश <linux/kconfig.h>
#समावेश <media/media-device.h>
#समावेश <media/dvb_frontend.h>

#घोषणा TDA18250_XTAL_FREQ_16MHZ 0
#घोषणा TDA18250_XTAL_FREQ_24MHZ 1
#घोषणा TDA18250_XTAL_FREQ_25MHZ 2
#घोषणा TDA18250_XTAL_FREQ_27MHZ 3
#घोषणा TDA18250_XTAL_FREQ_30MHZ 4
#घोषणा TDA18250_XTAL_FREQ_MAX 5

काष्ठा tda18250_config अणु
	u16 अगर_dvbt_6;
	u16 अगर_dvbt_7;
	u16 अगर_dvbt_8;
	u16 अगर_dvbc_6;
	u16 अगर_dvbc_8;
	u16 अगर_atsc;
	u8 xtal_freq;
	bool loopthrough;

	/*
	 * frontend
	 */
	काष्ठा dvb_frontend *fe;

#अगर defined(CONFIG_MEDIA_CONTROLLER)
	काष्ठा media_device *mdev;
#पूर्ण_अगर
पूर्ण;

#पूर्ण_अगर
