<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/* Copyright(c) 2009-2012  Realtek Corporation.*/

#समावेश "wifi.h"
#समावेश "cam.h"
#समावेश <linux/export.h>

व्योम rtl_cam_reset_sec_info(काष्ठा ieee80211_hw *hw)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);

	rtlpriv->sec.use_शेषkey = false;
	rtlpriv->sec.pairwise_enc_algorithm = NO_ENCRYPTION;
	rtlpriv->sec.group_enc_algorithm = NO_ENCRYPTION;
	स_रखो(rtlpriv->sec.key_buf, 0, KEY_BUF_SIZE * MAX_KEY_LEN);
	स_रखो(rtlpriv->sec.key_len, 0, KEY_BUF_SIZE);
	rtlpriv->sec.pairwise_key = शून्य;
पूर्ण

अटल व्योम rtl_cam_program_entry(काष्ठा ieee80211_hw *hw, u32 entry_no,
			   u8 *mac_addr, u8 *key_cont_128, u16 us_config)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);

	u32 target_command;
	u32 target_content = 0;
	पूर्णांक entry_i;

	RT_PRINT_DATA(rtlpriv, COMP_SEC, DBG_DMESG, "Key content :",
		      key_cont_128, 16);

	/* 0-1 config + mac, 2-5 fill 128key,6-7 are reserved */
	क्रम (entry_i = CAM_CONTENT_COUNT - 1; entry_i >= 0; entry_i--) अणु
		target_command = entry_i + CAM_CONTENT_COUNT * entry_no;
		target_command = target_command | BIT(31) | BIT(16);

		अगर (entry_i == 0) अणु
			target_content = (u32) (*(mac_addr + 0)) << 16 |
			    (u32) (*(mac_addr + 1)) << 24 | (u32) us_config;

			rtl_ग_लिखो_dword(rtlpriv, rtlpriv->cfg->maps[WCAMI],
					target_content);
			rtl_ग_लिखो_dword(rtlpriv, rtlpriv->cfg->maps[RWCAM],
					target_command);

			rtl_dbg(rtlpriv, COMP_SEC, DBG_LOUD,
				"WRITE %x: %x\n",
				rtlpriv->cfg->maps[WCAMI], target_content);
			rtl_dbg(rtlpriv, COMP_SEC, DBG_LOUD,
				"The Key ID is %d\n", entry_no);
			rtl_dbg(rtlpriv, COMP_SEC, DBG_LOUD,
				"WRITE %x: %x\n",
				rtlpriv->cfg->maps[RWCAM], target_command);

		पूर्ण अन्यथा अगर (entry_i == 1) अणु

			target_content = (u32) (*(mac_addr + 5)) << 24 |
			    (u32) (*(mac_addr + 4)) << 16 |
			    (u32) (*(mac_addr + 3)) << 8 |
			    (u32) (*(mac_addr + 2));

			rtl_ग_लिखो_dword(rtlpriv, rtlpriv->cfg->maps[WCAMI],
					target_content);
			rtl_ग_लिखो_dword(rtlpriv, rtlpriv->cfg->maps[RWCAM],
					target_command);

			rtl_dbg(rtlpriv, COMP_SEC, DBG_LOUD,
				"WRITE A4: %x\n", target_content);
			rtl_dbg(rtlpriv, COMP_SEC, DBG_LOUD,
				"WRITE A0: %x\n", target_command);

		पूर्ण अन्यथा अणु

			target_content =
			    (u32) (*(key_cont_128 + (entry_i * 4 - 8) + 3)) <<
			    24 | (u32) (*(key_cont_128 + (entry_i * 4 - 8) + 2))
			    << 16 |
			    (u32) (*(key_cont_128 + (entry_i * 4 - 8) + 1)) << 8
			    | (u32) (*(key_cont_128 + (entry_i * 4 - 8) + 0));

			rtl_ग_लिखो_dword(rtlpriv, rtlpriv->cfg->maps[WCAMI],
					target_content);
			rtl_ग_लिखो_dword(rtlpriv, rtlpriv->cfg->maps[RWCAM],
					target_command);

			rtl_dbg(rtlpriv, COMP_SEC, DBG_LOUD,
				"WRITE A4: %x\n", target_content);
			rtl_dbg(rtlpriv, COMP_SEC, DBG_LOUD,
				"WRITE A0: %x\n", target_command);
		पूर्ण
	पूर्ण

	rtl_dbg(rtlpriv, COMP_SEC, DBG_LOUD,
		"after set key, usconfig:%x\n", us_config);
पूर्ण

u8 rtl_cam_add_one_entry(काष्ठा ieee80211_hw *hw, u8 *mac_addr,
			 u32 ul_key_id, u32 ul_entry_idx, u32 ul_enc_alg,
			 u32 ul_शेष_key, u8 *key_content)
