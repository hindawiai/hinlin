<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * INET		An implementation of the TCP/IP protocol suite क्रम the LINUX
 *		operating प्रणाली.  INET is implemented using the  BSD Socket
 *		पूर्णांकerface as the means of communication with the user level.
 *
 *		Definitions क्रम the TCP protocol.
 *
 * Version:	@(#)tcp.h	1.0.2	04/28/93
 *
 * Author:	Fred N. van Kempen, <waltje@uWalt.NL.Mugnet.ORG>
 */
#अगर_अघोषित _LINUX_TCP_H
#घोषणा _LINUX_TCP_H


#समावेश <linux/skbuff.h>
#समावेश <linux/win_minmax.h>
#समावेश <net/sock.h>
#समावेश <net/inet_connection_sock.h>
#समावेश <net/inet_समयरुको_sock.h>
#समावेश <uapi/linux/tcp.h>

अटल अंतरभूत काष्ठा tcphdr *tcp_hdr(स्थिर काष्ठा sk_buff *skb)
अणु
	वापस (काष्ठा tcphdr *)skb_transport_header(skb);
पूर्ण

अटल अंतरभूत अचिन्हित पूर्णांक __tcp_hdrlen(स्थिर काष्ठा tcphdr *th)
अणु
	वापस th->करोff * 4;
पूर्ण

अटल अंतरभूत अचिन्हित पूर्णांक tcp_hdrlen(स्थिर काष्ठा sk_buff *skb)
अणु
	वापस __tcp_hdrlen(tcp_hdr(skb));
पूर्ण

अटल अंतरभूत काष्ठा tcphdr *inner_tcp_hdr(स्थिर काष्ठा sk_buff *skb)
अणु
	वापस (काष्ठा tcphdr *)skb_inner_transport_header(skb);
पूर्ण

अटल अंतरभूत अचिन्हित पूर्णांक inner_tcp_hdrlen(स्थिर काष्ठा sk_buff *skb)
अणु
	वापस inner_tcp_hdr(skb)->करोff * 4;
पूर्ण

अटल अंतरभूत अचिन्हित पूर्णांक tcp_optlen(स्थिर काष्ठा sk_buff *skb)
अणु
	वापस (tcp_hdr(skb)->करोff - 5) * 4;
पूर्ण

/* TCP Fast Open */
#घोषणा TCP_FASTOPEN_COOKIE_MIN	4	/* Min Fast Open Cookie size in bytes */
#घोषणा TCP_FASTOPEN_COOKIE_MAX	16	/* Max Fast Open Cookie size in bytes */
#घोषणा TCP_FASTOPEN_COOKIE_SIZE 8	/* the size employed by this impl. */

/* TCP Fast Open Cookie as stored in memory */
काष्ठा tcp_fastखोलो_cookie अणु
	__le64	val[DIV_ROUND_UP(TCP_FASTOPEN_COOKIE_MAX, माप(u64))];
	s8	len;
	bool	exp;	/* In RFC6994 experimental option क्रमmat */
पूर्ण;

/* This defines a selective acknowledgement block. */
काष्ठा tcp_sack_block_wire अणु
	__be32	start_seq;
	__be32	end_seq;
पूर्ण;

काष्ठा tcp_sack_block अणु
	u32	start_seq;
	u32	end_seq;
पूर्ण;

/*These are used to set the sack_ok field in काष्ठा tcp_options_received */
#घोषणा TCP_SACK_SEEN     (1 << 0)   /*1 = peer is SACK capable, */
#घोषणा TCP_DSACK_SEEN    (1 << 2)   /*1 = DSACK was received from peer*/

काष्ठा tcp_options_received अणु
/*	PAWS/RTTM data	*/
	पूर्णांक	ts_recent_stamp;/* Time we stored ts_recent (क्रम aging) */
	u32	ts_recent;	/* Time stamp to echo next		*/
	u32	rcv_tsval;	/* Time stamp value             	*/
	u32	rcv_tsecr;	/* Time stamp echo reply        	*/
	u16 	saw_tstamp : 1,	/* Saw TIMESTAMP on last packet		*/
		tstamp_ok : 1,	/* TIMESTAMP seen on SYN packet		*/
		dsack : 1,	/* D-SACK is scheduled			*/
		wscale_ok : 1,	/* Wscale seen on SYN packet		*/
		sack_ok : 3,	/* SACK seen on SYN packet		*/
		smc_ok : 1,	/* SMC seen on SYN packet		*/
		snd_wscale : 4,	/* Winकरोw scaling received from sender	*/
		rcv_wscale : 4;	/* Winकरोw scaling to send to receiver	*/
	u8	saw_unknown:1,	/* Received unknown option		*/
		unused:7;
	u8	num_sacks;	/* Number of SACK blocks		*/
	u16	user_mss;	/* mss requested by user in ioctl	*/
	u16	mss_clamp;	/* Maximal mss, negotiated at connection setup */
पूर्ण;

अटल अंतरभूत व्योम tcp_clear_options(काष्ठा tcp_options_received *rx_opt)
अणु
	rx_opt->tstamp_ok = rx_opt->sack_ok = 0;
	rx_opt->wscale_ok = rx_opt->snd_wscale = 0;
#अगर IS_ENABLED(CONFIG_SMC)
	rx_opt->smc_ok = 0;
#पूर्ण_अगर
पूर्ण

/* This is the max number of SACKS that we'll generate and process. It's safe
 * to increase this, although since:
 *   size = TCPOLEN_SACK_BASE_ALIGNED (4) + n * TCPOLEN_SACK_PERBLOCK (8)
 * only four options will fit in a standard TCP header */
#घोषणा TCP_NUM_SACKS 4

काष्ठा tcp_request_sock_ops;

काष्ठा tcp_request_sock अणु
	काष्ठा inet_request_sock 	req;
	स्थिर काष्ठा tcp_request_sock_ops *af_specअगरic;
	u64				snt_synack; /* first SYNACK sent समय */
	bool				tfo_listener;
	bool				is_mptcp;
#अगर IS_ENABLED(CONFIG_MPTCP)
	bool				drop_req;
#पूर्ण_अगर
	u32				txhash;
	u32				rcv_isn;
	u32				snt_isn;
	u32				ts_off;
	u32				last_oow_ack_समय; /* last SYNACK */
	u32				rcv_nxt; /* the ack # by SYNACK. For
						  * FastOpen it's the seq#
						  * after data-in-SYN.
						  */
	u8				syn_tos;
पूर्ण;

अटल अंतरभूत काष्ठा tcp_request_sock *tcp_rsk(स्थिर काष्ठा request_sock *req)
अणु
	वापस (काष्ठा tcp_request_sock *)req;
पूर्ण

काष्ठा tcp_sock अणु
	/* inet_connection_sock has to be the first member of tcp_sock */
	काष्ठा inet_connection_sock	inet_conn;
	u16	tcp_header_len;	/* Bytes of tcp header to send		*/
	u16	gso_segs;	/* Max number of segs per GSO packet	*/

/*
 *	Header prediction flags
 *	0x5?10 << 16 + snd_wnd in net byte order
 */
	__be32	pred_flags;

/*
 *	RFC793 variables by their proper names. This means you can
 *	पढ़ो the code and the spec side by side (and laugh ...)
 *	See RFC793 and RFC1122. The RFC ग_लिखोs these in capitals.
 */
	u64	bytes_received;	/* RFC4898 tcpEStatsAppHCThruOctetsReceived
				 * sum(delta(rcv_nxt)), or how many bytes
				 * were acked.
				 */
	u32	segs_in;	/* RFC4898 tcpEStatsPerfSegsIn
				 * total number of segments in.
				 */
	u32	data_segs_in;	/* RFC4898 tcpEStatsPerfDataSegsIn
				 * total number of data segments in.
				 */
 	u32	rcv_nxt;	/* What we want to receive next 	*/
	u32	copied_seq;	/* Head of yet unपढ़ो data		*/
	u32	rcv_wup;	/* rcv_nxt on last winकरोw update sent	*/
 	u32	snd_nxt;	/* Next sequence we send		*/
	u32	segs_out;	/* RFC4898 tcpEStatsPerfSegsOut
				 * The total number of segments sent.
				 */
	u32	data_segs_out;	/* RFC4898 tcpEStatsPerfDataSegsOut
				 * total number of data segments sent.
				 */
	u64	bytes_sent;	/* RFC4898 tcpEStatsPerfHCDataOctetsOut
				 * total number of data bytes sent.
				 */
	u64	bytes_acked;	/* RFC4898 tcpEStatsAppHCThruOctetsAcked
				 * sum(delta(snd_una)), or how many bytes
				 * were acked.
				 */
	u32	dsack_dups;	/* RFC4898 tcpEStatsStackDSACKDups
				 * total number of DSACK blocks received
				 */
 	u32	snd_una;	/* First byte we want an ack क्रम	*/
 	u32	snd_sml;	/* Last byte of the most recently transmitted small packet */
	u32	rcv_tstamp;	/* बारtamp of last received ACK (क्रम keepalives) */
	u32	lsndसमय;	/* बारtamp of last sent data packet (क्रम restart winकरोw) */
	u32	last_oow_ack_समय;  /* बारtamp of last out-of-winकरोw ACK */
	u32	compressed_ack_rcv_nxt;

	u32	tsoffset;	/* बारtamp offset */

	काष्ठा list_head tsq_node; /* anchor in tsq_tasklet.head list */
	काष्ठा list_head tsorted_sent_queue; /* समय-sorted sent but un-SACKed skbs */

	u32	snd_wl1;	/* Sequence क्रम winकरोw update		*/
	u32	snd_wnd;	/* The winकरोw we expect to receive	*/
	u32	max_winकरोw;	/* Maximal winकरोw ever seen from peer	*/
	u32	mss_cache;	/* Cached effective mss, not including SACKS */

	u32	winकरोw_clamp;	/* Maximal winकरोw to advertise		*/
	u32	rcv_ssthresh;	/* Current winकरोw clamp			*/

	/* Inक्रमmation of the most recently (s)acked skb */
	काष्ठा tcp_rack अणु
		u64 mstamp; /* (Re)sent समय of the skb */
		u32 rtt_us;  /* Associated RTT */
		u32 end_seq; /* Ending TCP sequence of the skb */
		u32 last_delivered; /* tp->delivered at last reo_wnd adj */
		u8 reo_wnd_steps;   /* Allowed reordering winकरोw */
#घोषणा TCP_RACK_RECOVERY_THRESH 16
		u8 reo_wnd_persist:5, /* No. of recovery since last adj */
		   dsack_seen:1, /* Whether DSACK seen after last adj */
		   advanced:1;	 /* mstamp advanced since last lost marking */
	पूर्ण rack;
	u16	advmss;		/* Advertised MSS			*/
	u8	compressed_ack;
	u8	dup_ack_counter:2,
		tlp_retrans:1,	/* TLP is a retransmission */
		unused:5;
	u32	chrono_start;	/* Start समय in jअगरfies of a TCP chrono */
	u32	chrono_stat[3];	/* Time in jअगरfies क्रम chrono_stat stats */
	u8	chrono_type:2,	/* current chronograph type */
		rate_app_limited:1,  /* rate_अणुdelivered,पूर्णांकerval_usपूर्ण limited? */
		fastखोलो_connect:1, /* FASTOPEN_CONNECT sockopt */
		fastखोलो_no_cookie:1, /* Allow send/recv SYN+data without a cookie */
		is_sack_reneg:1,    /* in recovery from loss with SACK reneg? */
		fastखोलो_client_fail:2; /* reason why fastखोलो failed */
	u8	nonagle     : 4,/* Disable Nagle algorithm?             */
		thin_lto    : 1,/* Use linear समयouts क्रम thin streams */
		recvmsg_inq : 1,/* Indicate # of bytes in queue upon recvmsg */
		repair      : 1,
		frto        : 1;/* F-RTO (RFC5682) activated in CA_Loss */
	u8	repair_queue;
	u8	save_syn:2,	/* Save headers of SYN packet */
		syn_data:1,	/* SYN includes data */
		syn_fastखोलो:1,	/* SYN includes Fast Open option */
		syn_fastखोलो_exp:1,/* SYN includes Fast Open exp. option */
		syn_fastखोलो_ch:1, /* Active TFO re-enabling probe */
		syn_data_acked:1,/* data in SYN is acked by SYN-ACK */
		is_cwnd_limited:1;/* क्रमward progress limited by snd_cwnd? */
	u32	tlp_high_seq;	/* snd_nxt at the समय of TLP */

	u32	tcp_tx_delay;	/* delay (in usec) added to TX packets */
	u64	tcp_wstamp_ns;	/* departure समय क्रम next sent data packet */
	u64	tcp_घड़ी_cache; /* cache last tcp_घड़ी_ns() (see tcp_mstamp_refresh()) */

/* RTT measurement */
	u64	tcp_mstamp;	/* most recent packet received/sent */
	u32	srtt_us;	/* smoothed round trip समय << 3 in usecs */
	u32	mdev_us;	/* medium deviation			*/
	u32	mdev_max_us;	/* maximal mdev क्रम the last rtt period	*/
	u32	rttvar_us;	/* smoothed mdev_max			*/
	u32	rtt_seq;	/* sequence number to update rttvar	*/
	काष्ठा  minmax rtt_min;

	u32	packets_out;	/* Packets which are "in flight"	*/
	u32	retrans_out;	/* Retransmitted packets out		*/
	u32	max_packets_out;  /* max packets_out in last winकरोw */
	u32	max_packets_seq;  /* right edge of max_packets_out flight */

	u16	urg_data;	/* Saved octet of OOB data and control flags */
	u8	ecn_flags;	/* ECN status bits.			*/
	u8	keepalive_probes; /* num of allowed keep alive probes	*/
	u32	reordering;	/* Packet reordering metric.		*/
	u32	reord_seen;	/* number of data packet reordering events */
	u32	snd_up;		/* Urgent poपूर्णांकer		*/

/*
 *      Options received (usually on last packet, some only on SYN packets).
 */
	काष्ठा tcp_options_received rx_opt;

/*
 *	Slow start and congestion control (see also Nagle, and Karn & Partridge)
 */
 	u32	snd_ssthresh;	/* Slow start size threshold		*/
 	u32	snd_cwnd;	/* Sending congestion winकरोw		*/
	u32	snd_cwnd_cnt;	/* Linear increase counter		*/
	u32	snd_cwnd_clamp; /* Do not allow snd_cwnd to grow above this */
	u32	snd_cwnd_used;
	u32	snd_cwnd_stamp;
	u32	prior_cwnd;	/* cwnd right beक्रमe starting loss recovery */
	u32	prr_delivered;	/* Number of newly delivered packets to
				 * receiver in Recovery. */
	u32	prr_out;	/* Total number of pkts sent during Recovery. */
	u32	delivered;	/* Total data packets delivered incl. rexmits */
	u32	delivered_ce;	/* Like the above but only ECE marked packets */
	u32	lost;		/* Total data packets lost incl. rexmits */
	u32	app_limited;	/* limited until "delivered" reaches this val */
	u64	first_tx_mstamp;  /* start of winकरोw send phase */
	u64	delivered_mstamp; /* समय we reached "delivered" */
	u32	rate_delivered;    /* saved rate sample: packets delivered */
	u32	rate_पूर्णांकerval_us;  /* saved rate sample: समय elapsed */

 	u32	rcv_wnd;	/* Current receiver winकरोw		*/
	u32	ग_लिखो_seq;	/* Tail(+1) of data held in tcp send buffer */
	u32	notsent_lowat;	/* TCP_NOTSENT_LOWAT */
	u32	pushed_seq;	/* Last pushed seq, required to talk to winकरोws */
	u32	lost_out;	/* Lost packets			*/
	u32	sacked_out;	/* SACK'd packets			*/

	काष्ठा hrसमयr	pacing_समयr;
	काष्ठा hrसमयr	compressed_ack_समयr;

	/* from STCP, retrans queue hपूर्णांकing */
	काष्ठा sk_buff* lost_skb_hपूर्णांक;
	काष्ठा sk_buff *retransmit_skb_hपूर्णांक;

	/* OOO segments go in this rbtree. Socket lock must be held. */
	काष्ठा rb_root	out_of_order_queue;
	काष्ठा sk_buff	*ooo_last_skb; /* cache rb_last(out_of_order_queue) */

	/* SACKs data, these 2 need to be together (see tcp_options_ग_लिखो) */
	काष्ठा tcp_sack_block duplicate_sack[1]; /* D-SACK block */
	काष्ठा tcp_sack_block selective_acks[4]; /* The SACKS themselves*/

	काष्ठा tcp_sack_block recv_sack_cache[4];

	काष्ठा sk_buff *highest_sack;   /* skb just after the highest
					 * skb with SACKed bit set
					 * (validity guaranteed only अगर
					 * sacked_out > 0)
					 */

	पूर्णांक     lost_cnt_hपूर्णांक;

	u32	prior_ssthresh; /* ssthresh saved at recovery start	*/
	u32	high_seq;	/* snd_nxt at onset of congestion	*/

	u32	retrans_stamp;	/* Timestamp of the last retransmit,
				 * also used in SYN-SENT to remember stamp of
				 * the first SYN. */
	u32	unकरो_marker;	/* snd_una upon a new recovery episode. */
	पूर्णांक	unकरो_retrans;	/* number of unकरोable retransmissions. */
	u64	bytes_retrans;	/* RFC4898 tcpEStatsPerfOctetsRetrans
				 * Total data bytes retransmitted
				 */
	u32	total_retrans;	/* Total retransmits क्रम entire connection */

	u32	urg_seq;	/* Seq of received urgent poपूर्णांकer */
	अचिन्हित पूर्णांक		keepalive_समय;	  /* समय beक्रमe keep alive takes place */
	अचिन्हित पूर्णांक		keepalive_पूर्णांकvl;  /* समय पूर्णांकerval between keep alive probes */

	पूर्णांक			linger2;


/* Sock_ops bpf program related variables */
#अगर_घोषित CONFIG_BPF
	u8	bpf_sock_ops_cb_flags;  /* Control calling BPF programs
					 * values defined in uapi/linux/tcp.h
					 */
#घोषणा BPF_SOCK_OPS_TEST_FLAG(TP, ARG) (TP->bpf_sock_ops_cb_flags & ARG)
#अन्यथा
#घोषणा BPF_SOCK_OPS_TEST_FLAG(TP, ARG) 0
#पूर्ण_अगर

	u16 समयout_rehash;	/* Timeout-triggered rehash attempts */

	u32 rcv_ooopack; /* Received out-of-order packets, क्रम tcpinfo */

/* Receiver side RTT estimation */
	u32 rcv_rtt_last_tsecr;
	काष्ठा अणु
		u32	rtt_us;
		u32	seq;
		u64	समय;
	पूर्ण rcv_rtt_est;

/* Receiver queue space */
	काष्ठा अणु
		u32	space;
		u32	seq;
		u64	समय;
	पूर्ण rcvq_space;

/* TCP-specअगरic MTU probe inक्रमmation. */
	काष्ठा अणु
		u32		  probe_seq_start;
		u32		  probe_seq_end;
	पूर्ण mtu_probe;
	u32	mtu_info; /* We received an ICMP_FRAG_NEEDED / ICMPV6_PKT_TOOBIG
			   * जबतक socket was owned by user.
			   */
#अगर IS_ENABLED(CONFIG_MPTCP)
	bool	is_mptcp;
#पूर्ण_अगर
#अगर IS_ENABLED(CONFIG_SMC)
	bool	syn_smc;	/* SYN includes SMC */
#पूर्ण_अगर

#अगर_घोषित CONFIG_TCP_MD5SIG
/* TCP AF-Specअगरic parts; only used by MD5 Signature support so far */
	स्थिर काष्ठा tcp_sock_af_ops	*af_specअगरic;

/* TCP MD5 Signature Option inक्रमmation */
	काष्ठा tcp_md5sig_info	__rcu *md5sig_info;
#पूर्ण_अगर

/* TCP fastखोलो related inक्रमmation */
	काष्ठा tcp_fastखोलो_request *fastखोलो_req;
	/* fastखोलो_rsk poपूर्णांकs to request_sock that resulted in this big
	 * socket. Used to retransmit SYNACKs etc.
	 */
	काष्ठा request_sock __rcu *fastखोलो_rsk;
	काष्ठा saved_syn *saved_syn;
पूर्ण;

क्रमागत tsq_क्रमागत अणु
	TSQ_THROTTLED,
	TSQ_QUEUED,
	TCP_TSQ_DEFERRED,	   /* tcp_tasklet_func() found socket was owned */
	TCP_WRITE_TIMER_DEFERRED,  /* tcp_ग_लिखो_समयr() found socket was owned */
	TCP_DELACK_TIMER_DEFERRED, /* tcp_delack_समयr() found socket was owned */
	TCP_MTU_REDUCED_DEFERRED,  /* tcp_vअणु4|6पूर्ण_err() could not call
				    * tcp_vअणु4|6पूर्ण_mtu_reduced()
				    */
पूर्ण;

क्रमागत tsq_flags अणु
	TSQF_THROTTLED			= (1UL << TSQ_THROTTLED),
	TSQF_QUEUED			= (1UL << TSQ_QUEUED),
	TCPF_TSQ_DEFERRED		= (1UL << TCP_TSQ_DEFERRED),
	TCPF_WRITE_TIMER_DEFERRED	= (1UL << TCP_WRITE_TIMER_DEFERRED),
	TCPF_DELACK_TIMER_DEFERRED	= (1UL << TCP_DELACK_TIMER_DEFERRED),
	TCPF_MTU_REDUCED_DEFERRED	= (1UL << TCP_MTU_REDUCED_DEFERRED),
पूर्ण;

अटल अंतरभूत काष्ठा tcp_sock *tcp_sk(स्थिर काष्ठा sock *sk)
अणु
	वापस (काष्ठा tcp_sock *)sk;
पूर्ण

काष्ठा tcp_समयरुको_sock अणु
	काष्ठा inet_समयरुको_sock tw_sk;
#घोषणा tw_rcv_nxt tw_sk.__tw_common.skc_tw_rcv_nxt
#घोषणा tw_snd_nxt tw_sk.__tw_common.skc_tw_snd_nxt
	u32			  tw_rcv_wnd;
	u32			  tw_ts_offset;
	u32			  tw_ts_recent;

	/* The समय we sent the last out-of-winकरोw ACK: */
	u32			  tw_last_oow_ack_समय;

	पूर्णांक			  tw_ts_recent_stamp;
	u32			  tw_tx_delay;
#अगर_घोषित CONFIG_TCP_MD5SIG
	काष्ठा tcp_md5sig_key	  *tw_md5_key;
#पूर्ण_अगर
पूर्ण;

अटल अंतरभूत काष्ठा tcp_समयरुको_sock *tcp_twsk(स्थिर काष्ठा sock *sk)
अणु
	वापस (काष्ठा tcp_समयरुको_sock *)sk;
पूर्ण

अटल अंतरभूत bool tcp_passive_fastखोलो(स्थिर काष्ठा sock *sk)
अणु
	वापस sk->sk_state == TCP_SYN_RECV &&
	       rcu_access_poपूर्णांकer(tcp_sk(sk)->fastखोलो_rsk) != शून्य;
पूर्ण

अटल अंतरभूत व्योम fastखोलो_queue_tune(काष्ठा sock *sk, पूर्णांक backlog)
अणु
	काष्ठा request_sock_queue *queue = &inet_csk(sk)->icsk_accept_queue;
	पूर्णांक somaxconn = READ_ONCE(sock_net(sk)->core.sysctl_somaxconn);

	queue->fastखोलोq.max_qlen = min_t(अचिन्हित पूर्णांक, backlog, somaxconn);
पूर्ण

अटल अंतरभूत व्योम tcp_move_syn(काष्ठा tcp_sock *tp,
				काष्ठा request_sock *req)
अणु
	tp->saved_syn = req->saved_syn;
	req->saved_syn = शून्य;
पूर्ण

अटल अंतरभूत व्योम tcp_saved_syn_मुक्त(काष्ठा tcp_sock *tp)
अणु
	kमुक्त(tp->saved_syn);
	tp->saved_syn = शून्य;
पूर्ण

अटल अंतरभूत u32 tcp_saved_syn_len(स्थिर काष्ठा saved_syn *saved_syn)
अणु
	वापस saved_syn->mac_hdrlen + saved_syn->network_hdrlen +
		saved_syn->tcp_hdrlen;
पूर्ण

काष्ठा sk_buff *tcp_get_बारtamping_opt_stats(स्थिर काष्ठा sock *sk,
					       स्थिर काष्ठा sk_buff *orig_skb,
					       स्थिर काष्ठा sk_buff *ack_skb);

अटल अंतरभूत u16 tcp_mss_clamp(स्थिर काष्ठा tcp_sock *tp, u16 mss)
अणु
	/* We use READ_ONCE() here because socket might not be locked.
	 * This happens क्रम listeners.
	 */
	u16 user_mss = READ_ONCE(tp->rx_opt.user_mss);

	वापस (user_mss && user_mss < mss) ? user_mss : mss;
पूर्ण

पूर्णांक tcp_skb_shअगरt(काष्ठा sk_buff *to, काष्ठा sk_buff *from, पूर्णांक pcount,
		  पूर्णांक shअगरtlen);

व्योम tcp_sock_set_cork(काष्ठा sock *sk, bool on);
पूर्णांक tcp_sock_set_keepcnt(काष्ठा sock *sk, पूर्णांक val);
पूर्णांक tcp_sock_set_keepidle_locked(काष्ठा sock *sk, पूर्णांक val);
पूर्णांक tcp_sock_set_keepidle(काष्ठा sock *sk, पूर्णांक val);
पूर्णांक tcp_sock_set_keepपूर्णांकvl(काष्ठा sock *sk, पूर्णांक val);
व्योम tcp_sock_set_nodelay(काष्ठा sock *sk);
व्योम tcp_sock_set_quickack(काष्ठा sock *sk, पूर्णांक val);
पूर्णांक tcp_sock_set_syncnt(काष्ठा sock *sk, पूर्णांक val);
व्योम tcp_sock_set_user_समयout(काष्ठा sock *sk, u32 val);

#पूर्ण_अगर	/* _LINUX_TCP_H */
