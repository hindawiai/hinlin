<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/* Copyright (C) B.A.T.M.A.N. contributors:
 *
 * Marek Lindner, Simon Wunderlich
 */

#अगर_अघोषित _NET_BATMAN_ADV_SEND_H_
#घोषणा _NET_BATMAN_ADV_SEND_H_

#समावेश "main.h"

#समावेश <linux/compiler.h>
#समावेश <linux/skbuff.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/types.h>
#समावेश <uapi/linux/batadv_packet.h>

व्योम batadv_क्रमw_packet_मुक्त(काष्ठा batadv_क्रमw_packet *क्रमw_packet,
			     bool dropped);
काष्ठा batadv_क्रमw_packet *
batadv_क्रमw_packet_alloc(काष्ठा batadv_hard_अगरace *अगर_incoming,
			 काष्ठा batadv_hard_अगरace *अगर_outgoing,
			 atomic_t *queue_left,
			 काष्ठा batadv_priv *bat_priv,
			 काष्ठा sk_buff *skb);
bool batadv_क्रमw_packet_steal(काष्ठा batadv_क्रमw_packet *packet, spinlock_t *l);
व्योम batadv_क्रमw_packet_ogmv1_queue(काष्ठा batadv_priv *bat_priv,
				    काष्ठा batadv_क्रमw_packet *क्रमw_packet,
				    अचिन्हित दीर्घ send_समय);
bool batadv_क्रमw_packet_is_rebroadcast(काष्ठा batadv_क्रमw_packet *क्रमw_packet);

पूर्णांक batadv_send_skb_to_orig(काष्ठा sk_buff *skb,
			    काष्ठा batadv_orig_node *orig_node,
			    काष्ठा batadv_hard_अगरace *recv_अगर);
पूर्णांक batadv_send_skb_packet(काष्ठा sk_buff *skb,
			   काष्ठा batadv_hard_अगरace *hard_अगरace,
			   स्थिर u8 *dst_addr);
पूर्णांक batadv_send_broadcast_skb(काष्ठा sk_buff *skb,
			      काष्ठा batadv_hard_अगरace *hard_अगरace);
पूर्णांक batadv_send_unicast_skb(काष्ठा sk_buff *skb,
			    काष्ठा batadv_neigh_node *neigh_node);
पूर्णांक batadv_add_bcast_packet_to_list(काष्ठा batadv_priv *bat_priv,
				    स्थिर काष्ठा sk_buff *skb,
				    अचिन्हित दीर्घ delay,
				    bool own_packet);
व्योम
batadv_purge_outstanding_packets(काष्ठा batadv_priv *bat_priv,
				 स्थिर काष्ठा batadv_hard_अगरace *hard_अगरace);
bool batadv_send_skb_prepare_unicast_4addr(काष्ठा batadv_priv *bat_priv,
					   काष्ठा sk_buff *skb,
					   काष्ठा batadv_orig_node *orig_node,
					   पूर्णांक packet_subtype);
पूर्णांक batadv_send_skb_unicast(काष्ठा batadv_priv *bat_priv,
			    काष्ठा sk_buff *skb, पूर्णांक packet_type,
			    पूर्णांक packet_subtype,
			    काष्ठा batadv_orig_node *orig_node,
			    अचिन्हित लघु vid);
पूर्णांक batadv_send_skb_via_tt_generic(काष्ठा batadv_priv *bat_priv,
				   काष्ठा sk_buff *skb, पूर्णांक packet_type,
				   पूर्णांक packet_subtype, u8 *dst_hपूर्णांक,
				   अचिन्हित लघु vid);
पूर्णांक batadv_send_skb_via_gw(काष्ठा batadv_priv *bat_priv, काष्ठा sk_buff *skb,
			   अचिन्हित लघु vid);

/**
 * batadv_send_skb_via_tt() - send an skb via TT lookup
 * @bat_priv: the bat priv with all the soft पूर्णांकerface inक्रमmation
 * @skb: the payload to send
 * @dst_hपूर्णांक: can be used to override the destination contained in the skb
 * @vid: the vid to be used to search the translation table
 *
 * Look up the recipient node क्रम the destination address in the ethernet
 * header via the translation table. Wrap the given skb पूर्णांकo a baपंचांगan-adv
 * unicast header. Then send this frame to the according destination node.
 *
 * Return: NET_XMIT_DROP in हाल of error or NET_XMIT_SUCCESS otherwise.
 */
अटल अंतरभूत पूर्णांक batadv_send_skb_via_tt(काष्ठा batadv_priv *bat_priv,
					 काष्ठा sk_buff *skb, u8 *dst_hपूर्णांक,
					 अचिन्हित लघु vid)
अणु
	वापस batadv_send_skb_via_tt_generic(bat_priv, skb, BATADV_UNICAST, 0,
					      dst_hपूर्णांक, vid);
पूर्ण

/**
 * batadv_send_skb_via_tt_4addr() - send an skb via TT lookup
 * @bat_priv: the bat priv with all the soft पूर्णांकerface inक्रमmation
 * @skb: the payload to send
 * @packet_subtype: the unicast 4addr packet subtype to use
 * @dst_hपूर्णांक: can be used to override the destination contained in the skb
 * @vid: the vid to be used to search the translation table
 *
 * Look up the recipient node क्रम the destination address in the ethernet
 * header via the translation table. Wrap the given skb पूर्णांकo a baपंचांगan-adv
 * unicast-4addr header. Then send this frame to the according destination
 * node.
 *
 * Return: NET_XMIT_DROP in हाल of error or NET_XMIT_SUCCESS otherwise.
 */
अटल अंतरभूत पूर्णांक batadv_send_skb_via_tt_4addr(काष्ठा batadv_priv *bat_priv,
					       काष्ठा sk_buff *skb,
					       पूर्णांक packet_subtype,
					       u8 *dst_hपूर्णांक,
					       अचिन्हित लघु vid)
अणु
	वापस batadv_send_skb_via_tt_generic(bat_priv, skb,
					      BATADV_UNICAST_4ADDR,
					      packet_subtype, dst_hपूर्णांक, vid);
पूर्ण

#पूर्ण_अगर /* _NET_BATMAN_ADV_SEND_H_ */
