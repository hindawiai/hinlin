<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 *    Copyright IBM Corp. 2007, 2009
 *    Author(s): Utz Bacher <utz.bacher@de.ibm.com>,
 *		 Frank Pavlic <fpavlic@de.ibm.com>,
 *		 Thomas Spatzier <tspat@de.ibm.com>,
 *		 Frank Blaschka <frank.blaschka@de.ibm.com>
 */

#घोषणा KMSG_COMPONENT "qeth"
#घोषणा pr_fmt(fmt) KMSG_COMPONENT ": " fmt

#समावेश <linux/module.h>
#समावेश <linux/moduleparam.h>
#समावेश <linux/माला.स>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/kernel.h>
#समावेश <linux/slab.h>
#समावेश <linux/etherdevice.h>
#समावेश <linux/अगर_bridge.h>
#समावेश <linux/list.h>
#समावेश <linux/hash.h>
#समावेश <linux/hashtable.h>
#समावेश <net/चयनdev.h>
#समावेश <यंत्र/chsc.h>
#समावेश <यंत्र/css_अक्षरs.h>
#समावेश <यंत्र/setup.h>
#समावेश "qeth_core.h"
#समावेश "qeth_l2.h"

अटल पूर्णांक qeth_l2_setdelmac_makerc(काष्ठा qeth_card *card, u16 retcode)
अणु
	पूर्णांक rc;

	अगर (retcode)
		QETH_CARD_TEXT_(card, 2, "err%04x", retcode);
	चयन (retcode) अणु
	हाल IPA_RC_SUCCESS:
		rc = 0;
		अवरोध;
	हाल IPA_RC_L2_UNSUPPORTED_CMD:
		rc = -EOPNOTSUPP;
		अवरोध;
	हाल IPA_RC_L2_ADDR_TABLE_FULL:
		rc = -ENOSPC;
		अवरोध;
	हाल IPA_RC_L2_DUP_MAC:
	हाल IPA_RC_L2_DUP_LAYER3_MAC:
		rc = -EADDRINUSE;
		अवरोध;
	हाल IPA_RC_L2_MAC_NOT_AUTH_BY_HYP:
	हाल IPA_RC_L2_MAC_NOT_AUTH_BY_ADP:
		rc = -EADDRNOTAVAIL;
		अवरोध;
	हाल IPA_RC_L2_MAC_NOT_FOUND:
		rc = -ENOENT;
		अवरोध;
	शेष:
		rc = -EIO;
		अवरोध;
	पूर्ण
	वापस rc;
पूर्ण

अटल पूर्णांक qeth_l2_send_setdelmac_cb(काष्ठा qeth_card *card,
				     काष्ठा qeth_reply *reply,
				     अचिन्हित दीर्घ data)
अणु
	काष्ठा qeth_ipa_cmd *cmd = (काष्ठा qeth_ipa_cmd *) data;

	वापस qeth_l2_setdelmac_makerc(card, cmd->hdr.वापस_code);
पूर्ण

अटल पूर्णांक qeth_l2_send_setdelmac(काष्ठा qeth_card *card, __u8 *mac,
			   क्रमागत qeth_ipa_cmds ipacmd)
अणु
	काष्ठा qeth_ipa_cmd *cmd;
	काष्ठा qeth_cmd_buffer *iob;

	QETH_CARD_TEXT(card, 2, "L2sdmac");
	iob = qeth_ipa_alloc_cmd(card, ipacmd, QETH_PROT_IPV4,
				 IPA_DATA_SIZखातापूर्ण(setdelmac));
	अगर (!iob)
		वापस -ENOMEM;
	cmd = __ipa_cmd(iob);
	cmd->data.setdelmac.mac_length = ETH_ALEN;
	ether_addr_copy(cmd->data.setdelmac.mac, mac);
	वापस qeth_send_ipa_cmd(card, iob, qeth_l2_send_setdelmac_cb, शून्य);
पूर्ण

अटल पूर्णांक qeth_l2_send_seपंचांगac(काष्ठा qeth_card *card, __u8 *mac)
अणु
	पूर्णांक rc;

	QETH_CARD_TEXT(card, 2, "L2Setmac");
	rc = qeth_l2_send_setdelmac(card, mac, IPA_CMD_SETVMAC);
	अगर (rc == 0) अणु
		dev_info(&card->gdev->dev,
			 "MAC address %pM successfully registered\n", mac);
	पूर्ण अन्यथा अणु
		चयन (rc) अणु
		हाल -EADDRINUSE:
			dev_warn(&card->gdev->dev,
				"MAC address %pM already exists\n", mac);
			अवरोध;
		हाल -EADDRNOTAVAIL:
			dev_warn(&card->gdev->dev,
				"MAC address %pM is not authorized\n", mac);
			अवरोध;
		पूर्ण
	पूर्ण
	वापस rc;
पूर्ण

अटल पूर्णांक qeth_l2_ग_लिखो_mac(काष्ठा qeth_card *card, u8 *mac)
अणु
	क्रमागत qeth_ipa_cmds cmd = is_multicast_ether_addr(mac) ?
					IPA_CMD_SETGMAC : IPA_CMD_SETVMAC;
	पूर्णांक rc;

	QETH_CARD_TEXT(card, 2, "L2Wmac");
	rc = qeth_l2_send_setdelmac(card, mac, cmd);
	अगर (rc == -EADDRINUSE)
		QETH_DBF_MESSAGE(2, "MAC already registered on device %x\n",
				 CARD_DEVID(card));
	अन्यथा अगर (rc)
		QETH_DBF_MESSAGE(2, "Failed to register MAC on device %x: %d\n",
				 CARD_DEVID(card), rc);
	वापस rc;
पूर्ण

अटल पूर्णांक qeth_l2_हटाओ_mac(काष्ठा qeth_card *card, u8 *mac)
अणु
	क्रमागत qeth_ipa_cmds cmd = is_multicast_ether_addr(mac) ?
					IPA_CMD_DELGMAC : IPA_CMD_DELVMAC;
	पूर्णांक rc;

	QETH_CARD_TEXT(card, 2, "L2Rmac");
	rc = qeth_l2_send_setdelmac(card, mac, cmd);
	अगर (rc)
		QETH_DBF_MESSAGE(2, "Failed to delete MAC on device %u: %d\n",
				 CARD_DEVID(card), rc);
	वापस rc;
पूर्ण

अटल व्योम qeth_l2_drain_rx_mode_cache(काष्ठा qeth_card *card)
अणु
	काष्ठा qeth_mac *mac;
	काष्ठा hlist_node *पंचांगp;
	पूर्णांक i;

	hash_क्रम_each_safe(card->rx_mode_addrs, i, पंचांगp, mac, hnode) अणु
		hash_del(&mac->hnode);
		kमुक्त(mac);
	पूर्ण
पूर्ण

अटल व्योम qeth_l2_fill_header(काष्ठा qeth_qdio_out_q *queue,
				काष्ठा qeth_hdr *hdr, काष्ठा sk_buff *skb,
				__be16 proto, अचिन्हित पूर्णांक data_len)
अणु
	पूर्णांक cast_type = qeth_get_ether_cast_type(skb);
	काष्ठा vlan_ethhdr *veth = vlan_eth_hdr(skb);

	hdr->hdr.l2.pkt_length = data_len;

	अगर (skb_is_gso(skb)) अणु
		hdr->hdr.l2.id = QETH_HEADER_TYPE_L2_TSO;
	पूर्ण अन्यथा अणु
		hdr->hdr.l2.id = QETH_HEADER_TYPE_LAYER2;
		अगर (skb->ip_summed == CHECKSUM_PARTIAL)
			qeth_tx_csum(skb, &hdr->hdr.l2.flags[1], proto);
	पूर्ण

	/* set byte byte 3 to casting flags */
	अगर (cast_type == RTN_MULTICAST)
		hdr->hdr.l2.flags[2] |= QETH_LAYER2_FLAG_MULTICAST;
	अन्यथा अगर (cast_type == RTN_BROADCAST)
		hdr->hdr.l2.flags[2] |= QETH_LAYER2_FLAG_BROADCAST;
	अन्यथा
		hdr->hdr.l2.flags[2] |= QETH_LAYER2_FLAG_UNICAST;

	/* VSWITCH relies on the VLAN
	 * inक्रमmation to be present in
	 * the QDIO header */
	अगर (veth->h_vlan_proto == htons(ETH_P_8021Q)) अणु
		hdr->hdr.l2.flags[2] |= QETH_LAYER2_FLAG_VLAN;
		hdr->hdr.l2.vlan_id = ntohs(veth->h_vlan_TCI);
	पूर्ण
पूर्ण

अटल पूर्णांक qeth_l2_setdelvlan_makerc(काष्ठा qeth_card *card, u16 retcode)
अणु
	अगर (retcode)
		QETH_CARD_TEXT_(card, 2, "err%04x", retcode);

	चयन (retcode) अणु
	हाल IPA_RC_SUCCESS:
		वापस 0;
	हाल IPA_RC_L2_INVALID_VLAN_ID:
		वापस -EINVAL;
	हाल IPA_RC_L2_DUP_VLAN_ID:
		वापस -EEXIST;
	हाल IPA_RC_L2_VLAN_ID_NOT_FOUND:
		वापस -ENOENT;
	हाल IPA_RC_L2_VLAN_ID_NOT_ALLOWED:
		वापस -EPERM;
	शेष:
		वापस -EIO;
	पूर्ण
पूर्ण

अटल पूर्णांक qeth_l2_send_setdelvlan_cb(काष्ठा qeth_card *card,
				      काष्ठा qeth_reply *reply,
				      अचिन्हित दीर्घ data)
अणु
	काष्ठा qeth_ipa_cmd *cmd = (काष्ठा qeth_ipa_cmd *) data;

	QETH_CARD_TEXT(card, 2, "L2sdvcb");
	अगर (cmd->hdr.वापस_code) अणु
		QETH_DBF_MESSAGE(2, "Error in processing VLAN %u on device %x: %#x.\n",
				 cmd->data.setdelvlan.vlan_id,
				 CARD_DEVID(card), cmd->hdr.वापस_code);
		QETH_CARD_TEXT_(card, 2, "L2VL%4x", cmd->hdr.command);
	पूर्ण
	वापस qeth_l2_setdelvlan_makerc(card, cmd->hdr.वापस_code);
पूर्ण

अटल पूर्णांक qeth_l2_send_setdelvlan(काष्ठा qeth_card *card, __u16 i,
				   क्रमागत qeth_ipa_cmds ipacmd)
अणु
	काष्ठा qeth_ipa_cmd *cmd;
	काष्ठा qeth_cmd_buffer *iob;

	QETH_CARD_TEXT_(card, 4, "L2sdv%x", ipacmd);
	iob = qeth_ipa_alloc_cmd(card, ipacmd, QETH_PROT_IPV4,
				 IPA_DATA_SIZखातापूर्ण(setdelvlan));
	अगर (!iob)
		वापस -ENOMEM;
	cmd = __ipa_cmd(iob);
	cmd->data.setdelvlan.vlan_id = i;
	वापस qeth_send_ipa_cmd(card, iob, qeth_l2_send_setdelvlan_cb, शून्य);
पूर्ण

अटल पूर्णांक qeth_l2_vlan_rx_add_vid(काष्ठा net_device *dev,
				   __be16 proto, u16 vid)
अणु
	काष्ठा qeth_card *card = dev->ml_priv;

	QETH_CARD_TEXT_(card, 4, "aid:%d", vid);
	अगर (!vid)
		वापस 0;

	वापस qeth_l2_send_setdelvlan(card, vid, IPA_CMD_SETVLAN);
पूर्ण

अटल पूर्णांक qeth_l2_vlan_rx_समाप्त_vid(काष्ठा net_device *dev,
				    __be16 proto, u16 vid)
अणु
	काष्ठा qeth_card *card = dev->ml_priv;

	QETH_CARD_TEXT_(card, 4, "kid:%d", vid);
	अगर (!vid)
		वापस 0;

	वापस qeth_l2_send_setdelvlan(card, vid, IPA_CMD_DELVLAN);
पूर्ण

अटल व्योम qeth_l2_set_pnso_mode(काष्ठा qeth_card *card,
				  क्रमागत qeth_pnso_mode mode)
अणु
	spin_lock_irq(get_ccwdev_lock(CARD_RDEV(card)));
	WRITE_ONCE(card->info.pnso_mode, mode);
	spin_unlock_irq(get_ccwdev_lock(CARD_RDEV(card)));

	अगर (mode == QETH_PNSO_NONE)
		drain_workqueue(card->event_wq);
पूर्ण

अटल व्योम qeth_l2_dev2br_fdb_flush(काष्ठा qeth_card *card)
अणु
	काष्ठा चयनdev_notअगरier_fdb_info info;

	QETH_CARD_TEXT(card, 2, "fdbflush");

	info.addr = शून्य;
	/* flush all VLANs: */
	info.vid = 0;
	info.added_by_user = false;
	info.offloaded = true;

	call_चयनdev_notअगरiers(SWITCHDEV_FDB_FLUSH_TO_BRIDGE,
				 card->dev, &info.info, शून्य);
