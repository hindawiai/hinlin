<शैली गुरु>
// SPDX-License-Identअगरier: BSD-3-Clause OR GPL-2.0
/* Copyright (c) 2017-2018 Mellanox Technologies. All rights reserved */

#समावेश "spectrum_acl_flex_actions.h"
#समावेश "core_acl_flex_actions.h"
#समावेश "spectrum_span.h"

अटल पूर्णांक mlxsw_sp_act_kvdl_set_add(व्योम *priv, u32 *p_kvdl_index,
				     अक्षर *enc_actions, bool is_first, bool ca)
अणु
	काष्ठा mlxsw_sp *mlxsw_sp = priv;
	अक्षर pefa_pl[MLXSW_REG_PEFA_LEN];
	u32 kvdl_index;
	पूर्णांक err;

	/* The first action set of a TCAM entry is stored directly in TCAM,
	 * not KVD linear area.
	 */
	अगर (is_first)
		वापस 0;

	err = mlxsw_sp_kvdl_alloc(mlxsw_sp, MLXSW_SP_KVDL_ENTRY_TYPE_ACTSET,
				  1, &kvdl_index);
	अगर (err)
		वापस err;
	mlxsw_reg_pefa_pack(pefa_pl, kvdl_index, ca, enc_actions);
	err = mlxsw_reg_ग_लिखो(mlxsw_sp->core, MLXSW_REG(pefa), pefa_pl);
	अगर (err)
		जाओ err_pefa_ग_लिखो;
	*p_kvdl_index = kvdl_index;
	वापस 0;

err_pefa_ग_लिखो:
	mlxsw_sp_kvdl_मुक्त(mlxsw_sp, MLXSW_SP_KVDL_ENTRY_TYPE_ACTSET,
			   1, kvdl_index);
	वापस err;
पूर्ण

अटल पूर्णांक mlxsw_sp1_act_kvdl_set_add(व्योम *priv, u32 *p_kvdl_index,
				      अक्षर *enc_actions, bool is_first)
अणु
	वापस mlxsw_sp_act_kvdl_set_add(priv, p_kvdl_index, enc_actions,
					 is_first, false);
पूर्ण

अटल पूर्णांक mlxsw_sp2_act_kvdl_set_add(व्योम *priv, u32 *p_kvdl_index,
				      अक्षर *enc_actions, bool is_first)
अणु
	वापस mlxsw_sp_act_kvdl_set_add(priv, p_kvdl_index, enc_actions,
					 is_first, true);
पूर्ण

अटल व्योम mlxsw_sp_act_kvdl_set_del(व्योम *priv, u32 kvdl_index,
				      bool is_first)
अणु
	काष्ठा mlxsw_sp *mlxsw_sp = priv;

	अगर (is_first)
		वापस;
	mlxsw_sp_kvdl_मुक्त(mlxsw_sp, MLXSW_SP_KVDL_ENTRY_TYPE_ACTSET,
			   1, kvdl_index);
पूर्ण

अटल पूर्णांक mlxsw_sp1_act_kvdl_set_activity_get(व्योम *priv, u32 kvdl_index,
					       bool *activity)
अणु
	वापस -EOPNOTSUPP;
पूर्ण

अटल पूर्णांक mlxsw_sp2_act_kvdl_set_activity_get(व्योम *priv, u32 kvdl_index,
					       bool *activity)
अणु
	काष्ठा mlxsw_sp *mlxsw_sp = priv;
	अक्षर pefa_pl[MLXSW_REG_PEFA_LEN];
	पूर्णांक err;

	mlxsw_reg_pefa_pack(pefa_pl, kvdl_index, true, शून्य);
	err = mlxsw_reg_query(mlxsw_sp->core, MLXSW_REG(pefa), pefa_pl);
	अगर (err)
		वापस err;
	mlxsw_reg_pefa_unpack(pefa_pl, activity);
	वापस 0;
पूर्ण

