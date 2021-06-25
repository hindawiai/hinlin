<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#समावेश <linux/types.h>
#समावेश <linux/netfilter.h>
#समावेश <linux/slab.h>
#समावेश <linux/module.h>
#समावेश <linux/skbuff.h>
#समावेश <linux/proc_fs.h>
#समावेश <linux/seq_file.h>
#समावेश <linux/percpu.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/security.h>
#समावेश <net/net_namespace.h>
#अगर_घोषित CONFIG_SYSCTL
#समावेश <linux/sysctl.h>
#पूर्ण_अगर

#समावेश <net/netfilter/nf_conntrack.h>
#समावेश <net/netfilter/nf_conntrack_core.h>
#समावेश <net/netfilter/nf_conntrack_l4proto.h>
#समावेश <net/netfilter/nf_conntrack_expect.h>
#समावेश <net/netfilter/nf_conntrack_helper.h>
#समावेश <net/netfilter/nf_conntrack_acct.h>
#समावेश <net/netfilter/nf_conntrack_zones.h>
#समावेश <net/netfilter/nf_conntrack_बारtamp.h>
#समावेश <linux/rculist_nulls.h>

अटल bool enable_hooks __पढ़ो_mostly;
MODULE_PARM_DESC(enable_hooks, "Always enable conntrack hooks");
module_param(enable_hooks, bool, 0000);

अचिन्हित पूर्णांक nf_conntrack_net_id __पढ़ो_mostly;

#अगर_घोषित CONFIG_NF_CONNTRACK_PROCFS
व्योम
prपूर्णांक_tuple(काष्ठा seq_file *s, स्थिर काष्ठा nf_conntrack_tuple *tuple,
            स्थिर काष्ठा nf_conntrack_l4proto *l4proto)
अणु
	चयन (tuple->src.l3num) अणु
	हाल NFPROTO_IPV4:
		seq_म_लिखो(s, "src=%pI4 dst=%pI4 ",
			   &tuple->src.u3.ip, &tuple->dst.u3.ip);
		अवरोध;
	हाल NFPROTO_IPV6:
		seq_म_लिखो(s, "src=%pI6 dst=%pI6 ",
			   tuple->src.u3.ip6, tuple->dst.u3.ip6);
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	चयन (l4proto->l4proto) अणु
	हाल IPPROTO_ICMP:
		seq_म_लिखो(s, "type=%u code=%u id=%u ",
			   tuple->dst.u.icmp.type,
			   tuple->dst.u.icmp.code,
			   ntohs(tuple->src.u.icmp.id));
		अवरोध;
	हाल IPPROTO_TCP:
		seq_म_लिखो(s, "sport=%hu dport=%hu ",
			   ntohs(tuple->src.u.tcp.port),
			   ntohs(tuple->dst.u.tcp.port));
		अवरोध;
	हाल IPPROTO_UDPLITE:
	हाल IPPROTO_UDP:
		seq_म_लिखो(s, "sport=%hu dport=%hu ",
			   ntohs(tuple->src.u.udp.port),
			   ntohs(tuple->dst.u.udp.port));

		अवरोध;
	हाल IPPROTO_DCCP:
		seq_म_लिखो(s, "sport=%hu dport=%hu ",
			   ntohs(tuple->src.u.dccp.port),
			   ntohs(tuple->dst.u.dccp.port));
		अवरोध;
	हाल IPPROTO_SCTP:
		seq_म_लिखो(s, "sport=%hu dport=%hu ",
			   ntohs(tuple->src.u.sctp.port),
			   ntohs(tuple->dst.u.sctp.port));
		अवरोध;
	हाल IPPROTO_ICMPV6:
		seq_म_लिखो(s, "type=%u code=%u id=%u ",
			   tuple->dst.u.icmp.type,
			   tuple->dst.u.icmp.code,
			   ntohs(tuple->src.u.icmp.id));
		अवरोध;
	हाल IPPROTO_GRE:
		seq_म_लिखो(s, "srckey=0x%x dstkey=0x%x ",
			   ntohs(tuple->src.u.gre.key),
			   ntohs(tuple->dst.u.gre.key));
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण
पूर्ण
EXPORT_SYMBOL_GPL(prपूर्णांक_tuple);

काष्ठा ct_iter_state अणु
	काष्ठा seq_net_निजी p;
	काष्ठा hlist_nulls_head *hash;
	अचिन्हित पूर्णांक htable_size;
	अचिन्हित पूर्णांक bucket;
	u_पूर्णांक64_t समय_now;
पूर्ण;

अटल काष्ठा hlist_nulls_node *ct_get_first(काष्ठा seq_file *seq)
अणु
	काष्ठा ct_iter_state *st = seq->निजी;
	काष्ठा hlist_nulls_node *n;

	क्रम (st->bucket = 0;
	     st->bucket < st->htable_size;
	     st->bucket++) अणु
		n = rcu_dereference(
			hlist_nulls_first_rcu(&st->hash[st->bucket]));
		अगर (!is_a_nulls(n))
			वापस n;
	पूर्ण
	वापस शून्य;
पूर्ण

अटल काष्ठा hlist_nulls_node *ct_get_next(काष्ठा seq_file *seq,
				      काष्ठा hlist_nulls_node *head)
अणु
	काष्ठा ct_iter_state *st = seq->निजी;

	head = rcu_dereference(hlist_nulls_next_rcu(head));
	जबतक (is_a_nulls(head)) अणु
		अगर (likely(get_nulls_value(head) == st->bucket)) अणु
			अगर (++st->bucket >= st->htable_size)
				वापस शून्य;
		पूर्ण
		head = rcu_dereference(
			hlist_nulls_first_rcu(&st->hash[st->bucket]));
	पूर्ण
	वापस head;
पूर्ण

अटल काष्ठा hlist_nulls_node *ct_get_idx(काष्ठा seq_file *seq, loff_t pos)
अणु
	काष्ठा hlist_nulls_node *head = ct_get_first(seq);

	अगर (head)
		जबतक (pos && (head = ct_get_next(seq, head)))
			pos--;
	वापस pos ? शून्य : head;
पूर्ण

अटल व्योम *ct_seq_start(काष्ठा seq_file *seq, loff_t *pos)
	__acquires(RCU)
अणु
	काष्ठा ct_iter_state *st = seq->निजी;

	st->समय_now = kसमय_get_real_ns();
	rcu_पढ़ो_lock();

	nf_conntrack_get_ht(&st->hash, &st->htable_size);
	वापस ct_get_idx(seq, *pos);
पूर्ण

अटल व्योम *ct_seq_next(काष्ठा seq_file *s, व्योम *v, loff_t *pos)
अणु
	(*pos)++;
	वापस ct_get_next(s, v);
पूर्ण

अटल व्योम ct_seq_stop(काष्ठा seq_file *s, व्योम *v)
	__releases(RCU)
अणु
	rcu_पढ़ो_unlock();
पूर्ण

#अगर_घोषित CONFIG_NF_CONNTRACK_SECMARK
अटल व्योम ct_show_secctx(काष्ठा seq_file *s, स्थिर काष्ठा nf_conn *ct)
अणु
	पूर्णांक ret;
	u32 len;
	अक्षर *secctx;

	ret = security_secid_to_secctx(ct->secmark, &secctx, &len);
	अगर (ret)
		वापस;

	seq_म_लिखो(s, "secctx=%s ", secctx);

	security_release_secctx(secctx, len);
