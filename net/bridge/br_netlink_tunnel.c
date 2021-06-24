<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *	Bridge per vlan tunnel port dst_metadata netlink control पूर्णांकerface
 *
 *	Authors:
 *	Roopa Prabhu		<roopa@cumulusnetworks.com>
 */

#समावेश <linux/kernel.h>
#समावेश <linux/slab.h>
#समावेश <linux/etherdevice.h>
#समावेश <net/rtnetlink.h>
#समावेश <net/net_namespace.h>
#समावेश <net/sock.h>
#समावेश <uapi/linux/अगर_bridge.h>
#समावेश <net/dst_metadata.h>

#समावेश "br_private.h"
#समावेश "br_private_tunnel.h"

अटल माप_प्रकार __get_vlan_tinfo_size(व्योम)
अणु
	वापस nla_total_size(0) + /* nest IFLA_BRIDGE_VLAN_TUNNEL_INFO */
		  nla_total_size(माप(u32)) + /* IFLA_BRIDGE_VLAN_TUNNEL_ID */
		  nla_total_size(माप(u16)) + /* IFLA_BRIDGE_VLAN_TUNNEL_VID */
		  nla_total_size(माप(u16)); /* IFLA_BRIDGE_VLAN_TUNNEL_FLAGS */
पूर्ण

bool vlan_tunid_inrange(स्थिर काष्ठा net_bridge_vlan *v_curr,
			स्थिर काष्ठा net_bridge_vlan *v_last)
अणु
	__be32 tunid_curr = tunnel_id_to_key32(v_curr->tinfo.tunnel_id);
	__be32 tunid_last = tunnel_id_to_key32(v_last->tinfo.tunnel_id);

	वापस (be32_to_cpu(tunid_curr) - be32_to_cpu(tunid_last)) == 1;
पूर्ण

अटल पूर्णांक __get_num_vlan_tunnel_infos(काष्ठा net_bridge_vlan_group *vg)
अणु
	काष्ठा net_bridge_vlan *v, *vtbegin = शून्य, *vtend = शून्य;
	पूर्णांक num_tinfos = 0;

	/* Count number of vlan infos */
	list_क्रम_each_entry_rcu(v, &vg->vlan_list, vlist) अणु
		/* only a context, bridge vlan not activated */
		अगर (!br_vlan_should_use(v) || !v->tinfo.tunnel_id)
			जारी;

		अगर (!vtbegin) अणु
			जाओ initvars;
		पूर्ण अन्यथा अगर ((v->vid - vtend->vid) == 1 &&
			   vlan_tunid_inrange(v, vtend)) अणु
			vtend = v;
			जारी;
		पूर्ण अन्यथा अणु
			अगर ((vtend->vid - vtbegin->vid) > 0)
				num_tinfos += 2;
			अन्यथा
				num_tinfos += 1;
		पूर्ण
initvars:
		vtbegin = v;
		vtend = v;
	पूर्ण

	अगर (vtbegin && vtend) अणु
		अगर ((vtend->vid - vtbegin->vid) > 0)
			num_tinfos += 2;
		अन्यथा
			num_tinfos += 1;
	पूर्ण

	वापस num_tinfos;
पूर्ण

पूर्णांक br_get_vlan_tunnel_info_size(काष्ठा net_bridge_vlan_group *vg)
अणु
	पूर्णांक num_tinfos;

	अगर (!vg)
		वापस 0;

	rcu_पढ़ो_lock();
	num_tinfos = __get_num_vlan_tunnel_infos(vg);
	rcu_पढ़ो_unlock();

	वापस num_tinfos * __get_vlan_tinfo_size();
पूर्ण

अटल पूर्णांक br_fill_vlan_tinfo(काष्ठा sk_buff *skb, u16 vid,
			      __be64 tunnel_id, u16 flags)
अणु
	__be32 tid = tunnel_id_to_key32(tunnel_id);
	काष्ठा nlattr *पंचांगap;

	पंचांगap = nla_nest_start_noflag(skb, IFLA_BRIDGE_VLAN_TUNNEL_INFO);
	अगर (!पंचांगap)
		वापस -EMSGSIZE;
	अगर (nla_put_u32(skb, IFLA_BRIDGE_VLAN_TUNNEL_ID,
			be32_to_cpu(tid)))
		जाओ nla_put_failure;
	अगर (nla_put_u16(skb, IFLA_BRIDGE_VLAN_TUNNEL_VID,
			vid))
		जाओ nla_put_failure;
	अगर (nla_put_u16(skb, IFLA_BRIDGE_VLAN_TUNNEL_FLAGS,
			flags))
		जाओ nla_put_failure;
	nla_nest_end(skb, पंचांगap);

	वापस 0;

