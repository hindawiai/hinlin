<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/* Copyright (C) 2018-2020, Intel Corporation. */

#समावेश "ice.h"

/**
 * ice_is_arfs_active - helper to check is aRFS is active
 * @vsi: VSI to check
 */
अटल bool ice_is_arfs_active(काष्ठा ice_vsi *vsi)
अणु
	वापस !!vsi->arfs_fltr_list;
पूर्ण

/**
 * ice_is_arfs_using_perfect_flow - check अगर aRFS has active perfect filters
 * @hw: poपूर्णांकer to the HW काष्ठाure
 * @flow_type: flow type as Flow Director understands it
 *
 * Flow Director will query this function to see अगर aRFS is currently using
 * the specअगरied flow_type क्रम perfect (4-tuple) filters.
 */
bool
ice_is_arfs_using_perfect_flow(काष्ठा ice_hw *hw, क्रमागत ice_fltr_ptype flow_type)
अणु
	काष्ठा ice_arfs_active_fltr_cntrs *arfs_fltr_cntrs;
	काष्ठा ice_pf *pf = hw->back;
	काष्ठा ice_vsi *vsi;

	vsi = ice_get_मुख्य_vsi(pf);
	अगर (!vsi)
		वापस false;

	arfs_fltr_cntrs = vsi->arfs_fltr_cntrs;

	/* active counters can be updated by multiple CPUs */
	smp_mb__beक्रमe_atomic();
	चयन (flow_type) अणु
	हाल ICE_FLTR_PTYPE_NONF_IPV4_UDP:
		वापस atomic_पढ़ो(&arfs_fltr_cntrs->active_udpv4_cnt) > 0;
	हाल ICE_FLTR_PTYPE_NONF_IPV6_UDP:
		वापस atomic_पढ़ो(&arfs_fltr_cntrs->active_udpv6_cnt) > 0;
	हाल ICE_FLTR_PTYPE_NONF_IPV4_TCP:
		वापस atomic_पढ़ो(&arfs_fltr_cntrs->active_tcpv4_cnt) > 0;
	हाल ICE_FLTR_PTYPE_NONF_IPV6_TCP:
		वापस atomic_पढ़ो(&arfs_fltr_cntrs->active_tcpv6_cnt) > 0;
	शेष:
		वापस false;
	पूर्ण
पूर्ण

/**
 * ice_arfs_update_active_fltr_cntrs - update active filter counters क्रम aRFS
 * @vsi: VSI that aRFS is active on
 * @entry: aRFS entry used to change counters
 * @add: true to increment counter, false to decrement
 */
अटल व्योम
ice_arfs_update_active_fltr_cntrs(काष्ठा ice_vsi *vsi,
				  काष्ठा ice_arfs_entry *entry, bool add)
अणु
	काष्ठा ice_arfs_active_fltr_cntrs *fltr_cntrs = vsi->arfs_fltr_cntrs;

	चयन (entry->fltr_info.flow_type) अणु
	हाल ICE_FLTR_PTYPE_NONF_IPV4_TCP:
		अगर (add)
			atomic_inc(&fltr_cntrs->active_tcpv4_cnt);
		अन्यथा
			atomic_dec(&fltr_cntrs->active_tcpv4_cnt);
		अवरोध;
	हाल ICE_FLTR_PTYPE_NONF_IPV6_TCP:
		अगर (add)
			atomic_inc(&fltr_cntrs->active_tcpv6_cnt);
		अन्यथा
			atomic_dec(&fltr_cntrs->active_tcpv6_cnt);
		अवरोध;
	हाल ICE_FLTR_PTYPE_NONF_IPV4_UDP:
		अगर (add)
			atomic_inc(&fltr_cntrs->active_udpv4_cnt);
		अन्यथा
			atomic_dec(&fltr_cntrs->active_udpv4_cnt);
		अवरोध;
	हाल ICE_FLTR_PTYPE_NONF_IPV6_UDP:
		अगर (add)
			atomic_inc(&fltr_cntrs->active_udpv6_cnt);
		अन्यथा
			atomic_dec(&fltr_cntrs->active_udpv6_cnt);
		अवरोध;
	शेष:
		dev_err(ice_pf_to_dev(vsi->back), "aRFS: Failed to update filter counters, invalid filter type %d\n",
			entry->fltr_info.flow_type);
	पूर्ण
