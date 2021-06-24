<शैली गुरु>
/*
 * Copyright (c) 2007 Mellanox Technologies. All rights reserved.
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
 *
 */

#समावेश <linux/bpf.h>
#समावेश <linux/bpf_trace.h>
#समावेश <linux/mlx4/cq.h>
#समावेश <linux/slab.h>
#समावेश <linux/mlx4/qp.h>
#समावेश <linux/skbuff.h>
#समावेश <linux/rculist.h>
#समावेश <linux/अगर_ether.h>
#समावेश <linux/अगर_vlan.h>
#समावेश <linux/vदो_स्मृति.h>
#समावेश <linux/irq.h>

#समावेश <net/ip.h>
#अगर IS_ENABLED(CONFIG_IPV6)
#समावेश <net/ip6_checksum.h>
#पूर्ण_अगर

#समावेश "mlx4_en.h"

अटल पूर्णांक mlx4_alloc_page(काष्ठा mlx4_en_priv *priv,
			   काष्ठा mlx4_en_rx_alloc *frag,
			   gfp_t gfp)
अणु
	काष्ठा page *page;
	dma_addr_t dma;

	page = alloc_page(gfp);
	अगर (unlikely(!page))
		वापस -ENOMEM;
	dma = dma_map_page(priv->ddev, page, 0, PAGE_SIZE, priv->dma_dir);
	अगर (unlikely(dma_mapping_error(priv->ddev, dma))) अणु
		__मुक्त_page(page);
		वापस -ENOMEM;
	पूर्ण
	frag->page = page;
	frag->dma = dma;
	frag->page_offset = priv->rx_headroom;
	वापस 0;
पूर्ण

अटल पूर्णांक mlx4_en_alloc_frags(काष्ठा mlx4_en_priv *priv,
			       काष्ठा mlx4_en_rx_ring *ring,
			       काष्ठा mlx4_en_rx_desc *rx_desc,
			       काष्ठा mlx4_en_rx_alloc *frags,
			       gfp_t gfp)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < priv->num_frags; i++, frags++) अणु
		अगर (!frags->page) अणु
			अगर (mlx4_alloc_page(priv, frags, gfp))
				वापस -ENOMEM;
			ring->rx_alloc_pages++;
		पूर्ण
		rx_desc->data[i].addr = cpu_to_be64(frags->dma +
						    frags->page_offset);
	पूर्ण
	वापस 0;
पूर्ण

अटल व्योम mlx4_en_मुक्त_frag(स्थिर काष्ठा mlx4_en_priv *priv,
			      काष्ठा mlx4_en_rx_alloc *frag)
अणु
	अगर (frag->page) अणु
		dma_unmap_page(priv->ddev, frag->dma,
			       PAGE_SIZE, priv->dma_dir);
		__मुक्त_page(frag->page);
	पूर्ण
	/* We need to clear all fields, otherwise a change of priv->log_rx_info
	 * could lead to see garbage later in frag->page.
	 */
	स_रखो(frag, 0, माप(*frag));
पूर्ण

अटल व्योम mlx4_en_init_rx_desc(स्थिर काष्ठा mlx4_en_priv *priv,
				 काष्ठा mlx4_en_rx_ring *ring, पूर्णांक index)
अणु
	काष्ठा mlx4_en_rx_desc *rx_desc = ring->buf + ring->stride * index;
	पूर्णांक possible_frags;
	पूर्णांक i;

	/* Set size and memtype fields */
	क्रम (i = 0; i < priv->num_frags; i++) अणु
		rx_desc->data[i].byte_count =
			cpu_to_be32(priv->frag_info[i].frag_size);
		rx_desc->data[i].lkey = cpu_to_be32(priv->mdev->mr.key);
	पूर्ण

	/* If the number of used fragments करोes not fill up the ring stride,
	 * reमुख्यing (unused) fragments must be padded with null address/size
	 * and a special memory key */
	possible_frags = (ring->stride - माप(काष्ठा mlx4_en_rx_desc)) / DS_SIZE;
	क्रम (i = priv->num_frags; i < possible_frags; i++) अणु
		rx_desc->data[i].byte_count = 0;
		rx_desc->data[i].lkey = cpu_to_be32(MLX4_EN_MEMTYPE_PAD);
		rx_desc->data[i].addr = 0;
	पूर्ण
पूर्ण

अटल पूर्णांक mlx4_en_prepare_rx_desc(काष्ठा mlx4_en_priv *priv,
				   काष्ठा mlx4_en_rx_ring *ring, पूर्णांक index,
				   gfp_t gfp)
अणु
	काष्ठा mlx4_en_rx_desc *rx_desc = ring->buf +
		(index << ring->log_stride);
	काष्ठा mlx4_en_rx_alloc *frags = ring->rx_info +
					(index << priv->log_rx_info);
	अगर (likely(ring->page_cache.index > 0)) अणु
		/* XDP uses a single page per frame */
		अगर (!frags->page) अणु
			ring->page_cache.index--;
			frags->page = ring->page_cache.buf[ring->page_cache.index].page;
			frags->dma  = ring->page_cache.buf[ring->page_cache.index].dma;
		पूर्ण
		frags->page_offset = XDP_PACKET_HEADROOM;
		rx_desc->data[0].addr = cpu_to_be64(frags->dma +
						    XDP_PACKET_HEADROOM);
		वापस 0;
	पूर्ण

	वापस mlx4_en_alloc_frags(priv, ring, rx_desc, frags, gfp);
पूर्ण

अटल bool mlx4_en_is_ring_empty(स्थिर काष्ठा mlx4_en_rx_ring *ring)
अणु
	वापस ring->prod == ring->cons;
पूर्ण

अटल अंतरभूत व्योम mlx4_en_update_rx_prod_db(काष्ठा mlx4_en_rx_ring *ring)
अणु
	*ring->wqres.db.db = cpu_to_be32(ring->prod & 0xffff);
पूर्ण

/* slow path */
अटल व्योम mlx4_en_मुक्त_rx_desc(स्थिर काष्ठा mlx4_en_priv *priv,
				 काष्ठा mlx4_en_rx_ring *ring,
				 पूर्णांक index)
अणु
	काष्ठा mlx4_en_rx_alloc *frags;
	पूर्णांक nr;

	frags = ring->rx_info + (index << priv->log_rx_info);
	क्रम (nr = 0; nr < priv->num_frags; nr++) अणु
		en_dbg(DRV, priv, "Freeing fragment:%d\n", nr);
		mlx4_en_मुक्त_frag(priv, frags + nr);
	पूर्ण
पूर्ण

