<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/* Copyright(c) 2009-2010  Realtek Corporation.*/

#समावेश "../wifi.h"
#समावेश "../base.h"
#समावेश "../pci.h"
#समावेश "../core.h"
#समावेश "reg.h"
#समावेश "def.h"
#समावेश "phy.h"
#समावेश "dm.h"
#समावेश "fw.h"
#समावेश "trx.h"
#समावेश "../btcoexist/rtl_btc.h"

अटल स्थिर u32 txscaling_tbl[TXSCALE_TABLE_SIZE] = अणु
	0x081, /* 0, -12.0dB */
	0x088, /* 1, -11.5dB */
	0x090, /* 2, -11.0dB */
	0x099, /* 3, -10.5dB */
	0x0A2, /* 4, -10.0dB */
	0x0AC, /* 5, -9.5dB */
	0x0B6, /* 6, -9.0dB */
	0x0C0, /* 7, -8.5dB */
	0x0CC, /* 8, -8.0dB */
	0x0D8, /* 9, -7.5dB */
	0x0E5, /* 10, -7.0dB */
	0x0F2, /* 11, -6.5dB */
	0x101, /* 12, -6.0dB */
	0x110, /* 13, -5.5dB */
	0x120, /* 14, -5.0dB */
	0x131, /* 15, -4.5dB */
	0x143, /* 16, -4.0dB */
	0x156, /* 17, -3.5dB */
	0x16A, /* 18, -3.0dB */
	0x180, /* 19, -2.5dB */
	0x197, /* 20, -2.0dB */
	0x1AF, /* 21, -1.5dB */
	0x1C8, /* 22, -1.0dB */
	0x1E3, /* 23, -0.5dB */
	0x200, /* 24, +0  dB */
	0x21E, /* 25, +0.5dB */
	0x23E, /* 26, +1.0dB */
	0x261, /* 27, +1.5dB */
	0x285, /* 28, +2.0dB */
	0x2AB, /* 29, +2.5dB */
	0x2D3, /* 30, +3.0dB */
	0x2FE, /* 31, +3.5dB */
	0x32B, /* 32, +4.0dB */
	0x35C, /* 33, +4.5dB */
	0x38E, /* 34, +5.0dB */
	0x3C4, /* 35, +5.5dB */
	0x3FE  /* 36, +6.0dB */
पूर्ण;

अटल स्थिर u32 rtl8821ae_txscaling_table[TXSCALE_TABLE_SIZE] = अणु
	0x081, /* 0, -12.0dB */
	0x088, /* 1, -11.5dB */
	0x090, /* 2, -11.0dB */
	0x099, /* 3, -10.5dB */
	0x0A2, /* 4, -10.0dB */
	0x0AC, /* 5, -9.5dB */
	0x0B6, /* 6, -9.0dB */
	0x0C0, /* 7, -8.5dB */
	0x0CC, /* 8, -8.0dB */
	0x0D8, /* 9, -7.5dB */
	0x0E5, /* 10, -7.0dB */
	0x0F2, /* 11, -6.5dB */
	0x101, /* 12, -6.0dB */
	0x110, /* 13, -5.5dB */
	0x120, /* 14, -5.0dB */
	0x131, /* 15, -4.5dB */
	0x143, /* 16, -4.0dB */
	0x156, /* 17, -3.5dB */
	0x16A, /* 18, -3.0dB */
	0x180, /* 19, -2.5dB */
	0x197, /* 20, -2.0dB */
	0x1AF, /* 21, -1.5dB */
	0x1C8, /* 22, -1.0dB */
	0x1E3, /* 23, -0.5dB */
	0x200, /* 24, +0  dB */
	0x21E, /* 25, +0.5dB */
	0x23E, /* 26, +1.0dB */
	0x261, /* 27, +1.5dB */
	0x285, /* 28, +2.0dB */
	0x2AB, /* 29, +2.5dB */
	0x2D3, /* 30, +3.0dB */
	0x2FE, /* 31, +3.5dB */
	0x32B, /* 32, +4.0dB */
	0x35C, /* 33, +4.5dB */
	0x38E, /* 34, +5.0dB */
	0x3C4, /* 35, +5.5dB */
	0x3FE  /* 36, +6.0dB */
पूर्ण;

अटल स्थिर u32 edca_setting_dl[PEER_MAX] = अणु
	0xa44f,		/* 0 UNKNOWN */
	0x5ea44f,	/* 1 REALTEK_90 */
	0x5e4322,	/* 2 REALTEK_92SE */
	0x5ea42b,		/* 3 BROAD	*/
	0xa44f,		/* 4 RAL */
	0xa630,		/* 5 ATH */
	0x5ea630,		/* 6 CISCO */
	0x5ea42b,		/* 7 MARVELL */
पूर्ण;

अटल स्थिर u32 edca_setting_ul[PEER_MAX] = अणु
	0x5e4322,	/* 0 UNKNOWN */
	0xa44f,		/* 1 REALTEK_90 */
	0x5ea44f,	/* 2 REALTEK_92SE */
	0x5ea32b,	/* 3 BROAD */
	0x5ea422,	/* 4 RAL */
	0x5ea322,	/* 5 ATH */
	0x3ea430,	/* 6 CISCO */
	0x5ea44f,	/* 7 MARV */
पूर्ण;

अटल स्थिर u8 rtl8818e_delta_swing_table_idx_24gb_p[] = अणु
	0, 0, 0, 0, 1, 1, 2, 2, 3, 3, 4, 4, 4, 4, 4,
	4, 4, 4, 5, 5, 7, 7, 8, 8, 8, 9, 9, 9, 9, 9पूर्ण;

अटल स्थिर u8 rtl8818e_delta_swing_table_idx_24gb_n[] = अणु
	0, 0, 0, 2, 2, 3, 3, 4, 4, 4, 4, 5, 5, 6, 6,
	7, 7, 7, 7, 8, 8, 9, 9, 10, 10, 10, 11, 11, 11, 11पूर्ण;

अटल स्थिर u8 rtl8812ae_delta_swing_table_idx_24gb_n[]  = अणु
	0, 1, 1, 1, 2, 2, 2, 3, 3, 3, 4, 4, 5, 5, 5, 6,
	6, 6, 7, 8, 9, 9, 9, 9, 10, 10, 10, 10, 11, 11पूर्ण;

अटल स्थिर u8 rtl8812ae_delta_swing_table_idx_24gb_p[] = अणु
	0, 0, 1, 1, 2, 2, 2, 2, 3, 3, 3, 4, 4, 5, 5, 6,
	6, 6, 7, 7, 7, 8, 8, 8, 9, 9, 9, 9, 9, 9पूर्ण;

अटल स्थिर u8 rtl8812ae_delta_swing_table_idx_24ga_n[] = अणु
	0, 1, 1, 1, 2, 2, 2, 3, 3, 3, 4, 4, 5, 5, 5, 6,
	6, 6, 7, 8, 8, 9, 9, 9, 10, 10, 10, 10, 11, 11पूर्ण;

अटल स्थिर u8 rtl8812ae_delta_swing_table_idx_24ga_p[] = अणु
	0, 0, 1, 1, 2, 2, 2, 2, 3, 3, 3, 4, 4, 5, 5, 6,
	6, 6, 7, 7, 7, 8, 8, 8, 9, 9, 9, 9, 9, 9पूर्ण;

अटल स्थिर u8 rtl8812ae_delta_swing_table_idx_24gcckb_n[] = अणु
	0, 1, 1, 1, 2, 2, 2, 3, 3, 3, 4, 4, 5, 5, 5, 6,
	6, 6, 7, 8, 9, 9, 9, 9, 10, 10, 10, 10, 11, 11पूर्ण;

अटल स्थिर u8 rtl8812ae_delta_swing_table_idx_24gcckb_p[] = अणु
	0, 0, 1, 1, 2, 2, 2, 2, 3, 3, 3, 4, 4, 5, 5, 6,
	6, 6, 7, 7, 7, 8, 8, 8, 9, 9, 9, 9, 9, 9पूर्ण;

अटल स्थिर u8 rtl8812ae_delta_swing_table_idx_24gccka_n[] = अणु
	0, 1, 1, 1, 2, 2, 2, 3, 3, 3, 4, 4, 5, 5, 5, 6,
	6, 6, 7, 8, 8, 9, 9, 9, 10, 10, 10, 10, 11, 11पूर्ण;

अटल स्थिर u8 rtl8812ae_delta_swing_table_idx_24gccka_p[] = अणु
	0, 0, 1, 1, 2, 2, 2, 2, 3, 3, 3, 4, 4, 5, 5, 6,
	6, 6, 7, 7, 7, 8, 8, 8, 9, 9, 9, 9, 9, 9पूर्ण;

अटल स्थिर u8 rtl8812ae_delta_swing_table_idx_5gb_n[][DEL_SW_IDX_SZ] = अणु
	अणु0, 1, 1, 2, 2, 2, 3, 3, 4, 4, 5, 5, 6, 6, 6, 7, 7,
	7, 8, 8, 9, 9, 9, 10, 10, 11, 11, 12, 12, 13पूर्ण,
	अणु0, 1, 1, 2, 2, 2, 3, 3, 4, 4, 4, 5, 5, 6, 6, 7,
	7, 8, 8, 9, 9, 10, 10, 11, 11, 12, 12, 12, 13, 13पूर्ण,
	अणु0, 1, 1, 2, 3, 3, 4, 4, 5, 6, 6, 7, 8, 9, 10, 11,
	12, 12, 13, 14, 14, 14, 15, 16, 17, 17, 17, 18, 18, 18पूर्ण,
पूर्ण;

अटल स्थिर u8 rtl8812ae_delta_swing_table_idx_5gb_p[][DEL_SW_IDX_SZ] = अणु
	अणु0, 1, 1, 2, 2, 3, 3, 4, 4, 5, 5, 6, 6, 6, 7, 7, 8,
	8, 9, 9, 10, 10, 11, 11, 11, 11, 11, 11, 11, 11पूर्ण,
	अणु0, 1, 1, 2, 2, 3, 3, 4, 4, 4, 5, 5, 6, 6, 7, 7, 8,
	8, 9, 9, 10, 10, 11, 11, 11, 11, 11, 11, 11, 11पूर्ण,
	अणु0, 1, 1, 2, 2, 3, 3, 4, 4, 5, 5, 6, 7, 7, 8, 8, 9,
	9, 10, 10, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11पूर्ण,
पूर्ण;

अटल स्थिर u8 rtl8812ae_delta_swing_table_idx_5ga_n[][DEL_SW_IDX_SZ] = अणु
	अणु0, 1, 1, 2, 2, 3, 3, 4, 4, 4, 5, 5, 6, 6, 7, 7, 8,
	8, 9, 9, 10, 10, 11, 11, 12, 12, 12, 13, 13, 13पूर्ण,
	अणु0, 1, 1, 2, 2, 2, 3, 3, 4, 4, 5, 5, 6, 6, 7, 8, 9,
	9, 10, 10, 11, 11, 11, 12, 12, 12, 12, 12, 13, 13पूर्ण,
	अणु0, 1, 1, 2, 2, 3, 3, 4, 5, 6, 7, 8, 8, 9, 10, 11,
	12, 13, 14, 14, 15, 15, 15, 16, 16, 16, 17, 17, 18, 18पूर्ण,
पूर्ण;

अटल स्थिर u8 rtl8812ae_delta_swing_table_idx_5ga_p[][DEL_SW_IDX_SZ] = अणु
	अणु0, 1, 1, 2, 2, 3, 3, 4, 4, 4, 4, 5, 5, 6, 7, 7, 8,
	8, 9, 9, 10, 10, 11, 11, 11, 11, 11, 11, 11, 11पूर्ण,
	अणु0, 1, 1, 2, 2, 3, 3, 4, 4, 4, 5, 5, 6, 6, 7, 7, 8,
	9, 9, 10, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11पूर्ण,
	अणु0, 1, 1, 2, 3, 3, 4, 4, 5, 6, 6, 7, 7, 8, 9, 9,
	10, 10, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11पूर्ण,
पूर्ण;

अटल स्थिर u8 rtl8821ae_delta_swing_table_idx_24ga_n[]  = अणु
	0, 1, 1, 2, 2, 2, 3, 3, 3, 4, 4, 4, 5, 5, 5, 6, 6,
	6, 7, 7, 7, 8, 8, 8, 9, 9, 9, 10, 10, 10पूर्ण;

अटल स्थिर u8 rtl8821ae_delta_swing_table_idx_24ga_p[] = अणु
	0, 0, 1, 1, 2, 2, 3, 3, 4, 4, 5, 5, 6, 6, 7, 7, 8,
	8, 9, 9, 10, 10, 11, 11, 12, 12, 12, 12, 12, 12पूर्ण;

अटल स्थिर u8 rtl8821ae_delta_swing_table_idx_24gccka_n[] = अणु
	0, 1, 1, 2, 2, 2, 3, 3, 3, 4, 4, 4, 5, 5, 5, 6, 6,
	6, 7, 7, 7, 8, 8, 8, 9, 9, 9, 10, 10, 10पूर्ण;

अटल स्थिर u8 rtl8821ae_delta_swing_table_idx_24gccka_p[] = अणु
	0, 0, 1, 1, 2, 2, 3, 3, 4, 4, 5, 5, 6, 6, 7, 7, 8,
	8, 9, 9, 10, 10, 11, 11, 12, 12, 12, 12, 12, 12पूर्ण;

अटल स्थिर u8 rtl8821ae_delta_swing_table_idx_5ga_n[][DEL_SW_IDX_SZ] = अणु
	अणु0, 0, 1, 2, 3, 3, 4, 5, 6, 6, 7, 8, 9, 9, 10, 11,
	12, 12, 13, 14, 15, 15, 16, 16, 16, 16, 16, 16, 16, 16पूर्ण,
	अणु0, 0, 1, 2, 3, 3, 4, 5, 6, 6, 7, 8, 9, 9, 10, 11,
	12, 12, 13, 14, 15, 15, 16, 16, 16, 16, 16, 16, 16, 16पूर्ण,
	अणु0, 0, 1, 2, 3, 3, 4, 5, 6, 6, 7, 8, 9, 9, 10, 11,
	12, 12, 13, 14, 15, 15, 16, 16, 16, 16, 16, 16, 16, 16पूर्ण,
पूर्ण;

अटल स्थिर u8 rtl8821ae_delta_swing_table_idx_5ga_p[][DEL_SW_IDX_SZ] = अणु
	अणु0, 0, 1, 2, 3, 3, 4, 5, 6, 6, 7, 8, 9, 9, 10, 11,
	12, 12, 13, 14, 15, 15, 16, 16, 16, 16, 16, 16, 16, 16पूर्ण,
	अणु0, 0, 1, 2, 3, 3, 4, 5, 6, 6, 7, 8, 9, 9, 10, 11,
	12, 12, 13, 14, 15, 15, 16, 16, 16, 16, 16, 16, 16, 16पूर्ण,
	अणु0, 0, 1, 2, 3, 3, 4, 5, 6, 6, 7, 8, 9, 9, 10, 11,
	12, 12, 13, 14, 15, 15, 16, 16, 16, 16, 16, 16, 16, 16पूर्ण,
पूर्ण;

व्योम rtl8821ae_dm_txघातer_track_adjust(काष्ठा ieee80211_hw *hw,
				       u8 type, u8 *pdirection,
				       u32 *poutग_लिखो_val)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	काष्ठा rtl_dm *rtldm = rtl_dm(rtl_priv(hw));
	u8 pwr_val = 0;

	अगर (type == 0) अणु
		अगर (rtlpriv->dm.swing_idx_ofdm[RF90_PATH_A] <=
			rtlpriv->dm.swing_idx_ofdm_base[RF90_PATH_A]) अणु
			*pdirection = 1;
			pwr_val = rtldm->swing_idx_ofdm_base[RF90_PATH_A] -
					rtldm->swing_idx_ofdm[RF90_PATH_A];
		पूर्ण अन्यथा अणु
			*pdirection = 2;
			pwr_val = rtldm->swing_idx_ofdm[RF90_PATH_A] -
				rtldm->swing_idx_ofdm_base[RF90_PATH_A];
		पूर्ण
	पूर्ण अन्यथा अगर (type == 1) अणु
		अगर (rtldm->swing_idx_cck <= rtldm->swing_idx_cck_base) अणु
			*pdirection = 1;
			pwr_val = rtldm->swing_idx_cck_base -
					rtldm->swing_idx_cck;
		पूर्ण अन्यथा अणु
			*pdirection = 2;
			pwr_val = rtldm->swing_idx_cck -
				rtldm->swing_idx_cck_base;
		पूर्ण
	पूर्ण

	अगर (pwr_val >= TXPWRTRACK_MAX_IDX && (*pdirection == 1))
		pwr_val = TXPWRTRACK_MAX_IDX;

	*poutग_लिखो_val = pwr_val | (pwr_val << 8)|
				(pwr_val << 16)|
				(pwr_val << 24);
पूर्ण

व्योम rtl8821ae_dm_clear_txघातer_tracking_state(काष्ठा ieee80211_hw *hw)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	काष्ठा rtl_dm *rtldm = rtl_dm(rtlpriv);
	काष्ठा rtl_efuse *rtlefuse = rtl_efuse(rtlpriv);
	u8 p = 0;

	rtldm->swing_idx_cck_base = rtldm->शेष_cck_index;
	rtldm->swing_idx_cck = rtldm->शेष_cck_index;
	rtldm->cck_index = 0;

	क्रम (p = RF90_PATH_A; p <= RF90_PATH_B; ++p) अणु
		rtldm->swing_idx_ofdm_base[p] = rtldm->शेष_ofdm_index;
		rtldm->swing_idx_ofdm[p] = rtldm->शेष_ofdm_index;
		rtldm->ofdm_index[p] = rtldm->शेष_ofdm_index;

		rtldm->घातer_index_offset[p] = 0;
		rtldm->delta_घातer_index[p] = 0;
		rtldm->delta_घातer_index_last[p] = 0;
		/*Initial Mix mode घातer tracking*/
		rtldm->असलolute_ofdm_swing_idx[p] = 0;
		rtldm->remnant_ofdm_swing_idx[p] = 0;
	पूर्ण
	/*Initial at Modअगरy Tx Scaling Mode*/
	rtldm->modअगरy_txagc_flag_path_a = false;
	/*Initial at Modअगरy Tx Scaling Mode*/
	rtldm->modअगरy_txagc_flag_path_b = false;
	rtldm->remnant_cck_idx = 0;
	rtldm->thermalvalue = rtlefuse->eeprom_thermalmeter;
	rtldm->thermalvalue_iqk = rtlefuse->eeprom_thermalmeter;
	rtldm->thermalvalue_lck = rtlefuse->eeprom_thermalmeter;
