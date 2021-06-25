<शैली गुरु>
/*
 * Copyright (c) 2015, Mellanox Technologies. All rights reserved.
 *
 * This software is available to you under a choice of one of two
 * licenses.  You may choose to be licensed under the terms of the GNU
 * General Public License (GPL) Version 2, available from the file
 * COPYING in the मुख्य directory of this source tree, or the
 * OpenIB.org BSD license below:
 *
 *     Redistribution and use in source and binary क्रमms, with or
 *     without modअगरication, are permitted provided that the following
 *     conditions are met:
 *
 *      - Redistributions of source code must retain the above
 *        copyright notice, this list of conditions and the following
 *        disclaimer.
 *
 *      - Redistributions in binary क्रमm must reproduce the above
 *        copyright notice, this list of conditions and the following
 *        disclaimer in the करोcumentation and/or other materials
 *        provided with the distribution.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS
 * BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN
 * ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#समावेश <linux/ip.h>
#समावेश <linux/ipv6.h>
#समावेश <linux/tcp.h>
#समावेश <net/ip6_checksum.h>
#समावेश <net/page_pool.h>
#समावेश <net/inet_ecn.h>
#समावेश "en.h"
#समावेश "en/txrx.h"
#समावेश "en_tc.h"
#समावेश "eswitch.h"
#समावेश "en_rep.h"
#समावेश "en/rep/tc.h"
#समावेश "ipoib/ipoib.h"
#समावेश "accel/ipsec.h"
#समावेश "fpga/ipsec.h"
#समावेश "en_accel/ipsec_rxtx.h"
#समावेश "en_accel/tls_rxtx.h"
#समावेश "en/xdp.h"
#समावेश "en/xsk/rx.h"
#समावेश "en/health.h"
#समावेश "en/params.h"
#समावेश "devlink.h"
#समावेश "en/devlink.h"

अटल काष्ठा sk_buff *
mlx5e_skb_from_cqe_mpwrq_linear(काष्ठा mlx5e_rq *rq, काष्ठा mlx5e_mpw_info *wi,
				u16 cqe_bcnt, u32 head_offset, u32 page_idx);
अटल काष्ठा sk_buff *
mlx5e_skb_from_cqe_mpwrq_nonlinear(काष्ठा mlx5e_rq *rq, काष्ठा mlx5e_mpw_info *wi,
				   u16 cqe_bcnt, u32 head_offset, u32 page_idx);
अटल व्योम mlx5e_handle_rx_cqe(काष्ठा mlx5e_rq *rq, काष्ठा mlx5_cqe64 *cqe);
अटल व्योम mlx5e_handle_rx_cqe_mpwrq(काष्ठा mlx5e_rq *rq, काष्ठा mlx5_cqe64 *cqe);

स्थिर काष्ठा mlx5e_rx_handlers mlx5e_rx_handlers_nic = अणु
	.handle_rx_cqe       = mlx5e_handle_rx_cqe,
	.handle_rx_cqe_mpwqe = mlx5e_handle_rx_cqe_mpwrq,
पूर्ण;

अटल अंतरभूत bool mlx5e_rx_hw_stamp(काष्ठा hwtstamp_config *config)
अणु
	वापस config->rx_filter == HWTSTAMP_FILTER_ALL;
पूर्ण

अटल अंतरभूत व्योम mlx5e_पढ़ो_cqe_slot(काष्ठा mlx5_cqwq *wq,
				       u32 cqcc, व्योम *data)
अणु
	u32 ci = mlx5_cqwq_ctr2ix(wq, cqcc);

	स_नकल(data, mlx5_cqwq_get_wqe(wq, ci), माप(काष्ठा mlx5_cqe64));
पूर्ण

अटल अंतरभूत व्योम mlx5e_पढ़ो_title_slot(काष्ठा mlx5e_rq *rq,
					 काष्ठा mlx5_cqwq *wq,
					 u32 cqcc)
अणु
	काष्ठा mlx5e_cq_decomp *cqd = &rq->cqd;
	काष्ठा mlx5_cqe64 *title = &cqd->title;

	mlx5e_पढ़ो_cqe_slot(wq, cqcc, title);
	cqd->left        = be32_to_cpu(title->byte_cnt);
	cqd->wqe_counter = be16_to_cpu(title->wqe_counter);
	rq->stats->cqe_compress_blks++;
पूर्ण

अटल अंतरभूत व्योम mlx5e_पढ़ो_mini_arr_slot(काष्ठा mlx5_cqwq *wq,
					    काष्ठा mlx5e_cq_decomp *cqd,
					    u32 cqcc)
अणु
	mlx5e_पढ़ो_cqe_slot(wq, cqcc, cqd->mini_arr);
	cqd->mini_arr_idx = 0;
पूर्ण

अटल अंतरभूत व्योम mlx5e_cqes_update_owner(काष्ठा mlx5_cqwq *wq, पूर्णांक n)
अणु
	u32 cqcc   = wq->cc;
	u8  op_own = mlx5_cqwq_get_ctr_wrap_cnt(wq, cqcc) & 1;
	u32 ci     = mlx5_cqwq_ctr2ix(wq, cqcc);
	u32 wq_sz  = mlx5_cqwq_get_size(wq);
	u32 ci_top = min_t(u32, wq_sz, ci + n);

	क्रम (; ci < ci_top; ci++, n--) अणु
		काष्ठा mlx5_cqe64 *cqe = mlx5_cqwq_get_wqe(wq, ci);

		cqe->op_own = op_own;
	पूर्ण

	अगर (unlikely(ci == wq_sz)) अणु
		op_own = !op_own;
		क्रम (ci = 0; ci < n; ci++) अणु
			काष्ठा mlx5_cqe64 *cqe = mlx5_cqwq_get_wqe(wq, ci);

			cqe->op_own = op_own;
		पूर्ण
	पूर्ण
पूर्ण

अटल अंतरभूत व्योम mlx5e_decompress_cqe(काष्ठा mlx5e_rq *rq,
					काष्ठा mlx5_cqwq *wq,
					u32 cqcc)
अणु
	काष्ठा mlx5e_cq_decomp *cqd = &rq->cqd;
	काष्ठा mlx5_mini_cqe8 *mini_cqe = &cqd->mini_arr[cqd->mini_arr_idx];
	काष्ठा mlx5_cqe64 *title = &cqd->title;

	title->byte_cnt     = mini_cqe->byte_cnt;
	title->check_sum    = mini_cqe->checksum;
	title->op_own      &= 0xf0;
	title->op_own      |= 0x01 & (cqcc >> wq->fbc.log_sz);

	/* state bit set implies linked-list striding RQ wq type and
	 * HW stride index capability supported
	 */
	अगर (test_bit(MLX5E_RQ_STATE_MINI_CQE_HW_STRIDX, &rq->state)) अणु
		title->wqe_counter = mini_cqe->stridx;
		वापस;
	पूर्ण

	/* HW stride index capability not supported */
	title->wqe_counter = cpu_to_be16(cqd->wqe_counter);
	अगर (rq->wq_type == MLX5_WQ_TYPE_LINKED_LIST_STRIDING_RQ)
		cqd->wqe_counter += mpwrq_get_cqe_consumed_strides(title);
	अन्यथा
		cqd->wqe_counter =
			mlx5_wq_cyc_ctr2ix(&rq->wqe.wq, cqd->wqe_counter + 1);
पूर्ण

अटल अंतरभूत व्योम mlx5e_decompress_cqe_no_hash(काष्ठा mlx5e_rq *rq,
						काष्ठा mlx5_cqwq *wq,
						u32 cqcc)
अणु
	काष्ठा mlx5e_cq_decomp *cqd = &rq->cqd;

	mlx5e_decompress_cqe(rq, wq, cqcc);
	cqd->title.rss_hash_type   = 0;
	cqd->title.rss_hash_result = 0;
पूर्ण

अटल अंतरभूत u32 mlx5e_decompress_cqes_cont(काष्ठा mlx5e_rq *rq,
					     काष्ठा mlx5_cqwq *wq,
					     पूर्णांक update_owner_only,
					     पूर्णांक budget_rem)
अणु
	काष्ठा mlx5e_cq_decomp *cqd = &rq->cqd;
	u32 cqcc = wq->cc + update_owner_only;
	u32 cqe_count;
	u32 i;

	cqe_count = min_t(u32, cqd->left, budget_rem);

	क्रम (i = update_owner_only; i < cqe_count;
	     i++, cqd->mini_arr_idx++, cqcc++) अणु
		अगर (cqd->mini_arr_idx == MLX5_MINI_CQE_ARRAY_SIZE)
			mlx5e_पढ़ो_mini_arr_slot(wq, cqd, cqcc);

		mlx5e_decompress_cqe_no_hash(rq, wq, cqcc);
		INसूचीECT_CALL_2(rq->handle_rx_cqe, mlx5e_handle_rx_cqe_mpwrq,
				mlx5e_handle_rx_cqe, rq, &cqd->title);
	पूर्ण
	mlx5e_cqes_update_owner(wq, cqcc - wq->cc);
	wq->cc = cqcc;
	cqd->left -= cqe_count;
	rq->stats->cqe_compress_pkts += cqe_count;

	वापस cqe_count;
पूर्ण

अटल अंतरभूत u32 mlx5e_decompress_cqes_start(काष्ठा mlx5e_rq *rq,
					      काष्ठा mlx5_cqwq *wq,
					      पूर्णांक budget_rem)
अणु
	काष्ठा mlx5e_cq_decomp *cqd = &rq->cqd;
	u32 cc = wq->cc;

	mlx5e_पढ़ो_title_slot(rq, wq, cc);
	mlx5e_पढ़ो_mini_arr_slot(wq, cqd, cc + 1);
	mlx5e_decompress_cqe(rq, wq, cc);
	INसूचीECT_CALL_2(rq->handle_rx_cqe, mlx5e_handle_rx_cqe_mpwrq,
			mlx5e_handle_rx_cqe, rq, &cqd->title);
	cqd->mini_arr_idx++;

	वापस mlx5e_decompress_cqes_cont(rq, wq, 1, budget_rem) - 1;
पूर्ण

अटल अंतरभूत bool mlx5e_rx_cache_put(काष्ठा mlx5e_rq *rq,
				      काष्ठा mlx5e_dma_info *dma_info)
