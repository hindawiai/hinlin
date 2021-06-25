<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/* Copyright (C) B.A.T.M.A.N. contributors:
 *
 * Antonio Quartulli
 */

#अगर_अघोषित _NET_BATMAN_ADV_DISTRIBUTED_ARP_TABLE_H_
#घोषणा _NET_BATMAN_ADV_DISTRIBUTED_ARP_TABLE_H_

#समावेश "main.h"

#समावेश <linux/compiler.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/netlink.h>
#समावेश <linux/skbuff.h>
#समावेश <linux/types.h>
#समावेश <uapi/linux/batadv_packet.h>

#समावेश "originator.h"

#अगर_घोषित CONFIG_BATMAN_ADV_DAT

/* BATADV_DAT_ADDR_MAX - maximum address value in the DHT space */
#घोषणा BATADV_DAT_ADDR_MAX ((batadv_dat_addr_t)~(batadv_dat_addr_t)0)

व्योम batadv_dat_status_update(काष्ठा net_device *net_dev);
bool batadv_dat_snoop_outgoing_arp_request(काष्ठा batadv_priv *bat_priv,
					   काष्ठा sk_buff *skb);
bool batadv_dat_snoop_incoming_arp_request(काष्ठा batadv_priv *bat_priv,
					   काष्ठा sk_buff *skb, पूर्णांक hdr_size);
व्योम batadv_dat_snoop_outgoing_arp_reply(काष्ठा batadv_priv *bat_priv,
					 काष्ठा sk_buff *skb);
bool batadv_dat_snoop_incoming_arp_reply(काष्ठा batadv_priv *bat_priv,
					 काष्ठा sk_buff *skb, पूर्णांक hdr_size);
व्योम batadv_dat_snoop_outgoing_dhcp_ack(काष्ठा batadv_priv *bat_priv,
					काष्ठा sk_buff *skb,
					__be16 proto,
					अचिन्हित लघु vid);
व्योम batadv_dat_snoop_incoming_dhcp_ack(काष्ठा batadv_priv *bat_priv,
					काष्ठा sk_buff *skb, पूर्णांक hdr_size);
bool batadv_dat_drop_broadcast_packet(काष्ठा batadv_priv *bat_priv,
				      काष्ठा batadv_क्रमw_packet *क्रमw_packet);

/**
 * batadv_dat_init_orig_node_addr() - assign a DAT address to the orig_node
 * @orig_node: the node to assign the DAT address to
 */
अटल अंतरभूत व्योम
batadv_dat_init_orig_node_addr(काष्ठा batadv_orig_node *orig_node)
अणु
	u32 addr;

	addr = batadv_choose_orig(orig_node->orig, BATADV_DAT_ADDR_MAX);
	orig_node->dat_addr = (batadv_dat_addr_t)addr;
पूर्ण

/**
 * batadv_dat_init_own_addr() - assign a DAT address to the node itself
 * @bat_priv: the bat priv with all the soft पूर्णांकerface inक्रमmation
 * @primary_अगर: a poपूर्णांकer to the primary पूर्णांकerface
 */
अटल अंतरभूत व्योम
batadv_dat_init_own_addr(काष्ठा batadv_priv *bat_priv,
			 काष्ठा batadv_hard_अगरace *primary_अगर)
अणु
	u32 addr;

	addr = batadv_choose_orig(primary_अगर->net_dev->dev_addr,
				  BATADV_DAT_ADDR_MAX);

	bat_priv->dat.addr = (batadv_dat_addr_t)addr;
पूर्ण

पूर्णांक batadv_dat_init(काष्ठा batadv_priv *bat_priv);
व्योम batadv_dat_मुक्त(काष्ठा batadv_priv *bat_priv);
पूर्णांक batadv_dat_cache_dump(काष्ठा sk_buff *msg, काष्ठा netlink_callback *cb);

