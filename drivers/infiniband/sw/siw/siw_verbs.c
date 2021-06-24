<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0 or BSD-3-Clause

/* Authors: Bernard Metzler <bmt@zurich.ibm.com> */
/* Copyright (c) 2008-2019, IBM Corporation */

#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/types.h>
#समावेश <linux/uaccess.h>
#समावेश <linux/vदो_स्मृति.h>
#समावेश <linux/xarray.h>

#समावेश <rdma/iw_cm.h>
#समावेश <rdma/ib_verbs.h>
#समावेश <rdma/ib_user_verbs.h>
#समावेश <rdma/uverbs_ioctl.h>

#समावेश "siw.h"
#समावेश "siw_verbs.h"
#समावेश "siw_mem.h"

अटल पूर्णांक ib_qp_state_to_siw_qp_state[IB_QPS_ERR + 1] = अणु
	[IB_QPS_RESET] = SIW_QP_STATE_IDLE,
	[IB_QPS_INIT] = SIW_QP_STATE_IDLE,
	[IB_QPS_RTR] = SIW_QP_STATE_RTR,
	[IB_QPS_RTS] = SIW_QP_STATE_RTS,
	[IB_QPS_SQD] = SIW_QP_STATE_CLOSING,
	[IB_QPS_SQE] = SIW_QP_STATE_TERMINATE,
	[IB_QPS_ERR] = SIW_QP_STATE_ERROR
पूर्ण;

अटल अक्षर ib_qp_state_to_string[IB_QPS_ERR + 1][माप("RESET")] = अणु
	[IB_QPS_RESET] = "RESET", [IB_QPS_INIT] = "INIT", [IB_QPS_RTR] = "RTR",
	[IB_QPS_RTS] = "RTS",     [IB_QPS_SQD] = "SQD",   [IB_QPS_SQE] = "SQE",
	[IB_QPS_ERR] = "ERR"
पूर्ण;

व्योम siw_mmap_मुक्त(काष्ठा rdma_user_mmap_entry *rdma_entry)
अणु
	काष्ठा siw_user_mmap_entry *entry = to_siw_mmap_entry(rdma_entry);

	kमुक्त(entry);
पूर्ण

पूर्णांक siw_mmap(काष्ठा ib_ucontext *ctx, काष्ठा vm_area_काष्ठा *vma)
अणु
	काष्ठा siw_ucontext *uctx = to_siw_ctx(ctx);
	माप_प्रकार size = vma->vm_end - vma->vm_start;
	काष्ठा rdma_user_mmap_entry *rdma_entry;
	काष्ठा siw_user_mmap_entry *entry;
	पूर्णांक rv = -EINVAL;

	/*
	 * Must be page aligned
	 */
	अगर (vma->vm_start & (PAGE_SIZE - 1)) अणु
		pr_warn("siw: mmap not page aligned\n");
		वापस -EINVAL;
	पूर्ण
	rdma_entry = rdma_user_mmap_entry_get(&uctx->base_ucontext, vma);
	अगर (!rdma_entry) अणु
		siw_dbg(&uctx->sdev->base_dev, "mmap lookup failed: %lu, %#zx\n",
			vma->vm_pgoff, size);
		वापस -EINVAL;
	पूर्ण
	entry = to_siw_mmap_entry(rdma_entry);

	rv = remap_vदो_स्मृति_range(vma, entry->address, 0);
	अगर (rv) अणु
		pr_warn("remap_vmalloc_range failed: %lu, %zu\n", vma->vm_pgoff,
			size);
		जाओ out;
	पूर्ण
out:
	rdma_user_mmap_entry_put(rdma_entry);

	वापस rv;
पूर्ण

पूर्णांक siw_alloc_ucontext(काष्ठा ib_ucontext *base_ctx, काष्ठा ib_udata *udata)
अणु
	काष्ठा siw_device *sdev = to_siw_dev(base_ctx->device);
	काष्ठा siw_ucontext *ctx = to_siw_ctx(base_ctx);
	काष्ठा siw_uresp_alloc_ctx uresp = अणुपूर्ण;
	पूर्णांक rv;

	अगर (atomic_inc_वापस(&sdev->num_ctx) > SIW_MAX_CONTEXT) अणु
		rv = -ENOMEM;
		जाओ err_out;
	पूर्ण
	ctx->sdev = sdev;

	uresp.dev_id = sdev->venकरोr_part_id;

	अगर (udata->outlen < माप(uresp)) अणु
		rv = -EINVAL;
		जाओ err_out;
	पूर्ण
	rv = ib_copy_to_udata(udata, &uresp, माप(uresp));
	अगर (rv)
		जाओ err_out;

	siw_dbg(base_ctx->device, "success. now %d context(s)\n",
		atomic_पढ़ो(&sdev->num_ctx));

	वापस 0;

err_out:
	atomic_dec(&sdev->num_ctx);
	siw_dbg(base_ctx->device, "failure %d. now %d context(s)\n", rv,
		atomic_पढ़ो(&sdev->num_ctx));

	वापस rv;
पूर्ण

व्योम siw_dealloc_ucontext(काष्ठा ib_ucontext *base_ctx)
अणु
	काष्ठा siw_ucontext *uctx = to_siw_ctx(base_ctx);

	atomic_dec(&uctx->sdev->num_ctx);
पूर्ण

पूर्णांक siw_query_device(काष्ठा ib_device *base_dev, काष्ठा ib_device_attr *attr,
		     काष्ठा ib_udata *udata)
अणु
	काष्ठा siw_device *sdev = to_siw_dev(base_dev);

	अगर (udata->inlen || udata->outlen)
		वापस -EINVAL;

	स_रखो(attr, 0, माप(*attr));

	/* Revisit atomic caps अगर RFC 7306 माला_लो supported */
	attr->atomic_cap = 0;
	attr->device_cap_flags =
		IB_DEVICE_MEM_MGT_EXTENSIONS | IB_DEVICE_ALLOW_USER_UNREG;
	attr->max_cq = sdev->attrs.max_cq;
	attr->max_cqe = sdev->attrs.max_cqe;
	attr->max_fast_reg_page_list_len = SIW_MAX_SGE_PBL;
	attr->max_mr = sdev->attrs.max_mr;
	attr->max_mw = sdev->attrs.max_mw;
	attr->max_mr_size = ~0ull;
	attr->max_pd = sdev->attrs.max_pd;
	attr->max_qp = sdev->attrs.max_qp;
	attr->max_qp_init_rd_atom = sdev->attrs.max_ird;
	attr->max_qp_rd_atom = sdev->attrs.max_ord;
	attr->max_qp_wr = sdev->attrs.max_qp_wr;
	attr->max_recv_sge = sdev->attrs.max_sge;
	attr->max_res_rd_atom = sdev->attrs.max_qp * sdev->attrs.max_ird;
	attr->max_send_sge = sdev->attrs.max_sge;
	attr->max_sge_rd = sdev->attrs.max_sge_rd;
	attr->max_srq = sdev->attrs.max_srq;
	attr->max_srq_sge = sdev->attrs.max_srq_sge;
	attr->max_srq_wr = sdev->attrs.max_srq_wr;
	attr->page_size_cap = PAGE_SIZE;
	attr->venकरोr_id = SIW_VENDOR_ID;
	attr->venकरोr_part_id = sdev->venकरोr_part_id;

	स_नकल(&attr->sys_image_guid, sdev->netdev->dev_addr, 6);

	वापस 0;
पूर्ण

पूर्णांक siw_query_port(काष्ठा ib_device *base_dev, u32 port,
		   काष्ठा ib_port_attr *attr)
अणु
	काष्ठा siw_device *sdev = to_siw_dev(base_dev);
	पूर्णांक rv;

	स_रखो(attr, 0, माप(*attr));

	rv = ib_get_eth_speed(base_dev, port, &attr->active_speed,
			 &attr->active_width);
	attr->gid_tbl_len = 1;
	attr->max_msg_sz = -1;
	attr->max_mtu = ib_mtu_पूर्णांक_to_क्रमागत(sdev->netdev->mtu);
	attr->active_mtu = ib_mtu_पूर्णांक_to_क्रमागत(sdev->netdev->mtu);
	attr->phys_state = sdev->state == IB_PORT_ACTIVE ?
		IB_PORT_PHYS_STATE_LINK_UP : IB_PORT_PHYS_STATE_DISABLED;
	attr->port_cap_flags = IB_PORT_CM_SUP | IB_PORT_DEVICE_MGMT_SUP;
	attr->state = sdev->state;
	/*
	 * All zero
	 *
	 * attr->lid = 0;
	 * attr->bad_pkey_cntr = 0;
	 * attr->qkey_viol_cntr = 0;
	 * attr->sm_lid = 0;
	 * attr->lmc = 0;
	 * attr->max_vl_num = 0;
	 * attr->sm_sl = 0;
	 * attr->subnet_समयout = 0;
	 * attr->init_type_repy = 0;
	 */
	वापस rv;
पूर्ण

पूर्णांक siw_get_port_immutable(काष्ठा ib_device *base_dev, u32 port,
			   काष्ठा ib_port_immutable *port_immutable)
