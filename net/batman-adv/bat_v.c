<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/* Copyright (C) B.A.T.M.A.N. contributors:
 *
 * Linus Lथञssing, Marek Lindner
 */

#समावेश "bat_v.h"
#समावेश "main.h"

#समावेश <linux/atomic.h>
#समावेश <linux/cache.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/अगर_ether.h>
#समावेश <linux/init.h>
#समावेश <linux/jअगरfies.h>
#समावेश <linux/kref.h>
#समावेश <linux/list.h>
#समावेश <linux/minmax.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/netlink.h>
#समावेश <linux/rculist.h>
#समावेश <linux/rcupdate.h>
#समावेश <linux/skbuff.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/मानकघोष.स>
#समावेश <linux/types.h>
#समावेश <linux/workqueue.h>
#समावेश <net/genetlink.h>
#समावेश <net/netlink.h>
#समावेश <uapi/linux/batadv_packet.h>
#समावेश <uapi/linux/baपंचांगan_adv.h>

#समावेश "bat_algo.h"
#समावेश "bat_v_elp.h"
#समावेश "bat_v_ogm.h"
#समावेश "gateway_client.h"
#समावेश "gateway_common.h"
#समावेश "hard-interface.h"
#समावेश "hash.h"
#समावेश "log.h"
#समावेश "netlink.h"
#समावेश "originator.h"

अटल व्योम batadv_v_अगरace_activate(काष्ठा batadv_hard_अगरace *hard_अगरace)
अणु
	काष्ठा batadv_priv *bat_priv = netdev_priv(hard_अगरace->soft_अगरace);
	काष्ठा batadv_hard_अगरace *primary_अगर;

	primary_अगर = batadv_primary_अगर_get_selected(bat_priv);

	अगर (primary_अगर) अणु
		batadv_v_elp_अगरace_activate(primary_अगर, hard_अगरace);
		batadv_hardअगर_put(primary_अगर);
	पूर्ण

	/* B.A.T.M.A.N. V करोes not use any queuing mechanism, thereक्रमe it can
	 * set the पूर्णांकerface as ACTIVE right away, without any risk of race
	 * condition
	 */
	अगर (hard_अगरace->अगर_status == BATADV_IF_TO_BE_ACTIVATED)
		hard_अगरace->अगर_status = BATADV_IF_ACTIVE;
पूर्ण

अटल पूर्णांक batadv_v_अगरace_enable(काष्ठा batadv_hard_अगरace *hard_अगरace)
अणु
	पूर्णांक ret;

	ret = batadv_v_elp_अगरace_enable(hard_अगरace);
	अगर (ret < 0)
		वापस ret;

	ret = batadv_v_ogm_अगरace_enable(hard_अगरace);
	अगर (ret < 0)
		batadv_v_elp_अगरace_disable(hard_अगरace);

	वापस ret;
पूर्ण

अटल व्योम batadv_v_अगरace_disable(काष्ठा batadv_hard_अगरace *hard_अगरace)
अणु
	batadv_v_ogm_अगरace_disable(hard_अगरace);
	batadv_v_elp_अगरace_disable(hard_अगरace);
पूर्ण

अटल व्योम batadv_v_primary_अगरace_set(काष्ठा batadv_hard_अगरace *hard_अगरace)
अणु
	batadv_v_elp_primary_अगरace_set(hard_अगरace);
	batadv_v_ogm_primary_अगरace_set(hard_अगरace);
पूर्ण

/**
 * batadv_v_अगरace_update_mac() - react to hard-पूर्णांकerface MAC address change
 * @hard_अगरace: the modअगरied पूर्णांकerface
 *
 * If the modअगरied पूर्णांकerface is the primary one, update the originator
 * address in the ELP and OGM messages to reflect the new MAC address.
 */
अटल व्योम batadv_v_अगरace_update_mac(काष्ठा batadv_hard_अगरace *hard_अगरace)
अणु
	काष्ठा batadv_priv *bat_priv = netdev_priv(hard_अगरace->soft_अगरace);
	काष्ठा batadv_hard_अगरace *primary_अगर;

	primary_अगर = batadv_primary_अगर_get_selected(bat_priv);
	अगर (primary_अगर != hard_अगरace)
		जाओ out;

	batadv_v_primary_अगरace_set(hard_अगरace);
out:
	अगर (primary_अगर)
		batadv_hardअगर_put(primary_अगर);
पूर्ण

अटल व्योम
batadv_v_hardअगर_neigh_init(काष्ठा batadv_hardअगर_neigh_node *hardअगर_neigh)
अणु
	ewma_throughput_init(&hardअगर_neigh->bat_v.throughput);
	INIT_WORK(&hardअगर_neigh->bat_v.metric_work,
		  batadv_v_elp_throughput_metric_update);