पूर्ण
#अन्यथा
अटल अंतरभूत व्योम ct_show_secctx(काष्ठा seq_file *s, स्थिर काष्ठा nf_conn *ct)
अणु
पूर्ण
#पूर्ण_अगर

#अगर_घोषित CONFIG_NF_CONNTRACK_ZONES
अटल व्योम ct_show_zone(काष्ठा seq_file *s, स्थिर काष्ठा nf_conn *ct,
			 पूर्णांक dir)
अणु
	स्थिर काष्ठा nf_conntrack_zone *zone = nf_ct_zone(ct);

	अगर (zone->dir != dir)
		वापस;
	चयन (zone->dir) अणु
	हाल NF_CT_DEFAULT_ZONE_सूची:
		seq_म_लिखो(s, "zone=%u ", zone->id);
		अवरोध;
	हाल NF_CT_ZONE_सूची_ORIG:
		seq_म_लिखो(s, "zone-orig=%u ", zone->id);
		अवरोध;
	हाल NF_CT_ZONE_सूची_REPL:
		seq_म_लिखो(s, "zone-reply=%u ", zone->id);
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण
पूर्ण
#अन्यथा
अटल अंतरभूत व्योम ct_show_zone(काष्ठा seq_file *s, स्थिर काष्ठा nf_conn *ct,
				पूर्णांक dir)
अणु
पूर्ण
#पूर्ण_अगर

#अगर_घोषित CONFIG_NF_CONNTRACK_TIMESTAMP
अटल व्योम ct_show_delta_समय(काष्ठा seq_file *s, स्थिर काष्ठा nf_conn *ct)
अणु
	काष्ठा ct_iter_state *st = s->निजी;
	काष्ठा nf_conn_tstamp *tstamp;
	s64 delta_समय;

	tstamp = nf_conn_tstamp_find(ct);
	अगर (tstamp) अणु
		delta_समय = st->समय_now - tstamp->start;
		अगर (delta_समय > 0)
			delta_समय = भाग_s64(delta_समय, NSEC_PER_SEC);
		अन्यथा
			delta_समय = 0;

		seq_म_लिखो(s, "delta-time=%llu ",
			   (अचिन्हित दीर्घ दीर्घ)delta_समय);
	पूर्ण
	वापस;
पूर्ण
#अन्यथा
अटल अंतरभूत व्योम
ct_show_delta_समय(काष्ठा seq_file *s, स्थिर काष्ठा nf_conn *ct)
अणु
पूर्ण
#पूर्ण_अगर

अटल स्थिर अक्षर* l3proto_name(u16 proto)
अणु
	चयन (proto) अणु
	हाल AF_INET: वापस "ipv4";
	हाल AF_INET6: वापस "ipv6";
	पूर्ण

	वापस "unknown";
पूर्ण

अटल स्थिर अक्षर* l4proto_name(u16 proto)
अणु
	चयन (proto) अणु
	हाल IPPROTO_ICMP: वापस "icmp";
	हाल IPPROTO_TCP: वापस "tcp";
	हाल IPPROTO_UDP: वापस "udp";
	हाल IPPROTO_DCCP: वापस "dccp";
	हाल IPPROTO_GRE: वापस "gre";
	हाल IPPROTO_SCTP: वापस "sctp";
	हाल IPPROTO_UDPLITE: वापस "udplite";
	हाल IPPROTO_ICMPV6: वापस "icmpv6";
	पूर्ण

	वापस "unknown";
पूर्ण

अटल अचिन्हित पूर्णांक
seq_prपूर्णांक_acct(काष्ठा seq_file *s, स्थिर काष्ठा nf_conn *ct, पूर्णांक dir)
अणु
	काष्ठा nf_conn_acct *acct;
	काष्ठा nf_conn_counter *counter;

	acct = nf_conn_acct_find(ct);
	अगर (!acct)
		वापस 0;

	counter = acct->counter;
	seq_म_लिखो(s, "packets=%llu bytes=%llu ",
		   (अचिन्हित दीर्घ दीर्घ)atomic64_पढ़ो(&counter[dir].packets),
		   (अचिन्हित दीर्घ दीर्घ)atomic64_पढ़ो(&counter[dir].bytes));

	वापस 0;
पूर्ण

/* वापस 0 on success, 1 in हाल of error */
अटल पूर्णांक ct_seq_show(काष्ठा seq_file *s, व्योम *v)
अणु
	काष्ठा nf_conntrack_tuple_hash *hash = v;
	काष्ठा nf_conn *ct = nf_ct_tuplehash_to_ctrack(hash);
	स्थिर काष्ठा nf_conntrack_l4proto *l4proto;
	काष्ठा net *net = seq_file_net(s);
	पूर्णांक ret = 0;

	WARN_ON(!ct);
	अगर (unlikely(!atomic_inc_not_zero(&ct->ct_general.use)))
		वापस 0;

	अगर (nf_ct_should_gc(ct)) अणु
		nf_ct_समाप्त(ct);
		जाओ release;
	पूर्ण

	/* we only want to prपूर्णांक सूची_ORIGINAL */
	अगर (NF_CT_सूचीECTION(hash))
		जाओ release;

	अगर (!net_eq(nf_ct_net(ct), net))
		जाओ release;

	l4proto = nf_ct_l4proto_find(nf_ct_protonum(ct));

	ret = -ENOSPC;
	seq_म_लिखो(s, "%-8s %u %-8s %u ",
		   l3proto_name(nf_ct_l3num(ct)), nf_ct_l3num(ct),
		   l4proto_name(l4proto->l4proto), nf_ct_protonum(ct));

	अगर (!test_bit(IPS_OFFLOAD_BIT, &ct->status))
		seq_म_लिखो(s, "%ld ", nf_ct_expires(ct)  / HZ);

	अगर (l4proto->prपूर्णांक_conntrack)
		l4proto->prपूर्णांक_conntrack(s, ct);

	prपूर्णांक_tuple(s, &ct->tuplehash[IP_CT_सूची_ORIGINAL].tuple,
		    l4proto);

	ct_show_zone(s, ct, NF_CT_ZONE_सूची_ORIG);

	अगर (seq_has_overflowed(s))
		जाओ release;

	अगर (seq_prपूर्णांक_acct(s, ct, IP_CT_सूची_ORIGINAL))
		जाओ release;

	अगर (!(test_bit(IPS_SEEN_REPLY_BIT, &ct->status)))
		seq_माला_दो(s, "[UNREPLIED] ");

	prपूर्णांक_tuple(s, &ct->tuplehash[IP_CT_सूची_REPLY].tuple, l4proto);

	ct_show_zone(s, ct, NF_CT_ZONE_सूची_REPL);

	अगर (seq_prपूर्णांक_acct(s, ct, IP_CT_सूची_REPLY))
		जाओ release;

	अगर (test_bit(IPS_HW_OFFLOAD_BIT, &ct->status))
		seq_माला_दो(s, "[HW_OFFLOAD] ");
	अन्यथा अगर (test_bit(IPS_OFFLOAD_BIT, &ct->status))
		seq_माला_दो(s, "[OFFLOAD] ");
	अन्यथा अगर (test_bit(IPS_ASSURED_BIT, &ct->status))
		seq_माला_दो(s, "[ASSURED] ");

	अगर (seq_has_overflowed(s))
		जाओ release;

