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

#समावेश <linux/mlx4/cq.h>
#समावेश <linux/mlx4/qp.h>
#समावेश <linux/mlx4/srq.h>
#समावेश <linux/slab.h>

#समावेश "mlx4_ib.h"
#समावेश <rdma/mlx4-abi.h>
#समावेश <rdma/uverbs_ioctl.h>

अटल व्योम mlx4_ib_cq_comp(काष्ठा mlx4_cq *cq)
अणु
	काष्ठा ib_cq *ibcq = &to_mibcq(cq)->ibcq;
	ibcq->comp_handler(ibcq, ibcq->cq_context);
पूर्ण

अटल व्योम mlx4_ib_cq_event(काष्ठा mlx4_cq *cq, क्रमागत mlx4_event type)
अणु
	काष्ठा ib_event event;
	काष्ठा ib_cq *ibcq;

	अगर (type != MLX4_EVENT_TYPE_CQ_ERROR) अणु
		pr_warn("Unexpected event type %d "
		       "on CQ %06x\n", type, cq->cqn);
		वापस;
	पूर्ण

	ibcq = &to_mibcq(cq)->ibcq;
	अगर (ibcq->event_handler) अणु
		event.device     = ibcq->device;
		event.event      = IB_EVENT_CQ_ERR;
		event.element.cq = ibcq;
		ibcq->event_handler(&event, ibcq->cq_context);
	पूर्ण
पूर्ण

अटल व्योम *get_cqe_from_buf(काष्ठा mlx4_ib_cq_buf *buf, पूर्णांक n)
अणु
	वापस mlx4_buf_offset(&buf->buf, n * buf->entry_size);
पूर्ण

अटल व्योम *get_cqe(काष्ठा mlx4_ib_cq *cq, पूर्णांक n)
अणु
	वापस get_cqe_from_buf(&cq->buf, n);
पूर्ण

अटल व्योम *get_sw_cqe(काष्ठा mlx4_ib_cq *cq, पूर्णांक n)
अणु
	काष्ठा mlx4_cqe *cqe = get_cqe(cq, n & cq->ibcq.cqe);
	काष्ठा mlx4_cqe *tcqe = ((cq->buf.entry_size == 64) ? (cqe + 1) : cqe);

	वापस (!!(tcqe->owner_sr_opcode & MLX4_CQE_OWNER_MASK) ^
		!!(n & (cq->ibcq.cqe + 1))) ? शून्य : cqe;
पूर्ण

अटल काष्ठा mlx4_cqe *next_cqe_sw(काष्ठा mlx4_ib_cq *cq)
अणु
	वापस get_sw_cqe(cq, cq->mcq.cons_index);
पूर्ण

पूर्णांक mlx4_ib_modअगरy_cq(काष्ठा ib_cq *cq, u16 cq_count, u16 cq_period)
अणु
	काष्ठा mlx4_ib_cq *mcq = to_mcq(cq);
	काष्ठा mlx4_ib_dev *dev = to_mdev(cq->device);

	वापस mlx4_cq_modअगरy(dev->dev, &mcq->mcq, cq_count, cq_period);
पूर्ण

अटल पूर्णांक mlx4_ib_alloc_cq_buf(काष्ठा mlx4_ib_dev *dev, काष्ठा mlx4_ib_cq_buf *buf, पूर्णांक nent)
अणु
	पूर्णांक err;

	err = mlx4_buf_alloc(dev->dev, nent * dev->dev->caps.cqe_size,
			     PAGE_SIZE * 2, &buf->buf);

	अगर (err)
		जाओ out;

	buf->entry_size = dev->dev->caps.cqe_size;
	err = mlx4_mtt_init(dev->dev, buf->buf.npages, buf->buf.page_shअगरt,
				    &buf->mtt);
	अगर (err)
		जाओ err_buf;

	err = mlx4_buf_ग_लिखो_mtt(dev->dev, &buf->mtt, &buf->buf);
	अगर (err)
		जाओ err_mtt;

	वापस 0;

err_mtt:
	mlx4_mtt_cleanup(dev->dev, &buf->mtt);

err_buf:
	mlx4_buf_मुक्त(dev->dev, nent * buf->entry_size, &buf->buf);

out:
	वापस err;
पूर्ण

अटल व्योम mlx4_ib_मुक्त_cq_buf(काष्ठा mlx4_ib_dev *dev, काष्ठा mlx4_ib_cq_buf *buf, पूर्णांक cqe)
अणु
	mlx4_buf_मुक्त(dev->dev, (cqe + 1) * buf->entry_size, &buf->buf);
पूर्ण

अटल पूर्णांक mlx4_ib_get_cq_umem(काष्ठा mlx4_ib_dev *dev, काष्ठा ib_udata *udata,
			       काष्ठा mlx4_ib_cq_buf *buf,
			       काष्ठा ib_umem **umem, u64 buf_addr, पूर्णांक cqe)
अणु
	पूर्णांक err;
	पूर्णांक cqe_size = dev->dev->caps.cqe_size;
	पूर्णांक shअगरt;
	पूर्णांक n;

	*umem = ib_umem_get(&dev->ib_dev, buf_addr, cqe * cqe_size,
			    IB_ACCESS_LOCAL_WRITE);
	अगर (IS_ERR(*umem))
		वापस PTR_ERR(*umem);

	shअगरt = mlx4_ib_umem_calc_optimal_mtt_size(*umem, 0, &n);
	err = mlx4_mtt_init(dev->dev, n, shअगरt, &buf->mtt);

	अगर (err)
		जाओ err_buf;

	err = mlx4_ib_umem_ग_लिखो_mtt(dev, &buf->mtt, *umem);
	अगर (err)
		जाओ err_mtt;

	वापस 0;

