<शैली गुरु>
/*
 * Copyright (c) 2013-2015, Mellanox Technologies. All rights reserved.
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

#समावेश <linux/module.h>
#समावेश <rdma/ib_uस्मृति.स>
#समावेश <rdma/ib_umem_odp.h>
#समावेश "mlx5_ib.h"
#समावेश <linux/jअगरfies.h>

/*
 * Fill in a physical address list. ib_umem_num_dma_blocks() entries will be
 * filled in the pas array.
 */
व्योम mlx5_ib_populate_pas(काष्ठा ib_umem *umem, माप_प्रकार page_size, __be64 *pas,
			  u64 access_flags)
अणु
	काष्ठा ib_block_iter biter;

	rdma_umem_क्रम_each_dma_block (umem, &biter, page_size) अणु
		*pas = cpu_to_be64(rdma_block_iter_dma_address(&biter) |
				   access_flags);
		pas++;
	पूर्ण
पूर्ण

/*
 * Compute the page shअगरt and page_offset क्रम mailboxes that use a quantized
 * page_offset. The granulatity of the page offset scales according to page
 * size.
 */
अचिन्हित दीर्घ __mlx5_umem_find_best_quantized_pgoff(
	काष्ठा ib_umem *umem, अचिन्हित दीर्घ pgsz_biपंचांगap,
	अचिन्हित पूर्णांक page_offset_bits, u64 pgoff_biपंचांगask, अचिन्हित पूर्णांक scale,
	अचिन्हित पूर्णांक *page_offset_quantized)
अणु
	स्थिर u64 page_offset_mask = (1UL << page_offset_bits) - 1;
	अचिन्हित दीर्घ page_size;
	u64 page_offset;

	page_size = ib_umem_find_best_pgoff(umem, pgsz_biपंचांगap, pgoff_biपंचांगask);
	अगर (!page_size)
		वापस 0;

	/*
	 * page size is the largest possible page size.
	 *
	 * Reduce the page_size, and thus the page_offset and quanta, until the
	 * page_offset fits पूर्णांकo the mailbox field. Once page_size < scale this
	 * loop is guaranteed to terminate.
	 */
	page_offset = ib_umem_dma_offset(umem, page_size);
	जबतक (page_offset & ~(u64)(page_offset_mask * (page_size / scale))) अणु
		page_size /= 2;
		page_offset = ib_umem_dma_offset(umem, page_size);
	पूर्ण

	/*
	 * The address is not aligned, or otherwise cannot be represented by the
	 * page_offset.
	 */
	अगर (!(pgsz_biपंचांगap & page_size))
		वापस 0;

	*page_offset_quantized =
		(अचिन्हित दीर्घ)page_offset / (page_size / scale);
	अगर (WARN_ON(*page_offset_quantized > page_offset_mask))
		वापस 0;
	वापस page_size;
पूर्ण

#घोषणा WR_ID_BF 0xBF
#घोषणा WR_ID_END 0xBAD
#घोषणा TEST_WC_NUM_WQES 255
#घोषणा TEST_WC_POLLING_MAX_TIME_JIFFIES msecs_to_jअगरfies(100)
अटल पूर्णांक post_send_nop(काष्ठा mlx5_ib_dev *dev, काष्ठा ib_qp *ibqp, u64 wr_id,
			 bool संकेतed)
अणु
	काष्ठा mlx5_ib_qp *qp = to_mqp(ibqp);
	काष्ठा mlx5_wqe_ctrl_seg *ctrl;
	काष्ठा mlx5_bf *bf = &qp->bf;
	__be32 mmio_wqe[16] = अणुपूर्ण;
	अचिन्हित दीर्घ flags;
	अचिन्हित पूर्णांक idx;
	पूर्णांक i;

	अगर (unlikely(dev->mdev->state == MLX5_DEVICE_STATE_INTERNAL_ERROR))
		वापस -EIO;

	spin_lock_irqsave(&qp->sq.lock, flags);

	idx = qp->sq.cur_post & (qp->sq.wqe_cnt - 1);
	ctrl = mlx5_frag_buf_get_wqe(&qp->sq.fbc, idx);

	स_रखो(ctrl, 0, माप(काष्ठा mlx5_wqe_ctrl_seg));
	ctrl->fm_ce_se = संकेतed ? MLX5_WQE_CTRL_CQ_UPDATE : 0;
	ctrl->opmod_idx_opcode =
		cpu_to_be32(((u32)(qp->sq.cur_post) << 8) | MLX5_OPCODE_NOP);
	ctrl->qpn_ds = cpu_to_be32((माप(काष्ठा mlx5_wqe_ctrl_seg) / 16) |
				   (qp->trans_qp.base.mqp.qpn << 8));

	qp->sq.wrid[idx] = wr_id;
	qp->sq.w_list[idx].opcode = MLX5_OPCODE_NOP;
	qp->sq.wqe_head[idx] = qp->sq.head + 1;
	qp->sq.cur_post += DIV_ROUND_UP(माप(काष्ठा mlx5_wqe_ctrl_seg),
					MLX5_SEND_WQE_BB);
	qp->sq.w_list[idx].next = qp->sq.cur_post;
	qp->sq.head++;

	स_नकल(mmio_wqe, ctrl, माप(*ctrl));
	((काष्ठा mlx5_wqe_ctrl_seg *)&mmio_wqe)->fm_ce_se |=
		MLX5_WQE_CTRL_CQ_UPDATE;

	/* Make sure that descriptors are written beक्रमe
	 * updating करोorbell record and ringing the करोorbell
	 */
	wmb();

	qp->db.db[MLX5_SND_DBR] = cpu_to_be32(qp->sq.cur_post);

	/* Make sure करोorbell record is visible to the HCA beक्रमe
	 * we hit करोorbell
	 */
	wmb();
	क्रम (i = 0; i < 8; i++)
		mlx5_ग_लिखो64(&mmio_wqe[i * 2],
			     bf->bfreg->map + bf->offset + i * 8);

	bf->offset ^= bf->buf_size;

	spin_unlock_irqrestore(&qp->sq.lock, flags);

	वापस 0;