पूर्ण

अटल u8  rtl8821ae_dm_get_swing_index(काष्ठा ieee80211_hw *hw)
अणु
	काष्ठा rtl_hal *rtlhal = rtl_hal(rtl_priv(hw));
	u8 i = 0;
	u32  bb_swing;

	bb_swing = phy_get_tx_swing_8812A(hw, rtlhal->current_bandtype,
					  RF90_PATH_A);

	क्रम (i = 0; i < TXSCALE_TABLE_SIZE; ++i)
		अगर (bb_swing == rtl8821ae_txscaling_table[i])
			अवरोध;

	वापस i;
पूर्ण

व्योम rtl8821ae_dm_initialize_txघातer_tracking_thermalmeter(
				काष्ठा ieee80211_hw *hw)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	काष्ठा rtl_dm *rtldm = rtl_dm(rtlpriv);
	काष्ठा rtl_efuse *rtlefuse = rtl_efuse(rtlpriv);
	u8 शेष_swing_index  = 0;
	u8 p = 0;

	rtlpriv->dm.txघातer_track_control = true;
	rtldm->thermalvalue = rtlefuse->eeprom_thermalmeter;
	rtldm->thermalvalue_iqk = rtlefuse->eeprom_thermalmeter;
	rtldm->thermalvalue_lck = rtlefuse->eeprom_thermalmeter;
	शेष_swing_index = rtl8821ae_dm_get_swing_index(hw);

	rtldm->शेष_ofdm_index =
		(शेष_swing_index == TXSCALE_TABLE_SIZE) ?
		24 : शेष_swing_index;
	rtldm->शेष_cck_index = 24;

	rtldm->swing_idx_cck_base = rtldm->शेष_cck_index;
	rtldm->cck_index = rtldm->शेष_cck_index;

	क्रम (p = RF90_PATH_A; p < MAX_RF_PATH; ++p) अणु
		rtldm->swing_idx_ofdm_base[p] =
			rtldm->शेष_ofdm_index;
		rtldm->ofdm_index[p] = rtldm->शेष_ofdm_index;
		rtldm->delta_घातer_index[p] = 0;
		rtldm->घातer_index_offset[p] = 0;
		rtldm->delta_घातer_index_last[p] = 0;
	पूर्ण
पूर्ण

व्योम rtl8821ae_dm_init_edca_turbo(काष्ठा ieee80211_hw *hw)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);

	rtlpriv->dm.current_turbo_edca = false;
	rtlpriv->dm.is_any_nonbepkts = false;
	rtlpriv->dm.is_cur_rdlstate = false;
पूर्ण

व्योम rtl8821ae_dm_init_rate_adaptive_mask(काष्ठा ieee80211_hw *hw)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	काष्ठा rate_adaptive *p_ra = &rtlpriv->ra;

	p_ra->ratr_state = DM_RATR_STA_INIT;
	p_ra->pre_ratr_state = DM_RATR_STA_INIT;

	rtlpriv->dm.dm_type = DM_TYPE_BYDRIVER;
	अगर (rtlpriv->dm.dm_type == DM_TYPE_BYDRIVER)
		rtlpriv->dm.useramask = true;
	अन्यथा
		rtlpriv->dm.useramask = false;

	p_ra->high_rssi_thresh_क्रम_ra = 50;
	p_ra->low_rssi_thresh_क्रम_ra40m = 20;
पूर्ण

अटल व्योम rtl8821ae_dm_init_dynamic_atc_चयन(काष्ठा ieee80211_hw *hw)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);

	rtlpriv->dm.crystal_cap = rtlpriv->efuse.crystalcap;

	rtlpriv->dm.atc_status = rtl_get_bbreg(hw, ROFDM1_CFOTRACKING, BIT(11));
	rtlpriv->dm.cfo_threshold = CFO_THRESHOLD_XTAL;
पूर्ण

अटल व्योम rtl8821ae_dm_common_info_self_init(काष्ठा ieee80211_hw *hw)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	काष्ठा rtl_phy *rtlphy = &rtlpriv->phy;
	u8 पंचांगp;

	rtlphy->cck_high_घातer =
		(bool)rtl_get_bbreg(hw, ODM_REG_CCK_RPT_FORMAT_11AC,
				    ODM_BIT_CCK_RPT_FORMAT_11AC);

	पंचांगp = (u8)rtl_get_bbreg(hw, ODM_REG_BB_RX_PATH_11AC,
				ODM_BIT_BB_RX_PATH_11AC);
	अगर (पंचांगp & BIT(0))
		rtlpriv->dm.rfpath_rxenable[0] = true;
	अगर (पंचांगp & BIT(1))
		rtlpriv->dm.rfpath_rxenable[1] = true;
पूर्ण

व्योम rtl8821ae_dm_init(काष्ठा ieee80211_hw *hw)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	काष्ठा rtl_phy *rtlphy = &rtlpriv->phy;
	u32 cur_igvalue = rtl_get_bbreg(hw, ROFDM0_XAAGCCORE1, 0x7f);

	spin_lock(&rtlpriv->locks.iqk_lock);
	rtlphy->lck_inprogress = false;
	spin_unlock(&rtlpriv->locks.iqk_lock);

	rtlpriv->dm.dm_type = DM_TYPE_BYDRIVER;
	rtl8821ae_dm_common_info_self_init(hw);
	rtl_dm_diginit(hw, cur_igvalue);
	rtl8821ae_dm_init_rate_adaptive_mask(hw);
	rtl8821ae_dm_init_edca_turbo(hw);
	rtl8821ae_dm_initialize_txघातer_tracking_thermalmeter(hw);
	rtl8821ae_dm_init_dynamic_atc_चयन(hw);
पूर्ण

अटल व्योम rtl8821ae_dm_find_minimum_rssi(काष्ठा ieee80211_hw *hw)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	काष्ठा dig_t *rtl_dm_dig = &rtlpriv->dm_digtable;
	काष्ठा rtl_mac *mac = rtl_mac(rtlpriv);

	/* Determine the minimum RSSI  */
	अगर ((mac->link_state < MAC80211_LINKED) &&
	    (rtlpriv->dm.entry_min_undec_sm_pwdb == 0)) अणु
		rtl_dm_dig->min_undec_pwdb_क्रम_dm = 0;
		pr_debug("rtl8821ae: Not connected to any AP\n");
	पूर्ण
	अगर (mac->link_state >= MAC80211_LINKED) अणु
		अगर (mac->opmode == NL80211_IFTYPE_AP ||
		    mac->opmode == NL80211_IFTYPE_ADHOC) अणु
			rtl_dm_dig->min_undec_pwdb_क्रम_dm =
			    rtlpriv->dm.entry_min_undec_sm_pwdb;
			rtl_dbg(rtlpriv, COMP_BB_POWERSAVING, DBG_LOUD,
				"AP Client PWDB = 0x%lx\n",
				rtlpriv->dm.entry_min_undec_sm_pwdb);
		पूर्ण अन्यथा अणु
			rtl_dm_dig->min_undec_pwdb_क्रम_dm =
			    rtlpriv->dm.undec_sm_pwdb;
			rtl_dbg(rtlpriv, COMP_BB_POWERSAVING, DBG_LOUD,
				"STA Default Port PWDB = 0x%x\n",
				rtl_dm_dig->min_undec_pwdb_क्रम_dm);
		पूर्ण
	पूर्ण अन्यथा अणु
		rtl_dm_dig->min_undec_pwdb_क्रम_dm =
		    rtlpriv->dm.entry_min_undec_sm_pwdb;
		rtl_dbg(rtlpriv, COMP_BB_POWERSAVING, DBG_LOUD,
			"AP Ext Port or disconnect PWDB = 0x%x\n",
			rtl_dm_dig->min_undec_pwdb_क्रम_dm);
	पूर्ण
	rtl_dbg(rtlpriv, COMP_DIG, DBG_LOUD,
		"MinUndecoratedPWDBForDM =%d\n",
		rtl_dm_dig->min_undec_pwdb_क्रम_dm);
पूर्ण

अटल व्योम  rtl8812ae_dm_rssi_dump_to_रेजिस्टर(काष्ठा ieee80211_hw *hw)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);

	rtl_ग_लिखो_byte(rtlpriv, RA_RSSI_DUMP,
		       rtlpriv->stats.rx_rssi_percentage[0]);
	rtl_ग_लिखो_byte(rtlpriv, RB_RSSI_DUMP,
		       rtlpriv->stats.rx_rssi_percentage[1]);

	/* Rx EVM*/
	rtl_ग_लिखो_byte(rtlpriv, RS1_RX_EVM_DUMP,
		       rtlpriv->stats.rx_evm_dbm[0]);
	rtl_ग_लिखो_byte(rtlpriv, RS2_RX_EVM_DUMP,
		       rtlpriv->stats.rx_evm_dbm[1]);

	/*Rx SNR*/
	rtl_ग_लिखो_byte(rtlpriv, RA_RX_SNR_DUMP,
		       (u8)(rtlpriv->stats.rx_snr_db[0]));
	rtl_ग_लिखो_byte(rtlpriv, RB_RX_SNR_DUMP,
		       (u8)(rtlpriv->stats.rx_snr_db[1]));

	/*Rx Cfo_Short*/
	rtl_ग_लिखो_word(rtlpriv, RA_CFO_SHORT_DUMP,
		       rtlpriv->stats.rx_cfo_लघु[0]);
	rtl_ग_लिखो_word(rtlpriv, RB_CFO_SHORT_DUMP,
		       rtlpriv->stats.rx_cfo_लघु[1]);

	/*Rx Cfo_Tail*/
	rtl_ग_लिखो_word(rtlpriv, RA_CFO_LONG_DUMP,
		       rtlpriv->stats.rx_cfo_tail[0]);
	rtl_ग_लिखो_word(rtlpriv, RB_CFO_LONG_DUMP,
		       rtlpriv->stats.rx_cfo_tail[1]);
पूर्ण

अटल व्योम rtl8821ae_dm_check_rssi_monitor(काष्ठा ieee80211_hw *hw)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	काष्ठा dig_t *dm_digtable = &rtlpriv->dm_digtable;
	काष्ठा rtl_hal *rtlhal = rtl_hal(rtlpriv);
	काष्ठा rtl_mac *mac = rtl_mac(rtl_priv(hw));
	काष्ठा rtl_sta_info *drv_priv;
	u8 h2c_parameter[4] = अणु 0 पूर्ण;
	दीर्घ पंचांगp_entry_max_pwdb = 0, पंचांगp_entry_min_pwdb = 0xff;
	u8 stbc_tx = 0;
	u64 cur_rxokcnt = 0;
	अटल u64 last_txokcnt = 0, last_rxokcnt;

	cur_rxokcnt = rtlpriv->stats.rxbytesunicast - last_rxokcnt;
	last_txokcnt = rtlpriv->stats.txbytesunicast;
	last_rxokcnt = rtlpriv->stats.rxbytesunicast;
	अगर (cur_rxokcnt > (last_txokcnt * 6))
		h2c_parameter[3] = 0x01;
	अन्यथा
		h2c_parameter[3] = 0x00;

	/* AP & ADHOC & MESH */
	अगर (mac->opmode == NL80211_IFTYPE_AP ||
	    mac->opmode == NL80211_IFTYPE_ADHOC ||
	    mac->opmode == NL80211_IFTYPE_MESH_POINT) अणु
		spin_lock_bh(&rtlpriv->locks.entry_list_lock);
		list_क्रम_each_entry(drv_priv, &rtlpriv->entry_list, list) अणु
			अगर (drv_priv->rssi_stat.undec_sm_pwdb <
					पंचांगp_entry_min_pwdb)
				पंचांगp_entry_min_pwdb =
					drv_priv->rssi_stat.undec_sm_pwdb;
			अगर (drv_priv->rssi_stat.undec_sm_pwdb >
					पंचांगp_entry_max_pwdb)
				पंचांगp_entry_max_pwdb =
					drv_priv->rssi_stat.undec_sm_pwdb;
		पूर्ण
		spin_unlock_bh(&rtlpriv->locks.entry_list_lock);

		/* If associated entry is found */
		अगर (पंचांगp_entry_max_pwdb != 0) अणु
			rtlpriv->dm.entry_max_undec_sm_pwdb =
				पंचांगp_entry_max_pwdb;
			RTPRINT(rtlpriv, FDM, DM_PWDB,
				"EntryMaxPWDB = 0x%lx(%ld)\n",
				पंचांगp_entry_max_pwdb, पंचांगp_entry_max_pwdb);
		पूर्ण अन्यथा अणु
			rtlpriv->dm.entry_max_undec_sm_pwdb = 0;
		पूर्ण
		/* If associated entry is found */
		अगर (पंचांगp_entry_min_pwdb != 0xff) अणु
			rtlpriv->dm.entry_min_undec_sm_pwdb =
				पंचांगp_entry_min_pwdb;
			RTPRINT(rtlpriv, FDM, DM_PWDB,
				"EntryMinPWDB = 0x%lx(%ld)\n",
				पंचांगp_entry_min_pwdb, पंचांगp_entry_min_pwdb);
		पूर्ण अन्यथा अणु
			rtlpriv->dm.entry_min_undec_sm_pwdb = 0;
		पूर्ण
	पूर्ण
	/* Indicate Rx संकेत strength to FW. */
	अगर (rtlpriv->dm.useramask) अणु
		अगर (rtlhal->hw_type == HARDWARE_TYPE_RTL8812AE) अणु
			अगर (mac->mode == WIRELESS_MODE_AC_24G ||
			    mac->mode == WIRELESS_MODE_AC_5G ||
			    mac->mode == WIRELESS_MODE_AC_ONLY)
				stbc_tx = (mac->vht_cur_stbc &
					   STBC_VHT_ENABLE_TX) ? 1 : 0;
			अन्यथा
				stbc_tx = (mac->ht_cur_stbc &
					   STBC_HT_ENABLE_TX) ? 1 : 0;
			h2c_parameter[3] |= stbc_tx << 1;
		पूर्ण
		h2c_parameter[2] =
			(u8)(rtlpriv->dm.undec_sm_pwdb & 0xFF);
		h2c_parameter[1] = 0x20;
		h2c_parameter[0] = 0;
		अगर (rtlhal->hw_type == HARDWARE_TYPE_RTL8812AE)
			rtl8821ae_fill_h2c_cmd(hw, H2C_RSSI_21AE_REPORT, 4,
					       h2c_parameter);
		अन्यथा
			rtl8821ae_fill_h2c_cmd(hw, H2C_RSSI_21AE_REPORT, 3,
					       h2c_parameter);
	पूर्ण अन्यथा अणु
		rtl_ग_लिखो_byte(rtlpriv, 0x4fe, rtlpriv->dm.undec_sm_pwdb);
	पूर्ण
	अगर (rtlhal->hw_type == HARDWARE_TYPE_RTL8812AE)
		rtl8812ae_dm_rssi_dump_to_रेजिस्टर(hw);
	rtl8821ae_dm_find_minimum_rssi(hw);
	dm_digtable->rssi_val_min = rtlpriv->dm_digtable.min_undec_pwdb_क्रम_dm;
पूर्ण

व्योम rtl8821ae_dm_ग_लिखो_cck_cca_thres(काष्ठा ieee80211_hw *hw, u8 current_cca)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	काष्ठा dig_t *dm_digtable = &rtlpriv->dm_digtable;

	अगर (dm_digtable->cur_cck_cca_thres != current_cca)
		rtl_ग_लिखो_byte(rtlpriv, DM_REG_CCK_CCA_11AC, current_cca);

	dm_digtable->pre_cck_cca_thres = dm_digtable->cur_cck_cca_thres;
	dm_digtable->cur_cck_cca_thres = current_cca;
पूर्ण

व्योम rtl8821ae_dm_ग_लिखो_dig(काष्ठा ieee80211_hw *hw, u8 current_igi)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	काष्ठा dig_t *dm_digtable = &rtlpriv->dm_digtable;

	अगर (dm_digtable->stop_dig)
		वापस;

	अगर (dm_digtable->cur_igvalue != current_igi) अणु
		rtl_set_bbreg(hw, DM_REG_IGI_A_11AC,
			      DM_BIT_IGI_11AC, current_igi);
		अगर (rtlpriv->phy.rf_type != RF_1T1R)
			rtl_set_bbreg(hw, DM_REG_IGI_B_11AC,
				      DM_BIT_IGI_11AC, current_igi);
	पूर्ण
	dm_digtable->cur_igvalue = current_igi;
पूर्ण

