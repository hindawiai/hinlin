<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/* Copyright 2011-2014 Autronica Fire and Security AS
 *
 * Author(s):
 *	2011-2014 Arvid Brodin, arvid.brodin@alten.se
 * This file contains device methods क्रम creating, using and destroying
 * भव HSR or PRP devices.
 */

#समावेश <linux/netdevice.h>
#समावेश <linux/skbuff.h>
#समावेश <linux/etherdevice.h>
#समावेश <linux/rtnetlink.h>
#समावेश <linux/pkt_sched.h>
#समावेश "hsr_device.h"
#समावेश "hsr_slave.h"
#समावेश "hsr_framereg.h"
#समावेश "hsr_main.h"
#समावेश "hsr_forward.h"

अटल bool is_admin_up(काष्ठा net_device *dev)
अणु
	वापस dev && (dev->flags & IFF_UP);
पूर्ण

अटल bool is_slave_up(काष्ठा net_device *dev)
अणु
	वापस dev && is_admin_up(dev) && netअगर_oper_up(dev);
पूर्ण

अटल व्योम __hsr_set_operstate(काष्ठा net_device *dev, पूर्णांक transition)
अणु
	ग_लिखो_lock_bh(&dev_base_lock);
	अगर (dev->operstate != transition) अणु
		dev->operstate = transition;
		ग_लिखो_unlock_bh(&dev_base_lock);
		netdev_state_change(dev);
	पूर्ण अन्यथा अणु
		ग_लिखो_unlock_bh(&dev_base_lock);
	पूर्ण
पूर्ण

अटल व्योम hsr_set_operstate(काष्ठा hsr_port *master, bool has_carrier)
अणु
	अगर (!is_admin_up(master->dev)) अणु
		__hsr_set_operstate(master->dev, IF_OPER_DOWN);
		वापस;
	पूर्ण

	अगर (has_carrier)
		__hsr_set_operstate(master->dev, IF_OPER_UP);
	अन्यथा
		__hsr_set_operstate(master->dev, IF_OPER_LOWERLAYERDOWN);
पूर्ण

अटल bool hsr_check_carrier(काष्ठा hsr_port *master)
अणु
	काष्ठा hsr_port *port;

	ASSERT_RTNL();

	hsr_क्रम_each_port(master->hsr, port) अणु
		अगर (port->type != HSR_PT_MASTER && is_slave_up(port->dev)) अणु
			netअगर_carrier_on(master->dev);
			वापस true;
		पूर्ण
	पूर्ण

	netअगर_carrier_off(master->dev);

	वापस false;
पूर्ण

अटल व्योम hsr_check_announce(काष्ठा net_device *hsr_dev,
			       अचिन्हित अक्षर old_operstate)
अणु
	काष्ठा hsr_priv *hsr;

	hsr = netdev_priv(hsr_dev);

	अगर (hsr_dev->operstate == IF_OPER_UP && old_operstate != IF_OPER_UP) अणु
		/* Went up */
		hsr->announce_count = 0;
		mod_समयr(&hsr->announce_समयr,
			  jअगरfies + msecs_to_jअगरfies(HSR_ANNOUNCE_INTERVAL));
	पूर्ण

	अगर (hsr_dev->operstate != IF_OPER_UP && old_operstate == IF_OPER_UP)
		/* Went करोwn */
		del_समयr(&hsr->announce_समयr);
पूर्ण

व्योम hsr_check_carrier_and_operstate(काष्ठा hsr_priv *hsr)
अणु
	काष्ठा hsr_port *master;
	अचिन्हित अक्षर old_operstate;
	bool has_carrier;

	master = hsr_port_get_hsr(hsr, HSR_PT_MASTER);
	/* netअगर_stacked_transfer_operstate() cannot be used here since
	 * it करोesn't set IF_OPER_LOWERLAYERDOWN (?)
	 */
	old_operstate = master->dev->operstate;
	has_carrier = hsr_check_carrier(master);
	hsr_set_operstate(master, has_carrier);
	hsr_check_announce(master->dev, old_operstate);
पूर्ण

पूर्णांक hsr_get_max_mtu(काष्ठा hsr_priv *hsr)
अणु
	अचिन्हित पूर्णांक mtu_max;
	काष्ठा hsr_port *port;

	mtu_max = ETH_DATA_LEN;
	hsr_क्रम_each_port(hsr, port)
		अगर (port->type != HSR_PT_MASTER)
			mtu_max = min(port->dev->mtu, mtu_max);

	अगर (mtu_max < HSR_HLEN)
		वापस 0;
	वापस mtu_max - HSR_HLEN;
