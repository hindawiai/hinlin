<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Sharp QM1D1C0042 8PSK tuner driver
 *
 * Copyright (C) 2014 Akihiro Tsukada <tskd08@gmail.com>
 */

#अगर_अघोषित QM1D1C0042_H
#घोषणा QM1D1C0042_H

#समावेश <media/dvb_frontend.h>


काष्ठा qm1d1c0042_config अणु
	काष्ठा dvb_frontend *fe;

	u32  xtal_freq;    /* [kHz] */ /* currently ignored */
	bool lpf;          /* enable LPF */
	bool fast_srch;    /* enable fast search mode, no LPF */
	u32  lpf_रुको;         /* रुको in tuning with LPF enabled. [ms] */
	u32  fast_srch_रुको;   /* with fast-search mode, no LPF. [ms] */
	u32  normal_srch_रुको; /* with no LPF/fast-search mode. [ms] */
पूर्ण;
/* special values indicating to use the शेष in qm1d1c0042_config */
#घोषणा QM1D1C0042_CFG_XTAL_DFLT 0
#घोषणा QM1D1C0042_CFG_WAIT_DFLT 0

#पूर्ण_अगर /* QM1D1C0042_H */
