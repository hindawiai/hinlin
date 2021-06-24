<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/* Copyright(c) 2009-2012  Realtek Corporation.*/

#समावेश "wifi.h"
#समावेश "core.h"
#समावेश "cam.h"
#समावेश "base.h"
#समावेश "ps.h"
#समावेश "pwrseqcmd.h"

#समावेश "btcoexist/rtl_btc.h"
#समावेश <linux/firmware.h>
#समावेश <linux/export.h>
#समावेश <net/cfg80211.h>

u8 channel5g[CHANNEL_MAX_NUMBER_5G] = अणु
	36, 38, 40, 42, 44, 46, 48,		/* Band 1 */
	52, 54, 56, 58, 60, 62, 64,		/* Band 2 */
	100, 102, 104, 106, 108, 110, 112,	/* Band 3 */
	116, 118, 120, 122, 124, 126, 128,	/* Band 3 */
	132, 134, 136, 138, 140, 142, 144,	/* Band 3 */
	149, 151, 153, 155, 157, 159, 161,	/* Band 4 */
	165, 167, 169, 171, 173, 175, 177	/* Band 4 */
पूर्ण;
EXPORT_SYMBOL(channel5g);

u8 channel5g_80m[CHANNEL_MAX_NUMBER_5G_80M] = अणु
	42, 58, 106, 122, 138, 155, 171
पूर्ण;
EXPORT_SYMBOL(channel5g_80m);

व्योम rtl_addr_delay(u32 addr)
अणु
	अगर (addr == 0xfe)
		mdelay(50);
	अन्यथा अगर (addr == 0xfd)
		msleep(5);
	अन्यथा अगर (addr == 0xfc)
		msleep(1);
	अन्यथा अगर (addr == 0xfb)
		usleep_range(50, 100);
	अन्यथा अगर (addr == 0xfa)
		usleep_range(5, 10);
	अन्यथा अगर (addr == 0xf9)
		usleep_range(1, 2);
पूर्ण
EXPORT_SYMBOL(rtl_addr_delay);

व्योम rtl_rfreg_delay(काष्ठा ieee80211_hw *hw, क्रमागत radio_path rfpath, u32 addr,
		     u32 mask, u32 data)
अणु
	अगर (addr >= 0xf9 && addr <= 0xfe) अणु
		rtl_addr_delay(addr);
	पूर्ण अन्यथा अणु
		rtl_set_rfreg(hw, rfpath, addr, mask, data);
		udelay(1);
	पूर्ण
पूर्ण
EXPORT_SYMBOL(rtl_rfreg_delay);

व्योम rtl_bb_delay(काष्ठा ieee80211_hw *hw, u32 addr, u32 data)
अणु
	अगर (addr >= 0xf9 && addr <= 0xfe) अणु
		rtl_addr_delay(addr);
	पूर्ण अन्यथा अणु
		rtl_set_bbreg(hw, addr, MASKDWORD, data);
		udelay(1);
	पूर्ण
पूर्ण
EXPORT_SYMBOL(rtl_bb_delay);

अटल व्योम rtl_fw_करो_work(स्थिर काष्ठा firmware *firmware, व्योम *context,
			   bool is_wow)
अणु
	काष्ठा ieee80211_hw *hw = context;
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	पूर्णांक err;

	rtl_dbg(rtlpriv, COMP_ERR, DBG_LOUD,
		"Firmware callback routine entered!\n");
	अगर (!firmware) अणु
		अगर (rtlpriv->cfg->alt_fw_name) अणु
			err = request_firmware(&firmware,
					       rtlpriv->cfg->alt_fw_name,
					       rtlpriv->io.dev);
			pr_info("Loading alternative firmware %s\n",
				rtlpriv->cfg->alt_fw_name);
			अगर (!err)
				जाओ found_alt;
		पूर्ण
		pr_err("Selected firmware is not available\n");
		rtlpriv->max_fw_size = 0;
		जाओ निकास;
	पूर्ण
found_alt:
	अगर (firmware->size > rtlpriv->max_fw_size) अणु
		pr_err("Firmware is too big!\n");
		release_firmware(firmware);
		जाओ निकास;
	पूर्ण
	अगर (!is_wow) अणु
		स_नकल(rtlpriv->rtlhal.pfirmware, firmware->data,
		       firmware->size);
		rtlpriv->rtlhal.fwsize = firmware->size;
	पूर्ण अन्यथा अणु
		स_नकल(rtlpriv->rtlhal.wowlan_firmware, firmware->data,
		       firmware->size);
		rtlpriv->rtlhal.wowlan_fwsize = firmware->size;
	पूर्ण
	release_firmware(firmware);

निकास:
	complete(&rtlpriv->firmware_loading_complete);
पूर्ण

व्योम rtl_fw_cb(स्थिर काष्ठा firmware *firmware, व्योम *context)
अणु
	rtl_fw_करो_work(firmware, context, false);
पूर्ण
EXPORT_SYMBOL(rtl_fw_cb);

व्योम rtl_wowlan_fw_cb(स्थिर काष्ठा firmware *firmware, व्योम *context)
अणु
	rtl_fw_करो_work(firmware, context, true);
पूर्ण
EXPORT_SYMBOL(rtl_wowlan_fw_cb);

/*mutex क्रम start & stop is must here. */
अटल पूर्णांक rtl_op_start(काष्ठा ieee80211_hw *hw)
अणु
	पूर्णांक err = 0;
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	काष्ठा rtl_hal *rtlhal = rtl_hal(rtl_priv(hw));

	अगर (!is_hal_stop(rtlhal))
		वापस 0;
	अगर (!test_bit(RTL_STATUS_INTERFACE_START, &rtlpriv->status))
		वापस 0;
	mutex_lock(&rtlpriv->locks.conf_mutex);
	err = rtlpriv->पूर्णांकf_ops->adapter_start(hw);
	अगर (!err)
		rtl_watch_करोg_समयr_callback(&rtlpriv->works.watchकरोg_समयr);
	mutex_unlock(&rtlpriv->locks.conf_mutex);
	वापस err;
पूर्ण

अटल व्योम rtl_op_stop(काष्ठा ieee80211_hw *hw)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	काष्ठा rtl_mac *mac = rtl_mac(rtl_priv(hw));
	काष्ठा rtl_hal *rtlhal = rtl_hal(rtl_priv(hw));
	काष्ठा rtl_ps_ctl *ppsc = rtl_psc(rtl_priv(hw));
	bool support_remote_wakeup = false;

	अगर (is_hal_stop(rtlhal))
		वापस;

	rtlpriv->cfg->ops->get_hw_reg(hw, HAL_DEF_WOWLAN,
				      (u8 *)(&support_remote_wakeup));
	/* here is must, because adhoc करो stop and start,
	 * but stop with RFOFF may cause something wrong,
	 * like adhoc TP
	 */
	अगर (unlikely(ppsc->rfpwr_state == ERFOFF))
		rtl_ips_nic_on(hw);

	mutex_lock(&rtlpriv->locks.conf_mutex);
	/* अगर wowlan supported, DON'T clear connected info */
	अगर (!(support_remote_wakeup &&
	      rtlhal->enter_pnp_sleep)) अणु
		mac->link_state = MAC80211_NOLINK;
		eth_zero_addr(mac->bssid);
		mac->venकरोr = PEER_UNKNOWN;

		/* reset sec info */
		rtl_cam_reset_sec_info(hw);

		rtl_deinit_deferred_work(hw, false);
	पूर्ण
	rtlpriv->पूर्णांकf_ops->adapter_stop(hw);

	mutex_unlock(&rtlpriv->locks.conf_mutex);
पूर्ण

अटल व्योम rtl_op_tx(काष्ठा ieee80211_hw *hw,
		      काष्ठा ieee80211_tx_control *control,
		      काष्ठा sk_buff *skb)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	काष्ठा rtl_hal *rtlhal = rtl_hal(rtl_priv(hw));
	काष्ठा rtl_ps_ctl *ppsc = rtl_psc(rtl_priv(hw));
	काष्ठा rtl_tcb_desc tcb_desc;

	स_रखो(&tcb_desc, 0, माप(काष्ठा rtl_tcb_desc));

	अगर (unlikely(is_hal_stop(rtlhal) || ppsc->rfpwr_state != ERFON))
		जाओ err_मुक्त;

	अगर (!test_bit(RTL_STATUS_INTERFACE_START, &rtlpriv->status))
		जाओ err_मुक्त;

	अगर (!rtlpriv->पूर्णांकf_ops->रुकोq_insert(hw, control->sta, skb))
		rtlpriv->पूर्णांकf_ops->adapter_tx(hw, control->sta, skb, &tcb_desc);
	वापस;

err_मुक्त:
	dev_kमुक्त_skb_any(skb);
पूर्ण

अटल पूर्णांक rtl_op_add_पूर्णांकerface(काष्ठा ieee80211_hw *hw,
		काष्ठा ieee80211_vअगर *vअगर)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	काष्ठा rtl_mac *mac = rtl_mac(rtl_priv(hw));
	पूर्णांक err = 0;
	u8 retry_limit = 0x30;

	अगर (mac->vअगर) अणु
		rtl_dbg(rtlpriv, COMP_ERR, DBG_WARNING,
			"vif has been set!! mac->vif = 0x%p\n", mac->vअगर);
		वापस -EOPNOTSUPP;
	पूर्ण

	vअगर->driver_flags |= IEEE80211_VIF_BEACON_FILTER;

	rtl_ips_nic_on(hw);

	mutex_lock(&rtlpriv->locks.conf_mutex);
	चयन (ieee80211_vअगर_type_p2p(vअगर)) अणु
	हाल NL80211_IFTYPE_P2P_CLIENT:
		mac->p2p = P2P_ROLE_CLIENT;
		fallthrough;
	हाल NL80211_IFTYPE_STATION:
		अगर (mac->beacon_enabled == 1) अणु
			rtl_dbg(rtlpriv, COMP_MAC80211, DBG_LOUD,
				"NL80211_IFTYPE_STATION\n");
			mac->beacon_enabled = 0;
			rtlpriv->cfg->ops->update_पूर्णांकerrupt_mask(hw, 0,
					rtlpriv->cfg->maps[RTL_IBSS_INT_MASKS]);
		पूर्ण
		अवरोध;
	हाल NL80211_IFTYPE_ADHOC:
		rtl_dbg(rtlpriv, COMP_MAC80211, DBG_LOUD,
			"NL80211_IFTYPE_ADHOC\n");

		mac->link_state = MAC80211_LINKED;
		rtlpriv->cfg->ops->set_bcn_reg(hw);
		अगर (rtlpriv->rtlhal.current_bandtype == BAND_ON_2_4G)
			mac->basic_rates = 0xfff;
		अन्यथा
			mac->basic_rates = 0xff0;
		rtlpriv->cfg->ops->set_hw_reg(hw, HW_VAR_BASIC_RATE,
				(u8 *)(&mac->basic_rates));

		retry_limit = 0x07;
		अवरोध;
	हाल NL80211_IFTYPE_P2P_GO:
		mac->p2p = P2P_ROLE_GO;
		fallthrough;
	हाल NL80211_IFTYPE_AP:
		rtl_dbg(rtlpriv, COMP_MAC80211, DBG_LOUD,
			"NL80211_IFTYPE_AP\n");

		mac->link_state = MAC80211_LINKED;
		rtlpriv->cfg->ops->set_bcn_reg(hw);
		अगर (rtlpriv->rtlhal.current_bandtype == BAND_ON_2_4G)
			mac->basic_rates = 0xfff;
		अन्यथा
			mac->basic_rates = 0xff0;
		rtlpriv->cfg->ops->set_hw_reg(hw, HW_VAR_BASIC_RATE,
					      (u8 *)(&mac->basic_rates));

		retry_limit = 0x07;
		अवरोध;
	हाल NL80211_IFTYPE_MESH_POINT:
		rtl_dbg(rtlpriv, COMP_MAC80211, DBG_LOUD,
			"NL80211_IFTYPE_MESH_POINT\n");

		mac->link_state = MAC80211_LINKED;
		rtlpriv->cfg->ops->set_bcn_reg(hw);
		अगर (rtlpriv->rtlhal.current_bandtype == BAND_ON_2_4G)
			mac->basic_rates = 0xfff;
		अन्यथा
			mac->basic_rates = 0xff0;
		rtlpriv->cfg->ops->set_hw_reg(hw, HW_VAR_BASIC_RATE,
				(u8 *)(&mac->basic_rates));

		retry_limit = 0x07;
		अवरोध;
	शेष:
		pr_err("operation mode %d is not supported!\n",
		       vअगर->type);
		err = -EOPNOTSUPP;
		जाओ out;
	पूर्ण

	अगर (mac->p2p) अणु
		rtl_dbg(rtlpriv, COMP_MAC80211, DBG_LOUD,
			"p2p role %x\n", vअगर->type);
		mac->basic_rates = 0xff0;/*disable cck rate क्रम p2p*/
		rtlpriv->cfg->ops->set_hw_reg(hw, HW_VAR_BASIC_RATE,
				(u8 *)(&mac->basic_rates));
	पूर्ण
	mac->vअगर = vअगर;
	mac->opmode = vअगर->type;
	rtlpriv->cfg->ops->set_network_type(hw, vअगर->type);
	स_नकल(mac->mac_addr, vअगर->addr, ETH_ALEN);
	rtlpriv->cfg->ops->set_hw_reg(hw, HW_VAR_ETHER_ADDR, mac->mac_addr);

	mac->retry_दीर्घ = retry_limit;
	mac->retry_लघु = retry_limit;
	rtlpriv->cfg->ops->set_hw_reg(hw, HW_VAR_RETRY_LIMIT,
			(u8 *)(&retry_limit));