अटल व्योम rtl8821ae_dm_dig(काष्ठा ieee80211_hw *hw)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	काष्ठा dig_t *dm_digtable = &rtlpriv->dm_digtable;
	काष्ठा rtl_mac *mac = rtl_mac(rtl_priv(hw));
	काष्ठा rtl_hal *rtlhal = rtl_hal(rtl_priv(hw));
	u8 dig_min_0;
	u8 dig_max_of_min;
	bool first_connect, first_disconnect;
	u8 dm_dig_max, dm_dig_min, offset;
	u8 current_igi = dm_digtable->cur_igvalue;

	rtl_dbg(rtlpriv, COMP_DIG, DBG_LOUD, "\n");

	अगर (mac->act_scanning) अणु
		rtl_dbg(rtlpriv, COMP_DIG, DBG_LOUD,
			"Return: In Scan Progress\n");
		वापस;
	पूर्ण

	/*add by Neil Chen to aव्योम PSD is processing*/
	dig_min_0 = dm_digtable->dig_min_0;
	first_connect = (mac->link_state >= MAC80211_LINKED) &&
			(!dm_digtable->media_connect_0);
	first_disconnect = (mac->link_state < MAC80211_LINKED) &&
			(dm_digtable->media_connect_0);

	/*1 Boundary Decision*/

	dm_dig_max = 0x5A;

	अगर (rtlhal->hw_type != HARDWARE_TYPE_RTL8821AE)
		dm_dig_min = DM_DIG_MIN;
	अन्यथा
		dm_dig_min = 0x1C;

	dig_max_of_min = DM_DIG_MAX_AP;

	अगर (mac->link_state >= MAC80211_LINKED) अणु
		अगर (rtlhal->hw_type != HARDWARE_TYPE_RTL8821AE)
			offset = 20;
		अन्यथा
			offset = 10;

		अगर ((dm_digtable->rssi_val_min + offset) > dm_dig_max)
			dm_digtable->rx_gain_max = dm_dig_max;
		अन्यथा अगर ((dm_digtable->rssi_val_min + offset) < dm_dig_min)
			dm_digtable->rx_gain_max = dm_dig_min;
		अन्यथा
			dm_digtable->rx_gain_max =
				dm_digtable->rssi_val_min + offset;

		rtl_dbg(rtlpriv, COMP_DIG, DBG_LOUD,
			"dm_digtable->rssi_val_min=0x%x,dm_digtable->rx_gain_max = 0x%x\n",
			dm_digtable->rssi_val_min,
			dm_digtable->rx_gain_max);
		अगर (rtlpriv->dm.one_entry_only) अणु
			offset = 0;

			अगर (dm_digtable->rssi_val_min - offset < dm_dig_min)
				dig_min_0 = dm_dig_min;
			अन्यथा अगर (dm_digtable->rssi_val_min -
				offset > dig_max_of_min)
				dig_min_0 = dig_max_of_min;
			अन्यथा
				dig_min_0 =
					dm_digtable->rssi_val_min - offset;

			rtl_dbg(rtlpriv, COMP_DIG, DBG_LOUD,
				"bOneEntryOnly=TRUE, dig_min_0=0x%x\n",
				dig_min_0);
		पूर्ण अन्यथा अणु
			dig_min_0 = dm_dig_min;
		पूर्ण
	पूर्ण अन्यथा अणु
		dm_digtable->rx_gain_max = dm_dig_max;
		dig_min_0 = dm_dig_min;
		rtl_dbg(rtlpriv, COMP_DIG, DBG_LOUD, "No Link\n");
	पूर्ण

	अगर (rtlpriv->falsealm_cnt.cnt_all > 10000) अणु
		rtl_dbg(rtlpriv, COMP_DIG, DBG_LOUD,
			"Abnormally false alarm case.\n");

		अगर (dm_digtable->large_fa_hit != 3)
			dm_digtable->large_fa_hit++;
		अगर (dm_digtable->क्रमbidden_igi < current_igi) अणु
			dm_digtable->क्रमbidden_igi = current_igi;
			dm_digtable->large_fa_hit = 1;
		पूर्ण

		अगर (dm_digtable->large_fa_hit >= 3) अणु
			अगर ((dm_digtable->क्रमbidden_igi + 1) >
				dm_digtable->rx_gain_max)
				dm_digtable->rx_gain_min =
					dm_digtable->rx_gain_max;
			अन्यथा
				dm_digtable->rx_gain_min =
					(dm_digtable->क्रमbidden_igi + 1);
			dm_digtable->recover_cnt = 3600;
		पूर्ण
	पूर्ण अन्यथा अणु
		/*Recovery mechanism क्रम IGI lower bound*/
		अगर (dm_digtable->recover_cnt != 0) अणु
			dm_digtable->recover_cnt--;
		पूर्ण अन्यथा अणु
			अगर (dm_digtable->large_fa_hit < 3) अणु
				अगर ((dm_digtable->क्रमbidden_igi - 1) <
				    dig_min_0) अणु
					dm_digtable->क्रमbidden_igi =
						dig_min_0;
					dm_digtable->rx_gain_min =
						dig_min_0;
					rtl_dbg(rtlpriv, COMP_DIG, DBG_LOUD,
						"Normal Case: At Lower Bound\n");
				पूर्ण अन्यथा अणु
					dm_digtable->क्रमbidden_igi--;
					dm_digtable->rx_gain_min =
					  (dm_digtable->क्रमbidden_igi + 1);
					rtl_dbg(rtlpriv, COMP_DIG, DBG_LOUD,
						"Normal Case: Approach Lower Bound\n");
				पूर्ण
			पूर्ण अन्यथा अणु
				dm_digtable->large_fa_hit = 0;
			पूर्ण
		पूर्ण
	पूर्ण
	rtl_dbg(rtlpriv, COMP_DIG, DBG_LOUD,
		"pDM_DigTable->LargeFAHit=%d\n",
		dm_digtable->large_fa_hit);

	अगर (rtlpriv->dm.dbginfo.num_qry_beacon_pkt < 10)
		dm_digtable->rx_gain_min = dm_dig_min;

	अगर (dm_digtable->rx_gain_min > dm_digtable->rx_gain_max)
		dm_digtable->rx_gain_min = dm_digtable->rx_gain_max;

	/*Adjust initial gain by false alarm*/
	अगर (mac->link_state >= MAC80211_LINKED) अणु
		rtl_dbg(rtlpriv, COMP_DIG, DBG_LOUD,
			"DIG AfterLink\n");
		अगर (first_connect) अणु
			अगर (dm_digtable->rssi_val_min <= dig_max_of_min)
				current_igi = dm_digtable->rssi_val_min;
			अन्यथा
				current_igi = dig_max_of_min;
			rtl_dbg(rtlpriv, COMP_DIG, DBG_LOUD,
				"First Connect\n");
		पूर्ण अन्यथा अणु
			अगर (rtlpriv->falsealm_cnt.cnt_all > DM_DIG_FA_TH2)
				current_igi = current_igi + 4;
			अन्यथा अगर (rtlpriv->falsealm_cnt.cnt_all > DM_DIG_FA_TH1)
				current_igi = current_igi + 2;
			अन्यथा अगर (rtlpriv->falsealm_cnt.cnt_all < DM_DIG_FA_TH0)
				current_igi = current_igi - 2;

			अगर ((rtlpriv->dm.dbginfo.num_qry_beacon_pkt < 10) &&
			    (rtlpriv->falsealm_cnt.cnt_all < DM_DIG_FA_TH1)) अणु
				current_igi = dm_digtable->rx_gain_min;
				rtl_dbg(rtlpriv, COMP_DIG, DBG_LOUD,
					"Beacon is less than 10 and FA is less than 768, IGI GOES TO 0x1E!!!!!!!!!!!!\n");
			पूर्ण
		पूर्ण
	पूर्ण अन्यथा अणु
		rtl_dbg(rtlpriv, COMP_DIG, DBG_LOUD,
			"DIG BeforeLink\n");
		अगर (first_disconnect) अणु
			current_igi = dm_digtable->rx_gain_min;
			rtl_dbg(rtlpriv, COMP_DIG, DBG_LOUD,
				"First DisConnect\n");
		पूर्ण अन्यथा अणु
			/* 2012.03.30 LukeLee: enable DIG beक्रमe
			 * link but with very high thresholds
			 */
			अगर (rtlpriv->falsealm_cnt.cnt_all > 2000)
				current_igi = current_igi + 4;
			अन्यथा अगर (rtlpriv->falsealm_cnt.cnt_all > 600)
				current_igi = current_igi + 2;
			अन्यथा अगर (rtlpriv->falsealm_cnt.cnt_all < 300)
				current_igi = current_igi - 2;

			अगर (current_igi >= 0x3e)
				current_igi = 0x3e;

			rtl_dbg(rtlpriv, COMP_DIG, DBG_LOUD, "England DIG\n");
		पूर्ण
	पूर्ण
	rtl_dbg(rtlpriv, COMP_DIG, DBG_LOUD,
		"DIG End Adjust IGI\n");
	/* Check initial gain by upper/lower bound*/

	अगर (current_igi > dm_digtable->rx_gain_max)
		current_igi = dm_digtable->rx_gain_max;
	अगर (current_igi < dm_digtable->rx_gain_min)
		current_igi = dm_digtable->rx_gain_min;

	rtl_dbg(rtlpriv, COMP_DIG, DBG_LOUD,
		"rx_gain_max=0x%x, rx_gain_min=0x%x\n",
		dm_digtable->rx_gain_max, dm_digtable->rx_gain_min);
	rtl_dbg(rtlpriv, COMP_DIG, DBG_LOUD,
		"TotalFA=%d\n", rtlpriv->falsealm_cnt.cnt_all);
	rtl_dbg(rtlpriv, COMP_DIG, DBG_LOUD,
		"CurIGValue=0x%x\n", current_igi);

	rtl8821ae_dm_ग_लिखो_dig(hw, current_igi);
	dm_digtable->media_connect_0 =
		((mac->link_state >= MAC80211_LINKED) ? true : false);
	dm_digtable->dig_min_0 = dig_min_0;
पूर्ण

अटल व्योम rtl8821ae_dm_common_info_self_update(काष्ठा ieee80211_hw *hw)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	u8 cnt = 0;
	काष्ठा rtl_sta_info *drv_priv;

	rtlpriv->dm.tx_rate = 0xff;

	rtlpriv->dm.one_entry_only = false;

	अगर (rtlpriv->mac80211.opmode == NL80211_IFTYPE_STATION &&
	    rtlpriv->mac80211.link_state >= MAC80211_LINKED) अणु
		rtlpriv->dm.one_entry_only = true;
		वापस;
	पूर्ण

	अगर (rtlpriv->mac80211.opmode == NL80211_IFTYPE_AP ||
	    rtlpriv->mac80211.opmode == NL80211_IFTYPE_ADHOC ||
	    rtlpriv->mac80211.opmode == NL80211_IFTYPE_MESH_POINT) अणु
		spin_lock_bh(&rtlpriv->locks.entry_list_lock);
		list_क्रम_each_entry(drv_priv, &rtlpriv->entry_list, list)
			cnt++;
		spin_unlock_bh(&rtlpriv->locks.entry_list_lock);

		अगर (cnt == 1)
			rtlpriv->dm.one_entry_only = true;
	पूर्ण
पूर्ण

अटल व्योम rtl8821ae_dm_false_alarm_counter_statistics(काष्ठा ieee80211_hw *hw)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	काष्ठा false_alarm_statistics *falsealm_cnt = &rtlpriv->falsealm_cnt;
	u32 cck_enable = 0;

	/*पढ़ो OFDM FA counter*/
	falsealm_cnt->cnt_ofdm_fail =
		rtl_get_bbreg(hw, ODM_REG_OFDM_FA_11AC, BMASKLWORD);
	falsealm_cnt->cnt_cck_fail =
		rtl_get_bbreg(hw, ODM_REG_CCK_FA_11AC, BMASKLWORD);

	cck_enable =  rtl_get_bbreg(hw, ODM_REG_BB_RX_PATH_11AC, BIT(28));
	अगर (cck_enable)  /*अगर(pDM_Odm->pBandType == ODM_BAND_2_4G)*/
		falsealm_cnt->cnt_all = falsealm_cnt->cnt_ofdm_fail +
					falsealm_cnt->cnt_cck_fail;
	अन्यथा
		falsealm_cnt->cnt_all = falsealm_cnt->cnt_ofdm_fail;

	/*reset OFDM FA coutner*/
	rtl_set_bbreg(hw, ODM_REG_OFDM_FA_RST_11AC, BIT(17), 1);
	rtl_set_bbreg(hw, ODM_REG_OFDM_FA_RST_11AC, BIT(17), 0);
	/* reset CCK FA counter*/
	rtl_set_bbreg(hw, ODM_REG_CCK_FA_RST_11AC, BIT(15), 0);
	rtl_set_bbreg(hw, ODM_REG_CCK_FA_RST_11AC, BIT(15), 1);

	rtl_dbg(rtlpriv, COMP_DIG, DBG_LOUD, "Cnt_Cck_fail=%d\n",
		falsealm_cnt->cnt_cck_fail);
	rtl_dbg(rtlpriv, COMP_DIG, DBG_LOUD, "cnt_ofdm_fail=%d\n",
		falsealm_cnt->cnt_ofdm_fail);
	rtl_dbg(rtlpriv, COMP_DIG, DBG_LOUD, "Total False Alarm=%d\n",
		falsealm_cnt->cnt_all);
पूर्ण

अटल व्योम rtl8812ae_dm_check_txघातer_tracking_thermalmeter(
		काष्ठा ieee80211_hw *hw)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);

	अगर (!rtlpriv->dm.पंचांग_trigger) अणु
		rtl_set_rfreg(hw, RF90_PATH_A, RF_T_METER_88E,
			      BIT(17) | BIT(16), 0x03);
		rtl_dbg(rtlpriv, COMP_POWER_TRACKING, DBG_LOUD,
			"Trigger 8812 Thermal Meter!!\n");
		rtlpriv->dm.पंचांग_trigger = 1;
		वापस;
	पूर्ण
	rtl_dbg(rtlpriv, COMP_POWER_TRACKING, DBG_LOUD,
		"Schedule TxPowerTracking direct call!!\n");
	rtl8812ae_dm_txघातer_tracking_callback_thermalmeter(hw);
पूर्ण

अटल व्योम rtl8821ae_dm_iq_calibrate(काष्ठा ieee80211_hw *hw)
अणु
	काष्ठा rtl_mac *mac = rtl_mac(rtl_priv(hw));
	काष्ठा rtl_dm *rtldm = rtl_dm(rtl_priv(hw));
	काष्ठा rtl_hal *rtlhal = rtl_hal(rtl_priv(hw));

	अगर (mac->link_state >= MAC80211_LINKED) अणु
		अगर (rtldm->linked_पूर्णांकerval < 3)
			rtldm->linked_पूर्णांकerval++;

		अगर (rtldm->linked_पूर्णांकerval == 2) अणु
			अगर (rtlhal->hw_type == HARDWARE_TYPE_RTL8812AE)
				rtl8812ae_phy_iq_calibrate(hw, false);
			अन्यथा
				rtl8821ae_phy_iq_calibrate(hw, false);
		पूर्ण
	पूर्ण अन्यथा अणु
		rtldm->linked_पूर्णांकerval = 0;
	पूर्ण
पूर्ण

अटल व्योम rtl8812ae_get_delta_swing_table(काष्ठा ieee80211_hw *hw,
					    स्थिर u8 **up_a,
					    स्थिर u8 **करोwn_a,
					    स्थिर u8 **up_b,
					    स्थिर u8 **करोwn_b)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	काष्ठा rtl_phy *rtlphy = &rtlpriv->phy;
	काष्ठा rtl_dm *rtldm = rtl_dm(rtl_priv(hw));
	u8 channel = rtlphy->current_channel;
	u8 rate = rtldm->tx_rate;

	अगर (1 <= channel && channel <= 14) अणु
		अगर (RTL8821AE_RX_HAL_IS_CCK_RATE(rate)) अणु
			*up_a = rtl8812ae_delta_swing_table_idx_24gccka_p;
			*करोwn_a = rtl8812ae_delta_swing_table_idx_24gccka_n;
			*up_b = rtl8812ae_delta_swing_table_idx_24gcckb_p;
			*करोwn_b = rtl8812ae_delta_swing_table_idx_24gcckb_n;
		पूर्ण अन्यथा अणु
			*up_a = rtl8812ae_delta_swing_table_idx_24ga_p;
			*करोwn_a = rtl8812ae_delta_swing_table_idx_24ga_n;
			*up_b = rtl8812ae_delta_swing_table_idx_24gb_p;
			*करोwn_b = rtl8812ae_delta_swing_table_idx_24gb_n;
		पूर्ण
	पूर्ण अन्यथा अगर (36 <= channel && channel <= 64) अणु
		*up_a = rtl8812ae_delta_swing_table_idx_5ga_p[0];
		*करोwn_a = rtl8812ae_delta_swing_table_idx_5ga_n[0];
		*up_b = rtl8812ae_delta_swing_table_idx_5gb_p[0];
		*करोwn_b = rtl8812ae_delta_swing_table_idx_5gb_n[0];
	पूर्ण अन्यथा अगर (100 <= channel && channel <= 140) अणु
		*up_a = rtl8812ae_delta_swing_table_idx_5ga_p[1];
		*करोwn_a = rtl8812ae_delta_swing_table_idx_5ga_n[1];
		*up_b = rtl8812ae_delta_swing_table_idx_5gb_p[1];
		*करोwn_b = rtl8812ae_delta_swing_table_idx_5gb_n[1];
	पूर्ण अन्यथा अगर (149 <= channel && channel <= 173) अणु
		*up_a = rtl8812ae_delta_swing_table_idx_5ga_p[2];
		*करोwn_a = rtl8812ae_delta_swing_table_idx_5ga_n[2];
		*up_b = rtl8812ae_delta_swing_table_idx_5gb_p[2];
		*करोwn_b = rtl8812ae_delta_swing_table_idx_5gb_n[2];
	पूर्ण अन्यथा अणु
		*up_a = rtl8818e_delta_swing_table_idx_24gb_p;
		*करोwn_a = rtl8818e_delta_swing_table_idx_24gb_n;
		*up_b = rtl8818e_delta_swing_table_idx_24gb_p;
		*करोwn_b = rtl8818e_delta_swing_table_idx_24gb_n;
	पूर्ण
पूर्ण

व्योम rtl8821ae_dm_update_init_rate(काष्ठा ieee80211_hw *hw, u8 rate)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	काष्ठा rtl_dm	*rtldm = rtl_dm(rtl_priv(hw));
	काष्ठा rtl_hal *rtlhal = rtl_hal(rtl_priv(hw));
	u8 p = 0;

	rtl_dbg(rtlpriv, COMP_POWER_TRACKING, DBG_LOUD,
		"Get C2H Command! Rate=0x%x\n", rate);

	rtldm->tx_rate = rate;

	अगर (rtlhal->hw_type == HARDWARE_TYPE_RTL8821AE) अणु
		rtl8821ae_dm_txpwr_track_set_pwr(hw, MIX_MODE, RF90_PATH_A, 0);
	पूर्ण अन्यथा अणु
		क्रम (p = RF90_PATH_A; p < MAX_PATH_NUM_8812A; p++)
			rtl8812ae_dm_txpwr_track_set_pwr(hw, MIX_MODE, p, 0);
	पूर्ण
पूर्ण

