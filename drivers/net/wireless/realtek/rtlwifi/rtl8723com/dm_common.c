<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/* Copyright(c) 2009-2014  Realtek Corporation.*/

#समावेश "../wifi.h"
#समावेश "dm_common.h"
#समावेश "../rtl8723ae/dm.h"
#समावेश <linux/module.h>

/* These routines are common to RTL8723AE and RTL8723bE */

व्योम rtl8723_dm_init_dynamic_txघातer(काष्ठा ieee80211_hw *hw)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);

	rtlpriv->dm.dynamic_txघातer_enable = false;

	rtlpriv->dm.last_dtp_lvl = TXHIGHPWRLEVEL_NORMAL;
	rtlpriv->dm.dynamic_txhighघातer_lvl = TXHIGHPWRLEVEL_NORMAL;
पूर्ण
EXPORT_SYMBOL_GPL(rtl8723_dm_init_dynamic_txघातer);

व्योम rtl8723_dm_init_edca_turbo(काष्ठा ieee80211_hw *hw)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	rtlpriv->dm.current_turbo_edca = false;
	rtlpriv->dm.is_any_nonbepkts = false;
	rtlpriv->dm.is_cur_rdlstate = false;
पूर्ण
EXPORT_SYMBOL_GPL(rtl8723_dm_init_edca_turbo);

व्योम rtl8723_dm_init_dynamic_bb_घातersaving(काष्ठा ieee80211_hw *hw)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	काष्ठा ps_t *dm_pstable = &rtlpriv->dm_pstable;

	dm_pstable->pre_ccastate = CCA_MAX;
	dm_pstable->cur_ccasate = CCA_MAX;
	dm_pstable->pre_rख_स्थितिe = RF_MAX;
	dm_pstable->cur_rख_स्थितिe = RF_MAX;
	dm_pstable->rssi_val_min = 0;
	dm_pstable->initialize = 0;
पूर्ण
EXPORT_SYMBOL_GPL(rtl8723_dm_init_dynamic_bb_घातersaving);
