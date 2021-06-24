<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Copyright (C) 2015-2019 Jason A. Donenfeld <Jason@zx2c4.com>. All Rights Reserved.
 */

#अगर_अघोषित _WG_QUEUEING_H
#घोषणा _WG_QUEUEING_H

#समावेश "peer.h"
#समावेश <linux/types.h>
#समावेश <linux/skbuff.h>
#समावेश <linux/ip.h>
#समावेश <linux/ipv6.h>
#समावेश <net/ip_tunnels.h>

काष्ठा wg_device;
काष्ठा wg_peer;
काष्ठा multicore_worker;
काष्ठा crypt_queue;
काष्ठा prev_queue;
काष्ठा sk_buff;

/* queueing.c APIs: */
पूर्णांक wg_packet_queue_init(काष्ठा crypt_queue *queue, work_func_t function,
			 अचिन्हित पूर्णांक len);
व्योम wg_packet_queue_मुक्त(काष्ठा crypt_queue *queue);
काष्ठा multicore_worker __percpu *
wg_packet_percpu_multicore_worker_alloc(work_func_t function, व्योम *ptr);

/* receive.c APIs: */
व्योम wg_packet_receive(काष्ठा wg_device *wg, काष्ठा sk_buff *skb);
व्योम wg_packet_handshake_receive_worker(काष्ठा work_काष्ठा *work);
/* NAPI poll function: */
पूर्णांक wg_packet_rx_poll(काष्ठा napi_काष्ठा *napi, पूर्णांक budget);
/* Workqueue worker: */
व्योम wg_packet_decrypt_worker(काष्ठा work_काष्ठा *work);

/* send.c APIs: */
व्योम wg_packet_send_queued_handshake_initiation(काष्ठा wg_peer *peer,
						bool is_retry);
व्योम wg_packet_send_handshake_response(काष्ठा wg_peer *peer);
व्योम wg_packet_send_handshake_cookie(काष्ठा wg_device *wg,
				     काष्ठा sk_buff *initiating_skb,
				     __le32 sender_index);
व्योम wg_packet_send_keepalive(काष्ठा wg_peer *peer);
व्योम wg_packet_purge_staged_packets(काष्ठा wg_peer *peer);
व्योम wg_packet_send_staged_packets(काष्ठा wg_peer *peer);
/* Workqueue workers: */
व्योम wg_packet_handshake_send_worker(काष्ठा work_काष्ठा *work);
व्योम wg_packet_tx_worker(काष्ठा work_काष्ठा *work);
व्योम wg_packet_encrypt_worker(काष्ठा work_काष्ठा *work);

क्रमागत packet_state अणु
	PACKET_STATE_UNCRYPTED,
	PACKET_STATE_CRYPTED,
	PACKET_STATE_DEAD
पूर्ण;

काष्ठा packet_cb अणु
	u64 nonce;
	काष्ठा noise_keypair *keypair;
	atomic_t state;
	u32 mtu;
	u8 ds;
पूर्ण;

#घोषणा PACKET_CB(skb) ((काष्ठा packet_cb *)((skb)->cb))
#घोषणा PACKET_PEER(skb) (PACKET_CB(skb)->keypair->entry.peer)

अटल अंतरभूत bool wg_check_packet_protocol(काष्ठा sk_buff *skb)
अणु
	__be16 real_protocol = ip_tunnel_parse_protocol(skb);
	वापस real_protocol && skb->protocol == real_protocol;
पूर्ण

अटल अंतरभूत व्योम wg_reset_packet(काष्ठा sk_buff *skb, bool encapsulating)
अणु
	u8 l4_hash = skb->l4_hash;
	u8 sw_hash = skb->sw_hash;
	u32 hash = skb->hash;
	skb_scrub_packet(skb, true);
	स_रखो(&skb->headers_start, 0,
	       दुरत्व(काष्ठा sk_buff, headers_end) -
		       दुरत्व(काष्ठा sk_buff, headers_start));
	अगर (encapsulating) अणु
		skb->l4_hash = l4_hash;
		skb->sw_hash = sw_hash;
		skb->hash = hash;
	पूर्ण
	skb->queue_mapping = 0;
	skb->nohdr = 0;
	skb->peeked = 0;
	skb->mac_len = 0;
	skb->dev = शून्य;
#अगर_घोषित CONFIG_NET_SCHED
	skb->tc_index = 0;
#पूर्ण_अगर
	skb_reset_redirect(skb);
	skb->hdr_len = skb_headroom(skb);
	skb_reset_mac_header(skb);
	skb_reset_network_header(skb);
	skb_reset_transport_header(skb);
	skb_probe_transport_header(skb);
	skb_reset_inner_headers(skb);
पूर्ण

