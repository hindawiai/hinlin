<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/* Copyright(c) 2009-2014  Realtek Corporation.*/

#समावेश "../wifi.h"
#समावेश "reg.h"
#समावेश "def.h"
#समावेश "phy.h"
#समावेश "rf.h"
#समावेश "dm.h"

अटल bool _rtl92ee_phy_rf6052_config_parafile(काष्ठा ieee80211_hw *hw);

व्योम rtl92ee_phy_rf6052_set_bandwidth(काष्ठा ieee80211_hw *hw, u8 bandwidth)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	काष्ठा rtl_phy *rtlphy = &rtlpriv->phy;

	चयन (bandwidth) अणु
	हाल HT_CHANNEL_WIDTH_20:
		rtlphy->rfreg_chnlval[0] = ((rtlphy->rfreg_chnlval[0] &
					     0xfffff3ff) | BIT(10) | BIT(11));
		rtl_set_rfreg(hw, RF90_PATH_A, RF_CHNLBW, RFREG_OFFSET_MASK,
			      rtlphy->rfreg_chnlval[0]);
		rtl_set_rfreg(hw, RF90_PATH_B, RF_CHNLBW, RFREG_OFFSET_MASK,
			      rtlphy->rfreg_chnlval[0]);
		अवरोध;
	हाल HT_CHANNEL_WIDTH_20_40:
		rtlphy->rfreg_chnlval[0] = ((rtlphy->rfreg_chnlval[0] &
					     0xfffff3ff) | BIT(10));
		rtl_set_rfreg(hw, RF90_PATH_A, RF_CHNLBW, RFREG_OFFSET_MASK,
			      rtlphy->rfreg_chnlval[0]);
		rtl_set_rfreg(hw, RF90_PATH_B, RF_CHNLBW, RFREG_OFFSET_MASK,
			      rtlphy->rfreg_chnlval[0]);
		अवरोध;
	शेष:
		pr_err("unknown bandwidth: %#X\n", bandwidth);
		अवरोध;
	पूर्ण
पूर्ण

bool rtl92ee_phy_rf6052_config(काष्ठा ieee80211_hw *hw)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	काष्ठा rtl_phy *rtlphy = &rtlpriv->phy;

	अगर (rtlphy->rf_type == RF_1T1R)
		rtlphy->num_total_rfpath = 1;
	अन्यथा
		rtlphy->num_total_rfpath = 2;

	वापस _rtl92ee_phy_rf6052_config_parafile(hw);
पूर्ण

अटल bool _rtl92ee_phy_rf6052_config_parafile(काष्ठा ieee80211_hw *hw)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	काष्ठा rtl_phy *rtlphy = &rtlpriv->phy;
	u32 u4_regvalue = 0;
	u8 rfpath;
	bool rtstatus = true;
	काष्ठा bb_reg_def *pphyreg;

	क्रम (rfpath = 0; rfpath < rtlphy->num_total_rfpath; rfpath++) अणु
		pphyreg = &rtlphy->phyreg_def[rfpath];

		चयन (rfpath) अणु
		हाल RF90_PATH_A:
		हाल RF90_PATH_C:
			u4_regvalue = rtl_get_bbreg(hw, pphyreg->rfपूर्णांकfs,
						    BRFSI_RFENV);
			अवरोध;
		हाल RF90_PATH_B:
		हाल RF90_PATH_D:
			u4_regvalue = rtl_get_bbreg(hw, pphyreg->rfपूर्णांकfs,
						    BRFSI_RFENV << 16);
			अवरोध;
		पूर्ण

		rtl_set_bbreg(hw, pphyreg->rfपूर्णांकfe, BRFSI_RFENV << 16, 0x1);
		udelay(1);

		rtl_set_bbreg(hw, pphyreg->rfपूर्णांकfo, BRFSI_RFENV, 0x1);
		udelay(1);

		rtl_set_bbreg(hw, pphyreg->rfhssi_para2,
			      B3WIREADDREAALENGTH, 0x0);
		udelay(1);

		rtl_set_bbreg(hw, pphyreg->rfhssi_para2, B3WIREDATALENGTH, 0x0);
		udelay(1);

		चयन (rfpath) अणु
		हाल RF90_PATH_A:
			rtstatus = rtl92ee_phy_config_rf_with_headerfile(hw,
						       (क्रमागत radio_path)rfpath);
			अवरोध;
		हाल RF90_PATH_B:
			rtstatus = rtl92ee_phy_config_rf_with_headerfile(hw,
						       (क्रमागत radio_path)rfpath);
			अवरोध;
		हाल RF90_PATH_C:
			अवरोध;
		हाल RF90_PATH_D:
			अवरोध;
		पूर्ण

		चयन (rfpath) अणु
		हाल RF90_PATH_A:
		हाल RF90_PATH_C:
			rtl_set_bbreg(hw, pphyreg->rfपूर्णांकfs,
				      BRFSI_RFENV, u4_regvalue);
			अवरोध;
		हाल RF90_PATH_B:
		हाल RF90_PATH_D:
			rtl_set_bbreg(hw, pphyreg->rfपूर्णांकfs,
				      BRFSI_RFENV << 16, u4_regvalue);
			अवरोध;
		पूर्ण

		अगर (!rtstatus) अणु
			rtl_dbg(rtlpriv, COMP_INIT, DBG_TRACE,
				"Radio[%d] Fail!!\n", rfpath);
			वापस false;
		पूर्ण
	पूर्ण

	rtl_dbg(rtlpriv, COMP_INIT, DBG_TRACE, "\n");
	वापस rtstatus;
पूर्ण
