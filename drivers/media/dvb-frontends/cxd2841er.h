<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * cxd2841er.h
 *
 * Sony CXD2441ER digital demodulator driver खुला definitions
 *
 * Copyright 2012 Sony Corporation
 * Copyright (C) 2014 NetUP Inc.
 * Copyright (C) 2014 Sergey Kozlov <serjk@netup.ru>
 * Copyright (C) 2014 Abylay Ospan <aospan@netup.ru>
  */

#अगर_अघोषित CXD2841ER_H
#घोषणा CXD2841ER_H

#समावेश <linux/dvb/frontend.h>

#घोषणा CXD2841ER_USE_GATECTRL	1	/* bit 0 */
#घोषणा CXD2841ER_AUTO_IFHZ	2	/* bit 1 */
#घोषणा CXD2841ER_TS_SERIAL	4	/* bit 2 */
#घोषणा CXD2841ER_ASCOT		8	/* bit 3 */
#घोषणा CXD2841ER_EARLY_TUNE	16	/* bit 4 */
#घोषणा CXD2841ER_NO_WAIT_LOCK	32	/* bit 5 */
#घोषणा CXD2841ER_NO_AGCNEG	64	/* bit 6 */
#घोषणा CXD2841ER_TSBITS	128	/* bit 7 */

क्रमागत cxd2841er_xtal अणु
	SONY_XTAL_20500, /* 20.5 MHz */
	SONY_XTAL_24000, /* 24 MHz */
	SONY_XTAL_41000 /* 41 MHz */
पूर्ण;

काष्ठा cxd2841er_config अणु
	u8	i2c_addr;
	क्रमागत cxd2841er_xtal	xtal;
	u32	flags;
पूर्ण;

#अगर IS_REACHABLE(CONFIG_DVB_CXD2841ER)
बाह्य काष्ठा dvb_frontend *cxd2841er_attach_s(काष्ठा cxd2841er_config *cfg,
					       काष्ठा i2c_adapter *i2c);

बाह्य काष्ठा dvb_frontend *cxd2841er_attach_t_c(काष्ठा cxd2841er_config *cfg,
					       काष्ठा i2c_adapter *i2c);
#अन्यथा
अटल अंतरभूत काष्ठा dvb_frontend *cxd2841er_attach_s(
					काष्ठा cxd2841er_config *cfg,
					काष्ठा i2c_adapter *i2c)
अणु
	pr_warn("%s: driver disabled by Kconfig\n", __func__);
	वापस शून्य;
पूर्ण

अटल अंतरभूत काष्ठा dvb_frontend *cxd2841er_attach_t_c(
		काष्ठा cxd2841er_config *cfg, काष्ठा i2c_adapter *i2c)
अणु
	pr_warn("%s: driver disabled by Kconfig\n", __func__);
	वापस शून्य;
पूर्ण

#पूर्ण_अगर

#पूर्ण_अगर