अणु
	काष्ठा ib_port_attr attr;
	पूर्णांक rv = siw_query_port(base_dev, port, &attr);

	अगर (rv)
		वापस rv;

	port_immutable->gid_tbl_len = attr.gid_tbl_len;
	port_immutable->core_cap_flags = RDMA_CORE_PORT_IWARP;

	वापस 0;
पूर्ण

पूर्णांक siw_query_gid(काष्ठा ib_device *base_dev, u32 port, पूर्णांक idx,
		  जोड़ ib_gid *gid)
अणु
	काष्ठा siw_device *sdev = to_siw_dev(base_dev);

	/* subnet_prefix == पूर्णांकerface_id == 0; */
	स_रखो(gid, 0, माप(*gid));
	स_नकल(&gid->raw[0], sdev->netdev->dev_addr, 6);

	वापस 0;
पूर्ण

पूर्णांक siw_alloc_pd(काष्ठा ib_pd *pd, काष्ठा ib_udata *udata)
अणु
	काष्ठा siw_device *sdev = to_siw_dev(pd->device);

	अगर (atomic_inc_वापस(&sdev->num_pd) > SIW_MAX_PD) अणु
		atomic_dec(&sdev->num_pd);
		वापस -ENOMEM;
	पूर्ण
	siw_dbg_pd(pd, "now %d PD's(s)\n", atomic_पढ़ो(&sdev->num_pd));

	वापस 0;
पूर्ण

पूर्णांक siw_dealloc_pd(काष्ठा ib_pd *pd, काष्ठा ib_udata *udata)
अणु
	काष्ठा siw_device *sdev = to_siw_dev(pd->device);

	siw_dbg_pd(pd, "free PD\n");
	atomic_dec(&sdev->num_pd);
	वापस 0;
पूर्ण

व्योम siw_qp_get_ref(काष्ठा ib_qp *base_qp)
अणु
	siw_qp_get(to_siw_qp(base_qp));
पूर्ण

व्योम siw_qp_put_ref(काष्ठा ib_qp *base_qp)
अणु
	siw_qp_put(to_siw_qp(base_qp));
पूर्ण

अटल काष्ठा rdma_user_mmap_entry *
siw_mmap_entry_insert(काष्ठा siw_ucontext *uctx,
		      व्योम *address, माप_प्रकार length,
		      u64 *offset)
अणु
	काष्ठा siw_user_mmap_entry *entry = kzalloc(माप(*entry), GFP_KERNEL);
	पूर्णांक rv;

	*offset = SIW_INVAL_UOBJ_KEY;
	अगर (!entry)
		वापस शून्य;

	entry->address = address;

	rv = rdma_user_mmap_entry_insert(&uctx->base_ucontext,
					 &entry->rdma_entry,
					 length);
	अगर (rv) अणु
		kमुक्त(entry);
		वापस शून्य;
	पूर्ण

	*offset = rdma_user_mmap_get_offset(&entry->rdma_entry);

	वापस &entry->rdma_entry;
पूर्ण

/*
 * siw_create_qp()
 *
 * Create QP of requested size on given device.
 *
 * @pd:		Protection Doमुख्य
 * @attrs:	Initial QP attributes.
 * @udata:	used to provide QP ID, SQ and RQ size back to user.
 */

काष्ठा ib_qp *siw_create_qp(काष्ठा ib_pd *pd,
			    काष्ठा ib_qp_init_attr *attrs,
			    काष्ठा ib_udata *udata)
अणु
	काष्ठा siw_qp *qp = शून्य;
	काष्ठा ib_device *base_dev = pd->device;
	काष्ठा siw_device *sdev = to_siw_dev(base_dev);
	काष्ठा siw_ucontext *uctx =
		rdma_udata_to_drv_context(udata, काष्ठा siw_ucontext,
					  base_ucontext);
	अचिन्हित दीर्घ flags;
	पूर्णांक num_sqe, num_rqe, rv = 0;
	माप_प्रकार length;

	siw_dbg(base_dev, "create new QP\n");

	अगर (attrs->create_flags)
		वापस ERR_PTR(-EOPNOTSUPP);

	अगर (atomic_inc_वापस(&sdev->num_qp) > SIW_MAX_QP) अणु
		siw_dbg(base_dev, "too many QP's\n");
		rv = -ENOMEM;
		जाओ err_out;
	पूर्ण
	अगर (attrs->qp_type != IB_QPT_RC) अणु
		siw_dbg(base_dev, "only RC QP's supported\n");
		rv = -EOPNOTSUPP;
		जाओ err_out;
	पूर्ण
	अगर ((attrs->cap.max_send_wr > SIW_MAX_QP_WR) ||
	    (attrs->cap.max_recv_wr > SIW_MAX_QP_WR) ||
	    (attrs->cap.max_send_sge > SIW_MAX_SGE) ||
	    (attrs->cap.max_recv_sge > SIW_MAX_SGE)) अणु
		siw_dbg(base_dev, "QP size error\n");
		rv = -EINVAL;
		जाओ err_out;
	पूर्ण
	अगर (attrs->cap.max_अंतरभूत_data > SIW_MAX_INLINE) अणु
		siw_dbg(base_dev, "max inline send: %d > %d\n",
			attrs->cap.max_अंतरभूत_data, (पूर्णांक)SIW_MAX_INLINE);
		rv = -EINVAL;
		जाओ err_out;
	पूर्ण
	/*
	 * NOTE: we allow क्रम zero element SQ and RQ WQE's SGL's
	 * but not क्रम a QP unable to hold any WQE (SQ + RQ)
	 */
	अगर (attrs->cap.max_send_wr + attrs->cap.max_recv_wr == 0) अणु
		siw_dbg(base_dev, "QP must have send or receive queue\n");
		rv = -EINVAL;
		जाओ err_out;
	पूर्ण

	अगर (!attrs->send_cq || (!attrs->recv_cq && !attrs->srq)) अणु
		siw_dbg(base_dev, "send CQ or receive CQ invalid\n");
		rv = -EINVAL;
		जाओ err_out;
	पूर्ण
	qp = kzalloc(माप(*qp), GFP_KERNEL);
	अगर (!qp) अणु
		rv = -ENOMEM;
		जाओ err_out;
	पूर्ण
	init_rwsem(&qp->state_lock);
	spin_lock_init(&qp->sq_lock);
	spin_lock_init(&qp->rq_lock);
	spin_lock_init(&qp->orq_lock);

	rv = siw_qp_add(sdev, qp);
	अगर (rv)
		जाओ err_out;

	num_sqe = attrs->cap.max_send_wr;
	num_rqe = attrs->cap.max_recv_wr;

	/* All queue indices are derived from modulo operations
	 * on a मुक्त running 'get' (consumer) and 'put' (producer)
	 * अचिन्हित counter. Having queue sizes at घातer of two
	 * aव्योमs handling counter wrap around.
	 */
	अगर (num_sqe)
		num_sqe = roundup_घात_of_two(num_sqe);
	अन्यथा अणु
		/* Zero sized SQ is not supported */
		rv = -EINVAL;
		जाओ err_out_xa;
	पूर्ण
	अगर (num_rqe)
		num_rqe = roundup_घात_of_two(num_rqe);

	अगर (udata)
		qp->sendq = vदो_स्मृति_user(num_sqe * माप(काष्ठा siw_sqe));
	अन्यथा
		qp->sendq = vzalloc(num_sqe * माप(काष्ठा siw_sqe));

	अगर (qp->sendq == शून्य) अणु
		rv = -ENOMEM;
		जाओ err_out_xa;
	पूर्ण
	अगर (attrs->sq_sig_type != IB_SIGNAL_REQ_WR) अणु
		अगर (attrs->sq_sig_type == IB_SIGNAL_ALL_WR)
			qp->attrs.flags |= SIW_SIGNAL_ALL_WR;
		अन्यथा अणु
			rv = -EINVAL;
			जाओ err_out_xa;
		पूर्ण
	पूर्ण
	qp->pd = pd;
	qp->scq = to_siw_cq(attrs->send_cq);
	qp->rcq = to_siw_cq(attrs->recv_cq);

	अगर (attrs->srq) अणु
		/*
		 * SRQ support.
		 * Verbs 6.3.7: ignore RQ size, अगर SRQ present
		 * Verbs 6.3.5: करो not check PD of SRQ against PD of QP
		 */
		qp->srq = to_siw_srq(attrs->srq);
		qp->attrs.rq_size = 0;
		siw_dbg(base_dev, "QP [%u]: SRQ attached\n",
			qp->base_qp.qp_num);
	पूर्ण अन्यथा अगर (num_rqe) अणु
		अगर (udata)
			qp->recvq =
				vदो_स्मृति_user(num_rqe * माप(काष्ठा siw_rqe));
		अन्यथा
			qp->recvq = vzalloc(num_rqe * माप(काष्ठा siw_rqe));

		अगर (qp->recvq == शून्य) अणु
			rv = -ENOMEM;
			जाओ err_out_xa;
		पूर्ण
		qp->attrs.rq_size = num_rqe;
	पूर्ण
	qp->attrs.sq_size = num_sqe;
	qp->attrs.sq_max_sges = attrs->cap.max_send_sge;
	qp->attrs.rq_max_sges = attrs->cap.max_recv_sge;

	/* Make those two tunables fixed क्रम now. */
	qp->tx_ctx.gso_seg_limit = 1;
	qp->tx_ctx.zcopy_tx = zcopy_tx;

	qp->attrs.state = SIW_QP_STATE_IDLE;

	अगर (udata) अणु
		काष्ठा siw_uresp_create_qp uresp = अणुपूर्ण;

		uresp.num_sqe = num_sqe;
		uresp.num_rqe = num_rqe;
		uresp.qp_id = qp_id(qp);

		अगर (qp->sendq) अणु
			length = num_sqe * माप(काष्ठा siw_sqe);
			qp->sq_entry =
				siw_mmap_entry_insert(uctx, qp->sendq,
						      length, &uresp.sq_key);
			अगर (!qp->sq_entry) अणु
				rv = -ENOMEM;
				जाओ err_out_xa;
			पूर्ण
		पूर्ण

		अगर (qp->recvq) अणु
			length = num_rqe * माप(काष्ठा siw_rqe);
			qp->rq_entry =
				siw_mmap_entry_insert(uctx, qp->recvq,
						      length, &uresp.rq_key);
			अगर (!qp->rq_entry) अणु
				uresp.sq_key = SIW_INVAL_UOBJ_KEY;
				rv = -ENOMEM;
				जाओ err_out_xa;
			पूर्ण
		पूर्ण

		अगर (udata->outlen < माप(uresp)) अणु
			rv = -EINVAL;
			जाओ err_out_xa;
		पूर्ण
		rv = ib_copy_to_udata(udata, &uresp, माप(uresp));
		अगर (rv)
			जाओ err_out_xa;
	पूर्ण
	qp->tx_cpu = siw_get_tx_cpu(sdev);
	अगर (qp->tx_cpu < 0) अणु
		rv = -EINVAL;
		जाओ err_out_xa;
	पूर्ण
	INIT_LIST_HEAD(&qp->devq);
	spin_lock_irqsave(&sdev->lock, flags);
	list_add_tail(&qp->devq, &sdev->qp_list);
	spin_unlock_irqrestore(&sdev->lock, flags);

	वापस &qp->base_qp;

