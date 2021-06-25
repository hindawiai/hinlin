<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/* SCTP kernel implementation
 * (C) Copyright IBM Corp. 2001, 2004
 * Copyright (c) 1999-2000 Cisco, Inc.
 * Copyright (c) 1999-2001 Motorola, Inc.
 * Copyright (c) 2001 Intel Corp.
 *
 * This file is part of the SCTP kernel implementation
 *
 * Please send any bug reports or fixes you make to the
 * email addresses:
 *    lksctp developers <linux-sctp@vger.kernel.org>
 *
 * Written or modअगरied by:
 *    Randall Stewart	    <अक्रमall@sctp.chicago.il.us>
 *    Ken Morneau	    <kmorneau@cisco.com>
 *    Qiaobing Xie	    <qxie1@email.mot.com>
 *    La Monte H.P. Yarroll <piggy@acm.org>
 *    Karl Knutson	    <karl@athena.chicago.il.us>
 *    Jon Grimm		    <jgrimm@us.ibm.com>
 *    Xingang Guo	    <xingang.guo@पूर्णांकel.com>
 *    Hui Huang		    <hui.huang@nokia.com>
 *    Sridhar Samudrala	    <sri@us.ibm.com>
 *    Daisy Chang	    <daisyc@us.ibm.com>
 *    Dajiang Zhang	    <dajiang.zhang@nokia.com>
 *    Ardelle Fan	    <ardelle.fan@पूर्णांकel.com>
 *    Ryan Layer	    <rmlayer@us.ibm.com>
 *    Anup Pemmaiah	    <pemmaiah@cc.usu.edu>
 *    Kevin Gao             <kevin.gao@पूर्णांकel.com>
 */

#अगर_अघोषित __sctp_काष्ठाs_h__
#घोषणा __sctp_काष्ठाs_h__

#समावेश <linux/kसमय.स>
#समावेश <linux/generic-radix-tree.h>
#समावेश <linux/rhashtable-types.h>
#समावेश <linux/socket.h>	/* linux/in.h needs this!!    */
#समावेश <linux/in.h>		/* We get काष्ठा sockaddr_in. */
#समावेश <linux/in6.h>		/* We get काष्ठा in6_addr     */
#समावेश <linux/ipv6.h>
#समावेश <यंत्र/param.h>		/* We get MAXHOSTNAMELEN.     */
#समावेश <linux/atomic.h>		/* This माला_लो us atomic counters.  */
#समावेश <linux/skbuff.h>	/* We need sk_buff_head. */
#समावेश <linux/workqueue.h>	/* We need tq_काष्ठा.	 */
#समावेश <linux/sctp.h>		/* We need sctp* header काष्ठाs.  */
#समावेश <net/sctp/auth.h>	/* We need auth specअगरic काष्ठाs */
#समावेश <net/ip.h>		/* For inet_skb_parm */

/* A convenience काष्ठाure क्रम handling sockaddr काष्ठाures.
 * We should wean ourselves off this.
 */
जोड़ sctp_addr अणु
	काष्ठा sockaddr_in v4;
	काष्ठा sockaddr_in6 v6;
	काष्ठा sockaddr sa;
पूर्ण;

/* Forward declarations क्रम data काष्ठाures. */
काष्ठा sctp_globals;
काष्ठा sctp_endpoपूर्णांक;
काष्ठा sctp_association;
काष्ठा sctp_transport;
काष्ठा sctp_packet;
काष्ठा sctp_chunk;
काष्ठा sctp_inq;
काष्ठा sctp_outq;
काष्ठा sctp_bind_addr;
काष्ठा sctp_ulpq;
काष्ठा sctp_ep_common;
काष्ठा crypto_shash;
काष्ठा sctp_stream;


#समावेश <net/sctp/tsnmap.h>
#समावेश <net/sctp/ulpevent.h>
#समावेश <net/sctp/ulpqueue.h>
#समावेश <net/sctp/stream_पूर्णांकerleave.h>

/* Structures useful क्रम managing bind/connect. */

काष्ठा sctp_bind_bucket अणु
	अचिन्हित लघु	port;
	चिन्हित अक्षर	fastreuse;
	चिन्हित अक्षर	fastreuseport;
	kuid_t		fastuid;
	काष्ठा hlist_node	node;
	काष्ठा hlist_head	owner;
	काष्ठा net	*net;
पूर्ण;

काष्ठा sctp_bind_hashbucket अणु
	spinlock_t	lock;
	काष्ठा hlist_head	chain;
पूर्ण;

/* Used क्रम hashing all associations.  */
काष्ठा sctp_hashbucket अणु
	rwlock_t	lock;
	काष्ठा hlist_head	chain;
पूर्ण __attribute__((__aligned__(8)));


/* The SCTP globals काष्ठाure. */
बाह्य काष्ठा sctp_globals अणु
	/* This is a list of groups of functions क्रम each address
	 * family that we support.
	 */
	काष्ठा list_head address_families;

	/* This is the hash of all endpoपूर्णांकs. */
	काष्ठा sctp_hashbucket *ep_hashtable;
	/* This is the sctp port control hash.	*/
	काष्ठा sctp_bind_hashbucket *port_hashtable;
	/* This is the hash of all transports. */
	काष्ठा rhltable transport_hashtable;

	/* Sizes of above hashtables. */
	पूर्णांक ep_hashsize;
	पूर्णांक port_hashsize;

	/* Default initialization values to be applied to new associations. */
	__u16 max_instreams;
	__u16 max_outstreams;

	/* Flag to indicate whether computing and verअगरying checksum
	 * is disabled. */
        bool checksum_disable;
पूर्ण sctp_globals;

#घोषणा sctp_max_instreams		(sctp_globals.max_instreams)
#घोषणा sctp_max_outstreams		(sctp_globals.max_outstreams)
#घोषणा sctp_address_families		(sctp_globals.address_families)
#घोषणा sctp_ep_hashsize		(sctp_globals.ep_hashsize)
#घोषणा sctp_ep_hashtable		(sctp_globals.ep_hashtable)
#घोषणा sctp_port_hashsize		(sctp_globals.port_hashsize)
#घोषणा sctp_port_hashtable		(sctp_globals.port_hashtable)
#घोषणा sctp_transport_hashtable	(sctp_globals.transport_hashtable)
#घोषणा sctp_checksum_disable		(sctp_globals.checksum_disable)

/* SCTP Socket type: UDP or TCP style. */
क्रमागत sctp_socket_type अणु
	SCTP_SOCKET_UDP = 0,
	SCTP_SOCKET_UDP_HIGH_BANDWIDTH,
	SCTP_SOCKET_TCP
पूर्ण;

/* Per socket SCTP inक्रमmation. */
काष्ठा sctp_sock अणु
	/* inet_sock has to be the first member of sctp_sock */
	काष्ठा inet_sock inet;
	/* What kind of a socket is this? */
	क्रमागत sctp_socket_type type;

	/* PF_ family specअगरic functions.  */
	काष्ठा sctp_pf *pf;

	/* Access to HMAC transक्रमm. */
	काष्ठा crypto_shash *hmac;
	अक्षर *sctp_hmac_alg;

	/* What is our base endpoपूर्णांकer? */
	काष्ठा sctp_endpoपूर्णांक *ep;

	काष्ठा sctp_bind_bucket *bind_hash;
	/* Various Socket Options.  */
	__u16 शेष_stream;
	__u32 शेष_ppid;
	__u16 शेष_flags;
	__u32 शेष_context;
	__u32 शेष_समयtolive;
	__u32 शेष_rcv_context;
	पूर्णांक max_burst;

	/* Heartbeat पूर्णांकerval: The endpoपूर्णांक sends out a Heartbeat chunk to
	 * the destination address every heartbeat पूर्णांकerval. This value
	 * will be inherited by all new associations.
	 */
	__u32 hbपूर्णांकerval;

	__be16 udp_port;
	__be16 encap_port;

	/* This is the max_retrans value क्रम new associations. */
	__u16 pathmaxrxt;

	__u32 flowlabel;
	__u8  dscp;

	__u16 pf_retrans;
	__u16 ps_retrans;

	/* The initial Path MTU to use क्रम new associations. */
	__u32 pathmtu;

	/* The शेष SACK delay समयout क्रम new associations. */
	__u32 sackdelay;
	__u32 sackfreq;

	/* Flags controlling Heartbeat, SACK delay, and Path MTU Discovery. */
	__u32 param_flags;

	__u32 शेष_ss;

	काष्ठा sctp_rtoinfo rtoinfo;
	काष्ठा sctp_paddrparams paddrparam;
	काष्ठा sctp_assocparams assocparams;

	/*
	 * These two काष्ठाures must be grouped together क्रम the usercopy
	 * whitelist region.
	 */
	__u16 subscribe;
	काष्ठा sctp_iniपंचांगsg iniपंचांगsg;

	पूर्णांक user_frag;

	__u32 स्वतःबंद;
	__u32 adaptation_ind;
	__u32 pd_poपूर्णांक;
	__u16	nodelay:1,
		pf_expose:2,
		reuse:1,
		disable_fragments:1,
		v4mapped:1,
		frag_पूर्णांकerleave:1,
		recvrcvinfo:1,
		recvnxtinfo:1,
		data_पढ़ोy_संकेतled:1;

	atomic_t pd_mode;

	/* Fields after this poपूर्णांक will be skipped on copies, like on accept
	 * and peeloff operations
	 */

	/* Receive to here जबतक partial delivery is in effect. */
	काष्ठा sk_buff_head pd_lobby;

	काष्ठा list_head स्वतः_asconf_list;
	पूर्णांक करो_स्वतः_asconf;
पूर्ण;

अटल अंतरभूत काष्ठा sctp_sock *sctp_sk(स्थिर काष्ठा sock *sk)
अणु
       वापस (काष्ठा sctp_sock *)sk;
पूर्ण

अटल अंतरभूत काष्ठा sock *sctp_opt2sk(स्थिर काष्ठा sctp_sock *sp)
अणु
       वापस (काष्ठा sock *)sp;
पूर्ण

#अगर IS_ENABLED(CONFIG_IPV6)
काष्ठा sctp6_sock अणु
       काष्ठा sctp_sock  sctp;
       काष्ठा ipv6_pinfo inet6;
पूर्ण;
#पूर्ण_अगर /* CONFIG_IPV6 */


/* This is our APPLICATION-SPECIFIC state cookie.
 * THIS IS NOT DICTATED BY THE SPECIFICATION.
 */
/* These are the parts of an association which we send in the cookie.
 * Most of these are straight out of:
 * RFC2960 12.2 Parameters necessary per association (i.e. the TCB)
 *
 */

