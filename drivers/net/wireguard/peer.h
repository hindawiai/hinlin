<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Copyright (C) 2015-2019 Jason A. Donenfeld <Jason@zx2c4.com>. All Rights Reserved.
 */

#अगर_अघोषित _WG_PEER_H
#घोषणा _WG_PEER_H

#समावेश "device.h"
#समावेश "noise.h"
#समावेश "cookie.h"

#समावेश <linux/types.h>
#समावेश <linux/netfilter.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/kref.h>
#समावेश <net/dst_cache.h>

काष्ठा wg_device;

काष्ठा endpoपूर्णांक अणु
	जोड़ अणु
		काष्ठा sockaddr addr;
		काष्ठा sockaddr_in addr4;
		काष्ठा sockaddr_in6 addr6;
	पूर्ण;
	जोड़ अणु
		काष्ठा अणु
			काष्ठा in_addr src4;
			/* Essentially the same as addr6->scope_id */
			पूर्णांक src_अगर4;
		पूर्ण;
		काष्ठा in6_addr src6;
	पूर्ण;
पूर्ण;

काष्ठा wg_peer अणु
	काष्ठा wg_device *device;
	काष्ठा prev_queue tx_queue, rx_queue;
	काष्ठा sk_buff_head staged_packet_queue;
	पूर्णांक serial_work_cpu;
	bool is_dead;
	काष्ठा noise_keypairs keypairs;
	काष्ठा endpoपूर्णांक endpoपूर्णांक;
	काष्ठा dst_cache endpoपूर्णांक_cache;
	rwlock_t endpoपूर्णांक_lock;
	काष्ठा noise_handshake handshake;
	atomic64_t last_sent_handshake;
	काष्ठा work_काष्ठा transmit_handshake_work, clear_peer_work, transmit_packet_work;
	काष्ठा cookie latest_cookie;
	काष्ठा hlist_node pubkey_hash;
	u64 rx_bytes, tx_bytes;
	काष्ठा समयr_list समयr_retransmit_handshake, समयr_send_keepalive;
	काष्ठा समयr_list समयr_new_handshake, समयr_zero_key_material;
	काष्ठा समयr_list समयr_persistent_keepalive;
	अचिन्हित पूर्णांक समयr_handshake_attempts;
	u16 persistent_keepalive_पूर्णांकerval;
	bool समयr_need_another_keepalive;
	bool sent_lasपंचांगinute_handshake;
	काष्ठा बारpec64 wallसमय_last_handshake;
	काष्ठा kref refcount;
	काष्ठा rcu_head rcu;
	काष्ठा list_head peer_list;
	काष्ठा list_head allowedips_list;
	काष्ठा napi_काष्ठा napi;
	u64 पूर्णांकernal_id;
पूर्ण;

काष्ठा wg_peer *wg_peer_create(काष्ठा wg_device *wg,
			       स्थिर u8 खुला_key[NOISE_PUBLIC_KEY_LEN],
			       स्थिर u8 preshared_key[NOISE_SYMMETRIC_KEY_LEN]);

काष्ठा wg_peer *__must_check wg_peer_get_maybe_zero(काष्ठा wg_peer *peer);
अटल अंतरभूत काष्ठा wg_peer *wg_peer_get(काष्ठा wg_peer *peer)
अणु
	kref_get(&peer->refcount);
	वापस peer;
पूर्ण
व्योम wg_peer_put(काष्ठा wg_peer *peer);
व्योम wg_peer_हटाओ(काष्ठा wg_peer *peer);
व्योम wg_peer_हटाओ_all(काष्ठा wg_device *wg);

पूर्णांक wg_peer_init(व्योम);
व्योम wg_peer_uninit(व्योम);

#पूर्ण_अगर /* _WG_PEER_H */
