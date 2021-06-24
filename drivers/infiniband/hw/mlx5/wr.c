<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0 OR Linux-OpenIB
/*
 * Copyright (c) 2020, Mellanox Technologies inc. All rights reserved.
 */

#समावेश <linux/gfp.h>
#समावेश <linux/mlx5/qp.h>
#समावेश <linux/mlx5/driver.h>
#समावेश "wr.h"

अटल स्थिर u32 mlx5_ib_opcode[] = अणु
	[IB_WR_SEND]				= MLX5_OPCODE_SEND,
	[IB_WR_LSO]				= MLX5_OPCODE_LSO,
	[IB_WR_SEND_WITH_IMM]			= MLX5_OPCODE_SEND_IMM,
	[IB_WR_RDMA_WRITE]			= MLX5_OPCODE_RDMA_WRITE,
	[IB_WR_RDMA_WRITE_WITH_IMM]		= MLX5_OPCODE_RDMA_WRITE_IMM,
	[IB_WR_RDMA_READ]			= MLX5_OPCODE_RDMA_READ,
	[IB_WR_ATOMIC_CMP_AND_SWP]		= MLX5_OPCODE_ATOMIC_CS,
	[IB_WR_ATOMIC_FETCH_AND_ADD]		= MLX5_OPCODE_ATOMIC_FA,
	[IB_WR_SEND_WITH_INV]			= MLX5_OPCODE_SEND_INVAL,
	[IB_WR_LOCAL_INV]			= MLX5_OPCODE_UMR,
	[IB_WR_REG_MR]				= MLX5_OPCODE_UMR,
	[IB_WR_MASKED_ATOMIC_CMP_AND_SWP]	= MLX5_OPCODE_ATOMIC_MASKED_CS,
	[IB_WR_MASKED_ATOMIC_FETCH_AND_ADD]	= MLX5_OPCODE_ATOMIC_MASKED_FA,
	[MLX5_IB_WR_UMR]			= MLX5_OPCODE_UMR,
पूर्ण;

/* handle_post_send_edge - Check अगर we get to SQ edge. If yes, update to the
 * next nearby edge and get new address translation क्रम current WQE position.
 * @sq - SQ buffer.
 * @seg: Current WQE position (16B aligned).
 * @wqe_sz: Total current WQE size [16B].
 * @cur_edge: Updated current edge.
 */
अटल अंतरभूत व्योम handle_post_send_edge(काष्ठा mlx5_ib_wq *sq, व्योम **seg,
					 u32 wqe_sz, व्योम **cur_edge)
अणु
	u32 idx;

	अगर (likely(*seg != *cur_edge))
		वापस;

	idx = (sq->cur_post + (wqe_sz >> 2)) & (sq->wqe_cnt - 1);
	*cur_edge = get_sq_edge(sq, idx);

	*seg = mlx5_frag_buf_get_wqe(&sq->fbc, idx);
पूर्ण

/* स_नकल_send_wqe - copy data from src to WQE and update the relevant WQ's
 * poपूर्णांकers. At the end @seg is aligned to 16B regardless the copied size.
 * @sq - SQ buffer.
 * @cur_edge: Updated current edge.
 * @seg: Current WQE position (16B aligned).
 * @wqe_sz: Total current WQE size [16B].
 * @src: Poपूर्णांकer to copy from.
 * @n: Number of bytes to copy.
 */
अटल अंतरभूत व्योम स_नकल_send_wqe(काष्ठा mlx5_ib_wq *sq, व्योम **cur_edge,
				   व्योम **seg, u32 *wqe_sz, स्थिर व्योम *src,
				   माप_प्रकार n)
अणु
	जबतक (likely(n)) अणु
		माप_प्रकार leftlen = *cur_edge - *seg;
		माप_प्रकार copysz = min_t(माप_प्रकार, leftlen, n);
		माप_प्रकार stride;

		स_नकल(*seg, src, copysz);

		n -= copysz;
		src += copysz;
		stride = !n ? ALIGN(copysz, 16) : copysz;
		*seg += stride;
		*wqe_sz += stride >> 4;
		handle_post_send_edge(sq, seg, *wqe_sz, cur_edge);
	पूर्ण
पूर्ण

अटल पूर्णांक mlx5_wq_overflow(काष्ठा mlx5_ib_wq *wq, पूर्णांक nreq,
			    काष्ठा ib_cq *ib_cq)
अणु
	काष्ठा mlx5_ib_cq *cq;
	अचिन्हित पूर्णांक cur;

	cur = wq->head - wq->tail;
	अगर (likely(cur + nreq < wq->max_post))
		वापस 0;

	cq = to_mcq(ib_cq);
	spin_lock(&cq->lock);
	cur = wq->head - wq->tail;
	spin_unlock(&cq->lock);

	वापस cur + nreq >= wq->max_post;
पूर्ण

अटल __always_अंतरभूत व्योम set_raddr_seg(काष्ठा mlx5_wqe_raddr_seg *rseg,
					  u64 remote_addr, u32 rkey)
अणु
	rseg->raddr    = cpu_to_be64(remote_addr);
	rseg->rkey     = cpu_to_be32(rkey);
	rseg->reserved = 0;
पूर्ण

अटल व्योम set_eth_seg(स्थिर काष्ठा ib_send_wr *wr, काष्ठा mlx5_ib_qp *qp,
			व्योम **seg, पूर्णांक *size, व्योम **cur_edge)
अणु
	काष्ठा mlx5_wqe_eth_seg *eseg = *seg;

	स_रखो(eseg, 0, माप(काष्ठा mlx5_wqe_eth_seg));

	अगर (wr->send_flags & IB_SEND_IP_CSUM)
		eseg->cs_flags = MLX5_ETH_WQE_L3_CSUM |
				 MLX5_ETH_WQE_L4_CSUM;

	अगर (wr->opcode == IB_WR_LSO) अणु
		काष्ठा ib_ud_wr *ud_wr = container_of(wr, काष्ठा ib_ud_wr, wr);
		माप_प्रकार left, copysz;
		व्योम *pdata = ud_wr->header;
		माप_प्रकार stride;

		left = ud_wr->hlen;
		eseg->mss = cpu_to_be16(ud_wr->mss);
		eseg->अंतरभूत_hdr.sz = cpu_to_be16(left);

		/* स_नकल_send_wqe should get a 16B align address. Hence, we
		 * first copy up to the current edge and then, अगर needed,
		 * जारी to स_नकल_send_wqe.
		 */
		copysz = min_t(u64, *cur_edge - (व्योम *)eseg->अंतरभूत_hdr.start,
			       left);
		स_नकल(eseg->अंतरभूत_hdr.start, pdata, copysz);
		stride = ALIGN(माप(काष्ठा mlx5_wqe_eth_seg) -
			       माप(eseg->अंतरभूत_hdr.start) + copysz, 16);
		*size += stride / 16;
		*seg += stride;

		अगर (copysz < left) अणु
			handle_post_send_edge(&qp->sq, seg, *size, cur_edge);
			left -= copysz;
			pdata += copysz;
			स_नकल_send_wqe(&qp->sq, cur_edge, seg, size, pdata,
					left);
		पूर्ण

		वापस;
	पूर्ण

	*seg += माप(काष्ठा mlx5_wqe_eth_seg);
	*size += माप(काष्ठा mlx5_wqe_eth_seg) / 16;
पूर्ण

अटल व्योम set_datagram_seg(काष्ठा mlx5_wqe_datagram_seg *dseg,
			     स्थिर काष्ठा ib_send_wr *wr)
अणु
	स_नकल(&dseg->av, &to_mah(ud_wr(wr)->ah)->av, माप(काष्ठा mlx5_av));
	dseg->av.dqp_dct =
		cpu_to_be32(ud_wr(wr)->remote_qpn | MLX5_EXTENDED_UD_AV);
	dseg->av.key.qkey.qkey = cpu_to_be32(ud_wr(wr)->remote_qkey);
पूर्ण

अटल व्योम set_data_ptr_seg(काष्ठा mlx5_wqe_data_seg *dseg, काष्ठा ib_sge *sg)
अणु
	dseg->byte_count = cpu_to_be32(sg->length);
	dseg->lkey       = cpu_to_be32(sg->lkey);
	dseg->addr       = cpu_to_be64(sg->addr);
पूर्ण

अटल u64 get_xlt_octo(u64 bytes)
अणु
	वापस ALIGN(bytes, MLX5_IB_UMR_XLT_ALIGNMENT) /
	       MLX5_IB_UMR_OCTOWORD;
पूर्ण

