<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/* IP Virtual Server
 * data काष्ठाure and functionality definitions
 */

#अगर_अघोषित _NET_IP_VS_H
#घोषणा _NET_IP_VS_H

#समावेश <linux/ip_vs.h>                /* definitions shared with userland */

#समावेश <यंत्र/types.h>                  /* क्रम __uXX types */

#समावेश <linux/list.h>                 /* क्रम काष्ठा list_head */
#समावेश <linux/spinlock.h>             /* क्रम काष्ठा rwlock_t */
#समावेश <linux/atomic.h>               /* क्रम काष्ठा atomic_t */
#समावेश <linux/refcount.h>             /* क्रम काष्ठा refcount_t */
#समावेश <linux/workqueue.h>

#समावेश <linux/compiler.h>
#समावेश <linux/समयr.h>
#समावेश <linux/bug.h>

#समावेश <net/checksum.h>
#समावेश <linux/netfilter.h>		/* क्रम जोड़ nf_inet_addr */
#समावेश <linux/ip.h>
#समावेश <linux/ipv6.h>			/* क्रम काष्ठा ipv6hdr */
#समावेश <net/ipv6.h>
#अगर IS_ENABLED(CONFIG_NF_CONNTRACK)
#समावेश <net/netfilter/nf_conntrack.h>
#पूर्ण_अगर
#समावेश <net/net_namespace.h>		/* Netw namespace */

#घोषणा IP_VS_HDR_INVERSE	1
#घोषणा IP_VS_HDR_ICMP		2

/* Generic access of ipvs काष्ठा */
अटल अंतरभूत काष्ठा netns_ipvs *net_ipvs(काष्ठा net* net)
अणु
	वापस net->ipvs;
पूर्ण

/* Connections' size value needed by ip_vs_ctl.c */
बाह्य पूर्णांक ip_vs_conn_tab_size;

काष्ठा ip_vs_iphdr अणु
	पूर्णांक hdr_flags;	/* ipvs flags */
	__u32 off;	/* Where IP or IPv4 header starts */
	__u32 len;	/* IPv4 simply where L4 starts
			 * IPv6 where L4 Transport Header starts */
	__u16 fragoffs; /* IPv6 fragment offset, 0 अगर first frag (or not frag)*/
	__s16 protocol;
	__s32 flags;
	जोड़ nf_inet_addr saddr;
	जोड़ nf_inet_addr daddr;
पूर्ण;

अटल अंतरभूत व्योम *frag_safe_skb_hp(स्थिर काष्ठा sk_buff *skb, पूर्णांक offset,
				      पूर्णांक len, व्योम *buffer)
अणु
	वापस skb_header_poपूर्णांकer(skb, offset, len, buffer);
पूर्ण

/* This function handles filling *ip_vs_iphdr, both क्रम IPv4 and IPv6.
 * IPv6 requires some extra work, as finding proper header position,
 * depend on the IPv6 extension headers.
 */
अटल अंतरभूत पूर्णांक
ip_vs_fill_iph_skb_off(पूर्णांक af, स्थिर काष्ठा sk_buff *skb, पूर्णांक offset,
		       पूर्णांक hdr_flags, काष्ठा ip_vs_iphdr *iphdr)
अणु
	iphdr->hdr_flags = hdr_flags;
	iphdr->off = offset;

#अगर_घोषित CONFIG_IP_VS_IPV6
	अगर (af == AF_INET6) अणु
		काष्ठा ipv6hdr _iph;
		स्थिर काष्ठा ipv6hdr *iph = skb_header_poपूर्णांकer(
			skb, offset, माप(_iph), &_iph);
		अगर (!iph)
			वापस 0;

		iphdr->saddr.in6 = iph->saddr;
		iphdr->daddr.in6 = iph->daddr;
		/* ipv6_find_hdr() updates len, flags */
		iphdr->len	 = offset;
		iphdr->flags	 = 0;
		iphdr->protocol  = ipv6_find_hdr(skb, &iphdr->len, -1,
						 &iphdr->fragoffs,
						 &iphdr->flags);
		अगर (iphdr->protocol < 0)
			वापस 0;
	पूर्ण अन्यथा
#पूर्ण_अगर
	अणु
		काष्ठा iphdr _iph;
		स्थिर काष्ठा iphdr *iph = skb_header_poपूर्णांकer(
			skb, offset, माप(_iph), &_iph);
		अगर (!iph)
			वापस 0;

		iphdr->len	= offset + iph->ihl * 4;
		iphdr->fragoffs	= 0;
		iphdr->protocol	= iph->protocol;
		iphdr->saddr.ip	= iph->saddr;
		iphdr->daddr.ip	= iph->daddr;
	पूर्ण

	वापस 1;
पूर्ण

अटल अंतरभूत पूर्णांक
ip_vs_fill_iph_skb_icmp(पूर्णांक af, स्थिर काष्ठा sk_buff *skb, पूर्णांक offset,
			bool inverse, काष्ठा ip_vs_iphdr *iphdr)
अणु
	पूर्णांक hdr_flags = IP_VS_HDR_ICMP;

	अगर (inverse)
		hdr_flags |= IP_VS_HDR_INVERSE;

	वापस ip_vs_fill_iph_skb_off(af, skb, offset, hdr_flags, iphdr);
पूर्ण

अटल अंतरभूत पूर्णांक
ip_vs_fill_iph_skb(पूर्णांक af, स्थिर काष्ठा sk_buff *skb, bool inverse,
		   काष्ठा ip_vs_iphdr *iphdr)
अणु
	पूर्णांक hdr_flags = 0;

	अगर (inverse)
		hdr_flags |= IP_VS_HDR_INVERSE;

	वापस ip_vs_fill_iph_skb_off(af, skb, skb_network_offset(skb),
				      hdr_flags, iphdr);
पूर्ण

अटल अंतरभूत bool
ip_vs_iph_inverse(स्थिर काष्ठा ip_vs_iphdr *iph)
अणु
	वापस !!(iph->hdr_flags & IP_VS_HDR_INVERSE);
पूर्ण

अटल अंतरभूत bool
ip_vs_iph_icmp(स्थिर काष्ठा ip_vs_iphdr *iph)
अणु
	वापस !!(iph->hdr_flags & IP_VS_HDR_ICMP);
पूर्ण

अटल अंतरभूत व्योम ip_vs_addr_copy(पूर्णांक af, जोड़ nf_inet_addr *dst,
				   स्थिर जोड़ nf_inet_addr *src)
अणु
#अगर_घोषित CONFIG_IP_VS_IPV6
	अगर (af == AF_INET6)
		dst->in6 = src->in6;
	अन्यथा
#पूर्ण_अगर
	dst->ip = src->ip;
पूर्ण

अटल अंतरभूत व्योम ip_vs_addr_set(पूर्णांक af, जोड़ nf_inet_addr *dst,
				  स्थिर जोड़ nf_inet_addr *src)
अणु
#अगर_घोषित CONFIG_IP_VS_IPV6
	अगर (af == AF_INET6) अणु
		dst->in6 = src->in6;
		वापस;
	पूर्ण
#पूर्ण_अगर
	dst->ip = src->ip;
	dst->all[1] = 0;
	dst->all[2] = 0;
	dst->all[3] = 0;
पूर्ण

अटल अंतरभूत पूर्णांक ip_vs_addr_equal(पूर्णांक af, स्थिर जोड़ nf_inet_addr *a,
				   स्थिर जोड़ nf_inet_addr *b)
अणु
#अगर_घोषित CONFIG_IP_VS_IPV6
	अगर (af == AF_INET6)
		वापस ipv6_addr_equal(&a->in6, &b->in6);
#पूर्ण_अगर
	वापस a->ip == b->ip;
पूर्ण

#अगर_घोषित CONFIG_IP_VS_DEBUG
#समावेश <linux/net.h>

पूर्णांक ip_vs_get_debug_level(व्योम);

अटल अंतरभूत स्थिर अक्षर *ip_vs_dbg_addr(पूर्णांक af, अक्षर *buf, माप_प्रकार buf_len,
					 स्थिर जोड़ nf_inet_addr *addr,
					 पूर्णांक *idx)
अणु
	पूर्णांक len;
#अगर_घोषित CONFIG_IP_VS_IPV6
	अगर (af == AF_INET6)
		len = snम_लिखो(&buf[*idx], buf_len - *idx, "[%pI6c]",
			       &addr->in6) + 1;
	अन्यथा
#पूर्ण_अगर
		len = snम_लिखो(&buf[*idx], buf_len - *idx, "%pI4",
			       &addr->ip) + 1;

	*idx += len;
	BUG_ON(*idx > buf_len + 1);
	वापस &buf[*idx - len];
पूर्ण