पूर्ण

/**
 * ice_arfs_del_flow_rules - delete the rules passed in from HW
 * @vsi: VSI क्रम the flow rules that need to be deleted
 * @del_list_head: head of the list of ice_arfs_entry(s) क्रम rule deletion
 *
 * Loop through the delete list passed in and हटाओ the rules from HW. After
 * each rule is deleted, disconnect and मुक्त the ice_arfs_entry because it is no
 * दीर्घer being referenced by the aRFS hash table.
 */
अटल व्योम
ice_arfs_del_flow_rules(काष्ठा ice_vsi *vsi, काष्ठा hlist_head *del_list_head)
अणु
	काष्ठा ice_arfs_entry *e;
	काष्ठा hlist_node *n;
	काष्ठा device *dev;

	dev = ice_pf_to_dev(vsi->back);

	hlist_क्रम_each_entry_safe(e, n, del_list_head, list_entry) अणु
		पूर्णांक result;

		result = ice_fdir_ग_लिखो_fltr(vsi->back, &e->fltr_info, false,
					     false);
		अगर (!result)
			ice_arfs_update_active_fltr_cntrs(vsi, e, false);
		अन्यथा
			dev_dbg(dev, "Unable to delete aRFS entry, err %d fltr_state %d fltr_id %d flow_id %d Q %d\n",
				result, e->fltr_state, e->fltr_info.fltr_id,
				e->flow_id, e->fltr_info.q_index);

		/* The aRFS hash table is no दीर्घer referencing this entry */
		hlist_del(&e->list_entry);
		devm_kमुक्त(dev, e);
	पूर्ण
पूर्ण

/**
 * ice_arfs_add_flow_rules - add the rules passed in from HW
 * @vsi: VSI क्रम the flow rules that need to be added
 * @add_list_head: head of the list of ice_arfs_entry_ptr(s) क्रम rule addition
 *
 * Loop through the add list passed in and हटाओ the rules from HW. After each
 * rule is added, disconnect and मुक्त the ice_arfs_entry_ptr node. Don't मुक्त
 * the ice_arfs_entry(s) because they are still being referenced in the aRFS
 * hash table.
 */
अटल व्योम
ice_arfs_add_flow_rules(काष्ठा ice_vsi *vsi, काष्ठा hlist_head *add_list_head)
अणु
	काष्ठा ice_arfs_entry_ptr *ep;
	काष्ठा hlist_node *n;
	काष्ठा device *dev;

	dev = ice_pf_to_dev(vsi->back);

	hlist_क्रम_each_entry_safe(ep, n, add_list_head, list_entry) अणु
		पूर्णांक result;

		result = ice_fdir_ग_लिखो_fltr(vsi->back,
					     &ep->arfs_entry->fltr_info, true,
					     false);
		अगर (!result)
			ice_arfs_update_active_fltr_cntrs(vsi, ep->arfs_entry,
							  true);
		अन्यथा
			dev_dbg(dev, "Unable to add aRFS entry, err %d fltr_state %d fltr_id %d flow_id %d Q %d\n",
				result, ep->arfs_entry->fltr_state,
				ep->arfs_entry->fltr_info.fltr_id,
				ep->arfs_entry->flow_id,
				ep->arfs_entry->fltr_info.q_index);

		hlist_del(&ep->list_entry);
		devm_kमुक्त(dev, ep);
	पूर्ण
पूर्ण

/**
 * ice_arfs_is_flow_expired - check अगर the aRFS entry has expired
 * @vsi: VSI containing the aRFS entry
 * @arfs_entry: aRFS entry that's being checked क्रम expiration
 *
 * Return true अगर the flow has expired, अन्यथा false. This function should be used
 * to determine whether or not an aRFS entry should be हटाओd from the hardware
 * and software काष्ठाures.
 */
अटल bool
ice_arfs_is_flow_expired(काष्ठा ice_vsi *vsi, काष्ठा ice_arfs_entry *arfs_entry)
अणु
#घोषणा ICE_ARFS_TIME_DELTA_EXPIRATION	msecs_to_jअगरfies(5000)
	अगर (rps_may_expire_flow(vsi->netdev, arfs_entry->fltr_info.q_index,
				arfs_entry->flow_id,
				arfs_entry->fltr_info.fltr_id))
		वापस true;

	/* expiration समयr only used क्रम UDP filters */
	अगर (arfs_entry->fltr_info.flow_type != ICE_FLTR_PTYPE_NONF_IPV4_UDP &&
	    arfs_entry->fltr_info.flow_type != ICE_FLTR_PTYPE_NONF_IPV6_UDP)
		वापस false;

	वापस समय_in_range64(arfs_entry->समय_activated +
			       ICE_ARFS_TIME_DELTA_EXPIRATION,
			       arfs_entry->समय_activated, get_jअगरfies_64());
