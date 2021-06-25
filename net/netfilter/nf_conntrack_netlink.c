<शैली गुरु>
/* Connection tracking via netlink socket. Allows क्रम user space
 * protocol helpers and general trouble making from userspace.
 *
 * (C) 2001 by Jay Schulist <jschlst@samba.org>
 * (C) 2002-2006 by Harald Welte <laक्रमge@gnumonks.org>
 * (C) 2003 by Patrick Mअक्षरdy <kaber@trash.net>
 * (C) 2005-2012 by Pablo Neira Ayuso <pablo@netfilter.org>
 *
 * Initial connection tracking via netlink development funded and
 * generally made possible by Network Robots, Inc. (www.networkrobots.com)
 *
 * Further development of this code funded by Astaro AG (http://www.astaro.com)
 *
 * This software may be used and distributed according to the terms
 * of the GNU General Public License, incorporated herein by reference.
 */

#समावेश <linux/init.h>
#समावेश <linux/module.h>
#समावेश <linux/kernel.h>
#समावेश <linux/rculist.h>
#समावेश <linux/rculist_nulls.h>
#समावेश <linux/types.h>
#समावेश <linux/समयr.h>
#समावेश <linux/security.h>
#समावेश <linux/skbuff.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/netlink.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/slab.h>
#समावेश <linux/siphash.h>

#समावेश <linux/netfilter.h>
#समावेश <net/netlink.h>
#समावेश <net/sock.h>
#समावेश <net/netfilter/nf_conntrack.h>
#समावेश <net/netfilter/nf_conntrack_core.h>
#समावेश <net/netfilter/nf_conntrack_expect.h>
#समावेश <net/netfilter/nf_conntrack_helper.h>
#समावेश <net/netfilter/nf_conntrack_seqadj.h>
#समावेश <net/netfilter/nf_conntrack_l4proto.h>
#समावेश <net/netfilter/nf_conntrack_tuple.h>
#समावेश <net/netfilter/nf_conntrack_acct.h>
#समावेश <net/netfilter/nf_conntrack_zones.h>
#समावेश <net/netfilter/nf_conntrack_बारtamp.h>
#समावेश <net/netfilter/nf_conntrack_labels.h>
#समावेश <net/netfilter/nf_conntrack_synproxy.h>
#अगर IS_ENABLED(CONFIG_NF_NAT)
#समावेश <net/netfilter/nf_nat.h>
#समावेश <net/netfilter/nf_nat_helper.h>
#पूर्ण_अगर

#समावेश <linux/netfilter/nfnetlink.h>
#समावेश <linux/netfilter/nfnetlink_conntrack.h>

#समावेश "nf_internals.h"

MODULE_LICENSE("GPL");

अटल पूर्णांक ctnetlink_dump_tuples_proto(काष्ठा sk_buff *skb,
				स्थिर काष्ठा nf_conntrack_tuple *tuple,
				स्थिर काष्ठा nf_conntrack_l4proto *l4proto)
अणु
	पूर्णांक ret = 0;
	काष्ठा nlattr *nest_parms;

	nest_parms = nla_nest_start(skb, CTA_TUPLE_PROTO);
	अगर (!nest_parms)
		जाओ nla_put_failure;
	अगर (nla_put_u8(skb, CTA_PROTO_NUM, tuple->dst.protonum))
		जाओ nla_put_failure;

	अगर (likely(l4proto->tuple_to_nlattr))
		ret = l4proto->tuple_to_nlattr(skb, tuple);

	nla_nest_end(skb, nest_parms);

	वापस ret;

nla_put_failure:
	वापस -1;
पूर्ण

अटल पूर्णांक ipv4_tuple_to_nlattr(काष्ठा sk_buff *skb,
				स्थिर काष्ठा nf_conntrack_tuple *tuple)
अणु
	अगर (nla_put_in_addr(skb, CTA_IP_V4_SRC, tuple->src.u3.ip) ||
	    nla_put_in_addr(skb, CTA_IP_V4_DST, tuple->dst.u3.ip))
		वापस -EMSGSIZE;
	वापस 0;
पूर्ण

अटल पूर्णांक ipv6_tuple_to_nlattr(काष्ठा sk_buff *skb,
				स्थिर काष्ठा nf_conntrack_tuple *tuple)
अणु
	अगर (nla_put_in6_addr(skb, CTA_IP_V6_SRC, &tuple->src.u3.in6) ||
	    nla_put_in6_addr(skb, CTA_IP_V6_DST, &tuple->dst.u3.in6))
		वापस -EMSGSIZE;
	वापस 0;
पूर्ण

अटल पूर्णांक ctnetlink_dump_tuples_ip(काष्ठा sk_buff *skb,
				    स्थिर काष्ठा nf_conntrack_tuple *tuple)
अणु
	पूर्णांक ret = 0;
	काष्ठा nlattr *nest_parms;

	nest_parms = nla_nest_start(skb, CTA_TUPLE_IP);
	अगर (!nest_parms)
		जाओ nla_put_failure;

	चयन (tuple->src.l3num) अणु
	हाल NFPROTO_IPV4:
		ret = ipv4_tuple_to_nlattr(skb, tuple);
		अवरोध;
	हाल NFPROTO_IPV6:
		ret = ipv6_tuple_to_nlattr(skb, tuple);
		अवरोध;
	पूर्ण

	nla_nest_end(skb, nest_parms);

	वापस ret;

nla_put_failure:
	वापस -1;
पूर्ण

अटल पूर्णांक ctnetlink_dump_tuples(काष्ठा sk_buff *skb,
				 स्थिर काष्ठा nf_conntrack_tuple *tuple)
अणु
	स्थिर काष्ठा nf_conntrack_l4proto *l4proto;
	पूर्णांक ret;

	rcu_पढ़ो_lock();
	ret = ctnetlink_dump_tuples_ip(skb, tuple);

	अगर (ret >= 0) अणु
		l4proto = nf_ct_l4proto_find(tuple->dst.protonum);
		ret = ctnetlink_dump_tuples_proto(skb, tuple, l4proto);
	पूर्ण
	rcu_पढ़ो_unlock();
	वापस ret;
पूर्ण

अटल पूर्णांक ctnetlink_dump_zone_id(काष्ठा sk_buff *skb, पूर्णांक attrtype,
				  स्थिर काष्ठा nf_conntrack_zone *zone, पूर्णांक dir)
अणु
	अगर (zone->id == NF_CT_DEFAULT_ZONE_ID || zone->dir != dir)
		वापस 0;
	अगर (nla_put_be16(skb, attrtype, htons(zone->id)))
		जाओ nla_put_failure;
	वापस 0;

nla_put_failure:
	वापस -1;
पूर्ण

अटल पूर्णांक ctnetlink_dump_status(काष्ठा sk_buff *skb, स्थिर काष्ठा nf_conn *ct)
अणु
	अगर (nla_put_be32(skb, CTA_STATUS, htonl(ct->status)))
		जाओ nla_put_failure;
	वापस 0;

nla_put_failure:
	वापस -1;
पूर्ण

अटल पूर्णांक ctnetlink_dump_समयout(काष्ठा sk_buff *skb, स्थिर काष्ठा nf_conn *ct,
				  bool skip_zero)
अणु
	दीर्घ समयout = nf_ct_expires(ct) / HZ;

	अगर (skip_zero && समयout == 0)
		वापस 0;

	अगर (nla_put_be32(skb, CTA_TIMEOUT, htonl(समयout)))
		जाओ nla_put_failure;
	वापस 0;

nla_put_failure:
	वापस -1;
पूर्ण

अटल पूर्णांक ctnetlink_dump_protoinfo(काष्ठा sk_buff *skb, काष्ठा nf_conn *ct,
				    bool destroy)
अणु
	स्थिर काष्ठा nf_conntrack_l4proto *l4proto;
	काष्ठा nlattr *nest_proto;
	पूर्णांक ret;

	l4proto = nf_ct_l4proto_find(nf_ct_protonum(ct));
	अगर (!l4proto->to_nlattr)
		वापस 0;

	nest_proto = nla_nest_start(skb, CTA_PROTOINFO);
	अगर (!nest_proto)
		जाओ nla_put_failure;

	ret = l4proto->to_nlattr(skb, nest_proto, ct, destroy);

	nla_nest_end(skb, nest_proto);

	वापस ret;

nla_put_failure:
	वापस -1;
पूर्ण

अटल पूर्णांक ctnetlink_dump_helpinfo(काष्ठा sk_buff *skb,
				   स्थिर काष्ठा nf_conn *ct)
अणु
	काष्ठा nlattr *nest_helper;
	स्थिर काष्ठा nf_conn_help *help = nfct_help(ct);
	काष्ठा nf_conntrack_helper *helper;

	अगर (!help)
		वापस 0;

	helper = rcu_dereference(help->helper);
	अगर (!helper)
		जाओ out;

	nest_helper = nla_nest_start(skb, CTA_HELP);
	अगर (!nest_helper)
		जाओ nla_put_failure;
	अगर (nla_put_string(skb, CTA_HELP_NAME, helper->name))
		जाओ nla_put_failure;

	अगर (helper->to_nlattr)
		helper->to_nlattr(skb, ct);

	nla_nest_end(skb, nest_helper);
out:
	वापस 0;

nla_put_failure:
	वापस -1;
पूर्ण

अटल पूर्णांक
dump_counters(काष्ठा sk_buff *skb, काष्ठा nf_conn_acct *acct,
	      क्रमागत ip_conntrack_dir dir, पूर्णांक type)
अणु
	क्रमागत ctattr_type attr = dir ? CTA_COUNTERS_REPLY: CTA_COUNTERS_ORIG;
	काष्ठा nf_conn_counter *counter = acct->counter;
	काष्ठा nlattr *nest_count;
	u64 pkts, bytes;

	अगर (type == IPCTNL_MSG_CT_GET_CTRZERO) अणु
		pkts = atomic64_xchg(&counter[dir].packets, 0);
		bytes = atomic64_xchg(&counter[dir].bytes, 0);
	पूर्ण अन्यथा अणु
		pkts = atomic64_पढ़ो(&counter[dir].packets);
		bytes = atomic64_पढ़ो(&counter[dir].bytes);
	पूर्ण

	nest_count = nla_nest_start(skb, attr);
	अगर (!nest_count)
		जाओ nla_put_failure;

	अगर (nla_put_be64(skb, CTA_COUNTERS_PACKETS, cpu_to_be64(pkts),
			 CTA_COUNTERS_PAD) ||
	    nla_put_be64(skb, CTA_COUNTERS_BYTES, cpu_to_be64(bytes),
			 CTA_COUNTERS_PAD))
		जाओ nla_put_failure;

	nla_nest_end(skb, nest_count);

	वापस 0;

nla_put_failure:
	वापस -1;
पूर्ण

अटल पूर्णांक
ctnetlink_dump_acct(काष्ठा sk_buff *skb, स्थिर काष्ठा nf_conn *ct, पूर्णांक type)
अणु
	काष्ठा nf_conn_acct *acct = nf_conn_acct_find(ct);

	अगर (!acct)
		वापस 0;

	अगर (dump_counters(skb, acct, IP_CT_सूची_ORIGINAL, type) < 0)
		वापस -1;
	अगर (dump_counters(skb, acct, IP_CT_सूची_REPLY, type) < 0)
		वापस -1;

	वापस 0;
पूर्ण

अटल पूर्णांक
ctnetlink_dump_बारtamp(काष्ठा sk_buff *skb, स्थिर काष्ठा nf_conn *ct)
अणु
	काष्ठा nlattr *nest_count;
	स्थिर काष्ठा nf_conn_tstamp *tstamp;

	tstamp = nf_conn_tstamp_find(ct);
	अगर (!tstamp)
		वापस 0;

	nest_count = nla_nest_start(skb, CTA_TIMESTAMP);
	अगर (!nest_count)
		जाओ nla_put_failure;

	अगर (nla_put_be64(skb, CTA_TIMESTAMP_START, cpu_to_be64(tstamp->start),
			 CTA_TIMESTAMP_PAD) ||
	    (tstamp->stop != 0 && nla_put_be64(skb, CTA_TIMESTAMP_STOP,
					       cpu_to_be64(tstamp->stop),
					       CTA_TIMESTAMP_PAD)))
		जाओ nla_put_failure;
	nla_nest_end(skb, nest_count);

	वापस 0;

nla_put_failure:
	वापस -1;
पूर्ण

#अगर_घोषित CONFIG_NF_CONNTRACK_MARK
अटल पूर्णांक ctnetlink_dump_mark(काष्ठा sk_buff *skb, स्थिर काष्ठा nf_conn *ct)
अणु
	अगर (nla_put_be32(skb, CTA_MARK, htonl(ct->mark)))
		जाओ nla_put_failure;
	वापस 0;

nla_put_failure:
	वापस -1;
पूर्ण
#अन्यथा
#घोषणा ctnetlink_dump_mark(a, b) (0)
#पूर्ण_अगर

#अगर_घोषित CONFIG_NF_CONNTRACK_SECMARK
अटल पूर्णांक ctnetlink_dump_secctx(काष्ठा sk_buff *skb, स्थिर काष्ठा nf_conn *ct)
अणु
	काष्ठा nlattr *nest_secctx;
	पूर्णांक len, ret;
	अक्षर *secctx;

	ret = security_secid_to_secctx(ct->secmark, &secctx, &len);
	अगर (ret)
		वापस 0;

	ret = -1;
	nest_secctx = nla_nest_start(skb, CTA_SECCTX);
	अगर (!nest_secctx)
		जाओ nla_put_failure;

	अगर (nla_put_string(skb, CTA_SECCTX_NAME, secctx))
		जाओ nla_put_failure;
	nla_nest_end(skb, nest_secctx);

	ret = 0;
nla_put_failure:
	security_release_secctx(secctx, len);
	वापस ret;
पूर्ण
#अन्यथा
#घोषणा ctnetlink_dump_secctx(a, b) (0)
#पूर्ण_अगर

#अगर_घोषित CONFIG_NF_CONNTRACK_LABELS
अटल अंतरभूत पूर्णांक ctnetlink_label_size(स्थिर काष्ठा nf_conn *ct)
अणु
	काष्ठा nf_conn_labels *labels = nf_ct_labels_find(ct);

	अगर (!labels)
		वापस 0;
	वापस nla_total_size(माप(labels->bits));
पूर्ण

अटल पूर्णांक
ctnetlink_dump_labels(काष्ठा sk_buff *skb, स्थिर काष्ठा nf_conn *ct)
अणु
	काष्ठा nf_conn_labels *labels = nf_ct_labels_find(ct);
	अचिन्हित पूर्णांक i;

	अगर (!labels)
		वापस 0;

	i = 0;
	करो अणु
		अगर (labels->bits[i] != 0)
			वापस nla_put(skb, CTA_LABELS, माप(labels->bits),
				       labels->bits);
		i++;
	पूर्ण जबतक (i < ARRAY_SIZE(labels->bits));

	वापस 0;
पूर्ण
#अन्यथा
#घोषणा ctnetlink_dump_labels(a, b) (0)
#घोषणा ctnetlink_label_size(a)	(0)
#पूर्ण_अगर

#घोषणा master_tuple(ct) &(ct->master->tuplehash[IP_CT_सूची_ORIGINAL].tuple)

अटल पूर्णांक ctnetlink_dump_master(काष्ठा sk_buff *skb, स्थिर काष्ठा nf_conn *ct)
अणु
	काष्ठा nlattr *nest_parms;

	अगर (!(ct->status & IPS_EXPECTED))
		वापस 0;

	nest_parms = nla_nest_start(skb, CTA_TUPLE_MASTER);
	अगर (!nest_parms)
		जाओ nla_put_failure;
	अगर (ctnetlink_dump_tuples(skb, master_tuple(ct)) < 0)
		जाओ nla_put_failure;
	nla_nest_end(skb, nest_parms);

	वापस 0;

nla_put_failure:
	वापस -1;
पूर्ण

अटल पूर्णांक
dump_ct_seq_adj(काष्ठा sk_buff *skb, स्थिर काष्ठा nf_ct_seqadj *seq, पूर्णांक type)
अणु
	काष्ठा nlattr *nest_parms;

	nest_parms = nla_nest_start(skb, type);
	अगर (!nest_parms)
		जाओ nla_put_failure;

	अगर (nla_put_be32(skb, CTA_SEQADJ_CORRECTION_POS,
			 htonl(seq->correction_pos)) ||
	    nla_put_be32(skb, CTA_SEQADJ_OFFSET_BEFORE,
			 htonl(seq->offset_beक्रमe)) ||
	    nla_put_be32(skb, CTA_SEQADJ_OFFSET_AFTER,
			 htonl(seq->offset_after)))
		जाओ nla_put_failure;

	nla_nest_end(skb, nest_parms);

	वापस 0;

nla_put_failure:
	वापस -1;
पूर्ण

अटल पूर्णांक ctnetlink_dump_ct_seq_adj(काष्ठा sk_buff *skb, काष्ठा nf_conn *ct)
अणु
	काष्ठा nf_conn_seqadj *seqadj = nfct_seqadj(ct);
	काष्ठा nf_ct_seqadj *seq;

	अगर (!(ct->status & IPS_SEQ_ADJUST) || !seqadj)
		वापस 0;

	spin_lock_bh(&ct->lock);
	seq = &seqadj->seq[IP_CT_सूची_ORIGINAL];
	अगर (dump_ct_seq_adj(skb, seq, CTA_SEQ_ADJ_ORIG) == -1)
		जाओ err;

	seq = &seqadj->seq[IP_CT_सूची_REPLY];
	अगर (dump_ct_seq_adj(skb, seq, CTA_SEQ_ADJ_REPLY) == -1)
		जाओ err;

	spin_unlock_bh(&ct->lock);
	वापस 0;
err:
	spin_unlock_bh(&ct->lock);
	वापस -1;
पूर्ण

अटल पूर्णांक ctnetlink_dump_ct_synproxy(काष्ठा sk_buff *skb, काष्ठा nf_conn *ct)
अणु
	काष्ठा nf_conn_synproxy *synproxy = nfct_synproxy(ct);
	काष्ठा nlattr *nest_parms;

	अगर (!synproxy)
		वापस 0;

	nest_parms = nla_nest_start(skb, CTA_SYNPROXY);
	अगर (!nest_parms)
		जाओ nla_put_failure;

	अगर (nla_put_be32(skb, CTA_SYNPROXY_ISN, htonl(synproxy->isn)) ||
	    nla_put_be32(skb, CTA_SYNPROXY_ITS, htonl(synproxy->its)) ||
	    nla_put_be32(skb, CTA_SYNPROXY_TSOFF, htonl(synproxy->tsoff)))
		जाओ nla_put_failure;

	nla_nest_end(skb, nest_parms);

	वापस 0;

nla_put_failure:
	वापस -1;
पूर्ण

अटल पूर्णांक ctnetlink_dump_id(काष्ठा sk_buff *skb, स्थिर काष्ठा nf_conn *ct)
अणु
	__be32 id = (__क्रमce __be32)nf_ct_get_id(ct);

	अगर (nla_put_be32(skb, CTA_ID, id))
		जाओ nla_put_failure;
	वापस 0;

nla_put_failure:
	वापस -1;
पूर्ण

अटल पूर्णांक ctnetlink_dump_use(काष्ठा sk_buff *skb, स्थिर काष्ठा nf_conn *ct)
अणु
	अगर (nla_put_be32(skb, CTA_USE, htonl(atomic_पढ़ो(&ct->ct_general.use))))
		जाओ nla_put_failure;
	वापस 0;

nla_put_failure:
	वापस -1;
पूर्ण

/* all these functions access ct->ext. Caller must either hold a reference
 * on ct or prevent its deletion by holding either the bucket spinlock or
 * pcpu dying list lock.
 */
अटल पूर्णांक ctnetlink_dump_extinfo(काष्ठा sk_buff *skb,
				  काष्ठा nf_conn *ct, u32 type)
अणु
	अगर (ctnetlink_dump_acct(skb, ct, type) < 0 ||
	    ctnetlink_dump_बारtamp(skb, ct) < 0 ||
	    ctnetlink_dump_helpinfo(skb, ct) < 0 ||
	    ctnetlink_dump_labels(skb, ct) < 0 ||
	    ctnetlink_dump_ct_seq_adj(skb, ct) < 0 ||
	    ctnetlink_dump_ct_synproxy(skb, ct) < 0)
		वापस -1;

	वापस 0;
पूर्ण

