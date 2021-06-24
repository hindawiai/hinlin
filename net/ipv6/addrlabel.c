<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * IPv6 Address Label subप्रणाली
 * क्रम the IPv6 "Default" Source Address Selection
 *
 * Copyright (C)2007 USAGI/WIDE Project
 */
/*
 * Author:
 *	YOSHIFUJI Hideaki @ USAGI/WIDE Project <yoshfuji@linux-ipv6.org>
 */

#समावेश <linux/kernel.h>
#समावेश <linux/list.h>
#समावेश <linux/rcupdate.h>
#समावेश <linux/in6.h>
#समावेश <linux/slab.h>
#समावेश <net/addrconf.h>
#समावेश <linux/अगर_addrlabel.h>
#समावेश <linux/netlink.h>
#समावेश <linux/rtnetlink.h>

#अगर 0
#घोषणा ADDRLABEL(x...) prपूर्णांकk(x)
#अन्यथा
#घोषणा ADDRLABEL(x...) करो अणु ; पूर्ण जबतक (0)
#पूर्ण_अगर

/*
 * Policy Table
 */
काष्ठा ip6addrlbl_entry अणु
	काष्ठा in6_addr prefix;
	पूर्णांक prefixlen;
	पूर्णांक अगरindex;
	पूर्णांक addrtype;
	u32 label;
	काष्ठा hlist_node list;
	काष्ठा rcu_head rcu;
पूर्ण;

/*
 * Default policy table (RFC6724 + extensions)
 *
 * prefix		addr_type	label
 * -------------------------------------------------------------------------
 * ::1/128		LOOPBACK	0
 * ::/0			N/A		1
 * 2002::/16		N/A		2
 * ::/96		COMPATv4	3
 * ::ffff:0:0/96	V4MAPPED	4
 * fc00::/7		N/A		5		ULA (RFC 4193)
 * 2001::/32		N/A		6		Tereकरो (RFC 4380)
 * 2001:10::/28		N/A		7		ORCHID (RFC 4843)
 * fec0::/10		N/A		11		Site-local
 *							(deprecated by RFC3879)
 * 3ffe::/16		N/A		12		6bone
 *
 * Note: 0xffffffff is used अगर we करो not have any policies.
 * Note: Labels क्रम ULA and 6to4 are dअगरferent from labels listed in RFC6724.
 */

#घोषणा IPV6_ADDR_LABEL_DEFAULT	0xffffffffUL

अटल स्थिर __net_initस्थिर काष्ठा ip6addrlbl_init_table
अणु
	स्थिर काष्ठा in6_addr *prefix;
	पूर्णांक prefixlen;
	u32 label;
पूर्ण ip6addrlbl_init_table[] = अणु
	अणु	/* ::/0 */
		.prefix = &in6addr_any,
		.label = 1,
	पूर्ण, अणु	/* fc00::/7 */
		.prefix = &(काष्ठा in6_addr)अणु अणु अणु 0xfc पूर्ण पूर्ण पूर्ण ,
		.prefixlen = 7,
		.label = 5,
	पूर्ण, अणु	/* fec0::/10 */
		.prefix = &(काष्ठा in6_addr)अणु अणु अणु 0xfe, 0xc0 पूर्ण पूर्ण पूर्ण,
		.prefixlen = 10,
		.label = 11,
	पूर्ण, अणु	/* 2002::/16 */
		.prefix = &(काष्ठा in6_addr)अणु अणु अणु 0x20, 0x02 पूर्ण पूर्ण पूर्ण,
		.prefixlen = 16,
		.label = 2,
	पूर्ण, अणु	/* 3ffe::/16 */
		.prefix = &(काष्ठा in6_addr)अणु अणु अणु 0x3f, 0xfe पूर्ण पूर्ण पूर्ण,
		.prefixlen = 16,
		.label = 12,
	पूर्ण, अणु	/* 2001::/32 */
		.prefix = &(काष्ठा in6_addr)अणु अणु अणु 0x20, 0x01 पूर्ण पूर्ण पूर्ण,
		.prefixlen = 32,
		.label = 6,
	पूर्ण, अणु	/* 2001:10::/28 */
		.prefix = &(काष्ठा in6_addr)अणु अणु अणु 0x20, 0x01, 0x00, 0x10 पूर्ण पूर्ण पूर्ण,
		.prefixlen = 28,
		.label = 7,
	पूर्ण, अणु	/* ::ffff:0:0 */
		.prefix = &(काष्ठा in6_addr)अणु अणु अणु [10] = 0xff, [11] = 0xff पूर्ण पूर्ण पूर्ण,
		.prefixlen = 96,
		.label = 4,
	पूर्ण, अणु	/* ::/96 */
		.prefix = &in6addr_any,
		.prefixlen = 96,
		.label = 3,
	पूर्ण, अणु	/* ::1/128 */
		.prefix = &in6addr_loopback,
		.prefixlen = 128,
		.label = 0,
	पूर्ण
