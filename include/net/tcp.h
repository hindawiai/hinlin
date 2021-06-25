<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * INET		An implementation of the TCP/IP protocol suite क्रम the LINUX
 *		operating प्रणाली.  INET is implemented using the  BSD Socket
 *		पूर्णांकerface as the means of communication with the user level.
 *
 *		Definitions क्रम the TCP module.
 *
 * Version:	@(#)tcp.h	1.0.5	05/23/93
 *
 * Authors:	Ross Biro
 *		Fred N. van Kempen, <waltje@uWalt.NL.Mugnet.ORG>
 */
#अगर_अघोषित _TCP_H
#घोषणा _TCP_H

#घोषणा FASTRETRANS_DEBUG 1

#समावेश <linux/list.h>
#समावेश <linux/tcp.h>
#समावेश <linux/bug.h>
#समावेश <linux/slab.h>
#समावेश <linux/cache.h>
#समावेश <linux/percpu.h>
#समावेश <linux/skbuff.h>
#समावेश <linux/kref.h>
#समावेश <linux/kसमय.स>
#समावेश <linux/indirect_call_wrapper.h>

#समावेश <net/inet_connection_sock.h>
#समावेश <net/inet_समयरुको_sock.h>
#समावेश <net/inet_hashtables.h>
#समावेश <net/checksum.h>
#समावेश <net/request_sock.h>
#समावेश <net/sock_reuseport.h>
#समावेश <net/sock.h>
#समावेश <net/snmp.h>
#समावेश <net/ip.h>
#समावेश <net/tcp_states.h>
#समावेश <net/inet_ecn.h>
#समावेश <net/dst.h>
#समावेश <net/mptcp.h>

#समावेश <linux/seq_file.h>
#समावेश <linux/memcontrol.h>
#समावेश <linux/bpf-cgroup.h>
#समावेश <linux/siphash.h>

बाह्य काष्ठा inet_hashinfo tcp_hashinfo;

बाह्य काष्ठा percpu_counter tcp_orphan_count;
व्योम tcp_समय_रुको(काष्ठा sock *sk, पूर्णांक state, पूर्णांक समयo);

#घोषणा MAX_TCP_HEADER	L1_CACHE_ALIGN(128 + MAX_HEADER)
#घोषणा MAX_TCP_OPTION_SPACE 40
#घोषणा TCP_MIN_SND_MSS		48
#घोषणा TCP_MIN_GSO_SIZE	(TCP_MIN_SND_MSS - MAX_TCP_OPTION_SPACE)

/*
 * Never offer a winकरोw over 32767 without using winकरोw scaling. Some
 * poor stacks करो चिन्हित 16bit maths!
 */
#घोषणा MAX_TCP_WINDOW		32767U

/* Minimal accepted MSS. It is (60+60+8) - (20+20). */
#घोषणा TCP_MIN_MSS		88U

/* The initial MTU to use क्रम probing */
#घोषणा TCP_BASE_MSS		1024

/* probing पूर्णांकerval, शेष to 10 minutes as per RFC4821 */
#घोषणा TCP_PROBE_INTERVAL	600

/* Specअगरy पूर्णांकerval when tcp mtu probing will stop */
#घोषणा TCP_PROBE_THRESHOLD	8

/* After receiving this amount of duplicate ACKs fast retransmit starts. */
#घोषणा TCP_FASTRETRANS_THRESH 3

/* Maximal number of ACKs sent quickly to accelerate slow-start. */
#घोषणा TCP_MAX_QUICKACKS	16U

/* Maximal number of winकरोw scale according to RFC1323 */
#घोषणा TCP_MAX_WSCALE		14U

/* urg_data states */
#घोषणा TCP_URG_VALID	0x0100
#घोषणा TCP_URG_NOTYET	0x0200
#घोषणा TCP_URG_READ	0x0400

#घोषणा TCP_RETR1	3	/*
				 * This is how many retries it करोes beक्रमe it
				 * tries to figure out अगर the gateway is
				 * करोwn. Minimal RFC value is 3; it corresponds
				 * to ~3sec-8min depending on RTO.
				 */

#घोषणा TCP_RETR2	15	/*
				 * This should take at least
				 * 90 minutes to समय out.
				 * RFC1122 says that the limit is 100 sec.
				 * 15 is ~13-30min depending on RTO.
				 */

#घोषणा TCP_SYN_RETRIES	 6	/* This is how many retries are करोne
				 * when active खोलोing a connection.
				 * RFC1122 says the minimum retry MUST
				 * be at least 180secs.  Nevertheless
				 * this value is corresponding to
				 * 63secs of retransmission with the
				 * current initial RTO.
				 */

#घोषणा TCP_SYNACK_RETRIES 5	/* This is how may retries are करोne
				 * when passive खोलोing a connection.
				 * This is corresponding to 31secs of
				 * retransmission with the current
				 * initial RTO.
				 */

#घोषणा TCP_TIMEWAIT_LEN (60*HZ) /* how दीर्घ to रुको to destroy TIME-WAIT
				  * state, about 60 seconds	*/
#घोषणा TCP_FIN_TIMEOUT	TCP_TIMEWAIT_LEN
                                 /* BSD style FIN_WAIT2 deadlock अवरोधer.
				  * It used to be 3min, new value is 60sec,
				  * to combine FIN-WAIT-2 समयout with
				  * TIME-WAIT समयr.
				  */
#घोषणा TCP_FIN_TIMEOUT_MAX (120 * HZ) /* max TCP_LINGER2 value (two minutes) */

#घोषणा TCP_DELACK_MAX	((अचिन्हित)(HZ/5))	/* maximal समय to delay beक्रमe sending an ACK */
#अगर HZ >= 100
#घोषणा TCP_DELACK_MIN	((अचिन्हित)(HZ/25))	/* minimal समय to delay beक्रमe sending an ACK */
#घोषणा TCP_ATO_MIN	((अचिन्हित)(HZ/25))
#अन्यथा
#घोषणा TCP_DELACK_MIN	4U
#घोषणा TCP_ATO_MIN	4U
#पूर्ण_अगर
#घोषणा TCP_RTO_MAX	((अचिन्हित)(120*HZ))
#घोषणा TCP_RTO_MIN	((अचिन्हित)(HZ/5))
#घोषणा TCP_TIMEOUT_MIN	(2U) /* Min समयout क्रम TCP समयrs in jअगरfies */
#घोषणा TCP_TIMEOUT_INIT ((अचिन्हित)(1*HZ))	/* RFC6298 2.1 initial RTO value	*/
#घोषणा TCP_TIMEOUT_FALLBACK ((अचिन्हित)(3*HZ))	/* RFC 1122 initial RTO value, now
						 * used as a fallback RTO क्रम the
						 * initial data transmission अगर no
						 * valid RTT sample has been acquired,
						 * most likely due to retrans in 3WHS.
						 */

#घोषणा TCP_RESOURCE_PROBE_INTERVAL ((अचिन्हित)(HZ/2U)) /* Maximal पूर्णांकerval between probes
					                 * क्रम local resources.
					                 */
#घोषणा TCP_KEEPALIVE_TIME	(120*60*HZ)	/* two hours */
#घोषणा TCP_KEEPALIVE_PROBES	9		/* Max of 9 keepalive probes	*/
#घोषणा TCP_KEEPALIVE_INTVL	(75*HZ)

#घोषणा MAX_TCP_KEEPIDLE	32767
#घोषणा MAX_TCP_KEEPINTVL	32767
#घोषणा MAX_TCP_KEEPCNT		127
#घोषणा MAX_TCP_SYNCNT		127

#घोषणा TCP_SYNQ_INTERVAL	(HZ/5)	/* Period of SYNACK समयr */

#घोषणा TCP_PAWS_24DAYS	(60 * 60 * 24 * 24)
#घोषणा TCP_PAWS_MSL	60		/* Per-host बारtamps are invalidated
					 * after this समय. It should be equal
					 * (or greater than) TCP_TIMEWAIT_LEN
					 * to provide reliability equal to one
					 * provided by समयरुको state.
					 */
#घोषणा TCP_PAWS_WINDOW	1		/* Replay winकरोw क्रम per-host
					 * बारtamps. It must be less than
					 * minimal समयरुको lअगरeसमय.
					 */
/*
 *	TCP option
 */

#घोषणा TCPOPT_NOP		1	/* Padding */
#घोषणा TCPOPT_EOL		0	/* End of options */
#घोषणा TCPOPT_MSS		2	/* Segment size negotiating */
#घोषणा TCPOPT_WINDOW		3	/* Winकरोw scaling */
#घोषणा TCPOPT_SACK_PERM        4       /* SACK Permitted */
#घोषणा TCPOPT_SACK             5       /* SACK Block */
#घोषणा TCPOPT_TIMESTAMP	8	/* Better RTT estimations/PAWS */
#घोषणा TCPOPT_MD5SIG		19	/* MD5 Signature (RFC2385) */
#घोषणा TCPOPT_MPTCP		30	/* Multipath TCP (RFC6824) */
#घोषणा TCPOPT_FASTOPEN		34	/* Fast खोलो (RFC7413) */
#घोषणा TCPOPT_EXP		254	/* Experimental */
/* Magic number to be after the option value क्रम sharing TCP
 * experimental options. See draft-ietf-tcpm-experimental-options-00.txt
 */
#घोषणा TCPOPT_FASTOPEN_MAGIC	0xF989
#घोषणा TCPOPT_SMC_MAGIC	0xE2D4C3D9

/*
 *     TCP option lengths
 */

#घोषणा TCPOLEN_MSS            4
#घोषणा TCPOLEN_WINDOW         3
#घोषणा TCPOLEN_SACK_PERM      2
#घोषणा TCPOLEN_TIMESTAMP      10
#घोषणा TCPOLEN_MD5SIG         18
#घोषणा TCPOLEN_FASTOPEN_BASE  2
#घोषणा TCPOLEN_EXP_FASTOPEN_BASE  4
#घोषणा TCPOLEN_EXP_SMC_BASE   6

/* But this is what stacks really send out. */
#घोषणा TCPOLEN_TSTAMP_ALIGNED		12
#घोषणा TCPOLEN_WSCALE_ALIGNED		4
#घोषणा TCPOLEN_SACKPERM_ALIGNED	4
#घोषणा TCPOLEN_SACK_BASE		2
#घोषणा TCPOLEN_SACK_BASE_ALIGNED	4
#घोषणा TCPOLEN_SACK_PERBLOCK		8
#घोषणा TCPOLEN_MD5SIG_ALIGNED		20
#घोषणा TCPOLEN_MSS_ALIGNED		4
#घोषणा TCPOLEN_EXP_SMC_BASE_ALIGNED	8

/* Flags in tp->nonagle */
#घोषणा TCP_NAGLE_OFF		1	/* Nagle's algo is disabled */
#घोषणा TCP_NAGLE_CORK		2	/* Socket is corked	    */
#घोषणा TCP_NAGLE_PUSH		4	/* Cork is overridden क्रम alपढ़ोy queued data */

/* TCP thin-stream limits */
#घोषणा TCP_THIN_LINEAR_RETRIES 6       /* After 6 linear retries, करो exp. backoff */

/* TCP initial congestion winकरोw as per rfc6928 */
#घोषणा TCP_INIT_CWND		10

/* Bit Flags क्रम sysctl_tcp_fastखोलो */
#घोषणा	TFO_CLIENT_ENABLE	1
#घोषणा	TFO_SERVER_ENABLE	2
#घोषणा	TFO_CLIENT_NO_COOKIE	4	/* Data in SYN w/o cookie option */

/* Accept SYN data w/o any cookie option */
#घोषणा	TFO_SERVER_COOKIE_NOT_REQD	0x200

/* Force enable TFO on all listeners, i.e., not requiring the
 * TCP_FASTOPEN socket option.
 */
#घोषणा	TFO_SERVER_WO_SOCKOPT1	0x400


/* sysctl variables क्रम tcp */
बाह्य पूर्णांक sysctl_tcp_max_orphans;
बाह्य दीर्घ sysctl_tcp_mem[3];

#घोषणा TCP_RACK_LOSS_DETECTION  0x1 /* Use RACK to detect losses */
#घोषणा TCP_RACK_STATIC_REO_WND  0x2 /* Use अटल RACK reo wnd */
#घोषणा TCP_RACK_NO_DUPTHRESH    0x4 /* Do not use DUPACK threshold in RACK */

बाह्य atomic_दीर्घ_t tcp_memory_allocated;
बाह्य काष्ठा percpu_counter tcp_sockets_allocated;
बाह्य अचिन्हित दीर्घ tcp_memory_pressure;

/* optimized version of sk_under_memory_pressure() क्रम TCP sockets */
अटल अंतरभूत bool tcp_under_memory_pressure(स्थिर काष्ठा sock *sk)
अणु
	अगर (mem_cgroup_sockets_enabled && sk->sk_memcg &&
	    mem_cgroup_under_socket_pressure(sk->sk_memcg))
		वापस true;

	वापस READ_ONCE(tcp_memory_pressure);
पूर्ण
/*
 * The next routines deal with comparing 32 bit अचिन्हित पूर्णांकs
 * and worry about wraparound (स्वतःmatic with अचिन्हित arithmetic).
 */

अटल अंतरभूत bool beक्रमe(__u32 seq1, __u32 seq2)
अणु
        वापस (__s32)(seq1-seq2) < 0;
पूर्ण
#घोषणा after(seq2, seq1) 	beक्रमe(seq1, seq2)

/* is s2<=s1<=s3 ? */
अटल अंतरभूत bool between(__u32 seq1, __u32 seq2, __u32 seq3)
अणु
	वापस seq3 - seq2 >= seq1 - seq2;
पूर्ण

अटल अंतरभूत bool tcp_out_of_memory(काष्ठा sock *sk)
अणु
	अगर (sk->sk_wmem_queued > SOCK_MIN_SNDBUF &&
	    sk_memory_allocated(sk) > sk_prot_mem_limits(sk, 2))
		वापस true;
	वापस false;
पूर्ण

व्योम sk_क्रमced_mem_schedule(काष्ठा sock *sk, पूर्णांक size);

अटल अंतरभूत bool tcp_too_many_orphans(काष्ठा sock *sk, पूर्णांक shअगरt)
अणु
	काष्ठा percpu_counter *ocp = sk->sk_prot->orphan_count;
	पूर्णांक orphans = percpu_counter_पढ़ो_positive(ocp);

	अगर (orphans << shअगरt > sysctl_tcp_max_orphans) अणु
		orphans = percpu_counter_sum_positive(ocp);
		अगर (orphans << shअगरt > sysctl_tcp_max_orphans)
			वापस true;
	पूर्ण
	वापस false;
पूर्ण

bool tcp_check_oom(काष्ठा sock *sk, पूर्णांक shअगरt);


बाह्य काष्ठा proto tcp_prot;

#घोषणा TCP_INC_STATS(net, field)	SNMP_INC_STATS((net)->mib.tcp_statistics, field)
#घोषणा __TCP_INC_STATS(net, field)	__SNMP_INC_STATS((net)->mib.tcp_statistics, field)
#घोषणा TCP_DEC_STATS(net, field)	SNMP_DEC_STATS((net)->mib.tcp_statistics, field)
#घोषणा TCP_ADD_STATS(net, field, val)	SNMP_ADD_STATS((net)->mib.tcp_statistics, field, val)

व्योम tcp_tasklet_init(व्योम);

पूर्णांक tcp_v4_err(काष्ठा sk_buff *skb, u32);

व्योम tcp_shutकरोwn(काष्ठा sock *sk, पूर्णांक how);

पूर्णांक tcp_v4_early_demux(काष्ठा sk_buff *skb);
पूर्णांक tcp_v4_rcv(काष्ठा sk_buff *skb);

व्योम tcp_हटाओ_empty_skb(काष्ठा sock *sk, काष्ठा sk_buff *skb);
पूर्णांक tcp_v4_tw_remember_stamp(काष्ठा inet_समयरुको_sock *tw);
पूर्णांक tcp_sendmsg(काष्ठा sock *sk, काष्ठा msghdr *msg, माप_प्रकार size);
पूर्णांक tcp_sendmsg_locked(काष्ठा sock *sk, काष्ठा msghdr *msg, माप_प्रकार size);
पूर्णांक tcp_sendpage(काष्ठा sock *sk, काष्ठा page *page, पूर्णांक offset, माप_प्रकार size,
		 पूर्णांक flags);
पूर्णांक tcp_sendpage_locked(काष्ठा sock *sk, काष्ठा page *page, पूर्णांक offset,
			माप_प्रकार size, पूर्णांक flags);
काष्ठा sk_buff *tcp_build_frag(काष्ठा sock *sk, पूर्णांक size_goal, पूर्णांक flags,
			       काष्ठा page *page, पूर्णांक offset, माप_प्रकार *size);
sमाप_प्रकार करो_tcp_sendpages(काष्ठा sock *sk, काष्ठा page *page, पूर्णांक offset,
		 माप_प्रकार size, पूर्णांक flags);
पूर्णांक tcp_send_mss(काष्ठा sock *sk, पूर्णांक *size_goal, पूर्णांक flags);
व्योम tcp_push(काष्ठा sock *sk, पूर्णांक flags, पूर्णांक mss_now, पूर्णांक nonagle,
	      पूर्णांक size_goal);
व्योम tcp_release_cb(काष्ठा sock *sk);
व्योम tcp_wमुक्त(काष्ठा sk_buff *skb);
व्योम tcp_ग_लिखो_समयr_handler(काष्ठा sock *sk);
व्योम tcp_delack_समयr_handler(काष्ठा sock *sk);
पूर्णांक tcp_ioctl(काष्ठा sock *sk, पूर्णांक cmd, अचिन्हित दीर्घ arg);
पूर्णांक tcp_rcv_state_process(काष्ठा sock *sk, काष्ठा sk_buff *skb);
व्योम tcp_rcv_established(काष्ठा sock *sk, काष्ठा sk_buff *skb);
व्योम tcp_rcv_space_adjust(काष्ठा sock *sk);
पूर्णांक tcp_twsk_unique(काष्ठा sock *sk, काष्ठा sock *sktw, व्योम *twp);
व्योम tcp_twsk_deकाष्ठाor(काष्ठा sock *sk);
sमाप_प्रकार tcp_splice_पढ़ो(काष्ठा socket *sk, loff_t *ppos,
			काष्ठा pipe_inode_info *pipe, माप_प्रकार len,
			अचिन्हित पूर्णांक flags);

व्योम tcp_enter_quickack_mode(काष्ठा sock *sk, अचिन्हित पूर्णांक max_quickacks);
अटल अंतरभूत व्योम tcp_dec_quickack_mode(काष्ठा sock *sk,
					 स्थिर अचिन्हित पूर्णांक pkts)
अणु
	काष्ठा inet_connection_sock *icsk = inet_csk(sk);

	अगर (icsk->icsk_ack.quick) अणु
		अगर (pkts >= icsk->icsk_ack.quick) अणु
			icsk->icsk_ack.quick = 0;
			/* Leaving quickack mode we deflate ATO. */
			icsk->icsk_ack.ato   = TCP_ATO_MIN;
		पूर्ण अन्यथा
			icsk->icsk_ack.quick -= pkts;
	पूर्ण
पूर्ण

#घोषणा	TCP_ECN_OK		1
#घोषणा	TCP_ECN_QUEUE_CWR	2
#घोषणा	TCP_ECN_DEMAND_CWR	4
#घोषणा	TCP_ECN_SEEN		8

क्रमागत tcp_tw_status अणु
	TCP_TW_SUCCESS = 0,
	TCP_TW_RST = 1,
	TCP_TW_ACK = 2,
	TCP_TW_SYN = 3
पूर्ण;


क्रमागत tcp_tw_status tcp_समयरुको_state_process(काष्ठा inet_समयरुको_sock *tw,
					      काष्ठा sk_buff *skb,
					      स्थिर काष्ठा tcphdr *th);
काष्ठा sock *tcp_check_req(काष्ठा sock *sk, काष्ठा sk_buff *skb,
			   काष्ठा request_sock *req, bool fastखोलो,
			   bool *lost_race);
पूर्णांक tcp_child_process(काष्ठा sock *parent, काष्ठा sock *child,
		      काष्ठा sk_buff *skb);
व्योम tcp_enter_loss(काष्ठा sock *sk);
व्योम tcp_cwnd_reduction(काष्ठा sock *sk, पूर्णांक newly_acked_sacked, पूर्णांक newly_lost, पूर्णांक flag);
व्योम tcp_clear_retrans(काष्ठा tcp_sock *tp);
व्योम tcp_update_metrics(काष्ठा sock *sk);
व्योम tcp_init_metrics(काष्ठा sock *sk);
व्योम tcp_metrics_init(व्योम);
bool tcp_peer_is_proven(काष्ठा request_sock *req, काष्ठा dst_entry *dst);
व्योम __tcp_बंद(काष्ठा sock *sk, दीर्घ समयout);
व्योम tcp_बंद(काष्ठा sock *sk, दीर्घ समयout);
व्योम tcp_init_sock(काष्ठा sock *sk);
व्योम tcp_init_transfer(काष्ठा sock *sk, पूर्णांक bpf_op, काष्ठा sk_buff *skb);
__poll_t tcp_poll(काष्ठा file *file, काष्ठा socket *sock,
		      काष्ठा poll_table_काष्ठा *रुको);
पूर्णांक tcp_माला_लोockopt(काष्ठा sock *sk, पूर्णांक level, पूर्णांक optname,
		   अक्षर __user *optval, पूर्णांक __user *optlen);
bool tcp_bpf_bypass_माला_लोockopt(पूर्णांक level, पूर्णांक optname);
पूर्णांक tcp_setsockopt(काष्ठा sock *sk, पूर्णांक level, पूर्णांक optname, sockptr_t optval,
		   अचिन्हित पूर्णांक optlen);
व्योम tcp_set_keepalive(काष्ठा sock *sk, पूर्णांक val);
व्योम tcp_syn_ack_समयout(स्थिर काष्ठा request_sock *req);
पूर्णांक tcp_recvmsg(काष्ठा sock *sk, काष्ठा msghdr *msg, माप_प्रकार len, पूर्णांक nonblock,
		पूर्णांक flags, पूर्णांक *addr_len);
पूर्णांक tcp_set_rcvlowat(काष्ठा sock *sk, पूर्णांक val);
पूर्णांक tcp_set_winकरोw_clamp(काष्ठा sock *sk, पूर्णांक val);
व्योम tcp_data_पढ़ोy(काष्ठा sock *sk);
#अगर_घोषित CONFIG_MMU
पूर्णांक tcp_mmap(काष्ठा file *file, काष्ठा socket *sock,
	     काष्ठा vm_area_काष्ठा *vma);
#पूर्ण_अगर
व्योम tcp_parse_options(स्थिर काष्ठा net *net, स्थिर काष्ठा sk_buff *skb,
		       काष्ठा tcp_options_received *opt_rx,
		       पूर्णांक estab, काष्ठा tcp_fastखोलो_cookie *foc);
स्थिर u8 *tcp_parse_md5sig_option(स्थिर काष्ठा tcphdr *th);

/*
 *	BPF SKB-less helpers
 */
u16 tcp_v4_get_syncookie(काष्ठा sock *sk, काष्ठा iphdr *iph,
			 काष्ठा tcphdr *th, u32 *cookie);
u16 tcp_v6_get_syncookie(काष्ठा sock *sk, काष्ठा ipv6hdr *iph,
			 काष्ठा tcphdr *th, u32 *cookie);
u16 tcp_get_syncookie_mss(काष्ठा request_sock_ops *rsk_ops,
			  स्थिर काष्ठा tcp_request_sock_ops *af_ops,
			  काष्ठा sock *sk, काष्ठा tcphdr *th);
/*
 *	TCP v4 functions exported क्रम the inet6 API
 */

व्योम tcp_v4_send_check(काष्ठा sock *sk, काष्ठा sk_buff *skb);
व्योम tcp_v4_mtu_reduced(काष्ठा sock *sk);
व्योम tcp_req_err(काष्ठा sock *sk, u32 seq, bool पात);
व्योम tcp_ld_RTO_revert(काष्ठा sock *sk, u32 seq);
पूर्णांक tcp_v4_conn_request(काष्ठा sock *sk, काष्ठा sk_buff *skb);
काष्ठा sock *tcp_create_खोलोreq_child(स्थिर काष्ठा sock *sk,
				      काष्ठा request_sock *req,
				      काष्ठा sk_buff *skb);
व्योम tcp_ca_खोलोreq_child(काष्ठा sock *sk, स्थिर काष्ठा dst_entry *dst);
काष्ठा sock *tcp_v4_syn_recv_sock(स्थिर काष्ठा sock *sk, काष्ठा sk_buff *skb,
				  काष्ठा request_sock *req,
				  काष्ठा dst_entry *dst,
				  काष्ठा request_sock *req_unhash,
				  bool *own_req);
पूर्णांक tcp_v4_करो_rcv(काष्ठा sock *sk, काष्ठा sk_buff *skb);
पूर्णांक tcp_v4_connect(काष्ठा sock *sk, काष्ठा sockaddr *uaddr, पूर्णांक addr_len);
पूर्णांक tcp_connect(काष्ठा sock *sk);
क्रमागत tcp_synack_type अणु
	TCP_SYNACK_NORMAL,
	TCP_SYNACK_FASTOPEN,
	TCP_SYNACK_COOKIE,
पूर्ण;
काष्ठा sk_buff *tcp_make_synack(स्थिर काष्ठा sock *sk, काष्ठा dst_entry *dst,
				काष्ठा request_sock *req,
				काष्ठा tcp_fastखोलो_cookie *foc,
				क्रमागत tcp_synack_type synack_type,
				काष्ठा sk_buff *syn_skb);
पूर्णांक tcp_disconnect(काष्ठा sock *sk, पूर्णांक flags);

व्योम tcp_finish_connect(काष्ठा sock *sk, काष्ठा sk_buff *skb);
पूर्णांक tcp_send_rcvq(काष्ठा sock *sk, काष्ठा msghdr *msg, माप_प्रकार size);
व्योम inet_sk_rx_dst_set(काष्ठा sock *sk, स्थिर काष्ठा sk_buff *skb);

/* From syncookies.c */
काष्ठा sock *tcp_get_cookie_sock(काष्ठा sock *sk, काष्ठा sk_buff *skb,
				 काष्ठा request_sock *req,
				 काष्ठा dst_entry *dst, u32 tsoff);
पूर्णांक __cookie_v4_check(स्थिर काष्ठा iphdr *iph, स्थिर काष्ठा tcphdr *th,
		      u32 cookie);
काष्ठा sock *cookie_v4_check(काष्ठा sock *sk, काष्ठा sk_buff *skb);
काष्ठा request_sock *cookie_tcp_reqsk_alloc(स्थिर काष्ठा request_sock_ops *ops,
					    काष्ठा sock *sk, काष्ठा sk_buff *skb);
#अगर_घोषित CONFIG_SYN_COOKIES

/* Syncookies use a monotonic समयr which increments every 60 seconds.
 * This counter is used both as a hash input and partially encoded पूर्णांकo
 * the cookie value.  A cookie is only validated further अगर the delta
 * between the current counter value and the encoded one is less than this,
 * i.e. a sent cookie is valid only at most क्रम 2*60 seconds (or less अगर
 * the counter advances immediately after a cookie is generated).
 */
#घोषणा MAX_SYNCOOKIE_AGE	2
#घोषणा TCP_SYNCOOKIE_PERIOD	(60 * HZ)
#घोषणा TCP_SYNCOOKIE_VALID	(MAX_SYNCOOKIE_AGE * TCP_SYNCOOKIE_PERIOD)

/* syncookies: remember समय of last synqueue overflow
 * But करो not dirty this field too often (once per second is enough)
 * It is racy as we करो not hold a lock, but race is very minor.
 */
अटल अंतरभूत व्योम tcp_synq_overflow(स्थिर काष्ठा sock *sk)
अणु
	अचिन्हित पूर्णांक last_overflow;
	अचिन्हित पूर्णांक now = jअगरfies;

	अगर (sk->sk_reuseport) अणु
		काष्ठा sock_reuseport *reuse;

		reuse = rcu_dereference(sk->sk_reuseport_cb);
		अगर (likely(reuse)) अणु
			last_overflow = READ_ONCE(reuse->synq_overflow_ts);
			अगर (!समय_between32(now, last_overflow,
					    last_overflow + HZ))
				WRITE_ONCE(reuse->synq_overflow_ts, now);
			वापस;
		पूर्ण
	पूर्ण

	last_overflow = READ_ONCE(tcp_sk(sk)->rx_opt.ts_recent_stamp);
	अगर (!समय_between32(now, last_overflow, last_overflow + HZ))
		WRITE_ONCE(tcp_sk(sk)->rx_opt.ts_recent_stamp, now);
पूर्ण

/* syncookies: no recent synqueue overflow on this listening socket? */
अटल अंतरभूत bool tcp_synq_no_recent_overflow(स्थिर काष्ठा sock *sk)
अणु
	अचिन्हित पूर्णांक last_overflow;
	अचिन्हित पूर्णांक now = jअगरfies;

	अगर (sk->sk_reuseport) अणु
		काष्ठा sock_reuseport *reuse;

		reuse = rcu_dereference(sk->sk_reuseport_cb);
		अगर (likely(reuse)) अणु
			last_overflow = READ_ONCE(reuse->synq_overflow_ts);
			वापस !समय_between32(now, last_overflow - HZ,
					       last_overflow +
					       TCP_SYNCOOKIE_VALID);
		पूर्ण
	पूर्ण

	last_overflow = READ_ONCE(tcp_sk(sk)->rx_opt.ts_recent_stamp);

	/* If last_overflow <= jअगरfies <= last_overflow + TCP_SYNCOOKIE_VALID,
	 * then we're under synflood. However, we have to use
	 * 'last_overflow - HZ' as lower bound. That's because a concurrent
	 * tcp_synq_overflow() could update .ts_recent_stamp after we पढ़ो
	 * jअगरfies but beक्रमe we store .ts_recent_stamp पूर्णांकo last_overflow,
	 * which could lead to rejecting a valid syncookie.
	 */
	वापस !समय_between32(now, last_overflow - HZ,
			       last_overflow + TCP_SYNCOOKIE_VALID);
पूर्ण

अटल अंतरभूत u32 tcp_cookie_समय(व्योम)
अणु
	u64 val = get_jअगरfies_64();

	करो_भाग(val, TCP_SYNCOOKIE_PERIOD);
	वापस val;
पूर्ण

u32 __cookie_v4_init_sequence(स्थिर काष्ठा iphdr *iph, स्थिर काष्ठा tcphdr *th,
			      u16 *mssp);
__u32 cookie_v4_init_sequence(स्थिर काष्ठा sk_buff *skb, __u16 *mss);
u64 cookie_init_बारtamp(काष्ठा request_sock *req, u64 now);
bool cookie_बारtamp_decode(स्थिर काष्ठा net *net,
			     काष्ठा tcp_options_received *opt);
bool cookie_ecn_ok(स्थिर काष्ठा tcp_options_received *opt,
		   स्थिर काष्ठा net *net, स्थिर काष्ठा dst_entry *dst);

/* From net/ipv6/syncookies.c */
पूर्णांक __cookie_v6_check(स्थिर काष्ठा ipv6hdr *iph, स्थिर काष्ठा tcphdr *th,
		      u32 cookie);
काष्ठा sock *cookie_v6_check(काष्ठा sock *sk, काष्ठा sk_buff *skb);

u32 __cookie_v6_init_sequence(स्थिर काष्ठा ipv6hdr *iph,
			      स्थिर काष्ठा tcphdr *th, u16 *mssp);
__u32 cookie_v6_init_sequence(स्थिर काष्ठा sk_buff *skb, __u16 *mss);
#पूर्ण_अगर
/* tcp_output.c */

व्योम __tcp_push_pending_frames(काष्ठा sock *sk, अचिन्हित पूर्णांक cur_mss,
			       पूर्णांक nonagle);
पूर्णांक __tcp_retransmit_skb(काष्ठा sock *sk, काष्ठा sk_buff *skb, पूर्णांक segs);
पूर्णांक tcp_retransmit_skb(काष्ठा sock *sk, काष्ठा sk_buff *skb, पूर्णांक segs);
व्योम tcp_retransmit_समयr(काष्ठा sock *sk);
व्योम tcp_xmit_retransmit_queue(काष्ठा sock *);
व्योम tcp_simple_retransmit(काष्ठा sock *);
व्योम tcp_enter_recovery(काष्ठा sock *sk, bool ece_ack);
पूर्णांक tcp_trim_head(काष्ठा sock *, काष्ठा sk_buff *, u32);
क्रमागत tcp_queue अणु
	TCP_FRAG_IN_WRITE_QUEUE,
	TCP_FRAG_IN_RTX_QUEUE,
पूर्ण;
पूर्णांक tcp_fragment(काष्ठा sock *sk, क्रमागत tcp_queue tcp_queue,
		 काष्ठा sk_buff *skb, u32 len,
		 अचिन्हित पूर्णांक mss_now, gfp_t gfp);

व्योम tcp_send_probe0(काष्ठा sock *);
व्योम tcp_send_partial(काष्ठा sock *);
पूर्णांक tcp_ग_लिखो_wakeup(काष्ठा sock *, पूर्णांक mib);
व्योम tcp_send_fin(काष्ठा sock *sk);
व्योम tcp_send_active_reset(काष्ठा sock *sk, gfp_t priority);
पूर्णांक tcp_send_synack(काष्ठा sock *);
व्योम tcp_push_one(काष्ठा sock *, अचिन्हित पूर्णांक mss_now);
व्योम __tcp_send_ack(काष्ठा sock *sk, u32 rcv_nxt);
व्योम tcp_send_ack(काष्ठा sock *sk);
व्योम tcp_send_delayed_ack(काष्ठा sock *sk);
व्योम tcp_send_loss_probe(काष्ठा sock *sk);
bool tcp_schedule_loss_probe(काष्ठा sock *sk, bool advancing_rto);
व्योम tcp_skb_collapse_tstamp(काष्ठा sk_buff *skb,
			     स्थिर काष्ठा sk_buff *next_skb);

/* tcp_input.c */
व्योम tcp_rearm_rto(काष्ठा sock *sk);
व्योम tcp_synack_rtt_meas(काष्ठा sock *sk, काष्ठा request_sock *req);
व्योम tcp_reset(काष्ठा sock *sk, काष्ठा sk_buff *skb);
व्योम tcp_skb_mark_lost_uncond_verअगरy(काष्ठा tcp_sock *tp, काष्ठा sk_buff *skb);
व्योम tcp_fin(काष्ठा sock *sk);

/* tcp_समयr.c */
व्योम tcp_init_xmit_समयrs(काष्ठा sock *);
अटल अंतरभूत व्योम tcp_clear_xmit_समयrs(काष्ठा sock *sk)
अणु
	अगर (hrसमयr_try_to_cancel(&tcp_sk(sk)->pacing_समयr) == 1)
		__sock_put(sk);

	अगर (hrसमयr_try_to_cancel(&tcp_sk(sk)->compressed_ack_समयr) == 1)
		__sock_put(sk);

	inet_csk_clear_xmit_समयrs(sk);
पूर्ण

अचिन्हित पूर्णांक tcp_sync_mss(काष्ठा sock *sk, u32 pmtu);
अचिन्हित पूर्णांक tcp_current_mss(काष्ठा sock *sk);
u32 tcp_clamp_probe0_to_user_समयout(स्थिर काष्ठा sock *sk, u32 when);

/* Bound MSS / TSO packet size with the half of the winकरोw */
अटल अंतरभूत पूर्णांक tcp_bound_to_half_wnd(काष्ठा tcp_sock *tp, पूर्णांक pktsize)
अणु
	पूर्णांक cutoff;

	/* When peer uses tiny winकरोws, there is no use in packetizing
	 * to sub-MSS pieces क्रम the sake of SWS or making sure there
	 * are enough packets in the pipe क्रम fast recovery.
	 *
	 * On the other hand, क्रम extremely large MSS devices, handling
	 * smaller than MSS winकरोws in this way करोes make sense.
	 */
	अगर (tp->max_winकरोw > TCP_MSS_DEFAULT)
		cutoff = (tp->max_winकरोw >> 1);
	अन्यथा
		cutoff = tp->max_winकरोw;

	अगर (cutoff && pktsize > cutoff)
		वापस max_t(पूर्णांक, cutoff, 68U - tp->tcp_header_len);
	अन्यथा
		वापस pktsize;
पूर्ण

/* tcp.c */
व्योम tcp_get_info(काष्ठा sock *, काष्ठा tcp_info *);

/* Read 'sendfile()'-style from a TCP socket */
पूर्णांक tcp_पढ़ो_sock(काष्ठा sock *sk, पढ़ो_descriptor_t *desc,
		  sk_पढ़ो_actor_t recv_actor);

व्योम tcp_initialize_rcv_mss(काष्ठा sock *sk);

पूर्णांक tcp_mtu_to_mss(काष्ठा sock *sk, पूर्णांक pmtu);
पूर्णांक tcp_mss_to_mtu(काष्ठा sock *sk, पूर्णांक mss);
व्योम tcp_mtup_init(काष्ठा sock *sk);

अटल अंतरभूत व्योम tcp_bound_rto(स्थिर काष्ठा sock *sk)
अणु
	अगर (inet_csk(sk)->icsk_rto > TCP_RTO_MAX)
		inet_csk(sk)->icsk_rto = TCP_RTO_MAX;
पूर्ण

अटल अंतरभूत u32 __tcp_set_rto(स्थिर काष्ठा tcp_sock *tp)
अणु
	वापस usecs_to_jअगरfies((tp->srtt_us >> 3) + tp->rttvar_us);
पूर्ण

अटल अंतरभूत व्योम __tcp_fast_path_on(काष्ठा tcp_sock *tp, u32 snd_wnd)
अणु
	tp->pred_flags = htonl((tp->tcp_header_len << 26) |
			       ntohl(TCP_FLAG_ACK) |
			       snd_wnd);
पूर्ण

अटल अंतरभूत व्योम tcp_fast_path_on(काष्ठा tcp_sock *tp)
अणु
	__tcp_fast_path_on(tp, tp->snd_wnd >> tp->rx_opt.snd_wscale);
पूर्ण

अटल अंतरभूत व्योम tcp_fast_path_check(काष्ठा sock *sk)
अणु
	काष्ठा tcp_sock *tp = tcp_sk(sk);

	अगर (RB_EMPTY_ROOT(&tp->out_of_order_queue) &&
	    tp->rcv_wnd &&
	    atomic_पढ़ो(&sk->sk_rmem_alloc) < sk->sk_rcvbuf &&
	    !tp->urg_data)
		tcp_fast_path_on(tp);
पूर्ण

/* Compute the actual rto_min value */
अटल अंतरभूत u32 tcp_rto_min(काष्ठा sock *sk)
अणु
	स्थिर काष्ठा dst_entry *dst = __sk_dst_get(sk);
	u32 rto_min = inet_csk(sk)->icsk_rto_min;

	अगर (dst && dst_metric_locked(dst, RTAX_RTO_MIN))
		rto_min = dst_metric_rtt(dst, RTAX_RTO_MIN);
	वापस rto_min;
पूर्ण

अटल अंतरभूत u32 tcp_rto_min_us(काष्ठा sock *sk)
अणु
	वापस jअगरfies_to_usecs(tcp_rto_min(sk));
पूर्ण

अटल अंतरभूत bool tcp_ca_dst_locked(स्थिर काष्ठा dst_entry *dst)
अणु
	वापस dst_metric_locked(dst, RTAX_CC_ALGO);
पूर्ण

/* Minimum RTT in usec. ~0 means not available. */
अटल अंतरभूत u32 tcp_min_rtt(स्थिर काष्ठा tcp_sock *tp)
अणु
	वापस minmax_get(&tp->rtt_min);
पूर्ण

/* Compute the actual receive winकरोw we are currently advertising.
 * Rcv_nxt can be after the winकरोw अगर our peer push more data
 * than the offered winकरोw.
 */
अटल अंतरभूत u32 tcp_receive_winकरोw(स्थिर काष्ठा tcp_sock *tp)
अणु
	s32 win = tp->rcv_wup + tp->rcv_wnd - tp->rcv_nxt;

	अगर (win < 0)
		win = 0;
	वापस (u32) win;
पूर्ण

/* Choose a new winकरोw, without checks क्रम shrinking, and without
 * scaling applied to the result.  The caller करोes these things
 * अगर necessary.  This is a "raw" winकरोw selection.
 */
u32 __tcp_select_winकरोw(काष्ठा sock *sk);

व्योम tcp_send_winकरोw_probe(काष्ठा sock *sk);

/* TCP uses 32bit jअगरfies to save some space.
 * Note that this is dअगरferent from tcp_समय_stamp, which
 * historically has been the same until linux-4.13.
 */
#घोषणा tcp_jअगरfies32 ((u32)jअगरfies)

/*
 * Deliver a 32bit value क्रम TCP बारtamp option (RFC 7323)
 * It is no दीर्घer tied to jअगरfies, but to 1 ms घड़ी.
 * Note: द्विगुन check अगर you want to use tcp_jअगरfies32 instead of this.
 */
#घोषणा TCP_TS_HZ	1000

अटल अंतरभूत u64 tcp_घड़ी_ns(व्योम)
अणु
	वापस kसमय_get_ns();
पूर्ण

अटल अंतरभूत u64 tcp_घड़ी_us(व्योम)
अणु
	वापस भाग_u64(tcp_घड़ी_ns(), NSEC_PER_USEC);
पूर्ण

/* This should only be used in contexts where tp->tcp_mstamp is up to date */
अटल अंतरभूत u32 tcp_समय_stamp(स्थिर काष्ठा tcp_sock *tp)
अणु
	वापस भाग_u64(tp->tcp_mstamp, USEC_PER_SEC / TCP_TS_HZ);
पूर्ण

/* Convert a nsec बारtamp पूर्णांकo TCP TSval बारtamp (ms based currently) */
अटल अंतरभूत u32 tcp_ns_to_ts(u64 ns)
अणु
	वापस भाग_u64(ns, NSEC_PER_SEC / TCP_TS_HZ);
पूर्ण

/* Could use tcp_घड़ी_us() / 1000, but this version uses a single भागide */
अटल अंतरभूत u32 tcp_समय_stamp_raw(व्योम)
अणु
	वापस tcp_ns_to_ts(tcp_घड़ी_ns());
पूर्ण

व्योम tcp_mstamp_refresh(काष्ठा tcp_sock *tp);

अटल अंतरभूत u32 tcp_stamp_us_delta(u64 t1, u64 t0)
अणु
	वापस max_t(s64, t1 - t0, 0);
पूर्ण

अटल अंतरभूत u32 tcp_skb_बारtamp(स्थिर काष्ठा sk_buff *skb)
अणु
	वापस tcp_ns_to_ts(skb->skb_mstamp_ns);
पूर्ण

/* provide the departure समय in us unit */
अटल अंतरभूत u64 tcp_skb_बारtamp_us(स्थिर काष्ठा sk_buff *skb)
अणु
	वापस भाग_u64(skb->skb_mstamp_ns, NSEC_PER_USEC);
पूर्ण


#घोषणा tcp_flag_byte(th) (((u_पूर्णांक8_t *)th)[13])

#घोषणा TCPHDR_FIN 0x01
#घोषणा TCPHDR_SYN 0x02
#घोषणा TCPHDR_RST 0x04
#घोषणा TCPHDR_PSH 0x08
#घोषणा TCPHDR_ACK 0x10
#घोषणा TCPHDR_URG 0x20
#घोषणा TCPHDR_ECE 0x40
#घोषणा TCPHDR_CWR 0x80

#घोषणा TCPHDR_SYN_ECN	(TCPHDR_SYN | TCPHDR_ECE | TCPHDR_CWR)

/* This is what the send packet queuing engine uses to pass
 * TCP per-packet control inक्रमmation to the transmission code.
 * We also store the host-order sequence numbers in here too.
 * This is 44 bytes अगर IPV6 is enabled.
 * If this grows please adjust skbuff.h:skbuff->cb[xxx] size appropriately.
 */
काष्ठा tcp_skb_cb अणु
	__u32		seq;		/* Starting sequence number	*/
	__u32		end_seq;	/* SEQ + FIN + SYN + datalen	*/
	जोड़ अणु
		/* Note : tcp_tw_isn is used in input path only
		 *	  (isn chosen by tcp_समयरुको_state_process())
		 *
		 * 	  tcp_gso_segs/size are used in ग_लिखो queue only,
		 *	  cf tcp_skb_pcount()/tcp_skb_mss()
		 */
		__u32		tcp_tw_isn;
		काष्ठा अणु
			u16	tcp_gso_segs;
			u16	tcp_gso_size;
		पूर्ण;
	पूर्ण;
	__u8		tcp_flags;	/* TCP header flags. (tcp[13])	*/

	__u8		sacked;		/* State flags क्रम SACK.	*/
#घोषणा TCPCB_SACKED_ACKED	0x01	/* SKB ACK'd by a SACK block	*/
#घोषणा TCPCB_SACKED_RETRANS	0x02	/* SKB retransmitted		*/
#घोषणा TCPCB_LOST		0x04	/* SKB is lost			*/
#घोषणा TCPCB_TAGBITS		0x07	/* All tag bits			*/
#घोषणा TCPCB_REPAIRED		0x10	/* SKB repaired (no skb_mstamp_ns)	*/
#घोषणा TCPCB_EVER_RETRANS	0x80	/* Ever retransmitted frame	*/
#घोषणा TCPCB_RETRANS		(TCPCB_SACKED_RETRANS|TCPCB_EVER_RETRANS| \
				TCPCB_REPAIRED)

	__u8		ip_dsfield;	/* IPv4 tos or IPv6 dsfield	*/
	__u8		txstamp_ack:1,	/* Record TX बारtamp क्रम ack? */
			eor:1,		/* Is skb MSG_EOR marked? */
			has_rxtstamp:1,	/* SKB has a RX बारtamp	*/
			unused:5;
	__u32		ack_seq;	/* Sequence number ACK'd	*/
	जोड़ अणु
		काष्ठा अणु
			/* There is space क्रम up to 24 bytes */
			__u32 in_flight:30,/* Bytes in flight at transmit */
			      is_app_limited:1, /* cwnd not fully used? */
			      unused:1;
			/* pkts S/ACKed so far upon tx of skb, incl retrans: */
			__u32 delivered;
			/* start of send pipeline phase */
			u64 first_tx_mstamp;
			/* when we reached the "delivered" count */
			u64 delivered_mstamp;
		पूर्ण tx;   /* only used क्रम outgoing skbs */
		जोड़ अणु
			काष्ठा inet_skb_parm	h4;