अणु
	u32 us_config;
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);

	rtl_dbg(rtlpriv, COMP_SEC, DBG_DMESG,
		"EntryNo:%x, ulKeyId=%x, ulEncAlg=%x, ulUseDK=%x MacAddr %pM\n",
		ul_entry_idx, ul_key_id, ul_enc_alg,
		ul_शेष_key, mac_addr);

	अगर (ul_key_id == TOTAL_CAM_ENTRY) अणु
		rtl_dbg(rtlpriv, COMP_ERR, DBG_WARNING,
			"ulKeyId exceed!\n");
		वापस 0;
	पूर्ण

	अगर (ul_शेष_key == 1)
		us_config = CFG_VALID | ((u16) (ul_enc_alg) << 2);
	अन्यथा
		us_config = CFG_VALID | ((ul_enc_alg) << 2) | ul_key_id;

	rtl_cam_program_entry(hw, ul_entry_idx, mac_addr,
			      (u8 *)key_content, us_config);

	rtl_dbg(rtlpriv, COMP_SEC, DBG_DMESG, "end\n");

	वापस 1;

पूर्ण
EXPORT_SYMBOL(rtl_cam_add_one_entry);

पूर्णांक rtl_cam_delete_one_entry(काष्ठा ieee80211_hw *hw,
			     u8 *mac_addr, u32 ul_key_id)
अणु
	u32 ul_command;
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);

	rtl_dbg(rtlpriv, COMP_SEC, DBG_DMESG, "key_idx:%d\n", ul_key_id);

	ul_command = ul_key_id * CAM_CONTENT_COUNT;
	ul_command = ul_command | BIT(31) | BIT(16);

	rtl_ग_लिखो_dword(rtlpriv, rtlpriv->cfg->maps[WCAMI], 0);
	rtl_ग_लिखो_dword(rtlpriv, rtlpriv->cfg->maps[RWCAM], ul_command);

	rtl_dbg(rtlpriv, COMP_SEC, DBG_DMESG,
		"%s: WRITE A4: %x\n", __func__, 0);
	rtl_dbg(rtlpriv, COMP_SEC, DBG_DMESG,
		"%s: WRITE A0: %x\n", __func__, ul_command);

	वापस 0;

पूर्ण
EXPORT_SYMBOL(rtl_cam_delete_one_entry);

व्योम rtl_cam_reset_all_entry(काष्ठा ieee80211_hw *hw)
अणु
	u32 ul_command;
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);

	ul_command = BIT(31) | BIT(30);
	rtl_ग_लिखो_dword(rtlpriv, rtlpriv->cfg->maps[RWCAM], ul_command);
पूर्ण
EXPORT_SYMBOL(rtl_cam_reset_all_entry);

व्योम rtl_cam_mark_invalid(काष्ठा ieee80211_hw *hw, u8 uc_index)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);

	u32 ul_command;
	u32 ul_content;
	u32 ul_enc_algo = rtlpriv->cfg->maps[SEC_CAM_AES];

	चयन (rtlpriv->sec.pairwise_enc_algorithm) अणु
	हाल WEP40_ENCRYPTION:
		ul_enc_algo = rtlpriv->cfg->maps[SEC_CAM_WEP40];
		अवरोध;
	हाल WEP104_ENCRYPTION:
		ul_enc_algo = rtlpriv->cfg->maps[SEC_CAM_WEP104];
		अवरोध;
	हाल TKIP_ENCRYPTION:
		ul_enc_algo = rtlpriv->cfg->maps[SEC_CAM_TKIP];
		अवरोध;
	हाल AESCCMP_ENCRYPTION:
		ul_enc_algo = rtlpriv->cfg->maps[SEC_CAM_AES];
		अवरोध;
	शेष:
		ul_enc_algo = rtlpriv->cfg->maps[SEC_CAM_AES];
	पूर्ण

	ul_content = (uc_index & 3) | ((u16) (ul_enc_algo) << 2);

	ul_content |= BIT(15);
	ul_command = CAM_CONTENT_COUNT * uc_index;
	ul_command = ul_command | BIT(31) | BIT(16);

	rtl_ग_लिखो_dword(rtlpriv, rtlpriv->cfg->maps[WCAMI], ul_content);
	rtl_ग_लिखो_dword(rtlpriv, rtlpriv->cfg->maps[RWCAM], ul_command);

	rtl_dbg(rtlpriv, COMP_SEC, DBG_DMESG,
		"%s: WRITE A4: %x\n", __func__, ul_content);
	rtl_dbg(rtlpriv, COMP_SEC, DBG_DMESG,
		"%s: WRITE A0: %x\n", __func__, ul_command);
पूर्ण
EXPORT_SYMBOL(rtl_cam_mark_invalid);