अटल __be64 frwr_mkey_mask(bool atomic)
अणु
	u64 result;

	result = MLX5_MKEY_MASK_LEN		|
		MLX5_MKEY_MASK_PAGE_SIZE	|
		MLX5_MKEY_MASK_START_ADDR	|
		MLX5_MKEY_MASK_EN_RINVAL	|
		MLX5_MKEY_MASK_KEY		|
		MLX5_MKEY_MASK_LR		|
		MLX5_MKEY_MASK_LW		|
		MLX5_MKEY_MASK_RR		|
		MLX5_MKEY_MASK_RW		|
		MLX5_MKEY_MASK_SMALL_FENCE	|
		MLX5_MKEY_MASK_FREE;

	अगर (atomic)
		result |= MLX5_MKEY_MASK_A;

	वापस cpu_to_be64(result);
पूर्ण

अटल __be64 sig_mkey_mask(व्योम)
अणु
	u64 result;

	result = MLX5_MKEY_MASK_LEN		|
		MLX5_MKEY_MASK_PAGE_SIZE	|
		MLX5_MKEY_MASK_START_ADDR	|
		MLX5_MKEY_MASK_EN_SIGERR	|
		MLX5_MKEY_MASK_EN_RINVAL	|
		MLX5_MKEY_MASK_KEY		|
		MLX5_MKEY_MASK_LR		|
		MLX5_MKEY_MASK_LW		|
		MLX5_MKEY_MASK_RR		|
		MLX5_MKEY_MASK_RW		|
		MLX5_MKEY_MASK_SMALL_FENCE	|
		MLX5_MKEY_MASK_FREE		|
		MLX5_MKEY_MASK_BSF_EN;

	वापस cpu_to_be64(result);
पूर्ण

अटल व्योम set_reg_umr_seg(काष्ठा mlx5_wqe_umr_ctrl_seg *umr,
			    काष्ठा mlx5_ib_mr *mr, u8 flags, bool atomic)
अणु
	पूर्णांक size = (mr->ndescs + mr->meta_ndescs) * mr->desc_size;

	स_रखो(umr, 0, माप(*umr));

	umr->flags = flags;
	umr->xlt_octowords = cpu_to_be16(get_xlt_octo(size));
	umr->mkey_mask = frwr_mkey_mask(atomic);
पूर्ण

अटल व्योम set_linv_umr_seg(काष्ठा mlx5_wqe_umr_ctrl_seg *umr)
अणु
	स_रखो(umr, 0, माप(*umr));
	umr->mkey_mask = cpu_to_be64(MLX5_MKEY_MASK_FREE);
	umr->flags = MLX5_UMR_INLINE;
पूर्ण

अटल __be64 get_umr_enable_mr_mask(व्योम)
अणु
	u64 result;

	result = MLX5_MKEY_MASK_KEY |
		 MLX5_MKEY_MASK_FREE;

	वापस cpu_to_be64(result);
पूर्ण

अटल __be64 get_umr_disable_mr_mask(व्योम)
अणु
	u64 result;

	result = MLX5_MKEY_MASK_FREE;

	वापस cpu_to_be64(result);
पूर्ण

अटल __be64 get_umr_update_translation_mask(व्योम)
अणु
	u64 result;

	result = MLX5_MKEY_MASK_LEN |
		 MLX5_MKEY_MASK_PAGE_SIZE |
		 MLX5_MKEY_MASK_START_ADDR;

	वापस cpu_to_be64(result);
पूर्ण

अटल __be64 get_umr_update_access_mask(पूर्णांक atomic,
					 पूर्णांक relaxed_ordering_ग_लिखो,
					 पूर्णांक relaxed_ordering_पढ़ो)
अणु
	u64 result;

	result = MLX5_MKEY_MASK_LR |
		 MLX5_MKEY_MASK_LW |
		 MLX5_MKEY_MASK_RR |
		 MLX5_MKEY_MASK_RW;

	अगर (atomic)
		result |= MLX5_MKEY_MASK_A;

	अगर (relaxed_ordering_ग_लिखो)
		result |= MLX5_MKEY_MASK_RELAXED_ORDERING_WRITE;

	अगर (relaxed_ordering_पढ़ो)
		result |= MLX5_MKEY_MASK_RELAXED_ORDERING_READ;

	वापस cpu_to_be64(result);
पूर्ण

अटल __be64 get_umr_update_pd_mask(व्योम)
अणु
	u64 result;

	result = MLX5_MKEY_MASK_PD;

	वापस cpu_to_be64(result);
पूर्ण

अटल पूर्णांक umr_check_mkey_mask(काष्ठा mlx5_ib_dev *dev, u64 mask)
अणु
	अगर (mask & MLX5_MKEY_MASK_PAGE_SIZE &&
	    MLX5_CAP_GEN(dev->mdev, umr_modअगरy_entity_size_disabled))
		वापस -EPERM;

	अगर (mask & MLX5_MKEY_MASK_A &&
	    MLX5_CAP_GEN(dev->mdev, umr_modअगरy_atomic_disabled))
		वापस -EPERM;

	अगर (mask & MLX5_MKEY_MASK_RELAXED_ORDERING_WRITE &&
	    !MLX5_CAP_GEN(dev->mdev, relaxed_ordering_ग_लिखो_umr))
		वापस -EPERM;

	अगर (mask & MLX5_MKEY_MASK_RELAXED_ORDERING_READ &&
	    !MLX5_CAP_GEN(dev->mdev, relaxed_ordering_पढ़ो_umr))
		वापस -EPERM;

	वापस 0;
पूर्ण

अटल पूर्णांक set_reg_umr_segment(काष्ठा mlx5_ib_dev *dev,
			       काष्ठा mlx5_wqe_umr_ctrl_seg *umr,
			       स्थिर काष्ठा ib_send_wr *wr)
अणु
	स्थिर काष्ठा mlx5_umr_wr *umrwr = umr_wr(wr);

	स_रखो(umr, 0, माप(*umr));

	अगर (!umrwr->ignore_मुक्त_state) अणु
		अगर (wr->send_flags & MLX5_IB_SEND_UMR_FAIL_IF_FREE)
			 /* fail अगर मुक्त */
			umr->flags = MLX5_UMR_CHECK_FREE;
		अन्यथा
			/* fail अगर not मुक्त */
			umr->flags = MLX5_UMR_CHECK_NOT_FREE;
	पूर्ण

	umr->xlt_octowords = cpu_to_be16(get_xlt_octo(umrwr->xlt_size));
	अगर (wr->send_flags & MLX5_IB_SEND_UMR_UPDATE_XLT) अणु
		u64 offset = get_xlt_octo(umrwr->offset);

		umr->xlt_offset = cpu_to_be16(offset & 0xffff);
		umr->xlt_offset_47_16 = cpu_to_be32(offset >> 16);
		umr->flags |= MLX5_UMR_TRANSLATION_OFFSET_EN;
	पूर्ण
	अगर (wr->send_flags & MLX5_IB_SEND_UMR_UPDATE_TRANSLATION)
		umr->mkey_mask |= get_umr_update_translation_mask();
	अगर (wr->send_flags & MLX5_IB_SEND_UMR_UPDATE_PD_ACCESS) अणु
		umr->mkey_mask |= get_umr_update_access_mask(
			!!(MLX5_CAP_GEN(dev->mdev, atomic)),
			!!(MLX5_CAP_GEN(dev->mdev, relaxed_ordering_ग_लिखो_umr)),
			!!(MLX5_CAP_GEN(dev->mdev, relaxed_ordering_पढ़ो_umr)));
		umr->mkey_mask |= get_umr_update_pd_mask();
	पूर्ण
	अगर (wr->send_flags & MLX5_IB_SEND_UMR_ENABLE_MR)
		umr->mkey_mask |= get_umr_enable_mr_mask();
	अगर (wr->send_flags & MLX5_IB_SEND_UMR_DISABLE_MR)
		umr->mkey_mask |= get_umr_disable_mr_mask();

	अगर (!wr->num_sge)
		umr->flags |= MLX5_UMR_INLINE;

	वापस umr_check_mkey_mask(dev, be64_to_cpu(umr->mkey_mask));
पूर्ण

अटल u8 get_umr_flags(पूर्णांक acc)
अणु
	वापस (acc & IB_ACCESS_REMOTE_ATOMIC ? MLX5_PERM_ATOMIC       : 0) |
	       (acc & IB_ACCESS_REMOTE_WRITE  ? MLX5_PERM_REMOTE_WRITE : 0) |
	       (acc & IB_ACCESS_REMOTE_READ   ? MLX5_PERM_REMOTE_READ  : 0) |
	       (acc & IB_ACCESS_LOCAL_WRITE   ? MLX5_PERM_LOCAL_WRITE  : 0) |
		MLX5_PERM_LOCAL_READ | MLX5_PERM_UMR_EN;
पूर्ण

अटल व्योम set_reg_mkey_seg(काष्ठा mlx5_mkey_seg *seg,
			     काष्ठा mlx5_ib_mr *mr,
			     u32 key, पूर्णांक access)