#अगर defined(CONFIG_NF_CONNTRACK_MARK)
	seq_म_लिखो(s, "mark=%u ", ct->mark);
#पूर्ण_अगर

	ct_show_secctx(s, ct);
	ct_show_zone(s, ct, NF_CT_DEFAULT_ZONE_सूची);
	ct_show_delta_समय(s, ct);

	seq_म_लिखो(s, "use=%u\n", atomic_पढ़ो(&ct->ct_general.use));

	अगर (seq_has_overflowed(s))
		जाओ release;

	ret = 0;
release:
	nf_ct_put(ct);
	वापस ret;
पूर्ण

अटल स्थिर काष्ठा seq_operations ct_seq_ops = अणु
	.start = ct_seq_start,
	.next  = ct_seq_next,
	.stop  = ct_seq_stop,
	.show  = ct_seq_show
पूर्ण;

अटल व्योम *ct_cpu_seq_start(काष्ठा seq_file *seq, loff_t *pos)
अणु
	काष्ठा net *net = seq_file_net(seq);
	पूर्णांक cpu;

	अगर (*pos == 0)
		वापस SEQ_START_TOKEN;

	क्रम (cpu = *pos-1; cpu < nr_cpu_ids; ++cpu) अणु
		अगर (!cpu_possible(cpu))
			जारी;
		*pos = cpu + 1;
		वापस per_cpu_ptr(net->ct.stat, cpu);
	पूर्ण

	वापस शून्य;
पूर्ण

अटल व्योम *ct_cpu_seq_next(काष्ठा seq_file *seq, व्योम *v, loff_t *pos)
अणु
	काष्ठा net *net = seq_file_net(seq);
	पूर्णांक cpu;

	क्रम (cpu = *pos; cpu < nr_cpu_ids; ++cpu) अणु
		अगर (!cpu_possible(cpu))
			जारी;
		*pos = cpu + 1;
		वापस per_cpu_ptr(net->ct.stat, cpu);
	पूर्ण
	(*pos)++;
	वापस शून्य;
पूर्ण

अटल व्योम ct_cpu_seq_stop(काष्ठा seq_file *seq, व्योम *v)
अणु
पूर्ण

अटल पूर्णांक ct_cpu_seq_show(काष्ठा seq_file *seq, व्योम *v)
अणु
	काष्ठा net *net = seq_file_net(seq);
	स्थिर काष्ठा ip_conntrack_stat *st = v;
	अचिन्हित पूर्णांक nr_conntracks;

	अगर (v == SEQ_START_TOKEN) अणु
		seq_माला_दो(seq, "entries  clashres found new invalid ignore delete delete_list insert insert_failed drop early_drop icmp_error  expect_new expect_create expect_delete search_restart\n");
		वापस 0;
	पूर्ण

	nr_conntracks = nf_conntrack_count(net);

	seq_म_लिखो(seq, "%08x  %08x %08x %08x %08x %08x %08x %08x "
			"%08x %08x %08x %08x %08x  %08x %08x %08x %08x\n",
		   nr_conntracks,
		   st->clash_resolve,
		   st->found,
		   0,
		   st->invalid,
		   0,
		   0,
		   0,
		   st->insert,
		   st->insert_failed,
		   st->drop,
		   st->early_drop,
		   st->error,

		   st->expect_new,
		   st->expect_create,
		   st->expect_delete,
		   st->search_restart
		);
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा seq_operations ct_cpu_seq_ops = अणु
	.start	= ct_cpu_seq_start,
	.next	= ct_cpu_seq_next,
	.stop	= ct_cpu_seq_stop,
	.show	= ct_cpu_seq_show,
पूर्ण;

अटल पूर्णांक nf_conntrack_standalone_init_proc(काष्ठा net *net)
अणु
	काष्ठा proc_dir_entry *pde;
	kuid_t root_uid;
	kgid_t root_gid;

	pde = proc_create_net("nf_conntrack", 0440, net->proc_net, &ct_seq_ops,
			माप(काष्ठा ct_iter_state));
	अगर (!pde)
		जाओ out_nf_conntrack;

	root_uid = make_kuid(net->user_ns, 0);
	root_gid = make_kgid(net->user_ns, 0);
	अगर (uid_valid(root_uid) && gid_valid(root_gid))
		proc_set_user(pde, root_uid, root_gid);

	pde = proc_create_net("nf_conntrack", 0444, net->proc_net_stat,
			&ct_cpu_seq_ops, माप(काष्ठा seq_net_निजी));
	अगर (!pde)
		जाओ out_stat_nf_conntrack;
	वापस 0;

out_stat_nf_conntrack:
	हटाओ_proc_entry("nf_conntrack", net->proc_net);
out_nf_conntrack:
	वापस -ENOMEM;
पूर्ण

अटल व्योम nf_conntrack_standalone_fini_proc(काष्ठा net *net)
अणु
	हटाओ_proc_entry("nf_conntrack", net->proc_net_stat);
	हटाओ_proc_entry("nf_conntrack", net->proc_net);
पूर्ण
#अन्यथा
अटल पूर्णांक nf_conntrack_standalone_init_proc(काष्ठा net *net)
अणु
	वापस 0;
पूर्ण

अटल व्योम nf_conntrack_standalone_fini_proc(काष्ठा net *net)
अणु
पूर्ण
#पूर्ण_अगर /* CONFIG_NF_CONNTRACK_PROCFS */

u32 nf_conntrack_count(स्थिर काष्ठा net *net)
अणु
	स्थिर काष्ठा nf_conntrack_net *cnet;

	cnet = net_generic(net, nf_conntrack_net_id);

	वापस atomic_पढ़ो(&cnet->count);
पूर्ण
EXPORT_SYMBOL_GPL(nf_conntrack_count);

/* Sysctl support */

#अगर_घोषित CONFIG_SYSCTL
/* size the user *wants to set */
अटल अचिन्हित पूर्णांक nf_conntrack_htable_size_user __पढ़ो_mostly;

अटल पूर्णांक
nf_conntrack_hash_sysctl(काष्ठा ctl_table *table, पूर्णांक ग_लिखो,
			 व्योम *buffer, माप_प्रकार *lenp, loff_t *ppos)
अणु
	पूर्णांक ret;

	/* module_param hashsize could have changed value */
	nf_conntrack_htable_size_user = nf_conntrack_htable_size;

	ret = proc_करोपूर्णांकvec(table, ग_लिखो, buffer, lenp, ppos);
	अगर (ret < 0 || !ग_लिखो)
		वापस ret;

	/* update ret, we might not be able to satisfy request */
	ret = nf_conntrack_hash_resize(nf_conntrack_htable_size_user);

	/* update it to the actual value used by conntrack */
	nf_conntrack_htable_size_user = nf_conntrack_htable_size;
	वापस ret;
पूर्ण

अटल काष्ठा ctl_table_header *nf_ct_netfilter_header;

