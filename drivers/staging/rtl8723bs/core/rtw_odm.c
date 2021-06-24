<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/******************************************************************************
 *
 * Copyright(c) 2013 Realtek Corporation. All rights reserved.
 *
 ******************************************************************************/

#समावेश <drv_types.h>
#समावेश <rtw_debug.h>
#समावेश <rtw_odm.h>
#समावेश <hal_data.h>

अटल स्थिर अक्षर * स्थिर odm_comp_str[] = अणु
	/* BIT0 */"ODM_COMP_DIG",
	/* BIT1 */"ODM_COMP_RA_MASK",
	/* BIT2 */"ODM_COMP_DYNAMIC_TXPWR",
	/* BIT3 */"ODM_COMP_FA_CNT",
	/* BIT4 */"ODM_COMP_RSSI_MONITOR",
	/* BIT5 */"ODM_COMP_CCK_PD",
	/* BIT6 */"ODM_COMP_ANT_DIV",
	/* BIT7 */"ODM_COMP_PWR_SAVE",
	/* BIT8 */"ODM_COMP_PWR_TRAIN",
	/* BIT9 */"ODM_COMP_RATE_ADAPTIVE",
	/* BIT10 */"ODM_COMP_PATH_DIV",
	/* BIT11 */"ODM_COMP_PSD",
	/* BIT12 */"ODM_COMP_DYNAMIC_PRICCA",
	/* BIT13 */"ODM_COMP_RXHP",
	/* BIT14 */"ODM_COMP_MP",
	/* BIT15 */"ODM_COMP_DYNAMIC_ATC",
	/* BIT16 */"ODM_COMP_EDCA_TURBO",
	/* BIT17 */"ODM_COMP_EARLY_MODE",
	/* BIT18 */शून्य,
	/* BIT19 */शून्य,
	/* BIT20 */शून्य,
	/* BIT21 */शून्य,
	/* BIT22 */शून्य,
	/* BIT23 */शून्य,
	/* BIT24 */"ODM_COMP_TX_PWR_TRACK",
	/* BIT25 */"ODM_COMP_RX_GAIN_TRACK",
	/* BIT26 */"ODM_COMP_CALIBRATION",
	/* BIT27 */शून्य,
	/* BIT28 */शून्य,
	/* BIT29 */शून्य,
	/* BIT30 */"ODM_COMP_COMMON",
	/* BIT31 */"ODM_COMP_INIT",
पूर्ण;

#घोषणा RTW_ODM_COMP_MAX 32

अटल स्थिर अक्षर * स्थिर odm_ability_str[] = अणु
	/* BIT0 */"ODM_BB_DIG",
	/* BIT1 */"ODM_BB_RA_MASK",
	/* BIT2 */"ODM_BB_DYNAMIC_TXPWR",
	/* BIT3 */"ODM_BB_FA_CNT",
	/* BIT4 */"ODM_BB_RSSI_MONITOR",
	/* BIT5 */"ODM_BB_CCK_PD",
	/* BIT6 */"ODM_BB_ANT_DIV",
	/* BIT7 */"ODM_BB_PWR_SAVE",
	/* BIT8 */"ODM_BB_PWR_TRAIN",
	/* BIT9 */"ODM_BB_RATE_ADAPTIVE",
	/* BIT10 */"ODM_BB_PATH_DIV",
	/* BIT11 */"ODM_BB_PSD",
	/* BIT12 */"ODM_BB_RXHP",
	/* BIT13 */"ODM_BB_ADAPTIVITY",
	/* BIT14 */"ODM_BB_DYNAMIC_ATC",
	/* BIT15 */शून्य,
	/* BIT16 */"ODM_MAC_EDCA_TURBO",
	/* BIT17 */"ODM_MAC_EARLY_MODE",
	/* BIT18 */शून्य,
	/* BIT19 */शून्य,
	/* BIT20 */शून्य,
	/* BIT21 */शून्य,
	/* BIT22 */शून्य,
	/* BIT23 */शून्य,
	/* BIT24 */"ODM_RF_TX_PWR_TRACK",
	/* BIT25 */"ODM_RF_RX_GAIN_TRACK",
	/* BIT26 */"ODM_RF_CALIBRATION",
पूर्ण;

#घोषणा RTW_ODM_ABILITY_MAX 27

अटल स्थिर अक्षर * स्थिर odm_dbg_level_str[] = अणु
	शून्य,
	"ODM_DBG_OFF",
	"ODM_DBG_SERIOUS",
	"ODM_DBG_WARNING",
	"ODM_DBG_LOUD",
	"ODM_DBG_TRACE",
पूर्ण;

#घोषणा RTW_ODM_DBG_LEVEL_NUM 6

व्योम rtw_odm_dbg_comp_msg(काष्ठा adapter *adapter)
अणु
	u64 dbg_comp;
	पूर्णांक i;

	rtw_hal_get_def_var(adapter, HW_DEF_ODM_DBG_FLAG, &dbg_comp);
	netdev_dbg(adapter->pnetdev, "odm.DebugComponents = 0x%016llx\n",
		   dbg_comp);
	क्रम (i = 0; i < RTW_ODM_COMP_MAX; i++) अणु
		अगर (odm_comp_str[i])
			netdev_dbg(adapter->pnetdev, "%cBIT%-2d %s\n",
				   (BIT0 << i) & dbg_comp ? '+' : ' ', i,
				   odm_comp_str[i]);
	पूर्ण