#अगर IS_ENABLED(CONFIG_IPV6)
			काष्ठा inet6_skb_parm	h6;
#पूर्ण_अगर
		पूर्ण header;	/* For incoming skbs */
	पूर्ण;
पूर्ण;

#घोषणा TCP_SKB_CB(__skb)	((काष्ठा tcp_skb_cb *)&((__skb)->cb[0]))

बाह्य स्थिर काष्ठा inet_connection_sock_af_ops ipv4_specअगरic;

#अगर IS_ENABLED(CONFIG_IPV6)
/* This is the variant of inet6_iअगर() that must be used by TCP,
 * as TCP moves IP6CB पूर्णांकo a dअगरferent location in skb->cb[]
 */
अटल अंतरभूत पूर्णांक tcp_v6_iअगर(स्थिर काष्ठा sk_buff *skb)
अणु
	वापस TCP_SKB_CB(skb)->header.h6.iअगर;
पूर्ण

अटल अंतरभूत पूर्णांक tcp_v6_iअगर_l3_slave(स्थिर काष्ठा sk_buff *skb)
अणु
	bool l3_slave = ipv6_l3mdev_skb(TCP_SKB_CB(skb)->header.h6.flags);

	वापस l3_slave ? skb->skb_iअगर : TCP_SKB_CB(skb)->header.h6.iअगर;
