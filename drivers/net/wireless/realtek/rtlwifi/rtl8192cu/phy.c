<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/* Copyright(c) 2009-2012  Realtek Corporation.*/

#समावेश "../wifi.h"
#समावेश "../pci.h"
#समावेश "../ps.h"
#समावेश "../core.h"
#समावेश "reg.h"
#समावेश "def.h"
#समावेश "phy.h"
#समावेश "../rtl8192c/phy_common.h"
#समावेश "rf.h"
#समावेश "dm.h"
#समावेश "../rtl8192c/dm_common.h"
#समावेश "../rtl8192c/fw_common.h"
#समावेश "table.h"

u32 rtl92cu_phy_query_rf_reg(काष्ठा ieee80211_hw *hw,
			     क्रमागत radio_path rfpath, u32 regaddr, u32 biपंचांगask)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	u32 original_value, पढ़ोback_value, bitshअगरt;
	काष्ठा rtl_phy *rtlphy = &(rtlpriv->phy);

	rtl_dbg(rtlpriv, COMP_RF, DBG_TRACE,
		"regaddr(%#x), rfpath(%#x), bitmask(%#x)\n",
		regaddr, rfpath, biपंचांगask);
	अगर (rtlphy->rf_mode != RF_OP_BY_FW) अणु
		original_value = _rtl92c_phy_rf_serial_पढ़ो(hw,
							    rfpath, regaddr);
	पूर्ण अन्यथा अणु
		original_value = _rtl92c_phy_fw_rf_serial_पढ़ो(hw,
							       rfpath, regaddr);
	पूर्ण
	bitshअगरt = _rtl92c_phy_calculate_bit_shअगरt(biपंचांगask);
	पढ़ोback_value = (original_value & biपंचांगask) >> bitshअगरt;
	rtl_dbg(rtlpriv, COMP_RF, DBG_TRACE,
		"regaddr(%#x), rfpath(%#x), bitmask(%#x), original_value(%#x)\n",
		regaddr, rfpath, biपंचांगask, original_value);
	वापस पढ़ोback_value;
पूर्ण

व्योम rtl92cu_phy_set_rf_reg(काष्ठा ieee80211_hw *hw,
			    क्रमागत radio_path rfpath,
			    u32 regaddr, u32 biपंचांगask, u32 data)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	काष्ठा rtl_phy *rtlphy = &(rtlpriv->phy);
	u32 original_value, bitshअगरt;

	rtl_dbg(rtlpriv, COMP_RF, DBG_TRACE,
		"regaddr(%#x), bitmask(%#x), data(%#x), rfpath(%#x)\n",
		regaddr, biपंचांगask, data, rfpath);
	अगर (rtlphy->rf_mode != RF_OP_BY_FW) अणु
		अगर (biपंचांगask != RFREG_OFFSET_MASK) अणु
			original_value = _rtl92c_phy_rf_serial_पढ़ो(hw,
								    rfpath,
								    regaddr);
			bitshअगरt = _rtl92c_phy_calculate_bit_shअगरt(biपंचांगask);
			data =
			    ((original_value & (~biपंचांगask)) |
			     (data << bitshअगरt));
		पूर्ण
		_rtl92c_phy_rf_serial_ग_लिखो(hw, rfpath, regaddr, data);
	पूर्ण अन्यथा अणु
		अगर (biपंचांगask != RFREG_OFFSET_MASK) अणु
			original_value = _rtl92c_phy_fw_rf_serial_पढ़ो(hw,
								       rfpath,
								       regaddr);
			bitshअगरt = _rtl92c_phy_calculate_bit_shअगरt(biपंचांगask);
			data =
			    ((original_value & (~biपंचांगask)) |
			     (data << bitshअगरt));
		पूर्ण
		_rtl92c_phy_fw_rf_serial_ग_लिखो(hw, rfpath, regaddr, data);
	पूर्ण
	rtl_dbg(rtlpriv, COMP_RF, DBG_TRACE,
		"regaddr(%#x), bitmask(%#x), data(%#x), rfpath(%#x)\n",
		regaddr, biपंचांगask, data, rfpath);
