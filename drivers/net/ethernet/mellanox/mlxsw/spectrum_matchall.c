<शैली गुरु>
// SPDX-License-Identअगरier: BSD-3-Clause OR GPL-2.0
/* Copyright (c) 2017-2020 Mellanox Technologies. All rights reserved */

#समावेश <linux/kernel.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/netdevice.h>
#समावेश <net/flow_offload.h>

#समावेश "spectrum.h"
#समावेश "spectrum_span.h"
#समावेश "reg.h"

अटल काष्ठा mlxsw_sp_mall_entry *
mlxsw_sp_mall_entry_find(काष्ठा mlxsw_sp_flow_block *block, अचिन्हित दीर्घ cookie)
अणु
	काष्ठा mlxsw_sp_mall_entry *mall_entry;

	list_क्रम_each_entry(mall_entry, &block->mall.list, list)
		अगर (mall_entry->cookie == cookie)
			वापस mall_entry;

	वापस शून्य;
पूर्ण

अटल पूर्णांक
mlxsw_sp_mall_port_mirror_add(काष्ठा mlxsw_sp_port *mlxsw_sp_port,
			      काष्ठा mlxsw_sp_mall_entry *mall_entry,
			      काष्ठा netlink_ext_ack *extack)
अणु
	काष्ठा mlxsw_sp *mlxsw_sp = mlxsw_sp_port->mlxsw_sp;
	काष्ठा mlxsw_sp_span_agent_parms agent_parms = अणुपूर्ण;
	काष्ठा mlxsw_sp_span_trigger_parms parms;
	क्रमागत mlxsw_sp_span_trigger trigger;
	पूर्णांक err;

	अगर (!mall_entry->mirror.to_dev) अणु
		NL_SET_ERR_MSG(extack, "Could not find requested device");
		वापस -EINVAL;
	पूर्ण

	agent_parms.to_dev = mall_entry->mirror.to_dev;
	err = mlxsw_sp_span_agent_get(mlxsw_sp, &mall_entry->mirror.span_id,
				      &agent_parms);
	अगर (err) अणु
		NL_SET_ERR_MSG(extack, "Failed to get SPAN agent");
		वापस err;
	पूर्ण

	err = mlxsw_sp_span_analyzed_port_get(mlxsw_sp_port,
					      mall_entry->ingress);
	अगर (err) अणु
		NL_SET_ERR_MSG(extack, "Failed to get analyzed port");
		जाओ err_analyzed_port_get;
	पूर्ण

	trigger = mall_entry->ingress ? MLXSW_SP_SPAN_TRIGGER_INGRESS :
					MLXSW_SP_SPAN_TRIGGER_EGRESS;
	parms.span_id = mall_entry->mirror.span_id;
	parms.probability_rate = 1;
	err = mlxsw_sp_span_agent_bind(mlxsw_sp, trigger, mlxsw_sp_port,
				       &parms);
	अगर (err) अणु
		NL_SET_ERR_MSG(extack, "Failed to bind SPAN agent");
		जाओ err_agent_bind;
	पूर्ण

	वापस 0;

err_agent_bind:
	mlxsw_sp_span_analyzed_port_put(mlxsw_sp_port, mall_entry->ingress);
err_analyzed_port_get:
	mlxsw_sp_span_agent_put(mlxsw_sp, mall_entry->mirror.span_id);
	वापस err;
पूर्ण

अटल व्योम
mlxsw_sp_mall_port_mirror_del(काष्ठा mlxsw_sp_port *mlxsw_sp_port,
			      काष्ठा mlxsw_sp_mall_entry *mall_entry)
अणु
	काष्ठा mlxsw_sp *mlxsw_sp = mlxsw_sp_port->mlxsw_sp;
	काष्ठा mlxsw_sp_span_trigger_parms parms;
	क्रमागत mlxsw_sp_span_trigger trigger;

	trigger = mall_entry->ingress ? MLXSW_SP_SPAN_TRIGGER_INGRESS :
					MLXSW_SP_SPAN_TRIGGER_EGRESS;
	parms.span_id = mall_entry->mirror.span_id;
	mlxsw_sp_span_agent_unbind(mlxsw_sp, trigger, mlxsw_sp_port, &parms);
	mlxsw_sp_span_analyzed_port_put(mlxsw_sp_port, mall_entry->ingress);
	mlxsw_sp_span_agent_put(mlxsw_sp, mall_entry->mirror.span_id);
पूर्ण

अटल पूर्णांक mlxsw_sp_mall_port_sample_set(काष्ठा mlxsw_sp_port *mlxsw_sp_port,
					 bool enable, u32 rate)