/* Function not in fast-path */
अटल पूर्णांक mlx4_en_fill_rx_buffers(काष्ठा mlx4_en_priv *priv)
अणु
	काष्ठा mlx4_en_rx_ring *ring;
	पूर्णांक ring_ind;
	पूर्णांक buf_ind;
	पूर्णांक new_size;

	क्रम (buf_ind = 0; buf_ind < priv->prof->rx_ring_size; buf_ind++) अणु
		क्रम (ring_ind = 0; ring_ind < priv->rx_ring_num; ring_ind++) अणु
			ring = priv->rx_ring[ring_ind];

			अगर (mlx4_en_prepare_rx_desc(priv, ring,
						    ring->actual_size,
						    GFP_KERNEL)) अणु
				अगर (ring->actual_size < MLX4_EN_MIN_RX_SIZE) अणु
					en_err(priv, "Failed to allocate enough rx buffers\n");
					वापस -ENOMEM;
				पूर्ण अन्यथा अणु
					new_size = roundकरोwn_घात_of_two(ring->actual_size);
					en_warn(priv, "Only %d buffers allocated reducing ring size to %d\n",
						ring->actual_size, new_size);
					जाओ reduce_rings;
				पूर्ण
			पूर्ण
			ring->actual_size++;
			ring->prod++;
		पूर्ण
	पूर्ण
	वापस 0;

reduce_rings:
	क्रम (ring_ind = 0; ring_ind < priv->rx_ring_num; ring_ind++) अणु
		ring = priv->rx_ring[ring_ind];
		जबतक (ring->actual_size > new_size) अणु
			ring->actual_size--;
			ring->prod--;
			mlx4_en_मुक्त_rx_desc(priv, ring, ring->actual_size);
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम mlx4_en_मुक्त_rx_buf(काष्ठा mlx4_en_priv *priv,
				काष्ठा mlx4_en_rx_ring *ring)
अणु
	पूर्णांक index;

	en_dbg(DRV, priv, "Freeing Rx buf - cons:%d prod:%d\n",
	       ring->cons, ring->prod);

	/* Unmap and मुक्त Rx buffers */
	क्रम (index = 0; index < ring->size; index++) अणु
		en_dbg(DRV, priv, "Processing descriptor:%d\n", index);
		mlx4_en_मुक्त_rx_desc(priv, ring, index);
	पूर्ण
	ring->cons = 0;
	ring->prod = 0;
पूर्ण

व्योम mlx4_en_set_num_rx_rings(काष्ठा mlx4_en_dev *mdev)
अणु
	पूर्णांक i;
	पूर्णांक num_of_eqs;
	पूर्णांक num_rx_rings;
	काष्ठा mlx4_dev *dev = mdev->dev;

	mlx4_क्रमeach_port(i, dev, MLX4_PORT_TYPE_ETH) अणु
		num_of_eqs = max_t(पूर्णांक, MIN_RX_RINGS,
				   min_t(पूर्णांक,
					 mlx4_get_eqs_per_port(mdev->dev, i),
					 DEF_RX_RINGS));

		num_rx_rings = mlx4_low_memory_profile() ? MIN_RX_RINGS :
			min_t(पूर्णांक, num_of_eqs, num_online_cpus());
		mdev->profile.prof[i].rx_ring_num =
			roundकरोwn_घात_of_two(num_rx_rings);
	पूर्ण
पूर्ण

पूर्णांक mlx4_en_create_rx_ring(काष्ठा mlx4_en_priv *priv,
			   काष्ठा mlx4_en_rx_ring **pring,
			   u32 size, u16 stride, पूर्णांक node, पूर्णांक queue_index)
अणु
	काष्ठा mlx4_en_dev *mdev = priv->mdev;
	काष्ठा mlx4_en_rx_ring *ring;
	पूर्णांक err = -ENOMEM;
	पूर्णांक पंचांगp;

	ring = kzalloc_node(माप(*ring), GFP_KERNEL, node);
	अगर (!ring) अणु
		en_err(priv, "Failed to allocate RX ring structure\n");
		वापस -ENOMEM;
	पूर्ण

	ring->prod = 0;
	ring->cons = 0;
	ring->size = size;
	ring->size_mask = size - 1;
	ring->stride = stride;
	ring->log_stride = ffs(ring->stride) - 1;
	ring->buf_size = ring->size * ring->stride + TXBB_SIZE;

	अगर (xdp_rxq_info_reg(&ring->xdp_rxq, priv->dev, queue_index, 0) < 0)
		जाओ err_ring;

	पंचांगp = size * roundup_घात_of_two(MLX4_EN_MAX_RX_FRAGS *
					माप(काष्ठा mlx4_en_rx_alloc));
	ring->rx_info = kvzalloc_node(पंचांगp, GFP_KERNEL, node);
	अगर (!ring->rx_info) अणु
		err = -ENOMEM;
		जाओ err_xdp_info;
	पूर्ण

	en_dbg(DRV, priv, "Allocated rx_info ring at addr:%p size:%d\n",
		 ring->rx_info, पंचांगp);

	/* Allocate HW buffers on provided NUMA node */
	set_dev_node(&mdev->dev->persist->pdev->dev, node);
	err = mlx4_alloc_hwq_res(mdev->dev, &ring->wqres, ring->buf_size);
	set_dev_node(&mdev->dev->persist->pdev->dev, mdev->dev->numa_node);
	अगर (err)
		जाओ err_info;

	ring->buf = ring->wqres.buf.direct.buf;

	ring->hwtstamp_rx_filter = priv->hwtstamp_config.rx_filter;

	*pring = ring;
	वापस 0;

err_info:
	kvमुक्त(ring->rx_info);
	ring->rx_info = शून्य;
err_xdp_info:
	xdp_rxq_info_unreg(&ring->xdp_rxq);
err_ring:
	kमुक्त(ring);
	*pring = शून्य;

	वापस err;
पूर्ण

पूर्णांक mlx4_en_activate_rx_rings(काष्ठा mlx4_en_priv *priv)
अणु
	काष्ठा mlx4_en_rx_ring *ring;
	पूर्णांक i;
	पूर्णांक ring_ind;
	पूर्णांक err;
	पूर्णांक stride = roundup_घात_of_two(माप(काष्ठा mlx4_en_rx_desc) +
					DS_SIZE * priv->num_frags);

	क्रम (ring_ind = 0; ring_ind < priv->rx_ring_num; ring_ind++) अणु
		ring = priv->rx_ring[ring_ind];

		ring->prod = 0;
		ring->cons = 0;
		ring->actual_size = 0;
		ring->cqn = priv->rx_cq[ring_ind]->mcq.cqn;

		ring->stride = stride;
		अगर (ring->stride <= TXBB_SIZE) अणु
			/* Stamp first unused send wqe */
			__be32 *ptr = (__be32 *)ring->buf;
			__be32 stamp = cpu_to_be32(1 << STAMP_SHIFT);
			*ptr = stamp;
			/* Move poपूर्णांकer to start of rx section */
			ring->buf += TXBB_SIZE;
		पूर्ण

		ring->log_stride = ffs(ring->stride) - 1;
		ring->buf_size = ring->size * ring->stride;

		स_रखो(ring->buf, 0, ring->buf_size);
		mlx4_en_update_rx_prod_db(ring);

		/* Initialize all descriptors */
		क्रम (i = 0; i < ring->size; i++)
			mlx4_en_init_rx_desc(priv, ring, i);
	पूर्ण
	err = mlx4_en_fill_rx_buffers(priv);
	अगर (err)
		जाओ err_buffers;

	क्रम (ring_ind = 0; ring_ind < priv->rx_ring_num; ring_ind++) अणु
		ring = priv->rx_ring[ring_ind];

		ring->size_mask = ring->actual_size - 1;
		mlx4_en_update_rx_prod_db(ring);
	पूर्ण

	वापस 0;

