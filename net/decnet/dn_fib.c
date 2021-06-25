<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * DECnet       An implementation of the DECnet protocol suite क्रम the LINUX
 *              operating प्रणाली.  DECnet is implemented using the  BSD Socket
 *              पूर्णांकerface as the means of communication with the user level.
 *
 *              DECnet Routing Forwarding Inक्रमmation Base (Glue/Info List)
 *
 * Author:      Steve Whitehouse <SteveW@ACM.org>
 *
 *
 * Changes:
 *              Alexey Kuznetsov : SMP locking changes
 *              Steve Whitehouse : Rewrote it... Well to be more correct, I
 *                                 copied most of it from the ipv4 fib code.
 *              Steve Whitehouse : Updated it in style and fixed a few bugs
 *                                 which were fixed in the ipv4 code since
 *                                 this code was copied from it.
 *
 */
#समावेश <linux/माला.स>
#समावेश <linux/net.h>
#समावेश <linux/socket.h>
#समावेश <linux/slab.h>
#समावेश <linux/sockios.h>
#समावेश <linux/init.h>
#समावेश <linux/skbuff.h>
#समावेश <linux/netlink.h>
#समावेश <linux/rtnetlink.h>
#समावेश <linux/proc_fs.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/समयr.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/atomic.h>
#समावेश <linux/uaccess.h>
#समावेश <net/neighbour.h>
#समावेश <net/dst.h>
#समावेश <net/flow.h>
#समावेश <net/fib_rules.h>
#समावेश <net/dn.h>
#समावेश <net/dn_route.h>
#समावेश <net/dn_fib.h>
#समावेश <net/dn_neigh.h>
#समावेश <net/dn_dev.h>
#समावेश <net/rtnh.h>

#घोषणा RT_MIN_TABLE 1

#घोषणा क्रम_fib_info() अणु काष्ठा dn_fib_info *fi;\
	क्रम(fi = dn_fib_info_list; fi; fi = fi->fib_next)
#घोषणा endक्रम_fib_info() पूर्ण

#घोषणा क्रम_nexthops(fi) अणु पूर्णांक nhsel; स्थिर काष्ठा dn_fib_nh *nh;\
	क्रम(nhsel = 0, nh = (fi)->fib_nh; nhsel < (fi)->fib_nhs; nh++, nhsel++)

#घोषणा change_nexthops(fi) अणु पूर्णांक nhsel; काष्ठा dn_fib_nh *nh;\
	क्रम(nhsel = 0, nh = (काष्ठा dn_fib_nh *)((fi)->fib_nh); nhsel < (fi)->fib_nhs; nh++, nhsel++)

#घोषणा endक्रम_nexthops(fi) पूर्ण

अटल DEFINE_SPINLOCK(dn_fib_multipath_lock);
अटल काष्ठा dn_fib_info *dn_fib_info_list;
अटल DEFINE_SPINLOCK(dn_fib_info_lock);

अटल काष्ठा
अणु
	पूर्णांक error;
	u8 scope;
पूर्ण dn_fib_props[RTN_MAX+1] = अणु
	[RTN_UNSPEC] =      अणु .error = 0,       .scope = RT_SCOPE_NOWHERE पूर्ण,
	[RTN_UNICAST] =     अणु .error = 0,       .scope = RT_SCOPE_UNIVERSE पूर्ण,
	[RTN_LOCAL] =       अणु .error = 0,       .scope = RT_SCOPE_HOST पूर्ण,
	[RTN_BROADCAST] =   अणु .error = -EINVAL, .scope = RT_SCOPE_NOWHERE पूर्ण,
	[RTN_ANYCAST] =     अणु .error = -EINVAL, .scope = RT_SCOPE_NOWHERE पूर्ण,
	[RTN_MULTICAST] =   अणु .error = -EINVAL, .scope = RT_SCOPE_NOWHERE पूर्ण,
	[RTN_BLACKHOLE] =   अणु .error = -EINVAL, .scope = RT_SCOPE_UNIVERSE पूर्ण,
	[RTN_UNREACHABLE] = अणु .error = -EHOSTUNREACH, .scope = RT_SCOPE_UNIVERSE पूर्ण,
	[RTN_PROHIBIT] =    अणु .error = -EACCES, .scope = RT_SCOPE_UNIVERSE पूर्ण,
	[RTN_THROW] =       अणु .error = -EAGAIN, .scope = RT_SCOPE_UNIVERSE पूर्ण,
	[RTN_NAT] =         अणु .error = 0,       .scope = RT_SCOPE_NOWHERE पूर्ण,
	[RTN_XRESOLVE] =    अणु .error = -EINVAL, .scope = RT_SCOPE_NOWHERE पूर्ण,
