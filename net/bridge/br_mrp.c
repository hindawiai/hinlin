<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later

#समावेश <linux/mrp_bridge.h>
#समावेश "br_private_mrp.h"

अटल स्थिर u8 mrp_test_dmac[ETH_ALEN] = अणु 0x1, 0x15, 0x4e, 0x0, 0x0, 0x1 पूर्ण;
अटल स्थिर u8 mrp_in_test_dmac[ETH_ALEN] = अणु 0x1, 0x15, 0x4e, 0x0, 0x0, 0x3 पूर्ण;

अटल पूर्णांक br_mrp_process(काष्ठा net_bridge_port *p, काष्ठा sk_buff *skb);

अटल काष्ठा br_frame_type mrp_frame_type __पढ़ो_mostly = अणु
	.type = cpu_to_be16(ETH_P_MRP),
	.frame_handler = br_mrp_process,
पूर्ण;

अटल bool br_mrp_is_ring_port(काष्ठा net_bridge_port *p_port,
				काष्ठा net_bridge_port *s_port,
				काष्ठा net_bridge_port *port)
अणु
	अगर (port == p_port ||
	    port == s_port)
		वापस true;

	वापस false;
पूर्ण

अटल bool br_mrp_is_in_port(काष्ठा net_bridge_port *i_port,
			      काष्ठा net_bridge_port *port)
अणु
	अगर (port == i_port)
		वापस true;

	वापस false;
पूर्ण

अटल काष्ठा net_bridge_port *br_mrp_get_port(काष्ठा net_bridge *br,
					       u32 अगरindex)
अणु
	काष्ठा net_bridge_port *res = शून्य;
	काष्ठा net_bridge_port *port;

	list_क्रम_each_entry(port, &br->port_list, list) अणु
		अगर (port->dev->अगरindex == अगरindex) अणु
			res = port;
			अवरोध;
		पूर्ण
	पूर्ण

	वापस res;
पूर्ण

अटल काष्ठा br_mrp *br_mrp_find_id(काष्ठा net_bridge *br, u32 ring_id)
अणु
	काष्ठा br_mrp *res = शून्य;
	काष्ठा br_mrp *mrp;

	hlist_क्रम_each_entry_rcu(mrp, &br->mrp_list, list,
				 lockdep_rtnl_is_held()) अणु
		अगर (mrp->ring_id == ring_id) अणु
			res = mrp;
			अवरोध;
		पूर्ण
	पूर्ण

	वापस res;
पूर्ण

अटल काष्ठा br_mrp *br_mrp_find_in_id(काष्ठा net_bridge *br, u32 in_id)
अणु
	काष्ठा br_mrp *res = शून्य;
	काष्ठा br_mrp *mrp;

	hlist_क्रम_each_entry_rcu(mrp, &br->mrp_list, list,
				 lockdep_rtnl_is_held()) अणु
		अगर (mrp->in_id == in_id) अणु
			res = mrp;
			अवरोध;
		पूर्ण
	पूर्ण

	वापस res;
पूर्ण

अटल bool br_mrp_unique_अगरindex(काष्ठा net_bridge *br, u32 अगरindex)
अणु
	काष्ठा br_mrp *mrp;

	hlist_क्रम_each_entry_rcu(mrp, &br->mrp_list, list,
				 lockdep_rtnl_is_held()) अणु
		काष्ठा net_bridge_port *p;

		p = rtnl_dereference(mrp->p_port);
		अगर (p && p->dev->अगरindex == अगरindex)
			वापस false;

		p = rtnl_dereference(mrp->s_port);
		अगर (p && p->dev->अगरindex == अगरindex)
			वापस false;

		p = rtnl_dereference(mrp->i_port);
		अगर (p && p->dev->अगरindex == अगरindex)
			वापस false;
	पूर्ण

	वापस true;
पूर्ण

अटल काष्ठा br_mrp *br_mrp_find_port(काष्ठा net_bridge *br,
				       काष्ठा net_bridge_port *p)
अणु
	काष्ठा br_mrp *res = शून्य;
	काष्ठा br_mrp *mrp;

	hlist_क्रम_each_entry_rcu(mrp, &br->mrp_list, list,
				 lockdep_rtnl_is_held()) अणु
		अगर (rcu_access_poपूर्णांकer(mrp->p_port) == p ||
		    rcu_access_poपूर्णांकer(mrp->s_port) == p ||
		    rcu_access_poपूर्णांकer(mrp->i_port) == p) अणु
			res = mrp;
			अवरोध;
		पूर्ण
	पूर्ण

	वापस res;
पूर्ण

अटल पूर्णांक br_mrp_next_seq(काष्ठा br_mrp *mrp)
अणु
	mrp->seq_id++;
	वापस mrp->seq_id;
पूर्ण

अटल काष्ठा sk_buff *br_mrp_skb_alloc(काष्ठा net_bridge_port *p,
					स्थिर u8 *src, स्थिर u8 *dst)
अणु
	काष्ठा ethhdr *eth_hdr;
	काष्ठा sk_buff *skb;
	__be16 *version;

	skb = dev_alloc_skb(MRP_MAX_FRAME_LENGTH);
	अगर (!skb)
		वापस शून्य;

	skb->dev = p->dev;
	skb->protocol = htons(ETH_P_MRP);
	skb->priority = MRP_FRAME_PRIO;
	skb_reserve(skb, माप(*eth_hdr));

	eth_hdr = skb_push(skb, माप(*eth_hdr));
	ether_addr_copy(eth_hdr->h_dest, dst);
	ether_addr_copy(eth_hdr->h_source, src);
	eth_hdr->h_proto = htons(ETH_P_MRP);

	version = skb_put(skb, माप(*version));
	*version = cpu_to_be16(MRP_VERSION);

	वापस skb;
पूर्ण

अटल व्योम br_mrp_skb_tlv(काष्ठा sk_buff *skb,
			   क्रमागत br_mrp_tlv_header_type type,
			   u8 length)
अणु
	काष्ठा br_mrp_tlv_hdr *hdr;

	hdr = skb_put(skb, माप(*hdr));
	hdr->type = type;
	hdr->length = length;
