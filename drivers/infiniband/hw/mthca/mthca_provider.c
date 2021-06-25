<शैली गुरु>
/*
 * Copyright (c) 2004, 2005 Topspin Communications.  All rights reserved.
 * Copyright (c) 2005 Sun Microप्रणालीs, Inc. All rights reserved.
 * Copyright (c) 2005, 2006 Cisco Systems.  All rights reserved.
 * Copyright (c) 2005 Mellanox Technologies. All rights reserved.
 * Copyright (c) 2004 Voltaire, Inc. All rights reserved.
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

#समावेश <rdma/ib_smi.h>
#समावेश <rdma/ib_uस्मृति.स>
#समावेश <rdma/ib_user_verbs.h>
#समावेश <rdma/uverbs_ioctl.h>

#समावेश <linux/sched.h>
#समावेश <linux/slab.h>
#समावेश <linux/स्थिति.स>
#समावेश <linux/mm.h>
#समावेश <linux/export.h>

#समावेश "mthca_dev.h"
#समावेश "mthca_cmd.h"
#समावेश <rdma/mthca-abi.h>
#समावेश "mthca_memfree.h"

अटल व्योम init_query_mad(काष्ठा ib_smp *mad)
अणु
	mad->base_version  = 1;
	mad->mgmt_class    = IB_MGMT_CLASS_SUBN_LID_ROUTED;
	mad->class_version = 1;
	mad->method    	   = IB_MGMT_METHOD_GET;
पूर्ण

अटल पूर्णांक mthca_query_device(काष्ठा ib_device *ibdev, काष्ठा ib_device_attr *props,
			      काष्ठा ib_udata *uhw)
अणु
	काष्ठा ib_smp *in_mad  = शून्य;
	काष्ठा ib_smp *out_mad = शून्य;
	पूर्णांक err = -ENOMEM;
	काष्ठा mthca_dev *mdev = to_mdev(ibdev);

	अगर (uhw->inlen || uhw->outlen)
		वापस -EINVAL;

	in_mad  = kzalloc(माप *in_mad, GFP_KERNEL);
	out_mad = kदो_स्मृति(माप *out_mad, GFP_KERNEL);
	अगर (!in_mad || !out_mad)
		जाओ out;

	स_रखो(props, 0, माप *props);

	props->fw_ver              = mdev->fw_ver;

	init_query_mad(in_mad);
	in_mad->attr_id = IB_SMP_ATTR_NODE_INFO;

	err = mthca_MAD_IFC(mdev, 1, 1,
			    1, शून्य, शून्य, in_mad, out_mad);
	अगर (err)
		जाओ out;

	props->device_cap_flags    = mdev->device_cap_flags;
	props->venकरोr_id           = be32_to_cpup((__be32 *) (out_mad->data + 36)) &
		0xffffff;
	props->venकरोr_part_id      = be16_to_cpup((__be16 *) (out_mad->data + 30));
	props->hw_ver              = be32_to_cpup((__be32 *) (out_mad->data + 32));
	स_नकल(&props->sys_image_guid, out_mad->data +  4, 8);

	props->max_mr_size         = ~0ull;
	props->page_size_cap       = mdev->limits.page_size_cap;
	props->max_qp              = mdev->limits.num_qps - mdev->limits.reserved_qps;
	props->max_qp_wr           = mdev->limits.max_wqes;
	props->max_send_sge        = mdev->limits.max_sg;
	props->max_recv_sge        = mdev->limits.max_sg;
	props->max_sge_rd          = mdev->limits.max_sg;
	props->max_cq              = mdev->limits.num_cqs - mdev->limits.reserved_cqs;
	props->max_cqe             = mdev->limits.max_cqes;
	props->max_mr              = mdev->limits.num_mpts - mdev->limits.reserved_mrws;
	props->max_pd              = mdev->limits.num_pds - mdev->limits.reserved_pds;
	props->max_qp_rd_atom      = 1 << mdev->qp_table.rdb_shअगरt;
	props->max_qp_init_rd_atom = mdev->limits.max_qp_init_rdma;
	props->max_res_rd_atom     = props->max_qp_rd_atom * props->max_qp;
	props->max_srq             = mdev->limits.num_srqs - mdev->limits.reserved_srqs;
	props->max_srq_wr          = mdev->limits.max_srq_wqes;
	props->max_srq_sge         = mdev->limits.max_srq_sge;
	props->local_ca_ack_delay  = mdev->limits.local_ca_ack_delay;
	props->atomic_cap          = mdev->limits.flags & DEV_LIM_FLAG_ATOMIC ?
					IB_ATOMIC_HCA : IB_ATOMIC_NONE;
	props->max_pkeys           = mdev->limits.pkey_table_len;
	props->max_mcast_grp       = mdev->limits.num_mgms + mdev->limits.num_amgms;
	props->max_mcast_qp_attach = MTHCA_QP_PER_MGM;
	props->max_total_mcast_qp_attach = props->max_mcast_qp_attach *
					   props->max_mcast_grp;

	err = 0;
 out:
	kमुक्त(in_mad);
	kमुक्त(out_mad);
	वापस err;
पूर्ण

अटल पूर्णांक mthca_query_port(काष्ठा ib_device *ibdev,
			    u32 port, काष्ठा ib_port_attr *props)
अणु
	काष्ठा ib_smp *in_mad  = शून्य;
	काष्ठा ib_smp *out_mad = शून्य;
	पूर्णांक err = -ENOMEM;

	in_mad  = kzalloc(माप *in_mad, GFP_KERNEL);
	out_mad = kदो_स्मृति(माप *out_mad, GFP_KERNEL);
	अगर (!in_mad || !out_mad)
		जाओ out;

	/* props being zeroed by the caller, aव्योम zeroing it here */

	init_query_mad(in_mad);
	in_mad->attr_id  = IB_SMP_ATTR_PORT_INFO;
	in_mad->attr_mod = cpu_to_be32(port);

	err = mthca_MAD_IFC(to_mdev(ibdev), 1, 1,
			    port, शून्य, शून्य, in_mad, out_mad);
	अगर (err)
		जाओ out;

	props->lid               = be16_to_cpup((__be16 *) (out_mad->data + 16));
	props->lmc               = out_mad->data[34] & 0x7;
	props->sm_lid            = be16_to_cpup((__be16 *) (out_mad->data + 18));
	props->sm_sl             = out_mad->data[36] & 0xf;
	props->state             = out_mad->data[32] & 0xf;
	props->phys_state        = out_mad->data[33] >> 4;
	props->port_cap_flags    = be32_to_cpup((__be32 *) (out_mad->data + 20));
	props->gid_tbl_len       = to_mdev(ibdev)->limits.gid_table_len;
	props->max_msg_sz        = 0x80000000;
	props->pkey_tbl_len      = to_mdev(ibdev)->limits.pkey_table_len;
	props->bad_pkey_cntr     = be16_to_cpup((__be16 *) (out_mad->data + 46));
	props->qkey_viol_cntr    = be16_to_cpup((__be16 *) (out_mad->data + 48));
	props->active_width      = out_mad->data[31] & 0xf;
	props->active_speed      = out_mad->data[35] >> 4;
	props->max_mtu           = out_mad->data[41] & 0xf;
	props->active_mtu        = out_mad->data[36] >> 4;
	props->subnet_समयout    = out_mad->data[51] & 0x1f;
	props->max_vl_num        = out_mad->data[37] >> 4;
	props->init_type_reply   = out_mad->data[41] >> 4;

 out:
	kमुक्त(in_mad);
	kमुक्त(out_mad);
	वापस err;
