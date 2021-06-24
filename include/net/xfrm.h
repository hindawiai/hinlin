<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _NET_XFRM_H
#घोषणा _NET_XFRM_H

#समावेश <linux/compiler.h>
#समावेश <linux/xfrm.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/list.h>
#समावेश <linux/skbuff.h>
#समावेश <linux/socket.h>
#समावेश <linux/pfkeyv2.h>
#समावेश <linux/ipsec.h>
#समावेश <linux/in6.h>
#समावेश <linux/mutex.h>
#समावेश <linux/audit.h>
#समावेश <linux/slab.h>
#समावेश <linux/refcount.h>
#समावेश <linux/sockptr.h>

#समावेश <net/sock.h>
#समावेश <net/dst.h>
#समावेश <net/ip.h>
#समावेश <net/route.h>
#समावेश <net/ipv6.h>
#समावेश <net/ip6_fib.h>
#समावेश <net/flow.h>
#समावेश <net/gro_cells.h>

#समावेश <linux/पूर्णांकerrupt.h>

#अगर_घोषित CONFIG_XFRM_STATISTICS
#समावेश <net/snmp.h>
#पूर्ण_अगर

#घोषणा XFRM_PROTO_ESP		50
#घोषणा XFRM_PROTO_AH		51
#घोषणा XFRM_PROTO_COMP		108
#घोषणा XFRM_PROTO_IPIP		4
#घोषणा XFRM_PROTO_IPV6		41
#घोषणा XFRM_PROTO_ROUTING	IPPROTO_ROUTING
#घोषणा XFRM_PROTO_DSTOPTS	IPPROTO_DSTOPTS

#घोषणा XFRM_ALIGN4(len)	(((len) + 3) & ~3)
#घोषणा XFRM_ALIGN8(len)	(((len) + 7) & ~7)
#घोषणा MODULE_ALIAS_XFRM_MODE(family, encap) \
	MODULE_ALIAS("xfrm-mode-" __stringअगरy(family) "-" __stringअगरy(encap))
#घोषणा MODULE_ALIAS_XFRM_TYPE(family, proto) \
	MODULE_ALIAS("xfrm-type-" __stringअगरy(family) "-" __stringअगरy(proto))
#घोषणा MODULE_ALIAS_XFRM_OFFLOAD_TYPE(family, proto) \
	MODULE_ALIAS("xfrm-offload-" __stringअगरy(family) "-" __stringअगरy(proto))

#अगर_घोषित CONFIG_XFRM_STATISTICS
#घोषणा XFRM_INC_STATS(net, field)	SNMP_INC_STATS((net)->mib.xfrm_statistics, field)
#अन्यथा
#घोषणा XFRM_INC_STATS(net, field)	((व्योम)(net))
#पूर्ण_अगर


/* Organization of SPD aka "XFRM rules"
   ------------------------------------

   Basic objects:
   - policy rule, काष्ठा xfrm_policy (=SPD entry)
   - bundle of transक्रमmations, काष्ठा dst_entry == काष्ठा xfrm_dst (=SA bundle)
   - instance of a transक्रमmer, काष्ठा xfrm_state (=SA)
   - ढाँचा to clone xfrm_state, काष्ठा xfrm_पंचांगpl

   SPD is plain linear list of xfrm_policy rules, ordered by priority.
   (To be compatible with existing pfkeyv2 implementations,
   many rules with priority of 0x7fffffff are allowed to exist and
   such rules are ordered in an unpredictable way, thanks to bsd folks.)

   Lookup is plain linear search until the first match with selector.

   If "action" is "block", then we prohibit the flow, otherwise:
   अगर "xfrms_nr" is zero, the flow passes untransक्रमmed. Otherwise,
   policy entry has list of up to XFRM_MAX_DEPTH transक्रमmations,
   described by ढाँचाs xfrm_पंचांगpl. Each ढाँचा is resolved
   to a complete xfrm_state (see below) and we pack bundle of transक्रमmations
   to a dst_entry वापसed to requestor.

   dst -. xfrm  .-> xfrm_state #1
    |---. child .-> dst -. xfrm .-> xfrm_state #2
                     |---. child .-> dst -. xfrm .-> xfrm_state #3
                                      |---. child .-> शून्य

   Bundles are cached at xrfm_policy काष्ठा (field ->bundles).


   Resolution of xrfm_पंचांगpl
   -----------------------
   Template contains:
   1. ->mode		Mode: transport or tunnel
   2. ->id.proto	Protocol: AH/ESP/IPCOMP
   3. ->id.daddr	Remote tunnel endpoपूर्णांक, ignored क्रम transport mode.
      Q: allow to resolve security gateway?
   4. ->id.spi          If not zero, अटल SPI.
   5. ->saddr		Local tunnel endpoपूर्णांक, ignored क्रम transport mode.
   6. ->algos		List of allowed algos. Plain biपंचांगask now.
      Q: ealgos, aalgos, calgos. What a mess...
   7. ->share		Sharing mode.
      Q: how to implement निजी sharing mode? To add काष्ठा sock* to
      flow id?

   Having this ढाँचा we search through SAD searching क्रम entries
   with appropriate mode/proto/algo, permitted by selector.
   If no appropriate entry found, it is requested from key manager.

   PROBLEMS:
   Q: How to find all the bundles referring to a physical path क्रम
      PMTU discovery? Seems, dst should contain list of all parents...
      and enter to infinite locking hierarchy disaster.
      No! It is easier, we will not search क्रम them, let them find us.
      We add genid to each dst plus poपूर्णांकer to genid of raw IP route,
      pmtu disc will update pmtu on raw IP route and increase its genid.
      dst_check() will see this क्रम top level and trigger resyncing
      metrics. Plus, it will be made via sk->sk_dst_cache. Solved.
 */

काष्ठा xfrm_state_walk अणु
	काष्ठा list_head	all;
	u8			state;
	u8			dying;
	u8			proto;
	u32			seq;
	काष्ठा xfrm_address_filter *filter;
पूर्ण;

काष्ठा xfrm_state_offload अणु
	काष्ठा net_device	*dev;
	काष्ठा net_device	*real_dev;
	अचिन्हित दीर्घ		offload_handle;
	अचिन्हित पूर्णांक		num_exthdrs;
	u8			flags;
पूर्ण;

काष्ठा xfrm_mode अणु
	u8 encap;
	u8 family;
	u8 flags;
पूर्ण;

/* Flags क्रम xfrm_mode. */
क्रमागत अणु
	XFRM_MODE_FLAG_TUNNEL = 1,
पूर्ण;

/* Full description of state of transक्रमmer. */
काष्ठा xfrm_state अणु
	possible_net_t		xs_net;
	जोड़ अणु
		काष्ठा hlist_node	gclist;
		काष्ठा hlist_node	bydst;
	पूर्ण;
	काष्ठा hlist_node	bysrc;
	काष्ठा hlist_node	byspi;

	refcount_t		refcnt;
	spinlock_t		lock;

	काष्ठा xfrm_id		id;
	काष्ठा xfrm_selector	sel;
	काष्ठा xfrm_mark	mark;
	u32			अगर_id;
	u32			tfcpad;

	u32			genid;

	/* Key manager bits */
	काष्ठा xfrm_state_walk	km;

	/* Parameters of this state. */
	काष्ठा अणु
		u32		reqid;
		u8		mode;
		u8		replay_winकरोw;
		u8		aalgo, ealgo, calgo;
		u8		flags;
		u16		family;
		xfrm_address_t	saddr;
		पूर्णांक		header_len;
		पूर्णांक		trailer_len;
		u32		extra_flags;
		काष्ठा xfrm_mark	smark;
	पूर्ण props;

	काष्ठा xfrm_lअगरeसमय_cfg lft;

	/* Data क्रम transक्रमmer */
	काष्ठा xfrm_algo_auth	*aalg;
	काष्ठा xfrm_algo	*ealg;
	काष्ठा xfrm_algo	*calg;
	काष्ठा xfrm_algo_aead	*aead;
	स्थिर अक्षर		*geniv;

	/* Data क्रम encapsulator */
	काष्ठा xfrm_encap_पंचांगpl	*encap;
	काष्ठा sock __rcu	*encap_sk;

	/* Data क्रम care-of address */
	xfrm_address_t	*coaddr;

	/* IPComp needs an IPIP tunnel क्रम handling uncompressed packets */
	काष्ठा xfrm_state	*tunnel;

	/* If a tunnel, number of users + 1 */
	atomic_t		tunnel_users;

	/* State क्रम replay detection */
	काष्ठा xfrm_replay_state replay;
	काष्ठा xfrm_replay_state_esn *replay_esn;

	/* Replay detection state at the समय we sent the last notअगरication */
	काष्ठा xfrm_replay_state preplay;
	काष्ठा xfrm_replay_state_esn *preplay_esn;

	/* The functions क्रम replay detection. */
	स्थिर काष्ठा xfrm_replay *repl;

	/* पूर्णांकernal flag that only holds state क्रम delayed aevent at the
	 * moment
	*/
	u32			xflags;

	/* Replay detection notअगरication settings */
	u32			replay_maxage;
	u32			replay_maxdअगरf;

	/* Replay detection notअगरication समयr */
	काष्ठा समयr_list	rसमयr;

	/* Statistics */
	काष्ठा xfrm_stats	stats;

	काष्ठा xfrm_lअगरeसमय_cur curlft;
	काष्ठा hrसमयr		mसमयr;

	काष्ठा xfrm_state_offload xso;

	/* used to fix curlft->add_समय when changing date */
	दीर्घ		saved_पंचांगo;

	/* Last used समय */
	समय64_t		lastused;

	काष्ठा page_frag xfrag;

	/* Reference to data common to all the instances of this
	 * transक्रमmer. */
	स्थिर काष्ठा xfrm_type	*type;
	काष्ठा xfrm_mode	inner_mode;
	काष्ठा xfrm_mode	inner_mode_iaf;
	काष्ठा xfrm_mode	outer_mode;

	स्थिर काष्ठा xfrm_type_offload	*type_offload;

	/* Security context */
	काष्ठा xfrm_sec_ctx	*security;

	/* Private data of this transक्रमmer, क्रमmat is opaque,
	 * पूर्णांकerpreted by xfrm_type methods. */
	व्योम			*data;
पूर्ण;

अटल अंतरभूत काष्ठा net *xs_net(काष्ठा xfrm_state *x)
अणु
	वापस पढ़ो_pnet(&x->xs_net);
पूर्ण

/* xflags - make क्रमागत अगर more show up */
#घोषणा XFRM_TIME_DEFER	1
#घोषणा XFRM_SOFT_EXPIRE 2

क्रमागत अणु
	XFRM_STATE_VOID,
	XFRM_STATE_ACQ,
	XFRM_STATE_VALID,
	XFRM_STATE_ERROR,
	XFRM_STATE_EXPIRED,
	XFRM_STATE_DEAD
पूर्ण;

/* callback काष्ठाure passed from either netlink or pfkey */
काष्ठा km_event अणु
	जोड़ अणु
		u32 hard;
		u32 proto;
		u32 byid;
		u32 aevent;
		u32 type;
	पूर्ण data;

	u32	seq;
	u32	portid;
	u32	event;
	काष्ठा net *net;
पूर्ण;

काष्ठा xfrm_replay अणु
	व्योम	(*advance)(काष्ठा xfrm_state *x, __be32 net_seq);
	पूर्णांक	(*check)(काष्ठा xfrm_state *x,
			 काष्ठा sk_buff *skb,
			 __be32 net_seq);
	पूर्णांक	(*recheck)(काष्ठा xfrm_state *x,
			   काष्ठा sk_buff *skb,
			   __be32 net_seq);
	व्योम	(*notअगरy)(काष्ठा xfrm_state *x, पूर्णांक event);
	पूर्णांक	(*overflow)(काष्ठा xfrm_state *x, काष्ठा sk_buff *skb);
पूर्ण;

