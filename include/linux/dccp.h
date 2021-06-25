<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _LINUX_DCCP_H
#घोषणा _LINUX_DCCP_H


#समावेश <linux/in.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/kसमय.स>
#समावेश <linux/list.h>
#समावेश <linux/uपन.स>
#समावेश <linux/workqueue.h>

#समावेश <net/inet_connection_sock.h>
#समावेश <net/inet_sock.h>
#समावेश <net/inet_समयरुको_sock.h>
#समावेश <net/tcp_states.h>
#समावेश <uapi/linux/dccp.h>

क्रमागत dccp_state अणु
	DCCP_OPEN	     = TCP_ESTABLISHED,
	DCCP_REQUESTING	     = TCP_SYN_SENT,
	DCCP_LISTEN	     = TCP_LISTEN,
	DCCP_RESPOND	     = TCP_SYN_RECV,
	/*
	 * States involved in closing a DCCP connection:
	 * 1) ACTIVE_CLOSEREQ is entered by a server sending a CloseReq.
	 *
	 * 2) CLOSING can have three dअगरferent meanings (RFC 4340, 8.3):
	 *  a. Client has perक्रमmed active-बंद, has sent a Close to the server
	 *     from state OPEN or PARTOPEN, and is रुकोing क्रम the final Reset
	 *     (in this हाल, SOCK_DONE == 1).
	 *  b. Client is asked to perक्रमm passive-बंद, by receiving a CloseReq
	 *     in (PART)OPEN state. It sends a Close and रुकोs क्रम final Reset
	 *     (in this हाल, SOCK_DONE == 0).
	 *  c. Server perक्रमms an active-बंद as in (a), keeps TIMEWAIT state.
	 *
	 * 3) The following पूर्णांकermediate states are employed to give passively
	 *    closing nodes a chance to process their unपढ़ो data:
	 *    - PASSIVE_CLOSE    (from OPEN => CLOSED) and
	 *    - PASSIVE_CLOSEREQ (from (PART)OPEN to CLOSING; हाल (b) above).
	 */
	DCCP_ACTIVE_CLOSEREQ = TCP_FIN_WAIT1,
	DCCP_PASSIVE_CLOSE   = TCP_CLOSE_WAIT,	/* any node receiving a Close */
	DCCP_CLOSING	     = TCP_CLOSING,
	DCCP_TIME_WAIT	     = TCP_TIME_WAIT,
	DCCP_CLOSED	     = TCP_CLOSE,
	DCCP_NEW_SYN_RECV    = TCP_NEW_SYN_RECV,
	DCCP_PARTOPEN	     = TCP_MAX_STATES,
	DCCP_PASSIVE_CLOSEREQ,			/* clients receiving CloseReq */
	DCCP_MAX_STATES
पूर्ण;

क्रमागत अणु
	DCCPF_OPEN	      = TCPF_ESTABLISHED,
	DCCPF_REQUESTING      = TCPF_SYN_SENT,
	DCCPF_LISTEN	      = TCPF_LISTEN,
	DCCPF_RESPOND	      = TCPF_SYN_RECV,
	DCCPF_ACTIVE_CLOSEREQ = TCPF_FIN_WAIT1,
	DCCPF_CLOSING	      = TCPF_CLOSING,
	DCCPF_TIME_WAIT	      = TCPF_TIME_WAIT,
	DCCPF_CLOSED	      = TCPF_CLOSE,
	DCCPF_NEW_SYN_RECV    = TCPF_NEW_SYN_RECV,
	DCCPF_PARTOPEN	      = (1 << DCCP_PARTOPEN),
पूर्ण;

अटल अंतरभूत काष्ठा dccp_hdr *dccp_hdr(स्थिर काष्ठा sk_buff *skb)
अणु
	वापस (काष्ठा dccp_hdr *)skb_transport_header(skb);
पूर्ण

अटल अंतरभूत काष्ठा dccp_hdr *dccp_zeroed_hdr(काष्ठा sk_buff *skb, पूर्णांक headlen)
अणु
	skb_push(skb, headlen);
	skb_reset_transport_header(skb);
	वापस स_रखो(skb_transport_header(skb), 0, headlen);
पूर्ण

