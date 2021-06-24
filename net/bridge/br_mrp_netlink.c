<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later

#समावेश <net/genetlink.h>

#समावेश <uapi/linux/mrp_bridge.h>
#समावेश "br_private.h"
#समावेश "br_private_mrp.h"

अटल स्थिर काष्ठा nla_policy br_mrp_policy[IFLA_BRIDGE_MRP_MAX + 1] = अणु
	[IFLA_BRIDGE_MRP_UNSPEC]	= अणु .type = NLA_REJECT पूर्ण,
	[IFLA_BRIDGE_MRP_INSTANCE]	= अणु .type = NLA_NESTED पूर्ण,
	[IFLA_BRIDGE_MRP_PORT_STATE]	= अणु .type = NLA_NESTED पूर्ण,
	[IFLA_BRIDGE_MRP_PORT_ROLE]	= अणु .type = NLA_NESTED पूर्ण,
	[IFLA_BRIDGE_MRP_RING_STATE]	= अणु .type = NLA_NESTED पूर्ण,
	[IFLA_BRIDGE_MRP_RING_ROLE]	= अणु .type = NLA_NESTED पूर्ण,
	[IFLA_BRIDGE_MRP_START_TEST]	= अणु .type = NLA_NESTED पूर्ण,
	[IFLA_BRIDGE_MRP_IN_ROLE]	= अणु .type = NLA_NESTED पूर्ण,
	[IFLA_BRIDGE_MRP_IN_STATE]	= अणु .type = NLA_NESTED पूर्ण,
	[IFLA_BRIDGE_MRP_START_IN_TEST]	= अणु .type = NLA_NESTED पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा nla_policy
br_mrp_instance_policy[IFLA_BRIDGE_MRP_INSTANCE_MAX + 1] = अणु
	[IFLA_BRIDGE_MRP_INSTANCE_UNSPEC]	= अणु .type = NLA_REJECT पूर्ण,
	[IFLA_BRIDGE_MRP_INSTANCE_RING_ID]	= अणु .type = NLA_U32 पूर्ण,
	[IFLA_BRIDGE_MRP_INSTANCE_P_IFINDEX]	= अणु .type = NLA_U32 पूर्ण,
	[IFLA_BRIDGE_MRP_INSTANCE_S_IFINDEX]	= अणु .type = NLA_U32 पूर्ण,
	[IFLA_BRIDGE_MRP_INSTANCE_PRIO]		= अणु .type = NLA_U16 पूर्ण,
पूर्ण;

अटल पूर्णांक br_mrp_instance_parse(काष्ठा net_bridge *br, काष्ठा nlattr *attr,
				 पूर्णांक cmd, काष्ठा netlink_ext_ack *extack)
अणु
	काष्ठा nlattr *tb[IFLA_BRIDGE_MRP_INSTANCE_MAX + 1];
	काष्ठा br_mrp_instance inst;
	पूर्णांक err;

	err = nla_parse_nested(tb, IFLA_BRIDGE_MRP_INSTANCE_MAX, attr,
			       br_mrp_instance_policy, extack);
	अगर (err)
		वापस err;

	अगर (!tb[IFLA_BRIDGE_MRP_INSTANCE_RING_ID] ||
	    !tb[IFLA_BRIDGE_MRP_INSTANCE_P_IFINDEX] ||
	    !tb[IFLA_BRIDGE_MRP_INSTANCE_S_IFINDEX]) अणु
		NL_SET_ERR_MSG_MOD(extack,
				   "Missing attribute: RING_ID or P_IFINDEX or S_IFINDEX");
		वापस -EINVAL;
	पूर्ण

	स_रखो(&inst, 0, माप(inst));

	inst.ring_id = nla_get_u32(tb[IFLA_BRIDGE_MRP_INSTANCE_RING_ID]);
	inst.p_अगरindex = nla_get_u32(tb[IFLA_BRIDGE_MRP_INSTANCE_P_IFINDEX]);
	inst.s_अगरindex = nla_get_u32(tb[IFLA_BRIDGE_MRP_INSTANCE_S_IFINDEX]);
	inst.prio = MRP_DEFAULT_PRIO;

	अगर (tb[IFLA_BRIDGE_MRP_INSTANCE_PRIO])
		inst.prio = nla_get_u16(tb[IFLA_BRIDGE_MRP_INSTANCE_PRIO]);

	अगर (cmd == RTM_SETLINK)
		वापस br_mrp_add(br, &inst);
	अन्यथा
		वापस br_mrp_del(br, &inst);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा nla_policy