err_buffers:
	क्रम (ring_ind = 0; ring_ind < priv->rx_ring_num; ring_ind++)
		mlx4_en_मुक्त_rx_buf(priv, priv->rx_ring[ring_ind]);

	ring_ind = priv->rx_ring_num - 1;
	जबतक (ring_ind >= 0) अणु
		अगर (priv->rx_ring[ring_ind]->stride <= TXBB_SIZE)
			priv->rx_ring[ring_ind]->buf -= TXBB_SIZE;
		ring_ind--;
	पूर्ण
	वापस err;
पूर्ण

/* We recover from out of memory by scheduling our napi poll
 * function (mlx4_en_process_cq), which tries to allocate
 * all missing RX buffers (call to mlx4_en_refill_rx_buffers).
 */
व्योम mlx4_en_recover_from_oom(काष्ठा mlx4_en_priv *priv)
अणु
	पूर्णांक ring;

	अगर (!priv->port_up)
		वापस;

	क्रम (ring = 0; ring < priv->rx_ring_num; ring++) अणु
		अगर (mlx4_en_is_ring_empty(priv->rx_ring[ring])) अणु
			local_bh_disable();
			napi_reschedule(&priv->rx_cq[ring]->napi);
			local_bh_enable();
		पूर्ण
	पूर्ण
पूर्ण

/* When the rx ring is running in page-per-packet mode, a released frame can go
 * directly पूर्णांकo a small cache, to aव्योम unmapping or touching the page
 * allocator. In bpf prog perक्रमmance scenarios, buffers are either क्रमwarded
 * or dropped, never converted to skbs, so every page can come directly from
 * this cache when it is sized to be a multiple of the napi budget.
 */
bool mlx4_en_rx_recycle(काष्ठा mlx4_en_rx_ring *ring,
			काष्ठा mlx4_en_rx_alloc *frame)
अणु
	काष्ठा mlx4_en_page_cache *cache = &ring->page_cache;

	अगर (cache->index >= MLX4_EN_CACHE_SIZE)
		वापस false;

	cache->buf[cache->index].page = frame->page;
	cache->buf[cache->index].dma = frame->dma;
	cache->index++;
	वापस true;
पूर्ण

व्योम mlx4_en_destroy_rx_ring(काष्ठा mlx4_en_priv *priv,
			     काष्ठा mlx4_en_rx_ring **pring,
			     u32 size, u16 stride)
अणु
	काष्ठा mlx4_en_dev *mdev = priv->mdev;
	काष्ठा mlx4_en_rx_ring *ring = *pring;
	काष्ठा bpf_prog *old_prog;

	old_prog = rcu_dereference_रक्षित(
					ring->xdp_prog,
					lockdep_is_held(&mdev->state_lock));
	अगर (old_prog)
		bpf_prog_put(old_prog);
	xdp_rxq_info_unreg(&ring->xdp_rxq);
	mlx4_मुक्त_hwq_res(mdev->dev, &ring->wqres, size * stride + TXBB_SIZE);
	kvमुक्त(ring->rx_info);
	ring->rx_info = शून्य;
	kमुक्त(ring);
	*pring = शून्य;
पूर्ण

व्योम mlx4_en_deactivate_rx_ring(काष्ठा mlx4_en_priv *priv,
				काष्ठा mlx4_en_rx_ring *ring)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < ring->page_cache.index; i++) अणु
		dma_unmap_page(priv->ddev, ring->page_cache.buf[i].dma,
			       PAGE_SIZE, priv->dma_dir);
		put_page(ring->page_cache.buf[i].page);
	पूर्ण
	ring->page_cache.index = 0;
	mlx4_en_मुक्त_rx_buf(priv, ring);
	अगर (ring->stride <= TXBB_SIZE)
		ring->buf -= TXBB_SIZE;
पूर्ण


अटल पूर्णांक mlx4_en_complete_rx_desc(काष्ठा mlx4_en_priv *priv,
				    काष्ठा mlx4_en_rx_alloc *frags,
				    काष्ठा sk_buff *skb,
				    पूर्णांक length)
अणु
	स्थिर काष्ठा mlx4_en_frag_info *frag_info = priv->frag_info;
	अचिन्हित पूर्णांक truesize = 0;
	bool release = true;
	पूर्णांक nr, frag_size;
	काष्ठा page *page;
	dma_addr_t dma;

	/* Collect used fragments जबतक replacing them in the HW descriptors */
	क्रम (nr = 0;; frags++) अणु
		frag_size = min_t(पूर्णांक, length, frag_info->frag_size);

		page = frags->page;
		अगर (unlikely(!page))
			जाओ fail;

		dma = frags->dma;
		dma_sync_single_range_क्रम_cpu(priv->ddev, dma, frags->page_offset,
					      frag_size, priv->dma_dir);

		__skb_fill_page_desc(skb, nr, page, frags->page_offset,
				     frag_size);

		truesize += frag_info->frag_stride;
		अगर (frag_info->frag_stride == PAGE_SIZE / 2) अणु
			frags->page_offset ^= PAGE_SIZE / 2;
			release = page_count(page) != 1 ||
				  page_is_pfmeदो_स्मृति(page) ||
				  page_to_nid(page) != numa_mem_id();
		पूर्ण अन्यथा अगर (!priv->rx_headroom) अणु
			/* rx_headroom क्रम non XDP setup is always 0.
			 * When XDP is set, the above condition will
			 * guarantee page is always released.
			 */
			u32 sz_align = ALIGN(frag_size, SMP_CACHE_BYTES);

			frags->page_offset += sz_align;
			release = frags->page_offset + frag_info->frag_size > PAGE_SIZE;
		पूर्ण
		अगर (release) अणु
			dma_unmap_page(priv->ddev, dma, PAGE_SIZE, priv->dma_dir);
			frags->page = शून्य;
		पूर्ण अन्यथा अणु
			page_ref_inc(page);
		पूर्ण

		nr++;
		length -= frag_size;
		अगर (!length)
			अवरोध;
		frag_info++;
	पूर्ण
	skb->truesize += truesize;
	वापस nr;