पूर्ण

अटल पूर्णांक qeth_l2_request_initial_mac(काष्ठा qeth_card *card)
अणु
	पूर्णांक rc = 0;

	QETH_CARD_TEXT(card, 2, "l2reqmac");

	अगर (MACHINE_IS_VM) अणु
		rc = qeth_vm_request_mac(card);
		अगर (!rc)
			जाओ out;
		QETH_DBF_MESSAGE(2, "z/VM MAC Service failed on device %x: %#x\n",
				 CARD_DEVID(card), rc);
		QETH_CARD_TEXT_(card, 2, "err%04x", rc);
		/* fall back to alternative mechanism: */
	पूर्ण

	अगर (!IS_OSN(card)) अणु
		rc = qeth_setadpparms_change_macaddr(card);
		अगर (!rc)
			जाओ out;
		QETH_DBF_MESSAGE(2, "READ_MAC Assist failed on device %x: %#x\n",
				 CARD_DEVID(card), rc);
		QETH_CARD_TEXT_(card, 2, "1err%04x", rc);
		/* fall back once more: */
	पूर्ण

	/* some devices करोn't support a custom MAC address: */
	अगर (IS_OSM(card) || IS_OSX(card))
		वापस (rc) ? rc : -EADDRNOTAVAIL;
	eth_hw_addr_अक्रमom(card->dev);

out:
	QETH_CARD_HEX(card, 2, card->dev->dev_addr, card->dev->addr_len);
	वापस 0;
पूर्ण

अटल व्योम qeth_l2_रेजिस्टर_dev_addr(काष्ठा qeth_card *card)
अणु
	अगर (!is_valid_ether_addr(card->dev->dev_addr))
		qeth_l2_request_initial_mac(card);

	अगर (!IS_OSN(card) && !qeth_l2_send_seपंचांगac(card, card->dev->dev_addr))
		card->info.dev_addr_is_रेजिस्टरed = 1;
	अन्यथा
		card->info.dev_addr_is_रेजिस्टरed = 0;
पूर्ण

अटल पूर्णांक qeth_l2_validate_addr(काष्ठा net_device *dev)
अणु
	काष्ठा qeth_card *card = dev->ml_priv;

	अगर (card->info.dev_addr_is_रेजिस्टरed)
		वापस eth_validate_addr(dev);

	QETH_CARD_TEXT(card, 4, "nomacadr");
	वापस -EPERM;
पूर्ण

अटल पूर्णांक qeth_l2_set_mac_address(काष्ठा net_device *dev, व्योम *p)
अणु
	काष्ठा sockaddr *addr = p;
	काष्ठा qeth_card *card = dev->ml_priv;
	u8 old_addr[ETH_ALEN];
	पूर्णांक rc = 0;

	QETH_CARD_TEXT(card, 3, "setmac");

	अगर (IS_OSM(card) || IS_OSX(card)) अणु
		QETH_CARD_TEXT(card, 3, "setmcTYP");
		वापस -EOPNOTSUPP;
	पूर्ण
	QETH_CARD_HEX(card, 3, addr->sa_data, ETH_ALEN);
	अगर (!is_valid_ether_addr(addr->sa_data))
		वापस -EADDRNOTAVAIL;

	/* करोn't रेजिस्टर the same address twice */
	अगर (ether_addr_equal_64bits(dev->dev_addr, addr->sa_data) &&
	    card->info.dev_addr_is_रेजिस्टरed)
		वापस 0;

	/* add the new address, चयन over, drop the old */
	rc = qeth_l2_send_seपंचांगac(card, addr->sa_data);
	अगर (rc)
		वापस rc;
	ether_addr_copy(old_addr, dev->dev_addr);
	ether_addr_copy(dev->dev_addr, addr->sa_data);

	अगर (card->info.dev_addr_is_रेजिस्टरed)
		qeth_l2_हटाओ_mac(card, old_addr);
	card->info.dev_addr_is_रेजिस्टरed = 1;
	वापस 0;
पूर्ण

अटल व्योम qeth_l2_promisc_to_bridge(काष्ठा qeth_card *card, bool enable)
अणु
	पूर्णांक role;
	पूर्णांक rc;

	QETH_CARD_TEXT(card, 3, "pmisc2br");

	अगर (enable) अणु
		अगर (card->options.sbp.reflect_promisc_primary)
			role = QETH_SBP_ROLE_PRIMARY;
		अन्यथा
			role = QETH_SBP_ROLE_SECONDARY;
	पूर्ण अन्यथा
		role = QETH_SBP_ROLE_NONE;

	rc = qeth_bridgeport_setrole(card, role);
	QETH_CARD_TEXT_(card, 2, "bpm%c%04x", enable ? '+' : '-', rc);
	अगर (!rc) अणु
		card->options.sbp.role = role;
		card->info.promisc_mode = enable;
	पूर्ण
पूर्ण

अटल व्योम qeth_l2_set_promisc_mode(काष्ठा qeth_card *card)
अणु
	bool enable = card->dev->flags & IFF_PROMISC;

	अगर (card->info.promisc_mode == enable)
		वापस;

	अगर (qeth_adp_supported(card, IPA_SETADP_SET_PROMISC_MODE)) अणु
		qeth_setadp_promisc_mode(card, enable);
	पूर्ण अन्यथा अणु
		mutex_lock(&card->sbp_lock);
		अगर (card->options.sbp.reflect_promisc)
			qeth_l2_promisc_to_bridge(card, enable);
		mutex_unlock(&card->sbp_lock);
	पूर्ण
पूर्ण

/* New MAC address is added to the hash table and marked to be written on card
 * only अगर there is not in the hash table storage alपढ़ोy
 *
*/
अटल व्योम qeth_l2_add_mac(काष्ठा qeth_card *card, काष्ठा netdev_hw_addr *ha)
अणु
	u32 mac_hash = get_unaligned((u32 *)(&ha->addr[2]));
	काष्ठा qeth_mac *mac;

	hash_क्रम_each_possible(card->rx_mode_addrs, mac, hnode, mac_hash) अणु
		अगर (ether_addr_equal_64bits(ha->addr, mac->mac_addr)) अणु
			mac->disp_flag = QETH_DISP_ADDR_DO_NOTHING;
			वापस;
		पूर्ण
	पूर्ण

	mac = kzalloc(माप(काष्ठा qeth_mac), GFP_ATOMIC);
	अगर (!mac)
		वापस;

	ether_addr_copy(mac->mac_addr, ha->addr);
	mac->disp_flag = QETH_DISP_ADDR_ADD;

	hash_add(card->rx_mode_addrs, &mac->hnode, mac_hash);
पूर्ण

अटल व्योम qeth_l2_rx_mode_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा qeth_card *card = container_of(work, काष्ठा qeth_card,
					      rx_mode_work);
	काष्ठा net_device *dev = card->dev;
	काष्ठा netdev_hw_addr *ha;
	काष्ठा qeth_mac *mac;
	काष्ठा hlist_node *पंचांगp;
	पूर्णांक i;
	पूर्णांक rc;

	QETH_CARD_TEXT(card, 3, "setmulti");

	netअगर_addr_lock_bh(dev);
	netdev_क्रम_each_mc_addr(ha, dev)
		qeth_l2_add_mac(card, ha);
	netdev_क्रम_each_uc_addr(ha, dev)
		qeth_l2_add_mac(card, ha);
	netअगर_addr_unlock_bh(dev);

	hash_क्रम_each_safe(card->rx_mode_addrs, i, पंचांगp, mac, hnode) अणु
		चयन (mac->disp_flag) अणु
		हाल QETH_DISP_ADDR_DELETE:
			qeth_l2_हटाओ_mac(card, mac->mac_addr);
			hash_del(&mac->hnode);
			kमुक्त(mac);
			अवरोध;
		हाल QETH_DISP_ADDR_ADD:
			rc = qeth_l2_ग_लिखो_mac(card, mac->mac_addr);
			अगर (rc) अणु
				hash_del(&mac->hnode);
				kमुक्त(mac);
				अवरोध;
			पूर्ण
			fallthrough;
		शेष:
			/* क्रम next call to set_rx_mode(): */
			mac->disp_flag = QETH_DISP_ADDR_DELETE;
		पूर्ण
	पूर्ण

	qeth_l2_set_promisc_mode(card);
पूर्ण

अटल पूर्णांक qeth_l2_xmit_osn(काष्ठा qeth_card *card, काष्ठा sk_buff *skb,
			    काष्ठा qeth_qdio_out_q *queue)
अणु
	gfp_t gfp = GFP_ATOMIC | (skb_pfmeदो_स्मृति(skb) ? __GFP_MEMALLOC : 0);
	काष्ठा qeth_hdr *hdr = (काष्ठा qeth_hdr *)skb->data;
	addr_t end = (addr_t)(skb->data + माप(*hdr));
	addr_t start = (addr_t)skb->data;
	अचिन्हित पूर्णांक elements = 0;
	अचिन्हित पूर्णांक hd_len = 0;
	पूर्णांक rc;

	अगर (skb->protocol == htons(ETH_P_IPV6))
		वापस -EPROTONOSUPPORT;

	अगर (qeth_get_elements_क्रम_range(start, end) > 1) अणु
		/* Misaligned HW header, move it to its own buffer element. */
		hdr = kmem_cache_alloc(qeth_core_header_cache, gfp);
		अगर (!hdr)
			वापस -ENOMEM;
		hd_len = माप(*hdr);
		skb_copy_from_linear_data(skb, (अक्षर *)hdr, hd_len);
		elements++;
	पूर्ण

	elements += qeth_count_elements(skb, hd_len);
	अगर (elements > queue->max_elements) अणु
		rc = -E2BIG;
		जाओ out;
	पूर्ण

	rc = qeth_करो_send_packet(card, queue, skb, hdr, hd_len, hd_len,
				 elements);
out:
	अगर (rc && hd_len)
		kmem_cache_मुक्त(qeth_core_header_cache, hdr);
	वापस rc;
पूर्ण

अटल netdev_tx_t qeth_l2_hard_start_xmit(काष्ठा sk_buff *skb,
					   काष्ठा net_device *dev)
अणु
	काष्ठा qeth_card *card = dev->ml_priv;
	u16 txq = skb_get_queue_mapping(skb);
	काष्ठा qeth_qdio_out_q *queue;
	पूर्णांक rc;

	अगर (!skb_is_gso(skb))
		qdisc_skb_cb(skb)->pkt_len = skb->len;
	अगर (IS_IQD(card))
		txq = qeth_iqd_translate_txq(dev, txq);
	queue = card->qdio.out_qs[txq];

	अगर (IS_OSN(card))
		rc = qeth_l2_xmit_osn(card, skb, queue);
	अन्यथा
		rc = qeth_xmit(card, skb, queue, vlan_get_protocol(skb),
			       qeth_l2_fill_header);

	अगर (!rc)
		वापस NETDEV_TX_OK;

	QETH_TXQ_STAT_INC(queue, tx_dropped);
	kमुक्त_skb(skb);
	वापस NETDEV_TX_OK;
पूर्ण

अटल u16 qeth_l2_select_queue(काष्ठा net_device *dev, काष्ठा sk_buff *skb,
				काष्ठा net_device *sb_dev)
अणु
	काष्ठा qeth_card *card = dev->ml_priv;

	अगर (IS_IQD(card))
		वापस qeth_iqd_select_queue(dev, skb,
					     qeth_get_ether_cast_type(skb),
					     sb_dev);
	अगर (qeth_uses_tx_prio_queueing(card))
		वापस qeth_get_priority_queue(card, skb);

	वापस netdev_pick_tx(dev, skb, sb_dev);
पूर्ण

अटल व्योम qeth_l2_set_rx_mode(काष्ठा net_device *dev)
अणु
	काष्ठा qeth_card *card = dev->ml_priv;

	schedule_work(&card->rx_mode_work);
पूर्ण

/**
 *	qeth_l2_pnso() - perक्रमm network subchannel operation
 *	@card: qeth_card काष्ठाure poपूर्णांकer
 *	@oc: Operation Code
 *	@cnc: Boolean Change-Notअगरication Control
 *	@cb: Callback function will be executed क्रम each element
 *		of the address list
 *	@priv: Poपूर्णांकer to pass to the callback function.
 *
 *	Collects network inक्रमmation in a network address list and calls the
 *	callback function क्रम every entry in the list. If "change-notअगरication-
 *	control" is set, further changes in the address list will be reported
 *	via the IPA command.
 */
अटल पूर्णांक qeth_l2_pnso(काष्ठा qeth_card *card, u8 oc, पूर्णांक cnc,
			व्योम (*cb)(व्योम *priv, काष्ठा chsc_pnso_naid_l2 *entry),
			व्योम *priv)
