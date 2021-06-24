<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Software WEP encryption implementation
 * Copyright 2002, Jouni Malinen <jkmaline@cc.hut.fi>
 * Copyright 2003, Instant802 Networks, Inc.
 */

#अगर_अघोषित WEP_H
#घोषणा WEP_H

#समावेश <linux/skbuff.h>
#समावेश <linux/types.h>
#समावेश "ieee80211_i.h"
#समावेश "key.h"

व्योम ieee80211_wep_init(काष्ठा ieee80211_local *local);
पूर्णांक ieee80211_wep_encrypt_data(काष्ठा arc4_ctx *ctx, u8 *rc4key,
				माप_प्रकार klen, u8 *data, माप_प्रकार data_len);
पूर्णांक ieee80211_wep_encrypt(काष्ठा ieee80211_local *local,
			  काष्ठा sk_buff *skb,
			  स्थिर u8 *key, पूर्णांक keylen, पूर्णांक keyidx);
पूर्णांक ieee80211_wep_decrypt_data(काष्ठा arc4_ctx *ctx, u8 *rc4key,
			       माप_प्रकार klen, u8 *data, माप_प्रकार data_len);

ieee80211_rx_result
ieee80211_crypto_wep_decrypt(काष्ठा ieee80211_rx_data *rx);
ieee80211_tx_result
ieee80211_crypto_wep_encrypt(काष्ठा ieee80211_tx_data *tx);

#पूर्ण_अगर /* WEP_H */