पूर्ण

अटल पूर्णांक mthca_modअगरy_device(काष्ठा ib_device *ibdev,
			       पूर्णांक mask,
			       काष्ठा ib_device_modअगरy *props)
अणु
	अगर (mask & ~IB_DEVICE_MODIFY_NODE_DESC)
		वापस -EOPNOTSUPP;

	अगर (mask & IB_DEVICE_MODIFY_NODE_DESC) अणु
		अगर (mutex_lock_पूर्णांकerruptible(&to_mdev(ibdev)->cap_mask_mutex))
			वापस -ERESTARTSYS;
		स_नकल(ibdev->node_desc, props->node_desc,
		       IB_DEVICE_NODE_DESC_MAX);
		mutex_unlock(&to_mdev(ibdev)->cap_mask_mutex);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक mthca_modअगरy_port(काष्ठा ib_device *ibdev,
			     u32 port, पूर्णांक port_modअगरy_mask,
			     काष्ठा ib_port_modअगरy *props)
अणु
	काष्ठा mthca_set_ib_param set_ib;
	काष्ठा ib_port_attr attr;
	पूर्णांक err;

	अगर (mutex_lock_पूर्णांकerruptible(&to_mdev(ibdev)->cap_mask_mutex))
		वापस -ERESTARTSYS;

	err = ib_query_port(ibdev, port, &attr);
	अगर (err)
		जाओ out;

	set_ib.set_si_guid     = 0;
	set_ib.reset_qkey_viol = !!(port_modअगरy_mask & IB_PORT_RESET_QKEY_CNTR);

	set_ib.cap_mask = (attr.port_cap_flags | props->set_port_cap_mask) &
		~props->clr_port_cap_mask;

	err = mthca_SET_IB(to_mdev(ibdev), &set_ib, port);
	अगर (err)
		जाओ out;
out:
	mutex_unlock(&to_mdev(ibdev)->cap_mask_mutex);
	वापस err;
पूर्ण

अटल पूर्णांक mthca_query_pkey(काष्ठा ib_device *ibdev,
			    u32 port, u16 index, u16 *pkey)
अणु
	काष्ठा ib_smp *in_mad  = शून्य;
	काष्ठा ib_smp *out_mad = शून्य;
	पूर्णांक err = -ENOMEM;

	in_mad  = kzalloc(माप *in_mad, GFP_KERNEL);
	out_mad = kदो_स्मृति(माप *out_mad, GFP_KERNEL);
	अगर (!in_mad || !out_mad)
		जाओ out;

	init_query_mad(in_mad);
	in_mad->attr_id  = IB_SMP_ATTR_PKEY_TABLE;
	in_mad->attr_mod = cpu_to_be32(index / 32);

	err = mthca_MAD_IFC(to_mdev(ibdev), 1, 1,
			    port, शून्य, शून्य, in_mad, out_mad);
	अगर (err)
		जाओ out;

	*pkey = be16_to_cpu(((__be16 *) out_mad->data)[index % 32]);

 out:
	kमुक्त(in_mad);
	kमुक्त(out_mad);
	वापस err;
पूर्ण

अटल पूर्णांक mthca_query_gid(काष्ठा ib_device *ibdev, u32 port,
			   पूर्णांक index, जोड़ ib_gid *gid)
अणु
	काष्ठा ib_smp *in_mad  = शून्य;
	काष्ठा ib_smp *out_mad = शून्य;
	पूर्णांक err = -ENOMEM;

	in_mad  = kzalloc(माप *in_mad, GFP_KERNEL);
	out_mad = kदो_स्मृति(माप *out_mad, GFP_KERNEL);
	अगर (!in_mad || !out_mad)
		जाओ out;

	init_query_mad(in_mad);
	in_mad->attr_id  = IB_SMP_ATTR_PORT_INFO;
	in_mad->attr_mod = cpu_to_be32(port);

	err = mthca_MAD_IFC(to_mdev(ibdev), 1, 1,
			    port, शून्य, शून्य, in_mad, out_mad);
	अगर (err)
		जाओ out;

	स_नकल(gid->raw, out_mad->data + 8, 8);

	init_query_mad(in_mad);
	in_mad->attr_id  = IB_SMP_ATTR_GUID_INFO;
	in_mad->attr_mod = cpu_to_be32(index / 8);

	err = mthca_MAD_IFC(to_mdev(ibdev), 1, 1,
			    port, शून्य, शून्य, in_mad, out_mad);
	अगर (err)
		जाओ out;

	स_नकल(gid->raw + 8, out_mad->data + (index % 8) * 8, 8);

 out:
	kमुक्त(in_mad);
	kमुक्त(out_mad);
	वापस err;