काष्ठा xfrm_अगर_cb अणु
	काष्ठा xfrm_अगर	*(*decode_session)(काष्ठा sk_buff *skb,
					   अचिन्हित लघु family);
पूर्ण;

व्योम xfrm_अगर_रेजिस्टर_cb(स्थिर काष्ठा xfrm_अगर_cb *अगरcb);
व्योम xfrm_अगर_unरेजिस्टर_cb(व्योम);

काष्ठा net_device;
काष्ठा xfrm_type;
काष्ठा xfrm_dst;
काष्ठा xfrm_policy_afinfo अणु
	काष्ठा dst_ops		*dst_ops;
	काष्ठा dst_entry	*(*dst_lookup)(काष्ठा net *net,
					       पूर्णांक tos, पूर्णांक oअगर,
					       स्थिर xfrm_address_t *saddr,
					       स्थिर xfrm_address_t *daddr,
					       u32 mark);
	पूर्णांक			(*get_saddr)(काष्ठा net *net, पूर्णांक oअगर,
					     xfrm_address_t *saddr,
					     xfrm_address_t *daddr,
					     u32 mark);
	पूर्णांक			(*fill_dst)(काष्ठा xfrm_dst *xdst,
					    काष्ठा net_device *dev,
					    स्थिर काष्ठा flowi *fl);
	काष्ठा dst_entry	*(*blackhole_route)(काष्ठा net *net, काष्ठा dst_entry *orig);
पूर्ण;

पूर्णांक xfrm_policy_रेजिस्टर_afinfo(स्थिर काष्ठा xfrm_policy_afinfo *afinfo, पूर्णांक family);
व्योम xfrm_policy_unरेजिस्टर_afinfo(स्थिर काष्ठा xfrm_policy_afinfo *afinfo);
व्योम km_policy_notअगरy(काष्ठा xfrm_policy *xp, पूर्णांक dir,
		      स्थिर काष्ठा km_event *c);
व्योम km_state_notअगरy(काष्ठा xfrm_state *x, स्थिर काष्ठा km_event *c);

काष्ठा xfrm_पंचांगpl;
पूर्णांक km_query(काष्ठा xfrm_state *x, काष्ठा xfrm_पंचांगpl *t,
	     काष्ठा xfrm_policy *pol);
व्योम km_state_expired(काष्ठा xfrm_state *x, पूर्णांक hard, u32 portid);
पूर्णांक __xfrm_state_delete(काष्ठा xfrm_state *x);

काष्ठा xfrm_state_afinfo अणु
	u8				family;
	u8				proto;

	स्थिर काष्ठा xfrm_type_offload *type_offload_esp;

	स्थिर काष्ठा xfrm_type		*type_esp;
	स्थिर काष्ठा xfrm_type		*type_ipip;
	स्थिर काष्ठा xfrm_type		*type_ipip6;
	स्थिर काष्ठा xfrm_type		*type_comp;
	स्थिर काष्ठा xfrm_type		*type_ah;
	स्थिर काष्ठा xfrm_type		*type_routing;
	स्थिर काष्ठा xfrm_type		*type_dstopts;

	पूर्णांक			(*output)(काष्ठा net *net, काष्ठा sock *sk, काष्ठा sk_buff *skb);
	पूर्णांक			(*transport_finish)(काष्ठा sk_buff *skb,
						    पूर्णांक async);
	व्योम			(*local_error)(काष्ठा sk_buff *skb, u32 mtu);
पूर्ण;

पूर्णांक xfrm_state_रेजिस्टर_afinfo(काष्ठा xfrm_state_afinfo *afinfo);
पूर्णांक xfrm_state_unरेजिस्टर_afinfo(काष्ठा xfrm_state_afinfo *afinfo);
काष्ठा xfrm_state_afinfo *xfrm_state_get_afinfo(अचिन्हित पूर्णांक family);
काष्ठा xfrm_state_afinfo *xfrm_state_afinfo_get_rcu(अचिन्हित पूर्णांक family);

काष्ठा xfrm_input_afinfo अणु
	u8			family;
	bool			is_ipip;
	पूर्णांक			(*callback)(काष्ठा sk_buff *skb, u8 protocol,
					    पूर्णांक err);
पूर्ण;

पूर्णांक xfrm_input_रेजिस्टर_afinfo(स्थिर काष्ठा xfrm_input_afinfo *afinfo);
पूर्णांक xfrm_input_unरेजिस्टर_afinfo(स्थिर काष्ठा xfrm_input_afinfo *afinfo);

व्योम xfrm_flush_gc(व्योम);
व्योम xfrm_state_delete_tunnel(काष्ठा xfrm_state *x);

काष्ठा xfrm_type अणु
	अक्षर			*description;
	काष्ठा module		*owner;
	u8			proto;
	u8			flags;
#घोषणा XFRM_TYPE_NON_FRAGMENT	1
#घोषणा XFRM_TYPE_REPLAY_PROT	2
#घोषणा XFRM_TYPE_LOCAL_COADDR	4
#घोषणा XFRM_TYPE_REMOTE_COADDR	8

	पूर्णांक			(*init_state)(काष्ठा xfrm_state *x);
	व्योम			(*deकाष्ठाor)(काष्ठा xfrm_state *);
	पूर्णांक			(*input)(काष्ठा xfrm_state *, काष्ठा sk_buff *skb);
	पूर्णांक			(*output)(काष्ठा xfrm_state *, काष्ठा sk_buff *pskb);
	पूर्णांक			(*reject)(काष्ठा xfrm_state *, काष्ठा sk_buff *,
					  स्थिर काष्ठा flowi *);
	पूर्णांक			(*hdr_offset)(काष्ठा xfrm_state *, काष्ठा sk_buff *, u8 **);
पूर्ण;

पूर्णांक xfrm_रेजिस्टर_type(स्थिर काष्ठा xfrm_type *type, अचिन्हित लघु family);
व्योम xfrm_unरेजिस्टर_type(स्थिर काष्ठा xfrm_type *type, अचिन्हित लघु family);

काष्ठा xfrm_type_offload अणु
	अक्षर		*description;
	काष्ठा module	*owner;
	u8		proto;
	व्योम		(*encap)(काष्ठा xfrm_state *, काष्ठा sk_buff *pskb);
	पूर्णांक		(*input_tail)(काष्ठा xfrm_state *x, काष्ठा sk_buff *skb);
	पूर्णांक		(*xmit)(काष्ठा xfrm_state *, काष्ठा sk_buff *pskb, netdev_features_t features);
पूर्ण;

पूर्णांक xfrm_रेजिस्टर_type_offload(स्थिर काष्ठा xfrm_type_offload *type, अचिन्हित लघु family);
व्योम xfrm_unरेजिस्टर_type_offload(स्थिर काष्ठा xfrm_type_offload *type, अचिन्हित लघु family);

अटल अंतरभूत पूर्णांक xfrm_af2proto(अचिन्हित पूर्णांक family)
अणु
	चयन(family) अणु
	हाल AF_INET:
		वापस IPPROTO_IPIP;
	हाल AF_INET6:
		वापस IPPROTO_IPV6;
	शेष:
		वापस 0;
	पूर्ण
पूर्ण

अटल अंतरभूत स्थिर काष्ठा xfrm_mode *xfrm_ip2inner_mode(काष्ठा xfrm_state *x, पूर्णांक ipproto)
अणु
	अगर ((ipproto == IPPROTO_IPIP && x->props.family == AF_INET) ||
	    (ipproto == IPPROTO_IPV6 && x->props.family == AF_INET6))
		वापस &x->inner_mode;
	अन्यथा
		वापस &x->inner_mode_iaf;
पूर्ण

काष्ठा xfrm_पंचांगpl अणु
/* id in ढाँचा is पूर्णांकerpreted as:
 * daddr - destination of tunnel, may be zero क्रम transport mode.
 * spi   - zero to acquire spi. Not zero अगर spi is अटल, then
 *	   daddr must be fixed too.
 * proto - AH/ESP/IPCOMP
 */
	काष्ठा xfrm_id		id;

/* Source address of tunnel. Ignored, अगर it is not a tunnel. */
	xfrm_address_t		saddr;

	अचिन्हित लघु		encap_family;

	u32			reqid;

/* Mode: transport, tunnel etc. */
	u8			mode;

/* Sharing mode: unique, this session only, this user only etc. */
	u8			share;

/* May skip this transfomration अगर no SA is found */
	u8			optional;

/* Skip aalgos/ealgos/calgos checks. */
	u8			allalgs;

/* Bit mask of algos allowed क्रम acquisition */
	u32			aalgos;
	u32			ealgos;
	u32			calgos;
पूर्ण;

#घोषणा XFRM_MAX_DEPTH		6
#घोषणा XFRM_MAX_OFFLOAD_DEPTH	1

काष्ठा xfrm_policy_walk_entry अणु
	काष्ठा list_head	all;
	u8			dead;
पूर्ण;

काष्ठा xfrm_policy_walk अणु
	काष्ठा xfrm_policy_walk_entry walk;
	u8 type;
	u32 seq;
पूर्ण;

काष्ठा xfrm_policy_queue अणु
	काष्ठा sk_buff_head	hold_queue;
	काष्ठा समयr_list	hold_समयr;
	अचिन्हित दीर्घ		समयout;
पूर्ण;

काष्ठा xfrm_policy अणु
	possible_net_t		xp_net;
	काष्ठा hlist_node	bydst;
	काष्ठा hlist_node	byidx;

	/* This lock only affects elements except क्रम entry. */
	rwlock_t		lock;
	refcount_t		refcnt;
	u32			pos;
	काष्ठा समयr_list	समयr;

	atomic_t		genid;
	u32			priority;
	u32			index;
	u32			अगर_id;
	काष्ठा xfrm_mark	mark;
	काष्ठा xfrm_selector	selector;
	काष्ठा xfrm_lअगरeसमय_cfg lft;
	काष्ठा xfrm_lअगरeसमय_cur curlft;
	काष्ठा xfrm_policy_walk_entry walk;
	काष्ठा xfrm_policy_queue polq;
	bool                    bydst_reinsert;
	u8			type;
	u8			action;
	u8			flags;
	u8			xfrm_nr;
	u16			family;
	काष्ठा xfrm_sec_ctx	*security;
	काष्ठा xfrm_पंचांगpl       	xfrm_vec[XFRM_MAX_DEPTH];
	काष्ठा hlist_node	bydst_inexact_list;
	काष्ठा rcu_head		rcu;
पूर्ण;

अटल अंतरभूत काष्ठा net *xp_net(स्थिर काष्ठा xfrm_policy *xp)
अणु
	वापस पढ़ो_pnet(&xp->xp_net);
पूर्ण

काष्ठा xfrm_kmaddress अणु
	xfrm_address_t          local;
	xfrm_address_t          remote;
	u32			reserved;
	u16			family;
पूर्ण;

काष्ठा xfrm_migrate अणु
	xfrm_address_t		old_daddr;
	xfrm_address_t		old_saddr;
	xfrm_address_t		new_daddr;
	xfrm_address_t		new_saddr;
	u8			proto;
	u8			mode;
	u16			reserved;
	u32			reqid;
	u16			old_family;
	u16			new_family;
पूर्ण;

#घोषणा XFRM_KM_TIMEOUT                30
/* what happened */
#घोषणा XFRM_REPLAY_UPDATE	XFRM_AE_CR
#घोषणा XFRM_REPLAY_TIMEOUT	XFRM_AE_CE

/* शेष aevent समयout in units of 100ms */
#घोषणा XFRM_AE_ETIME			10
/* Async Event समयr multiplier */
#घोषणा XFRM_AE_ETH_M			10
/* शेष seq threshold size */
#घोषणा XFRM_AE_SEQT_SIZE		2

