<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * DECnet       An implementation of the DECnet protocol suite क्रम the LINUX
 *              operating प्रणाली.  DECnet is implemented using the  BSD Socket
 *              पूर्णांकerface as the means of communication with the user level.
 *
 *              DECnet Routing Forwarding Inक्रमmation Base (Routing Tables)
 *
 * Author:      Steve Whitehouse <SteveW@ACM.org>
 *              Mostly copied from the IPv4 routing code
 *
 *
 * Changes:
 *
 */
#समावेश <linux/माला.स>
#समावेश <linux/net.h>
#समावेश <linux/socket.h>
#समावेश <linux/slab.h>
#समावेश <linux/sockios.h>
#समावेश <linux/init.h>
#समावेश <linux/skbuff.h>
#समावेश <linux/rtnetlink.h>
#समावेश <linux/proc_fs.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/समयr.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/atomic.h>
#समावेश <linux/uaccess.h>
#समावेश <linux/route.h> /* RTF_xxx */
#समावेश <net/neighbour.h>
#समावेश <net/netlink.h>
#समावेश <net/tcp.h>
#समावेश <net/dst.h>
#समावेश <net/flow.h>
#समावेश <net/fib_rules.h>
#समावेश <net/dn.h>
#समावेश <net/dn_route.h>
#समावेश <net/dn_fib.h>
#समावेश <net/dn_neigh.h>
#समावेश <net/dn_dev.h>

काष्ठा dn_zone
अणु
	काष्ठा dn_zone		*dz_next;
	काष्ठा dn_fib_node 	**dz_hash;
	पूर्णांक			dz_nent;
	पूर्णांक			dz_भागisor;
	u32			dz_hashmask;
#घोषणा DZ_HASHMASK(dz)	((dz)->dz_hashmask)
	पूर्णांक			dz_order;
	__le16			dz_mask;
#घोषणा DZ_MASK(dz)	((dz)->dz_mask)
पूर्ण;

काष्ठा dn_hash
अणु
	काष्ठा dn_zone	*dh_zones[17];
	काष्ठा dn_zone	*dh_zone_list;
पूर्ण;

#घोषणा dz_key_0(key)		((key).datum = 0)

#घोषणा क्रम_nexthops(fi) अणु पूर्णांक nhsel; स्थिर काष्ठा dn_fib_nh *nh;\
	क्रम(nhsel = 0, nh = (fi)->fib_nh; nhsel < (fi)->fib_nhs; nh++, nhsel++)

#घोषणा endक्रम_nexthops(fi) पूर्ण

#घोषणा DN_MAX_DIVISOR 1024
#घोषणा DN_S_ZOMBIE 1
#घोषणा DN_S_ACCESSED 2

#घोषणा DN_FIB_SCAN(f, fp) \
क्रम( ; ((f) = *(fp)) != शून्य; (fp) = &(f)->fn_next)

#घोषणा DN_FIB_SCAN_KEY(f, fp, key) \
क्रम( ; ((f) = *(fp)) != शून्य && dn_key_eq((f)->fn_key, (key)); (fp) = &(f)->fn_next)

#घोषणा RT_TABLE_MIN 1
#घोषणा DN_FIB_TABLE_HASHSZ 256
अटल काष्ठा hlist_head dn_fib_table_hash[DN_FIB_TABLE_HASHSZ];
अटल DEFINE_RWLOCK(dn_fib_tables_lock);

अटल काष्ठा kmem_cache *dn_hash_kmem __पढ़ो_mostly;
अटल पूर्णांक dn_fib_hash_zombies;

अटल अंतरभूत dn_fib_idx_t dn_hash(dn_fib_key_t key, काष्ठा dn_zone *dz)
अणु
	u16 h = le16_to_cpu(key.datum)>>(16 - dz->dz_order);
	h ^= (h >> 10);
	h ^= (h >> 6);
	h &= DZ_HASHMASK(dz);
	वापस *(dn_fib_idx_t *)&h;
पूर्ण

अटल अंतरभूत dn_fib_key_t dz_key(__le16 dst, काष्ठा dn_zone *dz)
अणु
	dn_fib_key_t k;
	k.datum = dst & DZ_MASK(dz);
	वापस k;
पूर्ण

अटल अंतरभूत काष्ठा dn_fib_node **dn_chain_p(dn_fib_key_t key, काष्ठा dn_zone *dz)
अणु
	वापस &dz->dz_hash[dn_hash(key, dz).datum];
पूर्ण

अटल अंतरभूत काष्ठा dn_fib_node *dz_chain(dn_fib_key_t key, काष्ठा dn_zone *dz)
अणु
	वापस dz->dz_hash[dn_hash(key, dz).datum];
