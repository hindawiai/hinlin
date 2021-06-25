<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
#समावेश <linux/kernel.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/rtnetlink.h>
#समावेश <linux/slab.h>
#समावेश <net/चयनdev.h>

#समावेश "br_private.h"
#समावेश "br_private_tunnel.h"

अटल व्योम nbp_vlan_set_vlan_dev_state(काष्ठा net_bridge_port *p, u16 vid);

अटल अंतरभूत पूर्णांक br_vlan_cmp(काष्ठा rhashtable_compare_arg *arg,
			      स्थिर व्योम *ptr)
अणु
	स्थिर काष्ठा net_bridge_vlan *vle = ptr;
	u16 vid = *(u16 *)arg->key;

	वापस vle->vid != vid;
पूर्ण

अटल स्थिर काष्ठा rhashtable_params br_vlan_rht_params = अणु
	.head_offset = दुरत्व(काष्ठा net_bridge_vlan, vnode),
	.key_offset = दुरत्व(काष्ठा net_bridge_vlan, vid),
	.key_len = माप(u16),
	.nelem_hपूर्णांक = 3,
	.max_size = VLAN_N_VID,
	.obj_cmpfn = br_vlan_cmp,
	.स्वतःmatic_shrinking = true,
पूर्ण;

अटल काष्ठा net_bridge_vlan *br_vlan_lookup(काष्ठा rhashtable *tbl, u16 vid)
अणु
	वापस rhashtable_lookup_fast(tbl, &vid, br_vlan_rht_params);
पूर्ण

अटल bool __vlan_add_pvid(काष्ठा net_bridge_vlan_group *vg,
			    स्थिर काष्ठा net_bridge_vlan *v)
अणु
	अगर (vg->pvid == v->vid)
		वापस false;

	smp_wmb();
	br_vlan_set_pvid_state(vg, v->state);
	vg->pvid = v->vid;

	वापस true;
पूर्ण

अटल bool __vlan_delete_pvid(काष्ठा net_bridge_vlan_group *vg, u16 vid)
अणु
	अगर (vg->pvid != vid)
		वापस false;

	smp_wmb();
	vg->pvid = 0;

	वापस true;
पूर्ण

/* वापस true अगर anything changed, false otherwise */
अटल bool __vlan_add_flags(काष्ठा net_bridge_vlan *v, u16 flags)
अणु
	काष्ठा net_bridge_vlan_group *vg;
	u16 old_flags = v->flags;
	bool ret;

	अगर (br_vlan_is_master(v))
		vg = br_vlan_group(v->br);
	अन्यथा
		vg = nbp_vlan_group(v->port);

	अगर (flags & BRIDGE_VLAN_INFO_PVID)
		ret = __vlan_add_pvid(vg, v);
	अन्यथा
		ret = __vlan_delete_pvid(vg, v->vid);

	अगर (flags & BRIDGE_VLAN_INFO_UNTAGGED)
		v->flags |= BRIDGE_VLAN_INFO_UNTAGGED;
	अन्यथा
		v->flags &= ~BRIDGE_VLAN_INFO_UNTAGGED;

	वापस ret || !!(old_flags ^ v->flags);
पूर्ण

अटल पूर्णांक __vlan_vid_add(काष्ठा net_device *dev, काष्ठा net_bridge *br,
			  काष्ठा net_bridge_vlan *v, u16 flags,
			  काष्ठा netlink_ext_ack *extack)
अणु
	पूर्णांक err;

	/* Try चयनdev op first. In हाल it is not supported, fallback to
	 * 8021q add.
	 */
	err = br_चयनdev_port_vlan_add(dev, v->vid, flags, extack);
	अगर (err == -EOPNOTSUPP)
		वापस vlan_vid_add(dev, br->vlan_proto, v->vid);
	v->priv_flags |= BR_VLFLAG_ADDED_BY_SWITCHDEV;
	वापस err;
पूर्ण

अटल व्योम __vlan_add_list(काष्ठा net_bridge_vlan *v)
अणु
	काष्ठा net_bridge_vlan_group *vg;
	काष्ठा list_head *headp, *hpos;
	काष्ठा net_bridge_vlan *vent;

	अगर (br_vlan_is_master(v))
		vg = br_vlan_group(v->br);
	अन्यथा
		vg = nbp_vlan_group(v->port);

	headp = &vg->vlan_list;
	list_क्रम_each_prev(hpos, headp) अणु
		vent = list_entry(hpos, काष्ठा net_bridge_vlan, vlist);
		अगर (v->vid < vent->vid)
			जारी;
		अन्यथा
			अवरोध;
	पूर्ण
	list_add_rcu(&v->vlist, hpos);
पूर्ण

अटल व्योम __vlan_del_list(काष्ठा net_bridge_vlan *v)
अणु
	list_del_rcu(&v->vlist);
पूर्ण

अटल पूर्णांक __vlan_vid_del(काष्ठा net_device *dev, काष्ठा net_bridge *br,
			  स्थिर काष्ठा net_bridge_vlan *v)
अणु
	पूर्णांक err;

	/* Try चयनdev op first. In हाल it is not supported, fallback to
	 * 8021q del.
	 */
	err = br_चयनdev_port_vlan_del(dev, v->vid);
	अगर (!(v->priv_flags & BR_VLFLAG_ADDED_BY_SWITCHDEV))
		vlan_vid_del(dev, br->vlan_proto, v->vid);
	वापस err == -EOPNOTSUPP ? 0 : err;
पूर्ण

/* Returns a master vlan, अगर it didn't exist it माला_लो created. In all हालs
 * a reference is taken to the master vlan beक्रमe वापसing.
 */
अटल काष्ठा net_bridge_vlan *
br_vlan_get_master(काष्ठा net_bridge *br, u16 vid,
		   काष्ठा netlink_ext_ack *extack)
अणु
	काष्ठा net_bridge_vlan_group *vg;
	काष्ठा net_bridge_vlan *masterv;

	vg = br_vlan_group(br);
	masterv = br_vlan_find(vg, vid);
	अगर (!masterv) अणु
		bool changed;

		/* missing global ctx, create it now */
		अगर (br_vlan_add(br, vid, 0, &changed, extack))
			वापस शून्य;
		masterv = br_vlan_find(vg, vid);
		अगर (WARN_ON(!masterv))
			वापस शून्य;
		refcount_set(&masterv->refcnt, 1);
		वापस masterv;
	पूर्ण
	refcount_inc(&masterv->refcnt);

	वापस masterv;
पूर्ण

अटल व्योम br_master_vlan_rcu_मुक्त(काष्ठा rcu_head *rcu)
अणु
	काष्ठा net_bridge_vlan *v;

	v = container_of(rcu, काष्ठा net_bridge_vlan, rcu);
	WARN_ON(!br_vlan_is_master(v));
	मुक्त_percpu(v->stats);
	v->stats = शून्य;
	kमुक्त(v);
पूर्ण

अटल व्योम br_vlan_put_master(काष्ठा net_bridge_vlan *masterv)
अणु
	काष्ठा net_bridge_vlan_group *vg;

	अगर (!br_vlan_is_master(masterv))
		वापस;

	vg = br_vlan_group(masterv->br);
	अगर (refcount_dec_and_test(&masterv->refcnt)) अणु
		rhashtable_हटाओ_fast(&vg->vlan_hash,
				       &masterv->vnode, br_vlan_rht_params);
		__vlan_del_list(masterv);
		call_rcu(&masterv->rcu, br_master_vlan_rcu_मुक्त);
	पूर्ण
पूर्ण

अटल व्योम nbp_vlan_rcu_मुक्त(काष्ठा rcu_head *rcu)
अणु
	काष्ठा net_bridge_vlan *v;

	v = container_of(rcu, काष्ठा net_bridge_vlan, rcu);
	WARN_ON(br_vlan_is_master(v));
	/* अगर we had per-port stats configured then मुक्त them here */
	अगर (v->priv_flags & BR_VLFLAG_PER_PORT_STATS)
		मुक्त_percpu(v->stats);
	v->stats = शून्य;
	kमुक्त(v);
पूर्ण

/* This is the shared VLAN add function which works क्रम both ports and bridge
 * devices. There are four possible calls to this function in terms of the
 * vlan entry type:
 * 1. vlan is being added on a port (no master flags, global entry exists)
 * 2. vlan is being added on a bridge (both master and brentry flags)
 * 3. vlan is being added on a port, but a global entry didn't exist which
 *    is being created right now (master flag set, brentry flag unset), the
 *    global entry is used क्रम global per-vlan features, but not क्रम filtering
 * 4. same as 3 but with both master and brentry flags set so the entry
 *    will be used क्रम filtering in both the port and the bridge
 */
अटल पूर्णांक __vlan_add(काष्ठा net_bridge_vlan *v, u16 flags,
		      काष्ठा netlink_ext_ack *extack)
अणु
	काष्ठा net_bridge_vlan *masterv = शून्य;
	काष्ठा net_bridge_port *p = शून्य;
	काष्ठा net_bridge_vlan_group *vg;
	काष्ठा net_device *dev;
	काष्ठा net_bridge *br;
	पूर्णांक err;

	अगर (br_vlan_is_master(v)) अणु
		br = v->br;
		dev = br->dev;
		vg = br_vlan_group(br);
	पूर्ण अन्यथा अणु
		p = v->port;
		br = p->br;
		dev = p->dev;
		vg = nbp_vlan_group(p);
	पूर्ण

	अगर (p) अणु
		/* Add VLAN to the device filter अगर it is supported.
		 * This ensures tagged traffic enters the bridge when
		 * promiscuous mode is disabled by br_manage_promisc().
		 */
		err = __vlan_vid_add(dev, br, v, flags, extack);
		अगर (err)
			जाओ out;

		/* need to work on the master vlan too */
		अगर (flags & BRIDGE_VLAN_INFO_MASTER) अणु
			bool changed;

			err = br_vlan_add(br, v->vid,
					  flags | BRIDGE_VLAN_INFO_BRENTRY,
					  &changed, extack);
			अगर (err)
				जाओ out_filt;

			अगर (changed)
				br_vlan_notअगरy(br, शून्य, v->vid, 0,
					       RTM_NEWVLAN);
		पूर्ण

		masterv = br_vlan_get_master(br, v->vid, extack);
		अगर (!masterv) अणु
			err = -ENOMEM;
			जाओ out_filt;
		पूर्ण
		v->brvlan = masterv;
		अगर (br_opt_get(br, BROPT_VLAN_STATS_PER_PORT)) अणु
			v->stats =
			     netdev_alloc_pcpu_stats(काष्ठा pcpu_sw_netstats);
			अगर (!v->stats) अणु
				err = -ENOMEM;
				जाओ out_filt;
			पूर्ण
			v->priv_flags |= BR_VLFLAG_PER_PORT_STATS;
		पूर्ण अन्यथा अणु
			v->stats = masterv->stats;
		पूर्ण
	पूर्ण अन्यथा अणु
		err = br_चयनdev_port_vlan_add(dev, v->vid, flags, extack);
		अगर (err && err != -EOPNOTSUPP)
			जाओ out;
	पूर्ण

	/* Add the dev mac and count the vlan only अगर it's usable */
	अगर (br_vlan_should_use(v)) अणु
		err = br_fdb_insert(br, p, dev->dev_addr, v->vid);
		अगर (err) अणु
			br_err(br, "failed insert local address into bridge forwarding table\n");
			जाओ out_filt;
		पूर्ण
		vg->num_vlans++;
	पूर्ण

	/* set the state beक्रमe publishing */
	v->state = BR_STATE_FORWARDING;

	err = rhashtable_lookup_insert_fast(&vg->vlan_hash, &v->vnode,
					    br_vlan_rht_params);
	अगर (err)
		जाओ out_fdb_insert;

	__vlan_add_list(v);
	__vlan_add_flags(v, flags);

	अगर (p)
		nbp_vlan_set_vlan_dev_state(p, v->vid);
