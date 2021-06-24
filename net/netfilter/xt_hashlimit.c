<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 *	xt_hashlimit - Netfilter module to limit the number of packets per समय
 *	separately क्रम each hashbucket (sourceip/sourceport/dstip/dstport)
 *
 *	(C) 2003-2004 by Harald Welte <laक्रमge@netfilter.org>
 *	(C) 2006-2012 Patrick McHardy <kaber@trash.net>
 *	Copyright तऊ CC Computer Consultants GmbH, 2007 - 2008
 *
 * Development of this code was funded by Astaro AG, http://www.astaro.com/
 */
#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt
#समावेश <linux/module.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/अक्रमom.h>
#समावेश <linux/jhash.h>
#समावेश <linux/slab.h>
#समावेश <linux/vदो_स्मृति.h>
#समावेश <linux/proc_fs.h>
#समावेश <linux/seq_file.h>
#समावेश <linux/list.h>
#समावेश <linux/skbuff.h>
#समावेश <linux/mm.h>
#समावेश <linux/in.h>
#समावेश <linux/ip.h>
#अगर IS_ENABLED(CONFIG_IP6_NF_IPTABLES)
#समावेश <linux/ipv6.h>
#समावेश <net/ipv6.h>
#पूर्ण_अगर

#समावेश <net/net_namespace.h>
#समावेश <net/netns/generic.h>

#समावेश <linux/netfilter/x_tables.h>
#समावेश <linux/netfilter_ipv4/ip_tables.h>
#समावेश <linux/netfilter_ipv6/ip6_tables.h>
#समावेश <linux/mutex.h>
#समावेश <linux/kernel.h>
#समावेश <linux/refcount.h>
#समावेश <uapi/linux/netfilter/xt_hashlimit.h>

#घोषणा XT_HASHLIMIT_ALL (XT_HASHLIMIT_HASH_DIP | XT_HASHLIMIT_HASH_DPT | \
			  XT_HASHLIMIT_HASH_SIP | XT_HASHLIMIT_HASH_SPT | \
			  XT_HASHLIMIT_INVERT | XT_HASHLIMIT_BYTES |\
			  XT_HASHLIMIT_RATE_MATCH)

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Harald Welte <laforge@netfilter.org>");
MODULE_AUTHOR("Jan Engelhardt <jengelh@medozas.de>");
MODULE_DESCRIPTION("Xtables: per hash-bucket rate-limit match");
MODULE_ALIAS("ipt_hashlimit");
MODULE_ALIAS("ip6t_hashlimit");

काष्ठा hashlimit_net अणु
	काष्ठा hlist_head	htables;
	काष्ठा proc_dir_entry	*ipt_hashlimit;
	काष्ठा proc_dir_entry	*ip6t_hashlimit;
पूर्ण;

अटल अचिन्हित पूर्णांक hashlimit_net_id;
अटल अंतरभूत काष्ठा hashlimit_net *hashlimit_pernet(काष्ठा net *net)
अणु
	वापस net_generic(net, hashlimit_net_id);
पूर्ण

/* need to declare this at the top */
अटल स्थिर काष्ठा seq_operations dl_seq_ops_v2;
अटल स्थिर काष्ठा seq_operations dl_seq_ops_v1;
अटल स्थिर काष्ठा seq_operations dl_seq_ops;

/* hash table crap */
काष्ठा dsthash_dst अणु
	जोड़ अणु
		काष्ठा अणु
			__be32 src;
			__be32 dst;
		पूर्ण ip;
#अगर IS_ENABLED(CONFIG_IP6_NF_IPTABLES)
		काष्ठा अणु
			__be32 src[4];
			__be32 dst[4];
		पूर्ण ip6;
#पूर्ण_अगर
	पूर्ण;
	__be16 src_port;
	__be16 dst_port;
पूर्ण;

काष्ठा dsthash_ent अणु
	/* अटल / पढ़ो-only parts in the beginning */
	काष्ठा hlist_node node;
	काष्ठा dsthash_dst dst;

	/* modअगरied काष्ठाure members in the end */
	spinlock_t lock;
	अचिन्हित दीर्घ expires;		/* precalculated expiry समय */
	काष्ठा अणु
		अचिन्हित दीर्घ prev;	/* last modअगरication */
		जोड़ अणु
			काष्ठा अणु
				u_पूर्णांक64_t credit;
				u_पूर्णांक64_t credit_cap;
				u_पूर्णांक64_t cost;
			पूर्ण;
			काष्ठा अणु
				u_पूर्णांक32_t पूर्णांकerval, prev_winकरोw;
				u_पूर्णांक64_t current_rate;
				u_पूर्णांक64_t rate;
				पूर्णांक64_t burst;
			पूर्ण;
		पूर्ण;
	पूर्ण rateinfo;
	काष्ठा rcu_head rcu;
पूर्ण;

काष्ठा xt_hashlimit_htable अणु
	काष्ठा hlist_node node;		/* global list of all htables */
	refcount_t use;
	u_पूर्णांक8_t family;
	bool rnd_initialized;

	काष्ठा hashlimit_cfg3 cfg;	/* config */

	/* used पूर्णांकernally */
	spinlock_t lock;		/* lock क्रम list_head */
	u_पूर्णांक32_t rnd;			/* अक्रमom seed क्रम hash */
	अचिन्हित पूर्णांक count;		/* number entries in table */
	काष्ठा delayed_work gc_work;

	/* seq_file stuff */
	काष्ठा proc_dir_entry *pde;
	स्थिर अक्षर *name;
	काष्ठा net *net;

	काष्ठा hlist_head hash[];	/* hashtable itself */
पूर्ण;

अटल पूर्णांक
cfg_copy(काष्ठा hashlimit_cfg3 *to, स्थिर व्योम *from, पूर्णांक revision)
अणु
	अगर (revision == 1) अणु
		काष्ठा hashlimit_cfg1 *cfg = (काष्ठा hashlimit_cfg1 *)from;

		to->mode = cfg->mode;
		to->avg = cfg->avg;
		to->burst = cfg->burst;
		to->size = cfg->size;
		to->max = cfg->max;
		to->gc_पूर्णांकerval = cfg->gc_पूर्णांकerval;
		to->expire = cfg->expire;
		to->srcmask = cfg->srcmask;
		to->dsपंचांगask = cfg->dsपंचांगask;
	पूर्ण अन्यथा अगर (revision == 2) अणु
		काष्ठा hashlimit_cfg2 *cfg = (काष्ठा hashlimit_cfg2 *)from;

		to->mode = cfg->mode;
		to->avg = cfg->avg;
		to->burst = cfg->burst;
		to->size = cfg->size;
		to->max = cfg->max;
		to->gc_पूर्णांकerval = cfg->gc_पूर्णांकerval;
		to->expire = cfg->expire;
		to->srcmask = cfg->srcmask;
		to->dsपंचांगask = cfg->dsपंचांगask;
	पूर्ण अन्यथा अगर (revision == 3) अणु
		स_नकल(to, from, माप(काष्ठा hashlimit_cfg3));
	पूर्ण अन्यथा अणु
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल DEFINE_MUTEX(hashlimit_mutex);	/* protects htables list */
अटल काष्ठा kmem_cache *hashlimit_cachep __पढ़ो_mostly;