पूर्ण

अटल पूर्णांक mthca_alloc_ucontext(काष्ठा ib_ucontext *uctx,
				काष्ठा ib_udata *udata)
अणु
	काष्ठा ib_device *ibdev = uctx->device;
	काष्ठा mthca_alloc_ucontext_resp uresp = अणुपूर्ण;
	काष्ठा mthca_ucontext *context = to_mucontext(uctx);
	पूर्णांक                              err;

	अगर (!(to_mdev(ibdev)->active))
		वापस -EAGAIN;

	uresp.qp_tab_size = to_mdev(ibdev)->limits.num_qps;
	अगर (mthca_is_memमुक्त(to_mdev(ibdev)))
		uresp.uarc_size = to_mdev(ibdev)->uar_table.uarc_size;
	अन्यथा
		uresp.uarc_size = 0;

	err = mthca_uar_alloc(to_mdev(ibdev), &context->uar);
	अगर (err)
		वापस err;

	context->db_tab = mthca_init_user_db_tab(to_mdev(ibdev));
	अगर (IS_ERR(context->db_tab)) अणु
		err = PTR_ERR(context->db_tab);
		mthca_uar_मुक्त(to_mdev(ibdev), &context->uar);
		वापस err;
	पूर्ण

	अगर (ib_copy_to_udata(udata, &uresp, माप(uresp))) अणु
		mthca_cleanup_user_db_tab(to_mdev(ibdev), &context->uar, context->db_tab);
		mthca_uar_मुक्त(to_mdev(ibdev), &context->uar);
		वापस -EFAULT;
	पूर्ण

	context->reg_mr_warned = 0;

	वापस 0;
पूर्ण

अटल व्योम mthca_dealloc_ucontext(काष्ठा ib_ucontext *context)
अणु
	mthca_cleanup_user_db_tab(to_mdev(context->device), &to_mucontext(context)->uar,
				  to_mucontext(context)->db_tab);
	mthca_uar_मुक्त(to_mdev(context->device), &to_mucontext(context)->uar);
पूर्ण

अटल पूर्णांक mthca_mmap_uar(काष्ठा ib_ucontext *context,
			  काष्ठा vm_area_काष्ठा *vma)
अणु
	अगर (vma->vm_end - vma->vm_start != PAGE_SIZE)
		वापस -EINVAL;

	vma->vm_page_prot = pgprot_noncached(vma->vm_page_prot);

	अगर (io_remap_pfn_range(vma, vma->vm_start,
			       to_mucontext(context)->uar.pfn,
			       PAGE_SIZE, vma->vm_page_prot))
		वापस -EAGAIN;

	वापस 0;
पूर्ण

अटल पूर्णांक mthca_alloc_pd(काष्ठा ib_pd *ibpd, काष्ठा ib_udata *udata)
अणु
	काष्ठा ib_device *ibdev = ibpd->device;
	काष्ठा mthca_pd *pd = to_mpd(ibpd);
	पूर्णांक err;

	err = mthca_pd_alloc(to_mdev(ibdev), !udata, pd);
	अगर (err)
		वापस err;

	अगर (udata) अणु
		अगर (ib_copy_to_udata(udata, &pd->pd_num, माप (__u32))) अणु
			mthca_pd_मुक्त(to_mdev(ibdev), pd);
			वापस -EFAULT;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक mthca_dealloc_pd(काष्ठा ib_pd *pd, काष्ठा ib_udata *udata)
अणु
	mthca_pd_मुक्त(to_mdev(pd->device), to_mpd(pd));
	वापस 0;
पूर्ण

अटल पूर्णांक mthca_ah_create(काष्ठा ib_ah *ibah,
			   काष्ठा rdma_ah_init_attr *init_attr,
			   काष्ठा ib_udata *udata)

अणु
	काष्ठा mthca_ah *ah = to_mah(ibah);

	वापस mthca_create_ah(to_mdev(ibah->device), to_mpd(ibah->pd),
			       init_attr->ah_attr, ah);
पूर्ण

अटल पूर्णांक mthca_ah_destroy(काष्ठा ib_ah *ah, u32 flags)
अणु
	mthca_destroy_ah(to_mdev(ah->device), to_mah(ah));
	वापस 0;
पूर्ण

अटल पूर्णांक mthca_create_srq(काष्ठा ib_srq *ibsrq,
			    काष्ठा ib_srq_init_attr *init_attr,
			    काष्ठा ib_udata *udata)
अणु
	काष्ठा mthca_create_srq ucmd;
	काष्ठा mthca_ucontext *context = rdma_udata_to_drv_context(
		udata, काष्ठा mthca_ucontext, ibucontext);
	काष्ठा mthca_srq *srq = to_msrq(ibsrq);
	पूर्णांक err;

	अगर (init_attr->srq_type != IB_SRQT_BASIC)
		वापस -EOPNOTSUPP;

	अगर (udata) अणु
		अगर (ib_copy_from_udata(&ucmd, udata, माप(ucmd)))
			वापस -EFAULT;

		err = mthca_map_user_db(to_mdev(ibsrq->device), &context->uar,
					context->db_tab, ucmd.db_index,
					ucmd.db_page);

		अगर (err)
			वापस err;

		srq->mr.ibmr.lkey = ucmd.lkey;
		srq->db_index     = ucmd.db_index;
	पूर्ण

	err = mthca_alloc_srq(to_mdev(ibsrq->device), to_mpd(ibsrq->pd),
			      &init_attr->attr, srq, udata);

	अगर (err && udata)
		mthca_unmap_user_db(to_mdev(ibsrq->device), &context->uar,
				    context->db_tab, ucmd.db_index);

	अगर (err)
		वापस err;

	अगर (context && ib_copy_to_udata(udata, &srq->srqn, माप(__u32))) अणु
		mthca_मुक्त_srq(to_mdev(ibsrq->device), srq);
		वापस -EFAULT;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक mthca_destroy_srq(काष्ठा ib_srq *srq, काष्ठा ib_udata *udata)