अणु
	काष्ठा mlx5e_page_cache *cache = &rq->page_cache;
	u32 tail_next = (cache->tail + 1) & (MLX5E_CACHE_SIZE - 1);
	काष्ठा mlx5e_rq_stats *stats = rq->stats;

	अगर (tail_next == cache->head) अणु
		stats->cache_full++;
		वापस false;
	पूर्ण

	अगर (!dev_page_is_reusable(dma_info->page)) अणु
		stats->cache_waive++;
		वापस false;
	पूर्ण

	cache->page_cache[cache->tail] = *dma_info;
	cache->tail = tail_next;
	वापस true;
पूर्ण

अटल अंतरभूत bool mlx5e_rx_cache_get(काष्ठा mlx5e_rq *rq,
				      काष्ठा mlx5e_dma_info *dma_info)
अणु
	काष्ठा mlx5e_page_cache *cache = &rq->page_cache;
	काष्ठा mlx5e_rq_stats *stats = rq->stats;

	अगर (unlikely(cache->head == cache->tail)) अणु
		stats->cache_empty++;
		वापस false;
	पूर्ण

	अगर (page_ref_count(cache->page_cache[cache->head].page) != 1) अणु
		stats->cache_busy++;
		वापस false;
	पूर्ण

	*dma_info = cache->page_cache[cache->head];
	cache->head = (cache->head + 1) & (MLX5E_CACHE_SIZE - 1);
	stats->cache_reuse++;

	dma_sync_single_क्रम_device(rq->pdev, dma_info->addr,
				   PAGE_SIZE,
				   DMA_FROM_DEVICE);
	वापस true;
पूर्ण

अटल अंतरभूत पूर्णांक mlx5e_page_alloc_pool(काष्ठा mlx5e_rq *rq,
					काष्ठा mlx5e_dma_info *dma_info)
अणु
	अगर (mlx5e_rx_cache_get(rq, dma_info))
		वापस 0;

	dma_info->page = page_pool_dev_alloc_pages(rq->page_pool);
	अगर (unlikely(!dma_info->page))
		वापस -ENOMEM;

	dma_info->addr = dma_map_page(rq->pdev, dma_info->page, 0,
				      PAGE_SIZE, rq->buff.map_dir);
	अगर (unlikely(dma_mapping_error(rq->pdev, dma_info->addr))) अणु
		page_pool_recycle_direct(rq->page_pool, dma_info->page);
		dma_info->page = शून्य;
		वापस -ENOMEM;
	पूर्ण

	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक mlx5e_page_alloc(काष्ठा mlx5e_rq *rq,
				   काष्ठा mlx5e_dma_info *dma_info)
अणु
	अगर (rq->xsk_pool)
		वापस mlx5e_xsk_page_alloc_pool(rq, dma_info);
	अन्यथा
		वापस mlx5e_page_alloc_pool(rq, dma_info);
पूर्ण

व्योम mlx5e_page_dma_unmap(काष्ठा mlx5e_rq *rq, काष्ठा mlx5e_dma_info *dma_info)
अणु
	dma_unmap_page(rq->pdev, dma_info->addr, PAGE_SIZE, rq->buff.map_dir);
पूर्ण

व्योम mlx5e_page_release_dynamic(काष्ठा mlx5e_rq *rq,
				काष्ठा mlx5e_dma_info *dma_info,
				bool recycle)
अणु
	अगर (likely(recycle)) अणु
		अगर (mlx5e_rx_cache_put(rq, dma_info))
			वापस;

		mlx5e_page_dma_unmap(rq, dma_info);
		page_pool_recycle_direct(rq->page_pool, dma_info->page);
	पूर्ण अन्यथा अणु
		mlx5e_page_dma_unmap(rq, dma_info);
		page_pool_release_page(rq->page_pool, dma_info->page);
		put_page(dma_info->page);
	पूर्ण
पूर्ण

अटल अंतरभूत व्योम mlx5e_page_release(काष्ठा mlx5e_rq *rq,
				      काष्ठा mlx5e_dma_info *dma_info,
				      bool recycle)
अणु
	अगर (rq->xsk_pool)
		/* The `recycle` parameter is ignored, and the page is always
		 * put पूर्णांकo the Reuse Ring, because there is no way to वापस
		 * the page to the userspace when the पूर्णांकerface goes करोwn.
		 */
		xsk_buff_मुक्त(dma_info->xsk);
	अन्यथा
		mlx5e_page_release_dynamic(rq, dma_info, recycle);
पूर्ण

अटल अंतरभूत पूर्णांक mlx5e_get_rx_frag(काष्ठा mlx5e_rq *rq,
				    काष्ठा mlx5e_wqe_frag_info *frag)
अणु
	पूर्णांक err = 0;

	अगर (!frag->offset)
		/* On first frag (offset == 0), replenish page (dma_info actually).
		 * Other frags that poपूर्णांक to the same dma_info (with a dअगरferent
		 * offset) should just use the new one without replenishing again
		 * by themselves.
		 */
		err = mlx5e_page_alloc(rq, frag->di);

	वापस err;
पूर्ण

अटल अंतरभूत व्योम mlx5e_put_rx_frag(काष्ठा mlx5e_rq *rq,
				     काष्ठा mlx5e_wqe_frag_info *frag,
				     bool recycle)
अणु
	अगर (frag->last_in_page)
		mlx5e_page_release(rq, frag->di, recycle);
पूर्ण

अटल अंतरभूत काष्ठा mlx5e_wqe_frag_info *get_frag(काष्ठा mlx5e_rq *rq, u16 ix)
अणु
	वापस &rq->wqe.frags[ix << rq->wqe.info.log_num_frags];
पूर्ण

अटल पूर्णांक mlx5e_alloc_rx_wqe(काष्ठा mlx5e_rq *rq, काष्ठा mlx5e_rx_wqe_cyc *wqe,
			      u16 ix)
अणु
	काष्ठा mlx5e_wqe_frag_info *frag = get_frag(rq, ix);
	पूर्णांक err;
	पूर्णांक i;

	क्रम (i = 0; i < rq->wqe.info.num_frags; i++, frag++) अणु
		err = mlx5e_get_rx_frag(rq, frag);
		अगर (unlikely(err))
			जाओ मुक्त_frags;

		wqe->data[i].addr = cpu_to_be64(frag->di->addr +
						frag->offset + rq->buff.headroom);
	पूर्ण

	वापस 0;

मुक्त_frags:
	जबतक (--i >= 0)
		mlx5e_put_rx_frag(rq, --frag, true);

	वापस err;
पूर्ण

अटल अंतरभूत व्योम mlx5e_मुक्त_rx_wqe(काष्ठा mlx5e_rq *rq,
				     काष्ठा mlx5e_wqe_frag_info *wi,
				     bool recycle)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < rq->wqe.info.num_frags; i++, wi++)
		mlx5e_put_rx_frag(rq, wi, recycle);
पूर्ण

अटल व्योम mlx5e_dealloc_rx_wqe(काष्ठा mlx5e_rq *rq, u16 ix)
अणु
	काष्ठा mlx5e_wqe_frag_info *wi = get_frag(rq, ix);

	mlx5e_मुक्त_rx_wqe(rq, wi, false);
पूर्ण

अटल पूर्णांक mlx5e_alloc_rx_wqes(काष्ठा mlx5e_rq *rq, u16 ix, u8 wqe_bulk)
अणु
	काष्ठा mlx5_wq_cyc *wq = &rq->wqe.wq;
	पूर्णांक err;
	पूर्णांक i;

	अगर (rq->xsk_pool) अणु
		पूर्णांक pages_desired = wqe_bulk << rq->wqe.info.log_num_frags;

		/* Check in advance that we have enough frames, instead of
		 * allocating one-by-one, failing and moving frames to the
		 * Reuse Ring.
		 */
		अगर (unlikely(!xsk_buff_can_alloc(rq->xsk_pool, pages_desired)))
			वापस -ENOMEM;
	पूर्ण

	क्रम (i = 0; i < wqe_bulk; i++) अणु
		काष्ठा mlx5e_rx_wqe_cyc *wqe = mlx5_wq_cyc_get_wqe(wq, ix + i);

		err = mlx5e_alloc_rx_wqe(rq, wqe, ix + i);
		अगर (unlikely(err))
			जाओ मुक्त_wqes;
	पूर्ण

	वापस 0;

मुक्त_wqes:
	जबतक (--i >= 0)
		mlx5e_dealloc_rx_wqe(rq, ix + i);

	वापस err;
पूर्ण

अटल अंतरभूत व्योम
mlx5e_add_skb_frag(काष्ठा mlx5e_rq *rq, काष्ठा sk_buff *skb,
		   काष्ठा mlx5e_dma_info *di, u32 frag_offset, u32 len,
		   अचिन्हित पूर्णांक truesize)
अणु
	dma_sync_single_क्रम_cpu(rq->pdev,
				di->addr + frag_offset,
				len, DMA_FROM_DEVICE);
	page_ref_inc(di->page);
	skb_add_rx_frag(skb, skb_shinfo(skb)->nr_frags,
			di->page, frag_offset, len, truesize);
पूर्ण

अटल अंतरभूत व्योम
mlx5e_copy_skb_header(काष्ठा device *pdev, काष्ठा sk_buff *skb,
		      काष्ठा mlx5e_dma_info *dma_info,
		      पूर्णांक offset_from, u32 headlen)
अणु
	स्थिर व्योम *from = page_address(dma_info->page) + offset_from;
	/* Aligning len to माप(दीर्घ) optimizes स_नकल perक्रमmance */
	अचिन्हित पूर्णांक len = ALIGN(headlen, माप(दीर्घ));

	dma_sync_single_क्रम_cpu(pdev, dma_info->addr + offset_from, len,
				DMA_FROM_DEVICE);
	skb_copy_to_linear_data(skb, from, len);
पूर्ण

अटल व्योम
mlx5e_मुक्त_rx_mpwqe(काष्ठा mlx5e_rq *rq, काष्ठा mlx5e_mpw_info *wi, bool recycle)
अणु
	bool no_xdp_xmit;
	काष्ठा mlx5e_dma_info *dma_info = wi->umr.dma_info;
	पूर्णांक i;

	/* A common हाल क्रम AF_XDP. */
	अगर (biपंचांगap_full(wi->xdp_xmit_biपंचांगap, MLX5_MPWRQ_PAGES_PER_WQE))
		वापस;

	no_xdp_xmit = biपंचांगap_empty(wi->xdp_xmit_biपंचांगap,
				   MLX5_MPWRQ_PAGES_PER_WQE);

	क्रम (i = 0; i < MLX5_MPWRQ_PAGES_PER_WQE; i++)
		अगर (no_xdp_xmit || !test_bit(i, wi->xdp_xmit_biपंचांगap))
			mlx5e_page_release(rq, &dma_info[i], recycle);
