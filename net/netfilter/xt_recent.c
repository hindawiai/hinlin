<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (c) 2006 Patrick McHardy <kaber@trash.net>
 * Copyright तऊ CC Computer Consultants GmbH, 2007 - 2008
 *
 * This is a replacement of the old ipt_recent module, which carried the
 * following copyright notice:
 *
 * Author: Stephen Frost <sfrost@snowman.net>
 * Copyright 2002-2003, Stephen Frost, 2.5.x port by laक्रमge@netfilter.org
 */
#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt
#समावेश <linux/init.h>
#समावेश <linux/ip.h>
#समावेश <linux/ipv6.h>
#समावेश <linux/module.h>
#समावेश <linux/moduleparam.h>
#समावेश <linux/proc_fs.h>
#समावेश <linux/seq_file.h>
#समावेश <linux/माला.स>
#समावेश <linux/प्रकार.स>
#समावेश <linux/list.h>
#समावेश <linux/अक्रमom.h>
#समावेश <linux/jhash.h>
#समावेश <linux/bitops.h>
#समावेश <linux/skbuff.h>
#समावेश <linux/inet.h>
#समावेश <linux/slab.h>
#समावेश <linux/vदो_स्मृति.h>
#समावेश <net/net_namespace.h>
#समावेश <net/netns/generic.h>

#समावेश <linux/netfilter/x_tables.h>
#समावेश <linux/netfilter/xt_recent.h>

MODULE_AUTHOR("Patrick McHardy <kaber@trash.net>");
MODULE_AUTHOR("Jan Engelhardt <jengelh@medozas.de>");
MODULE_DESCRIPTION("Xtables: \"recently-seen\" host matching");
MODULE_LICENSE("GPL");
MODULE_ALIAS("ipt_recent");
MODULE_ALIAS("ip6t_recent");

अटल अचिन्हित पूर्णांक ip_list_tot __पढ़ो_mostly = 100;
अटल अचिन्हित पूर्णांक ip_list_hash_size __पढ़ो_mostly;
अटल अचिन्हित पूर्णांक ip_list_perms __पढ़ो_mostly = 0644;
अटल अचिन्हित पूर्णांक ip_list_uid __पढ़ो_mostly;
अटल अचिन्हित पूर्णांक ip_list_gid __पढ़ो_mostly;
module_param(ip_list_tot, uपूर्णांक, 0400);
module_param(ip_list_hash_size, uपूर्णांक, 0400);
module_param(ip_list_perms, uपूर्णांक, 0400);
module_param(ip_list_uid, uपूर्णांक, 0644);
module_param(ip_list_gid, uपूर्णांक, 0644);
MODULE_PARM_DESC(ip_list_tot, "number of IPs to remember per list");
MODULE_PARM_DESC(ip_list_hash_size, "size of hash table used to look up IPs");
MODULE_PARM_DESC(ip_list_perms, "permissions on /proc/net/xt_recent/* files");
MODULE_PARM_DESC(ip_list_uid, "default owner of /proc/net/xt_recent/* files");
MODULE_PARM_DESC(ip_list_gid, "default owning group of /proc/net/xt_recent/* files");

/* retained क्रम backwards compatibility */
अटल अचिन्हित पूर्णांक ip_pkt_list_tot __पढ़ो_mostly;
module_param(ip_pkt_list_tot, uपूर्णांक, 0400);
MODULE_PARM_DESC(ip_pkt_list_tot, "number of packets per IP address to remember (max. 255)");

#घोषणा XT_RECENT_MAX_NSTAMPS	256

काष्ठा recent_entry अणु
	काष्ठा list_head	list;
	काष्ठा list_head	lru_list;
	जोड़ nf_inet_addr	addr;
	u_पूर्णांक16_t		family;
	u_पूर्णांक8_t		ttl;
	u_पूर्णांक8_t		index;
	u_पूर्णांक16_t		nstamps;
	अचिन्हित दीर्घ		stamps[];