अणु
	पूर्णांक ndescs = ALIGN(mr->ndescs + mr->meta_ndescs, 8) >> 1;

	स_रखो(seg, 0, माप(*seg));

	अगर (mr->access_mode == MLX5_MKC_ACCESS_MODE_MTT)
		seg->log2_page_size = ilog2(mr->ibmr.page_size);
	अन्यथा अगर (mr->access_mode == MLX5_MKC_ACCESS_MODE_KLMS)
		/* KLMs take twice the size of MTTs */
		ndescs *= 2;

	seg->flags = get_umr_flags(access) | mr->access_mode;
	seg->qpn_mkey7_0 = cpu_to_be32((key & 0xff) | 0xffffff00);
	seg->flags_pd = cpu_to_be32(MLX5_MKEY_REMOTE_INVAL);
	seg->start_addr = cpu_to_be64(mr->ibmr.iova);
	seg->len = cpu_to_be64(mr->ibmr.length);
	seg->xlt_oct_size = cpu_to_be32(ndescs);
पूर्ण

अटल व्योम set_linv_mkey_seg(काष्ठा mlx5_mkey_seg *seg)
अणु
	स_रखो(seg, 0, माप(*seg));
	seg->status = MLX5_MKEY_STATUS_FREE;
पूर्ण

अटल व्योम set_reg_mkey_segment(काष्ठा mlx5_ib_dev *dev,
				 काष्ठा mlx5_mkey_seg *seg,
				 स्थिर काष्ठा ib_send_wr *wr)
अणु
	स्थिर काष्ठा mlx5_umr_wr *umrwr = umr_wr(wr);

	स_रखो(seg, 0, माप(*seg));
	अगर (wr->send_flags & MLX5_IB_SEND_UMR_DISABLE_MR)
		MLX5_SET(mkc, seg, मुक्त, 1);

	MLX5_SET(mkc, seg, a,
		 !!(umrwr->access_flags & IB_ACCESS_REMOTE_ATOMIC));
	MLX5_SET(mkc, seg, rw,
		 !!(umrwr->access_flags & IB_ACCESS_REMOTE_WRITE));
	MLX5_SET(mkc, seg, rr, !!(umrwr->access_flags & IB_ACCESS_REMOTE_READ));
	MLX5_SET(mkc, seg, lw, !!(umrwr->access_flags & IB_ACCESS_LOCAL_WRITE));
	MLX5_SET(mkc, seg, lr, 1);
	अगर (MLX5_CAP_GEN(dev->mdev, relaxed_ordering_ग_लिखो_umr))
		MLX5_SET(mkc, seg, relaxed_ordering_ग_लिखो,
			 !!(umrwr->access_flags & IB_ACCESS_RELAXED_ORDERING));
	अगर (MLX5_CAP_GEN(dev->mdev, relaxed_ordering_पढ़ो_umr))
		MLX5_SET(mkc, seg, relaxed_ordering_पढ़ो,
			 !!(umrwr->access_flags & IB_ACCESS_RELAXED_ORDERING));

	अगर (umrwr->pd)
		MLX5_SET(mkc, seg, pd, to_mpd(umrwr->pd)->pdn);
	अगर (wr->send_flags & MLX5_IB_SEND_UMR_UPDATE_TRANSLATION &&
	    !umrwr->length)
		MLX5_SET(mkc, seg, length64, 1);

	MLX5_SET64(mkc, seg, start_addr, umrwr->virt_addr);
	MLX5_SET64(mkc, seg, len, umrwr->length);
	MLX5_SET(mkc, seg, log_page_size, umrwr->page_shअगरt);
	MLX5_SET(mkc, seg, qpn, 0xffffff);
	MLX5_SET(mkc, seg, mkey_7_0, mlx5_mkey_variant(umrwr->mkey));
पूर्ण

अटल व्योम set_reg_data_seg(काष्ठा mlx5_wqe_data_seg *dseg,
			     काष्ठा mlx5_ib_mr *mr,
			     काष्ठा mlx5_ib_pd *pd)
अणु
	पूर्णांक bcount = mr->desc_size * (mr->ndescs + mr->meta_ndescs);

	dseg->addr = cpu_to_be64(mr->desc_map);
	dseg->byte_count = cpu_to_be32(ALIGN(bcount, 64));
	dseg->lkey = cpu_to_be32(pd->ibpd.local_dma_lkey);
पूर्ण

अटल __be32 send_ieth(स्थिर काष्ठा ib_send_wr *wr)
अणु
	चयन (wr->opcode) अणु
	हाल IB_WR_SEND_WITH_IMM:
	हाल IB_WR_RDMA_WRITE_WITH_IMM:
		वापस wr->ex.imm_data;

	हाल IB_WR_SEND_WITH_INV:
		वापस cpu_to_be32(wr->ex.invalidate_rkey);

	शेष:
		वापस 0;
	पूर्ण
पूर्ण

अटल u8 calc_sig(व्योम *wqe, पूर्णांक size)
अणु
	u8 *p = wqe;
	u8 res = 0;
	पूर्णांक i;

	क्रम (i = 0; i < size; i++)
		res ^= p[i];

	वापस ~res;
पूर्ण

अटल u8 wq_sig(व्योम *wqe)
अणु
	वापस calc_sig(wqe, (*((u8 *)wqe + 8) & 0x3f) << 4);
पूर्ण

अटल पूर्णांक set_data_inl_seg(काष्ठा mlx5_ib_qp *qp, स्थिर काष्ठा ib_send_wr *wr,
			    व्योम **wqe, पूर्णांक *wqe_sz, व्योम **cur_edge)
अणु
	काष्ठा mlx5_wqe_अंतरभूत_seg *seg;
	माप_प्रकार offset;
	पूर्णांक inl = 0;
	पूर्णांक i;

	seg = *wqe;
	*wqe += माप(*seg);
	offset = माप(*seg);

	क्रम (i = 0; i < wr->num_sge; i++) अणु
		माप_प्रकार len  = wr->sg_list[i].length;
		व्योम *addr = (व्योम *)(अचिन्हित दीर्घ)(wr->sg_list[i].addr);

		inl += len;

		अगर (unlikely(inl > qp->max_अंतरभूत_data))
			वापस -ENOMEM;

		जबतक (likely(len)) अणु
			माप_प्रकार leftlen;
			माप_प्रकार copysz;

			handle_post_send_edge(&qp->sq, wqe,
					      *wqe_sz + (offset >> 4),
					      cur_edge);

			leftlen = *cur_edge - *wqe;
			copysz = min_t(माप_प्रकार, leftlen, len);

			स_नकल(*wqe, addr, copysz);
			len -= copysz;
			addr += copysz;
			*wqe += copysz;
			offset += copysz;
		पूर्ण
	पूर्ण

	seg->byte_count = cpu_to_be32(inl | MLX5_INLINE_SEG);

	*wqe_sz +=  ALIGN(inl + माप(seg->byte_count), 16) / 16;

	वापस 0;
पूर्ण

अटल u16 prot_field_size(क्रमागत ib_signature_type type)
अणु
	चयन (type) अणु
	हाल IB_SIG_TYPE_T10_DIF:
		वापस MLX5_DIF_SIZE;
	शेष:
		वापस 0;
	पूर्ण
पूर्ण

अटल u8 bs_selector(पूर्णांक block_size)
अणु
	चयन (block_size) अणु
	हाल 512:	    वापस 0x1;
	हाल 520:	    वापस 0x2;
	हाल 4096:	    वापस 0x3;
	हाल 4160:	    वापस 0x4;
	हाल 1073741824:    वापस 0x5;
	शेष:	    वापस 0;
	पूर्ण
पूर्ण

अटल व्योम mlx5_fill_inl_bsf(काष्ठा ib_sig_करोमुख्य *करोमुख्य,
			      काष्ठा mlx5_bsf_inl *inl)
अणु
	/* Valid अंतरभूत section and allow BSF refresh */
	inl->vld_refresh = cpu_to_be16(MLX5_BSF_INL_VALID |
				       MLX5_BSF_REFRESH_DIF);
	inl->dअगर_apptag = cpu_to_be16(करोमुख्य->sig.dअगर.app_tag);
	inl->dअगर_reftag = cpu_to_be32(करोमुख्य->sig.dअगर.ref_tag);
	/* repeating block */
	inl->rp_inv_seed = MLX5_BSF_REPEAT_BLOCK;
	inl->sig_type = करोमुख्य->sig.dअगर.bg_type == IB_T10DIF_CRC ?
			MLX5_DIF_CRC : MLX5_DIF_IPCS;

	अगर (करोमुख्य->sig.dअगर.ref_remap)
		inl->dअगर_inc_ref_guard_check |= MLX5_BSF_INC_REFTAG;

	अगर (करोमुख्य->sig.dअगर.app_escape) अणु
		अगर (करोमुख्य->sig.dअगर.ref_escape)
			inl->dअगर_inc_ref_guard_check |= MLX5_BSF_APPREF_ESCAPE;
		अन्यथा
			inl->dअगर_inc_ref_guard_check |= MLX5_BSF_APPTAG_ESCAPE;
	पूर्ण

	inl->dअगर_app_biपंचांगask_check =
		cpu_to_be16(करोमुख्य->sig.dअगर.apptag_check_mask);