out:
	mutex_unlock(&rtlpriv->locks.conf_mutex);
	वापस err;
पूर्ण

अटल व्योम rtl_op_हटाओ_पूर्णांकerface(काष्ठा ieee80211_hw *hw,
		काष्ठा ieee80211_vअगर *vअगर)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	काष्ठा rtl_mac *mac = rtl_mac(rtl_priv(hw));

	mutex_lock(&rtlpriv->locks.conf_mutex);

	/* Free beacon resources */
	अगर (vअगर->type == NL80211_IFTYPE_AP ||
	    vअगर->type == NL80211_IFTYPE_ADHOC ||
	    vअगर->type == NL80211_IFTYPE_MESH_POINT) अणु
		अगर (mac->beacon_enabled == 1) अणु
			mac->beacon_enabled = 0;
			rtlpriv->cfg->ops->update_पूर्णांकerrupt_mask(hw, 0,
					rtlpriv->cfg->maps[RTL_IBSS_INT_MASKS]);
		पूर्ण
	पूर्ण

	/*
	 *Note: We assume NL80211_IFTYPE_UNSPECIFIED as
	 *NO LINK क्रम our hardware.
	 */
	mac->p2p = 0;
	mac->vअगर = शून्य;
	mac->link_state = MAC80211_NOLINK;
	eth_zero_addr(mac->bssid);
	mac->venकरोr = PEER_UNKNOWN;
	mac->opmode = NL80211_IFTYPE_UNSPECIFIED;
	rtlpriv->cfg->ops->set_network_type(hw, mac->opmode);

	mutex_unlock(&rtlpriv->locks.conf_mutex);
पूर्ण

अटल पूर्णांक rtl_op_change_पूर्णांकerface(काष्ठा ieee80211_hw *hw,
				   काष्ठा ieee80211_vअगर *vअगर,
				   क्रमागत nl80211_अगरtype new_type, bool p2p)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	पूर्णांक ret;

	rtl_op_हटाओ_पूर्णांकerface(hw, vअगर);

	vअगर->type = new_type;
	vअगर->p2p = p2p;
	ret = rtl_op_add_पूर्णांकerface(hw, vअगर);
	rtl_dbg(rtlpriv, COMP_MAC80211, DBG_LOUD,
		"p2p  %x\n", p2p);
	वापस ret;
पूर्ण

#अगर_घोषित CONFIG_PM
अटल u16 crc16_ccitt(u8 data, u16 crc)
अणु
	u8 shअगरt_in, data_bit, crc_bit11, crc_bit4, crc_bit15;
	u8 i;
	u16 result;

	क्रम (i = 0; i < 8; i++) अणु
		crc_bit15 = ((crc & BIT(15)) ? 1 : 0);
		data_bit  = (data & (BIT(0) << i) ? 1 : 0);
		shअगरt_in = crc_bit15 ^ data_bit;

		result = crc << 1;
		अगर (shअगरt_in == 0)
			result &= (~BIT(0));
		अन्यथा
			result |= BIT(0);

		crc_bit11 = ((crc & BIT(11)) ? 1 : 0) ^ shअगरt_in;
		अगर (crc_bit11 == 0)
			result &= (~BIT(12));
		अन्यथा
			result |= BIT(12);

		crc_bit4 = ((crc & BIT(4)) ? 1 : 0) ^ shअगरt_in;
		अगर (crc_bit4 == 0)
			result &= (~BIT(5));
		अन्यथा
			result |= BIT(5);

		crc = result;
	पूर्ण

	वापस crc;
पूर्ण

अटल u16 _calculate_wol_pattern_crc(u8 *pattern, u16 len)
अणु
	u16 crc = 0xffff;
	u32 i;

	क्रम (i = 0; i < len; i++)
		crc = crc16_ccitt(pattern[i], crc);

	crc = ~crc;

	वापस crc;
पूर्ण

अटल व्योम _rtl_add_wowlan_patterns(काष्ठा ieee80211_hw *hw,
				     काष्ठा cfg80211_wowlan *wow)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	काष्ठा rtl_mac *mac = &rtlpriv->mac80211;
	काष्ठा cfg80211_pkt_pattern *patterns = wow->patterns;
	काष्ठा rtl_wow_pattern rtl_pattern;
	स्थिर u8 *pattern_os, *mask_os;
	u8 mask[MAX_WOL_BIT_MASK_SIZE] = अणु0पूर्ण;
	u8 content[MAX_WOL_PATTERN_SIZE] = अणु0पूर्ण;
	u8 broadcast_addr[6] = अणु0xff, 0xff, 0xff, 0xff, 0xff, 0xffपूर्ण;
	u8 multicast_addr1[2] = अणु0x33, 0x33पूर्ण;
	u8 multicast_addr2[3] = अणु0x01, 0x00, 0x5eपूर्ण;
	u8 i, mask_len;
	u16 j, len;

	क्रम (i = 0; i < wow->n_patterns; i++) अणु
		स_रखो(&rtl_pattern, 0, माप(काष्ठा rtl_wow_pattern));
		स_रखो(mask, 0, MAX_WOL_BIT_MASK_SIZE);
		अगर (patterns[i].pattern_len < 0 ||
		    patterns[i].pattern_len > MAX_WOL_PATTERN_SIZE) अणु
			rtl_dbg(rtlpriv, COMP_POWER, DBG_WARNING,
				"Pattern[%d] is too long\n", i);
			जारी;
		पूर्ण
		pattern_os = patterns[i].pattern;
		mask_len = DIV_ROUND_UP(patterns[i].pattern_len, 8);
		mask_os = patterns[i].mask;
		RT_PRINT_DATA(rtlpriv, COMP_POWER, DBG_TRACE,
			      "pattern content\n", pattern_os,
			       patterns[i].pattern_len);
		RT_PRINT_DATA(rtlpriv, COMP_POWER, DBG_TRACE,
			      "mask content\n", mask_os, mask_len);
		/* 1. unicast? multicast? or broadcast? */
		अगर (स_भेद(pattern_os, broadcast_addr, 6) == 0)
			rtl_pattern.type = BROADCAST_PATTERN;
		अन्यथा अगर (स_भेद(pattern_os, multicast_addr1, 2) == 0 ||
			 स_भेद(pattern_os, multicast_addr2, 3) == 0)
			rtl_pattern.type = MULTICAST_PATTERN;
		अन्यथा अगर  (स_भेद(pattern_os, mac->mac_addr, 6) == 0)
			rtl_pattern.type = UNICAST_PATTERN;
		अन्यथा
			rtl_pattern.type = UNKNOWN_TYPE;

		/* 2. translate mask_from_os to mask_क्रम_hw */

/******************************************************************************
 * pattern from OS uses 'ethenet frame', like this:

		   |    6   |    6   |   2  |     20    |  Variable  |	4  |
		   |--------+--------+------+-----------+------------+-----|
		   |    802.3 Mac Header    | IP Header | TCP Packet | FCS |
		   |   DA   |   SA   | Type |

 * BUT, packet catched by our HW is in '802.11 frame', begin from LLC,

	|     24 or 30      |    6   |   2  |     20    |  Variable  |  4  |
	|-------------------+--------+------+-----------+------------+-----|
	| 802.11 MAC Header |       LLC     | IP Header | TCP Packet | FCS |
			    | Others | Tpye |

 * Thereक्रमe, we need translate mask_from_OS to mask_to_hw.
 * We should left-shअगरt mask by 6 bits, then set the new bit[0~5] = 0,
 * because new mask[0~5] means 'SA', but our HW packet begins from LLC,
 * bit[0~5] corresponds to first 6 Bytes in LLC, they just करोn't match.
 ******************************************************************************/

		/* Shअगरt 6 bits */
		क्रम (j = 0; j < mask_len - 1; j++) अणु
			mask[j] = mask_os[j] >> 6;
			mask[j] |= (mask_os[j + 1] & 0x3F) << 2;
		पूर्ण
		mask[j] = (mask_os[j] >> 6) & 0x3F;
		/* Set bit 0-5 to zero */
		mask[0] &= 0xC0;

		RT_PRINT_DATA(rtlpriv, COMP_POWER, DBG_TRACE,
			      "mask to hw\n", mask, mask_len);
		क्रम (j = 0; j < (MAX_WOL_BIT_MASK_SIZE + 1) / 4; j++) अणु
			rtl_pattern.mask[j] = mask[j * 4];
			rtl_pattern.mask[j] |= (mask[j * 4 + 1] << 8);
			rtl_pattern.mask[j] |= (mask[j * 4 + 2] << 16);
			rtl_pattern.mask[j] |= (mask[j * 4 + 3] << 24);
		पूर्ण

		/* To get the wake up pattern from the mask.
		 * We करो not count first 12 bits which means
		 * DA[6] and SA[6] in the pattern to match HW design.
		 */
		len = 0;
		क्रम (j = 12; j < patterns[i].pattern_len; j++) अणु
			अगर ((mask_os[j / 8] >> (j % 8)) & 0x01) अणु
				content[len] = pattern_os[j];
				len++;
			पूर्ण
		पूर्ण

		RT_PRINT_DATA(rtlpriv, COMP_POWER, DBG_TRACE,
			      "pattern to hw\n", content, len);
		/* 3. calculate crc */
		rtl_pattern.crc = _calculate_wol_pattern_crc(content, len);
		rtl_dbg(rtlpriv, COMP_POWER, DBG_TRACE,
			"CRC_Remainder = 0x%x\n", rtl_pattern.crc);

		/* 4. ग_लिखो crc & mask_क्रम_hw to hw */
		rtlpriv->cfg->ops->add_wowlan_pattern(hw, &rtl_pattern, i);
	पूर्ण
	rtl_ग_लिखो_byte(rtlpriv, 0x698, wow->n_patterns);