पूर्ण;

काष्ठा recent_table अणु
	काष्ठा list_head	list;
	अक्षर			name[XT_RECENT_NAME_LEN];
	जोड़ nf_inet_addr	mask;
	अचिन्हित पूर्णांक		refcnt;
	अचिन्हित पूर्णांक		entries;
	u8			nstamps_max_mask;
	काष्ठा list_head	lru_list;
	काष्ठा list_head	iphash[];
पूर्ण;

काष्ठा recent_net अणु
	काष्ठा list_head	tables;
#अगर_घोषित CONFIG_PROC_FS
	काष्ठा proc_dir_entry	*xt_recent;
#पूर्ण_अगर
पूर्ण;

अटल अचिन्हित पूर्णांक recent_net_id __पढ़ो_mostly;

अटल अंतरभूत काष्ठा recent_net *recent_pernet(काष्ठा net *net)
अणु
	वापस net_generic(net, recent_net_id);
पूर्ण

अटल DEFINE_SPINLOCK(recent_lock);
अटल DEFINE_MUTEX(recent_mutex);

#अगर_घोषित CONFIG_PROC_FS
अटल स्थिर काष्ठा proc_ops recent_mt_proc_ops;
#पूर्ण_अगर

अटल u_पूर्णांक32_t hash_rnd __पढ़ो_mostly;

अटल अंतरभूत अचिन्हित पूर्णांक recent_entry_hash4(स्थिर जोड़ nf_inet_addr *addr)
अणु
	वापस jhash_1word((__क्रमce u32)addr->ip, hash_rnd) &
	       (ip_list_hash_size - 1);
पूर्ण

अटल अंतरभूत अचिन्हित पूर्णांक recent_entry_hash6(स्थिर जोड़ nf_inet_addr *addr)
अणु
	वापस jhash2((u32 *)addr->ip6, ARRAY_SIZE(addr->ip6), hash_rnd) &
	       (ip_list_hash_size - 1);
पूर्ण

अटल काष्ठा recent_entry *
recent_entry_lookup(स्थिर काष्ठा recent_table *table,
		    स्थिर जोड़ nf_inet_addr *addrp, u_पूर्णांक16_t family,
		    u_पूर्णांक8_t ttl)
अणु
	काष्ठा recent_entry *e;
	अचिन्हित पूर्णांक h;

	अगर (family == NFPROTO_IPV4)
		h = recent_entry_hash4(addrp);
	अन्यथा
		h = recent_entry_hash6(addrp);

	list_क्रम_each_entry(e, &table->iphash[h], list)
		अगर (e->family == family &&
		    स_भेद(&e->addr, addrp, माप(e->addr)) == 0 &&
		    (ttl == e->ttl || ttl == 0 || e->ttl == 0))
			वापस e;
	वापस शून्य;
पूर्ण

अटल व्योम recent_entry_हटाओ(काष्ठा recent_table *t, काष्ठा recent_entry *e)
अणु
	list_del(&e->list);
	list_del(&e->lru_list);
	kमुक्त(e);
	t->entries--;
पूर्ण

/*
 * Drop entries with बारtamps older then 'time'.
 */
अटल व्योम recent_entry_reap(काष्ठा recent_table *t, अचिन्हित दीर्घ समय,
			      काष्ठा recent_entry *working, bool update)
अणु
	काष्ठा recent_entry *e;

	/*
	 * The head of the LRU list is always the oldest entry.
	 */
	e = list_entry(t->lru_list.next, काष्ठा recent_entry, lru_list);

	/*
	 * Do not reap the entry which are going to be updated.
	 */
	अगर (e == working && update)
		वापस;

	/*
	 * The last समय stamp is the most recent.
	 */
	अगर (समय_after(समय, e->stamps[e->index-1]))
		recent_entry_हटाओ(t, e);
पूर्ण

अटल काष्ठा recent_entry *
recent_entry_init(काष्ठा recent_table *t, स्थिर जोड़ nf_inet_addr *addr,
		  u_पूर्णांक16_t family, u_पूर्णांक8_t ttl)