err_out_xa:
	xa_erase(&sdev->qp_xa, qp_id(qp));
err_out:
	अगर (qp) अणु
		अगर (uctx) अणु
			rdma_user_mmap_entry_हटाओ(qp->sq_entry);
			rdma_user_mmap_entry_हटाओ(qp->rq_entry);
		पूर्ण
		vमुक्त(qp->sendq);
		vमुक्त(qp->recvq);
		kमुक्त(qp);
	पूर्ण
	atomic_dec(&sdev->num_qp);

	वापस ERR_PTR(rv);
पूर्ण

/*
 * Minimum siw_query_qp() verb पूर्णांकerface.
 *
 * @qp_attr_mask is not used but all available inक्रमmation is provided
 */
पूर्णांक siw_query_qp(काष्ठा ib_qp *base_qp, काष्ठा ib_qp_attr *qp_attr,
		 पूर्णांक qp_attr_mask, काष्ठा ib_qp_init_attr *qp_init_attr)
अणु
	काष्ठा siw_qp *qp;
	काष्ठा siw_device *sdev;

	अगर (base_qp && qp_attr && qp_init_attr) अणु
		qp = to_siw_qp(base_qp);
		sdev = to_siw_dev(base_qp->device);
	पूर्ण अन्यथा अणु
		वापस -EINVAL;
	पूर्ण
	qp_attr->cap.max_अंतरभूत_data = SIW_MAX_INLINE;
	qp_attr->cap.max_send_wr = qp->attrs.sq_size;
	qp_attr->cap.max_send_sge = qp->attrs.sq_max_sges;
	qp_attr->cap.max_recv_wr = qp->attrs.rq_size;
	qp_attr->cap.max_recv_sge = qp->attrs.rq_max_sges;
	qp_attr->path_mtu = ib_mtu_पूर्णांक_to_क्रमागत(sdev->netdev->mtu);
	qp_attr->max_rd_atomic = qp->attrs.irq_size;
	qp_attr->max_dest_rd_atomic = qp->attrs.orq_size;

	qp_attr->qp_access_flags = IB_ACCESS_LOCAL_WRITE |
				   IB_ACCESS_REMOTE_WRITE |
				   IB_ACCESS_REMOTE_READ;

	qp_init_attr->qp_type = base_qp->qp_type;
	qp_init_attr->send_cq = base_qp->send_cq;
	qp_init_attr->recv_cq = base_qp->recv_cq;
	qp_init_attr->srq = base_qp->srq;

	qp_init_attr->cap = qp_attr->cap;

	वापस 0;
पूर्ण

पूर्णांक siw_verbs_modअगरy_qp(काष्ठा ib_qp *base_qp, काष्ठा ib_qp_attr *attr,
			पूर्णांक attr_mask, काष्ठा ib_udata *udata)
अणु
	काष्ठा siw_qp_attrs new_attrs;
	क्रमागत siw_qp_attr_mask siw_attr_mask = 0;
	काष्ठा siw_qp *qp = to_siw_qp(base_qp);
	पूर्णांक rv = 0;

	अगर (!attr_mask)
		वापस 0;

	अगर (attr_mask & ~IB_QP_ATTR_STANDARD_BITS)
		वापस -EOPNOTSUPP;

	स_रखो(&new_attrs, 0, माप(new_attrs));

	अगर (attr_mask & IB_QP_ACCESS_FLAGS) अणु
		siw_attr_mask = SIW_QP_ATTR_ACCESS_FLAGS;

		अगर (attr->qp_access_flags & IB_ACCESS_REMOTE_READ)
			new_attrs.flags |= SIW_RDMA_READ_ENABLED;
		अगर (attr->qp_access_flags & IB_ACCESS_REMOTE_WRITE)
			new_attrs.flags |= SIW_RDMA_WRITE_ENABLED;
		अगर (attr->qp_access_flags & IB_ACCESS_MW_BIND)
			new_attrs.flags |= SIW_RDMA_BIND_ENABLED;
	पूर्ण
	अगर (attr_mask & IB_QP_STATE) अणु
		siw_dbg_qp(qp, "desired IB QP state: %s\n",
			   ib_qp_state_to_string[attr->qp_state]);

		new_attrs.state = ib_qp_state_to_siw_qp_state[attr->qp_state];

		अगर (new_attrs.state > SIW_QP_STATE_RTS)
			qp->tx_ctx.tx_suspend = 1;

		siw_attr_mask |= SIW_QP_ATTR_STATE;
	पूर्ण
	अगर (!siw_attr_mask)
		जाओ out;

	करोwn_ग_लिखो(&qp->state_lock);

	rv = siw_qp_modअगरy(qp, &new_attrs, siw_attr_mask);

	up_ग_लिखो(&qp->state_lock);
out:
	वापस rv;
पूर्ण

पूर्णांक siw_destroy_qp(काष्ठा ib_qp *base_qp, काष्ठा ib_udata *udata)
अणु
	काष्ठा siw_qp *qp = to_siw_qp(base_qp);
	काष्ठा siw_ucontext *uctx =
		rdma_udata_to_drv_context(udata, काष्ठा siw_ucontext,
					  base_ucontext);
	काष्ठा siw_qp_attrs qp_attrs;

	siw_dbg_qp(qp, "state %d\n", qp->attrs.state);

	/*
	 * Mark QP as in process of deकाष्ठाion to prevent from
	 * any async callbacks to RDMA core
	 */
	qp->attrs.flags |= SIW_QP_IN_DESTROY;
	qp->rx_stream.rx_suspend = 1;

	अगर (uctx) अणु
		rdma_user_mmap_entry_हटाओ(qp->sq_entry);
		rdma_user_mmap_entry_हटाओ(qp->rq_entry);
	पूर्ण

	करोwn_ग_लिखो(&qp->state_lock);

	qp_attrs.state = SIW_QP_STATE_ERROR;
	siw_qp_modअगरy(qp, &qp_attrs, SIW_QP_ATTR_STATE);

	अगर (qp->cep) अणु
		siw_cep_put(qp->cep);
		qp->cep = शून्य;
	पूर्ण
	up_ग_लिखो(&qp->state_lock);

	kमुक्त(qp->tx_ctx.mpa_crc_hd);
	kमुक्त(qp->rx_stream.mpa_crc_hd);

	qp->scq = qp->rcq = शून्य;

	siw_qp_put(qp);

	वापस 0;
पूर्ण

/*
 * siw_copy_अंतरभूत_sgl()
 *
 * Prepare sgl of अंतरभूतd data क्रम sending. For userland callers
 * function checks अगर given buffer addresses and len's are within
 * process context bounds.
 * Data from all provided sge's are copied together पूर्णांकo the wqe,
 * referenced by a single sge.
 */
अटल पूर्णांक siw_copy_अंतरभूत_sgl(स्थिर काष्ठा ib_send_wr *core_wr,
			       काष्ठा siw_sqe *sqe)
