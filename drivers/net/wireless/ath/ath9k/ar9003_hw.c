<शैली गुरु>
/*
 * Copyright (c) 2008-2011 Atheros Communications Inc.
 *
 * Permission to use, copy, modअगरy, and/or distribute this software क्रम any
 * purpose with or without fee is hereby granted, provided that the above
 * copyright notice and this permission notice appear in all copies.
 *
 * THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
 * WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR
 * ANY SPECIAL, सूचीECT, INसूचीECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
 * WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN
 * ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF
 * OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
 */

#समावेश "hw.h"
#समावेश "ar9003_mac.h"
#समावेश "ar9003_2p2_initvals.h"
#समावेश "ar9003_buffalo_initvals.h"
#समावेश "ar9485_initvals.h"
#समावेश "ar9340_initvals.h"
#समावेश "ar9330_1p1_initvals.h"
#समावेश "ar9330_1p2_initvals.h"
#समावेश "ar955x_1p0_initvals.h"
#समावेश "ar9580_1p0_initvals.h"
#समावेश "ar9462_2p0_initvals.h"
#समावेश "ar9462_2p1_initvals.h"
#समावेश "ar9565_1p0_initvals.h"
#समावेश "ar9565_1p1_initvals.h"
#समावेश "ar953x_initvals.h"
#समावेश "ar956x_initvals.h"

/* General hardware code क्रम the AR9003 hadware family */

/*
 * The AR9003 family uses a new INI क्रमmat (pre, core, post
 * arrays per subप्रणाली). This provides support क्रम the
 * AR9003 2.2 chipsets.
 */