अणु
	काष्ठा recent_entry *e;
	अचिन्हित पूर्णांक nstamps_max = t->nstamps_max_mask;

	अगर (t->entries >= ip_list_tot) अणु
		e = list_entry(t->lru_list.next, काष्ठा recent_entry, lru_list);
		recent_entry_हटाओ(t, e);
	पूर्ण

	nstamps_max += 1;
	e = kदो_स्मृति(काष्ठा_size(e, stamps, nstamps_max), GFP_ATOMIC);
	अगर (e == शून्य)
		वापस शून्य;
	स_नकल(&e->addr, addr, माप(e->addr));
	e->ttl       = ttl;
	e->stamps[0] = jअगरfies;
	e->nstamps   = 1;
	e->index     = 1;
	e->family    = family;
	अगर (family == NFPROTO_IPV4)
		list_add_tail(&e->list, &t->iphash[recent_entry_hash4(addr)]);
	अन्यथा
		list_add_tail(&e->list, &t->iphash[recent_entry_hash6(addr)]);
	list_add_tail(&e->lru_list, &t->lru_list);
	t->entries++;
	वापस e;
पूर्ण

अटल व्योम recent_entry_update(काष्ठा recent_table *t, काष्ठा recent_entry *e)
अणु
	e->index &= t->nstamps_max_mask;
	e->stamps[e->index++] = jअगरfies;
	अगर (e->index > e->nstamps)
		e->nstamps = e->index;
	list_move_tail(&e->lru_list, &t->lru_list);
पूर्ण

अटल काष्ठा recent_table *recent_table_lookup(काष्ठा recent_net *recent_net,
						स्थिर अक्षर *name)
अणु
	काष्ठा recent_table *t;

	list_क्रम_each_entry(t, &recent_net->tables, list)
		अगर (!म_भेद(t->name, name))
			वापस t;
	वापस शून्य;
पूर्ण

अटल व्योम recent_table_flush(काष्ठा recent_table *t)
अणु
	काष्ठा recent_entry *e, *next;
	अचिन्हित पूर्णांक i;

	क्रम (i = 0; i < ip_list_hash_size; i++)
		list_क्रम_each_entry_safe(e, next, &t->iphash[i], list)
			recent_entry_हटाओ(t, e);
पूर्ण

