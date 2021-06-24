<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *	Spanning tree protocol; BPDU handling
 *	Linux ethernet bridge
 *
 *	Authors:
 *	Lennert Buytenhek		<buytenh@gnu.org>
 */

#समावेश <linux/kernel.h>
#समावेश <linux/netfilter_bridge.h>
#समावेश <linux/etherdevice.h>
#समावेश <linux/llc.h>
#समावेश <linux/slab.h>
#समावेश <linux/pkt_sched.h>
#समावेश <net/net_namespace.h>
#समावेश <net/llc.h>
#समावेश <net/llc_pdu.h>
#समावेश <net/stp.h>
#समावेश <यंत्र/unaligned.h>

#समावेश "br_private.h"
#समावेश "br_private_stp.h"

#घोषणा STP_HZ		256

#घोषणा LLC_RESERVE माप(काष्ठा llc_pdu_un)

अटल पूर्णांक br_send_bpdu_finish(काष्ठा net *net, काष्ठा sock *sk,
			       काष्ठा sk_buff *skb)
अणु
	वापस dev_queue_xmit(skb);
पूर्ण

अटल व्योम br_send_bpdu(काष्ठा net_bridge_port *p,
			 स्थिर अचिन्हित अक्षर *data, पूर्णांक length)
अणु
	काष्ठा sk_buff *skb;

	skb = dev_alloc_skb(length+LLC_RESERVE);
	अगर (!skb)
		वापस;

	skb->dev = p->dev;
	skb->protocol = htons(ETH_P_802_2);
	skb->priority = TC_PRIO_CONTROL;

	skb_reserve(skb, LLC_RESERVE);
	__skb_put_data(skb, data, length);

	llc_pdu_header_init(skb, LLC_PDU_TYPE_U, LLC_SAP_BSPAN,
			    LLC_SAP_BSPAN, LLC_PDU_CMD);
	llc_pdu_init_as_ui_cmd(skb);

	llc_mac_hdr_init(skb, p->dev->dev_addr, p->br->group_addr);

	skb_reset_mac_header(skb);

	NF_HOOK(NFPROTO_BRIDGE, NF_BR_LOCAL_OUT,
		dev_net(p->dev), शून्य, skb, शून्य, skb->dev,
		br_send_bpdu_finish);
पूर्ण

अटल अंतरभूत व्योम br_set_ticks(अचिन्हित अक्षर *dest, पूर्णांक j)
अणु
	अचिन्हित दीर्घ ticks = (STP_HZ * j)/ HZ;

	put_unaligned_be16(ticks, dest);
पूर्ण

अटल अंतरभूत पूर्णांक br_get_ticks(स्थिर अचिन्हित अक्षर *src)
अणु
	अचिन्हित दीर्घ ticks = get_unaligned_be16(src);

	वापस DIV_ROUND_UP(ticks * HZ, STP_HZ);
पूर्ण

/* called under bridge lock */
व्योम br_send_config_bpdu(काष्ठा net_bridge_port *p, काष्ठा br_config_bpdu *bpdu)
अणु
	अचिन्हित अक्षर buf[35];

	अगर (p->br->stp_enabled != BR_KERNEL_STP)
		वापस;

	buf[0] = 0;
	buf[1] = 0;
	buf[2] = 0;
	buf[3] = BPDU_TYPE_CONFIG;
	buf[4] = (bpdu->topology_change ? 0x01 : 0) |
		(bpdu->topology_change_ack ? 0x80 : 0);
	buf[5] = bpdu->root.prio[0];
	buf[6] = bpdu->root.prio[1];
	buf[7] = bpdu->root.addr[0];
	buf[8] = bpdu->root.addr[1];
	buf[9] = bpdu->root.addr[2];
	buf[10] = bpdu->root.addr[3];
	buf[11] = bpdu->root.addr[4];
	buf[12] = bpdu->root.addr[5];
	buf[13] = (bpdu->root_path_cost >> 24) & 0xFF;
	buf[14] = (bpdu->root_path_cost >> 16) & 0xFF;
	buf[15] = (bpdu->root_path_cost >> 8) & 0xFF;
	buf[16] = bpdu->root_path_cost & 0xFF;
	buf[17] = bpdu->bridge_id.prio[0];
	buf[18] = bpdu->bridge_id.prio[1];
	buf[19] = bpdu->bridge_id.addr[0];
	buf[20] = bpdu->bridge_id.addr[1];
	buf[21] = bpdu->bridge_id.addr[2];
	buf[22] = bpdu->bridge_id.addr[3];
	buf[23] = bpdu->bridge_id.addr[4];
	buf[24] = bpdu->bridge_id.addr[5];
	buf[25] = (bpdu->port_id >> 8) & 0xFF;
	buf[26] = bpdu->port_id & 0xFF;

	br_set_ticks(buf+27, bpdu->message_age);
	br_set_ticks(buf+29, bpdu->max_age);
	br_set_ticks(buf+31, bpdu->hello_समय);
	br_set_ticks(buf+33, bpdu->क्रमward_delay);

	br_send_bpdu(p, buf, 35);

	p->stp_xstats.tx_bpdu++;