पूर्ण;

अटल पूर्णांक dn_fib_sync_करोwn(__le16 local, काष्ठा net_device *dev, पूर्णांक क्रमce);
अटल पूर्णांक dn_fib_sync_up(काष्ठा net_device *dev);

व्योम dn_fib_मुक्त_info(काष्ठा dn_fib_info *fi)
अणु
	अगर (fi->fib_dead == 0) अणु
		prपूर्णांकk(KERN_DEBUG "DECnet: BUG! Attempt to free alive dn_fib_info\n");
		वापस;
	पूर्ण

	change_nexthops(fi) अणु
		अगर (nh->nh_dev)
			dev_put(nh->nh_dev);
		nh->nh_dev = शून्य;
	पूर्ण endक्रम_nexthops(fi);
	kमुक्त(fi);
पूर्ण

व्योम dn_fib_release_info(काष्ठा dn_fib_info *fi)
अणु
	spin_lock(&dn_fib_info_lock);
	अगर (fi && --fi->fib_treeref == 0) अणु
		अगर (fi->fib_next)
			fi->fib_next->fib_prev = fi->fib_prev;
		अगर (fi->fib_prev)
			fi->fib_prev->fib_next = fi->fib_next;
		अगर (fi == dn_fib_info_list)
			dn_fib_info_list = fi->fib_next;
		fi->fib_dead = 1;
		dn_fib_info_put(fi);
	पूर्ण
	spin_unlock(&dn_fib_info_lock);
पूर्ण

अटल अंतरभूत पूर्णांक dn_fib_nh_comp(स्थिर काष्ठा dn_fib_info *fi, स्थिर काष्ठा dn_fib_info *ofi)
अणु
	स्थिर काष्ठा dn_fib_nh *onh = ofi->fib_nh;

	क्रम_nexthops(fi) अणु
		अगर (nh->nh_oअगर != onh->nh_oअगर ||
			nh->nh_gw != onh->nh_gw ||
			nh->nh_scope != onh->nh_scope ||
			nh->nh_weight != onh->nh_weight ||
			((nh->nh_flags^onh->nh_flags)&~RTNH_F_DEAD))
				वापस -1;
		onh++;
	पूर्ण endक्रम_nexthops(fi);
	वापस 0;
पूर्ण

अटल अंतरभूत काष्ठा dn_fib_info *dn_fib_find_info(स्थिर काष्ठा dn_fib_info *nfi)
अणु
	क्रम_fib_info() अणु
		अगर (fi->fib_nhs != nfi->fib_nhs)
			जारी;
		अगर (nfi->fib_protocol == fi->fib_protocol &&
			nfi->fib_prefsrc == fi->fib_prefsrc &&
			nfi->fib_priority == fi->fib_priority &&
			स_भेद(nfi->fib_metrics, fi->fib_metrics, माप(fi->fib_metrics)) == 0 &&
			((nfi->fib_flags^fi->fib_flags)&~RTNH_F_DEAD) == 0 &&
			(nfi->fib_nhs == 0 || dn_fib_nh_comp(fi, nfi) == 0))
				वापस fi;
	पूर्ण endक्रम_fib_info();
	वापस शून्य;
पूर्ण

अटल पूर्णांक dn_fib_count_nhs(स्थिर काष्ठा nlattr *attr)
अणु
	काष्ठा rtnexthop *nhp = nla_data(attr);
	पूर्णांक nhs = 0, nhlen = nla_len(attr);

	जबतक (rtnh_ok(nhp, nhlen)) अणु
		nhs++;
		nhp = rtnh_next(nhp, &nhlen);
	पूर्ण

	/* leftover implies invalid nexthop configuration, discard it */
	वापस nhlen > 0 ? 0 : nhs;
पूर्ण

अटल पूर्णांक dn_fib_get_nhs(काष्ठा dn_fib_info *fi, स्थिर काष्ठा nlattr *attr,
			  स्थिर काष्ठा rपंचांगsg *r)