अटल bool
recent_mt(स्थिर काष्ठा sk_buff *skb, काष्ठा xt_action_param *par)
अणु
	काष्ठा net *net = xt_net(par);
	काष्ठा recent_net *recent_net = recent_pernet(net);
	स्थिर काष्ठा xt_recent_mtinfo_v1 *info = par->matchinfo;
	काष्ठा recent_table *t;
	काष्ठा recent_entry *e;
	जोड़ nf_inet_addr addr = अणुपूर्ण, addr_mask;
	u_पूर्णांक8_t ttl;
	bool ret = info->invert;

	अगर (xt_family(par) == NFPROTO_IPV4) अणु
		स्थिर काष्ठा iphdr *iph = ip_hdr(skb);

		अगर (info->side == XT_RECENT_DEST)
			addr.ip = iph->daddr;
		अन्यथा
			addr.ip = iph->saddr;

		ttl = iph->ttl;
	पूर्ण अन्यथा अणु
		स्थिर काष्ठा ipv6hdr *iph = ipv6_hdr(skb);

		अगर (info->side == XT_RECENT_DEST)
			स_नकल(&addr.in6, &iph->daddr, माप(addr.in6));
		अन्यथा
			स_नकल(&addr.in6, &iph->saddr, माप(addr.in6));

		ttl = iph->hop_limit;
	पूर्ण

	/* use TTL as seen beक्रमe क्रमwarding */
	अगर (xt_out(par) != शून्य &&
	    (!skb->sk || !net_eq(net, sock_net(skb->sk))))
		ttl++;

	spin_lock_bh(&recent_lock);
	t = recent_table_lookup(recent_net, info->name);

	nf_inet_addr_mask(&addr, &addr_mask, &t->mask);

	e = recent_entry_lookup(t, &addr_mask, xt_family(par),
				(info->check_set & XT_RECENT_TTL) ? ttl : 0);
	अगर (e == शून्य) अणु
		अगर (!(info->check_set & XT_RECENT_SET))
			जाओ out;
		e = recent_entry_init(t, &addr_mask, xt_family(par), ttl);
		अगर (e == शून्य)
			par->hotdrop = true;
		ret = !ret;
		जाओ out;
	पूर्ण

	अगर (info->check_set & XT_RECENT_SET)
		ret = !ret;
	अन्यथा अगर (info->check_set & XT_RECENT_REMOVE) अणु
		recent_entry_हटाओ(t, e);
		ret = !ret;
	पूर्ण अन्यथा अगर (info->check_set & (XT_RECENT_CHECK | XT_RECENT_UPDATE)) अणु
		अचिन्हित दीर्घ समय = jअगरfies - info->seconds * HZ;
		अचिन्हित पूर्णांक i, hits = 0;

		क्रम (i = 0; i < e->nstamps; i++) अणु
			अगर (info->seconds && समय_after(समय, e->stamps[i]))
				जारी;
			अगर (!info->hit_count || ++hits >= info->hit_count) अणु
				ret = !ret;
				अवरोध;
			पूर्ण
		पूर्ण

		/* info->seconds must be non-zero */
		अगर (info->check_set & XT_RECENT_REAP)
			recent_entry_reap(t, समय, e,
				info->check_set & XT_RECENT_UPDATE && ret);
	पूर्ण

	अगर (info->check_set & XT_RECENT_SET ||
	    (info->check_set & XT_RECENT_UPDATE && ret)) अणु
		recent_entry_update(t, e);
		e->ttl = ttl;
	पूर्ण
out:
	spin_unlock_bh(&recent_lock);
	वापस ret;
पूर्ण

अटल व्योम recent_table_मुक्त(व्योम *addr)
अणु
	kvमुक्त(addr);
पूर्ण

अटल पूर्णांक recent_mt_check(स्थिर काष्ठा xt_mtchk_param *par,
			   स्थिर काष्ठा xt_recent_mtinfo_v1 *info)
अणु
	काष्ठा recent_net *recent_net = recent_pernet(par->net);
	काष्ठा recent_table *t;
#अगर_घोषित CONFIG_PROC_FS
	काष्ठा proc_dir_entry *pde;
	kuid_t uid;
	kgid_t gid;
