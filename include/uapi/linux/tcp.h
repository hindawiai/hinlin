<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0+ WITH Linux-syscall-note */
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
 *
 *		This program is मुक्त software; you can redistribute it and/or
 *		modअगरy it under the terms of the GNU General Public License
 *		as published by the Free Software Foundation; either version
 *		2 of the License, or (at your option) any later version.
 */
#अगर_अघोषित _UAPI_LINUX_TCP_H
#घोषणा _UAPI_LINUX_TCP_H

#समावेश <linux/types.h>
#समावेश <यंत्र/byteorder.h>
#समावेश <linux/socket.h>

काष्ठा tcphdr अणु
	__be16	source;
	__be16	dest;
	__be32	seq;
	__be32	ack_seq;
#अगर defined(__LITTLE_ENDIAN_BITFIELD)
	__u16	res1:4,
		करोff:4,
		fin:1,
		syn:1,
		rst:1,
		psh:1,
		ack:1,
		urg:1,
		ece:1,
		cwr:1;
#या_अगर defined(__BIG_ENDIAN_BITFIELD)
	__u16	करोff:4,
		res1:4,
		cwr:1,
		ece:1,
		urg:1,
		ack:1,
		psh:1,
		rst:1,
		syn:1,
		fin:1;
#अन्यथा
#त्रुटि	"Adjust your <asm/byteorder.h> defines"
#पूर्ण_अगर
	__be16	winकरोw;
	__sum16	check;
	__be16	urg_ptr;
पूर्ण;

/*
 *	The जोड़ cast uses a gcc extension to aव्योम aliasing problems
 *  (जोड़ is compatible to any of its members)
 *  This means this part of the code is -fstrict-aliasing safe now.
 */
जोड़ tcp_word_hdr अणु
	काष्ठा tcphdr hdr;
	__be32        words[5];
पूर्ण;

#घोषणा tcp_flag_word(tp) (((जोड़ tcp_word_hdr *)(tp))->words[3])

क्रमागत अणु
	TCP_FLAG_CWR = __स्थिरant_cpu_to_be32(0x00800000),
	TCP_FLAG_ECE = __स्थिरant_cpu_to_be32(0x00400000),
	TCP_FLAG_URG = __स्थिरant_cpu_to_be32(0x00200000),
	TCP_FLAG_ACK = __स्थिरant_cpu_to_be32(0x00100000),
	TCP_FLAG_PSH = __स्थिरant_cpu_to_be32(0x00080000),
	TCP_FLAG_RST = __स्थिरant_cpu_to_be32(0x00040000),
	TCP_FLAG_SYN = __स्थिरant_cpu_to_be32(0x00020000),
	TCP_FLAG_FIN = __स्थिरant_cpu_to_be32(0x00010000),
	TCP_RESERVED_BITS = __स्थिरant_cpu_to_be32(0x0F000000),
	TCP_DATA_OFFSET = __स्थिरant_cpu_to_be32(0xF0000000)
पूर्ण;

/*
 * TCP general स्थिरants
 */
#घोषणा TCP_MSS_DEFAULT		 536U	/* IPv4 (RFC1122, RFC2581) */
#घोषणा TCP_MSS_DESIRED		1220U	/* IPv6 (tunneled), EDNS0 (RFC3226) */

