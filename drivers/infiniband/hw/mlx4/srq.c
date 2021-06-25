<शैली गुरु>
/*
 * Copyright (c) 2007 Cisco Systems, Inc. All rights reserved.
 * Copyright (c) 2007, 2008 Mellanox Technologies. All rights reserved.
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

#समावेश <linux/mlx4/qp.h>
#समावेश <linux/mlx4/srq.h>
#समावेश <linux/slab.h>

#समावेश "mlx4_ib.h"
#समावेश <rdma/mlx4-abi.h>
#समावेश <rdma/uverbs_ioctl.h>

अटल व्योम *get_wqe(काष्ठा mlx4_ib_srq *srq, पूर्णांक n)
अणु
	वापस mlx4_buf_offset(&srq->buf, n << srq->msrq.wqe_shअगरt);
पूर्ण

अटल व्योम mlx4_ib_srq_event(काष्ठा mlx4_srq *srq, क्रमागत mlx4_event type)
अणु
	काष्ठा ib_event event;
	काष्ठा ib_srq *ibsrq = &to_mibsrq(srq)->ibsrq;

	अगर (ibsrq->event_handler) अणु
		event.device      = ibsrq->device;
		event.element.srq = ibsrq;
		चयन (type) अणु
		हाल MLX4_EVENT_TYPE_SRQ_LIMIT:
			event.event = IB_EVENT_SRQ_LIMIT_REACHED;
			अवरोध;
		हाल MLX4_EVENT_TYPE_SRQ_CATAS_ERROR:
			event.event = IB_EVENT_SRQ_ERR;
			अवरोध;
		शेष:
			pr_warn("Unexpected event type %d "
			       "on SRQ %06x\n", type, srq->srqn);
			वापस;
		पूर्ण

		ibsrq->event_handler(&event, ibsrq->srq_context);
	पूर्ण
पूर्ण

पूर्णांक mlx4_ib_create_srq(काष्ठा ib_srq *ib_srq,
		       काष्ठा ib_srq_init_attr *init_attr,
		       काष्ठा ib_udata *udata)
अणु
	काष्ठा mlx4_ib_dev *dev = to_mdev(ib_srq->device);
	काष्ठा mlx4_ib_ucontext *ucontext = rdma_udata_to_drv_context(
		udata, काष्ठा mlx4_ib_ucontext, ibucontext);
	काष्ठा mlx4_ib_srq *srq = to_msrq(ib_srq);
	काष्ठा mlx4_wqe_srq_next_seg *next;
	काष्ठा mlx4_wqe_data_seg *scatter;
	u32 cqn;
	u16 xrcdn;
	पूर्णांक desc_size;
	पूर्णांक buf_size;
	पूर्णांक err;
	पूर्णांक i;

	अगर (init_attr->srq_type != IB_SRQT_BASIC &&
	    init_attr->srq_type != IB_SRQT_XRC)
		वापस -EOPNOTSUPP;

	/* Sanity check SRQ size beक्रमe proceeding */
	अगर (init_attr->attr.max_wr  >= dev->dev->caps.max_srq_wqes ||
	    init_attr->attr.max_sge >  dev->dev->caps.max_srq_sge)
		वापस -EINVAL;

	mutex_init(&srq->mutex);
	spin_lock_init(&srq->lock);
	srq->msrq.max    = roundup_घात_of_two(init_attr->attr.max_wr + 1);
	srq->msrq.max_gs = init_attr->attr.max_sge;

	desc_size = max(32UL,
			roundup_घात_of_two(माप (काष्ठा mlx4_wqe_srq_next_seg) +
					   srq->msrq.max_gs *
					   माप (काष्ठा mlx4_wqe_data_seg)));
	srq->msrq.wqe_shअगरt = ilog2(desc_size);

	buf_size = srq->msrq.max * desc_size;

	अगर (udata) अणु
		काष्ठा mlx4_ib_create_srq ucmd;

		अगर (ib_copy_from_udata(&ucmd, udata, माप(ucmd)))
			वापस -EFAULT;

		srq->umem =
			ib_umem_get(ib_srq->device, ucmd.buf_addr, buf_size, 0);
		अगर (IS_ERR(srq->umem))
			वापस PTR_ERR(srq->umem);

		err = mlx4_mtt_init(
			dev->dev, ib_umem_num_dma_blocks(srq->umem, PAGE_SIZE),
			PAGE_SHIFT, &srq->mtt);
		अगर (err)
			जाओ err_buf;

		err = mlx4_ib_umem_ग_लिखो_mtt(dev, &srq->mtt, srq->umem);
		अगर (err)
			जाओ err_mtt;

		err = mlx4_ib_db_map_user(udata, ucmd.db_addr, &srq->db);
		अगर (err)
			जाओ err_mtt;
	पूर्ण अन्यथा अणु
		err = mlx4_db_alloc(dev->dev, &srq->db, 0);
		अगर (err)
			वापस err;

		*srq->db.db = 0;

		अगर (mlx4_buf_alloc(dev->dev, buf_size, PAGE_SIZE * 2,
				   &srq->buf)) अणु
			err = -ENOMEM;
			जाओ err_db;
		पूर्ण

		srq->head    = 0;
		srq->tail    = srq->msrq.max - 1;
		srq->wqe_ctr = 0;

		क्रम (i = 0; i < srq->msrq.max; ++i) अणु
			next = get_wqe(srq, i);
			next->next_wqe_index =
				cpu_to_be16((i + 1) & (srq->msrq.max - 1));

			क्रम (scatter = (व्योम *) (next + 1);
			     (व्योम *) scatter < (व्योम *) next + desc_size;
			     ++scatter)
				scatter->lkey = cpu_to_be32(MLX4_INVALID_LKEY);
		पूर्ण

		err = mlx4_mtt_init(dev->dev, srq->buf.npages, srq->buf.page_shअगरt,
				    &srq->mtt);
		अगर (err)
			जाओ err_buf;

		err = mlx4_buf_ग_लिखो_mtt(dev->dev, &srq->mtt, &srq->buf);
		अगर (err)
			जाओ err_mtt;

		srq->wrid = kvदो_स्मृति_array(srq->msrq.max,
					   माप(u64), GFP_KERNEL);
		अगर (!srq->wrid) अणु
			err = -ENOMEM;
			जाओ err_mtt;
		पूर्ण
	पूर्ण

	cqn = ib_srq_has_cq(init_attr->srq_type) ?
		to_mcq(init_attr->ext.cq)->mcq.cqn : 0;
	xrcdn = (init_attr->srq_type == IB_SRQT_XRC) ?
		to_mxrcd(init_attr->ext.xrc.xrcd)->xrcdn :
		(u16) dev->dev->caps.reserved_xrcds;
	err = mlx4_srq_alloc(dev->dev, to_mpd(ib_srq->pd)->pdn, cqn, xrcdn,
			     &srq->mtt, srq->db.dma, &srq->msrq);
	अगर (err)
		जाओ err_wrid;

	srq->msrq.event = mlx4_ib_srq_event;
	srq->ibsrq.ext.xrc.srq_num = srq->msrq.srqn;

	अगर (udata)
		अगर (ib_copy_to_udata(udata, &srq->msrq.srqn, माप (__u32))) अणु
			err = -EFAULT;
			जाओ err_wrid;
		पूर्ण

	init_attr->attr.max_wr = srq->msrq.max - 1;

	वापस 0;