काष्ठा xfrm_mgr अणु
	काष्ठा list_head	list;
	पूर्णांक			(*notअगरy)(काष्ठा xfrm_state *x, स्थिर काष्ठा km_event *c);
	पूर्णांक			(*acquire)(काष्ठा xfrm_state *x, काष्ठा xfrm_पंचांगpl *, काष्ठा xfrm_policy *xp);
	काष्ठा xfrm_policy	*(*compile_policy)(काष्ठा sock *sk, पूर्णांक opt, u8 *data, पूर्णांक len, पूर्णांक *dir);
	पूर्णांक			(*new_mapping)(काष्ठा xfrm_state *x, xfrm_address_t *ipaddr, __be16 sport);
	पूर्णांक			(*notअगरy_policy)(काष्ठा xfrm_policy *x, पूर्णांक dir, स्थिर काष्ठा km_event *c);
	पूर्णांक			(*report)(काष्ठा net *net, u8 proto, काष्ठा xfrm_selector *sel, xfrm_address_t *addr);
	पूर्णांक			(*migrate)(स्थिर काष्ठा xfrm_selector *sel,
					   u8 dir, u8 type,
					   स्थिर काष्ठा xfrm_migrate *m,
					   पूर्णांक num_bundles,
					   स्थिर काष्ठा xfrm_kmaddress *k,
					   स्थिर काष्ठा xfrm_encap_पंचांगpl *encap);
	bool			(*is_alive)(स्थिर काष्ठा km_event *c);
पूर्ण;

पूर्णांक xfrm_रेजिस्टर_km(काष्ठा xfrm_mgr *km);
पूर्णांक xfrm_unरेजिस्टर_km(काष्ठा xfrm_mgr *km);

काष्ठा xfrm_tunnel_skb_cb अणु
	जोड़ अणु
		काष्ठा inet_skb_parm h4;
		काष्ठा inet6_skb_parm h6;
	पूर्ण header;

	जोड़ अणु
		काष्ठा ip_tunnel *ip4;
		काष्ठा ip6_tnl *ip6;
	पूर्ण tunnel;
पूर्ण;

#घोषणा XFRM_TUNNEL_SKB_CB(__skb) ((काष्ठा xfrm_tunnel_skb_cb *)&((__skb)->cb[0]))

/*
 * This काष्ठाure is used क्रम the duration where packets are being
 * transक्रमmed by IPsec.  As soon as the packet leaves IPsec the
 * area beyond the generic IP part may be overwritten.
 */
काष्ठा xfrm_skb_cb अणु
	काष्ठा xfrm_tunnel_skb_cb header;

        /* Sequence number क्रम replay protection. */
	जोड़ अणु
		काष्ठा अणु
			__u32 low;
			__u32 hi;
		पूर्ण output;
		काष्ठा अणु
			__be32 low;
			__be32 hi;
		पूर्ण input;
	पूर्ण seq;
पूर्ण;

#घोषणा XFRM_SKB_CB(__skb) ((काष्ठा xfrm_skb_cb *)&((__skb)->cb[0]))

/*
 * This काष्ठाure is used by the afinfo prepare_input/prepare_output functions
 * to transmit header inक्रमmation to the mode input/output functions.
 */
काष्ठा xfrm_mode_skb_cb अणु
	काष्ठा xfrm_tunnel_skb_cb header;

	/* Copied from header क्रम IPv4, always set to zero and DF क्रम IPv6. */
	__be16 id;
	__be16 frag_off;

	/* IP header length (excluding options or extension headers). */
	u8 ihl;

	/* TOS क्रम IPv4, class क्रम IPv6. */
	u8 tos;

	/* TTL क्रम IPv4, hop limitक्रम IPv6. */
	u8 ttl;

	/* Protocol क्रम IPv4, NH क्रम IPv6. */
	u8 protocol;

	/* Option length क्रम IPv4, zero क्रम IPv6. */
	u8 optlen;

	/* Used by IPv6 only, zero क्रम IPv4. */
	u8 flow_lbl[3];
पूर्ण;

#घोषणा XFRM_MODE_SKB_CB(__skb) ((काष्ठा xfrm_mode_skb_cb *)&((__skb)->cb[0]))

/*
 * This काष्ठाure is used by the input processing to locate the SPI and
 * related inक्रमmation.
 */
काष्ठा xfrm_spi_skb_cb अणु
	काष्ठा xfrm_tunnel_skb_cb header;

	अचिन्हित पूर्णांक daddroff;
	अचिन्हित पूर्णांक family;
	__be32 seq;
पूर्ण;

#घोषणा XFRM_SPI_SKB_CB(__skb) ((काष्ठा xfrm_spi_skb_cb *)&((__skb)->cb[0]))

#अगर_घोषित CONFIG_AUDITSYSCALL
अटल अंतरभूत काष्ठा audit_buffer *xfrm_audit_start(स्थिर अक्षर *op)
अणु
	काष्ठा audit_buffer *audit_buf = शून्य;

	अगर (audit_enabled == AUDIT_OFF)
		वापस शून्य;
	audit_buf = audit_log_start(audit_context(), GFP_ATOMIC,
				    AUDIT_MAC_IPSEC_EVENT);
	अगर (audit_buf == शून्य)
		वापस शून्य;
	audit_log_क्रमmat(audit_buf, "op=%s", op);
	वापस audit_buf;
पूर्ण

अटल अंतरभूत व्योम xfrm_audit_helper_usrinfo(bool task_valid,
					     काष्ठा audit_buffer *audit_buf)
अणु
	स्थिर अचिन्हित पूर्णांक auid = from_kuid(&init_user_ns, task_valid ?
					    audit_get_loginuid(current) :
					    INVALID_UID);
	स्थिर अचिन्हित पूर्णांक ses = task_valid ? audit_get_sessionid(current) :
		AUDIT_SID_UNSET;

	audit_log_क्रमmat(audit_buf, " auid=%u ses=%u", auid, ses);
	audit_log_task_context(audit_buf);
पूर्ण

व्योम xfrm_audit_policy_add(काष्ठा xfrm_policy *xp, पूर्णांक result, bool task_valid);
व्योम xfrm_audit_policy_delete(काष्ठा xfrm_policy *xp, पूर्णांक result,
			      bool task_valid);
व्योम xfrm_audit_state_add(काष्ठा xfrm_state *x, पूर्णांक result, bool task_valid);
व्योम xfrm_audit_state_delete(काष्ठा xfrm_state *x, पूर्णांक result, bool task_valid);
व्योम xfrm_audit_state_replay_overflow(काष्ठा xfrm_state *x,
				      काष्ठा sk_buff *skb);
व्योम xfrm_audit_state_replay(काष्ठा xfrm_state *x, काष्ठा sk_buff *skb,
			     __be32 net_seq);
व्योम xfrm_audit_state_notfound_simple(काष्ठा sk_buff *skb, u16 family);
व्योम xfrm_audit_state_notfound(काष्ठा sk_buff *skb, u16 family, __be32 net_spi,
			       __be32 net_seq);
व्योम xfrm_audit_state_icvfail(काष्ठा xfrm_state *x, काष्ठा sk_buff *skb,
			      u8 proto);
#अन्यथा

अटल अंतरभूत व्योम xfrm_audit_policy_add(काष्ठा xfrm_policy *xp, पूर्णांक result,
					 bool task_valid)
अणु
पूर्ण

अटल अंतरभूत व्योम xfrm_audit_policy_delete(काष्ठा xfrm_policy *xp, पूर्णांक result,
					    bool task_valid)
अणु
पूर्ण

अटल अंतरभूत व्योम xfrm_audit_state_add(काष्ठा xfrm_state *x, पूर्णांक result,
					bool task_valid)
अणु
पूर्ण

अटल अंतरभूत व्योम xfrm_audit_state_delete(काष्ठा xfrm_state *x, पूर्णांक result,
					   bool task_valid)
अणु
पूर्ण

अटल अंतरभूत व्योम xfrm_audit_state_replay_overflow(काष्ठा xfrm_state *x,
					     काष्ठा sk_buff *skb)
अणु
पूर्ण

अटल अंतरभूत व्योम xfrm_audit_state_replay(काष्ठा xfrm_state *x,
					   काष्ठा sk_buff *skb, __be32 net_seq)
अणु
पूर्ण

अटल अंतरभूत व्योम xfrm_audit_state_notfound_simple(काष्ठा sk_buff *skb,
				      u16 family)
अणु
पूर्ण

अटल अंतरभूत व्योम xfrm_audit_state_notfound(काष्ठा sk_buff *skb, u16 family,
				      __be32 net_spi, __be32 net_seq)
अणु
पूर्ण

अटल अंतरभूत व्योम xfrm_audit_state_icvfail(काष्ठा xfrm_state *x,
				     काष्ठा sk_buff *skb, u8 proto)
अणु
पूर्ण
#पूर्ण_अगर /* CONFIG_AUDITSYSCALL */

अटल अंतरभूत व्योम xfrm_pol_hold(काष्ठा xfrm_policy *policy)
अणु
	अगर (likely(policy != शून्य))
		refcount_inc(&policy->refcnt);
पूर्ण

व्योम xfrm_policy_destroy(काष्ठा xfrm_policy *policy);

अटल अंतरभूत व्योम xfrm_pol_put(काष्ठा xfrm_policy *policy)
अणु
	अगर (refcount_dec_and_test(&policy->refcnt))
		xfrm_policy_destroy(policy);
पूर्ण

अटल अंतरभूत व्योम xfrm_pols_put(काष्ठा xfrm_policy **pols, पूर्णांक npols)
अणु
	पूर्णांक i;
	क्रम (i = npols - 1; i >= 0; --i)
		xfrm_pol_put(pols[i]);
पूर्ण

व्योम __xfrm_state_destroy(काष्ठा xfrm_state *, bool);

अटल अंतरभूत व्योम __xfrm_state_put(काष्ठा xfrm_state *x)
अणु
	refcount_dec(&x->refcnt);
पूर्ण

अटल अंतरभूत व्योम xfrm_state_put(काष्ठा xfrm_state *x)
अणु
	अगर (refcount_dec_and_test(&x->refcnt))
		__xfrm_state_destroy(x, false);
पूर्ण

अटल अंतरभूत व्योम xfrm_state_put_sync(काष्ठा xfrm_state *x)
अणु
	अगर (refcount_dec_and_test(&x->refcnt))
		__xfrm_state_destroy(x, true);
पूर्ण

अटल अंतरभूत व्योम xfrm_state_hold(काष्ठा xfrm_state *x)
अणु
	refcount_inc(&x->refcnt);
पूर्ण

अटल अंतरभूत bool addr_match(स्थिर व्योम *token1, स्थिर व्योम *token2,
			      अचिन्हित पूर्णांक prefixlen)
अणु
	स्थिर __be32 *a1 = token1;
	स्थिर __be32 *a2 = token2;
	अचिन्हित पूर्णांक pdw;
	अचिन्हित पूर्णांक pbi;

	pdw = prefixlen >> 5;	  /* num of whole u32 in prefix */
	pbi = prefixlen &  0x1f;  /* num of bits in incomplete u32 in prefix */

	अगर (pdw)
		अगर (स_भेद(a1, a2, pdw << 2))
			वापस false;

	अगर (pbi) अणु
		__be32 mask;

		mask = htonl((0xffffffff) << (32 - pbi));

		अगर ((a1[pdw] ^ a2[pdw]) & mask)
			वापस false;
	पूर्ण

	वापस true;
पूर्ण

अटल अंतरभूत bool addr4_match(__be32 a1, __be32 a2, u8 prefixlen)
अणु
	/* C99 6.5.7 (3): u32 << 32 is undefined behaviour */
	अगर (माप(दीर्घ) == 4 && prefixlen == 0)
		वापस true;
	वापस !((a1 ^ a2) & htonl(~0UL << (32 - prefixlen)));
पूर्ण