अटल अंतरभूत पूर्णांक wg_cpumask_choose_online(पूर्णांक *stored_cpu, अचिन्हित पूर्णांक id)
अणु
	अचिन्हित पूर्णांक cpu = *stored_cpu, cpu_index, i;

	अगर (unlikely(cpu == nr_cpumask_bits ||
		     !cpumask_test_cpu(cpu, cpu_online_mask))) अणु
		cpu_index = id % cpumask_weight(cpu_online_mask);
		cpu = cpumask_first(cpu_online_mask);
		क्रम (i = 0; i < cpu_index; ++i)
			cpu = cpumask_next(cpu, cpu_online_mask);
		*stored_cpu = cpu;
	पूर्ण
	वापस cpu;
पूर्ण

/* This function is racy, in the sense that next is unlocked, so it could वापस
 * the same CPU twice. A race-मुक्त version of this would be to instead store an
 * atomic sequence number, करो an increment-and-वापस, and then iterate through
 * every possible CPU until we get to that index -- choose_cpu. However that's
 * a bit slower, and it करोesn't seem like this potential race actually
 * पूर्णांकroduces any perक्रमmance loss, so we live with it.
 */
अटल अंतरभूत पूर्णांक wg_cpumask_next_online(पूर्णांक *next)
अणु
	पूर्णांक cpu = *next;

	जबतक (unlikely(!cpumask_test_cpu(cpu, cpu_online_mask)))
		cpu = cpumask_next(cpu, cpu_online_mask) % nr_cpumask_bits;
	*next = cpumask_next(cpu, cpu_online_mask) % nr_cpumask_bits;
	वापस cpu;
पूर्ण

व्योम wg_prev_queue_init(काष्ठा prev_queue *queue);

/* Multi producer */
bool wg_prev_queue_enqueue(काष्ठा prev_queue *queue, काष्ठा sk_buff *skb);

/* Single consumer */
काष्ठा sk_buff *wg_prev_queue_dequeue(काष्ठा prev_queue *queue);

/* Single consumer */
अटल अंतरभूत काष्ठा sk_buff *wg_prev_queue_peek(काष्ठा prev_queue *queue)
अणु
	अगर (queue->peeked)
		वापस queue->peeked;
	queue->peeked = wg_prev_queue_dequeue(queue);
	वापस queue->peeked;
पूर्ण

/* Single consumer */
अटल अंतरभूत व्योम wg_prev_queue_drop_peeked(काष्ठा prev_queue *queue)
अणु
	queue->peeked = शून्य;
पूर्ण

अटल अंतरभूत पूर्णांक wg_queue_enqueue_per_device_and_peer(
	काष्ठा crypt_queue *device_queue, काष्ठा prev_queue *peer_queue,
	काष्ठा sk_buff *skb, काष्ठा workqueue_काष्ठा *wq, पूर्णांक *next_cpu)
अणु
	पूर्णांक cpu;

	atomic_set_release(&PACKET_CB(skb)->state, PACKET_STATE_UNCRYPTED);
	/* We first queue this up क्रम the peer ingestion, but the consumer
	 * will रुको क्रम the state to change to CRYPTED or DEAD beक्रमe.
	 */
	अगर (unlikely(!wg_prev_queue_enqueue(peer_queue, skb)))
		वापस -ENOSPC;

	/* Then we queue it up in the device queue, which consumes the
	 * packet as soon as it can.
	 */
	cpu = wg_cpumask_next_online(next_cpu);
	अगर (unlikely(ptr_ring_produce_bh(&device_queue->ring, skb)))
		वापस -EPIPE;
	queue_work_on(cpu, wq, &per_cpu_ptr(device_queue->worker, cpu)->work);
	वापस 0;
पूर्ण

अटल अंतरभूत व्योम wg_queue_enqueue_per_peer_tx(काष्ठा sk_buff *skb, क्रमागत packet_state state)
अणु
	/* We take a reference, because as soon as we call atomic_set, the
	 * peer can be मुक्तd from below us.
	 */
	काष्ठा wg_peer *peer = wg_peer_get(PACKET_PEER(skb));

	atomic_set_release(&PACKET_CB(skb)->state, state);
	queue_work_on(wg_cpumask_choose_online(&peer->serial_work_cpu, peer->पूर्णांकernal_id),
		      peer->device->packet_crypt_wq, &peer->transmit_packet_work);
	wg_peer_put(peer);
पूर्ण

अटल अंतरभूत व्योम wg_queue_enqueue_per_peer_rx(काष्ठा sk_buff *skb, क्रमागत packet_state state)
अणु
	/* We take a reference, because as soon as we call atomic_set, the
	 * peer can be मुक्तd from below us.
	 */
	काष्ठा wg_peer *peer = wg_peer_get(PACKET_PEER(skb));

	atomic_set_release(&PACKET_CB(skb)->state, state);
	napi_schedule(&peer->napi);
	wg_peer_put(peer);
पूर्ण

#अगर_घोषित DEBUG
bool wg_packet_counter_selftest(व्योम);
#पूर्ण_अगर

#पूर्ण_अगर /* _WG_QUEUEING_H */