अटल पूर्णांक ctnetlink_dump_info(काष्ठा sk_buff *skb, काष्ठा nf_conn *ct)
अणु
	अगर (ctnetlink_dump_status(skb, ct) < 0 ||
	    ctnetlink_dump_mark(skb, ct) < 0 ||
	    ctnetlink_dump_secctx(skb, ct) < 0 ||
	    ctnetlink_dump_id(skb, ct) < 0 ||
	    ctnetlink_dump_use(skb, ct) < 0 ||
	    ctnetlink_dump_master(skb, ct) < 0)
		वापस -1;

	अगर (!test_bit(IPS_OFFLOAD_BIT, &ct->status) &&
	    (ctnetlink_dump_समयout(skb, ct, false) < 0 ||
	     ctnetlink_dump_protoinfo(skb, ct, false) < 0))
		वापस -1;

	वापस 0;
पूर्ण

अटल पूर्णांक
ctnetlink_fill_info(काष्ठा sk_buff *skb, u32 portid, u32 seq, u32 type,
		    काष्ठा nf_conn *ct, bool extinfo, अचिन्हित पूर्णांक flags)
अणु
	स्थिर काष्ठा nf_conntrack_zone *zone;
	काष्ठा nlmsghdr *nlh;
	काष्ठा nlattr *nest_parms;
	अचिन्हित पूर्णांक event;

	अगर (portid)
		flags |= NLM_F_MULTI;
	event = nfnl_msg_type(NFNL_SUBSYS_CTNETLINK, IPCTNL_MSG_CT_NEW);
	nlh = nfnl_msg_put(skb, portid, seq, event, flags, nf_ct_l3num(ct),
			   NFNETLINK_V0, 0);
	अगर (!nlh)
		जाओ nlmsg_failure;

	zone = nf_ct_zone(ct);

	nest_parms = nla_nest_start(skb, CTA_TUPLE_ORIG);
	अगर (!nest_parms)
		जाओ nla_put_failure;
	अगर (ctnetlink_dump_tuples(skb, nf_ct_tuple(ct, IP_CT_सूची_ORIGINAL)) < 0)
		जाओ nla_put_failure;
	अगर (ctnetlink_dump_zone_id(skb, CTA_TUPLE_ZONE, zone,
				   NF_CT_ZONE_सूची_ORIG) < 0)
		जाओ nla_put_failure;
	nla_nest_end(skb, nest_parms);

	nest_parms = nla_nest_start(skb, CTA_TUPLE_REPLY);
	अगर (!nest_parms)
		जाओ nla_put_failure;
	अगर (ctnetlink_dump_tuples(skb, nf_ct_tuple(ct, IP_CT_सूची_REPLY)) < 0)
		जाओ nla_put_failure;
	अगर (ctnetlink_dump_zone_id(skb, CTA_TUPLE_ZONE, zone,
				   NF_CT_ZONE_सूची_REPL) < 0)
		जाओ nla_put_failure;
	nla_nest_end(skb, nest_parms);

	अगर (ctnetlink_dump_zone_id(skb, CTA_ZONE, zone,
				   NF_CT_DEFAULT_ZONE_सूची) < 0)
		जाओ nla_put_failure;

	अगर (ctnetlink_dump_info(skb, ct) < 0)
		जाओ nla_put_failure;
	अगर (extinfo && ctnetlink_dump_extinfo(skb, ct, type) < 0)
		जाओ nla_put_failure;

	nlmsg_end(skb, nlh);
	वापस skb->len;

nlmsg_failure:
nla_put_failure:
	nlmsg_cancel(skb, nlh);
	वापस -1;
पूर्ण

अटल स्थिर काष्ठा nla_policy cta_ip_nla_policy[CTA_IP_MAX + 1] = अणु
	[CTA_IP_V4_SRC]	= अणु .type = NLA_U32 पूर्ण,
	[CTA_IP_V4_DST]	= अणु .type = NLA_U32 पूर्ण,
	[CTA_IP_V6_SRC]	= अणु .len = माप(__be32) * 4 पूर्ण,
	[CTA_IP_V6_DST]	= अणु .len = माप(__be32) * 4 पूर्ण,
पूर्ण;

#अगर defined(CONFIG_NETFILTER_NETLINK_GLUE_CT) || defined(CONFIG_NF_CONNTRACK_EVENTS)
अटल माप_प्रकार ctnetlink_proto_size(स्थिर काष्ठा nf_conn *ct)
अणु
	स्थिर काष्ठा nf_conntrack_l4proto *l4proto;
	माप_प्रकार len, len4 = 0;

	len = nla_policy_len(cta_ip_nla_policy, CTA_IP_MAX + 1);
	len *= 3u; /* ORIG, REPLY, MASTER */

	l4proto = nf_ct_l4proto_find(nf_ct_protonum(ct));
	len += l4proto->nlattr_size;
	अगर (l4proto->nlattr_tuple_size) अणु
		len4 = l4proto->nlattr_tuple_size();
		len4 *= 3u; /* ORIG, REPLY, MASTER */
	पूर्ण

	वापस len + len4;
पूर्ण
#पूर्ण_अगर

अटल अंतरभूत माप_प्रकार ctnetlink_acct_size(स्थिर काष्ठा nf_conn *ct)
अणु
	अगर (!nf_ct_ext_exist(ct, NF_CT_EXT_ACCT))
		वापस 0;
	वापस 2 * nla_total_size(0) /* CTA_COUNTERS_ORIG|REPL */
	       + 2 * nla_total_size_64bit(माप(uपूर्णांक64_t)) /* CTA_COUNTERS_PACKETS */
	       + 2 * nla_total_size_64bit(माप(uपूर्णांक64_t)) /* CTA_COUNTERS_BYTES */
	       ;
पूर्ण

अटल अंतरभूत पूर्णांक ctnetlink_secctx_size(स्थिर काष्ठा nf_conn *ct)
अणु
#अगर_घोषित CONFIG_NF_CONNTRACK_SECMARK
	पूर्णांक len, ret;

	ret = security_secid_to_secctx(ct->secmark, शून्य, &len);
	अगर (ret)
		वापस 0;

	वापस nla_total_size(0) /* CTA_SECCTX */
	       + nla_total_size(माप(अक्षर) * len); /* CTA_SECCTX_NAME */
#अन्यथा
	वापस 0;
#पूर्ण_अगर
पूर्ण

अटल अंतरभूत माप_प्रकार ctnetlink_बारtamp_size(स्थिर काष्ठा nf_conn *ct)
अणु
#अगर_घोषित CONFIG_NF_CONNTRACK_TIMESTAMP
	अगर (!nf_ct_ext_exist(ct, NF_CT_EXT_TSTAMP))
		वापस 0;
	वापस nla_total_size(0) + 2 * nla_total_size_64bit(माप(uपूर्णांक64_t));
#अन्यथा
	वापस 0;
#पूर्ण_अगर
पूर्ण

#अगर_घोषित CONFIG_NF_CONNTRACK_EVENTS
अटल माप_प्रकार ctnetlink_nlmsg_size(स्थिर काष्ठा nf_conn *ct)
अणु
	वापस NLMSG_ALIGN(माप(काष्ठा nfgenmsg))
	       + 3 * nla_total_size(0) /* CTA_TUPLE_ORIG|REPL|MASTER */
	       + 3 * nla_total_size(0) /* CTA_TUPLE_IP */
	       + 3 * nla_total_size(0) /* CTA_TUPLE_PROTO */
	       + 3 * nla_total_size(माप(u_पूर्णांक8_t)) /* CTA_PROTO_NUM */
	       + nla_total_size(माप(u_पूर्णांक32_t)) /* CTA_ID */
	       + nla_total_size(माप(u_पूर्णांक32_t)) /* CTA_STATUS */
	       + ctnetlink_acct_size(ct)
	       + ctnetlink_बारtamp_size(ct)
	       + nla_total_size(माप(u_पूर्णांक32_t)) /* CTA_TIMEOUT */
	       + nla_total_size(0) /* CTA_PROTOINFO */
	       + nla_total_size(0) /* CTA_HELP */
	       + nla_total_size(NF_CT_HELPER_NAME_LEN) /* CTA_HELP_NAME */
	       + ctnetlink_secctx_size(ct)
#अगर IS_ENABLED(CONFIG_NF_NAT)
	       + 2 * nla_total_size(0) /* CTA_NAT_SEQ_ADJ_ORIG|REPL */
	       + 6 * nla_total_size(माप(u_पूर्णांक32_t)) /* CTA_NAT_SEQ_OFFSET */
#पूर्ण_अगर
#अगर_घोषित CONFIG_NF_CONNTRACK_MARK
	       + nla_total_size(माप(u_पूर्णांक32_t)) /* CTA_MARK */
#पूर्ण_अगर
#अगर_घोषित CONFIG_NF_CONNTRACK_ZONES
	       + nla_total_size(माप(u_पूर्णांक16_t)) /* CTA_ZONE|CTA_TUPLE_ZONE */
#पूर्ण_अगर
	       + ctnetlink_proto_size(ct)
	       + ctnetlink_label_size(ct)
	       ;
पूर्ण

अटल पूर्णांक
ctnetlink_conntrack_event(अचिन्हित पूर्णांक events, काष्ठा nf_ct_event *item)
अणु
	स्थिर काष्ठा nf_conntrack_zone *zone;
	काष्ठा net *net;
	काष्ठा nlmsghdr *nlh;
	काष्ठा nlattr *nest_parms;
	काष्ठा nf_conn *ct = item->ct;
	काष्ठा sk_buff *skb;
	अचिन्हित पूर्णांक type;
	अचिन्हित पूर्णांक flags = 0, group;
	पूर्णांक err;

	अगर (events & (1 << IPCT_DESTROY)) अणु
		type = IPCTNL_MSG_CT_DELETE;
		group = NFNLGRP_CONNTRACK_DESTROY;
	पूर्ण अन्यथा अगर (events & ((1 << IPCT_NEW) | (1 << IPCT_RELATED))) अणु
		type = IPCTNL_MSG_CT_NEW;
		flags = NLM_F_CREATE|NLM_F_EXCL;
		group = NFNLGRP_CONNTRACK_NEW;
	पूर्ण अन्यथा अगर (events) अणु
		type = IPCTNL_MSG_CT_NEW;
		group = NFNLGRP_CONNTRACK_UPDATE;
	पूर्ण अन्यथा
		वापस 0;

	net = nf_ct_net(ct);
	अगर (!item->report && !nfnetlink_has_listeners(net, group))
		वापस 0;

	skb = nlmsg_new(ctnetlink_nlmsg_size(ct), GFP_ATOMIC);
	अगर (skb == शून्य)
		जाओ errout;

	type = nfnl_msg_type(NFNL_SUBSYS_CTNETLINK, type);
	nlh = nfnl_msg_put(skb, item->portid, 0, type, flags, nf_ct_l3num(ct),
			   NFNETLINK_V0, 0);
	अगर (!nlh)
		जाओ nlmsg_failure;

	zone = nf_ct_zone(ct);

	nest_parms = nla_nest_start(skb, CTA_TUPLE_ORIG);
	अगर (!nest_parms)
		जाओ nla_put_failure;
	अगर (ctnetlink_dump_tuples(skb, nf_ct_tuple(ct, IP_CT_सूची_ORIGINAL)) < 0)
		जाओ nla_put_failure;
	अगर (ctnetlink_dump_zone_id(skb, CTA_TUPLE_ZONE, zone,
				   NF_CT_ZONE_सूची_ORIG) < 0)
		जाओ nla_put_failure;
	nla_nest_end(skb, nest_parms);

	nest_parms = nla_nest_start(skb, CTA_TUPLE_REPLY);
	अगर (!nest_parms)
		जाओ nla_put_failure;
	अगर (ctnetlink_dump_tuples(skb, nf_ct_tuple(ct, IP_CT_सूची_REPLY)) < 0)
		जाओ nla_put_failure;
	अगर (ctnetlink_dump_zone_id(skb, CTA_TUPLE_ZONE, zone,
				   NF_CT_ZONE_सूची_REPL) < 0)
		जाओ nla_put_failure;
	nla_nest_end(skb, nest_parms);

	अगर (ctnetlink_dump_zone_id(skb, CTA_ZONE, zone,
				   NF_CT_DEFAULT_ZONE_सूची) < 0)
		जाओ nla_put_failure;

	अगर (ctnetlink_dump_id(skb, ct) < 0)
		जाओ nla_put_failure;

	अगर (ctnetlink_dump_status(skb, ct) < 0)
		जाओ nla_put_failure;

	अगर (events & (1 << IPCT_DESTROY)) अणु
		अगर (ctnetlink_dump_समयout(skb, ct, true) < 0)
			जाओ nla_put_failure;

		अगर (ctnetlink_dump_acct(skb, ct, type) < 0 ||
		    ctnetlink_dump_बारtamp(skb, ct) < 0 ||
		    ctnetlink_dump_protoinfo(skb, ct, true) < 0)
			जाओ nla_put_failure;
	पूर्ण अन्यथा अणु
		अगर (ctnetlink_dump_समयout(skb, ct, false) < 0)
			जाओ nla_put_failure;

		अगर (events & (1 << IPCT_PROTOINFO) &&
		    ctnetlink_dump_protoinfo(skb, ct, false) < 0)
			जाओ nla_put_failure;

		अगर ((events & (1 << IPCT_HELPER) || nfct_help(ct))
		    && ctnetlink_dump_helpinfo(skb, ct) < 0)
			जाओ nla_put_failure;

#अगर_घोषित CONFIG_NF_CONNTRACK_SECMARK
		अगर ((events & (1 << IPCT_SECMARK) || ct->secmark)
		    && ctnetlink_dump_secctx(skb, ct) < 0)
			जाओ nla_put_failure;
#पूर्ण_अगर
		अगर (events & (1 << IPCT_LABEL) &&
		     ctnetlink_dump_labels(skb, ct) < 0)
			जाओ nla_put_failure;

		अगर (events & (1 << IPCT_RELATED) &&
		    ctnetlink_dump_master(skb, ct) < 0)
			जाओ nla_put_failure;

		अगर (events & (1 << IPCT_SEQADJ) &&
		    ctnetlink_dump_ct_seq_adj(skb, ct) < 0)
			जाओ nla_put_failure;

		अगर (events & (1 << IPCT_SYNPROXY) &&
		    ctnetlink_dump_ct_synproxy(skb, ct) < 0)
			जाओ nla_put_failure;
	पूर्ण

#अगर_घोषित CONFIG_NF_CONNTRACK_MARK
	अगर ((events & (1 << IPCT_MARK) || ct->mark)
	    && ctnetlink_dump_mark(skb, ct) < 0)
		जाओ nla_put_failure;
#पूर्ण_अगर
	nlmsg_end(skb, nlh);
	err = nfnetlink_send(skb, net, item->portid, group, item->report,
			     GFP_ATOMIC);
	अगर (err == -ENOBUFS || err == -EAGAIN)
		वापस -ENOBUFS;

	वापस 0;

nla_put_failure:
	nlmsg_cancel(skb, nlh);
nlmsg_failure:
	kमुक्त_skb(skb);
errout:
	अगर (nfnetlink_set_err(net, 0, group, -ENOBUFS) > 0)
		वापस -ENOBUFS;

	वापस 0;
पूर्ण
#पूर्ण_अगर /* CONFIG_NF_CONNTRACK_EVENTS */

अटल पूर्णांक ctnetlink_करोne(काष्ठा netlink_callback *cb)
अणु
	अगर (cb->args[1])
		nf_ct_put((काष्ठा nf_conn *)cb->args[1]);
	kमुक्त(cb->data);
	वापस 0;
पूर्ण

काष्ठा ctnetlink_filter अणु
	u8 family;

	u_पूर्णांक32_t orig_flags;
	u_पूर्णांक32_t reply_flags;

	काष्ठा nf_conntrack_tuple orig;
	काष्ठा nf_conntrack_tuple reply;
	काष्ठा nf_conntrack_zone zone;

	काष्ठा अणु
		u_पूर्णांक32_t val;
		u_पूर्णांक32_t mask;
	पूर्ण mark;
पूर्ण;

अटल स्थिर काष्ठा nla_policy cta_filter_nla_policy[CTA_FILTER_MAX + 1] = अणु
	[CTA_FILTER_ORIG_FLAGS]		= अणु .type = NLA_U32 पूर्ण,
	[CTA_FILTER_REPLY_FLAGS]	= अणु .type = NLA_U32 पूर्ण,
पूर्ण;

अटल पूर्णांक ctnetlink_parse_filter(स्थिर काष्ठा nlattr *attr,
				  काष्ठा ctnetlink_filter *filter)
अणु
	काष्ठा nlattr *tb[CTA_FILTER_MAX + 1];
	पूर्णांक ret = 0;

	ret = nla_parse_nested(tb, CTA_FILTER_MAX, attr, cta_filter_nla_policy,
			       शून्य);
	अगर (ret)
		वापस ret;

	अगर (tb[CTA_FILTER_ORIG_FLAGS]) अणु
		filter->orig_flags = nla_get_u32(tb[CTA_FILTER_ORIG_FLAGS]);
		अगर (filter->orig_flags & ~CTA_FILTER_F_ALL)
			वापस -EOPNOTSUPP;
	पूर्ण

	अगर (tb[CTA_FILTER_REPLY_FLAGS]) अणु
		filter->reply_flags = nla_get_u32(tb[CTA_FILTER_REPLY_FLAGS]);
		अगर (filter->reply_flags & ~CTA_FILTER_F_ALL)
			वापस -EOPNOTSUPP;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक ctnetlink_parse_zone(स्थिर काष्ठा nlattr *attr,
				काष्ठा nf_conntrack_zone *zone);
अटल पूर्णांक ctnetlink_parse_tuple_filter(स्थिर काष्ठा nlattr * स्थिर cda[],
					 काष्ठा nf_conntrack_tuple *tuple,
					 u32 type, u_पूर्णांक8_t l3num,
					 काष्ठा nf_conntrack_zone *zone,
					 u_पूर्णांक32_t flags);

अटल काष्ठा ctnetlink_filter *
ctnetlink_alloc_filter(स्थिर काष्ठा nlattr * स्थिर cda[], u8 family)
अणु
	काष्ठा ctnetlink_filter *filter;
	पूर्णांक err;

#अगर_अघोषित CONFIG_NF_CONNTRACK_MARK
	अगर (cda[CTA_MARK] || cda[CTA_MARK_MASK])
		वापस ERR_PTR(-EOPNOTSUPP);
#पूर्ण_अगर

	filter = kzalloc(माप(*filter), GFP_KERNEL);
	अगर (filter == शून्य)
		वापस ERR_PTR(-ENOMEM);

	filter->family = family;

#अगर_घोषित CONFIG_NF_CONNTRACK_MARK
	अगर (cda[CTA_MARK]) अणु
		filter->mark.val = ntohl(nla_get_be32(cda[CTA_MARK]));
		अगर (cda[CTA_MARK_MASK])
			filter->mark.mask = ntohl(nla_get_be32(cda[CTA_MARK_MASK]));
		अन्यथा
			filter->mark.mask = 0xffffffff;
	पूर्ण अन्यथा अगर (cda[CTA_MARK_MASK]) अणु
		err = -EINVAL;
		जाओ err_filter;
	पूर्ण
#पूर्ण_अगर
	अगर (!cda[CTA_FILTER])
		वापस filter;

	err = ctnetlink_parse_zone(cda[CTA_ZONE], &filter->zone);
	अगर (err < 0)
		जाओ err_filter;

	err = ctnetlink_parse_filter(cda[CTA_FILTER], filter);
	अगर (err < 0)
		जाओ err_filter;

	अगर (filter->orig_flags) अणु
		अगर (!cda[CTA_TUPLE_ORIG]) अणु
			err = -EINVAL;
			जाओ err_filter;
		पूर्ण

		err = ctnetlink_parse_tuple_filter(cda, &filter->orig,
						   CTA_TUPLE_ORIG,
						   filter->family,
						   &filter->zone,
						   filter->orig_flags);
		अगर (err < 0)
			जाओ err_filter;
	पूर्ण

	अगर (filter->reply_flags) अणु
		अगर (!cda[CTA_TUPLE_REPLY]) अणु
			err = -EINVAL;
			जाओ err_filter;
		पूर्ण

		err = ctnetlink_parse_tuple_filter(cda, &filter->reply,
						   CTA_TUPLE_REPLY,
						   filter->family,
						   &filter->zone,
						   filter->orig_flags);
		अगर (err < 0) अणु
			err = -EINVAL;
			जाओ err_filter;
		पूर्ण
	पूर्ण

	वापस filter;

