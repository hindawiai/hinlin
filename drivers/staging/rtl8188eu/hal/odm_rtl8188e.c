<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/******************************************************************************
 *
 * Copyright(c) 2007 - 2011 Realtek Corporation. All rights reserved.
 *
 ******************************************************************************/

#समावेश "odm_precomp.h"
#समावेश "phy.h"

अटल व्योम dm_rx_hw_antena_भाग_init(काष्ठा odm_dm_काष्ठा *dm_odm)
अणु
	काष्ठा adapter *adapter = dm_odm->Adapter;
	u32 value32;

	अगर (*dm_odm->mp_mode == 1) अणु
		dm_odm->AntDivType = CGCS_RX_SW_ANTDIV;
		phy_set_bb_reg(adapter, ODM_REG_IGI_A_11N, BIT(7), 0);
		phy_set_bb_reg(adapter, ODM_REG_LNA_SWITCH_11N, BIT(31), 1);
		वापस;
	पूर्ण

	/* MAC Setting */
	value32 = phy_query_bb_reg(adapter, ODM_REG_ANTSEL_PIN_11N, bMaskDWord);
	phy_set_bb_reg(adapter, ODM_REG_ANTSEL_PIN_11N, bMaskDWord,
		       value32 | (BIT(23) | BIT(25)));
	/* Pin Settings */
	phy_set_bb_reg(adapter, ODM_REG_PIN_CTRL_11N, BIT(9) | BIT(8), 0);
	phy_set_bb_reg(adapter, ODM_REG_RX_ANT_CTRL_11N, BIT(10), 0);
	phy_set_bb_reg(adapter, ODM_REG_LNA_SWITCH_11N, BIT(22), 1);
	phy_set_bb_reg(adapter, ODM_REG_LNA_SWITCH_11N, BIT(31), 1);
	/* OFDM Settings */
	phy_set_bb_reg(adapter, ODM_REG_ANTDIV_PARA1_11N, bMaskDWord,
		       0x000000a0);
	/* CCK Settings */
	phy_set_bb_reg(adapter, ODM_REG_BB_PWR_SAV4_11N, BIT(7), 1);
	phy_set_bb_reg(adapter, ODM_REG_CCK_ANTDIV_PARA2_11N, BIT(4), 1);
	rtl88eu_dm_update_rx_idle_ant(dm_odm, MAIN_ANT);
	phy_set_bb_reg(adapter, ODM_REG_ANT_MAPPING1_11N, 0xFFFF, 0x0201);
पूर्ण

अटल व्योम dm_trx_hw_antenna_भाग_init(काष्ठा odm_dm_काष्ठा *dm_odm)
अणु
	काष्ठा adapter *adapter = dm_odm->Adapter;
	u32	value32;

	अगर (*dm_odm->mp_mode == 1) अणु
		dm_odm->AntDivType = CGCS_RX_SW_ANTDIV;
		phy_set_bb_reg(adapter, ODM_REG_IGI_A_11N, BIT(7), 0);
		phy_set_bb_reg(adapter, ODM_REG_RX_ANT_CTRL_11N,
			       BIT(5) | BIT(4) | BIT(3), 0);
		वापस;
	पूर्ण

	/* MAC Setting */
	value32 = phy_query_bb_reg(adapter, ODM_REG_ANTSEL_PIN_11N, bMaskDWord);
	phy_set_bb_reg(adapter, ODM_REG_ANTSEL_PIN_11N, bMaskDWord,
		       value32 | (BIT(23) | BIT(25)));
	/* Pin Settings */
	phy_set_bb_reg(adapter, ODM_REG_PIN_CTRL_11N, BIT(9) | BIT(8), 0);
	phy_set_bb_reg(adapter, ODM_REG_RX_ANT_CTRL_11N, BIT(10), 0);
	phy_set_bb_reg(adapter, ODM_REG_LNA_SWITCH_11N, BIT(22), 0);
	phy_set_bb_reg(adapter, ODM_REG_LNA_SWITCH_11N, BIT(31), 1);
	/* OFDM Settings */
	phy_set_bb_reg(adapter, ODM_REG_ANTDIV_PARA1_11N, bMaskDWord,
		       0x000000a0);
	/* CCK Settings */
	phy_set_bb_reg(adapter, ODM_REG_BB_PWR_SAV4_11N, BIT(7), 1);
	phy_set_bb_reg(adapter, ODM_REG_CCK_ANTDIV_PARA2_11N, BIT(4), 1);
	/* Tx Settings */
	phy_set_bb_reg(adapter, ODM_REG_TX_ANT_CTRL_11N, BIT(21), 0);
	rtl88eu_dm_update_rx_idle_ant(dm_odm, MAIN_ANT);

	/* antenna mapping table */
	अगर (!dm_odm->bIsMPChip) अणु /* testchip */
		phy_set_bb_reg(adapter, ODM_REG_RX_DEFAULT_A_11N,
			       BIT(10) | BIT(9) | BIT(8), 1);
		phy_set_bb_reg(adapter, ODM_REG_RX_DEFAULT_A_11N,
			       BIT(13) | BIT(12) | BIT(11), 2);
	पूर्ण अन्यथा अणु /* MPchip */
		phy_set_bb_reg(adapter, ODM_REG_ANT_MAPPING1_11N, bMaskDWord,
			       0x0201);
	पूर्ण
