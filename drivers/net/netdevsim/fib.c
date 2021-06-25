<शैली गुरु>
/*
 * Copyright (c) 2018 Cumulus Networks. All rights reserved.
 * Copyright (c) 2018 David Ahern <dsa@cumulusnetworks.com>
 *
 * This software is licensed under the GNU General License Version 2,
 * June 1991 as shown in the file COPYING in the top-level directory of this
 * source tree.
 *
 * THE COPYRIGHT HOLDERS AND/OR OTHER PARTIES PROVIDE THE PROGRAM "AS IS"
 * WITHOUT WARRANTY OF ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING,
 * BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
 * FOR A PARTICULAR PURPOSE. THE ENTIRE RISK AS TO THE QUALITY AND PERFORMANCE
 * OF THE PROGRAM IS WITH YOU. SHOULD THE PROGRAM PROVE DEFECTIVE, YOU ASSUME
 * THE COST OF ALL NECESSARY SERVICING, REPAIR OR CORRECTION.
 */

#समावेश <linux/biपंचांगap.h>
#समावेश <linux/in6.h>
#समावेश <linux/kernel.h>
#समावेश <linux/list.h>
#समावेश <linux/rhashtable.h>
#समावेश <linux/spinlock_types.h>
#समावेश <linux/types.h>
#समावेश <net/fib_notअगरier.h>
#समावेश <net/ip_fib.h>
#समावेश <net/ip6_fib.h>
#समावेश <net/fib_rules.h>
#समावेश <net/net_namespace.h>
#समावेश <net/nexthop.h>
#समावेश <linux/debugfs.h>

#समावेश "netdevsim.h"

काष्ठा nsim_fib_entry अणु
	u64 max;
	atomic64_t num;
पूर्ण;

काष्ठा nsim_per_fib_data अणु
	काष्ठा nsim_fib_entry fib;
	काष्ठा nsim_fib_entry rules;
पूर्ण;

काष्ठा nsim_fib_data अणु
	काष्ठा notअगरier_block fib_nb;
	काष्ठा nsim_per_fib_data ipv4;
	काष्ठा nsim_per_fib_data ipv6;
	काष्ठा nsim_fib_entry nexthops;
	काष्ठा rhashtable fib_rt_ht;
	काष्ठा list_head fib_rt_list;
	काष्ठा mutex fib_lock; /* Protects FIB HT and list */
	काष्ठा notअगरier_block nexthop_nb;
	काष्ठा rhashtable nexthop_ht;
	काष्ठा devlink *devlink;
	काष्ठा work_काष्ठा fib_event_work;
	काष्ठा list_head fib_event_queue;
	spinlock_t fib_event_queue_lock; /* Protects fib event queue list */
	काष्ठा mutex nh_lock; /* Protects NH HT */
	काष्ठा dentry *ddir;
	bool fail_route_offload;
	bool fail_res_nexthop_group_replace;
	bool fail_nexthop_bucket_replace;
पूर्ण;

काष्ठा nsim_fib_rt_key अणु
	अचिन्हित अक्षर addr[माप(काष्ठा in6_addr)];
	अचिन्हित अक्षर prefix_len;
	पूर्णांक family;
	u32 tb_id;
पूर्ण;

काष्ठा nsim_fib_rt अणु
	काष्ठा nsim_fib_rt_key key;
	काष्ठा rhash_head ht_node;
	काष्ठा list_head list;	/* Member of fib_rt_list */
पूर्ण;

काष्ठा nsim_fib4_rt अणु
	काष्ठा nsim_fib_rt common;
	काष्ठा fib_info *fi;
	u8 tos;
	u8 type;
पूर्ण;

काष्ठा nsim_fib6_rt अणु
	काष्ठा nsim_fib_rt common;
	काष्ठा list_head nh_list;
	अचिन्हित पूर्णांक nhs;
पूर्ण;

काष्ठा nsim_fib6_rt_nh अणु
	काष्ठा list_head list;	/* Member of nh_list */
	काष्ठा fib6_info *rt;
पूर्ण;

काष्ठा nsim_fib6_event अणु
	काष्ठा fib6_info **rt_arr;
	अचिन्हित पूर्णांक nrt6;
पूर्ण;

काष्ठा nsim_fib_event अणु
	काष्ठा list_head list; /* node in fib queue */
	जोड़ अणु
		काष्ठा fib_entry_notअगरier_info fen_info;
		काष्ठा nsim_fib6_event fib6_event;
	पूर्ण;
	काष्ठा nsim_fib_data *data;
	अचिन्हित दीर्घ event;
	पूर्णांक family;
पूर्ण;

अटल स्थिर काष्ठा rhashtable_params nsim_fib_rt_ht_params = अणु
	.key_offset = दुरत्व(काष्ठा nsim_fib_rt, key),
	.head_offset = दुरत्व(काष्ठा nsim_fib_rt, ht_node),
	.key_len = माप(काष्ठा nsim_fib_rt_key),
	.स्वतःmatic_shrinking = true,
पूर्ण;

काष्ठा nsim_nexthop अणु
	काष्ठा rhash_head ht_node;
	u64 occ;
	u32 id;
	bool is_resilient;
पूर्ण;

अटल स्थिर काष्ठा rhashtable_params nsim_nexthop_ht_params = अणु
	.key_offset = दुरत्व(काष्ठा nsim_nexthop, id),
	.head_offset = दुरत्व(काष्ठा nsim_nexthop, ht_node),
	.key_len = माप(u32),
	.स्वतःmatic_shrinking = true,
पूर्ण;

u64 nsim_fib_get_val(काष्ठा nsim_fib_data *fib_data,
		     क्रमागत nsim_resource_id res_id, bool max)
अणु
	काष्ठा nsim_fib_entry *entry;

	चयन (res_id) अणु
	हाल NSIM_RESOURCE_IPV4_FIB:
		entry = &fib_data->ipv4.fib;
		अवरोध;
	हाल NSIM_RESOURCE_IPV4_FIB_RULES:
		entry = &fib_data->ipv4.rules;
		अवरोध;
	हाल NSIM_RESOURCE_IPV6_FIB:
		entry = &fib_data->ipv6.fib;
		अवरोध;
	हाल NSIM_RESOURCE_IPV6_FIB_RULES:
		entry = &fib_data->ipv6.rules;
		अवरोध;
	हाल NSIM_RESOURCE_NEXTHOPS:
		entry = &fib_data->nexthops;
		अवरोध;
	शेष:
		वापस 0;
	पूर्ण

	वापस max ? entry->max : atomic64_पढ़ो(&entry->num);
पूर्ण

अटल व्योम nsim_fib_set_max(काष्ठा nsim_fib_data *fib_data,
			     क्रमागत nsim_resource_id res_id, u64 val)
अणु
	काष्ठा nsim_fib_entry *entry;

	चयन (res_id) अणु
	हाल NSIM_RESOURCE_IPV4_FIB:
		entry = &fib_data->ipv4.fib;
		अवरोध;
	हाल NSIM_RESOURCE_IPV4_FIB_RULES:
		entry = &fib_data->ipv4.rules;
		अवरोध;
	हाल NSIM_RESOURCE_IPV6_FIB:
		entry = &fib_data->ipv6.fib;
		अवरोध;
	हाल NSIM_RESOURCE_IPV6_FIB_RULES:
		entry = &fib_data->ipv6.rules;
		अवरोध;
	हाल NSIM_RESOURCE_NEXTHOPS:
		entry = &fib_data->nexthops;
		अवरोध;
	शेष:
		WARN_ON(1);
		वापस;
	पूर्ण
	entry->max = val;
पूर्ण

अटल पूर्णांक nsim_fib_rule_account(काष्ठा nsim_fib_entry *entry, bool add,
				 काष्ठा netlink_ext_ack *extack)
अणु
	पूर्णांक err = 0;

	अगर (add) अणु
		अगर (!atomic64_add_unless(&entry->num, 1, entry->max)) अणु
			err = -ENOSPC;
			NL_SET_ERR_MSG_MOD(extack, "Exceeded number of supported fib rule entries");
		पूर्ण
	पूर्ण अन्यथा अणु
		atomic64_dec_अगर_positive(&entry->num);
	पूर्ण

	वापस err;