अणु
	अगर (udata) अणु
		काष्ठा mthca_ucontext *context =
			rdma_udata_to_drv_context(
				udata,
				काष्ठा mthca_ucontext,
				ibucontext);

		mthca_unmap_user_db(to_mdev(srq->device), &context->uar,
				    context->db_tab, to_msrq(srq)->db_index);
	पूर्ण

	mthca_मुक्त_srq(to_mdev(srq->device), to_msrq(srq));
	वापस 0;
पूर्ण

अटल काष्ठा ib_qp *mthca_create_qp(काष्ठा ib_pd *pd,
				     काष्ठा ib_qp_init_attr *init_attr,
				     काष्ठा ib_udata *udata)
अणु
	काष्ठा mthca_ucontext *context = rdma_udata_to_drv_context(
		udata, काष्ठा mthca_ucontext, ibucontext);
	काष्ठा mthca_create_qp ucmd;
	काष्ठा mthca_qp *qp;
	पूर्णांक err;

	अगर (init_attr->create_flags)
		वापस ERR_PTR(-EOPNOTSUPP);

	चयन (init_attr->qp_type) अणु
	हाल IB_QPT_RC:
	हाल IB_QPT_UC:
	हाल IB_QPT_UD:
	अणु
		qp = kzalloc(माप(*qp), GFP_KERNEL);
		अगर (!qp)
			वापस ERR_PTR(-ENOMEM);

		अगर (udata) अणु
			अगर (ib_copy_from_udata(&ucmd, udata, माप ucmd)) अणु
				kमुक्त(qp);
				वापस ERR_PTR(-EFAULT);
			पूर्ण

			err = mthca_map_user_db(to_mdev(pd->device), &context->uar,
						context->db_tab,
						ucmd.sq_db_index, ucmd.sq_db_page);
			अगर (err) अणु
				kमुक्त(qp);
				वापस ERR_PTR(err);
			पूर्ण

			err = mthca_map_user_db(to_mdev(pd->device), &context->uar,
						context->db_tab,
						ucmd.rq_db_index, ucmd.rq_db_page);
			अगर (err) अणु
				mthca_unmap_user_db(to_mdev(pd->device),
						    &context->uar,
						    context->db_tab,
						    ucmd.sq_db_index);
				kमुक्त(qp);
				वापस ERR_PTR(err);
			पूर्ण

			qp->mr.ibmr.lkey = ucmd.lkey;
			qp->sq.db_index  = ucmd.sq_db_index;
			qp->rq.db_index  = ucmd.rq_db_index;
		पूर्ण

		err = mthca_alloc_qp(to_mdev(pd->device), to_mpd(pd),
				     to_mcq(init_attr->send_cq),
				     to_mcq(init_attr->recv_cq),
				     init_attr->qp_type, init_attr->sq_sig_type,
				     &init_attr->cap, qp, udata);

		अगर (err && udata) अणु
			mthca_unmap_user_db(to_mdev(pd->device),
					    &context->uar,
					    context->db_tab,
					    ucmd.sq_db_index);
			mthca_unmap_user_db(to_mdev(pd->device),
					    &context->uar,
					    context->db_tab,
					    ucmd.rq_db_index);
		पूर्ण

		qp->ibqp.qp_num = qp->qpn;
		अवरोध;
	पूर्ण
	हाल IB_QPT_SMI:
	हाल IB_QPT_GSI:
	अणु
		qp = kzalloc(माप(*qp), GFP_KERNEL);
		अगर (!qp)
			वापस ERR_PTR(-ENOMEM);
		qp->sqp = kzalloc(माप(काष्ठा mthca_sqp), GFP_KERNEL);
		अगर (!qp->sqp) अणु
			kमुक्त(qp);
			वापस ERR_PTR(-ENOMEM);
		पूर्ण

		qp->ibqp.qp_num = init_attr->qp_type == IB_QPT_SMI ? 0 : 1;

		err = mthca_alloc_sqp(to_mdev(pd->device), to_mpd(pd),
				      to_mcq(init_attr->send_cq),
				      to_mcq(init_attr->recv_cq),
				      init_attr->sq_sig_type, &init_attr->cap,
				      qp->ibqp.qp_num, init_attr->port_num,
				      qp, udata);
		अवरोध;
	पूर्ण
	शेष:
		/* Don't support raw QPs */
		वापस ERR_PTR(-EOPNOTSUPP);
	पूर्ण

	अगर (err) अणु
		kमुक्त(qp->sqp);
		kमुक्त(qp);
		वापस ERR_PTR(err);
	पूर्ण

	init_attr->cap.max_send_wr     = qp->sq.max;
	init_attr->cap.max_recv_wr     = qp->rq.max;
	init_attr->cap.max_send_sge    = qp->sq.max_gs;
	init_attr->cap.max_recv_sge    = qp->rq.max_gs;
	init_attr->cap.max_अंतरभूत_data = qp->max_अंतरभूत_data;

	वापस &qp->ibqp;
पूर्ण

अटल पूर्णांक mthca_destroy_qp(काष्ठा ib_qp *qp, काष्ठा ib_udata *udata)
अणु
	अगर (udata) अणु
		काष्ठा mthca_ucontext *context =
			rdma_udata_to_drv_context(
				udata,
				काष्ठा mthca_ucontext,
				ibucontext);

		mthca_unmap_user_db(to_mdev(qp->device),
				    &context->uar,
				    context->db_tab,
				    to_mqp(qp)->sq.db_index);
		mthca_unmap_user_db(to_mdev(qp->device),
				    &context->uar,
				    context->db_tab,
				    to_mqp(qp)->rq.db_index);
	पूर्ण
	mthca_मुक्त_qp(to_mdev(qp->device), to_mqp(qp));
	kमुक्त(to_mqp(qp)->sqp);
	kमुक्त(to_mqp(qp));
	वापस 0;