अटल __अंतरभूत__
__be16 xfrm_flowi_sport(स्थिर काष्ठा flowi *fl, स्थिर जोड़ flowi_uli *uli)
अणु
	__be16 port;
	चयन(fl->flowi_proto) अणु
	हाल IPPROTO_TCP:
	हाल IPPROTO_UDP:
	हाल IPPROTO_UDPLITE:
	हाल IPPROTO_SCTP:
		port = uli->ports.sport;
		अवरोध;
	हाल IPPROTO_ICMP:
	हाल IPPROTO_ICMPV6:
		port = htons(uli->icmpt.type);
		अवरोध;
	हाल IPPROTO_MH:
		port = htons(uli->mht.type);
		अवरोध;
	हाल IPPROTO_GRE:
		port = htons(ntohl(uli->gre_key) >> 16);
		अवरोध;
	शेष:
		port = 0;	/*XXX*/
	पूर्ण
	वापस port;
पूर्ण

अटल __अंतरभूत__
__be16 xfrm_flowi_dport(स्थिर काष्ठा flowi *fl, स्थिर जोड़ flowi_uli *uli)
अणु
	__be16 port;
	चयन(fl->flowi_proto) अणु
	हाल IPPROTO_TCP:
	हाल IPPROTO_UDP:
	हाल IPPROTO_UDPLITE:
	हाल IPPROTO_SCTP:
		port = uli->ports.dport;
		अवरोध;
	हाल IPPROTO_ICMP:
	हाल IPPROTO_ICMPV6:
		port = htons(uli->icmpt.code);
		अवरोध;
	हाल IPPROTO_GRE:
		port = htons(ntohl(uli->gre_key) & 0xffff);
		अवरोध;
	शेष:
		port = 0;	/*XXX*/
	पूर्ण
	वापस port;
पूर्ण

bool xfrm_selector_match(स्थिर काष्ठा xfrm_selector *sel,
			 स्थिर काष्ठा flowi *fl, अचिन्हित लघु family);

#अगर_घोषित CONFIG_SECURITY_NETWORK_XFRM
/*	If neither has a context --> match
 * 	Otherwise, both must have a context and the sids, करोi, alg must match
 */
अटल अंतरभूत bool xfrm_sec_ctx_match(काष्ठा xfrm_sec_ctx *s1, काष्ठा xfrm_sec_ctx *s2)
अणु
	वापस ((!s1 && !s2) ||
		(s1 && s2 &&
		 (s1->ctx_sid == s2->ctx_sid) &&
		 (s1->ctx_करोi == s2->ctx_करोi) &&
		 (s1->ctx_alg == s2->ctx_alg)));
पूर्ण
#अन्यथा
अटल अंतरभूत bool xfrm_sec_ctx_match(काष्ठा xfrm_sec_ctx *s1, काष्ठा xfrm_sec_ctx *s2)
अणु
	वापस true;
पूर्ण
#पूर्ण_अगर

/* A काष्ठा encoding bundle of transक्रमmations to apply to some set of flow.
 *
 * xdst->child poपूर्णांकs to the next element of bundle.
 * dst->xfrm  poपूर्णांकs to an instanse of transक्रमmer.
 *
 * Due to unक्रमtunate limitations of current routing cache, which we
 * have no समय to fix, it mirrors काष्ठा rtable and bound to the same
 * routing key, including saddr,daddr. However, we can have many of
 * bundles dअगरfering by session id. All the bundles grow from a parent
 * policy rule.
 */
काष्ठा xfrm_dst अणु
	जोड़ अणु
		काष्ठा dst_entry	dst;
		काष्ठा rtable		rt;
		काष्ठा rt6_info		rt6;
	पूर्ण u;
	काष्ठा dst_entry *route;
	काष्ठा dst_entry *child;
	काष्ठा dst_entry *path;
	काष्ठा xfrm_policy *pols[XFRM_POLICY_TYPE_MAX];
	पूर्णांक num_pols, num_xfrms;
	u32 xfrm_genid;
	u32 policy_genid;
	u32 route_mtu_cached;
	u32 child_mtu_cached;
	u32 route_cookie;
	u32 path_cookie;
पूर्ण;

अटल अंतरभूत काष्ठा dst_entry *xfrm_dst_path(स्थिर काष्ठा dst_entry *dst)
अणु
#अगर_घोषित CONFIG_XFRM
	अगर (dst->xfrm || (dst->flags & DST_XFRM_QUEUE)) अणु
		स्थिर काष्ठा xfrm_dst *xdst = (स्थिर काष्ठा xfrm_dst *) dst;

		वापस xdst->path;
	पूर्ण
#पूर्ण_अगर
	वापस (काष्ठा dst_entry *) dst;
पूर्ण

अटल अंतरभूत काष्ठा dst_entry *xfrm_dst_child(स्थिर काष्ठा dst_entry *dst)
अणु
#अगर_घोषित CONFIG_XFRM
	अगर (dst->xfrm || (dst->flags & DST_XFRM_QUEUE)) अणु
		काष्ठा xfrm_dst *xdst = (काष्ठा xfrm_dst *) dst;
		वापस xdst->child;
	पूर्ण
#पूर्ण_अगर
	वापस शून्य;
पूर्ण

#अगर_घोषित CONFIG_XFRM
अटल अंतरभूत व्योम xfrm_dst_set_child(काष्ठा xfrm_dst *xdst, काष्ठा dst_entry *child)
अणु
	xdst->child = child;
पूर्ण

अटल अंतरभूत व्योम xfrm_dst_destroy(काष्ठा xfrm_dst *xdst)
अणु
	xfrm_pols_put(xdst->pols, xdst->num_pols);
	dst_release(xdst->route);
	अगर (likely(xdst->u.dst.xfrm))
		xfrm_state_put(xdst->u.dst.xfrm);
पूर्ण
#पूर्ण_अगर

व्योम xfrm_dst_अगरकरोwn(काष्ठा dst_entry *dst, काष्ठा net_device *dev);

काष्ठा xfrm_अगर_parms अणु
	पूर्णांक link;		/* अगरindex of underlying L2 पूर्णांकerface */
	u32 अगर_id;		/* पूर्णांकerface identअगरyer */
पूर्ण;

काष्ठा xfrm_अगर अणु
	काष्ठा xfrm_अगर __rcu *next;	/* next पूर्णांकerface in list */
	काष्ठा net_device *dev;		/* भव device associated with पूर्णांकerface */
	काष्ठा net *net;		/* netns क्रम packet i/o */
	काष्ठा xfrm_अगर_parms p;		/* पूर्णांकerface parms */

	काष्ठा gro_cells gro_cells;
पूर्ण;

काष्ठा xfrm_offload अणु
	/* Output sequence number क्रम replay protection on offloading. */
	काष्ठा अणु
		__u32 low;
		__u32 hi;
	पूर्ण seq;

	__u32			flags;
#घोषणा	SA_DELETE_REQ		1
#घोषणा	CRYPTO_DONE		2
#घोषणा	CRYPTO_NEXT_DONE	4
#घोषणा	CRYPTO_FALLBACK		8
#घोषणा	XFRM_GSO_SEGMENT	16
#घोषणा	XFRM_GRO		32
#घोषणा	XFRM_ESP_NO_TRAILER	64
#घोषणा	XFRM_DEV_RESUME		128
#घोषणा	XFRM_XMIT		256

	__u32			status;
#घोषणा CRYPTO_SUCCESS				1
#घोषणा CRYPTO_GENERIC_ERROR			2
#घोषणा CRYPTO_TRANSPORT_AH_AUTH_FAILED		4
#घोषणा CRYPTO_TRANSPORT_ESP_AUTH_FAILED	8
#घोषणा CRYPTO_TUNNEL_AH_AUTH_FAILED		16
#घोषणा CRYPTO_TUNNEL_ESP_AUTH_FAILED		32
#घोषणा CRYPTO_INVALID_PACKET_SYNTAX		64
#घोषणा CRYPTO_INVALID_PROTOCOL			128

	__u8			proto;
पूर्ण;

काष्ठा sec_path अणु
	पूर्णांक			len;
	पूर्णांक			olen;

	काष्ठा xfrm_state	*xvec[XFRM_MAX_DEPTH];
	काष्ठा xfrm_offload	ovec[XFRM_MAX_OFFLOAD_DEPTH];
पूर्ण;

काष्ठा sec_path *secpath_set(काष्ठा sk_buff *skb);

अटल अंतरभूत व्योम
secpath_reset(काष्ठा sk_buff *skb)
अणु
#अगर_घोषित CONFIG_XFRM
	skb_ext_del(skb, SKB_EXT_SEC_PATH);
#पूर्ण_अगर
पूर्ण

अटल अंतरभूत पूर्णांक
xfrm_addr_any(स्थिर xfrm_address_t *addr, अचिन्हित लघु family)
अणु
	चयन (family) अणु
	हाल AF_INET:
		वापस addr->a4 == 0;
	हाल AF_INET6:
		वापस ipv6_addr_any(&addr->in6);
	पूर्ण
	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक
__xfrm4_state_addr_cmp(स्थिर काष्ठा xfrm_पंचांगpl *पंचांगpl, स्थिर काष्ठा xfrm_state *x)
अणु
	वापस	(पंचांगpl->saddr.a4 &&
		 पंचांगpl->saddr.a4 != x->props.saddr.a4);
पूर्ण

अटल अंतरभूत पूर्णांक
__xfrm6_state_addr_cmp(स्थिर काष्ठा xfrm_पंचांगpl *पंचांगpl, स्थिर काष्ठा xfrm_state *x)
अणु
	वापस	(!ipv6_addr_any((काष्ठा in6_addr*)&पंचांगpl->saddr) &&
		 !ipv6_addr_equal((काष्ठा in6_addr *)&पंचांगpl->saddr, (काष्ठा in6_addr*)&x->props.saddr));
पूर्ण

अटल अंतरभूत पूर्णांक
xfrm_state_addr_cmp(स्थिर काष्ठा xfrm_पंचांगpl *पंचांगpl, स्थिर काष्ठा xfrm_state *x, अचिन्हित लघु family)
अणु
	चयन (family) अणु
	हाल AF_INET:
		वापस __xfrm4_state_addr_cmp(पंचांगpl, x);
	हाल AF_INET6:
		वापस __xfrm6_state_addr_cmp(पंचांगpl, x);
	पूर्ण
	वापस !0;
पूर्ण

#अगर_घोषित CONFIG_XFRM
पूर्णांक __xfrm_policy_check(काष्ठा sock *, पूर्णांक dir, काष्ठा sk_buff *skb,
			अचिन्हित लघु family);

अटल अंतरभूत पूर्णांक __xfrm_policy_check2(काष्ठा sock *sk, पूर्णांक dir,
				       काष्ठा sk_buff *skb,
				       अचिन्हित पूर्णांक family, पूर्णांक reverse)
अणु
	काष्ठा net *net = dev_net(skb->dev);
	पूर्णांक ndir = dir | (reverse ? XFRM_POLICY_MASK + 1 : 0);

	अगर (sk && sk->sk_policy[XFRM_POLICY_IN])
		वापस __xfrm_policy_check(sk, ndir, skb, family);

	वापस	(!net->xfrm.policy_count[dir] && !secpath_exists(skb)) ||
		(skb_dst(skb) && (skb_dst(skb)->flags & DST_NOPOLICY)) ||
		__xfrm_policy_check(sk, ndir, skb, family);
पूर्ण

अटल अंतरभूत पूर्णांक xfrm_policy_check(काष्ठा sock *sk, पूर्णांक dir, काष्ठा sk_buff *skb, अचिन्हित लघु family)
अणु
	वापस __xfrm_policy_check2(sk, dir, skb, family, 0);
पूर्ण

अटल अंतरभूत पूर्णांक xfrm4_policy_check(काष्ठा sock *sk, पूर्णांक dir, काष्ठा sk_buff *skb)
अणु
	वापस xfrm_policy_check(sk, dir, skb, AF_INET);
पूर्ण

अटल अंतरभूत पूर्णांक xfrm6_policy_check(काष्ठा sock *sk, पूर्णांक dir, काष्ठा sk_buff *skb)
अणु
	वापस xfrm_policy_check(sk, dir, skb, AF_INET6);
पूर्ण

अटल अंतरभूत पूर्णांक xfrm4_policy_check_reverse(काष्ठा sock *sk, पूर्णांक dir,
					     काष्ठा sk_buff *skb)
