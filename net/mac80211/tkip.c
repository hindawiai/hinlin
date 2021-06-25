<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright 2002-2004, Instant802 Networks, Inc.
 * Copyright 2005, Devicescape Software, Inc.
 * Copyright (C) 2016 Intel Deutschland GmbH
 */
#समावेश <linux/kernel.h>
#समावेश <linux/bitops.h>
#समावेश <linux/types.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/export.h>
#समावेश <यंत्र/unaligned.h>

#समावेश <net/mac80211.h>
#समावेश "driver-ops.h"
#समावेश "key.h"
#समावेश "tkip.h"
#समावेश "wep.h"

#घोषणा PHASE1_LOOP_COUNT 8

/*
 * 2-byte by 2-byte subset of the full AES S-box table; second part of this
 * table is identical to first part but byte-swapped
 */
अटल स्थिर u16 tkip_sbox[256] =
अणु
	0xC6A5, 0xF884, 0xEE99, 0xF68D, 0xFF0D, 0xD6BD, 0xDEB1, 0x9154,
	0x6050, 0x0203, 0xCEA9, 0x567D, 0xE719, 0xB562, 0x4DE6, 0xEC9A,
	0x8F45, 0x1F9D, 0x8940, 0xFA87, 0xEF15, 0xB2EB, 0x8EC9, 0xFB0B,
	0x41EC, 0xB367, 0x5FFD, 0x45EA, 0x23BF, 0x53F7, 0xE496, 0x9B5B,
	0x75C2, 0xE11C, 0x3DAE, 0x4C6A, 0x6C5A, 0x7E41, 0xF502, 0x834F,
	0x685C, 0x51F4, 0xD134, 0xF908, 0xE293, 0xAB73, 0x6253, 0x2A3F,
	0x080C, 0x9552, 0x4665, 0x9D5E, 0x3028, 0x37A1, 0x0A0F, 0x2FB5,
	0x0E09, 0x2436, 0x1B9B, 0xDF3D, 0xCD26, 0x4E69, 0x7FCD, 0xEA9F,
	0x121B, 0x1D9E, 0x5874, 0x342E, 0x362D, 0xDCB2, 0xB4EE, 0x5BFB,
	0xA4F6, 0x764D, 0xB761, 0x7DCE, 0x527B, 0xDD3E, 0x5E71, 0x1397,
	0xA6F5, 0xB968, 0x0000, 0xC12C, 0x4060, 0xE31F, 0x79C8, 0xB6ED,
	0xD4BE, 0x8D46, 0x67D9, 0x724B, 0x94DE, 0x98D4, 0xB0E8, 0x854A,
	0xBB6B, 0xC52A, 0x4FE5, 0xED16, 0x86C5, 0x9AD7, 0x6655, 0x1194,
	0x8ACF, 0xE910, 0x0406, 0xFE81, 0xA0F0, 0x7844, 0x25BA, 0x4BE3,
	0xA2F3, 0x5DFE, 0x80C0, 0x058A, 0x3FAD, 0x21BC, 0x7048, 0xF104,
	0x63DF, 0x77C1, 0xAF75, 0x4263, 0x2030, 0xE51A, 0xFD0E, 0xBF6D,
	0x814C, 0x1814, 0x2635, 0xC32F, 0xBEE1, 0x35A2, 0x88CC, 0x2E39,
	0x9357, 0x55F2, 0xFC82, 0x7A47, 0xC8AC, 0xBAE7, 0x322B, 0xE695,
	0xC0A0, 0x1998, 0x9ED1, 0xA37F, 0x4466, 0x547E, 0x3BAB, 0x0B83,
	0x8CCA, 0xC729, 0x6BD3, 0x283C, 0xA779, 0xBCE2, 0x161D, 0xAD76,
	0xDB3B, 0x6456, 0x744E, 0x141E, 0x92DB, 0x0C0A, 0x486C, 0xB8E4,
	0x9F5D, 0xBD6E, 0x43EF, 0xC4A6, 0x39A8, 0x31A4, 0xD337, 0xF28B,
	0xD532, 0x8B43, 0x6E59, 0xDAB7, 0x018C, 0xB164, 0x9CD2, 0x49E0,
	0xD8B4, 0xACFA, 0xF307, 0xCF25, 0xCAAF, 0xF48E, 0x47E9, 0x1018,
	0x6FD5, 0xF088, 0x4A6F, 0x5C72, 0x3824, 0x57F1, 0x73C7, 0x9751,
	0xCB23, 0xA17C, 0xE89C, 0x3E21, 0x96DD, 0x61DC, 0x0D86, 0x0F85,
	0xE090, 0x7C42, 0x71C4, 0xCCAA, 0x90D8, 0x0605, 0xF701, 0x1C12,
	0xC2A3, 0x6A5F, 0xAEF9, 0x69D0, 0x1791, 0x9958, 0x3A27, 0x27B9,
	0xD938, 0xEB13, 0x2BB3, 0x2233, 0xD2BB, 0xA970, 0x0789, 0x33A7,
	0x2DB6, 0x3C22, 0x1592, 0xC920, 0x8749, 0xAAFF, 0x5078, 0xA57A,
	0x038F, 0x59F8, 0x0980, 0x1A17, 0x65DA, 0xD731, 0x84C6, 0xD0B8,
	0x82C3, 0x29B0, 0x5A77, 0x1E11, 0x7BCB, 0xA8FC, 0x6DD6, 0x2C3A,
