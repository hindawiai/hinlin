<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/* Copyright (C) 2019 Chelsio Communications.  All rights reserved. */

#समावेश "cxgb4.h"
#समावेश "cxgb4_tc_matchall.h"
#समावेश "sched.h"
#समावेश "cxgb4_uld.h"
#समावेश "cxgb4_filter.h"
#समावेश "cxgb4_tc_flower.h"

अटल पूर्णांक cxgb4_matchall_egress_validate(काष्ठा net_device *dev,
					  काष्ठा tc_cls_matchall_offload *cls)
अणु
	काष्ठा netlink_ext_ack *extack = cls->common.extack;
	काष्ठा flow_action *actions = &cls->rule->action;
	काष्ठा port_info *pi = netdev2pinfo(dev);
	काष्ठा flow_action_entry *entry;
	काष्ठा ch_sched_queue qe;
	काष्ठा sched_class *e;
	u64 max_link_rate;
	u32 i, speed;
	पूर्णांक ret;

	अगर (!flow_action_has_entries(actions)) अणु
		NL_SET_ERR_MSG_MOD(extack,
				   "Egress MATCHALL offload needs at least 1 policing action");
		वापस -EINVAL;
	पूर्ण अन्यथा अगर (!flow_offload_has_one_action(actions)) अणु
		NL_SET_ERR_MSG_MOD(extack,
				   "Egress MATCHALL offload only supports 1 policing action");
		वापस -EINVAL;
	पूर्ण अन्यथा अगर (pi->tc_block_shared) अणु
		NL_SET_ERR_MSG_MOD(extack,
				   "Egress MATCHALL offload not supported with shared blocks");
		वापस -EINVAL;
	पूर्ण

	ret = t4_get_link_params(pi, शून्य, &speed, शून्य);
	अगर (ret) अणु
		NL_SET_ERR_MSG_MOD(extack,
				   "Failed to get max speed supported by the link");
		वापस -EINVAL;
	पूर्ण

	/* Convert from Mbps to bps */
	max_link_rate = (u64)speed * 1000 * 1000;

	flow_action_क्रम_each(i, entry, actions) अणु
		चयन (entry->id) अणु
		हाल FLOW_ACTION_POLICE:
			अगर (entry->police.rate_pkt_ps) अणु
				NL_SET_ERR_MSG_MOD(extack,
						   "QoS offload not support packets per second");
				वापस -EOPNOTSUPP;
			पूर्ण
			/* Convert bytes per second to bits per second */
			अगर (entry->police.rate_bytes_ps * 8 > max_link_rate) अणु
				NL_SET_ERR_MSG_MOD(extack,
						   "Specified policing max rate is larger than underlying link speed");
				वापस -दुस्फल;
			पूर्ण
			अवरोध;
		शेष:
			NL_SET_ERR_MSG_MOD(extack,
					   "Only policing action supported with Egress MATCHALL offload");
			वापस -EOPNOTSUPP;
		पूर्ण
	पूर्ण

	क्रम (i = 0; i < pi->nqsets; i++) अणु
		स_रखो(&qe, 0, माप(qe));
		qe.queue = i;

		e = cxgb4_sched_queue_lookup(dev, &qe);
		अगर (e && e->info.u.params.level != SCHED_CLASS_LEVEL_CH_RL) अणु
			NL_SET_ERR_MSG_MOD(extack,
					   "Some queues are already bound to different class");
			वापस -EBUSY;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक cxgb4_matchall_tc_bind_queues(काष्ठा net_device *dev, u32 tc)
अणु
	काष्ठा port_info *pi = netdev2pinfo(dev);
	काष्ठा ch_sched_queue qe;
	पूर्णांक ret;
	u32 i;

	क्रम (i = 0; i < pi->nqsets; i++) अणु
		qe.queue = i;
		qe.class = tc;
		ret = cxgb4_sched_class_bind(dev, &qe, SCHED_QUEUE);
		अगर (ret)
			जाओ out_मुक्त;
	पूर्ण

	वापस 0;

out_मुक्त:
	जबतक (i--) अणु
		qe.queue = i;
		qe.class = SCHED_CLS_NONE;
		cxgb4_sched_class_unbind(dev, &qe, SCHED_QUEUE);
	पूर्ण

	वापस ret;
पूर्ण