अणु
	वापस __xfrm_policy_check2(sk, dir, skb, AF_INET, 1);
पूर्ण

अटल अंतरभूत पूर्णांक xfrm6_policy_check_reverse(काष्ठा sock *sk, पूर्णांक dir,
					     काष्ठा sk_buff *skb)
अणु
	वापस __xfrm_policy_check2(sk, dir, skb, AF_INET6, 1);
पूर्ण

पूर्णांक __xfrm_decode_session(काष्ठा sk_buff *skb, काष्ठा flowi *fl,
			  अचिन्हित पूर्णांक family, पूर्णांक reverse);

अटल अंतरभूत पूर्णांक xfrm_decode_session(काष्ठा sk_buff *skb, काष्ठा flowi *fl,
				      अचिन्हित पूर्णांक family)
अणु
	वापस __xfrm_decode_session(skb, fl, family, 0);
पूर्ण

अटल अंतरभूत पूर्णांक xfrm_decode_session_reverse(काष्ठा sk_buff *skb,
					      काष्ठा flowi *fl,
					      अचिन्हित पूर्णांक family)
अणु
	वापस __xfrm_decode_session(skb, fl, family, 1);
पूर्ण

पूर्णांक __xfrm_route_क्रमward(काष्ठा sk_buff *skb, अचिन्हित लघु family);

अटल अंतरभूत पूर्णांक xfrm_route_क्रमward(काष्ठा sk_buff *skb, अचिन्हित लघु family)
अणु
	काष्ठा net *net = dev_net(skb->dev);

	वापस	!net->xfrm.policy_count[XFRM_POLICY_OUT] ||
		(skb_dst(skb)->flags & DST_NOXFRM) ||
		__xfrm_route_क्रमward(skb, family);
पूर्ण

अटल अंतरभूत पूर्णांक xfrm4_route_क्रमward(काष्ठा sk_buff *skb)
अणु
	वापस xfrm_route_क्रमward(skb, AF_INET);
पूर्ण

अटल अंतरभूत पूर्णांक xfrm6_route_क्रमward(काष्ठा sk_buff *skb)
अणु
	वापस xfrm_route_क्रमward(skb, AF_INET6);
पूर्ण

पूर्णांक __xfrm_sk_clone_policy(काष्ठा sock *sk, स्थिर काष्ठा sock *osk);

अटल अंतरभूत पूर्णांक xfrm_sk_clone_policy(काष्ठा sock *sk, स्थिर काष्ठा sock *osk)
अणु
	sk->sk_policy[0] = शून्य;
	sk->sk_policy[1] = शून्य;
	अगर (unlikely(osk->sk_policy[0] || osk->sk_policy[1]))
		वापस __xfrm_sk_clone_policy(sk, osk);
	वापस 0;
पूर्ण

पूर्णांक xfrm_policy_delete(काष्ठा xfrm_policy *pol, पूर्णांक dir);

अटल अंतरभूत व्योम xfrm_sk_मुक्त_policy(काष्ठा sock *sk)
अणु
	काष्ठा xfrm_policy *pol;

	pol = rcu_dereference_रक्षित(sk->sk_policy[0], 1);
	अगर (unlikely(pol != शून्य)) अणु
		xfrm_policy_delete(pol, XFRM_POLICY_MAX);
		sk->sk_policy[0] = शून्य;
	पूर्ण
	pol = rcu_dereference_रक्षित(sk->sk_policy[1], 1);
	अगर (unlikely(pol != शून्य)) अणु
		xfrm_policy_delete(pol, XFRM_POLICY_MAX+1);
		sk->sk_policy[1] = शून्य;
	पूर्ण
पूर्ण

#अन्यथा

अटल अंतरभूत व्योम xfrm_sk_मुक्त_policy(काष्ठा sock *sk) अणुपूर्ण
अटल अंतरभूत पूर्णांक xfrm_sk_clone_policy(काष्ठा sock *sk, स्थिर काष्ठा sock *osk) अणु वापस 0; पूर्ण
अटल अंतरभूत पूर्णांक xfrm6_route_क्रमward(काष्ठा sk_buff *skb) अणु वापस 1; पूर्ण
अटल अंतरभूत पूर्णांक xfrm4_route_क्रमward(काष्ठा sk_buff *skb) अणु वापस 1; पूर्ण
अटल अंतरभूत पूर्णांक xfrm6_policy_check(काष्ठा sock *sk, पूर्णांक dir, काष्ठा sk_buff *skb)
अणु
	वापस 1;
पूर्ण
अटल अंतरभूत पूर्णांक xfrm4_policy_check(काष्ठा sock *sk, पूर्णांक dir, काष्ठा sk_buff *skb)
अणु
	वापस 1;
पूर्ण
अटल अंतरभूत पूर्णांक xfrm_policy_check(काष्ठा sock *sk, पूर्णांक dir, काष्ठा sk_buff *skb, अचिन्हित लघु family)
अणु
	वापस 1;
पूर्ण
अटल अंतरभूत पूर्णांक xfrm_decode_session_reverse(काष्ठा sk_buff *skb,
					      काष्ठा flowi *fl,
					      अचिन्हित पूर्णांक family)
अणु
	वापस -ENOSYS;
पूर्ण
अटल अंतरभूत पूर्णांक xfrm4_policy_check_reverse(काष्ठा sock *sk, पूर्णांक dir,
					     काष्ठा sk_buff *skb)
अणु
	वापस 1;
पूर्ण
अटल अंतरभूत पूर्णांक xfrm6_policy_check_reverse(काष्ठा sock *sk, पूर्णांक dir,
					     काष्ठा sk_buff *skb)
अणु
	वापस 1;
पूर्ण
#पूर्ण_अगर

अटल __अंतरभूत__
xfrm_address_t *xfrm_flowi_daddr(स्थिर काष्ठा flowi *fl, अचिन्हित लघु family)
अणु
	चयन (family)अणु
	हाल AF_INET:
		वापस (xfrm_address_t *)&fl->u.ip4.daddr;
	हाल AF_INET6:
		वापस (xfrm_address_t *)&fl->u.ip6.daddr;
	पूर्ण
	वापस शून्य;
पूर्ण

अटल __अंतरभूत__
xfrm_address_t *xfrm_flowi_saddr(स्थिर काष्ठा flowi *fl, अचिन्हित लघु family)
अणु
	चयन (family)अणु
	हाल AF_INET:
		वापस (xfrm_address_t *)&fl->u.ip4.saddr;
	हाल AF_INET6:
		वापस (xfrm_address_t *)&fl->u.ip6.saddr;
	पूर्ण
	वापस शून्य;
पूर्ण

अटल __अंतरभूत__
व्योम xfrm_flowi_addr_get(स्थिर काष्ठा flowi *fl,
			 xfrm_address_t *saddr, xfrm_address_t *daddr,
			 अचिन्हित लघु family)
अणु
	चयन(family) अणु
	हाल AF_INET:
		स_नकल(&saddr->a4, &fl->u.ip4.saddr, माप(saddr->a4));
		स_नकल(&daddr->a4, &fl->u.ip4.daddr, माप(daddr->a4));
		अवरोध;
	हाल AF_INET6:
		saddr->in6 = fl->u.ip6.saddr;
		daddr->in6 = fl->u.ip6.daddr;
		अवरोध;
	पूर्ण
पूर्ण

अटल __अंतरभूत__ पूर्णांक
__xfrm4_state_addr_check(स्थिर काष्ठा xfrm_state *x,
			 स्थिर xfrm_address_t *daddr, स्थिर xfrm_address_t *saddr)
अणु
	अगर (daddr->a4 == x->id.daddr.a4 &&
	    (saddr->a4 == x->props.saddr.a4 || !saddr->a4 || !x->props.saddr.a4))
		वापस 1;
	वापस 0;
पूर्ण

अटल __अंतरभूत__ पूर्णांक
__xfrm6_state_addr_check(स्थिर काष्ठा xfrm_state *x,
			 स्थिर xfrm_address_t *daddr, स्थिर xfrm_address_t *saddr)
अणु
	अगर (ipv6_addr_equal((काष्ठा in6_addr *)daddr, (काष्ठा in6_addr *)&x->id.daddr) &&
	    (ipv6_addr_equal((काष्ठा in6_addr *)saddr, (काष्ठा in6_addr *)&x->props.saddr) ||
	     ipv6_addr_any((काष्ठा in6_addr *)saddr) ||
	     ipv6_addr_any((काष्ठा in6_addr *)&x->props.saddr)))
		वापस 1;
	वापस 0;
पूर्ण

अटल __अंतरभूत__ पूर्णांक
xfrm_state_addr_check(स्थिर काष्ठा xfrm_state *x,
		      स्थिर xfrm_address_t *daddr, स्थिर xfrm_address_t *saddr,
		      अचिन्हित लघु family)
अणु
	चयन (family) अणु
	हाल AF_INET:
		वापस __xfrm4_state_addr_check(x, daddr, saddr);
	हाल AF_INET6:
		वापस __xfrm6_state_addr_check(x, daddr, saddr);
	पूर्ण
	वापस 0;
पूर्ण

अटल __अंतरभूत__ पूर्णांक
xfrm_state_addr_flow_check(स्थिर काष्ठा xfrm_state *x, स्थिर काष्ठा flowi *fl,
			   अचिन्हित लघु family)
अणु
	चयन (family) अणु
	हाल AF_INET:
		वापस __xfrm4_state_addr_check(x,
						(स्थिर xfrm_address_t *)&fl->u.ip4.daddr,
						(स्थिर xfrm_address_t *)&fl->u.ip4.saddr);
	हाल AF_INET6:
		वापस __xfrm6_state_addr_check(x,
						(स्थिर xfrm_address_t *)&fl->u.ip6.daddr,
						(स्थिर xfrm_address_t *)&fl->u.ip6.saddr);
	पूर्ण
	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक xfrm_state_kern(स्थिर काष्ठा xfrm_state *x)
अणु
	वापस atomic_पढ़ो(&x->tunnel_users);
पूर्ण

अटल अंतरभूत bool xfrm_id_proto_valid(u8 proto)
अणु
	चयन (proto) अणु
	हाल IPPROTO_AH:
	हाल IPPROTO_ESP:
	हाल IPPROTO_COMP:
#अगर IS_ENABLED(CONFIG_IPV6)
	हाल IPPROTO_ROUTING:
	हाल IPPROTO_DSTOPTS:
#पूर्ण_अगर
		वापस true;
	शेष:
		वापस false;
	पूर्ण
पूर्ण

/* IPSEC_PROTO_ANY only matches 3 IPsec protocols, 0 could match all. */
अटल अंतरभूत पूर्णांक xfrm_id_proto_match(u8 proto, u8 userproto)
अणु
	वापस (!userproto || proto == userproto ||
		(userproto == IPSEC_PROTO_ANY && (proto == IPPROTO_AH ||
						  proto == IPPROTO_ESP ||
						  proto == IPPROTO_COMP)));
पूर्ण

/*
 * xfrm algorithm inक्रमmation
 */
काष्ठा xfrm_algo_aead_info अणु
	अक्षर *geniv;
	u16 icv_truncbits;
पूर्ण;

काष्ठा xfrm_algo_auth_info अणु
	u16 icv_truncbits;
	u16 icv_fullbits;
पूर्ण;

काष्ठा xfrm_algo_encr_info अणु
	अक्षर *geniv;
	u16 blockbits;
	u16 defkeybits;
पूर्ण;

काष्ठा xfrm_algo_comp_info अणु
	u16 threshold;
पूर्ण;

काष्ठा xfrm_algo_desc अणु
	अक्षर *name;
	अक्षर *compat;
	u8 available:1;
	u8 pfkey_supported:1;
	जोड़ अणु
		काष्ठा xfrm_algo_aead_info aead;
		काष्ठा xfrm_algo_auth_info auth;
		काष्ठा xfrm_algo_encr_info encr;
		काष्ठा xfrm_algo_comp_info comp;
	पूर्ण uinfo;
	काष्ठा sadb_alg desc;
