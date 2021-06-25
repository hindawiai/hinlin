<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/* Copyright(c) 2009-2012  Realtek Corporation.*/

#समावेश "../pwrseqcmd.h"
#समावेश "pwrseq.h"

/* drivers should parse below arrays and करो the corresponding actions */
/*3 Power on  Array*/
काष्ठा wlan_pwr_cfg rtl8723A_घातer_on_flow
		[RTL8723A_TRANS_CARDEMU_TO_ACT_STEPS +
		 RTL8723A_TRANS_END_STEPS] = अणु
	RTL8723A_TRANS_CARDEMU_TO_ACT
	RTL8723A_TRANS_END
पूर्ण;

/*3Radio off GPIO Array */
काष्ठा wlan_pwr_cfg rtl8723A_radio_off_flow
		[RTL8723A_TRANS_ACT_TO_CARDEMU_STEPS +
		 RTL8723A_TRANS_END_STEPS] = अणु
	RTL8723A_TRANS_ACT_TO_CARDEMU
	RTL8723A_TRANS_END
पूर्ण;

/*3Card Disable Array*/
काष्ठा wlan_pwr_cfg rtl8723A_card_disable_flow
		[RTL8723A_TRANS_ACT_TO_CARDEMU_STEPS +
		 RTL8723A_TRANS_CARDEMU_TO_PDN_STEPS +
		 RTL8723A_TRANS_END_STEPS] = अणु
	RTL8723A_TRANS_ACT_TO_CARDEMU
	RTL8723A_TRANS_CARDEMU_TO_CARDDIS
	RTL8723A_TRANS_END
पूर्ण;

/*3 Card Enable Array*/
काष्ठा wlan_pwr_cfg rtl8723A_card_enable_flow
		[RTL8723A_TRANS_ACT_TO_CARDEMU_STEPS +
		 RTL8723A_TRANS_CARDEMU_TO_PDN_STEPS +
		 RTL8723A_TRANS_END_STEPS] = अणु
	RTL8723A_TRANS_CARDDIS_TO_CARDEMU
	RTL8723A_TRANS_CARDEMU_TO_ACT
	RTL8723A_TRANS_END
पूर्ण;

/*3Suspend Array*/
काष्ठा wlan_pwr_cfg rtl8723A_suspend_flow
		[RTL8723A_TRANS_ACT_TO_CARDEMU_STEPS +
		 RTL8723A_TRANS_CARDEMU_TO_SUS_STEPS +
		 RTL8723A_TRANS_END_STEPS] = अणु
	RTL8723A_TRANS_ACT_TO_CARDEMU
	RTL8723A_TRANS_CARDEMU_TO_SUS
	RTL8723A_TRANS_END
पूर्ण;

/*3 Resume Array*/
काष्ठा wlan_pwr_cfg rtl8723A_resume_flow
		[RTL8723A_TRANS_ACT_TO_CARDEMU_STEPS +
		 RTL8723A_TRANS_CARDEMU_TO_SUS_STEPS +
		 RTL8723A_TRANS_END_STEPS] = अणु
	RTL8723A_TRANS_SUS_TO_CARDEMU
	RTL8723A_TRANS_CARDEMU_TO_ACT
	RTL8723A_TRANS_END
पूर्ण;

/*3HWPDN Array*/
काष्ठा wlan_pwr_cfg rtl8723A_hwpdn_flow
		[RTL8723A_TRANS_ACT_TO_CARDEMU_STEPS +
		 RTL8723A_TRANS_CARDEMU_TO_PDN_STEPS +
		 RTL8723A_TRANS_END_STEPS] = अणु
	RTL8723A_TRANS_ACT_TO_CARDEMU
	RTL8723A_TRANS_CARDEMU_TO_PDN
	RTL8723A_TRANS_END
पूर्ण;

/*3 Enter LPS */
काष्ठा wlan_pwr_cfg rtl8723A_enter_lps_flow
		[RTL8723A_TRANS_ACT_TO_LPS_STEPS +
		 RTL8723A_TRANS_END_STEPS] = अणु
	/*FW behavior*/
	RTL8723A_TRANS_ACT_TO_LPS
	RTL8723A_TRANS_END
पूर्ण;

/*3 Leave LPS */
काष्ठा wlan_pwr_cfg rtl8723A_leave_lps_flow
		[RTL8723A_TRANS_LPS_TO_ACT_STEPS +
		 RTL8723A_TRANS_END_STEPS] = अणु
	/*FW behavior*/
	RTL8723A_TRANS_LPS_TO_ACT
	RTL8723A_TRANS_END
पूर्ण;