अणु
	काष्ठा ib_sge *core_sge = core_wr->sg_list;
	व्योम *kbuf = &sqe->sge[1];
	पूर्णांक num_sge = core_wr->num_sge, bytes = 0;

	sqe->sge[0].laddr = (uपूर्णांकptr_t)kbuf;
	sqe->sge[0].lkey = 0;

	जबतक (num_sge--) अणु
		अगर (!core_sge->length) अणु
			core_sge++;
			जारी;
		पूर्ण
		bytes += core_sge->length;
		अगर (bytes > SIW_MAX_INLINE) अणु
			bytes = -EINVAL;
			अवरोध;
		पूर्ण
		स_नकल(kbuf, (व्योम *)(uपूर्णांकptr_t)core_sge->addr,
		       core_sge->length);

		kbuf += core_sge->length;
		core_sge++;
	पूर्ण
	sqe->sge[0].length = bytes > 0 ? bytes : 0;
	sqe->num_sge = bytes > 0 ? 1 : 0;

	वापस bytes;
पूर्ण

/* Complete SQ WR's without processing */
अटल पूर्णांक siw_sq_flush_wr(काष्ठा siw_qp *qp, स्थिर काष्ठा ib_send_wr *wr,
			   स्थिर काष्ठा ib_send_wr **bad_wr)
अणु
	काष्ठा siw_sqe sqe = अणुपूर्ण;
	पूर्णांक rv = 0;

	जबतक (wr) अणु
		sqe.id = wr->wr_id;
		sqe.opcode = wr->opcode;
		rv = siw_sqe_complete(qp, &sqe, 0, SIW_WC_WR_FLUSH_ERR);
		अगर (rv) अणु
			अगर (bad_wr)
				*bad_wr = wr;
			अवरोध;
		पूर्ण
		wr = wr->next;
	पूर्ण
	वापस rv;
पूर्ण

/* Complete RQ WR's without processing */
अटल पूर्णांक siw_rq_flush_wr(काष्ठा siw_qp *qp, स्थिर काष्ठा ib_recv_wr *wr,
			   स्थिर काष्ठा ib_recv_wr **bad_wr)
अणु
	काष्ठा siw_rqe rqe = अणुपूर्ण;
	पूर्णांक rv = 0;

	जबतक (wr) अणु
		rqe.id = wr->wr_id;
		rv = siw_rqe_complete(qp, &rqe, 0, 0, SIW_WC_WR_FLUSH_ERR);
		अगर (rv) अणु
			अगर (bad_wr)
				*bad_wr = wr;
			अवरोध;
		पूर्ण
		wr = wr->next;
	पूर्ण
	वापस rv;
पूर्ण

/*
 * siw_post_send()
 *
 * Post a list of S-WR's to a SQ.
 *
 * @base_qp:	Base QP contained in siw QP
 * @wr:		Null terminated list of user WR's
 * @bad_wr:	Poपूर्णांकs to failing WR in हाल of synchronous failure.
 */
पूर्णांक siw_post_send(काष्ठा ib_qp *base_qp, स्थिर काष्ठा ib_send_wr *wr,
		  स्थिर काष्ठा ib_send_wr **bad_wr)
अणु
	काष्ठा siw_qp *qp = to_siw_qp(base_qp);
	काष्ठा siw_wqe *wqe = tx_wqe(qp);

	अचिन्हित दीर्घ flags;
	पूर्णांक rv = 0;

	अगर (wr && !rdma_is_kernel_res(&qp->base_qp.res)) अणु
		siw_dbg_qp(qp, "wr must be empty for user mapped sq\n");
		*bad_wr = wr;
		वापस -EINVAL;
	पूर्ण

	/*
	 * Try to acquire QP state lock. Must be non-blocking
	 * to accommodate kernel clients needs.
	 */
	अगर (!करोwn_पढ़ो_trylock(&qp->state_lock)) अणु
		अगर (qp->attrs.state == SIW_QP_STATE_ERROR) अणु
			/*
			 * ERROR state is final, so we can be sure
			 * this state will not change as दीर्घ as the QP
			 * exists.
			 *
			 * This handles an ib_drain_sq() call with
			 * a concurrent request to set the QP state
			 * to ERROR.
			 */
			rv = siw_sq_flush_wr(qp, wr, bad_wr);
		पूर्ण अन्यथा अणु
			siw_dbg_qp(qp, "QP locked, state %d\n",
				   qp->attrs.state);
			*bad_wr = wr;
			rv = -ENOTCONN;
		पूर्ण
		वापस rv;
	पूर्ण
	अगर (unlikely(qp->attrs.state != SIW_QP_STATE_RTS)) अणु
		अगर (qp->attrs.state == SIW_QP_STATE_ERROR) अणु
			/*
			 * Immediately flush this WR to CQ, अगर QP
			 * is in ERROR state. SQ is guaranteed to
			 * be empty, so WR complets in-order.
			 *
			 * Typically triggered by ib_drain_sq().
			 */
			rv = siw_sq_flush_wr(qp, wr, bad_wr);
		पूर्ण अन्यथा अणु
			siw_dbg_qp(qp, "QP out of state %d\n",
				   qp->attrs.state);
			*bad_wr = wr;
			rv = -ENOTCONN;
		पूर्ण
		up_पढ़ो(&qp->state_lock);
		वापस rv;
	पूर्ण
	spin_lock_irqsave(&qp->sq_lock, flags);

	जबतक (wr) अणु
		u32 idx = qp->sq_put % qp->attrs.sq_size;
		काष्ठा siw_sqe *sqe = &qp->sendq[idx];

		अगर (sqe->flags) अणु
			siw_dbg_qp(qp, "sq full\n");
			rv = -ENOMEM;
			अवरोध;
		पूर्ण
		अगर (wr->num_sge > qp->attrs.sq_max_sges) अणु
			siw_dbg_qp(qp, "too many sge's: %d\n", wr->num_sge);
			rv = -EINVAL;
			अवरोध;
		पूर्ण
		sqe->id = wr->wr_id;

		अगर ((wr->send_flags & IB_SEND_SIGNALED) ||
		    (qp->attrs.flags & SIW_SIGNAL_ALL_WR))
			sqe->flags |= SIW_WQE_SIGNALLED;

		अगर (wr->send_flags & IB_SEND_FENCE)
			sqe->flags |= SIW_WQE_READ_FENCE;

		चयन (wr->opcode) अणु
		हाल IB_WR_SEND:
		हाल IB_WR_SEND_WITH_INV:
			अगर (wr->send_flags & IB_SEND_SOLICITED)
				sqe->flags |= SIW_WQE_SOLICITED;

			अगर (!(wr->send_flags & IB_SEND_INLINE)) अणु
				siw_copy_sgl(wr->sg_list, sqe->sge,
					     wr->num_sge);
				sqe->num_sge = wr->num_sge;
			पूर्ण अन्यथा अणु
				rv = siw_copy_अंतरभूत_sgl(wr, sqe);
				अगर (rv <= 0) अणु
					rv = -EINVAL;
					अवरोध;
				पूर्ण
				sqe->flags |= SIW_WQE_INLINE;
				sqe->num_sge = 1;
			पूर्ण
			अगर (wr->opcode == IB_WR_SEND)
				sqe->opcode = SIW_OP_SEND;
			अन्यथा अणु
				sqe->opcode = SIW_OP_SEND_REMOTE_INV;
				sqe->rkey = wr->ex.invalidate_rkey;
			पूर्ण
			अवरोध;

		हाल IB_WR_RDMA_READ_WITH_INV:
		हाल IB_WR_RDMA_READ:
			/*
			 * iWarp restricts RREAD sink to SGL containing
			 * 1 SGE only. we could relax to SGL with multiple
			 * elements referring the SAME ltag or even sending
			 * a निजी per-rreq tag referring to a checked
			 * local sgl with MULTIPLE ltag's.
			 */
			अगर (unlikely(wr->num_sge != 1)) अणु
				rv = -EINVAL;
				अवरोध;
			पूर्ण
			siw_copy_sgl(wr->sg_list, &sqe->sge[0], 1);
			/*
			 * NOTE: zero length RREAD is allowed!
			 */
			sqe->raddr = rdma_wr(wr)->remote_addr;
			sqe->rkey = rdma_wr(wr)->rkey;
			sqe->num_sge = 1;

			अगर (wr->opcode == IB_WR_RDMA_READ)
				sqe->opcode = SIW_OP_READ;
			अन्यथा
				sqe->opcode = SIW_OP_READ_LOCAL_INV;
			अवरोध;

		हाल IB_WR_RDMA_WRITE:
			अगर (!(wr->send_flags & IB_SEND_INLINE)) अणु
				siw_copy_sgl(wr->sg_list, &sqe->sge[0],
					     wr->num_sge);
				sqe->num_sge = wr->num_sge;
			पूर्ण अन्यथा अणु
				rv = siw_copy_अंतरभूत_sgl(wr, sqe);
				अगर (unlikely(rv < 0)) अणु
					rv = -EINVAL;
					अवरोध;
				पूर्ण
				sqe->flags |= SIW_WQE_INLINE;
				sqe->num_sge = 1;
			पूर्ण
			sqe->raddr = rdma_wr(wr)->remote_addr;
			sqe->rkey = rdma_wr(wr)->rkey;
			sqe->opcode = SIW_OP_WRITE;
			अवरोध;

		हाल IB_WR_REG_MR:
			sqe->base_mr = (uपूर्णांकptr_t)reg_wr(wr)->mr;
			sqe->rkey = reg_wr(wr)->key;
			sqe->access = reg_wr(wr)->access & IWARP_ACCESS_MASK;
			sqe->opcode = SIW_OP_REG_MR;
			अवरोध;

		हाल IB_WR_LOCAL_INV:
			sqe->rkey = wr->ex.invalidate_rkey;
			sqe->opcode = SIW_OP_INVAL_STAG;
			अवरोध;

		शेष:
			siw_dbg_qp(qp, "ib wr type %d unsupported\n",
				   wr->opcode);
			rv = -EINVAL;
			अवरोध;
		पूर्ण
		siw_dbg_qp(qp, "opcode %d, flags 0x%x, wr_id 0x%pK\n",
			   sqe->opcode, sqe->flags,
			   (व्योम *)(uपूर्णांकptr_t)sqe->id);

		अगर (unlikely(rv < 0))
			अवरोध;

		/* make SQE only valid after completely written */
		smp_wmb();
		sqe->flags |= SIW_WQE_VALID;

		qp->sq_put++;
		wr = wr->next;
	पूर्ण

	/*
	 * Send directly अगर SQ processing is not in progress.
	 * Eventual immediate errors (rv < 0) करो not affect the involved
	 * RI resources (Verbs, 8.3.1) and thus करो not prevent from SQ
	 * processing, अगर new work is alपढ़ोy pending. But rv must be passed
	 * to caller.
	 */
	अगर (wqe->wr_status != SIW_WR_IDLE) अणु
		spin_unlock_irqrestore(&qp->sq_lock, flags);
		जाओ skip_direct_sending;
	पूर्ण
	rv = siw_activate_tx(qp);
	spin_unlock_irqrestore(&qp->sq_lock, flags);

	अगर (rv <= 0)
		जाओ skip_direct_sending;

	अगर (rdma_is_kernel_res(&qp->base_qp.res)) अणु
		rv = siw_sq_start(qp);
	पूर्ण अन्यथा अणु
		qp->tx_ctx.in_syscall = 1;

		अगर (siw_qp_sq_process(qp) != 0 && !(qp->tx_ctx.tx_suspend))
			siw_qp_cm_drop(qp, 0);

		qp->tx_ctx.in_syscall = 0;
	पूर्ण
