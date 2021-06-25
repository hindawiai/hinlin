<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/* Copyright (C) 2000-2002 Joakim Axelsson <gozem@linux.nu>
 *                         Patrick Schaaf <bof@bof.de>
 *                         Martin Josefsson <gandalf@wlug.westbo.se>
 * Copyright (C) 2003-2013 Jozsef Kadlecsik <kadlec@netfilter.org>
 */
#अगर_अघोषित _IP_SET_H
#घोषणा _IP_SET_H

#समावेश <linux/ip.h>
#समावेश <linux/ipv6.h>
#समावेश <linux/netlink.h>
#समावेश <linux/netfilter.h>
#समावेश <linux/netfilter/x_tables.h>
#समावेश <linux/stringअगरy.h>
#समावेश <linux/vदो_स्मृति.h>
#समावेश <net/netlink.h>
#समावेश <uapi/linux/netfilter/ipset/ip_set.h>

#घोषणा _IP_SET_MODULE_DESC(a, b, c)		\
	MODULE_DESCRIPTION(a " type of IP sets, revisions " b "-" c)
#घोषणा IP_SET_MODULE_DESC(a, b, c)		\
	_IP_SET_MODULE_DESC(a, __stringअगरy(b), __stringअगरy(c))

/* Set features */
क्रमागत ip_set_feature अणु
	IPSET_TYPE_IP_FLAG = 0,
	IPSET_TYPE_IP = (1 << IPSET_TYPE_IP_FLAG),
	IPSET_TYPE_PORT_FLAG = 1,
	IPSET_TYPE_PORT = (1 << IPSET_TYPE_PORT_FLAG),
	IPSET_TYPE_MAC_FLAG = 2,
	IPSET_TYPE_MAC = (1 << IPSET_TYPE_MAC_FLAG),
	IPSET_TYPE_IP2_FLAG = 3,
	IPSET_TYPE_IP2 = (1 << IPSET_TYPE_IP2_FLAG),
	IPSET_TYPE_NAME_FLAG = 4,
	IPSET_TYPE_NAME = (1 << IPSET_TYPE_NAME_FLAG),
	IPSET_TYPE_IFACE_FLAG = 5,
	IPSET_TYPE_IFACE = (1 << IPSET_TYPE_IFACE_FLAG),
	IPSET_TYPE_MARK_FLAG = 6,
	IPSET_TYPE_MARK = (1 << IPSET_TYPE_MARK_FLAG),
	IPSET_TYPE_NOMATCH_FLAG = 7,
	IPSET_TYPE_NOMATCH = (1 << IPSET_TYPE_NOMATCH_FLAG),
	/* Strictly speaking not a feature, but a flag क्रम dumping:
	 * this settype must be dumped last */
	IPSET_DUMP_LAST_FLAG = 8,
	IPSET_DUMP_LAST = (1 << IPSET_DUMP_LAST_FLAG),
पूर्ण;

/* Set extensions */
क्रमागत ip_set_extension अणु
	IPSET_EXT_BIT_TIMEOUT = 0,
	IPSET_EXT_TIMEOUT = (1 << IPSET_EXT_BIT_TIMEOUT),
	IPSET_EXT_BIT_COUNTER = 1,
	IPSET_EXT_COUNTER = (1 << IPSET_EXT_BIT_COUNTER),
	IPSET_EXT_BIT_COMMENT = 2,
	IPSET_EXT_COMMENT = (1 << IPSET_EXT_BIT_COMMENT),
	IPSET_EXT_BIT_SKBINFO = 3,
	IPSET_EXT_SKBINFO = (1 << IPSET_EXT_BIT_SKBINFO),
	/* Mark set with an extension which needs to call destroy */
	IPSET_EXT_BIT_DESTROY = 7,
	IPSET_EXT_DESTROY = (1 << IPSET_EXT_BIT_DESTROY),
पूर्ण;

