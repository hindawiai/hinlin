<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Copyright (C) ST-Ericsson SA 2010
 *
 * Author: Bengt Jonsson <bengt.g.jonsson@stericsson.com> क्रम ST-Ericsson
 *
 * Interface to घातer करोमुख्य regulators on DB8500
 */

#अगर_अघोषित __REGULATOR_H__
#घोषणा __REGULATOR_H__

/* Number of DB8500 regulators and regulator क्रमागतeration */
क्रमागत db8500_regulator_id अणु
	DB8500_REGULATOR_VAPE,
	DB8500_REGULATOR_VARM,
	DB8500_REGULATOR_VMODEM,
	DB8500_REGULATOR_VPLL,
	DB8500_REGULATOR_VSMPS1,
	DB8500_REGULATOR_VSMPS2,
	DB8500_REGULATOR_VSMPS3,
	DB8500_REGULATOR_VRF1,
	DB8500_REGULATOR_SWITCH_SVAMMDSP,
	DB8500_REGULATOR_SWITCH_SVAMMDSPRET,
	DB8500_REGULATOR_SWITCH_SVAPIPE,
	DB8500_REGULATOR_SWITCH_SIAMMDSP,
	DB8500_REGULATOR_SWITCH_SIAMMDSPRET,
	DB8500_REGULATOR_SWITCH_SIAPIPE,
	DB8500_REGULATOR_SWITCH_SGA,
	DB8500_REGULATOR_SWITCH_B2R2_MCDE,
	DB8500_REGULATOR_SWITCH_ESRAM12,
	DB8500_REGULATOR_SWITCH_ESRAM12RET,
	DB8500_REGULATOR_SWITCH_ESRAM34,
	DB8500_REGULATOR_SWITCH_ESRAM34RET,
	DB8500_NUM_REGULATORS
पूर्ण;

/*
 * Exported पूर्णांकerface क्रम CPUIdle only. This function is called with all
 * पूर्णांकerrupts turned off.
 */
पूर्णांक घातer_state_active_is_enabled(व्योम);

#पूर्ण_अगर
