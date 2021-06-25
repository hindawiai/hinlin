<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/* Copyright(c) 2020 Intel Corporation. */

#अगर_अघोषित XSK_BUFF_POOL_H_
#घोषणा XSK_BUFF_POOL_H_

#समावेश <linux/अगर_xdp.h>
#समावेश <linux/types.h>
#समावेश <linux/dma-mapping.h>
#समावेश <net/xdp.h>

काष्ठा xsk_buff_pool;
काष्ठा xdp_rxq_info;
काष्ठा xsk_queue;
काष्ठा xdp_desc;
काष्ठा xdp_umem;
काष्ठा xdp_sock;
काष्ठा device;
काष्ठा page;

काष्ठा xdp_buff_xsk अणु
	काष्ठा xdp_buff xdp;
	dma_addr_t dma;
	dma_addr_t frame_dma;
	काष्ठा xsk_buff_pool *pool;
	bool unaligned;
	u64 orig_addr;
	काष्ठा list_head मुक्त_list_node;
पूर्ण;

काष्ठा xsk_dma_map अणु
	dma_addr_t *dma_pages;
	काष्ठा device *dev;
	काष्ठा net_device *netdev;
	refcount_t users;
	काष्ठा list_head list; /* Protected by the RTNL_LOCK */
	u32 dma_pages_cnt;
	bool dma_need_sync;
पूर्ण;

काष्ठा xsk_buff_pool अणु
	/* Members only used in the control path first. */
	काष्ठा device *dev;
	काष्ठा net_device *netdev;
	काष्ठा list_head xsk_tx_list;
	/* Protects modअगरications to the xsk_tx_list */
	spinlock_t xsk_tx_list_lock;
	refcount_t users;
	काष्ठा xdp_umem *umem;
	काष्ठा work_काष्ठा work;
	काष्ठा list_head मुक्त_list;
	u32 heads_cnt;
	u16 queue_id;

	/* Data path members as बंद to मुक्त_heads at the end as possible. */
	काष्ठा xsk_queue *fq ____cacheline_aligned_in_smp;
	काष्ठा xsk_queue *cq;
	/* For perक्रमmance reasons, each buff pool has its own array of dma_pages
	 * even when they are identical.
	 */
	dma_addr_t *dma_pages;
	काष्ठा xdp_buff_xsk *heads;
	u64 chunk_mask;
	u64 addrs_cnt;
	u32 मुक्त_list_cnt;
	u32 dma_pages_cnt;
	u32 मुक्त_heads_cnt;
	u32 headroom;
	u32 chunk_size;
	u32 frame_len;
	u8 cached_need_wakeup;
	bool uses_need_wakeup;
	bool dma_need_sync;
	bool unaligned;
	व्योम *addrs;
	/* Mutual exclusion of the completion ring in the SKB mode. Two हालs to protect:
	 * NAPI TX thपढ़ो and sendmsg error paths in the SKB deकाष्ठाor callback and when
	 * sockets share a single cq when the same netdev and queue id is shared.
	 */
	spinlock_t cq_lock;
	काष्ठा xdp_buff_xsk *मुक्त_heads[];
पूर्ण;

/* AF_XDP core. */
काष्ठा xsk_buff_pool *xp_create_and_assign_umem(काष्ठा xdp_sock *xs,
						काष्ठा xdp_umem *umem);
पूर्णांक xp_assign_dev(काष्ठा xsk_buff_pool *pool, काष्ठा net_device *dev,
		  u16 queue_id, u16 flags);
पूर्णांक xp_assign_dev_shared(काष्ठा xsk_buff_pool *pool, काष्ठा xdp_umem *umem,
			 काष्ठा net_device *dev, u16 queue_id);
व्योम xp_destroy(काष्ठा xsk_buff_pool *pool);
व्योम xp_release(काष्ठा xdp_buff_xsk *xskb);
व्योम xp_get_pool(काष्ठा xsk_buff_pool *pool);
bool xp_put_pool(काष्ठा xsk_buff_pool *pool);
व्योम xp_clear_dev(काष्ठा xsk_buff_pool *pool);
व्योम xp_add_xsk(काष्ठा xsk_buff_pool *pool, काष्ठा xdp_sock *xs);
व्योम xp_del_xsk(काष्ठा xsk_buff_pool *pool, काष्ठा xdp_sock *xs);