पूर्ण

अटल व्योम mlx5e_post_rx_mpwqe(काष्ठा mlx5e_rq *rq, u8 n)
अणु
	काष्ठा mlx5_wq_ll *wq = &rq->mpwqe.wq;

	करो अणु
		u16 next_wqe_index = mlx5_wq_ll_get_wqe_next_ix(wq, wq->head);

		mlx5_wq_ll_push(wq, next_wqe_index);
	पूर्ण जबतक (--n);

	/* ensure wqes are visible to device beक्रमe updating करोorbell record */
	dma_wmb();

	mlx5_wq_ll_update_db_record(wq);
पूर्ण

अटल पूर्णांक mlx5e_alloc_rx_mpwqe(काष्ठा mlx5e_rq *rq, u16 ix)
अणु
	काष्ठा mlx5e_mpw_info *wi = &rq->mpwqe.info[ix];
	काष्ठा mlx5e_dma_info *dma_info = &wi->umr.dma_info[0];
	काष्ठा mlx5e_icosq *sq = rq->icosq;
	काष्ठा mlx5_wq_cyc *wq = &sq->wq;
	काष्ठा mlx5e_umr_wqe *umr_wqe;
	u16 pi;
	पूर्णांक err;
	पूर्णांक i;

	/* Check in advance that we have enough frames, instead of allocating
	 * one-by-one, failing and moving frames to the Reuse Ring.
	 */
	अगर (rq->xsk_pool &&
	    unlikely(!xsk_buff_can_alloc(rq->xsk_pool, MLX5_MPWRQ_PAGES_PER_WQE))) अणु
		err = -ENOMEM;
		जाओ err;
	पूर्ण

	pi = mlx5e_icosq_get_next_pi(sq, MLX5E_UMR_WQEBBS);
	umr_wqe = mlx5_wq_cyc_get_wqe(wq, pi);
	स_नकल(umr_wqe, &rq->mpwqe.umr_wqe, दुरत्व(काष्ठा mlx5e_umr_wqe, अंतरभूत_mtts));

	क्रम (i = 0; i < MLX5_MPWRQ_PAGES_PER_WQE; i++, dma_info++) अणु
		err = mlx5e_page_alloc(rq, dma_info);
		अगर (unlikely(err))
			जाओ err_unmap;
		umr_wqe->अंतरभूत_mtts[i].ptag = cpu_to_be64(dma_info->addr | MLX5_EN_WR);
	पूर्ण

	biपंचांगap_zero(wi->xdp_xmit_biपंचांगap, MLX5_MPWRQ_PAGES_PER_WQE);
	wi->consumed_strides = 0;

	umr_wqe->ctrl.opmod_idx_opcode =
		cpu_to_be32((sq->pc << MLX5_WQE_CTRL_WQE_INDEX_SHIFT) |
			    MLX5_OPCODE_UMR);
	umr_wqe->uctrl.xlt_offset =
		cpu_to_be16(MLX5_ALIGNED_MTTS_OCTW(MLX5E_REQUIRED_MTTS(ix)));

	sq->db.wqe_info[pi] = (काष्ठा mlx5e_icosq_wqe_info) अणु
		.wqe_type   = MLX5E_ICOSQ_WQE_UMR_RX,
		.num_wqebbs = MLX5E_UMR_WQEBBS,
		.umr.rq     = rq,
	पूर्ण;

	sq->pc += MLX5E_UMR_WQEBBS;

	sq->करोorbell_cseg = &umr_wqe->ctrl;

	वापस 0;

err_unmap:
	जबतक (--i >= 0) अणु
		dma_info--;
		mlx5e_page_release(rq, dma_info, true);
	पूर्ण

err:
	rq->stats->buff_alloc_err++;

	वापस err;
पूर्ण

अटल व्योम mlx5e_dealloc_rx_mpwqe(काष्ठा mlx5e_rq *rq, u16 ix)
अणु
	काष्ठा mlx5e_mpw_info *wi = &rq->mpwqe.info[ix];
	/* Don't recycle, this function is called on rq/netdev बंद */
	mlx5e_मुक्त_rx_mpwqe(rq, wi, false);
पूर्ण

INसूचीECT_CALLABLE_SCOPE bool mlx5e_post_rx_wqes(काष्ठा mlx5e_rq *rq)
अणु
	काष्ठा mlx5_wq_cyc *wq = &rq->wqe.wq;
	u8 wqe_bulk;
	पूर्णांक err;

	अगर (unlikely(!test_bit(MLX5E_RQ_STATE_ENABLED, &rq->state)))
		वापस false;

	wqe_bulk = rq->wqe.info.wqe_bulk;

	अगर (mlx5_wq_cyc_missing(wq) < wqe_bulk)
		वापस false;

	करो अणु
		u16 head = mlx5_wq_cyc_get_head(wq);

		err = mlx5e_alloc_rx_wqes(rq, head, wqe_bulk);
		अगर (unlikely(err)) अणु
			rq->stats->buff_alloc_err++;
			अवरोध;
		पूर्ण

		mlx5_wq_cyc_push_n(wq, wqe_bulk);
	पूर्ण जबतक (mlx5_wq_cyc_missing(wq) >= wqe_bulk);

	/* ensure wqes are visible to device beक्रमe updating करोorbell record */
	dma_wmb();

	mlx5_wq_cyc_update_db_record(wq);

	वापस !!err;
पूर्ण

व्योम mlx5e_मुक्त_icosq_descs(काष्ठा mlx5e_icosq *sq)
अणु
	u16 sqcc;

	sqcc = sq->cc;

	जबतक (sqcc != sq->pc) अणु
		काष्ठा mlx5e_icosq_wqe_info *wi;
		u16 ci;

		ci = mlx5_wq_cyc_ctr2ix(&sq->wq, sqcc);
		wi = &sq->db.wqe_info[ci];
		sqcc += wi->num_wqebbs;
#अगर_घोषित CONFIG_MLX5_EN_TLS
		चयन (wi->wqe_type) अणु
		हाल MLX5E_ICOSQ_WQE_SET_PSV_TLS:
			mlx5e_ktls_handle_ctx_completion(wi);
			अवरोध;
		हाल MLX5E_ICOSQ_WQE_GET_PSV_TLS:
			mlx5e_ktls_handle_get_psv_completion(wi, sq);
			अवरोध;
		पूर्ण
#पूर्ण_अगर
	पूर्ण
	sq->cc = sqcc;
पूर्ण

पूर्णांक mlx5e_poll_ico_cq(काष्ठा mlx5e_cq *cq)
अणु
	काष्ठा mlx5e_icosq *sq = container_of(cq, काष्ठा mlx5e_icosq, cq);
	काष्ठा mlx5_cqe64 *cqe;
	u16 sqcc;
	पूर्णांक i;

	अगर (unlikely(!test_bit(MLX5E_SQ_STATE_ENABLED, &sq->state)))
		वापस 0;

	cqe = mlx5_cqwq_get_cqe(&cq->wq);
	अगर (likely(!cqe))
		वापस 0;

	/* sq->cc must be updated only after mlx5_cqwq_update_db_record(),
	 * otherwise a cq overrun may occur
	 */
	sqcc = sq->cc;

	i = 0;
	करो अणु
		u16 wqe_counter;
		bool last_wqe;

		mlx5_cqwq_pop(&cq->wq);

		wqe_counter = be16_to_cpu(cqe->wqe_counter);

		करो अणु
			काष्ठा mlx5e_icosq_wqe_info *wi;
			u16 ci;

			last_wqe = (sqcc == wqe_counter);

			ci = mlx5_wq_cyc_ctr2ix(&sq->wq, sqcc);
			wi = &sq->db.wqe_info[ci];
			sqcc += wi->num_wqebbs;

			अगर (last_wqe && unlikely(get_cqe_opcode(cqe) != MLX5_CQE_REQ)) अणु
				netdev_WARN_ONCE(cq->netdev,
						 "Bad OP in ICOSQ CQE: 0x%x\n",
						 get_cqe_opcode(cqe));
				mlx5e_dump_error_cqe(&sq->cq, sq->sqn,
						     (काष्ठा mlx5_err_cqe *)cqe);
				mlx5_wq_cyc_wqe_dump(&sq->wq, ci, wi->num_wqebbs);
				अगर (!test_and_set_bit(MLX5E_SQ_STATE_RECOVERING, &sq->state))
					queue_work(cq->priv->wq, &sq->recover_work);
				अवरोध;
			पूर्ण

			चयन (wi->wqe_type) अणु
			हाल MLX5E_ICOSQ_WQE_UMR_RX:
				wi->umr.rq->mpwqe.umr_completed++;
				अवरोध;
			हाल MLX5E_ICOSQ_WQE_NOP:
				अवरोध;
#अगर_घोषित CONFIG_MLX5_EN_TLS
			हाल MLX5E_ICOSQ_WQE_UMR_TLS:
				अवरोध;
			हाल MLX5E_ICOSQ_WQE_SET_PSV_TLS:
				mlx5e_ktls_handle_ctx_completion(wi);
				अवरोध;
			हाल MLX5E_ICOSQ_WQE_GET_PSV_TLS:
				mlx5e_ktls_handle_get_psv_completion(wi, sq);
				अवरोध;
#पूर्ण_अगर
			शेष:
				netdev_WARN_ONCE(cq->netdev,
						 "Bad WQE type in ICOSQ WQE info: 0x%x\n",
						 wi->wqe_type);
			पूर्ण
		पूर्ण जबतक (!last_wqe);
	पूर्ण जबतक ((++i < MLX5E_TX_CQ_POLL_BUDGET) && (cqe = mlx5_cqwq_get_cqe(&cq->wq)));

	sq->cc = sqcc;

	mlx5_cqwq_update_db_record(&cq->wq);

	वापस i;
पूर्ण

INसूचीECT_CALLABLE_SCOPE bool mlx5e_post_rx_mpwqes(काष्ठा mlx5e_rq *rq)
अणु
	काष्ठा mlx5_wq_ll *wq = &rq->mpwqe.wq;
	u8  umr_completed = rq->mpwqe.umr_completed;
	काष्ठा mlx5e_icosq *sq = rq->icosq;
	पूर्णांक alloc_err = 0;
	u8  missing, i;
	u16 head;

	अगर (unlikely(!test_bit(MLX5E_RQ_STATE_ENABLED, &rq->state)))
		वापस false;

	अगर (umr_completed) अणु
		mlx5e_post_rx_mpwqe(rq, umr_completed);
		rq->mpwqe.umr_in_progress -= umr_completed;
		rq->mpwqe.umr_completed = 0;
	पूर्ण

	missing = mlx5_wq_ll_missing(wq) - rq->mpwqe.umr_in_progress;

	अगर (unlikely(rq->mpwqe.umr_in_progress > rq->mpwqe.umr_last_bulk))
		rq->stats->congst_umr++;