पूर्ण

अटल व्योम dm_fast_training_init(काष्ठा odm_dm_काष्ठा *dm_odm)
अणु
	काष्ठा adapter *adapter = dm_odm->Adapter;
	u32 value32, i;
	काष्ठा fast_ant_train *dm_fat_tbl = &dm_odm->DM_FatTable;

	अगर (*dm_odm->mp_mode == 1)
		वापस;

	क्रम (i = 0; i < 6; i++) अणु
		dm_fat_tbl->Bssid[i] = 0;
		dm_fat_tbl->antSumRSSI[i] = 0;
		dm_fat_tbl->antRSSIcnt[i] = 0;
		dm_fat_tbl->antAveRSSI[i] = 0;
	पूर्ण
	dm_fat_tbl->TrainIdx = 0;
	dm_fat_tbl->FAT_State = FAT_NORMAL_STATE;

	/* MAC Setting */
	value32 = phy_query_bb_reg(adapter, 0x4c, bMaskDWord);
	phy_set_bb_reg(adapter, 0x4c, bMaskDWord,
		       value32 | (BIT(23) | BIT(25)));
	value32 = phy_query_bb_reg(adapter,  0x7B4, bMaskDWord);
	phy_set_bb_reg(adapter, 0x7b4, bMaskDWord,
		       value32 | (BIT(16) | BIT(17)));

	/* Match MAC ADDR */
	phy_set_bb_reg(adapter, 0x7b4, 0xFFFF, 0);
	phy_set_bb_reg(adapter, 0x7b0, bMaskDWord, 0);

	phy_set_bb_reg(adapter, 0x870, BIT(9) | BIT(8), 0);
	phy_set_bb_reg(adapter, 0x864, BIT(10), 0);
	phy_set_bb_reg(adapter, 0xb2c, BIT(22), 0);
	phy_set_bb_reg(adapter, 0xb2c, BIT(31), 1);
	phy_set_bb_reg(adapter, 0xca4, bMaskDWord, 0x000000a0);

	/* antenna mapping table */
	अगर (!dm_odm->bIsMPChip) अणु /* testchip */
		phy_set_bb_reg(adapter, 0x858, BIT(10) | BIT(9) | BIT(8), 1);
		phy_set_bb_reg(adapter, 0x858, BIT(13) | BIT(12) | BIT(11), 2);
	पूर्ण अन्यथा अणु /* MPchip */
		phy_set_bb_reg(adapter, 0x914, bMaskByte0, 1);
		phy_set_bb_reg(adapter, 0x914, bMaskByte1, 2);
	पूर्ण

	/* Default Ant Setting when no fast training */
	phy_set_bb_reg(adapter, 0x80c, BIT(21), 1);
	phy_set_bb_reg(adapter, 0x864, BIT(5) | BIT(4) | BIT(3), 0);
	phy_set_bb_reg(adapter, 0x864, BIT(8) | BIT(7) | BIT(6), 1);

	/* Enter Traing state */
	phy_set_bb_reg(adapter, 0x864, BIT(2) | BIT(1) | BIT(0), 1);
	phy_set_bb_reg(adapter, 0xc50, BIT(7), 1);
