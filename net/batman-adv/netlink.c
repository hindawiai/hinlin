<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/* Copyright (C) B.A.T.M.A.N. contributors:
 *
 * Matthias Schअगरfer
 */

#समावेश "netlink.h"
#समावेश "main.h"

#समावेश <linux/atomic.h>
#समावेश <linux/bitops.h>
#समावेश <linux/bug.h>
#समावेश <linux/byteorder/generic.h>
#समावेश <linux/cache.h>
#समावेश <linux/err.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/export.h>
#समावेश <linux/genetlink.h>
#समावेश <linux/gfp.h>
#समावेश <linux/अगर_ether.h>
#समावेश <linux/अगर_vlan.h>
#समावेश <linux/init.h>
#समावेश <linux/kernel.h>
#समावेश <linux/सीमा.स>
#समावेश <linux/list.h>
#समावेश <linux/minmax.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/netlink.h>
#समावेश <linux/prपूर्णांकk.h>
#समावेश <linux/rtnetlink.h>
#समावेश <linux/skbuff.h>
#समावेश <linux/मानकघोष.स>
#समावेश <linux/types.h>
#समावेश <net/genetlink.h>
#समावेश <net/net_namespace.h>
#समावेश <net/netlink.h>
#समावेश <net/sock.h>
#समावेश <uapi/linux/batadv_packet.h>
#समावेश <uapi/linux/baपंचांगan_adv.h>

#समावेश "bat_algo.h"
#समावेश "bridge_loop_avoidance.h"
#समावेश "distributed-arp-table.h"
#समावेश "gateway_client.h"
#समावेश "gateway_common.h"
#समावेश "hard-interface.h"
#समावेश "log.h"
#समावेश "multicast.h"
#समावेश "network-coding.h"
#समावेश "originator.h"
#समावेश "soft-interface.h"
#समावेश "tp_meter.h"
#समावेश "translation-table.h"

काष्ठा genl_family batadv_netlink_family;

/* multicast groups */
क्रमागत batadv_netlink_multicast_groups अणु
	BATADV_NL_MCGRP_CONFIG,
	BATADV_NL_MCGRP_TPMETER,
पूर्ण;

/**
 * क्रमागत batadv_genl_ops_flags - flags क्रम genl_ops's पूर्णांकernal_flags
 */
क्रमागत batadv_genl_ops_flags अणु
	/**
	 * @BATADV_FLAG_NEED_MESH: request requires valid soft पूर्णांकerface in
	 *  attribute BATADV_ATTR_MESH_IFINDEX and expects a poपूर्णांकer to it to be
	 *  saved in info->user_ptr[0]
	 */
	BATADV_FLAG_NEED_MESH = BIT(0),

	/**
	 * @BATADV_FLAG_NEED_HARDIF: request requires valid hard पूर्णांकerface in
	 *  attribute BATADV_ATTR_HARD_IFINDEX and expects a poपूर्णांकer to it to be
	 *  saved in info->user_ptr[1]
	 */
	BATADV_FLAG_NEED_HARDIF = BIT(1),

	/**
	 * @BATADV_FLAG_NEED_VLAN: request requires valid vlan in
	 *  attribute BATADV_ATTR_VLANID and expects a poपूर्णांकer to it to be
	 *  saved in info->user_ptr[1]
	 */
	BATADV_FLAG_NEED_VLAN = BIT(2),
पूर्ण;

अटल स्थिर काष्ठा genl_multicast_group batadv_netlink_mcgrps[] = अणु
	[BATADV_NL_MCGRP_CONFIG] = अणु .name = BATADV_NL_MCAST_GROUP_CONFIG पूर्ण,
	[BATADV_NL_MCGRP_TPMETER] = अणु .name = BATADV_NL_MCAST_GROUP_TPMETER पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा nla_policy batadv_netlink_policy[NUM_BATADV_ATTR] = अणु
	[BATADV_ATTR_VERSION]			= अणु .type = NLA_STRING पूर्ण,
	[BATADV_ATTR_ALGO_NAME]			= अणु .type = NLA_STRING पूर्ण,
	[BATADV_ATTR_MESH_IFINDEX]		= अणु .type = NLA_U32 पूर्ण,
	[BATADV_ATTR_MESH_IFNAME]		= अणु .type = NLA_STRING पूर्ण,
	[BATADV_ATTR_MESH_ADDRESS]		= अणु .len = ETH_ALEN पूर्ण,
	[BATADV_ATTR_HARD_IFINDEX]		= अणु .type = NLA_U32 पूर्ण,
	[BATADV_ATTR_HARD_IFNAME]		= अणु .type = NLA_STRING पूर्ण,
	[BATADV_ATTR_HARD_ADDRESS]		= अणु .len = ETH_ALEN पूर्ण,
	[BATADV_ATTR_ORIG_ADDRESS]		= अणु .len = ETH_ALEN पूर्ण,
	[BATADV_ATTR_TPMETER_RESULT]		= अणु .type = NLA_U8 पूर्ण,
	[BATADV_ATTR_TPMETER_TEST_TIME]		= अणु .type = NLA_U32 पूर्ण,
	[BATADV_ATTR_TPMETER_BYTES]		= अणु .type = NLA_U64 पूर्ण,
	[BATADV_ATTR_TPMETER_COOKIE]		= अणु .type = NLA_U32 पूर्ण,
	[BATADV_ATTR_ACTIVE]			= अणु .type = NLA_FLAG पूर्ण,
	[BATADV_ATTR_TT_ADDRESS]		= अणु .len = ETH_ALEN पूर्ण,
	[BATADV_ATTR_TT_TTVN]			= अणु .type = NLA_U8 पूर्ण,
	[BATADV_ATTR_TT_LAST_TTVN]		= अणु .type = NLA_U8 पूर्ण,
	[BATADV_ATTR_TT_CRC32]			= अणु .type = NLA_U32 पूर्ण,
	[BATADV_ATTR_TT_VID]			= अणु .type = NLA_U16 पूर्ण,
	[BATADV_ATTR_TT_FLAGS]			= अणु .type = NLA_U32 पूर्ण,
	[BATADV_ATTR_FLAG_BEST]			= अणु .type = NLA_FLAG पूर्ण,
	[BATADV_ATTR_LAST_SEEN_MSECS]		= अणु .type = NLA_U32 पूर्ण,
	[BATADV_ATTR_NEIGH_ADDRESS]		= अणु .len = ETH_ALEN पूर्ण,
	[BATADV_ATTR_TQ]			= अणु .type = NLA_U8 पूर्ण,
	[BATADV_ATTR_THROUGHPUT]		= अणु .type = NLA_U32 पूर्ण,
	[BATADV_ATTR_BANDWIDTH_UP]		= अणु .type = NLA_U32 पूर्ण,
	[BATADV_ATTR_BANDWIDTH_DOWN]		= अणु .type = NLA_U32 पूर्ण,
	[BATADV_ATTR_ROUTER]			= अणु .len = ETH_ALEN पूर्ण,
	[BATADV_ATTR_BLA_OWN]			= अणु .type = NLA_FLAG पूर्ण,
	[BATADV_ATTR_BLA_ADDRESS]		= अणु .len = ETH_ALEN पूर्ण,
	[BATADV_ATTR_BLA_VID]			= अणु .type = NLA_U16 पूर्ण,
	[BATADV_ATTR_BLA_BACKBONE]		= अणु .len = ETH_ALEN पूर्ण,
	[BATADV_ATTR_BLA_CRC]			= अणु .type = NLA_U16 पूर्ण,
	[BATADV_ATTR_DAT_CACHE_IP4ADDRESS]	= अणु .type = NLA_U32 पूर्ण,
	[BATADV_ATTR_DAT_CACHE_HWADDRESS]	= अणु .len = ETH_ALEN पूर्ण,
	[BATADV_ATTR_DAT_CACHE_VID]		= अणु .type = NLA_U16 पूर्ण,
	[BATADV_ATTR_MCAST_FLAGS]		= अणु .type = NLA_U32 पूर्ण,
	[BATADV_ATTR_MCAST_FLAGS_PRIV]		= अणु .type = NLA_U32 पूर्ण,
	[BATADV_ATTR_VLANID]			= अणु .type = NLA_U16 पूर्ण,
	[BATADV_ATTR_AGGREGATED_OGMS_ENABLED]	= अणु .type = NLA_U8 पूर्ण,
	[BATADV_ATTR_AP_ISOLATION_ENABLED]	= अणु .type = NLA_U8 पूर्ण,
	[BATADV_ATTR_ISOLATION_MARK]		= अणु .type = NLA_U32 पूर्ण,
	[BATADV_ATTR_ISOLATION_MASK]		= अणु .type = NLA_U32 पूर्ण,
	[BATADV_ATTR_BONDING_ENABLED]		= अणु .type = NLA_U8 पूर्ण,
	[BATADV_ATTR_BRIDGE_LOOP_AVOIDANCE_ENABLED]	= अणु .type = NLA_U8 पूर्ण,
	[BATADV_ATTR_DISTRIBUTED_ARP_TABLE_ENABLED]	= अणु .type = NLA_U8 पूर्ण,
	[BATADV_ATTR_FRAGMENTATION_ENABLED]	= अणु .type = NLA_U8 पूर्ण,
	[BATADV_ATTR_GW_BANDWIDTH_DOWN]		= अणु .type = NLA_U32 पूर्ण,
	[BATADV_ATTR_GW_BANDWIDTH_UP]		= अणु .type = NLA_U32 पूर्ण,
	[BATADV_ATTR_GW_MODE]			= अणु .type = NLA_U8 पूर्ण,
	[BATADV_ATTR_GW_SEL_CLASS]		= अणु .type = NLA_U32 पूर्ण,
	[BATADV_ATTR_HOP_PENALTY]		= अणु .type = NLA_U8 पूर्ण,
	[BATADV_ATTR_LOG_LEVEL]			= अणु .type = NLA_U32 पूर्ण,
	[BATADV_ATTR_MULTICAST_FORCEFLOOD_ENABLED]	= अणु .type = NLA_U8 पूर्ण,
	[BATADV_ATTR_MULTICAST_FANOUT]		= अणु .type = NLA_U32 पूर्ण,
	[BATADV_ATTR_NETWORK_CODING_ENABLED]	= अणु .type = NLA_U8 पूर्ण,
	[BATADV_ATTR_ORIG_INTERVAL]		= अणु .type = NLA_U32 पूर्ण,
	[BATADV_ATTR_ELP_INTERVAL]		= अणु .type = NLA_U32 पूर्ण,
	[BATADV_ATTR_THROUGHPUT_OVERRIDE]	= अणु .type = NLA_U32 पूर्ण,
