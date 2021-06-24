<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/* Copyright 2019 NXP Semiconductors
 */
#समावेश <linux/dsa/ocelot.h>
#समावेश <soc/mscc/ocelot.h>
#समावेश "dsa_priv.h"

अटल व्योम ocelot_xmit_common(काष्ठा sk_buff *skb, काष्ठा net_device *netdev,
			       __be32 अगरh_prefix, व्योम **अगरh)
अणु
	काष्ठा dsa_port *dp = dsa_slave_to_port(netdev);
	काष्ठा dsa_चयन *ds = dp->ds;
	व्योम *injection;
	__be32 *prefix;
	u32 rew_op = 0;

	injection = skb_push(skb, OCELOT_TAG_LEN);
	prefix = skb_push(skb, OCELOT_SHORT_PREFIX_LEN);

	*prefix = अगरh_prefix;
	स_रखो(injection, 0, OCELOT_TAG_LEN);
	ocelot_अगरh_set_bypass(injection, 1);
	ocelot_अगरh_set_src(injection, ds->num_ports);
	ocelot_अगरh_set_qos_class(injection, skb->priority);

	rew_op = ocelot_ptp_rew_op(skb);
	अगर (rew_op)
		ocelot_अगरh_set_rew_op(injection, rew_op);

	*अगरh = injection;
पूर्ण

अटल काष्ठा sk_buff *ocelot_xmit(काष्ठा sk_buff *skb,
				   काष्ठा net_device *netdev)
अणु
	काष्ठा dsa_port *dp = dsa_slave_to_port(netdev);
	व्योम *injection;

	ocelot_xmit_common(skb, netdev, cpu_to_be32(0x8880000a), &injection);
	ocelot_अगरh_set_dest(injection, BIT_ULL(dp->index));

	वापस skb;
पूर्ण

अटल काष्ठा sk_buff *seville_xmit(काष्ठा sk_buff *skb,
				    काष्ठा net_device *netdev)
अणु
	काष्ठा dsa_port *dp = dsa_slave_to_port(netdev);
	व्योम *injection;

	ocelot_xmit_common(skb, netdev, cpu_to_be32(0x88800005), &injection);
	seville_अगरh_set_dest(injection, BIT_ULL(dp->index));

	वापस skb;
पूर्ण

अटल काष्ठा sk_buff *ocelot_rcv(काष्ठा sk_buff *skb,
				  काष्ठा net_device *netdev,
				  काष्ठा packet_type *pt)