पूर्ण

अटल पूर्णांक hsr_dev_change_mtu(काष्ठा net_device *dev, पूर्णांक new_mtu)
अणु
	काष्ठा hsr_priv *hsr;

	hsr = netdev_priv(dev);

	अगर (new_mtu > hsr_get_max_mtu(hsr)) अणु
		netdev_info(dev, "A HSR master's MTU cannot be greater than the smallest MTU of its slaves minus the HSR Tag length (%d octets).\n",
			    HSR_HLEN);
		वापस -EINVAL;
	पूर्ण

	dev->mtu = new_mtu;

	वापस 0;
पूर्ण

अटल पूर्णांक hsr_dev_खोलो(काष्ठा net_device *dev)
अणु
	काष्ठा hsr_priv *hsr;
	काष्ठा hsr_port *port;
	अक्षर designation;

	hsr = netdev_priv(dev);
	designation = '\0';

	hsr_क्रम_each_port(hsr, port) अणु
		अगर (port->type == HSR_PT_MASTER)
			जारी;
		चयन (port->type) अणु
		हाल HSR_PT_SLAVE_A:
			designation = 'A';
			अवरोध;
		हाल HSR_PT_SLAVE_B:
			designation = 'B';
			अवरोध;
		शेष:
			designation = '?';
		पूर्ण
		अगर (!is_slave_up(port->dev))
			netdev_warn(dev, "Slave %c (%s) is not up; please bring it up to get a fully working HSR network\n",
				    designation, port->dev->name);
	पूर्ण

	अगर (designation == '\0')
		netdev_warn(dev, "No slave devices configured\n");

	वापस 0;
पूर्ण

अटल पूर्णांक hsr_dev_बंद(काष्ठा net_device *dev)
अणु
	/* Nothing to करो here. */
	वापस 0;
पूर्ण

अटल netdev_features_t hsr_features_recompute(काष्ठा hsr_priv *hsr,
						netdev_features_t features)
अणु
	netdev_features_t mask;
	काष्ठा hsr_port *port;

	mask = features;

	/* Mask out all features that, अगर supported by one device, should be
	 * enabled क्रम all devices (see NETIF_F_ONE_FOR_ALL).
	 *
	 * Anything that's off in mask will not be enabled - so only things
	 * that were in features originally, and also is in NETIF_F_ONE_FOR_ALL,
	 * may become enabled.
	 */
	features &= ~NETIF_F_ONE_FOR_ALL;
	hsr_क्रम_each_port(hsr, port)
		features = netdev_increment_features(features,
						     port->dev->features,
						     mask);

	वापस features;
पूर्ण

अटल netdev_features_t hsr_fix_features(काष्ठा net_device *dev,
					  netdev_features_t features)
अणु
	काष्ठा hsr_priv *hsr = netdev_priv(dev);

	वापस hsr_features_recompute(hsr, features);
पूर्ण

अटल netdev_tx_t hsr_dev_xmit(काष्ठा sk_buff *skb, काष्ठा net_device *dev)
अणु
	काष्ठा hsr_priv *hsr = netdev_priv(dev);
	काष्ठा hsr_port *master;

	master = hsr_port_get_hsr(hsr, HSR_PT_MASTER);
	अगर (master) अणु
		skb->dev = master->dev;
		skb_reset_mac_header(skb);
		skb_reset_mac_len(skb);
		hsr_क्रमward_skb(skb, master);
	पूर्ण अन्यथा अणु
		atomic_दीर्घ_inc(&dev->tx_dropped);
		dev_kमुक्त_skb_any(skb);
	पूर्ण
	वापस NETDEV_TX_OK;
पूर्ण

अटल स्थिर काष्ठा header_ops hsr_header_ops = अणु
	.create	 = eth_header,
	.parse	 = eth_header_parse,
पूर्ण;