पूर्ण

/**
 * batadv_v_neigh_dump_neigh() - Dump a neighbour पूर्णांकo a message
 * @msg: Netlink message to dump पूर्णांकo
 * @portid: Port making netlink request
 * @seq: Sequence number of netlink message
 * @hardअगर_neigh: Neighbour to dump
 *
 * Return: Error code, or 0 on success
 */
अटल पूर्णांक
batadv_v_neigh_dump_neigh(काष्ठा sk_buff *msg, u32 portid, u32 seq,
			  काष्ठा batadv_hardअगर_neigh_node *hardअगर_neigh)
अणु
	व्योम *hdr;
	अचिन्हित पूर्णांक last_seen_msecs;
	u32 throughput;

	last_seen_msecs = jअगरfies_to_msecs(jअगरfies - hardअगर_neigh->last_seen);
	throughput = ewma_throughput_पढ़ो(&hardअगर_neigh->bat_v.throughput);
	throughput = throughput * 100;

	hdr = genlmsg_put(msg, portid, seq, &batadv_netlink_family, NLM_F_MULTI,
			  BATADV_CMD_GET_NEIGHBORS);
	अगर (!hdr)
		वापस -ENOBUFS;

	अगर (nla_put(msg, BATADV_ATTR_NEIGH_ADDRESS, ETH_ALEN,
		    hardअगर_neigh->addr) ||
	    nla_put_u32(msg, BATADV_ATTR_HARD_IFINDEX,
			hardअगर_neigh->अगर_incoming->net_dev->अगरindex) ||
	    nla_put_u32(msg, BATADV_ATTR_LAST_SEEN_MSECS,
			last_seen_msecs) ||
	    nla_put_u32(msg, BATADV_ATTR_THROUGHPUT, throughput))
		जाओ nla_put_failure;

	genlmsg_end(msg, hdr);
	वापस 0;

 nla_put_failure:
	genlmsg_cancel(msg, hdr);
	वापस -EMSGSIZE;
पूर्ण

/**
 * batadv_v_neigh_dump_hardअगर() - Dump the  neighbours of a hard पूर्णांकerface पूर्णांकo
 *  a message
 * @msg: Netlink message to dump पूर्णांकo
 * @portid: Port making netlink request
 * @seq: Sequence number of netlink message
 * @bat_priv: The bat priv with all the soft पूर्णांकerface inक्रमmation
 * @hard_अगरace: The hard पूर्णांकerface to be dumped
 * @idx_s: Entries to be skipped
 *
 * This function assumes the caller holds rcu_पढ़ो_lock().
 *
 * Return: Error code, or 0 on success
 */
अटल पूर्णांक
batadv_v_neigh_dump_hardअगर(काष्ठा sk_buff *msg, u32 portid, u32 seq,
			   काष्ठा batadv_priv *bat_priv,
			   काष्ठा batadv_hard_अगरace *hard_अगरace,
			   पूर्णांक *idx_s)
अणु
	काष्ठा batadv_hardअगर_neigh_node *hardअगर_neigh;
	पूर्णांक idx = 0;

	hlist_क्रम_each_entry_rcu(hardअगर_neigh,
				 &hard_अगरace->neigh_list, list) अणु
		अगर (idx++ < *idx_s)
			जारी;

		अगर (batadv_v_neigh_dump_neigh(msg, portid, seq, hardअगर_neigh)) अणु
			*idx_s = idx - 1;
			वापस -EMSGSIZE;
		पूर्ण
	पूर्ण

	*idx_s = 0;
	वापस 0;
पूर्ण

/**
 * batadv_v_neigh_dump() - Dump the neighbours of a hard पूर्णांकerface  पूर्णांकo a
 *  message
 * @msg: Netlink message to dump पूर्णांकo
 * @cb: Control block containing additional options
 * @bat_priv: The bat priv with all the soft पूर्णांकerface inक्रमmation
 * @single_hardअगर: Limit dumping to this hard पूर्णांकerface
 */
अटल व्योम
batadv_v_neigh_dump(काष्ठा sk_buff *msg, काष्ठा netlink_callback *cb,
		    काष्ठा batadv_priv *bat_priv,
		    काष्ठा batadv_hard_अगरace *single_hardअगर)
