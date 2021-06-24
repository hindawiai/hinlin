<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0 OR Linux-OpenIB
/*
 * Copyright (c) 2013-2018, Mellanox Technologies inc.  All rights reserved.
 */

#समावेश <linux/module.h>
#समावेश <linux/mlx5/qp.h>
#समावेश <linux/slab.h>
#समावेश <rdma/ib_uस्मृति.स>
#समावेश <rdma/ib_user_verbs.h>
#समावेश "mlx5_ib.h"
#समावेश "srq.h"

अटल व्योम *get_wqe(काष्ठा mlx5_ib_srq *srq, पूर्णांक n)
अणु
	वापस mlx5_frag_buf_get_wqe(&srq->fbc, n);
पूर्ण

अटल व्योम mlx5_ib_srq_event(काष्ठा mlx5_core_srq *srq, क्रमागत mlx5_event type)
अणु
	काष्ठा ib_event event;
	काष्ठा ib_srq *ibsrq = &to_mibsrq(srq)->ibsrq;

	अगर (ibsrq->event_handler) अणु
		event.device      = ibsrq->device;
		event.element.srq = ibsrq;
		चयन (type) अणु
		हाल MLX5_EVENT_TYPE_SRQ_RQ_LIMIT:
			event.event = IB_EVENT_SRQ_LIMIT_REACHED;
			अवरोध;
		हाल MLX5_EVENT_TYPE_SRQ_CATAS_ERROR:
			event.event = IB_EVENT_SRQ_ERR;
			अवरोध;
		शेष:
			pr_warn("mlx5_ib: Unexpected event type %d on SRQ %06x\n",
				type, srq->srqn);
			वापस;
		पूर्ण

		ibsrq->event_handler(&event, ibsrq->srq_context);
	पूर्ण
पूर्ण

अटल पूर्णांक create_srq_user(काष्ठा ib_pd *pd, काष्ठा mlx5_ib_srq *srq,
			   काष्ठा mlx5_srq_attr *in,
			   काष्ठा ib_udata *udata, पूर्णांक buf_size)
अणु
	काष्ठा mlx5_ib_dev *dev = to_mdev(pd->device);
	काष्ठा mlx5_ib_create_srq ucmd = अणुपूर्ण;
	काष्ठा mlx5_ib_ucontext *ucontext = rdma_udata_to_drv_context(
		udata, काष्ठा mlx5_ib_ucontext, ibucontext);
	माप_प्रकार ucmdlen;
	पूर्णांक err;
	u32 uidx = MLX5_IB_DEFAULT_UIDX;

	ucmdlen = min(udata->inlen, माप(ucmd));

	अगर (ib_copy_from_udata(&ucmd, udata, ucmdlen)) अणु
		mlx5_ib_dbg(dev, "failed copy udata\n");
		वापस -EFAULT;
	पूर्ण

	अगर (ucmd.reserved0 || ucmd.reserved1)
		वापस -EINVAL;

	अगर (udata->inlen > माप(ucmd) &&
	    !ib_is_udata_cleared(udata, माप(ucmd),
				 udata->inlen - माप(ucmd)))
		वापस -EINVAL;

	अगर (in->type != IB_SRQT_BASIC) अणु
		err = get_srq_user_index(ucontext, &ucmd, udata->inlen, &uidx);
		अगर (err)
			वापस err;
	पूर्ण

	srq->wq_sig = !!(ucmd.flags & MLX5_SRQ_FLAG_SIGNATURE);

	srq->umem = ib_umem_get(pd->device, ucmd.buf_addr, buf_size, 0);
	अगर (IS_ERR(srq->umem)) अणु
		mlx5_ib_dbg(dev, "failed umem get, size %d\n", buf_size);
		err = PTR_ERR(srq->umem);
		वापस err;
	पूर्ण
	in->umem = srq->umem;

	err = mlx5_ib_db_map_user(ucontext, udata, ucmd.db_addr, &srq->db);
	अगर (err) अणु
		mlx5_ib_dbg(dev, "map doorbell failed\n");
		जाओ err_umem;
	पूर्ण

	in->uid = (in->type != IB_SRQT_XRC) ?  to_mpd(pd)->uid : 0;
	अगर (MLX5_CAP_GEN(dev->mdev, cqe_version) == MLX5_CQE_VERSION_V1 &&
	    in->type != IB_SRQT_BASIC)
		in->user_index = uidx;

	वापस 0;

err_umem:
	ib_umem_release(srq->umem);

	वापस err;
पूर्ण

अटल पूर्णांक create_srq_kernel(काष्ठा mlx5_ib_dev *dev, काष्ठा mlx5_ib_srq *srq,
			     काष्ठा mlx5_srq_attr *in, पूर्णांक buf_size)