#पूर्ण_अगर
	अचिन्हित पूर्णांक nstamp_mask;
	अचिन्हित पूर्णांक i;
	पूर्णांक ret = -EINVAL;

	net_get_अक्रमom_once(&hash_rnd, माप(hash_rnd));

	अगर (info->check_set & ~XT_RECENT_VALID_FLAGS) अणु
		pr_info_ratelimited("Unsupported userspace flags (%08x)\n",
				    info->check_set);
		वापस -EINVAL;
	पूर्ण
	अगर (hweight8(info->check_set &
		     (XT_RECENT_SET | XT_RECENT_REMOVE |
		      XT_RECENT_CHECK | XT_RECENT_UPDATE)) != 1)
		वापस -EINVAL;
	अगर ((info->check_set & (XT_RECENT_SET | XT_RECENT_REMOVE)) &&
	    (info->seconds || info->hit_count ||
	    (info->check_set & XT_RECENT_MODIFIERS)))
		वापस -EINVAL;
	अगर ((info->check_set & XT_RECENT_REAP) && !info->seconds)
		वापस -EINVAL;
	अगर (info->hit_count >= XT_RECENT_MAX_NSTAMPS) अणु
		pr_info_ratelimited("hitcount (%u) is larger than allowed maximum (%u)\n",
				    info->hit_count, XT_RECENT_MAX_NSTAMPS - 1);
		वापस -EINVAL;
	पूर्ण
	ret = xt_check_proc_name(info->name, माप(info->name));
	अगर (ret)
		वापस ret;

	अगर (ip_pkt_list_tot && info->hit_count < ip_pkt_list_tot)
		nstamp_mask = roundup_घात_of_two(ip_pkt_list_tot) - 1;
	अन्यथा अगर (info->hit_count)
		nstamp_mask = roundup_घात_of_two(info->hit_count) - 1;
	अन्यथा
		nstamp_mask = 32 - 1;

	mutex_lock(&recent_mutex);
	t = recent_table_lookup(recent_net, info->name);
	अगर (t != शून्य) अणु
		अगर (nstamp_mask > t->nstamps_max_mask) अणु
			spin_lock_bh(&recent_lock);
			recent_table_flush(t);
			t->nstamps_max_mask = nstamp_mask;
			spin_unlock_bh(&recent_lock);
		पूर्ण

		t->refcnt++;
		ret = 0;
		जाओ out;
	पूर्ण

	t = kvzalloc(काष्ठा_size(t, iphash, ip_list_hash_size), GFP_KERNEL);
	अगर (t == शून्य) अणु
		ret = -ENOMEM;
		जाओ out;
	पूर्ण
	t->refcnt = 1;
	t->nstamps_max_mask = nstamp_mask;

	स_नकल(&t->mask, &info->mask, माप(t->mask));
	म_नकल(t->name, info->name);
	INIT_LIST_HEAD(&t->lru_list);
	क्रम (i = 0; i < ip_list_hash_size; i++)
		INIT_LIST_HEAD(&t->iphash[i]);
#अगर_घोषित CONFIG_PROC_FS
	uid = make_kuid(&init_user_ns, ip_list_uid);
	gid = make_kgid(&init_user_ns, ip_list_gid);
	अगर (!uid_valid(uid) || !gid_valid(gid)) अणु
		recent_table_मुक्त(t);
		ret = -EINVAL;
		जाओ out;
	पूर्ण
	pde = proc_create_data(t->name, ip_list_perms, recent_net->xt_recent,
			       &recent_mt_proc_ops, t);
	अगर (pde == शून्य) अणु
		recent_table_मुक्त(t);
		ret = -ENOMEM;
		जाओ out;
	पूर्ण
	proc_set_user(pde, uid, gid);
#पूर्ण_अगर
	spin_lock_bh(&recent_lock);
	list_add_tail(&t->list, &recent_net->tables);
	spin_unlock_bh(&recent_lock);
	ret = 0;
out:
	mutex_unlock(&recent_mutex);
	वापस ret;
पूर्ण

अटल पूर्णांक recent_mt_check_v0(स्थिर काष्ठा xt_mtchk_param *par)
अणु
	स्थिर काष्ठा xt_recent_mtinfo_v0 *info_v0 = par->matchinfo;
	काष्ठा xt_recent_mtinfo_v1 info_v1;

	/* Copy revision 0 काष्ठाure to revision 1 */
	स_नकल(&info_v1, info_v0, माप(काष्ठा xt_recent_mtinfo));
	/* Set शेष mask to ensure backward compatible behaviour */
	स_रखो(info_v1.mask.all, 0xFF, माप(info_v1.mask.all));

	वापस recent_mt_check(par, &info_v1);
पूर्ण

अटल पूर्णांक recent_mt_check_v1(स्थिर काष्ठा xt_mtchk_param *par)
अणु
	वापस recent_mt_check(par, par->matchinfo);
पूर्ण

अटल व्योम recent_mt_destroy(स्थिर काष्ठा xt_mtdtor_param *par)
अणु
	काष्ठा recent_net *recent_net = recent_pernet(par->net);
	स्थिर काष्ठा xt_recent_mtinfo_v1 *info = par->matchinfo;
	काष्ठा recent_table *t;

	mutex_lock(&recent_mutex);
	t = recent_table_lookup(recent_net, info->name);
	अगर (--t->refcnt == 0) अणु
		spin_lock_bh(&recent_lock);
		list_del(&t->list);
		spin_unlock_bh(&recent_lock);