अणु
	काष्ठा mlxsw_sp *mlxsw_sp = mlxsw_sp_port->mlxsw_sp;
	अक्षर mpsc_pl[MLXSW_REG_MPSC_LEN];

	mlxsw_reg_mpsc_pack(mpsc_pl, mlxsw_sp_port->local_port, enable, rate);
	वापस mlxsw_reg_ग_लिखो(mlxsw_sp->core, MLXSW_REG(mpsc), mpsc_pl);
पूर्ण

अटल पूर्णांक
mlxsw_sp_mall_port_sample_add(काष्ठा mlxsw_sp_port *mlxsw_sp_port,
			      काष्ठा mlxsw_sp_mall_entry *mall_entry,
			      काष्ठा netlink_ext_ack *extack)
अणु
	काष्ठा mlxsw_sp *mlxsw_sp = mlxsw_sp_port->mlxsw_sp;
	काष्ठा mlxsw_sp_sample_trigger trigger;
	पूर्णांक err;

	अगर (mall_entry->ingress)
		trigger.type = MLXSW_SP_SAMPLE_TRIGGER_TYPE_INGRESS;
	अन्यथा
		trigger.type = MLXSW_SP_SAMPLE_TRIGGER_TYPE_EGRESS;
	trigger.local_port = mlxsw_sp_port->local_port;
	err = mlxsw_sp_sample_trigger_params_set(mlxsw_sp, &trigger,
						 &mall_entry->sample.params,
						 extack);
	अगर (err)
		वापस err;

	err = mlxsw_sp->mall_ops->sample_add(mlxsw_sp, mlxsw_sp_port,
					     mall_entry, extack);
	अगर (err)
		जाओ err_port_sample_set;
	वापस 0;

err_port_sample_set:
	mlxsw_sp_sample_trigger_params_unset(mlxsw_sp, &trigger);
	वापस err;
पूर्ण

अटल व्योम
mlxsw_sp_mall_port_sample_del(काष्ठा mlxsw_sp_port *mlxsw_sp_port,
			      काष्ठा mlxsw_sp_mall_entry *mall_entry)
अणु
	काष्ठा mlxsw_sp *mlxsw_sp = mlxsw_sp_port->mlxsw_sp;
	काष्ठा mlxsw_sp_sample_trigger trigger;

	अगर (mall_entry->ingress)
		trigger.type = MLXSW_SP_SAMPLE_TRIGGER_TYPE_INGRESS;
	अन्यथा
		trigger.type = MLXSW_SP_SAMPLE_TRIGGER_TYPE_EGRESS;
	trigger.local_port = mlxsw_sp_port->local_port;

	mlxsw_sp->mall_ops->sample_del(mlxsw_sp, mlxsw_sp_port, mall_entry);
	mlxsw_sp_sample_trigger_params_unset(mlxsw_sp, &trigger);
पूर्ण

अटल पूर्णांक
mlxsw_sp_mall_port_rule_add(काष्ठा mlxsw_sp_port *mlxsw_sp_port,
			    काष्ठा mlxsw_sp_mall_entry *mall_entry,
			    काष्ठा netlink_ext_ack *extack)
अणु
	चयन (mall_entry->type) अणु
	हाल MLXSW_SP_MALL_ACTION_TYPE_MIRROR:
		वापस mlxsw_sp_mall_port_mirror_add(mlxsw_sp_port, mall_entry,
						     extack);
	हाल MLXSW_SP_MALL_ACTION_TYPE_SAMPLE:
		वापस mlxsw_sp_mall_port_sample_add(mlxsw_sp_port, mall_entry,
						     extack);
	शेष:
		WARN_ON(1);
		वापस -EINVAL;
	पूर्ण
पूर्ण

अटल व्योम
mlxsw_sp_mall_port_rule_del(काष्ठा mlxsw_sp_port *mlxsw_sp_port,
			    काष्ठा mlxsw_sp_mall_entry *mall_entry)
अणु
	चयन (mall_entry->type) अणु
	हाल MLXSW_SP_MALL_ACTION_TYPE_MIRROR:
		mlxsw_sp_mall_port_mirror_del(mlxsw_sp_port, mall_entry);
		अवरोध;
	हाल MLXSW_SP_MALL_ACTION_TYPE_SAMPLE:
		mlxsw_sp_mall_port_sample_del(mlxsw_sp_port, mall_entry);
		अवरोध;
	शेष:
		WARN_ON(1);
	पूर्ण
पूर्ण

