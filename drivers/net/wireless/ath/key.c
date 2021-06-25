<शैली गुरु>
/*
 * Copyright (c) 2009 Atheros Communications Inc.
 * Copyright (c) 2010 Bruno Ranकरोlf <br1@einfach.org>
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

#समावेश <linux/export.h>
#समावेश <यंत्र/unaligned.h>
#समावेश <net/mac80211.h>

#समावेश "ath.h"
#समावेश "reg.h"

#घोषणा REG_READ			(common->ops->पढ़ो)
#घोषणा REG_WRITE(_ah, _reg, _val)	(common->ops->ग_लिखो)(_ah, _val, _reg)
#घोषणा ENABLE_REGWRITE_BUFFER(_ah)			\
	अगर (common->ops->enable_ग_लिखो_buffer)		\
		common->ops->enable_ग_लिखो_buffer((_ah));

#घोषणा REGWRITE_BUFFER_FLUSH(_ah)			\
	अगर (common->ops->ग_लिखो_flush)			\
		common->ops->ग_लिखो_flush((_ah));


#घोषणा IEEE80211_WEP_NKID      4       /* number of key ids */

/************************/
/* Key Cache Management */
/************************/

bool ath_hw_keyreset(काष्ठा ath_common *common, u16 entry)
अणु
	u32 keyType;
	व्योम *ah = common->ah;

	अगर (entry >= common->keymax) अणु
		ath_err(common, "keyreset: keycache entry %u out of range\n",
			entry);
		वापस false;
	पूर्ण

	keyType = REG_READ(ah, AR_KEYTABLE_TYPE(entry));

	ENABLE_REGWRITE_BUFFER(ah);

	REG_WRITE(ah, AR_KEYTABLE_KEY0(entry), 0);
	REG_WRITE(ah, AR_KEYTABLE_KEY1(entry), 0);
	REG_WRITE(ah, AR_KEYTABLE_KEY2(entry), 0);
	REG_WRITE(ah, AR_KEYTABLE_KEY3(entry), 0);
	REG_WRITE(ah, AR_KEYTABLE_KEY4(entry), 0);
	REG_WRITE(ah, AR_KEYTABLE_TYPE(entry), AR_KEYTABLE_TYPE_CLR);
	REG_WRITE(ah, AR_KEYTABLE_MAC0(entry), 0);
	REG_WRITE(ah, AR_KEYTABLE_MAC1(entry), 0);

	अगर (keyType == AR_KEYTABLE_TYPE_TKIP) अणु
		u16 micentry = entry + 64;

		REG_WRITE(ah, AR_KEYTABLE_KEY0(micentry), 0);
		REG_WRITE(ah, AR_KEYTABLE_KEY1(micentry), 0);
		REG_WRITE(ah, AR_KEYTABLE_KEY2(micentry), 0);
		REG_WRITE(ah, AR_KEYTABLE_KEY3(micentry), 0);
		अगर (common->crypt_caps & ATH_CRYPT_CAP_MIC_COMBINED) अणु
			REG_WRITE(ah, AR_KEYTABLE_KEY4(micentry), 0);
			REG_WRITE(ah, AR_KEYTABLE_TYPE(micentry),
				  AR_KEYTABLE_TYPE_CLR);
		पूर्ण

	पूर्ण

	REGWRITE_BUFFER_FLUSH(ah);

	वापस true;
पूर्ण
EXPORT_SYMBOL(ath_hw_keyreset);