पूर्ण;

अटल u16 tkipS(u16 val)
अणु
	वापस tkip_sbox[val & 0xff] ^ swab16(tkip_sbox[val >> 8]);
पूर्ण

अटल u8 *ग_लिखो_tkip_iv(u8 *pos, u16 iv16)
अणु
	*pos++ = iv16 >> 8;
	*pos++ = ((iv16 >> 8) | 0x20) & 0x7f;
	*pos++ = iv16 & 0xFF;
	वापस pos;
पूर्ण

/*
 * P1K := Phase1(TA, TK, TSC)
 * TA = transmitter address (48 bits)
 * TK = करोt11DefaultKeyValue or करोt11KeyMappingValue (128 bits)
 * TSC = TKIP sequence counter (48 bits, only 32 msb bits used)
 * P1K: 80 bits
 */
अटल व्योम tkip_mixing_phase1(स्थिर u8 *tk, काष्ठा tkip_ctx *ctx,
			       स्थिर u8 *ta, u32 tsc_IV32)
अणु
	पूर्णांक i, j;
	u16 *p1k = ctx->p1k;

	p1k[0] = tsc_IV32 & 0xFFFF;
	p1k[1] = tsc_IV32 >> 16;
	p1k[2] = get_unaligned_le16(ta + 0);
	p1k[3] = get_unaligned_le16(ta + 2);
	p1k[4] = get_unaligned_le16(ta + 4);

	क्रम (i = 0; i < PHASE1_LOOP_COUNT; i++) अणु
		j = 2 * (i & 1);
		p1k[0] += tkipS(p1k[4] ^ get_unaligned_le16(tk + 0 + j));
		p1k[1] += tkipS(p1k[0] ^ get_unaligned_le16(tk + 4 + j));
		p1k[2] += tkipS(p1k[1] ^ get_unaligned_le16(tk + 8 + j));
		p1k[3] += tkipS(p1k[2] ^ get_unaligned_le16(tk + 12 + j));
		p1k[4] += tkipS(p1k[3] ^ get_unaligned_le16(tk + 0 + j)) + i;
	पूर्ण
	ctx->state = TKIP_STATE_PHASE1_DONE;
	ctx->p1k_iv32 = tsc_IV32;
पूर्ण