पूर्ण

अटल पूर्णांक mlx5_set_bsf(काष्ठा ib_mr *sig_mr,
			काष्ठा ib_sig_attrs *sig_attrs,
			काष्ठा mlx5_bsf *bsf, u32 data_size)
अणु
	काष्ठा mlx5_core_sig_ctx *msig = to_mmr(sig_mr)->sig;
	काष्ठा mlx5_bsf_basic *basic = &bsf->basic;
	काष्ठा ib_sig_करोमुख्य *mem = &sig_attrs->mem;
	काष्ठा ib_sig_करोमुख्य *wire = &sig_attrs->wire;

	स_रखो(bsf, 0, माप(*bsf));

	/* Basic + Extended + Inline */
	basic->bsf_size_sbs = 1 << 7;
	/* Input करोमुख्य check byte mask */
	basic->check_byte_mask = sig_attrs->check_mask;
	basic->raw_data_size = cpu_to_be32(data_size);

	/* Memory करोमुख्य */
	चयन (sig_attrs->mem.sig_type) अणु
	हाल IB_SIG_TYPE_NONE:
		अवरोध;
	हाल IB_SIG_TYPE_T10_DIF:
		basic->mem.bs_selector = bs_selector(mem->sig.dअगर.pi_पूर्णांकerval);
		basic->m_bfs_psv = cpu_to_be32(msig->psv_memory.psv_idx);
		mlx5_fill_inl_bsf(mem, &bsf->m_inl);
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	/* Wire करोमुख्य */
	चयन (sig_attrs->wire.sig_type) अणु
	हाल IB_SIG_TYPE_NONE:
		अवरोध;
	हाल IB_SIG_TYPE_T10_DIF:
		अगर (mem->sig.dअगर.pi_पूर्णांकerval == wire->sig.dअगर.pi_पूर्णांकerval &&
		    mem->sig_type == wire->sig_type) अणु
			/* Same block काष्ठाure */
			basic->bsf_size_sbs |= 1 << 4;
			अगर (mem->sig.dअगर.bg_type == wire->sig.dअगर.bg_type)
				basic->wire.copy_byte_mask |= MLX5_CPY_GRD_MASK;
			अगर (mem->sig.dअगर.app_tag == wire->sig.dअगर.app_tag)
				basic->wire.copy_byte_mask |= MLX5_CPY_APP_MASK;
			अगर (mem->sig.dअगर.ref_tag == wire->sig.dअगर.ref_tag)
				basic->wire.copy_byte_mask |= MLX5_CPY_REF_MASK;
		पूर्ण अन्यथा
			basic->wire.bs_selector =
				bs_selector(wire->sig.dअगर.pi_पूर्णांकerval);

		basic->w_bfs_psv = cpu_to_be32(msig->psv_wire.psv_idx);
		mlx5_fill_inl_bsf(wire, &bsf->w_inl);
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण


अटल पूर्णांक set_sig_data_segment(स्थिर काष्ठा ib_send_wr *send_wr,
				काष्ठा ib_mr *sig_mr,
				काष्ठा ib_sig_attrs *sig_attrs,
				काष्ठा mlx5_ib_qp *qp, व्योम **seg, पूर्णांक *size,
				व्योम **cur_edge)
अणु
	काष्ठा mlx5_bsf *bsf;
	u32 data_len;
	u32 data_key;
	u64 data_va;
	u32 prot_len = 0;
	u32 prot_key = 0;
	u64 prot_va = 0;
	bool prot = false;
	पूर्णांक ret;
	पूर्णांक wqe_size;
	काष्ठा mlx5_ib_mr *mr = to_mmr(sig_mr);
	काष्ठा mlx5_ib_mr *pi_mr = mr->pi_mr;

	data_len = pi_mr->data_length;
	data_key = pi_mr->ibmr.lkey;
	data_va = pi_mr->data_iova;
	अगर (pi_mr->meta_ndescs) अणु
		prot_len = pi_mr->meta_length;
		prot_key = pi_mr->ibmr.lkey;
		prot_va = pi_mr->pi_iova;
		prot = true;
	पूर्ण

	अगर (!prot || (data_key == prot_key && data_va == prot_va &&
		      data_len == prot_len)) अणु
		/**
		 * Source करोमुख्य करोesn't contain signature inक्रमmation
		 * or data and protection are पूर्णांकerleaved in memory.
		 * So need स्थिरruct:
		 *                  ------------------
		 *                 |     data_klm     |
		 *                  ------------------
		 *                 |       BSF        |
		 *                  ------------------
		 **/
		काष्ठा mlx5_klm *data_klm = *seg;

		data_klm->bcount = cpu_to_be32(data_len);
		data_klm->key = cpu_to_be32(data_key);
		data_klm->va = cpu_to_be64(data_va);
		wqe_size = ALIGN(माप(*data_klm), 64);
	पूर्ण अन्यथा अणु
		/**
		 * Source करोमुख्य contains signature inक्रमmation
		 * So need स्थिरruct a strided block क्रमmat:
		 *               ---------------------------
		 *              |     stride_block_ctrl     |
		 *               ---------------------------
		 *              |          data_klm         |
		 *               ---------------------------
		 *              |          prot_klm         |
		 *               ---------------------------
		 *              |             BSF           |
		 *               ---------------------------
		 **/
		काष्ठा mlx5_stride_block_ctrl_seg *sblock_ctrl;
		काष्ठा mlx5_stride_block_entry *data_sentry;
		काष्ठा mlx5_stride_block_entry *prot_sentry;
		u16 block_size = sig_attrs->mem.sig.dअगर.pi_पूर्णांकerval;
		पूर्णांक prot_size;

		sblock_ctrl = *seg;
		data_sentry = (व्योम *)sblock_ctrl + माप(*sblock_ctrl);
		prot_sentry = (व्योम *)data_sentry + माप(*data_sentry);

		prot_size = prot_field_size(sig_attrs->mem.sig_type);
		अगर (!prot_size) अणु
			pr_err("Bad block size given: %u\n", block_size);
			वापस -EINVAL;
		पूर्ण
		sblock_ctrl->bcount_per_cycle = cpu_to_be32(block_size +
							    prot_size);
		sblock_ctrl->op = cpu_to_be32(MLX5_STRIDE_BLOCK_OP);
		sblock_ctrl->repeat_count = cpu_to_be32(data_len / block_size);
		sblock_ctrl->num_entries = cpu_to_be16(2);

		data_sentry->bcount = cpu_to_be16(block_size);
		data_sentry->key = cpu_to_be32(data_key);
		data_sentry->va = cpu_to_be64(data_va);
		data_sentry->stride = cpu_to_be16(block_size);

		prot_sentry->bcount = cpu_to_be16(prot_size);
		prot_sentry->key = cpu_to_be32(prot_key);
		prot_sentry->va = cpu_to_be64(prot_va);
		prot_sentry->stride = cpu_to_be16(prot_size);

		wqe_size = ALIGN(माप(*sblock_ctrl) + माप(*data_sentry) +
				 माप(*prot_sentry), 64);
	पूर्ण

	*seg += wqe_size;
	*size += wqe_size / 16;
	handle_post_send_edge(&qp->sq, seg, *size, cur_edge);

	bsf = *seg;
	ret = mlx5_set_bsf(sig_mr, sig_attrs, bsf, data_len);
	अगर (ret)
		वापस -EINVAL;

	*seg += माप(*bsf);
	*size += माप(*bsf) / 16;
	handle_post_send_edge(&qp->sq, seg, *size, cur_edge);

	वापस 0;
पूर्ण

अटल व्योम set_sig_mkey_segment(काष्ठा mlx5_mkey_seg *seg,
				 काष्ठा ib_mr *sig_mr, पूर्णांक access_flags,
				 u32 size, u32 length, u32 pdn)
अणु
	u32 sig_key = sig_mr->rkey;
	u8 sigerr = to_mmr(sig_mr)->sig->sigerr_count & 1;

	स_रखो(seg, 0, माप(*seg));

	seg->flags = get_umr_flags(access_flags) | MLX5_MKC_ACCESS_MODE_KLMS;
	seg->qpn_mkey7_0 = cpu_to_be32((sig_key & 0xff) | 0xffffff00);
	seg->flags_pd = cpu_to_be32(MLX5_MKEY_REMOTE_INVAL | sigerr << 26 |
				    MLX5_MKEY_BSF_EN | pdn);
	seg->len = cpu_to_be64(length);
	seg->xlt_oct_size = cpu_to_be32(get_xlt_octo(size));
	seg->bsfs_octo_size = cpu_to_be32(MLX5_MKEY_BSF_OCTO_SIZE);
पूर्ण

अटल व्योम set_sig_umr_segment(काष्ठा mlx5_wqe_umr_ctrl_seg *umr,
				u32 size)
