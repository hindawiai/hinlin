<शैली गुरु>
// SPDX-License-Identअगरier: BSD-3-Clause OR GPL-2.0
/* Copyright (c) 2018 Mellanox Technologies. All rights reserved */

#समावेश <linux/kernel.h>

#समावेश "core_acl_flex_actions.h"
#समावेश "spectrum.h"
#समावेश "spectrum_mr.h"

काष्ठा mlxsw_sp2_mr_tcam अणु
	काष्ठा mlxsw_sp *mlxsw_sp;
	काष्ठा mlxsw_sp_flow_block *flow_block;
	काष्ठा mlxsw_sp_acl_ruleset *ruleset4;
	काष्ठा mlxsw_sp_acl_ruleset *ruleset6;
पूर्ण;

काष्ठा mlxsw_sp2_mr_route अणु
	काष्ठा mlxsw_sp2_mr_tcam *mr_tcam;
पूर्ण;

अटल काष्ठा mlxsw_sp_acl_ruleset *
mlxsw_sp2_mr_tcam_proto_ruleset(काष्ठा mlxsw_sp2_mr_tcam *mr_tcam,
				क्रमागत mlxsw_sp_l3proto proto)
अणु
	चयन (proto) अणु
	हाल MLXSW_SP_L3_PROTO_IPV4:
		वापस mr_tcam->ruleset4;
	हाल MLXSW_SP_L3_PROTO_IPV6:
		वापस mr_tcam->ruleset6;
	पूर्ण
	वापस शून्य;
पूर्ण

अटल पूर्णांक mlxsw_sp2_mr_tcam_bind_group(काष्ठा mlxsw_sp *mlxsw_sp,
					क्रमागत mlxsw_reg_pemrbt_protocol protocol,
					काष्ठा mlxsw_sp_acl_ruleset *ruleset)
अणु
	अक्षर pemrbt_pl[MLXSW_REG_PEMRBT_LEN];
	u16 group_id;

	group_id = mlxsw_sp_acl_ruleset_group_id(ruleset);

	mlxsw_reg_pemrbt_pack(pemrbt_pl, protocol, group_id);
	वापस mlxsw_reg_ग_लिखो(mlxsw_sp->core, MLXSW_REG(pemrbt), pemrbt_pl);
पूर्ण

अटल स्थिर क्रमागत mlxsw_afk_element mlxsw_sp2_mr_tcam_usage_ipv4[] = अणु
		MLXSW_AFK_ELEMENT_VIRT_ROUTER_8_10,
		MLXSW_AFK_ELEMENT_VIRT_ROUTER_0_7,
		MLXSW_AFK_ELEMENT_SRC_IP_0_31,
		MLXSW_AFK_ELEMENT_DST_IP_0_31,
पूर्ण;

अटल पूर्णांक mlxsw_sp2_mr_tcam_ipv4_init(काष्ठा mlxsw_sp2_mr_tcam *mr_tcam)
अणु
	काष्ठा mlxsw_afk_element_usage elusage;
	पूर्णांक err;

	/* Initialize IPv4 ACL group. */
	mlxsw_afk_element_usage_fill(&elusage,
				     mlxsw_sp2_mr_tcam_usage_ipv4,
				     ARRAY_SIZE(mlxsw_sp2_mr_tcam_usage_ipv4));
	mr_tcam->ruleset4 = mlxsw_sp_acl_ruleset_get(mr_tcam->mlxsw_sp,
						     mr_tcam->flow_block,
						     MLXSW_SP_L3_PROTO_IPV4,
						     MLXSW_SP_ACL_PROखाता_MR,
						     &elusage);

	अगर (IS_ERR(mr_tcam->ruleset4))
		वापस PTR_ERR(mr_tcam->ruleset4);

	/* MC Router groups should be bound beक्रमe routes are inserted. */
	err = mlxsw_sp2_mr_tcam_bind_group(mr_tcam->mlxsw_sp,
					   MLXSW_REG_PEMRBT_PROTO_IPV4,
					   mr_tcam->ruleset4);
	अगर (err)
		जाओ err_bind_group;

	वापस 0;

err_bind_group:
	mlxsw_sp_acl_ruleset_put(mr_tcam->mlxsw_sp, mr_tcam->ruleset4);
	वापस err;
पूर्ण

अटल व्योम mlxsw_sp2_mr_tcam_ipv4_fini(काष्ठा mlxsw_sp2_mr_tcam *mr_tcam)
अणु
	mlxsw_sp_acl_ruleset_put(mr_tcam->mlxsw_sp, mr_tcam->ruleset4);
