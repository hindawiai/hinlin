<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * Copyright (C) 2005 Oracle.  All rights reserved.
 */

#अगर_अघोषित O2CLUSTER_TCP_INTERNAL_H
#घोषणा O2CLUSTER_TCP_INTERNAL_H

#घोषणा O2NET_MSG_MAGIC           ((u16)0xfa55)
#घोषणा O2NET_MSG_STATUS_MAGIC    ((u16)0xfa56)
#घोषणा O2NET_MSG_KEEP_REQ_MAGIC  ((u16)0xfa57)
#घोषणा O2NET_MSG_KEEP_RESP_MAGIC ((u16)0xfa58)

/* we're delaying our quorum decision so that heartbeat will have समयd
 * out truly dead nodes by the समय we come around to making decisions
 * on their number */
#घोषणा O2NET_QUORUM_DELAY_MS	((o2hb_dead_threshold + 2) * O2HB_REGION_TIMEOUT_MS)

/*
 * This version number represents quite a lot, unक्रमtunately.  It not
 * only represents the raw network message protocol on the wire but also
 * locking semantics of the file प्रणाली using the protocol.  It should
 * be somewhere अन्यथा, I'm sure, but right now it isn't.
 *
 * With version 11, we separate out the fileप्रणाली locking portion.  The
 * fileप्रणाली now has a major.minor version it negotiates.  Version 11
 * पूर्णांकroduces this negotiation to the o2dlm protocol, and as such the
 * version here in tcp_पूर्णांकernal.h should not need to be bumped क्रम
 * fileप्रणाली locking changes.
 *
 * New in version 11
 * 	- Negotiation of fileप्रणाली locking in the dlm join.
 *
 * New in version 10:
 * 	- Meta/data locks combined
 *
 * New in version 9:
 * 	- All votes हटाओd
 *
 * New in version 8:
 * 	- Replace delete inode votes with a cluster lock
 *
 * New in version 7:
 * 	- DLM join करोमुख्य includes the live nodemap
 *
 * New in version 6:
 * 	- DLM lockres remote refcount fixes.
 *
 * New in version 5:
 * 	- Network समयout checking protocol
 *
 * New in version 4:
 * 	- Remove i_generation from lock names क्रम better stat perक्रमmance.
 *
 * New in version 3:
 * 	- Replace dentry votes with a cluster lock
 *
 * New in version 2:
 * 	- full 64 bit i_size in the metadata lock lvbs
 * 	- पूर्णांकroduction of "rw" lock and pushing meta/data locking करोwn
 */
#घोषणा O2NET_PROTOCOL_VERSION 11ULL
काष्ठा o2net_handshake अणु
	__be64	protocol_version;
	__be64	connector_id;
	__be32  o2hb_heartbeat_समयout_ms;
	__be32  o2net_idle_समयout_ms;
	__be32  o2net_keepalive_delay_ms;
	__be32  o2net_reconnect_delay_ms;
पूर्ण;

काष्ठा o2net_node अणु
	/* this is never called from पूर्णांक/bh */
	spinlock_t			nn_lock;

	/* set the moment an sc is allocated and a connect is started */
	काष्ठा o2net_sock_container	*nn_sc;
	/* _valid is only set after the handshake passes and tx can happen */
	अचिन्हित			nn_sc_valid:1;
	/* अगर this is set tx just वापसs it */
	पूर्णांक				nn_persistent_error;
	/* It is only set to 1 after the idle समय out. */
	atomic_t			nn_समयout;

	/* thपढ़ोs रुकोing क्रम an sc to arrive रुको on the wq क्रम generation
	 * to increase.  it is increased when a connecting socket succeeds
	 * or fails or when an accepted socket is attached. */
	रुको_queue_head_t		nn_sc_wq;

	काष्ठा idr			nn_status_idr;
	काष्ठा list_head		nn_status_list;

	/* connects are attempted from when heartbeat comes up until either hb
	 * goes करोwn, the node is unconfigured, or a connect succeeds.
	 * connect_work is queued from set_nn_state both from hb up and from
	 * itself अगर a connect attempt fails and so can be self-arming.
	 * shutकरोwn is careful to first mark the nn such that no connects will
	 * be attempted beक्रमe canceling delayed connect work and flushing the
	 * queue. */
	काष्ठा delayed_work		nn_connect_work;
	अचिन्हित दीर्घ			nn_last_connect_attempt;

	/* this is queued as nodes come up and is canceled when a connection is
	 * established.  this expiring gives up on the node and errors out
	 * transmits */
	काष्ठा delayed_work		nn_connect_expired;

	/* after we give up on a socket we रुको a जबतक beक्रमe deciding
	 * that it is still heartbeating and that we should करो some
	 * quorum work */
	काष्ठा delayed_work		nn_still_up;
पूर्ण;