nla_put_failure:
	nla_nest_cancel(skb, पंचांगap);

	वापस -EMSGSIZE;
पूर्ण

अटल पूर्णांक br_fill_vlan_tinfo_range(काष्ठा sk_buff *skb,
				    काष्ठा net_bridge_vlan *vtbegin,
				    काष्ठा net_bridge_vlan *vtend)
अणु
	पूर्णांक err;

	अगर (vtend && (vtend->vid - vtbegin->vid) > 0) अणु
		/* add range to skb */
		err = br_fill_vlan_tinfo(skb, vtbegin->vid,
					 vtbegin->tinfo.tunnel_id,
					 BRIDGE_VLAN_INFO_RANGE_BEGIN);
		अगर (err)
			वापस err;

		err = br_fill_vlan_tinfo(skb, vtend->vid,
					 vtend->tinfo.tunnel_id,
					 BRIDGE_VLAN_INFO_RANGE_END);
		अगर (err)
			वापस err;
	पूर्ण अन्यथा अणु
		err = br_fill_vlan_tinfo(skb, vtbegin->vid,
					 vtbegin->tinfo.tunnel_id,
					 0);
		अगर (err)
			वापस err;
	पूर्ण

	वापस 0;
पूर्ण

पूर्णांक br_fill_vlan_tunnel_info(काष्ठा sk_buff *skb,
			     काष्ठा net_bridge_vlan_group *vg)
अणु
	काष्ठा net_bridge_vlan *vtbegin = शून्य;
	काष्ठा net_bridge_vlan *vtend = शून्य;
	काष्ठा net_bridge_vlan *v;
	पूर्णांक err;

	/* Count number of vlan infos */
	list_क्रम_each_entry_rcu(v, &vg->vlan_list, vlist) अणु
		/* only a context, bridge vlan not activated */
		अगर (!br_vlan_should_use(v))
			जारी;

		अगर (!v->tinfo.tunnel_dst)
			जारी;

		अगर (!vtbegin) अणु
			जाओ initvars;
		पूर्ण अन्यथा अगर ((v->vid - vtend->vid) == 1 &&
			    vlan_tunid_inrange(v, vtend)) अणु
			vtend = v;
			जारी;
		पूर्ण अन्यथा अणु
			err = br_fill_vlan_tinfo_range(skb, vtbegin, vtend);
			अगर (err)
				वापस err;
		पूर्ण
initvars:
		vtbegin = v;
		vtend = v;
	पूर्ण

	अगर (vtbegin) अणु
		err = br_fill_vlan_tinfo_range(skb, vtbegin, vtend);
		अगर (err)
			वापस err;
	पूर्ण

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा nla_policy vlan_tunnel_policy[IFLA_BRIDGE_VLAN_TUNNEL_MAX + 1] = अणु
	[IFLA_BRIDGE_VLAN_TUNNEL_ID] = अणु .type = NLA_U32 पूर्ण,
	[IFLA_BRIDGE_VLAN_TUNNEL_VID] = अणु .type = NLA_U16 पूर्ण,
	[IFLA_BRIDGE_VLAN_TUNNEL_FLAGS] = अणु .type = NLA_U16 पूर्ण,
पूर्ण;

पूर्णांक br_vlan_tunnel_info(स्थिर काष्ठा net_bridge_port *p, पूर्णांक cmd,
			u16 vid, u32 tun_id, bool *changed)
अणु
	पूर्णांक err = 0;

	अगर (!p)
		वापस -EINVAL;

	चयन (cmd) अणु
	हाल RTM_SETLINK:
		err = nbp_vlan_tunnel_info_add(p, vid, tun_id);
		अगर (!err)
			*changed = true;
		अवरोध;
	हाल RTM_DELLINK:
		अगर (!nbp_vlan_tunnel_info_delete(p, vid))
			*changed = true;
		अवरोध;
	पूर्ण

	वापस err;
पूर्ण

पूर्णांक br_parse_vlan_tunnel_info(काष्ठा nlattr *attr,
			      काष्ठा vtunnel_info *tinfo)
