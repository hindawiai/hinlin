<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * isl6421.h - driver क्रम lnb supply and control ic ISL6421
 *
 * Copyright (C) 2006 Andrew de Quincey
 * Copyright (C) 2006 Oliver Endriss
 *
 * the project's page is at https://linuxtv.org
 */

#अगर_अघोषित _ISL6421_H
#घोषणा _ISL6421_H

#समावेश <linux/dvb/frontend.h>

/* प्रणाली रेजिस्टर bits */
#घोषणा ISL6421_OLF1	0x01
#घोषणा ISL6421_EN1	0x02
#घोषणा ISL6421_VSEL1	0x04
#घोषणा ISL6421_LLC1	0x08
#घोषणा ISL6421_ENT1	0x10
#घोषणा ISL6421_ISEL1	0x20
#घोषणा ISL6421_DCL	0x40

#अगर IS_REACHABLE(CONFIG_DVB_ISL6421)
/* override_set and override_clear control which प्रणाली रेजिस्टर bits (above) to always set & clear */
बाह्य काष्ठा dvb_frontend *isl6421_attach(काष्ठा dvb_frontend *fe, काष्ठा i2c_adapter *i2c, u8 i2c_addr,
			  u8 override_set, u8 override_clear, bool override_tone);
#अन्यथा
अटल अंतरभूत काष्ठा dvb_frontend *isl6421_attach(काष्ठा dvb_frontend *fe, काष्ठा i2c_adapter *i2c, u8 i2c_addr,
						  u8 override_set, u8 override_clear, bool override_tone)
अणु
	prपूर्णांकk(KERN_WARNING "%s: driver disabled by Kconfig\n", __func__);
	वापस शून्य;
पूर्ण
#पूर्ण_अगर // CONFIG_DVB_ISL6421

#पूर्ण_अगर