काष्ठा o2net_sock_container अणु
	काष्ठा kref		sc_kref;
	/* the next two are valid क्रम the lअगरe समय of the sc */
	काष्ठा socket		*sc_sock;
	काष्ठा o2nm_node	*sc_node;

	/* all of these sc work काष्ठाs hold refs on the sc जबतक they are
	 * queued.  they should not be able to ref a मुक्तd sc.  the tearकरोwn
	 * race is with o2net_wq deकाष्ठाion in o2net_stop_listening() */

	/* rx and connect work are generated from socket callbacks.  sc
	 * shutकरोwn हटाओs the callbacks and then flushes the work queue */
	काष्ठा work_काष्ठा	sc_rx_work;
	काष्ठा work_काष्ठा	sc_connect_work;
	/* shutकरोwn work is triggered in two ways.  the simple way is
	 * क्रम a code path calls ensure_shutकरोwn which माला_लो a lock, हटाओs
	 * the sc from the nn, and queues the work.  in this हाल the
	 * work is single-shot.  the work is also queued from a sock
	 * callback, though, and in this हाल the work will find the sc
	 * still on the nn and will call ensure_shutकरोwn itself.. this
	 * ends up triggering the shutकरोwn work again, though nothing
	 * will be करोne in that second iteration.  so work queue tearकरोwn
	 * has to be careful to हटाओ the sc from the nn beक्रमe रुकोing
	 * on the work queue so that the shutकरोwn work करोesn't हटाओ the
	 * sc and rearm itself.
	 */
	काष्ठा work_काष्ठा	sc_shutकरोwn_work;

	काष्ठा समयr_list	sc_idle_समयout;
	काष्ठा delayed_work	sc_keepalive_work;

	अचिन्हित		sc_handshake_ok:1;

	काष्ठा page 		*sc_page;
	माप_प्रकार			sc_page_off;

	/* original handlers क्रम the sockets */
	व्योम			(*sc_state_change)(काष्ठा sock *sk);
	व्योम			(*sc_data_पढ़ोy)(काष्ठा sock *sk);

	u32			sc_msg_key;
	u16			sc_msg_type;

#अगर_घोषित CONFIG_DEBUG_FS
	काष्ठा list_head        sc_net_debug_item;
	kसमय_प्रकार			sc_tv_समयr;
	kसमय_प्रकार			sc_tv_data_पढ़ोy;
	kसमय_प्रकार			sc_tv_advance_start;
	kसमय_प्रकार			sc_tv_advance_stop;
	kसमय_प्रकार			sc_tv_func_start;
	kसमय_प्रकार			sc_tv_func_stop;
#पूर्ण_अगर
#अगर_घोषित CONFIG_OCFS2_FS_STATS
	kसमय_प्रकार			sc_tv_acquiry_total;
	kसमय_प्रकार			sc_tv_send_total;
	kसमय_प्रकार			sc_tv_status_total;
	u32			sc_send_count;
	u32			sc_recv_count;
	kसमय_प्रकार			sc_tv_process_total;
#पूर्ण_अगर
	काष्ठा mutex		sc_send_lock;
पूर्ण;

काष्ठा o2net_msg_handler अणु
	काष्ठा rb_node		nh_node;
	u32			nh_max_len;
	u32			nh_msg_type;
	u32			nh_key;
	o2net_msg_handler_func	*nh_func;
	व्योम			*nh_func_data;
	o2net_post_msg_handler_func
				*nh_post_func;
	काष्ठा kref		nh_kref;
	काष्ठा list_head	nh_unरेजिस्टर_item;
पूर्ण;

क्रमागत o2net_प्रणाली_error अणु
	O2NET_ERR_NONE = 0,
	O2NET_ERR_NO_HNDLR,
	O2NET_ERR_OVERFLOW,
	O2NET_ERR_DIED,
	O2NET_ERR_MAX
पूर्ण;

काष्ठा o2net_status_रुको अणु
	क्रमागत o2net_प्रणाली_error	ns_sys_status;
	s32			ns_status;
	पूर्णांक			ns_id;
	रुको_queue_head_t	ns_wq;
	काष्ठा list_head	ns_node_item;
पूर्ण;

#अगर_घोषित CONFIG_DEBUG_FS
/* just क्रम state dumps */
काष्ठा o2net_send_tracking अणु
	काष्ठा list_head		st_net_debug_item;
	काष्ठा task_काष्ठा		*st_task;
	काष्ठा o2net_sock_container	*st_sc;
	u32				st_id;
	u32				st_msg_type;
	u32				st_msg_key;
	u8				st_node;
	kसमय_प्रकार				st_sock_समय;
	kसमय_प्रकार				st_send_समय;
	kसमय_प्रकार				st_status_समय;
पूर्ण;
#अन्यथा
काष्ठा o2net_send_tracking अणु
	u32	dummy;
पूर्ण;
#पूर्ण_अगर	/* CONFIG_DEBUG_FS */

#पूर्ण_अगर /* O2CLUSTER_TCP_INTERNAL_H */
