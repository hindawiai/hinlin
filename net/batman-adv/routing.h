<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/* Copyright (C) B.A.T.M.A.N. contributors:
 *
 * Marek Lindner, Simon Wunderlich
 */

#अगर_अघोषित _NET_BATMAN_ADV_ROUTING_H_
#घोषणा _NET_BATMAN_ADV_ROUTING_H_

#समावेश "main.h"

#समावेश <linux/skbuff.h>
#समावेश <linux/types.h>

bool batadv_check_management_packet(काष्ठा sk_buff *skb,
				    काष्ठा batadv_hard_अगरace *hard_अगरace,
				    पूर्णांक header_len);
व्योम batadv_update_route(काष्ठा batadv_priv *bat_priv,
			 काष्ठा batadv_orig_node *orig_node,
			 काष्ठा batadv_hard_अगरace *recv_अगर,
			 काष्ठा batadv_neigh_node *neigh_node);
पूर्णांक batadv_recv_icmp_packet(काष्ठा sk_buff *skb,
			    काष्ठा batadv_hard_अगरace *recv_अगर);
पूर्णांक batadv_recv_unicast_packet(काष्ठा sk_buff *skb,
			       काष्ठा batadv_hard_अगरace *recv_अगर);
पूर्णांक batadv_recv_frag_packet(काष्ठा sk_buff *skb,
			    काष्ठा batadv_hard_अगरace *अगरace);
पूर्णांक batadv_recv_bcast_packet(काष्ठा sk_buff *skb,
			     काष्ठा batadv_hard_अगरace *recv_अगर);
पूर्णांक batadv_recv_tt_query(काष्ठा sk_buff *skb,
			 काष्ठा batadv_hard_अगरace *recv_अगर);
पूर्णांक batadv_recv_roam_adv(काष्ठा sk_buff *skb,
			 काष्ठा batadv_hard_अगरace *recv_अगर);
पूर्णांक batadv_recv_unicast_tvlv(काष्ठा sk_buff *skb,
			     काष्ठा batadv_hard_अगरace *recv_अगर);
पूर्णांक batadv_recv_unhandled_unicast_packet(काष्ठा sk_buff *skb,
					 काष्ठा batadv_hard_अगरace *recv_अगर);
काष्ठा batadv_neigh_node *
batadv_find_router(काष्ठा batadv_priv *bat_priv,
		   काष्ठा batadv_orig_node *orig_node,
		   काष्ठा batadv_hard_अगरace *recv_अगर);
bool batadv_winकरोw_रक्षित(काष्ठा batadv_priv *bat_priv, s32 seq_num_dअगरf,
			     s32 seq_old_max_dअगरf, अचिन्हित दीर्घ *last_reset,
			     bool *protection_started);

#पूर्ण_अगर /* _NET_BATMAN_ADV_ROUTING_H_ */