पूर्ण

अटल स्थिर क्रमागत mlxsw_afk_element mlxsw_sp2_mr_tcam_usage_ipv6[] = अणु
		MLXSW_AFK_ELEMENT_VIRT_ROUTER_8_10,
		MLXSW_AFK_ELEMENT_VIRT_ROUTER_0_7,
		MLXSW_AFK_ELEMENT_SRC_IP_96_127,
		MLXSW_AFK_ELEMENT_SRC_IP_64_95,
		MLXSW_AFK_ELEMENT_SRC_IP_32_63,
		MLXSW_AFK_ELEMENT_SRC_IP_0_31,
		MLXSW_AFK_ELEMENT_DST_IP_96_127,
		MLXSW_AFK_ELEMENT_DST_IP_64_95,
		MLXSW_AFK_ELEMENT_DST_IP_32_63,
		MLXSW_AFK_ELEMENT_DST_IP_0_31,
पूर्ण;

अटल पूर्णांक mlxsw_sp2_mr_tcam_ipv6_init(काष्ठा mlxsw_sp2_mr_tcam *mr_tcam)
अणु
	काष्ठा mlxsw_afk_element_usage elusage;
	पूर्णांक err;

	/* Initialize IPv6 ACL group */
	mlxsw_afk_element_usage_fill(&elusage,
				     mlxsw_sp2_mr_tcam_usage_ipv6,
				     ARRAY_SIZE(mlxsw_sp2_mr_tcam_usage_ipv6));
	mr_tcam->ruleset6 = mlxsw_sp_acl_ruleset_get(mr_tcam->mlxsw_sp,
						     mr_tcam->flow_block,
						     MLXSW_SP_L3_PROTO_IPV6,
						     MLXSW_SP_ACL_PROखाता_MR,
						     &elusage);

	अगर (IS_ERR(mr_tcam->ruleset6))
		वापस PTR_ERR(mr_tcam->ruleset6);

	/* MC Router groups should be bound beक्रमe routes are inserted. */
	err = mlxsw_sp2_mr_tcam_bind_group(mr_tcam->mlxsw_sp,
					   MLXSW_REG_PEMRBT_PROTO_IPV6,
					   mr_tcam->ruleset6);
	अगर (err)
		जाओ err_bind_group;

	वापस 0;

err_bind_group:
	mlxsw_sp_acl_ruleset_put(mr_tcam->mlxsw_sp, mr_tcam->ruleset6);
	वापस err;
पूर्ण

अटल व्योम mlxsw_sp2_mr_tcam_ipv6_fini(काष्ठा mlxsw_sp2_mr_tcam *mr_tcam)
अणु
	mlxsw_sp_acl_ruleset_put(mr_tcam->mlxsw_sp, mr_tcam->ruleset6);
पूर्ण

अटल व्योम
mlxsw_sp2_mr_tcam_rule_parse4(काष्ठा mlxsw_sp_acl_rule_info *rulei,
			      काष्ठा mlxsw_sp_mr_route_key *key)
अणु
	mlxsw_sp_acl_rulei_keymask_buf(rulei, MLXSW_AFK_ELEMENT_SRC_IP_0_31,
				       (अक्षर *) &key->source.addr4,
				       (अक्षर *) &key->source_mask.addr4, 4);
	mlxsw_sp_acl_rulei_keymask_buf(rulei, MLXSW_AFK_ELEMENT_DST_IP_0_31,
				       (अक्षर *) &key->group.addr4,
				       (अक्षर *) &key->group_mask.addr4, 4);
पूर्ण

अटल व्योम
mlxsw_sp2_mr_tcam_rule_parse6(काष्ठा mlxsw_sp_acl_rule_info *rulei,
			      काष्ठा mlxsw_sp_mr_route_key *key)