fail:
	जबतक (nr > 0) अणु
		nr--;
		__skb_frag_unref(skb_shinfo(skb)->frags + nr);
	पूर्ण
	वापस 0;
पूर्ण

अटल व्योम validate_loopback(काष्ठा mlx4_en_priv *priv, व्योम *va)
अणु
	स्थिर अचिन्हित अक्षर *data = va + ETH_HLEN;
	पूर्णांक i;

	क्रम (i = 0; i < MLX4_LOOPBACK_TEST_PAYLOAD; i++) अणु
		अगर (data[i] != (अचिन्हित अक्षर)i)
			वापस;
	पूर्ण
	/* Loopback found */
	priv->loopback_ok = 1;
पूर्ण

अटल व्योम mlx4_en_refill_rx_buffers(काष्ठा mlx4_en_priv *priv,
				      काष्ठा mlx4_en_rx_ring *ring)
अणु
	u32 missing = ring->actual_size - (ring->prod - ring->cons);

	/* Try to batch allocations, but not too much. */
	अगर (missing < 8)
		वापस;
	करो अणु
		अगर (mlx4_en_prepare_rx_desc(priv, ring,
					    ring->prod & ring->size_mask,
					    GFP_ATOMIC | __GFP_MEMALLOC))
			अवरोध;
		ring->prod++;
	पूर्ण जबतक (likely(--missing));

	mlx4_en_update_rx_prod_db(ring);
पूर्ण

/* When hardware करोesn't strip the vlan, we need to calculate the checksum
 * over it and add it to the hardware's checksum calculation
 */
अटल अंतरभूत __wsum get_fixed_vlan_csum(__wsum hw_checksum,
					 काष्ठा vlan_hdr *vlanh)
अणु
	वापस csum_add(hw_checksum, *(__wsum *)vlanh);
पूर्ण

/* Although the stack expects checksum which करोesn't include the pseuकरो
 * header, the HW adds it. To address that, we are subtracting the pseuकरो
 * header checksum from the checksum value provided by the HW.
 */
अटल पूर्णांक get_fixed_ipv4_csum(__wsum hw_checksum, काष्ठा sk_buff *skb,
			       काष्ठा iphdr *iph)
अणु
	__u16 length_क्रम_csum = 0;
	__wsum csum_pseuकरो_header = 0;
	__u8 ipproto = iph->protocol;

	अगर (unlikely(ipproto == IPPROTO_SCTP))
		वापस -1;

	length_क्रम_csum = (be16_to_cpu(iph->tot_len) - (iph->ihl << 2));
	csum_pseuकरो_header = csum_tcpudp_nofold(iph->saddr, iph->daddr,
						length_क्रम_csum, ipproto, 0);
	skb->csum = csum_sub(hw_checksum, csum_pseuकरो_header);
	वापस 0;
पूर्ण

#अगर IS_ENABLED(CONFIG_IPV6)
/* In IPv6 packets, hw_checksum lacks 6 bytes from IPv6 header:
 * 4 first bytes : priority, version, flow_lbl
 * and 2 additional bytes : nexthdr, hop_limit.
 */
अटल पूर्णांक get_fixed_ipv6_csum(__wsum hw_checksum, काष्ठा sk_buff *skb,
			       काष्ठा ipv6hdr *ipv6h)
अणु
	__u8 nexthdr = ipv6h->nexthdr;
	__wsum temp;

	अगर (unlikely(nexthdr == IPPROTO_FRAGMENT ||
		     nexthdr == IPPROTO_HOPOPTS ||
		     nexthdr == IPPROTO_SCTP))
		वापस -1;

	/* priority, version, flow_lbl */
	temp = csum_add(hw_checksum, *(__wsum *)ipv6h);
	/* nexthdr and hop_limit */
	skb->csum = csum_add(temp, (__क्रमce __wsum)*(__be16 *)&ipv6h->nexthdr);
	वापस 0;
पूर्ण
#पूर्ण_अगर

#घोषणा लघु_frame(size) ((size) <= ETH_ZLEN + ETH_FCS_LEN)

/* We reach this function only after checking that any of
 * the (IPv4 | IPv6) bits are set in cqe->status.
 */
अटल पूर्णांक check_csum(काष्ठा mlx4_cqe *cqe, काष्ठा sk_buff *skb, व्योम *va,
		      netdev_features_t dev_features)
अणु
	__wsum hw_checksum = 0;
	व्योम *hdr;

	/* CQE csum करोesn't cover padding octets in लघु ethernet
	 * frames. And the pad field is appended prior to calculating
	 * and appending the FCS field.
	 *
	 * Detecting these padded frames requires to verअगरy and parse
	 * IP headers, so we simply क्रमce all those small frames to skip
	 * checksum complete.
	 */
	अगर (लघु_frame(skb->len))
		वापस -EINVAL;

	hdr = (u8 *)va + माप(काष्ठा ethhdr);
	hw_checksum = csum_unfold((__क्रमce __sum16)cqe->checksum);

	अगर (cqe->vlan_my_qpn & cpu_to_be32(MLX4_CQE_CVLAN_PRESENT_MASK) &&
	    !(dev_features & NETIF_F_HW_VLAN_CTAG_RX)) अणु
		hw_checksum = get_fixed_vlan_csum(hw_checksum, hdr);
		hdr += माप(काष्ठा vlan_hdr);
	पूर्ण

#अगर IS_ENABLED(CONFIG_IPV6)
	अगर (cqe->status & cpu_to_be16(MLX4_CQE_STATUS_IPV6))
		वापस get_fixed_ipv6_csum(hw_checksum, skb, hdr);
#पूर्ण_अगर
	वापस get_fixed_ipv4_csum(hw_checksum, skb, hdr);
पूर्ण

#अगर IS_ENABLED(CONFIG_IPV6)
#घोषणा MLX4_CQE_STATUS_IP_ANY (MLX4_CQE_STATUS_IPV4 | MLX4_CQE_STATUS_IPV6)
#अन्यथा
#घोषणा MLX4_CQE_STATUS_IP_ANY (MLX4_CQE_STATUS_IPV4)
#पूर्ण_अगर