पूर्ण

bool rtl92cu_phy_mac_config(काष्ठा ieee80211_hw *hw)
अणु
	bool rtstatus;

	rtstatus = _rtl92cu_phy_config_mac_with_headerfile(hw);
	वापस rtstatus;
पूर्ण

bool rtl92cu_phy_bb_config(काष्ठा ieee80211_hw *hw)
अणु
	bool rtstatus = true;
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	u16 regval;
	u32 regval32;
	u8 b_reg_hwparafile = 1;

	_rtl92c_phy_init_bb_rf_रेजिस्टर_definition(hw);
	regval = rtl_पढ़ो_word(rtlpriv, REG_SYS_FUNC_EN);
	rtl_ग_लिखो_word(rtlpriv, REG_SYS_FUNC_EN, regval | BIT(13) |
		       BIT(0) | BIT(1));
	rtl_ग_लिखो_byte(rtlpriv, REG_AFE_PLL_CTRL, 0x83);
	rtl_ग_लिखो_byte(rtlpriv, REG_AFE_PLL_CTRL + 1, 0xdb);
	rtl_ग_लिखो_byte(rtlpriv, REG_RF_CTRL, RF_EN | RF_RSTB | RF_SDMRSTB);
	rtl_ग_लिखो_byte(rtlpriv, REG_SYS_FUNC_EN, FEN_USBA | FEN_USBD |
		       FEN_BB_GLB_RSTN | FEN_BBRSTB);
	regval32 = rtl_पढ़ो_dword(rtlpriv, 0x87c);
	rtl_ग_लिखो_dword(rtlpriv, 0x87c, regval32 & (~BIT(31)));
	rtl_ग_लिखो_byte(rtlpriv, REG_LDOHCI12_CTRL, 0x0f);
	rtl_ग_लिखो_byte(rtlpriv, REG_AFE_XTAL_CTRL + 1, 0x80);
	अगर (b_reg_hwparafile == 1)
		rtstatus = _rtl92c_phy_bb8192c_config_parafile(hw);
	वापस rtstatus;
पूर्ण

bool _rtl92cu_phy_config_mac_with_headerfile(काष्ठा ieee80211_hw *hw)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	काष्ठा rtl_phy *rtlphy = &(rtlpriv->phy);
	u32 i;
	u32 arraylength;
	u32 *ptrarray;

	rtl_dbg(rtlpriv, COMP_INIT, DBG_TRACE, "Read Rtl819XMACPHY_ARRAY\n");
	arraylength =  rtlphy->hwparam_tables[MAC_REG].length ;
	ptrarray = rtlphy->hwparam_tables[MAC_REG].pdata;
	rtl_dbg(rtlpriv, COMP_INIT, DBG_TRACE, "Img:RTL8192CUMAC_2T_ARRAY\n");
	क्रम (i = 0; i < arraylength; i = i + 2)
		rtl_ग_लिखो_byte(rtlpriv, ptrarray[i], (u8) ptrarray[i + 1]);
	वापस true;
पूर्ण

bool _rtl92cu_phy_config_bb_with_headerfile(काष्ठा ieee80211_hw *hw,
					    u8 configtype)