अणु
	mlxsw_sp_acl_rulei_keymask_buf(rulei, MLXSW_AFK_ELEMENT_SRC_IP_96_127,
				       &key->source.addr6.s6_addr[0x0],
				       &key->source_mask.addr6.s6_addr[0x0], 4);
	mlxsw_sp_acl_rulei_keymask_buf(rulei, MLXSW_AFK_ELEMENT_SRC_IP_64_95,
				       &key->source.addr6.s6_addr[0x4],
				       &key->source_mask.addr6.s6_addr[0x4], 4);
	mlxsw_sp_acl_rulei_keymask_buf(rulei, MLXSW_AFK_ELEMENT_SRC_IP_32_63,
				       &key->source.addr6.s6_addr[0x8],
				       &key->source_mask.addr6.s6_addr[0x8], 4);
	mlxsw_sp_acl_rulei_keymask_buf(rulei, MLXSW_AFK_ELEMENT_SRC_IP_0_31,
				       &key->source.addr6.s6_addr[0xc],
				       &key->source_mask.addr6.s6_addr[0xc], 4);
	mlxsw_sp_acl_rulei_keymask_buf(rulei, MLXSW_AFK_ELEMENT_DST_IP_96_127,
				       &key->group.addr6.s6_addr[0x0],
				       &key->group_mask.addr6.s6_addr[0x0], 4);
	mlxsw_sp_acl_rulei_keymask_buf(rulei, MLXSW_AFK_ELEMENT_DST_IP_64_95,
				       &key->group.addr6.s6_addr[0x4],
				       &key->group_mask.addr6.s6_addr[0x4], 4);
	mlxsw_sp_acl_rulei_keymask_buf(rulei, MLXSW_AFK_ELEMENT_DST_IP_32_63,
				       &key->group.addr6.s6_addr[0x8],
				       &key->group_mask.addr6.s6_addr[0x8], 4);
	mlxsw_sp_acl_rulei_keymask_buf(rulei, MLXSW_AFK_ELEMENT_DST_IP_0_31,
				       &key->group.addr6.s6_addr[0xc],
				       &key->group_mask.addr6.s6_addr[0xc], 4);
पूर्ण

अटल व्योम
mlxsw_sp2_mr_tcam_rule_parse(काष्ठा mlxsw_sp_acl_rule *rule,
			     काष्ठा mlxsw_sp_mr_route_key *key,
			     अचिन्हित पूर्णांक priority)
अणु
	काष्ठा mlxsw_sp_acl_rule_info *rulei;

	rulei = mlxsw_sp_acl_rule_rulei(rule);
	rulei->priority = priority;
	mlxsw_sp_acl_rulei_keymask_u32(rulei, MLXSW_AFK_ELEMENT_VIRT_ROUTER_0_7,
				       key->vrid, GENMASK(7, 0));
	mlxsw_sp_acl_rulei_keymask_u32(rulei,
				       MLXSW_AFK_ELEMENT_VIRT_ROUTER_8_10,
				       key->vrid >> 8, GENMASK(2, 0));
	चयन (key->proto) अणु
	हाल MLXSW_SP_L3_PROTO_IPV4:
		वापस mlxsw_sp2_mr_tcam_rule_parse4(rulei, key);
	हाल MLXSW_SP_L3_PROTO_IPV6:
		वापस mlxsw_sp2_mr_tcam_rule_parse6(rulei, key);
	पूर्ण
पूर्ण

अटल पूर्णांक
mlxsw_sp2_mr_tcam_route_create(काष्ठा mlxsw_sp *mlxsw_sp, व्योम *priv,
			       व्योम *route_priv,
			       काष्ठा mlxsw_sp_mr_route_key *key,
			       काष्ठा mlxsw_afa_block *afa_block,
			       क्रमागत mlxsw_sp_mr_route_prio prio)
अणु
	काष्ठा mlxsw_sp2_mr_route *mr_route = route_priv;
	काष्ठा mlxsw_sp2_mr_tcam *mr_tcam = priv;
	काष्ठा mlxsw_sp_acl_ruleset *ruleset;
	काष्ठा mlxsw_sp_acl_rule *rule;
	पूर्णांक err;

	mr_route->mr_tcam = mr_tcam;
	ruleset = mlxsw_sp2_mr_tcam_proto_ruleset(mr_tcam, key->proto);
	अगर (WARN_ON(!ruleset))
		वापस -EINVAL;

	rule = mlxsw_sp_acl_rule_create(mlxsw_sp, ruleset,
					(अचिन्हित दीर्घ) route_priv, afa_block,
					शून्य);
	अगर (IS_ERR(rule))
		वापस PTR_ERR(rule);

	mlxsw_sp2_mr_tcam_rule_parse(rule, key, prio);
	err = mlxsw_sp_acl_rule_add(mlxsw_sp, rule);
	अगर (err)
		जाओ err_rule_add;

	वापस 0;

err_rule_add:
	mlxsw_sp_acl_rule_destroy(mlxsw_sp, rule);
	वापस err;
पूर्ण