अटल व्योम ar9003_hw_init_mode_regs(काष्ठा ath_hw *ah)
अणु
	अगर (AR_SREV_9330_11(ah)) अणु
		/* mac */
		INIT_INI_ARRAY(&ah->iniMac[ATH_INI_CORE],
				ar9331_1p1_mac_core);
		INIT_INI_ARRAY(&ah->iniMac[ATH_INI_POST],
				ar9331_1p1_mac_postamble);

		/* bb */
		INIT_INI_ARRAY(&ah->iniBB[ATH_INI_CORE],
				ar9331_1p1_baseband_core);
		INIT_INI_ARRAY(&ah->iniBB[ATH_INI_POST],
				ar9331_1p1_baseband_postamble);

		/* radio */
		INIT_INI_ARRAY(&ah->iniRadio[ATH_INI_CORE],
				ar9331_1p1_radio_core);

		/* soc */
		INIT_INI_ARRAY(&ah->iniSOC[ATH_INI_PRE],
				ar9331_1p1_soc_preamble);
		INIT_INI_ARRAY(&ah->iniSOC[ATH_INI_POST],
				ar9331_1p1_soc_postamble);

		/* rx/tx gain */
		INIT_INI_ARRAY(&ah->iniModesRxGain,
				ar9331_common_rx_gain_1p1);
		INIT_INI_ARRAY(&ah->iniModesTxGain,
				ar9331_modes_lowest_ob_db_tx_gain_1p1);

		/* Japan 2484 Mhz CCK */
		INIT_INI_ARRAY(&ah->iniCckfirJapan2484,
			       ar9331_1p1_baseband_core_txfir_coeff_japan_2484);

		/* additional घड़ी settings */
		अगर (ah->is_clk_25mhz)
			INIT_INI_ARRAY(&ah->iniAdditional,
					ar9331_1p1_xtal_25M);
		अन्यथा
			INIT_INI_ARRAY(&ah->iniAdditional,
					ar9331_1p1_xtal_40M);
	पूर्ण अन्यथा अगर (AR_SREV_9330_12(ah)) अणु
		/* mac */
		INIT_INI_ARRAY(&ah->iniMac[ATH_INI_CORE],
				ar9331_1p2_mac_core);
		INIT_INI_ARRAY(&ah->iniMac[ATH_INI_POST],
				ar9331_1p2_mac_postamble);

		/* bb */
		INIT_INI_ARRAY(&ah->iniBB[ATH_INI_CORE],
				ar9331_1p2_baseband_core);
		INIT_INI_ARRAY(&ah->iniBB[ATH_INI_POST],
				ar9331_1p2_baseband_postamble);

		/* radio */
		INIT_INI_ARRAY(&ah->iniRadio[ATH_INI_CORE],
				ar9331_1p2_radio_core);

		/* soc */
		INIT_INI_ARRAY(&ah->iniSOC[ATH_INI_PRE],
				ar9331_1p2_soc_preamble);
		INIT_INI_ARRAY(&ah->iniSOC[ATH_INI_POST],
				ar9331_1p2_soc_postamble);

		/* rx/tx gain */
		INIT_INI_ARRAY(&ah->iniModesRxGain,
				ar9331_common_rx_gain_1p2);
		INIT_INI_ARRAY(&ah->iniModesTxGain,
				ar9331_modes_lowest_ob_db_tx_gain_1p2);

		/* Japan 2484 Mhz CCK */
		INIT_INI_ARRAY(&ah->iniCckfirJapan2484,
			       ar9331_1p2_baseband_core_txfir_coeff_japan_2484);

		/* additional घड़ी settings */
		अगर (ah->is_clk_25mhz)
			INIT_INI_ARRAY(&ah->iniAdditional,
					ar9331_1p2_xtal_25M);
		अन्यथा
			INIT_INI_ARRAY(&ah->iniAdditional,
					ar9331_1p2_xtal_40M);
	पूर्ण अन्यथा अगर (AR_SREV_9340(ah)) अणु
		/* mac */
		INIT_INI_ARRAY(&ah->iniMac[ATH_INI_CORE],
				ar9340_1p0_mac_core);
		INIT_INI_ARRAY(&ah->iniMac[ATH_INI_POST],
				ar9340_1p0_mac_postamble);

		/* bb */
		INIT_INI_ARRAY(&ah->iniBB[ATH_INI_CORE],
				ar9340_1p0_baseband_core);
		INIT_INI_ARRAY(&ah->iniBB[ATH_INI_POST],
				ar9340_1p0_baseband_postamble);

		/* radio */
		INIT_INI_ARRAY(&ah->iniRadio[ATH_INI_CORE],
				ar9340_1p0_radio_core);
		INIT_INI_ARRAY(&ah->iniRadio[ATH_INI_POST],
				ar9340_1p0_radio_postamble);

		/* soc */
		INIT_INI_ARRAY(&ah->iniSOC[ATH_INI_PRE],
				ar9340_1p0_soc_preamble);
		INIT_INI_ARRAY(&ah->iniSOC[ATH_INI_POST],
				ar9340_1p0_soc_postamble);

		/* rx/tx gain */
		INIT_INI_ARRAY(&ah->iniModesRxGain,
				ar9340Common_wo_xlna_rx_gain_table_1p0);
		INIT_INI_ARRAY(&ah->iniModesTxGain,
				ar9340Modes_high_ob_db_tx_gain_table_1p0);

		INIT_INI_ARRAY(&ah->iniModesFastClock,
			       ar9340Modes_fast_घड़ी_1p0);
		INIT_INI_ARRAY(&ah->iniCckfirJapan2484,
			       ar9340_1p0_baseband_core_txfir_coeff_japan_2484);
		INIT_INI_ARRAY(&ah->ini_dfs,
			       ar9340_1p0_baseband_postamble_dfs_channel);

		अगर (!ah->is_clk_25mhz)
			INIT_INI_ARRAY(&ah->iniAdditional,
				       ar9340_1p0_radio_core_40M);
	पूर्ण अन्यथा अगर (AR_SREV_9485_11_OR_LATER(ah)) अणु
		/* mac */
		INIT_INI_ARRAY(&ah->iniMac[ATH_INI_CORE],
				ar9485_1_1_mac_core);
		INIT_INI_ARRAY(&ah->iniMac[ATH_INI_POST],
				ar9485_1_1_mac_postamble);

		/* bb */
		INIT_INI_ARRAY(&ah->iniBB[ATH_INI_PRE], ar9485_1_1);
		INIT_INI_ARRAY(&ah->iniBB[ATH_INI_CORE],
				ar9485_1_1_baseband_core);
		INIT_INI_ARRAY(&ah->iniBB[ATH_INI_POST],
				ar9485_1_1_baseband_postamble);

		/* radio */
		INIT_INI_ARRAY(&ah->iniRadio[ATH_INI_CORE],
				ar9485_1_1_radio_core);
		INIT_INI_ARRAY(&ah->iniRadio[ATH_INI_POST],
				ar9485_1_1_radio_postamble);

		/* soc */
		INIT_INI_ARRAY(&ah->iniSOC[ATH_INI_PRE],
				ar9485_1_1_soc_preamble);

		/* rx/tx gain */
		INIT_INI_ARRAY(&ah->iniModesRxGain,
				ar9485Common_wo_xlna_rx_gain_1_1);
		INIT_INI_ARRAY(&ah->iniModesTxGain,
				ar9485_modes_lowest_ob_db_tx_gain_1_1);

		/* Japan 2484 Mhz CCK */
		INIT_INI_ARRAY(&ah->iniCckfirJapan2484,
			       ar9485_1_1_baseband_core_txfir_coeff_japan_2484);

		अगर (ah->config.pll_pwrsave & AR_PCIE_PLL_PWRSAVE_CONTROL) अणु
			INIT_INI_ARRAY(&ah->iniPcieSerdes,
				       ar9485_1_1_pll_on_cdr_on_clkreq_disable_L1);
			INIT_INI_ARRAY(&ah->iniPcieSerdesLowPower,
				       ar9485_1_1_pll_on_cdr_on_clkreq_disable_L1);
		पूर्ण अन्यथा अणु
			INIT_INI_ARRAY(&ah->iniPcieSerdes,
				       ar9485_1_1_pcie_phy_clkreq_disable_L1);
			INIT_INI_ARRAY(&ah->iniPcieSerdesLowPower,
				       ar9485_1_1_pcie_phy_clkreq_disable_L1);
		पूर्ण
	पूर्ण अन्यथा अगर (AR_SREV_9462_21(ah)) अणु
		INIT_INI_ARRAY(&ah->iniMac[ATH_INI_CORE],
			       ar9462_2p1_mac_core);
		INIT_INI_ARRAY(&ah->iniMac[ATH_INI_POST],
			       ar9462_2p1_mac_postamble);
		INIT_INI_ARRAY(&ah->iniBB[ATH_INI_CORE],
			       ar9462_2p1_baseband_core);
		INIT_INI_ARRAY(&ah->iniBB[ATH_INI_POST],
			       ar9462_2p1_baseband_postamble);
		INIT_INI_ARRAY(&ah->iniRadio[ATH_INI_CORE],
			       ar9462_2p1_radio_core);
		INIT_INI_ARRAY(&ah->iniRadio[ATH_INI_POST],
			       ar9462_2p1_radio_postamble);
		INIT_INI_ARRAY(&ah->ini_radio_post_sys2ant,
			       ar9462_2p1_radio_postamble_sys2ant);
		INIT_INI_ARRAY(&ah->iniSOC[ATH_INI_PRE],
			       ar9462_2p1_soc_preamble);
		INIT_INI_ARRAY(&ah->iniSOC[ATH_INI_POST],
			       ar9462_2p1_soc_postamble);
		INIT_INI_ARRAY(&ah->iniModesRxGain,
			       ar9462_2p1_common_rx_gain);
		INIT_INI_ARRAY(&ah->iniModesFastClock,
			       ar9462_2p1_modes_fast_घड़ी);
		INIT_INI_ARRAY(&ah->iniCckfirJapan2484,
			       ar9462_2p1_baseband_core_txfir_coeff_japan_2484);

		/* Awake -> Sleep Setting */
		अगर ((ah->config.pll_pwrsave & AR_PCIE_PLL_PWRSAVE_CONTROL) &&
		    (ah->config.pll_pwrsave & AR_PCIE_PLL_PWRSAVE_ON_D3)) अणु
			INIT_INI_ARRAY(&ah->iniPcieSerdes,
				       ar9462_2p1_pciephy_clkreq_disable_L1);
		पूर्ण

		/* Sleep -> Awake Setting */
		अगर ((ah->config.pll_pwrsave & AR_PCIE_PLL_PWRSAVE_CONTROL) &&
		    (ah->config.pll_pwrsave & AR_PCIE_PLL_PWRSAVE_ON_D0)) अणु
			INIT_INI_ARRAY(&ah->iniPcieSerdesLowPower,
				       ar9462_2p1_pciephy_clkreq_disable_L1);
		पूर्ण
	पूर्ण अन्यथा अगर (AR_SREV_9462_20(ah)) अणु

		INIT_INI_ARRAY(&ah->iniMac[ATH_INI_CORE], ar9462_2p0_mac_core);
		INIT_INI_ARRAY(&ah->iniMac[ATH_INI_POST],
				ar9462_2p0_mac_postamble);

		INIT_INI_ARRAY(&ah->iniBB[ATH_INI_CORE],
				ar9462_2p0_baseband_core);
		INIT_INI_ARRAY(&ah->iniBB[ATH_INI_POST],
				ar9462_2p0_baseband_postamble);

		INIT_INI_ARRAY(&ah->iniRadio[ATH_INI_CORE],
				ar9462_2p0_radio_core);
		INIT_INI_ARRAY(&ah->iniRadio[ATH_INI_POST],
				ar9462_2p0_radio_postamble);
		INIT_INI_ARRAY(&ah->ini_radio_post_sys2ant,
				ar9462_2p0_radio_postamble_sys2ant);

		INIT_INI_ARRAY(&ah->iniSOC[ATH_INI_PRE],
				ar9462_2p0_soc_preamble);
		INIT_INI_ARRAY(&ah->iniSOC[ATH_INI_POST],
				ar9462_2p0_soc_postamble);

		INIT_INI_ARRAY(&ah->iniModesRxGain,
				ar9462_2p0_common_rx_gain);

		/* Awake -> Sleep Setting */
		अगर ((ah->config.pll_pwrsave & AR_PCIE_PLL_PWRSAVE_CONTROL) &&
		    (ah->config.pll_pwrsave & AR_PCIE_PLL_PWRSAVE_ON_D3)) अणु
			INIT_INI_ARRAY(&ah->iniPcieSerdes,
				       ar9462_2p0_pciephy_clkreq_disable_L1);
		पूर्ण

		/* Sleep -> Awake Setting */
		अगर ((ah->config.pll_pwrsave & AR_PCIE_PLL_PWRSAVE_CONTROL) &&
		    (ah->config.pll_pwrsave & AR_PCIE_PLL_PWRSAVE_ON_D0)) अणु
			INIT_INI_ARRAY(&ah->iniPcieSerdesLowPower,
				       ar9462_2p0_pciephy_clkreq_disable_L1);
		पूर्ण

		/* Fast घड़ी modal settings */
		INIT_INI_ARRAY(&ah->iniModesFastClock,
				ar9462_2p0_modes_fast_घड़ी);

		INIT_INI_ARRAY(&ah->iniCckfirJapan2484,
			       ar9462_2p0_baseband_core_txfir_coeff_japan_2484);
	पूर्ण अन्यथा अगर (AR_SREV_9550(ah)) अणु
		/* mac */
		INIT_INI_ARRAY(&ah->iniMac[ATH_INI_CORE],
				ar955x_1p0_mac_core);
		INIT_INI_ARRAY(&ah->iniMac[ATH_INI_POST],
				ar955x_1p0_mac_postamble);

		/* bb */
		INIT_INI_ARRAY(&ah->iniBB[ATH_INI_CORE],
				ar955x_1p0_baseband_core);
		INIT_INI_ARRAY(&ah->iniBB[ATH_INI_POST],
				ar955x_1p0_baseband_postamble);

		/* radio */
		INIT_INI_ARRAY(&ah->iniRadio[ATH_INI_CORE],
				ar955x_1p0_radio_core);
		INIT_INI_ARRAY(&ah->iniRadio[ATH_INI_POST],
				ar955x_1p0_radio_postamble);

		/* soc */
		INIT_INI_ARRAY(&ah->iniSOC[ATH_INI_PRE],
				ar955x_1p0_soc_preamble);
		INIT_INI_ARRAY(&ah->iniSOC[ATH_INI_POST],
				ar955x_1p0_soc_postamble);

		/* rx/tx gain */
		INIT_INI_ARRAY(&ah->iniModesRxGain,
			ar955x_1p0_common_wo_xlna_rx_gain_table);
		INIT_INI_ARRAY(&ah->ini_modes_rx_gain_bounds,
			ar955x_1p0_common_wo_xlna_rx_gain_bounds);
		INIT_INI_ARRAY(&ah->iniModesTxGain,
				ar955x_1p0_modes_xpa_tx_gain_table);

		/* Fast घड़ी modal settings */
		INIT_INI_ARRAY(&ah->iniModesFastClock,
				ar955x_1p0_modes_fast_घड़ी);
	पूर्ण अन्यथा अगर (AR_SREV_9531(ah)) अणु
		INIT_INI_ARRAY(&ah->iniMac[ATH_INI_CORE],
			       qca953x_1p0_mac_core);
		INIT_INI_ARRAY(&ah->iniMac[ATH_INI_POST],
			       qca953x_1p0_mac_postamble);
		अगर (AR_SREV_9531_20(ah)) अणु
			INIT_INI_ARRAY(&ah->iniBB[ATH_INI_CORE],
				       qca953x_2p0_baseband_core);
			INIT_INI_ARRAY(&ah->iniBB[ATH_INI_POST],
				       qca953x_2p0_baseband_postamble);
		पूर्ण अन्यथा अणु
			INIT_INI_ARRAY(&ah->iniBB[ATH_INI_CORE],
				       qca953x_1p0_baseband_core);
			INIT_INI_ARRAY(&ah->iniBB[ATH_INI_POST],
				       qca953x_1p0_baseband_postamble);
		पूर्ण
		INIT_INI_ARRAY(&ah->iniRadio[ATH_INI_CORE],
			       qca953x_1p0_radio_core);
		INIT_INI_ARRAY(&ah->iniRadio[ATH_INI_POST],
			       qca953x_1p0_radio_postamble);
		INIT_INI_ARRAY(&ah->iniSOC[ATH_INI_PRE],
			       qca953x_1p0_soc_preamble);
		INIT_INI_ARRAY(&ah->iniSOC[ATH_INI_POST],
			       qca953x_1p0_soc_postamble);

		अगर (AR_SREV_9531_20(ah)) अणु
			INIT_INI_ARRAY(&ah->iniModesRxGain,
				       qca953x_2p0_common_wo_xlna_rx_gain_table);
			INIT_INI_ARRAY(&ah->ini_modes_rx_gain_bounds,
				       qca953x_2p0_common_wo_xlna_rx_gain_bounds);
		पूर्ण अन्यथा अणु
			INIT_INI_ARRAY(&ah->iniModesRxGain,
				       qca953x_1p0_common_wo_xlna_rx_gain_table);
			INIT_INI_ARRAY(&ah->ini_modes_rx_gain_bounds,
				       qca953x_1p0_common_wo_xlna_rx_gain_bounds);
		पूर्ण

		अगर (AR_SREV_9531_20(ah))
			INIT_INI_ARRAY(&ah->iniModesTxGain,
				       qca953x_2p0_modes_no_xpa_tx_gain_table);
		अन्यथा अगर (AR_SREV_9531_11(ah))
			INIT_INI_ARRAY(&ah->iniModesTxGain,
				       qca953x_1p1_modes_no_xpa_tx_gain_table);
		अन्यथा
			INIT_INI_ARRAY(&ah->iniModesTxGain,
				       qca953x_1p0_modes_no_xpa_tx_gain_table);

		INIT_INI_ARRAY(&ah->iniModesFastClock,
			       qca953x_1p0_modes_fast_घड़ी);
	पूर्ण अन्यथा अगर (AR_SREV_9561(ah)) अणु
		INIT_INI_ARRAY(&ah->iniMac[ATH_INI_CORE],
			       qca956x_1p0_mac_core);
		INIT_INI_ARRAY(&ah->iniMac[ATH_INI_POST],
			       qca956x_1p0_mac_postamble);

		INIT_INI_ARRAY(&ah->iniBB[ATH_INI_CORE],
			       qca956x_1p0_baseband_core);
		INIT_INI_ARRAY(&ah->iniBB[ATH_INI_POST],
			       qca956x_1p0_baseband_postamble);

		INIT_INI_ARRAY(&ah->iniRadio[ATH_INI_CORE],
			       qca956x_1p0_radio_core);
		INIT_INI_ARRAY(&ah->iniRadio[ATH_INI_POST],
			       qca956x_1p0_radio_postamble);

		INIT_INI_ARRAY(&ah->iniSOC[ATH_INI_PRE],
			       qca956x_1p0_soc_preamble);
		INIT_INI_ARRAY(&ah->iniSOC[ATH_INI_POST],
			       qca956x_1p0_soc_postamble);

		INIT_INI_ARRAY(&ah->iniModesRxGain,
			       qca956x_1p0_common_wo_xlna_rx_gain_table);
		INIT_INI_ARRAY(&ah->ini_modes_rx_gain_bounds,
			       qca956x_1p0_common_wo_xlna_rx_gain_bounds);
		INIT_INI_ARRAY(&ah->iniModesTxGain,
			       qca956x_1p0_modes_no_xpa_tx_gain_table);

		INIT_INI_ARRAY(&ah->ini_dfs,
			       qca956x_1p0_baseband_postamble_dfs_channel);
		INIT_INI_ARRAY(&ah->iniCckfirJapan2484,
			       qca956x_1p0_baseband_core_txfir_coeff_japan_2484);
		INIT_INI_ARRAY(&ah->iniModesFastClock,
			       qca956x_1p0_modes_fast_घड़ी);
	पूर्ण अन्यथा अगर (AR_SREV_9580(ah)) अणु
		/* mac */
		INIT_INI_ARRAY(&ah->iniMac[ATH_INI_CORE],
				ar9580_1p0_mac_core);
		INIT_INI_ARRAY(&ah->iniMac[ATH_INI_POST],
				ar9580_1p0_mac_postamble);

		/* bb */
		INIT_INI_ARRAY(&ah->iniBB[ATH_INI_CORE],
				ar9580_1p0_baseband_core);
		INIT_INI_ARRAY(&ah->iniBB[ATH_INI_POST],
				ar9580_1p0_baseband_postamble);

		/* radio */
		INIT_INI_ARRAY(&ah->iniRadio[ATH_INI_CORE],
				ar9580_1p0_radio_core);
		INIT_INI_ARRAY(&ah->iniRadio[ATH_INI_POST],
				ar9580_1p0_radio_postamble);

		/* soc */
		INIT_INI_ARRAY(&ah->iniSOC[ATH_INI_PRE],
				ar9580_1p0_soc_preamble);
		INIT_INI_ARRAY(&ah->iniSOC[ATH_INI_POST],
				ar9580_1p0_soc_postamble);

		/* rx/tx gain */
		INIT_INI_ARRAY(&ah->iniModesRxGain,
				ar9580_1p0_rx_gain_table);
		INIT_INI_ARRAY(&ah->iniModesTxGain,
				ar9580_1p0_low_ob_db_tx_gain_table);

		INIT_INI_ARRAY(&ah->iniModesFastClock,
			       ar9580_1p0_modes_fast_घड़ी);
		INIT_INI_ARRAY(&ah->iniCckfirJapan2484,
			       ar9580_1p0_baseband_core_txfir_coeff_japan_2484);
		INIT_INI_ARRAY(&ah->ini_dfs,
			       ar9580_1p0_baseband_postamble_dfs_channel);
	पूर्ण अन्यथा अगर (AR_SREV_9565_11_OR_LATER(ah)) अणु
		INIT_INI_ARRAY(&ah->iniMac[ATH_INI_CORE],
			       ar9565_1p1_mac_core);
		INIT_INI_ARRAY(&ah->iniMac[ATH_INI_POST],
			       ar9565_1p1_mac_postamble);

		INIT_INI_ARRAY(&ah->iniBB[ATH_INI_CORE],
			       ar9565_1p1_baseband_core);
		INIT_INI_ARRAY(&ah->iniBB[ATH_INI_POST],
			       ar9565_1p1_baseband_postamble);

		INIT_INI_ARRAY(&ah->iniRadio[ATH_INI_CORE],
			       ar9565_1p1_radio_core);
		INIT_INI_ARRAY(&ah->iniRadio[ATH_INI_POST],
			       ar9565_1p1_radio_postamble);

		INIT_INI_ARRAY(&ah->iniSOC[ATH_INI_PRE],
			       ar9565_1p1_soc_preamble);
		INIT_INI_ARRAY(&ah->iniSOC[ATH_INI_POST],
			       ar9565_1p1_soc_postamble);

		INIT_INI_ARRAY(&ah->iniModesRxGain,
			       ar9565_1p1_Common_rx_gain_table);
		INIT_INI_ARRAY(&ah->iniModesTxGain,
			       ar9565_1p1_Modes_lowest_ob_db_tx_gain_table);

		/* Awake -> Sleep Setting */
		अगर ((ah->config.pll_pwrsave & AR_PCIE_PLL_PWRSAVE_CONTROL) &&
		    (ah->config.pll_pwrsave & AR_PCIE_PLL_PWRSAVE_ON_D3)) अणु
			INIT_INI_ARRAY(&ah->iniPcieSerdes,
				       ar9565_1p1_pciephy_clkreq_disable_L1);
		पूर्ण

		/* Sleep -> Awake Setting */
		अगर ((ah->config.pll_pwrsave & AR_PCIE_PLL_PWRSAVE_CONTROL) &&
		    (ah->config.pll_pwrsave & AR_PCIE_PLL_PWRSAVE_ON_D0)) अणु
			INIT_INI_ARRAY(&ah->iniPcieSerdesLowPower,
				       ar9565_1p1_pciephy_clkreq_disable_L1);
		पूर्ण

		INIT_INI_ARRAY(&ah->iniModesFastClock,
				ar9565_1p1_modes_fast_घड़ी);
		INIT_INI_ARRAY(&ah->iniCckfirJapan2484,
			       ar9565_1p1_baseband_core_txfir_coeff_japan_2484);
	पूर्ण अन्यथा अगर (AR_SREV_9565(ah)) अणु
		INIT_INI_ARRAY(&ah->iniMac[ATH_INI_CORE],
			       ar9565_1p0_mac_core);
		INIT_INI_ARRAY(&ah->iniMac[ATH_INI_POST],
			       ar9565_1p0_mac_postamble);

		INIT_INI_ARRAY(&ah->iniBB[ATH_INI_CORE],
			       ar9565_1p0_baseband_core);
		INIT_INI_ARRAY(&ah->iniBB[ATH_INI_POST],
			       ar9565_1p0_baseband_postamble);

		INIT_INI_ARRAY(&ah->iniRadio[ATH_INI_CORE],
			       ar9565_1p0_radio_core);
		INIT_INI_ARRAY(&ah->iniRadio[ATH_INI_POST],
			       ar9565_1p0_radio_postamble);

		INIT_INI_ARRAY(&ah->iniSOC[ATH_INI_PRE],
			       ar9565_1p0_soc_preamble);
		INIT_INI_ARRAY(&ah->iniSOC[ATH_INI_POST],
			       ar9565_1p0_soc_postamble);

		INIT_INI_ARRAY(&ah->iniModesRxGain,
			       ar9565_1p0_Common_rx_gain_table);
		INIT_INI_ARRAY(&ah->iniModesTxGain,
			       ar9565_1p0_Modes_lowest_ob_db_tx_gain_table);

		/* Awake -> Sleep Setting */
		अगर ((ah->config.pll_pwrsave & AR_PCIE_PLL_PWRSAVE_CONTROL) &&
		    (ah->config.pll_pwrsave & AR_PCIE_PLL_PWRSAVE_ON_D3)) अणु
			INIT_INI_ARRAY(&ah->iniPcieSerdes,
				       ar9565_1p0_pciephy_clkreq_disable_L1);
		पूर्ण

		/* Sleep -> Awake Setting */
		अगर ((ah->config.pll_pwrsave & AR_PCIE_PLL_PWRSAVE_CONTROL) &&
		    (ah->config.pll_pwrsave & AR_PCIE_PLL_PWRSAVE_ON_D0)) अणु
			INIT_INI_ARRAY(&ah->iniPcieSerdesLowPower,
				       ar9565_1p0_pciephy_clkreq_disable_L1);
		पूर्ण

		INIT_INI_ARRAY(&ah->iniModesFastClock,
				ar9565_1p0_modes_fast_घड़ी);
		INIT_INI_ARRAY(&ah->iniCckfirJapan2484,
			       ar9565_1p0_baseband_core_txfir_coeff_japan_2484);
	पूर्ण अन्यथा अणु
		/* mac */
		INIT_INI_ARRAY(&ah->iniMac[ATH_INI_CORE],
				ar9300_2p2_mac_core);
		INIT_INI_ARRAY(&ah->iniMac[ATH_INI_POST],
				ar9300_2p2_mac_postamble);

		/* bb */
		INIT_INI_ARRAY(&ah->iniBB[ATH_INI_CORE],
				ar9300_2p2_baseband_core);
		INIT_INI_ARRAY(&ah->iniBB[ATH_INI_POST],
				ar9300_2p2_baseband_postamble);

		/* radio */
		INIT_INI_ARRAY(&ah->iniRadio[ATH_INI_CORE],
				ar9300_2p2_radio_core);
		INIT_INI_ARRAY(&ah->iniRadio[ATH_INI_POST],
				ar9300_2p2_radio_postamble);

		/* soc */
		INIT_INI_ARRAY(&ah->iniSOC[ATH_INI_PRE],
				ar9300_2p2_soc_preamble);
		INIT_INI_ARRAY(&ah->iniSOC[ATH_INI_POST],
				ar9300_2p2_soc_postamble);

		/* rx/tx gain */
		INIT_INI_ARRAY(&ah->iniModesRxGain,
				ar9300Common_rx_gain_table_2p2);
		INIT_INI_ARRAY(&ah->iniModesTxGain,
				ar9300Modes_lowest_ob_db_tx_gain_table_2p2);

		/* Load PCIE SERDES settings from INI */

		/* Awake Setting */

		INIT_INI_ARRAY(&ah->iniPcieSerdes,
				ar9300PciePhy_pll_on_clkreq_disable_L1_2p2);

		/* Sleep Setting */

		INIT_INI_ARRAY(&ah->iniPcieSerdesLowPower,
				ar9300PciePhy_pll_on_clkreq_disable_L1_2p2);

		/* Fast घड़ी modal settings */
		INIT_INI_ARRAY(&ah->iniModesFastClock,
			       ar9300Modes_fast_घड़ी_2p2);
		INIT_INI_ARRAY(&ah->iniCckfirJapan2484,
			       ar9300_2p2_baseband_core_txfir_coeff_japan_2484);
		INIT_INI_ARRAY(&ah->ini_dfs,
			       ar9300_2p2_baseband_postamble_dfs_channel);
	पूर्ण