अणु
	काष्ठा rtnexthop *nhp = nla_data(attr);
	पूर्णांक nhlen = nla_len(attr);

	change_nexthops(fi) अणु
		पूर्णांक attrlen;

		अगर (!rtnh_ok(nhp, nhlen))
			वापस -EINVAL;

		nh->nh_flags  = (r->rपंचांग_flags&~0xFF) | nhp->rtnh_flags;
		nh->nh_oअगर    = nhp->rtnh_अगरindex;
		nh->nh_weight = nhp->rtnh_hops + 1;

		attrlen = rtnh_attrlen(nhp);
		अगर (attrlen > 0) अणु
			काष्ठा nlattr *gw_attr;

			gw_attr = nla_find((काष्ठा nlattr *) (nhp + 1), attrlen, RTA_GATEWAY);
			nh->nh_gw = gw_attr ? nla_get_le16(gw_attr) : 0;
		पूर्ण

		nhp = rtnh_next(nhp, &nhlen);
	पूर्ण endक्रम_nexthops(fi);

	वापस 0;
पूर्ण


अटल पूर्णांक dn_fib_check_nh(स्थिर काष्ठा rपंचांगsg *r, काष्ठा dn_fib_info *fi, काष्ठा dn_fib_nh *nh)
अणु
	पूर्णांक err;

	अगर (nh->nh_gw) अणु
		काष्ठा flowidn fld;
		काष्ठा dn_fib_res res;

		अगर (nh->nh_flags&RTNH_F_ONLINK) अणु
			काष्ठा net_device *dev;

			अगर (r->rपंचांग_scope >= RT_SCOPE_LINK)
				वापस -EINVAL;
			अगर (dnet_addr_type(nh->nh_gw) != RTN_UNICAST)
				वापस -EINVAL;
			अगर ((dev = __dev_get_by_index(&init_net, nh->nh_oअगर)) == शून्य)
				वापस -ENODEV;
			अगर (!(dev->flags&IFF_UP))
				वापस -ENETDOWN;
			nh->nh_dev = dev;
			dev_hold(dev);
			nh->nh_scope = RT_SCOPE_LINK;
			वापस 0;
		पूर्ण

		स_रखो(&fld, 0, माप(fld));
		fld.daddr = nh->nh_gw;
		fld.flowidn_oअगर = nh->nh_oअगर;
		fld.flowidn_scope = r->rपंचांग_scope + 1;

		अगर (fld.flowidn_scope < RT_SCOPE_LINK)
			fld.flowidn_scope = RT_SCOPE_LINK;

		अगर ((err = dn_fib_lookup(&fld, &res)) != 0)
			वापस err;

		err = -EINVAL;
		अगर (res.type != RTN_UNICAST && res.type != RTN_LOCAL)
			जाओ out;
		nh->nh_scope = res.scope;
		nh->nh_oअगर = DN_FIB_RES_OIF(res);
		nh->nh_dev = DN_FIB_RES_DEV(res);
		अगर (nh->nh_dev == शून्य)
			जाओ out;
		dev_hold(nh->nh_dev);
		err = -ENETDOWN;
		अगर (!(nh->nh_dev->flags & IFF_UP))
			जाओ out;
		err = 0;
out:
		dn_fib_res_put(&res);
		वापस err;
	पूर्ण अन्यथा अणु
		काष्ठा net_device *dev;

		अगर (nh->nh_flags&(RTNH_F_PERVASIVE|RTNH_F_ONLINK))
			वापस -EINVAL;

		dev = __dev_get_by_index(&init_net, nh->nh_oअगर);
		अगर (dev == शून्य || dev->dn_ptr == शून्य)
			वापस -ENODEV;
		अगर (!(dev->flags&IFF_UP))
			वापस -ENETDOWN;
		nh->nh_dev = dev;
		dev_hold(nh->nh_dev);
		nh->nh_scope = RT_SCOPE_HOST;
	पूर्ण

	वापस 0;
पूर्ण


काष्ठा dn_fib_info *dn_fib_create_info(स्थिर काष्ठा rपंचांगsg *r, काष्ठा nlattr *attrs[],
				       स्थिर काष्ठा nlmsghdr *nlh, पूर्णांक *errp)