अटल अंतरभूत काष्ठा dccp_hdr_ext *dccp_hdrx(स्थिर काष्ठा dccp_hdr *dh)
अणु
	वापस (काष्ठा dccp_hdr_ext *)((अचिन्हित अक्षर *)dh + माप(*dh));
पूर्ण

अटल अंतरभूत अचिन्हित पूर्णांक __dccp_basic_hdr_len(स्थिर काष्ठा dccp_hdr *dh)
अणु
	वापस माप(*dh) + (dh->dccph_x ? माप(काष्ठा dccp_hdr_ext) : 0);
पूर्ण

अटल अंतरभूत अचिन्हित पूर्णांक dccp_basic_hdr_len(स्थिर काष्ठा sk_buff *skb)
अणु
	स्थिर काष्ठा dccp_hdr *dh = dccp_hdr(skb);
	वापस __dccp_basic_hdr_len(dh);
पूर्ण

अटल अंतरभूत __u64 dccp_hdr_seq(स्थिर काष्ठा dccp_hdr *dh)
अणु
	__u64 seq_nr =  ntohs(dh->dccph_seq);

	अगर (dh->dccph_x != 0)
		seq_nr = (seq_nr << 32) + ntohl(dccp_hdrx(dh)->dccph_seq_low);
	अन्यथा
		seq_nr += (u32)dh->dccph_seq2 << 16;

	वापस seq_nr;
पूर्ण

अटल अंतरभूत काष्ठा dccp_hdr_request *dccp_hdr_request(काष्ठा sk_buff *skb)
अणु
	वापस (काष्ठा dccp_hdr_request *)(skb_transport_header(skb) +
					   dccp_basic_hdr_len(skb));
पूर्ण

अटल अंतरभूत काष्ठा dccp_hdr_ack_bits *dccp_hdr_ack_bits(स्थिर काष्ठा sk_buff *skb)
अणु
	वापस (काष्ठा dccp_hdr_ack_bits *)(skb_transport_header(skb) +
					    dccp_basic_hdr_len(skb));
पूर्ण

अटल अंतरभूत u64 dccp_hdr_ack_seq(स्थिर काष्ठा sk_buff *skb)
अणु
	स्थिर काष्ठा dccp_hdr_ack_bits *dhack = dccp_hdr_ack_bits(skb);
	वापस ((u64)ntohs(dhack->dccph_ack_nr_high) << 32) + ntohl(dhack->dccph_ack_nr_low);
पूर्ण

अटल अंतरभूत काष्ठा dccp_hdr_response *dccp_hdr_response(काष्ठा sk_buff *skb)
अणु
	वापस (काष्ठा dccp_hdr_response *)(skb_transport_header(skb) +
					    dccp_basic_hdr_len(skb));
पूर्ण

अटल अंतरभूत काष्ठा dccp_hdr_reset *dccp_hdr_reset(काष्ठा sk_buff *skb)
अणु
	वापस (काष्ठा dccp_hdr_reset *)(skb_transport_header(skb) +
					 dccp_basic_hdr_len(skb));
पूर्ण

अटल अंतरभूत अचिन्हित पूर्णांक __dccp_hdr_len(स्थिर काष्ठा dccp_hdr *dh)
अणु
	वापस __dccp_basic_hdr_len(dh) +
	       dccp_packet_hdr_len(dh->dccph_type);
पूर्ण

अटल अंतरभूत अचिन्हित पूर्णांक dccp_hdr_len(स्थिर काष्ठा sk_buff *skb)
अणु
	वापस __dccp_hdr_len(dccp_hdr(skb));
पूर्ण

/**
 * काष्ठा dccp_request_sock  -  represent DCCP-specअगरic connection request
 * @dreq_inet_rsk: काष्ठाure inherited from
 * @dreq_iss: initial sequence number, sent on the first Response (RFC 4340, 7.1)
 * @dreq_gss: greatest sequence number sent (क्रम retransmitted Responses)
 * @dreq_isr: initial sequence number received in the first Request
 * @dreq_gsr: greatest sequence number received (क्रम retransmitted Request(s))
 * @dreq_service: service code present on the Request (there is just one)
 * @dreq_featneg: feature negotiation options क्रम this connection
 * The following two fields are analogous to the ones in dccp_sock:
 * @dreq_बारtamp_echo: last received बारtamp to echo (13.1)
 * @dreq_बारtamp_echo: the समय of receiving the last @dreq_बारtamp_echo
 */