अटल व्योम cxgb4_matchall_tc_unbind_queues(काष्ठा net_device *dev)
अणु
	काष्ठा port_info *pi = netdev2pinfo(dev);
	काष्ठा ch_sched_queue qe;
	u32 i;

	क्रम (i = 0; i < pi->nqsets; i++) अणु
		qe.queue = i;
		qe.class = SCHED_CLS_NONE;
		cxgb4_sched_class_unbind(dev, &qe, SCHED_QUEUE);
	पूर्ण
पूर्ण

अटल पूर्णांक cxgb4_matchall_alloc_tc(काष्ठा net_device *dev,
				   काष्ठा tc_cls_matchall_offload *cls)
अणु
	काष्ठा ch_sched_params p = अणु
		.type = SCHED_CLASS_TYPE_PACKET,
		.u.params.level = SCHED_CLASS_LEVEL_CH_RL,
		.u.params.mode = SCHED_CLASS_MODE_CLASS,
		.u.params.rateunit = SCHED_CLASS_RATEUNIT_BITS,
		.u.params.ratemode = SCHED_CLASS_RATEMODE_ABS,
		.u.params.class = SCHED_CLS_NONE,
		.u.params.minrate = 0,
		.u.params.weight = 0,
		.u.params.pktsize = dev->mtu,
	पूर्ण;
	काष्ठा netlink_ext_ack *extack = cls->common.extack;
	काष्ठा cxgb4_tc_port_matchall *tc_port_matchall;
	काष्ठा port_info *pi = netdev2pinfo(dev);
	काष्ठा adapter *adap = netdev2adap(dev);
	काष्ठा flow_action_entry *entry;
	काष्ठा sched_class *e;
	पूर्णांक ret;
	u32 i;

	tc_port_matchall = &adap->tc_matchall->port_matchall[pi->port_id];

	flow_action_क्रम_each(i, entry, &cls->rule->action)
		अगर (entry->id == FLOW_ACTION_POLICE)
			अवरोध;
	अगर (entry->police.rate_pkt_ps) अणु
		NL_SET_ERR_MSG_MOD(extack,
				   "QoS offload not support packets per second");
		वापस -EOPNOTSUPP;
	पूर्ण
	/* Convert from bytes per second to Kbps */
	p.u.params.maxrate = भाग_u64(entry->police.rate_bytes_ps * 8, 1000);
	p.u.params.channel = pi->tx_chan;
	e = cxgb4_sched_class_alloc(dev, &p);
	अगर (!e) अणु
		NL_SET_ERR_MSG_MOD(extack,
				   "No free traffic class available for policing action");
		वापस -ENOMEM;
	पूर्ण

	ret = cxgb4_matchall_tc_bind_queues(dev, e->idx);
	अगर (ret) अणु
		NL_SET_ERR_MSG_MOD(extack,
				   "Could not bind queues to traffic class");
		जाओ out_मुक्त;
	पूर्ण

	tc_port_matchall->egress.hwtc = e->idx;
	tc_port_matchall->egress.cookie = cls->cookie;
	tc_port_matchall->egress.state = CXGB4_MATCHALL_STATE_ENABLED;
	वापस 0;

out_मुक्त:
	cxgb4_sched_class_मुक्त(dev, e->idx);
	वापस ret;
पूर्ण

अटल व्योम cxgb4_matchall_मुक्त_tc(काष्ठा net_device *dev)
अणु
	काष्ठा cxgb4_tc_port_matchall *tc_port_matchall;
	काष्ठा port_info *pi = netdev2pinfo(dev);
	काष्ठा adapter *adap = netdev2adap(dev);

	tc_port_matchall = &adap->tc_matchall->port_matchall[pi->port_id];
	cxgb4_matchall_tc_unbind_queues(dev);
	cxgb4_sched_class_मुक्त(dev, tc_port_matchall->egress.hwtc);

	tc_port_matchall->egress.hwtc = SCHED_CLS_NONE;
	tc_port_matchall->egress.cookie = 0;
	tc_port_matchall->egress.state = CXGB4_MATCHALL_STATE_DISABLED;
पूर्ण

अटल पूर्णांक cxgb4_matchall_mirror_alloc(काष्ठा net_device *dev,
				       काष्ठा tc_cls_matchall_offload *cls)