err_filter:
	kमुक्त(filter);

	वापस ERR_PTR(err);
पूर्ण

अटल bool ctnetlink_needs_filter(u8 family, स्थिर काष्ठा nlattr * स्थिर *cda)
अणु
	वापस family || cda[CTA_MARK] || cda[CTA_FILTER];
पूर्ण

अटल पूर्णांक ctnetlink_start(काष्ठा netlink_callback *cb)
अणु
	स्थिर काष्ठा nlattr * स्थिर *cda = cb->data;
	काष्ठा ctnetlink_filter *filter = शून्य;
	काष्ठा nfgenmsg *nfmsg = nlmsg_data(cb->nlh);
	u8 family = nfmsg->nfgen_family;

	अगर (ctnetlink_needs_filter(family, cda)) अणु
		filter = ctnetlink_alloc_filter(cda, family);
		अगर (IS_ERR(filter))
			वापस PTR_ERR(filter);
	पूर्ण

	cb->data = filter;
	वापस 0;
पूर्ण

अटल पूर्णांक ctnetlink_filter_match_tuple(काष्ठा nf_conntrack_tuple *filter_tuple,
					काष्ठा nf_conntrack_tuple *ct_tuple,
					u_पूर्णांक32_t flags, पूर्णांक family)
अणु
	चयन (family) अणु
	हाल NFPROTO_IPV4:
		अगर ((flags & CTA_FILTER_FLAG(CTA_IP_SRC)) &&
		    filter_tuple->src.u3.ip != ct_tuple->src.u3.ip)
			वापस  0;

		अगर ((flags & CTA_FILTER_FLAG(CTA_IP_DST)) &&
		    filter_tuple->dst.u3.ip != ct_tuple->dst.u3.ip)
			वापस  0;
		अवरोध;
	हाल NFPROTO_IPV6:
		अगर ((flags & CTA_FILTER_FLAG(CTA_IP_SRC)) &&
		    !ipv6_addr_cmp(&filter_tuple->src.u3.in6,
				   &ct_tuple->src.u3.in6))
			वापस 0;

		अगर ((flags & CTA_FILTER_FLAG(CTA_IP_DST)) &&
		    !ipv6_addr_cmp(&filter_tuple->dst.u3.in6,
				   &ct_tuple->dst.u3.in6))
			वापस 0;
		अवरोध;
	पूर्ण

	अगर ((flags & CTA_FILTER_FLAG(CTA_PROTO_NUM)) &&
	    filter_tuple->dst.protonum != ct_tuple->dst.protonum)
		वापस 0;

	चयन (ct_tuple->dst.protonum) अणु
	हाल IPPROTO_TCP:
	हाल IPPROTO_UDP:
		अगर ((flags & CTA_FILTER_FLAG(CTA_PROTO_SRC_PORT)) &&
		    filter_tuple->src.u.tcp.port != ct_tuple->src.u.tcp.port)
			वापस 0;

		अगर ((flags & CTA_FILTER_FLAG(CTA_PROTO_DST_PORT)) &&
		    filter_tuple->dst.u.tcp.port != ct_tuple->dst.u.tcp.port)
			वापस 0;
		अवरोध;
	हाल IPPROTO_ICMP:
		अगर ((flags & CTA_FILTER_FLAG(CTA_PROTO_ICMP_TYPE)) &&
		    filter_tuple->dst.u.icmp.type != ct_tuple->dst.u.icmp.type)
			वापस 0;
		अगर ((flags & CTA_FILTER_FLAG(CTA_PROTO_ICMP_CODE)) &&
		    filter_tuple->dst.u.icmp.code != ct_tuple->dst.u.icmp.code)
			वापस 0;
		अगर ((flags & CTA_FILTER_FLAG(CTA_PROTO_ICMP_ID)) &&
		    filter_tuple->src.u.icmp.id != ct_tuple->src.u.icmp.id)
			वापस 0;
		अवरोध;
	हाल IPPROTO_ICMPV6:
		अगर ((flags & CTA_FILTER_FLAG(CTA_PROTO_ICMPV6_TYPE)) &&
		    filter_tuple->dst.u.icmp.type != ct_tuple->dst.u.icmp.type)
			वापस 0;
		अगर ((flags & CTA_FILTER_FLAG(CTA_PROTO_ICMPV6_CODE)) &&
		    filter_tuple->dst.u.icmp.code != ct_tuple->dst.u.icmp.code)
			वापस 0;
		अगर ((flags & CTA_FILTER_FLAG(CTA_PROTO_ICMPV6_ID)) &&
		    filter_tuple->src.u.icmp.id != ct_tuple->src.u.icmp.id)
			वापस 0;
		अवरोध;
	पूर्ण

	वापस 1;
पूर्ण

अटल पूर्णांक ctnetlink_filter_match(काष्ठा nf_conn *ct, व्योम *data)
अणु
	काष्ठा ctnetlink_filter *filter = data;
	काष्ठा nf_conntrack_tuple *tuple;

	अगर (filter == शून्य)
		जाओ out;

	/* Match entries of a given L3 protocol number.
	 * If it is not specअगरied, ie. l3proto == 0,
	 * then match everything.
	 */
	अगर (filter->family && nf_ct_l3num(ct) != filter->family)
		जाओ ignore_entry;

	अगर (filter->orig_flags) अणु
		tuple = nf_ct_tuple(ct, IP_CT_सूची_ORIGINAL);
		अगर (!ctnetlink_filter_match_tuple(&filter->orig, tuple,
						  filter->orig_flags,
						  filter->family))
			जाओ ignore_entry;
	पूर्ण

	अगर (filter->reply_flags) अणु
		tuple = nf_ct_tuple(ct, IP_CT_सूची_REPLY);
		अगर (!ctnetlink_filter_match_tuple(&filter->reply, tuple,
						  filter->reply_flags,
						  filter->family))
			जाओ ignore_entry;
	पूर्ण

#अगर_घोषित CONFIG_NF_CONNTRACK_MARK
	अगर ((ct->mark & filter->mark.mask) != filter->mark.val)
		जाओ ignore_entry;
#पूर्ण_अगर

out:
	वापस 1;

ignore_entry:
	वापस 0;
पूर्ण

अटल पूर्णांक
ctnetlink_dump_table(काष्ठा sk_buff *skb, काष्ठा netlink_callback *cb)
अणु
	अचिन्हित पूर्णांक flags = cb->data ? NLM_F_DUMP_FILTERED : 0;
	काष्ठा net *net = sock_net(skb->sk);
	काष्ठा nf_conn *ct, *last;
	काष्ठा nf_conntrack_tuple_hash *h;
	काष्ठा hlist_nulls_node *n;
	काष्ठा nf_conn *nf_ct_evict[8];
	पूर्णांक res, i;
	spinlock_t *lockp;

	last = (काष्ठा nf_conn *)cb->args[1];
	i = 0;

	local_bh_disable();
	क्रम (; cb->args[0] < nf_conntrack_htable_size; cb->args[0]++) अणु
restart:
		जबतक (i) अणु
			i--;
			अगर (nf_ct_should_gc(nf_ct_evict[i]))
				nf_ct_समाप्त(nf_ct_evict[i]);
			nf_ct_put(nf_ct_evict[i]);
		पूर्ण

		lockp = &nf_conntrack_locks[cb->args[0] % CONNTRACK_LOCKS];
		nf_conntrack_lock(lockp);
		अगर (cb->args[0] >= nf_conntrack_htable_size) अणु
			spin_unlock(lockp);
			जाओ out;
		पूर्ण
		hlist_nulls_क्रम_each_entry(h, n, &nf_conntrack_hash[cb->args[0]],
					   hnnode) अणु
			अगर (NF_CT_सूचीECTION(h) != IP_CT_सूची_ORIGINAL)
				जारी;
			ct = nf_ct_tuplehash_to_ctrack(h);
			अगर (nf_ct_is_expired(ct)) अणु
				अगर (i < ARRAY_SIZE(nf_ct_evict) &&
				    atomic_inc_not_zero(&ct->ct_general.use))
					nf_ct_evict[i++] = ct;
				जारी;
			पूर्ण

			अगर (!net_eq(net, nf_ct_net(ct)))
				जारी;

			अगर (cb->args[1]) अणु
				अगर (ct != last)
					जारी;
				cb->args[1] = 0;
			पूर्ण
			अगर (!ctnetlink_filter_match(ct, cb->data))
				जारी;

			res =
			ctnetlink_fill_info(skb, NETLINK_CB(cb->skb).portid,
					    cb->nlh->nlmsg_seq,
					    NFNL_MSG_TYPE(cb->nlh->nlmsg_type),
					    ct, true, flags);
			अगर (res < 0) अणु
				nf_conntrack_get(&ct->ct_general);
				cb->args[1] = (अचिन्हित दीर्घ)ct;
				spin_unlock(lockp);
				जाओ out;
			पूर्ण
		पूर्ण
		spin_unlock(lockp);
		अगर (cb->args[1]) अणु
			cb->args[1] = 0;
			जाओ restart;
		पूर्ण
	पूर्ण
out:
	local_bh_enable();
	अगर (last) अणु
		/* nf ct hash resize happened, now clear the leftover. */
		अगर ((काष्ठा nf_conn *)cb->args[1] == last)
			cb->args[1] = 0;

		nf_ct_put(last);
	पूर्ण

	जबतक (i) अणु
		i--;
		अगर (nf_ct_should_gc(nf_ct_evict[i]))
			nf_ct_समाप्त(nf_ct_evict[i]);
		nf_ct_put(nf_ct_evict[i]);
	पूर्ण

	वापस skb->len;
पूर्ण

अटल पूर्णांक ipv4_nlattr_to_tuple(काष्ठा nlattr *tb[],
				काष्ठा nf_conntrack_tuple *t,
				u_पूर्णांक32_t flags)
अणु
	अगर (flags & CTA_FILTER_FLAG(CTA_IP_SRC)) अणु
		अगर (!tb[CTA_IP_V4_SRC])
			वापस -EINVAL;

		t->src.u3.ip = nla_get_in_addr(tb[CTA_IP_V4_SRC]);
	पूर्ण

	अगर (flags & CTA_FILTER_FLAG(CTA_IP_DST)) अणु
		अगर (!tb[CTA_IP_V4_DST])
			वापस -EINVAL;

		t->dst.u3.ip = nla_get_in_addr(tb[CTA_IP_V4_DST]);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक ipv6_nlattr_to_tuple(काष्ठा nlattr *tb[],
				काष्ठा nf_conntrack_tuple *t,
				u_पूर्णांक32_t flags)
अणु
	अगर (flags & CTA_FILTER_FLAG(CTA_IP_SRC)) अणु
		अगर (!tb[CTA_IP_V6_SRC])
			वापस -EINVAL;

		t->src.u3.in6 = nla_get_in6_addr(tb[CTA_IP_V6_SRC]);
	पूर्ण

	अगर (flags & CTA_FILTER_FLAG(CTA_IP_DST)) अणु
		अगर (!tb[CTA_IP_V6_DST])
			वापस -EINVAL;

		t->dst.u3.in6 = nla_get_in6_addr(tb[CTA_IP_V6_DST]);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक ctnetlink_parse_tuple_ip(काष्ठा nlattr *attr,
				    काष्ठा nf_conntrack_tuple *tuple,
				    u_पूर्णांक32_t flags)
अणु
	काष्ठा nlattr *tb[CTA_IP_MAX+1];
	पूर्णांक ret = 0;

	ret = nla_parse_nested_deprecated(tb, CTA_IP_MAX, attr, शून्य, शून्य);
	अगर (ret < 0)
		वापस ret;

	ret = nla_validate_nested_deprecated(attr, CTA_IP_MAX,
					     cta_ip_nla_policy, शून्य);
	अगर (ret)
		वापस ret;

	चयन (tuple->src.l3num) अणु
	हाल NFPROTO_IPV4:
		ret = ipv4_nlattr_to_tuple(tb, tuple, flags);
		अवरोध;
	हाल NFPROTO_IPV6:
		ret = ipv6_nlattr_to_tuple(tb, tuple, flags);
		अवरोध;
	पूर्ण

	वापस ret;
पूर्ण

अटल स्थिर काष्ठा nla_policy proto_nla_policy[CTA_PROTO_MAX+1] = अणु
	[CTA_PROTO_NUM]	= अणु .type = NLA_U8 पूर्ण,
पूर्ण;

अटल पूर्णांक ctnetlink_parse_tuple_proto(काष्ठा nlattr *attr,
				       काष्ठा nf_conntrack_tuple *tuple,
				       u_पूर्णांक32_t flags)
अणु
	स्थिर काष्ठा nf_conntrack_l4proto *l4proto;
	काष्ठा nlattr *tb[CTA_PROTO_MAX+1];
	पूर्णांक ret = 0;

	ret = nla_parse_nested_deprecated(tb, CTA_PROTO_MAX, attr,
					  proto_nla_policy, शून्य);
	अगर (ret < 0)
		वापस ret;

	अगर (!(flags & CTA_FILTER_FLAG(CTA_PROTO_NUM)))
		वापस 0;

	अगर (!tb[CTA_PROTO_NUM])
		वापस -EINVAL;

	tuple->dst.protonum = nla_get_u8(tb[CTA_PROTO_NUM]);

	rcu_पढ़ो_lock();
	l4proto = nf_ct_l4proto_find(tuple->dst.protonum);

	अगर (likely(l4proto->nlattr_to_tuple)) अणु
		ret = nla_validate_nested_deprecated(attr, CTA_PROTO_MAX,
						     l4proto->nla_policy,
						     शून्य);
		अगर (ret == 0)
			ret = l4proto->nlattr_to_tuple(tb, tuple, flags);
	पूर्ण

	rcu_पढ़ो_unlock();

	वापस ret;
पूर्ण

अटल पूर्णांक
ctnetlink_parse_zone(स्थिर काष्ठा nlattr *attr,
		     काष्ठा nf_conntrack_zone *zone)
अणु
	nf_ct_zone_init(zone, NF_CT_DEFAULT_ZONE_ID,
			NF_CT_DEFAULT_ZONE_सूची, 0);
#अगर_घोषित CONFIG_NF_CONNTRACK_ZONES
	अगर (attr)
		zone->id = ntohs(nla_get_be16(attr));
#अन्यथा
	अगर (attr)
		वापस -EOPNOTSUPP;
#पूर्ण_अगर
	वापस 0;
पूर्ण

अटल पूर्णांक
ctnetlink_parse_tuple_zone(काष्ठा nlattr *attr, क्रमागत ctattr_type type,
			   काष्ठा nf_conntrack_zone *zone)
अणु
	पूर्णांक ret;

	अगर (zone->id != NF_CT_DEFAULT_ZONE_ID)
		वापस -EINVAL;

	ret = ctnetlink_parse_zone(attr, zone);
	अगर (ret < 0)
		वापस ret;

	अगर (type == CTA_TUPLE_REPLY)
		zone->dir = NF_CT_ZONE_सूची_REPL;
	अन्यथा
		zone->dir = NF_CT_ZONE_सूची_ORIG;

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा nla_policy tuple_nla_policy[CTA_TUPLE_MAX+1] = अणु
	[CTA_TUPLE_IP]		= अणु .type = NLA_NESTED पूर्ण,
	[CTA_TUPLE_PROTO]	= अणु .type = NLA_NESTED पूर्ण,
	[CTA_TUPLE_ZONE]	= अणु .type = NLA_U16 पूर्ण,
पूर्ण;

#घोषणा CTA_FILTER_F_ALL_CTA_PROTO \
  (CTA_FILTER_F_CTA_PROTO_SRC_PORT | \
   CTA_FILTER_F_CTA_PROTO_DST_PORT | \
   CTA_FILTER_F_CTA_PROTO_ICMP_TYPE | \
   CTA_FILTER_F_CTA_PROTO_ICMP_CODE | \
   CTA_FILTER_F_CTA_PROTO_ICMP_ID | \
   CTA_FILTER_F_CTA_PROTO_ICMPV6_TYPE | \
   CTA_FILTER_F_CTA_PROTO_ICMPV6_CODE | \
   CTA_FILTER_F_CTA_PROTO_ICMPV6_ID)

अटल पूर्णांक
ctnetlink_parse_tuple_filter(स्थिर काष्ठा nlattr * स्थिर cda[],
			      काष्ठा nf_conntrack_tuple *tuple, u32 type,
			      u_पूर्णांक8_t l3num, काष्ठा nf_conntrack_zone *zone,
			      u_पूर्णांक32_t flags)
अणु
	काष्ठा nlattr *tb[CTA_TUPLE_MAX+1];
	पूर्णांक err;

	स_रखो(tuple, 0, माप(*tuple));

	err = nla_parse_nested_deprecated(tb, CTA_TUPLE_MAX, cda[type],
					  tuple_nla_policy, शून्य);
	अगर (err < 0)
		वापस err;

	अगर (l3num != NFPROTO_IPV4 && l3num != NFPROTO_IPV6)
		वापस -EOPNOTSUPP;
	tuple->src.l3num = l3num;

	अगर (flags & CTA_FILTER_FLAG(CTA_IP_DST) ||
	    flags & CTA_FILTER_FLAG(CTA_IP_SRC)) अणु
		अगर (!tb[CTA_TUPLE_IP])
			वापस -EINVAL;

		err = ctnetlink_parse_tuple_ip(tb[CTA_TUPLE_IP], tuple, flags);
		अगर (err < 0)
			वापस err;
	पूर्ण

	अगर (flags & CTA_FILTER_FLAG(CTA_PROTO_NUM)) अणु
		अगर (!tb[CTA_TUPLE_PROTO])
			वापस -EINVAL;

		err = ctnetlink_parse_tuple_proto(tb[CTA_TUPLE_PROTO], tuple, flags);
		अगर (err < 0)
			वापस err;
	पूर्ण अन्यथा अगर (flags & CTA_FILTER_FLAG(ALL_CTA_PROTO)) अणु
		/* Can't manage proto flags without a protonum  */
		वापस -EINVAL;
	पूर्ण

	अगर ((flags & CTA_FILTER_FLAG(CTA_TUPLE_ZONE)) && tb[CTA_TUPLE_ZONE]) अणु
		अगर (!zone)
			वापस -EINVAL;

		err = ctnetlink_parse_tuple_zone(tb[CTA_TUPLE_ZONE],
						 type, zone);
		अगर (err < 0)
			वापस err;
	पूर्ण

	/* orig and expect tuples get सूची_ORIGINAL */
	अगर (type == CTA_TUPLE_REPLY)
		tuple->dst.dir = IP_CT_सूची_REPLY;
	अन्यथा
		tuple->dst.dir = IP_CT_सूची_ORIGINAL;

	वापस 0;
पूर्ण

अटल पूर्णांक
ctnetlink_parse_tuple(स्थिर काष्ठा nlattr * स्थिर cda[],
		      काष्ठा nf_conntrack_tuple *tuple, u32 type,
		      u_पूर्णांक8_t l3num, काष्ठा nf_conntrack_zone *zone)
अणु
	वापस ctnetlink_parse_tuple_filter(cda, tuple, type, l3num, zone,
					    CTA_FILTER_FLAG(ALL));
पूर्ण

अटल स्थिर काष्ठा nla_policy help_nla_policy[CTA_HELP_MAX+1] = अणु
	[CTA_HELP_NAME]		= अणु .type = NLA_NUL_STRING,
				    .len = NF_CT_HELPER_NAME_LEN - 1 पूर्ण,
पूर्ण;

अटल पूर्णांक ctnetlink_parse_help(स्थिर काष्ठा nlattr *attr, अक्षर **helper_name,
				काष्ठा nlattr **helpinfo)