bool ath_hw_keyseपंचांगac(काष्ठा ath_common *common, u16 entry, स्थिर u8 *mac)
अणु
	u32 macHi, macLo;
	u32 unicast_flag = AR_KEYTABLE_VALID;
	व्योम *ah = common->ah;

	अगर (entry >= common->keymax) अणु
		ath_err(common, "keysetmac: keycache entry %u out of range\n",
			entry);
		वापस false;
	पूर्ण

	अगर (mac != शून्य) अणु
		/*
		 * AR_KEYTABLE_VALID indicates that the address is a unicast
		 * address, which must match the transmitter address क्रम
		 * decrypting frames.
		 * Not setting this bit allows the hardware to use the key
		 * क्रम multicast frame decryption.
		 */
		अगर (mac[0] & 0x01)
			unicast_flag = 0;

		macLo = get_unaligned_le32(mac);
		macHi = get_unaligned_le16(mac + 4);
		macLo >>= 1;
		macLo |= (macHi & 1) << 31;
		macHi >>= 1;
	पूर्ण अन्यथा अणु
		macLo = macHi = 0;
	पूर्ण
	ENABLE_REGWRITE_BUFFER(ah);

	REG_WRITE(ah, AR_KEYTABLE_MAC0(entry), macLo);
	REG_WRITE(ah, AR_KEYTABLE_MAC1(entry), macHi | unicast_flag);

	REGWRITE_BUFFER_FLUSH(ah);

	वापस true;
पूर्ण
EXPORT_SYMBOL(ath_hw_keyseपंचांगac);

अटल bool ath_hw_set_keycache_entry(काष्ठा ath_common *common, u16 entry,
				      स्थिर काष्ठा ath_keyval *k,
				      स्थिर u8 *mac)