पूर्ण

व्योम rtl88eu_dm_antenna_भाग_init(काष्ठा odm_dm_काष्ठा *dm_odm)
अणु
	अगर (dm_odm->AntDivType == CGCS_RX_HW_ANTDIV)
		dm_rx_hw_antena_भाग_init(dm_odm);
	अन्यथा अगर (dm_odm->AntDivType == CG_TRX_HW_ANTDIV)
		dm_trx_hw_antenna_भाग_init(dm_odm);
	अन्यथा अगर (dm_odm->AntDivType == CG_TRX_SMART_ANTDIV)
		dm_fast_training_init(dm_odm);
पूर्ण

व्योम rtl88eu_dm_update_rx_idle_ant(काष्ठा odm_dm_काष्ठा *dm_odm, u8 ant)
अणु
	काष्ठा fast_ant_train *dm_fat_tbl = &dm_odm->DM_FatTable;
	काष्ठा adapter *adapter = dm_odm->Adapter;
	u32 शेष_ant, optional_ant;

	अगर (dm_fat_tbl->RxIdleAnt == ant)
		वापस;

	अगर (ant == MAIN_ANT) अणु
		शेष_ant = (dm_odm->AntDivType == CG_TRX_HW_ANTDIV) ?
			       MAIN_ANT_CG_TRX : MAIN_ANT_CGCS_RX;
		optional_ant = (dm_odm->AntDivType == CG_TRX_HW_ANTDIV) ?
				AUX_ANT_CG_TRX : AUX_ANT_CGCS_RX;
	पूर्ण अन्यथा अणु
		शेष_ant = (dm_odm->AntDivType == CG_TRX_HW_ANTDIV) ?
			       AUX_ANT_CG_TRX : AUX_ANT_CGCS_RX;
		optional_ant = (dm_odm->AntDivType == CG_TRX_HW_ANTDIV) ?
				MAIN_ANT_CG_TRX : MAIN_ANT_CGCS_RX;
	पूर्ण

	अगर (dm_odm->AntDivType == CG_TRX_HW_ANTDIV) अणु
		phy_set_bb_reg(adapter, ODM_REG_RX_ANT_CTRL_11N,
			       BIT(5) | BIT(4) | BIT(3), शेष_ant);
		phy_set_bb_reg(adapter, ODM_REG_RX_ANT_CTRL_11N,
			       BIT(8) | BIT(7) | BIT(6), optional_ant);
		phy_set_bb_reg(adapter, ODM_REG_ANTSEL_CTRL_11N,
			       BIT(14) | BIT(13) | BIT(12), शेष_ant);
		phy_set_bb_reg(adapter, ODM_REG_RESP_TX_11N,
			       BIT(6) | BIT(7), शेष_ant);
	पूर्ण अन्यथा अगर (dm_odm->AntDivType == CGCS_RX_HW_ANTDIV) अणु
		phy_set_bb_reg(adapter, ODM_REG_RX_ANT_CTRL_11N,
			       BIT(5) | BIT(4) | BIT(3), शेष_ant);
		phy_set_bb_reg(adapter, ODM_REG_RX_ANT_CTRL_11N,
			       BIT(8) | BIT(7) | BIT(6), optional_ant);
	पूर्ण

	dm_fat_tbl->RxIdleAnt = ant;
पूर्ण

अटल व्योम update_tx_ant_88eu(काष्ठा odm_dm_काष्ठा *dm_odm, u8 ant, u32 mac_id)
अणु
	काष्ठा fast_ant_train *dm_fat_tbl = &dm_odm->DM_FatTable;
	u8 target_ant;

	अगर (ant == MAIN_ANT)
		target_ant = MAIN_ANT_CG_TRX;
	अन्यथा
		target_ant = AUX_ANT_CG_TRX;
	dm_fat_tbl->antsel_a[mac_id] = target_ant & BIT(0);
	dm_fat_tbl->antsel_b[mac_id] = (target_ant & BIT(1)) >> 1;
	dm_fat_tbl->antsel_c[mac_id] = (target_ant & BIT(2)) >> 2;
पूर्ण

