<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _X25DEVICE_H
#घोषणा _X25DEVICE_H

#समावेश <linux/अगर_ether.h>
#समावेश <linux/अगर_packet.h>
#समावेश <linux/अगर_x25.h>
#समावेश <linux/skbuff.h>

अटल अंतरभूत __be16 x25_type_trans(काष्ठा sk_buff *skb, काष्ठा net_device *dev)
अणु
	skb->dev = dev;
	skb_reset_mac_header(skb);
	skb->pkt_type = PACKET_HOST;
	
	वापस htons(ETH_P_X25);
पूर्ण
#पूर्ण_अगर