पूर्ण;

/**
 * batadv_netlink_get_अगरindex() - Extract an पूर्णांकerface index from a message
 * @nlh: Message header
 * @attrtype: Attribute which holds an पूर्णांकerface index
 *
 * Return: पूर्णांकerface index, or 0.
 */
पूर्णांक
batadv_netlink_get_अगरindex(स्थिर काष्ठा nlmsghdr *nlh, पूर्णांक attrtype)
अणु
	काष्ठा nlattr *attr = nlmsg_find_attr(nlh, GENL_HDRLEN, attrtype);

	वापस (attr && nla_len(attr) == माप(u32)) ? nla_get_u32(attr) : 0;
पूर्ण

/**
 * batadv_netlink_mesh_fill_ap_isolation() - Add ap_isolation softअगर attribute
 * @msg: Netlink message to dump पूर्णांकo
 * @bat_priv: the bat priv with all the soft पूर्णांकerface inक्रमmation
 *
 * Return: 0 on success or negative error number in हाल of failure
 */
अटल पूर्णांक batadv_netlink_mesh_fill_ap_isolation(काष्ठा sk_buff *msg,
						 काष्ठा batadv_priv *bat_priv)
अणु
	काष्ठा batadv_softअगर_vlan *vlan;
	u8 ap_isolation;

	vlan = batadv_softअगर_vlan_get(bat_priv, BATADV_NO_FLAGS);
	अगर (!vlan)
		वापस 0;

	ap_isolation = atomic_पढ़ो(&vlan->ap_isolation);
	batadv_softअगर_vlan_put(vlan);

	वापस nla_put_u8(msg, BATADV_ATTR_AP_ISOLATION_ENABLED,
			  !!ap_isolation);
पूर्ण

/**
 * batadv_netlink_set_mesh_ap_isolation() - Set ap_isolation from genl msg
 * @attr: parsed BATADV_ATTR_AP_ISOLATION_ENABLED attribute
 * @bat_priv: the bat priv with all the soft पूर्णांकerface inक्रमmation
 *
 * Return: 0 on success or negative error number in हाल of failure
 */
अटल पूर्णांक batadv_netlink_set_mesh_ap_isolation(काष्ठा nlattr *attr,
						काष्ठा batadv_priv *bat_priv)
अणु
	काष्ठा batadv_softअगर_vlan *vlan;

	vlan = batadv_softअगर_vlan_get(bat_priv, BATADV_NO_FLAGS);
	अगर (!vlan)
		वापस -ENOENT;

	atomic_set(&vlan->ap_isolation, !!nla_get_u8(attr));
	batadv_softअगर_vlan_put(vlan);

	वापस 0;
पूर्ण

/**
 * batadv_netlink_mesh_fill() - Fill message with mesh attributes
 * @msg: Netlink message to dump पूर्णांकo
 * @bat_priv: the bat priv with all the soft पूर्णांकerface inक्रमmation
 * @cmd: type of message to generate
 * @portid: Port making netlink request
 * @seq: sequence number क्रम message
 * @flags: Additional flags क्रम message
 *
 * Return: 0 on success or negative error number in हाल of failure
 */
अटल पूर्णांक batadv_netlink_mesh_fill(काष्ठा sk_buff *msg,
				    काष्ठा batadv_priv *bat_priv,
				    क्रमागत batadv_nl_commands cmd,
				    u32 portid, u32 seq, पूर्णांक flags)
अणु
	काष्ठा net_device *soft_अगरace = bat_priv->soft_अगरace;
	काष्ठा batadv_hard_अगरace *primary_अगर = शून्य;
	काष्ठा net_device *hard_अगरace;
	व्योम *hdr;

	hdr = genlmsg_put(msg, portid, seq, &batadv_netlink_family, flags, cmd);
	अगर (!hdr)
		वापस -ENOBUFS;

	अगर (nla_put_string(msg, BATADV_ATTR_VERSION, BATADV_SOURCE_VERSION) ||
	    nla_put_string(msg, BATADV_ATTR_ALGO_NAME,
			   bat_priv->algo_ops->name) ||
	    nla_put_u32(msg, BATADV_ATTR_MESH_IFINDEX, soft_अगरace->अगरindex) ||
	    nla_put_string(msg, BATADV_ATTR_MESH_IFNAME, soft_अगरace->name) ||
	    nla_put(msg, BATADV_ATTR_MESH_ADDRESS, ETH_ALEN,
		    soft_अगरace->dev_addr) ||
	    nla_put_u8(msg, BATADV_ATTR_TT_TTVN,
		       (u8)atomic_पढ़ो(&bat_priv->tt.vn)))
		जाओ nla_put_failure;

#अगर_घोषित CONFIG_BATMAN_ADV_BLA
	अगर (nla_put_u16(msg, BATADV_ATTR_BLA_CRC,
			ntohs(bat_priv->bla.claim_dest.group)))
		जाओ nla_put_failure;
#पूर्ण_अगर

	अगर (batadv_mcast_mesh_info_put(msg, bat_priv))
		जाओ nla_put_failure;

	primary_अगर = batadv_primary_अगर_get_selected(bat_priv);
	अगर (primary_अगर && primary_अगर->अगर_status == BATADV_IF_ACTIVE) अणु
		hard_अगरace = primary_अगर->net_dev;

		अगर (nla_put_u32(msg, BATADV_ATTR_HARD_IFINDEX,
				hard_अगरace->अगरindex) ||
		    nla_put_string(msg, BATADV_ATTR_HARD_IFNAME,
				   hard_अगरace->name) ||
		    nla_put(msg, BATADV_ATTR_HARD_ADDRESS, ETH_ALEN,
			    hard_अगरace->dev_addr))
			जाओ nla_put_failure;
	पूर्ण

	अगर (nla_put_u8(msg, BATADV_ATTR_AGGREGATED_OGMS_ENABLED,
		       !!atomic_पढ़ो(&bat_priv->aggregated_ogms)))
		जाओ nla_put_failure;

	अगर (batadv_netlink_mesh_fill_ap_isolation(msg, bat_priv))
		जाओ nla_put_failure;

	अगर (nla_put_u32(msg, BATADV_ATTR_ISOLATION_MARK,
			bat_priv->isolation_mark))
		जाओ nla_put_failure;

	अगर (nla_put_u32(msg, BATADV_ATTR_ISOLATION_MASK,
			bat_priv->isolation_mark_mask))
		जाओ nla_put_failure;

	अगर (nla_put_u8(msg, BATADV_ATTR_BONDING_ENABLED,
		       !!atomic_पढ़ो(&bat_priv->bonding)))
		जाओ nla_put_failure;

#अगर_घोषित CONFIG_BATMAN_ADV_BLA
	अगर (nla_put_u8(msg, BATADV_ATTR_BRIDGE_LOOP_AVOIDANCE_ENABLED,
		       !!atomic_पढ़ो(&bat_priv->bridge_loop_aव्योमance)))
		जाओ nla_put_failure;