अणु
	पूर्णांक i;
	u32 *phy_regarray_table;
	u32 *agctab_array_table;
	u16 phy_reg_arraylen, agctab_arraylen;
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	काष्ठा rtl_hal *rtlhal = rtl_hal(rtl_priv(hw));
	काष्ठा rtl_phy *rtlphy = &(rtlpriv->phy);

	अगर (IS_92C_SERIAL(rtlhal->version)) अणु
		agctab_arraylen = rtlphy->hwparam_tables[AGCTAB_2T].length;
		agctab_array_table =  rtlphy->hwparam_tables[AGCTAB_2T].pdata;
		phy_reg_arraylen = rtlphy->hwparam_tables[PHY_REG_2T].length;
		phy_regarray_table = rtlphy->hwparam_tables[PHY_REG_2T].pdata;
	पूर्ण अन्यथा अणु
		agctab_arraylen = rtlphy->hwparam_tables[AGCTAB_1T].length;
		agctab_array_table =  rtlphy->hwparam_tables[AGCTAB_1T].pdata;
		phy_reg_arraylen = rtlphy->hwparam_tables[PHY_REG_1T].length;
		phy_regarray_table = rtlphy->hwparam_tables[PHY_REG_1T].pdata;
	पूर्ण
	अगर (configtype == BASEBAND_CONFIG_PHY_REG) अणु
		क्रम (i = 0; i < phy_reg_arraylen; i = i + 2) अणु
			rtl_addr_delay(phy_regarray_table[i]);
			rtl_set_bbreg(hw, phy_regarray_table[i], MASKDWORD,
				      phy_regarray_table[i + 1]);
			udelay(1);
			rtl_dbg(rtlpriv, COMP_INIT, DBG_TRACE,
				"The phy_regarray_table[0] is %x Rtl819XPHY_REGARRAY[1] is %x\n",
				phy_regarray_table[i],
				phy_regarray_table[i + 1]);
		पूर्ण
	पूर्ण अन्यथा अगर (configtype == BASEBAND_CONFIG_AGC_TAB) अणु
		क्रम (i = 0; i < agctab_arraylen; i = i + 2) अणु
			rtl_set_bbreg(hw, agctab_array_table[i], MASKDWORD,
				      agctab_array_table[i + 1]);
			udelay(1);
			rtl_dbg(rtlpriv, COMP_INIT, DBG_TRACE,
				"The agctab_array_table[0] is %x Rtl819XPHY_REGARRAY[1] is %x\n",
				agctab_array_table[i],
				agctab_array_table[i + 1]);
		पूर्ण
	पूर्ण
	वापस true;
पूर्ण

bool _rtl92cu_phy_config_bb_with_pgheaderfile(काष्ठा ieee80211_hw *hw,
					      u8 configtype)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	काष्ठा rtl_phy *rtlphy = &(rtlpriv->phy);
	पूर्णांक i;
	u32 *phy_regarray_table_pg;
	u16 phy_regarray_pg_len;

	rtlphy->pwrgroup_cnt = 0;
	phy_regarray_pg_len = rtlphy->hwparam_tables[PHY_REG_PG].length;
	phy_regarray_table_pg = rtlphy->hwparam_tables[PHY_REG_PG].pdata;
	अगर (configtype == BASEBAND_CONFIG_PHY_REG) अणु
		क्रम (i = 0; i < phy_regarray_pg_len; i = i + 3) अणु
			rtl_addr_delay(phy_regarray_table_pg[i]);
			_rtl92c_store_pwrindex_dअगरfrate_offset(hw,
						  phy_regarray_table_pg[i],
						  phy_regarray_table_pg[i + 1],
						  phy_regarray_table_pg[i + 2]);
		पूर्ण
	पूर्ण अन्यथा अणु
		rtl_dbg(rtlpriv, COMP_SEND, DBG_TRACE,
			"configtype != BaseBand_Config_PHY_REG\n");
	पूर्ण
	वापस true;
पूर्ण

bool rtl92cu_phy_config_rf_with_headerfile(काष्ठा ieee80211_hw *hw,
					  क्रमागत radio_path rfpath)