br_mrp_port_state_policy[IFLA_BRIDGE_MRP_PORT_STATE_MAX + 1] = अणु
	[IFLA_BRIDGE_MRP_PORT_STATE_UNSPEC]	= अणु .type = NLA_REJECT पूर्ण,
	[IFLA_BRIDGE_MRP_PORT_STATE_STATE]	= अणु .type = NLA_U32 पूर्ण,
पूर्ण;

अटल पूर्णांक br_mrp_port_state_parse(काष्ठा net_bridge_port *p,
				   काष्ठा nlattr *attr,
				   काष्ठा netlink_ext_ack *extack)
अणु
	काष्ठा nlattr *tb[IFLA_BRIDGE_MRP_PORT_STATE_MAX + 1];
	क्रमागत br_mrp_port_state_type state;
	पूर्णांक err;

	err = nla_parse_nested(tb, IFLA_BRIDGE_MRP_PORT_STATE_MAX, attr,
			       br_mrp_port_state_policy, extack);
	अगर (err)
		वापस err;

	अगर (!tb[IFLA_BRIDGE_MRP_PORT_STATE_STATE]) अणु
		NL_SET_ERR_MSG_MOD(extack, "Missing attribute: STATE");
		वापस -EINVAL;
	पूर्ण

	state = nla_get_u32(tb[IFLA_BRIDGE_MRP_PORT_STATE_STATE]);

	वापस br_mrp_set_port_state(p, state);
पूर्ण

अटल स्थिर काष्ठा nla_policy
br_mrp_port_role_policy[IFLA_BRIDGE_MRP_PORT_ROLE_MAX + 1] = अणु
	[IFLA_BRIDGE_MRP_PORT_ROLE_UNSPEC]	= अणु .type = NLA_REJECT पूर्ण,
	[IFLA_BRIDGE_MRP_PORT_ROLE_ROLE]	= अणु .type = NLA_U32 पूर्ण,
पूर्ण;

अटल पूर्णांक br_mrp_port_role_parse(काष्ठा net_bridge_port *p,
				  काष्ठा nlattr *attr,
				  काष्ठा netlink_ext_ack *extack)
अणु
	काष्ठा nlattr *tb[IFLA_BRIDGE_MRP_PORT_ROLE_MAX + 1];
	क्रमागत br_mrp_port_role_type role;
	पूर्णांक err;

	err = nla_parse_nested(tb, IFLA_BRIDGE_MRP_PORT_ROLE_MAX, attr,
			       br_mrp_port_role_policy, extack);
	अगर (err)
		वापस err;

	अगर (!tb[IFLA_BRIDGE_MRP_PORT_ROLE_ROLE]) अणु
		NL_SET_ERR_MSG_MOD(extack, "Missing attribute: ROLE");
		वापस -EINVAL;
	पूर्ण

	role = nla_get_u32(tb[IFLA_BRIDGE_MRP_PORT_ROLE_ROLE]);

	वापस br_mrp_set_port_role(p, role);
पूर्ण

अटल स्थिर काष्ठा nla_policy
br_mrp_ring_state_policy[IFLA_BRIDGE_MRP_RING_STATE_MAX + 1] = अणु
	[IFLA_BRIDGE_MRP_RING_STATE_UNSPEC]	= अणु .type = NLA_REJECT पूर्ण,
	[IFLA_BRIDGE_MRP_RING_STATE_RING_ID]	= अणु .type = NLA_U32 पूर्ण,
	[IFLA_BRIDGE_MRP_RING_STATE_STATE]	= अणु .type = NLA_U32 पूर्ण,
पूर्ण;

अटल पूर्णांक br_mrp_ring_state_parse(काष्ठा net_bridge *br, काष्ठा nlattr *attr,
				   काष्ठा netlink_ext_ack *extack)