#पूर्ण_अगर /* CONFIG_BATMAN_ADV_BLA */

#अगर_घोषित CONFIG_BATMAN_ADV_DAT
	अगर (nla_put_u8(msg, BATADV_ATTR_DISTRIBUTED_ARP_TABLE_ENABLED,
		       !!atomic_पढ़ो(&bat_priv->distributed_arp_table)))
		जाओ nla_put_failure;
#पूर्ण_अगर /* CONFIG_BATMAN_ADV_DAT */

	अगर (nla_put_u8(msg, BATADV_ATTR_FRAGMENTATION_ENABLED,
		       !!atomic_पढ़ो(&bat_priv->fragmentation)))
		जाओ nla_put_failure;

	अगर (nla_put_u32(msg, BATADV_ATTR_GW_BANDWIDTH_DOWN,
			atomic_पढ़ो(&bat_priv->gw.bandwidth_करोwn)))
		जाओ nla_put_failure;

	अगर (nla_put_u32(msg, BATADV_ATTR_GW_BANDWIDTH_UP,
			atomic_पढ़ो(&bat_priv->gw.bandwidth_up)))
		जाओ nla_put_failure;

	अगर (nla_put_u8(msg, BATADV_ATTR_GW_MODE,
		       atomic_पढ़ो(&bat_priv->gw.mode)))
		जाओ nla_put_failure;

	अगर (bat_priv->algo_ops->gw.get_best_gw_node &&
	    bat_priv->algo_ops->gw.is_eligible) अणु
		/* GW selection class is not available अगर the routing algorithm
		 * in use करोes not implement the GW API
		 */
		अगर (nla_put_u32(msg, BATADV_ATTR_GW_SEL_CLASS,
				atomic_पढ़ो(&bat_priv->gw.sel_class)))
			जाओ nla_put_failure;
	पूर्ण

	अगर (nla_put_u8(msg, BATADV_ATTR_HOP_PENALTY,
		       atomic_पढ़ो(&bat_priv->hop_penalty)))
		जाओ nla_put_failure;

#अगर_घोषित CONFIG_BATMAN_ADV_DEBUG
	अगर (nla_put_u32(msg, BATADV_ATTR_LOG_LEVEL,
			atomic_पढ़ो(&bat_priv->log_level)))
		जाओ nla_put_failure;
#पूर्ण_अगर /* CONFIG_BATMAN_ADV_DEBUG */

#अगर_घोषित CONFIG_BATMAN_ADV_MCAST
	अगर (nla_put_u8(msg, BATADV_ATTR_MULTICAST_FORCEFLOOD_ENABLED,
		       !atomic_पढ़ो(&bat_priv->multicast_mode)))
		जाओ nla_put_failure;

	अगर (nla_put_u32(msg, BATADV_ATTR_MULTICAST_FANOUT,
			atomic_पढ़ो(&bat_priv->multicast_fanout)))
		जाओ nla_put_failure;
#पूर्ण_अगर /* CONFIG_BATMAN_ADV_MCAST */

#अगर_घोषित CONFIG_BATMAN_ADV_NC
	अगर (nla_put_u8(msg, BATADV_ATTR_NETWORK_CODING_ENABLED,
		       !!atomic_पढ़ो(&bat_priv->network_coding)))
		जाओ nla_put_failure;
#पूर्ण_अगर /* CONFIG_BATMAN_ADV_NC */

	अगर (nla_put_u32(msg, BATADV_ATTR_ORIG_INTERVAL,
			atomic_पढ़ो(&bat_priv->orig_पूर्णांकerval)))
		जाओ nla_put_failure;

	अगर (primary_अगर)
		batadv_hardअगर_put(primary_अगर);

	genlmsg_end(msg, hdr);
	वापस 0;

nla_put_failure:
	अगर (primary_अगर)
		batadv_hardअगर_put(primary_अगर);

	genlmsg_cancel(msg, hdr);
	वापस -EMSGSIZE;
पूर्ण

/**
 * batadv_netlink_notअगरy_mesh() - send softअगर attributes to listener
 * @bat_priv: the bat priv with all the soft पूर्णांकerface inक्रमmation
 *
 * Return: 0 on success, < 0 on error
 */
पूर्णांक batadv_netlink_notअगरy_mesh(काष्ठा batadv_priv *bat_priv)
अणु
	काष्ठा sk_buff *msg;
	पूर्णांक ret;

	msg = nlmsg_new(NLMSG_DEFAULT_SIZE, GFP_KERNEL);
	अगर (!msg)
		वापस -ENOMEM;

	ret = batadv_netlink_mesh_fill(msg, bat_priv, BATADV_CMD_SET_MESH,
				       0, 0, 0);
	अगर (ret < 0) अणु
		nlmsg_मुक्त(msg);
		वापस ret;
	पूर्ण

	genlmsg_multicast_netns(&batadv_netlink_family,
				dev_net(bat_priv->soft_अगरace), msg, 0,
				BATADV_NL_MCGRP_CONFIG, GFP_KERNEL);

	वापस 0;
पूर्ण

/**
 * batadv_netlink_get_mesh() - Get softअगर attributes
 * @skb: Netlink message with request data
 * @info: receiver inक्रमmation
 *
 * Return: 0 on success or negative error number in हाल of failure
 */
अटल पूर्णांक batadv_netlink_get_mesh(काष्ठा sk_buff *skb, काष्ठा genl_info *info)
अणु
	काष्ठा batadv_priv *bat_priv = info->user_ptr[0];
	काष्ठा sk_buff *msg;
	पूर्णांक ret;

	msg = nlmsg_new(NLMSG_DEFAULT_SIZE, GFP_KERNEL);
	अगर (!msg)
		वापस -ENOMEM;

	ret = batadv_netlink_mesh_fill(msg, bat_priv, BATADV_CMD_GET_MESH,
				       info->snd_portid, info->snd_seq, 0);
	अगर (ret < 0) अणु
		nlmsg_मुक्त(msg);
		वापस ret;
	पूर्ण

	ret = genlmsg_reply(msg, info);

	वापस ret;
पूर्ण

/**
 * batadv_netlink_set_mesh() - Set softअगर attributes
 * @skb: Netlink message with request data
 * @info: receiver inक्रमmation
 *
 * Return: 0 on success or negative error number in हाल of failure
 */
अटल पूर्णांक batadv_netlink_set_mesh(काष्ठा sk_buff *skb, काष्ठा genl_info *info)
अणु
	काष्ठा batadv_priv *bat_priv = info->user_ptr[0];
	काष्ठा nlattr *attr;

	अगर (info->attrs[BATADV_ATTR_AGGREGATED_OGMS_ENABLED]) अणु
		attr = info->attrs[BATADV_ATTR_AGGREGATED_OGMS_ENABLED];

		atomic_set(&bat_priv->aggregated_ogms, !!nla_get_u8(attr));
	पूर्ण

	अगर (info->attrs[BATADV_ATTR_AP_ISOLATION_ENABLED]) अणु
		attr = info->attrs[BATADV_ATTR_AP_ISOLATION_ENABLED];

		batadv_netlink_set_mesh_ap_isolation(attr, bat_priv);
	पूर्ण

	अगर (info->attrs[BATADV_ATTR_ISOLATION_MARK]) अणु
		attr = info->attrs[BATADV_ATTR_ISOLATION_MARK];

		bat_priv->isolation_mark = nla_get_u32(attr);
	पूर्ण

	अगर (info->attrs[BATADV_ATTR_ISOLATION_MASK]) अणु
		attr = info->attrs[BATADV_ATTR_ISOLATION_MASK];

		bat_priv->isolation_mark_mask = nla_get_u32(attr);
	पूर्ण

	अगर (info->attrs[BATADV_ATTR_BONDING_ENABLED]) अणु
		attr = info->attrs[BATADV_ATTR_BONDING_ENABLED];

		atomic_set(&bat_priv->bonding, !!nla_get_u8(attr));
	पूर्ण

#अगर_घोषित CONFIG_BATMAN_ADV_BLA
	अगर (info->attrs[BATADV_ATTR_BRIDGE_LOOP_AVOIDANCE_ENABLED]) अणु
		attr = info->attrs[BATADV_ATTR_BRIDGE_LOOP_AVOIDANCE_ENABLED];

		atomic_set(&bat_priv->bridge_loop_aव्योमance,
			   !!nla_get_u8(attr));
		batadv_bla_status_update(bat_priv->soft_अगरace);
	पूर्ण
#पूर्ण_अगर /* CONFIG_BATMAN_ADV_BLA */