अटल व्योम tkip_mixing_phase2(स्थिर u8 *tk, काष्ठा tkip_ctx *ctx,
			       u16 tsc_IV16, u8 *rc4key)
अणु
	u16 ppk[6];
	स्थिर u16 *p1k = ctx->p1k;
	पूर्णांक i;

	ppk[0] = p1k[0];
	ppk[1] = p1k[1];
	ppk[2] = p1k[2];
	ppk[3] = p1k[3];
	ppk[4] = p1k[4];
	ppk[5] = p1k[4] + tsc_IV16;

	ppk[0] += tkipS(ppk[5] ^ get_unaligned_le16(tk + 0));
	ppk[1] += tkipS(ppk[0] ^ get_unaligned_le16(tk + 2));
	ppk[2] += tkipS(ppk[1] ^ get_unaligned_le16(tk + 4));
	ppk[3] += tkipS(ppk[2] ^ get_unaligned_le16(tk + 6));
	ppk[4] += tkipS(ppk[3] ^ get_unaligned_le16(tk + 8));
	ppk[5] += tkipS(ppk[4] ^ get_unaligned_le16(tk + 10));
	ppk[0] += ror16(ppk[5] ^ get_unaligned_le16(tk + 12), 1);
	ppk[1] += ror16(ppk[0] ^ get_unaligned_le16(tk + 14), 1);
	ppk[2] += ror16(ppk[1], 1);
	ppk[3] += ror16(ppk[2], 1);
	ppk[4] += ror16(ppk[3], 1);
	ppk[5] += ror16(ppk[4], 1);

	rc4key = ग_लिखो_tkip_iv(rc4key, tsc_IV16);
	*rc4key++ = ((ppk[5] ^ get_unaligned_le16(tk)) >> 1) & 0xFF;

	क्रम (i = 0; i < 6; i++)
		put_unaligned_le16(ppk[i], rc4key + 2 * i);
पूर्ण

/* Add TKIP IV and Ext. IV at @pos. @iv0, @iv1, and @iv2 are the first octets
 * of the IV. Returns poपूर्णांकer to the octet following IVs (i.e., beginning of
 * the packet payload). */
u8 *ieee80211_tkip_add_iv(u8 *pos, काष्ठा ieee80211_key_conf *keyconf, u64 pn)
अणु
	pos = ग_लिखो_tkip_iv(pos, TKIP_PN_TO_IV16(pn));
	*pos++ = (keyconf->keyidx << 6) | (1 << 5) /* Ext IV */;
	put_unaligned_le32(TKIP_PN_TO_IV32(pn), pos);
	वापस pos + 4;
पूर्ण
EXPORT_SYMBOL_GPL(ieee80211_tkip_add_iv);

अटल व्योम ieee80211_compute_tkip_p1k(काष्ठा ieee80211_key *key, u32 iv32)
अणु
	काष्ठा ieee80211_sub_अगर_data *sdata = key->sdata;
	काष्ठा tkip_ctx *ctx = &key->u.tkip.tx;
	स्थिर u8 *tk = &key->conf.key[NL80211_TKIP_DATA_OFFSET_ENCR_KEY];

	lockdep_निश्चित_held(&key->u.tkip.txlock);

	/*
	 * Update the P1K when the IV32 is dअगरferent from the value it
	 * had when we last computed it (or when not initialised yet).
	 * This might flip-flop back and क्रमth अगर packets are processed
	 * out-of-order due to the dअगरferent ACs, but then we have to
	 * just compute the P1K more often.
	 */
	अगर (ctx->p1k_iv32 != iv32 || ctx->state == TKIP_STATE_NOT_INIT)
		tkip_mixing_phase1(tk, ctx, sdata->vअगर.addr, iv32);
पूर्ण

व्योम ieee80211_get_tkip_p1k_iv(काष्ठा ieee80211_key_conf *keyconf,
			       u32 iv32, u16 *p1k)
