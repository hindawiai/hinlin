<शैली गुरु>
// SPDX-License-Identअगरier: (GPL-2.0-only OR BSD-2-Clause)
/* Copyright (C) 2015-2018 Netronome Systems, Inc. */

#समावेश <linux/bitfield.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/skbuff.h>
#समावेश <linux/workqueue.h>
#समावेश <net/dst_metadata.h>

#समावेश "main.h"
#समावेश "../nfp_net.h"
#समावेश "../nfp_net_repr.h"
#समावेश "./cmsg.h"

अटल काष्ठा nfp_flower_cmsg_hdr *
nfp_flower_cmsg_get_hdr(काष्ठा sk_buff *skb)
अणु
	वापस (काष्ठा nfp_flower_cmsg_hdr *)skb->data;
पूर्ण

काष्ठा sk_buff *
nfp_flower_cmsg_alloc(काष्ठा nfp_app *app, अचिन्हित पूर्णांक size,
		      क्रमागत nfp_flower_cmsg_type_port type, gfp_t flag)
अणु
	काष्ठा nfp_flower_cmsg_hdr *ch;
	काष्ठा sk_buff *skb;

	size += NFP_FLOWER_CMSG_HLEN;

	skb = nfp_app_ctrl_msg_alloc(app, size, flag);
	अगर (!skb)
		वापस शून्य;

	ch = nfp_flower_cmsg_get_hdr(skb);
	ch->pad = 0;
	ch->version = NFP_FLOWER_CMSG_VER1;
	ch->type = type;
	skb_put(skb, size);

	वापस skb;
पूर्ण

काष्ठा sk_buff *
nfp_flower_cmsg_mac_repr_start(काष्ठा nfp_app *app, अचिन्हित पूर्णांक num_ports)
अणु
	काष्ठा nfp_flower_cmsg_mac_repr *msg;
	काष्ठा sk_buff *skb;

	skb = nfp_flower_cmsg_alloc(app, काष्ठा_size(msg, ports, num_ports),
				    NFP_FLOWER_CMSG_TYPE_MAC_REPR, GFP_KERNEL);
	अगर (!skb)
		वापस शून्य;

	msg = nfp_flower_cmsg_get_data(skb);
	स_रखो(msg->reserved, 0, माप(msg->reserved));
	msg->num_ports = num_ports;

	वापस skb;
पूर्ण

व्योम
nfp_flower_cmsg_mac_repr_add(काष्ठा sk_buff *skb, अचिन्हित पूर्णांक idx,
			     अचिन्हित पूर्णांक nbi, अचिन्हित पूर्णांक nbi_port,
			     अचिन्हित पूर्णांक phys_port)
अणु
	काष्ठा nfp_flower_cmsg_mac_repr *msg;

	msg = nfp_flower_cmsg_get_data(skb);
	msg->ports[idx].idx = idx;
	msg->ports[idx].info = nbi & NFP_FLOWER_CMSG_MAC_REPR_NBI;
	msg->ports[idx].nbi_port = nbi_port;
	msg->ports[idx].phys_port = phys_port;
पूर्ण

पूर्णांक nfp_flower_cmsg_porपंचांगod(काष्ठा nfp_repr *repr, bool carrier_ok,
			    अचिन्हित पूर्णांक mtu, bool mtu_only)
अणु
	काष्ठा nfp_flower_cmsg_porपंचांगod *msg;
	काष्ठा sk_buff *skb;

	skb = nfp_flower_cmsg_alloc(repr->app, माप(*msg),
				    NFP_FLOWER_CMSG_TYPE_PORT_MOD, GFP_KERNEL);
	अगर (!skb)
		वापस -ENOMEM;

	msg = nfp_flower_cmsg_get_data(skb);
	msg->portnum = cpu_to_be32(repr->dst->u.port_info.port_id);
	msg->reserved = 0;
	msg->info = carrier_ok;

	अगर (mtu_only)
		msg->info |= NFP_FLOWER_CMSG_PORTMOD_MTU_CHANGE_ONLY;

	msg->mtu = cpu_to_be16(mtu);

	nfp_ctrl_tx(repr->app->ctrl, skb);

	वापस 0;
पूर्ण