अणु
	पूर्णांक err;
	काष्ठा nlattr *tb[CTA_HELP_MAX+1];

	err = nla_parse_nested_deprecated(tb, CTA_HELP_MAX, attr,
					  help_nla_policy, शून्य);
	अगर (err < 0)
		वापस err;

	अगर (!tb[CTA_HELP_NAME])
		वापस -EINVAL;

	*helper_name = nla_data(tb[CTA_HELP_NAME]);

	अगर (tb[CTA_HELP_INFO])
		*helpinfo = tb[CTA_HELP_INFO];

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा nla_policy ct_nla_policy[CTA_MAX+1] = अणु
	[CTA_TUPLE_ORIG]	= अणु .type = NLA_NESTED पूर्ण,
	[CTA_TUPLE_REPLY]	= अणु .type = NLA_NESTED पूर्ण,
	[CTA_STATUS] 		= अणु .type = NLA_U32 पूर्ण,
	[CTA_PROTOINFO]		= अणु .type = NLA_NESTED पूर्ण,
	[CTA_HELP]		= अणु .type = NLA_NESTED पूर्ण,
	[CTA_NAT_SRC]		= अणु .type = NLA_NESTED पूर्ण,
	[CTA_TIMEOUT] 		= अणु .type = NLA_U32 पूर्ण,
	[CTA_MARK]		= अणु .type = NLA_U32 पूर्ण,
	[CTA_ID]		= अणु .type = NLA_U32 पूर्ण,
	[CTA_NAT_DST]		= अणु .type = NLA_NESTED पूर्ण,
	[CTA_TUPLE_MASTER]	= अणु .type = NLA_NESTED पूर्ण,
	[CTA_NAT_SEQ_ADJ_ORIG]  = अणु .type = NLA_NESTED पूर्ण,
	[CTA_NAT_SEQ_ADJ_REPLY] = अणु .type = NLA_NESTED पूर्ण,
	[CTA_ZONE]		= अणु .type = NLA_U16 पूर्ण,
	[CTA_MARK_MASK]		= अणु .type = NLA_U32 पूर्ण,
	[CTA_LABELS]		= अणु .type = NLA_BINARY,
				    .len = NF_CT_LABELS_MAX_SIZE पूर्ण,
	[CTA_LABELS_MASK]	= अणु .type = NLA_BINARY,
				    .len = NF_CT_LABELS_MAX_SIZE पूर्ण,
	[CTA_FILTER]		= अणु .type = NLA_NESTED पूर्ण,
पूर्ण;

अटल पूर्णांक ctnetlink_flush_iterate(काष्ठा nf_conn *ct, व्योम *data)
अणु
	अगर (test_bit(IPS_OFFLOAD_BIT, &ct->status))
		वापस 0;

	वापस ctnetlink_filter_match(ct, data);
पूर्ण

अटल पूर्णांक ctnetlink_flush_conntrack(काष्ठा net *net,
				     स्थिर काष्ठा nlattr * स्थिर cda[],
				     u32 portid, पूर्णांक report, u8 family)
अणु
	काष्ठा ctnetlink_filter *filter = शून्य;

	अगर (ctnetlink_needs_filter(family, cda)) अणु
		अगर (cda[CTA_FILTER])
			वापस -EOPNOTSUPP;

		filter = ctnetlink_alloc_filter(cda, family);
		अगर (IS_ERR(filter))
			वापस PTR_ERR(filter);
	पूर्ण

	nf_ct_iterate_cleanup_net(net, ctnetlink_flush_iterate, filter,
				  portid, report);
	kमुक्त(filter);

	वापस 0;
पूर्ण

अटल पूर्णांक ctnetlink_del_conntrack(काष्ठा sk_buff *skb,
				   स्थिर काष्ठा nfnl_info *info,
				   स्थिर काष्ठा nlattr * स्थिर cda[])
अणु
	काष्ठा nfgenmsg *nfmsg = nlmsg_data(info->nlh);
	काष्ठा nf_conntrack_tuple_hash *h;
	काष्ठा nf_conntrack_tuple tuple;
	काष्ठा nf_conntrack_zone zone;
	काष्ठा nf_conn *ct;
	पूर्णांक err;

	err = ctnetlink_parse_zone(cda[CTA_ZONE], &zone);
	अगर (err < 0)
		वापस err;

	अगर (cda[CTA_TUPLE_ORIG])
		err = ctnetlink_parse_tuple(cda, &tuple, CTA_TUPLE_ORIG,
					    nfmsg->nfgen_family, &zone);
	अन्यथा अगर (cda[CTA_TUPLE_REPLY])
		err = ctnetlink_parse_tuple(cda, &tuple, CTA_TUPLE_REPLY,
					    nfmsg->nfgen_family, &zone);
	अन्यथा अणु
		u_पूर्णांक8_t u3 = nfmsg->version ? nfmsg->nfgen_family : AF_UNSPEC;

		वापस ctnetlink_flush_conntrack(info->net, cda,
						 NETLINK_CB(skb).portid,
						 nlmsg_report(info->nlh), u3);
	पूर्ण

	अगर (err < 0)
		वापस err;

	h = nf_conntrack_find_get(info->net, &zone, &tuple);
	अगर (!h)
		वापस -ENOENT;

	ct = nf_ct_tuplehash_to_ctrack(h);

	अगर (test_bit(IPS_OFFLOAD_BIT, &ct->status)) अणु
		nf_ct_put(ct);
		वापस -EBUSY;
	पूर्ण

	अगर (cda[CTA_ID]) अणु
		__be32 id = nla_get_be32(cda[CTA_ID]);

		अगर (id != (__क्रमce __be32)nf_ct_get_id(ct)) अणु
			nf_ct_put(ct);
			वापस -ENOENT;
		पूर्ण
	पूर्ण

	nf_ct_delete(ct, NETLINK_CB(skb).portid, nlmsg_report(info->nlh));
	nf_ct_put(ct);

	वापस 0;
पूर्ण

अटल पूर्णांक ctnetlink_get_conntrack(काष्ठा sk_buff *skb,
				   स्थिर काष्ठा nfnl_info *info,
				   स्थिर काष्ठा nlattr * स्थिर cda[])
अणु
	काष्ठा nfgenmsg *nfmsg = nlmsg_data(info->nlh);
	u_पूर्णांक8_t u3 = nfmsg->nfgen_family;
	काष्ठा nf_conntrack_tuple_hash *h;
	काष्ठा nf_conntrack_tuple tuple;
	काष्ठा nf_conntrack_zone zone;
	काष्ठा sk_buff *skb2;
	काष्ठा nf_conn *ct;
	पूर्णांक err;

	अगर (info->nlh->nlmsg_flags & NLM_F_DUMP) अणु
		काष्ठा netlink_dump_control c = अणु
			.start = ctnetlink_start,
			.dump = ctnetlink_dump_table,
			.करोne = ctnetlink_करोne,
			.data = (व्योम *)cda,
		पूर्ण;

		वापस netlink_dump_start(info->sk, skb, info->nlh, &c);
	पूर्ण

	err = ctnetlink_parse_zone(cda[CTA_ZONE], &zone);
	अगर (err < 0)
		वापस err;

	अगर (cda[CTA_TUPLE_ORIG])
		err = ctnetlink_parse_tuple(cda, &tuple, CTA_TUPLE_ORIG,
					    u3, &zone);
	अन्यथा अगर (cda[CTA_TUPLE_REPLY])
		err = ctnetlink_parse_tuple(cda, &tuple, CTA_TUPLE_REPLY,
					    u3, &zone);
	अन्यथा
		वापस -EINVAL;

	अगर (err < 0)
		वापस err;

	h = nf_conntrack_find_get(info->net, &zone, &tuple);
	अगर (!h)
		वापस -ENOENT;

	ct = nf_ct_tuplehash_to_ctrack(h);

	err = -ENOMEM;
	skb2 = nlmsg_new(NLMSG_DEFAULT_SIZE, GFP_KERNEL);
	अगर (skb2 == शून्य) अणु
		nf_ct_put(ct);
		वापस -ENOMEM;
	पूर्ण

	err = ctnetlink_fill_info(skb2, NETLINK_CB(skb).portid,
				  info->nlh->nlmsg_seq,
				  NFNL_MSG_TYPE(info->nlh->nlmsg_type), ct,
				  true, 0);
	nf_ct_put(ct);
	अगर (err <= 0)
		जाओ मुक्त;

	err = netlink_unicast(info->sk, skb2, NETLINK_CB(skb).portid,
			      MSG_DONTWAIT);
	अगर (err < 0)
		जाओ out;

	वापस 0;

मुक्त:
	kमुक्त_skb(skb2);
out:
	/* this aव्योमs a loop in nfnetlink. */
	वापस err == -EAGAIN ? -ENOBUFS : err;
पूर्ण

अटल पूर्णांक ctnetlink_करोne_list(काष्ठा netlink_callback *cb)
अणु
	अगर (cb->args[1])
		nf_ct_put((काष्ठा nf_conn *)cb->args[1]);
	वापस 0;
पूर्ण

अटल पूर्णांक
ctnetlink_dump_list(काष्ठा sk_buff *skb, काष्ठा netlink_callback *cb, bool dying)
अणु
	काष्ठा nf_conn *ct, *last;
	काष्ठा nf_conntrack_tuple_hash *h;
	काष्ठा hlist_nulls_node *n;
	काष्ठा nfgenmsg *nfmsg = nlmsg_data(cb->nlh);
	u_पूर्णांक8_t l3proto = nfmsg->nfgen_family;
	पूर्णांक res;
	पूर्णांक cpu;
	काष्ठा hlist_nulls_head *list;
	काष्ठा net *net = sock_net(skb->sk);

	अगर (cb->args[2])
		वापस 0;

	last = (काष्ठा nf_conn *)cb->args[1];

	क्रम (cpu = cb->args[0]; cpu < nr_cpu_ids; cpu++) अणु
		काष्ठा ct_pcpu *pcpu;

		अगर (!cpu_possible(cpu))
			जारी;

		pcpu = per_cpu_ptr(net->ct.pcpu_lists, cpu);
		spin_lock_bh(&pcpu->lock);
		list = dying ? &pcpu->dying : &pcpu->unconfirmed;
restart:
		hlist_nulls_क्रम_each_entry(h, n, list, hnnode) अणु
			ct = nf_ct_tuplehash_to_ctrack(h);
			अगर (l3proto && nf_ct_l3num(ct) != l3proto)
				जारी;
			अगर (cb->args[1]) अणु
				अगर (ct != last)
					जारी;
				cb->args[1] = 0;
			पूर्ण

			/* We can't dump extension info क्रम the unconfirmed
			 * list because unconfirmed conntracks can have
			 * ct->ext पुनः_स्मृतिated (and thus मुक्तd).
			 *
			 * In the dying list हाल ct->ext can't be free'd
			 * until after we drop pcpu->lock.
			 */
			res = ctnetlink_fill_info(skb, NETLINK_CB(cb->skb).portid,
						  cb->nlh->nlmsg_seq,
						  NFNL_MSG_TYPE(cb->nlh->nlmsg_type),
						  ct, dying ? true : false, 0);
			अगर (res < 0) अणु
				अगर (!atomic_inc_not_zero(&ct->ct_general.use))
					जारी;
				cb->args[0] = cpu;
				cb->args[1] = (अचिन्हित दीर्घ)ct;
				spin_unlock_bh(&pcpu->lock);
				जाओ out;
			पूर्ण
		पूर्ण
		अगर (cb->args[1]) अणु
			cb->args[1] = 0;
			जाओ restart;
		पूर्ण
		spin_unlock_bh(&pcpu->lock);
	पूर्ण
	cb->args[2] = 1;
out:
	अगर (last)
		nf_ct_put(last);

	वापस skb->len;
पूर्ण

अटल पूर्णांक
ctnetlink_dump_dying(काष्ठा sk_buff *skb, काष्ठा netlink_callback *cb)
अणु
	वापस ctnetlink_dump_list(skb, cb, true);
पूर्ण

अटल पूर्णांक ctnetlink_get_ct_dying(काष्ठा sk_buff *skb,
				  स्थिर काष्ठा nfnl_info *info,
				  स्थिर काष्ठा nlattr * स्थिर cda[])
अणु
	अगर (info->nlh->nlmsg_flags & NLM_F_DUMP) अणु
		काष्ठा netlink_dump_control c = अणु
			.dump = ctnetlink_dump_dying,
			.करोne = ctnetlink_करोne_list,
		पूर्ण;
		वापस netlink_dump_start(info->sk, skb, info->nlh, &c);
	पूर्ण

	वापस -EOPNOTSUPP;
पूर्ण

अटल पूर्णांक
ctnetlink_dump_unconfirmed(काष्ठा sk_buff *skb, काष्ठा netlink_callback *cb)
अणु
	वापस ctnetlink_dump_list(skb, cb, false);
पूर्ण

अटल पूर्णांक ctnetlink_get_ct_unconfirmed(काष्ठा sk_buff *skb,
					स्थिर काष्ठा nfnl_info *info,
					स्थिर काष्ठा nlattr * स्थिर cda[])
अणु
	अगर (info->nlh->nlmsg_flags & NLM_F_DUMP) अणु
		काष्ठा netlink_dump_control c = अणु
			.dump = ctnetlink_dump_unconfirmed,
			.करोne = ctnetlink_करोne_list,
		पूर्ण;
		वापस netlink_dump_start(info->sk, skb, info->nlh, &c);
	पूर्ण

	वापस -EOPNOTSUPP;
पूर्ण

#अगर IS_ENABLED(CONFIG_NF_NAT)
अटल पूर्णांक
ctnetlink_parse_nat_setup(काष्ठा nf_conn *ct,
			  क्रमागत nf_nat_manip_type manip,
			  स्थिर काष्ठा nlattr *attr)
	__must_hold(RCU)
अणु
	काष्ठा nf_nat_hook *nat_hook;
	पूर्णांक err;

	nat_hook = rcu_dereference(nf_nat_hook);
	अगर (!nat_hook) अणु
#अगर_घोषित CONFIG_MODULES
		rcu_पढ़ो_unlock();
		nfnl_unlock(NFNL_SUBSYS_CTNETLINK);
		अगर (request_module("nf-nat") < 0) अणु
			nfnl_lock(NFNL_SUBSYS_CTNETLINK);
			rcu_पढ़ो_lock();
			वापस -EOPNOTSUPP;
		पूर्ण
		nfnl_lock(NFNL_SUBSYS_CTNETLINK);
		rcu_पढ़ो_lock();
		nat_hook = rcu_dereference(nf_nat_hook);
		अगर (nat_hook)
			वापस -EAGAIN;
#पूर्ण_अगर
		वापस -EOPNOTSUPP;
	पूर्ण

	err = nat_hook->parse_nat_setup(ct, manip, attr);
	अगर (err == -EAGAIN) अणु
#अगर_घोषित CONFIG_MODULES
		rcu_पढ़ो_unlock();
		nfnl_unlock(NFNL_SUBSYS_CTNETLINK);
		अगर (request_module("nf-nat-%u", nf_ct_l3num(ct)) < 0) अणु
			nfnl_lock(NFNL_SUBSYS_CTNETLINK);
			rcu_पढ़ो_lock();
			वापस -EOPNOTSUPP;
		पूर्ण
		nfnl_lock(NFNL_SUBSYS_CTNETLINK);
		rcu_पढ़ो_lock();
#अन्यथा
		err = -EOPNOTSUPP;
#पूर्ण_अगर
	पूर्ण
	वापस err;
पूर्ण
#पूर्ण_अगर

अटल व्योम
__ctnetlink_change_status(काष्ठा nf_conn *ct, अचिन्हित दीर्घ on,
			  अचिन्हित दीर्घ off)
अणु
	अचिन्हित पूर्णांक bit;

	/* Ignore these unchangable bits */
	on &= ~IPS_UNCHANGEABLE_MASK;
	off &= ~IPS_UNCHANGEABLE_MASK;

	क्रम (bit = 0; bit < __IPS_MAX_BIT; bit++) अणु
		अगर (on & (1 << bit))
			set_bit(bit, &ct->status);
		अन्यथा अगर (off & (1 << bit))
			clear_bit(bit, &ct->status);
	पूर्ण
पूर्ण

अटल पूर्णांक
ctnetlink_change_status(काष्ठा nf_conn *ct, स्थिर काष्ठा nlattr * स्थिर cda[])
अणु
	अचिन्हित दीर्घ d;
	अचिन्हित पूर्णांक status = ntohl(nla_get_be32(cda[CTA_STATUS]));
	d = ct->status ^ status;

	अगर (d & (IPS_EXPECTED|IPS_CONFIRMED|IPS_DYING))
		/* unchangeable */
		वापस -EBUSY;

	अगर (d & IPS_SEEN_REPLY && !(status & IPS_SEEN_REPLY))
		/* SEEN_REPLY bit can only be set */
		वापस -EBUSY;

	अगर (d & IPS_ASSURED && !(status & IPS_ASSURED))
		/* ASSURED bit can only be set */
		वापस -EBUSY;

	__ctnetlink_change_status(ct, status, 0);
	वापस 0;
पूर्ण

अटल पूर्णांक
ctnetlink_setup_nat(काष्ठा nf_conn *ct, स्थिर काष्ठा nlattr * स्थिर cda[])
अणु
#अगर IS_ENABLED(CONFIG_NF_NAT)
	पूर्णांक ret;

	अगर (!cda[CTA_NAT_DST] && !cda[CTA_NAT_SRC])
		वापस 0;

	ret = ctnetlink_parse_nat_setup(ct, NF_NAT_MANIP_DST,
					cda[CTA_NAT_DST]);
	अगर (ret < 0)
		वापस ret;

	वापस ctnetlink_parse_nat_setup(ct, NF_NAT_MANIP_SRC,
					 cda[CTA_NAT_SRC]);
#अन्यथा
	अगर (!cda[CTA_NAT_DST] && !cda[CTA_NAT_SRC])
		वापस 0;
	वापस -EOPNOTSUPP;
#पूर्ण_अगर
पूर्ण

अटल पूर्णांक ctnetlink_change_helper(काष्ठा nf_conn *ct,
				   स्थिर काष्ठा nlattr * स्थिर cda[])
अणु
	काष्ठा nf_conntrack_helper *helper;
	काष्ठा nf_conn_help *help = nfct_help(ct);
	अक्षर *helpname = शून्य;
	काष्ठा nlattr *helpinfo = शून्य;
	पूर्णांक err;

	err = ctnetlink_parse_help(cda[CTA_HELP], &helpname, &helpinfo);
	अगर (err < 0)
		वापस err;

	/* करोn't change helper of sibling connections */
	अगर (ct->master) अणु
		/* If we try to change the helper to the same thing twice,
		 * treat the second attempt as a no-op instead of वापसing
		 * an error.
		 */
		err = -EBUSY;
		अगर (help) अणु
			rcu_पढ़ो_lock();
			helper = rcu_dereference(help->helper);
			अगर (helper && !म_भेद(helper->name, helpname))
				err = 0;
			rcu_पढ़ो_unlock();
		पूर्ण

		वापस err;
	पूर्ण

	अगर (!म_भेद(helpname, "")) अणु
		अगर (help && help->helper) अणु
			/* we had a helper beक्रमe ... */
			nf_ct_हटाओ_expectations(ct);
			RCU_INIT_POINTER(help->helper, शून्य);
		पूर्ण

		वापस 0;
	पूर्ण

	rcu_पढ़ो_lock();
	helper = __nf_conntrack_helper_find(helpname, nf_ct_l3num(ct),
					    nf_ct_protonum(ct));
	अगर (helper == शून्य) अणु
		rcu_पढ़ो_unlock();
		वापस -EOPNOTSUPP;
	पूर्ण

	अगर (help) अणु
		अगर (help->helper == helper) अणु
			/* update निजी helper data अगर allowed. */
			अगर (helper->from_nlattr)
				helper->from_nlattr(helpinfo, ct);
			err = 0;
		पूर्ण अन्यथा
			err = -EBUSY;
	पूर्ण अन्यथा अणु
		/* we cannot set a helper क्रम an existing conntrack */
		err = -EOPNOTSUPP;
	पूर्ण

	rcu_पढ़ो_unlock();
	वापस err;
पूर्ण

अटल पूर्णांक ctnetlink_change_समयout(काष्ठा nf_conn *ct,
				    स्थिर काष्ठा nlattr * स्थिर cda[])
अणु
	u64 समयout = (u64)ntohl(nla_get_be32(cda[CTA_TIMEOUT])) * HZ;

	अगर (समयout > पूर्णांक_उच्च)
		समयout = पूर्णांक_उच्च;
	ct->समयout = nfct_समय_stamp + (u32)समयout;

	अगर (test_bit(IPS_DYING_BIT, &ct->status))
		वापस -ETIME;

	वापस 0;
पूर्ण

#अगर defined(CONFIG_NF_CONNTRACK_MARK)
अटल व्योम ctnetlink_change_mark(काष्ठा nf_conn *ct,
				    स्थिर काष्ठा nlattr * स्थिर cda[])