पूर्ण

/**
 * ice_arfs_update_flow_rules - add/delete aRFS rules in HW
 * @vsi: the VSI to be क्रमwarded to
 * @idx: index पूर्णांकo the table of aRFS filter lists. Obtained from skb->hash
 * @add_list: list to populate with filters to be added to Flow Director
 * @del_list: list to populate with filters to be deleted from Flow Director
 *
 * Iterate over the hlist at the index given in the aRFS hash table and
 * determine अगर there are any aRFS entries that need to be either added or
 * deleted in the HW. If the aRFS entry is marked as ICE_ARFS_INACTIVE the
 * filter needs to be added to HW, अन्यथा अगर it's marked as ICE_ARFS_ACTIVE and
 * the flow has expired delete the filter from HW. The caller of this function
 * is expected to add/delete rules on the add_list/del_list respectively.
 */
अटल व्योम
ice_arfs_update_flow_rules(काष्ठा ice_vsi *vsi, u16 idx,
			   काष्ठा hlist_head *add_list,
			   काष्ठा hlist_head *del_list)
अणु
	काष्ठा ice_arfs_entry *e;
	काष्ठा hlist_node *n;
	काष्ठा device *dev;

	dev = ice_pf_to_dev(vsi->back);

	/* go through the aRFS hlist at this idx and check क्रम needed updates */
	hlist_क्रम_each_entry_safe(e, n, &vsi->arfs_fltr_list[idx], list_entry)
		/* check अगर filter needs to be added to HW */
		अगर (e->fltr_state == ICE_ARFS_INACTIVE) अणु
			क्रमागत ice_fltr_ptype flow_type = e->fltr_info.flow_type;
			काष्ठा ice_arfs_entry_ptr *ep =
				devm_kzalloc(dev, माप(*ep), GFP_ATOMIC);

			अगर (!ep)
				जारी;
			INIT_HLIST_NODE(&ep->list_entry);
			/* reference aRFS entry to add HW filter */
			ep->arfs_entry = e;
			hlist_add_head(&ep->list_entry, add_list);
			e->fltr_state = ICE_ARFS_ACTIVE;
			/* expiration समयr only used क्रम UDP flows */
			अगर (flow_type == ICE_FLTR_PTYPE_NONF_IPV4_UDP ||
			    flow_type == ICE_FLTR_PTYPE_NONF_IPV6_UDP)
				e->समय_activated = get_jअगरfies_64();
		पूर्ण अन्यथा अगर (e->fltr_state == ICE_ARFS_ACTIVE) अणु
			/* check अगर filter needs to be हटाओd from HW */
			अगर (ice_arfs_is_flow_expired(vsi, e)) अणु
				/* हटाओ aRFS entry from hash table क्रम delete
				 * and to prevent referencing it the next समय
				 * through this hlist index
				 */
				hlist_del(&e->list_entry);
				e->fltr_state = ICE_ARFS_TODEL;
				/* save reference to aRFS entry क्रम delete */
				hlist_add_head(&e->list_entry, del_list);
			पूर्ण
		पूर्ण
पूर्ण

/**
 * ice_sync_arfs_fltrs - update all aRFS filters
 * @pf: board निजी काष्ठाure
 */
व्योम ice_sync_arfs_fltrs(काष्ठा ice_pf *pf)
अणु
	HLIST_HEAD(पंचांगp_del_list);
	HLIST_HEAD(पंचांगp_add_list);
	काष्ठा ice_vsi *pf_vsi;
	अचिन्हित पूर्णांक i;

	pf_vsi = ice_get_मुख्य_vsi(pf);
	अगर (!pf_vsi)
		वापस;

	अगर (!ice_is_arfs_active(pf_vsi))
		वापस;

	spin_lock_bh(&pf_vsi->arfs_lock);
	/* Once we process aRFS क्रम the PF VSI get out */
	क्रम (i = 0; i < ICE_MAX_ARFS_LIST; i++)
		ice_arfs_update_flow_rules(pf_vsi, i, &पंचांगp_add_list,
					   &पंचांगp_del_list);
	spin_unlock_bh(&pf_vsi->arfs_lock);

	/* use list of ice_arfs_entry(s) क्रम delete */
	ice_arfs_del_flow_rules(pf_vsi, &पंचांगp_del_list);

	/* use list of ice_arfs_entry_ptr(s) क्रम add */
	ice_arfs_add_flow_rules(pf_vsi, &पंचांगp_add_list);