पूर्ण;

/* XFRM protocol handlers.  */
काष्ठा xfrm4_protocol अणु
	पूर्णांक (*handler)(काष्ठा sk_buff *skb);
	पूर्णांक (*input_handler)(काष्ठा sk_buff *skb, पूर्णांक nexthdr, __be32 spi,
			     पूर्णांक encap_type);
	पूर्णांक (*cb_handler)(काष्ठा sk_buff *skb, पूर्णांक err);
	पूर्णांक (*err_handler)(काष्ठा sk_buff *skb, u32 info);

	काष्ठा xfrm4_protocol __rcu *next;
	पूर्णांक priority;
पूर्ण;

काष्ठा xfrm6_protocol अणु
	पूर्णांक (*handler)(काष्ठा sk_buff *skb);
	पूर्णांक (*input_handler)(काष्ठा sk_buff *skb, पूर्णांक nexthdr, __be32 spi,
			     पूर्णांक encap_type);
	पूर्णांक (*cb_handler)(काष्ठा sk_buff *skb, पूर्णांक err);
	पूर्णांक (*err_handler)(काष्ठा sk_buff *skb, काष्ठा inet6_skb_parm *opt,
			   u8 type, u8 code, पूर्णांक offset, __be32 info);

	काष्ठा xfrm6_protocol __rcu *next;
	पूर्णांक priority;
पूर्ण;

/* XFRM tunnel handlers.  */
काष्ठा xfrm_tunnel अणु
	पूर्णांक (*handler)(काष्ठा sk_buff *skb);
	पूर्णांक (*cb_handler)(काष्ठा sk_buff *skb, पूर्णांक err);
	पूर्णांक (*err_handler)(काष्ठा sk_buff *skb, u32 info);

	काष्ठा xfrm_tunnel __rcu *next;
	पूर्णांक priority;
पूर्ण;

काष्ठा xfrm6_tunnel अणु
	पूर्णांक (*handler)(काष्ठा sk_buff *skb);
	पूर्णांक (*cb_handler)(काष्ठा sk_buff *skb, पूर्णांक err);
	पूर्णांक (*err_handler)(काष्ठा sk_buff *skb, काष्ठा inet6_skb_parm *opt,
			   u8 type, u8 code, पूर्णांक offset, __be32 info);
	काष्ठा xfrm6_tunnel __rcu *next;
	पूर्णांक priority;
पूर्ण;

व्योम xfrm_init(व्योम);
व्योम xfrm4_init(व्योम);
पूर्णांक xfrm_state_init(काष्ठा net *net);
व्योम xfrm_state_fini(काष्ठा net *net);
व्योम xfrm4_state_init(व्योम);
व्योम xfrm4_protocol_init(व्योम);
#अगर_घोषित CONFIG_XFRM
पूर्णांक xfrm6_init(व्योम);
व्योम xfrm6_fini(व्योम);
पूर्णांक xfrm6_state_init(व्योम);
व्योम xfrm6_state_fini(व्योम);
पूर्णांक xfrm6_protocol_init(व्योम);
व्योम xfrm6_protocol_fini(व्योम);
#अन्यथा
अटल अंतरभूत पूर्णांक xfrm6_init(व्योम)
अणु
	वापस 0;
पूर्ण
अटल अंतरभूत व्योम xfrm6_fini(व्योम)
अणु
	;
पूर्ण
#पूर्ण_अगर

#अगर_घोषित CONFIG_XFRM_STATISTICS
पूर्णांक xfrm_proc_init(काष्ठा net *net);
व्योम xfrm_proc_fini(काष्ठा net *net);
#पूर्ण_अगर

पूर्णांक xfrm_sysctl_init(काष्ठा net *net);
#अगर_घोषित CONFIG_SYSCTL
व्योम xfrm_sysctl_fini(काष्ठा net *net);
#अन्यथा
अटल अंतरभूत व्योम xfrm_sysctl_fini(काष्ठा net *net)
अणु
पूर्ण
#पूर्ण_अगर

व्योम xfrm_state_walk_init(काष्ठा xfrm_state_walk *walk, u8 proto,
			  काष्ठा xfrm_address_filter *filter);
पूर्णांक xfrm_state_walk(काष्ठा net *net, काष्ठा xfrm_state_walk *walk,
		    पूर्णांक (*func)(काष्ठा xfrm_state *, पूर्णांक, व्योम*), व्योम *);
व्योम xfrm_state_walk_करोne(काष्ठा xfrm_state_walk *walk, काष्ठा net *net);
काष्ठा xfrm_state *xfrm_state_alloc(काष्ठा net *net);
व्योम xfrm_state_मुक्त(काष्ठा xfrm_state *x);
काष्ठा xfrm_state *xfrm_state_find(स्थिर xfrm_address_t *daddr,
				   स्थिर xfrm_address_t *saddr,
				   स्थिर काष्ठा flowi *fl,
				   काष्ठा xfrm_पंचांगpl *पंचांगpl,
				   काष्ठा xfrm_policy *pol, पूर्णांक *err,
				   अचिन्हित लघु family, u32 अगर_id);
काष्ठा xfrm_state *xfrm_stateonly_find(काष्ठा net *net, u32 mark, u32 अगर_id,
				       xfrm_address_t *daddr,
				       xfrm_address_t *saddr,
				       अचिन्हित लघु family,
				       u8 mode, u8 proto, u32 reqid);
काष्ठा xfrm_state *xfrm_state_lookup_byspi(काष्ठा net *net, __be32 spi,
					      अचिन्हित लघु family);
पूर्णांक xfrm_state_check_expire(काष्ठा xfrm_state *x);
व्योम xfrm_state_insert(काष्ठा xfrm_state *x);
पूर्णांक xfrm_state_add(काष्ठा xfrm_state *x);
पूर्णांक xfrm_state_update(काष्ठा xfrm_state *x);
काष्ठा xfrm_state *xfrm_state_lookup(काष्ठा net *net, u32 mark,
				     स्थिर xfrm_address_t *daddr, __be32 spi,
				     u8 proto, अचिन्हित लघु family);
काष्ठा xfrm_state *xfrm_state_lookup_byaddr(काष्ठा net *net, u32 mark,
					    स्थिर xfrm_address_t *daddr,
					    स्थिर xfrm_address_t *saddr,
					    u8 proto,
					    अचिन्हित लघु family);
#अगर_घोषित CONFIG_XFRM_SUB_POLICY
व्योम xfrm_पंचांगpl_sort(काष्ठा xfrm_पंचांगpl **dst, काष्ठा xfrm_पंचांगpl **src, पूर्णांक n,
		    अचिन्हित लघु family);
व्योम xfrm_state_sort(काष्ठा xfrm_state **dst, काष्ठा xfrm_state **src, पूर्णांक n,
		     अचिन्हित लघु family);
#अन्यथा
अटल अंतरभूत व्योम xfrm_पंचांगpl_sort(काष्ठा xfrm_पंचांगpl **d, काष्ठा xfrm_पंचांगpl **s,
				  पूर्णांक n, अचिन्हित लघु family)
अणु
पूर्ण

अटल अंतरभूत व्योम xfrm_state_sort(काष्ठा xfrm_state **d, काष्ठा xfrm_state **s,
				   पूर्णांक n, अचिन्हित लघु family)
अणु
पूर्ण
#पूर्ण_अगर

काष्ठा xfrmk_sadinfo अणु
	u32 sadhcnt; /* current hash bkts */
	u32 sadhmcnt; /* max allowed hash bkts */
	u32 sadcnt; /* current running count */
पूर्ण;

काष्ठा xfrmk_spdinfo अणु
	u32 incnt;
	u32 outcnt;
	u32 fwdcnt;
	u32 inscnt;
	u32 outscnt;
	u32 fwdscnt;
	u32 spdhcnt;
	u32 spdhmcnt;
पूर्ण;

काष्ठा xfrm_state *xfrm_find_acq_byseq(काष्ठा net *net, u32 mark, u32 seq);
पूर्णांक xfrm_state_delete(काष्ठा xfrm_state *x);
पूर्णांक xfrm_state_flush(काष्ठा net *net, u8 proto, bool task_valid, bool sync);
पूर्णांक xfrm_dev_state_flush(काष्ठा net *net, काष्ठा net_device *dev, bool task_valid);
व्योम xfrm_sad_getinfo(काष्ठा net *net, काष्ठा xfrmk_sadinfo *si);
व्योम xfrm_spd_getinfo(काष्ठा net *net, काष्ठा xfrmk_spdinfo *si);
u32 xfrm_replay_seqhi(काष्ठा xfrm_state *x, __be32 net_seq);
पूर्णांक xfrm_init_replay(काष्ठा xfrm_state *x);
u32 xfrm_state_mtu(काष्ठा xfrm_state *x, पूर्णांक mtu);
पूर्णांक __xfrm_init_state(काष्ठा xfrm_state *x, bool init_replay, bool offload);
पूर्णांक xfrm_init_state(काष्ठा xfrm_state *x);
पूर्णांक xfrm_input(काष्ठा sk_buff *skb, पूर्णांक nexthdr, __be32 spi, पूर्णांक encap_type);
पूर्णांक xfrm_input_resume(काष्ठा sk_buff *skb, पूर्णांक nexthdr);
पूर्णांक xfrm_trans_queue_net(काष्ठा net *net, काष्ठा sk_buff *skb,
			 पूर्णांक (*finish)(काष्ठा net *, काष्ठा sock *,
				       काष्ठा sk_buff *));
पूर्णांक xfrm_trans_queue(काष्ठा sk_buff *skb,
		     पूर्णांक (*finish)(काष्ठा net *, काष्ठा sock *,
				   काष्ठा sk_buff *));
पूर्णांक xfrm_output_resume(काष्ठा sock *sk, काष्ठा sk_buff *skb, पूर्णांक err);
पूर्णांक xfrm_output(काष्ठा sock *sk, काष्ठा sk_buff *skb);

#अगर IS_ENABLED(CONFIG_NET_PKTGEN)
पूर्णांक pktgen_xfrm_outer_mode_output(काष्ठा xfrm_state *x, काष्ठा sk_buff *skb);
#पूर्ण_अगर

व्योम xfrm_local_error(काष्ठा sk_buff *skb, पूर्णांक mtu);
पूर्णांक xfrm4_extract_input(काष्ठा xfrm_state *x, काष्ठा sk_buff *skb);
पूर्णांक xfrm4_rcv_encap(काष्ठा sk_buff *skb, पूर्णांक nexthdr, __be32 spi,
		    पूर्णांक encap_type);
पूर्णांक xfrm4_transport_finish(काष्ठा sk_buff *skb, पूर्णांक async);
पूर्णांक xfrm4_rcv(काष्ठा sk_buff *skb);
पूर्णांक xfrm_parse_spi(काष्ठा sk_buff *skb, u8 nexthdr, __be32 *spi, __be32 *seq);

अटल अंतरभूत पूर्णांक xfrm4_rcv_spi(काष्ठा sk_buff *skb, पूर्णांक nexthdr, __be32 spi)
अणु
	XFRM_TUNNEL_SKB_CB(skb)->tunnel.ip4 = शून्य;
	XFRM_SPI_SKB_CB(skb)->family = AF_INET;
	XFRM_SPI_SKB_CB(skb)->daddroff = दुरत्व(काष्ठा iphdr, daddr);
	वापस xfrm_input(skb, nexthdr, spi, 0);
पूर्ण

