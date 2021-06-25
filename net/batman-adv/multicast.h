<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/* Copyright (C) B.A.T.M.A.N. contributors:
 *
 * Linus Lथञssing
 */

#अगर_अघोषित _NET_BATMAN_ADV_MULTICAST_H_
#घोषणा _NET_BATMAN_ADV_MULTICAST_H_

#समावेश "main.h"

#समावेश <linux/netlink.h>
#समावेश <linux/skbuff.h>

/**
 * क्रमागत batadv_क्रमw_mode - the way a packet should be क्रमwarded as
 */
क्रमागत batadv_क्रमw_mode अणु
	/**
	 * @BATADV_FORW_ALL: क्रमward the packet to all nodes (currently via
	 *  classic flooding)
	 */
	BATADV_FORW_ALL,

	/**
	 * @BATADV_FORW_SOME: क्रमward the packet to some nodes (currently via
	 *  a multicast-to-unicast conversion and the BATMAN unicast routing
	 *  protocol)
	 */
	BATADV_FORW_SOME,

	/**
	 * @BATADV_FORW_SINGLE: क्रमward the packet to a single node (currently
	 *  via the BATMAN unicast routing protocol)
	 */
	BATADV_FORW_SINGLE,

	/** @BATADV_FORW_NONE: करोn't क्रमward, drop it */
	BATADV_FORW_NONE,
पूर्ण;

#अगर_घोषित CONFIG_BATMAN_ADV_MCAST

क्रमागत batadv_क्रमw_mode
batadv_mcast_क्रमw_mode(काष्ठा batadv_priv *bat_priv, काष्ठा sk_buff *skb,
		       काष्ठा batadv_orig_node **mcast_single_orig);

पूर्णांक batadv_mcast_क्रमw_send_orig(काष्ठा batadv_priv *bat_priv,
				काष्ठा sk_buff *skb,
				अचिन्हित लघु vid,
				काष्ठा batadv_orig_node *orig_node);

पूर्णांक batadv_mcast_क्रमw_send(काष्ठा batadv_priv *bat_priv, काष्ठा sk_buff *skb,
			   अचिन्हित लघु vid);

व्योम batadv_mcast_init(काष्ठा batadv_priv *bat_priv);

पूर्णांक batadv_mcast_mesh_info_put(काष्ठा sk_buff *msg,
			       काष्ठा batadv_priv *bat_priv);

पूर्णांक batadv_mcast_flags_dump(काष्ठा sk_buff *msg, काष्ठा netlink_callback *cb);

व्योम batadv_mcast_मुक्त(काष्ठा batadv_priv *bat_priv);

व्योम batadv_mcast_purge_orig(काष्ठा batadv_orig_node *orig_node);

#अन्यथा

अटल अंतरभूत क्रमागत batadv_क्रमw_mode
batadv_mcast_क्रमw_mode(काष्ठा batadv_priv *bat_priv, काष्ठा sk_buff *skb,
		       काष्ठा batadv_orig_node **mcast_single_orig)
अणु
	वापस BATADV_FORW_ALL;
पूर्ण

अटल अंतरभूत पूर्णांक
batadv_mcast_क्रमw_send_orig(काष्ठा batadv_priv *bat_priv,
			    काष्ठा sk_buff *skb,
			    अचिन्हित लघु vid,
			    काष्ठा batadv_orig_node *orig_node)
अणु
	kमुक्त_skb(skb);
	वापस NET_XMIT_DROP;
पूर्ण

अटल अंतरभूत पूर्णांक
batadv_mcast_क्रमw_send(काष्ठा batadv_priv *bat_priv, काष्ठा sk_buff *skb,
		       अचिन्हित लघु vid)
अणु
	kमुक्त_skb(skb);
	वापस NET_XMIT_DROP;
पूर्ण

अटल अंतरभूत पूर्णांक batadv_mcast_init(काष्ठा batadv_priv *bat_priv)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक
batadv_mcast_mesh_info_put(काष्ठा sk_buff *msg, काष्ठा batadv_priv *bat_priv)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक batadv_mcast_flags_dump(काष्ठा sk_buff *msg,
					  काष्ठा netlink_callback *cb)
अणु
	वापस -EOPNOTSUPP;
पूर्ण

अटल अंतरभूत व्योम batadv_mcast_मुक्त(काष्ठा batadv_priv *bat_priv)
अणु
पूर्ण

अटल अंतरभूत व्योम batadv_mcast_purge_orig(काष्ठा batadv_orig_node *orig_node)
अणु
पूर्ण

#पूर्ण_अगर /* CONFIG_BATMAN_ADV_MCAST */

#पूर्ण_अगर /* _NET_BATMAN_ADV_MULTICAST_H_ */
