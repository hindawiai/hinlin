<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/******************************************************************************
 *
 * Copyright(c) 2007 - 2011 Realtek Corporation. All rights reserved.
 *
 ******************************************************************************/

#समावेश "pwrseq.h"
#समावेश <rtl8188e_hal.h>

/* drivers should parse below arrays and करो the corresponding actions */

/* 3 Power on  Array */
काष्ठा wl_pwr_cfg rtl8188E_घातer_on_flow[RTL8188E_TRANS_CARDEMU_TO_ACT_STEPS +
					 RTL8188E_TRANS_END_STEPS] = अणु
	RTL8188E_TRANS_CARDEMU_TO_ACT
	RTL8188E_TRANS_END
पूर्ण;

/* 3Radio off Array */
काष्ठा wl_pwr_cfg rtl8188E_radio_off_flow[RTL8188E_TRANS_ACT_TO_CARDEMU_STEPS +
					  RTL8188E_TRANS_END_STEPS] = अणु
	RTL8188E_TRANS_ACT_TO_CARDEMU
	RTL8188E_TRANS_END
पूर्ण;

/* 3Card Disable Array */
काष्ठा wl_pwr_cfg rtl8188E_card_disable_flow
	[RTL8188E_TRANS_ACT_TO_CARDEMU_STEPS +
	 RTL8188E_TRANS_CARDEMU_TO_PDN_STEPS +
	 RTL8188E_TRANS_END_STEPS] = अणु
		RTL8188E_TRANS_ACT_TO_CARDEMU
		RTL8188E_TRANS_CARDEMU_TO_CARDDIS
		RTL8188E_TRANS_END
पूर्ण;

/* 3 Card Enable Array */
काष्ठा wl_pwr_cfg rtl8188E_card_enable_flow
	[RTL8188E_TRANS_ACT_TO_CARDEMU_STEPS +
	 RTL8188E_TRANS_CARDEMU_TO_PDN_STEPS +
	 RTL8188E_TRANS_END_STEPS] = अणु
		RTL8188E_TRANS_CARDDIS_TO_CARDEMU
		RTL8188E_TRANS_CARDEMU_TO_ACT
		RTL8188E_TRANS_END
पूर्ण;

/* 3Suspend Array */
काष्ठा wl_pwr_cfg rtl8188E_suspend_flow[RTL8188E_TRANS_ACT_TO_CARDEMU_STEPS +
					RTL8188E_TRANS_CARDEMU_TO_SUS_STEPS +
					RTL8188E_TRANS_END_STEPS] = अणु
	RTL8188E_TRANS_ACT_TO_CARDEMU
	RTL8188E_TRANS_CARDEMU_TO_SUS
	RTL8188E_TRANS_END
पूर्ण;

/* 3 Resume Array */
काष्ठा wl_pwr_cfg rtl8188E_resume_flow[RTL8188E_TRANS_ACT_TO_CARDEMU_STEPS +
				       RTL8188E_TRANS_CARDEMU_TO_SUS_STEPS +
				       RTL8188E_TRANS_END_STEPS] = अणु
	RTL8188E_TRANS_SUS_TO_CARDEMU
	RTL8188E_TRANS_CARDEMU_TO_ACT
	RTL8188E_TRANS_END
पूर्ण;

/* 3HWPDN Array */
काष्ठा wl_pwr_cfg rtl8188E_hwpdn_flow[RTL8188E_TRANS_ACT_TO_CARDEMU_STEPS +
				      RTL8188E_TRANS_CARDEMU_TO_PDN_STEPS +
				      RTL8188E_TRANS_END_STEPS] = अणु
	RTL8188E_TRANS_ACT_TO_CARDEMU
	RTL8188E_TRANS_CARDEMU_TO_PDN
	RTL8188E_TRANS_END
पूर्ण;

/* 3 Enter LPS */
काष्ठा wl_pwr_cfg rtl8188E_enter_lps_flow[RTL8188E_TRANS_ACT_TO_LPS_STEPS +
					  RTL8188E_TRANS_END_STEPS] = अणु
	/* FW behavior */
	RTL8188E_TRANS_ACT_TO_LPS
	RTL8188E_TRANS_END
पूर्ण;

/* 3 Leave LPS */
काष्ठा wl_pwr_cfg rtl8188E_leave_lps_flow[RTL8188E_TRANS_LPS_TO_ACT_STEPS +
					  RTL8188E_TRANS_END_STEPS] = अणु
	/* FW behavior */
	RTL8188E_TRANS_LPS_TO_ACT
	RTL8188E_TRANS_END
पूर्ण;
