<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Copyright 2002-2004, Instant802 Networks, Inc.
 * Copyright 2005, Devicescape Software, Inc.
 * Copyright (C) 2019 Intel Corporation
 */

#अगर_अघोषित IEEE80211_KEY_H
#घोषणा IEEE80211_KEY_H

#समावेश <linux/types.h>
#समावेश <linux/list.h>
#समावेश <linux/crypto.h>
#समावेश <linux/rcupdate.h>
#समावेश <crypto/arc4.h>
#समावेश <net/mac80211.h>

#घोषणा NUM_DEFAULT_KEYS 4
#घोषणा NUM_DEFAULT_MGMT_KEYS 2
#घोषणा NUM_DEFAULT_BEACON_KEYS 2
#घोषणा INVALID_PTK_KEYIDX 2 /* Keyidx always poपूर्णांकing to a शून्य key क्रम PTK */

काष्ठा ieee80211_local;
काष्ठा ieee80211_sub_अगर_data;
काष्ठा sta_info;

/**
 * क्रमागत ieee80211_पूर्णांकernal_key_flags - पूर्णांकernal key flags
 *
 * @KEY_FLAG_UPLOADED_TO_HARDWARE: Indicates that this key is present
 *	in the hardware क्रम TX crypto hardware acceleration.
 * @KEY_FLAG_TAINTED: Key is taपूर्णांकed and packets should be dropped.
 * @KEY_FLAG_CIPHER_SCHEME: This key is क्रम a hardware cipher scheme
 */
क्रमागत ieee80211_पूर्णांकernal_key_flags अणु
	KEY_FLAG_UPLOADED_TO_HARDWARE	= BIT(0),
	KEY_FLAG_TAINTED		= BIT(1),
	KEY_FLAG_CIPHER_SCHEME		= BIT(2),
पूर्ण;

क्रमागत ieee80211_पूर्णांकernal_tkip_state अणु
	TKIP_STATE_NOT_INIT,
	TKIP_STATE_PHASE1_DONE,
	TKIP_STATE_PHASE1_HW_UPLOADED,
पूर्ण;

काष्ठा tkip_ctx अणु
	u16 p1k[5];	/* p1k cache */
	u32 p1k_iv32;	/* iv32 क्रम which p1k computed */
	क्रमागत ieee80211_पूर्णांकernal_tkip_state state;
पूर्ण;

काष्ठा tkip_ctx_rx अणु
	काष्ठा tkip_ctx ctx;
	u32 iv32;	/* current iv32 */
	u16 iv16;	/* current iv16 */
पूर्ण;

काष्ठा ieee80211_key अणु
	काष्ठा ieee80211_local *local;
	काष्ठा ieee80211_sub_अगर_data *sdata;
	काष्ठा sta_info *sta;

	/* क्रम sdata list */
	काष्ठा list_head list;

	/* रक्षित by key mutex */
	अचिन्हित पूर्णांक flags;

	जोड़ अणु
		काष्ठा अणु
			/* protects tx context */
			spinlock_t txlock;

			/* last used TSC */
			काष्ठा tkip_ctx tx;

			/* last received RSC */
			काष्ठा tkip_ctx_rx rx[IEEE80211_NUM_TIDS];

			/* number of mic failures */
			u32 mic_failures;
		पूर्ण tkip;
		काष्ठा अणु
			/*
			 * Last received packet number. The first
			 * IEEE80211_NUM_TIDS counters are used with Data
			 * frames and the last counter is used with Robust
			 * Management frames.
			 */
			u8 rx_pn[IEEE80211_NUM_TIDS + 1][IEEE80211_CCMP_PN_LEN];
			काष्ठा crypto_aead *tfm;
			u32 replays; /* करोt11RSNAStatsCCMPReplays */
		पूर्ण ccmp;
		काष्ठा अणु
			u8 rx_pn[IEEE80211_CMAC_PN_LEN];
			काष्ठा crypto_shash *tfm;
			u32 replays; /* करोt11RSNAStatsCMACReplays */
			u32 icverrors; /* करोt11RSNAStatsCMACICVErrors */
		पूर्ण aes_cmac;
		काष्ठा अणु
			u8 rx_pn[IEEE80211_GMAC_PN_LEN];
			काष्ठा crypto_aead *tfm;
			u32 replays; /* करोt11RSNAStatsCMACReplays */
			u32 icverrors; /* करोt11RSNAStatsCMACICVErrors */
		पूर्ण aes_gmac;
		काष्ठा अणु
			/* Last received packet number. The first
			 * IEEE80211_NUM_TIDS counters are used with Data
			 * frames and the last counter is used with Robust
			 * Management frames.
			 */
			u8 rx_pn[IEEE80211_NUM_TIDS + 1][IEEE80211_GCMP_PN_LEN];
			काष्ठा crypto_aead *tfm;
			u32 replays; /* करोt11RSNAStatsGCMPReplays */
		पूर्ण gcmp;
		काष्ठा अणु
			/* generic cipher scheme */
			u8 rx_pn[IEEE80211_NUM_TIDS + 1][IEEE80211_MAX_PN_LEN];
		पूर्ण gen;
	पूर्ण u;