u8 rtl8821ae_hw_rate_to_mrate(काष्ठा ieee80211_hw *hw, u8 rate)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	u8 ret_rate = MGN_1M;

	चयन (rate) अणु
	हाल DESC_RATE1M:
		ret_rate = MGN_1M;
		अवरोध;
	हाल DESC_RATE2M:
		ret_rate = MGN_2M;
		अवरोध;
	हाल DESC_RATE5_5M:
		ret_rate = MGN_5_5M;
		अवरोध;
	हाल DESC_RATE11M:
		ret_rate = MGN_11M;
		अवरोध;
	हाल DESC_RATE6M:
		ret_rate = MGN_6M;
		अवरोध;
	हाल DESC_RATE9M:
		ret_rate = MGN_9M;
		अवरोध;
	हाल DESC_RATE12M:
		ret_rate = MGN_12M;
		अवरोध;
	हाल DESC_RATE18M:
		ret_rate = MGN_18M;
		अवरोध;
	हाल DESC_RATE24M:
		ret_rate = MGN_24M;
		अवरोध;
	हाल DESC_RATE36M:
		ret_rate = MGN_36M;
		अवरोध;
	हाल DESC_RATE48M:
		ret_rate = MGN_48M;
		अवरोध;
	हाल DESC_RATE54M:
		ret_rate = MGN_54M;
		अवरोध;
	हाल DESC_RATEMCS0:
		ret_rate = MGN_MCS0;
		अवरोध;
	हाल DESC_RATEMCS1:
		ret_rate = MGN_MCS1;
		अवरोध;
	हाल DESC_RATEMCS2:
		ret_rate = MGN_MCS2;
		अवरोध;
	हाल DESC_RATEMCS3:
		ret_rate = MGN_MCS3;
		अवरोध;
	हाल DESC_RATEMCS4:
		ret_rate = MGN_MCS4;
		अवरोध;
	हाल DESC_RATEMCS5:
		ret_rate = MGN_MCS5;
		अवरोध;
	हाल DESC_RATEMCS6:
		ret_rate = MGN_MCS6;
		अवरोध;
	हाल DESC_RATEMCS7:
		ret_rate = MGN_MCS7;
		अवरोध;
	हाल DESC_RATEMCS8:
		ret_rate = MGN_MCS8;
		अवरोध;
	हाल DESC_RATEMCS9:
		ret_rate = MGN_MCS9;
		अवरोध;
	हाल DESC_RATEMCS10:
		ret_rate = MGN_MCS10;
		अवरोध;
	हाल DESC_RATEMCS11:
		ret_rate = MGN_MCS11;
		अवरोध;
	हाल DESC_RATEMCS12:
		ret_rate = MGN_MCS12;
		अवरोध;
	हाल DESC_RATEMCS13:
		ret_rate = MGN_MCS13;
		अवरोध;
	हाल DESC_RATEMCS14:
		ret_rate = MGN_MCS14;
		अवरोध;
	हाल DESC_RATEMCS15:
		ret_rate = MGN_MCS15;
		अवरोध;
	हाल DESC_RATEVHT1SS_MCS0:
		ret_rate = MGN_VHT1SS_MCS0;
		अवरोध;
	हाल DESC_RATEVHT1SS_MCS1:
		ret_rate = MGN_VHT1SS_MCS1;
		अवरोध;
	हाल DESC_RATEVHT1SS_MCS2:
		ret_rate = MGN_VHT1SS_MCS2;
		अवरोध;
	हाल DESC_RATEVHT1SS_MCS3:
		ret_rate = MGN_VHT1SS_MCS3;
		अवरोध;
	हाल DESC_RATEVHT1SS_MCS4:
		ret_rate = MGN_VHT1SS_MCS4;
		अवरोध;
	हाल DESC_RATEVHT1SS_MCS5:
		ret_rate = MGN_VHT1SS_MCS5;
		अवरोध;
	हाल DESC_RATEVHT1SS_MCS6:
		ret_rate = MGN_VHT1SS_MCS6;
		अवरोध;
	हाल DESC_RATEVHT1SS_MCS7:
		ret_rate = MGN_VHT1SS_MCS7;
		अवरोध;
	हाल DESC_RATEVHT1SS_MCS8:
		ret_rate = MGN_VHT1SS_MCS8;
		अवरोध;
	हाल DESC_RATEVHT1SS_MCS9:
		ret_rate = MGN_VHT1SS_MCS9;
		अवरोध;
	हाल DESC_RATEVHT2SS_MCS0:
		ret_rate = MGN_VHT2SS_MCS0;
		अवरोध;
	हाल DESC_RATEVHT2SS_MCS1:
		ret_rate = MGN_VHT2SS_MCS1;
		अवरोध;
	हाल DESC_RATEVHT2SS_MCS2:
		ret_rate = MGN_VHT2SS_MCS2;
		अवरोध;
	हाल DESC_RATEVHT2SS_MCS3:
		ret_rate = MGN_VHT2SS_MCS3;
		अवरोध;
	हाल DESC_RATEVHT2SS_MCS4:
		ret_rate = MGN_VHT2SS_MCS4;
		अवरोध;
	हाल DESC_RATEVHT2SS_MCS5:
		ret_rate = MGN_VHT2SS_MCS5;
		अवरोध;
	हाल DESC_RATEVHT2SS_MCS6:
		ret_rate = MGN_VHT2SS_MCS6;
		अवरोध;
	हाल DESC_RATEVHT2SS_MCS7:
		ret_rate = MGN_VHT2SS_MCS7;
		अवरोध;
	हाल DESC_RATEVHT2SS_MCS8:
		ret_rate = MGN_VHT2SS_MCS8;
		अवरोध;
	हाल DESC_RATEVHT2SS_MCS9:
		ret_rate = MGN_VHT2SS_MCS9;
		अवरोध;
	शेष:
		rtl_dbg(rtlpriv, COMP_POWER_TRACKING, DBG_LOUD,
			"HwRateToMRate8812(): Non supported Rate [%x]!!!\n",
			rate);
		अवरोध;
	पूर्ण
	वापस ret_rate;
पूर्ण

/*-----------------------------------------------------------------------------
 * Function:	odm_TxPwrTrackSetPwr88E()
 *
 * Overview:	88E change all channel tx घातer accordign to flag.
 *				OFDM & CCK are all dअगरferent.
 *
 * Input:		NONE
 *
 * Output:		NONE
 *
 * Return:		NONE
 *
 * Revised History:
 *	When		Who		Remark
 *	04/23/2012	MHC		Create Version 0.
 *
 *---------------------------------------------------------------------------
 */
व्योम rtl8812ae_dm_txpwr_track_set_pwr(काष्ठा ieee80211_hw *hw,
				      क्रमागत pwr_track_control_method method,
				      u8 rf_path, u8 channel_mapped_index)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	काष्ठा rtl_dm	*rtldm = rtl_dm(rtl_priv(hw));
	काष्ठा rtl_phy *rtlphy = &rtlpriv->phy;
	u32 final_swing_idx[2];
	u8 pwr_tracking_limit = 26; /*+1.0dB*/
	u8 tx_rate = 0xFF;
	s8 final_ofdm_swing_index = 0;

	अगर (rtldm->tx_rate != 0xFF)
		tx_rate =
			rtl8821ae_hw_rate_to_mrate(hw, rtldm->tx_rate);

	rtl_dbg(rtlpriv, COMP_POWER_TRACKING, DBG_LOUD,
		"===>%s\n", __func__);
	/*20130429 Mimic Modअगरy High Rate BBSwing Limit.*/
	अगर (tx_rate != 0xFF) अणु
		/*CCK*/
		अगर ((tx_rate >= MGN_1M) && (tx_rate <= MGN_11M))
			pwr_tracking_limit = 32; /*+4dB*/
		/*OFDM*/
		अन्यथा अगर ((tx_rate >= MGN_6M) && (tx_rate <= MGN_48M))
			pwr_tracking_limit = 30; /*+3dB*/
		अन्यथा अगर (tx_rate == MGN_54M)
			pwr_tracking_limit = 28; /*+2dB*/
		/*HT*/
		 /*QPSK/BPSK*/
		अन्यथा अगर ((tx_rate >= MGN_MCS0) && (tx_rate <= MGN_MCS2))
			pwr_tracking_limit = 34; /*+5dB*/
		 /*16QAM*/
		अन्यथा अगर ((tx_rate >= MGN_MCS3) && (tx_rate <= MGN_MCS4))
			pwr_tracking_limit = 30; /*+3dB*/
		 /*64QAM*/
		अन्यथा अगर ((tx_rate >= MGN_MCS5) && (tx_rate <= MGN_MCS7))
			pwr_tracking_limit = 28; /*+2dB*/
		 /*QPSK/BPSK*/
		अन्यथा अगर ((tx_rate >= MGN_MCS8) && (tx_rate <= MGN_MCS10))
			pwr_tracking_limit = 34; /*+5dB*/
		 /*16QAM*/
		अन्यथा अगर ((tx_rate >= MGN_MCS11) && (tx_rate <= MGN_MCS12))
			pwr_tracking_limit = 30; /*+3dB*/
		 /*64QAM*/
		अन्यथा अगर ((tx_rate >= MGN_MCS13) && (tx_rate <= MGN_MCS15))
			pwr_tracking_limit = 28; /*+2dB*/

		/*2 VHT*/
		 /*QPSK/BPSK*/
		अन्यथा अगर ((tx_rate >= MGN_VHT1SS_MCS0) &&
			 (tx_rate <= MGN_VHT1SS_MCS2))
			pwr_tracking_limit = 34; /*+5dB*/
		 /*16QAM*/
		अन्यथा अगर ((tx_rate >= MGN_VHT1SS_MCS3) &&
			 (tx_rate <= MGN_VHT1SS_MCS4))
			pwr_tracking_limit = 30; /*+3dB*/
		 /*64QAM*/
		अन्यथा अगर ((tx_rate >= MGN_VHT1SS_MCS5) &&
			 (tx_rate <= MGN_VHT1SS_MCS6))
			pwr_tracking_limit = 28; /*+2dB*/
		अन्यथा अगर (tx_rate == MGN_VHT1SS_MCS7) /*64QAM*/
			pwr_tracking_limit = 26; /*+1dB*/
		अन्यथा अगर (tx_rate == MGN_VHT1SS_MCS8) /*256QAM*/
			pwr_tracking_limit = 24; /*+0dB*/
		अन्यथा अगर (tx_rate == MGN_VHT1SS_MCS9) /*256QAM*/
			pwr_tracking_limit = 22; /*-1dB*/
		 /*QPSK/BPSK*/
		अन्यथा अगर ((tx_rate >= MGN_VHT2SS_MCS0) &&
			 (tx_rate <= MGN_VHT2SS_MCS2))
			pwr_tracking_limit = 34; /*+5dB*/
		 /*16QAM*/
		अन्यथा अगर ((tx_rate >= MGN_VHT2SS_MCS3) &&
			 (tx_rate <= MGN_VHT2SS_MCS4))
			pwr_tracking_limit = 30; /*+3dB*/
		 /*64QAM*/
		अन्यथा अगर ((tx_rate >= MGN_VHT2SS_MCS5) &&
			 (tx_rate <= MGN_VHT2SS_MCS6))
			pwr_tracking_limit = 28; /*+2dB*/
		अन्यथा अगर (tx_rate == MGN_VHT2SS_MCS7) /*64QAM*/
			pwr_tracking_limit = 26; /*+1dB*/
		अन्यथा अगर (tx_rate == MGN_VHT2SS_MCS8) /*256QAM*/
			pwr_tracking_limit = 24; /*+0dB*/
		अन्यथा अगर (tx_rate == MGN_VHT2SS_MCS9) /*256QAM*/
			pwr_tracking_limit = 22; /*-1dB*/
		अन्यथा
			pwr_tracking_limit = 24;
	पूर्ण
	rtl_dbg(rtlpriv, COMP_POWER_TRACKING, DBG_LOUD,
		"TxRate=0x%x, PwrTrackingLimit=%d\n",
		tx_rate, pwr_tracking_limit);

	अगर (method == BBSWING) अणु
		rtl_dbg(rtlpriv, COMP_POWER_TRACKING, DBG_LOUD,
			"===>%s\n", __func__);

		अगर (rf_path == RF90_PATH_A) अणु
			u32 पंचांगp;

			final_swing_idx[RF90_PATH_A] =
				(rtldm->ofdm_index[RF90_PATH_A] >
				pwr_tracking_limit) ?
				pwr_tracking_limit :
				rtldm->ofdm_index[RF90_PATH_A];
			पंचांगp = final_swing_idx[RF90_PATH_A];
			rtl_dbg(rtlpriv, COMP_POWER_TRACKING, DBG_LOUD,
				"pDM_Odm->RFCalibrateInfo.OFDM_index[ODM_RF_PATH_A]=%d,pDM_Odm->RealBbSwingIdx[ODM_RF_PATH_A]=%d\n",
				rtldm->ofdm_index[RF90_PATH_A],
				final_swing_idx[RF90_PATH_A]);

			rtl_set_bbreg(hw, RA_TXSCALE, 0xFFE00000,
				      txscaling_tbl[पंचांगp]);
		पूर्ण अन्यथा अणु
			u32 पंचांगp;

			final_swing_idx[RF90_PATH_B] =
				rtldm->ofdm_index[RF90_PATH_B] >
				pwr_tracking_limit ?
				pwr_tracking_limit :
				rtldm->ofdm_index[RF90_PATH_B];
			पंचांगp = final_swing_idx[RF90_PATH_B];
			rtl_dbg(rtlpriv, COMP_POWER_TRACKING, DBG_LOUD,
				"pDM_Odm->RFCalibrateInfo.OFDM_index[ODM_RF_PATH_B]=%d, pDM_Odm->RealBbSwingIdx[ODM_RF_PATH_B]=%d\n",
				rtldm->ofdm_index[RF90_PATH_B],
				final_swing_idx[RF90_PATH_B]);

			rtl_set_bbreg(hw, RB_TXSCALE, 0xFFE00000,
				      txscaling_tbl[पंचांगp]);
		पूर्ण
	पूर्ण अन्यथा अगर (method == MIX_MODE) अणु
		rtl_dbg(rtlpriv, COMP_POWER_TRACKING, DBG_LOUD,
			"pDM_Odm->DefaultOfdmIndex=%d, pDM_Odm->Absolute_OFDMSwingIdx[RFPath]=%d, RF_Path = %d\n",
			rtldm->शेष_ofdm_index,
			rtldm->असलolute_ofdm_swing_idx[rf_path],
			rf_path);

		final_ofdm_swing_index = rtldm->शेष_ofdm_index +
				rtldm->असलolute_ofdm_swing_idx[rf_path];

		अगर (rf_path == RF90_PATH_A) अणु
			/*BBSwing higher then Limit*/
			अगर (final_ofdm_swing_index > pwr_tracking_limit) अणु
				rtldm->remnant_cck_idx =
					final_ofdm_swing_index -
					pwr_tracking_limit;
				/* CCK Follow the same compensation value
				 * as Path A
				 */
				rtldm->remnant_ofdm_swing_idx[rf_path] =
					final_ofdm_swing_index -
					pwr_tracking_limit;

				rtl_set_bbreg(hw, RA_TXSCALE, 0xFFE00000,
					      txscaling_tbl[pwr_tracking_limit]);

				rtldm->modअगरy_txagc_flag_path_a = true;

				/*Set TxAGC Page Cअणुपूर्ण;*/
				rtl8821ae_phy_set_txघातer_level_by_path(hw,
					rtlphy->current_channel,
					RF90_PATH_A);

				rtl_dbg(rtlpriv, COMP_POWER_TRACKING, DBG_LOUD,
					"******Path_A Over BBSwing Limit ,PwrTrackingLimit = %d ,Remnant TxAGC Value = %d\n",
					pwr_tracking_limit,
					rtldm->remnant_ofdm_swing_idx[rf_path]);
			पूर्ण अन्यथा अगर (final_ofdm_swing_index < 0) अणु
				rtldm->remnant_cck_idx = final_ofdm_swing_index;
				/* CCK Follow the same compensate value as Path A*/
				rtldm->remnant_ofdm_swing_idx[rf_path] =
					final_ofdm_swing_index;

				rtl_set_bbreg(hw, RA_TXSCALE, 0xFFE00000,
					txscaling_tbl[0]);

				rtldm->modअगरy_txagc_flag_path_a = true;

				/*Set TxAGC Page Cअणुपूर्ण;*/
				rtl8821ae_phy_set_txघातer_level_by_path(hw,
					rtlphy->current_channel, RF90_PATH_A);

				rtl_dbg(rtlpriv, COMP_POWER_TRACKING, DBG_LOUD,
					"******Path_A Lower then BBSwing lower bound  0 , Remnant TxAGC Value = %d\n",
					rtldm->remnant_ofdm_swing_idx[rf_path]);
			पूर्ण अन्यथा अणु
				rtl_set_bbreg(hw, RA_TXSCALE, 0xFFE00000,
					txscaling_tbl[(u8)final_ofdm_swing_index]);

				rtl_dbg(rtlpriv, COMP_POWER_TRACKING, DBG_LOUD,
					"******Path_A Compensate with BBSwing, Final_OFDM_Swing_Index = %d\n",
					final_ofdm_swing_index);
				/*If TxAGC has changed, reset TxAGC again*/
				अगर (rtldm->modअगरy_txagc_flag_path_a) अणु
					rtldm->remnant_cck_idx = 0;
					rtldm->remnant_ofdm_swing_idx[rf_path] = 0;

					/*Set TxAGC Page Cअणुपूर्ण;*/
					rtl8821ae_phy_set_txघातer_level_by_path(hw,
						rtlphy->current_channel, RF90_PATH_A);
					rtldm->modअगरy_txagc_flag_path_a = false;

					rtl_dbg(rtlpriv, COMP_POWER_TRACKING,
						DBG_LOUD,
						"******Path_A pDM_Odm->Modify_TxAGC_Flag = FALSE\n");
				पूर्ण
			पूर्ण
		पूर्ण
		/*BBSwing higher then Limit*/
		अगर (rf_path == RF90_PATH_B) अणु
			अगर (final_ofdm_swing_index > pwr_tracking_limit) अणु
				rtldm->remnant_ofdm_swing_idx[rf_path] =
					final_ofdm_swing_index -
					pwr_tracking_limit;

				rtl_set_bbreg(hw, RB_TXSCALE,
					0xFFE00000,
					txscaling_tbl[pwr_tracking_limit]);

				rtldm->modअगरy_txagc_flag_path_b = true;

				/*Set TxAGC Page Eअणुपूर्ण;*/
				rtl8821ae_phy_set_txघातer_level_by_path(hw,
					rtlphy->current_channel, RF90_PATH_B);

				rtl_dbg(rtlpriv, COMP_POWER_TRACKING, DBG_LOUD,
					"******Path_B Over BBSwing Limit , PwrTrackingLimit = %d , Remnant TxAGC Value = %d\n",
					pwr_tracking_limit,
					 rtldm->remnant_ofdm_swing_idx[rf_path]);
			पूर्ण अन्यथा अगर (final_ofdm_swing_index < 0) अणु
				rtldm->remnant_ofdm_swing_idx[rf_path] =
					final_ofdm_swing_index;

				rtl_set_bbreg(hw, RB_TXSCALE, 0xFFE00000,
					      txscaling_tbl[0]);

				rtldm->modअगरy_txagc_flag_path_b = true;

				/*Set TxAGC Page Eअणुपूर्ण;*/
				rtl8821ae_phy_set_txघातer_level_by_path(hw,
					rtlphy->current_channel, RF90_PATH_B);

				rtl_dbg(rtlpriv, COMP_POWER_TRACKING, DBG_LOUD,
					"******Path_B Lower then BBSwing lower bound  0 , Remnant TxAGC Value = %d\n",
					rtldm->remnant_ofdm_swing_idx[rf_path]);
			पूर्ण अन्यथा अणु
				rtl_set_bbreg(hw, RB_TXSCALE, 0xFFE00000,
					txscaling_tbl[(u8)final_ofdm_swing_index]);

				rtl_dbg(rtlpriv, COMP_POWER_TRACKING, DBG_LOUD,
					"******Path_B Compensate with BBSwing ,Final_OFDM_Swing_Index = %d\n",
					final_ofdm_swing_index);
				 /*If TxAGC has changed, reset TxAGC again*/
				अगर (rtldm->modअगरy_txagc_flag_path_b) अणु
					rtldm->remnant_ofdm_swing_idx[rf_path] = 0;

					/*Set TxAGC Page Eअणुपूर्ण;*/
					rtl8821ae_phy_set_txघातer_level_by_path(hw,
					rtlphy->current_channel, RF90_PATH_B);

					rtldm->modअगरy_txagc_flag_path_b =
						false;

					rtl_dbg(rtlpriv, COMP_POWER_TRACKING, DBG_LOUD,
						"******Path_B pDM_Odm->Modify_TxAGC_Flag = FALSE\n");
				पूर्ण
			पूर्ण
		पूर्ण
	पूर्ण अन्यथा अणु
		वापस;
	पूर्ण