/* TCP socket options */
#घोषणा TCP_NODELAY		1	/* Turn off Nagle's algorithm. */
#घोषणा TCP_MAXSEG		2	/* Limit MSS */
#घोषणा TCP_CORK		3	/* Never send partially complete segments */
#घोषणा TCP_KEEPIDLE		4	/* Start keeplives after this period */
#घोषणा TCP_KEEPINTVL		5	/* Interval between keepalives */
#घोषणा TCP_KEEPCNT		6	/* Number of keepalives beक्रमe death */
#घोषणा TCP_SYNCNT		7	/* Number of SYN retransmits */
#घोषणा TCP_LINGER2		8	/* Lअगरe समय of orphaned FIN-WAIT-2 state */
#घोषणा TCP_DEFER_ACCEPT	9	/* Wake up listener only when data arrive */
#घोषणा TCP_WINDOW_CLAMP	10	/* Bound advertised winकरोw */
#घोषणा TCP_INFO		11	/* Inक्रमmation about this connection. */
#घोषणा TCP_QUICKACK		12	/* Block/reenable quick acks */
#घोषणा TCP_CONGESTION		13	/* Congestion control algorithm */
#घोषणा TCP_MD5SIG		14	/* TCP MD5 Signature (RFC2385) */
#घोषणा TCP_THIN_LINEAR_TIMEOUTS 16	/* Use linear समयouts क्रम thin streams*/
#घोषणा TCP_THIN_DUPACK		17	/* Fast retrans. after 1 dupack */
#घोषणा TCP_USER_TIMEOUT	18	/* How दीर्घ क्रम loss retry beक्रमe समयout */
#घोषणा TCP_REPAIR		19	/* TCP sock is under repair right now */
#घोषणा TCP_REPAIR_QUEUE	20
#घोषणा TCP_QUEUE_SEQ		21
#घोषणा TCP_REPAIR_OPTIONS	22
#घोषणा TCP_FASTOPEN		23	/* Enable FastOpen on listeners */
#घोषणा TCP_TIMESTAMP		24
#घोषणा TCP_NOTSENT_LOWAT	25	/* limit number of unsent bytes in ग_लिखो queue */
#घोषणा TCP_CC_INFO		26	/* Get Congestion Control (optional) info */
#घोषणा TCP_SAVE_SYN		27	/* Record SYN headers क्रम new connections */
#घोषणा TCP_SAVED_SYN		28	/* Get SYN headers recorded क्रम connection */
#घोषणा TCP_REPAIR_WINDOW	29	/* Get/set winकरोw parameters */
#घोषणा TCP_FASTOPEN_CONNECT	30	/* Attempt FastOpen with connect */
#घोषणा TCP_ULP			31	/* Attach a ULP to a TCP connection */
#घोषणा TCP_MD5SIG_EXT		32	/* TCP MD5 Signature with extensions */
#घोषणा TCP_FASTOPEN_KEY	33	/* Set the key क्रम Fast Open (cookie) */
#घोषणा TCP_FASTOPEN_NO_COOKIE	34	/* Enable TFO without a TFO cookie */
#घोषणा TCP_ZEROCOPY_RECEIVE	35
#घोषणा TCP_INQ			36	/* Notअगरy bytes available to पढ़ो as a cmsg on पढ़ो */

#घोषणा TCP_CM_INQ		TCP_INQ

#घोषणा TCP_TX_DELAY		37	/* delay outgoing packets by XX usec */


#घोषणा TCP_REPAIR_ON		1
#घोषणा TCP_REPAIR_OFF		0
#घोषणा TCP_REPAIR_OFF_NO_WP	-1	/* Turn off without winकरोw probes */

काष्ठा tcp_repair_opt अणु
	__u32	opt_code;
	__u32	opt_val;
पूर्ण;

काष्ठा tcp_repair_winकरोw अणु
	__u32	snd_wl1;
	__u32	snd_wnd;
	__u32	max_winकरोw;

	__u32	rcv_wnd;
	__u32	rcv_wup;
पूर्ण;

क्रमागत अणु
	TCP_NO_QUEUE,
	TCP_RECV_QUEUE,
	TCP_SEND_QUEUE,
	TCP_QUEUES_NR,
पूर्ण;

/* why fastखोलो failed from client perspective */
क्रमागत tcp_fastखोलो_client_fail अणु
	TFO_STATUS_UNSPEC, /* catch-all */
	TFO_COOKIE_UNAVAILABLE, /* अगर not in TFO_CLIENT_NO_COOKIE mode */
	TFO_DATA_NOT_ACKED, /* SYN-ACK did not ack SYN data */
	TFO_SYN_RETRANSMITTED, /* SYN-ACK did not ack SYN data after समयout */
पूर्ण;

/* क्रम TCP_INFO socket option */
#घोषणा TCPI_OPT_TIMESTAMPS	1
#घोषणा TCPI_OPT_SACK		2
#घोषणा TCPI_OPT_WSCALE		4
#घोषणा TCPI_OPT_ECN		8 /* ECN was negociated at TCP session init */
#घोषणा TCPI_OPT_ECN_SEEN	16 /* we received at least one packet with ECT */
#घोषणा TCPI_OPT_SYN_DATA	32 /* SYN-ACK acked data in SYN sent or rcvd */

/*
 * Sender's congestion state indicating normal or abnormal situations
 * in the last round of packets sent. The state is driven by the ACK
 * inक्रमmation and समयr events.
 */
क्रमागत tcp_ca_state अणु
	/*
	 * Nothing bad has been observed recently.
	 * No apparent reordering, packet loss, or ECN marks.
	 */
	TCP_CA_Open = 0,
#घोषणा TCPF_CA_Open	(1<<TCP_CA_Open)
	/*
	 * The sender enters disordered state when it has received DUPACKs or
	 * SACKs in the last round of packets sent. This could be due to packet
	 * loss or reordering but needs further inक्रमmation to confirm packets
	 * have been lost.
	 */
	TCP_CA_Disorder = 1,
