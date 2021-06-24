<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later

#समावेश <linux/cfm_bridge.h>
#समावेश <uapi/linux/cfm_bridge.h>
#समावेश "br_private_cfm.h"

अटल काष्ठा br_cfm_mep *br_mep_find(काष्ठा net_bridge *br, u32 instance)
अणु
	काष्ठा br_cfm_mep *mep;

	hlist_क्रम_each_entry(mep, &br->mep_list, head)
		अगर (mep->instance == instance)
			वापस mep;

	वापस शून्य;
पूर्ण

अटल काष्ठा br_cfm_mep *br_mep_find_अगरindex(काष्ठा net_bridge *br,
					      u32 अगरindex)
अणु
	काष्ठा br_cfm_mep *mep;

	hlist_क्रम_each_entry_rcu(mep, &br->mep_list, head,
				 lockdep_rtnl_is_held())
		अगर (mep->create.अगरindex == अगरindex)
			वापस mep;

	वापस शून्य;
पूर्ण

अटल काष्ठा br_cfm_peer_mep *br_peer_mep_find(काष्ठा br_cfm_mep *mep,
						u32 mepid)
अणु
	काष्ठा br_cfm_peer_mep *peer_mep;

	hlist_क्रम_each_entry_rcu(peer_mep, &mep->peer_mep_list, head,
				 lockdep_rtnl_is_held())
		अगर (peer_mep->mepid == mepid)
			वापस peer_mep;

	वापस शून्य;
पूर्ण

अटल काष्ठा net_bridge_port *br_mep_get_port(काष्ठा net_bridge *br,
					       u32 अगरindex)
अणु
	काष्ठा net_bridge_port *port;

	list_क्रम_each_entry(port, &br->port_list, list)
		अगर (port->dev->अगरindex == अगरindex)
			वापस port;

	वापस शून्य;
पूर्ण

/* Calculate the CCM पूर्णांकerval in us. */
अटल u32 पूर्णांकerval_to_us(क्रमागत br_cfm_ccm_पूर्णांकerval पूर्णांकerval)
अणु
	चयन (पूर्णांकerval) अणु
	हाल BR_CFM_CCM_INTERVAL_NONE:
		वापस 0;
	हाल BR_CFM_CCM_INTERVAL_3_3_MS:
		वापस 3300;
	हाल BR_CFM_CCM_INTERVAL_10_MS:
		वापस 10 * 1000;
	हाल BR_CFM_CCM_INTERVAL_100_MS:
		वापस 100 * 1000;
	हाल BR_CFM_CCM_INTERVAL_1_SEC:
		वापस 1000 * 1000;
	हाल BR_CFM_CCM_INTERVAL_10_SEC:
		वापस 10 * 1000 * 1000;
	हाल BR_CFM_CCM_INTERVAL_1_MIN:
		वापस 60 * 1000 * 1000;
	हाल BR_CFM_CCM_INTERVAL_10_MIN:
		वापस 10 * 60 * 1000 * 1000;
	पूर्ण
	वापस 0;
पूर्ण

/* Convert the पूर्णांकerface पूर्णांकerval to CCM PDU value. */
अटल u32 पूर्णांकerval_to_pdu(क्रमागत br_cfm_ccm_पूर्णांकerval पूर्णांकerval)
अणु
	चयन (पूर्णांकerval) अणु
	हाल BR_CFM_CCM_INTERVAL_NONE:
		वापस 0;
	हाल BR_CFM_CCM_INTERVAL_3_3_MS:
		वापस 1;
	हाल BR_CFM_CCM_INTERVAL_10_MS:
		वापस 2;
	हाल BR_CFM_CCM_INTERVAL_100_MS:
		वापस 3;
	हाल BR_CFM_CCM_INTERVAL_1_SEC:
		वापस 4;
	हाल BR_CFM_CCM_INTERVAL_10_SEC:
		वापस 5;
	हाल BR_CFM_CCM_INTERVAL_1_MIN:
		वापस 6;
	हाल BR_CFM_CCM_INTERVAL_10_MIN:
		वापस 7;
	पूर्ण
	वापस 0;
पूर्ण