#घोषणा UMR_WQE_BULK (2)
	अगर (likely(missing < UMR_WQE_BULK))
		वापस false;

	head = rq->mpwqe.actual_wq_head;
	i = missing;
	करो अणु
		alloc_err = mlx5e_alloc_rx_mpwqe(rq, head);

		अगर (unlikely(alloc_err))
			अवरोध;
		head = mlx5_wq_ll_get_wqe_next_ix(wq, head);
	पूर्ण जबतक (--i);

	rq->mpwqe.umr_last_bulk    = missing - i;
	अगर (sq->करोorbell_cseg) अणु
		mlx5e_notअगरy_hw(&sq->wq, sq->pc, sq->uar_map, sq->करोorbell_cseg);
		sq->करोorbell_cseg = शून्य;
	पूर्ण

	rq->mpwqe.umr_in_progress += rq->mpwqe.umr_last_bulk;
	rq->mpwqe.actual_wq_head   = head;

	/* If XSK Fill Ring करोesn't have enough frames, report the error, so
	 * that one of the actions can be perक्रमmed:
	 * 1. If need_wakeup is used, संकेत that the application has to kick
	 * the driver when it refills the Fill Ring.
	 * 2. Otherwise, busy poll by rescheduling the NAPI poll.
	 */
	अगर (unlikely(alloc_err == -ENOMEM && rq->xsk_pool))
		वापस true;

	वापस false;
पूर्ण

अटल व्योम mlx5e_lro_update_tcp_hdr(काष्ठा mlx5_cqe64 *cqe, काष्ठा tcphdr *tcp)
अणु
	u8 l4_hdr_type = get_cqe_l4_hdr_type(cqe);
	u8 tcp_ack     = (l4_hdr_type == CQE_L4_HDR_TYPE_TCP_ACK_NO_DATA) ||
			 (l4_hdr_type == CQE_L4_HDR_TYPE_TCP_ACK_AND_DATA);

	tcp->check                      = 0;
	tcp->psh                        = get_cqe_lro_tcppsh(cqe);

	अगर (tcp_ack) अणु
		tcp->ack                = 1;
		tcp->ack_seq            = cqe->lro_ack_seq_num;
		tcp->winकरोw             = cqe->lro_tcp_win;
	पूर्ण
पूर्ण

अटल व्योम mlx5e_lro_update_hdr(काष्ठा sk_buff *skb, काष्ठा mlx5_cqe64 *cqe,
				 u32 cqe_bcnt)
अणु
	काष्ठा ethhdr	*eth = (काष्ठा ethhdr *)(skb->data);
	काष्ठा tcphdr	*tcp;
	पूर्णांक network_depth = 0;
	__wsum check;
	__be16 proto;
	u16 tot_len;
	व्योम *ip_p;

	proto = __vlan_get_protocol(skb, eth->h_proto, &network_depth);

	tot_len = cqe_bcnt - network_depth;
	ip_p = skb->data + network_depth;

	अगर (proto == htons(ETH_P_IP)) अणु
		काष्ठा iphdr *ipv4 = ip_p;

		tcp = ip_p + माप(काष्ठा iphdr);
		skb_shinfo(skb)->gso_type = SKB_GSO_TCPV4;

		ipv4->ttl               = cqe->lro_min_ttl;
		ipv4->tot_len           = cpu_to_be16(tot_len);
		ipv4->check             = 0;
		ipv4->check             = ip_fast_csum((अचिन्हित अक्षर *)ipv4,
						       ipv4->ihl);

		mlx5e_lro_update_tcp_hdr(cqe, tcp);
		check = csum_partial(tcp, tcp->करोff * 4,
				     csum_unfold((__क्रमce __sum16)cqe->check_sum));
		/* Almost करोne, करोn't क्रमget the pseuकरो header */
		tcp->check = csum_tcpudp_magic(ipv4->saddr, ipv4->daddr,
					       tot_len - माप(काष्ठा iphdr),
					       IPPROTO_TCP, check);
	पूर्ण अन्यथा अणु
		u16 payload_len = tot_len - माप(काष्ठा ipv6hdr);
		काष्ठा ipv6hdr *ipv6 = ip_p;

		tcp = ip_p + माप(काष्ठा ipv6hdr);
		skb_shinfo(skb)->gso_type = SKB_GSO_TCPV6;

		ipv6->hop_limit         = cqe->lro_min_ttl;
		ipv6->payload_len       = cpu_to_be16(payload_len);

		mlx5e_lro_update_tcp_hdr(cqe, tcp);
		check = csum_partial(tcp, tcp->करोff * 4,
				     csum_unfold((__क्रमce __sum16)cqe->check_sum));
		/* Almost करोne, करोn't क्रमget the pseuकरो header */
		tcp->check = csum_ipv6_magic(&ipv6->saddr, &ipv6->daddr, payload_len,
					     IPPROTO_TCP, check);
	पूर्ण
पूर्ण

अटल अंतरभूत व्योम mlx5e_skb_set_hash(काष्ठा mlx5_cqe64 *cqe,
				      काष्ठा sk_buff *skb)
अणु
	u8 cht = cqe->rss_hash_type;
	पूर्णांक ht = (cht & CQE_RSS_HTYPE_L4) ? PKT_HASH_TYPE_L4 :
		 (cht & CQE_RSS_HTYPE_IP) ? PKT_HASH_TYPE_L3 :
					    PKT_HASH_TYPE_NONE;
	skb_set_hash(skb, be32_to_cpu(cqe->rss_hash_result), ht);
पूर्ण

अटल अंतरभूत bool is_last_ethertype_ip(काष्ठा sk_buff *skb, पूर्णांक *network_depth,
					__be16 *proto)
अणु
	*proto = ((काष्ठा ethhdr *)skb->data)->h_proto;
	*proto = __vlan_get_protocol(skb, *proto, network_depth);

	अगर (*proto == htons(ETH_P_IP))
		वापस pskb_may_pull(skb, *network_depth + माप(काष्ठा iphdr));

	अगर (*proto == htons(ETH_P_IPV6))
		वापस pskb_may_pull(skb, *network_depth + माप(काष्ठा ipv6hdr));

	वापस false;
पूर्ण

अटल अंतरभूत व्योम mlx5e_enable_ecn(काष्ठा mlx5e_rq *rq, काष्ठा sk_buff *skb)
अणु
	पूर्णांक network_depth = 0;
	__be16 proto;
	व्योम *ip;
	पूर्णांक rc;

	अगर (unlikely(!is_last_ethertype_ip(skb, &network_depth, &proto)))
		वापस;

	ip = skb->data + network_depth;
	rc = ((proto == htons(ETH_P_IP)) ? IP_ECN_set_ce((काष्ठा iphdr *)ip) :
					 IP6_ECN_set_ce(skb, (काष्ठा ipv6hdr *)ip));

	rq->stats->ecn_mark += !!rc;
पूर्ण

अटल u8 get_ip_proto(काष्ठा sk_buff *skb, पूर्णांक network_depth, __be16 proto)
अणु
	व्योम *ip_p = skb->data + network_depth;

	वापस (proto == htons(ETH_P_IP)) ? ((काष्ठा iphdr *)ip_p)->protocol :
					    ((काष्ठा ipv6hdr *)ip_p)->nexthdr;
पूर्ण

#घोषणा लघु_frame(size) ((size) <= ETH_ZLEN + ETH_FCS_LEN)

#घोषणा MAX_PADDING 8

अटल व्योम
tail_padding_csum_slow(काष्ठा sk_buff *skb, पूर्णांक offset, पूर्णांक len,
		       काष्ठा mlx5e_rq_stats *stats)
अणु
	stats->csum_complete_tail_slow++;
	skb->csum = csum_block_add(skb->csum,
				   skb_checksum(skb, offset, len, 0),
				   offset);
पूर्ण

अटल व्योम
tail_padding_csum(काष्ठा sk_buff *skb, पूर्णांक offset,
		  काष्ठा mlx5e_rq_stats *stats)
अणु
	u8 tail_padding[MAX_PADDING];
	पूर्णांक len = skb->len - offset;
	व्योम *tail;

	अगर (unlikely(len > MAX_PADDING)) अणु
		tail_padding_csum_slow(skb, offset, len, stats);
		वापस;
	पूर्ण

	tail = skb_header_poपूर्णांकer(skb, offset, len, tail_padding);
	अगर (unlikely(!tail)) अणु
		tail_padding_csum_slow(skb, offset, len, stats);
		वापस;
	पूर्ण

	stats->csum_complete_tail++;
	skb->csum = csum_block_add(skb->csum, csum_partial(tail, len, 0), offset);
पूर्ण

अटल व्योम
mlx5e_skb_csum_fixup(काष्ठा sk_buff *skb, पूर्णांक network_depth, __be16 proto,
		     काष्ठा mlx5e_rq_stats *stats)
अणु
	काष्ठा ipv6hdr *ip6;
	काष्ठा iphdr   *ip4;
	पूर्णांक pkt_len;

	/* Fixup vlan headers, अगर any */
	अगर (network_depth > ETH_HLEN)
		/* CQE csum is calculated from the IP header and करोes
		 * not cover VLAN headers (अगर present). This will add
		 * the checksum manually.
		 */
		skb->csum = csum_partial(skb->data + ETH_HLEN,
					 network_depth - ETH_HLEN,
					 skb->csum);

	/* Fixup tail padding, अगर any */
	चयन (proto) अणु
	हाल htons(ETH_P_IP):
		ip4 = (काष्ठा iphdr *)(skb->data + network_depth);
		pkt_len = network_depth + ntohs(ip4->tot_len);
		अवरोध;
	हाल htons(ETH_P_IPV6):
		ip6 = (काष्ठा ipv6hdr *)(skb->data + network_depth);
		pkt_len = network_depth + माप(*ip6) + ntohs(ip6->payload_len);
		अवरोध;
	शेष:
		वापस;
	पूर्ण

	अगर (likely(pkt_len >= skb->len))
		वापस;

	tail_padding_csum(skb, pkt_len, stats);