out:
	वापस err;

out_fdb_insert:
	अगर (br_vlan_should_use(v)) अणु
		br_fdb_find_delete_local(br, p, dev->dev_addr, v->vid);
		vg->num_vlans--;
	पूर्ण

out_filt:
	अगर (p) अणु
		__vlan_vid_del(dev, br, v);
		अगर (masterv) अणु
			अगर (v->stats && masterv->stats != v->stats)
				मुक्त_percpu(v->stats);
			v->stats = शून्य;

			br_vlan_put_master(masterv);
			v->brvlan = शून्य;
		पूर्ण
	पूर्ण अन्यथा अणु
		br_चयनdev_port_vlan_del(dev, v->vid);
	पूर्ण

	जाओ out;
पूर्ण

अटल पूर्णांक __vlan_del(काष्ठा net_bridge_vlan *v)
अणु
	काष्ठा net_bridge_vlan *masterv = v;
	काष्ठा net_bridge_vlan_group *vg;
	काष्ठा net_bridge_port *p = शून्य;
	पूर्णांक err = 0;

	अगर (br_vlan_is_master(v)) अणु
		vg = br_vlan_group(v->br);
	पूर्ण अन्यथा अणु
		p = v->port;
		vg = nbp_vlan_group(v->port);
		masterv = v->brvlan;
	पूर्ण

	__vlan_delete_pvid(vg, v->vid);
	अगर (p) अणु
		err = __vlan_vid_del(p->dev, p->br, v);
		अगर (err)
			जाओ out;
	पूर्ण अन्यथा अणु
		err = br_चयनdev_port_vlan_del(v->br->dev, v->vid);
		अगर (err && err != -EOPNOTSUPP)
			जाओ out;
		err = 0;
	पूर्ण

	अगर (br_vlan_should_use(v)) अणु
		v->flags &= ~BRIDGE_VLAN_INFO_BRENTRY;
		vg->num_vlans--;
	पूर्ण

	अगर (masterv != v) अणु
		vlan_tunnel_info_del(vg, v);
		rhashtable_हटाओ_fast(&vg->vlan_hash, &v->vnode,
				       br_vlan_rht_params);
		__vlan_del_list(v);
		nbp_vlan_set_vlan_dev_state(p, v->vid);
		call_rcu(&v->rcu, nbp_vlan_rcu_मुक्त);
	पूर्ण

	br_vlan_put_master(masterv);
out:
	वापस err;
पूर्ण

अटल व्योम __vlan_group_मुक्त(काष्ठा net_bridge_vlan_group *vg)
अणु
	WARN_ON(!list_empty(&vg->vlan_list));
	rhashtable_destroy(&vg->vlan_hash);
	vlan_tunnel_deinit(vg);
	kमुक्त(vg);
पूर्ण

अटल व्योम __vlan_flush(स्थिर काष्ठा net_bridge *br,
			 स्थिर काष्ठा net_bridge_port *p,
			 काष्ठा net_bridge_vlan_group *vg)
अणु
	काष्ठा net_bridge_vlan *vlan, *पंचांगp;
	u16 v_start = 0, v_end = 0;

	__vlan_delete_pvid(vg, vg->pvid);
	list_क्रम_each_entry_safe(vlan, पंचांगp, &vg->vlan_list, vlist) अणु
		/* take care of disjoपूर्णांक ranges */
		अगर (!v_start) अणु
			v_start = vlan->vid;
		पूर्ण अन्यथा अगर (vlan->vid - v_end != 1) अणु
			/* found range end, notअगरy and start next one */
			br_vlan_notअगरy(br, p, v_start, v_end, RTM_DELVLAN);
			v_start = vlan->vid;
		पूर्ण
		v_end = vlan->vid;

		__vlan_del(vlan);
	पूर्ण

	/* notअगरy about the last/whole vlan range */
	अगर (v_start)
		br_vlan_notअगरy(br, p, v_start, v_end, RTM_DELVLAN);
पूर्ण

काष्ठा sk_buff *br_handle_vlan(काष्ठा net_bridge *br,
			       स्थिर काष्ठा net_bridge_port *p,
			       काष्ठा net_bridge_vlan_group *vg,
			       काष्ठा sk_buff *skb)
अणु
	काष्ठा pcpu_sw_netstats *stats;
	काष्ठा net_bridge_vlan *v;
	u16 vid;

	/* If this packet was not filtered at input, let it pass */
	अगर (!BR_INPUT_SKB_CB(skb)->vlan_filtered)
		जाओ out;

	/* At this poपूर्णांक, we know that the frame was filtered and contains
	 * a valid vlan id.  If the vlan id has untagged flag set,
	 * send untagged; otherwise, send tagged.
	 */
	br_vlan_get_tag(skb, &vid);
	v = br_vlan_find(vg, vid);
	/* Vlan entry must be configured at this poपूर्णांक.  The
	 * only exception is the bridge is set in promisc mode and the
	 * packet is destined क्रम the bridge device.  In this हाल
	 * pass the packet as is.
	 */
	अगर (!v || !br_vlan_should_use(v)) अणु
		अगर ((br->dev->flags & IFF_PROMISC) && skb->dev == br->dev) अणु
			जाओ out;
		पूर्ण अन्यथा अणु
			kमुक्त_skb(skb);
			वापस शून्य;
		पूर्ण
	पूर्ण
	अगर (br_opt_get(br, BROPT_VLAN_STATS_ENABLED)) अणु
		stats = this_cpu_ptr(v->stats);
		u64_stats_update_begin(&stats->syncp);
		stats->tx_bytes += skb->len;
		stats->tx_packets++;
		u64_stats_update_end(&stats->syncp);
	पूर्ण

	अगर (v->flags & BRIDGE_VLAN_INFO_UNTAGGED)
		__vlan_hwaccel_clear_tag(skb);

	अगर (p && (p->flags & BR_VLAN_TUNNEL) &&
	    br_handle_egress_vlan_tunnel(skb, v)) अणु
		kमुक्त_skb(skb);
		वापस शून्य;
	पूर्ण
out:
	वापस skb;
पूर्ण

/* Called under RCU */
अटल bool __allowed_ingress(स्थिर काष्ठा net_bridge *br,
			      काष्ठा net_bridge_vlan_group *vg,
			      काष्ठा sk_buff *skb, u16 *vid,
			      u8 *state)
अणु
	काष्ठा pcpu_sw_netstats *stats;
	काष्ठा net_bridge_vlan *v;
	bool tagged;

	BR_INPUT_SKB_CB(skb)->vlan_filtered = true;
	/* If vlan tx offload is disabled on bridge device and frame was
	 * sent from vlan device on the bridge device, it करोes not have
	 * HW accelerated vlan tag.
	 */
	अगर (unlikely(!skb_vlan_tag_present(skb) &&
		     skb->protocol == br->vlan_proto)) अणु
		skb = skb_vlan_untag(skb);
		अगर (unlikely(!skb))
			वापस false;
	पूर्ण

	अगर (!br_vlan_get_tag(skb, vid)) अणु
		/* Tagged frame */
		अगर (skb->vlan_proto != br->vlan_proto) अणु
			/* Protocol-mismatch, empty out vlan_tci क्रम new tag */
			skb_push(skb, ETH_HLEN);
			skb = vlan_insert_tag_set_proto(skb, skb->vlan_proto,
							skb_vlan_tag_get(skb));
			अगर (unlikely(!skb))
				वापस false;

			skb_pull(skb, ETH_HLEN);
			skb_reset_mac_len(skb);
			*vid = 0;
			tagged = false;
		पूर्ण अन्यथा अणु
			tagged = true;
		पूर्ण
	पूर्ण अन्यथा अणु
		/* Untagged frame */
		tagged = false;
	पूर्ण

	अगर (!*vid) अणु
		u16 pvid = br_get_pvid(vg);

		/* Frame had a tag with VID 0 or did not have a tag.
		 * See अगर pvid is set on this port.  That tells us which
		 * vlan untagged or priority-tagged traffic beदीर्घs to.
		 */
		अगर (!pvid)
			जाओ drop;

		/* PVID is set on this port.  Any untagged or priority-tagged
		 * ingress frame is considered to beदीर्घ to this vlan.
		 */
		*vid = pvid;
		अगर (likely(!tagged))
			/* Untagged Frame. */
			__vlan_hwaccel_put_tag(skb, br->vlan_proto, pvid);
		अन्यथा
			/* Priority-tagged Frame.
			 * At this poपूर्णांक, we know that skb->vlan_tci VID
			 * field was 0.
			 * We update only VID field and preserve PCP field.
			 */
			skb->vlan_tci |= pvid;

		/* अगर stats are disabled we can aव्योम the lookup */
		अगर (!br_opt_get(br, BROPT_VLAN_STATS_ENABLED)) अणु
			अगर (*state == BR_STATE_FORWARDING) अणु
				*state = br_vlan_get_pvid_state(vg);
				वापस br_vlan_state_allowed(*state, true);
			पूर्ण अन्यथा अणु
				वापस true;
			पूर्ण
		पूर्ण
	पूर्ण
	v = br_vlan_find(vg, *vid);
	अगर (!v || !br_vlan_should_use(v))
		जाओ drop;

	अगर (*state == BR_STATE_FORWARDING) अणु
		*state = br_vlan_get_state(v);
		अगर (!br_vlan_state_allowed(*state, true))
			जाओ drop;
	पूर्ण

	अगर (br_opt_get(br, BROPT_VLAN_STATS_ENABLED)) अणु
		stats = this_cpu_ptr(v->stats);
		u64_stats_update_begin(&stats->syncp);
		stats->rx_bytes += skb->len;
		stats->rx_packets++;
		u64_stats_update_end(&stats->syncp);
	पूर्ण

	वापस true;