पूर्णांक mlx4_en_process_rx_cq(काष्ठा net_device *dev, काष्ठा mlx4_en_cq *cq, पूर्णांक budget)
अणु
	काष्ठा mlx4_en_priv *priv = netdev_priv(dev);
	पूर्णांक factor = priv->cqe_factor;
	काष्ठा mlx4_en_rx_ring *ring;
	काष्ठा bpf_prog *xdp_prog;
	पूर्णांक cq_ring = cq->ring;
	bool करोorbell_pending;
	काष्ठा mlx4_cqe *cqe;
	काष्ठा xdp_buff xdp;
	पूर्णांक polled = 0;
	पूर्णांक index;

	अगर (unlikely(!priv->port_up || budget <= 0))
		वापस 0;

	ring = priv->rx_ring[cq_ring];

	/* Protect accesses to: ring->xdp_prog, priv->mac_hash list */
	rcu_पढ़ो_lock();
	xdp_prog = rcu_dereference(ring->xdp_prog);
	xdp_init_buff(&xdp, priv->frag_info[0].frag_stride, &ring->xdp_rxq);
	करोorbell_pending = false;

	/* We assume a 1:1 mapping between CQEs and Rx descriptors, so Rx
	 * descriptor offset can be deduced from the CQE index instead of
	 * पढ़ोing 'cqe->index' */
	index = cq->mcq.cons_index & ring->size_mask;
	cqe = mlx4_en_get_cqe(cq->buf, index, priv->cqe_size) + factor;

	/* Process all completed CQEs */
	जबतक (XNOR(cqe->owner_sr_opcode & MLX4_CQE_OWNER_MASK,
		    cq->mcq.cons_index & cq->size)) अणु
		काष्ठा mlx4_en_rx_alloc *frags;
		क्रमागत pkt_hash_types hash_type;
		काष्ठा sk_buff *skb;
		अचिन्हित पूर्णांक length;
		पूर्णांक ip_summed;
		व्योम *va;
		पूर्णांक nr;

		frags = ring->rx_info + (index << priv->log_rx_info);
		va = page_address(frags[0].page) + frags[0].page_offset;
		net_prefetchw(va);
		/*
		 * make sure we पढ़ो the CQE after we पढ़ो the ownership bit
		 */
		dma_rmb();

		/* Drop packet on bad receive or bad checksum */
		अगर (unlikely((cqe->owner_sr_opcode & MLX4_CQE_OPCODE_MASK) ==
						MLX4_CQE_OPCODE_ERROR)) अणु
			en_err(priv, "CQE completed in error - vendor syndrom:%d syndrom:%d\n",
			       ((काष्ठा mlx4_err_cqe *)cqe)->venकरोr_err_syndrome,
			       ((काष्ठा mlx4_err_cqe *)cqe)->syndrome);
			जाओ next;
		पूर्ण
		अगर (unlikely(cqe->badfcs_enc & MLX4_CQE_BAD_FCS)) अणु
			en_dbg(RX_ERR, priv, "Accepted frame with bad FCS\n");
			जाओ next;
		पूर्ण

		/* Check अगर we need to drop the packet अगर SRIOV is not enabled
		 * and not perक्रमming the selftest or flb disabled
		 */
		अगर (priv->flags & MLX4_EN_FLAG_RX_FILTER_NEEDED) अणु
			स्थिर काष्ठा ethhdr *ethh = va;
			dma_addr_t dma;
			/* Get poपूर्णांकer to first fragment since we haven't
			 * skb yet and cast it to ethhdr काष्ठा
			 */
			dma = frags[0].dma + frags[0].page_offset;
			dma_sync_single_क्रम_cpu(priv->ddev, dma, माप(*ethh),
						DMA_FROM_DEVICE);

			अगर (is_multicast_ether_addr(ethh->h_dest)) अणु
				काष्ठा mlx4_mac_entry *entry;
				काष्ठा hlist_head *bucket;
				अचिन्हित पूर्णांक mac_hash;

				/* Drop the packet, since HW loopback-ed it */
				mac_hash = ethh->h_source[MLX4_EN_MAC_HASH_IDX];
				bucket = &priv->mac_hash[mac_hash];
				hlist_क्रम_each_entry_rcu(entry, bucket, hlist) अणु
					अगर (ether_addr_equal_64bits(entry->mac,
								    ethh->h_source))
						जाओ next;
				पूर्ण
			पूर्ण
		पूर्ण

		अगर (unlikely(priv->validate_loopback)) अणु
			validate_loopback(priv, va);
			जाओ next;
		पूर्ण

		/*
		 * Packet is OK - process it.
		 */
		length = be32_to_cpu(cqe->byte_cnt);
		length -= ring->fcs_del;

		/* A bpf program माला_लो first chance to drop the packet. It may
		 * पढ़ो bytes but not past the end of the frag.
		 */
		अगर (xdp_prog) अणु
			dma_addr_t dma;
			व्योम *orig_data;
			u32 act;

			dma = frags[0].dma + frags[0].page_offset;
			dma_sync_single_क्रम_cpu(priv->ddev, dma,
						priv->frag_info[0].frag_size,
						DMA_FROM_DEVICE);

			xdp_prepare_buff(&xdp, va - frags[0].page_offset,
					 frags[0].page_offset, length, false);
			orig_data = xdp.data;

			act = bpf_prog_run_xdp(xdp_prog, &xdp);

			length = xdp.data_end - xdp.data;
			अगर (xdp.data != orig_data) अणु
				frags[0].page_offset = xdp.data -
					xdp.data_hard_start;
				va = xdp.data;
			पूर्ण

			चयन (act) अणु
			हाल XDP_PASS:
				अवरोध;
			हाल XDP_TX:
				अगर (likely(!mlx4_en_xmit_frame(ring, frags, priv,
							length, cq_ring,
							&करोorbell_pending))) अणु
					frags[0].page = शून्य;
					जाओ next;
				पूर्ण
				trace_xdp_exception(dev, xdp_prog, act);
				जाओ xdp_drop_no_cnt; /* Drop on xmit failure */
			शेष:
				bpf_warn_invalid_xdp_action(act);
				fallthrough;
			हाल XDP_ABORTED:
				trace_xdp_exception(dev, xdp_prog, act);
				fallthrough;
			हाल XDP_DROP:
				ring->xdp_drop++;