पूर्ण;

/* Find label */
अटल bool __ip6addrlbl_match(स्थिर काष्ठा ip6addrlbl_entry *p,
			       स्थिर काष्ठा in6_addr *addr,
			       पूर्णांक addrtype, पूर्णांक अगरindex)
अणु
	अगर (p->अगरindex && p->अगरindex != अगरindex)
		वापस false;
	अगर (p->addrtype && p->addrtype != addrtype)
		वापस false;
	अगर (!ipv6_prefix_equal(addr, &p->prefix, p->prefixlen))
		वापस false;
	वापस true;
पूर्ण

अटल काष्ठा ip6addrlbl_entry *__ipv6_addr_label(काष्ठा net *net,
						  स्थिर काष्ठा in6_addr *addr,
						  पूर्णांक type, पूर्णांक अगरindex)
अणु
	काष्ठा ip6addrlbl_entry *p;

	hlist_क्रम_each_entry_rcu(p, &net->ipv6.ip6addrlbl_table.head, list) अणु
		अगर (__ip6addrlbl_match(p, addr, type, अगरindex))
			वापस p;
	पूर्ण
	वापस शून्य;
पूर्ण

u32 ipv6_addr_label(काष्ठा net *net,
		    स्थिर काष्ठा in6_addr *addr, पूर्णांक type, पूर्णांक अगरindex)
अणु
	u32 label;
	काष्ठा ip6addrlbl_entry *p;

	type &= IPV6_ADDR_MAPPED | IPV6_ADDR_COMPATv4 | IPV6_ADDR_LOOPBACK;

	rcu_पढ़ो_lock();
	p = __ipv6_addr_label(net, addr, type, अगरindex);
	label = p ? p->label : IPV6_ADDR_LABEL_DEFAULT;
	rcu_पढ़ो_unlock();

	ADDRLABEL(KERN_DEBUG "%s(addr=%pI6, type=%d, ifindex=%d) => %08x\n",
		  __func__, addr, type, अगरindex, label);

	वापस label;
पूर्ण

/* allocate one entry */
अटल काष्ठा ip6addrlbl_entry *ip6addrlbl_alloc(स्थिर काष्ठा in6_addr *prefix,
						 पूर्णांक prefixlen, पूर्णांक अगरindex,
						 u32 label)
अणु
	काष्ठा ip6addrlbl_entry *newp;
	पूर्णांक addrtype;

	ADDRLABEL(KERN_DEBUG "%s(prefix=%pI6, prefixlen=%d, ifindex=%d, label=%u)\n",
		  __func__, prefix, prefixlen, अगरindex, (अचिन्हित पूर्णांक)label);

	addrtype = ipv6_addr_type(prefix) & (IPV6_ADDR_MAPPED | IPV6_ADDR_COMPATv4 | IPV6_ADDR_LOOPBACK);

	चयन (addrtype) अणु
	हाल IPV6_ADDR_MAPPED:
		अगर (prefixlen > 96)
			वापस ERR_PTR(-EINVAL);
		अगर (prefixlen < 96)
			addrtype = 0;
		अवरोध;
	हाल IPV6_ADDR_COMPATv4:
		अगर (prefixlen != 96)
			addrtype = 0;
		अवरोध;
	हाल IPV6_ADDR_LOOPBACK:
		अगर (prefixlen != 128)
			addrtype = 0;
		अवरोध;
	पूर्ण

	newp = kदो_स्मृति(माप(*newp), GFP_KERNEL);
	अगर (!newp)
		वापस ERR_PTR(-ENOMEM);

	ipv6_addr_prefix(&newp->prefix, prefix, prefixlen);
	newp->prefixlen = prefixlen;
	newp->अगरindex = अगरindex;
	newp->addrtype = addrtype;
	newp->label = label;
	INIT_HLIST_NODE(&newp->list);
	वापस newp;