पूर्ण

व्योम rtl8812ae_dm_txघातer_tracking_callback_thermalmeter(
	काष्ठा ieee80211_hw *hw)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	काष्ठा rtl_efuse *rtlefuse = rtl_efuse(rtl_priv(hw));
	काष्ठा rtl_dm	*rtldm = rtl_dm(rtl_priv(hw));
	काष्ठा rtl_hal *rtlhal = rtl_hal(rtl_priv(hw));
	u8 thermal_value = 0, delta, delta_lck, delta_iqk, p = 0, i = 0;
	u8 thermal_value_avg_count = 0;
	u32 thermal_value_avg = 0;
	/* OFDM BB Swing should be less than +3.0dB, */
	u8 ofdm_min_index = 6;
	 /* GetRightChnlPlaceक्रमIQK(pHalData->CurrentChannel)*/
	u8 index_क्रम_channel = 0;
	/* 1. The following TWO tables decide
	 * the final index of OFDM/CCK swing table.
	 */
	स्थिर u8 *delta_swing_table_idx_tup_a;
	स्थिर u8 *delta_swing_table_idx_tकरोwn_a;
	स्थिर u8 *delta_swing_table_idx_tup_b;
	स्थिर u8 *delta_swing_table_idx_tकरोwn_b;

	/*2. Initilization ( 7 steps in total )*/
	rtl8812ae_get_delta_swing_table(hw,
		&delta_swing_table_idx_tup_a,
		&delta_swing_table_idx_tकरोwn_a,
		&delta_swing_table_idx_tup_b,
		&delta_swing_table_idx_tकरोwn_b);

	rtldm->txघातer_trackinginit = true;

	rtl_dbg(rtlpriv, COMP_POWER_TRACKING, DBG_LOUD,
		"pDM_Odm->BbSwingIdxCckBase: %d, pDM_Odm->BbSwingIdxOfdmBase[A]:%d, pDM_Odm->DefaultOfdmIndex: %d\n",
		rtldm->swing_idx_cck_base,
		rtldm->swing_idx_ofdm_base[RF90_PATH_A],
		rtldm->शेष_ofdm_index);

	thermal_value = (u8)rtl_get_rfreg(hw, RF90_PATH_A,
		/*0x42: RF Reg[15:10] 88E*/
		RF_T_METER_8812A, 0xfc00);
	rtl_dbg(rtlpriv, COMP_POWER_TRACKING, DBG_LOUD,
		"Thermal Meter = 0x%X, EFUSE Thermal Base = 0x%X\n",
		thermal_value, rtlefuse->eeprom_thermalmeter);
	अगर (!rtldm->txघातer_track_control ||
	    rtlefuse->eeprom_thermalmeter == 0 ||
	    rtlefuse->eeprom_thermalmeter == 0xFF)
		वापस;

	/* 3. Initialize ThermalValues of RFCalibrateInfo*/

	अगर (rtlhal->reloadtxघातerindex)
		rtl_dbg(rtlpriv, COMP_POWER_TRACKING, DBG_LOUD,
			"reload ofdm index for band switch\n");

	/*4. Calculate average thermal meter*/
	rtldm->thermalvalue_avg[rtldm->thermalvalue_avg_index] = thermal_value;
	rtldm->thermalvalue_avg_index++;
	अगर (rtldm->thermalvalue_avg_index == AVG_THERMAL_NUM_8812A)
		/*Average बार =  c.AverageThermalNum*/
		rtldm->thermalvalue_avg_index = 0;

	क्रम (i = 0; i < AVG_THERMAL_NUM_8812A; i++) अणु
		अगर (rtldm->thermalvalue_avg[i]) अणु
			thermal_value_avg += rtldm->thermalvalue_avg[i];
			thermal_value_avg_count++;
		पूर्ण
	पूर्ण
	/*Calculate Average ThermalValue after average enough बार*/
	अगर (thermal_value_avg_count) अणु
		thermal_value = (u8)(thermal_value_avg /
				thermal_value_avg_count);
		rtl_dbg(rtlpriv, COMP_POWER_TRACKING, DBG_LOUD,
			"AVG Thermal Meter = 0x%X, EFUSE Thermal Base = 0x%X\n",
			thermal_value, rtlefuse->eeprom_thermalmeter);
	पूर्ण

	/*5. Calculate delta, delta_LCK, delta_IQK.
	 *"delta" here is used to determine whether
	 *thermal value changes or not.
	 */
	delta = (thermal_value > rtldm->thermalvalue) ?
		(thermal_value - rtldm->thermalvalue) :
		(rtldm->thermalvalue - thermal_value);
	delta_lck = (thermal_value > rtldm->thermalvalue_lck) ?
		(thermal_value - rtldm->thermalvalue_lck) :
		(rtldm->thermalvalue_lck - thermal_value);
	delta_iqk = (thermal_value > rtldm->thermalvalue_iqk) ?
		(thermal_value - rtldm->thermalvalue_iqk) :
		(rtldm->thermalvalue_iqk - thermal_value);

	rtl_dbg(rtlpriv, COMP_POWER_TRACKING, DBG_LOUD,
		"(delta, delta_LCK, delta_IQK) = (%d, %d, %d)\n",
		delta, delta_lck, delta_iqk);

	/* 6. If necessary, करो LCK.
	 * Delta temperature is equal to or larger than 20 centigrade.
	 */
	अगर (delta_lck >= IQK_THRESHOLD) अणु
		rtl_dbg(rtlpriv, COMP_POWER_TRACKING, DBG_LOUD,
			"delta_LCK(%d) >= Threshold_IQK(%d)\n",
			delta_lck, IQK_THRESHOLD);
		rtldm->thermalvalue_lck = thermal_value;
		rtl8821ae_phy_lc_calibrate(hw);
	पूर्ण

	/*7. If necessary, move the index of swing table to adjust Tx घातer.*/

	अगर (delta > 0 && rtldm->txघातer_track_control) अणु
		/* "delta" here is used to record the
		 * असलolute value of dअगरferrence.
		 */
		delta = thermal_value > rtlefuse->eeprom_thermalmeter ?
			(thermal_value - rtlefuse->eeprom_thermalmeter) :
			(rtlefuse->eeprom_thermalmeter - thermal_value);

		अगर (delta >= TXPWR_TRACK_TABLE_SIZE)
			delta = TXPWR_TRACK_TABLE_SIZE - 1;

		/*7.1 The Final Power Index = BaseIndex + PowerIndexOffset*/

		अगर (thermal_value > rtlefuse->eeprom_thermalmeter) अणु
			rtl_dbg(rtlpriv, COMP_POWER_TRACKING, DBG_LOUD,
				"delta_swing_table_idx_tup_a[%d] = %d\n",
				delta, delta_swing_table_idx_tup_a[delta]);
			rtldm->delta_घातer_index_last[RF90_PATH_A] =
				rtldm->delta_घातer_index[RF90_PATH_A];
			rtldm->delta_घातer_index[RF90_PATH_A] =
				delta_swing_table_idx_tup_a[delta];

			rtldm->असलolute_ofdm_swing_idx[RF90_PATH_A] =
				delta_swing_table_idx_tup_a[delta];
			/*Record delta swing क्रम mix mode घातer tracking*/

			rtl_dbg(rtlpriv, COMP_POWER_TRACKING, DBG_LOUD,
				"******Temp is higher and pDM_Odm->Absolute_OFDMSwingIdx[ODM_RF_PATH_A] = %d\n",
			rtldm->असलolute_ofdm_swing_idx[RF90_PATH_A]);

			rtl_dbg(rtlpriv, COMP_POWER_TRACKING, DBG_LOUD,
				"delta_swing_table_idx_tup_b[%d] = %d\n",
				delta, delta_swing_table_idx_tup_b[delta]);
			rtldm->delta_घातer_index_last[RF90_PATH_B] =
				rtldm->delta_घातer_index[RF90_PATH_B];
			rtldm->delta_घातer_index[RF90_PATH_B] =
				delta_swing_table_idx_tup_b[delta];

			rtldm->असलolute_ofdm_swing_idx[RF90_PATH_B] =
				delta_swing_table_idx_tup_b[delta];
			/*Record delta swing क्रम mix mode घातer tracking*/

			rtl_dbg(rtlpriv, COMP_POWER_TRACKING, DBG_LOUD,
				"******Temp is higher and pDM_Odm->Absolute_OFDMSwingIdx[ODM_RF_PATH_B] = %d\n",
				rtldm->असलolute_ofdm_swing_idx[RF90_PATH_B]);
		पूर्ण अन्यथा अणु
			rtl_dbg(rtlpriv, COMP_POWER_TRACKING, DBG_LOUD,
				"delta_swing_table_idx_tdown_a[%d] = %d\n",
				delta, delta_swing_table_idx_tकरोwn_a[delta]);

			rtldm->delta_घातer_index_last[RF90_PATH_A] =
				rtldm->delta_घातer_index[RF90_PATH_A];
			rtldm->delta_घातer_index[RF90_PATH_A] =
				-1 * delta_swing_table_idx_tकरोwn_a[delta];

			rtldm->असलolute_ofdm_swing_idx[RF90_PATH_A] =
				-1 * delta_swing_table_idx_tकरोwn_a[delta];
			/* Record delta swing क्रम mix mode घातer tracking*/
			rtl_dbg(rtlpriv, COMP_POWER_TRACKING, DBG_LOUD,
				"******Temp is lower and pDM_Odm->Absolute_OFDMSwingIdx[ODM_RF_PATH_A] = %d\n",
				rtldm->असलolute_ofdm_swing_idx[RF90_PATH_A]);

			rtl_dbg(rtlpriv, COMP_POWER_TRACKING, DBG_LOUD,
				"deltaSwingTableIdx_TDOWN_B[%d] = %d\n",
				delta, delta_swing_table_idx_tकरोwn_b[delta]);

			rtldm->delta_घातer_index_last[RF90_PATH_B] =
				rtldm->delta_घातer_index[RF90_PATH_B];
			rtldm->delta_घातer_index[RF90_PATH_B] =
				-1 * delta_swing_table_idx_tकरोwn_b[delta];

			rtldm->असलolute_ofdm_swing_idx[RF90_PATH_B] =
				-1 * delta_swing_table_idx_tकरोwn_b[delta];
			/*Record delta swing क्रम mix mode घातer tracking*/

			rtl_dbg(rtlpriv, COMP_POWER_TRACKING, DBG_LOUD,
				"******Temp is lower and pDM_Odm->Absolute_OFDMSwingIdx[ODM_RF_PATH_B] = %d\n",
				rtldm->असलolute_ofdm_swing_idx[RF90_PATH_B]);
		पूर्ण

		क्रम (p = RF90_PATH_A; p < MAX_PATH_NUM_8812A; p++) अणु
			rtl_dbg(rtlpriv, COMP_POWER_TRACKING, DBG_LOUD,
				"============================= [Path-%c]Calculating PowerIndexOffset =============================\n",
				(p == RF90_PATH_A ? 'A' : 'B'));

			अगर (rtldm->delta_घातer_index[p] ==
				rtldm->delta_घातer_index_last[p])
				/*If Thermal value changes but lookup
				table value still the same*/
				rtldm->घातer_index_offset[p] = 0;
			अन्यथा
				rtldm->घातer_index_offset[p] =
					rtldm->delta_घातer_index[p] -
					rtldm->delta_घातer_index_last[p];
				/* Power Index Dअगरf between 2
				 * बार Power Tracking
				 */
			rtl_dbg(rtlpriv, COMP_POWER_TRACKING, DBG_LOUD,
				"[Path-%c] PowerIndexOffset(%d) =DeltaPowerIndex(%d) -DeltaPowerIndexLast(%d)\n",
				(p == RF90_PATH_A ? 'A' : 'B'),
				rtldm->घातer_index_offset[p],
				rtldm->delta_घातer_index[p],
				rtldm->delta_घातer_index_last[p]);

			rtldm->ofdm_index[p] =
					rtldm->swing_idx_ofdm_base[p] +
					rtldm->घातer_index_offset[p];
			rtldm->cck_index =
					rtldm->swing_idx_cck_base +
					rtldm->घातer_index_offset[p];

			rtldm->swing_idx_cck = rtldm->cck_index;
			rtldm->swing_idx_ofdm[p] = rtldm->ofdm_index[p];

			/****Prपूर्णांक BB Swing Base and Index Offset */

			rtl_dbg(rtlpriv, COMP_POWER_TRACKING, DBG_LOUD,
				"The 'CCK' final index(%d) = BaseIndex(%d) + PowerIndexOffset(%d)\n",
				rtldm->swing_idx_cck,
				rtldm->swing_idx_cck_base,
				rtldm->घातer_index_offset[p]);
			rtl_dbg(rtlpriv, COMP_POWER_TRACKING, DBG_LOUD,
				"The 'OFDM' final index(%d) = BaseIndex[%c](%d) + PowerIndexOffset(%d)\n",
				rtldm->swing_idx_ofdm[p],
				(p == RF90_PATH_A ? 'A' : 'B'),
				rtldm->swing_idx_ofdm_base[p],
				rtldm->घातer_index_offset[p]);

			/*7.1 Handle boundary conditions of index.*/

			अगर (rtldm->ofdm_index[p] > TXSCALE_TABLE_SIZE - 1)
				rtldm->ofdm_index[p] = TXSCALE_TABLE_SIZE - 1;
			अन्यथा अगर (rtldm->ofdm_index[p] < ofdm_min_index)
				rtldm->ofdm_index[p] = ofdm_min_index;
		पूर्ण
		rtl_dbg(rtlpriv, COMP_POWER_TRACKING, DBG_LOUD,
			"\n\n====================================================================================\n");
		अगर (rtldm->cck_index > TXSCALE_TABLE_SIZE - 1)
			rtldm->cck_index = TXSCALE_TABLE_SIZE - 1;
		अन्यथा अगर (rtldm->cck_index < 0)
			rtldm->cck_index = 0;
	पूर्ण अन्यथा अणु
		rtl_dbg(rtlpriv, COMP_POWER_TRACKING, DBG_LOUD,
			"The thermal meter is unchanged or TxPowerTracking OFF(%d): ThermalValue: %d , pDM_Odm->RFCalibrateInfo.ThermalValue: %d\n",
			rtldm->txघातer_track_control,
			thermal_value,
			rtldm->thermalvalue);

		क्रम (p = RF90_PATH_A; p < MAX_PATH_NUM_8812A; p++)
			rtldm->घातer_index_offset[p] = 0;
	पूर्ण
	/*Prपूर्णांक Swing base & current*/
	rtl_dbg(rtlpriv, COMP_POWER_TRACKING, DBG_LOUD,
		"TxPowerTracking: [CCK] Swing Current Index: %d,Swing Base Index: %d\n",
		rtldm->cck_index, rtldm->swing_idx_cck_base);
	क्रम (p = RF90_PATH_A; p < MAX_PATH_NUM_8812A; p++) अणु
		rtl_dbg(rtlpriv, COMP_POWER_TRACKING, DBG_LOUD,
			"TxPowerTracking: [OFDM] Swing Current Index: %d,Swing Base Index[%c]: %d\n",
			rtldm->ofdm_index[p],
			(p == RF90_PATH_A ? 'A' : 'B'),
			rtldm->swing_idx_ofdm_base[p]);
	पूर्ण

	अगर ((rtldm->घातer_index_offset[RF90_PATH_A] != 0 ||
		rtldm->घातer_index_offset[RF90_PATH_B] != 0) &&
		rtldm->txघातer_track_control) अणु
		/*7.2 Configure the Swing Table to adjust Tx Power.
		 *Always TRUE after Tx Power is adjusted by घातer tracking.
		 *
		 *2012/04/23 MH According to Luke's suggestion,
		 *we can not ग_लिखो BB digital
		 *to increase TX घातer. Otherwise, EVM will be bad.
		 *
		 *2012/04/25 MH Add क्रम tx घातer tracking to set
		 *tx घातer in tx agc क्रम 88E.
		 */
		अगर (thermal_value > rtldm->thermalvalue) अणु
			rtl_dbg(rtlpriv, COMP_POWER_TRACKING, DBG_LOUD,
				"Temperature Increasing(A): delta_pi: %d , delta_t: %d, Now_t: %d,EFUSE_t: %d, Last_t: %d\n",
				rtldm->घातer_index_offset[RF90_PATH_A],
				delta, thermal_value,
				rtlefuse->eeprom_thermalmeter,
				rtldm->thermalvalue);

			rtl_dbg(rtlpriv, COMP_POWER_TRACKING, DBG_LOUD,
				"Temperature Increasing(B): delta_pi: %d ,delta_t: %d, Now_t: %d, EFUSE_t: %d, Last_t: %d\n",
				rtldm->घातer_index_offset[RF90_PATH_B],
				delta, thermal_value,
				rtlefuse->eeprom_thermalmeter,
				rtldm->thermalvalue);
		पूर्ण अन्यथा अगर (thermal_value < rtldm->thermalvalue) अणु /*Low temperature*/
			rtl_dbg(rtlpriv, COMP_POWER_TRACKING, DBG_LOUD,
				"Temperature Decreasing(A): delta_pi: %d , delta_t: %d, Now_t: %d, EFUSE_t: %d, Last_t: %d\n",
				rtldm->घातer_index_offset[RF90_PATH_A],
				delta, thermal_value,
				rtlefuse->eeprom_thermalmeter,
				rtldm->thermalvalue);

			rtl_dbg(rtlpriv, COMP_POWER_TRACKING, DBG_LOUD,
				"Temperature Decreasing(B): delta_pi: %d , delta_t: %d, Now_t: %d, EFUSE_t: %d, Last_t: %d\n",
				rtldm->घातer_index_offset[RF90_PATH_B],
				delta, thermal_value,
				rtlefuse->eeprom_thermalmeter,
				rtldm->thermalvalue);
		पूर्ण

		अगर (thermal_value > rtlefuse->eeprom_thermalmeter) अणु
			rtl_dbg(rtlpriv, COMP_POWER_TRACKING, DBG_LOUD,
				"Temperature(%d) higher than PG value(%d)\n",
				thermal_value, rtlefuse->eeprom_thermalmeter);

			rtl_dbg(rtlpriv, COMP_POWER_TRACKING, DBG_LOUD,
				"**********Enter POWER Tracking MIX_MODE**********\n");
			क्रम (p = RF90_PATH_A; p < MAX_PATH_NUM_8812A; p++)
				rtl8812ae_dm_txpwr_track_set_pwr(hw, MIX_MODE,
								 p, 0);
		पूर्ण अन्यथा अणु
			rtl_dbg(rtlpriv, COMP_POWER_TRACKING, DBG_LOUD,
				"Temperature(%d) lower than PG value(%d)\n",
				thermal_value, rtlefuse->eeprom_thermalmeter);

			rtl_dbg(rtlpriv, COMP_POWER_TRACKING, DBG_LOUD,
				"**********Enter POWER Tracking MIX_MODE**********\n");
			क्रम (p = RF90_PATH_A; p < MAX_PATH_NUM_8812A; p++)
				rtl8812ae_dm_txpwr_track_set_pwr(hw, MIX_MODE,
								 p, index_क्रम_channel);
		पूर्ण
		/*Record last समय Power Tracking result as base.*/
		rtldm->swing_idx_cck_base = rtldm->swing_idx_cck;
		क्रम (p = RF90_PATH_A; p < MAX_PATH_NUM_8812A; p++)
				rtldm->swing_idx_ofdm_base[p] =
					rtldm->swing_idx_ofdm[p];

		rtl_dbg(rtlpriv, COMP_POWER_TRACKING, DBG_LOUD,
			"pDM_Odm->RFCalibrateInfo.ThermalValue =%d ThermalValue= %d\n",
			rtldm->thermalvalue, thermal_value);
		/*Record last Power Tracking Thermal Value*/
		rtldm->thermalvalue = thermal_value;
	पूर्ण
	/*Delta temperature is equal to or larger than
	20 centigrade (When threshold is 8).*/
	अगर (delta_iqk >= IQK_THRESHOLD)
		rtl8812ae_करो_iqk(hw, delta_iqk, thermal_value, 8);

	rtl_dbg(rtlpriv, COMP_POWER_TRACKING, DBG_LOUD,
		"<===%s\n", __func__);