पूर्ण

अटल अंतरभूत व्योम mlx5e_handle_csum(काष्ठा net_device *netdev,
				     काष्ठा mlx5_cqe64 *cqe,
				     काष्ठा mlx5e_rq *rq,
				     काष्ठा sk_buff *skb,
				     bool   lro)
अणु
	काष्ठा mlx5e_rq_stats *stats = rq->stats;
	पूर्णांक network_depth = 0;
	__be16 proto;

	अगर (unlikely(!(netdev->features & NETIF_F_RXCSUM)))
		जाओ csum_none;

	अगर (lro) अणु
		skb->ip_summed = CHECKSUM_UNNECESSARY;
		stats->csum_unnecessary++;
		वापस;
	पूर्ण

	/* True when explicitly set via priv flag, or XDP prog is loaded */
	अगर (test_bit(MLX5E_RQ_STATE_NO_CSUM_COMPLETE, &rq->state))
		जाओ csum_unnecessary;

	/* CQE csum करोesn't cover padding octets in लघु ethernet
	 * frames. And the pad field is appended prior to calculating
	 * and appending the FCS field.
	 *
	 * Detecting these padded frames requires to verअगरy and parse
	 * IP headers, so we simply क्रमce all those small frames to be
	 * CHECKSUM_UNNECESSARY even अगर they are not padded.
	 */
	अगर (लघु_frame(skb->len))
		जाओ csum_unnecessary;

	अगर (likely(is_last_ethertype_ip(skb, &network_depth, &proto))) अणु
		u8 ipproto = get_ip_proto(skb, network_depth, proto);

		अगर (unlikely(ipproto == IPPROTO_SCTP))
			जाओ csum_unnecessary;

		अगर (unlikely(mlx5_ipsec_is_rx_flow(cqe)))
			जाओ csum_none;

		stats->csum_complete++;
		skb->ip_summed = CHECKSUM_COMPLETE;
		skb->csum = csum_unfold((__क्रमce __sum16)cqe->check_sum);

		अगर (test_bit(MLX5E_RQ_STATE_CSUM_FULL, &rq->state))
			वापस; /* CQE csum covers all received bytes */

		/* csum might need some fixups ...*/
		mlx5e_skb_csum_fixup(skb, network_depth, proto, stats);
		वापस;
	पूर्ण

csum_unnecessary:
	अगर (likely((cqe->hds_ip_ext & CQE_L3_OK) &&
		   (cqe->hds_ip_ext & CQE_L4_OK))) अणु
		skb->ip_summed = CHECKSUM_UNNECESSARY;
		अगर (cqe_is_tunneled(cqe)) अणु
			skb->csum_level = 1;
			skb->encapsulation = 1;
			stats->csum_unnecessary_inner++;
			वापस;
		पूर्ण
		stats->csum_unnecessary++;
		वापस;
	पूर्ण
csum_none:
	skb->ip_summed = CHECKSUM_NONE;
	stats->csum_none++;
पूर्ण

#घोषणा MLX5E_CE_BIT_MASK 0x80

अटल अंतरभूत व्योम mlx5e_build_rx_skb(काष्ठा mlx5_cqe64 *cqe,
				      u32 cqe_bcnt,
				      काष्ठा mlx5e_rq *rq,
				      काष्ठा sk_buff *skb)
अणु
	u8 lro_num_seg = be32_to_cpu(cqe->srqn) >> 24;
	काष्ठा mlx5e_rq_stats *stats = rq->stats;
	काष्ठा net_device *netdev = rq->netdev;

	skb->mac_len = ETH_HLEN;

	mlx5e_tls_handle_rx_skb(rq, skb, cqe, &cqe_bcnt);

	अगर (unlikely(mlx5_ipsec_is_rx_flow(cqe)))
		mlx5e_ipsec_offload_handle_rx_skb(netdev, skb, cqe);

	अगर (lro_num_seg > 1) अणु
		mlx5e_lro_update_hdr(skb, cqe, cqe_bcnt);
		skb_shinfo(skb)->gso_size = DIV_ROUND_UP(cqe_bcnt, lro_num_seg);
		/* Subtract one since we alपढ़ोy counted this as one
		 * "regular" packet in mlx5e_complete_rx_cqe()
		 */
		stats->packets += lro_num_seg - 1;
		stats->lro_packets++;
		stats->lro_bytes += cqe_bcnt;
	पूर्ण

	अगर (unlikely(mlx5e_rx_hw_stamp(rq->tstamp)))
		skb_hwtstamps(skb)->hwtstamp = mlx5e_cqe_ts_to_ns(rq->ptp_cyc2समय,
								  rq->घड़ी, get_cqe_ts(cqe));
	skb_record_rx_queue(skb, rq->ix);

	अगर (likely(netdev->features & NETIF_F_RXHASH))
		mlx5e_skb_set_hash(cqe, skb);

	अगर (cqe_has_vlan(cqe)) अणु
		__vlan_hwaccel_put_tag(skb, htons(ETH_P_8021Q),
				       be16_to_cpu(cqe->vlan_info));
		stats->हटाओd_vlan_packets++;
	पूर्ण

	skb->mark = be32_to_cpu(cqe->sop_drop_qpn) & MLX5E_TC_FLOW_ID_MASK;

	mlx5e_handle_csum(netdev, cqe, rq, skb, !!lro_num_seg);
	/* checking CE bit in cqe - MSB in ml_path field */
	अगर (unlikely(cqe->ml_path & MLX5E_CE_BIT_MASK))
		mlx5e_enable_ecn(rq, skb);

	skb->protocol = eth_type_trans(skb, netdev);

	अगर (unlikely(mlx5e_skb_is_multicast(skb)))
		stats->mcast_packets++;
पूर्ण

अटल अंतरभूत व्योम mlx5e_complete_rx_cqe(काष्ठा mlx5e_rq *rq,
					 काष्ठा mlx5_cqe64 *cqe,
					 u32 cqe_bcnt,
					 काष्ठा sk_buff *skb)
अणु
	काष्ठा mlx5e_rq_stats *stats = rq->stats;

	stats->packets++;
	stats->bytes += cqe_bcnt;
	mlx5e_build_rx_skb(cqe, cqe_bcnt, rq, skb);
पूर्ण

अटल अंतरभूत
काष्ठा sk_buff *mlx5e_build_linear_skb(काष्ठा mlx5e_rq *rq, व्योम *va,
				       u32 frag_size, u16 headroom,
				       u32 cqe_bcnt)
अणु
	काष्ठा sk_buff *skb = build_skb(va, frag_size);

	अगर (unlikely(!skb)) अणु
		rq->stats->buff_alloc_err++;
		वापस शून्य;
	पूर्ण

	skb_reserve(skb, headroom);
	skb_put(skb, cqe_bcnt);

	वापस skb;
पूर्ण

अटल व्योम mlx5e_fill_xdp_buff(काष्ठा mlx5e_rq *rq, व्योम *va, u16 headroom,
				u32 len, काष्ठा xdp_buff *xdp)
अणु
	xdp_init_buff(xdp, rq->buff.frame0_sz, &rq->xdp_rxq);
	xdp_prepare_buff(xdp, va, headroom, len, false);
पूर्ण

अटल काष्ठा sk_buff *
mlx5e_skb_from_cqe_linear(काष्ठा mlx5e_rq *rq, काष्ठा mlx5_cqe64 *cqe,
			  काष्ठा mlx5e_wqe_frag_info *wi, u32 cqe_bcnt)
अणु
	काष्ठा mlx5e_dma_info *di = wi->di;
	u16 rx_headroom = rq->buff.headroom;
	काष्ठा xdp_buff xdp;
	काष्ठा sk_buff *skb;
	व्योम *va, *data;
	u32 frag_size;

	va             = page_address(di->page) + wi->offset;
	data           = va + rx_headroom;
	frag_size      = MLX5_SKB_FRAG_SZ(rx_headroom + cqe_bcnt);

	dma_sync_single_range_क्रम_cpu(rq->pdev, di->addr, wi->offset,
				      frag_size, DMA_FROM_DEVICE);
	net_prefetchw(va); /* xdp_frame data area */
	net_prefetch(data);

	mlx5e_fill_xdp_buff(rq, va, rx_headroom, cqe_bcnt, &xdp);
	अगर (mlx5e_xdp_handle(rq, di, &cqe_bcnt, &xdp))
		वापस शून्य; /* page/packet was consumed by XDP */

	rx_headroom = xdp.data - xdp.data_hard_start;
	frag_size = MLX5_SKB_FRAG_SZ(rx_headroom + cqe_bcnt);
	skb = mlx5e_build_linear_skb(rq, va, frag_size, rx_headroom, cqe_bcnt);
	अगर (unlikely(!skb))
		वापस शून्य;

	/* queue up क्रम recycling/reuse */
	page_ref_inc(di->page);

	वापस skb;
पूर्ण

अटल काष्ठा sk_buff *
mlx5e_skb_from_cqe_nonlinear(काष्ठा mlx5e_rq *rq, काष्ठा mlx5_cqe64 *cqe,
			     काष्ठा mlx5e_wqe_frag_info *wi, u32 cqe_bcnt)
अणु
	काष्ठा mlx5e_rq_frag_info *frag_info = &rq->wqe.info.arr[0];
	काष्ठा mlx5e_wqe_frag_info *head_wi = wi;
	u16 headlen      = min_t(u32, MLX5E_RX_MAX_HEAD, cqe_bcnt);
	u16 frag_headlen = headlen;
	u16 byte_cnt     = cqe_bcnt - headlen;
	काष्ठा sk_buff *skb;

	/* XDP is not supported in this configuration, as incoming packets
	 * might spपढ़ो among multiple pages.
	 */
	skb = napi_alloc_skb(rq->cq.napi,
			     ALIGN(MLX5E_RX_MAX_HEAD, माप(दीर्घ)));
	अगर (unlikely(!skb)) अणु
		rq->stats->buff_alloc_err++;
		वापस शून्य;
	पूर्ण

	net_prefetchw(skb->data);

	जबतक (byte_cnt) अणु
		u16 frag_consumed_bytes =
			min_t(u16, frag_info->frag_size - frag_headlen, byte_cnt);

		mlx5e_add_skb_frag(rq, skb, wi->di, wi->offset + frag_headlen,
				   frag_consumed_bytes, frag_info->frag_stride);
		byte_cnt -= frag_consumed_bytes;
		frag_headlen = 0;
		frag_info++;
		wi++;
	पूर्ण

	/* copy header */
	mlx5e_copy_skb_header(rq->pdev, skb, head_wi->di, head_wi->offset, headlen);
	/* skb linear part was allocated with headlen and aligned to दीर्घ */
	skb->tail += headlen;
	skb->len  += headlen;

	वापस skb;