पूर्ण

अटल व्योम ar9003_tx_gain_table_mode0(काष्ठा ath_hw *ah)
अणु
	अगर (AR_SREV_9330_12(ah))
		INIT_INI_ARRAY(&ah->iniModesTxGain,
			ar9331_modes_lowest_ob_db_tx_gain_1p2);
	अन्यथा अगर (AR_SREV_9330_11(ah))
		INIT_INI_ARRAY(&ah->iniModesTxGain,
			ar9331_modes_lowest_ob_db_tx_gain_1p1);
	अन्यथा अगर (AR_SREV_9340(ah))
		INIT_INI_ARRAY(&ah->iniModesTxGain,
			ar9340Modes_lowest_ob_db_tx_gain_table_1p0);
	अन्यथा अगर (AR_SREV_9485_11_OR_LATER(ah))
		INIT_INI_ARRAY(&ah->iniModesTxGain,
			ar9485_modes_lowest_ob_db_tx_gain_1_1);
	अन्यथा अगर (AR_SREV_9550(ah))
		INIT_INI_ARRAY(&ah->iniModesTxGain,
			ar955x_1p0_modes_xpa_tx_gain_table);
	अन्यथा अगर (AR_SREV_9531_10(ah))
		INIT_INI_ARRAY(&ah->iniModesTxGain,
			       qca953x_1p0_modes_xpa_tx_gain_table);
	अन्यथा अगर (AR_SREV_9531_11(ah))
		INIT_INI_ARRAY(&ah->iniModesTxGain,
			       qca953x_1p1_modes_xpa_tx_gain_table);
	अन्यथा अगर (AR_SREV_9531_20(ah))
		INIT_INI_ARRAY(&ah->iniModesTxGain,
			       qca953x_2p0_modes_xpa_tx_gain_table);
	अन्यथा अगर (AR_SREV_9561(ah))
		INIT_INI_ARRAY(&ah->iniModesTxGain,
			       qca956x_1p0_modes_xpa_tx_gain_table);
	अन्यथा अगर (AR_SREV_9580(ah))
		INIT_INI_ARRAY(&ah->iniModesTxGain,
			ar9580_1p0_lowest_ob_db_tx_gain_table);
	अन्यथा अगर (AR_SREV_9462_21(ah))
		INIT_INI_ARRAY(&ah->iniModesTxGain,
			ar9462_2p1_modes_low_ob_db_tx_gain);
	अन्यथा अगर (AR_SREV_9462_20(ah))
		INIT_INI_ARRAY(&ah->iniModesTxGain,
			ar9462_2p0_modes_low_ob_db_tx_gain);
	अन्यथा अगर (AR_SREV_9565_11(ah))
		INIT_INI_ARRAY(&ah->iniModesTxGain,
			       ar9565_1p1_modes_low_ob_db_tx_gain_table);
	अन्यथा अगर (AR_SREV_9565(ah))
		INIT_INI_ARRAY(&ah->iniModesTxGain,
			       ar9565_1p0_modes_low_ob_db_tx_gain_table);
	अन्यथा
		INIT_INI_ARRAY(&ah->iniModesTxGain,
			ar9300Modes_lowest_ob_db_tx_gain_table_2p2);