काष्ठा dccp_request_sock अणु
	काष्ठा inet_request_sock dreq_inet_rsk;
	__u64			 dreq_iss;
	__u64			 dreq_gss;
	__u64			 dreq_isr;
	__u64			 dreq_gsr;
	__be32			 dreq_service;
	spinlock_t		 dreq_lock;
	काष्ठा list_head	 dreq_featneg;
	__u32			 dreq_बारtamp_echo;
	__u32			 dreq_बारtamp_समय;
पूर्ण;

अटल अंतरभूत काष्ठा dccp_request_sock *dccp_rsk(स्थिर काष्ठा request_sock *req)
अणु
	वापस (काष्ठा dccp_request_sock *)req;
पूर्ण

बाह्य काष्ठा inet_समयरुको_death_row dccp_death_row;

बाह्य पूर्णांक dccp_parse_options(काष्ठा sock *sk, काष्ठा dccp_request_sock *dreq,
			      काष्ठा sk_buff *skb);

काष्ठा dccp_options_received अणु
	u64	dccpor_ndp:48;
	u32	dccpor_बारtamp;
	u32	dccpor_बारtamp_echo;
	u32	dccpor_elapsed_समय;
पूर्ण;

काष्ठा ccid;

क्रमागत dccp_role अणु
	DCCP_ROLE_UNDEFINED,
	DCCP_ROLE_LISTEN,
	DCCP_ROLE_CLIENT,
	DCCP_ROLE_SERVER,
पूर्ण;

काष्ठा dccp_service_list अणु
	__u32	dccpsl_nr;
	__be32	dccpsl_list[];
पूर्ण;

#घोषणा DCCP_SERVICE_INVALID_VALUE htonl((__u32)-1)
#घोषणा DCCP_SERVICE_CODE_IS_ABSENT		0

अटल अंतरभूत bool dccp_list_has_service(स्थिर काष्ठा dccp_service_list *sl,
					स्थिर __be32 service)
अणु
	अगर (likely(sl != शून्य)) अणु
		u32 i = sl->dccpsl_nr;
		जबतक (i--)
			अगर (sl->dccpsl_list[i] == service)
				वापस true;
	पूर्ण
	वापस false;
पूर्ण

काष्ठा dccp_ackvec;

/**
 * काष्ठा dccp_sock - DCCP socket state
 *
 * @dccps_swl - sequence number winकरोw low
 * @dccps_swh - sequence number winकरोw high
 * @dccps_awl - acknowledgement number winकरोw low
 * @dccps_awh - acknowledgement number winकरोw high
 * @dccps_iss - initial sequence number sent
 * @dccps_isr - initial sequence number received
 * @dccps_osr - first OPEN sequence number received
 * @dccps_gss - greatest sequence number sent
 * @dccps_gsr - greatest valid sequence number received
 * @dccps_gar - greatest valid ack number received on a non-Sync; initialized to %dccps_iss
 * @dccps_service - first (passive sock) or unique (active sock) service code
 * @dccps_service_list - second .. last service code on passive socket
 * @dccps_बारtamp_echo - latest बारtamp received on a TIMESTAMP option
 * @dccps_बारtamp_समय - समय of receiving latest @dccps_बारtamp_echo
 * @dccps_l_ack_ratio - feature-local Ack Ratio
 * @dccps_r_ack_ratio - feature-remote Ack Ratio
 * @dccps_l_seq_win - local Sequence Winकरोw (influences ack number validity)
 * @dccps_r_seq_win - remote Sequence Winकरोw (influences seq number validity)
 * @dccps_pcslen - sender   partial checksum coverage (via sockopt)
 * @dccps_pcrlen - receiver partial checksum coverage (via sockopt)
 * @dccps_send_ndp_count - local Send NDP Count feature (7.7.2)
 * @dccps_ndp_count - number of Non Data Packets since last data packet
 * @dccps_mss_cache - current value of MSS (path MTU minus header sizes)
 * @dccps_rate_last - बारtamp क्रम rate-limiting DCCP-Sync (RFC 4340, 7.5.4)
 * @dccps_featneg - tracks feature-negotiation state (mostly during handshake)
 * @dccps_hc_rx_ackvec - rx half connection ack vector
 * @dccps_hc_rx_ccid - CCID used क्रम the receiver (or receiving half-connection)
 * @dccps_hc_tx_ccid - CCID used क्रम the sender (or sending half-connection)
 * @dccps_options_received - parsed set of retrieved options
 * @dccps_qpolicy - TX dequeueing policy, one of %dccp_packet_dequeueing_policy
 * @dccps_tx_qlen - maximum length of the TX queue
 * @dccps_role - role of this sock, one of %dccp_role
 * @dccps_hc_rx_insert_options - receiver wants to add options when acking
 * @dccps_hc_tx_insert_options - sender wants to add options when sending
 * @dccps_server_समयरुको - server holds समयरुको state on बंद (RFC 4340, 8.3)
 * @dccps_sync_scheduled - flag which संकेतs "send out-of-band message soon"
 * @dccps_xmitlet - tasklet scheduled by the TX CCID to dequeue data packets
 * @dccps_xmit_समयr - used by the TX CCID to delay sending (rate-based pacing)
 * @dccps_syn_rtt - RTT sample from Request/Response exchange (in usecs)
 */