पूर्ण

/**
 * ice_arfs_build_entry - builds an aRFS entry based on input
 * @vsi: destination VSI क्रम this flow
 * @fk: flow dissector keys क्रम creating the tuple
 * @rxq_idx: Rx queue to steer this flow to
 * @flow_id: passed करोwn from the stack and saved क्रम flow expiration
 *
 * वापसs an aRFS entry on success and शून्य on failure
 */
अटल काष्ठा ice_arfs_entry *
ice_arfs_build_entry(काष्ठा ice_vsi *vsi, स्थिर काष्ठा flow_keys *fk,
		     u16 rxq_idx, u32 flow_id)
अणु
	काष्ठा ice_arfs_entry *arfs_entry;
	काष्ठा ice_fdir_fltr *fltr_info;
	u8 ip_proto;

	arfs_entry = devm_kzalloc(ice_pf_to_dev(vsi->back),
				  माप(*arfs_entry),
				  GFP_ATOMIC | __GFP_NOWARN);
	अगर (!arfs_entry)
		वापस शून्य;

	fltr_info = &arfs_entry->fltr_info;
	fltr_info->q_index = rxq_idx;
	fltr_info->dest_ctl = ICE_FLTR_PRGM_DESC_DEST_सूचीECT_PKT_QINDEX;
	fltr_info->dest_vsi = vsi->idx;
	ip_proto = fk->basic.ip_proto;

	अगर (fk->basic.n_proto == htons(ETH_P_IP)) अणु
		fltr_info->ip.v4.proto = ip_proto;
		fltr_info->flow_type = (ip_proto == IPPROTO_TCP) ?
			ICE_FLTR_PTYPE_NONF_IPV4_TCP :
			ICE_FLTR_PTYPE_NONF_IPV4_UDP;
		fltr_info->ip.v4.src_ip = fk->addrs.v4addrs.src;
		fltr_info->ip.v4.dst_ip = fk->addrs.v4addrs.dst;
		fltr_info->ip.v4.src_port = fk->ports.src;
		fltr_info->ip.v4.dst_port = fk->ports.dst;
	पूर्ण अन्यथा अणु /* ETH_P_IPV6 */
		fltr_info->ip.v6.proto = ip_proto;
		fltr_info->flow_type = (ip_proto == IPPROTO_TCP) ?
			ICE_FLTR_PTYPE_NONF_IPV6_TCP :
			ICE_FLTR_PTYPE_NONF_IPV6_UDP;
		स_नकल(&fltr_info->ip.v6.src_ip, &fk->addrs.v6addrs.src,
		       माप(काष्ठा in6_addr));
		स_नकल(&fltr_info->ip.v6.dst_ip, &fk->addrs.v6addrs.dst,
		       माप(काष्ठा in6_addr));
		fltr_info->ip.v6.src_port = fk->ports.src;
		fltr_info->ip.v6.dst_port = fk->ports.dst;
	पूर्ण

	arfs_entry->flow_id = flow_id;
	fltr_info->fltr_id =
		atomic_inc_वापस(vsi->arfs_last_fltr_id) % RPS_NO_FILTER;

	वापस arfs_entry;
पूर्ण

/**
 * ice_arfs_is_perfect_flow_set - Check to see अगर perfect flow is set
 * @hw: poपूर्णांकer to HW काष्ठाure
 * @l3_proto: ETH_P_IP or ETH_P_IPV6 in network order
 * @l4_proto: IPPROTO_UDP or IPPROTO_TCP
 *
 * We only support perfect (4-tuple) filters क्रम aRFS. This function allows aRFS
 * to check अगर perfect (4-tuple) flow rules are currently in place by Flow
 * Director.
 */