अणु
	काष्ठा ccw_device *ddev = CARD_DDEV(card);
	काष्ठा chsc_pnso_area *rr;
	u32 prev_instance = 0;
	पूर्णांक isfirstblock = 1;
	पूर्णांक i, size, elems;
	पूर्णांक rc;

	rr = (काष्ठा chsc_pnso_area *)get_zeroed_page(GFP_KERNEL);
	अगर (rr == शून्य)
		वापस -ENOMEM;
	करो अणु
		QETH_CARD_TEXT(card, 2, "PNSO");
		/* on the first iteration, naihdr.resume_token will be zero */
		rc = ccw_device_pnso(ddev, rr, oc, rr->naihdr.resume_token,
				     cnc);
		अगर (rc)
			जारी;
		अगर (cb == शून्य)
			जारी;

		size = rr->naihdr.naids;
		अगर (size != माप(काष्ठा chsc_pnso_naid_l2)) अणु
			WARN_ON_ONCE(1);
			जारी;
		पूर्ण

		elems = (rr->response.length - माप(काष्ठा chsc_header) -
			 माप(काष्ठा chsc_pnso_naihdr)) / size;

		अगर (!isfirstblock && (rr->naihdr.instance != prev_instance)) अणु
			/* Inक्रमm the caller that they need to scrap */
			/* the data that was alपढ़ोy reported via cb */
			rc = -EAGAIN;
			अवरोध;
		पूर्ण
		isfirstblock = 0;
		prev_instance = rr->naihdr.instance;
		क्रम (i = 0; i < elems; i++)
			(*cb)(priv, &rr->entries[i]);
	पूर्ण जबतक ((rc == -EBUSY) || (!rc && /* list stored */
		   /* resume token is non-zero => list incomplete */
		   (rr->naihdr.resume_token.t1 || rr->naihdr.resume_token.t2)));

	अगर (rc)
		QETH_CARD_TEXT_(card, 2, "PNrp%04x", rr->response.code);

	मुक्त_page((अचिन्हित दीर्घ)rr);
	वापस rc;
पूर्ण

अटल bool qeth_is_my_net_अगर_token(काष्ठा qeth_card *card,
				    काष्ठा net_अगर_token *token)
अणु
	वापस ((card->info.ddev_devno == token->devnum) &&
		(card->info.cssid == token->cssid) &&
		(card->info.iid == token->iid) &&
		(card->info.ssid == token->ssid) &&
		(card->info.chpid == token->chpid) &&
		(card->info.chid == token->chid));
पूर्ण

/**
 *	qeth_l2_dev2br_fdb_notअगरy() - update fdb of master bridge
 *	@card:	qeth_card काष्ठाure poपूर्णांकer
 *	@code:	event biपंचांगask: high order bit 0x80 set to
 *				1 - removal of an object
 *				0 - addition of an object
 *			       Object type(s):
 *				0x01 - VLAN, 0x02 - MAC, 0x03 - VLAN and MAC
 *	@token: "network token" काष्ठाure identअगरying 'physical' location
 *		of the target
 *	@addr_lnid: काष्ठाure with MAC address and VLAN ID of the target
 */
अटल व्योम qeth_l2_dev2br_fdb_notअगरy(काष्ठा qeth_card *card, u8 code,
				      काष्ठा net_अगर_token *token,
				      काष्ठा mac_addr_lnid *addr_lnid)
अणु
	काष्ठा चयनdev_notअगरier_fdb_info info;
	u8 ntfy_mac[ETH_ALEN];

	ether_addr_copy(ntfy_mac, addr_lnid->mac);
	/* Ignore VLAN only changes */
	अगर (!(code & IPA_ADDR_CHANGE_CODE_MACADDR))
		वापस;
	/* Ignore mcast entries */
	अगर (is_multicast_ether_addr(ntfy_mac))
		वापस;
	/* Ignore my own addresses */
	अगर (qeth_is_my_net_अगर_token(card, token))
		वापस;

	info.addr = ntfy_mac;
	/* करोn't report VLAN IDs */
	info.vid = 0;
	info.added_by_user = false;
	info.offloaded = true;

	अगर (code & IPA_ADDR_CHANGE_CODE_REMOVAL) अणु
		call_चयनdev_notअगरiers(SWITCHDEV_FDB_DEL_TO_BRIDGE,
					 card->dev, &info.info, शून्य);
		QETH_CARD_TEXT(card, 4, "andelmac");
		QETH_CARD_TEXT_(card, 4,
				"mc%012lx", ether_addr_to_u64(ntfy_mac));
	पूर्ण अन्यथा अणु
		call_चयनdev_notअगरiers(SWITCHDEV_FDB_ADD_TO_BRIDGE,
					 card->dev, &info.info, शून्य);
		QETH_CARD_TEXT(card, 4, "anaddmac");
		QETH_CARD_TEXT_(card, 4,
				"mc%012lx", ether_addr_to_u64(ntfy_mac));
	पूर्ण
पूर्ण

अटल व्योम qeth_l2_dev2br_an_set_cb(व्योम *priv,
				     काष्ठा chsc_pnso_naid_l2 *entry)
अणु
	u8 code = IPA_ADDR_CHANGE_CODE_MACADDR;
	काष्ठा qeth_card *card = priv;

	अगर (entry->addr_lnid.lnid < VLAN_N_VID)
		code |= IPA_ADDR_CHANGE_CODE_VLANID;
	qeth_l2_dev2br_fdb_notअगरy(card, code,
				  (काष्ठा net_अगर_token *)&entry->nit,
				  (काष्ठा mac_addr_lnid *)&entry->addr_lnid);
पूर्ण

/**
 *	qeth_l2_dev2br_an_set() -
 *	Enable or disable 'dev to bridge network address notification'
 *	@card: qeth_card काष्ठाure poपूर्णांकer
 *	@enable: Enable or disable 'dev to bridge network address notification'
 *
 *	Returns negative त्रुटि_सं-compatible error indication or 0 on success.
 *
 *	On enable, emits a series of address notअगरications क्रम all
 *	currently रेजिस्टरed hosts.
 */
अटल पूर्णांक qeth_l2_dev2br_an_set(काष्ठा qeth_card *card, bool enable)
अणु
	पूर्णांक rc;

	अगर (enable) अणु
		QETH_CARD_TEXT(card, 2, "anseton");
		rc = qeth_l2_pnso(card, PNSO_OC_NET_ADDR_INFO, 1,
				  qeth_l2_dev2br_an_set_cb, card);
		अगर (rc == -EAGAIN)
			/* address notअगरication enabled, but inconsistent
			 * addresses reported -> disable address notअगरication
			 */
			qeth_l2_pnso(card, PNSO_OC_NET_ADDR_INFO, 0,
				     शून्य, शून्य);
	पूर्ण अन्यथा अणु
		QETH_CARD_TEXT(card, 2, "ansetoff");
		rc = qeth_l2_pnso(card, PNSO_OC_NET_ADDR_INFO, 0, शून्य, शून्य);
	पूर्ण

	वापस rc;
पूर्ण

अटल पूर्णांक qeth_l2_bridge_getlink(काष्ठा sk_buff *skb, u32 pid, u32 seq,
				  काष्ठा net_device *dev, u32 filter_mask,
				  पूर्णांक nlflags)
अणु
	काष्ठा qeth_priv *priv = netdev_priv(dev);
	काष्ठा qeth_card *card = dev->ml_priv;
	u16 mode = BRIDGE_MODE_UNDEF;

	/* Do not even show qeth devs that cannot करो bridge_setlink */
	अगर (!priv->brport_hw_features || !netअगर_device_present(dev) ||
	    qeth_bridgeport_is_in_use(card))
		वापस -EOPNOTSUPP;

	वापस nकरो_dflt_bridge_getlink(skb, pid, seq, dev,
				       mode, priv->brport_features,
				       priv->brport_hw_features,
				       nlflags, filter_mask, शून्य);
पूर्ण

अटल स्थिर काष्ठा nla_policy qeth_brport_policy[IFLA_BRPORT_MAX + 1] = अणु
	[IFLA_BRPORT_LEARNING_SYNC]	= अणु .type = NLA_U8 पूर्ण,
पूर्ण;

/**
 *	qeth_l2_bridge_setlink() - set bridgeport attributes
 *	@dev: netdevice
 *	@nlh: netlink message header
 *	@flags: bridge flags (here: BRIDGE_FLAGS_SELF)
 *	@extack: extended ACK report काष्ठा
 *
 *	Called under rtnl_lock
 */
अटल पूर्णांक qeth_l2_bridge_setlink(काष्ठा net_device *dev, काष्ठा nlmsghdr *nlh,
				  u16 flags, काष्ठा netlink_ext_ack *extack)
अणु
	काष्ठा qeth_priv *priv = netdev_priv(dev);
	काष्ठा nlattr *bp_tb[IFLA_BRPORT_MAX + 1];
	काष्ठा qeth_card *card = dev->ml_priv;
	काष्ठा nlattr *attr, *nested_attr;
	bool enable, has_protinfo = false;
	पूर्णांक rem1, rem2;
	पूर्णांक rc;

	अगर (!netअगर_device_present(dev))
		वापस -ENODEV;
	अगर (!(priv->brport_hw_features))
		वापस -EOPNOTSUPP;

	nlmsg_क्रम_each_attr(attr, nlh, माप(काष्ठा अगरinfomsg), rem1) अणु
		अगर (nla_type(attr) == IFLA_PROTINFO) अणु
			rc = nla_parse_nested(bp_tb, IFLA_BRPORT_MAX, attr,
					      qeth_brport_policy, extack);
			अगर (rc)
				वापस rc;
			has_protinfo = true;
		पूर्ण अन्यथा अगर (nla_type(attr) == IFLA_AF_SPEC) अणु
			nla_क्रम_each_nested(nested_attr, attr, rem2) अणु
				अगर (nla_type(nested_attr) == IFLA_BRIDGE_FLAGS)
					जारी;
				NL_SET_ERR_MSG_ATTR(extack, nested_attr,
						    "Unsupported attribute");
				वापस -EINVAL;
			पूर्ण
		पूर्ण अन्यथा अणु
			NL_SET_ERR_MSG_ATTR(extack, attr, "Unsupported attribute");
			वापस -EINVAL;
		पूर्ण
	पूर्ण
	अगर (!has_protinfo)
		वापस 0;
	अगर (!bp_tb[IFLA_BRPORT_LEARNING_SYNC])
		वापस -EINVAL;
	enable = !!nla_get_u8(bp_tb[IFLA_BRPORT_LEARNING_SYNC]);

	अगर (enable == !!(priv->brport_features & BR_LEARNING_SYNC))
		वापस 0;

	mutex_lock(&card->sbp_lock);
	/* करो not change anything अगर BridgePort is enabled */
	अगर (qeth_bridgeport_is_in_use(card)) अणु
		NL_SET_ERR_MSG(extack, "n/a (BridgePort)");
		rc = -EBUSY;
	पूर्ण अन्यथा अगर (enable) अणु
		qeth_l2_set_pnso_mode(card, QETH_PNSO_ADDR_INFO);
		rc = qeth_l2_dev2br_an_set(card, true);
		अगर (rc)
			qeth_l2_set_pnso_mode(card, QETH_PNSO_NONE);
		अन्यथा
			priv->brport_features |= BR_LEARNING_SYNC;
	पूर्ण अन्यथा अणु
		rc = qeth_l2_dev2br_an_set(card, false);
		अगर (!rc) अणु
			qeth_l2_set_pnso_mode(card, QETH_PNSO_NONE);
			priv->brport_features ^= BR_LEARNING_SYNC;
			qeth_l2_dev2br_fdb_flush(card);
		पूर्ण
	पूर्ण
	mutex_unlock(&card->sbp_lock);

	वापस rc;
पूर्ण

अटल स्थिर काष्ठा net_device_ops qeth_l2_netdev_ops = अणु
	.nकरो_खोलो		= qeth_खोलो,
	.nकरो_stop		= qeth_stop,
	.nकरो_get_stats64	= qeth_get_stats64,
	.nकरो_start_xmit		= qeth_l2_hard_start_xmit,
	.nकरो_features_check	= qeth_features_check,
	.nकरो_select_queue	= qeth_l2_select_queue,
	.nकरो_validate_addr	= qeth_l2_validate_addr,
	.nकरो_set_rx_mode	= qeth_l2_set_rx_mode,
	.nकरो_करो_ioctl		= qeth_करो_ioctl,
	.nकरो_set_mac_address    = qeth_l2_set_mac_address,
	.nकरो_vlan_rx_add_vid	= qeth_l2_vlan_rx_add_vid,
	.nकरो_vlan_rx_समाप्त_vid   = qeth_l2_vlan_rx_समाप्त_vid,
	.nकरो_tx_समयout		= qeth_tx_समयout,
	.nकरो_fix_features	= qeth_fix_features,
	.nकरो_set_features	= qeth_set_features,
	.nकरो_bridge_getlink	= qeth_l2_bridge_getlink,
	.nकरो_bridge_setlink	= qeth_l2_bridge_setlink,
पूर्ण;