पूर्ण

/* add a label */
अटल पूर्णांक __ip6addrlbl_add(काष्ठा net *net, काष्ठा ip6addrlbl_entry *newp,
			    पूर्णांक replace)
अणु
	काष्ठा ip6addrlbl_entry *last = शून्य, *p = शून्य;
	काष्ठा hlist_node *n;
	पूर्णांक ret = 0;

	ADDRLABEL(KERN_DEBUG "%s(newp=%p, replace=%d)\n", __func__, newp,
		  replace);

	hlist_क्रम_each_entry_safe(p, n,	&net->ipv6.ip6addrlbl_table.head, list) अणु
		अगर (p->prefixlen == newp->prefixlen &&
		    p->अगरindex == newp->अगरindex &&
		    ipv6_addr_equal(&p->prefix, &newp->prefix)) अणु
			अगर (!replace) अणु
				ret = -EEXIST;
				जाओ out;
			पूर्ण
			hlist_replace_rcu(&p->list, &newp->list);
			kमुक्त_rcu(p, rcu);
			जाओ out;
		पूर्ण अन्यथा अगर ((p->prefixlen == newp->prefixlen && !p->अगरindex) ||
			   (p->prefixlen < newp->prefixlen)) अणु
			hlist_add_beक्रमe_rcu(&newp->list, &p->list);
			जाओ out;
		पूर्ण
		last = p;
	पूर्ण
	अगर (last)
		hlist_add_behind_rcu(&newp->list, &last->list);
	अन्यथा
		hlist_add_head_rcu(&newp->list, &net->ipv6.ip6addrlbl_table.head);
out:
	अगर (!ret)
		net->ipv6.ip6addrlbl_table.seq++;
	वापस ret;
पूर्ण

/* add a label */
अटल पूर्णांक ip6addrlbl_add(काष्ठा net *net,
			  स्थिर काष्ठा in6_addr *prefix, पूर्णांक prefixlen,
			  पूर्णांक अगरindex, u32 label, पूर्णांक replace)
अणु
	काष्ठा ip6addrlbl_entry *newp;
	पूर्णांक ret = 0;

	ADDRLABEL(KERN_DEBUG "%s(prefix=%pI6, prefixlen=%d, ifindex=%d, label=%u, replace=%d)\n",
		  __func__, prefix, prefixlen, अगरindex, (अचिन्हित पूर्णांक)label,
		  replace);

	newp = ip6addrlbl_alloc(prefix, prefixlen, अगरindex, label);
	अगर (IS_ERR(newp))
		वापस PTR_ERR(newp);
	spin_lock(&net->ipv6.ip6addrlbl_table.lock);
	ret = __ip6addrlbl_add(net, newp, replace);
	spin_unlock(&net->ipv6.ip6addrlbl_table.lock);
	अगर (ret)
		kमुक्त(newp);
	वापस ret;
पूर्ण

/* हटाओ a label */
अटल पूर्णांक __ip6addrlbl_del(काष्ठा net *net,
			    स्थिर काष्ठा in6_addr *prefix, पूर्णांक prefixlen,
			    पूर्णांक अगरindex)