व्योम rtl88eu_dm_set_tx_ant_by_tx_info(काष्ठा odm_dm_काष्ठा *dm_odm,
				      u8 *desc, u8 mac_id)
अणु
	काष्ठा fast_ant_train *dm_fat_tbl = &dm_odm->DM_FatTable;

	अगर ((dm_odm->AntDivType == CG_TRX_HW_ANTDIV) ||
	    (dm_odm->AntDivType == CG_TRX_SMART_ANTDIV)) अणु
		SET_TX_DESC_ANTSEL_A_88E(desc, dm_fat_tbl->antsel_a[mac_id]);
		SET_TX_DESC_ANTSEL_B_88E(desc, dm_fat_tbl->antsel_b[mac_id]);
		SET_TX_DESC_ANTSEL_C_88E(desc, dm_fat_tbl->antsel_c[mac_id]);
	पूर्ण
पूर्ण

व्योम rtl88eu_dm_ant_sel_statistics(काष्ठा odm_dm_काष्ठा *dm_odm,
				   u8 antsel_tr_mux, u32 mac_id, u8 rx_pwdb_all)
अणु
	काष्ठा fast_ant_train *dm_fat_tbl = &dm_odm->DM_FatTable;

	अगर (dm_odm->AntDivType == CG_TRX_HW_ANTDIV) अणु
		अगर (antsel_tr_mux == MAIN_ANT_CG_TRX) अणु
			dm_fat_tbl->MainAnt_Sum[mac_id] += rx_pwdb_all;
			dm_fat_tbl->MainAnt_Cnt[mac_id]++;
		पूर्ण अन्यथा अणु
			dm_fat_tbl->AuxAnt_Sum[mac_id] += rx_pwdb_all;
			dm_fat_tbl->AuxAnt_Cnt[mac_id]++;
		पूर्ण
	पूर्ण अन्यथा अगर (dm_odm->AntDivType == CGCS_RX_HW_ANTDIV) अणु
		अगर (antsel_tr_mux == MAIN_ANT_CGCS_RX) अणु
			dm_fat_tbl->MainAnt_Sum[mac_id] += rx_pwdb_all;
			dm_fat_tbl->MainAnt_Cnt[mac_id]++;
		पूर्ण अन्यथा अणु
			dm_fat_tbl->AuxAnt_Sum[mac_id] += rx_pwdb_all;
			dm_fat_tbl->AuxAnt_Cnt[mac_id]++;
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम rtl88eu_dm_hw_ant_भाग(काष्ठा odm_dm_काष्ठा *dm_odm)
अणु
	काष्ठा fast_ant_train *dm_fat_tbl = &dm_odm->DM_FatTable;
	काष्ठा rtw_dig *dig_table = &dm_odm->DM_DigTable;
	काष्ठा sta_info *entry;
	u32 i, min_rssi = 0xFF, ant_भाग_max_rssi = 0, max_rssi = 0;
	u32 local_min_rssi, local_max_rssi;
	u32 मुख्य_rssi, aux_rssi;
	u8 RxIdleAnt = 0, target_ant = 7;

	क्रम (i = 0; i < ODM_ASSOCIATE_ENTRY_NUM; i++) अणु
		entry = dm_odm->pODM_StaInfo[i];
		अगर (IS_STA_VALID(entry)) अणु
			/* 2 Calculate RSSI per Antenna */
			मुख्य_rssi = (dm_fat_tbl->MainAnt_Cnt[i] != 0) ?
				     (dm_fat_tbl->MainAnt_Sum[i] /
				      dm_fat_tbl->MainAnt_Cnt[i]) : 0;
			aux_rssi = (dm_fat_tbl->AuxAnt_Cnt[i] != 0) ?
				    (dm_fat_tbl->AuxAnt_Sum[i] /
				     dm_fat_tbl->AuxAnt_Cnt[i]) : 0;
			target_ant = (मुख्य_rssi >= aux_rssi) ? MAIN_ANT : AUX_ANT;
			/* 2 Select max_rssi क्रम DIG */
			local_max_rssi = max(मुख्य_rssi, aux_rssi);
			अगर ((local_max_rssi > ant_भाग_max_rssi) &&
			    (local_max_rssi < 40))
				ant_भाग_max_rssi = local_max_rssi;
			अगर (local_max_rssi > max_rssi)
				max_rssi = local_max_rssi;

			/* 2 Select RX Idle Antenna */
			अगर ((dm_fat_tbl->RxIdleAnt == MAIN_ANT) &&
			    (मुख्य_rssi == 0))
				मुख्य_rssi = aux_rssi;
			अन्यथा अगर ((dm_fat_tbl->RxIdleAnt == AUX_ANT) &&
				 (aux_rssi == 0))
				aux_rssi = मुख्य_rssi;

			local_min_rssi = min(मुख्य_rssi, aux_rssi);
			अगर (local_min_rssi < min_rssi) अणु
				min_rssi = local_min_rssi;
				RxIdleAnt = target_ant;
			पूर्ण
			/* 2 Select TRX Antenna */
			अगर (dm_odm->AntDivType == CG_TRX_HW_ANTDIV)
				update_tx_ant_88eu(dm_odm, target_ant, i);
		पूर्ण
		dm_fat_tbl->MainAnt_Sum[i] = 0;
		dm_fat_tbl->AuxAnt_Sum[i] = 0;
		dm_fat_tbl->MainAnt_Cnt[i] = 0;
		dm_fat_tbl->AuxAnt_Cnt[i] = 0;
	पूर्ण

	/* 2 Set RX Idle Antenna */
	rtl88eu_dm_update_rx_idle_ant(dm_odm, RxIdleAnt);

	dig_table->AntDiv_RSSI_max = ant_भाग_max_rssi;
	dig_table->RSSI_max = max_rssi;