पूर्ण

/* TCP_SKB_CB reference means this can not be used from early demux */
अटल अंतरभूत पूर्णांक tcp_v6_sdअगर(स्थिर काष्ठा sk_buff *skb)
अणु
#अगर IS_ENABLED(CONFIG_NET_L3_MASTER_DEV)
	अगर (skb && ipv6_l3mdev_skb(TCP_SKB_CB(skb)->header.h6.flags))
		वापस TCP_SKB_CB(skb)->header.h6.iअगर;
#पूर्ण_अगर
	वापस 0;
पूर्ण

बाह्य स्थिर काष्ठा inet_connection_sock_af_ops ipv6_specअगरic;

INसूचीECT_CALLABLE_DECLARE(व्योम tcp_v6_send_check(काष्ठा sock *sk, काष्ठा sk_buff *skb));
INसूचीECT_CALLABLE_DECLARE(पूर्णांक tcp_v6_rcv(काष्ठा sk_buff *skb));
INसूचीECT_CALLABLE_DECLARE(व्योम tcp_v6_early_demux(काष्ठा sk_buff *skb));

#पूर्ण_अगर

/* TCP_SKB_CB reference means this can not be used from early demux */
अटल अंतरभूत पूर्णांक tcp_v4_sdअगर(काष्ठा sk_buff *skb)
अणु
#अगर IS_ENABLED(CONFIG_NET_L3_MASTER_DEV)
	अगर (skb && ipv4_l3mdev_skb(TCP_SKB_CB(skb)->header.h4.flags))
		वापस TCP_SKB_CB(skb)->header.h4.iअगर;