पूर्ण

अटल अंतरभूत पूर्णांक dn_key_eq(dn_fib_key_t a, dn_fib_key_t b)
अणु
	वापस a.datum == b.datum;
पूर्ण

अटल अंतरभूत पूर्णांक dn_key_leq(dn_fib_key_t a, dn_fib_key_t b)
अणु
	वापस a.datum <= b.datum;
पूर्ण

अटल अंतरभूत व्योम dn_rebuild_zone(काष्ठा dn_zone *dz,
				   काष्ठा dn_fib_node **old_ht,
				   पूर्णांक old_भागisor)
अणु
	काष्ठा dn_fib_node *f, **fp, *next;
	पूर्णांक i;

	क्रम(i = 0; i < old_भागisor; i++) अणु
		क्रम(f = old_ht[i]; f; f = next) अणु
			next = f->fn_next;
			क्रम(fp = dn_chain_p(f->fn_key, dz);
				*fp && dn_key_leq((*fp)->fn_key, f->fn_key);
				fp = &(*fp)->fn_next)
				/* NOTHING */;
			f->fn_next = *fp;
			*fp = f;
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम dn_rehash_zone(काष्ठा dn_zone *dz)
अणु
	काष्ठा dn_fib_node **ht, **old_ht;
	पूर्णांक old_भागisor, new_भागisor;
	u32 new_hashmask;

	old_भागisor = dz->dz_भागisor;

	चयन (old_भागisor) अणु
	हाल 16:
		new_भागisor = 256;
		new_hashmask = 0xFF;
		अवरोध;
	शेष:
		prपूर्णांकk(KERN_DEBUG "DECnet: dn_rehash_zone: BUG! %d\n",
		       old_भागisor);
		fallthrough;
	हाल 256:
		new_भागisor = 1024;
		new_hashmask = 0x3FF;
		अवरोध;
	पूर्ण

	ht = kसुस्मृति(new_भागisor, माप(काष्ठा dn_fib_node*), GFP_KERNEL);
	अगर (ht == शून्य)
		वापस;

	ग_लिखो_lock_bh(&dn_fib_tables_lock);
	old_ht = dz->dz_hash;
	dz->dz_hash = ht;
	dz->dz_hashmask = new_hashmask;
	dz->dz_भागisor = new_भागisor;
	dn_rebuild_zone(dz, old_ht, old_भागisor);
	ग_लिखो_unlock_bh(&dn_fib_tables_lock);
	kमुक्त(old_ht);
पूर्ण

अटल व्योम dn_मुक्त_node(काष्ठा dn_fib_node *f)
अणु
	dn_fib_release_info(DN_FIB_INFO(f));
	kmem_cache_मुक्त(dn_hash_kmem, f);
पूर्ण


अटल काष्ठा dn_zone *dn_new_zone(काष्ठा dn_hash *table, पूर्णांक z)
अणु
	पूर्णांक i;
	काष्ठा dn_zone *dz = kzalloc(माप(काष्ठा dn_zone), GFP_KERNEL);
	अगर (!dz)
		वापस शून्य;

	अगर (z) अणु
		dz->dz_भागisor = 16;
		dz->dz_hashmask = 0x0F;
	पूर्ण अन्यथा अणु
		dz->dz_भागisor = 1;
		dz->dz_hashmask = 0;
	पूर्ण

	dz->dz_hash = kसुस्मृति(dz->dz_भागisor, माप(काष्ठा dn_fib_node *), GFP_KERNEL);
	अगर (!dz->dz_hash) अणु
		kमुक्त(dz);
		वापस शून्य;
	पूर्ण

	dz->dz_order = z;
	dz->dz_mask = dnet_make_mask(z);

	क्रम(i = z + 1; i <= 16; i++)
		अगर (table->dh_zones[i])
			अवरोध;

	ग_लिखो_lock_bh(&dn_fib_tables_lock);
	अगर (i>16) अणु
		dz->dz_next = table->dh_zone_list;
		table->dh_zone_list = dz;
	पूर्ण अन्यथा अणु
		dz->dz_next = table->dh_zones[i]->dz_next;
		table->dh_zones[i]->dz_next = dz;
	पूर्ण
	table->dh_zones[z] = dz;
	ग_लिखो_unlock_bh(&dn_fib_tables_lock);
	वापस dz;
पूर्ण