पूर्ण

अटल व्योम br_mrp_skb_common(काष्ठा sk_buff *skb, काष्ठा br_mrp *mrp)
अणु
	काष्ठा br_mrp_common_hdr *hdr;

	br_mrp_skb_tlv(skb, BR_MRP_TLV_HEADER_COMMON, माप(*hdr));

	hdr = skb_put(skb, माप(*hdr));
	hdr->seq_id = cpu_to_be16(br_mrp_next_seq(mrp));
	स_रखो(hdr->करोमुख्य, 0xff, MRP_DOMAIN_UUID_LENGTH);
पूर्ण

अटल काष्ठा sk_buff *br_mrp_alloc_test_skb(काष्ठा br_mrp *mrp,
					     काष्ठा net_bridge_port *p,
					     क्रमागत br_mrp_port_role_type port_role)
अणु
	काष्ठा br_mrp_ring_test_hdr *hdr = शून्य;
	काष्ठा sk_buff *skb = शून्य;

	अगर (!p)
		वापस शून्य;

	skb = br_mrp_skb_alloc(p, p->dev->dev_addr, mrp_test_dmac);
	अगर (!skb)
		वापस शून्य;

	br_mrp_skb_tlv(skb, BR_MRP_TLV_HEADER_RING_TEST, माप(*hdr));
	hdr = skb_put(skb, माप(*hdr));

	hdr->prio = cpu_to_be16(mrp->prio);
	ether_addr_copy(hdr->sa, p->br->dev->dev_addr);
	hdr->port_role = cpu_to_be16(port_role);
	hdr->state = cpu_to_be16(mrp->ring_state);
	hdr->transitions = cpu_to_be16(mrp->ring_transitions);
	hdr->बारtamp = cpu_to_be32(jअगरfies_to_msecs(jअगरfies));

	br_mrp_skb_common(skb, mrp);
	br_mrp_skb_tlv(skb, BR_MRP_TLV_HEADER_END, 0x0);

	वापस skb;
पूर्ण

अटल काष्ठा sk_buff *br_mrp_alloc_in_test_skb(काष्ठा br_mrp *mrp,
						काष्ठा net_bridge_port *p,
						क्रमागत br_mrp_port_role_type port_role)
अणु
	काष्ठा br_mrp_in_test_hdr *hdr = शून्य;
	काष्ठा sk_buff *skb = शून्य;

	अगर (!p)
		वापस शून्य;

	skb = br_mrp_skb_alloc(p, p->dev->dev_addr, mrp_in_test_dmac);
	अगर (!skb)
		वापस शून्य;

	br_mrp_skb_tlv(skb, BR_MRP_TLV_HEADER_IN_TEST, माप(*hdr));
	hdr = skb_put(skb, माप(*hdr));

	hdr->id = cpu_to_be16(mrp->in_id);
	ether_addr_copy(hdr->sa, p->br->dev->dev_addr);
	hdr->port_role = cpu_to_be16(port_role);
	hdr->state = cpu_to_be16(mrp->in_state);
	hdr->transitions = cpu_to_be16(mrp->in_transitions);
	hdr->बारtamp = cpu_to_be32(jअगरfies_to_msecs(jअगरfies));

	br_mrp_skb_common(skb, mrp);
	br_mrp_skb_tlv(skb, BR_MRP_TLV_HEADER_END, 0x0);

	वापस skb;
पूर्ण

/* This function is continuously called in the following हालs:
 * - when node role is MRM, in this हाल test_monitor is always set to false
 *   because it needs to notअगरy the userspace that the ring is खोलो and needs to
 *   send MRP_Test frames
 * - when node role is MRA, there are 2 subहालs:
 *     - when MRA behaves as MRM, in this हाल is similar with MRM role
 *     - when MRA behaves as MRC, in this हाल test_monitor is set to true,
 *       because it needs to detect when it stops seeing MRP_Test frames
 *       from MRM node but it करोesn't need to send MRP_Test frames.
 */