skip_direct_sending:

	up_पढ़ो(&qp->state_lock);

	अगर (rv >= 0)
		वापस 0;
	/*
	 * Immediate error
	 */
	siw_dbg_qp(qp, "error %d\n", rv);

	*bad_wr = wr;
	वापस rv;
पूर्ण

/*
 * siw_post_receive()
 *
 * Post a list of R-WR's to a RQ.
 *
 * @base_qp:	Base QP contained in siw QP
 * @wr:		Null terminated list of user WR's
 * @bad_wr:	Poपूर्णांकs to failing WR in हाल of synchronous failure.
 */
पूर्णांक siw_post_receive(काष्ठा ib_qp *base_qp, स्थिर काष्ठा ib_recv_wr *wr,
		     स्थिर काष्ठा ib_recv_wr **bad_wr)
अणु
	काष्ठा siw_qp *qp = to_siw_qp(base_qp);
	अचिन्हित दीर्घ flags;
	पूर्णांक rv = 0;

	अगर (qp->srq || qp->attrs.rq_size == 0) अणु
		*bad_wr = wr;
		वापस -EINVAL;
	पूर्ण
	अगर (!rdma_is_kernel_res(&qp->base_qp.res)) अणु
		siw_dbg_qp(qp, "no kernel post_recv for user mapped rq\n");
		*bad_wr = wr;
		वापस -EINVAL;
	पूर्ण

	/*
	 * Try to acquire QP state lock. Must be non-blocking
	 * to accommodate kernel clients needs.
	 */
	अगर (!करोwn_पढ़ो_trylock(&qp->state_lock)) अणु
		अगर (qp->attrs.state == SIW_QP_STATE_ERROR) अणु
			/*
			 * ERROR state is final, so we can be sure
			 * this state will not change as दीर्घ as the QP
			 * exists.
			 *
			 * This handles an ib_drain_rq() call with
			 * a concurrent request to set the QP state
			 * to ERROR.
			 */
			rv = siw_rq_flush_wr(qp, wr, bad_wr);
		पूर्ण अन्यथा अणु
			siw_dbg_qp(qp, "QP locked, state %d\n",
				   qp->attrs.state);
			*bad_wr = wr;
			rv = -ENOTCONN;
		पूर्ण
		वापस rv;
	पूर्ण
	अगर (qp->attrs.state > SIW_QP_STATE_RTS) अणु
		अगर (qp->attrs.state == SIW_QP_STATE_ERROR) अणु
			/*
			 * Immediately flush this WR to CQ, अगर QP
			 * is in ERROR state. RQ is guaranteed to
			 * be empty, so WR complets in-order.
			 *
			 * Typically triggered by ib_drain_rq().
			 */
			rv = siw_rq_flush_wr(qp, wr, bad_wr);
		पूर्ण अन्यथा अणु
			siw_dbg_qp(qp, "QP out of state %d\n",
				   qp->attrs.state);
			*bad_wr = wr;
			rv = -ENOTCONN;
		पूर्ण
		up_पढ़ो(&qp->state_lock);
		वापस rv;
	पूर्ण
	/*
	 * Serialize potentially multiple producers.
	 * Not needed क्रम single thपढ़ोed consumer side.
	 */
	spin_lock_irqsave(&qp->rq_lock, flags);

	जबतक (wr) अणु
		u32 idx = qp->rq_put % qp->attrs.rq_size;
		काष्ठा siw_rqe *rqe = &qp->recvq[idx];

		अगर (rqe->flags) अणु
			siw_dbg_qp(qp, "RQ full\n");
			rv = -ENOMEM;
			अवरोध;
		पूर्ण
		अगर (wr->num_sge > qp->attrs.rq_max_sges) अणु
			siw_dbg_qp(qp, "too many sge's: %d\n", wr->num_sge);
			rv = -EINVAL;
			अवरोध;
		पूर्ण
		rqe->id = wr->wr_id;
		rqe->num_sge = wr->num_sge;
		siw_copy_sgl(wr->sg_list, rqe->sge, wr->num_sge);

		/* make sure RQE is completely written beक्रमe valid */
		smp_wmb();

		rqe->flags = SIW_WQE_VALID;

		qp->rq_put++;
		wr = wr->next;
	पूर्ण
	spin_unlock_irqrestore(&qp->rq_lock, flags);

	up_पढ़ो(&qp->state_lock);

	अगर (rv < 0) अणु
		siw_dbg_qp(qp, "error %d\n", rv);
		*bad_wr = wr;
	पूर्ण
	वापस rv > 0 ? 0 : rv;
पूर्ण

पूर्णांक siw_destroy_cq(काष्ठा ib_cq *base_cq, काष्ठा ib_udata *udata)
अणु
	काष्ठा siw_cq *cq = to_siw_cq(base_cq);
	काष्ठा siw_device *sdev = to_siw_dev(base_cq->device);
	काष्ठा siw_ucontext *ctx =
		rdma_udata_to_drv_context(udata, काष्ठा siw_ucontext,
					  base_ucontext);

	siw_dbg_cq(cq, "free CQ resources\n");

	siw_cq_flush(cq);

	अगर (ctx)
		rdma_user_mmap_entry_हटाओ(cq->cq_entry);

	atomic_dec(&sdev->num_cq);

	vमुक्त(cq->queue);
	वापस 0;
पूर्ण

/*
 * siw_create_cq()
 *
 * Populate CQ of requested size
 *
 * @base_cq: CQ as allocated by RDMA midlayer
 * @attr: Initial CQ attributes
 * @udata: relates to user context
 */

पूर्णांक siw_create_cq(काष्ठा ib_cq *base_cq, स्थिर काष्ठा ib_cq_init_attr *attr,
		  काष्ठा ib_udata *udata)