पूर्ण

/* called under bridge lock */
व्योम br_send_tcn_bpdu(काष्ठा net_bridge_port *p)
अणु
	अचिन्हित अक्षर buf[4];

	अगर (p->br->stp_enabled != BR_KERNEL_STP)
		वापस;

	buf[0] = 0;
	buf[1] = 0;
	buf[2] = 0;
	buf[3] = BPDU_TYPE_TCN;
	br_send_bpdu(p, buf, 4);

	p->stp_xstats.tx_tcn++;
पूर्ण

/*
 * Called from llc.
 *
 * NO locks, but rcu_पढ़ो_lock
 */
व्योम br_stp_rcv(स्थिर काष्ठा stp_proto *proto, काष्ठा sk_buff *skb,
		काष्ठा net_device *dev)
अणु
	काष्ठा net_bridge_port *p;
	काष्ठा net_bridge *br;
	स्थिर अचिन्हित अक्षर *buf;

	अगर (!pskb_may_pull(skb, 4))
		जाओ err;

	/* compare of protocol id and version */
	buf = skb->data;
	अगर (buf[0] != 0 || buf[1] != 0 || buf[2] != 0)
		जाओ err;

	p = br_port_get_check_rcu(dev);
	अगर (!p)
		जाओ err;

	br = p->br;
	spin_lock(&br->lock);

	अगर (br->stp_enabled != BR_KERNEL_STP)
		जाओ out;

	अगर (!(br->dev->flags & IFF_UP))
		जाओ out;

	अगर (p->state == BR_STATE_DISABLED)
		जाओ out;

	अगर (!ether_addr_equal(eth_hdr(skb)->h_dest, br->group_addr))
		जाओ out;

	अगर (p->flags & BR_BPDU_GUARD) अणु
		br_notice(br, "BPDU received on blocked port %u(%s)\n",
			  (अचिन्हित पूर्णांक) p->port_no, p->dev->name);
		br_stp_disable_port(p);
		जाओ out;
	पूर्ण

	buf = skb_pull(skb, 3);

	अगर (buf[0] == BPDU_TYPE_CONFIG) अणु
		काष्ठा br_config_bpdu bpdu;

		अगर (!pskb_may_pull(skb, 32))
			जाओ out;

		buf = skb->data;
		bpdu.topology_change = (buf[1] & 0x01) ? 1 : 0;
		bpdu.topology_change_ack = (buf[1] & 0x80) ? 1 : 0;

		bpdu.root.prio[0] = buf[2];
		bpdu.root.prio[1] = buf[3];
		bpdu.root.addr[0] = buf[4];
		bpdu.root.addr[1] = buf[5];
		bpdu.root.addr[2] = buf[6];
		bpdu.root.addr[3] = buf[7];
		bpdu.root.addr[4] = buf[8];
		bpdu.root.addr[5] = buf[9];
		bpdu.root_path_cost =
			(buf[10] << 24) |
			(buf[11] << 16) |
			(buf[12] << 8) |
			buf[13];
		bpdu.bridge_id.prio[0] = buf[14];
		bpdu.bridge_id.prio[1] = buf[15];
		bpdu.bridge_id.addr[0] = buf[16];
		bpdu.bridge_id.addr[1] = buf[17];
		bpdu.bridge_id.addr[2] = buf[18];
		bpdu.bridge_id.addr[3] = buf[19];
		bpdu.bridge_id.addr[4] = buf[20];
		bpdu.bridge_id.addr[5] = buf[21];
		bpdu.port_id = (buf[22] << 8) | buf[23];

		bpdu.message_age = br_get_ticks(buf+24);
		bpdu.max_age = br_get_ticks(buf+26);
		bpdu.hello_समय = br_get_ticks(buf+28);
		bpdu.क्रमward_delay = br_get_ticks(buf+30);

		अगर (bpdu.message_age > bpdu.max_age) अणु
			अगर (net_ratelimit())
				br_notice(p->br,
					  "port %u config from %pM"
					  " (message_age %ul > max_age %ul)\n",
					  p->port_no,
					  eth_hdr(skb)->h_source,
					  bpdu.message_age, bpdu.max_age);
			जाओ out;
		पूर्ण

		br_received_config_bpdu(p, &bpdu);
	पूर्ण अन्यथा अगर (buf[0] == BPDU_TYPE_TCN) अणु
		br_received_tcn_bpdu(p);
	पूर्ण
 out:
	spin_unlock(&br->lock);
 err:
	kमुक्त_skb(skb);
पूर्ण
