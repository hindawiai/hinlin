<शैली गुरु>
// SPDX-License-Identअगरier: (GPL-2.0-only OR BSD-2-Clause)
/* Copyright (C) 2019 Netronome Systems, Inc. */

#समावेश <linux/math64.h>
#समावेश <net/pkt_cls.h>
#समावेश <net/pkt_sched.h>

#समावेश "cmsg.h"
#समावेश "main.h"
#समावेश "../nfp_port.h"

#घोषणा NFP_FL_QOS_UPDATE		msecs_to_jअगरfies(1000)
#घोषणा NFP_FL_QOS_PPS  BIT(15)

काष्ठा nfp_police_cfg_head अणु
	__be32 flags_opts;
	__be32 port;
पूर्ण;

क्रमागत NFP_FL_QOS_TYPES अणु
	NFP_FL_QOS_TYPE_BPS,
	NFP_FL_QOS_TYPE_PPS,
	NFP_FL_QOS_TYPE_MAX,
पूर्ण;

/* Police cmsg क्रम configuring a trTCM traffic conditioner (8W/32B)
 * See RFC 2698 क्रम more details.
 * ----------------------------------------------------------------
 *    3                   2                   1
 *  1 0 9 8 7 6 5 4 3 2 1 0 9 8 7 6 5 4 3 2 1 0 9 8 7 6 5 4 3 2 1 0
 * +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 * |             Reserved          |p|         Reserved            |
 * +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 * |                          Port Ingress                         |
 * +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 * |                        Token Bucket Peak                      |
 * +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 * |                     Token Bucket Committed                    |
 * +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 * |                         Peak Burst Size                       |
 * +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 * |                      Committed Burst Size                     |
 * +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 * |                      Peak Inक्रमmation Rate                    |
 * +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 * |                    Committed Inक्रमmation Rate                 |
 * +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 * Word[0](FLag options):
 * [15] p(pps) 1 क्रम pps ,0 क्रम bps
 *
 */
काष्ठा nfp_police_config अणु
	काष्ठा nfp_police_cfg_head head;
	__be32 bkt_tkn_p;
	__be32 bkt_tkn_c;
	__be32 pbs;
	__be32 cbs;
	__be32 pir;
	__be32 cir;
पूर्ण;

काष्ठा nfp_police_stats_reply अणु
	काष्ठा nfp_police_cfg_head head;
	__be64 pass_bytes;
	__be64 pass_pkts;
	__be64 drop_bytes;
	__be64 drop_pkts;
पूर्ण;

अटल पूर्णांक
nfp_flower_install_rate_limiter(काष्ठा nfp_app *app, काष्ठा net_device *netdev,
				काष्ठा tc_cls_matchall_offload *flow,
				काष्ठा netlink_ext_ack *extack)
