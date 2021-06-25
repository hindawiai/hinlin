<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/* Copyright(c) 2009-2012  Realtek Corporation.*/

#समावेश "../wifi.h"
#समावेश "../base.h"
#समावेश "reg.h"
#समावेश "def.h"
#समावेश "phy.h"
#समावेश "dm.h"

व्योम rtl92cu_dm_dynamic_txघातer(काष्ठा ieee80211_hw *hw)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	काष्ठा rtl_phy *rtlphy = &(rtlpriv->phy);
	काष्ठा rtl_mac *mac = rtl_mac(rtl_priv(hw));
	दीर्घ undec_sm_pwdb;

	अगर (!rtlpriv->dm.dynamic_txघातer_enable)
		वापस;

	अगर (rtlpriv->dm.dm_flag & HAL_DM_HIPWR_DISABLE) अणु
		rtlpriv->dm.dynamic_txhighघातer_lvl = TXHIGHPWRLEVEL_NORMAL;
		वापस;
	पूर्ण

	अगर ((mac->link_state < MAC80211_LINKED) &&
	    (rtlpriv->dm.entry_min_undec_sm_pwdb == 0)) अणु
		rtl_dbg(rtlpriv, COMP_POWER, DBG_TRACE,
			"Not connected to any\n");

		rtlpriv->dm.dynamic_txhighघातer_lvl = TXHIGHPWRLEVEL_NORMAL;

		rtlpriv->dm.last_dtp_lvl = TXHIGHPWRLEVEL_NORMAL;
		वापस;
	पूर्ण

	अगर (mac->link_state >= MAC80211_LINKED) अणु
		अगर (mac->opmode == NL80211_IFTYPE_ADHOC) अणु
			undec_sm_pwdb = rtlpriv->dm.entry_min_undec_sm_pwdb;
			rtl_dbg(rtlpriv, COMP_POWER, DBG_LOUD,
				"AP Client PWDB = 0x%lx\n",
				undec_sm_pwdb);
		पूर्ण अन्यथा अणु
			undec_sm_pwdb = rtlpriv->dm.undec_sm_pwdb;
			rtl_dbg(rtlpriv, COMP_POWER, DBG_LOUD,
				"STA Default Port PWDB = 0x%lx\n",
				undec_sm_pwdb);
		पूर्ण
	पूर्ण अन्यथा अणु
		undec_sm_pwdb = rtlpriv->dm.entry_min_undec_sm_pwdb;

		rtl_dbg(rtlpriv, COMP_POWER, DBG_LOUD,
			"AP Ext Port PWDB = 0x%lx\n",
			undec_sm_pwdb);
	पूर्ण

	अगर (undec_sm_pwdb >= TX_POWER_NEAR_FIELD_THRESH_LVL2) अणु
		rtlpriv->dm.dynamic_txhighघातer_lvl = TXHIGHPWRLEVEL_LEVEL1;
		rtl_dbg(rtlpriv, COMP_POWER, DBG_LOUD,
			"TXHIGHPWRLEVEL_LEVEL1 (TxPwr=0x0)\n");
	पूर्ण अन्यथा अगर ((undec_sm_pwdb < (TX_POWER_NEAR_FIELD_THRESH_LVL2 - 3)) &&
		   (undec_sm_pwdb >= TX_POWER_NEAR_FIELD_THRESH_LVL1)) अणु

		rtlpriv->dm.dynamic_txhighघातer_lvl = TXHIGHPWRLEVEL_LEVEL1;
		rtl_dbg(rtlpriv, COMP_POWER, DBG_LOUD,
			"TXHIGHPWRLEVEL_LEVEL1 (TxPwr=0x10)\n");
	पूर्ण अन्यथा अगर (undec_sm_pwdb < (TX_POWER_NEAR_FIELD_THRESH_LVL1 - 5)) अणु
		rtlpriv->dm.dynamic_txhighघातer_lvl = TXHIGHPWRLEVEL_NORMAL;
		rtl_dbg(rtlpriv, COMP_POWER, DBG_LOUD,
			"TXHIGHPWRLEVEL_NORMAL\n");
	पूर्ण

	अगर ((rtlpriv->dm.dynamic_txhighघातer_lvl != rtlpriv->dm.last_dtp_lvl)) अणु
		rtl_dbg(rtlpriv, COMP_POWER, DBG_LOUD,
			"PHY_SetTxPowerLevel8192S() Channel = %d\n",
			 rtlphy->current_channel);
		rtl92c_phy_set_txघातer_level(hw, rtlphy->current_channel);
		अगर (rtlpriv->dm.dynamic_txhighघातer_lvl ==
		    TXHIGHPWRLEVEL_NORMAL)
			dm_restoreघातerindex(hw);
		अन्यथा अगर (rtlpriv->dm.dynamic_txhighघातer_lvl ==
			 TXHIGHPWRLEVEL_LEVEL1)
			dm_ग_लिखोघातerindex(hw, 0x14);
		अन्यथा अगर (rtlpriv->dm.dynamic_txhighघातer_lvl ==
			 TXHIGHPWRLEVEL_LEVEL2)
			dm_ग_लिखोघातerindex(hw, 0x10);
	पूर्ण

	rtlpriv->dm.last_dtp_lvl = rtlpriv->dm.dynamic_txhighघातer_lvl;
पूर्ण
