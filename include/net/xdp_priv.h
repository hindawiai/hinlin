<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित __LINUX_NET_XDP_PRIV_H__
#घोषणा __LINUX_NET_XDP_PRIV_H__

#समावेश <linux/rhashtable.h>

/* Private to net/core/xdp.c, but used by trace/events/xdp.h */
काष्ठा xdp_mem_allocator अणु
	काष्ठा xdp_mem_info mem;
	जोड़ अणु
		व्योम *allocator;
		काष्ठा page_pool *page_pool;
		काष्ठा zero_copy_allocator *zc_alloc;
	पूर्ण;
	काष्ठा rhash_head node;
	काष्ठा rcu_head rcu;
पूर्ण;

#पूर्ण_अगर /* __LINUX_NET_XDP_PRIV_H__ */