पूर्ण

अटल पूर्णांक rtl_op_suspend(काष्ठा ieee80211_hw *hw,
			  काष्ठा cfg80211_wowlan *wow)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	काष्ठा rtl_hal *rtlhal = rtl_hal(rtlpriv);
	काष्ठा rtl_ps_ctl *ppsc = rtl_psc(rtl_priv(hw));

	rtl_dbg(rtlpriv, COMP_POWER, DBG_DMESG, "\n");
	अगर (WARN_ON(!wow))
		वापस -EINVAL;

	/* to resolve s4 can not wake up*/
	rtlhal->last_suspend_sec = kसमय_get_real_seconds();

	अगर ((ppsc->wo_wlan_mode & WAKE_ON_PATTERN_MATCH) && wow->n_patterns)
		_rtl_add_wowlan_patterns(hw, wow);

	rtlhal->driver_is_goingto_unload = true;
	rtlhal->enter_pnp_sleep = true;

	rtl_lps_leave(hw, true);
	rtl_op_stop(hw);
	device_set_wakeup_enable(wiphy_dev(hw->wiphy), true);
	वापस 0;
पूर्ण

अटल पूर्णांक rtl_op_resume(काष्ठा ieee80211_hw *hw)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	काष्ठा rtl_hal *rtlhal = rtl_hal(rtlpriv);
	काष्ठा rtl_mac *mac = rtl_mac(rtl_priv(hw));
	समय64_t now;

	rtl_dbg(rtlpriv, COMP_POWER, DBG_DMESG, "\n");
	rtlhal->driver_is_goingto_unload = false;
	rtlhal->enter_pnp_sleep = false;
	rtlhal->wake_from_pnp_sleep = true;

	/* to resolve s4 can not wake up*/
	now = kसमय_get_real_seconds();
	अगर (now - rtlhal->last_suspend_sec < 5)
		वापस -1;

	rtl_op_start(hw);
	device_set_wakeup_enable(wiphy_dev(hw->wiphy), false);
	ieee80211_resume_disconnect(mac->vअगर);
	rtlhal->wake_from_pnp_sleep = false;
	वापस 0;
पूर्ण
#पूर्ण_अगर

अटल पूर्णांक rtl_op_config(काष्ठा ieee80211_hw *hw, u32 changed)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	काष्ठा rtl_phy *rtlphy = &(rtlpriv->phy);
	काष्ठा rtl_mac *mac = rtl_mac(rtl_priv(hw));
	काष्ठा rtl_ps_ctl *ppsc = rtl_psc(rtl_priv(hw));
	काष्ठा ieee80211_conf *conf = &hw->conf;

	अगर (mac->skip_scan)
		वापस 1;

	mutex_lock(&rtlpriv->locks.conf_mutex);
	अगर (changed & IEEE80211_CONF_CHANGE_LISTEN_INTERVAL) अणु	/* BIT(2)*/
		rtl_dbg(rtlpriv, COMP_MAC80211, DBG_LOUD,
			"IEEE80211_CONF_CHANGE_LISTEN_INTERVAL\n");
	पूर्ण

	/*For IPS */
	अगर (changed & IEEE80211_CONF_CHANGE_IDLE) अणु
		अगर (hw->conf.flags & IEEE80211_CONF_IDLE)
			rtl_ips_nic_off(hw);
		अन्यथा
			rtl_ips_nic_on(hw);
	पूर्ण अन्यथा अणु
		/*
		 *although rfoff may not cause by ips, but we will
		 *check the reason in set_rf_घातer_state function
		 */
		अगर (unlikely(ppsc->rfpwr_state == ERFOFF))
			rtl_ips_nic_on(hw);
	पूर्ण

	/*For LPS */
	अगर ((changed & IEEE80211_CONF_CHANGE_PS) &&
	    rtlpriv->psc.swctrl_lps && !rtlpriv->psc.fwctrl_lps) अणु
		cancel_delayed_work(&rtlpriv->works.ps_work);
		cancel_delayed_work(&rtlpriv->works.ps_rfon_wq);
		अगर (conf->flags & IEEE80211_CONF_PS) अणु
			rtlpriv->psc.sw_ps_enabled = true;
			/* sleep here is must, or we may recv the beacon and
			 * cause mac80211 पूर्णांकo wrong ps state, this will cause
			 * घातer save nullfunc send fail, and further cause
			 * pkt loss, So sleep must quickly but not immediatly
			 * because that will cause nullfunc send by mac80211
			 * fail, and cause pkt loss, we have tested that 5mA
			 * is worked very well */
			अगर (!rtlpriv->psc.multi_buffered)
				queue_delayed_work(rtlpriv->works.rtl_wq,
						   &rtlpriv->works.ps_work,
						   MSECS(5));
		पूर्ण अन्यथा अणु
			rtl_swlps_rf_awake(hw);
			rtlpriv->psc.sw_ps_enabled = false;
		पूर्ण
	पूर्ण

	अगर (changed & IEEE80211_CONF_CHANGE_RETRY_LIMITS) अणु
		rtl_dbg(rtlpriv, COMP_MAC80211, DBG_LOUD,
			"IEEE80211_CONF_CHANGE_RETRY_LIMITS %x\n",
			hw->conf.दीर्घ_frame_max_tx_count);
		/* brought up everything changes (changed == ~0) indicates first
		 * खोलो, so use our शेष value instead of that of wiphy.
		 */
		अगर (changed != ~0) अणु
			mac->retry_दीर्घ = hw->conf.दीर्घ_frame_max_tx_count;
			mac->retry_लघु = hw->conf.दीर्घ_frame_max_tx_count;
			rtlpriv->cfg->ops->set_hw_reg(hw, HW_VAR_RETRY_LIMIT,
				(u8 *)(&hw->conf.दीर्घ_frame_max_tx_count));
		पूर्ण
	पूर्ण

	अगर (changed & IEEE80211_CONF_CHANGE_CHANNEL &&
	    !rtlpriv->proximity.proxim_on) अणु
		काष्ठा ieee80211_channel *channel = hw->conf.chandef.chan;
		क्रमागत nl80211_chan_width width = hw->conf.chandef.width;
		क्रमागत nl80211_channel_type channel_type = NL80211_CHAN_NO_HT;
		u8 wide_chan = (u8) channel->hw_value;

		/* channel_type is क्रम 20&40M */
		अगर (width < NL80211_CHAN_WIDTH_80)
			channel_type =
				cfg80211_get_chandef_type(&hw->conf.chandef);
		अगर (mac->act_scanning)
			mac->n_channels++;

		अगर (rtlpriv->dm.supp_phymode_चयन &&
			mac->link_state < MAC80211_LINKED &&
			!mac->act_scanning) अणु
			अगर (rtlpriv->cfg->ops->chk_चयन_dmdp)
				rtlpriv->cfg->ops->chk_चयन_dmdp(hw);
		पूर्ण

		/*
		 *because we should back channel to
		 *current_network.chan in in scanning,
		 *So अगर set_chan == current_network.chan
		 *we should set it.
		 *because mac80211 tell us wrong bw40
		 *info क्रम cisco1253 bw20, so we modअगरy
		 *it here based on UPPER & LOWER
		 */

		अगर (width >= NL80211_CHAN_WIDTH_80) अणु
			अगर (width == NL80211_CHAN_WIDTH_80) अणु
				u32 center = hw->conf.chandef.center_freq1;
				u32 primary =
				(u32)hw->conf.chandef.chan->center_freq;

				rtlphy->current_chan_bw =
					HT_CHANNEL_WIDTH_80;
				mac->bw_80 = true;
				mac->bw_40 = true;
				अगर (center > primary) अणु
					mac->cur_80_prime_sc =
					PRIME_CHNL_OFFSET_LOWER;
					अगर (center - primary == 10) अणु
						mac->cur_40_prime_sc =
						PRIME_CHNL_OFFSET_UPPER;

						wide_chan += 2;
					पूर्ण अन्यथा अगर (center - primary == 30) अणु
						mac->cur_40_prime_sc =
						PRIME_CHNL_OFFSET_LOWER;

						wide_chan += 6;
					पूर्ण
				पूर्ण अन्यथा अणु
					mac->cur_80_prime_sc =
					PRIME_CHNL_OFFSET_UPPER;
					अगर (primary - center == 10) अणु
						mac->cur_40_prime_sc =
						PRIME_CHNL_OFFSET_LOWER;

						wide_chan -= 2;
					पूर्ण अन्यथा अगर (primary - center == 30) अणु
						mac->cur_40_prime_sc =
						PRIME_CHNL_OFFSET_UPPER;

						wide_chan -= 6;
					पूर्ण
				पूर्ण
			पूर्ण
		पूर्ण अन्यथा अणु
			चयन (channel_type) अणु
			हाल NL80211_CHAN_HT20:
			हाल NL80211_CHAN_NO_HT:
					/* SC */
					mac->cur_40_prime_sc =
						PRIME_CHNL_OFFSET_DONT_CARE;
					rtlphy->current_chan_bw =
						HT_CHANNEL_WIDTH_20;
					mac->bw_40 = false;
					mac->bw_80 = false;
					अवरोध;
			हाल NL80211_CHAN_HT40MINUS:
					/* SC */
					mac->cur_40_prime_sc =
						PRIME_CHNL_OFFSET_UPPER;
					rtlphy->current_chan_bw =
						HT_CHANNEL_WIDTH_20_40;
					mac->bw_40 = true;
					mac->bw_80 = false;

					/*wide channel */
					wide_chan -= 2;

					अवरोध;
			हाल NL80211_CHAN_HT40PLUS:
					/* SC */
					mac->cur_40_prime_sc =
						PRIME_CHNL_OFFSET_LOWER;
					rtlphy->current_chan_bw =
						HT_CHANNEL_WIDTH_20_40;
					mac->bw_40 = true;
					mac->bw_80 = false;

					/*wide channel */
					wide_chan += 2;

					अवरोध;
			शेष:
					mac->bw_40 = false;
					mac->bw_80 = false;
					pr_err("switch case %#x not processed\n",
					       channel_type);
					अवरोध;
			पूर्ण
		पूर्ण

		अगर (wide_chan <= 0)
			wide_chan = 1;

		/* In scanning, when beक्रमe we offchannel we may send a ps=1
		 * null to AP, and then we may send a ps = 0 null to AP quickly,
		 * but first null may have caused AP to put lots of packet to
		 * hw tx buffer. These packets must be tx'd beक्रमe we go off
		 * channel so we must delay more समय to let AP flush these
		 * packets beक्रमe going offchannel, or dis-association or
		 * delete BA will be caused by AP
		 */
		अगर (rtlpriv->mac80211.offchan_delay) अणु
			rtlpriv->mac80211.offchan_delay = false;
			mdelay(50);
		पूर्ण

		rtlphy->current_channel = wide_chan;

		rtlpriv->cfg->ops->चयन_channel(hw);
		rtlpriv->cfg->ops->set_channel_access(hw);
		rtlpriv->cfg->ops->set_bw_mode(hw, channel_type);
	पूर्ण

	mutex_unlock(&rtlpriv->locks.conf_mutex);

	वापस 0;