अणु
	व्योम *ah = common->ah;
	u32 key0, key1, key2, key3, key4;
	u32 keyType;

	अगर (entry >= common->keymax) अणु
		ath_err(common, "set-entry: keycache entry %u out of range\n",
			entry);
		वापस false;
	पूर्ण

	चयन (k->kv_type) अणु
	हाल ATH_CIPHER_AES_OCB:
		keyType = AR_KEYTABLE_TYPE_AES;
		अवरोध;
	हाल ATH_CIPHER_AES_CCM:
		अगर (!(common->crypt_caps & ATH_CRYPT_CAP_CIPHER_AESCCM)) अणु
			ath_dbg(common, ANY,
				"AES-CCM not supported by this mac rev\n");
			वापस false;
		पूर्ण
		keyType = AR_KEYTABLE_TYPE_CCM;
		अवरोध;
	हाल ATH_CIPHER_TKIP:
		keyType = AR_KEYTABLE_TYPE_TKIP;
		अगर (entry + 64 >= common->keymax) अणु
			ath_dbg(common, ANY,
				"entry %u inappropriate for TKIP\n", entry);
			वापस false;
		पूर्ण
		अवरोध;
	हाल ATH_CIPHER_WEP:
		अगर (k->kv_len < WLAN_KEY_LEN_WEP40) अणु
			ath_dbg(common, ANY, "WEP key length %u too small\n",
				k->kv_len);
			वापस false;
		पूर्ण
		अगर (k->kv_len <= WLAN_KEY_LEN_WEP40)
			keyType = AR_KEYTABLE_TYPE_40;
		अन्यथा अगर (k->kv_len <= WLAN_KEY_LEN_WEP104)
			keyType = AR_KEYTABLE_TYPE_104;
		अन्यथा
			keyType = AR_KEYTABLE_TYPE_128;
		अवरोध;
	हाल ATH_CIPHER_CLR:
		keyType = AR_KEYTABLE_TYPE_CLR;
		अवरोध;
	शेष:
		ath_err(common, "cipher %u not supported\n", k->kv_type);
		वापस false;
	पूर्ण

	key0 = get_unaligned_le32(k->kv_val + 0);
	key1 = get_unaligned_le16(k->kv_val + 4);
	key2 = get_unaligned_le32(k->kv_val + 6);
	key3 = get_unaligned_le16(k->kv_val + 10);
	key4 = get_unaligned_le32(k->kv_val + 12);
	अगर (k->kv_len <= WLAN_KEY_LEN_WEP104)
		key4 &= 0xff;

	/*
	 * Note: Key cache रेजिस्टरs access special memory area that requires
	 * two 32-bit ग_लिखोs to actually update the values in the पूर्णांकernal
	 * memory. Consequently, the exact order and pairs used here must be
	 * मुख्यtained.
	 */

	अगर (keyType == AR_KEYTABLE_TYPE_TKIP) अणु
		u16 micentry = entry + 64;

		/*
		 * Write inverted key[47:0] first to aव्योम Michael MIC errors
		 * on frames that could be sent or received at the same समय.
		 * The correct key will be written in the end once everything
		 * अन्यथा is पढ़ोy.
		 */
		REG_WRITE(ah, AR_KEYTABLE_KEY0(entry), ~key0);
		REG_WRITE(ah, AR_KEYTABLE_KEY1(entry), ~key1);

		/* Write key[95:48] */
		REG_WRITE(ah, AR_KEYTABLE_KEY2(entry), key2);
		REG_WRITE(ah, AR_KEYTABLE_KEY3(entry), key3);

		/* Write key[127:96] and key type */
		REG_WRITE(ah, AR_KEYTABLE_KEY4(entry), key4);
		REG_WRITE(ah, AR_KEYTABLE_TYPE(entry), keyType);

		/* Write MAC address क्रम the entry */
		(व्योम) ath_hw_keyseपंचांगac(common, entry, mac);

		अगर (common->crypt_caps & ATH_CRYPT_CAP_MIC_COMBINED) अणु
			/*
			 * TKIP uses two key cache entries:
			 * Michael MIC TX/RX keys in the same key cache entry
			 * (idx = मुख्य index + 64):
			 * key0 [31:0] = RX key [31:0]
			 * key1 [15:0] = TX key [31:16]
			 * key1 [31:16] = reserved
			 * key2 [31:0] = RX key [63:32]
			 * key3 [15:0] = TX key [15:0]
			 * key3 [31:16] = reserved
			 * key4 [31:0] = TX key [63:32]
			 */
			u32 mic0, mic1, mic2, mic3, mic4;

			mic0 = get_unaligned_le32(k->kv_mic + 0);
			mic2 = get_unaligned_le32(k->kv_mic + 4);
			mic1 = get_unaligned_le16(k->kv_txmic + 2) & 0xffff;
			mic3 = get_unaligned_le16(k->kv_txmic + 0) & 0xffff;
			mic4 = get_unaligned_le32(k->kv_txmic + 4);

			ENABLE_REGWRITE_BUFFER(ah);

			/* Write RX[31:0] and TX[31:16] */
			REG_WRITE(ah, AR_KEYTABLE_KEY0(micentry), mic0);
			REG_WRITE(ah, AR_KEYTABLE_KEY1(micentry), mic1);

			/* Write RX[63:32] and TX[15:0] */
			REG_WRITE(ah, AR_KEYTABLE_KEY2(micentry), mic2);
			REG_WRITE(ah, AR_KEYTABLE_KEY3(micentry), mic3);

			/* Write TX[63:32] and keyType(reserved) */
			REG_WRITE(ah, AR_KEYTABLE_KEY4(micentry), mic4);
			REG_WRITE(ah, AR_KEYTABLE_TYPE(micentry),
				  AR_KEYTABLE_TYPE_CLR);

			REGWRITE_BUFFER_FLUSH(ah);

		पूर्ण अन्यथा अणु
			/*
			 * TKIP uses four key cache entries (two क्रम group
			 * keys):
			 * Michael MIC TX/RX keys are in dअगरferent key cache
			 * entries (idx = मुख्य index + 64 क्रम TX and
			 * मुख्य index + 32 + 96 क्रम RX):
			 * key0 [31:0] = TX/RX MIC key [31:0]
			 * key1 [31:0] = reserved
			 * key2 [31:0] = TX/RX MIC key [63:32]
			 * key3 [31:0] = reserved
			 * key4 [31:0] = reserved
			 *
			 * Upper layer code will call this function separately
			 * क्रम TX and RX keys when these रेजिस्टरs offsets are
			 * used.
			 */
			u32 mic0, mic2;

			mic0 = get_unaligned_le32(k->kv_mic + 0);
			mic2 = get_unaligned_le32(k->kv_mic + 4);

			ENABLE_REGWRITE_BUFFER(ah);

			/* Write MIC key[31:0] */
			REG_WRITE(ah, AR_KEYTABLE_KEY0(micentry), mic0);
			REG_WRITE(ah, AR_KEYTABLE_KEY1(micentry), 0);

			/* Write MIC key[63:32] */
			REG_WRITE(ah, AR_KEYTABLE_KEY2(micentry), mic2);
			REG_WRITE(ah, AR_KEYTABLE_KEY3(micentry), 0);

			/* Write TX[63:32] and keyType(reserved) */
			REG_WRITE(ah, AR_KEYTABLE_KEY4(micentry), 0);
			REG_WRITE(ah, AR_KEYTABLE_TYPE(micentry),
				  AR_KEYTABLE_TYPE_CLR);

			REGWRITE_BUFFER_FLUSH(ah);
		पूर्ण

		ENABLE_REGWRITE_BUFFER(ah);

		/* MAC address रेजिस्टरs are reserved क्रम the MIC entry */
		REG_WRITE(ah, AR_KEYTABLE_MAC0(micentry), 0);
		REG_WRITE(ah, AR_KEYTABLE_MAC1(micentry), 0);

		/*
		 * Write the correct (un-inverted) key[47:0] last to enable
		 * TKIP now that all other रेजिस्टरs are set with correct
		 * values.
		 */
		REG_WRITE(ah, AR_KEYTABLE_KEY0(entry), key0);
		REG_WRITE(ah, AR_KEYTABLE_KEY1(entry), key1);

		REGWRITE_BUFFER_FLUSH(ah);
	पूर्ण अन्यथा अणु
		ENABLE_REGWRITE_BUFFER(ah);

		/* Write key[47:0] */
		REG_WRITE(ah, AR_KEYTABLE_KEY0(entry), key0);
		REG_WRITE(ah, AR_KEYTABLE_KEY1(entry), key1);

		/* Write key[95:48] */
		REG_WRITE(ah, AR_KEYTABLE_KEY2(entry), key2);
		REG_WRITE(ah, AR_KEYTABLE_KEY3(entry), key3);

		/* Write key[127:96] and key type */
		REG_WRITE(ah, AR_KEYTABLE_KEY4(entry), key4);
		REG_WRITE(ah, AR_KEYTABLE_TYPE(entry), keyType);

		REGWRITE_BUFFER_FLUSH(ah);

		/* Write MAC address क्रम the entry */
		(व्योम) ath_hw_keyseपंचांगac(common, entry, mac);
	पूर्ण

	वापस true;