अणु
	काष्ठा nlattr *tb[IFLA_BRIDGE_MRP_RING_STATE_MAX + 1];
	काष्ठा br_mrp_ring_state state;
	पूर्णांक err;

	err = nla_parse_nested(tb, IFLA_BRIDGE_MRP_RING_STATE_MAX, attr,
			       br_mrp_ring_state_policy, extack);
	अगर (err)
		वापस err;

	अगर (!tb[IFLA_BRIDGE_MRP_RING_STATE_RING_ID] ||
	    !tb[IFLA_BRIDGE_MRP_RING_STATE_STATE]) अणु
		NL_SET_ERR_MSG_MOD(extack,
				   "Missing attribute: RING_ID or STATE");
		वापस -EINVAL;
	पूर्ण

	स_रखो(&state, 0x0, माप(state));

	state.ring_id = nla_get_u32(tb[IFLA_BRIDGE_MRP_RING_STATE_RING_ID]);
	state.ring_state = nla_get_u32(tb[IFLA_BRIDGE_MRP_RING_STATE_STATE]);

	वापस br_mrp_set_ring_state(br, &state);
पूर्ण

अटल स्थिर काष्ठा nla_policy
br_mrp_ring_role_policy[IFLA_BRIDGE_MRP_RING_ROLE_MAX + 1] = अणु
	[IFLA_BRIDGE_MRP_RING_ROLE_UNSPEC]	= अणु .type = NLA_REJECT पूर्ण,
	[IFLA_BRIDGE_MRP_RING_ROLE_RING_ID]	= अणु .type = NLA_U32 पूर्ण,
	[IFLA_BRIDGE_MRP_RING_ROLE_ROLE]	= अणु .type = NLA_U32 पूर्ण,
पूर्ण;

अटल पूर्णांक br_mrp_ring_role_parse(काष्ठा net_bridge *br, काष्ठा nlattr *attr,
				  काष्ठा netlink_ext_ack *extack)
अणु
	काष्ठा nlattr *tb[IFLA_BRIDGE_MRP_RING_ROLE_MAX + 1];
	काष्ठा br_mrp_ring_role role;
	पूर्णांक err;

	err = nla_parse_nested(tb, IFLA_BRIDGE_MRP_RING_ROLE_MAX, attr,
			       br_mrp_ring_role_policy, extack);
	अगर (err)
		वापस err;

	अगर (!tb[IFLA_BRIDGE_MRP_RING_ROLE_RING_ID] ||
	    !tb[IFLA_BRIDGE_MRP_RING_ROLE_ROLE]) अणु
		NL_SET_ERR_MSG_MOD(extack,
				   "Missing attribute: RING_ID or ROLE");
		वापस -EINVAL;
	पूर्ण

	स_रखो(&role, 0x0, माप(role));

	role.ring_id = nla_get_u32(tb[IFLA_BRIDGE_MRP_RING_ROLE_RING_ID]);
	role.ring_role = nla_get_u32(tb[IFLA_BRIDGE_MRP_RING_ROLE_ROLE]);

	वापस br_mrp_set_ring_role(br, &role);
पूर्ण

अटल स्थिर काष्ठा nla_policy
br_mrp_start_test_policy[IFLA_BRIDGE_MRP_START_TEST_MAX + 1] = अणु
	[IFLA_BRIDGE_MRP_START_TEST_UNSPEC]	= अणु .type = NLA_REJECT पूर्ण,
	[IFLA_BRIDGE_MRP_START_TEST_RING_ID]	= अणु .type = NLA_U32 पूर्ण,
	[IFLA_BRIDGE_MRP_START_TEST_INTERVAL]	= अणु .type = NLA_U32 पूर्ण,
	[IFLA_BRIDGE_MRP_START_TEST_MAX_MISS]	= अणु .type = NLA_U32 पूर्ण,
	[IFLA_BRIDGE_MRP_START_TEST_PERIOD]	= अणु .type = NLA_U32 पूर्ण,
	[IFLA_BRIDGE_MRP_START_TEST_MONITOR]	= अणु .type = NLA_U32 पूर्ण,
पूर्ण;

अटल पूर्णांक br_mrp_start_test_parse(काष्ठा net_bridge *br, काष्ठा nlattr *attr,
				   काष्ठा netlink_ext_ack *extack)
