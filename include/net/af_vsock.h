<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * VMware vSockets Driver
 *
 * Copyright (C) 2007-2013 VMware, Inc. All rights reserved.
 */

#अगर_अघोषित __AF_VSOCK_H__
#घोषणा __AF_VSOCK_H__

#समावेश <linux/kernel.h>
#समावेश <linux/workqueue.h>
#समावेश <uapi/linux/vm_sockets.h>

#समावेश "vsock_addr.h"

#घोषणा LAST_RESERVED_PORT 1023

#घोषणा VSOCK_HASH_SIZE         251
बाह्य काष्ठा list_head vsock_bind_table[VSOCK_HASH_SIZE + 1];
बाह्य काष्ठा list_head vsock_connected_table[VSOCK_HASH_SIZE];
बाह्य spinlock_t vsock_table_lock;

#घोषणा vsock_sk(__sk)    ((काष्ठा vsock_sock *)__sk)
#घोषणा sk_vsock(__vsk)   (&(__vsk)->sk)

काष्ठा vsock_sock अणु
	/* sk must be the first member. */
	काष्ठा sock sk;
	स्थिर काष्ठा vsock_transport *transport;
	काष्ठा sockaddr_vm local_addr;
	काष्ठा sockaddr_vm remote_addr;
	/* Links क्रम the global tables of bound and connected sockets. */
	काष्ठा list_head bound_table;
	काष्ठा list_head connected_table;
	/* Accessed without the socket lock held. This means it can never be
	 * modअगरied outsided of socket create or deकाष्ठा.
	 */
	bool trusted;
	bool cached_peer_allow_dgram;	/* Dgram communication allowed to
					 * cached peer?
					 */
	u32 cached_peer;  /* Context ID of last dgram destination check. */
	स्थिर काष्ठा cred *owner;
	/* Rest are SOCK_STREAM only. */
	दीर्घ connect_समयout;
	/* Listening socket that this came from. */
	काष्ठा sock *listener;
	/* Used क्रम pending list and accept queue during connection handshake.
	 * The listening socket is the head क्रम both lists.  Sockets created
	 * क्रम connection requests are placed in the pending list until they
	 * are connected, at which poपूर्णांक they are put in the accept queue list
	 * so they can be accepted in accept().  If accept() cannot accept the
	 * connection, it is marked as rejected so the cleanup function knows
	 * to clean up the socket.
	 */
	काष्ठा list_head pending_links;
	काष्ठा list_head accept_queue;
	bool rejected;
	काष्ठा delayed_work connect_work;
	काष्ठा delayed_work pending_work;
	काष्ठा delayed_work बंद_work;
	bool बंद_work_scheduled;
	u32 peer_shutकरोwn;
	bool sent_request;
	bool ignore_connecting_rst;

	/* Protected by lock_sock(sk) */
	u64 buffer_size;
	u64 buffer_min_size;
	u64 buffer_max_size;

	/* Private to transport. */
	व्योम *trans;
पूर्ण;

s64 vsock_stream_has_data(काष्ठा vsock_sock *vsk);
s64 vsock_stream_has_space(काष्ठा vsock_sock *vsk);
काष्ठा sock *vsock_create_connected(काष्ठा sock *parent);

/**** TRANSPORT ****/

काष्ठा vsock_transport_recv_notअगरy_data अणु
	u64 data1; /* Transport-defined. */
	u64 data2; /* Transport-defined. */
	bool notअगरy_on_block;
पूर्ण;

काष्ठा vsock_transport_send_notअगरy_data अणु
	u64 data1; /* Transport-defined. */
	u64 data2; /* Transport-defined. */
पूर्ण;

/* Transport features flags */
/* Transport provides host->guest communication */
#घोषणा VSOCK_TRANSPORT_F_H2G		0x00000001
/* Transport provides guest->host communication */
#घोषणा VSOCK_TRANSPORT_F_G2H		0x00000002
/* Transport provides DGRAM communication */
#घोषणा VSOCK_TRANSPORT_F_DGRAM		0x00000004
/* Transport provides local (loopback) communication */
#घोषणा VSOCK_TRANSPORT_F_LOCAL		0x00000008