पूर्ण

अटल पूर्णांक ath_setkey_tkip(काष्ठा ath_common *common, u16 keyix, स्थिर u8 *key,
			   काष्ठा ath_keyval *hk, स्थिर u8 *addr,
			   bool authenticator)
अणु
	स्थिर u8 *key_rxmic;
	स्थिर u8 *key_txmic;

	key_txmic = key + NL80211_TKIP_DATA_OFFSET_TX_MIC_KEY;
	key_rxmic = key + NL80211_TKIP_DATA_OFFSET_RX_MIC_KEY;

	अगर (addr == शून्य) अणु
		/*
		 * Group key installation - only two key cache entries are used
		 * regardless of spliपंचांगic capability since group key is only
		 * used either क्रम TX or RX.
		 */
		अगर (authenticator) अणु
			स_नकल(hk->kv_mic, key_txmic, माप(hk->kv_mic));
			स_नकल(hk->kv_txmic, key_txmic, माप(hk->kv_mic));
		पूर्ण अन्यथा अणु
			स_नकल(hk->kv_mic, key_rxmic, माप(hk->kv_mic));
			स_नकल(hk->kv_txmic, key_rxmic, माप(hk->kv_mic));
		पूर्ण
		वापस ath_hw_set_keycache_entry(common, keyix, hk, addr);
	पूर्ण
	अगर (common->crypt_caps & ATH_CRYPT_CAP_MIC_COMBINED) अणु
		/* TX and RX keys share the same key cache entry. */
		स_नकल(hk->kv_mic, key_rxmic, माप(hk->kv_mic));
		स_नकल(hk->kv_txmic, key_txmic, माप(hk->kv_txmic));
		वापस ath_hw_set_keycache_entry(common, keyix, hk, addr);
	पूर्ण

	/* Separate key cache entries क्रम TX and RX */

	/* TX key goes at first index, RX key at +32. */
	स_नकल(hk->kv_mic, key_txmic, माप(hk->kv_mic));
	अगर (!ath_hw_set_keycache_entry(common, keyix, hk, शून्य)) अणु
		/* TX MIC entry failed. No need to proceed further */
		ath_err(common, "Setting TX MIC Key Failed\n");
		वापस 0;
	पूर्ण

	स_नकल(hk->kv_mic, key_rxmic, माप(hk->kv_mic));
	/* XXX delete tx key on failure? */
	वापस ath_hw_set_keycache_entry(common, keyix + 32, hk, addr);
