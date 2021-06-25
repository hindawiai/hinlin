<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 *  Shared Memory Communications over RDMA (SMC-R) and RoCE
 *
 *  Definitions क्रम the SMC module (socket related)
 *
 *  Copyright IBM Corp. 2016
 *
 *  Author(s):  Ursula Braun <ubraun@linux.vnet.ibm.com>
 */
#अगर_अघोषित __SMC_H
#घोषणा __SMC_H

#समावेश <linux/socket.h>
#समावेश <linux/types.h>
#समावेश <linux/compiler.h> /* __aligned */
#समावेश <net/sock.h>

#समावेश "smc_ib.h"

#घोषणा SMC_V1		1		/* SMC version V1 */
#घोषणा SMC_V2		2		/* SMC version V2 */
#घोषणा SMC_RELEASE	0

#घोषणा SMCPROTO_SMC		0	/* SMC protocol, IPv4 */
#घोषणा SMCPROTO_SMC6		1	/* SMC protocol, IPv6 */

#घोषणा SMC_MAX_ISM_DEVS	8	/* max # of proposed non-native ISM
					 * devices
					 */

#घोषणा SMC_MAX_HOSTNAME_LEN	32
#घोषणा SMC_MAX_EID_LEN		32

बाह्य काष्ठा proto smc_proto;
बाह्य काष्ठा proto smc_proto6;

#अगर_घोषित ATOMIC64_INIT
#घोषणा KERNEL_HAS_ATOMIC64
#पूर्ण_अगर

क्रमागत smc_state अणु		/* possible states of an SMC socket */
	SMC_ACTIVE	= 1,
	SMC_INIT	= 2,
	SMC_CLOSED	= 7,
	SMC_LISTEN	= 10,
	/* normal बंद */
	SMC_PEERCLOSEWAIT1	= 20,
	SMC_PEERCLOSEWAIT2	= 21,
	SMC_APPFINCLOSEWAIT	= 24,
	SMC_APPCLOSEWAIT1	= 22,
	SMC_APPCLOSEWAIT2	= 23,
	SMC_PEERFINCLOSEWAIT	= 25,
	/* abnormal बंद */
	SMC_PEERABORTWAIT	= 26,
	SMC_PROCESSABORT	= 27,
पूर्ण;

काष्ठा smc_link_group;

काष्ठा smc_wr_rx_hdr अणु	/* common prefix part of LLC and CDC to demultiplex */
	u8			type;
पूर्ण __aligned(1);

काष्ठा smc_cdc_conn_state_flags अणु
#अगर defined(__BIG_ENDIAN_BITFIELD)
	u8	peer_करोne_writing : 1;	/* Sending करोne indicator */
	u8	peer_conn_बंदd : 1;	/* Peer connection बंदd indicator */
	u8	peer_conn_पात : 1;	/* Abnormal बंद indicator */
	u8	reserved : 5;
#या_अगर defined(__LITTLE_ENDIAN_BITFIELD)
	u8	reserved : 5;
	u8	peer_conn_पात : 1;
	u8	peer_conn_बंदd : 1;
	u8	peer_करोne_writing : 1;
#पूर्ण_अगर
पूर्ण;

काष्ठा smc_cdc_producer_flags अणु
#अगर defined(__BIG_ENDIAN_BITFIELD)
	u8	ग_लिखो_blocked : 1;	/* Writing Blocked, no rx buf space */
	u8	urg_data_pending : 1;	/* Urgent Data Pending */
	u8	urg_data_present : 1;	/* Urgent Data Present */
	u8	cons_curs_upd_req : 1;	/* cursor update requested */
	u8	failover_validation : 1;/* message replay due to failover */
	u8	reserved : 3;
#या_अगर defined(__LITTLE_ENDIAN_BITFIELD)
	u8	reserved : 3;
	u8	failover_validation : 1;
	u8	cons_curs_upd_req : 1;
	u8	urg_data_present : 1;
	u8	urg_data_pending : 1;
	u8	ग_लिखो_blocked : 1;
#पूर्ण_अगर
पूर्ण;

/* in host byte order */
जोड़ smc_host_cursor अणु	/* SMC cursor - an offset in an RMBE */
	काष्ठा अणु
		u16	reserved;
		u16	wrap;		/* winकरोw wrap sequence number */
		u32	count;		/* cursor (= offset) part */
	पूर्ण;
#अगर_घोषित KERNEL_HAS_ATOMIC64
	atomic64_t		acurs;	/* क्रम atomic processing */