अणु
	काष्ठा nlattr *tb[IFLA_BRIDGE_MRP_START_TEST_MAX + 1];
	काष्ठा br_mrp_start_test test;
	पूर्णांक err;

	err = nla_parse_nested(tb, IFLA_BRIDGE_MRP_START_TEST_MAX, attr,
			       br_mrp_start_test_policy, extack);
	अगर (err)
		वापस err;

	अगर (!tb[IFLA_BRIDGE_MRP_START_TEST_RING_ID] ||
	    !tb[IFLA_BRIDGE_MRP_START_TEST_INTERVAL] ||
	    !tb[IFLA_BRIDGE_MRP_START_TEST_MAX_MISS] ||
	    !tb[IFLA_BRIDGE_MRP_START_TEST_PERIOD]) अणु
		NL_SET_ERR_MSG_MOD(extack,
				   "Missing attribute: RING_ID or INTERVAL or MAX_MISS or PERIOD");
		वापस -EINVAL;
	पूर्ण

	स_रखो(&test, 0x0, माप(test));

	test.ring_id = nla_get_u32(tb[IFLA_BRIDGE_MRP_START_TEST_RING_ID]);
	test.पूर्णांकerval = nla_get_u32(tb[IFLA_BRIDGE_MRP_START_TEST_INTERVAL]);
	test.max_miss = nla_get_u32(tb[IFLA_BRIDGE_MRP_START_TEST_MAX_MISS]);
	test.period = nla_get_u32(tb[IFLA_BRIDGE_MRP_START_TEST_PERIOD]);
	test.monitor = false;

	अगर (tb[IFLA_BRIDGE_MRP_START_TEST_MONITOR])
		test.monitor =
			nla_get_u32(tb[IFLA_BRIDGE_MRP_START_TEST_MONITOR]);

	वापस br_mrp_start_test(br, &test);
पूर्ण

अटल स्थिर काष्ठा nla_policy
br_mrp_in_state_policy[IFLA_BRIDGE_MRP_IN_STATE_MAX + 1] = अणु
	[IFLA_BRIDGE_MRP_IN_STATE_UNSPEC]	= अणु .type = NLA_REJECT पूर्ण,
	[IFLA_BRIDGE_MRP_IN_STATE_IN_ID]	= अणु .type = NLA_U32 पूर्ण,
	[IFLA_BRIDGE_MRP_IN_STATE_STATE]	= अणु .type = NLA_U32 पूर्ण,
पूर्ण;

अटल पूर्णांक br_mrp_in_state_parse(काष्ठा net_bridge *br, काष्ठा nlattr *attr,
				 काष्ठा netlink_ext_ack *extack)
अणु
	काष्ठा nlattr *tb[IFLA_BRIDGE_MRP_IN_STATE_MAX + 1];
	काष्ठा br_mrp_in_state state;
	पूर्णांक err;

	err = nla_parse_nested(tb, IFLA_BRIDGE_MRP_IN_STATE_MAX, attr,
			       br_mrp_in_state_policy, extack);
	अगर (err)
		वापस err;

	अगर (!tb[IFLA_BRIDGE_MRP_IN_STATE_IN_ID] ||
	    !tb[IFLA_BRIDGE_MRP_IN_STATE_STATE]) अणु
		NL_SET_ERR_MSG_MOD(extack,
				   "Missing attribute: IN_ID or STATE");
		वापस -EINVAL;
	पूर्ण

	स_रखो(&state, 0x0, माप(state));

	state.in_id = nla_get_u32(tb[IFLA_BRIDGE_MRP_IN_STATE_IN_ID]);
	state.in_state = nla_get_u32(tb[IFLA_BRIDGE_MRP_IN_STATE_STATE]);

	वापस br_mrp_set_in_state(br, &state);
पूर्ण

अटल स्थिर काष्ठा nla_policy
br_mrp_in_role_policy[IFLA_BRIDGE_MRP_IN_ROLE_MAX + 1] = अणु
	[IFLA_BRIDGE_MRP_IN_ROLE_UNSPEC]	= अणु .type = NLA_REJECT पूर्ण,
	[IFLA_BRIDGE_MRP_IN_ROLE_RING_ID]	= अणु .type = NLA_U32 पूर्ण,
	[IFLA_BRIDGE_MRP_IN_ROLE_IN_ID]		= अणु .type = NLA_U16 पूर्ण,
	[IFLA_BRIDGE_MRP_IN_ROLE_ROLE]		= अणु .type = NLA_U32 पूर्ण,
	[IFLA_BRIDGE_MRP_IN_ROLE_I_IFINDEX]	= अणु .type = NLA_U32 पूर्ण,
पूर्ण;

अटल पूर्णांक br_mrp_in_role_parse(काष्ठा net_bridge *br, काष्ठा nlattr *attr,
				काष्ठा netlink_ext_ack *extack)