अणु
	काष्ठा batadv_hard_अगरace *hard_अगरace;
	पूर्णांक i_hardअगर = 0;
	पूर्णांक i_hardअगर_s = cb->args[0];
	पूर्णांक idx = cb->args[1];
	पूर्णांक portid = NETLINK_CB(cb->skb).portid;

	rcu_पढ़ो_lock();
	अगर (single_hardअगर) अणु
		अगर (i_hardअगर_s == 0) अणु
			अगर (batadv_v_neigh_dump_hardअगर(msg, portid,
						       cb->nlh->nlmsg_seq,
						       bat_priv, single_hardअगर,
						       &idx) == 0)
				i_hardअगर++;
		पूर्ण
	पूर्ण अन्यथा अणु
		list_क्रम_each_entry_rcu(hard_अगरace, &batadv_hardअगर_list, list) अणु
			अगर (hard_अगरace->soft_अगरace != bat_priv->soft_अगरace)
				जारी;

			अगर (i_hardअगर++ < i_hardअगर_s)
				जारी;

			अगर (batadv_v_neigh_dump_hardअगर(msg, portid,
						       cb->nlh->nlmsg_seq,
						       bat_priv, hard_अगरace,
						       &idx)) अणु
				i_hardअगर--;
				अवरोध;
			पूर्ण
		पूर्ण
	पूर्ण
	rcu_पढ़ो_unlock();

	cb->args[0] = i_hardअगर;
	cb->args[1] = idx;
पूर्ण

/**
 * batadv_v_orig_dump_subentry() - Dump an originator subentry पूर्णांकo a message
 * @msg: Netlink message to dump पूर्णांकo
 * @portid: Port making netlink request
 * @seq: Sequence number of netlink message
 * @bat_priv: The bat priv with all the soft पूर्णांकerface inक्रमmation
 * @अगर_outgoing: Limit dump to entries with this outgoing पूर्णांकerface
 * @orig_node: Originator to dump
 * @neigh_node: Single hops neighbour
 * @best: Is the best originator
 *
 * Return: Error code, or 0 on success
 */
अटल पूर्णांक
batadv_v_orig_dump_subentry(काष्ठा sk_buff *msg, u32 portid, u32 seq,
			    काष्ठा batadv_priv *bat_priv,
			    काष्ठा batadv_hard_अगरace *अगर_outgoing,
			    काष्ठा batadv_orig_node *orig_node,
			    काष्ठा batadv_neigh_node *neigh_node,
			    bool best)
अणु
	काष्ठा batadv_neigh_अगरinfo *n_अगरinfo;
	अचिन्हित पूर्णांक last_seen_msecs;
	u32 throughput;
	व्योम *hdr;

	n_अगरinfo = batadv_neigh_अगरinfo_get(neigh_node, अगर_outgoing);
	अगर (!n_अगरinfo)
		वापस 0;

	throughput = n_अगरinfo->bat_v.throughput * 100;

	batadv_neigh_अगरinfo_put(n_अगरinfo);

	last_seen_msecs = jअगरfies_to_msecs(jअगरfies - orig_node->last_seen);

	अगर (अगर_outgoing != BATADV_IF_DEFAULT &&
	    अगर_outgoing != neigh_node->अगर_incoming)
		वापस 0;

	hdr = genlmsg_put(msg, portid, seq, &batadv_netlink_family, NLM_F_MULTI,
			  BATADV_CMD_GET_ORIGINATORS);
	अगर (!hdr)
		वापस -ENOBUFS;

	अगर (nla_put(msg, BATADV_ATTR_ORIG_ADDRESS, ETH_ALEN, orig_node->orig) ||
	    nla_put(msg, BATADV_ATTR_NEIGH_ADDRESS, ETH_ALEN,
		    neigh_node->addr) ||
	    nla_put_u32(msg, BATADV_ATTR_HARD_IFINDEX,
			neigh_node->अगर_incoming->net_dev->अगरindex) ||
	    nla_put_u32(msg, BATADV_ATTR_THROUGHPUT, throughput) ||
	    nla_put_u32(msg, BATADV_ATTR_LAST_SEEN_MSECS,
			last_seen_msecs))
		जाओ nla_put_failure;

	अगर (best && nla_put_flag(msg, BATADV_ATTR_FLAG_BEST))
		जाओ nla_put_failure;

	genlmsg_end(msg, hdr);
	वापस 0;

 nla_put_failure:
	genlmsg_cancel(msg, hdr);
	वापस -EMSGSIZE;
पूर्ण

/**
 * batadv_v_orig_dump_entry() - Dump an originator entry पूर्णांकo a message
 * @msg: Netlink message to dump पूर्णांकo
 * @portid: Port making netlink request
 * @seq: Sequence number of netlink message
 * @bat_priv: The bat priv with all the soft पूर्णांकerface inक्रमmation
 * @अगर_outgoing: Limit dump to entries with this outgoing पूर्णांकerface
 * @orig_node: Originator to dump
 * @sub_s: Number of sub entries to skip
 *
 * This function assumes the caller holds rcu_पढ़ो_lock().
 *
 * Return: Error code, or 0 on success
 */