पूर्णांक nfp_flower_cmsg_portreअगरy(काष्ठा nfp_repr *repr, bool exists)
अणु
	काष्ठा nfp_flower_cmsg_portreअगरy *msg;
	काष्ठा sk_buff *skb;

	skb = nfp_flower_cmsg_alloc(repr->app, माप(*msg),
				    NFP_FLOWER_CMSG_TYPE_PORT_REIFY,
				    GFP_KERNEL);
	अगर (!skb)
		वापस -ENOMEM;

	msg = nfp_flower_cmsg_get_data(skb);
	msg->portnum = cpu_to_be32(repr->dst->u.port_info.port_id);
	msg->reserved = 0;
	msg->info = cpu_to_be16(exists);

	nfp_ctrl_tx(repr->app->ctrl, skb);

	वापस 0;
पूर्ण

अटल bool
nfp_flower_process_mtu_ack(काष्ठा nfp_app *app, काष्ठा sk_buff *skb)
अणु
	काष्ठा nfp_flower_priv *app_priv = app->priv;
	काष्ठा nfp_flower_cmsg_porपंचांगod *msg;

	msg = nfp_flower_cmsg_get_data(skb);

	अगर (!(msg->info & NFP_FLOWER_CMSG_PORTMOD_MTU_CHANGE_ONLY))
		वापस false;

	spin_lock_bh(&app_priv->mtu_conf.lock);
	अगर (!app_priv->mtu_conf.requested_val ||
	    app_priv->mtu_conf.portnum != be32_to_cpu(msg->portnum) ||
	    be16_to_cpu(msg->mtu) != app_priv->mtu_conf.requested_val) अणु
		/* Not an ack क्रम requested MTU change. */
		spin_unlock_bh(&app_priv->mtu_conf.lock);
		वापस false;
	पूर्ण

	app_priv->mtu_conf.ack = true;
	app_priv->mtu_conf.requested_val = 0;
	wake_up(&app_priv->mtu_conf.रुको_q);
	spin_unlock_bh(&app_priv->mtu_conf.lock);

	वापस true;
पूर्ण

अटल व्योम
nfp_flower_cmsg_porपंचांगod_rx(काष्ठा nfp_app *app, काष्ठा sk_buff *skb)
अणु
	काष्ठा nfp_flower_cmsg_porपंचांगod *msg;
	काष्ठा net_device *netdev;
	bool link;

	msg = nfp_flower_cmsg_get_data(skb);
	link = msg->info & NFP_FLOWER_CMSG_PORTMOD_INFO_LINK;

	rtnl_lock();
	rcu_पढ़ो_lock();
	netdev = nfp_app_dev_get(app, be32_to_cpu(msg->portnum), शून्य);
	rcu_पढ़ो_unlock();
	अगर (!netdev) अणु
		nfp_flower_cmsg_warn(app, "ctrl msg for unknown port 0x%08x\n",
				     be32_to_cpu(msg->portnum));
		rtnl_unlock();
		वापस;
	पूर्ण

	अगर (link) अणु
		u16 mtu = be16_to_cpu(msg->mtu);

		netअगर_carrier_on(netdev);

		/* An MTU of 0 from the firmware should be ignored */
		अगर (mtu)
			dev_set_mtu(netdev, mtu);
	पूर्ण अन्यथा अणु
		netअगर_carrier_off(netdev);
	पूर्ण
	rtnl_unlock();
पूर्ण

अटल व्योम
nfp_flower_cmsg_portreअगरy_rx(काष्ठा nfp_app *app, काष्ठा sk_buff *skb)
अणु
	काष्ठा nfp_flower_priv *priv = app->priv;
	काष्ठा nfp_flower_cmsg_portreअगरy *msg;
	bool exists;

	msg = nfp_flower_cmsg_get_data(skb);

	rcu_पढ़ो_lock();
	exists = !!nfp_app_dev_get(app, be32_to_cpu(msg->portnum), शून्य);
	rcu_पढ़ो_unlock();
	अगर (!exists) अणु
		nfp_flower_cmsg_warn(app, "ctrl msg for unknown port 0x%08x\n",
				     be32_to_cpu(msg->portnum));
		वापस;
	पूर्ण

	atomic_inc(&priv->reअगरy_replies);
	wake_up(&priv->reअगरy_रुको_queue);
पूर्ण

