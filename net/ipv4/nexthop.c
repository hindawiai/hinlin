<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/* Generic nexthop implementation
 *
 * Copyright (c) 2017-19 Cumulus Networks
 * Copyright (c) 2017-19 David Ahern <dsa@cumulusnetworks.com>
 */

#समावेश <linux/nexthop.h>
#समावेश <linux/rtnetlink.h>
#समावेश <linux/slab.h>
#समावेश <net/arp.h>
#समावेश <net/ipv6_stubs.h>
#समावेश <net/lwtunnel.h>
#समावेश <net/ndisc.h>
#समावेश <net/nexthop.h>
#समावेश <net/route.h>
#समावेश <net/sock.h>

#घोषणा NH_RES_DEFAULT_IDLE_TIMER	(120 * HZ)
#घोषणा NH_RES_DEFAULT_UNBALANCED_TIMER	0	/* No क्रमced rebalancing. */

अटल व्योम हटाओ_nexthop(काष्ठा net *net, काष्ठा nexthop *nh,
			   काष्ठा nl_info *nlinfo);

#घोषणा NH_DEV_HASHBITS  8
#घोषणा NH_DEV_HASHSIZE (1U << NH_DEV_HASHBITS)

अटल स्थिर काष्ठा nla_policy rपंचांग_nh_policy_new[] = अणु
	[NHA_ID]		= अणु .type = NLA_U32 पूर्ण,
	[NHA_GROUP]		= अणु .type = NLA_BINARY पूर्ण,
	[NHA_GROUP_TYPE]	= अणु .type = NLA_U16 पूर्ण,
	[NHA_BLACKHOLE]		= अणु .type = NLA_FLAG पूर्ण,
	[NHA_OIF]		= अणु .type = NLA_U32 पूर्ण,
	[NHA_GATEWAY]		= अणु .type = NLA_BINARY पूर्ण,
	[NHA_ENCAP_TYPE]	= अणु .type = NLA_U16 पूर्ण,
	[NHA_ENCAP]		= अणु .type = NLA_NESTED पूर्ण,
	[NHA_FDB]		= अणु .type = NLA_FLAG पूर्ण,
	[NHA_RES_GROUP]		= अणु .type = NLA_NESTED पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा nla_policy rपंचांग_nh_policy_get[] = अणु
	[NHA_ID]		= अणु .type = NLA_U32 पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा nla_policy rपंचांग_nh_policy_dump[] = अणु
	[NHA_OIF]		= अणु .type = NLA_U32 पूर्ण,
	[NHA_GROUPS]		= अणु .type = NLA_FLAG पूर्ण,
	[NHA_MASTER]		= अणु .type = NLA_U32 पूर्ण,
	[NHA_FDB]		= अणु .type = NLA_FLAG पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा nla_policy rपंचांग_nh_res_policy_new[] = अणु
	[NHA_RES_GROUP_BUCKETS]			= अणु .type = NLA_U16 पूर्ण,
	[NHA_RES_GROUP_IDLE_TIMER]		= अणु .type = NLA_U32 पूर्ण,
	[NHA_RES_GROUP_UNBALANCED_TIMER]	= अणु .type = NLA_U32 पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा nla_policy rपंचांग_nh_policy_dump_bucket[] = अणु
	[NHA_ID]		= अणु .type = NLA_U32 पूर्ण,
	[NHA_OIF]		= अणु .type = NLA_U32 पूर्ण,
	[NHA_MASTER]		= अणु .type = NLA_U32 पूर्ण,
	[NHA_RES_BUCKET]	= अणु .type = NLA_NESTED पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा nla_policy rपंचांग_nh_res_bucket_policy_dump[] = अणु
	[NHA_RES_BUCKET_NH_ID]	= अणु .type = NLA_U32 पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा nla_policy rपंचांग_nh_policy_get_bucket[] = अणु
	[NHA_ID]		= अणु .type = NLA_U32 पूर्ण,
	[NHA_RES_BUCKET]	= अणु .type = NLA_NESTED पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा nla_policy rपंचांग_nh_res_bucket_policy_get[] = अणु
	[NHA_RES_BUCKET_INDEX]	= अणु .type = NLA_U16 पूर्ण,
पूर्ण;

अटल bool nexthop_notअगरiers_is_empty(काष्ठा net *net)
अणु
	वापस !net->nexthop.notअगरier_chain.head;
पूर्ण

अटल व्योम
__nh_notअगरier_single_info_init(काष्ठा nh_notअगरier_single_info *nh_info,
			       स्थिर काष्ठा nh_info *nhi)
अणु
	nh_info->dev = nhi->fib_nhc.nhc_dev;
	nh_info->gw_family = nhi->fib_nhc.nhc_gw_family;
	अगर (nh_info->gw_family == AF_INET)
		nh_info->ipv4 = nhi->fib_nhc.nhc_gw.ipv4;
	अन्यथा अगर (nh_info->gw_family == AF_INET6)
		nh_info->ipv6 = nhi->fib_nhc.nhc_gw.ipv6;

	nh_info->is_reject = nhi->reject_nh;
	nh_info->is_fdb = nhi->fdb_nh;
	nh_info->has_encap = !!nhi->fib_nhc.nhc_lwtstate;
पूर्ण

अटल पूर्णांक nh_notअगरier_single_info_init(काष्ठा nh_notअगरier_info *info,
					स्थिर काष्ठा nexthop *nh)
अणु
	काष्ठा nh_info *nhi = rtnl_dereference(nh->nh_info);

	info->type = NH_NOTIFIER_INFO_TYPE_SINGLE;
	info->nh = kzalloc(माप(*info->nh), GFP_KERNEL);
	अगर (!info->nh)
		वापस -ENOMEM;

	__nh_notअगरier_single_info_init(info->nh, nhi);

	वापस 0;
पूर्ण

अटल व्योम nh_notअगरier_single_info_fini(काष्ठा nh_notअगरier_info *info)
अणु
	kमुक्त(info->nh);
पूर्ण

अटल पूर्णांक nh_notअगरier_mpath_info_init(काष्ठा nh_notअगरier_info *info,
				       काष्ठा nh_group *nhg)
अणु
	u16 num_nh = nhg->num_nh;
	पूर्णांक i;

	info->type = NH_NOTIFIER_INFO_TYPE_GRP;
	info->nh_grp = kzalloc(काष्ठा_size(info->nh_grp, nh_entries, num_nh),
			       GFP_KERNEL);
	अगर (!info->nh_grp)
		वापस -ENOMEM;

	info->nh_grp->num_nh = num_nh;
	info->nh_grp->is_fdb = nhg->fdb_nh;

	क्रम (i = 0; i < num_nh; i++) अणु
		काष्ठा nh_grp_entry *nhge = &nhg->nh_entries[i];
		काष्ठा nh_info *nhi;

		nhi = rtnl_dereference(nhge->nh->nh_info);
		info->nh_grp->nh_entries[i].id = nhge->nh->id;
		info->nh_grp->nh_entries[i].weight = nhge->weight;
		__nh_notअगरier_single_info_init(&info->nh_grp->nh_entries[i].nh,
					       nhi);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक nh_notअगरier_res_table_info_init(काष्ठा nh_notअगरier_info *info,
					   काष्ठा nh_group *nhg)
अणु
	काष्ठा nh_res_table *res_table = rtnl_dereference(nhg->res_table);
	u16 num_nh_buckets = res_table->num_nh_buckets;
	अचिन्हित दीर्घ size;
	u16 i;

	info->type = NH_NOTIFIER_INFO_TYPE_RES_TABLE;
	size = काष्ठा_size(info->nh_res_table, nhs, num_nh_buckets);
	info->nh_res_table = __vदो_स्मृति(size, GFP_KERNEL | __GFP_ZERO |
				       __GFP_NOWARN);
	अगर (!info->nh_res_table)
		वापस -ENOMEM;

	info->nh_res_table->num_nh_buckets = num_nh_buckets;

	क्रम (i = 0; i < num_nh_buckets; i++) अणु
		काष्ठा nh_res_bucket *bucket = &res_table->nh_buckets[i];
		काष्ठा nh_grp_entry *nhge;
		काष्ठा nh_info *nhi;

		nhge = rtnl_dereference(bucket->nh_entry);
		nhi = rtnl_dereference(nhge->nh->nh_info);
		__nh_notअगरier_single_info_init(&info->nh_res_table->nhs[i],
					       nhi);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक nh_notअगरier_grp_info_init(काष्ठा nh_notअगरier_info *info,
				     स्थिर काष्ठा nexthop *nh)
अणु
	काष्ठा nh_group *nhg = rtnl_dereference(nh->nh_grp);

	अगर (nhg->hash_threshold)
		वापस nh_notअगरier_mpath_info_init(info, nhg);
	अन्यथा अगर (nhg->resilient)
		वापस nh_notअगरier_res_table_info_init(info, nhg);
	वापस -EINVAL;
पूर्ण

अटल व्योम nh_notअगरier_grp_info_fini(काष्ठा nh_notअगरier_info *info,
				      स्थिर काष्ठा nexthop *nh)
अणु
	काष्ठा nh_group *nhg = rtnl_dereference(nh->nh_grp);

	अगर (nhg->hash_threshold)
		kमुक्त(info->nh_grp);
	अन्यथा अगर (nhg->resilient)
		vमुक्त(info->nh_res_table);
पूर्ण

अटल पूर्णांक nh_notअगरier_info_init(काष्ठा nh_notअगरier_info *info,
				 स्थिर काष्ठा nexthop *nh)
अणु
	info->id = nh->id;

	अगर (nh->is_group)
		वापस nh_notअगरier_grp_info_init(info, nh);
	अन्यथा
		वापस nh_notअगरier_single_info_init(info, nh);
पूर्ण

अटल व्योम nh_notअगरier_info_fini(काष्ठा nh_notअगरier_info *info,
				  स्थिर काष्ठा nexthop *nh)
अणु
	अगर (nh->is_group)
		nh_notअगरier_grp_info_fini(info, nh);
	अन्यथा
		nh_notअगरier_single_info_fini(info);
पूर्ण

अटल पूर्णांक call_nexthop_notअगरiers(काष्ठा net *net,
				  क्रमागत nexthop_event_type event_type,
				  काष्ठा nexthop *nh,
				  काष्ठा netlink_ext_ack *extack)
अणु
	काष्ठा nh_notअगरier_info info = अणु
		.net = net,
		.extack = extack,
	पूर्ण;
	पूर्णांक err;

	ASSERT_RTNL();

	अगर (nexthop_notअगरiers_is_empty(net))
		वापस 0;

	err = nh_notअगरier_info_init(&info, nh);
	अगर (err) अणु
		NL_SET_ERR_MSG(extack, "Failed to initialize nexthop notifier info");
		वापस err;
	पूर्ण

	err = blocking_notअगरier_call_chain(&net->nexthop.notअगरier_chain,
					   event_type, &info);
	nh_notअगरier_info_fini(&info, nh);

	वापस notअगरier_to_त्रुटि_सं(err);
पूर्ण

अटल पूर्णांक
nh_notअगरier_res_bucket_idle_समयr_get(स्थिर काष्ठा nh_notअगरier_info *info,
				      bool क्रमce, अचिन्हित पूर्णांक *p_idle_समयr_ms)
अणु
	काष्ठा nh_res_table *res_table;
	काष्ठा nh_group *nhg;
	काष्ठा nexthop *nh;
	पूर्णांक err = 0;

	/* When 'force' is false, nexthop bucket replacement is perक्रमmed
	 * because the bucket was deemed to be idle. In this हाल, capable
	 * listeners can choose to perक्रमm an atomic replacement: The bucket is
	 * only replaced अगर it is inactive. However, अगर the idle समयr पूर्णांकerval
	 * is smaller than the पूर्णांकerval in which a listener is querying
	 * buckets' activity from the device, then atomic replacement should
	 * not be tried. Pass the idle समयr value to listeners, so that they
	 * could determine which type of replacement to perक्रमm.
	 */
	अगर (क्रमce) अणु
		*p_idle_समयr_ms = 0;
		वापस 0;
	पूर्ण

	rcu_पढ़ो_lock();

	nh = nexthop_find_by_id(info->net, info->id);
	अगर (!nh) अणु
		err = -EINVAL;
		जाओ out;
	पूर्ण

	nhg = rcu_dereference(nh->nh_grp);
	res_table = rcu_dereference(nhg->res_table);
	*p_idle_समयr_ms = jअगरfies_to_msecs(res_table->idle_समयr);

out:
	rcu_पढ़ो_unlock();

	वापस err;
पूर्ण

अटल पूर्णांक nh_notअगरier_res_bucket_info_init(काष्ठा nh_notअगरier_info *info,
					    u16 bucket_index, bool क्रमce,
					    काष्ठा nh_info *oldi,
					    काष्ठा nh_info *newi)
अणु
	अचिन्हित पूर्णांक idle_समयr_ms;
	पूर्णांक err;

	err = nh_notअगरier_res_bucket_idle_समयr_get(info, क्रमce,
						    &idle_समयr_ms);
	अगर (err)
		वापस err;

	info->type = NH_NOTIFIER_INFO_TYPE_RES_BUCKET;
	info->nh_res_bucket = kzalloc(माप(*info->nh_res_bucket),
				      GFP_KERNEL);
	अगर (!info->nh_res_bucket)
		वापस -ENOMEM;

	info->nh_res_bucket->bucket_index = bucket_index;
	info->nh_res_bucket->idle_समयr_ms = idle_समयr_ms;
	info->nh_res_bucket->क्रमce = क्रमce;
	__nh_notअगरier_single_info_init(&info->nh_res_bucket->old_nh, oldi);
	__nh_notअगरier_single_info_init(&info->nh_res_bucket->new_nh, newi);
	वापस 0;
पूर्ण

अटल व्योम nh_notअगरier_res_bucket_info_fini(काष्ठा nh_notअगरier_info *info)
अणु
	kमुक्त(info->nh_res_bucket);
पूर्ण

अटल पूर्णांक __call_nexthop_res_bucket_notअगरiers(काष्ठा net *net, u32 nhg_id,
					       u16 bucket_index, bool क्रमce,
					       काष्ठा nh_info *oldi,
					       काष्ठा nh_info *newi,
					       काष्ठा netlink_ext_ack *extack)
अणु
	काष्ठा nh_notअगरier_info info = अणु
		.net = net,
		.extack = extack,
		.id = nhg_id,
	पूर्ण;
	पूर्णांक err;

	अगर (nexthop_notअगरiers_is_empty(net))
		वापस 0;

	err = nh_notअगरier_res_bucket_info_init(&info, bucket_index, क्रमce,
					       oldi, newi);
	अगर (err)
		वापस err;

	err = blocking_notअगरier_call_chain(&net->nexthop.notअगरier_chain,
					   NEXTHOP_EVENT_BUCKET_REPLACE, &info);
	nh_notअगरier_res_bucket_info_fini(&info);

	वापस notअगरier_to_त्रुटि_सं(err);
पूर्ण

/* There are three users of RES_TABLE, and NHs etc. referenced from there:
 *
 * 1) a collection of callbacks क्रम NH मुख्यtenance. This operates under
 *    RTNL,
 * 2) the delayed work that gradually balances the resilient table,
 * 3) and nexthop_select_path(), operating under RCU.
 *
 * Both the delayed work and the RTNL block are ग_लिखोrs, and need to
 * मुख्यtain mutual exclusion. Since there are only two and well-known
 * ग_लिखोrs क्रम each table, the RTNL code can make sure it has exclusive
 * access thus:
 *
 * - Have the DW operate without locking;
 * - synchronously cancel the DW;
 * - करो the writing;
 * - अगर the ग_लिखो was not actually a delete, call upkeep, which schedules
 *   DW again अगर necessary.
 *
 * The functions that are always called from the RTNL context use
 * rtnl_dereference(). The functions that can also be called from the DW करो
 * a raw dereference and rely on the above mutual exclusion scheme.
 */
#घोषणा nh_res_dereference(p) (rcu_dereference_raw(p))

अटल पूर्णांक call_nexthop_res_bucket_notअगरiers(काष्ठा net *net, u32 nhg_id,
					     u16 bucket_index, bool क्रमce,
					     काष्ठा nexthop *old_nh,
					     काष्ठा nexthop *new_nh,
					     काष्ठा netlink_ext_ack *extack)
अणु
	काष्ठा nh_info *oldi = nh_res_dereference(old_nh->nh_info);
	काष्ठा nh_info *newi = nh_res_dereference(new_nh->nh_info);

	वापस __call_nexthop_res_bucket_notअगरiers(net, nhg_id, bucket_index,
						   क्रमce, oldi, newi, extack);
पूर्ण

अटल पूर्णांक call_nexthop_res_table_notअगरiers(काष्ठा net *net, काष्ठा nexthop *nh,
					    काष्ठा netlink_ext_ack *extack)
अणु
	काष्ठा nh_notअगरier_info info = अणु
		.net = net,
		.extack = extack,
	पूर्ण;
	काष्ठा nh_group *nhg;
	पूर्णांक err;

	ASSERT_RTNL();

	अगर (nexthop_notअगरiers_is_empty(net))
		वापस 0;

	/* At this poपूर्णांक, the nexthop buckets are still not populated. Only
	 * emit a notअगरication with the logical nexthops, so that a listener
	 * could potentially veto it in हाल of unsupported configuration.
	 */
	nhg = rtnl_dereference(nh->nh_grp);
	err = nh_notअगरier_mpath_info_init(&info, nhg);
	अगर (err) अणु
		NL_SET_ERR_MSG(extack, "Failed to initialize nexthop notifier info");
		वापस err;
	पूर्ण

	err = blocking_notअगरier_call_chain(&net->nexthop.notअगरier_chain,
					   NEXTHOP_EVENT_RES_TABLE_PRE_REPLACE,
					   &info);
	kमुक्त(info.nh_grp);

	वापस notअगरier_to_त्रुटि_सं(err);
पूर्ण

अटल पूर्णांक call_nexthop_notअगरier(काष्ठा notअगरier_block *nb, काष्ठा net *net,
				 क्रमागत nexthop_event_type event_type,
				 काष्ठा nexthop *nh,
				 काष्ठा netlink_ext_ack *extack)