अटल पूर्णांक dn_fib_nh_match(काष्ठा rपंचांगsg *r, काष्ठा nlmsghdr *nlh, काष्ठा nlattr *attrs[], काष्ठा dn_fib_info *fi)
अणु
	काष्ठा rtnexthop *nhp;
	पूर्णांक nhlen;

	अगर (attrs[RTA_PRIORITY] &&
	    nla_get_u32(attrs[RTA_PRIORITY]) != fi->fib_priority)
		वापस 1;

	अगर (attrs[RTA_OIF] || attrs[RTA_GATEWAY]) अणु
		अगर ((!attrs[RTA_OIF] || nla_get_u32(attrs[RTA_OIF]) == fi->fib_nh->nh_oअगर) &&
		    (!attrs[RTA_GATEWAY]  || nla_get_le16(attrs[RTA_GATEWAY]) != fi->fib_nh->nh_gw))
			वापस 0;
		वापस 1;
	पूर्ण

	अगर (!attrs[RTA_MULTIPATH])
		वापस 0;

	nhp = nla_data(attrs[RTA_MULTIPATH]);
	nhlen = nla_len(attrs[RTA_MULTIPATH]);

	क्रम_nexthops(fi) अणु
		पूर्णांक attrlen = nhlen - माप(काष्ठा rtnexthop);
		__le16 gw;

		अगर (attrlen < 0 || (nhlen -= nhp->rtnh_len) < 0)
			वापस -EINVAL;
		अगर (nhp->rtnh_अगरindex && nhp->rtnh_अगरindex != nh->nh_oअगर)
			वापस 1;
		अगर (attrlen) अणु
			काष्ठा nlattr *gw_attr;

			gw_attr = nla_find((काष्ठा nlattr *) (nhp + 1), attrlen, RTA_GATEWAY);
			gw = gw_attr ? nla_get_le16(gw_attr) : 0;

			अगर (gw && gw != nh->nh_gw)
				वापस 1;
		पूर्ण
		nhp = RTNH_NEXT(nhp);
	पूर्ण endक्रम_nexthops(fi);

	वापस 0;
पूर्ण

अटल अंतरभूत माप_प्रकार dn_fib_nlmsg_size(काष्ठा dn_fib_info *fi)
अणु
	माप_प्रकार payload = NLMSG_ALIGN(माप(काष्ठा rपंचांगsg))
			 + nla_total_size(4) /* RTA_TABLE */
			 + nla_total_size(2) /* RTA_DST */
			 + nla_total_size(4) /* RTA_PRIORITY */
			 + nla_total_size(TCP_CA_NAME_MAX); /* RTAX_CC_ALGO */

	/* space क्रम nested metrics */
	payload += nla_total_size((RTAX_MAX * nla_total_size(4)));

	अगर (fi->fib_nhs) अणु
		/* Also handles the special हाल fib_nhs == 1 */

		/* each nexthop is packed in an attribute */
		माप_प्रकार nhsize = nla_total_size(माप(काष्ठा rtnexthop));

		/* may contain a gateway attribute */
		nhsize += nla_total_size(4);

		/* all nexthops are packed in a nested attribute */
		payload += nla_total_size(fi->fib_nhs * nhsize);
	पूर्ण

	वापस payload;
पूर्ण

अटल पूर्णांक dn_fib_dump_info(काष्ठा sk_buff *skb, u32 portid, u32 seq, पूर्णांक event,
			u32 tb_id, u8 type, u8 scope, व्योम *dst, पूर्णांक dst_len,
			काष्ठा dn_fib_info *fi, अचिन्हित पूर्णांक flags)