err_mtt:
	mlx4_mtt_cleanup(dev->dev, &buf->mtt);

err_buf:
	ib_umem_release(*umem);

	वापस err;
पूर्ण

#घोषणा CQ_CREATE_FLAGS_SUPPORTED IB_UVERBS_CQ_FLAGS_TIMESTAMP_COMPLETION
पूर्णांक mlx4_ib_create_cq(काष्ठा ib_cq *ibcq, स्थिर काष्ठा ib_cq_init_attr *attr,
		      काष्ठा ib_udata *udata)
अणु
	काष्ठा ib_device *ibdev = ibcq->device;
	पूर्णांक entries = attr->cqe;
	पूर्णांक vector = attr->comp_vector;
	काष्ठा mlx4_ib_dev *dev = to_mdev(ibdev);
	काष्ठा mlx4_ib_cq *cq = to_mcq(ibcq);
	काष्ठा mlx4_uar *uar;
	व्योम *buf_addr;
	पूर्णांक err;
	काष्ठा mlx4_ib_ucontext *context = rdma_udata_to_drv_context(
		udata, काष्ठा mlx4_ib_ucontext, ibucontext);

	अगर (entries < 1 || entries > dev->dev->caps.max_cqes)
		वापस -EINVAL;

	अगर (attr->flags & ~CQ_CREATE_FLAGS_SUPPORTED)
		वापस -EINVAL;

	entries      = roundup_घात_of_two(entries + 1);
	cq->ibcq.cqe = entries - 1;
	mutex_init(&cq->resize_mutex);
	spin_lock_init(&cq->lock);
	cq->resize_buf = शून्य;
	cq->resize_umem = शून्य;
	cq->create_flags = attr->flags;
	INIT_LIST_HEAD(&cq->send_qp_list);
	INIT_LIST_HEAD(&cq->recv_qp_list);

	अगर (udata) अणु
		काष्ठा mlx4_ib_create_cq ucmd;

		अगर (ib_copy_from_udata(&ucmd, udata, माप ucmd)) अणु
			err = -EFAULT;
			जाओ err_cq;
		पूर्ण

		buf_addr = (व्योम *)(अचिन्हित दीर्घ)ucmd.buf_addr;
		err = mlx4_ib_get_cq_umem(dev, udata, &cq->buf, &cq->umem,
					  ucmd.buf_addr, entries);
		अगर (err)
			जाओ err_cq;

		err = mlx4_ib_db_map_user(udata, ucmd.db_addr, &cq->db);
		अगर (err)
			जाओ err_mtt;

		uar = &context->uar;
		cq->mcq.usage = MLX4_RES_USAGE_USER_VERBS;
	पूर्ण अन्यथा अणु
		err = mlx4_db_alloc(dev->dev, &cq->db, 1);
		अगर (err)
			जाओ err_cq;

		cq->mcq.set_ci_db  = cq->db.db;
		cq->mcq.arm_db     = cq->db.db + 1;
		*cq->mcq.set_ci_db = 0;
		*cq->mcq.arm_db    = 0;

		err = mlx4_ib_alloc_cq_buf(dev, &cq->buf, entries);
		अगर (err)
			जाओ err_db;

		buf_addr = &cq->buf.buf;

		uar = &dev->priv_uar;
		cq->mcq.usage = MLX4_RES_USAGE_DRIVER;
	पूर्ण

	अगर (dev->eq_table)
		vector = dev->eq_table[vector % ibdev->num_comp_vectors];

	err = mlx4_cq_alloc(dev->dev, entries, &cq->buf.mtt, uar, cq->db.dma,
			    &cq->mcq, vector, 0,
			    !!(cq->create_flags &
			       IB_UVERBS_CQ_FLAGS_TIMESTAMP_COMPLETION),
			    buf_addr, !!udata);
	अगर (err)
		जाओ err_dbmap;

	अगर (udata)
		cq->mcq.tasklet_ctx.comp = mlx4_ib_cq_comp;
	अन्यथा
		cq->mcq.comp = mlx4_ib_cq_comp;
	cq->mcq.event = mlx4_ib_cq_event;

	अगर (udata)
		अगर (ib_copy_to_udata(udata, &cq->mcq.cqn, माप (__u32))) अणु
			err = -EFAULT;
			जाओ err_cq_मुक्त;
		पूर्ण

	वापस 0;

err_cq_मुक्त:
	mlx4_cq_मुक्त(dev->dev, &cq->mcq);

err_dbmap:
	अगर (udata)
		mlx4_ib_db_unmap_user(context, &cq->db);

err_mtt:
	mlx4_mtt_cleanup(dev->dev, &cq->buf.mtt);

	ib_umem_release(cq->umem);
	अगर (!udata)
		mlx4_ib_मुक्त_cq_buf(dev, &cq->buf, cq->ibcq.cqe);

err_db:
	अगर (!udata)
		mlx4_db_मुक्त(dev->dev, &cq->db);
err_cq:
	वापस err;
पूर्ण