अणु
	काष्ठा ip6addrlbl_entry *p = शून्य;
	काष्ठा hlist_node *n;
	पूर्णांक ret = -ESRCH;

	ADDRLABEL(KERN_DEBUG "%s(prefix=%pI6, prefixlen=%d, ifindex=%d)\n",
		  __func__, prefix, prefixlen, अगरindex);

	hlist_क्रम_each_entry_safe(p, n, &net->ipv6.ip6addrlbl_table.head, list) अणु
		अगर (p->prefixlen == prefixlen &&
		    p->अगरindex == अगरindex &&
		    ipv6_addr_equal(&p->prefix, prefix)) अणु
			hlist_del_rcu(&p->list);
			kमुक्त_rcu(p, rcu);
			ret = 0;
			अवरोध;
		पूर्ण
	पूर्ण
	वापस ret;
पूर्ण

अटल पूर्णांक ip6addrlbl_del(काष्ठा net *net,
			  स्थिर काष्ठा in6_addr *prefix, पूर्णांक prefixlen,
			  पूर्णांक अगरindex)
अणु
	काष्ठा in6_addr prefix_buf;
	पूर्णांक ret;

	ADDRLABEL(KERN_DEBUG "%s(prefix=%pI6, prefixlen=%d, ifindex=%d)\n",
		  __func__, prefix, prefixlen, अगरindex);

	ipv6_addr_prefix(&prefix_buf, prefix, prefixlen);
	spin_lock(&net->ipv6.ip6addrlbl_table.lock);
	ret = __ip6addrlbl_del(net, &prefix_buf, prefixlen, अगरindex);
	spin_unlock(&net->ipv6.ip6addrlbl_table.lock);
	वापस ret;
पूर्ण

/* add शेष label */
अटल पूर्णांक __net_init ip6addrlbl_net_init(काष्ठा net *net)
अणु
	काष्ठा ip6addrlbl_entry *p = शून्य;
	काष्ठा hlist_node *n;
	पूर्णांक err;
	पूर्णांक i;

	ADDRLABEL(KERN_DEBUG "%s\n", __func__);

	spin_lock_init(&net->ipv6.ip6addrlbl_table.lock);
	INIT_HLIST_HEAD(&net->ipv6.ip6addrlbl_table.head);

	क्रम (i = 0; i < ARRAY_SIZE(ip6addrlbl_init_table); i++) अणु
		err = ip6addrlbl_add(net,
				     ip6addrlbl_init_table[i].prefix,
				     ip6addrlbl_init_table[i].prefixlen,
				     0,
				     ip6addrlbl_init_table[i].label, 0);
		अगर (err)
			जाओ err_ip6addrlbl_add;
	पूर्ण
	वापस 0;

err_ip6addrlbl_add:
	hlist_क्रम_each_entry_safe(p, n, &net->ipv6.ip6addrlbl_table.head, list) अणु
		hlist_del_rcu(&p->list);
		kमुक्त_rcu(p, rcu);
	पूर्ण
	वापस err;
पूर्ण

अटल व्योम __net_निकास ip6addrlbl_net_निकास(काष्ठा net *net)
अणु
	काष्ठा ip6addrlbl_entry *p = शून्य;
	काष्ठा hlist_node *n;

	/* Remove all labels beदीर्घing to the निकासing net */
	spin_lock(&net->ipv6.ip6addrlbl_table.lock);
	hlist_क्रम_each_entry_safe(p, n, &net->ipv6.ip6addrlbl_table.head, list) अणु
		hlist_del_rcu(&p->list);
		kमुक्त_rcu(p, rcu);
	पूर्ण
	spin_unlock(&net->ipv6.ip6addrlbl_table.lock);
पूर्ण

अटल काष्ठा pernet_operations ipv6_addr_label_ops = अणु
	.init = ip6addrlbl_net_init,
	.निकास = ip6addrlbl_net_निकास,
पूर्ण;

पूर्णांक __init ipv6_addr_label_init(व्योम)
अणु
	वापस रेजिस्टर_pernet_subsys(&ipv6_addr_label_ops);
पूर्ण

व्योम ipv6_addr_label_cleanup(व्योम)
अणु
	unरेजिस्टर_pernet_subsys(&ipv6_addr_label_ops);