पूर्ण

अटल पूर्णांक ath_reserve_key_cache_slot_tkip(काष्ठा ath_common *common)
अणु
	पूर्णांक i;

	क्रम (i = IEEE80211_WEP_NKID; i < common->keymax / 2; i++) अणु
		अगर (test_bit(i, common->keymap) ||
		    test_bit(i + 64, common->keymap))
			जारी; /* At least one part of TKIP key allocated */
		अगर (!(common->crypt_caps & ATH_CRYPT_CAP_MIC_COMBINED) &&
		    (test_bit(i + 32, common->keymap) ||
		     test_bit(i + 64 + 32, common->keymap)))
			जारी; /* At least one part of TKIP key allocated */

		/* Found a मुक्त slot क्रम a TKIP key */
		वापस i;
	पूर्ण
	वापस -1;
पूर्ण

अटल पूर्णांक ath_reserve_key_cache_slot(काष्ठा ath_common *common,
				      u32 cipher)
अणु
	पूर्णांक i;

	अगर (cipher == WLAN_CIPHER_SUITE_TKIP)
		वापस ath_reserve_key_cache_slot_tkip(common);

	/* First, try to find slots that would not be available क्रम TKIP. */
	अगर (!(common->crypt_caps & ATH_CRYPT_CAP_MIC_COMBINED)) अणु
		क्रम (i = IEEE80211_WEP_NKID; i < common->keymax / 4; i++) अणु
			अगर (!test_bit(i, common->keymap) &&
			    (test_bit(i + 32, common->keymap) ||
			     test_bit(i + 64, common->keymap) ||
			     test_bit(i + 64 + 32, common->keymap)))
				वापस i;
			अगर (!test_bit(i + 32, common->keymap) &&
			    (test_bit(i, common->keymap) ||
			     test_bit(i + 64, common->keymap) ||
			     test_bit(i + 64 + 32, common->keymap)))
				वापस i + 32;
			अगर (!test_bit(i + 64, common->keymap) &&
			    (test_bit(i , common->keymap) ||
			     test_bit(i + 32, common->keymap) ||
			     test_bit(i + 64 + 32, common->keymap)))
				वापस i + 64;
			अगर (!test_bit(i + 64 + 32, common->keymap) &&
			    (test_bit(i, common->keymap) ||
			     test_bit(i + 32, common->keymap) ||
			     test_bit(i + 64, common->keymap)))
				वापस i + 64 + 32;
		पूर्ण
	पूर्ण अन्यथा अणु
		क्रम (i = IEEE80211_WEP_NKID; i < common->keymax / 2; i++) अणु
			अगर (!test_bit(i, common->keymap) &&
			    test_bit(i + 64, common->keymap))
				वापस i;
			अगर (test_bit(i, common->keymap) &&
			    !test_bit(i + 64, common->keymap))
				वापस i + 64;
		पूर्ण
	पूर्ण

	/* No partially used TKIP slots, pick any available slot */
	क्रम (i = IEEE80211_WEP_NKID; i < common->keymax; i++) अणु
		/* Do not allow slots that could be needed क्रम TKIP group keys
		 * to be used. This limitation could be हटाओd अगर we know that
		 * TKIP will not be used. */
		अगर (i >= 64 && i < 64 + IEEE80211_WEP_NKID)
			जारी;
		अगर (!(common->crypt_caps & ATH_CRYPT_CAP_MIC_COMBINED)) अणु
			अगर (i >= 32 && i < 32 + IEEE80211_WEP_NKID)
				जारी;
			अगर (i >= 64 + 32 && i < 64 + 32 + IEEE80211_WEP_NKID)
				जारी;
		पूर्ण

		अगर (!test_bit(i, common->keymap))
			वापस i; /* Found a मुक्त slot क्रम a key */
	पूर्ण

	/* No मुक्त slot found */
	वापस -1;