अटल पूर्णांक mlx4_alloc_resize_buf(काष्ठा mlx4_ib_dev *dev, काष्ठा mlx4_ib_cq *cq,
				  पूर्णांक entries)
अणु
	पूर्णांक err;

	अगर (cq->resize_buf)
		वापस -EBUSY;

	cq->resize_buf = kदो_स्मृति(माप *cq->resize_buf, GFP_KERNEL);
	अगर (!cq->resize_buf)
		वापस -ENOMEM;

	err = mlx4_ib_alloc_cq_buf(dev, &cq->resize_buf->buf, entries);
	अगर (err) अणु
		kमुक्त(cq->resize_buf);
		cq->resize_buf = शून्य;
		वापस err;
	पूर्ण

	cq->resize_buf->cqe = entries - 1;

	वापस 0;
पूर्ण

अटल पूर्णांक mlx4_alloc_resize_umem(काष्ठा mlx4_ib_dev *dev, काष्ठा mlx4_ib_cq *cq,
				   पूर्णांक entries, काष्ठा ib_udata *udata)
अणु
	काष्ठा mlx4_ib_resize_cq ucmd;
	पूर्णांक err;

	अगर (cq->resize_umem)
		वापस -EBUSY;

	अगर (ib_copy_from_udata(&ucmd, udata, माप ucmd))
		वापस -EFAULT;

	cq->resize_buf = kदो_स्मृति(माप *cq->resize_buf, GFP_KERNEL);
	अगर (!cq->resize_buf)
		वापस -ENOMEM;

	err = mlx4_ib_get_cq_umem(dev, udata, &cq->resize_buf->buf,
				  &cq->resize_umem, ucmd.buf_addr, entries);
	अगर (err) अणु
		kमुक्त(cq->resize_buf);
		cq->resize_buf = शून्य;
		वापस err;
	पूर्ण

	cq->resize_buf->cqe = entries - 1;

	वापस 0;
पूर्ण

अटल पूर्णांक mlx4_ib_get_outstanding_cqes(काष्ठा mlx4_ib_cq *cq)
अणु
	u32 i;

	i = cq->mcq.cons_index;
	जबतक (get_sw_cqe(cq, i))
		++i;

	वापस i - cq->mcq.cons_index;
पूर्ण

अटल व्योम mlx4_ib_cq_resize_copy_cqes(काष्ठा mlx4_ib_cq *cq)
अणु
	काष्ठा mlx4_cqe *cqe, *new_cqe;
	पूर्णांक i;
	पूर्णांक cqe_size = cq->buf.entry_size;
	पूर्णांक cqe_inc = cqe_size == 64 ? 1 : 0;

	i = cq->mcq.cons_index;
	cqe = get_cqe(cq, i & cq->ibcq.cqe);
	cqe += cqe_inc;

	जबतक ((cqe->owner_sr_opcode & MLX4_CQE_OPCODE_MASK) != MLX4_CQE_OPCODE_RESIZE) अणु
		new_cqe = get_cqe_from_buf(&cq->resize_buf->buf,
					   (i + 1) & cq->resize_buf->cqe);
		स_नकल(new_cqe, get_cqe(cq, i & cq->ibcq.cqe), cqe_size);
		new_cqe += cqe_inc;

		new_cqe->owner_sr_opcode = (cqe->owner_sr_opcode & ~MLX4_CQE_OWNER_MASK) |
			(((i + 1) & (cq->resize_buf->cqe + 1)) ? MLX4_CQE_OWNER_MASK : 0);
		cqe = get_cqe(cq, ++i & cq->ibcq.cqe);
		cqe += cqe_inc;
	पूर्ण
	++cq->mcq.cons_index;
पूर्ण

पूर्णांक mlx4_ib_resize_cq(काष्ठा ib_cq *ibcq, पूर्णांक entries, काष्ठा ib_udata *udata)
अणु
	काष्ठा mlx4_ib_dev *dev = to_mdev(ibcq->device);
	काष्ठा mlx4_ib_cq *cq = to_mcq(ibcq);
	काष्ठा mlx4_mtt mtt;
	पूर्णांक outst_cqe;
	पूर्णांक err;

	mutex_lock(&cq->resize_mutex);
	अगर (entries < 1 || entries > dev->dev->caps.max_cqes) अणु
		err = -EINVAL;
		जाओ out;
	पूर्ण

	entries = roundup_घात_of_two(entries + 1);
	अगर (entries == ibcq->cqe + 1) अणु
		err = 0;
		जाओ out;
	पूर्ण

	अगर (entries > dev->dev->caps.max_cqes + 1) अणु
		err = -EINVAL;
		जाओ out;
	पूर्ण

	अगर (ibcq->uobject) अणु
		err = mlx4_alloc_resize_umem(dev, cq, entries, udata);
		अगर (err)
			जाओ out;
	पूर्ण अन्यथा अणु
		/* Can't be smaller than the number of outstanding CQEs */
		outst_cqe = mlx4_ib_get_outstanding_cqes(cq);
		अगर (entries < outst_cqe + 1) अणु
			err = -EINVAL;
			जाओ out;
		पूर्ण

		err = mlx4_alloc_resize_buf(dev, cq, entries);
		अगर (err)
			जाओ out;
	पूर्ण

	mtt = cq->buf.mtt;

	err = mlx4_cq_resize(dev->dev, &cq->mcq, entries, &cq->resize_buf->buf.mtt);
	अगर (err)
		जाओ err_buf;

	mlx4_mtt_cleanup(dev->dev, &mtt);
	अगर (ibcq->uobject) अणु
		cq->buf      = cq->resize_buf->buf;
		cq->ibcq.cqe = cq->resize_buf->cqe;
		ib_umem_release(cq->umem);
		cq->umem     = cq->resize_umem;

		kमुक्त(cq->resize_buf);
		cq->resize_buf = शून्य;
		cq->resize_umem = शून्य;
	पूर्ण अन्यथा अणु
		काष्ठा mlx4_ib_cq_buf पंचांगp_buf;
		पूर्णांक पंचांगp_cqe = 0;

		spin_lock_irq(&cq->lock);
		अगर (cq->resize_buf) अणु
			mlx4_ib_cq_resize_copy_cqes(cq);
			पंचांगp_buf = cq->buf;
			पंचांगp_cqe = cq->ibcq.cqe;
			cq->buf      = cq->resize_buf->buf;
			cq->ibcq.cqe = cq->resize_buf->cqe;

			kमुक्त(cq->resize_buf);
			cq->resize_buf = शून्य;
		पूर्ण
		spin_unlock_irq(&cq->lock);

		अगर (पंचांगp_cqe)
			mlx4_ib_मुक्त_cq_buf(dev, &पंचांगp_buf, पंचांगp_cqe);
	पूर्ण

	जाओ out;

