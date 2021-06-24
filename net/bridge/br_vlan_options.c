<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
// Copyright (c) 2020, Nikolay Aleksandrov <nikolay@cumulusnetworks.com>
#समावेश <linux/kernel.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/rtnetlink.h>
#समावेश <linux/slab.h>
#समावेश <net/ip_tunnels.h>

#समावेश "br_private.h"
#समावेश "br_private_tunnel.h"

अटल bool __vlan_tun_put(काष्ठा sk_buff *skb, स्थिर काष्ठा net_bridge_vlan *v)
अणु
	__be32 tid = tunnel_id_to_key32(v->tinfo.tunnel_id);
	काष्ठा nlattr *nest;

	अगर (!v->tinfo.tunnel_dst)
		वापस true;

	nest = nla_nest_start(skb, BRIDGE_VLANDB_ENTRY_TUNNEL_INFO);
	अगर (!nest)
		वापस false;
	अगर (nla_put_u32(skb, BRIDGE_VLANDB_TINFO_ID, be32_to_cpu(tid))) अणु
		nla_nest_cancel(skb, nest);
		वापस false;
	पूर्ण
	nla_nest_end(skb, nest);

	वापस true;
पूर्ण

अटल bool __vlan_tun_can_enter_range(स्थिर काष्ठा net_bridge_vlan *v_curr,
				       स्थिर काष्ठा net_bridge_vlan *range_end)
अणु
	वापस (!v_curr->tinfo.tunnel_dst && !range_end->tinfo.tunnel_dst) ||
	       vlan_tunid_inrange(v_curr, range_end);
पूर्ण

/* check अगर the options' state of v_curr allow it to enter the range */
bool br_vlan_opts_eq_range(स्थिर काष्ठा net_bridge_vlan *v_curr,
			   स्थिर काष्ठा net_bridge_vlan *range_end)
अणु
	वापस v_curr->state == range_end->state &&
	       __vlan_tun_can_enter_range(v_curr, range_end);
पूर्ण

bool br_vlan_opts_fill(काष्ठा sk_buff *skb, स्थिर काष्ठा net_bridge_vlan *v)
अणु
	वापस !nla_put_u8(skb, BRIDGE_VLANDB_ENTRY_STATE,
			   br_vlan_get_state(v)) &&
	       __vlan_tun_put(skb, v);
पूर्ण

माप_प्रकार br_vlan_opts_nl_size(व्योम)
अणु
	वापस nla_total_size(माप(u8)) /* BRIDGE_VLANDB_ENTRY_STATE */
	       + nla_total_size(0) /* BRIDGE_VLANDB_ENTRY_TUNNEL_INFO */
	       + nla_total_size(माप(u32)); /* BRIDGE_VLANDB_TINFO_ID */
पूर्ण

अटल पूर्णांक br_vlan_modअगरy_state(काष्ठा net_bridge_vlan_group *vg,
				काष्ठा net_bridge_vlan *v,
				u8 state,
				bool *changed,
				काष्ठा netlink_ext_ack *extack)
अणु
	काष्ठा net_bridge *br;

	ASSERT_RTNL();

	अगर (state > BR_STATE_BLOCKING) अणु
		NL_SET_ERR_MSG_MOD(extack, "Invalid vlan state");
		वापस -EINVAL;
	पूर्ण

	अगर (br_vlan_is_brentry(v))
		br = v->br;
	अन्यथा
		br = v->port->br;

	अगर (br->stp_enabled == BR_KERNEL_STP) अणु
		NL_SET_ERR_MSG_MOD(extack, "Can't modify vlan state when using kernel STP");
		वापस -EBUSY;
	पूर्ण

	अगर (v->state == state)
		वापस 0;

	अगर (v->vid == br_get_pvid(vg))
		br_vlan_set_pvid_state(vg, state);

	br_vlan_set_state(v, state);
	*changed = true;

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा nla_policy br_vlandb_tinfo_pol[BRIDGE_VLANDB_TINFO_MAX + 1] = अणु
	[BRIDGE_VLANDB_TINFO_ID]	= अणु .type = NLA_U32 पूर्ण,
	[BRIDGE_VLANDB_TINFO_CMD]	= अणु .type = NLA_U32 पूर्ण,
पूर्ण;

अटल पूर्णांक br_vlan_modअगरy_tunnel(स्थिर काष्ठा net_bridge_port *p,
				 काष्ठा net_bridge_vlan *v,
				 काष्ठा nlattr **tb,
				 bool *changed,
				 काष्ठा netlink_ext_ack *extack)