पूर्ण

अटल स्थिर काष्ठा nla_policy अगरal_policy[IFAL_MAX+1] = अणु
	[IFAL_ADDRESS]		= अणु .len = माप(काष्ठा in6_addr), पूर्ण,
	[IFAL_LABEL]		= अणु .len = माप(u32), पूर्ण,
पूर्ण;

अटल bool addrlbl_अगरindex_exists(काष्ठा net *net, पूर्णांक अगरindex)
अणु

	काष्ठा net_device *dev;

	rcu_पढ़ो_lock();
	dev = dev_get_by_index_rcu(net, अगरindex);
	rcu_पढ़ो_unlock();

	वापस dev != शून्य;
पूर्ण

अटल पूर्णांक ip6addrlbl_newdel(काष्ठा sk_buff *skb, काष्ठा nlmsghdr *nlh,
			     काष्ठा netlink_ext_ack *extack)
अणु
	काष्ठा net *net = sock_net(skb->sk);
	काष्ठा अगरaddrlblmsg *अगरal;
	काष्ठा nlattr *tb[IFAL_MAX+1];
	काष्ठा in6_addr *pfx;
	u32 label;
	पूर्णांक err = 0;

	err = nlmsg_parse_deprecated(nlh, माप(*अगरal), tb, IFAL_MAX,
				     अगरal_policy, extack);
	अगर (err < 0)
		वापस err;

	अगरal = nlmsg_data(nlh);

	अगर (अगरal->अगरal_family != AF_INET6 ||
	    अगरal->अगरal_prefixlen > 128)
		वापस -EINVAL;

	अगर (!tb[IFAL_ADDRESS])
		वापस -EINVAL;
	pfx = nla_data(tb[IFAL_ADDRESS]);

	अगर (!tb[IFAL_LABEL])
		वापस -EINVAL;
	label = nla_get_u32(tb[IFAL_LABEL]);
	अगर (label == IPV6_ADDR_LABEL_DEFAULT)
		वापस -EINVAL;

	चयन (nlh->nlmsg_type) अणु
	हाल RTM_NEWADDRLABEL:
		अगर (अगरal->अगरal_index &&
		    !addrlbl_अगरindex_exists(net, अगरal->अगरal_index))
			वापस -EINVAL;

		err = ip6addrlbl_add(net, pfx, अगरal->अगरal_prefixlen,
				     अगरal->अगरal_index, label,
				     nlh->nlmsg_flags & NLM_F_REPLACE);
		अवरोध;
	हाल RTM_DELADDRLABEL:
		err = ip6addrlbl_del(net, pfx, अगरal->अगरal_prefixlen,
				     अगरal->अगरal_index);
		अवरोध;
	शेष:
		err = -EOPNOTSUPP;
	पूर्ण
	वापस err;
पूर्ण

अटल व्योम ip6addrlbl_puपंचांगsg(काष्ठा nlmsghdr *nlh,
			      पूर्णांक prefixlen, पूर्णांक अगरindex, u32 lseq)
अणु
	काष्ठा अगरaddrlblmsg *अगरal = nlmsg_data(nlh);
	अगरal->अगरal_family = AF_INET6;
	अगरal->अगरal_prefixlen = prefixlen;
	अगरal->अगरal_flags = 0;
	अगरal->अगरal_index = अगरindex;
	अगरal->अगरal_seq = lseq;
पूर्ण;

अटल पूर्णांक ip6addrlbl_fill(काष्ठा sk_buff *skb,
			   काष्ठा ip6addrlbl_entry *p,
			   u32 lseq,
			   u32 portid, u32 seq, पूर्णांक event,
			   अचिन्हित पूर्णांक flags)