#घोषणा IP_VS_DBG_BUF(level, msg, ...)					\
	करो अणु								\
		अक्षर ip_vs_dbg_buf[160];				\
		पूर्णांक ip_vs_dbg_idx = 0;					\
		अगर (level <= ip_vs_get_debug_level())			\
			prपूर्णांकk(KERN_DEBUG pr_fmt(msg), ##__VA_ARGS__);	\
	पूर्ण जबतक (0)
#घोषणा IP_VS_ERR_BUF(msg...)						\
	करो अणु								\
		अक्षर ip_vs_dbg_buf[160];				\
		पूर्णांक ip_vs_dbg_idx = 0;					\
		pr_err(msg);						\
	पूर्ण जबतक (0)

/* Only use from within IP_VS_DBG_BUF() or IP_VS_ERR_BUF macros */
#घोषणा IP_VS_DBG_ADDR(af, addr)					\
	ip_vs_dbg_addr(af, ip_vs_dbg_buf,				\
		       माप(ip_vs_dbg_buf), addr,			\
		       &ip_vs_dbg_idx)

#घोषणा IP_VS_DBG(level, msg, ...)					\
	करो अणु								\
		अगर (level <= ip_vs_get_debug_level())			\
			prपूर्णांकk(KERN_DEBUG pr_fmt(msg), ##__VA_ARGS__);	\
	पूर्ण जबतक (0)
#घोषणा IP_VS_DBG_RL(msg, ...)						\
	करो अणु								\
		अगर (net_ratelimit())					\
			prपूर्णांकk(KERN_DEBUG pr_fmt(msg), ##__VA_ARGS__);	\
	पूर्ण जबतक (0)
#घोषणा IP_VS_DBG_PKT(level, af, pp, skb, ofs, msg)			\
	करो अणु								\
		अगर (level <= ip_vs_get_debug_level())			\
			pp->debug_packet(af, pp, skb, ofs, msg);	\
	पूर्ण जबतक (0)
#घोषणा IP_VS_DBG_RL_PKT(level, af, pp, skb, ofs, msg)			\
	करो अणु								\
		अगर (level <= ip_vs_get_debug_level() &&			\
		    net_ratelimit())					\
			pp->debug_packet(af, pp, skb, ofs, msg);	\
	पूर्ण जबतक (0)
#अन्यथा	/* NO DEBUGGING at ALL */
#घोषणा IP_VS_DBG_BUF(level, msg...)  करो अणुपूर्ण जबतक (0)
#घोषणा IP_VS_ERR_BUF(msg...)  करो अणुपूर्ण जबतक (0)
#घोषणा IP_VS_DBG(level, msg...)  करो अणुपूर्ण जबतक (0)
#घोषणा IP_VS_DBG_RL(msg...)  करो अणुपूर्ण जबतक (0)
#घोषणा IP_VS_DBG_PKT(level, af, pp, skb, ofs, msg)	करो अणुपूर्ण जबतक (0)
#घोषणा IP_VS_DBG_RL_PKT(level, af, pp, skb, ofs, msg)	करो अणुपूर्ण जबतक (0)
#पूर्ण_अगर

#घोषणा IP_VS_BUG() BUG()
#घोषणा IP_VS_ERR_RL(msg, ...)						\
	करो अणु								\
		अगर (net_ratelimit())					\
			pr_err(msg, ##__VA_ARGS__);			\
	पूर्ण जबतक (0)

#अगर_घोषित CONFIG_IP_VS_DEBUG
#घोषणा EnterFunction(level)						\
	करो अणु								\
		अगर (level <= ip_vs_get_debug_level())			\
			prपूर्णांकk(KERN_DEBUG				\
			       pr_fmt("Enter: %s, %s line %i\n"),	\
			       __func__, __खाता__, __LINE__);		\
	पूर्ण जबतक (0)
#घोषणा LeaveFunction(level)						\
	करो अणु								\
		अगर (level <= ip_vs_get_debug_level())			\
			prपूर्णांकk(KERN_DEBUG				\
			       pr_fmt("Leave: %s, %s line %i\n"),	\
			       __func__, __खाता__, __LINE__);		\
	पूर्ण जबतक (0)
#अन्यथा
#घोषणा EnterFunction(level)   करो अणुपूर्ण जबतक (0)
#घोषणा LeaveFunction(level)   करो अणुपूर्ण जबतक (0)
#पूर्ण_अगर

/* The port number of FTP service (in network order). */
#घोषणा FTPPORT  cpu_to_be16(21)
#घोषणा FTPDATA  cpu_to_be16(20)

/* TCP State Values */
क्रमागत अणु
	IP_VS_TCP_S_NONE = 0,
	IP_VS_TCP_S_ESTABLISHED,
	IP_VS_TCP_S_SYN_SENT,
	IP_VS_TCP_S_SYN_RECV,
	IP_VS_TCP_S_FIN_WAIT,
	IP_VS_TCP_S_TIME_WAIT,
	IP_VS_TCP_S_CLOSE,
	IP_VS_TCP_S_CLOSE_WAIT,
	IP_VS_TCP_S_LAST_ACK,
	IP_VS_TCP_S_LISTEN,
	IP_VS_TCP_S_SYNACK,
	IP_VS_TCP_S_LAST
पूर्ण;

/* UDP State Values */
क्रमागत अणु
	IP_VS_UDP_S_NORMAL,
	IP_VS_UDP_S_LAST,
पूर्ण;

/* ICMP State Values */
क्रमागत अणु
	IP_VS_ICMP_S_NORMAL,
	IP_VS_ICMP_S_LAST,
पूर्ण;

/* SCTP State Values */
क्रमागत ip_vs_sctp_states अणु
	IP_VS_SCTP_S_NONE,
	IP_VS_SCTP_S_INIT1,
	IP_VS_SCTP_S_INIT,
	IP_VS_SCTP_S_COOKIE_SENT,
	IP_VS_SCTP_S_COOKIE_REPLIED,
	IP_VS_SCTP_S_COOKIE_WAIT,
	IP_VS_SCTP_S_COOKIE,
	IP_VS_SCTP_S_COOKIE_ECHOED,
	IP_VS_SCTP_S_ESTABLISHED,
	IP_VS_SCTP_S_SHUTDOWN_SENT,
	IP_VS_SCTP_S_SHUTDOWN_RECEIVED,
	IP_VS_SCTP_S_SHUTDOWN_ACK_SENT,
	IP_VS_SCTP_S_REJECTED,
	IP_VS_SCTP_S_CLOSED,
	IP_VS_SCTP_S_LAST
पूर्ण;

/* Connection ढाँचाs use bits from state */
#घोषणा IP_VS_CTPL_S_NONE		0x0000
#घोषणा IP_VS_CTPL_S_ASSURED		0x0001
#घोषणा IP_VS_CTPL_S_LAST		0x0002

/* Delta sequence info काष्ठाure
 * Each ip_vs_conn has 2 (output AND input seq. changes).
 * Only used in the VS/NAT.
 */
काष्ठा ip_vs_seq अणु
	__u32			init_seq;	/* Add delta from this seq */
	__u32			delta;		/* Delta in sequence numbers */
	__u32			previous_delta;	/* Delta in sequence numbers
						 * beक्रमe last resized pkt */
पूर्ण;

/* counters per cpu */
काष्ठा ip_vs_counters अणु
	__u64		conns;		/* connections scheduled */
	__u64		inpkts;		/* incoming packets */
	__u64		outpkts;	/* outgoing packets */
	__u64		inbytes;	/* incoming bytes */
	__u64		outbytes;	/* outgoing bytes */
पूर्ण;
/* Stats per cpu */
काष्ठा ip_vs_cpu_stats अणु
	काष्ठा ip_vs_counters   cnt;
	काष्ठा u64_stats_sync   syncp;
पूर्ण;

/* IPVS statistics objects */
काष्ठा ip_vs_estimator अणु
	काष्ठा list_head	list;

	u64			last_inbytes;
	u64			last_outbytes;
	u64			last_conns;
	u64			last_inpkts;
	u64			last_outpkts;

	u64			cps;
	u64			inpps;
	u64			outpps;
	u64			inbps;
	u64			outbps;
पूर्ण;

/*
 * IPVS statistics object, 64-bit kernel version of काष्ठा ip_vs_stats_user
 */
काष्ठा ip_vs_kstats अणु
	u64			conns;		/* connections scheduled */
	u64			inpkts;		/* incoming packets */
	u64			outpkts;	/* outgoing packets */
	u64			inbytes;	/* incoming bytes */
	u64			outbytes;	/* outgoing bytes */

	u64			cps;		/* current connection rate */
	u64			inpps;		/* current in packet rate */
	u64			outpps;		/* current out packet rate */
	u64			inbps;		/* current in byte rate */
	u64			outbps;		/* current out byte rate */
पूर्ण;

काष्ठा ip_vs_stats अणु
	काष्ठा ip_vs_kstats	kstats;		/* kernel statistics */
	काष्ठा ip_vs_estimator	est;		/* estimator */
	काष्ठा ip_vs_cpu_stats __percpu	*cpustats;	/* per cpu counters */
	spinlock_t		lock;		/* spin lock */
	काष्ठा ip_vs_kstats	kstats0;	/* reset values */
पूर्ण;

काष्ठा dst_entry;
काष्ठा iphdr;
काष्ठा ip_vs_conn;
काष्ठा ip_vs_app;
काष्ठा sk_buff;
काष्ठा ip_vs_proto_data;

काष्ठा ip_vs_protocol अणु
	काष्ठा ip_vs_protocol	*next;
	अक्षर			*name;
	u16			protocol;
	u16			num_states;
	पूर्णांक			करोnt_defrag;

	व्योम (*init)(काष्ठा ip_vs_protocol *pp);

	व्योम (*निकास)(काष्ठा ip_vs_protocol *pp);

	पूर्णांक (*init_netns)(काष्ठा netns_ipvs *ipvs, काष्ठा ip_vs_proto_data *pd);

	व्योम (*निकास_netns)(काष्ठा netns_ipvs *ipvs, काष्ठा ip_vs_proto_data *pd);

	पूर्णांक (*conn_schedule)(काष्ठा netns_ipvs *ipvs,
			     पूर्णांक af, काष्ठा sk_buff *skb,
			     काष्ठा ip_vs_proto_data *pd,
			     पूर्णांक *verdict, काष्ठा ip_vs_conn **cpp,
			     काष्ठा ip_vs_iphdr *iph);

	काष्ठा ip_vs_conn *
	(*conn_in_get)(काष्ठा netns_ipvs *ipvs,
		       पूर्णांक af,
		       स्थिर काष्ठा sk_buff *skb,
		       स्थिर काष्ठा ip_vs_iphdr *iph);

	काष्ठा ip_vs_conn *
	(*conn_out_get)(काष्ठा netns_ipvs *ipvs,
			पूर्णांक af,
			स्थिर काष्ठा sk_buff *skb,
			स्थिर काष्ठा ip_vs_iphdr *iph);

	पूर्णांक (*snat_handler)(काष्ठा sk_buff *skb, काष्ठा ip_vs_protocol *pp,
			    काष्ठा ip_vs_conn *cp, काष्ठा ip_vs_iphdr *iph);

	पूर्णांक (*dnat_handler)(काष्ठा sk_buff *skb, काष्ठा ip_vs_protocol *pp,
			    काष्ठा ip_vs_conn *cp, काष्ठा ip_vs_iphdr *iph);

	स्थिर अक्षर *(*state_name)(पूर्णांक state);

	व्योम (*state_transition)(काष्ठा ip_vs_conn *cp, पूर्णांक direction,
				 स्थिर काष्ठा sk_buff *skb,
				 काष्ठा ip_vs_proto_data *pd);

	पूर्णांक (*रेजिस्टर_app)(काष्ठा netns_ipvs *ipvs, काष्ठा ip_vs_app *inc);

	व्योम (*unरेजिस्टर_app)(काष्ठा netns_ipvs *ipvs, काष्ठा ip_vs_app *inc);

	पूर्णांक (*app_conn_bind)(काष्ठा ip_vs_conn *cp);

	व्योम (*debug_packet)(पूर्णांक af, काष्ठा ip_vs_protocol *pp,
			     स्थिर काष्ठा sk_buff *skb,
			     पूर्णांक offset,
			     स्थिर अक्षर *msg);

	व्योम (*समयout_change)(काष्ठा ip_vs_proto_data *pd, पूर्णांक flags);
पूर्ण;

/* protocol data per netns */
काष्ठा ip_vs_proto_data अणु
	काष्ठा ip_vs_proto_data	*next;
	काष्ठा ip_vs_protocol	*pp;
	पूर्णांक			*समयout_table;	/* protocol समयout table */
	atomic_t		appcnt;		/* counter of proto app incs. */
	काष्ठा tcp_states_t	*tcp_state_table;
पूर्ण;

काष्ठा ip_vs_protocol   *ip_vs_proto_get(अचिन्हित लघु proto);
काष्ठा ip_vs_proto_data *ip_vs_proto_data_get(काष्ठा netns_ipvs *ipvs,
					      अचिन्हित लघु proto);

काष्ठा ip_vs_conn_param अणु
	काष्ठा netns_ipvs		*ipvs;
	स्थिर जोड़ nf_inet_addr	*caddr;
	स्थिर जोड़ nf_inet_addr	*vaddr;
	__be16				cport;
	__be16				vport;
	__u16				protocol;
	u16				af;

	स्थिर काष्ठा ip_vs_pe		*pe;
	अक्षर				*pe_data;
	__u8				pe_data_len;
पूर्ण;

/* IP_VS काष्ठाure allocated क्रम each dynamically scheduled connection */
काष्ठा ip_vs_conn अणु
	काष्ठा hlist_node	c_list;         /* hashed list heads */
	/* Protocol, addresses and port numbers */
	__be16                  cport;
	__be16                  dport;
	__be16                  vport;
	u16			af;		/* address family */
	जोड़ nf_inet_addr      caddr;          /* client address */
	जोड़ nf_inet_addr      vaddr;          /* भव address */
	जोड़ nf_inet_addr      daddr;          /* destination address */
	अस्थिर __u32          flags;          /* status flags */
	__u16                   protocol;       /* Which protocol (TCP/UDP) */
	__u16			daf;		/* Address family of the dest */
	काष्ठा netns_ipvs	*ipvs;

	/* counter and समयr */
	refcount_t		refcnt;		/* reference count */
	काष्ठा समयr_list	समयr;		/* Expiration समयr */
	अस्थिर अचिन्हित दीर्घ	समयout;	/* समयout */

	/* Flags and state transition */
	spinlock_t              lock;           /* lock क्रम state transition */
	अस्थिर __u16          state;          /* state info */
	अस्थिर __u16          old_state;      /* old state, to be used क्रम
						 * state transition triggerd
						 * synchronization
						 */
	__u32			fwmark;		/* Fire wall mark from skb */
	अचिन्हित दीर्घ		sync_endसमय;	/* jअगरfies + sent_retries */

	/* Control members */
	काष्ठा ip_vs_conn       *control;       /* Master control connection */
	atomic_t                n_control;      /* Number of controlled ones */
	काष्ठा ip_vs_dest       *dest;          /* real server */
	atomic_t                in_pkts;        /* incoming packet counter */

	/* Packet transmitter क्रम dअगरferent क्रमwarding methods.  If it
	 * mangles the packet, it must वापस NF_DROP or better NF_STOLEN,
	 * otherwise this must be changed to a sk_buff **.
	 * NF_ACCEPT can be वापसed when destination is local.
	 */
	पूर्णांक (*packet_xmit)(काष्ठा sk_buff *skb, काष्ठा ip_vs_conn *cp,
			   काष्ठा ip_vs_protocol *pp, काष्ठा ip_vs_iphdr *iph);

	/* Note: we can group the following members पूर्णांकo a काष्ठाure,
	 * in order to save more space, and the following members are
	 * only used in VS/NAT anyway
	 */
	काष्ठा ip_vs_app        *app;           /* bound ip_vs_app object */
	व्योम                    *app_data;      /* Application निजी data */
	काष्ठा ip_vs_seq        in_seq;         /* incoming seq. काष्ठा */
	काष्ठा ip_vs_seq        out_seq;        /* outgoing seq. काष्ठा */

	स्थिर काष्ठा ip_vs_pe	*pe;
	अक्षर			*pe_data;
	__u8			pe_data_len;

	काष्ठा rcu_head		rcu_head;
पूर्ण;

/* Extended पूर्णांकernal versions of काष्ठा ip_vs_service_user and ip_vs_dest_user
 * क्रम IPv6 support.
 *
 * We need these to conveniently pass around service and destination
 * options, but unक्रमtunately, we also need to keep the old definitions to
 * मुख्यtain userspace backwards compatibility क्रम the setsockopt पूर्णांकerface.
 */
काष्ठा ip_vs_service_user_kern अणु
	/* भव service addresses */
	u16			af;
	u16			protocol;
	जोड़ nf_inet_addr	addr;		/* भव ip address */
	__be16			port;
	u32			fwmark;		/* firwall mark of service */

	/* भव service options */
	अक्षर			*sched_name;
	अक्षर			*pe_name;
	अचिन्हित पूर्णांक		flags;		/* भव service flags */
	अचिन्हित पूर्णांक		समयout;	/* persistent समयout in sec */
	__be32			neपंचांगask;	/* persistent neपंचांगask or plen */
पूर्ण;


काष्ठा ip_vs_dest_user_kern अणु
	/* destination server address */
	जोड़ nf_inet_addr	addr;
	__be16			port;

	/* real server options */
	अचिन्हित पूर्णांक		conn_flags;	/* connection flags */
	पूर्णांक			weight;		/* destination weight */

	/* thresholds क्रम active connections */
	u32			u_threshold;	/* upper threshold */
	u32			l_threshold;	/* lower threshold */

	/* Address family of addr */
	u16			af;

	u16			tun_type;	/* tunnel type */
	__be16			tun_port;	/* tunnel port */
	u16			tun_flags;	/* tunnel flags */
पूर्ण;


/*
 * The inक्रमmation about the भव service offered to the net and the
 * क्रमwarding entries.
 */
काष्ठा ip_vs_service अणु
	काष्ठा hlist_node	s_list;   /* क्रम normal service table */
	काष्ठा hlist_node	f_list;   /* क्रम fwmark-based service table */
	atomic_t		refcnt;   /* reference counter */

	u16			af;       /* address family */
	__u16			protocol; /* which protocol (TCP/UDP) */
	जोड़ nf_inet_addr	addr;	  /* IP address क्रम भव service */
	__be16			port;	  /* port number क्रम the service */
	__u32                   fwmark;   /* firewall mark of the service */
	अचिन्हित पूर्णांक		flags;	  /* service status flags */
	अचिन्हित पूर्णांक		समयout;  /* persistent समयout in ticks */
	__be32			neपंचांगask;  /* grouping granularity, mask/plen */
	काष्ठा netns_ipvs	*ipvs;

	काष्ठा list_head	destinations;  /* real server d-linked list */
	__u32			num_dests;     /* number of servers */
	काष्ठा ip_vs_stats      stats;         /* statistics क्रम the service */

	/* क्रम scheduling */
	काष्ठा ip_vs_scheduler __rcu *scheduler; /* bound scheduler object */
	spinlock_t		sched_lock;    /* lock sched_data */
	व्योम			*sched_data;   /* scheduler application data */

	/* alternate persistence engine */
	काष्ठा ip_vs_pe __rcu	*pe;
	पूर्णांक			conntrack_afmask;

	काष्ठा rcu_head		rcu_head;
पूर्ण;

/* Inक्रमmation क्रम cached dst */
काष्ठा ip_vs_dest_dst अणु
	काष्ठा dst_entry	*dst_cache;	/* destination cache entry */
	u32			dst_cookie;
	जोड़ nf_inet_addr	dst_saddr;
	काष्ठा rcu_head		rcu_head;
पूर्ण;

/* The real server destination क्रमwarding entry with ip address, port number,
 * and so on.
 */
काष्ठा ip_vs_dest अणु
	काष्ठा list_head	n_list;   /* क्रम the dests in the service */
	काष्ठा hlist_node	d_list;   /* क्रम table with all the dests */

	u16			af;		/* address family */
	__be16			port;		/* port number of the server */
	जोड़ nf_inet_addr	addr;		/* IP address of the server */
	अस्थिर अचिन्हित पूर्णांक	flags;		/* dest status flags */
	atomic_t		conn_flags;	/* flags to copy to conn */
	atomic_t		weight;		/* server weight */
	atomic_t		last_weight;	/* server latest weight */
	__u16			tun_type;	/* tunnel type */
	__be16			tun_port;	/* tunnel port */
	__u16			tun_flags;	/* tunnel flags */

	refcount_t		refcnt;		/* reference counter */
	काष्ठा ip_vs_stats      stats;          /* statistics */
	अचिन्हित दीर्घ		idle_start;	/* start समय, jअगरfies */

	/* connection counters and thresholds */
	atomic_t		activeconns;	/* active connections */
	atomic_t		inactconns;	/* inactive connections */
	atomic_t		persistconns;	/* persistent connections */
	__u32			u_threshold;	/* upper threshold */
	__u32			l_threshold;	/* lower threshold */

	/* क्रम destination cache */
	spinlock_t		dst_lock;	/* lock of dst_cache */
	काष्ठा ip_vs_dest_dst __rcu *dest_dst;	/* cached dst info */

	/* क्रम भव service */
	काष्ठा ip_vs_service __rcu *svc;	/* service it beदीर्घs to */
	__u16			protocol;	/* which protocol (TCP/UDP) */
	__be16			vport;		/* भव port number */
	जोड़ nf_inet_addr	vaddr;		/* भव IP address */
	__u32			vfwmark;	/* firewall mark of service */

	काष्ठा list_head	t_list;		/* in dest_trash */
	अचिन्हित पूर्णांक		in_rs_table:1;	/* we are in rs_table */
पूर्ण;

/* The scheduler object */
काष्ठा ip_vs_scheduler अणु
	काष्ठा list_head	n_list;		/* d-linked list head */
	अक्षर			*name;		/* scheduler name */
	atomic_t		refcnt;		/* reference counter */
	काष्ठा module		*module;	/* THIS_MODULE/शून्य */

	/* scheduler initializing service */
	पूर्णांक (*init_service)(काष्ठा ip_vs_service *svc);
	/* scheduling service finish */
	व्योम (*करोne_service)(काष्ठा ip_vs_service *svc);
	/* dest is linked */
	पूर्णांक (*add_dest)(काष्ठा ip_vs_service *svc, काष्ठा ip_vs_dest *dest);
	/* dest is unlinked */
	पूर्णांक (*del_dest)(काष्ठा ip_vs_service *svc, काष्ठा ip_vs_dest *dest);
	/* dest is updated */
	पूर्णांक (*upd_dest)(काष्ठा ip_vs_service *svc, काष्ठा ip_vs_dest *dest);

	/* selecting a server from the given service */
	काष्ठा ip_vs_dest* (*schedule)(काष्ठा ip_vs_service *svc,
				       स्थिर काष्ठा sk_buff *skb,
				       काष्ठा ip_vs_iphdr *iph);
पूर्ण;

/* The persistence engine object */
काष्ठा ip_vs_pe अणु
	काष्ठा list_head	n_list;		/* d-linked list head */
	अक्षर			*name;		/* scheduler name */
	atomic_t		refcnt;		/* reference counter */
	काष्ठा module		*module;	/* THIS_MODULE/शून्य */

	/* get the connection ढाँचा, अगर any */
	पूर्णांक (*fill_param)(काष्ठा ip_vs_conn_param *p, काष्ठा sk_buff *skb);
	bool (*ct_match)(स्थिर काष्ठा ip_vs_conn_param *p,
			 काष्ठा ip_vs_conn *ct);
	u32 (*hashkey_raw)(स्थिर काष्ठा ip_vs_conn_param *p, u32 initval,
			   bool inverse);
	पूर्णांक (*show_pe_data)(स्थिर काष्ठा ip_vs_conn *cp, अक्षर *buf);
	/* create connections क्रम real-server outgoing packets */
	काष्ठा ip_vs_conn* (*conn_out)(काष्ठा ip_vs_service *svc,
				       काष्ठा ip_vs_dest *dest,
				       काष्ठा sk_buff *skb,
				       स्थिर काष्ठा ip_vs_iphdr *iph,
				       __be16 dport, __be16 cport);
पूर्ण;

/* The application module object (a.k.a. app incarnation) */
काष्ठा ip_vs_app अणु
	काष्ठा list_head	a_list;		/* member in app list */
	पूर्णांक			type;		/* IP_VS_APP_TYPE_xxx */
	अक्षर			*name;		/* application module name */
	__u16			protocol;
	काष्ठा module		*module;	/* THIS_MODULE/शून्य */
	काष्ठा list_head	incs_list;	/* list of incarnations */

	/* members क्रम application incarnations */
	काष्ठा list_head	p_list;		/* member in proto app list */
	काष्ठा ip_vs_app	*app;		/* its real application */
	__be16			port;		/* port number in net order */
	atomic_t		usecnt;		/* usage counter */
	काष्ठा rcu_head		rcu_head;

	/* output hook: Process packet in inout direction, dअगरf set क्रम TCP.
	 * Return: 0=Error, 1=Payload Not Mangled/Mangled but checksum is ok,
	 *	   2=Mangled but checksum was not updated
	 */
	पूर्णांक (*pkt_out)(काष्ठा ip_vs_app *, काष्ठा ip_vs_conn *,
		       काष्ठा sk_buff *, पूर्णांक *dअगरf, काष्ठा ip_vs_iphdr *ipvsh);

	/* input hook: Process packet in outin direction, dअगरf set क्रम TCP.
	 * Return: 0=Error, 1=Payload Not Mangled/Mangled but checksum is ok,
	 *	   2=Mangled but checksum was not updated
	 */
	पूर्णांक (*pkt_in)(काष्ठा ip_vs_app *, काष्ठा ip_vs_conn *,
		      काष्ठा sk_buff *, पूर्णांक *dअगरf, काष्ठा ip_vs_iphdr *ipvsh);

	/* ip_vs_app initializer */
	पूर्णांक (*init_conn)(काष्ठा ip_vs_app *, काष्ठा ip_vs_conn *);

	/* ip_vs_app finish */
	पूर्णांक (*करोne_conn)(काष्ठा ip_vs_app *, काष्ठा ip_vs_conn *);


	/* not used now */
	पूर्णांक (*bind_conn)(काष्ठा ip_vs_app *, काष्ठा ip_vs_conn *,
			 काष्ठा ip_vs_protocol *);

	व्योम (*unbind_conn)(काष्ठा ip_vs_app *, काष्ठा ip_vs_conn *);

	पूर्णांक *			समयout_table;
	पूर्णांक *			समयouts;
	पूर्णांक			समयouts_size;

	पूर्णांक (*conn_schedule)(काष्ठा sk_buff *skb, काष्ठा ip_vs_app *app,
			     पूर्णांक *verdict, काष्ठा ip_vs_conn **cpp);

	काष्ठा ip_vs_conn *
	(*conn_in_get)(स्थिर काष्ठा sk_buff *skb, काष्ठा ip_vs_app *app,
		       स्थिर काष्ठा iphdr *iph, पूर्णांक inverse);

	काष्ठा ip_vs_conn *
	(*conn_out_get)(स्थिर काष्ठा sk_buff *skb, काष्ठा ip_vs_app *app,
			स्थिर काष्ठा iphdr *iph, पूर्णांक inverse);

	पूर्णांक (*state_transition)(काष्ठा ip_vs_conn *cp, पूर्णांक direction,
				स्थिर काष्ठा sk_buff *skb,
				काष्ठा ip_vs_app *app);

	व्योम (*समयout_change)(काष्ठा ip_vs_app *app, पूर्णांक flags);
पूर्ण;

काष्ठा ipvs_master_sync_state अणु
	काष्ठा list_head	sync_queue;
	काष्ठा ip_vs_sync_buff	*sync_buff;
	अचिन्हित दीर्घ		sync_queue_len;
	अचिन्हित पूर्णांक		sync_queue_delay;
	काष्ठा delayed_work	master_wakeup_work;
	काष्ठा netns_ipvs	*ipvs;
पूर्ण;

काष्ठा ip_vs_sync_thपढ़ो_data;

/* How much समय to keep dests in trash */
#घोषणा IP_VS_DEST_TRASH_PERIOD		(120 * HZ)

काष्ठा ipvs_sync_daemon_cfg अणु
	जोड़ nf_inet_addr	mcast_group;
	पूर्णांक			syncid;
	u16			sync_maxlen;
	u16			mcast_port;
	u8			mcast_af;
	u8			mcast_ttl;
	/* multicast पूर्णांकerface name */
	अक्षर			mcast_अगरn[IP_VS_IFNAME_MAXLEN];
पूर्ण;

/* IPVS in network namespace */
काष्ठा netns_ipvs अणु
	पूर्णांक			gen;		/* Generation */
	पूर्णांक			enable;		/* enable like nf_hooks करो */
	/* Hash table: क्रम real service lookups */
	#घोषणा IP_VS_RTAB_BITS 4
	#घोषणा IP_VS_RTAB_SIZE (1 << IP_VS_RTAB_BITS)
	#घोषणा IP_VS_RTAB_MASK (IP_VS_RTAB_SIZE - 1)

	काष्ठा hlist_head	rs_table[IP_VS_RTAB_SIZE];
	/* ip_vs_app */
	काष्ठा list_head	app_list;
	/* ip_vs_proto */
	#घोषणा IP_VS_PROTO_TAB_SIZE	32	/* must be घातer of 2 */
	काष्ठा ip_vs_proto_data *proto_data_table[IP_VS_PROTO_TAB_SIZE];
	/* ip_vs_proto_tcp */
#अगर_घोषित CONFIG_IP_VS_PROTO_TCP
	#घोषणा	TCP_APP_TAB_BITS	4
	#घोषणा	TCP_APP_TAB_SIZE	(1 << TCP_APP_TAB_BITS)
	#घोषणा	TCP_APP_TAB_MASK	(TCP_APP_TAB_SIZE - 1)
	काष्ठा list_head	tcp_apps[TCP_APP_TAB_SIZE];
#पूर्ण_अगर
	/* ip_vs_proto_udp */
#अगर_घोषित CONFIG_IP_VS_PROTO_UDP
	#घोषणा	UDP_APP_TAB_BITS	4
	#घोषणा	UDP_APP_TAB_SIZE	(1 << UDP_APP_TAB_BITS)
	#घोषणा	UDP_APP_TAB_MASK	(UDP_APP_TAB_SIZE - 1)
	काष्ठा list_head	udp_apps[UDP_APP_TAB_SIZE];
#पूर्ण_अगर
	/* ip_vs_proto_sctp */
#अगर_घोषित CONFIG_IP_VS_PROTO_SCTP
	#घोषणा SCTP_APP_TAB_BITS	4
	#घोषणा SCTP_APP_TAB_SIZE	(1 << SCTP_APP_TAB_BITS)
	#घोषणा SCTP_APP_TAB_MASK	(SCTP_APP_TAB_SIZE - 1)
	/* Hash table क्रम SCTP application incarnations	 */
	काष्ठा list_head	sctp_apps[SCTP_APP_TAB_SIZE];
#पूर्ण_अगर
	/* ip_vs_conn */
	atomic_t		conn_count;      /* connection counter */

	/* ip_vs_ctl */
	काष्ठा ip_vs_stats		tot_stats;  /* Statistics & est. */

	पूर्णांक			num_services;    /* no of भव services */
	पूर्णांक			num_services6;   /* IPv6 भव services */

	/* Trash क्रम destinations */
	काष्ठा list_head	dest_trash;
	spinlock_t		dest_trash_lock;
	काष्ठा समयr_list	dest_trash_समयr; /* expiration समयr */
	/* Service counters */
	atomic_t		ftpsvc_counter;
	atomic_t		nullsvc_counter;
	atomic_t		conn_out_counter;

#अगर_घोषित CONFIG_SYSCTL
	/* delayed work क्रम expiring no dest connections */
	काष्ठा delayed_work	expire_nodest_conn_work;
	/* 1/rate drop and drop-entry variables */
	काष्ठा delayed_work	defense_work;   /* Work handler */
	पूर्णांक			drop_rate;
	पूर्णांक			drop_counter;
	पूर्णांक			old_secure_tcp;
	atomic_t		drखोलोtry;
	/* locks in ctl.c */
	spinlock_t		drखोलोtry_lock;  /* drop entry handling */
	spinlock_t		droppacket_lock; /* drop packet handling */
	spinlock_t		securetcp_lock;  /* state and समयout tables */

	/* sys-ctl काष्ठा */
	काष्ठा ctl_table_header	*sysctl_hdr;
	काष्ठा ctl_table	*sysctl_tbl;
#पूर्ण_अगर

	/* sysctl variables */
	पूर्णांक			sysctl_amemthresh;
	पूर्णांक			sysctl_am_droprate;
	पूर्णांक			sysctl_drop_entry;
	पूर्णांक			sysctl_drop_packet;
	पूर्णांक			sysctl_secure_tcp;
#अगर_घोषित CONFIG_IP_VS_NFCT
	पूर्णांक			sysctl_conntrack;
#पूर्ण_अगर
	पूर्णांक			sysctl_snat_reroute;
	पूर्णांक			sysctl_sync_ver;
	पूर्णांक			sysctl_sync_ports;
	पूर्णांक			sysctl_sync_persist_mode;
	अचिन्हित दीर्घ		sysctl_sync_qlen_max;
	पूर्णांक			sysctl_sync_sock_size;
	पूर्णांक			sysctl_cache_bypass;
	पूर्णांक			sysctl_expire_nodest_conn;
	पूर्णांक			sysctl_sloppy_tcp;
	पूर्णांक			sysctl_sloppy_sctp;
	पूर्णांक			sysctl_expire_quiescent_ढाँचा;
	पूर्णांक			sysctl_sync_threshold[2];
	अचिन्हित पूर्णांक		sysctl_sync_refresh_period;
	पूर्णांक			sysctl_sync_retries;
	पूर्णांक			sysctl_nat_icmp_send;
	पूर्णांक			sysctl_pmtu_disc;
	पूर्णांक			sysctl_backup_only;
	पूर्णांक			sysctl_conn_reuse_mode;
	पूर्णांक			sysctl_schedule_icmp;
	पूर्णांक			sysctl_ignore_tunneled;

	/* ip_vs_lblc */
	पूर्णांक			sysctl_lblc_expiration;
	काष्ठा ctl_table_header	*lblc_ctl_header;
	काष्ठा ctl_table	*lblc_ctl_table;
	/* ip_vs_lblcr */
	पूर्णांक			sysctl_lblcr_expiration;
	काष्ठा ctl_table_header	*lblcr_ctl_header;
	काष्ठा ctl_table	*lblcr_ctl_table;
	/* ip_vs_est */
	काष्ठा list_head	est_list;	/* estimator list */
	spinlock_t		est_lock;
	काष्ठा समयr_list	est_समयr;	/* Estimation समयr */
	/* ip_vs_sync */
	spinlock_t		sync_lock;
	काष्ठा ipvs_master_sync_state *ms;
	spinlock_t		sync_buff_lock;
	काष्ठा ip_vs_sync_thपढ़ो_data *master_tinfo;
	काष्ठा ip_vs_sync_thपढ़ो_data *backup_tinfo;
	पूर्णांक			thपढ़ोs_mask;
	अस्थिर पूर्णांक		sync_state;
	काष्ठा mutex		sync_mutex;
	काष्ठा ipvs_sync_daemon_cfg	mcfg;	/* Master Configuration */
	काष्ठा ipvs_sync_daemon_cfg	bcfg;	/* Backup Configuration */
	/* net name space ptr */
	काष्ठा net		*net;            /* Needed by समयr routines */
	/* Number of heterogeneous destinations, needed becaus heterogeneous
	 * are not supported when synchronization is enabled.
	 */
	अचिन्हित पूर्णांक		mixed_address_family_dests;
	अचिन्हित पूर्णांक		hooks_afmask;	/* &1=AF_INET, &2=AF_INET6 */
पूर्ण;

#घोषणा DEFAULT_SYNC_THRESHOLD	3
#घोषणा DEFAULT_SYNC_PERIOD	50
#घोषणा DEFAULT_SYNC_VER	1
#घोषणा DEFAULT_SLOPPY_TCP	0
#घोषणा DEFAULT_SLOPPY_SCTP	0
#घोषणा DEFAULT_SYNC_REFRESH_PERIOD	(0U * HZ)
#घोषणा DEFAULT_SYNC_RETRIES		0
#घोषणा IPVS_SYNC_WAKEUP_RATE	8
#घोषणा IPVS_SYNC_QLEN_MAX	(IPVS_SYNC_WAKEUP_RATE * 4)
#घोषणा IPVS_SYNC_SEND_DELAY	(HZ / 50)
#घोषणा IPVS_SYNC_CHECK_PERIOD	HZ
#घोषणा IPVS_SYNC_FLUSH_TIME	(HZ * 2)
#घोषणा IPVS_SYNC_PORTS_MAX	(1 << 6)

#अगर_घोषित CONFIG_SYSCTL

अटल अंतरभूत पूर्णांक sysctl_sync_threshold(काष्ठा netns_ipvs *ipvs)
अणु
	वापस ipvs->sysctl_sync_threshold[0];
पूर्ण

अटल अंतरभूत पूर्णांक sysctl_sync_period(काष्ठा netns_ipvs *ipvs)
अणु
	वापस READ_ONCE(ipvs->sysctl_sync_threshold[1]);
पूर्ण

अटल अंतरभूत अचिन्हित पूर्णांक sysctl_sync_refresh_period(काष्ठा netns_ipvs *ipvs)
अणु
	वापस READ_ONCE(ipvs->sysctl_sync_refresh_period);
पूर्ण

अटल अंतरभूत पूर्णांक sysctl_sync_retries(काष्ठा netns_ipvs *ipvs)
अणु
	वापस ipvs->sysctl_sync_retries;
पूर्ण

अटल अंतरभूत पूर्णांक sysctl_sync_ver(काष्ठा netns_ipvs *ipvs)
अणु
	वापस ipvs->sysctl_sync_ver;
पूर्ण

अटल अंतरभूत पूर्णांक sysctl_sloppy_tcp(काष्ठा netns_ipvs *ipvs)
अणु
	वापस ipvs->sysctl_sloppy_tcp;
पूर्ण

अटल अंतरभूत पूर्णांक sysctl_sloppy_sctp(काष्ठा netns_ipvs *ipvs)
अणु
	वापस ipvs->sysctl_sloppy_sctp;
पूर्ण

अटल अंतरभूत पूर्णांक sysctl_sync_ports(काष्ठा netns_ipvs *ipvs)
अणु
	वापस READ_ONCE(ipvs->sysctl_sync_ports);
पूर्ण

अटल अंतरभूत पूर्णांक sysctl_sync_persist_mode(काष्ठा netns_ipvs *ipvs)
अणु
	वापस ipvs->sysctl_sync_persist_mode;
पूर्ण

अटल अंतरभूत अचिन्हित दीर्घ sysctl_sync_qlen_max(काष्ठा netns_ipvs *ipvs)
अणु
	वापस ipvs->sysctl_sync_qlen_max;
पूर्ण

अटल अंतरभूत पूर्णांक sysctl_sync_sock_size(काष्ठा netns_ipvs *ipvs)
अणु
	वापस ipvs->sysctl_sync_sock_size;
पूर्ण

अटल अंतरभूत पूर्णांक sysctl_pmtu_disc(काष्ठा netns_ipvs *ipvs)
अणु
	वापस ipvs->sysctl_pmtu_disc;
पूर्ण

अटल अंतरभूत पूर्णांक sysctl_backup_only(काष्ठा netns_ipvs *ipvs)
अणु
	वापस ipvs->sync_state & IP_VS_STATE_BACKUP &&
	       ipvs->sysctl_backup_only;
पूर्ण

अटल अंतरभूत पूर्णांक sysctl_conn_reuse_mode(काष्ठा netns_ipvs *ipvs)
अणु
	वापस ipvs->sysctl_conn_reuse_mode;
पूर्ण

अटल अंतरभूत पूर्णांक sysctl_expire_nodest_conn(काष्ठा netns_ipvs *ipvs)
अणु
	वापस ipvs->sysctl_expire_nodest_conn;
पूर्ण

अटल अंतरभूत पूर्णांक sysctl_schedule_icmp(काष्ठा netns_ipvs *ipvs)
अणु
	वापस ipvs->sysctl_schedule_icmp;
पूर्ण

अटल अंतरभूत पूर्णांक sysctl_ignore_tunneled(काष्ठा netns_ipvs *ipvs)
अणु
	वापस ipvs->sysctl_ignore_tunneled;
पूर्ण

अटल अंतरभूत पूर्णांक sysctl_cache_bypass(काष्ठा netns_ipvs *ipvs)
अणु
	वापस ipvs->sysctl_cache_bypass;
पूर्ण

#अन्यथा

अटल अंतरभूत पूर्णांक sysctl_sync_threshold(काष्ठा netns_ipvs *ipvs)
अणु
	वापस DEFAULT_SYNC_THRESHOLD;
पूर्ण

अटल अंतरभूत पूर्णांक sysctl_sync_period(काष्ठा netns_ipvs *ipvs)
अणु
	वापस DEFAULT_SYNC_PERIOD;
पूर्ण

अटल अंतरभूत अचिन्हित पूर्णांक sysctl_sync_refresh_period(काष्ठा netns_ipvs *ipvs)
अणु
	वापस DEFAULT_SYNC_REFRESH_PERIOD;
पूर्ण

अटल अंतरभूत पूर्णांक sysctl_sync_retries(काष्ठा netns_ipvs *ipvs)
अणु
	वापस DEFAULT_SYNC_RETRIES & 3;
पूर्ण

अटल अंतरभूत पूर्णांक sysctl_sync_ver(काष्ठा netns_ipvs *ipvs)
अणु
	वापस DEFAULT_SYNC_VER;
पूर्ण

अटल अंतरभूत पूर्णांक sysctl_sloppy_tcp(काष्ठा netns_ipvs *ipvs)
अणु
	वापस DEFAULT_SLOPPY_TCP;
पूर्ण

अटल अंतरभूत पूर्णांक sysctl_sloppy_sctp(काष्ठा netns_ipvs *ipvs)
अणु
	वापस DEFAULT_SLOPPY_SCTP;
पूर्ण

अटल अंतरभूत पूर्णांक sysctl_sync_ports(काष्ठा netns_ipvs *ipvs)
अणु
	वापस 1;
पूर्ण

अटल अंतरभूत पूर्णांक sysctl_sync_persist_mode(काष्ठा netns_ipvs *ipvs)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत अचिन्हित दीर्घ sysctl_sync_qlen_max(काष्ठा netns_ipvs *ipvs)
अणु
	वापस IPVS_SYNC_QLEN_MAX;
पूर्ण

अटल अंतरभूत पूर्णांक sysctl_sync_sock_size(काष्ठा netns_ipvs *ipvs)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक sysctl_pmtu_disc(काष्ठा netns_ipvs *ipvs)
अणु
	वापस 1;
पूर्ण

अटल अंतरभूत पूर्णांक sysctl_backup_only(काष्ठा netns_ipvs *ipvs)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक sysctl_conn_reuse_mode(काष्ठा netns_ipvs *ipvs)
अणु
	वापस 1;
पूर्ण

अटल अंतरभूत पूर्णांक sysctl_expire_nodest_conn(काष्ठा netns_ipvs *ipvs)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक sysctl_schedule_icmp(काष्ठा netns_ipvs *ipvs)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक sysctl_ignore_tunneled(काष्ठा netns_ipvs *ipvs)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक sysctl_cache_bypass(काष्ठा netns_ipvs *ipvs)
अणु
	वापस 0;
पूर्ण

#पूर्ण_अगर

/* IPVS core functions
 * (from ip_vs_core.c)
 */
स्थिर अक्षर *ip_vs_proto_name(अचिन्हित पूर्णांक proto);
व्योम ip_vs_init_hash_table(काष्ठा list_head *table, पूर्णांक rows);
काष्ठा ip_vs_conn *ip_vs_new_conn_out(काष्ठा ip_vs_service *svc,
				      काष्ठा ip_vs_dest *dest,
				      काष्ठा sk_buff *skb,
				      स्थिर काष्ठा ip_vs_iphdr *iph,
				      __be16 dport,
				      __be16 cport);
#घोषणा IP_VS_INIT_HASH_TABLE(t) ip_vs_init_hash_table((t), ARRAY_SIZE((t)))

#घोषणा IP_VS_APP_TYPE_FTP	1

/* ip_vs_conn handling functions
 * (from ip_vs_conn.c)
 */
क्रमागत अणु
	IP_VS_सूची_INPUT = 0,
	IP_VS_सूची_OUTPUT,
	IP_VS_सूची_INPUT_ONLY,
	IP_VS_सूची_LAST,
पूर्ण;

अटल अंतरभूत व्योम ip_vs_conn_fill_param(काष्ठा netns_ipvs *ipvs, पूर्णांक af, पूर्णांक protocol,
					 स्थिर जोड़ nf_inet_addr *caddr,
					 __be16 cport,
					 स्थिर जोड़ nf_inet_addr *vaddr,
					 __be16 vport,
					 काष्ठा ip_vs_conn_param *p)
अणु
	p->ipvs = ipvs;
	p->af = af;
	p->protocol = protocol;
	p->caddr = caddr;
	p->cport = cport;
	p->vaddr = vaddr;
	p->vport = vport;
	p->pe = शून्य;
	p->pe_data = शून्य;
पूर्ण

काष्ठा ip_vs_conn *ip_vs_conn_in_get(स्थिर काष्ठा ip_vs_conn_param *p);
काष्ठा ip_vs_conn *ip_vs_ct_in_get(स्थिर काष्ठा ip_vs_conn_param *p);

काष्ठा ip_vs_conn * ip_vs_conn_in_get_proto(काष्ठा netns_ipvs *ipvs, पूर्णांक af,
					    स्थिर काष्ठा sk_buff *skb,
					    स्थिर काष्ठा ip_vs_iphdr *iph);

काष्ठा ip_vs_conn *ip_vs_conn_out_get(स्थिर काष्ठा ip_vs_conn_param *p);

काष्ठा ip_vs_conn * ip_vs_conn_out_get_proto(काष्ठा netns_ipvs *ipvs, पूर्णांक af,
					     स्थिर काष्ठा sk_buff *skb,
					     स्थिर काष्ठा ip_vs_iphdr *iph);

/* Get reference to gain full access to conn.
 * By शेष, RCU पढ़ो-side critical sections have access only to
 * conn fields and its PE data, see ip_vs_conn_rcu_मुक्त() क्रम reference.
 */
अटल अंतरभूत bool __ip_vs_conn_get(काष्ठा ip_vs_conn *cp)
अणु
	वापस refcount_inc_not_zero(&cp->refcnt);
पूर्ण

/* put back the conn without restarting its समयr */
अटल अंतरभूत व्योम __ip_vs_conn_put(काष्ठा ip_vs_conn *cp)
अणु
	smp_mb__beक्रमe_atomic();
	refcount_dec(&cp->refcnt);
पूर्ण
व्योम ip_vs_conn_put(काष्ठा ip_vs_conn *cp);
व्योम ip_vs_conn_fill_cport(काष्ठा ip_vs_conn *cp, __be16 cport);

काष्ठा ip_vs_conn *ip_vs_conn_new(स्थिर काष्ठा ip_vs_conn_param *p, पूर्णांक dest_af,
				  स्थिर जोड़ nf_inet_addr *daddr,
				  __be16 dport, अचिन्हित पूर्णांक flags,
				  काष्ठा ip_vs_dest *dest, __u32 fwmark);
व्योम ip_vs_conn_expire_now(काष्ठा ip_vs_conn *cp);

स्थिर अक्षर *ip_vs_state_name(स्थिर काष्ठा ip_vs_conn *cp);

व्योम ip_vs_tcp_conn_listen(काष्ठा ip_vs_conn *cp);
पूर्णांक ip_vs_check_ढाँचा(काष्ठा ip_vs_conn *ct, काष्ठा ip_vs_dest *cdest);
व्योम ip_vs_अक्रमom_drखोलोtry(काष्ठा netns_ipvs *ipvs);
पूर्णांक ip_vs_conn_init(व्योम);
व्योम ip_vs_conn_cleanup(व्योम);

अटल अंतरभूत व्योम ip_vs_control_del(काष्ठा ip_vs_conn *cp)
अणु
	काष्ठा ip_vs_conn *ctl_cp = cp->control;
	अगर (!ctl_cp) अणु
		IP_VS_ERR_BUF("request control DEL for uncontrolled: "
			      "%s:%d to %s:%d\n",
			      IP_VS_DBG_ADDR(cp->af, &cp->caddr),
			      ntohs(cp->cport),
			      IP_VS_DBG_ADDR(cp->af, &cp->vaddr),
			      ntohs(cp->vport));

		वापस;
	पूर्ण

	IP_VS_DBG_BUF(7, "DELeting control for: "
		      "cp.dst=%s:%d ctl_cp.dst=%s:%d\n",
		      IP_VS_DBG_ADDR(cp->af, &cp->caddr),
		      ntohs(cp->cport),
		      IP_VS_DBG_ADDR(cp->af, &ctl_cp->caddr),
		      ntohs(ctl_cp->cport));

	cp->control = शून्य;
	अगर (atomic_पढ़ो(&ctl_cp->n_control) == 0) अणु
		IP_VS_ERR_BUF("BUG control DEL with n=0 : "
			      "%s:%d to %s:%d\n",
			      IP_VS_DBG_ADDR(cp->af, &cp->caddr),
			      ntohs(cp->cport),
			      IP_VS_DBG_ADDR(cp->af, &cp->vaddr),
			      ntohs(cp->vport));

		वापस;
	पूर्ण
	atomic_dec(&ctl_cp->n_control);
पूर्ण

अटल अंतरभूत व्योम
ip_vs_control_add(काष्ठा ip_vs_conn *cp, काष्ठा ip_vs_conn *ctl_cp)
अणु
	अगर (cp->control) अणु
		IP_VS_ERR_BUF("request control ADD for already controlled: "
			      "%s:%d to %s:%d\n",
			      IP_VS_DBG_ADDR(cp->af, &cp->caddr),
			      ntohs(cp->cport),
			      IP_VS_DBG_ADDR(cp->af, &cp->vaddr),
			      ntohs(cp->vport));

		ip_vs_control_del(cp);
	पूर्ण

	IP_VS_DBG_BUF(7, "ADDing control for: "
		      "cp.dst=%s:%d ctl_cp.dst=%s:%d\n",
		      IP_VS_DBG_ADDR(cp->af, &cp->caddr),
		      ntohs(cp->cport),
		      IP_VS_DBG_ADDR(cp->af, &ctl_cp->caddr),
		      ntohs(ctl_cp->cport));

	cp->control = ctl_cp;
	atomic_inc(&ctl_cp->n_control);
पूर्ण

/* Mark our ढाँचा as assured */
अटल अंतरभूत व्योम
ip_vs_control_assure_ct(काष्ठा ip_vs_conn *cp)
अणु
	काष्ठा ip_vs_conn *ct = cp->control;

	अगर (ct && !(ct->state & IP_VS_CTPL_S_ASSURED) &&
	    (ct->flags & IP_VS_CONN_F_TEMPLATE))
		ct->state |= IP_VS_CTPL_S_ASSURED;
पूर्ण

/* IPVS netns init & cleanup functions */
पूर्णांक ip_vs_estimator_net_init(काष्ठा netns_ipvs *ipvs);
पूर्णांक ip_vs_control_net_init(काष्ठा netns_ipvs *ipvs);
पूर्णांक ip_vs_protocol_net_init(काष्ठा netns_ipvs *ipvs);
पूर्णांक ip_vs_app_net_init(काष्ठा netns_ipvs *ipvs);
पूर्णांक ip_vs_conn_net_init(काष्ठा netns_ipvs *ipvs);
पूर्णांक ip_vs_sync_net_init(काष्ठा netns_ipvs *ipvs);
व्योम ip_vs_conn_net_cleanup(काष्ठा netns_ipvs *ipvs);
व्योम ip_vs_app_net_cleanup(काष्ठा netns_ipvs *ipvs);
व्योम ip_vs_protocol_net_cleanup(काष्ठा netns_ipvs *ipvs);
व्योम ip_vs_control_net_cleanup(काष्ठा netns_ipvs *ipvs);
व्योम ip_vs_estimator_net_cleanup(काष्ठा netns_ipvs *ipvs);
व्योम ip_vs_sync_net_cleanup(काष्ठा netns_ipvs *ipvs);
व्योम ip_vs_service_nets_cleanup(काष्ठा list_head *net_list);

/* IPVS application functions
 * (from ip_vs_app.c)
 */
#घोषणा IP_VS_APP_MAX_PORTS  8
काष्ठा ip_vs_app *रेजिस्टर_ip_vs_app(काष्ठा netns_ipvs *ipvs, काष्ठा ip_vs_app *app);
व्योम unरेजिस्टर_ip_vs_app(काष्ठा netns_ipvs *ipvs, काष्ठा ip_vs_app *app);
पूर्णांक ip_vs_bind_app(काष्ठा ip_vs_conn *cp, काष्ठा ip_vs_protocol *pp);
व्योम ip_vs_unbind_app(काष्ठा ip_vs_conn *cp);
पूर्णांक रेजिस्टर_ip_vs_app_inc(काष्ठा netns_ipvs *ipvs, काष्ठा ip_vs_app *app, __u16 proto,
			   __u16 port);
पूर्णांक ip_vs_app_inc_get(काष्ठा ip_vs_app *inc);
व्योम ip_vs_app_inc_put(काष्ठा ip_vs_app *inc);

पूर्णांक ip_vs_app_pkt_out(काष्ठा ip_vs_conn *, काष्ठा sk_buff *skb,
		      काष्ठा ip_vs_iphdr *ipvsh);
पूर्णांक ip_vs_app_pkt_in(काष्ठा ip_vs_conn *, काष्ठा sk_buff *skb,
		     काष्ठा ip_vs_iphdr *ipvsh);

पूर्णांक रेजिस्टर_ip_vs_pe(काष्ठा ip_vs_pe *pe);
पूर्णांक unरेजिस्टर_ip_vs_pe(काष्ठा ip_vs_pe *pe);
काष्ठा ip_vs_pe *ip_vs_pe_getbyname(स्थिर अक्षर *name);
काष्ठा ip_vs_pe *__ip_vs_pe_getbyname(स्थिर अक्षर *pe_name);

/* Use a #घोषणा to aव्योम all of module.h just क्रम these trivial ops */
#घोषणा ip_vs_pe_get(pe)			\
	अगर (pe && pe->module)			\
		__module_get(pe->module);

#घोषणा ip_vs_pe_put(pe)			\
	अगर (pe && pe->module)			\
		module_put(pe->module);

/* IPVS protocol functions (from ip_vs_proto.c) */
पूर्णांक ip_vs_protocol_init(व्योम);
व्योम ip_vs_protocol_cleanup(व्योम);
व्योम ip_vs_protocol_समयout_change(काष्ठा netns_ipvs *ipvs, पूर्णांक flags);
पूर्णांक *ip_vs_create_समयout_table(पूर्णांक *table, पूर्णांक size);
व्योम ip_vs_tcpudp_debug_packet(पूर्णांक af, काष्ठा ip_vs_protocol *pp,
			       स्थिर काष्ठा sk_buff *skb, पूर्णांक offset,
			       स्थिर अक्षर *msg);

बाह्य काष्ठा ip_vs_protocol ip_vs_protocol_tcp;
बाह्य काष्ठा ip_vs_protocol ip_vs_protocol_udp;
बाह्य काष्ठा ip_vs_protocol ip_vs_protocol_icmp;
बाह्य काष्ठा ip_vs_protocol ip_vs_protocol_esp;
बाह्य काष्ठा ip_vs_protocol ip_vs_protocol_ah;
बाह्य काष्ठा ip_vs_protocol ip_vs_protocol_sctp;

/* Registering/unरेजिस्टरing scheduler functions
 * (from ip_vs_sched.c)
 */
पूर्णांक रेजिस्टर_ip_vs_scheduler(काष्ठा ip_vs_scheduler *scheduler);
पूर्णांक unरेजिस्टर_ip_vs_scheduler(काष्ठा ip_vs_scheduler *scheduler);
पूर्णांक ip_vs_bind_scheduler(काष्ठा ip_vs_service *svc,
			 काष्ठा ip_vs_scheduler *scheduler);
व्योम ip_vs_unbind_scheduler(काष्ठा ip_vs_service *svc,
			    काष्ठा ip_vs_scheduler *sched);
काष्ठा ip_vs_scheduler *ip_vs_scheduler_get(स्थिर अक्षर *sched_name);
व्योम ip_vs_scheduler_put(काष्ठा ip_vs_scheduler *scheduler);
काष्ठा ip_vs_conn *
ip_vs_schedule(काष्ठा ip_vs_service *svc, काष्ठा sk_buff *skb,
	       काष्ठा ip_vs_proto_data *pd, पूर्णांक *ignored,
	       काष्ठा ip_vs_iphdr *iph);
पूर्णांक ip_vs_leave(काष्ठा ip_vs_service *svc, काष्ठा sk_buff *skb,
		काष्ठा ip_vs_proto_data *pd, काष्ठा ip_vs_iphdr *iph);

व्योम ip_vs_scheduler_err(काष्ठा ip_vs_service *svc, स्थिर अक्षर *msg);

/* IPVS control data and functions (from ip_vs_ctl.c) */
बाह्य काष्ठा ip_vs_stats ip_vs_stats;
बाह्य पूर्णांक sysctl_ip_vs_sync_ver;

काष्ठा ip_vs_service *
ip_vs_service_find(काष्ठा netns_ipvs *ipvs, पूर्णांक af, __u32 fwmark, __u16 protocol,
		  स्थिर जोड़ nf_inet_addr *vaddr, __be16 vport);

bool ip_vs_has_real_service(काष्ठा netns_ipvs *ipvs, पूर्णांक af, __u16 protocol,
			    स्थिर जोड़ nf_inet_addr *daddr, __be16 dport);

काष्ठा ip_vs_dest *
ip_vs_find_real_service(काष्ठा netns_ipvs *ipvs, पूर्णांक af, __u16 protocol,
			स्थिर जोड़ nf_inet_addr *daddr, __be16 dport);
काष्ठा ip_vs_dest *ip_vs_find_tunnel(काष्ठा netns_ipvs *ipvs, पूर्णांक af,
				     स्थिर जोड़ nf_inet_addr *daddr,
				     __be16 tun_port);

पूर्णांक ip_vs_use_count_inc(व्योम);
व्योम ip_vs_use_count_dec(व्योम);
पूर्णांक ip_vs_रेजिस्टर_nl_ioctl(व्योम);
व्योम ip_vs_unरेजिस्टर_nl_ioctl(व्योम);
पूर्णांक ip_vs_control_init(व्योम);
व्योम ip_vs_control_cleanup(व्योम);
काष्ठा ip_vs_dest *
ip_vs_find_dest(काष्ठा netns_ipvs *ipvs, पूर्णांक svc_af, पूर्णांक dest_af,
		स्थिर जोड़ nf_inet_addr *daddr, __be16 dport,
		स्थिर जोड़ nf_inet_addr *vaddr, __be16 vport,
		__u16 protocol, __u32 fwmark, __u32 flags);
व्योम ip_vs_try_bind_dest(काष्ठा ip_vs_conn *cp);

अटल अंतरभूत व्योम ip_vs_dest_hold(काष्ठा ip_vs_dest *dest)
अणु
	refcount_inc(&dest->refcnt);
पूर्ण

अटल अंतरभूत व्योम ip_vs_dest_put(काष्ठा ip_vs_dest *dest)
अणु
	smp_mb__beक्रमe_atomic();
	refcount_dec(&dest->refcnt);
पूर्ण

अटल अंतरभूत व्योम ip_vs_dest_put_and_मुक्त(काष्ठा ip_vs_dest *dest)
अणु
	अगर (refcount_dec_and_test(&dest->refcnt))
		kमुक्त(dest);
पूर्ण

/* IPVS sync daemon data and function prototypes
 * (from ip_vs_sync.c)
 */
पूर्णांक start_sync_thपढ़ो(काष्ठा netns_ipvs *ipvs, काष्ठा ipvs_sync_daemon_cfg *cfg,
		      पूर्णांक state);
पूर्णांक stop_sync_thपढ़ो(काष्ठा netns_ipvs *ipvs, पूर्णांक state);
व्योम ip_vs_sync_conn(काष्ठा netns_ipvs *ipvs, काष्ठा ip_vs_conn *cp, पूर्णांक pkts);

/* IPVS rate estimator prototypes (from ip_vs_est.c) */
व्योम ip_vs_start_estimator(काष्ठा netns_ipvs *ipvs, काष्ठा ip_vs_stats *stats);
व्योम ip_vs_stop_estimator(काष्ठा netns_ipvs *ipvs, काष्ठा ip_vs_stats *stats);
व्योम ip_vs_zero_estimator(काष्ठा ip_vs_stats *stats);
व्योम ip_vs_पढ़ो_estimator(काष्ठा ip_vs_kstats *dst, काष्ठा ip_vs_stats *stats);

/* Various IPVS packet transmitters (from ip_vs_xmit.c) */
पूर्णांक ip_vs_null_xmit(काष्ठा sk_buff *skb, काष्ठा ip_vs_conn *cp,
		    काष्ठा ip_vs_protocol *pp, काष्ठा ip_vs_iphdr *iph);
पूर्णांक ip_vs_bypass_xmit(काष्ठा sk_buff *skb, काष्ठा ip_vs_conn *cp,
		      काष्ठा ip_vs_protocol *pp, काष्ठा ip_vs_iphdr *iph);
पूर्णांक ip_vs_nat_xmit(काष्ठा sk_buff *skb, काष्ठा ip_vs_conn *cp,
		   काष्ठा ip_vs_protocol *pp, काष्ठा ip_vs_iphdr *iph);
पूर्णांक ip_vs_tunnel_xmit(काष्ठा sk_buff *skb, काष्ठा ip_vs_conn *cp,
		      काष्ठा ip_vs_protocol *pp, काष्ठा ip_vs_iphdr *iph);
पूर्णांक ip_vs_dr_xmit(काष्ठा sk_buff *skb, काष्ठा ip_vs_conn *cp,
		  काष्ठा ip_vs_protocol *pp, काष्ठा ip_vs_iphdr *iph);
पूर्णांक ip_vs_icmp_xmit(काष्ठा sk_buff *skb, काष्ठा ip_vs_conn *cp,
		    काष्ठा ip_vs_protocol *pp, पूर्णांक offset,
		    अचिन्हित पूर्णांक hooknum, काष्ठा ip_vs_iphdr *iph);
व्योम ip_vs_dest_dst_rcu_मुक्त(काष्ठा rcu_head *head);

#अगर_घोषित CONFIG_IP_VS_IPV6
पूर्णांक ip_vs_bypass_xmit_v6(काष्ठा sk_buff *skb, काष्ठा ip_vs_conn *cp,
			 काष्ठा ip_vs_protocol *pp, काष्ठा ip_vs_iphdr *iph);
पूर्णांक ip_vs_nat_xmit_v6(काष्ठा sk_buff *skb, काष्ठा ip_vs_conn *cp,
		      काष्ठा ip_vs_protocol *pp, काष्ठा ip_vs_iphdr *iph);
पूर्णांक ip_vs_tunnel_xmit_v6(काष्ठा sk_buff *skb, काष्ठा ip_vs_conn *cp,
			 काष्ठा ip_vs_protocol *pp, काष्ठा ip_vs_iphdr *iph);
पूर्णांक ip_vs_dr_xmit_v6(काष्ठा sk_buff *skb, काष्ठा ip_vs_conn *cp,
		     काष्ठा ip_vs_protocol *pp, काष्ठा ip_vs_iphdr *iph);
पूर्णांक ip_vs_icmp_xmit_v6(काष्ठा sk_buff *skb, काष्ठा ip_vs_conn *cp,
		       काष्ठा ip_vs_protocol *pp, पूर्णांक offset,
		       अचिन्हित पूर्णांक hooknum, काष्ठा ip_vs_iphdr *iph);
#पूर्ण_अगर

#अगर_घोषित CONFIG_SYSCTL
/* This is a simple mechanism to ignore packets when
 * we are loaded. Just set ip_vs_drop_rate to 'n' and
 * we start to drop 1/rate of the packets
 */
अटल अंतरभूत पूर्णांक ip_vs_todrop(काष्ठा netns_ipvs *ipvs)
अणु
	अगर (!ipvs->drop_rate)
		वापस 0;
	अगर (--ipvs->drop_counter > 0)
		वापस 0;
	ipvs->drop_counter = ipvs->drop_rate;
	वापस 1;
पूर्ण
#अन्यथा
अटल अंतरभूत पूर्णांक ip_vs_todrop(काष्ठा netns_ipvs *ipvs) अणु वापस 0; पूर्ण
#पूर्ण_अगर

#अगर_घोषित CONFIG_SYSCTL
/* Enqueue delayed work क्रम expiring no dest connections
 * Only run when sysctl_expire_nodest=1
 */
अटल अंतरभूत व्योम ip_vs_enqueue_expire_nodest_conns(काष्ठा netns_ipvs *ipvs)
अणु
	अगर (sysctl_expire_nodest_conn(ipvs))
		queue_delayed_work(प्रणाली_दीर्घ_wq,
				   &ipvs->expire_nodest_conn_work, 1);
पूर्ण

व्योम ip_vs_expire_nodest_conn_flush(काष्ठा netns_ipvs *ipvs);
#अन्यथा
अटल अंतरभूत व्योम ip_vs_enqueue_expire_nodest_conns(काष्ठा netns_ipvs *ipvs) अणुपूर्ण
#पूर्ण_अगर

#घोषणा IP_VS_DFWD_METHOD(dest) (atomic_पढ़ो(&(dest)->conn_flags) & \
				 IP_VS_CONN_F_FWD_MASK)

/* ip_vs_fwd_tag वापसs the क्रमwarding tag of the connection */
#घोषणा IP_VS_FWD_METHOD(cp)  (cp->flags & IP_VS_CONN_F_FWD_MASK)

अटल अंतरभूत अक्षर ip_vs_fwd_tag(काष्ठा ip_vs_conn *cp)
अणु
	अक्षर fwd;

	चयन (IP_VS_FWD_METHOD(cp)) अणु
	हाल IP_VS_CONN_F_MASQ:
		fwd = 'M'; अवरोध;
	हाल IP_VS_CONN_F_LOCALNODE:
		fwd = 'L'; अवरोध;
	हाल IP_VS_CONN_F_TUNNEL:
		fwd = 'T'; अवरोध;
	हाल IP_VS_CONN_F_DROUTE:
		fwd = 'R'; अवरोध;
	हाल IP_VS_CONN_F_BYPASS:
		fwd = 'B'; अवरोध;
	शेष:
		fwd = '?'; अवरोध;
	पूर्ण
	वापस fwd;
पूर्ण

व्योम ip_vs_nat_icmp(काष्ठा sk_buff *skb, काष्ठा ip_vs_protocol *pp,
		    काष्ठा ip_vs_conn *cp, पूर्णांक dir);

#अगर_घोषित CONFIG_IP_VS_IPV6
व्योम ip_vs_nat_icmp_v6(काष्ठा sk_buff *skb, काष्ठा ip_vs_protocol *pp,
		       काष्ठा ip_vs_conn *cp, पूर्णांक dir);
#पूर्ण_अगर

__sum16 ip_vs_checksum_complete(काष्ठा sk_buff *skb, पूर्णांक offset);

अटल अंतरभूत __wsum ip_vs_check_dअगरf4(__be32 old, __be32 new, __wsum oldsum)
अणु
	__be32 dअगरf[2] = अणु ~old, new पूर्ण;

	वापस csum_partial(dअगरf, माप(dअगरf), oldsum);
पूर्ण

#अगर_घोषित CONFIG_IP_VS_IPV6
अटल अंतरभूत __wsum ip_vs_check_dअगरf16(स्थिर __be32 *old, स्थिर __be32 *new,
					__wsum oldsum)
अणु
	__be32 dअगरf[8] = अणु ~old[3], ~old[2], ~old[1], ~old[0],
			    new[3],  new[2],  new[1],  new[0] पूर्ण;

	वापस csum_partial(dअगरf, माप(dअगरf), oldsum);
पूर्ण
#पूर्ण_अगर

अटल अंतरभूत __wsum ip_vs_check_dअगरf2(__be16 old, __be16 new, __wsum oldsum)
अणु
	__be16 dअगरf[2] = अणु ~old, new पूर्ण;

	वापस csum_partial(dअगरf, माप(dअगरf), oldsum);
पूर्ण

/* Forget current conntrack (unconfirmed) and attach notrack entry */
अटल अंतरभूत व्योम ip_vs_notrack(काष्ठा sk_buff *skb)
अणु
#अगर defined(CONFIG_NF_CONNTRACK) || defined(CONFIG_NF_CONNTRACK_MODULE)
	क्रमागत ip_conntrack_info ctinfo;
	काष्ठा nf_conn *ct = nf_ct_get(skb, &ctinfo);

	अगर (ct) अणु
		nf_conntrack_put(&ct->ct_general);
		nf_ct_set(skb, शून्य, IP_CT_UNTRACKED);
	पूर्ण
#पूर्ण_अगर
पूर्ण

#अगर_घोषित CONFIG_IP_VS_NFCT
/* Netfilter connection tracking
 * (from ip_vs_nfct.c)
 */
अटल अंतरभूत पूर्णांक ip_vs_conntrack_enabled(काष्ठा netns_ipvs *ipvs)
अणु
#अगर_घोषित CONFIG_SYSCTL
	वापस ipvs->sysctl_conntrack;
#अन्यथा
	वापस 0;
#पूर्ण_अगर
पूर्ण

व्योम ip_vs_update_conntrack(काष्ठा sk_buff *skb, काष्ठा ip_vs_conn *cp,
			    पूर्णांक outin);
पूर्णांक ip_vs_confirm_conntrack(काष्ठा sk_buff *skb);
व्योम ip_vs_nfct_expect_related(काष्ठा sk_buff *skb, काष्ठा nf_conn *ct,
			       काष्ठा ip_vs_conn *cp, u_पूर्णांक8_t proto,
			       स्थिर __be16 port, पूर्णांक from_rs);
व्योम ip_vs_conn_drop_conntrack(काष्ठा ip_vs_conn *cp);

#अन्यथा

अटल अंतरभूत पूर्णांक ip_vs_conntrack_enabled(काष्ठा netns_ipvs *ipvs)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत व्योम ip_vs_update_conntrack(काष्ठा sk_buff *skb,
					  काष्ठा ip_vs_conn *cp, पूर्णांक outin)
अणु
पूर्ण

अटल अंतरभूत पूर्णांक ip_vs_confirm_conntrack(काष्ठा sk_buff *skb)
अणु
	वापस NF_ACCEPT;
पूर्ण

अटल अंतरभूत व्योम ip_vs_conn_drop_conntrack(काष्ठा ip_vs_conn *cp)
अणु
पूर्ण
#पूर्ण_अगर /* CONFIG_IP_VS_NFCT */

/* Using old conntrack that can not be redirected to another real server? */
अटल अंतरभूत bool ip_vs_conn_uses_old_conntrack(काष्ठा ip_vs_conn *cp,
						 काष्ठा sk_buff *skb)
अणु
#अगर_घोषित CONFIG_IP_VS_NFCT
	क्रमागत ip_conntrack_info ctinfo;
	काष्ठा nf_conn *ct;

	ct = nf_ct_get(skb, &ctinfo);
	अगर (ct && nf_ct_is_confirmed(ct))
		वापस true;
#पूर्ण_अगर
	वापस false;
पूर्ण

अटल अंतरभूत पूर्णांक ip_vs_रेजिस्टर_conntrack(काष्ठा ip_vs_service *svc)
अणु
#अगर IS_ENABLED(CONFIG_NF_CONNTRACK)
	पूर्णांक afmask = (svc->af == AF_INET6) ? 2 : 1;
	पूर्णांक ret = 0;

	अगर (!(svc->conntrack_afmask & afmask)) अणु
		ret = nf_ct_netns_get(svc->ipvs->net, svc->af);
		अगर (ret >= 0)
			svc->conntrack_afmask |= afmask;
	पूर्ण
	वापस ret;
#अन्यथा
	वापस 0;
#पूर्ण_अगर
पूर्ण

अटल अंतरभूत व्योम ip_vs_unरेजिस्टर_conntrack(काष्ठा ip_vs_service *svc)
अणु
#अगर IS_ENABLED(CONFIG_NF_CONNTRACK)
	पूर्णांक afmask = (svc->af == AF_INET6) ? 2 : 1;

	अगर (svc->conntrack_afmask & afmask) अणु
		nf_ct_netns_put(svc->ipvs->net, svc->af);
		svc->conntrack_afmask &= ~afmask;
	पूर्ण
#पूर्ण_अगर
पूर्ण

पूर्णांक ip_vs_रेजिस्टर_hooks(काष्ठा netns_ipvs *ipvs, अचिन्हित पूर्णांक af);
व्योम ip_vs_unरेजिस्टर_hooks(काष्ठा netns_ipvs *ipvs, अचिन्हित पूर्णांक af);

अटल अंतरभूत पूर्णांक
ip_vs_dest_conn_overhead(काष्ठा ip_vs_dest *dest)
अणु
	/* We think the overhead of processing active connections is 256
	 * बार higher than that of inactive connections in average. (This
	 * 256 बार might not be accurate, we will change it later) We
	 * use the following क्रमmula to estimate the overhead now:
	 *		  dest->activeconns*256 + dest->inactconns
	 */
	वापस (atomic_पढ़ो(&dest->activeconns) << 8) +
		atomic_पढ़ो(&dest->inactconns);
पूर्ण

#अगर_घोषित CONFIG_IP_VS_PROTO_TCP
INसूचीECT_CALLABLE_DECLARE(पूर्णांक
	tcp_snat_handler(काष्ठा sk_buff *skb, काष्ठा ip_vs_protocol *pp,
			 काष्ठा ip_vs_conn *cp, काष्ठा ip_vs_iphdr *iph));
#पूर्ण_अगर

#अगर_घोषित CONFIG_IP_VS_PROTO_UDP
INसूचीECT_CALLABLE_DECLARE(पूर्णांक
	udp_snat_handler(काष्ठा sk_buff *skb, काष्ठा ip_vs_protocol *pp,
			 काष्ठा ip_vs_conn *cp, काष्ठा ip_vs_iphdr *iph));
#पूर्ण_अगर
#पूर्ण_अगर	/* _NET_IP_VS_H */