पूर्ण

अटल पूर्णांक mthca_create_cq(काष्ठा ib_cq *ibcq,
			   स्थिर काष्ठा ib_cq_init_attr *attr,
			   काष्ठा ib_udata *udata)
अणु
	काष्ठा ib_device *ibdev = ibcq->device;
	पूर्णांक entries = attr->cqe;
	काष्ठा mthca_create_cq ucmd;
	काष्ठा mthca_cq *cq;
	पूर्णांक nent;
	पूर्णांक err;
	काष्ठा mthca_ucontext *context = rdma_udata_to_drv_context(
		udata, काष्ठा mthca_ucontext, ibucontext);

	अगर (attr->flags)
		वापस -EOPNOTSUPP;

	अगर (entries < 1 || entries > to_mdev(ibdev)->limits.max_cqes)
		वापस -EINVAL;

	अगर (udata) अणु
		अगर (ib_copy_from_udata(&ucmd, udata, माप(ucmd)))
			वापस -EFAULT;

		err = mthca_map_user_db(to_mdev(ibdev), &context->uar,
					context->db_tab, ucmd.set_db_index,
					ucmd.set_db_page);
		अगर (err)
			वापस err;

		err = mthca_map_user_db(to_mdev(ibdev), &context->uar,
					context->db_tab, ucmd.arm_db_index,
					ucmd.arm_db_page);
		अगर (err)
			जाओ err_unmap_set;
	पूर्ण

	cq = to_mcq(ibcq);

	अगर (udata) अणु
		cq->buf.mr.ibmr.lkey = ucmd.lkey;
		cq->set_ci_db_index  = ucmd.set_db_index;
		cq->arm_db_index     = ucmd.arm_db_index;
	पूर्ण

	क्रम (nent = 1; nent <= entries; nent <<= 1)
		; /* nothing */

	err = mthca_init_cq(to_mdev(ibdev), nent, context,
			    udata ? ucmd.pdn : to_mdev(ibdev)->driver_pd.pd_num,
			    cq);
	अगर (err)
		जाओ err_unmap_arm;

	अगर (udata && ib_copy_to_udata(udata, &cq->cqn, माप(__u32))) अणु
		mthca_मुक्त_cq(to_mdev(ibdev), cq);
		err = -EFAULT;
		जाओ err_unmap_arm;
	पूर्ण

	cq->resize_buf = शून्य;

	वापस 0;

err_unmap_arm:
	अगर (udata)
		mthca_unmap_user_db(to_mdev(ibdev), &context->uar,
				    context->db_tab, ucmd.arm_db_index);

err_unmap_set:
	अगर (udata)
		mthca_unmap_user_db(to_mdev(ibdev), &context->uar,
				    context->db_tab, ucmd.set_db_index);

	वापस err;
पूर्ण

अटल पूर्णांक mthca_alloc_resize_buf(काष्ठा mthca_dev *dev, काष्ठा mthca_cq *cq,
				  पूर्णांक entries)
अणु
	पूर्णांक ret;

	spin_lock_irq(&cq->lock);
	अगर (cq->resize_buf) अणु
		ret = -EBUSY;
		जाओ unlock;
	पूर्ण

	cq->resize_buf = kदो_स्मृति(माप *cq->resize_buf, GFP_ATOMIC);
	अगर (!cq->resize_buf) अणु
		ret = -ENOMEM;
		जाओ unlock;
	पूर्ण

	cq->resize_buf->state = CQ_RESIZE_ALLOC;

	ret = 0;

unlock:
	spin_unlock_irq(&cq->lock);

	अगर (ret)
		वापस ret;

	ret = mthca_alloc_cq_buf(dev, &cq->resize_buf->buf, entries);
	अगर (ret) अणु
		spin_lock_irq(&cq->lock);
		kमुक्त(cq->resize_buf);
		cq->resize_buf = शून्य;
		spin_unlock_irq(&cq->lock);
		वापस ret;
	पूर्ण

	cq->resize_buf->cqe = entries - 1;

	spin_lock_irq(&cq->lock);
	cq->resize_buf->state = CQ_RESIZE_READY;
	spin_unlock_irq(&cq->lock);

	वापस 0;
पूर्ण

अटल पूर्णांक mthca_resize_cq(काष्ठा ib_cq *ibcq, पूर्णांक entries, काष्ठा ib_udata *udata)
अणु
	काष्ठा mthca_dev *dev = to_mdev(ibcq->device);
	काष्ठा mthca_cq *cq = to_mcq(ibcq);
	काष्ठा mthca_resize_cq ucmd;
	u32 lkey;
	पूर्णांक ret;

	अगर (entries < 1 || entries > dev->limits.max_cqes)
		वापस -EINVAL;

	mutex_lock(&cq->mutex);

	entries = roundup_घात_of_two(entries + 1);
	अगर (entries == ibcq->cqe + 1) अणु
		ret = 0;
		जाओ out;
	पूर्ण

	अगर (cq->is_kernel) अणु
		ret = mthca_alloc_resize_buf(dev, cq, entries);
		अगर (ret)
			जाओ out;
		lkey = cq->resize_buf->buf.mr.ibmr.lkey;
	पूर्ण अन्यथा अणु
		अगर (ib_copy_from_udata(&ucmd, udata, माप ucmd)) अणु
			ret = -EFAULT;
			जाओ out;
		पूर्ण
		lkey = ucmd.lkey;
	पूर्ण

	ret = mthca_RESIZE_CQ(dev, cq->cqn, lkey, ilog2(entries));

	अगर (ret) अणु
		अगर (cq->resize_buf) अणु
			mthca_मुक्त_cq_buf(dev, &cq->resize_buf->buf,
					  cq->resize_buf->cqe);
			kमुक्त(cq->resize_buf);
			spin_lock_irq(&cq->lock);
			cq->resize_buf = शून्य;
			spin_unlock_irq(&cq->lock);
		पूर्ण
		जाओ out;
	पूर्ण

	अगर (cq->is_kernel) अणु
		काष्ठा mthca_cq_buf tbuf;
		पूर्णांक tcqe;

		spin_lock_irq(&cq->lock);
		अगर (cq->resize_buf->state == CQ_RESIZE_READY) अणु
			mthca_cq_resize_copy_cqes(cq);
			tbuf         = cq->buf;
			tcqe         = cq->ibcq.cqe;
			cq->buf      = cq->resize_buf->buf;
			cq->ibcq.cqe = cq->resize_buf->cqe;
		पूर्ण अन्यथा अणु
			tbuf = cq->resize_buf->buf;
			tcqe = cq->resize_buf->cqe;
		पूर्ण

		kमुक्त(cq->resize_buf);
		cq->resize_buf = शून्य;
		spin_unlock_irq(&cq->lock);

		mthca_मुक्त_cq_buf(dev, &tbuf, tcqe);
	पूर्ण अन्यथा
		ibcq->cqe = entries - 1;

