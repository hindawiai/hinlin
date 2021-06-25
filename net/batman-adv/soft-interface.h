<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/* Copyright (C) B.A.T.M.A.N. contributors:
 *
 * Marek Lindner
 */

#अगर_अघोषित _NET_BATMAN_ADV_SOFT_INTERFACE_H_
#घोषणा _NET_BATMAN_ADV_SOFT_INTERFACE_H_

#समावेश "main.h"

#समावेश <linux/netdevice.h>
#समावेश <linux/skbuff.h>
#समावेश <linux/types.h>
#समावेश <net/net_namespace.h>
#समावेश <net/rtnetlink.h>

पूर्णांक batadv_skb_head_push(काष्ठा sk_buff *skb, अचिन्हित पूर्णांक len);
व्योम batadv_पूर्णांकerface_rx(काष्ठा net_device *soft_अगरace,
			 काष्ठा sk_buff *skb, पूर्णांक hdr_size,
			 काष्ठा batadv_orig_node *orig_node);
काष्ठा net_device *batadv_softअगर_create(काष्ठा net *net, स्थिर अक्षर *name);
bool batadv_softअगर_is_valid(स्थिर काष्ठा net_device *net_dev);
बाह्य काष्ठा rtnl_link_ops batadv_link_ops;
पूर्णांक batadv_softअगर_create_vlan(काष्ठा batadv_priv *bat_priv, अचिन्हित लघु vid);
व्योम batadv_softअगर_vlan_put(काष्ठा batadv_softअगर_vlan *softअगर_vlan);
काष्ठा batadv_softअगर_vlan *batadv_softअगर_vlan_get(काष्ठा batadv_priv *bat_priv,
						  अचिन्हित लघु vid);

#पूर्ण_अगर /* _NET_BATMAN_ADV_SOFT_INTERFACE_H_ */