पूर्ण

अटल व्योम rtl_op_configure_filter(काष्ठा ieee80211_hw *hw,
				    अचिन्हित पूर्णांक changed_flags,
				    अचिन्हित पूर्णांक *new_flags, u64 multicast)
अणु
	bool update_rcr = false;
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	काष्ठा rtl_mac *mac = rtl_mac(rtl_priv(hw));

	*new_flags &= RTL_SUPPORTED_FILTERS;
	अगर (0 == changed_flags)
		वापस;

	/*TODO: we disable broadcast now, so enable here */
	अगर (changed_flags & FIF_ALLMULTI) अणु
		अगर (*new_flags & FIF_ALLMULTI) अणु
			mac->rx_conf |= rtlpriv->cfg->maps[MAC_RCR_AM] |
			    rtlpriv->cfg->maps[MAC_RCR_AB];
			rtl_dbg(rtlpriv, COMP_MAC80211, DBG_LOUD,
				"Enable receive multicast frame\n");
		पूर्ण अन्यथा अणु
			mac->rx_conf &= ~(rtlpriv->cfg->maps[MAC_RCR_AM] |
					  rtlpriv->cfg->maps[MAC_RCR_AB]);
			rtl_dbg(rtlpriv, COMP_MAC80211, DBG_LOUD,
				"Disable receive multicast frame\n");
		पूर्ण
		update_rcr = true;
	पूर्ण

	अगर (changed_flags & FIF_FCSFAIL) अणु
		अगर (*new_flags & FIF_FCSFAIL) अणु
			mac->rx_conf |= rtlpriv->cfg->maps[MAC_RCR_ACRC32];
			rtl_dbg(rtlpriv, COMP_MAC80211, DBG_LOUD,
				"Enable receive FCS error frame\n");
		पूर्ण अन्यथा अणु
			mac->rx_conf &= ~rtlpriv->cfg->maps[MAC_RCR_ACRC32];
			rtl_dbg(rtlpriv, COMP_MAC80211, DBG_LOUD,
				"Disable receive FCS error frame\n");
		पूर्ण
		अगर (!update_rcr)
			update_rcr = true;
	पूर्ण

	/* अगर ssid not set to hw करोn't check bssid
	 * here just used क्रम linked scanning, & linked
	 * and nolink check bssid is set in set network_type
	 */
	अगर (changed_flags & FIF_BCN_PRBRESP_PROMISC &&
	    mac->link_state >= MAC80211_LINKED) अणु
		अगर (mac->opmode != NL80211_IFTYPE_AP &&
		    mac->opmode != NL80211_IFTYPE_MESH_POINT) अणु
			अगर (*new_flags & FIF_BCN_PRBRESP_PROMISC)
				rtlpriv->cfg->ops->set_chk_bssid(hw, false);
			अन्यथा
				rtlpriv->cfg->ops->set_chk_bssid(hw, true);
			अगर (update_rcr)
				update_rcr = false;
		पूर्ण
	पूर्ण

	अगर (changed_flags & FIF_CONTROL) अणु
		अगर (*new_flags & FIF_CONTROL) अणु
			mac->rx_conf |= rtlpriv->cfg->maps[MAC_RCR_ACF];

			rtl_dbg(rtlpriv, COMP_MAC80211, DBG_LOUD,
				"Enable receive control frame.\n");
		पूर्ण अन्यथा अणु
			mac->rx_conf &= ~rtlpriv->cfg->maps[MAC_RCR_ACF];
			rtl_dbg(rtlpriv, COMP_MAC80211, DBG_LOUD,
				"Disable receive control frame.\n");
		पूर्ण
		अगर (!update_rcr)
			update_rcr = true;
	पूर्ण

	अगर (changed_flags & FIF_OTHER_BSS) अणु
		अगर (*new_flags & FIF_OTHER_BSS) अणु
			mac->rx_conf |= rtlpriv->cfg->maps[MAC_RCR_AAP];
			rtl_dbg(rtlpriv, COMP_MAC80211, DBG_LOUD,
				"Enable receive other BSS's frame.\n");
		पूर्ण अन्यथा अणु
			mac->rx_conf &= ~rtlpriv->cfg->maps[MAC_RCR_AAP];
			rtl_dbg(rtlpriv, COMP_MAC80211, DBG_LOUD,
				"Disable receive other BSS's frame.\n");
		पूर्ण
		अगर (!update_rcr)
			update_rcr = true;
	पूर्ण

	अगर (update_rcr)
		rtlpriv->cfg->ops->set_hw_reg(hw, HW_VAR_RCR,
					      (u8 *)(&mac->rx_conf));
पूर्ण

अटल पूर्णांक rtl_op_sta_add(काष्ठा ieee80211_hw *hw,
			 काष्ठा ieee80211_vअगर *vअगर,
			 काष्ठा ieee80211_sta *sta)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	काष्ठा rtl_hal *rtlhal = rtl_hal(rtl_priv(hw));
	काष्ठा rtl_mac *mac = rtl_mac(rtl_priv(hw));
	काष्ठा rtl_sta_info *sta_entry;

	अगर (sta) अणु
		sta_entry = (काष्ठा rtl_sta_info *)sta->drv_priv;
		spin_lock_bh(&rtlpriv->locks.entry_list_lock);
		list_add_tail(&sta_entry->list, &rtlpriv->entry_list);
		spin_unlock_bh(&rtlpriv->locks.entry_list_lock);
		अगर (rtlhal->current_bandtype == BAND_ON_2_4G) अणु
			sta_entry->wireless_mode = WIRELESS_MODE_G;
			अगर (sta->supp_rates[0] <= 0xf)
				sta_entry->wireless_mode = WIRELESS_MODE_B;
			अगर (sta->ht_cap.ht_supported)
				sta_entry->wireless_mode = WIRELESS_MODE_N_24G;

			अगर (vअगर->type == NL80211_IFTYPE_ADHOC)
				sta_entry->wireless_mode = WIRELESS_MODE_G;
		पूर्ण अन्यथा अगर (rtlhal->current_bandtype == BAND_ON_5G) अणु
			sta_entry->wireless_mode = WIRELESS_MODE_A;
			अगर (sta->ht_cap.ht_supported)
				sta_entry->wireless_mode = WIRELESS_MODE_N_5G;
			अगर (sta->vht_cap.vht_supported)
				sta_entry->wireless_mode = WIRELESS_MODE_AC_5G;

			अगर (vअगर->type == NL80211_IFTYPE_ADHOC)
				sta_entry->wireless_mode = WIRELESS_MODE_A;
		पूर्ण
		/*disable cck rate क्रम p2p*/
		अगर (mac->p2p)
			sta->supp_rates[0] &= 0xfffffff0;

		स_नकल(sta_entry->mac_addr, sta->addr, ETH_ALEN);
		rtl_dbg(rtlpriv, COMP_MAC80211, DBG_DMESG,
			"Add sta addr is %pM\n", sta->addr);
		rtlpriv->cfg->ops->update_rate_tbl(hw, sta, 0, true);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक rtl_op_sta_हटाओ(काष्ठा ieee80211_hw *hw,
				काष्ठा ieee80211_vअगर *vअगर,
				काष्ठा ieee80211_sta *sta)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	काष्ठा rtl_sta_info *sta_entry;

	अगर (sta) अणु
		rtl_dbg(rtlpriv, COMP_MAC80211, DBG_DMESG,
			"Remove sta addr is %pM\n", sta->addr);
		sta_entry = (काष्ठा rtl_sta_info *)sta->drv_priv;
		sta_entry->wireless_mode = 0;
		sta_entry->ratr_index = 0;
		spin_lock_bh(&rtlpriv->locks.entry_list_lock);
		list_del(&sta_entry->list);
		spin_unlock_bh(&rtlpriv->locks.entry_list_lock);
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक _rtl_get_hal_qnum(u16 queue)
अणु
	पूर्णांक qnum;

	चयन (queue) अणु
	हाल 0:
		qnum = AC3_VO;
		अवरोध;
	हाल 1:
		qnum = AC2_VI;
		अवरोध;
	हाल 2:
		qnum = AC0_BE;
		अवरोध;
	हाल 3:
		qnum = AC1_BK;
		अवरोध;
	शेष:
		qnum = AC0_BE;
		अवरोध;
	पूर्ण
	वापस qnum;
पूर्ण

/*
 *क्रम mac80211 VO = 0, VI = 1, BE = 2, BK = 3
 *क्रम rtl819x  BE = 0, BK = 1, VI = 2, VO = 3
 */
अटल पूर्णांक rtl_op_conf_tx(काष्ठा ieee80211_hw *hw,
			  काष्ठा ieee80211_vअगर *vअगर, u16 queue,
			  स्थिर काष्ठा ieee80211_tx_queue_params *param)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	काष्ठा rtl_mac *mac = rtl_mac(rtl_priv(hw));
	पूर्णांक aci;

	अगर (queue >= AC_MAX) अणु
		rtl_dbg(rtlpriv, COMP_ERR, DBG_WARNING,
			"queue number %d is incorrect!\n", queue);
		वापस -EINVAL;
	पूर्ण

	aci = _rtl_get_hal_qnum(queue);
	mac->ac[aci].aअगरs = param->aअगरs;
	mac->ac[aci].cw_min = cpu_to_le16(param->cw_min);
	mac->ac[aci].cw_max = cpu_to_le16(param->cw_max);
	mac->ac[aci].tx_op = cpu_to_le16(param->txop);
	स_नकल(&mac->edca_param[aci], param, माप(*param));
	rtlpriv->cfg->ops->set_qos(hw, aci);
	वापस 0;
पूर्ण

अटल व्योम send_beacon_frame(काष्ठा ieee80211_hw *hw,
			      काष्ठा ieee80211_vअगर *vअगर)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	काष्ठा sk_buff *skb = ieee80211_beacon_get(hw, vअगर);
	काष्ठा rtl_tcb_desc tcb_desc;

	अगर (skb) अणु
		स_रखो(&tcb_desc, 0, माप(काष्ठा rtl_tcb_desc));
		rtlpriv->पूर्णांकf_ops->adapter_tx(hw, शून्य, skb, &tcb_desc);
	पूर्ण
पूर्ण