out:
	mutex_unlock(&cq->mutex);

	वापस ret;
पूर्ण

अटल पूर्णांक mthca_destroy_cq(काष्ठा ib_cq *cq, काष्ठा ib_udata *udata)
अणु
	अगर (udata) अणु
		काष्ठा mthca_ucontext *context =
			rdma_udata_to_drv_context(
				udata,
				काष्ठा mthca_ucontext,
				ibucontext);

		mthca_unmap_user_db(to_mdev(cq->device),
				    &context->uar,
				    context->db_tab,
				    to_mcq(cq)->arm_db_index);
		mthca_unmap_user_db(to_mdev(cq->device),
				    &context->uar,
				    context->db_tab,
				    to_mcq(cq)->set_ci_db_index);
	पूर्ण
	mthca_मुक्त_cq(to_mdev(cq->device), to_mcq(cq));
	वापस 0;
पूर्ण

अटल अंतरभूत u32 convert_access(पूर्णांक acc)
अणु
	वापस (acc & IB_ACCESS_REMOTE_ATOMIC ? MTHCA_MPT_FLAG_ATOMIC       : 0) |
	       (acc & IB_ACCESS_REMOTE_WRITE  ? MTHCA_MPT_FLAG_REMOTE_WRITE : 0) |
	       (acc & IB_ACCESS_REMOTE_READ   ? MTHCA_MPT_FLAG_REMOTE_READ  : 0) |
	       (acc & IB_ACCESS_LOCAL_WRITE   ? MTHCA_MPT_FLAG_LOCAL_WRITE  : 0) |
	       MTHCA_MPT_FLAG_LOCAL_READ;
पूर्ण

अटल काष्ठा ib_mr *mthca_get_dma_mr(काष्ठा ib_pd *pd, पूर्णांक acc)
अणु
	काष्ठा mthca_mr *mr;
	पूर्णांक err;

	mr = kदो_स्मृति(माप *mr, GFP_KERNEL);
	अगर (!mr)
		वापस ERR_PTR(-ENOMEM);

	err = mthca_mr_alloc_notrans(to_mdev(pd->device),
				     to_mpd(pd)->pd_num,
				     convert_access(acc), mr);

	अगर (err) अणु
		kमुक्त(mr);
		वापस ERR_PTR(err);
	पूर्ण

	mr->umem = शून्य;

	वापस &mr->ibmr;
पूर्ण

अटल काष्ठा ib_mr *mthca_reg_user_mr(काष्ठा ib_pd *pd, u64 start, u64 length,
				       u64 virt, पूर्णांक acc, काष्ठा ib_udata *udata)
अणु
	काष्ठा mthca_dev *dev = to_mdev(pd->device);
	काष्ठा ib_block_iter biter;
	काष्ठा mthca_ucontext *context = rdma_udata_to_drv_context(
		udata, काष्ठा mthca_ucontext, ibucontext);
	काष्ठा mthca_mr *mr;
	काष्ठा mthca_reg_mr ucmd;
	u64 *pages;
	पूर्णांक n, i;
	पूर्णांक err = 0;
	पूर्णांक ग_लिखो_mtt_size;

	अगर (udata->inlen < माप ucmd) अणु
		अगर (!context->reg_mr_warned) अणु
			mthca_warn(dev, "Process '%s' did not pass in MR attrs.\n",
				   current->comm);
			mthca_warn(dev, "  Update libmthca to fix this.\n");
		पूर्ण
		++context->reg_mr_warned;
		ucmd.mr_attrs = 0;
	पूर्ण अन्यथा अगर (ib_copy_from_udata(&ucmd, udata, माप ucmd))
		वापस ERR_PTR(-EFAULT);

	mr = kदो_स्मृति(माप *mr, GFP_KERNEL);
	अगर (!mr)
		वापस ERR_PTR(-ENOMEM);

	mr->umem = ib_umem_get(pd->device, start, length, acc);
	अगर (IS_ERR(mr->umem)) अणु
		err = PTR_ERR(mr->umem);
		जाओ err;
	पूर्ण

	n = ib_umem_num_dma_blocks(mr->umem, PAGE_SIZE);

	mr->mtt = mthca_alloc_mtt(dev, n);
	अगर (IS_ERR(mr->mtt)) अणु
		err = PTR_ERR(mr->mtt);
		जाओ err_umem;
	पूर्ण

	pages = (u64 *) __get_मुक्त_page(GFP_KERNEL);
	अगर (!pages) अणु
		err = -ENOMEM;
		जाओ err_mtt;
	पूर्ण

	i = n = 0;

	ग_लिखो_mtt_size = min(mthca_ग_लिखो_mtt_size(dev), (पूर्णांक) (PAGE_SIZE / माप *pages));

	rdma_umem_क्रम_each_dma_block(mr->umem, &biter, PAGE_SIZE) अणु
		pages[i++] = rdma_block_iter_dma_address(&biter);

		/*
		 * Be मित्रly to ग_लिखो_mtt and pass it chunks
		 * of appropriate size.
		 */
		अगर (i == ग_लिखो_mtt_size) अणु
			err = mthca_ग_लिखो_mtt(dev, mr->mtt, n, pages, i);
			अगर (err)
				जाओ mtt_करोne;
			n += i;
			i = 0;
		पूर्ण
	पूर्ण

	अगर (i)
		err = mthca_ग_लिखो_mtt(dev, mr->mtt, n, pages, i);
