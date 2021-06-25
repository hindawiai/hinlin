<शैली गुरु>
/* vcan.c - Virtual CAN पूर्णांकerface
 *
 * Copyright (c) 2002-2017 Volkswagen Group Electronic Research
 * All rights reserved.
 *
 * Redistribution and use in source and binary क्रमms, with or without
 * modअगरication, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary क्रमm must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    करोcumentation and/or other materials provided with the distribution.
 * 3. Neither the name of Volkswagen nor the names of its contributors
 *    may be used to enकरोrse or promote products derived from this software
 *    without specअगरic prior written permission.
 *
 * Alternatively, provided that this notice is retained in full, this
 * software may be distributed under the terms of the GNU General
 * Public License ("GPL") version 2, in which हाल the provisions of the
 * GPL apply INSTEAD OF those given above.
 *
 * The provided data काष्ठाures and बाह्यal पूर्णांकerfaces from this code
 * are not restricted to be used by modules with a GPL compatible license.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 * A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
 * OWNER OR CONTRIBUTORS BE LIABLE FOR ANY सूचीECT, INसूचीECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 * THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH
 * DAMAGE.
 *
 */

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#समावेश <linux/module.h>
#समावेश <linux/init.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/अगर_arp.h>
#समावेश <linux/अगर_ether.h>
#समावेश <linux/can.h>
#समावेश <linux/can/can-ml.h>
#समावेश <linux/can/dev.h>
#समावेश <linux/can/skb.h>
#समावेश <linux/slab.h>
#समावेश <net/rtnetlink.h>

#घोषणा DRV_NAME "vcan"

MODULE_DESCRIPTION("virtual CAN interface");
MODULE_LICENSE("Dual BSD/GPL");
MODULE_AUTHOR("Urs Thuermann <urs.thuermann@volkswagen.de>");
MODULE_ALIAS_RTNL_LINK(DRV_NAME);

/* CAN test feature:
 * Enable the echo on driver level क्रम testing the CAN core echo modes.
 * See Documentation/networking/can.rst क्रम details.
 */

अटल bool echo; /* echo testing. Default: 0 (Off) */
module_param(echo, bool, 0444);
MODULE_PARM_DESC(echo, "Echo sent frames (for testing). Default: 0 (Off)");

अटल व्योम vcan_rx(काष्ठा sk_buff *skb, काष्ठा net_device *dev)
अणु
	काष्ठा canfd_frame *cfd = (काष्ठा canfd_frame *)skb->data;
	काष्ठा net_device_stats *stats = &dev->stats;

	stats->rx_packets++;
	stats->rx_bytes += cfd->len;

	skb->pkt_type  = PACKET_BROADCAST;
	skb->dev       = dev;
	skb->ip_summed = CHECKSUM_UNNECESSARY;

	netअगर_rx_ni(skb);
पूर्ण

अटल netdev_tx_t vcan_tx(काष्ठा sk_buff *skb, काष्ठा net_device *dev)
अणु
	काष्ठा canfd_frame *cfd = (काष्ठा canfd_frame *)skb->data;
	काष्ठा net_device_stats *stats = &dev->stats;
	पूर्णांक loop;

	अगर (can_dropped_invalid_skb(dev, skb))
		वापस NETDEV_TX_OK;

	stats->tx_packets++;
	stats->tx_bytes += cfd->len;

	/* set flag whether this packet has to be looped back */
	loop = skb->pkt_type == PACKET_LOOPBACK;

	अगर (!echo) अणु
		/* no echo handling available inside this driver */
		अगर (loop) अणु
			/* only count the packets here, because the
			 * CAN core alपढ़ोy did the echo क्रम us
			 */
			stats->rx_packets++;
			stats->rx_bytes += cfd->len;
		पूर्ण
		consume_skb(skb);
		वापस NETDEV_TX_OK;
	पूर्ण

	/* perक्रमm standard echo handling क्रम CAN network पूर्णांकerfaces */

	अगर (loop) अणु
		skb = can_create_echo_skb(skb);
		अगर (!skb)
			वापस NETDEV_TX_OK;

		/* receive with packet counting */
		vcan_rx(skb, dev);
	पूर्ण अन्यथा अणु
		/* no looped packets => no counting */
		consume_skb(skb);
	पूर्ण
	वापस NETDEV_TX_OK;
पूर्ण

अटल पूर्णांक vcan_change_mtu(काष्ठा net_device *dev, पूर्णांक new_mtu)
अणु
	/* Do not allow changing the MTU जबतक running */
	अगर (dev->flags & IFF_UP)
		वापस -EBUSY;

	अगर (new_mtu != CAN_MTU && new_mtu != CANFD_MTU)
		वापस -EINVAL;

	dev->mtu = new_mtu;
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा net_device_ops vcan_netdev_ops = अणु
	.nकरो_start_xmit = vcan_tx,
	.nकरो_change_mtu = vcan_change_mtu,
पूर्ण;

अटल व्योम vcan_setup(काष्ठा net_device *dev)
अणु
	dev->type		= ARPHRD_CAN;
	dev->mtu		= CANFD_MTU;
	dev->hard_header_len	= 0;
	dev->addr_len		= 0;
	dev->tx_queue_len	= 0;
	dev->flags		= IFF_NOARP;
	can_set_ml_priv(dev, netdev_priv(dev));

	/* set flags according to driver capabilities */
	अगर (echo)
		dev->flags |= IFF_ECHO;

	dev->netdev_ops		= &vcan_netdev_ops;
	dev->needs_मुक्त_netdev	= true;
पूर्ण

अटल काष्ठा rtnl_link_ops vcan_link_ops __पढ़ो_mostly = अणु
	.kind = DRV_NAME,
	.priv_size = माप(काष्ठा can_ml_priv),
	.setup = vcan_setup,
पूर्ण;

अटल __init पूर्णांक vcan_init_module(व्योम)
अणु
	pr_info("Virtual CAN interface driver\n");

	अगर (echo)
		pr_info("enabled echo on driver level.\n");

	वापस rtnl_link_रेजिस्टर(&vcan_link_ops);
पूर्ण

अटल __निकास व्योम vcan_cleanup_module(व्योम)
अणु
	rtnl_link_unरेजिस्टर(&vcan_link_ops);
पूर्ण

module_init(vcan_init_module);
module_निकास(vcan_cleanup_module);