#घोषणा TCPF_CA_Disorder (1<<TCP_CA_Disorder)
	/*
	 * The sender enters Congestion Winकरोw Reduction (CWR) state when it
	 * has received ACKs with ECN-ECE marks, or has experienced congestion
	 * or packet discard on the sender host (e.g. qdisc).
	 */
	TCP_CA_CWR = 2,
#घोषणा TCPF_CA_CWR	(1<<TCP_CA_CWR)
	/*
	 * The sender is in fast recovery and retransmitting lost packets,
	 * typically triggered by ACK events.
	 */
	TCP_CA_Recovery = 3,
#घोषणा TCPF_CA_Recovery (1<<TCP_CA_Recovery)
	/*
	 * The sender is in loss recovery triggered by retransmission समयout.
	 */
	TCP_CA_Loss = 4
#घोषणा TCPF_CA_Loss	(1<<TCP_CA_Loss)
पूर्ण;

काष्ठा tcp_info अणु
	__u8	tcpi_state;
	__u8	tcpi_ca_state;
	__u8	tcpi_retransmits;
	__u8	tcpi_probes;
	__u8	tcpi_backoff;
	__u8	tcpi_options;
	__u8	tcpi_snd_wscale : 4, tcpi_rcv_wscale : 4;
	__u8	tcpi_delivery_rate_app_limited:1, tcpi_fastखोलो_client_fail:2;

	__u32	tcpi_rto;
	__u32	tcpi_ato;
	__u32	tcpi_snd_mss;
	__u32	tcpi_rcv_mss;

	__u32	tcpi_unacked;
	__u32	tcpi_sacked;
	__u32	tcpi_lost;
	__u32	tcpi_retrans;
	__u32	tcpi_fackets;

	/* Times. */
	__u32	tcpi_last_data_sent;
	__u32	tcpi_last_ack_sent;     /* Not remembered, sorry. */
	__u32	tcpi_last_data_recv;
	__u32	tcpi_last_ack_recv;

	/* Metrics. */
	__u32	tcpi_pmtu;
	__u32	tcpi_rcv_ssthresh;
	__u32	tcpi_rtt;
	__u32	tcpi_rttvar;
	__u32	tcpi_snd_ssthresh;
	__u32	tcpi_snd_cwnd;
	__u32	tcpi_advmss;
	__u32	tcpi_reordering;

	__u32	tcpi_rcv_rtt;
	__u32	tcpi_rcv_space;

	__u32	tcpi_total_retrans;

	__u64	tcpi_pacing_rate;
	__u64	tcpi_max_pacing_rate;
	__u64	tcpi_bytes_acked;    /* RFC4898 tcpEStatsAppHCThruOctetsAcked */
	__u64	tcpi_bytes_received; /* RFC4898 tcpEStatsAppHCThruOctetsReceived */
	__u32	tcpi_segs_out;	     /* RFC4898 tcpEStatsPerfSegsOut */
	__u32	tcpi_segs_in;	     /* RFC4898 tcpEStatsPerfSegsIn */

	__u32	tcpi_notsent_bytes;
	__u32	tcpi_min_rtt;
	__u32	tcpi_data_segs_in;	/* RFC4898 tcpEStatsDataSegsIn */
	__u32	tcpi_data_segs_out;	/* RFC4898 tcpEStatsDataSegsOut */

	__u64   tcpi_delivery_rate;

	__u64	tcpi_busy_समय;      /* Time (usec) busy sending data */
	__u64	tcpi_rwnd_limited;   /* Time (usec) limited by receive winकरोw */
	__u64	tcpi_sndbuf_limited; /* Time (usec) limited by send buffer */

	__u32	tcpi_delivered;
	__u32	tcpi_delivered_ce;

	__u64	tcpi_bytes_sent;     /* RFC4898 tcpEStatsPerfHCDataOctetsOut */
	__u64	tcpi_bytes_retrans;  /* RFC4898 tcpEStatsPerfOctetsRetrans */
	__u32	tcpi_dsack_dups;     /* RFC4898 tcpEStatsStackDSACKDups */
	__u32	tcpi_reord_seen;     /* reordering events seen */

	__u32	tcpi_rcv_ooopack;    /* Out-of-order packets received */

	__u32	tcpi_snd_wnd;	     /* peer's advertised receive winकरोw after
				      * scaling (bytes)
				      */
पूर्ण;