अणु
	काष्ठा rपंचांगsg *rपंचांग;
	काष्ठा nlmsghdr *nlh;

	nlh = nlmsg_put(skb, portid, seq, event, माप(*rपंचांग), flags);
	अगर (!nlh)
		वापस -EMSGSIZE;

	rपंचांग = nlmsg_data(nlh);
	rपंचांग->rपंचांग_family = AF_DECnet;
	rपंचांग->rपंचांग_dst_len = dst_len;
	rपंचांग->rपंचांग_src_len = 0;
	rपंचांग->rपंचांग_tos = 0;
	rपंचांग->rपंचांग_table = tb_id;
	rपंचांग->rपंचांग_flags = fi->fib_flags;
	rपंचांग->rपंचांग_scope = scope;
	rपंचांग->rपंचांग_type  = type;
	rपंचांग->rपंचांग_protocol = fi->fib_protocol;

	अगर (nla_put_u32(skb, RTA_TABLE, tb_id) < 0)
		जाओ errout;

	अगर (rपंचांग->rपंचांग_dst_len &&
	    nla_put(skb, RTA_DST, 2, dst) < 0)
		जाओ errout;

	अगर (fi->fib_priority &&
	    nla_put_u32(skb, RTA_PRIORITY, fi->fib_priority) < 0)
		जाओ errout;

	अगर (rtnetlink_put_metrics(skb, fi->fib_metrics) < 0)
		जाओ errout;

	अगर (fi->fib_nhs == 1) अणु
		अगर (fi->fib_nh->nh_gw &&
		    nla_put_le16(skb, RTA_GATEWAY, fi->fib_nh->nh_gw) < 0)
			जाओ errout;

		अगर (fi->fib_nh->nh_oअगर &&
		    nla_put_u32(skb, RTA_OIF, fi->fib_nh->nh_oअगर) < 0)
			जाओ errout;
	पूर्ण

	अगर (fi->fib_nhs > 1) अणु
		काष्ठा rtnexthop *nhp;
		काष्ठा nlattr *mp_head;

		mp_head = nla_nest_start_noflag(skb, RTA_MULTIPATH);
		अगर (!mp_head)
			जाओ errout;

		क्रम_nexthops(fi) अणु
			अगर (!(nhp = nla_reserve_nohdr(skb, माप(*nhp))))
				जाओ errout;

			nhp->rtnh_flags = nh->nh_flags & 0xFF;
			nhp->rtnh_hops = nh->nh_weight - 1;
			nhp->rtnh_अगरindex = nh->nh_oअगर;

			अगर (nh->nh_gw &&
			    nla_put_le16(skb, RTA_GATEWAY, nh->nh_gw) < 0)
				जाओ errout;

			nhp->rtnh_len = skb_tail_poपूर्णांकer(skb) - (अचिन्हित अक्षर *)nhp;
		पूर्ण endक्रम_nexthops(fi);

		nla_nest_end(skb, mp_head);
	पूर्ण

	nlmsg_end(skb, nlh);
	वापस 0;

errout:
	nlmsg_cancel(skb, nlh);
	वापस -EMSGSIZE;
पूर्ण


अटल व्योम dn_rपंचांगsg_fib(पूर्णांक event, काष्ठा dn_fib_node *f, पूर्णांक z, u32 tb_id,
			काष्ठा nlmsghdr *nlh, काष्ठा netlink_skb_parms *req)
अणु
	काष्ठा sk_buff *skb;
	u32 portid = req ? req->portid : 0;
	पूर्णांक err = -ENOBUFS;

	skb = nlmsg_new(dn_fib_nlmsg_size(DN_FIB_INFO(f)), GFP_KERNEL);
	अगर (skb == शून्य)
		जाओ errout;

	err = dn_fib_dump_info(skb, portid, nlh->nlmsg_seq, event, tb_id,
			       f->fn_type, f->fn_scope, &f->fn_key, z,
			       DN_FIB_INFO(f), 0);
	अगर (err < 0) अणु
		/* -EMSGSIZE implies BUG in dn_fib_nlmsg_size() */
		WARN_ON(err == -EMSGSIZE);
		kमुक्त_skb(skb);
		जाओ errout;
	पूर्ण
	rtnl_notअगरy(skb, &init_net, portid, RTNLGRP_DECnet_ROUTE, nlh, GFP_KERNEL);
	वापस;
errout:
	अगर (err < 0)
		rtnl_set_sk_err(&init_net, RTNLGRP_DECnet_ROUTE, err);
पूर्ण

अटल __अंतरभूत__ पूर्णांक dn_hash_dump_bucket(काष्ठा sk_buff *skb,
				काष्ठा netlink_callback *cb,
				काष्ठा dn_fib_table *tb,
				काष्ठा dn_zone *dz,
				काष्ठा dn_fib_node *f)
अणु
	पूर्णांक i, s_i;

	s_i = cb->args[4];
	क्रम(i = 0; f; i++, f = f->fn_next) अणु
		अगर (i < s_i)
			जारी;
		अगर (f->fn_state & DN_S_ZOMBIE)
			जारी;
		अगर (dn_fib_dump_info(skb, NETLINK_CB(cb->skb).portid,
				cb->nlh->nlmsg_seq,
				RTM_NEWROUTE,
				tb->n,
				(f->fn_state & DN_S_ZOMBIE) ? 0 : f->fn_type,
				f->fn_scope, &f->fn_key, dz->dz_order,
				f->fn_info, NLM_F_MULTI) < 0) अणु
			cb->args[4] = i;
			वापस -1;
		पूर्ण
	पूर्ण
	cb->args[4] = i;
	वापस skb->len;
पूर्ण

अटल __अंतरभूत__ पूर्णांक dn_hash_dump_zone(काष्ठा sk_buff *skb,
				काष्ठा netlink_callback *cb,
				काष्ठा dn_fib_table *tb,
				काष्ठा dn_zone *dz)
