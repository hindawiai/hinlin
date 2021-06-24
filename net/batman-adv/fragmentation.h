<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/* Copyright (C) B.A.T.M.A.N. contributors:
 *
 * Martin Hundebथचll <martin@hundeboll.net>
 */

#अगर_अघोषित _NET_BATMAN_ADV_FRAGMENTATION_H_
#घोषणा _NET_BATMAN_ADV_FRAGMENTATION_H_

#समावेश "main.h"

#समावेश <linux/compiler.h>
#समावेश <linux/list.h>
#समावेश <linux/skbuff.h>
#समावेश <linux/मानकघोष.स>
#समावेश <linux/types.h>

व्योम batadv_frag_purge_orig(काष्ठा batadv_orig_node *orig,
			    bool (*check_cb)(काष्ठा batadv_frag_table_entry *));
bool batadv_frag_skb_fwd(काष्ठा sk_buff *skb,
			 काष्ठा batadv_hard_अगरace *recv_अगर,
			 काष्ठा batadv_orig_node *orig_node_src);
bool batadv_frag_skb_buffer(काष्ठा sk_buff **skb,
			    काष्ठा batadv_orig_node *orig_node);
पूर्णांक batadv_frag_send_packet(काष्ठा sk_buff *skb,
			    काष्ठा batadv_orig_node *orig_node,
			    काष्ठा batadv_neigh_node *neigh_node);

/**
 * batadv_frag_check_entry() - check अगर a list of fragments has समयd out
 * @frags_entry: table entry to check
 *
 * Return: true अगर the frags entry has समयd out, false otherwise.
 */
अटल अंतरभूत bool
batadv_frag_check_entry(काष्ठा batadv_frag_table_entry *frags_entry)
अणु
	अगर (!hlist_empty(&frags_entry->fragment_list) &&
	    batadv_has_समयd_out(frags_entry->बारtamp, BATADV_FRAG_TIMEOUT))
		वापस true;
	वापस false;
पूर्ण

#पूर्ण_अगर /* _NET_BATMAN_ADV_FRAGMENTATION_H_ */