#अगर_घोषित CONFIG_BATMAN_ADV_DAT
	अगर (info->attrs[BATADV_ATTR_DISTRIBUTED_ARP_TABLE_ENABLED]) अणु
		attr = info->attrs[BATADV_ATTR_DISTRIBUTED_ARP_TABLE_ENABLED];

		atomic_set(&bat_priv->distributed_arp_table,
			   !!nla_get_u8(attr));
		batadv_dat_status_update(bat_priv->soft_अगरace);
	पूर्ण
#पूर्ण_अगर /* CONFIG_BATMAN_ADV_DAT */

	अगर (info->attrs[BATADV_ATTR_FRAGMENTATION_ENABLED]) अणु
		attr = info->attrs[BATADV_ATTR_FRAGMENTATION_ENABLED];

		atomic_set(&bat_priv->fragmentation, !!nla_get_u8(attr));
		batadv_update_min_mtu(bat_priv->soft_अगरace);
	पूर्ण

	अगर (info->attrs[BATADV_ATTR_GW_BANDWIDTH_DOWN]) अणु
		attr = info->attrs[BATADV_ATTR_GW_BANDWIDTH_DOWN];

		atomic_set(&bat_priv->gw.bandwidth_करोwn, nla_get_u32(attr));
		batadv_gw_tvlv_container_update(bat_priv);
	पूर्ण

	अगर (info->attrs[BATADV_ATTR_GW_BANDWIDTH_UP]) अणु
		attr = info->attrs[BATADV_ATTR_GW_BANDWIDTH_UP];

		atomic_set(&bat_priv->gw.bandwidth_up, nla_get_u32(attr));
		batadv_gw_tvlv_container_update(bat_priv);
	पूर्ण

	अगर (info->attrs[BATADV_ATTR_GW_MODE]) अणु
		u8 gw_mode;

		attr = info->attrs[BATADV_ATTR_GW_MODE];
		gw_mode = nla_get_u8(attr);

		अगर (gw_mode <= BATADV_GW_MODE_SERVER) अणु
			/* Invoking batadv_gw_reselect() is not enough to really
			 * de-select the current GW. It will only inकाष्ठा the
			 * gateway client code to perक्रमm a re-election the next
			 * समय that this is needed.
			 *
			 * When gw client mode is being चयनed off the current
			 * GW must be de-selected explicitly otherwise no GW_ADD
			 * uevent is thrown on client mode re-activation. This
			 * is operation is perक्रमmed in
			 * batadv_gw_check_client_stop().
			 */
			batadv_gw_reselect(bat_priv);

			/* always call batadv_gw_check_client_stop() beक्रमe
			 * changing the gateway state
			 */
			batadv_gw_check_client_stop(bat_priv);
			atomic_set(&bat_priv->gw.mode, gw_mode);
			batadv_gw_tvlv_container_update(bat_priv);
		पूर्ण
	पूर्ण

	अगर (info->attrs[BATADV_ATTR_GW_SEL_CLASS] &&
	    bat_priv->algo_ops->gw.get_best_gw_node &&
	    bat_priv->algo_ops->gw.is_eligible) अणु
		/* setting the GW selection class is allowed only अगर the routing
		 * algorithm in use implements the GW API
		 */

		u32 sel_class_max = 0xffffffffu;
		u32 sel_class;

		attr = info->attrs[BATADV_ATTR_GW_SEL_CLASS];
		sel_class = nla_get_u32(attr);

		अगर (!bat_priv->algo_ops->gw.store_sel_class)
			sel_class_max = BATADV_TQ_MAX_VALUE;

		अगर (sel_class >= 1 && sel_class <= sel_class_max) अणु
			atomic_set(&bat_priv->gw.sel_class, sel_class);
			batadv_gw_reselect(bat_priv);
		पूर्ण
	पूर्ण

	अगर (info->attrs[BATADV_ATTR_HOP_PENALTY]) अणु
		attr = info->attrs[BATADV_ATTR_HOP_PENALTY];

		atomic_set(&bat_priv->hop_penalty, nla_get_u8(attr));
	पूर्ण

#अगर_घोषित CONFIG_BATMAN_ADV_DEBUG
	अगर (info->attrs[BATADV_ATTR_LOG_LEVEL]) अणु
		attr = info->attrs[BATADV_ATTR_LOG_LEVEL];

		atomic_set(&bat_priv->log_level,
			   nla_get_u32(attr) & BATADV_DBG_ALL);
	पूर्ण
#पूर्ण_अगर /* CONFIG_BATMAN_ADV_DEBUG */

#अगर_घोषित CONFIG_BATMAN_ADV_MCAST
	अगर (info->attrs[BATADV_ATTR_MULTICAST_FORCEFLOOD_ENABLED]) अणु
		attr = info->attrs[BATADV_ATTR_MULTICAST_FORCEFLOOD_ENABLED];

		atomic_set(&bat_priv->multicast_mode, !nla_get_u8(attr));
	पूर्ण

	अगर (info->attrs[BATADV_ATTR_MULTICAST_FANOUT]) अणु
		attr = info->attrs[BATADV_ATTR_MULTICAST_FANOUT];

		atomic_set(&bat_priv->multicast_fanout, nla_get_u32(attr));
	पूर्ण
#पूर्ण_अगर /* CONFIG_BATMAN_ADV_MCAST */

#अगर_घोषित CONFIG_BATMAN_ADV_NC
	अगर (info->attrs[BATADV_ATTR_NETWORK_CODING_ENABLED]) अणु
		attr = info->attrs[BATADV_ATTR_NETWORK_CODING_ENABLED];

		atomic_set(&bat_priv->network_coding, !!nla_get_u8(attr));
		batadv_nc_status_update(bat_priv->soft_अगरace);
	पूर्ण
#पूर्ण_अगर /* CONFIG_BATMAN_ADV_NC */

	अगर (info->attrs[BATADV_ATTR_ORIG_INTERVAL]) अणु
		u32 orig_पूर्णांकerval;

		attr = info->attrs[BATADV_ATTR_ORIG_INTERVAL];
		orig_पूर्णांकerval = nla_get_u32(attr);

		orig_पूर्णांकerval = min_t(u32, orig_पूर्णांकerval, पूर्णांक_उच्च);
		orig_पूर्णांकerval = max_t(u32, orig_पूर्णांकerval, 2 * BATADV_JITTER);

		atomic_set(&bat_priv->orig_पूर्णांकerval, orig_पूर्णांकerval);
	पूर्ण

	batadv_netlink_notअगरy_mesh(bat_priv);

	वापस 0;
पूर्ण

/**
 * batadv_netlink_tp_meter_put() - Fill inक्रमmation of started tp_meter session
 * @msg: netlink message to be sent back
 * @cookie: tp meter session cookie
 *
 *  Return: 0 on success, < 0 on error
 */
अटल पूर्णांक
batadv_netlink_tp_meter_put(काष्ठा sk_buff *msg, u32 cookie)
अणु
	अगर (nla_put_u32(msg, BATADV_ATTR_TPMETER_COOKIE, cookie))
		वापस -ENOBUFS;

	वापस 0;
पूर्ण

/**
 * batadv_netlink_tpmeter_notअगरy() - send tp_meter result via netlink to client
 * @bat_priv: the bat priv with all the soft पूर्णांकerface inक्रमmation
 * @dst: destination of tp_meter session
 * @result: reason क्रम tp meter session stop
 * @test_समय: total समय of the tp_meter session
 * @total_bytes: bytes acked to the receiver
 * @cookie: cookie of tp_meter session
 *
 * Return: 0 on success, < 0 on error
 */
पूर्णांक batadv_netlink_tpmeter_notअगरy(काष्ठा batadv_priv *bat_priv, स्थिर u8 *dst,
				  u8 result, u32 test_समय, u64 total_bytes,
				  u32 cookie)
अणु
	काष्ठा sk_buff *msg;
	व्योम *hdr;
	पूर्णांक ret;

	msg = nlmsg_new(NLMSG_DEFAULT_SIZE, GFP_KERNEL);
	अगर (!msg)
		वापस -ENOMEM;

	hdr = genlmsg_put(msg, 0, 0, &batadv_netlink_family, 0,
			  BATADV_CMD_TP_METER);
	अगर (!hdr) अणु
		ret = -ENOBUFS;
		जाओ err_genlmsg;
	पूर्ण

	अगर (nla_put_u32(msg, BATADV_ATTR_TPMETER_COOKIE, cookie))
		जाओ nla_put_failure;

	अगर (nla_put_u32(msg, BATADV_ATTR_TPMETER_TEST_TIME, test_समय))
		जाओ nla_put_failure;

	अगर (nla_put_u64_64bit(msg, BATADV_ATTR_TPMETER_BYTES, total_bytes,
			      BATADV_ATTR_PAD))
		जाओ nla_put_failure;

	अगर (nla_put_u8(msg, BATADV_ATTR_TPMETER_RESULT, result))
		जाओ nla_put_failure;

	अगर (nla_put(msg, BATADV_ATTR_ORIG_ADDRESS, ETH_ALEN, dst))
		जाओ nla_put_failure;

	genlmsg_end(msg, hdr);

	genlmsg_multicast_netns(&batadv_netlink_family,
				dev_net(bat_priv->soft_अगरace), msg, 0,
				BATADV_NL_MCGRP_TPMETER, GFP_KERNEL);

	वापस 0;