drop:
	kमुक्त_skb(skb);
	वापस false;
पूर्ण

bool br_allowed_ingress(स्थिर काष्ठा net_bridge *br,
			काष्ठा net_bridge_vlan_group *vg, काष्ठा sk_buff *skb,
			u16 *vid, u8 *state)
अणु
	/* If VLAN filtering is disabled on the bridge, all packets are
	 * permitted.
	 */
	अगर (!br_opt_get(br, BROPT_VLAN_ENABLED)) अणु
		BR_INPUT_SKB_CB(skb)->vlan_filtered = false;
		वापस true;
	पूर्ण

	वापस __allowed_ingress(br, vg, skb, vid, state);
पूर्ण

/* Called under RCU. */
bool br_allowed_egress(काष्ठा net_bridge_vlan_group *vg,
		       स्थिर काष्ठा sk_buff *skb)
अणु
	स्थिर काष्ठा net_bridge_vlan *v;
	u16 vid;

	/* If this packet was not filtered at input, let it pass */
	अगर (!BR_INPUT_SKB_CB(skb)->vlan_filtered)
		वापस true;

	br_vlan_get_tag(skb, &vid);
	v = br_vlan_find(vg, vid);
	अगर (v && br_vlan_should_use(v) &&
	    br_vlan_state_allowed(br_vlan_get_state(v), false))
		वापस true;

	वापस false;
पूर्ण

/* Called under RCU */
bool br_should_learn(काष्ठा net_bridge_port *p, काष्ठा sk_buff *skb, u16 *vid)
अणु
	काष्ठा net_bridge_vlan_group *vg;
	काष्ठा net_bridge *br = p->br;
	काष्ठा net_bridge_vlan *v;

	/* If filtering was disabled at input, let it pass. */
	अगर (!br_opt_get(br, BROPT_VLAN_ENABLED))
		वापस true;

	vg = nbp_vlan_group_rcu(p);
	अगर (!vg || !vg->num_vlans)
		वापस false;

	अगर (!br_vlan_get_tag(skb, vid) && skb->vlan_proto != br->vlan_proto)
		*vid = 0;

	अगर (!*vid) अणु
		*vid = br_get_pvid(vg);
		अगर (!*vid ||
		    !br_vlan_state_allowed(br_vlan_get_pvid_state(vg), true))
			वापस false;

		वापस true;
	पूर्ण

	v = br_vlan_find(vg, *vid);
	अगर (v && br_vlan_state_allowed(br_vlan_get_state(v), true))
		वापस true;

	वापस false;
पूर्ण

अटल पूर्णांक br_vlan_add_existing(काष्ठा net_bridge *br,
				काष्ठा net_bridge_vlan_group *vg,
				काष्ठा net_bridge_vlan *vlan,
				u16 flags, bool *changed,
				काष्ठा netlink_ext_ack *extack)
अणु
	पूर्णांक err;

	err = br_चयनdev_port_vlan_add(br->dev, vlan->vid, flags, extack);
	अगर (err && err != -EOPNOTSUPP)
		वापस err;

	अगर (!br_vlan_is_brentry(vlan)) अणु
		/* Trying to change flags of non-existent bridge vlan */
		अगर (!(flags & BRIDGE_VLAN_INFO_BRENTRY)) अणु
			err = -EINVAL;
			जाओ err_flags;
		पूर्ण
		/* It was only kept क्रम port vlans, now make it real */
		err = br_fdb_insert(br, शून्य, br->dev->dev_addr,
				    vlan->vid);
		अगर (err) अणु
			br_err(br, "failed to insert local address into bridge forwarding table\n");
			जाओ err_fdb_insert;
		पूर्ण

		refcount_inc(&vlan->refcnt);
		vlan->flags |= BRIDGE_VLAN_INFO_BRENTRY;
		vg->num_vlans++;
		*changed = true;
	पूर्ण

	अगर (__vlan_add_flags(vlan, flags))
		*changed = true;

	वापस 0;

err_fdb_insert:
err_flags:
	br_चयनdev_port_vlan_del(br->dev, vlan->vid);
	वापस err;
पूर्ण

/* Must be रक्षित by RTNL.
 * Must be called with vid in range from 1 to 4094 inclusive.
 * changed must be true only अगर the vlan was created or updated
 */
पूर्णांक br_vlan_add(काष्ठा net_bridge *br, u16 vid, u16 flags, bool *changed,
		काष्ठा netlink_ext_ack *extack)
अणु
	काष्ठा net_bridge_vlan_group *vg;
	काष्ठा net_bridge_vlan *vlan;
	पूर्णांक ret;

	ASSERT_RTNL();

	*changed = false;
	vg = br_vlan_group(br);
	vlan = br_vlan_find(vg, vid);
	अगर (vlan)
		वापस br_vlan_add_existing(br, vg, vlan, flags, changed,
					    extack);

	vlan = kzalloc(माप(*vlan), GFP_KERNEL);
	अगर (!vlan)
		वापस -ENOMEM;

	vlan->stats = netdev_alloc_pcpu_stats(काष्ठा pcpu_sw_netstats);
	अगर (!vlan->stats) अणु
		kमुक्त(vlan);
		वापस -ENOMEM;
	पूर्ण
	vlan->vid = vid;
	vlan->flags = flags | BRIDGE_VLAN_INFO_MASTER;
	vlan->flags &= ~BRIDGE_VLAN_INFO_PVID;
	vlan->br = br;
	अगर (flags & BRIDGE_VLAN_INFO_BRENTRY)
		refcount_set(&vlan->refcnt, 1);
	ret = __vlan_add(vlan, flags, extack);
	अगर (ret) अणु
		मुक्त_percpu(vlan->stats);
		kमुक्त(vlan);
	पूर्ण अन्यथा अणु
		*changed = true;
	पूर्ण

	वापस ret;
पूर्ण

/* Must be रक्षित by RTNL.
 * Must be called with vid in range from 1 to 4094 inclusive.
 */
पूर्णांक br_vlan_delete(काष्ठा net_bridge *br, u16 vid)
अणु
	काष्ठा net_bridge_vlan_group *vg;
	काष्ठा net_bridge_vlan *v;

	ASSERT_RTNL();

	vg = br_vlan_group(br);
	v = br_vlan_find(vg, vid);
	अगर (!v || !br_vlan_is_brentry(v))
		वापस -ENOENT;

	br_fdb_find_delete_local(br, शून्य, br->dev->dev_addr, vid);
	br_fdb_delete_by_port(br, शून्य, vid, 0);

	vlan_tunnel_info_del(vg, v);

	वापस __vlan_del(v);
पूर्ण

व्योम br_vlan_flush(काष्ठा net_bridge *br)
अणु
	काष्ठा net_bridge_vlan_group *vg;

	ASSERT_RTNL();

	vg = br_vlan_group(br);
	__vlan_flush(br, शून्य, vg);
	RCU_INIT_POINTER(br->vlgrp, शून्य);
	synchronize_rcu();
	__vlan_group_मुक्त(vg);
पूर्ण

काष्ठा net_bridge_vlan *br_vlan_find(काष्ठा net_bridge_vlan_group *vg, u16 vid)
अणु
	अगर (!vg)
		वापस शून्य;

	वापस br_vlan_lookup(&vg->vlan_hash, vid);
पूर्ण

/* Must be रक्षित by RTNL. */
अटल व्योम recalculate_group_addr(काष्ठा net_bridge *br)
अणु
	अगर (br_opt_get(br, BROPT_GROUP_ADDR_SET))
		वापस;

	spin_lock_bh(&br->lock);
	अगर (!br_opt_get(br, BROPT_VLAN_ENABLED) ||
	    br->vlan_proto == htons(ETH_P_8021Q)) अणु
		/* Bridge Group Address */
		br->group_addr[5] = 0x00;
	पूर्ण अन्यथा अणु /* vlan_enabled && ETH_P_8021AD */
		/* Provider Bridge Group Address */
		br->group_addr[5] = 0x08;
	पूर्ण
	spin_unlock_bh(&br->lock);
पूर्ण

/* Must be रक्षित by RTNL. */
व्योम br_recalculate_fwd_mask(काष्ठा net_bridge *br)
अणु
	अगर (!br_opt_get(br, BROPT_VLAN_ENABLED) ||
	    br->vlan_proto == htons(ETH_P_8021Q))
		br->group_fwd_mask_required = BR_GROUPFWD_DEFAULT;
	अन्यथा /* vlan_enabled && ETH_P_8021AD */
		br->group_fwd_mask_required = BR_GROUPFWD_8021AD &
					      ~(1u << br->group_addr[5]);
पूर्ण

पूर्णांक br_vlan_filter_toggle(काष्ठा net_bridge *br, अचिन्हित दीर्घ val,
			  काष्ठा netlink_ext_ack *extack)
अणु
	काष्ठा चयनdev_attr attr = अणु
		.orig_dev = br->dev,
		.id = SWITCHDEV_ATTR_ID_BRIDGE_VLAN_FILTERING,
		.flags = SWITCHDEV_F_SKIP_EOPNOTSUPP,
		.u.vlan_filtering = val,
	पूर्ण;
	पूर्णांक err;

	अगर (br_opt_get(br, BROPT_VLAN_ENABLED) == !!val)
		वापस 0;

	err = चयनdev_port_attr_set(br->dev, &attr, extack);
	अगर (err && err != -EOPNOTSUPP)
		वापस err;

	br_opt_toggle(br, BROPT_VLAN_ENABLED, !!val);
	br_manage_promisc(br);
	recalculate_group_addr(br);
	br_recalculate_fwd_mask(br);

	वापस 0;
पूर्ण

bool br_vlan_enabled(स्थिर काष्ठा net_device *dev)
अणु
	काष्ठा net_bridge *br = netdev_priv(dev);

	वापस br_opt_get(br, BROPT_VLAN_ENABLED);
पूर्ण
EXPORT_SYMBOL_GPL(br_vlan_enabled);

पूर्णांक br_vlan_get_proto(स्थिर काष्ठा net_device *dev, u16 *p_proto)
अणु
	काष्ठा net_bridge *br = netdev_priv(dev);

	*p_proto = ntohs(br->vlan_proto);

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(br_vlan_get_proto);