err_buf:
	mlx4_mtt_cleanup(dev->dev, &cq->resize_buf->buf.mtt);
	अगर (!ibcq->uobject)
		mlx4_ib_मुक्त_cq_buf(dev, &cq->resize_buf->buf,
				    cq->resize_buf->cqe);

	kमुक्त(cq->resize_buf);
	cq->resize_buf = शून्य;

	ib_umem_release(cq->resize_umem);
	cq->resize_umem = शून्य;
out:
	mutex_unlock(&cq->resize_mutex);

	वापस err;
पूर्ण

पूर्णांक mlx4_ib_destroy_cq(काष्ठा ib_cq *cq, काष्ठा ib_udata *udata)
अणु
	काष्ठा mlx4_ib_dev *dev = to_mdev(cq->device);
	काष्ठा mlx4_ib_cq *mcq = to_mcq(cq);

	mlx4_cq_मुक्त(dev->dev, &mcq->mcq);
	mlx4_mtt_cleanup(dev->dev, &mcq->buf.mtt);

	अगर (udata) अणु
		mlx4_ib_db_unmap_user(
			rdma_udata_to_drv_context(
				udata,
				काष्ठा mlx4_ib_ucontext,
				ibucontext),
			&mcq->db);
	पूर्ण अन्यथा अणु
		mlx4_ib_मुक्त_cq_buf(dev, &mcq->buf, cq->cqe);
		mlx4_db_मुक्त(dev->dev, &mcq->db);
	पूर्ण
	ib_umem_release(mcq->umem);
	वापस 0;
पूर्ण

अटल व्योम dump_cqe(व्योम *cqe)
अणु
	__be32 *buf = cqe;

	pr_debug("CQE contents %08x %08x %08x %08x %08x %08x %08x %08x\n",
	       be32_to_cpu(buf[0]), be32_to_cpu(buf[1]), be32_to_cpu(buf[2]),
	       be32_to_cpu(buf[3]), be32_to_cpu(buf[4]), be32_to_cpu(buf[5]),
	       be32_to_cpu(buf[6]), be32_to_cpu(buf[7]));
पूर्ण

अटल व्योम mlx4_ib_handle_error_cqe(काष्ठा mlx4_err_cqe *cqe,
				     काष्ठा ib_wc *wc)
अणु
	अगर (cqe->syndrome == MLX4_CQE_SYNDROME_LOCAL_QP_OP_ERR) अणु
		pr_debug("local QP operation err "
		       "(QPN %06x, WQE index %x, vendor syndrome %02x, "
		       "opcode = %02x)\n",
		       be32_to_cpu(cqe->my_qpn), be16_to_cpu(cqe->wqe_index),
		       cqe->venकरोr_err_syndrome,
		       cqe->owner_sr_opcode & ~MLX4_CQE_OWNER_MASK);
		dump_cqe(cqe);
	पूर्ण

	चयन (cqe->syndrome) अणु
	हाल MLX4_CQE_SYNDROME_LOCAL_LENGTH_ERR:
		wc->status = IB_WC_LOC_LEN_ERR;
		अवरोध;
	हाल MLX4_CQE_SYNDROME_LOCAL_QP_OP_ERR:
		wc->status = IB_WC_LOC_QP_OP_ERR;
		अवरोध;
	हाल MLX4_CQE_SYNDROME_LOCAL_PROT_ERR:
		wc->status = IB_WC_LOC_PROT_ERR;
		अवरोध;
	हाल MLX4_CQE_SYNDROME_WR_FLUSH_ERR:
		wc->status = IB_WC_WR_FLUSH_ERR;
		अवरोध;
	हाल MLX4_CQE_SYNDROME_MW_BIND_ERR:
		wc->status = IB_WC_MW_BIND_ERR;
		अवरोध;
	हाल MLX4_CQE_SYNDROME_BAD_RESP_ERR:
		wc->status = IB_WC_BAD_RESP_ERR;
		अवरोध;
	हाल MLX4_CQE_SYNDROME_LOCAL_ACCESS_ERR:
		wc->status = IB_WC_LOC_ACCESS_ERR;
		अवरोध;
	हाल MLX4_CQE_SYNDROME_REMOTE_INVAL_REQ_ERR:
		wc->status = IB_WC_REM_INV_REQ_ERR;
		अवरोध;
	हाल MLX4_CQE_SYNDROME_REMOTE_ACCESS_ERR:
		wc->status = IB_WC_REM_ACCESS_ERR;
		अवरोध;
	हाल MLX4_CQE_SYNDROME_REMOTE_OP_ERR:
		wc->status = IB_WC_REM_OP_ERR;
		अवरोध;
	हाल MLX4_CQE_SYNDROME_TRANSPORT_RETRY_EXC_ERR:
		wc->status = IB_WC_RETRY_EXC_ERR;
		अवरोध;
	हाल MLX4_CQE_SYNDROME_RNR_RETRY_EXC_ERR:
		wc->status = IB_WC_RNR_RETRY_EXC_ERR;
		अवरोध;
	हाल MLX4_CQE_SYNDROME_REMOTE_ABORTED_ERR:
		wc->status = IB_WC_REM_ABORT_ERR;
		अवरोध;
	शेष:
		wc->status = IB_WC_GENERAL_ERR;
		अवरोध;
	पूर्ण

	wc->venकरोr_err = cqe->venकरोr_err_syndrome;