पूर्ण

अटल पूर्णांक nsim_fib_rule_event(काष्ठा nsim_fib_data *data,
			       काष्ठा fib_notअगरier_info *info, bool add)
अणु
	काष्ठा netlink_ext_ack *extack = info->extack;
	पूर्णांक err = 0;

	चयन (info->family) अणु
	हाल AF_INET:
		err = nsim_fib_rule_account(&data->ipv4.rules, add, extack);
		अवरोध;
	हाल AF_INET6:
		err = nsim_fib_rule_account(&data->ipv6.rules, add, extack);
		अवरोध;
	पूर्ण

	वापस err;
पूर्ण

अटल पूर्णांक nsim_fib_account(काष्ठा nsim_fib_entry *entry, bool add)
अणु
	पूर्णांक err = 0;

	अगर (add) अणु
		अगर (!atomic64_add_unless(&entry->num, 1, entry->max))
			err = -ENOSPC;
	पूर्ण अन्यथा अणु
		atomic64_dec_अगर_positive(&entry->num);
	पूर्ण

	वापस err;
पूर्ण

अटल व्योम nsim_fib_rt_init(काष्ठा nsim_fib_data *data,
			     काष्ठा nsim_fib_rt *fib_rt, स्थिर व्योम *addr,
			     माप_प्रकार addr_len, अचिन्हित पूर्णांक prefix_len,
			     पूर्णांक family, u32 tb_id)
अणु
	स_नकल(fib_rt->key.addr, addr, addr_len);
	fib_rt->key.prefix_len = prefix_len;
	fib_rt->key.family = family;
	fib_rt->key.tb_id = tb_id;
	list_add(&fib_rt->list, &data->fib_rt_list);
पूर्ण

अटल व्योम nsim_fib_rt_fini(काष्ठा nsim_fib_rt *fib_rt)
अणु
	list_del(&fib_rt->list);
पूर्ण

अटल काष्ठा nsim_fib_rt *nsim_fib_rt_lookup(काष्ठा rhashtable *fib_rt_ht,
					      स्थिर व्योम *addr, माप_प्रकार addr_len,
					      अचिन्हित पूर्णांक prefix_len,
					      पूर्णांक family, u32 tb_id)
अणु
	काष्ठा nsim_fib_rt_key key;

	स_रखो(&key, 0, माप(key));
	स_नकल(key.addr, addr, addr_len);
	key.prefix_len = prefix_len;
	key.family = family;
	key.tb_id = tb_id;

	वापस rhashtable_lookup_fast(fib_rt_ht, &key, nsim_fib_rt_ht_params);
पूर्ण

अटल काष्ठा nsim_fib4_rt *
nsim_fib4_rt_create(काष्ठा nsim_fib_data *data,
		    काष्ठा fib_entry_notअगरier_info *fen_info)
अणु
	काष्ठा nsim_fib4_rt *fib4_rt;

	fib4_rt = kzalloc(माप(*fib4_rt), GFP_KERNEL);
	अगर (!fib4_rt)
		वापस शून्य;

	nsim_fib_rt_init(data, &fib4_rt->common, &fen_info->dst, माप(u32),
			 fen_info->dst_len, AF_INET, fen_info->tb_id);

	fib4_rt->fi = fen_info->fi;
	fib_info_hold(fib4_rt->fi);
	fib4_rt->tos = fen_info->tos;
	fib4_rt->type = fen_info->type;

	वापस fib4_rt;
पूर्ण

अटल व्योम nsim_fib4_rt_destroy(काष्ठा nsim_fib4_rt *fib4_rt)
अणु
	fib_info_put(fib4_rt->fi);
	nsim_fib_rt_fini(&fib4_rt->common);
	kमुक्त(fib4_rt);
पूर्ण

अटल काष्ठा nsim_fib4_rt *
nsim_fib4_rt_lookup(काष्ठा rhashtable *fib_rt_ht,
		    स्थिर काष्ठा fib_entry_notअगरier_info *fen_info)
अणु
	काष्ठा nsim_fib_rt *fib_rt;

	fib_rt = nsim_fib_rt_lookup(fib_rt_ht, &fen_info->dst, माप(u32),
				    fen_info->dst_len, AF_INET,
				    fen_info->tb_id);
	अगर (!fib_rt)
		वापस शून्य;

	वापस container_of(fib_rt, काष्ठा nsim_fib4_rt, common);
पूर्ण

अटल व्योम
nsim_fib4_rt_offload_failed_flag_set(काष्ठा net *net,
				     काष्ठा fib_entry_notअगरier_info *fen_info)
अणु
	u32 *p_dst = (u32 *)&fen_info->dst;
	काष्ठा fib_rt_info fri;

	fri.fi = fen_info->fi;
	fri.tb_id = fen_info->tb_id;
	fri.dst = cpu_to_be32(*p_dst);
	fri.dst_len = fen_info->dst_len;
	fri.tos = fen_info->tos;
	fri.type = fen_info->type;
	fri.offload = false;
	fri.trap = false;
	fri.offload_failed = true;
	fib_alias_hw_flags_set(net, &fri);
पूर्ण

अटल व्योम nsim_fib4_rt_hw_flags_set(काष्ठा net *net,
				      स्थिर काष्ठा nsim_fib4_rt *fib4_rt,
				      bool trap)
अणु
	u32 *p_dst = (u32 *) fib4_rt->common.key.addr;
	पूर्णांक dst_len = fib4_rt->common.key.prefix_len;
	काष्ठा fib_rt_info fri;

	fri.fi = fib4_rt->fi;
	fri.tb_id = fib4_rt->common.key.tb_id;
	fri.dst = cpu_to_be32(*p_dst);
	fri.dst_len = dst_len;
	fri.tos = fib4_rt->tos;
	fri.type = fib4_rt->type;
	fri.offload = false;
	fri.trap = trap;
	fri.offload_failed = false;
	fib_alias_hw_flags_set(net, &fri);
पूर्ण

अटल पूर्णांक nsim_fib4_rt_add(काष्ठा nsim_fib_data *data,
			    काष्ठा nsim_fib4_rt *fib4_rt)
अणु
	काष्ठा net *net = devlink_net(data->devlink);
	पूर्णांक err;

	err = rhashtable_insert_fast(&data->fib_rt_ht,
				     &fib4_rt->common.ht_node,
				     nsim_fib_rt_ht_params);
	अगर (err)
		जाओ err_fib_dismiss;

	/* Simulate hardware programming latency. */
	msleep(1);
	nsim_fib4_rt_hw_flags_set(net, fib4_rt, true);

	वापस 0;

err_fib_dismiss:
	/* Drop the accounting that was increased from the notअगरication
	 * context when FIB_EVENT_ENTRY_REPLACE was triggered.
	 */
	nsim_fib_account(&data->ipv4.fib, false);
	वापस err;
पूर्ण

अटल पूर्णांक nsim_fib4_rt_replace(काष्ठा nsim_fib_data *data,
				काष्ठा nsim_fib4_rt *fib4_rt,
				काष्ठा nsim_fib4_rt *fib4_rt_old)
अणु
	काष्ठा net *net = devlink_net(data->devlink);
	पूर्णांक err;

	/* We are replacing a route, so need to हटाओ the accounting which
	 * was increased when FIB_EVENT_ENTRY_REPLACE was triggered.
	 */
	err = nsim_fib_account(&data->ipv4.fib, false);
	अगर (err)
		वापस err;
	err = rhashtable_replace_fast(&data->fib_rt_ht,
				      &fib4_rt_old->common.ht_node,
				      &fib4_rt->common.ht_node,
				      nsim_fib_rt_ht_params);
	अगर (err)
		वापस err;

	msleep(1);
	nsim_fib4_rt_hw_flags_set(net, fib4_rt, true);

	nsim_fib4_rt_hw_flags_set(net, fib4_rt_old, false);
	nsim_fib4_rt_destroy(fib4_rt_old);

	वापस 0;