अणु
	पूर्णांक err;
	पूर्णांक i;
	काष्ठा mlx5_wqe_srq_next_seg *next;

	err = mlx5_db_alloc(dev->mdev, &srq->db);
	अगर (err) अणु
		mlx5_ib_warn(dev, "alloc dbell rec failed\n");
		वापस err;
	पूर्ण

	अगर (mlx5_frag_buf_alloc_node(dev->mdev, buf_size, &srq->buf,
				     dev->mdev->priv.numa_node)) अणु
		mlx5_ib_dbg(dev, "buf alloc failed\n");
		err = -ENOMEM;
		जाओ err_db;
	पूर्ण

	mlx5_init_fbc(srq->buf.frags, srq->msrq.wqe_shअगरt, ilog2(srq->msrq.max),
		      &srq->fbc);

	srq->head    = 0;
	srq->tail    = srq->msrq.max - 1;
	srq->wqe_ctr = 0;

	क्रम (i = 0; i < srq->msrq.max; i++) अणु
		next = get_wqe(srq, i);
		next->next_wqe_index =
			cpu_to_be16((i + 1) & (srq->msrq.max - 1));
	पूर्ण

	mlx5_ib_dbg(dev, "srq->buf.page_shift = %d\n", srq->buf.page_shअगरt);
	in->pas = kvसुस्मृति(srq->buf.npages, माप(*in->pas), GFP_KERNEL);
	अगर (!in->pas) अणु
		err = -ENOMEM;
		जाओ err_buf;
	पूर्ण
	mlx5_fill_page_frag_array(&srq->buf, in->pas);

	srq->wrid = kvदो_स्मृति_array(srq->msrq.max, माप(u64), GFP_KERNEL);
	अगर (!srq->wrid) अणु
		err = -ENOMEM;
		जाओ err_in;
	पूर्ण
	srq->wq_sig = 0;

	in->log_page_size = srq->buf.page_shअगरt - MLX5_ADAPTER_PAGE_SHIFT;
	अगर (MLX5_CAP_GEN(dev->mdev, cqe_version) == MLX5_CQE_VERSION_V1 &&
	    in->type != IB_SRQT_BASIC)
		in->user_index = MLX5_IB_DEFAULT_UIDX;

	वापस 0;

err_in:
	kvमुक्त(in->pas);

err_buf:
	mlx5_frag_buf_मुक्त(dev->mdev, &srq->buf);

err_db:
	mlx5_db_मुक्त(dev->mdev, &srq->db);
	वापस err;
पूर्ण

अटल व्योम destroy_srq_user(काष्ठा ib_pd *pd, काष्ठा mlx5_ib_srq *srq,
			     काष्ठा ib_udata *udata)
अणु
	mlx5_ib_db_unmap_user(
		rdma_udata_to_drv_context(
			udata,
			काष्ठा mlx5_ib_ucontext,
			ibucontext),
		&srq->db);
	ib_umem_release(srq->umem);
पूर्ण


अटल व्योम destroy_srq_kernel(काष्ठा mlx5_ib_dev *dev, काष्ठा mlx5_ib_srq *srq)
अणु
	kvमुक्त(srq->wrid);
	mlx5_frag_buf_मुक्त(dev->mdev, &srq->buf);
	mlx5_db_मुक्त(dev->mdev, &srq->db);
पूर्ण

पूर्णांक mlx5_ib_create_srq(काष्ठा ib_srq *ib_srq,
		       काष्ठा ib_srq_init_attr *init_attr,
		       काष्ठा ib_udata *udata)