पूर्ण

अटल व्योम rtl8821ae_get_delta_swing_table(काष्ठा ieee80211_hw *hw,
					    स्थिर u8 **up_a,
					    स्थिर u8 **करोwn_a)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	काष्ठा rtl_phy *rtlphy = &rtlpriv->phy;
	काष्ठा rtl_dm *rtldm = rtl_dm(rtl_priv(hw));
	u8 channel = rtlphy->current_channel;
	u8 rate = rtldm->tx_rate;

	अगर (1 <= channel && channel <= 14) अणु
		अगर (RTL8821AE_RX_HAL_IS_CCK_RATE(rate)) अणु
			*up_a = rtl8821ae_delta_swing_table_idx_24gccka_p;
			*करोwn_a = rtl8821ae_delta_swing_table_idx_24gccka_n;
		पूर्ण अन्यथा अणु
			*up_a = rtl8821ae_delta_swing_table_idx_24ga_p;
			*करोwn_a = rtl8821ae_delta_swing_table_idx_24ga_n;
		पूर्ण
	पूर्ण अन्यथा अगर (36 <= channel && channel <= 64) अणु
		*up_a = rtl8821ae_delta_swing_table_idx_5ga_p[0];
		*करोwn_a = rtl8821ae_delta_swing_table_idx_5ga_n[0];
	पूर्ण अन्यथा अगर (100 <= channel && channel <= 140) अणु
		*up_a = rtl8821ae_delta_swing_table_idx_5ga_p[1];
		*करोwn_a = rtl8821ae_delta_swing_table_idx_5ga_n[1];
	पूर्ण अन्यथा अगर (149 <= channel && channel <= 173) अणु
		*up_a = rtl8821ae_delta_swing_table_idx_5ga_p[2];
		*करोwn_a = rtl8821ae_delta_swing_table_idx_5ga_n[2];
	पूर्ण अन्यथा अणु
		*up_a = rtl8818e_delta_swing_table_idx_24gb_p;
		*करोwn_a = rtl8818e_delta_swing_table_idx_24gb_n;
	पूर्ण
	वापस;
पूर्ण

/*-----------------------------------------------------------------------------
 * Function:	odm_TxPwrTrackSetPwr88E()
 *
 * Overview:	88E change all channel tx घातer accordign to flag.
 *				OFDM & CCK are all dअगरferent.
 *
 * Input:		NONE
 *
 * Output:		NONE
 *
 * Return:		NONE
 *
 * Revised History:
 *	When		Who		Remark
 *	04/23/2012	MHC		Create Version 0.
 *
 *---------------------------------------------------------------------------
 */
व्योम rtl8821ae_dm_txpwr_track_set_pwr(काष्ठा ieee80211_hw *hw,
				      क्रमागत pwr_track_control_method method,
				      u8 rf_path, u8 channel_mapped_index)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	काष्ठा rtl_dm	*rtldm = rtl_dm(rtl_priv(hw));
	काष्ठा rtl_phy *rtlphy = &rtlpriv->phy;
	u32 final_swing_idx[1];
	u8 pwr_tracking_limit = 26; /*+1.0dB*/
	u8 tx_rate = 0xFF;
	s8 final_ofdm_swing_index = 0;

	अगर (rtldm->tx_rate != 0xFF)
		tx_rate = rtl8821ae_hw_rate_to_mrate(hw, rtldm->tx_rate);

	rtl_dbg(rtlpriv, COMP_POWER_TRACKING, DBG_LOUD, "===>%s\n", __func__);

	अगर (tx_rate != 0xFF) अणु /* Mimic Modअगरy High Rate BBSwing Limit.*/
		/*CCK*/
		अगर ((tx_rate >= MGN_1M) && (tx_rate <= MGN_11M))
			pwr_tracking_limit = 32; /*+4dB*/
		/*OFDM*/
		अन्यथा अगर ((tx_rate >= MGN_6M) && (tx_rate <= MGN_48M))
			pwr_tracking_limit = 30; /*+3dB*/
		अन्यथा अगर (tx_rate == MGN_54M)
			pwr_tracking_limit = 28; /*+2dB*/
		/*HT*/
		/*QPSK/BPSK*/
		अन्यथा अगर ((tx_rate >= MGN_MCS0) && (tx_rate <= MGN_MCS2))
			pwr_tracking_limit = 34; /*+5dB*/
		/*16QAM*/
		अन्यथा अगर ((tx_rate >= MGN_MCS3) && (tx_rate <= MGN_MCS4))
			pwr_tracking_limit = 30; /*+3dB*/
		/*64QAM*/
		अन्यथा अगर ((tx_rate >= MGN_MCS5) && (tx_rate <= MGN_MCS7))
			pwr_tracking_limit = 28; /*+2dB*/
		/*2 VHT*/
		/*QPSK/BPSK*/
		अन्यथा अगर ((tx_rate >= MGN_VHT1SS_MCS0) &&
			(tx_rate <= MGN_VHT1SS_MCS2))
			pwr_tracking_limit = 34; /*+5dB*/
		/*16QAM*/
		अन्यथा अगर ((tx_rate >= MGN_VHT1SS_MCS3) &&
			(tx_rate <= MGN_VHT1SS_MCS4))
			pwr_tracking_limit = 30; /*+3dB*/
		/*64QAM*/
		अन्यथा अगर ((tx_rate >= MGN_VHT1SS_MCS5) &&
			(tx_rate <= MGN_VHT1SS_MCS6))
			pwr_tracking_limit = 28; /*+2dB*/
		अन्यथा अगर (tx_rate == MGN_VHT1SS_MCS7) /*64QAM*/
			pwr_tracking_limit = 26; /*+1dB*/
		अन्यथा अगर (tx_rate == MGN_VHT1SS_MCS8) /*256QAM*/
			pwr_tracking_limit = 24; /*+0dB*/
		अन्यथा अगर (tx_rate == MGN_VHT1SS_MCS9) /*256QAM*/
			pwr_tracking_limit = 22; /*-1dB*/
		अन्यथा
			pwr_tracking_limit = 24;
	पूर्ण
	rtl_dbg(rtlpriv, COMP_POWER_TRACKING, DBG_LOUD,
		"TxRate=0x%x, PwrTrackingLimit=%d\n",
		tx_rate, pwr_tracking_limit);

	अगर (method == BBSWING) अणु
		rtl_dbg(rtlpriv, COMP_POWER_TRACKING, DBG_LOUD,
			"===>%s\n", __func__);
		अगर (rf_path == RF90_PATH_A) अणु
			final_swing_idx[RF90_PATH_A] =
				(rtldm->ofdm_index[RF90_PATH_A] >
				pwr_tracking_limit) ?
				pwr_tracking_limit :
				rtldm->ofdm_index[RF90_PATH_A];
			rtl_dbg(rtlpriv, COMP_POWER_TRACKING, DBG_LOUD,
				"pDM_Odm->RFCalibrateInfo.OFDM_index[ODM_RF_PATH_A]=%d,pDM_Odm->RealBbSwingIdx[ODM_RF_PATH_A]=%d\n",
				rtldm->ofdm_index[RF90_PATH_A],
				final_swing_idx[RF90_PATH_A]);

			rtl_set_bbreg(hw, RA_TXSCALE, 0xFFE00000,
				txscaling_tbl[final_swing_idx[RF90_PATH_A]]);
		पूर्ण
	पूर्ण अन्यथा अगर (method == MIX_MODE) अणु
		rtl_dbg(rtlpriv, COMP_POWER_TRACKING, DBG_LOUD,
			"pDM_Odm->DefaultOfdmIndex=%d,pDM_Odm->Absolute_OFDMSwingIdx[RFPath]=%d, RF_Path = %d\n",
			rtldm->शेष_ofdm_index,
			rtldm->असलolute_ofdm_swing_idx[rf_path],
			rf_path);

		final_ofdm_swing_index =
			rtldm->शेष_ofdm_index +
			rtldm->असलolute_ofdm_swing_idx[rf_path];
		/*BBSwing higher then Limit*/
		अगर (rf_path == RF90_PATH_A) अणु
			अगर (final_ofdm_swing_index > pwr_tracking_limit) अणु
				rtldm->remnant_cck_idx =
					final_ofdm_swing_index -
					pwr_tracking_limit;
				/* CCK Follow the same compensate value as Path A*/
				rtldm->remnant_ofdm_swing_idx[rf_path] =
					final_ofdm_swing_index -
					pwr_tracking_limit;

				rtl_set_bbreg(hw, RA_TXSCALE,
					0xFFE00000,
					txscaling_tbl[pwr_tracking_limit]);

				rtldm->modअगरy_txagc_flag_path_a = true;

				/*Set TxAGC Page Cअणुपूर्ण;*/
				rtl8821ae_phy_set_txघातer_level_by_path(hw,
					rtlphy->current_channel,
					RF90_PATH_A);

				rtl_dbg(rtlpriv, COMP_POWER_TRACKING, DBG_LOUD,
					" ******Path_A Over BBSwing Limit , PwrTrackingLimit = %d , Remnant TxAGC Value = %d\n",
					pwr_tracking_limit,
					rtldm->remnant_ofdm_swing_idx[rf_path]);
			पूर्ण अन्यथा अगर (final_ofdm_swing_index < 0) अणु
				rtldm->remnant_cck_idx = final_ofdm_swing_index;
				/* CCK Follow the same compensate value as Path A*/
				rtldm->remnant_ofdm_swing_idx[rf_path] =
					final_ofdm_swing_index;

				rtl_set_bbreg(hw, RA_TXSCALE, 0xFFE00000,
					txscaling_tbl[0]);

				rtldm->modअगरy_txagc_flag_path_a = true;

				/*Set TxAGC Page Cअणुपूर्ण;*/
				rtl8821ae_phy_set_txघातer_level_by_path(hw,
					rtlphy->current_channel, RF90_PATH_A);

				rtl_dbg(rtlpriv, COMP_POWER_TRACKING, DBG_LOUD,
					"******Path_A Lower then BBSwing lower bound  0 , Remnant TxAGC Value = %d\n",
					rtldm->remnant_ofdm_swing_idx[rf_path]);
			पूर्ण अन्यथा अणु
				rtl_set_bbreg(hw, RA_TXSCALE, 0xFFE00000,
					txscaling_tbl[(u8)final_ofdm_swing_index]);

				rtl_dbg(rtlpriv, COMP_POWER_TRACKING, DBG_LOUD,
					"******Path_A Compensate with BBSwing ,Final_OFDM_Swing_Index = %d\n",
					final_ofdm_swing_index);
				/*If TxAGC has changed, reset TxAGC again*/
				अगर (rtldm->modअगरy_txagc_flag_path_a) अणु
					rtldm->remnant_cck_idx = 0;
					rtldm->remnant_ofdm_swing_idx[rf_path] = 0;

					/*Set TxAGC Page Cअणुपूर्ण;*/
					rtl8821ae_phy_set_txघातer_level_by_path(hw,
						rtlphy->current_channel, RF90_PATH_A);

					rtldm->modअगरy_txagc_flag_path_a = false;

					rtl_dbg(rtlpriv, COMP_POWER_TRACKING,
						DBG_LOUD,
						"******Path_A pDM_Odm->Modify_TxAGC_Flag= FALSE\n");
				पूर्ण
			पूर्ण
		पूर्ण
	पूर्ण अन्यथा अणु
		वापस;
	पूर्ण
पूर्ण