अणु
	पूर्णांक err;
	काष्ठा dn_fib_info *fi = शून्य;
	काष्ठा dn_fib_info *ofi;
	पूर्णांक nhs = 1;

	अगर (r->rपंचांग_type > RTN_MAX)
		जाओ err_inval;

	अगर (dn_fib_props[r->rपंचांग_type].scope > r->rपंचांग_scope)
		जाओ err_inval;

	अगर (attrs[RTA_MULTIPATH] &&
	    (nhs = dn_fib_count_nhs(attrs[RTA_MULTIPATH])) == 0)
		जाओ err_inval;

	fi = kzalloc(काष्ठा_size(fi, fib_nh, nhs), GFP_KERNEL);
	err = -ENOBUFS;
	अगर (fi == शून्य)
		जाओ failure;

	fi->fib_protocol = r->rपंचांग_protocol;
	fi->fib_nhs = nhs;
	fi->fib_flags = r->rपंचांग_flags;

	अगर (attrs[RTA_PRIORITY])
		fi->fib_priority = nla_get_u32(attrs[RTA_PRIORITY]);

	अगर (attrs[RTA_METRICS]) अणु
		काष्ठा nlattr *attr;
		पूर्णांक rem;

		nla_क्रम_each_nested(attr, attrs[RTA_METRICS], rem) अणु
			पूर्णांक type = nla_type(attr);

			अगर (type) अणु
				अगर (type > RTAX_MAX || type == RTAX_CC_ALGO ||
				    nla_len(attr) < 4)
					जाओ err_inval;

				fi->fib_metrics[type-1] = nla_get_u32(attr);
			पूर्ण
		पूर्ण
	पूर्ण

	अगर (attrs[RTA_PREFSRC])
		fi->fib_prefsrc = nla_get_le16(attrs[RTA_PREFSRC]);

	अगर (attrs[RTA_MULTIPATH]) अणु
		अगर ((err = dn_fib_get_nhs(fi, attrs[RTA_MULTIPATH], r)) != 0)
			जाओ failure;

		अगर (attrs[RTA_OIF] &&
		    fi->fib_nh->nh_oअगर != nla_get_u32(attrs[RTA_OIF]))
			जाओ err_inval;

		अगर (attrs[RTA_GATEWAY] &&
		    fi->fib_nh->nh_gw != nla_get_le16(attrs[RTA_GATEWAY]))
			जाओ err_inval;
	पूर्ण अन्यथा अणु
		काष्ठा dn_fib_nh *nh = fi->fib_nh;

		अगर (attrs[RTA_OIF])
			nh->nh_oअगर = nla_get_u32(attrs[RTA_OIF]);

		अगर (attrs[RTA_GATEWAY])
			nh->nh_gw = nla_get_le16(attrs[RTA_GATEWAY]);

		nh->nh_flags = r->rपंचांग_flags;
		nh->nh_weight = 1;
	पूर्ण

	अगर (r->rपंचांग_type == RTN_NAT) अणु
		अगर (!attrs[RTA_GATEWAY] || nhs != 1 || attrs[RTA_OIF])
			जाओ err_inval;

		fi->fib_nh->nh_gw = nla_get_le16(attrs[RTA_GATEWAY]);
		जाओ link_it;
	पूर्ण

	अगर (dn_fib_props[r->rपंचांग_type].error) अणु
		अगर (attrs[RTA_GATEWAY] || attrs[RTA_OIF] || attrs[RTA_MULTIPATH])
			जाओ err_inval;

		जाओ link_it;
	पूर्ण

	अगर (r->rपंचांग_scope > RT_SCOPE_HOST)
		जाओ err_inval;

	अगर (r->rपंचांग_scope == RT_SCOPE_HOST) अणु
		काष्ठा dn_fib_nh *nh = fi->fib_nh;

		/* Local address is added */
		अगर (nhs != 1 || nh->nh_gw)
			जाओ err_inval;
		nh->nh_scope = RT_SCOPE_NOWHERE;
		nh->nh_dev = dev_get_by_index(&init_net, fi->fib_nh->nh_oअगर);
		err = -ENODEV;
		अगर (nh->nh_dev == शून्य)
			जाओ failure;
	पूर्ण अन्यथा अणु
		change_nexthops(fi) अणु
			अगर ((err = dn_fib_check_nh(r, fi, nh)) != 0)
				जाओ failure;
		पूर्ण endक्रम_nexthops(fi)
	पूर्ण

	अगर (fi->fib_prefsrc) अणु
		अगर (r->rपंचांग_type != RTN_LOCAL || !attrs[RTA_DST] ||
		    fi->fib_prefsrc != nla_get_le16(attrs[RTA_DST]))
			अगर (dnet_addr_type(fi->fib_prefsrc) != RTN_LOCAL)
				जाओ err_inval;
	पूर्ण