#पूर्ण_अगर
	वापस 0;
पूर्ण

/* Due to TSO, an SKB can be composed of multiple actual
 * packets.  To keep these tracked properly, we use this.
 */
अटल अंतरभूत पूर्णांक tcp_skb_pcount(स्थिर काष्ठा sk_buff *skb)
अणु
	वापस TCP_SKB_CB(skb)->tcp_gso_segs;
पूर्ण

अटल अंतरभूत व्योम tcp_skb_pcount_set(काष्ठा sk_buff *skb, पूर्णांक segs)
अणु
	TCP_SKB_CB(skb)->tcp_gso_segs = segs;
पूर्ण

अटल अंतरभूत व्योम tcp_skb_pcount_add(काष्ठा sk_buff *skb, पूर्णांक segs)
अणु
	TCP_SKB_CB(skb)->tcp_gso_segs += segs;
पूर्ण

/* This is valid अगरf skb is in ग_लिखो queue and tcp_skb_pcount() > 1. */
अटल अंतरभूत पूर्णांक tcp_skb_mss(स्थिर काष्ठा sk_buff *skb)
अणु
	वापस TCP_SKB_CB(skb)->tcp_gso_size;
पूर्ण

अटल अंतरभूत bool tcp_skb_can_collapse_to(स्थिर काष्ठा sk_buff *skb)
अणु
	वापस likely(!TCP_SKB_CB(skb)->eor);
पूर्ण

अटल अंतरभूत bool tcp_skb_can_collapse(स्थिर काष्ठा sk_buff *to,
					स्थिर काष्ठा sk_buff *from)
अणु
	वापस likely(tcp_skb_can_collapse_to(to) &&
		      mptcp_skb_can_collapse(to, from));
पूर्ण

/* Events passed to congestion control पूर्णांकerface */
क्रमागत tcp_ca_event अणु
	CA_EVENT_TX_START,	/* first transmit when no packets in flight */
	CA_EVENT_CWND_RESTART,	/* congestion winकरोw restart */
	CA_EVENT_COMPLETE_CWR,	/* end of congestion recovery */
	CA_EVENT_LOSS,		/* loss समयout */
	CA_EVENT_ECN_NO_CE,	/* ECT set, but not CE marked */
	CA_EVENT_ECN_IS_CE,	/* received CE marked IP packet */
पूर्ण;

/* Inक्रमmation about inbound ACK, passed to cong_ops->in_ack_event() */
क्रमागत tcp_ca_ack_event_flags अणु
	CA_ACK_SLOWPATH		= (1 << 0),	/* In slow path processing */
	CA_ACK_WIN_UPDATE	= (1 << 1),	/* ACK updated winकरोw */
	CA_ACK_ECE		= (1 << 2),	/* ECE bit is set on ack */
पूर्ण;

/*
 * Interface क्रम adding new TCP congestion control handlers
 */
#घोषणा TCP_CA_NAME_MAX	16
#घोषणा TCP_CA_MAX	128
#घोषणा TCP_CA_BUF_MAX	(TCP_CA_NAME_MAX*TCP_CA_MAX)

#घोषणा TCP_CA_UNSPEC	0

/* Algorithm can be set on socket without CAP_NET_ADMIN privileges */
#घोषणा TCP_CONG_NON_RESTRICTED 0x1
/* Requires ECN/ECT set on all packets */
#घोषणा TCP_CONG_NEEDS_ECN	0x2
#घोषणा TCP_CONG_MASK	(TCP_CONG_NON_RESTRICTED | TCP_CONG_NEEDS_ECN)

जोड़ tcp_cc_info;

काष्ठा ack_sample अणु
	u32 pkts_acked;
	s32 rtt_us;
	u32 in_flight;
पूर्ण;

/* A rate sample measures the number of (original/retransmitted) data
 * packets delivered "delivered" over an पूर्णांकerval of समय "interval_us".
 * The tcp_rate.c code fills in the rate sample, and congestion
 * control modules that define a cong_control function to run at the end
 * of ACK processing can optionally chose to consult this sample when
 * setting cwnd and pacing rate.
 * A sample is invalid अगर "delivered" or "interval_us" is negative.
 */
काष्ठा rate_sample अणु
	u64  prior_mstamp; /* starting बारtamp क्रम पूर्णांकerval */
	u32  prior_delivered;	/* tp->delivered at "prior_mstamp" */
	s32  delivered;		/* number of packets delivered over पूर्णांकerval */
	दीर्घ पूर्णांकerval_us;	/* समय क्रम tp->delivered to incr "delivered" */
	u32 snd_पूर्णांकerval_us;	/* snd पूर्णांकerval क्रम delivered packets */
	u32 rcv_पूर्णांकerval_us;	/* rcv पूर्णांकerval क्रम delivered packets */
	दीर्घ rtt_us;		/* RTT of last (S)ACKed packet (or -1) */
	पूर्णांक  losses;		/* number of packets marked lost upon ACK */
	u32  acked_sacked;	/* number of packets newly (S)ACKed upon ACK */
	u32  prior_in_flight;	/* in flight beक्रमe this ACK */
	bool is_app_limited;	/* is sample from packet with bubble in pipe? */
	bool is_retrans;	/* is sample from retransmission? */
	bool is_ack_delayed;	/* is this (likely) a delayed ACK? */
पूर्ण;

काष्ठा tcp_congestion_ops अणु
/* fast path fields are put first to fill one cache line */

	/* वापस slow start threshold (required) */
	u32 (*ssthresh)(काष्ठा sock *sk);

	/* करो new cwnd calculation (required) */
	व्योम (*cong_aव्योम)(काष्ठा sock *sk, u32 ack, u32 acked);

	/* call beक्रमe changing ca_state (optional) */
	व्योम (*set_state)(काष्ठा sock *sk, u8 new_state);

	/* call when cwnd event occurs (optional) */
	व्योम (*cwnd_event)(काष्ठा sock *sk, क्रमागत tcp_ca_event ev);

	/* call when ack arrives (optional) */
	व्योम (*in_ack_event)(काष्ठा sock *sk, u32 flags);

	/* hook क्रम packet ack accounting (optional) */
	व्योम (*pkts_acked)(काष्ठा sock *sk, स्थिर काष्ठा ack_sample *sample);

	/* override sysctl_tcp_min_tso_segs */
	u32 (*min_tso_segs)(काष्ठा sock *sk);

	/* call when packets are delivered to update cwnd and pacing rate,
	 * after all the ca_state processing. (optional)
	 */
	व्योम (*cong_control)(काष्ठा sock *sk, स्थिर काष्ठा rate_sample *rs);


	/* new value of cwnd after loss (required) */
	u32  (*unकरो_cwnd)(काष्ठा sock *sk);
	/* वापसs the multiplier used in tcp_sndbuf_expand (optional) */
	u32 (*sndbuf_expand)(काष्ठा sock *sk);

/* control/slow paths put last */
	/* get info क्रम inet_diag (optional) */
	माप_प्रकार (*get_info)(काष्ठा sock *sk, u32 ext, पूर्णांक *attr,
			   जोड़ tcp_cc_info *info);

	अक्षर 			name[TCP_CA_NAME_MAX];
	काष्ठा module		*owner;
	काष्ठा list_head	list;
	u32			key;
	u32			flags;

	/* initialize निजी data (optional) */
	व्योम (*init)(काष्ठा sock *sk);
	/* cleanup निजी data  (optional) */
	व्योम (*release)(काष्ठा sock *sk);
पूर्ण ____cacheline_aligned_in_smp;

पूर्णांक tcp_रेजिस्टर_congestion_control(काष्ठा tcp_congestion_ops *type);
व्योम tcp_unरेजिस्टर_congestion_control(काष्ठा tcp_congestion_ops *type);

व्योम tcp_assign_congestion_control(काष्ठा sock *sk);
व्योम tcp_init_congestion_control(काष्ठा sock *sk);
व्योम tcp_cleanup_congestion_control(काष्ठा sock *sk);
पूर्णांक tcp_set_शेष_congestion_control(काष्ठा net *net, स्थिर अक्षर *name);
व्योम tcp_get_शेष_congestion_control(काष्ठा net *net, अक्षर *name);
व्योम tcp_get_available_congestion_control(अक्षर *buf, माप_प्रकार len);
व्योम tcp_get_allowed_congestion_control(अक्षर *buf, माप_प्रकार len);
पूर्णांक tcp_set_allowed_congestion_control(अक्षर *allowed);
पूर्णांक tcp_set_congestion_control(काष्ठा sock *sk, स्थिर अक्षर *name, bool load,
			       bool cap_net_admin);
u32 tcp_slow_start(काष्ठा tcp_sock *tp, u32 acked);
व्योम tcp_cong_aव्योम_ai(काष्ठा tcp_sock *tp, u32 w, u32 acked);

u32 tcp_reno_ssthresh(काष्ठा sock *sk);
u32 tcp_reno_unकरो_cwnd(काष्ठा sock *sk);
व्योम tcp_reno_cong_aव्योम(काष्ठा sock *sk, u32 ack, u32 acked);
बाह्य काष्ठा tcp_congestion_ops tcp_reno;

काष्ठा tcp_congestion_ops *tcp_ca_find(स्थिर अक्षर *name);
काष्ठा tcp_congestion_ops *tcp_ca_find_key(u32 key);
u32 tcp_ca_get_key_by_name(काष्ठा net *net, स्थिर अक्षर *name, bool *ecn_ca);
#अगर_घोषित CONFIG_INET
अक्षर *tcp_ca_get_name_by_key(u32 key, अक्षर *buffer);
#अन्यथा
अटल अंतरभूत अक्षर *tcp_ca_get_name_by_key(u32 key, अक्षर *buffer)
अणु
	वापस शून्य;
पूर्ण
#पूर्ण_अगर

अटल अंतरभूत bool tcp_ca_needs_ecn(स्थिर काष्ठा sock *sk)
अणु
	स्थिर काष्ठा inet_connection_sock *icsk = inet_csk(sk);

	वापस icsk->icsk_ca_ops->flags & TCP_CONG_NEEDS_ECN;
पूर्ण

अटल अंतरभूत व्योम tcp_set_ca_state(काष्ठा sock *sk, स्थिर u8 ca_state)
अणु
	काष्ठा inet_connection_sock *icsk = inet_csk(sk);

	अगर (icsk->icsk_ca_ops->set_state)
		icsk->icsk_ca_ops->set_state(sk, ca_state);
	icsk->icsk_ca_state = ca_state;