पूर्णांक __br_vlan_set_proto(काष्ठा net_bridge *br, __be16 proto,
			काष्ठा netlink_ext_ack *extack)
अणु
	काष्ठा चयनdev_attr attr = अणु
		.orig_dev = br->dev,
		.id = SWITCHDEV_ATTR_ID_BRIDGE_VLAN_PROTOCOL,
		.flags = SWITCHDEV_F_SKIP_EOPNOTSUPP,
		.u.vlan_protocol = ntohs(proto),
	पूर्ण;
	पूर्णांक err = 0;
	काष्ठा net_bridge_port *p;
	काष्ठा net_bridge_vlan *vlan;
	काष्ठा net_bridge_vlan_group *vg;
	__be16 oldproto = br->vlan_proto;

	अगर (br->vlan_proto == proto)
		वापस 0;

	err = चयनdev_port_attr_set(br->dev, &attr, extack);
	अगर (err && err != -EOPNOTSUPP)
		वापस err;

	/* Add VLANs क्रम the new proto to the device filter. */
	list_क्रम_each_entry(p, &br->port_list, list) अणु
		vg = nbp_vlan_group(p);
		list_क्रम_each_entry(vlan, &vg->vlan_list, vlist) अणु
			err = vlan_vid_add(p->dev, proto, vlan->vid);
			अगर (err)
				जाओ err_filt;
		पूर्ण
	पूर्ण

	br->vlan_proto = proto;

	recalculate_group_addr(br);
	br_recalculate_fwd_mask(br);

	/* Delete VLANs क्रम the old proto from the device filter. */
	list_क्रम_each_entry(p, &br->port_list, list) अणु
		vg = nbp_vlan_group(p);
		list_क्रम_each_entry(vlan, &vg->vlan_list, vlist)
			vlan_vid_del(p->dev, oldproto, vlan->vid);
	पूर्ण

	वापस 0;

err_filt:
	attr.u.vlan_protocol = ntohs(oldproto);
	चयनdev_port_attr_set(br->dev, &attr, शून्य);

	list_क्रम_each_entry_जारी_reverse(vlan, &vg->vlan_list, vlist)
		vlan_vid_del(p->dev, proto, vlan->vid);

	list_क्रम_each_entry_जारी_reverse(p, &br->port_list, list) अणु
		vg = nbp_vlan_group(p);
		list_क्रम_each_entry(vlan, &vg->vlan_list, vlist)
			vlan_vid_del(p->dev, proto, vlan->vid);
	पूर्ण

	वापस err;
पूर्ण

पूर्णांक br_vlan_set_proto(काष्ठा net_bridge *br, अचिन्हित दीर्घ val,
		      काष्ठा netlink_ext_ack *extack)
अणु
	अगर (!eth_type_vlan(htons(val)))
		वापस -EPROTONOSUPPORT;

	वापस __br_vlan_set_proto(br, htons(val), extack);
पूर्ण

पूर्णांक br_vlan_set_stats(काष्ठा net_bridge *br, अचिन्हित दीर्घ val)
अणु
	चयन (val) अणु
	हाल 0:
	हाल 1:
		br_opt_toggle(br, BROPT_VLAN_STATS_ENABLED, !!val);
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

पूर्णांक br_vlan_set_stats_per_port(काष्ठा net_bridge *br, अचिन्हित दीर्घ val)
अणु
	काष्ठा net_bridge_port *p;

	/* allow to change the option अगर there are no port vlans configured */
	list_क्रम_each_entry(p, &br->port_list, list) अणु
		काष्ठा net_bridge_vlan_group *vg = nbp_vlan_group(p);

		अगर (vg->num_vlans)
			वापस -EBUSY;
	पूर्ण

	चयन (val) अणु
	हाल 0:
	हाल 1:
		br_opt_toggle(br, BROPT_VLAN_STATS_PER_PORT, !!val);
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल bool vlan_शेष_pvid(काष्ठा net_bridge_vlan_group *vg, u16 vid)
अणु
	काष्ठा net_bridge_vlan *v;

	अगर (vid != vg->pvid)
		वापस false;

	v = br_vlan_lookup(&vg->vlan_hash, vid);
	अगर (v && br_vlan_should_use(v) &&
	    (v->flags & BRIDGE_VLAN_INFO_UNTAGGED))
		वापस true;

	वापस false;
पूर्ण

अटल व्योम br_vlan_disable_शेष_pvid(काष्ठा net_bridge *br)
अणु
	काष्ठा net_bridge_port *p;
	u16 pvid = br->शेष_pvid;

	/* Disable शेष_pvid on all ports where it is still
	 * configured.
	 */
	अगर (vlan_शेष_pvid(br_vlan_group(br), pvid)) अणु
		अगर (!br_vlan_delete(br, pvid))
			br_vlan_notअगरy(br, शून्य, pvid, 0, RTM_DELVLAN);
	पूर्ण

	list_क्रम_each_entry(p, &br->port_list, list) अणु
		अगर (vlan_शेष_pvid(nbp_vlan_group(p), pvid) &&
		    !nbp_vlan_delete(p, pvid))
			br_vlan_notअगरy(br, p, pvid, 0, RTM_DELVLAN);
	पूर्ण

	br->शेष_pvid = 0;
पूर्ण

पूर्णांक __br_vlan_set_शेष_pvid(काष्ठा net_bridge *br, u16 pvid,
			       काष्ठा netlink_ext_ack *extack)
अणु
	स्थिर काष्ठा net_bridge_vlan *pvent;
	काष्ठा net_bridge_vlan_group *vg;
	काष्ठा net_bridge_port *p;
	अचिन्हित दीर्घ *changed;
	bool vlchange;
	u16 old_pvid;
	पूर्णांक err = 0;

	अगर (!pvid) अणु
		br_vlan_disable_शेष_pvid(br);
		वापस 0;
	पूर्ण

	changed = biपंचांगap_zalloc(BR_MAX_PORTS, GFP_KERNEL);
	अगर (!changed)
		वापस -ENOMEM;

	old_pvid = br->शेष_pvid;

	/* Update शेष_pvid config only अगर we करो not conflict with
	 * user configuration.
	 */
	vg = br_vlan_group(br);
	pvent = br_vlan_find(vg, pvid);
	अगर ((!old_pvid || vlan_शेष_pvid(vg, old_pvid)) &&
	    (!pvent || !br_vlan_should_use(pvent))) अणु
		err = br_vlan_add(br, pvid,
				  BRIDGE_VLAN_INFO_PVID |
				  BRIDGE_VLAN_INFO_UNTAGGED |
				  BRIDGE_VLAN_INFO_BRENTRY,
				  &vlchange, extack);
		अगर (err)
			जाओ out;

		अगर (br_vlan_delete(br, old_pvid))
			br_vlan_notअगरy(br, शून्य, old_pvid, 0, RTM_DELVLAN);
		br_vlan_notअगरy(br, शून्य, pvid, 0, RTM_NEWVLAN);
		set_bit(0, changed);
	पूर्ण

	list_क्रम_each_entry(p, &br->port_list, list) अणु
		/* Update शेष_pvid config only अगर we करो not conflict with
		 * user configuration.
		 */
		vg = nbp_vlan_group(p);
		अगर ((old_pvid &&
		     !vlan_शेष_pvid(vg, old_pvid)) ||
		    br_vlan_find(vg, pvid))
			जारी;

		err = nbp_vlan_add(p, pvid,
				   BRIDGE_VLAN_INFO_PVID |
				   BRIDGE_VLAN_INFO_UNTAGGED,
				   &vlchange, extack);
		अगर (err)
			जाओ err_port;
		अगर (nbp_vlan_delete(p, old_pvid))
			br_vlan_notअगरy(br, p, old_pvid, 0, RTM_DELVLAN);
		br_vlan_notअगरy(p->br, p, pvid, 0, RTM_NEWVLAN);
		set_bit(p->port_no, changed);
	पूर्ण

	br->शेष_pvid = pvid;

out:
	biपंचांगap_मुक्त(changed);
	वापस err;

err_port:
	list_क्रम_each_entry_जारी_reverse(p, &br->port_list, list) अणु
		अगर (!test_bit(p->port_no, changed))
			जारी;

		अगर (old_pvid) अणु
			nbp_vlan_add(p, old_pvid,
				     BRIDGE_VLAN_INFO_PVID |
				     BRIDGE_VLAN_INFO_UNTAGGED,
				     &vlchange, शून्य);
			br_vlan_notअगरy(p->br, p, old_pvid, 0, RTM_NEWVLAN);
		पूर्ण
		nbp_vlan_delete(p, pvid);
		br_vlan_notअगरy(br, p, pvid, 0, RTM_DELVLAN);
	पूर्ण

	अगर (test_bit(0, changed)) अणु
		अगर (old_pvid) अणु
			br_vlan_add(br, old_pvid,
				    BRIDGE_VLAN_INFO_PVID |
				    BRIDGE_VLAN_INFO_UNTAGGED |
				    BRIDGE_VLAN_INFO_BRENTRY,
				    &vlchange, शून्य);
			br_vlan_notअगरy(br, शून्य, old_pvid, 0, RTM_NEWVLAN);
		पूर्ण
		br_vlan_delete(br, pvid);
		br_vlan_notअगरy(br, शून्य, pvid, 0, RTM_DELVLAN);
	पूर्ण
	जाओ out;
पूर्ण

पूर्णांक br_vlan_set_शेष_pvid(काष्ठा net_bridge *br, अचिन्हित दीर्घ val,
			     काष्ठा netlink_ext_ack *extack)
अणु
	u16 pvid = val;
	पूर्णांक err = 0;

	अगर (val >= VLAN_VID_MASK)
		वापस -EINVAL;

	अगर (pvid == br->शेष_pvid)
		जाओ out;

	/* Only allow शेष pvid change when filtering is disabled */
	अगर (br_opt_get(br, BROPT_VLAN_ENABLED)) अणु
		pr_info_once("Please disable vlan filtering to change default_pvid\n");
		err = -EPERM;
		जाओ out;
	पूर्ण
	err = __br_vlan_set_शेष_pvid(br, pvid, extack);
out:
	वापस err;
पूर्ण

पूर्णांक br_vlan_init(काष्ठा net_bridge *br)
अणु
	काष्ठा net_bridge_vlan_group *vg;
	पूर्णांक ret = -ENOMEM;

	vg = kzalloc(माप(*vg), GFP_KERNEL);
	अगर (!vg)
		जाओ out;
	ret = rhashtable_init(&vg->vlan_hash, &br_vlan_rht_params);
	अगर (ret)
		जाओ err_rhtbl;
	ret = vlan_tunnel_init(vg);
	अगर (ret)
		जाओ err_tunnel_init;
	INIT_LIST_HEAD(&vg->vlan_list);
	br->vlan_proto = htons(ETH_P_8021Q);
	br->शेष_pvid = 1;
	rcu_assign_poपूर्णांकer(br->vlgrp, vg);