क्रमागत nf_ct_sysctl_index अणु
	NF_SYSCTL_CT_MAX,
	NF_SYSCTL_CT_COUNT,
	NF_SYSCTL_CT_BUCKETS,
	NF_SYSCTL_CT_CHECKSUM,
	NF_SYSCTL_CT_LOG_INVALID,
	NF_SYSCTL_CT_EXPECT_MAX,
	NF_SYSCTL_CT_ACCT,
	NF_SYSCTL_CT_HELPER,
#अगर_घोषित CONFIG_NF_CONNTRACK_EVENTS
	NF_SYSCTL_CT_EVENTS,
#पूर्ण_अगर
#अगर_घोषित CONFIG_NF_CONNTRACK_TIMESTAMP
	NF_SYSCTL_CT_TIMESTAMP,
#पूर्ण_अगर
	NF_SYSCTL_CT_PROTO_TIMEOUT_GENERIC,
	NF_SYSCTL_CT_PROTO_TIMEOUT_TCP_SYN_SENT,
	NF_SYSCTL_CT_PROTO_TIMEOUT_TCP_SYN_RECV,
	NF_SYSCTL_CT_PROTO_TIMEOUT_TCP_ESTABLISHED,
	NF_SYSCTL_CT_PROTO_TIMEOUT_TCP_FIN_WAIT,
	NF_SYSCTL_CT_PROTO_TIMEOUT_TCP_CLOSE_WAIT,
	NF_SYSCTL_CT_PROTO_TIMEOUT_TCP_LAST_ACK,
	NF_SYSCTL_CT_PROTO_TIMEOUT_TCP_TIME_WAIT,
	NF_SYSCTL_CT_PROTO_TIMEOUT_TCP_CLOSE,
	NF_SYSCTL_CT_PROTO_TIMEOUT_TCP_RETRANS,
	NF_SYSCTL_CT_PROTO_TIMEOUT_TCP_UNACK,
	NF_SYSCTL_CT_PROTO_TCP_LOOSE,
	NF_SYSCTL_CT_PROTO_TCP_LIBERAL,
	NF_SYSCTL_CT_PROTO_TCP_MAX_RETRANS,
	NF_SYSCTL_CT_PROTO_TIMEOUT_UDP,
	NF_SYSCTL_CT_PROTO_TIMEOUT_UDP_STREAM,
	NF_SYSCTL_CT_PROTO_TIMEOUT_ICMP,
	NF_SYSCTL_CT_PROTO_TIMEOUT_ICMPV6,
#अगर_घोषित CONFIG_NF_CT_PROTO_SCTP
	NF_SYSCTL_CT_PROTO_TIMEOUT_SCTP_CLOSED,
	NF_SYSCTL_CT_PROTO_TIMEOUT_SCTP_COOKIE_WAIT,
	NF_SYSCTL_CT_PROTO_TIMEOUT_SCTP_COOKIE_ECHOED,
	NF_SYSCTL_CT_PROTO_TIMEOUT_SCTP_ESTABLISHED,
	NF_SYSCTL_CT_PROTO_TIMEOUT_SCTP_SHUTDOWN_SENT,
	NF_SYSCTL_CT_PROTO_TIMEOUT_SCTP_SHUTDOWN_RECD,
	NF_SYSCTL_CT_PROTO_TIMEOUT_SCTP_SHUTDOWN_ACK_SENT,
	NF_SYSCTL_CT_PROTO_TIMEOUT_SCTP_HEARTBEAT_SENT,
	NF_SYSCTL_CT_PROTO_TIMEOUT_SCTP_HEARTBEAT_ACKED,
#पूर्ण_अगर
#अगर_घोषित CONFIG_NF_CT_PROTO_DCCP
	NF_SYSCTL_CT_PROTO_TIMEOUT_DCCP_REQUEST,
	NF_SYSCTL_CT_PROTO_TIMEOUT_DCCP_RESPOND,
	NF_SYSCTL_CT_PROTO_TIMEOUT_DCCP_PARTOPEN,
	NF_SYSCTL_CT_PROTO_TIMEOUT_DCCP_OPEN,
	NF_SYSCTL_CT_PROTO_TIMEOUT_DCCP_CLOSEREQ,
	NF_SYSCTL_CT_PROTO_TIMEOUT_DCCP_CLOSING,
	NF_SYSCTL_CT_PROTO_TIMEOUT_DCCP_TIMEWAIT,
	NF_SYSCTL_CT_PROTO_DCCP_LOOSE,
#पूर्ण_अगर
#अगर_घोषित CONFIG_NF_CT_PROTO_GRE
	NF_SYSCTL_CT_PROTO_TIMEOUT_GRE,
	NF_SYSCTL_CT_PROTO_TIMEOUT_GRE_STREAM,
#पूर्ण_अगर

	__NF_SYSCTL_CT_LAST_SYSCTL,
पूर्ण;

#घोषणा NF_SYSCTL_CT_LAST_SYSCTL (__NF_SYSCTL_CT_LAST_SYSCTL + 1)

अटल काष्ठा ctl_table nf_ct_sysctl_table[] = अणु
	[NF_SYSCTL_CT_MAX] = अणु
		.procname	= "nf_conntrack_max",
		.data		= &nf_conntrack_max,
		.maxlen		= माप(पूर्णांक),
		.mode		= 0644,
		.proc_handler	= proc_करोपूर्णांकvec,
	पूर्ण,
	[NF_SYSCTL_CT_COUNT] = अणु
		.procname	= "nf_conntrack_count",
		.maxlen		= माप(पूर्णांक),
		.mode		= 0444,
		.proc_handler	= proc_करोपूर्णांकvec,
	पूर्ण,
	[NF_SYSCTL_CT_BUCKETS] = अणु
		.procname       = "nf_conntrack_buckets",
		.data           = &nf_conntrack_htable_size_user,
		.maxlen         = माप(अचिन्हित पूर्णांक),
		.mode           = 0644,
		.proc_handler   = nf_conntrack_hash_sysctl,
	पूर्ण,
	[NF_SYSCTL_CT_CHECKSUM] = अणु
		.procname	= "nf_conntrack_checksum",
		.data		= &init_net.ct.sysctl_checksum,
		.maxlen		= माप(u8),
		.mode		= 0644,
		.proc_handler	= proc_करोu8vec_minmax,
		.extra1 	= SYSCTL_ZERO,
		.extra2 	= SYSCTL_ONE,
	पूर्ण,
	[NF_SYSCTL_CT_LOG_INVALID] = अणु
		.procname	= "nf_conntrack_log_invalid",
		.data		= &init_net.ct.sysctl_log_invalid,
		.maxlen		= माप(u8),
		.mode		= 0644,
		.proc_handler	= proc_करोu8vec_minmax,
	पूर्ण,
	[NF_SYSCTL_CT_EXPECT_MAX] = अणु
		.procname	= "nf_conntrack_expect_max",
		.data		= &nf_ct_expect_max,
		.maxlen		= माप(पूर्णांक),
		.mode		= 0644,
		.proc_handler	= proc_करोपूर्णांकvec,
	पूर्ण,
	[NF_SYSCTL_CT_ACCT] = अणु
		.procname	= "nf_conntrack_acct",
		.data		= &init_net.ct.sysctl_acct,
		.maxlen		= माप(u8),
		.mode		= 0644,
		.proc_handler	= proc_करोu8vec_minmax,
		.extra1 	= SYSCTL_ZERO,
		.extra2 	= SYSCTL_ONE,
	पूर्ण,
	[NF_SYSCTL_CT_HELPER] = अणु
		.procname	= "nf_conntrack_helper",
		.maxlen		= माप(u8),
		.mode		= 0644,
		.proc_handler	= proc_करोu8vec_minmax,
		.extra1 	= SYSCTL_ZERO,
		.extra2 	= SYSCTL_ONE,
	पूर्ण,