व्योम rtl_update_beacon_work_callback(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा rtl_works *rtlworks =
	    container_of(work, काष्ठा rtl_works, update_beacon_work);
	काष्ठा ieee80211_hw *hw = rtlworks->hw;
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	काष्ठा ieee80211_vअगर *vअगर = rtlpriv->mac80211.vअगर;

	अगर (!vअगर) अणु
		WARN_ONCE(true, "no vif to update beacon\n");
		वापस;
	पूर्ण

	mutex_lock(&rtlpriv->locks.conf_mutex);
	send_beacon_frame(hw, vअगर);
	mutex_unlock(&rtlpriv->locks.conf_mutex);
पूर्ण
EXPORT_SYMBOL_GPL(rtl_update_beacon_work_callback);

अटल व्योम rtl_op_bss_info_changed(काष्ठा ieee80211_hw *hw,
				    काष्ठा ieee80211_vअगर *vअगर,
				    काष्ठा ieee80211_bss_conf *bss_conf,
				    u32 changed)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	काष्ठा rtl_hal *rtlhal = rtl_hal(rtlpriv);
	काष्ठा rtl_mac *mac = rtl_mac(rtl_priv(hw));
	काष्ठा rtl_ps_ctl *ppsc = rtl_psc(rtl_priv(hw));

	mutex_lock(&rtlpriv->locks.conf_mutex);
	अगर (vअगर->type == NL80211_IFTYPE_ADHOC ||
	    vअगर->type == NL80211_IFTYPE_AP ||
	    vअगर->type == NL80211_IFTYPE_MESH_POINT) अणु
		अगर (changed & BSS_CHANGED_BEACON ||
		    (changed & BSS_CHANGED_BEACON_ENABLED &&
		     bss_conf->enable_beacon)) अणु
			अगर (mac->beacon_enabled == 0) अणु
				rtl_dbg(rtlpriv, COMP_MAC80211, DBG_DMESG,
					"BSS_CHANGED_BEACON_ENABLED\n");

				/*start hw beacon पूर्णांकerrupt. */
				/*rtlpriv->cfg->ops->set_bcn_reg(hw); */
				mac->beacon_enabled = 1;
				rtlpriv->cfg->ops->update_पूर्णांकerrupt_mask(hw,
						rtlpriv->cfg->maps
						[RTL_IBSS_INT_MASKS], 0);

				अगर (rtlpriv->cfg->ops->linked_set_reg)
					rtlpriv->cfg->ops->linked_set_reg(hw);
				send_beacon_frame(hw, vअगर);
			पूर्ण
		पूर्ण
		अगर ((changed & BSS_CHANGED_BEACON_ENABLED &&
		    !bss_conf->enable_beacon)) अणु
			अगर (mac->beacon_enabled == 1) अणु
				rtl_dbg(rtlpriv, COMP_MAC80211, DBG_DMESG,
					"ADHOC DISABLE BEACON\n");

				mac->beacon_enabled = 0;
				rtlpriv->cfg->ops->update_पूर्णांकerrupt_mask(hw, 0,
						rtlpriv->cfg->maps
						[RTL_IBSS_INT_MASKS]);
			पूर्ण
		पूर्ण
		अगर (changed & BSS_CHANGED_BEACON_INT) अणु
			rtl_dbg(rtlpriv, COMP_BEACON, DBG_TRACE,
				"BSS_CHANGED_BEACON_INT\n");
			mac->beacon_पूर्णांकerval = bss_conf->beacon_पूर्णांक;
			rtlpriv->cfg->ops->set_bcn_पूर्णांकv(hw);
		पूर्ण
	पूर्ण

	/*TODO: reference to क्रमागत ieee80211_bss_change */
	अगर (changed & BSS_CHANGED_ASSOC) अणु
		u8 mstatus;

		अगर (bss_conf->assoc) अणु
			काष्ठा ieee80211_sta *sta = शून्य;
			u8 keep_alive = 10;

			mstatus = RT_MEDIA_CONNECT;
			/* we should reset all sec info & cam
			 * beक्रमe set cam after linked, we should not
			 * reset in disassoc, that will cause tkip->wep
			 * fail because some flag will be wrong */
			/* reset sec info */
			rtl_cam_reset_sec_info(hw);
			/* reset cam to fix wep fail issue
			 * when change from wpa to wep */
			rtl_cam_reset_all_entry(hw);

			mac->link_state = MAC80211_LINKED;
			mac->cnt_after_linked = 0;
			mac->assoc_id = bss_conf->aid;
			स_नकल(mac->bssid, bss_conf->bssid, ETH_ALEN);

			अगर (rtlpriv->cfg->ops->linked_set_reg)
				rtlpriv->cfg->ops->linked_set_reg(hw);

			rcu_पढ़ो_lock();
			sta = ieee80211_find_sta(vअगर, (u8 *)bss_conf->bssid);
			अगर (!sta) अणु
				rcu_पढ़ो_unlock();
				जाओ out;
			पूर्ण
			rtl_dbg(rtlpriv, COMP_EASY_CONCURRENT, DBG_LOUD,
				"send PS STATIC frame\n");
			अगर (rtlpriv->dm.supp_phymode_चयन) अणु
				अगर (sta->ht_cap.ht_supported)
					rtl_send_smps_action(hw, sta,
							IEEE80211_SMPS_STATIC);
			पूर्ण

			अगर (rtlhal->current_bandtype == BAND_ON_5G) अणु
				mac->mode = WIRELESS_MODE_A;
			पूर्ण अन्यथा अणु
				अगर (sta->supp_rates[0] <= 0xf)
					mac->mode = WIRELESS_MODE_B;
				अन्यथा
					mac->mode = WIRELESS_MODE_G;
			पूर्ण

			अगर (sta->ht_cap.ht_supported) अणु
				अगर (rtlhal->current_bandtype == BAND_ON_2_4G)
					mac->mode = WIRELESS_MODE_N_24G;
				अन्यथा
					mac->mode = WIRELESS_MODE_N_5G;
			पूर्ण

			अगर (sta->vht_cap.vht_supported) अणु
				अगर (rtlhal->current_bandtype == BAND_ON_5G)
					mac->mode = WIRELESS_MODE_AC_5G;
				अन्यथा
					mac->mode = WIRELESS_MODE_AC_24G;
			पूर्ण

			अगर (vअगर->type == NL80211_IFTYPE_STATION)
				rtlpriv->cfg->ops->update_rate_tbl(hw, sta, 0,
								   true);
			rcu_पढ़ो_unlock();

			/* to aव्योम AP Disassociation caused by inactivity */
			rtlpriv->cfg->ops->set_hw_reg(hw,
						      HW_VAR_KEEP_ALIVE,
						      (u8 *)(&keep_alive));

			rtl_dbg(rtlpriv, COMP_MAC80211, DBG_DMESG,
				"BSS_CHANGED_ASSOC\n");
		पूर्ण अन्यथा अणु
			काष्ठा cfg80211_bss *bss = शून्य;

			mstatus = RT_MEDIA_DISCONNECT;

			अगर (mac->link_state == MAC80211_LINKED)
				rtl_lps_leave(hw, true);
			अगर (ppsc->p2p_ps_info.p2p_ps_mode > P2P_PS_NONE)
				rtl_p2p_ps_cmd(hw, P2P_PS_DISABLE);
			mac->link_state = MAC80211_NOLINK;

			bss = cfg80211_get_bss(hw->wiphy, शून्य,
					       (u8 *)mac->bssid, शून्य, 0,
					       IEEE80211_BSS_TYPE_ESS,
					       IEEE80211_PRIVACY_OFF);

			rtl_dbg(rtlpriv, COMP_MAC80211, DBG_DMESG,
				"bssid = %pMF\n", mac->bssid);

			अगर (bss) अणु
				cfg80211_unlink_bss(hw->wiphy, bss);
				cfg80211_put_bss(hw->wiphy, bss);
				rtl_dbg(rtlpriv, COMP_MAC80211, DBG_DMESG,
					"cfg80211_unlink !!\n");
			पूर्ण

			eth_zero_addr(mac->bssid);
			mac->venकरोr = PEER_UNKNOWN;
			mac->mode = 0;

			अगर (rtlpriv->dm.supp_phymode_चयन) अणु
				अगर (rtlpriv->cfg->ops->chk_चयन_dmdp)
					rtlpriv->cfg->ops->chk_चयन_dmdp(hw);
			पूर्ण
			rtl_dbg(rtlpriv, COMP_MAC80211, DBG_DMESG,
				"BSS_CHANGED_UN_ASSOC\n");
		पूर्ण
		rtlpriv->cfg->ops->set_network_type(hw, vअगर->type);
		/* For FW LPS:
		 * To tell firmware we have connected or disconnected
		 */
		rtlpriv->cfg->ops->set_hw_reg(hw,
					      HW_VAR_H2C_FW_JOINBSSRPT,
					      (u8 *)(&mstatus));
		ppsc->report_linked = (mstatus == RT_MEDIA_CONNECT) ?
				      true : false;

		अगर (rtlpriv->cfg->ops->get_btc_status())
			rtlpriv->btcoexist.btc_ops->btc_mediastatus_notअगरy(
							rtlpriv, mstatus);
	पूर्ण

	अगर (changed & BSS_CHANGED_ERP_CTS_PROT) अणु
		rtl_dbg(rtlpriv, COMP_MAC80211, DBG_TRACE,
			"BSS_CHANGED_ERP_CTS_PROT\n");
		mac->use_cts_protect = bss_conf->use_cts_prot;
	पूर्ण

	अगर (changed & BSS_CHANGED_ERP_PREAMBLE) अणु
		rtl_dbg(rtlpriv, COMP_MAC80211, DBG_LOUD,
			"BSS_CHANGED_ERP_PREAMBLE use short preamble:%x\n",
			  bss_conf->use_लघु_preamble);

		mac->लघु_preamble = bss_conf->use_लघु_preamble;
		rtlpriv->cfg->ops->set_hw_reg(hw, HW_VAR_ACK_PREAMBLE,
					      (u8 *)(&mac->लघु_preamble));
	पूर्ण

	अगर (changed & BSS_CHANGED_ERP_SLOT) अणु
		rtl_dbg(rtlpriv, COMP_MAC80211, DBG_TRACE,
			"BSS_CHANGED_ERP_SLOT\n");

		अगर (bss_conf->use_लघु_slot)
			mac->slot_समय = RTL_SLOT_TIME_9;
		अन्यथा
			mac->slot_समय = RTL_SLOT_TIME_20;

		rtlpriv->cfg->ops->set_hw_reg(hw, HW_VAR_SLOT_TIME,
					      (u8 *)(&mac->slot_समय));
	पूर्ण

	अगर (changed & BSS_CHANGED_HT) अणु
		काष्ठा ieee80211_sta *sta = शून्य;

		rtl_dbg(rtlpriv, COMP_MAC80211, DBG_TRACE,
			"BSS_CHANGED_HT\n");

		rcu_पढ़ो_lock();
		sta = ieee80211_find_sta(vअगर, (u8 *)bss_conf->bssid);
		अगर (sta) अणु
			अगर (sta->ht_cap.ampdu_density >
			    mac->current_ampdu_density)
				mac->current_ampdu_density =
				    sta->ht_cap.ampdu_density;
			अगर (sta->ht_cap.ampdu_factor <
			    mac->current_ampdu_factor)
				mac->current_ampdu_factor =
				    sta->ht_cap.ampdu_factor;
		पूर्ण
		rcu_पढ़ो_unlock();

		rtlpriv->cfg->ops->set_hw_reg(hw, HW_VAR_SHORTGI_DENSITY,
					      (u8 *)(&mac->max_mss_density));
		rtlpriv->cfg->ops->set_hw_reg(hw, HW_VAR_AMPDU_FACTOR,
					      &mac->current_ampdu_factor);
		rtlpriv->cfg->ops->set_hw_reg(hw, HW_VAR_AMPDU_MIN_SPACE,
					      &mac->current_ampdu_density);
	पूर्ण

	अगर (changed & BSS_CHANGED_BSSID) अणु
		u32 basic_rates;
		काष्ठा ieee80211_sta *sta = शून्य;

		rtlpriv->cfg->ops->set_hw_reg(hw, HW_VAR_BSSID,
					      (u8 *)bss_conf->bssid);

		rtl_dbg(rtlpriv, COMP_MAC80211, DBG_DMESG,
			"bssid: %pM\n", bss_conf->bssid);

		mac->venकरोr = PEER_UNKNOWN;
		स_नकल(mac->bssid, bss_conf->bssid, ETH_ALEN);

		rcu_पढ़ो_lock();
		sta = ieee80211_find_sta(vअगर, (u8 *)bss_conf->bssid);
		अगर (!sta) अणु
			rcu_पढ़ो_unlock();
			जाओ out;
		पूर्ण

		अगर (rtlhal->current_bandtype == BAND_ON_5G) अणु
			mac->mode = WIRELESS_MODE_A;
		पूर्ण अन्यथा अणु
			अगर (sta->supp_rates[0] <= 0xf)
				mac->mode = WIRELESS_MODE_B;
			अन्यथा
				mac->mode = WIRELESS_MODE_G;
		पूर्ण

		अगर (sta->ht_cap.ht_supported) अणु
			अगर (rtlhal->current_bandtype == BAND_ON_2_4G)
				mac->mode = WIRELESS_MODE_N_24G;
			अन्यथा
				mac->mode = WIRELESS_MODE_N_5G;
		पूर्ण

		अगर (sta->vht_cap.vht_supported) अणु
			अगर (rtlhal->current_bandtype == BAND_ON_5G)
				mac->mode = WIRELESS_MODE_AC_5G;
			अन्यथा
				mac->mode = WIRELESS_MODE_AC_24G;
		पूर्ण

		/* just station need it, because ibss & ap mode will
		 * set in sta_add, and will be शून्य here */
		अगर (vअगर->type == NL80211_IFTYPE_STATION) अणु
			काष्ठा rtl_sta_info *sta_entry;

			sta_entry = (काष्ठा rtl_sta_info *)sta->drv_priv;
			sta_entry->wireless_mode = mac->mode;
		पूर्ण

		अगर (sta->ht_cap.ht_supported) अणु
			mac->ht_enable = true;

			/*
			 * क्रम cisco 1252 bw20 it's wrong
			 * अगर (ht_cap & IEEE80211_HT_CAP_SUP_WIDTH_20_40) अणु
			 *	mac->bw_40 = true;
			 * पूर्ण
			 * */
		पूर्ण

		अगर (sta->vht_cap.vht_supported)
			mac->vht_enable = true;

		अगर (changed & BSS_CHANGED_BASIC_RATES) अणु
			/* क्रम 5G must << RATE_6M_INDEX = 4,
			 * because 5G have no cck rate*/
			अगर (rtlhal->current_bandtype == BAND_ON_5G)
				basic_rates = sta->supp_rates[1] << 4;
			अन्यथा
				basic_rates = sta->supp_rates[0];

			mac->basic_rates = basic_rates;
			rtlpriv->cfg->ops->set_hw_reg(hw, HW_VAR_BASIC_RATE,
					(u8 *)(&basic_rates));
		पूर्ण
		rcu_पढ़ो_unlock();
	पूर्ण
out:
	mutex_unlock(&rtlpriv->locks.conf_mutex);
पूर्ण

अटल u64 rtl_op_get_tsf(काष्ठा ieee80211_hw *hw, काष्ठा ieee80211_vअगर *vअगर)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	u64 tsf;

	rtlpriv->cfg->ops->get_hw_reg(hw, HW_VAR_CORRECT_TSF, (u8 *)(&tsf));
	वापस tsf;
पूर्ण

अटल व्योम rtl_op_set_tsf(काष्ठा ieee80211_hw *hw,
			   काष्ठा ieee80211_vअगर *vअगर, u64 tsf)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	काष्ठा rtl_mac *mac = rtl_mac(rtl_priv(hw));
	u8 bibss = (mac->opmode == NL80211_IFTYPE_ADHOC) ? 1 : 0;

	mac->tsf = tsf;
	rtlpriv->cfg->ops->set_hw_reg(hw, HW_VAR_CORRECT_TSF, (u8 *)(&bibss));
पूर्ण

अटल व्योम rtl_op_reset_tsf(काष्ठा ieee80211_hw *hw, काष्ठा ieee80211_vअगर *vअगर)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	u8 पंचांगp = 0;

	rtlpriv->cfg->ops->set_hw_reg(hw, HW_VAR_DUAL_TSF_RST, (u8 *)(&पंचांगp));
पूर्ण

अटल व्योम rtl_op_sta_notअगरy(काष्ठा ieee80211_hw *hw,
			      काष्ठा ieee80211_vअगर *vअगर,
			      क्रमागत sta_notअगरy_cmd cmd,
			      काष्ठा ieee80211_sta *sta)
अणु
	चयन (cmd) अणु
	हाल STA_NOTIFY_SLEEP:
		अवरोध;
	हाल STA_NOTIFY_AWAKE:
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण
पूर्ण

अटल पूर्णांक rtl_op_ampdu_action(काष्ठा ieee80211_hw *hw,
			       काष्ठा ieee80211_vअगर *vअगर,
			       काष्ठा ieee80211_ampdu_params *params)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	काष्ठा ieee80211_sta *sta = params->sta;
	क्रमागत ieee80211_ampdu_mlme_action action = params->action;
	u16 tid = params->tid;
	u16 *ssn = &params->ssn;

	चयन (action) अणु
	हाल IEEE80211_AMPDU_TX_START:
		rtl_dbg(rtlpriv, COMP_MAC80211, DBG_TRACE,
			"IEEE80211_AMPDU_TX_START: TID:%d\n", tid);
		वापस rtl_tx_agg_start(hw, vअगर, sta, tid, ssn);
	हाल IEEE80211_AMPDU_TX_STOP_CONT:
	हाल IEEE80211_AMPDU_TX_STOP_FLUSH:
	हाल IEEE80211_AMPDU_TX_STOP_FLUSH_CONT:
		rtl_dbg(rtlpriv, COMP_MAC80211, DBG_TRACE,
			"IEEE80211_AMPDU_TX_STOP: TID:%d\n", tid);
		वापस rtl_tx_agg_stop(hw, vअगर, sta, tid);
	हाल IEEE80211_AMPDU_TX_OPERATIONAL:
		rtl_dbg(rtlpriv, COMP_MAC80211, DBG_TRACE,
			"IEEE80211_AMPDU_TX_OPERATIONAL:TID:%d\n", tid);
		rtl_tx_agg_oper(hw, sta, tid);
		अवरोध;
	हाल IEEE80211_AMPDU_RX_START:
		rtl_dbg(rtlpriv, COMP_MAC80211, DBG_TRACE,
			"IEEE80211_AMPDU_RX_START:TID:%d\n", tid);
		वापस rtl_rx_agg_start(hw, sta, tid);
	हाल IEEE80211_AMPDU_RX_STOP:
		rtl_dbg(rtlpriv, COMP_MAC80211, DBG_TRACE,
			"IEEE80211_AMPDU_RX_STOP:TID:%d\n", tid);
		वापस rtl_rx_agg_stop(hw, sta, tid);
	शेष:
		pr_err("IEEE80211_AMPDU_ERR!!!!:\n");
		वापस -EOPNOTSUPP;
	पूर्ण
	वापस 0;
पूर्ण

अटल व्योम rtl_op_sw_scan_start(काष्ठा ieee80211_hw *hw,
				 काष्ठा ieee80211_vअगर *vअगर,
				 स्थिर u8 *mac_addr)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	काष्ठा rtl_mac *mac = rtl_mac(rtl_priv(hw));

	rtl_dbg(rtlpriv, COMP_MAC80211, DBG_LOUD, "\n");
	mac->act_scanning = true;
	अगर (rtlpriv->link_info.higher_busytraffic) अणु
		mac->skip_scan = true;
		वापस;
	पूर्ण

	अगर (rtlpriv->cfg->ops->get_btc_status())
		rtlpriv->btcoexist.btc_ops->btc_scan_notअगरy(rtlpriv, 1);
	अन्यथा अगर (rtlpriv->btcoexist.btc_ops)
		rtlpriv->btcoexist.btc_ops->btc_scan_notअगरy_wअगरi_only(rtlpriv,
								      1);

	अगर (rtlpriv->dm.supp_phymode_चयन) अणु
		अगर (rtlpriv->cfg->ops->chk_चयन_dmdp)
			rtlpriv->cfg->ops->chk_चयन_dmdp(hw);
	पूर्ण

	अगर (mac->link_state == MAC80211_LINKED) अणु
		rtl_lps_leave(hw, true);
		mac->link_state = MAC80211_LINKED_SCANNING;
	पूर्ण अन्यथा अणु
		rtl_ips_nic_on(hw);
	पूर्ण

	/* Dul mac */
	rtlpriv->rtlhal.load_imअक्रमiqk_setting_क्रम2g = false;

	rtlpriv->cfg->ops->led_control(hw, LED_CTL_SITE_SURVEY);
	rtlpriv->cfg->ops->scan_operation_backup(hw, SCAN_OPT_BACKUP_BAND0);
पूर्ण

अटल व्योम rtl_op_sw_scan_complete(काष्ठा ieee80211_hw *hw,
				    काष्ठा ieee80211_vअगर *vअगर)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	काष्ठा rtl_mac *mac = rtl_mac(rtl_priv(hw));

	rtl_dbg(rtlpriv, COMP_MAC80211, DBG_LOUD, "\n");
	mac->act_scanning = false;
	mac->skip_scan = false;

	rtlpriv->btcoexist.btc_info.ap_num = rtlpriv->scan_list.num;

	अगर (rtlpriv->link_info.higher_busytraffic)
		वापस;

	/* p2p will use 1/6/11 to scan */
	अगर (mac->n_channels == 3)
		mac->p2p_in_use = true;
	अन्यथा
		mac->p2p_in_use = false;
	mac->n_channels = 0;
	/* Dul mac */
	rtlpriv->rtlhal.load_imअक्रमiqk_setting_क्रम2g = false;

	अगर (mac->link_state == MAC80211_LINKED_SCANNING) अणु
		mac->link_state = MAC80211_LINKED;
		अगर (mac->opmode == NL80211_IFTYPE_STATION) अणु
			/* fix fwlps issue */
			rtlpriv->cfg->ops->set_network_type(hw, mac->opmode);
		पूर्ण
	पूर्ण

	rtlpriv->cfg->ops->scan_operation_backup(hw, SCAN_OPT_RESTORE);
	अगर (rtlpriv->cfg->ops->get_btc_status())
		rtlpriv->btcoexist.btc_ops->btc_scan_notअगरy(rtlpriv, 0);
	अन्यथा अगर (rtlpriv->btcoexist.btc_ops)
		rtlpriv->btcoexist.btc_ops->btc_scan_notअगरy_wअगरi_only(rtlpriv,
								      0);
पूर्ण

अटल पूर्णांक rtl_op_set_key(काष्ठा ieee80211_hw *hw, क्रमागत set_key_cmd cmd,
			  काष्ठा ieee80211_vअगर *vअगर, काष्ठा ieee80211_sta *sta,
			  काष्ठा ieee80211_key_conf *key)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	u8 key_type = NO_ENCRYPTION;
	u8 key_idx;
	bool group_key = false;
	bool wep_only = false;
	पूर्णांक err = 0;
	u8 mac_addr[ETH_ALEN];
	u8 bcast_addr[ETH_ALEN] = अणु 0xff, 0xff, 0xff, 0xff, 0xff, 0xff पूर्ण;

	rtlpriv->btcoexist.btc_info.in_4way = false;

	अगर (rtlpriv->cfg->mod_params->sw_crypto || rtlpriv->sec.use_sw_sec) अणु
		rtl_dbg(rtlpriv, COMP_ERR, DBG_WARNING,
			"not open hw encryption\n");
		वापस -ENOSPC;	/*User disabled HW-crypto */
	पूर्ण
	/* To support IBSS, use sw-crypto क्रम GTK */
	अगर ((vअगर->type == NL80211_IFTYPE_ADHOC ||
	     vअगर->type == NL80211_IFTYPE_MESH_POINT) &&
	    !(key->flags & IEEE80211_KEY_FLAG_PAIRWISE))
		वापस -ENOSPC;
	rtl_dbg(rtlpriv, COMP_SEC, DBG_DMESG,
		"%s hardware based encryption for keyidx: %d, mac: %pM\n",
		cmd == SET_KEY ? "Using" : "Disabling", key->keyidx,
		sta ? sta->addr : bcast_addr);
	rtlpriv->sec.being_setkey = true;
	rtl_ips_nic_on(hw);
	mutex_lock(&rtlpriv->locks.conf_mutex);
	/* <1> get encryption alg */

	चयन (key->cipher) अणु
	हाल WLAN_CIPHER_SUITE_WEP40:
		key_type = WEP40_ENCRYPTION;
		rtl_dbg(rtlpriv, COMP_SEC, DBG_DMESG, "alg:WEP40\n");
		अवरोध;
	हाल WLAN_CIPHER_SUITE_WEP104:
		rtl_dbg(rtlpriv, COMP_SEC, DBG_DMESG, "alg:WEP104\n");
		key_type = WEP104_ENCRYPTION;
		अवरोध;
	हाल WLAN_CIPHER_SUITE_TKIP:
		key_type = TKIP_ENCRYPTION;
		rtl_dbg(rtlpriv, COMP_SEC, DBG_DMESG, "alg:TKIP\n");
		अवरोध;
	हाल WLAN_CIPHER_SUITE_CCMP:
		key_type = AESCCMP_ENCRYPTION;
		rtl_dbg(rtlpriv, COMP_SEC, DBG_DMESG, "alg:CCMP\n");
		अवरोध;
	हाल WLAN_CIPHER_SUITE_AES_CMAC:
		/* HW करोn't support CMAC encryption,
		 * use software CMAC encryption
		 */
		key_type = AESCMAC_ENCRYPTION;
		rtl_dbg(rtlpriv, COMP_SEC, DBG_DMESG, "alg:CMAC\n");
		rtl_dbg(rtlpriv, COMP_SEC, DBG_DMESG,
			"HW don't support CMAC encryption, use software CMAC encryption\n");
		err = -EOPNOTSUPP;
		जाओ out_unlock;
	शेष:
		pr_err("alg_err:%x!!!!:\n", key->cipher);
		जाओ out_unlock;
	पूर्ण
	अगर (key_type == WEP40_ENCRYPTION ||
	   key_type == WEP104_ENCRYPTION ||
	   vअगर->type == NL80211_IFTYPE_ADHOC)
		rtlpriv->sec.use_शेषkey = true;

	/* <2> get key_idx */
	key_idx = (u8) (key->keyidx);
	अगर (key_idx > 3)
		जाओ out_unlock;
	/* <3> अगर pairwise key enable_hw_sec */
	group_key = !(key->flags & IEEE80211_KEY_FLAG_PAIRWISE);

	/* wep always be group key, but there are two conditions:
	 * 1) wep only: is just क्रम wep enc, in this condition
	 * rtlpriv->sec.pairwise_enc_algorithm == NO_ENCRYPTION
	 * will be true & enable_hw_sec will be set when wep
	 * ke setting.
	 * 2) wep(group) + AES(pairwise): some AP like cisco
	 * may use it, in this condition enable_hw_sec will not
	 * be set when wep key setting */
	/* we must reset sec_info after lingked beक्रमe set key,
	 * or some flag will be wrong*/
	अगर (vअगर->type == NL80211_IFTYPE_AP ||
		vअगर->type == NL80211_IFTYPE_MESH_POINT) अणु
		अगर (!group_key || key_type == WEP40_ENCRYPTION ||
			key_type == WEP104_ENCRYPTION) अणु
			अगर (group_key)
				wep_only = true;
			rtlpriv->cfg->ops->enable_hw_sec(hw);
		पूर्ण
	पूर्ण अन्यथा अणु
		अगर (!group_key || vअगर->type == NL80211_IFTYPE_ADHOC ||
		    rtlpriv->sec.pairwise_enc_algorithm == NO_ENCRYPTION) अणु
			अगर (rtlpriv->sec.pairwise_enc_algorithm ==
			    NO_ENCRYPTION &&
			   (key_type == WEP40_ENCRYPTION ||
			    key_type == WEP104_ENCRYPTION))
				wep_only = true;
			rtlpriv->sec.pairwise_enc_algorithm = key_type;
			rtl_dbg(rtlpriv, COMP_SEC, DBG_DMESG,
				"set enable_hw_sec, key_type:%x(OPEN:0 WEP40:1 TKIP:2 AES:4 WEP104:5)\n",
				key_type);
			rtlpriv->cfg->ops->enable_hw_sec(hw);
		पूर्ण
	पूर्ण
	/* <4> set key based on cmd */
	चयन (cmd) अणु
	हाल SET_KEY:
		अगर (wep_only) अणु
			rtl_dbg(rtlpriv, COMP_SEC, DBG_DMESG,
				"set WEP(group/pairwise) key\n");
			/* Pairwise key with an asचिन्हित MAC address. */
			rtlpriv->sec.pairwise_enc_algorithm = key_type;
			rtlpriv->sec.group_enc_algorithm = key_type;
			/*set local buf about wep key. */
			स_नकल(rtlpriv->sec.key_buf[key_idx],
			       key->key, key->keylen);
			rtlpriv->sec.key_len[key_idx] = key->keylen;
			eth_zero_addr(mac_addr);
		पूर्ण अन्यथा अगर (group_key) अणु	/* group key */
			rtl_dbg(rtlpriv, COMP_SEC, DBG_DMESG,
				"set group key\n");
			/* group key */
			rtlpriv->sec.group_enc_algorithm = key_type;
			/*set local buf about group key. */
			स_नकल(rtlpriv->sec.key_buf[key_idx],
			       key->key, key->keylen);
			rtlpriv->sec.key_len[key_idx] = key->keylen;
			स_नकल(mac_addr, bcast_addr, ETH_ALEN);
		पूर्ण अन्यथा अणु	/* pairwise key */
			rtl_dbg(rtlpriv, COMP_SEC, DBG_DMESG,
				"set pairwise key\n");
			अगर (!sta) अणु
				WARN_ONCE(true,
					  "rtlwifi: pairwise key without mac_addr\n");

				err = -EOPNOTSUPP;
				जाओ out_unlock;
			पूर्ण
			/* Pairwise key with an asचिन्हित MAC address. */
			rtlpriv->sec.pairwise_enc_algorithm = key_type;
			/*set local buf about pairwise key. */
			स_नकल(rtlpriv->sec.key_buf[PAIRWISE_KEYIDX],
			       key->key, key->keylen);
			rtlpriv->sec.key_len[PAIRWISE_KEYIDX] = key->keylen;
			rtlpriv->sec.pairwise_key =
			    rtlpriv->sec.key_buf[PAIRWISE_KEYIDX];
			स_नकल(mac_addr, sta->addr, ETH_ALEN);
		पूर्ण
		rtlpriv->cfg->ops->set_key(hw, key_idx, mac_addr,
					   group_key, key_type, wep_only,
					   false);
		/* <5> tell mac80211 करो something: */
		/*must use sw generate IV, or can not work !!!!. */
		key->flags |= IEEE80211_KEY_FLAG_GENERATE_IV;
		key->hw_key_idx = key_idx;
		अगर (key_type == TKIP_ENCRYPTION)
			key->flags |= IEEE80211_KEY_FLAG_GENERATE_MMIC;
		/*use software CCMP encryption क्रम management frames (MFP) */
		अगर (key_type == AESCCMP_ENCRYPTION)
			key->flags |= IEEE80211_KEY_FLAG_SW_MGMT_TX;
		अवरोध;
	हाल DISABLE_KEY:
		rtl_dbg(rtlpriv, COMP_SEC, DBG_DMESG,
			"disable key delete one entry\n");
		/*set local buf about wep key. */
		अगर (vअगर->type == NL80211_IFTYPE_AP ||
			vअगर->type == NL80211_IFTYPE_MESH_POINT) अणु
			अगर (sta)
				rtl_cam_del_entry(hw, sta->addr);
		पूर्ण
		स_रखो(rtlpriv->sec.key_buf[key_idx], 0, key->keylen);
		rtlpriv->sec.key_len[key_idx] = 0;
		eth_zero_addr(mac_addr);
		/*
		 *mac80211 will delete entrys one by one,
		 *so करोn't use rtl_cam_reset_all_entry
		 *or clear all entry here.
		 */
		rtl_रुको_tx_report_acked(hw, 500); /* रुको 500ms क्रम TX ack */

		rtl_cam_delete_one_entry(hw, mac_addr, key_idx);
		अवरोध;
	शेष:
		pr_err("cmd_err:%x!!!!:\n", cmd);
	पूर्ण
out_unlock:
	mutex_unlock(&rtlpriv->locks.conf_mutex);
	rtlpriv->sec.being_setkey = false;
	वापस err;
पूर्ण

अटल व्योम rtl_op_rfसमाप्त_poll(काष्ठा ieee80211_hw *hw)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);

	bool radio_state;
	bool blocked;
	u8 valid = 0;

	अगर (!test_bit(RTL_STATUS_INTERFACE_START, &rtlpriv->status))
		वापस;

	mutex_lock(&rtlpriv->locks.conf_mutex);

	/*अगर Radio On वापस true here */
	radio_state = rtlpriv->cfg->ops->radio_onoff_checking(hw, &valid);

	अगर (valid) अणु
		अगर (unlikely(radio_state != rtlpriv->rfसमाप्त.rfसमाप्त_state)) अणु
			rtlpriv->rfसमाप्त.rfसमाप्त_state = radio_state;

			rtl_dbg(rtlpriv, COMP_RF, DBG_DMESG,
				"wireless radio switch turned %s\n",
				radio_state ? "on" : "off");

			blocked = !rtlpriv->rfसमाप्त.rfसमाप्त_state;
			wiphy_rfसमाप्त_set_hw_state(hw->wiphy, blocked);
		पूर्ण
	पूर्ण

	mutex_unlock(&rtlpriv->locks.conf_mutex);