पूर्ण

अटल व्योम ar9003_tx_gain_table_mode1(काष्ठा ath_hw *ah)
अणु
	अगर (AR_SREV_9330_12(ah))
		INIT_INI_ARRAY(&ah->iniModesTxGain,
			ar9331_modes_high_ob_db_tx_gain_1p2);
	अन्यथा अगर (AR_SREV_9330_11(ah))
		INIT_INI_ARRAY(&ah->iniModesTxGain,
			ar9331_modes_high_ob_db_tx_gain_1p1);
	अन्यथा अगर (AR_SREV_9340(ah))
		INIT_INI_ARRAY(&ah->iniModesTxGain,
			ar9340Modes_high_ob_db_tx_gain_table_1p0);
	अन्यथा अगर (AR_SREV_9485_11_OR_LATER(ah))
		INIT_INI_ARRAY(&ah->iniModesTxGain,
			ar9485Modes_high_ob_db_tx_gain_1_1);
	अन्यथा अगर (AR_SREV_9580(ah))
		INIT_INI_ARRAY(&ah->iniModesTxGain,
			ar9580_1p0_high_ob_db_tx_gain_table);
	अन्यथा अगर (AR_SREV_9550(ah))
		INIT_INI_ARRAY(&ah->iniModesTxGain,
			ar955x_1p0_modes_no_xpa_tx_gain_table);
	अन्यथा अगर (AR_SREV_9531(ah)) अणु
		अगर (AR_SREV_9531_20(ah))
			INIT_INI_ARRAY(&ah->iniModesTxGain,
				       qca953x_2p0_modes_no_xpa_tx_gain_table);
		अन्यथा अगर (AR_SREV_9531_11(ah))
			INIT_INI_ARRAY(&ah->iniModesTxGain,
				       qca953x_1p1_modes_no_xpa_tx_gain_table);
		अन्यथा
			INIT_INI_ARRAY(&ah->iniModesTxGain,
				       qca953x_1p0_modes_no_xpa_tx_gain_table);
	पूर्ण अन्यथा अगर (AR_SREV_9561(ah))
		INIT_INI_ARRAY(&ah->iniModesTxGain,
			       qca956x_1p0_modes_no_xpa_tx_gain_table);
	अन्यथा अगर (AR_SREV_9462_21(ah))
		INIT_INI_ARRAY(&ah->iniModesTxGain,
			ar9462_2p1_modes_high_ob_db_tx_gain);
	अन्यथा अगर (AR_SREV_9462_20(ah))
		INIT_INI_ARRAY(&ah->iniModesTxGain,
			ar9462_2p0_modes_high_ob_db_tx_gain);
	अन्यथा अगर (AR_SREV_9565_11(ah))
		INIT_INI_ARRAY(&ah->iniModesTxGain,
			       ar9565_1p1_modes_high_ob_db_tx_gain_table);
	अन्यथा अगर (AR_SREV_9565(ah))
		INIT_INI_ARRAY(&ah->iniModesTxGain,
			       ar9565_1p0_modes_high_ob_db_tx_gain_table);
	अन्यथा
		INIT_INI_ARRAY(&ah->iniModesTxGain,
			ar9300Modes_high_ob_db_tx_gain_table_2p2);