पूर्ण

अटल पूर्णांक nsim_fib4_rt_insert(काष्ठा nsim_fib_data *data,
			       काष्ठा fib_entry_notअगरier_info *fen_info)
अणु
	काष्ठा nsim_fib4_rt *fib4_rt, *fib4_rt_old;
	पूर्णांक err;

	अगर (data->fail_route_offload) अणु
		/* For testing purposes, user set debugfs fail_route_offload
		 * value to true. Simulate hardware programming latency and then
		 * fail.
		 */
		msleep(1);
		वापस -EINVAL;
	पूर्ण

	fib4_rt = nsim_fib4_rt_create(data, fen_info);
	अगर (!fib4_rt)
		वापस -ENOMEM;

	fib4_rt_old = nsim_fib4_rt_lookup(&data->fib_rt_ht, fen_info);
	अगर (!fib4_rt_old)
		err = nsim_fib4_rt_add(data, fib4_rt);
	अन्यथा
		err = nsim_fib4_rt_replace(data, fib4_rt, fib4_rt_old);

	अगर (err)
		nsim_fib4_rt_destroy(fib4_rt);

	वापस err;
पूर्ण

अटल व्योम nsim_fib4_rt_हटाओ(काष्ठा nsim_fib_data *data,
				स्थिर काष्ठा fib_entry_notअगरier_info *fen_info)
अणु
	काष्ठा nsim_fib4_rt *fib4_rt;

	fib4_rt = nsim_fib4_rt_lookup(&data->fib_rt_ht, fen_info);
	अगर (!fib4_rt)
		वापस;

	rhashtable_हटाओ_fast(&data->fib_rt_ht, &fib4_rt->common.ht_node,
			       nsim_fib_rt_ht_params);
	nsim_fib4_rt_destroy(fib4_rt);
पूर्ण

अटल पूर्णांक nsim_fib4_event(काष्ठा nsim_fib_data *data,
			   काष्ठा fib_entry_notअगरier_info *fen_info,
			   अचिन्हित दीर्घ event)
अणु
	पूर्णांक err = 0;

	चयन (event) अणु
	हाल FIB_EVENT_ENTRY_REPLACE:
		err = nsim_fib4_rt_insert(data, fen_info);
		अगर (err) अणु
			काष्ठा net *net = devlink_net(data->devlink);

			nsim_fib4_rt_offload_failed_flag_set(net, fen_info);
		पूर्ण
		अवरोध;
	हाल FIB_EVENT_ENTRY_DEL:
		nsim_fib4_rt_हटाओ(data, fen_info);
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	वापस err;
पूर्ण

अटल काष्ठा nsim_fib6_rt_nh *
nsim_fib6_rt_nh_find(स्थिर काष्ठा nsim_fib6_rt *fib6_rt,
		     स्थिर काष्ठा fib6_info *rt)
अणु
	काष्ठा nsim_fib6_rt_nh *fib6_rt_nh;

	list_क्रम_each_entry(fib6_rt_nh, &fib6_rt->nh_list, list) अणु
		अगर (fib6_rt_nh->rt == rt)
			वापस fib6_rt_nh;
	पूर्ण

	वापस शून्य;
पूर्ण

अटल पूर्णांक nsim_fib6_rt_nh_add(काष्ठा nsim_fib6_rt *fib6_rt,
			       काष्ठा fib6_info *rt)
अणु
	काष्ठा nsim_fib6_rt_nh *fib6_rt_nh;

	fib6_rt_nh = kzalloc(माप(*fib6_rt_nh), GFP_KERNEL);
	अगर (!fib6_rt_nh)
		वापस -ENOMEM;

	fib6_info_hold(rt);
	fib6_rt_nh->rt = rt;
	list_add_tail(&fib6_rt_nh->list, &fib6_rt->nh_list);
	fib6_rt->nhs++;

	वापस 0;
पूर्ण

#अगर IS_ENABLED(CONFIG_IPV6)
अटल व्योम nsim_rt6_release(काष्ठा fib6_info *rt)
अणु
	fib6_info_release(rt);
पूर्ण
#अन्यथा
अटल व्योम nsim_rt6_release(काष्ठा fib6_info *rt)
अणु
पूर्ण
#पूर्ण_अगर

अटल व्योम nsim_fib6_rt_nh_del(काष्ठा nsim_fib6_rt *fib6_rt,
				स्थिर काष्ठा fib6_info *rt)
अणु
	काष्ठा nsim_fib6_rt_nh *fib6_rt_nh;

	fib6_rt_nh = nsim_fib6_rt_nh_find(fib6_rt, rt);
	अगर (!fib6_rt_nh)
		वापस;

	fib6_rt->nhs--;
	list_del(&fib6_rt_nh->list);
	nsim_rt6_release(fib6_rt_nh->rt);
	kमुक्त(fib6_rt_nh);
पूर्ण

अटल काष्ठा nsim_fib6_rt *
nsim_fib6_rt_create(काष्ठा nsim_fib_data *data,
		    काष्ठा fib6_info **rt_arr, अचिन्हित पूर्णांक nrt6)
अणु
	काष्ठा fib6_info *rt = rt_arr[0];
	काष्ठा nsim_fib6_rt *fib6_rt;
	पूर्णांक i = 0;
	पूर्णांक err;

	fib6_rt = kzalloc(माप(*fib6_rt), GFP_KERNEL);
	अगर (!fib6_rt)
		वापस ERR_PTR(-ENOMEM);

	nsim_fib_rt_init(data, &fib6_rt->common, &rt->fib6_dst.addr,
			 माप(rt->fib6_dst.addr), rt->fib6_dst.plen, AF_INET6,
			 rt->fib6_table->tb6_id);

	/* We consider a multipath IPv6 route as one entry, but it can be made
	 * up from several fib6_info काष्ठाs (one क्रम each nexthop), so we
	 * add them all to the same list under the entry.
	 */
	INIT_LIST_HEAD(&fib6_rt->nh_list);

	क्रम (i = 0; i < nrt6; i++) अणु
		err = nsim_fib6_rt_nh_add(fib6_rt, rt_arr[i]);
		अगर (err)
			जाओ err_fib6_rt_nh_del;
	पूर्ण

	वापस fib6_rt;

err_fib6_rt_nh_del:
	क्रम (i--; i >= 0; i--) अणु
		nsim_fib6_rt_nh_del(fib6_rt, rt_arr[i]);
	पूर्ण
	nsim_fib_rt_fini(&fib6_rt->common);
	kमुक्त(fib6_rt);
	वापस ERR_PTR(err);
पूर्ण

अटल व्योम nsim_fib6_rt_destroy(काष्ठा nsim_fib6_rt *fib6_rt)
अणु
	काष्ठा nsim_fib6_rt_nh *iter, *पंचांगp;

	list_क्रम_each_entry_safe(iter, पंचांगp, &fib6_rt->nh_list, list)
		nsim_fib6_rt_nh_del(fib6_rt, iter->rt);
	WARN_ON_ONCE(!list_empty(&fib6_rt->nh_list));
	nsim_fib_rt_fini(&fib6_rt->common);
	kमुक्त(fib6_rt);
पूर्ण

अटल काष्ठा nsim_fib6_rt *
nsim_fib6_rt_lookup(काष्ठा rhashtable *fib_rt_ht, स्थिर काष्ठा fib6_info *rt)
अणु
	काष्ठा nsim_fib_rt *fib_rt;

	fib_rt = nsim_fib_rt_lookup(fib_rt_ht, &rt->fib6_dst.addr,
				    माप(rt->fib6_dst.addr),
				    rt->fib6_dst.plen, AF_INET6,
				    rt->fib6_table->tb6_id);
	अगर (!fib_rt)
		वापस शून्य;

	वापस container_of(fib_rt, काष्ठा nsim_fib6_rt, common);
पूर्ण

अटल पूर्णांक nsim_fib6_rt_append(काष्ठा nsim_fib_data *data,
			       काष्ठा nsim_fib6_event *fib6_event)