अणु
	काष्ठा netlink_ext_ack *extack = cls->common.extack;
	काष्ठा cxgb4_tc_port_matchall *tc_port_matchall;
	काष्ठा port_info *pi = netdev2pinfo(dev);
	काष्ठा adapter *adap = netdev2adap(dev);
	काष्ठा flow_action_entry *act;
	पूर्णांक ret;
	u32 i;

	tc_port_matchall = &adap->tc_matchall->port_matchall[pi->port_id];
	flow_action_क्रम_each(i, act, &cls->rule->action) अणु
		अगर (act->id == FLOW_ACTION_MIRRED) अणु
			ret = cxgb4_port_mirror_alloc(dev);
			अगर (ret) अणु
				NL_SET_ERR_MSG_MOD(extack,
						   "Couldn't allocate mirror");
				वापस ret;
			पूर्ण

			tc_port_matchall->ingress.viid_mirror = pi->viid_mirror;
			अवरोध;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम cxgb4_matchall_mirror_मुक्त(काष्ठा net_device *dev)
अणु
	काष्ठा cxgb4_tc_port_matchall *tc_port_matchall;
	काष्ठा port_info *pi = netdev2pinfo(dev);
	काष्ठा adapter *adap = netdev2adap(dev);

	tc_port_matchall = &adap->tc_matchall->port_matchall[pi->port_id];
	अगर (!tc_port_matchall->ingress.viid_mirror)
		वापस;

	cxgb4_port_mirror_मुक्त(dev);
	tc_port_matchall->ingress.viid_mirror = 0;
पूर्ण

अटल पूर्णांक cxgb4_matchall_del_filter(काष्ठा net_device *dev, u8 filter_type)
अणु
	काष्ठा cxgb4_tc_port_matchall *tc_port_matchall;
	काष्ठा port_info *pi = netdev2pinfo(dev);
	काष्ठा adapter *adap = netdev2adap(dev);
	पूर्णांक ret;

	tc_port_matchall = &adap->tc_matchall->port_matchall[pi->port_id];
	ret = cxgb4_del_filter(dev, tc_port_matchall->ingress.tid[filter_type],
			       &tc_port_matchall->ingress.fs[filter_type]);
	अगर (ret)
		वापस ret;

	tc_port_matchall->ingress.tid[filter_type] = 0;
	वापस 0;
पूर्ण

अटल पूर्णांक cxgb4_matchall_add_filter(काष्ठा net_device *dev,
				     काष्ठा tc_cls_matchall_offload *cls,
				     u8 filter_type)
अणु
	काष्ठा netlink_ext_ack *extack = cls->common.extack;
	काष्ठा cxgb4_tc_port_matchall *tc_port_matchall;
	काष्ठा port_info *pi = netdev2pinfo(dev);
	काष्ठा adapter *adap = netdev2adap(dev);
	काष्ठा ch_filter_specअगरication *fs;
	पूर्णांक ret, fidx;

	/* Get a मुक्त filter entry TID, where we can insert this new
	 * rule. Only insert rule अगर its prio करोesn't conflict with
	 * existing rules.
	 */
	fidx = cxgb4_get_मुक्त_ftid(dev, filter_type ? PF_INET6 : PF_INET,
				   false, cls->common.prio);
	अगर (fidx < 0) अणु
		NL_SET_ERR_MSG_MOD(extack,
				   "No free LETCAM index available");
		वापस -ENOMEM;
	पूर्ण

	tc_port_matchall = &adap->tc_matchall->port_matchall[pi->port_id];
	fs = &tc_port_matchall->ingress.fs[filter_type];
	स_रखो(fs, 0, माप(*fs));

	अगर (fidx < adap->tids.nhpftids)
		fs->prio = 1;
	fs->tc_prio = cls->common.prio;
	fs->tc_cookie = cls->cookie;
	fs->type = filter_type;
	fs->hitcnts = 1;

	fs->val.pfvf_vld = 1;
	fs->val.pf = adap->pf;
	fs->val.vf = pi->vin;

	cxgb4_process_flow_actions(dev, &cls->rule->action, fs);

	ret = cxgb4_set_filter(dev, fidx, fs);
	अगर (ret)
		वापस ret;

	tc_port_matchall->ingress.tid[filter_type] = fidx;
	वापस 0;
पूर्ण

अटल पूर्णांक cxgb4_matchall_alloc_filter(काष्ठा net_device *dev,
				       काष्ठा tc_cls_matchall_offload *cls)