अटल व्योम
nfp_flower_cmsg_merge_hपूर्णांक_rx(काष्ठा nfp_app *app, काष्ठा sk_buff *skb)
अणु
	अचिन्हित पूर्णांक msg_len = nfp_flower_cmsg_get_data_len(skb);
	काष्ठा nfp_flower_cmsg_merge_hपूर्णांक *msg;
	काष्ठा nfp_fl_payload *sub_flows[2];
	पूर्णांक err, i, flow_cnt;

	msg = nfp_flower_cmsg_get_data(skb);
	/* msg->count starts at 0 and always assumes at least 1 entry. */
	flow_cnt = msg->count + 1;

	अगर (msg_len < काष्ठा_size(msg, flow, flow_cnt)) अणु
		nfp_flower_cmsg_warn(app, "Merge hint ctrl msg too short - %d bytes but expect %zd\n",
				     msg_len, काष्ठा_size(msg, flow, flow_cnt));
		वापस;
	पूर्ण

	अगर (flow_cnt != 2) अणु
		nfp_flower_cmsg_warn(app, "Merge hint contains %d flows - two are expected\n",
				     flow_cnt);
		वापस;
	पूर्ण

	rtnl_lock();
	क्रम (i = 0; i < flow_cnt; i++) अणु
		u32 ctx = be32_to_cpu(msg->flow[i].host_ctx);

		sub_flows[i] = nfp_flower_get_fl_payload_from_ctx(app, ctx);
		अगर (!sub_flows[i]) अणु
			nfp_flower_cmsg_warn(app, "Invalid flow in merge hint\n");
			जाओ err_rtnl_unlock;
		पूर्ण
	पूर्ण

	err = nfp_flower_merge_offloaded_flows(app, sub_flows[0], sub_flows[1]);
	/* Only warn on memory fail. Hपूर्णांक veto will not अवरोध functionality. */
	अगर (err == -ENOMEM)
		nfp_flower_cmsg_warn(app, "Flow merge memory fail.\n");

err_rtnl_unlock:
	rtnl_unlock();
पूर्ण

अटल व्योम
nfp_flower_cmsg_process_one_rx(काष्ठा nfp_app *app, काष्ठा sk_buff *skb)
अणु
	काष्ठा nfp_flower_priv *app_priv = app->priv;
	काष्ठा nfp_flower_cmsg_hdr *cmsg_hdr;
	क्रमागत nfp_flower_cmsg_type_port type;
	bool skb_stored = false;

	cmsg_hdr = nfp_flower_cmsg_get_hdr(skb);

	type = cmsg_hdr->type;
	चयन (type) अणु
	हाल NFP_FLOWER_CMSG_TYPE_PORT_MOD:
		nfp_flower_cmsg_porपंचांगod_rx(app, skb);
		अवरोध;
	हाल NFP_FLOWER_CMSG_TYPE_MERGE_HINT:
		अगर (app_priv->flower_en_feats & NFP_FL_ENABLE_FLOW_MERGE) अणु
			nfp_flower_cmsg_merge_hपूर्णांक_rx(app, skb);
			अवरोध;
		पूर्ण
		जाओ err_शेष;
	हाल NFP_FLOWER_CMSG_TYPE_NO_NEIGH:
		nfp_tunnel_request_route_v4(app, skb);
		अवरोध;
	हाल NFP_FLOWER_CMSG_TYPE_NO_NEIGH_V6:
		nfp_tunnel_request_route_v6(app, skb);
		अवरोध;
	हाल NFP_FLOWER_CMSG_TYPE_ACTIVE_TUNS:
		nfp_tunnel_keep_alive(app, skb);
		अवरोध;
	हाल NFP_FLOWER_CMSG_TYPE_ACTIVE_TUNS_V6:
		nfp_tunnel_keep_alive_v6(app, skb);
		अवरोध;
	हाल NFP_FLOWER_CMSG_TYPE_QOS_STATS:
		nfp_flower_stats_rlim_reply(app, skb);
		अवरोध;
	हाल NFP_FLOWER_CMSG_TYPE_LAG_CONFIG:
		अगर (app_priv->flower_en_feats & NFP_FL_ENABLE_LAG) अणु
			skb_stored = nfp_flower_lag_unprocessed_msg(app, skb);
			अवरोध;
		पूर्ण
		fallthrough;
	शेष:
