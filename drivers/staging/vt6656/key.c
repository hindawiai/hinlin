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
 * Functions:
 *
 * Revision History:
 *
 */

#समावेश "mac.h"
#समावेश "key.h"
#समावेश "usbpipe.h"

पूर्णांक vnt_key_init_table(काष्ठा vnt_निजी *priv)
अणु
	u8 i;
	u8 data[MAX_KEY_TABLE];

	क्रम (i = 0; i < MAX_KEY_TABLE; i++)
		data[i] = i;

	वापस vnt_control_out(priv, MESSAGE_TYPE_CLRKEYENTRY,
			0, 0, ARRAY_SIZE(data), data);
पूर्ण

अटल पूर्णांक vnt_set_keymode(काष्ठा ieee80211_hw *hw, u8 *mac_addr,
			   काष्ठा ieee80211_key_conf *key, u32 key_type,
			   u32 mode)
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
	हाल VNT_KEY_GROUP_ADDRESS:
		key_mode = mode | (mode << 4);
		अवरोध;
	हाल VNT_KEY_GROUP:
		key_mode = mode << 4;
		अवरोध;
	हाल  VNT_KEY_PAIRWISE:
		key_mode |= mode;
		key_inx = 4;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	key_mode |= key_type;

	अगर (mode == KEY_CTL_WEP) अणु
		अगर (key->keylen == WLAN_KEY_LEN_WEP40)
			key->key[15] &= 0x7f;
		अगर (key->keylen == WLAN_KEY_LEN_WEP104)
			key->key[15] |= 0x80;
	पूर्ण

	वापस vnt_mac_set_keyentry(priv, key_mode, entry,
				    key_inx, bssid, key->key);
पूर्ण

पूर्णांक vnt_set_keys(काष्ठा ieee80211_hw *hw, काष्ठा ieee80211_sta *sta,
		 काष्ठा ieee80211_vअगर *vअगर, काष्ठा ieee80211_key_conf *key)
अणु
	काष्ठा vnt_निजी *priv = hw->priv;
	u8 *mac_addr = शून्य;
	u8 key_dec_mode = 0;

	अगर (sta)
		mac_addr = &sta->addr[0];

	चयन (key->cipher) अणु
	हाल WLAN_CIPHER_SUITE_WEP40:
	हाल WLAN_CIPHER_SUITE_WEP104:
		vnt_set_keymode(hw, mac_addr, key, VNT_KEY_DEFAULTKEY,
				KEY_CTL_WEP);

		key->flags |= IEEE80211_KEY_FLAG_GENERATE_IV;

		वापस vnt_set_keymode(hw, mac_addr, key, VNT_KEY_DEFAULTKEY,
				       KEY_CTL_WEP);

	हाल WLAN_CIPHER_SUITE_TKIP:
		key->flags |= IEEE80211_KEY_FLAG_GENERATE_MMIC;
		key->flags |= IEEE80211_KEY_FLAG_GENERATE_IV;

		key_dec_mode = KEY_CTL_TKIP;

		अवरोध;
	हाल WLAN_CIPHER_SUITE_CCMP:
		अगर (priv->local_id <= MAC_REVISION_A1)
			वापस -EOPNOTSUPP;

		key_dec_mode = KEY_CTL_CCMP;

		key->flags |= IEEE80211_KEY_FLAG_GENERATE_IV;
		अवरोध;
	शेष:
		वापस -EOPNOTSUPP;
	पूर्ण

	अगर (key->flags & IEEE80211_KEY_FLAG_PAIRWISE)
		वापस vnt_set_keymode(hw, mac_addr, key, VNT_KEY_PAIRWISE,
				       key_dec_mode);

	वापस vnt_set_keymode(hw, mac_addr, key,
				VNT_KEY_GROUP_ADDRESS, key_dec_mode);
पूर्ण
