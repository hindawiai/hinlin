<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * Copyright (c) 1996, 2003 VIA Networking Technologies, Inc.
 * All rights reserved.
 *
 * File: key.c
 *
 * Purpose: Implement functions क्रम 802.11i Key management
 *
 * Author: Jerry Chen
 *
 * Date: May 29, 2003
 *
 */

#समावेश "tmacro.h"
#समावेश "key.h"
#समावेश "mac.h"

अटल पूर्णांक vnt_set_keymode(काष्ठा ieee80211_hw *hw, u8 *mac_addr,
			   काष्ठा ieee80211_key_conf *key, u32 key_type,
			   u32 mode, bool onfly_latch)
अणु
	काष्ठा vnt_निजी *priv = hw->priv;
	u8 broadcast[6] = अणु0xff, 0xff, 0xff, 0xff, 0xff, 0xffपूर्ण;
	u16 key_mode = 0;
	u32 entry = 0;
	u8 *bssid;
	u8 key_inx = key->keyidx;
	u8 i;

	अगर (mac_addr)
		bssid = mac_addr;
	अन्यथा
		bssid = &broadcast[0];

	अगर (key_type != VNT_KEY_DEFAULTKEY) अणु
		क्रम (i = 0; i < (MAX_KEY_TABLE - 1); i++) अणु
			अगर (!test_bit(i, &priv->key_entry_inuse)) अणु
				set_bit(i, &priv->key_entry_inuse);

				key->hw_key_idx = i;
				entry = key->hw_key_idx;
				अवरोध;
			पूर्ण
		पूर्ण
	पूर्ण

	चयन (key_type) अणु
	हाल VNT_KEY_DEFAULTKEY:
		/* शेष key last entry */
		entry = MAX_KEY_TABLE - 1;
		key->hw_key_idx = entry;
		fallthrough;
	हाल VNT_KEY_ALLGROUP:
		key_mode |= VNT_KEY_ALLGROUP;
		अगर (onfly_latch)
			key_mode |= VNT_KEY_ONFLY_ALL;
		fallthrough;
	हाल VNT_KEY_GROUP_ADDRESS:
		key_mode |= mode;
		fallthrough;
	हाल VNT_KEY_GROUP:
		key_mode |= (mode << 4);
		key_mode |= VNT_KEY_GROUP;
		अवरोध;
	हाल  VNT_KEY_PAIRWISE:
		key_mode |= mode;
		key_inx = 4;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	अगर (onfly_latch)
		key_mode |= VNT_KEY_ONFLY;

	अगर (mode == KEY_CTL_WEP) अणु
		अगर (key->keylen == WLAN_KEY_LEN_WEP40)
			key->key[15] &= 0x7f;
		अगर (key->keylen == WLAN_KEY_LEN_WEP104)
			key->key[15] |= 0x80;
	पूर्ण

	MACvSetKeyEntry(priv, key_mode, entry, key_inx,
			bssid, (u32 *)key->key, priv->byLocalID);

	वापस 0;
पूर्ण

पूर्णांक vnt_set_keys(काष्ठा ieee80211_hw *hw, काष्ठा ieee80211_sta *sta,
		 काष्ठा ieee80211_vअगर *vअगर, काष्ठा ieee80211_key_conf *key)
अणु
	काष्ठा ieee80211_bss_conf *conf = &vअगर->bss_conf;
	काष्ठा vnt_निजी *priv = hw->priv;
	u8 *mac_addr = शून्य;
	u8 key_dec_mode = 0;
	पूर्णांक ret = 0;
	u32 u;

	अगर (sta)
		mac_addr = &sta->addr[0];

	चयन (key->cipher) अणु
	हाल 0:
		क्रम (u = 0 ; u < MAX_KEY_TABLE; u++)
			MACvDisableKeyEntry(priv, u);
		वापस ret;

	हाल WLAN_CIPHER_SUITE_WEP40:
	हाल WLAN_CIPHER_SUITE_WEP104:
		क्रम (u = 0; u < MAX_KEY_TABLE; u++)
			MACvDisableKeyEntry(priv, u);

		vnt_set_keymode(hw, mac_addr,
				key, VNT_KEY_DEFAULTKEY, KEY_CTL_WEP, true);

		key->flags |= IEEE80211_KEY_FLAG_GENERATE_IV;

		वापस ret;
	हाल WLAN_CIPHER_SUITE_TKIP:
		key->flags |= IEEE80211_KEY_FLAG_GENERATE_MMIC;
		key->flags |= IEEE80211_KEY_FLAG_GENERATE_IV;

		key_dec_mode = KEY_CTL_TKIP;

		अवरोध;
	हाल WLAN_CIPHER_SUITE_CCMP:
		key_dec_mode = KEY_CTL_CCMP;

		key->flags |= IEEE80211_KEY_FLAG_GENERATE_IV;
	पूर्ण

	अगर (key->flags & IEEE80211_KEY_FLAG_PAIRWISE) अणु
		vnt_set_keymode(hw, mac_addr,
				key, VNT_KEY_PAIRWISE, key_dec_mode, true);
	पूर्ण अन्यथा अणु
		vnt_set_keymode(hw, mac_addr,
				key, VNT_KEY_DEFAULTKEY, key_dec_mode, true);

		vnt_set_keymode(hw, (u8 *)conf->bssid,
				key, VNT_KEY_GROUP_ADDRESS, key_dec_mode, true);
	पूर्ण

	वापस 0;
पूर्ण
