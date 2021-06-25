<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *	Bridge per vlan tunnel port dst_metadata handling code
 *
 *	Authors:
 *	Roopa Prabhu		<roopa@cumulusnetworks.com>
 */

#समावेश <linux/kernel.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/rtnetlink.h>
#समावेश <linux/slab.h>
#समावेश <net/चयनdev.h>
#समावेश <net/dst_metadata.h>

#समावेश "br_private.h"
#समावेश "br_private_tunnel.h"

अटल अंतरभूत पूर्णांक br_vlan_tunid_cmp(काष्ठा rhashtable_compare_arg *arg,
				    स्थिर व्योम *ptr)
अणु
	स्थिर काष्ठा net_bridge_vlan *vle = ptr;
	__be64 tunid = *(__be64 *)arg->key;

	वापस vle->tinfo.tunnel_id != tunid;
पूर्ण

अटल स्थिर काष्ठा rhashtable_params br_vlan_tunnel_rht_params = अणु
	.head_offset = दुरत्व(काष्ठा net_bridge_vlan, tnode),
	.key_offset = दुरत्व(काष्ठा net_bridge_vlan, tinfo.tunnel_id),
	.key_len = माप(__be64),
	.nelem_hपूर्णांक = 3,
	.obj_cmpfn = br_vlan_tunid_cmp,
	.स्वतःmatic_shrinking = true,
पूर्ण;

अटल काष्ठा net_bridge_vlan *br_vlan_tunnel_lookup(काष्ठा rhashtable *tbl,
						     __be64 tunnel_id)
अणु
	वापस rhashtable_lookup_fast(tbl, &tunnel_id,
				      br_vlan_tunnel_rht_params);
पूर्ण

अटल व्योम vlan_tunnel_info_release(काष्ठा net_bridge_vlan *vlan)
अणु
	काष्ठा metadata_dst *tdst = rtnl_dereference(vlan->tinfo.tunnel_dst);

	WRITE_ONCE(vlan->tinfo.tunnel_id, 0);
	RCU_INIT_POINTER(vlan->tinfo.tunnel_dst, शून्य);
	dst_release(&tdst->dst);
पूर्ण

व्योम vlan_tunnel_info_del(काष्ठा net_bridge_vlan_group *vg,
			  काष्ठा net_bridge_vlan *vlan)
अणु
	अगर (!rcu_access_poपूर्णांकer(vlan->tinfo.tunnel_dst))
		वापस;
	rhashtable_हटाओ_fast(&vg->tunnel_hash, &vlan->tnode,
			       br_vlan_tunnel_rht_params);
	vlan_tunnel_info_release(vlan);
पूर्ण

अटल पूर्णांक __vlan_tunnel_info_add(काष्ठा net_bridge_vlan_group *vg,
				  काष्ठा net_bridge_vlan *vlan, u32 tun_id)
अणु
	काष्ठा metadata_dst *metadata = rtnl_dereference(vlan->tinfo.tunnel_dst);
	__be64 key = key32_to_tunnel_id(cpu_to_be32(tun_id));
	पूर्णांक err;

	अगर (metadata)
		वापस -EEXIST;

	metadata = __ip_tun_set_dst(0, 0, 0, 0, 0, TUNNEL_KEY,
				    key, 0);
	अगर (!metadata)
		वापस -EINVAL;

	metadata->u.tun_info.mode |= IP_TUNNEL_INFO_TX | IP_TUNNEL_INFO_BRIDGE;
	rcu_assign_poपूर्णांकer(vlan->tinfo.tunnel_dst, metadata);
	WRITE_ONCE(vlan->tinfo.tunnel_id, key);

	err = rhashtable_lookup_insert_fast(&vg->tunnel_hash, &vlan->tnode,
					    br_vlan_tunnel_rht_params);
	अगर (err)
		जाओ out;

	वापस 0;
out:
	vlan_tunnel_info_release(vlan);

	वापस err;
पूर्ण

/* Must be रक्षित by RTNL.
 * Must be called with vid in range from 1 to 4094 inclusive.
 */