link_it:
	अगर ((ofi = dn_fib_find_info(fi)) != शून्य) अणु
		fi->fib_dead = 1;
		dn_fib_मुक्त_info(fi);
		ofi->fib_treeref++;
		वापस ofi;
	पूर्ण

	fi->fib_treeref++;
	refcount_set(&fi->fib_clntref, 1);
	spin_lock(&dn_fib_info_lock);
	fi->fib_next = dn_fib_info_list;
	fi->fib_prev = शून्य;
	अगर (dn_fib_info_list)
		dn_fib_info_list->fib_prev = fi;
	dn_fib_info_list = fi;
	spin_unlock(&dn_fib_info_lock);
	वापस fi;

err_inval:
	err = -EINVAL;

failure:
	*errp = err;
	अगर (fi) अणु
		fi->fib_dead = 1;
		dn_fib_मुक्त_info(fi);
	पूर्ण

	वापस शून्य;
पूर्ण

पूर्णांक dn_fib_semantic_match(पूर्णांक type, काष्ठा dn_fib_info *fi, स्थिर काष्ठा flowidn *fld, काष्ठा dn_fib_res *res)
अणु
	पूर्णांक err = dn_fib_props[type].error;

	अगर (err == 0) अणु
		अगर (fi->fib_flags & RTNH_F_DEAD)
			वापस 1;

		res->fi = fi;

		चयन (type) अणु
		हाल RTN_NAT:
			DN_FIB_RES_RESET(*res);
			refcount_inc(&fi->fib_clntref);
			वापस 0;
		हाल RTN_UNICAST:
		हाल RTN_LOCAL:
			क्रम_nexthops(fi) अणु
				अगर (nh->nh_flags & RTNH_F_DEAD)
					जारी;
				अगर (!fld->flowidn_oअगर ||
				    fld->flowidn_oअगर == nh->nh_oअगर)
					अवरोध;
			पूर्ण
			अगर (nhsel < fi->fib_nhs) अणु
				res->nh_sel = nhsel;
				refcount_inc(&fi->fib_clntref);
				वापस 0;
			पूर्ण
			endक्रम_nexthops(fi);
			res->fi = शून्य;
			वापस 1;
		शेष:
			net_err_ratelimited("DECnet: impossible routing event : dn_fib_semantic_match type=%d\n",
					    type);
			res->fi = शून्य;
			वापस -EINVAL;
		पूर्ण
	पूर्ण
	वापस err;
पूर्ण

व्योम dn_fib_select_multipath(स्थिर काष्ठा flowidn *fld, काष्ठा dn_fib_res *res)
अणु
	काष्ठा dn_fib_info *fi = res->fi;
	पूर्णांक w;

	spin_lock_bh(&dn_fib_multipath_lock);
	अगर (fi->fib_घातer <= 0) अणु
		पूर्णांक घातer = 0;
		change_nexthops(fi) अणु
			अगर (!(nh->nh_flags&RTNH_F_DEAD)) अणु
				घातer += nh->nh_weight;
				nh->nh_घातer = nh->nh_weight;
			पूर्ण
		पूर्ण endक्रम_nexthops(fi);
		fi->fib_घातer = घातer;
		अगर (घातer < 0) अणु
			spin_unlock_bh(&dn_fib_multipath_lock);
			res->nh_sel = 0;
			वापस;
		पूर्ण
	पूर्ण

	w = jअगरfies % fi->fib_घातer;

	change_nexthops(fi) अणु
		अगर (!(nh->nh_flags&RTNH_F_DEAD) && nh->nh_घातer) अणु
			अगर ((w -= nh->nh_घातer) <= 0) अणु
				nh->nh_घातer--;
				fi->fib_घातer--;
				res->nh_sel = nhsel;
				spin_unlock_bh(&dn_fib_multipath_lock);
				वापस;
			पूर्ण
		पूर्ण
	पूर्ण endक्रम_nexthops(fi);
	res->nh_sel = 0;
	spin_unlock_bh(&dn_fib_multipath_lock);