#घोषणा SET_WITH_TIMEOUT(s)	((s)->extensions & IPSET_EXT_TIMEOUT)
#घोषणा SET_WITH_COUNTER(s)	((s)->extensions & IPSET_EXT_COUNTER)
#घोषणा SET_WITH_COMMENT(s)	((s)->extensions & IPSET_EXT_COMMENT)
#घोषणा SET_WITH_SKBINFO(s)	((s)->extensions & IPSET_EXT_SKBINFO)
#घोषणा SET_WITH_FORCEADD(s)	((s)->flags & IPSET_CREATE_FLAG_FORCEADD)

/* Extension id, in size order */
क्रमागत ip_set_ext_id अणु
	IPSET_EXT_ID_COUNTER = 0,
	IPSET_EXT_ID_TIMEOUT,
	IPSET_EXT_ID_SKBINFO,
	IPSET_EXT_ID_COMMENT,
	IPSET_EXT_ID_MAX,
पूर्ण;

काष्ठा ip_set;

/* Extension type */
काष्ठा ip_set_ext_type अणु
	/* Destroy extension निजी data (can be शून्य) */
	व्योम (*destroy)(काष्ठा ip_set *set, व्योम *ext);
	क्रमागत ip_set_extension type;
	क्रमागत ipset_cadt_flags flag;
	/* Size and minimal alignment */
	u8 len;
	u8 align;
पूर्ण;

बाह्य स्थिर काष्ठा ip_set_ext_type ip_set_extensions[];

काष्ठा ip_set_counter अणु
	atomic64_t bytes;
	atomic64_t packets;
पूर्ण;

काष्ठा ip_set_comment_rcu अणु
	काष्ठा rcu_head rcu;
	अक्षर str[];
पूर्ण;

काष्ठा ip_set_comment अणु
	काष्ठा ip_set_comment_rcu __rcu *c;
पूर्ण;

काष्ठा ip_set_skbinfo अणु
	u32 skbmark;
	u32 skbmarkmask;
	u32 skbprio;
	u16 skbqueue;
	u16 __pad;
पूर्ण;

काष्ठा ip_set_ext अणु
	काष्ठा ip_set_skbinfo skbinfo;
	u64 packets;
	u64 bytes;
	अक्षर *comment;
	u32 समयout;
	u8 packets_op;
	u8 bytes_op;
	bool target;
पूर्ण;

#घोषणा ext_समयout(e, s)	\
((अचिन्हित दीर्घ *)(((व्योम *)(e)) + (s)->offset[IPSET_EXT_ID_TIMEOUT]))
#घोषणा ext_counter(e, s)	\
((काष्ठा ip_set_counter *)(((व्योम *)(e)) + (s)->offset[IPSET_EXT_ID_COUNTER]))
#घोषणा ext_comment(e, s)	\
((काष्ठा ip_set_comment *)(((व्योम *)(e)) + (s)->offset[IPSET_EXT_ID_COMMENT]))
#घोषणा ext_skbinfo(e, s)	\
((काष्ठा ip_set_skbinfo *)(((व्योम *)(e)) + (s)->offset[IPSET_EXT_ID_SKBINFO]))

प्रकार पूर्णांक (*ipset_adtfn)(काष्ठा ip_set *set, व्योम *value,
			   स्थिर काष्ठा ip_set_ext *ext,
			   काष्ठा ip_set_ext *mext, u32 cmdflags);

/* Kernel API function options */
काष्ठा ip_set_adt_opt अणु
	u8 family;		/* Actual protocol family */
	u8 dim;			/* Dimension of match/target */
	u8 flags;		/* Direction and negation flags */
	u32 cmdflags;		/* Command-like flags */
	काष्ठा ip_set_ext ext;	/* Extensions */
पूर्ण;