अणु
	पूर्णांक h, s_h;

	s_h = cb->args[3];
	क्रम(h = 0; h < dz->dz_भागisor; h++) अणु
		अगर (h < s_h)
			जारी;
		अगर (h > s_h)
			स_रखो(&cb->args[4], 0, माप(cb->args) - 4*माप(cb->args[0]));
		अगर (dz->dz_hash == शून्य || dz->dz_hash[h] == शून्य)
			जारी;
		अगर (dn_hash_dump_bucket(skb, cb, tb, dz, dz->dz_hash[h]) < 0) अणु
			cb->args[3] = h;
			वापस -1;
		पूर्ण
	पूर्ण
	cb->args[3] = h;
	वापस skb->len;
पूर्ण

अटल पूर्णांक dn_fib_table_dump(काष्ठा dn_fib_table *tb, काष्ठा sk_buff *skb,
				काष्ठा netlink_callback *cb)
अणु
	पूर्णांक m, s_m;
	काष्ठा dn_zone *dz;
	काष्ठा dn_hash *table = (काष्ठा dn_hash *)tb->data;

	s_m = cb->args[2];
	पढ़ो_lock(&dn_fib_tables_lock);
	क्रम(dz = table->dh_zone_list, m = 0; dz; dz = dz->dz_next, m++) अणु
		अगर (m < s_m)
			जारी;
		अगर (m > s_m)
			स_रखो(&cb->args[3], 0, माप(cb->args) - 3*माप(cb->args[0]));

		अगर (dn_hash_dump_zone(skb, cb, tb, dz) < 0) अणु
			cb->args[2] = m;
			पढ़ो_unlock(&dn_fib_tables_lock);
			वापस -1;
		पूर्ण
	पूर्ण
	पढ़ो_unlock(&dn_fib_tables_lock);
	cb->args[2] = m;

	वापस skb->len;
पूर्ण

पूर्णांक dn_fib_dump(काष्ठा sk_buff *skb, काष्ठा netlink_callback *cb)
अणु
	काष्ठा net *net = sock_net(skb->sk);
	अचिन्हित पूर्णांक h, s_h;
	अचिन्हित पूर्णांक e = 0, s_e;
	काष्ठा dn_fib_table *tb;
	पूर्णांक dumped = 0;

	अगर (!net_eq(net, &init_net))
		वापस 0;

	अगर (nlmsg_len(cb->nlh) >= माप(काष्ठा rपंचांगsg) &&
		((काष्ठा rपंचांगsg *)nlmsg_data(cb->nlh))->rपंचांग_flags&RTM_F_CLONED)
			वापस dn_cache_dump(skb, cb);

	s_h = cb->args[0];
	s_e = cb->args[1];

	क्रम (h = s_h; h < DN_FIB_TABLE_HASHSZ; h++, s_h = 0) अणु
		e = 0;
		hlist_क्रम_each_entry(tb, &dn_fib_table_hash[h], hlist) अणु
			अगर (e < s_e)
				जाओ next;
			अगर (dumped)
				स_रखो(&cb->args[2], 0, माप(cb->args) -
						 2 * माप(cb->args[0]));
			अगर (tb->dump(tb, skb, cb) < 0)
				जाओ out;
			dumped = 1;
next:
			e++;
		पूर्ण
	पूर्ण
out:
	cb->args[1] = e;
	cb->args[0] = h;

	वापस skb->len;
पूर्ण

अटल पूर्णांक dn_fib_table_insert(काष्ठा dn_fib_table *tb, काष्ठा rपंचांगsg *r, काष्ठा nlattr *attrs[],
			       काष्ठा nlmsghdr *n, काष्ठा netlink_skb_parms *req)