पूर्ण

अटल व्योम ar9003_tx_gain_table_mode2(काष्ठा ath_hw *ah)
अणु
	अगर (AR_SREV_9330_12(ah))
		INIT_INI_ARRAY(&ah->iniModesTxGain,
			ar9331_modes_low_ob_db_tx_gain_1p2);
	अन्यथा अगर (AR_SREV_9330_11(ah))
		INIT_INI_ARRAY(&ah->iniModesTxGain,
			ar9331_modes_low_ob_db_tx_gain_1p1);
	अन्यथा अगर (AR_SREV_9340(ah))
		INIT_INI_ARRAY(&ah->iniModesTxGain,
			ar9340Modes_low_ob_db_tx_gain_table_1p0);
	अन्यथा अगर (AR_SREV_9531_11(ah))
		INIT_INI_ARRAY(&ah->iniModesTxGain,
			       qca953x_1p1_modes_no_xpa_low_घातer_tx_gain_table);
	अन्यथा अगर (AR_SREV_9485_11_OR_LATER(ah))
		INIT_INI_ARRAY(&ah->iniModesTxGain,
			ar9485Modes_low_ob_db_tx_gain_1_1);
	अन्यथा अगर (AR_SREV_9580(ah))
		INIT_INI_ARRAY(&ah->iniModesTxGain,
			ar9580_1p0_low_ob_db_tx_gain_table);
	अन्यथा अगर (AR_SREV_9561(ah))
		INIT_INI_ARRAY(&ah->iniModesTxGain,
			       qca956x_1p0_modes_no_xpa_low_ob_db_tx_gain_table);
	अन्यथा अगर (AR_SREV_9565_11(ah))
		INIT_INI_ARRAY(&ah->iniModesTxGain,
			       ar9565_1p1_modes_low_ob_db_tx_gain_table);
	अन्यथा अगर (AR_SREV_9565(ah))
		INIT_INI_ARRAY(&ah->iniModesTxGain,
			       ar9565_1p0_modes_low_ob_db_tx_gain_table);
	अन्यथा
		INIT_INI_ARRAY(&ah->iniModesTxGain,
			ar9300Modes_low_ob_db_tx_gain_table_2p2);