#अगर_घोषित CONFIG_NF_CONNTRACK_EVENTS
	[NF_SYSCTL_CT_EVENTS] = अणु
		.procname	= "nf_conntrack_events",
		.data		= &init_net.ct.sysctl_events,
		.maxlen		= माप(u8),
		.mode		= 0644,
		.proc_handler	= proc_करोu8vec_minmax,
		.extra1 	= SYSCTL_ZERO,
		.extra2 	= SYSCTL_ONE,
	पूर्ण,
#पूर्ण_अगर
#अगर_घोषित CONFIG_NF_CONNTRACK_TIMESTAMP
	[NF_SYSCTL_CT_TIMESTAMP] = अणु
		.procname	= "nf_conntrack_timestamp",
		.data		= &init_net.ct.sysctl_tstamp,
		.maxlen		= माप(u8),
		.mode		= 0644,
		.proc_handler	= proc_करोu8vec_minmax,
		.extra1 	= SYSCTL_ZERO,
		.extra2 	= SYSCTL_ONE,
	पूर्ण,
#पूर्ण_अगर
	[NF_SYSCTL_CT_PROTO_TIMEOUT_GENERIC] = अणु
		.procname	= "nf_conntrack_generic_timeout",
		.maxlen		= माप(अचिन्हित पूर्णांक),
		.mode		= 0644,
		.proc_handler	= proc_करोपूर्णांकvec_jअगरfies,
	पूर्ण,
	[NF_SYSCTL_CT_PROTO_TIMEOUT_TCP_SYN_SENT] = अणु
		.procname	= "nf_conntrack_tcp_timeout_syn_sent",
		.maxlen		= माप(अचिन्हित पूर्णांक),
		.mode		= 0644,
		.proc_handler	= proc_करोपूर्णांकvec_jअगरfies,
	पूर्ण,
	[NF_SYSCTL_CT_PROTO_TIMEOUT_TCP_SYN_RECV] = अणु
		.procname	= "nf_conntrack_tcp_timeout_syn_recv",
		.maxlen		= माप(अचिन्हित पूर्णांक),
		.mode		= 0644,
		.proc_handler	= proc_करोपूर्णांकvec_jअगरfies,
	पूर्ण,
	[NF_SYSCTL_CT_PROTO_TIMEOUT_TCP_ESTABLISHED] = अणु
		.procname	= "nf_conntrack_tcp_timeout_established",
		.maxlen		= माप(अचिन्हित पूर्णांक),
		.mode		= 0644,
		.proc_handler	= proc_करोपूर्णांकvec_jअगरfies,
	पूर्ण,
	[NF_SYSCTL_CT_PROTO_TIMEOUT_TCP_FIN_WAIT] = अणु
		.procname	= "nf_conntrack_tcp_timeout_fin_wait",
		.maxlen		= माप(अचिन्हित पूर्णांक),
		.mode		= 0644,
		.proc_handler	= proc_करोपूर्णांकvec_jअगरfies,
	पूर्ण,
	[NF_SYSCTL_CT_PROTO_TIMEOUT_TCP_CLOSE_WAIT] = अणु
		.procname	= "nf_conntrack_tcp_timeout_close_wait",
		.maxlen		= माप(अचिन्हित पूर्णांक),
		.mode		= 0644,
		.proc_handler	= proc_करोपूर्णांकvec_jअगरfies,
	पूर्ण,
	[NF_SYSCTL_CT_PROTO_TIMEOUT_TCP_LAST_ACK] = अणु
		.procname	= "nf_conntrack_tcp_timeout_last_ack",
		.maxlen		= माप(अचिन्हित पूर्णांक),
		.mode		= 0644,
		.proc_handler	= proc_करोपूर्णांकvec_jअगरfies,
	पूर्ण,
	[NF_SYSCTL_CT_PROTO_TIMEOUT_TCP_TIME_WAIT] = अणु
		.procname	= "nf_conntrack_tcp_timeout_time_wait",
		.maxlen		= माप(अचिन्हित पूर्णांक),
		.mode		= 0644,
		.proc_handler	= proc_करोपूर्णांकvec_jअगरfies,
	पूर्ण,
	[NF_SYSCTL_CT_PROTO_TIMEOUT_TCP_CLOSE] = अणु
		.procname	= "nf_conntrack_tcp_timeout_close",
		.maxlen		= माप(अचिन्हित पूर्णांक),
		.mode		= 0644,
		.proc_handler	= proc_करोपूर्णांकvec_jअगरfies,
	पूर्ण,
	[NF_SYSCTL_CT_PROTO_TIMEOUT_TCP_RETRANS] = अणु
		.procname	= "nf_conntrack_tcp_timeout_max_retrans",
		.maxlen		= माप(अचिन्हित पूर्णांक),
		.mode		= 0644,
		.proc_handler	= proc_करोपूर्णांकvec_jअगरfies,
	पूर्ण,
	[NF_SYSCTL_CT_PROTO_TIMEOUT_TCP_UNACK] = अणु
		.procname	= "nf_conntrack_tcp_timeout_unacknowledged",
		.maxlen		= माप(अचिन्हित पूर्णांक),
		.mode		= 0644,
		.proc_handler	= proc_करोपूर्णांकvec_jअगरfies,
	पूर्ण,
	[NF_SYSCTL_CT_PROTO_TCP_LOOSE] = अणु
		.procname	= "nf_conntrack_tcp_loose",
		.maxlen		= माप(u8),
		.mode		= 0644,
		.proc_handler	= proc_करोu8vec_minmax,
		.extra1 	= SYSCTL_ZERO,
		.extra2 	= SYSCTL_ONE,
	पूर्ण,
	[NF_SYSCTL_CT_PROTO_TCP_LIBERAL] = अणु
		.procname       = "nf_conntrack_tcp_be_liberal",
		.maxlen		= माप(u8),
		.mode           = 0644,
		.proc_handler	= proc_करोu8vec_minmax,
		.extra1 	= SYSCTL_ZERO,
		.extra2 	= SYSCTL_ONE,
	पूर्ण,
	[NF_SYSCTL_CT_PROTO_TCP_MAX_RETRANS] = अणु
		.procname	= "nf_conntrack_tcp_max_retrans",
		.maxlen		= माप(u8),
		.mode		= 0644,
		.proc_handler	= proc_करोu8vec_minmax,
	पूर्ण,
	[NF_SYSCTL_CT_PROTO_TIMEOUT_UDP] = अणु
		.procname	= "nf_conntrack_udp_timeout",
		.maxlen		= माप(अचिन्हित पूर्णांक),
		.mode		= 0644,
		.proc_handler	= proc_करोपूर्णांकvec_jअगरfies,
	पूर्ण,
	[NF_SYSCTL_CT_PROTO_TIMEOUT_UDP_STREAM] = अणु
		.procname	= "nf_conntrack_udp_timeout_stream",
		.maxlen		= माप(अचिन्हित पूर्णांक),
		.mode		= 0644,
		.proc_handler	= proc_करोपूर्णांकvec_jअगरfies,
	पूर्ण,
	[NF_SYSCTL_CT_PROTO_TIMEOUT_ICMP] = अणु
		.procname	= "nf_conntrack_icmp_timeout",
		.maxlen		= माप(अचिन्हित पूर्णांक),
		.mode		= 0644,
		.proc_handler	= proc_करोपूर्णांकvec_jअगरfies,
	पूर्ण,
	[NF_SYSCTL_CT_PROTO_TIMEOUT_ICMPV6] = अणु
		.procname	= "nf_conntrack_icmpv6_timeout",
		.maxlen		= माप(अचिन्हित पूर्णांक),
		.mode		= 0644,
		.proc_handler	= proc_करोपूर्णांकvec_jअगरfies,
	पूर्ण,