xdp_drop_no_cnt:
				जाओ next;
			पूर्ण
		पूर्ण

		ring->bytes += length;
		ring->packets++;

		skb = napi_get_frags(&cq->napi);
		अगर (unlikely(!skb))
			जाओ next;

		अगर (unlikely(ring->hwtstamp_rx_filter == HWTSTAMP_FILTER_ALL)) अणु
			u64 बारtamp = mlx4_en_get_cqe_ts(cqe);

			mlx4_en_fill_hwtstamps(priv->mdev, skb_hwtstamps(skb),
					       बारtamp);
		पूर्ण
		skb_record_rx_queue(skb, cq_ring);

		अगर (likely(dev->features & NETIF_F_RXCSUM)) अणु
			/* TODO: For IP non TCP/UDP packets when csum complete is
			 * not an option (not supported or any other reason) we can
			 * actually check cqe IPOK status bit and report
			 * CHECKSUM_UNNECESSARY rather than CHECKSUM_NONE
			 */
			अगर ((cqe->status & cpu_to_be16(MLX4_CQE_STATUS_TCP |
						       MLX4_CQE_STATUS_UDP)) &&
			    (cqe->status & cpu_to_be16(MLX4_CQE_STATUS_IPOK)) &&
			    cqe->checksum == cpu_to_be16(0xffff)) अणु
				bool l2_tunnel;

				l2_tunnel = (dev->hw_enc_features & NETIF_F_RXCSUM) &&
					(cqe->vlan_my_qpn & cpu_to_be32(MLX4_CQE_L2_TUNNEL));
				ip_summed = CHECKSUM_UNNECESSARY;
				hash_type = PKT_HASH_TYPE_L4;
				अगर (l2_tunnel)
					skb->csum_level = 1;
				ring->csum_ok++;
			पूर्ण अन्यथा अणु
				अगर (!(priv->flags & MLX4_EN_FLAG_RX_CSUM_NON_TCP_UDP &&
				      (cqe->status & cpu_to_be16(MLX4_CQE_STATUS_IP_ANY))))
					जाओ csum_none;
				अगर (check_csum(cqe, skb, va, dev->features))
					जाओ csum_none;
				ip_summed = CHECKSUM_COMPLETE;
				hash_type = PKT_HASH_TYPE_L3;
				ring->csum_complete++;
			पूर्ण
		पूर्ण अन्यथा अणु
csum_none:
			ip_summed = CHECKSUM_NONE;
			hash_type = PKT_HASH_TYPE_L3;
			ring->csum_none++;
		पूर्ण
		skb->ip_summed = ip_summed;
		अगर (dev->features & NETIF_F_RXHASH)
			skb_set_hash(skb,
				     be32_to_cpu(cqe->immed_rss_invalid),
				     hash_type);

		अगर ((cqe->vlan_my_qpn &
		     cpu_to_be32(MLX4_CQE_CVLAN_PRESENT_MASK)) &&
		    (dev->features & NETIF_F_HW_VLAN_CTAG_RX))
			__vlan_hwaccel_put_tag(skb, htons(ETH_P_8021Q),
					       be16_to_cpu(cqe->sl_vid));
		अन्यथा अगर ((cqe->vlan_my_qpn &
			  cpu_to_be32(MLX4_CQE_SVLAN_PRESENT_MASK)) &&
			 (dev->features & NETIF_F_HW_VLAN_STAG_RX))
			__vlan_hwaccel_put_tag(skb, htons(ETH_P_8021AD),
					       be16_to_cpu(cqe->sl_vid));

		nr = mlx4_en_complete_rx_desc(priv, frags, skb, length);
		अगर (likely(nr)) अणु
			skb_shinfo(skb)->nr_frags = nr;
			skb->len = length;
			skb->data_len = length;
			napi_gro_frags(&cq->napi);
		पूर्ण अन्यथा अणु
			__vlan_hwaccel_clear_tag(skb);
			skb_clear_hash(skb);
		पूर्ण
next:
		++cq->mcq.cons_index;
		index = (cq->mcq.cons_index) & ring->size_mask;
		cqe = mlx4_en_get_cqe(cq->buf, index, priv->cqe_size) + factor;
		अगर (unlikely(++polled == budget))
			अवरोध;
	पूर्ण

	rcu_पढ़ो_unlock();

	अगर (likely(polled)) अणु
		अगर (करोorbell_pending) अणु
			priv->tx_cq[TX_XDP][cq_ring]->xdp_busy = true;
			mlx4_en_xmit_करोorbell(priv->tx_ring[TX_XDP][cq_ring]);
		पूर्ण

		mlx4_cq_set_ci(&cq->mcq);
		wmb(); /* ensure HW sees CQ consumer beक्रमe we post new buffers */
		ring->cons = cq->mcq.cons_index;
	पूर्ण

	mlx4_en_refill_rx_buffers(priv, ring);

	वापस polled;
पूर्ण


व्योम mlx4_en_rx_irq(काष्ठा mlx4_cq *mcq)
अणु
	काष्ठा mlx4_en_cq *cq = container_of(mcq, काष्ठा mlx4_en_cq, mcq);
	काष्ठा mlx4_en_priv *priv = netdev_priv(cq->dev);

	अगर (likely(priv->port_up))
		napi_schedule_irqoff(&cq->napi);
	अन्यथा
		mlx4_en_arm_cq(priv, cq);
पूर्ण

/* Rx CQ polling - called by NAPI */
पूर्णांक mlx4_en_poll_rx_cq(काष्ठा napi_काष्ठा *napi, पूर्णांक budget)
अणु
	काष्ठा mlx4_en_cq *cq = container_of(napi, काष्ठा mlx4_en_cq, napi);
	काष्ठा net_device *dev = cq->dev;
	काष्ठा mlx4_en_priv *priv = netdev_priv(dev);
	काष्ठा mlx4_en_cq *xdp_tx_cq = शून्य;
	bool clean_complete = true;
	पूर्णांक करोne;

	अगर (!budget)
		वापस 0;

	अगर (priv->tx_ring_num[TX_XDP]) अणु
		xdp_tx_cq = priv->tx_cq[TX_XDP][cq->ring];
		अगर (xdp_tx_cq->xdp_busy) अणु
			clean_complete = mlx4_en_process_tx_cq(dev, xdp_tx_cq,
							       budget) < budget;
			xdp_tx_cq->xdp_busy = !clean_complete;
		पूर्ण
	पूर्ण

	करोne = mlx4_en_process_rx_cq(dev, cq, budget);

	/* If we used up all the quota - we're probably not करोne yet... */
	अगर (करोne == budget || !clean_complete) अणु
		पूर्णांक cpu_curr;

		/* in हाल we got here because of !clean_complete */
		करोne = budget;

		cpu_curr = smp_processor_id();

		अगर (likely(cpumask_test_cpu(cpu_curr, cq->aff_mask)))
			वापस budget;

		/* Current cpu is not according to smp_irq_affinity -
		 * probably affinity changed. Need to stop this NAPI
		 * poll, and restart it on the right CPU.
		 * Try to aव्योम वापसing a too small value (like 0),
		 * to not fool net_rx_action() and its netdev_budget
		 */
		अगर (करोne)
			करोne--;
	पूर्ण
	/* Done क्रम now */
	अगर (likely(napi_complete_करोne(napi, करोne)))
		mlx4_en_arm_cq(priv, cq);
	वापस करोne;
पूर्ण