अणु
	काष्ठा mlx5_ib_dev *dev = to_mdev(ib_srq->device);
	काष्ठा mlx5_ib_srq *srq = to_msrq(ib_srq);
	माप_प्रकार desc_size;
	माप_प्रकार buf_size;
	पूर्णांक err;
	काष्ठा mlx5_srq_attr in = अणुपूर्ण;
	__u32 max_srq_wqes = 1 << MLX5_CAP_GEN(dev->mdev, log_max_srq_sz);

	अगर (init_attr->srq_type != IB_SRQT_BASIC &&
	    init_attr->srq_type != IB_SRQT_XRC &&
	    init_attr->srq_type != IB_SRQT_TM)
		वापस -EOPNOTSUPP;

	/* Sanity check SRQ size beक्रमe proceeding */
	अगर (init_attr->attr.max_wr >= max_srq_wqes) अणु
		mlx5_ib_dbg(dev, "max_wr %d, cap %d\n",
			    init_attr->attr.max_wr,
			    max_srq_wqes);
		वापस -EINVAL;
	पूर्ण

	mutex_init(&srq->mutex);
	spin_lock_init(&srq->lock);
	srq->msrq.max    = roundup_घात_of_two(init_attr->attr.max_wr + 1);
	srq->msrq.max_gs = init_attr->attr.max_sge;

	desc_size = माप(काष्ठा mlx5_wqe_srq_next_seg) +
		    srq->msrq.max_gs * माप(काष्ठा mlx5_wqe_data_seg);
	अगर (desc_size == 0 || srq->msrq.max_gs > desc_size)
		वापस -EINVAL;

	desc_size = roundup_घात_of_two(desc_size);
	desc_size = max_t(माप_प्रकार, 32, desc_size);
	अगर (desc_size < माप(काष्ठा mlx5_wqe_srq_next_seg))
		वापस -EINVAL;

	srq->msrq.max_avail_gather = (desc_size - माप(काष्ठा mlx5_wqe_srq_next_seg)) /
		माप(काष्ठा mlx5_wqe_data_seg);
	srq->msrq.wqe_shअगरt = ilog2(desc_size);
	buf_size = srq->msrq.max * desc_size;
	अगर (buf_size < desc_size)
		वापस -EINVAL;

	in.type = init_attr->srq_type;

	अगर (udata)
		err = create_srq_user(ib_srq->pd, srq, &in, udata, buf_size);
	अन्यथा
		err = create_srq_kernel(dev, srq, &in, buf_size);

	अगर (err) अणु
		mlx5_ib_warn(dev, "create srq %s failed, err %d\n",
			     udata ? "user" : "kernel", err);
		वापस err;
	पूर्ण

	in.log_size = ilog2(srq->msrq.max);
	in.wqe_shअगरt = srq->msrq.wqe_shअगरt - 4;
	अगर (srq->wq_sig)
		in.flags |= MLX5_SRQ_FLAG_WQ_SIG;

	अगर (init_attr->srq_type == IB_SRQT_XRC && init_attr->ext.xrc.xrcd)
		in.xrcd = to_mxrcd(init_attr->ext.xrc.xrcd)->xrcdn;
	अन्यथा
		in.xrcd = dev->devr.xrcdn0;

	अगर (init_attr->srq_type == IB_SRQT_TM) अणु
		in.पंचांग_log_list_size =
			ilog2(init_attr->ext.tag_matching.max_num_tags) + 1;
		अगर (in.पंचांग_log_list_size >
		    MLX5_CAP_GEN(dev->mdev, log_tag_matching_list_sz)) अणु
			mlx5_ib_dbg(dev, "TM SRQ max_num_tags exceeding limit\n");
			err = -EINVAL;
			जाओ err_usr_kern_srq;
		पूर्ण
		in.flags |= MLX5_SRQ_FLAG_RNDV;
	पूर्ण

	अगर (ib_srq_has_cq(init_attr->srq_type))
		in.cqn = to_mcq(init_attr->ext.cq)->mcq.cqn;
	अन्यथा
		in.cqn = to_mcq(dev->devr.c0)->mcq.cqn;

	in.pd = to_mpd(ib_srq->pd)->pdn;
	in.db_record = srq->db.dma;
	err = mlx5_cmd_create_srq(dev, &srq->msrq, &in);
	kvमुक्त(in.pas);
	अगर (err) अणु
		mlx5_ib_dbg(dev, "create SRQ failed, err %d\n", err);
		जाओ err_usr_kern_srq;
	पूर्ण

	mlx5_ib_dbg(dev, "create SRQ with srqn 0x%x\n", srq->msrq.srqn);

	srq->msrq.event = mlx5_ib_srq_event;
	srq->ibsrq.ext.xrc.srq_num = srq->msrq.srqn;

	अगर (udata) अणु
		काष्ठा mlx5_ib_create_srq_resp resp = अणु
			.srqn = srq->msrq.srqn,
		पूर्ण;

		अगर (ib_copy_to_udata(udata, &resp, min(udata->outlen,
				     माप(resp)))) अणु
			mlx5_ib_dbg(dev, "copy to user failed\n");
			err = -EFAULT;
			जाओ err_core;
		पूर्ण
	पूर्ण

	init_attr->attr.max_wr = srq->msrq.max - 1;

	वापस 0;

err_core:
	mlx5_cmd_destroy_srq(dev, &srq->msrq);

err_usr_kern_srq:
	अगर (udata)
		destroy_srq_user(ib_srq->pd, srq, udata);
	अन्यथा
		destroy_srq_kernel(dev, srq);

	वापस err;
पूर्ण

पूर्णांक mlx5_ib_modअगरy_srq(काष्ठा ib_srq *ibsrq, काष्ठा ib_srq_attr *attr,
		       क्रमागत ib_srq_attr_mask attr_mask, काष्ठा ib_udata *udata)