mtt_करोne:
	मुक्त_page((अचिन्हित दीर्घ) pages);
	अगर (err)
		जाओ err_mtt;

	err = mthca_mr_alloc(dev, to_mpd(pd)->pd_num, PAGE_SHIFT, virt, length,
			     convert_access(acc), mr);

	अगर (err)
		जाओ err_mtt;

	वापस &mr->ibmr;

err_mtt:
	mthca_मुक्त_mtt(dev, mr->mtt);

err_umem:
	ib_umem_release(mr->umem);

err:
	kमुक्त(mr);
	वापस ERR_PTR(err);
पूर्ण

अटल पूर्णांक mthca_dereg_mr(काष्ठा ib_mr *mr, काष्ठा ib_udata *udata)
अणु
	काष्ठा mthca_mr *mmr = to_mmr(mr);

	mthca_मुक्त_mr(to_mdev(mr->device), mmr);
	ib_umem_release(mmr->umem);
	kमुक्त(mmr);

	वापस 0;
पूर्ण

अटल sमाप_प्रकार hw_rev_show(काष्ठा device *device,
			   काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा mthca_dev *dev =
		rdma_device_to_drv_device(device, काष्ठा mthca_dev, ib_dev);

	वापस sysfs_emit(buf, "%x\n", dev->rev_id);
पूर्ण
अटल DEVICE_ATTR_RO(hw_rev);

अटल स्थिर अक्षर *hca_type_string(पूर्णांक hca_type)
अणु
	चयन (hca_type) अणु
	हाल PCI_DEVICE_ID_MELLANOX_TAVOR:
		वापस "MT23108";
	हाल PCI_DEVICE_ID_MELLANOX_ARBEL_COMPAT:
		वापस "MT25208 (MT23108 compat mode)";
	हाल PCI_DEVICE_ID_MELLANOX_ARBEL:
		वापस "MT25208";
	हाल PCI_DEVICE_ID_MELLANOX_SINAI:
	हाल PCI_DEVICE_ID_MELLANOX_SINAI_OLD:
		वापस "MT25204";
	पूर्ण

	वापस "unknown";
पूर्ण

अटल sमाप_प्रकार hca_type_show(काष्ठा device *device,
			     काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा mthca_dev *dev =
		rdma_device_to_drv_device(device, काष्ठा mthca_dev, ib_dev);

	वापस sysfs_emit(buf, "%s\n", hca_type_string(dev->pdev->device));
पूर्ण
अटल DEVICE_ATTR_RO(hca_type);

अटल sमाप_प्रकार board_id_show(काष्ठा device *device,
			     काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा mthca_dev *dev =
		rdma_device_to_drv_device(device, काष्ठा mthca_dev, ib_dev);

	वापस sysfs_emit(buf, "%.*s\n", MTHCA_BOARD_ID_LEN, dev->board_id);
पूर्ण
अटल DEVICE_ATTR_RO(board_id);

अटल काष्ठा attribute *mthca_dev_attributes[] = अणु
	&dev_attr_hw_rev.attr,
	&dev_attr_hca_type.attr,
	&dev_attr_board_id.attr,
	शून्य
पूर्ण;

अटल स्थिर काष्ठा attribute_group mthca_attr_group = अणु
	.attrs = mthca_dev_attributes,
पूर्ण;

अटल पूर्णांक mthca_init_node_data(काष्ठा mthca_dev *dev)
अणु
	काष्ठा ib_smp *in_mad  = शून्य;
	काष्ठा ib_smp *out_mad = शून्य;
	पूर्णांक err = -ENOMEM;

	in_mad  = kzalloc(माप *in_mad, GFP_KERNEL);
	out_mad = kदो_स्मृति(माप *out_mad, GFP_KERNEL);
	अगर (!in_mad || !out_mad)
		जाओ out;

	init_query_mad(in_mad);
	in_mad->attr_id = IB_SMP_ATTR_NODE_DESC;

	err = mthca_MAD_IFC(dev, 1, 1,
			    1, शून्य, शून्य, in_mad, out_mad);
	अगर (err)
		जाओ out;

	स_नकल(dev->ib_dev.node_desc, out_mad->data, IB_DEVICE_NODE_DESC_MAX);

	in_mad->attr_id = IB_SMP_ATTR_NODE_INFO;

	err = mthca_MAD_IFC(dev, 1, 1,
			    1, शून्य, शून्य, in_mad, out_mad);
	अगर (err)
		जाओ out;

	अगर (mthca_is_memमुक्त(dev))
		dev->rev_id = be32_to_cpup((__be32 *) (out_mad->data + 32));
	स_नकल(&dev->ib_dev.node_guid, out_mad->data + 12, 8);

out:
	kमुक्त(in_mad);
	kमुक्त(out_mad);
	वापस err;
पूर्ण

अटल पूर्णांक mthca_port_immutable(काष्ठा ib_device *ibdev, u32 port_num,
			        काष्ठा ib_port_immutable *immutable)
अणु
	काष्ठा ib_port_attr attr;
	पूर्णांक err;

	immutable->core_cap_flags = RDMA_CORE_PORT_IBA_IB;

	err = ib_query_port(ibdev, port_num, &attr);
	अगर (err)
		वापस err;

	immutable->pkey_tbl_len = attr.pkey_tbl_len;
	immutable->gid_tbl_len = attr.gid_tbl_len;
	immutable->max_mad_size = IB_MGMT_MAD_SIZE;

	वापस 0;
पूर्ण

अटल व्योम get_dev_fw_str(काष्ठा ib_device *device, अक्षर *str)
अणु
	काष्ठा mthca_dev *dev =
		container_of(device, काष्ठा mthca_dev, ib_dev);
	snम_लिखो(str, IB_FW_VERSION_NAME_MAX, "%d.%d.%d",
		 (पूर्णांक) (dev->fw_ver >> 32),
		 (पूर्णांक) (dev->fw_ver >> 16) & 0xffff,
		 (पूर्णांक) dev->fw_ver & 0xffff);
पूर्ण

अटल स्थिर काष्ठा ib_device_ops mthca_dev_ops = अणु
	.owner = THIS_MODULE,
	.driver_id = RDMA_DRIVER_MTHCA,
	.uverbs_abi_ver = MTHCA_UVERBS_ABI_VERSION,
	.uverbs_no_driver_id_binding = 1,

	.alloc_pd = mthca_alloc_pd,
	.alloc_ucontext = mthca_alloc_ucontext,
	.attach_mcast = mthca_multicast_attach,
	.create_ah = mthca_ah_create,
	.create_cq = mthca_create_cq,
	.create_qp = mthca_create_qp,
	.dealloc_pd = mthca_dealloc_pd,
	.dealloc_ucontext = mthca_dealloc_ucontext,
	.dereg_mr = mthca_dereg_mr,
	.destroy_ah = mthca_ah_destroy,
	.destroy_cq = mthca_destroy_cq,
	.destroy_qp = mthca_destroy_qp,
	.detach_mcast = mthca_multicast_detach,
	.get_dev_fw_str = get_dev_fw_str,
	.get_dma_mr = mthca_get_dma_mr,
	.get_port_immutable = mthca_port_immutable,
	.mmap = mthca_mmap_uar,
	.modअगरy_device = mthca_modअगरy_device,
	.modअगरy_port = mthca_modअगरy_port,
	.modअगरy_qp = mthca_modअगरy_qp,
	.poll_cq = mthca_poll_cq,
	.process_mad = mthca_process_mad,
	.query_ah = mthca_ah_query,
	.query_device = mthca_query_device,
	.query_gid = mthca_query_gid,
	.query_pkey = mthca_query_pkey,
	.query_port = mthca_query_port,
	.query_qp = mthca_query_qp,
	.reg_user_mr = mthca_reg_user_mr,
	.resize_cq = mthca_resize_cq,

	INIT_RDMA_OBJ_SIZE(ib_ah, mthca_ah, ibah),
	INIT_RDMA_OBJ_SIZE(ib_cq, mthca_cq, ibcq),
	INIT_RDMA_OBJ_SIZE(ib_pd, mthca_pd, ibpd),
	INIT_RDMA_OBJ_SIZE(ib_ucontext, mthca_ucontext, ibucontext),
पूर्ण;

अटल स्थिर काष्ठा ib_device_ops mthca_dev_arbel_srq_ops = अणु
	.create_srq = mthca_create_srq,
	.destroy_srq = mthca_destroy_srq,
	.modअगरy_srq = mthca_modअगरy_srq,
	.post_srq_recv = mthca_arbel_post_srq_recv,
	.query_srq = mthca_query_srq,

	INIT_RDMA_OBJ_SIZE(ib_srq, mthca_srq, ibsrq),
पूर्ण;

अटल स्थिर काष्ठा ib_device_ops mthca_dev_tavor_srq_ops = अणु
	.create_srq = mthca_create_srq,
	.destroy_srq = mthca_destroy_srq,
	.modअगरy_srq = mthca_modअगरy_srq,
	.post_srq_recv = mthca_tavor_post_srq_recv,
	.query_srq = mthca_query_srq,

	INIT_RDMA_OBJ_SIZE(ib_srq, mthca_srq, ibsrq),
पूर्ण;

अटल स्थिर काष्ठा ib_device_ops mthca_dev_arbel_ops = अणु
	.post_recv = mthca_arbel_post_receive,
	.post_send = mthca_arbel_post_send,
	.req_notअगरy_cq = mthca_arbel_arm_cq,
पूर्ण;

अटल स्थिर काष्ठा ib_device_ops mthca_dev_tavor_ops = अणु
	.post_recv = mthca_tavor_post_receive,
	.post_send = mthca_tavor_post_send,
	.req_notअगरy_cq = mthca_tavor_arm_cq,
पूर्ण;

पूर्णांक mthca_रेजिस्टर_device(काष्ठा mthca_dev *dev)
अणु
	पूर्णांक ret;

	ret = mthca_init_node_data(dev);
	अगर (ret)
		वापस ret;

	dev->ib_dev.node_type            = RDMA_NODE_IB_CA;
	dev->ib_dev.phys_port_cnt        = dev->limits.num_ports;
	dev->ib_dev.num_comp_vectors     = 1;
	dev->ib_dev.dev.parent           = &dev->pdev->dev;

	अगर (dev->mthca_flags & MTHCA_FLAG_SRQ) अणु
		अगर (mthca_is_memमुक्त(dev))
			ib_set_device_ops(&dev->ib_dev,
					  &mthca_dev_arbel_srq_ops);
		अन्यथा
			ib_set_device_ops(&dev->ib_dev,
					  &mthca_dev_tavor_srq_ops);
	पूर्ण

	ib_set_device_ops(&dev->ib_dev, &mthca_dev_ops);

	अगर (mthca_is_memमुक्त(dev))
		ib_set_device_ops(&dev->ib_dev, &mthca_dev_arbel_ops);
	अन्यथा
		ib_set_device_ops(&dev->ib_dev, &mthca_dev_tavor_ops);

	mutex_init(&dev->cap_mask_mutex);

	rdma_set_device_sysfs_group(&dev->ib_dev, &mthca_attr_group);
	ret = ib_रेजिस्टर_device(&dev->ib_dev, "mthca%d", &dev->pdev->dev);
	अगर (ret)
		वापस ret;

	mthca_start_catas_poll(dev);

	वापस 0;
पूर्ण

व्योम mthca_unरेजिस्टर_device(काष्ठा mthca_dev *dev)
अणु
	mthca_stop_catas_poll(dev);
	ib_unरेजिस्टर_device(&dev->ib_dev);
पूर्ण