अटल स्थिर काष्ठा net_device_ops qeth_osn_netdev_ops = अणु
	.nकरो_खोलो		= qeth_खोलो,
	.nकरो_stop		= qeth_stop,
	.nकरो_get_stats64	= qeth_get_stats64,
	.nकरो_start_xmit		= qeth_l2_hard_start_xmit,
	.nकरो_validate_addr	= eth_validate_addr,
	.nकरो_tx_समयout		= qeth_tx_समयout,
पूर्ण;

अटल पूर्णांक qeth_l2_setup_netdev(काष्ठा qeth_card *card)
अणु
	अगर (IS_OSN(card)) अणु
		card->dev->netdev_ops = &qeth_osn_netdev_ops;
		card->dev->flags |= IFF_NOARP;
		जाओ add_napi;
	पूर्ण

	card->dev->needed_headroom = माप(काष्ठा qeth_hdr);
	card->dev->netdev_ops = &qeth_l2_netdev_ops;
	card->dev->priv_flags |= IFF_UNICAST_FLT;

	अगर (IS_OSM(card)) अणु
		card->dev->features |= NETIF_F_VLAN_CHALLENGED;
	पूर्ण अन्यथा अणु
		अगर (!IS_VM_NIC(card))
			card->dev->hw_features |= NETIF_F_HW_VLAN_CTAG_FILTER;
		card->dev->features |= NETIF_F_HW_VLAN_CTAG_FILTER;
	पूर्ण

	अगर (IS_OSD(card) && !IS_VM_NIC(card)) अणु
		card->dev->features |= NETIF_F_SG;
		/* OSA 3S and earlier has no RX/TX support */
		अगर (qeth_is_supported(card, IPA_OUTBOUND_CHECKSUM)) अणु
			card->dev->hw_features |= NETIF_F_IP_CSUM;
			card->dev->vlan_features |= NETIF_F_IP_CSUM;
		पूर्ण
	पूर्ण
	अगर (qeth_is_supported6(card, IPA_OUTBOUND_CHECKSUM_V6)) अणु
		card->dev->hw_features |= NETIF_F_IPV6_CSUM;
		card->dev->vlan_features |= NETIF_F_IPV6_CSUM;
	पूर्ण
	अगर (qeth_is_supported(card, IPA_INBOUND_CHECKSUM) ||
	    qeth_is_supported6(card, IPA_INBOUND_CHECKSUM_V6)) अणु
		card->dev->hw_features |= NETIF_F_RXCSUM;
		card->dev->vlan_features |= NETIF_F_RXCSUM;
	पूर्ण
	अगर (qeth_is_supported(card, IPA_OUTBOUND_TSO)) अणु
		card->dev->hw_features |= NETIF_F_TSO;
		card->dev->vlan_features |= NETIF_F_TSO;
	पूर्ण
	अगर (qeth_is_supported6(card, IPA_OUTBOUND_TSO)) अणु
		card->dev->hw_features |= NETIF_F_TSO6;
		card->dev->vlan_features |= NETIF_F_TSO6;
	पूर्ण

	अगर (card->dev->hw_features & (NETIF_F_TSO | NETIF_F_TSO6)) अणु
		card->dev->needed_headroom = माप(काष्ठा qeth_hdr_tso);
		netअगर_keep_dst(card->dev);
		netअगर_set_gso_max_size(card->dev,
				       PAGE_SIZE * (QDIO_MAX_ELEMENTS_PER_BUFFER - 1));
	पूर्ण

add_napi:
	netअगर_napi_add(card->dev, &card->napi, qeth_poll, QETH_NAPI_WEIGHT);
	वापस रेजिस्टर_netdev(card->dev);
पूर्ण

अटल व्योम qeth_l2_trace_features(काष्ठा qeth_card *card)
अणु
	/* Set BridgePort features */
	QETH_CARD_TEXT(card, 2, "featuSBP");
	QETH_CARD_HEX(card, 2, &card->options.sbp.supported_funcs,
		      माप(card->options.sbp.supported_funcs));
	/* VNIC Characteristics features */
	QETH_CARD_TEXT(card, 2, "feaVNICC");
	QETH_CARD_HEX(card, 2, &card->options.vnicc.sup_अक्षरs,
		      माप(card->options.vnicc.sup_अक्षरs));
पूर्ण

अटल व्योम qeth_l2_setup_bridgeport_attrs(काष्ठा qeth_card *card)
अणु
	अगर (!card->options.sbp.reflect_promisc &&
	    card->options.sbp.role != QETH_SBP_ROLE_NONE) अणु
		/* Conditional to aव्योम spurious error messages */
		qeth_bridgeport_setrole(card, card->options.sbp.role);
		/* Let the callback function refresh the stored role value. */
		qeth_bridgeport_query_ports(card, &card->options.sbp.role,
					    शून्य);
	पूर्ण
	अगर (card->options.sbp.hostnotअगरication) अणु
		अगर (qeth_bridgeport_an_set(card, 1))
			card->options.sbp.hostnotअगरication = 0;
	पूर्ण
पूर्ण

/**
 *	qeth_l2_detect_dev2br_support() -
 *	Detect whether this card supports 'dev to bridge fdb network address
 *	change notअगरication' and thus can support the learning_sync bridgeport
 *	attribute
 *	@card: qeth_card काष्ठाure poपूर्णांकer
 */
अटल व्योम qeth_l2_detect_dev2br_support(काष्ठा qeth_card *card)
अणु
	काष्ठा qeth_priv *priv = netdev_priv(card->dev);
	bool dev2br_supported;

	QETH_CARD_TEXT(card, 2, "d2brsup");
	अगर (!IS_IQD(card))
		वापस;

	/* dev2br requires valid cssid,iid,chid */
	dev2br_supported = card->info.ids_valid &&
			   css_general_अक्षरacteristics.enarf;
	QETH_CARD_TEXT_(card, 2, "D2Bsup%02x", dev2br_supported);

	अगर (dev2br_supported)
		priv->brport_hw_features |= BR_LEARNING_SYNC;
	अन्यथा
		priv->brport_hw_features &= ~BR_LEARNING_SYNC;
पूर्ण

अटल व्योम qeth_l2_enable_brport_features(काष्ठा qeth_card *card)
अणु
	काष्ठा qeth_priv *priv = netdev_priv(card->dev);
	पूर्णांक rc;

	अगर (priv->brport_features & BR_LEARNING_SYNC) अणु
		अगर (priv->brport_hw_features & BR_LEARNING_SYNC) अणु
			qeth_l2_set_pnso_mode(card, QETH_PNSO_ADDR_INFO);
			rc = qeth_l2_dev2br_an_set(card, true);
			अगर (rc == -EAGAIN) अणु
				/* Recoverable error, retry once */
				qeth_l2_set_pnso_mode(card, QETH_PNSO_NONE);
				qeth_l2_dev2br_fdb_flush(card);
				qeth_l2_set_pnso_mode(card, QETH_PNSO_ADDR_INFO);
				rc = qeth_l2_dev2br_an_set(card, true);
			पूर्ण
			अगर (rc) अणु
				netdev_err(card->dev,
					   "failed to enable bridge learning_sync: %d\n",
					   rc);
				qeth_l2_set_pnso_mode(card, QETH_PNSO_NONE);
				qeth_l2_dev2br_fdb_flush(card);
				priv->brport_features ^= BR_LEARNING_SYNC;
			पूर्ण
		पूर्ण अन्यथा अणु
			dev_warn(&card->gdev->dev,
				"bridge learning_sync not supported\n");
			priv->brport_features ^= BR_LEARNING_SYNC;
		पूर्ण
	पूर्ण
पूर्ण

#अगर_घोषित CONFIG_QETH_OSN
अटल व्योम qeth_osn_assist_cb(काष्ठा qeth_card *card,
			       काष्ठा qeth_cmd_buffer *iob,
			       अचिन्हित पूर्णांक data_length)
अणु
	qeth_notअगरy_cmd(iob, 0);
	qeth_put_cmd(iob);
पूर्ण

पूर्णांक qeth_osn_assist(काष्ठा net_device *dev, व्योम *data, पूर्णांक data_len)
अणु
	काष्ठा qeth_cmd_buffer *iob;
	काष्ठा qeth_card *card;

	अगर (data_len < 0)
		वापस -EINVAL;
	अगर (!dev)
		वापस -ENODEV;
	card = dev->ml_priv;
	अगर (!card)
		वापस -ENODEV;
	QETH_CARD_TEXT(card, 2, "osnsdmc");
	अगर (!qeth_card_hw_is_reachable(card))
		वापस -ENODEV;

	iob = qeth_alloc_cmd(&card->ग_लिखो, IPA_PDU_HEADER_SIZE + data_len, 1,
			     QETH_IPA_TIMEOUT);
	अगर (!iob)
		वापस -ENOMEM;

	qeth_prepare_ipa_cmd(card, iob, (u16) data_len, शून्य);

	स_नकल(__ipa_cmd(iob), data, data_len);
	iob->callback = qeth_osn_assist_cb;
	वापस qeth_send_ipa_cmd(card, iob, शून्य, शून्य);
पूर्ण
EXPORT_SYMBOL(qeth_osn_assist);

पूर्णांक qeth_osn_रेजिस्टर(अचिन्हित अक्षर *पढ़ो_dev_no, काष्ठा net_device **dev,
		  पूर्णांक (*assist_cb)(काष्ठा net_device *, व्योम *),
		  पूर्णांक (*data_cb)(काष्ठा sk_buff *))
अणु
	काष्ठा qeth_card *card;
	अक्षर bus_id[16];
	u16 devno;

	स_नकल(&devno, पढ़ो_dev_no, 2);
	प्र_लिखो(bus_id, "0.0.%04x", devno);
	card = qeth_get_card_by_busid(bus_id);
	अगर (!card || !IS_OSN(card))
		वापस -ENODEV;
	*dev = card->dev;

	QETH_CARD_TEXT(card, 2, "osnreg");
	अगर ((assist_cb == शून्य) || (data_cb == शून्य))
		वापस -EINVAL;
	card->osn_info.assist_cb = assist_cb;
	card->osn_info.data_cb = data_cb;
	वापस 0;
पूर्ण
EXPORT_SYMBOL(qeth_osn_रेजिस्टर);

व्योम qeth_osn_deरेजिस्टर(काष्ठा net_device *dev)
अणु
	काष्ठा qeth_card *card;

	अगर (!dev)
		वापस;
	card = dev->ml_priv;
	अगर (!card)
		वापस;
	QETH_CARD_TEXT(card, 2, "osndereg");
	card->osn_info.assist_cb = शून्य;
	card->osn_info.data_cb = शून्य;
पूर्ण
EXPORT_SYMBOL(qeth_osn_deरेजिस्टर);
#पूर्ण_अगर

/* SETBRIDGEPORT support, async notअगरications */

क्रमागत qeth_an_event_type अणुanev_reg_unreg, anev_पात, anev_resetपूर्ण;

/**
 * qeth_bridge_emit_host_event() - bridgeport address change notअगरication
 * @card:  qeth_card काष्ठाure poपूर्णांकer, क्रम udev events.
 * @evtype:  "normal" रेजिस्टर/unरेजिस्टर, or पात, or reset. For पात
 *	      and reset token and addr_lnid are unused and may be शून्य.
 * @code:  event biपंचांगask: high order bit 0x80 value 1 means removal of an
 *			  object, 0 - addition of an object.
 *			  0x01 - VLAN, 0x02 - MAC, 0x03 - VLAN and MAC.
 * @token: "network token" काष्ठाure identअगरying physical address of the port.
 * @addr_lnid: poपूर्णांकer to काष्ठाure with MAC address and VLAN ID.
 *
 * This function is called when registrations and deregistrations are
 * reported by the hardware, and also when notअगरications are enabled -
 * क्रम all currently रेजिस्टरed addresses.
 */
अटल व्योम qeth_bridge_emit_host_event(काष्ठा qeth_card *card,
					क्रमागत qeth_an_event_type evtype,
					u8 code,
					काष्ठा net_अगर_token *token,
					काष्ठा mac_addr_lnid *addr_lnid)