अणु
	काष्ठा nlmsghdr *nlh = nlmsg_put(skb, portid, seq, event,
					 माप(काष्ठा अगरaddrlblmsg), flags);
	अगर (!nlh)
		वापस -EMSGSIZE;

	ip6addrlbl_puपंचांगsg(nlh, p->prefixlen, p->अगरindex, lseq);

	अगर (nla_put_in6_addr(skb, IFAL_ADDRESS, &p->prefix) < 0 ||
	    nla_put_u32(skb, IFAL_LABEL, p->label) < 0) अणु
		nlmsg_cancel(skb, nlh);
		वापस -EMSGSIZE;
	पूर्ण

	nlmsg_end(skb, nlh);
	वापस 0;
पूर्ण

अटल पूर्णांक ip6addrlbl_valid_dump_req(स्थिर काष्ठा nlmsghdr *nlh,
				     काष्ठा netlink_ext_ack *extack)
अणु
	काष्ठा अगरaddrlblmsg *अगरal;

	अगर (nlh->nlmsg_len < nlmsg_msg_size(माप(*अगरal))) अणु
		NL_SET_ERR_MSG_MOD(extack, "Invalid header for address label dump request");
		वापस -EINVAL;
	पूर्ण

	अगरal = nlmsg_data(nlh);
	अगर (अगरal->__अगरal_reserved || अगरal->अगरal_prefixlen ||
	    अगरal->अगरal_flags || अगरal->अगरal_index || अगरal->अगरal_seq) अणु
		NL_SET_ERR_MSG_MOD(extack, "Invalid values in header for address label dump request");
		वापस -EINVAL;
	पूर्ण

	अगर (nlmsg_attrlen(nlh, माप(*अगरal))) अणु
		NL_SET_ERR_MSG_MOD(extack, "Invalid data after header for address label dump request");
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक ip6addrlbl_dump(काष्ठा sk_buff *skb, काष्ठा netlink_callback *cb)
अणु
	स्थिर काष्ठा nlmsghdr *nlh = cb->nlh;
	काष्ठा net *net = sock_net(skb->sk);
	काष्ठा ip6addrlbl_entry *p;
	पूर्णांक idx = 0, s_idx = cb->args[0];
	पूर्णांक err;

	अगर (cb->strict_check) अणु
		err = ip6addrlbl_valid_dump_req(nlh, cb->extack);
		अगर (err < 0)
			वापस err;
	पूर्ण

	rcu_पढ़ो_lock();
	hlist_क्रम_each_entry_rcu(p, &net->ipv6.ip6addrlbl_table.head, list) अणु
		अगर (idx >= s_idx) अणु
			err = ip6addrlbl_fill(skb, p,
					      net->ipv6.ip6addrlbl_table.seq,
					      NETLINK_CB(cb->skb).portid,
					      nlh->nlmsg_seq,
					      RTM_NEWADDRLABEL,
					      NLM_F_MULTI);
			अगर (err < 0)
				अवरोध;
		पूर्ण
		idx++;
	पूर्ण
	rcu_पढ़ो_unlock();
	cb->args[0] = idx;
	वापस skb->len;
पूर्ण

अटल अंतरभूत पूर्णांक ip6addrlbl_msgsize(व्योम)
अणु
	वापस NLMSG_ALIGN(माप(काष्ठा अगरaddrlblmsg))
		+ nla_total_size(16)	/* IFAL_ADDRESS */
		+ nla_total_size(4);	/* IFAL_LABEL */
पूर्ण

अटल पूर्णांक ip6addrlbl_valid_get_req(काष्ठा sk_buff *skb,
				    स्थिर काष्ठा nlmsghdr *nlh,
				    काष्ठा nlattr **tb,
				    काष्ठा netlink_ext_ack *extack)
