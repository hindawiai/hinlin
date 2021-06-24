<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/* Copyright (C) B.A.T.M.A.N. contributors:
 *
 * Marek Lindner
 */

#अगर_अघोषित _NET_BATMAN_ADV_GATEWAY_CLIENT_H_
#घोषणा _NET_BATMAN_ADV_GATEWAY_CLIENT_H_

#समावेश "main.h"

#समावेश <linux/netlink.h>
#समावेश <linux/skbuff.h>
#समावेश <linux/types.h>
#समावेश <uapi/linux/batadv_packet.h>

व्योम batadv_gw_check_client_stop(काष्ठा batadv_priv *bat_priv);
व्योम batadv_gw_reselect(काष्ठा batadv_priv *bat_priv);
व्योम batadv_gw_election(काष्ठा batadv_priv *bat_priv);
काष्ठा batadv_orig_node *
batadv_gw_get_selected_orig(काष्ठा batadv_priv *bat_priv);
व्योम batadv_gw_check_election(काष्ठा batadv_priv *bat_priv,
			      काष्ठा batadv_orig_node *orig_node);
व्योम batadv_gw_node_update(काष्ठा batadv_priv *bat_priv,
			   काष्ठा batadv_orig_node *orig_node,
			   काष्ठा batadv_tvlv_gateway_data *gateway);
व्योम batadv_gw_node_delete(काष्ठा batadv_priv *bat_priv,
			   काष्ठा batadv_orig_node *orig_node);
व्योम batadv_gw_node_मुक्त(काष्ठा batadv_priv *bat_priv);
व्योम batadv_gw_node_put(काष्ठा batadv_gw_node *gw_node);
काष्ठा batadv_gw_node *
batadv_gw_get_selected_gw_node(काष्ठा batadv_priv *bat_priv);
पूर्णांक batadv_gw_dump(काष्ठा sk_buff *msg, काष्ठा netlink_callback *cb);
bool batadv_gw_out_of_range(काष्ठा batadv_priv *bat_priv, काष्ठा sk_buff *skb);
क्रमागत batadv_dhcp_recipient
batadv_gw_dhcp_recipient_get(काष्ठा sk_buff *skb, अचिन्हित पूर्णांक *header_len,
			     u8 *chaddr);
काष्ठा batadv_gw_node *batadv_gw_node_get(काष्ठा batadv_priv *bat_priv,
					  काष्ठा batadv_orig_node *orig_node);

#पूर्ण_अगर /* _NET_BATMAN_ADV_GATEWAY_CLIENT_H_ */