अटल काष्ठा sk_buff *hsr_init_skb(काष्ठा hsr_port *master)
अणु
	काष्ठा hsr_priv *hsr = master->hsr;
	काष्ठा sk_buff *skb;
	पूर्णांक hlen, tlen;

	hlen = LL_RESERVED_SPACE(master->dev);
	tlen = master->dev->needed_tailroom;
	/* skb size is same क्रम PRP/HSR frames, only dअगरference
	 * being, क्रम PRP it is a trailer and क्रम HSR it is a
	 * header
	 */
	skb = dev_alloc_skb(माप(काष्ठा hsr_sup_tag) +
			    माप(काष्ठा hsr_sup_payload) + hlen + tlen);

	अगर (!skb)
		वापस skb;

	skb_reserve(skb, hlen);
	skb->dev = master->dev;
	skb->priority = TC_PRIO_CONTROL;

	अगर (dev_hard_header(skb, skb->dev, ETH_P_PRP,
			    hsr->sup_multicast_addr,
			    skb->dev->dev_addr, skb->len) <= 0)
		जाओ out;

	skb_reset_mac_header(skb);
	skb_reset_mac_len(skb);
	skb_reset_network_header(skb);
	skb_reset_transport_header(skb);

	वापस skb;
out:
	kमुक्त_skb(skb);

	वापस शून्य;
पूर्ण

अटल व्योम send_hsr_supervision_frame(काष्ठा hsr_port *master,
				       अचिन्हित दीर्घ *पूर्णांकerval)
अणु
	काष्ठा hsr_priv *hsr = master->hsr;
	__u8 type = HSR_TLV_LIFE_CHECK;
	काष्ठा hsr_sup_payload *hsr_sp;
	काष्ठा hsr_sup_tag *hsr_stag;
	अचिन्हित दीर्घ irqflags;
	काष्ठा sk_buff *skb;

	*पूर्णांकerval = msecs_to_jअगरfies(HSR_LIFE_CHECK_INTERVAL);
	अगर (hsr->announce_count < 3 && hsr->prot_version == 0) अणु
		type = HSR_TLV_ANNOUNCE;
		*पूर्णांकerval = msecs_to_jअगरfies(HSR_ANNOUNCE_INTERVAL);
		hsr->announce_count++;
	पूर्ण

	skb = hsr_init_skb(master);
	अगर (!skb) अणु
		WARN_ONCE(1, "HSR: Could not send supervision frame\n");
		वापस;
	पूर्ण

	hsr_stag = skb_put(skb, माप(काष्ठा hsr_sup_tag));
	set_hsr_stag_path(hsr_stag, (hsr->prot_version ? 0x0 : 0xf));
	set_hsr_stag_HSR_ver(hsr_stag, hsr->prot_version);

	/* From HSRv1 on we have separate supervision sequence numbers. */
	spin_lock_irqsave(&master->hsr->seqnr_lock, irqflags);
	अगर (hsr->prot_version > 0) अणु
		hsr_stag->sequence_nr = htons(hsr->sup_sequence_nr);
		hsr->sup_sequence_nr++;
	पूर्ण अन्यथा अणु
		hsr_stag->sequence_nr = htons(hsr->sequence_nr);
		hsr->sequence_nr++;
	पूर्ण
	spin_unlock_irqrestore(&master->hsr->seqnr_lock, irqflags);

	hsr_stag->HSR_TLV_type = type;
	/* TODO: Why 12 in HSRv0? */
	hsr_stag->HSR_TLV_length = hsr->prot_version ?
				माप(काष्ठा hsr_sup_payload) : 12;

	/* Payload: MacAddressA */
	hsr_sp = skb_put(skb, माप(काष्ठा hsr_sup_payload));
	ether_addr_copy(hsr_sp->macaddress_A, master->dev->dev_addr);

	अगर (skb_put_padto(skb, ETH_ZLEN))
		वापस;

	hsr_क्रमward_skb(skb, master);

	वापस;
पूर्ण

अटल व्योम send_prp_supervision_frame(काष्ठा hsr_port *master,
				       अचिन्हित दीर्घ *पूर्णांकerval)