अटल पूर्णांक
batadv_v_orig_dump_entry(काष्ठा sk_buff *msg, u32 portid, u32 seq,
			 काष्ठा batadv_priv *bat_priv,
			 काष्ठा batadv_hard_अगरace *अगर_outgoing,
			 काष्ठा batadv_orig_node *orig_node, पूर्णांक *sub_s)
अणु
	काष्ठा batadv_neigh_node *neigh_node_best;
	काष्ठा batadv_neigh_node *neigh_node;
	पूर्णांक sub = 0;
	bool best;

	neigh_node_best = batadv_orig_router_get(orig_node, अगर_outgoing);
	अगर (!neigh_node_best)
		जाओ out;

	hlist_क्रम_each_entry_rcu(neigh_node, &orig_node->neigh_list, list) अणु
		अगर (sub++ < *sub_s)
			जारी;

		best = (neigh_node == neigh_node_best);

		अगर (batadv_v_orig_dump_subentry(msg, portid, seq, bat_priv,
						अगर_outgoing, orig_node,
						neigh_node, best)) अणु
			batadv_neigh_node_put(neigh_node_best);

			*sub_s = sub - 1;
			वापस -EMSGSIZE;
		पूर्ण
	पूर्ण

 out:
	अगर (neigh_node_best)
		batadv_neigh_node_put(neigh_node_best);

	*sub_s = 0;
	वापस 0;
पूर्ण

/**
 * batadv_v_orig_dump_bucket() - Dump an originator bucket पूर्णांकo a message
 * @msg: Netlink message to dump पूर्णांकo
 * @portid: Port making netlink request
 * @seq: Sequence number of netlink message
 * @bat_priv: The bat priv with all the soft पूर्णांकerface inक्रमmation
 * @अगर_outgoing: Limit dump to entries with this outgoing पूर्णांकerface
 * @head: Bucket to be dumped
 * @idx_s: Number of entries to be skipped
 * @sub: Number of sub entries to be skipped
 *
 * Return: Error code, or 0 on success
 */
अटल पूर्णांक
batadv_v_orig_dump_bucket(काष्ठा sk_buff *msg, u32 portid, u32 seq,
			  काष्ठा batadv_priv *bat_priv,
			  काष्ठा batadv_hard_अगरace *अगर_outgoing,
			  काष्ठा hlist_head *head, पूर्णांक *idx_s, पूर्णांक *sub)
अणु
	काष्ठा batadv_orig_node *orig_node;
	पूर्णांक idx = 0;

	rcu_पढ़ो_lock();
	hlist_क्रम_each_entry_rcu(orig_node, head, hash_entry) अणु
		अगर (idx++ < *idx_s)
			जारी;

		अगर (batadv_v_orig_dump_entry(msg, portid, seq, bat_priv,
					     अगर_outgoing, orig_node, sub)) अणु
			rcu_पढ़ो_unlock();
			*idx_s = idx - 1;
			वापस -EMSGSIZE;
		पूर्ण
	पूर्ण
	rcu_पढ़ो_unlock();

	*idx_s = 0;
	*sub = 0;
	वापस 0;
पूर्ण

/**
 * batadv_v_orig_dump() - Dump the originators पूर्णांकo a message
 * @msg: Netlink message to dump पूर्णांकo
 * @cb: Control block containing additional options
 * @bat_priv: The bat priv with all the soft पूर्णांकerface inक्रमmation
 * @अगर_outgoing: Limit dump to entries with this outgoing पूर्णांकerface
 */
अटल व्योम
batadv_v_orig_dump(काष्ठा sk_buff *msg, काष्ठा netlink_callback *cb,
		   काष्ठा batadv_priv *bat_priv,
		   काष्ठा batadv_hard_अगरace *अगर_outgoing)
अणु
	काष्ठा batadv_hashtable *hash = bat_priv->orig_hash;
	काष्ठा hlist_head *head;
	पूर्णांक bucket = cb->args[0];
	पूर्णांक idx = cb->args[1];
	पूर्णांक sub = cb->args[2];
	पूर्णांक portid = NETLINK_CB(cb->skb).portid;

	जबतक (bucket < hash->size) अणु
		head = &hash->table[bucket];

		अगर (batadv_v_orig_dump_bucket(msg, portid,
					      cb->nlh->nlmsg_seq,
					      bat_priv, अगर_outgoing, head, &idx,
					      &sub))
			अवरोध;

		bucket++;
	पूर्ण

	cb->args[0] = bucket;
	cb->args[1] = idx;
	cb->args[2] = sub;