अणु
	काष्ठा dn_hash *table = (काष्ठा dn_hash *)tb->data;
	काष्ठा dn_fib_node *new_f, *f, **fp, **del_fp;
	काष्ठा dn_zone *dz;
	काष्ठा dn_fib_info *fi;
	पूर्णांक z = r->rपंचांग_dst_len;
	पूर्णांक type = r->rपंचांग_type;
	dn_fib_key_t key;
	पूर्णांक err;

	अगर (z > 16)
		वापस -EINVAL;

	dz = table->dh_zones[z];
	अगर (!dz && !(dz = dn_new_zone(table, z)))
		वापस -ENOBUFS;

	dz_key_0(key);
	अगर (attrs[RTA_DST]) अणु
		__le16 dst = nla_get_le16(attrs[RTA_DST]);
		अगर (dst & ~DZ_MASK(dz))
			वापस -EINVAL;
		key = dz_key(dst, dz);
	पूर्ण

	अगर ((fi = dn_fib_create_info(r, attrs, n, &err)) == शून्य)
		वापस err;

	अगर (dz->dz_nent > (dz->dz_भागisor << 2) &&
			dz->dz_भागisor > DN_MAX_DIVISOR &&
			(z==16 || (1<<z) > dz->dz_भागisor))
		dn_rehash_zone(dz);

	fp = dn_chain_p(key, dz);

	DN_FIB_SCAN(f, fp) अणु
		अगर (dn_key_leq(key, f->fn_key))
			अवरोध;
	पूर्ण

	del_fp = शून्य;

	अगर (f && (f->fn_state & DN_S_ZOMBIE) &&
			dn_key_eq(f->fn_key, key)) अणु
		del_fp = fp;
		fp = &f->fn_next;
		f = *fp;
		जाओ create;
	पूर्ण

	DN_FIB_SCAN_KEY(f, fp, key) अणु
		अगर (fi->fib_priority <= DN_FIB_INFO(f)->fib_priority)
			अवरोध;
	पूर्ण

	अगर (f && dn_key_eq(f->fn_key, key) &&
			fi->fib_priority == DN_FIB_INFO(f)->fib_priority) अणु
		काष्ठा dn_fib_node **ins_fp;

		err = -EEXIST;
		अगर (n->nlmsg_flags & NLM_F_EXCL)
			जाओ out;

		अगर (n->nlmsg_flags & NLM_F_REPLACE) अणु
			del_fp = fp;
			fp = &f->fn_next;
			f = *fp;
			जाओ replace;
		पूर्ण

		ins_fp = fp;
		err = -EEXIST;

		DN_FIB_SCAN_KEY(f, fp, key) अणु
			अगर (fi->fib_priority != DN_FIB_INFO(f)->fib_priority)
				अवरोध;
			अगर (f->fn_type == type &&
			    f->fn_scope == r->rपंचांग_scope &&
			    DN_FIB_INFO(f) == fi)
				जाओ out;
		पूर्ण

		अगर (!(n->nlmsg_flags & NLM_F_APPEND)) अणु
			fp = ins_fp;
			f = *fp;
		पूर्ण
	पूर्ण

create:
	err = -ENOENT;
	अगर (!(n->nlmsg_flags & NLM_F_CREATE))
		जाओ out;

replace:
	err = -ENOBUFS;
	new_f = kmem_cache_zalloc(dn_hash_kmem, GFP_KERNEL);
	अगर (new_f == शून्य)
		जाओ out;

	new_f->fn_key = key;
	new_f->fn_type = type;
	new_f->fn_scope = r->rपंचांग_scope;
	DN_FIB_INFO(new_f) = fi;

	new_f->fn_next = f;
	ग_लिखो_lock_bh(&dn_fib_tables_lock);
	*fp = new_f;
	ग_लिखो_unlock_bh(&dn_fib_tables_lock);
	dz->dz_nent++;

	अगर (del_fp) अणु
		f = *del_fp;
		ग_लिखो_lock_bh(&dn_fib_tables_lock);
		*del_fp = f->fn_next;
		ग_लिखो_unlock_bh(&dn_fib_tables_lock);

		अगर (!(f->fn_state & DN_S_ZOMBIE))
			dn_rपंचांगsg_fib(RTM_DELROUTE, f, z, tb->n, n, req);
		अगर (f->fn_state & DN_S_ACCESSED)
			dn_rt_cache_flush(-1);
		dn_मुक्त_node(f);
		dz->dz_nent--;
	पूर्ण अन्यथा अणु
		dn_rt_cache_flush(-1);
	पूर्ण

	dn_rपंचांगsg_fib(RTM_NEWROUTE, new_f, z, tb->n, n, req);

	वापस 0;
out:
	dn_fib_release_info(fi);
	वापस err;
पूर्ण


अटल पूर्णांक dn_fib_table_delete(काष्ठा dn_fib_table *tb, काष्ठा rपंचांगsg *r, काष्ठा nlattr *attrs[],
			       काष्ठा nlmsghdr *n, काष्ठा netlink_skb_parms *req)