#अगर_घोषित CONFIG_NF_CT_PROTO_SCTP
	[NF_SYSCTL_CT_PROTO_TIMEOUT_SCTP_CLOSED] = अणु
		.procname	= "nf_conntrack_sctp_timeout_closed",
		.maxlen		= माप(अचिन्हित पूर्णांक),
		.mode		= 0644,
		.proc_handler	= proc_करोपूर्णांकvec_jअगरfies,
	पूर्ण,
	[NF_SYSCTL_CT_PROTO_TIMEOUT_SCTP_COOKIE_WAIT] = अणु
		.procname	= "nf_conntrack_sctp_timeout_cookie_wait",
		.maxlen		= माप(अचिन्हित पूर्णांक),
		.mode		= 0644,
		.proc_handler	= proc_करोपूर्णांकvec_jअगरfies,
	पूर्ण,
	[NF_SYSCTL_CT_PROTO_TIMEOUT_SCTP_COOKIE_ECHOED] = अणु
		.procname	= "nf_conntrack_sctp_timeout_cookie_echoed",
		.maxlen		= माप(अचिन्हित पूर्णांक),
		.mode		= 0644,
		.proc_handler	= proc_करोपूर्णांकvec_jअगरfies,
	पूर्ण,
	[NF_SYSCTL_CT_PROTO_TIMEOUT_SCTP_ESTABLISHED] = अणु
		.procname	= "nf_conntrack_sctp_timeout_established",
		.maxlen		= माप(अचिन्हित पूर्णांक),
		.mode		= 0644,
		.proc_handler	= proc_करोपूर्णांकvec_jअगरfies,
	पूर्ण,
	[NF_SYSCTL_CT_PROTO_TIMEOUT_SCTP_SHUTDOWN_SENT] = अणु
		.procname	= "nf_conntrack_sctp_timeout_shutdown_sent",
		.maxlen		= माप(अचिन्हित पूर्णांक),
		.mode		= 0644,
		.proc_handler	= proc_करोपूर्णांकvec_jअगरfies,
	पूर्ण,
	[NF_SYSCTL_CT_PROTO_TIMEOUT_SCTP_SHUTDOWN_RECD] = अणु
		.procname	= "nf_conntrack_sctp_timeout_shutdown_recd",
		.maxlen		= माप(अचिन्हित पूर्णांक),
		.mode		= 0644,
		.proc_handler	= proc_करोपूर्णांकvec_jअगरfies,
	पूर्ण,
	[NF_SYSCTL_CT_PROTO_TIMEOUT_SCTP_SHUTDOWN_ACK_SENT] = अणु
		.procname	= "nf_conntrack_sctp_timeout_shutdown_ack_sent",
		.maxlen		= माप(अचिन्हित पूर्णांक),
		.mode		= 0644,
		.proc_handler	= proc_करोपूर्णांकvec_jअगरfies,
	पूर्ण,
	[NF_SYSCTL_CT_PROTO_TIMEOUT_SCTP_HEARTBEAT_SENT] = अणु
		.procname	= "nf_conntrack_sctp_timeout_heartbeat_sent",
		.maxlen		= माप(अचिन्हित पूर्णांक),
		.mode		= 0644,
		.proc_handler	= proc_करोपूर्णांकvec_jअगरfies,
	पूर्ण,
	[NF_SYSCTL_CT_PROTO_TIMEOUT_SCTP_HEARTBEAT_ACKED] = अणु
		.procname       = "nf_conntrack_sctp_timeout_heartbeat_acked",
		.maxlen         = माप(अचिन्हित पूर्णांक),
		.mode           = 0644,
		.proc_handler   = proc_करोपूर्णांकvec_jअगरfies,
	पूर्ण,
#पूर्ण_अगर
#अगर_घोषित CONFIG_NF_CT_PROTO_DCCP
	[NF_SYSCTL_CT_PROTO_TIMEOUT_DCCP_REQUEST] = अणु
		.procname	= "nf_conntrack_dccp_timeout_request",
		.maxlen		= माप(अचिन्हित पूर्णांक),
		.mode		= 0644,
		.proc_handler	= proc_करोपूर्णांकvec_jअगरfies,
	पूर्ण,
	[NF_SYSCTL_CT_PROTO_TIMEOUT_DCCP_RESPOND] = अणु
		.procname	= "nf_conntrack_dccp_timeout_respond",
		.maxlen		= माप(अचिन्हित पूर्णांक),
		.mode		= 0644,
		.proc_handler	= proc_करोपूर्णांकvec_jअगरfies,
	पूर्ण,
	[NF_SYSCTL_CT_PROTO_TIMEOUT_DCCP_PARTOPEN] = अणु
		.procname	= "nf_conntrack_dccp_timeout_partopen",
		.maxlen		= माप(अचिन्हित पूर्णांक),
		.mode		= 0644,
		.proc_handler	= proc_करोपूर्णांकvec_jअगरfies,
	पूर्ण,
	[NF_SYSCTL_CT_PROTO_TIMEOUT_DCCP_OPEN] = अणु
		.procname	= "nf_conntrack_dccp_timeout_open",
		.maxlen		= माप(अचिन्हित पूर्णांक),
		.mode		= 0644,
		.proc_handler	= proc_करोपूर्णांकvec_jअगरfies,
	पूर्ण,
	[NF_SYSCTL_CT_PROTO_TIMEOUT_DCCP_CLOSEREQ] = अणु
		.procname	= "nf_conntrack_dccp_timeout_closereq",
		.maxlen		= माप(अचिन्हित पूर्णांक),
		.mode		= 0644,
		.proc_handler	= proc_करोपूर्णांकvec_jअगरfies,
	पूर्ण,
	[NF_SYSCTL_CT_PROTO_TIMEOUT_DCCP_CLOSING] = अणु
		.procname	= "nf_conntrack_dccp_timeout_closing",
		.maxlen		= माप(अचिन्हित पूर्णांक),
		.mode		= 0644,
		.proc_handler	= proc_करोपूर्णांकvec_jअगरfies,
	पूर्ण,
	[NF_SYSCTL_CT_PROTO_TIMEOUT_DCCP_TIMEWAIT] = अणु
		.procname	= "nf_conntrack_dccp_timeout_timewait",
		.maxlen		= माप(अचिन्हित पूर्णांक),
		.mode		= 0644,
		.proc_handler	= proc_करोपूर्णांकvec_jअगरfies,
	पूर्ण,
	[NF_SYSCTL_CT_PROTO_DCCP_LOOSE] = अणु
		.procname	= "nf_conntrack_dccp_loose",
		.maxlen		= माप(u8),
		.mode		= 0644,
		.proc_handler	= proc_करोu8vec_minmax,
		.extra1 	= SYSCTL_ZERO,
		.extra2 	= SYSCTL_ONE,
	पूर्ण,