पूर्ण

अटल पूर्णांक test_wc_poll_cq_result(काष्ठा mlx5_ib_dev *dev, काष्ठा ib_cq *cq)
अणु
	पूर्णांक ret;
	काष्ठा ib_wc wc = अणुपूर्ण;
	अचिन्हित दीर्घ end = jअगरfies + TEST_WC_POLLING_MAX_TIME_JIFFIES;

	करो अणु
		ret = ib_poll_cq(cq, 1, &wc);
		अगर (ret < 0 || wc.status)
			वापस ret < 0 ? ret : -EINVAL;
		अगर (ret)
			अवरोध;
	पूर्ण जबतक (!समय_after(jअगरfies, end));

	अगर (!ret)
		वापस -ETIMEDOUT;

	अगर (wc.wr_id != WR_ID_BF)
		ret = 0;

	वापस ret;
पूर्ण

अटल पूर्णांक test_wc_करो_send(काष्ठा mlx5_ib_dev *dev, काष्ठा ib_qp *qp)
अणु
	पूर्णांक err, i;

	क्रम (i = 0; i < TEST_WC_NUM_WQES; i++) अणु
		err = post_send_nop(dev, qp, WR_ID_BF, false);
		अगर (err)
			वापस err;
	पूर्ण

	वापस post_send_nop(dev, qp, WR_ID_END, true);
पूर्ण

पूर्णांक mlx5_ib_test_wc(काष्ठा mlx5_ib_dev *dev)
अणु
	काष्ठा ib_cq_init_attr cq_attr = अणु .cqe = TEST_WC_NUM_WQES + 1 पूर्ण;
	पूर्णांक port_type_cap = MLX5_CAP_GEN(dev->mdev, port_type);
	काष्ठा ib_qp_init_attr qp_init_attr = अणु
		.cap = अणु .max_send_wr = TEST_WC_NUM_WQES पूर्ण,
		.qp_type = IB_QPT_UD,
		.sq_sig_type = IB_SIGNAL_REQ_WR,
		.create_flags = MLX5_IB_QP_CREATE_WC_TEST,
	पूर्ण;
	काष्ठा ib_qp_attr qp_attr = अणु .port_num = 1 पूर्ण;
	काष्ठा ib_device *ibdev = &dev->ib_dev;
	काष्ठा ib_qp *qp;
	काष्ठा ib_cq *cq;
	काष्ठा ib_pd *pd;
	पूर्णांक ret;

	अगर (!MLX5_CAP_GEN(dev->mdev, bf))
		वापस 0;

	अगर (!dev->mdev->roce.roce_en &&
	    port_type_cap == MLX5_CAP_PORT_TYPE_ETH) अणु
		अगर (mlx5_core_is_pf(dev->mdev))
			dev->wc_support = arch_can_pci_mmap_wc();
		वापस 0;
	पूर्ण

	ret = mlx5_alloc_bfreg(dev->mdev, &dev->wc_bfreg, true, false);
	अगर (ret)
		जाओ prपूर्णांक_err;

	अगर (!dev->wc_bfreg.wc)
		जाओ out1;

	pd = ib_alloc_pd(ibdev, 0);
	अगर (IS_ERR(pd)) अणु
		ret = PTR_ERR(pd);
		जाओ out1;
	पूर्ण

	cq = ib_create_cq(ibdev, शून्य, शून्य, शून्य, &cq_attr);
	अगर (IS_ERR(cq)) अणु
		ret = PTR_ERR(cq);
		जाओ out2;
	पूर्ण

	qp_init_attr.recv_cq = cq;
	qp_init_attr.send_cq = cq;
	qp = ib_create_qp(pd, &qp_init_attr);
	अगर (IS_ERR(qp)) अणु
		ret = PTR_ERR(qp);
		जाओ out3;
	पूर्ण

	qp_attr.qp_state = IB_QPS_INIT;
	ret = ib_modअगरy_qp(qp, &qp_attr,
			   IB_QP_STATE | IB_QP_PORT | IB_QP_PKEY_INDEX |
				   IB_QP_QKEY);
	अगर (ret)
		जाओ out4;

	qp_attr.qp_state = IB_QPS_RTR;
	ret = ib_modअगरy_qp(qp, &qp_attr, IB_QP_STATE);
	अगर (ret)
		जाओ out4;

	qp_attr.qp_state = IB_QPS_RTS;
	ret = ib_modअगरy_qp(qp, &qp_attr, IB_QP_STATE | IB_QP_SQ_PSN);
	अगर (ret)
		जाओ out4;

	ret = test_wc_करो_send(dev, qp);
	अगर (ret < 0)
		जाओ out4;

	ret = test_wc_poll_cq_result(dev, cq);
	अगर (ret > 0) अणु
		dev->wc_support = true;
		ret = 0;
	पूर्ण

out4:
	ib_destroy_qp(qp);
out3:
	ib_destroy_cq(cq);
out2:
	ib_dealloc_pd(pd);
out1:
	mlx5_मुक्त_bfreg(dev->mdev, &dev->wc_bfreg);
prपूर्णांक_err:
	अगर (ret)
		mlx5_ib_err(
			dev,
			"Error %d while trying to test write-combining support\n",
			ret);
	वापस ret;
पूर्ण