पूर्ण

अटल अंतरभूत व्योम tcp_ca_event(काष्ठा sock *sk, स्थिर क्रमागत tcp_ca_event event)
अणु
	स्थिर काष्ठा inet_connection_sock *icsk = inet_csk(sk);

	अगर (icsk->icsk_ca_ops->cwnd_event)
		icsk->icsk_ca_ops->cwnd_event(sk, event);
पूर्ण

/* From tcp_rate.c */
व्योम tcp_rate_skb_sent(काष्ठा sock *sk, काष्ठा sk_buff *skb);
व्योम tcp_rate_skb_delivered(काष्ठा sock *sk, काष्ठा sk_buff *skb,
			    काष्ठा rate_sample *rs);
व्योम tcp_rate_gen(काष्ठा sock *sk, u32 delivered, u32 lost,
		  bool is_sack_reneg, काष्ठा rate_sample *rs);
व्योम tcp_rate_check_app_limited(काष्ठा sock *sk);

/* These functions determine how the current flow behaves in respect of SACK
 * handling. SACK is negotiated with the peer, and thereक्रमe it can vary
 * between dअगरferent flows.
 *
 * tcp_is_sack - SACK enabled
 * tcp_is_reno - No SACK
 */
अटल अंतरभूत पूर्णांक tcp_is_sack(स्थिर काष्ठा tcp_sock *tp)
अणु
	वापस likely(tp->rx_opt.sack_ok);
पूर्ण

अटल अंतरभूत bool tcp_is_reno(स्थिर काष्ठा tcp_sock *tp)
अणु
	वापस !tcp_is_sack(tp);
पूर्ण

अटल अंतरभूत अचिन्हित पूर्णांक tcp_left_out(स्थिर काष्ठा tcp_sock *tp)
अणु
	वापस tp->sacked_out + tp->lost_out;
पूर्ण

/* This determines how many packets are "in the network" to the best
 * of our knowledge.  In many हालs it is conservative, but where
 * detailed inक्रमmation is available from the receiver (via SACK
 * blocks etc.) we can make more aggressive calculations.
 *
 * Use this क्रम decisions involving congestion control, use just
 * tp->packets_out to determine अगर the send queue is empty or not.
 *
 * Read this equation as:
 *
 *	"Packets sent once on transmission queue" MINUS
 *	"Packets left network, but not honestly ACKed yet" PLUS
 *	"Packets fast retransmitted"
 */
अटल अंतरभूत अचिन्हित पूर्णांक tcp_packets_in_flight(स्थिर काष्ठा tcp_sock *tp)
अणु
	वापस tp->packets_out - tcp_left_out(tp) + tp->retrans_out;
पूर्ण

#घोषणा TCP_INFINITE_SSTHRESH	0x7fffffff

अटल अंतरभूत bool tcp_in_slow_start(स्थिर काष्ठा tcp_sock *tp)
अणु
	वापस tp->snd_cwnd < tp->snd_ssthresh;
पूर्ण

अटल अंतरभूत bool tcp_in_initial_slowstart(स्थिर काष्ठा tcp_sock *tp)
अणु
	वापस tp->snd_ssthresh >= TCP_INFINITE_SSTHRESH;
पूर्ण

अटल अंतरभूत bool tcp_in_cwnd_reduction(स्थिर काष्ठा sock *sk)
अणु
	वापस (TCPF_CA_CWR | TCPF_CA_Recovery) &
	       (1 << inet_csk(sk)->icsk_ca_state);
पूर्ण

/* If cwnd > ssthresh, we may उठाओ ssthresh to be half-way to cwnd.
 * The exception is cwnd reduction phase, when cwnd is decreasing towards
 * ssthresh.
 */
अटल अंतरभूत __u32 tcp_current_ssthresh(स्थिर काष्ठा sock *sk)
अणु
	स्थिर काष्ठा tcp_sock *tp = tcp_sk(sk);

	अगर (tcp_in_cwnd_reduction(sk))
		वापस tp->snd_ssthresh;
	अन्यथा
		वापस max(tp->snd_ssthresh,
			   ((tp->snd_cwnd >> 1) +
			    (tp->snd_cwnd >> 2)));
पूर्ण

/* Use define here पूर्णांकentionally to get WARN_ON location shown at the caller */
#घोषणा tcp_verअगरy_left_out(tp)	WARN_ON(tcp_left_out(tp) > tp->packets_out)

व्योम tcp_enter_cwr(काष्ठा sock *sk);
__u32 tcp_init_cwnd(स्थिर काष्ठा tcp_sock *tp, स्थिर काष्ठा dst_entry *dst);

/* The maximum number of MSS of available cwnd क्रम which TSO defers
 * sending अगर not using sysctl_tcp_tso_win_भागisor.
 */
अटल अंतरभूत __u32 tcp_max_tso_deferred_mss(स्थिर काष्ठा tcp_sock *tp)
अणु
	वापस 3;
पूर्ण

/* Returns end sequence number of the receiver's advertised winकरोw */
अटल अंतरभूत u32 tcp_wnd_end(स्थिर काष्ठा tcp_sock *tp)
अणु
	वापस tp->snd_una + tp->snd_wnd;
पूर्ण

/* We follow the spirit of RFC2861 to validate cwnd but implement a more
 * flexible approach. The RFC suggests cwnd should not be उठाओd unless
 * it was fully used previously. And that's exactly what we करो in
 * congestion aव्योमance mode. But in slow start we allow cwnd to grow
 * as दीर्घ as the application has used half the cwnd.
 * Example :
 *    cwnd is 10 (IW10), but application sends 9 frames.
 *    We allow cwnd to reach 18 when all frames are ACKed.
 * This check is safe because it's as aggressive as slow start which alपढ़ोy
 * risks 100% overshoot. The advantage is that we discourage application to
 * either send more filler packets or data to artअगरicially blow up the cwnd
 * usage, and allow application-limited process to probe bw more aggressively.
 */
अटल अंतरभूत bool tcp_is_cwnd_limited(स्थिर काष्ठा sock *sk)
अणु
	स्थिर काष्ठा tcp_sock *tp = tcp_sk(sk);

	/* If in slow start, ensure cwnd grows to twice what was ACKed. */
	अगर (tcp_in_slow_start(tp))
		वापस tp->snd_cwnd < 2 * tp->max_packets_out;

	वापस tp->is_cwnd_limited;
पूर्ण

/* BBR congestion control needs pacing.
 * Same remark क्रम SO_MAX_PACING_RATE.
 * sch_fq packet scheduler is efficiently handling pacing,
 * but is not always installed/used.
 * Return true अगर TCP stack should pace packets itself.
 */
अटल अंतरभूत bool tcp_needs_पूर्णांकernal_pacing(स्थिर काष्ठा sock *sk)
अणु
	वापस smp_load_acquire(&sk->sk_pacing_status) == SK_PACING_NEEDED;
पूर्ण

/* Estimates in how many jअगरfies next packet क्रम this flow can be sent.
 * Scheduling a retransmit समयr too early would be silly.
 */
अटल अंतरभूत अचिन्हित दीर्घ tcp_pacing_delay(स्थिर काष्ठा sock *sk)
अणु
	s64 delay = tcp_sk(sk)->tcp_wstamp_ns - tcp_sk(sk)->tcp_घड़ी_cache;

	वापस delay > 0 ? nsecs_to_jअगरfies(delay) : 0;
पूर्ण

अटल अंतरभूत व्योम tcp_reset_xmit_समयr(काष्ठा sock *sk,
					स्थिर पूर्णांक what,
					अचिन्हित दीर्घ when,
					स्थिर अचिन्हित दीर्घ max_when)
अणु
	inet_csk_reset_xmit_समयr(sk, what, when + tcp_pacing_delay(sk),
				  max_when);
पूर्ण

/* Something is really bad, we could not queue an additional packet,
 * because qdisc is full or receiver sent a 0 winकरोw, or we are paced.
 * We करो not want to add fuel to the fire, or पात too early,
 * so make sure the समयr we arm now is at least 200ms in the future,
 * regardless of current icsk_rto value (as it could be ~2ms)
 */
अटल अंतरभूत अचिन्हित दीर्घ tcp_probe0_base(स्थिर काष्ठा sock *sk)
अणु
	वापस max_t(अचिन्हित दीर्घ, inet_csk(sk)->icsk_rto, TCP_RTO_MIN);
पूर्ण

/* Variant of inet_csk_rto_backoff() used क्रम zero winकरोw probes */
अटल अंतरभूत अचिन्हित दीर्घ tcp_probe0_when(स्थिर काष्ठा sock *sk,
					    अचिन्हित दीर्घ max_when)
अणु
	u8 backoff = min_t(u8, ilog2(TCP_RTO_MAX / TCP_RTO_MIN) + 1,
			   inet_csk(sk)->icsk_backoff);
	u64 when = (u64)tcp_probe0_base(sk) << backoff;

	वापस (अचिन्हित दीर्घ)min_t(u64, when, max_when);
पूर्ण

अटल अंतरभूत व्योम tcp_check_probe_समयr(काष्ठा sock *sk)
अणु
	अगर (!tcp_sk(sk)->packets_out && !inet_csk(sk)->icsk_pending)
		tcp_reset_xmit_समयr(sk, ICSK_TIME_PROBE0,
				     tcp_probe0_base(sk), TCP_RTO_MAX);
पूर्ण

अटल अंतरभूत व्योम tcp_init_wl(काष्ठा tcp_sock *tp, u32 seq)
अणु
	tp->snd_wl1 = seq;
पूर्ण

अटल अंतरभूत व्योम tcp_update_wl(काष्ठा tcp_sock *tp, u32 seq)
अणु
	tp->snd_wl1 = seq;
पूर्ण

/*
 * Calculate(/check) TCP checksum
 */
अटल अंतरभूत __sum16 tcp_v4_check(पूर्णांक len, __be32 saddr,
				   __be32 daddr, __wsum base)
अणु
	वापस csum_tcpudp_magic(saddr, daddr, len, IPPROTO_TCP, base);
पूर्ण

अटल अंतरभूत bool tcp_checksum_complete(काष्ठा sk_buff *skb)
अणु
	वापस !skb_csum_unnecessary(skb) &&
		__skb_checksum_complete(skb);
पूर्ण

bool tcp_add_backlog(काष्ठा sock *sk, काष्ठा sk_buff *skb);
पूर्णांक tcp_filter(काष्ठा sock *sk, काष्ठा sk_buff *skb);
व्योम tcp_set_state(काष्ठा sock *sk, पूर्णांक state);
व्योम tcp_करोne(काष्ठा sock *sk);
पूर्णांक tcp_पात(काष्ठा sock *sk, पूर्णांक err);

अटल अंतरभूत व्योम tcp_sack_reset(काष्ठा tcp_options_received *rx_opt)
अणु
	rx_opt->dsack = 0;
	rx_opt->num_sacks = 0;
पूर्ण

व्योम tcp_cwnd_restart(काष्ठा sock *sk, s32 delta);

अटल अंतरभूत व्योम tcp_slow_start_after_idle_check(काष्ठा sock *sk)
अणु
	स्थिर काष्ठा tcp_congestion_ops *ca_ops = inet_csk(sk)->icsk_ca_ops;
	काष्ठा tcp_sock *tp = tcp_sk(sk);
	s32 delta;

	अगर (!sock_net(sk)->ipv4.sysctl_tcp_slow_start_after_idle || tp->packets_out ||
	    ca_ops->cong_control)
		वापस;
	delta = tcp_jअगरfies32 - tp->lsndसमय;
	अगर (delta > inet_csk(sk)->icsk_rto)
		tcp_cwnd_restart(sk, delta);
पूर्ण

/* Determine a winकरोw scaling and initial winकरोw to offer. */
व्योम tcp_select_initial_winकरोw(स्थिर काष्ठा sock *sk, पूर्णांक __space,
			       __u32 mss, __u32 *rcv_wnd,
			       __u32 *winकरोw_clamp, पूर्णांक wscale_ok,
			       __u8 *rcv_wscale, __u32 init_rcv_wnd);

अटल अंतरभूत पूर्णांक tcp_win_from_space(स्थिर काष्ठा sock *sk, पूर्णांक space)
अणु
	पूर्णांक tcp_adv_win_scale = sock_net(sk)->ipv4.sysctl_tcp_adv_win_scale;

	वापस tcp_adv_win_scale <= 0 ?
		(space>>(-tcp_adv_win_scale)) :
		space - (space>>tcp_adv_win_scale);
पूर्ण

/* Note: caller must be prepared to deal with negative वापसs */
अटल अंतरभूत पूर्णांक tcp_space(स्थिर काष्ठा sock *sk)
अणु
	वापस tcp_win_from_space(sk, READ_ONCE(sk->sk_rcvbuf) -
				  READ_ONCE(sk->sk_backlog.len) -
				  atomic_पढ़ो(&sk->sk_rmem_alloc));
पूर्ण

अटल अंतरभूत पूर्णांक tcp_full_space(स्थिर काष्ठा sock *sk)
अणु
	वापस tcp_win_from_space(sk, READ_ONCE(sk->sk_rcvbuf));
पूर्ण

व्योम tcp_cleanup_rbuf(काष्ठा sock *sk, पूर्णांक copied);

/* We provision sk_rcvbuf around 200% of sk_rcvlowat.
 * If 87.5 % (7/8) of the space has been consumed, we want to override
 * SO_RCVLOWAT स्थिरraपूर्णांक, since we are receiving skbs with too small
 * len/truesize ratio.
 */
अटल अंतरभूत bool tcp_rmem_pressure(स्थिर काष्ठा sock *sk)
अणु
	पूर्णांक rcvbuf, threshold;

	अगर (tcp_under_memory_pressure(sk))
		वापस true;

	rcvbuf = READ_ONCE(sk->sk_rcvbuf);
	threshold = rcvbuf - (rcvbuf >> 3);

	वापस atomic_पढ़ो(&sk->sk_rmem_alloc) > threshold;
पूर्ण

अटल अंतरभूत bool tcp_epollin_पढ़ोy(स्थिर काष्ठा sock *sk, पूर्णांक target)
अणु
	स्थिर काष्ठा tcp_sock *tp = tcp_sk(sk);
	पूर्णांक avail = READ_ONCE(tp->rcv_nxt) - READ_ONCE(tp->copied_seq);

	अगर (avail <= 0)
		वापस false;

	वापस (avail >= target) || tcp_rmem_pressure(sk) ||
	       (tcp_receive_winकरोw(tp) <= inet_csk(sk)->icsk_ack.rcv_mss);
पूर्ण

बाह्य व्योम tcp_खोलोreq_init_rwin(काष्ठा request_sock *req,
				  स्थिर काष्ठा sock *sk_listener,
				  स्थिर काष्ठा dst_entry *dst);

व्योम tcp_enter_memory_pressure(काष्ठा sock *sk);
व्योम tcp_leave_memory_pressure(काष्ठा sock *sk);