out:
	वापस ret;

err_tunnel_init:
	rhashtable_destroy(&vg->vlan_hash);
err_rhtbl:
	kमुक्त(vg);

	जाओ out;
पूर्ण

पूर्णांक nbp_vlan_init(काष्ठा net_bridge_port *p, काष्ठा netlink_ext_ack *extack)
अणु
	काष्ठा चयनdev_attr attr = अणु
		.orig_dev = p->br->dev,
		.id = SWITCHDEV_ATTR_ID_BRIDGE_VLAN_FILTERING,
		.flags = SWITCHDEV_F_SKIP_EOPNOTSUPP,
		.u.vlan_filtering = br_opt_get(p->br, BROPT_VLAN_ENABLED),
	पूर्ण;
	काष्ठा net_bridge_vlan_group *vg;
	पूर्णांक ret = -ENOMEM;

	vg = kzalloc(माप(काष्ठा net_bridge_vlan_group), GFP_KERNEL);
	अगर (!vg)
		जाओ out;

	ret = चयनdev_port_attr_set(p->dev, &attr, extack);
	अगर (ret && ret != -EOPNOTSUPP)
		जाओ err_vlan_enabled;

	ret = rhashtable_init(&vg->vlan_hash, &br_vlan_rht_params);
	अगर (ret)
		जाओ err_rhtbl;
	ret = vlan_tunnel_init(vg);
	अगर (ret)
		जाओ err_tunnel_init;
	INIT_LIST_HEAD(&vg->vlan_list);
	rcu_assign_poपूर्णांकer(p->vlgrp, vg);
	अगर (p->br->शेष_pvid) अणु
		bool changed;

		ret = nbp_vlan_add(p, p->br->शेष_pvid,
				   BRIDGE_VLAN_INFO_PVID |
				   BRIDGE_VLAN_INFO_UNTAGGED,
				   &changed, extack);
		अगर (ret)
			जाओ err_vlan_add;
		br_vlan_notअगरy(p->br, p, p->br->शेष_pvid, 0, RTM_NEWVLAN);
	पूर्ण
out:
	वापस ret;

err_vlan_add:
	RCU_INIT_POINTER(p->vlgrp, शून्य);
	synchronize_rcu();
	vlan_tunnel_deinit(vg);
err_tunnel_init:
	rhashtable_destroy(&vg->vlan_hash);
err_rhtbl:
err_vlan_enabled:
	kमुक्त(vg);

	जाओ out;
पूर्ण

/* Must be रक्षित by RTNL.
 * Must be called with vid in range from 1 to 4094 inclusive.
 * changed must be true only अगर the vlan was created or updated
 */
पूर्णांक nbp_vlan_add(काष्ठा net_bridge_port *port, u16 vid, u16 flags,
		 bool *changed, काष्ठा netlink_ext_ack *extack)
अणु
	काष्ठा net_bridge_vlan *vlan;
	पूर्णांक ret;

	ASSERT_RTNL();

	*changed = false;
	vlan = br_vlan_find(nbp_vlan_group(port), vid);
	अगर (vlan) अणु
		/* Pass the flags to the hardware bridge */
		ret = br_चयनdev_port_vlan_add(port->dev, vid, flags, extack);
		अगर (ret && ret != -EOPNOTSUPP)
			वापस ret;
		*changed = __vlan_add_flags(vlan, flags);

		वापस 0;
	पूर्ण

	vlan = kzalloc(माप(*vlan), GFP_KERNEL);
	अगर (!vlan)
		वापस -ENOMEM;

	vlan->vid = vid;
	vlan->port = port;
	ret = __vlan_add(vlan, flags, extack);
	अगर (ret)
		kमुक्त(vlan);
	अन्यथा
		*changed = true;

	वापस ret;
पूर्ण

/* Must be रक्षित by RTNL.
 * Must be called with vid in range from 1 to 4094 inclusive.
 */
पूर्णांक nbp_vlan_delete(काष्ठा net_bridge_port *port, u16 vid)
अणु
	काष्ठा net_bridge_vlan *v;

	ASSERT_RTNL();

	v = br_vlan_find(nbp_vlan_group(port), vid);
	अगर (!v)
		वापस -ENOENT;
	br_fdb_find_delete_local(port->br, port, port->dev->dev_addr, vid);
	br_fdb_delete_by_port(port->br, port, vid, 0);

	वापस __vlan_del(v);
पूर्ण

व्योम nbp_vlan_flush(काष्ठा net_bridge_port *port)
अणु
	काष्ठा net_bridge_vlan_group *vg;

	ASSERT_RTNL();

	vg = nbp_vlan_group(port);
	__vlan_flush(port->br, port, vg);
	RCU_INIT_POINTER(port->vlgrp, शून्य);
	synchronize_rcu();
	__vlan_group_मुक्त(vg);
पूर्ण

व्योम br_vlan_get_stats(स्थिर काष्ठा net_bridge_vlan *v,
		       काष्ठा pcpu_sw_netstats *stats)
अणु
	पूर्णांक i;

	स_रखो(stats, 0, माप(*stats));
	क्रम_each_possible_cpu(i) अणु
		u64 rxpackets, rxbytes, txpackets, txbytes;
		काष्ठा pcpu_sw_netstats *cpu_stats;
		अचिन्हित पूर्णांक start;

		cpu_stats = per_cpu_ptr(v->stats, i);
		करो अणु
			start = u64_stats_fetch_begin_irq(&cpu_stats->syncp);
			rxpackets = cpu_stats->rx_packets;
			rxbytes = cpu_stats->rx_bytes;
			txbytes = cpu_stats->tx_bytes;
			txpackets = cpu_stats->tx_packets;
		पूर्ण जबतक (u64_stats_fetch_retry_irq(&cpu_stats->syncp, start));

		stats->rx_packets += rxpackets;
		stats->rx_bytes += rxbytes;
		stats->tx_bytes += txbytes;
		stats->tx_packets += txpackets;
	पूर्ण
पूर्ण

पूर्णांक br_vlan_get_pvid(स्थिर काष्ठा net_device *dev, u16 *p_pvid)
अणु
	काष्ठा net_bridge_vlan_group *vg;
	काष्ठा net_bridge_port *p;

	ASSERT_RTNL();
	p = br_port_get_check_rtnl(dev);
	अगर (p)
		vg = nbp_vlan_group(p);
	अन्यथा अगर (netअगर_is_bridge_master(dev))
		vg = br_vlan_group(netdev_priv(dev));
	अन्यथा
		वापस -EINVAL;

	*p_pvid = br_get_pvid(vg);
	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(br_vlan_get_pvid);

पूर्णांक br_vlan_get_pvid_rcu(स्थिर काष्ठा net_device *dev, u16 *p_pvid)
अणु
	काष्ठा net_bridge_vlan_group *vg;
	काष्ठा net_bridge_port *p;

	p = br_port_get_check_rcu(dev);
	अगर (p)
		vg = nbp_vlan_group_rcu(p);
	अन्यथा अगर (netअगर_is_bridge_master(dev))
		vg = br_vlan_group_rcu(netdev_priv(dev));
	अन्यथा
		वापस -EINVAL;

	*p_pvid = br_get_pvid(vg);
	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(br_vlan_get_pvid_rcu);

व्योम br_vlan_fill_क्रमward_path_pvid(काष्ठा net_bridge *br,
				    काष्ठा net_device_path_ctx *ctx,
				    काष्ठा net_device_path *path)
अणु
	काष्ठा net_bridge_vlan_group *vg;
	पूर्णांक idx = ctx->num_vlans - 1;
	u16 vid;

	path->bridge.vlan_mode = DEV_PATH_BR_VLAN_KEEP;

	अगर (!br_opt_get(br, BROPT_VLAN_ENABLED))
		वापस;

	vg = br_vlan_group(br);

	अगर (idx >= 0 &&
	    ctx->vlan[idx].proto == br->vlan_proto) अणु
		vid = ctx->vlan[idx].id;
	पूर्ण अन्यथा अणु
		path->bridge.vlan_mode = DEV_PATH_BR_VLAN_TAG;
		vid = br_get_pvid(vg);
	पूर्ण

	path->bridge.vlan_id = vid;
	path->bridge.vlan_proto = br->vlan_proto;
पूर्ण

पूर्णांक br_vlan_fill_क्रमward_path_mode(काष्ठा net_bridge *br,
				   काष्ठा net_bridge_port *dst,
				   काष्ठा net_device_path *path)
अणु
	काष्ठा net_bridge_vlan_group *vg;
	काष्ठा net_bridge_vlan *v;

	अगर (!br_opt_get(br, BROPT_VLAN_ENABLED))
		वापस 0;

	vg = nbp_vlan_group_rcu(dst);
	v = br_vlan_find(vg, path->bridge.vlan_id);
	अगर (!v || !br_vlan_should_use(v))
		वापस -EINVAL;

	अगर (!(v->flags & BRIDGE_VLAN_INFO_UNTAGGED))
		वापस 0;

	अगर (path->bridge.vlan_mode == DEV_PATH_BR_VLAN_TAG)
		path->bridge.vlan_mode = DEV_PATH_BR_VLAN_KEEP;
	अन्यथा अगर (v->priv_flags & BR_VLFLAG_ADDED_BY_SWITCHDEV)
		path->bridge.vlan_mode = DEV_PATH_BR_VLAN_UNTAG_HW;
	अन्यथा
		path->bridge.vlan_mode = DEV_PATH_BR_VLAN_UNTAG;

	वापस 0;
पूर्ण

पूर्णांक br_vlan_get_info(स्थिर काष्ठा net_device *dev, u16 vid,
		     काष्ठा bridge_vlan_info *p_vinfo)
अणु
	काष्ठा net_bridge_vlan_group *vg;
	काष्ठा net_bridge_vlan *v;
	काष्ठा net_bridge_port *p;

	ASSERT_RTNL();
	p = br_port_get_check_rtnl(dev);
	अगर (p)
		vg = nbp_vlan_group(p);
	अन्यथा अगर (netअगर_is_bridge_master(dev))
		vg = br_vlan_group(netdev_priv(dev));
	अन्यथा
		वापस -EINVAL;

	v = br_vlan_find(vg, vid);
	अगर (!v)
		वापस -ENOENT;

	p_vinfo->vid = vid;
	p_vinfo->flags = v->flags;
	अगर (vid == br_get_pvid(vg))
		p_vinfo->flags |= BRIDGE_VLAN_INFO_PVID;
	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(br_vlan_get_info);

