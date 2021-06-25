<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Copyright (C) 2015-2019 Jason A. Donenfeld <Jason@zx2c4.com>. All Rights Reserved.
 */

#अगर_अघोषित _WG_COOKIE_H
#घोषणा _WG_COOKIE_H

#समावेश "messages.h"
#समावेश <linux/rwsem.h>

काष्ठा wg_peer;

काष्ठा cookie_checker अणु
	u8 secret[NOISE_HASH_LEN];
	u8 cookie_encryption_key[NOISE_SYMMETRIC_KEY_LEN];
	u8 message_mac1_key[NOISE_SYMMETRIC_KEY_LEN];
	u64 secret_birthdate;
	काष्ठा rw_semaphore secret_lock;
	काष्ठा wg_device *device;
पूर्ण;

काष्ठा cookie अणु
	u64 birthdate;
	bool is_valid;
	u8 cookie[COOKIE_LEN];
	bool have_sent_mac1;
	u8 last_mac1_sent[COOKIE_LEN];
	u8 cookie_decryption_key[NOISE_SYMMETRIC_KEY_LEN];
	u8 message_mac1_key[NOISE_SYMMETRIC_KEY_LEN];
	काष्ठा rw_semaphore lock;
पूर्ण;

क्रमागत cookie_mac_state अणु
	INVALID_MAC,
	VALID_MAC_BUT_NO_COOKIE,
	VALID_MAC_WITH_COOKIE_BUT_RATELIMITED,
	VALID_MAC_WITH_COOKIE
पूर्ण;

व्योम wg_cookie_checker_init(काष्ठा cookie_checker *checker,
			    काष्ठा wg_device *wg);
व्योम wg_cookie_checker_precompute_device_keys(काष्ठा cookie_checker *checker);
व्योम wg_cookie_checker_precompute_peer_keys(काष्ठा wg_peer *peer);
व्योम wg_cookie_init(काष्ठा cookie *cookie);

क्रमागत cookie_mac_state wg_cookie_validate_packet(काष्ठा cookie_checker *checker,
						काष्ठा sk_buff *skb,
						bool check_cookie);
व्योम wg_cookie_add_mac_to_packet(व्योम *message, माप_प्रकार len,
				 काष्ठा wg_peer *peer);

व्योम wg_cookie_message_create(काष्ठा message_handshake_cookie *src,
			      काष्ठा sk_buff *skb, __le32 index,
			      काष्ठा cookie_checker *checker);
व्योम wg_cookie_message_consume(काष्ठा message_handshake_cookie *src,
			       काष्ठा wg_device *wg);

#पूर्ण_अगर /* _WG_COOKIE_H */