अटल व्योम mlxsw_sp_mall_prio_update(काष्ठा mlxsw_sp_flow_block *block)
अणु
	काष्ठा mlxsw_sp_mall_entry *mall_entry;

	अगर (list_empty(&block->mall.list))
		वापस;
	block->mall.min_prio = अच_पूर्णांक_उच्च;
	block->mall.max_prio = 0;
	list_क्रम_each_entry(mall_entry, &block->mall.list, list) अणु
		अगर (mall_entry->priority < block->mall.min_prio)
			block->mall.min_prio = mall_entry->priority;
		अगर (mall_entry->priority > block->mall.max_prio)
			block->mall.max_prio = mall_entry->priority;
	पूर्ण
पूर्ण

पूर्णांक mlxsw_sp_mall_replace(काष्ठा mlxsw_sp *mlxsw_sp,
			  काष्ठा mlxsw_sp_flow_block *block,
			  काष्ठा tc_cls_matchall_offload *f)
अणु
	काष्ठा mlxsw_sp_flow_block_binding *binding;
	काष्ठा mlxsw_sp_mall_entry *mall_entry;
	__be16 protocol = f->common.protocol;
	काष्ठा flow_action_entry *act;
	अचिन्हित पूर्णांक flower_min_prio;
	अचिन्हित पूर्णांक flower_max_prio;
	bool flower_prio_valid;
	पूर्णांक err;

	अगर (!flow_offload_has_one_action(&f->rule->action)) अणु
		NL_SET_ERR_MSG(f->common.extack, "Only singular actions are supported");
		वापस -EOPNOTSUPP;
	पूर्ण

	अगर (f->common.chain_index) अणु
		NL_SET_ERR_MSG(f->common.extack, "Only chain 0 is supported");
		वापस -EOPNOTSUPP;
	पूर्ण

	अगर (mlxsw_sp_flow_block_is_mixed_bound(block)) अणु
		NL_SET_ERR_MSG(f->common.extack, "Only not mixed bound blocks are supported");
		वापस -EOPNOTSUPP;
	पूर्ण

	err = mlxsw_sp_flower_prio_get(mlxsw_sp, block, f->common.chain_index,
				       &flower_min_prio, &flower_max_prio);
	अगर (err) अणु
		अगर (err != -ENOENT) अणु
			NL_SET_ERR_MSG(f->common.extack, "Failed to get flower priorities");
			वापस err;
		पूर्ण
		flower_prio_valid = false;
		/* No flower filters are installed in specअगरied chain. */
	पूर्ण अन्यथा अणु
		flower_prio_valid = true;
	पूर्ण

	अगर (protocol != htons(ETH_P_ALL)) अणु
		NL_SET_ERR_MSG(f->common.extack, "matchall rules only supported with 'all' protocol");
		वापस -EOPNOTSUPP;
	पूर्ण

	mall_entry = kzalloc(माप(*mall_entry), GFP_KERNEL);
	अगर (!mall_entry)
		वापस -ENOMEM;
	mall_entry->cookie = f->cookie;
	mall_entry->priority = f->common.prio;
	mall_entry->ingress = mlxsw_sp_flow_block_is_ingress_bound(block);

	अगर (flower_prio_valid && mall_entry->ingress &&
	    mall_entry->priority >= flower_min_prio) अणु
		NL_SET_ERR_MSG(f->common.extack, "Failed to add behind existing flower rules");
		err = -EOPNOTSUPP;
		जाओ errout;
	पूर्ण
	अगर (flower_prio_valid && !mall_entry->ingress &&
	    mall_entry->priority <= flower_max_prio) अणु
		NL_SET_ERR_MSG(f->common.extack, "Failed to add in front of existing flower rules");
		err = -EOPNOTSUPP;
		जाओ errout;
	पूर्ण

	act = &f->rule->action.entries[0];

	चयन (act->id) अणु
	हाल FLOW_ACTION_MIRRED:
		mall_entry->type = MLXSW_SP_MALL_ACTION_TYPE_MIRROR;
		mall_entry->mirror.to_dev = act->dev;
		अवरोध;
	हाल FLOW_ACTION_SAMPLE:
		mall_entry->type = MLXSW_SP_MALL_ACTION_TYPE_SAMPLE;
		mall_entry->sample.params.psample_group = act->sample.psample_group;
		mall_entry->sample.params.truncate = act->sample.truncate;
		mall_entry->sample.params.trunc_size = act->sample.trunc_size;
		mall_entry->sample.params.rate = act->sample.rate;
		अवरोध;
	शेष:
		err = -EOPNOTSUPP;
		जाओ errout;
	पूर्ण

	list_क्रम_each_entry(binding, &block->binding_list, list) अणु
		err = mlxsw_sp_mall_port_rule_add(binding->mlxsw_sp_port,
						  mall_entry, f->common.extack);
		अगर (err)
			जाओ rollback;
	पूर्ण

	block->rule_count++;
	अगर (mall_entry->ingress)
		block->egress_blocker_rule_count++;
	अन्यथा
		block->ingress_blocker_rule_count++;
	list_add_tail(&mall_entry->list, &block->mall.list);
	mlxsw_sp_mall_prio_update(block);
	वापस 0;

