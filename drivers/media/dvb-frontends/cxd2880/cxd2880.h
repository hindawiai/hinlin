<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * cxd2880.h
 * Sony CXD2880 DVB-T2/T tuner + demodulator driver खुला definitions
 *
 * Copyright (C) 2016, 2017, 2018 Sony Semiconductor Solutions Corporation
 */

#अगर_अघोषित CXD2880_H
#घोषणा CXD2880_H

काष्ठा cxd2880_config अणु
	काष्ठा spi_device *spi;
	काष्ठा mutex *spi_mutex; /* For SPI access exclusive control */
पूर्ण;

#अगर IS_REACHABLE(CONFIG_DVB_CXD2880)
बाह्य काष्ठा dvb_frontend *cxd2880_attach(काष्ठा dvb_frontend *fe,
					काष्ठा cxd2880_config *cfg);
#अन्यथा
अटल अंतरभूत काष्ठा dvb_frontend *cxd2880_attach(काष्ठा dvb_frontend *fe,
					काष्ठा cxd2880_config *cfg)
अणु
	pr_warn("%s: driver disabled by Kconfig\n", __func__);
	वापस शून्य;
पूर्ण
#पूर्ण_अगर /* CONFIG_DVB_CXD2880 */

#पूर्ण_अगर /* CXD2880_H */