अणु
	काष्ठा अगरaddrlblmsg *अगरal;
	पूर्णांक i, err;

	अगर (nlh->nlmsg_len < nlmsg_msg_size(माप(*अगरal))) अणु
		NL_SET_ERR_MSG_MOD(extack, "Invalid header for addrlabel get request");
		वापस -EINVAL;
	पूर्ण

	अगर (!netlink_strict_get_check(skb))
		वापस nlmsg_parse_deprecated(nlh, माप(*अगरal), tb,
					      IFAL_MAX, अगरal_policy, extack);

	अगरal = nlmsg_data(nlh);
	अगर (अगरal->__अगरal_reserved || अगरal->अगरal_flags || अगरal->अगरal_seq) अणु
		NL_SET_ERR_MSG_MOD(extack, "Invalid values in header for addrlabel get request");
		वापस -EINVAL;
	पूर्ण

	err = nlmsg_parse_deprecated_strict(nlh, माप(*अगरal), tb, IFAL_MAX,
					    अगरal_policy, extack);
	अगर (err)
		वापस err;

	क्रम (i = 0; i <= IFAL_MAX; i++) अणु
		अगर (!tb[i])
			जारी;

		चयन (i) अणु
		हाल IFAL_ADDRESS:
			अवरोध;
		शेष:
			NL_SET_ERR_MSG_MOD(extack, "Unsupported attribute in addrlabel get request");
			वापस -EINVAL;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक ip6addrlbl_get(काष्ठा sk_buff *in_skb, काष्ठा nlmsghdr *nlh,
			  काष्ठा netlink_ext_ack *extack)
अणु
	काष्ठा net *net = sock_net(in_skb->sk);
	काष्ठा अगरaddrlblmsg *अगरal;
	काष्ठा nlattr *tb[IFAL_MAX+1];
	काष्ठा in6_addr *addr;
	u32 lseq;
	पूर्णांक err = 0;
	काष्ठा ip6addrlbl_entry *p;
	काष्ठा sk_buff *skb;

	err = ip6addrlbl_valid_get_req(in_skb, nlh, tb, extack);
	अगर (err < 0)
		वापस err;

	अगरal = nlmsg_data(nlh);

	अगर (अगरal->अगरal_family != AF_INET6 ||
	    अगरal->अगरal_prefixlen != 128)
		वापस -EINVAL;

	अगर (अगरal->अगरal_index &&
	    !addrlbl_अगरindex_exists(net, अगरal->अगरal_index))
		वापस -EINVAL;

	अगर (!tb[IFAL_ADDRESS])
		वापस -EINVAL;
	addr = nla_data(tb[IFAL_ADDRESS]);

	skb = nlmsg_new(ip6addrlbl_msgsize(), GFP_KERNEL);
	अगर (!skb)
		वापस -ENOBUFS;

	err = -ESRCH;

	rcu_पढ़ो_lock();
	p = __ipv6_addr_label(net, addr, ipv6_addr_type(addr), अगरal->अगरal_index);
	lseq = net->ipv6.ip6addrlbl_table.seq;
	अगर (p)
		err = ip6addrlbl_fill(skb, p, lseq,
				      NETLINK_CB(in_skb).portid,
				      nlh->nlmsg_seq,
				      RTM_NEWADDRLABEL, 0);
	rcu_पढ़ो_unlock();

	अगर (err < 0) अणु
		WARN_ON(err == -EMSGSIZE);
		kमुक्त_skb(skb);
	पूर्ण अन्यथा अणु
		err = rtnl_unicast(skb, net, NETLINK_CB(in_skb).portid);
	पूर्ण
	वापस err;
पूर्ण

पूर्णांक __init ipv6_addr_label_rtnl_रेजिस्टर(व्योम)
अणु
	पूर्णांक ret;

	ret = rtnl_रेजिस्टर_module(THIS_MODULE, PF_INET6, RTM_NEWADDRLABEL,
				   ip6addrlbl_newdel,
				   शून्य, RTNL_FLAG_DOIT_UNLOCKED);
	अगर (ret < 0)
		वापस ret;
	ret = rtnl_रेजिस्टर_module(THIS_MODULE, PF_INET6, RTM_DELADDRLABEL,
				   ip6addrlbl_newdel,
				   शून्य, RTNL_FLAG_DOIT_UNLOCKED);
	अगर (ret < 0)
		वापस ret;
	ret = rtnl_रेजिस्टर_module(THIS_MODULE, PF_INET6, RTM_GETADDRLABEL,
				   ip6addrlbl_get,
				   ip6addrlbl_dump, RTNL_FLAG_DOIT_UNLOCKED);
	वापस ret;
पूर्ण