rollback:
	list_क्रम_each_entry_जारी_reverse(binding, &block->binding_list,
					     list)
		mlxsw_sp_mall_port_rule_del(binding->mlxsw_sp_port, mall_entry);
errout:
	kमुक्त(mall_entry);
	वापस err;
पूर्ण

व्योम mlxsw_sp_mall_destroy(काष्ठा mlxsw_sp_flow_block *block,
			   काष्ठा tc_cls_matchall_offload *f)
अणु
	काष्ठा mlxsw_sp_flow_block_binding *binding;
	काष्ठा mlxsw_sp_mall_entry *mall_entry;

	mall_entry = mlxsw_sp_mall_entry_find(block, f->cookie);
	अगर (!mall_entry) अणु
		NL_SET_ERR_MSG(f->common.extack, "Entry not found");
		वापस;
	पूर्ण

	list_del(&mall_entry->list);
	अगर (mall_entry->ingress)
		block->egress_blocker_rule_count--;
	अन्यथा
		block->ingress_blocker_rule_count--;
	block->rule_count--;
	list_क्रम_each_entry(binding, &block->binding_list, list)
		mlxsw_sp_mall_port_rule_del(binding->mlxsw_sp_port, mall_entry);
	kमुक्त_rcu(mall_entry, rcu); /* sample RX packets may be in-flight */
	mlxsw_sp_mall_prio_update(block);
पूर्ण

पूर्णांक mlxsw_sp_mall_port_bind(काष्ठा mlxsw_sp_flow_block *block,
			    काष्ठा mlxsw_sp_port *mlxsw_sp_port,
			    काष्ठा netlink_ext_ack *extack)
अणु
	काष्ठा mlxsw_sp_mall_entry *mall_entry;
	पूर्णांक err;

	list_क्रम_each_entry(mall_entry, &block->mall.list, list) अणु
		err = mlxsw_sp_mall_port_rule_add(mlxsw_sp_port, mall_entry,
						  extack);
		अगर (err)
			जाओ rollback;
	पूर्ण
	वापस 0;

rollback:
	list_क्रम_each_entry_जारी_reverse(mall_entry, &block->mall.list,
					     list)
		mlxsw_sp_mall_port_rule_del(mlxsw_sp_port, mall_entry);
	वापस err;
पूर्ण

व्योम mlxsw_sp_mall_port_unbind(काष्ठा mlxsw_sp_flow_block *block,
			       काष्ठा mlxsw_sp_port *mlxsw_sp_port)
अणु
	काष्ठा mlxsw_sp_mall_entry *mall_entry;

	list_क्रम_each_entry(mall_entry, &block->mall.list, list)
		mlxsw_sp_mall_port_rule_del(mlxsw_sp_port, mall_entry);
पूर्ण

पूर्णांक mlxsw_sp_mall_prio_get(काष्ठा mlxsw_sp_flow_block *block, u32 chain_index,
			   अचिन्हित पूर्णांक *p_min_prio, अचिन्हित पूर्णांक *p_max_prio)
अणु
	अगर (chain_index || list_empty(&block->mall.list))
		/* In हाल there are no matchall rules, the caller
		 * receives -ENOENT to indicate there is no need
		 * to check the priorities.
		 */
		वापस -ENOENT;
	*p_min_prio = block->mall.min_prio;
	*p_max_prio = block->mall.max_prio;
	वापस 0;
पूर्ण

अटल पूर्णांक mlxsw_sp1_mall_sample_add(काष्ठा mlxsw_sp *mlxsw_sp,
				     काष्ठा mlxsw_sp_port *mlxsw_sp_port,
				     काष्ठा mlxsw_sp_mall_entry *mall_entry,
				     काष्ठा netlink_ext_ack *extack)
अणु
	u32 rate = mall_entry->sample.params.rate;

	अगर (!mall_entry->ingress) अणु
		NL_SET_ERR_MSG(extack, "Sampling is not supported on egress");
		वापस -EOPNOTSUPP;
	पूर्ण

	अगर (rate > MLXSW_REG_MPSC_RATE_MAX) अणु
		NL_SET_ERR_MSG(extack, "Unsupported sampling rate");
		वापस -EOPNOTSUPP;
	पूर्ण

	वापस mlxsw_sp_mall_port_sample_set(mlxsw_sp_port, true, rate);