पूर्णांक xfrm4_output(काष्ठा net *net, काष्ठा sock *sk, काष्ठा sk_buff *skb);
पूर्णांक xfrm4_output_finish(काष्ठा sock *sk, काष्ठा sk_buff *skb);
पूर्णांक xfrm4_protocol_रेजिस्टर(काष्ठा xfrm4_protocol *handler, अचिन्हित अक्षर protocol);
पूर्णांक xfrm4_protocol_deरेजिस्टर(काष्ठा xfrm4_protocol *handler, अचिन्हित अक्षर protocol);
पूर्णांक xfrm4_tunnel_रेजिस्टर(काष्ठा xfrm_tunnel *handler, अचिन्हित लघु family);
पूर्णांक xfrm4_tunnel_deरेजिस्टर(काष्ठा xfrm_tunnel *handler, अचिन्हित लघु family);
व्योम xfrm4_local_error(काष्ठा sk_buff *skb, u32 mtu);
पूर्णांक xfrm6_extract_input(काष्ठा xfrm_state *x, काष्ठा sk_buff *skb);
पूर्णांक xfrm6_rcv_spi(काष्ठा sk_buff *skb, पूर्णांक nexthdr, __be32 spi,
		  काष्ठा ip6_tnl *t);
पूर्णांक xfrm6_rcv_encap(काष्ठा sk_buff *skb, पूर्णांक nexthdr, __be32 spi,
		    पूर्णांक encap_type);
पूर्णांक xfrm6_transport_finish(काष्ठा sk_buff *skb, पूर्णांक async);
पूर्णांक xfrm6_rcv_tnl(काष्ठा sk_buff *skb, काष्ठा ip6_tnl *t);
पूर्णांक xfrm6_rcv(काष्ठा sk_buff *skb);
पूर्णांक xfrm6_input_addr(काष्ठा sk_buff *skb, xfrm_address_t *daddr,
		     xfrm_address_t *saddr, u8 proto);
व्योम xfrm6_local_error(काष्ठा sk_buff *skb, u32 mtu);
पूर्णांक xfrm6_protocol_रेजिस्टर(काष्ठा xfrm6_protocol *handler, अचिन्हित अक्षर protocol);
पूर्णांक xfrm6_protocol_deरेजिस्टर(काष्ठा xfrm6_protocol *handler, अचिन्हित अक्षर protocol);
पूर्णांक xfrm6_tunnel_रेजिस्टर(काष्ठा xfrm6_tunnel *handler, अचिन्हित लघु family);
पूर्णांक xfrm6_tunnel_deरेजिस्टर(काष्ठा xfrm6_tunnel *handler, अचिन्हित लघु family);
__be32 xfrm6_tunnel_alloc_spi(काष्ठा net *net, xfrm_address_t *saddr);
__be32 xfrm6_tunnel_spi_lookup(काष्ठा net *net, स्थिर xfrm_address_t *saddr);
पूर्णांक xfrm6_output(काष्ठा net *net, काष्ठा sock *sk, काष्ठा sk_buff *skb);
पूर्णांक xfrm6_output_finish(काष्ठा sock *sk, काष्ठा sk_buff *skb);
पूर्णांक xfrm6_find_1stfragopt(काष्ठा xfrm_state *x, काष्ठा sk_buff *skb,
			  u8 **prevhdr);

#अगर_घोषित CONFIG_XFRM
व्योम xfrm6_local_rxpmtu(काष्ठा sk_buff *skb, u32 mtu);
पूर्णांक xfrm4_udp_encap_rcv(काष्ठा sock *sk, काष्ठा sk_buff *skb);
पूर्णांक xfrm6_udp_encap_rcv(काष्ठा sock *sk, काष्ठा sk_buff *skb);
पूर्णांक xfrm_user_policy(काष्ठा sock *sk, पूर्णांक optname, sockptr_t optval,
		     पूर्णांक optlen);
#अन्यथा
अटल अंतरभूत पूर्णांक xfrm_user_policy(काष्ठा sock *sk, पूर्णांक optname,
				   sockptr_t optval, पूर्णांक optlen)
अणु
 	वापस -ENOPROTOOPT;
पूर्ण
#पूर्ण_अगर

काष्ठा dst_entry *__xfrm_dst_lookup(काष्ठा net *net, पूर्णांक tos, पूर्णांक oअगर,
				    स्थिर xfrm_address_t *saddr,
				    स्थिर xfrm_address_t *daddr,
				    पूर्णांक family, u32 mark);

काष्ठा xfrm_policy *xfrm_policy_alloc(काष्ठा net *net, gfp_t gfp);

व्योम xfrm_policy_walk_init(काष्ठा xfrm_policy_walk *walk, u8 type);
पूर्णांक xfrm_policy_walk(काष्ठा net *net, काष्ठा xfrm_policy_walk *walk,
		     पूर्णांक (*func)(काष्ठा xfrm_policy *, पूर्णांक, पूर्णांक, व्योम*),
		     व्योम *);
व्योम xfrm_policy_walk_करोne(काष्ठा xfrm_policy_walk *walk, काष्ठा net *net);
पूर्णांक xfrm_policy_insert(पूर्णांक dir, काष्ठा xfrm_policy *policy, पूर्णांक excl);
काष्ठा xfrm_policy *xfrm_policy_bysel_ctx(काष्ठा net *net,
					  स्थिर काष्ठा xfrm_mark *mark,
					  u32 अगर_id, u8 type, पूर्णांक dir,
					  काष्ठा xfrm_selector *sel,
					  काष्ठा xfrm_sec_ctx *ctx, पूर्णांक delete,
					  पूर्णांक *err);
काष्ठा xfrm_policy *xfrm_policy_byid(काष्ठा net *net,
				     स्थिर काष्ठा xfrm_mark *mark, u32 अगर_id,
				     u8 type, पूर्णांक dir, u32 id, पूर्णांक delete,
				     पूर्णांक *err);
पूर्णांक xfrm_policy_flush(काष्ठा net *net, u8 type, bool task_valid);
व्योम xfrm_policy_hash_rebuild(काष्ठा net *net);
u32 xfrm_get_acqseq(व्योम);
पूर्णांक verअगरy_spi_info(u8 proto, u32 min, u32 max);
पूर्णांक xfrm_alloc_spi(काष्ठा xfrm_state *x, u32 minspi, u32 maxspi);
काष्ठा xfrm_state *xfrm_find_acq(काष्ठा net *net, स्थिर काष्ठा xfrm_mark *mark,
				 u8 mode, u32 reqid, u32 अगर_id, u8 proto,
				 स्थिर xfrm_address_t *daddr,
				 स्थिर xfrm_address_t *saddr, पूर्णांक create,
				 अचिन्हित लघु family);
पूर्णांक xfrm_sk_policy_insert(काष्ठा sock *sk, पूर्णांक dir, काष्ठा xfrm_policy *pol);

#अगर_घोषित CONFIG_XFRM_MIGRATE
पूर्णांक km_migrate(स्थिर काष्ठा xfrm_selector *sel, u8 dir, u8 type,
	       स्थिर काष्ठा xfrm_migrate *m, पूर्णांक num_bundles,
	       स्थिर काष्ठा xfrm_kmaddress *k,
	       स्थिर काष्ठा xfrm_encap_पंचांगpl *encap);
काष्ठा xfrm_state *xfrm_migrate_state_find(काष्ठा xfrm_migrate *m, काष्ठा net *net);
काष्ठा xfrm_state *xfrm_state_migrate(काष्ठा xfrm_state *x,
				      काष्ठा xfrm_migrate *m,
				      काष्ठा xfrm_encap_पंचांगpl *encap);
पूर्णांक xfrm_migrate(स्थिर काष्ठा xfrm_selector *sel, u8 dir, u8 type,
		 काष्ठा xfrm_migrate *m, पूर्णांक num_bundles,
		 काष्ठा xfrm_kmaddress *k, काष्ठा net *net,
		 काष्ठा xfrm_encap_पंचांगpl *encap);
#पूर्ण_अगर

पूर्णांक km_new_mapping(काष्ठा xfrm_state *x, xfrm_address_t *ipaddr, __be16 sport);
व्योम km_policy_expired(काष्ठा xfrm_policy *pol, पूर्णांक dir, पूर्णांक hard, u32 portid);
पूर्णांक km_report(काष्ठा net *net, u8 proto, काष्ठा xfrm_selector *sel,
	      xfrm_address_t *addr);

व्योम xfrm_input_init(व्योम);
पूर्णांक xfrm_parse_spi(काष्ठा sk_buff *skb, u8 nexthdr, __be32 *spi, __be32 *seq);

व्योम xfrm_probe_algs(व्योम);
पूर्णांक xfrm_count_pfkey_auth_supported(व्योम);
पूर्णांक xfrm_count_pfkey_enc_supported(व्योम);
काष्ठा xfrm_algo_desc *xfrm_aalg_get_byidx(अचिन्हित पूर्णांक idx);
काष्ठा xfrm_algo_desc *xfrm_ealg_get_byidx(अचिन्हित पूर्णांक idx);
काष्ठा xfrm_algo_desc *xfrm_aalg_get_byid(पूर्णांक alg_id);
काष्ठा xfrm_algo_desc *xfrm_ealg_get_byid(पूर्णांक alg_id);
काष्ठा xfrm_algo_desc *xfrm_calg_get_byid(पूर्णांक alg_id);
काष्ठा xfrm_algo_desc *xfrm_aalg_get_byname(स्थिर अक्षर *name, पूर्णांक probe);
काष्ठा xfrm_algo_desc *xfrm_ealg_get_byname(स्थिर अक्षर *name, पूर्णांक probe);
काष्ठा xfrm_algo_desc *xfrm_calg_get_byname(स्थिर अक्षर *name, पूर्णांक probe);
काष्ठा xfrm_algo_desc *xfrm_aead_get_byname(स्थिर अक्षर *name, पूर्णांक icv_len,
					    पूर्णांक probe);

अटल अंतरभूत bool xfrm6_addr_equal(स्थिर xfrm_address_t *a,
				    स्थिर xfrm_address_t *b)
अणु
	वापस ipv6_addr_equal((स्थिर काष्ठा in6_addr *)a,
			       (स्थिर काष्ठा in6_addr *)b);
पूर्ण

अटल अंतरभूत bool xfrm_addr_equal(स्थिर xfrm_address_t *a,
				   स्थिर xfrm_address_t *b,
				   sa_family_t family)
अणु
	चयन (family) अणु
	शेष:
	हाल AF_INET:
		वापस ((__क्रमce u32)a->a4 ^ (__क्रमce u32)b->a4) == 0;
	हाल AF_INET6:
		वापस xfrm6_addr_equal(a, b);
	पूर्ण
पूर्ण

अटल अंतरभूत पूर्णांक xfrm_policy_id2dir(u32 index)
अणु
	वापस index & 7;
पूर्ण

#अगर_घोषित CONFIG_XFRM
अटल अंतरभूत पूर्णांक xfrm_aevent_is_on(काष्ठा net *net)
अणु
	काष्ठा sock *nlsk;
	पूर्णांक ret = 0;

	rcu_पढ़ो_lock();
	nlsk = rcu_dereference(net->xfrm.nlsk);
	अगर (nlsk)
		ret = netlink_has_listeners(nlsk, XFRMNLGRP_AEVENTS);
	rcu_पढ़ो_unlock();
	वापस ret;
पूर्ण

अटल अंतरभूत पूर्णांक xfrm_acquire_is_on(काष्ठा net *net)
अणु
	काष्ठा sock *nlsk;
	पूर्णांक ret = 0;

	rcu_पढ़ो_lock();
	nlsk = rcu_dereference(net->xfrm.nlsk);
	अगर (nlsk)
		ret = netlink_has_listeners(nlsk, XFRMNLGRP_ACQUIRE);
	rcu_पढ़ो_unlock();

	वापस ret;
पूर्ण
#पूर्ण_अगर

अटल अंतरभूत अचिन्हित पूर्णांक aead_len(काष्ठा xfrm_algo_aead *alg)
अणु
	वापस माप(*alg) + ((alg->alg_key_len + 7) / 8);
पूर्ण

अटल अंतरभूत अचिन्हित पूर्णांक xfrm_alg_len(स्थिर काष्ठा xfrm_algo *alg)
अणु
	वापस माप(*alg) + ((alg->alg_key_len + 7) / 8);
पूर्ण