/* Set type, variant-specअगरic part */
काष्ठा ip_set_type_variant अणु
	/* Kernelspace: test/add/del entries
	 *		वापसs negative error code,
	 *			zero क्रम no match/success to add/delete
	 *			positive क्रम matching element */
	पूर्णांक (*kadt)(काष्ठा ip_set *set, स्थिर काष्ठा sk_buff *skb,
		    स्थिर काष्ठा xt_action_param *par,
		    क्रमागत ipset_adt adt, काष्ठा ip_set_adt_opt *opt);

	/* Userspace: test/add/del entries
	 *		वापसs negative error code,
	 *			zero क्रम no match/success to add/delete
	 *			positive क्रम matching element */
	पूर्णांक (*uadt)(काष्ठा ip_set *set, काष्ठा nlattr *tb[],
		    क्रमागत ipset_adt adt, u32 *lineno, u32 flags, bool retried);

	/* Low level add/del/test functions */
	ipset_adtfn adt[IPSET_ADT_MAX];

	/* When adding entries and set is full, try to resize the set */
	पूर्णांक (*resize)(काष्ठा ip_set *set, bool retried);
	/* Destroy the set */
	व्योम (*destroy)(काष्ठा ip_set *set);
	/* Flush the elements */
	व्योम (*flush)(काष्ठा ip_set *set);
	/* Expire entries beक्रमe listing */
	व्योम (*expire)(काष्ठा ip_set *set);
	/* List set header data */
	पूर्णांक (*head)(काष्ठा ip_set *set, काष्ठा sk_buff *skb);
	/* List elements */
	पूर्णांक (*list)(स्थिर काष्ठा ip_set *set, काष्ठा sk_buff *skb,
		    काष्ठा netlink_callback *cb);
	/* Keep listing निजी when resizing runs parallel */
	व्योम (*uref)(काष्ठा ip_set *set, काष्ठा netlink_callback *cb,
		     bool start);

	/* Return true अगर "b" set is the same as "a"
	 * according to the create set parameters */
	bool (*same_set)(स्थिर काष्ठा ip_set *a, स्थिर काष्ठा ip_set *b);
	/* Region-locking is used */
	bool region_lock;
पूर्ण;

काष्ठा ip_set_region अणु
	spinlock_t lock;	/* Region lock */
	माप_प्रकार ext_size;	/* Size of the dynamic extensions */
	u32 elements;		/* Number of elements vs समयout */
पूर्ण;

/* The max revision number supported by any set type + 1 */
#घोषणा IPSET_REVISION_MAX	9

/* The core set type काष्ठाure */
काष्ठा ip_set_type अणु
	काष्ठा list_head list;

	/* Typename */
	अक्षर name[IPSET_MAXNAMELEN];
	/* Protocol version */
	u8 protocol;
	/* Set type dimension */
	u8 dimension;
	/*
	 * Supported family: may be NFPROTO_UNSPEC क्रम both
	 * NFPROTO_IPV4/NFPROTO_IPV6.
	 */
	u8 family;
	/* Type revisions */
	u8 revision_min, revision_max;
	/* Revision-specअगरic supported (create) flags */
	u8 create_flags[IPSET_REVISION_MAX+1];
	/* Set features to control swapping */
	u16 features;

	/* Create set */
	पूर्णांक (*create)(काष्ठा net *net, काष्ठा ip_set *set,
		      काष्ठा nlattr *tb[], u32 flags);

	/* Attribute policies */
	स्थिर काष्ठा nla_policy create_policy[IPSET_ATTR_CREATE_MAX + 1];
	स्थिर काष्ठा nla_policy adt_policy[IPSET_ATTR_ADT_MAX + 1];

	/* Set this to THIS_MODULE अगर you are a module, otherwise शून्य */
	काष्ठा module *me;
पूर्ण;

/* रेजिस्टर and unरेजिस्टर set type */
बाह्य पूर्णांक ip_set_type_रेजिस्टर(काष्ठा ip_set_type *set_type);
बाह्य व्योम ip_set_type_unरेजिस्टर(काष्ठा ip_set_type *set_type);

/* A generic IP set */
काष्ठा ip_set अणु
	/* The name of the set */
	अक्षर name[IPSET_MAXNAMELEN];
	/* Lock protecting the set data */
	spinlock_t lock;
	/* References to the set */
	u32 ref;
	/* References to the set क्रम netlink events like dump,
	 * ref can be swapped out by ip_set_swap
	 */
	u32 ref_netlink;
	/* The core set type */
	काष्ठा ip_set_type *type;
	/* The type variant करोing the real job */
	स्थिर काष्ठा ip_set_type_variant *variant;
	/* The actual INET family of the set */
	u8 family;
	/* The type revision */
	u8 revision;
	/* Extensions */
	u8 extensions;
	/* Create flags */
	u8 flags;
	/* Default समयout value, अगर enabled */
	u32 समयout;
	/* Number of elements (vs समयout) */
	u32 elements;
	/* Size of the dynamic extensions (vs समयout) */
	माप_प्रकार ext_size;
	/* Element data size */
	माप_प्रकार dsize;
	/* Offsets to extensions in elements */
	माप_प्रकार offset[IPSET_EXT_ID_MAX];
	/* The type specअगरic data */
	व्योम *data;