अणु
	स_रखो(umr, 0, माप(*umr));

	umr->flags = MLX5_FLAGS_INLINE | MLX5_FLAGS_CHECK_FREE;
	umr->xlt_octowords = cpu_to_be16(get_xlt_octo(size));
	umr->bsf_octowords = cpu_to_be16(MLX5_MKEY_BSF_OCTO_SIZE);
	umr->mkey_mask = sig_mkey_mask();
पूर्ण

अटल पूर्णांक set_pi_umr_wr(स्थिर काष्ठा ib_send_wr *send_wr,
			 काष्ठा mlx5_ib_qp *qp, व्योम **seg, पूर्णांक *size,
			 व्योम **cur_edge)
अणु
	स्थिर काष्ठा ib_reg_wr *wr = reg_wr(send_wr);
	काष्ठा mlx5_ib_mr *sig_mr = to_mmr(wr->mr);
	काष्ठा mlx5_ib_mr *pi_mr = sig_mr->pi_mr;
	काष्ठा ib_sig_attrs *sig_attrs = sig_mr->ibmr.sig_attrs;
	u32 pdn = to_mpd(qp->ibqp.pd)->pdn;
	u32 xlt_size;
	पूर्णांक region_len, ret;

	अगर (unlikely(send_wr->num_sge != 0) ||
	    unlikely(wr->access & IB_ACCESS_REMOTE_ATOMIC) ||
	    unlikely(!sig_mr->sig) || unlikely(!qp->ibqp.पूर्णांकegrity_en) ||
	    unlikely(!sig_mr->sig->sig_status_checked))
		वापस -EINVAL;

	/* length of the रक्षित region, data + protection */
	region_len = pi_mr->ibmr.length;

	/**
	 * KLM octoword size - अगर protection was provided
	 * then we use strided block क्रमmat (3 octowords),
	 * अन्यथा we use single KLM (1 octoword)
	 **/
	अगर (sig_attrs->mem.sig_type != IB_SIG_TYPE_NONE)
		xlt_size = 0x30;
	अन्यथा
		xlt_size = माप(काष्ठा mlx5_klm);

	set_sig_umr_segment(*seg, xlt_size);
	*seg += माप(काष्ठा mlx5_wqe_umr_ctrl_seg);
	*size += माप(काष्ठा mlx5_wqe_umr_ctrl_seg) / 16;
	handle_post_send_edge(&qp->sq, seg, *size, cur_edge);

	set_sig_mkey_segment(*seg, wr->mr, wr->access, xlt_size, region_len,
			     pdn);
	*seg += माप(काष्ठा mlx5_mkey_seg);
	*size += माप(काष्ठा mlx5_mkey_seg) / 16;
	handle_post_send_edge(&qp->sq, seg, *size, cur_edge);

	ret = set_sig_data_segment(send_wr, wr->mr, sig_attrs, qp, seg, size,
				   cur_edge);
	अगर (ret)
		वापस ret;

	sig_mr->sig->sig_status_checked = false;
	वापस 0;
पूर्ण

अटल पूर्णांक set_psv_wr(काष्ठा ib_sig_करोमुख्य *करोमुख्य,
		      u32 psv_idx, व्योम **seg, पूर्णांक *size)
अणु
	काष्ठा mlx5_seg_set_psv *psv_seg = *seg;

	स_रखो(psv_seg, 0, माप(*psv_seg));
	psv_seg->psv_num = cpu_to_be32(psv_idx);
	चयन (करोमुख्य->sig_type) अणु
	हाल IB_SIG_TYPE_NONE:
		अवरोध;
	हाल IB_SIG_TYPE_T10_DIF:
		psv_seg->transient_sig = cpu_to_be32(करोमुख्य->sig.dअगर.bg << 16 |
						     करोमुख्य->sig.dअगर.app_tag);
		psv_seg->ref_tag = cpu_to_be32(करोमुख्य->sig.dअगर.ref_tag);
		अवरोध;
	शेष:
		pr_err("Bad signature type (%d) is given.\n",
		       करोमुख्य->sig_type);
		वापस -EINVAL;
	पूर्ण

	*seg += माप(*psv_seg);
	*size += माप(*psv_seg) / 16;

	वापस 0;
पूर्ण

अटल पूर्णांक set_reg_wr(काष्ठा mlx5_ib_qp *qp,
		      स्थिर काष्ठा ib_reg_wr *wr,
		      व्योम **seg, पूर्णांक *size, व्योम **cur_edge,
		      bool check_not_मुक्त)
अणु
	काष्ठा mlx5_ib_mr *mr = to_mmr(wr->mr);
	काष्ठा mlx5_ib_pd *pd = to_mpd(qp->ibqp.pd);
	काष्ठा mlx5_ib_dev *dev = to_mdev(pd->ibpd.device);
	पूर्णांक mr_list_size = (mr->ndescs + mr->meta_ndescs) * mr->desc_size;
	bool umr_अंतरभूत = mr_list_size <= MLX5_IB_SQ_UMR_INLINE_THRESHOLD;
	bool atomic = wr->access & IB_ACCESS_REMOTE_ATOMIC;
	u8 flags = 0;

	/* Matches access in mlx5_set_umr_मुक्त_mkey() */
	अगर (!mlx5_ib_can_reconfig_with_umr(dev, 0, wr->access)) अणु
		mlx5_ib_warn(
			to_mdev(qp->ibqp.device),
			"Fast update for MR access flags is not possible\n");
		वापस -EINVAL;
	पूर्ण

	अगर (unlikely(wr->wr.send_flags & IB_SEND_INLINE)) अणु
		mlx5_ib_warn(to_mdev(qp->ibqp.device),
			     "Invalid IB_SEND_INLINE send flag\n");
		वापस -EINVAL;
	पूर्ण

	अगर (check_not_मुक्त)
		flags |= MLX5_UMR_CHECK_NOT_FREE;
	अगर (umr_अंतरभूत)
		flags |= MLX5_UMR_INLINE;

	set_reg_umr_seg(*seg, mr, flags, atomic);
	*seg += माप(काष्ठा mlx5_wqe_umr_ctrl_seg);
	*size += माप(काष्ठा mlx5_wqe_umr_ctrl_seg) / 16;
	handle_post_send_edge(&qp->sq, seg, *size, cur_edge);

	set_reg_mkey_seg(*seg, mr, wr->key, wr->access);
	*seg += माप(काष्ठा mlx5_mkey_seg);
	*size += माप(काष्ठा mlx5_mkey_seg) / 16;
	handle_post_send_edge(&qp->sq, seg, *size, cur_edge);

	अगर (umr_अंतरभूत) अणु
		स_नकल_send_wqe(&qp->sq, cur_edge, seg, size, mr->descs,
				mr_list_size);
		*size = ALIGN(*size, MLX5_SEND_WQE_BB >> 4);
	पूर्ण अन्यथा अणु
		set_reg_data_seg(*seg, mr, pd);
		*seg += माप(काष्ठा mlx5_wqe_data_seg);
		*size += (माप(काष्ठा mlx5_wqe_data_seg) / 16);
	पूर्ण
	वापस 0;
पूर्ण

अटल व्योम set_linv_wr(काष्ठा mlx5_ib_qp *qp, व्योम **seg, पूर्णांक *size,
			व्योम **cur_edge)
अणु
	set_linv_umr_seg(*seg);
	*seg += माप(काष्ठा mlx5_wqe_umr_ctrl_seg);
	*size += माप(काष्ठा mlx5_wqe_umr_ctrl_seg) / 16;
	handle_post_send_edge(&qp->sq, seg, *size, cur_edge);
	set_linv_mkey_seg(*seg);
	*seg += माप(काष्ठा mlx5_mkey_seg);
	*size += माप(काष्ठा mlx5_mkey_seg) / 16;
	handle_post_send_edge(&qp->sq, seg, *size, cur_edge);
पूर्ण

अटल व्योम dump_wqe(काष्ठा mlx5_ib_qp *qp, u32 idx, पूर्णांक size_16)
अणु
	__be32 *p = शून्य;
	पूर्णांक i, j;

	pr_debug("dump WQE index %u:\n", idx);
	क्रम (i = 0, j = 0; i < size_16 * 4; i += 4, j += 4) अणु
		अगर ((i & 0xf) == 0) अणु
			p = mlx5_frag_buf_get_wqe(&qp->sq.fbc, idx);
			pr_debug("WQBB at %p:\n", (व्योम *)p);
			j = 0;
			idx = (idx + 1) & (qp->sq.wqe_cnt - 1);
		पूर्ण
		pr_debug("%08x %08x %08x %08x\n", be32_to_cpu(p[j]),
			 be32_to_cpu(p[j + 1]), be32_to_cpu(p[j + 2]),
			 be32_to_cpu(p[j + 3]));
	पूर्ण
पूर्ण

अटल पूर्णांक __begin_wqe(काष्ठा mlx5_ib_qp *qp, व्योम **seg,
		       काष्ठा mlx5_wqe_ctrl_seg **ctrl,
		       स्थिर काष्ठा ib_send_wr *wr, अचिन्हित पूर्णांक *idx,
		       पूर्णांक *size, व्योम **cur_edge, पूर्णांक nreq,
		       bool send_संकेतed, bool solicited)