अटल अंतरभूत अचिन्हित पूर्णांक xfrm_alg_auth_len(स्थिर काष्ठा xfrm_algo_auth *alg)
अणु
	वापस माप(*alg) + ((alg->alg_key_len + 7) / 8);
पूर्ण

अटल अंतरभूत अचिन्हित पूर्णांक xfrm_replay_state_esn_len(काष्ठा xfrm_replay_state_esn *replay_esn)
अणु
	वापस माप(*replay_esn) + replay_esn->bmp_len * माप(__u32);
पूर्ण

#अगर_घोषित CONFIG_XFRM_MIGRATE
अटल अंतरभूत पूर्णांक xfrm_replay_clone(काष्ठा xfrm_state *x,
				     काष्ठा xfrm_state *orig)
अणु

	x->replay_esn = kmemdup(orig->replay_esn,
				xfrm_replay_state_esn_len(orig->replay_esn),
				GFP_KERNEL);
	अगर (!x->replay_esn)
		वापस -ENOMEM;
	x->preplay_esn = kmemdup(orig->preplay_esn,
				 xfrm_replay_state_esn_len(orig->preplay_esn),
				 GFP_KERNEL);
	अगर (!x->preplay_esn)
		वापस -ENOMEM;

	वापस 0;
पूर्ण

अटल अंतरभूत काष्ठा xfrm_algo_aead *xfrm_algo_aead_clone(काष्ठा xfrm_algo_aead *orig)
अणु
	वापस kmemdup(orig, aead_len(orig), GFP_KERNEL);
पूर्ण


अटल अंतरभूत काष्ठा xfrm_algo *xfrm_algo_clone(काष्ठा xfrm_algo *orig)
अणु
	वापस kmemdup(orig, xfrm_alg_len(orig), GFP_KERNEL);
पूर्ण

अटल अंतरभूत काष्ठा xfrm_algo_auth *xfrm_algo_auth_clone(काष्ठा xfrm_algo_auth *orig)
अणु
	वापस kmemdup(orig, xfrm_alg_auth_len(orig), GFP_KERNEL);
पूर्ण

अटल अंतरभूत व्योम xfrm_states_put(काष्ठा xfrm_state **states, पूर्णांक n)
अणु
	पूर्णांक i;
	क्रम (i = 0; i < n; i++)
		xfrm_state_put(*(states + i));
पूर्ण

अटल अंतरभूत व्योम xfrm_states_delete(काष्ठा xfrm_state **states, पूर्णांक n)
अणु
	पूर्णांक i;
	क्रम (i = 0; i < n; i++)
		xfrm_state_delete(*(states + i));
पूर्ण
#पूर्ण_अगर

#अगर_घोषित CONFIG_XFRM
अटल अंतरभूत काष्ठा xfrm_state *xfrm_input_state(काष्ठा sk_buff *skb)
अणु
	काष्ठा sec_path *sp = skb_sec_path(skb);

	वापस sp->xvec[sp->len - 1];
पूर्ण
#पूर्ण_अगर

अटल अंतरभूत काष्ठा xfrm_offload *xfrm_offload(काष्ठा sk_buff *skb)
अणु
#अगर_घोषित CONFIG_XFRM
	काष्ठा sec_path *sp = skb_sec_path(skb);

	अगर (!sp || !sp->olen || sp->len != sp->olen)
		वापस शून्य;

	वापस &sp->ovec[sp->olen - 1];
#अन्यथा
	वापस शून्य;
#पूर्ण_अगर
पूर्ण

व्योम __init xfrm_dev_init(व्योम);

#अगर_घोषित CONFIG_XFRM_OFFLOAD
व्योम xfrm_dev_resume(काष्ठा sk_buff *skb);
व्योम xfrm_dev_backlog(काष्ठा softnet_data *sd);
काष्ठा sk_buff *validate_xmit_xfrm(काष्ठा sk_buff *skb, netdev_features_t features, bool *again);
पूर्णांक xfrm_dev_state_add(काष्ठा net *net, काष्ठा xfrm_state *x,
		       काष्ठा xfrm_user_offload *xuo);
bool xfrm_dev_offload_ok(काष्ठा sk_buff *skb, काष्ठा xfrm_state *x);

अटल अंतरभूत व्योम xfrm_dev_state_advance_esn(काष्ठा xfrm_state *x)
अणु
	काष्ठा xfrm_state_offload *xso = &x->xso;

	अगर (xso->dev && xso->dev->xfrmdev_ops->xकरो_dev_state_advance_esn)
		xso->dev->xfrmdev_ops->xकरो_dev_state_advance_esn(x);
पूर्ण

अटल अंतरभूत bool xfrm_dst_offload_ok(काष्ठा dst_entry *dst)
अणु
	काष्ठा xfrm_state *x = dst->xfrm;
	काष्ठा xfrm_dst *xdst;

	अगर (!x || !x->type_offload)
		वापस false;

	xdst = (काष्ठा xfrm_dst *) dst;
	अगर (!x->xso.offload_handle && !xdst->child->xfrm)
		वापस true;
	अगर (x->xso.offload_handle && (x->xso.dev == xfrm_dst_path(dst)->dev) &&
	    !xdst->child->xfrm)
		वापस true;

	वापस false;
पूर्ण

अटल अंतरभूत व्योम xfrm_dev_state_delete(काष्ठा xfrm_state *x)
अणु
	काष्ठा xfrm_state_offload *xso = &x->xso;

	अगर (xso->dev)
		xso->dev->xfrmdev_ops->xकरो_dev_state_delete(x);
पूर्ण

अटल अंतरभूत व्योम xfrm_dev_state_मुक्त(काष्ठा xfrm_state *x)
अणु
	काष्ठा xfrm_state_offload *xso = &x->xso;
	काष्ठा net_device *dev = xso->dev;

	अगर (dev && dev->xfrmdev_ops) अणु
		अगर (dev->xfrmdev_ops->xकरो_dev_state_मुक्त)
			dev->xfrmdev_ops->xकरो_dev_state_मुक्त(x);
		xso->dev = शून्य;
		dev_put(dev);
	पूर्ण
पूर्ण
#अन्यथा
अटल अंतरभूत व्योम xfrm_dev_resume(काष्ठा sk_buff *skb)
अणु
पूर्ण

अटल अंतरभूत व्योम xfrm_dev_backlog(काष्ठा softnet_data *sd)
अणु
पूर्ण

अटल अंतरभूत काष्ठा sk_buff *validate_xmit_xfrm(काष्ठा sk_buff *skb, netdev_features_t features, bool *again)
अणु
	वापस skb;
पूर्ण

अटल अंतरभूत पूर्णांक xfrm_dev_state_add(काष्ठा net *net, काष्ठा xfrm_state *x, काष्ठा xfrm_user_offload *xuo)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत व्योम xfrm_dev_state_delete(काष्ठा xfrm_state *x)
अणु
पूर्ण

अटल अंतरभूत व्योम xfrm_dev_state_मुक्त(काष्ठा xfrm_state *x)
अणु
पूर्ण

अटल अंतरभूत bool xfrm_dev_offload_ok(काष्ठा sk_buff *skb, काष्ठा xfrm_state *x)
अणु
	वापस false;
पूर्ण

अटल अंतरभूत व्योम xfrm_dev_state_advance_esn(काष्ठा xfrm_state *x)
अणु
पूर्ण

अटल अंतरभूत bool xfrm_dst_offload_ok(काष्ठा dst_entry *dst)
अणु
	वापस false;
पूर्ण
#पूर्ण_अगर

अटल अंतरभूत पूर्णांक xfrm_mark_get(काष्ठा nlattr **attrs, काष्ठा xfrm_mark *m)
अणु
	अगर (attrs[XFRMA_MARK])
		स_नकल(m, nla_data(attrs[XFRMA_MARK]), माप(काष्ठा xfrm_mark));
	अन्यथा
		m->v = m->m = 0;

	वापस m->v & m->m;
पूर्ण

अटल अंतरभूत पूर्णांक xfrm_mark_put(काष्ठा sk_buff *skb, स्थिर काष्ठा xfrm_mark *m)
अणु
	पूर्णांक ret = 0;

	अगर (m->m | m->v)
		ret = nla_put(skb, XFRMA_MARK, माप(काष्ठा xfrm_mark), m);
	वापस ret;
पूर्ण

अटल अंतरभूत __u32 xfrm_smark_get(__u32 mark, काष्ठा xfrm_state *x)
अणु
	काष्ठा xfrm_mark *m = &x->props.smark;

	वापस (m->v & m->m) | (mark & ~m->m);
पूर्ण

अटल अंतरभूत पूर्णांक xfrm_अगर_id_put(काष्ठा sk_buff *skb, __u32 अगर_id)
अणु
	पूर्णांक ret = 0;

	अगर (अगर_id)
		ret = nla_put_u32(skb, XFRMA_IF_ID, अगर_id);
	वापस ret;
पूर्ण

अटल अंतरभूत पूर्णांक xfrm_tunnel_check(काष्ठा sk_buff *skb, काष्ठा xfrm_state *x,
				    अचिन्हित पूर्णांक family)
अणु
	bool tunnel = false;

	चयन(family) अणु
	हाल AF_INET:
		अगर (XFRM_TUNNEL_SKB_CB(skb)->tunnel.ip4)
			tunnel = true;
		अवरोध;
	हाल AF_INET6:
		अगर (XFRM_TUNNEL_SKB_CB(skb)->tunnel.ip6)
			tunnel = true;
		अवरोध;
	पूर्ण
	अगर (tunnel && !(x->outer_mode.flags & XFRM_MODE_FLAG_TUNNEL))
		वापस -EINVAL;

	वापस 0;
पूर्ण

बाह्य स्थिर पूर्णांक xfrm_msg_min[XFRM_NR_MSGTYPES];
बाह्य स्थिर काष्ठा nla_policy xfrma_policy[XFRMA_MAX+1];

काष्ठा xfrm_translator अणु
	/* Allocate frag_list and put compat translation there */
	पूर्णांक (*alloc_compat)(काष्ठा sk_buff *skb, स्थिर काष्ठा nlmsghdr *src);

	/* Allocate nlmsg with 64-bit translaton of received 32-bit message */
	काष्ठा nlmsghdr *(*rcv_msg_compat)(स्थिर काष्ठा nlmsghdr *nlh,
			पूर्णांक maxtype, स्थिर काष्ठा nla_policy *policy,
			काष्ठा netlink_ext_ack *extack);

	/* Translate 32-bit user_policy from sockptr */
	पूर्णांक (*xlate_user_policy_sockptr)(u8 **pdata32, पूर्णांक optlen);

	काष्ठा module *owner;
पूर्ण;

#अगर IS_ENABLED(CONFIG_XFRM_USER_COMPAT)
बाह्य पूर्णांक xfrm_रेजिस्टर_translator(काष्ठा xfrm_translator *xtr);
बाह्य पूर्णांक xfrm_unरेजिस्टर_translator(काष्ठा xfrm_translator *xtr);
बाह्य काष्ठा xfrm_translator *xfrm_get_translator(व्योम);
बाह्य व्योम xfrm_put_translator(काष्ठा xfrm_translator *xtr);
#अन्यथा
अटल अंतरभूत काष्ठा xfrm_translator *xfrm_get_translator(व्योम)
अणु
	वापस शून्य;
पूर्ण
अटल अंतरभूत व्योम xfrm_put_translator(काष्ठा xfrm_translator *xtr)
अणु
पूर्ण
#पूर्ण_अगर

#अगर IS_ENABLED(CONFIG_IPV6)
अटल अंतरभूत bool xfrm6_local_करोntfrag(स्थिर काष्ठा sock *sk)
अणु
	पूर्णांक proto;

	अगर (!sk || sk->sk_family != AF_INET6)
		वापस false;

	proto = sk->sk_protocol;
	अगर (proto == IPPROTO_UDP || proto == IPPROTO_RAW)
		वापस inet6_sk(sk)->करोntfrag;

	वापस false;
पूर्ण
#पूर्ण_अगर
#पूर्ण_अगर	/* _NET_XFRM_H */