पूर्ण

व्योम rtl88eu_dm_antenna_भागersity(काष्ठा odm_dm_काष्ठा *dm_odm)
अणु
	काष्ठा fast_ant_train *dm_fat_tbl = &dm_odm->DM_FatTable;
	काष्ठा adapter *adapter = dm_odm->Adapter;

	अगर (!(dm_odm->SupportAbility & ODM_BB_ANT_DIV))
		वापस;

	अगर (!dm_odm->bLinked) अणु
		ODM_RT_TRACE(dm_odm, ODM_COMP_ANT_DIV, ODM_DBG_LOUD,
			     ("ODM_AntennaDiversity_88E(): No Link.\n"));
		अगर (dm_fat_tbl->bBecomeLinked) अणु
			ODM_RT_TRACE(dm_odm, ODM_COMP_ANT_DIV, ODM_DBG_LOUD,
				     ("Need to Turn off HW AntDiv\n"));
			phy_set_bb_reg(adapter, ODM_REG_IGI_A_11N, BIT(7), 0);
			phy_set_bb_reg(adapter, ODM_REG_CCK_ANTDIV_PARA1_11N,
				       BIT(15), 0);
			अगर (dm_odm->AntDivType == CG_TRX_HW_ANTDIV)
				phy_set_bb_reg(adapter, ODM_REG_TX_ANT_CTRL_11N,
					       BIT(21), 0);
			dm_fat_tbl->bBecomeLinked = dm_odm->bLinked;
		पूर्ण
		वापस;
	पूर्ण

	अगर (!dm_fat_tbl->bBecomeLinked) अणु
		ODM_RT_TRACE(dm_odm, ODM_COMP_ANT_DIV, ODM_DBG_LOUD,
			     ("Need to Turn on HW AntDiv\n"));
		phy_set_bb_reg(adapter, ODM_REG_IGI_A_11N, BIT(7), 1);
		phy_set_bb_reg(adapter, ODM_REG_CCK_ANTDIV_PARA1_11N,
			       BIT(15), 1);
		अगर (dm_odm->AntDivType == CG_TRX_HW_ANTDIV)
			phy_set_bb_reg(adapter, ODM_REG_TX_ANT_CTRL_11N,
				       BIT(21), 1);
		dm_fat_tbl->bBecomeLinked = dm_odm->bLinked;
	पूर्ण

	अगर ((dm_odm->AntDivType == CG_TRX_HW_ANTDIV) ||
	    (dm_odm->AntDivType == CGCS_RX_HW_ANTDIV))
		rtl88eu_dm_hw_ant_भाग(dm_odm);
पूर्ण