अणु
	u32 mark, newmark, mask = 0;

	अगर (cda[CTA_MARK_MASK])
		mask = ~ntohl(nla_get_be32(cda[CTA_MARK_MASK]));

	mark = ntohl(nla_get_be32(cda[CTA_MARK]));
	newmark = (ct->mark & mask) ^ mark;
	अगर (newmark != ct->mark)
		ct->mark = newmark;
पूर्ण
#पूर्ण_अगर

अटल स्थिर काष्ठा nla_policy protoinfo_policy[CTA_PROTOINFO_MAX+1] = अणु
	[CTA_PROTOINFO_TCP]	= अणु .type = NLA_NESTED पूर्ण,
	[CTA_PROTOINFO_DCCP]	= अणु .type = NLA_NESTED पूर्ण,
	[CTA_PROTOINFO_SCTP]	= अणु .type = NLA_NESTED पूर्ण,
पूर्ण;

अटल पूर्णांक ctnetlink_change_protoinfo(काष्ठा nf_conn *ct,
				      स्थिर काष्ठा nlattr * स्थिर cda[])
अणु
	स्थिर काष्ठा nlattr *attr = cda[CTA_PROTOINFO];
	स्थिर काष्ठा nf_conntrack_l4proto *l4proto;
	काष्ठा nlattr *tb[CTA_PROTOINFO_MAX+1];
	पूर्णांक err = 0;

	err = nla_parse_nested_deprecated(tb, CTA_PROTOINFO_MAX, attr,
					  protoinfo_policy, शून्य);
	अगर (err < 0)
		वापस err;

	l4proto = nf_ct_l4proto_find(nf_ct_protonum(ct));
	अगर (l4proto->from_nlattr)
		err = l4proto->from_nlattr(tb, ct);

	वापस err;
पूर्ण

अटल स्थिर काष्ठा nla_policy seqadj_policy[CTA_SEQADJ_MAX+1] = अणु
	[CTA_SEQADJ_CORRECTION_POS]	= अणु .type = NLA_U32 पूर्ण,
	[CTA_SEQADJ_OFFSET_BEFORE]	= अणु .type = NLA_U32 पूर्ण,
	[CTA_SEQADJ_OFFSET_AFTER]	= अणु .type = NLA_U32 पूर्ण,
पूर्ण;

अटल पूर्णांक change_seq_adj(काष्ठा nf_ct_seqadj *seq,
			  स्थिर काष्ठा nlattr * स्थिर attr)
अणु
	पूर्णांक err;
	काष्ठा nlattr *cda[CTA_SEQADJ_MAX+1];

	err = nla_parse_nested_deprecated(cda, CTA_SEQADJ_MAX, attr,
					  seqadj_policy, शून्य);
	अगर (err < 0)
		वापस err;

	अगर (!cda[CTA_SEQADJ_CORRECTION_POS])
		वापस -EINVAL;

	seq->correction_pos =
		ntohl(nla_get_be32(cda[CTA_SEQADJ_CORRECTION_POS]));

	अगर (!cda[CTA_SEQADJ_OFFSET_BEFORE])
		वापस -EINVAL;

	seq->offset_beक्रमe =
		ntohl(nla_get_be32(cda[CTA_SEQADJ_OFFSET_BEFORE]));

	अगर (!cda[CTA_SEQADJ_OFFSET_AFTER])
		वापस -EINVAL;

	seq->offset_after =
		ntohl(nla_get_be32(cda[CTA_SEQADJ_OFFSET_AFTER]));

	वापस 0;
पूर्ण

अटल पूर्णांक
ctnetlink_change_seq_adj(काष्ठा nf_conn *ct,
			 स्थिर काष्ठा nlattr * स्थिर cda[])
अणु
	काष्ठा nf_conn_seqadj *seqadj = nfct_seqadj(ct);
	पूर्णांक ret = 0;

	अगर (!seqadj)
		वापस 0;

	spin_lock_bh(&ct->lock);
	अगर (cda[CTA_SEQ_ADJ_ORIG]) अणु
		ret = change_seq_adj(&seqadj->seq[IP_CT_सूची_ORIGINAL],
				     cda[CTA_SEQ_ADJ_ORIG]);
		अगर (ret < 0)
			जाओ err;

		set_bit(IPS_SEQ_ADJUST_BIT, &ct->status);
	पूर्ण

	अगर (cda[CTA_SEQ_ADJ_REPLY]) अणु
		ret = change_seq_adj(&seqadj->seq[IP_CT_सूची_REPLY],
				     cda[CTA_SEQ_ADJ_REPLY]);
		अगर (ret < 0)
			जाओ err;

		set_bit(IPS_SEQ_ADJUST_BIT, &ct->status);
	पूर्ण

	spin_unlock_bh(&ct->lock);
	वापस 0;
err:
	spin_unlock_bh(&ct->lock);
	वापस ret;
पूर्ण

अटल स्थिर काष्ठा nla_policy synproxy_policy[CTA_SYNPROXY_MAX + 1] = अणु
	[CTA_SYNPROXY_ISN]	= अणु .type = NLA_U32 पूर्ण,
	[CTA_SYNPROXY_ITS]	= अणु .type = NLA_U32 पूर्ण,
	[CTA_SYNPROXY_TSOFF]	= अणु .type = NLA_U32 पूर्ण,
पूर्ण;

अटल पूर्णांक ctnetlink_change_synproxy(काष्ठा nf_conn *ct,
				     स्थिर काष्ठा nlattr * स्थिर cda[])
अणु
	काष्ठा nf_conn_synproxy *synproxy = nfct_synproxy(ct);
	काष्ठा nlattr *tb[CTA_SYNPROXY_MAX + 1];
	पूर्णांक err;

	अगर (!synproxy)
		वापस 0;

	err = nla_parse_nested_deprecated(tb, CTA_SYNPROXY_MAX,
					  cda[CTA_SYNPROXY], synproxy_policy,
					  शून्य);
	अगर (err < 0)
		वापस err;

	अगर (!tb[CTA_SYNPROXY_ISN] ||
	    !tb[CTA_SYNPROXY_ITS] ||
	    !tb[CTA_SYNPROXY_TSOFF])
		वापस -EINVAL;

	synproxy->isn = ntohl(nla_get_be32(tb[CTA_SYNPROXY_ISN]));
	synproxy->its = ntohl(nla_get_be32(tb[CTA_SYNPROXY_ITS]));
	synproxy->tsoff = ntohl(nla_get_be32(tb[CTA_SYNPROXY_TSOFF]));

	वापस 0;
पूर्ण

अटल पूर्णांक
ctnetlink_attach_labels(काष्ठा nf_conn *ct, स्थिर काष्ठा nlattr * स्थिर cda[])
अणु
#अगर_घोषित CONFIG_NF_CONNTRACK_LABELS
	माप_प्रकार len = nla_len(cda[CTA_LABELS]);
	स्थिर व्योम *mask = cda[CTA_LABELS_MASK];

	अगर (len & (माप(u32)-1)) /* must be multiple of u32 */
		वापस -EINVAL;

	अगर (mask) अणु
		अगर (nla_len(cda[CTA_LABELS_MASK]) == 0 ||
		    nla_len(cda[CTA_LABELS_MASK]) != len)
			वापस -EINVAL;
		mask = nla_data(cda[CTA_LABELS_MASK]);
	पूर्ण

	len /= माप(u32);

	वापस nf_connlabels_replace(ct, nla_data(cda[CTA_LABELS]), mask, len);
#अन्यथा
	वापस -EOPNOTSUPP;
#पूर्ण_अगर
पूर्ण

अटल पूर्णांक
ctnetlink_change_conntrack(काष्ठा nf_conn *ct,
			   स्थिर काष्ठा nlattr * स्थिर cda[])
अणु
	पूर्णांक err;

	/* only allow NAT changes and master assignation क्रम new conntracks */
	अगर (cda[CTA_NAT_SRC] || cda[CTA_NAT_DST] || cda[CTA_TUPLE_MASTER])
		वापस -EOPNOTSUPP;

	अगर (cda[CTA_HELP]) अणु
		err = ctnetlink_change_helper(ct, cda);
		अगर (err < 0)
			वापस err;
	पूर्ण

	अगर (cda[CTA_TIMEOUT]) अणु
		err = ctnetlink_change_समयout(ct, cda);
		अगर (err < 0)
			वापस err;
	पूर्ण

	अगर (cda[CTA_STATUS]) अणु
		err = ctnetlink_change_status(ct, cda);
		अगर (err < 0)
			वापस err;
	पूर्ण

	अगर (cda[CTA_PROTOINFO]) अणु
		err = ctnetlink_change_protoinfo(ct, cda);
		अगर (err < 0)
			वापस err;
	पूर्ण

#अगर defined(CONFIG_NF_CONNTRACK_MARK)
	अगर (cda[CTA_MARK])
		ctnetlink_change_mark(ct, cda);
#पूर्ण_अगर

	अगर (cda[CTA_SEQ_ADJ_ORIG] || cda[CTA_SEQ_ADJ_REPLY]) अणु
		err = ctnetlink_change_seq_adj(ct, cda);
		अगर (err < 0)
			वापस err;
	पूर्ण

	अगर (cda[CTA_SYNPROXY]) अणु
		err = ctnetlink_change_synproxy(ct, cda);
		अगर (err < 0)
			वापस err;
	पूर्ण

	अगर (cda[CTA_LABELS]) अणु
		err = ctnetlink_attach_labels(ct, cda);
		अगर (err < 0)
			वापस err;
	पूर्ण

	वापस 0;
पूर्ण

अटल काष्ठा nf_conn *
ctnetlink_create_conntrack(काष्ठा net *net,
			   स्थिर काष्ठा nf_conntrack_zone *zone,
			   स्थिर काष्ठा nlattr * स्थिर cda[],
			   काष्ठा nf_conntrack_tuple *otuple,
			   काष्ठा nf_conntrack_tuple *rtuple,
			   u8 u3)
अणु
	काष्ठा nf_conn *ct;
	पूर्णांक err = -EINVAL;
	काष्ठा nf_conntrack_helper *helper;
	काष्ठा nf_conn_tstamp *tstamp;
	u64 समयout;

	ct = nf_conntrack_alloc(net, zone, otuple, rtuple, GFP_ATOMIC);
	अगर (IS_ERR(ct))
		वापस ERR_PTR(-ENOMEM);

	अगर (!cda[CTA_TIMEOUT])
		जाओ err1;

	समयout = (u64)ntohl(nla_get_be32(cda[CTA_TIMEOUT])) * HZ;
	अगर (समयout > पूर्णांक_उच्च)
		समयout = पूर्णांक_उच्च;
	ct->समयout = (u32)समयout + nfct_समय_stamp;

	rcu_पढ़ो_lock();
 	अगर (cda[CTA_HELP]) अणु
		अक्षर *helpname = शून्य;
		काष्ठा nlattr *helpinfo = शून्य;

		err = ctnetlink_parse_help(cda[CTA_HELP], &helpname, &helpinfo);
 		अगर (err < 0)
			जाओ err2;

		helper = __nf_conntrack_helper_find(helpname, nf_ct_l3num(ct),
						    nf_ct_protonum(ct));
		अगर (helper == शून्य) अणु
			rcu_पढ़ो_unlock();
#अगर_घोषित CONFIG_MODULES
			अगर (request_module("nfct-helper-%s", helpname) < 0) अणु
				err = -EOPNOTSUPP;
				जाओ err1;
			पूर्ण

			rcu_पढ़ो_lock();
			helper = __nf_conntrack_helper_find(helpname,
							    nf_ct_l3num(ct),
							    nf_ct_protonum(ct));
			अगर (helper) अणु
				err = -EAGAIN;
				जाओ err2;
			पूर्ण
			rcu_पढ़ो_unlock();
#पूर्ण_अगर
			err = -EOPNOTSUPP;
			जाओ err1;
		पूर्ण अन्यथा अणु
			काष्ठा nf_conn_help *help;

			help = nf_ct_helper_ext_add(ct, GFP_ATOMIC);
			अगर (help == शून्य) अणु
				err = -ENOMEM;
				जाओ err2;
			पूर्ण
			/* set निजी helper data अगर allowed. */
			अगर (helper->from_nlattr)
				helper->from_nlattr(helpinfo, ct);

			/* not in hash table yet so not strictly necessary */
			RCU_INIT_POINTER(help->helper, helper);
		पूर्ण
	पूर्ण अन्यथा अणु
		/* try an implicit helper assignation */
		err = __nf_ct_try_assign_helper(ct, शून्य, GFP_ATOMIC);
		अगर (err < 0)
			जाओ err2;
	पूर्ण

	err = ctnetlink_setup_nat(ct, cda);
	अगर (err < 0)
		जाओ err2;

	nf_ct_acct_ext_add(ct, GFP_ATOMIC);
	nf_ct_tstamp_ext_add(ct, GFP_ATOMIC);
	nf_ct_ecache_ext_add(ct, 0, 0, GFP_ATOMIC);
	nf_ct_labels_ext_add(ct);
	nfct_seqadj_ext_add(ct);
	nfct_synproxy_ext_add(ct);

	/* we must add conntrack extensions beक्रमe confirmation. */
	ct->status |= IPS_CONFIRMED;

	अगर (cda[CTA_STATUS]) अणु
		err = ctnetlink_change_status(ct, cda);
		अगर (err < 0)
			जाओ err2;
	पूर्ण

	अगर (cda[CTA_SEQ_ADJ_ORIG] || cda[CTA_SEQ_ADJ_REPLY]) अणु
		err = ctnetlink_change_seq_adj(ct, cda);
		अगर (err < 0)
			जाओ err2;
	पूर्ण

	स_रखो(&ct->proto, 0, माप(ct->proto));
	अगर (cda[CTA_PROTOINFO]) अणु
		err = ctnetlink_change_protoinfo(ct, cda);
		अगर (err < 0)
			जाओ err2;
	पूर्ण

	अगर (cda[CTA_SYNPROXY]) अणु
		err = ctnetlink_change_synproxy(ct, cda);
		अगर (err < 0)
			जाओ err2;
	पूर्ण

#अगर defined(CONFIG_NF_CONNTRACK_MARK)
	अगर (cda[CTA_MARK])
		ctnetlink_change_mark(ct, cda);
#पूर्ण_अगर

	/* setup master conntrack: this is a confirmed expectation */
	अगर (cda[CTA_TUPLE_MASTER]) अणु
		काष्ठा nf_conntrack_tuple master;
		काष्ठा nf_conntrack_tuple_hash *master_h;
		काष्ठा nf_conn *master_ct;

		err = ctnetlink_parse_tuple(cda, &master, CTA_TUPLE_MASTER,
					    u3, शून्य);
		अगर (err < 0)
			जाओ err2;

		master_h = nf_conntrack_find_get(net, zone, &master);
		अगर (master_h == शून्य) अणु
			err = -ENOENT;
			जाओ err2;
		पूर्ण
		master_ct = nf_ct_tuplehash_to_ctrack(master_h);
		__set_bit(IPS_EXPECTED_BIT, &ct->status);
		ct->master = master_ct;
	पूर्ण
	tstamp = nf_conn_tstamp_find(ct);
	अगर (tstamp)
		tstamp->start = kसमय_get_real_ns();

	err = nf_conntrack_hash_check_insert(ct);
	अगर (err < 0)
		जाओ err2;

	rcu_पढ़ो_unlock();

	वापस ct;

err2:
	rcu_पढ़ो_unlock();
err1:
	nf_conntrack_मुक्त(ct);
	वापस ERR_PTR(err);
पूर्ण

अटल पूर्णांक ctnetlink_new_conntrack(काष्ठा sk_buff *skb,
				   स्थिर काष्ठा nfnl_info *info,
				   स्थिर काष्ठा nlattr * स्थिर cda[])
अणु
	काष्ठा nfgenmsg *nfmsg = nlmsg_data(info->nlh);
	काष्ठा nf_conntrack_tuple otuple, rtuple;
	काष्ठा nf_conntrack_tuple_hash *h = शून्य;
	u_पूर्णांक8_t u3 = nfmsg->nfgen_family;
	काष्ठा nf_conntrack_zone zone;
	काष्ठा nf_conn *ct;
	पूर्णांक err;

	err = ctnetlink_parse_zone(cda[CTA_ZONE], &zone);
	अगर (err < 0)
		वापस err;

	अगर (cda[CTA_TUPLE_ORIG]) अणु
		err = ctnetlink_parse_tuple(cda, &otuple, CTA_TUPLE_ORIG,
					    u3, &zone);
		अगर (err < 0)
			वापस err;
	पूर्ण

	अगर (cda[CTA_TUPLE_REPLY]) अणु
		err = ctnetlink_parse_tuple(cda, &rtuple, CTA_TUPLE_REPLY,
					    u3, &zone);
		अगर (err < 0)
			वापस err;
	पूर्ण

	अगर (cda[CTA_TUPLE_ORIG])
		h = nf_conntrack_find_get(info->net, &zone, &otuple);
	अन्यथा अगर (cda[CTA_TUPLE_REPLY])
		h = nf_conntrack_find_get(info->net, &zone, &rtuple);

	अगर (h == शून्य) अणु
		err = -ENOENT;
		अगर (info->nlh->nlmsg_flags & NLM_F_CREATE) अणु
			क्रमागत ip_conntrack_events events;

			अगर (!cda[CTA_TUPLE_ORIG] || !cda[CTA_TUPLE_REPLY])
				वापस -EINVAL;
			अगर (otuple.dst.protonum != rtuple.dst.protonum)
				वापस -EINVAL;

			ct = ctnetlink_create_conntrack(info->net, &zone, cda,
							&otuple, &rtuple, u3);
			अगर (IS_ERR(ct))
				वापस PTR_ERR(ct);

			err = 0;
			अगर (test_bit(IPS_EXPECTED_BIT, &ct->status))
				events = 1 << IPCT_RELATED;
			अन्यथा
				events = 1 << IPCT_NEW;

			अगर (cda[CTA_LABELS] &&
			    ctnetlink_attach_labels(ct, cda) == 0)
				events |= (1 << IPCT_LABEL);

			nf_conntrack_evenपंचांगask_report((1 << IPCT_REPLY) |
						      (1 << IPCT_ASSURED) |
						      (1 << IPCT_HELPER) |
						      (1 << IPCT_PROTOINFO) |
						      (1 << IPCT_SEQADJ) |
						      (1 << IPCT_MARK) |
						      (1 << IPCT_SYNPROXY) |
						      events,
						      ct, NETLINK_CB(skb).portid,
						      nlmsg_report(info->nlh));
			nf_ct_put(ct);
		पूर्ण

		वापस err;
	पूर्ण
	/* implicit 'else' */

	err = -EEXIST;
	ct = nf_ct_tuplehash_to_ctrack(h);
	अगर (!(info->nlh->nlmsg_flags & NLM_F_EXCL)) अणु
		err = ctnetlink_change_conntrack(ct, cda);
		अगर (err == 0) अणु
			nf_conntrack_evenपंचांगask_report((1 << IPCT_REPLY) |
						      (1 << IPCT_ASSURED) |
						      (1 << IPCT_HELPER) |
						      (1 << IPCT_LABEL) |
						      (1 << IPCT_PROTOINFO) |
						      (1 << IPCT_SEQADJ) |
						      (1 << IPCT_MARK) |
						      (1 << IPCT_SYNPROXY),
						      ct, NETLINK_CB(skb).portid,
						      nlmsg_report(info->nlh));
		पूर्ण
	पूर्ण

	nf_ct_put(ct);
	वापस err;
पूर्ण

अटल पूर्णांक
ctnetlink_ct_stat_cpu_fill_info(काष्ठा sk_buff *skb, u32 portid, u32 seq,
				__u16 cpu, स्थिर काष्ठा ip_conntrack_stat *st)
अणु
	काष्ठा nlmsghdr *nlh;
	अचिन्हित पूर्णांक flags = portid ? NLM_F_MULTI : 0, event;

	event = nfnl_msg_type(NFNL_SUBSYS_CTNETLINK,
			      IPCTNL_MSG_CT_GET_STATS_CPU);
	nlh = nfnl_msg_put(skb, portid, seq, event, flags, AF_UNSPEC,
			   NFNETLINK_V0, htons(cpu));
	अगर (!nlh)
		जाओ nlmsg_failure;

	अगर (nla_put_be32(skb, CTA_STATS_FOUND, htonl(st->found)) ||
	    nla_put_be32(skb, CTA_STATS_INVALID, htonl(st->invalid)) ||
	    nla_put_be32(skb, CTA_STATS_INSERT, htonl(st->insert)) ||
	    nla_put_be32(skb, CTA_STATS_INSERT_FAILED,
				htonl(st->insert_failed)) ||
	    nla_put_be32(skb, CTA_STATS_DROP, htonl(st->drop)) ||
	    nla_put_be32(skb, CTA_STATS_EARLY_DROP, htonl(st->early_drop)) ||
	    nla_put_be32(skb, CTA_STATS_ERROR, htonl(st->error)) ||
	    nla_put_be32(skb, CTA_STATS_SEARCH_RESTART,
				htonl(st->search_restart)) ||
	    nla_put_be32(skb, CTA_STATS_CLASH_RESOLVE,
				htonl(st->clash_resolve)))
		जाओ nla_put_failure;

	nlmsg_end(skb, nlh);
	वापस skb->len;