अणु
	काष्ठा siw_device *sdev = to_siw_dev(base_cq->device);
	काष्ठा siw_cq *cq = to_siw_cq(base_cq);
	पूर्णांक rv, size = attr->cqe;

	अगर (attr->flags)
		वापस -EOPNOTSUPP;

	अगर (atomic_inc_वापस(&sdev->num_cq) > SIW_MAX_CQ) अणु
		siw_dbg(base_cq->device, "too many CQ's\n");
		rv = -ENOMEM;
		जाओ err_out;
	पूर्ण
	अगर (size < 1 || size > sdev->attrs.max_cqe) अणु
		siw_dbg(base_cq->device, "CQ size error: %d\n", size);
		rv = -EINVAL;
		जाओ err_out;
	पूर्ण
	size = roundup_घात_of_two(size);
	cq->base_cq.cqe = size;
	cq->num_cqe = size;

	अगर (udata)
		cq->queue = vदो_स्मृति_user(size * माप(काष्ठा siw_cqe) +
					 माप(काष्ठा siw_cq_ctrl));
	अन्यथा
		cq->queue = vzalloc(size * माप(काष्ठा siw_cqe) +
				    माप(काष्ठा siw_cq_ctrl));

	अगर (cq->queue == शून्य) अणु
		rv = -ENOMEM;
		जाओ err_out;
	पूर्ण
	get_अक्रमom_bytes(&cq->id, 4);
	siw_dbg(base_cq->device, "new CQ [%u]\n", cq->id);

	spin_lock_init(&cq->lock);

	cq->notअगरy = (काष्ठा siw_cq_ctrl *)&cq->queue[size];

	अगर (udata) अणु
		काष्ठा siw_uresp_create_cq uresp = अणुपूर्ण;
		काष्ठा siw_ucontext *ctx =
			rdma_udata_to_drv_context(udata, काष्ठा siw_ucontext,
						  base_ucontext);
		माप_प्रकार length = size * माप(काष्ठा siw_cqe) +
			माप(काष्ठा siw_cq_ctrl);

		cq->cq_entry =
			siw_mmap_entry_insert(ctx, cq->queue,
					      length, &uresp.cq_key);
		अगर (!cq->cq_entry) अणु
			rv = -ENOMEM;
			जाओ err_out;
		पूर्ण

		uresp.cq_id = cq->id;
		uresp.num_cqe = size;

		अगर (udata->outlen < माप(uresp)) अणु
			rv = -EINVAL;
			जाओ err_out;
		पूर्ण
		rv = ib_copy_to_udata(udata, &uresp, माप(uresp));
		अगर (rv)
			जाओ err_out;
	पूर्ण
	वापस 0;

err_out:
	siw_dbg(base_cq->device, "CQ creation failed: %d", rv);

	अगर (cq && cq->queue) अणु
		काष्ठा siw_ucontext *ctx =
			rdma_udata_to_drv_context(udata, काष्ठा siw_ucontext,
						  base_ucontext);
		अगर (ctx)
			rdma_user_mmap_entry_हटाओ(cq->cq_entry);
		vमुक्त(cq->queue);
	पूर्ण
	atomic_dec(&sdev->num_cq);

	वापस rv;
पूर्ण

/*
 * siw_poll_cq()
 *
 * Reap CQ entries अगर available and copy work completion status पूर्णांकo
 * array of WC's provided by caller. Returns number of reaped CQE's.
 *
 * @base_cq:	Base CQ contained in siw CQ.
 * @num_cqe:	Maximum number of CQE's to reap.
 * @wc:		Array of work completions to be filled by siw.
 */
पूर्णांक siw_poll_cq(काष्ठा ib_cq *base_cq, पूर्णांक num_cqe, काष्ठा ib_wc *wc)
अणु
	काष्ठा siw_cq *cq = to_siw_cq(base_cq);
	पूर्णांक i;

	क्रम (i = 0; i < num_cqe; i++) अणु
		अगर (!siw_reap_cqe(cq, wc))
			अवरोध;
		wc++;
	पूर्ण
	वापस i;
पूर्ण

/*
 * siw_req_notअगरy_cq()
 *
 * Request notअगरication क्रम new CQE's added to that CQ.
 * Defined flags:
 * o SIW_CQ_NOTIFY_SOLICITED lets siw trigger a notअगरication
 *   event अगर a WQE with notअगरication flag set enters the CQ
 * o SIW_CQ_NOTIFY_NEXT_COMP lets siw trigger a notअगरication
 *   event अगर a WQE enters the CQ.
 * o IB_CQ_REPORT_MISSED_EVENTS: वापस value will provide the
 *   number of not reaped CQE's regardless of its notअगरication
 *   type and current or new CQ notअगरication settings.
 *
 * @base_cq:	Base CQ contained in siw CQ.
 * @flags:	Requested notअगरication flags.
 */
पूर्णांक siw_req_notअगरy_cq(काष्ठा ib_cq *base_cq, क्रमागत ib_cq_notअगरy_flags flags)
अणु
	काष्ठा siw_cq *cq = to_siw_cq(base_cq);

	siw_dbg_cq(cq, "flags: 0x%02x\n", flags);

	अगर ((flags & IB_CQ_SOLICITED_MASK) == IB_CQ_SOLICITED)
		/*
		 * Enable CQ event क्रम next solicited completion.
		 * and make it visible to all associated producers.
		 */
		smp_store_mb(cq->notअगरy->flags, SIW_NOTIFY_SOLICITED);
	अन्यथा
		/*
		 * Enable CQ event क्रम any संकेतled completion.
		 * and make it visible to all associated producers.
		 */
		smp_store_mb(cq->notअगरy->flags, SIW_NOTIFY_ALL);

	अगर (flags & IB_CQ_REPORT_MISSED_EVENTS)
		वापस cq->cq_put - cq->cq_get;

	वापस 0;
पूर्ण

/*
 * siw_dereg_mr()
 *
 * Release Memory Region.
 *
 * @base_mr: Base MR contained in siw MR.
 * @udata: poपूर्णांकs to user context, unused.
 */
पूर्णांक siw_dereg_mr(काष्ठा ib_mr *base_mr, काष्ठा ib_udata *udata)
अणु
	काष्ठा siw_mr *mr = to_siw_mr(base_mr);
	काष्ठा siw_device *sdev = to_siw_dev(base_mr->device);

	siw_dbg_mem(mr->mem, "deregister MR\n");

	atomic_dec(&sdev->num_mr);

	siw_mr_drop_mem(mr);
	kमुक्त_rcu(mr, rcu);

	वापस 0;
पूर्ण

/*
 * siw_reg_user_mr()
 *
 * Register Memory Region.
 *
 * @pd:		Protection Doमुख्य
 * @start:	starting address of MR (भव address)
 * @len:	len of MR
 * @rnic_va:	not used by siw
 * @rights:	MR access rights
 * @udata:	user buffer to communicate STag and Key.
 */
काष्ठा ib_mr *siw_reg_user_mr(काष्ठा ib_pd *pd, u64 start, u64 len,
			      u64 rnic_va, पूर्णांक rights, काष्ठा ib_udata *udata)
अणु
	काष्ठा siw_mr *mr = शून्य;
	काष्ठा siw_umem *umem = शून्य;
	काष्ठा siw_ureq_reg_mr ureq;
	काष्ठा siw_device *sdev = to_siw_dev(pd->device);

	अचिन्हित दीर्घ mem_limit = rlimit(RLIMIT_MEMLOCK);
	पूर्णांक rv;

	siw_dbg_pd(pd, "start: 0x%pK, va: 0x%pK, len: %llu\n",
		   (व्योम *)(uपूर्णांकptr_t)start, (व्योम *)(uपूर्णांकptr_t)rnic_va,
		   (अचिन्हित दीर्घ दीर्घ)len);

	अगर (atomic_inc_वापस(&sdev->num_mr) > SIW_MAX_MR) अणु
		siw_dbg_pd(pd, "too many mr's\n");
		rv = -ENOMEM;
		जाओ err_out;
	पूर्ण
	अगर (!len) अणु
		rv = -EINVAL;
		जाओ err_out;
	पूर्ण
	अगर (mem_limit != RLIM_अनन्त) अणु
		अचिन्हित दीर्घ num_pages =
			(PAGE_ALIGN(len + (start & ~PAGE_MASK))) >> PAGE_SHIFT;
		mem_limit >>= PAGE_SHIFT;

		अगर (num_pages > mem_limit - current->mm->locked_vm) अणु
			siw_dbg_pd(pd, "pages req %lu, max %lu, lock %lu\n",
				   num_pages, mem_limit,
				   current->mm->locked_vm);
			rv = -ENOMEM;
			जाओ err_out;
		पूर्ण
	पूर्ण
	umem = siw_umem_get(start, len, ib_access_writable(rights));
	अगर (IS_ERR(umem)) अणु
		rv = PTR_ERR(umem);
		siw_dbg_pd(pd, "getting user memory failed: %d\n", rv);
		umem = शून्य;
		जाओ err_out;
	पूर्ण
	mr = kzalloc(माप(*mr), GFP_KERNEL);
	अगर (!mr) अणु
		rv = -ENOMEM;
		जाओ err_out;
	पूर्ण
	rv = siw_mr_add_mem(mr, pd, umem, start, len, rights);
	अगर (rv)
		जाओ err_out;

	अगर (udata) अणु
		काष्ठा siw_uresp_reg_mr uresp = अणुपूर्ण;
		काष्ठा siw_mem *mem = mr->mem;

		अगर (udata->inlen < माप(ureq)) अणु
			rv = -EINVAL;
			जाओ err_out;
		पूर्ण
		rv = ib_copy_from_udata(&ureq, udata, माप(ureq));
		अगर (rv)
			जाओ err_out;

		mr->base_mr.lkey |= ureq.stag_key;
		mr->base_mr.rkey |= ureq.stag_key;
		mem->stag |= ureq.stag_key;
		uresp.stag = mem->stag;

		अगर (udata->outlen < माप(uresp)) अणु
			rv = -EINVAL;
			जाओ err_out;
		पूर्ण
		rv = ib_copy_to_udata(udata, &uresp, माप(uresp));
		अगर (rv)
			जाओ err_out;
	पूर्ण
	mr->mem->stag_valid = 1;

	वापस &mr->base_mr;