#पूर्ण_अगर
#अगर_घोषित CONFIG_NF_CT_PROTO_GRE
	[NF_SYSCTL_CT_PROTO_TIMEOUT_GRE] = अणु
		.procname       = "nf_conntrack_gre_timeout",
		.maxlen         = माप(अचिन्हित पूर्णांक),
		.mode           = 0644,
		.proc_handler   = proc_करोपूर्णांकvec_jअगरfies,
	पूर्ण,
	[NF_SYSCTL_CT_PROTO_TIMEOUT_GRE_STREAM] = अणु
		.procname       = "nf_conntrack_gre_timeout_stream",
		.maxlen         = माप(अचिन्हित पूर्णांक),
		.mode           = 0644,
		.proc_handler   = proc_करोपूर्णांकvec_jअगरfies,
	पूर्ण,
#पूर्ण_अगर
	अणुपूर्ण
पूर्ण;

अटल काष्ठा ctl_table nf_ct_netfilter_table[] = अणु
	अणु
		.procname	= "nf_conntrack_max",
		.data		= &nf_conntrack_max,
		.maxlen		= माप(पूर्णांक),
		.mode		= 0644,
		.proc_handler	= proc_करोपूर्णांकvec,
	पूर्ण,
	अणु पूर्ण
पूर्ण;

अटल व्योम nf_conntrack_standalone_init_tcp_sysctl(काष्ठा net *net,
						    काष्ठा ctl_table *table)
अणु
	काष्ठा nf_tcp_net *tn = nf_tcp_pernet(net);