/* AF_XDP, and XDP core. */
व्योम xp_मुक्त(काष्ठा xdp_buff_xsk *xskb);

/* AF_XDP ZC drivers, via xdp_sock_buff.h */
व्योम xp_set_rxq_info(काष्ठा xsk_buff_pool *pool, काष्ठा xdp_rxq_info *rxq);
पूर्णांक xp_dma_map(काष्ठा xsk_buff_pool *pool, काष्ठा device *dev,
	       अचिन्हित दीर्घ attrs, काष्ठा page **pages, u32 nr_pages);
व्योम xp_dma_unmap(काष्ठा xsk_buff_pool *pool, अचिन्हित दीर्घ attrs);
काष्ठा xdp_buff *xp_alloc(काष्ठा xsk_buff_pool *pool);
bool xp_can_alloc(काष्ठा xsk_buff_pool *pool, u32 count);
व्योम *xp_raw_get_data(काष्ठा xsk_buff_pool *pool, u64 addr);
dma_addr_t xp_raw_get_dma(काष्ठा xsk_buff_pool *pool, u64 addr);
अटल अंतरभूत dma_addr_t xp_get_dma(काष्ठा xdp_buff_xsk *xskb)
अणु
	वापस xskb->dma;
पूर्ण

अटल अंतरभूत dma_addr_t xp_get_frame_dma(काष्ठा xdp_buff_xsk *xskb)
अणु
	वापस xskb->frame_dma;
पूर्ण

व्योम xp_dma_sync_क्रम_cpu_slow(काष्ठा xdp_buff_xsk *xskb);
अटल अंतरभूत व्योम xp_dma_sync_क्रम_cpu(काष्ठा xdp_buff_xsk *xskb)
अणु
	xp_dma_sync_क्रम_cpu_slow(xskb);
पूर्ण

व्योम xp_dma_sync_क्रम_device_slow(काष्ठा xsk_buff_pool *pool, dma_addr_t dma,
				 माप_प्रकार size);
अटल अंतरभूत व्योम xp_dma_sync_क्रम_device(काष्ठा xsk_buff_pool *pool,
					  dma_addr_t dma, माप_प्रकार size)
अणु
	अगर (!pool->dma_need_sync)
		वापस;

	xp_dma_sync_क्रम_device_slow(pool, dma, size);
पूर्ण

/* Masks क्रम xdp_umem_page flags.
 * The low 12-bits of the addr will be 0 since this is the page address, so we
 * can use them क्रम flags.
 */
#घोषणा XSK_NEXT_PG_CONTIG_SHIFT 0
#घोषणा XSK_NEXT_PG_CONTIG_MASK BIT_ULL(XSK_NEXT_PG_CONTIG_SHIFT)

अटल अंतरभूत bool xp_desc_crosses_non_contig_pg(काष्ठा xsk_buff_pool *pool,
						 u64 addr, u32 len)
अणु
	bool cross_pg = (addr & (PAGE_SIZE - 1)) + len > PAGE_SIZE;

	अगर (pool->dma_pages_cnt && cross_pg) अणु
		वापस !(pool->dma_pages[addr >> PAGE_SHIFT] &
			 XSK_NEXT_PG_CONTIG_MASK);
	पूर्ण
	वापस false;
पूर्ण

अटल अंतरभूत u64 xp_aligned_extract_addr(काष्ठा xsk_buff_pool *pool, u64 addr)
अणु
	वापस addr & pool->chunk_mask;
पूर्ण

अटल अंतरभूत u64 xp_unaligned_extract_addr(u64 addr)
अणु
	वापस addr & XSK_UNALIGNED_BUF_ADDR_MASK;
पूर्ण

अटल अंतरभूत u64 xp_unaligned_extract_offset(u64 addr)
अणु
	वापस addr >> XSK_UNALIGNED_BUF_OFFSET_SHIFT;
पूर्ण

अटल अंतरभूत u64 xp_unaligned_add_offset_to_addr(u64 addr)
अणु
	वापस xp_unaligned_extract_addr(addr) +
		xp_unaligned_extract_offset(addr);
पूर्ण

#पूर्ण_अगर /* XSK_BUFF_POOL_H_ */