अणु
	काष्ठा fib6_info *rt = fib6_event->rt_arr[0];
	काष्ठा nsim_fib6_rt *fib6_rt;
	पूर्णांक i, err;

	अगर (data->fail_route_offload) अणु
		/* For testing purposes, user set debugfs fail_route_offload
		 * value to true. Simulate hardware programming latency and then
		 * fail.
		 */
		msleep(1);
		वापस -EINVAL;
	पूर्ण

	fib6_rt = nsim_fib6_rt_lookup(&data->fib_rt_ht, rt);
	अगर (!fib6_rt)
		वापस -EINVAL;

	क्रम (i = 0; i < fib6_event->nrt6; i++) अणु
		err = nsim_fib6_rt_nh_add(fib6_rt, fib6_event->rt_arr[i]);
		अगर (err)
			जाओ err_fib6_rt_nh_del;

		fib6_event->rt_arr[i]->trap = true;
	पूर्ण

	वापस 0;

err_fib6_rt_nh_del:
	क्रम (i--; i >= 0; i--) अणु
		fib6_event->rt_arr[i]->trap = false;
		nsim_fib6_rt_nh_del(fib6_rt, fib6_event->rt_arr[i]);
	पूर्ण
	वापस err;
पूर्ण

#अगर IS_ENABLED(CONFIG_IPV6)
अटल व्योम nsim_fib6_rt_offload_failed_flag_set(काष्ठा nsim_fib_data *data,
						 काष्ठा fib6_info **rt_arr,
						 अचिन्हित पूर्णांक nrt6)

अणु
	काष्ठा net *net = devlink_net(data->devlink);
	पूर्णांक i;

	क्रम (i = 0; i < nrt6; i++)
		fib6_info_hw_flags_set(net, rt_arr[i], false, false, true);
पूर्ण
#अन्यथा
अटल व्योम nsim_fib6_rt_offload_failed_flag_set(काष्ठा nsim_fib_data *data,
						 काष्ठा fib6_info **rt_arr,
						 अचिन्हित पूर्णांक nrt6)
अणु
पूर्ण
#पूर्ण_अगर

#अगर IS_ENABLED(CONFIG_IPV6)
अटल व्योम nsim_fib6_rt_hw_flags_set(काष्ठा nsim_fib_data *data,
				      स्थिर काष्ठा nsim_fib6_rt *fib6_rt,
				      bool trap)
अणु
	काष्ठा net *net = devlink_net(data->devlink);
	काष्ठा nsim_fib6_rt_nh *fib6_rt_nh;

	list_क्रम_each_entry(fib6_rt_nh, &fib6_rt->nh_list, list)
		fib6_info_hw_flags_set(net, fib6_rt_nh->rt, false, trap, false);
पूर्ण
#अन्यथा
अटल व्योम nsim_fib6_rt_hw_flags_set(काष्ठा nsim_fib_data *data,
				      स्थिर काष्ठा nsim_fib6_rt *fib6_rt,
				      bool trap)
अणु
पूर्ण
#पूर्ण_अगर

अटल पूर्णांक nsim_fib6_rt_add(काष्ठा nsim_fib_data *data,
			    काष्ठा nsim_fib6_rt *fib6_rt)
अणु
	पूर्णांक err;

	err = rhashtable_insert_fast(&data->fib_rt_ht,
				     &fib6_rt->common.ht_node,
				     nsim_fib_rt_ht_params);

	अगर (err)
		जाओ err_fib_dismiss;

	msleep(1);
	nsim_fib6_rt_hw_flags_set(data, fib6_rt, true);

	वापस 0;

err_fib_dismiss:
	/* Drop the accounting that was increased from the notअगरication
	 * context when FIB_EVENT_ENTRY_REPLACE was triggered.
	 */
	nsim_fib_account(&data->ipv6.fib, false);
	वापस err;
पूर्ण

अटल पूर्णांक nsim_fib6_rt_replace(काष्ठा nsim_fib_data *data,
				काष्ठा nsim_fib6_rt *fib6_rt,
				काष्ठा nsim_fib6_rt *fib6_rt_old)
अणु
	पूर्णांक err;

	/* We are replacing a route, so need to हटाओ the accounting which
	 * was increased when FIB_EVENT_ENTRY_REPLACE was triggered.
	 */
	err = nsim_fib_account(&data->ipv6.fib, false);
	अगर (err)
		वापस err;

	err = rhashtable_replace_fast(&data->fib_rt_ht,
				      &fib6_rt_old->common.ht_node,
				      &fib6_rt->common.ht_node,
				      nsim_fib_rt_ht_params);

	अगर (err)
		वापस err;

	msleep(1);
	nsim_fib6_rt_hw_flags_set(data, fib6_rt, true);

	nsim_fib6_rt_hw_flags_set(data, fib6_rt_old, false);
	nsim_fib6_rt_destroy(fib6_rt_old);

	वापस 0;
पूर्ण

अटल पूर्णांक nsim_fib6_rt_insert(काष्ठा nsim_fib_data *data,
			       काष्ठा nsim_fib6_event *fib6_event)
अणु
	काष्ठा fib6_info *rt = fib6_event->rt_arr[0];
	काष्ठा nsim_fib6_rt *fib6_rt, *fib6_rt_old;
	पूर्णांक err;

	अगर (data->fail_route_offload) अणु
		/* For testing purposes, user set debugfs fail_route_offload
		 * value to true. Simulate hardware programming latency and then
		 * fail.
		 */
		msleep(1);
		वापस -EINVAL;
	पूर्ण

	fib6_rt = nsim_fib6_rt_create(data, fib6_event->rt_arr,
				      fib6_event->nrt6);
	अगर (IS_ERR(fib6_rt))
		वापस PTR_ERR(fib6_rt);

	fib6_rt_old = nsim_fib6_rt_lookup(&data->fib_rt_ht, rt);
	अगर (!fib6_rt_old)
		err = nsim_fib6_rt_add(data, fib6_rt);
	अन्यथा
		err = nsim_fib6_rt_replace(data, fib6_rt, fib6_rt_old);

	अगर (err)
		nsim_fib6_rt_destroy(fib6_rt);

	वापस err;
पूर्ण

अटल व्योम nsim_fib6_rt_हटाओ(काष्ठा nsim_fib_data *data,
				काष्ठा nsim_fib6_event *fib6_event)
अणु
	काष्ठा fib6_info *rt = fib6_event->rt_arr[0];
	काष्ठा nsim_fib6_rt *fib6_rt;
	पूर्णांक i;

	/* Multipath routes are first added to the FIB trie and only then
	 * notअगरied. If we vetoed the addition, we will get a delete
	 * notअगरication क्रम a route we करो not have. Thereक्रमe, करो not warn अगर
	 * route was not found.
	 */
	fib6_rt = nsim_fib6_rt_lookup(&data->fib_rt_ht, rt);
	अगर (!fib6_rt)
		वापस;

	/* If not all the nexthops are deleted, then only reduce the nexthop
	 * group.
	 */
	अगर (fib6_event->nrt6 != fib6_rt->nhs) अणु
		क्रम (i = 0; i < fib6_event->nrt6; i++)
			nsim_fib6_rt_nh_del(fib6_rt, fib6_event->rt_arr[i]);
		वापस;
	पूर्ण

	rhashtable_हटाओ_fast(&data->fib_rt_ht, &fib6_rt->common.ht_node,
			       nsim_fib_rt_ht_params);
	nsim_fib6_rt_destroy(fib6_rt);
पूर्ण

अटल पूर्णांक nsim_fib6_event_init(काष्ठा nsim_fib6_event *fib6_event,
				काष्ठा fib6_entry_notअगरier_info *fen6_info)