अटल व्योम br_mrp_test_work_expired(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा delayed_work *del_work = to_delayed_work(work);
	काष्ठा br_mrp *mrp = container_of(del_work, काष्ठा br_mrp, test_work);
	काष्ठा net_bridge_port *p;
	bool notअगरy_खोलो = false;
	काष्ठा sk_buff *skb;

	अगर (समय_beक्रमe_eq(mrp->test_end, jअगरfies))
		वापस;

	अगर (mrp->test_count_miss < mrp->test_max_miss) अणु
		mrp->test_count_miss++;
	पूर्ण अन्यथा अणु
		/* Notअगरy that the ring is खोलो only अगर the ring state is
		 * बंदd, otherwise it would जारी to notअगरy at every
		 * पूर्णांकerval.
		 * Also notअगरy that the ring is खोलो when the node has the
		 * role MRA and behaves as MRC. The reason is that the
		 * userspace needs to know when the MRM stopped sending
		 * MRP_Test frames so that the current node to try to take
		 * the role of a MRM.
		 */
		अगर (mrp->ring_state == BR_MRP_RING_STATE_CLOSED ||
		    mrp->test_monitor)
			notअगरy_खोलो = true;
	पूर्ण

	rcu_पढ़ो_lock();

	p = rcu_dereference(mrp->p_port);
	अगर (p) अणु
		अगर (!mrp->test_monitor) अणु
			skb = br_mrp_alloc_test_skb(mrp, p,
						    BR_MRP_PORT_ROLE_PRIMARY);
			अगर (!skb)
				जाओ out;

			skb_reset_network_header(skb);
			dev_queue_xmit(skb);
		पूर्ण

		अगर (notअगरy_खोलो && !mrp->ring_role_offloaded)
			br_mrp_ring_port_खोलो(p->dev, true);
	पूर्ण

	p = rcu_dereference(mrp->s_port);
	अगर (p) अणु
		अगर (!mrp->test_monitor) अणु
			skb = br_mrp_alloc_test_skb(mrp, p,
						    BR_MRP_PORT_ROLE_SECONDARY);
			अगर (!skb)
				जाओ out;

			skb_reset_network_header(skb);
			dev_queue_xmit(skb);
		पूर्ण

		अगर (notअगरy_खोलो && !mrp->ring_role_offloaded)
			br_mrp_ring_port_खोलो(p->dev, true);
	पूर्ण

out:
	rcu_पढ़ो_unlock();

	queue_delayed_work(प्रणाली_wq, &mrp->test_work,
			   usecs_to_jअगरfies(mrp->test_पूर्णांकerval));
पूर्ण

/* This function is continuously called when the node has the पूर्णांकerconnect role
 * MIM. It would generate पूर्णांकerconnect test frames and will send them on all 3
 * ports. But will also check अगर it stop receiving पूर्णांकerconnect test frames.
 */
अटल व्योम br_mrp_in_test_work_expired(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा delayed_work *del_work = to_delayed_work(work);
	काष्ठा br_mrp *mrp = container_of(del_work, काष्ठा br_mrp, in_test_work);
	काष्ठा net_bridge_port *p;
	bool notअगरy_खोलो = false;
	काष्ठा sk_buff *skb;

	अगर (समय_beक्रमe_eq(mrp->in_test_end, jअगरfies))
		वापस;

	अगर (mrp->in_test_count_miss < mrp->in_test_max_miss) अणु
		mrp->in_test_count_miss++;
	पूर्ण अन्यथा अणु
		/* Notअगरy that the पूर्णांकerconnect ring is खोलो only अगर the
		 * पूर्णांकerconnect ring state is बंदd, otherwise it would
		 * जारी to notअगरy at every पूर्णांकerval.
		 */
		अगर (mrp->in_state == BR_MRP_IN_STATE_CLOSED)
			notअगरy_खोलो = true;
	पूर्ण

	rcu_पढ़ो_lock();

	p = rcu_dereference(mrp->p_port);
	अगर (p) अणु
		skb = br_mrp_alloc_in_test_skb(mrp, p,
					       BR_MRP_PORT_ROLE_PRIMARY);
		अगर (!skb)
			जाओ out;

		skb_reset_network_header(skb);
		dev_queue_xmit(skb);

		अगर (notअगरy_खोलो && !mrp->in_role_offloaded)
			br_mrp_in_port_खोलो(p->dev, true);
	पूर्ण

	p = rcu_dereference(mrp->s_port);
	अगर (p) अणु
		skb = br_mrp_alloc_in_test_skb(mrp, p,
					       BR_MRP_PORT_ROLE_SECONDARY);
		अगर (!skb)
			जाओ out;

		skb_reset_network_header(skb);
		dev_queue_xmit(skb);

		अगर (notअगरy_खोलो && !mrp->in_role_offloaded)
			br_mrp_in_port_खोलो(p->dev, true);
	पूर्ण

	p = rcu_dereference(mrp->i_port);
	अगर (p) अणु
		skb = br_mrp_alloc_in_test_skb(mrp, p,
					       BR_MRP_PORT_ROLE_INTER);
		अगर (!skb)
			जाओ out;

		skb_reset_network_header(skb);
		dev_queue_xmit(skb);

		अगर (notअगरy_खोलो && !mrp->in_role_offloaded)
			br_mrp_in_port_खोलो(p->dev, true);
	पूर्ण

out:
	rcu_पढ़ो_unlock();

	queue_delayed_work(प्रणाली_wq, &mrp->in_test_work,
			   usecs_to_jअगरfies(mrp->in_test_पूर्णांकerval));
पूर्ण

/* Deletes the MRP instance.
 * note: called under rtnl_lock
 */
अटल व्योम br_mrp_del_impl(काष्ठा net_bridge *br, काष्ठा br_mrp *mrp)
अणु
	काष्ठा net_bridge_port *p;
	u8 state;

	/* Stop sending MRP_Test frames */
	cancel_delayed_work_sync(&mrp->test_work);
	br_mrp_चयनdev_send_ring_test(br, mrp, 0, 0, 0, 0);

	/* Stop sending MRP_InTest frames अगर has an पूर्णांकerconnect role */
	cancel_delayed_work_sync(&mrp->in_test_work);
	br_mrp_चयनdev_send_in_test(br, mrp, 0, 0, 0);

	/* Disable the roles */
	br_mrp_चयनdev_set_ring_role(br, mrp, BR_MRP_RING_ROLE_DISABLED);
	p = rtnl_dereference(mrp->i_port);
	अगर (p)
		br_mrp_चयनdev_set_in_role(br, mrp, mrp->in_id, mrp->ring_id,
					     BR_MRP_IN_ROLE_DISABLED);

	br_mrp_चयनdev_del(br, mrp);

	/* Reset the ports */
	p = rtnl_dereference(mrp->p_port);
	अगर (p) अणु
		spin_lock_bh(&br->lock);
		state = netअगर_running(br->dev) ?
				BR_STATE_FORWARDING : BR_STATE_DISABLED;
		p->state = state;
		p->flags &= ~BR_MRP_AWARE;
		spin_unlock_bh(&br->lock);
		br_mrp_port_चयनdev_set_state(p, state);
		rcu_assign_poपूर्णांकer(mrp->p_port, शून्य);
	पूर्ण

	p = rtnl_dereference(mrp->s_port);
	अगर (p) अणु
		spin_lock_bh(&br->lock);
		state = netअगर_running(br->dev) ?
				BR_STATE_FORWARDING : BR_STATE_DISABLED;
		p->state = state;
		p->flags &= ~BR_MRP_AWARE;
		spin_unlock_bh(&br->lock);
		br_mrp_port_चयनdev_set_state(p, state);
		rcu_assign_poपूर्णांकer(mrp->s_port, शून्य);
	पूर्ण

	p = rtnl_dereference(mrp->i_port);
	अगर (p) अणु
		spin_lock_bh(&br->lock);
		state = netअगर_running(br->dev) ?
				BR_STATE_FORWARDING : BR_STATE_DISABLED;
		p->state = state;
		p->flags &= ~BR_MRP_AWARE;
		spin_unlock_bh(&br->lock);
		br_mrp_port_चयनdev_set_state(p, state);
		rcu_assign_poपूर्णांकer(mrp->i_port, शून्य);
	पूर्ण

	hlist_del_rcu(&mrp->list);
	kमुक्त_rcu(mrp, rcu);

	अगर (hlist_empty(&br->mrp_list))
		br_del_frame(br, &mrp_frame_type);
पूर्ण

/* Adds a new MRP instance.
 * note: called under rtnl_lock
 */
पूर्णांक br_mrp_add(काष्ठा net_bridge *br, काष्ठा br_mrp_instance *instance)
अणु
	काष्ठा net_bridge_port *p;
	काष्ठा br_mrp *mrp;
	पूर्णांक err;

	/* If the ring exists, it is not possible to create another one with the
	 * same ring_id
	 */
	mrp = br_mrp_find_id(br, instance->ring_id);
	अगर (mrp)
		वापस -EINVAL;

	अगर (!br_mrp_get_port(br, instance->p_अगरindex) ||
	    !br_mrp_get_port(br, instance->s_अगरindex))
		वापस -EINVAL;

	/* It is not possible to have the same port part of multiple rings */
	अगर (!br_mrp_unique_अगरindex(br, instance->p_अगरindex) ||
	    !br_mrp_unique_अगरindex(br, instance->s_अगरindex))
		वापस -EINVAL;

	mrp = kzalloc(माप(*mrp), GFP_KERNEL);
	अगर (!mrp)
		वापस -ENOMEM;

	mrp->ring_id = instance->ring_id;
	mrp->prio = instance->prio;

	p = br_mrp_get_port(br, instance->p_अगरindex);
	spin_lock_bh(&br->lock);
	p->state = BR_STATE_FORWARDING;
	p->flags |= BR_MRP_AWARE;
	spin_unlock_bh(&br->lock);
	rcu_assign_poपूर्णांकer(mrp->p_port, p);

	p = br_mrp_get_port(br, instance->s_अगरindex);
	spin_lock_bh(&br->lock);
	p->state = BR_STATE_FORWARDING;
	p->flags |= BR_MRP_AWARE;
	spin_unlock_bh(&br->lock);
	rcu_assign_poपूर्णांकer(mrp->s_port, p);

	अगर (hlist_empty(&br->mrp_list))
		br_add_frame(br, &mrp_frame_type);

	INIT_DELAYED_WORK(&mrp->test_work, br_mrp_test_work_expired);
	INIT_DELAYED_WORK(&mrp->in_test_work, br_mrp_in_test_work_expired);
	hlist_add_tail_rcu(&mrp->list, &br->mrp_list);

	err = br_mrp_चयनdev_add(br, mrp);
	अगर (err)
		जाओ delete_mrp;

	वापस 0;

delete_mrp:
	br_mrp_del_impl(br, mrp);

	वापस err;
पूर्ण

/* Deletes the MRP instance from which the port is part of
 * note: called under rtnl_lock
 */
व्योम br_mrp_port_del(काष्ठा net_bridge *br, काष्ठा net_bridge_port *p)
अणु
	काष्ठा br_mrp *mrp = br_mrp_find_port(br, p);

	/* If the port is not part of a MRP instance just bail out */
	अगर (!mrp)
		वापस;

	br_mrp_del_impl(br, mrp);
पूर्ण

/* Deletes existing MRP instance based on ring_id
 * note: called under rtnl_lock
 */
पूर्णांक br_mrp_del(काष्ठा net_bridge *br, काष्ठा br_mrp_instance *instance)
अणु
	काष्ठा br_mrp *mrp = br_mrp_find_id(br, instance->ring_id);

	अगर (!mrp)
		वापस -EINVAL;

	br_mrp_del_impl(br, mrp);

	वापस 0;
पूर्ण

/* Set port state, port state can be क्रमwarding, blocked or disabled
 * note: alपढ़ोy called with rtnl_lock
 */
पूर्णांक br_mrp_set_port_state(काष्ठा net_bridge_port *p,
			  क्रमागत br_mrp_port_state_type state)
अणु
	u32 port_state;

	अगर (!p || !(p->flags & BR_MRP_AWARE))
		वापस -EINVAL;

	spin_lock_bh(&p->br->lock);

	अगर (state == BR_MRP_PORT_STATE_FORWARDING)
		port_state = BR_STATE_FORWARDING;
	अन्यथा
		port_state = BR_STATE_BLOCKING;

	p->state = port_state;
	spin_unlock_bh(&p->br->lock);

	br_mrp_port_चयनdev_set_state(p, port_state);

	वापस 0;
पूर्ण

/* Set port role, port role can be primary or secondary
 * note: alपढ़ोy called with rtnl_lock
 */
पूर्णांक br_mrp_set_port_role(काष्ठा net_bridge_port *p,
			 क्रमागत br_mrp_port_role_type role)
अणु
	काष्ठा br_mrp *mrp;

	अगर (!p || !(p->flags & BR_MRP_AWARE))
		वापस -EINVAL;

	mrp = br_mrp_find_port(p->br, p);

	अगर (!mrp)
		वापस -EINVAL;

	चयन (role) अणु
	हाल BR_MRP_PORT_ROLE_PRIMARY:
		rcu_assign_poपूर्णांकer(mrp->p_port, p);
		अवरोध;
	हाल BR_MRP_PORT_ROLE_SECONDARY:
		rcu_assign_poपूर्णांकer(mrp->s_port, p);
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	br_mrp_port_चयनdev_set_role(p, role);

	वापस 0;
पूर्ण

/* Set ring state, ring state can be only Open or Closed
 * note: alपढ़ोy called with rtnl_lock
 */
पूर्णांक br_mrp_set_ring_state(काष्ठा net_bridge *br,
			  काष्ठा br_mrp_ring_state *state)
अणु
	काष्ठा br_mrp *mrp = br_mrp_find_id(br, state->ring_id);

	अगर (!mrp)
		वापस -EINVAL;

	अगर (mrp->ring_state == BR_MRP_RING_STATE_CLOSED &&
	    state->ring_state != BR_MRP_RING_STATE_CLOSED)
		mrp->ring_transitions++;

	mrp->ring_state = state->ring_state;

	br_mrp_चयनdev_set_ring_state(br, mrp, state->ring_state);

	वापस 0;
पूर्ण

/* Set ring role, ring role can be only MRM(Media Redundancy Manager) or
 * MRC(Media Redundancy Client).
 * note: alपढ़ोy called with rtnl_lock
 */
पूर्णांक br_mrp_set_ring_role(काष्ठा net_bridge *br,
			 काष्ठा br_mrp_ring_role *role)
अणु
	काष्ठा br_mrp *mrp = br_mrp_find_id(br, role->ring_id);
	क्रमागत br_mrp_hw_support support;

	अगर (!mrp)
		वापस -EINVAL;

	mrp->ring_role = role->ring_role;

	/* If there is an error just bailed out */
	support = br_mrp_चयनdev_set_ring_role(br, mrp, role->ring_role);
	अगर (support == BR_MRP_NONE)
		वापस -EOPNOTSUPP;

	/* Now detect अगर the HW actually applied the role or not. If the HW
	 * applied the role it means that the SW will not to करो those operations
	 * anymore. For example अगर the role ir MRM then the HW will notअगरy the
	 * SW when ring is खोलो, but अगर the is not pushed to the HW the SW will
	 * need to detect when the ring is खोलो
	 */
	mrp->ring_role_offloaded = support == BR_MRP_SW ? 0 : 1;

	वापस 0;
पूर्ण

/* Start to generate or monitor MRP test frames, the frames are generated by
 * HW and अगर it fails, they are generated by the SW.
 * note: alपढ़ोy called with rtnl_lock
 */
पूर्णांक br_mrp_start_test(काष्ठा net_bridge *br,
		      काष्ठा br_mrp_start_test *test)
अणु
	काष्ठा br_mrp *mrp = br_mrp_find_id(br, test->ring_id);
	क्रमागत br_mrp_hw_support support;

	अगर (!mrp)
		वापस -EINVAL;

	/* Try to push it to the HW and अगर it fails then जारी with SW
	 * implementation and अगर that also fails then वापस error.
	 */
	support = br_mrp_चयनdev_send_ring_test(br, mrp, test->पूर्णांकerval,
						  test->max_miss, test->period,
						  test->monitor);
	अगर (support == BR_MRP_NONE)
		वापस -EOPNOTSUPP;

	अगर (support == BR_MRP_HW)
		वापस 0;

	mrp->test_पूर्णांकerval = test->पूर्णांकerval;
	mrp->test_end = jअगरfies + usecs_to_jअगरfies(test->period);
	mrp->test_max_miss = test->max_miss;
	mrp->test_monitor = test->monitor;
	mrp->test_count_miss = 0;
	queue_delayed_work(प्रणाली_wq, &mrp->test_work,
			   usecs_to_jअगरfies(test->पूर्णांकerval));

	वापस 0;
पूर्ण

/* Set in state, पूर्णांक state can be only Open or Closed
 * note: alपढ़ोy called with rtnl_lock
 */
पूर्णांक br_mrp_set_in_state(काष्ठा net_bridge *br, काष्ठा br_mrp_in_state *state)
अणु
	काष्ठा br_mrp *mrp = br_mrp_find_in_id(br, state->in_id);

	अगर (!mrp)
		वापस -EINVAL;

	अगर (mrp->in_state == BR_MRP_IN_STATE_CLOSED &&
	    state->in_state != BR_MRP_IN_STATE_CLOSED)
		mrp->in_transitions++;

	mrp->in_state = state->in_state;

	br_mrp_चयनdev_set_in_state(br, mrp, state->in_state);

	वापस 0;
पूर्ण

/* Set in role, in role can be only MIM(Media Interconnection Manager) or
 * MIC(Media Interconnection Client).
 * note: alपढ़ोy called with rtnl_lock
 */
पूर्णांक br_mrp_set_in_role(काष्ठा net_bridge *br, काष्ठा br_mrp_in_role *role)
अणु
	काष्ठा br_mrp *mrp = br_mrp_find_id(br, role->ring_id);
	क्रमागत br_mrp_hw_support support;
	काष्ठा net_bridge_port *p;

	अगर (!mrp)
		वापस -EINVAL;

	अगर (!br_mrp_get_port(br, role->i_अगरindex))
		वापस -EINVAL;

	अगर (role->in_role == BR_MRP_IN_ROLE_DISABLED) अणु
		u8 state;

		/* It is not allowed to disable a port that करोesn't exist */
		p = rtnl_dereference(mrp->i_port);
		अगर (!p)
			वापस -EINVAL;

		/* Stop the generating MRP_InTest frames */
		cancel_delayed_work_sync(&mrp->in_test_work);
		br_mrp_चयनdev_send_in_test(br, mrp, 0, 0, 0);

		/* Remove the port */
		spin_lock_bh(&br->lock);
		state = netअगर_running(br->dev) ?
				BR_STATE_FORWARDING : BR_STATE_DISABLED;
		p->state = state;
		p->flags &= ~BR_MRP_AWARE;
		spin_unlock_bh(&br->lock);
		br_mrp_port_चयनdev_set_state(p, state);
		rcu_assign_poपूर्णांकer(mrp->i_port, शून्य);

		mrp->in_role = role->in_role;
		mrp->in_id = 0;

		वापस 0;
	पूर्ण

	/* It is not possible to have the same port part of multiple rings */
	अगर (!br_mrp_unique_अगरindex(br, role->i_अगरindex))
		वापस -EINVAL;

	/* It is not allowed to set a dअगरferent पूर्णांकerconnect port अगर the mrp
	 * instance has alपढ़ोy one. First it needs to be disabled and after
	 * that set the new port
	 */
	अगर (rcu_access_poपूर्णांकer(mrp->i_port))
		वापस -EINVAL;

	p = br_mrp_get_port(br, role->i_अगरindex);
	spin_lock_bh(&br->lock);
	p->state = BR_STATE_FORWARDING;
	p->flags |= BR_MRP_AWARE;
	spin_unlock_bh(&br->lock);
	rcu_assign_poपूर्णांकer(mrp->i_port, p);

	mrp->in_role = role->in_role;
	mrp->in_id = role->in_id;

	/* If there is an error just bailed out */
	support = br_mrp_चयनdev_set_in_role(br, mrp, role->in_id,
					       role->ring_id, role->in_role);
	अगर (support == BR_MRP_NONE)
		वापस -EOPNOTSUPP;

	/* Now detect अगर the HW actually applied the role or not. If the HW
	 * applied the role it means that the SW will not to करो those operations
	 * anymore. For example अगर the role is MIM then the HW will notअगरy the
	 * SW when पूर्णांकerconnect ring is खोलो, but अगर the is not pushed to the HW
	 * the SW will need to detect when the पूर्णांकerconnect ring is खोलो.
	 */
	mrp->in_role_offloaded = support == BR_MRP_SW ? 0 : 1;

	वापस 0;
पूर्ण

/* Start to generate MRP_InTest frames, the frames are generated by
 * HW and अगर it fails, they are generated by the SW.
 * note: alपढ़ोy called with rtnl_lock
 */
पूर्णांक br_mrp_start_in_test(काष्ठा net_bridge *br,
			 काष्ठा br_mrp_start_in_test *in_test)
अणु
	काष्ठा br_mrp *mrp = br_mrp_find_in_id(br, in_test->in_id);
	क्रमागत br_mrp_hw_support support;

	अगर (!mrp)
		वापस -EINVAL;

	अगर (mrp->in_role != BR_MRP_IN_ROLE_MIM)
		वापस -EINVAL;

	/* Try to push it to the HW and अगर it fails then जारी with SW
	 * implementation and अगर that also fails then वापस error.
	 */
	support =  br_mrp_चयनdev_send_in_test(br, mrp, in_test->पूर्णांकerval,
						 in_test->max_miss,
						 in_test->period);
	अगर (support == BR_MRP_NONE)
		वापस -EOPNOTSUPP;

	अगर (support == BR_MRP_HW)
		वापस 0;

	mrp->in_test_पूर्णांकerval = in_test->पूर्णांकerval;
	mrp->in_test_end = jअगरfies + usecs_to_jअगरfies(in_test->period);
	mrp->in_test_max_miss = in_test->max_miss;
	mrp->in_test_count_miss = 0;
	queue_delayed_work(प्रणाली_wq, &mrp->in_test_work,
			   usecs_to_jअगरfies(in_test->पूर्णांकerval));

	वापस 0;
पूर्ण

/* Determine अगर the frame type is a ring frame */
अटल bool br_mrp_ring_frame(काष्ठा sk_buff *skb)
अणु
	स्थिर काष्ठा br_mrp_tlv_hdr *hdr;
	काष्ठा br_mrp_tlv_hdr _hdr;

	hdr = skb_header_poपूर्णांकer(skb, माप(uपूर्णांक16_t), माप(_hdr), &_hdr);
	अगर (!hdr)
		वापस false;

	अगर (hdr->type == BR_MRP_TLV_HEADER_RING_TEST ||
	    hdr->type == BR_MRP_TLV_HEADER_RING_TOPO ||
	    hdr->type == BR_MRP_TLV_HEADER_RING_LINK_DOWN ||
	    hdr->type == BR_MRP_TLV_HEADER_RING_LINK_UP ||
	    hdr->type == BR_MRP_TLV_HEADER_OPTION)
		वापस true;

	वापस false;
पूर्ण

/* Determine अगर the frame type is an पूर्णांकerconnect frame */
अटल bool br_mrp_in_frame(काष्ठा sk_buff *skb)
अणु
	स्थिर काष्ठा br_mrp_tlv_hdr *hdr;
	काष्ठा br_mrp_tlv_hdr _hdr;

	hdr = skb_header_poपूर्णांकer(skb, माप(uपूर्णांक16_t), माप(_hdr), &_hdr);
	अगर (!hdr)
		वापस false;

	अगर (hdr->type == BR_MRP_TLV_HEADER_IN_TEST ||
	    hdr->type == BR_MRP_TLV_HEADER_IN_TOPO ||
	    hdr->type == BR_MRP_TLV_HEADER_IN_LINK_DOWN ||
	    hdr->type == BR_MRP_TLV_HEADER_IN_LINK_UP ||
	    hdr->type == BR_MRP_TLV_HEADER_IN_LINK_STATUS)
		वापस true;

	वापस false;
पूर्ण

/* Process only MRP Test frame. All the other MRP frames are processed by
 * userspace application
 * note: alपढ़ोy called with rcu_पढ़ो_lock
 */
अटल व्योम br_mrp_mrm_process(काष्ठा br_mrp *mrp, काष्ठा net_bridge_port *port,
			       काष्ठा sk_buff *skb)
अणु
	स्थिर काष्ठा br_mrp_tlv_hdr *hdr;
	काष्ठा br_mrp_tlv_hdr _hdr;

	/* Each MRP header starts with a version field which is 16 bits.
	 * Thereक्रमe skip the version and get directly the TLV header.
	 */
	hdr = skb_header_poपूर्णांकer(skb, माप(uपूर्णांक16_t), माप(_hdr), &_hdr);
	अगर (!hdr)
		वापस;

	अगर (hdr->type != BR_MRP_TLV_HEADER_RING_TEST)
		वापस;

	mrp->test_count_miss = 0;

	/* Notअगरy the userspace that the ring is बंदd only when the ring is
	 * not बंदd
	 */
	अगर (mrp->ring_state != BR_MRP_RING_STATE_CLOSED)
		br_mrp_ring_port_खोलो(port->dev, false);
पूर्ण

/* Determine अगर the test hdr has a better priority than the node */
अटल bool br_mrp_test_better_than_own(काष्ठा br_mrp *mrp,
					काष्ठा net_bridge *br,
					स्थिर काष्ठा br_mrp_ring_test_hdr *hdr)
अणु
	u16 prio = be16_to_cpu(hdr->prio);

	अगर (prio < mrp->prio ||
	    (prio == mrp->prio &&
	    ether_addr_to_u64(hdr->sa) < ether_addr_to_u64(br->dev->dev_addr)))
		वापस true;

	वापस false;
पूर्ण

/* Process only MRP Test frame. All the other MRP frames are processed by
 * userspace application
 * note: alपढ़ोy called with rcu_पढ़ो_lock
 */
अटल व्योम br_mrp_mra_process(काष्ठा br_mrp *mrp, काष्ठा net_bridge *br,
			       काष्ठा net_bridge_port *port,
			       काष्ठा sk_buff *skb)
अणु
	स्थिर काष्ठा br_mrp_ring_test_hdr *test_hdr;
	काष्ठा br_mrp_ring_test_hdr _test_hdr;
	स्थिर काष्ठा br_mrp_tlv_hdr *hdr;
	काष्ठा br_mrp_tlv_hdr _hdr;

	/* Each MRP header starts with a version field which is 16 bits.
	 * Thereक्रमe skip the version and get directly the TLV header.
	 */
	hdr = skb_header_poपूर्णांकer(skb, माप(uपूर्णांक16_t), माप(_hdr), &_hdr);
	अगर (!hdr)
		वापस;

	अगर (hdr->type != BR_MRP_TLV_HEADER_RING_TEST)
		वापस;

	test_hdr = skb_header_poपूर्णांकer(skb, माप(uपूर्णांक16_t) + माप(_hdr),
				      माप(_test_hdr), &_test_hdr);
	अगर (!test_hdr)
		वापस;

	/* Only frames that have a better priority than the node will
	 * clear the miss counter because otherwise the node will need to behave
	 * as MRM.
	 */
	अगर (br_mrp_test_better_than_own(mrp, br, test_hdr))
		mrp->test_count_miss = 0;
पूर्ण

/* Process only MRP InTest frame. All the other MRP frames are processed by
 * userspace application
 * note: alपढ़ोy called with rcu_पढ़ो_lock
 */
अटल bool br_mrp_mim_process(काष्ठा br_mrp *mrp, काष्ठा net_bridge_port *port,
			       काष्ठा sk_buff *skb)
अणु
	स्थिर काष्ठा br_mrp_in_test_hdr *in_hdr;
	काष्ठा br_mrp_in_test_hdr _in_hdr;
	स्थिर काष्ठा br_mrp_tlv_hdr *hdr;
	काष्ठा br_mrp_tlv_hdr _hdr;

	/* Each MRP header starts with a version field which is 16 bits.
	 * Thereक्रमe skip the version and get directly the TLV header.
	 */
	hdr = skb_header_poपूर्णांकer(skb, माप(uपूर्णांक16_t), माप(_hdr), &_hdr);
	अगर (!hdr)
		वापस false;

	/* The check क्रम InTest frame type was alपढ़ोy करोne */
	in_hdr = skb_header_poपूर्णांकer(skb, माप(uपूर्णांक16_t) + माप(_hdr),
				    माप(_in_hdr), &_in_hdr);
	अगर (!in_hdr)
		वापस false;

	/* It needs to process only it's own InTest frames. */
	अगर (mrp->in_id != ntohs(in_hdr->id))
		वापस false;

	mrp->in_test_count_miss = 0;

	/* Notअगरy the userspace that the ring is बंदd only when the ring is
	 * not बंदd
	 */
	अगर (mrp->in_state != BR_MRP_IN_STATE_CLOSED)
		br_mrp_in_port_खोलो(port->dev, false);

	वापस true;
पूर्ण

/* Get the MRP frame type
 * note: alपढ़ोy called with rcu_पढ़ो_lock
 */
अटल u8 br_mrp_get_frame_type(काष्ठा sk_buff *skb)
अणु
	स्थिर काष्ठा br_mrp_tlv_hdr *hdr;
	काष्ठा br_mrp_tlv_hdr _hdr;

	/* Each MRP header starts with a version field which is 16 bits.
	 * Thereक्रमe skip the version and get directly the TLV header.
	 */
	hdr = skb_header_poपूर्णांकer(skb, माप(uपूर्णांक16_t), माप(_hdr), &_hdr);
	अगर (!hdr)
		वापस 0xff;

	वापस hdr->type;
पूर्ण

अटल bool br_mrp_mrm_behaviour(काष्ठा br_mrp *mrp)
अणु
	अगर (mrp->ring_role == BR_MRP_RING_ROLE_MRM ||
	    (mrp->ring_role == BR_MRP_RING_ROLE_MRA && !mrp->test_monitor))
		वापस true;

	वापस false;
पूर्ण

अटल bool br_mrp_mrc_behaviour(काष्ठा br_mrp *mrp)
अणु
	अगर (mrp->ring_role == BR_MRP_RING_ROLE_MRC ||
	    (mrp->ring_role == BR_MRP_RING_ROLE_MRA && mrp->test_monitor))
		वापस true;

	वापस false;
पूर्ण

/* This will just क्रमward the frame to the other mrp ring ports, depending on
 * the frame type, ring role and पूर्णांकerconnect role
 * note: alपढ़ोy called with rcu_पढ़ो_lock
 */
अटल पूर्णांक br_mrp_rcv(काष्ठा net_bridge_port *p,
		      काष्ठा sk_buff *skb, काष्ठा net_device *dev)
अणु
	काष्ठा net_bridge_port *p_port, *s_port, *i_port = शून्य;
	काष्ठा net_bridge_port *p_dst, *s_dst, *i_dst = शून्य;
	काष्ठा net_bridge *br;
	काष्ठा br_mrp *mrp;

	/* If port is disabled करोn't accept any frames */
	अगर (p->state == BR_STATE_DISABLED)
		वापस 0;

	br = p->br;
	mrp =  br_mrp_find_port(br, p);
	अगर (unlikely(!mrp))
		वापस 0;

	p_port = rcu_dereference(mrp->p_port);
	अगर (!p_port)
		वापस 0;
	p_dst = p_port;

	s_port = rcu_dereference(mrp->s_port);
	अगर (!s_port)
		वापस 0;
	s_dst = s_port;

	/* If the frame is a ring frame then it is not required to check the
	 * पूर्णांकerconnect role and ports to process or क्रमward the frame
	 */
	अगर (br_mrp_ring_frame(skb)) अणु
		/* If the role is MRM then करोn't क्रमward the frames */
		अगर (mrp->ring_role == BR_MRP_RING_ROLE_MRM) अणु
			br_mrp_mrm_process(mrp, p, skb);
			जाओ no_क्रमward;
		पूर्ण

		/* If the role is MRA then करोn't क्रमward the frames अगर it
		 * behaves as MRM node
		 */
		अगर (mrp->ring_role == BR_MRP_RING_ROLE_MRA) अणु
			अगर (!mrp->test_monitor) अणु
				br_mrp_mrm_process(mrp, p, skb);
				जाओ no_क्रमward;
			पूर्ण

			br_mrp_mra_process(mrp, br, p, skb);
		पूर्ण

		जाओ क्रमward;
	पूर्ण

	अगर (br_mrp_in_frame(skb)) अणु
		u8 in_type = br_mrp_get_frame_type(skb);

		i_port = rcu_dereference(mrp->i_port);
		i_dst = i_port;

		/* If the ring port is in block state it should not क्रमward
		 * In_Test frames
		 */
		अगर (br_mrp_is_ring_port(p_port, s_port, p) &&
		    p->state == BR_STATE_BLOCKING &&
		    in_type == BR_MRP_TLV_HEADER_IN_TEST)
			जाओ no_क्रमward;

		/* Nodes that behaves as MRM needs to stop क्रमwarding the
		 * frames in हाल the ring is बंदd, otherwise will be a loop.
		 * In this हाल the frame is no क्रमward between the ring ports.
		 */
		अगर (br_mrp_mrm_behaviour(mrp) &&
		    br_mrp_is_ring_port(p_port, s_port, p) &&
		    (s_port->state != BR_STATE_FORWARDING ||
		     p_port->state != BR_STATE_FORWARDING)) अणु
			p_dst = शून्य;
			s_dst = शून्य;
		पूर्ण

		/* A node that behaves as MRC and करोesn't have a पूर्णांकerconnect
		 * role then it should क्रमward all frames between the ring ports
		 * because it करोesn't have an पूर्णांकerconnect port
		 */
		अगर (br_mrp_mrc_behaviour(mrp) &&
		    mrp->in_role == BR_MRP_IN_ROLE_DISABLED)
			जाओ क्रमward;

		अगर (mrp->in_role == BR_MRP_IN_ROLE_MIM) अणु
			अगर (in_type == BR_MRP_TLV_HEADER_IN_TEST) अणु
				/* MIM should not क्रमward it's own InTest
				 * frames
				 */
				अगर (br_mrp_mim_process(mrp, p, skb)) अणु
					जाओ no_क्रमward;
				पूर्ण अन्यथा अणु
					अगर (br_mrp_is_ring_port(p_port, s_port,
								p))
						i_dst = शून्य;

					अगर (br_mrp_is_in_port(i_port, p))
						जाओ no_क्रमward;
				पूर्ण
			पूर्ण अन्यथा अणु
				/* MIM should क्रमward IntLinkChange/Status and
				 * IntTopoChange between ring ports but MIM
				 * should not क्रमward IntLinkChange/Status and
				 * IntTopoChange अगर the frame was received at
				 * the पूर्णांकerconnect port
				 */
				अगर (br_mrp_is_ring_port(p_port, s_port, p))
					i_dst = शून्य;

				अगर (br_mrp_is_in_port(i_port, p))
					जाओ no_क्रमward;
			पूर्ण
		पूर्ण

		अगर (mrp->in_role == BR_MRP_IN_ROLE_MIC) अणु
			/* MIC should क्रमward InTest frames on all ports
			 * regardless of the received port
			 */
			अगर (in_type == BR_MRP_TLV_HEADER_IN_TEST)
				जाओ क्रमward;

			/* MIC should क्रमward IntLinkChange frames only अगर they
			 * are received on ring ports to all the ports
			 */
			अगर (br_mrp_is_ring_port(p_port, s_port, p) &&
			    (in_type == BR_MRP_TLV_HEADER_IN_LINK_UP ||
			     in_type == BR_MRP_TLV_HEADER_IN_LINK_DOWN))
				जाओ क्रमward;

			/* MIC should क्रमward IntLinkStatus frames only to
			 * पूर्णांकerconnect port अगर it was received on a ring port.
			 * If it is received on पूर्णांकerconnect port then, it
			 * should be क्रमward on both ring ports
			 */
			अगर (br_mrp_is_ring_port(p_port, s_port, p) &&
			    in_type == BR_MRP_TLV_HEADER_IN_LINK_STATUS) अणु
				p_dst = शून्य;
				s_dst = शून्य;
			पूर्ण

			/* Should क्रमward the InTopo frames only between the
			 * ring ports
			 */
			अगर (in_type == BR_MRP_TLV_HEADER_IN_TOPO) अणु
				i_dst = शून्य;
				जाओ क्रमward;
			पूर्ण

			/* In all the other हालs करोn't क्रमward the frames */
			जाओ no_क्रमward;
		पूर्ण
	पूर्ण

क्रमward:
	अगर (p_dst)
		br_क्रमward(p_dst, skb, true, false);
	अगर (s_dst)
		br_क्रमward(s_dst, skb, true, false);
	अगर (i_dst)
		br_क्रमward(i_dst, skb, true, false);

no_क्रमward:
	वापस 1;
पूर्ण

/* Check अगर the frame was received on a port that is part of MRP ring
 * and अगर the frame has MRP eth. In that हाल process the frame otherwise करो
 * normal क्रमwarding.
 * note: alपढ़ोy called with rcu_पढ़ो_lock
 */
अटल पूर्णांक br_mrp_process(काष्ठा net_bridge_port *p, काष्ठा sk_buff *skb)
अणु
	/* If there is no MRP instance करो normal क्रमwarding */
	अगर (likely(!(p->flags & BR_MRP_AWARE)))
		जाओ out;

	वापस br_mrp_rcv(p, skb, p->dev);
out:
	वापस 0;
पूर्ण

bool br_mrp_enabled(काष्ठा net_bridge *br)
अणु
	वापस !hlist_empty(&br->mrp_list);
पूर्ण
