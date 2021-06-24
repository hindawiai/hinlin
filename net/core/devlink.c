<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * net/core/devlink.c - Network physical/parent device Netlink पूर्णांकerface
 *
 * Heavily inspired by net/wireless/
 * Copyright (c) 2016 Mellanox Technologies. All rights reserved.
 * Copyright (c) 2016 Jiri Pirko <jiri@mellanox.com>
 */

#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/types.h>
#समावेश <linux/slab.h>
#समावेश <linux/gfp.h>
#समावेश <linux/device.h>
#समावेश <linux/list.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/refcount.h>
#समावेश <linux/workqueue.h>
#समावेश <linux/u64_stats_sync.h>
#समावेश <linux/समयkeeping.h>
#समावेश <rdma/ib_verbs.h>
#समावेश <net/netlink.h>
#समावेश <net/genetlink.h>
#समावेश <net/rtnetlink.h>
#समावेश <net/net_namespace.h>
#समावेश <net/sock.h>
#समावेश <net/devlink.h>
#घोषणा CREATE_TRACE_POINTS
#समावेश <trace/events/devlink.h>

अटल काष्ठा devlink_dpipe_field devlink_dpipe_fields_ethernet[] = अणु
	अणु
		.name = "destination mac",
		.id = DEVLINK_DPIPE_FIELD_ETHERNET_DST_MAC,
		.bitwidth = 48,
	पूर्ण,
पूर्ण;

काष्ठा devlink_dpipe_header devlink_dpipe_header_ethernet = अणु
	.name = "ethernet",
	.id = DEVLINK_DPIPE_HEADER_ETHERNET,
	.fields = devlink_dpipe_fields_ethernet,
	.fields_count = ARRAY_SIZE(devlink_dpipe_fields_ethernet),
	.global = true,
पूर्ण;
EXPORT_SYMBOL(devlink_dpipe_header_ethernet);

अटल काष्ठा devlink_dpipe_field devlink_dpipe_fields_ipv4[] = अणु
	अणु
		.name = "destination ip",
		.id = DEVLINK_DPIPE_FIELD_IPV4_DST_IP,
		.bitwidth = 32,
	पूर्ण,
पूर्ण;

काष्ठा devlink_dpipe_header devlink_dpipe_header_ipv4 = अणु
	.name = "ipv4",
	.id = DEVLINK_DPIPE_HEADER_IPV4,
	.fields = devlink_dpipe_fields_ipv4,
	.fields_count = ARRAY_SIZE(devlink_dpipe_fields_ipv4),
	.global = true,
पूर्ण;
EXPORT_SYMBOL(devlink_dpipe_header_ipv4);

अटल काष्ठा devlink_dpipe_field devlink_dpipe_fields_ipv6[] = अणु
	अणु
		.name = "destination ip",
		.id = DEVLINK_DPIPE_FIELD_IPV6_DST_IP,
		.bitwidth = 128,
	पूर्ण,
पूर्ण;

काष्ठा devlink_dpipe_header devlink_dpipe_header_ipv6 = अणु
	.name = "ipv6",
	.id = DEVLINK_DPIPE_HEADER_IPV6,
	.fields = devlink_dpipe_fields_ipv6,
	.fields_count = ARRAY_SIZE(devlink_dpipe_fields_ipv6),
	.global = true,
पूर्ण;
EXPORT_SYMBOL(devlink_dpipe_header_ipv6);

EXPORT_TRACEPOINT_SYMBOL_GPL(devlink_hwmsg);
EXPORT_TRACEPOINT_SYMBOL_GPL(devlink_hwerr);
EXPORT_TRACEPOINT_SYMBOL_GPL(devlink_trap_report);

अटल स्थिर काष्ठा nla_policy devlink_function_nl_policy[DEVLINK_PORT_FUNCTION_ATTR_MAX + 1] = अणु
	[DEVLINK_PORT_FUNCTION_ATTR_HW_ADDR] = अणु .type = NLA_BINARY पूर्ण,
	[DEVLINK_PORT_FN_ATTR_STATE] =
		NLA_POLICY_RANGE(NLA_U8, DEVLINK_PORT_FN_STATE_INACTIVE,
				 DEVLINK_PORT_FN_STATE_ACTIVE),
पूर्ण;

अटल LIST_HEAD(devlink_list);

/* devlink_mutex
 *
 * An overall lock guarding every operation coming from userspace.
 * It also guards devlink devices list and it is taken when
 * driver रेजिस्टरs/unरेजिस्टरs it.
 */
अटल DEFINE_MUTEX(devlink_mutex);

काष्ठा net *devlink_net(स्थिर काष्ठा devlink *devlink)
अणु
	वापस पढ़ो_pnet(&devlink->_net);
पूर्ण
EXPORT_SYMBOL_GPL(devlink_net);

अटल व्योम __devlink_net_set(काष्ठा devlink *devlink, काष्ठा net *net)
अणु
	ग_लिखो_pnet(&devlink->_net, net);
पूर्ण

व्योम devlink_net_set(काष्ठा devlink *devlink, काष्ठा net *net)
अणु
	अगर (WARN_ON(devlink->रेजिस्टरed))
		वापस;
	__devlink_net_set(devlink, net);
पूर्ण
EXPORT_SYMBOL_GPL(devlink_net_set);

अटल काष्ठा devlink *devlink_get_from_attrs(काष्ठा net *net,
					      काष्ठा nlattr **attrs)
अणु
	काष्ठा devlink *devlink;
	अक्षर *busname;
	अक्षर *devname;

	अगर (!attrs[DEVLINK_ATTR_BUS_NAME] || !attrs[DEVLINK_ATTR_DEV_NAME])
		वापस ERR_PTR(-EINVAL);

	busname = nla_data(attrs[DEVLINK_ATTR_BUS_NAME]);
	devname = nla_data(attrs[DEVLINK_ATTR_DEV_NAME]);

	lockdep_निश्चित_held(&devlink_mutex);

	list_क्रम_each_entry(devlink, &devlink_list, list) अणु
		अगर (म_भेद(devlink->dev->bus->name, busname) == 0 &&
		    म_भेद(dev_name(devlink->dev), devname) == 0 &&
		    net_eq(devlink_net(devlink), net))
			वापस devlink;
	पूर्ण

	वापस ERR_PTR(-ENODEV);
पूर्ण

अटल काष्ठा devlink *devlink_get_from_info(काष्ठा genl_info *info)
अणु
	वापस devlink_get_from_attrs(genl_info_net(info), info->attrs);
पूर्ण

अटल काष्ठा devlink_port *devlink_port_get_by_index(काष्ठा devlink *devlink,
						      अचिन्हित पूर्णांक port_index)
अणु
	काष्ठा devlink_port *devlink_port;

	list_क्रम_each_entry(devlink_port, &devlink->port_list, list) अणु
		अगर (devlink_port->index == port_index)
			वापस devlink_port;
	पूर्ण
	वापस शून्य;
पूर्ण

अटल bool devlink_port_index_exists(काष्ठा devlink *devlink,
				      अचिन्हित पूर्णांक port_index)
अणु
	वापस devlink_port_get_by_index(devlink, port_index);
पूर्ण

अटल काष्ठा devlink_port *devlink_port_get_from_attrs(काष्ठा devlink *devlink,
							काष्ठा nlattr **attrs)
अणु
	अगर (attrs[DEVLINK_ATTR_PORT_INDEX]) अणु
		u32 port_index = nla_get_u32(attrs[DEVLINK_ATTR_PORT_INDEX]);
		काष्ठा devlink_port *devlink_port;

		devlink_port = devlink_port_get_by_index(devlink, port_index);
		अगर (!devlink_port)
			वापस ERR_PTR(-ENODEV);
		वापस devlink_port;
	पूर्ण
	वापस ERR_PTR(-EINVAL);
पूर्ण

अटल काष्ठा devlink_port *devlink_port_get_from_info(काष्ठा devlink *devlink,
						       काष्ठा genl_info *info)
अणु
	वापस devlink_port_get_from_attrs(devlink, info->attrs);
पूर्ण

काष्ठा devlink_sb अणु
	काष्ठा list_head list;
	अचिन्हित पूर्णांक index;
	u32 size;
	u16 ingress_pools_count;
	u16 egress_pools_count;
	u16 ingress_tc_count;
	u16 egress_tc_count;
पूर्ण;

अटल u16 devlink_sb_pool_count(काष्ठा devlink_sb *devlink_sb)
अणु
	वापस devlink_sb->ingress_pools_count + devlink_sb->egress_pools_count;
पूर्ण

अटल काष्ठा devlink_sb *devlink_sb_get_by_index(काष्ठा devlink *devlink,
						  अचिन्हित पूर्णांक sb_index)
अणु
	काष्ठा devlink_sb *devlink_sb;

	list_क्रम_each_entry(devlink_sb, &devlink->sb_list, list) अणु
		अगर (devlink_sb->index == sb_index)
			वापस devlink_sb;
	पूर्ण
	वापस शून्य;
पूर्ण

अटल bool devlink_sb_index_exists(काष्ठा devlink *devlink,
				    अचिन्हित पूर्णांक sb_index)
अणु
	वापस devlink_sb_get_by_index(devlink, sb_index);
पूर्ण

अटल काष्ठा devlink_sb *devlink_sb_get_from_attrs(काष्ठा devlink *devlink,
						    काष्ठा nlattr **attrs)
अणु
	अगर (attrs[DEVLINK_ATTR_SB_INDEX]) अणु
		u32 sb_index = nla_get_u32(attrs[DEVLINK_ATTR_SB_INDEX]);
		काष्ठा devlink_sb *devlink_sb;

		devlink_sb = devlink_sb_get_by_index(devlink, sb_index);
		अगर (!devlink_sb)
			वापस ERR_PTR(-ENODEV);
		वापस devlink_sb;
	पूर्ण
	वापस ERR_PTR(-EINVAL);
पूर्ण

अटल काष्ठा devlink_sb *devlink_sb_get_from_info(काष्ठा devlink *devlink,
						   काष्ठा genl_info *info)
अणु
	वापस devlink_sb_get_from_attrs(devlink, info->attrs);
पूर्ण

अटल पूर्णांक devlink_sb_pool_index_get_from_attrs(काष्ठा devlink_sb *devlink_sb,
						काष्ठा nlattr **attrs,
						u16 *p_pool_index)
अणु
	u16 val;

	अगर (!attrs[DEVLINK_ATTR_SB_POOL_INDEX])
		वापस -EINVAL;

	val = nla_get_u16(attrs[DEVLINK_ATTR_SB_POOL_INDEX]);
	अगर (val >= devlink_sb_pool_count(devlink_sb))
		वापस -EINVAL;
	*p_pool_index = val;
	वापस 0;
पूर्ण

अटल पूर्णांक devlink_sb_pool_index_get_from_info(काष्ठा devlink_sb *devlink_sb,
					       काष्ठा genl_info *info,
					       u16 *p_pool_index)
अणु
	वापस devlink_sb_pool_index_get_from_attrs(devlink_sb, info->attrs,
						    p_pool_index);
पूर्ण

अटल पूर्णांक
devlink_sb_pool_type_get_from_attrs(काष्ठा nlattr **attrs,
				    क्रमागत devlink_sb_pool_type *p_pool_type)
अणु
	u8 val;

	अगर (!attrs[DEVLINK_ATTR_SB_POOL_TYPE])
		वापस -EINVAL;

	val = nla_get_u8(attrs[DEVLINK_ATTR_SB_POOL_TYPE]);
	अगर (val != DEVLINK_SB_POOL_TYPE_INGRESS &&
	    val != DEVLINK_SB_POOL_TYPE_EGRESS)
		वापस -EINVAL;
	*p_pool_type = val;
	वापस 0;
पूर्ण

अटल पूर्णांक
devlink_sb_pool_type_get_from_info(काष्ठा genl_info *info,
				   क्रमागत devlink_sb_pool_type *p_pool_type)
अणु
	वापस devlink_sb_pool_type_get_from_attrs(info->attrs, p_pool_type);
पूर्ण

अटल पूर्णांक
devlink_sb_th_type_get_from_attrs(काष्ठा nlattr **attrs,
				  क्रमागत devlink_sb_threshold_type *p_th_type)
अणु
	u8 val;

	अगर (!attrs[DEVLINK_ATTR_SB_POOL_THRESHOLD_TYPE])
		वापस -EINVAL;

	val = nla_get_u8(attrs[DEVLINK_ATTR_SB_POOL_THRESHOLD_TYPE]);
	अगर (val != DEVLINK_SB_THRESHOLD_TYPE_STATIC &&
	    val != DEVLINK_SB_THRESHOLD_TYPE_DYNAMIC)
		वापस -EINVAL;
	*p_th_type = val;
	वापस 0;
पूर्ण

अटल पूर्णांक
devlink_sb_th_type_get_from_info(काष्ठा genl_info *info,
				 क्रमागत devlink_sb_threshold_type *p_th_type)
अणु
	वापस devlink_sb_th_type_get_from_attrs(info->attrs, p_th_type);
पूर्ण

अटल पूर्णांक
devlink_sb_tc_index_get_from_attrs(काष्ठा devlink_sb *devlink_sb,
				   काष्ठा nlattr **attrs,
				   क्रमागत devlink_sb_pool_type pool_type,
				   u16 *p_tc_index)
अणु
	u16 val;

	अगर (!attrs[DEVLINK_ATTR_SB_TC_INDEX])
		वापस -EINVAL;

	val = nla_get_u16(attrs[DEVLINK_ATTR_SB_TC_INDEX]);
	अगर (pool_type == DEVLINK_SB_POOL_TYPE_INGRESS &&
	    val >= devlink_sb->ingress_tc_count)
		वापस -EINVAL;
	अगर (pool_type == DEVLINK_SB_POOL_TYPE_EGRESS &&
	    val >= devlink_sb->egress_tc_count)
		वापस -EINVAL;
	*p_tc_index = val;
	वापस 0;
पूर्ण

अटल पूर्णांक
devlink_sb_tc_index_get_from_info(काष्ठा devlink_sb *devlink_sb,
				  काष्ठा genl_info *info,
				  क्रमागत devlink_sb_pool_type pool_type,
				  u16 *p_tc_index)
अणु
	वापस devlink_sb_tc_index_get_from_attrs(devlink_sb, info->attrs,
						  pool_type, p_tc_index);
पूर्ण

काष्ठा devlink_region अणु
	काष्ठा devlink *devlink;
	काष्ठा devlink_port *port;
	काष्ठा list_head list;
	जोड़ अणु
		स्थिर काष्ठा devlink_region_ops *ops;
		स्थिर काष्ठा devlink_port_region_ops *port_ops;
	पूर्ण;
	काष्ठा list_head snapshot_list;
	u32 max_snapshots;
	u32 cur_snapshots;
	u64 size;
पूर्ण;

काष्ठा devlink_snapshot अणु
	काष्ठा list_head list;
	काष्ठा devlink_region *region;
	u8 *data;
	u32 id;
पूर्ण;

अटल काष्ठा devlink_region *
devlink_region_get_by_name(काष्ठा devlink *devlink, स्थिर अक्षर *region_name)
अणु
	काष्ठा devlink_region *region;

	list_क्रम_each_entry(region, &devlink->region_list, list)
		अगर (!म_भेद(region->ops->name, region_name))
			वापस region;

	वापस शून्य;
पूर्ण

अटल काष्ठा devlink_region *
devlink_port_region_get_by_name(काष्ठा devlink_port *port,
				स्थिर अक्षर *region_name)
अणु
	काष्ठा devlink_region *region;

	list_क्रम_each_entry(region, &port->region_list, list)
		अगर (!म_भेद(region->ops->name, region_name))
			वापस region;

	वापस शून्य;
पूर्ण

अटल काष्ठा devlink_snapshot *
devlink_region_snapshot_get_by_id(काष्ठा devlink_region *region, u32 id)
अणु
	काष्ठा devlink_snapshot *snapshot;

	list_क्रम_each_entry(snapshot, &region->snapshot_list, list)
		अगर (snapshot->id == id)
			वापस snapshot;

	वापस शून्य;
पूर्ण

#घोषणा DEVLINK_NL_FLAG_NEED_PORT		BIT(0)
#घोषणा DEVLINK_NL_FLAG_NEED_DEVLINK_OR_PORT	BIT(1)

/* The per devlink instance lock is taken by शेष in the pre-करोit
 * operation, yet several commands करो not require this. The global
 * devlink lock is taken and protects from disruption by user-calls.
 */
#घोषणा DEVLINK_NL_FLAG_NO_LOCK			BIT(2)

अटल पूर्णांक devlink_nl_pre_करोit(स्थिर काष्ठा genl_ops *ops,
			       काष्ठा sk_buff *skb, काष्ठा genl_info *info)
अणु
	काष्ठा devlink_port *devlink_port;
	काष्ठा devlink *devlink;
	पूर्णांक err;

	mutex_lock(&devlink_mutex);
	devlink = devlink_get_from_info(info);
	अगर (IS_ERR(devlink)) अणु
		mutex_unlock(&devlink_mutex);
		वापस PTR_ERR(devlink);
	पूर्ण
	अगर (~ops->पूर्णांकernal_flags & DEVLINK_NL_FLAG_NO_LOCK)
		mutex_lock(&devlink->lock);
	info->user_ptr[0] = devlink;
	अगर (ops->पूर्णांकernal_flags & DEVLINK_NL_FLAG_NEED_PORT) अणु
		devlink_port = devlink_port_get_from_info(devlink, info);
		अगर (IS_ERR(devlink_port)) अणु
			err = PTR_ERR(devlink_port);
			जाओ unlock;
		पूर्ण
		info->user_ptr[1] = devlink_port;
	पूर्ण अन्यथा अगर (ops->पूर्णांकernal_flags & DEVLINK_NL_FLAG_NEED_DEVLINK_OR_PORT) अणु
		devlink_port = devlink_port_get_from_info(devlink, info);
		अगर (!IS_ERR(devlink_port))
			info->user_ptr[1] = devlink_port;
	पूर्ण
	वापस 0;

unlock:
	अगर (~ops->पूर्णांकernal_flags & DEVLINK_NL_FLAG_NO_LOCK)
		mutex_unlock(&devlink->lock);
	mutex_unlock(&devlink_mutex);
	वापस err;
पूर्ण

अटल व्योम devlink_nl_post_करोit(स्थिर काष्ठा genl_ops *ops,
				 काष्ठा sk_buff *skb, काष्ठा genl_info *info)
अणु
	काष्ठा devlink *devlink;

	devlink = info->user_ptr[0];
	अगर (~ops->पूर्णांकernal_flags & DEVLINK_NL_FLAG_NO_LOCK)
		mutex_unlock(&devlink->lock);
	mutex_unlock(&devlink_mutex);
पूर्ण

अटल काष्ठा genl_family devlink_nl_family;

क्रमागत devlink_multicast_groups अणु
	DEVLINK_MCGRP_CONFIG,
पूर्ण;

अटल स्थिर काष्ठा genl_multicast_group devlink_nl_mcgrps[] = अणु
	[DEVLINK_MCGRP_CONFIG] = अणु .name = DEVLINK_GENL_MCGRP_CONFIG_NAME पूर्ण,
पूर्ण;

अटल पूर्णांक devlink_nl_put_handle(काष्ठा sk_buff *msg, काष्ठा devlink *devlink)
अणु
	अगर (nla_put_string(msg, DEVLINK_ATTR_BUS_NAME, devlink->dev->bus->name))
		वापस -EMSGSIZE;
	अगर (nla_put_string(msg, DEVLINK_ATTR_DEV_NAME, dev_name(devlink->dev)))
		वापस -EMSGSIZE;
	वापस 0;
पूर्ण

काष्ठा devlink_reload_combination अणु
	क्रमागत devlink_reload_action action;
	क्रमागत devlink_reload_limit limit;
पूर्ण;

अटल स्थिर काष्ठा devlink_reload_combination devlink_reload_invalid_combinations[] = अणु
	अणु
		/* can't reinitialize driver with no करोwn समय */
		.action = DEVLINK_RELOAD_ACTION_DRIVER_REINIT,
		.limit = DEVLINK_RELOAD_LIMIT_NO_RESET,
	पूर्ण,
पूर्ण;

अटल bool
devlink_reload_combination_is_invalid(क्रमागत devlink_reload_action action,
				      क्रमागत devlink_reload_limit limit)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(devlink_reload_invalid_combinations); i++)
		अगर (devlink_reload_invalid_combinations[i].action == action &&
		    devlink_reload_invalid_combinations[i].limit == limit)
			वापस true;
	वापस false;
पूर्ण

अटल bool
devlink_reload_action_is_supported(काष्ठा devlink *devlink, क्रमागत devlink_reload_action action)
अणु
	वापस test_bit(action, &devlink->ops->reload_actions);
पूर्ण

अटल bool
devlink_reload_limit_is_supported(काष्ठा devlink *devlink, क्रमागत devlink_reload_limit limit)
अणु
	वापस test_bit(limit, &devlink->ops->reload_limits);
पूर्ण

अटल पूर्णांक devlink_reload_stat_put(काष्ठा sk_buff *msg,
				   क्रमागत devlink_reload_limit limit, u32 value)
अणु
	काष्ठा nlattr *reload_stats_entry;

	reload_stats_entry = nla_nest_start(msg, DEVLINK_ATTR_RELOAD_STATS_ENTRY);
	अगर (!reload_stats_entry)
		वापस -EMSGSIZE;

	अगर (nla_put_u8(msg, DEVLINK_ATTR_RELOAD_STATS_LIMIT, limit) ||
	    nla_put_u32(msg, DEVLINK_ATTR_RELOAD_STATS_VALUE, value))
		जाओ nla_put_failure;
	nla_nest_end(msg, reload_stats_entry);
	वापस 0;

nla_put_failure:
	nla_nest_cancel(msg, reload_stats_entry);
	वापस -EMSGSIZE;
पूर्ण

अटल पूर्णांक devlink_reload_stats_put(काष्ठा sk_buff *msg, काष्ठा devlink *devlink, bool is_remote)
अणु
	काष्ठा nlattr *reload_stats_attr, *act_info, *act_stats;
	पूर्णांक i, j, stat_idx;
	u32 value;

	अगर (!is_remote)
		reload_stats_attr = nla_nest_start(msg, DEVLINK_ATTR_RELOAD_STATS);
	अन्यथा
		reload_stats_attr = nla_nest_start(msg, DEVLINK_ATTR_REMOTE_RELOAD_STATS);

	अगर (!reload_stats_attr)
		वापस -EMSGSIZE;

	क्रम (i = 0; i <= DEVLINK_RELOAD_ACTION_MAX; i++) अणु
		अगर ((!is_remote &&
		     !devlink_reload_action_is_supported(devlink, i)) ||
		    i == DEVLINK_RELOAD_ACTION_UNSPEC)
			जारी;
		act_info = nla_nest_start(msg, DEVLINK_ATTR_RELOAD_ACTION_INFO);
		अगर (!act_info)
			जाओ nla_put_failure;

		अगर (nla_put_u8(msg, DEVLINK_ATTR_RELOAD_ACTION, i))
			जाओ action_info_nest_cancel;
		act_stats = nla_nest_start(msg, DEVLINK_ATTR_RELOAD_ACTION_STATS);
		अगर (!act_stats)
			जाओ action_info_nest_cancel;

		क्रम (j = 0; j <= DEVLINK_RELOAD_LIMIT_MAX; j++) अणु
			/* Remote stats are shown even अगर not locally supported.
			 * Stats of actions with unspecअगरied limit are shown
			 * though drivers करोn't need to रेजिस्टर unspecअगरied
			 * limit.
			 */
			अगर ((!is_remote && j != DEVLINK_RELOAD_LIMIT_UNSPEC &&
			     !devlink_reload_limit_is_supported(devlink, j)) ||
			    devlink_reload_combination_is_invalid(i, j))
				जारी;

			stat_idx = j * __DEVLINK_RELOAD_ACTION_MAX + i;
			अगर (!is_remote)
				value = devlink->stats.reload_stats[stat_idx];
			अन्यथा
				value = devlink->stats.remote_reload_stats[stat_idx];
			अगर (devlink_reload_stat_put(msg, j, value))
				जाओ action_stats_nest_cancel;
		पूर्ण
		nla_nest_end(msg, act_stats);
		nla_nest_end(msg, act_info);
	पूर्ण
	nla_nest_end(msg, reload_stats_attr);
	वापस 0;

action_stats_nest_cancel:
	nla_nest_cancel(msg, act_stats);
action_info_nest_cancel:
	nla_nest_cancel(msg, act_info);
nla_put_failure:
	nla_nest_cancel(msg, reload_stats_attr);
	वापस -EMSGSIZE;
पूर्ण

अटल पूर्णांक devlink_nl_fill(काष्ठा sk_buff *msg, काष्ठा devlink *devlink,
			   क्रमागत devlink_command cmd, u32 portid,
			   u32 seq, पूर्णांक flags)
अणु
	काष्ठा nlattr *dev_stats;
	व्योम *hdr;

	hdr = genlmsg_put(msg, portid, seq, &devlink_nl_family, flags, cmd);
	अगर (!hdr)
		वापस -EMSGSIZE;

	अगर (devlink_nl_put_handle(msg, devlink))
		जाओ nla_put_failure;
	अगर (nla_put_u8(msg, DEVLINK_ATTR_RELOAD_FAILED, devlink->reload_failed))
		जाओ nla_put_failure;

	dev_stats = nla_nest_start(msg, DEVLINK_ATTR_DEV_STATS);
	अगर (!dev_stats)
		जाओ nla_put_failure;

	अगर (devlink_reload_stats_put(msg, devlink, false))
		जाओ dev_stats_nest_cancel;
	अगर (devlink_reload_stats_put(msg, devlink, true))
		जाओ dev_stats_nest_cancel;

	nla_nest_end(msg, dev_stats);
	genlmsg_end(msg, hdr);
	वापस 0;

dev_stats_nest_cancel:
	nla_nest_cancel(msg, dev_stats);
nla_put_failure:
	genlmsg_cancel(msg, hdr);
	वापस -EMSGSIZE;
पूर्ण

अटल व्योम devlink_notअगरy(काष्ठा devlink *devlink, क्रमागत devlink_command cmd)
अणु
	काष्ठा sk_buff *msg;
	पूर्णांक err;

	WARN_ON(cmd != DEVLINK_CMD_NEW && cmd != DEVLINK_CMD_DEL);

	msg = nlmsg_new(NLMSG_DEFAULT_SIZE, GFP_KERNEL);
	अगर (!msg)
		वापस;

	err = devlink_nl_fill(msg, devlink, cmd, 0, 0, 0);
	अगर (err) अणु
		nlmsg_मुक्त(msg);
		वापस;
	पूर्ण

	genlmsg_multicast_netns(&devlink_nl_family, devlink_net(devlink),
				msg, 0, DEVLINK_MCGRP_CONFIG, GFP_KERNEL);
पूर्ण

अटल पूर्णांक devlink_nl_port_attrs_put(काष्ठा sk_buff *msg,
				     काष्ठा devlink_port *devlink_port)
अणु
	काष्ठा devlink_port_attrs *attrs = &devlink_port->attrs;

	अगर (!devlink_port->attrs_set)
		वापस 0;
	अगर (attrs->lanes) अणु
		अगर (nla_put_u32(msg, DEVLINK_ATTR_PORT_LANES, attrs->lanes))
			वापस -EMSGSIZE;
	पूर्ण
	अगर (nla_put_u8(msg, DEVLINK_ATTR_PORT_SPLITTABLE, attrs->splittable))
		वापस -EMSGSIZE;
	अगर (nla_put_u16(msg, DEVLINK_ATTR_PORT_FLAVOUR, attrs->flavour))
		वापस -EMSGSIZE;
	चयन (devlink_port->attrs.flavour) अणु
	हाल DEVLINK_PORT_FLAVOUR_PCI_PF:
		अगर (nla_put_u32(msg, DEVLINK_ATTR_PORT_CONTROLLER_NUMBER,
				attrs->pci_pf.controller) ||
		    nla_put_u16(msg, DEVLINK_ATTR_PORT_PCI_PF_NUMBER, attrs->pci_pf.pf))
			वापस -EMSGSIZE;
		अगर (nla_put_u8(msg, DEVLINK_ATTR_PORT_EXTERNAL, attrs->pci_pf.बाह्यal))
			वापस -EMSGSIZE;
		अवरोध;
	हाल DEVLINK_PORT_FLAVOUR_PCI_VF:
		अगर (nla_put_u32(msg, DEVLINK_ATTR_PORT_CONTROLLER_NUMBER,
				attrs->pci_vf.controller) ||
		    nla_put_u16(msg, DEVLINK_ATTR_PORT_PCI_PF_NUMBER, attrs->pci_vf.pf) ||
		    nla_put_u16(msg, DEVLINK_ATTR_PORT_PCI_VF_NUMBER, attrs->pci_vf.vf))
			वापस -EMSGSIZE;
		अगर (nla_put_u8(msg, DEVLINK_ATTR_PORT_EXTERNAL, attrs->pci_vf.बाह्यal))
			वापस -EMSGSIZE;
		अवरोध;
	हाल DEVLINK_PORT_FLAVOUR_PCI_SF:
		अगर (nla_put_u32(msg, DEVLINK_ATTR_PORT_CONTROLLER_NUMBER,
				attrs->pci_sf.controller) ||
		    nla_put_u16(msg, DEVLINK_ATTR_PORT_PCI_PF_NUMBER,
				attrs->pci_sf.pf) ||
		    nla_put_u32(msg, DEVLINK_ATTR_PORT_PCI_SF_NUMBER,
				attrs->pci_sf.sf))
			वापस -EMSGSIZE;
		अवरोध;
	हाल DEVLINK_PORT_FLAVOUR_PHYSICAL:
	हाल DEVLINK_PORT_FLAVOUR_CPU:
	हाल DEVLINK_PORT_FLAVOUR_DSA:
		अगर (nla_put_u32(msg, DEVLINK_ATTR_PORT_NUMBER,
				attrs->phys.port_number))
			वापस -EMSGSIZE;
		अगर (!attrs->split)
			वापस 0;
		अगर (nla_put_u32(msg, DEVLINK_ATTR_PORT_SPLIT_GROUP,
				attrs->phys.port_number))
			वापस -EMSGSIZE;
		अगर (nla_put_u32(msg, DEVLINK_ATTR_PORT_SPLIT_SUBPORT_NUMBER,
				attrs->phys.split_subport_number))
			वापस -EMSGSIZE;
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक
devlink_port_fn_hw_addr_fill(काष्ठा devlink *devlink, स्थिर काष्ठा devlink_ops *ops,
			     काष्ठा devlink_port *port, काष्ठा sk_buff *msg,
			     काष्ठा netlink_ext_ack *extack, bool *msg_updated)
अणु
	u8 hw_addr[MAX_ADDR_LEN];
	पूर्णांक hw_addr_len;
	पूर्णांक err;

	अगर (!ops->port_function_hw_addr_get)
		वापस 0;

	err = ops->port_function_hw_addr_get(devlink, port, hw_addr, &hw_addr_len, extack);
	अगर (err) अणु
		अगर (err == -EOPNOTSUPP)
			वापस 0;
		वापस err;
	पूर्ण
	err = nla_put(msg, DEVLINK_PORT_FUNCTION_ATTR_HW_ADDR, hw_addr_len, hw_addr);
	अगर (err)
		वापस err;
	*msg_updated = true;
	वापस 0;
पूर्ण

अटल bool
devlink_port_fn_state_valid(क्रमागत devlink_port_fn_state state)
अणु
	वापस state == DEVLINK_PORT_FN_STATE_INACTIVE ||
	       state == DEVLINK_PORT_FN_STATE_ACTIVE;
पूर्ण

अटल bool
devlink_port_fn_opstate_valid(क्रमागत devlink_port_fn_opstate opstate)
अणु
	वापस opstate == DEVLINK_PORT_FN_OPSTATE_DETACHED ||
	       opstate == DEVLINK_PORT_FN_OPSTATE_ATTACHED;
पूर्ण

अटल पूर्णांक
devlink_port_fn_state_fill(काष्ठा devlink *devlink,
			   स्थिर काष्ठा devlink_ops *ops,
			   काष्ठा devlink_port *port, काष्ठा sk_buff *msg,
			   काष्ठा netlink_ext_ack *extack,
			   bool *msg_updated)
अणु
	क्रमागत devlink_port_fn_opstate opstate;
	क्रमागत devlink_port_fn_state state;
	पूर्णांक err;

	अगर (!ops->port_fn_state_get)
		वापस 0;

	err = ops->port_fn_state_get(devlink, port, &state, &opstate, extack);
	अगर (err) अणु
		अगर (err == -EOPNOTSUPP)
			वापस 0;
		वापस err;
	पूर्ण
	अगर (!devlink_port_fn_state_valid(state)) अणु
		WARN_ON_ONCE(1);
		NL_SET_ERR_MSG_MOD(extack, "Invalid state read from driver");
		वापस -EINVAL;
	पूर्ण
	अगर (!devlink_port_fn_opstate_valid(opstate)) अणु
		WARN_ON_ONCE(1);
		NL_SET_ERR_MSG_MOD(extack,
				   "Invalid operational state read from driver");
		वापस -EINVAL;
	पूर्ण
	अगर (nla_put_u8(msg, DEVLINK_PORT_FN_ATTR_STATE, state) ||
	    nla_put_u8(msg, DEVLINK_PORT_FN_ATTR_OPSTATE, opstate))
		वापस -EMSGSIZE;
	*msg_updated = true;
	वापस 0;
पूर्ण

अटल पूर्णांक
devlink_nl_port_function_attrs_put(काष्ठा sk_buff *msg, काष्ठा devlink_port *port,
				   काष्ठा netlink_ext_ack *extack)
अणु
	काष्ठा devlink *devlink = port->devlink;
	स्थिर काष्ठा devlink_ops *ops;
	काष्ठा nlattr *function_attr;
	bool msg_updated = false;
	पूर्णांक err;

	function_attr = nla_nest_start_noflag(msg, DEVLINK_ATTR_PORT_FUNCTION);
	अगर (!function_attr)
		वापस -EMSGSIZE;

	ops = devlink->ops;
	err = devlink_port_fn_hw_addr_fill(devlink, ops, port, msg,
					   extack, &msg_updated);
	अगर (err)
		जाओ out;
	err = devlink_port_fn_state_fill(devlink, ops, port, msg, extack,
					 &msg_updated);
out:
	अगर (err || !msg_updated)
		nla_nest_cancel(msg, function_attr);
	अन्यथा
		nla_nest_end(msg, function_attr);
	वापस err;
पूर्ण

अटल पूर्णांक devlink_nl_port_fill(काष्ठा sk_buff *msg, काष्ठा devlink *devlink,
				काष्ठा devlink_port *devlink_port,
				क्रमागत devlink_command cmd, u32 portid,
				u32 seq, पूर्णांक flags,
				काष्ठा netlink_ext_ack *extack)
अणु
	व्योम *hdr;

	hdr = genlmsg_put(msg, portid, seq, &devlink_nl_family, flags, cmd);
	अगर (!hdr)
		वापस -EMSGSIZE;

	अगर (devlink_nl_put_handle(msg, devlink))
		जाओ nla_put_failure;
	अगर (nla_put_u32(msg, DEVLINK_ATTR_PORT_INDEX, devlink_port->index))
		जाओ nla_put_failure;

	/* Hold rtnl lock जबतक accessing port's netdev attributes. */
	rtnl_lock();
	spin_lock_bh(&devlink_port->type_lock);
	अगर (nla_put_u16(msg, DEVLINK_ATTR_PORT_TYPE, devlink_port->type))
		जाओ nla_put_failure_type_locked;
	अगर (devlink_port->desired_type != DEVLINK_PORT_TYPE_NOTSET &&
	    nla_put_u16(msg, DEVLINK_ATTR_PORT_DESIRED_TYPE,
			devlink_port->desired_type))
		जाओ nla_put_failure_type_locked;
	अगर (devlink_port->type == DEVLINK_PORT_TYPE_ETH) अणु
		काष्ठा net *net = devlink_net(devlink_port->devlink);
		काष्ठा net_device *netdev = devlink_port->type_dev;

		अगर (netdev && net_eq(net, dev_net(netdev)) &&
		    (nla_put_u32(msg, DEVLINK_ATTR_PORT_NETDEV_IFINDEX,
				 netdev->अगरindex) ||
		     nla_put_string(msg, DEVLINK_ATTR_PORT_NETDEV_NAME,
				    netdev->name)))
			जाओ nla_put_failure_type_locked;
	पूर्ण
	अगर (devlink_port->type == DEVLINK_PORT_TYPE_IB) अणु
		काष्ठा ib_device *ibdev = devlink_port->type_dev;

		अगर (ibdev &&
		    nla_put_string(msg, DEVLINK_ATTR_PORT_IBDEV_NAME,
				   ibdev->name))
			जाओ nla_put_failure_type_locked;
	पूर्ण
	spin_unlock_bh(&devlink_port->type_lock);
	rtnl_unlock();
	अगर (devlink_nl_port_attrs_put(msg, devlink_port))
		जाओ nla_put_failure;
	अगर (devlink_nl_port_function_attrs_put(msg, devlink_port, extack))
		जाओ nla_put_failure;

	genlmsg_end(msg, hdr);
	वापस 0;

nla_put_failure_type_locked:
	spin_unlock_bh(&devlink_port->type_lock);
	rtnl_unlock();
nla_put_failure:
	genlmsg_cancel(msg, hdr);
	वापस -EMSGSIZE;
पूर्ण

अटल व्योम devlink_port_notअगरy(काष्ठा devlink_port *devlink_port,
				क्रमागत devlink_command cmd)
अणु
	काष्ठा devlink *devlink = devlink_port->devlink;
	काष्ठा sk_buff *msg;
	पूर्णांक err;

	अगर (!devlink_port->रेजिस्टरed)
		वापस;

	WARN_ON(cmd != DEVLINK_CMD_PORT_NEW && cmd != DEVLINK_CMD_PORT_DEL);

	msg = nlmsg_new(NLMSG_DEFAULT_SIZE, GFP_KERNEL);
	अगर (!msg)
		वापस;

	err = devlink_nl_port_fill(msg, devlink, devlink_port, cmd, 0, 0, 0,
				   शून्य);
	अगर (err) अणु
		nlmsg_मुक्त(msg);
		वापस;
	पूर्ण

	genlmsg_multicast_netns(&devlink_nl_family, devlink_net(devlink),
				msg, 0, DEVLINK_MCGRP_CONFIG, GFP_KERNEL);
पूर्ण

अटल पूर्णांक devlink_nl_cmd_get_करोit(काष्ठा sk_buff *skb, काष्ठा genl_info *info)
अणु
	काष्ठा devlink *devlink = info->user_ptr[0];
	काष्ठा sk_buff *msg;
	पूर्णांक err;

	msg = nlmsg_new(NLMSG_DEFAULT_SIZE, GFP_KERNEL);
	अगर (!msg)
		वापस -ENOMEM;

	err = devlink_nl_fill(msg, devlink, DEVLINK_CMD_NEW,
			      info->snd_portid, info->snd_seq, 0);
	अगर (err) अणु
		nlmsg_मुक्त(msg);
		वापस err;
	पूर्ण

	वापस genlmsg_reply(msg, info);
पूर्ण

अटल पूर्णांक devlink_nl_cmd_get_dumpit(काष्ठा sk_buff *msg,
				     काष्ठा netlink_callback *cb)
अणु
	काष्ठा devlink *devlink;
	पूर्णांक start = cb->args[0];
	पूर्णांक idx = 0;
	पूर्णांक err;

	mutex_lock(&devlink_mutex);
	list_क्रम_each_entry(devlink, &devlink_list, list) अणु
		अगर (!net_eq(devlink_net(devlink), sock_net(msg->sk)))
			जारी;
		अगर (idx < start) अणु
			idx++;
			जारी;
		पूर्ण
		err = devlink_nl_fill(msg, devlink, DEVLINK_CMD_NEW,
				      NETLINK_CB(cb->skb).portid,
				      cb->nlh->nlmsg_seq, NLM_F_MULTI);
		अगर (err)
			जाओ out;
		idx++;
	पूर्ण
out:
	mutex_unlock(&devlink_mutex);

	cb->args[0] = idx;
	वापस msg->len;
पूर्ण

अटल पूर्णांक devlink_nl_cmd_port_get_करोit(काष्ठा sk_buff *skb,
					काष्ठा genl_info *info)
अणु
	काष्ठा devlink_port *devlink_port = info->user_ptr[1];
	काष्ठा devlink *devlink = devlink_port->devlink;
	काष्ठा sk_buff *msg;
	पूर्णांक err;

	msg = nlmsg_new(NLMSG_DEFAULT_SIZE, GFP_KERNEL);
	अगर (!msg)
		वापस -ENOMEM;

	err = devlink_nl_port_fill(msg, devlink, devlink_port,
				   DEVLINK_CMD_PORT_NEW,
				   info->snd_portid, info->snd_seq, 0,
				   info->extack);
	अगर (err) अणु
		nlmsg_मुक्त(msg);
		वापस err;
	पूर्ण

	वापस genlmsg_reply(msg, info);
पूर्ण

अटल पूर्णांक devlink_nl_cmd_port_get_dumpit(काष्ठा sk_buff *msg,
					  काष्ठा netlink_callback *cb)
अणु
	काष्ठा devlink *devlink;
	काष्ठा devlink_port *devlink_port;
	पूर्णांक start = cb->args[0];
	पूर्णांक idx = 0;
	पूर्णांक err;

	mutex_lock(&devlink_mutex);
	list_क्रम_each_entry(devlink, &devlink_list, list) अणु
		अगर (!net_eq(devlink_net(devlink), sock_net(msg->sk)))
			जारी;
		mutex_lock(&devlink->lock);
		list_क्रम_each_entry(devlink_port, &devlink->port_list, list) अणु
			अगर (idx < start) अणु
				idx++;
				जारी;
			पूर्ण
			err = devlink_nl_port_fill(msg, devlink, devlink_port,
						   DEVLINK_CMD_NEW,
						   NETLINK_CB(cb->skb).portid,
						   cb->nlh->nlmsg_seq,
						   NLM_F_MULTI,
						   cb->extack);
			अगर (err) अणु
				mutex_unlock(&devlink->lock);
				जाओ out;
			पूर्ण
			idx++;
		पूर्ण
		mutex_unlock(&devlink->lock);
	पूर्ण
out:
	mutex_unlock(&devlink_mutex);

	cb->args[0] = idx;
	वापस msg->len;
पूर्ण

अटल पूर्णांक devlink_port_type_set(काष्ठा devlink *devlink,
				 काष्ठा devlink_port *devlink_port,
				 क्रमागत devlink_port_type port_type)

अणु
	पूर्णांक err;

	अगर (devlink->ops->port_type_set) अणु
		अगर (port_type == devlink_port->type)
			वापस 0;
		err = devlink->ops->port_type_set(devlink_port, port_type);
		अगर (err)
			वापस err;
		devlink_port->desired_type = port_type;
		devlink_port_notअगरy(devlink_port, DEVLINK_CMD_PORT_NEW);
		वापस 0;
	पूर्ण
	वापस -EOPNOTSUPP;
पूर्ण

अटल पूर्णांक
devlink_port_function_hw_addr_set(काष्ठा devlink *devlink, काष्ठा devlink_port *port,
				  स्थिर काष्ठा nlattr *attr, काष्ठा netlink_ext_ack *extack)
अणु
	स्थिर काष्ठा devlink_ops *ops;
	स्थिर u8 *hw_addr;
	पूर्णांक hw_addr_len;

	hw_addr = nla_data(attr);
	hw_addr_len = nla_len(attr);
	अगर (hw_addr_len > MAX_ADDR_LEN) अणु
		NL_SET_ERR_MSG_MOD(extack, "Port function hardware address too long");
		वापस -EINVAL;
	पूर्ण
	अगर (port->type == DEVLINK_PORT_TYPE_ETH) अणु
		अगर (hw_addr_len != ETH_ALEN) अणु
			NL_SET_ERR_MSG_MOD(extack, "Address must be 6 bytes for Ethernet device");
			वापस -EINVAL;
		पूर्ण
		अगर (!is_unicast_ether_addr(hw_addr)) अणु
			NL_SET_ERR_MSG_MOD(extack, "Non-unicast hardware address unsupported");
			वापस -EINVAL;
		पूर्ण
	पूर्ण

	ops = devlink->ops;
	अगर (!ops->port_function_hw_addr_set) अणु
		NL_SET_ERR_MSG_MOD(extack, "Port doesn't support function attributes");
		वापस -EOPNOTSUPP;
	पूर्ण

	वापस ops->port_function_hw_addr_set(devlink, port, hw_addr, hw_addr_len, extack);
पूर्ण

अटल पूर्णांक devlink_port_fn_state_set(काष्ठा devlink *devlink,
				     काष्ठा devlink_port *port,
				     स्थिर काष्ठा nlattr *attr,
				     काष्ठा netlink_ext_ack *extack)
अणु
	क्रमागत devlink_port_fn_state state;
	स्थिर काष्ठा devlink_ops *ops;

	state = nla_get_u8(attr);
	ops = devlink->ops;
	अगर (!ops->port_fn_state_set) अणु
		NL_SET_ERR_MSG_MOD(extack,
				   "Function does not support state setting");
		वापस -EOPNOTSUPP;
	पूर्ण
	वापस ops->port_fn_state_set(devlink, port, state, extack);
पूर्ण

अटल पूर्णांक
devlink_port_function_set(काष्ठा devlink *devlink, काष्ठा devlink_port *port,
			  स्थिर काष्ठा nlattr *attr, काष्ठा netlink_ext_ack *extack)
अणु
	काष्ठा nlattr *tb[DEVLINK_PORT_FUNCTION_ATTR_MAX + 1];
	पूर्णांक err;

	err = nla_parse_nested(tb, DEVLINK_PORT_FUNCTION_ATTR_MAX, attr,
			       devlink_function_nl_policy, extack);
	अगर (err < 0) अणु
		NL_SET_ERR_MSG_MOD(extack, "Fail to parse port function attributes");
		वापस err;
	पूर्ण

	attr = tb[DEVLINK_PORT_FUNCTION_ATTR_HW_ADDR];
	अगर (attr) अणु
		err = devlink_port_function_hw_addr_set(devlink, port, attr, extack);
		अगर (err)
			वापस err;
	पूर्ण
	/* Keep this as the last function attribute set, so that when
	 * multiple port function attributes are set aदीर्घ with state,
	 * Those can be applied first beक्रमe activating the state.
	 */
	attr = tb[DEVLINK_PORT_FN_ATTR_STATE];
	अगर (attr)
		err = devlink_port_fn_state_set(devlink, port, attr, extack);

	अगर (!err)
		devlink_port_notअगरy(port, DEVLINK_CMD_PORT_NEW);
	वापस err;
पूर्ण

अटल पूर्णांक devlink_nl_cmd_port_set_करोit(काष्ठा sk_buff *skb,
					काष्ठा genl_info *info)
अणु
	काष्ठा devlink_port *devlink_port = info->user_ptr[1];
	काष्ठा devlink *devlink = devlink_port->devlink;
	पूर्णांक err;

	अगर (info->attrs[DEVLINK_ATTR_PORT_TYPE]) अणु
		क्रमागत devlink_port_type port_type;

		port_type = nla_get_u16(info->attrs[DEVLINK_ATTR_PORT_TYPE]);
		err = devlink_port_type_set(devlink, devlink_port, port_type);
		अगर (err)
			वापस err;
	पूर्ण

	अगर (info->attrs[DEVLINK_ATTR_PORT_FUNCTION]) अणु
		काष्ठा nlattr *attr = info->attrs[DEVLINK_ATTR_PORT_FUNCTION];
		काष्ठा netlink_ext_ack *extack = info->extack;

		err = devlink_port_function_set(devlink, devlink_port, attr, extack);
		अगर (err)
			वापस err;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक devlink_port_split(काष्ठा devlink *devlink, u32 port_index,
			      u32 count, काष्ठा netlink_ext_ack *extack)

अणु
	अगर (devlink->ops->port_split)
		वापस devlink->ops->port_split(devlink, port_index, count,
						extack);
	वापस -EOPNOTSUPP;
पूर्ण

अटल पूर्णांक devlink_nl_cmd_port_split_करोit(काष्ठा sk_buff *skb,
					  काष्ठा genl_info *info)
अणु
	काष्ठा devlink *devlink = info->user_ptr[0];
	काष्ठा devlink_port *devlink_port;
	u32 port_index;
	u32 count;

	अगर (!info->attrs[DEVLINK_ATTR_PORT_INDEX] ||
	    !info->attrs[DEVLINK_ATTR_PORT_SPLIT_COUNT])
		वापस -EINVAL;

	devlink_port = devlink_port_get_from_info(devlink, info);
	port_index = nla_get_u32(info->attrs[DEVLINK_ATTR_PORT_INDEX]);
	count = nla_get_u32(info->attrs[DEVLINK_ATTR_PORT_SPLIT_COUNT]);

	अगर (IS_ERR(devlink_port))
		वापस -EINVAL;

	अगर (!devlink_port->attrs.splittable) अणु
		/* Split ports cannot be split. */
		अगर (devlink_port->attrs.split)
			NL_SET_ERR_MSG_MOD(info->extack, "Port cannot be split further");
		अन्यथा
			NL_SET_ERR_MSG_MOD(info->extack, "Port cannot be split");
		वापस -EINVAL;
	पूर्ण

	अगर (count < 2 || !is_घातer_of_2(count) || count > devlink_port->attrs.lanes) अणु
		NL_SET_ERR_MSG_MOD(info->extack, "Invalid split count");
		वापस -EINVAL;
	पूर्ण

	वापस devlink_port_split(devlink, port_index, count, info->extack);
पूर्ण

अटल पूर्णांक devlink_port_unsplit(काष्ठा devlink *devlink, u32 port_index,
				काष्ठा netlink_ext_ack *extack)

अणु
	अगर (devlink->ops->port_unsplit)
		वापस devlink->ops->port_unsplit(devlink, port_index, extack);
	वापस -EOPNOTSUPP;
पूर्ण

अटल पूर्णांक devlink_nl_cmd_port_unsplit_करोit(काष्ठा sk_buff *skb,
					    काष्ठा genl_info *info)
अणु
	काष्ठा devlink *devlink = info->user_ptr[0];
	u32 port_index;

	अगर (!info->attrs[DEVLINK_ATTR_PORT_INDEX])
		वापस -EINVAL;

	port_index = nla_get_u32(info->attrs[DEVLINK_ATTR_PORT_INDEX]);
	वापस devlink_port_unsplit(devlink, port_index, info->extack);
पूर्ण

अटल पूर्णांक devlink_port_new_notअगरiy(काष्ठा devlink *devlink,
				    अचिन्हित पूर्णांक port_index,
				    काष्ठा genl_info *info)
अणु
	काष्ठा devlink_port *devlink_port;
	काष्ठा sk_buff *msg;
	पूर्णांक err;

	msg = nlmsg_new(NLMSG_DEFAULT_SIZE, GFP_KERNEL);
	अगर (!msg)
		वापस -ENOMEM;

	mutex_lock(&devlink->lock);
	devlink_port = devlink_port_get_by_index(devlink, port_index);
	अगर (!devlink_port) अणु
		err = -ENODEV;
		जाओ out;
	पूर्ण

	err = devlink_nl_port_fill(msg, devlink, devlink_port,
				   DEVLINK_CMD_NEW, info->snd_portid,
				   info->snd_seq, 0, शून्य);
	अगर (err)
		जाओ out;

	err = genlmsg_reply(msg, info);
	mutex_unlock(&devlink->lock);
	वापस err;

out:
	mutex_unlock(&devlink->lock);
	nlmsg_मुक्त(msg);
	वापस err;
पूर्ण

अटल पूर्णांक devlink_nl_cmd_port_new_करोit(काष्ठा sk_buff *skb,
					काष्ठा genl_info *info)
अणु
	काष्ठा netlink_ext_ack *extack = info->extack;
	काष्ठा devlink_port_new_attrs new_attrs = अणुपूर्ण;
	काष्ठा devlink *devlink = info->user_ptr[0];
	अचिन्हित पूर्णांक new_port_index;
	पूर्णांक err;

	अगर (!devlink->ops->port_new || !devlink->ops->port_del)
		वापस -EOPNOTSUPP;

	अगर (!info->attrs[DEVLINK_ATTR_PORT_FLAVOUR] ||
	    !info->attrs[DEVLINK_ATTR_PORT_PCI_PF_NUMBER]) अणु
		NL_SET_ERR_MSG_MOD(extack, "Port flavour or PCI PF are not specified");
		वापस -EINVAL;
	पूर्ण
	new_attrs.flavour = nla_get_u16(info->attrs[DEVLINK_ATTR_PORT_FLAVOUR]);
	new_attrs.pfnum =
		nla_get_u16(info->attrs[DEVLINK_ATTR_PORT_PCI_PF_NUMBER]);

	अगर (info->attrs[DEVLINK_ATTR_PORT_INDEX]) अणु
		/* Port index of the new port being created by driver. */
		new_attrs.port_index =
			nla_get_u32(info->attrs[DEVLINK_ATTR_PORT_INDEX]);
		new_attrs.port_index_valid = true;
	पूर्ण
	अगर (info->attrs[DEVLINK_ATTR_PORT_CONTROLLER_NUMBER]) अणु
		new_attrs.controller =
			nla_get_u16(info->attrs[DEVLINK_ATTR_PORT_CONTROLLER_NUMBER]);
		new_attrs.controller_valid = true;
	पूर्ण
	अगर (new_attrs.flavour == DEVLINK_PORT_FLAVOUR_PCI_SF &&
	    info->attrs[DEVLINK_ATTR_PORT_PCI_SF_NUMBER]) अणु
		new_attrs.sfnum = nla_get_u32(info->attrs[DEVLINK_ATTR_PORT_PCI_SF_NUMBER]);
		new_attrs.sfnum_valid = true;
	पूर्ण

	err = devlink->ops->port_new(devlink, &new_attrs, extack,
				     &new_port_index);
	अगर (err)
		वापस err;

	err = devlink_port_new_notअगरiy(devlink, new_port_index, info);
	अगर (err && err != -ENODEV) अणु
		/* Fail to send the response; destroy newly created port. */
		devlink->ops->port_del(devlink, new_port_index, extack);
	पूर्ण
	वापस err;
पूर्ण

अटल पूर्णांक devlink_nl_cmd_port_del_करोit(काष्ठा sk_buff *skb,
					काष्ठा genl_info *info)
अणु
	काष्ठा netlink_ext_ack *extack = info->extack;
	काष्ठा devlink *devlink = info->user_ptr[0];
	अचिन्हित पूर्णांक port_index;

	अगर (!devlink->ops->port_del)
		वापस -EOPNOTSUPP;

	अगर (!info->attrs[DEVLINK_ATTR_PORT_INDEX]) अणु
		NL_SET_ERR_MSG_MOD(extack, "Port index is not specified");
		वापस -EINVAL;
	पूर्ण
	port_index = nla_get_u32(info->attrs[DEVLINK_ATTR_PORT_INDEX]);

	वापस devlink->ops->port_del(devlink, port_index, extack);
पूर्ण

अटल पूर्णांक devlink_nl_sb_fill(काष्ठा sk_buff *msg, काष्ठा devlink *devlink,
			      काष्ठा devlink_sb *devlink_sb,
			      क्रमागत devlink_command cmd, u32 portid,
			      u32 seq, पूर्णांक flags)
अणु
	व्योम *hdr;

	hdr = genlmsg_put(msg, portid, seq, &devlink_nl_family, flags, cmd);
	अगर (!hdr)
		वापस -EMSGSIZE;

	अगर (devlink_nl_put_handle(msg, devlink))
		जाओ nla_put_failure;
	अगर (nla_put_u32(msg, DEVLINK_ATTR_SB_INDEX, devlink_sb->index))
		जाओ nla_put_failure;
	अगर (nla_put_u32(msg, DEVLINK_ATTR_SB_SIZE, devlink_sb->size))
		जाओ nla_put_failure;
	अगर (nla_put_u16(msg, DEVLINK_ATTR_SB_INGRESS_POOL_COUNT,
			devlink_sb->ingress_pools_count))
		जाओ nla_put_failure;
	अगर (nla_put_u16(msg, DEVLINK_ATTR_SB_EGRESS_POOL_COUNT,
			devlink_sb->egress_pools_count))
		जाओ nla_put_failure;
	अगर (nla_put_u16(msg, DEVLINK_ATTR_SB_INGRESS_TC_COUNT,
			devlink_sb->ingress_tc_count))
		जाओ nla_put_failure;
	अगर (nla_put_u16(msg, DEVLINK_ATTR_SB_EGRESS_TC_COUNT,
			devlink_sb->egress_tc_count))
		जाओ nla_put_failure;

	genlmsg_end(msg, hdr);
	वापस 0;

nla_put_failure:
	genlmsg_cancel(msg, hdr);
	वापस -EMSGSIZE;
पूर्ण

अटल पूर्णांक devlink_nl_cmd_sb_get_करोit(काष्ठा sk_buff *skb,
				      काष्ठा genl_info *info)
अणु
	काष्ठा devlink *devlink = info->user_ptr[0];
	काष्ठा devlink_sb *devlink_sb;
	काष्ठा sk_buff *msg;
	पूर्णांक err;

	devlink_sb = devlink_sb_get_from_info(devlink, info);
	अगर (IS_ERR(devlink_sb))
		वापस PTR_ERR(devlink_sb);

	msg = nlmsg_new(NLMSG_DEFAULT_SIZE, GFP_KERNEL);
	अगर (!msg)
		वापस -ENOMEM;

	err = devlink_nl_sb_fill(msg, devlink, devlink_sb,
				 DEVLINK_CMD_SB_NEW,
				 info->snd_portid, info->snd_seq, 0);
	अगर (err) अणु
		nlmsg_मुक्त(msg);
		वापस err;
	पूर्ण

	वापस genlmsg_reply(msg, info);
पूर्ण

अटल पूर्णांक devlink_nl_cmd_sb_get_dumpit(काष्ठा sk_buff *msg,
					काष्ठा netlink_callback *cb)
अणु
	काष्ठा devlink *devlink;
	काष्ठा devlink_sb *devlink_sb;
	पूर्णांक start = cb->args[0];
	पूर्णांक idx = 0;
	पूर्णांक err;

	mutex_lock(&devlink_mutex);
	list_क्रम_each_entry(devlink, &devlink_list, list) अणु
		अगर (!net_eq(devlink_net(devlink), sock_net(msg->sk)))
			जारी;
		mutex_lock(&devlink->lock);
		list_क्रम_each_entry(devlink_sb, &devlink->sb_list, list) अणु
			अगर (idx < start) अणु
				idx++;
				जारी;
			पूर्ण
			err = devlink_nl_sb_fill(msg, devlink, devlink_sb,
						 DEVLINK_CMD_SB_NEW,
						 NETLINK_CB(cb->skb).portid,
						 cb->nlh->nlmsg_seq,
						 NLM_F_MULTI);
			अगर (err) अणु
				mutex_unlock(&devlink->lock);
				जाओ out;
			पूर्ण
			idx++;
		पूर्ण
		mutex_unlock(&devlink->lock);
	पूर्ण
out:
	mutex_unlock(&devlink_mutex);

	cb->args[0] = idx;
	वापस msg->len;
पूर्ण

अटल पूर्णांक devlink_nl_sb_pool_fill(काष्ठा sk_buff *msg, काष्ठा devlink *devlink,
				   काष्ठा devlink_sb *devlink_sb,
				   u16 pool_index, क्रमागत devlink_command cmd,
				   u32 portid, u32 seq, पूर्णांक flags)
अणु
	काष्ठा devlink_sb_pool_info pool_info;
	व्योम *hdr;
	पूर्णांक err;

	err = devlink->ops->sb_pool_get(devlink, devlink_sb->index,
					pool_index, &pool_info);
	अगर (err)
		वापस err;

	hdr = genlmsg_put(msg, portid, seq, &devlink_nl_family, flags, cmd);
	अगर (!hdr)
		वापस -EMSGSIZE;

	अगर (devlink_nl_put_handle(msg, devlink))
		जाओ nla_put_failure;
	अगर (nla_put_u32(msg, DEVLINK_ATTR_SB_INDEX, devlink_sb->index))
		जाओ nla_put_failure;
	अगर (nla_put_u16(msg, DEVLINK_ATTR_SB_POOL_INDEX, pool_index))
		जाओ nla_put_failure;
	अगर (nla_put_u8(msg, DEVLINK_ATTR_SB_POOL_TYPE, pool_info.pool_type))
		जाओ nla_put_failure;
	अगर (nla_put_u32(msg, DEVLINK_ATTR_SB_POOL_SIZE, pool_info.size))
		जाओ nla_put_failure;
	अगर (nla_put_u8(msg, DEVLINK_ATTR_SB_POOL_THRESHOLD_TYPE,
		       pool_info.threshold_type))
		जाओ nla_put_failure;
	अगर (nla_put_u32(msg, DEVLINK_ATTR_SB_POOL_CELL_SIZE,
			pool_info.cell_size))
		जाओ nla_put_failure;

	genlmsg_end(msg, hdr);
	वापस 0;

nla_put_failure:
	genlmsg_cancel(msg, hdr);
	वापस -EMSGSIZE;
पूर्ण

अटल पूर्णांक devlink_nl_cmd_sb_pool_get_करोit(काष्ठा sk_buff *skb,
					   काष्ठा genl_info *info)
अणु
	काष्ठा devlink *devlink = info->user_ptr[0];
	काष्ठा devlink_sb *devlink_sb;
	काष्ठा sk_buff *msg;
	u16 pool_index;
	पूर्णांक err;

	devlink_sb = devlink_sb_get_from_info(devlink, info);
	अगर (IS_ERR(devlink_sb))
		वापस PTR_ERR(devlink_sb);

	err = devlink_sb_pool_index_get_from_info(devlink_sb, info,
						  &pool_index);
	अगर (err)
		वापस err;

	अगर (!devlink->ops->sb_pool_get)
		वापस -EOPNOTSUPP;

	msg = nlmsg_new(NLMSG_DEFAULT_SIZE, GFP_KERNEL);
	अगर (!msg)
		वापस -ENOMEM;

	err = devlink_nl_sb_pool_fill(msg, devlink, devlink_sb, pool_index,
				      DEVLINK_CMD_SB_POOL_NEW,
				      info->snd_portid, info->snd_seq, 0);
	अगर (err) अणु
		nlmsg_मुक्त(msg);
		वापस err;
	पूर्ण

	वापस genlmsg_reply(msg, info);
पूर्ण

अटल पूर्णांक __sb_pool_get_dumpit(काष्ठा sk_buff *msg, पूर्णांक start, पूर्णांक *p_idx,
				काष्ठा devlink *devlink,
				काष्ठा devlink_sb *devlink_sb,
				u32 portid, u32 seq)
अणु
	u16 pool_count = devlink_sb_pool_count(devlink_sb);
	u16 pool_index;
	पूर्णांक err;

	क्रम (pool_index = 0; pool_index < pool_count; pool_index++) अणु
		अगर (*p_idx < start) अणु
			(*p_idx)++;
			जारी;
		पूर्ण
		err = devlink_nl_sb_pool_fill(msg, devlink,
					      devlink_sb,
					      pool_index,
					      DEVLINK_CMD_SB_POOL_NEW,
					      portid, seq, NLM_F_MULTI);
		अगर (err)
			वापस err;
		(*p_idx)++;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक devlink_nl_cmd_sb_pool_get_dumpit(काष्ठा sk_buff *msg,
					     काष्ठा netlink_callback *cb)
अणु
	काष्ठा devlink *devlink;
	काष्ठा devlink_sb *devlink_sb;
	पूर्णांक start = cb->args[0];
	पूर्णांक idx = 0;
	पूर्णांक err = 0;

	mutex_lock(&devlink_mutex);
	list_क्रम_each_entry(devlink, &devlink_list, list) अणु
		अगर (!net_eq(devlink_net(devlink), sock_net(msg->sk)) ||
		    !devlink->ops->sb_pool_get)
			जारी;
		mutex_lock(&devlink->lock);
		list_क्रम_each_entry(devlink_sb, &devlink->sb_list, list) अणु
			err = __sb_pool_get_dumpit(msg, start, &idx, devlink,
						   devlink_sb,
						   NETLINK_CB(cb->skb).portid,
						   cb->nlh->nlmsg_seq);
			अगर (err == -EOPNOTSUPP) अणु
				err = 0;
			पूर्ण अन्यथा अगर (err) अणु
				mutex_unlock(&devlink->lock);
				जाओ out;
			पूर्ण
		पूर्ण
		mutex_unlock(&devlink->lock);
	पूर्ण
out:
	mutex_unlock(&devlink_mutex);

	अगर (err != -EMSGSIZE)
		वापस err;

	cb->args[0] = idx;
	वापस msg->len;
पूर्ण

अटल पूर्णांक devlink_sb_pool_set(काष्ठा devlink *devlink, अचिन्हित पूर्णांक sb_index,
			       u16 pool_index, u32 size,
			       क्रमागत devlink_sb_threshold_type threshold_type,
			       काष्ठा netlink_ext_ack *extack)

अणु
	स्थिर काष्ठा devlink_ops *ops = devlink->ops;

	अगर (ops->sb_pool_set)
		वापस ops->sb_pool_set(devlink, sb_index, pool_index,
					size, threshold_type, extack);
	वापस -EOPNOTSUPP;
पूर्ण

अटल पूर्णांक devlink_nl_cmd_sb_pool_set_करोit(काष्ठा sk_buff *skb,
					   काष्ठा genl_info *info)
अणु
	काष्ठा devlink *devlink = info->user_ptr[0];
	क्रमागत devlink_sb_threshold_type threshold_type;
	काष्ठा devlink_sb *devlink_sb;
	u16 pool_index;
	u32 size;
	पूर्णांक err;

	devlink_sb = devlink_sb_get_from_info(devlink, info);
	अगर (IS_ERR(devlink_sb))
		वापस PTR_ERR(devlink_sb);

	err = devlink_sb_pool_index_get_from_info(devlink_sb, info,
						  &pool_index);
	अगर (err)
		वापस err;

	err = devlink_sb_th_type_get_from_info(info, &threshold_type);
	अगर (err)
		वापस err;

	अगर (!info->attrs[DEVLINK_ATTR_SB_POOL_SIZE])
		वापस -EINVAL;

	size = nla_get_u32(info->attrs[DEVLINK_ATTR_SB_POOL_SIZE]);
	वापस devlink_sb_pool_set(devlink, devlink_sb->index,
				   pool_index, size, threshold_type,
				   info->extack);
पूर्ण

अटल पूर्णांक devlink_nl_sb_port_pool_fill(काष्ठा sk_buff *msg,
					काष्ठा devlink *devlink,
					काष्ठा devlink_port *devlink_port,
					काष्ठा devlink_sb *devlink_sb,
					u16 pool_index,
					क्रमागत devlink_command cmd,
					u32 portid, u32 seq, पूर्णांक flags)
अणु
	स्थिर काष्ठा devlink_ops *ops = devlink->ops;
	u32 threshold;
	व्योम *hdr;
	पूर्णांक err;

	err = ops->sb_port_pool_get(devlink_port, devlink_sb->index,
				    pool_index, &threshold);
	अगर (err)
		वापस err;

	hdr = genlmsg_put(msg, portid, seq, &devlink_nl_family, flags, cmd);
	अगर (!hdr)
		वापस -EMSGSIZE;

	अगर (devlink_nl_put_handle(msg, devlink))
		जाओ nla_put_failure;
	अगर (nla_put_u32(msg, DEVLINK_ATTR_PORT_INDEX, devlink_port->index))
		जाओ nla_put_failure;
	अगर (nla_put_u32(msg, DEVLINK_ATTR_SB_INDEX, devlink_sb->index))
		जाओ nla_put_failure;
	अगर (nla_put_u16(msg, DEVLINK_ATTR_SB_POOL_INDEX, pool_index))
		जाओ nla_put_failure;
	अगर (nla_put_u32(msg, DEVLINK_ATTR_SB_THRESHOLD, threshold))
		जाओ nla_put_failure;

	अगर (ops->sb_occ_port_pool_get) अणु
		u32 cur;
		u32 max;

		err = ops->sb_occ_port_pool_get(devlink_port, devlink_sb->index,
						pool_index, &cur, &max);
		अगर (err && err != -EOPNOTSUPP)
			जाओ sb_occ_get_failure;
		अगर (!err) अणु
			अगर (nla_put_u32(msg, DEVLINK_ATTR_SB_OCC_CUR, cur))
				जाओ nla_put_failure;
			अगर (nla_put_u32(msg, DEVLINK_ATTR_SB_OCC_MAX, max))
				जाओ nla_put_failure;
		पूर्ण
	पूर्ण

	genlmsg_end(msg, hdr);
	वापस 0;

nla_put_failure:
	err = -EMSGSIZE;
sb_occ_get_failure:
	genlmsg_cancel(msg, hdr);
	वापस err;
पूर्ण

अटल पूर्णांक devlink_nl_cmd_sb_port_pool_get_करोit(काष्ठा sk_buff *skb,
						काष्ठा genl_info *info)
अणु
	काष्ठा devlink_port *devlink_port = info->user_ptr[1];
	काष्ठा devlink *devlink = devlink_port->devlink;
	काष्ठा devlink_sb *devlink_sb;
	काष्ठा sk_buff *msg;
	u16 pool_index;
	पूर्णांक err;

	devlink_sb = devlink_sb_get_from_info(devlink, info);
	अगर (IS_ERR(devlink_sb))
		वापस PTR_ERR(devlink_sb);

	err = devlink_sb_pool_index_get_from_info(devlink_sb, info,
						  &pool_index);
	अगर (err)
		वापस err;

	अगर (!devlink->ops->sb_port_pool_get)
		वापस -EOPNOTSUPP;

	msg = nlmsg_new(NLMSG_DEFAULT_SIZE, GFP_KERNEL);
	अगर (!msg)
		वापस -ENOMEM;

	err = devlink_nl_sb_port_pool_fill(msg, devlink, devlink_port,
					   devlink_sb, pool_index,
					   DEVLINK_CMD_SB_PORT_POOL_NEW,
					   info->snd_portid, info->snd_seq, 0);
	अगर (err) अणु
		nlmsg_मुक्त(msg);
		वापस err;
	पूर्ण

	वापस genlmsg_reply(msg, info);
पूर्ण

अटल पूर्णांक __sb_port_pool_get_dumpit(काष्ठा sk_buff *msg, पूर्णांक start, पूर्णांक *p_idx,
				     काष्ठा devlink *devlink,
				     काष्ठा devlink_sb *devlink_sb,
				     u32 portid, u32 seq)
अणु
	काष्ठा devlink_port *devlink_port;
	u16 pool_count = devlink_sb_pool_count(devlink_sb);
	u16 pool_index;
	पूर्णांक err;

	list_क्रम_each_entry(devlink_port, &devlink->port_list, list) अणु
		क्रम (pool_index = 0; pool_index < pool_count; pool_index++) अणु
			अगर (*p_idx < start) अणु
				(*p_idx)++;
				जारी;
			पूर्ण
			err = devlink_nl_sb_port_pool_fill(msg, devlink,
							   devlink_port,
							   devlink_sb,
							   pool_index,
							   DEVLINK_CMD_SB_PORT_POOL_NEW,
							   portid, seq,
							   NLM_F_MULTI);
			अगर (err)
				वापस err;
			(*p_idx)++;
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक devlink_nl_cmd_sb_port_pool_get_dumpit(काष्ठा sk_buff *msg,
						  काष्ठा netlink_callback *cb)
अणु
	काष्ठा devlink *devlink;
	काष्ठा devlink_sb *devlink_sb;
	पूर्णांक start = cb->args[0];
	पूर्णांक idx = 0;
	पूर्णांक err = 0;

	mutex_lock(&devlink_mutex);
	list_क्रम_each_entry(devlink, &devlink_list, list) अणु
		अगर (!net_eq(devlink_net(devlink), sock_net(msg->sk)) ||
		    !devlink->ops->sb_port_pool_get)
			जारी;
		mutex_lock(&devlink->lock);
		list_क्रम_each_entry(devlink_sb, &devlink->sb_list, list) अणु
			err = __sb_port_pool_get_dumpit(msg, start, &idx,
							devlink, devlink_sb,
							NETLINK_CB(cb->skb).portid,
							cb->nlh->nlmsg_seq);
			अगर (err == -EOPNOTSUPP) अणु
				err = 0;
			पूर्ण अन्यथा अगर (err) अणु
				mutex_unlock(&devlink->lock);
				जाओ out;
			पूर्ण
		पूर्ण
		mutex_unlock(&devlink->lock);
	पूर्ण
out:
	mutex_unlock(&devlink_mutex);

	अगर (err != -EMSGSIZE)
		वापस err;

	cb->args[0] = idx;
	वापस msg->len;
पूर्ण

अटल पूर्णांक devlink_sb_port_pool_set(काष्ठा devlink_port *devlink_port,
				    अचिन्हित पूर्णांक sb_index, u16 pool_index,
				    u32 threshold,
				    काष्ठा netlink_ext_ack *extack)

अणु
	स्थिर काष्ठा devlink_ops *ops = devlink_port->devlink->ops;

	अगर (ops->sb_port_pool_set)
		वापस ops->sb_port_pool_set(devlink_port, sb_index,
					     pool_index, threshold, extack);
	वापस -EOPNOTSUPP;
पूर्ण

अटल पूर्णांक devlink_nl_cmd_sb_port_pool_set_करोit(काष्ठा sk_buff *skb,
						काष्ठा genl_info *info)
अणु
	काष्ठा devlink_port *devlink_port = info->user_ptr[1];
	काष्ठा devlink *devlink = info->user_ptr[0];
	काष्ठा devlink_sb *devlink_sb;
	u16 pool_index;
	u32 threshold;
	पूर्णांक err;

	devlink_sb = devlink_sb_get_from_info(devlink, info);
	अगर (IS_ERR(devlink_sb))
		वापस PTR_ERR(devlink_sb);

	err = devlink_sb_pool_index_get_from_info(devlink_sb, info,
						  &pool_index);
	अगर (err)
		वापस err;

	अगर (!info->attrs[DEVLINK_ATTR_SB_THRESHOLD])
		वापस -EINVAL;

	threshold = nla_get_u32(info->attrs[DEVLINK_ATTR_SB_THRESHOLD]);
	वापस devlink_sb_port_pool_set(devlink_port, devlink_sb->index,
					pool_index, threshold, info->extack);
पूर्ण

अटल पूर्णांक
devlink_nl_sb_tc_pool_bind_fill(काष्ठा sk_buff *msg, काष्ठा devlink *devlink,
				काष्ठा devlink_port *devlink_port,
				काष्ठा devlink_sb *devlink_sb, u16 tc_index,
				क्रमागत devlink_sb_pool_type pool_type,
				क्रमागत devlink_command cmd,
				u32 portid, u32 seq, पूर्णांक flags)
अणु
	स्थिर काष्ठा devlink_ops *ops = devlink->ops;
	u16 pool_index;
	u32 threshold;
	व्योम *hdr;
	पूर्णांक err;

	err = ops->sb_tc_pool_bind_get(devlink_port, devlink_sb->index,
				       tc_index, pool_type,
				       &pool_index, &threshold);
	अगर (err)
		वापस err;

	hdr = genlmsg_put(msg, portid, seq, &devlink_nl_family, flags, cmd);
	अगर (!hdr)
		वापस -EMSGSIZE;

	अगर (devlink_nl_put_handle(msg, devlink))
		जाओ nla_put_failure;
	अगर (nla_put_u32(msg, DEVLINK_ATTR_PORT_INDEX, devlink_port->index))
		जाओ nla_put_failure;
	अगर (nla_put_u32(msg, DEVLINK_ATTR_SB_INDEX, devlink_sb->index))
		जाओ nla_put_failure;
	अगर (nla_put_u16(msg, DEVLINK_ATTR_SB_TC_INDEX, tc_index))
		जाओ nla_put_failure;
	अगर (nla_put_u8(msg, DEVLINK_ATTR_SB_POOL_TYPE, pool_type))
		जाओ nla_put_failure;
	अगर (nla_put_u16(msg, DEVLINK_ATTR_SB_POOL_INDEX, pool_index))
		जाओ nla_put_failure;
	अगर (nla_put_u32(msg, DEVLINK_ATTR_SB_THRESHOLD, threshold))
		जाओ nla_put_failure;

	अगर (ops->sb_occ_tc_port_bind_get) अणु
		u32 cur;
		u32 max;

		err = ops->sb_occ_tc_port_bind_get(devlink_port,
						   devlink_sb->index,
						   tc_index, pool_type,
						   &cur, &max);
		अगर (err && err != -EOPNOTSUPP)
			वापस err;
		अगर (!err) अणु
			अगर (nla_put_u32(msg, DEVLINK_ATTR_SB_OCC_CUR, cur))
				जाओ nla_put_failure;
			अगर (nla_put_u32(msg, DEVLINK_ATTR_SB_OCC_MAX, max))
				जाओ nla_put_failure;
		पूर्ण
	पूर्ण

	genlmsg_end(msg, hdr);
	वापस 0;

nla_put_failure:
	genlmsg_cancel(msg, hdr);
	वापस -EMSGSIZE;
पूर्ण

अटल पूर्णांक devlink_nl_cmd_sb_tc_pool_bind_get_करोit(काष्ठा sk_buff *skb,
						   काष्ठा genl_info *info)
अणु
	काष्ठा devlink_port *devlink_port = info->user_ptr[1];
	काष्ठा devlink *devlink = devlink_port->devlink;
	काष्ठा devlink_sb *devlink_sb;
	काष्ठा sk_buff *msg;
	क्रमागत devlink_sb_pool_type pool_type;
	u16 tc_index;
	पूर्णांक err;

	devlink_sb = devlink_sb_get_from_info(devlink, info);
	अगर (IS_ERR(devlink_sb))
		वापस PTR_ERR(devlink_sb);

	err = devlink_sb_pool_type_get_from_info(info, &pool_type);
	अगर (err)
		वापस err;

	err = devlink_sb_tc_index_get_from_info(devlink_sb, info,
						pool_type, &tc_index);
	अगर (err)
		वापस err;

	अगर (!devlink->ops->sb_tc_pool_bind_get)
		वापस -EOPNOTSUPP;

	msg = nlmsg_new(NLMSG_DEFAULT_SIZE, GFP_KERNEL);
	अगर (!msg)
		वापस -ENOMEM;

	err = devlink_nl_sb_tc_pool_bind_fill(msg, devlink, devlink_port,
					      devlink_sb, tc_index, pool_type,
					      DEVLINK_CMD_SB_TC_POOL_BIND_NEW,
					      info->snd_portid,
					      info->snd_seq, 0);
	अगर (err) अणु
		nlmsg_मुक्त(msg);
		वापस err;
	पूर्ण

	वापस genlmsg_reply(msg, info);
पूर्ण

अटल पूर्णांक __sb_tc_pool_bind_get_dumpit(काष्ठा sk_buff *msg,
					पूर्णांक start, पूर्णांक *p_idx,
					काष्ठा devlink *devlink,
					काष्ठा devlink_sb *devlink_sb,
					u32 portid, u32 seq)
अणु
	काष्ठा devlink_port *devlink_port;
	u16 tc_index;
	पूर्णांक err;

	list_क्रम_each_entry(devlink_port, &devlink->port_list, list) अणु
		क्रम (tc_index = 0;
		     tc_index < devlink_sb->ingress_tc_count; tc_index++) अणु
			अगर (*p_idx < start) अणु
				(*p_idx)++;
				जारी;
			पूर्ण
			err = devlink_nl_sb_tc_pool_bind_fill(msg, devlink,
							      devlink_port,
							      devlink_sb,
							      tc_index,
							      DEVLINK_SB_POOL_TYPE_INGRESS,
							      DEVLINK_CMD_SB_TC_POOL_BIND_NEW,
							      portid, seq,
							      NLM_F_MULTI);
			अगर (err)
				वापस err;
			(*p_idx)++;
		पूर्ण
		क्रम (tc_index = 0;
		     tc_index < devlink_sb->egress_tc_count; tc_index++) अणु
			अगर (*p_idx < start) अणु
				(*p_idx)++;
				जारी;
			पूर्ण
			err = devlink_nl_sb_tc_pool_bind_fill(msg, devlink,
							      devlink_port,
							      devlink_sb,
							      tc_index,
							      DEVLINK_SB_POOL_TYPE_EGRESS,
							      DEVLINK_CMD_SB_TC_POOL_BIND_NEW,
							      portid, seq,
							      NLM_F_MULTI);
			अगर (err)
				वापस err;
			(*p_idx)++;
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक
devlink_nl_cmd_sb_tc_pool_bind_get_dumpit(काष्ठा sk_buff *msg,
					  काष्ठा netlink_callback *cb)
अणु
	काष्ठा devlink *devlink;
	काष्ठा devlink_sb *devlink_sb;
	पूर्णांक start = cb->args[0];
	पूर्णांक idx = 0;
	पूर्णांक err = 0;

	mutex_lock(&devlink_mutex);
	list_क्रम_each_entry(devlink, &devlink_list, list) अणु
		अगर (!net_eq(devlink_net(devlink), sock_net(msg->sk)) ||
		    !devlink->ops->sb_tc_pool_bind_get)
			जारी;

		mutex_lock(&devlink->lock);
		list_क्रम_each_entry(devlink_sb, &devlink->sb_list, list) अणु
			err = __sb_tc_pool_bind_get_dumpit(msg, start, &idx,
							   devlink,
							   devlink_sb,
							   NETLINK_CB(cb->skb).portid,
							   cb->nlh->nlmsg_seq);
			अगर (err == -EOPNOTSUPP) अणु
				err = 0;
			पूर्ण अन्यथा अगर (err) अणु
				mutex_unlock(&devlink->lock);
				जाओ out;
			पूर्ण
		पूर्ण
		mutex_unlock(&devlink->lock);
	पूर्ण
out:
	mutex_unlock(&devlink_mutex);

	अगर (err != -EMSGSIZE)
		वापस err;

	cb->args[0] = idx;
	वापस msg->len;
पूर्ण

अटल पूर्णांक devlink_sb_tc_pool_bind_set(काष्ठा devlink_port *devlink_port,
				       अचिन्हित पूर्णांक sb_index, u16 tc_index,
				       क्रमागत devlink_sb_pool_type pool_type,
				       u16 pool_index, u32 threshold,
				       काष्ठा netlink_ext_ack *extack)

अणु
	स्थिर काष्ठा devlink_ops *ops = devlink_port->devlink->ops;

	अगर (ops->sb_tc_pool_bind_set)
		वापस ops->sb_tc_pool_bind_set(devlink_port, sb_index,
						tc_index, pool_type,
						pool_index, threshold, extack);
	वापस -EOPNOTSUPP;
पूर्ण

अटल पूर्णांक devlink_nl_cmd_sb_tc_pool_bind_set_करोit(काष्ठा sk_buff *skb,
						   काष्ठा genl_info *info)
अणु
	काष्ठा devlink_port *devlink_port = info->user_ptr[1];
	काष्ठा devlink *devlink = info->user_ptr[0];
	क्रमागत devlink_sb_pool_type pool_type;
	काष्ठा devlink_sb *devlink_sb;
	u16 tc_index;
	u16 pool_index;
	u32 threshold;
	पूर्णांक err;

	devlink_sb = devlink_sb_get_from_info(devlink, info);
	अगर (IS_ERR(devlink_sb))
		वापस PTR_ERR(devlink_sb);

	err = devlink_sb_pool_type_get_from_info(info, &pool_type);
	अगर (err)
		वापस err;

	err = devlink_sb_tc_index_get_from_info(devlink_sb, info,
						pool_type, &tc_index);
	अगर (err)
		वापस err;

	err = devlink_sb_pool_index_get_from_info(devlink_sb, info,
						  &pool_index);
	अगर (err)
		वापस err;

	अगर (!info->attrs[DEVLINK_ATTR_SB_THRESHOLD])
		वापस -EINVAL;

	threshold = nla_get_u32(info->attrs[DEVLINK_ATTR_SB_THRESHOLD]);
	वापस devlink_sb_tc_pool_bind_set(devlink_port, devlink_sb->index,
					   tc_index, pool_type,
					   pool_index, threshold, info->extack);
पूर्ण

अटल पूर्णांक devlink_nl_cmd_sb_occ_snapshot_करोit(काष्ठा sk_buff *skb,
					       काष्ठा genl_info *info)
अणु
	काष्ठा devlink *devlink = info->user_ptr[0];
	स्थिर काष्ठा devlink_ops *ops = devlink->ops;
	काष्ठा devlink_sb *devlink_sb;

	devlink_sb = devlink_sb_get_from_info(devlink, info);
	अगर (IS_ERR(devlink_sb))
		वापस PTR_ERR(devlink_sb);

	अगर (ops->sb_occ_snapshot)
		वापस ops->sb_occ_snapshot(devlink, devlink_sb->index);
	वापस -EOPNOTSUPP;
पूर्ण

अटल पूर्णांक devlink_nl_cmd_sb_occ_max_clear_करोit(काष्ठा sk_buff *skb,
						काष्ठा genl_info *info)
अणु
	काष्ठा devlink *devlink = info->user_ptr[0];
	स्थिर काष्ठा devlink_ops *ops = devlink->ops;
	काष्ठा devlink_sb *devlink_sb;

	devlink_sb = devlink_sb_get_from_info(devlink, info);
	अगर (IS_ERR(devlink_sb))
		वापस PTR_ERR(devlink_sb);

	अगर (ops->sb_occ_max_clear)
		वापस ops->sb_occ_max_clear(devlink, devlink_sb->index);
	वापस -EOPNOTSUPP;
पूर्ण

अटल पूर्णांक devlink_nl_eचयन_fill(काष्ठा sk_buff *msg, काष्ठा devlink *devlink,
				   क्रमागत devlink_command cmd, u32 portid,
				   u32 seq, पूर्णांक flags)
अणु
	स्थिर काष्ठा devlink_ops *ops = devlink->ops;
	क्रमागत devlink_eचयन_encap_mode encap_mode;
	u8 अंतरभूत_mode;
	व्योम *hdr;
	पूर्णांक err = 0;
	u16 mode;

	hdr = genlmsg_put(msg, portid, seq, &devlink_nl_family, flags, cmd);
	अगर (!hdr)
		वापस -EMSGSIZE;

	err = devlink_nl_put_handle(msg, devlink);
	अगर (err)
		जाओ nla_put_failure;

	अगर (ops->eचयन_mode_get) अणु
		err = ops->eचयन_mode_get(devlink, &mode);
		अगर (err)
			जाओ nla_put_failure;
		err = nla_put_u16(msg, DEVLINK_ATTR_ESWITCH_MODE, mode);
		अगर (err)
			जाओ nla_put_failure;
	पूर्ण

	अगर (ops->eचयन_अंतरभूत_mode_get) अणु
		err = ops->eचयन_अंतरभूत_mode_get(devlink, &अंतरभूत_mode);
		अगर (err)
			जाओ nla_put_failure;
		err = nla_put_u8(msg, DEVLINK_ATTR_ESWITCH_INLINE_MODE,
				 अंतरभूत_mode);
		अगर (err)
			जाओ nla_put_failure;
	पूर्ण

	अगर (ops->eचयन_encap_mode_get) अणु
		err = ops->eचयन_encap_mode_get(devlink, &encap_mode);
		अगर (err)
			जाओ nla_put_failure;
		err = nla_put_u8(msg, DEVLINK_ATTR_ESWITCH_ENCAP_MODE, encap_mode);
		अगर (err)
			जाओ nla_put_failure;
	पूर्ण

	genlmsg_end(msg, hdr);
	वापस 0;

nla_put_failure:
	genlmsg_cancel(msg, hdr);
	वापस err;
पूर्ण

अटल पूर्णांक devlink_nl_cmd_eचयन_get_करोit(काष्ठा sk_buff *skb,
					   काष्ठा genl_info *info)
अणु
	काष्ठा devlink *devlink = info->user_ptr[0];
	काष्ठा sk_buff *msg;
	पूर्णांक err;

	msg = nlmsg_new(NLMSG_DEFAULT_SIZE, GFP_KERNEL);
	अगर (!msg)
		वापस -ENOMEM;

	err = devlink_nl_eचयन_fill(msg, devlink, DEVLINK_CMD_ESWITCH_GET,
				      info->snd_portid, info->snd_seq, 0);

	अगर (err) अणु
		nlmsg_मुक्त(msg);
		वापस err;
	पूर्ण

	वापस genlmsg_reply(msg, info);
पूर्ण

अटल पूर्णांक devlink_nl_cmd_eचयन_set_करोit(काष्ठा sk_buff *skb,
					   काष्ठा genl_info *info)
अणु
	काष्ठा devlink *devlink = info->user_ptr[0];
	स्थिर काष्ठा devlink_ops *ops = devlink->ops;
	क्रमागत devlink_eचयन_encap_mode encap_mode;
	u8 अंतरभूत_mode;
	पूर्णांक err = 0;
	u16 mode;

	अगर (info->attrs[DEVLINK_ATTR_ESWITCH_MODE]) अणु
		अगर (!ops->eचयन_mode_set)
			वापस -EOPNOTSUPP;
		mode = nla_get_u16(info->attrs[DEVLINK_ATTR_ESWITCH_MODE]);
		err = ops->eचयन_mode_set(devlink, mode, info->extack);
		अगर (err)
			वापस err;
	पूर्ण

	अगर (info->attrs[DEVLINK_ATTR_ESWITCH_INLINE_MODE]) अणु
		अगर (!ops->eचयन_अंतरभूत_mode_set)
			वापस -EOPNOTSUPP;
		अंतरभूत_mode = nla_get_u8(
				info->attrs[DEVLINK_ATTR_ESWITCH_INLINE_MODE]);
		err = ops->eचयन_अंतरभूत_mode_set(devlink, अंतरभूत_mode,
						   info->extack);
		अगर (err)
			वापस err;
	पूर्ण

	अगर (info->attrs[DEVLINK_ATTR_ESWITCH_ENCAP_MODE]) अणु
		अगर (!ops->eचयन_encap_mode_set)
			वापस -EOPNOTSUPP;
		encap_mode = nla_get_u8(info->attrs[DEVLINK_ATTR_ESWITCH_ENCAP_MODE]);
		err = ops->eचयन_encap_mode_set(devlink, encap_mode,
						  info->extack);
		अगर (err)
			वापस err;
	पूर्ण

	वापस 0;
पूर्ण

पूर्णांक devlink_dpipe_match_put(काष्ठा sk_buff *skb,
			    काष्ठा devlink_dpipe_match *match)
अणु
	काष्ठा devlink_dpipe_header *header = match->header;
	काष्ठा devlink_dpipe_field *field = &header->fields[match->field_id];
	काष्ठा nlattr *match_attr;

	match_attr = nla_nest_start_noflag(skb, DEVLINK_ATTR_DPIPE_MATCH);
	अगर (!match_attr)
		वापस -EMSGSIZE;

	अगर (nla_put_u32(skb, DEVLINK_ATTR_DPIPE_MATCH_TYPE, match->type) ||
	    nla_put_u32(skb, DEVLINK_ATTR_DPIPE_HEADER_INDEX, match->header_index) ||
	    nla_put_u32(skb, DEVLINK_ATTR_DPIPE_HEADER_ID, header->id) ||
	    nla_put_u32(skb, DEVLINK_ATTR_DPIPE_FIELD_ID, field->id) ||
	    nla_put_u8(skb, DEVLINK_ATTR_DPIPE_HEADER_GLOBAL, header->global))
		जाओ nla_put_failure;

	nla_nest_end(skb, match_attr);
	वापस 0;

nla_put_failure:
	nla_nest_cancel(skb, match_attr);
	वापस -EMSGSIZE;
पूर्ण
EXPORT_SYMBOL_GPL(devlink_dpipe_match_put);

अटल पूर्णांक devlink_dpipe_matches_put(काष्ठा devlink_dpipe_table *table,
				     काष्ठा sk_buff *skb)
अणु
	काष्ठा nlattr *matches_attr;

	matches_attr = nla_nest_start_noflag(skb,
					     DEVLINK_ATTR_DPIPE_TABLE_MATCHES);
	अगर (!matches_attr)
		वापस -EMSGSIZE;

	अगर (table->table_ops->matches_dump(table->priv, skb))
		जाओ nla_put_failure;

	nla_nest_end(skb, matches_attr);
	वापस 0;

nla_put_failure:
	nla_nest_cancel(skb, matches_attr);
	वापस -EMSGSIZE;
पूर्ण

पूर्णांक devlink_dpipe_action_put(काष्ठा sk_buff *skb,
			     काष्ठा devlink_dpipe_action *action)
अणु
	काष्ठा devlink_dpipe_header *header = action->header;
	काष्ठा devlink_dpipe_field *field = &header->fields[action->field_id];
	काष्ठा nlattr *action_attr;

	action_attr = nla_nest_start_noflag(skb, DEVLINK_ATTR_DPIPE_ACTION);
	अगर (!action_attr)
		वापस -EMSGSIZE;

	अगर (nla_put_u32(skb, DEVLINK_ATTR_DPIPE_ACTION_TYPE, action->type) ||
	    nla_put_u32(skb, DEVLINK_ATTR_DPIPE_HEADER_INDEX, action->header_index) ||
	    nla_put_u32(skb, DEVLINK_ATTR_DPIPE_HEADER_ID, header->id) ||
	    nla_put_u32(skb, DEVLINK_ATTR_DPIPE_FIELD_ID, field->id) ||
	    nla_put_u8(skb, DEVLINK_ATTR_DPIPE_HEADER_GLOBAL, header->global))
		जाओ nla_put_failure;

	nla_nest_end(skb, action_attr);
	वापस 0;

nla_put_failure:
	nla_nest_cancel(skb, action_attr);
	वापस -EMSGSIZE;
पूर्ण
EXPORT_SYMBOL_GPL(devlink_dpipe_action_put);

अटल पूर्णांक devlink_dpipe_actions_put(काष्ठा devlink_dpipe_table *table,
				     काष्ठा sk_buff *skb)
अणु
	काष्ठा nlattr *actions_attr;

	actions_attr = nla_nest_start_noflag(skb,
					     DEVLINK_ATTR_DPIPE_TABLE_ACTIONS);
	अगर (!actions_attr)
		वापस -EMSGSIZE;

	अगर (table->table_ops->actions_dump(table->priv, skb))
		जाओ nla_put_failure;

	nla_nest_end(skb, actions_attr);
	वापस 0;

nla_put_failure:
	nla_nest_cancel(skb, actions_attr);
	वापस -EMSGSIZE;
पूर्ण

अटल पूर्णांक devlink_dpipe_table_put(काष्ठा sk_buff *skb,
				   काष्ठा devlink_dpipe_table *table)
अणु
	काष्ठा nlattr *table_attr;
	u64 table_size;

	table_size = table->table_ops->size_get(table->priv);
	table_attr = nla_nest_start_noflag(skb, DEVLINK_ATTR_DPIPE_TABLE);
	अगर (!table_attr)
		वापस -EMSGSIZE;

	अगर (nla_put_string(skb, DEVLINK_ATTR_DPIPE_TABLE_NAME, table->name) ||
	    nla_put_u64_64bit(skb, DEVLINK_ATTR_DPIPE_TABLE_SIZE, table_size,
			      DEVLINK_ATTR_PAD))
		जाओ nla_put_failure;
	अगर (nla_put_u8(skb, DEVLINK_ATTR_DPIPE_TABLE_COUNTERS_ENABLED,
		       table->counters_enabled))
		जाओ nla_put_failure;

	अगर (table->resource_valid) अणु
		अगर (nla_put_u64_64bit(skb, DEVLINK_ATTR_DPIPE_TABLE_RESOURCE_ID,
				      table->resource_id, DEVLINK_ATTR_PAD) ||
		    nla_put_u64_64bit(skb, DEVLINK_ATTR_DPIPE_TABLE_RESOURCE_UNITS,
				      table->resource_units, DEVLINK_ATTR_PAD))
			जाओ nla_put_failure;
	पूर्ण
	अगर (devlink_dpipe_matches_put(table, skb))
		जाओ nla_put_failure;

	अगर (devlink_dpipe_actions_put(table, skb))
		जाओ nla_put_failure;

	nla_nest_end(skb, table_attr);
	वापस 0;

nla_put_failure:
	nla_nest_cancel(skb, table_attr);
	वापस -EMSGSIZE;
पूर्ण

अटल पूर्णांक devlink_dpipe_send_and_alloc_skb(काष्ठा sk_buff **pskb,
					    काष्ठा genl_info *info)
अणु
	पूर्णांक err;

	अगर (*pskb) अणु
		err = genlmsg_reply(*pskb, info);
		अगर (err)
			वापस err;
	पूर्ण
	*pskb = genlmsg_new(GENLMSG_DEFAULT_SIZE, GFP_KERNEL);
	अगर (!*pskb)
		वापस -ENOMEM;
	वापस 0;
पूर्ण

अटल पूर्णांक devlink_dpipe_tables_fill(काष्ठा genl_info *info,
				     क्रमागत devlink_command cmd, पूर्णांक flags,
				     काष्ठा list_head *dpipe_tables,
				     स्थिर अक्षर *table_name)
अणु
	काष्ठा devlink *devlink = info->user_ptr[0];
	काष्ठा devlink_dpipe_table *table;
	काष्ठा nlattr *tables_attr;
	काष्ठा sk_buff *skb = शून्य;
	काष्ठा nlmsghdr *nlh;
	bool incomplete;
	व्योम *hdr;
	पूर्णांक i;
	पूर्णांक err;

	table = list_first_entry(dpipe_tables,
				 काष्ठा devlink_dpipe_table, list);
start_again:
	err = devlink_dpipe_send_and_alloc_skb(&skb, info);
	अगर (err)
		वापस err;

	hdr = genlmsg_put(skb, info->snd_portid, info->snd_seq,
			  &devlink_nl_family, NLM_F_MULTI, cmd);
	अगर (!hdr) अणु
		nlmsg_मुक्त(skb);
		वापस -EMSGSIZE;
	पूर्ण

	अगर (devlink_nl_put_handle(skb, devlink))
		जाओ nla_put_failure;
	tables_attr = nla_nest_start_noflag(skb, DEVLINK_ATTR_DPIPE_TABLES);
	अगर (!tables_attr)
		जाओ nla_put_failure;

	i = 0;
	incomplete = false;
	list_क्रम_each_entry_from(table, dpipe_tables, list) अणु
		अगर (!table_name) अणु
			err = devlink_dpipe_table_put(skb, table);
			अगर (err) अणु
				अगर (!i)
					जाओ err_table_put;
				incomplete = true;
				अवरोध;
			पूर्ण
		पूर्ण अन्यथा अणु
			अगर (!म_भेद(table->name, table_name)) अणु
				err = devlink_dpipe_table_put(skb, table);
				अगर (err)
					अवरोध;
			पूर्ण
		पूर्ण
		i++;
	पूर्ण

	nla_nest_end(skb, tables_attr);
	genlmsg_end(skb, hdr);
	अगर (incomplete)
		जाओ start_again;

send_करोne:
	nlh = nlmsg_put(skb, info->snd_portid, info->snd_seq,
			NLMSG_DONE, 0, flags | NLM_F_MULTI);
	अगर (!nlh) अणु
		err = devlink_dpipe_send_and_alloc_skb(&skb, info);
		अगर (err)
			वापस err;
		जाओ send_करोne;
	पूर्ण

	वापस genlmsg_reply(skb, info);

nla_put_failure:
	err = -EMSGSIZE;
err_table_put:
	nlmsg_मुक्त(skb);
	वापस err;
पूर्ण

अटल पूर्णांक devlink_nl_cmd_dpipe_table_get(काष्ठा sk_buff *skb,
					  काष्ठा genl_info *info)
अणु
	काष्ठा devlink *devlink = info->user_ptr[0];
	स्थिर अक्षर *table_name =  शून्य;

	अगर (info->attrs[DEVLINK_ATTR_DPIPE_TABLE_NAME])
		table_name = nla_data(info->attrs[DEVLINK_ATTR_DPIPE_TABLE_NAME]);

	वापस devlink_dpipe_tables_fill(info, DEVLINK_CMD_DPIPE_TABLE_GET, 0,
					 &devlink->dpipe_table_list,
					 table_name);
पूर्ण

अटल पूर्णांक devlink_dpipe_value_put(काष्ठा sk_buff *skb,
				   काष्ठा devlink_dpipe_value *value)
अणु
	अगर (nla_put(skb, DEVLINK_ATTR_DPIPE_VALUE,
		    value->value_size, value->value))
		वापस -EMSGSIZE;
	अगर (value->mask)
		अगर (nla_put(skb, DEVLINK_ATTR_DPIPE_VALUE_MASK,
			    value->value_size, value->mask))
			वापस -EMSGSIZE;
	अगर (value->mapping_valid)
		अगर (nla_put_u32(skb, DEVLINK_ATTR_DPIPE_VALUE_MAPPING,
				value->mapping_value))
			वापस -EMSGSIZE;
	वापस 0;
पूर्ण

अटल पूर्णांक devlink_dpipe_action_value_put(काष्ठा sk_buff *skb,
					  काष्ठा devlink_dpipe_value *value)
अणु
	अगर (!value->action)
		वापस -EINVAL;
	अगर (devlink_dpipe_action_put(skb, value->action))
		वापस -EMSGSIZE;
	अगर (devlink_dpipe_value_put(skb, value))
		वापस -EMSGSIZE;
	वापस 0;
पूर्ण

अटल पूर्णांक devlink_dpipe_action_values_put(काष्ठा sk_buff *skb,
					   काष्ठा devlink_dpipe_value *values,
					   अचिन्हित पूर्णांक values_count)
अणु
	काष्ठा nlattr *action_attr;
	पूर्णांक i;
	पूर्णांक err;

	क्रम (i = 0; i < values_count; i++) अणु
		action_attr = nla_nest_start_noflag(skb,
						    DEVLINK_ATTR_DPIPE_ACTION_VALUE);
		अगर (!action_attr)
			वापस -EMSGSIZE;
		err = devlink_dpipe_action_value_put(skb, &values[i]);
		अगर (err)
			जाओ err_action_value_put;
		nla_nest_end(skb, action_attr);
	पूर्ण
	वापस 0;

err_action_value_put:
	nla_nest_cancel(skb, action_attr);
	वापस err;
पूर्ण

अटल पूर्णांक devlink_dpipe_match_value_put(काष्ठा sk_buff *skb,
					 काष्ठा devlink_dpipe_value *value)
अणु
	अगर (!value->match)
		वापस -EINVAL;
	अगर (devlink_dpipe_match_put(skb, value->match))
		वापस -EMSGSIZE;
	अगर (devlink_dpipe_value_put(skb, value))
		वापस -EMSGSIZE;
	वापस 0;
पूर्ण

अटल पूर्णांक devlink_dpipe_match_values_put(काष्ठा sk_buff *skb,
					  काष्ठा devlink_dpipe_value *values,
					  अचिन्हित पूर्णांक values_count)
अणु
	काष्ठा nlattr *match_attr;
	पूर्णांक i;
	पूर्णांक err;

	क्रम (i = 0; i < values_count; i++) अणु
		match_attr = nla_nest_start_noflag(skb,
						   DEVLINK_ATTR_DPIPE_MATCH_VALUE);
		अगर (!match_attr)
			वापस -EMSGSIZE;
		err = devlink_dpipe_match_value_put(skb, &values[i]);
		अगर (err)
			जाओ err_match_value_put;
		nla_nest_end(skb, match_attr);
	पूर्ण
	वापस 0;

err_match_value_put:
	nla_nest_cancel(skb, match_attr);
	वापस err;
पूर्ण

अटल पूर्णांक devlink_dpipe_entry_put(काष्ठा sk_buff *skb,
				   काष्ठा devlink_dpipe_entry *entry)
अणु
	काष्ठा nlattr *entry_attr, *matches_attr, *actions_attr;
	पूर्णांक err;

	entry_attr = nla_nest_start_noflag(skb, DEVLINK_ATTR_DPIPE_ENTRY);
	अगर (!entry_attr)
		वापस  -EMSGSIZE;

	अगर (nla_put_u64_64bit(skb, DEVLINK_ATTR_DPIPE_ENTRY_INDEX, entry->index,
			      DEVLINK_ATTR_PAD))
		जाओ nla_put_failure;
	अगर (entry->counter_valid)
		अगर (nla_put_u64_64bit(skb, DEVLINK_ATTR_DPIPE_ENTRY_COUNTER,
				      entry->counter, DEVLINK_ATTR_PAD))
			जाओ nla_put_failure;

	matches_attr = nla_nest_start_noflag(skb,
					     DEVLINK_ATTR_DPIPE_ENTRY_MATCH_VALUES);
	अगर (!matches_attr)
		जाओ nla_put_failure;

	err = devlink_dpipe_match_values_put(skb, entry->match_values,
					     entry->match_values_count);
	अगर (err) अणु
		nla_nest_cancel(skb, matches_attr);
		जाओ err_match_values_put;
	पूर्ण
	nla_nest_end(skb, matches_attr);

	actions_attr = nla_nest_start_noflag(skb,
					     DEVLINK_ATTR_DPIPE_ENTRY_ACTION_VALUES);
	अगर (!actions_attr)
		जाओ nla_put_failure;

	err = devlink_dpipe_action_values_put(skb, entry->action_values,
					      entry->action_values_count);
	अगर (err) अणु
		nla_nest_cancel(skb, actions_attr);
		जाओ err_action_values_put;
	पूर्ण
	nla_nest_end(skb, actions_attr);

	nla_nest_end(skb, entry_attr);
	वापस 0;

nla_put_failure:
	err = -EMSGSIZE;
err_match_values_put:
err_action_values_put:
	nla_nest_cancel(skb, entry_attr);
	वापस err;
पूर्ण

अटल काष्ठा devlink_dpipe_table *
devlink_dpipe_table_find(काष्ठा list_head *dpipe_tables,
			 स्थिर अक्षर *table_name, काष्ठा devlink *devlink)
अणु
	काष्ठा devlink_dpipe_table *table;
	list_क्रम_each_entry_rcu(table, dpipe_tables, list,
				lockdep_is_held(&devlink->lock)) अणु
		अगर (!म_भेद(table->name, table_name))
			वापस table;
	पूर्ण
	वापस शून्य;
पूर्ण

पूर्णांक devlink_dpipe_entry_ctx_prepare(काष्ठा devlink_dpipe_dump_ctx *dump_ctx)
अणु
	काष्ठा devlink *devlink;
	पूर्णांक err;

	err = devlink_dpipe_send_and_alloc_skb(&dump_ctx->skb,
					       dump_ctx->info);
	अगर (err)
		वापस err;

	dump_ctx->hdr = genlmsg_put(dump_ctx->skb,
				    dump_ctx->info->snd_portid,
				    dump_ctx->info->snd_seq,
				    &devlink_nl_family, NLM_F_MULTI,
				    dump_ctx->cmd);
	अगर (!dump_ctx->hdr)
		जाओ nla_put_failure;

	devlink = dump_ctx->info->user_ptr[0];
	अगर (devlink_nl_put_handle(dump_ctx->skb, devlink))
		जाओ nla_put_failure;
	dump_ctx->nest = nla_nest_start_noflag(dump_ctx->skb,
					       DEVLINK_ATTR_DPIPE_ENTRIES);
	अगर (!dump_ctx->nest)
		जाओ nla_put_failure;
	वापस 0;

nla_put_failure:
	nlmsg_मुक्त(dump_ctx->skb);
	वापस -EMSGSIZE;
पूर्ण
EXPORT_SYMBOL_GPL(devlink_dpipe_entry_ctx_prepare);

पूर्णांक devlink_dpipe_entry_ctx_append(काष्ठा devlink_dpipe_dump_ctx *dump_ctx,
				   काष्ठा devlink_dpipe_entry *entry)
अणु
	वापस devlink_dpipe_entry_put(dump_ctx->skb, entry);
पूर्ण
EXPORT_SYMBOL_GPL(devlink_dpipe_entry_ctx_append);

पूर्णांक devlink_dpipe_entry_ctx_बंद(काष्ठा devlink_dpipe_dump_ctx *dump_ctx)
अणु
	nla_nest_end(dump_ctx->skb, dump_ctx->nest);
	genlmsg_end(dump_ctx->skb, dump_ctx->hdr);
	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(devlink_dpipe_entry_ctx_बंद);

व्योम devlink_dpipe_entry_clear(काष्ठा devlink_dpipe_entry *entry)

अणु
	अचिन्हित पूर्णांक value_count, value_index;
	काष्ठा devlink_dpipe_value *value;

	value = entry->action_values;
	value_count = entry->action_values_count;
	क्रम (value_index = 0; value_index < value_count; value_index++) अणु
		kमुक्त(value[value_index].value);
		kमुक्त(value[value_index].mask);
	पूर्ण

	value = entry->match_values;
	value_count = entry->match_values_count;
	क्रम (value_index = 0; value_index < value_count; value_index++) अणु
		kमुक्त(value[value_index].value);
		kमुक्त(value[value_index].mask);
	पूर्ण
पूर्ण
EXPORT_SYMBOL(devlink_dpipe_entry_clear);

अटल पूर्णांक devlink_dpipe_entries_fill(काष्ठा genl_info *info,
				      क्रमागत devlink_command cmd, पूर्णांक flags,
				      काष्ठा devlink_dpipe_table *table)
अणु
	काष्ठा devlink_dpipe_dump_ctx dump_ctx;
	काष्ठा nlmsghdr *nlh;
	पूर्णांक err;

	dump_ctx.skb = शून्य;
	dump_ctx.cmd = cmd;
	dump_ctx.info = info;

	err = table->table_ops->entries_dump(table->priv,
					     table->counters_enabled,
					     &dump_ctx);
	अगर (err)
		वापस err;

send_करोne:
	nlh = nlmsg_put(dump_ctx.skb, info->snd_portid, info->snd_seq,
			NLMSG_DONE, 0, flags | NLM_F_MULTI);
	अगर (!nlh) अणु
		err = devlink_dpipe_send_and_alloc_skb(&dump_ctx.skb, info);
		अगर (err)
			वापस err;
		जाओ send_करोne;
	पूर्ण
	वापस genlmsg_reply(dump_ctx.skb, info);
पूर्ण

अटल पूर्णांक devlink_nl_cmd_dpipe_entries_get(काष्ठा sk_buff *skb,
					    काष्ठा genl_info *info)
अणु
	काष्ठा devlink *devlink = info->user_ptr[0];
	काष्ठा devlink_dpipe_table *table;
	स्थिर अक्षर *table_name;

	अगर (!info->attrs[DEVLINK_ATTR_DPIPE_TABLE_NAME])
		वापस -EINVAL;

	table_name = nla_data(info->attrs[DEVLINK_ATTR_DPIPE_TABLE_NAME]);
	table = devlink_dpipe_table_find(&devlink->dpipe_table_list,
					 table_name, devlink);
	अगर (!table)
		वापस -EINVAL;

	अगर (!table->table_ops->entries_dump)
		वापस -EINVAL;

	वापस devlink_dpipe_entries_fill(info, DEVLINK_CMD_DPIPE_ENTRIES_GET,
					  0, table);
पूर्ण

अटल पूर्णांक devlink_dpipe_fields_put(काष्ठा sk_buff *skb,
				    स्थिर काष्ठा devlink_dpipe_header *header)
अणु
	काष्ठा devlink_dpipe_field *field;
	काष्ठा nlattr *field_attr;
	पूर्णांक i;

	क्रम (i = 0; i < header->fields_count; i++) अणु
		field = &header->fields[i];
		field_attr = nla_nest_start_noflag(skb,
						   DEVLINK_ATTR_DPIPE_FIELD);
		अगर (!field_attr)
			वापस -EMSGSIZE;
		अगर (nla_put_string(skb, DEVLINK_ATTR_DPIPE_FIELD_NAME, field->name) ||
		    nla_put_u32(skb, DEVLINK_ATTR_DPIPE_FIELD_ID, field->id) ||
		    nla_put_u32(skb, DEVLINK_ATTR_DPIPE_FIELD_BITWIDTH, field->bitwidth) ||
		    nla_put_u32(skb, DEVLINK_ATTR_DPIPE_FIELD_MAPPING_TYPE, field->mapping_type))
			जाओ nla_put_failure;
		nla_nest_end(skb, field_attr);
	पूर्ण
	वापस 0;

nla_put_failure:
	nla_nest_cancel(skb, field_attr);
	वापस -EMSGSIZE;
पूर्ण

अटल पूर्णांक devlink_dpipe_header_put(काष्ठा sk_buff *skb,
				    काष्ठा devlink_dpipe_header *header)
अणु
	काष्ठा nlattr *fields_attr, *header_attr;
	पूर्णांक err;

	header_attr = nla_nest_start_noflag(skb, DEVLINK_ATTR_DPIPE_HEADER);
	अगर (!header_attr)
		वापस -EMSGSIZE;

	अगर (nla_put_string(skb, DEVLINK_ATTR_DPIPE_HEADER_NAME, header->name) ||
	    nla_put_u32(skb, DEVLINK_ATTR_DPIPE_HEADER_ID, header->id) ||
	    nla_put_u8(skb, DEVLINK_ATTR_DPIPE_HEADER_GLOBAL, header->global))
		जाओ nla_put_failure;

	fields_attr = nla_nest_start_noflag(skb,
					    DEVLINK_ATTR_DPIPE_HEADER_FIELDS);
	अगर (!fields_attr)
		जाओ nla_put_failure;

	err = devlink_dpipe_fields_put(skb, header);
	अगर (err) अणु
		nla_nest_cancel(skb, fields_attr);
		जाओ nla_put_failure;
	पूर्ण
	nla_nest_end(skb, fields_attr);
	nla_nest_end(skb, header_attr);
	वापस 0;

nla_put_failure:
	err = -EMSGSIZE;
	nla_nest_cancel(skb, header_attr);
	वापस err;
पूर्ण

अटल पूर्णांक devlink_dpipe_headers_fill(काष्ठा genl_info *info,
				      क्रमागत devlink_command cmd, पूर्णांक flags,
				      काष्ठा devlink_dpipe_headers *
				      dpipe_headers)
अणु
	काष्ठा devlink *devlink = info->user_ptr[0];
	काष्ठा nlattr *headers_attr;
	काष्ठा sk_buff *skb = शून्य;
	काष्ठा nlmsghdr *nlh;
	व्योम *hdr;
	पूर्णांक i, j;
	पूर्णांक err;

	i = 0;
start_again:
	err = devlink_dpipe_send_and_alloc_skb(&skb, info);
	अगर (err)
		वापस err;

	hdr = genlmsg_put(skb, info->snd_portid, info->snd_seq,
			  &devlink_nl_family, NLM_F_MULTI, cmd);
	अगर (!hdr) अणु
		nlmsg_मुक्त(skb);
		वापस -EMSGSIZE;
	पूर्ण

	अगर (devlink_nl_put_handle(skb, devlink))
		जाओ nla_put_failure;
	headers_attr = nla_nest_start_noflag(skb, DEVLINK_ATTR_DPIPE_HEADERS);
	अगर (!headers_attr)
		जाओ nla_put_failure;

	j = 0;
	क्रम (; i < dpipe_headers->headers_count; i++) अणु
		err = devlink_dpipe_header_put(skb, dpipe_headers->headers[i]);
		अगर (err) अणु
			अगर (!j)
				जाओ err_table_put;
			अवरोध;
		पूर्ण
		j++;
	पूर्ण
	nla_nest_end(skb, headers_attr);
	genlmsg_end(skb, hdr);
	अगर (i != dpipe_headers->headers_count)
		जाओ start_again;

send_करोne:
	nlh = nlmsg_put(skb, info->snd_portid, info->snd_seq,
			NLMSG_DONE, 0, flags | NLM_F_MULTI);
	अगर (!nlh) अणु
		err = devlink_dpipe_send_and_alloc_skb(&skb, info);
		अगर (err)
			वापस err;
		जाओ send_करोne;
	पूर्ण
	वापस genlmsg_reply(skb, info);

nla_put_failure:
	err = -EMSGSIZE;
err_table_put:
	nlmsg_मुक्त(skb);
	वापस err;
पूर्ण

अटल पूर्णांक devlink_nl_cmd_dpipe_headers_get(काष्ठा sk_buff *skb,
					    काष्ठा genl_info *info)
अणु
	काष्ठा devlink *devlink = info->user_ptr[0];

	अगर (!devlink->dpipe_headers)
		वापस -EOPNOTSUPP;
	वापस devlink_dpipe_headers_fill(info, DEVLINK_CMD_DPIPE_HEADERS_GET,
					  0, devlink->dpipe_headers);
पूर्ण

अटल पूर्णांक devlink_dpipe_table_counters_set(काष्ठा devlink *devlink,
					    स्थिर अक्षर *table_name,
					    bool enable)
अणु
	काष्ठा devlink_dpipe_table *table;

	table = devlink_dpipe_table_find(&devlink->dpipe_table_list,
					 table_name, devlink);
	अगर (!table)
		वापस -EINVAL;

	अगर (table->counter_control_बाह्य)
		वापस -EOPNOTSUPP;

	अगर (!(table->counters_enabled ^ enable))
		वापस 0;

	table->counters_enabled = enable;
	अगर (table->table_ops->counters_set_update)
		table->table_ops->counters_set_update(table->priv, enable);
	वापस 0;
पूर्ण

अटल पूर्णांक devlink_nl_cmd_dpipe_table_counters_set(काष्ठा sk_buff *skb,
						   काष्ठा genl_info *info)
अणु
	काष्ठा devlink *devlink = info->user_ptr[0];
	स्थिर अक्षर *table_name;
	bool counters_enable;

	अगर (!info->attrs[DEVLINK_ATTR_DPIPE_TABLE_NAME] ||
	    !info->attrs[DEVLINK_ATTR_DPIPE_TABLE_COUNTERS_ENABLED])
		वापस -EINVAL;

	table_name = nla_data(info->attrs[DEVLINK_ATTR_DPIPE_TABLE_NAME]);
	counters_enable = !!nla_get_u8(info->attrs[DEVLINK_ATTR_DPIPE_TABLE_COUNTERS_ENABLED]);

	वापस devlink_dpipe_table_counters_set(devlink, table_name,
						counters_enable);
पूर्ण

अटल काष्ठा devlink_resource *
devlink_resource_find(काष्ठा devlink *devlink,
		      काष्ठा devlink_resource *resource, u64 resource_id)
अणु
	काष्ठा list_head *resource_list;

	अगर (resource)
		resource_list = &resource->resource_list;
	अन्यथा
		resource_list = &devlink->resource_list;

	list_क्रम_each_entry(resource, resource_list, list) अणु
		काष्ठा devlink_resource *child_resource;

		अगर (resource->id == resource_id)
			वापस resource;

		child_resource = devlink_resource_find(devlink, resource,
						       resource_id);
		अगर (child_resource)
			वापस child_resource;
	पूर्ण
	वापस शून्य;
पूर्ण

अटल व्योम
devlink_resource_validate_children(काष्ठा devlink_resource *resource)
अणु
	काष्ठा devlink_resource *child_resource;
	bool size_valid = true;
	u64 parts_size = 0;

	अगर (list_empty(&resource->resource_list))
		जाओ out;

	list_क्रम_each_entry(child_resource, &resource->resource_list, list)
		parts_size += child_resource->size_new;

	अगर (parts_size > resource->size_new)
		size_valid = false;
out:
	resource->size_valid = size_valid;
पूर्ण

अटल पूर्णांक
devlink_resource_validate_size(काष्ठा devlink_resource *resource, u64 size,
			       काष्ठा netlink_ext_ack *extack)
अणु
	u64 reminder;
	पूर्णांक err = 0;

	अगर (size > resource->size_params.size_max) अणु
		NL_SET_ERR_MSG_MOD(extack, "Size larger than maximum");
		err = -EINVAL;
	पूर्ण

	अगर (size < resource->size_params.size_min) अणु
		NL_SET_ERR_MSG_MOD(extack, "Size smaller than minimum");
		err = -EINVAL;
	पूर्ण

	भाग64_u64_rem(size, resource->size_params.size_granularity, &reminder);
	अगर (reminder) अणु
		NL_SET_ERR_MSG_MOD(extack, "Wrong granularity");
		err = -EINVAL;
	पूर्ण

	वापस err;
पूर्ण

अटल पूर्णांक devlink_nl_cmd_resource_set(काष्ठा sk_buff *skb,
				       काष्ठा genl_info *info)
अणु
	काष्ठा devlink *devlink = info->user_ptr[0];
	काष्ठा devlink_resource *resource;
	u64 resource_id;
	u64 size;
	पूर्णांक err;

	अगर (!info->attrs[DEVLINK_ATTR_RESOURCE_ID] ||
	    !info->attrs[DEVLINK_ATTR_RESOURCE_SIZE])
		वापस -EINVAL;
	resource_id = nla_get_u64(info->attrs[DEVLINK_ATTR_RESOURCE_ID]);

	resource = devlink_resource_find(devlink, शून्य, resource_id);
	अगर (!resource)
		वापस -EINVAL;

	size = nla_get_u64(info->attrs[DEVLINK_ATTR_RESOURCE_SIZE]);
	err = devlink_resource_validate_size(resource, size, info->extack);
	अगर (err)
		वापस err;

	resource->size_new = size;
	devlink_resource_validate_children(resource);
	अगर (resource->parent)
		devlink_resource_validate_children(resource->parent);
	वापस 0;
पूर्ण

अटल पूर्णांक
devlink_resource_size_params_put(काष्ठा devlink_resource *resource,
				 काष्ठा sk_buff *skb)
अणु
	काष्ठा devlink_resource_size_params *size_params;

	size_params = &resource->size_params;
	अगर (nla_put_u64_64bit(skb, DEVLINK_ATTR_RESOURCE_SIZE_GRAN,
			      size_params->size_granularity, DEVLINK_ATTR_PAD) ||
	    nla_put_u64_64bit(skb, DEVLINK_ATTR_RESOURCE_SIZE_MAX,
			      size_params->size_max, DEVLINK_ATTR_PAD) ||
	    nla_put_u64_64bit(skb, DEVLINK_ATTR_RESOURCE_SIZE_MIN,
			      size_params->size_min, DEVLINK_ATTR_PAD) ||
	    nla_put_u8(skb, DEVLINK_ATTR_RESOURCE_UNIT, size_params->unit))
		वापस -EMSGSIZE;
	वापस 0;
पूर्ण

अटल पूर्णांक devlink_resource_occ_put(काष्ठा devlink_resource *resource,
				    काष्ठा sk_buff *skb)
अणु
	अगर (!resource->occ_get)
		वापस 0;
	वापस nla_put_u64_64bit(skb, DEVLINK_ATTR_RESOURCE_OCC,
				 resource->occ_get(resource->occ_get_priv),
				 DEVLINK_ATTR_PAD);
पूर्ण

अटल पूर्णांक devlink_resource_put(काष्ठा devlink *devlink, काष्ठा sk_buff *skb,
				काष्ठा devlink_resource *resource)
अणु
	काष्ठा devlink_resource *child_resource;
	काष्ठा nlattr *child_resource_attr;
	काष्ठा nlattr *resource_attr;

	resource_attr = nla_nest_start_noflag(skb, DEVLINK_ATTR_RESOURCE);
	अगर (!resource_attr)
		वापस -EMSGSIZE;

	अगर (nla_put_string(skb, DEVLINK_ATTR_RESOURCE_NAME, resource->name) ||
	    nla_put_u64_64bit(skb, DEVLINK_ATTR_RESOURCE_SIZE, resource->size,
			      DEVLINK_ATTR_PAD) ||
	    nla_put_u64_64bit(skb, DEVLINK_ATTR_RESOURCE_ID, resource->id,
			      DEVLINK_ATTR_PAD))
		जाओ nla_put_failure;
	अगर (resource->size != resource->size_new)
		nla_put_u64_64bit(skb, DEVLINK_ATTR_RESOURCE_SIZE_NEW,
				  resource->size_new, DEVLINK_ATTR_PAD);
	अगर (devlink_resource_occ_put(resource, skb))
		जाओ nla_put_failure;
	अगर (devlink_resource_size_params_put(resource, skb))
		जाओ nla_put_failure;
	अगर (list_empty(&resource->resource_list))
		जाओ out;

	अगर (nla_put_u8(skb, DEVLINK_ATTR_RESOURCE_SIZE_VALID,
		       resource->size_valid))
		जाओ nla_put_failure;

	child_resource_attr = nla_nest_start_noflag(skb,
						    DEVLINK_ATTR_RESOURCE_LIST);
	अगर (!child_resource_attr)
		जाओ nla_put_failure;

	list_क्रम_each_entry(child_resource, &resource->resource_list, list) अणु
		अगर (devlink_resource_put(devlink, skb, child_resource))
			जाओ resource_put_failure;
	पूर्ण

	nla_nest_end(skb, child_resource_attr);
out:
	nla_nest_end(skb, resource_attr);
	वापस 0;

resource_put_failure:
	nla_nest_cancel(skb, child_resource_attr);
nla_put_failure:
	nla_nest_cancel(skb, resource_attr);
	वापस -EMSGSIZE;
पूर्ण

अटल पूर्णांक devlink_resource_fill(काष्ठा genl_info *info,
				 क्रमागत devlink_command cmd, पूर्णांक flags)
अणु
	काष्ठा devlink *devlink = info->user_ptr[0];
	काष्ठा devlink_resource *resource;
	काष्ठा nlattr *resources_attr;
	काष्ठा sk_buff *skb = शून्य;
	काष्ठा nlmsghdr *nlh;
	bool incomplete;
	व्योम *hdr;
	पूर्णांक i;
	पूर्णांक err;

	resource = list_first_entry(&devlink->resource_list,
				    काष्ठा devlink_resource, list);
start_again:
	err = devlink_dpipe_send_and_alloc_skb(&skb, info);
	अगर (err)
		वापस err;

	hdr = genlmsg_put(skb, info->snd_portid, info->snd_seq,
			  &devlink_nl_family, NLM_F_MULTI, cmd);
	अगर (!hdr) अणु
		nlmsg_मुक्त(skb);
		वापस -EMSGSIZE;
	पूर्ण

	अगर (devlink_nl_put_handle(skb, devlink))
		जाओ nla_put_failure;

	resources_attr = nla_nest_start_noflag(skb,
					       DEVLINK_ATTR_RESOURCE_LIST);
	अगर (!resources_attr)
		जाओ nla_put_failure;

	incomplete = false;
	i = 0;
	list_क्रम_each_entry_from(resource, &devlink->resource_list, list) अणु
		err = devlink_resource_put(devlink, skb, resource);
		अगर (err) अणु
			अगर (!i)
				जाओ err_resource_put;
			incomplete = true;
			अवरोध;
		पूर्ण
		i++;
	पूर्ण
	nla_nest_end(skb, resources_attr);
	genlmsg_end(skb, hdr);
	अगर (incomplete)
		जाओ start_again;
send_करोne:
	nlh = nlmsg_put(skb, info->snd_portid, info->snd_seq,
			NLMSG_DONE, 0, flags | NLM_F_MULTI);
	अगर (!nlh) अणु
		err = devlink_dpipe_send_and_alloc_skb(&skb, info);
		अगर (err)
			वापस err;
		जाओ send_करोne;
	पूर्ण
	वापस genlmsg_reply(skb, info);

nla_put_failure:
	err = -EMSGSIZE;
err_resource_put:
	nlmsg_मुक्त(skb);
	वापस err;
पूर्ण

अटल पूर्णांक devlink_nl_cmd_resource_dump(काष्ठा sk_buff *skb,
					काष्ठा genl_info *info)
अणु
	काष्ठा devlink *devlink = info->user_ptr[0];

	अगर (list_empty(&devlink->resource_list))
		वापस -EOPNOTSUPP;

	वापस devlink_resource_fill(info, DEVLINK_CMD_RESOURCE_DUMP, 0);
पूर्ण

अटल पूर्णांक
devlink_resources_validate(काष्ठा devlink *devlink,
			   काष्ठा devlink_resource *resource,
			   काष्ठा genl_info *info)
अणु
	काष्ठा list_head *resource_list;
	पूर्णांक err = 0;

	अगर (resource)
		resource_list = &resource->resource_list;
	अन्यथा
		resource_list = &devlink->resource_list;

	list_क्रम_each_entry(resource, resource_list, list) अणु
		अगर (!resource->size_valid)
			वापस -EINVAL;
		err = devlink_resources_validate(devlink, resource, info);
		अगर (err)
			वापस err;
	पूर्ण
	वापस err;
पूर्ण

अटल काष्ठा net *devlink_netns_get(काष्ठा sk_buff *skb,
				     काष्ठा genl_info *info)
अणु
	काष्ठा nlattr *netns_pid_attr = info->attrs[DEVLINK_ATTR_NETNS_PID];
	काष्ठा nlattr *netns_fd_attr = info->attrs[DEVLINK_ATTR_NETNS_FD];
	काष्ठा nlattr *netns_id_attr = info->attrs[DEVLINK_ATTR_NETNS_ID];
	काष्ठा net *net;

	अगर (!!netns_pid_attr + !!netns_fd_attr + !!netns_id_attr > 1) अणु
		NL_SET_ERR_MSG_MOD(info->extack, "multiple netns identifying attributes specified");
		वापस ERR_PTR(-EINVAL);
	पूर्ण

	अगर (netns_pid_attr) अणु
		net = get_net_ns_by_pid(nla_get_u32(netns_pid_attr));
	पूर्ण अन्यथा अगर (netns_fd_attr) अणु
		net = get_net_ns_by_fd(nla_get_u32(netns_fd_attr));
	पूर्ण अन्यथा अगर (netns_id_attr) अणु
		net = get_net_ns_by_id(sock_net(skb->sk),
				       nla_get_u32(netns_id_attr));
		अगर (!net)
			net = ERR_PTR(-EINVAL);
	पूर्ण अन्यथा अणु
		WARN_ON(1);
		net = ERR_PTR(-EINVAL);
	पूर्ण
	अगर (IS_ERR(net)) अणु
		NL_SET_ERR_MSG_MOD(info->extack, "Unknown network namespace");
		वापस ERR_PTR(-EINVAL);
	पूर्ण
	अगर (!netlink_ns_capable(skb, net->user_ns, CAP_NET_ADMIN)) अणु
		put_net(net);
		वापस ERR_PTR(-EPERM);
	पूर्ण
	वापस net;
पूर्ण

अटल व्योम devlink_param_notअगरy(काष्ठा devlink *devlink,
				 अचिन्हित पूर्णांक port_index,
				 काष्ठा devlink_param_item *param_item,
				 क्रमागत devlink_command cmd);

अटल व्योम devlink_reload_netns_change(काष्ठा devlink *devlink,
					काष्ठा net *dest_net)
अणु
	काष्ठा devlink_param_item *param_item;

	/* Userspace needs to be notअगरied about devlink objects
	 * हटाओd from original and entering new network namespace.
	 * The rest of the devlink objects are re-created during
	 * reload process so the notअगरications are generated separatelly.
	 */

	list_क्रम_each_entry(param_item, &devlink->param_list, list)
		devlink_param_notअगरy(devlink, 0, param_item,
				     DEVLINK_CMD_PARAM_DEL);
	devlink_notअगरy(devlink, DEVLINK_CMD_DEL);

	__devlink_net_set(devlink, dest_net);

	devlink_notअगरy(devlink, DEVLINK_CMD_NEW);
	list_क्रम_each_entry(param_item, &devlink->param_list, list)
		devlink_param_notअगरy(devlink, 0, param_item,
				     DEVLINK_CMD_PARAM_NEW);
पूर्ण

अटल bool devlink_reload_supported(स्थिर काष्ठा devlink_ops *ops)
अणु
	वापस ops->reload_करोwn && ops->reload_up;
पूर्ण

अटल व्योम devlink_reload_failed_set(काष्ठा devlink *devlink,
				      bool reload_failed)
अणु
	अगर (devlink->reload_failed == reload_failed)
		वापस;
	devlink->reload_failed = reload_failed;
	devlink_notअगरy(devlink, DEVLINK_CMD_NEW);
पूर्ण

bool devlink_is_reload_failed(स्थिर काष्ठा devlink *devlink)
अणु
	वापस devlink->reload_failed;
पूर्ण
EXPORT_SYMBOL_GPL(devlink_is_reload_failed);

अटल व्योम
__devlink_reload_stats_update(काष्ठा devlink *devlink, u32 *reload_stats,
			      क्रमागत devlink_reload_limit limit, u32 actions_perक्रमmed)
अणु
	अचिन्हित दीर्घ actions = actions_perक्रमmed;
	पूर्णांक stat_idx;
	पूर्णांक action;

	क्रम_each_set_bit(action, &actions, __DEVLINK_RELOAD_ACTION_MAX) अणु
		stat_idx = limit * __DEVLINK_RELOAD_ACTION_MAX + action;
		reload_stats[stat_idx]++;
	पूर्ण
	devlink_notअगरy(devlink, DEVLINK_CMD_NEW);
पूर्ण

अटल व्योम
devlink_reload_stats_update(काष्ठा devlink *devlink, क्रमागत devlink_reload_limit limit,
			    u32 actions_perक्रमmed)
अणु
	__devlink_reload_stats_update(devlink, devlink->stats.reload_stats, limit,
				      actions_perक्रमmed);
पूर्ण

/**
 *	devlink_remote_reload_actions_perक्रमmed - Update devlink on reload actions
 *	  perक्रमmed which are not a direct result of devlink reload call.
 *
 *	This should be called by a driver after perक्रमming reload actions in हाल it was not
 *	a result of devlink reload call. For example fw_activate was perक्रमmed as a result
 *	of devlink reload triggered fw_activate on another host.
 *	The motivation क्रम this function is to keep data on reload actions perक्रमmed on this
 *	function whether it was करोne due to direct devlink reload call or not.
 *
 *	@devlink: devlink
 *	@limit: reload limit
 *	@actions_perक्रमmed: biपंचांगask of actions perक्रमmed
 */
व्योम devlink_remote_reload_actions_perक्रमmed(काष्ठा devlink *devlink,
					     क्रमागत devlink_reload_limit limit,
					     u32 actions_perक्रमmed)
अणु
	अगर (WARN_ON(!actions_perक्रमmed ||
		    actions_perक्रमmed & BIT(DEVLINK_RELOAD_ACTION_UNSPEC) ||
		    actions_perक्रमmed >= BIT(__DEVLINK_RELOAD_ACTION_MAX) ||
		    limit > DEVLINK_RELOAD_LIMIT_MAX))
		वापस;

	__devlink_reload_stats_update(devlink, devlink->stats.remote_reload_stats, limit,
				      actions_perक्रमmed);
पूर्ण
EXPORT_SYMBOL_GPL(devlink_remote_reload_actions_perक्रमmed);

अटल पूर्णांक devlink_reload(काष्ठा devlink *devlink, काष्ठा net *dest_net,
			  क्रमागत devlink_reload_action action, क्रमागत devlink_reload_limit limit,
			  u32 *actions_perक्रमmed, काष्ठा netlink_ext_ack *extack)
अणु
	u32 remote_reload_stats[DEVLINK_RELOAD_STATS_ARRAY_SIZE];
	पूर्णांक err;

	अगर (!devlink->reload_enabled)
		वापस -EOPNOTSUPP;

	स_नकल(remote_reload_stats, devlink->stats.remote_reload_stats,
	       माप(remote_reload_stats));
	err = devlink->ops->reload_करोwn(devlink, !!dest_net, action, limit, extack);
	अगर (err)
		वापस err;

	अगर (dest_net && !net_eq(dest_net, devlink_net(devlink)))
		devlink_reload_netns_change(devlink, dest_net);

	err = devlink->ops->reload_up(devlink, action, limit, actions_perक्रमmed, extack);
	devlink_reload_failed_set(devlink, !!err);
	अगर (err)
		वापस err;

	WARN_ON(!(*actions_perक्रमmed & BIT(action)));
	/* Catch driver on updating the remote action within devlink reload */
	WARN_ON(स_भेद(remote_reload_stats, devlink->stats.remote_reload_stats,
		       माप(remote_reload_stats)));
	devlink_reload_stats_update(devlink, limit, *actions_perक्रमmed);
	वापस 0;
पूर्ण

अटल पूर्णांक
devlink_nl_reload_actions_perक्रमmed_snd(काष्ठा devlink *devlink, u32 actions_perक्रमmed,
					क्रमागत devlink_command cmd, काष्ठा genl_info *info)
अणु
	काष्ठा sk_buff *msg;
	व्योम *hdr;

	msg = nlmsg_new(NLMSG_DEFAULT_SIZE, GFP_KERNEL);
	अगर (!msg)
		वापस -ENOMEM;

	hdr = genlmsg_put(msg, info->snd_portid, info->snd_seq, &devlink_nl_family, 0, cmd);
	अगर (!hdr)
		जाओ मुक्त_msg;

	अगर (devlink_nl_put_handle(msg, devlink))
		जाओ nla_put_failure;

	अगर (nla_put_bitfield32(msg, DEVLINK_ATTR_RELOAD_ACTIONS_PERFORMED, actions_perक्रमmed,
			       actions_perक्रमmed))
		जाओ nla_put_failure;
	genlmsg_end(msg, hdr);

	वापस genlmsg_reply(msg, info);

nla_put_failure:
	genlmsg_cancel(msg, hdr);
मुक्त_msg:
	nlmsg_मुक्त(msg);
	वापस -EMSGSIZE;
पूर्ण

अटल पूर्णांक devlink_nl_cmd_reload(काष्ठा sk_buff *skb, काष्ठा genl_info *info)
अणु
	काष्ठा devlink *devlink = info->user_ptr[0];
	क्रमागत devlink_reload_action action;
	क्रमागत devlink_reload_limit limit;
	काष्ठा net *dest_net = शून्य;
	u32 actions_perक्रमmed;
	पूर्णांक err;

	अगर (!devlink_reload_supported(devlink->ops))
		वापस -EOPNOTSUPP;

	err = devlink_resources_validate(devlink, शून्य, info);
	अगर (err) अणु
		NL_SET_ERR_MSG_MOD(info->extack, "resources size validation failed");
		वापस err;
	पूर्ण

	अगर (info->attrs[DEVLINK_ATTR_NETNS_PID] ||
	    info->attrs[DEVLINK_ATTR_NETNS_FD] ||
	    info->attrs[DEVLINK_ATTR_NETNS_ID]) अणु
		dest_net = devlink_netns_get(skb, info);
		अगर (IS_ERR(dest_net))
			वापस PTR_ERR(dest_net);
	पूर्ण

	अगर (info->attrs[DEVLINK_ATTR_RELOAD_ACTION])
		action = nla_get_u8(info->attrs[DEVLINK_ATTR_RELOAD_ACTION]);
	अन्यथा
		action = DEVLINK_RELOAD_ACTION_DRIVER_REINIT;

	अगर (!devlink_reload_action_is_supported(devlink, action)) अणु
		NL_SET_ERR_MSG_MOD(info->extack,
				   "Requested reload action is not supported by the driver");
		वापस -EOPNOTSUPP;
	पूर्ण

	limit = DEVLINK_RELOAD_LIMIT_UNSPEC;
	अगर (info->attrs[DEVLINK_ATTR_RELOAD_LIMITS]) अणु
		काष्ठा nla_bitfield32 limits;
		u32 limits_selected;

		limits = nla_get_bitfield32(info->attrs[DEVLINK_ATTR_RELOAD_LIMITS]);
		limits_selected = limits.value & limits.selector;
		अगर (!limits_selected) अणु
			NL_SET_ERR_MSG_MOD(info->extack, "Invalid limit selected");
			वापस -EINVAL;
		पूर्ण
		क्रम (limit = 0 ; limit <= DEVLINK_RELOAD_LIMIT_MAX ; limit++)
			अगर (limits_selected & BIT(limit))
				अवरोध;
		/* UAPI enables multiselection, but currently it is not used */
		अगर (limits_selected != BIT(limit)) अणु
			NL_SET_ERR_MSG_MOD(info->extack,
					   "Multiselection of limit is not supported");
			वापस -EOPNOTSUPP;
		पूर्ण
		अगर (!devlink_reload_limit_is_supported(devlink, limit)) अणु
			NL_SET_ERR_MSG_MOD(info->extack,
					   "Requested limit is not supported by the driver");
			वापस -EOPNOTSUPP;
		पूर्ण
		अगर (devlink_reload_combination_is_invalid(action, limit)) अणु
			NL_SET_ERR_MSG_MOD(info->extack,
					   "Requested limit is invalid for this action");
			वापस -EINVAL;
		पूर्ण
	पूर्ण
	err = devlink_reload(devlink, dest_net, action, limit, &actions_perक्रमmed, info->extack);

	अगर (dest_net)
		put_net(dest_net);

	अगर (err)
		वापस err;
	/* For backward compatibility generate reply only अगर attributes used by user */
	अगर (!info->attrs[DEVLINK_ATTR_RELOAD_ACTION] && !info->attrs[DEVLINK_ATTR_RELOAD_LIMITS])
		वापस 0;

	वापस devlink_nl_reload_actions_perक्रमmed_snd(devlink, actions_perक्रमmed,
						       DEVLINK_CMD_RELOAD, info);
पूर्ण

अटल पूर्णांक devlink_nl_flash_update_fill(काष्ठा sk_buff *msg,
					काष्ठा devlink *devlink,
					क्रमागत devlink_command cmd,
					काष्ठा devlink_flash_notअगरy *params)
अणु
	व्योम *hdr;

	hdr = genlmsg_put(msg, 0, 0, &devlink_nl_family, 0, cmd);
	अगर (!hdr)
		वापस -EMSGSIZE;

	अगर (devlink_nl_put_handle(msg, devlink))
		जाओ nla_put_failure;

	अगर (cmd != DEVLINK_CMD_FLASH_UPDATE_STATUS)
		जाओ out;

	अगर (params->status_msg &&
	    nla_put_string(msg, DEVLINK_ATTR_FLASH_UPDATE_STATUS_MSG,
			   params->status_msg))
		जाओ nla_put_failure;
	अगर (params->component &&
	    nla_put_string(msg, DEVLINK_ATTR_FLASH_UPDATE_COMPONENT,
			   params->component))
		जाओ nla_put_failure;
	अगर (nla_put_u64_64bit(msg, DEVLINK_ATTR_FLASH_UPDATE_STATUS_DONE,
			      params->करोne, DEVLINK_ATTR_PAD))
		जाओ nla_put_failure;
	अगर (nla_put_u64_64bit(msg, DEVLINK_ATTR_FLASH_UPDATE_STATUS_TOTAL,
			      params->total, DEVLINK_ATTR_PAD))
		जाओ nla_put_failure;
	अगर (nla_put_u64_64bit(msg, DEVLINK_ATTR_FLASH_UPDATE_STATUS_TIMEOUT,
			      params->समयout, DEVLINK_ATTR_PAD))
		जाओ nla_put_failure;

out:
	genlmsg_end(msg, hdr);
	वापस 0;

nla_put_failure:
	genlmsg_cancel(msg, hdr);
	वापस -EMSGSIZE;
पूर्ण

अटल व्योम __devlink_flash_update_notअगरy(काष्ठा devlink *devlink,
					  क्रमागत devlink_command cmd,
					  काष्ठा devlink_flash_notअगरy *params)
अणु
	काष्ठा sk_buff *msg;
	पूर्णांक err;

	WARN_ON(cmd != DEVLINK_CMD_FLASH_UPDATE &&
		cmd != DEVLINK_CMD_FLASH_UPDATE_END &&
		cmd != DEVLINK_CMD_FLASH_UPDATE_STATUS);

	msg = nlmsg_new(NLMSG_DEFAULT_SIZE, GFP_KERNEL);
	अगर (!msg)
		वापस;

	err = devlink_nl_flash_update_fill(msg, devlink, cmd, params);
	अगर (err)
		जाओ out_मुक्त_msg;

	genlmsg_multicast_netns(&devlink_nl_family, devlink_net(devlink),
				msg, 0, DEVLINK_MCGRP_CONFIG, GFP_KERNEL);
	वापस;

out_मुक्त_msg:
	nlmsg_मुक्त(msg);
पूर्ण

अटल व्योम devlink_flash_update_begin_notअगरy(काष्ठा devlink *devlink)
अणु
	काष्ठा devlink_flash_notअगरy params = अणु 0 पूर्ण;

	__devlink_flash_update_notअगरy(devlink,
				      DEVLINK_CMD_FLASH_UPDATE,
				      &params);
पूर्ण

अटल व्योम devlink_flash_update_end_notअगरy(काष्ठा devlink *devlink)
अणु
	काष्ठा devlink_flash_notअगरy params = अणु 0 पूर्ण;

	__devlink_flash_update_notअगरy(devlink,
				      DEVLINK_CMD_FLASH_UPDATE_END,
				      &params);
पूर्ण

व्योम devlink_flash_update_status_notअगरy(काष्ठा devlink *devlink,
					स्थिर अक्षर *status_msg,
					स्थिर अक्षर *component,
					अचिन्हित दीर्घ करोne,
					अचिन्हित दीर्घ total)
अणु
	काष्ठा devlink_flash_notअगरy params = अणु
		.status_msg = status_msg,
		.component = component,
		.करोne = करोne,
		.total = total,
	पूर्ण;

	__devlink_flash_update_notअगरy(devlink,
				      DEVLINK_CMD_FLASH_UPDATE_STATUS,
				      &params);
पूर्ण
EXPORT_SYMBOL_GPL(devlink_flash_update_status_notअगरy);

व्योम devlink_flash_update_समयout_notअगरy(काष्ठा devlink *devlink,
					 स्थिर अक्षर *status_msg,
					 स्थिर अक्षर *component,
					 अचिन्हित दीर्घ समयout)
अणु
	काष्ठा devlink_flash_notअगरy params = अणु
		.status_msg = status_msg,
		.component = component,
		.समयout = समयout,
	पूर्ण;

	__devlink_flash_update_notअगरy(devlink,
				      DEVLINK_CMD_FLASH_UPDATE_STATUS,
				      &params);
पूर्ण
EXPORT_SYMBOL_GPL(devlink_flash_update_समयout_notअगरy);

अटल पूर्णांक devlink_nl_cmd_flash_update(काष्ठा sk_buff *skb,
				       काष्ठा genl_info *info)
अणु
	काष्ठा nlattr *nla_component, *nla_overग_लिखो_mask, *nla_file_name;
	काष्ठा devlink_flash_update_params params = अणुपूर्ण;
	काष्ठा devlink *devlink = info->user_ptr[0];
	स्थिर अक्षर *file_name;
	u32 supported_params;
	पूर्णांक ret;

	अगर (!devlink->ops->flash_update)
		वापस -EOPNOTSUPP;

	अगर (!info->attrs[DEVLINK_ATTR_FLASH_UPDATE_खाता_NAME])
		वापस -EINVAL;

	supported_params = devlink->ops->supported_flash_update_params;

	nla_component = info->attrs[DEVLINK_ATTR_FLASH_UPDATE_COMPONENT];
	अगर (nla_component) अणु
		अगर (!(supported_params & DEVLINK_SUPPORT_FLASH_UPDATE_COMPONENT)) अणु
			NL_SET_ERR_MSG_ATTR(info->extack, nla_component,
					    "component update is not supported by this device");
			वापस -EOPNOTSUPP;
		पूर्ण
		params.component = nla_data(nla_component);
	पूर्ण

	nla_overग_लिखो_mask = info->attrs[DEVLINK_ATTR_FLASH_UPDATE_OVERWRITE_MASK];
	अगर (nla_overग_लिखो_mask) अणु
		काष्ठा nla_bitfield32 sections;

		अगर (!(supported_params & DEVLINK_SUPPORT_FLASH_UPDATE_OVERWRITE_MASK)) अणु
			NL_SET_ERR_MSG_ATTR(info->extack, nla_overग_लिखो_mask,
					    "overwrite settings are not supported by this device");
			वापस -EOPNOTSUPP;
		पूर्ण
		sections = nla_get_bitfield32(nla_overग_लिखो_mask);
		params.overग_लिखो_mask = sections.value & sections.selector;
	पूर्ण

	nla_file_name = info->attrs[DEVLINK_ATTR_FLASH_UPDATE_खाता_NAME];
	file_name = nla_data(nla_file_name);
	ret = request_firmware(&params.fw, file_name, devlink->dev);
	अगर (ret) अणु
		NL_SET_ERR_MSG_ATTR(info->extack, nla_file_name, "failed to locate the requested firmware file");
		वापस ret;
	पूर्ण

	devlink_flash_update_begin_notअगरy(devlink);
	ret = devlink->ops->flash_update(devlink, &params, info->extack);
	devlink_flash_update_end_notअगरy(devlink);

	release_firmware(params.fw);

	वापस ret;
पूर्ण

अटल स्थिर काष्ठा devlink_param devlink_param_generic[] = अणु
	अणु
		.id = DEVLINK_PARAM_GENERIC_ID_INT_ERR_RESET,
		.name = DEVLINK_PARAM_GENERIC_INT_ERR_RESET_NAME,
		.type = DEVLINK_PARAM_GENERIC_INT_ERR_RESET_TYPE,
	पूर्ण,
	अणु
		.id = DEVLINK_PARAM_GENERIC_ID_MAX_MACS,
		.name = DEVLINK_PARAM_GENERIC_MAX_MACS_NAME,
		.type = DEVLINK_PARAM_GENERIC_MAX_MACS_TYPE,
	पूर्ण,
	अणु
		.id = DEVLINK_PARAM_GENERIC_ID_ENABLE_SRIOV,
		.name = DEVLINK_PARAM_GENERIC_ENABLE_SRIOV_NAME,
		.type = DEVLINK_PARAM_GENERIC_ENABLE_SRIOV_TYPE,
	पूर्ण,
	अणु
		.id = DEVLINK_PARAM_GENERIC_ID_REGION_SNAPSHOT,
		.name = DEVLINK_PARAM_GENERIC_REGION_SNAPSHOT_NAME,
		.type = DEVLINK_PARAM_GENERIC_REGION_SNAPSHOT_TYPE,
	पूर्ण,
	अणु
		.id = DEVLINK_PARAM_GENERIC_ID_IGNORE_ARI,
		.name = DEVLINK_PARAM_GENERIC_IGNORE_ARI_NAME,
		.type = DEVLINK_PARAM_GENERIC_IGNORE_ARI_TYPE,
	पूर्ण,
	अणु
		.id = DEVLINK_PARAM_GENERIC_ID_MSIX_VEC_PER_PF_MAX,
		.name = DEVLINK_PARAM_GENERIC_MSIX_VEC_PER_PF_MAX_NAME,
		.type = DEVLINK_PARAM_GENERIC_MSIX_VEC_PER_PF_MAX_TYPE,
	पूर्ण,
	अणु
		.id = DEVLINK_PARAM_GENERIC_ID_MSIX_VEC_PER_PF_MIN,
		.name = DEVLINK_PARAM_GENERIC_MSIX_VEC_PER_PF_MIN_NAME,
		.type = DEVLINK_PARAM_GENERIC_MSIX_VEC_PER_PF_MIN_TYPE,
	पूर्ण,
	अणु
		.id = DEVLINK_PARAM_GENERIC_ID_FW_LOAD_POLICY,
		.name = DEVLINK_PARAM_GENERIC_FW_LOAD_POLICY_NAME,
		.type = DEVLINK_PARAM_GENERIC_FW_LOAD_POLICY_TYPE,
	पूर्ण,
	अणु
		.id = DEVLINK_PARAM_GENERIC_ID_RESET_DEV_ON_DRV_PROBE,
		.name = DEVLINK_PARAM_GENERIC_RESET_DEV_ON_DRV_PROBE_NAME,
		.type = DEVLINK_PARAM_GENERIC_RESET_DEV_ON_DRV_PROBE_TYPE,
	पूर्ण,
	अणु
		.id = DEVLINK_PARAM_GENERIC_ID_ENABLE_ROCE,
		.name = DEVLINK_PARAM_GENERIC_ENABLE_ROCE_NAME,
		.type = DEVLINK_PARAM_GENERIC_ENABLE_ROCE_TYPE,
	पूर्ण,
	अणु
		.id = DEVLINK_PARAM_GENERIC_ID_ENABLE_REMOTE_DEV_RESET,
		.name = DEVLINK_PARAM_GENERIC_ENABLE_REMOTE_DEV_RESET_NAME,
		.type = DEVLINK_PARAM_GENERIC_ENABLE_REMOTE_DEV_RESET_TYPE,
	पूर्ण,
पूर्ण;

अटल पूर्णांक devlink_param_generic_verअगरy(स्थिर काष्ठा devlink_param *param)
अणु
	/* verअगरy it match generic parameter by id and name */
	अगर (param->id > DEVLINK_PARAM_GENERIC_ID_MAX)
		वापस -EINVAL;
	अगर (म_भेद(param->name, devlink_param_generic[param->id].name))
		वापस -ENOENT;

	WARN_ON(param->type != devlink_param_generic[param->id].type);

	वापस 0;
पूर्ण

अटल पूर्णांक devlink_param_driver_verअगरy(स्थिर काष्ठा devlink_param *param)
अणु
	पूर्णांक i;

	अगर (param->id <= DEVLINK_PARAM_GENERIC_ID_MAX)
		वापस -EINVAL;
	/* verअगरy no such name in generic params */
	क्रम (i = 0; i <= DEVLINK_PARAM_GENERIC_ID_MAX; i++)
		अगर (!म_भेद(param->name, devlink_param_generic[i].name))
			वापस -EEXIST;

	वापस 0;
पूर्ण

अटल काष्ठा devlink_param_item *
devlink_param_find_by_name(काष्ठा list_head *param_list,
			   स्थिर अक्षर *param_name)
अणु
	काष्ठा devlink_param_item *param_item;

	list_क्रम_each_entry(param_item, param_list, list)
		अगर (!म_भेद(param_item->param->name, param_name))
			वापस param_item;
	वापस शून्य;
पूर्ण

अटल काष्ठा devlink_param_item *
devlink_param_find_by_id(काष्ठा list_head *param_list, u32 param_id)
अणु
	काष्ठा devlink_param_item *param_item;

	list_क्रम_each_entry(param_item, param_list, list)
		अगर (param_item->param->id == param_id)
			वापस param_item;
	वापस शून्य;
पूर्ण

अटल bool
devlink_param_cmode_is_supported(स्थिर काष्ठा devlink_param *param,
				 क्रमागत devlink_param_cmode cmode)
अणु
	वापस test_bit(cmode, &param->supported_cmodes);
पूर्ण

अटल पूर्णांक devlink_param_get(काष्ठा devlink *devlink,
			     स्थिर काष्ठा devlink_param *param,
			     काष्ठा devlink_param_gset_ctx *ctx)
अणु
	अगर (!param->get)
		वापस -EOPNOTSUPP;
	वापस param->get(devlink, param->id, ctx);
पूर्ण

अटल पूर्णांक devlink_param_set(काष्ठा devlink *devlink,
			     स्थिर काष्ठा devlink_param *param,
			     काष्ठा devlink_param_gset_ctx *ctx)
अणु
	अगर (!param->set)
		वापस -EOPNOTSUPP;
	वापस param->set(devlink, param->id, ctx);
पूर्ण

अटल पूर्णांक
devlink_param_type_to_nla_type(क्रमागत devlink_param_type param_type)
अणु
	चयन (param_type) अणु
	हाल DEVLINK_PARAM_TYPE_U8:
		वापस NLA_U8;
	हाल DEVLINK_PARAM_TYPE_U16:
		वापस NLA_U16;
	हाल DEVLINK_PARAM_TYPE_U32:
		वापस NLA_U32;
	हाल DEVLINK_PARAM_TYPE_STRING:
		वापस NLA_STRING;
	हाल DEVLINK_PARAM_TYPE_BOOL:
		वापस NLA_FLAG;
	शेष:
		वापस -EINVAL;
	पूर्ण
पूर्ण

अटल पूर्णांक
devlink_nl_param_value_fill_one(काष्ठा sk_buff *msg,
				क्रमागत devlink_param_type type,
				क्रमागत devlink_param_cmode cmode,
				जोड़ devlink_param_value val)
अणु
	काष्ठा nlattr *param_value_attr;

	param_value_attr = nla_nest_start_noflag(msg,
						 DEVLINK_ATTR_PARAM_VALUE);
	अगर (!param_value_attr)
		जाओ nla_put_failure;

	अगर (nla_put_u8(msg, DEVLINK_ATTR_PARAM_VALUE_CMODE, cmode))
		जाओ value_nest_cancel;

	चयन (type) अणु
	हाल DEVLINK_PARAM_TYPE_U8:
		अगर (nla_put_u8(msg, DEVLINK_ATTR_PARAM_VALUE_DATA, val.vu8))
			जाओ value_nest_cancel;
		अवरोध;
	हाल DEVLINK_PARAM_TYPE_U16:
		अगर (nla_put_u16(msg, DEVLINK_ATTR_PARAM_VALUE_DATA, val.vu16))
			जाओ value_nest_cancel;
		अवरोध;
	हाल DEVLINK_PARAM_TYPE_U32:
		अगर (nla_put_u32(msg, DEVLINK_ATTR_PARAM_VALUE_DATA, val.vu32))
			जाओ value_nest_cancel;
		अवरोध;
	हाल DEVLINK_PARAM_TYPE_STRING:
		अगर (nla_put_string(msg, DEVLINK_ATTR_PARAM_VALUE_DATA,
				   val.vstr))
			जाओ value_nest_cancel;
		अवरोध;
	हाल DEVLINK_PARAM_TYPE_BOOL:
		अगर (val.vbool &&
		    nla_put_flag(msg, DEVLINK_ATTR_PARAM_VALUE_DATA))
			जाओ value_nest_cancel;
		अवरोध;
	पूर्ण

	nla_nest_end(msg, param_value_attr);
	वापस 0;

value_nest_cancel:
	nla_nest_cancel(msg, param_value_attr);
nla_put_failure:
	वापस -EMSGSIZE;
पूर्ण

अटल पूर्णांक devlink_nl_param_fill(काष्ठा sk_buff *msg, काष्ठा devlink *devlink,
				 अचिन्हित पूर्णांक port_index,
				 काष्ठा devlink_param_item *param_item,
				 क्रमागत devlink_command cmd,
				 u32 portid, u32 seq, पूर्णांक flags)
अणु
	जोड़ devlink_param_value param_value[DEVLINK_PARAM_CMODE_MAX + 1];
	bool param_value_set[DEVLINK_PARAM_CMODE_MAX + 1] = अणुपूर्ण;
	स्थिर काष्ठा devlink_param *param = param_item->param;
	काष्ठा devlink_param_gset_ctx ctx;
	काष्ठा nlattr *param_values_list;
	काष्ठा nlattr *param_attr;
	पूर्णांक nla_type;
	व्योम *hdr;
	पूर्णांक err;
	पूर्णांक i;

	/* Get value from driver part to driverinit configuration mode */
	क्रम (i = 0; i <= DEVLINK_PARAM_CMODE_MAX; i++) अणु
		अगर (!devlink_param_cmode_is_supported(param, i))
			जारी;
		अगर (i == DEVLINK_PARAM_CMODE_DRIVERINIT) अणु
			अगर (!param_item->driverinit_value_valid)
				वापस -EOPNOTSUPP;
			param_value[i] = param_item->driverinit_value;
		पूर्ण अन्यथा अणु
			अगर (!param_item->published)
				जारी;
			ctx.cmode = i;
			err = devlink_param_get(devlink, param, &ctx);
			अगर (err)
				वापस err;
			param_value[i] = ctx.val;
		पूर्ण
		param_value_set[i] = true;
	पूर्ण

	hdr = genlmsg_put(msg, portid, seq, &devlink_nl_family, flags, cmd);
	अगर (!hdr)
		वापस -EMSGSIZE;

	अगर (devlink_nl_put_handle(msg, devlink))
		जाओ genlmsg_cancel;

	अगर (cmd == DEVLINK_CMD_PORT_PARAM_GET ||
	    cmd == DEVLINK_CMD_PORT_PARAM_NEW ||
	    cmd == DEVLINK_CMD_PORT_PARAM_DEL)
		अगर (nla_put_u32(msg, DEVLINK_ATTR_PORT_INDEX, port_index))
			जाओ genlmsg_cancel;

	param_attr = nla_nest_start_noflag(msg, DEVLINK_ATTR_PARAM);
	अगर (!param_attr)
		जाओ genlmsg_cancel;
	अगर (nla_put_string(msg, DEVLINK_ATTR_PARAM_NAME, param->name))
		जाओ param_nest_cancel;
	अगर (param->generic && nla_put_flag(msg, DEVLINK_ATTR_PARAM_GENERIC))
		जाओ param_nest_cancel;

	nla_type = devlink_param_type_to_nla_type(param->type);
	अगर (nla_type < 0)
		जाओ param_nest_cancel;
	अगर (nla_put_u8(msg, DEVLINK_ATTR_PARAM_TYPE, nla_type))
		जाओ param_nest_cancel;

	param_values_list = nla_nest_start_noflag(msg,
						  DEVLINK_ATTR_PARAM_VALUES_LIST);
	अगर (!param_values_list)
		जाओ param_nest_cancel;

	क्रम (i = 0; i <= DEVLINK_PARAM_CMODE_MAX; i++) अणु
		अगर (!param_value_set[i])
			जारी;
		err = devlink_nl_param_value_fill_one(msg, param->type,
						      i, param_value[i]);
		अगर (err)
			जाओ values_list_nest_cancel;
	पूर्ण

	nla_nest_end(msg, param_values_list);
	nla_nest_end(msg, param_attr);
	genlmsg_end(msg, hdr);
	वापस 0;

values_list_nest_cancel:
	nla_nest_end(msg, param_values_list);
param_nest_cancel:
	nla_nest_cancel(msg, param_attr);
genlmsg_cancel:
	genlmsg_cancel(msg, hdr);
	वापस -EMSGSIZE;
पूर्ण

अटल व्योम devlink_param_notअगरy(काष्ठा devlink *devlink,
				 अचिन्हित पूर्णांक port_index,
				 काष्ठा devlink_param_item *param_item,
				 क्रमागत devlink_command cmd)
अणु
	काष्ठा sk_buff *msg;
	पूर्णांक err;

	WARN_ON(cmd != DEVLINK_CMD_PARAM_NEW && cmd != DEVLINK_CMD_PARAM_DEL &&
		cmd != DEVLINK_CMD_PORT_PARAM_NEW &&
		cmd != DEVLINK_CMD_PORT_PARAM_DEL);

	msg = nlmsg_new(NLMSG_DEFAULT_SIZE, GFP_KERNEL);
	अगर (!msg)
		वापस;
	err = devlink_nl_param_fill(msg, devlink, port_index, param_item, cmd,
				    0, 0, 0);
	अगर (err) अणु
		nlmsg_मुक्त(msg);
		वापस;
	पूर्ण

	genlmsg_multicast_netns(&devlink_nl_family, devlink_net(devlink),
				msg, 0, DEVLINK_MCGRP_CONFIG, GFP_KERNEL);
पूर्ण

अटल पूर्णांक devlink_nl_cmd_param_get_dumpit(काष्ठा sk_buff *msg,
					   काष्ठा netlink_callback *cb)
अणु
	काष्ठा devlink_param_item *param_item;
	काष्ठा devlink *devlink;
	पूर्णांक start = cb->args[0];
	पूर्णांक idx = 0;
	पूर्णांक err = 0;

	mutex_lock(&devlink_mutex);
	list_क्रम_each_entry(devlink, &devlink_list, list) अणु
		अगर (!net_eq(devlink_net(devlink), sock_net(msg->sk)))
			जारी;
		mutex_lock(&devlink->lock);
		list_क्रम_each_entry(param_item, &devlink->param_list, list) अणु
			अगर (idx < start) अणु
				idx++;
				जारी;
			पूर्ण
			err = devlink_nl_param_fill(msg, devlink, 0, param_item,
						    DEVLINK_CMD_PARAM_GET,
						    NETLINK_CB(cb->skb).portid,
						    cb->nlh->nlmsg_seq,
						    NLM_F_MULTI);
			अगर (err == -EOPNOTSUPP) अणु
				err = 0;
			पूर्ण अन्यथा अगर (err) अणु
				mutex_unlock(&devlink->lock);
				जाओ out;
			पूर्ण
			idx++;
		पूर्ण
		mutex_unlock(&devlink->lock);
	पूर्ण
out:
	mutex_unlock(&devlink_mutex);

	अगर (err != -EMSGSIZE)
		वापस err;

	cb->args[0] = idx;
	वापस msg->len;
पूर्ण

अटल पूर्णांक
devlink_param_type_get_from_info(काष्ठा genl_info *info,
				 क्रमागत devlink_param_type *param_type)
अणु
	अगर (!info->attrs[DEVLINK_ATTR_PARAM_TYPE])
		वापस -EINVAL;

	चयन (nla_get_u8(info->attrs[DEVLINK_ATTR_PARAM_TYPE])) अणु
	हाल NLA_U8:
		*param_type = DEVLINK_PARAM_TYPE_U8;
		अवरोध;
	हाल NLA_U16:
		*param_type = DEVLINK_PARAM_TYPE_U16;
		अवरोध;
	हाल NLA_U32:
		*param_type = DEVLINK_PARAM_TYPE_U32;
		अवरोध;
	हाल NLA_STRING:
		*param_type = DEVLINK_PARAM_TYPE_STRING;
		अवरोध;
	हाल NLA_FLAG:
		*param_type = DEVLINK_PARAM_TYPE_BOOL;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक
devlink_param_value_get_from_info(स्थिर काष्ठा devlink_param *param,
				  काष्ठा genl_info *info,
				  जोड़ devlink_param_value *value)
अणु
	काष्ठा nlattr *param_data;
	पूर्णांक len;

	param_data = info->attrs[DEVLINK_ATTR_PARAM_VALUE_DATA];

	अगर (param->type != DEVLINK_PARAM_TYPE_BOOL && !param_data)
		वापस -EINVAL;

	चयन (param->type) अणु
	हाल DEVLINK_PARAM_TYPE_U8:
		अगर (nla_len(param_data) != माप(u8))
			वापस -EINVAL;
		value->vu8 = nla_get_u8(param_data);
		अवरोध;
	हाल DEVLINK_PARAM_TYPE_U16:
		अगर (nla_len(param_data) != माप(u16))
			वापस -EINVAL;
		value->vu16 = nla_get_u16(param_data);
		अवरोध;
	हाल DEVLINK_PARAM_TYPE_U32:
		अगर (nla_len(param_data) != माप(u32))
			वापस -EINVAL;
		value->vu32 = nla_get_u32(param_data);
		अवरोध;
	हाल DEVLINK_PARAM_TYPE_STRING:
		len = strnlen(nla_data(param_data), nla_len(param_data));
		अगर (len == nla_len(param_data) ||
		    len >= __DEVLINK_PARAM_MAX_STRING_VALUE)
			वापस -EINVAL;
		म_नकल(value->vstr, nla_data(param_data));
		अवरोध;
	हाल DEVLINK_PARAM_TYPE_BOOL:
		अगर (param_data && nla_len(param_data))
			वापस -EINVAL;
		value->vbool = nla_get_flag(param_data);
		अवरोध;
	पूर्ण
	वापस 0;
पूर्ण

अटल काष्ठा devlink_param_item *
devlink_param_get_from_info(काष्ठा list_head *param_list,
			    काष्ठा genl_info *info)
अणु
	अक्षर *param_name;

	अगर (!info->attrs[DEVLINK_ATTR_PARAM_NAME])
		वापस शून्य;

	param_name = nla_data(info->attrs[DEVLINK_ATTR_PARAM_NAME]);
	वापस devlink_param_find_by_name(param_list, param_name);
पूर्ण

अटल पूर्णांक devlink_nl_cmd_param_get_करोit(काष्ठा sk_buff *skb,
					 काष्ठा genl_info *info)
अणु
	काष्ठा devlink *devlink = info->user_ptr[0];
	काष्ठा devlink_param_item *param_item;
	काष्ठा sk_buff *msg;
	पूर्णांक err;

	param_item = devlink_param_get_from_info(&devlink->param_list, info);
	अगर (!param_item)
		वापस -EINVAL;

	msg = nlmsg_new(NLMSG_DEFAULT_SIZE, GFP_KERNEL);
	अगर (!msg)
		वापस -ENOMEM;

	err = devlink_nl_param_fill(msg, devlink, 0, param_item,
				    DEVLINK_CMD_PARAM_GET,
				    info->snd_portid, info->snd_seq, 0);
	अगर (err) अणु
		nlmsg_मुक्त(msg);
		वापस err;
	पूर्ण

	वापस genlmsg_reply(msg, info);
पूर्ण

अटल पूर्णांक __devlink_nl_cmd_param_set_करोit(काष्ठा devlink *devlink,
					   अचिन्हित पूर्णांक port_index,
					   काष्ठा list_head *param_list,
					   काष्ठा genl_info *info,
					   क्रमागत devlink_command cmd)
अणु
	क्रमागत devlink_param_type param_type;
	काष्ठा devlink_param_gset_ctx ctx;
	क्रमागत devlink_param_cmode cmode;
	काष्ठा devlink_param_item *param_item;
	स्थिर काष्ठा devlink_param *param;
	जोड़ devlink_param_value value;
	पूर्णांक err = 0;

	param_item = devlink_param_get_from_info(param_list, info);
	अगर (!param_item)
		वापस -EINVAL;
	param = param_item->param;
	err = devlink_param_type_get_from_info(info, &param_type);
	अगर (err)
		वापस err;
	अगर (param_type != param->type)
		वापस -EINVAL;
	err = devlink_param_value_get_from_info(param, info, &value);
	अगर (err)
		वापस err;
	अगर (param->validate) अणु
		err = param->validate(devlink, param->id, value, info->extack);
		अगर (err)
			वापस err;
	पूर्ण

	अगर (!info->attrs[DEVLINK_ATTR_PARAM_VALUE_CMODE])
		वापस -EINVAL;
	cmode = nla_get_u8(info->attrs[DEVLINK_ATTR_PARAM_VALUE_CMODE]);
	अगर (!devlink_param_cmode_is_supported(param, cmode))
		वापस -EOPNOTSUPP;

	अगर (cmode == DEVLINK_PARAM_CMODE_DRIVERINIT) अणु
		अगर (param->type == DEVLINK_PARAM_TYPE_STRING)
			म_नकल(param_item->driverinit_value.vstr, value.vstr);
		अन्यथा
			param_item->driverinit_value = value;
		param_item->driverinit_value_valid = true;
	पूर्ण अन्यथा अणु
		अगर (!param->set)
			वापस -EOPNOTSUPP;
		ctx.val = value;
		ctx.cmode = cmode;
		err = devlink_param_set(devlink, param, &ctx);
		अगर (err)
			वापस err;
	पूर्ण

	devlink_param_notअगरy(devlink, port_index, param_item, cmd);
	वापस 0;
पूर्ण

अटल पूर्णांक devlink_nl_cmd_param_set_करोit(काष्ठा sk_buff *skb,
					 काष्ठा genl_info *info)
अणु
	काष्ठा devlink *devlink = info->user_ptr[0];

	वापस __devlink_nl_cmd_param_set_करोit(devlink, 0, &devlink->param_list,
					       info, DEVLINK_CMD_PARAM_NEW);
पूर्ण

अटल पूर्णांक devlink_param_रेजिस्टर_one(काष्ठा devlink *devlink,
				      अचिन्हित पूर्णांक port_index,
				      काष्ठा list_head *param_list,
				      स्थिर काष्ठा devlink_param *param,
				      क्रमागत devlink_command cmd)
अणु
	काष्ठा devlink_param_item *param_item;

	अगर (devlink_param_find_by_name(param_list, param->name))
		वापस -EEXIST;

	अगर (param->supported_cmodes == BIT(DEVLINK_PARAM_CMODE_DRIVERINIT))
		WARN_ON(param->get || param->set);
	अन्यथा
		WARN_ON(!param->get || !param->set);

	param_item = kzalloc(माप(*param_item), GFP_KERNEL);
	अगर (!param_item)
		वापस -ENOMEM;
	param_item->param = param;

	list_add_tail(&param_item->list, param_list);
	devlink_param_notअगरy(devlink, port_index, param_item, cmd);
	वापस 0;
पूर्ण

अटल व्योम devlink_param_unरेजिस्टर_one(काष्ठा devlink *devlink,
					 अचिन्हित पूर्णांक port_index,
					 काष्ठा list_head *param_list,
					 स्थिर काष्ठा devlink_param *param,
					 क्रमागत devlink_command cmd)
अणु
	काष्ठा devlink_param_item *param_item;

	param_item = devlink_param_find_by_name(param_list, param->name);
	WARN_ON(!param_item);
	devlink_param_notअगरy(devlink, port_index, param_item, cmd);
	list_del(&param_item->list);
	kमुक्त(param_item);
पूर्ण

अटल पूर्णांक devlink_nl_cmd_port_param_get_dumpit(काष्ठा sk_buff *msg,
						काष्ठा netlink_callback *cb)
अणु
	काष्ठा devlink_param_item *param_item;
	काष्ठा devlink_port *devlink_port;
	काष्ठा devlink *devlink;
	पूर्णांक start = cb->args[0];
	पूर्णांक idx = 0;
	पूर्णांक err = 0;

	mutex_lock(&devlink_mutex);
	list_क्रम_each_entry(devlink, &devlink_list, list) अणु
		अगर (!net_eq(devlink_net(devlink), sock_net(msg->sk)))
			जारी;
		mutex_lock(&devlink->lock);
		list_क्रम_each_entry(devlink_port, &devlink->port_list, list) अणु
			list_क्रम_each_entry(param_item,
					    &devlink_port->param_list, list) अणु
				अगर (idx < start) अणु
					idx++;
					जारी;
				पूर्ण
				err = devlink_nl_param_fill(msg,
						devlink_port->devlink,
						devlink_port->index, param_item,
						DEVLINK_CMD_PORT_PARAM_GET,
						NETLINK_CB(cb->skb).portid,
						cb->nlh->nlmsg_seq,
						NLM_F_MULTI);
				अगर (err == -EOPNOTSUPP) अणु
					err = 0;
				पूर्ण अन्यथा अगर (err) अणु
					mutex_unlock(&devlink->lock);
					जाओ out;
				पूर्ण
				idx++;
			पूर्ण
		पूर्ण
		mutex_unlock(&devlink->lock);
	पूर्ण
out:
	mutex_unlock(&devlink_mutex);

	अगर (err != -EMSGSIZE)
		वापस err;

	cb->args[0] = idx;
	वापस msg->len;
पूर्ण

अटल पूर्णांक devlink_nl_cmd_port_param_get_करोit(काष्ठा sk_buff *skb,
					      काष्ठा genl_info *info)
अणु
	काष्ठा devlink_port *devlink_port = info->user_ptr[1];
	काष्ठा devlink_param_item *param_item;
	काष्ठा sk_buff *msg;
	पूर्णांक err;

	param_item = devlink_param_get_from_info(&devlink_port->param_list,
						 info);
	अगर (!param_item)
		वापस -EINVAL;

	msg = nlmsg_new(NLMSG_DEFAULT_SIZE, GFP_KERNEL);
	अगर (!msg)
		वापस -ENOMEM;

	err = devlink_nl_param_fill(msg, devlink_port->devlink,
				    devlink_port->index, param_item,
				    DEVLINK_CMD_PORT_PARAM_GET,
				    info->snd_portid, info->snd_seq, 0);
	अगर (err) अणु
		nlmsg_मुक्त(msg);
		वापस err;
	पूर्ण

	वापस genlmsg_reply(msg, info);
पूर्ण

अटल पूर्णांक devlink_nl_cmd_port_param_set_करोit(काष्ठा sk_buff *skb,
					      काष्ठा genl_info *info)
अणु
	काष्ठा devlink_port *devlink_port = info->user_ptr[1];

	वापस __devlink_nl_cmd_param_set_करोit(devlink_port->devlink,
					       devlink_port->index,
					       &devlink_port->param_list, info,
					       DEVLINK_CMD_PORT_PARAM_NEW);
पूर्ण

अटल पूर्णांक devlink_nl_region_snapshot_id_put(काष्ठा sk_buff *msg,
					     काष्ठा devlink *devlink,
					     काष्ठा devlink_snapshot *snapshot)
अणु
	काष्ठा nlattr *snap_attr;
	पूर्णांक err;

	snap_attr = nla_nest_start_noflag(msg, DEVLINK_ATTR_REGION_SNAPSHOT);
	अगर (!snap_attr)
		वापस -EINVAL;

	err = nla_put_u32(msg, DEVLINK_ATTR_REGION_SNAPSHOT_ID, snapshot->id);
	अगर (err)
		जाओ nla_put_failure;

	nla_nest_end(msg, snap_attr);
	वापस 0;

nla_put_failure:
	nla_nest_cancel(msg, snap_attr);
	वापस err;
पूर्ण

अटल पूर्णांक devlink_nl_region_snapshots_id_put(काष्ठा sk_buff *msg,
					      काष्ठा devlink *devlink,
					      काष्ठा devlink_region *region)
अणु
	काष्ठा devlink_snapshot *snapshot;
	काष्ठा nlattr *snapshots_attr;
	पूर्णांक err;

	snapshots_attr = nla_nest_start_noflag(msg,
					       DEVLINK_ATTR_REGION_SNAPSHOTS);
	अगर (!snapshots_attr)
		वापस -EINVAL;

	list_क्रम_each_entry(snapshot, &region->snapshot_list, list) अणु
		err = devlink_nl_region_snapshot_id_put(msg, devlink, snapshot);
		अगर (err)
			जाओ nla_put_failure;
	पूर्ण

	nla_nest_end(msg, snapshots_attr);
	वापस 0;

nla_put_failure:
	nla_nest_cancel(msg, snapshots_attr);
	वापस err;
पूर्ण

अटल पूर्णांक devlink_nl_region_fill(काष्ठा sk_buff *msg, काष्ठा devlink *devlink,
				  क्रमागत devlink_command cmd, u32 portid,
				  u32 seq, पूर्णांक flags,
				  काष्ठा devlink_region *region)
अणु
	व्योम *hdr;
	पूर्णांक err;

	hdr = genlmsg_put(msg, portid, seq, &devlink_nl_family, flags, cmd);
	अगर (!hdr)
		वापस -EMSGSIZE;

	err = devlink_nl_put_handle(msg, devlink);
	अगर (err)
		जाओ nla_put_failure;

	अगर (region->port) अणु
		err = nla_put_u32(msg, DEVLINK_ATTR_PORT_INDEX,
				  region->port->index);
		अगर (err)
			जाओ nla_put_failure;
	पूर्ण

	err = nla_put_string(msg, DEVLINK_ATTR_REGION_NAME, region->ops->name);
	अगर (err)
		जाओ nla_put_failure;

	err = nla_put_u64_64bit(msg, DEVLINK_ATTR_REGION_SIZE,
				region->size,
				DEVLINK_ATTR_PAD);
	अगर (err)
		जाओ nla_put_failure;

	err = devlink_nl_region_snapshots_id_put(msg, devlink, region);
	अगर (err)
		जाओ nla_put_failure;

	genlmsg_end(msg, hdr);
	वापस 0;

nla_put_failure:
	genlmsg_cancel(msg, hdr);
	वापस err;
पूर्ण

अटल काष्ठा sk_buff *
devlink_nl_region_notअगरy_build(काष्ठा devlink_region *region,
			       काष्ठा devlink_snapshot *snapshot,
			       क्रमागत devlink_command cmd, u32 portid, u32 seq)
अणु
	काष्ठा devlink *devlink = region->devlink;
	काष्ठा sk_buff *msg;
	व्योम *hdr;
	पूर्णांक err;


	msg = nlmsg_new(NLMSG_DEFAULT_SIZE, GFP_KERNEL);
	अगर (!msg)
		वापस ERR_PTR(-ENOMEM);

	hdr = genlmsg_put(msg, portid, seq, &devlink_nl_family, 0, cmd);
	अगर (!hdr) अणु
		err = -EMSGSIZE;
		जाओ out_मुक्त_msg;
	पूर्ण

	err = devlink_nl_put_handle(msg, devlink);
	अगर (err)
		जाओ out_cancel_msg;

	अगर (region->port) अणु
		err = nla_put_u32(msg, DEVLINK_ATTR_PORT_INDEX,
				  region->port->index);
		अगर (err)
			जाओ out_cancel_msg;
	पूर्ण

	err = nla_put_string(msg, DEVLINK_ATTR_REGION_NAME,
			     region->ops->name);
	अगर (err)
		जाओ out_cancel_msg;

	अगर (snapshot) अणु
		err = nla_put_u32(msg, DEVLINK_ATTR_REGION_SNAPSHOT_ID,
				  snapshot->id);
		अगर (err)
			जाओ out_cancel_msg;
	पूर्ण अन्यथा अणु
		err = nla_put_u64_64bit(msg, DEVLINK_ATTR_REGION_SIZE,
					region->size, DEVLINK_ATTR_PAD);
		अगर (err)
			जाओ out_cancel_msg;
	पूर्ण
	genlmsg_end(msg, hdr);

	वापस msg;

out_cancel_msg:
	genlmsg_cancel(msg, hdr);
out_मुक्त_msg:
	nlmsg_मुक्त(msg);
	वापस ERR_PTR(err);
पूर्ण

अटल व्योम devlink_nl_region_notअगरy(काष्ठा devlink_region *region,
				     काष्ठा devlink_snapshot *snapshot,
				     क्रमागत devlink_command cmd)
अणु
	काष्ठा devlink *devlink = region->devlink;
	काष्ठा sk_buff *msg;

	WARN_ON(cmd != DEVLINK_CMD_REGION_NEW && cmd != DEVLINK_CMD_REGION_DEL);

	msg = devlink_nl_region_notअगरy_build(region, snapshot, cmd, 0, 0);
	अगर (IS_ERR(msg))
		वापस;

	genlmsg_multicast_netns(&devlink_nl_family, devlink_net(devlink),
				msg, 0, DEVLINK_MCGRP_CONFIG, GFP_KERNEL);
पूर्ण

/**
 * __devlink_snapshot_id_increment - Increment number of snapshots using an id
 *	@devlink: devlink instance
 *	@id: the snapshot id
 *
 *	Track when a new snapshot begins using an id. Load the count क्रम the
 *	given id from the snapshot xarray, increment it, and store it back.
 *
 *	Called when a new snapshot is created with the given id.
 *
 *	The id *must* have been previously allocated by
 *	devlink_region_snapshot_id_get().
 *
 *	Returns 0 on success, or an error on failure.
 */
अटल पूर्णांक __devlink_snapshot_id_increment(काष्ठा devlink *devlink, u32 id)
अणु
	अचिन्हित दीर्घ count;
	व्योम *p;

	lockdep_निश्चित_held(&devlink->lock);

	p = xa_load(&devlink->snapshot_ids, id);
	अगर (WARN_ON(!p))
		वापस -EINVAL;

	अगर (WARN_ON(!xa_is_value(p)))
		वापस -EINVAL;

	count = xa_to_value(p);
	count++;

	वापस xa_err(xa_store(&devlink->snapshot_ids, id, xa_mk_value(count),
			       GFP_KERNEL));
पूर्ण

/**
 * __devlink_snapshot_id_decrement - Decrease number of snapshots using an id
 *	@devlink: devlink instance
 *	@id: the snapshot id
 *
 *	Track when a snapshot is deleted and stops using an id. Load the count
 *	क्रम the given id from the snapshot xarray, decrement it, and store it
 *	back.
 *
 *	If the count reaches zero, erase this id from the xarray, मुक्तing it
 *	up क्रम future re-use by devlink_region_snapshot_id_get().
 *
 *	Called when a snapshot using the given id is deleted, and when the
 *	initial allocator of the id is finished using it.
 */
अटल व्योम __devlink_snapshot_id_decrement(काष्ठा devlink *devlink, u32 id)
अणु
	अचिन्हित दीर्घ count;
	व्योम *p;

	lockdep_निश्चित_held(&devlink->lock);

	p = xa_load(&devlink->snapshot_ids, id);
	अगर (WARN_ON(!p))
		वापस;

	अगर (WARN_ON(!xa_is_value(p)))
		वापस;

	count = xa_to_value(p);

	अगर (count > 1) अणु
		count--;
		xa_store(&devlink->snapshot_ids, id, xa_mk_value(count),
			 GFP_KERNEL);
	पूर्ण अन्यथा अणु
		/* If this was the last user, we can erase this id */
		xa_erase(&devlink->snapshot_ids, id);
	पूर्ण
पूर्ण

/**
 *	__devlink_snapshot_id_insert - Insert a specअगरic snapshot ID
 *	@devlink: devlink instance
 *	@id: the snapshot id
 *
 *	Mark the given snapshot id as used by inserting a zero value पूर्णांकo the
 *	snapshot xarray.
 *
 *	This must be called जबतक holding the devlink instance lock. Unlike
 *	devlink_snapshot_id_get, the initial reference count is zero, not one.
 *	It is expected that the id will immediately be used beक्रमe
 *	releasing the devlink instance lock.
 *
 *	Returns zero on success, or an error code अगर the snapshot id could not
 *	be inserted.
 */
अटल पूर्णांक __devlink_snapshot_id_insert(काष्ठा devlink *devlink, u32 id)
अणु
	lockdep_निश्चित_held(&devlink->lock);

	अगर (xa_load(&devlink->snapshot_ids, id))
		वापस -EEXIST;

	वापस xa_err(xa_store(&devlink->snapshot_ids, id, xa_mk_value(0),
			       GFP_KERNEL));
पूर्ण

/**
 *	__devlink_region_snapshot_id_get - get snapshot ID
 *	@devlink: devlink instance
 *	@id: storage to वापस snapshot id
 *
 *	Allocates a new snapshot id. Returns zero on success, or a negative
 *	error on failure. Must be called जबतक holding the devlink instance
 *	lock.
 *
 *	Snapshot IDs are tracked using an xarray which stores the number of
 *	users of the snapshot id.
 *
 *	Note that the caller of this function counts as a 'user', in order to
 *	aव्योम race conditions. The caller must release its hold on the
 *	snapshot by using devlink_region_snapshot_id_put.
 */
अटल पूर्णांक __devlink_region_snapshot_id_get(काष्ठा devlink *devlink, u32 *id)
अणु
	lockdep_निश्चित_held(&devlink->lock);

	वापस xa_alloc(&devlink->snapshot_ids, id, xa_mk_value(1),
			xa_limit_32b, GFP_KERNEL);
पूर्ण

/**
 *	__devlink_region_snapshot_create - create a new snapshot
 *	This will add a new snapshot of a region. The snapshot
 *	will be stored on the region काष्ठा and can be accessed
 *	from devlink. This is useful क्रम future analyses of snapshots.
 *	Multiple snapshots can be created on a region.
 *	The @snapshot_id should be obtained using the getter function.
 *
 *	Must be called only जबतक holding the devlink instance lock.
 *
 *	@region: devlink region of the snapshot
 *	@data: snapshot data
 *	@snapshot_id: snapshot id to be created
 */
अटल पूर्णांक
__devlink_region_snapshot_create(काष्ठा devlink_region *region,
				 u8 *data, u32 snapshot_id)
अणु
	काष्ठा devlink *devlink = region->devlink;
	काष्ठा devlink_snapshot *snapshot;
	पूर्णांक err;

	lockdep_निश्चित_held(&devlink->lock);

	/* check अगर region can hold one more snapshot */
	अगर (region->cur_snapshots == region->max_snapshots)
		वापस -ENOSPC;

	अगर (devlink_region_snapshot_get_by_id(region, snapshot_id))
		वापस -EEXIST;

	snapshot = kzalloc(माप(*snapshot), GFP_KERNEL);
	अगर (!snapshot)
		वापस -ENOMEM;

	err = __devlink_snapshot_id_increment(devlink, snapshot_id);
	अगर (err)
		जाओ err_snapshot_id_increment;

	snapshot->id = snapshot_id;
	snapshot->region = region;
	snapshot->data = data;

	list_add_tail(&snapshot->list, &region->snapshot_list);

	region->cur_snapshots++;

	devlink_nl_region_notअगरy(region, snapshot, DEVLINK_CMD_REGION_NEW);
	वापस 0;

err_snapshot_id_increment:
	kमुक्त(snapshot);
	वापस err;
पूर्ण

अटल व्योम devlink_region_snapshot_del(काष्ठा devlink_region *region,
					काष्ठा devlink_snapshot *snapshot)
अणु
	काष्ठा devlink *devlink = region->devlink;

	lockdep_निश्चित_held(&devlink->lock);

	devlink_nl_region_notअगरy(region, snapshot, DEVLINK_CMD_REGION_DEL);
	region->cur_snapshots--;
	list_del(&snapshot->list);
	region->ops->deकाष्ठाor(snapshot->data);
	__devlink_snapshot_id_decrement(devlink, snapshot->id);
	kमुक्त(snapshot);
पूर्ण

अटल पूर्णांक devlink_nl_cmd_region_get_करोit(काष्ठा sk_buff *skb,
					  काष्ठा genl_info *info)
अणु
	काष्ठा devlink *devlink = info->user_ptr[0];
	काष्ठा devlink_port *port = शून्य;
	काष्ठा devlink_region *region;
	स्थिर अक्षर *region_name;
	काष्ठा sk_buff *msg;
	अचिन्हित पूर्णांक index;
	पूर्णांक err;

	अगर (!info->attrs[DEVLINK_ATTR_REGION_NAME])
		वापस -EINVAL;

	अगर (info->attrs[DEVLINK_ATTR_PORT_INDEX]) अणु
		index = nla_get_u32(info->attrs[DEVLINK_ATTR_PORT_INDEX]);

		port = devlink_port_get_by_index(devlink, index);
		अगर (!port)
			वापस -ENODEV;
	पूर्ण

	region_name = nla_data(info->attrs[DEVLINK_ATTR_REGION_NAME]);
	अगर (port)
		region = devlink_port_region_get_by_name(port, region_name);
	अन्यथा
		region = devlink_region_get_by_name(devlink, region_name);

	अगर (!region)
		वापस -EINVAL;

	msg = nlmsg_new(NLMSG_DEFAULT_SIZE, GFP_KERNEL);
	अगर (!msg)
		वापस -ENOMEM;

	err = devlink_nl_region_fill(msg, devlink, DEVLINK_CMD_REGION_GET,
				     info->snd_portid, info->snd_seq, 0,
				     region);
	अगर (err) अणु
		nlmsg_मुक्त(msg);
		वापस err;
	पूर्ण

	वापस genlmsg_reply(msg, info);
पूर्ण

अटल पूर्णांक devlink_nl_cmd_region_get_port_dumpit(काष्ठा sk_buff *msg,
						 काष्ठा netlink_callback *cb,
						 काष्ठा devlink_port *port,
						 पूर्णांक *idx,
						 पूर्णांक start)
अणु
	काष्ठा devlink_region *region;
	पूर्णांक err = 0;

	list_क्रम_each_entry(region, &port->region_list, list) अणु
		अगर (*idx < start) अणु
			(*idx)++;
			जारी;
		पूर्ण
		err = devlink_nl_region_fill(msg, port->devlink,
					     DEVLINK_CMD_REGION_GET,
					     NETLINK_CB(cb->skb).portid,
					     cb->nlh->nlmsg_seq,
					     NLM_F_MULTI, region);
		अगर (err)
			जाओ out;
		(*idx)++;
	पूर्ण

out:
	वापस err;
पूर्ण

अटल पूर्णांक devlink_nl_cmd_region_get_devlink_dumpit(काष्ठा sk_buff *msg,
						    काष्ठा netlink_callback *cb,
						    काष्ठा devlink *devlink,
						    पूर्णांक *idx,
						    पूर्णांक start)
अणु
	काष्ठा devlink_region *region;
	काष्ठा devlink_port *port;
	पूर्णांक err = 0;

	mutex_lock(&devlink->lock);
	list_क्रम_each_entry(region, &devlink->region_list, list) अणु
		अगर (*idx < start) अणु
			(*idx)++;
			जारी;
		पूर्ण
		err = devlink_nl_region_fill(msg, devlink,
					     DEVLINK_CMD_REGION_GET,
					     NETLINK_CB(cb->skb).portid,
					     cb->nlh->nlmsg_seq,
					     NLM_F_MULTI, region);
		अगर (err)
			जाओ out;
		(*idx)++;
	पूर्ण

	list_क्रम_each_entry(port, &devlink->port_list, list) अणु
		err = devlink_nl_cmd_region_get_port_dumpit(msg, cb, port, idx,
							    start);
		अगर (err)
			जाओ out;
	पूर्ण

out:
	mutex_unlock(&devlink->lock);
	वापस err;
पूर्ण

अटल पूर्णांक devlink_nl_cmd_region_get_dumpit(काष्ठा sk_buff *msg,
					    काष्ठा netlink_callback *cb)
अणु
	काष्ठा devlink *devlink;
	पूर्णांक start = cb->args[0];
	पूर्णांक idx = 0;
	पूर्णांक err;

	mutex_lock(&devlink_mutex);
	list_क्रम_each_entry(devlink, &devlink_list, list) अणु
		अगर (!net_eq(devlink_net(devlink), sock_net(msg->sk)))
			जारी;
		err = devlink_nl_cmd_region_get_devlink_dumpit(msg, cb, devlink,
							       &idx, start);
		अगर (err)
			जाओ out;
	पूर्ण
out:
	mutex_unlock(&devlink_mutex);
	cb->args[0] = idx;
	वापस msg->len;
पूर्ण

अटल पूर्णांक devlink_nl_cmd_region_del(काष्ठा sk_buff *skb,
				     काष्ठा genl_info *info)
अणु
	काष्ठा devlink *devlink = info->user_ptr[0];
	काष्ठा devlink_snapshot *snapshot;
	काष्ठा devlink_port *port = शून्य;
	काष्ठा devlink_region *region;
	स्थिर अक्षर *region_name;
	अचिन्हित पूर्णांक index;
	u32 snapshot_id;

	अगर (!info->attrs[DEVLINK_ATTR_REGION_NAME] ||
	    !info->attrs[DEVLINK_ATTR_REGION_SNAPSHOT_ID])
		वापस -EINVAL;

	region_name = nla_data(info->attrs[DEVLINK_ATTR_REGION_NAME]);
	snapshot_id = nla_get_u32(info->attrs[DEVLINK_ATTR_REGION_SNAPSHOT_ID]);

	अगर (info->attrs[DEVLINK_ATTR_PORT_INDEX]) अणु
		index = nla_get_u32(info->attrs[DEVLINK_ATTR_PORT_INDEX]);

		port = devlink_port_get_by_index(devlink, index);
		अगर (!port)
			वापस -ENODEV;
	पूर्ण

	अगर (port)
		region = devlink_port_region_get_by_name(port, region_name);
	अन्यथा
		region = devlink_region_get_by_name(devlink, region_name);

	अगर (!region)
		वापस -EINVAL;

	snapshot = devlink_region_snapshot_get_by_id(region, snapshot_id);
	अगर (!snapshot)
		वापस -EINVAL;

	devlink_region_snapshot_del(region, snapshot);
	वापस 0;
पूर्ण

अटल पूर्णांक
devlink_nl_cmd_region_new(काष्ठा sk_buff *skb, काष्ठा genl_info *info)
अणु
	काष्ठा devlink *devlink = info->user_ptr[0];
	काष्ठा devlink_snapshot *snapshot;
	काष्ठा devlink_port *port = शून्य;
	काष्ठा nlattr *snapshot_id_attr;
	काष्ठा devlink_region *region;
	स्थिर अक्षर *region_name;
	अचिन्हित पूर्णांक index;
	u32 snapshot_id;
	u8 *data;
	पूर्णांक err;

	अगर (!info->attrs[DEVLINK_ATTR_REGION_NAME]) अणु
		NL_SET_ERR_MSG_MOD(info->extack, "No region name provided");
		वापस -EINVAL;
	पूर्ण

	region_name = nla_data(info->attrs[DEVLINK_ATTR_REGION_NAME]);

	अगर (info->attrs[DEVLINK_ATTR_PORT_INDEX]) अणु
		index = nla_get_u32(info->attrs[DEVLINK_ATTR_PORT_INDEX]);

		port = devlink_port_get_by_index(devlink, index);
		अगर (!port)
			वापस -ENODEV;
	पूर्ण

	अगर (port)
		region = devlink_port_region_get_by_name(port, region_name);
	अन्यथा
		region = devlink_region_get_by_name(devlink, region_name);

	अगर (!region) अणु
		NL_SET_ERR_MSG_MOD(info->extack, "The requested region does not exist");
		वापस -EINVAL;
	पूर्ण

	अगर (!region->ops->snapshot) अणु
		NL_SET_ERR_MSG_MOD(info->extack, "The requested region does not support taking an immediate snapshot");
		वापस -EOPNOTSUPP;
	पूर्ण

	अगर (region->cur_snapshots == region->max_snapshots) अणु
		NL_SET_ERR_MSG_MOD(info->extack, "The region has reached the maximum number of stored snapshots");
		वापस -ENOSPC;
	पूर्ण

	snapshot_id_attr = info->attrs[DEVLINK_ATTR_REGION_SNAPSHOT_ID];
	अगर (snapshot_id_attr) अणु
		snapshot_id = nla_get_u32(snapshot_id_attr);

		अगर (devlink_region_snapshot_get_by_id(region, snapshot_id)) अणु
			NL_SET_ERR_MSG_MOD(info->extack, "The requested snapshot id is already in use");
			वापस -EEXIST;
		पूर्ण

		err = __devlink_snapshot_id_insert(devlink, snapshot_id);
		अगर (err)
			वापस err;
	पूर्ण अन्यथा अणु
		err = __devlink_region_snapshot_id_get(devlink, &snapshot_id);
		अगर (err) अणु
			NL_SET_ERR_MSG_MOD(info->extack, "Failed to allocate a new snapshot id");
			वापस err;
		पूर्ण
	पूर्ण

	अगर (port)
		err = region->port_ops->snapshot(port, region->port_ops,
						 info->extack, &data);
	अन्यथा
		err = region->ops->snapshot(devlink, region->ops,
					    info->extack, &data);
	अगर (err)
		जाओ err_snapshot_capture;

	err = __devlink_region_snapshot_create(region, data, snapshot_id);
	अगर (err)
		जाओ err_snapshot_create;

	अगर (!snapshot_id_attr) अणु
		काष्ठा sk_buff *msg;

		snapshot = devlink_region_snapshot_get_by_id(region,
							     snapshot_id);
		अगर (WARN_ON(!snapshot))
			वापस -EINVAL;

		msg = devlink_nl_region_notअगरy_build(region, snapshot,
						     DEVLINK_CMD_REGION_NEW,
						     info->snd_portid,
						     info->snd_seq);
		err = PTR_ERR_OR_ZERO(msg);
		अगर (err)
			जाओ err_notअगरy;

		err = genlmsg_reply(msg, info);
		अगर (err)
			जाओ err_notअगरy;
	पूर्ण

	वापस 0;

err_snapshot_create:
	region->ops->deकाष्ठाor(data);
err_snapshot_capture:
	__devlink_snapshot_id_decrement(devlink, snapshot_id);
	वापस err;

err_notअगरy:
	devlink_region_snapshot_del(region, snapshot);
	वापस err;
पूर्ण

अटल पूर्णांक devlink_nl_cmd_region_पढ़ो_chunk_fill(काष्ठा sk_buff *msg,
						 काष्ठा devlink *devlink,
						 u8 *chunk, u32 chunk_size,
						 u64 addr)
अणु
	काष्ठा nlattr *chunk_attr;
	पूर्णांक err;

	chunk_attr = nla_nest_start_noflag(msg, DEVLINK_ATTR_REGION_CHUNK);
	अगर (!chunk_attr)
		वापस -EINVAL;

	err = nla_put(msg, DEVLINK_ATTR_REGION_CHUNK_DATA, chunk_size, chunk);
	अगर (err)
		जाओ nla_put_failure;

	err = nla_put_u64_64bit(msg, DEVLINK_ATTR_REGION_CHUNK_ADDR, addr,
				DEVLINK_ATTR_PAD);
	अगर (err)
		जाओ nla_put_failure;

	nla_nest_end(msg, chunk_attr);
	वापस 0;

nla_put_failure:
	nla_nest_cancel(msg, chunk_attr);
	वापस err;
पूर्ण

#घोषणा DEVLINK_REGION_READ_CHUNK_SIZE 256

अटल पूर्णांक devlink_nl_region_पढ़ो_snapshot_fill(काष्ठा sk_buff *skb,
						काष्ठा devlink *devlink,
						काष्ठा devlink_region *region,
						काष्ठा nlattr **attrs,
						u64 start_offset,
						u64 end_offset,
						u64 *new_offset)
अणु
	काष्ठा devlink_snapshot *snapshot;
	u64 curr_offset = start_offset;
	u32 snapshot_id;
	पूर्णांक err = 0;

	*new_offset = start_offset;

	snapshot_id = nla_get_u32(attrs[DEVLINK_ATTR_REGION_SNAPSHOT_ID]);
	snapshot = devlink_region_snapshot_get_by_id(region, snapshot_id);
	अगर (!snapshot)
		वापस -EINVAL;

	जबतक (curr_offset < end_offset) अणु
		u32 data_size;
		u8 *data;

		अगर (end_offset - curr_offset < DEVLINK_REGION_READ_CHUNK_SIZE)
			data_size = end_offset - curr_offset;
		अन्यथा
			data_size = DEVLINK_REGION_READ_CHUNK_SIZE;

		data = &snapshot->data[curr_offset];
		err = devlink_nl_cmd_region_पढ़ो_chunk_fill(skb, devlink,
							    data, data_size,
							    curr_offset);
		अगर (err)
			अवरोध;

		curr_offset += data_size;
	पूर्ण
	*new_offset = curr_offset;

	वापस err;
पूर्ण

अटल पूर्णांक devlink_nl_cmd_region_पढ़ो_dumpit(काष्ठा sk_buff *skb,
					     काष्ठा netlink_callback *cb)
अणु
	स्थिर काष्ठा genl_dumpit_info *info = genl_dumpit_info(cb);
	u64 ret_offset, start_offset, end_offset = U64_MAX;
	काष्ठा nlattr **attrs = info->attrs;
	काष्ठा devlink_port *port = शून्य;
	काष्ठा devlink_region *region;
	काष्ठा nlattr *chunks_attr;
	स्थिर अक्षर *region_name;
	काष्ठा devlink *devlink;
	अचिन्हित पूर्णांक index;
	व्योम *hdr;
	पूर्णांक err;

	start_offset = *((u64 *)&cb->args[0]);

	mutex_lock(&devlink_mutex);
	devlink = devlink_get_from_attrs(sock_net(cb->skb->sk), attrs);
	अगर (IS_ERR(devlink)) अणु
		err = PTR_ERR(devlink);
		जाओ out_dev;
	पूर्ण

	mutex_lock(&devlink->lock);

	अगर (!attrs[DEVLINK_ATTR_REGION_NAME] ||
	    !attrs[DEVLINK_ATTR_REGION_SNAPSHOT_ID]) अणु
		err = -EINVAL;
		जाओ out_unlock;
	पूर्ण

	अगर (info->attrs[DEVLINK_ATTR_PORT_INDEX]) अणु
		index = nla_get_u32(info->attrs[DEVLINK_ATTR_PORT_INDEX]);

		port = devlink_port_get_by_index(devlink, index);
		अगर (!port) अणु
			err = -ENODEV;
			जाओ out_unlock;
		पूर्ण
	पूर्ण

	region_name = nla_data(attrs[DEVLINK_ATTR_REGION_NAME]);

	अगर (port)
		region = devlink_port_region_get_by_name(port, region_name);
	अन्यथा
		region = devlink_region_get_by_name(devlink, region_name);

	अगर (!region) अणु
		err = -EINVAL;
		जाओ out_unlock;
	पूर्ण

	अगर (attrs[DEVLINK_ATTR_REGION_CHUNK_ADDR] &&
	    attrs[DEVLINK_ATTR_REGION_CHUNK_LEN]) अणु
		अगर (!start_offset)
			start_offset =
				nla_get_u64(attrs[DEVLINK_ATTR_REGION_CHUNK_ADDR]);

		end_offset = nla_get_u64(attrs[DEVLINK_ATTR_REGION_CHUNK_ADDR]);
		end_offset += nla_get_u64(attrs[DEVLINK_ATTR_REGION_CHUNK_LEN]);
	पूर्ण

	अगर (end_offset > region->size)
		end_offset = region->size;

	/* वापस 0 अगर there is no further data to पढ़ो */
	अगर (start_offset == end_offset) अणु
		err = 0;
		जाओ out_unlock;
	पूर्ण

	hdr = genlmsg_put(skb, NETLINK_CB(cb->skb).portid, cb->nlh->nlmsg_seq,
			  &devlink_nl_family, NLM_F_ACK | NLM_F_MULTI,
			  DEVLINK_CMD_REGION_READ);
	अगर (!hdr) अणु
		err = -EMSGSIZE;
		जाओ out_unlock;
	पूर्ण

	err = devlink_nl_put_handle(skb, devlink);
	अगर (err)
		जाओ nla_put_failure;

	अगर (region->port) अणु
		err = nla_put_u32(skb, DEVLINK_ATTR_PORT_INDEX,
				  region->port->index);
		अगर (err)
			जाओ nla_put_failure;
	पूर्ण

	err = nla_put_string(skb, DEVLINK_ATTR_REGION_NAME, region_name);
	अगर (err)
		जाओ nla_put_failure;

	chunks_attr = nla_nest_start_noflag(skb, DEVLINK_ATTR_REGION_CHUNKS);
	अगर (!chunks_attr) अणु
		err = -EMSGSIZE;
		जाओ nla_put_failure;
	पूर्ण

	err = devlink_nl_region_पढ़ो_snapshot_fill(skb, devlink,
						   region, attrs,
						   start_offset,
						   end_offset, &ret_offset);

	अगर (err && err != -EMSGSIZE)
		जाओ nla_put_failure;

	/* Check अगर there was any progress करोne to prevent infinite loop */
	अगर (ret_offset == start_offset) अणु
		err = -EINVAL;
		जाओ nla_put_failure;
	पूर्ण

	*((u64 *)&cb->args[0]) = ret_offset;

	nla_nest_end(skb, chunks_attr);
	genlmsg_end(skb, hdr);
	mutex_unlock(&devlink->lock);
	mutex_unlock(&devlink_mutex);

	वापस skb->len;

nla_put_failure:
	genlmsg_cancel(skb, hdr);
out_unlock:
	mutex_unlock(&devlink->lock);
out_dev:
	mutex_unlock(&devlink_mutex);
	वापस err;
पूर्ण

काष्ठा devlink_info_req अणु
	काष्ठा sk_buff *msg;
पूर्ण;

पूर्णांक devlink_info_driver_name_put(काष्ठा devlink_info_req *req, स्थिर अक्षर *name)
अणु
	वापस nla_put_string(req->msg, DEVLINK_ATTR_INFO_DRIVER_NAME, name);
पूर्ण
EXPORT_SYMBOL_GPL(devlink_info_driver_name_put);

पूर्णांक devlink_info_serial_number_put(काष्ठा devlink_info_req *req, स्थिर अक्षर *sn)
अणु
	वापस nla_put_string(req->msg, DEVLINK_ATTR_INFO_SERIAL_NUMBER, sn);
पूर्ण
EXPORT_SYMBOL_GPL(devlink_info_serial_number_put);

पूर्णांक devlink_info_board_serial_number_put(काष्ठा devlink_info_req *req,
					 स्थिर अक्षर *bsn)
अणु
	वापस nla_put_string(req->msg, DEVLINK_ATTR_INFO_BOARD_SERIAL_NUMBER,
			      bsn);
पूर्ण
EXPORT_SYMBOL_GPL(devlink_info_board_serial_number_put);

अटल पूर्णांक devlink_info_version_put(काष्ठा devlink_info_req *req, पूर्णांक attr,
				    स्थिर अक्षर *version_name,
				    स्थिर अक्षर *version_value)
अणु
	काष्ठा nlattr *nest;
	पूर्णांक err;

	nest = nla_nest_start_noflag(req->msg, attr);
	अगर (!nest)
		वापस -EMSGSIZE;

	err = nla_put_string(req->msg, DEVLINK_ATTR_INFO_VERSION_NAME,
			     version_name);
	अगर (err)
		जाओ nla_put_failure;

	err = nla_put_string(req->msg, DEVLINK_ATTR_INFO_VERSION_VALUE,
			     version_value);
	अगर (err)
		जाओ nla_put_failure;

	nla_nest_end(req->msg, nest);

	वापस 0;

nla_put_failure:
	nla_nest_cancel(req->msg, nest);
	वापस err;
पूर्ण

पूर्णांक devlink_info_version_fixed_put(काष्ठा devlink_info_req *req,
				   स्थिर अक्षर *version_name,
				   स्थिर अक्षर *version_value)
अणु
	वापस devlink_info_version_put(req, DEVLINK_ATTR_INFO_VERSION_FIXED,
					version_name, version_value);
पूर्ण
EXPORT_SYMBOL_GPL(devlink_info_version_fixed_put);

पूर्णांक devlink_info_version_stored_put(काष्ठा devlink_info_req *req,
				    स्थिर अक्षर *version_name,
				    स्थिर अक्षर *version_value)
अणु
	वापस devlink_info_version_put(req, DEVLINK_ATTR_INFO_VERSION_STORED,
					version_name, version_value);
पूर्ण
EXPORT_SYMBOL_GPL(devlink_info_version_stored_put);

पूर्णांक devlink_info_version_running_put(काष्ठा devlink_info_req *req,
				     स्थिर अक्षर *version_name,
				     स्थिर अक्षर *version_value)
अणु
	वापस devlink_info_version_put(req, DEVLINK_ATTR_INFO_VERSION_RUNNING,
					version_name, version_value);
पूर्ण
EXPORT_SYMBOL_GPL(devlink_info_version_running_put);

अटल पूर्णांक
devlink_nl_info_fill(काष्ठा sk_buff *msg, काष्ठा devlink *devlink,
		     क्रमागत devlink_command cmd, u32 portid,
		     u32 seq, पूर्णांक flags, काष्ठा netlink_ext_ack *extack)
अणु
	काष्ठा devlink_info_req req;
	व्योम *hdr;
	पूर्णांक err;

	hdr = genlmsg_put(msg, portid, seq, &devlink_nl_family, flags, cmd);
	अगर (!hdr)
		वापस -EMSGSIZE;

	err = -EMSGSIZE;
	अगर (devlink_nl_put_handle(msg, devlink))
		जाओ err_cancel_msg;

	req.msg = msg;
	err = devlink->ops->info_get(devlink, &req, extack);
	अगर (err)
		जाओ err_cancel_msg;

	genlmsg_end(msg, hdr);
	वापस 0;

err_cancel_msg:
	genlmsg_cancel(msg, hdr);
	वापस err;
पूर्ण

अटल पूर्णांक devlink_nl_cmd_info_get_करोit(काष्ठा sk_buff *skb,
					काष्ठा genl_info *info)
अणु
	काष्ठा devlink *devlink = info->user_ptr[0];
	काष्ठा sk_buff *msg;
	पूर्णांक err;

	अगर (!devlink->ops->info_get)
		वापस -EOPNOTSUPP;

	msg = nlmsg_new(NLMSG_DEFAULT_SIZE, GFP_KERNEL);
	अगर (!msg)
		वापस -ENOMEM;

	err = devlink_nl_info_fill(msg, devlink, DEVLINK_CMD_INFO_GET,
				   info->snd_portid, info->snd_seq, 0,
				   info->extack);
	अगर (err) अणु
		nlmsg_मुक्त(msg);
		वापस err;
	पूर्ण

	वापस genlmsg_reply(msg, info);
पूर्ण

अटल पूर्णांक devlink_nl_cmd_info_get_dumpit(काष्ठा sk_buff *msg,
					  काष्ठा netlink_callback *cb)
अणु
	काष्ठा devlink *devlink;
	पूर्णांक start = cb->args[0];
	पूर्णांक idx = 0;
	पूर्णांक err = 0;

	mutex_lock(&devlink_mutex);
	list_क्रम_each_entry(devlink, &devlink_list, list) अणु
		अगर (!net_eq(devlink_net(devlink), sock_net(msg->sk)))
			जारी;
		अगर (idx < start) अणु
			idx++;
			जारी;
		पूर्ण

		अगर (!devlink->ops->info_get) अणु
			idx++;
			जारी;
		पूर्ण

		mutex_lock(&devlink->lock);
		err = devlink_nl_info_fill(msg, devlink, DEVLINK_CMD_INFO_GET,
					   NETLINK_CB(cb->skb).portid,
					   cb->nlh->nlmsg_seq, NLM_F_MULTI,
					   cb->extack);
		mutex_unlock(&devlink->lock);
		अगर (err == -EOPNOTSUPP)
			err = 0;
		अन्यथा अगर (err)
			अवरोध;
		idx++;
	पूर्ण
	mutex_unlock(&devlink_mutex);

	अगर (err != -EMSGSIZE)
		वापस err;

	cb->args[0] = idx;
	वापस msg->len;
पूर्ण

काष्ठा devlink_fmsg_item अणु
	काष्ठा list_head list;
	पूर्णांक attrtype;
	u8 nla_type;
	u16 len;
	पूर्णांक value[];
पूर्ण;

काष्ठा devlink_fmsg अणु
	काष्ठा list_head item_list;
	bool putting_binary; /* This flag क्रमces enclosing of binary data
			      * in an array brackets. It क्रमces using
			      * of designated API:
			      * devlink_fmsg_binary_pair_nest_start()
			      * devlink_fmsg_binary_pair_nest_end()
			      */
पूर्ण;

अटल काष्ठा devlink_fmsg *devlink_fmsg_alloc(व्योम)
अणु
	काष्ठा devlink_fmsg *fmsg;

	fmsg = kzalloc(माप(*fmsg), GFP_KERNEL);
	अगर (!fmsg)
		वापस शून्य;

	INIT_LIST_HEAD(&fmsg->item_list);

	वापस fmsg;
पूर्ण

अटल व्योम devlink_fmsg_मुक्त(काष्ठा devlink_fmsg *fmsg)
अणु
	काष्ठा devlink_fmsg_item *item, *पंचांगp;

	list_क्रम_each_entry_safe(item, पंचांगp, &fmsg->item_list, list) अणु
		list_del(&item->list);
		kमुक्त(item);
	पूर्ण
	kमुक्त(fmsg);
पूर्ण

अटल पूर्णांक devlink_fmsg_nest_common(काष्ठा devlink_fmsg *fmsg,
				    पूर्णांक attrtype)
अणु
	काष्ठा devlink_fmsg_item *item;

	item = kzalloc(माप(*item), GFP_KERNEL);
	अगर (!item)
		वापस -ENOMEM;

	item->attrtype = attrtype;
	list_add_tail(&item->list, &fmsg->item_list);

	वापस 0;
पूर्ण

पूर्णांक devlink_fmsg_obj_nest_start(काष्ठा devlink_fmsg *fmsg)
अणु
	अगर (fmsg->putting_binary)
		वापस -EINVAL;

	वापस devlink_fmsg_nest_common(fmsg, DEVLINK_ATTR_FMSG_OBJ_NEST_START);
पूर्ण
EXPORT_SYMBOL_GPL(devlink_fmsg_obj_nest_start);

अटल पूर्णांक devlink_fmsg_nest_end(काष्ठा devlink_fmsg *fmsg)
अणु
	अगर (fmsg->putting_binary)
		वापस -EINVAL;

	वापस devlink_fmsg_nest_common(fmsg, DEVLINK_ATTR_FMSG_NEST_END);
पूर्ण

पूर्णांक devlink_fmsg_obj_nest_end(काष्ठा devlink_fmsg *fmsg)
अणु
	अगर (fmsg->putting_binary)
		वापस -EINVAL;

	वापस devlink_fmsg_nest_end(fmsg);
पूर्ण
EXPORT_SYMBOL_GPL(devlink_fmsg_obj_nest_end);

#घोषणा DEVLINK_FMSG_MAX_SIZE (GENLMSG_DEFAULT_SIZE - GENL_HDRLEN - NLA_HDRLEN)

अटल पूर्णांक devlink_fmsg_put_name(काष्ठा devlink_fmsg *fmsg, स्थिर अक्षर *name)
अणु
	काष्ठा devlink_fmsg_item *item;

	अगर (fmsg->putting_binary)
		वापस -EINVAL;

	अगर (म_माप(name) + 1 > DEVLINK_FMSG_MAX_SIZE)
		वापस -EMSGSIZE;

	item = kzalloc(माप(*item) + म_माप(name) + 1, GFP_KERNEL);
	अगर (!item)
		वापस -ENOMEM;

	item->nla_type = NLA_NUL_STRING;
	item->len = म_माप(name) + 1;
	item->attrtype = DEVLINK_ATTR_FMSG_OBJ_NAME;
	स_नकल(&item->value, name, item->len);
	list_add_tail(&item->list, &fmsg->item_list);

	वापस 0;
पूर्ण

पूर्णांक devlink_fmsg_pair_nest_start(काष्ठा devlink_fmsg *fmsg, स्थिर अक्षर *name)
अणु
	पूर्णांक err;

	अगर (fmsg->putting_binary)
		वापस -EINVAL;

	err = devlink_fmsg_nest_common(fmsg, DEVLINK_ATTR_FMSG_PAIR_NEST_START);
	अगर (err)
		वापस err;

	err = devlink_fmsg_put_name(fmsg, name);
	अगर (err)
		वापस err;

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(devlink_fmsg_pair_nest_start);

पूर्णांक devlink_fmsg_pair_nest_end(काष्ठा devlink_fmsg *fmsg)
अणु
	अगर (fmsg->putting_binary)
		वापस -EINVAL;

	वापस devlink_fmsg_nest_end(fmsg);
पूर्ण
EXPORT_SYMBOL_GPL(devlink_fmsg_pair_nest_end);

पूर्णांक devlink_fmsg_arr_pair_nest_start(काष्ठा devlink_fmsg *fmsg,
				     स्थिर अक्षर *name)
अणु
	पूर्णांक err;

	अगर (fmsg->putting_binary)
		वापस -EINVAL;

	err = devlink_fmsg_pair_nest_start(fmsg, name);
	अगर (err)
		वापस err;

	err = devlink_fmsg_nest_common(fmsg, DEVLINK_ATTR_FMSG_ARR_NEST_START);
	अगर (err)
		वापस err;

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(devlink_fmsg_arr_pair_nest_start);

पूर्णांक devlink_fmsg_arr_pair_nest_end(काष्ठा devlink_fmsg *fmsg)
अणु
	पूर्णांक err;

	अगर (fmsg->putting_binary)
		वापस -EINVAL;

	err = devlink_fmsg_nest_end(fmsg);
	अगर (err)
		वापस err;

	err = devlink_fmsg_nest_end(fmsg);
	अगर (err)
		वापस err;

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(devlink_fmsg_arr_pair_nest_end);

पूर्णांक devlink_fmsg_binary_pair_nest_start(काष्ठा devlink_fmsg *fmsg,
					स्थिर अक्षर *name)
अणु
	पूर्णांक err;

	err = devlink_fmsg_arr_pair_nest_start(fmsg, name);
	अगर (err)
		वापस err;

	fmsg->putting_binary = true;
	वापस err;
पूर्ण
EXPORT_SYMBOL_GPL(devlink_fmsg_binary_pair_nest_start);

पूर्णांक devlink_fmsg_binary_pair_nest_end(काष्ठा devlink_fmsg *fmsg)
अणु
	अगर (!fmsg->putting_binary)
		वापस -EINVAL;

	fmsg->putting_binary = false;
	वापस devlink_fmsg_arr_pair_nest_end(fmsg);
पूर्ण
EXPORT_SYMBOL_GPL(devlink_fmsg_binary_pair_nest_end);

अटल पूर्णांक devlink_fmsg_put_value(काष्ठा devlink_fmsg *fmsg,
				  स्थिर व्योम *value, u16 value_len,
				  u8 value_nla_type)
अणु
	काष्ठा devlink_fmsg_item *item;

	अगर (value_len > DEVLINK_FMSG_MAX_SIZE)
		वापस -EMSGSIZE;

	item = kzalloc(माप(*item) + value_len, GFP_KERNEL);
	अगर (!item)
		वापस -ENOMEM;

	item->nla_type = value_nla_type;
	item->len = value_len;
	item->attrtype = DEVLINK_ATTR_FMSG_OBJ_VALUE_DATA;
	स_नकल(&item->value, value, item->len);
	list_add_tail(&item->list, &fmsg->item_list);

	वापस 0;
पूर्ण

पूर्णांक devlink_fmsg_bool_put(काष्ठा devlink_fmsg *fmsg, bool value)
अणु
	अगर (fmsg->putting_binary)
		वापस -EINVAL;

	वापस devlink_fmsg_put_value(fmsg, &value, माप(value), NLA_FLAG);
पूर्ण
EXPORT_SYMBOL_GPL(devlink_fmsg_bool_put);

पूर्णांक devlink_fmsg_u8_put(काष्ठा devlink_fmsg *fmsg, u8 value)
अणु
	अगर (fmsg->putting_binary)
		वापस -EINVAL;

	वापस devlink_fmsg_put_value(fmsg, &value, माप(value), NLA_U8);
पूर्ण
EXPORT_SYMBOL_GPL(devlink_fmsg_u8_put);

पूर्णांक devlink_fmsg_u32_put(काष्ठा devlink_fmsg *fmsg, u32 value)
अणु
	अगर (fmsg->putting_binary)
		वापस -EINVAL;

	वापस devlink_fmsg_put_value(fmsg, &value, माप(value), NLA_U32);
पूर्ण
EXPORT_SYMBOL_GPL(devlink_fmsg_u32_put);

पूर्णांक devlink_fmsg_u64_put(काष्ठा devlink_fmsg *fmsg, u64 value)
अणु
	अगर (fmsg->putting_binary)
		वापस -EINVAL;

	वापस devlink_fmsg_put_value(fmsg, &value, माप(value), NLA_U64);
पूर्ण
EXPORT_SYMBOL_GPL(devlink_fmsg_u64_put);

पूर्णांक devlink_fmsg_string_put(काष्ठा devlink_fmsg *fmsg, स्थिर अक्षर *value)
अणु
	अगर (fmsg->putting_binary)
		वापस -EINVAL;

	वापस devlink_fmsg_put_value(fmsg, value, म_माप(value) + 1,
				      NLA_NUL_STRING);
पूर्ण
EXPORT_SYMBOL_GPL(devlink_fmsg_string_put);

पूर्णांक devlink_fmsg_binary_put(काष्ठा devlink_fmsg *fmsg, स्थिर व्योम *value,
			    u16 value_len)
अणु
	अगर (!fmsg->putting_binary)
		वापस -EINVAL;

	वापस devlink_fmsg_put_value(fmsg, value, value_len, NLA_BINARY);
पूर्ण
EXPORT_SYMBOL_GPL(devlink_fmsg_binary_put);

पूर्णांक devlink_fmsg_bool_pair_put(काष्ठा devlink_fmsg *fmsg, स्थिर अक्षर *name,
			       bool value)
अणु
	पूर्णांक err;

	err = devlink_fmsg_pair_nest_start(fmsg, name);
	अगर (err)
		वापस err;

	err = devlink_fmsg_bool_put(fmsg, value);
	अगर (err)
		वापस err;

	err = devlink_fmsg_pair_nest_end(fmsg);
	अगर (err)
		वापस err;

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(devlink_fmsg_bool_pair_put);

पूर्णांक devlink_fmsg_u8_pair_put(काष्ठा devlink_fmsg *fmsg, स्थिर अक्षर *name,
			     u8 value)
अणु
	पूर्णांक err;

	err = devlink_fmsg_pair_nest_start(fmsg, name);
	अगर (err)
		वापस err;

	err = devlink_fmsg_u8_put(fmsg, value);
	अगर (err)
		वापस err;

	err = devlink_fmsg_pair_nest_end(fmsg);
	अगर (err)
		वापस err;

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(devlink_fmsg_u8_pair_put);

पूर्णांक devlink_fmsg_u32_pair_put(काष्ठा devlink_fmsg *fmsg, स्थिर अक्षर *name,
			      u32 value)
अणु
	पूर्णांक err;

	err = devlink_fmsg_pair_nest_start(fmsg, name);
	अगर (err)
		वापस err;

	err = devlink_fmsg_u32_put(fmsg, value);
	अगर (err)
		वापस err;

	err = devlink_fmsg_pair_nest_end(fmsg);
	अगर (err)
		वापस err;

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(devlink_fmsg_u32_pair_put);

पूर्णांक devlink_fmsg_u64_pair_put(काष्ठा devlink_fmsg *fmsg, स्थिर अक्षर *name,
			      u64 value)
अणु
	पूर्णांक err;

	err = devlink_fmsg_pair_nest_start(fmsg, name);
	अगर (err)
		वापस err;

	err = devlink_fmsg_u64_put(fmsg, value);
	अगर (err)
		वापस err;

	err = devlink_fmsg_pair_nest_end(fmsg);
	अगर (err)
		वापस err;

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(devlink_fmsg_u64_pair_put);

पूर्णांक devlink_fmsg_string_pair_put(काष्ठा devlink_fmsg *fmsg, स्थिर अक्षर *name,
				 स्थिर अक्षर *value)
अणु
	पूर्णांक err;

	err = devlink_fmsg_pair_nest_start(fmsg, name);
	अगर (err)
		वापस err;

	err = devlink_fmsg_string_put(fmsg, value);
	अगर (err)
		वापस err;

	err = devlink_fmsg_pair_nest_end(fmsg);
	अगर (err)
		वापस err;

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(devlink_fmsg_string_pair_put);

पूर्णांक devlink_fmsg_binary_pair_put(काष्ठा devlink_fmsg *fmsg, स्थिर अक्षर *name,
				 स्थिर व्योम *value, u32 value_len)
अणु
	u32 data_size;
	पूर्णांक end_err;
	u32 offset;
	पूर्णांक err;

	err = devlink_fmsg_binary_pair_nest_start(fmsg, name);
	अगर (err)
		वापस err;

	क्रम (offset = 0; offset < value_len; offset += data_size) अणु
		data_size = value_len - offset;
		अगर (data_size > DEVLINK_FMSG_MAX_SIZE)
			data_size = DEVLINK_FMSG_MAX_SIZE;
		err = devlink_fmsg_binary_put(fmsg, value + offset, data_size);
		अगर (err)
			अवरोध;
		/* Exit from loop with a अवरोध (instead of
		 * वापस) to make sure putting_binary is turned off in
		 * devlink_fmsg_binary_pair_nest_end
		 */
	पूर्ण

	end_err = devlink_fmsg_binary_pair_nest_end(fmsg);
	अगर (end_err)
		err = end_err;

	वापस err;
पूर्ण
EXPORT_SYMBOL_GPL(devlink_fmsg_binary_pair_put);

अटल पूर्णांक
devlink_fmsg_item_fill_type(काष्ठा devlink_fmsg_item *msg, काष्ठा sk_buff *skb)
अणु
	चयन (msg->nla_type) अणु
	हाल NLA_FLAG:
	हाल NLA_U8:
	हाल NLA_U32:
	हाल NLA_U64:
	हाल NLA_NUL_STRING:
	हाल NLA_BINARY:
		वापस nla_put_u8(skb, DEVLINK_ATTR_FMSG_OBJ_VALUE_TYPE,
				  msg->nla_type);
	शेष:
		वापस -EINVAL;
	पूर्ण
पूर्ण

अटल पूर्णांक
devlink_fmsg_item_fill_data(काष्ठा devlink_fmsg_item *msg, काष्ठा sk_buff *skb)
अणु
	पूर्णांक attrtype = DEVLINK_ATTR_FMSG_OBJ_VALUE_DATA;
	u8 पंचांगp;

	चयन (msg->nla_type) अणु
	हाल NLA_FLAG:
		/* Always provide flag data, regardless of its value */
		पंचांगp = *(bool *) msg->value;

		वापस nla_put_u8(skb, attrtype, पंचांगp);
	हाल NLA_U8:
		वापस nla_put_u8(skb, attrtype, *(u8 *) msg->value);
	हाल NLA_U32:
		वापस nla_put_u32(skb, attrtype, *(u32 *) msg->value);
	हाल NLA_U64:
		वापस nla_put_u64_64bit(skb, attrtype, *(u64 *) msg->value,
					 DEVLINK_ATTR_PAD);
	हाल NLA_NUL_STRING:
		वापस nla_put_string(skb, attrtype, (अक्षर *) &msg->value);
	हाल NLA_BINARY:
		वापस nla_put(skb, attrtype, msg->len, (व्योम *) &msg->value);
	शेष:
		वापस -EINVAL;
	पूर्ण
पूर्ण

अटल पूर्णांक
devlink_fmsg_prepare_skb(काष्ठा devlink_fmsg *fmsg, काष्ठा sk_buff *skb,
			 पूर्णांक *start)
अणु
	काष्ठा devlink_fmsg_item *item;
	काष्ठा nlattr *fmsg_nlattr;
	पूर्णांक i = 0;
	पूर्णांक err;

	fmsg_nlattr = nla_nest_start_noflag(skb, DEVLINK_ATTR_FMSG);
	अगर (!fmsg_nlattr)
		वापस -EMSGSIZE;

	list_क्रम_each_entry(item, &fmsg->item_list, list) अणु
		अगर (i < *start) अणु
			i++;
			जारी;
		पूर्ण

		चयन (item->attrtype) अणु
		हाल DEVLINK_ATTR_FMSG_OBJ_NEST_START:
		हाल DEVLINK_ATTR_FMSG_PAIR_NEST_START:
		हाल DEVLINK_ATTR_FMSG_ARR_NEST_START:
		हाल DEVLINK_ATTR_FMSG_NEST_END:
			err = nla_put_flag(skb, item->attrtype);
			अवरोध;
		हाल DEVLINK_ATTR_FMSG_OBJ_VALUE_DATA:
			err = devlink_fmsg_item_fill_type(item, skb);
			अगर (err)
				अवरोध;
			err = devlink_fmsg_item_fill_data(item, skb);
			अवरोध;
		हाल DEVLINK_ATTR_FMSG_OBJ_NAME:
			err = nla_put_string(skb, item->attrtype,
					     (अक्षर *) &item->value);
			अवरोध;
		शेष:
			err = -EINVAL;
			अवरोध;
		पूर्ण
		अगर (!err)
			*start = ++i;
		अन्यथा
			अवरोध;
	पूर्ण

	nla_nest_end(skb, fmsg_nlattr);
	वापस err;
पूर्ण

अटल पूर्णांक devlink_fmsg_snd(काष्ठा devlink_fmsg *fmsg,
			    काष्ठा genl_info *info,
			    क्रमागत devlink_command cmd, पूर्णांक flags)
अणु
	काष्ठा nlmsghdr *nlh;
	काष्ठा sk_buff *skb;
	bool last = false;
	पूर्णांक index = 0;
	व्योम *hdr;
	पूर्णांक err;

	जबतक (!last) अणु
		पूर्णांक पंचांगp_index = index;

		skb = genlmsg_new(GENLMSG_DEFAULT_SIZE, GFP_KERNEL);
		अगर (!skb)
			वापस -ENOMEM;

		hdr = genlmsg_put(skb, info->snd_portid, info->snd_seq,
				  &devlink_nl_family, flags | NLM_F_MULTI, cmd);
		अगर (!hdr) अणु
			err = -EMSGSIZE;
			जाओ nla_put_failure;
		पूर्ण

		err = devlink_fmsg_prepare_skb(fmsg, skb, &index);
		अगर (!err)
			last = true;
		अन्यथा अगर (err != -EMSGSIZE || पंचांगp_index == index)
			जाओ nla_put_failure;

		genlmsg_end(skb, hdr);
		err = genlmsg_reply(skb, info);
		अगर (err)
			वापस err;
	पूर्ण

	skb = genlmsg_new(GENLMSG_DEFAULT_SIZE, GFP_KERNEL);
	अगर (!skb)
		वापस -ENOMEM;
	nlh = nlmsg_put(skb, info->snd_portid, info->snd_seq,
			NLMSG_DONE, 0, flags | NLM_F_MULTI);
	अगर (!nlh) अणु
		err = -EMSGSIZE;
		जाओ nla_put_failure;
	पूर्ण

	वापस genlmsg_reply(skb, info);

nla_put_failure:
	nlmsg_मुक्त(skb);
	वापस err;
पूर्ण

अटल पूर्णांक devlink_fmsg_dumpit(काष्ठा devlink_fmsg *fmsg, काष्ठा sk_buff *skb,
			       काष्ठा netlink_callback *cb,
			       क्रमागत devlink_command cmd)
अणु
	पूर्णांक index = cb->args[0];
	पूर्णांक पंचांगp_index = index;
	व्योम *hdr;
	पूर्णांक err;

	hdr = genlmsg_put(skb, NETLINK_CB(cb->skb).portid, cb->nlh->nlmsg_seq,
			  &devlink_nl_family, NLM_F_ACK | NLM_F_MULTI, cmd);
	अगर (!hdr) अणु
		err = -EMSGSIZE;
		जाओ nla_put_failure;
	पूर्ण

	err = devlink_fmsg_prepare_skb(fmsg, skb, &index);
	अगर ((err && err != -EMSGSIZE) || पंचांगp_index == index)
		जाओ nla_put_failure;

	cb->args[0] = index;
	genlmsg_end(skb, hdr);
	वापस skb->len;

nla_put_failure:
	genlmsg_cancel(skb, hdr);
	वापस err;
पूर्ण

काष्ठा devlink_health_reporter अणु
	काष्ठा list_head list;
	व्योम *priv;
	स्थिर काष्ठा devlink_health_reporter_ops *ops;
	काष्ठा devlink *devlink;
	काष्ठा devlink_port *devlink_port;
	काष्ठा devlink_fmsg *dump_fmsg;
	काष्ठा mutex dump_lock; /* lock parallel पढ़ो/ग_लिखो from dump buffers */
	u64 graceful_period;
	bool स्वतः_recover;
	bool स्वतः_dump;
	u8 health_state;
	u64 dump_ts;
	u64 dump_real_ts;
	u64 error_count;
	u64 recovery_count;
	u64 last_recovery_ts;
	refcount_t refcount;
पूर्ण;

व्योम *
devlink_health_reporter_priv(काष्ठा devlink_health_reporter *reporter)
अणु
	वापस reporter->priv;
पूर्ण
EXPORT_SYMBOL_GPL(devlink_health_reporter_priv);

अटल काष्ठा devlink_health_reporter *
__devlink_health_reporter_find_by_name(काष्ठा list_head *reporter_list,
				       काष्ठा mutex *list_lock,
				       स्थिर अक्षर *reporter_name)
अणु
	काष्ठा devlink_health_reporter *reporter;

	lockdep_निश्चित_held(list_lock);
	list_क्रम_each_entry(reporter, reporter_list, list)
		अगर (!म_भेद(reporter->ops->name, reporter_name))
			वापस reporter;
	वापस शून्य;
पूर्ण

अटल काष्ठा devlink_health_reporter *
devlink_health_reporter_find_by_name(काष्ठा devlink *devlink,
				     स्थिर अक्षर *reporter_name)
अणु
	वापस __devlink_health_reporter_find_by_name(&devlink->reporter_list,
						      &devlink->reporters_lock,
						      reporter_name);
पूर्ण

अटल काष्ठा devlink_health_reporter *
devlink_port_health_reporter_find_by_name(काष्ठा devlink_port *devlink_port,
					  स्थिर अक्षर *reporter_name)
अणु
	वापस __devlink_health_reporter_find_by_name(&devlink_port->reporter_list,
						      &devlink_port->reporters_lock,
						      reporter_name);
पूर्ण

अटल काष्ठा devlink_health_reporter *
__devlink_health_reporter_create(काष्ठा devlink *devlink,
				 स्थिर काष्ठा devlink_health_reporter_ops *ops,
				 u64 graceful_period, व्योम *priv)
अणु
	काष्ठा devlink_health_reporter *reporter;

	अगर (WARN_ON(graceful_period && !ops->recover))
		वापस ERR_PTR(-EINVAL);

	reporter = kzalloc(माप(*reporter), GFP_KERNEL);
	अगर (!reporter)
		वापस ERR_PTR(-ENOMEM);

	reporter->priv = priv;
	reporter->ops = ops;
	reporter->devlink = devlink;
	reporter->graceful_period = graceful_period;
	reporter->स्वतः_recover = !!ops->recover;
	reporter->स्वतः_dump = !!ops->dump;
	mutex_init(&reporter->dump_lock);
	refcount_set(&reporter->refcount, 1);
	वापस reporter;
पूर्ण

/**
 *	devlink_port_health_reporter_create - create devlink health reporter क्रम
 *	                                      specअगरied port instance
 *
 *	@port: devlink_port which should contain the new reporter
 *	@ops: ops
 *	@graceful_period: to aव्योम recovery loops, in msecs
 *	@priv: priv
 */
काष्ठा devlink_health_reporter *
devlink_port_health_reporter_create(काष्ठा devlink_port *port,
				    स्थिर काष्ठा devlink_health_reporter_ops *ops,
				    u64 graceful_period, व्योम *priv)
अणु
	काष्ठा devlink_health_reporter *reporter;

	mutex_lock(&port->reporters_lock);
	अगर (__devlink_health_reporter_find_by_name(&port->reporter_list,
						   &port->reporters_lock, ops->name)) अणु
		reporter = ERR_PTR(-EEXIST);
		जाओ unlock;
	पूर्ण

	reporter = __devlink_health_reporter_create(port->devlink, ops,
						    graceful_period, priv);
	अगर (IS_ERR(reporter))
		जाओ unlock;

	reporter->devlink_port = port;
	list_add_tail(&reporter->list, &port->reporter_list);
unlock:
	mutex_unlock(&port->reporters_lock);
	वापस reporter;
पूर्ण
EXPORT_SYMBOL_GPL(devlink_port_health_reporter_create);

/**
 *	devlink_health_reporter_create - create devlink health reporter
 *
 *	@devlink: devlink
 *	@ops: ops
 *	@graceful_period: to aव्योम recovery loops, in msecs
 *	@priv: priv
 */
काष्ठा devlink_health_reporter *
devlink_health_reporter_create(काष्ठा devlink *devlink,
			       स्थिर काष्ठा devlink_health_reporter_ops *ops,
			       u64 graceful_period, व्योम *priv)
अणु
	काष्ठा devlink_health_reporter *reporter;

	mutex_lock(&devlink->reporters_lock);
	अगर (devlink_health_reporter_find_by_name(devlink, ops->name)) अणु
		reporter = ERR_PTR(-EEXIST);
		जाओ unlock;
	पूर्ण

	reporter = __devlink_health_reporter_create(devlink, ops,
						    graceful_period, priv);
	अगर (IS_ERR(reporter))
		जाओ unlock;

	list_add_tail(&reporter->list, &devlink->reporter_list);
unlock:
	mutex_unlock(&devlink->reporters_lock);
	वापस reporter;
पूर्ण
EXPORT_SYMBOL_GPL(devlink_health_reporter_create);

अटल व्योम
devlink_health_reporter_मुक्त(काष्ठा devlink_health_reporter *reporter)
अणु
	mutex_destroy(&reporter->dump_lock);
	अगर (reporter->dump_fmsg)
		devlink_fmsg_मुक्त(reporter->dump_fmsg);
	kमुक्त(reporter);
पूर्ण

अटल व्योम
devlink_health_reporter_put(काष्ठा devlink_health_reporter *reporter)
अणु
	अगर (refcount_dec_and_test(&reporter->refcount))
		devlink_health_reporter_मुक्त(reporter);
पूर्ण

अटल व्योम
__devlink_health_reporter_destroy(काष्ठा devlink_health_reporter *reporter)
अणु
	list_del(&reporter->list);
	devlink_health_reporter_put(reporter);
पूर्ण

/**
 *	devlink_health_reporter_destroy - destroy devlink health reporter
 *
 *	@reporter: devlink health reporter to destroy
 */
व्योम
devlink_health_reporter_destroy(काष्ठा devlink_health_reporter *reporter)
अणु
	काष्ठा mutex *lock = &reporter->devlink->reporters_lock;

	mutex_lock(lock);
	__devlink_health_reporter_destroy(reporter);
	mutex_unlock(lock);
पूर्ण
EXPORT_SYMBOL_GPL(devlink_health_reporter_destroy);

/**
 *	devlink_port_health_reporter_destroy - destroy devlink port health reporter
 *
 *	@reporter: devlink health reporter to destroy
 */
व्योम
devlink_port_health_reporter_destroy(काष्ठा devlink_health_reporter *reporter)
अणु
	काष्ठा mutex *lock = &reporter->devlink_port->reporters_lock;

	mutex_lock(lock);
	__devlink_health_reporter_destroy(reporter);
	mutex_unlock(lock);
पूर्ण
EXPORT_SYMBOL_GPL(devlink_port_health_reporter_destroy);

अटल पूर्णांक
devlink_nl_health_reporter_fill(काष्ठा sk_buff *msg,
				काष्ठा devlink *devlink,
				काष्ठा devlink_health_reporter *reporter,
				क्रमागत devlink_command cmd, u32 portid,
				u32 seq, पूर्णांक flags)
अणु
	काष्ठा nlattr *reporter_attr;
	व्योम *hdr;

	hdr = genlmsg_put(msg, portid, seq, &devlink_nl_family, flags, cmd);
	अगर (!hdr)
		वापस -EMSGSIZE;

	अगर (devlink_nl_put_handle(msg, devlink))
		जाओ genlmsg_cancel;

	अगर (reporter->devlink_port) अणु
		अगर (nla_put_u32(msg, DEVLINK_ATTR_PORT_INDEX, reporter->devlink_port->index))
			जाओ genlmsg_cancel;
	पूर्ण
	reporter_attr = nla_nest_start_noflag(msg,
					      DEVLINK_ATTR_HEALTH_REPORTER);
	अगर (!reporter_attr)
		जाओ genlmsg_cancel;
	अगर (nla_put_string(msg, DEVLINK_ATTR_HEALTH_REPORTER_NAME,
			   reporter->ops->name))
		जाओ reporter_nest_cancel;
	अगर (nla_put_u8(msg, DEVLINK_ATTR_HEALTH_REPORTER_STATE,
		       reporter->health_state))
		जाओ reporter_nest_cancel;
	अगर (nla_put_u64_64bit(msg, DEVLINK_ATTR_HEALTH_REPORTER_ERR_COUNT,
			      reporter->error_count, DEVLINK_ATTR_PAD))
		जाओ reporter_nest_cancel;
	अगर (nla_put_u64_64bit(msg, DEVLINK_ATTR_HEALTH_REPORTER_RECOVER_COUNT,
			      reporter->recovery_count, DEVLINK_ATTR_PAD))
		जाओ reporter_nest_cancel;
	अगर (reporter->ops->recover &&
	    nla_put_u64_64bit(msg, DEVLINK_ATTR_HEALTH_REPORTER_GRACEFUL_PERIOD,
			      reporter->graceful_period,
			      DEVLINK_ATTR_PAD))
		जाओ reporter_nest_cancel;
	अगर (reporter->ops->recover &&
	    nla_put_u8(msg, DEVLINK_ATTR_HEALTH_REPORTER_AUTO_RECOVER,
		       reporter->स्वतः_recover))
		जाओ reporter_nest_cancel;
	अगर (reporter->dump_fmsg &&
	    nla_put_u64_64bit(msg, DEVLINK_ATTR_HEALTH_REPORTER_DUMP_TS,
			      jअगरfies_to_msecs(reporter->dump_ts),
			      DEVLINK_ATTR_PAD))
		जाओ reporter_nest_cancel;
	अगर (reporter->dump_fmsg &&
	    nla_put_u64_64bit(msg, DEVLINK_ATTR_HEALTH_REPORTER_DUMP_TS_NS,
			      reporter->dump_real_ts, DEVLINK_ATTR_PAD))
		जाओ reporter_nest_cancel;
	अगर (reporter->ops->dump &&
	    nla_put_u8(msg, DEVLINK_ATTR_HEALTH_REPORTER_AUTO_DUMP,
		       reporter->स्वतः_dump))
		जाओ reporter_nest_cancel;

	nla_nest_end(msg, reporter_attr);
	genlmsg_end(msg, hdr);
	वापस 0;

reporter_nest_cancel:
	nla_nest_end(msg, reporter_attr);
genlmsg_cancel:
	genlmsg_cancel(msg, hdr);
	वापस -EMSGSIZE;
पूर्ण

अटल व्योम devlink_recover_notअगरy(काष्ठा devlink_health_reporter *reporter,
				   क्रमागत devlink_command cmd)
अणु
	काष्ठा sk_buff *msg;
	पूर्णांक err;

	WARN_ON(cmd != DEVLINK_CMD_HEALTH_REPORTER_RECOVER);

	msg = nlmsg_new(NLMSG_DEFAULT_SIZE, GFP_KERNEL);
	अगर (!msg)
		वापस;

	err = devlink_nl_health_reporter_fill(msg, reporter->devlink,
					      reporter, cmd, 0, 0, 0);
	अगर (err) अणु
		nlmsg_मुक्त(msg);
		वापस;
	पूर्ण

	genlmsg_multicast_netns(&devlink_nl_family,
				devlink_net(reporter->devlink),
				msg, 0, DEVLINK_MCGRP_CONFIG, GFP_KERNEL);
पूर्ण

व्योम
devlink_health_reporter_recovery_करोne(काष्ठा devlink_health_reporter *reporter)
अणु
	reporter->recovery_count++;
	reporter->last_recovery_ts = jअगरfies;
पूर्ण
EXPORT_SYMBOL_GPL(devlink_health_reporter_recovery_करोne);

अटल पूर्णांक
devlink_health_reporter_recover(काष्ठा devlink_health_reporter *reporter,
				व्योम *priv_ctx, काष्ठा netlink_ext_ack *extack)
अणु
	पूर्णांक err;

	अगर (reporter->health_state == DEVLINK_HEALTH_REPORTER_STATE_HEALTHY)
		वापस 0;

	अगर (!reporter->ops->recover)
		वापस -EOPNOTSUPP;

	err = reporter->ops->recover(reporter, priv_ctx, extack);
	अगर (err)
		वापस err;

	devlink_health_reporter_recovery_करोne(reporter);
	reporter->health_state = DEVLINK_HEALTH_REPORTER_STATE_HEALTHY;
	devlink_recover_notअगरy(reporter, DEVLINK_CMD_HEALTH_REPORTER_RECOVER);

	वापस 0;
पूर्ण

अटल व्योम
devlink_health_dump_clear(काष्ठा devlink_health_reporter *reporter)
अणु
	अगर (!reporter->dump_fmsg)
		वापस;
	devlink_fmsg_मुक्त(reporter->dump_fmsg);
	reporter->dump_fmsg = शून्य;
पूर्ण

अटल पूर्णांक devlink_health_करो_dump(काष्ठा devlink_health_reporter *reporter,
				  व्योम *priv_ctx,
				  काष्ठा netlink_ext_ack *extack)
अणु
	पूर्णांक err;

	अगर (!reporter->ops->dump)
		वापस 0;

	अगर (reporter->dump_fmsg)
		वापस 0;

	reporter->dump_fmsg = devlink_fmsg_alloc();
	अगर (!reporter->dump_fmsg) अणु
		err = -ENOMEM;
		वापस err;
	पूर्ण

	err = devlink_fmsg_obj_nest_start(reporter->dump_fmsg);
	अगर (err)
		जाओ dump_err;

	err = reporter->ops->dump(reporter, reporter->dump_fmsg,
				  priv_ctx, extack);
	अगर (err)
		जाओ dump_err;

	err = devlink_fmsg_obj_nest_end(reporter->dump_fmsg);
	अगर (err)
		जाओ dump_err;

	reporter->dump_ts = jअगरfies;
	reporter->dump_real_ts = kसमय_get_real_ns();

	वापस 0;

dump_err:
	devlink_health_dump_clear(reporter);
	वापस err;
पूर्ण

पूर्णांक devlink_health_report(काष्ठा devlink_health_reporter *reporter,
			  स्थिर अक्षर *msg, व्योम *priv_ctx)
अणु
	क्रमागत devlink_health_reporter_state prev_health_state;
	काष्ठा devlink *devlink = reporter->devlink;
	अचिन्हित दीर्घ recover_ts_threshold;

	/* ग_लिखो a log message of the current error */
	WARN_ON(!msg);
	trace_devlink_health_report(devlink, reporter->ops->name, msg);
	reporter->error_count++;
	prev_health_state = reporter->health_state;
	reporter->health_state = DEVLINK_HEALTH_REPORTER_STATE_ERROR;
	devlink_recover_notअगरy(reporter, DEVLINK_CMD_HEALTH_REPORTER_RECOVER);

	/* पात अगर the previous error wasn't recovered */
	recover_ts_threshold = reporter->last_recovery_ts +
			       msecs_to_jअगरfies(reporter->graceful_period);
	अगर (reporter->स्वतः_recover &&
	    (prev_health_state != DEVLINK_HEALTH_REPORTER_STATE_HEALTHY ||
	     (reporter->last_recovery_ts && reporter->recovery_count &&
	      समय_is_after_jअगरfies(recover_ts_threshold)))) अणु
		trace_devlink_health_recover_पातed(devlink,
						     reporter->ops->name,
						     reporter->health_state,
						     jअगरfies -
						     reporter->last_recovery_ts);
		वापस -ECANCELED;
	पूर्ण

	reporter->health_state = DEVLINK_HEALTH_REPORTER_STATE_ERROR;

	अगर (reporter->स्वतः_dump) अणु
		mutex_lock(&reporter->dump_lock);
		/* store current dump of current error, क्रम later analysis */
		devlink_health_करो_dump(reporter, priv_ctx, शून्य);
		mutex_unlock(&reporter->dump_lock);
	पूर्ण

	अगर (reporter->स्वतः_recover)
		वापस devlink_health_reporter_recover(reporter,
						       priv_ctx, शून्य);

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(devlink_health_report);

अटल काष्ठा devlink_health_reporter *
devlink_health_reporter_get_from_attrs(काष्ठा devlink *devlink,
				       काष्ठा nlattr **attrs)
अणु
	काष्ठा devlink_health_reporter *reporter;
	काष्ठा devlink_port *devlink_port;
	अक्षर *reporter_name;

	अगर (!attrs[DEVLINK_ATTR_HEALTH_REPORTER_NAME])
		वापस शून्य;

	reporter_name = nla_data(attrs[DEVLINK_ATTR_HEALTH_REPORTER_NAME]);
	devlink_port = devlink_port_get_from_attrs(devlink, attrs);
	अगर (IS_ERR(devlink_port)) अणु
		mutex_lock(&devlink->reporters_lock);
		reporter = devlink_health_reporter_find_by_name(devlink, reporter_name);
		अगर (reporter)
			refcount_inc(&reporter->refcount);
		mutex_unlock(&devlink->reporters_lock);
	पूर्ण अन्यथा अणु
		mutex_lock(&devlink_port->reporters_lock);
		reporter = devlink_port_health_reporter_find_by_name(devlink_port, reporter_name);
		अगर (reporter)
			refcount_inc(&reporter->refcount);
		mutex_unlock(&devlink_port->reporters_lock);
	पूर्ण

	वापस reporter;
पूर्ण

अटल काष्ठा devlink_health_reporter *
devlink_health_reporter_get_from_info(काष्ठा devlink *devlink,
				      काष्ठा genl_info *info)
अणु
	वापस devlink_health_reporter_get_from_attrs(devlink, info->attrs);
पूर्ण

अटल काष्ठा devlink_health_reporter *
devlink_health_reporter_get_from_cb(काष्ठा netlink_callback *cb)
अणु
	स्थिर काष्ठा genl_dumpit_info *info = genl_dumpit_info(cb);
	काष्ठा devlink_health_reporter *reporter;
	काष्ठा nlattr **attrs = info->attrs;
	काष्ठा devlink *devlink;

	mutex_lock(&devlink_mutex);
	devlink = devlink_get_from_attrs(sock_net(cb->skb->sk), attrs);
	अगर (IS_ERR(devlink))
		जाओ unlock;

	reporter = devlink_health_reporter_get_from_attrs(devlink, attrs);
	mutex_unlock(&devlink_mutex);
	वापस reporter;
unlock:
	mutex_unlock(&devlink_mutex);
	वापस शून्य;
पूर्ण

व्योम
devlink_health_reporter_state_update(काष्ठा devlink_health_reporter *reporter,
				     क्रमागत devlink_health_reporter_state state)
अणु
	अगर (WARN_ON(state != DEVLINK_HEALTH_REPORTER_STATE_HEALTHY &&
		    state != DEVLINK_HEALTH_REPORTER_STATE_ERROR))
		वापस;

	अगर (reporter->health_state == state)
		वापस;

	reporter->health_state = state;
	trace_devlink_health_reporter_state_update(reporter->devlink,
						   reporter->ops->name, state);
	devlink_recover_notअगरy(reporter, DEVLINK_CMD_HEALTH_REPORTER_RECOVER);
पूर्ण
EXPORT_SYMBOL_GPL(devlink_health_reporter_state_update);

अटल पूर्णांक devlink_nl_cmd_health_reporter_get_करोit(काष्ठा sk_buff *skb,
						   काष्ठा genl_info *info)
अणु
	काष्ठा devlink *devlink = info->user_ptr[0];
	काष्ठा devlink_health_reporter *reporter;
	काष्ठा sk_buff *msg;
	पूर्णांक err;

	reporter = devlink_health_reporter_get_from_info(devlink, info);
	अगर (!reporter)
		वापस -EINVAL;

	msg = nlmsg_new(NLMSG_DEFAULT_SIZE, GFP_KERNEL);
	अगर (!msg) अणु
		err = -ENOMEM;
		जाओ out;
	पूर्ण

	err = devlink_nl_health_reporter_fill(msg, devlink, reporter,
					      DEVLINK_CMD_HEALTH_REPORTER_GET,
					      info->snd_portid, info->snd_seq,
					      0);
	अगर (err) अणु
		nlmsg_मुक्त(msg);
		जाओ out;
	पूर्ण

	err = genlmsg_reply(msg, info);
out:
	devlink_health_reporter_put(reporter);
	वापस err;
पूर्ण

अटल पूर्णांक
devlink_nl_cmd_health_reporter_get_dumpit(काष्ठा sk_buff *msg,
					  काष्ठा netlink_callback *cb)
अणु
	काष्ठा devlink_health_reporter *reporter;
	काष्ठा devlink_port *port;
	काष्ठा devlink *devlink;
	पूर्णांक start = cb->args[0];
	पूर्णांक idx = 0;
	पूर्णांक err;

	mutex_lock(&devlink_mutex);
	list_क्रम_each_entry(devlink, &devlink_list, list) अणु
		अगर (!net_eq(devlink_net(devlink), sock_net(msg->sk)))
			जारी;
		mutex_lock(&devlink->reporters_lock);
		list_क्रम_each_entry(reporter, &devlink->reporter_list,
				    list) अणु
			अगर (idx < start) अणु
				idx++;
				जारी;
			पूर्ण
			err = devlink_nl_health_reporter_fill(msg, devlink,
							      reporter,
							      DEVLINK_CMD_HEALTH_REPORTER_GET,
							      NETLINK_CB(cb->skb).portid,
							      cb->nlh->nlmsg_seq,
							      NLM_F_MULTI);
			अगर (err) अणु
				mutex_unlock(&devlink->reporters_lock);
				जाओ out;
			पूर्ण
			idx++;
		पूर्ण
		mutex_unlock(&devlink->reporters_lock);
	पूर्ण

	list_क्रम_each_entry(devlink, &devlink_list, list) अणु
		अगर (!net_eq(devlink_net(devlink), sock_net(msg->sk)))
			जारी;
		mutex_lock(&devlink->lock);
		list_क्रम_each_entry(port, &devlink->port_list, list) अणु
			mutex_lock(&port->reporters_lock);
			list_क्रम_each_entry(reporter, &port->reporter_list, list) अणु
				अगर (idx < start) अणु
					idx++;
					जारी;
				पूर्ण
				err = devlink_nl_health_reporter_fill(msg, devlink, reporter,
								      DEVLINK_CMD_HEALTH_REPORTER_GET,
								      NETLINK_CB(cb->skb).portid,
								      cb->nlh->nlmsg_seq,
								      NLM_F_MULTI);
				अगर (err) अणु
					mutex_unlock(&port->reporters_lock);
					mutex_unlock(&devlink->lock);
					जाओ out;
				पूर्ण
				idx++;
			पूर्ण
			mutex_unlock(&port->reporters_lock);
		पूर्ण
		mutex_unlock(&devlink->lock);
	पूर्ण
out:
	mutex_unlock(&devlink_mutex);

	cb->args[0] = idx;
	वापस msg->len;
पूर्ण

अटल पूर्णांक
devlink_nl_cmd_health_reporter_set_करोit(काष्ठा sk_buff *skb,
					काष्ठा genl_info *info)
अणु
	काष्ठा devlink *devlink = info->user_ptr[0];
	काष्ठा devlink_health_reporter *reporter;
	पूर्णांक err;

	reporter = devlink_health_reporter_get_from_info(devlink, info);
	अगर (!reporter)
		वापस -EINVAL;

	अगर (!reporter->ops->recover &&
	    (info->attrs[DEVLINK_ATTR_HEALTH_REPORTER_GRACEFUL_PERIOD] ||
	     info->attrs[DEVLINK_ATTR_HEALTH_REPORTER_AUTO_RECOVER])) अणु
		err = -EOPNOTSUPP;
		जाओ out;
	पूर्ण
	अगर (!reporter->ops->dump &&
	    info->attrs[DEVLINK_ATTR_HEALTH_REPORTER_AUTO_DUMP]) अणु
		err = -EOPNOTSUPP;
		जाओ out;
	पूर्ण

	अगर (info->attrs[DEVLINK_ATTR_HEALTH_REPORTER_GRACEFUL_PERIOD])
		reporter->graceful_period =
			nla_get_u64(info->attrs[DEVLINK_ATTR_HEALTH_REPORTER_GRACEFUL_PERIOD]);

	अगर (info->attrs[DEVLINK_ATTR_HEALTH_REPORTER_AUTO_RECOVER])
		reporter->स्वतः_recover =
			nla_get_u8(info->attrs[DEVLINK_ATTR_HEALTH_REPORTER_AUTO_RECOVER]);

	अगर (info->attrs[DEVLINK_ATTR_HEALTH_REPORTER_AUTO_DUMP])
		reporter->स्वतः_dump =
		nla_get_u8(info->attrs[DEVLINK_ATTR_HEALTH_REPORTER_AUTO_DUMP]);

	devlink_health_reporter_put(reporter);
	वापस 0;
out:
	devlink_health_reporter_put(reporter);
	वापस err;
पूर्ण

अटल पूर्णांक devlink_nl_cmd_health_reporter_recover_करोit(काष्ठा sk_buff *skb,
						       काष्ठा genl_info *info)
अणु
	काष्ठा devlink *devlink = info->user_ptr[0];
	काष्ठा devlink_health_reporter *reporter;
	पूर्णांक err;

	reporter = devlink_health_reporter_get_from_info(devlink, info);
	अगर (!reporter)
		वापस -EINVAL;

	err = devlink_health_reporter_recover(reporter, शून्य, info->extack);

	devlink_health_reporter_put(reporter);
	वापस err;
पूर्ण

अटल पूर्णांक devlink_nl_cmd_health_reporter_diagnose_करोit(काष्ठा sk_buff *skb,
							काष्ठा genl_info *info)
अणु
	काष्ठा devlink *devlink = info->user_ptr[0];
	काष्ठा devlink_health_reporter *reporter;
	काष्ठा devlink_fmsg *fmsg;
	पूर्णांक err;

	reporter = devlink_health_reporter_get_from_info(devlink, info);
	अगर (!reporter)
		वापस -EINVAL;

	अगर (!reporter->ops->diagnose) अणु
		devlink_health_reporter_put(reporter);
		वापस -EOPNOTSUPP;
	पूर्ण

	fmsg = devlink_fmsg_alloc();
	अगर (!fmsg) अणु
		devlink_health_reporter_put(reporter);
		वापस -ENOMEM;
	पूर्ण

	err = devlink_fmsg_obj_nest_start(fmsg);
	अगर (err)
		जाओ out;

	err = reporter->ops->diagnose(reporter, fmsg, info->extack);
	अगर (err)
		जाओ out;

	err = devlink_fmsg_obj_nest_end(fmsg);
	अगर (err)
		जाओ out;

	err = devlink_fmsg_snd(fmsg, info,
			       DEVLINK_CMD_HEALTH_REPORTER_DIAGNOSE, 0);

out:
	devlink_fmsg_मुक्त(fmsg);
	devlink_health_reporter_put(reporter);
	वापस err;
पूर्ण

अटल पूर्णांक
devlink_nl_cmd_health_reporter_dump_get_dumpit(काष्ठा sk_buff *skb,
					       काष्ठा netlink_callback *cb)
अणु
	काष्ठा devlink_health_reporter *reporter;
	u64 start = cb->args[0];
	पूर्णांक err;

	reporter = devlink_health_reporter_get_from_cb(cb);
	अगर (!reporter)
		वापस -EINVAL;

	अगर (!reporter->ops->dump) अणु
		err = -EOPNOTSUPP;
		जाओ out;
	पूर्ण
	mutex_lock(&reporter->dump_lock);
	अगर (!start) अणु
		err = devlink_health_करो_dump(reporter, शून्य, cb->extack);
		अगर (err)
			जाओ unlock;
		cb->args[1] = reporter->dump_ts;
	पूर्ण
	अगर (!reporter->dump_fmsg || cb->args[1] != reporter->dump_ts) अणु
		NL_SET_ERR_MSG_MOD(cb->extack, "Dump trampled, please retry");
		err = -EAGAIN;
		जाओ unlock;
	पूर्ण

	err = devlink_fmsg_dumpit(reporter->dump_fmsg, skb, cb,
				  DEVLINK_CMD_HEALTH_REPORTER_DUMP_GET);
unlock:
	mutex_unlock(&reporter->dump_lock);
out:
	devlink_health_reporter_put(reporter);
	वापस err;
पूर्ण

अटल पूर्णांक
devlink_nl_cmd_health_reporter_dump_clear_करोit(काष्ठा sk_buff *skb,
					       काष्ठा genl_info *info)
अणु
	काष्ठा devlink *devlink = info->user_ptr[0];
	काष्ठा devlink_health_reporter *reporter;

	reporter = devlink_health_reporter_get_from_info(devlink, info);
	अगर (!reporter)
		वापस -EINVAL;

	अगर (!reporter->ops->dump) अणु
		devlink_health_reporter_put(reporter);
		वापस -EOPNOTSUPP;
	पूर्ण

	mutex_lock(&reporter->dump_lock);
	devlink_health_dump_clear(reporter);
	mutex_unlock(&reporter->dump_lock);
	devlink_health_reporter_put(reporter);
	वापस 0;
पूर्ण

अटल पूर्णांक devlink_nl_cmd_health_reporter_test_करोit(काष्ठा sk_buff *skb,
						    काष्ठा genl_info *info)
अणु
	काष्ठा devlink *devlink = info->user_ptr[0];
	काष्ठा devlink_health_reporter *reporter;
	पूर्णांक err;

	reporter = devlink_health_reporter_get_from_info(devlink, info);
	अगर (!reporter)
		वापस -EINVAL;

	अगर (!reporter->ops->test) अणु
		devlink_health_reporter_put(reporter);
		वापस -EOPNOTSUPP;
	पूर्ण

	err = reporter->ops->test(reporter, info->extack);

	devlink_health_reporter_put(reporter);
	वापस err;
पूर्ण

काष्ठा devlink_stats अणु
	u64 rx_bytes;
	u64 rx_packets;
	काष्ठा u64_stats_sync syncp;
पूर्ण;

/**
 * काष्ठा devlink_trap_policer_item - Packet trap policer attributes.
 * @policer: Immutable packet trap policer attributes.
 * @rate: Rate in packets / sec.
 * @burst: Burst size in packets.
 * @list: trap_policer_list member.
 *
 * Describes packet trap policer attributes. Created by devlink during trap
 * policer registration.
 */
काष्ठा devlink_trap_policer_item अणु
	स्थिर काष्ठा devlink_trap_policer *policer;
	u64 rate;
	u64 burst;
	काष्ठा list_head list;
पूर्ण;

/**
 * काष्ठा devlink_trap_group_item - Packet trap group attributes.
 * @group: Immutable packet trap group attributes.
 * @policer_item: Associated policer item. Can be शून्य.
 * @list: trap_group_list member.
 * @stats: Trap group statistics.
 *
 * Describes packet trap group attributes. Created by devlink during trap
 * group registration.
 */
काष्ठा devlink_trap_group_item अणु
	स्थिर काष्ठा devlink_trap_group *group;
	काष्ठा devlink_trap_policer_item *policer_item;
	काष्ठा list_head list;
	काष्ठा devlink_stats __percpu *stats;
पूर्ण;

/**
 * काष्ठा devlink_trap_item - Packet trap attributes.
 * @trap: Immutable packet trap attributes.
 * @group_item: Associated group item.
 * @list: trap_list member.
 * @action: Trap action.
 * @stats: Trap statistics.
 * @priv: Driver निजी inक्रमmation.
 *
 * Describes both mutable and immutable packet trap attributes. Created by
 * devlink during trap registration and used क्रम all trap related operations.
 */
काष्ठा devlink_trap_item अणु
	स्थिर काष्ठा devlink_trap *trap;
	काष्ठा devlink_trap_group_item *group_item;
	काष्ठा list_head list;
	क्रमागत devlink_trap_action action;
	काष्ठा devlink_stats __percpu *stats;
	व्योम *priv;
पूर्ण;

अटल काष्ठा devlink_trap_policer_item *
devlink_trap_policer_item_lookup(काष्ठा devlink *devlink, u32 id)
अणु
	काष्ठा devlink_trap_policer_item *policer_item;

	list_क्रम_each_entry(policer_item, &devlink->trap_policer_list, list) अणु
		अगर (policer_item->policer->id == id)
			वापस policer_item;
	पूर्ण

	वापस शून्य;
पूर्ण

अटल काष्ठा devlink_trap_item *
devlink_trap_item_lookup(काष्ठा devlink *devlink, स्थिर अक्षर *name)
अणु
	काष्ठा devlink_trap_item *trap_item;

	list_क्रम_each_entry(trap_item, &devlink->trap_list, list) अणु
		अगर (!म_भेद(trap_item->trap->name, name))
			वापस trap_item;
	पूर्ण

	वापस शून्य;
पूर्ण

अटल काष्ठा devlink_trap_item *
devlink_trap_item_get_from_info(काष्ठा devlink *devlink,
				काष्ठा genl_info *info)
अणु
	काष्ठा nlattr *attr;

	अगर (!info->attrs[DEVLINK_ATTR_TRAP_NAME])
		वापस शून्य;
	attr = info->attrs[DEVLINK_ATTR_TRAP_NAME];

	वापस devlink_trap_item_lookup(devlink, nla_data(attr));
पूर्ण

अटल पूर्णांक
devlink_trap_action_get_from_info(काष्ठा genl_info *info,
				  क्रमागत devlink_trap_action *p_trap_action)
अणु
	u8 val;

	val = nla_get_u8(info->attrs[DEVLINK_ATTR_TRAP_ACTION]);
	चयन (val) अणु
	हाल DEVLINK_TRAP_ACTION_DROP:
	हाल DEVLINK_TRAP_ACTION_TRAP:
	हाल DEVLINK_TRAP_ACTION_MIRROR:
		*p_trap_action = val;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक devlink_trap_metadata_put(काष्ठा sk_buff *msg,
				     स्थिर काष्ठा devlink_trap *trap)
अणु
	काष्ठा nlattr *attr;

	attr = nla_nest_start(msg, DEVLINK_ATTR_TRAP_METADATA);
	अगर (!attr)
		वापस -EMSGSIZE;

	अगर ((trap->metadata_cap & DEVLINK_TRAP_METADATA_TYPE_F_IN_PORT) &&
	    nla_put_flag(msg, DEVLINK_ATTR_TRAP_METADATA_TYPE_IN_PORT))
		जाओ nla_put_failure;
	अगर ((trap->metadata_cap & DEVLINK_TRAP_METADATA_TYPE_F_FA_COOKIE) &&
	    nla_put_flag(msg, DEVLINK_ATTR_TRAP_METADATA_TYPE_FA_COOKIE))
		जाओ nla_put_failure;

	nla_nest_end(msg, attr);

	वापस 0;

nla_put_failure:
	nla_nest_cancel(msg, attr);
	वापस -EMSGSIZE;
पूर्ण

अटल व्योम devlink_trap_stats_पढ़ो(काष्ठा devlink_stats __percpu *trap_stats,
				    काष्ठा devlink_stats *stats)
अणु
	पूर्णांक i;

	स_रखो(stats, 0, माप(*stats));
	क्रम_each_possible_cpu(i) अणु
		काष्ठा devlink_stats *cpu_stats;
		u64 rx_packets, rx_bytes;
		अचिन्हित पूर्णांक start;

		cpu_stats = per_cpu_ptr(trap_stats, i);
		करो अणु
			start = u64_stats_fetch_begin_irq(&cpu_stats->syncp);
			rx_packets = cpu_stats->rx_packets;
			rx_bytes = cpu_stats->rx_bytes;
		पूर्ण जबतक (u64_stats_fetch_retry_irq(&cpu_stats->syncp, start));

		stats->rx_packets += rx_packets;
		stats->rx_bytes += rx_bytes;
	पूर्ण
पूर्ण

अटल पूर्णांक devlink_trap_stats_put(काष्ठा sk_buff *msg,
				  काष्ठा devlink_stats __percpu *trap_stats)
अणु
	काष्ठा devlink_stats stats;
	काष्ठा nlattr *attr;

	devlink_trap_stats_पढ़ो(trap_stats, &stats);

	attr = nla_nest_start(msg, DEVLINK_ATTR_STATS);
	अगर (!attr)
		वापस -EMSGSIZE;

	अगर (nla_put_u64_64bit(msg, DEVLINK_ATTR_STATS_RX_PACKETS,
			      stats.rx_packets, DEVLINK_ATTR_PAD))
		जाओ nla_put_failure;

	अगर (nla_put_u64_64bit(msg, DEVLINK_ATTR_STATS_RX_BYTES,
			      stats.rx_bytes, DEVLINK_ATTR_PAD))
		जाओ nla_put_failure;

	nla_nest_end(msg, attr);

	वापस 0;

nla_put_failure:
	nla_nest_cancel(msg, attr);
	वापस -EMSGSIZE;
पूर्ण

अटल पूर्णांक devlink_nl_trap_fill(काष्ठा sk_buff *msg, काष्ठा devlink *devlink,
				स्थिर काष्ठा devlink_trap_item *trap_item,
				क्रमागत devlink_command cmd, u32 portid, u32 seq,
				पूर्णांक flags)
अणु
	काष्ठा devlink_trap_group_item *group_item = trap_item->group_item;
	व्योम *hdr;
	पूर्णांक err;

	hdr = genlmsg_put(msg, portid, seq, &devlink_nl_family, flags, cmd);
	अगर (!hdr)
		वापस -EMSGSIZE;

	अगर (devlink_nl_put_handle(msg, devlink))
		जाओ nla_put_failure;

	अगर (nla_put_string(msg, DEVLINK_ATTR_TRAP_GROUP_NAME,
			   group_item->group->name))
		जाओ nla_put_failure;

	अगर (nla_put_string(msg, DEVLINK_ATTR_TRAP_NAME, trap_item->trap->name))
		जाओ nla_put_failure;

	अगर (nla_put_u8(msg, DEVLINK_ATTR_TRAP_TYPE, trap_item->trap->type))
		जाओ nla_put_failure;

	अगर (trap_item->trap->generic &&
	    nla_put_flag(msg, DEVLINK_ATTR_TRAP_GENERIC))
		जाओ nla_put_failure;

	अगर (nla_put_u8(msg, DEVLINK_ATTR_TRAP_ACTION, trap_item->action))
		जाओ nla_put_failure;

	err = devlink_trap_metadata_put(msg, trap_item->trap);
	अगर (err)
		जाओ nla_put_failure;

	err = devlink_trap_stats_put(msg, trap_item->stats);
	अगर (err)
		जाओ nla_put_failure;

	genlmsg_end(msg, hdr);

	वापस 0;

nla_put_failure:
	genlmsg_cancel(msg, hdr);
	वापस -EMSGSIZE;
पूर्ण

अटल पूर्णांक devlink_nl_cmd_trap_get_करोit(काष्ठा sk_buff *skb,
					काष्ठा genl_info *info)
अणु
	काष्ठा netlink_ext_ack *extack = info->extack;
	काष्ठा devlink *devlink = info->user_ptr[0];
	काष्ठा devlink_trap_item *trap_item;
	काष्ठा sk_buff *msg;
	पूर्णांक err;

	अगर (list_empty(&devlink->trap_list))
		वापस -EOPNOTSUPP;

	trap_item = devlink_trap_item_get_from_info(devlink, info);
	अगर (!trap_item) अणु
		NL_SET_ERR_MSG_MOD(extack, "Device did not register this trap");
		वापस -ENOENT;
	पूर्ण

	msg = nlmsg_new(NLMSG_DEFAULT_SIZE, GFP_KERNEL);
	अगर (!msg)
		वापस -ENOMEM;

	err = devlink_nl_trap_fill(msg, devlink, trap_item,
				   DEVLINK_CMD_TRAP_NEW, info->snd_portid,
				   info->snd_seq, 0);
	अगर (err)
		जाओ err_trap_fill;

	वापस genlmsg_reply(msg, info);

err_trap_fill:
	nlmsg_मुक्त(msg);
	वापस err;
पूर्ण

अटल पूर्णांक devlink_nl_cmd_trap_get_dumpit(काष्ठा sk_buff *msg,
					  काष्ठा netlink_callback *cb)
अणु
	काष्ठा devlink_trap_item *trap_item;
	काष्ठा devlink *devlink;
	पूर्णांक start = cb->args[0];
	पूर्णांक idx = 0;
	पूर्णांक err;

	mutex_lock(&devlink_mutex);
	list_क्रम_each_entry(devlink, &devlink_list, list) अणु
		अगर (!net_eq(devlink_net(devlink), sock_net(msg->sk)))
			जारी;
		mutex_lock(&devlink->lock);
		list_क्रम_each_entry(trap_item, &devlink->trap_list, list) अणु
			अगर (idx < start) अणु
				idx++;
				जारी;
			पूर्ण
			err = devlink_nl_trap_fill(msg, devlink, trap_item,
						   DEVLINK_CMD_TRAP_NEW,
						   NETLINK_CB(cb->skb).portid,
						   cb->nlh->nlmsg_seq,
						   NLM_F_MULTI);
			अगर (err) अणु
				mutex_unlock(&devlink->lock);
				जाओ out;
			पूर्ण
			idx++;
		पूर्ण
		mutex_unlock(&devlink->lock);
	पूर्ण
out:
	mutex_unlock(&devlink_mutex);

	cb->args[0] = idx;
	वापस msg->len;
पूर्ण

अटल पूर्णांक __devlink_trap_action_set(काष्ठा devlink *devlink,
				     काष्ठा devlink_trap_item *trap_item,
				     क्रमागत devlink_trap_action trap_action,
				     काष्ठा netlink_ext_ack *extack)
अणु
	पूर्णांक err;

	अगर (trap_item->action != trap_action &&
	    trap_item->trap->type != DEVLINK_TRAP_TYPE_DROP) अणु
		NL_SET_ERR_MSG_MOD(extack, "Cannot change action of non-drop traps. Skipping");
		वापस 0;
	पूर्ण

	err = devlink->ops->trap_action_set(devlink, trap_item->trap,
					    trap_action, extack);
	अगर (err)
		वापस err;

	trap_item->action = trap_action;

	वापस 0;
पूर्ण

अटल पूर्णांक devlink_trap_action_set(काष्ठा devlink *devlink,
				   काष्ठा devlink_trap_item *trap_item,
				   काष्ठा genl_info *info)
अणु
	क्रमागत devlink_trap_action trap_action;
	पूर्णांक err;

	अगर (!info->attrs[DEVLINK_ATTR_TRAP_ACTION])
		वापस 0;

	err = devlink_trap_action_get_from_info(info, &trap_action);
	अगर (err) अणु
		NL_SET_ERR_MSG_MOD(info->extack, "Invalid trap action");
		वापस -EINVAL;
	पूर्ण

	वापस __devlink_trap_action_set(devlink, trap_item, trap_action,
					 info->extack);
पूर्ण

अटल पूर्णांक devlink_nl_cmd_trap_set_करोit(काष्ठा sk_buff *skb,
					काष्ठा genl_info *info)
अणु
	काष्ठा netlink_ext_ack *extack = info->extack;
	काष्ठा devlink *devlink = info->user_ptr[0];
	काष्ठा devlink_trap_item *trap_item;

	अगर (list_empty(&devlink->trap_list))
		वापस -EOPNOTSUPP;

	trap_item = devlink_trap_item_get_from_info(devlink, info);
	अगर (!trap_item) अणु
		NL_SET_ERR_MSG_MOD(extack, "Device did not register this trap");
		वापस -ENOENT;
	पूर्ण

	वापस devlink_trap_action_set(devlink, trap_item, info);
पूर्ण

अटल काष्ठा devlink_trap_group_item *
devlink_trap_group_item_lookup(काष्ठा devlink *devlink, स्थिर अक्षर *name)
अणु
	काष्ठा devlink_trap_group_item *group_item;

	list_क्रम_each_entry(group_item, &devlink->trap_group_list, list) अणु
		अगर (!म_भेद(group_item->group->name, name))
			वापस group_item;
	पूर्ण

	वापस शून्य;
पूर्ण

अटल काष्ठा devlink_trap_group_item *
devlink_trap_group_item_lookup_by_id(काष्ठा devlink *devlink, u16 id)
अणु
	काष्ठा devlink_trap_group_item *group_item;

	list_क्रम_each_entry(group_item, &devlink->trap_group_list, list) अणु
		अगर (group_item->group->id == id)
			वापस group_item;
	पूर्ण

	वापस शून्य;
पूर्ण

अटल काष्ठा devlink_trap_group_item *
devlink_trap_group_item_get_from_info(काष्ठा devlink *devlink,
				      काष्ठा genl_info *info)
अणु
	अक्षर *name;

	अगर (!info->attrs[DEVLINK_ATTR_TRAP_GROUP_NAME])
		वापस शून्य;
	name = nla_data(info->attrs[DEVLINK_ATTR_TRAP_GROUP_NAME]);

	वापस devlink_trap_group_item_lookup(devlink, name);
पूर्ण

अटल पूर्णांक
devlink_nl_trap_group_fill(काष्ठा sk_buff *msg, काष्ठा devlink *devlink,
			   स्थिर काष्ठा devlink_trap_group_item *group_item,
			   क्रमागत devlink_command cmd, u32 portid, u32 seq,
			   पूर्णांक flags)
अणु
	व्योम *hdr;
	पूर्णांक err;

	hdr = genlmsg_put(msg, portid, seq, &devlink_nl_family, flags, cmd);
	अगर (!hdr)
		वापस -EMSGSIZE;

	अगर (devlink_nl_put_handle(msg, devlink))
		जाओ nla_put_failure;

	अगर (nla_put_string(msg, DEVLINK_ATTR_TRAP_GROUP_NAME,
			   group_item->group->name))
		जाओ nla_put_failure;

	अगर (group_item->group->generic &&
	    nla_put_flag(msg, DEVLINK_ATTR_TRAP_GENERIC))
		जाओ nla_put_failure;

	अगर (group_item->policer_item &&
	    nla_put_u32(msg, DEVLINK_ATTR_TRAP_POLICER_ID,
			group_item->policer_item->policer->id))
		जाओ nla_put_failure;

	err = devlink_trap_stats_put(msg, group_item->stats);
	अगर (err)
		जाओ nla_put_failure;

	genlmsg_end(msg, hdr);

	वापस 0;

nla_put_failure:
	genlmsg_cancel(msg, hdr);
	वापस -EMSGSIZE;
पूर्ण

अटल पूर्णांक devlink_nl_cmd_trap_group_get_करोit(काष्ठा sk_buff *skb,
					      काष्ठा genl_info *info)
अणु
	काष्ठा netlink_ext_ack *extack = info->extack;
	काष्ठा devlink *devlink = info->user_ptr[0];
	काष्ठा devlink_trap_group_item *group_item;
	काष्ठा sk_buff *msg;
	पूर्णांक err;

	अगर (list_empty(&devlink->trap_group_list))
		वापस -EOPNOTSUPP;

	group_item = devlink_trap_group_item_get_from_info(devlink, info);
	अगर (!group_item) अणु
		NL_SET_ERR_MSG_MOD(extack, "Device did not register this trap group");
		वापस -ENOENT;
	पूर्ण

	msg = nlmsg_new(NLMSG_DEFAULT_SIZE, GFP_KERNEL);
	अगर (!msg)
		वापस -ENOMEM;

	err = devlink_nl_trap_group_fill(msg, devlink, group_item,
					 DEVLINK_CMD_TRAP_GROUP_NEW,
					 info->snd_portid, info->snd_seq, 0);
	अगर (err)
		जाओ err_trap_group_fill;

	वापस genlmsg_reply(msg, info);

err_trap_group_fill:
	nlmsg_मुक्त(msg);
	वापस err;
पूर्ण

अटल पूर्णांक devlink_nl_cmd_trap_group_get_dumpit(काष्ठा sk_buff *msg,
						काष्ठा netlink_callback *cb)
अणु
	क्रमागत devlink_command cmd = DEVLINK_CMD_TRAP_GROUP_NEW;
	काष्ठा devlink_trap_group_item *group_item;
	u32 portid = NETLINK_CB(cb->skb).portid;
	काष्ठा devlink *devlink;
	पूर्णांक start = cb->args[0];
	पूर्णांक idx = 0;
	पूर्णांक err;

	mutex_lock(&devlink_mutex);
	list_क्रम_each_entry(devlink, &devlink_list, list) अणु
		अगर (!net_eq(devlink_net(devlink), sock_net(msg->sk)))
			जारी;
		mutex_lock(&devlink->lock);
		list_क्रम_each_entry(group_item, &devlink->trap_group_list,
				    list) अणु
			अगर (idx < start) अणु
				idx++;
				जारी;
			पूर्ण
			err = devlink_nl_trap_group_fill(msg, devlink,
							 group_item, cmd,
							 portid,
							 cb->nlh->nlmsg_seq,
							 NLM_F_MULTI);
			अगर (err) अणु
				mutex_unlock(&devlink->lock);
				जाओ out;
			पूर्ण
			idx++;
		पूर्ण
		mutex_unlock(&devlink->lock);
	पूर्ण
out:
	mutex_unlock(&devlink_mutex);

	cb->args[0] = idx;
	वापस msg->len;
पूर्ण

अटल पूर्णांक
__devlink_trap_group_action_set(काष्ठा devlink *devlink,
				काष्ठा devlink_trap_group_item *group_item,
				क्रमागत devlink_trap_action trap_action,
				काष्ठा netlink_ext_ack *extack)
अणु
	स्थिर अक्षर *group_name = group_item->group->name;
	काष्ठा devlink_trap_item *trap_item;
	पूर्णांक err;

	अगर (devlink->ops->trap_group_action_set) अणु
		err = devlink->ops->trap_group_action_set(devlink, group_item->group,
							  trap_action, extack);
		अगर (err)
			वापस err;

		list_क्रम_each_entry(trap_item, &devlink->trap_list, list) अणु
			अगर (म_भेद(trap_item->group_item->group->name, group_name))
				जारी;
			अगर (trap_item->action != trap_action &&
			    trap_item->trap->type != DEVLINK_TRAP_TYPE_DROP)
				जारी;
			trap_item->action = trap_action;
		पूर्ण

		वापस 0;
	पूर्ण

	list_क्रम_each_entry(trap_item, &devlink->trap_list, list) अणु
		अगर (म_भेद(trap_item->group_item->group->name, group_name))
			जारी;
		err = __devlink_trap_action_set(devlink, trap_item,
						trap_action, extack);
		अगर (err)
			वापस err;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक
devlink_trap_group_action_set(काष्ठा devlink *devlink,
			      काष्ठा devlink_trap_group_item *group_item,
			      काष्ठा genl_info *info, bool *p_modअगरied)
अणु
	क्रमागत devlink_trap_action trap_action;
	पूर्णांक err;

	अगर (!info->attrs[DEVLINK_ATTR_TRAP_ACTION])
		वापस 0;

	err = devlink_trap_action_get_from_info(info, &trap_action);
	अगर (err) अणु
		NL_SET_ERR_MSG_MOD(info->extack, "Invalid trap action");
		वापस -EINVAL;
	पूर्ण

	err = __devlink_trap_group_action_set(devlink, group_item, trap_action,
					      info->extack);
	अगर (err)
		वापस err;

	*p_modअगरied = true;

	वापस 0;
पूर्ण

अटल पूर्णांक devlink_trap_group_set(काष्ठा devlink *devlink,
				  काष्ठा devlink_trap_group_item *group_item,
				  काष्ठा genl_info *info)
अणु
	काष्ठा devlink_trap_policer_item *policer_item;
	काष्ठा netlink_ext_ack *extack = info->extack;
	स्थिर काष्ठा devlink_trap_policer *policer;
	काष्ठा nlattr **attrs = info->attrs;
	पूर्णांक err;

	अगर (!attrs[DEVLINK_ATTR_TRAP_POLICER_ID])
		वापस 0;

	अगर (!devlink->ops->trap_group_set)
		वापस -EOPNOTSUPP;

	policer_item = group_item->policer_item;
	अगर (attrs[DEVLINK_ATTR_TRAP_POLICER_ID]) अणु
		u32 policer_id;

		policer_id = nla_get_u32(attrs[DEVLINK_ATTR_TRAP_POLICER_ID]);
		policer_item = devlink_trap_policer_item_lookup(devlink,
								policer_id);
		अगर (policer_id && !policer_item) अणु
			NL_SET_ERR_MSG_MOD(extack, "Device did not register this trap policer");
			वापस -ENOENT;
		पूर्ण
	पूर्ण
	policer = policer_item ? policer_item->policer : शून्य;

	err = devlink->ops->trap_group_set(devlink, group_item->group, policer,
					   extack);
	अगर (err)
		वापस err;

	group_item->policer_item = policer_item;

	वापस 0;
पूर्ण

अटल पूर्णांक devlink_nl_cmd_trap_group_set_करोit(काष्ठा sk_buff *skb,
					      काष्ठा genl_info *info)
अणु
	काष्ठा netlink_ext_ack *extack = info->extack;
	काष्ठा devlink *devlink = info->user_ptr[0];
	काष्ठा devlink_trap_group_item *group_item;
	bool modअगरied = false;
	पूर्णांक err;

	अगर (list_empty(&devlink->trap_group_list))
		वापस -EOPNOTSUPP;

	group_item = devlink_trap_group_item_get_from_info(devlink, info);
	अगर (!group_item) अणु
		NL_SET_ERR_MSG_MOD(extack, "Device did not register this trap group");
		वापस -ENOENT;
	पूर्ण

	err = devlink_trap_group_action_set(devlink, group_item, info,
					    &modअगरied);
	अगर (err)
		वापस err;

	err = devlink_trap_group_set(devlink, group_item, info);
	अगर (err)
		जाओ err_trap_group_set;

	वापस 0;

err_trap_group_set:
	अगर (modअगरied)
		NL_SET_ERR_MSG_MOD(extack, "Trap group set failed, but some changes were committed already");
	वापस err;
पूर्ण

अटल काष्ठा devlink_trap_policer_item *
devlink_trap_policer_item_get_from_info(काष्ठा devlink *devlink,
					काष्ठा genl_info *info)
अणु
	u32 id;

	अगर (!info->attrs[DEVLINK_ATTR_TRAP_POLICER_ID])
		वापस शून्य;
	id = nla_get_u32(info->attrs[DEVLINK_ATTR_TRAP_POLICER_ID]);

	वापस devlink_trap_policer_item_lookup(devlink, id);
पूर्ण

अटल पूर्णांक
devlink_trap_policer_stats_put(काष्ठा sk_buff *msg, काष्ठा devlink *devlink,
			       स्थिर काष्ठा devlink_trap_policer *policer)
अणु
	काष्ठा nlattr *attr;
	u64 drops;
	पूर्णांक err;

	अगर (!devlink->ops->trap_policer_counter_get)
		वापस 0;

	err = devlink->ops->trap_policer_counter_get(devlink, policer, &drops);
	अगर (err)
		वापस err;

	attr = nla_nest_start(msg, DEVLINK_ATTR_STATS);
	अगर (!attr)
		वापस -EMSGSIZE;

	अगर (nla_put_u64_64bit(msg, DEVLINK_ATTR_STATS_RX_DROPPED, drops,
			      DEVLINK_ATTR_PAD))
		जाओ nla_put_failure;

	nla_nest_end(msg, attr);

	वापस 0;

nla_put_failure:
	nla_nest_cancel(msg, attr);
	वापस -EMSGSIZE;
पूर्ण

अटल पूर्णांक
devlink_nl_trap_policer_fill(काष्ठा sk_buff *msg, काष्ठा devlink *devlink,
			     स्थिर काष्ठा devlink_trap_policer_item *policer_item,
			     क्रमागत devlink_command cmd, u32 portid, u32 seq,
			     पूर्णांक flags)
अणु
	व्योम *hdr;
	पूर्णांक err;

	hdr = genlmsg_put(msg, portid, seq, &devlink_nl_family, flags, cmd);
	अगर (!hdr)
		वापस -EMSGSIZE;

	अगर (devlink_nl_put_handle(msg, devlink))
		जाओ nla_put_failure;

	अगर (nla_put_u32(msg, DEVLINK_ATTR_TRAP_POLICER_ID,
			policer_item->policer->id))
		जाओ nla_put_failure;

	अगर (nla_put_u64_64bit(msg, DEVLINK_ATTR_TRAP_POLICER_RATE,
			      policer_item->rate, DEVLINK_ATTR_PAD))
		जाओ nla_put_failure;

	अगर (nla_put_u64_64bit(msg, DEVLINK_ATTR_TRAP_POLICER_BURST,
			      policer_item->burst, DEVLINK_ATTR_PAD))
		जाओ nla_put_failure;

	err = devlink_trap_policer_stats_put(msg, devlink,
					     policer_item->policer);
	अगर (err)
		जाओ nla_put_failure;

	genlmsg_end(msg, hdr);

	वापस 0;

nla_put_failure:
	genlmsg_cancel(msg, hdr);
	वापस -EMSGSIZE;
पूर्ण

अटल पूर्णांक devlink_nl_cmd_trap_policer_get_करोit(काष्ठा sk_buff *skb,
						काष्ठा genl_info *info)
अणु
	काष्ठा devlink_trap_policer_item *policer_item;
	काष्ठा netlink_ext_ack *extack = info->extack;
	काष्ठा devlink *devlink = info->user_ptr[0];
	काष्ठा sk_buff *msg;
	पूर्णांक err;

	अगर (list_empty(&devlink->trap_policer_list))
		वापस -EOPNOTSUPP;

	policer_item = devlink_trap_policer_item_get_from_info(devlink, info);
	अगर (!policer_item) अणु
		NL_SET_ERR_MSG_MOD(extack, "Device did not register this trap policer");
		वापस -ENOENT;
	पूर्ण

	msg = nlmsg_new(NLMSG_DEFAULT_SIZE, GFP_KERNEL);
	अगर (!msg)
		वापस -ENOMEM;

	err = devlink_nl_trap_policer_fill(msg, devlink, policer_item,
					   DEVLINK_CMD_TRAP_POLICER_NEW,
					   info->snd_portid, info->snd_seq, 0);
	अगर (err)
		जाओ err_trap_policer_fill;

	वापस genlmsg_reply(msg, info);

err_trap_policer_fill:
	nlmsg_मुक्त(msg);
	वापस err;
पूर्ण

अटल पूर्णांक devlink_nl_cmd_trap_policer_get_dumpit(काष्ठा sk_buff *msg,
						  काष्ठा netlink_callback *cb)
अणु
	क्रमागत devlink_command cmd = DEVLINK_CMD_TRAP_POLICER_NEW;
	काष्ठा devlink_trap_policer_item *policer_item;
	u32 portid = NETLINK_CB(cb->skb).portid;
	काष्ठा devlink *devlink;
	पूर्णांक start = cb->args[0];
	पूर्णांक idx = 0;
	पूर्णांक err;

	mutex_lock(&devlink_mutex);
	list_क्रम_each_entry(devlink, &devlink_list, list) अणु
		अगर (!net_eq(devlink_net(devlink), sock_net(msg->sk)))
			जारी;
		mutex_lock(&devlink->lock);
		list_क्रम_each_entry(policer_item, &devlink->trap_policer_list,
				    list) अणु
			अगर (idx < start) अणु
				idx++;
				जारी;
			पूर्ण
			err = devlink_nl_trap_policer_fill(msg, devlink,
							   policer_item, cmd,
							   portid,
							   cb->nlh->nlmsg_seq,
							   NLM_F_MULTI);
			अगर (err) अणु
				mutex_unlock(&devlink->lock);
				जाओ out;
			पूर्ण
			idx++;
		पूर्ण
		mutex_unlock(&devlink->lock);
	पूर्ण
out:
	mutex_unlock(&devlink_mutex);

	cb->args[0] = idx;
	वापस msg->len;
पूर्ण

अटल पूर्णांक
devlink_trap_policer_set(काष्ठा devlink *devlink,
			 काष्ठा devlink_trap_policer_item *policer_item,
			 काष्ठा genl_info *info)
अणु
	काष्ठा netlink_ext_ack *extack = info->extack;
	काष्ठा nlattr **attrs = info->attrs;
	u64 rate, burst;
	पूर्णांक err;

	rate = policer_item->rate;
	burst = policer_item->burst;

	अगर (attrs[DEVLINK_ATTR_TRAP_POLICER_RATE])
		rate = nla_get_u64(attrs[DEVLINK_ATTR_TRAP_POLICER_RATE]);

	अगर (attrs[DEVLINK_ATTR_TRAP_POLICER_BURST])
		burst = nla_get_u64(attrs[DEVLINK_ATTR_TRAP_POLICER_BURST]);

	अगर (rate < policer_item->policer->min_rate) अणु
		NL_SET_ERR_MSG_MOD(extack, "Policer rate lower than limit");
		वापस -EINVAL;
	पूर्ण

	अगर (rate > policer_item->policer->max_rate) अणु
		NL_SET_ERR_MSG_MOD(extack, "Policer rate higher than limit");
		वापस -EINVAL;
	पूर्ण

	अगर (burst < policer_item->policer->min_burst) अणु
		NL_SET_ERR_MSG_MOD(extack, "Policer burst size lower than limit");
		वापस -EINVAL;
	पूर्ण

	अगर (burst > policer_item->policer->max_burst) अणु
		NL_SET_ERR_MSG_MOD(extack, "Policer burst size higher than limit");
		वापस -EINVAL;
	पूर्ण

	err = devlink->ops->trap_policer_set(devlink, policer_item->policer,
					     rate, burst, info->extack);
	अगर (err)
		वापस err;

	policer_item->rate = rate;
	policer_item->burst = burst;

	वापस 0;
पूर्ण

अटल पूर्णांक devlink_nl_cmd_trap_policer_set_करोit(काष्ठा sk_buff *skb,
						काष्ठा genl_info *info)
अणु
	काष्ठा devlink_trap_policer_item *policer_item;
	काष्ठा netlink_ext_ack *extack = info->extack;
	काष्ठा devlink *devlink = info->user_ptr[0];

	अगर (list_empty(&devlink->trap_policer_list))
		वापस -EOPNOTSUPP;

	अगर (!devlink->ops->trap_policer_set)
		वापस -EOPNOTSUPP;

	policer_item = devlink_trap_policer_item_get_from_info(devlink, info);
	अगर (!policer_item) अणु
		NL_SET_ERR_MSG_MOD(extack, "Device did not register this trap policer");
		वापस -ENOENT;
	पूर्ण

	वापस devlink_trap_policer_set(devlink, policer_item, info);
पूर्ण

अटल स्थिर काष्ठा nla_policy devlink_nl_policy[DEVLINK_ATTR_MAX + 1] = अणु
	[DEVLINK_ATTR_UNSPEC] = अणु .strict_start_type =
		DEVLINK_ATTR_TRAP_POLICER_ID पूर्ण,
	[DEVLINK_ATTR_BUS_NAME] = अणु .type = NLA_NUL_STRING पूर्ण,
	[DEVLINK_ATTR_DEV_NAME] = अणु .type = NLA_NUL_STRING पूर्ण,
	[DEVLINK_ATTR_PORT_INDEX] = अणु .type = NLA_U32 पूर्ण,
	[DEVLINK_ATTR_PORT_TYPE] = NLA_POLICY_RANGE(NLA_U16, DEVLINK_PORT_TYPE_AUTO,
						    DEVLINK_PORT_TYPE_IB),
	[DEVLINK_ATTR_PORT_SPLIT_COUNT] = अणु .type = NLA_U32 पूर्ण,
	[DEVLINK_ATTR_SB_INDEX] = अणु .type = NLA_U32 पूर्ण,
	[DEVLINK_ATTR_SB_POOL_INDEX] = अणु .type = NLA_U16 पूर्ण,
	[DEVLINK_ATTR_SB_POOL_TYPE] = अणु .type = NLA_U8 पूर्ण,
	[DEVLINK_ATTR_SB_POOL_SIZE] = अणु .type = NLA_U32 पूर्ण,
	[DEVLINK_ATTR_SB_POOL_THRESHOLD_TYPE] = अणु .type = NLA_U8 पूर्ण,
	[DEVLINK_ATTR_SB_THRESHOLD] = अणु .type = NLA_U32 पूर्ण,
	[DEVLINK_ATTR_SB_TC_INDEX] = अणु .type = NLA_U16 पूर्ण,
	[DEVLINK_ATTR_ESWITCH_MODE] = NLA_POLICY_RANGE(NLA_U16, DEVLINK_ESWITCH_MODE_LEGACY,
						       DEVLINK_ESWITCH_MODE_SWITCHDEV),
	[DEVLINK_ATTR_ESWITCH_INLINE_MODE] = अणु .type = NLA_U8 पूर्ण,
	[DEVLINK_ATTR_ESWITCH_ENCAP_MODE] = अणु .type = NLA_U8 पूर्ण,
	[DEVLINK_ATTR_DPIPE_TABLE_NAME] = अणु .type = NLA_NUL_STRING पूर्ण,
	[DEVLINK_ATTR_DPIPE_TABLE_COUNTERS_ENABLED] = अणु .type = NLA_U8 पूर्ण,
	[DEVLINK_ATTR_RESOURCE_ID] = अणु .type = NLA_U64पूर्ण,
	[DEVLINK_ATTR_RESOURCE_SIZE] = अणु .type = NLA_U64पूर्ण,
	[DEVLINK_ATTR_PARAM_NAME] = अणु .type = NLA_NUL_STRING पूर्ण,
	[DEVLINK_ATTR_PARAM_TYPE] = अणु .type = NLA_U8 पूर्ण,
	[DEVLINK_ATTR_PARAM_VALUE_CMODE] = अणु .type = NLA_U8 पूर्ण,
	[DEVLINK_ATTR_REGION_NAME] = अणु .type = NLA_NUL_STRING पूर्ण,
	[DEVLINK_ATTR_REGION_SNAPSHOT_ID] = अणु .type = NLA_U32 पूर्ण,
	[DEVLINK_ATTR_REGION_CHUNK_ADDR] = अणु .type = NLA_U64 पूर्ण,
	[DEVLINK_ATTR_REGION_CHUNK_LEN] = अणु .type = NLA_U64 पूर्ण,
	[DEVLINK_ATTR_HEALTH_REPORTER_NAME] = अणु .type = NLA_NUL_STRING पूर्ण,
	[DEVLINK_ATTR_HEALTH_REPORTER_GRACEFUL_PERIOD] = अणु .type = NLA_U64 पूर्ण,
	[DEVLINK_ATTR_HEALTH_REPORTER_AUTO_RECOVER] = अणु .type = NLA_U8 पूर्ण,
	[DEVLINK_ATTR_FLASH_UPDATE_खाता_NAME] = अणु .type = NLA_NUL_STRING पूर्ण,
	[DEVLINK_ATTR_FLASH_UPDATE_COMPONENT] = अणु .type = NLA_NUL_STRING पूर्ण,
	[DEVLINK_ATTR_FLASH_UPDATE_OVERWRITE_MASK] =
		NLA_POLICY_BITFIELD32(DEVLINK_SUPPORTED_FLASH_OVERWRITE_SECTIONS),
	[DEVLINK_ATTR_TRAP_NAME] = अणु .type = NLA_NUL_STRING पूर्ण,
	[DEVLINK_ATTR_TRAP_ACTION] = अणु .type = NLA_U8 पूर्ण,
	[DEVLINK_ATTR_TRAP_GROUP_NAME] = अणु .type = NLA_NUL_STRING पूर्ण,
	[DEVLINK_ATTR_NETNS_PID] = अणु .type = NLA_U32 पूर्ण,
	[DEVLINK_ATTR_NETNS_FD] = अणु .type = NLA_U32 पूर्ण,
	[DEVLINK_ATTR_NETNS_ID] = अणु .type = NLA_U32 पूर्ण,
	[DEVLINK_ATTR_HEALTH_REPORTER_AUTO_DUMP] = अणु .type = NLA_U8 पूर्ण,
	[DEVLINK_ATTR_TRAP_POLICER_ID] = अणु .type = NLA_U32 पूर्ण,
	[DEVLINK_ATTR_TRAP_POLICER_RATE] = अणु .type = NLA_U64 पूर्ण,
	[DEVLINK_ATTR_TRAP_POLICER_BURST] = अणु .type = NLA_U64 पूर्ण,
	[DEVLINK_ATTR_PORT_FUNCTION] = अणु .type = NLA_NESTED पूर्ण,
	[DEVLINK_ATTR_RELOAD_ACTION] = NLA_POLICY_RANGE(NLA_U8, DEVLINK_RELOAD_ACTION_DRIVER_REINIT,
							DEVLINK_RELOAD_ACTION_MAX),
	[DEVLINK_ATTR_RELOAD_LIMITS] = NLA_POLICY_BITFIELD32(DEVLINK_RELOAD_LIMITS_VALID_MASK),
	[DEVLINK_ATTR_PORT_FLAVOUR] = अणु .type = NLA_U16 पूर्ण,
	[DEVLINK_ATTR_PORT_PCI_PF_NUMBER] = अणु .type = NLA_U16 पूर्ण,
	[DEVLINK_ATTR_PORT_PCI_SF_NUMBER] = अणु .type = NLA_U32 पूर्ण,
	[DEVLINK_ATTR_PORT_CONTROLLER_NUMBER] = अणु .type = NLA_U32 पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा genl_small_ops devlink_nl_ops[] = अणु
	अणु
		.cmd = DEVLINK_CMD_GET,
		.validate = GENL_DONT_VALIDATE_STRICT | GENL_DONT_VALIDATE_DUMP,
		.करोit = devlink_nl_cmd_get_करोit,
		.dumpit = devlink_nl_cmd_get_dumpit,
		/* can be retrieved by unprivileged users */
	पूर्ण,
	अणु
		.cmd = DEVLINK_CMD_PORT_GET,
		.validate = GENL_DONT_VALIDATE_STRICT | GENL_DONT_VALIDATE_DUMP,
		.करोit = devlink_nl_cmd_port_get_करोit,
		.dumpit = devlink_nl_cmd_port_get_dumpit,
		.पूर्णांकernal_flags = DEVLINK_NL_FLAG_NEED_PORT,
		/* can be retrieved by unprivileged users */
	पूर्ण,
	अणु
		.cmd = DEVLINK_CMD_PORT_SET,
		.validate = GENL_DONT_VALIDATE_STRICT | GENL_DONT_VALIDATE_DUMP,
		.करोit = devlink_nl_cmd_port_set_करोit,
		.flags = GENL_ADMIN_PERM,
		.पूर्णांकernal_flags = DEVLINK_NL_FLAG_NEED_PORT,
	पूर्ण,
	अणु
		.cmd = DEVLINK_CMD_PORT_SPLIT,
		.validate = GENL_DONT_VALIDATE_STRICT | GENL_DONT_VALIDATE_DUMP,
		.करोit = devlink_nl_cmd_port_split_करोit,
		.flags = GENL_ADMIN_PERM,
		.पूर्णांकernal_flags = DEVLINK_NL_FLAG_NO_LOCK,
	पूर्ण,
	अणु
		.cmd = DEVLINK_CMD_PORT_UNSPLIT,
		.validate = GENL_DONT_VALIDATE_STRICT | GENL_DONT_VALIDATE_DUMP,
		.करोit = devlink_nl_cmd_port_unsplit_करोit,
		.flags = GENL_ADMIN_PERM,
		.पूर्णांकernal_flags = DEVLINK_NL_FLAG_NO_LOCK,
	पूर्ण,
	अणु
		.cmd = DEVLINK_CMD_PORT_NEW,
		.करोit = devlink_nl_cmd_port_new_करोit,
		.flags = GENL_ADMIN_PERM,
		.पूर्णांकernal_flags = DEVLINK_NL_FLAG_NO_LOCK,
	पूर्ण,
	अणु
		.cmd = DEVLINK_CMD_PORT_DEL,
		.करोit = devlink_nl_cmd_port_del_करोit,
		.flags = GENL_ADMIN_PERM,
		.पूर्णांकernal_flags = DEVLINK_NL_FLAG_NO_LOCK,
	पूर्ण,
	अणु
		.cmd = DEVLINK_CMD_SB_GET,
		.validate = GENL_DONT_VALIDATE_STRICT | GENL_DONT_VALIDATE_DUMP,
		.करोit = devlink_nl_cmd_sb_get_करोit,
		.dumpit = devlink_nl_cmd_sb_get_dumpit,
		/* can be retrieved by unprivileged users */
	पूर्ण,
	अणु
		.cmd = DEVLINK_CMD_SB_POOL_GET,
		.validate = GENL_DONT_VALIDATE_STRICT | GENL_DONT_VALIDATE_DUMP,
		.करोit = devlink_nl_cmd_sb_pool_get_करोit,
		.dumpit = devlink_nl_cmd_sb_pool_get_dumpit,
		/* can be retrieved by unprivileged users */
	पूर्ण,
	अणु
		.cmd = DEVLINK_CMD_SB_POOL_SET,
		.validate = GENL_DONT_VALIDATE_STRICT | GENL_DONT_VALIDATE_DUMP,
		.करोit = devlink_nl_cmd_sb_pool_set_करोit,
		.flags = GENL_ADMIN_PERM,
	पूर्ण,
	अणु
		.cmd = DEVLINK_CMD_SB_PORT_POOL_GET,
		.validate = GENL_DONT_VALIDATE_STRICT | GENL_DONT_VALIDATE_DUMP,
		.करोit = devlink_nl_cmd_sb_port_pool_get_करोit,
		.dumpit = devlink_nl_cmd_sb_port_pool_get_dumpit,
		.पूर्णांकernal_flags = DEVLINK_NL_FLAG_NEED_PORT,
		/* can be retrieved by unprivileged users */
	पूर्ण,
	अणु
		.cmd = DEVLINK_CMD_SB_PORT_POOL_SET,
		.validate = GENL_DONT_VALIDATE_STRICT | GENL_DONT_VALIDATE_DUMP,
		.करोit = devlink_nl_cmd_sb_port_pool_set_करोit,
		.flags = GENL_ADMIN_PERM,
		.पूर्णांकernal_flags = DEVLINK_NL_FLAG_NEED_PORT,
	पूर्ण,
	अणु
		.cmd = DEVLINK_CMD_SB_TC_POOL_BIND_GET,
		.validate = GENL_DONT_VALIDATE_STRICT | GENL_DONT_VALIDATE_DUMP,
		.करोit = devlink_nl_cmd_sb_tc_pool_bind_get_करोit,
		.dumpit = devlink_nl_cmd_sb_tc_pool_bind_get_dumpit,
		.पूर्णांकernal_flags = DEVLINK_NL_FLAG_NEED_PORT,
		/* can be retrieved by unprivileged users */
	पूर्ण,
	अणु
		.cmd = DEVLINK_CMD_SB_TC_POOL_BIND_SET,
		.validate = GENL_DONT_VALIDATE_STRICT | GENL_DONT_VALIDATE_DUMP,
		.करोit = devlink_nl_cmd_sb_tc_pool_bind_set_करोit,
		.flags = GENL_ADMIN_PERM,
		.पूर्णांकernal_flags = DEVLINK_NL_FLAG_NEED_PORT,
	पूर्ण,
	अणु
		.cmd = DEVLINK_CMD_SB_OCC_SNAPSHOT,
		.validate = GENL_DONT_VALIDATE_STRICT | GENL_DONT_VALIDATE_DUMP,
		.करोit = devlink_nl_cmd_sb_occ_snapshot_करोit,
		.flags = GENL_ADMIN_PERM,
	पूर्ण,
	अणु
		.cmd = DEVLINK_CMD_SB_OCC_MAX_CLEAR,
		.validate = GENL_DONT_VALIDATE_STRICT | GENL_DONT_VALIDATE_DUMP,
		.करोit = devlink_nl_cmd_sb_occ_max_clear_करोit,
		.flags = GENL_ADMIN_PERM,
	पूर्ण,
	अणु
		.cmd = DEVLINK_CMD_ESWITCH_GET,
		.validate = GENL_DONT_VALIDATE_STRICT | GENL_DONT_VALIDATE_DUMP,
		.करोit = devlink_nl_cmd_eचयन_get_करोit,
		.flags = GENL_ADMIN_PERM,
		.पूर्णांकernal_flags = DEVLINK_NL_FLAG_NO_LOCK,
	पूर्ण,
	अणु
		.cmd = DEVLINK_CMD_ESWITCH_SET,
		.validate = GENL_DONT_VALIDATE_STRICT | GENL_DONT_VALIDATE_DUMP,
		.करोit = devlink_nl_cmd_eचयन_set_करोit,
		.flags = GENL_ADMIN_PERM,
		.पूर्णांकernal_flags = DEVLINK_NL_FLAG_NO_LOCK,
	पूर्ण,
	अणु
		.cmd = DEVLINK_CMD_DPIPE_TABLE_GET,
		.validate = GENL_DONT_VALIDATE_STRICT | GENL_DONT_VALIDATE_DUMP,
		.करोit = devlink_nl_cmd_dpipe_table_get,
		/* can be retrieved by unprivileged users */
	पूर्ण,
	अणु
		.cmd = DEVLINK_CMD_DPIPE_ENTRIES_GET,
		.validate = GENL_DONT_VALIDATE_STRICT | GENL_DONT_VALIDATE_DUMP,
		.करोit = devlink_nl_cmd_dpipe_entries_get,
		/* can be retrieved by unprivileged users */
	पूर्ण,
	अणु
		.cmd = DEVLINK_CMD_DPIPE_HEADERS_GET,
		.validate = GENL_DONT_VALIDATE_STRICT | GENL_DONT_VALIDATE_DUMP,
		.करोit = devlink_nl_cmd_dpipe_headers_get,
		/* can be retrieved by unprivileged users */
	पूर्ण,
	अणु
		.cmd = DEVLINK_CMD_DPIPE_TABLE_COUNTERS_SET,
		.validate = GENL_DONT_VALIDATE_STRICT | GENL_DONT_VALIDATE_DUMP,
		.करोit = devlink_nl_cmd_dpipe_table_counters_set,
		.flags = GENL_ADMIN_PERM,
	पूर्ण,
	अणु
		.cmd = DEVLINK_CMD_RESOURCE_SET,
		.validate = GENL_DONT_VALIDATE_STRICT | GENL_DONT_VALIDATE_DUMP,
		.करोit = devlink_nl_cmd_resource_set,
		.flags = GENL_ADMIN_PERM,
	पूर्ण,
	अणु
		.cmd = DEVLINK_CMD_RESOURCE_DUMP,
		.validate = GENL_DONT_VALIDATE_STRICT | GENL_DONT_VALIDATE_DUMP,
		.करोit = devlink_nl_cmd_resource_dump,
		/* can be retrieved by unprivileged users */
	पूर्ण,
	अणु
		.cmd = DEVLINK_CMD_RELOAD,
		.validate = GENL_DONT_VALIDATE_STRICT | GENL_DONT_VALIDATE_DUMP,
		.करोit = devlink_nl_cmd_reload,
		.flags = GENL_ADMIN_PERM,
		.पूर्णांकernal_flags = DEVLINK_NL_FLAG_NO_LOCK,
	पूर्ण,
	अणु
		.cmd = DEVLINK_CMD_PARAM_GET,
		.validate = GENL_DONT_VALIDATE_STRICT | GENL_DONT_VALIDATE_DUMP,
		.करोit = devlink_nl_cmd_param_get_करोit,
		.dumpit = devlink_nl_cmd_param_get_dumpit,
		/* can be retrieved by unprivileged users */
	पूर्ण,
	अणु
		.cmd = DEVLINK_CMD_PARAM_SET,
		.validate = GENL_DONT_VALIDATE_STRICT | GENL_DONT_VALIDATE_DUMP,
		.करोit = devlink_nl_cmd_param_set_करोit,
		.flags = GENL_ADMIN_PERM,
	पूर्ण,
	अणु
		.cmd = DEVLINK_CMD_PORT_PARAM_GET,
		.validate = GENL_DONT_VALIDATE_STRICT | GENL_DONT_VALIDATE_DUMP,
		.करोit = devlink_nl_cmd_port_param_get_करोit,
		.dumpit = devlink_nl_cmd_port_param_get_dumpit,
		.पूर्णांकernal_flags = DEVLINK_NL_FLAG_NEED_PORT,
		/* can be retrieved by unprivileged users */
	पूर्ण,
	अणु
		.cmd = DEVLINK_CMD_PORT_PARAM_SET,
		.validate = GENL_DONT_VALIDATE_STRICT | GENL_DONT_VALIDATE_DUMP,
		.करोit = devlink_nl_cmd_port_param_set_करोit,
		.flags = GENL_ADMIN_PERM,
		.पूर्णांकernal_flags = DEVLINK_NL_FLAG_NEED_PORT,
	पूर्ण,
	अणु
		.cmd = DEVLINK_CMD_REGION_GET,
		.validate = GENL_DONT_VALIDATE_STRICT | GENL_DONT_VALIDATE_DUMP,
		.करोit = devlink_nl_cmd_region_get_करोit,
		.dumpit = devlink_nl_cmd_region_get_dumpit,
		.flags = GENL_ADMIN_PERM,
	पूर्ण,
	अणु
		.cmd = DEVLINK_CMD_REGION_NEW,
		.validate = GENL_DONT_VALIDATE_STRICT | GENL_DONT_VALIDATE_DUMP,
		.करोit = devlink_nl_cmd_region_new,
		.flags = GENL_ADMIN_PERM,
	पूर्ण,
	अणु
		.cmd = DEVLINK_CMD_REGION_DEL,
		.validate = GENL_DONT_VALIDATE_STRICT | GENL_DONT_VALIDATE_DUMP,
		.करोit = devlink_nl_cmd_region_del,
		.flags = GENL_ADMIN_PERM,
	पूर्ण,
	अणु
		.cmd = DEVLINK_CMD_REGION_READ,
		.validate = GENL_DONT_VALIDATE_STRICT |
			    GENL_DONT_VALIDATE_DUMP_STRICT,
		.dumpit = devlink_nl_cmd_region_पढ़ो_dumpit,
		.flags = GENL_ADMIN_PERM,
	पूर्ण,
	अणु
		.cmd = DEVLINK_CMD_INFO_GET,
		.validate = GENL_DONT_VALIDATE_STRICT | GENL_DONT_VALIDATE_DUMP,
		.करोit = devlink_nl_cmd_info_get_करोit,
		.dumpit = devlink_nl_cmd_info_get_dumpit,
		/* can be retrieved by unprivileged users */
	पूर्ण,
	अणु
		.cmd = DEVLINK_CMD_HEALTH_REPORTER_GET,
		.validate = GENL_DONT_VALIDATE_STRICT | GENL_DONT_VALIDATE_DUMP,
		.करोit = devlink_nl_cmd_health_reporter_get_करोit,
		.dumpit = devlink_nl_cmd_health_reporter_get_dumpit,
		.पूर्णांकernal_flags = DEVLINK_NL_FLAG_NEED_DEVLINK_OR_PORT |
				  DEVLINK_NL_FLAG_NO_LOCK,
		/* can be retrieved by unprivileged users */
	पूर्ण,
	अणु
		.cmd = DEVLINK_CMD_HEALTH_REPORTER_SET,
		.validate = GENL_DONT_VALIDATE_STRICT | GENL_DONT_VALIDATE_DUMP,
		.करोit = devlink_nl_cmd_health_reporter_set_करोit,
		.flags = GENL_ADMIN_PERM,
		.पूर्णांकernal_flags = DEVLINK_NL_FLAG_NEED_DEVLINK_OR_PORT |
				  DEVLINK_NL_FLAG_NO_LOCK,
	पूर्ण,
	अणु
		.cmd = DEVLINK_CMD_HEALTH_REPORTER_RECOVER,
		.validate = GENL_DONT_VALIDATE_STRICT | GENL_DONT_VALIDATE_DUMP,
		.करोit = devlink_nl_cmd_health_reporter_recover_करोit,
		.flags = GENL_ADMIN_PERM,
		.पूर्णांकernal_flags = DEVLINK_NL_FLAG_NEED_DEVLINK_OR_PORT |
				  DEVLINK_NL_FLAG_NO_LOCK,
	पूर्ण,
	अणु
		.cmd = DEVLINK_CMD_HEALTH_REPORTER_DIAGNOSE,
		.validate = GENL_DONT_VALIDATE_STRICT | GENL_DONT_VALIDATE_DUMP,
		.करोit = devlink_nl_cmd_health_reporter_diagnose_करोit,
		.flags = GENL_ADMIN_PERM,
		.पूर्णांकernal_flags = DEVLINK_NL_FLAG_NEED_DEVLINK_OR_PORT |
				  DEVLINK_NL_FLAG_NO_LOCK,
	पूर्ण,
	अणु
		.cmd = DEVLINK_CMD_HEALTH_REPORTER_DUMP_GET,
		.validate = GENL_DONT_VALIDATE_STRICT |
			    GENL_DONT_VALIDATE_DUMP_STRICT,
		.dumpit = devlink_nl_cmd_health_reporter_dump_get_dumpit,
		.flags = GENL_ADMIN_PERM,
		.पूर्णांकernal_flags = DEVLINK_NL_FLAG_NEED_DEVLINK_OR_PORT |
				  DEVLINK_NL_FLAG_NO_LOCK,
	पूर्ण,
	अणु
		.cmd = DEVLINK_CMD_HEALTH_REPORTER_DUMP_CLEAR,
		.validate = GENL_DONT_VALIDATE_STRICT | GENL_DONT_VALIDATE_DUMP,
		.करोit = devlink_nl_cmd_health_reporter_dump_clear_करोit,
		.flags = GENL_ADMIN_PERM,
		.पूर्णांकernal_flags = DEVLINK_NL_FLAG_NEED_DEVLINK_OR_PORT |
				  DEVLINK_NL_FLAG_NO_LOCK,
	पूर्ण,
	अणु
		.cmd = DEVLINK_CMD_HEALTH_REPORTER_TEST,
		.validate = GENL_DONT_VALIDATE_STRICT | GENL_DONT_VALIDATE_DUMP,
		.करोit = devlink_nl_cmd_health_reporter_test_करोit,
		.flags = GENL_ADMIN_PERM,
		.पूर्णांकernal_flags = DEVLINK_NL_FLAG_NEED_DEVLINK_OR_PORT |
				  DEVLINK_NL_FLAG_NO_LOCK,
	पूर्ण,
	अणु
		.cmd = DEVLINK_CMD_FLASH_UPDATE,
		.validate = GENL_DONT_VALIDATE_STRICT | GENL_DONT_VALIDATE_DUMP,
		.करोit = devlink_nl_cmd_flash_update,
		.flags = GENL_ADMIN_PERM,
	पूर्ण,
	अणु
		.cmd = DEVLINK_CMD_TRAP_GET,
		.करोit = devlink_nl_cmd_trap_get_करोit,
		.dumpit = devlink_nl_cmd_trap_get_dumpit,
		/* can be retrieved by unprivileged users */
	पूर्ण,
	अणु
		.cmd = DEVLINK_CMD_TRAP_SET,
		.करोit = devlink_nl_cmd_trap_set_करोit,
		.flags = GENL_ADMIN_PERM,
	पूर्ण,
	अणु
		.cmd = DEVLINK_CMD_TRAP_GROUP_GET,
		.करोit = devlink_nl_cmd_trap_group_get_करोit,
		.dumpit = devlink_nl_cmd_trap_group_get_dumpit,
		/* can be retrieved by unprivileged users */
	पूर्ण,
	अणु
		.cmd = DEVLINK_CMD_TRAP_GROUP_SET,
		.करोit = devlink_nl_cmd_trap_group_set_करोit,
		.flags = GENL_ADMIN_PERM,
	पूर्ण,
	अणु
		.cmd = DEVLINK_CMD_TRAP_POLICER_GET,
		.करोit = devlink_nl_cmd_trap_policer_get_करोit,
		.dumpit = devlink_nl_cmd_trap_policer_get_dumpit,
		/* can be retrieved by unprivileged users */
	पूर्ण,
	अणु
		.cmd = DEVLINK_CMD_TRAP_POLICER_SET,
		.करोit = devlink_nl_cmd_trap_policer_set_करोit,
		.flags = GENL_ADMIN_PERM,
	पूर्ण,
पूर्ण;

अटल काष्ठा genl_family devlink_nl_family __ro_after_init = अणु
	.name		= DEVLINK_GENL_NAME,
	.version	= DEVLINK_GENL_VERSION,
	.maxattr	= DEVLINK_ATTR_MAX,
	.policy = devlink_nl_policy,
	.netnsok	= true,
	.pre_करोit	= devlink_nl_pre_करोit,
	.post_करोit	= devlink_nl_post_करोit,
	.module		= THIS_MODULE,
	.small_ops	= devlink_nl_ops,
	.n_small_ops	= ARRAY_SIZE(devlink_nl_ops),
	.mcgrps		= devlink_nl_mcgrps,
	.n_mcgrps	= ARRAY_SIZE(devlink_nl_mcgrps),
पूर्ण;

अटल bool devlink_reload_actions_valid(स्थिर काष्ठा devlink_ops *ops)
अणु
	स्थिर काष्ठा devlink_reload_combination *comb;
	पूर्णांक i;

	अगर (!devlink_reload_supported(ops)) अणु
		अगर (WARN_ON(ops->reload_actions))
			वापस false;
		वापस true;
	पूर्ण

	अगर (WARN_ON(!ops->reload_actions ||
		    ops->reload_actions & BIT(DEVLINK_RELOAD_ACTION_UNSPEC) ||
		    ops->reload_actions >= BIT(__DEVLINK_RELOAD_ACTION_MAX)))
		वापस false;

	अगर (WARN_ON(ops->reload_limits & BIT(DEVLINK_RELOAD_LIMIT_UNSPEC) ||
		    ops->reload_limits >= BIT(__DEVLINK_RELOAD_LIMIT_MAX)))
		वापस false;

	क्रम (i = 0; i < ARRAY_SIZE(devlink_reload_invalid_combinations); i++)  अणु
		comb = &devlink_reload_invalid_combinations[i];
		अगर (ops->reload_actions == BIT(comb->action) &&
		    ops->reload_limits == BIT(comb->limit))
			वापस false;
	पूर्ण
	वापस true;
पूर्ण

/**
 *	devlink_alloc - Allocate new devlink instance resources
 *
 *	@ops: ops
 *	@priv_size: size of user निजी data
 *
 *	Allocate new devlink instance resources, including devlink index
 *	and name.
 */
काष्ठा devlink *devlink_alloc(स्थिर काष्ठा devlink_ops *ops, माप_प्रकार priv_size)
अणु
	काष्ठा devlink *devlink;

	अगर (WARN_ON(!ops))
		वापस शून्य;

	अगर (!devlink_reload_actions_valid(ops))
		वापस शून्य;

	devlink = kzalloc(माप(*devlink) + priv_size, GFP_KERNEL);
	अगर (!devlink)
		वापस शून्य;
	devlink->ops = ops;
	xa_init_flags(&devlink->snapshot_ids, XA_FLAGS_ALLOC);
	__devlink_net_set(devlink, &init_net);
	INIT_LIST_HEAD(&devlink->port_list);
	INIT_LIST_HEAD(&devlink->sb_list);
	INIT_LIST_HEAD_RCU(&devlink->dpipe_table_list);
	INIT_LIST_HEAD(&devlink->resource_list);
	INIT_LIST_HEAD(&devlink->param_list);
	INIT_LIST_HEAD(&devlink->region_list);
	INIT_LIST_HEAD(&devlink->reporter_list);
	INIT_LIST_HEAD(&devlink->trap_list);
	INIT_LIST_HEAD(&devlink->trap_group_list);
	INIT_LIST_HEAD(&devlink->trap_policer_list);
	mutex_init(&devlink->lock);
	mutex_init(&devlink->reporters_lock);
	वापस devlink;
पूर्ण
EXPORT_SYMBOL_GPL(devlink_alloc);

/**
 *	devlink_रेजिस्टर - Register devlink instance
 *
 *	@devlink: devlink
 *	@dev: parent device
 */
पूर्णांक devlink_रेजिस्टर(काष्ठा devlink *devlink, काष्ठा device *dev)
अणु
	devlink->dev = dev;
	devlink->रेजिस्टरed = true;
	mutex_lock(&devlink_mutex);
	list_add_tail(&devlink->list, &devlink_list);
	devlink_notअगरy(devlink, DEVLINK_CMD_NEW);
	mutex_unlock(&devlink_mutex);
	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(devlink_रेजिस्टर);

/**
 *	devlink_unरेजिस्टर - Unरेजिस्टर devlink instance
 *
 *	@devlink: devlink
 */
व्योम devlink_unरेजिस्टर(काष्ठा devlink *devlink)
अणु
	mutex_lock(&devlink_mutex);
	WARN_ON(devlink_reload_supported(devlink->ops) &&
		devlink->reload_enabled);
	devlink_notअगरy(devlink, DEVLINK_CMD_DEL);
	list_del(&devlink->list);
	mutex_unlock(&devlink_mutex);
पूर्ण
EXPORT_SYMBOL_GPL(devlink_unरेजिस्टर);

/**
 *	devlink_reload_enable - Enable reload of devlink instance
 *
 *	@devlink: devlink
 *
 *	Should be called at end of device initialization
 *	process when reload operation is supported.
 */
व्योम devlink_reload_enable(काष्ठा devlink *devlink)
अणु
	mutex_lock(&devlink_mutex);
	devlink->reload_enabled = true;
	mutex_unlock(&devlink_mutex);
पूर्ण
EXPORT_SYMBOL_GPL(devlink_reload_enable);

/**
 *	devlink_reload_disable - Disable reload of devlink instance
 *
 *	@devlink: devlink
 *
 *	Should be called at the beginning of device cleanup
 *	process when reload operation is supported.
 */
व्योम devlink_reload_disable(काष्ठा devlink *devlink)
अणु
	mutex_lock(&devlink_mutex);
	/* Mutex is taken which ensures that no reload operation is in
	 * progress जबतक setting up क्रमbidded flag.
	 */
	devlink->reload_enabled = false;
	mutex_unlock(&devlink_mutex);
पूर्ण
EXPORT_SYMBOL_GPL(devlink_reload_disable);

/**
 *	devlink_मुक्त - Free devlink instance resources
 *
 *	@devlink: devlink
 */
व्योम devlink_मुक्त(काष्ठा devlink *devlink)
अणु
	mutex_destroy(&devlink->reporters_lock);
	mutex_destroy(&devlink->lock);
	WARN_ON(!list_empty(&devlink->trap_policer_list));
	WARN_ON(!list_empty(&devlink->trap_group_list));
	WARN_ON(!list_empty(&devlink->trap_list));
	WARN_ON(!list_empty(&devlink->reporter_list));
	WARN_ON(!list_empty(&devlink->region_list));
	WARN_ON(!list_empty(&devlink->param_list));
	WARN_ON(!list_empty(&devlink->resource_list));
	WARN_ON(!list_empty(&devlink->dpipe_table_list));
	WARN_ON(!list_empty(&devlink->sb_list));
	WARN_ON(!list_empty(&devlink->port_list));

	xa_destroy(&devlink->snapshot_ids);

	kमुक्त(devlink);
पूर्ण
EXPORT_SYMBOL_GPL(devlink_मुक्त);

अटल व्योम devlink_port_type_warn(काष्ठा work_काष्ठा *work)
अणु
	WARN(true, "Type was not set for devlink port.");
पूर्ण

अटल bool devlink_port_type_should_warn(काष्ठा devlink_port *devlink_port)
अणु
	/* Ignore CPU and DSA flavours. */
	वापस devlink_port->attrs.flavour != DEVLINK_PORT_FLAVOUR_CPU &&
	       devlink_port->attrs.flavour != DEVLINK_PORT_FLAVOUR_DSA &&
	       devlink_port->attrs.flavour != DEVLINK_PORT_FLAVOUR_UNUSED;
पूर्ण

#घोषणा DEVLINK_PORT_TYPE_WARN_TIMEOUT (HZ * 3600)

अटल व्योम devlink_port_type_warn_schedule(काष्ठा devlink_port *devlink_port)
अणु
	अगर (!devlink_port_type_should_warn(devlink_port))
		वापस;
	/* Schedule a work to WARN in हाल driver करोes not set port
	 * type within समयout.
	 */
	schedule_delayed_work(&devlink_port->type_warn_dw,
			      DEVLINK_PORT_TYPE_WARN_TIMEOUT);
पूर्ण

अटल व्योम devlink_port_type_warn_cancel(काष्ठा devlink_port *devlink_port)
अणु
	अगर (!devlink_port_type_should_warn(devlink_port))
		वापस;
	cancel_delayed_work_sync(&devlink_port->type_warn_dw);
पूर्ण

/**
 *	devlink_port_रेजिस्टर - Register devlink port
 *
 *	@devlink: devlink
 *	@devlink_port: devlink port
 *	@port_index: driver-specअगरic numerical identअगरier of the port
 *
 *	Register devlink port with provided port index. User can use
 *	any indexing, even hw-related one. devlink_port काष्ठाure
 *	is convenient to be embedded inside user driver निजी काष्ठाure.
 *	Note that the caller should take care of zeroing the devlink_port
 *	काष्ठाure.
 */
पूर्णांक devlink_port_रेजिस्टर(काष्ठा devlink *devlink,
			  काष्ठा devlink_port *devlink_port,
			  अचिन्हित पूर्णांक port_index)
अणु
	mutex_lock(&devlink->lock);
	अगर (devlink_port_index_exists(devlink, port_index)) अणु
		mutex_unlock(&devlink->lock);
		वापस -EEXIST;
	पूर्ण
	devlink_port->devlink = devlink;
	devlink_port->index = port_index;
	devlink_port->रेजिस्टरed = true;
	spin_lock_init(&devlink_port->type_lock);
	INIT_LIST_HEAD(&devlink_port->reporter_list);
	mutex_init(&devlink_port->reporters_lock);
	list_add_tail(&devlink_port->list, &devlink->port_list);
	INIT_LIST_HEAD(&devlink_port->param_list);
	INIT_LIST_HEAD(&devlink_port->region_list);
	mutex_unlock(&devlink->lock);
	INIT_DELAYED_WORK(&devlink_port->type_warn_dw, &devlink_port_type_warn);
	devlink_port_type_warn_schedule(devlink_port);
	devlink_port_notअगरy(devlink_port, DEVLINK_CMD_PORT_NEW);
	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(devlink_port_रेजिस्टर);

/**
 *	devlink_port_unरेजिस्टर - Unरेजिस्टर devlink port
 *
 *	@devlink_port: devlink port
 */
व्योम devlink_port_unरेजिस्टर(काष्ठा devlink_port *devlink_port)
अणु
	काष्ठा devlink *devlink = devlink_port->devlink;

	devlink_port_type_warn_cancel(devlink_port);
	devlink_port_notअगरy(devlink_port, DEVLINK_CMD_PORT_DEL);
	mutex_lock(&devlink->lock);
	list_del(&devlink_port->list);
	mutex_unlock(&devlink->lock);
	WARN_ON(!list_empty(&devlink_port->reporter_list));
	WARN_ON(!list_empty(&devlink_port->region_list));
	mutex_destroy(&devlink_port->reporters_lock);
पूर्ण
EXPORT_SYMBOL_GPL(devlink_port_unरेजिस्टर);

अटल व्योम __devlink_port_type_set(काष्ठा devlink_port *devlink_port,
				    क्रमागत devlink_port_type type,
				    व्योम *type_dev)
अणु
	अगर (WARN_ON(!devlink_port->रेजिस्टरed))
		वापस;
	devlink_port_type_warn_cancel(devlink_port);
	spin_lock_bh(&devlink_port->type_lock);
	devlink_port->type = type;
	devlink_port->type_dev = type_dev;
	spin_unlock_bh(&devlink_port->type_lock);
	devlink_port_notअगरy(devlink_port, DEVLINK_CMD_PORT_NEW);
पूर्ण

अटल व्योम devlink_port_type_netdev_checks(काष्ठा devlink_port *devlink_port,
					    काष्ठा net_device *netdev)
अणु
	स्थिर काष्ठा net_device_ops *ops = netdev->netdev_ops;

	/* If driver रेजिस्टरs devlink port, it should set devlink port
	 * attributes accordingly so the compat functions are called
	 * and the original ops are not used.
	 */
	अगर (ops->nकरो_get_phys_port_name) अणु
		/* Some drivers use the same set of nकरोs क्रम netdevs
		 * that have devlink_port रेजिस्टरed and also क्रम
		 * those who करोn't. Make sure that nकरो_get_phys_port_name
		 * वापसs -EOPNOTSUPP here in हाल it is defined.
		 * Warn अगर not.
		 */
		अक्षर name[IFNAMSIZ];
		पूर्णांक err;

		err = ops->nकरो_get_phys_port_name(netdev, name, माप(name));
		WARN_ON(err != -EOPNOTSUPP);
	पूर्ण
	अगर (ops->nकरो_get_port_parent_id) अणु
		/* Some drivers use the same set of nकरोs क्रम netdevs
		 * that have devlink_port रेजिस्टरed and also क्रम
		 * those who करोn't. Make sure that nकरो_get_port_parent_id
		 * वापसs -EOPNOTSUPP here in हाल it is defined.
		 * Warn अगर not.
		 */
		काष्ठा netdev_phys_item_id ppid;
		पूर्णांक err;

		err = ops->nकरो_get_port_parent_id(netdev, &ppid);
		WARN_ON(err != -EOPNOTSUPP);
	पूर्ण
पूर्ण

/**
 *	devlink_port_type_eth_set - Set port type to Ethernet
 *
 *	@devlink_port: devlink port
 *	@netdev: related netdevice
 */
व्योम devlink_port_type_eth_set(काष्ठा devlink_port *devlink_port,
			       काष्ठा net_device *netdev)
अणु
	अगर (netdev)
		devlink_port_type_netdev_checks(devlink_port, netdev);
	अन्यथा
		dev_warn(devlink_port->devlink->dev,
			 "devlink port type for port %d set to Ethernet without a software interface reference, device type not supported by the kernel?\n",
			 devlink_port->index);

	__devlink_port_type_set(devlink_port, DEVLINK_PORT_TYPE_ETH, netdev);
पूर्ण
EXPORT_SYMBOL_GPL(devlink_port_type_eth_set);

/**
 *	devlink_port_type_ib_set - Set port type to InfiniBand
 *
 *	@devlink_port: devlink port
 *	@ibdev: related IB device
 */
व्योम devlink_port_type_ib_set(काष्ठा devlink_port *devlink_port,
			      काष्ठा ib_device *ibdev)
अणु
	__devlink_port_type_set(devlink_port, DEVLINK_PORT_TYPE_IB, ibdev);
पूर्ण
EXPORT_SYMBOL_GPL(devlink_port_type_ib_set);

/**
 *	devlink_port_type_clear - Clear port type
 *
 *	@devlink_port: devlink port
 */
व्योम devlink_port_type_clear(काष्ठा devlink_port *devlink_port)
अणु
	__devlink_port_type_set(devlink_port, DEVLINK_PORT_TYPE_NOTSET, शून्य);
	devlink_port_type_warn_schedule(devlink_port);
पूर्ण
EXPORT_SYMBOL_GPL(devlink_port_type_clear);

अटल पूर्णांक __devlink_port_attrs_set(काष्ठा devlink_port *devlink_port,
				    क्रमागत devlink_port_flavour flavour)
अणु
	काष्ठा devlink_port_attrs *attrs = &devlink_port->attrs;

	devlink_port->attrs_set = true;
	attrs->flavour = flavour;
	अगर (attrs->चयन_id.id_len) अणु
		devlink_port->चयन_port = true;
		अगर (WARN_ON(attrs->चयन_id.id_len > MAX_PHYS_ITEM_ID_LEN))
			attrs->चयन_id.id_len = MAX_PHYS_ITEM_ID_LEN;
	पूर्ण अन्यथा अणु
		devlink_port->चयन_port = false;
	पूर्ण
	वापस 0;
पूर्ण

/**
 *	devlink_port_attrs_set - Set port attributes
 *
 *	@devlink_port: devlink port
 *	@attrs: devlink port attrs
 */
व्योम devlink_port_attrs_set(काष्ठा devlink_port *devlink_port,
			    काष्ठा devlink_port_attrs *attrs)
अणु
	पूर्णांक ret;

	अगर (WARN_ON(devlink_port->रेजिस्टरed))
		वापस;
	devlink_port->attrs = *attrs;
	ret = __devlink_port_attrs_set(devlink_port, attrs->flavour);
	अगर (ret)
		वापस;
	WARN_ON(attrs->splittable && attrs->split);
पूर्ण
EXPORT_SYMBOL_GPL(devlink_port_attrs_set);

/**
 *	devlink_port_attrs_pci_pf_set - Set PCI PF port attributes
 *
 *	@devlink_port: devlink port
 *	@controller: associated controller number क्रम the devlink port instance
 *	@pf: associated PF क्रम the devlink port instance
 *	@बाह्यal: indicates अगर the port is क्रम an बाह्यal controller
 */
व्योम devlink_port_attrs_pci_pf_set(काष्ठा devlink_port *devlink_port, u32 controller,
				   u16 pf, bool बाह्यal)
अणु
	काष्ठा devlink_port_attrs *attrs = &devlink_port->attrs;
	पूर्णांक ret;

	अगर (WARN_ON(devlink_port->रेजिस्टरed))
		वापस;
	ret = __devlink_port_attrs_set(devlink_port,
				       DEVLINK_PORT_FLAVOUR_PCI_PF);
	अगर (ret)
		वापस;
	attrs->pci_pf.controller = controller;
	attrs->pci_pf.pf = pf;
	attrs->pci_pf.बाह्यal = बाह्यal;
पूर्ण
EXPORT_SYMBOL_GPL(devlink_port_attrs_pci_pf_set);

/**
 *	devlink_port_attrs_pci_vf_set - Set PCI VF port attributes
 *
 *	@devlink_port: devlink port
 *	@controller: associated controller number क्रम the devlink port instance
 *	@pf: associated PF क्रम the devlink port instance
 *	@vf: associated VF of a PF क्रम the devlink port instance
 *	@बाह्यal: indicates अगर the port is क्रम an बाह्यal controller
 */
व्योम devlink_port_attrs_pci_vf_set(काष्ठा devlink_port *devlink_port, u32 controller,
				   u16 pf, u16 vf, bool बाह्यal)
अणु
	काष्ठा devlink_port_attrs *attrs = &devlink_port->attrs;
	पूर्णांक ret;

	अगर (WARN_ON(devlink_port->रेजिस्टरed))
		वापस;
	ret = __devlink_port_attrs_set(devlink_port,
				       DEVLINK_PORT_FLAVOUR_PCI_VF);
	अगर (ret)
		वापस;
	attrs->pci_vf.controller = controller;
	attrs->pci_vf.pf = pf;
	attrs->pci_vf.vf = vf;
	attrs->pci_vf.बाह्यal = बाह्यal;
पूर्ण
EXPORT_SYMBOL_GPL(devlink_port_attrs_pci_vf_set);

/**
 *	devlink_port_attrs_pci_sf_set - Set PCI SF port attributes
 *
 *	@devlink_port: devlink port
 *	@controller: associated controller number क्रम the devlink port instance
 *	@pf: associated PF क्रम the devlink port instance
 *	@sf: associated SF of a PF क्रम the devlink port instance
 *	@बाह्यal: indicates अगर the port is क्रम an बाह्यal controller
 */
व्योम devlink_port_attrs_pci_sf_set(काष्ठा devlink_port *devlink_port, u32 controller,
				   u16 pf, u32 sf, bool बाह्यal)
अणु
	काष्ठा devlink_port_attrs *attrs = &devlink_port->attrs;
	पूर्णांक ret;

	अगर (WARN_ON(devlink_port->रेजिस्टरed))
		वापस;
	ret = __devlink_port_attrs_set(devlink_port,
				       DEVLINK_PORT_FLAVOUR_PCI_SF);
	अगर (ret)
		वापस;
	attrs->pci_sf.controller = controller;
	attrs->pci_sf.pf = pf;
	attrs->pci_sf.sf = sf;
	attrs->pci_sf.बाह्यal = बाह्यal;
पूर्ण
EXPORT_SYMBOL_GPL(devlink_port_attrs_pci_sf_set);

अटल पूर्णांक __devlink_port_phys_port_name_get(काष्ठा devlink_port *devlink_port,
					     अक्षर *name, माप_प्रकार len)
अणु
	काष्ठा devlink_port_attrs *attrs = &devlink_port->attrs;
	पूर्णांक n = 0;

	अगर (!devlink_port->attrs_set)
		वापस -EOPNOTSUPP;

	चयन (attrs->flavour) अणु
	हाल DEVLINK_PORT_FLAVOUR_PHYSICAL:
		अगर (!attrs->split)
			n = snम_लिखो(name, len, "p%u", attrs->phys.port_number);
		अन्यथा
			n = snम_लिखो(name, len, "p%us%u",
				     attrs->phys.port_number,
				     attrs->phys.split_subport_number);
		अवरोध;
	हाल DEVLINK_PORT_FLAVOUR_CPU:
	हाल DEVLINK_PORT_FLAVOUR_DSA:
	हाल DEVLINK_PORT_FLAVOUR_UNUSED:
		/* As CPU and DSA ports करो not have a netdevice associated
		 * हाल should not ever happen.
		 */
		WARN_ON(1);
		वापस -EINVAL;
	हाल DEVLINK_PORT_FLAVOUR_PCI_PF:
		अगर (attrs->pci_pf.बाह्यal) अणु
			n = snम_लिखो(name, len, "c%u", attrs->pci_pf.controller);
			अगर (n >= len)
				वापस -EINVAL;
			len -= n;
			name += n;
		पूर्ण
		n = snम_लिखो(name, len, "pf%u", attrs->pci_pf.pf);
		अवरोध;
	हाल DEVLINK_PORT_FLAVOUR_PCI_VF:
		अगर (attrs->pci_vf.बाह्यal) अणु
			n = snम_लिखो(name, len, "c%u", attrs->pci_vf.controller);
			अगर (n >= len)
				वापस -EINVAL;
			len -= n;
			name += n;
		पूर्ण
		n = snम_लिखो(name, len, "pf%uvf%u",
			     attrs->pci_vf.pf, attrs->pci_vf.vf);
		अवरोध;
	हाल DEVLINK_PORT_FLAVOUR_PCI_SF:
		अगर (attrs->pci_sf.बाह्यal) अणु
			n = snम_लिखो(name, len, "c%u", attrs->pci_sf.controller);
			अगर (n >= len)
				वापस -EINVAL;
			len -= n;
			name += n;
		पूर्ण
		n = snम_लिखो(name, len, "pf%usf%u", attrs->pci_sf.pf,
			     attrs->pci_sf.sf);
		अवरोध;
	हाल DEVLINK_PORT_FLAVOUR_VIRTUAL:
		वापस -EOPNOTSUPP;
	पूर्ण

	अगर (n >= len)
		वापस -EINVAL;

	वापस 0;
पूर्ण

पूर्णांक devlink_sb_रेजिस्टर(काष्ठा devlink *devlink, अचिन्हित पूर्णांक sb_index,
			u32 size, u16 ingress_pools_count,
			u16 egress_pools_count, u16 ingress_tc_count,
			u16 egress_tc_count)
अणु
	काष्ठा devlink_sb *devlink_sb;
	पूर्णांक err = 0;

	mutex_lock(&devlink->lock);
	अगर (devlink_sb_index_exists(devlink, sb_index)) अणु
		err = -EEXIST;
		जाओ unlock;
	पूर्ण

	devlink_sb = kzalloc(माप(*devlink_sb), GFP_KERNEL);
	अगर (!devlink_sb) अणु
		err = -ENOMEM;
		जाओ unlock;
	पूर्ण
	devlink_sb->index = sb_index;
	devlink_sb->size = size;
	devlink_sb->ingress_pools_count = ingress_pools_count;
	devlink_sb->egress_pools_count = egress_pools_count;
	devlink_sb->ingress_tc_count = ingress_tc_count;
	devlink_sb->egress_tc_count = egress_tc_count;
	list_add_tail(&devlink_sb->list, &devlink->sb_list);
unlock:
	mutex_unlock(&devlink->lock);
	वापस err;
पूर्ण
EXPORT_SYMBOL_GPL(devlink_sb_रेजिस्टर);

व्योम devlink_sb_unरेजिस्टर(काष्ठा devlink *devlink, अचिन्हित पूर्णांक sb_index)
अणु
	काष्ठा devlink_sb *devlink_sb;

	mutex_lock(&devlink->lock);
	devlink_sb = devlink_sb_get_by_index(devlink, sb_index);
	WARN_ON(!devlink_sb);
	list_del(&devlink_sb->list);
	mutex_unlock(&devlink->lock);
	kमुक्त(devlink_sb);
पूर्ण
EXPORT_SYMBOL_GPL(devlink_sb_unरेजिस्टर);

/**
 *	devlink_dpipe_headers_रेजिस्टर - रेजिस्टर dpipe headers
 *
 *	@devlink: devlink
 *	@dpipe_headers: dpipe header array
 *
 *	Register the headers supported by hardware.
 */
पूर्णांक devlink_dpipe_headers_रेजिस्टर(काष्ठा devlink *devlink,
				   काष्ठा devlink_dpipe_headers *dpipe_headers)
अणु
	mutex_lock(&devlink->lock);
	devlink->dpipe_headers = dpipe_headers;
	mutex_unlock(&devlink->lock);
	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(devlink_dpipe_headers_रेजिस्टर);

/**
 *	devlink_dpipe_headers_unरेजिस्टर - unरेजिस्टर dpipe headers
 *
 *	@devlink: devlink
 *
 *	Unरेजिस्टर the headers supported by hardware.
 */
व्योम devlink_dpipe_headers_unरेजिस्टर(काष्ठा devlink *devlink)
अणु
	mutex_lock(&devlink->lock);
	devlink->dpipe_headers = शून्य;
	mutex_unlock(&devlink->lock);
पूर्ण
EXPORT_SYMBOL_GPL(devlink_dpipe_headers_unरेजिस्टर);

/**
 *	devlink_dpipe_table_counter_enabled - check अगर counter allocation
 *					      required
 *	@devlink: devlink
 *	@table_name: tables name
 *
 *	Used by driver to check अगर counter allocation is required.
 *	After counter allocation is turned on the table entries
 *	are updated to include counter statistics.
 *
 *	After that poपूर्णांक on the driver must respect the counter
 *	state so that each entry added to the table is added
 *	with a counter.
 */
bool devlink_dpipe_table_counter_enabled(काष्ठा devlink *devlink,
					 स्थिर अक्षर *table_name)
अणु
	काष्ठा devlink_dpipe_table *table;
	bool enabled;

	rcu_पढ़ो_lock();
	table = devlink_dpipe_table_find(&devlink->dpipe_table_list,
					 table_name, devlink);
	enabled = false;
	अगर (table)
		enabled = table->counters_enabled;
	rcu_पढ़ो_unlock();
	वापस enabled;
पूर्ण
EXPORT_SYMBOL_GPL(devlink_dpipe_table_counter_enabled);

/**
 *	devlink_dpipe_table_रेजिस्टर - रेजिस्टर dpipe table
 *
 *	@devlink: devlink
 *	@table_name: table name
 *	@table_ops: table ops
 *	@priv: priv
 *	@counter_control_बाह्य: बाह्यal control क्रम counters
 */
पूर्णांक devlink_dpipe_table_रेजिस्टर(काष्ठा devlink *devlink,
				 स्थिर अक्षर *table_name,
				 काष्ठा devlink_dpipe_table_ops *table_ops,
				 व्योम *priv, bool counter_control_बाह्य)
अणु
	काष्ठा devlink_dpipe_table *table;
	पूर्णांक err = 0;

	अगर (WARN_ON(!table_ops->size_get))
		वापस -EINVAL;

	mutex_lock(&devlink->lock);

	अगर (devlink_dpipe_table_find(&devlink->dpipe_table_list, table_name,
				     devlink)) अणु
		err = -EEXIST;
		जाओ unlock;
	पूर्ण

	table = kzalloc(माप(*table), GFP_KERNEL);
	अगर (!table) अणु
		err = -ENOMEM;
		जाओ unlock;
	पूर्ण

	table->name = table_name;
	table->table_ops = table_ops;
	table->priv = priv;
	table->counter_control_बाह्य = counter_control_बाह्य;

	list_add_tail_rcu(&table->list, &devlink->dpipe_table_list);
unlock:
	mutex_unlock(&devlink->lock);
	वापस err;
पूर्ण
EXPORT_SYMBOL_GPL(devlink_dpipe_table_रेजिस्टर);

/**
 *	devlink_dpipe_table_unरेजिस्टर - unरेजिस्टर dpipe table
 *
 *	@devlink: devlink
 *	@table_name: table name
 */
व्योम devlink_dpipe_table_unरेजिस्टर(काष्ठा devlink *devlink,
				    स्थिर अक्षर *table_name)
अणु
	काष्ठा devlink_dpipe_table *table;

	mutex_lock(&devlink->lock);
	table = devlink_dpipe_table_find(&devlink->dpipe_table_list,
					 table_name, devlink);
	अगर (!table)
		जाओ unlock;
	list_del_rcu(&table->list);
	mutex_unlock(&devlink->lock);
	kमुक्त_rcu(table, rcu);
	वापस;
unlock:
	mutex_unlock(&devlink->lock);
पूर्ण
EXPORT_SYMBOL_GPL(devlink_dpipe_table_unरेजिस्टर);

/**
 *	devlink_resource_रेजिस्टर - devlink resource रेजिस्टर
 *
 *	@devlink: devlink
 *	@resource_name: resource's name
 *	@resource_size: resource's size
 *	@resource_id: resource's id
 *	@parent_resource_id: resource's parent id
 *	@size_params: size parameters
 *
 *	Generic resources should reuse the same names across drivers.
 *	Please see the generic resources list at:
 *	Documentation/networking/devlink/devlink-resource.rst
 */
पूर्णांक devlink_resource_रेजिस्टर(काष्ठा devlink *devlink,
			      स्थिर अक्षर *resource_name,
			      u64 resource_size,
			      u64 resource_id,
			      u64 parent_resource_id,
			      स्थिर काष्ठा devlink_resource_size_params *size_params)
अणु
	काष्ठा devlink_resource *resource;
	काष्ठा list_head *resource_list;
	bool top_hierarchy;
	पूर्णांक err = 0;

	top_hierarchy = parent_resource_id == DEVLINK_RESOURCE_ID_PARENT_TOP;

	mutex_lock(&devlink->lock);
	resource = devlink_resource_find(devlink, शून्य, resource_id);
	अगर (resource) अणु
		err = -EINVAL;
		जाओ out;
	पूर्ण

	resource = kzalloc(माप(*resource), GFP_KERNEL);
	अगर (!resource) अणु
		err = -ENOMEM;
		जाओ out;
	पूर्ण

	अगर (top_hierarchy) अणु
		resource_list = &devlink->resource_list;
	पूर्ण अन्यथा अणु
		काष्ठा devlink_resource *parent_resource;

		parent_resource = devlink_resource_find(devlink, शून्य,
							parent_resource_id);
		अगर (parent_resource) अणु
			resource_list = &parent_resource->resource_list;
			resource->parent = parent_resource;
		पूर्ण अन्यथा अणु
			kमुक्त(resource);
			err = -EINVAL;
			जाओ out;
		पूर्ण
	पूर्ण

	resource->name = resource_name;
	resource->size = resource_size;
	resource->size_new = resource_size;
	resource->id = resource_id;
	resource->size_valid = true;
	स_नकल(&resource->size_params, size_params,
	       माप(resource->size_params));
	INIT_LIST_HEAD(&resource->resource_list);
	list_add_tail(&resource->list, resource_list);
out:
	mutex_unlock(&devlink->lock);
	वापस err;
पूर्ण
EXPORT_SYMBOL_GPL(devlink_resource_रेजिस्टर);

/**
 *	devlink_resources_unरेजिस्टर - मुक्त all resources
 *
 *	@devlink: devlink
 *	@resource: resource
 */
व्योम devlink_resources_unरेजिस्टर(काष्ठा devlink *devlink,
				  काष्ठा devlink_resource *resource)
अणु
	काष्ठा devlink_resource *पंचांगp, *child_resource;
	काष्ठा list_head *resource_list;

	अगर (resource)
		resource_list = &resource->resource_list;
	अन्यथा
		resource_list = &devlink->resource_list;

	अगर (!resource)
		mutex_lock(&devlink->lock);

	list_क्रम_each_entry_safe(child_resource, पंचांगp, resource_list, list) अणु
		devlink_resources_unरेजिस्टर(devlink, child_resource);
		list_del(&child_resource->list);
		kमुक्त(child_resource);
	पूर्ण

	अगर (!resource)
		mutex_unlock(&devlink->lock);
पूर्ण
EXPORT_SYMBOL_GPL(devlink_resources_unरेजिस्टर);

/**
 *	devlink_resource_size_get - get and update size
 *
 *	@devlink: devlink
 *	@resource_id: the requested resource id
 *	@p_resource_size: ptr to update
 */
पूर्णांक devlink_resource_size_get(काष्ठा devlink *devlink,
			      u64 resource_id,
			      u64 *p_resource_size)
अणु
	काष्ठा devlink_resource *resource;
	पूर्णांक err = 0;

	mutex_lock(&devlink->lock);
	resource = devlink_resource_find(devlink, शून्य, resource_id);
	अगर (!resource) अणु
		err = -EINVAL;
		जाओ out;
	पूर्ण
	*p_resource_size = resource->size_new;
	resource->size = resource->size_new;
out:
	mutex_unlock(&devlink->lock);
	वापस err;
पूर्ण
EXPORT_SYMBOL_GPL(devlink_resource_size_get);

/**
 *	devlink_dpipe_table_resource_set - set the resource id
 *
 *	@devlink: devlink
 *	@table_name: table name
 *	@resource_id: resource id
 *	@resource_units: number of resource's units consumed per table's entry
 */
पूर्णांक devlink_dpipe_table_resource_set(काष्ठा devlink *devlink,
				     स्थिर अक्षर *table_name, u64 resource_id,
				     u64 resource_units)
अणु
	काष्ठा devlink_dpipe_table *table;
	पूर्णांक err = 0;

	mutex_lock(&devlink->lock);
	table = devlink_dpipe_table_find(&devlink->dpipe_table_list,
					 table_name, devlink);
	अगर (!table) अणु
		err = -EINVAL;
		जाओ out;
	पूर्ण
	table->resource_id = resource_id;
	table->resource_units = resource_units;
	table->resource_valid = true;
out:
	mutex_unlock(&devlink->lock);
	वापस err;
पूर्ण
EXPORT_SYMBOL_GPL(devlink_dpipe_table_resource_set);

/**
 *	devlink_resource_occ_get_रेजिस्टर - रेजिस्टर occupancy getter
 *
 *	@devlink: devlink
 *	@resource_id: resource id
 *	@occ_get: occupancy getter callback
 *	@occ_get_priv: occupancy getter callback priv
 */
व्योम devlink_resource_occ_get_रेजिस्टर(काष्ठा devlink *devlink,
				       u64 resource_id,
				       devlink_resource_occ_get_t *occ_get,
				       व्योम *occ_get_priv)
अणु
	काष्ठा devlink_resource *resource;

	mutex_lock(&devlink->lock);
	resource = devlink_resource_find(devlink, शून्य, resource_id);
	अगर (WARN_ON(!resource))
		जाओ out;
	WARN_ON(resource->occ_get);

	resource->occ_get = occ_get;
	resource->occ_get_priv = occ_get_priv;
out:
	mutex_unlock(&devlink->lock);
पूर्ण
EXPORT_SYMBOL_GPL(devlink_resource_occ_get_रेजिस्टर);

/**
 *	devlink_resource_occ_get_unरेजिस्टर - unरेजिस्टर occupancy getter
 *
 *	@devlink: devlink
 *	@resource_id: resource id
 */
व्योम devlink_resource_occ_get_unरेजिस्टर(काष्ठा devlink *devlink,
					 u64 resource_id)
अणु
	काष्ठा devlink_resource *resource;

	mutex_lock(&devlink->lock);
	resource = devlink_resource_find(devlink, शून्य, resource_id);
	अगर (WARN_ON(!resource))
		जाओ out;
	WARN_ON(!resource->occ_get);

	resource->occ_get = शून्य;
	resource->occ_get_priv = शून्य;
out:
	mutex_unlock(&devlink->lock);
पूर्ण
EXPORT_SYMBOL_GPL(devlink_resource_occ_get_unरेजिस्टर);

अटल पूर्णांक devlink_param_verअगरy(स्थिर काष्ठा devlink_param *param)
अणु
	अगर (!param || !param->name || !param->supported_cmodes)
		वापस -EINVAL;
	अगर (param->generic)
		वापस devlink_param_generic_verअगरy(param);
	अन्यथा
		वापस devlink_param_driver_verअगरy(param);
पूर्ण

अटल पूर्णांक __devlink_params_रेजिस्टर(काष्ठा devlink *devlink,
				     अचिन्हित पूर्णांक port_index,
				     काष्ठा list_head *param_list,
				     स्थिर काष्ठा devlink_param *params,
				     माप_प्रकार params_count,
				     क्रमागत devlink_command reg_cmd,
				     क्रमागत devlink_command unreg_cmd)
अणु
	स्थिर काष्ठा devlink_param *param = params;
	पूर्णांक i;
	पूर्णांक err;

	mutex_lock(&devlink->lock);
	क्रम (i = 0; i < params_count; i++, param++) अणु
		err = devlink_param_verअगरy(param);
		अगर (err)
			जाओ rollback;

		err = devlink_param_रेजिस्टर_one(devlink, port_index,
						 param_list, param, reg_cmd);
		अगर (err)
			जाओ rollback;
	पूर्ण

	mutex_unlock(&devlink->lock);
	वापस 0;

rollback:
	अगर (!i)
		जाओ unlock;
	क्रम (param--; i > 0; i--, param--)
		devlink_param_unरेजिस्टर_one(devlink, port_index, param_list,
					     param, unreg_cmd);
unlock:
	mutex_unlock(&devlink->lock);
	वापस err;
पूर्ण

अटल व्योम __devlink_params_unरेजिस्टर(काष्ठा devlink *devlink,
					अचिन्हित पूर्णांक port_index,
					काष्ठा list_head *param_list,
					स्थिर काष्ठा devlink_param *params,
					माप_प्रकार params_count,
					क्रमागत devlink_command cmd)
अणु
	स्थिर काष्ठा devlink_param *param = params;
	पूर्णांक i;

	mutex_lock(&devlink->lock);
	क्रम (i = 0; i < params_count; i++, param++)
		devlink_param_unरेजिस्टर_one(devlink, 0, param_list, param,
					     cmd);
	mutex_unlock(&devlink->lock);
पूर्ण

/**
 *	devlink_params_रेजिस्टर - रेजिस्टर configuration parameters
 *
 *	@devlink: devlink
 *	@params: configuration parameters array
 *	@params_count: number of parameters provided
 *
 *	Register the configuration parameters supported by the driver.
 */
पूर्णांक devlink_params_रेजिस्टर(काष्ठा devlink *devlink,
			    स्थिर काष्ठा devlink_param *params,
			    माप_प्रकार params_count)
अणु
	वापस __devlink_params_रेजिस्टर(devlink, 0, &devlink->param_list,
					 params, params_count,
					 DEVLINK_CMD_PARAM_NEW,
					 DEVLINK_CMD_PARAM_DEL);
पूर्ण
EXPORT_SYMBOL_GPL(devlink_params_रेजिस्टर);

/**
 *	devlink_params_unरेजिस्टर - unरेजिस्टर configuration parameters
 *	@devlink: devlink
 *	@params: configuration parameters to unरेजिस्टर
 *	@params_count: number of parameters provided
 */
व्योम devlink_params_unरेजिस्टर(काष्ठा devlink *devlink,
			       स्थिर काष्ठा devlink_param *params,
			       माप_प्रकार params_count)
अणु
	वापस __devlink_params_unरेजिस्टर(devlink, 0, &devlink->param_list,
					   params, params_count,
					   DEVLINK_CMD_PARAM_DEL);
पूर्ण
EXPORT_SYMBOL_GPL(devlink_params_unरेजिस्टर);

/**
 *	devlink_params_publish - publish configuration parameters
 *
 *	@devlink: devlink
 *
 *	Publish previously रेजिस्टरed configuration parameters.
 */
व्योम devlink_params_publish(काष्ठा devlink *devlink)
अणु
	काष्ठा devlink_param_item *param_item;

	list_क्रम_each_entry(param_item, &devlink->param_list, list) अणु
		अगर (param_item->published)
			जारी;
		param_item->published = true;
		devlink_param_notअगरy(devlink, 0, param_item,
				     DEVLINK_CMD_PARAM_NEW);
	पूर्ण
पूर्ण
EXPORT_SYMBOL_GPL(devlink_params_publish);

/**
 *	devlink_params_unpublish - unpublish configuration parameters
 *
 *	@devlink: devlink
 *
 *	Unpublish previously रेजिस्टरed configuration parameters.
 */
व्योम devlink_params_unpublish(काष्ठा devlink *devlink)
अणु
	काष्ठा devlink_param_item *param_item;

	list_क्रम_each_entry(param_item, &devlink->param_list, list) अणु
		अगर (!param_item->published)
			जारी;
		param_item->published = false;
		devlink_param_notअगरy(devlink, 0, param_item,
				     DEVLINK_CMD_PARAM_DEL);
	पूर्ण
पूर्ण
EXPORT_SYMBOL_GPL(devlink_params_unpublish);

/**
 *	devlink_port_params_रेजिस्टर - रेजिस्टर port configuration parameters
 *
 *	@devlink_port: devlink port
 *	@params: configuration parameters array
 *	@params_count: number of parameters provided
 *
 *	Register the configuration parameters supported by the port.
 */
पूर्णांक devlink_port_params_रेजिस्टर(काष्ठा devlink_port *devlink_port,
				 स्थिर काष्ठा devlink_param *params,
				 माप_प्रकार params_count)
अणु
	वापस __devlink_params_रेजिस्टर(devlink_port->devlink,
					 devlink_port->index,
					 &devlink_port->param_list, params,
					 params_count,
					 DEVLINK_CMD_PORT_PARAM_NEW,
					 DEVLINK_CMD_PORT_PARAM_DEL);
पूर्ण
EXPORT_SYMBOL_GPL(devlink_port_params_रेजिस्टर);

/**
 *	devlink_port_params_unरेजिस्टर - unरेजिस्टर port configuration
 *	parameters
 *
 *	@devlink_port: devlink port
 *	@params: configuration parameters array
 *	@params_count: number of parameters provided
 */
व्योम devlink_port_params_unरेजिस्टर(काष्ठा devlink_port *devlink_port,
				    स्थिर काष्ठा devlink_param *params,
				    माप_प्रकार params_count)
अणु
	वापस __devlink_params_unरेजिस्टर(devlink_port->devlink,
					   devlink_port->index,
					   &devlink_port->param_list,
					   params, params_count,
					   DEVLINK_CMD_PORT_PARAM_DEL);
पूर्ण
EXPORT_SYMBOL_GPL(devlink_port_params_unरेजिस्टर);

अटल पूर्णांक
__devlink_param_driverinit_value_get(काष्ठा list_head *param_list, u32 param_id,
				     जोड़ devlink_param_value *init_val)
अणु
	काष्ठा devlink_param_item *param_item;

	param_item = devlink_param_find_by_id(param_list, param_id);
	अगर (!param_item)
		वापस -EINVAL;

	अगर (!param_item->driverinit_value_valid ||
	    !devlink_param_cmode_is_supported(param_item->param,
					      DEVLINK_PARAM_CMODE_DRIVERINIT))
		वापस -EOPNOTSUPP;

	अगर (param_item->param->type == DEVLINK_PARAM_TYPE_STRING)
		म_नकल(init_val->vstr, param_item->driverinit_value.vstr);
	अन्यथा
		*init_val = param_item->driverinit_value;

	वापस 0;
पूर्ण

अटल पूर्णांक
__devlink_param_driverinit_value_set(काष्ठा devlink *devlink,
				     अचिन्हित पूर्णांक port_index,
				     काष्ठा list_head *param_list, u32 param_id,
				     जोड़ devlink_param_value init_val,
				     क्रमागत devlink_command cmd)
अणु
	काष्ठा devlink_param_item *param_item;

	param_item = devlink_param_find_by_id(param_list, param_id);
	अगर (!param_item)
		वापस -EINVAL;

	अगर (!devlink_param_cmode_is_supported(param_item->param,
					      DEVLINK_PARAM_CMODE_DRIVERINIT))
		वापस -EOPNOTSUPP;

	अगर (param_item->param->type == DEVLINK_PARAM_TYPE_STRING)
		म_नकल(param_item->driverinit_value.vstr, init_val.vstr);
	अन्यथा
		param_item->driverinit_value = init_val;
	param_item->driverinit_value_valid = true;

	devlink_param_notअगरy(devlink, port_index, param_item, cmd);
	वापस 0;
पूर्ण

/**
 *	devlink_param_driverinit_value_get - get configuration parameter
 *					     value क्रम driver initializing
 *
 *	@devlink: devlink
 *	@param_id: parameter ID
 *	@init_val: value of parameter in driverinit configuration mode
 *
 *	This function should be used by the driver to get driverinit
 *	configuration क्रम initialization after reload command.
 */
पूर्णांक devlink_param_driverinit_value_get(काष्ठा devlink *devlink, u32 param_id,
				       जोड़ devlink_param_value *init_val)
अणु
	अगर (!devlink_reload_supported(devlink->ops))
		वापस -EOPNOTSUPP;

	वापस __devlink_param_driverinit_value_get(&devlink->param_list,
						    param_id, init_val);
पूर्ण
EXPORT_SYMBOL_GPL(devlink_param_driverinit_value_get);

/**
 *	devlink_param_driverinit_value_set - set value of configuration
 *					     parameter क्रम driverinit
 *					     configuration mode
 *
 *	@devlink: devlink
 *	@param_id: parameter ID
 *	@init_val: value of parameter to set क्रम driverinit configuration mode
 *
 *	This function should be used by the driver to set driverinit
 *	configuration mode शेष value.
 */
पूर्णांक devlink_param_driverinit_value_set(काष्ठा devlink *devlink, u32 param_id,
				       जोड़ devlink_param_value init_val)
अणु
	वापस __devlink_param_driverinit_value_set(devlink, 0,
						    &devlink->param_list,
						    param_id, init_val,
						    DEVLINK_CMD_PARAM_NEW);
पूर्ण
EXPORT_SYMBOL_GPL(devlink_param_driverinit_value_set);

/**
 *	devlink_port_param_driverinit_value_get - get configuration parameter
 *						value क्रम driver initializing
 *
 *	@devlink_port: devlink_port
 *	@param_id: parameter ID
 *	@init_val: value of parameter in driverinit configuration mode
 *
 *	This function should be used by the driver to get driverinit
 *	configuration क्रम initialization after reload command.
 */
पूर्णांक devlink_port_param_driverinit_value_get(काष्ठा devlink_port *devlink_port,
					    u32 param_id,
					    जोड़ devlink_param_value *init_val)
अणु
	काष्ठा devlink *devlink = devlink_port->devlink;

	अगर (!devlink_reload_supported(devlink->ops))
		वापस -EOPNOTSUPP;

	वापस __devlink_param_driverinit_value_get(&devlink_port->param_list,
						    param_id, init_val);
पूर्ण
EXPORT_SYMBOL_GPL(devlink_port_param_driverinit_value_get);

/**
 *     devlink_port_param_driverinit_value_set - set value of configuration
 *                                               parameter क्रम driverinit
 *                                               configuration mode
 *
 *     @devlink_port: devlink_port
 *     @param_id: parameter ID
 *     @init_val: value of parameter to set क्रम driverinit configuration mode
 *
 *     This function should be used by the driver to set driverinit
 *     configuration mode शेष value.
 */
पूर्णांक devlink_port_param_driverinit_value_set(काष्ठा devlink_port *devlink_port,
					    u32 param_id,
					    जोड़ devlink_param_value init_val)
अणु
	वापस __devlink_param_driverinit_value_set(devlink_port->devlink,
						    devlink_port->index,
						    &devlink_port->param_list,
						    param_id, init_val,
						    DEVLINK_CMD_PORT_PARAM_NEW);
पूर्ण
EXPORT_SYMBOL_GPL(devlink_port_param_driverinit_value_set);

/**
 *	devlink_param_value_changed - notअगरy devlink on a parameter's value
 *				      change. Should be called by the driver
 *				      right after the change.
 *
 *	@devlink: devlink
 *	@param_id: parameter ID
 *
 *	This function should be used by the driver to notअगरy devlink on value
 *	change, excluding driverinit configuration mode.
 *	For driverinit configuration mode driver should use the function
 */
व्योम devlink_param_value_changed(काष्ठा devlink *devlink, u32 param_id)
अणु
	काष्ठा devlink_param_item *param_item;

	param_item = devlink_param_find_by_id(&devlink->param_list, param_id);
	WARN_ON(!param_item);

	devlink_param_notअगरy(devlink, 0, param_item, DEVLINK_CMD_PARAM_NEW);
पूर्ण
EXPORT_SYMBOL_GPL(devlink_param_value_changed);

/**
 *     devlink_port_param_value_changed - notअगरy devlink on a parameter's value
 *                                      change. Should be called by the driver
 *                                      right after the change.
 *
 *     @devlink_port: devlink_port
 *     @param_id: parameter ID
 *
 *     This function should be used by the driver to notअगरy devlink on value
 *     change, excluding driverinit configuration mode.
 *     For driverinit configuration mode driver should use the function
 *     devlink_port_param_driverinit_value_set() instead.
 */
व्योम devlink_port_param_value_changed(काष्ठा devlink_port *devlink_port,
				      u32 param_id)
अणु
	काष्ठा devlink_param_item *param_item;

	param_item = devlink_param_find_by_id(&devlink_port->param_list,
					      param_id);
	WARN_ON(!param_item);

	devlink_param_notअगरy(devlink_port->devlink, devlink_port->index,
			     param_item, DEVLINK_CMD_PORT_PARAM_NEW);
पूर्ण
EXPORT_SYMBOL_GPL(devlink_port_param_value_changed);

/**
 *	devlink_param_value_str_fill - Safely fill-up the string preventing
 *				       from overflow of the pपुनः_स्मृतिated buffer
 *
 *	@dst_val: destination devlink_param_value
 *	@src: source buffer
 */
व्योम devlink_param_value_str_fill(जोड़ devlink_param_value *dst_val,
				  स्थिर अक्षर *src)
अणु
	माप_प्रकार len;

	len = strlcpy(dst_val->vstr, src, __DEVLINK_PARAM_MAX_STRING_VALUE);
	WARN_ON(len >= __DEVLINK_PARAM_MAX_STRING_VALUE);
पूर्ण
EXPORT_SYMBOL_GPL(devlink_param_value_str_fill);

/**
 *	devlink_region_create - create a new address region
 *
 *	@devlink: devlink
 *	@ops: region operations and name
 *	@region_max_snapshots: Maximum supported number of snapshots क्रम region
 *	@region_size: size of region
 */
काष्ठा devlink_region *
devlink_region_create(काष्ठा devlink *devlink,
		      स्थिर काष्ठा devlink_region_ops *ops,
		      u32 region_max_snapshots, u64 region_size)
अणु
	काष्ठा devlink_region *region;
	पूर्णांक err = 0;

	अगर (WARN_ON(!ops) || WARN_ON(!ops->deकाष्ठाor))
		वापस ERR_PTR(-EINVAL);

	mutex_lock(&devlink->lock);

	अगर (devlink_region_get_by_name(devlink, ops->name)) अणु
		err = -EEXIST;
		जाओ unlock;
	पूर्ण

	region = kzalloc(माप(*region), GFP_KERNEL);
	अगर (!region) अणु
		err = -ENOMEM;
		जाओ unlock;
	पूर्ण

	region->devlink = devlink;
	region->max_snapshots = region_max_snapshots;
	region->ops = ops;
	region->size = region_size;
	INIT_LIST_HEAD(&region->snapshot_list);
	list_add_tail(&region->list, &devlink->region_list);
	devlink_nl_region_notअगरy(region, शून्य, DEVLINK_CMD_REGION_NEW);

	mutex_unlock(&devlink->lock);
	वापस region;

unlock:
	mutex_unlock(&devlink->lock);
	वापस ERR_PTR(err);
पूर्ण
EXPORT_SYMBOL_GPL(devlink_region_create);

/**
 *	devlink_port_region_create - create a new address region क्रम a port
 *
 *	@port: devlink port
 *	@ops: region operations and name
 *	@region_max_snapshots: Maximum supported number of snapshots क्रम region
 *	@region_size: size of region
 */
काष्ठा devlink_region *
devlink_port_region_create(काष्ठा devlink_port *port,
			   स्थिर काष्ठा devlink_port_region_ops *ops,
			   u32 region_max_snapshots, u64 region_size)
अणु
	काष्ठा devlink *devlink = port->devlink;
	काष्ठा devlink_region *region;
	पूर्णांक err = 0;

	अगर (WARN_ON(!ops) || WARN_ON(!ops->deकाष्ठाor))
		वापस ERR_PTR(-EINVAL);

	mutex_lock(&devlink->lock);

	अगर (devlink_port_region_get_by_name(port, ops->name)) अणु
		err = -EEXIST;
		जाओ unlock;
	पूर्ण

	region = kzalloc(माप(*region), GFP_KERNEL);
	अगर (!region) अणु
		err = -ENOMEM;
		जाओ unlock;
	पूर्ण

	region->devlink = devlink;
	region->port = port;
	region->max_snapshots = region_max_snapshots;
	region->port_ops = ops;
	region->size = region_size;
	INIT_LIST_HEAD(&region->snapshot_list);
	list_add_tail(&region->list, &port->region_list);
	devlink_nl_region_notअगरy(region, शून्य, DEVLINK_CMD_REGION_NEW);

	mutex_unlock(&devlink->lock);
	वापस region;

unlock:
	mutex_unlock(&devlink->lock);
	वापस ERR_PTR(err);
पूर्ण
EXPORT_SYMBOL_GPL(devlink_port_region_create);

/**
 *	devlink_region_destroy - destroy address region
 *
 *	@region: devlink region to destroy
 */
व्योम devlink_region_destroy(काष्ठा devlink_region *region)
अणु
	काष्ठा devlink *devlink = region->devlink;
	काष्ठा devlink_snapshot *snapshot, *ts;

	mutex_lock(&devlink->lock);

	/* Free all snapshots of region */
	list_क्रम_each_entry_safe(snapshot, ts, &region->snapshot_list, list)
		devlink_region_snapshot_del(region, snapshot);

	list_del(&region->list);

	devlink_nl_region_notअगरy(region, शून्य, DEVLINK_CMD_REGION_DEL);
	mutex_unlock(&devlink->lock);
	kमुक्त(region);
पूर्ण
EXPORT_SYMBOL_GPL(devlink_region_destroy);

/**
 *	devlink_region_snapshot_id_get - get snapshot ID
 *
 *	This callback should be called when adding a new snapshot,
 *	Driver should use the same id क्रम multiple snapshots taken
 *	on multiple regions at the same समय/by the same trigger.
 *
 *	The caller of this function must use devlink_region_snapshot_id_put
 *	when finished creating regions using this id.
 *
 *	Returns zero on success, or a negative error code on failure.
 *
 *	@devlink: devlink
 *	@id: storage to वापस id
 */
पूर्णांक devlink_region_snapshot_id_get(काष्ठा devlink *devlink, u32 *id)
अणु
	पूर्णांक err;

	mutex_lock(&devlink->lock);
	err = __devlink_region_snapshot_id_get(devlink, id);
	mutex_unlock(&devlink->lock);

	वापस err;
पूर्ण
EXPORT_SYMBOL_GPL(devlink_region_snapshot_id_get);

/**
 *	devlink_region_snapshot_id_put - put snapshot ID reference
 *
 *	This should be called by a driver after finishing creating snapshots
 *	with an id. Doing so ensures that the ID can later be released in the
 *	event that all snapshots using it have been destroyed.
 *
 *	@devlink: devlink
 *	@id: id to release reference on
 */
व्योम devlink_region_snapshot_id_put(काष्ठा devlink *devlink, u32 id)
अणु
	mutex_lock(&devlink->lock);
	__devlink_snapshot_id_decrement(devlink, id);
	mutex_unlock(&devlink->lock);
पूर्ण
EXPORT_SYMBOL_GPL(devlink_region_snapshot_id_put);

/**
 *	devlink_region_snapshot_create - create a new snapshot
 *	This will add a new snapshot of a region. The snapshot
 *	will be stored on the region काष्ठा and can be accessed
 *	from devlink. This is useful क्रम future analyses of snapshots.
 *	Multiple snapshots can be created on a region.
 *	The @snapshot_id should be obtained using the getter function.
 *
 *	@region: devlink region of the snapshot
 *	@data: snapshot data
 *	@snapshot_id: snapshot id to be created
 */
पूर्णांक devlink_region_snapshot_create(काष्ठा devlink_region *region,
				   u8 *data, u32 snapshot_id)
अणु
	काष्ठा devlink *devlink = region->devlink;
	पूर्णांक err;

	mutex_lock(&devlink->lock);
	err = __devlink_region_snapshot_create(region, data, snapshot_id);
	mutex_unlock(&devlink->lock);

	वापस err;
पूर्ण
EXPORT_SYMBOL_GPL(devlink_region_snapshot_create);

#घोषणा DEVLINK_TRAP(_id, _type)					      \
	अणु								      \
		.type = DEVLINK_TRAP_TYPE_##_type,			      \
		.id = DEVLINK_TRAP_GENERIC_ID_##_id,			      \
		.name = DEVLINK_TRAP_GENERIC_NAME_##_id,		      \
	पूर्ण

अटल स्थिर काष्ठा devlink_trap devlink_trap_generic[] = अणु
	DEVLINK_TRAP(SMAC_MC, DROP),
	DEVLINK_TRAP(VLAN_TAG_MISMATCH, DROP),
	DEVLINK_TRAP(INGRESS_VLAN_FILTER, DROP),
	DEVLINK_TRAP(INGRESS_STP_FILTER, DROP),
	DEVLINK_TRAP(EMPTY_TX_LIST, DROP),
	DEVLINK_TRAP(PORT_LOOPBACK_FILTER, DROP),
	DEVLINK_TRAP(BLACKHOLE_ROUTE, DROP),
	DEVLINK_TRAP(TTL_ERROR, EXCEPTION),
	DEVLINK_TRAP(TAIL_DROP, DROP),
	DEVLINK_TRAP(NON_IP_PACKET, DROP),
	DEVLINK_TRAP(UC_DIP_MC_DMAC, DROP),
	DEVLINK_TRAP(DIP_LB, DROP),
	DEVLINK_TRAP(SIP_MC, DROP),
	DEVLINK_TRAP(SIP_LB, DROP),
	DEVLINK_TRAP(CORRUPTED_IP_HDR, DROP),
	DEVLINK_TRAP(IPV4_SIP_BC, DROP),
	DEVLINK_TRAP(IPV6_MC_DIP_RESERVED_SCOPE, DROP),
	DEVLINK_TRAP(IPV6_MC_DIP_INTERFACE_LOCAL_SCOPE, DROP),
	DEVLINK_TRAP(MTU_ERROR, EXCEPTION),
	DEVLINK_TRAP(UNRESOLVED_NEIGH, EXCEPTION),
	DEVLINK_TRAP(RPF, EXCEPTION),
	DEVLINK_TRAP(REJECT_ROUTE, EXCEPTION),
	DEVLINK_TRAP(IPV4_LPM_UNICAST_MISS, EXCEPTION),
	DEVLINK_TRAP(IPV6_LPM_UNICAST_MISS, EXCEPTION),
	DEVLINK_TRAP(NON_ROUTABLE, DROP),
	DEVLINK_TRAP(DECAP_ERROR, EXCEPTION),
	DEVLINK_TRAP(OVERLAY_SMAC_MC, DROP),
	DEVLINK_TRAP(INGRESS_FLOW_ACTION_DROP, DROP),
	DEVLINK_TRAP(EGRESS_FLOW_ACTION_DROP, DROP),
	DEVLINK_TRAP(STP, CONTROL),
	DEVLINK_TRAP(LACP, CONTROL),
	DEVLINK_TRAP(LLDP, CONTROL),
	DEVLINK_TRAP(IGMP_QUERY, CONTROL),
	DEVLINK_TRAP(IGMP_V1_REPORT, CONTROL),
	DEVLINK_TRAP(IGMP_V2_REPORT, CONTROL),
	DEVLINK_TRAP(IGMP_V3_REPORT, CONTROL),
	DEVLINK_TRAP(IGMP_V2_LEAVE, CONTROL),
	DEVLINK_TRAP(MLD_QUERY, CONTROL),
	DEVLINK_TRAP(MLD_V1_REPORT, CONTROL),
	DEVLINK_TRAP(MLD_V2_REPORT, CONTROL),
	DEVLINK_TRAP(MLD_V1_DONE, CONTROL),
	DEVLINK_TRAP(IPV4_DHCP, CONTROL),
	DEVLINK_TRAP(IPV6_DHCP, CONTROL),
	DEVLINK_TRAP(ARP_REQUEST, CONTROL),
	DEVLINK_TRAP(ARP_RESPONSE, CONTROL),
	DEVLINK_TRAP(ARP_OVERLAY, CONTROL),
	DEVLINK_TRAP(IPV6_NEIGH_SOLICIT, CONTROL),
	DEVLINK_TRAP(IPV6_NEIGH_ADVERT, CONTROL),
	DEVLINK_TRAP(IPV4_BFD, CONTROL),
	DEVLINK_TRAP(IPV6_BFD, CONTROL),
	DEVLINK_TRAP(IPV4_OSPF, CONTROL),
	DEVLINK_TRAP(IPV6_OSPF, CONTROL),
	DEVLINK_TRAP(IPV4_BGP, CONTROL),
	DEVLINK_TRAP(IPV6_BGP, CONTROL),
	DEVLINK_TRAP(IPV4_VRRP, CONTROL),
	DEVLINK_TRAP(IPV6_VRRP, CONTROL),
	DEVLINK_TRAP(IPV4_PIM, CONTROL),
	DEVLINK_TRAP(IPV6_PIM, CONTROL),
	DEVLINK_TRAP(UC_LB, CONTROL),
	DEVLINK_TRAP(LOCAL_ROUTE, CONTROL),
	DEVLINK_TRAP(EXTERNAL_ROUTE, CONTROL),
	DEVLINK_TRAP(IPV6_UC_DIP_LINK_LOCAL_SCOPE, CONTROL),
	DEVLINK_TRAP(IPV6_DIP_ALL_NODES, CONTROL),
	DEVLINK_TRAP(IPV6_DIP_ALL_ROUTERS, CONTROL),
	DEVLINK_TRAP(IPV6_ROUTER_SOLICIT, CONTROL),
	DEVLINK_TRAP(IPV6_ROUTER_ADVERT, CONTROL),
	DEVLINK_TRAP(IPV6_REसूचीECT, CONTROL),
	DEVLINK_TRAP(IPV4_ROUTER_ALERT, CONTROL),
	DEVLINK_TRAP(IPV6_ROUTER_ALERT, CONTROL),
	DEVLINK_TRAP(PTP_EVENT, CONTROL),
	DEVLINK_TRAP(PTP_GENERAL, CONTROL),
	DEVLINK_TRAP(FLOW_ACTION_SAMPLE, CONTROL),
	DEVLINK_TRAP(FLOW_ACTION_TRAP, CONTROL),
	DEVLINK_TRAP(EARLY_DROP, DROP),
	DEVLINK_TRAP(VXLAN_PARSING, DROP),
	DEVLINK_TRAP(LLC_SNAP_PARSING, DROP),
	DEVLINK_TRAP(VLAN_PARSING, DROP),
	DEVLINK_TRAP(PPPOE_PPP_PARSING, DROP),
	DEVLINK_TRAP(MPLS_PARSING, DROP),
	DEVLINK_TRAP(ARP_PARSING, DROP),
	DEVLINK_TRAP(IP_1_PARSING, DROP),
	DEVLINK_TRAP(IP_N_PARSING, DROP),
	DEVLINK_TRAP(GRE_PARSING, DROP),
	DEVLINK_TRAP(UDP_PARSING, DROP),
	DEVLINK_TRAP(TCP_PARSING, DROP),
	DEVLINK_TRAP(IPSEC_PARSING, DROP),
	DEVLINK_TRAP(SCTP_PARSING, DROP),
	DEVLINK_TRAP(DCCP_PARSING, DROP),
	DEVLINK_TRAP(GTP_PARSING, DROP),
	DEVLINK_TRAP(ESP_PARSING, DROP),
	DEVLINK_TRAP(BLACKHOLE_NEXTHOP, DROP),
	DEVLINK_TRAP(DMAC_FILTER, DROP),
पूर्ण;

#घोषणा DEVLINK_TRAP_GROUP(_id)						      \
	अणु								      \
		.id = DEVLINK_TRAP_GROUP_GENERIC_ID_##_id,		      \
		.name = DEVLINK_TRAP_GROUP_GENERIC_NAME_##_id,		      \
	पूर्ण

अटल स्थिर काष्ठा devlink_trap_group devlink_trap_group_generic[] = अणु
	DEVLINK_TRAP_GROUP(L2_DROPS),
	DEVLINK_TRAP_GROUP(L3_DROPS),
	DEVLINK_TRAP_GROUP(L3_EXCEPTIONS),
	DEVLINK_TRAP_GROUP(BUFFER_DROPS),
	DEVLINK_TRAP_GROUP(TUNNEL_DROPS),
	DEVLINK_TRAP_GROUP(ACL_DROPS),
	DEVLINK_TRAP_GROUP(STP),
	DEVLINK_TRAP_GROUP(LACP),
	DEVLINK_TRAP_GROUP(LLDP),
	DEVLINK_TRAP_GROUP(MC_SNOOPING),
	DEVLINK_TRAP_GROUP(DHCP),
	DEVLINK_TRAP_GROUP(NEIGH_DISCOVERY),
	DEVLINK_TRAP_GROUP(BFD),
	DEVLINK_TRAP_GROUP(OSPF),
	DEVLINK_TRAP_GROUP(BGP),
	DEVLINK_TRAP_GROUP(VRRP),
	DEVLINK_TRAP_GROUP(PIM),
	DEVLINK_TRAP_GROUP(UC_LB),
	DEVLINK_TRAP_GROUP(LOCAL_DELIVERY),
	DEVLINK_TRAP_GROUP(EXTERNAL_DELIVERY),
	DEVLINK_TRAP_GROUP(IPV6),
	DEVLINK_TRAP_GROUP(PTP_EVENT),
	DEVLINK_TRAP_GROUP(PTP_GENERAL),
	DEVLINK_TRAP_GROUP(ACL_SAMPLE),
	DEVLINK_TRAP_GROUP(ACL_TRAP),
	DEVLINK_TRAP_GROUP(PARSER_ERROR_DROPS),
पूर्ण;

अटल पूर्णांक devlink_trap_generic_verअगरy(स्थिर काष्ठा devlink_trap *trap)
अणु
	अगर (trap->id > DEVLINK_TRAP_GENERIC_ID_MAX)
		वापस -EINVAL;

	अगर (म_भेद(trap->name, devlink_trap_generic[trap->id].name))
		वापस -EINVAL;

	अगर (trap->type != devlink_trap_generic[trap->id].type)
		वापस -EINVAL;

	वापस 0;
पूर्ण

अटल पूर्णांक devlink_trap_driver_verअगरy(स्थिर काष्ठा devlink_trap *trap)
अणु
	पूर्णांक i;

	अगर (trap->id <= DEVLINK_TRAP_GENERIC_ID_MAX)
		वापस -EINVAL;

	क्रम (i = 0; i < ARRAY_SIZE(devlink_trap_generic); i++) अणु
		अगर (!म_भेद(trap->name, devlink_trap_generic[i].name))
			वापस -EEXIST;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक devlink_trap_verअगरy(स्थिर काष्ठा devlink_trap *trap)
अणु
	अगर (!trap || !trap->name)
		वापस -EINVAL;

	अगर (trap->generic)
		वापस devlink_trap_generic_verअगरy(trap);
	अन्यथा
		वापस devlink_trap_driver_verअगरy(trap);
पूर्ण

अटल पूर्णांक
devlink_trap_group_generic_verअगरy(स्थिर काष्ठा devlink_trap_group *group)
अणु
	अगर (group->id > DEVLINK_TRAP_GROUP_GENERIC_ID_MAX)
		वापस -EINVAL;

	अगर (म_भेद(group->name, devlink_trap_group_generic[group->id].name))
		वापस -EINVAL;

	वापस 0;
पूर्ण

अटल पूर्णांक
devlink_trap_group_driver_verअगरy(स्थिर काष्ठा devlink_trap_group *group)
अणु
	पूर्णांक i;

	अगर (group->id <= DEVLINK_TRAP_GROUP_GENERIC_ID_MAX)
		वापस -EINVAL;

	क्रम (i = 0; i < ARRAY_SIZE(devlink_trap_group_generic); i++) अणु
		अगर (!म_भेद(group->name, devlink_trap_group_generic[i].name))
			वापस -EEXIST;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक devlink_trap_group_verअगरy(स्थिर काष्ठा devlink_trap_group *group)
अणु
	अगर (group->generic)
		वापस devlink_trap_group_generic_verअगरy(group);
	अन्यथा
		वापस devlink_trap_group_driver_verअगरy(group);
पूर्ण

अटल व्योम
devlink_trap_group_notअगरy(काष्ठा devlink *devlink,
			  स्थिर काष्ठा devlink_trap_group_item *group_item,
			  क्रमागत devlink_command cmd)
अणु
	काष्ठा sk_buff *msg;
	पूर्णांक err;

	WARN_ON_ONCE(cmd != DEVLINK_CMD_TRAP_GROUP_NEW &&
		     cmd != DEVLINK_CMD_TRAP_GROUP_DEL);

	msg = nlmsg_new(NLMSG_DEFAULT_SIZE, GFP_KERNEL);
	अगर (!msg)
		वापस;

	err = devlink_nl_trap_group_fill(msg, devlink, group_item, cmd, 0, 0,
					 0);
	अगर (err) अणु
		nlmsg_मुक्त(msg);
		वापस;
	पूर्ण

	genlmsg_multicast_netns(&devlink_nl_family, devlink_net(devlink),
				msg, 0, DEVLINK_MCGRP_CONFIG, GFP_KERNEL);
पूर्ण

अटल पूर्णांक
devlink_trap_item_group_link(काष्ठा devlink *devlink,
			     काष्ठा devlink_trap_item *trap_item)
अणु
	u16 group_id = trap_item->trap->init_group_id;
	काष्ठा devlink_trap_group_item *group_item;

	group_item = devlink_trap_group_item_lookup_by_id(devlink, group_id);
	अगर (WARN_ON_ONCE(!group_item))
		वापस -EINVAL;

	trap_item->group_item = group_item;

	वापस 0;
पूर्ण

अटल व्योम devlink_trap_notअगरy(काष्ठा devlink *devlink,
				स्थिर काष्ठा devlink_trap_item *trap_item,
				क्रमागत devlink_command cmd)
अणु
	काष्ठा sk_buff *msg;
	पूर्णांक err;

	WARN_ON_ONCE(cmd != DEVLINK_CMD_TRAP_NEW &&
		     cmd != DEVLINK_CMD_TRAP_DEL);

	msg = nlmsg_new(NLMSG_DEFAULT_SIZE, GFP_KERNEL);
	अगर (!msg)
		वापस;

	err = devlink_nl_trap_fill(msg, devlink, trap_item, cmd, 0, 0, 0);
	अगर (err) अणु
		nlmsg_मुक्त(msg);
		वापस;
	पूर्ण

	genlmsg_multicast_netns(&devlink_nl_family, devlink_net(devlink),
				msg, 0, DEVLINK_MCGRP_CONFIG, GFP_KERNEL);
पूर्ण

अटल पूर्णांक
devlink_trap_रेजिस्टर(काष्ठा devlink *devlink,
		      स्थिर काष्ठा devlink_trap *trap, व्योम *priv)
अणु
	काष्ठा devlink_trap_item *trap_item;
	पूर्णांक err;

	अगर (devlink_trap_item_lookup(devlink, trap->name))
		वापस -EEXIST;

	trap_item = kzalloc(माप(*trap_item), GFP_KERNEL);
	अगर (!trap_item)
		वापस -ENOMEM;

	trap_item->stats = netdev_alloc_pcpu_stats(काष्ठा devlink_stats);
	अगर (!trap_item->stats) अणु
		err = -ENOMEM;
		जाओ err_stats_alloc;
	पूर्ण

	trap_item->trap = trap;
	trap_item->action = trap->init_action;
	trap_item->priv = priv;

	err = devlink_trap_item_group_link(devlink, trap_item);
	अगर (err)
		जाओ err_group_link;

	err = devlink->ops->trap_init(devlink, trap, trap_item);
	अगर (err)
		जाओ err_trap_init;

	list_add_tail(&trap_item->list, &devlink->trap_list);
	devlink_trap_notअगरy(devlink, trap_item, DEVLINK_CMD_TRAP_NEW);

	वापस 0;

err_trap_init:
err_group_link:
	मुक्त_percpu(trap_item->stats);
err_stats_alloc:
	kमुक्त(trap_item);
	वापस err;
पूर्ण

अटल व्योम devlink_trap_unरेजिस्टर(काष्ठा devlink *devlink,
				    स्थिर काष्ठा devlink_trap *trap)
अणु
	काष्ठा devlink_trap_item *trap_item;

	trap_item = devlink_trap_item_lookup(devlink, trap->name);
	अगर (WARN_ON_ONCE(!trap_item))
		वापस;

	devlink_trap_notअगरy(devlink, trap_item, DEVLINK_CMD_TRAP_DEL);
	list_del(&trap_item->list);
	अगर (devlink->ops->trap_fini)
		devlink->ops->trap_fini(devlink, trap, trap_item);
	मुक्त_percpu(trap_item->stats);
	kमुक्त(trap_item);
पूर्ण

अटल व्योम devlink_trap_disable(काष्ठा devlink *devlink,
				 स्थिर काष्ठा devlink_trap *trap)
अणु
	काष्ठा devlink_trap_item *trap_item;

	trap_item = devlink_trap_item_lookup(devlink, trap->name);
	अगर (WARN_ON_ONCE(!trap_item))
		वापस;

	devlink->ops->trap_action_set(devlink, trap, DEVLINK_TRAP_ACTION_DROP,
				      शून्य);
	trap_item->action = DEVLINK_TRAP_ACTION_DROP;
पूर्ण

/**
 * devlink_traps_रेजिस्टर - Register packet traps with devlink.
 * @devlink: devlink.
 * @traps: Packet traps.
 * @traps_count: Count of provided packet traps.
 * @priv: Driver निजी inक्रमmation.
 *
 * Return: Non-zero value on failure.
 */
पूर्णांक devlink_traps_रेजिस्टर(काष्ठा devlink *devlink,
			   स्थिर काष्ठा devlink_trap *traps,
			   माप_प्रकार traps_count, व्योम *priv)
अणु
	पूर्णांक i, err;

	अगर (!devlink->ops->trap_init || !devlink->ops->trap_action_set)
		वापस -EINVAL;

	mutex_lock(&devlink->lock);
	क्रम (i = 0; i < traps_count; i++) अणु
		स्थिर काष्ठा devlink_trap *trap = &traps[i];

		err = devlink_trap_verअगरy(trap);
		अगर (err)
			जाओ err_trap_verअगरy;

		err = devlink_trap_रेजिस्टर(devlink, trap, priv);
		अगर (err)
			जाओ err_trap_रेजिस्टर;
	पूर्ण
	mutex_unlock(&devlink->lock);

	वापस 0;

err_trap_रेजिस्टर:
err_trap_verअगरy:
	क्रम (i--; i >= 0; i--)
		devlink_trap_unरेजिस्टर(devlink, &traps[i]);
	mutex_unlock(&devlink->lock);
	वापस err;
पूर्ण
EXPORT_SYMBOL_GPL(devlink_traps_रेजिस्टर);

/**
 * devlink_traps_unरेजिस्टर - Unरेजिस्टर packet traps from devlink.
 * @devlink: devlink.
 * @traps: Packet traps.
 * @traps_count: Count of provided packet traps.
 */
व्योम devlink_traps_unरेजिस्टर(काष्ठा devlink *devlink,
			      स्थिर काष्ठा devlink_trap *traps,
			      माप_प्रकार traps_count)
अणु
	पूर्णांक i;

	mutex_lock(&devlink->lock);
	/* Make sure we करो not have any packets in-flight जबतक unरेजिस्टरing
	 * traps by disabling all of them and रुकोing क्रम a grace period.
	 */
	क्रम (i = traps_count - 1; i >= 0; i--)
		devlink_trap_disable(devlink, &traps[i]);
	synchronize_rcu();
	क्रम (i = traps_count - 1; i >= 0; i--)
		devlink_trap_unरेजिस्टर(devlink, &traps[i]);
	mutex_unlock(&devlink->lock);
पूर्ण
EXPORT_SYMBOL_GPL(devlink_traps_unरेजिस्टर);

अटल व्योम
devlink_trap_stats_update(काष्ठा devlink_stats __percpu *trap_stats,
			  माप_प्रकार skb_len)
अणु
	काष्ठा devlink_stats *stats;

	stats = this_cpu_ptr(trap_stats);
	u64_stats_update_begin(&stats->syncp);
	stats->rx_bytes += skb_len;
	stats->rx_packets++;
	u64_stats_update_end(&stats->syncp);
पूर्ण

अटल व्योम
devlink_trap_report_metadata_set(काष्ठा devlink_trap_metadata *metadata,
				 स्थिर काष्ठा devlink_trap_item *trap_item,
				 काष्ठा devlink_port *in_devlink_port,
				 स्थिर काष्ठा flow_action_cookie *fa_cookie)
अणु
	metadata->trap_name = trap_item->trap->name;
	metadata->trap_group_name = trap_item->group_item->group->name;
	metadata->fa_cookie = fa_cookie;
	metadata->trap_type = trap_item->trap->type;

	spin_lock(&in_devlink_port->type_lock);
	अगर (in_devlink_port->type == DEVLINK_PORT_TYPE_ETH)
		metadata->input_dev = in_devlink_port->type_dev;
	spin_unlock(&in_devlink_port->type_lock);
पूर्ण

/**
 * devlink_trap_report - Report trapped packet to drop monitor.
 * @devlink: devlink.
 * @skb: Trapped packet.
 * @trap_ctx: Trap context.
 * @in_devlink_port: Input devlink port.
 * @fa_cookie: Flow action cookie. Could be शून्य.
 */
व्योम devlink_trap_report(काष्ठा devlink *devlink, काष्ठा sk_buff *skb,
			 व्योम *trap_ctx, काष्ठा devlink_port *in_devlink_port,
			 स्थिर काष्ठा flow_action_cookie *fa_cookie)

अणु
	काष्ठा devlink_trap_item *trap_item = trap_ctx;

	devlink_trap_stats_update(trap_item->stats, skb->len);
	devlink_trap_stats_update(trap_item->group_item->stats, skb->len);

	अगर (trace_devlink_trap_report_enabled()) अणु
		काष्ठा devlink_trap_metadata metadata = अणुपूर्ण;

		devlink_trap_report_metadata_set(&metadata, trap_item,
						 in_devlink_port, fa_cookie);
		trace_devlink_trap_report(devlink, skb, &metadata);
	पूर्ण
पूर्ण
EXPORT_SYMBOL_GPL(devlink_trap_report);

/**
 * devlink_trap_ctx_priv - Trap context to driver निजी inक्रमmation.
 * @trap_ctx: Trap context.
 *
 * Return: Driver निजी inक्रमmation passed during registration.
 */
व्योम *devlink_trap_ctx_priv(व्योम *trap_ctx)
अणु
	काष्ठा devlink_trap_item *trap_item = trap_ctx;

	वापस trap_item->priv;
पूर्ण
EXPORT_SYMBOL_GPL(devlink_trap_ctx_priv);

अटल पूर्णांक
devlink_trap_group_item_policer_link(काष्ठा devlink *devlink,
				     काष्ठा devlink_trap_group_item *group_item)
अणु
	u32 policer_id = group_item->group->init_policer_id;
	काष्ठा devlink_trap_policer_item *policer_item;

	अगर (policer_id == 0)
		वापस 0;

	policer_item = devlink_trap_policer_item_lookup(devlink, policer_id);
	अगर (WARN_ON_ONCE(!policer_item))
		वापस -EINVAL;

	group_item->policer_item = policer_item;

	वापस 0;
पूर्ण

अटल पूर्णांक
devlink_trap_group_रेजिस्टर(काष्ठा devlink *devlink,
			    स्थिर काष्ठा devlink_trap_group *group)
अणु
	काष्ठा devlink_trap_group_item *group_item;
	पूर्णांक err;

	अगर (devlink_trap_group_item_lookup(devlink, group->name))
		वापस -EEXIST;

	group_item = kzalloc(माप(*group_item), GFP_KERNEL);
	अगर (!group_item)
		वापस -ENOMEM;

	group_item->stats = netdev_alloc_pcpu_stats(काष्ठा devlink_stats);
	अगर (!group_item->stats) अणु
		err = -ENOMEM;
		जाओ err_stats_alloc;
	पूर्ण

	group_item->group = group;

	err = devlink_trap_group_item_policer_link(devlink, group_item);
	अगर (err)
		जाओ err_policer_link;

	अगर (devlink->ops->trap_group_init) अणु
		err = devlink->ops->trap_group_init(devlink, group);
		अगर (err)
			जाओ err_group_init;
	पूर्ण

	list_add_tail(&group_item->list, &devlink->trap_group_list);
	devlink_trap_group_notअगरy(devlink, group_item,
				  DEVLINK_CMD_TRAP_GROUP_NEW);

	वापस 0;

err_group_init:
err_policer_link:
	मुक्त_percpu(group_item->stats);
err_stats_alloc:
	kमुक्त(group_item);
	वापस err;
पूर्ण

अटल व्योम
devlink_trap_group_unरेजिस्टर(काष्ठा devlink *devlink,
			      स्थिर काष्ठा devlink_trap_group *group)
अणु
	काष्ठा devlink_trap_group_item *group_item;

	group_item = devlink_trap_group_item_lookup(devlink, group->name);
	अगर (WARN_ON_ONCE(!group_item))
		वापस;

	devlink_trap_group_notअगरy(devlink, group_item,
				  DEVLINK_CMD_TRAP_GROUP_DEL);
	list_del(&group_item->list);
	मुक्त_percpu(group_item->stats);
	kमुक्त(group_item);
पूर्ण

/**
 * devlink_trap_groups_रेजिस्टर - Register packet trap groups with devlink.
 * @devlink: devlink.
 * @groups: Packet trap groups.
 * @groups_count: Count of provided packet trap groups.
 *
 * Return: Non-zero value on failure.
 */
पूर्णांक devlink_trap_groups_रेजिस्टर(काष्ठा devlink *devlink,
				 स्थिर काष्ठा devlink_trap_group *groups,
				 माप_प्रकार groups_count)
अणु
	पूर्णांक i, err;

	mutex_lock(&devlink->lock);
	क्रम (i = 0; i < groups_count; i++) अणु
		स्थिर काष्ठा devlink_trap_group *group = &groups[i];

		err = devlink_trap_group_verअगरy(group);
		अगर (err)
			जाओ err_trap_group_verअगरy;

		err = devlink_trap_group_रेजिस्टर(devlink, group);
		अगर (err)
			जाओ err_trap_group_रेजिस्टर;
	पूर्ण
	mutex_unlock(&devlink->lock);

	वापस 0;

err_trap_group_रेजिस्टर:
err_trap_group_verअगरy:
	क्रम (i--; i >= 0; i--)
		devlink_trap_group_unरेजिस्टर(devlink, &groups[i]);
	mutex_unlock(&devlink->lock);
	वापस err;
पूर्ण
EXPORT_SYMBOL_GPL(devlink_trap_groups_रेजिस्टर);

/**
 * devlink_trap_groups_unरेजिस्टर - Unरेजिस्टर packet trap groups from devlink.
 * @devlink: devlink.
 * @groups: Packet trap groups.
 * @groups_count: Count of provided packet trap groups.
 */
व्योम devlink_trap_groups_unरेजिस्टर(काष्ठा devlink *devlink,
				    स्थिर काष्ठा devlink_trap_group *groups,
				    माप_प्रकार groups_count)
अणु
	पूर्णांक i;

	mutex_lock(&devlink->lock);
	क्रम (i = groups_count - 1; i >= 0; i--)
		devlink_trap_group_unरेजिस्टर(devlink, &groups[i]);
	mutex_unlock(&devlink->lock);
पूर्ण
EXPORT_SYMBOL_GPL(devlink_trap_groups_unरेजिस्टर);

अटल व्योम
devlink_trap_policer_notअगरy(काष्ठा devlink *devlink,
			    स्थिर काष्ठा devlink_trap_policer_item *policer_item,
			    क्रमागत devlink_command cmd)
अणु
	काष्ठा sk_buff *msg;
	पूर्णांक err;

	WARN_ON_ONCE(cmd != DEVLINK_CMD_TRAP_POLICER_NEW &&
		     cmd != DEVLINK_CMD_TRAP_POLICER_DEL);

	msg = nlmsg_new(NLMSG_DEFAULT_SIZE, GFP_KERNEL);
	अगर (!msg)
		वापस;

	err = devlink_nl_trap_policer_fill(msg, devlink, policer_item, cmd, 0,
					   0, 0);
	अगर (err) अणु
		nlmsg_मुक्त(msg);
		वापस;
	पूर्ण

	genlmsg_multicast_netns(&devlink_nl_family, devlink_net(devlink),
				msg, 0, DEVLINK_MCGRP_CONFIG, GFP_KERNEL);
पूर्ण

अटल पूर्णांक
devlink_trap_policer_रेजिस्टर(काष्ठा devlink *devlink,
			      स्थिर काष्ठा devlink_trap_policer *policer)
अणु
	काष्ठा devlink_trap_policer_item *policer_item;
	पूर्णांक err;

	अगर (devlink_trap_policer_item_lookup(devlink, policer->id))
		वापस -EEXIST;

	policer_item = kzalloc(माप(*policer_item), GFP_KERNEL);
	अगर (!policer_item)
		वापस -ENOMEM;

	policer_item->policer = policer;
	policer_item->rate = policer->init_rate;
	policer_item->burst = policer->init_burst;

	अगर (devlink->ops->trap_policer_init) अणु
		err = devlink->ops->trap_policer_init(devlink, policer);
		अगर (err)
			जाओ err_policer_init;
	पूर्ण

	list_add_tail(&policer_item->list, &devlink->trap_policer_list);
	devlink_trap_policer_notअगरy(devlink, policer_item,
				    DEVLINK_CMD_TRAP_POLICER_NEW);

	वापस 0;

err_policer_init:
	kमुक्त(policer_item);
	वापस err;
पूर्ण

अटल व्योम
devlink_trap_policer_unरेजिस्टर(काष्ठा devlink *devlink,
				स्थिर काष्ठा devlink_trap_policer *policer)
अणु
	काष्ठा devlink_trap_policer_item *policer_item;

	policer_item = devlink_trap_policer_item_lookup(devlink, policer->id);
	अगर (WARN_ON_ONCE(!policer_item))
		वापस;

	devlink_trap_policer_notअगरy(devlink, policer_item,
				    DEVLINK_CMD_TRAP_POLICER_DEL);
	list_del(&policer_item->list);
	अगर (devlink->ops->trap_policer_fini)
		devlink->ops->trap_policer_fini(devlink, policer);
	kमुक्त(policer_item);
पूर्ण

/**
 * devlink_trap_policers_रेजिस्टर - Register packet trap policers with devlink.
 * @devlink: devlink.
 * @policers: Packet trap policers.
 * @policers_count: Count of provided packet trap policers.
 *
 * Return: Non-zero value on failure.
 */
पूर्णांक
devlink_trap_policers_रेजिस्टर(काष्ठा devlink *devlink,
			       स्थिर काष्ठा devlink_trap_policer *policers,
			       माप_प्रकार policers_count)
अणु
	पूर्णांक i, err;

	mutex_lock(&devlink->lock);
	क्रम (i = 0; i < policers_count; i++) अणु
		स्थिर काष्ठा devlink_trap_policer *policer = &policers[i];

		अगर (WARN_ON(policer->id == 0 ||
			    policer->max_rate < policer->min_rate ||
			    policer->max_burst < policer->min_burst)) अणु
			err = -EINVAL;
			जाओ err_trap_policer_verअगरy;
		पूर्ण

		err = devlink_trap_policer_रेजिस्टर(devlink, policer);
		अगर (err)
			जाओ err_trap_policer_रेजिस्टर;
	पूर्ण
	mutex_unlock(&devlink->lock);

	वापस 0;

err_trap_policer_रेजिस्टर:
err_trap_policer_verअगरy:
	क्रम (i--; i >= 0; i--)
		devlink_trap_policer_unरेजिस्टर(devlink, &policers[i]);
	mutex_unlock(&devlink->lock);
	वापस err;
पूर्ण
EXPORT_SYMBOL_GPL(devlink_trap_policers_रेजिस्टर);

/**
 * devlink_trap_policers_unरेजिस्टर - Unरेजिस्टर packet trap policers from devlink.
 * @devlink: devlink.
 * @policers: Packet trap policers.
 * @policers_count: Count of provided packet trap policers.
 */
व्योम
devlink_trap_policers_unरेजिस्टर(काष्ठा devlink *devlink,
				 स्थिर काष्ठा devlink_trap_policer *policers,
				 माप_प्रकार policers_count)
अणु
	पूर्णांक i;

	mutex_lock(&devlink->lock);
	क्रम (i = policers_count - 1; i >= 0; i--)
		devlink_trap_policer_unरेजिस्टर(devlink, &policers[i]);
	mutex_unlock(&devlink->lock);
पूर्ण
EXPORT_SYMBOL_GPL(devlink_trap_policers_unरेजिस्टर);

अटल व्योम __devlink_compat_running_version(काष्ठा devlink *devlink,
					     अक्षर *buf, माप_प्रकार len)
अणु
	स्थिर काष्ठा nlattr *nlattr;
	काष्ठा devlink_info_req req;
	काष्ठा sk_buff *msg;
	पूर्णांक rem, err;

	msg = nlmsg_new(NLMSG_DEFAULT_SIZE, GFP_KERNEL);
	अगर (!msg)
		वापस;

	req.msg = msg;
	err = devlink->ops->info_get(devlink, &req, शून्य);
	अगर (err)
		जाओ मुक्त_msg;

	nla_क्रम_each_attr(nlattr, (व्योम *)msg->data, msg->len, rem) अणु
		स्थिर काष्ठा nlattr *kv;
		पूर्णांक rem_kv;

		अगर (nla_type(nlattr) != DEVLINK_ATTR_INFO_VERSION_RUNNING)
			जारी;

		nla_क्रम_each_nested(kv, nlattr, rem_kv) अणु
			अगर (nla_type(kv) != DEVLINK_ATTR_INFO_VERSION_VALUE)
				जारी;

			strlcat(buf, nla_data(kv), len);
			strlcat(buf, " ", len);
		पूर्ण
	पूर्ण
मुक्त_msg:
	nlmsg_मुक्त(msg);
पूर्ण

व्योम devlink_compat_running_version(काष्ठा net_device *dev,
				    अक्षर *buf, माप_प्रकार len)
अणु
	काष्ठा devlink *devlink;

	dev_hold(dev);
	rtnl_unlock();

	devlink = netdev_to_devlink(dev);
	अगर (!devlink || !devlink->ops->info_get)
		जाओ out;

	mutex_lock(&devlink->lock);
	__devlink_compat_running_version(devlink, buf, len);
	mutex_unlock(&devlink->lock);

out:
	rtnl_lock();
	dev_put(dev);
पूर्ण

पूर्णांक devlink_compat_flash_update(काष्ठा net_device *dev, स्थिर अक्षर *file_name)
अणु
	काष्ठा devlink_flash_update_params params = अणुपूर्ण;
	काष्ठा devlink *devlink;
	पूर्णांक ret;

	dev_hold(dev);
	rtnl_unlock();

	devlink = netdev_to_devlink(dev);
	अगर (!devlink || !devlink->ops->flash_update) अणु
		ret = -EOPNOTSUPP;
		जाओ out;
	पूर्ण

	ret = request_firmware(&params.fw, file_name, devlink->dev);
	अगर (ret)
		जाओ out;

	mutex_lock(&devlink->lock);
	devlink_flash_update_begin_notअगरy(devlink);
	ret = devlink->ops->flash_update(devlink, &params, शून्य);
	devlink_flash_update_end_notअगरy(devlink);
	mutex_unlock(&devlink->lock);

	release_firmware(params.fw);

out:
	rtnl_lock();
	dev_put(dev);

	वापस ret;
पूर्ण

पूर्णांक devlink_compat_phys_port_name_get(काष्ठा net_device *dev,
				      अक्षर *name, माप_प्रकार len)
अणु
	काष्ठा devlink_port *devlink_port;

	/* RTNL mutex is held here which ensures that devlink_port
	 * instance cannot disappear in the middle. No need to take
	 * any devlink lock as only permanent values are accessed.
	 */
	ASSERT_RTNL();

	devlink_port = netdev_to_devlink_port(dev);
	अगर (!devlink_port)
		वापस -EOPNOTSUPP;

	वापस __devlink_port_phys_port_name_get(devlink_port, name, len);
पूर्ण

पूर्णांक devlink_compat_चयन_id_get(काष्ठा net_device *dev,
				 काष्ठा netdev_phys_item_id *ppid)
अणु
	काष्ठा devlink_port *devlink_port;

	/* Caller must hold RTNL mutex or reference to dev, which ensures that
	 * devlink_port instance cannot disappear in the middle. No need to take
	 * any devlink lock as only permanent values are accessed.
	 */
	devlink_port = netdev_to_devlink_port(dev);
	अगर (!devlink_port || !devlink_port->चयन_port)
		वापस -EOPNOTSUPP;

	स_नकल(ppid, &devlink_port->attrs.चयन_id, माप(*ppid));

	वापस 0;
पूर्ण

अटल व्योम __net_निकास devlink_pernet_pre_निकास(काष्ठा net *net)
अणु
	काष्ठा devlink *devlink;
	u32 actions_perक्रमmed;
	पूर्णांक err;

	/* In हाल network namespace is getting destroyed, reload
	 * all devlink instances from this namespace पूर्णांकo init_net.
	 */
	mutex_lock(&devlink_mutex);
	list_क्रम_each_entry(devlink, &devlink_list, list) अणु
		अगर (net_eq(devlink_net(devlink), net)) अणु
			अगर (WARN_ON(!devlink_reload_supported(devlink->ops)))
				जारी;
			err = devlink_reload(devlink, &init_net,
					     DEVLINK_RELOAD_ACTION_DRIVER_REINIT,
					     DEVLINK_RELOAD_LIMIT_UNSPEC,
					     &actions_perक्रमmed, शून्य);
			अगर (err && err != -EOPNOTSUPP)
				pr_warn("Failed to reload devlink instance into init_net\n");
		पूर्ण
	पूर्ण
	mutex_unlock(&devlink_mutex);
पूर्ण

अटल काष्ठा pernet_operations devlink_pernet_ops __net_initdata = अणु
	.pre_निकास = devlink_pernet_pre_निकास,
पूर्ण;

अटल पूर्णांक __init devlink_init(व्योम)
अणु
	पूर्णांक err;

	err = genl_रेजिस्टर_family(&devlink_nl_family);
	अगर (err)
		जाओ out;
	err = रेजिस्टर_pernet_subsys(&devlink_pernet_ops);

out:
	WARN_ON(err);
	वापस err;
पूर्ण

subsys_initcall(devlink_init);