व्योम mlx4_en_calc_rx_buf(काष्ठा net_device *dev)
अणु
	काष्ठा mlx4_en_priv *priv = netdev_priv(dev);
	पूर्णांक eff_mtu = MLX4_EN_EFF_MTU(dev->mtu);
	पूर्णांक i = 0;

	/* bpf requires buffers to be set up as 1 packet per page.
	 * This only works when num_frags == 1.
	 */
	अगर (priv->tx_ring_num[TX_XDP]) अणु
		priv->frag_info[0].frag_size = eff_mtu;
		/* This will gain efficient xdp frame recycling at the
		 * expense of more costly truesize accounting
		 */
		priv->frag_info[0].frag_stride = PAGE_SIZE;
		priv->dma_dir = PCI_DMA_BIसूचीECTIONAL;
		priv->rx_headroom = XDP_PACKET_HEADROOM;
		i = 1;
	पूर्ण अन्यथा अणु
		पूर्णांक frag_size_max = 2048, buf_size = 0;

		/* should not happen, right ? */
		अगर (eff_mtu > PAGE_SIZE + (MLX4_EN_MAX_RX_FRAGS - 1) * 2048)
			frag_size_max = PAGE_SIZE;

		जबतक (buf_size < eff_mtu) अणु
			पूर्णांक frag_stride, frag_size = eff_mtu - buf_size;
			पूर्णांक pad, nb;

			अगर (i < MLX4_EN_MAX_RX_FRAGS - 1)
				frag_size = min(frag_size, frag_size_max);

			priv->frag_info[i].frag_size = frag_size;
			frag_stride = ALIGN(frag_size, SMP_CACHE_BYTES);
			/* We can only pack 2 1536-bytes frames in on 4K page
			 * Thereक्रमe, each frame would consume more bytes (truesize)
			 */
			nb = PAGE_SIZE / frag_stride;
			pad = (PAGE_SIZE - nb * frag_stride) / nb;
			pad &= ~(SMP_CACHE_BYTES - 1);
			priv->frag_info[i].frag_stride = frag_stride + pad;

			buf_size += frag_size;
			i++;
		पूर्ण
		priv->dma_dir = PCI_DMA_FROMDEVICE;
		priv->rx_headroom = 0;
	पूर्ण

	priv->num_frags = i;
	priv->rx_skb_size = eff_mtu;
	priv->log_rx_info = ROUNDUP_LOG2(i * माप(काष्ठा mlx4_en_rx_alloc));

	en_dbg(DRV, priv, "Rx buffer scatter-list (effective-mtu:%d num_frags:%d):\n",
	       eff_mtu, priv->num_frags);
	क्रम (i = 0; i < priv->num_frags; i++) अणु
		en_dbg(DRV,
		       priv,
		       "  frag:%d - size:%d stride:%d\n",
		       i,
		       priv->frag_info[i].frag_size,
		       priv->frag_info[i].frag_stride);
	पूर्ण
पूर्ण

/* RSS related functions */

अटल पूर्णांक mlx4_en_config_rss_qp(काष्ठा mlx4_en_priv *priv, पूर्णांक qpn,
				 काष्ठा mlx4_en_rx_ring *ring,
				 क्रमागत mlx4_qp_state *state,
				 काष्ठा mlx4_qp *qp)
अणु
	काष्ठा mlx4_en_dev *mdev = priv->mdev;
	काष्ठा mlx4_qp_context *context;
	पूर्णांक err = 0;

	context = kदो_स्मृति(माप(*context), GFP_KERNEL);
	अगर (!context)
		वापस -ENOMEM;

	err = mlx4_qp_alloc(mdev->dev, qpn, qp);
	अगर (err) अणु
		en_err(priv, "Failed to allocate qp #%x\n", qpn);
		जाओ out;
	पूर्ण
	qp->event = mlx4_en_sqp_event;

	स_रखो(context, 0, माप(*context));
	mlx4_en_fill_qp_context(priv, ring->actual_size, ring->stride, 0, 0,
				qpn, ring->cqn, -1, context);
	context->db_rec_addr = cpu_to_be64(ring->wqres.db.dma);

	/* Cancel FCS removal अगर FW allows */
	अगर (mdev->dev->caps.flags & MLX4_DEV_CAP_FLAG_FCS_KEEP) अणु
		context->param3 |= cpu_to_be32(1 << 29);
		अगर (priv->dev->features & NETIF_F_RXFCS)
			ring->fcs_del = 0;
		अन्यथा
			ring->fcs_del = ETH_FCS_LEN;
	पूर्ण अन्यथा
		ring->fcs_del = 0;

	err = mlx4_qp_to_पढ़ोy(mdev->dev, &ring->wqres.mtt, context, qp, state);
	अगर (err) अणु
		mlx4_qp_हटाओ(mdev->dev, qp);
		mlx4_qp_मुक्त(mdev->dev, qp);
	पूर्ण
	mlx4_en_update_rx_prod_db(ring);
out:
	kमुक्त(context);
	वापस err;
पूर्ण

पूर्णांक mlx4_en_create_drop_qp(काष्ठा mlx4_en_priv *priv)
अणु
	पूर्णांक err;
	u32 qpn;

	err = mlx4_qp_reserve_range(priv->mdev->dev, 1, 1, &qpn,
				    MLX4_RESERVE_A0_QP,
				    MLX4_RES_USAGE_DRIVER);
	अगर (err) अणु
		en_err(priv, "Failed reserving drop qpn\n");
		वापस err;
	पूर्ण
	err = mlx4_qp_alloc(priv->mdev->dev, qpn, &priv->drop_qp);
	अगर (err) अणु
		en_err(priv, "Failed allocating drop qp\n");
		mlx4_qp_release_range(priv->mdev->dev, qpn, 1);
		वापस err;
	पूर्ण

	वापस 0;
पूर्ण

व्योम mlx4_en_destroy_drop_qp(काष्ठा mlx4_en_priv *priv)
अणु
	u32 qpn;

	qpn = priv->drop_qp.qpn;
	mlx4_qp_हटाओ(priv->mdev->dev, &priv->drop_qp);
	mlx4_qp_मुक्त(priv->mdev->dev, &priv->drop_qp);
	mlx4_qp_release_range(priv->mdev->dev, qpn, 1);
पूर्ण