nla_put_failure:
nlmsg_failure:
	nlmsg_cancel(skb, nlh);
	वापस -1;
पूर्ण

अटल पूर्णांक
ctnetlink_ct_stat_cpu_dump(काष्ठा sk_buff *skb, काष्ठा netlink_callback *cb)
अणु
	पूर्णांक cpu;
	काष्ठा net *net = sock_net(skb->sk);

	अगर (cb->args[0] == nr_cpu_ids)
		वापस 0;

	क्रम (cpu = cb->args[0]; cpu < nr_cpu_ids; cpu++) अणु
		स्थिर काष्ठा ip_conntrack_stat *st;

		अगर (!cpu_possible(cpu))
			जारी;

		st = per_cpu_ptr(net->ct.stat, cpu);
		अगर (ctnetlink_ct_stat_cpu_fill_info(skb,
						    NETLINK_CB(cb->skb).portid,
						    cb->nlh->nlmsg_seq,
						    cpu, st) < 0)
				अवरोध;
	पूर्ण
	cb->args[0] = cpu;

	वापस skb->len;
पूर्ण

अटल पूर्णांक ctnetlink_stat_ct_cpu(काष्ठा sk_buff *skb,
				 स्थिर काष्ठा nfnl_info *info,
				 स्थिर काष्ठा nlattr * स्थिर cda[])
अणु
	अगर (info->nlh->nlmsg_flags & NLM_F_DUMP) अणु
		काष्ठा netlink_dump_control c = अणु
			.dump = ctnetlink_ct_stat_cpu_dump,
		पूर्ण;
		वापस netlink_dump_start(info->sk, skb, info->nlh, &c);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक
ctnetlink_stat_ct_fill_info(काष्ठा sk_buff *skb, u32 portid, u32 seq, u32 type,
			    काष्ठा net *net)
अणु
	अचिन्हित पूर्णांक flags = portid ? NLM_F_MULTI : 0, event;
	अचिन्हित पूर्णांक nr_conntracks;
	काष्ठा nlmsghdr *nlh;

	event = nfnl_msg_type(NFNL_SUBSYS_CTNETLINK, IPCTNL_MSG_CT_GET_STATS);
	nlh = nfnl_msg_put(skb, portid, seq, event, flags, AF_UNSPEC,
			   NFNETLINK_V0, 0);
	अगर (!nlh)
		जाओ nlmsg_failure;

	nr_conntracks = nf_conntrack_count(net);
	अगर (nla_put_be32(skb, CTA_STATS_GLOBAL_ENTRIES, htonl(nr_conntracks)))
		जाओ nla_put_failure;

	अगर (nla_put_be32(skb, CTA_STATS_GLOBAL_MAX_ENTRIES, htonl(nf_conntrack_max)))
		जाओ nla_put_failure;

	nlmsg_end(skb, nlh);
	वापस skb->len;

nla_put_failure:
nlmsg_failure:
	nlmsg_cancel(skb, nlh);
	वापस -1;
पूर्ण

अटल पूर्णांक ctnetlink_stat_ct(काष्ठा sk_buff *skb, स्थिर काष्ठा nfnl_info *info,
			     स्थिर काष्ठा nlattr * स्थिर cda[])
अणु
	काष्ठा sk_buff *skb2;
	पूर्णांक err;

	skb2 = nlmsg_new(NLMSG_DEFAULT_SIZE, GFP_KERNEL);
	अगर (skb2 == शून्य)
		वापस -ENOMEM;

	err = ctnetlink_stat_ct_fill_info(skb2, NETLINK_CB(skb).portid,
					  info->nlh->nlmsg_seq,
					  NFNL_MSG_TYPE(info->nlh->nlmsg_type),
					  sock_net(skb->sk));
	अगर (err <= 0)
		जाओ मुक्त;

	err = netlink_unicast(info->sk, skb2, NETLINK_CB(skb).portid,
			      MSG_DONTWAIT);
	अगर (err < 0)
		जाओ out;

	वापस 0;

मुक्त:
	kमुक्त_skb(skb2);
out:
	/* this aव्योमs a loop in nfnetlink. */
	वापस err == -EAGAIN ? -ENOBUFS : err;
पूर्ण

अटल स्थिर काष्ठा nla_policy exp_nla_policy[CTA_EXPECT_MAX+1] = अणु
	[CTA_EXPECT_MASTER]	= अणु .type = NLA_NESTED पूर्ण,
	[CTA_EXPECT_TUPLE]	= अणु .type = NLA_NESTED पूर्ण,
	[CTA_EXPECT_MASK]	= अणु .type = NLA_NESTED पूर्ण,
	[CTA_EXPECT_TIMEOUT]	= अणु .type = NLA_U32 पूर्ण,
	[CTA_EXPECT_ID]		= अणु .type = NLA_U32 पूर्ण,
	[CTA_EXPECT_HELP_NAME]	= अणु .type = NLA_NUL_STRING,
				    .len = NF_CT_HELPER_NAME_LEN - 1 पूर्ण,
	[CTA_EXPECT_ZONE]	= अणु .type = NLA_U16 पूर्ण,
	[CTA_EXPECT_FLAGS]	= अणु .type = NLA_U32 पूर्ण,
	[CTA_EXPECT_CLASS]	= अणु .type = NLA_U32 पूर्ण,
	[CTA_EXPECT_NAT]	= अणु .type = NLA_NESTED पूर्ण,
	[CTA_EXPECT_FN]		= अणु .type = NLA_NUL_STRING पूर्ण,
पूर्ण;

अटल काष्ठा nf_conntrack_expect *
ctnetlink_alloc_expect(स्थिर काष्ठा nlattr *स्थिर cda[], काष्ठा nf_conn *ct,
		       काष्ठा nf_conntrack_helper *helper,
		       काष्ठा nf_conntrack_tuple *tuple,
		       काष्ठा nf_conntrack_tuple *mask);

#अगर_घोषित CONFIG_NETFILTER_NETLINK_GLUE_CT
अटल माप_प्रकार
ctnetlink_glue_build_size(स्थिर काष्ठा nf_conn *ct)
अणु
	वापस 3 * nla_total_size(0) /* CTA_TUPLE_ORIG|REPL|MASTER */
	       + 3 * nla_total_size(0) /* CTA_TUPLE_IP */
	       + 3 * nla_total_size(0) /* CTA_TUPLE_PROTO */
	       + 3 * nla_total_size(माप(u_पूर्णांक8_t)) /* CTA_PROTO_NUM */
	       + nla_total_size(माप(u_पूर्णांक32_t)) /* CTA_ID */
	       + nla_total_size(माप(u_पूर्णांक32_t)) /* CTA_STATUS */
	       + nla_total_size(माप(u_पूर्णांक32_t)) /* CTA_TIMEOUT */
	       + nla_total_size(0) /* CTA_PROTOINFO */
	       + nla_total_size(0) /* CTA_HELP */
	       + nla_total_size(NF_CT_HELPER_NAME_LEN) /* CTA_HELP_NAME */
	       + ctnetlink_secctx_size(ct)
#अगर IS_ENABLED(CONFIG_NF_NAT)
	       + 2 * nla_total_size(0) /* CTA_NAT_SEQ_ADJ_ORIG|REPL */
	       + 6 * nla_total_size(माप(u_पूर्णांक32_t)) /* CTA_NAT_SEQ_OFFSET */
#पूर्ण_अगर
#अगर_घोषित CONFIG_NF_CONNTRACK_MARK
	       + nla_total_size(माप(u_पूर्णांक32_t)) /* CTA_MARK */
#पूर्ण_अगर
#अगर_घोषित CONFIG_NF_CONNTRACK_ZONES
	       + nla_total_size(माप(u_पूर्णांक16_t)) /* CTA_ZONE|CTA_TUPLE_ZONE */
#पूर्ण_अगर
	       + ctnetlink_proto_size(ct)
	       ;
पूर्ण

अटल पूर्णांक __ctnetlink_glue_build(काष्ठा sk_buff *skb, काष्ठा nf_conn *ct)
अणु
	स्थिर काष्ठा nf_conntrack_zone *zone;
	काष्ठा nlattr *nest_parms;

	zone = nf_ct_zone(ct);

	nest_parms = nla_nest_start(skb, CTA_TUPLE_ORIG);
	अगर (!nest_parms)
		जाओ nla_put_failure;
	अगर (ctnetlink_dump_tuples(skb, nf_ct_tuple(ct, IP_CT_सूची_ORIGINAL)) < 0)
		जाओ nla_put_failure;
	अगर (ctnetlink_dump_zone_id(skb, CTA_TUPLE_ZONE, zone,
				   NF_CT_ZONE_सूची_ORIG) < 0)
		जाओ nla_put_failure;
	nla_nest_end(skb, nest_parms);

	nest_parms = nla_nest_start(skb, CTA_TUPLE_REPLY);
	अगर (!nest_parms)
		जाओ nla_put_failure;
	अगर (ctnetlink_dump_tuples(skb, nf_ct_tuple(ct, IP_CT_सूची_REPLY)) < 0)
		जाओ nla_put_failure;
	अगर (ctnetlink_dump_zone_id(skb, CTA_TUPLE_ZONE, zone,
				   NF_CT_ZONE_सूची_REPL) < 0)
		जाओ nla_put_failure;
	nla_nest_end(skb, nest_parms);

	अगर (ctnetlink_dump_zone_id(skb, CTA_ZONE, zone,
				   NF_CT_DEFAULT_ZONE_सूची) < 0)
		जाओ nla_put_failure;

	अगर (ctnetlink_dump_id(skb, ct) < 0)
		जाओ nla_put_failure;

	अगर (ctnetlink_dump_status(skb, ct) < 0)
		जाओ nla_put_failure;

	अगर (ctnetlink_dump_समयout(skb, ct, false) < 0)
		जाओ nla_put_failure;

	अगर (ctnetlink_dump_protoinfo(skb, ct, false) < 0)
		जाओ nla_put_failure;

	अगर (ctnetlink_dump_helpinfo(skb, ct) < 0)
		जाओ nla_put_failure;

#अगर_घोषित CONFIG_NF_CONNTRACK_SECMARK
	अगर (ct->secmark && ctnetlink_dump_secctx(skb, ct) < 0)
		जाओ nla_put_failure;
#पूर्ण_अगर
	अगर (ct->master && ctnetlink_dump_master(skb, ct) < 0)
		जाओ nla_put_failure;

	अगर ((ct->status & IPS_SEQ_ADJUST) &&
	    ctnetlink_dump_ct_seq_adj(skb, ct) < 0)
		जाओ nla_put_failure;

	अगर (ctnetlink_dump_ct_synproxy(skb, ct) < 0)
		जाओ nla_put_failure;

#अगर_घोषित CONFIG_NF_CONNTRACK_MARK
	अगर (ct->mark && ctnetlink_dump_mark(skb, ct) < 0)
		जाओ nla_put_failure;
#पूर्ण_अगर
	अगर (ctnetlink_dump_labels(skb, ct) < 0)
		जाओ nla_put_failure;
	वापस 0;

nla_put_failure:
	वापस -ENOSPC;
पूर्ण

अटल पूर्णांक
ctnetlink_glue_build(काष्ठा sk_buff *skb, काष्ठा nf_conn *ct,
		     क्रमागत ip_conntrack_info ctinfo,
		     u_पूर्णांक16_t ct_attr, u_पूर्णांक16_t ct_info_attr)
अणु
	काष्ठा nlattr *nest_parms;

	nest_parms = nla_nest_start(skb, ct_attr);
	अगर (!nest_parms)
		जाओ nla_put_failure;

	अगर (__ctnetlink_glue_build(skb, ct) < 0)
		जाओ nla_put_failure;

	nla_nest_end(skb, nest_parms);

	अगर (nla_put_be32(skb, ct_info_attr, htonl(ctinfo)))
		जाओ nla_put_failure;

	वापस 0;

nla_put_failure:
	वापस -ENOSPC;
पूर्ण

अटल पूर्णांक
ctnetlink_update_status(काष्ठा nf_conn *ct, स्थिर काष्ठा nlattr * स्थिर cda[])
अणु
	अचिन्हित पूर्णांक status = ntohl(nla_get_be32(cda[CTA_STATUS]));
	अचिन्हित दीर्घ d = ct->status ^ status;

	अगर (d & IPS_SEEN_REPLY && !(status & IPS_SEEN_REPLY))
		/* SEEN_REPLY bit can only be set */
		वापस -EBUSY;

	अगर (d & IPS_ASSURED && !(status & IPS_ASSURED))
		/* ASSURED bit can only be set */
		वापस -EBUSY;

	/* This check is less strict than ctnetlink_change_status()
	 * because callers often flip IPS_EXPECTED bits when sending
	 * an NFQA_CT attribute to the kernel.  So ignore the
	 * unchangeable bits but करो not error out. Also user programs
	 * are allowed to clear the bits that they are allowed to change.
	 */
	__ctnetlink_change_status(ct, status, ~status);
	वापस 0;
पूर्ण

अटल पूर्णांक
ctnetlink_glue_parse_ct(स्थिर काष्ठा nlattr *cda[], काष्ठा nf_conn *ct)
अणु
	पूर्णांक err;

	अगर (cda[CTA_TIMEOUT]) अणु
		err = ctnetlink_change_समयout(ct, cda);
		अगर (err < 0)
			वापस err;
	पूर्ण
	अगर (cda[CTA_STATUS]) अणु
		err = ctnetlink_update_status(ct, cda);
		अगर (err < 0)
			वापस err;
	पूर्ण
	अगर (cda[CTA_HELP]) अणु
		err = ctnetlink_change_helper(ct, cda);
		अगर (err < 0)
			वापस err;
	पूर्ण
	अगर (cda[CTA_LABELS]) अणु
		err = ctnetlink_attach_labels(ct, cda);
		अगर (err < 0)
			वापस err;
	पूर्ण
#अगर defined(CONFIG_NF_CONNTRACK_MARK)
	अगर (cda[CTA_MARK]) अणु
		ctnetlink_change_mark(ct, cda);
	पूर्ण
#पूर्ण_अगर
	वापस 0;
पूर्ण

अटल पूर्णांक
ctnetlink_glue_parse(स्थिर काष्ठा nlattr *attr, काष्ठा nf_conn *ct)
अणु
	काष्ठा nlattr *cda[CTA_MAX+1];
	पूर्णांक ret;

	ret = nla_parse_nested_deprecated(cda, CTA_MAX, attr, ct_nla_policy,
					  शून्य);
	अगर (ret < 0)
		वापस ret;

	वापस ctnetlink_glue_parse_ct((स्थिर काष्ठा nlattr **)cda, ct);
पूर्ण

अटल पूर्णांक ctnetlink_glue_exp_parse(स्थिर काष्ठा nlattr * स्थिर *cda,
				    स्थिर काष्ठा nf_conn *ct,
				    काष्ठा nf_conntrack_tuple *tuple,
				    काष्ठा nf_conntrack_tuple *mask)
अणु
	पूर्णांक err;

	err = ctnetlink_parse_tuple(cda, tuple, CTA_EXPECT_TUPLE,
				    nf_ct_l3num(ct), शून्य);
	अगर (err < 0)
		वापस err;

	वापस ctnetlink_parse_tuple(cda, mask, CTA_EXPECT_MASK,
				     nf_ct_l3num(ct), शून्य);
पूर्ण

अटल पूर्णांक
ctnetlink_glue_attach_expect(स्थिर काष्ठा nlattr *attr, काष्ठा nf_conn *ct,
			     u32 portid, u32 report)
अणु
	काष्ठा nlattr *cda[CTA_EXPECT_MAX+1];
	काष्ठा nf_conntrack_tuple tuple, mask;
	काष्ठा nf_conntrack_helper *helper = शून्य;
	काष्ठा nf_conntrack_expect *exp;
	पूर्णांक err;

	err = nla_parse_nested_deprecated(cda, CTA_EXPECT_MAX, attr,
					  exp_nla_policy, शून्य);
	अगर (err < 0)
		वापस err;

	err = ctnetlink_glue_exp_parse((स्थिर काष्ठा nlattr * स्थिर *)cda,
				       ct, &tuple, &mask);
	अगर (err < 0)
		वापस err;

	अगर (cda[CTA_EXPECT_HELP_NAME]) अणु
		स्थिर अक्षर *helpname = nla_data(cda[CTA_EXPECT_HELP_NAME]);

		helper = __nf_conntrack_helper_find(helpname, nf_ct_l3num(ct),
						    nf_ct_protonum(ct));
		अगर (helper == शून्य)
			वापस -EOPNOTSUPP;
	पूर्ण

	exp = ctnetlink_alloc_expect((स्थिर काष्ठा nlattr * स्थिर *)cda, ct,
				     helper, &tuple, &mask);
	अगर (IS_ERR(exp))
		वापस PTR_ERR(exp);

	err = nf_ct_expect_related_report(exp, portid, report, 0);
	nf_ct_expect_put(exp);
	वापस err;
पूर्ण

अटल व्योम ctnetlink_glue_seqadj(काष्ठा sk_buff *skb, काष्ठा nf_conn *ct,
				  क्रमागत ip_conntrack_info ctinfo, पूर्णांक dअगरf)
अणु
	अगर (!(ct->status & IPS_NAT_MASK))
		वापस;

	nf_ct_tcp_seqadj_set(skb, ct, ctinfo, dअगरf);
पूर्ण

अटल काष्ठा nfnl_ct_hook ctnetlink_glue_hook = अणु
	.build_size	= ctnetlink_glue_build_size,
	.build		= ctnetlink_glue_build,
	.parse		= ctnetlink_glue_parse,
	.attach_expect	= ctnetlink_glue_attach_expect,
	.seq_adjust	= ctnetlink_glue_seqadj,
पूर्ण;
#पूर्ण_अगर /* CONFIG_NETFILTER_NETLINK_GLUE_CT */

/***********************************************************************
 * EXPECT
 ***********************************************************************/

अटल पूर्णांक ctnetlink_exp_dump_tuple(काष्ठा sk_buff *skb,
				    स्थिर काष्ठा nf_conntrack_tuple *tuple,
				    u32 type)
अणु
	काष्ठा nlattr *nest_parms;

	nest_parms = nla_nest_start(skb, type);
	अगर (!nest_parms)
		जाओ nla_put_failure;
	अगर (ctnetlink_dump_tuples(skb, tuple) < 0)
		जाओ nla_put_failure;
	nla_nest_end(skb, nest_parms);

	वापस 0;

nla_put_failure:
	वापस -1;
पूर्ण

अटल पूर्णांक ctnetlink_exp_dump_mask(काष्ठा sk_buff *skb,
				   स्थिर काष्ठा nf_conntrack_tuple *tuple,
				   स्थिर काष्ठा nf_conntrack_tuple_mask *mask)
अणु
	स्थिर काष्ठा nf_conntrack_l4proto *l4proto;
	काष्ठा nf_conntrack_tuple m;
	काष्ठा nlattr *nest_parms;
	पूर्णांक ret;

	स_रखो(&m, 0xFF, माप(m));
	स_नकल(&m.src.u3, &mask->src.u3, माप(m.src.u3));
	m.src.u.all = mask->src.u.all;
	m.src.l3num = tuple->src.l3num;
	m.dst.protonum = tuple->dst.protonum;

	nest_parms = nla_nest_start(skb, CTA_EXPECT_MASK);
	अगर (!nest_parms)
		जाओ nla_put_failure;

	rcu_पढ़ो_lock();
	ret = ctnetlink_dump_tuples_ip(skb, &m);
	अगर (ret >= 0) अणु
		l4proto = nf_ct_l4proto_find(tuple->dst.protonum);
		ret = ctnetlink_dump_tuples_proto(skb, &m, l4proto);
	पूर्ण
	rcu_पढ़ो_unlock();

	अगर (unlikely(ret < 0))
		जाओ nla_put_failure;

	nla_nest_end(skb, nest_parms);

	वापस 0;