#अगर_घोषित CONFIG_MAC80211_DEBUGFS
	काष्ठा अणु
		काष्ठा dentry *stalink;
		काष्ठा dentry *dir;
		पूर्णांक cnt;
	पूर्ण debugfs;
#पूर्ण_अगर

	अचिन्हित पूर्णांक color;

	/*
	 * key config, must be last because it contains key
	 * material as variable length member
	 */
	काष्ठा ieee80211_key_conf conf;
पूर्ण;

काष्ठा ieee80211_key *
ieee80211_key_alloc(u32 cipher, पूर्णांक idx, माप_प्रकार key_len,
		    स्थिर u8 *key_data,
		    माप_प्रकार seq_len, स्थिर u8 *seq,
		    स्थिर काष्ठा ieee80211_cipher_scheme *cs);
/*
 * Insert a key पूर्णांकo data काष्ठाures (sdata, sta अगर necessary)
 * to make it used, मुक्त old key. On failure, also मुक्त the new key.
 */
पूर्णांक ieee80211_key_link(काष्ठा ieee80211_key *key,
		       काष्ठा ieee80211_sub_अगर_data *sdata,
		       काष्ठा sta_info *sta);
पूर्णांक ieee80211_set_tx_key(काष्ठा ieee80211_key *key);
व्योम ieee80211_key_मुक्त(काष्ठा ieee80211_key *key, bool delay_tailroom);
व्योम ieee80211_key_मुक्त_unused(काष्ठा ieee80211_key *key);
व्योम ieee80211_set_शेष_key(काष्ठा ieee80211_sub_अगर_data *sdata, पूर्णांक idx,
			       bool uni, bool multi);
व्योम ieee80211_set_शेष_mgmt_key(काष्ठा ieee80211_sub_अगर_data *sdata,
				    पूर्णांक idx);
व्योम ieee80211_set_शेष_beacon_key(काष्ठा ieee80211_sub_अगर_data *sdata,
				      पूर्णांक idx);
व्योम ieee80211_मुक्त_keys(काष्ठा ieee80211_sub_अगर_data *sdata,
			 bool क्रमce_synchronize);
व्योम ieee80211_मुक्त_sta_keys(काष्ठा ieee80211_local *local,
			     काष्ठा sta_info *sta);
व्योम ieee80211_reenable_keys(काष्ठा ieee80211_sub_अगर_data *sdata);

#घोषणा key_mtx_dereference(local, ref) \
	rcu_dereference_रक्षित(ref, lockdep_is_held(&((local)->key_mtx)))

व्योम ieee80211_delayed_tailroom_dec(काष्ठा work_काष्ठा *wk);

#पूर्ण_अगर /* IEEE80211_KEY_H */