व्योम rtl8821ae_dm_txघातer_tracking_callback_thermalmeter(
	काष्ठा ieee80211_hw *hw)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	काष्ठा rtl_efuse *rtlefuse = rtl_efuse(rtl_priv(hw));
	काष्ठा rtl_dm	*rtldm = rtl_dm(rtl_priv(hw));
	काष्ठा rtl_hal *rtlhal = rtl_hal(rtl_priv(hw));
	काष्ठा rtl_phy *rtlphy = &rtlpriv->phy;

	u8 thermal_value = 0, delta, delta_lck, delta_iqk, p = 0, i = 0;
	u8 thermal_value_avg_count = 0;
	u32 thermal_value_avg = 0;

	u8 ofdm_min_index = 6;  /*OFDM BB Swing should be less than +3.0dB */
	/* GetRightChnlPlaceक्रमIQK(pHalData->CurrentChannel)*/
	u8 index_क्रम_channel = 0;

	/* 1. The following TWO tables decide the final
	 * index of OFDM/CCK swing table.
	 */
	स्थिर u8 *delta_swing_table_idx_tup_a;
	स्थिर u8 *delta_swing_table_idx_tकरोwn_a;

	/*2. Initilization ( 7 steps in total )*/
	rtl8821ae_get_delta_swing_table(hw,
					&delta_swing_table_idx_tup_a,
					&delta_swing_table_idx_tकरोwn_a);

	rtldm->txघातer_trackinginit = true;

	rtl_dbg(rtlpriv, COMP_POWER_TRACKING, DBG_LOUD,
		"===>%s,\n pDM_Odm->BbSwingIdxCckBase: %d,pDM_Odm->BbSwingIdxOfdmBase[A]:%d, pDM_Odm->DefaultOfdmIndex: %d\n",
		__func__,
		rtldm->swing_idx_cck_base,
		rtldm->swing_idx_ofdm_base[RF90_PATH_A],
		rtldm->शेष_ofdm_index);
	/*0x42: RF Reg[15:10] 88E*/
	thermal_value = (u8)rtl_get_rfreg(hw,
		RF90_PATH_A, RF_T_METER_8812A, 0xfc00);
	अगर (!rtldm->txघातer_track_control ||
		rtlefuse->eeprom_thermalmeter == 0 ||
		rtlefuse->eeprom_thermalmeter == 0xFF)
		वापस;

	/* 3. Initialize ThermalValues of RFCalibrateInfo*/

	अगर (rtlhal->reloadtxघातerindex) अणु
		rtl_dbg(rtlpriv, COMP_POWER_TRACKING, DBG_LOUD,
			"reload ofdm index for band switch\n");
	पूर्ण

	/*4. Calculate average thermal meter*/
	rtldm->thermalvalue_avg[rtldm->thermalvalue_avg_index] = thermal_value;
	rtldm->thermalvalue_avg_index++;
	अगर (rtldm->thermalvalue_avg_index == AVG_THERMAL_NUM_8812A)
		/*Average बार =  c.AverageThermalNum*/
		rtldm->thermalvalue_avg_index = 0;

	क्रम (i = 0; i < AVG_THERMAL_NUM_8812A; i++) अणु
		अगर (rtldm->thermalvalue_avg[i]) अणु
			thermal_value_avg += rtldm->thermalvalue_avg[i];
			thermal_value_avg_count++;
		पूर्ण
	पूर्ण
	/*Calculate Average ThermalValue after average enough बार*/
	अगर (thermal_value_avg_count) अणु
		thermal_value = (u8)(thermal_value_avg /
				thermal_value_avg_count);
		rtl_dbg(rtlpriv, COMP_POWER_TRACKING, DBG_LOUD,
			"AVG Thermal Meter = 0x%X, EFUSE Thermal Base = 0x%X\n",
			thermal_value, rtlefuse->eeprom_thermalmeter);
	पूर्ण

	/*5. Calculate delta, delta_LCK, delta_IQK.
	 *"delta" here is used to determine whether
	 * thermal value changes or not.
	 */
	delta = (thermal_value > rtldm->thermalvalue) ?
		(thermal_value - rtldm->thermalvalue) :
		(rtldm->thermalvalue - thermal_value);
	delta_lck = (thermal_value > rtldm->thermalvalue_lck) ?
		(thermal_value - rtldm->thermalvalue_lck) :
		(rtldm->thermalvalue_lck - thermal_value);
	delta_iqk = (thermal_value > rtldm->thermalvalue_iqk) ?
		(thermal_value - rtldm->thermalvalue_iqk) :
		(rtldm->thermalvalue_iqk - thermal_value);

	rtl_dbg(rtlpriv, COMP_POWER_TRACKING, DBG_LOUD,
		"(delta, delta_LCK, delta_IQK) = (%d, %d, %d)\n",
		delta, delta_lck, delta_iqk);

	/* 6. If necessary, करो LCK.	*/
	/*Delta temperature is equal to or larger than 20 centigrade.*/
	अगर (delta_lck >= IQK_THRESHOLD) अणु
		rtl_dbg(rtlpriv, COMP_POWER_TRACKING, DBG_LOUD,
			"delta_LCK(%d) >= Threshold_IQK(%d)\n",
			delta_lck, IQK_THRESHOLD);
		rtldm->thermalvalue_lck = thermal_value;
		rtl8821ae_phy_lc_calibrate(hw);
	पूर्ण

	/*7. If necessary, move the index of swing table to adjust Tx घातer.*/

	अगर (delta > 0 && rtldm->txघातer_track_control) अणु
		/*"delta" here is used to record the
		 * असलolute value of dअगरferrence.
		 */
		delta = thermal_value > rtlefuse->eeprom_thermalmeter ?
			(thermal_value - rtlefuse->eeprom_thermalmeter) :
			(rtlefuse->eeprom_thermalmeter - thermal_value);

		अगर (delta >= TXSCALE_TABLE_SIZE)
			delta = TXSCALE_TABLE_SIZE - 1;

		/*7.1 The Final Power Index = BaseIndex + PowerIndexOffset*/

		अगर (thermal_value > rtlefuse->eeprom_thermalmeter) अणु
			rtl_dbg(rtlpriv, COMP_POWER_TRACKING, DBG_LOUD,
				"delta_swing_table_idx_tup_a[%d] = %d\n",
				delta, delta_swing_table_idx_tup_a[delta]);
			rtldm->delta_घातer_index_last[RF90_PATH_A] =
				rtldm->delta_घातer_index[RF90_PATH_A];
			rtldm->delta_घातer_index[RF90_PATH_A] =
				delta_swing_table_idx_tup_a[delta];

			rtldm->असलolute_ofdm_swing_idx[RF90_PATH_A] =
				delta_swing_table_idx_tup_a[delta];
			/*Record delta swing क्रम mix mode घातer tracking*/

			rtl_dbg(rtlpriv, COMP_POWER_TRACKING, DBG_LOUD,
				"******Temp is higher and pDM_Odm->Absolute_OFDMSwingIdx[ODM_RF_PATH_A] = %d\n",
				rtldm->असलolute_ofdm_swing_idx[RF90_PATH_A]);
		पूर्ण अन्यथा अणु
			rtl_dbg(rtlpriv, COMP_POWER_TRACKING, DBG_LOUD,
				"delta_swing_table_idx_tdown_a[%d] = %d\n",
				delta, delta_swing_table_idx_tकरोwn_a[delta]);

			rtldm->delta_घातer_index_last[RF90_PATH_A] =
				rtldm->delta_घातer_index[RF90_PATH_A];
			rtldm->delta_घातer_index[RF90_PATH_A] =
				-1 * delta_swing_table_idx_tकरोwn_a[delta];

			rtldm->असलolute_ofdm_swing_idx[RF90_PATH_A] =
				-1 * delta_swing_table_idx_tकरोwn_a[delta];
			/* Record delta swing क्रम mix mode घातer tracking*/
			rtl_dbg(rtlpriv, COMP_POWER_TRACKING, DBG_LOUD,
				"******Temp is lower and pDM_Odm->Absolute_OFDMSwingIdx[ODM_RF_PATH_A] = %d\n",
				rtldm->असलolute_ofdm_swing_idx[RF90_PATH_A]);
		पूर्ण

		क्रम (p = RF90_PATH_A; p < MAX_PATH_NUM_8821A; p++) अणु
			rtl_dbg(rtlpriv, COMP_POWER_TRACKING, DBG_LOUD,
				"\n\n================================ [Path-%c]Calculating PowerIndexOffset ================================\n",
				(p == RF90_PATH_A ? 'A' : 'B'));
			/*If Thermal value changes but lookup table value
			 * still the same
			 */
			अगर (rtldm->delta_घातer_index[p] ==
				rtldm->delta_घातer_index_last[p])

				rtldm->घातer_index_offset[p] = 0;
			अन्यथा
				rtldm->घातer_index_offset[p] =
					rtldm->delta_घातer_index[p] -
					rtldm->delta_घातer_index_last[p];
			/*Power Index Dअगरf between 2 बार Power Tracking*/

			rtl_dbg(rtlpriv, COMP_POWER_TRACKING, DBG_LOUD,
				"[Path-%c] PowerIndexOffset(%d) = DeltaPowerIndex(%d) - DeltaPowerIndexLast(%d)\n",
				(p == RF90_PATH_A ? 'A' : 'B'),
				rtldm->घातer_index_offset[p],
				rtldm->delta_घातer_index[p] ,
				rtldm->delta_घातer_index_last[p]);

			rtldm->ofdm_index[p] =
					rtldm->swing_idx_ofdm_base[p] +
					rtldm->घातer_index_offset[p];
			rtldm->cck_index =
					rtldm->swing_idx_cck_base +
					rtldm->घातer_index_offset[p];

			rtldm->swing_idx_cck = rtldm->cck_index;
			rtldm->swing_idx_ofdm[p] = rtldm->ofdm_index[p];

			/*********Prपूर्णांक BB Swing Base and Index Offset********/

			rtl_dbg(rtlpriv, COMP_POWER_TRACKING, DBG_LOUD,
				"The 'CCK' final index(%d) = BaseIndex(%d) + PowerIndexOffset(%d)\n",
				rtldm->swing_idx_cck,
				rtldm->swing_idx_cck_base,
				rtldm->घातer_index_offset[p]);
			rtl_dbg(rtlpriv, COMP_POWER_TRACKING, DBG_LOUD,
				"The 'OFDM' final index(%d) = BaseIndex[%c](%d) + PowerIndexOffset(%d)\n",
				rtldm->swing_idx_ofdm[p],
				(p == RF90_PATH_A ? 'A' : 'B'),
				rtldm->swing_idx_ofdm_base[p],
				rtldm->घातer_index_offset[p]);

			/*7.1 Handle boundary conditions of index.*/

			अगर (rtldm->ofdm_index[p] > TXSCALE_TABLE_SIZE - 1)
				rtldm->ofdm_index[p] = TXSCALE_TABLE_SIZE - 1;
			अन्यथा अगर (rtldm->ofdm_index[p] < ofdm_min_index)
				rtldm->ofdm_index[p] = ofdm_min_index;
		पूर्ण
		rtl_dbg(rtlpriv, COMP_POWER_TRACKING, DBG_LOUD,
			"\n\n========================================================================================================\n");
		अगर (rtldm->cck_index > TXSCALE_TABLE_SIZE - 1)
			rtldm->cck_index = TXSCALE_TABLE_SIZE - 1;
		अन्यथा अगर (rtldm->cck_index < 0)
			rtldm->cck_index = 0;
	पूर्ण अन्यथा अणु
		rtl_dbg(rtlpriv, COMP_POWER_TRACKING, DBG_LOUD,
			"The thermal meter is unchanged or TxPowerTracking OFF(%d):ThermalValue: %d , pDM_Odm->RFCalibrateInfo.ThermalValue: %d\n",
			rtldm->txघातer_track_control,
			thermal_value,
			rtldm->thermalvalue);

		क्रम (p = RF90_PATH_A; p < MAX_PATH_NUM_8821A; p++)
			rtldm->घातer_index_offset[p] = 0;
	पूर्ण
	rtl_dbg(rtlpriv, COMP_POWER_TRACKING, DBG_LOUD,
		"TxPowerTracking: [CCK] Swing Current Index: %d, Swing Base Index: %d\n",
		/*Prपूर्णांक Swing base & current*/
		rtldm->cck_index, rtldm->swing_idx_cck_base);
	क्रम (p = RF90_PATH_A; p < MAX_PATH_NUM_8821A; p++) अणु
		rtl_dbg(rtlpriv, COMP_POWER_TRACKING, DBG_LOUD,
			"TxPowerTracking: [OFDM] Swing Current Index: %d, Swing Base Index[%c]: %d\n",
			rtldm->ofdm_index[p],
			(p == RF90_PATH_A ? 'A' : 'B'),
			rtldm->swing_idx_ofdm_base[p]);
	पूर्ण

	अगर ((rtldm->घातer_index_offset[RF90_PATH_A] != 0 ||
		rtldm->घातer_index_offset[RF90_PATH_B] != 0) &&
		rtldm->txघातer_track_control) अणु
		/*7.2 Configure the Swing Table to adjust Tx Power.*/
		/*Always TRUE after Tx Power is adjusted by घातer tracking.*/
		/*
		 *  2012/04/23 MH According to Luke's suggestion,
		 *  we can not ग_लिखो BB digital
		 *  to increase TX घातer. Otherwise, EVM will be bad.
		 *
		 *  2012/04/25 MH Add क्रम tx घातer tracking to
		 *  set tx घातer in tx agc क्रम 88E.
		 */
		अगर (thermal_value > rtldm->thermalvalue) अणु
			rtl_dbg(rtlpriv, COMP_POWER_TRACKING, DBG_LOUD,
				"Temperature Increasing(A): delta_pi: %d , delta_t: %d,Now_t: %d, EFUSE_t: %d, Last_t: %d\n",
				rtldm->घातer_index_offset[RF90_PATH_A],
				delta, thermal_value,
				rtlefuse->eeprom_thermalmeter,
				rtldm->thermalvalue);
		पूर्ण अन्यथा अगर (thermal_value < rtldm->thermalvalue) अणु /*Low temperature*/
			rtl_dbg(rtlpriv, COMP_POWER_TRACKING, DBG_LOUD,
				"Temperature Decreasing(A): delta_pi: %d , delta_t: %d, Now_t: %d, EFUSE_t: %d, Last_t: %d\n",
				rtldm->घातer_index_offset[RF90_PATH_A],
				delta, thermal_value,
				rtlefuse->eeprom_thermalmeter,
				rtldm->thermalvalue);
		पूर्ण

		अगर (thermal_value > rtlefuse->eeprom_thermalmeter) अणु
			rtl_dbg(rtlpriv, COMP_POWER_TRACKING, DBG_LOUD,
				"Temperature(%d) higher than PG value(%d)\n",
				thermal_value, rtlefuse->eeprom_thermalmeter);

			rtl_dbg(rtlpriv, COMP_POWER_TRACKING, DBG_LOUD,
				"****Enter POWER Tracking MIX_MODE****\n");
			क्रम (p = RF90_PATH_A; p < MAX_PATH_NUM_8821A; p++)
					rtl8821ae_dm_txpwr_track_set_pwr(hw,
						MIX_MODE, p, index_क्रम_channel);
		पूर्ण अन्यथा अणु
			rtl_dbg(rtlpriv, COMP_POWER_TRACKING, DBG_LOUD,
				"Temperature(%d) lower than PG value(%d)\n",
				thermal_value, rtlefuse->eeprom_thermalmeter);

			rtl_dbg(rtlpriv, COMP_POWER_TRACKING, DBG_LOUD,
				"*****Enter POWER Tracking MIX_MODE*****\n");
			क्रम (p = RF90_PATH_A; p < MAX_PATH_NUM_8821A; p++)
				rtl8812ae_dm_txpwr_track_set_pwr(hw,
					MIX_MODE, p, index_क्रम_channel);
		पूर्ण
		/*Record last समय Power Tracking result as base.*/
		rtldm->swing_idx_cck_base = rtldm->swing_idx_cck;
		क्रम (p = RF90_PATH_A; p < MAX_PATH_NUM_8821A; p++)
			rtldm->swing_idx_ofdm_base[p] = rtldm->swing_idx_ofdm[p];

		rtl_dbg(rtlpriv, COMP_POWER_TRACKING, DBG_LOUD,
			"pDM_Odm->RFCalibrateInfo.ThermalValue = %d ThermalValue= %d\n",
			rtldm->thermalvalue, thermal_value);
		/*Record last Power Tracking Thermal Value*/
		rtldm->thermalvalue = thermal_value;
	पूर्ण
	/* Delta temperature is equal to or larger than
	 * 20 centigrade (When threshold is 8).
	 */
	अगर (delta_iqk >= IQK_THRESHOLD) अणु
		अगर (!rtlphy->lck_inprogress) अणु
			spin_lock(&rtlpriv->locks.iqk_lock);
			rtlphy->lck_inprogress = true;
			spin_unlock(&rtlpriv->locks.iqk_lock);

			rtl8821ae_करो_iqk(hw, delta_iqk, thermal_value, 8);

			spin_lock(&rtlpriv->locks.iqk_lock);
			rtlphy->lck_inprogress = false;
			spin_unlock(&rtlpriv->locks.iqk_lock);
		पूर्ण
	पूर्ण

	rtl_dbg(rtlpriv, COMP_POWER_TRACKING, DBG_LOUD, "<===%s\n", __func__);
पूर्ण

व्योम rtl8821ae_dm_check_txघातer_tracking_thermalmeter(काष्ठा ieee80211_hw *hw)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	अगर (!rtlpriv->dm.पंचांग_trigger) अणु
		rtl_set_rfreg(hw, RF90_PATH_A, RF_T_METER_88E, BIT(17)|BIT(16),
			      0x03);
		rtl_dbg(rtlpriv, COMP_POWER_TRACKING, DBG_LOUD,
			"Trigger 8821ae Thermal Meter!!\n");
		rtlpriv->dm.पंचांग_trigger = 1;
		वापस;
	पूर्ण अन्यथा अणु
		rtl_dbg(rtlpriv, COMP_POWER_TRACKING, DBG_LOUD,
			"Schedule TxPowerTracking !!\n");

		rtl8821ae_dm_txघातer_tracking_callback_thermalmeter(hw);
		rtlpriv->dm.पंचांग_trigger = 0;
	पूर्ण
पूर्ण

अटल व्योम rtl8821ae_dm_refresh_rate_adaptive_mask(काष्ठा ieee80211_hw *hw)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	काष्ठा rtl_hal *rtlhal = rtl_hal(rtl_priv(hw));
	काष्ठा rtl_mac *mac = rtl_mac(rtl_priv(hw));
	काष्ठा rate_adaptive *p_ra = &rtlpriv->ra;
	u32 low_rssithresh_क्रम_ra = p_ra->low2high_rssi_thresh_क्रम_ra40m;
	u32 high_rssithresh_क्रम_ra = p_ra->high_rssi_thresh_क्रम_ra;
	u8 go_up_gap = 5;
	काष्ठा ieee80211_sta *sta = शून्य;

	अगर (is_hal_stop(rtlhal)) अणु
		rtl_dbg(rtlpriv, COMP_RATE, DBG_LOUD,
			"driver is going to unload\n");
		वापस;
	पूर्ण

	अगर (!rtlpriv->dm.useramask) अणु
		rtl_dbg(rtlpriv, COMP_RATE, DBG_LOUD,
			"driver does not control rate adaptive mask\n");
		वापस;
	पूर्ण

	अगर (mac->link_state == MAC80211_LINKED &&
		mac->opmode == NL80211_IFTYPE_STATION) अणु
		चयन (p_ra->pre_ratr_state) अणु
		हाल DM_RATR_STA_MIDDLE:
			high_rssithresh_क्रम_ra += go_up_gap;
			अवरोध;
		हाल DM_RATR_STA_LOW:
			high_rssithresh_क्रम_ra += go_up_gap;
			low_rssithresh_क्रम_ra += go_up_gap;
			अवरोध;
		शेष:
			अवरोध;
		पूर्ण

		अगर (rtlpriv->dm.undec_sm_pwdb >
		    (दीर्घ)high_rssithresh_क्रम_ra)
			p_ra->ratr_state = DM_RATR_STA_HIGH;
		अन्यथा अगर (rtlpriv->dm.undec_sm_pwdb >
			 (दीर्घ)low_rssithresh_क्रम_ra)
			p_ra->ratr_state = DM_RATR_STA_MIDDLE;
		अन्यथा
			p_ra->ratr_state = DM_RATR_STA_LOW;

		अगर (p_ra->pre_ratr_state != p_ra->ratr_state) अणु
			rtl_dbg(rtlpriv, COMP_RATE, DBG_LOUD,
				"RSSI = %ld\n",
				rtlpriv->dm.undec_sm_pwdb);
			rtl_dbg(rtlpriv, COMP_RATE, DBG_LOUD,
				"RSSI_LEVEL = %d\n", p_ra->ratr_state);
			rtl_dbg(rtlpriv, COMP_RATE, DBG_LOUD,
				"PreState = %d, CurState = %d\n",
				p_ra->pre_ratr_state, p_ra->ratr_state);

			rcu_पढ़ो_lock();
			sta = rtl_find_sta(hw, mac->bssid);
			अगर (sta)
				rtlpriv->cfg->ops->update_rate_tbl(hw,
						sta, p_ra->ratr_state, true);
			rcu_पढ़ो_unlock();

			p_ra->pre_ratr_state = p_ra->ratr_state;
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम rtl8821ae_dm_refresh_basic_rate_mask(काष्ठा ieee80211_hw *hw)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	काष्ठा dig_t *dm_digtable = &rtlpriv->dm_digtable;
	काष्ठा rtl_mac *mac = &rtlpriv->mac80211;
	अटल u8 stage;
	u8 cur_stage = 0;
	u16 basic_rate = RRSR_1M | RRSR_2M | RRSR_5_5M | RRSR_11M | RRSR_6M;

	अगर (mac->link_state < MAC80211_LINKED)
		cur_stage = 0;
	अन्यथा अगर (dm_digtable->rssi_val_min < 25)
		cur_stage = 1;
	अन्यथा अगर (dm_digtable->rssi_val_min > 30)
		cur_stage = 3;
	अन्यथा
		cur_stage = 2;

	अगर (cur_stage != stage) अणु
		अगर (cur_stage == 1) अणु
			basic_rate &= (!(basic_rate ^ mac->basic_rates));
			rtlpriv->cfg->ops->set_hw_reg(hw,
				HW_VAR_BASIC_RATE, (u8 *)&basic_rate);
		पूर्ण अन्यथा अगर (cur_stage == 3 && (stage == 1 || stage == 2)) अणु
			rtlpriv->cfg->ops->set_hw_reg(hw,
				HW_VAR_BASIC_RATE, (u8 *)&mac->basic_rates);
		पूर्ण
	पूर्ण
	stage = cur_stage;