अणु
	काष्ठा fib6_info *rt = fen6_info->rt;
	काष्ठा fib6_info **rt_arr;
	काष्ठा fib6_info *iter;
	अचिन्हित पूर्णांक nrt6;
	पूर्णांक i = 0;

	nrt6 = fen6_info->nsiblings + 1;

	rt_arr = kसुस्मृति(nrt6, माप(काष्ठा fib6_info *), GFP_ATOMIC);
	अगर (!rt_arr)
		वापस -ENOMEM;

	fib6_event->rt_arr = rt_arr;
	fib6_event->nrt6 = nrt6;

	rt_arr[0] = rt;
	fib6_info_hold(rt);

	अगर (!fen6_info->nsiblings)
		वापस 0;

	list_क्रम_each_entry(iter, &rt->fib6_siblings, fib6_siblings) अणु
		अगर (i == fen6_info->nsiblings)
			अवरोध;

		rt_arr[i + 1] = iter;
		fib6_info_hold(iter);
		i++;
	पूर्ण
	WARN_ON_ONCE(i != fen6_info->nsiblings);

	वापस 0;
पूर्ण

अटल व्योम nsim_fib6_event_fini(काष्ठा nsim_fib6_event *fib6_event)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < fib6_event->nrt6; i++)
		nsim_rt6_release(fib6_event->rt_arr[i]);
	kमुक्त(fib6_event->rt_arr);
पूर्ण

अटल पूर्णांक nsim_fib6_event(काष्ठा nsim_fib_data *data,
			   काष्ठा nsim_fib6_event *fib6_event,
			   अचिन्हित दीर्घ event)
अणु
	पूर्णांक err;

	अगर (fib6_event->rt_arr[0]->fib6_src.plen)
		वापस 0;

	चयन (event) अणु
	हाल FIB_EVENT_ENTRY_REPLACE:
		err = nsim_fib6_rt_insert(data, fib6_event);
		अगर (err)
			जाओ err_rt_offload_failed_flag_set;
		अवरोध;
	हाल FIB_EVENT_ENTRY_APPEND:
		err = nsim_fib6_rt_append(data, fib6_event);
		अगर (err)
			जाओ err_rt_offload_failed_flag_set;
		अवरोध;
	हाल FIB_EVENT_ENTRY_DEL:
		nsim_fib6_rt_हटाओ(data, fib6_event);
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	वापस 0;

err_rt_offload_failed_flag_set:
	nsim_fib6_rt_offload_failed_flag_set(data, fib6_event->rt_arr,
					     fib6_event->nrt6);
	वापस err;
पूर्ण

अटल व्योम nsim_fib_event(काष्ठा nsim_fib_event *fib_event)
अणु
	चयन (fib_event->family) अणु
	हाल AF_INET:
		nsim_fib4_event(fib_event->data, &fib_event->fen_info,
				fib_event->event);
		fib_info_put(fib_event->fen_info.fi);
		अवरोध;
	हाल AF_INET6:
		nsim_fib6_event(fib_event->data, &fib_event->fib6_event,
				fib_event->event);
		nsim_fib6_event_fini(&fib_event->fib6_event);
		अवरोध;
	पूर्ण
पूर्ण

अटल पूर्णांक nsim_fib4_prepare_event(काष्ठा fib_notअगरier_info *info,
				   काष्ठा nsim_fib_event *fib_event,
				   अचिन्हित दीर्घ event)
अणु
	काष्ठा nsim_fib_data *data = fib_event->data;
	काष्ठा fib_entry_notअगरier_info *fen_info;
	काष्ठा netlink_ext_ack *extack;
	पूर्णांक err = 0;

	fen_info = container_of(info, काष्ठा fib_entry_notअगरier_info,
				info);
	fib_event->fen_info = *fen_info;
	extack = info->extack;

	चयन (event) अणु
	हाल FIB_EVENT_ENTRY_REPLACE:
		err = nsim_fib_account(&data->ipv4.fib, true);
		अगर (err) अणु
			NL_SET_ERR_MSG_MOD(extack, "Exceeded number of supported fib entries");
			वापस err;
		पूर्ण
		अवरोध;
	हाल FIB_EVENT_ENTRY_DEL:
		nsim_fib_account(&data->ipv4.fib, false);
		अवरोध;
	पूर्ण

	/* Take reference on fib_info to prevent it from being
	 * मुक्तd जबतक event is queued. Release it afterwards.
	 */
	fib_info_hold(fib_event->fen_info.fi);

	वापस 0;
पूर्ण

अटल पूर्णांक nsim_fib6_prepare_event(काष्ठा fib_notअगरier_info *info,
				   काष्ठा nsim_fib_event *fib_event,
				   अचिन्हित दीर्घ event)
अणु
	काष्ठा nsim_fib_data *data = fib_event->data;
	काष्ठा fib6_entry_notअगरier_info *fen6_info;
	काष्ठा netlink_ext_ack *extack;
	पूर्णांक err = 0;

	fen6_info = container_of(info, काष्ठा fib6_entry_notअगरier_info,
				 info);

	err = nsim_fib6_event_init(&fib_event->fib6_event, fen6_info);
	अगर (err)
		वापस err;

	extack = info->extack;
	चयन (event) अणु
	हाल FIB_EVENT_ENTRY_REPLACE:
		err = nsim_fib_account(&data->ipv6.fib, true);
		अगर (err) अणु
			NL_SET_ERR_MSG_MOD(extack, "Exceeded number of supported fib entries");
			जाओ err_fib6_event_fini;
		पूर्ण
		अवरोध;
	हाल FIB_EVENT_ENTRY_DEL:
		nsim_fib_account(&data->ipv6.fib, false);
		अवरोध;
	पूर्ण

	वापस 0;

err_fib6_event_fini:
	nsim_fib6_event_fini(&fib_event->fib6_event);
	वापस err;
पूर्ण

अटल पूर्णांक nsim_fib_event_schedule_work(काष्ठा nsim_fib_data *data,
					काष्ठा fib_notअगरier_info *info,
					अचिन्हित दीर्घ event)
अणु
	काष्ठा nsim_fib_event *fib_event;
	पूर्णांक err;

	अगर (info->family != AF_INET && info->family != AF_INET6)
		/* netdevsim करोes not support 'RTNL_FAMILY_IP6MR' and
		 * 'RTNL_FAMILY_IPMR' and should ignore them.
		 */
		वापस NOTIFY_DONE;

	fib_event = kzalloc(माप(*fib_event), GFP_ATOMIC);
	अगर (!fib_event)
		वापस NOTIFY_BAD;

	fib_event->data = data;
	fib_event->event = event;
	fib_event->family = info->family;

	चयन (info->family) अणु
	हाल AF_INET:
		err = nsim_fib4_prepare_event(info, fib_event, event);
		अवरोध;
	हाल AF_INET6:
		err = nsim_fib6_prepare_event(info, fib_event, event);
		अवरोध;
	पूर्ण

	अगर (err)
		जाओ err_fib_prepare_event;

	/* Enqueue the event and trigger the work */
	spin_lock_bh(&data->fib_event_queue_lock);
	list_add_tail(&fib_event->list, &data->fib_event_queue);
	spin_unlock_bh(&data->fib_event_queue_lock);
	schedule_work(&data->fib_event_work);

	वापस NOTIFY_DONE;

err_fib_prepare_event:
	kमुक्त(fib_event);
	वापस NOTIFY_BAD;
पूर्ण

अटल पूर्णांक nsim_fib_event_nb(काष्ठा notअगरier_block *nb, अचिन्हित दीर्घ event,
			     व्योम *ptr)
अणु
	काष्ठा nsim_fib_data *data = container_of(nb, काष्ठा nsim_fib_data,
						  fib_nb);
	काष्ठा fib_notअगरier_info *info = ptr;
	पूर्णांक err;

	चयन (event) अणु
	हाल FIB_EVENT_RULE_ADD:
	हाल FIB_EVENT_RULE_DEL:
		err = nsim_fib_rule_event(data, info,
					  event == FIB_EVENT_RULE_ADD);
		वापस notअगरier_from_त्रुटि_सं(err);
	हाल FIB_EVENT_ENTRY_REPLACE:
	हाल FIB_EVENT_ENTRY_APPEND:
	हाल FIB_EVENT_ENTRY_DEL:
		वापस nsim_fib_event_schedule_work(data, info, event);
	पूर्ण

	वापस NOTIFY_DONE;
पूर्ण