पूर्ण

अटल पूर्णांक batadv_v_neigh_cmp(काष्ठा batadv_neigh_node *neigh1,
			      काष्ठा batadv_hard_अगरace *अगर_outgoing1,
			      काष्ठा batadv_neigh_node *neigh2,
			      काष्ठा batadv_hard_अगरace *अगर_outgoing2)
अणु
	काष्ठा batadv_neigh_अगरinfo *अगरinfo1, *अगरinfo2;
	पूर्णांक ret = 0;

	अगरinfo1 = batadv_neigh_अगरinfo_get(neigh1, अगर_outgoing1);
	अगर (!अगरinfo1)
		जाओ err_अगरinfo1;

	अगरinfo2 = batadv_neigh_अगरinfo_get(neigh2, अगर_outgoing2);
	अगर (!अगरinfo2)
		जाओ err_अगरinfo2;

	ret = अगरinfo1->bat_v.throughput - अगरinfo2->bat_v.throughput;

	batadv_neigh_अगरinfo_put(अगरinfo2);
err_अगरinfo2:
	batadv_neigh_अगरinfo_put(अगरinfo1);
err_अगरinfo1:
	वापस ret;
पूर्ण

अटल bool batadv_v_neigh_is_sob(काष्ठा batadv_neigh_node *neigh1,
				  काष्ठा batadv_hard_अगरace *अगर_outgoing1,
				  काष्ठा batadv_neigh_node *neigh2,
				  काष्ठा batadv_hard_अगरace *अगर_outgoing2)
अणु
	काष्ठा batadv_neigh_अगरinfo *अगरinfo1, *अगरinfo2;
	u32 threshold;
	bool ret = false;

	अगरinfo1 = batadv_neigh_अगरinfo_get(neigh1, अगर_outgoing1);
	अगर (!अगरinfo1)
		जाओ err_अगरinfo1;

	अगरinfo2 = batadv_neigh_अगरinfo_get(neigh2, अगर_outgoing2);
	अगर (!अगरinfo2)
		जाओ err_अगरinfo2;

	threshold = अगरinfo1->bat_v.throughput / 4;
	threshold = अगरinfo1->bat_v.throughput - threshold;

	ret = अगरinfo2->bat_v.throughput > threshold;

	batadv_neigh_अगरinfo_put(अगरinfo2);
err_अगरinfo2:
	batadv_neigh_अगरinfo_put(अगरinfo1);
err_अगरinfo1:
	वापस ret;
पूर्ण

/**
 * batadv_v_init_sel_class() - initialize GW selection class
 * @bat_priv: the bat priv with all the soft पूर्णांकerface inक्रमmation
 */
अटल व्योम batadv_v_init_sel_class(काष्ठा batadv_priv *bat_priv)
अणु
	/* set शेष throughput dअगरference threshold to 5Mbps */
	atomic_set(&bat_priv->gw.sel_class, 50);
पूर्ण

अटल sमाप_प्रकार batadv_v_store_sel_class(काष्ठा batadv_priv *bat_priv,
					अक्षर *buff, माप_प्रकार count)
अणु
	u32 old_class, class;

	अगर (!batadv_parse_throughput(bat_priv->soft_अगरace, buff,
				     "B.A.T.M.A.N. V GW selection class",
				     &class))
		वापस -EINVAL;

	old_class = atomic_पढ़ो(&bat_priv->gw.sel_class);
	atomic_set(&bat_priv->gw.sel_class, class);

	अगर (old_class != class)
		batadv_gw_reselect(bat_priv);

	वापस count;
पूर्ण

/**
 * batadv_v_gw_throughput_get() - retrieve the GW-bandwidth क्रम a given GW
 * @gw_node: the GW to retrieve the metric क्रम
 * @bw: the poपूर्णांकer where the metric will be stored. The metric is computed as
 *  the minimum between the GW advertised throughput and the path throughput to
 *  it in the mesh
 *
 * Return: 0 on success, -1 on failure
 */
