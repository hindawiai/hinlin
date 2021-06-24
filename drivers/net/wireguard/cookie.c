<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (C) 2015-2019 Jason A. Donenfeld <Jason@zx2c4.com>. All Rights Reserved.
 */

#समावेश "cookie.h"
#समावेश "peer.h"
#समावेश "device.h"
#समावेश "messages.h"
#समावेश "ratelimiter.h"
#समावेश "timers.h"

#समावेश <crypto/blake2s.h>
#समावेश <crypto/chacha20poly1305.h>

#समावेश <net/ipv6.h>
#समावेश <crypto/algapi.h>

व्योम wg_cookie_checker_init(काष्ठा cookie_checker *checker,
			    काष्ठा wg_device *wg)
अणु
	init_rwsem(&checker->secret_lock);
	checker->secret_birthdate = kसमय_get_coarse_bootसमय_ns();
	get_अक्रमom_bytes(checker->secret, NOISE_HASH_LEN);
	checker->device = wg;
पूर्ण

क्रमागत अणु COOKIE_KEY_LABEL_LEN = 8 पूर्ण;
अटल स्थिर u8 mac1_key_label[COOKIE_KEY_LABEL_LEN] = "mac1----";
अटल स्थिर u8 cookie_key_label[COOKIE_KEY_LABEL_LEN] = "cookie--";

अटल व्योम precompute_key(u8 key[NOISE_SYMMETRIC_KEY_LEN],
			   स्थिर u8 pubkey[NOISE_PUBLIC_KEY_LEN],
			   स्थिर u8 label[COOKIE_KEY_LABEL_LEN])
अणु
	काष्ठा blake2s_state blake;

	blake2s_init(&blake, NOISE_SYMMETRIC_KEY_LEN);
	blake2s_update(&blake, label, COOKIE_KEY_LABEL_LEN);
	blake2s_update(&blake, pubkey, NOISE_PUBLIC_KEY_LEN);
	blake2s_final(&blake, key);
पूर्ण

/* Must hold peer->handshake.अटल_identity->lock */
व्योम wg_cookie_checker_precompute_device_keys(काष्ठा cookie_checker *checker)
अणु
	अगर (likely(checker->device->अटल_identity.has_identity)) अणु
		precompute_key(checker->cookie_encryption_key,
			       checker->device->अटल_identity.अटल_खुला,
			       cookie_key_label);
		precompute_key(checker->message_mac1_key,
			       checker->device->अटल_identity.अटल_खुला,
			       mac1_key_label);
	पूर्ण अन्यथा अणु
		स_रखो(checker->cookie_encryption_key, 0,
		       NOISE_SYMMETRIC_KEY_LEN);
		स_रखो(checker->message_mac1_key, 0, NOISE_SYMMETRIC_KEY_LEN);
	पूर्ण
पूर्ण

व्योम wg_cookie_checker_precompute_peer_keys(काष्ठा wg_peer *peer)
अणु
	precompute_key(peer->latest_cookie.cookie_decryption_key,
		       peer->handshake.remote_अटल, cookie_key_label);
	precompute_key(peer->latest_cookie.message_mac1_key,
		       peer->handshake.remote_अटल, mac1_key_label);
पूर्ण

व्योम wg_cookie_init(काष्ठा cookie *cookie)
अणु
	स_रखो(cookie, 0, माप(*cookie));
	init_rwsem(&cookie->lock);
पूर्ण

अटल व्योम compute_mac1(u8 mac1[COOKIE_LEN], स्थिर व्योम *message, माप_प्रकार len,
			 स्थिर u8 key[NOISE_SYMMETRIC_KEY_LEN])
अणु
	len = len - माप(काष्ठा message_macs) +
	      दुरत्व(काष्ठा message_macs, mac1);
	blake2s(mac1, message, key, COOKIE_LEN, len, NOISE_SYMMETRIC_KEY_LEN);
पूर्ण

अटल व्योम compute_mac2(u8 mac2[COOKIE_LEN], स्थिर व्योम *message, माप_प्रकार len,
			 स्थिर u8 cookie[COOKIE_LEN])
अणु
	len = len - माप(काष्ठा message_macs) +
	      दुरत्व(काष्ठा message_macs, mac2);
	blake2s(mac2, message, cookie, COOKIE_LEN, len, COOKIE_LEN);
पूर्ण

अटल व्योम make_cookie(u8 cookie[COOKIE_LEN], काष्ठा sk_buff *skb,
			काष्ठा cookie_checker *checker)
अणु
	काष्ठा blake2s_state state;

	अगर (wg_birthdate_has_expired(checker->secret_birthdate,
				     COOKIE_SECRET_MAX_AGE)) अणु
		करोwn_ग_लिखो(&checker->secret_lock);
		checker->secret_birthdate = kसमय_get_coarse_bootसमय_ns();
		get_अक्रमom_bytes(checker->secret, NOISE_HASH_LEN);
		up_ग_लिखो(&checker->secret_lock);
	पूर्ण

	करोwn_पढ़ो(&checker->secret_lock);

	blake2s_init_key(&state, COOKIE_LEN, checker->secret, NOISE_HASH_LEN);
	अगर (skb->protocol == htons(ETH_P_IP))
		blake2s_update(&state, (u8 *)&ip_hdr(skb)->saddr,
			       माप(काष्ठा in_addr));
	अन्यथा अगर (skb->protocol == htons(ETH_P_IPV6))
		blake2s_update(&state, (u8 *)&ipv6_hdr(skb)->saddr,
			       माप(काष्ठा in6_addr));
	blake2s_update(&state, (u8 *)&udp_hdr(skb)->source, माप(__be16));
	blake2s_final(&state, cookie);

	up_पढ़ो(&checker->secret_lock);
