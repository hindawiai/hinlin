<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * isl6405.h - driver क्रम dual lnb supply and control ic ISL6405
 *
 * Copyright (C) 2008 Harपंचांगut Hackmann
 * Copyright (C) 2006 Oliver Endriss
 *
 * the project's page is at https://linuxtv.org
 */

#अगर_अघोषित _ISL6405_H
#घोषणा _ISL6405_H

#समावेश <linux/dvb/frontend.h>

/* प्रणाली रेजिस्टर bits */

/* this bit selects रेजिस्टर (control) 1 or 2
   note that the bit maps are dअगरferent */

#घोषणा ISL6405_SR	0x80

/* SR = 0 */
#घोषणा ISL6405_OLF1	0x01
#घोषणा ISL6405_EN1	0x02
#घोषणा ISL6405_VSEL1	0x04
#घोषणा ISL6405_LLC1	0x08
#घोषणा ISL6405_ENT1	0x10
#घोषणा ISL6405_ISEL1	0x20
#घोषणा ISL6405_DCL	0x40

/* SR = 1 */
#घोषणा ISL6405_OLF2	0x01
#घोषणा ISL6405_OTF	0x02
#घोषणा ISL6405_EN2	0x04
#घोषणा ISL6405_VSEL2	0x08
#घोषणा ISL6405_LLC2	0x10
#घोषणा ISL6405_ENT2	0x20
#घोषणा ISL6405_ISEL2	0x40

#अगर IS_REACHABLE(CONFIG_DVB_ISL6405)
/* override_set and override_clear control which प्रणाली रेजिस्टर bits (above)
 * to always set & clear
 */
बाह्य काष्ठा dvb_frontend *isl6405_attach(काष्ठा dvb_frontend *fe, काष्ठा i2c_adapter *i2c,
					   u8 i2c_addr, u8 override_set, u8 override_clear);
#अन्यथा
अटल अंतरभूत काष्ठा dvb_frontend *isl6405_attach(काष्ठा dvb_frontend *fe,
						  काष्ठा i2c_adapter *i2c, u8 i2c_addr,
						  u8 override_set, u8 override_clear)
अणु
	prपूर्णांकk(KERN_WARNING "%s: driver disabled by Kconfig\n", __func__);
	वापस शून्य;
पूर्ण
#पूर्ण_अगर /* CONFIG_DVB_ISL6405 */

#पूर्ण_अगर