अणु
	u64 src_port, qos_class;
	u64 vlan_tci, tag_type;
	u8 *start = skb->data;
	काष्ठा dsa_port *dp;
	u8 *extraction;
	u16 vlan_tpid;

	/* Revert skb->data by the amount consumed by the DSA master,
	 * so it poपूर्णांकs to the beginning of the frame.
	 */
	skb_push(skb, ETH_HLEN);
	/* We करोn't care about the लघु prefix, it is just क्रम easy entrance
	 * पूर्णांकo the DSA master's RX filter. Discard it now by moving it पूर्णांकo
	 * the headroom.
	 */
	skb_pull(skb, OCELOT_SHORT_PREFIX_LEN);
	/* And skb->data now poपूर्णांकs to the extraction frame header.
	 * Keep a poपूर्णांकer to it.
	 */
	extraction = skb->data;
	/* Now the EFH is part of the headroom as well */
	skb_pull(skb, OCELOT_TAG_LEN);
	/* Reset the poपूर्णांकer to the real MAC header */
	skb_reset_mac_header(skb);
	skb_reset_mac_len(skb);
	/* And move skb->data to the correct location again */
	skb_pull(skb, ETH_HLEN);

	/* Remove from inet csum the extraction header */
	skb_postpull_rcsum(skb, start, OCELOT_TOTAL_TAG_LEN);

	ocelot_xfh_get_src_port(extraction, &src_port);
	ocelot_xfh_get_qos_class(extraction, &qos_class);
	ocelot_xfh_get_tag_type(extraction, &tag_type);
	ocelot_xfh_get_vlan_tci(extraction, &vlan_tci);

	skb->dev = dsa_master_find_slave(netdev, 0, src_port);
	अगर (!skb->dev)
		/* The चयन will reflect back some frames sent through
		 * sockets खोलोed on the bare DSA master. These will come back
		 * with src_port equal to the index of the CPU port, क्रम which
		 * there is no slave रेजिस्टरed. So करोn't prपूर्णांक any error
		 * message here (ignore and drop those frames).
		 */
		वापस शून्य;

	skb->offload_fwd_mark = 1;
	skb->priority = qos_class;

	/* Ocelot चयनes copy frames unmodअगरied to the CPU. However, it is
	 * possible क्रम the user to request a VLAN modअगरication through
	 * VCAP_IS1_ACT_VID_REPLACE_ENA. In this हाल, what will happen is that
	 * the VLAN ID field from the Extraction Header माला_लो updated, but the
	 * 802.1Q header करोes not (the classअगरied VLAN only becomes visible on
	 * egress through the "port tag" of front-panel ports).
	 * So, क्रम traffic extracted by the CPU, we want to pick up the
	 * classअगरied VLAN and manually replace the existing 802.1Q header from
	 * the packet with it, so that the operating प्रणाली is always up to
	 * date with the result of tc-vlan actions.
	 * NOTE: In VLAN-unaware mode, we करोn't want to करो that, we want the
	 * frame to reमुख्य unmodअगरied, because the classअगरied VLAN is always
	 * equal to the pvid of the ingress port and should not be used क्रम
	 * processing.
	 */
	dp = dsa_slave_to_port(skb->dev);
	vlan_tpid = tag_type ? ETH_P_8021AD : ETH_P_8021Q;

	अगर (dsa_port_is_vlan_filtering(dp) &&
	    eth_hdr(skb)->h_proto == htons(vlan_tpid)) अणु
		u16 dummy_vlan_tci;

		skb_push_rcsum(skb, ETH_HLEN);
		__skb_vlan_pop(skb, &dummy_vlan_tci);
		skb_pull_rcsum(skb, ETH_HLEN);
		__vlan_hwaccel_put_tag(skb, htons(vlan_tpid), vlan_tci);
	पूर्ण

	वापस skb;
पूर्ण

अटल स्थिर काष्ठा dsa_device_ops ocelot_netdev_ops = अणु
	.name			= "ocelot",
	.proto			= DSA_TAG_PROTO_OCELOT,
	.xmit			= ocelot_xmit,
	.rcv			= ocelot_rcv,
	.overhead		= OCELOT_TOTAL_TAG_LEN,
	.promisc_on_master	= true,
पूर्ण;

DSA_TAG_DRIVER(ocelot_netdev_ops);
MODULE_ALIAS_DSA_TAG_DRIVER(DSA_TAG_PROTO_OCELOT);

अटल स्थिर काष्ठा dsa_device_ops seville_netdev_ops = अणु
	.name			= "seville",
	.proto			= DSA_TAG_PROTO_SEVILLE,
	.xmit			= seville_xmit,
	.rcv			= ocelot_rcv,
	.overhead		= OCELOT_TOTAL_TAG_LEN,
	.promisc_on_master	= true,
पूर्ण;

DSA_TAG_DRIVER(seville_netdev_ops);
MODULE_ALIAS_DSA_TAG_DRIVER(DSA_TAG_PROTO_SEVILLE);

अटल काष्ठा dsa_tag_driver *ocelot_tag_driver_array[] = अणु
	&DSA_TAG_DRIVER_NAME(ocelot_netdev_ops),
	&DSA_TAG_DRIVER_NAME(seville_netdev_ops),
पूर्ण;

module_dsa_tag_drivers(ocelot_tag_driver_array);

MODULE_LICENSE("GPL v2");
