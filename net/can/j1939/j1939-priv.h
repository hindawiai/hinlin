<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
// Copyright (c) 2010-2011 EIA Electronics,
//                         Kurt Van Dijck <kurt.van.dijck@eia.be>
// Copyright (c) 2017-2019 Pengutronix,
//                         Marc Kleine-Budde <kernel@pengutronix.de>
// Copyright (c) 2017-2019 Pengutronix,
//                         Oleksij Rempel <kernel@pengutronix.de>

#अगर_अघोषित _J1939_PRIV_H_
#घोषणा _J1939_PRIV_H_

#समावेश <linux/can/j1939.h>
#समावेश <net/sock.h>

/* Timeout to receive the पात संकेत over loop back. In हाल CAN
 * bus is खोलो, the समयout should be triggered.
 */
#घोषणा J1939_XTP_ABORT_TIMEOUT_MS 500
#घोषणा J1939_SIMPLE_ECHO_TIMEOUT_MS (10 * 1000)

काष्ठा j1939_session;
क्रमागत j1939_sk_errqueue_type अणु
	J1939_ERRQUEUE_ACK,
	J1939_ERRQUEUE_SCHED,
	J1939_ERRQUEUE_ABORT,
पूर्ण;

/* j1939 devices */
काष्ठा j1939_ecu अणु
	काष्ठा list_head list;
	name_t name;
	u8 addr;

	/* indicates that this ecu successfully claimed @sa as its address */
	काष्ठा hrसमयr ac_समयr;
	काष्ठा kref kref;
	काष्ठा j1939_priv *priv;

	/* count users, to help transport protocol decide क्रम पूर्णांकeraction */
	पूर्णांक nusers;
पूर्ण;

काष्ठा j1939_priv अणु
	काष्ठा list_head ecus;
	/* local list entry in priv
	 * These allow irq (& softirq) context lookups on j1939 devices
	 * This approach (separate lists) is करोne as the other 2 alternatives
	 * are not easier or even wrong
	 * 1) using the pure kobject methods involves mutexes, which are not
	 *    allowed in irq context.
	 * 2) duplicating data काष्ठाures would require a lot of synchronization
	 *    code
	 * usage:
	 */

	/* segments need a lock to protect the above list */
	rwlock_t lock;

	काष्ठा net_device *ndev;

	/* list of 256 ecu ptrs, that cache the claimed addresses.
	 * also रक्षित by the above lock
	 */
	काष्ठा j1939_addr_ent अणु
		काष्ठा j1939_ecu *ecu;
		/* count users, to help transport protocol */
		पूर्णांक nusers;
	पूर्ण ents[256];

	काष्ठा kref kref;

	/* List of active sessions to prevent start of conflicting
	 * one.
	 *
	 * Do not start two sessions of same type, addresses and
	 * direction.
	 */
	काष्ठा list_head active_session_list;

	/* protects active_session_list */
	spinlock_t active_session_list_lock;

	अचिन्हित पूर्णांक tp_max_packet_size;

	/* lock क्रम j1939_socks list */
	spinlock_t j1939_socks_lock;
	काष्ठा list_head j1939_socks;

	काष्ठा kref rx_kref;
पूर्ण;

व्योम j1939_ecu_put(काष्ठा j1939_ecu *ecu);

/* keep the cache of what is local */
पूर्णांक j1939_local_ecu_get(काष्ठा j1939_priv *priv, name_t name, u8 sa);
व्योम j1939_local_ecu_put(काष्ठा j1939_priv *priv, name_t name, u8 sa);

अटल अंतरभूत bool j1939_address_is_unicast(u8 addr)
अणु
	वापस addr <= J1939_MAX_UNICAST_ADDR;
पूर्ण

अटल अंतरभूत bool j1939_address_is_idle(u8 addr)
अणु
	वापस addr == J1939_IDLE_ADDR;
पूर्ण

अटल अंतरभूत bool j1939_address_is_valid(u8 addr)
अणु
	वापस addr != J1939_NO_ADDR;
पूर्ण

अटल अंतरभूत bool j1939_pgn_is_pdu1(pgn_t pgn)
अणु
	/* ignore dp & res bits क्रम this */
	वापस (pgn & 0xff00) < 0xf000;
पूर्ण

/* utility to correctly unmap an ECU */
व्योम j1939_ecu_unmap_locked(काष्ठा j1939_ecu *ecu);
व्योम j1939_ecu_unmap(काष्ठा j1939_ecu *ecu);

u8 j1939_name_to_addr(काष्ठा j1939_priv *priv, name_t name);
काष्ठा j1939_ecu *j1939_ecu_find_by_addr_locked(काष्ठा j1939_priv *priv,
						u8 addr);