err_out:
	atomic_dec(&sdev->num_mr);
	अगर (mr) अणु
		अगर (mr->mem)
			siw_mr_drop_mem(mr);
		kमुक्त_rcu(mr, rcu);
	पूर्ण अन्यथा अणु
		अगर (umem)
			siw_umem_release(umem, false);
	पूर्ण
	वापस ERR_PTR(rv);
पूर्ण

काष्ठा ib_mr *siw_alloc_mr(काष्ठा ib_pd *pd, क्रमागत ib_mr_type mr_type,
			   u32 max_sge)
अणु
	काष्ठा siw_device *sdev = to_siw_dev(pd->device);
	काष्ठा siw_mr *mr = शून्य;
	काष्ठा siw_pbl *pbl = शून्य;
	पूर्णांक rv;

	अगर (atomic_inc_वापस(&sdev->num_mr) > SIW_MAX_MR) अणु
		siw_dbg_pd(pd, "too many mr's\n");
		rv = -ENOMEM;
		जाओ err_out;
	पूर्ण
	अगर (mr_type != IB_MR_TYPE_MEM_REG) अणु
		siw_dbg_pd(pd, "mr type %d unsupported\n", mr_type);
		rv = -EOPNOTSUPP;
		जाओ err_out;
	पूर्ण
	अगर (max_sge > SIW_MAX_SGE_PBL) अणु
		siw_dbg_pd(pd, "too many sge's: %d\n", max_sge);
		rv = -ENOMEM;
		जाओ err_out;
	पूर्ण
	pbl = siw_pbl_alloc(max_sge);
	अगर (IS_ERR(pbl)) अणु
		rv = PTR_ERR(pbl);
		siw_dbg_pd(pd, "pbl allocation failed: %d\n", rv);
		pbl = शून्य;
		जाओ err_out;
	पूर्ण
	mr = kzalloc(माप(*mr), GFP_KERNEL);
	अगर (!mr) अणु
		rv = -ENOMEM;
		जाओ err_out;
	पूर्ण
	rv = siw_mr_add_mem(mr, pd, pbl, 0, max_sge * PAGE_SIZE, 0);
	अगर (rv)
		जाओ err_out;

	mr->mem->is_pbl = 1;

	siw_dbg_pd(pd, "[MEM %u]: success\n", mr->mem->stag);

	वापस &mr->base_mr;

err_out:
	atomic_dec(&sdev->num_mr);

	अगर (!mr) अणु
		kमुक्त(pbl);
	पूर्ण अन्यथा अणु
		अगर (mr->mem)
			siw_mr_drop_mem(mr);
		kमुक्त_rcu(mr, rcu);
	पूर्ण
	siw_dbg_pd(pd, "failed: %d\n", rv);

	वापस ERR_PTR(rv);
पूर्ण

/* Just used to count number of pages being mapped */
अटल पूर्णांक siw_set_pbl_page(काष्ठा ib_mr *base_mr, u64 buf_addr)
अणु
	वापस 0;
पूर्ण

पूर्णांक siw_map_mr_sg(काष्ठा ib_mr *base_mr, काष्ठा scatterlist *sl, पूर्णांक num_sle,
		  अचिन्हित पूर्णांक *sg_off)
अणु
	काष्ठा scatterlist *slp;
	काष्ठा siw_mr *mr = to_siw_mr(base_mr);
	काष्ठा siw_mem *mem = mr->mem;
	काष्ठा siw_pbl *pbl = mem->pbl;
	काष्ठा siw_pble *pble;
	अचिन्हित दीर्घ pbl_size;
	पूर्णांक i, rv;

	अगर (!pbl) अणु
		siw_dbg_mem(mem, "no PBL allocated\n");
		वापस -EINVAL;
	पूर्ण
	pble = pbl->pbe;

	अगर (pbl->max_buf < num_sle) अणु
		siw_dbg_mem(mem, "too many SGE's: %d > %d\n",
			    mem->pbl->max_buf, num_sle);
		वापस -ENOMEM;
	पूर्ण
	क्रम_each_sg(sl, slp, num_sle, i) अणु
		अगर (sg_dma_len(slp) == 0) अणु
			siw_dbg_mem(mem, "empty SGE\n");
			वापस -EINVAL;
		पूर्ण
		अगर (i == 0) अणु
			pble->addr = sg_dma_address(slp);
			pble->size = sg_dma_len(slp);
			pble->pbl_off = 0;
			pbl_size = pble->size;
			pbl->num_buf = 1;
		पूर्ण अन्यथा अणु
			/* Merge PBL entries अगर adjacent */
			अगर (pble->addr + pble->size == sg_dma_address(slp)) अणु
				pble->size += sg_dma_len(slp);
			पूर्ण अन्यथा अणु
				pble++;
				pbl->num_buf++;
				pble->addr = sg_dma_address(slp);
				pble->size = sg_dma_len(slp);
				pble->pbl_off = pbl_size;
			पूर्ण
			pbl_size += sg_dma_len(slp);
		पूर्ण
		siw_dbg_mem(mem,
			"sge[%d], size %u, addr 0x%p, total %lu\n",
			i, pble->size, (व्योम *)(uपूर्णांकptr_t)pble->addr,
			pbl_size);
	पूर्ण
	rv = ib_sg_to_pages(base_mr, sl, num_sle, sg_off, siw_set_pbl_page);
	अगर (rv > 0) अणु
		mem->len = base_mr->length;
		mem->va = base_mr->iova;
		siw_dbg_mem(mem,
			"%llu bytes, start 0x%pK, %u SLE to %u entries\n",
			mem->len, (व्योम *)(uपूर्णांकptr_t)mem->va, num_sle,
			pbl->num_buf);
	पूर्ण
	वापस rv;
पूर्ण

/*
 * siw_get_dma_mr()
 *
 * Create a (empty) DMA memory region, where no umem is attached.
 */
काष्ठा ib_mr *siw_get_dma_mr(काष्ठा ib_pd *pd, पूर्णांक rights)
अणु
	काष्ठा siw_device *sdev = to_siw_dev(pd->device);
	काष्ठा siw_mr *mr = शून्य;
	पूर्णांक rv;

	अगर (atomic_inc_वापस(&sdev->num_mr) > SIW_MAX_MR) अणु
		siw_dbg_pd(pd, "too many mr's\n");
		rv = -ENOMEM;
		जाओ err_out;
	पूर्ण
	mr = kzalloc(माप(*mr), GFP_KERNEL);
	अगर (!mr) अणु
		rv = -ENOMEM;
		जाओ err_out;
	पूर्ण
	rv = siw_mr_add_mem(mr, pd, शून्य, 0, अच_दीर्घ_उच्च, rights);
	अगर (rv)
		जाओ err_out;

	mr->mem->stag_valid = 1;

	siw_dbg_pd(pd, "[MEM %u]: success\n", mr->mem->stag);

	वापस &mr->base_mr;

err_out:
	अगर (rv)
		kमुक्त(mr);

	atomic_dec(&sdev->num_mr);

	वापस ERR_PTR(rv);
पूर्ण

/*
 * siw_create_srq()
 *
 * Create Shared Receive Queue of attributes @init_attrs
 * within protection करोमुख्य given by @pd.
 *
 * @base_srq:	Base SRQ contained in siw SRQ.
 * @init_attrs:	SRQ init attributes.
 * @udata:	poपूर्णांकs to user context
 */
पूर्णांक siw_create_srq(काष्ठा ib_srq *base_srq,
		   काष्ठा ib_srq_init_attr *init_attrs, काष्ठा ib_udata *udata)
अणु
	काष्ठा siw_srq *srq = to_siw_srq(base_srq);
	काष्ठा ib_srq_attr *attrs = &init_attrs->attr;
	काष्ठा siw_device *sdev = to_siw_dev(base_srq->device);
	काष्ठा siw_ucontext *ctx =
		rdma_udata_to_drv_context(udata, काष्ठा siw_ucontext,
					  base_ucontext);
	पूर्णांक rv;

	अगर (init_attrs->srq_type != IB_SRQT_BASIC)
		वापस -EOPNOTSUPP;

	अगर (atomic_inc_वापस(&sdev->num_srq) > SIW_MAX_SRQ) अणु
		siw_dbg_pd(base_srq->pd, "too many SRQ's\n");
		rv = -ENOMEM;
		जाओ err_out;
	पूर्ण
	अगर (attrs->max_wr == 0 || attrs->max_wr > SIW_MAX_SRQ_WR ||
	    attrs->max_sge > SIW_MAX_SGE || attrs->srq_limit > attrs->max_wr) अणु
		rv = -EINVAL;
		जाओ err_out;
	पूर्ण
	srq->max_sge = attrs->max_sge;
	srq->num_rqe = roundup_घात_of_two(attrs->max_wr);
	srq->limit = attrs->srq_limit;
	अगर (srq->limit)
		srq->armed = true;

	srq->is_kernel_res = !udata;

	अगर (udata)
		srq->recvq =
			vदो_स्मृति_user(srq->num_rqe * माप(काष्ठा siw_rqe));
	अन्यथा
		srq->recvq = vzalloc(srq->num_rqe * माप(काष्ठा siw_rqe));

	अगर (srq->recvq == शून्य) अणु
		rv = -ENOMEM;
		जाओ err_out;
	पूर्ण
	अगर (udata) अणु
		काष्ठा siw_uresp_create_srq uresp = अणुपूर्ण;
		माप_प्रकार length = srq->num_rqe * माप(काष्ठा siw_rqe);

		srq->srq_entry =
			siw_mmap_entry_insert(ctx, srq->recvq,
					      length, &uresp.srq_key);
		अगर (!srq->srq_entry) अणु
			rv = -ENOMEM;
			जाओ err_out;
		पूर्ण

		uresp.num_rqe = srq->num_rqe;

		अगर (udata->outlen < माप(uresp)) अणु
			rv = -EINVAL;
			जाओ err_out;
		पूर्ण
		rv = ib_copy_to_udata(udata, &uresp, माप(uresp));
		अगर (rv)
			जाओ err_out;
	पूर्ण
	spin_lock_init(&srq->lock);

	siw_dbg_pd(base_srq->pd, "[SRQ]: success\n");

	वापस 0;