पूर्ण

अटल व्योम trigger_report(काष्ठा mlx5e_rq *rq, काष्ठा mlx5_cqe64 *cqe)
अणु
	काष्ठा mlx5_err_cqe *err_cqe = (काष्ठा mlx5_err_cqe *)cqe;
	काष्ठा mlx5e_priv *priv = rq->priv;

	अगर (cqe_syndrome_needs_recover(err_cqe->syndrome) &&
	    !test_and_set_bit(MLX5E_RQ_STATE_RECOVERING, &rq->state)) अणु
		mlx5e_dump_error_cqe(&rq->cq, rq->rqn, err_cqe);
		queue_work(priv->wq, &rq->recover_work);
	पूर्ण
पूर्ण

अटल व्योम mlx5e_handle_rx_cqe(काष्ठा mlx5e_rq *rq, काष्ठा mlx5_cqe64 *cqe)
अणु
	काष्ठा mlx5_wq_cyc *wq = &rq->wqe.wq;
	काष्ठा mlx5e_wqe_frag_info *wi;
	काष्ठा sk_buff *skb;
	u32 cqe_bcnt;
	u16 ci;

	ci       = mlx5_wq_cyc_ctr2ix(wq, be16_to_cpu(cqe->wqe_counter));
	wi       = get_frag(rq, ci);
	cqe_bcnt = be32_to_cpu(cqe->byte_cnt);

	अगर (unlikely(MLX5E_RX_ERR_CQE(cqe))) अणु
		trigger_report(rq, cqe);
		rq->stats->wqe_err++;
		जाओ मुक्त_wqe;
	पूर्ण

	skb = INसूचीECT_CALL_2(rq->wqe.skb_from_cqe,
			      mlx5e_skb_from_cqe_linear,
			      mlx5e_skb_from_cqe_nonlinear,
			      rq, cqe, wi, cqe_bcnt);
	अगर (!skb) अणु
		/* probably क्रम XDP */
		अगर (__test_and_clear_bit(MLX5E_RQ_FLAG_XDP_XMIT, rq->flags)) अणु
			/* करो not वापस page to cache,
			 * it will be वापसed on XDP_TX completion.
			 */
			जाओ wq_cyc_pop;
		पूर्ण
		जाओ मुक्त_wqe;
	पूर्ण

	mlx5e_complete_rx_cqe(rq, cqe, cqe_bcnt, skb);

	अगर (mlx5e_cqe_regb_chain(cqe))
		अगर (!mlx5e_tc_update_skb(cqe, skb)) अणु
			dev_kमुक्त_skb_any(skb);
			जाओ मुक्त_wqe;
		पूर्ण

	napi_gro_receive(rq->cq.napi, skb);

मुक्त_wqe:
	mlx5e_मुक्त_rx_wqe(rq, wi, true);
wq_cyc_pop:
	mlx5_wq_cyc_pop(wq);
पूर्ण

#अगर_घोषित CONFIG_MLX5_ESWITCH
अटल व्योम mlx5e_handle_rx_cqe_rep(काष्ठा mlx5e_rq *rq, काष्ठा mlx5_cqe64 *cqe)
अणु
	काष्ठा net_device *netdev = rq->netdev;
	काष्ठा mlx5e_priv *priv = netdev_priv(netdev);
	काष्ठा mlx5e_rep_priv *rpriv  = priv->ppriv;
	काष्ठा mlx5_eचयन_rep *rep = rpriv->rep;
	काष्ठा mlx5e_tc_update_priv tc_priv = अणुपूर्ण;
	काष्ठा mlx5_wq_cyc *wq = &rq->wqe.wq;
	काष्ठा mlx5e_wqe_frag_info *wi;
	काष्ठा sk_buff *skb;
	u32 cqe_bcnt;
	u16 ci;

	ci       = mlx5_wq_cyc_ctr2ix(wq, be16_to_cpu(cqe->wqe_counter));
	wi       = get_frag(rq, ci);
	cqe_bcnt = be32_to_cpu(cqe->byte_cnt);

	अगर (unlikely(MLX5E_RX_ERR_CQE(cqe))) अणु
		rq->stats->wqe_err++;
		जाओ मुक्त_wqe;
	पूर्ण

	skb = INसूचीECT_CALL_2(rq->wqe.skb_from_cqe,
			      mlx5e_skb_from_cqe_linear,
			      mlx5e_skb_from_cqe_nonlinear,
			      rq, cqe, wi, cqe_bcnt);
	अगर (!skb) अणु
		/* probably क्रम XDP */
		अगर (__test_and_clear_bit(MLX5E_RQ_FLAG_XDP_XMIT, rq->flags)) अणु
			/* करो not वापस page to cache,
			 * it will be वापसed on XDP_TX completion.
			 */
			जाओ wq_cyc_pop;
		पूर्ण
		जाओ मुक्त_wqe;
	पूर्ण

	mlx5e_complete_rx_cqe(rq, cqe, cqe_bcnt, skb);

	अगर (rep->vlan && skb_vlan_tag_present(skb))
		skb_vlan_pop(skb);

	अगर (!mlx5e_rep_tc_update_skb(cqe, skb, &tc_priv)) अणु
		dev_kमुक्त_skb_any(skb);
		जाओ मुक्त_wqe;
	पूर्ण

	napi_gro_receive(rq->cq.napi, skb);

	mlx5_rep_tc_post_napi_receive(&tc_priv);

मुक्त_wqe:
	mlx5e_मुक्त_rx_wqe(rq, wi, true);
wq_cyc_pop:
	mlx5_wq_cyc_pop(wq);
पूर्ण

अटल व्योम mlx5e_handle_rx_cqe_mpwrq_rep(काष्ठा mlx5e_rq *rq, काष्ठा mlx5_cqe64 *cqe)
अणु
	u16 cstrides       = mpwrq_get_cqe_consumed_strides(cqe);
	u16 wqe_id         = be16_to_cpu(cqe->wqe_id);
	काष्ठा mlx5e_mpw_info *wi = &rq->mpwqe.info[wqe_id];
	u16 stride_ix      = mpwrq_get_cqe_stride_index(cqe);
	u32 wqe_offset     = stride_ix << rq->mpwqe.log_stride_sz;
	u32 head_offset    = wqe_offset & (PAGE_SIZE - 1);
	u32 page_idx       = wqe_offset >> PAGE_SHIFT;
	काष्ठा mlx5e_tc_update_priv tc_priv = अणुपूर्ण;
	काष्ठा mlx5e_rx_wqe_ll *wqe;
	काष्ठा mlx5_wq_ll *wq;
	काष्ठा sk_buff *skb;
	u16 cqe_bcnt;

	wi->consumed_strides += cstrides;

	अगर (unlikely(MLX5E_RX_ERR_CQE(cqe))) अणु
		trigger_report(rq, cqe);
		rq->stats->wqe_err++;
		जाओ mpwrq_cqe_out;
	पूर्ण

	अगर (unlikely(mpwrq_is_filler_cqe(cqe))) अणु
		काष्ठा mlx5e_rq_stats *stats = rq->stats;

		stats->mpwqe_filler_cqes++;
		stats->mpwqe_filler_strides += cstrides;
		जाओ mpwrq_cqe_out;
	पूर्ण

	cqe_bcnt = mpwrq_get_cqe_byte_cnt(cqe);

	skb = INसूचीECT_CALL_2(rq->mpwqe.skb_from_cqe_mpwrq,
			      mlx5e_skb_from_cqe_mpwrq_linear,
			      mlx5e_skb_from_cqe_mpwrq_nonlinear,
			      rq, wi, cqe_bcnt, head_offset, page_idx);
	अगर (!skb)
		जाओ mpwrq_cqe_out;

	mlx5e_complete_rx_cqe(rq, cqe, cqe_bcnt, skb);

	अगर (!mlx5e_rep_tc_update_skb(cqe, skb, &tc_priv)) अणु
		dev_kमुक्त_skb_any(skb);
		जाओ mpwrq_cqe_out;
	पूर्ण

	napi_gro_receive(rq->cq.napi, skb);

	mlx5_rep_tc_post_napi_receive(&tc_priv);

mpwrq_cqe_out:
	अगर (likely(wi->consumed_strides < rq->mpwqe.num_strides))
		वापस;

	wq  = &rq->mpwqe.wq;
	wqe = mlx5_wq_ll_get_wqe(wq, wqe_id);
	mlx5e_मुक्त_rx_mpwqe(rq, wi, true);
	mlx5_wq_ll_pop(wq, cqe->wqe_id, &wqe->next.next_wqe_index);
पूर्ण

स्थिर काष्ठा mlx5e_rx_handlers mlx5e_rx_handlers_rep = अणु
	.handle_rx_cqe       = mlx5e_handle_rx_cqe_rep,
	.handle_rx_cqe_mpwqe = mlx5e_handle_rx_cqe_mpwrq_rep,
पूर्ण;
#पूर्ण_अगर

अटल काष्ठा sk_buff *
mlx5e_skb_from_cqe_mpwrq_nonlinear(काष्ठा mlx5e_rq *rq, काष्ठा mlx5e_mpw_info *wi,
				   u16 cqe_bcnt, u32 head_offset, u32 page_idx)
अणु
	u16 headlen = min_t(u16, MLX5E_RX_MAX_HEAD, cqe_bcnt);
	काष्ठा mlx5e_dma_info *di = &wi->umr.dma_info[page_idx];
	u32 frag_offset    = head_offset + headlen;
	u32 byte_cnt       = cqe_bcnt - headlen;
	काष्ठा mlx5e_dma_info *head_di = di;
	काष्ठा sk_buff *skb;

	skb = napi_alloc_skb(rq->cq.napi,
			     ALIGN(MLX5E_RX_MAX_HEAD, माप(दीर्घ)));
	अगर (unlikely(!skb)) अणु
		rq->stats->buff_alloc_err++;
		वापस शून्य;
	पूर्ण

	net_prefetchw(skb->data);

	अगर (unlikely(frag_offset >= PAGE_SIZE)) अणु
		di++;
		frag_offset -= PAGE_SIZE;
	पूर्ण

	जबतक (byte_cnt) अणु
		u32 pg_consumed_bytes =
			min_t(u32, PAGE_SIZE - frag_offset, byte_cnt);
		अचिन्हित पूर्णांक truesize =
			ALIGN(pg_consumed_bytes, BIT(rq->mpwqe.log_stride_sz));

		mlx5e_add_skb_frag(rq, skb, di, frag_offset,
				   pg_consumed_bytes, truesize);
		byte_cnt -= pg_consumed_bytes;
		frag_offset = 0;
		di++;
	पूर्ण
	/* copy header */
	mlx5e_copy_skb_header(rq->pdev, skb, head_di, head_offset, headlen);
	/* skb linear part was allocated with headlen and aligned to दीर्घ */
	skb->tail += headlen;
	skb->len  += headlen;

	वापस skb;