अणु
	अगर (unlikely(mlx5_wq_overflow(&qp->sq, nreq, qp->ibqp.send_cq)))
		वापस -ENOMEM;

	*idx = qp->sq.cur_post & (qp->sq.wqe_cnt - 1);
	*seg = mlx5_frag_buf_get_wqe(&qp->sq.fbc, *idx);
	*ctrl = *seg;
	*(uपूर्णांक32_t *)(*seg + 8) = 0;
	(*ctrl)->imm = send_ieth(wr);
	(*ctrl)->fm_ce_se = qp->sq_संकेत_bits |
		(send_संकेतed ? MLX5_WQE_CTRL_CQ_UPDATE : 0) |
		(solicited ? MLX5_WQE_CTRL_SOLICITED : 0);

	*seg += माप(**ctrl);
	*size = माप(**ctrl) / 16;
	*cur_edge = qp->sq.cur_edge;

	वापस 0;
पूर्ण

अटल पूर्णांक begin_wqe(काष्ठा mlx5_ib_qp *qp, व्योम **seg,
		     काष्ठा mlx5_wqe_ctrl_seg **ctrl,
		     स्थिर काष्ठा ib_send_wr *wr, अचिन्हित पूर्णांक *idx, पूर्णांक *size,
		     व्योम **cur_edge, पूर्णांक nreq)
अणु
	वापस __begin_wqe(qp, seg, ctrl, wr, idx, size, cur_edge, nreq,
			   wr->send_flags & IB_SEND_SIGNALED,
			   wr->send_flags & IB_SEND_SOLICITED);
पूर्ण

अटल व्योम finish_wqe(काष्ठा mlx5_ib_qp *qp,
		       काष्ठा mlx5_wqe_ctrl_seg *ctrl,
		       व्योम *seg, u8 size, व्योम *cur_edge,
		       अचिन्हित पूर्णांक idx, u64 wr_id, पूर्णांक nreq, u8 fence,
		       u32 mlx5_opcode)
अणु
	u8 opmod = 0;

	ctrl->opmod_idx_opcode = cpu_to_be32(((u32)(qp->sq.cur_post) << 8) |
					     mlx5_opcode | ((u32)opmod << 24));
	ctrl->qpn_ds = cpu_to_be32(size | (qp->trans_qp.base.mqp.qpn << 8));
	ctrl->fm_ce_se |= fence;
	अगर (unlikely(qp->flags_en & MLX5_QP_FLAG_SIGNATURE))
		ctrl->signature = wq_sig(ctrl);

	qp->sq.wrid[idx] = wr_id;
	qp->sq.w_list[idx].opcode = mlx5_opcode;
	qp->sq.wqe_head[idx] = qp->sq.head + nreq;
	qp->sq.cur_post += DIV_ROUND_UP(size * 16, MLX5_SEND_WQE_BB);
	qp->sq.w_list[idx].next = qp->sq.cur_post;

	/* We save the edge which was possibly updated during the WQE
	 * स्थिरruction, पूर्णांकo SQ's cache.
	 */
	seg = PTR_ALIGN(seg, MLX5_SEND_WQE_BB);
	qp->sq.cur_edge = (unlikely(seg == cur_edge)) ?
			  get_sq_edge(&qp->sq, qp->sq.cur_post &
				      (qp->sq.wqe_cnt - 1)) :
			  cur_edge;
पूर्ण

अटल व्योम handle_rdma_op(स्थिर काष्ठा ib_send_wr *wr, व्योम **seg, पूर्णांक *size)
अणु
	set_raddr_seg(*seg, rdma_wr(wr)->remote_addr, rdma_wr(wr)->rkey);
	*seg += माप(काष्ठा mlx5_wqe_raddr_seg);
	*size += माप(काष्ठा mlx5_wqe_raddr_seg) / 16;
पूर्ण

अटल व्योम handle_local_inv(काष्ठा mlx5_ib_qp *qp, स्थिर काष्ठा ib_send_wr *wr,
			     काष्ठा mlx5_wqe_ctrl_seg **ctrl, व्योम **seg,
			     पूर्णांक *size, व्योम **cur_edge, अचिन्हित पूर्णांक idx)
अणु
	qp->sq.wr_data[idx] = IB_WR_LOCAL_INV;
	(*ctrl)->imm = cpu_to_be32(wr->ex.invalidate_rkey);
	set_linv_wr(qp, seg, size, cur_edge);
पूर्ण

अटल पूर्णांक handle_reg_mr(काष्ठा mlx5_ib_qp *qp, स्थिर काष्ठा ib_send_wr *wr,
			 काष्ठा mlx5_wqe_ctrl_seg **ctrl, व्योम **seg, पूर्णांक *size,
			 व्योम **cur_edge, अचिन्हित पूर्णांक idx)
अणु
	qp->sq.wr_data[idx] = IB_WR_REG_MR;
	(*ctrl)->imm = cpu_to_be32(reg_wr(wr)->key);
	वापस set_reg_wr(qp, reg_wr(wr), seg, size, cur_edge, true);
पूर्ण

अटल पूर्णांक handle_psv(काष्ठा mlx5_ib_dev *dev, काष्ठा mlx5_ib_qp *qp,
		      स्थिर काष्ठा ib_send_wr *wr,
		      काष्ठा mlx5_wqe_ctrl_seg **ctrl, व्योम **seg, पूर्णांक *size,
		      व्योम **cur_edge, अचिन्हित पूर्णांक *idx, पूर्णांक nreq,
		      काष्ठा ib_sig_करोमुख्य *करोमुख्य, u32 psv_index,
		      u8 next_fence)
अणु
	पूर्णांक err;

	/*
	 * SET_PSV WQEs are not संकेतed and solicited on error.
	 */
	err = __begin_wqe(qp, seg, ctrl, wr, idx, size, cur_edge, nreq,
			  false, true);
	अगर (unlikely(err)) अणु
		mlx5_ib_warn(dev, "\n");
		err = -ENOMEM;
		जाओ out;
	पूर्ण
	err = set_psv_wr(करोमुख्य, psv_index, seg, size);
	अगर (unlikely(err)) अणु
		mlx5_ib_warn(dev, "\n");
		जाओ out;
	पूर्ण
	finish_wqe(qp, *ctrl, *seg, *size, *cur_edge, *idx, wr->wr_id, nreq,
		   next_fence, MLX5_OPCODE_SET_PSV);

out:
	वापस err;
पूर्ण

अटल पूर्णांक handle_reg_mr_पूर्णांकegrity(काष्ठा mlx5_ib_dev *dev,
				   काष्ठा mlx5_ib_qp *qp,
				   स्थिर काष्ठा ib_send_wr *wr,
				   काष्ठा mlx5_wqe_ctrl_seg **ctrl, व्योम **seg,
				   पूर्णांक *size, व्योम **cur_edge,
				   अचिन्हित पूर्णांक *idx, पूर्णांक nreq, u8 fence,
				   u8 next_fence)
अणु
	काष्ठा mlx5_ib_mr *mr;
	काष्ठा mlx5_ib_mr *pi_mr;
	काष्ठा mlx5_ib_mr pa_pi_mr;
	काष्ठा ib_sig_attrs *sig_attrs;
	काष्ठा ib_reg_wr reg_pi_wr;
	पूर्णांक err;

	qp->sq.wr_data[*idx] = IB_WR_REG_MR_INTEGRITY;

	mr = to_mmr(reg_wr(wr)->mr);
	pi_mr = mr->pi_mr;

	अगर (pi_mr) अणु
		स_रखो(&reg_pi_wr, 0,
		       माप(काष्ठा ib_reg_wr));

		reg_pi_wr.mr = &pi_mr->ibmr;
		reg_pi_wr.access = reg_wr(wr)->access;
		reg_pi_wr.key = pi_mr->ibmr.rkey;

		(*ctrl)->imm = cpu_to_be32(reg_pi_wr.key);
		/* UMR क्रम data + prot registration */
		err = set_reg_wr(qp, &reg_pi_wr, seg, size, cur_edge, false);
		अगर (unlikely(err))
			जाओ out;

		finish_wqe(qp, *ctrl, *seg, *size, *cur_edge, *idx, wr->wr_id,
			   nreq, fence, MLX5_OPCODE_UMR);

		err = begin_wqe(qp, seg, ctrl, wr, idx, size, cur_edge, nreq);
		अगर (unlikely(err)) अणु
			mlx5_ib_warn(dev, "\n");
			err = -ENOMEM;
			जाओ out;
		पूर्ण
	पूर्ण अन्यथा अणु
		स_रखो(&pa_pi_mr, 0, माप(काष्ठा mlx5_ib_mr));
		/* No UMR, use local_dma_lkey */
		pa_pi_mr.ibmr.lkey = mr->ibmr.pd->local_dma_lkey;
		pa_pi_mr.ndescs = mr->ndescs;
		pa_pi_mr.data_length = mr->data_length;
		pa_pi_mr.data_iova = mr->data_iova;
		अगर (mr->meta_ndescs) अणु
			pa_pi_mr.meta_ndescs = mr->meta_ndescs;
			pa_pi_mr.meta_length = mr->meta_length;
			pa_pi_mr.pi_iova = mr->pi_iova;
		पूर्ण

		pa_pi_mr.ibmr.length = mr->ibmr.length;
		mr->pi_mr = &pa_pi_mr;
	पूर्ण
	(*ctrl)->imm = cpu_to_be32(mr->ibmr.rkey);
	/* UMR क्रम sig MR */
	err = set_pi_umr_wr(wr, qp, seg, size, cur_edge);
	अगर (unlikely(err)) अणु
		mlx5_ib_warn(dev, "\n");
		जाओ out;
	पूर्ण
	finish_wqe(qp, *ctrl, *seg, *size, *cur_edge, *idx, wr->wr_id, nreq,
		   fence, MLX5_OPCODE_UMR);

	sig_attrs = mr->ibmr.sig_attrs;
	err = handle_psv(dev, qp, wr, ctrl, seg, size, cur_edge, idx, nreq,
			 &sig_attrs->mem, mr->sig->psv_memory.psv_idx,
			 next_fence);
	अगर (unlikely(err))
		जाओ out;

	err = handle_psv(dev, qp, wr, ctrl, seg, size, cur_edge, idx, nreq,
			 &sig_attrs->wire, mr->sig->psv_wire.psv_idx,
			 next_fence);
	अगर (unlikely(err))
		जाओ out;

	qp->next_fence = MLX5_FENCE_MODE_INITIATOR_SMALL;