अटल अंतरभूत पूर्णांक keepalive_पूर्णांकvl_when(स्थिर काष्ठा tcp_sock *tp)
अणु
	काष्ठा net *net = sock_net((काष्ठा sock *)tp);

	वापस tp->keepalive_पूर्णांकvl ? : net->ipv4.sysctl_tcp_keepalive_पूर्णांकvl;
पूर्ण

अटल अंतरभूत पूर्णांक keepalive_समय_when(स्थिर काष्ठा tcp_sock *tp)
अणु
	काष्ठा net *net = sock_net((काष्ठा sock *)tp);

	वापस tp->keepalive_समय ? : net->ipv4.sysctl_tcp_keepalive_समय;
पूर्ण

अटल अंतरभूत पूर्णांक keepalive_probes(स्थिर काष्ठा tcp_sock *tp)
अणु
	काष्ठा net *net = sock_net((काष्ठा sock *)tp);

	वापस tp->keepalive_probes ? : net->ipv4.sysctl_tcp_keepalive_probes;
पूर्ण

अटल अंतरभूत u32 keepalive_समय_elapsed(स्थिर काष्ठा tcp_sock *tp)
अणु
	स्थिर काष्ठा inet_connection_sock *icsk = &tp->inet_conn;

	वापस min_t(u32, tcp_jअगरfies32 - icsk->icsk_ack.lrcvसमय,
			  tcp_jअगरfies32 - tp->rcv_tstamp);
पूर्ण

अटल अंतरभूत पूर्णांक tcp_fin_समय(स्थिर काष्ठा sock *sk)
अणु
	पूर्णांक fin_समयout = tcp_sk(sk)->linger2 ? : sock_net(sk)->ipv4.sysctl_tcp_fin_समयout;
	स्थिर पूर्णांक rto = inet_csk(sk)->icsk_rto;

	अगर (fin_समयout < (rto << 2) - (rto >> 1))
		fin_समयout = (rto << 2) - (rto >> 1);

	वापस fin_समयout;
पूर्ण

अटल अंतरभूत bool tcp_paws_check(स्थिर काष्ठा tcp_options_received *rx_opt,
				  पूर्णांक paws_win)
अणु
	अगर ((s32)(rx_opt->ts_recent - rx_opt->rcv_tsval) <= paws_win)
		वापस true;
	अगर (unlikely(!समय_beक्रमe32(kसमय_get_seconds(),
				    rx_opt->ts_recent_stamp + TCP_PAWS_24DAYS)))
		वापस true;
	/*
	 * Some OSes send SYN and SYNACK messages with tsval=0 tsecr=0,
	 * then following tcp messages have valid values. Ignore 0 value,
	 * or अन्यथा 'negative' tsval might क्रमbid us to accept their packets.
	 */
	अगर (!rx_opt->ts_recent)
		वापस true;
	वापस false;
पूर्ण

अटल अंतरभूत bool tcp_paws_reject(स्थिर काष्ठा tcp_options_received *rx_opt,
				   पूर्णांक rst)
अणु
	अगर (tcp_paws_check(rx_opt, 0))
		वापस false;

	/* RST segments are not recommended to carry बारtamp,
	   and, अगर they करो, it is recommended to ignore PAWS because
	   "their cleanup function should take precedence over timestamps."
	   Certainly, it is mistake. It is necessary to understand the reasons
	   of this स्थिरraपूर्णांक to relax it: अगर peer reboots, घड़ी may go
	   out-of-sync and half-खोलो connections will not be reset.
	   Actually, the problem would be not existing अगर all
	   the implementations followed draft about मुख्यtaining घड़ी
	   via reboots. Linux-2.2 DOES NOT!

	   However, we can relax समय bounds क्रम RST segments to MSL.
	 */
	अगर (rst && !समय_beक्रमe32(kसमय_get_seconds(),
				  rx_opt->ts_recent_stamp + TCP_PAWS_MSL))
		वापस false;
	वापस true;
पूर्ण

bool tcp_oow_rate_limited(काष्ठा net *net, स्थिर काष्ठा sk_buff *skb,
			  पूर्णांक mib_idx, u32 *last_oow_ack_समय);

अटल अंतरभूत व्योम tcp_mib_init(काष्ठा net *net)
अणु
	/* See RFC 2012 */
	TCP_ADD_STATS(net, TCP_MIB_RTOALGORITHM, 1);
	TCP_ADD_STATS(net, TCP_MIB_RTOMIN, TCP_RTO_MIN*1000/HZ);
	TCP_ADD_STATS(net, TCP_MIB_RTOMAX, TCP_RTO_MAX*1000/HZ);
	TCP_ADD_STATS(net, TCP_MIB_MAXCONN, -1);
पूर्ण

/* from STCP */
अटल अंतरभूत व्योम tcp_clear_retrans_hपूर्णांकs_partial(काष्ठा tcp_sock *tp)
अणु
	tp->lost_skb_hपूर्णांक = शून्य;
पूर्ण

अटल अंतरभूत व्योम tcp_clear_all_retrans_hपूर्णांकs(काष्ठा tcp_sock *tp)
अणु
	tcp_clear_retrans_hपूर्णांकs_partial(tp);
	tp->retransmit_skb_hपूर्णांक = शून्य;
पूर्ण

जोड़ tcp_md5_addr अणु
	काष्ठा in_addr  a4;
#अगर IS_ENABLED(CONFIG_IPV6)
	काष्ठा in6_addr	a6;
#पूर्ण_अगर
पूर्ण;

/* - key database */
काष्ठा tcp_md5sig_key अणु
	काष्ठा hlist_node	node;
	u8			keylen;
	u8			family; /* AF_INET or AF_INET6 */
	u8			prefixlen;
	जोड़ tcp_md5_addr	addr;
	पूर्णांक			l3index; /* set अगर key added with L3 scope */
	u8			key[TCP_MD5SIG_MAXKEYLEN];
	काष्ठा rcu_head		rcu;
पूर्ण;

/* - sock block */
काष्ठा tcp_md5sig_info अणु
	काष्ठा hlist_head	head;
	काष्ठा rcu_head		rcu;
पूर्ण;

/* - pseuकरो header */
काष्ठा tcp4_pseuकरोhdr अणु
	__be32		saddr;
	__be32		daddr;
	__u8		pad;
	__u8		protocol;
	__be16		len;
पूर्ण;

काष्ठा tcp6_pseuकरोhdr अणु
	काष्ठा in6_addr	saddr;
	काष्ठा in6_addr daddr;
	__be32		len;
	__be32		protocol;	/* including padding */
पूर्ण;

जोड़ tcp_md5sum_block अणु
	काष्ठा tcp4_pseuकरोhdr ip4;
#अगर IS_ENABLED(CONFIG_IPV6)
	काष्ठा tcp6_pseuकरोhdr ip6;
#पूर्ण_अगर
पूर्ण;

/* - pool: digest algorithm, hash description and scratch buffer */
काष्ठा tcp_md5sig_pool अणु
	काष्ठा ahash_request	*md5_req;
	व्योम			*scratch;
पूर्ण;

/* - functions */
पूर्णांक tcp_v4_md5_hash_skb(अक्षर *md5_hash, स्थिर काष्ठा tcp_md5sig_key *key,
			स्थिर काष्ठा sock *sk, स्थिर काष्ठा sk_buff *skb);
पूर्णांक tcp_md5_करो_add(काष्ठा sock *sk, स्थिर जोड़ tcp_md5_addr *addr,
		   पूर्णांक family, u8 prefixlen, पूर्णांक l3index,
		   स्थिर u8 *newkey, u8 newkeylen, gfp_t gfp);
पूर्णांक tcp_md5_करो_del(काष्ठा sock *sk, स्थिर जोड़ tcp_md5_addr *addr,
		   पूर्णांक family, u8 prefixlen, पूर्णांक l3index);
काष्ठा tcp_md5sig_key *tcp_v4_md5_lookup(स्थिर काष्ठा sock *sk,
					 स्थिर काष्ठा sock *addr_sk);

#अगर_घोषित CONFIG_TCP_MD5SIG
#समावेश <linux/jump_label.h>
बाह्य काष्ठा अटल_key_false tcp_md5_needed;
काष्ठा tcp_md5sig_key *__tcp_md5_करो_lookup(स्थिर काष्ठा sock *sk, पूर्णांक l3index,
					   स्थिर जोड़ tcp_md5_addr *addr,
					   पूर्णांक family);
अटल अंतरभूत काष्ठा tcp_md5sig_key *
tcp_md5_करो_lookup(स्थिर काष्ठा sock *sk, पूर्णांक l3index,
		  स्थिर जोड़ tcp_md5_addr *addr, पूर्णांक family)
अणु
	अगर (!अटल_branch_unlikely(&tcp_md5_needed))
		वापस शून्य;
	वापस __tcp_md5_करो_lookup(sk, l3index, addr, family);
पूर्ण

#घोषणा tcp_twsk_md5_key(twsk)	((twsk)->tw_md5_key)
#अन्यथा
अटल अंतरभूत काष्ठा tcp_md5sig_key *
tcp_md5_करो_lookup(स्थिर काष्ठा sock *sk, पूर्णांक l3index,
		  स्थिर जोड़ tcp_md5_addr *addr, पूर्णांक family)
अणु
	वापस शून्य;
पूर्ण
#घोषणा tcp_twsk_md5_key(twsk)	शून्य
#पूर्ण_अगर

bool tcp_alloc_md5sig_pool(व्योम);

काष्ठा tcp_md5sig_pool *tcp_get_md5sig_pool(व्योम);
अटल अंतरभूत व्योम tcp_put_md5sig_pool(व्योम)
अणु
	local_bh_enable();
पूर्ण

पूर्णांक tcp_md5_hash_skb_data(काष्ठा tcp_md5sig_pool *, स्थिर काष्ठा sk_buff *,
			  अचिन्हित पूर्णांक header_len);
पूर्णांक tcp_md5_hash_key(काष्ठा tcp_md5sig_pool *hp,
		     स्थिर काष्ठा tcp_md5sig_key *key);

/* From tcp_fastखोलो.c */
व्योम tcp_fastखोलो_cache_get(काष्ठा sock *sk, u16 *mss,
			    काष्ठा tcp_fastखोलो_cookie *cookie);
व्योम tcp_fastखोलो_cache_set(काष्ठा sock *sk, u16 mss,
			    काष्ठा tcp_fastखोलो_cookie *cookie, bool syn_lost,
			    u16 try_exp);
काष्ठा tcp_fastखोलो_request अणु
	/* Fast Open cookie. Size 0 means a cookie request */
	काष्ठा tcp_fastखोलो_cookie	cookie;
	काष्ठा msghdr			*data;  /* data in MSG_FASTOPEN */
	माप_प्रकार				size;
	पूर्णांक				copied;	/* queued in tcp_connect() */
	काष्ठा ubuf_info		*uarg;
पूर्ण;
व्योम tcp_मुक्त_fastखोलो_req(काष्ठा tcp_sock *tp);
व्योम tcp_fastखोलो_destroy_cipher(काष्ठा sock *sk);
व्योम tcp_fastखोलो_ctx_destroy(काष्ठा net *net);
पूर्णांक tcp_fastखोलो_reset_cipher(काष्ठा net *net, काष्ठा sock *sk,
			      व्योम *primary_key, व्योम *backup_key);
पूर्णांक tcp_fastखोलो_get_cipher(काष्ठा net *net, काष्ठा inet_connection_sock *icsk,
			    u64 *key);
व्योम tcp_fastखोलो_add_skb(काष्ठा sock *sk, काष्ठा sk_buff *skb);
काष्ठा sock *tcp_try_fastखोलो(काष्ठा sock *sk, काष्ठा sk_buff *skb,
			      काष्ठा request_sock *req,
			      काष्ठा tcp_fastखोलो_cookie *foc,
			      स्थिर काष्ठा dst_entry *dst);
व्योम tcp_fastखोलो_init_key_once(काष्ठा net *net);
bool tcp_fastखोलो_cookie_check(काष्ठा sock *sk, u16 *mss,
			     काष्ठा tcp_fastखोलो_cookie *cookie);
bool tcp_fastखोलो_defer_connect(काष्ठा sock *sk, पूर्णांक *err);
#घोषणा TCP_FASTOPEN_KEY_LENGTH माप(siphash_key_t)
#घोषणा TCP_FASTOPEN_KEY_MAX 2
#घोषणा TCP_FASTOPEN_KEY_BUF_LENGTH \
	(TCP_FASTOPEN_KEY_LENGTH * TCP_FASTOPEN_KEY_MAX)

/* Fastखोलो key context */
काष्ठा tcp_fastखोलो_context अणु
	siphash_key_t	key[TCP_FASTOPEN_KEY_MAX];
	पूर्णांक		num;
	काष्ठा rcu_head	rcu;
पूर्ण;

बाह्य अचिन्हित पूर्णांक sysctl_tcp_fastखोलो_blackhole_समयout;
व्योम tcp_fastखोलो_active_disable(काष्ठा sock *sk);
bool tcp_fastखोलो_active_should_disable(काष्ठा sock *sk);
व्योम tcp_fastखोलो_active_disable_ofo_check(काष्ठा sock *sk);
व्योम tcp_fastखोलो_active_detect_blackhole(काष्ठा sock *sk, bool expired);

/* Caller needs to wrap with rcu_पढ़ो_(un)lock() */
अटल अंतरभूत
काष्ठा tcp_fastखोलो_context *tcp_fastखोलो_get_ctx(स्थिर काष्ठा sock *sk)
अणु
	काष्ठा tcp_fastखोलो_context *ctx;

	ctx = rcu_dereference(inet_csk(sk)->icsk_accept_queue.fastखोलोq.ctx);
	अगर (!ctx)
		ctx = rcu_dereference(sock_net(sk)->ipv4.tcp_fastखोलो_ctx);
	वापस ctx;
पूर्ण

अटल अंतरभूत
bool tcp_fastखोलो_cookie_match(स्थिर काष्ठा tcp_fastखोलो_cookie *foc,
			       स्थिर काष्ठा tcp_fastखोलो_cookie *orig)
अणु
	अगर (orig->len == TCP_FASTOPEN_COOKIE_SIZE &&
	    orig->len == foc->len &&
	    !स_भेद(orig->val, foc->val, foc->len))
		वापस true;
	वापस false;
पूर्ण

अटल अंतरभूत
पूर्णांक tcp_fastखोलो_context_len(स्थिर काष्ठा tcp_fastखोलो_context *ctx)
अणु
	वापस ctx->num;
पूर्ण

/* Latencies incurred by various limits क्रम a sender. They are
 * chronograph-like stats that are mutually exclusive.
 */
क्रमागत tcp_chrono अणु
	TCP_CHRONO_UNSPEC,
	TCP_CHRONO_BUSY, /* Actively sending data (non-empty ग_लिखो queue) */
	TCP_CHRONO_RWND_LIMITED, /* Stalled by insufficient receive winकरोw */
	TCP_CHRONO_SNDBUF_LIMITED, /* Stalled by insufficient send buffer */
	__TCP_CHRONO_MAX,
पूर्ण;

व्योम tcp_chrono_start(काष्ठा sock *sk, स्थिर क्रमागत tcp_chrono type);
व्योम tcp_chrono_stop(काष्ठा sock *sk, स्थिर क्रमागत tcp_chrono type);

