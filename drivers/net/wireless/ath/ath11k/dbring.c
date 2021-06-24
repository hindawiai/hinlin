<शैली गुरु>
// SPDX-License-Identअगरier: BSD-3-Clause-Clear
/*
 * Copyright (c) 2019-2020 The Linux Foundation. All rights reserved.
 */

#समावेश "core.h"
#समावेश "debug.h"

अटल पूर्णांक ath11k_dbring_bufs_replenish(काष्ठा ath11k *ar,
					काष्ठा ath11k_dbring *ring,
					काष्ठा ath11k_dbring_element *buff,
					gfp_t gfp)
अणु
	काष्ठा ath11k_base *ab = ar->ab;
	काष्ठा hal_srng *srng;
	dma_addr_t paddr;
	व्योम *ptr_aligned, *ptr_unaligned, *desc;
	पूर्णांक ret;
	पूर्णांक buf_id;
	u32 cookie;

	srng = &ab->hal.srng_list[ring->refill_srng.ring_id];

	lockdep_निश्चित_held(&srng->lock);

	ath11k_hal_srng_access_begin(ab, srng);

	ptr_unaligned = buff->payload;
	ptr_aligned = PTR_ALIGN(ptr_unaligned, ring->buf_align);
	paddr = dma_map_single(ab->dev, ptr_aligned, ring->buf_sz,
			       DMA_FROM_DEVICE);

	ret = dma_mapping_error(ab->dev, paddr);
	अगर (ret)
		जाओ err;

	spin_lock_bh(&ring->idr_lock);
	buf_id = idr_alloc(&ring->bufs_idr, buff, 0, ring->bufs_max, gfp);
	spin_unlock_bh(&ring->idr_lock);
	अगर (buf_id < 0) अणु
		ret = -ENOBUFS;
		जाओ err_dma_unmap;
	पूर्ण

	desc = ath11k_hal_srng_src_get_next_entry(ab, srng);
	अगर (!desc) अणु
		ret = -ENOENT;
		जाओ err_idr_हटाओ;
	पूर्ण

	buff->paddr = paddr;

	cookie = FIELD_PREP(DP_RXDMA_BUF_COOKIE_PDEV_ID, ar->pdev_idx) |
		 FIELD_PREP(DP_RXDMA_BUF_COOKIE_BUF_ID, buf_id);

	ath11k_hal_rx_buf_addr_info_set(desc, paddr, cookie, 0);

	ath11k_hal_srng_access_end(ab, srng);

	वापस 0;

err_idr_हटाओ:
	spin_lock_bh(&ring->idr_lock);
	idr_हटाओ(&ring->bufs_idr, buf_id);
	spin_unlock_bh(&ring->idr_lock);
err_dma_unmap:
	dma_unmap_single(ab->dev, paddr, ring->buf_sz,
			 DMA_FROM_DEVICE);
err:
	ath11k_hal_srng_access_end(ab, srng);
	वापस ret;
पूर्ण

अटल पूर्णांक ath11k_dbring_fill_bufs(काष्ठा ath11k *ar,
				   काष्ठा ath11k_dbring *ring,
				   gfp_t gfp)
अणु
	काष्ठा ath11k_dbring_element *buff;
	काष्ठा hal_srng *srng;
	पूर्णांक num_reमुख्य, req_entries, num_मुक्त;
	u32 align;
	पूर्णांक size, ret;

	srng = &ar->ab->hal.srng_list[ring->refill_srng.ring_id];

	spin_lock_bh(&srng->lock);

	num_मुक्त = ath11k_hal_srng_src_num_मुक्त(ar->ab, srng, true);
	req_entries = min(num_मुक्त, ring->bufs_max);
	num_reमुख्य = req_entries;
	align = ring->buf_align;
	size = माप(*buff) + ring->buf_sz + align - 1;

	जबतक (num_reमुख्य > 0) अणु
		buff = kzalloc(size, gfp);
		अगर (!buff)
			अवरोध;

		ret = ath11k_dbring_bufs_replenish(ar, ring, buff, gfp);
		अगर (ret) अणु
			ath11k_warn(ar->ab, "failed to replenish db ring num_remain %d req_ent %d\n",
				    num_reमुख्य, req_entries);
			kमुक्त(buff);
			अवरोध;
		पूर्ण
		num_reमुख्य--;
	पूर्ण

	spin_unlock_bh(&srng->lock);

	वापस num_reमुख्य;
पूर्ण

पूर्णांक ath11k_dbring_wmi_cfg_setup(काष्ठा ath11k *ar,
				काष्ठा ath11k_dbring *ring,
				क्रमागत wmi_direct_buffer_module id)