अणु
	काष्ठा hsr_priv *hsr = master->hsr;
	काष्ठा hsr_sup_payload *hsr_sp;
	काष्ठा hsr_sup_tag *hsr_stag;
	अचिन्हित दीर्घ irqflags;
	काष्ठा sk_buff *skb;

	skb = hsr_init_skb(master);
	अगर (!skb) अणु
		WARN_ONCE(1, "PRP: Could not send supervision frame\n");
		वापस;
	पूर्ण

	*पूर्णांकerval = msecs_to_jअगरfies(HSR_LIFE_CHECK_INTERVAL);
	hsr_stag = skb_put(skb, माप(काष्ठा hsr_sup_tag));
	set_hsr_stag_path(hsr_stag, (hsr->prot_version ? 0x0 : 0xf));
	set_hsr_stag_HSR_ver(hsr_stag, (hsr->prot_version ? 1 : 0));

	/* From HSRv1 on we have separate supervision sequence numbers. */
	spin_lock_irqsave(&master->hsr->seqnr_lock, irqflags);
	hsr_stag->sequence_nr = htons(hsr->sup_sequence_nr);
	hsr->sup_sequence_nr++;
	hsr_stag->HSR_TLV_type = PRP_TLV_LIFE_CHECK_DD;
	hsr_stag->HSR_TLV_length = माप(काष्ठा hsr_sup_payload);

	/* Payload: MacAddressA */
	hsr_sp = skb_put(skb, माप(काष्ठा hsr_sup_payload));
	ether_addr_copy(hsr_sp->macaddress_A, master->dev->dev_addr);

	अगर (skb_put_padto(skb, ETH_ZLEN)) अणु
		spin_unlock_irqrestore(&master->hsr->seqnr_lock, irqflags);
		वापस;
	पूर्ण

	spin_unlock_irqrestore(&master->hsr->seqnr_lock, irqflags);

	hsr_क्रमward_skb(skb, master);
पूर्ण

/* Announce (supervision frame) समयr function
 */
अटल व्योम hsr_announce(काष्ठा समयr_list *t)
अणु
	काष्ठा hsr_priv *hsr;
	काष्ठा hsr_port *master;
	अचिन्हित दीर्घ पूर्णांकerval;

	hsr = from_समयr(hsr, t, announce_समयr);

	rcu_पढ़ो_lock();
	master = hsr_port_get_hsr(hsr, HSR_PT_MASTER);
	hsr->proto_ops->send_sv_frame(master, &पूर्णांकerval);

	अगर (is_admin_up(master->dev))
		mod_समयr(&hsr->announce_समयr, jअगरfies + पूर्णांकerval);

	rcu_पढ़ो_unlock();
पूर्ण

व्योम hsr_del_ports(काष्ठा hsr_priv *hsr)
अणु
	काष्ठा hsr_port *port;

	port = hsr_port_get_hsr(hsr, HSR_PT_SLAVE_A);
	अगर (port)
		hsr_del_port(port);

	port = hsr_port_get_hsr(hsr, HSR_PT_SLAVE_B);
	अगर (port)
		hsr_del_port(port);

	port = hsr_port_get_hsr(hsr, HSR_PT_MASTER);
	अगर (port)
		hsr_del_port(port);
पूर्ण

अटल स्थिर काष्ठा net_device_ops hsr_device_ops = अणु
	.nकरो_change_mtu = hsr_dev_change_mtu,
	.nकरो_खोलो = hsr_dev_खोलो,
	.nकरो_stop = hsr_dev_बंद,
	.nकरो_start_xmit = hsr_dev_xmit,
	.nकरो_fix_features = hsr_fix_features,
पूर्ण;

अटल काष्ठा device_type hsr_type = अणु
	.name = "hsr",
पूर्ण;

अटल काष्ठा hsr_proto_ops hsr_ops = अणु
	.send_sv_frame = send_hsr_supervision_frame,
	.create_tagged_frame = hsr_create_tagged_frame,
	.get_untagged_frame = hsr_get_untagged_frame,
	.drop_frame = hsr_drop_frame,
	.fill_frame_info = hsr_fill_frame_info,
	.invalid_dan_ingress_frame = hsr_invalid_dan_ingress_frame,
पूर्ण;

अटल काष्ठा hsr_proto_ops prp_ops = अणु
	.send_sv_frame = send_prp_supervision_frame,
	.create_tagged_frame = prp_create_tagged_frame,
	.get_untagged_frame = prp_get_untagged_frame,
	.drop_frame = prp_drop_frame,
	.fill_frame_info = prp_fill_frame_info,
	.handle_san_frame = prp_handle_san_frame,
	.update_san_info = prp_update_san_info,
पूर्ण;

व्योम hsr_dev_setup(काष्ठा net_device *dev)
अणु
	eth_hw_addr_अक्रमom(dev);

	ether_setup(dev);
	dev->min_mtu = 0;
	dev->header_ops = &hsr_header_ops;
	dev->netdev_ops = &hsr_device_ops;
	SET_NETDEV_DEVTYPE(dev, &hsr_type);
	dev->priv_flags |= IFF_NO_QUEUE;

	dev->needs_मुक्त_netdev = true;

	dev->hw_features = NETIF_F_SG | NETIF_F_FRAGLIST | NETIF_F_HIGHDMA |
			   NETIF_F_GSO_MASK | NETIF_F_HW_CSUM |
			   NETIF_F_HW_VLAN_CTAG_TX;

	dev->features = dev->hw_features;

	/* Prevent recursive tx locking */
	dev->features |= NETIF_F_LLTX;
	/* VLAN on top of HSR needs testing and probably some work on
	 * hsr_header_create() etc.
	 */
	dev->features |= NETIF_F_VLAN_CHALLENGED;
	/* Not sure about this. Taken from bridge code. netdev_features.h says
	 * it means "Does not change network namespaces".
	 */
	dev->features |= NETIF_F_NETNS_LOCAL;