अटल पूर्णांक batadv_v_gw_throughput_get(काष्ठा batadv_gw_node *gw_node, u32 *bw)
अणु
	काष्ठा batadv_neigh_अगरinfo *router_अगरinfo = शून्य;
	काष्ठा batadv_orig_node *orig_node;
	काष्ठा batadv_neigh_node *router;
	पूर्णांक ret = -1;

	orig_node = gw_node->orig_node;
	router = batadv_orig_router_get(orig_node, BATADV_IF_DEFAULT);
	अगर (!router)
		जाओ out;

	router_अगरinfo = batadv_neigh_अगरinfo_get(router, BATADV_IF_DEFAULT);
	अगर (!router_अगरinfo)
		जाओ out;

	/* the GW metric is computed as the minimum between the path throughput
	 * to reach the GW itself and the advertised bandwidth.
	 * This gives us an approximation of the effective throughput that the
	 * client can expect via this particular GW node
	 */
	*bw = router_अगरinfo->bat_v.throughput;
	*bw = min_t(u32, *bw, gw_node->bandwidth_करोwn);

	ret = 0;
out:
	अगर (router)
		batadv_neigh_node_put(router);
	अगर (router_अगरinfo)
		batadv_neigh_अगरinfo_put(router_अगरinfo);

	वापस ret;
पूर्ण

/**
 * batadv_v_gw_get_best_gw_node() - retrieve the best GW node
 * @bat_priv: the bat priv with all the soft पूर्णांकerface inक्रमmation
 *
 * Return: the GW node having the best GW-metric, शून्य अगर no GW is known
 */
अटल काष्ठा batadv_gw_node *
batadv_v_gw_get_best_gw_node(काष्ठा batadv_priv *bat_priv)
अणु
	काष्ठा batadv_gw_node *gw_node, *curr_gw = शून्य;
	u32 max_bw = 0, bw;

	rcu_पढ़ो_lock();
	hlist_क्रम_each_entry_rcu(gw_node, &bat_priv->gw.gateway_list, list) अणु
		अगर (!kref_get_unless_zero(&gw_node->refcount))
			जारी;

		अगर (batadv_v_gw_throughput_get(gw_node, &bw) < 0)
			जाओ next;

		अगर (curr_gw && bw <= max_bw)
			जाओ next;

		अगर (curr_gw)
			batadv_gw_node_put(curr_gw);

		curr_gw = gw_node;
		kref_get(&curr_gw->refcount);
		max_bw = bw;

next:
		batadv_gw_node_put(gw_node);
	पूर्ण
	rcu_पढ़ो_unlock();

	वापस curr_gw;
पूर्ण

/**
 * batadv_v_gw_is_eligible() - check अगर a originator would be selected as GW
 * @bat_priv: the bat priv with all the soft पूर्णांकerface inक्रमmation
 * @curr_gw_orig: originator representing the currently selected GW
 * @orig_node: the originator representing the new candidate
 *
 * Return: true अगर orig_node can be selected as current GW, false otherwise
 */
अटल bool batadv_v_gw_is_eligible(काष्ठा batadv_priv *bat_priv,
				    काष्ठा batadv_orig_node *curr_gw_orig,
				    काष्ठा batadv_orig_node *orig_node)
अणु
	काष्ठा batadv_gw_node *curr_gw, *orig_gw = शून्य;
	u32 gw_throughput, orig_throughput, threshold;
	bool ret = false;

	threshold = atomic_पढ़ो(&bat_priv->gw.sel_class);

	curr_gw = batadv_gw_node_get(bat_priv, curr_gw_orig);
	अगर (!curr_gw) अणु
		ret = true;
		जाओ out;
	पूर्ण

	अगर (batadv_v_gw_throughput_get(curr_gw, &gw_throughput) < 0) अणु
		ret = true;
		जाओ out;
	पूर्ण

	orig_gw = batadv_gw_node_get(bat_priv, orig_node);
	अगर (!orig_gw)
		जाओ out;

	अगर (batadv_v_gw_throughput_get(orig_gw, &orig_throughput) < 0)
		जाओ out;

	अगर (orig_throughput < gw_throughput)
		जाओ out;

	अगर ((orig_throughput - gw_throughput) < threshold)
		जाओ out;

	batadv_dbg(BATADV_DBG_BATMAN, bat_priv,
		   "Restarting gateway selection: better gateway found (throughput curr: %u, throughput new: %u)\n",
		   gw_throughput, orig_throughput);

	ret = true;
out:
	अगर (curr_gw)
		batadv_gw_node_put(curr_gw);
	अगर (orig_gw)
		batadv_gw_node_put(orig_gw);

	वापस ret;
पूर्ण

/**
 * batadv_v_gw_dump_entry() - Dump a gateway पूर्णांकo a message
 * @msg: Netlink message to dump पूर्णांकo
 * @portid: Port making netlink request
 * @cb: Control block containing additional options
 * @bat_priv: The bat priv with all the soft पूर्णांकerface inक्रमmation
 * @gw_node: Gateway to be dumped
 *
 * Return: Error code, or 0 on success
 */