पूर्ण

/*
 * Configure encryption in the HW.
 */
पूर्णांक ath_key_config(काष्ठा ath_common *common,
			  काष्ठा ieee80211_vअगर *vअगर,
			  काष्ठा ieee80211_sta *sta,
			  काष्ठा ieee80211_key_conf *key)
अणु
	काष्ठा ath_keyval hk;
	स्थिर u8 *mac = शून्य;
	u8 gmac[ETH_ALEN];
	पूर्णांक ret = 0;
	पूर्णांक idx;

	स_रखो(&hk, 0, माप(hk));

	चयन (key->cipher) अणु
	हाल 0:
		hk.kv_type = ATH_CIPHER_CLR;
		अवरोध;
	हाल WLAN_CIPHER_SUITE_WEP40:
	हाल WLAN_CIPHER_SUITE_WEP104:
		hk.kv_type = ATH_CIPHER_WEP;
		अवरोध;
	हाल WLAN_CIPHER_SUITE_TKIP:
		hk.kv_type = ATH_CIPHER_TKIP;
		अवरोध;
	हाल WLAN_CIPHER_SUITE_CCMP:
		hk.kv_type = ATH_CIPHER_AES_CCM;
		अवरोध;
	शेष:
		वापस -EOPNOTSUPP;
	पूर्ण

	hk.kv_len = key->keylen;
	अगर (key->keylen)
		स_नकल(hk.kv_val, key->key, key->keylen);

	अगर (!(key->flags & IEEE80211_KEY_FLAG_PAIRWISE)) अणु
		चयन (vअगर->type) अणु
		हाल NL80211_IFTYPE_AP:
			स_नकल(gmac, vअगर->addr, ETH_ALEN);
			gmac[0] |= 0x01;
			mac = gmac;
			idx = ath_reserve_key_cache_slot(common, key->cipher);
			अवरोध;
		हाल NL80211_IFTYPE_ADHOC:
			अगर (!sta) अणु
				idx = key->keyidx;
				अवरोध;
			पूर्ण
			स_नकल(gmac, sta->addr, ETH_ALEN);
			gmac[0] |= 0x01;
			mac = gmac;
			idx = ath_reserve_key_cache_slot(common, key->cipher);
			अवरोध;
		शेष:
			idx = key->keyidx;
			अवरोध;
		पूर्ण
	पूर्ण अन्यथा अगर (key->keyidx) अणु
		अगर (WARN_ON(!sta))
			वापस -EOPNOTSUPP;
		mac = sta->addr;

		अगर (vअगर->type != NL80211_IFTYPE_AP) अणु
			/* Only keyidx 0 should be used with unicast key, but
			 * allow this क्रम client mode क्रम now. */
			idx = key->keyidx;
		पूर्ण अन्यथा
			वापस -EIO;
	पूर्ण अन्यथा अणु
		अगर (WARN_ON(!sta))
			वापस -EOPNOTSUPP;
		mac = sta->addr;

		idx = ath_reserve_key_cache_slot(common, key->cipher);
	पूर्ण

	अगर (idx < 0)
		वापस -ENOSPC; /* no मुक्त key cache entries */

	अगर (key->cipher == WLAN_CIPHER_SUITE_TKIP)
		ret = ath_setkey_tkip(common, idx, key->key, &hk, mac,
				      vअगर->type == NL80211_IFTYPE_AP);
	अन्यथा
		ret = ath_hw_set_keycache_entry(common, idx, &hk, mac);

	अगर (!ret)
		वापस -EIO;

	set_bit(idx, common->keymap);
	अगर (key->cipher == WLAN_CIPHER_SUITE_CCMP)
		set_bit(idx, common->ccmp_keymap);

	अगर (key->cipher == WLAN_CIPHER_SUITE_TKIP) अणु
		set_bit(idx + 64, common->keymap);
		set_bit(idx, common->tkip_keymap);
		set_bit(idx + 64, common->tkip_keymap);
		अगर (!(common->crypt_caps & ATH_CRYPT_CAP_MIC_COMBINED)) अणु
			set_bit(idx + 32, common->keymap);
			set_bit(idx + 64 + 32, common->keymap);
			set_bit(idx + 32, common->tkip_keymap);
			set_bit(idx + 64 + 32, common->tkip_keymap);
		पूर्ण
	पूर्ण

	वापस idx;