#अगर_घोषित CONFIG_PROC_FS
		अगर (recent_net->xt_recent != शून्य)
			हटाओ_proc_entry(t->name, recent_net->xt_recent);
#पूर्ण_अगर
		recent_table_flush(t);
		recent_table_मुक्त(t);
	पूर्ण
	mutex_unlock(&recent_mutex);
पूर्ण

#अगर_घोषित CONFIG_PROC_FS
काष्ठा recent_iter_state अणु
	स्थिर काष्ठा recent_table *table;
	अचिन्हित पूर्णांक		bucket;
पूर्ण;

अटल व्योम *recent_seq_start(काष्ठा seq_file *seq, loff_t *pos)
	__acquires(recent_lock)
अणु
	काष्ठा recent_iter_state *st = seq->निजी;
	स्थिर काष्ठा recent_table *t = st->table;
	काष्ठा recent_entry *e;
	loff_t p = *pos;

	spin_lock_bh(&recent_lock);

	क्रम (st->bucket = 0; st->bucket < ip_list_hash_size; st->bucket++)
		list_क्रम_each_entry(e, &t->iphash[st->bucket], list)
			अगर (p-- == 0)
				वापस e;
	वापस शून्य;
पूर्ण

अटल व्योम *recent_seq_next(काष्ठा seq_file *seq, व्योम *v, loff_t *pos)
अणु
	काष्ठा recent_iter_state *st = seq->निजी;
	स्थिर काष्ठा recent_table *t = st->table;
	स्थिर काष्ठा recent_entry *e = v;
	स्थिर काष्ठा list_head *head = e->list.next;

	(*pos)++;
	जबतक (head == &t->iphash[st->bucket]) अणु
		अगर (++st->bucket >= ip_list_hash_size)
			वापस शून्य;
		head = t->iphash[st->bucket].next;
	पूर्ण
	वापस list_entry(head, काष्ठा recent_entry, list);
पूर्ण

अटल व्योम recent_seq_stop(काष्ठा seq_file *s, व्योम *v)
	__releases(recent_lock)
अणु
	spin_unlock_bh(&recent_lock);
पूर्ण

अटल पूर्णांक recent_seq_show(काष्ठा seq_file *seq, व्योम *v)
अणु
	स्थिर काष्ठा recent_entry *e = v;
	काष्ठा recent_iter_state *st = seq->निजी;
	स्थिर काष्ठा recent_table *t = st->table;
	अचिन्हित पूर्णांक i;

	i = (e->index - 1) & t->nstamps_max_mask;

	अगर (e->family == NFPROTO_IPV4)
		seq_म_लिखो(seq, "src=%pI4 ttl: %u last_seen: %lu oldest_pkt: %u",
			   &e->addr.ip, e->ttl, e->stamps[i], e->index);
	अन्यथा
		seq_म_लिखो(seq, "src=%pI6 ttl: %u last_seen: %lu oldest_pkt: %u",
			   &e->addr.in6, e->ttl, e->stamps[i], e->index);
	क्रम (i = 0; i < e->nstamps; i++)
		seq_म_लिखो(seq, "%s %lu", i ? "," : "", e->stamps[i]);
	seq_अ_दो(seq, '\n');
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा seq_operations recent_seq_ops = अणु
	.start		= recent_seq_start,
	.next		= recent_seq_next,
	.stop		= recent_seq_stop,
	.show		= recent_seq_show,
पूर्ण;

अटल पूर्णांक recent_seq_खोलो(काष्ठा inode *inode, काष्ठा file *file)
अणु
	काष्ठा recent_iter_state *st;

	st = __seq_खोलो_निजी(file, &recent_seq_ops, माप(*st));
	अगर (st == शून्य)
		वापस -ENOMEM;

	st->table    = PDE_DATA(inode);
	वापस 0;