अटल व्योम nsim_fib4_rt_मुक्त(काष्ठा nsim_fib_rt *fib_rt,
			      काष्ठा nsim_fib_data *data)
अणु
	काष्ठा devlink *devlink = data->devlink;
	काष्ठा nsim_fib4_rt *fib4_rt;

	fib4_rt = container_of(fib_rt, काष्ठा nsim_fib4_rt, common);
	nsim_fib4_rt_hw_flags_set(devlink_net(devlink), fib4_rt, false);
	nsim_fib_account(&data->ipv4.fib, false);
	nsim_fib4_rt_destroy(fib4_rt);
पूर्ण

अटल व्योम nsim_fib6_rt_मुक्त(काष्ठा nsim_fib_rt *fib_rt,
			      काष्ठा nsim_fib_data *data)
अणु
	काष्ठा nsim_fib6_rt *fib6_rt;

	fib6_rt = container_of(fib_rt, काष्ठा nsim_fib6_rt, common);
	nsim_fib6_rt_hw_flags_set(data, fib6_rt, false);
	nsim_fib_account(&data->ipv6.fib, false);
	nsim_fib6_rt_destroy(fib6_rt);
पूर्ण

अटल व्योम nsim_fib_rt_मुक्त(व्योम *ptr, व्योम *arg)
अणु
	काष्ठा nsim_fib_rt *fib_rt = ptr;
	काष्ठा nsim_fib_data *data = arg;

	चयन (fib_rt->key.family) अणु
	हाल AF_INET:
		nsim_fib4_rt_मुक्त(fib_rt, data);
		अवरोध;
	हाल AF_INET6:
		nsim_fib6_rt_मुक्त(fib_rt, data);
		अवरोध;
	शेष:
		WARN_ON_ONCE(1);
	पूर्ण
पूर्ण

/* inconsistent dump, trying again */
अटल व्योम nsim_fib_dump_inconsistent(काष्ठा notअगरier_block *nb)
अणु
	काष्ठा nsim_fib_data *data = container_of(nb, काष्ठा nsim_fib_data,
						  fib_nb);
	काष्ठा nsim_fib_rt *fib_rt, *fib_rt_पंचांगp;

	/* Flush the work to make sure there is no race with notअगरications. */
	flush_work(&data->fib_event_work);

	/* The notअगरier block is still not रेजिस्टरed, so we करो not need to
	 * take any locks here.
	 */
	list_क्रम_each_entry_safe(fib_rt, fib_rt_पंचांगp, &data->fib_rt_list, list) अणु
		rhashtable_हटाओ_fast(&data->fib_rt_ht, &fib_rt->ht_node,
				       nsim_fib_rt_ht_params);
		nsim_fib_rt_मुक्त(fib_rt, data);
	पूर्ण

	atomic64_set(&data->ipv4.rules.num, 0ULL);
	atomic64_set(&data->ipv6.rules.num, 0ULL);
पूर्ण

अटल काष्ठा nsim_nexthop *nsim_nexthop_create(काष्ठा nsim_fib_data *data,
						काष्ठा nh_notअगरier_info *info)
अणु
	काष्ठा nsim_nexthop *nexthop;
	u64 occ = 0;
	पूर्णांक i;

	nexthop = kzalloc(माप(*nexthop), GFP_KERNEL);
	अगर (!nexthop)
		वापस ERR_PTR(-ENOMEM);

	nexthop->id = info->id;

	/* Determine the number of nexthop entries the new nexthop will
	 * occupy.
	 */

	चयन (info->type) अणु
	हाल NH_NOTIFIER_INFO_TYPE_SINGLE:
		occ = 1;
		अवरोध;
	हाल NH_NOTIFIER_INFO_TYPE_GRP:
		क्रम (i = 0; i < info->nh_grp->num_nh; i++)
			occ += info->nh_grp->nh_entries[i].weight;
		अवरोध;
	हाल NH_NOTIFIER_INFO_TYPE_RES_TABLE:
		occ = info->nh_res_table->num_nh_buckets;
		nexthop->is_resilient = true;
		अवरोध;
	शेष:
		NL_SET_ERR_MSG_MOD(info->extack, "Unsupported nexthop type");
		kमुक्त(nexthop);
		वापस ERR_PTR(-EOPNOTSUPP);
	पूर्ण

	nexthop->occ = occ;
	वापस nexthop;
पूर्ण

अटल व्योम nsim_nexthop_destroy(काष्ठा nsim_nexthop *nexthop)
अणु
	kमुक्त(nexthop);
पूर्ण

अटल पूर्णांक nsim_nexthop_account(काष्ठा nsim_fib_data *data, u64 occ,
				bool add, काष्ठा netlink_ext_ack *extack)
अणु
	पूर्णांक i, err = 0;

	अगर (add) अणु
		क्रम (i = 0; i < occ; i++)
			अगर (!atomic64_add_unless(&data->nexthops.num, 1,
						 data->nexthops.max)) अणु
				err = -ENOSPC;
				NL_SET_ERR_MSG_MOD(extack, "Exceeded number of supported nexthops");
				जाओ err_num_decrease;
			पूर्ण
	पूर्ण अन्यथा अणु
		अगर (WARN_ON(occ > atomic64_पढ़ो(&data->nexthops.num)))
			वापस -EINVAL;
		atomic64_sub(occ, &data->nexthops.num);
	पूर्ण

	वापस err;

err_num_decrease:
	atomic64_sub(i, &data->nexthops.num);
	वापस err;

पूर्ण

अटल व्योम nsim_nexthop_hw_flags_set(काष्ठा net *net,
				      स्थिर काष्ठा nsim_nexthop *nexthop,
				      bool trap)
अणु
	पूर्णांक i;

	nexthop_set_hw_flags(net, nexthop->id, false, trap);

	अगर (!nexthop->is_resilient)
		वापस;

	क्रम (i = 0; i < nexthop->occ; i++)
		nexthop_bucket_set_hw_flags(net, nexthop->id, i, false, trap);
पूर्ण

अटल पूर्णांक nsim_nexthop_add(काष्ठा nsim_fib_data *data,
			    काष्ठा nsim_nexthop *nexthop,
			    काष्ठा netlink_ext_ack *extack)
अणु
	काष्ठा net *net = devlink_net(data->devlink);
	पूर्णांक err;

	err = nsim_nexthop_account(data, nexthop->occ, true, extack);
	अगर (err)
		वापस err;

	err = rhashtable_insert_fast(&data->nexthop_ht, &nexthop->ht_node,
				     nsim_nexthop_ht_params);
	अगर (err) अणु
		NL_SET_ERR_MSG_MOD(extack, "Failed to insert nexthop");
		जाओ err_nexthop_dismiss;
	पूर्ण

	nsim_nexthop_hw_flags_set(net, nexthop, true);

	वापस 0;

err_nexthop_dismiss:
	nsim_nexthop_account(data, nexthop->occ, false, extack);
	वापस err;
पूर्ण

अटल पूर्णांक nsim_nexthop_replace(काष्ठा nsim_fib_data *data,
				काष्ठा nsim_nexthop *nexthop,
				काष्ठा nsim_nexthop *nexthop_old,
				काष्ठा netlink_ext_ack *extack)
अणु
	काष्ठा net *net = devlink_net(data->devlink);
	पूर्णांक err;

	err = nsim_nexthop_account(data, nexthop->occ, true, extack);
	अगर (err)
		वापस err;

	err = rhashtable_replace_fast(&data->nexthop_ht,
				      &nexthop_old->ht_node, &nexthop->ht_node,
				      nsim_nexthop_ht_params);
	अगर (err) अणु
		NL_SET_ERR_MSG_MOD(extack, "Failed to replace nexthop");
		जाओ err_nexthop_dismiss;
	पूर्ण

	nsim_nexthop_hw_flags_set(net, nexthop, true);
	nsim_nexthop_account(data, nexthop_old->occ, false, extack);
	nsim_nexthop_destroy(nexthop_old);

	वापस 0;

err_nexthop_dismiss:
	nsim_nexthop_account(data, nexthop->occ, false, extack);
	वापस err;
पूर्ण