अणु
	काष्ठा cxgb4_tc_port_matchall *tc_port_matchall;
	काष्ठा port_info *pi = netdev2pinfo(dev);
	काष्ठा adapter *adap = netdev2adap(dev);
	पूर्णांक ret, i;

	tc_port_matchall = &adap->tc_matchall->port_matchall[pi->port_id];

	ret = cxgb4_matchall_mirror_alloc(dev, cls);
	अगर (ret)
		वापस ret;

	क्रम (i = 0; i < CXGB4_FILTER_TYPE_MAX; i++) अणु
		ret = cxgb4_matchall_add_filter(dev, cls, i);
		अगर (ret)
			जाओ out_मुक्त;
	पूर्ण

	tc_port_matchall->ingress.state = CXGB4_MATCHALL_STATE_ENABLED;
	वापस 0;

out_मुक्त:
	जबतक (i-- > 0)
		cxgb4_matchall_del_filter(dev, i);

	cxgb4_matchall_mirror_मुक्त(dev);
	वापस ret;
पूर्ण

अटल पूर्णांक cxgb4_matchall_मुक्त_filter(काष्ठा net_device *dev)
अणु
	काष्ठा cxgb4_tc_port_matchall *tc_port_matchall;
	काष्ठा port_info *pi = netdev2pinfo(dev);
	काष्ठा adapter *adap = netdev2adap(dev);
	पूर्णांक ret;
	u8 i;

	tc_port_matchall = &adap->tc_matchall->port_matchall[pi->port_id];

	क्रम (i = 0; i < CXGB4_FILTER_TYPE_MAX; i++) अणु
		ret = cxgb4_matchall_del_filter(dev, i);
		अगर (ret)
			वापस ret;
	पूर्ण

	cxgb4_matchall_mirror_मुक्त(dev);

	tc_port_matchall->ingress.packets = 0;
	tc_port_matchall->ingress.bytes = 0;
	tc_port_matchall->ingress.last_used = 0;
	tc_port_matchall->ingress.state = CXGB4_MATCHALL_STATE_DISABLED;
	वापस 0;
पूर्ण

पूर्णांक cxgb4_tc_matchall_replace(काष्ठा net_device *dev,
			      काष्ठा tc_cls_matchall_offload *cls_matchall,
			      bool ingress)
अणु
	काष्ठा netlink_ext_ack *extack = cls_matchall->common.extack;
	काष्ठा cxgb4_tc_port_matchall *tc_port_matchall;
	काष्ठा port_info *pi = netdev2pinfo(dev);
	काष्ठा adapter *adap = netdev2adap(dev);
	पूर्णांक ret;

	tc_port_matchall = &adap->tc_matchall->port_matchall[pi->port_id];
	अगर (ingress) अणु
		अगर (tc_port_matchall->ingress.state ==
		    CXGB4_MATCHALL_STATE_ENABLED) अणु
			NL_SET_ERR_MSG_MOD(extack,
					   "Only 1 Ingress MATCHALL can be offloaded");
			वापस -ENOMEM;
		पूर्ण

		ret = cxgb4_validate_flow_actions(dev,
						  &cls_matchall->rule->action,
						  extack, 1);
		अगर (ret)
			वापस ret;

		वापस cxgb4_matchall_alloc_filter(dev, cls_matchall);
	पूर्ण

	अगर (tc_port_matchall->egress.state == CXGB4_MATCHALL_STATE_ENABLED) अणु
		NL_SET_ERR_MSG_MOD(extack,
				   "Only 1 Egress MATCHALL can be offloaded");
		वापस -ENOMEM;
	पूर्ण

	ret = cxgb4_matchall_egress_validate(dev, cls_matchall);
	अगर (ret)
		वापस ret;

	वापस cxgb4_matchall_alloc_tc(dev, cls_matchall);
पूर्ण

पूर्णांक cxgb4_tc_matchall_destroy(काष्ठा net_device *dev,
			      काष्ठा tc_cls_matchall_offload *cls_matchall,
			      bool ingress)
अणु
	काष्ठा cxgb4_tc_port_matchall *tc_port_matchall;
	काष्ठा port_info *pi = netdev2pinfo(dev);
	काष्ठा adapter *adap = netdev2adap(dev);

	tc_port_matchall = &adap->tc_matchall->port_matchall[pi->port_id];
	अगर (ingress) अणु
		/* All the filter types of this matchall rule save the
		 * same cookie. So, checking क्रम the first one is
		 * enough.
		 */
		अगर (cls_matchall->cookie !=
		    tc_port_matchall->ingress.fs[0].tc_cookie)
			वापस -ENOENT;

		वापस cxgb4_matchall_मुक्त_filter(dev);
	पूर्ण

	अगर (cls_matchall->cookie != tc_port_matchall->egress.cookie)
		वापस -ENOENT;

	cxgb4_matchall_मुक्त_tc(dev);
	वापस 0;