पूर्ण

अटल sमाप_प्रकार
recent_mt_proc_ग_लिखो(काष्ठा file *file, स्थिर अक्षर __user *input,
		     माप_प्रकार size, loff_t *loff)
अणु
	काष्ठा recent_table *t = PDE_DATA(file_inode(file));
	काष्ठा recent_entry *e;
	अक्षर buf[माप("+b335:1d35:1e55:dead:c0de:1715:5afe:c0de")];
	स्थिर अक्षर *c = buf;
	जोड़ nf_inet_addr addr = अणुपूर्ण;
	u_पूर्णांक16_t family;
	bool add, succ;

	अगर (size == 0)
		वापस 0;
	अगर (size > माप(buf))
		size = माप(buf);
	अगर (copy_from_user(buf, input, size) != 0)
		वापस -EFAULT;

	/* Strict protocol! */
	अगर (*loff != 0)
		वापस -ESPIPE;
	चयन (*c) अणु
	हाल '/': /* flush table */
		spin_lock_bh(&recent_lock);
		recent_table_flush(t);
		spin_unlock_bh(&recent_lock);
		वापस size;
	हाल '-': /* हटाओ address */
		add = false;
		अवरोध;
	हाल '+': /* add address */
		add = true;
		अवरोध;
	शेष:
		pr_info_ratelimited("Need \"+ip\", \"-ip\" or \"/\"\n");
		वापस -EINVAL;
	पूर्ण

	++c;
	--size;
	अगर (strnchr(c, size, ':') != शून्य) अणु
		family = NFPROTO_IPV6;
		succ   = in6_pton(c, size, (व्योम *)&addr, '\n', शून्य);
	पूर्ण अन्यथा अणु
		family = NFPROTO_IPV4;
		succ   = in4_pton(c, size, (व्योम *)&addr, '\n', शून्य);
	पूर्ण

	अगर (!succ)
		वापस -EINVAL;

	spin_lock_bh(&recent_lock);
	e = recent_entry_lookup(t, &addr, family, 0);
	अगर (e == शून्य) अणु
		अगर (add)
			recent_entry_init(t, &addr, family, 0);
	पूर्ण अन्यथा अणु
		अगर (add)
			recent_entry_update(t, e);
		अन्यथा
			recent_entry_हटाओ(t, e);
	पूर्ण
	spin_unlock_bh(&recent_lock);
	/* Note we हटाओd one above */
	*loff += size + 1;
	वापस size + 1;
पूर्ण

अटल स्थिर काष्ठा proc_ops recent_mt_proc_ops = अणु
	.proc_खोलो	= recent_seq_खोलो,
	.proc_पढ़ो	= seq_पढ़ो,
	.proc_ग_लिखो	= recent_mt_proc_ग_लिखो,
	.proc_release	= seq_release_निजी,
	.proc_lseek	= seq_lseek,
पूर्ण;

अटल पूर्णांक __net_init recent_proc_net_init(काष्ठा net *net)
अणु
	काष्ठा recent_net *recent_net = recent_pernet(net);

	recent_net->xt_recent = proc_सूची_गढ़ो("xt_recent", net->proc_net);
	अगर (!recent_net->xt_recent)
		वापस -ENOMEM;
	वापस 0;
पूर्ण

अटल व्योम __net_निकास recent_proc_net_निकास(काष्ठा net *net)
अणु
	काष्ठा recent_net *recent_net = recent_pernet(net);
	काष्ठा recent_table *t;

	/* recent_net_निकास() is called beक्रमe recent_mt_destroy(). Make sure
	 * that the parent xt_recent proc entry is empty beक्रमe trying to
	 * हटाओ it.
	 */
	spin_lock_bh(&recent_lock);
	list_क्रम_each_entry(t, &recent_net->tables, list)
	        हटाओ_proc_entry(t->name, recent_net->xt_recent);

	recent_net->xt_recent = शून्य;
	spin_unlock_bh(&recent_lock);

	हटाओ_proc_entry("xt_recent", net->proc_net);