अणु
	काष्ठा nlattr *tb[IFLA_BRIDGE_MRP_IN_ROLE_MAX + 1];
	काष्ठा br_mrp_in_role role;
	पूर्णांक err;

	err = nla_parse_nested(tb, IFLA_BRIDGE_MRP_IN_ROLE_MAX, attr,
			       br_mrp_in_role_policy, extack);
	अगर (err)
		वापस err;

	अगर (!tb[IFLA_BRIDGE_MRP_IN_ROLE_RING_ID] ||
	    !tb[IFLA_BRIDGE_MRP_IN_ROLE_IN_ID] ||
	    !tb[IFLA_BRIDGE_MRP_IN_ROLE_I_IFINDEX] ||
	    !tb[IFLA_BRIDGE_MRP_IN_ROLE_ROLE]) अणु
		NL_SET_ERR_MSG_MOD(extack,
				   "Missing attribute: RING_ID or ROLE or IN_ID or I_IFINDEX");
		वापस -EINVAL;
	पूर्ण

	स_रखो(&role, 0x0, माप(role));

	role.ring_id = nla_get_u32(tb[IFLA_BRIDGE_MRP_IN_ROLE_RING_ID]);
	role.in_id = nla_get_u16(tb[IFLA_BRIDGE_MRP_IN_ROLE_IN_ID]);
	role.i_अगरindex = nla_get_u32(tb[IFLA_BRIDGE_MRP_IN_ROLE_I_IFINDEX]);
	role.in_role = nla_get_u32(tb[IFLA_BRIDGE_MRP_IN_ROLE_ROLE]);

	वापस br_mrp_set_in_role(br, &role);
पूर्ण

अटल स्थिर काष्ठा nla_policy
br_mrp_start_in_test_policy[IFLA_BRIDGE_MRP_START_IN_TEST_MAX + 1] = अणु
	[IFLA_BRIDGE_MRP_START_IN_TEST_UNSPEC]	= अणु .type = NLA_REJECT पूर्ण,
	[IFLA_BRIDGE_MRP_START_IN_TEST_IN_ID]	= अणु .type = NLA_U32 पूर्ण,
	[IFLA_BRIDGE_MRP_START_IN_TEST_INTERVAL]	= अणु .type = NLA_U32 पूर्ण,
	[IFLA_BRIDGE_MRP_START_IN_TEST_MAX_MISS]	= अणु .type = NLA_U32 पूर्ण,
	[IFLA_BRIDGE_MRP_START_IN_TEST_PERIOD]	= अणु .type = NLA_U32 पूर्ण,
पूर्ण;

अटल पूर्णांक br_mrp_start_in_test_parse(काष्ठा net_bridge *br,
				      काष्ठा nlattr *attr,
				      काष्ठा netlink_ext_ack *extack)
अणु
	काष्ठा nlattr *tb[IFLA_BRIDGE_MRP_START_IN_TEST_MAX + 1];
	काष्ठा br_mrp_start_in_test test;
	पूर्णांक err;

	err = nla_parse_nested(tb, IFLA_BRIDGE_MRP_START_IN_TEST_MAX, attr,
			       br_mrp_start_in_test_policy, extack);
	अगर (err)
		वापस err;

	अगर (!tb[IFLA_BRIDGE_MRP_START_IN_TEST_IN_ID] ||
	    !tb[IFLA_BRIDGE_MRP_START_IN_TEST_INTERVAL] ||
	    !tb[IFLA_BRIDGE_MRP_START_IN_TEST_MAX_MISS] ||
	    !tb[IFLA_BRIDGE_MRP_START_IN_TEST_PERIOD]) अणु
		NL_SET_ERR_MSG_MOD(extack,
				   "Missing attribute: RING_ID or INTERVAL or MAX_MISS or PERIOD");
		वापस -EINVAL;
	पूर्ण

	स_रखो(&test, 0x0, माप(test));

	test.in_id = nla_get_u32(tb[IFLA_BRIDGE_MRP_START_IN_TEST_IN_ID]);
	test.पूर्णांकerval = nla_get_u32(tb[IFLA_BRIDGE_MRP_START_IN_TEST_INTERVAL]);
	test.max_miss = nla_get_u32(tb[IFLA_BRIDGE_MRP_START_IN_TEST_MAX_MISS]);
	test.period = nla_get_u32(tb[IFLA_BRIDGE_MRP_START_IN_TEST_PERIOD]);

	वापस br_mrp_start_in_test(br, &test);