अणु
	काष्ठा flow_action_entry *paction = &flow->rule->action.entries[0];
	u32 action_num = flow->rule->action.num_entries;
	काष्ठा nfp_flower_priv *fl_priv = app->priv;
	काष्ठा flow_action_entry *action = शून्य;
	काष्ठा nfp_flower_repr_priv *repr_priv;
	काष्ठा nfp_police_config *config;
	u32 netdev_port_id, i;
	काष्ठा nfp_repr *repr;
	काष्ठा sk_buff *skb;
	bool pps_support;
	u32 bps_num = 0;
	u32 pps_num = 0;
	u32 burst;
	u64 rate;

	अगर (!nfp_netdev_is_nfp_repr(netdev)) अणु
		NL_SET_ERR_MSG_MOD(extack, "unsupported offload: qos rate limit offload not supported on higher level port");
		वापस -EOPNOTSUPP;
	पूर्ण
	repr = netdev_priv(netdev);
	repr_priv = repr->app_priv;
	netdev_port_id = nfp_repr_get_port_id(netdev);
	pps_support = !!(fl_priv->flower_ext_feats & NFP_FL_FEATS_QOS_PPS);

	अगर (repr_priv->block_shared) अणु
		NL_SET_ERR_MSG_MOD(extack, "unsupported offload: qos rate limit offload not supported on shared blocks");
		वापस -EOPNOTSUPP;
	पूर्ण

	अगर (repr->port->type != NFP_PORT_VF_PORT) अणु
		NL_SET_ERR_MSG_MOD(extack, "unsupported offload: qos rate limit offload not supported on non-VF ports");
		वापस -EOPNOTSUPP;
	पूर्ण

	अगर (pps_support) अणु
		अगर (action_num > 2 || action_num == 0) अणु
			NL_SET_ERR_MSG_MOD(extack,
					   "unsupported offload: qos rate limit offload only support action number 1 or 2");
			वापस -EOPNOTSUPP;
		पूर्ण
	पूर्ण अन्यथा अणु
		अगर (!flow_offload_has_one_action(&flow->rule->action)) अणु
			NL_SET_ERR_MSG_MOD(extack,
					   "unsupported offload: qos rate limit offload requires a single action");
			वापस -EOPNOTSUPP;
		पूर्ण
	पूर्ण

	अगर (flow->common.prio != 1) अणु
		NL_SET_ERR_MSG_MOD(extack, "unsupported offload: qos rate limit offload requires highest priority");
		वापस -EOPNOTSUPP;
	पूर्ण

	क्रम (i = 0 ; i < action_num; i++) अणु
		action = paction + i;
		अगर (action->id != FLOW_ACTION_POLICE) अणु
			NL_SET_ERR_MSG_MOD(extack,
					   "unsupported offload: qos rate limit offload requires police action");
			वापस -EOPNOTSUPP;
		पूर्ण
		अगर (action->police.rate_bytes_ps > 0) अणु
			अगर (bps_num++) अणु
				NL_SET_ERR_MSG_MOD(extack,
						   "unsupported offload: qos rate limit offload only support one BPS action");
				वापस -EOPNOTSUPP;
			पूर्ण
		पूर्ण
		अगर (action->police.rate_pkt_ps > 0) अणु
			अगर (!pps_support) अणु
				NL_SET_ERR_MSG_MOD(extack,
						   "unsupported offload: FW does not support PPS action");
				वापस -EOPNOTSUPP;
			पूर्ण
			अगर (pps_num++) अणु
				NL_SET_ERR_MSG_MOD(extack,
						   "unsupported offload: qos rate limit offload only support one PPS action");
				वापस -EOPNOTSUPP;
			पूर्ण
		पूर्ण
	पूर्ण

	क्रम (i = 0 ; i < action_num; i++) अणु
		/* Set QoS data क्रम this पूर्णांकerface */
		action = paction + i;
		अगर (action->police.rate_bytes_ps > 0) अणु
			rate = action->police.rate_bytes_ps;
			burst = action->police.burst;
		पूर्ण अन्यथा अगर (action->police.rate_pkt_ps > 0) अणु
			rate = action->police.rate_pkt_ps;
			burst = action->police.burst_pkt;
		पूर्ण अन्यथा अणु
			NL_SET_ERR_MSG_MOD(extack,
					   "unsupported offload: qos rate limit is not BPS or PPS");
			जारी;
		पूर्ण

		अगर (rate != 0) अणु
			skb = nfp_flower_cmsg_alloc(repr->app, माप(काष्ठा nfp_police_config),
						    NFP_FLOWER_CMSG_TYPE_QOS_MOD, GFP_KERNEL);
			अगर (!skb)
				वापस -ENOMEM;

			config = nfp_flower_cmsg_get_data(skb);
			स_रखो(config, 0, माप(काष्ठा nfp_police_config));
			अगर (action->police.rate_pkt_ps > 0)
				config->head.flags_opts = cpu_to_be32(NFP_FL_QOS_PPS);
			config->head.port = cpu_to_be32(netdev_port_id);
			config->bkt_tkn_p = cpu_to_be32(burst);
			config->bkt_tkn_c = cpu_to_be32(burst);
			config->pbs = cpu_to_be32(burst);
			config->cbs = cpu_to_be32(burst);
			config->pir = cpu_to_be32(rate);
			config->cir = cpu_to_be32(rate);
			nfp_ctrl_tx(repr->app->ctrl, skb);
		पूर्ण
	पूर्ण
	repr_priv->qos_table.netdev_port_id = netdev_port_id;
	fl_priv->qos_rate_limiters++;
	अगर (fl_priv->qos_rate_limiters == 1)
		schedule_delayed_work(&fl_priv->qos_stats_work,
				      NFP_FL_QOS_UPDATE);

	वापस 0;