पूर्ण

अटल अंतरभूत u32 rपंचांग_get_table(काष्ठा nlattr *attrs[], u8 table)
अणु
	अगर (attrs[RTA_TABLE])
		table = nla_get_u32(attrs[RTA_TABLE]);

	वापस table;
पूर्ण

अटल पूर्णांक dn_fib_rपंचांग_delroute(काष्ठा sk_buff *skb, काष्ठा nlmsghdr *nlh,
			       काष्ठा netlink_ext_ack *extack)
अणु
	काष्ठा net *net = sock_net(skb->sk);
	काष्ठा dn_fib_table *tb;
	काष्ठा rपंचांगsg *r = nlmsg_data(nlh);
	काष्ठा nlattr *attrs[RTA_MAX+1];
	पूर्णांक err;

	अगर (!netlink_capable(skb, CAP_NET_ADMIN))
		वापस -EPERM;

	अगर (!net_eq(net, &init_net))
		वापस -EINVAL;

	err = nlmsg_parse_deprecated(nlh, माप(*r), attrs, RTA_MAX,
				     rपंचांग_dn_policy, extack);
	अगर (err < 0)
		वापस err;

	tb = dn_fib_get_table(rपंचांग_get_table(attrs, r->rपंचांग_table), 0);
	अगर (!tb)
		वापस -ESRCH;

	वापस tb->delete(tb, r, attrs, nlh, &NETLINK_CB(skb));
पूर्ण

अटल पूर्णांक dn_fib_rपंचांग_newroute(काष्ठा sk_buff *skb, काष्ठा nlmsghdr *nlh,
			       काष्ठा netlink_ext_ack *extack)
अणु
	काष्ठा net *net = sock_net(skb->sk);
	काष्ठा dn_fib_table *tb;
	काष्ठा rपंचांगsg *r = nlmsg_data(nlh);
	काष्ठा nlattr *attrs[RTA_MAX+1];
	पूर्णांक err;

	अगर (!netlink_capable(skb, CAP_NET_ADMIN))
		वापस -EPERM;

	अगर (!net_eq(net, &init_net))
		वापस -EINVAL;

	err = nlmsg_parse_deprecated(nlh, माप(*r), attrs, RTA_MAX,
				     rपंचांग_dn_policy, extack);
	अगर (err < 0)
		वापस err;

	tb = dn_fib_get_table(rपंचांग_get_table(attrs, r->rपंचांग_table), 1);
	अगर (!tb)
		वापस -ENOBUFS;

	वापस tb->insert(tb, r, attrs, nlh, &NETLINK_CB(skb));
पूर्ण

अटल व्योम fib_magic(पूर्णांक cmd, पूर्णांक type, __le16 dst, पूर्णांक dst_len, काष्ठा dn_अगरaddr *अगरa)
अणु
	काष्ठा dn_fib_table *tb;
	काष्ठा अणु
		काष्ठा nlmsghdr nlh;
		काष्ठा rपंचांगsg rपंचांग;
	पूर्ण req;
	काष्ठा अणु
		काष्ठा nlattr hdr;
		__le16 dst;
	पूर्ण dst_attr = अणु
		.dst = dst,
	पूर्ण;
	काष्ठा अणु
		काष्ठा nlattr hdr;
		__le16 prefsrc;
	पूर्ण prefsrc_attr = अणु
		.prefsrc = अगरa->अगरa_local,
	पूर्ण;
	काष्ठा अणु
		काष्ठा nlattr hdr;
		u32 oअगर;
	पूर्ण oअगर_attr = अणु
		.oअगर = अगरa->अगरa_dev->dev->अगरindex,
	पूर्ण;
	काष्ठा nlattr *attrs[RTA_MAX+1] = अणु
		[RTA_DST] = (काष्ठा nlattr *) &dst_attr,
		[RTA_PREFSRC] = (काष्ठा nlattr * ) &prefsrc_attr,
		[RTA_OIF] = (काष्ठा nlattr *) &oअगर_attr,
	पूर्ण;

	स_रखो(&req.rपंचांग, 0, माप(req.rपंचांग));

	अगर (type == RTN_UNICAST)
		tb = dn_fib_get_table(RT_MIN_TABLE, 1);
	अन्यथा
		tb = dn_fib_get_table(RT_TABLE_LOCAL, 1);

	अगर (tb == शून्य)
		वापस;

	req.nlh.nlmsg_len = माप(req);
	req.nlh.nlmsg_type = cmd;
	req.nlh.nlmsg_flags = NLM_F_REQUEST|NLM_F_CREATE|NLM_F_APPEND;
	req.nlh.nlmsg_pid = 0;
	req.nlh.nlmsg_seq = 0;

	req.rपंचांग.rपंचांग_dst_len = dst_len;
	req.rपंचांग.rपंचांग_table = tb->n;
	req.rपंचांग.rपंचांग_protocol = RTPROT_KERNEL;
	req.rपंचांग.rपंचांग_scope = (type != RTN_LOCAL ? RT_SCOPE_LINK : RT_SCOPE_HOST);
	req.rपंचांग.rपंचांग_type = type;

	अगर (cmd == RTM_NEWROUTE)
		tb->insert(tb, &req.rपंचांग, attrs, &req.nlh, शून्य);
	अन्यथा
		tb->delete(tb, &req.rपंचांग, attrs, &req.nlh, शून्य);