पूर्ण

पूर्णांक br_mrp_parse(काष्ठा net_bridge *br, काष्ठा net_bridge_port *p,
		 काष्ठा nlattr *attr, पूर्णांक cmd, काष्ठा netlink_ext_ack *extack)
अणु
	काष्ठा nlattr *tb[IFLA_BRIDGE_MRP_MAX + 1];
	पूर्णांक err;

	/* When this function is called क्रम a port then the br poपूर्णांकer is
	 * invalid, thereक्रम set the br to poपूर्णांक correctly
	 */
	अगर (p)
		br = p->br;

	अगर (br->stp_enabled != BR_NO_STP) अणु
		NL_SET_ERR_MSG_MOD(extack, "MRP can't be enabled if STP is already enabled");
		वापस -EINVAL;
	पूर्ण

	err = nla_parse_nested(tb, IFLA_BRIDGE_MRP_MAX, attr,
			       br_mrp_policy, extack);
	अगर (err)
		वापस err;

	अगर (tb[IFLA_BRIDGE_MRP_INSTANCE]) अणु
		err = br_mrp_instance_parse(br, tb[IFLA_BRIDGE_MRP_INSTANCE],
					    cmd, extack);
		अगर (err)
			वापस err;
	पूर्ण

	अगर (tb[IFLA_BRIDGE_MRP_PORT_STATE]) अणु
		err = br_mrp_port_state_parse(p, tb[IFLA_BRIDGE_MRP_PORT_STATE],
					      extack);
		अगर (err)
			वापस err;
	पूर्ण

	अगर (tb[IFLA_BRIDGE_MRP_PORT_ROLE]) अणु
		err = br_mrp_port_role_parse(p, tb[IFLA_BRIDGE_MRP_PORT_ROLE],
					     extack);
		अगर (err)
			वापस err;
	पूर्ण

	अगर (tb[IFLA_BRIDGE_MRP_RING_STATE]) अणु
		err = br_mrp_ring_state_parse(br,
					      tb[IFLA_BRIDGE_MRP_RING_STATE],
					      extack);
		अगर (err)
			वापस err;
	पूर्ण

	अगर (tb[IFLA_BRIDGE_MRP_RING_ROLE]) अणु
		err = br_mrp_ring_role_parse(br, tb[IFLA_BRIDGE_MRP_RING_ROLE],
					     extack);
		अगर (err)
			वापस err;
	पूर्ण

	अगर (tb[IFLA_BRIDGE_MRP_START_TEST]) अणु
		err = br_mrp_start_test_parse(br,
					      tb[IFLA_BRIDGE_MRP_START_TEST],
					      extack);
		अगर (err)
			वापस err;
	पूर्ण

	अगर (tb[IFLA_BRIDGE_MRP_IN_STATE]) अणु
		err = br_mrp_in_state_parse(br, tb[IFLA_BRIDGE_MRP_IN_STATE],
					    extack);
		अगर (err)
			वापस err;
	पूर्ण

	अगर (tb[IFLA_BRIDGE_MRP_IN_ROLE]) अणु
		err = br_mrp_in_role_parse(br, tb[IFLA_BRIDGE_MRP_IN_ROLE],
					   extack);
		अगर (err)
			वापस err;
	पूर्ण

	अगर (tb[IFLA_BRIDGE_MRP_START_IN_TEST]) अणु
		err = br_mrp_start_in_test_parse(br,
						 tb[IFLA_BRIDGE_MRP_START_IN_TEST],
						 extack);
		अगर (err)
			वापस err;
	पूर्ण

	वापस 0;
पूर्ण

