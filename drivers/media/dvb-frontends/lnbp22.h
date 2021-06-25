<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * lnbp22.h - driver क्रम lnb supply and control ic lnbp22
 *
 * Copyright (C) 2006 Dominik Kuhlen
 * Based on lnbp21.h
 *
 * the project's page is at https://linuxtv.org
 */

#अगर_अघोषित _LNBP22_H
#घोषणा _LNBP22_H

/* Enable */
#घोषणा LNBP22_EN	  0x10
/* Voltage selection */
#घोषणा LNBP22_VSEL	0x02
/* Plus 1 Volt Bit */
#घोषणा LNBP22_LLC	0x01

#समावेश <linux/dvb/frontend.h>

#अगर IS_REACHABLE(CONFIG_DVB_LNBP22)
/*
 * override_set and override_clear control which प्रणाली रेजिस्टर bits (above)
 * to always set & clear
 */
बाह्य काष्ठा dvb_frontend *lnbp22_attach(काष्ठा dvb_frontend *fe,
						काष्ठा i2c_adapter *i2c);
#अन्यथा
अटल अंतरभूत काष्ठा dvb_frontend *lnbp22_attach(काष्ठा dvb_frontend *fe,
						काष्ठा i2c_adapter *i2c)
अणु
	prपूर्णांकk(KERN_WARNING "%s: driver disabled by Kconfig\n", __func__);
	वापस शून्य;
पूर्ण
#पूर्ण_अगर /* CONFIG_DVB_LNBP22 */

#पूर्ण_अगर /* _LNBP22_H */
