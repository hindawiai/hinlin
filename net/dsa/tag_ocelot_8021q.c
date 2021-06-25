<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/* Copyright 2020-2021 NXP Semiconductors
 *
 * An implementation of the software-defined tag_8021q.c tagger क्रमmat, which
 * also preserves full functionality under a vlan_filtering bridge. It करोes
 * this by using the TCAM engines क्रम:
 * - pushing the RX VLAN as a second, outer tag, on egress towards the CPU port
 * - redirecting towards the correct front port based on TX VLAN and popping
 *   that on egress
 */
#समावेश <linux/dsa/8021q.h>
#समावेश <soc/mscc/ocelot.h>
#समावेश <soc/mscc/ocelot_ptp.h>
#समावेश "dsa_priv.h"

अटल काष्ठा sk_buff *ocelot_xmit(काष्ठा sk_buff *skb,
				   काष्ठा net_device *netdev)
अणु
	काष्ठा dsa_port *dp = dsa_slave_to_port(netdev);
	u16 tx_vid = dsa_8021q_tx_vid(dp->ds, dp->index);
	u16 queue_mapping = skb_get_queue_mapping(skb);
	u8 pcp = netdev_txq_to_tc(netdev, queue_mapping);
	काष्ठा ocelot *ocelot = dp->ds->priv;
	पूर्णांक port = dp->index;
	u32 rew_op = 0;

	rew_op = ocelot_ptp_rew_op(skb);
	अगर (rew_op) अणु
		अगर (!ocelot_can_inject(ocelot, 0))
			वापस शून्य;

		ocelot_port_inject_frame(ocelot, port, 0, rew_op, skb);
		वापस शून्य;
	पूर्ण

	वापस dsa_8021q_xmit(skb, netdev, ETH_P_8021Q,
			      ((pcp << VLAN_PRIO_SHIFT) | tx_vid));
पूर्ण

अटल काष्ठा sk_buff *ocelot_rcv(काष्ठा sk_buff *skb,
				  काष्ठा net_device *netdev,
				  काष्ठा packet_type *pt)
अणु
	पूर्णांक src_port, चयन_id, qos_class;
	u16 vid, tci;

	skb_push_rcsum(skb, ETH_HLEN);
	अगर (skb_vlan_tag_present(skb)) अणु
		tci = skb_vlan_tag_get(skb);
		__vlan_hwaccel_clear_tag(skb);
	पूर्ण अन्यथा अणु
		__skb_vlan_pop(skb, &tci);
	पूर्ण
	skb_pull_rcsum(skb, ETH_HLEN);

	vid = tci & VLAN_VID_MASK;
	src_port = dsa_8021q_rx_source_port(vid);
	चयन_id = dsa_8021q_rx_चयन_id(vid);
	qos_class = (tci & VLAN_PRIO_MASK) >> VLAN_PRIO_SHIFT;

	skb->dev = dsa_master_find_slave(netdev, चयन_id, src_port);
	अगर (!skb->dev)
		वापस शून्य;

	skb->offload_fwd_mark = 1;
	skb->priority = qos_class;

	वापस skb;
पूर्ण

अटल स्थिर काष्ठा dsa_device_ops ocelot_8021q_netdev_ops = अणु
	.name			= "ocelot-8021q",
	.proto			= DSA_TAG_PROTO_OCELOT_8021Q,
	.xmit			= ocelot_xmit,
	.rcv			= ocelot_rcv,
	.overhead		= VLAN_HLEN,
	.promisc_on_master	= true,
पूर्ण;

MODULE_LICENSE("GPL v2");
MODULE_ALIAS_DSA_TAG_DRIVER(DSA_TAG_PROTO_OCELOT_8021Q);

module_dsa_tag_driver(ocelot_8021q_netdev_ops);