अणु
	पूर्णांक i;
	u32 *radioa_array_table;
	u32 *radiob_array_table;
	u16 radioa_arraylen, radiob_arraylen;
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	काष्ठा rtl_hal *rtlhal = rtl_hal(rtl_priv(hw));
	काष्ठा rtl_phy *rtlphy = &(rtlpriv->phy);

	अगर (IS_92C_SERIAL(rtlhal->version)) अणु
		radioa_arraylen = rtlphy->hwparam_tables[RADIOA_2T].length;
		radioa_array_table = rtlphy->hwparam_tables[RADIOA_2T].pdata;
		radiob_arraylen = rtlphy->hwparam_tables[RADIOB_2T].length;
		radiob_array_table = rtlphy->hwparam_tables[RADIOB_2T].pdata;
		rtl_dbg(rtlpriv, COMP_INIT, DBG_TRACE,
			"Radio_A:RTL8192CURADIOA_2TARRAY\n");
		rtl_dbg(rtlpriv, COMP_INIT, DBG_TRACE,
			"Radio_B:RTL8192CU_RADIOB_2TARRAY\n");
	पूर्ण अन्यथा अणु
		radioa_arraylen = rtlphy->hwparam_tables[RADIOA_1T].length;
		radioa_array_table = rtlphy->hwparam_tables[RADIOA_1T].pdata;
		radiob_arraylen = rtlphy->hwparam_tables[RADIOB_1T].length;
		radiob_array_table = rtlphy->hwparam_tables[RADIOB_1T].pdata;
		rtl_dbg(rtlpriv, COMP_INIT, DBG_TRACE,
			"Radio_A:RTL8192CU_RADIOA_1TARRAY\n");
		rtl_dbg(rtlpriv, COMP_INIT, DBG_TRACE,
			"Radio_B:RTL8192CU_RADIOB_1TARRAY\n");
	पूर्ण
	rtl_dbg(rtlpriv, COMP_INIT, DBG_TRACE, "Radio No %x\n", rfpath);
	चयन (rfpath) अणु
	हाल RF90_PATH_A:
		क्रम (i = 0; i < radioa_arraylen; i = i + 2) अणु
			rtl_rfreg_delay(hw, rfpath, radioa_array_table[i],
					RFREG_OFFSET_MASK,
					radioa_array_table[i + 1]);
		पूर्ण
		अवरोध;
	हाल RF90_PATH_B:
		क्रम (i = 0; i < radiob_arraylen; i = i + 2) अणु
			rtl_rfreg_delay(hw, rfpath, radiob_array_table[i],
					RFREG_OFFSET_MASK,
					radiob_array_table[i + 1]);
		पूर्ण
		अवरोध;
	हाल RF90_PATH_C:
	हाल RF90_PATH_D:
		pr_err("switch case %#x not processed\n", rfpath);
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण
	वापस true;
पूर्ण