अणु
	काष्ठा mlx5_ib_dev *dev = to_mdev(ibsrq->device);
	काष्ठा mlx5_ib_srq *srq = to_msrq(ibsrq);
	पूर्णांक ret;

	/* We करोn't support resizing SRQs yet */
	अगर (attr_mask & IB_SRQ_MAX_WR)
		वापस -EINVAL;

	अगर (attr_mask & IB_SRQ_LIMIT) अणु
		अगर (attr->srq_limit >= srq->msrq.max)
			वापस -EINVAL;

		mutex_lock(&srq->mutex);
		ret = mlx5_cmd_arm_srq(dev, &srq->msrq, attr->srq_limit, 1);
		mutex_unlock(&srq->mutex);

		अगर (ret)
			वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

पूर्णांक mlx5_ib_query_srq(काष्ठा ib_srq *ibsrq, काष्ठा ib_srq_attr *srq_attr)
अणु
	काष्ठा mlx5_ib_dev *dev = to_mdev(ibsrq->device);
	काष्ठा mlx5_ib_srq *srq = to_msrq(ibsrq);
	पूर्णांक ret;
	काष्ठा mlx5_srq_attr *out;

	out = kzalloc(माप(*out), GFP_KERNEL);
	अगर (!out)
		वापस -ENOMEM;

	ret = mlx5_cmd_query_srq(dev, &srq->msrq, out);
	अगर (ret)
		जाओ out_box;

	srq_attr->srq_limit = out->lwm;
	srq_attr->max_wr    = srq->msrq.max - 1;
	srq_attr->max_sge   = srq->msrq.max_gs;

out_box:
	kमुक्त(out);
	वापस ret;
पूर्ण

पूर्णांक mlx5_ib_destroy_srq(काष्ठा ib_srq *srq, काष्ठा ib_udata *udata)
अणु
	काष्ठा mlx5_ib_dev *dev = to_mdev(srq->device);
	काष्ठा mlx5_ib_srq *msrq = to_msrq(srq);
	पूर्णांक ret;

	ret = mlx5_cmd_destroy_srq(dev, &msrq->msrq);
	अगर (ret)
		वापस ret;

	अगर (udata)
		destroy_srq_user(srq->pd, msrq, udata);
	अन्यथा
		destroy_srq_kernel(dev, msrq);
	वापस 0;
पूर्ण

व्योम mlx5_ib_मुक्त_srq_wqe(काष्ठा mlx5_ib_srq *srq, पूर्णांक wqe_index)
अणु
	काष्ठा mlx5_wqe_srq_next_seg *next;

	/* always called with पूर्णांकerrupts disabled. */
	spin_lock(&srq->lock);

	next = get_wqe(srq, srq->tail);
	next->next_wqe_index = cpu_to_be16(wqe_index);
	srq->tail = wqe_index;

	spin_unlock(&srq->lock);
पूर्ण

पूर्णांक mlx5_ib_post_srq_recv(काष्ठा ib_srq *ibsrq, स्थिर काष्ठा ib_recv_wr *wr,
			  स्थिर काष्ठा ib_recv_wr **bad_wr)
अणु
	काष्ठा mlx5_ib_srq *srq = to_msrq(ibsrq);
	काष्ठा mlx5_wqe_srq_next_seg *next;
	काष्ठा mlx5_wqe_data_seg *scat;
	काष्ठा mlx5_ib_dev *dev = to_mdev(ibsrq->device);
	काष्ठा mlx5_core_dev *mdev = dev->mdev;
	अचिन्हित दीर्घ flags;
	पूर्णांक err = 0;
	पूर्णांक nreq;
	पूर्णांक i;

	spin_lock_irqsave(&srq->lock, flags);

	अगर (mdev->state == MLX5_DEVICE_STATE_INTERNAL_ERROR) अणु
		err = -EIO;
		*bad_wr = wr;
		जाओ out;
	पूर्ण

	क्रम (nreq = 0; wr; nreq++, wr = wr->next) अणु
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
		scat      = (काष्ठा mlx5_wqe_data_seg *)(next + 1);

		क्रम (i = 0; i < wr->num_sge; i++) अणु
			scat[i].byte_count = cpu_to_be32(wr->sg_list[i].length);
			scat[i].lkey       = cpu_to_be32(wr->sg_list[i].lkey);
			scat[i].addr       = cpu_to_be64(wr->sg_list[i].addr);
		पूर्ण

		अगर (i < srq->msrq.max_avail_gather) अणु
			scat[i].byte_count = 0;
			scat[i].lkey       = cpu_to_be32(MLX5_INVALID_LKEY);
			scat[i].addr       = 0;
		पूर्ण
	पूर्ण

	अगर (likely(nreq)) अणु
		srq->wqe_ctr += nreq;

		/* Make sure that descriptors are written beक्रमe
		 * करोorbell record.
		 */
		wmb();

		*srq->db.db = cpu_to_be32(srq->wqe_ctr);
	पूर्ण
out:
	spin_unlock_irqrestore(&srq->lock, flags);

	वापस err;
पूर्ण