अटल पूर्णांक mlxsw_sp_act_kvdl_fwd_entry_add(व्योम *priv, u32 *p_kvdl_index,
					   u8 local_port)
अणु
	काष्ठा mlxsw_sp *mlxsw_sp = priv;
	अक्षर ppbs_pl[MLXSW_REG_PPBS_LEN];
	u32 kvdl_index;
	पूर्णांक err;

	err = mlxsw_sp_kvdl_alloc(mlxsw_sp, MLXSW_SP_KVDL_ENTRY_TYPE_PBS,
				  1, &kvdl_index);
	अगर (err)
		वापस err;
	mlxsw_reg_ppbs_pack(ppbs_pl, kvdl_index, local_port);
	err = mlxsw_reg_ग_लिखो(mlxsw_sp->core, MLXSW_REG(ppbs), ppbs_pl);
	अगर (err)
		जाओ err_ppbs_ग_लिखो;
	*p_kvdl_index = kvdl_index;
	वापस 0;

err_ppbs_ग_लिखो:
	mlxsw_sp_kvdl_मुक्त(mlxsw_sp, MLXSW_SP_KVDL_ENTRY_TYPE_PBS,
			   1, kvdl_index);
	वापस err;
पूर्ण

अटल व्योम mlxsw_sp_act_kvdl_fwd_entry_del(व्योम *priv, u32 kvdl_index)
अणु
	काष्ठा mlxsw_sp *mlxsw_sp = priv;

	mlxsw_sp_kvdl_मुक्त(mlxsw_sp, MLXSW_SP_KVDL_ENTRY_TYPE_PBS,
			   1, kvdl_index);
पूर्ण

अटल पूर्णांक
mlxsw_sp_act_counter_index_get(व्योम *priv, अचिन्हित पूर्णांक *p_counter_index)
अणु
	काष्ठा mlxsw_sp *mlxsw_sp = priv;

	वापस mlxsw_sp_flow_counter_alloc(mlxsw_sp, p_counter_index);
पूर्ण

अटल व्योम
mlxsw_sp_act_counter_index_put(व्योम *priv, अचिन्हित पूर्णांक counter_index)
अणु
	काष्ठा mlxsw_sp *mlxsw_sp = priv;

	mlxsw_sp_flow_counter_मुक्त(mlxsw_sp, counter_index);
पूर्ण

अटल पूर्णांक
mlxsw_sp_act_mirror_add(व्योम *priv, u8 local_in_port,
			स्थिर काष्ठा net_device *out_dev,
			bool ingress, पूर्णांक *p_span_id)
अणु
	काष्ठा mlxsw_sp_span_agent_parms agent_parms = अणुपूर्ण;
	काष्ठा mlxsw_sp_port *mlxsw_sp_port;
	काष्ठा mlxsw_sp *mlxsw_sp = priv;
	पूर्णांक err;

	agent_parms.to_dev = out_dev;
	err = mlxsw_sp_span_agent_get(mlxsw_sp, p_span_id, &agent_parms);
	अगर (err)
		वापस err;

	mlxsw_sp_port = mlxsw_sp->ports[local_in_port];
	err = mlxsw_sp_span_analyzed_port_get(mlxsw_sp_port, ingress);
	अगर (err)
		जाओ err_analyzed_port_get;

	वापस 0;

err_analyzed_port_get:
	mlxsw_sp_span_agent_put(mlxsw_sp, *p_span_id);
	वापस err;
पूर्ण

अटल व्योम
mlxsw_sp_act_mirror_del(व्योम *priv, u8 local_in_port, पूर्णांक span_id, bool ingress)
अणु
	काष्ठा mlxsw_sp_port *mlxsw_sp_port;
	काष्ठा mlxsw_sp *mlxsw_sp = priv;

	mlxsw_sp_port = mlxsw_sp->ports[local_in_port];
	mlxsw_sp_span_analyzed_port_put(mlxsw_sp_port, ingress);
	mlxsw_sp_span_agent_put(mlxsw_sp, span_id);