काष्ठा j1939_ecu *j1939_ecu_get_by_addr(काष्ठा j1939_priv *priv, u8 addr);
काष्ठा j1939_ecu *j1939_ecu_get_by_addr_locked(काष्ठा j1939_priv *priv,
					       u8 addr);
काष्ठा j1939_ecu *j1939_ecu_get_by_name(काष्ठा j1939_priv *priv, name_t name);
काष्ठा j1939_ecu *j1939_ecu_get_by_name_locked(काष्ठा j1939_priv *priv,
					       name_t name);

क्रमागत j1939_transfer_type अणु
	J1939_TP,
	J1939_ETP,
	J1939_SIMPLE,
पूर्ण;

काष्ठा j1939_addr अणु
	name_t src_name;
	name_t dst_name;
	pgn_t pgn;

	u8 sa;
	u8 da;

	u8 type;
पूर्ण;

/* control buffer of the sk_buff */
काष्ठा j1939_sk_buff_cb अणु
	/* Offset in bytes within one ETP session */
	u32 offset;

	/* क्रम tx, MSG_SYN will be used to sync on sockets */
	u32 msg_flags;
	u32 tskey;

	काष्ठा j1939_addr addr;

	/* Flags क्रम quick lookups during skb processing.
	 * These are set in the receive path only.
	 */
#घोषणा J1939_ECU_LOCAL_SRC BIT(0)
#घोषणा J1939_ECU_LOCAL_DST BIT(1)
	u8 flags;

	priority_t priority;
पूर्ण;

अटल अंतरभूत
काष्ठा j1939_sk_buff_cb *j1939_skb_to_cb(स्थिर काष्ठा sk_buff *skb)
अणु
	BUILD_BUG_ON(माप(काष्ठा j1939_sk_buff_cb) > माप(skb->cb));

	वापस (काष्ठा j1939_sk_buff_cb *)skb->cb;
पूर्ण

पूर्णांक j1939_send_one(काष्ठा j1939_priv *priv, काष्ठा sk_buff *skb);
व्योम j1939_sk_recv(काष्ठा j1939_priv *priv, काष्ठा sk_buff *skb);
bool j1939_sk_recv_match(काष्ठा j1939_priv *priv,
			 काष्ठा j1939_sk_buff_cb *skcb);
व्योम j1939_sk_send_loop_पात(काष्ठा sock *sk, पूर्णांक err);
व्योम j1939_sk_errqueue(काष्ठा j1939_session *session,
		       क्रमागत j1939_sk_errqueue_type type);
व्योम j1939_sk_queue_activate_next(काष्ठा j1939_session *session);

/* stack entries */
काष्ठा j1939_session *j1939_tp_send(काष्ठा j1939_priv *priv,
				    काष्ठा sk_buff *skb, माप_प्रकार size);
पूर्णांक j1939_tp_recv(काष्ठा j1939_priv *priv, काष्ठा sk_buff *skb);
पूर्णांक j1939_ac_fixup(काष्ठा j1939_priv *priv, काष्ठा sk_buff *skb);
व्योम j1939_ac_recv(काष्ठा j1939_priv *priv, काष्ठा sk_buff *skb);
व्योम j1939_simple_recv(काष्ठा j1939_priv *priv, काष्ठा sk_buff *skb);

/* network management */
काष्ठा j1939_ecu *j1939_ecu_create_locked(काष्ठा j1939_priv *priv, name_t name);

व्योम j1939_ecu_समयr_start(काष्ठा j1939_ecu *ecu);
व्योम j1939_ecu_समयr_cancel(काष्ठा j1939_ecu *ecu);
व्योम j1939_ecu_unmap_all(काष्ठा j1939_priv *priv);

काष्ठा j1939_priv *j1939_netdev_start(काष्ठा net_device *ndev);
व्योम j1939_netdev_stop(काष्ठा j1939_priv *priv);

व्योम j1939_priv_put(काष्ठा j1939_priv *priv);
व्योम j1939_priv_get(काष्ठा j1939_priv *priv);

/* notअगरy/alert all j1939 sockets bound to अगरindex */
व्योम j1939_sk_netdev_event_netकरोwn(काष्ठा j1939_priv *priv);
पूर्णांक j1939_cancel_active_session(काष्ठा j1939_priv *priv, काष्ठा sock *sk);
व्योम j1939_tp_init(काष्ठा j1939_priv *priv);

/* decrement pending skb क्रम a j1939 socket */
व्योम j1939_sock_pending_del(काष्ठा sock *sk);

क्रमागत j1939_session_state अणु
	J1939_SESSION_NEW,
	J1939_SESSION_ACTIVE,
	/* रुकोing क्रम पात संकेत on the bus */
	J1939_SESSION_WAITING_ABORT,
	J1939_SESSION_ACTIVE_MAX,
	J1939_SESSION_DONE,