पूर्ण

अटल व्योम rtl8821ae_dm_edca_choose_traffic_idx(
	काष्ठा ieee80211_hw *hw, u64 cur_tx_bytes,
	u64 cur_rx_bytes, bool b_bias_on_rx,
	bool *pb_is_cur_rdl_state)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);

	अगर (b_bias_on_rx) अणु
		अगर (cur_tx_bytes > (cur_rx_bytes*4)) अणु
			*pb_is_cur_rdl_state = false;
			rtl_dbg(rtlpriv, COMP_TURBO, DBG_LOUD,
				"Uplink Traffic\n");
		पूर्ण अन्यथा अणु
			*pb_is_cur_rdl_state = true;
			rtl_dbg(rtlpriv, COMP_TURBO, DBG_LOUD,
				"Balance Traffic\n");
		पूर्ण
	पूर्ण अन्यथा अणु
		अगर (cur_rx_bytes > (cur_tx_bytes*4)) अणु
			*pb_is_cur_rdl_state = true;
			rtl_dbg(rtlpriv, COMP_TURBO, DBG_LOUD,
				"Downlink	Traffic\n");
		पूर्ण अन्यथा अणु
			*pb_is_cur_rdl_state = false;
			rtl_dbg(rtlpriv, COMP_TURBO, DBG_LOUD,
				"Balance Traffic\n");
		पूर्ण
	पूर्ण
	वापस;
पूर्ण

अटल व्योम rtl8821ae_dm_check_edca_turbo(काष्ठा ieee80211_hw *hw)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	काष्ठा rtl_mac *mac = rtl_mac(rtl_priv(hw));
	काष्ठा rtl_dm *rtldm =  rtl_dm(rtl_priv(hw));

	/*Keep past Tx/Rx packet count क्रम RT-to-RT EDCA turbo.*/
	u64 cur_tx_ok_cnt = 0;
	u64 cur_rx_ok_cnt = 0;
	u32 edca_be_ul = 0x5ea42b;
	u32 edca_be_dl = 0x5ea42b;
	u32 edca_be = 0x5ea42b;
	u8 iot_peer = 0;
	bool *pb_is_cur_rdl_state = शून्य;
	bool b_bias_on_rx = false;
	bool b_edca_turbo_on = false;

	rtl_dbg(rtlpriv, COMP_TURBO, DBG_LOUD,
		"%s=====>\n", __func__);
	rtl_dbg(rtlpriv, COMP_TURBO, DBG_LOUD,
		"Original BE PARAM: 0x%x\n",
		rtl_पढ़ो_dword(rtlpriv, DM_REG_EDCA_BE_11N));

	अगर (rtlpriv->dm.dbginfo.num_non_be_pkt > 0x100)
		rtlpriv->dm.is_any_nonbepkts = true;
	rtlpriv->dm.dbginfo.num_non_be_pkt = 0;

	/*===============================
	 * list paramter क्रम dअगरferent platक्रमm
	 *===============================
	 */
	pb_is_cur_rdl_state = &rtlpriv->dm.is_cur_rdlstate;

	cur_tx_ok_cnt = rtlpriv->stats.txbytesunicast - rtldm->last_tx_ok_cnt;
	cur_rx_ok_cnt = rtlpriv->stats.rxbytesunicast - rtldm->last_rx_ok_cnt;

	rtldm->last_tx_ok_cnt = rtlpriv->stats.txbytesunicast;
	rtldm->last_rx_ok_cnt = rtlpriv->stats.rxbytesunicast;

	iot_peer = rtlpriv->mac80211.venकरोr;
	b_bias_on_rx = false;
	b_edca_turbo_on = ((!rtlpriv->dm.is_any_nonbepkts) &&
			   (!rtlpriv->dm.disable_framebursting)) ?
			   true : false;

	अगर (rtlpriv->rtlhal.hw_type != HARDWARE_TYPE_RTL8812AE) अणु
		अगर ((iot_peer == PEER_CISCO) &&
			(mac->mode == WIRELESS_MODE_N_24G)) अणु
			edca_be_dl = edca_setting_dl[iot_peer];
			edca_be_ul = edca_setting_ul[iot_peer];
		पूर्ण
	पूर्ण

	rtl_dbg(rtlpriv, COMP_TURBO, DBG_LOUD,
		"bIsAnyNonBEPkts : 0x%x  bDisableFrameBursting : 0x%x\n",
		rtlpriv->dm.is_any_nonbepkts,
		rtlpriv->dm.disable_framebursting);

	rtl_dbg(rtlpriv, COMP_TURBO, DBG_LOUD,
		"bEdcaTurboOn : 0x%x bBiasOnRx : 0x%x\n",
		b_edca_turbo_on, b_bias_on_rx);

	अगर (b_edca_turbo_on) अणु
		rtl_dbg(rtlpriv, COMP_TURBO, DBG_LOUD,
			"curTxOkCnt : 0x%llx\n", cur_tx_ok_cnt);
		rtl_dbg(rtlpriv, COMP_TURBO, DBG_LOUD,
			"curRxOkCnt : 0x%llx\n", cur_rx_ok_cnt);
		अगर (b_bias_on_rx)
			rtl8821ae_dm_edca_choose_traffic_idx(hw, cur_tx_ok_cnt,
				cur_rx_ok_cnt, true, pb_is_cur_rdl_state);
		अन्यथा
			rtl8821ae_dm_edca_choose_traffic_idx(hw, cur_tx_ok_cnt,
				cur_rx_ok_cnt, false, pb_is_cur_rdl_state);

		edca_be = (*pb_is_cur_rdl_state) ?  edca_be_dl : edca_be_ul;

		rtl_ग_लिखो_dword(rtlpriv, DM_REG_EDCA_BE_11N, edca_be);

		rtl_dbg(rtlpriv, COMP_TURBO, DBG_LOUD,
			"EDCA Turbo on: EDCA_BE:0x%x\n", edca_be);

		rtlpriv->dm.current_turbo_edca = true;

		rtl_dbg(rtlpriv, COMP_TURBO, DBG_LOUD,
			"EDCA_BE_DL : 0x%x  EDCA_BE_UL : 0x%x  EDCA_BE : 0x%x\n",
			edca_be_dl, edca_be_ul, edca_be);
	पूर्ण अन्यथा अणु
		अगर (rtlpriv->dm.current_turbo_edca) अणु
			u8 पंचांगp = AC0_BE;
			rtlpriv->cfg->ops->set_hw_reg(hw, HW_VAR_AC_PARAM,
						      (u8 *)(&पंचांगp));
		पूर्ण
		rtlpriv->dm.current_turbo_edca = false;
	पूर्ण

	rtlpriv->dm.is_any_nonbepkts = false;
	rtldm->last_tx_ok_cnt = rtlpriv->stats.txbytesunicast;
	rtldm->last_rx_ok_cnt = rtlpriv->stats.rxbytesunicast;
पूर्ण

अटल व्योम rtl8821ae_dm_cck_packet_detection_thresh(काष्ठा ieee80211_hw *hw)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	काष्ठा dig_t *dm_digtable = &rtlpriv->dm_digtable;
	u8 cur_cck_cca_thresh;

	अगर (rtlpriv->mac80211.link_state >= MAC80211_LINKED) अणु
		अगर (dm_digtable->rssi_val_min > 25) अणु
			cur_cck_cca_thresh = 0xcd;
		पूर्ण अन्यथा अगर ((dm_digtable->rssi_val_min <= 25) &&
			   (dm_digtable->rssi_val_min > 10)) अणु
			cur_cck_cca_thresh = 0x83;
		पूर्ण अन्यथा अणु
			अगर (rtlpriv->falsealm_cnt.cnt_cck_fail > 1000)
				cur_cck_cca_thresh = 0x83;
			अन्यथा
				cur_cck_cca_thresh = 0x40;
		पूर्ण
	पूर्ण अन्यथा अणु
		अगर (rtlpriv->falsealm_cnt.cnt_cck_fail > 1000)
			cur_cck_cca_thresh = 0x83;
		अन्यथा
			cur_cck_cca_thresh = 0x40;
	पूर्ण

	अगर (dm_digtable->cur_cck_cca_thres != cur_cck_cca_thresh)
		rtl_ग_लिखो_byte(rtlpriv, ODM_REG_CCK_CCA_11AC,
			       cur_cck_cca_thresh);

	dm_digtable->pre_cck_cca_thres = dm_digtable->cur_cck_cca_thres;
	dm_digtable->cur_cck_cca_thres = cur_cck_cca_thresh;
	rtl_dbg(rtlpriv, COMP_DIG, DBG_TRACE,
		"CCK cca thresh hold =%x\n", dm_digtable->cur_cck_cca_thres);
पूर्ण

अटल व्योम rtl8821ae_dm_dynamic_atc_चयन(काष्ठा ieee80211_hw *hw)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	काष्ठा rtl_dm *rtldm = rtl_dm(rtl_priv(hw));
	u8 crystal_cap;
	u32 packet_count;
	पूर्णांक cfo_khz_a, cfo_khz_b, cfo_ave = 0, adjust_xtal = 0;
	पूर्णांक cfo_ave_dअगरf;

	अगर (rtlpriv->mac80211.link_state < MAC80211_LINKED) अणु
		/*1.Enable ATC*/
		अगर (rtldm->atc_status == ATC_STATUS_OFF) अणु
			rtl_set_bbreg(hw, RFC_AREA, BIT(14), ATC_STATUS_ON);
			rtldm->atc_status = ATC_STATUS_ON;
		पूर्ण

		rtl_dbg(rtlpriv, COMP_DIG, DBG_LOUD, "No link!!\n");
		rtl_dbg(rtlpriv, COMP_DIG, DBG_LOUD,
			"atc_status = %d\n", rtldm->atc_status);

		अगर (rtldm->crystal_cap != rtlpriv->efuse.crystalcap) अणु
			rtldm->crystal_cap = rtlpriv->efuse.crystalcap;
			crystal_cap = rtldm->crystal_cap & 0x3f;
			crystal_cap = crystal_cap & 0x3f;
			अगर (rtlpriv->rtlhal.hw_type == HARDWARE_TYPE_RTL8812AE)
				rtl_set_bbreg(hw, REG_MAC_PHY_CTRL,
					      0x7ff80000, (crystal_cap |
					      (crystal_cap << 6)));
			अन्यथा
				rtl_set_bbreg(hw, REG_MAC_PHY_CTRL,
					      0xfff000, (crystal_cap |
					      (crystal_cap << 6)));
		पूर्ण
		rtl_dbg(rtlpriv, COMP_DIG, DBG_LOUD, "crystal_cap = 0x%x\n",
			rtldm->crystal_cap);
	पूर्ण अन्यथाअणु
		/*1. Calculate CFO क्रम path-A & path-B*/
		cfo_khz_a = (पूर्णांक)(rtldm->cfo_tail[0] * 3125) / 1280;
		cfo_khz_b = (पूर्णांक)(rtldm->cfo_tail[1] * 3125) / 1280;
		packet_count = rtldm->packet_count;

		/*2.No new packet*/
		अगर (packet_count == rtldm->packet_count_pre) अणु
			rtl_dbg(rtlpriv, COMP_DIG, DBG_LOUD,
				"packet counter doesn't change\n");
			वापस;
		पूर्ण

		rtldm->packet_count_pre = packet_count;
		rtl_dbg(rtlpriv, COMP_DIG, DBG_LOUD,
			"packet counter = %d\n",
			rtldm->packet_count);

		/*3.Average CFO*/
		अगर (rtlpriv->phy.rf_type == RF_1T1R)
			cfo_ave = cfo_khz_a;
		अन्यथा
			cfo_ave = (cfo_khz_a + cfo_khz_b) >> 1;

		rtl_dbg(rtlpriv, COMP_DIG, DBG_LOUD,
			"cfo_khz_a = %dkHz, cfo_khz_b = %dkHz, cfo_ave = %dkHz\n",
			cfo_khz_a, cfo_khz_b, cfo_ave);

		/*4.Aव्योम abnormal large CFO*/
		cfo_ave_dअगरf = (rtldm->cfo_ave_pre >= cfo_ave) ?
						(rtldm->cfo_ave_pre - cfo_ave) :
						(cfo_ave - rtldm->cfo_ave_pre);

		अगर (cfo_ave_dअगरf > 20 && !rtldm->large_cfo_hit) अणु
			rtl_dbg(rtlpriv, COMP_DIG, DBG_LOUD,
				"first large CFO hit\n");
			rtldm->large_cfo_hit = true;
			वापस;
		पूर्ण अन्यथा
			rtldm->large_cfo_hit = false;

		rtldm->cfo_ave_pre = cfo_ave;

		/*CFO tracking by adjusting Xtal cap.*/

		/*1.Dynamic Xtal threshold*/
		अगर (cfo_ave >= -rtldm->cfo_threshold &&
			cfo_ave <= rtldm->cfo_threshold &&
			rtldm->is_मुक्तze == 0) अणु
			अगर (rtldm->cfo_threshold == CFO_THRESHOLD_XTAL) अणु
				rtldm->cfo_threshold = CFO_THRESHOLD_XTAL + 10;
				rtldm->is_मुक्तze = 1;
			पूर्ण अन्यथा अणु
				rtldm->cfo_threshold = CFO_THRESHOLD_XTAL;
			पूर्ण
		पूर्ण
		rtl_dbg(rtlpriv, COMP_DIG, DBG_LOUD,
			"Dynamic threshold = %d\n",
			rtldm->cfo_threshold);

		/* 2.Calculate Xtal offset*/
		अगर (cfo_ave > rtldm->cfo_threshold && rtldm->crystal_cap < 0x3f)
			adjust_xtal = ((cfo_ave - CFO_THRESHOLD_XTAL) >> 2) + 1;
		अन्यथा अगर ((cfo_ave < -rtlpriv->dm.cfo_threshold) &&
			 rtlpriv->dm.crystal_cap > 0)
			adjust_xtal = ((cfo_ave + CFO_THRESHOLD_XTAL) >> 2) - 1;
		rtl_dbg(rtlpriv, COMP_DIG, DBG_LOUD,
			"Crystal cap = 0x%x, Crystal cap offset = %d\n",
			rtldm->crystal_cap, adjust_xtal);

		/*3.Adjudt Crystal Cap.*/
		अगर (adjust_xtal != 0) अणु
			rtldm->is_मुक्तze = 0;
			rtldm->crystal_cap += adjust_xtal;

			अगर (rtldm->crystal_cap > 0x3f)
				rtldm->crystal_cap = 0x3f;
			अन्यथा अगर (rtldm->crystal_cap < 0)
				rtldm->crystal_cap = 0;

			crystal_cap = rtldm->crystal_cap & 0x3f;
			crystal_cap = crystal_cap & 0x3f;
			अगर (rtlpriv->rtlhal.hw_type == HARDWARE_TYPE_RTL8812AE)
				rtl_set_bbreg(hw, REG_MAC_PHY_CTRL,
					      0x7ff80000, (crystal_cap |
					      (crystal_cap << 6)));
			अन्यथा
				rtl_set_bbreg(hw, REG_MAC_PHY_CTRL,
					      0xfff000, (crystal_cap |
					      (crystal_cap << 6)));
			rtl_dbg(rtlpriv, COMP_DIG, DBG_LOUD,
				"New crystal cap = 0x%x\n",
				rtldm->crystal_cap);
		पूर्ण
	पूर्ण
पूर्ण

व्योम rtl8821ae_dm_watchकरोg(काष्ठा ieee80211_hw *hw)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	काष्ठा rtl_ps_ctl *ppsc = rtl_psc(rtl_priv(hw));
	काष्ठा rtl_hal *rtlhal = rtl_hal(rtl_priv(hw));
	bool fw_current_inpsmode = false;
	bool fw_ps_awake = true;

	rtlpriv->cfg->ops->get_hw_reg(hw, HW_VAR_FW_PSMODE_STATUS,
				      (u8 *)(&fw_current_inpsmode));

	rtlpriv->cfg->ops->get_hw_reg(hw, HW_VAR_FWLPS_RF_ON,
				      (u8 *)(&fw_ps_awake));

	अगर (ppsc->p2p_ps_info.p2p_ps_mode)
		fw_ps_awake = false;

	spin_lock(&rtlpriv->locks.rf_ps_lock);
	अगर ((ppsc->rfpwr_state == ERFON) &&
	    ((!fw_current_inpsmode) && fw_ps_awake) &&
	    (!ppsc->rfchange_inprogress)) अणु
		rtl8821ae_dm_common_info_self_update(hw);
		rtl8821ae_dm_false_alarm_counter_statistics(hw);
		rtl8821ae_dm_check_rssi_monitor(hw);
		rtl8821ae_dm_dig(hw);
		rtl8821ae_dm_cck_packet_detection_thresh(hw);
		rtl8821ae_dm_refresh_rate_adaptive_mask(hw);
		rtl8821ae_dm_refresh_basic_rate_mask(hw);
		rtl8821ae_dm_check_edca_turbo(hw);
		rtl8821ae_dm_dynamic_atc_चयन(hw);
		अगर (rtlhal->hw_type == HARDWARE_TYPE_RTL8812AE)
			rtl8812ae_dm_check_txघातer_tracking_thermalmeter(hw);
		अन्यथा
			rtl8821ae_dm_check_txघातer_tracking_thermalmeter(hw);
		rtl8821ae_dm_iq_calibrate(hw);
	पूर्ण
	spin_unlock(&rtlpriv->locks.rf_ps_lock);

	rtlpriv->dm.dbginfo.num_qry_beacon_pkt = 0;
	rtl_dbg(rtlpriv, COMP_DIG, DBG_DMESG, "\n");
पूर्ण

व्योम rtl8821ae_dm_set_tx_ant_by_tx_info(काष्ठा ieee80211_hw *hw,
					u8 *pdesc, u32 mac_id)
अणु
	काष्ठा rtl_efuse *rtlefuse = rtl_efuse(rtl_priv(hw));
	काष्ठा rtl_hal *rtlhal = rtl_hal(rtl_priv(hw));
	काष्ठा rtl_dm *rtldm = rtl_dm(rtl_priv(hw));
	काष्ठा fast_ant_training *pfat_table = &rtldm->fat_table;
	__le32 *pdesc32 = (__le32 *)pdesc;

	अगर (rtlhal->hw_type != HARDWARE_TYPE_RTL8812AE)
		वापस;

	अगर (rtlefuse->antenna_भाग_प्रकारype == CG_TRX_HW_ANTDIV)
		set_tx_desc_tx_ant(pdesc32, pfat_table->antsel_a[mac_id]);
पूर्ण