अणु
	काष्ठा nh_notअगरier_info info = अणु
		.net = net,
		.extack = extack,
	पूर्ण;
	पूर्णांक err;

	err = nh_notअगरier_info_init(&info, nh);
	अगर (err)
		वापस err;

	err = nb->notअगरier_call(nb, event_type, &info);
	nh_notअगरier_info_fini(&info, nh);

	वापस notअगरier_to_त्रुटि_सं(err);
पूर्ण

अटल अचिन्हित पूर्णांक nh_dev_hashfn(अचिन्हित पूर्णांक val)
अणु
	अचिन्हित पूर्णांक mask = NH_DEV_HASHSIZE - 1;

	वापस (val ^
		(val >> NH_DEV_HASHBITS) ^
		(val >> (NH_DEV_HASHBITS * 2))) & mask;
पूर्ण

अटल व्योम nexthop_devhash_add(काष्ठा net *net, काष्ठा nh_info *nhi)
अणु
	काष्ठा net_device *dev = nhi->fib_nhc.nhc_dev;
	काष्ठा hlist_head *head;
	अचिन्हित पूर्णांक hash;

	WARN_ON(!dev);

	hash = nh_dev_hashfn(dev->अगरindex);
	head = &net->nexthop.devhash[hash];
	hlist_add_head(&nhi->dev_hash, head);
पूर्ण

अटल व्योम nexthop_मुक्त_group(काष्ठा nexthop *nh)
अणु
	काष्ठा nh_group *nhg;
	पूर्णांक i;

	nhg = rcu_dereference_raw(nh->nh_grp);
	क्रम (i = 0; i < nhg->num_nh; ++i) अणु
		काष्ठा nh_grp_entry *nhge = &nhg->nh_entries[i];

		WARN_ON(!list_empty(&nhge->nh_list));
		nexthop_put(nhge->nh);
	पूर्ण

	WARN_ON(nhg->spare == nhg);

	अगर (nhg->resilient)
		vमुक्त(rcu_dereference_raw(nhg->res_table));

	kमुक्त(nhg->spare);
	kमुक्त(nhg);
पूर्ण

अटल व्योम nexthop_मुक्त_single(काष्ठा nexthop *nh)
अणु
	काष्ठा nh_info *nhi;

	nhi = rcu_dereference_raw(nh->nh_info);
	चयन (nhi->family) अणु
	हाल AF_INET:
		fib_nh_release(nh->net, &nhi->fib_nh);
		अवरोध;
	हाल AF_INET6:
		ipv6_stub->fib6_nh_release(&nhi->fib6_nh);
		अवरोध;
	पूर्ण
	kमुक्त(nhi);
पूर्ण

व्योम nexthop_मुक्त_rcu(काष्ठा rcu_head *head)
अणु
	काष्ठा nexthop *nh = container_of(head, काष्ठा nexthop, rcu);

	अगर (nh->is_group)
		nexthop_मुक्त_group(nh);
	अन्यथा
		nexthop_मुक्त_single(nh);

	kमुक्त(nh);
पूर्ण
EXPORT_SYMBOL_GPL(nexthop_मुक्त_rcu);

अटल काष्ठा nexthop *nexthop_alloc(व्योम)
अणु
	काष्ठा nexthop *nh;

	nh = kzalloc(माप(काष्ठा nexthop), GFP_KERNEL);
	अगर (nh) अणु
		INIT_LIST_HEAD(&nh->fi_list);
		INIT_LIST_HEAD(&nh->f6i_list);
		INIT_LIST_HEAD(&nh->grp_list);
		INIT_LIST_HEAD(&nh->fdb_list);
	पूर्ण
	वापस nh;
पूर्ण

अटल काष्ठा nh_group *nexthop_grp_alloc(u16 num_nh)
अणु
	काष्ठा nh_group *nhg;

	nhg = kzalloc(काष्ठा_size(nhg, nh_entries, num_nh), GFP_KERNEL);
	अगर (nhg)
		nhg->num_nh = num_nh;

	वापस nhg;
पूर्ण

अटल व्योम nh_res_table_upkeep_dw(काष्ठा work_काष्ठा *work);

अटल काष्ठा nh_res_table *
nexthop_res_table_alloc(काष्ठा net *net, u32 nhg_id, काष्ठा nh_config *cfg)
अणु
	स्थिर u16 num_nh_buckets = cfg->nh_grp_res_num_buckets;
	काष्ठा nh_res_table *res_table;
	अचिन्हित दीर्घ size;

	size = काष्ठा_size(res_table, nh_buckets, num_nh_buckets);
	res_table = __vदो_स्मृति(size, GFP_KERNEL | __GFP_ZERO | __GFP_NOWARN);
	अगर (!res_table)
		वापस शून्य;

	res_table->net = net;
	res_table->nhg_id = nhg_id;
	INIT_DELAYED_WORK(&res_table->upkeep_dw, &nh_res_table_upkeep_dw);
	INIT_LIST_HEAD(&res_table->uw_nh_entries);
	res_table->idle_समयr = cfg->nh_grp_res_idle_समयr;
	res_table->unbalanced_समयr = cfg->nh_grp_res_unbalanced_समयr;
	res_table->num_nh_buckets = num_nh_buckets;
	वापस res_table;
पूर्ण

अटल व्योम nh_base_seq_inc(काष्ठा net *net)
अणु
	जबतक (++net->nexthop.seq == 0)
		;
पूर्ण

/* no reference taken; rcu lock or rtnl must be held */
काष्ठा nexthop *nexthop_find_by_id(काष्ठा net *net, u32 id)
अणु
	काष्ठा rb_node **pp, *parent = शून्य, *next;

	pp = &net->nexthop.rb_root.rb_node;
	जबतक (1) अणु
		काष्ठा nexthop *nh;

		next = rcu_dereference_raw(*pp);
		अगर (!next)
			अवरोध;
		parent = next;

		nh = rb_entry(parent, काष्ठा nexthop, rb_node);
		अगर (id < nh->id)
			pp = &next->rb_left;
		अन्यथा अगर (id > nh->id)
			pp = &next->rb_right;
		अन्यथा
			वापस nh;
	पूर्ण
	वापस शून्य;
पूर्ण
EXPORT_SYMBOL_GPL(nexthop_find_by_id);

/* used क्रम स्वतः id allocation; called with rtnl held */
अटल u32 nh_find_unused_id(काष्ठा net *net)
अणु
	u32 id_start = net->nexthop.last_id_allocated;

	जबतक (1) अणु
		net->nexthop.last_id_allocated++;
		अगर (net->nexthop.last_id_allocated == id_start)
			अवरोध;

		अगर (!nexthop_find_by_id(net, net->nexthop.last_id_allocated))
			वापस net->nexthop.last_id_allocated;
	पूर्ण
	वापस 0;
पूर्ण

अटल व्योम nh_res_समय_set_deadline(अचिन्हित दीर्घ next_समय,
				     अचिन्हित दीर्घ *deadline)
अणु
	अगर (समय_beक्रमe(next_समय, *deadline))
		*deadline = next_समय;
पूर्ण

अटल घड़ी_प्रकार nh_res_table_unbalanced_समय(काष्ठा nh_res_table *res_table)
अणु
	अगर (list_empty(&res_table->uw_nh_entries))
		वापस 0;
	वापस jअगरfies_delta_to_घड़ी_प्रकार(jअगरfies - res_table->unbalanced_since);
पूर्ण

अटल पूर्णांक nla_put_nh_group_res(काष्ठा sk_buff *skb, काष्ठा nh_group *nhg)
अणु
	काष्ठा nh_res_table *res_table = rtnl_dereference(nhg->res_table);
	काष्ठा nlattr *nest;

	nest = nla_nest_start(skb, NHA_RES_GROUP);
	अगर (!nest)
		वापस -EMSGSIZE;

	अगर (nla_put_u16(skb, NHA_RES_GROUP_BUCKETS,
			res_table->num_nh_buckets) ||
	    nla_put_u32(skb, NHA_RES_GROUP_IDLE_TIMER,
			jअगरfies_to_घड़ी_प्रकार(res_table->idle_समयr)) ||
	    nla_put_u32(skb, NHA_RES_GROUP_UNBALANCED_TIMER,
			jअगरfies_to_घड़ी_प्रकार(res_table->unbalanced_समयr)) ||
	    nla_put_u64_64bit(skb, NHA_RES_GROUP_UNBALANCED_TIME,
			      nh_res_table_unbalanced_समय(res_table),
			      NHA_RES_GROUP_PAD))
		जाओ nla_put_failure;

	nla_nest_end(skb, nest);
	वापस 0;

nla_put_failure:
	nla_nest_cancel(skb, nest);
	वापस -EMSGSIZE;
पूर्ण

अटल पूर्णांक nla_put_nh_group(काष्ठा sk_buff *skb, काष्ठा nh_group *nhg)
अणु
	काष्ठा nexthop_grp *p;
	माप_प्रकार len = nhg->num_nh * माप(*p);
	काष्ठा nlattr *nla;
	u16 group_type = 0;
	पूर्णांक i;

	अगर (nhg->hash_threshold)
		group_type = NEXTHOP_GRP_TYPE_MPATH;
	अन्यथा अगर (nhg->resilient)
		group_type = NEXTHOP_GRP_TYPE_RES;

	अगर (nla_put_u16(skb, NHA_GROUP_TYPE, group_type))
		जाओ nla_put_failure;

	nla = nla_reserve(skb, NHA_GROUP, len);
	अगर (!nla)
		जाओ nla_put_failure;

	p = nla_data(nla);
	क्रम (i = 0; i < nhg->num_nh; ++i) अणु
		p->id = nhg->nh_entries[i].nh->id;
		p->weight = nhg->nh_entries[i].weight - 1;
		p += 1;
	पूर्ण

	अगर (nhg->resilient && nla_put_nh_group_res(skb, nhg))
		जाओ nla_put_failure;

	वापस 0;

nla_put_failure:
	वापस -EMSGSIZE;
पूर्ण

अटल पूर्णांक nh_fill_node(काष्ठा sk_buff *skb, काष्ठा nexthop *nh,
			पूर्णांक event, u32 portid, u32 seq, अचिन्हित पूर्णांक nlflags)
अणु
	काष्ठा fib6_nh *fib6_nh;
	काष्ठा fib_nh *fib_nh;
	काष्ठा nlmsghdr *nlh;
	काष्ठा nh_info *nhi;
	काष्ठा nhmsg *nhm;

	nlh = nlmsg_put(skb, portid, seq, event, माप(*nhm), nlflags);
	अगर (!nlh)
		वापस -EMSGSIZE;

	nhm = nlmsg_data(nlh);
	nhm->nh_family = AF_UNSPEC;
	nhm->nh_flags = nh->nh_flags;
	nhm->nh_protocol = nh->protocol;
	nhm->nh_scope = 0;
	nhm->resvd = 0;

	अगर (nla_put_u32(skb, NHA_ID, nh->id))
		जाओ nla_put_failure;

	अगर (nh->is_group) अणु
		काष्ठा nh_group *nhg = rtnl_dereference(nh->nh_grp);

		अगर (nhg->fdb_nh && nla_put_flag(skb, NHA_FDB))
			जाओ nla_put_failure;
		अगर (nla_put_nh_group(skb, nhg))
			जाओ nla_put_failure;
		जाओ out;
	पूर्ण

	nhi = rtnl_dereference(nh->nh_info);
	nhm->nh_family = nhi->family;
	अगर (nhi->reject_nh) अणु
		अगर (nla_put_flag(skb, NHA_BLACKHOLE))
			जाओ nla_put_failure;
		जाओ out;
	पूर्ण अन्यथा अगर (nhi->fdb_nh) अणु
		अगर (nla_put_flag(skb, NHA_FDB))
			जाओ nla_put_failure;
	पूर्ण अन्यथा अणु
		स्थिर काष्ठा net_device *dev;

		dev = nhi->fib_nhc.nhc_dev;
		अगर (dev && nla_put_u32(skb, NHA_OIF, dev->अगरindex))
			जाओ nla_put_failure;
	पूर्ण

	nhm->nh_scope = nhi->fib_nhc.nhc_scope;
	चयन (nhi->family) अणु
	हाल AF_INET:
		fib_nh = &nhi->fib_nh;
		अगर (fib_nh->fib_nh_gw_family &&
		    nla_put_be32(skb, NHA_GATEWAY, fib_nh->fib_nh_gw4))
			जाओ nla_put_failure;
		अवरोध;

	हाल AF_INET6:
		fib6_nh = &nhi->fib6_nh;
		अगर (fib6_nh->fib_nh_gw_family &&
		    nla_put_in6_addr(skb, NHA_GATEWAY, &fib6_nh->fib_nh_gw6))
			जाओ nla_put_failure;
		अवरोध;
	पूर्ण

	अगर (nhi->fib_nhc.nhc_lwtstate &&
	    lwtunnel_fill_encap(skb, nhi->fib_nhc.nhc_lwtstate,
				NHA_ENCAP, NHA_ENCAP_TYPE) < 0)
		जाओ nla_put_failure;

out:
	nlmsg_end(skb, nlh);
	वापस 0;

nla_put_failure:
	nlmsg_cancel(skb, nlh);
	वापस -EMSGSIZE;
पूर्ण

अटल माप_प्रकार nh_nlmsg_size_grp_res(काष्ठा nh_group *nhg)
अणु
	वापस nla_total_size(0) +	/* NHA_RES_GROUP */
		nla_total_size(2) +	/* NHA_RES_GROUP_BUCKETS */
		nla_total_size(4) +	/* NHA_RES_GROUP_IDLE_TIMER */
		nla_total_size(4) +	/* NHA_RES_GROUP_UNBALANCED_TIMER */
		nla_total_size_64bit(8);/* NHA_RES_GROUP_UNBALANCED_TIME */
पूर्ण

अटल माप_प्रकार nh_nlmsg_size_grp(काष्ठा nexthop *nh)
अणु
	काष्ठा nh_group *nhg = rtnl_dereference(nh->nh_grp);
	माप_प्रकार sz = माप(काष्ठा nexthop_grp) * nhg->num_nh;
	माप_प्रकार tot = nla_total_size(sz) +
		nla_total_size(2); /* NHA_GROUP_TYPE */

	अगर (nhg->resilient)
		tot += nh_nlmsg_size_grp_res(nhg);

	वापस tot;
पूर्ण

अटल माप_प्रकार nh_nlmsg_size_single(काष्ठा nexthop *nh)
अणु
	काष्ठा nh_info *nhi = rtnl_dereference(nh->nh_info);
	माप_प्रकार sz;

	/* covers NHA_BLACKHOLE since NHA_OIF and BLACKHOLE
	 * are mutually exclusive
	 */
	sz = nla_total_size(4);  /* NHA_OIF */

	चयन (nhi->family) अणु
	हाल AF_INET:
		अगर (nhi->fib_nh.fib_nh_gw_family)
			sz += nla_total_size(4);  /* NHA_GATEWAY */
		अवरोध;

	हाल AF_INET6:
		/* NHA_GATEWAY */
		अगर (nhi->fib6_nh.fib_nh_gw_family)
			sz += nla_total_size(माप(स्थिर काष्ठा in6_addr));
		अवरोध;
	पूर्ण

	अगर (nhi->fib_nhc.nhc_lwtstate) अणु
		sz += lwtunnel_get_encap_size(nhi->fib_nhc.nhc_lwtstate);
		sz += nla_total_size(2);  /* NHA_ENCAP_TYPE */
	पूर्ण

	वापस sz;
पूर्ण

अटल माप_प्रकार nh_nlmsg_size(काष्ठा nexthop *nh)
अणु
	माप_प्रकार sz = NLMSG_ALIGN(माप(काष्ठा nhmsg));

	sz += nla_total_size(4); /* NHA_ID */

	अगर (nh->is_group)
		sz += nh_nlmsg_size_grp(nh);
	अन्यथा
		sz += nh_nlmsg_size_single(nh);

	वापस sz;
पूर्ण

अटल व्योम nexthop_notअगरy(पूर्णांक event, काष्ठा nexthop *nh, काष्ठा nl_info *info)
अणु
	अचिन्हित पूर्णांक nlflags = info->nlh ? info->nlh->nlmsg_flags : 0;
	u32 seq = info->nlh ? info->nlh->nlmsg_seq : 0;
	काष्ठा sk_buff *skb;
	पूर्णांक err = -ENOBUFS;

	skb = nlmsg_new(nh_nlmsg_size(nh), gfp_any());
	अगर (!skb)
		जाओ errout;

	err = nh_fill_node(skb, nh, event, info->portid, seq, nlflags);
	अगर (err < 0) अणु
		/* -EMSGSIZE implies BUG in nh_nlmsg_size() */
		WARN_ON(err == -EMSGSIZE);
		kमुक्त_skb(skb);
		जाओ errout;
	पूर्ण

	rtnl_notअगरy(skb, info->nl_net, info->portid, RTNLGRP_NEXTHOP,
		    info->nlh, gfp_any());
	वापस;
errout:
	अगर (err < 0)
		rtnl_set_sk_err(info->nl_net, RTNLGRP_NEXTHOP, err);
पूर्ण

अटल अचिन्हित दीर्घ nh_res_bucket_used_समय(स्थिर काष्ठा nh_res_bucket *bucket)
अणु
	वापस (अचिन्हित दीर्घ)atomic_दीर्घ_पढ़ो(&bucket->used_समय);
पूर्ण

अटल अचिन्हित दीर्घ
nh_res_bucket_idle_poपूर्णांक(स्थिर काष्ठा nh_res_table *res_table,
			 स्थिर काष्ठा nh_res_bucket *bucket,
			 अचिन्हित दीर्घ now)
अणु
	अचिन्हित दीर्घ समय = nh_res_bucket_used_समय(bucket);

	/* Bucket was not used since it was migrated. The idle समय is now. */
	अगर (समय == bucket->migrated_समय)
		वापस now;

	वापस समय + res_table->idle_समयr;
पूर्ण

अटल अचिन्हित दीर्घ
nh_res_table_unb_poपूर्णांक(स्थिर काष्ठा nh_res_table *res_table)
अणु
	वापस res_table->unbalanced_since + res_table->unbalanced_समयr;
पूर्ण

अटल व्योम nh_res_bucket_set_idle(स्थिर काष्ठा nh_res_table *res_table,
				   काष्ठा nh_res_bucket *bucket)
अणु
	अचिन्हित दीर्घ now = jअगरfies;

	atomic_दीर्घ_set(&bucket->used_समय, (दीर्घ)now);
	bucket->migrated_समय = now;