पूर्ण

/* this function is called by mac80211 to flush tx buffer
 * beक्रमe चयन channle or घातer save, or tx buffer packet
 * maybe send after offchannel or rf sleep, this may cause
 * dis-association by AP */
अटल व्योम rtl_op_flush(काष्ठा ieee80211_hw *hw,
			 काष्ठा ieee80211_vअगर *vअगर,
			 u32 queues,
			 bool drop)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);

	अगर (rtlpriv->पूर्णांकf_ops->flush)
		rtlpriv->पूर्णांकf_ops->flush(hw, queues, drop);
पूर्ण

अटल पूर्णांक rtl_op_set_tim(काष्ठा ieee80211_hw *hw, काष्ठा ieee80211_sta *sta,
			  bool set)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	काष्ठा rtl_hal *rtlhal = rtl_hal(rtl_priv(hw));

	अगर (rtlhal->hw_type == HARDWARE_TYPE_RTL8192CU)
		schedule_work(&rtlpriv->works.update_beacon_work);

	वापस 0;
पूर्ण

/*	Description:
 *		This routine deals with the Power Configuration CMD
 *		 parsing क्रम RTL8723/RTL8188E Series IC.
 *	Assumption:
 *		We should follow specअगरic क्रमmat that was released from HW SD.
 */