nla_put_failure:
	genlmsg_cancel(msg, hdr);
	ret = -EMSGSIZE;

err_genlmsg:
	nlmsg_मुक्त(msg);
	वापस ret;
पूर्ण

/**
 * batadv_netlink_tp_meter_start() - Start a new tp_meter session
 * @skb: received netlink message
 * @info: receiver inक्रमmation
 *
 * Return: 0 on success, < 0 on error
 */
अटल पूर्णांक
batadv_netlink_tp_meter_start(काष्ठा sk_buff *skb, काष्ठा genl_info *info)
अणु
	काष्ठा batadv_priv *bat_priv = info->user_ptr[0];
	काष्ठा sk_buff *msg = शून्य;
	u32 test_length;
	व्योम *msg_head;
	u32 cookie;
	u8 *dst;
	पूर्णांक ret;

	अगर (!info->attrs[BATADV_ATTR_ORIG_ADDRESS])
		वापस -EINVAL;

	अगर (!info->attrs[BATADV_ATTR_TPMETER_TEST_TIME])
		वापस -EINVAL;

	dst = nla_data(info->attrs[BATADV_ATTR_ORIG_ADDRESS]);

	test_length = nla_get_u32(info->attrs[BATADV_ATTR_TPMETER_TEST_TIME]);

	msg = nlmsg_new(NLMSG_DEFAULT_SIZE, GFP_KERNEL);
	अगर (!msg) अणु
		ret = -ENOMEM;
		जाओ out;
	पूर्ण

	msg_head = genlmsg_put(msg, info->snd_portid, info->snd_seq,
			       &batadv_netlink_family, 0,
			       BATADV_CMD_TP_METER);
	अगर (!msg_head) अणु
		ret = -ENOBUFS;
		जाओ out;
	पूर्ण

	batadv_tp_start(bat_priv, dst, test_length, &cookie);

	ret = batadv_netlink_tp_meter_put(msg, cookie);

 out:
	अगर (ret) अणु
		अगर (msg)
			nlmsg_मुक्त(msg);
		वापस ret;
	पूर्ण

	genlmsg_end(msg, msg_head);
	वापस genlmsg_reply(msg, info);
पूर्ण

/**
 * batadv_netlink_tp_meter_cancel() - Cancel a running tp_meter session
 * @skb: received netlink message
 * @info: receiver inक्रमmation
 *
 * Return: 0 on success, < 0 on error
 */
अटल पूर्णांक
batadv_netlink_tp_meter_cancel(काष्ठा sk_buff *skb, काष्ठा genl_info *info)
अणु
	काष्ठा batadv_priv *bat_priv = info->user_ptr[0];
	u8 *dst;
	पूर्णांक ret = 0;

	अगर (!info->attrs[BATADV_ATTR_ORIG_ADDRESS])
		वापस -EINVAL;

	dst = nla_data(info->attrs[BATADV_ATTR_ORIG_ADDRESS]);

	batadv_tp_stop(bat_priv, dst, BATADV_TP_REASON_CANCEL);

	वापस ret;
पूर्ण

/**
 * batadv_netlink_hardअगर_fill() - Fill message with hardअगर attributes
 * @msg: Netlink message to dump पूर्णांकo
 * @bat_priv: the bat priv with all the soft पूर्णांकerface inक्रमmation
 * @hard_अगरace: hard पूर्णांकerface which was modअगरied
 * @cmd: type of message to generate
 * @portid: Port making netlink request
 * @seq: sequence number क्रम message
 * @flags: Additional flags क्रम message
 * @cb: Control block containing additional options
 *
 * Return: 0 on success or negative error number in हाल of failure
 */
अटल पूर्णांक batadv_netlink_hardअगर_fill(काष्ठा sk_buff *msg,
				      काष्ठा batadv_priv *bat_priv,
				      काष्ठा batadv_hard_अगरace *hard_अगरace,
				      क्रमागत batadv_nl_commands cmd,
				      u32 portid, u32 seq, पूर्णांक flags,
				      काष्ठा netlink_callback *cb)
अणु
	काष्ठा net_device *net_dev = hard_अगरace->net_dev;
	व्योम *hdr;

	hdr = genlmsg_put(msg, portid, seq, &batadv_netlink_family, flags, cmd);
	अगर (!hdr)
		वापस -ENOBUFS;

	अगर (cb)
		genl_dump_check_consistent(cb, hdr);

	अगर (nla_put_u32(msg, BATADV_ATTR_MESH_IFINDEX,
			bat_priv->soft_अगरace->अगरindex))
		जाओ nla_put_failure;

	अगर (nla_put_u32(msg, BATADV_ATTR_HARD_IFINDEX,
			net_dev->अगरindex) ||
	    nla_put_string(msg, BATADV_ATTR_HARD_IFNAME,
			   net_dev->name) ||
	    nla_put(msg, BATADV_ATTR_HARD_ADDRESS, ETH_ALEN,
		    net_dev->dev_addr))
		जाओ nla_put_failure;

	अगर (hard_अगरace->अगर_status == BATADV_IF_ACTIVE) अणु
		अगर (nla_put_flag(msg, BATADV_ATTR_ACTIVE))
			जाओ nla_put_failure;
	पूर्ण

	अगर (nla_put_u8(msg, BATADV_ATTR_HOP_PENALTY,
		       atomic_पढ़ो(&hard_अगरace->hop_penalty)))
		जाओ nla_put_failure;

#अगर_घोषित CONFIG_BATMAN_ADV_BATMAN_V
	अगर (nla_put_u32(msg, BATADV_ATTR_ELP_INTERVAL,
			atomic_पढ़ो(&hard_अगरace->bat_v.elp_पूर्णांकerval)))
		जाओ nla_put_failure;

	अगर (nla_put_u32(msg, BATADV_ATTR_THROUGHPUT_OVERRIDE,
			atomic_पढ़ो(&hard_अगरace->bat_v.throughput_override)))
		जाओ nla_put_failure;
#पूर्ण_अगर /* CONFIG_BATMAN_ADV_BATMAN_V */

	genlmsg_end(msg, hdr);
	वापस 0;

nla_put_failure:
	genlmsg_cancel(msg, hdr);
	वापस -EMSGSIZE;
पूर्ण

/**
 * batadv_netlink_notअगरy_hardअगर() - send hardअगर attributes to listener
 * @bat_priv: the bat priv with all the soft पूर्णांकerface inक्रमmation
 * @hard_अगरace: hard पूर्णांकerface which was modअगरied
 *
 * Return: 0 on success, < 0 on error
 */
पूर्णांक batadv_netlink_notअगरy_hardअगर(काष्ठा batadv_priv *bat_priv,
				 काष्ठा batadv_hard_अगरace *hard_अगरace)
अणु
	काष्ठा sk_buff *msg;
	पूर्णांक ret;

	msg = nlmsg_new(NLMSG_DEFAULT_SIZE, GFP_KERNEL);
	अगर (!msg)
		वापस -ENOMEM;

	ret = batadv_netlink_hardअगर_fill(msg, bat_priv, hard_अगरace,
					 BATADV_CMD_SET_HARDIF, 0, 0, 0, शून्य);
	अगर (ret < 0) अणु
		nlmsg_मुक्त(msg);
		वापस ret;
	पूर्ण

	genlmsg_multicast_netns(&batadv_netlink_family,
				dev_net(bat_priv->soft_अगरace), msg, 0,
				BATADV_NL_MCGRP_CONFIG, GFP_KERNEL);

	वापस 0;
पूर्ण

/**
 * batadv_netlink_get_hardअगर() - Get hardअगर attributes
 * @skb: Netlink message with request data
 * @info: receiver inक्रमmation
 *
 * Return: 0 on success or negative error number in हाल of failure
 */
अटल पूर्णांक batadv_netlink_get_hardअगर(काष्ठा sk_buff *skb,
				     काष्ठा genl_info *info)