#घोषणा XASSIGN(XNAME, tn) \
	table[NF_SYSCTL_CT_PROTO_TIMEOUT_TCP_ ## XNAME].data = \
			&(tn)->समयouts[TCP_CONNTRACK_ ## XNAME]

	XASSIGN(SYN_SENT, tn);
	XASSIGN(SYN_RECV, tn);
	XASSIGN(ESTABLISHED, tn);
	XASSIGN(FIN_WAIT, tn);
	XASSIGN(CLOSE_WAIT, tn);
	XASSIGN(LAST_ACK, tn);
	XASSIGN(TIME_WAIT, tn);
	XASSIGN(CLOSE, tn);
	XASSIGN(RETRANS, tn);
	XASSIGN(UNACK, tn);
#अघोषित XASSIGN
#घोषणा XASSIGN(XNAME, rval) \
	table[NF_SYSCTL_CT_PROTO_TCP_ ## XNAME].data = (rval)

	XASSIGN(LOOSE, &tn->tcp_loose);
	XASSIGN(LIBERAL, &tn->tcp_be_liberal);
	XASSIGN(MAX_RETRANS, &tn->tcp_max_retrans);
#अघोषित XASSIGN
पूर्ण

अटल व्योम nf_conntrack_standalone_init_sctp_sysctl(काष्ठा net *net,
						     काष्ठा ctl_table *table)
अणु
#अगर_घोषित CONFIG_NF_CT_PROTO_SCTP
	काष्ठा nf_sctp_net *sn = nf_sctp_pernet(net);

#घोषणा XASSIGN(XNAME, sn) \
	table[NF_SYSCTL_CT_PROTO_TIMEOUT_SCTP_ ## XNAME].data = \
			&(sn)->समयouts[SCTP_CONNTRACK_ ## XNAME]

	XASSIGN(CLOSED, sn);
	XASSIGN(COOKIE_WAIT, sn);
	XASSIGN(COOKIE_ECHOED, sn);
	XASSIGN(ESTABLISHED, sn);
	XASSIGN(SHUTDOWN_SENT, sn);
	XASSIGN(SHUTDOWN_RECD, sn);
	XASSIGN(SHUTDOWN_ACK_SENT, sn);
	XASSIGN(HEARTBEAT_SENT, sn);
	XASSIGN(HEARTBEAT_ACKED, sn);
#अघोषित XASSIGN
#पूर्ण_अगर
पूर्ण

अटल व्योम nf_conntrack_standalone_init_dccp_sysctl(काष्ठा net *net,
						     काष्ठा ctl_table *table)
अणु
#अगर_घोषित CONFIG_NF_CT_PROTO_DCCP
	काष्ठा nf_dccp_net *dn = nf_dccp_pernet(net);

#घोषणा XASSIGN(XNAME, dn) \
	table[NF_SYSCTL_CT_PROTO_TIMEOUT_DCCP_ ## XNAME].data = \
			&(dn)->dccp_समयout[CT_DCCP_ ## XNAME]

	XASSIGN(REQUEST, dn);
	XASSIGN(RESPOND, dn);
	XASSIGN(PARTOPEN, dn);
	XASSIGN(OPEN, dn);
	XASSIGN(CLOSEREQ, dn);
	XASSIGN(CLOSING, dn);
	XASSIGN(TIMEWAIT, dn);
#अघोषित XASSIGN

	table[NF_SYSCTL_CT_PROTO_DCCP_LOOSE].data = &dn->dccp_loose;
#पूर्ण_अगर
पूर्ण

अटल व्योम nf_conntrack_standalone_init_gre_sysctl(काष्ठा net *net,
						    काष्ठा ctl_table *table)
अणु
#अगर_घोषित CONFIG_NF_CT_PROTO_GRE
	काष्ठा nf_gre_net *gn = nf_gre_pernet(net);

	table[NF_SYSCTL_CT_PROTO_TIMEOUT_GRE].data = &gn->समयouts[GRE_CT_UNREPLIED];
	table[NF_SYSCTL_CT_PROTO_TIMEOUT_GRE_STREAM].data = &gn->समयouts[GRE_CT_REPLIED];
#पूर्ण_अगर
पूर्ण

अटल पूर्णांक nf_conntrack_standalone_init_sysctl(काष्ठा net *net)
अणु
	काष्ठा nf_conntrack_net *cnet = net_generic(net, nf_conntrack_net_id);
	काष्ठा nf_udp_net *un = nf_udp_pernet(net);
	काष्ठा ctl_table *table;

	BUILD_BUG_ON(ARRAY_SIZE(nf_ct_sysctl_table) != NF_SYSCTL_CT_LAST_SYSCTL);

	table = kmemdup(nf_ct_sysctl_table, माप(nf_ct_sysctl_table),
			GFP_KERNEL);
	अगर (!table)
		वापस -ENOMEM;

	table[NF_SYSCTL_CT_COUNT].data = &cnet->count;
	table[NF_SYSCTL_CT_CHECKSUM].data = &net->ct.sysctl_checksum;
	table[NF_SYSCTL_CT_LOG_INVALID].data = &net->ct.sysctl_log_invalid;
	table[NF_SYSCTL_CT_ACCT].data = &net->ct.sysctl_acct;
	table[NF_SYSCTL_CT_HELPER].data = &cnet->sysctl_स्वतः_assign_helper;
#अगर_घोषित CONFIG_NF_CONNTRACK_EVENTS
	table[NF_SYSCTL_CT_EVENTS].data = &net->ct.sysctl_events;
#पूर्ण_अगर
#अगर_घोषित CONFIG_NF_CONNTRACK_TIMESTAMP
	table[NF_SYSCTL_CT_TIMESTAMP].data = &net->ct.sysctl_tstamp;
#पूर्ण_अगर
	table[NF_SYSCTL_CT_PROTO_TIMEOUT_GENERIC].data = &nf_generic_pernet(net)->समयout;
	table[NF_SYSCTL_CT_PROTO_TIMEOUT_ICMP].data = &nf_icmp_pernet(net)->समयout;
	table[NF_SYSCTL_CT_PROTO_TIMEOUT_ICMPV6].data = &nf_icmpv6_pernet(net)->समयout;
	table[NF_SYSCTL_CT_PROTO_TIMEOUT_UDP].data = &un->समयouts[UDP_CT_UNREPLIED];
	table[NF_SYSCTL_CT_PROTO_TIMEOUT_UDP_STREAM].data = &un->समयouts[UDP_CT_REPLIED];

	nf_conntrack_standalone_init_tcp_sysctl(net, table);
	nf_conntrack_standalone_init_sctp_sysctl(net, table);
	nf_conntrack_standalone_init_dccp_sysctl(net, table);
	nf_conntrack_standalone_init_gre_sysctl(net, table);

	/* Don't allow non-init_net ns to alter global sysctls */
	अगर (!net_eq(&init_net, net)) अणु
		table[NF_SYSCTL_CT_MAX].mode = 0444;
		table[NF_SYSCTL_CT_EXPECT_MAX].mode = 0444;
		table[NF_SYSCTL_CT_BUCKETS].mode = 0444;
	पूर्ण

	cnet->sysctl_header = रेजिस्टर_net_sysctl(net, "net/netfilter", table);
	अगर (!cnet->sysctl_header)
		जाओ out_unरेजिस्टर_netfilter;

	वापस 0;

out_unरेजिस्टर_netfilter:
	kमुक्त(table);
	वापस -ENOMEM;
पूर्ण

अटल व्योम nf_conntrack_standalone_fini_sysctl(काष्ठा net *net)
अणु
	काष्ठा nf_conntrack_net *cnet = net_generic(net, nf_conntrack_net_id);
	काष्ठा ctl_table *table;

	table = cnet->sysctl_header->ctl_table_arg;
	unरेजिस्टर_net_sysctl_table(cnet->sysctl_header);
	kमुक्त(table);
पूर्ण
#अन्यथा
अटल पूर्णांक nf_conntrack_standalone_init_sysctl(काष्ठा net *net)
अणु
	वापस 0;
पूर्ण

अटल व्योम nf_conntrack_standalone_fini_sysctl(काष्ठा net *net)
अणु
पूर्ण
#पूर्ण_अगर /* CONFIG_SYSCTL */

अटल व्योम nf_conntrack_fini_net(काष्ठा net *net)
अणु
	अगर (enable_hooks)
		nf_ct_netns_put(net, NFPROTO_INET);

	nf_conntrack_standalone_fini_proc(net);
	nf_conntrack_standalone_fini_sysctl(net);
पूर्ण

अटल पूर्णांक nf_conntrack_pernet_init(काष्ठा net *net)
अणु
	पूर्णांक ret;

	net->ct.sysctl_checksum = 1;

	ret = nf_conntrack_standalone_init_sysctl(net);
	अगर (ret < 0)
		वापस ret;

	ret = nf_conntrack_standalone_init_proc(net);
	अगर (ret < 0)
		जाओ out_proc;

	ret = nf_conntrack_init_net(net);
	अगर (ret < 0)
		जाओ out_init_net;

	अगर (enable_hooks) अणु
		ret = nf_ct_netns_get(net, NFPROTO_INET);
		अगर (ret < 0)
			जाओ out_hooks;
	पूर्ण

	वापस 0;

out_hooks:
	nf_conntrack_cleanup_net(net);
out_init_net:
	nf_conntrack_standalone_fini_proc(net);
out_proc:
	nf_conntrack_standalone_fini_sysctl(net);
	वापस ret;
पूर्ण

अटल व्योम nf_conntrack_pernet_निकास(काष्ठा list_head *net_निकास_list)
अणु
	काष्ठा net *net;

	list_क्रम_each_entry(net, net_निकास_list, निकास_list)
		nf_conntrack_fini_net(net);

	nf_conntrack_cleanup_net_list(net_निकास_list);
पूर्ण

अटल काष्ठा pernet_operations nf_conntrack_net_ops = अणु
	.init		= nf_conntrack_pernet_init,
	.निकास_batch	= nf_conntrack_pernet_निकास,
	.id		= &nf_conntrack_net_id,
	.size = माप(काष्ठा nf_conntrack_net),
पूर्ण;

अटल पूर्णांक __init nf_conntrack_standalone_init(व्योम)
अणु
	पूर्णांक ret = nf_conntrack_init_start();
	अगर (ret < 0)
		जाओ out_start;

	BUILD_BUG_ON(NFCT_INFOMASK <= IP_CT_NUMBER);

#अगर_घोषित CONFIG_SYSCTL
	nf_ct_netfilter_header =
		रेजिस्टर_net_sysctl(&init_net, "net", nf_ct_netfilter_table);
	अगर (!nf_ct_netfilter_header) अणु
		pr_err("nf_conntrack: can't register to sysctl.\n");
		ret = -ENOMEM;
		जाओ out_sysctl;
	पूर्ण

	nf_conntrack_htable_size_user = nf_conntrack_htable_size;
#पूर्ण_अगर

	ret = रेजिस्टर_pernet_subsys(&nf_conntrack_net_ops);
	अगर (ret < 0)
		जाओ out_pernet;

	nf_conntrack_init_end();
	वापस 0;

out_pernet:
#अगर_घोषित CONFIG_SYSCTL
	unरेजिस्टर_net_sysctl_table(nf_ct_netfilter_header);
out_sysctl:
#पूर्ण_अगर
	nf_conntrack_cleanup_end();
out_start:
	वापस ret;
पूर्ण

अटल व्योम __निकास nf_conntrack_standalone_fini(व्योम)
अणु
	nf_conntrack_cleanup_start();
	unरेजिस्टर_pernet_subsys(&nf_conntrack_net_ops);
#अगर_घोषित CONFIG_SYSCTL
	unरेजिस्टर_net_sysctl_table(nf_ct_netfilter_header);
#पूर्ण_अगर
	nf_conntrack_cleanup_end();
पूर्ण

module_init(nf_conntrack_standalone_init);
module_निकास(nf_conntrack_standalone_fini);