पूर्ण

अटल पूर्णांक
nfp_flower_हटाओ_rate_limiter(काष्ठा nfp_app *app, काष्ठा net_device *netdev,
			       काष्ठा tc_cls_matchall_offload *flow,
			       काष्ठा netlink_ext_ack *extack)
अणु
	काष्ठा nfp_flower_priv *fl_priv = app->priv;
	काष्ठा nfp_flower_repr_priv *repr_priv;
	काष्ठा nfp_police_config *config;
	u32 netdev_port_id, i;
	काष्ठा nfp_repr *repr;
	काष्ठा sk_buff *skb;
	bool pps_support;

	अगर (!nfp_netdev_is_nfp_repr(netdev)) अणु
		NL_SET_ERR_MSG_MOD(extack, "unsupported offload: qos rate limit offload not supported on higher level port");
		वापस -EOPNOTSUPP;
	पूर्ण
	repr = netdev_priv(netdev);

	netdev_port_id = nfp_repr_get_port_id(netdev);
	repr_priv = repr->app_priv;
	pps_support = !!(fl_priv->flower_ext_feats & NFP_FL_FEATS_QOS_PPS);

	अगर (!repr_priv->qos_table.netdev_port_id) अणु
		NL_SET_ERR_MSG_MOD(extack, "unsupported offload: cannot remove qos entry that does not exist");
		वापस -EOPNOTSUPP;
	पूर्ण

	स_रखो(&repr_priv->qos_table, 0, माप(काष्ठा nfp_fl_qos));
	fl_priv->qos_rate_limiters--;
	अगर (!fl_priv->qos_rate_limiters)
		cancel_delayed_work_sync(&fl_priv->qos_stats_work);
	क्रम (i = 0 ; i < NFP_FL_QOS_TYPE_MAX; i++) अणु
		अगर (i == NFP_FL_QOS_TYPE_PPS && !pps_support)
			अवरोध;
		/* 0:bps 1:pps
		 * Clear QoS data क्रम this पूर्णांकerface.
		 * There is no need to check अगर a specअगरic QOS_TYPE was
		 * configured as the firmware handles clearing a QoS entry
		 * safely, even अगर it wasn't explicitly added.
		 */
		skb = nfp_flower_cmsg_alloc(repr->app, माप(काष्ठा nfp_police_config),
					    NFP_FLOWER_CMSG_TYPE_QOS_DEL, GFP_KERNEL);
		अगर (!skb)
			वापस -ENOMEM;

		config = nfp_flower_cmsg_get_data(skb);
		स_रखो(config, 0, माप(काष्ठा nfp_police_config));
		अगर (i == NFP_FL_QOS_TYPE_PPS)
			config->head.flags_opts = cpu_to_be32(NFP_FL_QOS_PPS);
		config->head.port = cpu_to_be32(netdev_port_id);
		nfp_ctrl_tx(repr->app->ctrl, skb);
	पूर्ण

	वापस 0;
पूर्ण