पूर्ण

अंतरभूत व्योम rtw_odm_dbg_comp_set(काष्ठा adapter *adapter, u64 comps)
अणु
	rtw_hal_set_def_var(adapter, HW_DEF_ODM_DBG_FLAG, &comps);
पूर्ण

व्योम rtw_odm_dbg_level_msg(व्योम *sel, काष्ठा adapter *adapter)
अणु
	u32 dbg_level;
	पूर्णांक i;

	rtw_hal_get_def_var(adapter, HW_DEF_ODM_DBG_LEVEL, &dbg_level);
	netdev_dbg(adapter->pnetdev, "odm.DebugLevel = %u\n", dbg_level);
	क्रम (i = 0; i < RTW_ODM_DBG_LEVEL_NUM; i++) अणु
		अगर (odm_dbg_level_str[i])
			netdev_dbg(adapter->pnetdev, "%u %s\n", i,
				   odm_dbg_level_str[i]);
	पूर्ण
पूर्ण

अंतरभूत व्योम rtw_odm_dbg_level_set(काष्ठा adapter *adapter, u32 level)
अणु
	rtw_hal_set_def_var(adapter, HW_DEF_ODM_DBG_LEVEL, &level);
पूर्ण

व्योम rtw_odm_ability_msg(व्योम *sel, काष्ठा adapter *adapter)
अणु
	u32 ability = 0;
	पूर्णांक i;

	rtw_hal_get_hwreg(adapter, HW_VAR_DM_FLAG, (u8 *)&ability);
	netdev_dbg(adapter->pnetdev, "odm.SupportAbility = 0x%08x\n", ability);
	क्रम (i = 0; i < RTW_ODM_ABILITY_MAX; i++) अणु
		अगर (odm_ability_str[i])
			netdev_dbg(adapter->pnetdev, "%cBIT%-2d %s\n",
				   (BIT0 << i) & ability ? '+' : ' ', i,
				   odm_ability_str[i]);
	पूर्ण
पूर्ण

अंतरभूत व्योम rtw_odm_ability_set(काष्ठा adapter *adapter, u32 ability)
अणु
	rtw_hal_set_hwreg(adapter, HW_VAR_DM_FLAG, (u8 *)&ability);
पूर्ण

व्योम rtw_odm_adaptivity_parm_msg(व्योम *sel, काष्ठा adapter *adapter)
अणु
	काष्ठा hal_com_data *pHalData = GET_HAL_DATA(adapter);
	काष्ठा dm_odm_t *odm = &pHalData->odmpriv;

	netdev_dbg(adapter->pnetdev, "%10s %16s %8s %10s %11s %14s\n",
		   "TH_L2H_ini", "TH_EDCCA_HL_diff", "IGI_Base", "ForceEDCCA",
		   "AdapEn_RSSI", "IGI_LowerBound");
	netdev_dbg(adapter->pnetdev,
		   "0x%-8x %-16d 0x%-6x %-10d %-11u %-14u\n",
		   (u8)odm->TH_L2H_ini,
		   odm->TH_EDCCA_HL_dअगरf,
		   odm->IGI_Base,
		   odm->ForceEDCCA,
		   odm->AdapEn_RSSI,
		   odm->IGI_LowerBound);
पूर्ण

व्योम rtw_odm_adaptivity_parm_set(काष्ठा adapter *adapter, s8 TH_L2H_ini,
				 s8 TH_EDCCA_HL_dअगरf, s8 IGI_Base,
				 bool ForceEDCCA, u8 AdapEn_RSSI,
				 u8 IGI_LowerBound)
अणु
	काष्ठा hal_com_data *pHalData = GET_HAL_DATA(adapter);
	काष्ठा dm_odm_t *odm = &pHalData->odmpriv;

	odm->TH_L2H_ini = TH_L2H_ini;
	odm->TH_EDCCA_HL_dअगरf = TH_EDCCA_HL_dअगरf;
	odm->IGI_Base = IGI_Base;
	odm->ForceEDCCA = ForceEDCCA;
	odm->AdapEn_RSSI = AdapEn_RSSI;
	odm->IGI_LowerBound = IGI_LowerBound;
पूर्ण

व्योम rtw_odm_get_perpkt_rssi(व्योम *sel, काष्ठा adapter *adapter)
अणु
	काष्ठा hal_com_data *hal_data = GET_HAL_DATA(adapter);
	काष्ठा dm_odm_t *odm = &hal_data->odmpriv;

	netdev_dbg(adapter->pnetdev,
		   "RxRate = %s, RSSI_A = %d(%%), RSSI_B = %d(%%)\n",
		   HDATA_RATE(odm->RxRate), odm->RSSI_A, odm->RSSI_B);
पूर्ण