अणु
	काष्ठा ath11k_wmi_pdev_dma_ring_cfg_req_cmd param = अणु0पूर्ण;
	पूर्णांक ret;

	अगर (id >= WMI_सूचीECT_BUF_MAX)
		वापस -EINVAL;

	param.pdev_id		= DP_SW2HW_MACID(ring->pdev_id);
	param.module_id		= id;
	param.base_paddr_lo	= lower_32_bits(ring->refill_srng.paddr);
	param.base_paddr_hi	= upper_32_bits(ring->refill_srng.paddr);
	param.head_idx_paddr_lo	= lower_32_bits(ring->hp_addr);
	param.head_idx_paddr_hi = upper_32_bits(ring->hp_addr);
	param.tail_idx_paddr_lo = lower_32_bits(ring->tp_addr);
	param.tail_idx_paddr_hi = upper_32_bits(ring->tp_addr);
	param.num_elems		= ring->bufs_max;
	param.buf_size		= ring->buf_sz;
	param.num_resp_per_event = ring->num_resp_per_event;
	param.event_समयout_ms	= ring->event_समयout_ms;

	ret = ath11k_wmi_pdev_dma_ring_cfg(ar, &param);
	अगर (ret) अणु
		ath11k_warn(ar->ab, "failed to setup db ring cfg\n");
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

पूर्णांक ath11k_dbring_set_cfg(काष्ठा ath11k *ar, काष्ठा ath11k_dbring *ring,
			  u32 num_resp_per_event, u32 event_समयout_ms,
			  पूर्णांक (*handler)(काष्ठा ath11k *,
					 काष्ठा ath11k_dbring_data *))
अणु
	अगर (WARN_ON(!ring))
		वापस -EINVAL;

	ring->num_resp_per_event = num_resp_per_event;
	ring->event_समयout_ms = event_समयout_ms;
	ring->handler = handler;

	वापस 0;
पूर्ण

पूर्णांक ath11k_dbring_buf_setup(काष्ठा ath11k *ar,
			    काष्ठा ath11k_dbring *ring,
			    काष्ठा ath11k_dbring_cap *db_cap)
अणु
	काष्ठा ath11k_base *ab = ar->ab;
	काष्ठा hal_srng *srng;
	पूर्णांक ret;

	srng = &ab->hal.srng_list[ring->refill_srng.ring_id];
	ring->bufs_max = ring->refill_srng.size /
		ath11k_hal_srng_get_entrysize(ab, HAL_RXDMA_सूची_BUF);

	ring->buf_sz = db_cap->min_buf_sz;
	ring->buf_align = db_cap->min_buf_align;
	ring->pdev_id = db_cap->pdev_id;
	ring->hp_addr = ath11k_hal_srng_get_hp_addr(ar->ab, srng);
	ring->tp_addr = ath11k_hal_srng_get_tp_addr(ar->ab, srng);

	ret = ath11k_dbring_fill_bufs(ar, ring, GFP_KERNEL);

	वापस ret;
पूर्ण

पूर्णांक ath11k_dbring_srng_setup(काष्ठा ath11k *ar, काष्ठा ath11k_dbring *ring,
			     पूर्णांक ring_num, पूर्णांक num_entries)
अणु
	पूर्णांक ret;

	ret = ath11k_dp_srng_setup(ar->ab, &ring->refill_srng, HAL_RXDMA_सूची_BUF,
				   ring_num, ar->pdev_idx, num_entries);
	अगर (ret < 0) अणु
		ath11k_warn(ar->ab, "failed to setup srng: %d ring_id %d\n",
			    ret, ring_num);
		जाओ err;
	पूर्ण

	वापस 0;
err:
	ath11k_dp_srng_cleanup(ar->ab, &ring->refill_srng);
	वापस ret;
पूर्ण

पूर्णांक ath11k_dbring_get_cap(काष्ठा ath11k_base *ab,
			  u8 pdev_idx,
			  क्रमागत wmi_direct_buffer_module id,
			  काष्ठा ath11k_dbring_cap *db_cap)
अणु
	पूर्णांक i;

	अगर (!ab->num_db_cap || !ab->db_caps)
		वापस -ENOENT;

	अगर (id >= WMI_सूचीECT_BUF_MAX)
		वापस -EINVAL;

	क्रम (i = 0; i < ab->num_db_cap; i++) अणु
		अगर (pdev_idx == ab->db_caps[i].pdev_id &&
		    id == ab->db_caps[i].id) अणु
			*db_cap = ab->db_caps[i];

			वापस 0;
		पूर्ण
	पूर्ण

	वापस -ENOENT;
पूर्ण

पूर्णांक ath11k_dbring_buffer_release_event(काष्ठा ath11k_base *ab,
				       काष्ठा ath11k_dbring_buf_release_event *ev)