पूर्ण;

अटल अंतरभूत व्योम
ip_set_ext_destroy(काष्ठा ip_set *set, व्योम *data)
अणु
	/* Check that the extension is enabled क्रम the set and
	 * call it's destroy function क्रम its extension part in data.
	 */
	अगर (SET_WITH_COMMENT(set)) अणु
		काष्ठा ip_set_comment *c = ext_comment(data, set);

		ip_set_extensions[IPSET_EXT_ID_COMMENT].destroy(set, c);
	पूर्ण
पूर्ण

पूर्णांक ip_set_put_flags(काष्ठा sk_buff *skb, काष्ठा ip_set *set);

/* Netlink CB args */
क्रमागत अणु
	IPSET_CB_NET = 0,	/* net namespace */
	IPSET_CB_PROTO,		/* ipset protocol */
	IPSET_CB_DUMP,		/* dump single set/all sets */
	IPSET_CB_INDEX,		/* set index */
	IPSET_CB_PRIVATE,	/* set निजी data */
	IPSET_CB_ARG0,		/* type specअगरic */
पूर्ण;

/* रेजिस्टर and unरेजिस्टर set references */
बाह्य ip_set_id_t ip_set_get_byname(काष्ठा net *net,
				     स्थिर अक्षर *name, काष्ठा ip_set **set);
बाह्य व्योम ip_set_put_byindex(काष्ठा net *net, ip_set_id_t index);
बाह्य व्योम ip_set_name_byindex(काष्ठा net *net, ip_set_id_t index, अक्षर *name);
बाह्य ip_set_id_t ip_set_nfnl_get_byindex(काष्ठा net *net, ip_set_id_t index);
बाह्य व्योम ip_set_nfnl_put(काष्ठा net *net, ip_set_id_t index);

/* API क्रम iptables set match, and SET target */

बाह्य पूर्णांक ip_set_add(ip_set_id_t id, स्थिर काष्ठा sk_buff *skb,
		      स्थिर काष्ठा xt_action_param *par,
		      काष्ठा ip_set_adt_opt *opt);
बाह्य पूर्णांक ip_set_del(ip_set_id_t id, स्थिर काष्ठा sk_buff *skb,
		      स्थिर काष्ठा xt_action_param *par,
		      काष्ठा ip_set_adt_opt *opt);
बाह्य पूर्णांक ip_set_test(ip_set_id_t id, स्थिर काष्ठा sk_buff *skb,
		       स्थिर काष्ठा xt_action_param *par,
		       काष्ठा ip_set_adt_opt *opt);

/* Utility functions */
बाह्य व्योम *ip_set_alloc(माप_प्रकार size);
बाह्य व्योम ip_set_मुक्त(व्योम *members);
बाह्य पूर्णांक ip_set_get_ipaddr4(काष्ठा nlattr *nla,  __be32 *ipaddr);
बाह्य पूर्णांक ip_set_get_ipaddr6(काष्ठा nlattr *nla, जोड़ nf_inet_addr *ipaddr);
बाह्य माप_प्रकार ip_set_elem_len(काष्ठा ip_set *set, काष्ठा nlattr *tb[],
			      माप_प्रकार len, माप_प्रकार align);
बाह्य पूर्णांक ip_set_get_extensions(काष्ठा ip_set *set, काष्ठा nlattr *tb[],
				 काष्ठा ip_set_ext *ext);
बाह्य पूर्णांक ip_set_put_extensions(काष्ठा sk_buff *skb, स्थिर काष्ठा ip_set *set,
				 स्थिर व्योम *e, bool active);