पूर्ण

अटल पूर्णांक mlx4_ib_ipoib_csum_ok(__be16 status, u8 badfcs_enc, __be16 checksum)
अणु
	वापस ((badfcs_enc & MLX4_CQE_STATUS_L4_CSUM) ||
		((status & cpu_to_be16(MLX4_CQE_STATUS_IPOK)) &&
		 (status & cpu_to_be16(MLX4_CQE_STATUS_TCP |
				       MLX4_CQE_STATUS_UDP)) &&
		 (checksum == cpu_to_be16(0xffff))));
पूर्ण

अटल व्योम use_tunnel_data(काष्ठा mlx4_ib_qp *qp, काष्ठा mlx4_ib_cq *cq, काष्ठा ib_wc *wc,
			    अचिन्हित tail, काष्ठा mlx4_cqe *cqe, पूर्णांक is_eth)
अणु
	काष्ठा mlx4_ib_proxy_sqp_hdr *hdr;

	ib_dma_sync_single_क्रम_cpu(qp->ibqp.device,
				   qp->sqp_proxy_rcv[tail].map,
				   माप (काष्ठा mlx4_ib_proxy_sqp_hdr),
				   DMA_FROM_DEVICE);
	hdr = (काष्ठा mlx4_ib_proxy_sqp_hdr *) (qp->sqp_proxy_rcv[tail].addr);
	wc->pkey_index	= be16_to_cpu(hdr->tun.pkey_index);
	wc->src_qp	= be32_to_cpu(hdr->tun.flags_src_qp) & 0xFFFFFF;
	wc->wc_flags   |= (hdr->tun.g_ml_path & 0x80) ? (IB_WC_GRH) : 0;
	wc->dlid_path_bits = 0;

	अगर (is_eth) अणु
		wc->slid = 0;
		wc->vlan_id = be16_to_cpu(hdr->tun.sl_vid);
		स_नकल(&(wc->smac[0]), (अक्षर *)&hdr->tun.mac_31_0, 4);
		स_नकल(&(wc->smac[4]), (अक्षर *)&hdr->tun.slid_mac_47_32, 2);
		wc->wc_flags |= (IB_WC_WITH_VLAN | IB_WC_WITH_SMAC);
	पूर्ण अन्यथा अणु
		wc->slid        = be16_to_cpu(hdr->tun.slid_mac_47_32);
		wc->sl          = (u8) (be16_to_cpu(hdr->tun.sl_vid) >> 12);
	पूर्ण
पूर्ण

अटल व्योम mlx4_ib_qp_sw_comp(काष्ठा mlx4_ib_qp *qp, पूर्णांक num_entries,
			       काष्ठा ib_wc *wc, पूर्णांक *npolled, पूर्णांक is_send)
अणु
	काष्ठा mlx4_ib_wq *wq;
	अचिन्हित cur;
	पूर्णांक i;

	wq = is_send ? &qp->sq : &qp->rq;
	cur = wq->head - wq->tail;

	अगर (cur == 0)
		वापस;

	क्रम (i = 0;  i < cur && *npolled < num_entries; i++) अणु
		wc->wr_id = wq->wrid[wq->tail & (wq->wqe_cnt - 1)];
		wc->status = IB_WC_WR_FLUSH_ERR;
		wc->venकरोr_err = MLX4_CQE_SYNDROME_WR_FLUSH_ERR;
		wq->tail++;
		(*npolled)++;
		wc->qp = &qp->ibqp;
		wc++;
	पूर्ण
पूर्ण

अटल व्योम mlx4_ib_poll_sw_comp(काष्ठा mlx4_ib_cq *cq, पूर्णांक num_entries,
				 काष्ठा ib_wc *wc, पूर्णांक *npolled)