अणु
	काष्ठा ath11k_dbring *ring;
	काष्ठा hal_srng *srng;
	काष्ठा ath11k *ar;
	काष्ठा ath11k_dbring_element *buff;
	काष्ठा ath11k_dbring_data handler_data;
	काष्ठा ath11k_buffer_addr desc;
	u8 *vaddr_unalign;
	u32 num_entry, num_buff_reaped;
	u8 pdev_idx, rbm;
	u32 cookie;
	पूर्णांक buf_id;
	पूर्णांक size;
	dma_addr_t paddr;
	पूर्णांक ret = 0;

	pdev_idx = ev->fixed.pdev_id;

	अगर (pdev_idx >= ab->num_radios) अणु
		ath11k_warn(ab, "Invalid pdev id %d\n", pdev_idx);
		वापस -EINVAL;
	पूर्ण

	अगर (ev->fixed.num_buf_release_entry !=
	    ev->fixed.num_meta_data_entry) अणु
		ath11k_warn(ab, "Buffer entry %d mismatch meta entry %d\n",
			    ev->fixed.num_buf_release_entry,
			    ev->fixed.num_meta_data_entry);
		वापस -EINVAL;
	पूर्ण

	ar = ab->pdevs[pdev_idx].ar;

	rcu_पढ़ो_lock();
	अगर (!rcu_dereference(ab->pdevs_active[pdev_idx])) अणु
		ret = -EINVAL;
		जाओ rcu_unlock;
	पूर्ण

	चयन (ev->fixed.module_id) अणु
	हाल WMI_सूचीECT_BUF_SPECTRAL:
		ring = ath11k_spectral_get_dbring(ar);
		अवरोध;
	शेष:
		ring = शून्य;
		ath11k_warn(ab, "Recv dma buffer release ev on unsupp module %d\n",
			    ev->fixed.module_id);
		अवरोध;
	पूर्ण

	अगर (!ring) अणु
		ret = -EINVAL;
		जाओ rcu_unlock;
	पूर्ण

	srng = &ab->hal.srng_list[ring->refill_srng.ring_id];
	num_entry = ev->fixed.num_buf_release_entry;
	size = माप(*buff) + ring->buf_sz + ring->buf_align - 1;
	num_buff_reaped = 0;

	spin_lock_bh(&srng->lock);

	जबतक (num_buff_reaped < num_entry) अणु
		desc.info0 = ev->buf_entry[num_buff_reaped].paddr_lo;
		desc.info1 = ev->buf_entry[num_buff_reaped].paddr_hi;
		handler_data.meta = ev->meta_data[num_buff_reaped];

		num_buff_reaped++;

		ath11k_hal_rx_buf_addr_info_get(&desc, &paddr, &cookie, &rbm);

		buf_id = FIELD_GET(DP_RXDMA_BUF_COOKIE_BUF_ID, cookie);

		spin_lock_bh(&ring->idr_lock);
		buff = idr_find(&ring->bufs_idr, buf_id);
		अगर (!buff) अणु
			spin_unlock_bh(&ring->idr_lock);
			जारी;
		पूर्ण
		idr_हटाओ(&ring->bufs_idr, buf_id);
		spin_unlock_bh(&ring->idr_lock);

		dma_unmap_single(ab->dev, buff->paddr, ring->buf_sz,
				 DMA_FROM_DEVICE);

		अगर (ring->handler) अणु
			vaddr_unalign = buff->payload;
			handler_data.data = PTR_ALIGN(vaddr_unalign,
						      ring->buf_align);
			handler_data.data_sz = ring->buf_sz;

			ring->handler(ar, &handler_data);
		पूर्ण

		स_रखो(buff, 0, size);
		ath11k_dbring_bufs_replenish(ar, ring, buff, GFP_ATOMIC);
	पूर्ण

	spin_unlock_bh(&srng->lock);

rcu_unlock:
	rcu_पढ़ो_unlock();

	वापस ret;
पूर्ण

व्योम ath11k_dbring_srng_cleanup(काष्ठा ath11k *ar, काष्ठा ath11k_dbring *ring)
अणु
	ath11k_dp_srng_cleanup(ar->ab, &ring->refill_srng);
पूर्ण

व्योम ath11k_dbring_buf_cleanup(काष्ठा ath11k *ar, काष्ठा ath11k_dbring *ring)
अणु
	काष्ठा ath11k_dbring_element *buff;
	पूर्णांक buf_id;

	spin_lock_bh(&ring->idr_lock);
	idr_क्रम_each_entry(&ring->bufs_idr, buff, buf_id) अणु
		idr_हटाओ(&ring->bufs_idr, buf_id);
		dma_unmap_single(ar->ab->dev, buff->paddr,
				 ring->buf_sz, DMA_FROM_DEVICE);
		kमुक्त(buff);
	पूर्ण

	idr_destroy(&ring->bufs_idr);
	spin_unlock_bh(&ring->idr_lock);
पूर्ण