व्योम rtl_cam_empty_entry(काष्ठा ieee80211_hw *hw, u8 uc_index)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);

	u32 ul_command;
	u32 ul_content;
	u32 ul_encalgo = rtlpriv->cfg->maps[SEC_CAM_AES];
	u8 entry_i;

	चयन (rtlpriv->sec.pairwise_enc_algorithm) अणु
	हाल WEP40_ENCRYPTION:
		ul_encalgo = rtlpriv->cfg->maps[SEC_CAM_WEP40];
		अवरोध;
	हाल WEP104_ENCRYPTION:
		ul_encalgo = rtlpriv->cfg->maps[SEC_CAM_WEP104];
		अवरोध;
	हाल TKIP_ENCRYPTION:
		ul_encalgo = rtlpriv->cfg->maps[SEC_CAM_TKIP];
		अवरोध;
	हाल AESCCMP_ENCRYPTION:
		ul_encalgo = rtlpriv->cfg->maps[SEC_CAM_AES];
		अवरोध;
	शेष:
		ul_encalgo = rtlpriv->cfg->maps[SEC_CAM_AES];
	पूर्ण

	क्रम (entry_i = 0; entry_i < CAM_CONTENT_COUNT; entry_i++) अणु

		अगर (entry_i == 0) अणु
			ul_content =
			    (uc_index & 0x03) | ((u16) (ul_encalgo) << 2);
			ul_content |= BIT(15);

		पूर्ण अन्यथा अणु
			ul_content = 0;
		पूर्ण

		ul_command = CAM_CONTENT_COUNT * uc_index + entry_i;
		ul_command = ul_command | BIT(31) | BIT(16);

		rtl_ग_लिखो_dword(rtlpriv, rtlpriv->cfg->maps[WCAMI], ul_content);
		rtl_ग_लिखो_dword(rtlpriv, rtlpriv->cfg->maps[RWCAM], ul_command);

		rtl_dbg(rtlpriv, COMP_SEC, DBG_LOUD,
			"%s: WRITE A4: %x\n", __func__, ul_content);
		rtl_dbg(rtlpriv, COMP_SEC, DBG_LOUD,
			"%s: WRITE A0: %x\n", __func__, ul_command);
	पूर्ण

पूर्ण
EXPORT_SYMBOL(rtl_cam_empty_entry);

u8 rtl_cam_get_मुक्त_entry(काष्ठा ieee80211_hw *hw, u8 *sta_addr)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	u32 biपंचांगap = (rtlpriv->sec.hwsec_cam_biपंचांगap) >> 4;
	u8 entry_idx = 0;
	u8 i, *addr;

	अगर (शून्य == sta_addr) अणु
		pr_err("sta_addr is NULL.\n");
		वापस TOTAL_CAM_ENTRY;
	पूर्ण
	/* Does STA alपढ़ोy exist? */
	क्रम (i = 4; i < TOTAL_CAM_ENTRY; i++) अणु
		addr = rtlpriv->sec.hwsec_cam_sta_addr[i];
		अगर (ether_addr_equal_unaligned(addr, sta_addr))
			वापस i;
	पूर्ण
	/* Get a मुक्त CAM entry. */
	क्रम (entry_idx = 4; entry_idx < TOTAL_CAM_ENTRY; entry_idx++) अणु
		अगर ((biपंचांगap & BIT(0)) == 0) अणु
			pr_err("-----hwsec_cam_bitmap: 0x%x entry_idx=%d\n",
			       rtlpriv->sec.hwsec_cam_biपंचांगap, entry_idx);
			rtlpriv->sec.hwsec_cam_biपंचांगap |= BIT(0) << entry_idx;
			स_नकल(rtlpriv->sec.hwsec_cam_sta_addr[entry_idx],
			       sta_addr, ETH_ALEN);
			वापस entry_idx;
		पूर्ण
		biपंचांगap = biपंचांगap >> 1;
	पूर्ण
	वापस TOTAL_CAM_ENTRY;
पूर्ण
EXPORT_SYMBOL(rtl_cam_get_मुक्त_entry);

व्योम rtl_cam_del_entry(काष्ठा ieee80211_hw *hw, u8 *sta_addr)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	u32 biपंचांगap;
	u8 i, *addr;

	अगर (शून्य == sta_addr) अणु
		pr_err("sta_addr is NULL.\n");
		वापस;
	पूर्ण

	अगर (is_zero_ether_addr(sta_addr)) अणु
		pr_err("sta_addr is %pM\n", sta_addr);
		वापस;
	पूर्ण
	/* Does STA alपढ़ोy exist? */
	क्रम (i = 4; i < TOTAL_CAM_ENTRY; i++) अणु
		addr = rtlpriv->sec.hwsec_cam_sta_addr[i];
		biपंचांगap = (rtlpriv->sec.hwsec_cam_biपंचांगap) >> i;
		अगर (((biपंचांगap & BIT(0)) == BIT(0)) &&
		    (ether_addr_equal_unaligned(addr, sta_addr))) अणु
			/* Remove from HW Security CAM */
			eth_zero_addr(rtlpriv->sec.hwsec_cam_sta_addr[i]);
			rtlpriv->sec.hwsec_cam_biपंचांगap &= ~(BIT(0) << i);
			rtl_dbg(rtlpriv, COMP_SEC, DBG_DMESG,
				"&&&&&&&&&del entry %d\n", i);
		पूर्ण
	पूर्ण
	वापस;
पूर्ण
EXPORT_SYMBOL(rtl_cam_del_entry);