bool rtl_hal_pwrseqcmdparsing(काष्ठा rtl_priv *rtlpriv, u8 cut_version,
			      u8 faversion, u8 पूर्णांकerface_type,
			      काष्ठा wlan_pwr_cfg pwrcfgcmd[])
अणु
	काष्ठा wlan_pwr_cfg cfg_cmd;
	bool polling_bit = false;
	u32 ary_idx = 0;
	u8 value = 0;
	u32 offset = 0;
	u32 polling_count = 0;
	u32 max_polling_cnt = 5000;

	करो अणु
		cfg_cmd = pwrcfgcmd[ary_idx];
		rtl_dbg(rtlpriv, COMP_INIT, DBG_TRACE,
			"%s: offset(%#x),cut_msk(%#x), famsk(%#x), interface_msk(%#x), base(%#x), cmd(%#x), msk(%#x), value(%#x)\n",
			__func__,
			GET_PWR_CFG_OFFSET(cfg_cmd),
					   GET_PWR_CFG_CUT_MASK(cfg_cmd),
			GET_PWR_CFG_FAB_MASK(cfg_cmd),
					     GET_PWR_CFG_INTF_MASK(cfg_cmd),
			GET_PWR_CFG_BASE(cfg_cmd), GET_PWR_CFG_CMD(cfg_cmd),
			GET_PWR_CFG_MASK(cfg_cmd), GET_PWR_CFG_VALUE(cfg_cmd));

		अगर ((GET_PWR_CFG_FAB_MASK(cfg_cmd)&faversion) &&
		    (GET_PWR_CFG_CUT_MASK(cfg_cmd)&cut_version) &&
		    (GET_PWR_CFG_INTF_MASK(cfg_cmd)&पूर्णांकerface_type)) अणु
			चयन (GET_PWR_CFG_CMD(cfg_cmd)) अणु
			हाल PWR_CMD_READ:
				rtl_dbg(rtlpriv, COMP_INIT, DBG_TRACE,
					"rtl_hal_pwrseqcmdparsing(): PWR_CMD_READ\n");
				अवरोध;
			हाल PWR_CMD_WRITE:
				rtl_dbg(rtlpriv, COMP_INIT, DBG_TRACE,
					"%s(): PWR_CMD_WRITE\n", __func__);
				offset = GET_PWR_CFG_OFFSET(cfg_cmd);

				/*Read the value from प्रणाली रेजिस्टर*/
				value = rtl_पढ़ो_byte(rtlpriv, offset);
				value &= (~(GET_PWR_CFG_MASK(cfg_cmd)));
				value |= (GET_PWR_CFG_VALUE(cfg_cmd) &
					  GET_PWR_CFG_MASK(cfg_cmd));

				/*Write the value back to प्रणाली रेजिस्टर*/
				rtl_ग_लिखो_byte(rtlpriv, offset, value);
				अवरोध;
			हाल PWR_CMD_POLLING:
				rtl_dbg(rtlpriv, COMP_INIT, DBG_TRACE,
					"rtl_hal_pwrseqcmdparsing(): PWR_CMD_POLLING\n");
				polling_bit = false;
				offset = GET_PWR_CFG_OFFSET(cfg_cmd);

				करो अणु
					value = rtl_पढ़ो_byte(rtlpriv, offset);

					value &= GET_PWR_CFG_MASK(cfg_cmd);
					अगर (value ==
					    (GET_PWR_CFG_VALUE(cfg_cmd) &
					     GET_PWR_CFG_MASK(cfg_cmd)))
						polling_bit = true;
					अन्यथा
						udelay(10);

					अगर (polling_count++ > max_polling_cnt)
						वापस false;
				पूर्ण जबतक (!polling_bit);
				अवरोध;
			हाल PWR_CMD_DELAY:
				rtl_dbg(rtlpriv, COMP_INIT, DBG_TRACE,
					"%s: PWR_CMD_DELAY\n", __func__);
				अगर (GET_PWR_CFG_VALUE(cfg_cmd) ==
				    PWRSEQ_DELAY_US)
					udelay(GET_PWR_CFG_OFFSET(cfg_cmd));
				अन्यथा
					mdelay(GET_PWR_CFG_OFFSET(cfg_cmd));
				अवरोध;
			हाल PWR_CMD_END:
				rtl_dbg(rtlpriv, COMP_INIT, DBG_TRACE,
					"%s: PWR_CMD_END\n", __func__);
				वापस true;
			शेष:
				WARN_ONCE(true,
					  "rtlwifi: rtl_hal_pwrseqcmdparsing(): Unknown CMD!!\n");
				अवरोध;
			पूर्ण
		पूर्ण
		ary_idx++;
	पूर्ण जबतक (1);

	वापस true;