अणु
	काष्ठा batadv_hard_अगरace *hard_अगरace = info->user_ptr[1];
	काष्ठा batadv_priv *bat_priv = info->user_ptr[0];
	काष्ठा sk_buff *msg;
	पूर्णांक ret;

	msg = nlmsg_new(NLMSG_DEFAULT_SIZE, GFP_KERNEL);
	अगर (!msg)
		वापस -ENOMEM;

	ret = batadv_netlink_hardअगर_fill(msg, bat_priv, hard_अगरace,
					 BATADV_CMD_GET_HARDIF,
					 info->snd_portid, info->snd_seq, 0,
					 शून्य);
	अगर (ret < 0) अणु
		nlmsg_मुक्त(msg);
		वापस ret;
	पूर्ण

	ret = genlmsg_reply(msg, info);

	वापस ret;
पूर्ण

/**
 * batadv_netlink_set_hardअगर() - Set hardअगर attributes
 * @skb: Netlink message with request data
 * @info: receiver inक्रमmation
 *
 * Return: 0 on success or negative error number in हाल of failure
 */
अटल पूर्णांक batadv_netlink_set_hardअगर(काष्ठा sk_buff *skb,
				     काष्ठा genl_info *info)
अणु
	काष्ठा batadv_hard_अगरace *hard_अगरace = info->user_ptr[1];
	काष्ठा batadv_priv *bat_priv = info->user_ptr[0];
	काष्ठा nlattr *attr;

	अगर (info->attrs[BATADV_ATTR_HOP_PENALTY]) अणु
		attr = info->attrs[BATADV_ATTR_HOP_PENALTY];

		atomic_set(&hard_अगरace->hop_penalty, nla_get_u8(attr));
	पूर्ण

#अगर_घोषित CONFIG_BATMAN_ADV_BATMAN_V

	अगर (info->attrs[BATADV_ATTR_ELP_INTERVAL]) अणु
		attr = info->attrs[BATADV_ATTR_ELP_INTERVAL];

		atomic_set(&hard_अगरace->bat_v.elp_पूर्णांकerval, nla_get_u32(attr));
	पूर्ण

	अगर (info->attrs[BATADV_ATTR_THROUGHPUT_OVERRIDE]) अणु
		attr = info->attrs[BATADV_ATTR_THROUGHPUT_OVERRIDE];

		atomic_set(&hard_अगरace->bat_v.throughput_override,
			   nla_get_u32(attr));
	पूर्ण
#पूर्ण_अगर /* CONFIG_BATMAN_ADV_BATMAN_V */

	batadv_netlink_notअगरy_hardअगर(bat_priv, hard_अगरace);

	वापस 0;
पूर्ण

/**
 * batadv_netlink_dump_hardअगर() - Dump all hard पूर्णांकerface पूर्णांकo a messages
 * @msg: Netlink message to dump पूर्णांकo
 * @cb: Parameters from query
 *
 * Return: error code, or length of reply message on success
 */
अटल पूर्णांक
batadv_netlink_dump_hardअगर(काष्ठा sk_buff *msg, काष्ठा netlink_callback *cb)
अणु
	काष्ठा net *net = sock_net(cb->skb->sk);
	काष्ठा net_device *soft_अगरace;
	काष्ठा batadv_hard_अगरace *hard_अगरace;
	काष्ठा batadv_priv *bat_priv;
	पूर्णांक अगरindex;
	पूर्णांक portid = NETLINK_CB(cb->skb).portid;
	पूर्णांक skip = cb->args[0];
	पूर्णांक i = 0;

	अगरindex = batadv_netlink_get_अगरindex(cb->nlh,
					     BATADV_ATTR_MESH_IFINDEX);
	अगर (!अगरindex)
		वापस -EINVAL;

	soft_अगरace = dev_get_by_index(net, अगरindex);
	अगर (!soft_अगरace)
		वापस -ENODEV;

	अगर (!batadv_softअगर_is_valid(soft_अगरace)) अणु
		dev_put(soft_अगरace);
		वापस -ENODEV;
	पूर्ण

	bat_priv = netdev_priv(soft_अगरace);

	rtnl_lock();
	cb->seq = batadv_hardअगर_generation << 1 | 1;

	list_क्रम_each_entry(hard_अगरace, &batadv_hardअगर_list, list) अणु
		अगर (hard_अगरace->soft_अगरace != soft_अगरace)
			जारी;

		अगर (i++ < skip)
			जारी;

		अगर (batadv_netlink_hardअगर_fill(msg, bat_priv, hard_अगरace,
					       BATADV_CMD_GET_HARDIF,
					       portid, cb->nlh->nlmsg_seq,
					       NLM_F_MULTI, cb)) अणु
			i--;
			अवरोध;
		पूर्ण
	पूर्ण

	rtnl_unlock();

	dev_put(soft_अगरace);

	cb->args[0] = i;

	वापस msg->len;
पूर्ण

/**
 * batadv_netlink_vlan_fill() - Fill message with vlan attributes
 * @msg: Netlink message to dump पूर्णांकo
 * @bat_priv: the bat priv with all the soft पूर्णांकerface inक्रमmation
 * @vlan: vlan which was modअगरied
 * @cmd: type of message to generate
 * @portid: Port making netlink request
 * @seq: sequence number क्रम message
 * @flags: Additional flags क्रम message
 *
 * Return: 0 on success or negative error number in हाल of failure
 */
अटल पूर्णांक batadv_netlink_vlan_fill(काष्ठा sk_buff *msg,
				    काष्ठा batadv_priv *bat_priv,
				    काष्ठा batadv_softअगर_vlan *vlan,
				    क्रमागत batadv_nl_commands cmd,
				    u32 portid, u32 seq, पूर्णांक flags)
अणु
	व्योम *hdr;

	hdr = genlmsg_put(msg, portid, seq, &batadv_netlink_family, flags, cmd);
	अगर (!hdr)
		वापस -ENOBUFS;

	अगर (nla_put_u32(msg, BATADV_ATTR_MESH_IFINDEX,
			bat_priv->soft_अगरace->अगरindex))
		जाओ nla_put_failure;

	अगर (nla_put_u32(msg, BATADV_ATTR_VLANID, vlan->vid & VLAN_VID_MASK))
		जाओ nla_put_failure;

	अगर (nla_put_u8(msg, BATADV_ATTR_AP_ISOLATION_ENABLED,
		       !!atomic_पढ़ो(&vlan->ap_isolation)))
		जाओ nla_put_failure;

	genlmsg_end(msg, hdr);
	वापस 0;

nla_put_failure:
	genlmsg_cancel(msg, hdr);
	वापस -EMSGSIZE;
पूर्ण

/**
 * batadv_netlink_notअगरy_vlan() - send vlan attributes to listener
 * @bat_priv: the bat priv with all the soft पूर्णांकerface inक्रमmation
 * @vlan: vlan which was modअगरied
 *
 * Return: 0 on success, < 0 on error
 */
पूर्णांक batadv_netlink_notअगरy_vlan(काष्ठा batadv_priv *bat_priv,
			       काष्ठा batadv_softअगर_vlan *vlan)
अणु
	काष्ठा sk_buff *msg;
	पूर्णांक ret;

	msg = nlmsg_new(NLMSG_DEFAULT_SIZE, GFP_KERNEL);
	अगर (!msg)
		वापस -ENOMEM;

	ret = batadv_netlink_vlan_fill(msg, bat_priv, vlan,
				       BATADV_CMD_SET_VLAN, 0, 0, 0);
	अगर (ret < 0) अणु
		nlmsg_मुक्त(msg);
		वापस ret;
	पूर्ण

	genlmsg_multicast_netns(&batadv_netlink_family,
				dev_net(bat_priv->soft_अगरace), msg, 0,
				BATADV_NL_MCGRP_CONFIG, GFP_KERNEL);

	वापस 0;
पूर्ण

/**
 * batadv_netlink_get_vlan() - Get vlan attributes
 * @skb: Netlink message with request data
 * @info: receiver inक्रमmation
 *
 * Return: 0 on success or negative error number in हाल of failure
 */
अटल पूर्णांक batadv_netlink_get_vlan(काष्ठा sk_buff *skb, काष्ठा genl_info *info)
अणु
	काष्ठा batadv_softअगर_vlan *vlan = info->user_ptr[1];
	काष्ठा batadv_priv *bat_priv = info->user_ptr[0];
	काष्ठा sk_buff *msg;
	पूर्णांक ret;

	msg = nlmsg_new(NLMSG_DEFAULT_SIZE, GFP_KERNEL);
	अगर (!msg)
		वापस -ENOMEM;

	ret = batadv_netlink_vlan_fill(msg, bat_priv, vlan, BATADV_CMD_GET_VLAN,
				       info->snd_portid, info->snd_seq, 0);
	अगर (ret < 0) अणु
		nlmsg_मुक्त(msg);
		वापस ret;
	पूर्ण

	ret = genlmsg_reply(msg, info);

	वापस ret;
पूर्ण

