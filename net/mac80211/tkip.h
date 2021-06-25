<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Copyright 2002-2004, Instant802 Networks, Inc.
 */

#अगर_अघोषित TKIP_H
#घोषणा TKIP_H

#समावेश <linux/types.h>
#समावेश <linux/crypto.h>
#समावेश "key.h"

पूर्णांक ieee80211_tkip_encrypt_data(काष्ठा arc4_ctx *ctx,
				काष्ठा ieee80211_key *key,
				काष्ठा sk_buff *skb,
				u8 *payload, माप_प्रकार payload_len);

क्रमागत अणु
	TKIP_DECRYPT_OK = 0,
	TKIP_DECRYPT_NO_EXT_IV = -1,
	TKIP_DECRYPT_INVALID_KEYIDX = -2,
	TKIP_DECRYPT_REPLAY = -3,
पूर्ण;
पूर्णांक ieee80211_tkip_decrypt_data(काष्ठा arc4_ctx *ctx,
				काष्ठा ieee80211_key *key,
				u8 *payload, माप_प्रकार payload_len, u8 *ta,
				u8 *ra, पूर्णांक only_iv, पूर्णांक queue,
				u32 *out_iv32, u16 *out_iv16);

#पूर्ण_अगर /* TKIP_H */