अटल अंतरभूत bool dst_cmp(स्थिर काष्ठा dsthash_ent *ent,
			   स्थिर काष्ठा dsthash_dst *b)
अणु
	वापस !स_भेद(&ent->dst, b, माप(ent->dst));
पूर्ण

अटल u_पूर्णांक32_t
hash_dst(स्थिर काष्ठा xt_hashlimit_htable *ht, स्थिर काष्ठा dsthash_dst *dst)
अणु
	u_पूर्णांक32_t hash = jhash2((स्थिर u32 *)dst,
				माप(*dst)/माप(u32),
				ht->rnd);
	/*
	 * Instead of वापसing hash % ht->cfg.size (implying a भागide)
	 * we वापस the high 32 bits of the (hash * ht->cfg.size) that will
	 * give results between [0 and cfg.size-1] and same hash distribution,
	 * but using a multiply, less expensive than a भागide
	 */
	वापस reciprocal_scale(hash, ht->cfg.size);
पूर्ण

अटल काष्ठा dsthash_ent *
dsthash_find(स्थिर काष्ठा xt_hashlimit_htable *ht,
	     स्थिर काष्ठा dsthash_dst *dst)
अणु
	काष्ठा dsthash_ent *ent;
	u_पूर्णांक32_t hash = hash_dst(ht, dst);

	अगर (!hlist_empty(&ht->hash[hash])) अणु
		hlist_क्रम_each_entry_rcu(ent, &ht->hash[hash], node)
			अगर (dst_cmp(ent, dst)) अणु
				spin_lock(&ent->lock);
				वापस ent;
			पूर्ण
	पूर्ण
	वापस शून्य;
पूर्ण

/* allocate dsthash_ent, initialize dst, put in htable and lock it */
अटल काष्ठा dsthash_ent *
dsthash_alloc_init(काष्ठा xt_hashlimit_htable *ht,
		   स्थिर काष्ठा dsthash_dst *dst, bool *race)
अणु
	काष्ठा dsthash_ent *ent;

	spin_lock(&ht->lock);

	/* Two or more packets may race to create the same entry in the
	 * hashtable, द्विगुन check अगर this packet lost race.
	 */
	ent = dsthash_find(ht, dst);
	अगर (ent != शून्य) अणु
		spin_unlock(&ht->lock);
		*race = true;
		वापस ent;
	पूर्ण

	/* initialize hash with अक्रमom val at the समय we allocate
	 * the first hashtable entry */
	अगर (unlikely(!ht->rnd_initialized)) अणु
		get_अक्रमom_bytes(&ht->rnd, माप(ht->rnd));
		ht->rnd_initialized = true;
	पूर्ण

	अगर (ht->cfg.max && ht->count >= ht->cfg.max) अणु
		/* FIXME: करो something. question is what.. */
		net_err_ratelimited("max count of %u reached\n", ht->cfg.max);
		ent = शून्य;
	पूर्ण अन्यथा
		ent = kmem_cache_alloc(hashlimit_cachep, GFP_ATOMIC);
	अगर (ent) अणु
		स_नकल(&ent->dst, dst, माप(ent->dst));
		spin_lock_init(&ent->lock);

		spin_lock(&ent->lock);
		hlist_add_head_rcu(&ent->node, &ht->hash[hash_dst(ht, dst)]);
		ht->count++;
	पूर्ण
	spin_unlock(&ht->lock);
	वापस ent;
पूर्ण

अटल व्योम dsthash_मुक्त_rcu(काष्ठा rcu_head *head)
अणु
	काष्ठा dsthash_ent *ent = container_of(head, काष्ठा dsthash_ent, rcu);

	kmem_cache_मुक्त(hashlimit_cachep, ent);
पूर्ण

अटल अंतरभूत व्योम
dsthash_मुक्त(काष्ठा xt_hashlimit_htable *ht, काष्ठा dsthash_ent *ent)
अणु
	hlist_del_rcu(&ent->node);
	call_rcu(&ent->rcu, dsthash_मुक्त_rcu);
	ht->count--;
पूर्ण
अटल व्योम htable_gc(काष्ठा work_काष्ठा *work);

अटल पूर्णांक htable_create(काष्ठा net *net, काष्ठा hashlimit_cfg3 *cfg,
			 स्थिर अक्षर *name, u_पूर्णांक8_t family,
			 काष्ठा xt_hashlimit_htable **out_hinfo,
			 पूर्णांक revision)
अणु
	काष्ठा hashlimit_net *hashlimit_net = hashlimit_pernet(net);
	काष्ठा xt_hashlimit_htable *hinfo;
	स्थिर काष्ठा seq_operations *ops;
	अचिन्हित पूर्णांक size, i;
	अचिन्हित दीर्घ nr_pages = totalram_pages();
	पूर्णांक ret;

	अगर (cfg->size) अणु
		size = cfg->size;
	पूर्ण अन्यथा अणु
		size = (nr_pages << PAGE_SHIFT) / 16384 /
		       माप(काष्ठा hlist_head);
		अगर (nr_pages > 1024 * 1024 * 1024 / PAGE_SIZE)
			size = 8192;
		अगर (size < 16)
			size = 16;
	पूर्ण
	/* FIXME: करोn't use vदो_स्मृति() here or anywhere अन्यथा -HW */
	hinfo = vदो_स्मृति(काष्ठा_size(hinfo, hash, size));
	अगर (hinfo == शून्य)
		वापस -ENOMEM;
	*out_hinfo = hinfo;

	/* copy match config पूर्णांकo hashtable config */
	ret = cfg_copy(&hinfo->cfg, (व्योम *)cfg, 3);
	अगर (ret) अणु
		vमुक्त(hinfo);
		वापस ret;
	पूर्ण

	hinfo->cfg.size = size;
	अगर (hinfo->cfg.max == 0)
		hinfo->cfg.max = 8 * hinfo->cfg.size;
	अन्यथा अगर (hinfo->cfg.max < hinfo->cfg.size)
		hinfo->cfg.max = hinfo->cfg.size;

	क्रम (i = 0; i < hinfo->cfg.size; i++)
		INIT_HLIST_HEAD(&hinfo->hash[i]);

	refcount_set(&hinfo->use, 1);
	hinfo->count = 0;
	hinfo->family = family;
	hinfo->rnd_initialized = false;
	hinfo->name = kstrdup(name, GFP_KERNEL);
	अगर (!hinfo->name) अणु
		vमुक्त(hinfo);
		वापस -ENOMEM;
	पूर्ण
	spin_lock_init(&hinfo->lock);

	चयन (revision) अणु
	हाल 1:
		ops = &dl_seq_ops_v1;
		अवरोध;
	हाल 2:
		ops = &dl_seq_ops_v2;
		अवरोध;
	शेष:
		ops = &dl_seq_ops;
	पूर्ण

	hinfo->pde = proc_create_seq_data(name, 0,
		(family == NFPROTO_IPV4) ?
		hashlimit_net->ipt_hashlimit : hashlimit_net->ip6t_hashlimit,
		ops, hinfo);
	अगर (hinfo->pde == शून्य) अणु
		kमुक्त(hinfo->name);
		vमुक्त(hinfo);
		वापस -ENOMEM;
	पूर्ण
	hinfo->net = net;

	INIT_DEFERRABLE_WORK(&hinfo->gc_work, htable_gc);
	queue_delayed_work(प्रणाली_घातer_efficient_wq, &hinfo->gc_work,
			   msecs_to_jअगरfies(hinfo->cfg.gc_पूर्णांकerval));

	hlist_add_head(&hinfo->node, &hashlimit_net->htables);

	वापस 0;