/* This helper is needed, because skb->tcp_tsorted_anchor uses
 * the same memory storage than skb->deकाष्ठाor/_skb_refdst
 */
अटल अंतरभूत व्योम tcp_skb_tsorted_anchor_cleanup(काष्ठा sk_buff *skb)
अणु
	skb->deकाष्ठाor = शून्य;
	skb->_skb_refdst = 0UL;
पूर्ण

#घोषणा tcp_skb_tsorted_save(skb) अणु		\
	अचिन्हित दीर्घ _save = skb->_skb_refdst;	\
	skb->_skb_refdst = 0UL;

#घोषणा tcp_skb_tsorted_restore(skb)		\
	skb->_skb_refdst = _save;		\
पूर्ण

व्योम tcp_ग_लिखो_queue_purge(काष्ठा sock *sk);

अटल अंतरभूत काष्ठा sk_buff *tcp_rtx_queue_head(स्थिर काष्ठा sock *sk)
अणु
	वापस skb_rb_first(&sk->tcp_rtx_queue);
पूर्ण

अटल अंतरभूत काष्ठा sk_buff *tcp_rtx_queue_tail(स्थिर काष्ठा sock *sk)
अणु
	वापस skb_rb_last(&sk->tcp_rtx_queue);
पूर्ण

अटल अंतरभूत काष्ठा sk_buff *tcp_ग_लिखो_queue_head(स्थिर काष्ठा sock *sk)
अणु
	वापस skb_peek(&sk->sk_ग_लिखो_queue);
पूर्ण

अटल अंतरभूत काष्ठा sk_buff *tcp_ग_लिखो_queue_tail(स्थिर काष्ठा sock *sk)
अणु
	वापस skb_peek_tail(&sk->sk_ग_लिखो_queue);
पूर्ण

#घोषणा tcp_क्रम_ग_लिखो_queue_from_safe(skb, पंचांगp, sk)			\
	skb_queue_walk_from_safe(&(sk)->sk_ग_लिखो_queue, skb, पंचांगp)

अटल अंतरभूत काष्ठा sk_buff *tcp_send_head(स्थिर काष्ठा sock *sk)
अणु
	वापस skb_peek(&sk->sk_ग_लिखो_queue);
पूर्ण

अटल अंतरभूत bool tcp_skb_is_last(स्थिर काष्ठा sock *sk,
				   स्थिर काष्ठा sk_buff *skb)
अणु
	वापस skb_queue_is_last(&sk->sk_ग_लिखो_queue, skb);
पूर्ण

/**
 * tcp_ग_लिखो_queue_empty - test अगर any payload (or FIN) is available in ग_लिखो queue
 * @sk: socket
 *
 * Since the ग_लिखो queue can have a temporary empty skb in it,
 * we must not use "return skb_queue_empty(&sk->sk_write_queue)"
 */
अटल अंतरभूत bool tcp_ग_लिखो_queue_empty(स्थिर काष्ठा sock *sk)
अणु
	स्थिर काष्ठा tcp_sock *tp = tcp_sk(sk);

	वापस tp->ग_लिखो_seq == tp->snd_nxt;
पूर्ण

अटल अंतरभूत bool tcp_rtx_queue_empty(स्थिर काष्ठा sock *sk)
अणु
	वापस RB_EMPTY_ROOT(&sk->tcp_rtx_queue);
पूर्ण

अटल अंतरभूत bool tcp_rtx_and_ग_लिखो_queues_empty(स्थिर काष्ठा sock *sk)
अणु
	वापस tcp_rtx_queue_empty(sk) && tcp_ग_लिखो_queue_empty(sk);
पूर्ण

अटल अंतरभूत व्योम tcp_add_ग_लिखो_queue_tail(काष्ठा sock *sk, काष्ठा sk_buff *skb)
अणु
	__skb_queue_tail(&sk->sk_ग_लिखो_queue, skb);

	/* Queue it, remembering where we must start sending. */
	अगर (sk->sk_ग_लिखो_queue.next == skb)
		tcp_chrono_start(sk, TCP_CHRONO_BUSY);
पूर्ण

/* Insert new beक्रमe skb on the ग_लिखो queue of sk.  */
अटल अंतरभूत व्योम tcp_insert_ग_लिखो_queue_beक्रमe(काष्ठा sk_buff *new,
						  काष्ठा sk_buff *skb,
						  काष्ठा sock *sk)
अणु
	__skb_queue_beक्रमe(&sk->sk_ग_लिखो_queue, skb, new);
पूर्ण

अटल अंतरभूत व्योम tcp_unlink_ग_लिखो_queue(काष्ठा sk_buff *skb, काष्ठा sock *sk)
अणु
	tcp_skb_tsorted_anchor_cleanup(skb);
	__skb_unlink(skb, &sk->sk_ग_लिखो_queue);
पूर्ण

व्योम tcp_rbtree_insert(काष्ठा rb_root *root, काष्ठा sk_buff *skb);

अटल अंतरभूत व्योम tcp_rtx_queue_unlink(काष्ठा sk_buff *skb, काष्ठा sock *sk)
अणु
	tcp_skb_tsorted_anchor_cleanup(skb);
	rb_erase(&skb->rbnode, &sk->tcp_rtx_queue);
पूर्ण

अटल अंतरभूत व्योम tcp_rtx_queue_unlink_and_मुक्त(काष्ठा sk_buff *skb, काष्ठा sock *sk)
अणु
	list_del(&skb->tcp_tsorted_anchor);
	tcp_rtx_queue_unlink(skb, sk);
	sk_wmem_मुक्त_skb(sk, skb);
पूर्ण

अटल अंतरभूत व्योम tcp_push_pending_frames(काष्ठा sock *sk)
अणु
	अगर (tcp_send_head(sk)) अणु
		काष्ठा tcp_sock *tp = tcp_sk(sk);

		__tcp_push_pending_frames(sk, tcp_current_mss(sk), tp->nonagle);
	पूर्ण
पूर्ण

/* Start sequence of the skb just after the highest skb with SACKed
 * bit, valid only अगर sacked_out > 0 or when the caller has ensured
 * validity by itself.
 */
अटल अंतरभूत u32 tcp_highest_sack_seq(काष्ठा tcp_sock *tp)
अणु
	अगर (!tp->sacked_out)
		वापस tp->snd_una;

	अगर (tp->highest_sack == शून्य)
		वापस tp->snd_nxt;

	वापस TCP_SKB_CB(tp->highest_sack)->seq;
पूर्ण

अटल अंतरभूत व्योम tcp_advance_highest_sack(काष्ठा sock *sk, काष्ठा sk_buff *skb)
अणु
	tcp_sk(sk)->highest_sack = skb_rb_next(skb);
पूर्ण

अटल अंतरभूत काष्ठा sk_buff *tcp_highest_sack(काष्ठा sock *sk)
अणु
	वापस tcp_sk(sk)->highest_sack;
पूर्ण

अटल अंतरभूत व्योम tcp_highest_sack_reset(काष्ठा sock *sk)
अणु
	tcp_sk(sk)->highest_sack = tcp_rtx_queue_head(sk);
पूर्ण

/* Called when old skb is about to be deleted and replaced by new skb */
अटल अंतरभूत व्योम tcp_highest_sack_replace(काष्ठा sock *sk,
					    काष्ठा sk_buff *old,
					    काष्ठा sk_buff *new)
अणु
	अगर (old == tcp_highest_sack(sk))
		tcp_sk(sk)->highest_sack = new;
पूर्ण

/* This helper checks अगर socket has IP_TRANSPARENT set */
अटल अंतरभूत bool inet_sk_transparent(स्थिर काष्ठा sock *sk)
अणु
	चयन (sk->sk_state) अणु
	हाल TCP_TIME_WAIT:
		वापस inet_twsk(sk)->tw_transparent;
	हाल TCP_NEW_SYN_RECV:
		वापस inet_rsk(inet_reqsk(sk))->no_srccheck;
	पूर्ण
	वापस inet_sk(sk)->transparent;
पूर्ण

/* Determines whether this is a thin stream (which may suffer from
 * increased latency). Used to trigger latency-reducing mechanisms.
 */
अटल अंतरभूत bool tcp_stream_is_thin(काष्ठा tcp_sock *tp)
अणु
	वापस tp->packets_out < 4 && !tcp_in_initial_slowstart(tp);
पूर्ण

/* /proc */
क्रमागत tcp_seq_states अणु
	TCP_SEQ_STATE_LISTENING,
	TCP_SEQ_STATE_ESTABLISHED,
पूर्ण;

व्योम *tcp_seq_start(काष्ठा seq_file *seq, loff_t *pos);
व्योम *tcp_seq_next(काष्ठा seq_file *seq, व्योम *v, loff_t *pos);
व्योम tcp_seq_stop(काष्ठा seq_file *seq, व्योम *v);

काष्ठा tcp_seq_afinfo अणु
	sa_family_t			family;
पूर्ण;

काष्ठा tcp_iter_state अणु
	काष्ठा seq_net_निजी	p;
	क्रमागत tcp_seq_states	state;
	काष्ठा sock		*syn_रुको_sk;
	काष्ठा tcp_seq_afinfo	*bpf_seq_afinfo;
	पूर्णांक			bucket, offset, sbucket, num;
	loff_t			last_pos;
पूर्ण;

बाह्य काष्ठा request_sock_ops tcp_request_sock_ops;
बाह्य काष्ठा request_sock_ops tcp6_request_sock_ops;

व्योम tcp_v4_destroy_sock(काष्ठा sock *sk);

काष्ठा sk_buff *tcp_gso_segment(काष्ठा sk_buff *skb,
				netdev_features_t features);
काष्ठा sk_buff *tcp_gro_receive(काष्ठा list_head *head, काष्ठा sk_buff *skb);
INसूचीECT_CALLABLE_DECLARE(पूर्णांक tcp4_gro_complete(काष्ठा sk_buff *skb, पूर्णांक thoff));
INसूचीECT_CALLABLE_DECLARE(काष्ठा sk_buff *tcp4_gro_receive(काष्ठा list_head *head, काष्ठा sk_buff *skb));
INसूचीECT_CALLABLE_DECLARE(पूर्णांक tcp6_gro_complete(काष्ठा sk_buff *skb, पूर्णांक thoff));
INसूचीECT_CALLABLE_DECLARE(काष्ठा sk_buff *tcp6_gro_receive(काष्ठा list_head *head, काष्ठा sk_buff *skb));
पूर्णांक tcp_gro_complete(काष्ठा sk_buff *skb);

व्योम __tcp_v4_send_check(काष्ठा sk_buff *skb, __be32 saddr, __be32 daddr);

अटल अंतरभूत u32 tcp_notsent_lowat(स्थिर काष्ठा tcp_sock *tp)
अणु
	काष्ठा net *net = sock_net((काष्ठा sock *)tp);
	वापस tp->notsent_lowat ?: net->ipv4.sysctl_tcp_notsent_lowat;
पूर्ण

bool tcp_stream_memory_मुक्त(स्थिर काष्ठा sock *sk, पूर्णांक wake);

#अगर_घोषित CONFIG_PROC_FS
पूर्णांक tcp4_proc_init(व्योम);
व्योम tcp4_proc_निकास(व्योम);
#पूर्ण_अगर

पूर्णांक tcp_rtx_synack(स्थिर काष्ठा sock *sk, काष्ठा request_sock *req);
पूर्णांक tcp_conn_request(काष्ठा request_sock_ops *rsk_ops,
		     स्थिर काष्ठा tcp_request_sock_ops *af_ops,
		     काष्ठा sock *sk, काष्ठा sk_buff *skb);

/* TCP af-specअगरic functions */
काष्ठा tcp_sock_af_ops अणु
#अगर_घोषित CONFIG_TCP_MD5SIG
	काष्ठा tcp_md5sig_key	*(*md5_lookup) (स्थिर काष्ठा sock *sk,
						स्थिर काष्ठा sock *addr_sk);
	पूर्णांक		(*calc_md5_hash)(अक्षर *location,
					 स्थिर काष्ठा tcp_md5sig_key *md5,
					 स्थिर काष्ठा sock *sk,
					 स्थिर काष्ठा sk_buff *skb);
	पूर्णांक		(*md5_parse)(काष्ठा sock *sk,
				     पूर्णांक optname,
				     sockptr_t optval,
				     पूर्णांक optlen);
#पूर्ण_अगर
पूर्ण;

काष्ठा tcp_request_sock_ops अणु
	u16 mss_clamp;
#अगर_घोषित CONFIG_TCP_MD5SIG
	काष्ठा tcp_md5sig_key *(*req_md5_lookup)(स्थिर काष्ठा sock *sk,
						 स्थिर काष्ठा sock *addr_sk);
	पूर्णांक		(*calc_md5_hash) (अक्षर *location,
					  स्थिर काष्ठा tcp_md5sig_key *md5,
					  स्थिर काष्ठा sock *sk,
					  स्थिर काष्ठा sk_buff *skb);
#पूर्ण_अगर
#अगर_घोषित CONFIG_SYN_COOKIES
	__u32 (*cookie_init_seq)(स्थिर काष्ठा sk_buff *skb,
				 __u16 *mss);
#पूर्ण_अगर
	काष्ठा dst_entry *(*route_req)(स्थिर काष्ठा sock *sk,
				       काष्ठा sk_buff *skb,
				       काष्ठा flowi *fl,
				       काष्ठा request_sock *req);
	u32 (*init_seq)(स्थिर काष्ठा sk_buff *skb);
	u32 (*init_ts_off)(स्थिर काष्ठा net *net, स्थिर काष्ठा sk_buff *skb);
	पूर्णांक (*send_synack)(स्थिर काष्ठा sock *sk, काष्ठा dst_entry *dst,
			   काष्ठा flowi *fl, काष्ठा request_sock *req,
			   काष्ठा tcp_fastखोलो_cookie *foc,
			   क्रमागत tcp_synack_type synack_type,
			   काष्ठा sk_buff *syn_skb);
पूर्ण;

बाह्य स्थिर काष्ठा tcp_request_sock_ops tcp_request_sock_ipv4_ops;
#अगर IS_ENABLED(CONFIG_IPV6)
बाह्य स्थिर काष्ठा tcp_request_sock_ops tcp_request_sock_ipv6_ops;
#पूर्ण_अगर

#अगर_घोषित CONFIG_SYN_COOKIES
अटल अंतरभूत __u32 cookie_init_sequence(स्थिर काष्ठा tcp_request_sock_ops *ops,
					 स्थिर काष्ठा sock *sk, काष्ठा sk_buff *skb,
					 __u16 *mss)
अणु
	tcp_synq_overflow(sk);
	__NET_INC_STATS(sock_net(sk), LINUX_MIB_SYNCOOKIESSENT);
	वापस ops->cookie_init_seq(skb, mss);
पूर्ण
#अन्यथा
अटल अंतरभूत __u32 cookie_init_sequence(स्थिर काष्ठा tcp_request_sock_ops *ops,
					 स्थिर काष्ठा sock *sk, काष्ठा sk_buff *skb,
					 __u16 *mss)