पूर्ण

अटल पूर्णांक mlxsw_sp_act_policer_add(व्योम *priv, u64 rate_bytes_ps, u32 burst,
				    u16 *p_policer_index,
				    काष्ठा netlink_ext_ack *extack)
अणु
	काष्ठा mlxsw_sp_policer_params params;
	काष्ठा mlxsw_sp *mlxsw_sp = priv;

	params.rate = rate_bytes_ps;
	params.burst = burst;
	params.bytes = true;
	वापस mlxsw_sp_policer_add(mlxsw_sp,
				    MLXSW_SP_POLICER_TYPE_SINGLE_RATE,
				    &params, extack, p_policer_index);
पूर्ण

अटल व्योम mlxsw_sp_act_policer_del(व्योम *priv, u16 policer_index)
अणु
	काष्ठा mlxsw_sp *mlxsw_sp = priv;

	mlxsw_sp_policer_del(mlxsw_sp, MLXSW_SP_POLICER_TYPE_SINGLE_RATE,
			     policer_index);
पूर्ण

अटल पूर्णांक mlxsw_sp1_act_sampler_add(व्योम *priv, u8 local_port,
				     काष्ठा psample_group *psample_group,
				     u32 rate, u32 trunc_size, bool truncate,
				     bool ingress, पूर्णांक *p_span_id,
				     काष्ठा netlink_ext_ack *extack)
अणु
	NL_SET_ERR_MSG_MOD(extack, "Sampling action is not supported on Spectrum-1");
	वापस -EOPNOTSUPP;
पूर्ण

अटल व्योम mlxsw_sp1_act_sampler_del(व्योम *priv, u8 local_port, पूर्णांक span_id,
				      bool ingress)
अणु
	WARN_ON_ONCE(1);
पूर्ण

स्थिर काष्ठा mlxsw_afa_ops mlxsw_sp1_act_afa_ops = अणु
	.kvdl_set_add		= mlxsw_sp1_act_kvdl_set_add,
	.kvdl_set_del		= mlxsw_sp_act_kvdl_set_del,
	.kvdl_set_activity_get	= mlxsw_sp1_act_kvdl_set_activity_get,
	.kvdl_fwd_entry_add	= mlxsw_sp_act_kvdl_fwd_entry_add,
	.kvdl_fwd_entry_del	= mlxsw_sp_act_kvdl_fwd_entry_del,
	.counter_index_get	= mlxsw_sp_act_counter_index_get,
	.counter_index_put	= mlxsw_sp_act_counter_index_put,
	.mirror_add		= mlxsw_sp_act_mirror_add,
	.mirror_del		= mlxsw_sp_act_mirror_del,
	.policer_add		= mlxsw_sp_act_policer_add,
	.policer_del		= mlxsw_sp_act_policer_del,
	.sampler_add		= mlxsw_sp1_act_sampler_add,
	.sampler_del		= mlxsw_sp1_act_sampler_del,
पूर्ण;

अटल पूर्णांक mlxsw_sp2_act_sampler_add(व्योम *priv, u8 local_port,
				     काष्ठा psample_group *psample_group,
				     u32 rate, u32 trunc_size, bool truncate,
				     bool ingress, पूर्णांक *p_span_id,
				     काष्ठा netlink_ext_ack *extack)