nla_put_failure:
	वापस -1;
पूर्ण

अटल स्थिर जोड़ nf_inet_addr any_addr;

अटल __be32 nf_expect_get_id(स्थिर काष्ठा nf_conntrack_expect *exp)
अणु
	अटल __पढ़ो_mostly siphash_key_t exp_id_seed;
	अचिन्हित दीर्घ a, b, c, d;

	net_get_अक्रमom_once(&exp_id_seed, माप(exp_id_seed));

	a = (अचिन्हित दीर्घ)exp;
	b = (अचिन्हित दीर्घ)exp->helper;
	c = (अचिन्हित दीर्घ)exp->master;
	d = (अचिन्हित दीर्घ)siphash(&exp->tuple, माप(exp->tuple), &exp_id_seed);

#अगर_घोषित CONFIG_64BIT
	वापस (__क्रमce __be32)siphash_4u64((u64)a, (u64)b, (u64)c, (u64)d, &exp_id_seed);
#अन्यथा
	वापस (__क्रमce __be32)siphash_4u32((u32)a, (u32)b, (u32)c, (u32)d, &exp_id_seed);
#पूर्ण_अगर
पूर्ण

अटल पूर्णांक
ctnetlink_exp_dump_expect(काष्ठा sk_buff *skb,
			  स्थिर काष्ठा nf_conntrack_expect *exp)
अणु
	काष्ठा nf_conn *master = exp->master;
	दीर्घ समयout = ((दीर्घ)exp->समयout.expires - (दीर्घ)jअगरfies) / HZ;
	काष्ठा nf_conn_help *help;
#अगर IS_ENABLED(CONFIG_NF_NAT)
	काष्ठा nlattr *nest_parms;
	काष्ठा nf_conntrack_tuple nat_tuple = अणुपूर्ण;
#पूर्ण_अगर
	काष्ठा nf_ct_helper_expectfn *expfn;

	अगर (समयout < 0)
		समयout = 0;

	अगर (ctnetlink_exp_dump_tuple(skb, &exp->tuple, CTA_EXPECT_TUPLE) < 0)
		जाओ nla_put_failure;
	अगर (ctnetlink_exp_dump_mask(skb, &exp->tuple, &exp->mask) < 0)
		जाओ nla_put_failure;
	अगर (ctnetlink_exp_dump_tuple(skb,
				 &master->tuplehash[IP_CT_सूची_ORIGINAL].tuple,
				 CTA_EXPECT_MASTER) < 0)
		जाओ nla_put_failure;

#अगर IS_ENABLED(CONFIG_NF_NAT)
	अगर (!nf_inet_addr_cmp(&exp->saved_addr, &any_addr) ||
	    exp->saved_proto.all) अणु
		nest_parms = nla_nest_start(skb, CTA_EXPECT_NAT);
		अगर (!nest_parms)
			जाओ nla_put_failure;

		अगर (nla_put_be32(skb, CTA_EXPECT_NAT_सूची, htonl(exp->dir)))
			जाओ nla_put_failure;

		nat_tuple.src.l3num = nf_ct_l3num(master);
		nat_tuple.src.u3 = exp->saved_addr;
		nat_tuple.dst.protonum = nf_ct_protonum(master);
		nat_tuple.src.u = exp->saved_proto;

		अगर (ctnetlink_exp_dump_tuple(skb, &nat_tuple,
						CTA_EXPECT_NAT_TUPLE) < 0)
	                जाओ nla_put_failure;
	        nla_nest_end(skb, nest_parms);
	पूर्ण
#पूर्ण_अगर
	अगर (nla_put_be32(skb, CTA_EXPECT_TIMEOUT, htonl(समयout)) ||
	    nla_put_be32(skb, CTA_EXPECT_ID, nf_expect_get_id(exp)) ||
	    nla_put_be32(skb, CTA_EXPECT_FLAGS, htonl(exp->flags)) ||
	    nla_put_be32(skb, CTA_EXPECT_CLASS, htonl(exp->class)))
		जाओ nla_put_failure;
	help = nfct_help(master);
	अगर (help) अणु
		काष्ठा nf_conntrack_helper *helper;

		helper = rcu_dereference(help->helper);
		अगर (helper &&
		    nla_put_string(skb, CTA_EXPECT_HELP_NAME, helper->name))
			जाओ nla_put_failure;
	पूर्ण
	expfn = nf_ct_helper_expectfn_find_by_symbol(exp->expectfn);
	अगर (expfn != शून्य &&
	    nla_put_string(skb, CTA_EXPECT_FN, expfn->name))
		जाओ nla_put_failure;

	वापस 0;

nla_put_failure:
	वापस -1;
पूर्ण

अटल पूर्णांक
ctnetlink_exp_fill_info(काष्ठा sk_buff *skb, u32 portid, u32 seq,
			पूर्णांक event, स्थिर काष्ठा nf_conntrack_expect *exp)
अणु
	काष्ठा nlmsghdr *nlh;
	अचिन्हित पूर्णांक flags = portid ? NLM_F_MULTI : 0;

	event = nfnl_msg_type(NFNL_SUBSYS_CTNETLINK_EXP, event);
	nlh = nfnl_msg_put(skb, portid, seq, event, flags,
			   exp->tuple.src.l3num, NFNETLINK_V0, 0);
	अगर (!nlh)
		जाओ nlmsg_failure;

	अगर (ctnetlink_exp_dump_expect(skb, exp) < 0)
		जाओ nla_put_failure;

	nlmsg_end(skb, nlh);
	वापस skb->len;

nlmsg_failure:
nla_put_failure:
	nlmsg_cancel(skb, nlh);
	वापस -1;
पूर्ण

#अगर_घोषित CONFIG_NF_CONNTRACK_EVENTS
अटल पूर्णांक
ctnetlink_expect_event(अचिन्हित पूर्णांक events, काष्ठा nf_exp_event *item)
अणु
	काष्ठा nf_conntrack_expect *exp = item->exp;
	काष्ठा net *net = nf_ct_exp_net(exp);
	काष्ठा nlmsghdr *nlh;
	काष्ठा sk_buff *skb;
	अचिन्हित पूर्णांक type, group;
	पूर्णांक flags = 0;

	अगर (events & (1 << IPEXP_DESTROY)) अणु
		type = IPCTNL_MSG_EXP_DELETE;
		group = NFNLGRP_CONNTRACK_EXP_DESTROY;
	पूर्ण अन्यथा अगर (events & (1 << IPEXP_NEW)) अणु
		type = IPCTNL_MSG_EXP_NEW;
		flags = NLM_F_CREATE|NLM_F_EXCL;
		group = NFNLGRP_CONNTRACK_EXP_NEW;
	पूर्ण अन्यथा
		वापस 0;

	अगर (!item->report && !nfnetlink_has_listeners(net, group))
		वापस 0;

	skb = nlmsg_new(NLMSG_DEFAULT_SIZE, GFP_ATOMIC);
	अगर (skb == शून्य)
		जाओ errout;

	type = nfnl_msg_type(NFNL_SUBSYS_CTNETLINK_EXP, type);
	nlh = nfnl_msg_put(skb, item->portid, 0, type, flags,
			   exp->tuple.src.l3num, NFNETLINK_V0, 0);
	अगर (!nlh)
		जाओ nlmsg_failure;

	अगर (ctnetlink_exp_dump_expect(skb, exp) < 0)
		जाओ nla_put_failure;

	nlmsg_end(skb, nlh);
	nfnetlink_send(skb, net, item->portid, group, item->report, GFP_ATOMIC);
	वापस 0;

nla_put_failure:
	nlmsg_cancel(skb, nlh);
nlmsg_failure:
	kमुक्त_skb(skb);
errout:
	nfnetlink_set_err(net, 0, 0, -ENOBUFS);
	वापस 0;
पूर्ण
#पूर्ण_अगर
अटल पूर्णांक ctnetlink_exp_करोne(काष्ठा netlink_callback *cb)
अणु
	अगर (cb->args[1])
		nf_ct_expect_put((काष्ठा nf_conntrack_expect *)cb->args[1]);
	वापस 0;
पूर्ण

अटल पूर्णांक
ctnetlink_exp_dump_table(काष्ठा sk_buff *skb, काष्ठा netlink_callback *cb)
अणु
	काष्ठा net *net = sock_net(skb->sk);
	काष्ठा nf_conntrack_expect *exp, *last;
	काष्ठा nfgenmsg *nfmsg = nlmsg_data(cb->nlh);
	u_पूर्णांक8_t l3proto = nfmsg->nfgen_family;

	rcu_पढ़ो_lock();
	last = (काष्ठा nf_conntrack_expect *)cb->args[1];
	क्रम (; cb->args[0] < nf_ct_expect_hsize; cb->args[0]++) अणु
restart:
		hlist_क्रम_each_entry_rcu(exp, &nf_ct_expect_hash[cb->args[0]],
					 hnode) अणु
			अगर (l3proto && exp->tuple.src.l3num != l3proto)
				जारी;

			अगर (!net_eq(nf_ct_net(exp->master), net))
				जारी;

			अगर (cb->args[1]) अणु
				अगर (exp != last)
					जारी;
				cb->args[1] = 0;
			पूर्ण
			अगर (ctnetlink_exp_fill_info(skb,
						    NETLINK_CB(cb->skb).portid,
						    cb->nlh->nlmsg_seq,
						    IPCTNL_MSG_EXP_NEW,
						    exp) < 0) अणु
				अगर (!refcount_inc_not_zero(&exp->use))
					जारी;
				cb->args[1] = (अचिन्हित दीर्घ)exp;
				जाओ out;
			पूर्ण
		पूर्ण
		अगर (cb->args[1]) अणु
			cb->args[1] = 0;
			जाओ restart;
		पूर्ण
	पूर्ण
out:
	rcu_पढ़ो_unlock();
	अगर (last)
		nf_ct_expect_put(last);

	वापस skb->len;
पूर्ण

अटल पूर्णांक
ctnetlink_exp_ct_dump_table(काष्ठा sk_buff *skb, काष्ठा netlink_callback *cb)
अणु
	काष्ठा nf_conntrack_expect *exp, *last;
	काष्ठा nfgenmsg *nfmsg = nlmsg_data(cb->nlh);
	काष्ठा nf_conn *ct = cb->data;
	काष्ठा nf_conn_help *help = nfct_help(ct);
	u_पूर्णांक8_t l3proto = nfmsg->nfgen_family;

	अगर (cb->args[0])
		वापस 0;

	rcu_पढ़ो_lock();
	last = (काष्ठा nf_conntrack_expect *)cb->args[1];
restart:
	hlist_क्रम_each_entry_rcu(exp, &help->expectations, lnode) अणु
		अगर (l3proto && exp->tuple.src.l3num != l3proto)
			जारी;
		अगर (cb->args[1]) अणु
			अगर (exp != last)
				जारी;
			cb->args[1] = 0;
		पूर्ण
		अगर (ctnetlink_exp_fill_info(skb, NETLINK_CB(cb->skb).portid,
					    cb->nlh->nlmsg_seq,
					    IPCTNL_MSG_EXP_NEW,
					    exp) < 0) अणु
			अगर (!refcount_inc_not_zero(&exp->use))
				जारी;
			cb->args[1] = (अचिन्हित दीर्घ)exp;
			जाओ out;
		पूर्ण
	पूर्ण
	अगर (cb->args[1]) अणु
		cb->args[1] = 0;
		जाओ restart;
	पूर्ण
	cb->args[0] = 1;
out:
	rcu_पढ़ो_unlock();
	अगर (last)
		nf_ct_expect_put(last);

	वापस skb->len;
पूर्ण

अटल पूर्णांक ctnetlink_dump_exp_ct(काष्ठा net *net, काष्ठा sock *ctnl,
				 काष्ठा sk_buff *skb,
				 स्थिर काष्ठा nlmsghdr *nlh,
				 स्थिर काष्ठा nlattr * स्थिर cda[],
				 काष्ठा netlink_ext_ack *extack)
अणु
	पूर्णांक err;
	काष्ठा nfgenmsg *nfmsg = nlmsg_data(nlh);
	u_पूर्णांक8_t u3 = nfmsg->nfgen_family;
	काष्ठा nf_conntrack_tuple tuple;
	काष्ठा nf_conntrack_tuple_hash *h;
	काष्ठा nf_conn *ct;
	काष्ठा nf_conntrack_zone zone;
	काष्ठा netlink_dump_control c = अणु
		.dump = ctnetlink_exp_ct_dump_table,
		.करोne = ctnetlink_exp_करोne,
	पूर्ण;

	err = ctnetlink_parse_tuple(cda, &tuple, CTA_EXPECT_MASTER,
				    u3, शून्य);
	अगर (err < 0)
		वापस err;

	err = ctnetlink_parse_zone(cda[CTA_EXPECT_ZONE], &zone);
	अगर (err < 0)
		वापस err;

	h = nf_conntrack_find_get(net, &zone, &tuple);
	अगर (!h)
		वापस -ENOENT;

	ct = nf_ct_tuplehash_to_ctrack(h);
	/* No expectation linked to this connection tracking. */
	अगर (!nfct_help(ct)) अणु
		nf_ct_put(ct);
		वापस 0;
	पूर्ण

	c.data = ct;

	err = netlink_dump_start(ctnl, skb, nlh, &c);
	nf_ct_put(ct);

	वापस err;
पूर्ण

अटल पूर्णांक ctnetlink_get_expect(काष्ठा sk_buff *skb,
				स्थिर काष्ठा nfnl_info *info,
				स्थिर काष्ठा nlattr * स्थिर cda[])
अणु
	काष्ठा nfgenmsg *nfmsg = nlmsg_data(info->nlh);
	u_पूर्णांक8_t u3 = nfmsg->nfgen_family;
	काष्ठा nf_conntrack_tuple tuple;
	काष्ठा nf_conntrack_expect *exp;
	काष्ठा nf_conntrack_zone zone;
	काष्ठा sk_buff *skb2;
	पूर्णांक err;

	अगर (info->nlh->nlmsg_flags & NLM_F_DUMP) अणु
		अगर (cda[CTA_EXPECT_MASTER])
			वापस ctnetlink_dump_exp_ct(info->net, info->sk, skb,
						     info->nlh, cda,
						     info->extack);
		अन्यथा अणु
			काष्ठा netlink_dump_control c = अणु
				.dump = ctnetlink_exp_dump_table,
				.करोne = ctnetlink_exp_करोne,
			पूर्ण;
			वापस netlink_dump_start(info->sk, skb, info->nlh, &c);
		पूर्ण
	पूर्ण

	err = ctnetlink_parse_zone(cda[CTA_EXPECT_ZONE], &zone);
	अगर (err < 0)
		वापस err;

	अगर (cda[CTA_EXPECT_TUPLE])
		err = ctnetlink_parse_tuple(cda, &tuple, CTA_EXPECT_TUPLE,
					    u3, शून्य);
	अन्यथा अगर (cda[CTA_EXPECT_MASTER])
		err = ctnetlink_parse_tuple(cda, &tuple, CTA_EXPECT_MASTER,
					    u3, शून्य);
	अन्यथा
		वापस -EINVAL;

	अगर (err < 0)
		वापस err;

	exp = nf_ct_expect_find_get(info->net, &zone, &tuple);
	अगर (!exp)
		वापस -ENOENT;

	अगर (cda[CTA_EXPECT_ID]) अणु
		__be32 id = nla_get_be32(cda[CTA_EXPECT_ID]);

		अगर (id != nf_expect_get_id(exp)) अणु
			nf_ct_expect_put(exp);
			वापस -ENOENT;
		पूर्ण
	पूर्ण

	err = -ENOMEM;
	skb2 = nlmsg_new(NLMSG_DEFAULT_SIZE, GFP_KERNEL);
	अगर (skb2 == शून्य) अणु
		nf_ct_expect_put(exp);
		जाओ out;
	पूर्ण

	rcu_पढ़ो_lock();
	err = ctnetlink_exp_fill_info(skb2, NETLINK_CB(skb).portid,
				      info->nlh->nlmsg_seq, IPCTNL_MSG_EXP_NEW,
				      exp);
	rcu_पढ़ो_unlock();
	nf_ct_expect_put(exp);
	अगर (err <= 0)
		जाओ मुक्त;

	err = netlink_unicast(info->sk, skb2, NETLINK_CB(skb).portid,
			      MSG_DONTWAIT);
	अगर (err < 0)
		जाओ out;

	वापस 0;

मुक्त:
	kमुक्त_skb(skb2);
out:
	/* this aव्योमs a loop in nfnetlink. */
	वापस err == -EAGAIN ? -ENOBUFS : err;
पूर्ण

अटल bool expect_iter_name(काष्ठा nf_conntrack_expect *exp, व्योम *data)
अणु
	स्थिर काष्ठा nf_conn_help *m_help;
	स्थिर अक्षर *name = data;

	m_help = nfct_help(exp->master);

	वापस म_भेद(m_help->helper->name, name) == 0;
पूर्ण

अटल bool expect_iter_all(काष्ठा nf_conntrack_expect *exp, व्योम *data)
अणु
	वापस true;
पूर्ण

अटल पूर्णांक ctnetlink_del_expect(काष्ठा sk_buff *skb,
				स्थिर काष्ठा nfnl_info *info,
				स्थिर काष्ठा nlattr * स्थिर cda[])
अणु
	काष्ठा nfgenmsg *nfmsg = nlmsg_data(info->nlh);
	u_पूर्णांक8_t u3 = nfmsg->nfgen_family;
	काष्ठा nf_conntrack_expect *exp;
	काष्ठा nf_conntrack_tuple tuple;
	काष्ठा nf_conntrack_zone zone;
	पूर्णांक err;

	अगर (cda[CTA_EXPECT_TUPLE]) अणु
		/* delete a single expect by tuple */
		err = ctnetlink_parse_zone(cda[CTA_EXPECT_ZONE], &zone);
		अगर (err < 0)
			वापस err;

		err = ctnetlink_parse_tuple(cda, &tuple, CTA_EXPECT_TUPLE,
					    u3, शून्य);
		अगर (err < 0)
			वापस err;

		/* bump usage count to 2 */
		exp = nf_ct_expect_find_get(info->net, &zone, &tuple);
		अगर (!exp)
			वापस -ENOENT;

		अगर (cda[CTA_EXPECT_ID]) अणु
			__be32 id = nla_get_be32(cda[CTA_EXPECT_ID]);
			अगर (ntohl(id) != (u32)(अचिन्हित दीर्घ)exp) अणु
				nf_ct_expect_put(exp);
				वापस -ENOENT;
			पूर्ण
		पूर्ण

		/* after list removal, usage count == 1 */
		spin_lock_bh(&nf_conntrack_expect_lock);
		अगर (del_समयr(&exp->समयout)) अणु
			nf_ct_unlink_expect_report(exp, NETLINK_CB(skb).portid,
						   nlmsg_report(info->nlh));
			nf_ct_expect_put(exp);
		पूर्ण
		spin_unlock_bh(&nf_conntrack_expect_lock);
		/* have to put what we 'get' above.
		 * after this line usage count == 0 */
		nf_ct_expect_put(exp);
	पूर्ण अन्यथा अगर (cda[CTA_EXPECT_HELP_NAME]) अणु
		अक्षर *name = nla_data(cda[CTA_EXPECT_HELP_NAME]);

		nf_ct_expect_iterate_net(info->net, expect_iter_name, name,
					 NETLINK_CB(skb).portid,
					 nlmsg_report(info->nlh));
	पूर्ण अन्यथा अणु
		/* This basically means we have to flush everything*/
		nf_ct_expect_iterate_net(info->net, expect_iter_all, शून्य,
					 NETLINK_CB(skb).portid,
					 nlmsg_report(info->nlh));
	पूर्ण

	वापस 0;
पूर्ण
अटल पूर्णांक
ctnetlink_change_expect(काष्ठा nf_conntrack_expect *x,
			स्थिर काष्ठा nlattr * स्थिर cda[])
अणु
	अगर (cda[CTA_EXPECT_TIMEOUT]) अणु
		अगर (!del_समयr(&x->समयout))
			वापस -ETIME;

		x->समयout.expires = jअगरfies +
			ntohl(nla_get_be32(cda[CTA_EXPECT_TIMEOUT])) * HZ;
		add_समयr(&x->समयout);
	पूर्ण
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा nla_policy exp_nat_nla_policy[CTA_EXPECT_NAT_MAX+1] = अणु
	[CTA_EXPECT_NAT_सूची]	= अणु .type = NLA_U32 पूर्ण,
	[CTA_EXPECT_NAT_TUPLE]	= अणु .type = NLA_NESTED पूर्ण,