अणु
	काष्ठा nlattr *tb[IFLA_BRIDGE_VLAN_TUNNEL_MAX + 1];
	u32 tun_id;
	u16 vid, flags = 0;
	पूर्णांक err;

	स_रखो(tinfo, 0, माप(*tinfo));

	err = nla_parse_nested_deprecated(tb, IFLA_BRIDGE_VLAN_TUNNEL_MAX,
					  attr, vlan_tunnel_policy, शून्य);
	अगर (err < 0)
		वापस err;

	अगर (!tb[IFLA_BRIDGE_VLAN_TUNNEL_ID] ||
	    !tb[IFLA_BRIDGE_VLAN_TUNNEL_VID])
		वापस -EINVAL;

	tun_id = nla_get_u32(tb[IFLA_BRIDGE_VLAN_TUNNEL_ID]);
	vid = nla_get_u16(tb[IFLA_BRIDGE_VLAN_TUNNEL_VID]);
	अगर (vid >= VLAN_VID_MASK)
		वापस -दुस्फल;

	अगर (tb[IFLA_BRIDGE_VLAN_TUNNEL_FLAGS])
		flags = nla_get_u16(tb[IFLA_BRIDGE_VLAN_TUNNEL_FLAGS]);

	tinfo->tunid = tun_id;
	tinfo->vid = vid;
	tinfo->flags = flags;

	वापस 0;
पूर्ण

/* send a notअगरication अगर v_curr can't enter the range and start a new one */
अटल व्योम __vlan_tunnel_handle_range(स्थिर काष्ठा net_bridge_port *p,
				       काष्ठा net_bridge_vlan **v_start,
				       काष्ठा net_bridge_vlan **v_end,
				       पूर्णांक v_curr, bool curr_change)
अणु
	काष्ठा net_bridge_vlan_group *vg;
	काष्ठा net_bridge_vlan *v;

	vg = nbp_vlan_group(p);
	अगर (!vg)
		वापस;

	v = br_vlan_find(vg, v_curr);

	अगर (!*v_start)
		जाओ out_init;

	अगर (v && curr_change && br_vlan_can_enter_range(v, *v_end)) अणु
		*v_end = v;
		वापस;
	पूर्ण

	br_vlan_notअगरy(p->br, p, (*v_start)->vid, (*v_end)->vid, RTM_NEWVLAN);
out_init:
	/* we start a range only अगर there are any changes to notअगरy about */
	*v_start = curr_change ? v : शून्य;
	*v_end = *v_start;
पूर्ण

पूर्णांक br_process_vlan_tunnel_info(स्थिर काष्ठा net_bridge *br,
				स्थिर काष्ठा net_bridge_port *p, पूर्णांक cmd,
				काष्ठा vtunnel_info *tinfo_curr,
				काष्ठा vtunnel_info *tinfo_last,
				bool *changed)
अणु
	पूर्णांक err;

	अगर (tinfo_curr->flags & BRIDGE_VLAN_INFO_RANGE_BEGIN) अणु
		अगर (tinfo_last->flags & BRIDGE_VLAN_INFO_RANGE_BEGIN)
			वापस -EINVAL;
		स_नकल(tinfo_last, tinfo_curr, माप(काष्ठा vtunnel_info));
	पूर्ण अन्यथा अगर (tinfo_curr->flags & BRIDGE_VLAN_INFO_RANGE_END) अणु
		काष्ठा net_bridge_vlan *v_start = शून्य, *v_end = शून्य;
		पूर्णांक t, v;

		अगर (!(tinfo_last->flags & BRIDGE_VLAN_INFO_RANGE_BEGIN))
			वापस -EINVAL;
		अगर ((tinfo_curr->vid - tinfo_last->vid) !=
		    (tinfo_curr->tunid - tinfo_last->tunid))
			वापस -EINVAL;
		t = tinfo_last->tunid;
		क्रम (v = tinfo_last->vid; v <= tinfo_curr->vid; v++) अणु
			bool curr_change = false;

			err = br_vlan_tunnel_info(p, cmd, v, t, &curr_change);
			अगर (err)
				अवरोध;
			t++;

			अगर (curr_change)
				*changed = curr_change;
			 __vlan_tunnel_handle_range(p, &v_start, &v_end, v,
						    curr_change);
		पूर्ण
		अगर (v_start && v_end)
			br_vlan_notअगरy(br, p, v_start->vid, v_end->vid,
				       RTM_NEWVLAN);
		अगर (err)
			वापस err;

		स_रखो(tinfo_last, 0, माप(काष्ठा vtunnel_info));
		स_रखो(tinfo_curr, 0, माप(काष्ठा vtunnel_info));
	पूर्ण अन्यथा अणु
		अगर (tinfo_last->flags)
			वापस -EINVAL;
		err = br_vlan_tunnel_info(p, cmd, tinfo_curr->vid,
					  tinfo_curr->tunid, changed);
		अगर (err)
			वापस err;
		br_vlan_notअगरy(br, p, tinfo_curr->vid, 0, RTM_NEWVLAN);
		स_रखो(tinfo_last, 0, माप(काष्ठा vtunnel_info));
		स_रखो(tinfo_curr, 0, माप(काष्ठा vtunnel_info));
	पूर्ण

	वापस 0;
पूर्ण