काष्ठा vsock_transport अणु
	काष्ठा module *module;

	/* Initialize/tear-करोwn socket. */
	पूर्णांक (*init)(काष्ठा vsock_sock *, काष्ठा vsock_sock *);
	व्योम (*deकाष्ठा)(काष्ठा vsock_sock *);
	व्योम (*release)(काष्ठा vsock_sock *);

	/* Cancel all pending packets sent on vsock. */
	पूर्णांक (*cancel_pkt)(काष्ठा vsock_sock *vsk);

	/* Connections. */
	पूर्णांक (*connect)(काष्ठा vsock_sock *);

	/* DGRAM. */
	पूर्णांक (*dgram_bind)(काष्ठा vsock_sock *, काष्ठा sockaddr_vm *);
	पूर्णांक (*dgram_dequeue)(काष्ठा vsock_sock *vsk, काष्ठा msghdr *msg,
			     माप_प्रकार len, पूर्णांक flags);
	पूर्णांक (*dgram_enqueue)(काष्ठा vsock_sock *, काष्ठा sockaddr_vm *,
			     काष्ठा msghdr *, माप_प्रकार len);
	bool (*dgram_allow)(u32 cid, u32 port);

	/* STREAM. */
	/* TODO: stream_bind() */
	sमाप_प्रकार (*stream_dequeue)(काष्ठा vsock_sock *, काष्ठा msghdr *,
				  माप_प्रकार len, पूर्णांक flags);
	sमाप_प्रकार (*stream_enqueue)(काष्ठा vsock_sock *, काष्ठा msghdr *,
				  माप_प्रकार len);
	s64 (*stream_has_data)(काष्ठा vsock_sock *);
	s64 (*stream_has_space)(काष्ठा vsock_sock *);
	u64 (*stream_rcvhiwat)(काष्ठा vsock_sock *);
	bool (*stream_is_active)(काष्ठा vsock_sock *);
	bool (*stream_allow)(u32 cid, u32 port);

	/* Notअगरication. */
	पूर्णांक (*notअगरy_poll_in)(काष्ठा vsock_sock *, माप_प्रकार, bool *);
	पूर्णांक (*notअगरy_poll_out)(काष्ठा vsock_sock *, माप_प्रकार, bool *);
	पूर्णांक (*notअगरy_recv_init)(काष्ठा vsock_sock *, माप_प्रकार,
		काष्ठा vsock_transport_recv_notअगरy_data *);
	पूर्णांक (*notअगरy_recv_pre_block)(काष्ठा vsock_sock *, माप_प्रकार,
		काष्ठा vsock_transport_recv_notअगरy_data *);
	पूर्णांक (*notअगरy_recv_pre_dequeue)(काष्ठा vsock_sock *, माप_प्रकार,
		काष्ठा vsock_transport_recv_notअगरy_data *);
	पूर्णांक (*notअगरy_recv_post_dequeue)(काष्ठा vsock_sock *, माप_प्रकार,
		sमाप_प्रकार, bool, काष्ठा vsock_transport_recv_notअगरy_data *);
	पूर्णांक (*notअगरy_send_init)(काष्ठा vsock_sock *,
		काष्ठा vsock_transport_send_notअगरy_data *);
	पूर्णांक (*notअगरy_send_pre_block)(काष्ठा vsock_sock *,
		काष्ठा vsock_transport_send_notअगरy_data *);
	पूर्णांक (*notअगरy_send_pre_enqueue)(काष्ठा vsock_sock *,
		काष्ठा vsock_transport_send_notअगरy_data *);
	पूर्णांक (*notअगरy_send_post_enqueue)(काष्ठा vsock_sock *, sमाप_प्रकार,
		काष्ठा vsock_transport_send_notअगरy_data *);
	/* sk_lock held by the caller */
	व्योम (*notअगरy_buffer_size)(काष्ठा vsock_sock *, u64 *);

	/* Shutकरोwn. */
	पूर्णांक (*shutकरोwn)(काष्ठा vsock_sock *, पूर्णांक);

	/* Addressing. */
	u32 (*get_local_cid)(व्योम);
पूर्ण;

/**** CORE ****/

पूर्णांक vsock_core_रेजिस्टर(स्थिर काष्ठा vsock_transport *t, पूर्णांक features);
व्योम vsock_core_unरेजिस्टर(स्थिर काष्ठा vsock_transport *t);

/* The transport may करोwncast this to access transport-specअगरic functions */
स्थिर काष्ठा vsock_transport *vsock_core_get_transport(काष्ठा vsock_sock *vsk);

/**** UTILS ****/

/* vsock_table_lock must be held */
अटल अंतरभूत bool __vsock_in_bound_table(काष्ठा vsock_sock *vsk)
अणु
	वापस !list_empty(&vsk->bound_table);
पूर्ण

/* vsock_table_lock must be held */
अटल अंतरभूत bool __vsock_in_connected_table(काष्ठा vsock_sock *vsk)
अणु
	वापस !list_empty(&vsk->connected_table);
पूर्ण

व्योम vsock_release_pending(काष्ठा sock *pending);
व्योम vsock_add_pending(काष्ठा sock *listener, काष्ठा sock *pending);
व्योम vsock_हटाओ_pending(काष्ठा sock *listener, काष्ठा sock *pending);
व्योम vsock_enqueue_accept(काष्ठा sock *listener, काष्ठा sock *connected);
व्योम vsock_insert_connected(काष्ठा vsock_sock *vsk);
व्योम vsock_हटाओ_bound(काष्ठा vsock_sock *vsk);
व्योम vsock_हटाओ_connected(काष्ठा vsock_sock *vsk);
काष्ठा sock *vsock_find_bound_socket(काष्ठा sockaddr_vm *addr);
काष्ठा sock *vsock_find_connected_socket(काष्ठा sockaddr_vm *src,
					 काष्ठा sockaddr_vm *dst);
व्योम vsock_हटाओ_sock(काष्ठा vsock_sock *vsk);
व्योम vsock_क्रम_each_connected_socket(व्योम (*fn)(काष्ठा sock *sk));
पूर्णांक vsock_assign_transport(काष्ठा vsock_sock *vsk, काष्ठा vsock_sock *psk);
bool vsock_find_cid(अचिन्हित पूर्णांक cid);

/**** TAP ****/

काष्ठा vsock_tap अणु
	काष्ठा net_device *dev;
	काष्ठा module *module;
	काष्ठा list_head list;
पूर्ण;

पूर्णांक vsock_init_tap(व्योम);
पूर्णांक vsock_add_tap(काष्ठा vsock_tap *vt);
पूर्णांक vsock_हटाओ_tap(काष्ठा vsock_tap *vt);
व्योम vsock_deliver_tap(काष्ठा sk_buff *build_skb(व्योम *opaque), व्योम *opaque);

#पूर्ण_अगर /* __AF_VSOCK_H__ */