पूर्ण
EXPORT_SYMBOL(rtl_hal_pwrseqcmdparsing);

bool rtl_cmd_send_packet(काष्ठा ieee80211_hw *hw, काष्ठा sk_buff *skb)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	काष्ठा rtl_pci *rtlpci = rtl_pcidev(rtl_pcipriv(hw));
	काष्ठा rtl8192_tx_ring *ring;
	काष्ठा rtl_tx_desc *pdesc;
	अचिन्हित दीर्घ flags;
	काष्ठा sk_buff *pskb = शून्य;

	ring = &rtlpci->tx_ring[BEACON_QUEUE];

	spin_lock_irqsave(&rtlpriv->locks.irq_th_lock, flags);
	pskb = __skb_dequeue(&ring->queue);
	अगर (pskb)
		dev_kमुक्त_skb_irq(pskb);

	/*this is wrong, fill_tx_cmddesc needs update*/
	pdesc = &ring->desc[0];

	rtlpriv->cfg->ops->fill_tx_cmddesc(hw, (u8 *)pdesc, 1, 1, skb);

	__skb_queue_tail(&ring->queue, skb);

	spin_unlock_irqrestore(&rtlpriv->locks.irq_th_lock, flags);

	rtlpriv->cfg->ops->tx_polling(hw, BEACON_QUEUE);

	वापस true;
पूर्ण
EXPORT_SYMBOL(rtl_cmd_send_packet);
स्थिर काष्ठा ieee80211_ops rtl_ops = अणु
	.start = rtl_op_start,
	.stop = rtl_op_stop,
	.tx = rtl_op_tx,
	.add_पूर्णांकerface = rtl_op_add_पूर्णांकerface,
	.हटाओ_पूर्णांकerface = rtl_op_हटाओ_पूर्णांकerface,
	.change_पूर्णांकerface = rtl_op_change_पूर्णांकerface,
#अगर_घोषित CONFIG_PM
	.suspend = rtl_op_suspend,
	.resume = rtl_op_resume,
#पूर्ण_अगर
	.config = rtl_op_config,
	.configure_filter = rtl_op_configure_filter,
	.set_key = rtl_op_set_key,
	.conf_tx = rtl_op_conf_tx,
	.bss_info_changed = rtl_op_bss_info_changed,
	.get_tsf = rtl_op_get_tsf,
	.set_tsf = rtl_op_set_tsf,
	.reset_tsf = rtl_op_reset_tsf,
	.sta_notअगरy = rtl_op_sta_notअगरy,
	.ampdu_action = rtl_op_ampdu_action,
	.sw_scan_start = rtl_op_sw_scan_start,
	.sw_scan_complete = rtl_op_sw_scan_complete,
	.rfसमाप्त_poll = rtl_op_rfसमाप्त_poll,
	.sta_add = rtl_op_sta_add,
	.sta_हटाओ = rtl_op_sta_हटाओ,
	.flush = rtl_op_flush,
	.set_tim = rtl_op_set_tim,
पूर्ण;
EXPORT_SYMBOL_GPL(rtl_ops);

bool rtl_btc_status_false(व्योम)
अणु
	वापस false;
पूर्ण
EXPORT_SYMBOL_GPL(rtl_btc_status_false);

व्योम rtl_dm_diginit(काष्ठा ieee80211_hw *hw, u32 cur_igvalue)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	काष्ठा dig_t *dm_digtable = &rtlpriv->dm_digtable;

	dm_digtable->dig_enable_flag = true;
	dm_digtable->dig_ext_port_stage = DIG_EXT_PORT_STAGE_MAX;
	dm_digtable->cur_igvalue = cur_igvalue;
	dm_digtable->pre_igvalue = 0;
	dm_digtable->cur_sta_cstate = DIG_STA_DISCONNECT;
	dm_digtable->presta_cstate = DIG_STA_DISCONNECT;
	dm_digtable->curmultista_cstate = DIG_MULTISTA_DISCONNECT;
	dm_digtable->rssi_lowthresh = DM_DIG_THRESH_LOW;
	dm_digtable->rssi_highthresh = DM_DIG_THRESH_HIGH;
	dm_digtable->fa_lowthresh = DM_FALSEALARM_THRESH_LOW;
	dm_digtable->fa_highthresh = DM_FALSEALARM_THRESH_HIGH;
	dm_digtable->rx_gain_max = DM_DIG_MAX;
	dm_digtable->rx_gain_min = DM_DIG_MIN;
	dm_digtable->back_val = DM_DIG_BACKOFF_DEFAULT;
	dm_digtable->back_range_max = DM_DIG_BACKOFF_MAX;
	dm_digtable->back_range_min = DM_DIG_BACKOFF_MIN;
	dm_digtable->pre_cck_cca_thres = 0xff;
	dm_digtable->cur_cck_cca_thres = 0x83;
	dm_digtable->क्रमbidden_igi = DM_DIG_MIN;
	dm_digtable->large_fa_hit = 0;
	dm_digtable->recover_cnt = 0;
	dm_digtable->dig_min_0 = 0x25;
	dm_digtable->dig_min_1 = 0x25;
	dm_digtable->media_connect_0 = false;
	dm_digtable->media_connect_1 = false;
	rtlpriv->dm.dm_initialgain_enable = true;
	dm_digtable->bt30_cur_igi = 0x32;
	dm_digtable->pre_cck_pd_state = CCK_PD_STAGE_MAX;
	dm_digtable->cur_cck_pd_state = CCK_PD_STAGE_LOWRSSI;
	dm_digtable->pre_cck_fa_state = 0;
	dm_digtable->cur_cck_fa_state = 0;
पूर्ण
EXPORT_SYMBOL(rtl_dm_diginit);