अणु
	अक्षर str[7][32];
	अक्षर *env[8];
	पूर्णांक i = 0;

	चयन (evtype) अणु
	हाल anev_reg_unreg:
		snम_लिखो(str[i], माप(str[i]), "BRIDGEDHOST=%s",
				(code & IPA_ADDR_CHANGE_CODE_REMOVAL)
				? "deregister" : "register");
		env[i] = str[i]; i++;
		अगर (code & IPA_ADDR_CHANGE_CODE_VLANID) अणु
			snम_लिखो(str[i], माप(str[i]), "VLAN=%d",
				addr_lnid->lnid);
			env[i] = str[i]; i++;
		पूर्ण
		अगर (code & IPA_ADDR_CHANGE_CODE_MACADDR) अणु
			snम_लिखो(str[i], माप(str[i]), "MAC=%pM",
				addr_lnid->mac);
			env[i] = str[i]; i++;
		पूर्ण
		snम_लिखो(str[i], माप(str[i]), "NTOK_BUSID=%x.%x.%04x",
			token->cssid, token->ssid, token->devnum);
		env[i] = str[i]; i++;
		snम_लिखो(str[i], माप(str[i]), "NTOK_IID=%02x", token->iid);
		env[i] = str[i]; i++;
		snम_लिखो(str[i], माप(str[i]), "NTOK_CHPID=%02x",
				token->chpid);
		env[i] = str[i]; i++;
		snम_लिखो(str[i], माप(str[i]), "NTOK_CHID=%04x", token->chid);
		env[i] = str[i]; i++;
		अवरोध;
	हाल anev_पात:
		snम_लिखो(str[i], माप(str[i]), "BRIDGEDHOST=abort");
		env[i] = str[i]; i++;
		अवरोध;
	हाल anev_reset:
		snम_लिखो(str[i], माप(str[i]), "BRIDGEDHOST=reset");
		env[i] = str[i]; i++;
		अवरोध;
	पूर्ण
	env[i] = शून्य;
	kobject_uevent_env(&card->gdev->dev.kobj, KOBJ_CHANGE, env);
पूर्ण

काष्ठा qeth_bridge_state_data अणु
	काष्ठा work_काष्ठा worker;
	काष्ठा qeth_card *card;
	u8 role;
	u8 state;
पूर्ण;