पूर्ण

अटल काष्ठा sk_buff *
mlx5e_skb_from_cqe_mpwrq_linear(काष्ठा mlx5e_rq *rq, काष्ठा mlx5e_mpw_info *wi,
				u16 cqe_bcnt, u32 head_offset, u32 page_idx)
अणु
	काष्ठा mlx5e_dma_info *di = &wi->umr.dma_info[page_idx];
	u16 rx_headroom = rq->buff.headroom;
	u32 cqe_bcnt32 = cqe_bcnt;
	काष्ठा xdp_buff xdp;
	काष्ठा sk_buff *skb;
	व्योम *va, *data;
	u32 frag_size;

	/* Check packet size. Note LRO करोesn't use linear SKB */
	अगर (unlikely(cqe_bcnt > rq->hw_mtu)) अणु
		rq->stats->oversize_pkts_sw_drop++;
		वापस शून्य;
	पूर्ण

	va             = page_address(di->page) + head_offset;
	data           = va + rx_headroom;
	frag_size      = MLX5_SKB_FRAG_SZ(rx_headroom + cqe_bcnt32);

	dma_sync_single_range_क्रम_cpu(rq->pdev, di->addr, head_offset,
				      frag_size, DMA_FROM_DEVICE);
	net_prefetchw(va); /* xdp_frame data area */
	net_prefetch(data);

	mlx5e_fill_xdp_buff(rq, va, rx_headroom, cqe_bcnt32, &xdp);
	अगर (mlx5e_xdp_handle(rq, di, &cqe_bcnt32, &xdp)) अणु
		अगर (__test_and_clear_bit(MLX5E_RQ_FLAG_XDP_XMIT, rq->flags))
			__set_bit(page_idx, wi->xdp_xmit_biपंचांगap); /* non-atomic */
		वापस शून्य; /* page/packet was consumed by XDP */
	पूर्ण

	rx_headroom = xdp.data - xdp.data_hard_start;
	frag_size = MLX5_SKB_FRAG_SZ(rx_headroom + cqe_bcnt32);
	skb = mlx5e_build_linear_skb(rq, va, frag_size, rx_headroom, cqe_bcnt32);
	अगर (unlikely(!skb))
		वापस शून्य;

	/* queue up क्रम recycling/reuse */
	page_ref_inc(di->page);

	वापस skb;
पूर्ण

अटल व्योम mlx5e_handle_rx_cqe_mpwrq(काष्ठा mlx5e_rq *rq, काष्ठा mlx5_cqe64 *cqe)
अणु
	u16 cstrides       = mpwrq_get_cqe_consumed_strides(cqe);
	u16 wqe_id         = be16_to_cpu(cqe->wqe_id);
	काष्ठा mlx5e_mpw_info *wi = &rq->mpwqe.info[wqe_id];
	u16 stride_ix      = mpwrq_get_cqe_stride_index(cqe);
	u32 wqe_offset     = stride_ix << rq->mpwqe.log_stride_sz;
	u32 head_offset    = wqe_offset & (PAGE_SIZE - 1);
	u32 page_idx       = wqe_offset >> PAGE_SHIFT;
	काष्ठा mlx5e_rx_wqe_ll *wqe;
	काष्ठा mlx5_wq_ll *wq;
	काष्ठा sk_buff *skb;
	u16 cqe_bcnt;

	wi->consumed_strides += cstrides;

	अगर (unlikely(MLX5E_RX_ERR_CQE(cqe))) अणु
		trigger_report(rq, cqe);
		rq->stats->wqe_err++;
		जाओ mpwrq_cqe_out;
	पूर्ण

	अगर (unlikely(mpwrq_is_filler_cqe(cqe))) अणु
		काष्ठा mlx5e_rq_stats *stats = rq->stats;

		stats->mpwqe_filler_cqes++;
		stats->mpwqe_filler_strides += cstrides;
		जाओ mpwrq_cqe_out;
	पूर्ण

	cqe_bcnt = mpwrq_get_cqe_byte_cnt(cqe);

	skb = INसूचीECT_CALL_2(rq->mpwqe.skb_from_cqe_mpwrq,
			      mlx5e_skb_from_cqe_mpwrq_linear,
			      mlx5e_skb_from_cqe_mpwrq_nonlinear,
			      rq, wi, cqe_bcnt, head_offset, page_idx);
	अगर (!skb)
		जाओ mpwrq_cqe_out;

	mlx5e_complete_rx_cqe(rq, cqe, cqe_bcnt, skb);

	अगर (mlx5e_cqe_regb_chain(cqe))
		अगर (!mlx5e_tc_update_skb(cqe, skb)) अणु
			dev_kमुक्त_skb_any(skb);
			जाओ mpwrq_cqe_out;
		पूर्ण

	napi_gro_receive(rq->cq.napi, skb);

mpwrq_cqe_out:
	अगर (likely(wi->consumed_strides < rq->mpwqe.num_strides))
		वापस;

	wq  = &rq->mpwqe.wq;
	wqe = mlx5_wq_ll_get_wqe(wq, wqe_id);
	mlx5e_मुक्त_rx_mpwqe(rq, wi, true);
	mlx5_wq_ll_pop(wq, cqe->wqe_id, &wqe->next.next_wqe_index);
पूर्ण

पूर्णांक mlx5e_poll_rx_cq(काष्ठा mlx5e_cq *cq, पूर्णांक budget)
अणु
	काष्ठा mlx5e_rq *rq = container_of(cq, काष्ठा mlx5e_rq, cq);
	काष्ठा mlx5_cqwq *cqwq = &cq->wq;
	काष्ठा mlx5_cqe64 *cqe;
	पूर्णांक work_करोne = 0;

	अगर (unlikely(!test_bit(MLX5E_RQ_STATE_ENABLED, &rq->state)))
		वापस 0;

	अगर (rq->page_pool)
		page_pool_nid_changed(rq->page_pool, numa_mem_id());

	अगर (rq->cqd.left) अणु
		work_करोne += mlx5e_decompress_cqes_cont(rq, cqwq, 0, budget);
		अगर (rq->cqd.left || work_करोne >= budget)
			जाओ out;
	पूर्ण

	cqe = mlx5_cqwq_get_cqe(cqwq);
	अगर (!cqe) अणु
		अगर (unlikely(work_करोne))
			जाओ out;
		वापस 0;
	पूर्ण

	करो अणु
		अगर (mlx5_get_cqe_क्रमmat(cqe) == MLX5_COMPRESSED) अणु
			work_करोne +=
				mlx5e_decompress_cqes_start(rq, cqwq,
							    budget - work_करोne);
			जारी;
		पूर्ण

		mlx5_cqwq_pop(cqwq);

		INसूचीECT_CALL_2(rq->handle_rx_cqe, mlx5e_handle_rx_cqe_mpwrq,
				mlx5e_handle_rx_cqe, rq, cqe);
	पूर्ण जबतक ((++work_करोne < budget) && (cqe = mlx5_cqwq_get_cqe(cqwq)));

out:
	अगर (rcu_access_poपूर्णांकer(rq->xdp_prog))
		mlx5e_xdp_rx_poll_complete(rq);

	mlx5_cqwq_update_db_record(cqwq);

	/* ensure cq space is मुक्तd beक्रमe enabling more cqes */
	wmb();

	वापस work_करोne;
पूर्ण

#अगर_घोषित CONFIG_MLX5_CORE_IPOIB

#घोषणा MLX5_IB_GRH_SGID_OFFSET 8
#घोषणा MLX5_IB_GRH_DGID_OFFSET 24
#घोषणा MLX5_GID_SIZE           16

अटल अंतरभूत व्योम mlx5i_complete_rx_cqe(काष्ठा mlx5e_rq *rq,
					 काष्ठा mlx5_cqe64 *cqe,
					 u32 cqe_bcnt,
					 काष्ठा sk_buff *skb)
अणु
	काष्ठा hwtstamp_config *tstamp;
	काष्ठा mlx5e_rq_stats *stats;
	काष्ठा net_device *netdev;
	काष्ठा mlx5e_priv *priv;
	अक्षर *pseuकरो_header;
	u32 flags_rqpn;
	u32 qpn;
	u8 *dgid;
	u8 g;

	qpn = be32_to_cpu(cqe->sop_drop_qpn) & 0xffffff;
	netdev = mlx5i_pkey_get_netdev(rq->netdev, qpn);

	/* No mapping present, cannot process SKB. This might happen अगर a child
	 * पूर्णांकerface is going करोwn जबतक having unprocessed CQEs on parent RQ
	 */
	अगर (unlikely(!netdev)) अणु
		/* TODO: add drop counters support */
		skb->dev = शून्य;
		pr_warn_once("Unable to map QPN %u to dev - dropping skb\n", qpn);
		वापस;
	पूर्ण

	priv = mlx5i_epriv(netdev);
	tstamp = &priv->tstamp;
	stats = &priv->channel_stats[rq->ix].rq;

	flags_rqpn = be32_to_cpu(cqe->flags_rqpn);
	g = (flags_rqpn >> 28) & 3;
	dgid = skb->data + MLX5_IB_GRH_DGID_OFFSET;
	अगर ((!g) || dgid[0] != 0xff)
		skb->pkt_type = PACKET_HOST;
	अन्यथा अगर (स_भेद(dgid, netdev->broadcast + 4, MLX5_GID_SIZE) == 0)
		skb->pkt_type = PACKET_BROADCAST;
	अन्यथा
		skb->pkt_type = PACKET_MULTICAST;

	/* Drop packets that this पूर्णांकerface sent, ie multicast packets
	 * that the HCA has replicated.
	 */
	अगर (g && (qpn == (flags_rqpn & 0xffffff)) &&
	    (स_भेद(netdev->dev_addr + 4, skb->data + MLX5_IB_GRH_SGID_OFFSET,
		    MLX5_GID_SIZE) == 0)) अणु
		skb->dev = शून्य;
		वापस;
	पूर्ण

	skb_pull(skb, MLX5_IB_GRH_BYTES);

	skb->protocol = *((__be16 *)(skb->data));

	अगर (netdev->features & NETIF_F_RXCSUM) अणु
		skb->ip_summed = CHECKSUM_COMPLETE;
		skb->csum = csum_unfold((__क्रमce __sum16)cqe->check_sum);
		stats->csum_complete++;
	पूर्ण अन्यथा अणु
		skb->ip_summed = CHECKSUM_NONE;
		stats->csum_none++;
	पूर्ण

	अगर (unlikely(mlx5e_rx_hw_stamp(tstamp)))
		skb_hwtstamps(skb)->hwtstamp = mlx5e_cqe_ts_to_ns(rq->ptp_cyc2समय,
								  rq->घड़ी, get_cqe_ts(cqe));
	skb_record_rx_queue(skb, rq->ix);

	अगर (likely(netdev->features & NETIF_F_RXHASH))
		mlx5e_skb_set_hash(cqe, skb);

	/* 20 bytes of ipoib header and 4 क्रम encap existing */
	pseuकरो_header = skb_push(skb, MLX5_IPOIB_PSEUDO_LEN);
	स_रखो(pseuकरो_header, 0, MLX5_IPOIB_PSEUDO_LEN);
	skb_reset_mac_header(skb);
	skb_pull(skb, MLX5_IPOIB_HARD_LEN);

	skb->dev = netdev;

	stats->packets++;
	stats->bytes += cqe_bcnt;