/**
 * batadv_netlink_set_vlan() - Get vlan attributes
 * @skb: Netlink message with request data
 * @info: receiver inक्रमmation
 *
 * Return: 0 on success or negative error number in हाल of failure
 */
अटल पूर्णांक batadv_netlink_set_vlan(काष्ठा sk_buff *skb, काष्ठा genl_info *info)
अणु
	काष्ठा batadv_softअगर_vlan *vlan = info->user_ptr[1];
	काष्ठा batadv_priv *bat_priv = info->user_ptr[0];
	काष्ठा nlattr *attr;

	अगर (info->attrs[BATADV_ATTR_AP_ISOLATION_ENABLED]) अणु
		attr = info->attrs[BATADV_ATTR_AP_ISOLATION_ENABLED];

		atomic_set(&vlan->ap_isolation, !!nla_get_u8(attr));
	पूर्ण

	batadv_netlink_notअगरy_vlan(bat_priv, vlan);

	वापस 0;
पूर्ण

/**
 * batadv_get_softअगर_from_info() - Retrieve soft पूर्णांकerface from genl attributes
 * @net: the applicable net namespace
 * @info: receiver inक्रमmation
 *
 * Return: Poपूर्णांकer to soft पूर्णांकerface (with increased refcnt) on success, error
 *  poपूर्णांकer on error
 */
अटल काष्ठा net_device *
batadv_get_softअगर_from_info(काष्ठा net *net, काष्ठा genl_info *info)
अणु
	काष्ठा net_device *soft_अगरace;
	पूर्णांक अगरindex;

	अगर (!info->attrs[BATADV_ATTR_MESH_IFINDEX])
		वापस ERR_PTR(-EINVAL);

	अगरindex = nla_get_u32(info->attrs[BATADV_ATTR_MESH_IFINDEX]);

	soft_अगरace = dev_get_by_index(net, अगरindex);
	अगर (!soft_अगरace)
		वापस ERR_PTR(-ENODEV);

	अगर (!batadv_softअगर_is_valid(soft_अगरace))
		जाओ err_put_softअगर;

	वापस soft_अगरace;

err_put_softअगर:
	dev_put(soft_अगरace);

	वापस ERR_PTR(-EINVAL);
पूर्ण

/**
 * batadv_get_hardअगर_from_info() - Retrieve hardअगर from genl attributes
 * @bat_priv: the bat priv with all the soft पूर्णांकerface inक्रमmation
 * @net: the applicable net namespace
 * @info: receiver inक्रमmation
 *
 * Return: Poपूर्णांकer to hard पूर्णांकerface (with increased refcnt) on success, error
 *  poपूर्णांकer on error
 */
अटल काष्ठा batadv_hard_अगरace *
batadv_get_hardअगर_from_info(काष्ठा batadv_priv *bat_priv, काष्ठा net *net,
			    काष्ठा genl_info *info)
अणु
	काष्ठा batadv_hard_अगरace *hard_अगरace;
	काष्ठा net_device *hard_dev;
	अचिन्हित पूर्णांक hardअगर_index;

	अगर (!info->attrs[BATADV_ATTR_HARD_IFINDEX])
		वापस ERR_PTR(-EINVAL);

	hardअगर_index = nla_get_u32(info->attrs[BATADV_ATTR_HARD_IFINDEX]);

	hard_dev = dev_get_by_index(net, hardअगर_index);
	अगर (!hard_dev)
		वापस ERR_PTR(-ENODEV);

	hard_अगरace = batadv_hardअगर_get_by_netdev(hard_dev);
	अगर (!hard_अगरace)
		जाओ err_put_harddev;

	अगर (hard_अगरace->soft_अगरace != bat_priv->soft_अगरace)
		जाओ err_put_hardअगर;

	/* hard_dev is referenced by hard_अगरace and not needed here */
	dev_put(hard_dev);

	वापस hard_अगरace;

err_put_hardअगर:
	batadv_hardअगर_put(hard_अगरace);
err_put_harddev:
	dev_put(hard_dev);

	वापस ERR_PTR(-EINVAL);
पूर्ण

/**
 * batadv_get_vlan_from_info() - Retrieve vlan from genl attributes
 * @bat_priv: the bat priv with all the soft पूर्णांकerface inक्रमmation
 * @net: the applicable net namespace
 * @info: receiver inक्रमmation
 *
 * Return: Poपूर्णांकer to vlan on success (with increased refcnt), error poपूर्णांकer
 *  on error
 */
अटल काष्ठा batadv_softअगर_vlan *
batadv_get_vlan_from_info(काष्ठा batadv_priv *bat_priv, काष्ठा net *net,
			  काष्ठा genl_info *info)
अणु
	काष्ठा batadv_softअगर_vlan *vlan;
	u16 vid;

	अगर (!info->attrs[BATADV_ATTR_VLANID])
		वापस ERR_PTR(-EINVAL);

	vid = nla_get_u16(info->attrs[BATADV_ATTR_VLANID]);

	vlan = batadv_softअगर_vlan_get(bat_priv, vid | BATADV_VLAN_HAS_TAG);
	अगर (!vlan)
		वापस ERR_PTR(-ENOENT);

	वापस vlan;
पूर्ण

/**
 * batadv_pre_करोit() - Prepare baपंचांगan-adv genl करोit request
 * @ops: requested netlink operation
 * @skb: Netlink message with request data
 * @info: receiver inक्रमmation
 *
 * Return: 0 on success or negative error number in हाल of failure
 */
अटल पूर्णांक batadv_pre_करोit(स्थिर काष्ठा genl_ops *ops, काष्ठा sk_buff *skb,
			   काष्ठा genl_info *info)
अणु
	काष्ठा net *net = genl_info_net(info);
	काष्ठा batadv_hard_अगरace *hard_अगरace;
	काष्ठा batadv_priv *bat_priv = शून्य;
	काष्ठा batadv_softअगर_vlan *vlan;
	काष्ठा net_device *soft_अगरace;
	u8 user_ptr1_flags;
	u8 mesh_dep_flags;
	पूर्णांक ret;

	user_ptr1_flags = BATADV_FLAG_NEED_HARDIF | BATADV_FLAG_NEED_VLAN;
	अगर (WARN_ON(hweight8(ops->पूर्णांकernal_flags & user_ptr1_flags) > 1))
		वापस -EINVAL;

	mesh_dep_flags = BATADV_FLAG_NEED_HARDIF | BATADV_FLAG_NEED_VLAN;
	अगर (WARN_ON((ops->पूर्णांकernal_flags & mesh_dep_flags) &&
		    (~ops->पूर्णांकernal_flags & BATADV_FLAG_NEED_MESH)))
		वापस -EINVAL;

	अगर (ops->पूर्णांकernal_flags & BATADV_FLAG_NEED_MESH) अणु
		soft_अगरace = batadv_get_softअगर_from_info(net, info);
		अगर (IS_ERR(soft_अगरace))
			वापस PTR_ERR(soft_अगरace);

		bat_priv = netdev_priv(soft_अगरace);
		info->user_ptr[0] = bat_priv;
	पूर्ण

	अगर (ops->पूर्णांकernal_flags & BATADV_FLAG_NEED_HARDIF) अणु
		hard_अगरace = batadv_get_hardअगर_from_info(bat_priv, net, info);
		अगर (IS_ERR(hard_अगरace)) अणु
			ret = PTR_ERR(hard_अगरace);
			जाओ err_put_softअगर;
		पूर्ण

		info->user_ptr[1] = hard_अगरace;
	पूर्ण

	अगर (ops->पूर्णांकernal_flags & BATADV_FLAG_NEED_VLAN) अणु
		vlan = batadv_get_vlan_from_info(bat_priv, net, info);
		अगर (IS_ERR(vlan)) अणु
			ret = PTR_ERR(vlan);
			जाओ err_put_softअगर;
		पूर्ण

		info->user_ptr[1] = vlan;
	पूर्ण

	वापस 0;

err_put_softअगर:
	अगर (bat_priv)
		dev_put(bat_priv->soft_अगरace);

	वापस ret;
पूर्ण

/**
 * batadv_post_करोit() - End baपंचांगan-adv genl करोit request
 * @ops: requested netlink operation
 * @skb: Netlink message with request data
 * @info: receiver inक्रमmation
 */
अटल व्योम batadv_post_करोit(स्थिर काष्ठा genl_ops *ops, काष्ठा sk_buff *skb,
			     काष्ठा genl_info *info)