पूर्ण
#अन्यथा
अटल अंतरभूत पूर्णांक recent_proc_net_init(काष्ठा net *net)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत व्योम recent_proc_net_निकास(काष्ठा net *net)
अणु
पूर्ण
#पूर्ण_अगर /* CONFIG_PROC_FS */

अटल पूर्णांक __net_init recent_net_init(काष्ठा net *net)
अणु
	काष्ठा recent_net *recent_net = recent_pernet(net);

	INIT_LIST_HEAD(&recent_net->tables);
	वापस recent_proc_net_init(net);
पूर्ण

अटल व्योम __net_निकास recent_net_निकास(काष्ठा net *net)
अणु
	recent_proc_net_निकास(net);
पूर्ण

अटल काष्ठा pernet_operations recent_net_ops = अणु
	.init	= recent_net_init,
	.निकास	= recent_net_निकास,
	.id	= &recent_net_id,
	.size	= माप(काष्ठा recent_net),
पूर्ण;

अटल काष्ठा xt_match recent_mt_reg[] __पढ़ो_mostly = अणु
	अणु
		.name       = "recent",
		.revision   = 0,
		.family     = NFPROTO_IPV4,
		.match      = recent_mt,
		.matchsize  = माप(काष्ठा xt_recent_mtinfo),
		.checkentry = recent_mt_check_v0,
		.destroy    = recent_mt_destroy,
		.me         = THIS_MODULE,
	पूर्ण,
	अणु
		.name       = "recent",
		.revision   = 0,
		.family     = NFPROTO_IPV6,
		.match      = recent_mt,
		.matchsize  = माप(काष्ठा xt_recent_mtinfo),
		.checkentry = recent_mt_check_v0,
		.destroy    = recent_mt_destroy,
		.me         = THIS_MODULE,
	पूर्ण,
	अणु
		.name       = "recent",
		.revision   = 1,
		.family     = NFPROTO_IPV4,
		.match      = recent_mt,
		.matchsize  = माप(काष्ठा xt_recent_mtinfo_v1),
		.checkentry = recent_mt_check_v1,
		.destroy    = recent_mt_destroy,
		.me         = THIS_MODULE,
	पूर्ण,
	अणु
		.name       = "recent",
		.revision   = 1,
		.family     = NFPROTO_IPV6,
		.match      = recent_mt,
		.matchsize  = माप(काष्ठा xt_recent_mtinfo_v1),
		.checkentry = recent_mt_check_v1,
		.destroy    = recent_mt_destroy,
		.me         = THIS_MODULE,
	पूर्ण
पूर्ण;

अटल पूर्णांक __init recent_mt_init(व्योम)
अणु
	पूर्णांक err;

	BUILD_BUG_ON_NOT_POWER_OF_2(XT_RECENT_MAX_NSTAMPS);

	अगर (!ip_list_tot || ip_pkt_list_tot >= XT_RECENT_MAX_NSTAMPS)
		वापस -EINVAL;
	ip_list_hash_size = 1 << fls(ip_list_tot);

	err = रेजिस्टर_pernet_subsys(&recent_net_ops);
	अगर (err)
		वापस err;
	err = xt_रेजिस्टर_matches(recent_mt_reg, ARRAY_SIZE(recent_mt_reg));
	अगर (err)
		unरेजिस्टर_pernet_subsys(&recent_net_ops);
	वापस err;
पूर्ण

अटल व्योम __निकास recent_mt_निकास(व्योम)
अणु
	xt_unरेजिस्टर_matches(recent_mt_reg, ARRAY_SIZE(recent_mt_reg));
	unरेजिस्टर_pernet_subsys(&recent_net_ops);
पूर्ण

module_init(recent_mt_init);
module_निकास(recent_mt_निकास);