पूर्ण

अटल व्योम mlxsw_sp1_mall_sample_del(काष्ठा mlxsw_sp *mlxsw_sp,
				      काष्ठा mlxsw_sp_port *mlxsw_sp_port,
				      काष्ठा mlxsw_sp_mall_entry *mall_entry)
अणु
	mlxsw_sp_mall_port_sample_set(mlxsw_sp_port, false, 1);
पूर्ण

स्थिर काष्ठा mlxsw_sp_mall_ops mlxsw_sp1_mall_ops = अणु
	.sample_add = mlxsw_sp1_mall_sample_add,
	.sample_del = mlxsw_sp1_mall_sample_del,
पूर्ण;

अटल पूर्णांक mlxsw_sp2_mall_sample_add(काष्ठा mlxsw_sp *mlxsw_sp,
				     काष्ठा mlxsw_sp_port *mlxsw_sp_port,
				     काष्ठा mlxsw_sp_mall_entry *mall_entry,
				     काष्ठा netlink_ext_ack *extack)
अणु
	काष्ठा mlxsw_sp_span_trigger_parms trigger_parms = अणुपूर्ण;
	काष्ठा mlxsw_sp_span_agent_parms agent_parms = अणु
		.to_dev = शून्य,	/* Mirror to CPU. */
		.session_id = MLXSW_SP_SPAN_SESSION_ID_SAMPLING,
	पूर्ण;
	u32 rate = mall_entry->sample.params.rate;
	क्रमागत mlxsw_sp_span_trigger span_trigger;
	पूर्णांक err;

	err = mlxsw_sp_span_agent_get(mlxsw_sp, &mall_entry->sample.span_id,
				      &agent_parms);
	अगर (err) अणु
		NL_SET_ERR_MSG(extack, "Failed to get SPAN agent");
		वापस err;
	पूर्ण

	err = mlxsw_sp_span_analyzed_port_get(mlxsw_sp_port,
					      mall_entry->ingress);
	अगर (err) अणु
		NL_SET_ERR_MSG(extack, "Failed to get analyzed port");
		जाओ err_analyzed_port_get;
	पूर्ण

	span_trigger = mall_entry->ingress ? MLXSW_SP_SPAN_TRIGGER_INGRESS :
					     MLXSW_SP_SPAN_TRIGGER_EGRESS;
	trigger_parms.span_id = mall_entry->sample.span_id;
	trigger_parms.probability_rate = rate;
	err = mlxsw_sp_span_agent_bind(mlxsw_sp, span_trigger, mlxsw_sp_port,
				       &trigger_parms);
	अगर (err) अणु
		NL_SET_ERR_MSG(extack, "Failed to bind SPAN agent");
		जाओ err_agent_bind;
	पूर्ण

	वापस 0;

err_agent_bind:
	mlxsw_sp_span_analyzed_port_put(mlxsw_sp_port, mall_entry->ingress);
err_analyzed_port_get:
	mlxsw_sp_span_agent_put(mlxsw_sp, mall_entry->sample.span_id);
	वापस err;
पूर्ण

अटल व्योम mlxsw_sp2_mall_sample_del(काष्ठा mlxsw_sp *mlxsw_sp,
				      काष्ठा mlxsw_sp_port *mlxsw_sp_port,
				      काष्ठा mlxsw_sp_mall_entry *mall_entry)
अणु
	काष्ठा mlxsw_sp_span_trigger_parms trigger_parms = अणुपूर्ण;
	क्रमागत mlxsw_sp_span_trigger span_trigger;

	span_trigger = mall_entry->ingress ? MLXSW_SP_SPAN_TRIGGER_INGRESS :
					     MLXSW_SP_SPAN_TRIGGER_EGRESS;
	trigger_parms.span_id = mall_entry->sample.span_id;
	mlxsw_sp_span_agent_unbind(mlxsw_sp, span_trigger, mlxsw_sp_port,
				   &trigger_parms);
	mlxsw_sp_span_analyzed_port_put(mlxsw_sp_port, mall_entry->ingress);
	mlxsw_sp_span_agent_put(mlxsw_sp, mall_entry->sample.span_id);
पूर्ण

स्थिर काष्ठा mlxsw_sp_mall_ops mlxsw_sp2_mall_ops = अणु
	.sample_add = mlxsw_sp2_mall_sample_add,
	.sample_del = mlxsw_sp2_mall_sample_del,
पूर्ण;