अटल bool
ice_arfs_is_perfect_flow_set(काष्ठा ice_hw *hw, __be16 l3_proto, u8 l4_proto)
अणु
	अचिन्हित दीर्घ *perfect_fltr = hw->fdir_perfect_fltr;

	/* advanced Flow Director disabled, perfect filters always supported */
	अगर (!perfect_fltr)
		वापस true;

	अगर (l3_proto == htons(ETH_P_IP) && l4_proto == IPPROTO_UDP)
		वापस test_bit(ICE_FLTR_PTYPE_NONF_IPV4_UDP, perfect_fltr);
	अन्यथा अगर (l3_proto == htons(ETH_P_IP) && l4_proto == IPPROTO_TCP)
		वापस test_bit(ICE_FLTR_PTYPE_NONF_IPV4_TCP, perfect_fltr);
	अन्यथा अगर (l3_proto == htons(ETH_P_IPV6) && l4_proto == IPPROTO_UDP)
		वापस test_bit(ICE_FLTR_PTYPE_NONF_IPV6_UDP, perfect_fltr);
	अन्यथा अगर (l3_proto == htons(ETH_P_IPV6) && l4_proto == IPPROTO_TCP)
		वापस test_bit(ICE_FLTR_PTYPE_NONF_IPV6_TCP, perfect_fltr);

	वापस false;
पूर्ण

/**
 * ice_rx_flow_steer - steer the Rx flow to where application is being run
 * @netdev: ptr to the netdev being adjusted
 * @skb: buffer with required header inक्रमmation
 * @rxq_idx: queue to which the flow needs to move
 * @flow_id: flow identअगरier provided by the netdev
 *
 * Based on the skb, rxq_idx, and flow_id passed in add/update an entry in the
 * aRFS hash table. Iterate over one of the hlists in the aRFS hash table and
 * अगर the flow_id alपढ़ोy exists in the hash table but the rxq_idx has changed
 * mark the entry as ICE_ARFS_INACTIVE so it can get updated in HW, अन्यथा
 * अगर the entry is marked as ICE_ARFS_TODEL delete it from the aRFS hash table.
 * If neither of the previous conditions are true then add a new entry in the
 * aRFS hash table, which माला_लो set to ICE_ARFS_INACTIVE by शेष so it can be
 * added to HW.
 */
पूर्णांक
ice_rx_flow_steer(काष्ठा net_device *netdev, स्थिर काष्ठा sk_buff *skb,
		  u16 rxq_idx, u32 flow_id)
अणु
	काष्ठा ice_netdev_priv *np = netdev_priv(netdev);
	काष्ठा ice_arfs_entry *arfs_entry;
	काष्ठा ice_vsi *vsi = np->vsi;
	काष्ठा flow_keys fk;
	काष्ठा ice_pf *pf;
	__be16 n_proto;
	u8 ip_proto;
	u16 idx;
	पूर्णांक ret;

	/* failed to allocate memory क्रम aRFS so करोn't crash */
	अगर (unlikely(!vsi->arfs_fltr_list))
		वापस -ENODEV;

	pf = vsi->back;

	अगर (skb->encapsulation)
		वापस -EPROTONOSUPPORT;

	अगर (!skb_flow_dissect_flow_keys(skb, &fk, 0))
		वापस -EPROTONOSUPPORT;

	n_proto = fk.basic.n_proto;
	/* Support only IPV4 and IPV6 */
	अगर ((n_proto == htons(ETH_P_IP) && !ip_is_fragment(ip_hdr(skb))) ||
	    n_proto == htons(ETH_P_IPV6))
		ip_proto = fk.basic.ip_proto;
	अन्यथा
		वापस -EPROTONOSUPPORT;

	/* Support only TCP and UDP */
	अगर (ip_proto != IPPROTO_TCP && ip_proto != IPPROTO_UDP)
		वापस -EPROTONOSUPPORT;

	/* only support 4-tuple filters क्रम aRFS */
	अगर (!ice_arfs_is_perfect_flow_set(&pf->hw, n_proto, ip_proto))
		वापस -EOPNOTSUPP;

	/* choose the aRFS list bucket based on skb hash */
	idx = skb_get_hash_raw(skb) & ICE_ARFS_LST_MASK;
	/* search क्रम entry in the bucket */
	spin_lock_bh(&vsi->arfs_lock);
	hlist_क्रम_each_entry(arfs_entry, &vsi->arfs_fltr_list[idx],
			     list_entry) अणु
		काष्ठा ice_fdir_fltr *fltr_info;

		/* keep searching क्रम the alपढ़ोy existing arfs_entry flow */
		अगर (arfs_entry->flow_id != flow_id)
			जारी;

		fltr_info = &arfs_entry->fltr_info;
		ret = fltr_info->fltr_id;

		अगर (fltr_info->q_index == rxq_idx ||
		    arfs_entry->fltr_state != ICE_ARFS_ACTIVE)
			जाओ out;

		/* update the queue to क्रमward to on an alपढ़ोy existing flow */
		fltr_info->q_index = rxq_idx;
		arfs_entry->fltr_state = ICE_ARFS_INACTIVE;
		ice_arfs_update_active_fltr_cntrs(vsi, arfs_entry, false);
		जाओ out_schedule_service_task;
	पूर्ण

	arfs_entry = ice_arfs_build_entry(vsi, &fk, rxq_idx, flow_id);
	अगर (!arfs_entry) अणु
		ret = -ENOMEM;
		जाओ out;
	पूर्ण

	ret = arfs_entry->fltr_info.fltr_id;
	INIT_HLIST_NODE(&arfs_entry->list_entry);
	hlist_add_head(&arfs_entry->list_entry, &vsi->arfs_fltr_list[idx]);
