<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * lnbp21.h - driver क्रम lnb supply and control ic lnbp21
 *
 * Copyright (C) 2006 Oliver Endriss
 *
 * the project's page is at https://linuxtv.org
 */

#अगर_अघोषित _LNBP21_H
#घोषणा _LNBP21_H

/* प्रणाली रेजिस्टर bits */
/* [RO] 0=OK; 1=over current limit flag */
#घोषणा LNBP21_OLF	0x01
/* [RO] 0=OK; 1=over temperature flag (150 C) */
#घोषणा LNBP21_OTF	0x02
/* [RW] 0=disable LNB घातer, enable loopthrough
	1=enable LNB घातer, disable loopthrough */
#घोषणा LNBP21_EN	0x04
/* [RW] 0=low voltage (13/14V, vert pol)
	1=high voltage (18/19V,horiz pol) */
#घोषणा LNBP21_VSEL	0x08
/* [RW] increase LNB voltage by 1V:
	0=13/18V; 1=14/19V */
#घोषणा LNBP21_LLC	0x10
/* [RW] 0=tone controlled by DSQIN pin
	1=tone enable, disable DSQIN */
#घोषणा LNBP21_TEN	0x20
/* [RW] current limit select:
	0:Iout=500-650mA Isc=300mA
	1:Iout=400-550mA Isc=200mA */
#घोषणा LNBP21_ISEL	0x40
/* [RW] लघु-circuit protect:
	0=pulsed (dynamic) curr limiting
	1=अटल curr limiting */
#घोषणा LNBP21_PCL	0x80

#समावेश <linux/dvb/frontend.h>

#अगर IS_REACHABLE(CONFIG_DVB_LNBP21)
/* override_set and override_clear control which
 प्रणाली रेजिस्टर bits (above) to always set & clear */
बाह्य काष्ठा dvb_frontend *lnbp21_attach(काष्ठा dvb_frontend *fe,
				काष्ठा i2c_adapter *i2c, u8 override_set,
				u8 override_clear);
#अन्यथा
अटल अंतरभूत काष्ठा dvb_frontend *lnbp21_attach(काष्ठा dvb_frontend *fe,
				काष्ठा i2c_adapter *i2c, u8 override_set,
				u8 override_clear)
अणु
	prपूर्णांकk(KERN_WARNING "%s: driver disabled by Kconfig\n", __func__);
	वापस शून्य;
पूर्ण
#पूर्ण_अगर

#पूर्ण_अगर