पूर्ण

अटल व्योम ar9003_tx_gain_table_mode3(काष्ठा ath_hw *ah)
अणु
	अगर (AR_SREV_9330_12(ah))
		INIT_INI_ARRAY(&ah->iniModesTxGain,
			ar9331_modes_high_घातer_tx_gain_1p2);
	अन्यथा अगर (AR_SREV_9330_11(ah))
		INIT_INI_ARRAY(&ah->iniModesTxGain,
			ar9331_modes_high_घातer_tx_gain_1p1);
	अन्यथा अगर (AR_SREV_9340(ah))
		INIT_INI_ARRAY(&ah->iniModesTxGain,
			ar9340Modes_high_घातer_tx_gain_table_1p0);
	अन्यथा अगर (AR_SREV_9485_11_OR_LATER(ah))
		INIT_INI_ARRAY(&ah->iniModesTxGain,
			ar9485Modes_high_घातer_tx_gain_1_1);
	अन्यथा अगर (AR_SREV_9580(ah))
		INIT_INI_ARRAY(&ah->iniModesTxGain,
			ar9580_1p0_high_घातer_tx_gain_table);
	अन्यथा अगर (AR_SREV_9565_11(ah))
		INIT_INI_ARRAY(&ah->iniModesTxGain,
			       ar9565_1p1_modes_high_घातer_tx_gain_table);
	अन्यथा अगर (AR_SREV_9565(ah))
		INIT_INI_ARRAY(&ah->iniModesTxGain,
			       ar9565_1p0_modes_high_घातer_tx_gain_table);
	अन्यथा अणु
		अगर (ah->config.tx_gain_buffalo)
			INIT_INI_ARRAY(&ah->iniModesTxGain,
				       ar9300Modes_high_घातer_tx_gain_table_buffalo);
		अन्यथा
			INIT_INI_ARRAY(&ah->iniModesTxGain,
				       ar9300Modes_high_घातer_tx_gain_table_2p2);
	पूर्ण
पूर्ण

अटल व्योम ar9003_tx_gain_table_mode4(काष्ठा ath_hw *ah)
अणु
	अगर (AR_SREV_9340(ah))
		INIT_INI_ARRAY(&ah->iniModesTxGain,
			ar9340Modes_mixed_ob_db_tx_gain_table_1p0);
	अन्यथा अगर (AR_SREV_9580(ah))
		INIT_INI_ARRAY(&ah->iniModesTxGain,
			ar9580_1p0_mixed_ob_db_tx_gain_table);
	अन्यथा अगर (AR_SREV_9462_21(ah))
		INIT_INI_ARRAY(&ah->iniModesTxGain,
		       ar9462_2p1_modes_mix_ob_db_tx_gain);
	अन्यथा अगर (AR_SREV_9462_20(ah))
		INIT_INI_ARRAY(&ah->iniModesTxGain,
		       ar9462_2p0_modes_mix_ob_db_tx_gain);
	अन्यथा
		INIT_INI_ARRAY(&ah->iniModesTxGain,
			ar9300Modes_mixed_ob_db_tx_gain_table_2p2);
पूर्ण

अटल व्योम ar9003_tx_gain_table_mode5(काष्ठा ath_hw *ah)
अणु
	अगर (AR_SREV_9485_11_OR_LATER(ah))
		INIT_INI_ARRAY(&ah->iniModesTxGain,
			ar9485Modes_green_ob_db_tx_gain_1_1);
	अन्यथा अगर (AR_SREV_9580(ah))
		INIT_INI_ARRAY(&ah->iniModesTxGain,
			ar9580_1p0_type5_tx_gain_table);
	अन्यथा अगर (AR_SREV_9561(ah))
		INIT_INI_ARRAY(&ah->iniModesTxGain,
			       qca956x_1p0_modes_no_xpa_green_tx_gain_table);
	अन्यथा अगर (AR_SREV_9300_22(ah))
		INIT_INI_ARRAY(&ah->iniModesTxGain,
			ar9300Modes_type5_tx_gain_table_2p2);
पूर्ण

अटल व्योम ar9003_tx_gain_table_mode6(काष्ठा ath_hw *ah)
अणु
	अगर (AR_SREV_9340(ah))
		INIT_INI_ARRAY(&ah->iniModesTxGain,
			ar9340Modes_low_ob_db_and_spur_tx_gain_table_1p0);
	अन्यथा अगर (AR_SREV_9485_11_OR_LATER(ah))
		INIT_INI_ARRAY(&ah->iniModesTxGain,
			ar9485Modes_green_spur_ob_db_tx_gain_1_1);
	अन्यथा अगर (AR_SREV_9580(ah))
		INIT_INI_ARRAY(&ah->iniModesTxGain,
			ar9580_1p0_type6_tx_gain_table);
पूर्ण

अटल व्योम ar9003_tx_gain_table_mode7(काष्ठा ath_hw *ah)
अणु
	अगर (AR_SREV_9340(ah))
		INIT_INI_ARRAY(&ah->iniModesTxGain,
			       ar9340_cus227_tx_gain_table_1p0);
पूर्ण

प्रकार व्योम (*ath_txgain_tab)(काष्ठा ath_hw *ah);

अटल व्योम ar9003_tx_gain_table_apply(काष्ठा ath_hw *ah)
अणु
	अटल स्थिर ath_txgain_tab modes[] = अणु
		ar9003_tx_gain_table_mode0,
		ar9003_tx_gain_table_mode1,
		ar9003_tx_gain_table_mode2,
		ar9003_tx_gain_table_mode3,
		ar9003_tx_gain_table_mode4,
		ar9003_tx_gain_table_mode5,
		ar9003_tx_gain_table_mode6,
		ar9003_tx_gain_table_mode7,
	पूर्ण;
	पूर्णांक idx = ar9003_hw_get_tx_gain_idx(ah);

	अगर (idx >= ARRAY_SIZE(modes))
		idx = 0;

	modes[idx](ah);
पूर्ण

अटल व्योम ar9003_rx_gain_table_mode0(काष्ठा ath_hw *ah)
अणु
	अगर (AR_SREV_9330_12(ah))
		INIT_INI_ARRAY(&ah->iniModesRxGain,
				ar9331_common_rx_gain_1p2);
	अन्यथा अगर (AR_SREV_9330_11(ah))
		INIT_INI_ARRAY(&ah->iniModesRxGain,
				ar9331_common_rx_gain_1p1);
	अन्यथा अगर (AR_SREV_9340(ah))
		INIT_INI_ARRAY(&ah->iniModesRxGain,
				ar9340Common_rx_gain_table_1p0);
	अन्यथा अगर (AR_SREV_9485_11_OR_LATER(ah))
		INIT_INI_ARRAY(&ah->iniModesRxGain,
			       ar9485_common_rx_gain_1_1);
	अन्यथा अगर (AR_SREV_9550(ah)) अणु
		INIT_INI_ARRAY(&ah->iniModesRxGain,
				ar955x_1p0_common_rx_gain_table);
		INIT_INI_ARRAY(&ah->ini_modes_rx_gain_bounds,
				ar955x_1p0_common_rx_gain_bounds);
	पूर्ण अन्यथा अगर (AR_SREV_9531(ah)) अणु
		INIT_INI_ARRAY(&ah->iniModesRxGain,
			       qca953x_1p0_common_rx_gain_table);
		INIT_INI_ARRAY(&ah->ini_modes_rx_gain_bounds,
			       qca953x_1p0_common_rx_gain_bounds);
	पूर्ण अन्यथा अगर (AR_SREV_9561(ah)) अणु
		INIT_INI_ARRAY(&ah->iniModesRxGain,
			       qca956x_1p0_common_rx_gain_table);
		INIT_INI_ARRAY(&ah->ini_modes_rx_gain_bounds,
			       qca956x_1p0_common_rx_gain_bounds);
		INIT_INI_ARRAY(&ah->ini_modes_rxgain_xlna,
			       qca956x_1p0_xlna_only);
	पूर्ण अन्यथा अगर (AR_SREV_9580(ah))
		INIT_INI_ARRAY(&ah->iniModesRxGain,
				ar9580_1p0_rx_gain_table);
	अन्यथा अगर (AR_SREV_9462_21(ah))
		INIT_INI_ARRAY(&ah->iniModesRxGain,
				ar9462_2p1_common_rx_gain);
	अन्यथा अगर (AR_SREV_9462_20(ah))
		INIT_INI_ARRAY(&ah->iniModesRxGain,
				ar9462_2p0_common_rx_gain);
	अन्यथा अगर (AR_SREV_9565_11(ah))
		INIT_INI_ARRAY(&ah->iniModesRxGain,
			       ar9565_1p1_Common_rx_gain_table);
	अन्यथा अगर (AR_SREV_9565(ah))
		INIT_INI_ARRAY(&ah->iniModesRxGain,
			       ar9565_1p0_Common_rx_gain_table);
	अन्यथा
		INIT_INI_ARRAY(&ah->iniModesRxGain,
				ar9300Common_rx_gain_table_2p2);