पूर्ण;

काष्ठा j1939_session अणु
	काष्ठा j1939_priv *priv;
	काष्ठा list_head active_session_list_entry;
	काष्ठा list_head sk_session_queue_entry;
	काष्ठा kref kref;
	काष्ठा sock *sk;

	/* अगरindex, src, dst, pgn define the session block
	 * the are _never_ modअगरied after insertion in the list
	 * this decreases locking problems a _lot_
	 */
	काष्ठा j1939_sk_buff_cb skcb;
	काष्ठा sk_buff_head skb_queue;

	/* all tx related stuff (last_txcmd, pkt.tx)
	 * is रक्षित (modअगरied only) with the txसमयr hrसमयr
	 * 'total' & 'block' are never changed,
	 * last_cmd, last & block are रक्षित by ->lock
	 * this means that the tx may run after cts is received that should
	 * have stopped tx, but this समय discrepancy is never aव्योमed anyhow
	 */
	u8 last_cmd, last_txcmd;
	bool transmission;
	bool extd;
	/* Total message size, number of bytes */
	अचिन्हित पूर्णांक total_message_size;
	/* Total number of bytes queue from socket to the session */
	अचिन्हित पूर्णांक total_queued_size;
	अचिन्हित पूर्णांक tx_retry;

	पूर्णांक err;
	u32 tskey;
	क्रमागत j1939_session_state state;

	/* Packets counters क्रम a (extended) transfer session. The packet is
	 * maximal of 7 bytes.
	 */
	काष्ठा अणु
		/* total - total number of packets क्रम this session */
		अचिन्हित पूर्णांक total;
		/* last - last packet of a transfer block after which
		 * responder should send ETP.CM_CTS and originator
		 * ETP.CM_DPO
		 */
		अचिन्हित पूर्णांक last;
		/* tx - number of packets send by originator node.
		 * this counter can be set back अगर responder node
		 * didn't received all packets send by originator.
		 */
		अचिन्हित पूर्णांक tx;
		अचिन्हित पूर्णांक tx_acked;
		/* rx - number of packets received */
		अचिन्हित पूर्णांक rx;
		/* block - amount of packets expected in one block */
		अचिन्हित पूर्णांक block;
		/* dpo - ETP.CM_DPO, Data Packet Offset */
		अचिन्हित पूर्णांक dpo;
	पूर्ण pkt;
	काष्ठा hrसमयr txसमयr, rxसमयr;
पूर्ण;

काष्ठा j1939_sock अणु
	काष्ठा sock sk; /* must be first to skip with स_रखो */
	काष्ठा j1939_priv *priv;
	काष्ठा list_head list;

#घोषणा J1939_SOCK_BOUND BIT(0)
#घोषणा J1939_SOCK_CONNECTED BIT(1)
#घोषणा J1939_SOCK_PROMISC BIT(2)
#घोषणा J1939_SOCK_ERRQUEUE BIT(3)
	पूर्णांक state;

	पूर्णांक अगरindex;
	काष्ठा j1939_addr addr;
	काष्ठा j1939_filter *filters;
	पूर्णांक nfilters;
	pgn_t pgn_rx_filter;

	/* j1939 may emit equal PGN (!= equal CAN-id's) out of order
	 * when transport protocol comes in.
	 * To allow emitting in order, keep a 'pending' nr. of packets
	 */
	atomic_t skb_pending;
	रुको_queue_head_t रुकोq;

	/* lock क्रम the sk_session_queue list */
	spinlock_t sk_session_queue_lock;
	काष्ठा list_head sk_session_queue;
पूर्ण;

अटल अंतरभूत काष्ठा j1939_sock *j1939_sk(स्थिर काष्ठा sock *sk)
अणु
	वापस container_of(sk, काष्ठा j1939_sock, sk);
पूर्ण

व्योम j1939_session_get(काष्ठा j1939_session *session);
व्योम j1939_session_put(काष्ठा j1939_session *session);
व्योम j1939_session_skb_queue(काष्ठा j1939_session *session,
			     काष्ठा sk_buff *skb);
पूर्णांक j1939_session_activate(काष्ठा j1939_session *session);
व्योम j1939_tp_schedule_txसमयr(काष्ठा j1939_session *session, पूर्णांक msec);
व्योम j1939_session_समयrs_cancel(काष्ठा j1939_session *session);

#घोषणा J1939_MAX_TP_PACKET_SIZE (7 * 0xff)
#घोषणा J1939_MAX_ETP_PACKET_SIZE (7 * 0x00ffffff)

#घोषणा J1939_REGULAR 0
#घोषणा J1939_EXTENDED 1

/* CAN protocol */
बाह्य स्थिर काष्ठा can_proto j1939_can_proto;

#पूर्ण_अगर /* _J1939_PRIV_H_ */