अटल व्योम
mlxsw_sp2_mr_tcam_route_destroy(काष्ठा mlxsw_sp *mlxsw_sp, व्योम *priv,
				व्योम *route_priv,
				काष्ठा mlxsw_sp_mr_route_key *key)
अणु
	काष्ठा mlxsw_sp2_mr_tcam *mr_tcam = priv;
	काष्ठा mlxsw_sp_acl_ruleset *ruleset;
	काष्ठा mlxsw_sp_acl_rule *rule;

	ruleset = mlxsw_sp2_mr_tcam_proto_ruleset(mr_tcam, key->proto);
	अगर (WARN_ON(!ruleset))
		वापस;

	rule = mlxsw_sp_acl_rule_lookup(mlxsw_sp, ruleset,
					(अचिन्हित दीर्घ) route_priv);
	अगर (WARN_ON(!rule))
		वापस;

	mlxsw_sp_acl_rule_del(mlxsw_sp, rule);
	mlxsw_sp_acl_rule_destroy(mlxsw_sp, rule);
पूर्ण

अटल पूर्णांक
mlxsw_sp2_mr_tcam_route_update(काष्ठा mlxsw_sp *mlxsw_sp,
			       व्योम *route_priv,
			       काष्ठा mlxsw_sp_mr_route_key *key,
			       काष्ठा mlxsw_afa_block *afa_block)
अणु
	काष्ठा mlxsw_sp2_mr_route *mr_route = route_priv;
	काष्ठा mlxsw_sp2_mr_tcam *mr_tcam = mr_route->mr_tcam;
	काष्ठा mlxsw_sp_acl_ruleset *ruleset;
	काष्ठा mlxsw_sp_acl_rule *rule;

	ruleset = mlxsw_sp2_mr_tcam_proto_ruleset(mr_tcam, key->proto);
	अगर (WARN_ON(!ruleset))
		वापस -EINVAL;

	rule = mlxsw_sp_acl_rule_lookup(mlxsw_sp, ruleset,
					(अचिन्हित दीर्घ) route_priv);
	अगर (WARN_ON(!rule))
		वापस -EINVAL;

	वापस mlxsw_sp_acl_rule_action_replace(mlxsw_sp, rule, afa_block);
पूर्ण

अटल पूर्णांक mlxsw_sp2_mr_tcam_init(काष्ठा mlxsw_sp *mlxsw_sp, व्योम *priv)
अणु
	काष्ठा mlxsw_sp2_mr_tcam *mr_tcam = priv;
	पूर्णांक err;

	mr_tcam->mlxsw_sp = mlxsw_sp;
	mr_tcam->flow_block = mlxsw_sp_flow_block_create(mlxsw_sp, शून्य);
	अगर (!mr_tcam->flow_block)
		वापस -ENOMEM;

	err = mlxsw_sp2_mr_tcam_ipv4_init(mr_tcam);
	अगर (err)
		जाओ err_ipv4_init;

	err = mlxsw_sp2_mr_tcam_ipv6_init(mr_tcam);
	अगर (err)
		जाओ err_ipv6_init;

	वापस 0;

err_ipv6_init:
	mlxsw_sp2_mr_tcam_ipv4_fini(mr_tcam);
err_ipv4_init:
	mlxsw_sp_flow_block_destroy(mr_tcam->flow_block);
	वापस err;
पूर्ण

अटल व्योम mlxsw_sp2_mr_tcam_fini(व्योम *priv)
अणु
	काष्ठा mlxsw_sp2_mr_tcam *mr_tcam = priv;

	mlxsw_sp2_mr_tcam_ipv6_fini(mr_tcam);
	mlxsw_sp2_mr_tcam_ipv4_fini(mr_tcam);
	mlxsw_sp_flow_block_destroy(mr_tcam->flow_block);
पूर्ण

स्थिर काष्ठा mlxsw_sp_mr_tcam_ops mlxsw_sp2_mr_tcam_ops = अणु
	.priv_size = माप(काष्ठा mlxsw_sp2_mr_tcam),
	.init = mlxsw_sp2_mr_tcam_init,
	.fini = mlxsw_sp2_mr_tcam_fini,
	.route_priv_size = माप(काष्ठा mlxsw_sp2_mr_route),
	.route_create = mlxsw_sp2_mr_tcam_route_create,
	.route_destroy = mlxsw_sp2_mr_tcam_route_destroy,
	.route_update = mlxsw_sp2_mr_tcam_route_update,
पूर्ण;
