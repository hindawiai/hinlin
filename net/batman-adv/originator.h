<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/* Copyright (C) B.A.T.M.A.N. contributors:
 *
 * Marek Lindner, Simon Wunderlich
 */

#अगर_अघोषित _NET_BATMAN_ADV_ORIGINATOR_H_
#घोषणा _NET_BATMAN_ADV_ORIGINATOR_H_

#समावेश "main.h"

#समावेश <linux/compiler.h>
#समावेश <linux/अगर_ether.h>
#समावेश <linux/jhash.h>
#समावेश <linux/netlink.h>
#समावेश <linux/skbuff.h>
#समावेश <linux/types.h>

bool batadv_compare_orig(स्थिर काष्ठा hlist_node *node, स्थिर व्योम *data2);
पूर्णांक batadv_originator_init(काष्ठा batadv_priv *bat_priv);
व्योम batadv_originator_मुक्त(काष्ठा batadv_priv *bat_priv);
व्योम batadv_purge_orig_ref(काष्ठा batadv_priv *bat_priv);
व्योम batadv_orig_node_put(काष्ठा batadv_orig_node *orig_node);
काष्ठा batadv_orig_node *batadv_orig_node_new(काष्ठा batadv_priv *bat_priv,
					      स्थिर u8 *addr);
काष्ठा batadv_hardअगर_neigh_node *
batadv_hardअगर_neigh_get(स्थिर काष्ठा batadv_hard_अगरace *hard_अगरace,
			स्थिर u8 *neigh_addr);
व्योम
batadv_hardअगर_neigh_put(काष्ठा batadv_hardअगर_neigh_node *hardअगर_neigh);
काष्ठा batadv_neigh_node *
batadv_neigh_node_get_or_create(काष्ठा batadv_orig_node *orig_node,
				काष्ठा batadv_hard_अगरace *hard_अगरace,
				स्थिर u8 *neigh_addr);
व्योम batadv_neigh_node_put(काष्ठा batadv_neigh_node *neigh_node);
काष्ठा batadv_neigh_node *
batadv_orig_router_get(काष्ठा batadv_orig_node *orig_node,
		       स्थिर काष्ठा batadv_hard_अगरace *अगर_outgoing);
काष्ठा batadv_neigh_अगरinfo *
batadv_neigh_अगरinfo_new(काष्ठा batadv_neigh_node *neigh,
			काष्ठा batadv_hard_अगरace *अगर_outgoing);
काष्ठा batadv_neigh_अगरinfo *
batadv_neigh_अगरinfo_get(काष्ठा batadv_neigh_node *neigh,
			काष्ठा batadv_hard_अगरace *अगर_outgoing);
व्योम batadv_neigh_अगरinfo_put(काष्ठा batadv_neigh_अगरinfo *neigh_अगरinfo);

पूर्णांक batadv_hardअगर_neigh_dump(काष्ठा sk_buff *msg, काष्ठा netlink_callback *cb);

काष्ठा batadv_orig_अगरinfo *
batadv_orig_अगरinfo_get(काष्ठा batadv_orig_node *orig_node,
		       काष्ठा batadv_hard_अगरace *अगर_outgoing);
काष्ठा batadv_orig_अगरinfo *
batadv_orig_अगरinfo_new(काष्ठा batadv_orig_node *orig_node,
		       काष्ठा batadv_hard_अगरace *अगर_outgoing);
व्योम batadv_orig_अगरinfo_put(काष्ठा batadv_orig_अगरinfo *orig_अगरinfo);

पूर्णांक batadv_orig_dump(काष्ठा sk_buff *msg, काष्ठा netlink_callback *cb);
काष्ठा batadv_orig_node_vlan *
batadv_orig_node_vlan_new(काष्ठा batadv_orig_node *orig_node,
			  अचिन्हित लघु vid);
काष्ठा batadv_orig_node_vlan *
batadv_orig_node_vlan_get(काष्ठा batadv_orig_node *orig_node,
			  अचिन्हित लघु vid);
व्योम batadv_orig_node_vlan_put(काष्ठा batadv_orig_node_vlan *orig_vlan);

/**
 * batadv_choose_orig() - Return the index of the orig entry in the hash table
 * @data: mac address of the originator node
 * @size: the size of the hash table
 *
 * Return: the hash index where the object represented by @data should be
 * stored at.
 */
अटल अंतरभूत u32 batadv_choose_orig(स्थिर व्योम *data, u32 size)
अणु
	u32 hash = 0;

	hash = jhash(data, ETH_ALEN, hash);
	वापस hash % size;
पूर्ण

काष्ठा batadv_orig_node *
batadv_orig_hash_find(काष्ठा batadv_priv *bat_priv, स्थिर व्योम *data);

#पूर्ण_अगर /* _NET_BATMAN_ADV_ORIGINATOR_H_ */
