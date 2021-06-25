<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Sharp QM1D1B0004 satellite tuner
 *
 * Copyright (C) 2014 Akihiro Tsukada <tskd08@gmail.com>
 */

#अगर_अघोषित QM1D1B0004_H
#घोषणा QM1D1B0004_H

#समावेश <media/dvb_frontend.h>

काष्ठा qm1d1b0004_config अणु
	काष्ठा dvb_frontend *fe;

	u32 lpf_freq;   /* LPF frequency[kHz]. Default: symbol rate */
	bool half_step; /* use PLL frequency step of 500Hz instead of 1000Hz */
पूर्ण;

/* special values indicating to use the शेष in qm1d1b0004_config */
#घोषणा QM1D1B0004_CFG_PLL_DFLT 0
#घोषणा QM1D1B0004_CFG_LPF_DFLT 0

#पूर्ण_अगर