बाह्य bool ip_set_match_extensions(काष्ठा ip_set *set,
				    स्थिर काष्ठा ip_set_ext *ext,
				    काष्ठा ip_set_ext *mext,
				    u32 flags, व्योम *data);

अटल अंतरभूत पूर्णांक
ip_set_get_hostipaddr4(काष्ठा nlattr *nla, u32 *ipaddr)
अणु
	__be32 ip;
	पूर्णांक ret = ip_set_get_ipaddr4(nla, &ip);

	अगर (ret)
		वापस ret;
	*ipaddr = ntohl(ip);
	वापस 0;
पूर्ण

/* Ignore IPSET_ERR_EXIST errors अगर asked to करो so? */
अटल अंतरभूत bool
ip_set_eexist(पूर्णांक ret, u32 flags)
अणु
	वापस ret == -IPSET_ERR_EXIST && (flags & IPSET_FLAG_EXIST);
पूर्ण

/* Match elements marked with nomatch */
अटल अंतरभूत bool
ip_set_enomatch(पूर्णांक ret, u32 flags, क्रमागत ipset_adt adt, काष्ठा ip_set *set)
अणु
	वापस adt == IPSET_TEST &&
	       (set->type->features & IPSET_TYPE_NOMATCH) &&
	       ((flags >> 16) & IPSET_FLAG_NOMATCH) &&
	       (ret > 0 || ret == -ENOTEMPTY);
पूर्ण

/* Check the NLA_F_NET_BYTEORDER flag */
अटल अंतरभूत bool
ip_set_attr_netorder(काष्ठा nlattr *tb[], पूर्णांक type)
अणु
	वापस tb[type] && (tb[type]->nla_type & NLA_F_NET_BYTEORDER);
पूर्ण

अटल अंतरभूत bool
ip_set_optattr_netorder(काष्ठा nlattr *tb[], पूर्णांक type)
अणु
	वापस !tb[type] || (tb[type]->nla_type & NLA_F_NET_BYTEORDER);
पूर्ण

/* Useful converters */
अटल अंतरभूत u32
ip_set_get_h32(स्थिर काष्ठा nlattr *attr)
अणु
	वापस ntohl(nla_get_be32(attr));
पूर्ण

अटल अंतरभूत u16
ip_set_get_h16(स्थिर काष्ठा nlattr *attr)
अणु
	वापस ntohs(nla_get_be16(attr));
पूर्ण

अटल अंतरभूत पूर्णांक nla_put_ipaddr4(काष्ठा sk_buff *skb, पूर्णांक type, __be32 ipaddr)
अणु
	काष्ठा nlattr *__nested = nla_nest_start(skb, type);
	पूर्णांक ret;

	अगर (!__nested)
		वापस -EMSGSIZE;
	ret = nla_put_in_addr(skb, IPSET_ATTR_IPADDR_IPV4, ipaddr);
	अगर (!ret)
		nla_nest_end(skb, __nested);
	वापस ret;
पूर्ण

अटल अंतरभूत पूर्णांक nla_put_ipaddr6(काष्ठा sk_buff *skb, पूर्णांक type,
				  स्थिर काष्ठा in6_addr *ipaddrptr)
अणु
	काष्ठा nlattr *__nested = nla_nest_start(skb, type);
	पूर्णांक ret;

	अगर (!__nested)
		वापस -EMSGSIZE;
	ret = nla_put_in6_addr(skb, IPSET_ATTR_IPADDR_IPV6, ipaddrptr);
	अगर (!ret)
		nla_nest_end(skb, __nested);
	वापस ret;
पूर्ण

/* Get address from skbuff */
अटल अंतरभूत __be32
ip4addr(स्थिर काष्ठा sk_buff *skb, bool src)
अणु
	वापस src ? ip_hdr(skb)->saddr : ip_hdr(skb)->daddr;
पूर्ण

अटल अंतरभूत व्योम
ip4addrptr(स्थिर काष्ठा sk_buff *skb, bool src, __be32 *addr)
अणु
	*addr = src ? ip_hdr(skb)->saddr : ip_hdr(skb)->daddr;
पूर्ण