पूर्ण

अटल व्योम dn_fib_add_अगरaddr(काष्ठा dn_अगरaddr *अगरa)
अणु

	fib_magic(RTM_NEWROUTE, RTN_LOCAL, अगरa->अगरa_local, 16, अगरa);

#अगर 0
	अगर (!(dev->flags&IFF_UP))
		वापस;
	/* In the future, we will want to add शेष routes here */

#पूर्ण_अगर
पूर्ण

अटल व्योम dn_fib_del_अगरaddr(काष्ठा dn_अगरaddr *अगरa)
अणु
	पूर्णांक found_it = 0;
	काष्ठा net_device *dev;
	काष्ठा dn_dev *dn_db;
	काष्ठा dn_अगरaddr *अगरa2;

	ASSERT_RTNL();

	/* Scan device list */
	rcu_पढ़ो_lock();
	क्रम_each_netdev_rcu(&init_net, dev) अणु
		dn_db = rcu_dereference(dev->dn_ptr);
		अगर (dn_db == शून्य)
			जारी;
		क्रम (अगरa2 = rcu_dereference(dn_db->अगरa_list);
		     अगरa2 != शून्य;
		     अगरa2 = rcu_dereference(अगरa2->अगरa_next)) अणु
			अगर (अगरa2->अगरa_local == अगरa->अगरa_local) अणु
				found_it = 1;
				अवरोध;
			पूर्ण
		पूर्ण
	पूर्ण
	rcu_पढ़ो_unlock();

	अगर (found_it == 0) अणु
		fib_magic(RTM_DELROUTE, RTN_LOCAL, अगरa->अगरa_local, 16, अगरa);

		अगर (dnet_addr_type(अगरa->अगरa_local) != RTN_LOCAL) अणु
			अगर (dn_fib_sync_करोwn(अगरa->अगरa_local, शून्य, 0))
				dn_fib_flush();
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम dn_fib_disable_addr(काष्ठा net_device *dev, पूर्णांक क्रमce)
अणु
	अगर (dn_fib_sync_करोwn(0, dev, क्रमce))
		dn_fib_flush();
	dn_rt_cache_flush(0);
	neigh_अगरकरोwn(&dn_neigh_table, dev);
पूर्ण

अटल पूर्णांक dn_fib_dnaddr_event(काष्ठा notअगरier_block *this, अचिन्हित दीर्घ event, व्योम *ptr)
अणु
	काष्ठा dn_अगरaddr *अगरa = (काष्ठा dn_अगरaddr *)ptr;

	चयन (event) अणु
	हाल NETDEV_UP:
		dn_fib_add_अगरaddr(अगरa);
		dn_fib_sync_up(अगरa->अगरa_dev->dev);
		dn_rt_cache_flush(-1);
		अवरोध;
	हाल NETDEV_DOWN:
		dn_fib_del_अगरaddr(अगरa);
		अगर (अगरa->अगरa_dev && अगरa->अगरa_dev->अगरa_list == शून्य) अणु
			dn_fib_disable_addr(अगरa->अगरa_dev->dev, 1);
		पूर्ण अन्यथा अणु
			dn_rt_cache_flush(-1);
		पूर्ण
		अवरोध;
	पूर्ण
	वापस NOTIFY_DONE;