पूर्णांक nbp_vlan_tunnel_info_add(स्थिर काष्ठा net_bridge_port *port, u16 vid,
			     u32 tun_id)
अणु
	काष्ठा net_bridge_vlan_group *vg;
	काष्ठा net_bridge_vlan *vlan;

	ASSERT_RTNL();

	vg = nbp_vlan_group(port);
	vlan = br_vlan_find(vg, vid);
	अगर (!vlan)
		वापस -EINVAL;

	वापस __vlan_tunnel_info_add(vg, vlan, tun_id);
पूर्ण

/* Must be रक्षित by RTNL.
 * Must be called with vid in range from 1 to 4094 inclusive.
 */
पूर्णांक nbp_vlan_tunnel_info_delete(स्थिर काष्ठा net_bridge_port *port, u16 vid)
अणु
	काष्ठा net_bridge_vlan_group *vg;
	काष्ठा net_bridge_vlan *v;

	ASSERT_RTNL();

	vg = nbp_vlan_group(port);
	v = br_vlan_find(vg, vid);
	अगर (!v)
		वापस -ENOENT;

	vlan_tunnel_info_del(vg, v);

	वापस 0;
पूर्ण

अटल व्योम __vlan_tunnel_info_flush(काष्ठा net_bridge_vlan_group *vg)
अणु
	काष्ठा net_bridge_vlan *vlan, *पंचांगp;

	list_क्रम_each_entry_safe(vlan, पंचांगp, &vg->vlan_list, vlist)
		vlan_tunnel_info_del(vg, vlan);
पूर्ण

व्योम nbp_vlan_tunnel_info_flush(काष्ठा net_bridge_port *port)
अणु
	काष्ठा net_bridge_vlan_group *vg;

	ASSERT_RTNL();

	vg = nbp_vlan_group(port);
	__vlan_tunnel_info_flush(vg);
पूर्ण

पूर्णांक vlan_tunnel_init(काष्ठा net_bridge_vlan_group *vg)
अणु
	वापस rhashtable_init(&vg->tunnel_hash, &br_vlan_tunnel_rht_params);
पूर्ण

व्योम vlan_tunnel_deinit(काष्ठा net_bridge_vlan_group *vg)
अणु
	rhashtable_destroy(&vg->tunnel_hash);
पूर्ण

पूर्णांक br_handle_ingress_vlan_tunnel(काष्ठा sk_buff *skb,
				  काष्ठा net_bridge_port *p,
				  काष्ठा net_bridge_vlan_group *vg)
अणु
	काष्ठा ip_tunnel_info *tinfo = skb_tunnel_info(skb);
	काष्ठा net_bridge_vlan *vlan;

	अगर (!vg || !tinfo)
		वापस 0;

	/* अगर alपढ़ोy tagged, ignore */
	अगर (skb_vlan_tagged(skb))
		वापस 0;

	/* lookup vid, given tunnel id */
	vlan = br_vlan_tunnel_lookup(&vg->tunnel_hash, tinfo->key.tun_id);
	अगर (!vlan)
		वापस 0;

	skb_dst_drop(skb);

	__vlan_hwaccel_put_tag(skb, p->br->vlan_proto, vlan->vid);

	वापस 0;
पूर्ण

पूर्णांक br_handle_egress_vlan_tunnel(काष्ठा sk_buff *skb,
				 काष्ठा net_bridge_vlan *vlan)
अणु
	काष्ठा metadata_dst *tunnel_dst;
	__be64 tunnel_id;
	पूर्णांक err;

	अगर (!vlan)
		वापस 0;

	tunnel_id = READ_ONCE(vlan->tinfo.tunnel_id);
	अगर (!tunnel_id || unlikely(!skb_vlan_tag_present(skb)))
		वापस 0;

	skb_dst_drop(skb);
	err = skb_vlan_pop(skb);
	अगर (err)
		वापस err;

	tunnel_dst = rcu_dereference(vlan->tinfo.tunnel_dst);
	अगर (tunnel_dst && dst_hold_safe(&tunnel_dst->dst))
		skb_dst_set(skb, &tunnel_dst->dst);

	वापस 0;
पूर्ण