काष्ठा sctp_cookie अणु

	/* My	       : Tag expected in every inbound packet and sent
	 * Verअगरication: in the INIT or INIT ACK chunk.
	 * Tag	       :
	 */
	__u32 my_vtag;

	/* Peer's      : Tag expected in every outbound packet except
	 * Verअगरication: in the INIT chunk.
	 * Tag	       :
	 */
	__u32 peer_vtag;

	/* The rest of these are not from the spec, but really need to
	 * be in the cookie.
	 */

	/* My Tie Tag  : Assist in discovering a restarting association. */
	__u32 my_ttag;

	/* Peer's Tie Tag: Assist in discovering a restarting association. */
	__u32 peer_ttag;

	/* When करोes this cookie expire? */
	kसमय_प्रकार expiration;

	/* Number of inbound/outbound streams which are set
	 * and negotiated during the INIT process.
	 */
	__u16 sinit_num_ostreams;
	__u16 sinit_max_instreams;

	/* This is the first sequence number I used.  */
	__u32 initial_tsn;

	/* This holds the originating address of the INIT packet.  */
	जोड़ sctp_addr peer_addr;

	/* IG Section 2.35.3 
	 * Include the source port of the INIT-ACK
	 */
	__u16		my_port;

	__u8 prsctp_capable;

	/* Padding क्रम future use */
	__u8 padding;  		

	__u32 adaptation_ind;

	__u8 auth_अक्रमom[माप(काष्ठा sctp_paramhdr) +
			 SCTP_AUTH_RANDOM_LENGTH];
	__u8 auth_hmacs[SCTP_AUTH_NUM_HMACS * माप(__u16) + 2];
	__u8 auth_chunks[माप(काष्ठा sctp_paramhdr) + SCTP_AUTH_MAX_CHUNKS];

	/* This is a shim क्रम my peer's INIT packet, followed by
	 * a copy of the raw address list of the association.
	 * The length of the raw address list is saved in the
	 * raw_addr_list_len field, which will be used at the समय when
	 * the association TCB is re-स्थिरructed from the cookie.
	 */
	__u32 raw_addr_list_len;
	काष्ठा sctp_init_chunk peer_init[];
पूर्ण;


/* The क्रमmat of our cookie that we send to our peer. */
काष्ठा sctp_चिन्हित_cookie अणु
	__u8 signature[SCTP_SECRET_SIZE];
	__u32 __pad;		/* क्रमce sctp_cookie alignment to 64 bits */
	काष्ठा sctp_cookie c;
पूर्ण __packed;

/* This is another convenience type to allocate memory क्रम address
 * params क्रम the maximum size and pass such काष्ठाures around
 * पूर्णांकernally.
 */
जोड़ sctp_addr_param अणु
	काष्ठा sctp_paramhdr p;
	काष्ठा sctp_ipv4addr_param v4;
	काष्ठा sctp_ipv6addr_param v6;
पूर्ण;

/* A convenience type to allow walking through the various
 * parameters and aव्योम casting all over the place.
 */
जोड़ sctp_params अणु
	व्योम *v;
	काष्ठा sctp_paramhdr *p;
	काष्ठा sctp_cookie_preserve_param *lअगरe;
	काष्ठा sctp_hostname_param *dns;
	काष्ठा sctp_cookie_param *cookie;
	काष्ठा sctp_supported_addrs_param *sat;
	काष्ठा sctp_ipv4addr_param *v4;
	काष्ठा sctp_ipv6addr_param *v6;
	जोड़ sctp_addr_param *addr;
	काष्ठा sctp_adaptation_ind_param *aind;
	काष्ठा sctp_supported_ext_param *ext;
	काष्ठा sctp_अक्रमom_param *अक्रमom;
	काष्ठा sctp_chunks_param *chunks;
	काष्ठा sctp_hmac_algo_param *hmac_algo;
	काष्ठा sctp_addip_param *addip;
पूर्ण;

/* RFC 2960.  Section 3.3.5 Heartbeat.
 *    Heartbeat Inक्रमmation: variable length
 *    The Sender-specअगरic Heartbeat Info field should normally include
 *    inक्रमmation about the sender's current समय when this HEARTBEAT
 *    chunk is sent and the destination transport address to which this
 *    HEARTBEAT is sent (see Section 8.3).
 */
काष्ठा sctp_sender_hb_info अणु
	काष्ठा sctp_paramhdr param_hdr;
	जोड़ sctp_addr daddr;
	अचिन्हित दीर्घ sent_at;
	__u64 hb_nonce;
पूर्ण;

पूर्णांक sctp_stream_init(काष्ठा sctp_stream *stream, __u16 outcnt, __u16 incnt,
		     gfp_t gfp);
पूर्णांक sctp_stream_init_ext(काष्ठा sctp_stream *stream, __u16 sid);
व्योम sctp_stream_मुक्त(काष्ठा sctp_stream *stream);
व्योम sctp_stream_clear(काष्ठा sctp_stream *stream);
व्योम sctp_stream_update(काष्ठा sctp_stream *stream, काष्ठा sctp_stream *new);

