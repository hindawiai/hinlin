<शैली गुरु>
/* SPDX-License-Identअगरier: (GPL-2.0 OR MIT) */
/* Microsemi Ocelot Switch driver
 *
 * Copyright (c) 2019 Microsemi Corporation
 */

#अगर_अघोषित _MSCC_OCELOT_POLICE_H_
#घोषणा _MSCC_OCELOT_POLICE_H_

#समावेश "ocelot.h"

क्रमागत mscc_qos_rate_mode अणु
	MSCC_QOS_RATE_MODE_DISABLED, /* Policer/shaper disabled */
	MSCC_QOS_RATE_MODE_LINE, /* Measure line rate in kbps incl. IPG */
	MSCC_QOS_RATE_MODE_DATA, /* Measures data rate in kbps excl. IPG */
	MSCC_QOS_RATE_MODE_FRAME, /* Measures frame rate in fps */
	__MSCC_QOS_RATE_MODE_END,
	NUM_MSCC_QOS_RATE_MODE = __MSCC_QOS_RATE_MODE_END,
	MSCC_QOS_RATE_MODE_MAX = __MSCC_QOS_RATE_MODE_END - 1,
पूर्ण;

काष्ठा qos_policer_conf अणु
	क्रमागत mscc_qos_rate_mode mode;
	bool dlb; /* Enable DLB (dual leaky bucket mode */
	bool cf;  /* Coupling flag (ignored in SLB mode) */
	u32  cir; /* CIR in kbps/fps (ignored in SLB mode) */
	u32  cbs; /* CBS in bytes/frames (ignored in SLB mode) */
	u32  pir; /* PIR in kbps/fps */
	u32  pbs; /* PBS in bytes/frames */
	u8   ipg; /* Size of IPG when MSCC_QOS_RATE_MODE_LINE is chosen */
पूर्ण;

पूर्णांक qos_policer_conf_set(काष्ठा ocelot *ocelot, पूर्णांक port, u32 pol_ix,
			 काष्ठा qos_policer_conf *conf);

#पूर्ण_अगर /* _MSCC_OCELOT_POLICE_H_ */