out:
	वापस err;
पूर्ण

अटल पूर्णांक handle_qpt_rc(काष्ठा mlx5_ib_dev *dev, काष्ठा mlx5_ib_qp *qp,
			 स्थिर काष्ठा ib_send_wr *wr,
			 काष्ठा mlx5_wqe_ctrl_seg **ctrl, व्योम **seg, पूर्णांक *size,
			 व्योम **cur_edge, अचिन्हित पूर्णांक *idx, पूर्णांक nreq, u8 fence,
			 u8 next_fence, पूर्णांक *num_sge)
अणु
	पूर्णांक err = 0;

	चयन (wr->opcode) अणु
	हाल IB_WR_RDMA_READ:
	हाल IB_WR_RDMA_WRITE:
	हाल IB_WR_RDMA_WRITE_WITH_IMM:
		handle_rdma_op(wr, seg, size);
		अवरोध;

	हाल IB_WR_ATOMIC_CMP_AND_SWP:
	हाल IB_WR_ATOMIC_FETCH_AND_ADD:
	हाल IB_WR_MASKED_ATOMIC_CMP_AND_SWP:
		mlx5_ib_warn(dev, "Atomic operations are not supported yet\n");
		err = -EOPNOTSUPP;
		जाओ out;

	हाल IB_WR_LOCAL_INV:
		handle_local_inv(qp, wr, ctrl, seg, size, cur_edge, *idx);
		*num_sge = 0;
		अवरोध;

	हाल IB_WR_REG_MR:
		err = handle_reg_mr(qp, wr, ctrl, seg, size, cur_edge, *idx);
		अगर (unlikely(err))
			जाओ out;
		*num_sge = 0;
		अवरोध;

	हाल IB_WR_REG_MR_INTEGRITY:
		err = handle_reg_mr_पूर्णांकegrity(dev, qp, wr, ctrl, seg, size,
					      cur_edge, idx, nreq, fence,
					      next_fence);
		अगर (unlikely(err))
			जाओ out;
		*num_sge = 0;
		अवरोध;

	शेष:
		अवरोध;
	पूर्ण

out:
	वापस err;
पूर्ण

अटल व्योम handle_qpt_uc(स्थिर काष्ठा ib_send_wr *wr, व्योम **seg, पूर्णांक *size)
अणु
	चयन (wr->opcode) अणु
	हाल IB_WR_RDMA_WRITE:
	हाल IB_WR_RDMA_WRITE_WITH_IMM:
		handle_rdma_op(wr, seg, size);
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण
पूर्ण

अटल व्योम handle_qpt_hw_gsi(काष्ठा mlx5_ib_qp *qp,
			      स्थिर काष्ठा ib_send_wr *wr, व्योम **seg,
			      पूर्णांक *size, व्योम **cur_edge)
अणु
	set_datagram_seg(*seg, wr);
	*seg += माप(काष्ठा mlx5_wqe_datagram_seg);
	*size += माप(काष्ठा mlx5_wqe_datagram_seg) / 16;
	handle_post_send_edge(&qp->sq, seg, *size, cur_edge);
पूर्ण

अटल व्योम handle_qpt_ud(काष्ठा mlx5_ib_qp *qp, स्थिर काष्ठा ib_send_wr *wr,
			  व्योम **seg, पूर्णांक *size, व्योम **cur_edge)
अणु
	set_datagram_seg(*seg, wr);
	*seg += माप(काष्ठा mlx5_wqe_datagram_seg);
	*size += माप(काष्ठा mlx5_wqe_datagram_seg) / 16;
	handle_post_send_edge(&qp->sq, seg, *size, cur_edge);

	/* handle qp that supports ud offload */
	अगर (qp->flags & IB_QP_CREATE_IPOIB_UD_LSO) अणु
		काष्ठा mlx5_wqe_eth_pad *pad;

		pad = *seg;
		स_रखो(pad, 0, माप(काष्ठा mlx5_wqe_eth_pad));
		*seg += माप(काष्ठा mlx5_wqe_eth_pad);
		*size += माप(काष्ठा mlx5_wqe_eth_pad) / 16;
		set_eth_seg(wr, qp, seg, size, cur_edge);
		handle_post_send_edge(&qp->sq, seg, *size, cur_edge);
	पूर्ण
पूर्ण

अटल पूर्णांक handle_qpt_reg_umr(काष्ठा mlx5_ib_dev *dev, काष्ठा mlx5_ib_qp *qp,
			      स्थिर काष्ठा ib_send_wr *wr,
			      काष्ठा mlx5_wqe_ctrl_seg **ctrl, व्योम **seg,
			      पूर्णांक *size, व्योम **cur_edge, अचिन्हित पूर्णांक idx)
अणु
	पूर्णांक err = 0;

	अगर (unlikely(wr->opcode != MLX5_IB_WR_UMR)) अणु
		err = -EINVAL;
		mlx5_ib_warn(dev, "bad opcode %d\n", wr->opcode);
		जाओ out;
	पूर्ण

	qp->sq.wr_data[idx] = MLX5_IB_WR_UMR;
	(*ctrl)->imm = cpu_to_be32(umr_wr(wr)->mkey);
	err = set_reg_umr_segment(dev, *seg, wr);
	अगर (unlikely(err))
		जाओ out;
	*seg += माप(काष्ठा mlx5_wqe_umr_ctrl_seg);
	*size += माप(काष्ठा mlx5_wqe_umr_ctrl_seg) / 16;
	handle_post_send_edge(&qp->sq, seg, *size, cur_edge);
	set_reg_mkey_segment(dev, *seg, wr);
	*seg += माप(काष्ठा mlx5_mkey_seg);
	*size += माप(काष्ठा mlx5_mkey_seg) / 16;
	handle_post_send_edge(&qp->sq, seg, *size, cur_edge);
out:
	वापस err;
पूर्ण

पूर्णांक mlx5_ib_post_send(काष्ठा ib_qp *ibqp, स्थिर काष्ठा ib_send_wr *wr,
		      स्थिर काष्ठा ib_send_wr **bad_wr, bool drain)