अणु
	काष्ठा mlx4_ib_qp *qp;

	*npolled = 0;
	/* Find uncompleted WQEs beदीर्घing to that cq and वापस
	 * simulated FLUSH_ERR completions
	 */
	list_क्रम_each_entry(qp, &cq->send_qp_list, cq_send_list) अणु
		mlx4_ib_qp_sw_comp(qp, num_entries, wc + *npolled, npolled, 1);
		अगर (*npolled >= num_entries)
			जाओ out;
	पूर्ण

	list_क्रम_each_entry(qp, &cq->recv_qp_list, cq_recv_list) अणु
		mlx4_ib_qp_sw_comp(qp, num_entries, wc + *npolled, npolled, 0);
		अगर (*npolled >= num_entries)
			जाओ out;
	पूर्ण

out:
	वापस;
पूर्ण

अटल पूर्णांक mlx4_ib_poll_one(काष्ठा mlx4_ib_cq *cq,
			    काष्ठा mlx4_ib_qp **cur_qp,
			    काष्ठा ib_wc *wc)
अणु
	काष्ठा mlx4_cqe *cqe;
	काष्ठा mlx4_qp *mqp;
	काष्ठा mlx4_ib_wq *wq;
	काष्ठा mlx4_ib_srq *srq;
	काष्ठा mlx4_srq *msrq = शून्य;
	पूर्णांक is_send;
	पूर्णांक is_error;
	पूर्णांक is_eth;
	u32 g_mlpath_rqpn;
	u16 wqe_ctr;
	अचिन्हित tail = 0;