err_out:
	अगर (srq->recvq) अणु
		अगर (ctx)
			rdma_user_mmap_entry_हटाओ(srq->srq_entry);
		vमुक्त(srq->recvq);
	पूर्ण
	atomic_dec(&sdev->num_srq);

	वापस rv;
पूर्ण

/*
 * siw_modअगरy_srq()
 *
 * Modअगरy SRQ. The caller may resize SRQ and/or set/reset notअगरication
 * limit and (re)arm IB_EVENT_SRQ_LIMIT_REACHED notअगरication.
 *
 * NOTE: it is unclear अगर RDMA core allows क्रम changing the MAX_SGE
 * parameter. siw_modअगरy_srq() करोes not check the attrs->max_sge param.
 */
पूर्णांक siw_modअगरy_srq(काष्ठा ib_srq *base_srq, काष्ठा ib_srq_attr *attrs,
		   क्रमागत ib_srq_attr_mask attr_mask, काष्ठा ib_udata *udata)
अणु
	काष्ठा siw_srq *srq = to_siw_srq(base_srq);
	अचिन्हित दीर्घ flags;
	पूर्णांक rv = 0;

	spin_lock_irqsave(&srq->lock, flags);

	अगर (attr_mask & IB_SRQ_MAX_WR) अणु
		/* resize request not yet supported */
		rv = -EOPNOTSUPP;
		जाओ out;
	पूर्ण
	अगर (attr_mask & IB_SRQ_LIMIT) अणु
		अगर (attrs->srq_limit) अणु
			अगर (unlikely(attrs->srq_limit > srq->num_rqe)) अणु
				rv = -EINVAL;
				जाओ out;
			पूर्ण
			srq->armed = true;
		पूर्ण अन्यथा अणु
			srq->armed = false;
		पूर्ण
		srq->limit = attrs->srq_limit;
	पूर्ण
out:
	spin_unlock_irqrestore(&srq->lock, flags);

	वापस rv;
पूर्ण

/*
 * siw_query_srq()
 *
 * Query SRQ attributes.
 */
पूर्णांक siw_query_srq(काष्ठा ib_srq *base_srq, काष्ठा ib_srq_attr *attrs)
अणु
	काष्ठा siw_srq *srq = to_siw_srq(base_srq);
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&srq->lock, flags);

	attrs->max_wr = srq->num_rqe;
	attrs->max_sge = srq->max_sge;
	attrs->srq_limit = srq->limit;

	spin_unlock_irqrestore(&srq->lock, flags);

	वापस 0;
पूर्ण

/*
 * siw_destroy_srq()
 *
 * Destroy SRQ.
 * It is assumed that the SRQ is not referenced by any
 * QP anymore - the code trusts the RDMA core environment to keep track
 * of QP references.
 */
पूर्णांक siw_destroy_srq(काष्ठा ib_srq *base_srq, काष्ठा ib_udata *udata)
अणु
	काष्ठा siw_srq *srq = to_siw_srq(base_srq);
	काष्ठा siw_device *sdev = to_siw_dev(base_srq->device);
	काष्ठा siw_ucontext *ctx =
		rdma_udata_to_drv_context(udata, काष्ठा siw_ucontext,
					  base_ucontext);

	अगर (ctx)
		rdma_user_mmap_entry_हटाओ(srq->srq_entry);
	vमुक्त(srq->recvq);
	atomic_dec(&sdev->num_srq);
	वापस 0;
पूर्ण

/*
 * siw_post_srq_recv()
 *
 * Post a list of receive queue elements to SRQ.
 * NOTE: The function करोes not check or lock a certain SRQ state
 *       during the post operation. The code simply trusts the
 *       RDMA core environment.
 *
 * @base_srq:	Base SRQ contained in siw SRQ
 * @wr:		List of R-WR's
 * @bad_wr:	Updated to failing WR अगर posting fails.
 */
पूर्णांक siw_post_srq_recv(काष्ठा ib_srq *base_srq, स्थिर काष्ठा ib_recv_wr *wr,
		      स्थिर काष्ठा ib_recv_wr **bad_wr)
अणु
	काष्ठा siw_srq *srq = to_siw_srq(base_srq);
	अचिन्हित दीर्घ flags;
	पूर्णांक rv = 0;

	अगर (unlikely(!srq->is_kernel_res)) अणु
		siw_dbg_pd(base_srq->pd,
			   "[SRQ]: no kernel post_recv for mapped srq\n");
		rv = -EINVAL;
		जाओ out;
	पूर्ण
	/*
	 * Serialize potentially multiple producers.
	 * Also needed to serialize potentially multiple
	 * consumers.
	 */
	spin_lock_irqsave(&srq->lock, flags);

	जबतक (wr) अणु
		u32 idx = srq->rq_put % srq->num_rqe;
		काष्ठा siw_rqe *rqe = &srq->recvq[idx];

		अगर (rqe->flags) अणु
			siw_dbg_pd(base_srq->pd, "SRQ full\n");
			rv = -ENOMEM;
			अवरोध;
		पूर्ण
		अगर (unlikely(wr->num_sge > srq->max_sge)) अणु
			siw_dbg_pd(base_srq->pd,
				   "[SRQ]: too many sge's: %d\n", wr->num_sge);
			rv = -EINVAL;
			अवरोध;
		पूर्ण
		rqe->id = wr->wr_id;
		rqe->num_sge = wr->num_sge;
		siw_copy_sgl(wr->sg_list, rqe->sge, wr->num_sge);

		/* Make sure S-RQE is completely written beक्रमe valid */
		smp_wmb();

		rqe->flags = SIW_WQE_VALID;

		srq->rq_put++;
		wr = wr->next;
	पूर्ण
	spin_unlock_irqrestore(&srq->lock, flags);
out:
	अगर (unlikely(rv < 0)) अणु
		siw_dbg_pd(base_srq->pd, "[SRQ]: error %d\n", rv);
		*bad_wr = wr;
	पूर्ण
	वापस rv;
पूर्ण

व्योम siw_qp_event(काष्ठा siw_qp *qp, क्रमागत ib_event_type etype)
अणु
	काष्ठा ib_event event;
	काष्ठा ib_qp *base_qp = &qp->base_qp;

	/*
	 * Do not report asynchronous errors on QP which माला_लो
	 * destroyed via verbs पूर्णांकerface (siw_destroy_qp())
	 */
	अगर (qp->attrs.flags & SIW_QP_IN_DESTROY)
		वापस;

	event.event = etype;
	event.device = base_qp->device;
	event.element.qp = base_qp;

	अगर (base_qp->event_handler) अणु
		siw_dbg_qp(qp, "reporting event %d\n", etype);
		base_qp->event_handler(&event, base_qp->qp_context);
	पूर्ण
पूर्ण

व्योम siw_cq_event(काष्ठा siw_cq *cq, क्रमागत ib_event_type etype)
अणु
	काष्ठा ib_event event;
	काष्ठा ib_cq *base_cq = &cq->base_cq;

	event.event = etype;
	event.device = base_cq->device;
	event.element.cq = base_cq;

	अगर (base_cq->event_handler) अणु
		siw_dbg_cq(cq, "reporting CQ event %d\n", etype);
		base_cq->event_handler(&event, base_cq->cq_context);
	पूर्ण
पूर्ण

व्योम siw_srq_event(काष्ठा siw_srq *srq, क्रमागत ib_event_type etype)
अणु
	काष्ठा ib_event event;
	काष्ठा ib_srq *base_srq = &srq->base_srq;

	event.event = etype;
	event.device = base_srq->device;
	event.element.srq = base_srq;

	अगर (base_srq->event_handler) अणु
		siw_dbg_pd(srq->base_srq.pd,
			   "reporting SRQ event %d\n", etype);
		base_srq->event_handler(&event, base_srq->srq_context);
	पूर्ण
पूर्ण

व्योम siw_port_event(काष्ठा siw_device *sdev, u32 port, क्रमागत ib_event_type etype)
अणु
	काष्ठा ib_event event;

	event.event = etype;
	event.device = &sdev->base_dev;
	event.element.port_num = port;

	siw_dbg(&sdev->base_dev, "reporting port event %d\n", etype);

	ib_dispatch_event(&event);
पूर्ण