अटल अंतरभूत व्योम
ip6addrptr(स्थिर काष्ठा sk_buff *skb, bool src, काष्ठा in6_addr *addr)
अणु
	स_नकल(addr, src ? &ipv6_hdr(skb)->saddr : &ipv6_hdr(skb)->daddr,
	       माप(*addr));
पूर्ण

/* How often should the gc be run by शेष */
#घोषणा IPSET_GC_TIME			(3 * 60)

/* Timeout period depending on the समयout value of the given set */
#घोषणा IPSET_GC_PERIOD(समयout) \
	((समयout/3) ? min_t(u32, (समयout)/3, IPSET_GC_TIME) : 1)

/* Entry is set with no समयout value */
#घोषणा IPSET_ELEM_PERMANENT	0

/* Set is defined with समयout support: समयout value may be 0 */
#घोषणा IPSET_NO_TIMEOUT	अच_पूर्णांक_उच्च

/* Max समयout value, see msecs_to_jअगरfies() in jअगरfies.h */
#घोषणा IPSET_MAX_TIMEOUT	(अच_पूर्णांक_उच्च >> 1)/MSEC_PER_SEC

#घोषणा ip_set_adt_opt_समयout(opt, set)	\
((opt)->ext.समयout != IPSET_NO_TIMEOUT ? (opt)->ext.समयout : (set)->समयout)

अटल अंतरभूत अचिन्हित पूर्णांक
ip_set_समयout_uget(काष्ठा nlattr *tb)
अणु
	अचिन्हित पूर्णांक समयout = ip_set_get_h32(tb);

	/* Normalize to fit पूर्णांकo jअगरfies */
	अगर (समयout > IPSET_MAX_TIMEOUT)
		समयout = IPSET_MAX_TIMEOUT;

	वापस समयout;
पूर्ण

अटल अंतरभूत bool
ip_set_समयout_expired(स्थिर अचिन्हित दीर्घ *t)
अणु
	वापस *t != IPSET_ELEM_PERMANENT && समय_is_beक्रमe_jअगरfies(*t);
पूर्ण

अटल अंतरभूत व्योम
ip_set_समयout_set(अचिन्हित दीर्घ *समयout, u32 value)
अणु
	अचिन्हित दीर्घ t;

	अगर (!value) अणु
		*समयout = IPSET_ELEM_PERMANENT;
		वापस;
	पूर्ण

	t = msecs_to_jअगरfies(value * MSEC_PER_SEC) + jअगरfies;
	अगर (t == IPSET_ELEM_PERMANENT)
		/* Bingo! :-) */
		t--;
	*समयout = t;
पूर्ण

व्योम ip_set_init_comment(काष्ठा ip_set *set, काष्ठा ip_set_comment *comment,
			 स्थिर काष्ठा ip_set_ext *ext);

अटल अंतरभूत व्योम
ip_set_init_counter(काष्ठा ip_set_counter *counter,
		    स्थिर काष्ठा ip_set_ext *ext)
अणु
	अगर (ext->bytes != ULदीर्घ_उच्च)
		atomic64_set(&(counter)->bytes, (दीर्घ दीर्घ)(ext->bytes));
	अगर (ext->packets != ULदीर्घ_उच्च)
		atomic64_set(&(counter)->packets, (दीर्घ दीर्घ)(ext->packets));
पूर्ण

अटल अंतरभूत व्योम
ip_set_init_skbinfo(काष्ठा ip_set_skbinfo *skbinfo,
		    स्थिर काष्ठा ip_set_ext *ext)
अणु
	*skbinfo = ext->skbinfo;
पूर्ण

#घोषणा IP_SET_INIT_KEXT(skb, opt, set)			\
	अणु .bytes = (skb)->len, .packets = 1, .target = true,\
	  .समयout = ip_set_adt_opt_समयout(opt, set) पूर्ण

#घोषणा IP_SET_INIT_UEXT(set)				\
	अणु .bytes = ULदीर्घ_उच्च, .packets = ULदीर्घ_उच्च,	\
	  .समयout = (set)->समयout पूर्ण

#घोषणा IPSET_CONCAT(a, b)		a##b
#घोषणा IPSET_TOKEN(a, b)		IPSET_CONCAT(a, b)

#पूर्ण_अगर /*_IP_SET_H */