/**
 * batadv_dat_inc_counter() - increment the correct DAT packet counter
 * @bat_priv: the bat priv with all the soft पूर्णांकerface inक्रमmation
 * @subtype: the 4addr subtype of the packet to be counted
 *
 * Updates the ethtool statistics क्रम the received packet अगर it is a DAT subtype
 */
अटल अंतरभूत व्योम batadv_dat_inc_counter(काष्ठा batadv_priv *bat_priv,
					  u8 subtype)
अणु
	चयन (subtype) अणु
	हाल BATADV_P_DAT_DHT_GET:
		batadv_inc_counter(bat_priv,
				   BATADV_CNT_DAT_GET_RX);
		अवरोध;
	हाल BATADV_P_DAT_DHT_PUT:
		batadv_inc_counter(bat_priv,
				   BATADV_CNT_DAT_PUT_RX);
		अवरोध;
	पूर्ण
पूर्ण

#अन्यथा

अटल अंतरभूत व्योम batadv_dat_status_update(काष्ठा net_device *net_dev)
अणु
पूर्ण

अटल अंतरभूत bool
batadv_dat_snoop_outgoing_arp_request(काष्ठा batadv_priv *bat_priv,
				      काष्ठा sk_buff *skb)
अणु
	वापस false;
पूर्ण

अटल अंतरभूत bool
batadv_dat_snoop_incoming_arp_request(काष्ठा batadv_priv *bat_priv,
				      काष्ठा sk_buff *skb, पूर्णांक hdr_size)
अणु
	वापस false;
पूर्ण

अटल अंतरभूत bool
batadv_dat_snoop_outgoing_arp_reply(काष्ठा batadv_priv *bat_priv,
				    काष्ठा sk_buff *skb)
अणु
	वापस false;
पूर्ण

अटल अंतरभूत bool
batadv_dat_snoop_incoming_arp_reply(काष्ठा batadv_priv *bat_priv,
				    काष्ठा sk_buff *skb, पूर्णांक hdr_size)
अणु
	वापस false;
पूर्ण

अटल अंतरभूत व्योम
batadv_dat_snoop_outgoing_dhcp_ack(काष्ठा batadv_priv *bat_priv,
				   काष्ठा sk_buff *skb, __be16 proto,
				   अचिन्हित लघु vid)
अणु
पूर्ण

अटल अंतरभूत व्योम
batadv_dat_snoop_incoming_dhcp_ack(काष्ठा batadv_priv *bat_priv,
				   काष्ठा sk_buff *skb, पूर्णांक hdr_size)
अणु
पूर्ण

अटल अंतरभूत bool
batadv_dat_drop_broadcast_packet(काष्ठा batadv_priv *bat_priv,
				 काष्ठा batadv_क्रमw_packet *क्रमw_packet)
अणु
	वापस false;
पूर्ण

अटल अंतरभूत व्योम
batadv_dat_init_orig_node_addr(काष्ठा batadv_orig_node *orig_node)
अणु
पूर्ण

अटल अंतरभूत व्योम batadv_dat_init_own_addr(काष्ठा batadv_priv *bat_priv,
					    काष्ठा batadv_hard_अगरace *अगरace)
अणु
पूर्ण

अटल अंतरभूत पूर्णांक batadv_dat_init(काष्ठा batadv_priv *bat_priv)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत व्योम batadv_dat_मुक्त(काष्ठा batadv_priv *bat_priv)
अणु
पूर्ण

अटल अंतरभूत पूर्णांक
batadv_dat_cache_dump(काष्ठा sk_buff *msg, काष्ठा netlink_callback *cb)
अणु
	वापस -EOPNOTSUPP;
पूर्ण

अटल अंतरभूत व्योम batadv_dat_inc_counter(काष्ठा batadv_priv *bat_priv,
					  u8 subtype)
अणु
पूर्ण

#पूर्ण_अगर /* CONFIG_BATMAN_ADV_DAT */

#पूर्ण_अगर /* _NET_BATMAN_ADV_DISTRIBUTED_ARP_TABLE_H_ */