out_schedule_service_task:
	ice_service_task_schedule(pf);
out:
	spin_unlock_bh(&vsi->arfs_lock);
	वापस ret;
पूर्ण

/**
 * ice_init_arfs_cntrs - initialize aRFS counter values
 * @vsi: VSI that aRFS counters need to be initialized on
 */
अटल पूर्णांक ice_init_arfs_cntrs(काष्ठा ice_vsi *vsi)
अणु
	अगर (!vsi || vsi->type != ICE_VSI_PF)
		वापस -EINVAL;

	vsi->arfs_fltr_cntrs = kzalloc(माप(*vsi->arfs_fltr_cntrs),
				       GFP_KERNEL);
	अगर (!vsi->arfs_fltr_cntrs)
		वापस -ENOMEM;

	vsi->arfs_last_fltr_id = kzalloc(माप(*vsi->arfs_last_fltr_id),
					 GFP_KERNEL);
	अगर (!vsi->arfs_last_fltr_id) अणु
		kमुक्त(vsi->arfs_fltr_cntrs);
		vsi->arfs_fltr_cntrs = शून्य;
		वापस -ENOMEM;
	पूर्ण

	वापस 0;
पूर्ण

/**
 * ice_init_arfs - initialize aRFS resources
 * @vsi: the VSI to be क्रमwarded to
 */
व्योम ice_init_arfs(काष्ठा ice_vsi *vsi)
अणु
	काष्ठा hlist_head *arfs_fltr_list;
	अचिन्हित पूर्णांक i;

	अगर (!vsi || vsi->type != ICE_VSI_PF)
		वापस;

	arfs_fltr_list = kzalloc(माप(*arfs_fltr_list) * ICE_MAX_ARFS_LIST,
				 GFP_KERNEL);
	अगर (!arfs_fltr_list)
		वापस;

	अगर (ice_init_arfs_cntrs(vsi))
		जाओ मुक्त_arfs_fltr_list;

	क्रम (i = 0; i < ICE_MAX_ARFS_LIST; i++)
		INIT_HLIST_HEAD(&arfs_fltr_list[i]);

	spin_lock_init(&vsi->arfs_lock);

	vsi->arfs_fltr_list = arfs_fltr_list;

	वापस;

मुक्त_arfs_fltr_list:
	kमुक्त(arfs_fltr_list);
पूर्ण

/**
 * ice_clear_arfs - clear the aRFS hash table and any memory used क्रम aRFS
 * @vsi: the VSI to be क्रमwarded to
 */
