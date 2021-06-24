<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/* Interface क्रम implementing AF_XDP zero-copy support in drivers.
 * Copyright(c) 2020 Intel Corporation.
 */

#अगर_अघोषित _LINUX_XDP_SOCK_DRV_H
#घोषणा _LINUX_XDP_SOCK_DRV_H

#समावेश <net/xdp_sock.h>
#समावेश <net/xsk_buff_pool.h>

#अगर_घोषित CONFIG_XDP_SOCKETS

व्योम xsk_tx_completed(काष्ठा xsk_buff_pool *pool, u32 nb_entries);
bool xsk_tx_peek_desc(काष्ठा xsk_buff_pool *pool, काष्ठा xdp_desc *desc);
u32 xsk_tx_peek_release_desc_batch(काष्ठा xsk_buff_pool *pool, काष्ठा xdp_desc *desc, u32 max);
व्योम xsk_tx_release(काष्ठा xsk_buff_pool *pool);
काष्ठा xsk_buff_pool *xsk_get_pool_from_qid(काष्ठा net_device *dev,
					    u16 queue_id);
व्योम xsk_set_rx_need_wakeup(काष्ठा xsk_buff_pool *pool);
व्योम xsk_set_tx_need_wakeup(काष्ठा xsk_buff_pool *pool);
व्योम xsk_clear_rx_need_wakeup(काष्ठा xsk_buff_pool *pool);
व्योम xsk_clear_tx_need_wakeup(काष्ठा xsk_buff_pool *pool);
bool xsk_uses_need_wakeup(काष्ठा xsk_buff_pool *pool);

अटल अंतरभूत u32 xsk_pool_get_headroom(काष्ठा xsk_buff_pool *pool)
अणु
	वापस XDP_PACKET_HEADROOM + pool->headroom;
पूर्ण

अटल अंतरभूत u32 xsk_pool_get_chunk_size(काष्ठा xsk_buff_pool *pool)
अणु
	वापस pool->chunk_size;
पूर्ण

अटल अंतरभूत u32 xsk_pool_get_rx_frame_size(काष्ठा xsk_buff_pool *pool)
अणु
	वापस xsk_pool_get_chunk_size(pool) - xsk_pool_get_headroom(pool);
पूर्ण

अटल अंतरभूत व्योम xsk_pool_set_rxq_info(काष्ठा xsk_buff_pool *pool,
					 काष्ठा xdp_rxq_info *rxq)
अणु
	xp_set_rxq_info(pool, rxq);
पूर्ण

अटल अंतरभूत व्योम xsk_pool_dma_unmap(काष्ठा xsk_buff_pool *pool,
				      अचिन्हित दीर्घ attrs)
अणु
	xp_dma_unmap(pool, attrs);
पूर्ण

अटल अंतरभूत पूर्णांक xsk_pool_dma_map(काष्ठा xsk_buff_pool *pool,
				   काष्ठा device *dev, अचिन्हित दीर्घ attrs)
अणु
	काष्ठा xdp_umem *umem = pool->umem;

	वापस xp_dma_map(pool, dev, attrs, umem->pgs, umem->npgs);
पूर्ण

अटल अंतरभूत dma_addr_t xsk_buff_xdp_get_dma(काष्ठा xdp_buff *xdp)
अणु
	काष्ठा xdp_buff_xsk *xskb = container_of(xdp, काष्ठा xdp_buff_xsk, xdp);

	वापस xp_get_dma(xskb);
पूर्ण

अटल अंतरभूत dma_addr_t xsk_buff_xdp_get_frame_dma(काष्ठा xdp_buff *xdp)
अणु
	काष्ठा xdp_buff_xsk *xskb = container_of(xdp, काष्ठा xdp_buff_xsk, xdp);

	वापस xp_get_frame_dma(xskb);
पूर्ण

अटल अंतरभूत काष्ठा xdp_buff *xsk_buff_alloc(काष्ठा xsk_buff_pool *pool)
अणु
	वापस xp_alloc(pool);
पूर्ण

अटल अंतरभूत bool xsk_buff_can_alloc(काष्ठा xsk_buff_pool *pool, u32 count)
अणु
	वापस xp_can_alloc(pool, count);
पूर्ण

अटल अंतरभूत व्योम xsk_buff_मुक्त(काष्ठा xdp_buff *xdp)
अणु
	काष्ठा xdp_buff_xsk *xskb = container_of(xdp, काष्ठा xdp_buff_xsk, xdp);

	xp_मुक्त(xskb);
पूर्ण

अटल अंतरभूत dma_addr_t xsk_buff_raw_get_dma(काष्ठा xsk_buff_pool *pool,
					      u64 addr)
अणु
	वापस xp_raw_get_dma(pool, addr);
पूर्ण

अटल अंतरभूत व्योम *xsk_buff_raw_get_data(काष्ठा xsk_buff_pool *pool, u64 addr)
अणु
	वापस xp_raw_get_data(pool, addr);
पूर्ण