अटल पूर्णांक batadv_v_gw_dump_entry(काष्ठा sk_buff *msg, u32 portid,
				  काष्ठा netlink_callback *cb,
				  काष्ठा batadv_priv *bat_priv,
				  काष्ठा batadv_gw_node *gw_node)
अणु
	काष्ठा batadv_neigh_अगरinfo *router_अगरinfo = शून्य;
	काष्ठा batadv_neigh_node *router;
	काष्ठा batadv_gw_node *curr_gw = शून्य;
	पूर्णांक ret = 0;
	व्योम *hdr;

	router = batadv_orig_router_get(gw_node->orig_node, BATADV_IF_DEFAULT);
	अगर (!router)
		जाओ out;

	router_अगरinfo = batadv_neigh_अगरinfo_get(router, BATADV_IF_DEFAULT);
	अगर (!router_अगरinfo)
		जाओ out;

	curr_gw = batadv_gw_get_selected_gw_node(bat_priv);

	hdr = genlmsg_put(msg, portid, cb->nlh->nlmsg_seq,
			  &batadv_netlink_family, NLM_F_MULTI,
			  BATADV_CMD_GET_GATEWAYS);
	अगर (!hdr) अणु
		ret = -ENOBUFS;
		जाओ out;
	पूर्ण

	genl_dump_check_consistent(cb, hdr);

	ret = -EMSGSIZE;

	अगर (curr_gw == gw_node) अणु
		अगर (nla_put_flag(msg, BATADV_ATTR_FLAG_BEST)) अणु
			genlmsg_cancel(msg, hdr);
			जाओ out;
		पूर्ण
	पूर्ण

	अगर (nla_put(msg, BATADV_ATTR_ORIG_ADDRESS, ETH_ALEN,
		    gw_node->orig_node->orig)) अणु
		genlmsg_cancel(msg, hdr);
		जाओ out;
	पूर्ण

	अगर (nla_put_u32(msg, BATADV_ATTR_THROUGHPUT,
			router_अगरinfo->bat_v.throughput)) अणु
		genlmsg_cancel(msg, hdr);
		जाओ out;
	पूर्ण

	अगर (nla_put(msg, BATADV_ATTR_ROUTER, ETH_ALEN, router->addr)) अणु
		genlmsg_cancel(msg, hdr);
		जाओ out;
	पूर्ण

	अगर (nla_put_string(msg, BATADV_ATTR_HARD_IFNAME,
			   router->अगर_incoming->net_dev->name)) अणु
		genlmsg_cancel(msg, hdr);
		जाओ out;
	पूर्ण

	अगर (nla_put_u32(msg, BATADV_ATTR_BANDWIDTH_DOWN,
			gw_node->bandwidth_करोwn)) अणु
		genlmsg_cancel(msg, hdr);
		जाओ out;
	पूर्ण

	अगर (nla_put_u32(msg, BATADV_ATTR_BANDWIDTH_UP, gw_node->bandwidth_up)) अणु
		genlmsg_cancel(msg, hdr);
		जाओ out;
	पूर्ण

	genlmsg_end(msg, hdr);
	ret = 0;

out:
	अगर (curr_gw)
		batadv_gw_node_put(curr_gw);
	अगर (router_अगरinfo)
		batadv_neigh_अगरinfo_put(router_अगरinfo);
	अगर (router)
		batadv_neigh_node_put(router);
	वापस ret;
पूर्ण

/**
 * batadv_v_gw_dump() - Dump gateways पूर्णांकo a message
 * @msg: Netlink message to dump पूर्णांकo
 * @cb: Control block containing additional options
 * @bat_priv: The bat priv with all the soft पूर्णांकerface inक्रमmation
 */
अटल व्योम batadv_v_gw_dump(काष्ठा sk_buff *msg, काष्ठा netlink_callback *cb,
			     काष्ठा batadv_priv *bat_priv)
अणु
	पूर्णांक portid = NETLINK_CB(cb->skb).portid;
	काष्ठा batadv_gw_node *gw_node;
	पूर्णांक idx_skip = cb->args[0];
	पूर्णांक idx = 0;

	spin_lock_bh(&bat_priv->gw.list_lock);
	cb->seq = bat_priv->gw.generation << 1 | 1;

	hlist_क्रम_each_entry(gw_node, &bat_priv->gw.gateway_list, list) अणु
		अगर (idx++ < idx_skip)
			जारी;

		अगर (batadv_v_gw_dump_entry(msg, portid, cb, bat_priv,
					   gw_node)) अणु
			idx_skip = idx - 1;
			जाओ unlock;
		पूर्ण
	पूर्ण

	idx_skip = idx;