काष्ठा dccp_sock अणु
	/* inet_connection_sock has to be the first member of dccp_sock */
	काष्ठा inet_connection_sock	dccps_inet_connection;
#घोषणा dccps_syn_rtt			dccps_inet_connection.icsk_ack.lrcvसमय
	__u64				dccps_swl;
	__u64				dccps_swh;
	__u64				dccps_awl;
	__u64				dccps_awh;
	__u64				dccps_iss;
	__u64				dccps_isr;
	__u64				dccps_osr;
	__u64				dccps_gss;
	__u64				dccps_gsr;
	__u64				dccps_gar;
	__be32				dccps_service;
	__u32				dccps_mss_cache;
	काष्ठा dccp_service_list	*dccps_service_list;
	__u32				dccps_बारtamp_echo;
	__u32				dccps_बारtamp_समय;
	__u16				dccps_l_ack_ratio;
	__u16				dccps_r_ack_ratio;
	__u64				dccps_l_seq_win:48;
	__u64				dccps_r_seq_win:48;
	__u8				dccps_pcslen:4;
	__u8				dccps_pcrlen:4;
	__u8				dccps_send_ndp_count:1;
	__u64				dccps_ndp_count:48;
	अचिन्हित दीर्घ			dccps_rate_last;
	काष्ठा list_head		dccps_featneg;
	काष्ठा dccp_ackvec		*dccps_hc_rx_ackvec;
	काष्ठा ccid			*dccps_hc_rx_ccid;
	काष्ठा ccid			*dccps_hc_tx_ccid;
	काष्ठा dccp_options_received	dccps_options_received;
	__u8				dccps_qpolicy;
	__u32				dccps_tx_qlen;
	क्रमागत dccp_role			dccps_role:2;
	__u8				dccps_hc_rx_insert_options:1;
	__u8				dccps_hc_tx_insert_options:1;
	__u8				dccps_server_समयरुको:1;
	__u8				dccps_sync_scheduled:1;
	काष्ठा tasklet_काष्ठा		dccps_xmitlet;
	काष्ठा समयr_list		dccps_xmit_समयr;
पूर्ण;

अटल अंतरभूत काष्ठा dccp_sock *dccp_sk(स्थिर काष्ठा sock *sk)
अणु
	वापस (काष्ठा dccp_sock *)sk;
पूर्ण

अटल अंतरभूत स्थिर अक्षर *dccp_role(स्थिर काष्ठा sock *sk)
अणु
	चयन (dccp_sk(sk)->dccps_role) अणु
	हाल DCCP_ROLE_UNDEFINED: वापस "undefined";
	हाल DCCP_ROLE_LISTEN:	  वापस "listen";
	हाल DCCP_ROLE_SERVER:	  वापस "server";
	हाल DCCP_ROLE_CLIENT:	  वापस "client";
	पूर्ण
	वापस शून्य;
पूर्ण

बाह्य व्योम dccp_syn_ack_समयout(स्थिर काष्ठा request_sock *req);

#पूर्ण_अगर /* _LINUX_DCCP_H */
