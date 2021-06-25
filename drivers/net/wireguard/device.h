<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Copyright (C) 2015-2019 Jason A. Donenfeld <Jason@zx2c4.com>. All Rights Reserved.
 */

#अगर_अघोषित _WG_DEVICE_H
#घोषणा _WG_DEVICE_H

#समावेश "noise.h"
#समावेश "allowedips.h"
#समावेश "peerlookup.h"
#समावेश "cookie.h"

#समावेश <linux/types.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/workqueue.h>
#समावेश <linux/mutex.h>
#समावेश <linux/net.h>
#समावेश <linux/ptr_ring.h>

काष्ठा wg_device;

काष्ठा multicore_worker अणु
	व्योम *ptr;
	काष्ठा work_काष्ठा work;
पूर्ण;

काष्ठा crypt_queue अणु
	काष्ठा ptr_ring ring;
	काष्ठा multicore_worker __percpu *worker;
	पूर्णांक last_cpu;
पूर्ण;

काष्ठा prev_queue अणु
	काष्ठा sk_buff *head, *tail, *peeked;
	काष्ठा अणु काष्ठा sk_buff *next, *prev; पूर्ण empty; // Match first 2 members of काष्ठा sk_buff.
	atomic_t count;
पूर्ण;

काष्ठा wg_device अणु
	काष्ठा net_device *dev;
	काष्ठा crypt_queue encrypt_queue, decrypt_queue;
	काष्ठा sock __rcu *sock4, *sock6;
	काष्ठा net __rcu *creating_net;
	काष्ठा noise_अटल_identity अटल_identity;
	काष्ठा workqueue_काष्ठा *handshake_receive_wq, *handshake_send_wq;
	काष्ठा workqueue_काष्ठा *packet_crypt_wq;
	काष्ठा sk_buff_head incoming_handshakes;
	पूर्णांक incoming_handshake_cpu;
	काष्ठा multicore_worker __percpu *incoming_handshakes_worker;
	काष्ठा cookie_checker cookie_checker;
	काष्ठा pubkey_hashtable *peer_hashtable;
	काष्ठा index_hashtable *index_hashtable;
	काष्ठा allowedips peer_allowedips;
	काष्ठा mutex device_update_lock, socket_update_lock;
	काष्ठा list_head device_list, peer_list;
	अचिन्हित पूर्णांक num_peers, device_update_gen;
	u32 fwmark;
	u16 incoming_port;
पूर्ण;

पूर्णांक wg_device_init(व्योम);
व्योम wg_device_uninit(व्योम);

#पूर्ण_अगर /* _WG_DEVICE_H */
