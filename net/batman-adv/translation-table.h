<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/* Copyright (C) B.A.T.M.A.N. contributors:
 *
 * Marek Lindner, Simon Wunderlich, Antonio Quartulli
 */

#अगर_अघोषित _NET_BATMAN_ADV_TRANSLATION_TABLE_H_
#घोषणा _NET_BATMAN_ADV_TRANSLATION_TABLE_H_

#समावेश "main.h"

#समावेश <linux/netdevice.h>
#समावेश <linux/netlink.h>
#समावेश <linux/skbuff.h>
#समावेश <linux/types.h>

पूर्णांक batadv_tt_init(काष्ठा batadv_priv *bat_priv);
bool batadv_tt_local_add(काष्ठा net_device *soft_अगरace, स्थिर u8 *addr,
			 अचिन्हित लघु vid, पूर्णांक अगरindex, u32 mark);
u16 batadv_tt_local_हटाओ(काष्ठा batadv_priv *bat_priv,
			   स्थिर u8 *addr, अचिन्हित लघु vid,
			   स्थिर अक्षर *message, bool roaming);
पूर्णांक batadv_tt_local_dump(काष्ठा sk_buff *msg, काष्ठा netlink_callback *cb);
पूर्णांक batadv_tt_global_dump(काष्ठा sk_buff *msg, काष्ठा netlink_callback *cb);
व्योम batadv_tt_global_del_orig(काष्ठा batadv_priv *bat_priv,
			       काष्ठा batadv_orig_node *orig_node,
			       s32 match_vid, स्थिर अक्षर *message);
काष्ठा batadv_tt_global_entry *
batadv_tt_global_hash_find(काष्ठा batadv_priv *bat_priv, स्थिर u8 *addr,
			   अचिन्हित लघु vid);
व्योम batadv_tt_global_entry_put(काष्ठा batadv_tt_global_entry *tt_global_entry);
पूर्णांक batadv_tt_global_hash_count(काष्ठा batadv_priv *bat_priv,
				स्थिर u8 *addr, अचिन्हित लघु vid);
काष्ठा batadv_orig_node *batadv_transtable_search(काष्ठा batadv_priv *bat_priv,
						  स्थिर u8 *src, स्थिर u8 *addr,
						  अचिन्हित लघु vid);
व्योम batadv_tt_मुक्त(काष्ठा batadv_priv *bat_priv);
bool batadv_is_my_client(काष्ठा batadv_priv *bat_priv, स्थिर u8 *addr,
			 अचिन्हित लघु vid);
bool batadv_is_ap_isolated(काष्ठा batadv_priv *bat_priv, u8 *src, u8 *dst,
			   अचिन्हित लघु vid);
व्योम batadv_tt_local_commit_changes(काष्ठा batadv_priv *bat_priv);
bool batadv_tt_global_client_is_roaming(काष्ठा batadv_priv *bat_priv,
					u8 *addr, अचिन्हित लघु vid);
bool batadv_tt_local_client_is_roaming(काष्ठा batadv_priv *bat_priv,
				       u8 *addr, अचिन्हित लघु vid);
व्योम batadv_tt_local_reमाप_प्रकारo_mtu(काष्ठा net_device *soft_अगरace);
bool batadv_tt_add_temporary_global_entry(काष्ठा batadv_priv *bat_priv,
					  काष्ठा batadv_orig_node *orig_node,
					  स्थिर अचिन्हित अक्षर *addr,
					  अचिन्हित लघु vid);
bool batadv_tt_global_is_isolated(काष्ठा batadv_priv *bat_priv,
				  स्थिर u8 *addr, अचिन्हित लघु vid);

पूर्णांक batadv_tt_cache_init(व्योम);
व्योम batadv_tt_cache_destroy(व्योम);

#पूर्ण_अगर /* _NET_BATMAN_ADV_TRANSLATION_TABLE_H_ */