पूर्ण

अटल व्योम htable_selective_cleanup(काष्ठा xt_hashlimit_htable *ht, bool select_all)
अणु
	अचिन्हित पूर्णांक i;

	क्रम (i = 0; i < ht->cfg.size; i++) अणु
		काष्ठा dsthash_ent *dh;
		काष्ठा hlist_node *n;

		spin_lock_bh(&ht->lock);
		hlist_क्रम_each_entry_safe(dh, n, &ht->hash[i], node) अणु
			अगर (समय_after_eq(jअगरfies, dh->expires) || select_all)
				dsthash_मुक्त(ht, dh);
		पूर्ण
		spin_unlock_bh(&ht->lock);
		cond_resched();
	पूर्ण
पूर्ण

अटल व्योम htable_gc(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा xt_hashlimit_htable *ht;

	ht = container_of(work, काष्ठा xt_hashlimit_htable, gc_work.work);

	htable_selective_cleanup(ht, false);

	queue_delayed_work(प्रणाली_घातer_efficient_wq,
			   &ht->gc_work, msecs_to_jअगरfies(ht->cfg.gc_पूर्णांकerval));
पूर्ण

अटल व्योम htable_हटाओ_proc_entry(काष्ठा xt_hashlimit_htable *hinfo)
अणु
	काष्ठा hashlimit_net *hashlimit_net = hashlimit_pernet(hinfo->net);
	काष्ठा proc_dir_entry *parent;

	अगर (hinfo->family == NFPROTO_IPV4)
		parent = hashlimit_net->ipt_hashlimit;
	अन्यथा
		parent = hashlimit_net->ip6t_hashlimit;

	अगर (parent != शून्य)
		हटाओ_proc_entry(hinfo->name, parent);
पूर्ण

अटल काष्ठा xt_hashlimit_htable *htable_find_get(काष्ठा net *net,
						   स्थिर अक्षर *name,
						   u_पूर्णांक8_t family)
अणु
	काष्ठा hashlimit_net *hashlimit_net = hashlimit_pernet(net);
	काष्ठा xt_hashlimit_htable *hinfo;

	hlist_क्रम_each_entry(hinfo, &hashlimit_net->htables, node) अणु
		अगर (!म_भेद(name, hinfo->name) &&
		    hinfo->family == family) अणु
			refcount_inc(&hinfo->use);
			वापस hinfo;
		पूर्ण
	पूर्ण
	वापस शून्य;
पूर्ण

अटल व्योम htable_put(काष्ठा xt_hashlimit_htable *hinfo)
अणु
	अगर (refcount_dec_and_mutex_lock(&hinfo->use, &hashlimit_mutex)) अणु
		hlist_del(&hinfo->node);
		htable_हटाओ_proc_entry(hinfo);
		mutex_unlock(&hashlimit_mutex);

		cancel_delayed_work_sync(&hinfo->gc_work);
		htable_selective_cleanup(hinfo, true);
		kमुक्त(hinfo->name);
		vमुक्त(hinfo);
	पूर्ण
पूर्ण

/* The algorithm used is the Simple Token Bucket Filter (TBF)
 * see net/sched/sch_tbf.c in the linux source tree
 */

/* Rusty: This is my (non-mathematically-inclined) understanding of
   this algorithm.  The `average rate' in jअगरfies becomes your initial
   amount of credit `credit' and the most credit you can ever have
   `credit_cap'.  The `peak rate' becomes the cost of passing the
   test, `cost'.

   `prev' tracks the last packet hit: you gain one credit per jअगरfy.
   If you get credit balance more than this, the extra credit is
   discarded.  Every समय the match passes, you lose `cost' credits;
   अगर you करोn't have that many, the test fails.

   See Alexey's क्रमmal explanation in net/sched/sch_tbf.c.

   To get the maximum range, we multiply by this factor (ie. you get N
   credits per jअगरfy).  We want to allow a rate as low as 1 per day
   (slowest userspace tool allows), which means
   CREDITS_PER_JIFFY*HZ*60*60*24 < 2^32 ie.
*/
#घोषणा MAX_CPJ_v1 (0xFFFFFFFF / (HZ*60*60*24))
#घोषणा MAX_CPJ (0xFFFFFFFFFFFFFFFFULL / (HZ*60*60*24))

/* Repeated shअगरt and or gives us all 1s, final shअगरt and add 1 gives
 * us the घातer of 2 below the theoretical max, so GCC simply करोes a
 * shअगरt. */
#घोषणा _POW2_BELOW2(x) ((x)|((x)>>1))
#घोषणा _POW2_BELOW4(x) (_POW2_BELOW2(x)|_POW2_BELOW2((x)>>2))
#घोषणा _POW2_BELOW8(x) (_POW2_BELOW4(x)|_POW2_BELOW4((x)>>4))
#घोषणा _POW2_BELOW16(x) (_POW2_BELOW8(x)|_POW2_BELOW8((x)>>8))
#घोषणा _POW2_BELOW32(x) (_POW2_BELOW16(x)|_POW2_BELOW16((x)>>16))
#घोषणा _POW2_BELOW64(x) (_POW2_BELOW32(x)|_POW2_BELOW32((x)>>32))
#घोषणा POW2_BELOW32(x) ((_POW2_BELOW32(x)>>1) + 1)
#घोषणा POW2_BELOW64(x) ((_POW2_BELOW64(x)>>1) + 1)

#घोषणा CREDITS_PER_JIFFY POW2_BELOW64(MAX_CPJ)
#घोषणा CREDITS_PER_JIFFY_v1 POW2_BELOW32(MAX_CPJ_v1)

/* in byte mode, the lowest possible rate is one packet/second.
 * credit_cap is used as a counter that tells us how many बार we can
 * refill the "credits available" counter when it becomes empty.
 */
#घोषणा MAX_CPJ_BYTES (0xFFFFFFFF / HZ)
#घोषणा CREDITS_PER_JIFFY_BYTES POW2_BELOW32(MAX_CPJ_BYTES)

अटल u32 xt_hashlimit_len_to_chunks(u32 len)
अणु
	वापस (len >> XT_HASHLIMIT_BYTE_SHIFT) + 1;
पूर्ण

/* Precision saver. */
अटल u64 user2credits(u64 user, पूर्णांक revision)
अणु
	u64 scale = (revision == 1) ?
		XT_HASHLIMIT_SCALE : XT_HASHLIMIT_SCALE_v2;
	u64 cpj = (revision == 1) ?
		CREDITS_PER_JIFFY_v1 : CREDITS_PER_JIFFY;

	/* Aव्योम overflow: भागide the स्थिरant opeअक्रमs first */
	अगर (scale >= HZ * cpj)
		वापस भाग64_u64(user, भाग64_u64(scale, HZ * cpj));

	वापस user * भाग64_u64(HZ * cpj, scale);
पूर्ण

अटल u32 user2credits_byte(u32 user)
अणु
	u64 us = user;
	us *= HZ * CREDITS_PER_JIFFY_BYTES;
	वापस (u32) (us >> 32);
पूर्ण

अटल u64 user2rate(u64 user)
अणु
	अगर (user != 0) अणु
		वापस भाग64_u64(XT_HASHLIMIT_SCALE_v2, user);
	पूर्ण अन्यथा अणु
		pr_info_ratelimited("invalid rate from userspace: %llu\n",
				    user);
		वापस 0;
	पूर्ण
पूर्ण

अटल u64 user2rate_bytes(u32 user)
अणु
	u64 r;

	r = user ? U32_MAX / user : U32_MAX;
	वापस (r - 1) << XT_HASHLIMIT_BYTE_SHIFT;
पूर्ण

अटल व्योम rateinfo_recalc(काष्ठा dsthash_ent *dh, अचिन्हित दीर्घ now,
			    u32 mode, पूर्णांक revision)
अणु
	अचिन्हित दीर्घ delta = now - dh->rateinfo.prev;
	u64 cap, cpj;

	अगर (delta == 0)
		वापस;

	अगर (revision >= 3 && mode & XT_HASHLIMIT_RATE_MATCH) अणु
		u64 पूर्णांकerval = dh->rateinfo.पूर्णांकerval * HZ;

		अगर (delta < पूर्णांकerval)
			वापस;

		dh->rateinfo.prev = now;
		dh->rateinfo.prev_winकरोw =
			((dh->rateinfo.current_rate * पूर्णांकerval) >
			 (delta * dh->rateinfo.rate));
		dh->rateinfo.current_rate = 0;

		वापस;
	पूर्ण

	dh->rateinfo.prev = now;

	अगर (mode & XT_HASHLIMIT_BYTES) अणु
		u64 पंचांगp = dh->rateinfo.credit;
		dh->rateinfo.credit += CREDITS_PER_JIFFY_BYTES * delta;
		cap = CREDITS_PER_JIFFY_BYTES * HZ;
		अगर (पंचांगp >= dh->rateinfo.credit) अणु/* overflow */
			dh->rateinfo.credit = cap;
			वापस;
		पूर्ण
	पूर्ण अन्यथा अणु
		cpj = (revision == 1) ?
			CREDITS_PER_JIFFY_v1 : CREDITS_PER_JIFFY;
		dh->rateinfo.credit += delta * cpj;
		cap = dh->rateinfo.credit_cap;
	पूर्ण
	अगर (dh->rateinfo.credit > cap)
		dh->rateinfo.credit = cap;
पूर्ण

अटल व्योम rateinfo_init(काष्ठा dsthash_ent *dh,
			  काष्ठा xt_hashlimit_htable *hinfo, पूर्णांक revision)
अणु
	dh->rateinfo.prev = jअगरfies;
	अगर (revision >= 3 && hinfo->cfg.mode & XT_HASHLIMIT_RATE_MATCH) अणु
		dh->rateinfo.prev_winकरोw = 0;
		dh->rateinfo.current_rate = 0;
		अगर (hinfo->cfg.mode & XT_HASHLIMIT_BYTES) अणु
			dh->rateinfo.rate =
				user2rate_bytes((u32)hinfo->cfg.avg);
			अगर (hinfo->cfg.burst)
				dh->rateinfo.burst =
					hinfo->cfg.burst * dh->rateinfo.rate;
			अन्यथा
				dh->rateinfo.burst = dh->rateinfo.rate;
		पूर्ण अन्यथा अणु
			dh->rateinfo.rate = user2rate(hinfo->cfg.avg);
			dh->rateinfo.burst =
				hinfo->cfg.burst + dh->rateinfo.rate;
		पूर्ण
		dh->rateinfo.पूर्णांकerval = hinfo->cfg.पूर्णांकerval;
	पूर्ण अन्यथा अगर (hinfo->cfg.mode & XT_HASHLIMIT_BYTES) अणु
		dh->rateinfo.credit = CREDITS_PER_JIFFY_BYTES * HZ;
		dh->rateinfo.cost = user2credits_byte(hinfo->cfg.avg);
		dh->rateinfo.credit_cap = hinfo->cfg.burst;
	पूर्ण अन्यथा अणु
		dh->rateinfo.credit = user2credits(hinfo->cfg.avg *
						   hinfo->cfg.burst, revision);
		dh->rateinfo.cost = user2credits(hinfo->cfg.avg, revision);
		dh->rateinfo.credit_cap = dh->rateinfo.credit;
	पूर्ण
पूर्ण

अटल अंतरभूत __be32 maskl(__be32 a, अचिन्हित पूर्णांक l)
अणु
	वापस l ? htonl(ntohl(a) & ~0 << (32 - l)) : 0;
पूर्ण

#अगर IS_ENABLED(CONFIG_IP6_NF_IPTABLES)
अटल व्योम hashlimit_ipv6_mask(__be32 *i, अचिन्हित पूर्णांक p)
अणु
	चयन (p) अणु
	हाल 0 ... 31:
		i[0] = maskl(i[0], p);
		i[1] = i[2] = i[3] = 0;
		अवरोध;
	हाल 32 ... 63:
		i[1] = maskl(i[1], p - 32);
		i[2] = i[3] = 0;
		अवरोध;
	हाल 64 ... 95:
		i[2] = maskl(i[2], p - 64);
		i[3] = 0;
		अवरोध;
	हाल 96 ... 127:
		i[3] = maskl(i[3], p - 96);
		अवरोध;
	हाल 128:
		अवरोध;
	पूर्ण
पूर्ण
#पूर्ण_अगर

अटल पूर्णांक
hashlimit_init_dst(स्थिर काष्ठा xt_hashlimit_htable *hinfo,
		   काष्ठा dsthash_dst *dst,
		   स्थिर काष्ठा sk_buff *skb, अचिन्हित पूर्णांक protoff)
अणु
	__be16 _ports[2], *ports;
	u8 nexthdr;
	पूर्णांक poff;

	स_रखो(dst, 0, माप(*dst));

	चयन (hinfo->family) अणु
	हाल NFPROTO_IPV4:
		अगर (hinfo->cfg.mode & XT_HASHLIMIT_HASH_DIP)
			dst->ip.dst = maskl(ip_hdr(skb)->daddr,
			              hinfo->cfg.dsपंचांगask);
		अगर (hinfo->cfg.mode & XT_HASHLIMIT_HASH_SIP)
			dst->ip.src = maskl(ip_hdr(skb)->saddr,
			              hinfo->cfg.srcmask);

		अगर (!(hinfo->cfg.mode &
		      (XT_HASHLIMIT_HASH_DPT | XT_HASHLIMIT_HASH_SPT)))
			वापस 0;
		nexthdr = ip_hdr(skb)->protocol;
		अवरोध;
#अगर IS_ENABLED(CONFIG_IP6_NF_IPTABLES)
	हाल NFPROTO_IPV6:
	अणु
		__be16 frag_off;

		अगर (hinfo->cfg.mode & XT_HASHLIMIT_HASH_DIP) अणु
			स_नकल(&dst->ip6.dst, &ipv6_hdr(skb)->daddr,
			       माप(dst->ip6.dst));
			hashlimit_ipv6_mask(dst->ip6.dst, hinfo->cfg.dsपंचांगask);
		पूर्ण
		अगर (hinfo->cfg.mode & XT_HASHLIMIT_HASH_SIP) अणु
			स_नकल(&dst->ip6.src, &ipv6_hdr(skb)->saddr,
			       माप(dst->ip6.src));
			hashlimit_ipv6_mask(dst->ip6.src, hinfo->cfg.srcmask);
		पूर्ण

		अगर (!(hinfo->cfg.mode &
		      (XT_HASHLIMIT_HASH_DPT | XT_HASHLIMIT_HASH_SPT)))
			वापस 0;
		nexthdr = ipv6_hdr(skb)->nexthdr;
		protoff = ipv6_skip_exthdr(skb, माप(काष्ठा ipv6hdr), &nexthdr, &frag_off);
		अगर ((पूर्णांक)protoff < 0)
			वापस -1;
		अवरोध;
	पूर्ण
#पूर्ण_अगर
	शेष:
		BUG();
		वापस 0;
	पूर्ण

	poff = proto_ports_offset(nexthdr);
	अगर (poff >= 0) अणु
		ports = skb_header_poपूर्णांकer(skb, protoff + poff, माप(_ports),
					   &_ports);
	पूर्ण अन्यथा अणु
		_ports[0] = _ports[1] = 0;
		ports = _ports;
	पूर्ण
	अगर (!ports)
		वापस -1;
	अगर (hinfo->cfg.mode & XT_HASHLIMIT_HASH_SPT)
		dst->src_port = ports[0];
	अगर (hinfo->cfg.mode & XT_HASHLIMIT_HASH_DPT)
		dst->dst_port = ports[1];
	वापस 0;
पूर्ण

अटल u32 hashlimit_byte_cost(अचिन्हित पूर्णांक len, काष्ठा dsthash_ent *dh)
अणु
	u64 पंचांगp = xt_hashlimit_len_to_chunks(len);
	पंचांगp = पंचांगp * dh->rateinfo.cost;

	अगर (unlikely(पंचांगp > CREDITS_PER_JIFFY_BYTES * HZ))
		पंचांगp = CREDITS_PER_JIFFY_BYTES * HZ;

	अगर (dh->rateinfo.credit < पंचांगp && dh->rateinfo.credit_cap) अणु
		dh->rateinfo.credit_cap--;
		dh->rateinfo.credit = CREDITS_PER_JIFFY_BYTES * HZ;
	पूर्ण
	वापस (u32) पंचांगp;
पूर्ण

अटल bool
hashlimit_mt_common(स्थिर काष्ठा sk_buff *skb, काष्ठा xt_action_param *par,
		    काष्ठा xt_hashlimit_htable *hinfo,
		    स्थिर काष्ठा hashlimit_cfg3 *cfg, पूर्णांक revision)
अणु
	अचिन्हित दीर्घ now = jअगरfies;
	काष्ठा dsthash_ent *dh;
	काष्ठा dsthash_dst dst;
	bool race = false;
	u64 cost;

	अगर (hashlimit_init_dst(hinfo, &dst, skb, par->thoff) < 0)
		जाओ hotdrop;

	local_bh_disable();
	dh = dsthash_find(hinfo, &dst);
	अगर (dh == शून्य) अणु
		dh = dsthash_alloc_init(hinfo, &dst, &race);
		अगर (dh == शून्य) अणु
			local_bh_enable();
			जाओ hotdrop;
		पूर्ण अन्यथा अगर (race) अणु
			/* Alपढ़ोy got an entry, update expiration समयout */
			dh->expires = now + msecs_to_jअगरfies(hinfo->cfg.expire);
			rateinfo_recalc(dh, now, hinfo->cfg.mode, revision);
		पूर्ण अन्यथा अणु
			dh->expires = jअगरfies + msecs_to_jअगरfies(hinfo->cfg.expire);
			rateinfo_init(dh, hinfo, revision);
		पूर्ण
	पूर्ण अन्यथा अणु
		/* update expiration समयout */
		dh->expires = now + msecs_to_jअगरfies(hinfo->cfg.expire);
		rateinfo_recalc(dh, now, hinfo->cfg.mode, revision);
	पूर्ण

	अगर (cfg->mode & XT_HASHLIMIT_RATE_MATCH) अणु
		cost = (cfg->mode & XT_HASHLIMIT_BYTES) ? skb->len : 1;
		dh->rateinfo.current_rate += cost;

		अगर (!dh->rateinfo.prev_winकरोw &&
		    (dh->rateinfo.current_rate <= dh->rateinfo.burst)) अणु
			spin_unlock(&dh->lock);
			local_bh_enable();
			वापस !(cfg->mode & XT_HASHLIMIT_INVERT);
		पूर्ण अन्यथा अणु
			जाओ overlimit;
		पूर्ण
	पूर्ण

	अगर (cfg->mode & XT_HASHLIMIT_BYTES)
		cost = hashlimit_byte_cost(skb->len, dh);
	अन्यथा
		cost = dh->rateinfo.cost;

	अगर (dh->rateinfo.credit >= cost) अणु
		/* below the limit */
		dh->rateinfo.credit -= cost;
		spin_unlock(&dh->lock);
		local_bh_enable();
		वापस !(cfg->mode & XT_HASHLIMIT_INVERT);
	पूर्ण

overlimit:
	spin_unlock(&dh->lock);
	local_bh_enable();
	/* शेष match is underlimit - so over the limit, we need to invert */
	वापस cfg->mode & XT_HASHLIMIT_INVERT;

 hotdrop:
	par->hotdrop = true;
	वापस false;
पूर्ण

अटल bool
hashlimit_mt_v1(स्थिर काष्ठा sk_buff *skb, काष्ठा xt_action_param *par)
अणु
	स्थिर काष्ठा xt_hashlimit_mtinfo1 *info = par->matchinfo;
	काष्ठा xt_hashlimit_htable *hinfo = info->hinfo;
	काष्ठा hashlimit_cfg3 cfg = अणुपूर्ण;
	पूर्णांक ret;

	ret = cfg_copy(&cfg, (व्योम *)&info->cfg, 1);
	अगर (ret)
		वापस ret;

	वापस hashlimit_mt_common(skb, par, hinfo, &cfg, 1);
पूर्ण

अटल bool
hashlimit_mt_v2(स्थिर काष्ठा sk_buff *skb, काष्ठा xt_action_param *par)
अणु
	स्थिर काष्ठा xt_hashlimit_mtinfo2 *info = par->matchinfo;
	काष्ठा xt_hashlimit_htable *hinfo = info->hinfo;
	काष्ठा hashlimit_cfg3 cfg = अणुपूर्ण;
	पूर्णांक ret;

	ret = cfg_copy(&cfg, (व्योम *)&info->cfg, 2);
	अगर (ret)
		वापस ret;

	वापस hashlimit_mt_common(skb, par, hinfo, &cfg, 2);
पूर्ण

अटल bool
hashlimit_mt(स्थिर काष्ठा sk_buff *skb, काष्ठा xt_action_param *par)
अणु
	स्थिर काष्ठा xt_hashlimit_mtinfo3 *info = par->matchinfo;
	काष्ठा xt_hashlimit_htable *hinfo = info->hinfo;

	वापस hashlimit_mt_common(skb, par, hinfo, &info->cfg, 3);
पूर्ण

#घोषणा HASHLIMIT_MAX_SIZE 1048576

अटल पूर्णांक hashlimit_mt_check_common(स्थिर काष्ठा xt_mtchk_param *par,
				     काष्ठा xt_hashlimit_htable **hinfo,
				     काष्ठा hashlimit_cfg3 *cfg,
				     स्थिर अक्षर *name, पूर्णांक revision)
अणु
	काष्ठा net *net = par->net;
	पूर्णांक ret;

	अगर (cfg->gc_पूर्णांकerval == 0 || cfg->expire == 0)
		वापस -EINVAL;
	अगर (cfg->size > HASHLIMIT_MAX_SIZE) अणु
		cfg->size = HASHLIMIT_MAX_SIZE;
		pr_info_ratelimited("size too large, truncated to %u\n", cfg->size);
	पूर्ण
	अगर (cfg->max > HASHLIMIT_MAX_SIZE) अणु
		cfg->max = HASHLIMIT_MAX_SIZE;
		pr_info_ratelimited("max too large, truncated to %u\n", cfg->max);
	पूर्ण
	अगर (par->family == NFPROTO_IPV4) अणु
		अगर (cfg->srcmask > 32 || cfg->dsपंचांगask > 32)
			वापस -EINVAL;
	पूर्ण अन्यथा अणु
		अगर (cfg->srcmask > 128 || cfg->dsपंचांगask > 128)
			वापस -EINVAL;
	पूर्ण

	अगर (cfg->mode & ~XT_HASHLIMIT_ALL) अणु
		pr_info_ratelimited("Unknown mode mask %X, kernel too old?\n",
				    cfg->mode);
		वापस -EINVAL;
	पूर्ण

	/* Check क्रम overflow. */
	अगर (revision >= 3 && cfg->mode & XT_HASHLIMIT_RATE_MATCH) अणु
		अगर (cfg->avg == 0 || cfg->avg > U32_MAX) अणु
			pr_info_ratelimited("invalid rate\n");
			वापस -दुस्फल;
		पूर्ण

		अगर (cfg->पूर्णांकerval == 0) अणु
			pr_info_ratelimited("invalid interval\n");
			वापस -EINVAL;
		पूर्ण
	पूर्ण अन्यथा अगर (cfg->mode & XT_HASHLIMIT_BYTES) अणु
		अगर (user2credits_byte(cfg->avg) == 0) अणु
			pr_info_ratelimited("overflow, rate too high: %llu\n",
					    cfg->avg);
			वापस -EINVAL;
		पूर्ण
	पूर्ण अन्यथा अगर (cfg->burst == 0 ||
		   user2credits(cfg->avg * cfg->burst, revision) <
		   user2credits(cfg->avg, revision)) अणु
		pr_info_ratelimited("overflow, try lower: %llu/%llu\n",
				    cfg->avg, cfg->burst);
		वापस -दुस्फल;
	पूर्ण

	mutex_lock(&hashlimit_mutex);
	*hinfo = htable_find_get(net, name, par->family);
	अगर (*hinfo == शून्य) अणु
		ret = htable_create(net, cfg, name, par->family,
				    hinfo, revision);
		अगर (ret < 0) अणु
			mutex_unlock(&hashlimit_mutex);
			वापस ret;
		पूर्ण
	पूर्ण
	mutex_unlock(&hashlimit_mutex);

	वापस 0;
पूर्ण

अटल पूर्णांक hashlimit_mt_check_v1(स्थिर काष्ठा xt_mtchk_param *par)
अणु
	काष्ठा xt_hashlimit_mtinfo1 *info = par->matchinfo;
	काष्ठा hashlimit_cfg3 cfg = अणुपूर्ण;
	पूर्णांक ret;

	ret = xt_check_proc_name(info->name, माप(info->name));
	अगर (ret)
		वापस ret;

	ret = cfg_copy(&cfg, (व्योम *)&info->cfg, 1);
	अगर (ret)
		वापस ret;

	वापस hashlimit_mt_check_common(par, &info->hinfo,
					 &cfg, info->name, 1);
पूर्ण

अटल पूर्णांक hashlimit_mt_check_v2(स्थिर काष्ठा xt_mtchk_param *par)
अणु
	काष्ठा xt_hashlimit_mtinfo2 *info = par->matchinfo;
	काष्ठा hashlimit_cfg3 cfg = अणुपूर्ण;
	पूर्णांक ret;

	ret = xt_check_proc_name(info->name, माप(info->name));
	अगर (ret)
		वापस ret;

	ret = cfg_copy(&cfg, (व्योम *)&info->cfg, 2);
	अगर (ret)
		वापस ret;

	वापस hashlimit_mt_check_common(par, &info->hinfo,
					 &cfg, info->name, 2);
पूर्ण

अटल पूर्णांक hashlimit_mt_check(स्थिर काष्ठा xt_mtchk_param *par)
अणु
	काष्ठा xt_hashlimit_mtinfo3 *info = par->matchinfo;
	पूर्णांक ret;

	ret = xt_check_proc_name(info->name, माप(info->name));
	अगर (ret)
		वापस ret;

	वापस hashlimit_mt_check_common(par, &info->hinfo, &info->cfg,
					 info->name, 3);
पूर्ण

अटल व्योम hashlimit_mt_destroy_v2(स्थिर काष्ठा xt_mtdtor_param *par)
अणु
	स्थिर काष्ठा xt_hashlimit_mtinfo2 *info = par->matchinfo;

	htable_put(info->hinfo);
पूर्ण

अटल व्योम hashlimit_mt_destroy_v1(स्थिर काष्ठा xt_mtdtor_param *par)
अणु
	स्थिर काष्ठा xt_hashlimit_mtinfo1 *info = par->matchinfo;

	htable_put(info->hinfo);
पूर्ण

अटल व्योम hashlimit_mt_destroy(स्थिर काष्ठा xt_mtdtor_param *par)
अणु
	स्थिर काष्ठा xt_hashlimit_mtinfo3 *info = par->matchinfo;

	htable_put(info->hinfo);
पूर्ण

अटल काष्ठा xt_match hashlimit_mt_reg[] __पढ़ो_mostly = अणु
	अणु
		.name           = "hashlimit",
		.revision       = 1,
		.family         = NFPROTO_IPV4,
		.match          = hashlimit_mt_v1,
		.matchsize      = माप(काष्ठा xt_hashlimit_mtinfo1),
		.usersize	= दुरत्व(काष्ठा xt_hashlimit_mtinfo1, hinfo),
		.checkentry     = hashlimit_mt_check_v1,
		.destroy        = hashlimit_mt_destroy_v1,
		.me             = THIS_MODULE,
	पूर्ण,
	अणु
		.name           = "hashlimit",
		.revision       = 2,
		.family         = NFPROTO_IPV4,
		.match          = hashlimit_mt_v2,
		.matchsize      = माप(काष्ठा xt_hashlimit_mtinfo2),
		.usersize	= दुरत्व(काष्ठा xt_hashlimit_mtinfo2, hinfo),
		.checkentry     = hashlimit_mt_check_v2,
		.destroy        = hashlimit_mt_destroy_v2,
		.me             = THIS_MODULE,
	पूर्ण,
	अणु
		.name           = "hashlimit",
		.revision       = 3,
		.family         = NFPROTO_IPV4,
		.match          = hashlimit_mt,
		.matchsize      = माप(काष्ठा xt_hashlimit_mtinfo3),
		.usersize	= दुरत्व(काष्ठा xt_hashlimit_mtinfo3, hinfo),
		.checkentry     = hashlimit_mt_check,
		.destroy        = hashlimit_mt_destroy,
		.me             = THIS_MODULE,
	पूर्ण,
#अगर IS_ENABLED(CONFIG_IP6_NF_IPTABLES)
	अणु
		.name           = "hashlimit",
		.revision       = 1,
		.family         = NFPROTO_IPV6,
		.match          = hashlimit_mt_v1,
		.matchsize      = माप(काष्ठा xt_hashlimit_mtinfo1),
		.usersize	= दुरत्व(काष्ठा xt_hashlimit_mtinfo1, hinfo),
		.checkentry     = hashlimit_mt_check_v1,
		.destroy        = hashlimit_mt_destroy_v1,
		.me             = THIS_MODULE,
	पूर्ण,
	अणु
		.name           = "hashlimit",
		.revision       = 2,
		.family         = NFPROTO_IPV6,
		.match          = hashlimit_mt_v2,
		.matchsize      = माप(काष्ठा xt_hashlimit_mtinfo2),
		.usersize	= दुरत्व(काष्ठा xt_hashlimit_mtinfo2, hinfo),
		.checkentry     = hashlimit_mt_check_v2,
		.destroy        = hashlimit_mt_destroy_v2,
		.me             = THIS_MODULE,
	पूर्ण,
	अणु
		.name           = "hashlimit",
		.revision       = 3,
		.family         = NFPROTO_IPV6,
		.match          = hashlimit_mt,
		.matchsize      = माप(काष्ठा xt_hashlimit_mtinfo3),
		.usersize	= दुरत्व(काष्ठा xt_hashlimit_mtinfo3, hinfo),
		.checkentry     = hashlimit_mt_check,
		.destroy        = hashlimit_mt_destroy,
		.me             = THIS_MODULE,
	पूर्ण,
#पूर्ण_अगर
पूर्ण;

/* PROC stuff */
अटल व्योम *dl_seq_start(काष्ठा seq_file *s, loff_t *pos)
	__acquires(htable->lock)
अणु
	काष्ठा xt_hashlimit_htable *htable = PDE_DATA(file_inode(s->file));
	अचिन्हित पूर्णांक *bucket;

	spin_lock_bh(&htable->lock);
	अगर (*pos >= htable->cfg.size)
		वापस शून्य;

	bucket = kदो_स्मृति(माप(अचिन्हित पूर्णांक), GFP_ATOMIC);
	अगर (!bucket)
		वापस ERR_PTR(-ENOMEM);

	*bucket = *pos;
	वापस bucket;
पूर्ण

अटल व्योम *dl_seq_next(काष्ठा seq_file *s, व्योम *v, loff_t *pos)
अणु
	काष्ठा xt_hashlimit_htable *htable = PDE_DATA(file_inode(s->file));
	अचिन्हित पूर्णांक *bucket = v;

	*pos = ++(*bucket);
	अगर (*pos >= htable->cfg.size) अणु
		kमुक्त(v);
		वापस शून्य;
	पूर्ण
	वापस bucket;
पूर्ण

अटल व्योम dl_seq_stop(काष्ठा seq_file *s, व्योम *v)
	__releases(htable->lock)
अणु
	काष्ठा xt_hashlimit_htable *htable = PDE_DATA(file_inode(s->file));
	अचिन्हित पूर्णांक *bucket = v;

	अगर (!IS_ERR(bucket))
		kमुक्त(bucket);
	spin_unlock_bh(&htable->lock);
पूर्ण

अटल व्योम dl_seq_prपूर्णांक(काष्ठा dsthash_ent *ent, u_पूर्णांक8_t family,
			 काष्ठा seq_file *s)
अणु
	चयन (family) अणु
	हाल NFPROTO_IPV4:
		seq_म_लिखो(s, "%ld %pI4:%u->%pI4:%u %llu %llu %llu\n",
			   (दीर्घ)(ent->expires - jअगरfies)/HZ,
			   &ent->dst.ip.src,
			   ntohs(ent->dst.src_port),
			   &ent->dst.ip.dst,
			   ntohs(ent->dst.dst_port),
			   ent->rateinfo.credit, ent->rateinfo.credit_cap,
			   ent->rateinfo.cost);
		अवरोध;
#अगर IS_ENABLED(CONFIG_IP6_NF_IPTABLES)
	हाल NFPROTO_IPV6:
		seq_म_लिखो(s, "%ld %pI6:%u->%pI6:%u %llu %llu %llu\n",
			   (दीर्घ)(ent->expires - jअगरfies)/HZ,
			   &ent->dst.ip6.src,
			   ntohs(ent->dst.src_port),
			   &ent->dst.ip6.dst,
			   ntohs(ent->dst.dst_port),
			   ent->rateinfo.credit, ent->rateinfo.credit_cap,
			   ent->rateinfo.cost);
		अवरोध;
#पूर्ण_अगर
	शेष:
		BUG();
	पूर्ण
पूर्ण

अटल पूर्णांक dl_seq_real_show_v2(काष्ठा dsthash_ent *ent, u_पूर्णांक8_t family,
			       काष्ठा seq_file *s)
अणु
	काष्ठा xt_hashlimit_htable *ht = PDE_DATA(file_inode(s->file));

	spin_lock(&ent->lock);
	/* recalculate to show accurate numbers */
	rateinfo_recalc(ent, jअगरfies, ht->cfg.mode, 2);

	dl_seq_prपूर्णांक(ent, family, s);

	spin_unlock(&ent->lock);
	वापस seq_has_overflowed(s);
पूर्ण

अटल पूर्णांक dl_seq_real_show_v1(काष्ठा dsthash_ent *ent, u_पूर्णांक8_t family,
			       काष्ठा seq_file *s)
अणु
	काष्ठा xt_hashlimit_htable *ht = PDE_DATA(file_inode(s->file));

	spin_lock(&ent->lock);
	/* recalculate to show accurate numbers */
	rateinfo_recalc(ent, jअगरfies, ht->cfg.mode, 1);

	dl_seq_prपूर्णांक(ent, family, s);

	spin_unlock(&ent->lock);
	वापस seq_has_overflowed(s);
पूर्ण

अटल पूर्णांक dl_seq_real_show(काष्ठा dsthash_ent *ent, u_पूर्णांक8_t family,
			    काष्ठा seq_file *s)
अणु
	काष्ठा xt_hashlimit_htable *ht = PDE_DATA(file_inode(s->file));

	spin_lock(&ent->lock);
	/* recalculate to show accurate numbers */
	rateinfo_recalc(ent, jअगरfies, ht->cfg.mode, 3);

	dl_seq_prपूर्णांक(ent, family, s);

	spin_unlock(&ent->lock);
	वापस seq_has_overflowed(s);
पूर्ण

अटल पूर्णांक dl_seq_show_v2(काष्ठा seq_file *s, व्योम *v)
अणु
	काष्ठा xt_hashlimit_htable *htable = PDE_DATA(file_inode(s->file));
	अचिन्हित पूर्णांक *bucket = (अचिन्हित पूर्णांक *)v;
	काष्ठा dsthash_ent *ent;

	अगर (!hlist_empty(&htable->hash[*bucket])) अणु
		hlist_क्रम_each_entry(ent, &htable->hash[*bucket], node)
			अगर (dl_seq_real_show_v2(ent, htable->family, s))
				वापस -1;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक dl_seq_show_v1(काष्ठा seq_file *s, व्योम *v)
अणु
	काष्ठा xt_hashlimit_htable *htable = PDE_DATA(file_inode(s->file));
	अचिन्हित पूर्णांक *bucket = v;
	काष्ठा dsthash_ent *ent;

	अगर (!hlist_empty(&htable->hash[*bucket])) अणु
		hlist_क्रम_each_entry(ent, &htable->hash[*bucket], node)
			अगर (dl_seq_real_show_v1(ent, htable->family, s))
				वापस -1;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक dl_seq_show(काष्ठा seq_file *s, व्योम *v)
अणु
	काष्ठा xt_hashlimit_htable *htable = PDE_DATA(file_inode(s->file));
	अचिन्हित पूर्णांक *bucket = v;
	काष्ठा dsthash_ent *ent;

	अगर (!hlist_empty(&htable->hash[*bucket])) अणु
		hlist_क्रम_each_entry(ent, &htable->hash[*bucket], node)
			अगर (dl_seq_real_show(ent, htable->family, s))
				वापस -1;
	पूर्ण
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा seq_operations dl_seq_ops_v1 = अणु
	.start = dl_seq_start,
	.next  = dl_seq_next,
	.stop  = dl_seq_stop,
	.show  = dl_seq_show_v1
पूर्ण;

अटल स्थिर काष्ठा seq_operations dl_seq_ops_v2 = अणु
	.start = dl_seq_start,
	.next  = dl_seq_next,
	.stop  = dl_seq_stop,
	.show  = dl_seq_show_v2
पूर्ण;

अटल स्थिर काष्ठा seq_operations dl_seq_ops = अणु
	.start = dl_seq_start,
	.next  = dl_seq_next,
	.stop  = dl_seq_stop,
	.show  = dl_seq_show
पूर्ण;

अटल पूर्णांक __net_init hashlimit_proc_net_init(काष्ठा net *net)
अणु
	काष्ठा hashlimit_net *hashlimit_net = hashlimit_pernet(net);

	hashlimit_net->ipt_hashlimit = proc_सूची_गढ़ो("ipt_hashlimit", net->proc_net);
	अगर (!hashlimit_net->ipt_hashlimit)
		वापस -ENOMEM;
#अगर IS_ENABLED(CONFIG_IP6_NF_IPTABLES)
	hashlimit_net->ip6t_hashlimit = proc_सूची_गढ़ो("ip6t_hashlimit", net->proc_net);
	अगर (!hashlimit_net->ip6t_hashlimit) अणु
		हटाओ_proc_entry("ipt_hashlimit", net->proc_net);
		वापस -ENOMEM;
	पूर्ण
#पूर्ण_अगर
	वापस 0;
पूर्ण

अटल व्योम __net_निकास hashlimit_proc_net_निकास(काष्ठा net *net)
अणु
	काष्ठा xt_hashlimit_htable *hinfo;
	काष्ठा hashlimit_net *hashlimit_net = hashlimit_pernet(net);

	/* hashlimit_net_निकास() is called beक्रमe hashlimit_mt_destroy().
	 * Make sure that the parent ipt_hashlimit and ip6t_hashlimit proc
	 * entries is empty beक्रमe trying to हटाओ it.
	 */
	mutex_lock(&hashlimit_mutex);
	hlist_क्रम_each_entry(hinfo, &hashlimit_net->htables, node)
		htable_हटाओ_proc_entry(hinfo);
	hashlimit_net->ipt_hashlimit = शून्य;
	hashlimit_net->ip6t_hashlimit = शून्य;
	mutex_unlock(&hashlimit_mutex);

	हटाओ_proc_entry("ipt_hashlimit", net->proc_net);
#अगर IS_ENABLED(CONFIG_IP6_NF_IPTABLES)
	हटाओ_proc_entry("ip6t_hashlimit", net->proc_net);
#पूर्ण_अगर
पूर्ण

अटल पूर्णांक __net_init hashlimit_net_init(काष्ठा net *net)
अणु
	काष्ठा hashlimit_net *hashlimit_net = hashlimit_pernet(net);

	INIT_HLIST_HEAD(&hashlimit_net->htables);
	वापस hashlimit_proc_net_init(net);
पूर्ण

अटल व्योम __net_निकास hashlimit_net_निकास(काष्ठा net *net)
अणु
	hashlimit_proc_net_निकास(net);
पूर्ण

अटल काष्ठा pernet_operations hashlimit_net_ops = अणु
	.init	= hashlimit_net_init,
	.निकास	= hashlimit_net_निकास,
	.id	= &hashlimit_net_id,
	.size	= माप(काष्ठा hashlimit_net),
पूर्ण;

अटल पूर्णांक __init hashlimit_mt_init(व्योम)
अणु
	पूर्णांक err;

	err = रेजिस्टर_pernet_subsys(&hashlimit_net_ops);
	अगर (err < 0)
		वापस err;
	err = xt_रेजिस्टर_matches(hashlimit_mt_reg,
	      ARRAY_SIZE(hashlimit_mt_reg));
	अगर (err < 0)
		जाओ err1;

	err = -ENOMEM;
	hashlimit_cachep = kmem_cache_create("xt_hashlimit",
					    माप(काष्ठा dsthash_ent), 0, 0,
					    शून्य);
	अगर (!hashlimit_cachep) अणु
		pr_warn("unable to create slab cache\n");
		जाओ err2;
	पूर्ण
	वापस 0;

err2:
	xt_unरेजिस्टर_matches(hashlimit_mt_reg, ARRAY_SIZE(hashlimit_mt_reg));
err1:
	unरेजिस्टर_pernet_subsys(&hashlimit_net_ops);
	वापस err;

पूर्ण

अटल व्योम __निकास hashlimit_mt_निकास(व्योम)
अणु
	xt_unरेजिस्टर_matches(hashlimit_mt_reg, ARRAY_SIZE(hashlimit_mt_reg));
	unरेजिस्टर_pernet_subsys(&hashlimit_net_ops);

	rcu_barrier();
	kmem_cache_destroy(hashlimit_cachep);
पूर्ण

module_init(hashlimit_mt_init);
module_निकास(hashlimit_mt_निकास);