/* Convert the CCM PDU value to पूर्णांकerval on पूर्णांकerface. */
अटल u32 pdu_to_पूर्णांकerval(u32 value)
अणु
	चयन (value) अणु
	हाल 0:
		वापस BR_CFM_CCM_INTERVAL_NONE;
	हाल 1:
		वापस BR_CFM_CCM_INTERVAL_3_3_MS;
	हाल 2:
		वापस BR_CFM_CCM_INTERVAL_10_MS;
	हाल 3:
		वापस BR_CFM_CCM_INTERVAL_100_MS;
	हाल 4:
		वापस BR_CFM_CCM_INTERVAL_1_SEC;
	हाल 5:
		वापस BR_CFM_CCM_INTERVAL_10_SEC;
	हाल 6:
		वापस BR_CFM_CCM_INTERVAL_1_MIN;
	हाल 7:
		वापस BR_CFM_CCM_INTERVAL_10_MIN;
	पूर्ण
	वापस BR_CFM_CCM_INTERVAL_NONE;
पूर्ण

अटल व्योम ccm_rx_समयr_start(काष्ठा br_cfm_peer_mep *peer_mep)
अणु
	u32 पूर्णांकerval_us;

	पूर्णांकerval_us = पूर्णांकerval_to_us(peer_mep->mep->cc_config.exp_पूर्णांकerval);
	/* Function ccm_rx_dwork must be called with 1/4
	 * of the configured CC 'expected_interval'
	 * in order to detect CCM defect after 3.25 पूर्णांकerval.
	 */
	queue_delayed_work(प्रणाली_wq, &peer_mep->ccm_rx_dwork,
			   usecs_to_jअगरfies(पूर्णांकerval_us / 4));
पूर्ण

अटल व्योम br_cfm_notअगरy(पूर्णांक event, स्थिर काष्ठा net_bridge_port *port)
अणु
	u32 filter = RTEXT_FILTER_CFM_STATUS;

	वापस br_info_notअगरy(event, port->br, शून्य, filter);
पूर्ण

अटल व्योम cc_peer_enable(काष्ठा br_cfm_peer_mep *peer_mep)
अणु
	स_रखो(&peer_mep->cc_status, 0, माप(peer_mep->cc_status));
	peer_mep->ccm_rx_count_miss = 0;

	ccm_rx_समयr_start(peer_mep);
पूर्ण

अटल व्योम cc_peer_disable(काष्ठा br_cfm_peer_mep *peer_mep)
अणु
	cancel_delayed_work_sync(&peer_mep->ccm_rx_dwork);
पूर्ण

अटल काष्ठा sk_buff *ccm_frame_build(काष्ठा br_cfm_mep *mep,
				       स्थिर काष्ठा br_cfm_cc_ccm_tx_info *स्थिर tx_info)