अटल पूर्णांक br_vlan_is_bind_vlan_dev(स्थिर काष्ठा net_device *dev)
अणु
	वापस is_vlan_dev(dev) &&
		!!(vlan_dev_priv(dev)->flags & VLAN_FLAG_BRIDGE_BINDING);
पूर्ण

अटल पूर्णांक br_vlan_is_bind_vlan_dev_fn(काष्ठा net_device *dev,
			       __always_unused काष्ठा netdev_nested_priv *priv)
अणु
	वापस br_vlan_is_bind_vlan_dev(dev);
पूर्ण

अटल bool br_vlan_has_upper_bind_vlan_dev(काष्ठा net_device *dev)
अणु
	पूर्णांक found;

	rcu_पढ़ो_lock();
	found = netdev_walk_all_upper_dev_rcu(dev, br_vlan_is_bind_vlan_dev_fn,
					      शून्य);
	rcu_पढ़ो_unlock();

	वापस !!found;
पूर्ण

काष्ठा br_vlan_bind_walk_data अणु
	u16 vid;
	काष्ठा net_device *result;
पूर्ण;

अटल पूर्णांक br_vlan_match_bind_vlan_dev_fn(काष्ठा net_device *dev,
					  काष्ठा netdev_nested_priv *priv)
अणु
	काष्ठा br_vlan_bind_walk_data *data = priv->data;
	पूर्णांक found = 0;

	अगर (br_vlan_is_bind_vlan_dev(dev) &&
	    vlan_dev_priv(dev)->vlan_id == data->vid) अणु
		data->result = dev;
		found = 1;
	पूर्ण

	वापस found;
पूर्ण

अटल काष्ठा net_device *
br_vlan_get_upper_bind_vlan_dev(काष्ठा net_device *dev, u16 vid)
अणु
	काष्ठा br_vlan_bind_walk_data data = अणु
		.vid = vid,
	पूर्ण;
	काष्ठा netdev_nested_priv priv = अणु
		.data = (व्योम *)&data,
	पूर्ण;

	rcu_पढ़ो_lock();
	netdev_walk_all_upper_dev_rcu(dev, br_vlan_match_bind_vlan_dev_fn,
				      &priv);
	rcu_पढ़ो_unlock();

	वापस data.result;
पूर्ण

अटल bool br_vlan_is_dev_up(स्थिर काष्ठा net_device *dev)
अणु
	वापस  !!(dev->flags & IFF_UP) && netअगर_oper_up(dev);
पूर्ण

अटल व्योम br_vlan_set_vlan_dev_state(स्थिर काष्ठा net_bridge *br,
				       काष्ठा net_device *vlan_dev)
अणु
	u16 vid = vlan_dev_priv(vlan_dev)->vlan_id;
	काष्ठा net_bridge_vlan_group *vg;
	काष्ठा net_bridge_port *p;
	bool has_carrier = false;

	अगर (!netअगर_carrier_ok(br->dev)) अणु
		netअगर_carrier_off(vlan_dev);
		वापस;
	पूर्ण

	list_क्रम_each_entry(p, &br->port_list, list) अणु
		vg = nbp_vlan_group(p);
		अगर (br_vlan_find(vg, vid) && br_vlan_is_dev_up(p->dev)) अणु
			has_carrier = true;
			अवरोध;
		पूर्ण
	पूर्ण

	अगर (has_carrier)
		netअगर_carrier_on(vlan_dev);
	अन्यथा
		netअगर_carrier_off(vlan_dev);
पूर्ण

अटल व्योम br_vlan_set_all_vlan_dev_state(काष्ठा net_bridge_port *p)
अणु
	काष्ठा net_bridge_vlan_group *vg = nbp_vlan_group(p);
	काष्ठा net_bridge_vlan *vlan;
	काष्ठा net_device *vlan_dev;

	list_क्रम_each_entry(vlan, &vg->vlan_list, vlist) अणु
		vlan_dev = br_vlan_get_upper_bind_vlan_dev(p->br->dev,
							   vlan->vid);
		अगर (vlan_dev) अणु
			अगर (br_vlan_is_dev_up(p->dev)) अणु
				अगर (netअगर_carrier_ok(p->br->dev))
					netअगर_carrier_on(vlan_dev);
			पूर्ण अन्यथा अणु
				br_vlan_set_vlan_dev_state(p->br, vlan_dev);
			पूर्ण
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम br_vlan_upper_change(काष्ठा net_device *dev,
				 काष्ठा net_device *upper_dev,
				 bool linking)
अणु
	काष्ठा net_bridge *br = netdev_priv(dev);

	अगर (!br_vlan_is_bind_vlan_dev(upper_dev))
		वापस;

	अगर (linking) अणु
		br_vlan_set_vlan_dev_state(br, upper_dev);
		br_opt_toggle(br, BROPT_VLAN_BRIDGE_BINDING, true);
	पूर्ण अन्यथा अणु
		br_opt_toggle(br, BROPT_VLAN_BRIDGE_BINDING,
			      br_vlan_has_upper_bind_vlan_dev(dev));
	पूर्ण
पूर्ण

काष्ठा br_vlan_link_state_walk_data अणु
	काष्ठा net_bridge *br;
पूर्ण;

अटल पूर्णांक br_vlan_link_state_change_fn(काष्ठा net_device *vlan_dev,
					काष्ठा netdev_nested_priv *priv)
अणु
	काष्ठा br_vlan_link_state_walk_data *data = priv->data;

	अगर (br_vlan_is_bind_vlan_dev(vlan_dev))
		br_vlan_set_vlan_dev_state(data->br, vlan_dev);

	वापस 0;
पूर्ण

अटल व्योम br_vlan_link_state_change(काष्ठा net_device *dev,
				      काष्ठा net_bridge *br)
अणु
	काष्ठा br_vlan_link_state_walk_data data = अणु
		.br = br
	पूर्ण;
	काष्ठा netdev_nested_priv priv = अणु
		.data = (व्योम *)&data,
	पूर्ण;

	rcu_पढ़ो_lock();
	netdev_walk_all_upper_dev_rcu(dev, br_vlan_link_state_change_fn,
				      &priv);
	rcu_पढ़ो_unlock();
पूर्ण

/* Must be रक्षित by RTNL. */
अटल व्योम nbp_vlan_set_vlan_dev_state(काष्ठा net_bridge_port *p, u16 vid)
अणु
	काष्ठा net_device *vlan_dev;

	अगर (!br_opt_get(p->br, BROPT_VLAN_BRIDGE_BINDING))
		वापस;

	vlan_dev = br_vlan_get_upper_bind_vlan_dev(p->br->dev, vid);
	अगर (vlan_dev)
		br_vlan_set_vlan_dev_state(p->br, vlan_dev);
पूर्ण

/* Must be रक्षित by RTNL. */
पूर्णांक br_vlan_bridge_event(काष्ठा net_device *dev, अचिन्हित दीर्घ event, व्योम *ptr)
अणु
	काष्ठा netdev_notअगरier_changeupper_info *info;
	काष्ठा net_bridge *br = netdev_priv(dev);
	पूर्णांक vlcmd = 0, ret = 0;
	bool changed = false;

	चयन (event) अणु
	हाल NETDEV_REGISTER:
		ret = br_vlan_add(br, br->शेष_pvid,
				  BRIDGE_VLAN_INFO_PVID |
				  BRIDGE_VLAN_INFO_UNTAGGED |
				  BRIDGE_VLAN_INFO_BRENTRY, &changed, शून्य);
		vlcmd = RTM_NEWVLAN;
		अवरोध;
	हाल NETDEV_UNREGISTER:
		changed = !br_vlan_delete(br, br->शेष_pvid);
		vlcmd = RTM_DELVLAN;
		अवरोध;
	हाल NETDEV_CHANGEUPPER:
		info = ptr;
		br_vlan_upper_change(dev, info->upper_dev, info->linking);
		अवरोध;

	हाल NETDEV_CHANGE:
	हाल NETDEV_UP:
		अगर (!br_opt_get(br, BROPT_VLAN_BRIDGE_BINDING))
			अवरोध;
		br_vlan_link_state_change(dev, br);
		अवरोध;
	पूर्ण
	अगर (changed)
		br_vlan_notअगरy(br, शून्य, br->शेष_pvid, 0, vlcmd);

	वापस ret;
पूर्ण

/* Must be रक्षित by RTNL. */
व्योम br_vlan_port_event(काष्ठा net_bridge_port *p, अचिन्हित दीर्घ event)
अणु
	अगर (!br_opt_get(p->br, BROPT_VLAN_BRIDGE_BINDING))
		वापस;

	चयन (event) अणु
	हाल NETDEV_CHANGE:
	हाल NETDEV_DOWN:
	हाल NETDEV_UP:
		br_vlan_set_all_vlan_dev_state(p);
		अवरोध;
	पूर्ण
पूर्ण

अटल bool br_vlan_stats_fill(काष्ठा sk_buff *skb,
			       स्थिर काष्ठा net_bridge_vlan *v)
अणु
	काष्ठा pcpu_sw_netstats stats;
	काष्ठा nlattr *nest;

	nest = nla_nest_start(skb, BRIDGE_VLANDB_ENTRY_STATS);
	अगर (!nest)
		वापस false;

	br_vlan_get_stats(v, &stats);
	अगर (nla_put_u64_64bit(skb, BRIDGE_VLANDB_STATS_RX_BYTES, stats.rx_bytes,
			      BRIDGE_VLANDB_STATS_PAD) ||
	    nla_put_u64_64bit(skb, BRIDGE_VLANDB_STATS_RX_PACKETS,
			      stats.rx_packets, BRIDGE_VLANDB_STATS_PAD) ||
	    nla_put_u64_64bit(skb, BRIDGE_VLANDB_STATS_TX_BYTES, stats.tx_bytes,
			      BRIDGE_VLANDB_STATS_PAD) ||
	    nla_put_u64_64bit(skb, BRIDGE_VLANDB_STATS_TX_PACKETS,
			      stats.tx_packets, BRIDGE_VLANDB_STATS_PAD))
		जाओ out_err;

	nla_nest_end(skb, nest);

	वापस true;

out_err:
	nla_nest_cancel(skb, nest);
	वापस false;
पूर्ण

/* v_opts is used to dump the options which must be equal in the whole range */
अटल bool br_vlan_fill_vids(काष्ठा sk_buff *skb, u16 vid, u16 vid_range,
			      स्थिर काष्ठा net_bridge_vlan *v_opts,
			      u16 flags,
			      bool dump_stats)