अणु
	काष्ठा dn_hash *table = (काष्ठा dn_hash*)tb->data;
	काष्ठा dn_fib_node **fp, **del_fp, *f;
	पूर्णांक z = r->rपंचांग_dst_len;
	काष्ठा dn_zone *dz;
	dn_fib_key_t key;
	पूर्णांक matched;


	अगर (z > 16)
		वापस -EINVAL;

	अगर ((dz = table->dh_zones[z]) == शून्य)
		वापस -ESRCH;

	dz_key_0(key);
	अगर (attrs[RTA_DST]) अणु
		__le16 dst = nla_get_le16(attrs[RTA_DST]);
		अगर (dst & ~DZ_MASK(dz))
			वापस -EINVAL;
		key = dz_key(dst, dz);
	पूर्ण

	fp = dn_chain_p(key, dz);

	DN_FIB_SCAN(f, fp) अणु
		अगर (dn_key_eq(f->fn_key, key))
			अवरोध;
		अगर (dn_key_leq(key, f->fn_key))
			वापस -ESRCH;
	पूर्ण

	matched = 0;
	del_fp = शून्य;
	DN_FIB_SCAN_KEY(f, fp, key) अणु
		काष्ठा dn_fib_info *fi = DN_FIB_INFO(f);

		अगर (f->fn_state & DN_S_ZOMBIE)
			वापस -ESRCH;

		matched++;

		अगर (del_fp == शून्य &&
				(!r->rपंचांग_type || f->fn_type == r->rपंचांग_type) &&
				(r->rपंचांग_scope == RT_SCOPE_NOWHERE || f->fn_scope == r->rपंचांग_scope) &&
				(!r->rपंचांग_protocol ||
					fi->fib_protocol == r->rपंचांग_protocol) &&
				dn_fib_nh_match(r, n, attrs, fi) == 0)
			del_fp = fp;
	पूर्ण

	अगर (del_fp) अणु
		f = *del_fp;
		dn_rपंचांगsg_fib(RTM_DELROUTE, f, z, tb->n, n, req);

		अगर (matched != 1) अणु
			ग_लिखो_lock_bh(&dn_fib_tables_lock);
			*del_fp = f->fn_next;
			ग_लिखो_unlock_bh(&dn_fib_tables_lock);

			अगर (f->fn_state & DN_S_ACCESSED)
				dn_rt_cache_flush(-1);
			dn_मुक्त_node(f);
			dz->dz_nent--;
		पूर्ण अन्यथा अणु
			f->fn_state |= DN_S_ZOMBIE;
			अगर (f->fn_state & DN_S_ACCESSED) अणु
				f->fn_state &= ~DN_S_ACCESSED;
				dn_rt_cache_flush(-1);
			पूर्ण
			अगर (++dn_fib_hash_zombies > 128)
				dn_fib_flush();
		पूर्ण

		वापस 0;
	पूर्ण

	वापस -ESRCH;
पूर्ण

अटल अंतरभूत पूर्णांक dn_flush_list(काष्ठा dn_fib_node **fp, पूर्णांक z, काष्ठा dn_hash *table)
अणु
	पूर्णांक found = 0;
	काष्ठा dn_fib_node *f;

	जबतक((f = *fp) != शून्य) अणु
		काष्ठा dn_fib_info *fi = DN_FIB_INFO(f);

		अगर (fi && ((f->fn_state & DN_S_ZOMBIE) || (fi->fib_flags & RTNH_F_DEAD))) अणु
			ग_लिखो_lock_bh(&dn_fib_tables_lock);
			*fp = f->fn_next;
			ग_लिखो_unlock_bh(&dn_fib_tables_lock);

			dn_मुक्त_node(f);
			found++;
			जारी;
		पूर्ण
		fp = &f->fn_next;
	पूर्ण

	वापस found;
पूर्ण

अटल पूर्णांक dn_fib_table_flush(काष्ठा dn_fib_table *tb)
अणु
	काष्ठा dn_hash *table = (काष्ठा dn_hash *)tb->data;
	काष्ठा dn_zone *dz;
	पूर्णांक found = 0;

	dn_fib_hash_zombies = 0;
	क्रम(dz = table->dh_zone_list; dz; dz = dz->dz_next) अणु
		पूर्णांक i;
		पूर्णांक पंचांगp = 0;
		क्रम(i = dz->dz_भागisor-1; i >= 0; i--)
			पंचांगp += dn_flush_list(&dz->dz_hash[i], dz->dz_order, table);
		dz->dz_nent -= पंचांगp;
		found += पंचांगp;
	पूर्ण

	वापस found;
पूर्ण