व्योम nfp_flower_stats_rlim_reply(काष्ठा nfp_app *app, काष्ठा sk_buff *skb)
अणु
	काष्ठा nfp_flower_priv *fl_priv = app->priv;
	काष्ठा nfp_flower_repr_priv *repr_priv;
	काष्ठा nfp_police_stats_reply *msg;
	काष्ठा nfp_stat_pair *curr_stats;
	काष्ठा nfp_stat_pair *prev_stats;
	काष्ठा net_device *netdev;
	काष्ठा nfp_repr *repr;
	u32 netdev_port_id;

	msg = nfp_flower_cmsg_get_data(skb);
	netdev_port_id = be32_to_cpu(msg->head.port);
	rcu_पढ़ो_lock();
	netdev = nfp_app_dev_get(app, netdev_port_id, शून्य);
	अगर (!netdev)
		जाओ निकास_unlock_rcu;

	repr = netdev_priv(netdev);
	repr_priv = repr->app_priv;
	curr_stats = &repr_priv->qos_table.curr_stats;
	prev_stats = &repr_priv->qos_table.prev_stats;

	spin_lock_bh(&fl_priv->qos_stats_lock);
	curr_stats->pkts = be64_to_cpu(msg->pass_pkts) +
			   be64_to_cpu(msg->drop_pkts);
	curr_stats->bytes = be64_to_cpu(msg->pass_bytes) +
			    be64_to_cpu(msg->drop_bytes);

	अगर (!repr_priv->qos_table.last_update) अणु
		prev_stats->pkts = curr_stats->pkts;
		prev_stats->bytes = curr_stats->bytes;
	पूर्ण

	repr_priv->qos_table.last_update = jअगरfies;
	spin_unlock_bh(&fl_priv->qos_stats_lock);

निकास_unlock_rcu:
	rcu_पढ़ो_unlock();
पूर्ण

अटल व्योम
nfp_flower_stats_rlim_request(काष्ठा nfp_flower_priv *fl_priv,
			      u32 netdev_port_id)
अणु
	काष्ठा nfp_police_cfg_head *head;
	काष्ठा sk_buff *skb;

	skb = nfp_flower_cmsg_alloc(fl_priv->app,
				    माप(काष्ठा nfp_police_cfg_head),
				    NFP_FLOWER_CMSG_TYPE_QOS_STATS,
				    GFP_ATOMIC);
	अगर (!skb)
		वापस;

	head = nfp_flower_cmsg_get_data(skb);
	स_रखो(head, 0, माप(काष्ठा nfp_police_cfg_head));
	head->port = cpu_to_be32(netdev_port_id);

	nfp_ctrl_tx(fl_priv->app->ctrl, skb);
पूर्ण

अटल व्योम
nfp_flower_stats_rlim_request_all(काष्ठा nfp_flower_priv *fl_priv)
अणु
	काष्ठा nfp_reprs *repr_set;
	पूर्णांक i;

	rcu_पढ़ो_lock();
	repr_set = rcu_dereference(fl_priv->app->reprs[NFP_REPR_TYPE_VF]);
	अगर (!repr_set)
		जाओ निकास_unlock_rcu;

	क्रम (i = 0; i < repr_set->num_reprs; i++) अणु
		काष्ठा net_device *netdev;

		netdev = rcu_dereference(repr_set->reprs[i]);
		अगर (netdev) अणु
			काष्ठा nfp_repr *priv = netdev_priv(netdev);
			काष्ठा nfp_flower_repr_priv *repr_priv;
			u32 netdev_port_id;

			repr_priv = priv->app_priv;
			netdev_port_id = repr_priv->qos_table.netdev_port_id;
			अगर (!netdev_port_id)
				जारी;

			nfp_flower_stats_rlim_request(fl_priv, netdev_port_id);
		पूर्ण
	पूर्ण

निकास_unlock_rcu:
	rcu_पढ़ो_unlock();
पूर्ण