पूर्ण

/* Return true अगर dev is a HSR master; वापस false otherwise.
 */
bool is_hsr_master(काष्ठा net_device *dev)
अणु
	वापस (dev->netdev_ops->nकरो_start_xmit == hsr_dev_xmit);
पूर्ण
EXPORT_SYMBOL(is_hsr_master);

/* Default multicast address क्रम HSR Supervision frames */
अटल स्थिर अचिन्हित अक्षर def_multicast_addr[ETH_ALEN] __aligned(2) = अणु
	0x01, 0x15, 0x4e, 0x00, 0x01, 0x00
पूर्ण;

पूर्णांक hsr_dev_finalize(काष्ठा net_device *hsr_dev, काष्ठा net_device *slave[2],
		     अचिन्हित अक्षर multicast_spec, u8 protocol_version,
		     काष्ठा netlink_ext_ack *extack)
अणु
	bool unरेजिस्टर = false;
	काष्ठा hsr_priv *hsr;
	पूर्णांक res;

	hsr = netdev_priv(hsr_dev);
	INIT_LIST_HEAD(&hsr->ports);
	INIT_LIST_HEAD(&hsr->node_db);
	INIT_LIST_HEAD(&hsr->self_node_db);
	spin_lock_init(&hsr->list_lock);

	ether_addr_copy(hsr_dev->dev_addr, slave[0]->dev_addr);

	/* initialize protocol specअगरic functions */
	अगर (protocol_version == PRP_V1) अणु
		/* For PRP, lan_id has most signअगरicant 3 bits holding
		 * the net_id of PRP_LAN_ID
		 */
		hsr->net_id = PRP_LAN_ID << 1;
		hsr->proto_ops = &prp_ops;
	पूर्ण अन्यथा अणु
		hsr->proto_ops = &hsr_ops;
	पूर्ण

	/* Make sure we recognize frames from ourselves in hsr_rcv() */
	res = hsr_create_self_node(hsr, hsr_dev->dev_addr,
				   slave[1]->dev_addr);
	अगर (res < 0)
		वापस res;

	spin_lock_init(&hsr->seqnr_lock);
	/* Overflow soon to find bugs easier: */
	hsr->sequence_nr = HSR_SEQNR_START;
	hsr->sup_sequence_nr = HSR_SUP_SEQNR_START;

	समयr_setup(&hsr->announce_समयr, hsr_announce, 0);
	समयr_setup(&hsr->prune_समयr, hsr_prune_nodes, 0);

	ether_addr_copy(hsr->sup_multicast_addr, def_multicast_addr);
	hsr->sup_multicast_addr[ETH_ALEN - 1] = multicast_spec;

	hsr->prot_version = protocol_version;

	/* Make sure the 1st call to netअगर_carrier_on() माला_लो through */
	netअगर_carrier_off(hsr_dev);

	res = hsr_add_port(hsr, hsr_dev, HSR_PT_MASTER, extack);
	अगर (res)
		जाओ err_add_master;

	res = रेजिस्टर_netdevice(hsr_dev);
	अगर (res)
		जाओ err_unरेजिस्टर;

	unरेजिस्टर = true;

	res = hsr_add_port(hsr, slave[0], HSR_PT_SLAVE_A, extack);
	अगर (res)
		जाओ err_unरेजिस्टर;

	res = hsr_add_port(hsr, slave[1], HSR_PT_SLAVE_B, extack);
	अगर (res)
		जाओ err_unरेजिस्टर;

	hsr_debugfs_init(hsr, hsr_dev);
	mod_समयr(&hsr->prune_समयr, jअगरfies + msecs_to_jअगरfies(PRUNE_PERIOD));

	वापस 0;

err_unरेजिस्टर:
	hsr_del_ports(hsr);
err_add_master:
	hsr_del_self_node(hsr);

	अगर (unरेजिस्टर)
		unरेजिस्टर_netdevice(hsr_dev);
	वापस res;
पूर्ण