पूर्ण

पूर्णांक cxgb4_tc_matchall_stats(काष्ठा net_device *dev,
			    काष्ठा tc_cls_matchall_offload *cls_matchall)
अणु
	u64 पंचांगp_packets, पंचांगp_bytes, packets = 0, bytes = 0;
	काष्ठा cxgb4_tc_port_matchall *tc_port_matchall;
	काष्ठा cxgb4_matchall_ingress_entry *ingress;
	काष्ठा port_info *pi = netdev2pinfo(dev);
	काष्ठा adapter *adap = netdev2adap(dev);
	पूर्णांक ret;
	u8 i;

	tc_port_matchall = &adap->tc_matchall->port_matchall[pi->port_id];
	अगर (tc_port_matchall->ingress.state == CXGB4_MATCHALL_STATE_DISABLED)
		वापस -ENOENT;

	ingress = &tc_port_matchall->ingress;
	क्रम (i = 0; i < CXGB4_FILTER_TYPE_MAX; i++) अणु
		ret = cxgb4_get_filter_counters(dev, ingress->tid[i],
						&पंचांगp_packets, &पंचांगp_bytes,
						ingress->fs[i].hash);
		अगर (ret)
			वापस ret;

		packets += पंचांगp_packets;
		bytes += पंचांगp_bytes;
	पूर्ण

	अगर (tc_port_matchall->ingress.packets != packets) अणु
		flow_stats_update(&cls_matchall->stats,
				  bytes - tc_port_matchall->ingress.bytes,
				  packets - tc_port_matchall->ingress.packets,
				  0, tc_port_matchall->ingress.last_used,
				  FLOW_ACTION_HW_STATS_IMMEDIATE);

		tc_port_matchall->ingress.packets = packets;
		tc_port_matchall->ingress.bytes = bytes;
		tc_port_matchall->ingress.last_used = jअगरfies;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम cxgb4_matchall_disable_offload(काष्ठा net_device *dev)
अणु
	काष्ठा cxgb4_tc_port_matchall *tc_port_matchall;
	काष्ठा port_info *pi = netdev2pinfo(dev);
	काष्ठा adapter *adap = netdev2adap(dev);

	tc_port_matchall = &adap->tc_matchall->port_matchall[pi->port_id];
	अगर (tc_port_matchall->egress.state == CXGB4_MATCHALL_STATE_ENABLED)
		cxgb4_matchall_मुक्त_tc(dev);

	अगर (tc_port_matchall->ingress.state == CXGB4_MATCHALL_STATE_ENABLED)
		cxgb4_matchall_मुक्त_filter(dev);
पूर्ण

पूर्णांक cxgb4_init_tc_matchall(काष्ठा adapter *adap)
अणु
	काष्ठा cxgb4_tc_port_matchall *tc_port_matchall;
	काष्ठा cxgb4_tc_matchall *tc_matchall;
	पूर्णांक ret;

	tc_matchall = kzalloc(माप(*tc_matchall), GFP_KERNEL);
	अगर (!tc_matchall)
		वापस -ENOMEM;

	tc_port_matchall = kसुस्मृति(adap->params.nports,
				   माप(*tc_port_matchall),
				   GFP_KERNEL);
	अगर (!tc_port_matchall) अणु
		ret = -ENOMEM;
		जाओ out_मुक्त_matchall;
	पूर्ण

	tc_matchall->port_matchall = tc_port_matchall;
	adap->tc_matchall = tc_matchall;
	वापस 0;

out_मुक्त_matchall:
	kमुक्त(tc_matchall);
	वापस ret;
पूर्ण

व्योम cxgb4_cleanup_tc_matchall(काष्ठा adapter *adap)
अणु
	u8 i;

	अगर (adap->tc_matchall) अणु
		अगर (adap->tc_matchall->port_matchall) अणु
			क्रम (i = 0; i < adap->params.nports; i++) अणु
				काष्ठा net_device *dev = adap->port[i];

				अगर (dev)
					cxgb4_matchall_disable_offload(dev);
			पूर्ण
			kमुक्त(adap->tc_matchall->port_matchall);
		पूर्ण
		kमुक्त(adap->tc_matchall);
	पूर्ण
पूर्ण