/* netlink attributes types क्रम SCM_TIMESTAMPING_OPT_STATS */
क्रमागत अणु
	TCP_NLA_PAD,
	TCP_NLA_BUSY,		/* Time (usec) busy sending data */
	TCP_NLA_RWND_LIMITED,	/* Time (usec) limited by receive winकरोw */
	TCP_NLA_SNDBUF_LIMITED,	/* Time (usec) limited by send buffer */
	TCP_NLA_DATA_SEGS_OUT,	/* Data pkts sent including retransmission */
	TCP_NLA_TOTAL_RETRANS,	/* Data pkts retransmitted */
	TCP_NLA_PACING_RATE,    /* Pacing rate in bytes per second */
	TCP_NLA_DELIVERY_RATE,  /* Delivery rate in bytes per second */
	TCP_NLA_SND_CWND,       /* Sending congestion winकरोw */
	TCP_NLA_REORDERING,     /* Reordering metric */
	TCP_NLA_MIN_RTT,        /* minimum RTT */
	TCP_NLA_RECUR_RETRANS,  /* Recurring retransmits क्रम the current pkt */
	TCP_NLA_DELIVERY_RATE_APP_LMT, /* delivery rate application limited ? */
	TCP_NLA_SNDQ_SIZE,	/* Data (bytes) pending in send queue */
	TCP_NLA_CA_STATE,	/* ca_state of socket */
	TCP_NLA_SND_SSTHRESH,	/* Slow start size threshold */
	TCP_NLA_DELIVERED,	/* Data pkts delivered incl. out-of-order */
	TCP_NLA_DELIVERED_CE,	/* Like above but only ones w/ CE marks */
	TCP_NLA_BYTES_SENT,	/* Data bytes sent including retransmission */
	TCP_NLA_BYTES_RETRANS,	/* Data bytes retransmitted */
	TCP_NLA_DSACK_DUPS,	/* DSACK blocks received */
	TCP_NLA_REORD_SEEN,	/* reordering events seen */
	TCP_NLA_SRTT,		/* smoothed RTT in usecs */
	TCP_NLA_TIMEOUT_REHASH, /* Timeout-triggered rehash attempts */
	TCP_NLA_BYTES_NOTSENT,	/* Bytes in ग_लिखो queue not yet sent */
	TCP_NLA_EDT,		/* Earliest departure समय (CLOCK_MONOTONIC) */
	TCP_NLA_TTL,		/* TTL or hop limit of a packet received */
पूर्ण;

/* क्रम TCP_MD5SIG socket option */
#घोषणा TCP_MD5SIG_MAXKEYLEN	80

/* tcp_md5sig extension flags क्रम TCP_MD5SIG_EXT */
#घोषणा TCP_MD5SIG_FLAG_PREFIX		0x1	/* address prefix length */
#घोषणा TCP_MD5SIG_FLAG_IFINDEX		0x2	/* अगरindex set */

काष्ठा tcp_md5sig अणु
	काष्ठा __kernel_sockaddr_storage tcpm_addr;	/* address associated */
	__u8	tcpm_flags;				/* extension flags */
	__u8	tcpm_prefixlen;				/* address prefix */
	__u16	tcpm_keylen;				/* key length */
	पूर्णांक	tcpm_अगरindex;				/* device index क्रम scope */
	__u8	tcpm_key[TCP_MD5SIG_MAXKEYLEN];		/* key (binary) */
पूर्ण;

/* INET_DIAG_MD5SIG */
काष्ठा tcp_diag_md5sig अणु
	__u8	tcpm_family;
	__u8	tcpm_prefixlen;
	__u16	tcpm_keylen;
	__be32	tcpm_addr[4];
	__u8	tcpm_key[TCP_MD5SIG_MAXKEYLEN];
पूर्ण;

/* setsockopt(fd, IPPROTO_TCP, TCP_ZEROCOPY_RECEIVE, ...) */

#घोषणा TCP_RECEIVE_ZEROCOPY_FLAG_TLB_CLEAN_HINT 0x1
काष्ठा tcp_zerocopy_receive अणु
	__u64 address;		/* in: address of mapping */
	__u32 length;		/* in/out: number of bytes to map/mapped */
	__u32 recv_skip_hपूर्णांक;	/* out: amount of bytes to skip */
	__u32 inq; /* out: amount of bytes in पढ़ो queue */
	__s32 err; /* out: socket error */
	__u64 copybuf_address;	/* in: copybuf address (small पढ़ोs) */
	__s32 copybuf_len; /* in/out: copybuf bytes avail/used or error */
	__u32 flags; /* in: flags */
	__u64 msg_control; /* ancillary data */
	__u64 msg_controllen;
	__u32 msg_flags;
	__u32 reserved; /* set to 0 क्रम now */
पूर्ण;
#पूर्ण_अगर /* _UAPI_LINUX_TCP_H */
