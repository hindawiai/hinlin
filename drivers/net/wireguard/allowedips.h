<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Copyright (C) 2015-2019 Jason A. Donenfeld <Jason@zx2c4.com>. All Rights Reserved.
 */

#अगर_अघोषित _WG_ALLOWEDIPS_H
#घोषणा _WG_ALLOWEDIPS_H

#समावेश <linux/mutex.h>
#समावेश <linux/ip.h>
#समावेश <linux/ipv6.h>

काष्ठा wg_peer;

काष्ठा allowedips_node अणु
	काष्ठा wg_peer __rcu *peer;
	काष्ठा allowedips_node __rcu *bit[2];
	u8 cidr, bit_at_a, bit_at_b, bitlen;
	u8 bits[16] __aligned(__alignof(u64));

	/* Keep rarely used members at bottom to be beyond cache line. */
	अचिन्हित दीर्घ parent_bit_packed;
	जोड़ अणु
		काष्ठा list_head peer_list;
		काष्ठा rcu_head rcu;
	पूर्ण;
पूर्ण;

काष्ठा allowedips अणु
	काष्ठा allowedips_node __rcu *root4;
	काष्ठा allowedips_node __rcu *root6;
	u64 seq;
पूर्ण __aligned(4); /* We pack the lower 2 bits of &root, but m68k only gives 16-bit alignment. */

व्योम wg_allowedips_init(काष्ठा allowedips *table);
व्योम wg_allowedips_मुक्त(काष्ठा allowedips *table, काष्ठा mutex *mutex);
पूर्णांक wg_allowedips_insert_v4(काष्ठा allowedips *table, स्थिर काष्ठा in_addr *ip,
			    u8 cidr, काष्ठा wg_peer *peer, काष्ठा mutex *lock);
पूर्णांक wg_allowedips_insert_v6(काष्ठा allowedips *table, स्थिर काष्ठा in6_addr *ip,
			    u8 cidr, काष्ठा wg_peer *peer, काष्ठा mutex *lock);
व्योम wg_allowedips_हटाओ_by_peer(काष्ठा allowedips *table,
				  काष्ठा wg_peer *peer, काष्ठा mutex *lock);
/* The ip input poपूर्णांकer should be __aligned(__alignof(u64))) */
पूर्णांक wg_allowedips_पढ़ो_node(काष्ठा allowedips_node *node, u8 ip[16], u8 *cidr);

/* These वापस a strong reference to a peer: */
काष्ठा wg_peer *wg_allowedips_lookup_dst(काष्ठा allowedips *table,
					 काष्ठा sk_buff *skb);
काष्ठा wg_peer *wg_allowedips_lookup_src(काष्ठा allowedips *table,
					 काष्ठा sk_buff *skb);

#अगर_घोषित DEBUG
bool wg_allowedips_selftest(व्योम);
#पूर्ण_अगर

पूर्णांक wg_allowedips_slab_init(व्योम);
व्योम wg_allowedips_slab_uninit(व्योम);

#पूर्ण_अगर /* _WG_ALLOWEDIPS_H */