अटल पूर्णांक dn_fib_table_lookup(काष्ठा dn_fib_table *tb, स्थिर काष्ठा flowidn *flp, काष्ठा dn_fib_res *res)
अणु
	पूर्णांक err;
	काष्ठा dn_zone *dz;
	काष्ठा dn_hash *t = (काष्ठा dn_hash *)tb->data;

	पढ़ो_lock(&dn_fib_tables_lock);
	क्रम(dz = t->dh_zone_list; dz; dz = dz->dz_next) अणु
		काष्ठा dn_fib_node *f;
		dn_fib_key_t k = dz_key(flp->daddr, dz);

		क्रम(f = dz_chain(k, dz); f; f = f->fn_next) अणु
			अगर (!dn_key_eq(k, f->fn_key)) अणु
				अगर (dn_key_leq(k, f->fn_key))
					अवरोध;
				अन्यथा
					जारी;
			पूर्ण

			f->fn_state |= DN_S_ACCESSED;

			अगर (f->fn_state&DN_S_ZOMBIE)
				जारी;

			अगर (f->fn_scope < flp->flowidn_scope)
				जारी;

			err = dn_fib_semantic_match(f->fn_type, DN_FIB_INFO(f), flp, res);

			अगर (err == 0) अणु
				res->type = f->fn_type;
				res->scope = f->fn_scope;
				res->prefixlen = dz->dz_order;
				जाओ out;
			पूर्ण
			अगर (err < 0)
				जाओ out;
		पूर्ण
	पूर्ण
	err = 1;
out:
	पढ़ो_unlock(&dn_fib_tables_lock);
	वापस err;
पूर्ण


काष्ठा dn_fib_table *dn_fib_get_table(u32 n, पूर्णांक create)
अणु
	काष्ठा dn_fib_table *t;
	अचिन्हित पूर्णांक h;

	अगर (n < RT_TABLE_MIN)
		वापस शून्य;

	अगर (n > RT_TABLE_MAX)
		वापस शून्य;

	h = n & (DN_FIB_TABLE_HASHSZ - 1);
	rcu_पढ़ो_lock();
	hlist_क्रम_each_entry_rcu(t, &dn_fib_table_hash[h], hlist) अणु
		अगर (t->n == n) अणु
			rcu_पढ़ो_unlock();
			वापस t;
		पूर्ण
	पूर्ण
	rcu_पढ़ो_unlock();

	अगर (!create)
		वापस शून्य;

	अगर (in_पूर्णांकerrupt()) अणु
		net_dbg_ratelimited("DECnet: BUG! Attempt to create routing table from interrupt\n");
		वापस शून्य;
	पूर्ण

	t = kzalloc(माप(काष्ठा dn_fib_table) + माप(काष्ठा dn_hash),
		    GFP_KERNEL);
	अगर (t == शून्य)
		वापस शून्य;

	t->n = n;
	t->insert = dn_fib_table_insert;
	t->delete = dn_fib_table_delete;
	t->lookup = dn_fib_table_lookup;
	t->flush  = dn_fib_table_flush;
	t->dump = dn_fib_table_dump;
	hlist_add_head_rcu(&t->hlist, &dn_fib_table_hash[h]);

	वापस t;
पूर्ण

काष्ठा dn_fib_table *dn_fib_empty_table(व्योम)
अणु
	u32 id;

	क्रम(id = RT_TABLE_MIN; id <= RT_TABLE_MAX; id++)
		अगर (dn_fib_get_table(id, 0) == शून्य)
			वापस dn_fib_get_table(id, 1);
	वापस शून्य;
पूर्ण

व्योम dn_fib_flush(व्योम)
अणु
	पूर्णांक flushed = 0;
	काष्ठा dn_fib_table *tb;
	अचिन्हित पूर्णांक h;

	क्रम (h = 0; h < DN_FIB_TABLE_HASHSZ; h++) अणु
		hlist_क्रम_each_entry(tb, &dn_fib_table_hash[h], hlist)
			flushed += tb->flush(tb);
	पूर्ण

	अगर (flushed)
		dn_rt_cache_flush(-1);
पूर्ण

व्योम __init dn_fib_table_init(व्योम)
अणु
	dn_hash_kmem = kmem_cache_create("dn_fib_info_cache",
					माप(काष्ठा dn_fib_info),
					0, SLAB_HWCACHE_ALIGN,
					शून्य);
पूर्ण

व्योम __निकास dn_fib_table_cleanup(व्योम)
अणु
	काष्ठा dn_fib_table *t;
	काष्ठा hlist_node *next;
	अचिन्हित पूर्णांक h;

	ग_लिखो_lock(&dn_fib_tables_lock);
	क्रम (h = 0; h < DN_FIB_TABLE_HASHSZ; h++) अणु
		hlist_क्रम_each_entry_safe(t, next, &dn_fib_table_hash[h],
					  hlist) अणु
			hlist_del(&t->hlist);
			kमुक्त(t);
		पूर्ण
	पूर्ण
	ग_लिखो_unlock(&dn_fib_tables_lock);
पूर्ण