पूर्ण

अटल व्योम ar9003_rx_gain_table_mode1(काष्ठा ath_hw *ah)
अणु
	अगर (AR_SREV_9330_12(ah))
		INIT_INI_ARRAY(&ah->iniModesRxGain,
			ar9331_common_wo_xlna_rx_gain_1p2);
	अन्यथा अगर (AR_SREV_9330_11(ah))
		INIT_INI_ARRAY(&ah->iniModesRxGain,
			ar9331_common_wo_xlna_rx_gain_1p1);
	अन्यथा अगर (AR_SREV_9340(ah))
		INIT_INI_ARRAY(&ah->iniModesRxGain,
			ar9340Common_wo_xlna_rx_gain_table_1p0);
	अन्यथा अगर (AR_SREV_9485_11_OR_LATER(ah))
		INIT_INI_ARRAY(&ah->iniModesRxGain,
			ar9485Common_wo_xlna_rx_gain_1_1);
	अन्यथा अगर (AR_SREV_9462_21(ah))
		INIT_INI_ARRAY(&ah->iniModesRxGain,
			ar9462_2p1_common_wo_xlna_rx_gain);
	अन्यथा अगर (AR_SREV_9462_20(ah))
		INIT_INI_ARRAY(&ah->iniModesRxGain,
			ar9462_2p0_common_wo_xlna_rx_gain);
	अन्यथा अगर (AR_SREV_9550(ah)) अणु
		INIT_INI_ARRAY(&ah->iniModesRxGain,
			ar955x_1p0_common_wo_xlna_rx_gain_table);
		INIT_INI_ARRAY(&ah->ini_modes_rx_gain_bounds,
			ar955x_1p0_common_wo_xlna_rx_gain_bounds);
	पूर्ण अन्यथा अगर (AR_SREV_9531_10(ah) || AR_SREV_9531_11(ah)) अणु
		INIT_INI_ARRAY(&ah->iniModesRxGain,
			       qca953x_1p0_common_wo_xlna_rx_gain_table);
		INIT_INI_ARRAY(&ah->ini_modes_rx_gain_bounds,
			       qca953x_1p0_common_wo_xlna_rx_gain_bounds);
	पूर्ण अन्यथा अगर (AR_SREV_9531_20(ah)) अणु
		INIT_INI_ARRAY(&ah->iniModesRxGain,
			       qca953x_2p0_common_wo_xlna_rx_gain_table);
		INIT_INI_ARRAY(&ah->ini_modes_rx_gain_bounds,
			       qca953x_2p0_common_wo_xlna_rx_gain_bounds);
	पूर्ण अन्यथा अगर (AR_SREV_9561(ah)) अणु
		INIT_INI_ARRAY(&ah->iniModesRxGain,
			       qca956x_1p0_common_wo_xlna_rx_gain_table);
		INIT_INI_ARRAY(&ah->ini_modes_rx_gain_bounds,
			       qca956x_1p0_common_wo_xlna_rx_gain_bounds);
	पूर्ण अन्यथा अगर (AR_SREV_9580(ah))
		INIT_INI_ARRAY(&ah->iniModesRxGain,
			ar9580_1p0_wo_xlna_rx_gain_table);
	अन्यथा अगर (AR_SREV_9565_11(ah))
		INIT_INI_ARRAY(&ah->iniModesRxGain,
			       ar9565_1p1_common_wo_xlna_rx_gain_table);
	अन्यथा अगर (AR_SREV_9565(ah))
		INIT_INI_ARRAY(&ah->iniModesRxGain,
			       ar9565_1p0_common_wo_xlna_rx_gain_table);
	अन्यथा
		INIT_INI_ARRAY(&ah->iniModesRxGain,
			ar9300Common_wo_xlna_rx_gain_table_2p2);
पूर्ण

अटल व्योम ar9003_rx_gain_table_mode2(काष्ठा ath_hw *ah)
अणु
	अगर (AR_SREV_9462_21(ah)) अणु
		INIT_INI_ARRAY(&ah->iniModesRxGain,
			       ar9462_2p1_common_mixed_rx_gain);
		INIT_INI_ARRAY(&ah->ini_modes_rxgain_bb_core,
			       ar9462_2p1_baseband_core_mix_rxgain);
		INIT_INI_ARRAY(&ah->ini_modes_rxgain_bb_postamble,
			       ar9462_2p1_baseband_postamble_mix_rxgain);
		INIT_INI_ARRAY(&ah->ini_modes_rxgain_xlna,
			       ar9462_2p1_baseband_postamble_5g_xlna);
	पूर्ण अन्यथा अगर (AR_SREV_9462_20(ah)) अणु
		INIT_INI_ARRAY(&ah->iniModesRxGain,
			       ar9462_2p0_common_mixed_rx_gain);
		INIT_INI_ARRAY(&ah->ini_modes_rxgain_bb_core,
			       ar9462_2p0_baseband_core_mix_rxgain);
		INIT_INI_ARRAY(&ah->ini_modes_rxgain_bb_postamble,
			       ar9462_2p0_baseband_postamble_mix_rxgain);
		INIT_INI_ARRAY(&ah->ini_modes_rxgain_xlna,
			       ar9462_2p0_baseband_postamble_5g_xlna);
	पूर्ण
पूर्ण

अटल व्योम ar9003_rx_gain_table_mode3(काष्ठा ath_hw *ah)
अणु
	अगर (AR_SREV_9462_21(ah)) अणु
		INIT_INI_ARRAY(&ah->iniModesRxGain,
			       ar9462_2p1_common_5g_xlna_only_rxgain);
		INIT_INI_ARRAY(&ah->ini_modes_rxgain_xlna,
			       ar9462_2p1_baseband_postamble_5g_xlna);
	पूर्ण अन्यथा अगर (AR_SREV_9462_20(ah)) अणु
		INIT_INI_ARRAY(&ah->iniModesRxGain,
			       ar9462_2p0_common_5g_xlna_only_rxgain);
		INIT_INI_ARRAY(&ah->ini_modes_rxgain_xlna,
			       ar9462_2p0_baseband_postamble_5g_xlna);
	पूर्ण
पूर्ण

अटल व्योम ar9003_rx_gain_table_apply(काष्ठा ath_hw *ah)
अणु
	चयन (ar9003_hw_get_rx_gain_idx(ah)) अणु
	हाल 0:
	शेष:
		ar9003_rx_gain_table_mode0(ah);
		अवरोध;
	हाल 1:
		ar9003_rx_gain_table_mode1(ah);
		अवरोध;
	हाल 2:
		ar9003_rx_gain_table_mode2(ah);
		अवरोध;
	हाल 3:
		ar9003_rx_gain_table_mode3(ah);
		अवरोध;
	पूर्ण
पूर्ण

/* set gain table poपूर्णांकers according to values पढ़ो from the eeprom */
अटल व्योम ar9003_hw_init_mode_gain_regs(काष्ठा ath_hw *ah)
अणु
	ar9003_tx_gain_table_apply(ah);
	ar9003_rx_gain_table_apply(ah);