err_wrid:
	अगर (udata)
		mlx4_ib_db_unmap_user(ucontext, &srq->db);
	अन्यथा
		kvमुक्त(srq->wrid);

err_mtt:
	mlx4_mtt_cleanup(dev->dev, &srq->mtt);

err_buf:
	अगर (!srq->umem)
		mlx4_buf_मुक्त(dev->dev, buf_size, &srq->buf);
	ib_umem_release(srq->umem);

err_db:
	अगर (!udata)
		mlx4_db_मुक्त(dev->dev, &srq->db);

	वापस err;
पूर्ण

पूर्णांक mlx4_ib_modअगरy_srq(काष्ठा ib_srq *ibsrq, काष्ठा ib_srq_attr *attr,
		       क्रमागत ib_srq_attr_mask attr_mask, काष्ठा ib_udata *udata)
अणु
	काष्ठा mlx4_ib_dev *dev = to_mdev(ibsrq->device);
	काष्ठा mlx4_ib_srq *srq = to_msrq(ibsrq);
	पूर्णांक ret;

	/* We करोn't support resizing SRQs (yet?) */
	अगर (attr_mask & IB_SRQ_MAX_WR)
		वापस -EINVAL;

	अगर (attr_mask & IB_SRQ_LIMIT) अणु
		अगर (attr->srq_limit >= srq->msrq.max)
			वापस -EINVAL;

		mutex_lock(&srq->mutex);
		ret = mlx4_srq_arm(dev->dev, &srq->msrq, attr->srq_limit);
		mutex_unlock(&srq->mutex);

		अगर (ret)
			वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