#अन्यथा
	u64			acurs;	/* क्रम atomic processing */
#पूर्ण_अगर
पूर्ण __aligned(8);

/* in host byte order, except क्रम flag bitfields in network byte order */
काष्ठा smc_host_cdc_msg अणु		/* Connection Data Control message */
	काष्ठा smc_wr_rx_hdr		common; /* .type = 0xFE */
	u8				len;	/* length = 44 */
	u16				seqno;	/* connection seq # */
	u32				token;	/* alert_token */
	जोड़ smc_host_cursor		prod;		/* producer cursor */
	जोड़ smc_host_cursor		cons;		/* consumer cursor,
							 * piggy backed "ack"
							 */
	काष्ठा smc_cdc_producer_flags	prod_flags;	/* conn. tx/rx status */
	काष्ठा smc_cdc_conn_state_flags	conn_state_flags; /* peer conn. status*/
	u8				reserved[18];
पूर्ण __aligned(8);

क्रमागत smc_urg_state अणु
	SMC_URG_VALID	= 1,			/* data present */
	SMC_URG_NOTYET	= 2,			/* data pending */
	SMC_URG_READ	= 3,			/* data was alपढ़ोy पढ़ो */
पूर्ण;

काष्ठा smc_connection अणु
	काष्ठा rb_node		alert_node;
	काष्ठा smc_link_group	*lgr;		/* link group of connection */
	काष्ठा smc_link		*lnk;		/* asचिन्हित SMC-R link */
	u32			alert_token_local; /* unique conn. id */
	u8			peer_rmbe_idx;	/* from tcp handshake */
	पूर्णांक			peer_rmbe_size;	/* size of peer rx buffer */
	atomic_t		peer_rmbe_space;/* reमुख्यing मुक्त bytes in peer
						 * rmbe
						 */
	पूर्णांक			rtoken_idx;	/* idx to peer RMB rkey/addr */

	काष्ठा smc_buf_desc	*sndbuf_desc;	/* send buffer descriptor */
	काष्ठा smc_buf_desc	*rmb_desc;	/* RMBE descriptor */
	पूर्णांक			rmbe_size_लघु;/* compressed notation */
	पूर्णांक			rmbe_update_limit;
						/* lower limit क्रम consumer
						 * cursor update
						 */

	काष्ठा smc_host_cdc_msg	local_tx_ctrl;	/* host byte order staging
						 * buffer क्रम CDC msg send
						 * .prod cf. TCP snd_nxt
						 * .cons cf. TCP sends ack
						 */
	जोड़ smc_host_cursor	local_tx_ctrl_fin;
						/* prod crsr - confirmed by peer
						 */
	जोड़ smc_host_cursor	tx_curs_prep;	/* tx - prepared data
						 * snd_max..wmem_alloc
						 */
	जोड़ smc_host_cursor	tx_curs_sent;	/* tx - sent data
						 * snd_nxt ?
						 */
	जोड़ smc_host_cursor	tx_curs_fin;	/* tx - confirmed by peer
						 * snd-wnd-begin ?
						 */
	atomic_t		sndbuf_space;	/* reमुख्यing space in sndbuf */
	u16			tx_cdc_seq;	/* sequence # क्रम CDC send */
	u16			tx_cdc_seq_fin;	/* sequence # - tx completed */
	spinlock_t		send_lock;	/* protect wr_sends */
	काष्ठा delayed_work	tx_work;	/* retry of smc_cdc_msg_send */
	u32			tx_off;		/* base offset in peer rmb */

	काष्ठा smc_host_cdc_msg	local_rx_ctrl;	/* filled during event_handl.
						 * .prod cf. TCP rcv_nxt
						 * .cons cf. TCP snd_una
						 */
	जोड़ smc_host_cursor	rx_curs_confirmed; /* confirmed to peer
						    * source of snd_una ?
						    */
	जोड़ smc_host_cursor	urg_curs;	/* poपूर्णांकs at urgent byte */
	क्रमागत smc_urg_state	urg_state;
	bool			urg_tx_pend;	/* urgent data staged */
	bool			urg_rx_skip_pend;
						/* indicate urgent oob data
						 * पढ़ो, but previous regular
						 * data still pending
						 */
	अक्षर			urg_rx_byte;	/* urgent byte */
	atomic_t		bytes_to_rcv;	/* arrived data,
						 * not yet received
						 */
	atomic_t		splice_pending;	/* number of spliced bytes
						 * pending processing
						 */