err_शेष:
		nfp_flower_cmsg_warn(app, "Cannot handle invalid repr control type %u\n",
				     type);
		जाओ out;
	पूर्ण

	अगर (!skb_stored)
		dev_consume_skb_any(skb);
	वापस;
out:
	dev_kमुक्त_skb_any(skb);
पूर्ण

व्योम nfp_flower_cmsg_process_rx(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा sk_buff_head cmsg_joined;
	काष्ठा nfp_flower_priv *priv;
	काष्ठा sk_buff *skb;

	priv = container_of(work, काष्ठा nfp_flower_priv, cmsg_work);
	skb_queue_head_init(&cmsg_joined);

	spin_lock_bh(&priv->cmsg_skbs_high.lock);
	skb_queue_splice_tail_init(&priv->cmsg_skbs_high, &cmsg_joined);
	spin_unlock_bh(&priv->cmsg_skbs_high.lock);

	spin_lock_bh(&priv->cmsg_skbs_low.lock);
	skb_queue_splice_tail_init(&priv->cmsg_skbs_low, &cmsg_joined);
	spin_unlock_bh(&priv->cmsg_skbs_low.lock);

	जबतक ((skb = __skb_dequeue(&cmsg_joined)))
		nfp_flower_cmsg_process_one_rx(priv->app, skb);
पूर्ण

अटल व्योम
nfp_flower_queue_ctl_msg(काष्ठा nfp_app *app, काष्ठा sk_buff *skb, पूर्णांक type)
अणु
	काष्ठा nfp_flower_priv *priv = app->priv;
	काष्ठा sk_buff_head *skb_head;

	अगर (type == NFP_FLOWER_CMSG_TYPE_PORT_MOD)
		skb_head = &priv->cmsg_skbs_high;
	अन्यथा
		skb_head = &priv->cmsg_skbs_low;

	अगर (skb_queue_len(skb_head) >= NFP_FLOWER_WORKQ_MAX_SKBS) अणु
		nfp_flower_cmsg_warn(app, "Dropping queued control messages\n");
		dev_kमुक्त_skb_any(skb);
		वापस;
	पूर्ण

	skb_queue_tail(skb_head, skb);
	schedule_work(&priv->cmsg_work);
पूर्ण

व्योम nfp_flower_cmsg_rx(काष्ठा nfp_app *app, काष्ठा sk_buff *skb)
अणु
	काष्ठा nfp_flower_cmsg_hdr *cmsg_hdr;

	cmsg_hdr = nfp_flower_cmsg_get_hdr(skb);

	अगर (unlikely(cmsg_hdr->version != NFP_FLOWER_CMSG_VER1)) अणु
		nfp_flower_cmsg_warn(app, "Cannot handle repr control version %u\n",
				     cmsg_hdr->version);
		dev_kमुक्त_skb_any(skb);
		वापस;
	पूर्ण

	अगर (cmsg_hdr->type == NFP_FLOWER_CMSG_TYPE_FLOW_STATS) अणु
		/* We need to deal with stats updates from HW asap */
		nfp_flower_rx_flow_stats(app, skb);
		dev_consume_skb_any(skb);
	पूर्ण अन्यथा अगर (cmsg_hdr->type == NFP_FLOWER_CMSG_TYPE_PORT_MOD &&
		   nfp_flower_process_mtu_ack(app, skb)) अणु
		/* Handle MTU acks outside wq to prevent RTNL conflict. */
		dev_consume_skb_any(skb);
	पूर्ण अन्यथा अगर (cmsg_hdr->type == NFP_FLOWER_CMSG_TYPE_TUN_NEIGH ||
		   cmsg_hdr->type == NFP_FLOWER_CMSG_TYPE_TUN_NEIGH_V6) अणु
		/* Acks from the NFP that the route is added - ignore. */
		dev_consume_skb_any(skb);
	पूर्ण अन्यथा अगर (cmsg_hdr->type == NFP_FLOWER_CMSG_TYPE_PORT_REIFY) अणु
		/* Handle REIFY acks outside wq to prevent RTNL conflict. */
		nfp_flower_cmsg_portreअगरy_rx(app, skb);
		dev_consume_skb_any(skb);
	पूर्ण अन्यथा अणु
		nfp_flower_queue_ctl_msg(app, skb, cmsg_hdr->type);
	पूर्ण
पूर्ण