पूर्ण

/*
 * Helper क्रम ASPM support.
 *
 * Disable PLL when in L0s as well as receiver घड़ी when in L1.
 * This घातer saving option must be enabled through the SerDes.
 *
 * Programming the SerDes must go through the same 288 bit serial shअगरt
 * रेजिस्टर as the other analog रेजिस्टरs.  Hence the 9 ग_लिखोs.
 */
अटल व्योम ar9003_hw_configpciघातersave(काष्ठा ath_hw *ah,
					 bool घातer_off)
अणु
	अचिन्हित पूर्णांक i;
	काष्ठा ar5416IniArray *array;

	/*
	 * Increase L1 Entry Latency. Some WB222 boards करोn't have
	 * this change in eeprom/OTP.
	 *
	 */
	अगर (AR_SREV_9462(ah)) अणु
		u32 val = ah->config.aspm_l1_fix;
		अगर ((val & 0xff000000) == 0x17000000) अणु
			val &= 0x00ffffff;
			val |= 0x27000000;
			REG_WRITE(ah, 0x570c, val);
		पूर्ण
	पूर्ण

	/* Nothing to करो on restore क्रम 11N */
	अगर (!घातer_off /* !restore */) अणु
		/* set bit 19 to allow क्रमcing of pcie core पूर्णांकo L1 state */
		REG_SET_BIT(ah, AR_PCIE_PM_CTRL, AR_PCIE_PM_CTRL_ENA);
		REG_WRITE(ah, AR_WA, ah->WARegVal);
	पूर्ण

	/*
	 * Configure PCIE after Ini init. SERDES values now come from ini file
	 * This enables PCIe low घातer mode.
	 */
	array = घातer_off ? &ah->iniPcieSerdes :
		&ah->iniPcieSerdesLowPower;

	क्रम (i = 0; i < array->ia_rows; i++) अणु
		REG_WRITE(ah,
			  INI_RA(array, i, 0),
			  INI_RA(array, i, 1));
	पूर्ण
पूर्ण

अटल व्योम ar9003_hw_init_hang_checks(काष्ठा ath_hw *ah)
अणु
	/*
	 * All chips support detection of BB/MAC hangs.
	 */
	ah->config.hw_hang_checks |= HW_BB_WATCHDOG;
	ah->config.hw_hang_checks |= HW_MAC_HANG;

	/*
	 * This is not required क्रम AR9580 1.0
	 */
	अगर (AR_SREV_9300_22(ah))
		ah->config.hw_hang_checks |= HW_PHYRESTART_CLC_WAR;

	अगर (AR_SREV_9330(ah))
		ah->bb_watchकरोg_समयout_ms = 85;
	अन्यथा
		ah->bb_watchकरोg_समयout_ms = 25;
पूर्ण

/*
 * MAC HW hang check
 * =================
 *
 * Signature: dcu_chain_state is 0x6 and dcu_complete_state is 0x1.
 *
 * The state of each DCU chain (mapped to TX queues) is available from these
 * DMA debug रेजिस्टरs:
 *
 * Chain 0 state : Bits 4:0   of AR_DMADBG_4
 * Chain 1 state : Bits 9:5   of AR_DMADBG_4
 * Chain 2 state : Bits 14:10 of AR_DMADBG_4
 * Chain 3 state : Bits 19:15 of AR_DMADBG_4
 * Chain 4 state : Bits 24:20 of AR_DMADBG_4
 * Chain 5 state : Bits 29:25 of AR_DMADBG_4
 * Chain 6 state : Bits 4:0   of AR_DMADBG_5
 * Chain 7 state : Bits 9:5   of AR_DMADBG_5
 * Chain 8 state : Bits 14:10 of AR_DMADBG_5
 * Chain 9 state : Bits 19:15 of AR_DMADBG_5
 *
 * The DCU chain state "0x6" means "WAIT_FRDONE" - रुको क्रम TX frame to be करोne.
 */

#घोषणा NUM_STATUS_READS 50

अटल bool ath9k_hw_verअगरy_hang(काष्ठा ath_hw *ah, अचिन्हित पूर्णांक queue)
अणु
	u32 dma_dbg_chain, dma_dbg_complete;
	u8 dcu_chain_state, dcu_complete_state;
	पूर्णांक i;

	क्रम (i = 0; i < NUM_STATUS_READS; i++) अणु
		अगर (queue < 6)
			dma_dbg_chain = REG_READ(ah, AR_DMADBG_4);
		अन्यथा
			dma_dbg_chain = REG_READ(ah, AR_DMADBG_5);

		dma_dbg_complete = REG_READ(ah, AR_DMADBG_6);

		dcu_chain_state = (dma_dbg_chain >> (5 * queue)) & 0x1f;
		dcu_complete_state = dma_dbg_complete & 0x3;

		अगर ((dcu_chain_state != 0x6) || (dcu_complete_state != 0x1))
			वापस false;
	पूर्ण

	ath_dbg(ath9k_hw_common(ah), RESET,
		"MAC Hang signature found for queue: %d\n", queue);

	वापस true;
पूर्ण

अटल bool ar9003_hw_detect_mac_hang(काष्ठा ath_hw *ah)
अणु
	u32 dma_dbg_4, dma_dbg_5, dma_dbg_6, chk_dbg;
	u8 dcu_chain_state, dcu_complete_state;
	bool dcu_रुको_frकरोne = false;
	अचिन्हित दीर्घ chk_dcu = 0;
	अचिन्हित पूर्णांक i = 0;

	dma_dbg_4 = REG_READ(ah, AR_DMADBG_4);
	dma_dbg_5 = REG_READ(ah, AR_DMADBG_5);
	dma_dbg_6 = REG_READ(ah, AR_DMADBG_6);

	dcu_complete_state = dma_dbg_6 & 0x3;
	अगर (dcu_complete_state != 0x1)
		जाओ निकास;

	क्रम (i = 0; i < ATH9K_NUM_TX_QUEUES; i++) अणु
		अगर (i < 6)
			chk_dbg = dma_dbg_4;
		अन्यथा
			chk_dbg = dma_dbg_5;

		dcu_chain_state = (chk_dbg >> (5 * i)) & 0x1f;
		अगर (dcu_chain_state == 0x6) अणु
			dcu_रुको_frकरोne = true;
			chk_dcu |= BIT(i);
		पूर्ण
	पूर्ण

	अगर ((dcu_complete_state == 0x1) && dcu_रुको_frकरोne) अणु
		क्रम_each_set_bit(i, &chk_dcu, ATH9K_NUM_TX_QUEUES) अणु
			अगर (ath9k_hw_verअगरy_hang(ah, i))
				वापस true;
		पूर्ण
	पूर्ण
निकास:
	वापस false;
पूर्ण

/* Sets up the AR9003 hardware familiy callbacks */
व्योम ar9003_hw_attach_ops(काष्ठा ath_hw *ah)
अणु
	काष्ठा ath_hw_निजी_ops *priv_ops = ath9k_hw_निजी_ops(ah);
	काष्ठा ath_hw_ops *ops = ath9k_hw_ops(ah);

	ar9003_hw_init_mode_regs(ah);

	अगर (AR_SREV_9003_PCOEM(ah)) अणु
		WARN_ON(!ah->iniPcieSerdes.ia_array);
		WARN_ON(!ah->iniPcieSerdesLowPower.ia_array);
	पूर्ण

	priv_ops->init_mode_gain_regs = ar9003_hw_init_mode_gain_regs;
	priv_ops->init_hang_checks = ar9003_hw_init_hang_checks;
	priv_ops->detect_mac_hang = ar9003_hw_detect_mac_hang;

	ops->config_pci_घातersave = ar9003_hw_configpciघातersave;

	ar9003_hw_attach_phy_ops(ah);
	ar9003_hw_attach_calib_ops(ah);
	ar9003_hw_attach_mac_ops(ah);
	ar9003_hw_attach_aic_ops(ah);
पूर्ण