पूर्ण

अटल व्योम mlx5i_handle_rx_cqe(काष्ठा mlx5e_rq *rq, काष्ठा mlx5_cqe64 *cqe)
अणु
	काष्ठा mlx5_wq_cyc *wq = &rq->wqe.wq;
	काष्ठा mlx5e_wqe_frag_info *wi;
	काष्ठा sk_buff *skb;
	u32 cqe_bcnt;
	u16 ci;

	ci       = mlx5_wq_cyc_ctr2ix(wq, be16_to_cpu(cqe->wqe_counter));
	wi       = get_frag(rq, ci);
	cqe_bcnt = be32_to_cpu(cqe->byte_cnt);

	अगर (unlikely(MLX5E_RX_ERR_CQE(cqe))) अणु
		rq->stats->wqe_err++;
		जाओ wq_मुक्त_wqe;
	पूर्ण

	skb = INसूचीECT_CALL_2(rq->wqe.skb_from_cqe,
			      mlx5e_skb_from_cqe_linear,
			      mlx5e_skb_from_cqe_nonlinear,
			      rq, cqe, wi, cqe_bcnt);
	अगर (!skb)
		जाओ wq_मुक्त_wqe;

	mlx5i_complete_rx_cqe(rq, cqe, cqe_bcnt, skb);
	अगर (unlikely(!skb->dev)) अणु
		dev_kमुक्त_skb_any(skb);
		जाओ wq_मुक्त_wqe;
	पूर्ण
	napi_gro_receive(rq->cq.napi, skb);

wq_मुक्त_wqe:
	mlx5e_मुक्त_rx_wqe(rq, wi, true);
	mlx5_wq_cyc_pop(wq);
पूर्ण

स्थिर काष्ठा mlx5e_rx_handlers mlx5i_rx_handlers = अणु
	.handle_rx_cqe       = mlx5i_handle_rx_cqe,
	.handle_rx_cqe_mpwqe = शून्य, /* Not supported */
पूर्ण;
#पूर्ण_अगर /* CONFIG_MLX5_CORE_IPOIB */

#अगर_घोषित CONFIG_MLX5_EN_IPSEC

अटल व्योम mlx5e_ipsec_handle_rx_cqe(काष्ठा mlx5e_rq *rq, काष्ठा mlx5_cqe64 *cqe)
अणु
	काष्ठा mlx5_wq_cyc *wq = &rq->wqe.wq;
	काष्ठा mlx5e_wqe_frag_info *wi;
	काष्ठा sk_buff *skb;
	u32 cqe_bcnt;
	u16 ci;

	ci       = mlx5_wq_cyc_ctr2ix(wq, be16_to_cpu(cqe->wqe_counter));
	wi       = get_frag(rq, ci);
	cqe_bcnt = be32_to_cpu(cqe->byte_cnt);

	अगर (unlikely(MLX5E_RX_ERR_CQE(cqe))) अणु
		rq->stats->wqe_err++;
		जाओ wq_मुक्त_wqe;
	पूर्ण

	skb = INसूचीECT_CALL_2(rq->wqe.skb_from_cqe,
			      mlx5e_skb_from_cqe_linear,
			      mlx5e_skb_from_cqe_nonlinear,
			      rq, cqe, wi, cqe_bcnt);
	अगर (unlikely(!skb)) /* a DROP, save the page-reuse checks */
		जाओ wq_मुक्त_wqe;

	skb = mlx5e_ipsec_handle_rx_skb(rq->netdev, skb, &cqe_bcnt);
	अगर (unlikely(!skb))
		जाओ wq_मुक्त_wqe;

	mlx5e_complete_rx_cqe(rq, cqe, cqe_bcnt, skb);
	napi_gro_receive(rq->cq.napi, skb);

wq_मुक्त_wqe:
	mlx5e_मुक्त_rx_wqe(rq, wi, true);
	mlx5_wq_cyc_pop(wq);
पूर्ण

#पूर्ण_अगर /* CONFIG_MLX5_EN_IPSEC */

पूर्णांक mlx5e_rq_set_handlers(काष्ठा mlx5e_rq *rq, काष्ठा mlx5e_params *params, bool xsk)
अणु
	काष्ठा net_device *netdev = rq->netdev;
	काष्ठा mlx5_core_dev *mdev = rq->mdev;
	काष्ठा mlx5e_priv *priv = rq->priv;

	चयन (rq->wq_type) अणु
	हाल MLX5_WQ_TYPE_LINKED_LIST_STRIDING_RQ:
		rq->mpwqe.skb_from_cqe_mpwrq = xsk ?
			mlx5e_xsk_skb_from_cqe_mpwrq_linear :
			mlx5e_rx_mpwqe_is_linear_skb(mdev, params, शून्य) ?
				mlx5e_skb_from_cqe_mpwrq_linear :
				mlx5e_skb_from_cqe_mpwrq_nonlinear;
		rq->post_wqes = mlx5e_post_rx_mpwqes;
		rq->dealloc_wqe = mlx5e_dealloc_rx_mpwqe;

		rq->handle_rx_cqe = priv->profile->rx_handlers->handle_rx_cqe_mpwqe;
		अगर (mlx5_fpga_is_ipsec_device(mdev)) अणु
			netdev_err(netdev, "MPWQE RQ with Innova IPSec offload not supported\n");
			वापस -EINVAL;
		पूर्ण
		अगर (!rq->handle_rx_cqe) अणु
			netdev_err(netdev, "RX handler of MPWQE RQ is not set\n");
			वापस -EINVAL;
		पूर्ण
		अवरोध;
	शेष: /* MLX5_WQ_TYPE_CYCLIC */
		rq->wqe.skb_from_cqe = xsk ?
			mlx5e_xsk_skb_from_cqe_linear :
			mlx5e_rx_is_linear_skb(params, शून्य) ?
				mlx5e_skb_from_cqe_linear :
				mlx5e_skb_from_cqe_nonlinear;
		rq->post_wqes = mlx5e_post_rx_wqes;
		rq->dealloc_wqe = mlx5e_dealloc_rx_wqe;

#अगर_घोषित CONFIG_MLX5_EN_IPSEC
		अगर ((mlx5_fpga_ipsec_device_caps(mdev) & MLX5_ACCEL_IPSEC_CAP_DEVICE) &&
		    priv->ipsec)
			rq->handle_rx_cqe = mlx5e_ipsec_handle_rx_cqe;
		अन्यथा
#पूर्ण_अगर
			rq->handle_rx_cqe = priv->profile->rx_handlers->handle_rx_cqe;
		अगर (!rq->handle_rx_cqe) अणु
			netdev_err(netdev, "RX handler of RQ is not set\n");
			वापस -EINVAL;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम mlx5e_trap_handle_rx_cqe(काष्ठा mlx5e_rq *rq, काष्ठा mlx5_cqe64 *cqe)
अणु
	काष्ठा mlx5e_priv *priv = netdev_priv(rq->netdev);
	काष्ठा mlx5_wq_cyc *wq = &rq->wqe.wq;
	काष्ठा mlx5e_wqe_frag_info *wi;
	काष्ठा devlink_port *dl_port;
	काष्ठा sk_buff *skb;
	u32 cqe_bcnt;
	u16 trap_id;
	u16 ci;

	trap_id  = get_cqe_flow_tag(cqe);
	ci       = mlx5_wq_cyc_ctr2ix(wq, be16_to_cpu(cqe->wqe_counter));
	wi       = get_frag(rq, ci);
	cqe_bcnt = be32_to_cpu(cqe->byte_cnt);

	अगर (unlikely(MLX5E_RX_ERR_CQE(cqe))) अणु
		rq->stats->wqe_err++;
		जाओ मुक्त_wqe;
	पूर्ण

	skb = mlx5e_skb_from_cqe_nonlinear(rq, cqe, wi, cqe_bcnt);
	अगर (!skb)
		जाओ मुक्त_wqe;

	mlx5e_complete_rx_cqe(rq, cqe, cqe_bcnt, skb);
	skb_push(skb, ETH_HLEN);

	dl_port = mlx5e_devlink_get_dl_port(priv);
	mlx5_devlink_trap_report(rq->mdev, trap_id, skb, dl_port);
	dev_kमुक्त_skb_any(skb);

मुक्त_wqe:
	mlx5e_मुक्त_rx_wqe(rq, wi, false);
	mlx5_wq_cyc_pop(wq);
पूर्ण

व्योम mlx5e_rq_set_trap_handlers(काष्ठा mlx5e_rq *rq, काष्ठा mlx5e_params *params)
अणु
	rq->wqe.skb_from_cqe = mlx5e_rx_is_linear_skb(params, शून्य) ?
			       mlx5e_skb_from_cqe_linear :
			       mlx5e_skb_from_cqe_nonlinear;
	rq->post_wqes = mlx5e_post_rx_wqes;
	rq->dealloc_wqe = mlx5e_dealloc_rx_wqe;
	rq->handle_rx_cqe = mlx5e_trap_handle_rx_cqe;
पूर्ण