अणु
	काष्ठा br_cfm_common_hdr *common_hdr;
	काष्ठा net_bridge_port *b_port;
	काष्ठा br_cfm_maid *maid;
	u8 *itu_reserved, *e_tlv;
	काष्ठा ethhdr *eth_hdr;
	काष्ठा sk_buff *skb;
	__be32 *status_tlv;
	__be32 *snumber;
	__be16 *mepid;

	skb = dev_alloc_skb(CFM_CCM_MAX_FRAME_LENGTH);
	अगर (!skb)
		वापस शून्य;

	rcu_पढ़ो_lock();
	b_port = rcu_dereference(mep->b_port);
	अगर (!b_port) अणु
		kमुक्त_skb(skb);
		rcu_पढ़ो_unlock();
		वापस शून्य;
	पूर्ण
	skb->dev = b_port->dev;
	rcu_पढ़ो_unlock();
	/* The device cannot be deleted until the work_queue functions has
	 * completed. This function is called from ccm_tx_work_expired()
	 * that is a work_queue functions.
	 */

	skb->protocol = htons(ETH_P_CFM);
	skb->priority = CFM_FRAME_PRIO;

	/* Ethernet header */
	eth_hdr = skb_put(skb, माप(*eth_hdr));
	ether_addr_copy(eth_hdr->h_dest, tx_info->dmac.addr);
	ether_addr_copy(eth_hdr->h_source, mep->config.unicast_mac.addr);
	eth_hdr->h_proto = htons(ETH_P_CFM);

	/* Common CFM Header */
	common_hdr = skb_put(skb, माप(*common_hdr));
	common_hdr->mdlevel_version = mep->config.mdlevel << 5;
	common_hdr->opcode = BR_CFM_OPCODE_CCM;
	common_hdr->flags = (mep->rdi << 7) |
			    पूर्णांकerval_to_pdu(mep->cc_config.exp_पूर्णांकerval);
	common_hdr->tlv_offset = CFM_CCM_TLV_OFFSET;

	/* Sequence number */
	snumber = skb_put(skb, माप(*snumber));
	अगर (tx_info->seq_no_update) अणु
		*snumber = cpu_to_be32(mep->ccm_tx_snumber);
		mep->ccm_tx_snumber += 1;
	पूर्ण अन्यथा अणु
		*snumber = 0;
	पूर्ण

	mepid = skb_put(skb, माप(*mepid));
	*mepid = cpu_to_be16((u16)mep->config.mepid);

	maid = skb_put(skb, माप(*maid));
	स_नकल(maid->data, mep->cc_config.exp_maid.data, माप(maid->data));

	/* ITU reserved (CFM_CCM_ITU_RESERVED_SIZE octets) */
	itu_reserved = skb_put(skb, CFM_CCM_ITU_RESERVED_SIZE);
	स_रखो(itu_reserved, 0, CFM_CCM_ITU_RESERVED_SIZE);

	/* Generel CFM TLV क्रमmat:
	 * TLV type:		one byte
	 * TLV value length:	two bytes
	 * TLV value:		'TLV value length' bytes
	 */

	/* Port status TLV. The value length is 1. Total of 4 bytes. */
	अगर (tx_info->port_tlv) अणु
		status_tlv = skb_put(skb, माप(*status_tlv));
		*status_tlv = cpu_to_be32((CFM_PORT_STATUS_TLV_TYPE << 24) |
					  (1 << 8) |	/* Value length */
					  (tx_info->port_tlv_value & 0xFF));
	पूर्ण

	/* Interface status TLV. The value length is 1. Total of 4 bytes. */
	अगर (tx_info->अगर_tlv) अणु
		status_tlv = skb_put(skb, माप(*status_tlv));
		*status_tlv = cpu_to_be32((CFM_IF_STATUS_TLV_TYPE << 24) |
					  (1 << 8) |	/* Value length */
					  (tx_info->अगर_tlv_value & 0xFF));
	पूर्ण

	/* End TLV */
	e_tlv = skb_put(skb, माप(*e_tlv));
	*e_tlv = CFM_ENDE_TLV_TYPE;

	वापस skb;
पूर्ण

अटल व्योम ccm_frame_tx(काष्ठा sk_buff *skb)
अणु
	skb_reset_network_header(skb);
	dev_queue_xmit(skb);
पूर्ण

/* This function is called with the configured CC 'expected_interval'
 * in order to drive CCM transmission when enabled.
 */