पूर्ण

अटल पूर्णांक dn_fib_sync_करोwn(__le16 local, काष्ठा net_device *dev, पूर्णांक क्रमce)
अणु
	पूर्णांक ret = 0;
	पूर्णांक scope = RT_SCOPE_NOWHERE;

	अगर (क्रमce)
		scope = -1;

	क्रम_fib_info() अणु
		/*
		 * This makes no sense क्रम DECnet.... we will almost
		 * certainly have more than one local address the same
		 * over all our पूर्णांकerfaces. It needs thinking about
		 * some more.
		 */
		अगर (local && fi->fib_prefsrc == local) अणु
			fi->fib_flags |= RTNH_F_DEAD;
			ret++;
		पूर्ण अन्यथा अगर (dev && fi->fib_nhs) अणु
			पूर्णांक dead = 0;

			change_nexthops(fi) अणु
				अगर (nh->nh_flags&RTNH_F_DEAD)
					dead++;
				अन्यथा अगर (nh->nh_dev == dev &&
						nh->nh_scope != scope) अणु
					spin_lock_bh(&dn_fib_multipath_lock);
					nh->nh_flags |= RTNH_F_DEAD;
					fi->fib_घातer -= nh->nh_घातer;
					nh->nh_घातer = 0;
					spin_unlock_bh(&dn_fib_multipath_lock);
					dead++;
				पूर्ण
			पूर्ण endक्रम_nexthops(fi)
			अगर (dead == fi->fib_nhs) अणु
				fi->fib_flags |= RTNH_F_DEAD;
				ret++;
			पूर्ण
		पूर्ण
	पूर्ण endक्रम_fib_info();
	वापस ret;
पूर्ण


अटल पूर्णांक dn_fib_sync_up(काष्ठा net_device *dev)
अणु
	पूर्णांक ret = 0;

	अगर (!(dev->flags&IFF_UP))
		वापस 0;

	क्रम_fib_info() अणु
		पूर्णांक alive = 0;

		change_nexthops(fi) अणु
			अगर (!(nh->nh_flags&RTNH_F_DEAD)) अणु
				alive++;
				जारी;
			पूर्ण
			अगर (nh->nh_dev == शून्य || !(nh->nh_dev->flags&IFF_UP))
				जारी;
			अगर (nh->nh_dev != dev || dev->dn_ptr == शून्य)
				जारी;
			alive++;
			spin_lock_bh(&dn_fib_multipath_lock);
			nh->nh_घातer = 0;
			nh->nh_flags &= ~RTNH_F_DEAD;
			spin_unlock_bh(&dn_fib_multipath_lock);
		पूर्ण endक्रम_nexthops(fi);

		अगर (alive > 0) अणु
			fi->fib_flags &= ~RTNH_F_DEAD;
			ret++;
		पूर्ण
	पूर्ण endक्रम_fib_info();
	वापस ret;
पूर्ण

अटल काष्ठा notअगरier_block dn_fib_dnaddr_notअगरier = अणु
	.notअगरier_call = dn_fib_dnaddr_event,
पूर्ण;

व्योम __निकास dn_fib_cleanup(व्योम)
अणु
	dn_fib_table_cleanup();
	dn_fib_rules_cleanup();

	unरेजिस्टर_dnaddr_notअगरier(&dn_fib_dnaddr_notअगरier);
पूर्ण


व्योम __init dn_fib_init(व्योम)
अणु
	dn_fib_table_init();
	dn_fib_rules_init();

	रेजिस्टर_dnaddr_notअगरier(&dn_fib_dnaddr_notअगरier);

	rtnl_रेजिस्टर_module(THIS_MODULE, PF_DECnet, RTM_NEWROUTE,
			     dn_fib_rपंचांग_newroute, शून्य, 0);
	rtnl_रेजिस्टर_module(THIS_MODULE, PF_DECnet, RTM_DELROUTE,
			     dn_fib_rपंचांग_delroute, शून्य, 0);
पूर्ण