अणु
	काष्ठा nlattr *tun_tb[BRIDGE_VLANDB_TINFO_MAX + 1], *attr;
	काष्ठा bridge_vlan_info *vinfo;
	u32 tun_id = 0;
	पूर्णांक cmd, err;

	अगर (!p) अणु
		NL_SET_ERR_MSG_MOD(extack, "Can't modify tunnel mapping of non-port vlans");
		वापस -EINVAL;
	पूर्ण
	अगर (!(p->flags & BR_VLAN_TUNNEL)) अणु
		NL_SET_ERR_MSG_MOD(extack, "Port doesn't have tunnel flag set");
		वापस -EINVAL;
	पूर्ण

	attr = tb[BRIDGE_VLANDB_ENTRY_TUNNEL_INFO];
	err = nla_parse_nested(tun_tb, BRIDGE_VLANDB_TINFO_MAX, attr,
			       br_vlandb_tinfo_pol, extack);
	अगर (err)
		वापस err;

	अगर (!tun_tb[BRIDGE_VLANDB_TINFO_CMD]) अणु
		NL_SET_ERR_MSG_MOD(extack, "Missing tunnel command attribute");
		वापस -ENOENT;
	पूर्ण
	cmd = nla_get_u32(tun_tb[BRIDGE_VLANDB_TINFO_CMD]);
	चयन (cmd) अणु
	हाल RTM_SETLINK:
		अगर (!tun_tb[BRIDGE_VLANDB_TINFO_ID]) अणु
			NL_SET_ERR_MSG_MOD(extack, "Missing tunnel id attribute");
			वापस -ENOENT;
		पूर्ण
		/* when working on vlan ranges this is the starting tunnel id */
		tun_id = nla_get_u32(tun_tb[BRIDGE_VLANDB_TINFO_ID]);
		/* vlan info attr is guaranteed by br_vlan_rपंचांग_process_one */
		vinfo = nla_data(tb[BRIDGE_VLANDB_ENTRY_INFO]);
		/* tunnel ids are mapped to each vlan in increasing order,
		 * the starting vlan is in BRIDGE_VLANDB_ENTRY_INFO and v is the
		 * current vlan, so we compute: tun_id + v - vinfo->vid
		 */
		tun_id += v->vid - vinfo->vid;
		अवरोध;
	हाल RTM_DELLINK:
		अवरोध;
	शेष:
		NL_SET_ERR_MSG_MOD(extack, "Unsupported tunnel command");
		वापस -EINVAL;
	पूर्ण

	वापस br_vlan_tunnel_info(p, cmd, v->vid, tun_id, changed);
पूर्ण

अटल पूर्णांक br_vlan_process_one_opts(स्थिर काष्ठा net_bridge *br,
				    स्थिर काष्ठा net_bridge_port *p,
				    काष्ठा net_bridge_vlan_group *vg,
				    काष्ठा net_bridge_vlan *v,
				    काष्ठा nlattr **tb,
				    bool *changed,
				    काष्ठा netlink_ext_ack *extack)
अणु
	पूर्णांक err;

	*changed = false;
	अगर (tb[BRIDGE_VLANDB_ENTRY_STATE]) अणु
		u8 state = nla_get_u8(tb[BRIDGE_VLANDB_ENTRY_STATE]);

		err = br_vlan_modअगरy_state(vg, v, state, changed, extack);
		अगर (err)
			वापस err;
	पूर्ण
	अगर (tb[BRIDGE_VLANDB_ENTRY_TUNNEL_INFO]) अणु
		err = br_vlan_modअगरy_tunnel(p, v, tb, changed, extack);
		अगर (err)
			वापस err;
	पूर्ण

	वापस 0;
पूर्ण

पूर्णांक br_vlan_process_options(स्थिर काष्ठा net_bridge *br,
			    स्थिर काष्ठा net_bridge_port *p,
			    काष्ठा net_bridge_vlan *range_start,
			    काष्ठा net_bridge_vlan *range_end,
			    काष्ठा nlattr **tb,
			    काष्ठा netlink_ext_ack *extack)
अणु
	काष्ठा net_bridge_vlan *v, *curr_start = शून्य, *curr_end = शून्य;
	काष्ठा net_bridge_vlan_group *vg;
	पूर्णांक vid, err = 0;
	u16 pvid;

	अगर (p)
		vg = nbp_vlan_group(p);
	अन्यथा
		vg = br_vlan_group(br);

	अगर (!range_start || !br_vlan_should_use(range_start)) अणु
		NL_SET_ERR_MSG_MOD(extack, "Vlan range start doesn't exist, can't process options");
		वापस -ENOENT;
	पूर्ण
	अगर (!range_end || !br_vlan_should_use(range_end)) अणु
		NL_SET_ERR_MSG_MOD(extack, "Vlan range end doesn't exist, can't process options");
		वापस -ENOENT;
	पूर्ण

	pvid = br_get_pvid(vg);
	क्रम (vid = range_start->vid; vid <= range_end->vid; vid++) अणु
		bool changed = false;

		v = br_vlan_find(vg, vid);
		अगर (!v || !br_vlan_should_use(v)) अणु
			NL_SET_ERR_MSG_MOD(extack, "Vlan in range doesn't exist, can't process options");
			err = -ENOENT;
			अवरोध;
		पूर्ण

		err = br_vlan_process_one_opts(br, p, vg, v, tb, &changed,
					       extack);
		अगर (err)
			अवरोध;

		अगर (changed) अणु
			/* vlan options changed, check क्रम range */
			अगर (!curr_start) अणु
				curr_start = v;
				curr_end = v;
				जारी;
			पूर्ण

			अगर (v->vid == pvid ||
			    !br_vlan_can_enter_range(v, curr_end)) अणु
				br_vlan_notअगरy(br, p, curr_start->vid,
					       curr_end->vid, RTM_NEWVLAN);
				curr_start = v;
			पूर्ण
			curr_end = v;
		पूर्ण अन्यथा अणु
			/* nothing changed and nothing to notअगरy yet */
			अगर (!curr_start)
				जारी;

			br_vlan_notअगरy(br, p, curr_start->vid, curr_end->vid,
				       RTM_NEWVLAN);
			curr_start = शून्य;
			curr_end = शून्य;
		पूर्ण
	पूर्ण
	अगर (curr_start)
		br_vlan_notअगरy(br, p, curr_start->vid, curr_end->vid,
			       RTM_NEWVLAN);

	वापस err;
पूर्ण