पूर्ण

अटल व्योम nh_res_bucket_set_busy(काष्ठा nh_res_bucket *bucket)
अणु
	atomic_दीर्घ_set(&bucket->used_समय, (दीर्घ)jअगरfies);
पूर्ण

अटल घड़ी_प्रकार nh_res_bucket_idle_समय(स्थिर काष्ठा nh_res_bucket *bucket)
अणु
	अचिन्हित दीर्घ used_समय = nh_res_bucket_used_समय(bucket);

	वापस jअगरfies_delta_to_घड़ी_प्रकार(jअगरfies - used_समय);
पूर्ण

अटल पूर्णांक nh_fill_res_bucket(काष्ठा sk_buff *skb, काष्ठा nexthop *nh,
			      काष्ठा nh_res_bucket *bucket, u16 bucket_index,
			      पूर्णांक event, u32 portid, u32 seq,
			      अचिन्हित पूर्णांक nlflags,
			      काष्ठा netlink_ext_ack *extack)
अणु
	काष्ठा nh_grp_entry *nhge = nh_res_dereference(bucket->nh_entry);
	काष्ठा nlmsghdr *nlh;
	काष्ठा nlattr *nest;
	काष्ठा nhmsg *nhm;

	nlh = nlmsg_put(skb, portid, seq, event, माप(*nhm), nlflags);
	अगर (!nlh)
		वापस -EMSGSIZE;

	nhm = nlmsg_data(nlh);
	nhm->nh_family = AF_UNSPEC;
	nhm->nh_flags = bucket->nh_flags;
	nhm->nh_protocol = nh->protocol;
	nhm->nh_scope = 0;
	nhm->resvd = 0;

	अगर (nla_put_u32(skb, NHA_ID, nh->id))
		जाओ nla_put_failure;

	nest = nla_nest_start(skb, NHA_RES_BUCKET);
	अगर (!nest)
		जाओ nla_put_failure;

	अगर (nla_put_u16(skb, NHA_RES_BUCKET_INDEX, bucket_index) ||
	    nla_put_u32(skb, NHA_RES_BUCKET_NH_ID, nhge->nh->id) ||
	    nla_put_u64_64bit(skb, NHA_RES_BUCKET_IDLE_TIME,
			      nh_res_bucket_idle_समय(bucket),
			      NHA_RES_BUCKET_PAD))
		जाओ nla_put_failure_nest;

	nla_nest_end(skb, nest);
	nlmsg_end(skb, nlh);
	वापस 0;

nla_put_failure_nest:
	nla_nest_cancel(skb, nest);
nla_put_failure:
	nlmsg_cancel(skb, nlh);
	वापस -EMSGSIZE;
पूर्ण

अटल व्योम nexthop_bucket_notअगरy(काष्ठा nh_res_table *res_table,
				  u16 bucket_index)
अणु
	काष्ठा nh_res_bucket *bucket = &res_table->nh_buckets[bucket_index];
	काष्ठा nh_grp_entry *nhge = nh_res_dereference(bucket->nh_entry);
	काष्ठा nexthop *nh = nhge->nh_parent;
	काष्ठा sk_buff *skb;
	पूर्णांक err = -ENOBUFS;

	skb = alloc_skb(NLMSG_GOODSIZE, GFP_KERNEL);
	अगर (!skb)
		जाओ errout;

	err = nh_fill_res_bucket(skb, nh, bucket, bucket_index,
				 RTM_NEWNEXTHOPBUCKET, 0, 0, NLM_F_REPLACE,
				 शून्य);
	अगर (err < 0) अणु
		kमुक्त_skb(skb);
		जाओ errout;
	पूर्ण

	rtnl_notअगरy(skb, nh->net, 0, RTNLGRP_NEXTHOP, शून्य, GFP_KERNEL);
	वापस;
errout:
	अगर (err < 0)
		rtnl_set_sk_err(nh->net, RTNLGRP_NEXTHOP, err);
पूर्ण

अटल bool valid_group_nh(काष्ठा nexthop *nh, अचिन्हित पूर्णांक npaths,
			   bool *is_fdb, काष्ठा netlink_ext_ack *extack)
अणु
	अगर (nh->is_group) अणु
		काष्ठा nh_group *nhg = rtnl_dereference(nh->nh_grp);

		/* Nesting groups within groups is not supported. */
		अगर (nhg->hash_threshold) अणु
			NL_SET_ERR_MSG(extack,
				       "Hash-threshold group can not be a nexthop within a group");
			वापस false;
		पूर्ण
		अगर (nhg->resilient) अणु
			NL_SET_ERR_MSG(extack,
				       "Resilient group can not be a nexthop within a group");
			वापस false;
		पूर्ण
		*is_fdb = nhg->fdb_nh;
	पूर्ण अन्यथा अणु
		काष्ठा nh_info *nhi = rtnl_dereference(nh->nh_info);

		अगर (nhi->reject_nh && npaths > 1) अणु
			NL_SET_ERR_MSG(extack,
				       "Blackhole nexthop can not be used in a group with more than 1 path");
			वापस false;
		पूर्ण
		*is_fdb = nhi->fdb_nh;
	पूर्ण

	वापस true;
पूर्ण

अटल पूर्णांक nh_check_attr_fdb_group(काष्ठा nexthop *nh, u8 *nh_family,
				   काष्ठा netlink_ext_ack *extack)
अणु
	काष्ठा nh_info *nhi;

	nhi = rtnl_dereference(nh->nh_info);

	अगर (!nhi->fdb_nh) अणु
		NL_SET_ERR_MSG(extack, "FDB nexthop group can only have fdb nexthops");
		वापस -EINVAL;
	पूर्ण

	अगर (*nh_family == AF_UNSPEC) अणु
		*nh_family = nhi->family;
	पूर्ण अन्यथा अगर (*nh_family != nhi->family) अणु
		NL_SET_ERR_MSG(extack, "FDB nexthop group cannot have mixed family nexthops");
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक nh_check_attr_group(काष्ठा net *net,
			       काष्ठा nlattr *tb[], माप_प्रकार tb_size,
			       u16 nh_grp_type, काष्ठा netlink_ext_ack *extack)
अणु
	अचिन्हित पूर्णांक len = nla_len(tb[NHA_GROUP]);
	u8 nh_family = AF_UNSPEC;
	काष्ठा nexthop_grp *nhg;
	अचिन्हित पूर्णांक i, j;
	u8 nhg_fdb = 0;

	अगर (!len || len & (माप(काष्ठा nexthop_grp) - 1)) अणु
		NL_SET_ERR_MSG(extack,
			       "Invalid length for nexthop group attribute");
		वापस -EINVAL;
	पूर्ण

	/* convert len to number of nexthop ids */
	len /= माप(*nhg);

	nhg = nla_data(tb[NHA_GROUP]);
	क्रम (i = 0; i < len; ++i) अणु
		अगर (nhg[i].resvd1 || nhg[i].resvd2) अणु
			NL_SET_ERR_MSG(extack, "Reserved fields in nexthop_grp must be 0");
			वापस -EINVAL;
		पूर्ण
		अगर (nhg[i].weight > 254) अणु
			NL_SET_ERR_MSG(extack, "Invalid value for weight");
			वापस -EINVAL;
		पूर्ण
		क्रम (j = i + 1; j < len; ++j) अणु
			अगर (nhg[i].id == nhg[j].id) अणु
				NL_SET_ERR_MSG(extack, "Nexthop id can not be used twice in a group");
				वापस -EINVAL;
			पूर्ण
		पूर्ण
	पूर्ण

	अगर (tb[NHA_FDB])
		nhg_fdb = 1;
	nhg = nla_data(tb[NHA_GROUP]);
	क्रम (i = 0; i < len; ++i) अणु
		काष्ठा nexthop *nh;
		bool is_fdb_nh;

		nh = nexthop_find_by_id(net, nhg[i].id);
		अगर (!nh) अणु
			NL_SET_ERR_MSG(extack, "Invalid nexthop id");
			वापस -EINVAL;
		पूर्ण
		अगर (!valid_group_nh(nh, len, &is_fdb_nh, extack))
			वापस -EINVAL;

		अगर (nhg_fdb && nh_check_attr_fdb_group(nh, &nh_family, extack))
			वापस -EINVAL;

		अगर (!nhg_fdb && is_fdb_nh) अणु
			NL_SET_ERR_MSG(extack, "Non FDB nexthop group cannot have fdb nexthops");
			वापस -EINVAL;
		पूर्ण
	पूर्ण
	क्रम (i = NHA_GROUP_TYPE + 1; i < tb_size; ++i) अणु
		अगर (!tb[i])
			जारी;
		चयन (i) अणु
		हाल NHA_FDB:
			जारी;
		हाल NHA_RES_GROUP:
			अगर (nh_grp_type == NEXTHOP_GRP_TYPE_RES)
				जारी;
			अवरोध;
		पूर्ण
		NL_SET_ERR_MSG(extack,
			       "No other attributes can be set in nexthop groups");
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल bool ipv6_good_nh(स्थिर काष्ठा fib6_nh *nh)
अणु
	पूर्णांक state = NUD_REACHABLE;
	काष्ठा neighbour *n;

	rcu_पढ़ो_lock_bh();

	n = __ipv6_neigh_lookup_noref_stub(nh->fib_nh_dev, &nh->fib_nh_gw6);
	अगर (n)
		state = n->nud_state;

	rcu_पढ़ो_unlock_bh();

	वापस !!(state & NUD_VALID);
पूर्ण

अटल bool ipv4_good_nh(स्थिर काष्ठा fib_nh *nh)
अणु
	पूर्णांक state = NUD_REACHABLE;
	काष्ठा neighbour *n;

	rcu_पढ़ो_lock_bh();

	n = __ipv4_neigh_lookup_noref(nh->fib_nh_dev,
				      (__क्रमce u32)nh->fib_nh_gw4);
	अगर (n)
		state = n->nud_state;

	rcu_पढ़ो_unlock_bh();

	वापस !!(state & NUD_VALID);
पूर्ण

अटल काष्ठा nexthop *nexthop_select_path_hthr(काष्ठा nh_group *nhg, पूर्णांक hash)
अणु
	काष्ठा nexthop *rc = शून्य;
	पूर्णांक i;

	क्रम (i = 0; i < nhg->num_nh; ++i) अणु
		काष्ठा nh_grp_entry *nhge = &nhg->nh_entries[i];
		काष्ठा nh_info *nhi;

		अगर (hash > atomic_पढ़ो(&nhge->hthr.upper_bound))
			जारी;

		nhi = rcu_dereference(nhge->nh->nh_info);
		अगर (nhi->fdb_nh)
			वापस nhge->nh;

		/* nexthops always check अगर it is good and करोes
		 * not rely on a sysctl क्रम this behavior
		 */
		चयन (nhi->family) अणु
		हाल AF_INET:
			अगर (ipv4_good_nh(&nhi->fib_nh))
				वापस nhge->nh;
			अवरोध;
		हाल AF_INET6:
			अगर (ipv6_good_nh(&nhi->fib6_nh))
				वापस nhge->nh;
			अवरोध;
		पूर्ण

		अगर (!rc)
			rc = nhge->nh;
	पूर्ण

	वापस rc;
पूर्ण

अटल काष्ठा nexthop *nexthop_select_path_res(काष्ठा nh_group *nhg, पूर्णांक hash)
अणु
	काष्ठा nh_res_table *res_table = rcu_dereference(nhg->res_table);
	u16 bucket_index = hash % res_table->num_nh_buckets;
	काष्ठा nh_res_bucket *bucket;
	काष्ठा nh_grp_entry *nhge;

	/* nexthop_select_path() is expected to वापस a non-शून्य value, so
	 * skip protocol validation and just hand out whatever there is.
	 */
	bucket = &res_table->nh_buckets[bucket_index];
	nh_res_bucket_set_busy(bucket);
	nhge = rcu_dereference(bucket->nh_entry);
	वापस nhge->nh;
पूर्ण

काष्ठा nexthop *nexthop_select_path(काष्ठा nexthop *nh, पूर्णांक hash)
अणु
	काष्ठा nh_group *nhg;

	अगर (!nh->is_group)
		वापस nh;

	nhg = rcu_dereference(nh->nh_grp);
	अगर (nhg->hash_threshold)
		वापस nexthop_select_path_hthr(nhg, hash);
	अन्यथा अगर (nhg->resilient)
		वापस nexthop_select_path_res(nhg, hash);

	/* Unreachable. */
	वापस शून्य;
पूर्ण
EXPORT_SYMBOL_GPL(nexthop_select_path);

पूर्णांक nexthop_क्रम_each_fib6_nh(काष्ठा nexthop *nh,
			     पूर्णांक (*cb)(काष्ठा fib6_nh *nh, व्योम *arg),
			     व्योम *arg)
अणु
	काष्ठा nh_info *nhi;
	पूर्णांक err;

	अगर (nh->is_group) अणु
		काष्ठा nh_group *nhg;
		पूर्णांक i;

		nhg = rcu_dereference_rtnl(nh->nh_grp);
		क्रम (i = 0; i < nhg->num_nh; i++) अणु
			काष्ठा nh_grp_entry *nhge = &nhg->nh_entries[i];

			nhi = rcu_dereference_rtnl(nhge->nh->nh_info);
			err = cb(&nhi->fib6_nh, arg);
			अगर (err)
				वापस err;
		पूर्ण
	पूर्ण अन्यथा अणु
		nhi = rcu_dereference_rtnl(nh->nh_info);
		err = cb(&nhi->fib6_nh, arg);
		अगर (err)
			वापस err;
	पूर्ण

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(nexthop_क्रम_each_fib6_nh);

अटल पूर्णांक check_src_addr(स्थिर काष्ठा in6_addr *saddr,
			  काष्ठा netlink_ext_ack *extack)
अणु
	अगर (!ipv6_addr_any(saddr)) अणु
		NL_SET_ERR_MSG(extack, "IPv6 routes using source address can not use nexthop objects");
		वापस -EINVAL;
	पूर्ण
	वापस 0;
पूर्ण

पूर्णांक fib6_check_nexthop(काष्ठा nexthop *nh, काष्ठा fib6_config *cfg,
		       काष्ठा netlink_ext_ack *extack)
अणु
	काष्ठा nh_info *nhi;
	bool is_fdb_nh;

	/* fib6_src is unique to a fib6_info and limits the ability to cache
	 * routes in fib6_nh within a nexthop that is potentially shared
	 * across multiple fib entries. If the config wants to use source
	 * routing it can not use nexthop objects. mlxsw also करोes not allow
	 * fib6_src on routes.
	 */
	अगर (cfg && check_src_addr(&cfg->fc_src, extack) < 0)
		वापस -EINVAL;

	अगर (nh->is_group) अणु
		काष्ठा nh_group *nhg;

		nhg = rtnl_dereference(nh->nh_grp);
		अगर (nhg->has_v4)
			जाओ no_v4_nh;
		is_fdb_nh = nhg->fdb_nh;
	पूर्ण अन्यथा अणु
		nhi = rtnl_dereference(nh->nh_info);
		अगर (nhi->family == AF_INET)
			जाओ no_v4_nh;
		is_fdb_nh = nhi->fdb_nh;
	पूर्ण

	अगर (is_fdb_nh) अणु
		NL_SET_ERR_MSG(extack, "Route cannot point to a fdb nexthop");
		वापस -EINVAL;
	पूर्ण

	वापस 0;
no_v4_nh:
	NL_SET_ERR_MSG(extack, "IPv6 routes can not use an IPv4 nexthop");
	वापस -EINVAL;
पूर्ण
EXPORT_SYMBOL_GPL(fib6_check_nexthop);

/* अगर existing nexthop has ipv6 routes linked to it, need
 * to verअगरy this new spec works with ipv6
 */
अटल पूर्णांक fib6_check_nh_list(काष्ठा nexthop *old, काष्ठा nexthop *new,
			      काष्ठा netlink_ext_ack *extack)
अणु
	काष्ठा fib6_info *f6i;

	अगर (list_empty(&old->f6i_list))
		वापस 0;

	list_क्रम_each_entry(f6i, &old->f6i_list, nh_list) अणु
		अगर (check_src_addr(&f6i->fib6_src.addr, extack) < 0)
			वापस -EINVAL;
	पूर्ण

	वापस fib6_check_nexthop(new, शून्य, extack);
पूर्ण

अटल पूर्णांक nexthop_check_scope(काष्ठा nh_info *nhi, u8 scope,
			       काष्ठा netlink_ext_ack *extack)
अणु
	अगर (scope == RT_SCOPE_HOST && nhi->fib_nhc.nhc_gw_family) अणु
		NL_SET_ERR_MSG(extack,
			       "Route with host scope can not have a gateway");
		वापस -EINVAL;
	पूर्ण

	अगर (nhi->fib_nhc.nhc_flags & RTNH_F_ONLINK && scope >= RT_SCOPE_LINK) अणु
		NL_SET_ERR_MSG(extack, "Scope mismatch with nexthop");
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

/* Invoked by fib add code to verअगरy nexthop by id is ok with
 * config क्रम prefix; parts of fib_check_nh not करोne when nexthop
 * object is used.
 */
पूर्णांक fib_check_nexthop(काष्ठा nexthop *nh, u8 scope,
		      काष्ठा netlink_ext_ack *extack)
अणु
	काष्ठा nh_info *nhi;
	पूर्णांक err = 0;

	अगर (nh->is_group) अणु
		काष्ठा nh_group *nhg;

		nhg = rtnl_dereference(nh->nh_grp);
		अगर (nhg->fdb_nh) अणु
			NL_SET_ERR_MSG(extack, "Route cannot point to a fdb nexthop");
			err = -EINVAL;
			जाओ out;
		पूर्ण

		अगर (scope == RT_SCOPE_HOST) अणु
			NL_SET_ERR_MSG(extack, "Route with host scope can not have multiple nexthops");
			err = -EINVAL;
			जाओ out;
		पूर्ण

		/* all nexthops in a group have the same scope */
		nhi = rtnl_dereference(nhg->nh_entries[0].nh->nh_info);
		err = nexthop_check_scope(nhi, scope, extack);
	पूर्ण अन्यथा अणु
		nhi = rtnl_dereference(nh->nh_info);
		अगर (nhi->fdb_nh) अणु
			NL_SET_ERR_MSG(extack, "Route cannot point to a fdb nexthop");
			err = -EINVAL;
			जाओ out;
		पूर्ण
		err = nexthop_check_scope(nhi, scope, extack);
	पूर्ण