अटल पूर्णांक nsim_nexthop_insert(काष्ठा nsim_fib_data *data,
			       काष्ठा nh_notअगरier_info *info)
अणु
	काष्ठा nsim_nexthop *nexthop, *nexthop_old;
	पूर्णांक err;

	nexthop = nsim_nexthop_create(data, info);
	अगर (IS_ERR(nexthop))
		वापस PTR_ERR(nexthop);

	nexthop_old = rhashtable_lookup_fast(&data->nexthop_ht, &info->id,
					     nsim_nexthop_ht_params);
	अगर (!nexthop_old)
		err = nsim_nexthop_add(data, nexthop, info->extack);
	अन्यथा
		err = nsim_nexthop_replace(data, nexthop, nexthop_old,
					   info->extack);

	अगर (err)
		nsim_nexthop_destroy(nexthop);

	वापस err;
पूर्ण

अटल व्योम nsim_nexthop_हटाओ(काष्ठा nsim_fib_data *data,
				काष्ठा nh_notअगरier_info *info)
अणु
	काष्ठा nsim_nexthop *nexthop;

	nexthop = rhashtable_lookup_fast(&data->nexthop_ht, &info->id,
					 nsim_nexthop_ht_params);
	अगर (!nexthop)
		वापस;

	rhashtable_हटाओ_fast(&data->nexthop_ht, &nexthop->ht_node,
			       nsim_nexthop_ht_params);
	nsim_nexthop_account(data, nexthop->occ, false, info->extack);
	nsim_nexthop_destroy(nexthop);
पूर्ण

अटल पूर्णांक nsim_nexthop_res_table_pre_replace(काष्ठा nsim_fib_data *data,
					      काष्ठा nh_notअगरier_info *info)
अणु
	अगर (data->fail_res_nexthop_group_replace) अणु
		NL_SET_ERR_MSG_MOD(info->extack, "Failed to replace a resilient nexthop group");
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक nsim_nexthop_bucket_replace(काष्ठा nsim_fib_data *data,
				       काष्ठा nh_notअगरier_info *info)
अणु
	अगर (data->fail_nexthop_bucket_replace) अणु
		NL_SET_ERR_MSG_MOD(info->extack, "Failed to replace nexthop bucket");
		वापस -EINVAL;
	पूर्ण

	nexthop_bucket_set_hw_flags(info->net, info->id,
				    info->nh_res_bucket->bucket_index,
				    false, true);

	वापस 0;
पूर्ण

अटल पूर्णांक nsim_nexthop_event_nb(काष्ठा notअगरier_block *nb, अचिन्हित दीर्घ event,
				 व्योम *ptr)
अणु
	काष्ठा nsim_fib_data *data = container_of(nb, काष्ठा nsim_fib_data,
						  nexthop_nb);
	काष्ठा nh_notअगरier_info *info = ptr;
	पूर्णांक err = 0;

	mutex_lock(&data->nh_lock);
	चयन (event) अणु
	हाल NEXTHOP_EVENT_REPLACE:
		err = nsim_nexthop_insert(data, info);
		अवरोध;
	हाल NEXTHOP_EVENT_DEL:
		nsim_nexthop_हटाओ(data, info);
		अवरोध;
	हाल NEXTHOP_EVENT_RES_TABLE_PRE_REPLACE:
		err = nsim_nexthop_res_table_pre_replace(data, info);
		अवरोध;
	हाल NEXTHOP_EVENT_BUCKET_REPLACE:
		err = nsim_nexthop_bucket_replace(data, info);
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	mutex_unlock(&data->nh_lock);
	वापस notअगरier_from_त्रुटि_सं(err);
पूर्ण

अटल व्योम nsim_nexthop_मुक्त(व्योम *ptr, व्योम *arg)
अणु
	काष्ठा nsim_nexthop *nexthop = ptr;
	काष्ठा nsim_fib_data *data = arg;
	काष्ठा net *net;

	net = devlink_net(data->devlink);
	nsim_nexthop_hw_flags_set(net, nexthop, false);
	nsim_nexthop_account(data, nexthop->occ, false, शून्य);
	nsim_nexthop_destroy(nexthop);
पूर्ण

अटल sमाप_प्रकार nsim_nexthop_bucket_activity_ग_लिखो(काष्ठा file *file,
						  स्थिर अक्षर __user *user_buf,
						  माप_प्रकार size, loff_t *ppos)
अणु
	काष्ठा nsim_fib_data *data = file->निजी_data;
	काष्ठा net *net = devlink_net(data->devlink);
	काष्ठा nsim_nexthop *nexthop;
	अचिन्हित दीर्घ *activity;
	loff_t pos = *ppos;
	u16 bucket_index;
	अक्षर buf[128];
	पूर्णांक err = 0;
	u32 nhid;

	अगर (pos != 0)
		वापस -EINVAL;
	अगर (size > माप(buf))
		वापस -EINVAL;
	अगर (copy_from_user(buf, user_buf, size))
		वापस -EFAULT;
	अगर (माला_पूछो(buf, "%u %hu", &nhid, &bucket_index) != 2)
		वापस -EINVAL;

	rtnl_lock();

	nexthop = rhashtable_lookup_fast(&data->nexthop_ht, &nhid,
					 nsim_nexthop_ht_params);
	अगर (!nexthop || !nexthop->is_resilient ||
	    bucket_index >= nexthop->occ) अणु
		err = -EINVAL;
		जाओ out;
	पूर्ण

	activity = biपंचांगap_zalloc(nexthop->occ, GFP_KERNEL);
	अगर (!activity) अणु
		err = -ENOMEM;
		जाओ out;
	पूर्ण

	biपंचांगap_set(activity, bucket_index, 1);
	nexthop_res_grp_activity_update(net, nhid, nexthop->occ, activity);
	biपंचांगap_मुक्त(activity);

out:
	rtnl_unlock();

	*ppos = size;
	वापस err ?: size;
पूर्ण

अटल स्थिर काष्ठा file_operations nsim_nexthop_bucket_activity_fops = अणु
	.खोलो = simple_खोलो,
	.ग_लिखो = nsim_nexthop_bucket_activity_ग_लिखो,
	.llseek = no_llseek,
	.owner = THIS_MODULE,
पूर्ण;

अटल u64 nsim_fib_ipv4_resource_occ_get(व्योम *priv)
अणु
	काष्ठा nsim_fib_data *data = priv;

	वापस nsim_fib_get_val(data, NSIM_RESOURCE_IPV4_FIB, false);
पूर्ण

अटल u64 nsim_fib_ipv4_rules_res_occ_get(व्योम *priv)
अणु
	काष्ठा nsim_fib_data *data = priv;

	वापस nsim_fib_get_val(data, NSIM_RESOURCE_IPV4_FIB_RULES, false);
पूर्ण

अटल u64 nsim_fib_ipv6_resource_occ_get(व्योम *priv)
अणु
	काष्ठा nsim_fib_data *data = priv;

	वापस nsim_fib_get_val(data, NSIM_RESOURCE_IPV6_FIB, false);
पूर्ण

अटल u64 nsim_fib_ipv6_rules_res_occ_get(व्योम *priv)
अणु
	काष्ठा nsim_fib_data *data = priv;

	वापस nsim_fib_get_val(data, NSIM_RESOURCE_IPV6_FIB_RULES, false);
पूर्ण

अटल u64 nsim_fib_nexthops_res_occ_get(व्योम *priv)
अणु
	काष्ठा nsim_fib_data *data = priv;

	वापस nsim_fib_get_val(data, NSIM_RESOURCE_NEXTHOPS, false);
पूर्ण

अटल व्योम nsim_fib_set_max_all(काष्ठा nsim_fib_data *data,
				 काष्ठा devlink *devlink)
अणु
	क्रमागत nsim_resource_id res_ids[] = अणु
		NSIM_RESOURCE_IPV4_FIB, NSIM_RESOURCE_IPV4_FIB_RULES,
		NSIM_RESOURCE_IPV6_FIB, NSIM_RESOURCE_IPV6_FIB_RULES,
		NSIM_RESOURCE_NEXTHOPS,
	पूर्ण;
	पूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(res_ids); i++) अणु
		पूर्णांक err;
		u64 val;

		err = devlink_resource_size_get(devlink, res_ids[i], &val);
		अगर (err)
			val = (u64) -1;
		nsim_fib_set_max(data, res_ids[i], val);
	पूर्ण