व्योम rtl92cu_phy_set_bw_mode_callback(काष्ठा ieee80211_hw *hw)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	काष्ठा rtl_hal *rtlhal = rtl_hal(rtl_priv(hw));
	काष्ठा rtl_phy *rtlphy = &(rtlpriv->phy);
	काष्ठा rtl_mac *mac = rtl_mac(rtl_priv(hw));
	u8 reg_bw_opmode;
	u8 reg_prsr_rsc;

	rtl_dbg(rtlpriv, COMP_SCAN, DBG_TRACE, "Switch to %s bandwidth\n",
		rtlphy->current_chan_bw == HT_CHANNEL_WIDTH_20 ?
		"20MHz" : "40MHz");
	अगर (is_hal_stop(rtlhal)) अणु
		rtlphy->set_bwmode_inprogress = false;
		वापस;
	पूर्ण
	reg_bw_opmode = rtl_पढ़ो_byte(rtlpriv, REG_BWOPMODE);
	reg_prsr_rsc = rtl_पढ़ो_byte(rtlpriv, REG_RRSR + 2);
	चयन (rtlphy->current_chan_bw) अणु
	हाल HT_CHANNEL_WIDTH_20:
		reg_bw_opmode |= BW_OPMODE_20MHZ;
		rtl_ग_लिखो_byte(rtlpriv, REG_BWOPMODE, reg_bw_opmode);
		अवरोध;
	हाल HT_CHANNEL_WIDTH_20_40:
		reg_bw_opmode &= ~BW_OPMODE_20MHZ;
		rtl_ग_लिखो_byte(rtlpriv, REG_BWOPMODE, reg_bw_opmode);
		reg_prsr_rsc =
		    (reg_prsr_rsc & 0x90) | (mac->cur_40_prime_sc << 5);
		rtl_ग_लिखो_byte(rtlpriv, REG_RRSR + 2, reg_prsr_rsc);
		अवरोध;
	शेष:
		pr_err("unknown bandwidth: %#X\n",
		       rtlphy->current_chan_bw);
		अवरोध;
	पूर्ण
	चयन (rtlphy->current_chan_bw) अणु
	हाल HT_CHANNEL_WIDTH_20:
		rtl_set_bbreg(hw, RFPGA0_RFMOD, BRFMOD, 0x0);
		rtl_set_bbreg(hw, RFPGA1_RFMOD, BRFMOD, 0x0);
		rtl_set_bbreg(hw, RFPGA0_ANALOGPARAMETER2, BIT(10), 1);
		अवरोध;
	हाल HT_CHANNEL_WIDTH_20_40:
		rtl_set_bbreg(hw, RFPGA0_RFMOD, BRFMOD, 0x1);
		rtl_set_bbreg(hw, RFPGA1_RFMOD, BRFMOD, 0x1);
		rtl_set_bbreg(hw, RCCK0_SYSTEM, BCCK_SIDEBAND,
			      (mac->cur_40_prime_sc >> 1));
		rtl_set_bbreg(hw, ROFDM1_LSTF, 0xC00, mac->cur_40_prime_sc);
		rtl_set_bbreg(hw, RFPGA0_ANALOGPARAMETER2, BIT(10), 0);
		rtl_set_bbreg(hw, 0x818, (BIT(26) | BIT(27)),
			      (mac->cur_40_prime_sc ==
			       HAL_PRIME_CHNL_OFFSET_LOWER) ? 2 : 1);
		अवरोध;
	शेष:
		pr_err("unknown bandwidth: %#X\n",
		       rtlphy->current_chan_bw);
		अवरोध;
	पूर्ण
	rtl92cu_phy_rf6052_set_bandwidth(hw, rtlphy->current_chan_bw);
	rtlphy->set_bwmode_inprogress = false;
	rtl_dbg(rtlpriv, COMP_SCAN, DBG_TRACE, "<==\n");
पूर्ण

व्योम rtl92cu_bb_block_on(काष्ठा ieee80211_hw *hw)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);

	mutex_lock(&rtlpriv->io.bb_mutex);
	rtl_set_bbreg(hw, RFPGA0_RFMOD, BCCKEN, 0x1);
	rtl_set_bbreg(hw, RFPGA0_RFMOD, BOFDMEN, 0x1);
	mutex_unlock(&rtlpriv->io.bb_mutex);
पूर्ण