अणु
	वापस 0;
पूर्ण
#पूर्ण_अगर

पूर्णांक tcpv4_offload_init(व्योम);

व्योम tcp_v4_init(व्योम);
व्योम tcp_init(व्योम);

/* tcp_recovery.c */
व्योम tcp_mark_skb_lost(काष्ठा sock *sk, काष्ठा sk_buff *skb);
व्योम tcp_newreno_mark_lost(काष्ठा sock *sk, bool snd_una_advanced);
बाह्य s32 tcp_rack_skb_समयout(काष्ठा tcp_sock *tp, काष्ठा sk_buff *skb,
				u32 reo_wnd);
बाह्य bool tcp_rack_mark_lost(काष्ठा sock *sk);
बाह्य व्योम tcp_rack_advance(काष्ठा tcp_sock *tp, u8 sacked, u32 end_seq,
			     u64 xmit_समय);
बाह्य व्योम tcp_rack_reo_समयout(काष्ठा sock *sk);
बाह्य व्योम tcp_rack_update_reo_wnd(काष्ठा sock *sk, काष्ठा rate_sample *rs);

/* At how many usecs पूर्णांकo the future should the RTO fire? */
अटल अंतरभूत s64 tcp_rto_delta_us(स्थिर काष्ठा sock *sk)
अणु
	स्थिर काष्ठा sk_buff *skb = tcp_rtx_queue_head(sk);
	u32 rto = inet_csk(sk)->icsk_rto;
	u64 rto_समय_stamp_us = tcp_skb_बारtamp_us(skb) + jअगरfies_to_usecs(rto);

	वापस rto_समय_stamp_us - tcp_sk(sk)->tcp_mstamp;
पूर्ण

/*
 * Save and compile IPv4 options, वापस a poपूर्णांकer to it
 */
अटल अंतरभूत काष्ठा ip_options_rcu *tcp_v4_save_options(काष्ठा net *net,
							 काष्ठा sk_buff *skb)
अणु
	स्थिर काष्ठा ip_options *opt = &TCP_SKB_CB(skb)->header.h4.opt;
	काष्ठा ip_options_rcu *करोpt = शून्य;

	अगर (opt->optlen) अणु
		पूर्णांक opt_size = माप(*करोpt) + opt->optlen;

		करोpt = kदो_स्मृति(opt_size, GFP_ATOMIC);
		अगर (करोpt && __ip_options_echo(net, &करोpt->opt, skb, opt)) अणु
			kमुक्त(करोpt);
			करोpt = शून्य;
		पूर्ण
	पूर्ण
	वापस करोpt;
पूर्ण

/* locally generated TCP pure ACKs have skb->truesize == 2
 * (check tcp_send_ack() in net/ipv4/tcp_output.c )
 * This is much faster than dissecting the packet to find out.
 * (Think of GRE encapsulations, IPv4, IPv6, ...)
 */
अटल अंतरभूत bool skb_is_tcp_pure_ack(स्थिर काष्ठा sk_buff *skb)
अणु
	वापस skb->truesize == 2;
पूर्ण

अटल अंतरभूत व्योम skb_set_tcp_pure_ack(काष्ठा sk_buff *skb)
अणु
	skb->truesize = 2;
पूर्ण

अटल अंतरभूत पूर्णांक tcp_inq(काष्ठा sock *sk)
अणु
	काष्ठा tcp_sock *tp = tcp_sk(sk);
	पूर्णांक answ;

	अगर ((1 << sk->sk_state) & (TCPF_SYN_SENT | TCPF_SYN_RECV)) अणु
		answ = 0;
	पूर्ण अन्यथा अगर (sock_flag(sk, SOCK_URGINLINE) ||
		   !tp->urg_data ||
		   beक्रमe(tp->urg_seq, tp->copied_seq) ||
		   !beक्रमe(tp->urg_seq, tp->rcv_nxt)) अणु

		answ = tp->rcv_nxt - tp->copied_seq;

		/* Subtract 1, अगर FIN was received */
		अगर (answ && sock_flag(sk, SOCK_DONE))
			answ--;
	पूर्ण अन्यथा अणु
		answ = tp->urg_seq - tp->copied_seq;
	पूर्ण

	वापस answ;
पूर्ण

पूर्णांक tcp_peek_len(काष्ठा socket *sock);

अटल अंतरभूत व्योम tcp_segs_in(काष्ठा tcp_sock *tp, स्थिर काष्ठा sk_buff *skb)
अणु
	u16 segs_in;

	segs_in = max_t(u16, 1, skb_shinfo(skb)->gso_segs);
	tp->segs_in += segs_in;
	अगर (skb->len > tcp_hdrlen(skb))
		tp->data_segs_in += segs_in;
पूर्ण

/*
 * TCP listen path runs lockless.
 * We क्रमced "struct sock" to be स्थिर qualअगरied to make sure
 * we करोn't modअगरy one of its field by mistake.
 * Here, we increment sk_drops which is an atomic_t, so we can safely
 * make sock writable again.
 */
अटल अंतरभूत व्योम tcp_listendrop(स्थिर काष्ठा sock *sk)
अणु
	atomic_inc(&((काष्ठा sock *)sk)->sk_drops);
	__NET_INC_STATS(sock_net(sk), LINUX_MIB_LISTENDROPS);
पूर्ण

क्रमागत hrसमयr_restart tcp_pace_kick(काष्ठा hrसमयr *समयr);

/*
 * Interface क्रम adding Upper Level Protocols over TCP
 */

#घोषणा TCP_ULP_NAME_MAX	16
#घोषणा TCP_ULP_MAX		128
#घोषणा TCP_ULP_BUF_MAX		(TCP_ULP_NAME_MAX*TCP_ULP_MAX)

काष्ठा tcp_ulp_ops अणु
	काष्ठा list_head	list;

	/* initialize ulp */
	पूर्णांक (*init)(काष्ठा sock *sk);
	/* update ulp */
	व्योम (*update)(काष्ठा sock *sk, काष्ठा proto *p,
		       व्योम (*ग_लिखो_space)(काष्ठा sock *sk));
	/* cleanup ulp */
	व्योम (*release)(काष्ठा sock *sk);
	/* diagnostic */
	पूर्णांक (*get_info)(स्थिर काष्ठा sock *sk, काष्ठा sk_buff *skb);
	माप_प्रकार (*get_info_size)(स्थिर काष्ठा sock *sk);
	/* clone ulp */
	व्योम (*clone)(स्थिर काष्ठा request_sock *req, काष्ठा sock *newsk,
		      स्थिर gfp_t priority);

	अक्षर		name[TCP_ULP_NAME_MAX];
	काष्ठा module	*owner;
पूर्ण;
पूर्णांक tcp_रेजिस्टर_ulp(काष्ठा tcp_ulp_ops *type);
व्योम tcp_unरेजिस्टर_ulp(काष्ठा tcp_ulp_ops *type);
पूर्णांक tcp_set_ulp(काष्ठा sock *sk, स्थिर अक्षर *name);
व्योम tcp_get_available_ulp(अक्षर *buf, माप_प्रकार len);
व्योम tcp_cleanup_ulp(काष्ठा sock *sk);
व्योम tcp_update_ulp(काष्ठा sock *sk, काष्ठा proto *p,
		    व्योम (*ग_लिखो_space)(काष्ठा sock *sk));

#घोषणा MODULE_ALIAS_TCP_ULP(name)				\
	__MODULE_INFO(alias, alias_userspace, name);		\
	__MODULE_INFO(alias, alias_tcp_ulp, "tcp-ulp-" name)

#अगर_घोषित CONFIG_NET_SOCK_MSG
काष्ठा sk_msg;
काष्ठा sk_psock;

#अगर_घोषित CONFIG_BPF_SYSCALL
काष्ठा proto *tcp_bpf_get_proto(काष्ठा sock *sk, काष्ठा sk_psock *psock);
पूर्णांक tcp_bpf_update_proto(काष्ठा sock *sk, काष्ठा sk_psock *psock, bool restore);
व्योम tcp_bpf_clone(स्थिर काष्ठा sock *sk, काष्ठा sock *newsk);
#पूर्ण_अगर /* CONFIG_BPF_SYSCALL */

पूर्णांक tcp_bpf_sendmsg_redir(काष्ठा sock *sk, काष्ठा sk_msg *msg, u32 bytes,
			  पूर्णांक flags);
#पूर्ण_अगर /* CONFIG_NET_SOCK_MSG */

#अगर !defined(CONFIG_BPF_SYSCALL) || !defined(CONFIG_NET_SOCK_MSG)
अटल अंतरभूत व्योम tcp_bpf_clone(स्थिर काष्ठा sock *sk, काष्ठा sock *newsk)
अणु
पूर्ण
#पूर्ण_अगर

#अगर_घोषित CONFIG_CGROUP_BPF
अटल अंतरभूत व्योम bpf_skops_init_skb(काष्ठा bpf_sock_ops_kern *skops,
				      काष्ठा sk_buff *skb,
				      अचिन्हित पूर्णांक end_offset)
अणु
	skops->skb = skb;
	skops->skb_data_end = skb->data + end_offset;
पूर्ण
#अन्यथा
अटल अंतरभूत व्योम bpf_skops_init_skb(काष्ठा bpf_sock_ops_kern *skops,
				      काष्ठा sk_buff *skb,
				      अचिन्हित पूर्णांक end_offset)
अणु
पूर्ण
#पूर्ण_अगर

/* Call BPF_SOCK_OPS program that वापसs an पूर्णांक. If the वापस value
 * is < 0, then the BPF op failed (क्रम example अगर the loaded BPF
 * program करोes not support the chosen operation or there is no BPF
 * program loaded).
 */
#अगर_घोषित CONFIG_BPF
अटल अंतरभूत पूर्णांक tcp_call_bpf(काष्ठा sock *sk, पूर्णांक op, u32 nargs, u32 *args)
अणु
	काष्ठा bpf_sock_ops_kern sock_ops;
	पूर्णांक ret;

	स_रखो(&sock_ops, 0, दुरत्व(काष्ठा bpf_sock_ops_kern, temp));
	अगर (sk_fullsock(sk)) अणु
		sock_ops.is_fullsock = 1;
		sock_owned_by_me(sk);
	पूर्ण

	sock_ops.sk = sk;
	sock_ops.op = op;
	अगर (nargs > 0)
		स_नकल(sock_ops.args, args, nargs * माप(*args));

	ret = BPF_CGROUP_RUN_PROG_SOCK_OPS(&sock_ops);
	अगर (ret == 0)
		ret = sock_ops.reply;
	अन्यथा
		ret = -1;
	वापस ret;
पूर्ण

अटल अंतरभूत पूर्णांक tcp_call_bpf_2arg(काष्ठा sock *sk, पूर्णांक op, u32 arg1, u32 arg2)
अणु
	u32 args[2] = अणुarg1, arg2पूर्ण;

	वापस tcp_call_bpf(sk, op, 2, args);
पूर्ण

अटल अंतरभूत पूर्णांक tcp_call_bpf_3arg(काष्ठा sock *sk, पूर्णांक op, u32 arg1, u32 arg2,
				    u32 arg3)
अणु
	u32 args[3] = अणुarg1, arg2, arg3पूर्ण;

	वापस tcp_call_bpf(sk, op, 3, args);
पूर्ण

#अन्यथा
अटल अंतरभूत पूर्णांक tcp_call_bpf(काष्ठा sock *sk, पूर्णांक op, u32 nargs, u32 *args)
अणु
	वापस -EPERM;
पूर्ण

अटल अंतरभूत पूर्णांक tcp_call_bpf_2arg(काष्ठा sock *sk, पूर्णांक op, u32 arg1, u32 arg2)
अणु
	वापस -EPERM;
पूर्ण

अटल अंतरभूत पूर्णांक tcp_call_bpf_3arg(काष्ठा sock *sk, पूर्णांक op, u32 arg1, u32 arg2,
				    u32 arg3)
अणु
	वापस -EPERM;
पूर्ण

#पूर्ण_अगर

अटल अंतरभूत u32 tcp_समयout_init(काष्ठा sock *sk)
अणु
	पूर्णांक समयout;

	समयout = tcp_call_bpf(sk, BPF_SOCK_OPS_TIMEOUT_INIT, 0, शून्य);

	अगर (समयout <= 0)
		समयout = TCP_TIMEOUT_INIT;
	वापस समयout;
पूर्ण

अटल अंतरभूत u32 tcp_rwnd_init_bpf(काष्ठा sock *sk)
अणु
	पूर्णांक rwnd;

	rwnd = tcp_call_bpf(sk, BPF_SOCK_OPS_RWND_INIT, 0, शून्य);

	अगर (rwnd < 0)
		rwnd = 0;
	वापस rwnd;
पूर्ण

अटल अंतरभूत bool tcp_bpf_ca_needs_ecn(काष्ठा sock *sk)
अणु
	वापस (tcp_call_bpf(sk, BPF_SOCK_OPS_NEEDS_ECN, 0, शून्य) == 1);
पूर्ण

अटल अंतरभूत व्योम tcp_bpf_rtt(काष्ठा sock *sk)
अणु
	अगर (BPF_SOCK_OPS_TEST_FLAG(tcp_sk(sk), BPF_SOCK_OPS_RTT_CB_FLAG))
		tcp_call_bpf(sk, BPF_SOCK_OPS_RTT_CB, 0, शून्य);
पूर्ण

#अगर IS_ENABLED(CONFIG_SMC)
बाह्य काष्ठा अटल_key_false tcp_have_smc;
#पूर्ण_अगर

#अगर IS_ENABLED(CONFIG_TLS_DEVICE)
व्योम clean_acked_data_enable(काष्ठा inet_connection_sock *icsk,
			     व्योम (*cad)(काष्ठा sock *sk, u32 ack_seq));
व्योम clean_acked_data_disable(काष्ठा inet_connection_sock *icsk);
व्योम clean_acked_data_flush(व्योम);
#पूर्ण_अगर

DECLARE_STATIC_KEY_FALSE(tcp_tx_delay_enabled);
अटल अंतरभूत व्योम tcp_add_tx_delay(काष्ठा sk_buff *skb,
				    स्थिर काष्ठा tcp_sock *tp)
अणु
	अगर (अटल_branch_unlikely(&tcp_tx_delay_enabled))
		skb->skb_mstamp_ns += (u64)tp->tcp_tx_delay * NSEC_PER_USEC;
पूर्ण

/* Compute Earliest Departure Time क्रम some control packets
 * like ACK or RST क्रम TIME_WAIT or non ESTABLISHED sockets.
 */
अटल अंतरभूत u64 tcp_transmit_समय(स्थिर काष्ठा sock *sk)
अणु
	अगर (अटल_branch_unlikely(&tcp_tx_delay_enabled)) अणु
		u32 delay = (sk->sk_state == TCP_TIME_WAIT) ?
			tcp_twsk(sk)->tw_tx_delay : tcp_sk(sk)->tcp_tx_delay;

		वापस tcp_घड़ी_ns() + (u64)delay * NSEC_PER_USEC;
	पूर्ण
	वापस 0;
पूर्ण

#पूर्ण_अगर	/* _TCP_H */