अणु
	काष्ठा mlx5_wqe_ctrl_seg *ctrl = शून्य;  /* compiler warning */
	काष्ठा mlx5_ib_dev *dev = to_mdev(ibqp->device);
	काष्ठा mlx5_core_dev *mdev = dev->mdev;
	काष्ठा mlx5_ib_qp *qp;
	काष्ठा mlx5_wqe_xrc_seg *xrc;
	काष्ठा mlx5_bf *bf;
	व्योम *cur_edge;
	पूर्णांक size;
	अचिन्हित दीर्घ flags;
	अचिन्हित पूर्णांक idx;
	पूर्णांक err = 0;
	पूर्णांक num_sge;
	व्योम *seg;
	पूर्णांक nreq;
	पूर्णांक i;
	u8 next_fence = 0;
	u8 fence;

	अगर (unlikely(mdev->state == MLX5_DEVICE_STATE_INTERNAL_ERROR &&
		     !drain)) अणु
		*bad_wr = wr;
		वापस -EIO;
	पूर्ण

	अगर (unlikely(ibqp->qp_type == IB_QPT_GSI))
		वापस mlx5_ib_gsi_post_send(ibqp, wr, bad_wr);

	qp = to_mqp(ibqp);
	bf = &qp->bf;

	spin_lock_irqsave(&qp->sq.lock, flags);

	क्रम (nreq = 0; wr; nreq++, wr = wr->next) अणु
		अगर (unlikely(wr->opcode >= ARRAY_SIZE(mlx5_ib_opcode))) अणु
			mlx5_ib_warn(dev, "\n");
			err = -EINVAL;
			*bad_wr = wr;
			जाओ out;
		पूर्ण

		num_sge = wr->num_sge;
		अगर (unlikely(num_sge > qp->sq.max_gs)) अणु
			mlx5_ib_warn(dev, "\n");
			err = -EINVAL;
			*bad_wr = wr;
			जाओ out;
		पूर्ण

		err = begin_wqe(qp, &seg, &ctrl, wr, &idx, &size, &cur_edge,
				nreq);
		अगर (err) अणु
			mlx5_ib_warn(dev, "\n");
			err = -ENOMEM;
			*bad_wr = wr;
			जाओ out;
		पूर्ण

		अगर (wr->opcode == IB_WR_REG_MR ||
		    wr->opcode == IB_WR_REG_MR_INTEGRITY) अणु
			fence = dev->umr_fence;
			next_fence = MLX5_FENCE_MODE_INITIATOR_SMALL;
		पूर्ण अन्यथा  अणु
			अगर (wr->send_flags & IB_SEND_FENCE) अणु
				अगर (qp->next_fence)
					fence = MLX5_FENCE_MODE_SMALL_AND_FENCE;
				अन्यथा
					fence = MLX5_FENCE_MODE_FENCE;
			पूर्ण अन्यथा अणु
				fence = qp->next_fence;
			पूर्ण
		पूर्ण

		चयन (ibqp->qp_type) अणु
		हाल IB_QPT_XRC_INI:
			xrc = seg;
			seg += माप(*xrc);
			size += माप(*xrc) / 16;
			fallthrough;
		हाल IB_QPT_RC:
			err = handle_qpt_rc(dev, qp, wr, &ctrl, &seg, &size,
					    &cur_edge, &idx, nreq, fence,
					    next_fence, &num_sge);
			अगर (unlikely(err)) अणु
				*bad_wr = wr;
				जाओ out;
			पूर्ण अन्यथा अगर (wr->opcode == IB_WR_REG_MR_INTEGRITY) अणु
				जाओ skip_psv;
			पूर्ण
			अवरोध;

		हाल IB_QPT_UC:
			handle_qpt_uc(wr, &seg, &size);
			अवरोध;
		हाल IB_QPT_SMI:
			अगर (unlikely(!dev->port_caps[qp->port - 1].has_smi)) अणु
				mlx5_ib_warn(dev, "Send SMP MADs is not allowed\n");
				err = -EPERM;
				*bad_wr = wr;
				जाओ out;
			पूर्ण
			fallthrough;
		हाल MLX5_IB_QPT_HW_GSI:
			handle_qpt_hw_gsi(qp, wr, &seg, &size, &cur_edge);
			अवरोध;
		हाल IB_QPT_UD:
			handle_qpt_ud(qp, wr, &seg, &size, &cur_edge);
			अवरोध;
		हाल MLX5_IB_QPT_REG_UMR:
			err = handle_qpt_reg_umr(dev, qp, wr, &ctrl, &seg,
						       &size, &cur_edge, idx);
			अगर (unlikely(err))
				जाओ out;
			अवरोध;

		शेष:
			अवरोध;
		पूर्ण

		अगर (wr->send_flags & IB_SEND_INLINE && num_sge) अणु
			err = set_data_inl_seg(qp, wr, &seg, &size, &cur_edge);
			अगर (unlikely(err)) अणु
				mlx5_ib_warn(dev, "\n");
				*bad_wr = wr;
				जाओ out;
			पूर्ण
		पूर्ण अन्यथा अणु
			क्रम (i = 0; i < num_sge; i++) अणु
				handle_post_send_edge(&qp->sq, &seg, size,
						      &cur_edge);
				अगर (unlikely(!wr->sg_list[i].length))
					जारी;

				set_data_ptr_seg(
					(काष्ठा mlx5_wqe_data_seg *)seg,
					wr->sg_list + i);
				size += माप(काष्ठा mlx5_wqe_data_seg) / 16;
				seg += माप(काष्ठा mlx5_wqe_data_seg);
			पूर्ण
		पूर्ण

		qp->next_fence = next_fence;
		finish_wqe(qp, ctrl, seg, size, cur_edge, idx, wr->wr_id, nreq,
			   fence, mlx5_ib_opcode[wr->opcode]);
skip_psv:
		अगर (0)
			dump_wqe(qp, idx, size);
	पूर्ण

out:
	अगर (likely(nreq)) अणु
		qp->sq.head += nreq;

		/* Make sure that descriptors are written beक्रमe
		 * updating करोorbell record and ringing the करोorbell
		 */
		wmb();

		qp->db.db[MLX5_SND_DBR] = cpu_to_be32(qp->sq.cur_post);

		/* Make sure करोorbell record is visible to the HCA beक्रमe
		 * we hit करोorbell.
		 */
		wmb();

		mlx5_ग_लिखो64((__be32 *)ctrl, bf->bfreg->map + bf->offset);
		/* Make sure करोorbells करोn't leak out of SQ spinlock
		 * and reach the HCA out of order.
		 */
		bf->offset ^= bf->buf_size;
	पूर्ण

	spin_unlock_irqrestore(&qp->sq.lock, flags);

	वापस err;
पूर्ण

अटल व्योम set_sig_seg(काष्ठा mlx5_rwqe_sig *sig, पूर्णांक max_gs)
अणु
	 sig->signature = calc_sig(sig, (max_gs + 1) << 2);
पूर्ण

पूर्णांक mlx5_ib_post_recv(काष्ठा ib_qp *ibqp, स्थिर काष्ठा ib_recv_wr *wr,
		      स्थिर काष्ठा ib_recv_wr **bad_wr, bool drain)
अणु
	काष्ठा mlx5_ib_qp *qp = to_mqp(ibqp);
	काष्ठा mlx5_wqe_data_seg *scat;
	काष्ठा mlx5_rwqe_sig *sig;
	काष्ठा mlx5_ib_dev *dev = to_mdev(ibqp->device);
	काष्ठा mlx5_core_dev *mdev = dev->mdev;
	अचिन्हित दीर्घ flags;
	पूर्णांक err = 0;
	पूर्णांक nreq;
	पूर्णांक ind;
	पूर्णांक i;

	अगर (unlikely(mdev->state == MLX5_DEVICE_STATE_INTERNAL_ERROR &&
		     !drain)) अणु
		*bad_wr = wr;
		वापस -EIO;
	पूर्ण

	अगर (unlikely(ibqp->qp_type == IB_QPT_GSI))
		वापस mlx5_ib_gsi_post_recv(ibqp, wr, bad_wr);

	spin_lock_irqsave(&qp->rq.lock, flags);

	ind = qp->rq.head & (qp->rq.wqe_cnt - 1);

	क्रम (nreq = 0; wr; nreq++, wr = wr->next) अणु
		अगर (mlx5_wq_overflow(&qp->rq, nreq, qp->ibqp.recv_cq)) अणु
			err = -ENOMEM;
			*bad_wr = wr;
			जाओ out;
		पूर्ण

		अगर (unlikely(wr->num_sge > qp->rq.max_gs)) अणु
			err = -EINVAL;
			*bad_wr = wr;
			जाओ out;
		पूर्ण

		scat = mlx5_frag_buf_get_wqe(&qp->rq.fbc, ind);
		अगर (qp->flags_en & MLX5_QP_FLAG_SIGNATURE)
			scat++;

		क्रम (i = 0; i < wr->num_sge; i++)
			set_data_ptr_seg(scat + i, wr->sg_list + i);

		अगर (i < qp->rq.max_gs) अणु
			scat[i].byte_count = 0;
			scat[i].lkey       = cpu_to_be32(MLX5_INVALID_LKEY);
			scat[i].addr       = 0;
		पूर्ण

		अगर (qp->flags_en & MLX5_QP_FLAG_SIGNATURE) अणु
			sig = (काष्ठा mlx5_rwqe_sig *)scat;
			set_sig_seg(sig, qp->rq.max_gs);
		पूर्ण

		qp->rq.wrid[ind] = wr->wr_id;

		ind = (ind + 1) & (qp->rq.wqe_cnt - 1);
	पूर्ण

out:
	अगर (likely(nreq)) अणु
		qp->rq.head += nreq;

		/* Make sure that descriptors are written beक्रमe
		 * करोorbell record.
		 */
		wmb();

		*qp->db.db = cpu_to_be32(qp->rq.head & 0xffff);
	पूर्ण

	spin_unlock_irqrestore(&qp->rq.lock, flags);

	वापस err;
पूर्ण