व्योम _rtl92cu_phy_lc_calibrate(काष्ठा ieee80211_hw *hw, bool is2t)
अणु
	u8 पंचांगpreg;
	u32 rf_a_mode = 0, rf_b_mode = 0, lc_cal;
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);

	पंचांगpreg = rtl_पढ़ो_byte(rtlpriv, 0xd03);

	अगर ((पंचांगpreg & 0x70) != 0)
		rtl_ग_लिखो_byte(rtlpriv, 0xd03, पंचांगpreg & 0x8F);
	अन्यथा
		rtl_ग_लिखो_byte(rtlpriv, REG_TXPAUSE, 0xFF);

	अगर ((पंचांगpreg & 0x70) != 0) अणु
		rf_a_mode = rtl_get_rfreg(hw, RF90_PATH_A, 0x00, MASK12BITS);
		अगर (is2t)
			rf_b_mode = rtl_get_rfreg(hw, RF90_PATH_B, 0x00,
						  MASK12BITS);
		rtl_set_rfreg(hw, RF90_PATH_A, 0x00, MASK12BITS,
			      (rf_a_mode & 0x8FFFF) | 0x10000);
		अगर (is2t)
			rtl_set_rfreg(hw, RF90_PATH_B, 0x00, MASK12BITS,
				      (rf_b_mode & 0x8FFFF) | 0x10000);
	पूर्ण
	lc_cal = rtl_get_rfreg(hw, RF90_PATH_A, 0x18, MASK12BITS);
	rtl_set_rfreg(hw, RF90_PATH_A, 0x18, MASK12BITS, lc_cal | 0x08000);
	mdelay(100);
	अगर ((पंचांगpreg & 0x70) != 0) अणु
		rtl_ग_लिखो_byte(rtlpriv, 0xd03, पंचांगpreg);
		rtl_set_rfreg(hw, RF90_PATH_A, 0x00, MASK12BITS, rf_a_mode);
		अगर (is2t)
			rtl_set_rfreg(hw, RF90_PATH_B, 0x00, MASK12BITS,
				      rf_b_mode);
	पूर्ण अन्यथा अणु
		rtl_ग_लिखो_byte(rtlpriv, REG_TXPAUSE, 0x00);
	पूर्ण
पूर्ण