अणु
	काष्ठा ieee80211_key *key = (काष्ठा ieee80211_key *)
			container_of(keyconf, काष्ठा ieee80211_key, conf);
	काष्ठा tkip_ctx *ctx = &key->u.tkip.tx;

	spin_lock_bh(&key->u.tkip.txlock);
	ieee80211_compute_tkip_p1k(key, iv32);
	स_नकल(p1k, ctx->p1k, माप(ctx->p1k));
	spin_unlock_bh(&key->u.tkip.txlock);
पूर्ण
EXPORT_SYMBOL(ieee80211_get_tkip_p1k_iv);

व्योम ieee80211_get_tkip_rx_p1k(काष्ठा ieee80211_key_conf *keyconf,
			       स्थिर u8 *ta, u32 iv32, u16 *p1k)
अणु
	स्थिर u8 *tk = &keyconf->key[NL80211_TKIP_DATA_OFFSET_ENCR_KEY];
	काष्ठा tkip_ctx ctx;

	tkip_mixing_phase1(tk, &ctx, ta, iv32);
	स_नकल(p1k, ctx.p1k, माप(ctx.p1k));
पूर्ण
EXPORT_SYMBOL(ieee80211_get_tkip_rx_p1k);

व्योम ieee80211_get_tkip_p2k(काष्ठा ieee80211_key_conf *keyconf,
			    काष्ठा sk_buff *skb, u8 *p2k)
अणु
	काष्ठा ieee80211_key *key = (काष्ठा ieee80211_key *)
			container_of(keyconf, काष्ठा ieee80211_key, conf);
	स्थिर u8 *tk = &key->conf.key[NL80211_TKIP_DATA_OFFSET_ENCR_KEY];
	काष्ठा tkip_ctx *ctx = &key->u.tkip.tx;
	काष्ठा ieee80211_hdr *hdr = (काष्ठा ieee80211_hdr *)skb->data;
	स्थिर u8 *data = (u8 *)hdr + ieee80211_hdrlen(hdr->frame_control);
	u32 iv32 = get_unaligned_le32(&data[4]);
	u16 iv16 = data[2] | (data[0] << 8);

	spin_lock(&key->u.tkip.txlock);
	ieee80211_compute_tkip_p1k(key, iv32);
	tkip_mixing_phase2(tk, ctx, iv16, p2k);
	spin_unlock(&key->u.tkip.txlock);
पूर्ण
EXPORT_SYMBOL(ieee80211_get_tkip_p2k);

/*
 * Encrypt packet payload with TKIP using @key. @pos is a poपूर्णांकer to the
 * beginning of the buffer containing payload. This payload must include
 * the IV/Ext.IV and space क्रम (taildroom) four octets क्रम ICV.
 * @payload_len is the length of payload (_not_ including IV/ICV length).
 * @ta is the transmitter addresses.
 */
पूर्णांक ieee80211_tkip_encrypt_data(काष्ठा arc4_ctx *ctx,
				काष्ठा ieee80211_key *key,
				काष्ठा sk_buff *skb,
				u8 *payload, माप_प्रकार payload_len)
अणु
	u8 rc4key[16];

	ieee80211_get_tkip_p2k(&key->conf, skb, rc4key);

	वापस ieee80211_wep_encrypt_data(ctx, rc4key, 16,
					  payload, payload_len);
पूर्ण

/* Decrypt packet payload with TKIP using @key. @pos is a poपूर्णांकer to the
 * beginning of the buffer containing IEEE 802.11 header payload, i.e.,
 * including IV, Ext. IV, real data, Michael MIC, ICV. @payload_len is the
 * length of payload, including IV, Ext. IV, MIC, ICV.  */
पूर्णांक ieee80211_tkip_decrypt_data(काष्ठा arc4_ctx *ctx,
				काष्ठा ieee80211_key *key,
				u8 *payload, माप_प्रकार payload_len, u8 *ta,
				u8 *ra, पूर्णांक only_iv, पूर्णांक queue,
				u32 *out_iv32, u16 *out_iv16)