पूर्ण;

अटल पूर्णांक
ctnetlink_parse_expect_nat(स्थिर काष्ठा nlattr *attr,
			   काष्ठा nf_conntrack_expect *exp,
			   u_पूर्णांक8_t u3)
अणु
#अगर IS_ENABLED(CONFIG_NF_NAT)
	काष्ठा nlattr *tb[CTA_EXPECT_NAT_MAX+1];
	काष्ठा nf_conntrack_tuple nat_tuple = अणुपूर्ण;
	पूर्णांक err;

	err = nla_parse_nested_deprecated(tb, CTA_EXPECT_NAT_MAX, attr,
					  exp_nat_nla_policy, शून्य);
	अगर (err < 0)
		वापस err;

	अगर (!tb[CTA_EXPECT_NAT_सूची] || !tb[CTA_EXPECT_NAT_TUPLE])
		वापस -EINVAL;

	err = ctnetlink_parse_tuple((स्थिर काष्ठा nlattr * स्थिर *)tb,
				    &nat_tuple, CTA_EXPECT_NAT_TUPLE,
				    u3, शून्य);
	अगर (err < 0)
		वापस err;

	exp->saved_addr = nat_tuple.src.u3;
	exp->saved_proto = nat_tuple.src.u;
	exp->dir = ntohl(nla_get_be32(tb[CTA_EXPECT_NAT_सूची]));

	वापस 0;
#अन्यथा
	वापस -EOPNOTSUPP;
#पूर्ण_अगर
पूर्ण

अटल काष्ठा nf_conntrack_expect *
ctnetlink_alloc_expect(स्थिर काष्ठा nlattr * स्थिर cda[], काष्ठा nf_conn *ct,
		       काष्ठा nf_conntrack_helper *helper,
		       काष्ठा nf_conntrack_tuple *tuple,
		       काष्ठा nf_conntrack_tuple *mask)
अणु
	u_पूर्णांक32_t class = 0;
	काष्ठा nf_conntrack_expect *exp;
	काष्ठा nf_conn_help *help;
	पूर्णांक err;

	help = nfct_help(ct);
	अगर (!help)
		वापस ERR_PTR(-EOPNOTSUPP);

	अगर (cda[CTA_EXPECT_CLASS] && helper) अणु
		class = ntohl(nla_get_be32(cda[CTA_EXPECT_CLASS]));
		अगर (class > helper->expect_class_max)
			वापस ERR_PTR(-EINVAL);
	पूर्ण
	exp = nf_ct_expect_alloc(ct);
	अगर (!exp)
		वापस ERR_PTR(-ENOMEM);

	अगर (cda[CTA_EXPECT_FLAGS]) अणु
		exp->flags = ntohl(nla_get_be32(cda[CTA_EXPECT_FLAGS]));
		exp->flags &= ~NF_CT_EXPECT_USERSPACE;
	पूर्ण अन्यथा अणु
		exp->flags = 0;
	पूर्ण
	अगर (cda[CTA_EXPECT_FN]) अणु
		स्थिर अक्षर *name = nla_data(cda[CTA_EXPECT_FN]);
		काष्ठा nf_ct_helper_expectfn *expfn;

		expfn = nf_ct_helper_expectfn_find_by_name(name);
		अगर (expfn == शून्य) अणु
			err = -EINVAL;
			जाओ err_out;
		पूर्ण
		exp->expectfn = expfn->expectfn;
	पूर्ण अन्यथा
		exp->expectfn = शून्य;

	exp->class = class;
	exp->master = ct;
	exp->helper = helper;
	exp->tuple = *tuple;
	exp->mask.src.u3 = mask->src.u3;
	exp->mask.src.u.all = mask->src.u.all;

	अगर (cda[CTA_EXPECT_NAT]) अणु
		err = ctnetlink_parse_expect_nat(cda[CTA_EXPECT_NAT],
						 exp, nf_ct_l3num(ct));
		अगर (err < 0)
			जाओ err_out;
	पूर्ण
	वापस exp;
err_out:
	nf_ct_expect_put(exp);
	वापस ERR_PTR(err);
पूर्ण

अटल पूर्णांक
ctnetlink_create_expect(काष्ठा net *net,
			स्थिर काष्ठा nf_conntrack_zone *zone,
			स्थिर काष्ठा nlattr * स्थिर cda[],
			u_पूर्णांक8_t u3, u32 portid, पूर्णांक report)
अणु
	काष्ठा nf_conntrack_tuple tuple, mask, master_tuple;
	काष्ठा nf_conntrack_tuple_hash *h = शून्य;
	काष्ठा nf_conntrack_helper *helper = शून्य;
	काष्ठा nf_conntrack_expect *exp;
	काष्ठा nf_conn *ct;
	पूर्णांक err;

	/* caller guarantees that those three CTA_EXPECT_* exist */
	err = ctnetlink_parse_tuple(cda, &tuple, CTA_EXPECT_TUPLE,
				    u3, शून्य);
	अगर (err < 0)
		वापस err;
	err = ctnetlink_parse_tuple(cda, &mask, CTA_EXPECT_MASK,
				    u3, शून्य);
	अगर (err < 0)
		वापस err;
	err = ctnetlink_parse_tuple(cda, &master_tuple, CTA_EXPECT_MASTER,
				    u3, शून्य);
	अगर (err < 0)
		वापस err;

	/* Look क्रम master conntrack of this expectation */
	h = nf_conntrack_find_get(net, zone, &master_tuple);
	अगर (!h)
		वापस -ENOENT;
	ct = nf_ct_tuplehash_to_ctrack(h);

	rcu_पढ़ो_lock();
	अगर (cda[CTA_EXPECT_HELP_NAME]) अणु
		स्थिर अक्षर *helpname = nla_data(cda[CTA_EXPECT_HELP_NAME]);

		helper = __nf_conntrack_helper_find(helpname, u3,
						    nf_ct_protonum(ct));
		अगर (helper == शून्य) अणु
			rcu_पढ़ो_unlock();
#अगर_घोषित CONFIG_MODULES
			अगर (request_module("nfct-helper-%s", helpname) < 0) अणु
				err = -EOPNOTSUPP;
				जाओ err_ct;
			पूर्ण
			rcu_पढ़ो_lock();
			helper = __nf_conntrack_helper_find(helpname, u3,
							    nf_ct_protonum(ct));
			अगर (helper) अणु
				err = -EAGAIN;
				जाओ err_rcu;
			पूर्ण
			rcu_पढ़ो_unlock();
#पूर्ण_अगर
			err = -EOPNOTSUPP;
			जाओ err_ct;
		पूर्ण
	पूर्ण

	exp = ctnetlink_alloc_expect(cda, ct, helper, &tuple, &mask);
	अगर (IS_ERR(exp)) अणु
		err = PTR_ERR(exp);
		जाओ err_rcu;
	पूर्ण

	err = nf_ct_expect_related_report(exp, portid, report, 0);
	nf_ct_expect_put(exp);
err_rcu:
	rcu_पढ़ो_unlock();
err_ct:
	nf_ct_put(ct);
	वापस err;
पूर्ण

अटल पूर्णांक ctnetlink_new_expect(काष्ठा sk_buff *skb,
				स्थिर काष्ठा nfnl_info *info,
				स्थिर काष्ठा nlattr * स्थिर cda[])
अणु
	काष्ठा nfgenmsg *nfmsg = nlmsg_data(info->nlh);
	u_पूर्णांक8_t u3 = nfmsg->nfgen_family;
	काष्ठा nf_conntrack_tuple tuple;
	काष्ठा nf_conntrack_expect *exp;
	काष्ठा nf_conntrack_zone zone;
	पूर्णांक err;

	अगर (!cda[CTA_EXPECT_TUPLE]
	    || !cda[CTA_EXPECT_MASK]
	    || !cda[CTA_EXPECT_MASTER])
		वापस -EINVAL;

	err = ctnetlink_parse_zone(cda[CTA_EXPECT_ZONE], &zone);
	अगर (err < 0)
		वापस err;

	err = ctnetlink_parse_tuple(cda, &tuple, CTA_EXPECT_TUPLE,
				    u3, शून्य);
	अगर (err < 0)
		वापस err;

	spin_lock_bh(&nf_conntrack_expect_lock);
	exp = __nf_ct_expect_find(info->net, &zone, &tuple);
	अगर (!exp) अणु
		spin_unlock_bh(&nf_conntrack_expect_lock);
		err = -ENOENT;
		अगर (info->nlh->nlmsg_flags & NLM_F_CREATE) अणु
			err = ctnetlink_create_expect(info->net, &zone, cda, u3,
						      NETLINK_CB(skb).portid,
						      nlmsg_report(info->nlh));
		पूर्ण
		वापस err;
	पूर्ण

	err = -EEXIST;
	अगर (!(info->nlh->nlmsg_flags & NLM_F_EXCL))
		err = ctnetlink_change_expect(exp, cda);
	spin_unlock_bh(&nf_conntrack_expect_lock);

	वापस err;
पूर्ण

अटल पूर्णांक
ctnetlink_exp_stat_fill_info(काष्ठा sk_buff *skb, u32 portid, u32 seq, पूर्णांक cpu,
			     स्थिर काष्ठा ip_conntrack_stat *st)
अणु
	काष्ठा nlmsghdr *nlh;
	अचिन्हित पूर्णांक flags = portid ? NLM_F_MULTI : 0, event;

	event = nfnl_msg_type(NFNL_SUBSYS_CTNETLINK,
			      IPCTNL_MSG_EXP_GET_STATS_CPU);
	nlh = nfnl_msg_put(skb, portid, seq, event, flags, AF_UNSPEC,
			   NFNETLINK_V0, htons(cpu));
	अगर (!nlh)
		जाओ nlmsg_failure;

	अगर (nla_put_be32(skb, CTA_STATS_EXP_NEW, htonl(st->expect_new)) ||
	    nla_put_be32(skb, CTA_STATS_EXP_CREATE, htonl(st->expect_create)) ||
	    nla_put_be32(skb, CTA_STATS_EXP_DELETE, htonl(st->expect_delete)))
		जाओ nla_put_failure;

	nlmsg_end(skb, nlh);
	वापस skb->len;

nla_put_failure:
nlmsg_failure:
	nlmsg_cancel(skb, nlh);
	वापस -1;
पूर्ण

अटल पूर्णांक
ctnetlink_exp_stat_cpu_dump(काष्ठा sk_buff *skb, काष्ठा netlink_callback *cb)
अणु
	पूर्णांक cpu;
	काष्ठा net *net = sock_net(skb->sk);

	अगर (cb->args[0] == nr_cpu_ids)
		वापस 0;

	क्रम (cpu = cb->args[0]; cpu < nr_cpu_ids; cpu++) अणु
		स्थिर काष्ठा ip_conntrack_stat *st;

		अगर (!cpu_possible(cpu))
			जारी;

		st = per_cpu_ptr(net->ct.stat, cpu);
		अगर (ctnetlink_exp_stat_fill_info(skb, NETLINK_CB(cb->skb).portid,
						 cb->nlh->nlmsg_seq,
						 cpu, st) < 0)
			अवरोध;
	पूर्ण
	cb->args[0] = cpu;

	वापस skb->len;
पूर्ण

अटल पूर्णांक ctnetlink_stat_exp_cpu(काष्ठा sk_buff *skb,
				  स्थिर काष्ठा nfnl_info *info,
				  स्थिर काष्ठा nlattr * स्थिर cda[])
अणु
	अगर (info->nlh->nlmsg_flags & NLM_F_DUMP) अणु
		काष्ठा netlink_dump_control c = अणु
			.dump = ctnetlink_exp_stat_cpu_dump,
		पूर्ण;
		वापस netlink_dump_start(info->sk, skb, info->nlh, &c);
	पूर्ण

	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_NF_CONNTRACK_EVENTS
अटल काष्ठा nf_ct_event_notअगरier ctnl_notअगरier = अणु
	.fcn = ctnetlink_conntrack_event,
पूर्ण;

अटल काष्ठा nf_exp_event_notअगरier ctnl_notअगरier_exp = अणु
	.fcn = ctnetlink_expect_event,
पूर्ण;
#पूर्ण_अगर

अटल स्थिर काष्ठा nfnl_callback ctnl_cb[IPCTNL_MSG_MAX] = अणु
	[IPCTNL_MSG_CT_NEW]	= अणु
		.call		= ctnetlink_new_conntrack,
		.type		= NFNL_CB_MUTEX,
		.attr_count	= CTA_MAX,
		.policy		= ct_nla_policy
	पूर्ण,
	[IPCTNL_MSG_CT_GET]	= अणु
		.call		= ctnetlink_get_conntrack,
		.type		= NFNL_CB_MUTEX,
		.attr_count	= CTA_MAX,
		.policy		= ct_nla_policy
	पूर्ण,
	[IPCTNL_MSG_CT_DELETE]	= अणु
		.call		= ctnetlink_del_conntrack,
		.type		= NFNL_CB_MUTEX,
		.attr_count	= CTA_MAX,
		.policy		= ct_nla_policy
	पूर्ण,
	[IPCTNL_MSG_CT_GET_CTRZERO] = अणु
		.call		= ctnetlink_get_conntrack,
		.type		= NFNL_CB_MUTEX,
		.attr_count	= CTA_MAX,
		.policy		= ct_nla_policy
	पूर्ण,
	[IPCTNL_MSG_CT_GET_STATS_CPU] = अणु
		.call		= ctnetlink_stat_ct_cpu,
		.type		= NFNL_CB_MUTEX,
	पूर्ण,
	[IPCTNL_MSG_CT_GET_STATS] = अणु
		.call		= ctnetlink_stat_ct,
		.type		= NFNL_CB_MUTEX,
	पूर्ण,
	[IPCTNL_MSG_CT_GET_DYING] = अणु
		.call		= ctnetlink_get_ct_dying,
		.type		= NFNL_CB_MUTEX,
	पूर्ण,
	[IPCTNL_MSG_CT_GET_UNCONFIRMED]	= अणु
		.call		= ctnetlink_get_ct_unconfirmed,
		.type		= NFNL_CB_MUTEX,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा nfnl_callback ctnl_exp_cb[IPCTNL_MSG_EXP_MAX] = अणु
	[IPCTNL_MSG_EXP_GET] = अणु
		.call		= ctnetlink_get_expect,
		.type		= NFNL_CB_MUTEX,
		.attr_count	= CTA_EXPECT_MAX,
		.policy		= exp_nla_policy
	पूर्ण,
	[IPCTNL_MSG_EXP_NEW] = अणु
		.call		= ctnetlink_new_expect,
		.type		= NFNL_CB_MUTEX,
		.attr_count	= CTA_EXPECT_MAX,
		.policy		= exp_nla_policy
	पूर्ण,
	[IPCTNL_MSG_EXP_DELETE] = अणु
		.call		= ctnetlink_del_expect,
		.type		= NFNL_CB_MUTEX,
		.attr_count	= CTA_EXPECT_MAX,
		.policy		= exp_nla_policy
	पूर्ण,
	[IPCTNL_MSG_EXP_GET_STATS_CPU] = अणु
		.call		= ctnetlink_stat_exp_cpu,
		.type		= NFNL_CB_MUTEX,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा nfnetlink_subप्रणाली ctnl_subsys = अणु
	.name				= "conntrack",
	.subsys_id			= NFNL_SUBSYS_CTNETLINK,
	.cb_count			= IPCTNL_MSG_MAX,
	.cb				= ctnl_cb,
पूर्ण;

अटल स्थिर काष्ठा nfnetlink_subप्रणाली ctnl_exp_subsys = अणु
	.name				= "conntrack_expect",
	.subsys_id			= NFNL_SUBSYS_CTNETLINK_EXP,
	.cb_count			= IPCTNL_MSG_EXP_MAX,
	.cb				= ctnl_exp_cb,
पूर्ण;

MODULE_ALIAS("ip_conntrack_netlink");
MODULE_ALIAS_NFNL_SUBSYS(NFNL_SUBSYS_CTNETLINK);
MODULE_ALIAS_NFNL_SUBSYS(NFNL_SUBSYS_CTNETLINK_EXP);

अटल पूर्णांक __net_init ctnetlink_net_init(काष्ठा net *net)
अणु
#अगर_घोषित CONFIG_NF_CONNTRACK_EVENTS
	पूर्णांक ret;

	ret = nf_conntrack_रेजिस्टर_notअगरier(net, &ctnl_notअगरier);
	अगर (ret < 0) अणु
		pr_err("ctnetlink_init: cannot register notifier.\n");
		जाओ err_out;
	पूर्ण

	ret = nf_ct_expect_रेजिस्टर_notअगरier(net, &ctnl_notअगरier_exp);
	अगर (ret < 0) अणु
		pr_err("ctnetlink_init: cannot expect register notifier.\n");
		जाओ err_unreg_notअगरier;
	पूर्ण
#पूर्ण_अगर
	वापस 0;

#अगर_घोषित CONFIG_NF_CONNTRACK_EVENTS
err_unreg_notअगरier:
	nf_conntrack_unरेजिस्टर_notअगरier(net, &ctnl_notअगरier);
err_out:
	वापस ret;
#पूर्ण_अगर
पूर्ण

अटल व्योम ctnetlink_net_निकास(काष्ठा net *net)
अणु
#अगर_घोषित CONFIG_NF_CONNTRACK_EVENTS
	nf_ct_expect_unरेजिस्टर_notअगरier(net, &ctnl_notअगरier_exp);
	nf_conntrack_unरेजिस्टर_notअगरier(net, &ctnl_notअगरier);
#पूर्ण_अगर
पूर्ण

अटल व्योम __net_निकास ctnetlink_net_निकास_batch(काष्ठा list_head *net_निकास_list)
अणु
	काष्ठा net *net;

	list_क्रम_each_entry(net, net_निकास_list, निकास_list)
		ctnetlink_net_निकास(net);

	/* रुको क्रम other cpus until they are करोne with ctnl_notअगरiers */
	synchronize_rcu();
पूर्ण

अटल काष्ठा pernet_operations ctnetlink_net_ops = अणु
	.init		= ctnetlink_net_init,
	.निकास_batch	= ctnetlink_net_निकास_batch,
पूर्ण;

अटल पूर्णांक __init ctnetlink_init(व्योम)
अणु
	पूर्णांक ret;

	ret = nfnetlink_subsys_रेजिस्टर(&ctnl_subsys);
	अगर (ret < 0) अणु
		pr_err("ctnetlink_init: cannot register with nfnetlink.\n");
		जाओ err_out;
	पूर्ण

	ret = nfnetlink_subsys_रेजिस्टर(&ctnl_exp_subsys);
	अगर (ret < 0) अणु
		pr_err("ctnetlink_init: cannot register exp with nfnetlink.\n");
		जाओ err_unreg_subsys;
	पूर्ण

	ret = रेजिस्टर_pernet_subsys(&ctnetlink_net_ops);
	अगर (ret < 0) अणु
		pr_err("ctnetlink_init: cannot register pernet operations\n");
		जाओ err_unreg_exp_subsys;
	पूर्ण
#अगर_घोषित CONFIG_NETFILTER_NETLINK_GLUE_CT
	/* setup पूर्णांकeraction between nf_queue and nf_conntrack_netlink. */
	RCU_INIT_POINTER(nfnl_ct_hook, &ctnetlink_glue_hook);
#पूर्ण_अगर
	वापस 0;

err_unreg_exp_subsys:
	nfnetlink_subsys_unरेजिस्टर(&ctnl_exp_subsys);
err_unreg_subsys:
	nfnetlink_subsys_unरेजिस्टर(&ctnl_subsys);
err_out:
	वापस ret;
पूर्ण

अटल व्योम __निकास ctnetlink_निकास(व्योम)
अणु
	unरेजिस्टर_pernet_subsys(&ctnetlink_net_ops);
	nfnetlink_subsys_unरेजिस्टर(&ctnl_exp_subsys);
	nfnetlink_subsys_unरेजिस्टर(&ctnl_subsys);
#अगर_घोषित CONFIG_NETFILTER_NETLINK_GLUE_CT
	RCU_INIT_POINTER(nfnl_ct_hook, शून्य);
#पूर्ण_अगर
	synchronize_rcu();
पूर्ण

module_init(ctnetlink_init);
module_निकास(ctnetlink_निकास);