#अगर_अघोषित KERNEL_HAS_ATOMIC64
	spinlock_t		acurs_lock;	/* protect cursors */
#पूर्ण_अगर
	काष्ठा work_काष्ठा	बंद_work;	/* peer sent some closing */
	काष्ठा work_काष्ठा	पात_work;	/* पात the connection */
	काष्ठा tasklet_काष्ठा	rx_tsklet;	/* Receiver tasklet क्रम SMC-D */
	u8			rx_off;		/* receive offset:
						 * 0 क्रम SMC-R, 32 क्रम SMC-D
						 */
	u64			peer_token;	/* SMC-D token of peer */
	u8			समाप्तed : 1;	/* abnormal termination */
	u8			out_of_sync : 1; /* out of sync with peer */
पूर्ण;

काष्ठा smc_sock अणु				/* smc sock container */
	काष्ठा sock		sk;
	काष्ठा socket		*clcsock;	/* पूर्णांकernal tcp socket */
	व्योम			(*clcsk_data_पढ़ोy)(काष्ठा sock *sk);
						/* original data_पढ़ोy fct. **/
	काष्ठा smc_connection	conn;		/* smc connection */
	काष्ठा smc_sock		*listen_smc;	/* listen parent */
	काष्ठा work_काष्ठा	connect_work;	/* handle non-blocking connect*/
	काष्ठा work_काष्ठा	tcp_listen_work;/* handle tcp socket accepts */
	काष्ठा work_काष्ठा	smc_listen_work;/* prepare new accept socket */
	काष्ठा list_head	accept_q;	/* sockets to be accepted */
	spinlock_t		accept_q_lock;	/* protects accept_q */
	bool			use_fallback;	/* fallback to tcp */
	पूर्णांक			fallback_rsn;	/* reason क्रम fallback */
	u32			peer_diagnosis; /* decline reason from peer */
	पूर्णांक			sockopt_defer_accept;
						/* sockopt TCP_DEFER_ACCEPT
						 * value
						 */
	u8			रुको_बंद_tx_prepared : 1;
						/* shutकरोwn wr or बंद
						 * started, रुकोing क्रम unsent
						 * data to be sent
						 */
	u8			connect_nonblock : 1;
						/* non-blocking connect in
						 * flight
						 */
	काष्ठा mutex            clcsock_release_lock;
						/* protects clcsock of a listen
						 * socket
						 * */
पूर्ण;

अटल अंतरभूत काष्ठा smc_sock *smc_sk(स्थिर काष्ठा sock *sk)
अणु
	वापस (काष्ठा smc_sock *)sk;
पूर्ण

बाह्य काष्ठा workqueue_काष्ठा	*smc_hs_wq;	/* wq क्रम handshake work */
बाह्य काष्ठा workqueue_काष्ठा	*smc_बंद_wq;	/* wq क्रम बंद work */

#घोषणा SMC_SYSTEMID_LEN		8

बाह्य u8	local_प्रणालीid[SMC_SYSTEMID_LEN]; /* unique प्रणाली identअगरier */

#घोषणा ntohll(x) be64_to_cpu(x)
#घोषणा htonll(x) cpu_to_be64(x)

/* convert an u32 value पूर्णांकo network byte order, store it पूर्णांकo a 3 byte field */
अटल अंतरभूत व्योम hton24(u8 *net, u32 host)
अणु
	__be32 t;

	t = cpu_to_be32(host);
	स_नकल(net, ((u8 *)&t) + 1, 3);
पूर्ण

/* convert a received 3 byte field पूर्णांकo host byte order*/
अटल अंतरभूत u32 ntoh24(u8 *net)
अणु
	__be32 t = 0;

	स_नकल(((u8 *)&t) + 1, net, 3);
	वापस be32_to_cpu(t);
पूर्ण

#अगर_घोषित CONFIG_XFRM
अटल अंतरभूत bool using_ipsec(काष्ठा smc_sock *smc)
अणु
	वापस (smc->clcsock->sk->sk_policy[0] ||
		smc->clcsock->sk->sk_policy[1]) ? true : false;
पूर्ण
#अन्यथा
अटल अंतरभूत bool using_ipsec(काष्ठा smc_sock *smc)
अणु
	वापस false;
पूर्ण
#पूर्ण_अगर

काष्ठा sock *smc_accept_dequeue(काष्ठा sock *parent, काष्ठा socket *new_sock);
व्योम smc_बंद_non_accepted(काष्ठा sock *sk);

#पूर्ण_अगर	/* __SMC_H */