व्योम ice_clear_arfs(काष्ठा ice_vsi *vsi)
अणु
	काष्ठा device *dev;
	अचिन्हित पूर्णांक i;

	अगर (!vsi || vsi->type != ICE_VSI_PF || !vsi->back ||
	    !vsi->arfs_fltr_list)
		वापस;

	dev = ice_pf_to_dev(vsi->back);
	क्रम (i = 0; i < ICE_MAX_ARFS_LIST; i++) अणु
		काष्ठा ice_arfs_entry *r;
		काष्ठा hlist_node *n;

		spin_lock_bh(&vsi->arfs_lock);
		hlist_क्रम_each_entry_safe(r, n, &vsi->arfs_fltr_list[i],
					  list_entry) अणु
			hlist_del(&r->list_entry);
			devm_kमुक्त(dev, r);
		पूर्ण
		spin_unlock_bh(&vsi->arfs_lock);
	पूर्ण

	kमुक्त(vsi->arfs_fltr_list);
	vsi->arfs_fltr_list = शून्य;
	kमुक्त(vsi->arfs_last_fltr_id);
	vsi->arfs_last_fltr_id = शून्य;
	kमुक्त(vsi->arfs_fltr_cntrs);
	vsi->arfs_fltr_cntrs = शून्य;
पूर्ण

/**
 * ice_मुक्त_cpu_rx_rmap - मुक्त setup CPU reverse map
 * @vsi: the VSI to be क्रमwarded to
 */
व्योम ice_मुक्त_cpu_rx_rmap(काष्ठा ice_vsi *vsi)
अणु
	काष्ठा net_device *netdev;

	अगर (!vsi || vsi->type != ICE_VSI_PF || !vsi->arfs_fltr_list)
		वापस;

	netdev = vsi->netdev;
	अगर (!netdev || !netdev->rx_cpu_rmap)
		वापस;

	मुक्त_irq_cpu_rmap(netdev->rx_cpu_rmap);
	netdev->rx_cpu_rmap = शून्य;
पूर्ण

/**
 * ice_set_cpu_rx_rmap - setup CPU reverse map क्रम each queue
 * @vsi: the VSI to be क्रमwarded to
 */
पूर्णांक ice_set_cpu_rx_rmap(काष्ठा ice_vsi *vsi)
अणु
	काष्ठा net_device *netdev;
	काष्ठा ice_pf *pf;
	पूर्णांक base_idx, i;

	अगर (!vsi || vsi->type != ICE_VSI_PF)
		वापस -EINVAL;

	pf = vsi->back;
	netdev = vsi->netdev;
	अगर (!pf || !netdev || !vsi->num_q_vectors)
		वापस -EINVAL;

	netdev_dbg(netdev, "Setup CPU RMAP: vsi type 0x%x, ifname %s, q_vectors %d\n",
		   vsi->type, netdev->name, vsi->num_q_vectors);

	netdev->rx_cpu_rmap = alloc_irq_cpu_rmap(vsi->num_q_vectors);
	अगर (unlikely(!netdev->rx_cpu_rmap))
		वापस -EINVAL;

	base_idx = vsi->base_vector;
	क्रम (i = 0; i < vsi->num_q_vectors; i++)
		अगर (irq_cpu_rmap_add(netdev->rx_cpu_rmap,
				     pf->msix_entries[base_idx + i].vector)) अणु
			ice_मुक्त_cpu_rx_rmap(vsi);
			वापस -EINVAL;
		पूर्ण

	वापस 0;
पूर्ण

/**
 * ice_हटाओ_arfs - हटाओ/clear all aRFS resources
 * @pf: device निजी काष्ठाure
 */
व्योम ice_हटाओ_arfs(काष्ठा ice_pf *pf)
अणु
	काष्ठा ice_vsi *pf_vsi;

	pf_vsi = ice_get_मुख्य_vsi(pf);
	अगर (!pf_vsi)
		वापस;

	ice_मुक्त_cpu_rx_rmap(pf_vsi);
	ice_clear_arfs(pf_vsi);
पूर्ण

/**
 * ice_rebuild_arfs - हटाओ/clear all aRFS resources and rebuild after reset
 * @pf: device निजी काष्ठाure
 */
व्योम ice_rebuild_arfs(काष्ठा ice_pf *pf)
अणु
	काष्ठा ice_vsi *pf_vsi;

	pf_vsi = ice_get_मुख्य_vsi(pf);
	अगर (!pf_vsi)
		वापस;

	ice_हटाओ_arfs(pf);
	अगर (ice_set_cpu_rx_rmap(pf_vsi)) अणु
		dev_err(ice_pf_to_dev(pf), "Failed to rebuild aRFS\n");
		वापस;
	पूर्ण
	ice_init_arfs(pf_vsi);
पूर्ण