पूर्ण

अटल व्योम nsim_fib_event_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा nsim_fib_data *data = container_of(work, काष्ठा nsim_fib_data,
						  fib_event_work);
	काष्ठा nsim_fib_event *fib_event, *next_fib_event;

	LIST_HEAD(fib_event_queue);

	spin_lock_bh(&data->fib_event_queue_lock);
	list_splice_init(&data->fib_event_queue, &fib_event_queue);
	spin_unlock_bh(&data->fib_event_queue_lock);

	mutex_lock(&data->fib_lock);
	list_क्रम_each_entry_safe(fib_event, next_fib_event, &fib_event_queue,
				 list) अणु
		nsim_fib_event(fib_event);
		list_del(&fib_event->list);
		kमुक्त(fib_event);
		cond_resched();
	पूर्ण
	mutex_unlock(&data->fib_lock);
पूर्ण

अटल पूर्णांक
nsim_fib_debugfs_init(काष्ठा nsim_fib_data *data, काष्ठा nsim_dev *nsim_dev)
अणु
	data->ddir = debugfs_create_dir("fib", nsim_dev->ddir);
	अगर (IS_ERR(data->ddir))
		वापस PTR_ERR(data->ddir);

	data->fail_route_offload = false;
	debugfs_create_bool("fail_route_offload", 0600, data->ddir,
			    &data->fail_route_offload);

	data->fail_res_nexthop_group_replace = false;
	debugfs_create_bool("fail_res_nexthop_group_replace", 0600, data->ddir,
			    &data->fail_res_nexthop_group_replace);

	data->fail_nexthop_bucket_replace = false;
	debugfs_create_bool("fail_nexthop_bucket_replace", 0600, data->ddir,
			    &data->fail_nexthop_bucket_replace);

	debugfs_create_file("nexthop_bucket_activity", 0200, data->ddir,
			    data, &nsim_nexthop_bucket_activity_fops);
	वापस 0;
पूर्ण

अटल व्योम nsim_fib_debugfs_निकास(काष्ठा nsim_fib_data *data)
अणु
	debugfs_हटाओ_recursive(data->ddir);
पूर्ण

काष्ठा nsim_fib_data *nsim_fib_create(काष्ठा devlink *devlink,
				      काष्ठा netlink_ext_ack *extack)
अणु
	काष्ठा nsim_fib_data *data;
	काष्ठा nsim_dev *nsim_dev;
	पूर्णांक err;

	data = kzalloc(माप(*data), GFP_KERNEL);
	अगर (!data)
		वापस ERR_PTR(-ENOMEM);
	data->devlink = devlink;

	nsim_dev = devlink_priv(devlink);
	err = nsim_fib_debugfs_init(data, nsim_dev);
	अगर (err)
		जाओ err_data_मुक्त;

	mutex_init(&data->nh_lock);
	err = rhashtable_init(&data->nexthop_ht, &nsim_nexthop_ht_params);
	अगर (err)
		जाओ err_debugfs_निकास;

	mutex_init(&data->fib_lock);
	INIT_LIST_HEAD(&data->fib_rt_list);
	err = rhashtable_init(&data->fib_rt_ht, &nsim_fib_rt_ht_params);
	अगर (err)
		जाओ err_rhashtable_nexthop_destroy;

	INIT_WORK(&data->fib_event_work, nsim_fib_event_work);
	INIT_LIST_HEAD(&data->fib_event_queue);
	spin_lock_init(&data->fib_event_queue_lock);

	nsim_fib_set_max_all(data, devlink);

	data->nexthop_nb.notअगरier_call = nsim_nexthop_event_nb;
	err = रेजिस्टर_nexthop_notअगरier(devlink_net(devlink), &data->nexthop_nb,
					extack);
	अगर (err) अणु
		pr_err("Failed to register nexthop notifier\n");
		जाओ err_rhashtable_fib_destroy;
	पूर्ण

	data->fib_nb.notअगरier_call = nsim_fib_event_nb;
	err = रेजिस्टर_fib_notअगरier(devlink_net(devlink), &data->fib_nb,
				    nsim_fib_dump_inconsistent, extack);
	अगर (err) अणु
		pr_err("Failed to register fib notifier\n");
		जाओ err_nexthop_nb_unरेजिस्टर;
	पूर्ण

	devlink_resource_occ_get_रेजिस्टर(devlink,
					  NSIM_RESOURCE_IPV4_FIB,
					  nsim_fib_ipv4_resource_occ_get,
					  data);
	devlink_resource_occ_get_रेजिस्टर(devlink,
					  NSIM_RESOURCE_IPV4_FIB_RULES,
					  nsim_fib_ipv4_rules_res_occ_get,
					  data);
	devlink_resource_occ_get_रेजिस्टर(devlink,
					  NSIM_RESOURCE_IPV6_FIB,
					  nsim_fib_ipv6_resource_occ_get,
					  data);
	devlink_resource_occ_get_रेजिस्टर(devlink,
					  NSIM_RESOURCE_IPV6_FIB_RULES,
					  nsim_fib_ipv6_rules_res_occ_get,
					  data);
	devlink_resource_occ_get_रेजिस्टर(devlink,
					  NSIM_RESOURCE_NEXTHOPS,
					  nsim_fib_nexthops_res_occ_get,
					  data);
	वापस data;

err_nexthop_nb_unरेजिस्टर:
	unरेजिस्टर_nexthop_notअगरier(devlink_net(devlink), &data->nexthop_nb);
err_rhashtable_fib_destroy:
	flush_work(&data->fib_event_work);
	rhashtable_मुक्त_and_destroy(&data->fib_rt_ht, nsim_fib_rt_मुक्त,
				    data);
err_rhashtable_nexthop_destroy:
	rhashtable_मुक्त_and_destroy(&data->nexthop_ht, nsim_nexthop_मुक्त,
				    data);
	mutex_destroy(&data->fib_lock);
err_debugfs_निकास:
	mutex_destroy(&data->nh_lock);
	nsim_fib_debugfs_निकास(data);
err_data_मुक्त:
	kमुक्त(data);
	वापस ERR_PTR(err);
पूर्ण

व्योम nsim_fib_destroy(काष्ठा devlink *devlink, काष्ठा nsim_fib_data *data)
अणु
	devlink_resource_occ_get_unरेजिस्टर(devlink,
					    NSIM_RESOURCE_NEXTHOPS);
	devlink_resource_occ_get_unरेजिस्टर(devlink,
					    NSIM_RESOURCE_IPV6_FIB_RULES);
	devlink_resource_occ_get_unरेजिस्टर(devlink,
					    NSIM_RESOURCE_IPV6_FIB);
	devlink_resource_occ_get_unरेजिस्टर(devlink,
					    NSIM_RESOURCE_IPV4_FIB_RULES);
	devlink_resource_occ_get_unरेजिस्टर(devlink,
					    NSIM_RESOURCE_IPV4_FIB);
	unरेजिस्टर_fib_notअगरier(devlink_net(devlink), &data->fib_nb);
	unरेजिस्टर_nexthop_notअगरier(devlink_net(devlink), &data->nexthop_nb);
	flush_work(&data->fib_event_work);
	rhashtable_मुक्त_and_destroy(&data->fib_rt_ht, nsim_fib_rt_मुक्त,
				    data);
	rhashtable_मुक्त_and_destroy(&data->nexthop_ht, nsim_nexthop_मुक्त,
				    data);
	WARN_ON_ONCE(!list_empty(&data->fib_event_queue));
	WARN_ON_ONCE(!list_empty(&data->fib_rt_list));
	mutex_destroy(&data->fib_lock);
	mutex_destroy(&data->nh_lock);
	nsim_fib_debugfs_निकास(data);
	kमुक्त(data);
पूर्ण
