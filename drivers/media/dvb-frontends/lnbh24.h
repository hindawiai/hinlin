<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * lnbh24.h - driver क्रम lnb supply and control ic lnbh24
 *
 * Copyright (C) 2009 NetUP Inc.
 * Copyright (C) 2009 Igor M. Liplianin <liplianin@netup.ru>
 */

#अगर_अघोषित _LNBH24_H
#घोषणा _LNBH24_H

/* प्रणाली रेजिस्टर bits */
#घोषणा LNBH24_OLF	0x01
#घोषणा LNBH24_OTF	0x02
#घोषणा LNBH24_EN	0x04
#घोषणा LNBH24_VSEL	0x08
#घोषणा LNBH24_LLC	0x10
#घोषणा LNBH24_TEN	0x20
#घोषणा LNBH24_TTX	0x40
#घोषणा LNBH24_PCL	0x80

#समावेश <linux/dvb/frontend.h>

#अगर IS_REACHABLE(CONFIG_DVB_LNBP21)
/* override_set and override_clear control which
   प्रणाली रेजिस्टर bits (above) to always set & clear */
बाह्य काष्ठा dvb_frontend *lnbh24_attach(काष्ठा dvb_frontend *fe,
				काष्ठा i2c_adapter *i2c, u8 override_set,
				u8 override_clear, u8 i2c_addr);
#अन्यथा
अटल अंतरभूत काष्ठा dvb_frontend *lnbh24_attach(काष्ठा dvb_frontend *fe,
				काष्ठा i2c_adapter *i2c, u8 override_set,
				u8 override_clear, u8 i2c_addr)
अणु
	prपूर्णांकk(KERN_WARNING "%s: driver disabled by Kconfig\n", __func__);
	वापस शून्य;
पूर्ण
#पूर्ण_अगर

#पूर्ण_अगर