अटल व्योम qeth_bridge_state_change_worker(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा qeth_bridge_state_data *data =
		container_of(work, काष्ठा qeth_bridge_state_data, worker);
	अक्षर env_locrem[32];
	अक्षर env_role[32];
	अक्षर env_state[32];
	अक्षर *env[] = अणु
		env_locrem,
		env_role,
		env_state,
		शून्य
	पूर्ण;

	snम_लिखो(env_locrem, माप(env_locrem), "BRIDGEPORT=statechange");
	snम_लिखो(env_role, माप(env_role), "ROLE=%s",
		(data->role == QETH_SBP_ROLE_NONE) ? "none" :
		(data->role == QETH_SBP_ROLE_PRIMARY) ? "primary" :
		(data->role == QETH_SBP_ROLE_SECONDARY) ? "secondary" :
		"<INVALID>");
	snम_लिखो(env_state, माप(env_state), "STATE=%s",
		(data->state == QETH_SBP_STATE_INACTIVE) ? "inactive" :
		(data->state == QETH_SBP_STATE_STANDBY) ? "standby" :
		(data->state == QETH_SBP_STATE_ACTIVE) ? "active" :
		"<INVALID>");
	kobject_uevent_env(&data->card->gdev->dev.kobj,
				KOBJ_CHANGE, env);
	kमुक्त(data);
पूर्ण

अटल व्योम qeth_bridge_state_change(काष्ठा qeth_card *card,
					काष्ठा qeth_ipa_cmd *cmd)
अणु
	काष्ठा qeth_sbp_port_data *qports = &cmd->data.sbp.data.port_data;
	काष्ठा qeth_bridge_state_data *data;

	QETH_CARD_TEXT(card, 2, "brstchng");
	अगर (qports->num_entries == 0) अणु
		QETH_CARD_TEXT(card, 2, "BPempty");
		वापस;
	पूर्ण
	अगर (qports->entry_length != माप(काष्ठा qeth_sbp_port_entry)) अणु
		QETH_CARD_TEXT_(card, 2, "BPsz%04x", qports->entry_length);
		वापस;
	पूर्ण

	data = kzalloc(माप(*data), GFP_ATOMIC);
	अगर (!data) अणु
		QETH_CARD_TEXT(card, 2, "BPSalloc");
		वापस;
	पूर्ण
	INIT_WORK(&data->worker, qeth_bridge_state_change_worker);
	data->card = card;
	/* Inक्रमmation क्रम the local port: */
	data->role = qports->entry[0].role;
	data->state = qports->entry[0].state;

	queue_work(card->event_wq, &data->worker);
पूर्ण

काष्ठा qeth_addr_change_data अणु
	काष्ठा delayed_work dwork;
	काष्ठा qeth_card *card;
	काष्ठा qeth_ipacmd_addr_change ac_event;
पूर्ण;

अटल व्योम qeth_l2_dev2br_worker(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा delayed_work *dwork = to_delayed_work(work);
	काष्ठा qeth_addr_change_data *data;
	काष्ठा qeth_card *card;
	काष्ठा qeth_priv *priv;
	अचिन्हित पूर्णांक i;
	पूर्णांक rc;

	data = container_of(dwork, काष्ठा qeth_addr_change_data, dwork);
	card = data->card;
	priv = netdev_priv(card->dev);

	QETH_CARD_TEXT(card, 4, "dev2brew");

	अगर (READ_ONCE(card->info.pnso_mode) == QETH_PNSO_NONE)
		जाओ मुक्त;

	अगर (data->ac_event.lost_event_mask) अणु
		/* Potential re-config in progress, try again later: */
		अगर (!rtnl_trylock()) अणु
			queue_delayed_work(card->event_wq, dwork,
					   msecs_to_jअगरfies(100));
			वापस;
		पूर्ण

		अगर (!netअगर_device_present(card->dev)) अणु
			rtnl_unlock();
			जाओ मुक्त;
		पूर्ण

		QETH_DBF_MESSAGE(3,
				 "Address change notification overflow on device %x\n",
				 CARD_DEVID(card));
		/* Card fdb and bridge fdb are out of sync, card has stopped
		 * notअगरications (no need to drain_workqueue). Purge all
		 * 'extern_learn' entries from the parent bridge and restart
		 * the notअगरications.
		 */
		qeth_l2_dev2br_fdb_flush(card);
		rc = qeth_l2_dev2br_an_set(card, true);
		अगर (rc) अणु
			/* TODO: अगर we want to retry after -EAGAIN, be
			 * aware there could be stale entries in the
			 * workqueue now, that need to be drained.
			 * For now we give up:
			 */
			netdev_err(card->dev,
				   "bridge learning_sync failed to recover: %d\n",
				   rc);
			WRITE_ONCE(card->info.pnso_mode,
				   QETH_PNSO_NONE);
			/* To हटाओ fdb entries reported by an_set: */
			qeth_l2_dev2br_fdb_flush(card);
			priv->brport_features ^= BR_LEARNING_SYNC;
		पूर्ण अन्यथा अणु
			QETH_DBF_MESSAGE(3,
					 "Address Notification resynced on device %x\n",
					 CARD_DEVID(card));
		पूर्ण

		rtnl_unlock();
	पूर्ण अन्यथा अणु
		क्रम (i = 0; i < data->ac_event.num_entries; i++) अणु
			काष्ठा qeth_ipacmd_addr_change_entry *entry =
					&data->ac_event.entry[i];
			qeth_l2_dev2br_fdb_notअगरy(card,
						  entry->change_code,
						  &entry->token,
						  &entry->addr_lnid);
		पूर्ण
	पूर्ण

मुक्त:
	kमुक्त(data);
पूर्ण

अटल व्योम qeth_addr_change_event_worker(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा delayed_work *dwork = to_delayed_work(work);
	काष्ठा qeth_addr_change_data *data;
	काष्ठा qeth_card *card;
	पूर्णांक i;

	data = container_of(dwork, काष्ठा qeth_addr_change_data, dwork);
	card = data->card;

	QETH_CARD_TEXT(data->card, 4, "adrchgew");

	अगर (READ_ONCE(card->info.pnso_mode) == QETH_PNSO_NONE)
		जाओ मुक्त;

	अगर (data->ac_event.lost_event_mask) अणु
		/* Potential re-config in progress, try again later: */
		अगर (!mutex_trylock(&card->sbp_lock)) अणु
			queue_delayed_work(card->event_wq, dwork,
					   msecs_to_jअगरfies(100));
			वापस;
		पूर्ण

		dev_info(&data->card->gdev->dev,
			 "Address change notification stopped on %s (%s)\n",
			 netdev_name(card->dev),
			(data->ac_event.lost_event_mask == 0x01)
			? "Overflow"
			: (data->ac_event.lost_event_mask == 0x02)
			? "Bridge port state change"
			: "Unknown reason");

		data->card->options.sbp.hostnotअगरication = 0;
		card->info.pnso_mode = QETH_PNSO_NONE;
		mutex_unlock(&data->card->sbp_lock);
		qeth_bridge_emit_host_event(data->card, anev_पात,
					    0, शून्य, शून्य);
	पूर्ण अन्यथा
		क्रम (i = 0; i < data->ac_event.num_entries; i++) अणु
			काष्ठा qeth_ipacmd_addr_change_entry *entry =
					&data->ac_event.entry[i];
			qeth_bridge_emit_host_event(data->card,
						    anev_reg_unreg,
						    entry->change_code,
						    &entry->token,
						    &entry->addr_lnid);
		पूर्ण

मुक्त:
	kमुक्त(data);
पूर्ण

अटल व्योम qeth_addr_change_event(काष्ठा qeth_card *card,
				   काष्ठा qeth_ipa_cmd *cmd)
अणु
	काष्ठा qeth_ipacmd_addr_change *hostevs =
		 &cmd->data.addrchange;
	काष्ठा qeth_addr_change_data *data;
	पूर्णांक extrasize;

	अगर (card->info.pnso_mode == QETH_PNSO_NONE)
		वापस;

	QETH_CARD_TEXT(card, 4, "adrchgev");
	अगर (cmd->hdr.वापस_code != 0x0000) अणु
		अगर (cmd->hdr.वापस_code == 0x0010) अणु
			अगर (hostevs->lost_event_mask == 0x00)
				hostevs->lost_event_mask = 0xff;
		पूर्ण अन्यथा अणु
			QETH_CARD_TEXT_(card, 2, "ACHN%04x",
				cmd->hdr.वापस_code);
			वापस;
		पूर्ण
	पूर्ण
	extrasize = माप(काष्ठा qeth_ipacmd_addr_change_entry) *
						hostevs->num_entries;
	data = kzalloc(माप(काष्ठा qeth_addr_change_data) + extrasize,
		       GFP_ATOMIC);
	अगर (!data) अणु
		QETH_CARD_TEXT(card, 2, "ACNalloc");
		वापस;
	पूर्ण
	अगर (card->info.pnso_mode == QETH_PNSO_BRIDGEPORT)
		INIT_DELAYED_WORK(&data->dwork, qeth_addr_change_event_worker);
	अन्यथा
		INIT_DELAYED_WORK(&data->dwork, qeth_l2_dev2br_worker);
	data->card = card;
	स_नकल(&data->ac_event, hostevs,
			माप(काष्ठा qeth_ipacmd_addr_change) + extrasize);
	queue_delayed_work(card->event_wq, &data->dwork, 0);
पूर्ण

/* SETBRIDGEPORT support; sending commands */

काष्ठा _qeth_sbp_cbctl अणु
	जोड़ अणु
		u32 supported;
		काष्ठा अणु
			क्रमागत qeth_sbp_roles *role;
			क्रमागत qeth_sbp_states *state;
		पूर्ण qports;
	पूर्ण data;
पूर्ण;

अटल पूर्णांक qeth_bridgeport_makerc(काष्ठा qeth_card *card,
				  काष्ठा qeth_ipa_cmd *cmd)
अणु
	काष्ठा qeth_ipacmd_setbridgeport *sbp = &cmd->data.sbp;
	क्रमागत qeth_ipa_sbp_cmd setcmd = sbp->hdr.command_code;
	u16 ipa_rc = cmd->hdr.वापस_code;
	u16 sbp_rc = sbp->hdr.वापस_code;
	पूर्णांक rc;

	अगर (ipa_rc == IPA_RC_SUCCESS && sbp_rc == IPA_RC_SUCCESS)
		वापस 0;

	अगर ((IS_IQD(card) && ipa_rc == IPA_RC_SUCCESS) ||
	    (!IS_IQD(card) && ipa_rc == sbp_rc)) अणु
		चयन (sbp_rc) अणु
		हाल IPA_RC_SUCCESS:
			rc = 0;
			अवरोध;
		हाल IPA_RC_L2_UNSUPPORTED_CMD:
		हाल IPA_RC_UNSUPPORTED_COMMAND:
			rc = -EOPNOTSUPP;
			अवरोध;
		हाल IPA_RC_SBP_OSA_NOT_CONFIGURED:
		हाल IPA_RC_SBP_IQD_NOT_CONFIGURED:
			rc = -ENODEV; /* maybe not the best code here? */
			dev_err(&card->gdev->dev,
	"The device is not configured as a Bridge Port\n");
			अवरोध;
		हाल IPA_RC_SBP_OSA_OS_MISMATCH:
		हाल IPA_RC_SBP_IQD_OS_MISMATCH:
			rc = -EPERM;
			dev_err(&card->gdev->dev,
	"A Bridge Port is already configured by a different operating system\n");
			अवरोध;
		हाल IPA_RC_SBP_OSA_ANO_DEV_PRIMARY:
		हाल IPA_RC_SBP_IQD_ANO_DEV_PRIMARY:
			चयन (setcmd) अणु
			हाल IPA_SBP_SET_PRIMARY_BRIDGE_PORT:
				rc = -EEXIST;
				dev_err(&card->gdev->dev,
	"The LAN already has a primary Bridge Port\n");
				अवरोध;
			हाल IPA_SBP_SET_SECONDARY_BRIDGE_PORT:
				rc = -EBUSY;
				dev_err(&card->gdev->dev,
	"The device is already a primary Bridge Port\n");
				अवरोध;
			शेष:
				rc = -EIO;
			पूर्ण
			अवरोध;
		हाल IPA_RC_SBP_OSA_CURRENT_SECOND:
		हाल IPA_RC_SBP_IQD_CURRENT_SECOND:
			rc = -EBUSY;
			dev_err(&card->gdev->dev,
	"The device is already a secondary Bridge Port\n");
			अवरोध;
		हाल IPA_RC_SBP_OSA_LIMIT_SECOND:
		हाल IPA_RC_SBP_IQD_LIMIT_SECOND:
			rc = -EEXIST;
			dev_err(&card->gdev->dev,
	"The LAN cannot have more secondary Bridge Ports\n");
			अवरोध;
		हाल IPA_RC_SBP_OSA_CURRENT_PRIMARY:
		हाल IPA_RC_SBP_IQD_CURRENT_PRIMARY:
			rc = -EBUSY;
			dev_err(&card->gdev->dev,
	"The device is already a primary Bridge Port\n");
			अवरोध;
		हाल IPA_RC_SBP_OSA_NOT_AUTHD_BY_ZMAN:
		हाल IPA_RC_SBP_IQD_NOT_AUTHD_BY_ZMAN:
			rc = -EACCES;
			dev_err(&card->gdev->dev,
	"The device is not authorized to be a Bridge Port\n");
			अवरोध;
		शेष:
			rc = -EIO;
		पूर्ण
	पूर्ण अन्यथा अणु
		चयन (ipa_rc) अणु
		हाल IPA_RC_NOTSUPP:
			rc = -EOPNOTSUPP;
			अवरोध;
		हाल IPA_RC_UNSUPPORTED_COMMAND:
			rc = -EOPNOTSUPP;
			अवरोध;
		शेष:
			rc = -EIO;
		पूर्ण
	पूर्ण

	अगर (rc) अणु
		QETH_CARD_TEXT_(card, 2, "SBPi%04x", ipa_rc);
		QETH_CARD_TEXT_(card, 2, "SBPc%04x", sbp_rc);
	पूर्ण
	वापस rc;
पूर्ण

अटल काष्ठा qeth_cmd_buffer *qeth_sbp_build_cmd(काष्ठा qeth_card *card,
						  क्रमागत qeth_ipa_sbp_cmd sbp_cmd,
						  अचिन्हित पूर्णांक data_length)
अणु
	क्रमागत qeth_ipa_cmds ipa_cmd = IS_IQD(card) ? IPA_CMD_SETBRIDGEPORT_IQD :
						    IPA_CMD_SETBRIDGEPORT_OSA;
	काष्ठा qeth_ipacmd_sbp_hdr *hdr;
	काष्ठा qeth_cmd_buffer *iob;

	iob = qeth_ipa_alloc_cmd(card, ipa_cmd, QETH_PROT_NONE,
				 data_length +
				 दुरत्व(काष्ठा qeth_ipacmd_setbridgeport,
					  data));
	अगर (!iob)
		वापस iob;

	hdr = &__ipa_cmd(iob)->data.sbp.hdr;
	hdr->cmdlength = माप(*hdr) + data_length;
	hdr->command_code = sbp_cmd;
	hdr->used_total = 1;
	hdr->seq_no = 1;
	वापस iob;
पूर्ण

अटल पूर्णांक qeth_bridgeport_query_support_cb(काष्ठा qeth_card *card,
	काष्ठा qeth_reply *reply, अचिन्हित दीर्घ data)
अणु
	काष्ठा qeth_ipa_cmd *cmd = (काष्ठा qeth_ipa_cmd *) data;
	काष्ठा _qeth_sbp_cbctl *cbctl = (काष्ठा _qeth_sbp_cbctl *)reply->param;
	पूर्णांक rc;

	QETH_CARD_TEXT(card, 2, "brqsupcb");
	rc = qeth_bridgeport_makerc(card, cmd);
	अगर (rc)
		वापस rc;

	cbctl->data.supported =
		cmd->data.sbp.data.query_cmds_supp.supported_cmds;
	वापस 0;
पूर्ण

/**
 * qeth_bridgeport_query_support() - store biपंचांगask of supported subfunctions.
 * @card:			     qeth_card काष्ठाure poपूर्णांकer.
 *
 * Sets biपंचांगask of supported setbridgeport subfunctions in the qeth_card
 * strucutre: card->options.sbp.supported_funcs.
 */
अटल व्योम qeth_bridgeport_query_support(काष्ठा qeth_card *card)
अणु
	काष्ठा qeth_cmd_buffer *iob;
	काष्ठा _qeth_sbp_cbctl cbctl;

	QETH_CARD_TEXT(card, 2, "brqsuppo");
	iob = qeth_sbp_build_cmd(card, IPA_SBP_QUERY_COMMANDS_SUPPORTED,
				 SBP_DATA_SIZखातापूर्ण(query_cmds_supp));
	अगर (!iob)
		वापस;

	अगर (qeth_send_ipa_cmd(card, iob, qeth_bridgeport_query_support_cb,
			      &cbctl)) अणु
		card->options.sbp.role = QETH_SBP_ROLE_NONE;
		card->options.sbp.supported_funcs = 0;
		वापस;
	पूर्ण
	card->options.sbp.supported_funcs = cbctl.data.supported;
पूर्ण

अटल पूर्णांक qeth_bridgeport_query_ports_cb(काष्ठा qeth_card *card,
	काष्ठा qeth_reply *reply, अचिन्हित दीर्घ data)
अणु
	काष्ठा qeth_ipa_cmd *cmd = (काष्ठा qeth_ipa_cmd *) data;
	काष्ठा _qeth_sbp_cbctl *cbctl = (काष्ठा _qeth_sbp_cbctl *)reply->param;
	काष्ठा qeth_sbp_port_data *qports;
	पूर्णांक rc;

	QETH_CARD_TEXT(card, 2, "brqprtcb");
	rc = qeth_bridgeport_makerc(card, cmd);
	अगर (rc)
		वापस rc;

	qports = &cmd->data.sbp.data.port_data;
	अगर (qports->entry_length != माप(काष्ठा qeth_sbp_port_entry)) अणु
		QETH_CARD_TEXT_(card, 2, "SBPs%04x", qports->entry_length);
		वापस -EINVAL;
	पूर्ण
	/* first entry contains the state of the local port */
	अगर (qports->num_entries > 0) अणु
		अगर (cbctl->data.qports.role)
			*cbctl->data.qports.role = qports->entry[0].role;
		अगर (cbctl->data.qports.state)
			*cbctl->data.qports.state = qports->entry[0].state;
	पूर्ण
	वापस 0;
पूर्ण

/**
 * qeth_bridgeport_query_ports() - query local bridgeport status.
 * @card:			   qeth_card काष्ठाure poपूर्णांकer.
 * @role:   Role of the port: 0-none, 1-primary, 2-secondary.
 * @state:  State of the port: 0-inactive, 1-standby, 2-active.
 *
 * Returns negative त्रुटि_सं-compatible error indication or 0 on success.
 *
 * 'role' and 'state' are not updated in हाल of hardware operation failure.
 */
पूर्णांक qeth_bridgeport_query_ports(काष्ठा qeth_card *card,
	क्रमागत qeth_sbp_roles *role, क्रमागत qeth_sbp_states *state)
अणु
	काष्ठा qeth_cmd_buffer *iob;
	काष्ठा _qeth_sbp_cbctl cbctl = अणु
		.data = अणु
			.qports = अणु
				.role = role,
				.state = state,
			पूर्ण,
		पूर्ण,
	पूर्ण;

	QETH_CARD_TEXT(card, 2, "brqports");
	अगर (!(card->options.sbp.supported_funcs & IPA_SBP_QUERY_BRIDGE_PORTS))
		वापस -EOPNOTSUPP;
	iob = qeth_sbp_build_cmd(card, IPA_SBP_QUERY_BRIDGE_PORTS, 0);
	अगर (!iob)
		वापस -ENOMEM;

	वापस qeth_send_ipa_cmd(card, iob, qeth_bridgeport_query_ports_cb,
				 &cbctl);
पूर्ण

अटल पूर्णांक qeth_bridgeport_set_cb(काष्ठा qeth_card *card,
	काष्ठा qeth_reply *reply, अचिन्हित दीर्घ data)
अणु
	काष्ठा qeth_ipa_cmd *cmd = (काष्ठा qeth_ipa_cmd *)data;

	QETH_CARD_TEXT(card, 2, "brsetrcb");
	वापस qeth_bridgeport_makerc(card, cmd);
पूर्ण

/**
 * qeth_bridgeport_setrole() - Assign primary role to the port.
 * @card:		       qeth_card काष्ठाure poपूर्णांकer.
 * @role:		       Role to assign.
 *
 * Returns negative त्रुटि_सं-compatible error indication or 0 on success.
 */
पूर्णांक qeth_bridgeport_setrole(काष्ठा qeth_card *card, क्रमागत qeth_sbp_roles role)
अणु
	काष्ठा qeth_cmd_buffer *iob;
	क्रमागत qeth_ipa_sbp_cmd setcmd;
	अचिन्हित पूर्णांक cmdlength = 0;

	QETH_CARD_TEXT(card, 2, "brsetrol");
	चयन (role) अणु
	हाल QETH_SBP_ROLE_NONE:
		setcmd = IPA_SBP_RESET_BRIDGE_PORT_ROLE;
		अवरोध;
	हाल QETH_SBP_ROLE_PRIMARY:
		setcmd = IPA_SBP_SET_PRIMARY_BRIDGE_PORT;
		cmdlength = SBP_DATA_SIZखातापूर्ण(set_primary);
		अवरोध;
	हाल QETH_SBP_ROLE_SECONDARY:
		setcmd = IPA_SBP_SET_SECONDARY_BRIDGE_PORT;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण
	अगर (!(card->options.sbp.supported_funcs & setcmd))
		वापस -EOPNOTSUPP;
	iob = qeth_sbp_build_cmd(card, setcmd, cmdlength);
	अगर (!iob)
		वापस -ENOMEM;

	वापस qeth_send_ipa_cmd(card, iob, qeth_bridgeport_set_cb, शून्य);
पूर्ण

अटल व्योम qeth_bridgeport_an_set_cb(व्योम *priv,
				      काष्ठा chsc_pnso_naid_l2 *entry)
अणु
	काष्ठा qeth_card *card = (काष्ठा qeth_card *)priv;
	u8 code;

	code = IPA_ADDR_CHANGE_CODE_MACADDR;
	अगर (entry->addr_lnid.lnid < VLAN_N_VID)
		code |= IPA_ADDR_CHANGE_CODE_VLANID;
	qeth_bridge_emit_host_event(card, anev_reg_unreg, code,
				    (काष्ठा net_अगर_token *)&entry->nit,
				    (काष्ठा mac_addr_lnid *)&entry->addr_lnid);
पूर्ण

/**
 * qeth_bridgeport_an_set() - Enable or disable bridgeport address notअगरication
 * @card:		      qeth_card काष्ठाure poपूर्णांकer.
 * @enable:		      0 - disable, non-zero - enable notअगरications
 *
 * Returns negative त्रुटि_सं-compatible error indication or 0 on success.
 *
 * On enable, emits a series of address notअगरications udev events क्रम all
 * currently रेजिस्टरed hosts.
 */
पूर्णांक qeth_bridgeport_an_set(काष्ठा qeth_card *card, पूर्णांक enable)
अणु
	पूर्णांक rc;

	अगर (!card->options.sbp.supported_funcs)
		वापस -EOPNOTSUPP;

	अगर (enable) अणु
		qeth_bridge_emit_host_event(card, anev_reset, 0, शून्य, शून्य);
		qeth_l2_set_pnso_mode(card, QETH_PNSO_BRIDGEPORT);
		rc = qeth_l2_pnso(card, PNSO_OC_NET_BRIDGE_INFO, 1,
				  qeth_bridgeport_an_set_cb, card);
		अगर (rc)
			qeth_l2_set_pnso_mode(card, QETH_PNSO_NONE);
	पूर्ण अन्यथा अणु
		rc = qeth_l2_pnso(card, PNSO_OC_NET_BRIDGE_INFO, 0, शून्य, शून्य);
		qeth_l2_set_pnso_mode(card, QETH_PNSO_NONE);
	पूर्ण
	वापस rc;
पूर्ण

/* VNIC Characteristics support */

/* handle VNICC IPA command वापस codes; convert to error codes */
अटल पूर्णांक qeth_l2_vnicc_makerc(काष्ठा qeth_card *card, u16 ipa_rc)
अणु
	पूर्णांक rc;

	चयन (ipa_rc) अणु
	हाल IPA_RC_SUCCESS:
		वापस ipa_rc;
	हाल IPA_RC_L2_UNSUPPORTED_CMD:
	हाल IPA_RC_NOTSUPP:
		rc = -EOPNOTSUPP;
		अवरोध;
	हाल IPA_RC_VNICC_OOSEQ:
		rc = -EALREADY;
		अवरोध;
	हाल IPA_RC_VNICC_VNICBP:
		rc = -EBUSY;
		अवरोध;
	हाल IPA_RC_L2_ADDR_TABLE_FULL:
		rc = -ENOSPC;
		अवरोध;
	हाल IPA_RC_L2_MAC_NOT_AUTH_BY_ADP:
		rc = -EACCES;
		अवरोध;
	शेष:
		rc = -EIO;
	पूर्ण

	QETH_CARD_TEXT_(card, 2, "err%04x", ipa_rc);
	वापस rc;
पूर्ण

/* generic VNICC request call back */
अटल पूर्णांक qeth_l2_vnicc_request_cb(काष्ठा qeth_card *card,
				    काष्ठा qeth_reply *reply,
				    अचिन्हित दीर्घ data)
अणु
	काष्ठा qeth_ipa_cmd *cmd = (काष्ठा qeth_ipa_cmd *) data;
	काष्ठा qeth_ipacmd_vnicc *rep = &cmd->data.vnicc;
	u32 sub_cmd = cmd->data.vnicc.hdr.sub_command;

	QETH_CARD_TEXT(card, 2, "vniccrcb");
	अगर (cmd->hdr.वापस_code)
		वापस qeth_l2_vnicc_makerc(card, cmd->hdr.वापस_code);
	/* वापस results to caller */
	card->options.vnicc.sup_अक्षरs = rep->vnicc_cmds.supported;
	card->options.vnicc.cur_अक्षरs = rep->vnicc_cmds.enabled;

	अगर (sub_cmd == IPA_VNICC_QUERY_CMDS)
		*(u32 *)reply->param = rep->data.query_cmds.sup_cmds;
	अन्यथा अगर (sub_cmd == IPA_VNICC_GET_TIMEOUT)
		*(u32 *)reply->param = rep->data.माला_लोet_समयout.समयout;

	वापस 0;
पूर्ण

अटल काष्ठा qeth_cmd_buffer *qeth_l2_vnicc_build_cmd(काष्ठा qeth_card *card,
						       u32 vnicc_cmd,
						       अचिन्हित पूर्णांक data_length)
अणु
	काष्ठा qeth_ipacmd_vnicc_hdr *hdr;
	काष्ठा qeth_cmd_buffer *iob;

	iob = qeth_ipa_alloc_cmd(card, IPA_CMD_VNICC, QETH_PROT_NONE,
				 data_length +
				 दुरत्व(काष्ठा qeth_ipacmd_vnicc, data));
	अगर (!iob)
		वापस शून्य;

	hdr = &__ipa_cmd(iob)->data.vnicc.hdr;
	hdr->data_length = माप(*hdr) + data_length;
	hdr->sub_command = vnicc_cmd;
	वापस iob;
पूर्ण

/* VNICC query VNIC अक्षरacteristics request */
अटल पूर्णांक qeth_l2_vnicc_query_अक्षरs(काष्ठा qeth_card *card)
अणु
	काष्ठा qeth_cmd_buffer *iob;

	QETH_CARD_TEXT(card, 2, "vniccqch");
	iob = qeth_l2_vnicc_build_cmd(card, IPA_VNICC_QUERY_CHARS, 0);
	अगर (!iob)
		वापस -ENOMEM;

	वापस qeth_send_ipa_cmd(card, iob, qeth_l2_vnicc_request_cb, शून्य);
पूर्ण

/* VNICC query sub commands request */
अटल पूर्णांक qeth_l2_vnicc_query_cmds(काष्ठा qeth_card *card, u32 vnic_अक्षर,
				    u32 *sup_cmds)
अणु
	काष्ठा qeth_cmd_buffer *iob;

	QETH_CARD_TEXT(card, 2, "vniccqcm");
	iob = qeth_l2_vnicc_build_cmd(card, IPA_VNICC_QUERY_CMDS,
				      VNICC_DATA_SIZखातापूर्ण(query_cmds));
	अगर (!iob)
		वापस -ENOMEM;

	__ipa_cmd(iob)->data.vnicc.data.query_cmds.vnic_अक्षर = vnic_अक्षर;

	वापस qeth_send_ipa_cmd(card, iob, qeth_l2_vnicc_request_cb, sup_cmds);
पूर्ण

/* VNICC enable/disable अक्षरacteristic request */
अटल पूर्णांक qeth_l2_vnicc_set_अक्षर(काष्ठा qeth_card *card, u32 vnic_अक्षर,
				      u32 cmd)
अणु
	काष्ठा qeth_cmd_buffer *iob;

	QETH_CARD_TEXT(card, 2, "vniccedc");
	iob = qeth_l2_vnicc_build_cmd(card, cmd, VNICC_DATA_SIZखातापूर्ण(set_अक्षर));
	अगर (!iob)
		वापस -ENOMEM;

	__ipa_cmd(iob)->data.vnicc.data.set_अक्षर.vnic_अक्षर = vnic_अक्षर;

	वापस qeth_send_ipa_cmd(card, iob, qeth_l2_vnicc_request_cb, शून्य);
पूर्ण

/* VNICC get/set समयout क्रम अक्षरacteristic request */
अटल पूर्णांक qeth_l2_vnicc_माला_लोet_समयout(काष्ठा qeth_card *card, u32 vnicc,
					u32 cmd, u32 *समयout)
अणु
	काष्ठा qeth_vnicc_माला_लोet_समयout *माला_लोet_समयout;
	काष्ठा qeth_cmd_buffer *iob;

	QETH_CARD_TEXT(card, 2, "vniccgst");
	iob = qeth_l2_vnicc_build_cmd(card, cmd,
				      VNICC_DATA_SIZखातापूर्ण(माला_लोet_समयout));
	अगर (!iob)
		वापस -ENOMEM;

	माला_लोet_समयout = &__ipa_cmd(iob)->data.vnicc.data.माला_लोet_समयout;
	माला_लोet_समयout->vnic_अक्षर = vnicc;

	अगर (cmd == IPA_VNICC_SET_TIMEOUT)
		माला_लोet_समयout->समयout = *समयout;

	वापस qeth_send_ipa_cmd(card, iob, qeth_l2_vnicc_request_cb, समयout);
पूर्ण

/* recover user समयout setting */
अटल bool qeth_l2_vnicc_recover_समयout(काष्ठा qeth_card *card, u32 vnicc,
					  u32 *समयout)
अणु
	अगर (card->options.vnicc.sup_अक्षरs & vnicc &&
	    card->options.vnicc.माला_लोet_समयout_sup & vnicc &&
	    !qeth_l2_vnicc_माला_लोet_समयout(card, vnicc, IPA_VNICC_SET_TIMEOUT,
					  समयout))
		वापस false;
	*समयout = QETH_VNICC_DEFAULT_TIMEOUT;
	वापस true;
पूर्ण

/* set current VNICC flag state; called from sysfs store function */
पूर्णांक qeth_l2_vnicc_set_state(काष्ठा qeth_card *card, u32 vnicc, bool state)
अणु
	पूर्णांक rc = 0;
	u32 cmd;

	QETH_CARD_TEXT(card, 2, "vniccsch");

	/* check अगर अक्षरacteristic and enable/disable are supported */
	अगर (!(card->options.vnicc.sup_अक्षरs & vnicc) ||
	    !(card->options.vnicc.set_अक्षर_sup & vnicc))
		वापस -EOPNOTSUPP;

	अगर (qeth_bridgeport_is_in_use(card))
		वापस -EBUSY;

	/* set enable/disable command and store wanted अक्षरacteristic */
	अगर (state) अणु
		cmd = IPA_VNICC_ENABLE;
		card->options.vnicc.wanted_अक्षरs |= vnicc;
	पूर्ण अन्यथा अणु
		cmd = IPA_VNICC_DISABLE;
		card->options.vnicc.wanted_अक्षरs &= ~vnicc;
	पूर्ण

	/* करो we need to करो anything? */
	अगर (card->options.vnicc.cur_अक्षरs == card->options.vnicc.wanted_अक्षरs)
		वापस rc;

	/* अगर card is not पढ़ोy, simply stop here */
	अगर (!qeth_card_hw_is_reachable(card)) अणु
		अगर (state)
			card->options.vnicc.cur_अक्षरs |= vnicc;
		अन्यथा
			card->options.vnicc.cur_अक्षरs &= ~vnicc;
		वापस rc;
	पूर्ण

	rc = qeth_l2_vnicc_set_अक्षर(card, vnicc, cmd);
	अगर (rc)
		card->options.vnicc.wanted_अक्षरs =
			card->options.vnicc.cur_अक्षरs;
	अन्यथा अणु
		/* successful online VNICC change; handle special हालs */
		अगर (state && vnicc == QETH_VNICC_RX_BCAST)
			card->options.vnicc.rx_bcast_enabled = true;
		अगर (!state && vnicc == QETH_VNICC_LEARNING)
			qeth_l2_vnicc_recover_समयout(card, vnicc,
					&card->options.vnicc.learning_समयout);
	पूर्ण

	वापस rc;
पूर्ण

/* get current VNICC flag state; called from sysfs show function */
पूर्णांक qeth_l2_vnicc_get_state(काष्ठा qeth_card *card, u32 vnicc, bool *state)
अणु
	पूर्णांक rc = 0;

	QETH_CARD_TEXT(card, 2, "vniccgch");

	/* check अगर अक्षरacteristic is supported */
	अगर (!(card->options.vnicc.sup_अक्षरs & vnicc))
		वापस -EOPNOTSUPP;

	अगर (qeth_bridgeport_is_in_use(card))
		वापस -EBUSY;

	/* अगर card is पढ़ोy, query current VNICC state */
	अगर (qeth_card_hw_is_reachable(card))
		rc = qeth_l2_vnicc_query_अक्षरs(card);

	*state = (card->options.vnicc.cur_अक्षरs & vnicc) ? true : false;
	वापस rc;
पूर्ण

/* set VNICC समयout; called from sysfs store function. Currently, only learning
 * supports समयout
 */
पूर्णांक qeth_l2_vnicc_set_समयout(काष्ठा qeth_card *card, u32 समयout)
अणु
	पूर्णांक rc = 0;

	QETH_CARD_TEXT(card, 2, "vniccsto");

	/* check अगर अक्षरacteristic and set_समयout are supported */
	अगर (!(card->options.vnicc.sup_अक्षरs & QETH_VNICC_LEARNING) ||
	    !(card->options.vnicc.माला_लोet_समयout_sup & QETH_VNICC_LEARNING))
		वापस -EOPNOTSUPP;

	अगर (qeth_bridgeport_is_in_use(card))
		वापस -EBUSY;

	/* करो we need to करो anything? */
	अगर (card->options.vnicc.learning_समयout == समयout)
		वापस rc;

	/* अगर card is not पढ़ोy, simply store the value पूर्णांकernally and वापस */
	अगर (!qeth_card_hw_is_reachable(card)) अणु
		card->options.vnicc.learning_समयout = समयout;
		वापस rc;
	पूर्ण

	/* send समयout value to card; अगर successful, store value पूर्णांकernally */
	rc = qeth_l2_vnicc_माला_लोet_समयout(card, QETH_VNICC_LEARNING,
					  IPA_VNICC_SET_TIMEOUT, &समयout);
	अगर (!rc)
		card->options.vnicc.learning_समयout = समयout;

	वापस rc;
पूर्ण

/* get current VNICC समयout; called from sysfs show function. Currently, only
 * learning supports समयout
 */
पूर्णांक qeth_l2_vnicc_get_समयout(काष्ठा qeth_card *card, u32 *समयout)
अणु
	पूर्णांक rc = 0;

	QETH_CARD_TEXT(card, 2, "vniccgto");

	/* check अगर अक्षरacteristic and get_समयout are supported */
	अगर (!(card->options.vnicc.sup_अक्षरs & QETH_VNICC_LEARNING) ||
	    !(card->options.vnicc.माला_लोet_समयout_sup & QETH_VNICC_LEARNING))
		वापस -EOPNOTSUPP;

	अगर (qeth_bridgeport_is_in_use(card))
		वापस -EBUSY;

	/* अगर card is पढ़ोy, get समयout. Otherwise, just वापस stored value */
	*समयout = card->options.vnicc.learning_समयout;
	अगर (qeth_card_hw_is_reachable(card))
		rc = qeth_l2_vnicc_माला_लोet_समयout(card, QETH_VNICC_LEARNING,
						  IPA_VNICC_GET_TIMEOUT,
						  समयout);

	वापस rc;
पूर्ण

/* check अगर VNICC is currently enabled */
अटल bool _qeth_l2_vnicc_is_in_use(काष्ठा qeth_card *card)
अणु
	अगर (!card->options.vnicc.sup_अक्षरs)
		वापस false;
	/* शेष values are only OK अगर rx_bcast was not enabled by user
	 * or the card is offline.
	 */
	अगर (card->options.vnicc.cur_अक्षरs == QETH_VNICC_DEFAULT) अणु
		अगर (!card->options.vnicc.rx_bcast_enabled ||
		    !qeth_card_hw_is_reachable(card))
			वापस false;
	पूर्ण
	वापस true;
पूर्ण

/**
 *	qeth_bridgeport_allowed - are any qeth_bridgeport functions allowed?
 *	@card: qeth_card काष्ठाure poपूर्णांकer
 *
 *	qeth_bridgeport functionality is mutually exclusive with usage of the
 *	VNIC Characteristics and dev2br address notअगरications
 */
bool qeth_bridgeport_allowed(काष्ठा qeth_card *card)
अणु
	काष्ठा qeth_priv *priv = netdev_priv(card->dev);

	वापस (!_qeth_l2_vnicc_is_in_use(card) &&
		!(priv->brport_features & BR_LEARNING_SYNC));
पूर्ण

/* recover user अक्षरacteristic setting */
अटल bool qeth_l2_vnicc_recover_अक्षर(काष्ठा qeth_card *card, u32 vnicc,
				       bool enable)
अणु
	u32 cmd = enable ? IPA_VNICC_ENABLE : IPA_VNICC_DISABLE;

	अगर (card->options.vnicc.sup_अक्षरs & vnicc &&
	    card->options.vnicc.set_अक्षर_sup & vnicc &&
	    !qeth_l2_vnicc_set_अक्षर(card, vnicc, cmd))
		वापस false;
	card->options.vnicc.wanted_अक्षरs &= ~vnicc;
	card->options.vnicc.wanted_अक्षरs |= QETH_VNICC_DEFAULT & vnicc;
	वापस true;
पूर्ण

/* (re-)initialize VNICC */
अटल व्योम qeth_l2_vnicc_init(काष्ठा qeth_card *card)
अणु
	u32 *समयout = &card->options.vnicc.learning_समयout;
	bool enable, error = false;
	अचिन्हित पूर्णांक अक्षरs_len, i;
	अचिन्हित दीर्घ अक्षरs_पंचांगp;
	u32 sup_cmds, vnicc;

	QETH_CARD_TEXT(card, 2, "vniccini");
	/* reset rx_bcast */
	card->options.vnicc.rx_bcast_enabled = 0;
	/* initial query and storage of VNIC अक्षरacteristics */
	अगर (qeth_l2_vnicc_query_अक्षरs(card)) अणु
		अगर (card->options.vnicc.wanted_अक्षरs != QETH_VNICC_DEFAULT ||
		    *समयout != QETH_VNICC_DEFAULT_TIMEOUT)
			dev_err(&card->gdev->dev, "Configuring the VNIC characteristics failed\n");
		/* fail quietly अगर user didn't change the शेष config */
		card->options.vnicc.sup_अक्षरs = 0;
		card->options.vnicc.cur_अक्षरs = 0;
		card->options.vnicc.wanted_अक्षरs = QETH_VNICC_DEFAULT;
		वापस;
	पूर्ण
	/* get supported commands क्रम each supported अक्षरacteristic */
	अक्षरs_पंचांगp = card->options.vnicc.sup_अक्षरs;
	अक्षरs_len = माप(card->options.vnicc.sup_अक्षरs) * BITS_PER_BYTE;
	क्रम_each_set_bit(i, &अक्षरs_पंचांगp, अक्षरs_len) अणु
		vnicc = BIT(i);
		अगर (qeth_l2_vnicc_query_cmds(card, vnicc, &sup_cmds)) अणु
			sup_cmds = 0;
			error = true;
		पूर्ण
		अगर ((sup_cmds & IPA_VNICC_SET_TIMEOUT) &&
		    (sup_cmds & IPA_VNICC_GET_TIMEOUT))
			card->options.vnicc.माला_लोet_समयout_sup |= vnicc;
		अन्यथा
			card->options.vnicc.माला_लोet_समयout_sup &= ~vnicc;
		अगर ((sup_cmds & IPA_VNICC_ENABLE) &&
		    (sup_cmds & IPA_VNICC_DISABLE))
			card->options.vnicc.set_अक्षर_sup |= vnicc;
		अन्यथा
			card->options.vnicc.set_अक्षर_sup &= ~vnicc;
	पूर्ण
	/* enक्रमce assumed शेष values and recover settings, अगर changed  */
	error |= qeth_l2_vnicc_recover_समयout(card, QETH_VNICC_LEARNING,
					       समयout);
	/* Change अक्षरs, अगर necessary  */
	अक्षरs_पंचांगp = card->options.vnicc.wanted_अक्षरs ^
		    card->options.vnicc.cur_अक्षरs;
	अक्षरs_len = माप(card->options.vnicc.wanted_अक्षरs) * BITS_PER_BYTE;
	क्रम_each_set_bit(i, &अक्षरs_पंचांगp, अक्षरs_len) अणु
		vnicc = BIT(i);
		enable = card->options.vnicc.wanted_अक्षरs & vnicc;
		error |= qeth_l2_vnicc_recover_अक्षर(card, vnicc, enable);
	पूर्ण
	अगर (error)
		dev_err(&card->gdev->dev, "Configuring the VNIC characteristics failed\n");
पूर्ण

/* configure शेष values of VNIC अक्षरacteristics */
अटल व्योम qeth_l2_vnicc_set_शेषs(काष्ठा qeth_card *card)
अणु
	/* अक्षरacteristics values */
	card->options.vnicc.sup_अक्षरs = QETH_VNICC_ALL;
	card->options.vnicc.cur_अक्षरs = QETH_VNICC_DEFAULT;
	card->options.vnicc.learning_समयout = QETH_VNICC_DEFAULT_TIMEOUT;
	/* supported commands */
	card->options.vnicc.set_अक्षर_sup = QETH_VNICC_ALL;
	card->options.vnicc.माला_लोet_समयout_sup = QETH_VNICC_LEARNING;
	/* settings wanted by users */
	card->options.vnicc.wanted_अक्षरs = QETH_VNICC_DEFAULT;
पूर्ण

अटल स्थिर काष्ठा device_type qeth_l2_devtype = अणु
	.name = "qeth_layer2",
	.groups = qeth_l2_attr_groups,
पूर्ण;

अटल पूर्णांक qeth_l2_probe_device(काष्ठा ccwgroup_device *gdev)
अणु
	काष्ठा qeth_card *card = dev_get_drvdata(&gdev->dev);
	पूर्णांक rc;

	अगर (IS_OSN(card))
		dev_notice(&gdev->dev, "OSN support will be dropped in 2021\n");

	qeth_l2_vnicc_set_शेषs(card);
	mutex_init(&card->sbp_lock);

	अगर (gdev->dev.type == &qeth_generic_devtype) अणु
		rc = device_add_groups(&gdev->dev, qeth_l2_attr_groups);
		अगर (rc)
			वापस rc;
	पूर्ण

	INIT_WORK(&card->rx_mode_work, qeth_l2_rx_mode_work);
	वापस 0;
पूर्ण

अटल व्योम qeth_l2_हटाओ_device(काष्ठा ccwgroup_device *gdev)
अणु
	काष्ठा qeth_card *card = dev_get_drvdata(&gdev->dev);

	अगर (gdev->dev.type == &qeth_generic_devtype)
		device_हटाओ_groups(&gdev->dev, qeth_l2_attr_groups);
	qeth_set_allowed_thपढ़ोs(card, 0, 1);
	रुको_event(card->रुको_q, qeth_thपढ़ोs_running(card, 0xffffffff) == 0);

	अगर (gdev->state == CCWGROUP_ONLINE)
		qeth_set_offline(card, card->discipline, false);

	cancel_work_sync(&card->बंद_dev_work);
	अगर (card->dev->reg_state == NETREG_REGISTERED)
		unरेजिस्टर_netdev(card->dev);
पूर्ण

अटल पूर्णांक qeth_l2_set_online(काष्ठा qeth_card *card, bool carrier_ok)
अणु
	काष्ठा net_device *dev = card->dev;
	पूर्णांक rc = 0;

	qeth_l2_detect_dev2br_support(card);

	mutex_lock(&card->sbp_lock);
	qeth_bridgeport_query_support(card);
	अगर (card->options.sbp.supported_funcs) अणु
		qeth_l2_setup_bridgeport_attrs(card);
		dev_info(&card->gdev->dev,
			 "The device represents a Bridge Capable Port\n");
	पूर्ण
	mutex_unlock(&card->sbp_lock);

	qeth_l2_रेजिस्टर_dev_addr(card);

	/* क्रम the rx_bcast अक्षरacteristic, init VNICC after seपंचांगac */
	qeth_l2_vnicc_init(card);

	qeth_l2_trace_features(card);

	/* softsetup */
	QETH_CARD_TEXT(card, 2, "softsetp");

	card->state = CARD_STATE_SOFTSETUP;

	qeth_set_allowed_thपढ़ोs(card, 0xffffffff, 0);

	अगर (dev->reg_state != NETREG_REGISTERED) अणु
		rc = qeth_l2_setup_netdev(card);
		अगर (rc)
			जाओ err_setup;

		अगर (carrier_ok)
			netअगर_carrier_on(dev);
	पूर्ण अन्यथा अणु
		rtnl_lock();
		rc = qeth_set_real_num_tx_queues(card,
						 qeth_tx_actual_queues(card));
		अगर (rc) अणु
			rtnl_unlock();
			जाओ err_set_queues;
		पूर्ण

		अगर (carrier_ok)
			netअगर_carrier_on(dev);
		अन्यथा
			netअगर_carrier_off(dev);

		netअगर_device_attach(dev);
		qeth_enable_hw_features(dev);
		qeth_l2_enable_brport_features(card);

		अगर (card->info.खोलो_when_online) अणु
			card->info.खोलो_when_online = 0;
			dev_खोलो(dev, शून्य);
		पूर्ण
		rtnl_unlock();
	पूर्ण
	वापस 0;

err_set_queues:
err_setup:
	qeth_set_allowed_thपढ़ोs(card, 0, 1);
	card->state = CARD_STATE_DOWN;
	वापस rc;
पूर्ण

अटल व्योम qeth_l2_set_offline(काष्ठा qeth_card *card)
अणु
	काष्ठा qeth_priv *priv = netdev_priv(card->dev);

	qeth_set_allowed_thपढ़ोs(card, 0, 1);
	qeth_l2_drain_rx_mode_cache(card);

	अगर (card->state == CARD_STATE_SOFTSETUP)
		card->state = CARD_STATE_DOWN;

	qeth_l2_set_pnso_mode(card, QETH_PNSO_NONE);
	अगर (priv->brport_features & BR_LEARNING_SYNC)
		qeth_l2_dev2br_fdb_flush(card);
पूर्ण

/* Returns zero अगर the command is successfully "consumed" */
अटल पूर्णांक qeth_l2_control_event(काष्ठा qeth_card *card,
				 काष्ठा qeth_ipa_cmd *cmd)
अणु
	चयन (cmd->hdr.command) अणु
	हाल IPA_CMD_SETBRIDGEPORT_OSA:
	हाल IPA_CMD_SETBRIDGEPORT_IQD:
		अगर (cmd->data.sbp.hdr.command_code ==
		    IPA_SBP_BRIDGE_PORT_STATE_CHANGE) अणु
			qeth_bridge_state_change(card, cmd);
			वापस 0;
		पूर्ण

		वापस 1;
	हाल IPA_CMD_ADDRESS_CHANGE_NOTIF:
		qeth_addr_change_event(card, cmd);
		वापस 0;
	शेष:
		वापस 1;
	पूर्ण
पूर्ण

स्थिर काष्ठा qeth_discipline qeth_l2_discipline = अणु
	.devtype = &qeth_l2_devtype,
	.setup = qeth_l2_probe_device,
	.हटाओ = qeth_l2_हटाओ_device,
	.set_online = qeth_l2_set_online,
	.set_offline = qeth_l2_set_offline,
	.करो_ioctl = शून्य,
	.control_event_handler = qeth_l2_control_event,
पूर्ण;
EXPORT_SYMBOL_GPL(qeth_l2_discipline);

अटल पूर्णांक __init qeth_l2_init(व्योम)
अणु
	pr_info("register layer 2 discipline\n");
	वापस 0;
पूर्ण

अटल व्योम __निकास qeth_l2_निकास(व्योम)
अणु
	pr_info("unregister layer 2 discipline\n");
पूर्ण

module_init(qeth_l2_init);
module_निकास(qeth_l2_निकास);
MODULE_AUTHOR("Frank Blaschka <frank.blaschka@de.ibm.com>");
MODULE_DESCRIPTION("qeth layer 2 discipline");
MODULE_LICENSE("GPL");