अणु
	u32 iv32;
	u32 iv16;
	u8 rc4key[16], keyid, *pos = payload;
	पूर्णांक res;
	स्थिर u8 *tk = &key->conf.key[NL80211_TKIP_DATA_OFFSET_ENCR_KEY];
	काष्ठा tkip_ctx_rx *rx_ctx = &key->u.tkip.rx[queue];

	अगर (payload_len < 12)
		वापस -1;

	iv16 = (pos[0] << 8) | pos[2];
	keyid = pos[3];
	iv32 = get_unaligned_le32(pos + 4);
	pos += 8;

	अगर (!(keyid & (1 << 5)))
		वापस TKIP_DECRYPT_NO_EXT_IV;

	अगर ((keyid >> 6) != key->conf.keyidx)
		वापस TKIP_DECRYPT_INVALID_KEYIDX;

	/* Reject replays अगर the received TSC is smaller than or equal to the
	 * last received value in a valid message, but with an exception क्रम
	 * the हाल where a new key has been set and no valid frame using that
	 * key has yet received and the local RSC was initialized to 0. This
	 * exception allows the very first frame sent by the transmitter to be
	 * accepted even अगर that transmitter were to use TSC 0 (IEEE 802.11
	 * described TSC to be initialized to 1 whenever a new key is taken पूर्णांकo
	 * use).
	 */
	अगर (iv32 < rx_ctx->iv32 ||
	    (iv32 == rx_ctx->iv32 &&
	     (iv16 < rx_ctx->iv16 ||
	      (iv16 == rx_ctx->iv16 &&
	       (rx_ctx->iv32 || rx_ctx->iv16 ||
		rx_ctx->ctx.state != TKIP_STATE_NOT_INIT)))))
		वापस TKIP_DECRYPT_REPLAY;

	अगर (only_iv) अणु
		res = TKIP_DECRYPT_OK;
		rx_ctx->ctx.state = TKIP_STATE_PHASE1_HW_UPLOADED;
		जाओ करोne;
	पूर्ण

	अगर (rx_ctx->ctx.state == TKIP_STATE_NOT_INIT ||
	    rx_ctx->iv32 != iv32) अणु
		/* IV16 wrapped around - perक्रमm TKIP phase 1 */
		tkip_mixing_phase1(tk, &rx_ctx->ctx, ta, iv32);
	पूर्ण
	अगर (key->local->ops->update_tkip_key &&
	    key->flags & KEY_FLAG_UPLOADED_TO_HARDWARE &&
	    rx_ctx->ctx.state != TKIP_STATE_PHASE1_HW_UPLOADED) अणु
		काष्ठा ieee80211_sub_अगर_data *sdata = key->sdata;

		अगर (sdata->vअगर.type == NL80211_IFTYPE_AP_VLAN)
			sdata = container_of(key->sdata->bss,
					काष्ठा ieee80211_sub_अगर_data, u.ap);
		drv_update_tkip_key(key->local, sdata, &key->conf, key->sta,
				iv32, rx_ctx->ctx.p1k);
		rx_ctx->ctx.state = TKIP_STATE_PHASE1_HW_UPLOADED;
	पूर्ण

	tkip_mixing_phase2(tk, &rx_ctx->ctx, iv16, rc4key);

	res = ieee80211_wep_decrypt_data(ctx, rc4key, 16, pos, payload_len - 12);
 करोne:
	अगर (res == TKIP_DECRYPT_OK) अणु
		/*
		 * Record previously received IV, will be copied पूर्णांकo the
		 * key inक्रमmation after MIC verअगरication. It is possible
		 * that we करोn't catch replays of fragments but that's ok
		 * because the Michael MIC verication will then fail.
		 */
		*out_iv32 = iv32;
		*out_iv16 = iv16;
	पूर्ण

	वापस res;
पूर्ण