पूर्णांक mlx4_ib_query_srq(काष्ठा ib_srq *ibsrq, काष्ठा ib_srq_attr *srq_attr)
अणु
	काष्ठा mlx4_ib_dev *dev = to_mdev(ibsrq->device);
	काष्ठा mlx4_ib_srq *srq = to_msrq(ibsrq);
	पूर्णांक ret;
	पूर्णांक limit_watermark;

	ret = mlx4_srq_query(dev->dev, &srq->msrq, &limit_watermark);
	अगर (ret)
		वापस ret;

	srq_attr->srq_limit = limit_watermark;
	srq_attr->max_wr    = srq->msrq.max - 1;
	srq_attr->max_sge   = srq->msrq.max_gs;

	वापस 0;
पूर्ण

पूर्णांक mlx4_ib_destroy_srq(काष्ठा ib_srq *srq, काष्ठा ib_udata *udata)
अणु
	काष्ठा mlx4_ib_dev *dev = to_mdev(srq->device);
	काष्ठा mlx4_ib_srq *msrq = to_msrq(srq);

	mlx4_srq_मुक्त(dev->dev, &msrq->msrq);
	mlx4_mtt_cleanup(dev->dev, &msrq->mtt);

	अगर (udata) अणु
		mlx4_ib_db_unmap_user(
			rdma_udata_to_drv_context(
				udata,
				काष्ठा mlx4_ib_ucontext,
				ibucontext),
			&msrq->db);
	पूर्ण अन्यथा अणु
		kvमुक्त(msrq->wrid);
		mlx4_buf_मुक्त(dev->dev, msrq->msrq.max << msrq->msrq.wqe_shअगरt,
			      &msrq->buf);
		mlx4_db_मुक्त(dev->dev, &msrq->db);
	पूर्ण
	ib_umem_release(msrq->umem);
	वापस 0;
पूर्ण

व्योम mlx4_ib_मुक्त_srq_wqe(काष्ठा mlx4_ib_srq *srq, पूर्णांक wqe_index)
अणु
	काष्ठा mlx4_wqe_srq_next_seg *next;

	/* always called with पूर्णांकerrupts disabled. */
	spin_lock(&srq->lock);

	next = get_wqe(srq, srq->tail);
	next->next_wqe_index = cpu_to_be16(wqe_index);
	srq->tail = wqe_index;

	spin_unlock(&srq->lock);
पूर्ण

पूर्णांक mlx4_ib_post_srq_recv(काष्ठा ib_srq *ibsrq, स्थिर काष्ठा ib_recv_wr *wr,
			  स्थिर काष्ठा ib_recv_wr **bad_wr)
अणु
	काष्ठा mlx4_ib_srq *srq = to_msrq(ibsrq);
	काष्ठा mlx4_wqe_srq_next_seg *next;
	काष्ठा mlx4_wqe_data_seg *scat;
	अचिन्हित दीर्घ flags;
	पूर्णांक err = 0;
	पूर्णांक nreq;
	पूर्णांक i;
	काष्ठा mlx4_ib_dev *mdev = to_mdev(ibsrq->device);

	spin_lock_irqsave(&srq->lock, flags);
	अगर (mdev->dev->persist->state & MLX4_DEVICE_STATE_INTERNAL_ERROR) अणु
		err = -EIO;
		*bad_wr = wr;
		nreq = 0;
		जाओ out;
	पूर्ण

	क्रम (nreq = 0; wr; ++nreq, wr = wr->next) अणु
		अगर (unlikely(wr->num_sge > srq->msrq.max_gs)) अणु
			err = -EINVAL;
			*bad_wr = wr;
			अवरोध;
		पूर्ण

		अगर (unlikely(srq->head == srq->tail)) अणु
			err = -ENOMEM;
			*bad_wr = wr;
			अवरोध;
		पूर्ण

		srq->wrid[srq->head] = wr->wr_id;

		next      = get_wqe(srq, srq->head);
		srq->head = be16_to_cpu(next->next_wqe_index);
		scat      = (काष्ठा mlx4_wqe_data_seg *) (next + 1);

		क्रम (i = 0; i < wr->num_sge; ++i) अणु
			scat[i].byte_count = cpu_to_be32(wr->sg_list[i].length);
			scat[i].lkey       = cpu_to_be32(wr->sg_list[i].lkey);
			scat[i].addr       = cpu_to_be64(wr->sg_list[i].addr);
		पूर्ण

		अगर (i < srq->msrq.max_gs) अणु
			scat[i].byte_count = 0;
			scat[i].lkey       = cpu_to_be32(MLX4_INVALID_LKEY);
			scat[i].addr       = 0;
		पूर्ण
	पूर्ण

	अगर (likely(nreq)) अणु
		srq->wqe_ctr += nreq;

		/*
		 * Make sure that descriptors are written beक्रमe
		 * करोorbell record.
		 */
		wmb();

		*srq->db.db = cpu_to_be32(srq->wqe_ctr);
	पूर्ण
out:

	spin_unlock_irqrestore(&srq->lock, flags);

	वापस err;
पूर्ण