पूर्ण

क्रमागत cookie_mac_state wg_cookie_validate_packet(काष्ठा cookie_checker *checker,
						काष्ठा sk_buff *skb,
						bool check_cookie)
अणु
	काष्ठा message_macs *macs = (काष्ठा message_macs *)
		(skb->data + skb->len - माप(*macs));
	क्रमागत cookie_mac_state ret;
	u8 computed_mac[COOKIE_LEN];
	u8 cookie[COOKIE_LEN];

	ret = INVALID_MAC;
	compute_mac1(computed_mac, skb->data, skb->len,
		     checker->message_mac1_key);
	अगर (crypto_memneq(computed_mac, macs->mac1, COOKIE_LEN))
		जाओ out;

	ret = VALID_MAC_BUT_NO_COOKIE;

	अगर (!check_cookie)
		जाओ out;

	make_cookie(cookie, skb, checker);

	compute_mac2(computed_mac, skb->data, skb->len, cookie);
	अगर (crypto_memneq(computed_mac, macs->mac2, COOKIE_LEN))
		जाओ out;

	ret = VALID_MAC_WITH_COOKIE_BUT_RATELIMITED;
	अगर (!wg_ratelimiter_allow(skb, dev_net(checker->device->dev)))
		जाओ out;

	ret = VALID_MAC_WITH_COOKIE;

out:
	वापस ret;
पूर्ण

व्योम wg_cookie_add_mac_to_packet(व्योम *message, माप_प्रकार len,
				 काष्ठा wg_peer *peer)
अणु
	काष्ठा message_macs *macs = (काष्ठा message_macs *)
		((u8 *)message + len - माप(*macs));

	करोwn_ग_लिखो(&peer->latest_cookie.lock);
	compute_mac1(macs->mac1, message, len,
		     peer->latest_cookie.message_mac1_key);
	स_नकल(peer->latest_cookie.last_mac1_sent, macs->mac1, COOKIE_LEN);
	peer->latest_cookie.have_sent_mac1 = true;
	up_ग_लिखो(&peer->latest_cookie.lock);

	करोwn_पढ़ो(&peer->latest_cookie.lock);
	अगर (peer->latest_cookie.is_valid &&
	    !wg_birthdate_has_expired(peer->latest_cookie.birthdate,
				COOKIE_SECRET_MAX_AGE - COOKIE_SECRET_LATENCY))
		compute_mac2(macs->mac2, message, len,
			     peer->latest_cookie.cookie);
	अन्यथा
		स_रखो(macs->mac2, 0, COOKIE_LEN);
	up_पढ़ो(&peer->latest_cookie.lock);
पूर्ण

व्योम wg_cookie_message_create(काष्ठा message_handshake_cookie *dst,
			      काष्ठा sk_buff *skb, __le32 index,
			      काष्ठा cookie_checker *checker)
अणु
	काष्ठा message_macs *macs = (काष्ठा message_macs *)
		((u8 *)skb->data + skb->len - माप(*macs));
	u8 cookie[COOKIE_LEN];

	dst->header.type = cpu_to_le32(MESSAGE_HANDSHAKE_COOKIE);
	dst->receiver_index = index;
	get_अक्रमom_bytes_रुको(dst->nonce, COOKIE_NONCE_LEN);

	make_cookie(cookie, skb, checker);
	xchacha20poly1305_encrypt(dst->encrypted_cookie, cookie, COOKIE_LEN,
				  macs->mac1, COOKIE_LEN, dst->nonce,
				  checker->cookie_encryption_key);
पूर्ण

व्योम wg_cookie_message_consume(काष्ठा message_handshake_cookie *src,
			       काष्ठा wg_device *wg)
अणु
	काष्ठा wg_peer *peer = शून्य;
	u8 cookie[COOKIE_LEN];
	bool ret;

	अगर (unlikely(!wg_index_hashtable_lookup(wg->index_hashtable,
						INDEX_HASHTABLE_HANDSHAKE |
						INDEX_HASHTABLE_KEYPAIR,
						src->receiver_index, &peer)))
		वापस;

	करोwn_पढ़ो(&peer->latest_cookie.lock);
	अगर (unlikely(!peer->latest_cookie.have_sent_mac1)) अणु
		up_पढ़ो(&peer->latest_cookie.lock);
		जाओ out;
	पूर्ण
	ret = xchacha20poly1305_decrypt(
		cookie, src->encrypted_cookie, माप(src->encrypted_cookie),
		peer->latest_cookie.last_mac1_sent, COOKIE_LEN, src->nonce,
		peer->latest_cookie.cookie_decryption_key);
	up_पढ़ो(&peer->latest_cookie.lock);

	अगर (ret) अणु
		करोwn_ग_लिखो(&peer->latest_cookie.lock);
		स_नकल(peer->latest_cookie.cookie, cookie, COOKIE_LEN);
		peer->latest_cookie.birthdate = kसमय_get_coarse_bootसमय_ns();
		peer->latest_cookie.is_valid = true;
		peer->latest_cookie.have_sent_mac1 = false;
		up_ग_लिखो(&peer->latest_cookie.lock);
	पूर्ण अन्यथा अणु
		net_dbg_ratelimited("%s: Could not decrypt invalid cookie response\n",
				    wg->dev->name);
	पूर्ण

out:
	wg_peer_put(peer);
पूर्ण