अणु
	काष्ठा bridge_vlan_info info;
	काष्ठा nlattr *nest;

	nest = nla_nest_start(skb, BRIDGE_VLANDB_ENTRY);
	अगर (!nest)
		वापस false;

	स_रखो(&info, 0, माप(info));
	info.vid = vid;
	अगर (flags & BRIDGE_VLAN_INFO_UNTAGGED)
		info.flags |= BRIDGE_VLAN_INFO_UNTAGGED;
	अगर (flags & BRIDGE_VLAN_INFO_PVID)
		info.flags |= BRIDGE_VLAN_INFO_PVID;

	अगर (nla_put(skb, BRIDGE_VLANDB_ENTRY_INFO, माप(info), &info))
		जाओ out_err;

	अगर (vid_range && vid < vid_range &&
	    !(flags & BRIDGE_VLAN_INFO_PVID) &&
	    nla_put_u16(skb, BRIDGE_VLANDB_ENTRY_RANGE, vid_range))
		जाओ out_err;

	अगर (v_opts) अणु
		अगर (!br_vlan_opts_fill(skb, v_opts))
			जाओ out_err;

		अगर (dump_stats && !br_vlan_stats_fill(skb, v_opts))
			जाओ out_err;
	पूर्ण

	nla_nest_end(skb, nest);

	वापस true;

out_err:
	nla_nest_cancel(skb, nest);
	वापस false;
पूर्ण

अटल माप_प्रकार rtnl_vlan_nlmsg_size(व्योम)
अणु
	वापस NLMSG_ALIGN(माप(काष्ठा br_vlan_msg))
		+ nla_total_size(0) /* BRIDGE_VLANDB_ENTRY */
		+ nla_total_size(माप(u16)) /* BRIDGE_VLANDB_ENTRY_RANGE */
		+ nla_total_size(माप(काष्ठा bridge_vlan_info)) /* BRIDGE_VLANDB_ENTRY_INFO */
		+ br_vlan_opts_nl_size(); /* bridge vlan options */
पूर्ण

व्योम br_vlan_notअगरy(स्थिर काष्ठा net_bridge *br,
		    स्थिर काष्ठा net_bridge_port *p,
		    u16 vid, u16 vid_range,
		    पूर्णांक cmd)
अणु
	काष्ठा net_bridge_vlan_group *vg;
	काष्ठा net_bridge_vlan *v = शून्य;
	काष्ठा br_vlan_msg *bvm;
	काष्ठा nlmsghdr *nlh;
	काष्ठा sk_buff *skb;
	पूर्णांक err = -ENOBUFS;
	काष्ठा net *net;
	u16 flags = 0;
	पूर्णांक अगरindex;

	/* right now notअगरications are करोne only with rtnl held */
	ASSERT_RTNL();

	अगर (p) अणु
		अगरindex = p->dev->अगरindex;
		vg = nbp_vlan_group(p);
		net = dev_net(p->dev);
	पूर्ण अन्यथा अणु
		अगरindex = br->dev->अगरindex;
		vg = br_vlan_group(br);
		net = dev_net(br->dev);
	पूर्ण

	skb = nlmsg_new(rtnl_vlan_nlmsg_size(), GFP_KERNEL);
	अगर (!skb)
		जाओ out_err;

	err = -EMSGSIZE;
	nlh = nlmsg_put(skb, 0, 0, cmd, माप(*bvm), 0);
	अगर (!nlh)
		जाओ out_err;
	bvm = nlmsg_data(nlh);
	स_रखो(bvm, 0, माप(*bvm));
	bvm->family = AF_BRIDGE;
	bvm->अगरindex = अगरindex;

	चयन (cmd) अणु
	हाल RTM_NEWVLAN:
		/* need to find the vlan due to flags/options */
		v = br_vlan_find(vg, vid);
		अगर (!v || !br_vlan_should_use(v))
			जाओ out_kमुक्त;

		flags = v->flags;
		अगर (br_get_pvid(vg) == v->vid)
			flags |= BRIDGE_VLAN_INFO_PVID;
		अवरोध;
	हाल RTM_DELVLAN:
		अवरोध;
	शेष:
		जाओ out_kमुक्त;
	पूर्ण

	अगर (!br_vlan_fill_vids(skb, vid, vid_range, v, flags, false))
		जाओ out_err;

	nlmsg_end(skb, nlh);
	rtnl_notअगरy(skb, net, 0, RTNLGRP_BRVLAN, शून्य, GFP_KERNEL);
	वापस;

out_err:
	rtnl_set_sk_err(net, RTNLGRP_BRVLAN, err);
out_kमुक्त:
	kमुक्त_skb(skb);
पूर्ण

अटल पूर्णांक br_vlan_replay_one(काष्ठा notअगरier_block *nb,
			      काष्ठा net_device *dev,
			      काष्ठा चयनdev_obj_port_vlan *vlan,
			      काष्ठा netlink_ext_ack *extack)
अणु
	काष्ठा चयनdev_notअगरier_port_obj_info obj_info = अणु
		.info = अणु
			.dev = dev,
			.extack = extack,
		पूर्ण,
		.obj = &vlan->obj,
	पूर्ण;
	पूर्णांक err;

	err = nb->notअगरier_call(nb, SWITCHDEV_PORT_OBJ_ADD, &obj_info);
	वापस notअगरier_to_त्रुटि_सं(err);
पूर्ण

पूर्णांक br_vlan_replay(काष्ठा net_device *br_dev, काष्ठा net_device *dev,
		   काष्ठा notअगरier_block *nb, काष्ठा netlink_ext_ack *extack)
अणु
	काष्ठा net_bridge_vlan_group *vg;
	काष्ठा net_bridge_vlan *v;
	काष्ठा net_bridge_port *p;
	काष्ठा net_bridge *br;
	पूर्णांक err = 0;
	u16 pvid;

	ASSERT_RTNL();

	अगर (!netअगर_is_bridge_master(br_dev))
		वापस -EINVAL;

	अगर (!netअगर_is_bridge_master(dev) && !netअगर_is_bridge_port(dev))
		वापस -EINVAL;

	अगर (netअगर_is_bridge_master(dev)) अणु
		br = netdev_priv(dev);
		vg = br_vlan_group(br);
		p = शून्य;
	पूर्ण अन्यथा अणु
		p = br_port_get_rtnl(dev);
		अगर (WARN_ON(!p))
			वापस -EINVAL;
		vg = nbp_vlan_group(p);
		br = p->br;
	पूर्ण

	अगर (!vg)
		वापस 0;

	pvid = br_get_pvid(vg);

	list_क्रम_each_entry(v, &vg->vlan_list, vlist) अणु
		काष्ठा चयनdev_obj_port_vlan vlan = अणु
			.obj.orig_dev = dev,
			.obj.id = SWITCHDEV_OBJ_ID_PORT_VLAN,
			.flags = br_vlan_flags(v, pvid),
			.vid = v->vid,
		पूर्ण;

		अगर (!br_vlan_should_use(v))
			जारी;

		err = br_vlan_replay_one(nb, dev, &vlan, extack);
		अगर (err)
			वापस err;
	पूर्ण

	वापस err;
पूर्ण
EXPORT_SYMBOL_GPL(br_vlan_replay);

/* check अगर v_curr can enter a range ending in range_end */
bool br_vlan_can_enter_range(स्थिर काष्ठा net_bridge_vlan *v_curr,
			     स्थिर काष्ठा net_bridge_vlan *range_end)
अणु
	वापस v_curr->vid - range_end->vid == 1 &&
	       range_end->flags == v_curr->flags &&
	       br_vlan_opts_eq_range(v_curr, range_end);
पूर्ण

अटल पूर्णांक br_vlan_dump_dev(स्थिर काष्ठा net_device *dev,
			    काष्ठा sk_buff *skb,
			    काष्ठा netlink_callback *cb,
			    u32 dump_flags)
अणु
	काष्ठा net_bridge_vlan *v, *range_start = शून्य, *range_end = शून्य;
	bool dump_stats = !!(dump_flags & BRIDGE_VLANDB_DUMPF_STATS);
	काष्ठा net_bridge_vlan_group *vg;
	पूर्णांक idx = 0, s_idx = cb->args[1];
	काष्ठा nlmsghdr *nlh = शून्य;
	काष्ठा net_bridge_port *p;
	काष्ठा br_vlan_msg *bvm;
	काष्ठा net_bridge *br;
	पूर्णांक err = 0;
	u16 pvid;

	अगर (!netअगर_is_bridge_master(dev) && !netअगर_is_bridge_port(dev))
		वापस -EINVAL;

	अगर (netअगर_is_bridge_master(dev)) अणु
		br = netdev_priv(dev);
		vg = br_vlan_group_rcu(br);
		p = शून्य;
	पूर्ण अन्यथा अणु
		p = br_port_get_rcu(dev);
		अगर (WARN_ON(!p))
			वापस -EINVAL;
		vg = nbp_vlan_group_rcu(p);
		br = p->br;
	पूर्ण

	अगर (!vg)
		वापस 0;

	nlh = nlmsg_put(skb, NETLINK_CB(cb->skb).portid, cb->nlh->nlmsg_seq,
			RTM_NEWVLAN, माप(*bvm), NLM_F_MULTI);
	अगर (!nlh)
		वापस -EMSGSIZE;
	bvm = nlmsg_data(nlh);
	स_रखो(bvm, 0, माप(*bvm));
	bvm->family = PF_BRIDGE;
	bvm->अगरindex = dev->अगरindex;
	pvid = br_get_pvid(vg);

	/* idx must stay at range's beginning until it is filled in */
	list_क्रम_each_entry_rcu(v, &vg->vlan_list, vlist) अणु
		अगर (!br_vlan_should_use(v))
			जारी;
		अगर (idx < s_idx) अणु
			idx++;
			जारी;
		पूर्ण

		अगर (!range_start) अणु
			range_start = v;
			range_end = v;
			जारी;
		पूर्ण

		अगर (dump_stats || v->vid == pvid ||
		    !br_vlan_can_enter_range(v, range_end)) अणु
			u16 vlan_flags = br_vlan_flags(range_start, pvid);

			अगर (!br_vlan_fill_vids(skb, range_start->vid,
					       range_end->vid, range_start,
					       vlan_flags, dump_stats)) अणु
				err = -EMSGSIZE;
				अवरोध;
			पूर्ण
			/* advance number of filled vlans */
			idx += range_end->vid - range_start->vid + 1;

			range_start = v;
		पूर्ण
		range_end = v;
	पूर्ण

	/* err will be 0 and range_start will be set in 3 हालs here:
	 * - first vlan (range_start == range_end)
	 * - last vlan (range_start == range_end, not in range)
	 * - last vlan range (range_start != range_end, in range)
	 */
	अगर (!err && range_start &&
	    !br_vlan_fill_vids(skb, range_start->vid, range_end->vid,
			       range_start, br_vlan_flags(range_start, pvid),
			       dump_stats))
		err = -EMSGSIZE;

	cb->args[1] = err ? idx : 0;

	nlmsg_end(skb, nlh);

	वापस err;
