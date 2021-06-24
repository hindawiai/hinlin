<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित __NET_FIB_RULES_H
#घोषणा __NET_FIB_RULES_H

#समावेश <linux/types.h>
#समावेश <linux/slab.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/fib_rules.h>
#समावेश <linux/refcount.h>
#समावेश <net/flow.h>
#समावेश <net/rtnetlink.h>
#समावेश <net/fib_notअगरier.h>
#समावेश <linux/indirect_call_wrapper.h>

काष्ठा fib_kuid_range अणु
	kuid_t start;
	kuid_t end;
पूर्ण;

काष्ठा fib_rule अणु
	काष्ठा list_head	list;
	पूर्णांक			iअगरindex;
	पूर्णांक			oअगरindex;
	u32			mark;
	u32			mark_mask;
	u32			flags;
	u32			table;
	u8			action;
	u8			l3mdev;
	u8                      proto;
	u8			ip_proto;
	u32			target;
	__be64			tun_id;
	काष्ठा fib_rule __rcu	*ctarget;
	काष्ठा net		*fr_net;

	refcount_t		refcnt;
	u32			pref;
	पूर्णांक			suppress_अगरgroup;
	पूर्णांक			suppress_prefixlen;
	अक्षर			iअगरname[IFNAMSIZ];
	अक्षर			oअगरname[IFNAMSIZ];
	काष्ठा fib_kuid_range	uid_range;
	काष्ठा fib_rule_port_range	sport_range;
	काष्ठा fib_rule_port_range	dport_range;
	काष्ठा rcu_head		rcu;
पूर्ण;

काष्ठा fib_lookup_arg अणु
	व्योम			*lookup_ptr;
	स्थिर व्योम		*lookup_data;
	व्योम			*result;
	काष्ठा fib_rule		*rule;
	u32			table;
	पूर्णांक			flags;
#घोषणा FIB_LOOKUP_NOREF		1
#घोषणा FIB_LOOKUP_IGNORE_LINKSTATE	2
पूर्ण;

काष्ठा fib_rules_ops अणु
	पूर्णांक			family;
	काष्ठा list_head	list;
	पूर्णांक			rule_size;
	पूर्णांक			addr_size;
	पूर्णांक			unresolved_rules;
	पूर्णांक			nr_जाओ_rules;
	अचिन्हित पूर्णांक		fib_rules_seq;

	पूर्णांक			(*action)(काष्ठा fib_rule *,
					  काष्ठा flowi *, पूर्णांक,
					  काष्ठा fib_lookup_arg *);
	bool			(*suppress)(काष्ठा fib_rule *,
					    काष्ठा fib_lookup_arg *);
	पूर्णांक			(*match)(काष्ठा fib_rule *,
					 काष्ठा flowi *, पूर्णांक);
	पूर्णांक			(*configure)(काष्ठा fib_rule *,
					     काष्ठा sk_buff *,
					     काष्ठा fib_rule_hdr *,
					     काष्ठा nlattr **,
					     काष्ठा netlink_ext_ack *);
	पूर्णांक			(*delete)(काष्ठा fib_rule *);
	पूर्णांक			(*compare)(काष्ठा fib_rule *,
					   काष्ठा fib_rule_hdr *,
					   काष्ठा nlattr **);
	पूर्णांक			(*fill)(काष्ठा fib_rule *, काष्ठा sk_buff *,
					काष्ठा fib_rule_hdr *);
	माप_प्रकार			(*nlmsg_payload)(काष्ठा fib_rule *);

	/* Called after modअगरications to the rules set, must flush
	 * the route cache अगर one exists. */
	व्योम			(*flush_cache)(काष्ठा fib_rules_ops *ops);

	पूर्णांक			nlgroup;
	स्थिर काष्ठा nla_policy	*policy;
	काष्ठा list_head	rules_list;
	काष्ठा module		*owner;
	काष्ठा net		*fro_net;
	काष्ठा rcu_head		rcu;
पूर्ण;

काष्ठा fib_rule_notअगरier_info अणु
	काष्ठा fib_notअगरier_info info; /* must be first */
	काष्ठा fib_rule *rule;
पूर्ण;

#घोषणा FRA_GENERIC_POLICY \
	[FRA_UNSPEC]	= अणु .strict_start_type = FRA_DPORT_RANGE + 1 पूर्ण, \
	[FRA_IIFNAME]	= अणु .type = NLA_STRING, .len = IFNAMSIZ - 1 पूर्ण, \
	[FRA_OIFNAME]	= अणु .type = NLA_STRING, .len = IFNAMSIZ - 1 पूर्ण, \
	[FRA_PRIORITY]	= अणु .type = NLA_U32 पूर्ण, \
	[FRA_FWMARK]	= अणु .type = NLA_U32 पूर्ण, \
	[FRA_TUN_ID]	= अणु .type = NLA_U64 पूर्ण, \
	[FRA_FWMASK]	= अणु .type = NLA_U32 पूर्ण, \
	[FRA_TABLE]     = अणु .type = NLA_U32 पूर्ण, \
	[FRA_SUPPRESS_PREFIXLEN] = अणु .type = NLA_U32 पूर्ण, \
	[FRA_SUPPRESS_IFGROUP] = अणु .type = NLA_U32 पूर्ण, \
	[FRA_GOTO]	= अणु .type = NLA_U32 पूर्ण, \
	[FRA_L3MDEV]	= अणु .type = NLA_U8 पूर्ण, \
	[FRA_UID_RANGE]	= अणु .len = माप(काष्ठा fib_rule_uid_range) पूर्ण, \
	[FRA_PROTOCOL]  = अणु .type = NLA_U8 पूर्ण, \
	[FRA_IP_PROTO]  = अणु .type = NLA_U8 पूर्ण, \
	[FRA_SPORT_RANGE] = अणु .len = माप(काष्ठा fib_rule_port_range) पूर्ण, \
	[FRA_DPORT_RANGE] = अणु .len = माप(काष्ठा fib_rule_port_range) पूर्ण