/* What is the current SSN number क्रम this stream? */
#घोषणा sctp_ssn_peek(stream, type, sid) \
	(sctp_stream_##type((stream), (sid))->ssn)

/* Return the next SSN number क्रम this stream.	*/
#घोषणा sctp_ssn_next(stream, type, sid) \
	(sctp_stream_##type((stream), (sid))->ssn++)

/* Skip over this ssn and all below. */
#घोषणा sctp_ssn_skip(stream, type, sid, ssn) \
	(sctp_stream_##type((stream), (sid))->ssn = ssn + 1)

/* What is the current MID number क्रम this stream? */
#घोषणा sctp_mid_peek(stream, type, sid) \
	(sctp_stream_##type((stream), (sid))->mid)

/* Return the next MID number क्रम this stream.  */
#घोषणा sctp_mid_next(stream, type, sid) \
	(sctp_stream_##type((stream), (sid))->mid++)

/* Skip over this mid and all below. */
#घोषणा sctp_mid_skip(stream, type, sid, mid) \
	(sctp_stream_##type((stream), (sid))->mid = mid + 1)

/* What is the current MID_uo number क्रम this stream? */
#घोषणा sctp_mid_uo_peek(stream, type, sid) \
	(sctp_stream_##type((stream), (sid))->mid_uo)

/* Return the next MID_uo number क्रम this stream.  */
#घोषणा sctp_mid_uo_next(stream, type, sid) \
	(sctp_stream_##type((stream), (sid))->mid_uo++)

/*
 * Poपूर्णांकers to address related SCTP functions.
 * (i.e. things that depend on the address family.)
 */
काष्ठा sctp_af अणु
	पूर्णांक		(*sctp_xmit)	(काष्ठा sk_buff *skb,
					 काष्ठा sctp_transport *);
	पूर्णांक		(*setsockopt)	(काष्ठा sock *sk,
					 पूर्णांक level,
					 पूर्णांक optname,
					 sockptr_t optval,
					 अचिन्हित पूर्णांक optlen);
	पूर्णांक		(*माला_लोockopt)	(काष्ठा sock *sk,
					 पूर्णांक level,
					 पूर्णांक optname,
					 अक्षर __user *optval,
					 पूर्णांक __user *optlen);
	व्योम		(*get_dst)	(काष्ठा sctp_transport *t,
					 जोड़ sctp_addr *saddr,
					 काष्ठा flowi *fl,
					 काष्ठा sock *sk);
	व्योम		(*get_saddr)	(काष्ठा sctp_sock *sk,
					 काष्ठा sctp_transport *t,
					 काष्ठा flowi *fl);
	व्योम		(*copy_addrlist) (काष्ठा list_head *,
					  काष्ठा net_device *);
	पूर्णांक		(*cmp_addr)	(स्थिर जोड़ sctp_addr *addr1,
					 स्थिर जोड़ sctp_addr *addr2);
	व्योम		(*addr_copy)	(जोड़ sctp_addr *dst,
					 जोड़ sctp_addr *src);
	व्योम		(*from_skb)	(जोड़ sctp_addr *,
					 काष्ठा sk_buff *skb,
					 पूर्णांक saddr);
	व्योम		(*from_sk)	(जोड़ sctp_addr *,
					 काष्ठा sock *sk);
	व्योम		(*from_addr_param) (जोड़ sctp_addr *,
					    जोड़ sctp_addr_param *,
					    __be16 port, पूर्णांक iअगर);
	पूर्णांक		(*to_addr_param) (स्थिर जोड़ sctp_addr *,
					  जोड़ sctp_addr_param *); 
	पूर्णांक		(*addr_valid)	(जोड़ sctp_addr *,
					 काष्ठा sctp_sock *,
					 स्थिर काष्ठा sk_buff *);
	क्रमागत sctp_scope	(*scope)(जोड़ sctp_addr *);
	व्योम		(*inaddr_any)	(जोड़ sctp_addr *, __be16);
	पूर्णांक		(*is_any)	(स्थिर जोड़ sctp_addr *);
	पूर्णांक		(*available)	(जोड़ sctp_addr *,
					 काष्ठा sctp_sock *);
	पूर्णांक		(*skb_iअगर)	(स्थिर काष्ठा sk_buff *sk);
	पूर्णांक		(*is_ce)	(स्थिर काष्ठा sk_buff *sk);
	व्योम		(*seq_dump_addr)(काष्ठा seq_file *seq,
					 जोड़ sctp_addr *addr);
	व्योम		(*ecn_capable)(काष्ठा sock *sk);
	__u16		net_header_len;
	पूर्णांक		sockaddr_len;
	पूर्णांक		(*ip_options_len)(काष्ठा sock *sk);
	sa_family_t	sa_family;
	काष्ठा list_head list;
पूर्ण;

काष्ठा sctp_af *sctp_get_af_specअगरic(sa_family_t);
पूर्णांक sctp_रेजिस्टर_af(काष्ठा sctp_af *);

/* Protocol family functions. */
काष्ठा sctp_pf अणु
	व्योम (*event_msgname)(काष्ठा sctp_ulpevent *, अक्षर *, पूर्णांक *);
	व्योम (*skb_msgname)  (काष्ठा sk_buff *, अक्षर *, पूर्णांक *);
	पूर्णांक  (*af_supported) (sa_family_t, काष्ठा sctp_sock *);
	पूर्णांक  (*cmp_addr) (स्थिर जोड़ sctp_addr *,
			  स्थिर जोड़ sctp_addr *,
			  काष्ठा sctp_sock *);
	पूर्णांक  (*bind_verअगरy) (काष्ठा sctp_sock *, जोड़ sctp_addr *);
	पूर्णांक  (*send_verअगरy) (काष्ठा sctp_sock *, जोड़ sctp_addr *);
	पूर्णांक  (*supported_addrs)(स्थिर काष्ठा sctp_sock *, __be16 *);
	काष्ठा sock *(*create_accept_sk) (काष्ठा sock *sk,
					  काष्ठा sctp_association *asoc,
					  bool kern);
	पूर्णांक (*addr_to_user)(काष्ठा sctp_sock *sk, जोड़ sctp_addr *addr);
	व्योम (*to_sk_saddr)(जोड़ sctp_addr *, काष्ठा sock *sk);
	व्योम (*to_sk_daddr)(जोड़ sctp_addr *, काष्ठा sock *sk);
	व्योम (*copy_ip_options)(काष्ठा sock *sk, काष्ठा sock *newsk);
	काष्ठा sctp_af *af;
पूर्ण;


/* Structure to track chunk fragments that have been acked, but peer
 * fragments of the same message have not.
 */
काष्ठा sctp_datamsg अणु
	/* Chunks रुकोing to be submitted to lower layer. */
	काष्ठा list_head chunks;
	/* Reference counting. */
	refcount_t refcnt;
	/* When is this message no दीर्घer पूर्णांकeresting to the peer? */
	अचिन्हित दीर्घ expires_at;
	/* Did the messenge fail to send? */
	पूर्णांक send_error;
	u8 send_failed:1,
	   can_delay:1,	/* should this message be Nagle delayed */
	   abanकरोned:1;	/* should this message be abanकरोned */
पूर्ण;

काष्ठा sctp_datamsg *sctp_datamsg_from_user(काष्ठा sctp_association *,
					    काष्ठा sctp_sndrcvinfo *,
					    काष्ठा iov_iter *);
व्योम sctp_datamsg_मुक्त(काष्ठा sctp_datamsg *);
व्योम sctp_datamsg_put(काष्ठा sctp_datamsg *);
व्योम sctp_chunk_fail(काष्ठा sctp_chunk *, पूर्णांक error);
पूर्णांक sctp_chunk_abanकरोned(काष्ठा sctp_chunk *);

/* RFC2960 1.4 Key Terms
 *
 * o Chunk: A unit of inक्रमmation within an SCTP packet, consisting of
 * a chunk header and chunk-specअगरic content.
 *
 * As a matter of convenience, we remember the SCTP common header क्रम
 * each chunk as well as a few other header poपूर्णांकers...
 */
काष्ठा sctp_chunk अणु
	काष्ठा list_head list;

	refcount_t refcnt;

	/* How many बार this chunk have been sent, क्रम prsctp RTX policy */
	पूर्णांक sent_count;

	जोड़ अणु
		/* This is our link to the per-transport transmitted list.  */
		काष्ठा list_head transmitted_list;
		/* List in specअगरic stream outq */
		काष्ठा list_head stream_list;
	पूर्ण;

	/* This field is used by chunks that hold fragmented data.
	 * For the first fragment this is the list that holds the rest of
	 * fragments. For the reमुख्यing fragments, this is the link to the
	 * frag_list मुख्यtained in the first fragment.
	 */
	काष्ठा list_head frag_list;

	/* This poपूर्णांकs to the sk_buff containing the actual data.  */
	काष्ठा sk_buff *skb;

	जोड़ अणु
		/* In हाल of GSO packets, this will store the head one */
		काष्ठा sk_buff *head_skb;
		/* In हाल of auth enabled, this will poपूर्णांक to the shkey */
		काष्ठा sctp_shared_key *shkey;
	पूर्ण;

	/* These are the SCTP headers by reverse order in a packet.
	 * Note that some of these may happen more than once.  In that
	 * हाल, we poपूर्णांक at the "current" one, whatever that means
	 * क्रम that level of header.
	 */

	/* We poपूर्णांक this at the FIRST TLV parameter to chunk_hdr.  */
	जोड़ sctp_params param_hdr;
	जोड़ अणु
		__u8 *v;
		काष्ठा sctp_datahdr *data_hdr;
		काष्ठा sctp_inithdr *init_hdr;
		काष्ठा sctp_sackhdr *sack_hdr;
		काष्ठा sctp_heartbeathdr *hb_hdr;
		काष्ठा sctp_sender_hb_info *hbs_hdr;
		काष्ठा sctp_shutकरोwnhdr *shutकरोwn_hdr;
		काष्ठा sctp_चिन्हित_cookie *cookie_hdr;
		काष्ठा sctp_ecnehdr *ecne_hdr;
		काष्ठा sctp_cwrhdr *ecn_cwr_hdr;
		काष्ठा sctp_errhdr *err_hdr;
		काष्ठा sctp_addiphdr *addip_hdr;
		काष्ठा sctp_fwdtsn_hdr *fwdtsn_hdr;
		काष्ठा sctp_authhdr *auth_hdr;
		काष्ठा sctp_idatahdr *idata_hdr;
		काष्ठा sctp_अगरwdtsn_hdr *अगरwdtsn_hdr;
	पूर्ण subh;

	__u8 *chunk_end;

	काष्ठा sctp_chunkhdr *chunk_hdr;
	काष्ठा sctphdr *sctp_hdr;

	/* This needs to be recoverable क्रम SCTP_SEND_FAILED events. */
	काष्ठा sctp_sndrcvinfo sinfo;

	/* Which association करोes this beदीर्घ to?  */
	काष्ठा sctp_association *asoc;

	/* What endpoपूर्णांक received this chunk? */
	काष्ठा sctp_ep_common *rcvr;

	/* We fill this in अगर we are calculating RTT. */
	अचिन्हित दीर्घ sent_at;

	/* What is the origin IP address क्रम this chunk?  */
	जोड़ sctp_addr source;
	/* Destination address क्रम this chunk. */
	जोड़ sctp_addr dest;

	/* For outbound message, track all fragments क्रम SEND_FAILED. */
	काष्ठा sctp_datamsg *msg;

	/* For an inbound chunk, this tells us where it came from.
	 * For an outbound chunk, it tells us where we'd like it to
	 * go.	It is शून्य अगर we have no preference.
	 */
	काष्ठा sctp_transport *transport;

	/* SCTP-AUTH:  For the special हाल inbound processing of COOKIE-ECHO
	 * we need save a poपूर्णांकer to the AUTH chunk, since the SCTP-AUTH
	 * spec violates the principle premis that all chunks are processed
	 * in order.
	 */
	काष्ठा sk_buff *auth_chunk;

#घोषणा SCTP_CAN_FRTX 0x0
#घोषणा SCTP_NEED_FRTX 0x1
#घोषणा SCTP_DONT_FRTX 0x2
	__u16	rtt_in_progress:1,	/* This chunk used क्रम RTT calc? */
		has_tsn:1,		/* Does this chunk have a TSN yet? */
		has_ssn:1,		/* Does this chunk have a SSN yet? */
#घोषणा has_mid has_ssn
		singleton:1,		/* Only chunk in the packet? */
		end_of_packet:1,	/* Last chunk in the packet? */
		ecn_ce_करोne:1,		/* Have we processed the ECN CE bit? */
		pdiscard:1,		/* Discard the whole packet now? */
		tsn_gap_acked:1,	/* Is this chunk acked by a GAP ACK? */
		data_accepted:1,	/* At least 1 chunk accepted */
		auth:1,			/* IN: was auth'ed | OUT: needs auth */
		has_asconf:1,		/* IN: have seen an asconf beक्रमe */
		tsn_missing_report:2,	/* Data chunk missing counter. */
		fast_retransmit:2;	/* Is this chunk fast retransmitted? */
पूर्ण;

#घोषणा sctp_chunk_retransmitted(chunk)	(chunk->sent_count > 1)
व्योम sctp_chunk_hold(काष्ठा sctp_chunk *);
व्योम sctp_chunk_put(काष्ठा sctp_chunk *);
पूर्णांक sctp_user_addto_chunk(काष्ठा sctp_chunk *chunk, पूर्णांक len,
			  काष्ठा iov_iter *from);
व्योम sctp_chunk_मुक्त(काष्ठा sctp_chunk *);
व्योम  *sctp_addto_chunk(काष्ठा sctp_chunk *, पूर्णांक len, स्थिर व्योम *data);
काष्ठा sctp_chunk *sctp_chunkअगरy(काष्ठा sk_buff *,
				 स्थिर काष्ठा sctp_association *,
				 काष्ठा sock *, gfp_t gfp);
व्योम sctp_init_addrs(काष्ठा sctp_chunk *, जोड़ sctp_addr *,
		     जोड़ sctp_addr *);
स्थिर जोड़ sctp_addr *sctp_source(स्थिर काष्ठा sctp_chunk *chunk);

अटल अंतरभूत __u16 sctp_chunk_stream_no(काष्ठा sctp_chunk *ch)
अणु
	वापस ntohs(ch->subh.data_hdr->stream);
पूर्ण

क्रमागत अणु
	SCTP_ADDR_NEW,		/* new address added to assoc/ep */
	SCTP_ADDR_SRC,		/* address can be used as source */
	SCTP_ADDR_DEL,		/* address about to be deleted */
पूर्ण;

/* This is a काष्ठाure क्रम holding either an IPv6 or an IPv4 address.  */
काष्ठा sctp_sockaddr_entry अणु
	काष्ठा list_head list;
	काष्ठा rcu_head	rcu;
	जोड़ sctp_addr a;
	__u8 state;
	__u8 valid;
पूर्ण;

#घोषणा SCTP_ADDRESS_TICK_DELAY	500

/* This काष्ठाure holds lists of chunks as we are assembling क्रम
 * transmission.
 */
काष्ठा sctp_packet अणु
	/* These are the SCTP header values (host order) क्रम the packet. */
	__u16 source_port;
	__u16 destination_port;
	__u32 vtag;

	/* This contains the payload chunks.  */
	काष्ठा list_head chunk_list;

	/* This is the overhead of the sctp and ip headers. */
	माप_प्रकार overhead;
	/* This is the total size of all chunks INCLUDING padding.  */
	माप_प्रकार size;
	/* This is the maximum size this packet may have */
	माप_प्रकार max_size;

	/* The packet is destined क्रम this transport address.
	 * The function we finally use to pass करोwn to the next lower
	 * layer lives in the transport काष्ठाure.
	 */
	काष्ठा sctp_transport *transport;

	/* poपूर्णांकer to the auth chunk क्रम this packet */
	काष्ठा sctp_chunk *auth;

	u8  has_cookie_echo:1,	/* This packet contains a COOKIE-ECHO chunk. */
	    has_sack:1,		/* This packet contains a SACK chunk. */
	    has_auth:1,		/* This packet contains an AUTH chunk */
	    has_data:1,		/* This packet contains at least 1 DATA chunk */
	    ipfragok:1;		/* So let ip fragment this packet */
पूर्ण;

व्योम sctp_packet_init(काष्ठा sctp_packet *, काष्ठा sctp_transport *,
		      __u16 sport, __u16 dport);
व्योम sctp_packet_config(काष्ठा sctp_packet *, __u32 vtag, पूर्णांक);
क्रमागत sctp_xmit sctp_packet_transmit_chunk(काष्ठा sctp_packet *packet,
					  काष्ठा sctp_chunk *chunk,
					  पूर्णांक one_packet, gfp_t gfp);
क्रमागत sctp_xmit sctp_packet_append_chunk(काष्ठा sctp_packet *packet,
					काष्ठा sctp_chunk *chunk);
पूर्णांक sctp_packet_transmit(काष्ठा sctp_packet *, gfp_t);
व्योम sctp_packet_मुक्त(काष्ठा sctp_packet *);

अटल अंतरभूत पूर्णांक sctp_packet_empty(काष्ठा sctp_packet *packet)
अणु
	वापस packet->size == packet->overhead;
पूर्ण

/* This represents a remote transport address.
 * For local transport addresses, we just use जोड़ sctp_addr.
 *
 * RFC2960 Section 1.4 Key Terms
 *
 *   o	Transport address:  A Transport Address is traditionally defined
 *	by Network Layer address, Transport Layer protocol and Transport
 *	Layer port number.  In the हाल of SCTP running over IP, a
 *	transport address is defined by the combination of an IP address
 *	and an SCTP port number (where SCTP is the Transport protocol).
 *
 * RFC2960 Section 7.1 SCTP Dअगरferences from TCP Congestion control
 *
 *   o	The sender keeps a separate congestion control parameter set क्रम
 *	each of the destination addresses it can send to (not each
 *	source-destination pair but क्रम each destination).  The parameters
 *	should decay अगर the address is not used क्रम a दीर्घ enough समय
 *	period.
 *
 */
काष्ठा sctp_transport अणु
	/* A list of transports. */
	काष्ठा list_head transports;
	काष्ठा rhlist_head node;

	/* Reference counting. */
	refcount_t refcnt;
		/* RTO-Pending : A flag used to track अगर one of the DATA
		 *		chunks sent to this address is currently being
		 *		used to compute a RTT. If this flag is 0,
		 *		the next DATA chunk sent to this destination
		 *		should be used to compute a RTT and this flag
		 *		should be set. Every समय the RTT
		 *		calculation completes (i.e. the DATA chunk
		 *		is SACK'd) clear this flag.
		 */
	__u32	rto_pending:1,

		/*
		 * hb_sent : a flag that संकेतs that we have a pending
		 * heartbeat.
		 */
		hb_sent:1,

		/* Is the Path MTU update pending on this tranport */
		pmtu_pending:1,

		dst_pending_confirm:1,	/* need to confirm neighbour */

		/* Has this transport moved the ctsn since we last sacked */
		sack_generation:1;
	u32 dst_cookie;

	काष्ठा flowi fl;

	/* This is the peer's IP address and port. */
	जोड़ sctp_addr ipaddr;

	/* These are the functions we call to handle LLP stuff.	 */
	काष्ठा sctp_af *af_specअगरic;

	/* Which association करो we beदीर्घ to?  */
	काष्ठा sctp_association *asoc;

	/* RFC2960
	 *
	 * 12.3 Per Transport Address Data
	 *
	 * For each destination transport address in the peer's
	 * address list derived from the INIT or INIT ACK chunk, a
	 * number of data elements needs to be मुख्यtained including:
	 */
	/* RTO	       : The current retransmission समयout value.  */
	अचिन्हित दीर्घ rto;

	__u32 rtt;		/* This is the most recent RTT.	 */

	/* RTTVAR      : The current RTT variation.  */
	__u32 rttvar;

	/* SRTT	       : The current smoothed round trip समय.	*/
	__u32 srtt;

	/*
	 * These are the congestion stats.
	 */
	/* cwnd	       : The current congestion winकरोw.	 */
	__u32 cwnd;		  /* This is the actual cwnd.  */

	/* ssthresh    : The current slow start threshold value.  */
	__u32 ssthresh;

	/* partial     : The tracking method क्रम increase of cwnd when in
	 * bytes acked : congestion aव्योमance mode (see Section 6.2.2)
	 */
	__u32 partial_bytes_acked;

	/* Data that has been sent, but not acknowledged. */
	__u32 flight_size;

	__u32 burst_limited;	/* Holds old cwnd when max.burst is applied */

	/* Destination */
	काष्ठा dst_entry *dst;
	/* Source address. */
	जोड़ sctp_addr saddr;

	/* Heartbeat पूर्णांकerval: The endpoपूर्णांक sends out a Heartbeat chunk to
	 * the destination address every heartbeat पूर्णांकerval.
	 */
	अचिन्हित दीर्घ hbपूर्णांकerval;

	/* SACK delay समयout */
	अचिन्हित दीर्घ sackdelay;
	__u32 sackfreq;

	atomic_t mtu_info;

	/* When was the last समय that we heard from this transport? We use
	 * this to pick new active and retran paths.
	 */
	kसमय_प्रकार last_समय_heard;

	/* When was the last समय that we sent a chunk using this
	 * transport? We use this to check क्रम idle transports
	 */
	अचिन्हित दीर्घ last_समय_sent;

	/* Last समय(in jअगरfies) when cwnd is reduced due to the congestion
	 * indication based on ECNE chunk.
	 */
	अचिन्हित दीर्घ last_समय_ecne_reduced;

	__be16 encap_port;

	/* This is the max_retrans value क्रम the transport and will
	 * be initialized from the assocs value.  This can be changed
	 * using the SCTP_SET_PEER_ADDR_PARAMS socket option.
	 */
	__u16 pathmaxrxt;

	__u32 flowlabel;
	__u8  dscp;

	/* This is the partially failed retrans value क्रम the transport
	 * and will be initialized from the assocs value.  This can be changed
	 * using the SCTP_PEER_ADDR_THLDS socket option
	 */
	__u16 pf_retrans;
	/* Used क्रम primary path चयनover. */
	__u16 ps_retrans;
	/* PMTU	      : The current known path MTU.  */
	__u32 pathmtu;

	/* Flags controlling Heartbeat, SACK delay, and Path MTU Discovery. */
	__u32 param_flags;

	/* The number of बार INIT has been sent on this transport. */
	पूर्णांक init_sent_count;

	/* state       : The current state of this destination,
	 *             : i.e. SCTP_ACTIVE, SCTP_INACTIVE, SCTP_UNKNOWN.
	 */
	पूर्णांक state;

	/* These are the error stats क्रम this destination.  */

	/* Error count : The current error count क्रम this destination.	*/
	अचिन्हित लघु error_count;

	/* Per	       : A समयr used by each destination.
	 * Destination :
	 * Timer       :
	 *
	 * [Everywhere अन्यथा in the text this is called T3-rtx. -ed]
	 */
	काष्ठा समयr_list T3_rtx_समयr;

	/* Heartbeat समयr is per destination. */
	काष्ठा समयr_list hb_समयr;

	/* Timer to handle ICMP proto unreachable envets */
	काष्ठा समयr_list proto_unreach_समयr;

	/* Timer to handler reconf chunk rtx */
	काष्ठा समयr_list reconf_समयr;

	/* Since we're using per-destination retransmission समयrs
	 * (see above), we're also using per-destination "transmitted"
	 * queues.  This probably ought to be a निजी काष्ठा
	 * accessible only within the outqueue, but it's not, yet.
	 */
	काष्ठा list_head transmitted;

	/* We build bundle-able packets क्रम this transport here.  */
	काष्ठा sctp_packet packet;

	/* This is the list of transports that have chunks to send.  */
	काष्ठा list_head send_पढ़ोy;

	/* State inक्रमmation saved क्रम SFR_CACC algorithm. The key
	 * idea in SFR_CACC is to मुख्यtain state at the sender on a
	 * per-destination basis when a changeover happens.
	 *	अक्षर changeover_active;
	 *	अक्षर cycling_changeover;
	 *	__u32 next_tsn_at_change;
	 *	अक्षर cacc_saw_newack;
	 */
	काष्ठा अणु
		/* An अचिन्हित पूर्णांकeger, which stores the next TSN to be
		 * used by the sender, at the moment of changeover.
		 */
		__u32 next_tsn_at_change;

		/* A flag which indicates the occurrence of a changeover */
		अक्षर changeover_active;

		/* A flag which indicates whether the change of primary is
		 * the first चयन to this destination address during an
		 * active चयन.
		 */
		अक्षर cycling_changeover;

		/* A temporary flag, which is used during the processing of
		 * a SACK to estimate the causative TSN(s)'s group.
		 */
		अक्षर cacc_saw_newack;
	पूर्ण cacc;

	/* 64-bit अक्रमom number sent with heartbeat. */
	__u64 hb_nonce;

	काष्ठा rcu_head rcu;
पूर्ण;

काष्ठा sctp_transport *sctp_transport_new(काष्ठा net *, स्थिर जोड़ sctp_addr *,
					  gfp_t);
व्योम sctp_transport_set_owner(काष्ठा sctp_transport *,
			      काष्ठा sctp_association *);
व्योम sctp_transport_route(काष्ठा sctp_transport *, जोड़ sctp_addr *,
			  काष्ठा sctp_sock *);
व्योम sctp_transport_pmtu(काष्ठा sctp_transport *, काष्ठा sock *sk);
व्योम sctp_transport_मुक्त(काष्ठा sctp_transport *);
व्योम sctp_transport_reset_t3_rtx(काष्ठा sctp_transport *);
व्योम sctp_transport_reset_hb_समयr(काष्ठा sctp_transport *);
व्योम sctp_transport_reset_reconf_समयr(काष्ठा sctp_transport *transport);
पूर्णांक sctp_transport_hold(काष्ठा sctp_transport *);
व्योम sctp_transport_put(काष्ठा sctp_transport *);
व्योम sctp_transport_update_rto(काष्ठा sctp_transport *, __u32);
व्योम sctp_transport_उठाओ_cwnd(काष्ठा sctp_transport *, __u32, __u32);
व्योम sctp_transport_lower_cwnd(काष्ठा sctp_transport *t,
			       क्रमागत sctp_lower_cwnd reason);
व्योम sctp_transport_burst_limited(काष्ठा sctp_transport *);
व्योम sctp_transport_burst_reset(काष्ठा sctp_transport *);
अचिन्हित दीर्घ sctp_transport_समयout(काष्ठा sctp_transport *);
व्योम sctp_transport_reset(काष्ठा sctp_transport *t);
bool sctp_transport_update_pmtu(काष्ठा sctp_transport *t, u32 pmtu);
व्योम sctp_transport_immediate_rtx(काष्ठा sctp_transport *);
व्योम sctp_transport_dst_release(काष्ठा sctp_transport *t);
व्योम sctp_transport_dst_confirm(काष्ठा sctp_transport *t);


/* This is the काष्ठाure we use to queue packets as they come पूर्णांकo
 * SCTP.  We ग_लिखो packets to it and पढ़ो chunks from it.
 */
काष्ठा sctp_inq अणु
	/* This is actually a queue of sctp_chunk each
	 * containing a partially decoded packet.
	 */
	काष्ठा list_head in_chunk_list;
	/* This is the packet which is currently off the in queue and is
	 * being worked on through the inbound chunk processing.
	 */
	काष्ठा sctp_chunk *in_progress;

	/* This is the delayed task to finish delivering inbound
	 * messages.
	 */
	काष्ठा work_काष्ठा immediate;
पूर्ण;

व्योम sctp_inq_init(काष्ठा sctp_inq *);
व्योम sctp_inq_मुक्त(काष्ठा sctp_inq *);
व्योम sctp_inq_push(काष्ठा sctp_inq *, काष्ठा sctp_chunk *packet);
काष्ठा sctp_chunk *sctp_inq_pop(काष्ठा sctp_inq *);
काष्ठा sctp_chunkhdr *sctp_inq_peek(काष्ठा sctp_inq *);
व्योम sctp_inq_set_th_handler(काष्ठा sctp_inq *, work_func_t);

/* This is the काष्ठाure we use to hold outbound chunks.  You push
 * chunks in and they स्वतःmatically pop out the other end as bundled
 * packets (it calls (*output_handler)()).
 *
 * This काष्ठाure covers sections 6.3, 6.4, 6.7, 6.8, 6.10, 7., 8.1,
 * and 8.2 of the v13 draft.
 *
 * It handles retransmissions.	The connection to the समयout portion
 * of the state machine is through sctp_..._समयout() and समयout_handler.
 *
 * If you feed it SACKs, it will eat them.
 *
 * If you give it big chunks, it will fragment them.
 *
 * It assigns TSN's to data chunks.  This happens at the last possible
 * instant beक्रमe transmission.
 *
 * When मुक्त()'d, it empties itself out via output_handler().
 */
काष्ठा sctp_outq अणु
	काष्ठा sctp_association *asoc;

	/* Data pending that has never been transmitted.  */
	काष्ठा list_head out_chunk_list;

	/* Stream scheduler being used */
	काष्ठा sctp_sched_ops *sched;

	अचिन्हित पूर्णांक out_qlen;	/* Total length of queued data chunks. */

	/* Error of send failed, may used in SCTP_SEND_FAILED event. */
	अचिन्हित पूर्णांक error;

	/* These are control chunks we want to send.  */
	काष्ठा list_head control_chunk_list;

	/* These are chunks that have been sacked but are above the
	 * CTSN, or cumulative tsn ack poपूर्णांक.
	 */
	काष्ठा list_head sacked;

	/* Put chunks on this list to schedule them क्रम
	 * retransmission.
	 */
	काष्ठा list_head retransmit;

	/* Put chunks on this list to save them क्रम FWD TSN processing as
	 * they were abanकरोned.
	 */
	काष्ठा list_head abanकरोned;

	/* How many unackd bytes करो we have in-flight?	*/
	__u32 outstanding_bytes;

	/* Are we करोing fast-rtx on this queue */
	अक्षर fast_rtx;

	/* Corked? */
	अक्षर cork;
पूर्ण;

व्योम sctp_outq_init(काष्ठा sctp_association *, काष्ठा sctp_outq *);
व्योम sctp_outq_tearकरोwn(काष्ठा sctp_outq *);
व्योम sctp_outq_मुक्त(काष्ठा sctp_outq*);
व्योम sctp_outq_tail(काष्ठा sctp_outq *, काष्ठा sctp_chunk *chunk, gfp_t);
पूर्णांक sctp_outq_sack(काष्ठा sctp_outq *, काष्ठा sctp_chunk *);
पूर्णांक sctp_outq_is_empty(स्थिर काष्ठा sctp_outq *);
व्योम sctp_outq_restart(काष्ठा sctp_outq *);

व्योम sctp_retransmit(काष्ठा sctp_outq *q, काष्ठा sctp_transport *transport,
		     क्रमागत sctp_retransmit_reason reason);
व्योम sctp_retransmit_mark(काष्ठा sctp_outq *, काष्ठा sctp_transport *, __u8);
व्योम sctp_outq_uncork(काष्ठा sctp_outq *, gfp_t gfp);
व्योम sctp_prsctp_prune(काष्ठा sctp_association *asoc,
		       काष्ठा sctp_sndrcvinfo *sinfo, पूर्णांक msg_len);
व्योम sctp_generate_fwdtsn(काष्ठा sctp_outq *q, __u32 sack_ctsn);
/* Uncork and flush an outqueue.  */
अटल अंतरभूत व्योम sctp_outq_cork(काष्ठा sctp_outq *q)
अणु
	q->cork = 1;
पूर्ण

/* SCTP skb control block.
 * sctp_input_cb is currently used on rx and sock rx queue
 */
काष्ठा sctp_input_cb अणु
	जोड़ अणु
		काष्ठा inet_skb_parm    h4;
#अगर IS_ENABLED(CONFIG_IPV6)
		काष्ठा inet6_skb_parm   h6;
#पूर्ण_अगर
	पूर्ण header;
	काष्ठा sctp_chunk *chunk;
	काष्ठा sctp_af *af;
	__be16 encap_port;
पूर्ण;
#घोषणा SCTP_INPUT_CB(__skb)	((काष्ठा sctp_input_cb *)&((__skb)->cb[0]))

काष्ठा sctp_output_cb अणु
	काष्ठा sk_buff *last;
पूर्ण;
#घोषणा SCTP_OUTPUT_CB(__skb)	((काष्ठा sctp_output_cb *)&((__skb)->cb[0]))

अटल अंतरभूत स्थिर काष्ठा sk_buff *sctp_gso_headskb(स्थिर काष्ठा sk_buff *skb)
अणु
	स्थिर काष्ठा sctp_chunk *chunk = SCTP_INPUT_CB(skb)->chunk;

	वापस chunk->head_skb ? : skb;
पूर्ण

/* These bind address data fields common between endpoपूर्णांकs and associations */
काष्ठा sctp_bind_addr अणु

	/* RFC 2960 12.1 Parameters necessary क्रम the SCTP instance
	 *
	 * SCTP Port:	The local SCTP port number the endpoपूर्णांक is
	 *		bound to.
	 */
	__u16 port;

	/* RFC 2960 12.1 Parameters necessary क्रम the SCTP instance
	 *
	 * Address List: The list of IP addresses that this instance
	 *	has bound.  This inक्रमmation is passed to one's
	 *	peer(s) in INIT and INIT ACK chunks.
	 */
	काष्ठा list_head address_list;
पूर्ण;

व्योम sctp_bind_addr_init(काष्ठा sctp_bind_addr *, __u16 port);
व्योम sctp_bind_addr_मुक्त(काष्ठा sctp_bind_addr *);
पूर्णांक sctp_bind_addr_copy(काष्ठा net *net, काष्ठा sctp_bind_addr *dest,
			स्थिर काष्ठा sctp_bind_addr *src,
			क्रमागत sctp_scope scope, gfp_t gfp,
			पूर्णांक flags);
पूर्णांक sctp_bind_addr_dup(काष्ठा sctp_bind_addr *dest,
			स्थिर काष्ठा sctp_bind_addr *src,
			gfp_t gfp);
पूर्णांक sctp_add_bind_addr(काष्ठा sctp_bind_addr *, जोड़ sctp_addr *,
		       पूर्णांक new_size, __u8 addr_state, gfp_t gfp);
पूर्णांक sctp_del_bind_addr(काष्ठा sctp_bind_addr *, जोड़ sctp_addr *);
पूर्णांक sctp_bind_addr_match(काष्ठा sctp_bind_addr *, स्थिर जोड़ sctp_addr *,
			 काष्ठा sctp_sock *);
पूर्णांक sctp_bind_addr_conflict(काष्ठा sctp_bind_addr *, स्थिर जोड़ sctp_addr *,
			 काष्ठा sctp_sock *, काष्ठा sctp_sock *);
पूर्णांक sctp_bind_addr_state(स्थिर काष्ठा sctp_bind_addr *bp,
			 स्थिर जोड़ sctp_addr *addr);
पूर्णांक sctp_bind_addrs_check(काष्ठा sctp_sock *sp,
			  काष्ठा sctp_sock *sp2, पूर्णांक cnt2);
जोड़ sctp_addr *sctp_find_unmatch_addr(काष्ठा sctp_bind_addr	*bp,
					स्थिर जोड़ sctp_addr	*addrs,
					पूर्णांक			addrcnt,
					काष्ठा sctp_sock	*opt);
जोड़ sctp_params sctp_bind_addrs_to_raw(स्थिर काष्ठा sctp_bind_addr *bp,
					 पूर्णांक *addrs_len,
					 gfp_t gfp);
पूर्णांक sctp_raw_to_bind_addrs(काष्ठा sctp_bind_addr *bp, __u8 *raw, पूर्णांक len,
			   __u16 port, gfp_t gfp);

क्रमागत sctp_scope sctp_scope(स्थिर जोड़ sctp_addr *addr);
पूर्णांक sctp_in_scope(काष्ठा net *net, स्थिर जोड़ sctp_addr *addr,
		  स्थिर क्रमागत sctp_scope scope);
पूर्णांक sctp_is_any(काष्ठा sock *sk, स्थिर जोड़ sctp_addr *addr);
पूर्णांक sctp_is_ep_boundall(काष्ठा sock *sk);


/* What type of endpoपूर्णांक?  */
क्रमागत sctp_endpoपूर्णांक_type अणु
	SCTP_EP_TYPE_SOCKET,
	SCTP_EP_TYPE_ASSOCIATION,
पूर्ण;

/*
 * A common base class to bridge the implmentation view of a
 * socket (usually listening) endpoपूर्णांक versus an association's
 * local endpoपूर्णांक.
 * This common काष्ठाure is useful क्रम several purposes:
 *   1) Common पूर्णांकerface क्रम lookup routines.
 *	a) Subfunctions work क्रम either endpoपूर्णांक or association
 *	b) Single पूर्णांकerface to lookup allows hiding the lookup lock rather
 *	   than acquiring it बाह्यally.
 *   2) Common पूर्णांकerface क्रम the inbound chunk handling/state machine.
 *   3) Common object handling routines क्रम reference counting, etc.
 *   4) Disentangle association lookup from endpoपूर्णांक lookup, where we
 *	करो not have to find our endpoपूर्णांक to find our association.
 *
 */

काष्ठा sctp_ep_common अणु
	/* Fields to help us manage our entries in the hash tables. */
	काष्ठा hlist_node node;
	पूर्णांक hashent;

	/* Runसमय type inक्रमmation.  What kind of endpoपूर्णांक is this? */
	क्रमागत sctp_endpoपूर्णांक_type type;

	/* Some fields to help us manage this object.
	 *   refcnt   - Reference count access to this object.
	 *   dead     - Do not attempt to use this object.
	 */
	refcount_t    refcnt;
	bool	    dead;

	/* What socket करोes this endpoपूर्णांक beदीर्घ to?  */
	काष्ठा sock *sk;

	/* Cache netns and it won't change once set */
	काष्ठा net *net;

	/* This is where we receive inbound chunks.  */
	काष्ठा sctp_inq	  inqueue;

	/* This subकाष्ठाure includes the defining parameters of the
	 * endpoपूर्णांक:
	 * bind_addr.port is our shared port number.
	 * bind_addr.address_list is our set of local IP addresses.
	 */
	काष्ठा sctp_bind_addr bind_addr;
पूर्ण;


/* RFC Section 1.4 Key Terms
 *
 * o SCTP endpoपूर्णांक: The logical sender/receiver of SCTP packets. On a
 *   multi-homed host, an SCTP endpoपूर्णांक is represented to its peers as a
 *   combination of a set of eligible destination transport addresses to
 *   which SCTP packets can be sent and a set of eligible source
 *   transport addresses from which SCTP packets can be received.
 *   All transport addresses used by an SCTP endpoपूर्णांक must use the
 *   same port number, but can use multiple IP addresses. A transport
 *   address used by an SCTP endpoपूर्णांक must not be used by another
 *   SCTP endpoपूर्णांक. In other words, a transport address is unique
 *   to an SCTP endpoपूर्णांक.
 *
 * From an implementation perspective, each socket has one of these.
 * A TCP-style socket will have exactly one association on one of
 * these.  An UDP-style socket will have multiple associations hanging
 * off one of these.
 */

काष्ठा sctp_endpoपूर्णांक अणु
	/* Common subकाष्ठाure क्रम endpoपूर्णांक and association. */
	काष्ठा sctp_ep_common base;

	/* Associations: A list of current associations and mappings
	 *	      to the data consumers क्रम each association. This
	 *	      may be in the क्रमm of a hash table or other
	 *	      implementation dependent काष्ठाure. The data
	 *	      consumers may be process identअगरication
	 *	      inक्रमmation such as file descriptors, named pipe
	 *	      poपूर्णांकer, or table poपूर्णांकers dependent on how SCTP
	 *	      is implemented.
	 */
	/* This is really a list of काष्ठा sctp_association entries. */
	काष्ठा list_head asocs;

	/* Secret Key: A secret key used by this endpoपूर्णांक to compute
	 *	      the MAC.	This SHOULD be a cryptographic quality
	 *	      अक्रमom number with a sufficient length.
	 *	      Discussion in [RFC1750] can be helpful in
	 *	      selection of the key.
	 */
	__u8 secret_key[SCTP_SECRET_SIZE];

 	/* digest:  This is a digest of the sctp cookie.  This field is
 	 * 	    only used on the receive path when we try to validate
 	 * 	    that the cookie has not been tampered with.  We put
 	 * 	    this here so we pre-allocate this once and can re-use
 	 * 	    on every receive.
 	 */
 	__u8 *digest;
 
	/* sendbuf acct. policy.	*/
	__u32 sndbuf_policy;

	/* rcvbuf acct. policy.	*/
	__u32 rcvbuf_policy;

	/* SCTP AUTH: array of the HMACs that will be allocated
	 * we need this per association so that we करोn't serialize
	 */
	काष्ठा crypto_shash **auth_hmacs;

	/* SCTP-AUTH: hmacs क्रम the endpoपूर्णांक encoded पूर्णांकo parameter */
	 काष्ठा sctp_hmac_algo_param *auth_hmacs_list;

	/* SCTP-AUTH: chunks to authenticate encoded पूर्णांकo parameter */
	काष्ठा sctp_chunks_param *auth_chunk_list;

	/* SCTP-AUTH: endpoपूर्णांक shared keys */
	काष्ठा list_head endpoपूर्णांक_shared_keys;
	__u16 active_key_id;
	__u8  ecn_enable:1,
	      auth_enable:1,
	      पूर्णांकl_enable:1,
	      prsctp_enable:1,
	      asconf_enable:1,
	      reconf_enable:1;

	__u8  strreset_enable;

	/* Security identअगरiers from incoming (INIT). These are set by
	 * security_sctp_assoc_request(). These will only be used by
	 * SCTP TCP type sockets and peeled off connections as they
	 * cause a new socket to be generated. security_sctp_sk_clone()
	 * will then plug these पूर्णांकo the new socket.
	 */

	u32 secid;
	u32 peer_secid;
पूर्ण;

/* Recover the outter endpoपूर्णांक काष्ठाure. */
अटल अंतरभूत काष्ठा sctp_endpoपूर्णांक *sctp_ep(काष्ठा sctp_ep_common *base)
अणु
	काष्ठा sctp_endpoपूर्णांक *ep;

	ep = container_of(base, काष्ठा sctp_endpoपूर्णांक, base);
	वापस ep;
पूर्ण

/* These are function signatures क्रम manipulating endpoपूर्णांकs.  */
काष्ठा sctp_endpoपूर्णांक *sctp_endpoपूर्णांक_new(काष्ठा sock *, gfp_t);
व्योम sctp_endpoपूर्णांक_मुक्त(काष्ठा sctp_endpoपूर्णांक *);
व्योम sctp_endpoपूर्णांक_put(काष्ठा sctp_endpoपूर्णांक *);
व्योम sctp_endpoपूर्णांक_hold(काष्ठा sctp_endpoपूर्णांक *);
व्योम sctp_endpoपूर्णांक_add_asoc(काष्ठा sctp_endpoपूर्णांक *, काष्ठा sctp_association *);
काष्ठा sctp_association *sctp_endpoपूर्णांक_lookup_assoc(
	स्थिर काष्ठा sctp_endpoपूर्णांक *ep,
	स्थिर जोड़ sctp_addr *paddr,
	काष्ठा sctp_transport **);
bool sctp_endpoपूर्णांक_is_peeled_off(काष्ठा sctp_endpoपूर्णांक *ep,
				 स्थिर जोड़ sctp_addr *paddr);
काष्ठा sctp_endpoपूर्णांक *sctp_endpoपूर्णांक_is_match(काष्ठा sctp_endpoपूर्णांक *,
					काष्ठा net *, स्थिर जोड़ sctp_addr *);
bool sctp_has_association(काष्ठा net *net, स्थिर जोड़ sctp_addr *laddr,
			  स्थिर जोड़ sctp_addr *paddr);

पूर्णांक sctp_verअगरy_init(काष्ठा net *net, स्थिर काष्ठा sctp_endpoपूर्णांक *ep,
		     स्थिर काष्ठा sctp_association *asoc,
		     क्रमागत sctp_cid cid, काष्ठा sctp_init_chunk *peer_init,
		     काष्ठा sctp_chunk *chunk, काष्ठा sctp_chunk **err_chunk);
पूर्णांक sctp_process_init(काष्ठा sctp_association *, काष्ठा sctp_chunk *chunk,
		      स्थिर जोड़ sctp_addr *peer,
		      काष्ठा sctp_init_chunk *init, gfp_t gfp);
__u32 sctp_generate_tag(स्थिर काष्ठा sctp_endpoपूर्णांक *);
__u32 sctp_generate_tsn(स्थिर काष्ठा sctp_endpoपूर्णांक *);

काष्ठा sctp_inithdr_host अणु
	__u32 init_tag;
	__u32 a_rwnd;
	__u16 num_outbound_streams;
	__u16 num_inbound_streams;
	__u32 initial_tsn;
पूर्ण;

काष्ठा sctp_stream_priorities अणु
	/* List of priorities scheduled */
	काष्ठा list_head prio_sched;
	/* List of streams scheduled */
	काष्ठा list_head active;
	/* The next stream in line */
	काष्ठा sctp_stream_out_ext *next;
	__u16 prio;
पूर्ण;

काष्ठा sctp_stream_out_ext अणु
	__u64 abanकरोned_unsent[SCTP_PR_INDEX(MAX) + 1];
	__u64 abanकरोned_sent[SCTP_PR_INDEX(MAX) + 1];
	काष्ठा list_head outq; /* chunks enqueued by this stream */
	जोड़ अणु
		काष्ठा अणु
			/* Scheduled streams list */
			काष्ठा list_head prio_list;
			काष्ठा sctp_stream_priorities *prio_head;
		पूर्ण;
		/* Fields used by RR scheduler */
		काष्ठा अणु
			काष्ठा list_head rr_list;
		पूर्ण;
	पूर्ण;
पूर्ण;

काष्ठा sctp_stream_out अणु
	जोड़ अणु
		__u32 mid;
		__u16 ssn;
	पूर्ण;
	__u32 mid_uo;
	काष्ठा sctp_stream_out_ext *ext;
	__u8 state;
पूर्ण;

काष्ठा sctp_stream_in अणु
	जोड़ अणु
		__u32 mid;
		__u16 ssn;
	पूर्ण;
	__u32 mid_uo;
	__u32 fsn;
	__u32 fsn_uo;
	अक्षर pd_mode;
	अक्षर pd_mode_uo;
पूर्ण;

काष्ठा sctp_stream अणु
	GENRADIX(काष्ठा sctp_stream_out) out;
	GENRADIX(काष्ठा sctp_stream_in)	in;

	__u16 outcnt;
	__u16 incnt;
	/* Current stream being sent, अगर any */
	काष्ठा sctp_stream_out *out_curr;
	जोड़ अणु
		/* Fields used by priority scheduler */
		काष्ठा अणु
			/* List of priorities scheduled */
			काष्ठा list_head prio_list;
		पूर्ण;
		/* Fields used by RR scheduler */
		काष्ठा अणु
			/* List of streams scheduled */
			काष्ठा list_head rr_list;
			/* The next stream in line */
			काष्ठा sctp_stream_out_ext *rr_next;
		पूर्ण;
	पूर्ण;
	काष्ठा sctp_stream_पूर्णांकerleave *si;
पूर्ण;

अटल अंतरभूत काष्ठा sctp_stream_out *sctp_stream_out(
	काष्ठा sctp_stream *stream,
	__u16 sid)
अणु
	वापस genradix_ptr(&stream->out, sid);
पूर्ण

अटल अंतरभूत काष्ठा sctp_stream_in *sctp_stream_in(
	काष्ठा sctp_stream *stream,
	__u16 sid)
अणु
	वापस genradix_ptr(&stream->in, sid);
पूर्ण

#घोषणा SCTP_SO(s, i) sctp_stream_out((s), (i))
#घोषणा SCTP_SI(s, i) sctp_stream_in((s), (i))

#घोषणा SCTP_STREAM_CLOSED		0x00
#घोषणा SCTP_STREAM_OPEN		0x01

अटल अंतरभूत __u16 sctp_datachk_len(स्थिर काष्ठा sctp_stream *stream)
अणु
	वापस stream->si->data_chunk_len;
पूर्ण

अटल अंतरभूत __u16 sctp_datahdr_len(स्थिर काष्ठा sctp_stream *stream)
अणु
	वापस stream->si->data_chunk_len - माप(काष्ठा sctp_chunkhdr);
पूर्ण

अटल अंतरभूत __u16 sctp_ftsnchk_len(स्थिर काष्ठा sctp_stream *stream)
अणु
	वापस stream->si->ftsn_chunk_len;
पूर्ण

अटल अंतरभूत __u16 sctp_ftsnhdr_len(स्थिर काष्ठा sctp_stream *stream)
अणु
	वापस stream->si->ftsn_chunk_len - माप(काष्ठा sctp_chunkhdr);
पूर्ण

/* SCTP_GET_ASSOC_STATS counters */
काष्ठा sctp_priv_assoc_stats अणु
	/* Maximum observed rto in the association during subsequent
	 * observations. Value is set to 0 अगर no RTO measurement took place
	 * The transport where the max_rto was observed is वापसed in
	 * obs_rto_ipaddr
	 */
	काष्ठा sockaddr_storage obs_rto_ipaddr;
	__u64 max_obs_rto;
	/* Total In and Out SACKs received and sent */
	__u64 isacks;
	__u64 osacks;
	/* Total In and Out packets received and sent */
	__u64 opackets;
	__u64 ipackets;
	/* Total retransmitted chunks */
	__u64 rtxchunks;
	/* TSN received > next expected */
	__u64 outofseqtsns;
	/* Duplicate Chunks received */
	__u64 idupchunks;
	/* Gap Ack Blocks received */
	__u64 gapcnt;
	/* Unordered data chunks sent and received */
	__u64 ouodchunks;
	__u64 iuodchunks;
	/* Ordered data chunks sent and received */
	__u64 oodchunks;
	__u64 iodchunks;
	/* Control chunks sent and received */
	__u64 octrlchunks;
	__u64 ictrlchunks;
पूर्ण;

/* RFC2960
 *
 * 12. Recommended Transmission Control Block (TCB) Parameters
 *
 * This section details a recommended set of parameters that should
 * be contained within the TCB क्रम an implementation. This section is
 * क्रम illustrative purposes and should not be deemed as requirements
 * on an implementation or as an exhaustive list of all parameters
 * inside an SCTP TCB. Each implementation may need its own additional
 * parameters क्रम optimization.
 */


/* Here we have inक्रमmation about each inभागidual association. */
काष्ठा sctp_association अणु

	/* A base काष्ठाure common to endpoपूर्णांक and association.
	 * In this context, it represents the associations's view
	 * of the local endpoपूर्णांक of the association.
	 */
	काष्ठा sctp_ep_common base;

	/* Associations on the same socket. */
	काष्ठा list_head asocs;

	/* association id. */
	sctp_assoc_t assoc_id;

	/* This is our parent endpoपूर्णांक.	 */
	काष्ठा sctp_endpoपूर्णांक *ep;

	/* These are those association elements needed in the cookie.  */
	काष्ठा sctp_cookie c;

	/* This is all inक्रमmation about our peer.  */
	काष्ठा अणु
		/* transport_addr_list
		 *
		 * Peer	       : A list of SCTP transport addresses that the
		 * Transport   : peer is bound to. This inक्रमmation is derived
		 * Address     : from the INIT or INIT ACK and is used to
		 * List	       : associate an inbound packet with a given
		 *	       : association. Normally this inक्रमmation is
		 *	       : hashed or keyed क्रम quick lookup and access
		 *	       : of the TCB.
		 *	       : The list is also initialized with the list
		 *	       : of addresses passed with the sctp_connectx()
		 *	       : call.
		 *
		 * It is a list of SCTP_transport's.
		 */
		काष्ठा list_head transport_addr_list;

		/* rwnd
		 *
		 * Peer Rwnd   : Current calculated value of the peer's rwnd.
		 */
		__u32 rwnd;

		/* transport_count
		 *
		 * Peer        : A count of the number of peer addresses
		 * Transport   : in the Peer Transport Address List.
		 * Address     :
		 * Count       :
		 */
		__u16 transport_count;

		/* port
		 *   The transport layer port number.
		 */
		__u16 port;

		/* primary_path
		 *
		 * Primary     : This is the current primary destination
		 * Path	       : transport address of the peer endpoपूर्णांक.  It
		 *	       : may also specअगरy a source transport address
		 *	       : on this endpoपूर्णांक.
		 *
		 * All of these paths live on transport_addr_list.
		 *
		 * At the bakeoffs, we discovered that the पूर्णांकent of
		 * primaryPath is that it only changes when the ULP
		 * asks to have it changed.  We add the activePath to
		 * designate the connection we are currently using to
		 * transmit new data and most control chunks.
		 */
		काष्ठा sctp_transport *primary_path;

		/* Cache the primary path address here, when we
		 * need a an address क्रम msg_name.
		 */
		जोड़ sctp_addr primary_addr;

		/* active_path
		 *   The path that we are currently using to
		 *   transmit new data and most control chunks.
		 */
		काष्ठा sctp_transport *active_path;

		/* retran_path
		 *
		 * RFC2960 6.4 Multi-homed SCTP Endpoपूर्णांकs
		 * ...
		 * Furthermore, when its peer is multi-homed, an
		 * endpoपूर्णांक SHOULD try to retransmit a chunk to an
		 * active destination transport address that is
		 * dअगरferent from the last destination address to
		 * which the DATA chunk was sent.
		 */
		काष्ठा sctp_transport *retran_path;

		/* Poपूर्णांकer to last transport I have sent on.  */
		काष्ठा sctp_transport *last_sent_to;

		/* This is the last transport I have received DATA on.	*/
		काष्ठा sctp_transport *last_data_from;

		/*
		 * Mapping  An array of bits or bytes indicating which out of
		 * Array    order TSN's have been received (relative to the
		 *	    Last Rcvd TSN). If no gaps exist, i.e. no out of
		 *	    order packets have been received, this array
		 *	    will be set to all zero. This काष्ठाure may be
		 *	    in the क्रमm of a circular buffer or bit array.
		 *
		 * Last Rcvd   : This is the last TSN received in
		 * TSN	       : sequence. This value is set initially by
		 *	       : taking the peer's Initial TSN, received in
		 *	       : the INIT or INIT ACK chunk, and subtracting
		 *	       : one from it.
		 *
		 * Throughout most of the specअगरication this is called the
		 * "Cumulative TSN ACK Point".	In this हाल, we
		 * ignore the advice in 12.2 in favour of the term
		 * used in the bulk of the text.  This value is hidden
		 * in tsn_map--we get it by calling sctp_tsnmap_get_ctsn().
		 */
		काष्ठा sctp_tsnmap tsn_map;

		/* This mask is used to disable sending the ASCONF chunk
		 * with specअगरied parameter to peer.
		 */
		__be16 addip_disabled_mask;

		/* These are capabilities which our peer advertised.  */
		__u16	ecn_capable:1,      /* Can peer करो ECN? */
			ipv4_address:1,     /* Peer understands IPv4 addresses? */
			ipv6_address:1,     /* Peer understands IPv6 addresses? */
			hostname_address:1, /* Peer understands DNS addresses? */
			asconf_capable:1,   /* Does peer support ADDIP? */
			prsctp_capable:1,   /* Can peer करो PR-SCTP? */
			reconf_capable:1,   /* Can peer करो RE-CONFIG? */
			पूर्णांकl_capable:1,     /* Can peer करो INTERLEAVE */
			auth_capable:1,     /* Is peer करोing SCTP-AUTH? */
			/* sack_needed:
			 *   This flag indicates अगर the next received
			 *   packet is to be responded to with a
			 *   SACK. This is initialized to 0.  When a packet
			 *   is received sack_cnt is incremented. If this value
			 *   reaches 2 or more, a SACK is sent and the
			 *   value is reset to 0. Note: This is used only
			 *   when no DATA chunks are received out of
			 *   order.  When DATA chunks are out of order,
			 *   SACK's are not delayed (see Section 6).
			 */
			sack_needed:1,     /* Do we need to sack the peer? */
			sack_generation:1,
			zero_winकरोw_announced:1;

		__u32	sack_cnt;

		__u32   adaptation_ind;	 /* Adaptation Code poपूर्णांक. */

		काष्ठा sctp_inithdr_host i;
		व्योम *cookie;
		पूर्णांक cookie_len;

		/* ADDIP Section 4.2 Upon reception of an ASCONF Chunk.
		 * C1) ... "Peer-Serial-Number'. This value MUST be initialized to the
		 * Initial TSN Value minus 1
		 */
		__u32 addip_serial;

		/* SCTP-AUTH: We need to know pears अक्रमom number, hmac list
		 * and authenticated chunk list.  All that is part of the
		 * cookie and these are just poपूर्णांकers to those locations
		 */
		काष्ठा sctp_अक्रमom_param *peer_अक्रमom;
		काष्ठा sctp_chunks_param *peer_chunks;
		काष्ठा sctp_hmac_algo_param *peer_hmacs;
	पूर्ण peer;

	/* State       : A state variable indicating what state the
	 *	       : association is in, i.e. COOKIE-WAIT,
	 *	       : COOKIE-ECHOED, ESTABLISHED, SHUTDOWN-PENDING,
	 *	       : SHUTDOWN-SENT, SHUTDOWN-RECEIVED, SHUTDOWN-ACK-SENT.
	 *
	 *		Note: No "CLOSED" state is illustrated since अगर a
	 *		association is "CLOSED" its TCB SHOULD be हटाओd.
	 *
	 *		In this implementation we DO have a CLOSED
	 *		state which is used during initiation and shutकरोwn.
	 *
	 *		State takes values from SCTP_STATE_*.
	 */
	क्रमागत sctp_state state;

	/* Overall     : The overall association error count.
	 * Error Count : [Clear this any समय I get something.]
	 */
	पूर्णांक overall_error_count;

	/* The cookie lअगरe I award क्रम any cookie.  */
	kसमय_प्रकार cookie_lअगरe;

	/* These are the association's initial, max, and min RTO values.
	 * These values will be initialized by प्रणाली शेषs, but can
	 * be modअगरied via the SCTP_RTOINFO socket option.
	 */
	अचिन्हित दीर्घ rto_initial;
	अचिन्हित दीर्घ rto_max;
	अचिन्हित दीर्घ rto_min;

	/* Maximum number of new data packets that can be sent in a burst.  */
	पूर्णांक max_burst;

	/* This is the max_retrans value क्रम the association.  This value will
	 * be initialized from प्रणाली शेषs, but can be
	 * modअगरied by the SCTP_ASSOCINFO socket option.
	 */
	पूर्णांक max_retrans;

	/* This is the partially failed retrans value क्रम the transport
	 * and will be initialized from the assocs value.  This can be
	 * changed using the SCTP_PEER_ADDR_THLDS socket option
	 */
	__u16 pf_retrans;
	/* Used क्रम primary path चयनover. */
	__u16 ps_retrans;

	/* Maximum number of बार the endpoपूर्णांक will retransmit INIT  */
	__u16 max_init_attempts;

	/* How many बार have we resent an INIT? */
	__u16 init_retries;

	/* The largest समयout or RTO value to use in attempting an INIT */
	अचिन्हित दीर्घ max_init_समयo;

	/* Heartbeat पूर्णांकerval: The endpoपूर्णांक sends out a Heartbeat chunk to
	 * the destination address every heartbeat पूर्णांकerval. This value
	 * will be inherited by all new transports.
	 */
	अचिन्हित दीर्घ hbपूर्णांकerval;

	__be16 encap_port;

	/* This is the max_retrans value क्रम new transports in the
	 * association.
	 */
	__u16 pathmaxrxt;

	__u32 flowlabel;
	__u8  dscp;

	/* Flag that path mtu update is pending */
	__u8   pmtu_pending;

	/* Association : The smallest PMTU discovered क्रम all of the
	 * PMTU	       : peer's transport addresses.
	 */
	__u32 pathmtu;

	/* Flags controlling Heartbeat, SACK delay, and Path MTU Discovery. */
	__u32 param_flags;

	__u32 sackfreq;
	/* SACK delay समयout */
	अचिन्हित दीर्घ sackdelay;

	अचिन्हित दीर्घ समयouts[SCTP_NUM_TIMEOUT_TYPES];
	काष्ठा समयr_list समयrs[SCTP_NUM_TIMEOUT_TYPES];

	/* Transport to which SHUTDOWN chunk was last sent.  */
	काष्ठा sctp_transport *shutकरोwn_last_sent_to;

	/* Transport to which INIT chunk was last sent.  */
	काष्ठा sctp_transport *init_last_sent_to;

	/* How many बार have we resent a SHUTDOWN */
	पूर्णांक shutकरोwn_retries;

	/* Next TSN    : The next TSN number to be asचिन्हित to a new
	 *	       : DATA chunk.  This is sent in the INIT or INIT
	 *	       : ACK chunk to the peer and incremented each
	 *	       : समय a DATA chunk is asचिन्हित a TSN
	 *	       : (normally just prior to transmit or during
	 *	       : fragmentation).
	 */
	__u32 next_tsn;

	/*
	 * Last Rcvd   : This is the last TSN received in sequence.  This value
	 * TSN	       : is set initially by taking the peer's Initial TSN,
	 *	       : received in the INIT or INIT ACK chunk, and
	 *	       : subtracting one from it.
	 *
	 * Most of RFC 2960 refers to this as the Cumulative TSN Ack Poपूर्णांक.
	 */

	__u32 ctsn_ack_poपूर्णांक;

	/* PR-SCTP Advanced.Peer.Ack.Poपूर्णांक */
	__u32 adv_peer_ack_poपूर्णांक;

	/* Highest TSN that is acknowledged by incoming SACKs. */
	__u32 highest_sacked;

	/* TSN marking the fast recovery निकास poपूर्णांक */
	__u32 fast_recovery_निकास;

	/* Flag to track the current fast recovery state */
	__u8 fast_recovery;

	/* The number of unacknowledged data chunks.  Reported through
	 * the SCTP_STATUS sockopt.
	 */
	__u16 unack_data;

	/* The total number of data chunks that we've had to retransmit
	 * as the result of a T3 समयr expiration
	 */
	__u32 rtx_data_chunks;

	/* This is the association's receive buffer space.  This value is used
	 * to set a_rwnd field in an INIT or a SACK chunk.
	 */
	__u32 rwnd;

	/* This is the last advertised value of rwnd over a SACK chunk. */
	__u32 a_rwnd;

	/* Number of bytes by which the rwnd has slopped.  The rwnd is allowed
	 * to slop over a maximum of the association's frag_poपूर्णांक.
	 */
	__u32 rwnd_over;

	/* Keeps treack of rwnd pressure.  This happens when we have
	 * a winकरोw, but not recevie buffer (i.e small packets).  This one
	 * is releases slowly (1 PMTU at a समय ).
	 */
	__u32 rwnd_press;

	/* This is the sndbuf size in use क्रम the association.
	 * This corresponds to the sndbuf size क्रम the association,
	 * as specअगरied in the sk->sndbuf.
	 */
	पूर्णांक sndbuf_used;

	/* This is the amount of memory that this association has allocated
	 * in the receive path at any given समय.
	 */
	atomic_t rmem_alloc;

	/* This is the रुको queue head क्रम send requests रुकोing on
	 * the association sndbuf space.
	 */
	रुको_queue_head_t	रुको;

	/* The message size at which SCTP fragmentation will occur. */
	__u32 frag_poपूर्णांक;
	__u32 user_frag;

	/* Counter used to count INIT errors. */
	पूर्णांक init_err_counter;

	/* Count the number of INIT cycles (क्रम करोubling समयout). */
	पूर्णांक init_cycle;

	/* Default send parameters. */
	__u16 शेष_stream;
	__u16 शेष_flags;
	__u32 शेष_ppid;
	__u32 शेष_context;
	__u32 शेष_समयtolive;

	/* Default receive parameters */
	__u32 शेष_rcv_context;

	/* Stream arrays */
	काष्ठा sctp_stream stream;

	/* All outbound chunks go through this काष्ठाure.  */
	काष्ठा sctp_outq outqueue;

	/* A smart pipe that will handle reordering and fragmentation,
	 * as well as handle passing events up to the ULP.
	 */
	काष्ठा sctp_ulpq ulpq;

	/* Last TSN that caused an ECNE Chunk to be sent.  */
	__u32 last_ecne_tsn;

	/* Last TSN that caused a CWR Chunk to be sent.	 */
	__u32 last_cwr_tsn;

	/* How many duplicated TSNs have we seen?  */
	पूर्णांक numduptsns;

	/* These are to support
	 * "SCTP Extensions क्रम Dynamic Reconfiguration of IP Addresses
	 *  and Enक्रमcement of Flow and Message Limits"
	 * <draft-ietf-tsvwg-addip-sctp-02.txt>
	 * or "ADDIP" क्रम लघु.
	 */



	/* ADDIP Section 4.1.1 Congestion Control of ASCONF Chunks
	 *
	 * R1) One and only one ASCONF Chunk MAY be in transit and
	 * unacknowledged at any one समय.  If a sender, after sending
	 * an ASCONF chunk, decides it needs to transfer another
	 * ASCONF Chunk, it MUST रुको until the ASCONF-ACK Chunk
	 * वापसs from the previous ASCONF Chunk beक्रमe sending a
	 * subsequent ASCONF. Note this restriction binds each side,
	 * so at any समय two ASCONF may be in-transit on any given
	 * association (one sent from each endpoपूर्णांक).
	 *
	 * [This is our one-and-only-one ASCONF in flight.  If we करो
	 * not have an ASCONF in flight, this is शून्य.]
	 */
	काष्ठा sctp_chunk *addip_last_asconf;

	/* ADDIP Section 5.2 Upon reception of an ASCONF Chunk.
	 *
	 * This is needed to implement iपंचांगes E1 - E4 of the updated
	 * spec.  Here is the justअगरication:
	 *
	 * Since the peer may bundle multiple ASCONF chunks toward us,
	 * we now need the ability to cache multiple ACKs.  The section
	 * describes in detail how they are cached and cleaned up.
	 */
	काष्ठा list_head asconf_ack_list;

	/* These ASCONF chunks are रुकोing to be sent.
	 *
	 * These chunaks can't be pushed to outqueue until receiving
	 * ASCONF_ACK क्रम the previous ASCONF indicated by
	 * addip_last_asconf, so as to guarantee that only one ASCONF
	 * is in flight at any समय.
	 *
	 * ADDIP Section 4.1.1 Congestion Control of ASCONF Chunks
	 *
	 * In defining the ASCONF Chunk transfer procedures, it is
	 * essential that these transfers MUST NOT cause congestion
	 * within the network.	To achieve this, we place these
	 * restrictions on the transfer of ASCONF Chunks:
	 *
	 * R1) One and only one ASCONF Chunk MAY be in transit and
	 * unacknowledged at any one समय.  If a sender, after sending
	 * an ASCONF chunk, decides it needs to transfer another
	 * ASCONF Chunk, it MUST रुको until the ASCONF-ACK Chunk
	 * वापसs from the previous ASCONF Chunk beक्रमe sending a
	 * subsequent ASCONF. Note this restriction binds each side,
	 * so at any समय two ASCONF may be in-transit on any given
	 * association (one sent from each endpoपूर्णांक).
	 *
	 *
	 * [I really think this is EXACTLY the sort of पूर्णांकelligence
	 *  which alपढ़ोy resides in sctp_outq.	 Please move this
	 *  queue and its supporting logic करोwn there.	--piggy]
	 */
	काष्ठा list_head addip_chunk_list;

	/* ADDIP Section 4.1 ASCONF Chunk Procedures
	 *
	 * A2) A serial number should be asचिन्हित to the Chunk. The
	 * serial number SHOULD be a monotonically increasing
	 * number. The serial number SHOULD be initialized at
	 * the start of the association to the same value as the
	 * Initial TSN and every समय a new ASCONF chunk is created
	 * it is incremented by one after assigning the serial number
	 * to the newly created chunk.
	 *
	 * ADDIP
	 * 3.1.1  Address/Stream Configuration Change Chunk (ASCONF)
	 *
	 * Serial Number : 32 bits (अचिन्हित पूर्णांकeger)
	 *
	 * This value represents a Serial Number क्रम the ASCONF
	 * Chunk. The valid range of Serial Number is from 0 to
	 * 4294967295 (2^32 - 1).  Serial Numbers wrap back to 0
	 * after reaching 4294967295.
	 */
	__u32 addip_serial;
	पूर्णांक src_out_of_asoc_ok;
	जोड़ sctp_addr *asconf_addr_del_pending;
	काष्ठा sctp_transport *new_transport;

	/* SCTP AUTH: list of the endpoपूर्णांक shared keys.  These
	 * keys are provided out of band by the user applicaton
	 * and can't change during the lअगरeसमय of the association
	 */
	काष्ठा list_head endpoपूर्णांक_shared_keys;

	/* SCTP AUTH:
	 * The current generated assocaition shared key (secret)
	 */
	काष्ठा sctp_auth_bytes *asoc_shared_key;
	काष्ठा sctp_shared_key *shkey;

	/* SCTP AUTH: hmac id of the first peer requested algorithm
	 * that we support.
	 */
	__u16 शेष_hmac_id;

	__u16 active_key_id;

	__u8 need_ecne:1,	/* Need to send an ECNE Chunk? */
	     temp:1,		/* Is it a temporary association? */
	     pf_expose:2,       /* Expose pf state? */
	     क्रमce_delay:1;

	__u8 strreset_enable;
	__u8 strreset_outstanding; /* request param count on the fly */

	__u32 strreset_outseq; /* Update after receiving response */
	__u32 strreset_inseq; /* Update after receiving request */
	__u32 strreset_result[2]; /* save the results of last 2 responses */

	काष्ठा sctp_chunk *strreset_chunk; /* save request chunk */

	काष्ठा sctp_priv_assoc_stats stats;

	पूर्णांक sent_cnt_removable;

	__u16 subscribe;

	__u64 abanकरोned_unsent[SCTP_PR_INDEX(MAX) + 1];
	__u64 abanकरोned_sent[SCTP_PR_INDEX(MAX) + 1];

	काष्ठा rcu_head rcu;
पूर्ण;


/* An eyecatcher क्रम determining अगर we are really looking at an
 * association data काष्ठाure.
 */
क्रमागत अणु
	SCTP_ASSOC_EYECATCHER = 0xa550c123,
पूर्ण;

/* Recover the outter association काष्ठाure. */
अटल अंतरभूत काष्ठा sctp_association *sctp_assoc(काष्ठा sctp_ep_common *base)
अणु
	काष्ठा sctp_association *asoc;

	asoc = container_of(base, काष्ठा sctp_association, base);
	वापस asoc;
पूर्ण

/* These are function signatures क्रम manipulating associations.	 */


काष्ठा sctp_association *
sctp_association_new(स्थिर काष्ठा sctp_endpoपूर्णांक *ep, स्थिर काष्ठा sock *sk,
		     क्रमागत sctp_scope scope, gfp_t gfp);
व्योम sctp_association_मुक्त(काष्ठा sctp_association *);
व्योम sctp_association_put(काष्ठा sctp_association *);
व्योम sctp_association_hold(काष्ठा sctp_association *);

काष्ठा sctp_transport *sctp_assoc_choose_alter_transport(
	काष्ठा sctp_association *, काष्ठा sctp_transport *);
व्योम sctp_assoc_update_retran_path(काष्ठा sctp_association *);
काष्ठा sctp_transport *sctp_assoc_lookup_paddr(स्थिर काष्ठा sctp_association *,
					  स्थिर जोड़ sctp_addr *);
पूर्णांक sctp_assoc_lookup_laddr(काष्ठा sctp_association *asoc,
			    स्थिर जोड़ sctp_addr *laddr);
काष्ठा sctp_transport *sctp_assoc_add_peer(काष्ठा sctp_association *,
				     स्थिर जोड़ sctp_addr *address,
				     स्थिर gfp_t gfp,
				     स्थिर पूर्णांक peer_state);
व्योम sctp_assoc_del_peer(काष्ठा sctp_association *asoc,
			 स्थिर जोड़ sctp_addr *addr);
व्योम sctp_assoc_rm_peer(काष्ठा sctp_association *asoc,
			 काष्ठा sctp_transport *peer);
व्योम sctp_assoc_control_transport(काष्ठा sctp_association *asoc,
				  काष्ठा sctp_transport *transport,
				  क्रमागत sctp_transport_cmd command,
				  sctp_sn_error_t error);
काष्ठा sctp_transport *sctp_assoc_lookup_tsn(काष्ठा sctp_association *, __u32);
व्योम sctp_assoc_migrate(काष्ठा sctp_association *, काष्ठा sock *);
पूर्णांक sctp_assoc_update(काष्ठा sctp_association *old,
		      काष्ठा sctp_association *new);

__u32 sctp_association_get_next_tsn(काष्ठा sctp_association *);

व्योम sctp_assoc_update_frag_poपूर्णांक(काष्ठा sctp_association *asoc);
व्योम sctp_assoc_set_pmtu(काष्ठा sctp_association *asoc, __u32 pmtu);
व्योम sctp_assoc_sync_pmtu(काष्ठा sctp_association *asoc);
व्योम sctp_assoc_rwnd_increase(काष्ठा sctp_association *, अचिन्हित पूर्णांक);
व्योम sctp_assoc_rwnd_decrease(काष्ठा sctp_association *, अचिन्हित पूर्णांक);
व्योम sctp_assoc_set_primary(काष्ठा sctp_association *,
			    काष्ठा sctp_transport *);
व्योम sctp_assoc_del_nonprimary_peers(काष्ठा sctp_association *,
				    काष्ठा sctp_transport *);
पूर्णांक sctp_assoc_set_bind_addr_from_ep(काष्ठा sctp_association *asoc,
				     क्रमागत sctp_scope scope, gfp_t gfp);
पूर्णांक sctp_assoc_set_bind_addr_from_cookie(काष्ठा sctp_association *,
					 काष्ठा sctp_cookie*,
					 gfp_t gfp);
पूर्णांक sctp_assoc_set_id(काष्ठा sctp_association *, gfp_t);
व्योम sctp_assoc_clean_asconf_ack_cache(स्थिर काष्ठा sctp_association *asoc);
काष्ठा sctp_chunk *sctp_assoc_lookup_asconf_ack(
					स्थिर काष्ठा sctp_association *asoc,
					__be32 serial);
व्योम sctp_asconf_queue_tearकरोwn(काष्ठा sctp_association *asoc);

पूर्णांक sctp_cmp_addr_exact(स्थिर जोड़ sctp_addr *ss1,
			स्थिर जोड़ sctp_addr *ss2);
काष्ठा sctp_chunk *sctp_get_ecne_prepend(काष्ठा sctp_association *asoc);

/* A convenience काष्ठाure to parse out SCTP specअगरic CMSGs. */
काष्ठा sctp_cmsgs अणु
	काष्ठा sctp_iniपंचांगsg *init;
	काष्ठा sctp_sndrcvinfo *srinfo;
	काष्ठा sctp_sndinfo *sinfo;
	काष्ठा sctp_prinfo *prinfo;
	काष्ठा sctp_authinfo *authinfo;
	काष्ठा msghdr *addrs_msg;
पूर्ण;

/* Structure क्रम tracking memory objects */
काष्ठा sctp_dbg_objcnt_entry अणु
	अक्षर *label;
	atomic_t *counter;
पूर्ण;

#पूर्ण_अगर /* __sctp_काष्ठाs_h__ */