out:
	वापस err;
पूर्ण

अटल पूर्णांक fib_check_nh_list(काष्ठा nexthop *old, काष्ठा nexthop *new,
			     काष्ठा netlink_ext_ack *extack)
अणु
	काष्ठा fib_info *fi;

	list_क्रम_each_entry(fi, &old->fi_list, nh_list) अणु
		पूर्णांक err;

		err = fib_check_nexthop(new, fi->fib_scope, extack);
		अगर (err)
			वापस err;
	पूर्ण
	वापस 0;
पूर्ण

अटल bool nh_res_nhge_is_balanced(स्थिर काष्ठा nh_grp_entry *nhge)
अणु
	वापस nhge->res.count_buckets == nhge->res.wants_buckets;
पूर्ण

अटल bool nh_res_nhge_is_ow(स्थिर काष्ठा nh_grp_entry *nhge)
अणु
	वापस nhge->res.count_buckets > nhge->res.wants_buckets;
पूर्ण

अटल bool nh_res_nhge_is_uw(स्थिर काष्ठा nh_grp_entry *nhge)
अणु
	वापस nhge->res.count_buckets < nhge->res.wants_buckets;
पूर्ण

अटल bool nh_res_table_is_balanced(स्थिर काष्ठा nh_res_table *res_table)
अणु
	वापस list_empty(&res_table->uw_nh_entries);
पूर्ण

अटल व्योम nh_res_bucket_unset_nh(काष्ठा nh_res_bucket *bucket)
अणु
	काष्ठा nh_grp_entry *nhge;

	अगर (bucket->occupied) अणु
		nhge = nh_res_dereference(bucket->nh_entry);
		nhge->res.count_buckets--;
		bucket->occupied = false;
	पूर्ण
पूर्ण

अटल व्योम nh_res_bucket_set_nh(काष्ठा nh_res_bucket *bucket,
				 काष्ठा nh_grp_entry *nhge)
अणु
	nh_res_bucket_unset_nh(bucket);

	bucket->occupied = true;
	rcu_assign_poपूर्णांकer(bucket->nh_entry, nhge);
	nhge->res.count_buckets++;
पूर्ण

अटल bool nh_res_bucket_should_migrate(काष्ठा nh_res_table *res_table,
					 काष्ठा nh_res_bucket *bucket,
					 अचिन्हित दीर्घ *deadline, bool *क्रमce)
अणु
	अचिन्हित दीर्घ now = jअगरfies;
	काष्ठा nh_grp_entry *nhge;
	अचिन्हित दीर्घ idle_poपूर्णांक;

	अगर (!bucket->occupied) अणु
		/* The bucket is not occupied, its NHGE poपूर्णांकer is either
		 * शून्य or obsolete. We _have to_ migrate: set क्रमce.
		 */
		*क्रमce = true;
		वापस true;
	पूर्ण

	nhge = nh_res_dereference(bucket->nh_entry);

	/* If the bucket is populated by an underweight or balanced
	 * nexthop, करो not migrate.
	 */
	अगर (!nh_res_nhge_is_ow(nhge))
		वापस false;

	/* At this poपूर्णांक we know that the bucket is populated with an
	 * overweight nexthop. It needs to be migrated to a new nexthop अगर
	 * the idle समयr of unbalanced समयr expired.
	 */

	idle_poपूर्णांक = nh_res_bucket_idle_poपूर्णांक(res_table, bucket, now);
	अगर (समय_after_eq(now, idle_poपूर्णांक)) अणु
		/* The bucket is idle. We _can_ migrate: unset क्रमce. */
		*क्रमce = false;
		वापस true;
	पूर्ण

	/* Unbalanced समयr of 0 means "never force". */
	अगर (res_table->unbalanced_समयr) अणु
		अचिन्हित दीर्घ unb_poपूर्णांक;

		unb_poपूर्णांक = nh_res_table_unb_poपूर्णांक(res_table);
		अगर (समय_after(now, unb_poपूर्णांक)) अणु
			/* The bucket is not idle, but the unbalanced समयr
			 * expired. We _can_ migrate, but set क्रमce anyway,
			 * so that drivers know to ignore activity reports
			 * from the HW.
			 */
			*क्रमce = true;
			वापस true;
		पूर्ण

		nh_res_समय_set_deadline(unb_poपूर्णांक, deadline);
	पूर्ण

	nh_res_समय_set_deadline(idle_poपूर्णांक, deadline);
	वापस false;
पूर्ण

अटल bool nh_res_bucket_migrate(काष्ठा nh_res_table *res_table,
				  u16 bucket_index, bool notअगरy,
				  bool notअगरy_nl, bool क्रमce)
अणु
	काष्ठा nh_res_bucket *bucket = &res_table->nh_buckets[bucket_index];
	काष्ठा nh_grp_entry *new_nhge;
	काष्ठा netlink_ext_ack extack;
	पूर्णांक err;

	new_nhge = list_first_entry_or_null(&res_table->uw_nh_entries,
					    काष्ठा nh_grp_entry,
					    res.uw_nh_entry);
	अगर (WARN_ON_ONCE(!new_nhge))
		/* If this function is called, "bucket" is either not
		 * occupied, or it beदीर्घs to a next hop that is
		 * overweight. In either हाल, there ought to be a
		 * corresponding underweight next hop.
		 */
		वापस false;

	अगर (notअगरy) अणु
		काष्ठा nh_grp_entry *old_nhge;

		old_nhge = nh_res_dereference(bucket->nh_entry);
		err = call_nexthop_res_bucket_notअगरiers(res_table->net,
							res_table->nhg_id,
							bucket_index, क्रमce,
							old_nhge->nh,
							new_nhge->nh, &extack);
		अगर (err) अणु
			pr_err_ratelimited("%s\n", extack._msg);
			अगर (!क्रमce)
				वापस false;
			/* It is not possible to veto a क्रमced replacement, so
			 * just clear the hardware flags from the nexthop
			 * bucket to indicate to user space that this bucket is
			 * not correctly populated in hardware.
			 */
			bucket->nh_flags &= ~(RTNH_F_OFFLOAD | RTNH_F_TRAP);
		पूर्ण
	पूर्ण

	nh_res_bucket_set_nh(bucket, new_nhge);
	nh_res_bucket_set_idle(res_table, bucket);

	अगर (notअगरy_nl)
		nexthop_bucket_notअगरy(res_table, bucket_index);

	अगर (nh_res_nhge_is_balanced(new_nhge))
		list_del(&new_nhge->res.uw_nh_entry);
	वापस true;
पूर्ण

#घोषणा NH_RES_UPKEEP_DW_MINIMUM_INTERVAL (HZ / 2)

अटल व्योम nh_res_table_upkeep(काष्ठा nh_res_table *res_table,
				bool notअगरy, bool notअगरy_nl)
अणु
	अचिन्हित दीर्घ now = jअगरfies;
	अचिन्हित दीर्घ deadline;
	u16 i;

	/* Deadline is the next समय that upkeep should be run. It is the
	 * earliest समय at which one of the buckets might be migrated.
	 * Start at the most pessimistic estimate: either unbalanced_समयr
	 * from now, or अगर there is none, idle_समयr from now. For each
	 * encountered समय poपूर्णांक, call nh_res_समय_set_deadline() to
	 * refine the estimate.
	 */
	अगर (res_table->unbalanced_समयr)
		deadline = now + res_table->unbalanced_समयr;
	अन्यथा
		deadline = now + res_table->idle_समयr;

	क्रम (i = 0; i < res_table->num_nh_buckets; i++) अणु
		काष्ठा nh_res_bucket *bucket = &res_table->nh_buckets[i];
		bool क्रमce;

		अगर (nh_res_bucket_should_migrate(res_table, bucket,
						 &deadline, &क्रमce)) अणु
			अगर (!nh_res_bucket_migrate(res_table, i, notअगरy,
						   notअगरy_nl, क्रमce)) अणु
				अचिन्हित दीर्घ idle_poपूर्णांक;

				/* A driver can override the migration
				 * decision अगर the HW reports that the
				 * bucket is actually not idle. Thereक्रमe
				 * remark the bucket as busy again and
				 * update the deadline.
				 */
				nh_res_bucket_set_busy(bucket);
				idle_poपूर्णांक = nh_res_bucket_idle_poपूर्णांक(res_table,
								      bucket,
								      now);
				nh_res_समय_set_deadline(idle_poपूर्णांक, &deadline);
			पूर्ण
		पूर्ण
	पूर्ण

	/* If the group is still unbalanced, schedule the next upkeep to
	 * either the deadline computed above, or the minimum deadline,
	 * whichever comes later.
	 */
	अगर (!nh_res_table_is_balanced(res_table)) अणु
		अचिन्हित दीर्घ now = jअगरfies;
		अचिन्हित दीर्घ min_deadline;

		min_deadline = now + NH_RES_UPKEEP_DW_MINIMUM_INTERVAL;
		अगर (समय_beक्रमe(deadline, min_deadline))
			deadline = min_deadline;

		queue_delayed_work(प्रणाली_घातer_efficient_wq,
				   &res_table->upkeep_dw, deadline - now);
	पूर्ण
पूर्ण