पूर्णांक br_mrp_fill_info(काष्ठा sk_buff *skb, काष्ठा net_bridge *br)
अणु
	काष्ठा nlattr *tb, *mrp_tb;
	काष्ठा br_mrp *mrp;

	mrp_tb = nla_nest_start_noflag(skb, IFLA_BRIDGE_MRP);
	अगर (!mrp_tb)
		वापस -EMSGSIZE;

	hlist_क्रम_each_entry_rcu(mrp, &br->mrp_list, list) अणु
		काष्ठा net_bridge_port *p;

		tb = nla_nest_start_noflag(skb, IFLA_BRIDGE_MRP_INFO);
		अगर (!tb)
			जाओ nla_info_failure;

		अगर (nla_put_u32(skb, IFLA_BRIDGE_MRP_INFO_RING_ID,
				mrp->ring_id))
			जाओ nla_put_failure;

		p = rcu_dereference(mrp->p_port);
		अगर (p && nla_put_u32(skb, IFLA_BRIDGE_MRP_INFO_P_IFINDEX,
				     p->dev->अगरindex))
			जाओ nla_put_failure;

		p = rcu_dereference(mrp->s_port);
		अगर (p && nla_put_u32(skb, IFLA_BRIDGE_MRP_INFO_S_IFINDEX,
				     p->dev->अगरindex))
			जाओ nla_put_failure;

		p = rcu_dereference(mrp->i_port);
		अगर (p && nla_put_u32(skb, IFLA_BRIDGE_MRP_INFO_I_IFINDEX,
				     p->dev->अगरindex))
			जाओ nla_put_failure;

		अगर (nla_put_u16(skb, IFLA_BRIDGE_MRP_INFO_PRIO,
				mrp->prio))
			जाओ nla_put_failure;
		अगर (nla_put_u32(skb, IFLA_BRIDGE_MRP_INFO_RING_STATE,
				mrp->ring_state))
			जाओ nla_put_failure;
		अगर (nla_put_u32(skb, IFLA_BRIDGE_MRP_INFO_RING_ROLE,
				mrp->ring_role))
			जाओ nla_put_failure;
		अगर (nla_put_u32(skb, IFLA_BRIDGE_MRP_INFO_TEST_INTERVAL,
				mrp->test_पूर्णांकerval))
			जाओ nla_put_failure;
		अगर (nla_put_u32(skb, IFLA_BRIDGE_MRP_INFO_TEST_MAX_MISS,
				mrp->test_max_miss))
			जाओ nla_put_failure;
		अगर (nla_put_u32(skb, IFLA_BRIDGE_MRP_INFO_TEST_MONITOR,
				mrp->test_monitor))
			जाओ nla_put_failure;

		अगर (nla_put_u32(skb, IFLA_BRIDGE_MRP_INFO_IN_STATE,
				mrp->in_state))
			जाओ nla_put_failure;
		अगर (nla_put_u32(skb, IFLA_BRIDGE_MRP_INFO_IN_ROLE,
				mrp->in_role))
			जाओ nla_put_failure;
		अगर (nla_put_u32(skb, IFLA_BRIDGE_MRP_INFO_IN_TEST_INTERVAL,
				mrp->in_test_पूर्णांकerval))
			जाओ nla_put_failure;
		अगर (nla_put_u32(skb, IFLA_BRIDGE_MRP_INFO_IN_TEST_MAX_MISS,
				mrp->in_test_max_miss))
			जाओ nla_put_failure;

		nla_nest_end(skb, tb);
	पूर्ण
	nla_nest_end(skb, mrp_tb);

	वापस 0;

nla_put_failure:
	nla_nest_cancel(skb, tb);

nla_info_failure:
	nla_nest_cancel(skb, mrp_tb);

	वापस -EMSGSIZE;
पूर्ण

पूर्णांक br_mrp_ring_port_खोलो(काष्ठा net_device *dev, u8 loc)
अणु
	काष्ठा net_bridge_port *p;
	पूर्णांक err = 0;

	p = br_port_get_rcu(dev);
	अगर (!p) अणु
		err = -EINVAL;
		जाओ out;
	पूर्ण

	अगर (loc)
		p->flags |= BR_MRP_LOST_CONT;
	अन्यथा
		p->flags &= ~BR_MRP_LOST_CONT;

	br_अगरinfo_notअगरy(RTM_NEWLINK, शून्य, p);

out:
	वापस err;
पूर्ण

पूर्णांक br_mrp_in_port_खोलो(काष्ठा net_device *dev, u8 loc)
अणु
	काष्ठा net_bridge_port *p;
	पूर्णांक err = 0;

	p = br_port_get_rcu(dev);
	अगर (!p) अणु
		err = -EINVAL;
		जाओ out;
	पूर्ण

	अगर (loc)
		p->flags |= BR_MRP_LOST_IN_CONT;
	अन्यथा
		p->flags &= ~BR_MRP_LOST_IN_CONT;

	br_अगरinfo_notअगरy(RTM_NEWLINK, शून्य, p);

out:
	वापस err;
पूर्ण