अटल व्योम update_stats_cache(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा delayed_work *delayed_work;
	काष्ठा nfp_flower_priv *fl_priv;

	delayed_work = to_delayed_work(work);
	fl_priv = container_of(delayed_work, काष्ठा nfp_flower_priv,
			       qos_stats_work);

	nfp_flower_stats_rlim_request_all(fl_priv);
	schedule_delayed_work(&fl_priv->qos_stats_work, NFP_FL_QOS_UPDATE);
पूर्ण

अटल पूर्णांक
nfp_flower_stats_rate_limiter(काष्ठा nfp_app *app, काष्ठा net_device *netdev,
			      काष्ठा tc_cls_matchall_offload *flow,
			      काष्ठा netlink_ext_ack *extack)
अणु
	काष्ठा nfp_flower_priv *fl_priv = app->priv;
	काष्ठा nfp_flower_repr_priv *repr_priv;
	काष्ठा nfp_stat_pair *curr_stats;
	काष्ठा nfp_stat_pair *prev_stats;
	u64 dअगरf_bytes, dअगरf_pkts;
	काष्ठा nfp_repr *repr;

	अगर (!nfp_netdev_is_nfp_repr(netdev)) अणु
		NL_SET_ERR_MSG_MOD(extack, "unsupported offload: qos rate limit offload not supported on higher level port");
		वापस -EOPNOTSUPP;
	पूर्ण
	repr = netdev_priv(netdev);

	repr_priv = repr->app_priv;
	अगर (!repr_priv->qos_table.netdev_port_id) अणु
		NL_SET_ERR_MSG_MOD(extack, "unsupported offload: cannot find qos entry for stats update");
		वापस -EOPNOTSUPP;
	पूर्ण

	spin_lock_bh(&fl_priv->qos_stats_lock);
	curr_stats = &repr_priv->qos_table.curr_stats;
	prev_stats = &repr_priv->qos_table.prev_stats;
	dअगरf_pkts = curr_stats->pkts - prev_stats->pkts;
	dअगरf_bytes = curr_stats->bytes - prev_stats->bytes;
	prev_stats->pkts = curr_stats->pkts;
	prev_stats->bytes = curr_stats->bytes;
	spin_unlock_bh(&fl_priv->qos_stats_lock);

	flow_stats_update(&flow->stats, dअगरf_bytes, dअगरf_pkts, 0,
			  repr_priv->qos_table.last_update,
			  FLOW_ACTION_HW_STATS_DELAYED);
	वापस 0;
पूर्ण

व्योम nfp_flower_qos_init(काष्ठा nfp_app *app)
अणु
	काष्ठा nfp_flower_priv *fl_priv = app->priv;

	spin_lock_init(&fl_priv->qos_stats_lock);
	INIT_DELAYED_WORK(&fl_priv->qos_stats_work, &update_stats_cache);
पूर्ण

व्योम nfp_flower_qos_cleanup(काष्ठा nfp_app *app)
अणु
	काष्ठा nfp_flower_priv *fl_priv = app->priv;

	cancel_delayed_work_sync(&fl_priv->qos_stats_work);
पूर्ण

पूर्णांक nfp_flower_setup_qos_offload(काष्ठा nfp_app *app, काष्ठा net_device *netdev,
				 काष्ठा tc_cls_matchall_offload *flow)
अणु
	काष्ठा netlink_ext_ack *extack = flow->common.extack;
	काष्ठा nfp_flower_priv *fl_priv = app->priv;

	अगर (!(fl_priv->flower_ext_feats & NFP_FL_FEATS_VF_RLIM)) अणु
		NL_SET_ERR_MSG_MOD(extack, "unsupported offload: loaded firmware does not support qos rate limit offload");
		वापस -EOPNOTSUPP;
	पूर्ण

	चयन (flow->command) अणु
	हाल TC_CLSMATCHALL_REPLACE:
		वापस nfp_flower_install_rate_limiter(app, netdev, flow,
						       extack);
	हाल TC_CLSMATCHALL_DESTROY:
		वापस nfp_flower_हटाओ_rate_limiter(app, netdev, flow,
						      extack);
	हाल TC_CLSMATCHALL_STATS:
		वापस nfp_flower_stats_rate_limiter(app, netdev, flow,
						     extack);
	शेष:
		वापस -EOPNOTSUPP;
	पूर्ण
पूर्ण