repoll:
	cqe = next_cqe_sw(cq);
	अगर (!cqe)
		वापस -EAGAIN;

	अगर (cq->buf.entry_size == 64)
		cqe++;

	++cq->mcq.cons_index;

	/*
	 * Make sure we पढ़ो CQ entry contents after we've checked the
	 * ownership bit.
	 */
	rmb();

	is_send  = cqe->owner_sr_opcode & MLX4_CQE_IS_SEND_MASK;
	is_error = (cqe->owner_sr_opcode & MLX4_CQE_OPCODE_MASK) ==
		MLX4_CQE_OPCODE_ERROR;

	/* Resize CQ in progress */
	अगर (unlikely((cqe->owner_sr_opcode & MLX4_CQE_OPCODE_MASK) == MLX4_CQE_OPCODE_RESIZE)) अणु
		अगर (cq->resize_buf) अणु
			काष्ठा mlx4_ib_dev *dev = to_mdev(cq->ibcq.device);

			mlx4_ib_मुक्त_cq_buf(dev, &cq->buf, cq->ibcq.cqe);
			cq->buf      = cq->resize_buf->buf;
			cq->ibcq.cqe = cq->resize_buf->cqe;

			kमुक्त(cq->resize_buf);
			cq->resize_buf = शून्य;
		पूर्ण

		जाओ repoll;
	पूर्ण

	अगर (!*cur_qp ||
	    (be32_to_cpu(cqe->vlan_my_qpn) & MLX4_CQE_QPN_MASK) != (*cur_qp)->mqp.qpn) अणु
		/*
		 * We करो not have to take the QP table lock here,
		 * because CQs will be locked जबतक QPs are हटाओd
		 * from the table.
		 */
		mqp = __mlx4_qp_lookup(to_mdev(cq->ibcq.device)->dev,
				       be32_to_cpu(cqe->vlan_my_qpn));
		*cur_qp = to_mibqp(mqp);
	पूर्ण

	wc->qp = &(*cur_qp)->ibqp;

	अगर (wc->qp->qp_type == IB_QPT_XRC_TGT) अणु
		u32 srq_num;
		g_mlpath_rqpn = be32_to_cpu(cqe->g_mlpath_rqpn);
		srq_num       = g_mlpath_rqpn & 0xffffff;
		/* SRQ is also in the radix tree */
		msrq = mlx4_srq_lookup(to_mdev(cq->ibcq.device)->dev,
				       srq_num);
	पूर्ण

	अगर (is_send) अणु
		wq = &(*cur_qp)->sq;
		अगर (!(*cur_qp)->sq_संकेत_bits) अणु
			wqe_ctr = be16_to_cpu(cqe->wqe_index);
			wq->tail += (u16) (wqe_ctr - (u16) wq->tail);
		पूर्ण
		wc->wr_id = wq->wrid[wq->tail & (wq->wqe_cnt - 1)];
		++wq->tail;
	पूर्ण अन्यथा अगर ((*cur_qp)->ibqp.srq) अणु
		srq = to_msrq((*cur_qp)->ibqp.srq);
		wqe_ctr = be16_to_cpu(cqe->wqe_index);
		wc->wr_id = srq->wrid[wqe_ctr];
		mlx4_ib_मुक्त_srq_wqe(srq, wqe_ctr);
	पूर्ण अन्यथा अगर (msrq) अणु
		srq = to_mibsrq(msrq);
		wqe_ctr = be16_to_cpu(cqe->wqe_index);
		wc->wr_id = srq->wrid[wqe_ctr];
		mlx4_ib_मुक्त_srq_wqe(srq, wqe_ctr);
	पूर्ण अन्यथा अणु
		wq	  = &(*cur_qp)->rq;
		tail	  = wq->tail & (wq->wqe_cnt - 1);
		wc->wr_id = wq->wrid[tail];
		++wq->tail;
	पूर्ण

	अगर (unlikely(is_error)) अणु
		mlx4_ib_handle_error_cqe((काष्ठा mlx4_err_cqe *) cqe, wc);
		वापस 0;
	पूर्ण

	wc->status = IB_WC_SUCCESS;

	अगर (is_send) अणु
		wc->wc_flags = 0;
		चयन (cqe->owner_sr_opcode & MLX4_CQE_OPCODE_MASK) अणु
		हाल MLX4_OPCODE_RDMA_WRITE_IMM:
			wc->wc_flags |= IB_WC_WITH_IMM;
			fallthrough;
		हाल MLX4_OPCODE_RDMA_WRITE:
			wc->opcode    = IB_WC_RDMA_WRITE;
			अवरोध;
		हाल MLX4_OPCODE_SEND_IMM:
			wc->wc_flags |= IB_WC_WITH_IMM;
			fallthrough;
		हाल MLX4_OPCODE_SEND:
		हाल MLX4_OPCODE_SEND_INVAL:
			wc->opcode    = IB_WC_SEND;
			अवरोध;
		हाल MLX4_OPCODE_RDMA_READ:
			wc->opcode    = IB_WC_RDMA_READ;
			wc->byte_len  = be32_to_cpu(cqe->byte_cnt);
			अवरोध;
		हाल MLX4_OPCODE_ATOMIC_CS:
			wc->opcode    = IB_WC_COMP_SWAP;
			wc->byte_len  = 8;
			अवरोध;
		हाल MLX4_OPCODE_ATOMIC_FA:
			wc->opcode    = IB_WC_FETCH_ADD;
			wc->byte_len  = 8;
			अवरोध;
		हाल MLX4_OPCODE_MASKED_ATOMIC_CS:
			wc->opcode    = IB_WC_MASKED_COMP_SWAP;
			wc->byte_len  = 8;
			अवरोध;
		हाल MLX4_OPCODE_MASKED_ATOMIC_FA:
			wc->opcode    = IB_WC_MASKED_FETCH_ADD;
			wc->byte_len  = 8;
			अवरोध;
		हाल MLX4_OPCODE_LSO:
			wc->opcode    = IB_WC_LSO;
			अवरोध;
		हाल MLX4_OPCODE_FMR:
			wc->opcode    = IB_WC_REG_MR;
			अवरोध;
		हाल MLX4_OPCODE_LOCAL_INVAL:
			wc->opcode    = IB_WC_LOCAL_INV;
			अवरोध;
		पूर्ण
	पूर्ण अन्यथा अणु
		wc->byte_len = be32_to_cpu(cqe->byte_cnt);

		चयन (cqe->owner_sr_opcode & MLX4_CQE_OPCODE_MASK) अणु
		हाल MLX4_RECV_OPCODE_RDMA_WRITE_IMM:
			wc->opcode	= IB_WC_RECV_RDMA_WITH_IMM;
			wc->wc_flags	= IB_WC_WITH_IMM;
			wc->ex.imm_data = cqe->immed_rss_invalid;
			अवरोध;
		हाल MLX4_RECV_OPCODE_SEND_INVAL:
			wc->opcode	= IB_WC_RECV;
			wc->wc_flags	= IB_WC_WITH_INVALIDATE;
			wc->ex.invalidate_rkey = be32_to_cpu(cqe->immed_rss_invalid);
			अवरोध;
		हाल MLX4_RECV_OPCODE_SEND:
			wc->opcode   = IB_WC_RECV;
			wc->wc_flags = 0;
			अवरोध;
		हाल MLX4_RECV_OPCODE_SEND_IMM:
			wc->opcode	= IB_WC_RECV;
			wc->wc_flags	= IB_WC_WITH_IMM;
			wc->ex.imm_data = cqe->immed_rss_invalid;
			अवरोध;
		पूर्ण

		is_eth = (rdma_port_get_link_layer(wc->qp->device,
						  (*cur_qp)->port) ==
			  IB_LINK_LAYER_ETHERNET);
		अगर (mlx4_is_mfunc(to_mdev(cq->ibcq.device)->dev)) अणु
			अगर ((*cur_qp)->mlx4_ib_qp_type &
			    (MLX4_IB_QPT_PROXY_SMI_OWNER |
			     MLX4_IB_QPT_PROXY_SMI | MLX4_IB_QPT_PROXY_GSI)) अणु
				use_tunnel_data(*cur_qp, cq, wc, tail, cqe,
						is_eth);
				वापस 0;
			पूर्ण
		पूर्ण

		g_mlpath_rqpn	   = be32_to_cpu(cqe->g_mlpath_rqpn);
		wc->src_qp	   = g_mlpath_rqpn & 0xffffff;
		wc->dlid_path_bits = (g_mlpath_rqpn >> 24) & 0x7f;
		wc->wc_flags	  |= g_mlpath_rqpn & 0x80000000 ? IB_WC_GRH : 0;
		wc->pkey_index     = be32_to_cpu(cqe->immed_rss_invalid) & 0x7f;
		wc->wc_flags	  |= mlx4_ib_ipoib_csum_ok(cqe->status,
					cqe->badfcs_enc,
					cqe->checksum) ? IB_WC_IP_CSUM_OK : 0;
		अगर (is_eth) अणु
			wc->slid = 0;
			wc->sl  = be16_to_cpu(cqe->sl_vid) >> 13;
			अगर (be32_to_cpu(cqe->vlan_my_qpn) &
					MLX4_CQE_CVLAN_PRESENT_MASK) अणु
				wc->vlan_id = be16_to_cpu(cqe->sl_vid) &
					MLX4_CQE_VID_MASK;
			पूर्ण अन्यथा अणु
				wc->vlan_id = 0xffff;
			पूर्ण
			स_नकल(wc->smac, cqe->smac, ETH_ALEN);
			wc->wc_flags |= (IB_WC_WITH_VLAN | IB_WC_WITH_SMAC);
		पूर्ण अन्यथा अणु
			wc->slid = be16_to_cpu(cqe->rlid);
			wc->sl  = be16_to_cpu(cqe->sl_vid) >> 12;
			wc->vlan_id = 0xffff;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