अणु
	काष्ठा batadv_hard_अगरace *hard_अगरace;
	काष्ठा batadv_softअगर_vlan *vlan;
	काष्ठा batadv_priv *bat_priv;

	अगर (ops->पूर्णांकernal_flags & BATADV_FLAG_NEED_HARDIF &&
	    info->user_ptr[1]) अणु
		hard_अगरace = info->user_ptr[1];

		batadv_hardअगर_put(hard_अगरace);
	पूर्ण

	अगर (ops->पूर्णांकernal_flags & BATADV_FLAG_NEED_VLAN && info->user_ptr[1]) अणु
		vlan = info->user_ptr[1];
		batadv_softअगर_vlan_put(vlan);
	पूर्ण

	अगर (ops->पूर्णांकernal_flags & BATADV_FLAG_NEED_MESH && info->user_ptr[0]) अणु
		bat_priv = info->user_ptr[0];
		dev_put(bat_priv->soft_अगरace);
	पूर्ण
पूर्ण

अटल स्थिर काष्ठा genl_small_ops batadv_netlink_ops[] = अणु
	अणु
		.cmd = BATADV_CMD_GET_MESH,
		.validate = GENL_DONT_VALIDATE_STRICT | GENL_DONT_VALIDATE_DUMP,
		/* can be retrieved by unprivileged users */
		.करोit = batadv_netlink_get_mesh,
		.पूर्णांकernal_flags = BATADV_FLAG_NEED_MESH,
	पूर्ण,
	अणु
		.cmd = BATADV_CMD_TP_METER,
		.validate = GENL_DONT_VALIDATE_STRICT | GENL_DONT_VALIDATE_DUMP,
		.flags = GENL_ADMIN_PERM,
		.करोit = batadv_netlink_tp_meter_start,
		.पूर्णांकernal_flags = BATADV_FLAG_NEED_MESH,
	पूर्ण,
	अणु
		.cmd = BATADV_CMD_TP_METER_CANCEL,
		.validate = GENL_DONT_VALIDATE_STRICT | GENL_DONT_VALIDATE_DUMP,
		.flags = GENL_ADMIN_PERM,
		.करोit = batadv_netlink_tp_meter_cancel,
		.पूर्णांकernal_flags = BATADV_FLAG_NEED_MESH,
	पूर्ण,
	अणु
		.cmd = BATADV_CMD_GET_ROUTING_ALGOS,
		.validate = GENL_DONT_VALIDATE_STRICT | GENL_DONT_VALIDATE_DUMP,
		.flags = GENL_ADMIN_PERM,
		.dumpit = batadv_algo_dump,
	पूर्ण,
	अणु
		.cmd = BATADV_CMD_GET_HARDIF,
		.validate = GENL_DONT_VALIDATE_STRICT | GENL_DONT_VALIDATE_DUMP,
		/* can be retrieved by unprivileged users */
		.dumpit = batadv_netlink_dump_hardअगर,
		.करोit = batadv_netlink_get_hardअगर,
		.पूर्णांकernal_flags = BATADV_FLAG_NEED_MESH |
				  BATADV_FLAG_NEED_HARDIF,
	पूर्ण,
	अणु
		.cmd = BATADV_CMD_GET_TRANSTABLE_LOCAL,
		.validate = GENL_DONT_VALIDATE_STRICT | GENL_DONT_VALIDATE_DUMP,
		.flags = GENL_ADMIN_PERM,
		.dumpit = batadv_tt_local_dump,
	पूर्ण,
	अणु
		.cmd = BATADV_CMD_GET_TRANSTABLE_GLOBAL,
		.validate = GENL_DONT_VALIDATE_STRICT | GENL_DONT_VALIDATE_DUMP,
		.flags = GENL_ADMIN_PERM,
		.dumpit = batadv_tt_global_dump,
	पूर्ण,
	अणु
		.cmd = BATADV_CMD_GET_ORIGINATORS,
		.validate = GENL_DONT_VALIDATE_STRICT | GENL_DONT_VALIDATE_DUMP,
		.flags = GENL_ADMIN_PERM,
		.dumpit = batadv_orig_dump,
	पूर्ण,
	अणु
		.cmd = BATADV_CMD_GET_NEIGHBORS,
		.validate = GENL_DONT_VALIDATE_STRICT | GENL_DONT_VALIDATE_DUMP,
		.flags = GENL_ADMIN_PERM,
		.dumpit = batadv_hardअगर_neigh_dump,
	पूर्ण,
	अणु
		.cmd = BATADV_CMD_GET_GATEWAYS,
		.validate = GENL_DONT_VALIDATE_STRICT | GENL_DONT_VALIDATE_DUMP,
		.flags = GENL_ADMIN_PERM,
		.dumpit = batadv_gw_dump,
	पूर्ण,
	अणु
		.cmd = BATADV_CMD_GET_BLA_CLAIM,
		.validate = GENL_DONT_VALIDATE_STRICT | GENL_DONT_VALIDATE_DUMP,
		.flags = GENL_ADMIN_PERM,
		.dumpit = batadv_bla_claim_dump,
	पूर्ण,
	अणु
		.cmd = BATADV_CMD_GET_BLA_BACKBONE,
		.validate = GENL_DONT_VALIDATE_STRICT | GENL_DONT_VALIDATE_DUMP,
		.flags = GENL_ADMIN_PERM,
		.dumpit = batadv_bla_backbone_dump,
	पूर्ण,
	अणु
		.cmd = BATADV_CMD_GET_DAT_CACHE,
		.validate = GENL_DONT_VALIDATE_STRICT | GENL_DONT_VALIDATE_DUMP,
		.flags = GENL_ADMIN_PERM,
		.dumpit = batadv_dat_cache_dump,
	पूर्ण,
	अणु
		.cmd = BATADV_CMD_GET_MCAST_FLAGS,
		.validate = GENL_DONT_VALIDATE_STRICT | GENL_DONT_VALIDATE_DUMP,
		.flags = GENL_ADMIN_PERM,
		.dumpit = batadv_mcast_flags_dump,
	पूर्ण,
	अणु
		.cmd = BATADV_CMD_SET_MESH,
		.validate = GENL_DONT_VALIDATE_STRICT | GENL_DONT_VALIDATE_DUMP,
		.flags = GENL_ADMIN_PERM,
		.करोit = batadv_netlink_set_mesh,
		.पूर्णांकernal_flags = BATADV_FLAG_NEED_MESH,
	पूर्ण,
	अणु
		.cmd = BATADV_CMD_SET_HARDIF,
		.validate = GENL_DONT_VALIDATE_STRICT | GENL_DONT_VALIDATE_DUMP,
		.flags = GENL_ADMIN_PERM,
		.करोit = batadv_netlink_set_hardअगर,
		.पूर्णांकernal_flags = BATADV_FLAG_NEED_MESH |
				  BATADV_FLAG_NEED_HARDIF,
	पूर्ण,
	अणु
		.cmd = BATADV_CMD_GET_VLAN,
		.validate = GENL_DONT_VALIDATE_STRICT | GENL_DONT_VALIDATE_DUMP,
		/* can be retrieved by unprivileged users */
		.करोit = batadv_netlink_get_vlan,
		.पूर्णांकernal_flags = BATADV_FLAG_NEED_MESH |
				  BATADV_FLAG_NEED_VLAN,
	पूर्ण,
	अणु
		.cmd = BATADV_CMD_SET_VLAN,
		.validate = GENL_DONT_VALIDATE_STRICT | GENL_DONT_VALIDATE_DUMP,
		.flags = GENL_ADMIN_PERM,
		.करोit = batadv_netlink_set_vlan,
		.पूर्णांकernal_flags = BATADV_FLAG_NEED_MESH |
				  BATADV_FLAG_NEED_VLAN,
	पूर्ण,
पूर्ण;

काष्ठा genl_family batadv_netlink_family __ro_after_init = अणु
	.hdrsize = 0,
	.name = BATADV_NL_NAME,
	.version = 1,
	.maxattr = BATADV_ATTR_MAX,
	.policy = batadv_netlink_policy,
	.netnsok = true,
	.pre_करोit = batadv_pre_करोit,
	.post_करोit = batadv_post_करोit,
	.module = THIS_MODULE,
	.small_ops = batadv_netlink_ops,
	.n_small_ops = ARRAY_SIZE(batadv_netlink_ops),
	.mcgrps = batadv_netlink_mcgrps,
	.n_mcgrps = ARRAY_SIZE(batadv_netlink_mcgrps),
पूर्ण;

/**
 * batadv_netlink_रेजिस्टर() - रेजिस्टर batadv genl netlink family
 */
व्योम __init batadv_netlink_रेजिस्टर(व्योम)
अणु
	पूर्णांक ret;

	ret = genl_रेजिस्टर_family(&batadv_netlink_family);
	अगर (ret)
		pr_warn("unable to register netlink family");
पूर्ण

/**
 * batadv_netlink_unरेजिस्टर() - unरेजिस्टर batadv genl netlink family
 */
व्योम batadv_netlink_unरेजिस्टर(व्योम)
अणु
	genl_unरेजिस्टर_family(&batadv_netlink_family);
पूर्ण