पूर्ण

अटल स्थिर काष्ठा nla_policy br_vlan_db_dump_pol[BRIDGE_VLANDB_DUMP_MAX + 1] = अणु
	[BRIDGE_VLANDB_DUMP_FLAGS] = अणु .type = NLA_U32 पूर्ण,
पूर्ण;

अटल पूर्णांक br_vlan_rपंचांग_dump(काष्ठा sk_buff *skb, काष्ठा netlink_callback *cb)
अणु
	काष्ठा nlattr *dtb[BRIDGE_VLANDB_DUMP_MAX + 1];
	पूर्णांक idx = 0, err = 0, s_idx = cb->args[0];
	काष्ठा net *net = sock_net(skb->sk);
	काष्ठा br_vlan_msg *bvm;
	काष्ठा net_device *dev;
	u32 dump_flags = 0;

	err = nlmsg_parse(cb->nlh, माप(*bvm), dtb, BRIDGE_VLANDB_DUMP_MAX,
			  br_vlan_db_dump_pol, cb->extack);
	अगर (err < 0)
		वापस err;

	bvm = nlmsg_data(cb->nlh);
	अगर (dtb[BRIDGE_VLANDB_DUMP_FLAGS])
		dump_flags = nla_get_u32(dtb[BRIDGE_VLANDB_DUMP_FLAGS]);

	rcu_पढ़ो_lock();
	अगर (bvm->अगरindex) अणु
		dev = dev_get_by_index_rcu(net, bvm->अगरindex);
		अगर (!dev) अणु
			err = -ENODEV;
			जाओ out_err;
		पूर्ण
		err = br_vlan_dump_dev(dev, skb, cb, dump_flags);
		अगर (err && err != -EMSGSIZE)
			जाओ out_err;
	पूर्ण अन्यथा अणु
		क्रम_each_netdev_rcu(net, dev) अणु
			अगर (idx < s_idx)
				जाओ skip;

			err = br_vlan_dump_dev(dev, skb, cb, dump_flags);
			अगर (err == -EMSGSIZE)
				अवरोध;
skip:
			idx++;
		पूर्ण
	पूर्ण
	cb->args[0] = idx;
	rcu_पढ़ो_unlock();

	वापस skb->len;

out_err:
	rcu_पढ़ो_unlock();

	वापस err;
पूर्ण

अटल स्थिर काष्ठा nla_policy br_vlan_db_policy[BRIDGE_VLANDB_ENTRY_MAX + 1] = अणु
	[BRIDGE_VLANDB_ENTRY_INFO]	=
		NLA_POLICY_EXACT_LEN(माप(काष्ठा bridge_vlan_info)),
	[BRIDGE_VLANDB_ENTRY_RANGE]	= अणु .type = NLA_U16 पूर्ण,
	[BRIDGE_VLANDB_ENTRY_STATE]	= अणु .type = NLA_U8 पूर्ण,
	[BRIDGE_VLANDB_ENTRY_TUNNEL_INFO] = अणु .type = NLA_NESTED पूर्ण,
पूर्ण;

अटल पूर्णांक br_vlan_rपंचांग_process_one(काष्ठा net_device *dev,
				   स्थिर काष्ठा nlattr *attr,
				   पूर्णांक cmd, काष्ठा netlink_ext_ack *extack)
अणु
	काष्ठा bridge_vlan_info *vinfo, vrange_end, *vinfo_last = शून्य;
	काष्ठा nlattr *tb[BRIDGE_VLANDB_ENTRY_MAX + 1];
	bool changed = false, skip_processing = false;
	काष्ठा net_bridge_vlan_group *vg;
	काष्ठा net_bridge_port *p = शून्य;
	पूर्णांक err = 0, cmdmap = 0;
	काष्ठा net_bridge *br;

	अगर (netअगर_is_bridge_master(dev)) अणु
		br = netdev_priv(dev);
		vg = br_vlan_group(br);
	पूर्ण अन्यथा अणु
		p = br_port_get_rtnl(dev);
		अगर (WARN_ON(!p))
			वापस -ENODEV;
		br = p->br;
		vg = nbp_vlan_group(p);
	पूर्ण

	अगर (WARN_ON(!vg))
		वापस -ENODEV;

	err = nla_parse_nested(tb, BRIDGE_VLANDB_ENTRY_MAX, attr,
			       br_vlan_db_policy, extack);
	अगर (err)
		वापस err;

	अगर (!tb[BRIDGE_VLANDB_ENTRY_INFO]) अणु
		NL_SET_ERR_MSG_MOD(extack, "Missing vlan entry info");
		वापस -EINVAL;
	पूर्ण
	स_रखो(&vrange_end, 0, माप(vrange_end));

	vinfo = nla_data(tb[BRIDGE_VLANDB_ENTRY_INFO]);
	अगर (vinfo->flags & (BRIDGE_VLAN_INFO_RANGE_BEGIN |
			    BRIDGE_VLAN_INFO_RANGE_END)) अणु
		NL_SET_ERR_MSG_MOD(extack, "Old-style vlan ranges are not allowed when using RTM vlan calls");
		वापस -EINVAL;
	पूर्ण
	अगर (!br_vlan_valid_id(vinfo->vid, extack))
		वापस -EINVAL;

	अगर (tb[BRIDGE_VLANDB_ENTRY_RANGE]) अणु
		vrange_end.vid = nla_get_u16(tb[BRIDGE_VLANDB_ENTRY_RANGE]);
		/* validate user-provided flags without RANGE_BEGIN */
		vrange_end.flags = BRIDGE_VLAN_INFO_RANGE_END | vinfo->flags;
		vinfo->flags |= BRIDGE_VLAN_INFO_RANGE_BEGIN;

		/* vinfo_last is the range start, vinfo the range end */
		vinfo_last = vinfo;
		vinfo = &vrange_end;

		अगर (!br_vlan_valid_id(vinfo->vid, extack) ||
		    !br_vlan_valid_range(vinfo, vinfo_last, extack))
			वापस -EINVAL;
	पूर्ण

	चयन (cmd) अणु
	हाल RTM_NEWVLAN:
		cmdmap = RTM_SETLINK;
		skip_processing = !!(vinfo->flags & BRIDGE_VLAN_INFO_ONLY_OPTS);
		अवरोध;
	हाल RTM_DELVLAN:
		cmdmap = RTM_DELLINK;
		अवरोध;
	पूर्ण

	अगर (!skip_processing) अणु
		काष्ठा bridge_vlan_info *पंचांगp_last = vinfo_last;

		/* br_process_vlan_info may overग_लिखो vinfo_last */
		err = br_process_vlan_info(br, p, cmdmap, vinfo, &पंचांगp_last,
					   &changed, extack);

		/* notअगरy first अगर anything changed */
		अगर (changed)
			br_अगरinfo_notअगरy(cmdmap, br, p);

		अगर (err)
			वापस err;
	पूर्ण

	/* deal with options */
	अगर (cmd == RTM_NEWVLAN) अणु
		काष्ठा net_bridge_vlan *range_start, *range_end;

		अगर (vinfo_last) अणु
			range_start = br_vlan_find(vg, vinfo_last->vid);
			range_end = br_vlan_find(vg, vinfo->vid);
		पूर्ण अन्यथा अणु
			range_start = br_vlan_find(vg, vinfo->vid);
			range_end = range_start;
		पूर्ण

		err = br_vlan_process_options(br, p, range_start, range_end,
					      tb, extack);
	पूर्ण

	वापस err;
पूर्ण

अटल पूर्णांक br_vlan_rपंचांग_process(काष्ठा sk_buff *skb, काष्ठा nlmsghdr *nlh,
			       काष्ठा netlink_ext_ack *extack)
अणु
	काष्ठा net *net = sock_net(skb->sk);
	काष्ठा br_vlan_msg *bvm;
	काष्ठा net_device *dev;
	काष्ठा nlattr *attr;
	पूर्णांक err, vlans = 0;
	पूर्णांक rem;

	/* this should validate the header and check क्रम reमुख्यing bytes */
	err = nlmsg_parse(nlh, माप(*bvm), शून्य, BRIDGE_VLANDB_MAX, शून्य,
			  extack);
	अगर (err < 0)
		वापस err;

	bvm = nlmsg_data(nlh);
	dev = __dev_get_by_index(net, bvm->अगरindex);
	अगर (!dev)
		वापस -ENODEV;

	अगर (!netअगर_is_bridge_master(dev) && !netअगर_is_bridge_port(dev)) अणु
		NL_SET_ERR_MSG_MOD(extack, "The device is not a valid bridge or bridge port");
		वापस -EINVAL;
	पूर्ण

	nlmsg_क्रम_each_attr(attr, nlh, माप(*bvm), rem) अणु
		अगर (nla_type(attr) != BRIDGE_VLANDB_ENTRY)
			जारी;

		vlans++;
		err = br_vlan_rपंचांग_process_one(dev, attr, nlh->nlmsg_type,
					      extack);
		अगर (err)
			अवरोध;
	पूर्ण
	अगर (!vlans) अणु
		NL_SET_ERR_MSG_MOD(extack, "No vlans found to process");
		err = -EINVAL;
	पूर्ण

	वापस err;
पूर्ण

व्योम br_vlan_rtnl_init(व्योम)
अणु
	rtnl_रेजिस्टर_module(THIS_MODULE, PF_BRIDGE, RTM_GETVLAN, शून्य,
			     br_vlan_rपंचांग_dump, 0);
	rtnl_रेजिस्टर_module(THIS_MODULE, PF_BRIDGE, RTM_NEWVLAN,
			     br_vlan_rपंचांग_process, शून्य, 0);
	rtnl_रेजिस्टर_module(THIS_MODULE, PF_BRIDGE, RTM_DELVLAN,
			     br_vlan_rपंचांग_process, शून्य, 0);
पूर्ण

व्योम br_vlan_rtnl_uninit(व्योम)
अणु
	rtnl_unरेजिस्टर(PF_BRIDGE, RTM_GETVLAN);
	rtnl_unरेजिस्टर(PF_BRIDGE, RTM_NEWVLAN);
	rtnl_unरेजिस्टर(PF_BRIDGE, RTM_DELVLAN);
पूर्ण