अटल अंतरभूत व्योम xsk_buff_dma_sync_क्रम_cpu(काष्ठा xdp_buff *xdp, काष्ठा xsk_buff_pool *pool)
अणु
	काष्ठा xdp_buff_xsk *xskb = container_of(xdp, काष्ठा xdp_buff_xsk, xdp);

	अगर (!pool->dma_need_sync)
		वापस;

	xp_dma_sync_क्रम_cpu(xskb);
पूर्ण

अटल अंतरभूत व्योम xsk_buff_raw_dma_sync_क्रम_device(काष्ठा xsk_buff_pool *pool,
						    dma_addr_t dma,
						    माप_प्रकार size)
अणु
	xp_dma_sync_क्रम_device(pool, dma, size);
पूर्ण

#अन्यथा

अटल अंतरभूत व्योम xsk_tx_completed(काष्ठा xsk_buff_pool *pool, u32 nb_entries)
अणु
पूर्ण

अटल अंतरभूत bool xsk_tx_peek_desc(काष्ठा xsk_buff_pool *pool,
				    काष्ठा xdp_desc *desc)
अणु
	वापस false;
पूर्ण

अटल अंतरभूत u32 xsk_tx_peek_release_desc_batch(काष्ठा xsk_buff_pool *pool, काष्ठा xdp_desc *desc,
						 u32 max)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत व्योम xsk_tx_release(काष्ठा xsk_buff_pool *pool)
अणु
पूर्ण

अटल अंतरभूत काष्ठा xsk_buff_pool *
xsk_get_pool_from_qid(काष्ठा net_device *dev, u16 queue_id)
अणु
	वापस शून्य;
पूर्ण

अटल अंतरभूत व्योम xsk_set_rx_need_wakeup(काष्ठा xsk_buff_pool *pool)
अणु
पूर्ण

अटल अंतरभूत व्योम xsk_set_tx_need_wakeup(काष्ठा xsk_buff_pool *pool)
अणु
पूर्ण

अटल अंतरभूत व्योम xsk_clear_rx_need_wakeup(काष्ठा xsk_buff_pool *pool)
अणु
पूर्ण

अटल अंतरभूत व्योम xsk_clear_tx_need_wakeup(काष्ठा xsk_buff_pool *pool)
अणु
पूर्ण

अटल अंतरभूत bool xsk_uses_need_wakeup(काष्ठा xsk_buff_pool *pool)
अणु
	वापस false;
पूर्ण

अटल अंतरभूत u32 xsk_pool_get_headroom(काष्ठा xsk_buff_pool *pool)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत u32 xsk_pool_get_chunk_size(काष्ठा xsk_buff_pool *pool)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत u32 xsk_pool_get_rx_frame_size(काष्ठा xsk_buff_pool *pool)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत व्योम xsk_pool_set_rxq_info(काष्ठा xsk_buff_pool *pool,
					 काष्ठा xdp_rxq_info *rxq)
अणु
पूर्ण

अटल अंतरभूत व्योम xsk_pool_dma_unmap(काष्ठा xsk_buff_pool *pool,
				      अचिन्हित दीर्घ attrs)
अणु
पूर्ण

अटल अंतरभूत पूर्णांक xsk_pool_dma_map(काष्ठा xsk_buff_pool *pool,
				   काष्ठा device *dev, अचिन्हित दीर्घ attrs)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत dma_addr_t xsk_buff_xdp_get_dma(काष्ठा xdp_buff *xdp)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत dma_addr_t xsk_buff_xdp_get_frame_dma(काष्ठा xdp_buff *xdp)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत काष्ठा xdp_buff *xsk_buff_alloc(काष्ठा xsk_buff_pool *pool)
अणु
	वापस शून्य;
पूर्ण

अटल अंतरभूत bool xsk_buff_can_alloc(काष्ठा xsk_buff_pool *pool, u32 count)
अणु
	वापस false;
पूर्ण

अटल अंतरभूत व्योम xsk_buff_मुक्त(काष्ठा xdp_buff *xdp)
अणु
पूर्ण

अटल अंतरभूत dma_addr_t xsk_buff_raw_get_dma(काष्ठा xsk_buff_pool *pool,
					      u64 addr)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत व्योम *xsk_buff_raw_get_data(काष्ठा xsk_buff_pool *pool, u64 addr)
अणु
	वापस शून्य;
पूर्ण

अटल अंतरभूत व्योम xsk_buff_dma_sync_क्रम_cpu(काष्ठा xdp_buff *xdp, काष्ठा xsk_buff_pool *pool)
अणु
पूर्ण

अटल अंतरभूत व्योम xsk_buff_raw_dma_sync_क्रम_device(काष्ठा xsk_buff_pool *pool,
						    dma_addr_t dma,
						    माप_प्रकार size)
अणु
पूर्ण

#पूर्ण_अगर /* CONFIG_XDP_SOCKETS */

#पूर्ण_अगर /* _LINUX_XDP_SOCK_DRV_H */