अटल bool _rtl92cu_phy_set_rf_घातer_state(काष्ठा ieee80211_hw *hw,
					    क्रमागत rf_pwrstate rfpwr_state)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	काष्ठा rtl_pci_priv *pcipriv = rtl_pcipriv(hw);
	काष्ठा rtl_mac *mac = rtl_mac(rtl_priv(hw));
	काष्ठा rtl_ps_ctl *ppsc = rtl_psc(rtl_priv(hw));
	bool bresult = true;
	u8 i, queue_id;
	काष्ठा rtl8192_tx_ring *ring = शून्य;

	चयन (rfpwr_state) अणु
	हाल ERFON:
		अगर ((ppsc->rfpwr_state == ERFOFF) &&
		    RT_IN_PS_LEVEL(ppsc, RT_RF_OFF_LEVL_HALT_NIC)) अणु
			bool rtstatus;
			u32 init_count = 0;

			करो अणु
				init_count++;
				rtl_dbg(rtlpriv, COMP_RF, DBG_DMESG,
					"IPS Set eRf nic enable\n");
				rtstatus = rtl_ps_enable_nic(hw);
			पूर्ण जबतक (!rtstatus && (init_count < 10));
			RT_CLEAR_PS_LEVEL(ppsc,
					  RT_RF_OFF_LEVL_HALT_NIC);
		पूर्ण अन्यथा अणु
			rtl_dbg(rtlpriv, COMP_RF, DBG_DMESG,
				"Set ERFON slept:%d ms\n",
				jअगरfies_to_msecs(jअगरfies -
						 ppsc->last_sleep_jअगरfies));
			ppsc->last_awake_jअगरfies = jअगरfies;
			rtl92ce_phy_set_rf_on(hw);
		पूर्ण
		अगर (mac->link_state == MAC80211_LINKED) अणु
			rtlpriv->cfg->ops->led_control(hw,
						       LED_CTL_LINK);
		पूर्ण अन्यथा अणु
			rtlpriv->cfg->ops->led_control(hw,
						       LED_CTL_NO_LINK);
		पूर्ण
		अवरोध;
	हाल ERFOFF:
		क्रम (queue_id = 0, i = 0;
		     queue_id < RTL_PCI_MAX_TX_QUEUE_COUNT;) अणु
			ring = &pcipriv->dev.tx_ring[queue_id];
			अगर (skb_queue_len(&ring->queue) == 0 ||
				queue_id == BEACON_QUEUE) अणु
				queue_id++;
				जारी;
			पूर्ण अन्यथा अणु
				rtl_dbg(rtlpriv, COMP_ERR, DBG_WARNING,
					"eRf Off/Sleep: %d times TcbBusyQueue[%d] =%d before doze!\n",
					i + 1,
					queue_id,
					skb_queue_len(&ring->queue));
				udelay(10);
				i++;
			पूर्ण
			अगर (i >= MAX_DOZE_WAITING_TIMES_9x) अणु
				rtl_dbg(rtlpriv, COMP_ERR, DBG_WARNING,
					"ERFOFF: %d times TcbBusyQueue[%d] = %d !\n",
					MAX_DOZE_WAITING_TIMES_9x,
					queue_id,
					skb_queue_len(&ring->queue));
				अवरोध;
			पूर्ण
		पूर्ण
		अगर (ppsc->reg_rfps_level & RT_RF_OFF_LEVL_HALT_NIC) अणु
			rtl_dbg(rtlpriv, COMP_RF, DBG_DMESG,
				"IPS Set eRf nic disable\n");
			rtl_ps_disable_nic(hw);
			RT_SET_PS_LEVEL(ppsc, RT_RF_OFF_LEVL_HALT_NIC);
		पूर्ण अन्यथा अणु
			अगर (ppsc->rfoff_reason == RF_CHANGE_BY_IPS) अणु
				rtlpriv->cfg->ops->led_control(hw,
							 LED_CTL_NO_LINK);
			पूर्ण अन्यथा अणु
				rtlpriv->cfg->ops->led_control(hw,
							 LED_CTL_POWER_OFF);
			पूर्ण
		पूर्ण
		अवरोध;
	हाल ERFSLEEP:
		अगर (ppsc->rfpwr_state == ERFOFF)
			वापस false;
		क्रम (queue_id = 0, i = 0;
		     queue_id < RTL_PCI_MAX_TX_QUEUE_COUNT;) अणु
			ring = &pcipriv->dev.tx_ring[queue_id];
			अगर (skb_queue_len(&ring->queue) == 0) अणु
				queue_id++;
				जारी;
			पूर्ण अन्यथा अणु
				rtl_dbg(rtlpriv, COMP_ERR, DBG_WARNING,
					"eRf Off/Sleep: %d times TcbBusyQueue[%d] =%d before doze!\n",
					i + 1, queue_id,
					skb_queue_len(&ring->queue));
				udelay(10);
				i++;
			पूर्ण
			अगर (i >= MAX_DOZE_WAITING_TIMES_9x) अणु
				rtl_dbg(rtlpriv, COMP_ERR, DBG_WARNING,
					"ERFSLEEP: %d times TcbBusyQueue[%d] = %d !\n",
					MAX_DOZE_WAITING_TIMES_9x,
					queue_id,
					skb_queue_len(&ring->queue));
				अवरोध;
			पूर्ण
		पूर्ण
		rtl_dbg(rtlpriv, COMP_RF, DBG_DMESG,
			"Set ERFSLEEP awaked:%d ms\n",
			jअगरfies_to_msecs(jअगरfies - ppsc->last_awake_jअगरfies));
		ppsc->last_sleep_jअगरfies = jअगरfies;
		_rtl92c_phy_set_rf_sleep(hw);
		अवरोध;
	शेष:
		pr_err("switch case %#x not processed\n",
		       rfpwr_state);
		bresult = false;
		अवरोध;
	पूर्ण
	अगर (bresult)
		ppsc->rfpwr_state = rfpwr_state;
	वापस bresult;
पूर्ण

bool rtl92cu_phy_set_rf_घातer_state(काष्ठा ieee80211_hw *hw,
				    क्रमागत rf_pwrstate rfpwr_state)
अणु
	काष्ठा rtl_ps_ctl *ppsc = rtl_psc(rtl_priv(hw));
	bool bresult = false;

	अगर (rfpwr_state == ppsc->rfpwr_state)
		वापस bresult;
	bresult = _rtl92cu_phy_set_rf_घातer_state(hw, rfpwr_state);
	वापस bresult;
पूर्ण
