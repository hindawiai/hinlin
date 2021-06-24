<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/* Copyright (C) B.A.T.M.A.N. contributors:
 *
 * Martin Hundebथचll, Jeppe Ledet-Pedersen
 */

#अगर_अघोषित _NET_BATMAN_ADV_NETWORK_CODING_H_
#घोषणा _NET_BATMAN_ADV_NETWORK_CODING_H_

#समावेश "main.h"

#समावेश <linux/netdevice.h>
#समावेश <linux/skbuff.h>
#समावेश <linux/types.h>
#समावेश <uapi/linux/batadv_packet.h>

#अगर_घोषित CONFIG_BATMAN_ADV_NC

व्योम batadv_nc_status_update(काष्ठा net_device *net_dev);
पूर्णांक batadv_nc_init(व्योम);
पूर्णांक batadv_nc_mesh_init(काष्ठा batadv_priv *bat_priv);
व्योम batadv_nc_mesh_मुक्त(काष्ठा batadv_priv *bat_priv);
व्योम batadv_nc_update_nc_node(काष्ठा batadv_priv *bat_priv,
			      काष्ठा batadv_orig_node *orig_node,
			      काष्ठा batadv_orig_node *orig_neigh_node,
			      काष्ठा batadv_ogm_packet *ogm_packet,
			      पूर्णांक is_single_hop_neigh);
व्योम batadv_nc_purge_orig(काष्ठा batadv_priv *bat_priv,
			  काष्ठा batadv_orig_node *orig_node,
			  bool (*to_purge)(काष्ठा batadv_priv *,
					   काष्ठा batadv_nc_node *));
व्योम batadv_nc_init_bat_priv(काष्ठा batadv_priv *bat_priv);
व्योम batadv_nc_init_orig(काष्ठा batadv_orig_node *orig_node);
bool batadv_nc_skb_क्रमward(काष्ठा sk_buff *skb,
			   काष्ठा batadv_neigh_node *neigh_node);
व्योम batadv_nc_skb_store_क्रम_decoding(काष्ठा batadv_priv *bat_priv,
				      काष्ठा sk_buff *skb);
व्योम batadv_nc_skb_store_snअगरfed_unicast(काष्ठा batadv_priv *bat_priv,
					 काष्ठा sk_buff *skb);

#अन्यथा /* अगरdef CONFIG_BATMAN_ADV_NC */

अटल अंतरभूत व्योम batadv_nc_status_update(काष्ठा net_device *net_dev)
अणु
पूर्ण

अटल अंतरभूत पूर्णांक batadv_nc_init(व्योम)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक batadv_nc_mesh_init(काष्ठा batadv_priv *bat_priv)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत व्योम batadv_nc_mesh_मुक्त(काष्ठा batadv_priv *bat_priv)
अणु
पूर्ण

अटल अंतरभूत व्योम
batadv_nc_update_nc_node(काष्ठा batadv_priv *bat_priv,
			 काष्ठा batadv_orig_node *orig_node,
			 काष्ठा batadv_orig_node *orig_neigh_node,
			 काष्ठा batadv_ogm_packet *ogm_packet,
			 पूर्णांक is_single_hop_neigh)
अणु
पूर्ण

अटल अंतरभूत व्योम
batadv_nc_purge_orig(काष्ठा batadv_priv *bat_priv,
		     काष्ठा batadv_orig_node *orig_node,
		     bool (*to_purge)(काष्ठा batadv_priv *,
				      काष्ठा batadv_nc_node *))
अणु
पूर्ण

अटल अंतरभूत व्योम batadv_nc_init_bat_priv(काष्ठा batadv_priv *bat_priv)
अणु
पूर्ण

अटल अंतरभूत व्योम batadv_nc_init_orig(काष्ठा batadv_orig_node *orig_node)
अणु
पूर्ण

अटल अंतरभूत bool batadv_nc_skb_क्रमward(काष्ठा sk_buff *skb,
					 काष्ठा batadv_neigh_node *neigh_node)
अणु
	वापस false;
पूर्ण

अटल अंतरभूत व्योम
batadv_nc_skb_store_क्रम_decoding(काष्ठा batadv_priv *bat_priv,
				 काष्ठा sk_buff *skb)
अणु
पूर्ण

अटल अंतरभूत व्योम
batadv_nc_skb_store_snअगरfed_unicast(काष्ठा batadv_priv *bat_priv,
				    काष्ठा sk_buff *skb)
अणु
पूर्ण

#पूर्ण_अगर /* अगरdef CONFIG_BATMAN_ADV_NC */

#पूर्ण_अगर /* _NET_BATMAN_ADV_NETWORK_CODING_H_ */