पूर्णांक mlx4_ib_poll_cq(काष्ठा ib_cq *ibcq, पूर्णांक num_entries, काष्ठा ib_wc *wc)
अणु
	काष्ठा mlx4_ib_cq *cq = to_mcq(ibcq);
	काष्ठा mlx4_ib_qp *cur_qp = शून्य;
	अचिन्हित दीर्घ flags;
	पूर्णांक npolled;
	काष्ठा mlx4_ib_dev *mdev = to_mdev(cq->ibcq.device);

	spin_lock_irqsave(&cq->lock, flags);
	अगर (mdev->dev->persist->state & MLX4_DEVICE_STATE_INTERNAL_ERROR) अणु
		mlx4_ib_poll_sw_comp(cq, num_entries, wc, &npolled);
		जाओ out;
	पूर्ण

	क्रम (npolled = 0; npolled < num_entries; ++npolled) अणु
		अगर (mlx4_ib_poll_one(cq, &cur_qp, wc + npolled))
			अवरोध;
	पूर्ण

	mlx4_cq_set_ci(&cq->mcq);

out:
	spin_unlock_irqrestore(&cq->lock, flags);

	वापस npolled;
पूर्ण

पूर्णांक mlx4_ib_arm_cq(काष्ठा ib_cq *ibcq, क्रमागत ib_cq_notअगरy_flags flags)
अणु
	mlx4_cq_arm(&to_mcq(ibcq)->mcq,
		    (flags & IB_CQ_SOLICITED_MASK) == IB_CQ_SOLICITED ?
		    MLX4_CQ_DB_REQ_NOT_SOL : MLX4_CQ_DB_REQ_NOT,
		    to_mdev(ibcq->device)->uar_map,
		    MLX4_GET_DOORBELL_LOCK(&to_mdev(ibcq->device)->uar_lock));

	वापस 0;
पूर्ण

व्योम __mlx4_ib_cq_clean(काष्ठा mlx4_ib_cq *cq, u32 qpn, काष्ठा mlx4_ib_srq *srq)
अणु
	u32 prod_index;
	पूर्णांक nमुक्तd = 0;
	काष्ठा mlx4_cqe *cqe, *dest;
	u8 owner_bit;
	पूर्णांक cqe_inc = cq->buf.entry_size == 64 ? 1 : 0;

	/*
	 * First we need to find the current producer index, so we
	 * know where to start cleaning from.  It करोesn't matter अगर HW
	 * adds new entries after this loop -- the QP we're worried
	 * about is alपढ़ोy in RESET, so the new entries won't come
	 * from our QP and thereक्रमe करोn't need to be checked.
	 */
	क्रम (prod_index = cq->mcq.cons_index; get_sw_cqe(cq, prod_index); ++prod_index)
		अगर (prod_index == cq->mcq.cons_index + cq->ibcq.cqe)
			अवरोध;

	/*
	 * Now sweep backwards through the CQ, removing CQ entries
	 * that match our QP by copying older entries on top of them.
	 */
	जबतक ((पूर्णांक) --prod_index - (पूर्णांक) cq->mcq.cons_index >= 0) अणु
		cqe = get_cqe(cq, prod_index & cq->ibcq.cqe);
		cqe += cqe_inc;

		अगर ((be32_to_cpu(cqe->vlan_my_qpn) & MLX4_CQE_QPN_MASK) == qpn) अणु
			अगर (srq && !(cqe->owner_sr_opcode & MLX4_CQE_IS_SEND_MASK))
				mlx4_ib_मुक्त_srq_wqe(srq, be16_to_cpu(cqe->wqe_index));
			++nमुक्तd;
		पूर्ण अन्यथा अगर (nमुक्तd) अणु
			dest = get_cqe(cq, (prod_index + nमुक्तd) & cq->ibcq.cqe);
			dest += cqe_inc;

			owner_bit = dest->owner_sr_opcode & MLX4_CQE_OWNER_MASK;
			स_नकल(dest, cqe, माप *cqe);
			dest->owner_sr_opcode = owner_bit |
				(dest->owner_sr_opcode & ~MLX4_CQE_OWNER_MASK);
		पूर्ण
	पूर्ण

	अगर (nमुक्तd) अणु
		cq->mcq.cons_index += nमुक्तd;
		/*
		 * Make sure update of buffer contents is करोne beक्रमe
		 * updating consumer index.
		 */
		wmb();
		mlx4_cq_set_ci(&cq->mcq);
	पूर्ण
पूर्ण

व्योम mlx4_ib_cq_clean(काष्ठा mlx4_ib_cq *cq, u32 qpn, काष्ठा mlx4_ib_srq *srq)
अणु
	spin_lock_irq(&cq->lock);
	__mlx4_ib_cq_clean(cq, qpn, srq);
	spin_unlock_irq(&cq->lock);
पूर्ण