/* Allocate rx qp's and configure them according to rss map */
पूर्णांक mlx4_en_config_rss_steer(काष्ठा mlx4_en_priv *priv)
अणु
	काष्ठा mlx4_en_dev *mdev = priv->mdev;
	काष्ठा mlx4_en_rss_map *rss_map = &priv->rss_map;
	काष्ठा mlx4_qp_context context;
	काष्ठा mlx4_rss_context *rss_context;
	पूर्णांक rss_rings;
	व्योम *ptr;
	u8 rss_mask = (MLX4_RSS_IPV4 | MLX4_RSS_TCP_IPV4 | MLX4_RSS_IPV6 |
			MLX4_RSS_TCP_IPV6);
	पूर्णांक i, qpn;
	पूर्णांक err = 0;
	पूर्णांक good_qps = 0;
	u8 flags;

	en_dbg(DRV, priv, "Configuring rss steering\n");

	flags = priv->rx_ring_num == 1 ? MLX4_RESERVE_A0_QP : 0;
	err = mlx4_qp_reserve_range(mdev->dev, priv->rx_ring_num,
				    priv->rx_ring_num,
				    &rss_map->base_qpn, flags,
				    MLX4_RES_USAGE_DRIVER);
	अगर (err) अणु
		en_err(priv, "Failed reserving %d qps\n", priv->rx_ring_num);
		वापस err;
	पूर्ण

	क्रम (i = 0; i < priv->rx_ring_num; i++) अणु
		qpn = rss_map->base_qpn + i;
		err = mlx4_en_config_rss_qp(priv, qpn, priv->rx_ring[i],
					    &rss_map->state[i],
					    &rss_map->qps[i]);
		अगर (err)
			जाओ rss_err;

		++good_qps;
	पूर्ण

	अगर (priv->rx_ring_num == 1) अणु
		rss_map->indir_qp = &rss_map->qps[0];
		priv->base_qpn = rss_map->indir_qp->qpn;
		en_info(priv, "Optimized Non-RSS steering\n");
		वापस 0;
	पूर्ण

	rss_map->indir_qp = kzalloc(माप(*rss_map->indir_qp), GFP_KERNEL);
	अगर (!rss_map->indir_qp) अणु
		err = -ENOMEM;
		जाओ rss_err;
	पूर्ण

	/* Configure RSS indirection qp */
	err = mlx4_qp_alloc(mdev->dev, priv->base_qpn, rss_map->indir_qp);
	अगर (err) अणु
		en_err(priv, "Failed to allocate RSS indirection QP\n");
		जाओ qp_alloc_err;
	पूर्ण

	rss_map->indir_qp->event = mlx4_en_sqp_event;
	mlx4_en_fill_qp_context(priv, 0, 0, 0, 1, priv->base_qpn,
				priv->rx_ring[0]->cqn, -1, &context);

	अगर (!priv->prof->rss_rings || priv->prof->rss_rings > priv->rx_ring_num)
		rss_rings = priv->rx_ring_num;
	अन्यथा
		rss_rings = priv->prof->rss_rings;

	ptr = ((व्योम *) &context) + दुरत्व(काष्ठा mlx4_qp_context, pri_path)
					+ MLX4_RSS_OFFSET_IN_QPC_PRI_PATH;
	rss_context = ptr;
	rss_context->base_qpn = cpu_to_be32(ilog2(rss_rings) << 24 |
					    (rss_map->base_qpn));
	rss_context->शेष_qpn = cpu_to_be32(rss_map->base_qpn);
	अगर (priv->mdev->profile.udp_rss) अणु
		rss_mask |=  MLX4_RSS_UDP_IPV4 | MLX4_RSS_UDP_IPV6;
		rss_context->base_qpn_udp = rss_context->शेष_qpn;
	पूर्ण

	अगर (mdev->dev->caps.tunnel_offload_mode == MLX4_TUNNEL_OFFLOAD_MODE_VXLAN) अणु
		en_info(priv, "Setting RSS context tunnel type to RSS on inner headers\n");
		rss_mask |= MLX4_RSS_BY_INNER_HEADERS;
	पूर्ण

	rss_context->flags = rss_mask;
	rss_context->hash_fn = MLX4_RSS_HASH_TOP;
	अगर (priv->rss_hash_fn == ETH_RSS_HASH_XOR) अणु
		rss_context->hash_fn = MLX4_RSS_HASH_XOR;
	पूर्ण अन्यथा अगर (priv->rss_hash_fn == ETH_RSS_HASH_TOP) अणु
		rss_context->hash_fn = MLX4_RSS_HASH_TOP;
		स_नकल(rss_context->rss_key, priv->rss_key,
		       MLX4_EN_RSS_KEY_SIZE);
	पूर्ण अन्यथा अणु
		en_err(priv, "Unknown RSS hash function requested\n");
		err = -EINVAL;
		जाओ indir_err;
	पूर्ण

	err = mlx4_qp_to_पढ़ोy(mdev->dev, &priv->res.mtt, &context,
			       rss_map->indir_qp, &rss_map->indir_state);
	अगर (err)
		जाओ indir_err;

	वापस 0;

indir_err:
	mlx4_qp_modअगरy(mdev->dev, शून्य, rss_map->indir_state,
		       MLX4_QP_STATE_RST, शून्य, 0, 0, rss_map->indir_qp);
	mlx4_qp_हटाओ(mdev->dev, rss_map->indir_qp);
	mlx4_qp_मुक्त(mdev->dev, rss_map->indir_qp);
qp_alloc_err:
	kमुक्त(rss_map->indir_qp);
	rss_map->indir_qp = शून्य;
rss_err:
	क्रम (i = 0; i < good_qps; i++) अणु
		mlx4_qp_modअगरy(mdev->dev, शून्य, rss_map->state[i],
			       MLX4_QP_STATE_RST, शून्य, 0, 0, &rss_map->qps[i]);
		mlx4_qp_हटाओ(mdev->dev, &rss_map->qps[i]);
		mlx4_qp_मुक्त(mdev->dev, &rss_map->qps[i]);
	पूर्ण
	mlx4_qp_release_range(mdev->dev, rss_map->base_qpn, priv->rx_ring_num);
	वापस err;
पूर्ण

व्योम mlx4_en_release_rss_steer(काष्ठा mlx4_en_priv *priv)
अणु
	काष्ठा mlx4_en_dev *mdev = priv->mdev;
	काष्ठा mlx4_en_rss_map *rss_map = &priv->rss_map;
	पूर्णांक i;

	अगर (priv->rx_ring_num > 1) अणु
		mlx4_qp_modअगरy(mdev->dev, शून्य, rss_map->indir_state,
			       MLX4_QP_STATE_RST, शून्य, 0, 0,
			       rss_map->indir_qp);
		mlx4_qp_हटाओ(mdev->dev, rss_map->indir_qp);
		mlx4_qp_मुक्त(mdev->dev, rss_map->indir_qp);
		kमुक्त(rss_map->indir_qp);
		rss_map->indir_qp = शून्य;
	पूर्ण

	क्रम (i = 0; i < priv->rx_ring_num; i++) अणु
		mlx4_qp_modअगरy(mdev->dev, शून्य, rss_map->state[i],
			       MLX4_QP_STATE_RST, शून्य, 0, 0, &rss_map->qps[i]);
		mlx4_qp_हटाओ(mdev->dev, &rss_map->qps[i]);
		mlx4_qp_मुक्त(mdev->dev, &rss_map->qps[i]);
	पूर्ण
	mlx4_qp_release_range(mdev->dev, rss_map->base_qpn, priv->rx_ring_num);
पूर्ण