अणु
	काष्ठा mlxsw_sp_span_agent_parms agent_parms = अणु
		.session_id = MLXSW_SP_SPAN_SESSION_ID_SAMPLING,
	पूर्ण;
	काष्ठा mlxsw_sp_sample_trigger trigger = अणु
		.type = MLXSW_SP_SAMPLE_TRIGGER_TYPE_POLICY_ENGINE,
	पूर्ण;
	काष्ठा mlxsw_sp_sample_params params;
	काष्ठा mlxsw_sp_port *mlxsw_sp_port;
	काष्ठा mlxsw_sp *mlxsw_sp = priv;
	पूर्णांक err;

	params.psample_group = psample_group;
	params.trunc_size = trunc_size;
	params.rate = rate;
	params.truncate = truncate;
	err = mlxsw_sp_sample_trigger_params_set(mlxsw_sp, &trigger, &params,
						 extack);
	अगर (err)
		वापस err;

	err = mlxsw_sp_span_agent_get(mlxsw_sp, p_span_id, &agent_parms);
	अगर (err) अणु
		NL_SET_ERR_MSG_MOD(extack, "Failed to get SPAN agent");
		जाओ err_span_agent_get;
	पूर्ण

	mlxsw_sp_port = mlxsw_sp->ports[local_port];
	err = mlxsw_sp_span_analyzed_port_get(mlxsw_sp_port, ingress);
	अगर (err) अणु
		NL_SET_ERR_MSG_MOD(extack, "Failed to get analyzed port");
		जाओ err_analyzed_port_get;
	पूर्ण

	वापस 0;

err_analyzed_port_get:
	mlxsw_sp_span_agent_put(mlxsw_sp, *p_span_id);
err_span_agent_get:
	mlxsw_sp_sample_trigger_params_unset(mlxsw_sp, &trigger);
	वापस err;
पूर्ण

अटल व्योम mlxsw_sp2_act_sampler_del(व्योम *priv, u8 local_port, पूर्णांक span_id,
				      bool ingress)
अणु
	काष्ठा mlxsw_sp_sample_trigger trigger = अणु
		.type = MLXSW_SP_SAMPLE_TRIGGER_TYPE_POLICY_ENGINE,
	पूर्ण;
	काष्ठा mlxsw_sp_port *mlxsw_sp_port;
	काष्ठा mlxsw_sp *mlxsw_sp = priv;

	mlxsw_sp_port = mlxsw_sp->ports[local_port];
	mlxsw_sp_span_analyzed_port_put(mlxsw_sp_port, ingress);
	mlxsw_sp_span_agent_put(mlxsw_sp, span_id);
	mlxsw_sp_sample_trigger_params_unset(mlxsw_sp, &trigger);
पूर्ण

स्थिर काष्ठा mlxsw_afa_ops mlxsw_sp2_act_afa_ops = अणु
	.kvdl_set_add		= mlxsw_sp2_act_kvdl_set_add,
	.kvdl_set_del		= mlxsw_sp_act_kvdl_set_del,
	.kvdl_set_activity_get	= mlxsw_sp2_act_kvdl_set_activity_get,
	.kvdl_fwd_entry_add	= mlxsw_sp_act_kvdl_fwd_entry_add,
	.kvdl_fwd_entry_del	= mlxsw_sp_act_kvdl_fwd_entry_del,
	.counter_index_get	= mlxsw_sp_act_counter_index_get,
	.counter_index_put	= mlxsw_sp_act_counter_index_put,
	.mirror_add		= mlxsw_sp_act_mirror_add,
	.mirror_del		= mlxsw_sp_act_mirror_del,
	.policer_add		= mlxsw_sp_act_policer_add,
	.policer_del		= mlxsw_sp_act_policer_del,
	.sampler_add		= mlxsw_sp2_act_sampler_add,
	.sampler_del		= mlxsw_sp2_act_sampler_del,
	.dummy_first_set	= true,
पूर्ण;

पूर्णांक mlxsw_sp_afa_init(काष्ठा mlxsw_sp *mlxsw_sp)
अणु
	mlxsw_sp->afa = mlxsw_afa_create(MLXSW_CORE_RES_GET(mlxsw_sp->core,
							    ACL_ACTIONS_PER_SET),
					 mlxsw_sp->afa_ops, mlxsw_sp);
	वापस PTR_ERR_OR_ZERO(mlxsw_sp->afa);
पूर्ण

व्योम mlxsw_sp_afa_fini(काष्ठा mlxsw_sp *mlxsw_sp)
अणु
	mlxsw_afa_destroy(mlxsw_sp->afa);
पूर्ण