unlock:
	spin_unlock_bh(&bat_priv->gw.list_lock);

	cb->args[0] = idx_skip;
पूर्ण

अटल काष्ठा batadv_algo_ops batadv_baपंचांगan_v __पढ़ो_mostly = अणु
	.name = "BATMAN_V",
	.अगरace = अणु
		.activate = batadv_v_अगरace_activate,
		.enable = batadv_v_अगरace_enable,
		.disable = batadv_v_अगरace_disable,
		.update_mac = batadv_v_अगरace_update_mac,
		.primary_set = batadv_v_primary_अगरace_set,
	पूर्ण,
	.neigh = अणु
		.hardअगर_init = batadv_v_hardअगर_neigh_init,
		.cmp = batadv_v_neigh_cmp,
		.is_similar_or_better = batadv_v_neigh_is_sob,
		.dump = batadv_v_neigh_dump,
	पूर्ण,
	.orig = अणु
		.dump = batadv_v_orig_dump,
	पूर्ण,
	.gw = अणु
		.init_sel_class = batadv_v_init_sel_class,
		.store_sel_class = batadv_v_store_sel_class,
		.get_best_gw_node = batadv_v_gw_get_best_gw_node,
		.is_eligible = batadv_v_gw_is_eligible,
		.dump = batadv_v_gw_dump,
	पूर्ण,
पूर्ण;

/**
 * batadv_v_hardअगर_init() - initialize the algorithm specअगरic fields in the
 *  hard-पूर्णांकerface object
 * @hard_अगरace: the hard-पूर्णांकerface to initialize
 */
व्योम batadv_v_hardअगर_init(काष्ठा batadv_hard_अगरace *hard_अगरace)
अणु
	/* enable link throughput स्वतः-detection by setting the throughput
	 * override to zero
	 */
	atomic_set(&hard_अगरace->bat_v.throughput_override, 0);
	atomic_set(&hard_अगरace->bat_v.elp_पूर्णांकerval, 500);

	hard_अगरace->bat_v.aggr_len = 0;
	skb_queue_head_init(&hard_अगरace->bat_v.aggr_list);
	INIT_DELAYED_WORK(&hard_अगरace->bat_v.aggr_wq,
			  batadv_v_ogm_aggr_work);
पूर्ण

/**
 * batadv_v_mesh_init() - initialize the B.A.T.M.A.N. V निजी resources क्रम a
 *  mesh
 * @bat_priv: the object representing the mesh पूर्णांकerface to initialise
 *
 * Return: 0 on success or a negative error code otherwise
 */
पूर्णांक batadv_v_mesh_init(काष्ठा batadv_priv *bat_priv)
अणु
	पूर्णांक ret = 0;

	ret = batadv_v_ogm_init(bat_priv);
	अगर (ret < 0)
		वापस ret;

	वापस 0;
पूर्ण

/**
 * batadv_v_mesh_मुक्त() - मुक्त the B.A.T.M.A.N. V निजी resources क्रम a mesh
 * @bat_priv: the object representing the mesh पूर्णांकerface to मुक्त
 */
व्योम batadv_v_mesh_मुक्त(काष्ठा batadv_priv *bat_priv)
अणु
	batadv_v_ogm_मुक्त(bat_priv);
पूर्ण

/**
 * batadv_v_init() - B.A.T.M.A.N. V initialization function
 *
 * Description: Takes care of initializing all the subcomponents.
 * It is invoked upon module load only.
 *
 * Return: 0 on success or a negative error code otherwise
 */
पूर्णांक __init batadv_v_init(व्योम)
अणु
	पूर्णांक ret;

	/* B.A.T.M.A.N. V echo location protocol packet  */
	ret = batadv_recv_handler_रेजिस्टर(BATADV_ELP,
					   batadv_v_elp_packet_recv);
	अगर (ret < 0)
		वापस ret;

	ret = batadv_recv_handler_रेजिस्टर(BATADV_OGM2,
					   batadv_v_ogm_packet_recv);
	अगर (ret < 0)
		जाओ elp_unरेजिस्टर;

	ret = batadv_algo_रेजिस्टर(&batadv_baपंचांगan_v);
	अगर (ret < 0)
		जाओ ogm_unरेजिस्टर;

	वापस ret;

ogm_unरेजिस्टर:
	batadv_recv_handler_unरेजिस्टर(BATADV_OGM2);

elp_unरेजिस्टर:
	batadv_recv_handler_unरेजिस्टर(BATADV_ELP);

	वापस ret;
पूर्ण