अटल व्योम ccm_tx_work_expired(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा delayed_work *del_work;
	काष्ठा br_cfm_mep *mep;
	काष्ठा sk_buff *skb;
	u32 पूर्णांकerval_us;

	del_work = to_delayed_work(work);
	mep = container_of(del_work, काष्ठा br_cfm_mep, ccm_tx_dwork);

	अगर (समय_beक्रमe_eq(mep->ccm_tx_end, jअगरfies)) अणु
		/* Transmission period has ended */
		mep->cc_ccm_tx_info.period = 0;
		वापस;
	पूर्ण

	skb = ccm_frame_build(mep, &mep->cc_ccm_tx_info);
	अगर (skb)
		ccm_frame_tx(skb);

	पूर्णांकerval_us = पूर्णांकerval_to_us(mep->cc_config.exp_पूर्णांकerval);
	queue_delayed_work(प्रणाली_wq, &mep->ccm_tx_dwork,
			   usecs_to_jअगरfies(पूर्णांकerval_us));
पूर्ण

/* This function is called with 1/4 of the configured CC 'expected_interval'
 * in order to detect CCM defect after 3.25 पूर्णांकerval.
 */
अटल व्योम ccm_rx_work_expired(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा br_cfm_peer_mep *peer_mep;
	काष्ठा net_bridge_port *b_port;
	काष्ठा delayed_work *del_work;

	del_work = to_delayed_work(work);
	peer_mep = container_of(del_work, काष्ठा br_cfm_peer_mep, ccm_rx_dwork);

	/* After 13 counts (4 * 3,25) then 3.25 पूर्णांकervals are expired */
	अगर (peer_mep->ccm_rx_count_miss < 13) अणु
		/* 3.25 पूर्णांकervals are NOT expired without CCM reception */
		peer_mep->ccm_rx_count_miss++;

		/* Start समयr again */
		ccm_rx_समयr_start(peer_mep);
	पूर्ण अन्यथा अणु
		/* 3.25 पूर्णांकervals are expired without CCM reception.
		 * CCM defect detected
		 */
		peer_mep->cc_status.ccm_defect = true;

		/* Change in CCM defect status - notअगरy */
		rcu_पढ़ो_lock();
		b_port = rcu_dereference(peer_mep->mep->b_port);
		अगर (b_port)
			br_cfm_notअगरy(RTM_NEWLINK, b_port);
		rcu_पढ़ो_unlock();
	पूर्ण
पूर्ण

अटल u32 ccm_tlv_extract(काष्ठा sk_buff *skb, u32 index,
			   काष्ठा br_cfm_peer_mep *peer_mep)
अणु
	__be32 *s_tlv;
	__be32 _s_tlv;
	u32 h_s_tlv;
	u8 *e_tlv;
	u8 _e_tlv;

	e_tlv = skb_header_poपूर्णांकer(skb, index, माप(_e_tlv), &_e_tlv);
	अगर (!e_tlv)
		वापस 0;

	/* TLV is present - get the status TLV */
	s_tlv = skb_header_poपूर्णांकer(skb,
				   index,
				   माप(_s_tlv), &_s_tlv);
	अगर (!s_tlv)
		वापस 0;

	h_s_tlv = ntohl(*s_tlv);
	अगर ((h_s_tlv >> 24) == CFM_IF_STATUS_TLV_TYPE) अणु
		/* Interface status TLV */
		peer_mep->cc_status.tlv_seen = true;
		peer_mep->cc_status.अगर_tlv_value = (h_s_tlv & 0xFF);
	पूर्ण

	अगर ((h_s_tlv >> 24) == CFM_PORT_STATUS_TLV_TYPE) अणु
		/* Port status TLV */
		peer_mep->cc_status.tlv_seen = true;
		peer_mep->cc_status.port_tlv_value = (h_s_tlv & 0xFF);
	पूर्ण

	/* The Sender ID TLV is not handled */
	/* The Organization-Specअगरic TLV is not handled */

	/* Return the length of this tlv.
	 * This is the length of the value field plus 3 bytes क्रम size of type
	 * field and length field
	 */
	वापस ((h_s_tlv >> 8) & 0xFFFF) + 3;
पूर्ण

/* note: alपढ़ोy called with rcu_पढ़ो_lock */
अटल पूर्णांक br_cfm_frame_rx(काष्ठा net_bridge_port *port, काष्ठा sk_buff *skb)
अणु
	u32 mdlevel, पूर्णांकerval, size, index, max;
	स्थिर काष्ठा br_cfm_common_hdr *hdr;
	काष्ठा br_cfm_peer_mep *peer_mep;
	स्थिर काष्ठा br_cfm_maid *maid;
	काष्ठा br_cfm_common_hdr _hdr;
	काष्ठा br_cfm_maid _maid;
	काष्ठा br_cfm_mep *mep;
	काष्ठा net_bridge *br;
	__be32 *snumber;
	__be32 _snumber;
	__be16 *mepid;
	__be16 _mepid;

	अगर (port->state == BR_STATE_DISABLED)
		वापस 0;

	hdr = skb_header_poपूर्णांकer(skb, 0, माप(_hdr), &_hdr);
	अगर (!hdr)
		वापस 1;

	br = port->br;
	mep = br_mep_find_अगरindex(br, port->dev->अगरindex);
	अगर (unlikely(!mep))
		/* No MEP on this port - must be क्रमwarded */
		वापस 0;

	mdlevel = hdr->mdlevel_version >> 5;
	अगर (mdlevel > mep->config.mdlevel)
		/* The level is above this MEP level - must be क्रमwarded */
		वापस 0;

	अगर ((hdr->mdlevel_version & 0x1F) != 0) अणु
		/* Invalid version */
		mep->status.version_unexp_seen = true;
		वापस 1;
	पूर्ण

	अगर (mdlevel < mep->config.mdlevel) अणु
		/* The level is below this MEP level */
		mep->status.rx_level_low_seen = true;
		वापस 1;
	पूर्ण

	अगर (hdr->opcode == BR_CFM_OPCODE_CCM) अणु
		/* CCM PDU received. */
		/* MA ID is after common header + sequence number + MEP ID */
		maid = skb_header_poपूर्णांकer(skb,
					  CFM_CCM_PDU_MAID_OFFSET,
					  माप(_maid), &_maid);
		अगर (!maid)
			वापस 1;
		अगर (स_भेद(maid->data, mep->cc_config.exp_maid.data,
			   माप(maid->data)))
			/* MA ID not as expected */
			वापस 1;

		/* MEP ID is after common header + sequence number */
		mepid = skb_header_poपूर्णांकer(skb,
					   CFM_CCM_PDU_MEPID_OFFSET,
					   माप(_mepid), &_mepid);
		अगर (!mepid)
			वापस 1;
		peer_mep = br_peer_mep_find(mep, (u32)ntohs(*mepid));
		अगर (!peer_mep)
			वापस 1;

		/* Interval is in common header flags */
		पूर्णांकerval = hdr->flags & 0x07;
		अगर (mep->cc_config.exp_पूर्णांकerval != pdu_to_पूर्णांकerval(पूर्णांकerval))
			/* Interval not as expected */
			वापस 1;

		/* A valid CCM frame is received */
		अगर (peer_mep->cc_status.ccm_defect) अणु
			peer_mep->cc_status.ccm_defect = false;

			/* Change in CCM defect status - notअगरy */
			br_cfm_notअगरy(RTM_NEWLINK, port);

			/* Start CCM RX समयr */
			ccm_rx_समयr_start(peer_mep);
		पूर्ण

		peer_mep->cc_status.seen = true;
		peer_mep->ccm_rx_count_miss = 0;

		/* RDI is in common header flags */
		peer_mep->cc_status.rdi = (hdr->flags & 0x80) ? true : false;

		/* Sequence number is after common header */
		snumber = skb_header_poपूर्णांकer(skb,
					     CFM_CCM_PDU_SEQNR_OFFSET,
					     माप(_snumber), &_snumber);
		अगर (!snumber)
			वापस 1;
		अगर (ntohl(*snumber) != (mep->ccm_rx_snumber + 1))
			/* Unexpected sequence number */
			peer_mep->cc_status.seq_unexp_seen = true;

		mep->ccm_rx_snumber = ntohl(*snumber);

		/* TLV end is after common header + sequence number + MEP ID +
		 * MA ID + ITU reserved
		 */
		index = CFM_CCM_PDU_TLV_OFFSET;
		max = 0;
		करो अणु /* Handle all TLVs */
			size = ccm_tlv_extract(skb, index, peer_mep);
			index += size;
			max += 1;
		पूर्ण जबतक (size != 0 && max < 4); /* Max four TLVs possible */

		वापस 1;
	पूर्ण

	mep->status.opcode_unexp_seen = true;

	वापस 1;
पूर्ण

अटल काष्ठा br_frame_type cfm_frame_type __पढ़ो_mostly = अणु
	.type = cpu_to_be16(ETH_P_CFM),
	.frame_handler = br_cfm_frame_rx,
पूर्ण;

पूर्णांक br_cfm_mep_create(काष्ठा net_bridge *br,
		      स्थिर u32 instance,
		      काष्ठा br_cfm_mep_create *स्थिर create,
		      काष्ठा netlink_ext_ack *extack)
अणु
	काष्ठा net_bridge_port *p;
	काष्ठा br_cfm_mep *mep;

	ASSERT_RTNL();

	अगर (create->करोमुख्य == BR_CFM_VLAN) अणु
		NL_SET_ERR_MSG_MOD(extack,
				   "VLAN domain not supported");
		वापस -EINVAL;
	पूर्ण
	अगर (create->करोमुख्य != BR_CFM_PORT) अणु
		NL_SET_ERR_MSG_MOD(extack,
				   "Invalid domain value");
		वापस -EINVAL;
	पूर्ण
	अगर (create->direction == BR_CFM_MEP_सूचीECTION_UP) अणु
		NL_SET_ERR_MSG_MOD(extack,
				   "Up-MEP not supported");
		वापस -EINVAL;
	पूर्ण
	अगर (create->direction != BR_CFM_MEP_सूचीECTION_DOWN) अणु
		NL_SET_ERR_MSG_MOD(extack,
				   "Invalid direction value");
		वापस -EINVAL;
	पूर्ण
	p = br_mep_get_port(br, create->अगरindex);
	अगर (!p) अणु
		NL_SET_ERR_MSG_MOD(extack,
				   "Port is not related to bridge");
		वापस -EINVAL;
	पूर्ण
	mep = br_mep_find(br, instance);
	अगर (mep) अणु
		NL_SET_ERR_MSG_MOD(extack,
				   "MEP instance already exists");
		वापस -EEXIST;
	पूर्ण

	/* In PORT करोमुख्य only one instance can be created per port */
	अगर (create->करोमुख्य == BR_CFM_PORT) अणु
		mep = br_mep_find_अगरindex(br, create->अगरindex);
		अगर (mep) अणु
			NL_SET_ERR_MSG_MOD(extack,
					   "Only one Port MEP on a port allowed");
			वापस -EINVAL;
		पूर्ण
	पूर्ण

	mep = kzalloc(माप(*mep), GFP_KERNEL);
	अगर (!mep)
		वापस -ENOMEM;

	mep->create = *create;
	mep->instance = instance;
	rcu_assign_poपूर्णांकer(mep->b_port, p);

	INIT_HLIST_HEAD(&mep->peer_mep_list);
	INIT_DELAYED_WORK(&mep->ccm_tx_dwork, ccm_tx_work_expired);

	अगर (hlist_empty(&br->mep_list))
		br_add_frame(br, &cfm_frame_type);

	hlist_add_tail_rcu(&mep->head, &br->mep_list);

	वापस 0;
पूर्ण

अटल व्योम mep_delete_implementation(काष्ठा net_bridge *br,
				      काष्ठा br_cfm_mep *mep)
अणु
	काष्ठा br_cfm_peer_mep *peer_mep;
	काष्ठा hlist_node *n_store;

	ASSERT_RTNL();

	/* Empty and मुक्त peer MEP list */
	hlist_क्रम_each_entry_safe(peer_mep, n_store, &mep->peer_mep_list, head) अणु
		cancel_delayed_work_sync(&peer_mep->ccm_rx_dwork);
		hlist_del_rcu(&peer_mep->head);
		kमुक्त_rcu(peer_mep, rcu);
	पूर्ण

	cancel_delayed_work_sync(&mep->ccm_tx_dwork);

	RCU_INIT_POINTER(mep->b_port, शून्य);
	hlist_del_rcu(&mep->head);
	kमुक्त_rcu(mep, rcu);

	अगर (hlist_empty(&br->mep_list))
		br_del_frame(br, &cfm_frame_type);
पूर्ण

पूर्णांक br_cfm_mep_delete(काष्ठा net_bridge *br,
		      स्थिर u32 instance,
		      काष्ठा netlink_ext_ack *extack)
अणु
	काष्ठा br_cfm_mep *mep;

	ASSERT_RTNL();

	mep = br_mep_find(br, instance);
	अगर (!mep) अणु
		NL_SET_ERR_MSG_MOD(extack,
				   "MEP instance does not exists");
		वापस -ENOENT;
	पूर्ण

	mep_delete_implementation(br, mep);

	वापस 0;
पूर्ण

पूर्णांक br_cfm_mep_config_set(काष्ठा net_bridge *br,
			  स्थिर u32 instance,
			  स्थिर काष्ठा br_cfm_mep_config *स्थिर config,
			  काष्ठा netlink_ext_ack *extack)
अणु
	काष्ठा br_cfm_mep *mep;

	ASSERT_RTNL();

	mep = br_mep_find(br, instance);
	अगर (!mep) अणु
		NL_SET_ERR_MSG_MOD(extack,
				   "MEP instance does not exists");
		वापस -ENOENT;
	पूर्ण

	mep->config = *config;

	वापस 0;
पूर्ण

पूर्णांक br_cfm_cc_config_set(काष्ठा net_bridge *br,
			 स्थिर u32 instance,
			 स्थिर काष्ठा br_cfm_cc_config *स्थिर config,
			 काष्ठा netlink_ext_ack *extack)
अणु
	काष्ठा br_cfm_peer_mep *peer_mep;
	काष्ठा br_cfm_mep *mep;

	ASSERT_RTNL();

	mep = br_mep_find(br, instance);
	अगर (!mep) अणु
		NL_SET_ERR_MSG_MOD(extack,
				   "MEP instance does not exists");
		वापस -ENOENT;
	पूर्ण

	/* Check क्रम no change in configuration */
	अगर (स_भेद(config, &mep->cc_config, माप(*config)) == 0)
		वापस 0;

	अगर (config->enable && !mep->cc_config.enable)
		/* CC is enabled */
		hlist_क्रम_each_entry(peer_mep, &mep->peer_mep_list, head)
			cc_peer_enable(peer_mep);

	अगर (!config->enable && mep->cc_config.enable)
		/* CC is disabled */
		hlist_क्रम_each_entry(peer_mep, &mep->peer_mep_list, head)
			cc_peer_disable(peer_mep);

	mep->cc_config = *config;
	mep->ccm_rx_snumber = 0;
	mep->ccm_tx_snumber = 1;

	वापस 0;
पूर्ण

पूर्णांक br_cfm_cc_peer_mep_add(काष्ठा net_bridge *br, स्थिर u32 instance,
			   u32 mepid,
			   काष्ठा netlink_ext_ack *extack)
अणु
	काष्ठा br_cfm_peer_mep *peer_mep;
	काष्ठा br_cfm_mep *mep;

	ASSERT_RTNL();

	mep = br_mep_find(br, instance);
	अगर (!mep) अणु
		NL_SET_ERR_MSG_MOD(extack,
				   "MEP instance does not exists");
		वापस -ENOENT;
	पूर्ण

	peer_mep = br_peer_mep_find(mep, mepid);
	अगर (peer_mep) अणु
		NL_SET_ERR_MSG_MOD(extack,
				   "Peer MEP-ID already exists");
		वापस -EEXIST;
	पूर्ण

	peer_mep = kzalloc(माप(*peer_mep), GFP_KERNEL);
	अगर (!peer_mep)
		वापस -ENOMEM;

	peer_mep->mepid = mepid;
	peer_mep->mep = mep;
	INIT_DELAYED_WORK(&peer_mep->ccm_rx_dwork, ccm_rx_work_expired);

	अगर (mep->cc_config.enable)
		cc_peer_enable(peer_mep);

	hlist_add_tail_rcu(&peer_mep->head, &mep->peer_mep_list);

	वापस 0;
पूर्ण

पूर्णांक br_cfm_cc_peer_mep_हटाओ(काष्ठा net_bridge *br, स्थिर u32 instance,
			      u32 mepid,
			      काष्ठा netlink_ext_ack *extack)
अणु
	काष्ठा br_cfm_peer_mep *peer_mep;
	काष्ठा br_cfm_mep *mep;

	ASSERT_RTNL();

	mep = br_mep_find(br, instance);
	अगर (!mep) अणु
		NL_SET_ERR_MSG_MOD(extack,
				   "MEP instance does not exists");
		वापस -ENOENT;
	पूर्ण

	peer_mep = br_peer_mep_find(mep, mepid);
	अगर (!peer_mep) अणु
		NL_SET_ERR_MSG_MOD(extack,
				   "Peer MEP-ID does not exists");
		वापस -ENOENT;
	पूर्ण

	cc_peer_disable(peer_mep);

	hlist_del_rcu(&peer_mep->head);
	kमुक्त_rcu(peer_mep, rcu);

	वापस 0;
पूर्ण

पूर्णांक br_cfm_cc_rdi_set(काष्ठा net_bridge *br, स्थिर u32 instance,
		      स्थिर bool rdi, काष्ठा netlink_ext_ack *extack)
अणु
	काष्ठा br_cfm_mep *mep;

	ASSERT_RTNL();

	mep = br_mep_find(br, instance);
	अगर (!mep) अणु
		NL_SET_ERR_MSG_MOD(extack,
				   "MEP instance does not exists");
		वापस -ENOENT;
	पूर्ण

	mep->rdi = rdi;

	वापस 0;
पूर्ण

पूर्णांक br_cfm_cc_ccm_tx(काष्ठा net_bridge *br, स्थिर u32 instance,
		     स्थिर काष्ठा br_cfm_cc_ccm_tx_info *स्थिर tx_info,
		     काष्ठा netlink_ext_ack *extack)
अणु
	काष्ठा br_cfm_mep *mep;

	ASSERT_RTNL();

	mep = br_mep_find(br, instance);
	अगर (!mep) अणु
		NL_SET_ERR_MSG_MOD(extack,
				   "MEP instance does not exists");
		वापस -ENOENT;
	पूर्ण

	अगर (स_भेद(tx_info, &mep->cc_ccm_tx_info, माप(*tx_info)) == 0) अणु
		/* No change in tx_info. */
		अगर (mep->cc_ccm_tx_info.period == 0)
			/* Transmission is not enabled - just वापस */
			वापस 0;

		/* Transmission is ongoing, the end समय is recalculated */
		mep->ccm_tx_end = jअगरfies +
				  usecs_to_jअगरfies(tx_info->period * 1000000);
		वापस 0;
	पूर्ण

	अगर (tx_info->period == 0 && mep->cc_ccm_tx_info.period == 0)
		/* Some change in info and transmission is not ongoing */
		जाओ save;

	अगर (tx_info->period != 0 && mep->cc_ccm_tx_info.period != 0) अणु
		/* Some change in info and transmission is ongoing
		 * The end समय is recalculated
		 */
		mep->ccm_tx_end = jअगरfies +
				  usecs_to_jअगरfies(tx_info->period * 1000000);

		जाओ save;
	पूर्ण

	अगर (tx_info->period == 0 && mep->cc_ccm_tx_info.period != 0) अणु
		cancel_delayed_work_sync(&mep->ccm_tx_dwork);
		जाओ save;
	पूर्ण

	/* Start delayed work to transmit CCM frames. It is करोne with zero delay
	 * to send first frame immediately
	 */
	mep->ccm_tx_end = jअगरfies + usecs_to_jअगरfies(tx_info->period * 1000000);
	queue_delayed_work(प्रणाली_wq, &mep->ccm_tx_dwork, 0);

save:
	mep->cc_ccm_tx_info = *tx_info;

	वापस 0;
पूर्ण

पूर्णांक br_cfm_mep_count(काष्ठा net_bridge *br, u32 *count)
अणु
	काष्ठा br_cfm_mep *mep;

	*count = 0;

	rcu_पढ़ो_lock();
	hlist_क्रम_each_entry_rcu(mep, &br->mep_list, head)
		*count += 1;
	rcu_पढ़ो_unlock();

	वापस 0;
पूर्ण

पूर्णांक br_cfm_peer_mep_count(काष्ठा net_bridge *br, u32 *count)
अणु
	काष्ठा br_cfm_peer_mep *peer_mep;
	काष्ठा br_cfm_mep *mep;

	*count = 0;

	rcu_पढ़ो_lock();
	hlist_क्रम_each_entry_rcu(mep, &br->mep_list, head)
		hlist_क्रम_each_entry_rcu(peer_mep, &mep->peer_mep_list, head)
			*count += 1;
	rcu_पढ़ो_unlock();

	वापस 0;
पूर्ण

bool br_cfm_created(काष्ठा net_bridge *br)
अणु
	वापस !hlist_empty(&br->mep_list);
पूर्ण

/* Deletes the CFM instances on a specअगरic bridge port
 */
व्योम br_cfm_port_del(काष्ठा net_bridge *br, काष्ठा net_bridge_port *port)
अणु
	काष्ठा hlist_node *n_store;
	काष्ठा br_cfm_mep *mep;

	ASSERT_RTNL();

	hlist_क्रम_each_entry_safe(mep, n_store, &br->mep_list, head)
		अगर (mep->create.अगरindex == port->dev->अगरindex)
			mep_delete_implementation(br, mep);
पूर्ण