अटल अंतरभूत व्योम fib_rule_get(काष्ठा fib_rule *rule)
अणु
	refcount_inc(&rule->refcnt);
पूर्ण

अटल अंतरभूत व्योम fib_rule_put(काष्ठा fib_rule *rule)
अणु
	अगर (refcount_dec_and_test(&rule->refcnt))
		kमुक्त_rcu(rule, rcu);
पूर्ण

#अगर_घोषित CONFIG_NET_L3_MASTER_DEV
अटल अंतरभूत u32 fib_rule_get_table(काष्ठा fib_rule *rule,
				     काष्ठा fib_lookup_arg *arg)
अणु
	वापस rule->l3mdev ? arg->table : rule->table;
पूर्ण
#अन्यथा
अटल अंतरभूत u32 fib_rule_get_table(काष्ठा fib_rule *rule,
				     काष्ठा fib_lookup_arg *arg)
अणु
	वापस rule->table;
पूर्ण
#पूर्ण_अगर

अटल अंतरभूत u32 frh_get_table(काष्ठा fib_rule_hdr *frh, काष्ठा nlattr **nla)
अणु
	अगर (nla[FRA_TABLE])
		वापस nla_get_u32(nla[FRA_TABLE]);
	वापस frh->table;
पूर्ण

अटल अंतरभूत bool fib_rule_port_range_set(स्थिर काष्ठा fib_rule_port_range *range)
अणु
	वापस range->start != 0 && range->end != 0;
पूर्ण

अटल अंतरभूत bool fib_rule_port_inrange(स्थिर काष्ठा fib_rule_port_range *a,
					 __be16 port)
अणु
	वापस ntohs(port) >= a->start &&
		ntohs(port) <= a->end;
पूर्ण

अटल अंतरभूत bool fib_rule_port_range_valid(स्थिर काष्ठा fib_rule_port_range *a)
अणु
	वापस a->start != 0 && a->end != 0 && a->end < 0xffff &&
		a->start <= a->end;
पूर्ण

अटल अंतरभूत bool fib_rule_port_range_compare(काष्ठा fib_rule_port_range *a,
					       काष्ठा fib_rule_port_range *b)
अणु
	वापस a->start == b->start &&
		a->end == b->end;
पूर्ण

अटल अंतरभूत bool fib_rule_requires_fldissect(काष्ठा fib_rule *rule)
अणु
	वापस rule->iअगरindex != LOOPBACK_IFINDEX && (rule->ip_proto ||
		fib_rule_port_range_set(&rule->sport_range) ||
		fib_rule_port_range_set(&rule->dport_range));
पूर्ण

काष्ठा fib_rules_ops *fib_rules_रेजिस्टर(स्थिर काष्ठा fib_rules_ops *,
					 काष्ठा net *);
व्योम fib_rules_unरेजिस्टर(काष्ठा fib_rules_ops *);

पूर्णांक fib_rules_lookup(काष्ठा fib_rules_ops *, काष्ठा flowi *, पूर्णांक flags,
		     काष्ठा fib_lookup_arg *);
पूर्णांक fib_शेष_rule_add(काष्ठा fib_rules_ops *, u32 pref, u32 table,
			 u32 flags);
bool fib_rule_matchall(स्थिर काष्ठा fib_rule *rule);
पूर्णांक fib_rules_dump(काष्ठा net *net, काष्ठा notअगरier_block *nb, पूर्णांक family,
		   काष्ठा netlink_ext_ack *extack);
अचिन्हित पूर्णांक fib_rules_seq_पढ़ो(काष्ठा net *net, पूर्णांक family);

पूर्णांक fib_nl_newrule(काष्ठा sk_buff *skb, काष्ठा nlmsghdr *nlh,
		   काष्ठा netlink_ext_ack *extack);
पूर्णांक fib_nl_delrule(काष्ठा sk_buff *skb, काष्ठा nlmsghdr *nlh,
		   काष्ठा netlink_ext_ack *extack);

INसूचीECT_CALLABLE_DECLARE(पूर्णांक fib6_rule_match(काष्ठा fib_rule *rule,
					    काष्ठा flowi *fl, पूर्णांक flags));
INसूचीECT_CALLABLE_DECLARE(पूर्णांक fib4_rule_match(काष्ठा fib_rule *rule,
					    काष्ठा flowi *fl, पूर्णांक flags));

INसूचीECT_CALLABLE_DECLARE(पूर्णांक fib6_rule_action(काष्ठा fib_rule *rule,
			    काष्ठा flowi *flp, पूर्णांक flags,
			    काष्ठा fib_lookup_arg *arg));
INसूचीECT_CALLABLE_DECLARE(पूर्णांक fib4_rule_action(काष्ठा fib_rule *rule,
			    काष्ठा flowi *flp, पूर्णांक flags,
			    काष्ठा fib_lookup_arg *arg));

INसूचीECT_CALLABLE_DECLARE(bool fib6_rule_suppress(काष्ठा fib_rule *rule,
						काष्ठा fib_lookup_arg *arg));
INसूचीECT_CALLABLE_DECLARE(bool fib4_rule_suppress(काष्ठा fib_rule *rule,
						काष्ठा fib_lookup_arg *arg));
#पूर्ण_अगर