पूर्ण
EXPORT_SYMBOL(ath_key_config);

/*
 * Delete Key.
 */
व्योम ath_key_delete(काष्ठा ath_common *common, u8 hw_key_idx)
अणु
	/* Leave CCMP and TKIP (मुख्य key) configured to aव्योम disabling
	 * encryption क्रम potentially pending frames alपढ़ोy in a TXQ with the
	 * keyix poपूर्णांकing to this key entry. Instead, only clear the MAC address
	 * to prevent RX processing from using this key cache entry.
	 */
	अगर (test_bit(hw_key_idx, common->ccmp_keymap) ||
	    test_bit(hw_key_idx, common->tkip_keymap))
		ath_hw_keyseपंचांगac(common, hw_key_idx, शून्य);
	अन्यथा
		ath_hw_keyreset(common, hw_key_idx);
	अगर (hw_key_idx < IEEE80211_WEP_NKID)
		वापस;

	clear_bit(hw_key_idx, common->keymap);
	clear_bit(hw_key_idx, common->ccmp_keymap);
	अगर (!test_bit(hw_key_idx, common->tkip_keymap))
		वापस;

	clear_bit(hw_key_idx + 64, common->keymap);

	clear_bit(hw_key_idx, common->tkip_keymap);
	clear_bit(hw_key_idx + 64, common->tkip_keymap);

	अगर (!(common->crypt_caps & ATH_CRYPT_CAP_MIC_COMBINED)) अणु
		ath_hw_keyreset(common, hw_key_idx + 32);
		clear_bit(hw_key_idx + 32, common->keymap);
		clear_bit(hw_key_idx + 64 + 32, common->keymap);

		clear_bit(hw_key_idx + 32, common->tkip_keymap);
		clear_bit(hw_key_idx + 64 + 32, common->tkip_keymap);
	पूर्ण
पूर्ण
EXPORT_SYMBOL(ath_key_delete);