अटल व्योम nh_res_table_upkeep_dw(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा delayed_work *dw = to_delayed_work(work);
	काष्ठा nh_res_table *res_table;

	res_table = container_of(dw, काष्ठा nh_res_table, upkeep_dw);
	nh_res_table_upkeep(res_table, true, true);
पूर्ण

अटल व्योम nh_res_table_cancel_upkeep(काष्ठा nh_res_table *res_table)
अणु
	cancel_delayed_work_sync(&res_table->upkeep_dw);
पूर्ण

अटल व्योम nh_res_group_rebalance(काष्ठा nh_group *nhg,
				   काष्ठा nh_res_table *res_table)
अणु
	पूर्णांक prev_upper_bound = 0;
	पूर्णांक total = 0;
	पूर्णांक w = 0;
	पूर्णांक i;

	INIT_LIST_HEAD(&res_table->uw_nh_entries);

	क्रम (i = 0; i < nhg->num_nh; ++i)
		total += nhg->nh_entries[i].weight;

	क्रम (i = 0; i < nhg->num_nh; ++i) अणु
		काष्ठा nh_grp_entry *nhge = &nhg->nh_entries[i];
		पूर्णांक upper_bound;

		w += nhge->weight;
		upper_bound = DIV_ROUND_CLOSEST(res_table->num_nh_buckets * w,
						total);
		nhge->res.wants_buckets = upper_bound - prev_upper_bound;
		prev_upper_bound = upper_bound;

		अगर (nh_res_nhge_is_uw(nhge)) अणु
			अगर (list_empty(&res_table->uw_nh_entries))
				res_table->unbalanced_since = jअगरfies;
			list_add(&nhge->res.uw_nh_entry,
				 &res_table->uw_nh_entries);
		पूर्ण
	पूर्ण
पूर्ण

/* Migrate buckets in res_table so that they reference NHGE's from NHG with
 * the right NH ID. Set those buckets that करो not have a corresponding NHGE
 * entry in NHG as not occupied.
 */
अटल व्योम nh_res_table_migrate_buckets(काष्ठा nh_res_table *res_table,
					 काष्ठा nh_group *nhg)
अणु
	u16 i;

	क्रम (i = 0; i < res_table->num_nh_buckets; i++) अणु
		काष्ठा nh_res_bucket *bucket = &res_table->nh_buckets[i];
		u32 id = rtnl_dereference(bucket->nh_entry)->nh->id;
		bool found = false;
		पूर्णांक j;

		क्रम (j = 0; j < nhg->num_nh; j++) अणु
			काष्ठा nh_grp_entry *nhge = &nhg->nh_entries[j];

			अगर (nhge->nh->id == id) अणु
				nh_res_bucket_set_nh(bucket, nhge);
				found = true;
				अवरोध;
			पूर्ण
		पूर्ण

		अगर (!found)
			nh_res_bucket_unset_nh(bucket);
	पूर्ण
पूर्ण

अटल व्योम replace_nexthop_grp_res(काष्ठा nh_group *oldg,
				    काष्ठा nh_group *newg)
अणु
	/* For NH group replacement, the new NHG might only have a stub
	 * hash table with 0 buckets, because the number of buckets was not
	 * specअगरied. For NH removal, oldg and newg both reference the same
	 * res_table. So in any हाल, in the following, we want to work
	 * with oldg->res_table.
	 */
	काष्ठा nh_res_table *old_res_table = rtnl_dereference(oldg->res_table);
	अचिन्हित दीर्घ prev_unbalanced_since = old_res_table->unbalanced_since;
	bool prev_has_uw = !list_empty(&old_res_table->uw_nh_entries);

	nh_res_table_cancel_upkeep(old_res_table);
	nh_res_table_migrate_buckets(old_res_table, newg);
	nh_res_group_rebalance(newg, old_res_table);
	अगर (prev_has_uw && !list_empty(&old_res_table->uw_nh_entries))
		old_res_table->unbalanced_since = prev_unbalanced_since;
	nh_res_table_upkeep(old_res_table, true, false);
पूर्ण

अटल व्योम nh_hthr_group_rebalance(काष्ठा nh_group *nhg)
अणु
	पूर्णांक total = 0;
	पूर्णांक w = 0;
	पूर्णांक i;

	क्रम (i = 0; i < nhg->num_nh; ++i)
		total += nhg->nh_entries[i].weight;

	क्रम (i = 0; i < nhg->num_nh; ++i) अणु
		काष्ठा nh_grp_entry *nhge = &nhg->nh_entries[i];
		पूर्णांक upper_bound;

		w += nhge->weight;
		upper_bound = DIV_ROUND_CLOSEST_ULL((u64)w << 31, total) - 1;
		atomic_set(&nhge->hthr.upper_bound, upper_bound);
	पूर्ण
पूर्ण

अटल व्योम हटाओ_nh_grp_entry(काष्ठा net *net, काष्ठा nh_grp_entry *nhge,
				काष्ठा nl_info *nlinfo)
अणु
	काष्ठा nh_grp_entry *nhges, *new_nhges;
	काष्ठा nexthop *nhp = nhge->nh_parent;
	काष्ठा netlink_ext_ack extack;
	काष्ठा nexthop *nh = nhge->nh;
	काष्ठा nh_group *nhg, *newg;
	पूर्णांक i, j, err;

	WARN_ON(!nh);

	nhg = rtnl_dereference(nhp->nh_grp);
	newg = nhg->spare;

	/* last entry, keep it visible and हटाओ the parent */
	अगर (nhg->num_nh == 1) अणु
		हटाओ_nexthop(net, nhp, nlinfo);
		वापस;
	पूर्ण

	newg->has_v4 = false;
	newg->is_multipath = nhg->is_multipath;
	newg->hash_threshold = nhg->hash_threshold;
	newg->resilient = nhg->resilient;
	newg->fdb_nh = nhg->fdb_nh;
	newg->num_nh = nhg->num_nh;

	/* copy old entries to new except the one getting हटाओd */
	nhges = nhg->nh_entries;
	new_nhges = newg->nh_entries;
	क्रम (i = 0, j = 0; i < nhg->num_nh; ++i) अणु
		काष्ठा nh_info *nhi;

		/* current nexthop getting हटाओd */
		अगर (nhg->nh_entries[i].nh == nh) अणु
			newg->num_nh--;
			जारी;
		पूर्ण

		nhi = rtnl_dereference(nhges[i].nh->nh_info);
		अगर (nhi->family == AF_INET)
			newg->has_v4 = true;

		list_del(&nhges[i].nh_list);
		new_nhges[j].nh_parent = nhges[i].nh_parent;
		new_nhges[j].nh = nhges[i].nh;
		new_nhges[j].weight = nhges[i].weight;
		list_add(&new_nhges[j].nh_list, &new_nhges[j].nh->grp_list);
		j++;
	पूर्ण

	अगर (newg->hash_threshold)
		nh_hthr_group_rebalance(newg);
	अन्यथा अगर (newg->resilient)
		replace_nexthop_grp_res(nhg, newg);

	rcu_assign_poपूर्णांकer(nhp->nh_grp, newg);

	list_del(&nhge->nh_list);
	nexthop_put(nhge->nh);

	/* Removal of a NH from a resilient group is notअगरied through
	 * bucket notअगरications.
	 */
	अगर (newg->hash_threshold) अणु
		err = call_nexthop_notअगरiers(net, NEXTHOP_EVENT_REPLACE, nhp,
					     &extack);
		अगर (err)
			pr_err("%s\n", extack._msg);
	पूर्ण

	अगर (nlinfo)
		nexthop_notअगरy(RTM_NEWNEXTHOP, nhp, nlinfo);
पूर्ण

अटल व्योम हटाओ_nexthop_from_groups(काष्ठा net *net, काष्ठा nexthop *nh,
				       काष्ठा nl_info *nlinfo)
अणु
	काष्ठा nh_grp_entry *nhge, *पंचांगp;

	list_क्रम_each_entry_safe(nhge, पंचांगp, &nh->grp_list, nh_list)
		हटाओ_nh_grp_entry(net, nhge, nlinfo);

	/* make sure all see the newly published array beक्रमe releasing rtnl */
	synchronize_net();
पूर्ण

अटल व्योम हटाओ_nexthop_group(काष्ठा nexthop *nh, काष्ठा nl_info *nlinfo)
अणु
	काष्ठा nh_group *nhg = rcu_dereference_rtnl(nh->nh_grp);
	काष्ठा nh_res_table *res_table;
	पूर्णांक i, num_nh = nhg->num_nh;

	क्रम (i = 0; i < num_nh; ++i) अणु
		काष्ठा nh_grp_entry *nhge = &nhg->nh_entries[i];

		अगर (WARN_ON(!nhge->nh))
			जारी;

		list_del_init(&nhge->nh_list);
	पूर्ण

	अगर (nhg->resilient) अणु
		res_table = rtnl_dereference(nhg->res_table);
		nh_res_table_cancel_upkeep(res_table);
	पूर्ण
पूर्ण

/* not called क्रम nexthop replace */
अटल व्योम __हटाओ_nexthop_fib(काष्ठा net *net, काष्ठा nexthop *nh)
अणु
	काष्ठा fib6_info *f6i, *पंचांगp;
	bool करो_flush = false;
	काष्ठा fib_info *fi;

	list_क्रम_each_entry(fi, &nh->fi_list, nh_list) अणु
		fi->fib_flags |= RTNH_F_DEAD;
		करो_flush = true;
	पूर्ण
	अगर (करो_flush)
		fib_flush(net);

	/* ip6_del_rt हटाओs the entry from this list hence the _safe */
	list_क्रम_each_entry_safe(f6i, पंचांगp, &nh->f6i_list, nh_list) अणु
		/* __ip6_del_rt करोes a release, so करो a hold here */
		fib6_info_hold(f6i);
		ipv6_stub->ip6_del_rt(net, f6i,
				      !net->ipv4.sysctl_nexthop_compat_mode);
	पूर्ण
पूर्ण

अटल व्योम __हटाओ_nexthop(काष्ठा net *net, काष्ठा nexthop *nh,
			     काष्ठा nl_info *nlinfo)
अणु
	__हटाओ_nexthop_fib(net, nh);

	अगर (nh->is_group) अणु
		हटाओ_nexthop_group(nh, nlinfo);
	पूर्ण अन्यथा अणु
		काष्ठा nh_info *nhi;

		nhi = rtnl_dereference(nh->nh_info);
		अगर (nhi->fib_nhc.nhc_dev)
			hlist_del(&nhi->dev_hash);

		हटाओ_nexthop_from_groups(net, nh, nlinfo);
	पूर्ण
पूर्ण

अटल व्योम हटाओ_nexthop(काष्ठा net *net, काष्ठा nexthop *nh,
			   काष्ठा nl_info *nlinfo)
अणु
	call_nexthop_notअगरiers(net, NEXTHOP_EVENT_DEL, nh, शून्य);

	/* हटाओ from the tree */
	rb_erase(&nh->rb_node, &net->nexthop.rb_root);

	अगर (nlinfo)
		nexthop_notअगरy(RTM_DELNEXTHOP, nh, nlinfo);

	__हटाओ_nexthop(net, nh, nlinfo);
	nh_base_seq_inc(net);

	nexthop_put(nh);
पूर्ण

/* अगर any FIB entries reference this nexthop, any dst entries
 * need to be regenerated
 */
अटल व्योम nh_rt_cache_flush(काष्ठा net *net, काष्ठा nexthop *nh)
अणु
	काष्ठा fib6_info *f6i;

	अगर (!list_empty(&nh->fi_list))
		rt_cache_flush(net);

	list_क्रम_each_entry(f6i, &nh->f6i_list, nh_list)
		ipv6_stub->fib6_update_sernum(net, f6i);
पूर्ण

अटल पूर्णांक replace_nexthop_grp(काष्ठा net *net, काष्ठा nexthop *old,
			       काष्ठा nexthop *new, स्थिर काष्ठा nh_config *cfg,
			       काष्ठा netlink_ext_ack *extack)
अणु
	काष्ठा nh_res_table *पंचांगp_table = शून्य;
	काष्ठा nh_res_table *new_res_table;
	काष्ठा nh_res_table *old_res_table;
	काष्ठा nh_group *oldg, *newg;
	पूर्णांक i, err;

	अगर (!new->is_group) अणु
		NL_SET_ERR_MSG(extack, "Can not replace a nexthop group with a nexthop.");
		वापस -EINVAL;
	पूर्ण

	oldg = rtnl_dereference(old->nh_grp);
	newg = rtnl_dereference(new->nh_grp);

	अगर (newg->hash_threshold != oldg->hash_threshold) अणु
		NL_SET_ERR_MSG(extack, "Can not replace a nexthop group with one of a different type.");
		वापस -EINVAL;
	पूर्ण

	अगर (newg->hash_threshold) अणु
		err = call_nexthop_notअगरiers(net, NEXTHOP_EVENT_REPLACE, new,
					     extack);
		अगर (err)
			वापस err;
	पूर्ण अन्यथा अगर (newg->resilient) अणु
		new_res_table = rtnl_dereference(newg->res_table);
		old_res_table = rtnl_dereference(oldg->res_table);

		/* Accept अगर num_nh_buckets was not given, but अगर it was
		 * given, demand that the value be correct.
		 */
		अगर (cfg->nh_grp_res_has_num_buckets &&
		    cfg->nh_grp_res_num_buckets !=
		    old_res_table->num_nh_buckets) अणु
			NL_SET_ERR_MSG(extack, "Can not change number of buckets of a resilient nexthop group.");
			वापस -EINVAL;
		पूर्ण

		/* Emit a pre-replace notअगरication so that listeners could veto
		 * a potentially unsupported configuration. Otherwise,
		 * inभागidual bucket replacement notअगरications would need to be
		 * vetoed, which is something that should only happen अगर the
		 * bucket is currently active.
		 */
		err = call_nexthop_res_table_notअगरiers(net, new, extack);
		अगर (err)
			वापस err;

		अगर (cfg->nh_grp_res_has_idle_समयr)
			old_res_table->idle_समयr = cfg->nh_grp_res_idle_समयr;
		अगर (cfg->nh_grp_res_has_unbalanced_समयr)
			old_res_table->unbalanced_समयr =
				cfg->nh_grp_res_unbalanced_समयr;

		replace_nexthop_grp_res(oldg, newg);

		पंचांगp_table = new_res_table;
		rcu_assign_poपूर्णांकer(newg->res_table, old_res_table);
		rcu_assign_poपूर्णांकer(newg->spare->res_table, old_res_table);
	पूर्ण

	/* update parents - used by nexthop code क्रम cleanup */
	क्रम (i = 0; i < newg->num_nh; i++)
		newg->nh_entries[i].nh_parent = old;

	rcu_assign_poपूर्णांकer(old->nh_grp, newg);

	अगर (newg->resilient) अणु
		rcu_assign_poपूर्णांकer(oldg->res_table, पंचांगp_table);
		rcu_assign_poपूर्णांकer(oldg->spare->res_table, पंचांगp_table);
	पूर्ण

	क्रम (i = 0; i < oldg->num_nh; i++)
		oldg->nh_entries[i].nh_parent = new;

	rcu_assign_poपूर्णांकer(new->nh_grp, oldg);

	वापस 0;
पूर्ण

अटल व्योम nh_group_v4_update(काष्ठा nh_group *nhg)
अणु
	काष्ठा nh_grp_entry *nhges;
	bool has_v4 = false;
	पूर्णांक i;

	nhges = nhg->nh_entries;
	क्रम (i = 0; i < nhg->num_nh; i++) अणु
		काष्ठा nh_info *nhi;

		nhi = rtnl_dereference(nhges[i].nh->nh_info);
		अगर (nhi->family == AF_INET)
			has_v4 = true;
	पूर्ण
	nhg->has_v4 = has_v4;
पूर्ण

अटल पूर्णांक replace_nexthop_single_notअगरy_res(काष्ठा net *net,
					     काष्ठा nh_res_table *res_table,
					     काष्ठा nexthop *old,
					     काष्ठा nh_info *oldi,
					     काष्ठा nh_info *newi,
					     काष्ठा netlink_ext_ack *extack)
अणु
	u32 nhg_id = res_table->nhg_id;
	पूर्णांक err;
	u16 i;

	क्रम (i = 0; i < res_table->num_nh_buckets; i++) अणु
		काष्ठा nh_res_bucket *bucket = &res_table->nh_buckets[i];
		काष्ठा nh_grp_entry *nhge;

		nhge = rtnl_dereference(bucket->nh_entry);
		अगर (nhge->nh == old) अणु
			err = __call_nexthop_res_bucket_notअगरiers(net, nhg_id,
								  i, true,
								  oldi, newi,
								  extack);
			अगर (err)
				जाओ err_notअगरy;
		पूर्ण
	पूर्ण

	वापस 0;

err_notअगरy:
	जबतक (i-- > 0) अणु
		काष्ठा nh_res_bucket *bucket = &res_table->nh_buckets[i];
		काष्ठा nh_grp_entry *nhge;

		nhge = rtnl_dereference(bucket->nh_entry);
		अगर (nhge->nh == old)
			__call_nexthop_res_bucket_notअगरiers(net, nhg_id, i,
							    true, newi, oldi,
							    extack);
	पूर्ण
	वापस err;
पूर्ण

अटल पूर्णांक replace_nexthop_single_notअगरy(काष्ठा net *net,
					 काष्ठा nexthop *group_nh,
					 काष्ठा nexthop *old,
					 काष्ठा nh_info *oldi,
					 काष्ठा nh_info *newi,
					 काष्ठा netlink_ext_ack *extack)
अणु
	काष्ठा nh_group *nhg = rtnl_dereference(group_nh->nh_grp);
	काष्ठा nh_res_table *res_table;

	अगर (nhg->hash_threshold) अणु
		वापस call_nexthop_notअगरiers(net, NEXTHOP_EVENT_REPLACE,
					      group_nh, extack);
	पूर्ण अन्यथा अगर (nhg->resilient) अणु
		res_table = rtnl_dereference(nhg->res_table);
		वापस replace_nexthop_single_notअगरy_res(net, res_table,
							 old, oldi, newi,
							 extack);
	पूर्ण

	वापस -EINVAL;
पूर्ण

अटल पूर्णांक replace_nexthop_single(काष्ठा net *net, काष्ठा nexthop *old,
				  काष्ठा nexthop *new,
				  काष्ठा netlink_ext_ack *extack)
अणु
	u8 old_protocol, old_nh_flags;
	काष्ठा nh_info *oldi, *newi;
	काष्ठा nh_grp_entry *nhge;
	पूर्णांक err;

	अगर (new->is_group) अणु
		NL_SET_ERR_MSG(extack, "Can not replace a nexthop with a nexthop group.");
		वापस -EINVAL;
	पूर्ण

	err = call_nexthop_notअगरiers(net, NEXTHOP_EVENT_REPLACE, new, extack);
	अगर (err)
		वापस err;

	/* Hardware flags were set on 'old' as 'new' is not in the red-black
	 * tree. Thereक्रमe, inherit the flags from 'old' to 'new'.
	 */
	new->nh_flags |= old->nh_flags & (RTNH_F_OFFLOAD | RTNH_F_TRAP);

	oldi = rtnl_dereference(old->nh_info);
	newi = rtnl_dereference(new->nh_info);

	newi->nh_parent = old;
	oldi->nh_parent = new;

	old_protocol = old->protocol;
	old_nh_flags = old->nh_flags;

	old->protocol = new->protocol;
	old->nh_flags = new->nh_flags;

	rcu_assign_poपूर्णांकer(old->nh_info, newi);
	rcu_assign_poपूर्णांकer(new->nh_info, oldi);

	/* Send a replace notअगरication क्रम all the groups using the nexthop. */
	list_क्रम_each_entry(nhge, &old->grp_list, nh_list) अणु
		काष्ठा nexthop *nhp = nhge->nh_parent;

		err = replace_nexthop_single_notअगरy(net, nhp, old, oldi, newi,
						    extack);
		अगर (err)
			जाओ err_notअगरy;
	पूर्ण

	/* When replacing an IPv4 nexthop with an IPv6 nexthop, potentially
	 * update IPv4 indication in all the groups using the nexthop.
	 */
	अगर (oldi->family == AF_INET && newi->family == AF_INET6) अणु
		list_क्रम_each_entry(nhge, &old->grp_list, nh_list) अणु
			काष्ठा nexthop *nhp = nhge->nh_parent;
			काष्ठा nh_group *nhg;

			nhg = rtnl_dereference(nhp->nh_grp);
			nh_group_v4_update(nhg);
		पूर्ण
	पूर्ण

	वापस 0;

err_notअगरy:
	rcu_assign_poपूर्णांकer(new->nh_info, newi);
	rcu_assign_poपूर्णांकer(old->nh_info, oldi);
	old->nh_flags = old_nh_flags;
	old->protocol = old_protocol;
	oldi->nh_parent = old;
	newi->nh_parent = new;
	list_क्रम_each_entry_जारी_reverse(nhge, &old->grp_list, nh_list) अणु
		काष्ठा nexthop *nhp = nhge->nh_parent;

		replace_nexthop_single_notअगरy(net, nhp, old, newi, oldi, शून्य);
	पूर्ण
	call_nexthop_notअगरiers(net, NEXTHOP_EVENT_REPLACE, old, extack);
	वापस err;
पूर्ण

अटल व्योम __nexthop_replace_notअगरy(काष्ठा net *net, काष्ठा nexthop *nh,
				     काष्ठा nl_info *info)
अणु
	काष्ठा fib6_info *f6i;

	अगर (!list_empty(&nh->fi_list)) अणु
		काष्ठा fib_info *fi;

		/* expectation is a few fib_info per nexthop and then
		 * a lot of routes per fib_info. So mark the fib_info
		 * and then walk the fib tables once
		 */
		list_क्रम_each_entry(fi, &nh->fi_list, nh_list)
			fi->nh_updated = true;

		fib_info_notअगरy_update(net, info);

		list_क्रम_each_entry(fi, &nh->fi_list, nh_list)
			fi->nh_updated = false;
	पूर्ण

	list_क्रम_each_entry(f6i, &nh->f6i_list, nh_list)
		ipv6_stub->fib6_rt_update(net, f6i, info);
पूर्ण

/* send RTM_NEWROUTE with REPLACE flag set क्रम all FIB entries
 * linked to this nexthop and क्रम all groups that the nexthop
 * is a member of
 */
अटल व्योम nexthop_replace_notअगरy(काष्ठा net *net, काष्ठा nexthop *nh,
				   काष्ठा nl_info *info)
अणु
	काष्ठा nh_grp_entry *nhge;

	__nexthop_replace_notअगरy(net, nh, info);

	list_क्रम_each_entry(nhge, &nh->grp_list, nh_list)
		__nexthop_replace_notअगरy(net, nhge->nh_parent, info);
पूर्ण

अटल पूर्णांक replace_nexthop(काष्ठा net *net, काष्ठा nexthop *old,
			   काष्ठा nexthop *new, स्थिर काष्ठा nh_config *cfg,
			   काष्ठा netlink_ext_ack *extack)
अणु
	bool new_is_reject = false;
	काष्ठा nh_grp_entry *nhge;
	पूर्णांक err;

	/* check that existing FIB entries are ok with the
	 * new nexthop definition
	 */
	err = fib_check_nh_list(old, new, extack);
	अगर (err)
		वापस err;

	err = fib6_check_nh_list(old, new, extack);
	अगर (err)
		वापस err;

	अगर (!new->is_group) अणु
		काष्ठा nh_info *nhi = rtnl_dereference(new->nh_info);

		new_is_reject = nhi->reject_nh;
	पूर्ण

	list_क्रम_each_entry(nhge, &old->grp_list, nh_list) अणु
		/* अगर new nexthop is a blackhole, any groups using this
		 * nexthop cannot have more than 1 path
		 */
		अगर (new_is_reject &&
		    nexthop_num_path(nhge->nh_parent) > 1) अणु
			NL_SET_ERR_MSG(extack, "Blackhole nexthop can not be a member of a group with more than one path");
			वापस -EINVAL;
		पूर्ण

		err = fib_check_nh_list(nhge->nh_parent, new, extack);
		अगर (err)
			वापस err;

		err = fib6_check_nh_list(nhge->nh_parent, new, extack);
		अगर (err)
			वापस err;
	पूर्ण

	अगर (old->is_group)
		err = replace_nexthop_grp(net, old, new, cfg, extack);
	अन्यथा
		err = replace_nexthop_single(net, old, new, extack);

	अगर (!err) अणु
		nh_rt_cache_flush(net, old);

		__हटाओ_nexthop(net, new, शून्य);
		nexthop_put(new);
	पूर्ण

	वापस err;
पूर्ण

/* called with rtnl_lock held */
अटल पूर्णांक insert_nexthop(काष्ठा net *net, काष्ठा nexthop *new_nh,
			  काष्ठा nh_config *cfg, काष्ठा netlink_ext_ack *extack)
अणु
	काष्ठा rb_node **pp, *parent = शून्य, *next;
	काष्ठा rb_root *root = &net->nexthop.rb_root;
	bool replace = !!(cfg->nlflags & NLM_F_REPLACE);
	bool create = !!(cfg->nlflags & NLM_F_CREATE);
	u32 new_id = new_nh->id;
	पूर्णांक replace_notअगरy = 0;
	पूर्णांक rc = -EEXIST;

	pp = &root->rb_node;
	जबतक (1) अणु
		काष्ठा nexthop *nh;

		next = *pp;
		अगर (!next)
			अवरोध;

		parent = next;

		nh = rb_entry(parent, काष्ठा nexthop, rb_node);
		अगर (new_id < nh->id) अणु
			pp = &next->rb_left;
		पूर्ण अन्यथा अगर (new_id > nh->id) अणु
			pp = &next->rb_right;
		पूर्ण अन्यथा अगर (replace) अणु
			rc = replace_nexthop(net, nh, new_nh, cfg, extack);
			अगर (!rc) अणु
				new_nh = nh; /* send notअगरication with old nh */
				replace_notअगरy = 1;
			पूर्ण
			जाओ out;
		पूर्ण अन्यथा अणु
			/* id alपढ़ोy exists and not a replace */
			जाओ out;
		पूर्ण
	पूर्ण

	अगर (replace && !create) अणु
		NL_SET_ERR_MSG(extack, "Replace specified without create and no entry exists");
		rc = -ENOENT;
		जाओ out;
	पूर्ण

	अगर (new_nh->is_group) अणु
		काष्ठा nh_group *nhg = rtnl_dereference(new_nh->nh_grp);
		काष्ठा nh_res_table *res_table;

		अगर (nhg->resilient) अणु
			res_table = rtnl_dereference(nhg->res_table);

			/* Not passing the number of buckets is OK when
			 * replacing, but not when creating a new group.
			 */
			अगर (!cfg->nh_grp_res_has_num_buckets) अणु
				NL_SET_ERR_MSG(extack, "Number of buckets not specified for nexthop group insertion");
				rc = -EINVAL;
				जाओ out;
			पूर्ण

			nh_res_group_rebalance(nhg, res_table);

			/* Do not send bucket notअगरications, we करो full
			 * notअगरication below.
			 */
			nh_res_table_upkeep(res_table, false, false);
		पूर्ण
	पूर्ण

	rb_link_node_rcu(&new_nh->rb_node, parent, pp);
	rb_insert_color(&new_nh->rb_node, root);

	/* The initial insertion is a full notअगरication क्रम hash-threshold as
	 * well as resilient groups.
	 */
	rc = call_nexthop_notअगरiers(net, NEXTHOP_EVENT_REPLACE, new_nh, extack);
	अगर (rc)
		rb_erase(&new_nh->rb_node, &net->nexthop.rb_root);

out:
	अगर (!rc) अणु
		nh_base_seq_inc(net);
		nexthop_notअगरy(RTM_NEWNEXTHOP, new_nh, &cfg->nlinfo);
		अगर (replace_notअगरy && net->ipv4.sysctl_nexthop_compat_mode)
			nexthop_replace_notअगरy(net, new_nh, &cfg->nlinfo);
	पूर्ण

	वापस rc;
पूर्ण

/* rtnl */
/* हटाओ all nexthops tied to a device being deleted */
अटल व्योम nexthop_flush_dev(काष्ठा net_device *dev, अचिन्हित दीर्घ event)
अणु
	अचिन्हित पूर्णांक hash = nh_dev_hashfn(dev->अगरindex);
	काष्ठा net *net = dev_net(dev);
	काष्ठा hlist_head *head = &net->nexthop.devhash[hash];
	काष्ठा hlist_node *n;
	काष्ठा nh_info *nhi;

	hlist_क्रम_each_entry_safe(nhi, n, head, dev_hash) अणु
		अगर (nhi->fib_nhc.nhc_dev != dev)
			जारी;

		अगर (nhi->reject_nh &&
		    (event == NETDEV_DOWN || event == NETDEV_CHANGE))
			जारी;

		हटाओ_nexthop(net, nhi->nh_parent, शून्य);
	पूर्ण
पूर्ण

/* rtnl; called when net namespace is deleted */
अटल व्योम flush_all_nexthops(काष्ठा net *net)
अणु
	काष्ठा rb_root *root = &net->nexthop.rb_root;
	काष्ठा rb_node *node;
	काष्ठा nexthop *nh;

	जबतक ((node = rb_first(root))) अणु
		nh = rb_entry(node, काष्ठा nexthop, rb_node);
		हटाओ_nexthop(net, nh, शून्य);
		cond_resched();
	पूर्ण
पूर्ण

अटल काष्ठा nexthop *nexthop_create_group(काष्ठा net *net,
					    काष्ठा nh_config *cfg)
अणु
	काष्ठा nlattr *grps_attr = cfg->nh_grp;
	काष्ठा nexthop_grp *entry = nla_data(grps_attr);
	u16 num_nh = nla_len(grps_attr) / माप(*entry);
	काष्ठा nh_group *nhg;
	काष्ठा nexthop *nh;
	पूर्णांक err;
	पूर्णांक i;

	अगर (WARN_ON(!num_nh))
		वापस ERR_PTR(-EINVAL);

	nh = nexthop_alloc();
	अगर (!nh)
		वापस ERR_PTR(-ENOMEM);

	nh->is_group = 1;

	nhg = nexthop_grp_alloc(num_nh);
	अगर (!nhg) अणु
		kमुक्त(nh);
		वापस ERR_PTR(-ENOMEM);
	पूर्ण

	/* spare group used क्रम removals */
	nhg->spare = nexthop_grp_alloc(num_nh);
	अगर (!nhg->spare) अणु
		kमुक्त(nhg);
		kमुक्त(nh);
		वापस ERR_PTR(-ENOMEM);
	पूर्ण
	nhg->spare->spare = nhg;

	क्रम (i = 0; i < nhg->num_nh; ++i) अणु
		काष्ठा nexthop *nhe;
		काष्ठा nh_info *nhi;

		nhe = nexthop_find_by_id(net, entry[i].id);
		अगर (!nexthop_get(nhe)) अणु
			err = -ENOENT;
			जाओ out_no_nh;
		पूर्ण

		nhi = rtnl_dereference(nhe->nh_info);
		अगर (nhi->family == AF_INET)
			nhg->has_v4 = true;

		nhg->nh_entries[i].nh = nhe;
		nhg->nh_entries[i].weight = entry[i].weight + 1;
		list_add(&nhg->nh_entries[i].nh_list, &nhe->grp_list);
		nhg->nh_entries[i].nh_parent = nh;
	पूर्ण

	अगर (cfg->nh_grp_type == NEXTHOP_GRP_TYPE_MPATH) अणु
		nhg->hash_threshold = 1;
		nhg->is_multipath = true;
	पूर्ण अन्यथा अगर (cfg->nh_grp_type == NEXTHOP_GRP_TYPE_RES) अणु
		काष्ठा nh_res_table *res_table;

		res_table = nexthop_res_table_alloc(net, cfg->nh_id, cfg);
		अगर (!res_table) अणु
			err = -ENOMEM;
			जाओ out_no_nh;
		पूर्ण

		rcu_assign_poपूर्णांकer(nhg->spare->res_table, res_table);
		rcu_assign_poपूर्णांकer(nhg->res_table, res_table);
		nhg->resilient = true;
		nhg->is_multipath = true;
	पूर्ण

	WARN_ON_ONCE(nhg->hash_threshold + nhg->resilient != 1);

	अगर (nhg->hash_threshold)
		nh_hthr_group_rebalance(nhg);

	अगर (cfg->nh_fdb)
		nhg->fdb_nh = 1;

	rcu_assign_poपूर्णांकer(nh->nh_grp, nhg);

	वापस nh;

out_no_nh:
	क्रम (i--; i >= 0; --i) अणु
		list_del(&nhg->nh_entries[i].nh_list);
		nexthop_put(nhg->nh_entries[i].nh);
	पूर्ण

	kमुक्त(nhg->spare);
	kमुक्त(nhg);
	kमुक्त(nh);

	वापस ERR_PTR(err);
पूर्ण

अटल पूर्णांक nh_create_ipv4(काष्ठा net *net, काष्ठा nexthop *nh,
			  काष्ठा nh_info *nhi, काष्ठा nh_config *cfg,
			  काष्ठा netlink_ext_ack *extack)
अणु
	काष्ठा fib_nh *fib_nh = &nhi->fib_nh;
	काष्ठा fib_config fib_cfg = अणु
		.fc_oअगर   = cfg->nh_अगरindex,
		.fc_gw4   = cfg->gw.ipv4,
		.fc_gw_family = cfg->gw.ipv4 ? AF_INET : 0,
		.fc_flags = cfg->nh_flags,
		.fc_encap = cfg->nh_encap,
		.fc_encap_type = cfg->nh_encap_type,
	पूर्ण;
	u32 tb_id = (cfg->dev ? l3mdev_fib_table(cfg->dev) : RT_TABLE_MAIN);
	पूर्णांक err;

	err = fib_nh_init(net, fib_nh, &fib_cfg, 1, extack);
	अगर (err) अणु
		fib_nh_release(net, fib_nh);
		जाओ out;
	पूर्ण

	अगर (nhi->fdb_nh)
		जाओ out;

	/* sets nh_dev अगर successful */
	err = fib_check_nh(net, fib_nh, tb_id, 0, extack);
	अगर (!err) अणु
		nh->nh_flags = fib_nh->fib_nh_flags;
		fib_info_update_nhc_saddr(net, &fib_nh->nh_common,
					  fib_nh->fib_nh_scope);
	पूर्ण अन्यथा अणु
		fib_nh_release(net, fib_nh);
	पूर्ण
out:
	वापस err;
पूर्ण

अटल पूर्णांक nh_create_ipv6(काष्ठा net *net,  काष्ठा nexthop *nh,
			  काष्ठा nh_info *nhi, काष्ठा nh_config *cfg,
			  काष्ठा netlink_ext_ack *extack)
अणु
	काष्ठा fib6_nh *fib6_nh = &nhi->fib6_nh;
	काष्ठा fib6_config fib6_cfg = अणु
		.fc_table = l3mdev_fib_table(cfg->dev),
		.fc_अगरindex = cfg->nh_अगरindex,
		.fc_gateway = cfg->gw.ipv6,
		.fc_flags = cfg->nh_flags,
		.fc_encap = cfg->nh_encap,
		.fc_encap_type = cfg->nh_encap_type,
		.fc_is_fdb = cfg->nh_fdb,
	पूर्ण;
	पूर्णांक err;

	अगर (!ipv6_addr_any(&cfg->gw.ipv6))
		fib6_cfg.fc_flags |= RTF_GATEWAY;

	/* sets nh_dev अगर successful */
	err = ipv6_stub->fib6_nh_init(net, fib6_nh, &fib6_cfg, GFP_KERNEL,
				      extack);
	अगर (err)
		ipv6_stub->fib6_nh_release(fib6_nh);
	अन्यथा
		nh->nh_flags = fib6_nh->fib_nh_flags;

	वापस err;
पूर्ण

अटल काष्ठा nexthop *nexthop_create(काष्ठा net *net, काष्ठा nh_config *cfg,
				      काष्ठा netlink_ext_ack *extack)
अणु
	काष्ठा nh_info *nhi;
	काष्ठा nexthop *nh;
	पूर्णांक err = 0;

	nh = nexthop_alloc();
	अगर (!nh)
		वापस ERR_PTR(-ENOMEM);

	nhi = kzalloc(माप(*nhi), GFP_KERNEL);
	अगर (!nhi) अणु
		kमुक्त(nh);
		वापस ERR_PTR(-ENOMEM);
	पूर्ण

	nh->nh_flags = cfg->nh_flags;
	nh->net = net;

	nhi->nh_parent = nh;
	nhi->family = cfg->nh_family;
	nhi->fib_nhc.nhc_scope = RT_SCOPE_LINK;

	अगर (cfg->nh_fdb)
		nhi->fdb_nh = 1;

	अगर (cfg->nh_blackhole) अणु
		nhi->reject_nh = 1;
		cfg->nh_अगरindex = net->loopback_dev->अगरindex;
	पूर्ण

	चयन (cfg->nh_family) अणु
	हाल AF_INET:
		err = nh_create_ipv4(net, nh, nhi, cfg, extack);
		अवरोध;
	हाल AF_INET6:
		err = nh_create_ipv6(net, nh, nhi, cfg, extack);
		अवरोध;
	पूर्ण

	अगर (err) अणु
		kमुक्त(nhi);
		kमुक्त(nh);
		वापस ERR_PTR(err);
	पूर्ण

	/* add the entry to the device based hash */
	अगर (!nhi->fdb_nh)
		nexthop_devhash_add(net, nhi);

	rcu_assign_poपूर्णांकer(nh->nh_info, nhi);

	वापस nh;
पूर्ण

/* called with rtnl lock held */
अटल काष्ठा nexthop *nexthop_add(काष्ठा net *net, काष्ठा nh_config *cfg,
				   काष्ठा netlink_ext_ack *extack)
अणु
	काष्ठा nexthop *nh;
	पूर्णांक err;

	अगर (cfg->nlflags & NLM_F_REPLACE && !cfg->nh_id) अणु
		NL_SET_ERR_MSG(extack, "Replace requires nexthop id");
		वापस ERR_PTR(-EINVAL);
	पूर्ण

	अगर (!cfg->nh_id) अणु
		cfg->nh_id = nh_find_unused_id(net);
		अगर (!cfg->nh_id) अणु
			NL_SET_ERR_MSG(extack, "No unused id");
			वापस ERR_PTR(-EINVAL);
		पूर्ण
	पूर्ण

	अगर (cfg->nh_grp)
		nh = nexthop_create_group(net, cfg);
	अन्यथा
		nh = nexthop_create(net, cfg, extack);

	अगर (IS_ERR(nh))
		वापस nh;

	refcount_set(&nh->refcnt, 1);
	nh->id = cfg->nh_id;
	nh->protocol = cfg->nh_protocol;
	nh->net = net;

	err = insert_nexthop(net, nh, cfg, extack);
	अगर (err) अणु
		__हटाओ_nexthop(net, nh, शून्य);
		nexthop_put(nh);
		nh = ERR_PTR(err);
	पूर्ण

	वापस nh;
पूर्ण

अटल पूर्णांक rपंचांग_nh_get_समयr(काष्ठा nlattr *attr, अचिन्हित दीर्घ fallback,
			    अचिन्हित दीर्घ *समयr_p, bool *has_p,
			    काष्ठा netlink_ext_ack *extack)
अणु
	अचिन्हित दीर्घ समयr;
	u32 value;

	अगर (!attr) अणु
		*समयr_p = fallback;
		*has_p = false;
		वापस 0;
	पूर्ण

	value = nla_get_u32(attr);
	समयr = घड़ी_प्रकार_to_jअगरfies(value);
	अगर (समयr == ~0UL) अणु
		NL_SET_ERR_MSG(extack, "Timer value too large");
		वापस -EINVAL;
	पूर्ण

	*समयr_p = समयr;
	*has_p = true;
	वापस 0;
पूर्ण

अटल पूर्णांक rपंचांग_to_nh_config_grp_res(काष्ठा nlattr *res, काष्ठा nh_config *cfg,
				    काष्ठा netlink_ext_ack *extack)
अणु
	काष्ठा nlattr *tb[ARRAY_SIZE(rपंचांग_nh_res_policy_new)] = अणुपूर्ण;
	पूर्णांक err;

	अगर (res) अणु
		err = nla_parse_nested(tb,
				       ARRAY_SIZE(rपंचांग_nh_res_policy_new) - 1,
				       res, rपंचांग_nh_res_policy_new, extack);
		अगर (err < 0)
			वापस err;
	पूर्ण

	अगर (tb[NHA_RES_GROUP_BUCKETS]) अणु
		cfg->nh_grp_res_num_buckets =
			nla_get_u16(tb[NHA_RES_GROUP_BUCKETS]);
		cfg->nh_grp_res_has_num_buckets = true;
		अगर (!cfg->nh_grp_res_num_buckets) अणु
			NL_SET_ERR_MSG(extack, "Number of buckets needs to be non-0");
			वापस -EINVAL;
		पूर्ण
	पूर्ण

	err = rपंचांग_nh_get_समयr(tb[NHA_RES_GROUP_IDLE_TIMER],
			       NH_RES_DEFAULT_IDLE_TIMER,
			       &cfg->nh_grp_res_idle_समयr,
			       &cfg->nh_grp_res_has_idle_समयr,
			       extack);
	अगर (err)
		वापस err;

	वापस rपंचांग_nh_get_समयr(tb[NHA_RES_GROUP_UNBALANCED_TIMER],
				NH_RES_DEFAULT_UNBALANCED_TIMER,
				&cfg->nh_grp_res_unbalanced_समयr,
				&cfg->nh_grp_res_has_unbalanced_समयr,
				extack);
पूर्ण

अटल पूर्णांक rपंचांग_to_nh_config(काष्ठा net *net, काष्ठा sk_buff *skb,
			    काष्ठा nlmsghdr *nlh, काष्ठा nh_config *cfg,
			    काष्ठा netlink_ext_ack *extack)
अणु
	काष्ठा nhmsg *nhm = nlmsg_data(nlh);
	काष्ठा nlattr *tb[ARRAY_SIZE(rपंचांग_nh_policy_new)];
	पूर्णांक err;

	err = nlmsg_parse(nlh, माप(*nhm), tb,
			  ARRAY_SIZE(rपंचांग_nh_policy_new) - 1,
			  rपंचांग_nh_policy_new, extack);
	अगर (err < 0)
		वापस err;

	err = -EINVAL;
	अगर (nhm->resvd || nhm->nh_scope) अणु
		NL_SET_ERR_MSG(extack, "Invalid values in ancillary header");
		जाओ out;
	पूर्ण
	अगर (nhm->nh_flags & ~NEXTHOP_VALID_USER_FLAGS) अणु
		NL_SET_ERR_MSG(extack, "Invalid nexthop flags in ancillary header");
		जाओ out;
	पूर्ण

	चयन (nhm->nh_family) अणु
	हाल AF_INET:
	हाल AF_INET6:
		अवरोध;
	हाल AF_UNSPEC:
		अगर (tb[NHA_GROUP])
			अवरोध;
		fallthrough;
	शेष:
		NL_SET_ERR_MSG(extack, "Invalid address family");
		जाओ out;
	पूर्ण

	स_रखो(cfg, 0, माप(*cfg));
	cfg->nlflags = nlh->nlmsg_flags;
	cfg->nlinfo.portid = NETLINK_CB(skb).portid;
	cfg->nlinfo.nlh = nlh;
	cfg->nlinfo.nl_net = net;

	cfg->nh_family = nhm->nh_family;
	cfg->nh_protocol = nhm->nh_protocol;
	cfg->nh_flags = nhm->nh_flags;

	अगर (tb[NHA_ID])
		cfg->nh_id = nla_get_u32(tb[NHA_ID]);

	अगर (tb[NHA_FDB]) अणु
		अगर (tb[NHA_OIF] || tb[NHA_BLACKHOLE] ||
		    tb[NHA_ENCAP]   || tb[NHA_ENCAP_TYPE]) अणु
			NL_SET_ERR_MSG(extack, "Fdb attribute can not be used with encap, oif or blackhole");
			जाओ out;
		पूर्ण
		अगर (nhm->nh_flags) अणु
			NL_SET_ERR_MSG(extack, "Unsupported nexthop flags in ancillary header");
			जाओ out;
		पूर्ण
		cfg->nh_fdb = nla_get_flag(tb[NHA_FDB]);
	पूर्ण

	अगर (tb[NHA_GROUP]) अणु
		अगर (nhm->nh_family != AF_UNSPEC) अणु
			NL_SET_ERR_MSG(extack, "Invalid family for group");
			जाओ out;
		पूर्ण
		cfg->nh_grp = tb[NHA_GROUP];

		cfg->nh_grp_type = NEXTHOP_GRP_TYPE_MPATH;
		अगर (tb[NHA_GROUP_TYPE])
			cfg->nh_grp_type = nla_get_u16(tb[NHA_GROUP_TYPE]);

		अगर (cfg->nh_grp_type > NEXTHOP_GRP_TYPE_MAX) अणु
			NL_SET_ERR_MSG(extack, "Invalid group type");
			जाओ out;
		पूर्ण
		err = nh_check_attr_group(net, tb, ARRAY_SIZE(tb),
					  cfg->nh_grp_type, extack);
		अगर (err)
			जाओ out;

		अगर (cfg->nh_grp_type == NEXTHOP_GRP_TYPE_RES)
			err = rपंचांग_to_nh_config_grp_res(tb[NHA_RES_GROUP],
						       cfg, extack);

		/* no other attributes should be set */
		जाओ out;
	पूर्ण

	अगर (tb[NHA_BLACKHOLE]) अणु
		अगर (tb[NHA_GATEWAY] || tb[NHA_OIF] ||
		    tb[NHA_ENCAP]   || tb[NHA_ENCAP_TYPE] || tb[NHA_FDB]) अणु
			NL_SET_ERR_MSG(extack, "Blackhole attribute can not be used with gateway, oif, encap or fdb");
			जाओ out;
		पूर्ण

		cfg->nh_blackhole = 1;
		err = 0;
		जाओ out;
	पूर्ण

	अगर (!cfg->nh_fdb && !tb[NHA_OIF]) अणु
		NL_SET_ERR_MSG(extack, "Device attribute required for non-blackhole and non-fdb nexthops");
		जाओ out;
	पूर्ण

	अगर (!cfg->nh_fdb && tb[NHA_OIF]) अणु
		cfg->nh_अगरindex = nla_get_u32(tb[NHA_OIF]);
		अगर (cfg->nh_अगरindex)
			cfg->dev = __dev_get_by_index(net, cfg->nh_अगरindex);

		अगर (!cfg->dev) अणु
			NL_SET_ERR_MSG(extack, "Invalid device index");
			जाओ out;
		पूर्ण अन्यथा अगर (!(cfg->dev->flags & IFF_UP)) अणु
			NL_SET_ERR_MSG(extack, "Nexthop device is not up");
			err = -ENETDOWN;
			जाओ out;
		पूर्ण अन्यथा अगर (!netअगर_carrier_ok(cfg->dev)) अणु
			NL_SET_ERR_MSG(extack, "Carrier for nexthop device is down");
			err = -ENETDOWN;
			जाओ out;
		पूर्ण
	पूर्ण

	err = -EINVAL;
	अगर (tb[NHA_GATEWAY]) अणु
		काष्ठा nlattr *gwa = tb[NHA_GATEWAY];

		चयन (cfg->nh_family) अणु
		हाल AF_INET:
			अगर (nla_len(gwa) != माप(u32)) अणु
				NL_SET_ERR_MSG(extack, "Invalid gateway");
				जाओ out;
			पूर्ण
			cfg->gw.ipv4 = nla_get_be32(gwa);
			अवरोध;
		हाल AF_INET6:
			अगर (nla_len(gwa) != माप(काष्ठा in6_addr)) अणु
				NL_SET_ERR_MSG(extack, "Invalid gateway");
				जाओ out;
			पूर्ण
			cfg->gw.ipv6 = nla_get_in6_addr(gwa);
			अवरोध;
		शेष:
			NL_SET_ERR_MSG(extack,
				       "Unknown address family for gateway");
			जाओ out;
		पूर्ण
	पूर्ण अन्यथा अणु
		/* device only nexthop (no gateway) */
		अगर (cfg->nh_flags & RTNH_F_ONLINK) अणु
			NL_SET_ERR_MSG(extack,
				       "ONLINK flag can not be set for nexthop without a gateway");
			जाओ out;
		पूर्ण
	पूर्ण

	अगर (tb[NHA_ENCAP]) अणु
		cfg->nh_encap = tb[NHA_ENCAP];

		अगर (!tb[NHA_ENCAP_TYPE]) अणु
			NL_SET_ERR_MSG(extack, "LWT encapsulation type is missing");
			जाओ out;
		पूर्ण

		cfg->nh_encap_type = nla_get_u16(tb[NHA_ENCAP_TYPE]);
		err = lwtunnel_valid_encap_type(cfg->nh_encap_type, extack);
		अगर (err < 0)
			जाओ out;

	पूर्ण अन्यथा अगर (tb[NHA_ENCAP_TYPE]) अणु
		NL_SET_ERR_MSG(extack, "LWT encapsulation attribute is missing");
		जाओ out;
	पूर्ण


	err = 0;
out:
	वापस err;
पूर्ण

/* rtnl */
अटल पूर्णांक rपंचांग_new_nexthop(काष्ठा sk_buff *skb, काष्ठा nlmsghdr *nlh,
			   काष्ठा netlink_ext_ack *extack)
अणु
	काष्ठा net *net = sock_net(skb->sk);
	काष्ठा nh_config cfg;
	काष्ठा nexthop *nh;
	पूर्णांक err;

	err = rपंचांग_to_nh_config(net, skb, nlh, &cfg, extack);
	अगर (!err) अणु
		nh = nexthop_add(net, &cfg, extack);
		अगर (IS_ERR(nh))
			err = PTR_ERR(nh);
	पूर्ण

	वापस err;
पूर्ण

अटल पूर्णांक __nh_valid_get_del_req(स्थिर काष्ठा nlmsghdr *nlh,
				  काष्ठा nlattr **tb, u32 *id,
				  काष्ठा netlink_ext_ack *extack)
अणु
	काष्ठा nhmsg *nhm = nlmsg_data(nlh);

	अगर (nhm->nh_protocol || nhm->resvd || nhm->nh_scope || nhm->nh_flags) अणु
		NL_SET_ERR_MSG(extack, "Invalid values in header");
		वापस -EINVAL;
	पूर्ण

	अगर (!tb[NHA_ID]) अणु
		NL_SET_ERR_MSG(extack, "Nexthop id is missing");
		वापस -EINVAL;
	पूर्ण

	*id = nla_get_u32(tb[NHA_ID]);
	अगर (!(*id)) अणु
		NL_SET_ERR_MSG(extack, "Invalid nexthop id");
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक nh_valid_get_del_req(स्थिर काष्ठा nlmsghdr *nlh, u32 *id,
				काष्ठा netlink_ext_ack *extack)
अणु
	काष्ठा nlattr *tb[ARRAY_SIZE(rपंचांग_nh_policy_get)];
	पूर्णांक err;

	err = nlmsg_parse(nlh, माप(काष्ठा nhmsg), tb,
			  ARRAY_SIZE(rपंचांग_nh_policy_get) - 1,
			  rपंचांग_nh_policy_get, extack);
	अगर (err < 0)
		वापस err;

	वापस __nh_valid_get_del_req(nlh, tb, id, extack);
पूर्ण

/* rtnl */
अटल पूर्णांक rपंचांग_del_nexthop(काष्ठा sk_buff *skb, काष्ठा nlmsghdr *nlh,
			   काष्ठा netlink_ext_ack *extack)
अणु
	काष्ठा net *net = sock_net(skb->sk);
	काष्ठा nl_info nlinfo = अणु
		.nlh = nlh,
		.nl_net = net,
		.portid = NETLINK_CB(skb).portid,
	पूर्ण;
	काष्ठा nexthop *nh;
	पूर्णांक err;
	u32 id;

	err = nh_valid_get_del_req(nlh, &id, extack);
	अगर (err)
		वापस err;

	nh = nexthop_find_by_id(net, id);
	अगर (!nh)
		वापस -ENOENT;

	हटाओ_nexthop(net, nh, &nlinfo);

	वापस 0;
पूर्ण

/* rtnl */
अटल पूर्णांक rपंचांग_get_nexthop(काष्ठा sk_buff *in_skb, काष्ठा nlmsghdr *nlh,
			   काष्ठा netlink_ext_ack *extack)
अणु
	काष्ठा net *net = sock_net(in_skb->sk);
	काष्ठा sk_buff *skb = शून्य;
	काष्ठा nexthop *nh;
	पूर्णांक err;
	u32 id;

	err = nh_valid_get_del_req(nlh, &id, extack);
	अगर (err)
		वापस err;

	err = -ENOBUFS;
	skb = alloc_skb(NLMSG_GOODSIZE, GFP_KERNEL);
	अगर (!skb)
		जाओ out;

	err = -ENOENT;
	nh = nexthop_find_by_id(net, id);
	अगर (!nh)
		जाओ errout_मुक्त;

	err = nh_fill_node(skb, nh, RTM_NEWNEXTHOP, NETLINK_CB(in_skb).portid,
			   nlh->nlmsg_seq, 0);
	अगर (err < 0) अणु
		WARN_ON(err == -EMSGSIZE);
		जाओ errout_मुक्त;
	पूर्ण

	err = rtnl_unicast(skb, net, NETLINK_CB(in_skb).portid);
out:
	वापस err;
errout_मुक्त:
	kमुक्त_skb(skb);
	जाओ out;
पूर्ण

काष्ठा nh_dump_filter अणु
	u32 nh_id;
	पूर्णांक dev_idx;
	पूर्णांक master_idx;
	bool group_filter;
	bool fdb_filter;
	u32 res_bucket_nh_id;
पूर्ण;

अटल bool nh_dump_filtered(काष्ठा nexthop *nh,
			     काष्ठा nh_dump_filter *filter, u8 family)
अणु
	स्थिर काष्ठा net_device *dev;
	स्थिर काष्ठा nh_info *nhi;

	अगर (filter->group_filter && !nh->is_group)
		वापस true;

	अगर (!filter->dev_idx && !filter->master_idx && !family)
		वापस false;

	अगर (nh->is_group)
		वापस true;

	nhi = rtnl_dereference(nh->nh_info);
	अगर (family && nhi->family != family)
		वापस true;

	dev = nhi->fib_nhc.nhc_dev;
	अगर (filter->dev_idx && (!dev || dev->अगरindex != filter->dev_idx))
		वापस true;

	अगर (filter->master_idx) अणु
		काष्ठा net_device *master;

		अगर (!dev)
			वापस true;

		master = netdev_master_upper_dev_get((काष्ठा net_device *)dev);
		अगर (!master || master->अगरindex != filter->master_idx)
			वापस true;
	पूर्ण

	वापस false;
पूर्ण

अटल पूर्णांक __nh_valid_dump_req(स्थिर काष्ठा nlmsghdr *nlh, काष्ठा nlattr **tb,
			       काष्ठा nh_dump_filter *filter,
			       काष्ठा netlink_ext_ack *extack)
अणु
	काष्ठा nhmsg *nhm;
	u32 idx;

	अगर (tb[NHA_OIF]) अणु
		idx = nla_get_u32(tb[NHA_OIF]);
		अगर (idx > पूर्णांक_उच्च) अणु
			NL_SET_ERR_MSG(extack, "Invalid device index");
			वापस -EINVAL;
		पूर्ण
		filter->dev_idx = idx;
	पूर्ण
	अगर (tb[NHA_MASTER]) अणु
		idx = nla_get_u32(tb[NHA_MASTER]);
		अगर (idx > पूर्णांक_उच्च) अणु
			NL_SET_ERR_MSG(extack, "Invalid master device index");
			वापस -EINVAL;
		पूर्ण
		filter->master_idx = idx;
	पूर्ण
	filter->group_filter = nla_get_flag(tb[NHA_GROUPS]);
	filter->fdb_filter = nla_get_flag(tb[NHA_FDB]);

	nhm = nlmsg_data(nlh);
	अगर (nhm->nh_protocol || nhm->resvd || nhm->nh_scope || nhm->nh_flags) अणु
		NL_SET_ERR_MSG(extack, "Invalid values in header for nexthop dump request");
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक nh_valid_dump_req(स्थिर काष्ठा nlmsghdr *nlh,
			     काष्ठा nh_dump_filter *filter,
			     काष्ठा netlink_callback *cb)
अणु
	काष्ठा nlattr *tb[ARRAY_SIZE(rपंचांग_nh_policy_dump)];
	पूर्णांक err;

	err = nlmsg_parse(nlh, माप(काष्ठा nhmsg), tb,
			  ARRAY_SIZE(rपंचांग_nh_policy_dump) - 1,
			  rपंचांग_nh_policy_dump, cb->extack);
	अगर (err < 0)
		वापस err;

	वापस __nh_valid_dump_req(nlh, tb, filter, cb->extack);
पूर्ण

काष्ठा rपंचांग_dump_nh_ctx अणु
	u32 idx;
पूर्ण;

अटल काष्ठा rपंचांग_dump_nh_ctx *
rपंचांग_dump_nh_ctx(काष्ठा netlink_callback *cb)
अणु
	काष्ठा rपंचांग_dump_nh_ctx *ctx = (व्योम *)cb->ctx;

	BUILD_BUG_ON(माप(*ctx) > माप(cb->ctx));
	वापस ctx;
पूर्ण

अटल पूर्णांक rपंचांग_dump_walk_nexthops(काष्ठा sk_buff *skb,
				  काष्ठा netlink_callback *cb,
				  काष्ठा rb_root *root,
				  काष्ठा rपंचांग_dump_nh_ctx *ctx,
				  पूर्णांक (*nh_cb)(काष्ठा sk_buff *skb,
					       काष्ठा netlink_callback *cb,
					       काष्ठा nexthop *nh, व्योम *data),
				  व्योम *data)
अणु
	काष्ठा rb_node *node;
	पूर्णांक s_idx;
	पूर्णांक err;

	s_idx = ctx->idx;
	क्रम (node = rb_first(root); node; node = rb_next(node)) अणु
		काष्ठा nexthop *nh;

		nh = rb_entry(node, काष्ठा nexthop, rb_node);
		अगर (nh->id < s_idx)
			जारी;

		ctx->idx = nh->id;
		err = nh_cb(skb, cb, nh, data);
		अगर (err)
			वापस err;
	पूर्ण

	ctx->idx++;
	वापस 0;
पूर्ण

अटल पूर्णांक rपंचांग_dump_nexthop_cb(काष्ठा sk_buff *skb, काष्ठा netlink_callback *cb,
			       काष्ठा nexthop *nh, व्योम *data)
अणु
	काष्ठा nhmsg *nhm = nlmsg_data(cb->nlh);
	काष्ठा nh_dump_filter *filter = data;

	अगर (nh_dump_filtered(nh, filter, nhm->nh_family))
		वापस 0;

	वापस nh_fill_node(skb, nh, RTM_NEWNEXTHOP,
			    NETLINK_CB(cb->skb).portid,
			    cb->nlh->nlmsg_seq, NLM_F_MULTI);
पूर्ण

/* rtnl */
अटल पूर्णांक rपंचांग_dump_nexthop(काष्ठा sk_buff *skb, काष्ठा netlink_callback *cb)
अणु
	काष्ठा rपंचांग_dump_nh_ctx *ctx = rपंचांग_dump_nh_ctx(cb);
	काष्ठा net *net = sock_net(skb->sk);
	काष्ठा rb_root *root = &net->nexthop.rb_root;
	काष्ठा nh_dump_filter filter = अणुपूर्ण;
	पूर्णांक err;

	err = nh_valid_dump_req(cb->nlh, &filter, cb);
	अगर (err < 0)
		वापस err;

	err = rपंचांग_dump_walk_nexthops(skb, cb, root, ctx,
				     &rपंचांग_dump_nexthop_cb, &filter);
	अगर (err < 0) अणु
		अगर (likely(skb->len))
			जाओ out;
		जाओ out_err;
	पूर्ण

out:
	err = skb->len;
out_err:
	cb->seq = net->nexthop.seq;
	nl_dump_check_consistent(cb, nlmsg_hdr(skb));
	वापस err;
पूर्ण

अटल काष्ठा nexthop *
nexthop_find_group_resilient(काष्ठा net *net, u32 id,
			     काष्ठा netlink_ext_ack *extack)
अणु
	काष्ठा nh_group *nhg;
	काष्ठा nexthop *nh;

	nh = nexthop_find_by_id(net, id);
	अगर (!nh)
		वापस ERR_PTR(-ENOENT);

	अगर (!nh->is_group) अणु
		NL_SET_ERR_MSG(extack, "Not a nexthop group");
		वापस ERR_PTR(-EINVAL);
	पूर्ण

	nhg = rtnl_dereference(nh->nh_grp);
	अगर (!nhg->resilient) अणु
		NL_SET_ERR_MSG(extack, "Nexthop group not of type resilient");
		वापस ERR_PTR(-EINVAL);
	पूर्ण

	वापस nh;
पूर्ण

अटल पूर्णांक nh_valid_dump_nhid(काष्ठा nlattr *attr, u32 *nh_id_p,
			      काष्ठा netlink_ext_ack *extack)
अणु
	u32 idx;

	अगर (attr) अणु
		idx = nla_get_u32(attr);
		अगर (!idx) अणु
			NL_SET_ERR_MSG(extack, "Invalid nexthop id");
			वापस -EINVAL;
		पूर्ण
		*nh_id_p = idx;
	पूर्ण अन्यथा अणु
		*nh_id_p = 0;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक nh_valid_dump_bucket_req(स्थिर काष्ठा nlmsghdr *nlh,
				    काष्ठा nh_dump_filter *filter,
				    काष्ठा netlink_callback *cb)
अणु
	काष्ठा nlattr *res_tb[ARRAY_SIZE(rपंचांग_nh_res_bucket_policy_dump)];
	काष्ठा nlattr *tb[ARRAY_SIZE(rपंचांग_nh_policy_dump_bucket)];
	पूर्णांक err;

	err = nlmsg_parse(nlh, माप(काष्ठा nhmsg), tb,
			  ARRAY_SIZE(rपंचांग_nh_policy_dump_bucket) - 1,
			  rपंचांग_nh_policy_dump_bucket, शून्य);
	अगर (err < 0)
		वापस err;

	err = nh_valid_dump_nhid(tb[NHA_ID], &filter->nh_id, cb->extack);
	अगर (err)
		वापस err;

	अगर (tb[NHA_RES_BUCKET]) अणु
		माप_प्रकार max = ARRAY_SIZE(rपंचांग_nh_res_bucket_policy_dump) - 1;

		err = nla_parse_nested(res_tb, max,
				       tb[NHA_RES_BUCKET],
				       rपंचांग_nh_res_bucket_policy_dump,
				       cb->extack);
		अगर (err < 0)
			वापस err;

		err = nh_valid_dump_nhid(res_tb[NHA_RES_BUCKET_NH_ID],
					 &filter->res_bucket_nh_id,
					 cb->extack);
		अगर (err)
			वापस err;
	पूर्ण

	वापस __nh_valid_dump_req(nlh, tb, filter, cb->extack);
पूर्ण

काष्ठा rपंचांग_dump_res_bucket_ctx अणु
	काष्ठा rपंचांग_dump_nh_ctx nh;
	u16 bucket_index;
	u32 करोne_nh_idx; /* 1 + the index of the last fully processed NH. */
पूर्ण;

अटल काष्ठा rपंचांग_dump_res_bucket_ctx *
rपंचांग_dump_res_bucket_ctx(काष्ठा netlink_callback *cb)
अणु
	काष्ठा rपंचांग_dump_res_bucket_ctx *ctx = (व्योम *)cb->ctx;

	BUILD_BUG_ON(माप(*ctx) > माप(cb->ctx));
	वापस ctx;
पूर्ण

काष्ठा rपंचांग_dump_nexthop_bucket_data अणु
	काष्ठा rपंचांग_dump_res_bucket_ctx *ctx;
	काष्ठा nh_dump_filter filter;
पूर्ण;

अटल पूर्णांक rपंचांग_dump_nexthop_bucket_nh(काष्ठा sk_buff *skb,
				      काष्ठा netlink_callback *cb,
				      काष्ठा nexthop *nh,
				      काष्ठा rपंचांग_dump_nexthop_bucket_data *dd)
अणु
	u32 portid = NETLINK_CB(cb->skb).portid;
	काष्ठा nhmsg *nhm = nlmsg_data(cb->nlh);
	काष्ठा nh_res_table *res_table;
	काष्ठा nh_group *nhg;
	u16 bucket_index;
	पूर्णांक err;

	अगर (dd->ctx->nh.idx < dd->ctx->करोne_nh_idx)
		वापस 0;

	nhg = rtnl_dereference(nh->nh_grp);
	res_table = rtnl_dereference(nhg->res_table);
	क्रम (bucket_index = dd->ctx->bucket_index;
	     bucket_index < res_table->num_nh_buckets;
	     bucket_index++) अणु
		काष्ठा nh_res_bucket *bucket;
		काष्ठा nh_grp_entry *nhge;

		bucket = &res_table->nh_buckets[bucket_index];
		nhge = rtnl_dereference(bucket->nh_entry);
		अगर (nh_dump_filtered(nhge->nh, &dd->filter, nhm->nh_family))
			जारी;

		अगर (dd->filter.res_bucket_nh_id &&
		    dd->filter.res_bucket_nh_id != nhge->nh->id)
			जारी;

		err = nh_fill_res_bucket(skb, nh, bucket, bucket_index,
					 RTM_NEWNEXTHOPBUCKET, portid,
					 cb->nlh->nlmsg_seq, NLM_F_MULTI,
					 cb->extack);
		अगर (err < 0) अणु
			अगर (likely(skb->len))
				जाओ out;
			जाओ out_err;
		पूर्ण
	पूर्ण

	dd->ctx->करोne_nh_idx = dd->ctx->nh.idx + 1;
	bucket_index = 0;

out:
	err = skb->len;
out_err:
	dd->ctx->bucket_index = bucket_index;
	वापस err;
पूर्ण

अटल पूर्णांक rपंचांग_dump_nexthop_bucket_cb(काष्ठा sk_buff *skb,
				      काष्ठा netlink_callback *cb,
				      काष्ठा nexthop *nh, व्योम *data)
अणु
	काष्ठा rपंचांग_dump_nexthop_bucket_data *dd = data;
	काष्ठा nh_group *nhg;

	अगर (!nh->is_group)
		वापस 0;

	nhg = rtnl_dereference(nh->nh_grp);
	अगर (!nhg->resilient)
		वापस 0;

	वापस rपंचांग_dump_nexthop_bucket_nh(skb, cb, nh, dd);
पूर्ण

/* rtnl */
अटल पूर्णांक rपंचांग_dump_nexthop_bucket(काष्ठा sk_buff *skb,
				   काष्ठा netlink_callback *cb)
अणु
	काष्ठा rपंचांग_dump_res_bucket_ctx *ctx = rपंचांग_dump_res_bucket_ctx(cb);
	काष्ठा rपंचांग_dump_nexthop_bucket_data dd = अणु .ctx = ctx पूर्ण;
	काष्ठा net *net = sock_net(skb->sk);
	काष्ठा nexthop *nh;
	पूर्णांक err;

	err = nh_valid_dump_bucket_req(cb->nlh, &dd.filter, cb);
	अगर (err)
		वापस err;

	अगर (dd.filter.nh_id) अणु
		nh = nexthop_find_group_resilient(net, dd.filter.nh_id,
						  cb->extack);
		अगर (IS_ERR(nh))
			वापस PTR_ERR(nh);
		err = rपंचांग_dump_nexthop_bucket_nh(skb, cb, nh, &dd);
	पूर्ण अन्यथा अणु
		काष्ठा rb_root *root = &net->nexthop.rb_root;

		err = rपंचांग_dump_walk_nexthops(skb, cb, root, &ctx->nh,
					     &rपंचांग_dump_nexthop_bucket_cb, &dd);
	पूर्ण

	अगर (err < 0) अणु
		अगर (likely(skb->len))
			जाओ out;
		जाओ out_err;
	पूर्ण

out:
	err = skb->len;
out_err:
	cb->seq = net->nexthop.seq;
	nl_dump_check_consistent(cb, nlmsg_hdr(skb));
	वापस err;
पूर्ण

अटल पूर्णांक nh_valid_get_bucket_req_res_bucket(काष्ठा nlattr *res,
					      u16 *bucket_index,
					      काष्ठा netlink_ext_ack *extack)
अणु
	काष्ठा nlattr *tb[ARRAY_SIZE(rपंचांग_nh_res_bucket_policy_get)];
	पूर्णांक err;

	err = nla_parse_nested(tb, ARRAY_SIZE(rपंचांग_nh_res_bucket_policy_get) - 1,
			       res, rपंचांग_nh_res_bucket_policy_get, extack);
	अगर (err < 0)
		वापस err;

	अगर (!tb[NHA_RES_BUCKET_INDEX]) अणु
		NL_SET_ERR_MSG(extack, "Bucket index is missing");
		वापस -EINVAL;
	पूर्ण

	*bucket_index = nla_get_u16(tb[NHA_RES_BUCKET_INDEX]);
	वापस 0;
पूर्ण

अटल पूर्णांक nh_valid_get_bucket_req(स्थिर काष्ठा nlmsghdr *nlh,
				   u32 *id, u16 *bucket_index,
				   काष्ठा netlink_ext_ack *extack)
अणु
	काष्ठा nlattr *tb[ARRAY_SIZE(rपंचांग_nh_policy_get_bucket)];
	पूर्णांक err;

	err = nlmsg_parse(nlh, माप(काष्ठा nhmsg), tb,
			  ARRAY_SIZE(rपंचांग_nh_policy_get_bucket) - 1,
			  rपंचांग_nh_policy_get_bucket, extack);
	अगर (err < 0)
		वापस err;

	err = __nh_valid_get_del_req(nlh, tb, id, extack);
	अगर (err)
		वापस err;

	अगर (!tb[NHA_RES_BUCKET]) अणु
		NL_SET_ERR_MSG(extack, "Bucket information is missing");
		वापस -EINVAL;
	पूर्ण

	err = nh_valid_get_bucket_req_res_bucket(tb[NHA_RES_BUCKET],
						 bucket_index, extack);
	अगर (err)
		वापस err;

	वापस 0;
पूर्ण

/* rtnl */
अटल पूर्णांक rपंचांग_get_nexthop_bucket(काष्ठा sk_buff *in_skb, काष्ठा nlmsghdr *nlh,
				  काष्ठा netlink_ext_ack *extack)
अणु
	काष्ठा net *net = sock_net(in_skb->sk);
	काष्ठा nh_res_table *res_table;
	काष्ठा sk_buff *skb = शून्य;
	काष्ठा nh_group *nhg;
	काष्ठा nexthop *nh;
	u16 bucket_index;
	पूर्णांक err;
	u32 id;

	err = nh_valid_get_bucket_req(nlh, &id, &bucket_index, extack);
	अगर (err)
		वापस err;

	nh = nexthop_find_group_resilient(net, id, extack);
	अगर (IS_ERR(nh))
		वापस PTR_ERR(nh);

	nhg = rtnl_dereference(nh->nh_grp);
	res_table = rtnl_dereference(nhg->res_table);
	अगर (bucket_index >= res_table->num_nh_buckets) अणु
		NL_SET_ERR_MSG(extack, "Bucket index out of bounds");
		वापस -ENOENT;
	पूर्ण

	skb = alloc_skb(NLMSG_GOODSIZE, GFP_KERNEL);
	अगर (!skb)
		वापस -ENOBUFS;

	err = nh_fill_res_bucket(skb, nh, &res_table->nh_buckets[bucket_index],
				 bucket_index, RTM_NEWNEXTHOPBUCKET,
				 NETLINK_CB(in_skb).portid, nlh->nlmsg_seq,
				 0, extack);
	अगर (err < 0) अणु
		WARN_ON(err == -EMSGSIZE);
		जाओ errout_मुक्त;
	पूर्ण

	वापस rtnl_unicast(skb, net, NETLINK_CB(in_skb).portid);

errout_मुक्त:
	kमुक्त_skb(skb);
	वापस err;
पूर्ण

अटल व्योम nexthop_sync_mtu(काष्ठा net_device *dev, u32 orig_mtu)
अणु
	अचिन्हित पूर्णांक hash = nh_dev_hashfn(dev->अगरindex);
	काष्ठा net *net = dev_net(dev);
	काष्ठा hlist_head *head = &net->nexthop.devhash[hash];
	काष्ठा hlist_node *n;
	काष्ठा nh_info *nhi;

	hlist_क्रम_each_entry_safe(nhi, n, head, dev_hash) अणु
		अगर (nhi->fib_nhc.nhc_dev == dev) अणु
			अगर (nhi->family == AF_INET)
				fib_nhc_update_mtu(&nhi->fib_nhc, dev->mtu,
						   orig_mtu);
		पूर्ण
	पूर्ण
पूर्ण

/* rtnl */
अटल पूर्णांक nh_netdev_event(काष्ठा notअगरier_block *this,
			   अचिन्हित दीर्घ event, व्योम *ptr)
अणु
	काष्ठा net_device *dev = netdev_notअगरier_info_to_dev(ptr);
	काष्ठा netdev_notअगरier_info_ext *info_ext;

	चयन (event) अणु
	हाल NETDEV_DOWN:
	हाल NETDEV_UNREGISTER:
		nexthop_flush_dev(dev, event);
		अवरोध;
	हाल NETDEV_CHANGE:
		अगर (!(dev_get_flags(dev) & (IFF_RUNNING | IFF_LOWER_UP)))
			nexthop_flush_dev(dev, event);
		अवरोध;
	हाल NETDEV_CHANGEMTU:
		info_ext = ptr;
		nexthop_sync_mtu(dev, info_ext->ext.mtu);
		rt_cache_flush(dev_net(dev));
		अवरोध;
	पूर्ण
	वापस NOTIFY_DONE;
पूर्ण

अटल काष्ठा notअगरier_block nh_netdev_notअगरier = अणु
	.notअगरier_call = nh_netdev_event,
पूर्ण;

अटल पूर्णांक nexthops_dump(काष्ठा net *net, काष्ठा notअगरier_block *nb,
			 काष्ठा netlink_ext_ack *extack)
अणु
	काष्ठा rb_root *root = &net->nexthop.rb_root;
	काष्ठा rb_node *node;
	पूर्णांक err = 0;

	क्रम (node = rb_first(root); node; node = rb_next(node)) अणु
		काष्ठा nexthop *nh;

		nh = rb_entry(node, काष्ठा nexthop, rb_node);
		err = call_nexthop_notअगरier(nb, net, NEXTHOP_EVENT_REPLACE, nh,
					    extack);
		अगर (err)
			अवरोध;
	पूर्ण

	वापस err;
पूर्ण

पूर्णांक रेजिस्टर_nexthop_notअगरier(काष्ठा net *net, काष्ठा notअगरier_block *nb,
			      काष्ठा netlink_ext_ack *extack)
अणु
	पूर्णांक err;

	rtnl_lock();
	err = nexthops_dump(net, nb, extack);
	अगर (err)
		जाओ unlock;
	err = blocking_notअगरier_chain_रेजिस्टर(&net->nexthop.notअगरier_chain,
					       nb);
unlock:
	rtnl_unlock();
	वापस err;
पूर्ण
EXPORT_SYMBOL(रेजिस्टर_nexthop_notअगरier);

पूर्णांक unरेजिस्टर_nexthop_notअगरier(काष्ठा net *net, काष्ठा notअगरier_block *nb)
अणु
	वापस blocking_notअगरier_chain_unरेजिस्टर(&net->nexthop.notअगरier_chain,
						  nb);
पूर्ण
EXPORT_SYMBOL(unरेजिस्टर_nexthop_notअगरier);

व्योम nexthop_set_hw_flags(काष्ठा net *net, u32 id, bool offload, bool trap)
अणु
	काष्ठा nexthop *nexthop;

	rcu_पढ़ो_lock();

	nexthop = nexthop_find_by_id(net, id);
	अगर (!nexthop)
		जाओ out;

	nexthop->nh_flags &= ~(RTNH_F_OFFLOAD | RTNH_F_TRAP);
	अगर (offload)
		nexthop->nh_flags |= RTNH_F_OFFLOAD;
	अगर (trap)
		nexthop->nh_flags |= RTNH_F_TRAP;

out:
	rcu_पढ़ो_unlock();
पूर्ण
EXPORT_SYMBOL(nexthop_set_hw_flags);

व्योम nexthop_bucket_set_hw_flags(काष्ठा net *net, u32 id, u16 bucket_index,
				 bool offload, bool trap)
अणु
	काष्ठा nh_res_table *res_table;
	काष्ठा nh_res_bucket *bucket;
	काष्ठा nexthop *nexthop;
	काष्ठा nh_group *nhg;

	rcu_पढ़ो_lock();

	nexthop = nexthop_find_by_id(net, id);
	अगर (!nexthop || !nexthop->is_group)
		जाओ out;

	nhg = rcu_dereference(nexthop->nh_grp);
	अगर (!nhg->resilient)
		जाओ out;

	अगर (bucket_index >= nhg->res_table->num_nh_buckets)
		जाओ out;

	res_table = rcu_dereference(nhg->res_table);
	bucket = &res_table->nh_buckets[bucket_index];
	bucket->nh_flags &= ~(RTNH_F_OFFLOAD | RTNH_F_TRAP);
	अगर (offload)
		bucket->nh_flags |= RTNH_F_OFFLOAD;
	अगर (trap)
		bucket->nh_flags |= RTNH_F_TRAP;

out:
	rcu_पढ़ो_unlock();
पूर्ण
EXPORT_SYMBOL(nexthop_bucket_set_hw_flags);

व्योम nexthop_res_grp_activity_update(काष्ठा net *net, u32 id, u16 num_buckets,
				     अचिन्हित दीर्घ *activity)
अणु
	काष्ठा nh_res_table *res_table;
	काष्ठा nexthop *nexthop;
	काष्ठा nh_group *nhg;
	u16 i;

	rcu_पढ़ो_lock();

	nexthop = nexthop_find_by_id(net, id);
	अगर (!nexthop || !nexthop->is_group)
		जाओ out;

	nhg = rcu_dereference(nexthop->nh_grp);
	अगर (!nhg->resilient)
		जाओ out;

	/* Instead of silently ignoring some buckets, demand that the sizes
	 * be the same.
	 */
	res_table = rcu_dereference(nhg->res_table);
	अगर (num_buckets != res_table->num_nh_buckets)
		जाओ out;

	क्रम (i = 0; i < num_buckets; i++) अणु
		अगर (test_bit(i, activity))
			nh_res_bucket_set_busy(&res_table->nh_buckets[i]);
	पूर्ण

out:
	rcu_पढ़ो_unlock();
पूर्ण
EXPORT_SYMBOL(nexthop_res_grp_activity_update);

अटल व्योम __net_निकास nexthop_net_निकास(काष्ठा net *net)
अणु
	rtnl_lock();
	flush_all_nexthops(net);
	rtnl_unlock();
	kमुक्त(net->nexthop.devhash);
पूर्ण

अटल पूर्णांक __net_init nexthop_net_init(काष्ठा net *net)
अणु
	माप_प्रकार sz = माप(काष्ठा hlist_head) * NH_DEV_HASHSIZE;

	net->nexthop.rb_root = RB_ROOT;
	net->nexthop.devhash = kzalloc(sz, GFP_KERNEL);
	अगर (!net->nexthop.devhash)
		वापस -ENOMEM;
	BLOCKING_INIT_NOTIFIER_HEAD(&net->nexthop.notअगरier_chain);

	वापस 0;
पूर्ण

अटल काष्ठा pernet_operations nexthop_net_ops = अणु
	.init = nexthop_net_init,
	.निकास = nexthop_net_निकास,
पूर्ण;

अटल पूर्णांक __init nexthop_init(व्योम)
अणु
	रेजिस्टर_pernet_subsys(&nexthop_net_ops);

	रेजिस्टर_netdevice_notअगरier(&nh_netdev_notअगरier);

	rtnl_रेजिस्टर(PF_UNSPEC, RTM_NEWNEXTHOP, rपंचांग_new_nexthop, शून्य, 0);
	rtnl_रेजिस्टर(PF_UNSPEC, RTM_DELNEXTHOP, rपंचांग_del_nexthop, शून्य, 0);
	rtnl_रेजिस्टर(PF_UNSPEC, RTM_GETNEXTHOP, rपंचांग_get_nexthop,
		      rपंचांग_dump_nexthop, 0);

	rtnl_रेजिस्टर(PF_INET, RTM_NEWNEXTHOP, rपंचांग_new_nexthop, शून्य, 0);
	rtnl_रेजिस्टर(PF_INET, RTM_GETNEXTHOP, शून्य, rपंचांग_dump_nexthop, 0);

	rtnl_रेजिस्टर(PF_INET6, RTM_NEWNEXTHOP, rपंचांग_new_nexthop, शून्य, 0);
	rtnl_रेजिस्टर(PF_INET6, RTM_GETNEXTHOP, शून्य, rपंचांग_dump_nexthop, 0);

	rtnl_रेजिस्टर(PF_UNSPEC, RTM_GETNEXTHOPBUCKET, rपंचांग_get_nexthop_bucket,
		      rपंचांग_dump_nexthop_bucket, 0);

	वापस 0;
पूर्ण
subsys_initcall(nexthop_init);
