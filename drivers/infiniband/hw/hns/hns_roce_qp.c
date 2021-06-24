<शैली गुरु>
/*
 * Copyright (c) 2016 Hisilicon Limited.
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

#समावेश <linux/pci.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <rdma/ib_addr.h>
#समावेश <rdma/ib_uस्मृति.स>
#समावेश <rdma/uverbs_ioctl.h>
#समावेश "hns_roce_common.h"
#समावेश "hns_roce_device.h"
#समावेश "hns_roce_hem.h"

अटल व्योम flush_work_handle(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा hns_roce_work *flush_work = container_of(work,
					काष्ठा hns_roce_work, work);
	काष्ठा hns_roce_qp *hr_qp = container_of(flush_work,
					काष्ठा hns_roce_qp, flush_work);
	काष्ठा device *dev = flush_work->hr_dev->dev;
	काष्ठा ib_qp_attr attr;
	पूर्णांक attr_mask;
	पूर्णांक ret;

	attr_mask = IB_QP_STATE;
	attr.qp_state = IB_QPS_ERR;

	अगर (test_and_clear_bit(HNS_ROCE_FLUSH_FLAG, &hr_qp->flush_flag)) अणु
		ret = hns_roce_modअगरy_qp(&hr_qp->ibqp, &attr, attr_mask, शून्य);
		अगर (ret)
			dev_err(dev, "Modify QP to error state failed(%d) during CQE flush\n",
				ret);
	पूर्ण

	/*
	 * make sure we संकेत QP destroy leg that flush QP was completed
	 * so that it can safely proceed ahead now and destroy QP
	 */
	अगर (atomic_dec_and_test(&hr_qp->refcount))
		complete(&hr_qp->मुक्त);
पूर्ण

व्योम init_flush_work(काष्ठा hns_roce_dev *hr_dev, काष्ठा hns_roce_qp *hr_qp)
अणु
	काष्ठा hns_roce_work *flush_work = &hr_qp->flush_work;

	flush_work->hr_dev = hr_dev;
	INIT_WORK(&flush_work->work, flush_work_handle);
	atomic_inc(&hr_qp->refcount);
	queue_work(hr_dev->irq_workq, &flush_work->work);
पूर्ण

व्योम hns_roce_qp_event(काष्ठा hns_roce_dev *hr_dev, u32 qpn, पूर्णांक event_type)
अणु
	काष्ठा device *dev = hr_dev->dev;
	काष्ठा hns_roce_qp *qp;

	xa_lock(&hr_dev->qp_table_xa);
	qp = __hns_roce_qp_lookup(hr_dev, qpn);
	अगर (qp)
		atomic_inc(&qp->refcount);
	xa_unlock(&hr_dev->qp_table_xa);

	अगर (!qp) अणु
		dev_warn(dev, "Async event for bogus QP %08x\n", qpn);
		वापस;
	पूर्ण

	अगर (hr_dev->hw_rev != HNS_ROCE_HW_VER1 &&
	    (event_type == HNS_ROCE_EVENT_TYPE_WQ_CATAS_ERROR ||
	     event_type == HNS_ROCE_EVENT_TYPE_INV_REQ_LOCAL_WQ_ERROR ||
	     event_type == HNS_ROCE_EVENT_TYPE_LOCAL_WQ_ACCESS_ERROR ||
	     event_type == HNS_ROCE_EVENT_TYPE_XRCD_VIOLATION ||
	     event_type == HNS_ROCE_EVENT_TYPE_INVALID_XRCETH)) अणु
		qp->state = IB_QPS_ERR;
		अगर (!test_and_set_bit(HNS_ROCE_FLUSH_FLAG, &qp->flush_flag))
			init_flush_work(hr_dev, qp);
	पूर्ण

	qp->event(qp, (क्रमागत hns_roce_event)event_type);

	अगर (atomic_dec_and_test(&qp->refcount))
		complete(&qp->मुक्त);
पूर्ण

अटल व्योम hns_roce_ib_qp_event(काष्ठा hns_roce_qp *hr_qp,
				 क्रमागत hns_roce_event type)
अणु
	काष्ठा ib_qp *ibqp = &hr_qp->ibqp;
	काष्ठा ib_event event;

	अगर (ibqp->event_handler) अणु
		event.device = ibqp->device;
		event.element.qp = ibqp;
		चयन (type) अणु
		हाल HNS_ROCE_EVENT_TYPE_PATH_MIG:
			event.event = IB_EVENT_PATH_MIG;
			अवरोध;
		हाल HNS_ROCE_EVENT_TYPE_COMM_EST:
			event.event = IB_EVENT_COMM_EST;
			अवरोध;
		हाल HNS_ROCE_EVENT_TYPE_SQ_DRAINED:
			event.event = IB_EVENT_SQ_DRAINED;
			अवरोध;
		हाल HNS_ROCE_EVENT_TYPE_SRQ_LAST_WQE_REACH:
			event.event = IB_EVENT_QP_LAST_WQE_REACHED;
			अवरोध;
		हाल HNS_ROCE_EVENT_TYPE_WQ_CATAS_ERROR:
			event.event = IB_EVENT_QP_FATAL;
			अवरोध;
		हाल HNS_ROCE_EVENT_TYPE_PATH_MIG_FAILED:
			event.event = IB_EVENT_PATH_MIG_ERR;
			अवरोध;
		हाल HNS_ROCE_EVENT_TYPE_INV_REQ_LOCAL_WQ_ERROR:
			event.event = IB_EVENT_QP_REQ_ERR;
			अवरोध;
		हाल HNS_ROCE_EVENT_TYPE_LOCAL_WQ_ACCESS_ERROR:
		हाल HNS_ROCE_EVENT_TYPE_XRCD_VIOLATION:
		हाल HNS_ROCE_EVENT_TYPE_INVALID_XRCETH:
			event.event = IB_EVENT_QP_ACCESS_ERR;
			अवरोध;
		शेष:
			dev_dbg(ibqp->device->dev.parent, "roce_ib: Unexpected event type %d on QP %06lx\n",
				type, hr_qp->qpn);
			वापस;
		पूर्ण
		ibqp->event_handler(&event, ibqp->qp_context);
	पूर्ण
पूर्ण

अटल u8 get_least_load_bankid_क्रम_qp(काष्ठा hns_roce_bank *bank)
अणु
	u32 least_load = bank[0].inuse;
	u8 bankid = 0;
	u32 bankcnt;
	u8 i;

	क्रम (i = 1; i < HNS_ROCE_QP_BANK_NUM; i++) अणु
		bankcnt = bank[i].inuse;
		अगर (bankcnt < least_load) अणु
			least_load = bankcnt;
			bankid = i;
		पूर्ण
	पूर्ण

	वापस bankid;
पूर्ण

अटल पूर्णांक alloc_qpn_with_bankid(काष्ठा hns_roce_bank *bank, u8 bankid,
				 अचिन्हित दीर्घ *qpn)
अणु
	पूर्णांक id;

	id = ida_alloc_range(&bank->ida, bank->next, bank->max, GFP_KERNEL);
	अगर (id < 0) अणु
		id = ida_alloc_range(&bank->ida, bank->min, bank->max,
				     GFP_KERNEL);
		अगर (id < 0)
			वापस id;
	पूर्ण

	/* the QPN should keep increasing until the max value is reached. */
	bank->next = (id + 1) > bank->max ? bank->min : id + 1;

	/* the lower 3 bits is bankid */
	*qpn = (id << 3) | bankid;

	वापस 0;
पूर्ण
अटल पूर्णांक alloc_qpn(काष्ठा hns_roce_dev *hr_dev, काष्ठा hns_roce_qp *hr_qp)
अणु
	काष्ठा hns_roce_qp_table *qp_table = &hr_dev->qp_table;
	अचिन्हित दीर्घ num = 0;
	u8 bankid;
	पूर्णांक ret;

	अगर (hr_qp->ibqp.qp_type == IB_QPT_GSI) अणु
		/* when hw version is v1, the sqpn is allocated */
		अगर (hr_dev->hw_rev == HNS_ROCE_HW_VER1)
			num = HNS_ROCE_MAX_PORTS +
			      hr_dev->iboe.phy_port[hr_qp->port];
		अन्यथा
			num = 1;

		hr_qp->करोorbell_qpn = 1;
	पूर्ण अन्यथा अणु
		mutex_lock(&qp_table->bank_mutex);
		bankid = get_least_load_bankid_क्रम_qp(qp_table->bank);

		ret = alloc_qpn_with_bankid(&qp_table->bank[bankid], bankid,
					    &num);
		अगर (ret) अणु
			ibdev_err(&hr_dev->ib_dev,
				  "failed to alloc QPN, ret = %d\n", ret);
			mutex_unlock(&qp_table->bank_mutex);
			वापस ret;
		पूर्ण

		qp_table->bank[bankid].inuse++;
		mutex_unlock(&qp_table->bank_mutex);

		hr_qp->करोorbell_qpn = (u32)num;
	पूर्ण

	hr_qp->qpn = num;

	वापस 0;
पूर्ण

क्रमागत hns_roce_qp_state to_hns_roce_state(क्रमागत ib_qp_state state)
अणु
	चयन (state) अणु
	हाल IB_QPS_RESET:
		वापस HNS_ROCE_QP_STATE_RST;
	हाल IB_QPS_INIT:
		वापस HNS_ROCE_QP_STATE_INIT;
	हाल IB_QPS_RTR:
		वापस HNS_ROCE_QP_STATE_RTR;
	हाल IB_QPS_RTS:
		वापस HNS_ROCE_QP_STATE_RTS;
	हाल IB_QPS_SQD:
		वापस HNS_ROCE_QP_STATE_SQD;
	हाल IB_QPS_ERR:
		वापस HNS_ROCE_QP_STATE_ERR;
	शेष:
		वापस HNS_ROCE_QP_NUM_STATE;
	पूर्ण
पूर्ण

अटल व्योम add_qp_to_list(काष्ठा hns_roce_dev *hr_dev,
			   काष्ठा hns_roce_qp *hr_qp,
			   काष्ठा ib_cq *send_cq, काष्ठा ib_cq *recv_cq)
अणु
	काष्ठा hns_roce_cq *hr_send_cq, *hr_recv_cq;
	अचिन्हित दीर्घ flags;

	hr_send_cq = send_cq ? to_hr_cq(send_cq) : शून्य;
	hr_recv_cq = recv_cq ? to_hr_cq(recv_cq) : शून्य;

	spin_lock_irqsave(&hr_dev->qp_list_lock, flags);
	hns_roce_lock_cqs(hr_send_cq, hr_recv_cq);

	list_add_tail(&hr_qp->node, &hr_dev->qp_list);
	अगर (hr_send_cq)
		list_add_tail(&hr_qp->sq_node, &hr_send_cq->sq_list);
	अगर (hr_recv_cq)
		list_add_tail(&hr_qp->rq_node, &hr_recv_cq->rq_list);

	hns_roce_unlock_cqs(hr_send_cq, hr_recv_cq);
	spin_unlock_irqrestore(&hr_dev->qp_list_lock, flags);
पूर्ण

अटल पूर्णांक hns_roce_qp_store(काष्ठा hns_roce_dev *hr_dev,
			     काष्ठा hns_roce_qp *hr_qp,
			     काष्ठा ib_qp_init_attr *init_attr)
अणु
	काष्ठा xarray *xa = &hr_dev->qp_table_xa;
	पूर्णांक ret;

	अगर (!hr_qp->qpn)
		वापस -EINVAL;

	ret = xa_err(xa_store_irq(xa, hr_qp->qpn, hr_qp, GFP_KERNEL));
	अगर (ret)
		dev_err(hr_dev->dev, "Failed to xa store for QPC\n");
	अन्यथा
		/* add QP to device's QP list क्रम softwc */
		add_qp_to_list(hr_dev, hr_qp, init_attr->send_cq,
			       init_attr->recv_cq);

	वापस ret;
पूर्ण

अटल पूर्णांक alloc_qpc(काष्ठा hns_roce_dev *hr_dev, काष्ठा hns_roce_qp *hr_qp)
अणु
	काष्ठा hns_roce_qp_table *qp_table = &hr_dev->qp_table;
	काष्ठा device *dev = hr_dev->dev;
	पूर्णांक ret;

	अगर (!hr_qp->qpn)
		वापस -EINVAL;

	/* In v1 engine, GSI QP context is saved in the RoCE hw's रेजिस्टर */
	अगर (hr_qp->ibqp.qp_type == IB_QPT_GSI &&
	    hr_dev->hw_rev == HNS_ROCE_HW_VER1)
		वापस 0;

	/* Alloc memory क्रम QPC */
	ret = hns_roce_table_get(hr_dev, &qp_table->qp_table, hr_qp->qpn);
	अगर (ret) अणु
		dev_err(dev, "Failed to get QPC table\n");
		जाओ err_out;
	पूर्ण

	/* Alloc memory क्रम IRRL */
	ret = hns_roce_table_get(hr_dev, &qp_table->irrl_table, hr_qp->qpn);
	अगर (ret) अणु
		dev_err(dev, "Failed to get IRRL table\n");
		जाओ err_put_qp;
	पूर्ण

	अगर (hr_dev->caps.trrl_entry_sz) अणु
		/* Alloc memory क्रम TRRL */
		ret = hns_roce_table_get(hr_dev, &qp_table->trrl_table,
					 hr_qp->qpn);
		अगर (ret) अणु
			dev_err(dev, "Failed to get TRRL table\n");
			जाओ err_put_irrl;
		पूर्ण
	पूर्ण

	अगर (hr_dev->caps.flags & HNS_ROCE_CAP_FLAG_QP_FLOW_CTRL) अणु
		/* Alloc memory क्रम SCC CTX */
		ret = hns_roce_table_get(hr_dev, &qp_table->sccc_table,
					 hr_qp->qpn);
		अगर (ret) अणु
			dev_err(dev, "Failed to get SCC CTX table\n");
			जाओ err_put_trrl;
		पूर्ण
	पूर्ण

	वापस 0;

err_put_trrl:
	अगर (hr_dev->caps.trrl_entry_sz)
		hns_roce_table_put(hr_dev, &qp_table->trrl_table, hr_qp->qpn);

err_put_irrl:
	hns_roce_table_put(hr_dev, &qp_table->irrl_table, hr_qp->qpn);

err_put_qp:
	hns_roce_table_put(hr_dev, &qp_table->qp_table, hr_qp->qpn);

err_out:
	वापस ret;
पूर्ण

व्योम hns_roce_qp_हटाओ(काष्ठा hns_roce_dev *hr_dev, काष्ठा hns_roce_qp *hr_qp)
अणु
	काष्ठा xarray *xa = &hr_dev->qp_table_xa;
	अचिन्हित दीर्घ flags;

	list_del(&hr_qp->node);

	अगर (hr_qp->ibqp.qp_type != IB_QPT_XRC_TGT)
		list_del(&hr_qp->sq_node);

	अगर (hr_qp->ibqp.qp_type != IB_QPT_XRC_INI &&
	    hr_qp->ibqp.qp_type != IB_QPT_XRC_TGT)
		list_del(&hr_qp->rq_node);

	xa_lock_irqsave(xa, flags);
	__xa_erase(xa, hr_qp->qpn & (hr_dev->caps.num_qps - 1));
	xa_unlock_irqrestore(xa, flags);
पूर्ण

अटल व्योम मुक्त_qpc(काष्ठा hns_roce_dev *hr_dev, काष्ठा hns_roce_qp *hr_qp)
अणु
	काष्ठा hns_roce_qp_table *qp_table = &hr_dev->qp_table;

	/* In v1 engine, GSI QP context is saved in the RoCE hw's रेजिस्टर */
	अगर (hr_qp->ibqp.qp_type == IB_QPT_GSI &&
	    hr_dev->hw_rev == HNS_ROCE_HW_VER1)
		वापस;

	अगर (hr_dev->caps.trrl_entry_sz)
		hns_roce_table_put(hr_dev, &qp_table->trrl_table, hr_qp->qpn);
	hns_roce_table_put(hr_dev, &qp_table->irrl_table, hr_qp->qpn);
पूर्ण

अटल अंतरभूत u8 get_qp_bankid(अचिन्हित दीर्घ qpn)
अणु
	/* The lower 3 bits of QPN are used to hash to dअगरferent banks */
	वापस (u8)(qpn & GENMASK(2, 0));
पूर्ण

अटल व्योम मुक्त_qpn(काष्ठा hns_roce_dev *hr_dev, काष्ठा hns_roce_qp *hr_qp)
अणु
	u8 bankid;

	अगर (hr_qp->ibqp.qp_type == IB_QPT_GSI)
		वापस;

	अगर (hr_qp->qpn < hr_dev->caps.reserved_qps)
		वापस;

	bankid = get_qp_bankid(hr_qp->qpn);

	ida_मुक्त(&hr_dev->qp_table.bank[bankid].ida, hr_qp->qpn >> 3);

	mutex_lock(&hr_dev->qp_table.bank_mutex);
	hr_dev->qp_table.bank[bankid].inuse--;
	mutex_unlock(&hr_dev->qp_table.bank_mutex);
पूर्ण

अटल u32 proc_rq_sge(काष्ठा hns_roce_dev *dev, काष्ठा hns_roce_qp *hr_qp,
		       bool user)
अणु
	u32 max_sge = dev->caps.max_rq_sg;

	अगर (dev->pci_dev->revision >= PCI_REVISION_ID_HIP09)
		वापस max_sge;

	/* Reserve SGEs only क्रम HIP08 in kernel; The userspace driver will
	 * calculate number of max_sge with reserved SGEs when allocating wqe
	 * buf, so there is no need to करो this again in kernel. But the number
	 * may exceed the capacity of SGEs recorded in the firmware, so the
	 * kernel driver should just adapt the value accordingly.
	 */
	अगर (user)
		max_sge = roundup_घात_of_two(max_sge + 1);
	अन्यथा
		hr_qp->rq.rsv_sge = 1;

	वापस max_sge;
पूर्ण

अटल पूर्णांक set_rq_size(काष्ठा hns_roce_dev *hr_dev, काष्ठा ib_qp_cap *cap,
		       काष्ठा hns_roce_qp *hr_qp, पूर्णांक has_rq, bool user)
अणु
	u32 max_sge = proc_rq_sge(hr_dev, hr_qp, user);
	u32 cnt;

	/* If srq exist, set zero क्रम relative number of rq */
	अगर (!has_rq) अणु
		hr_qp->rq.wqe_cnt = 0;
		hr_qp->rq.max_gs = 0;
		hr_qp->rq_inl_buf.wqe_cnt = 0;
		cap->max_recv_wr = 0;
		cap->max_recv_sge = 0;

		वापस 0;
	पूर्ण

	/* Check the validity of QP support capacity */
	अगर (!cap->max_recv_wr || cap->max_recv_wr > hr_dev->caps.max_wqes ||
	    cap->max_recv_sge > max_sge) अणु
		ibdev_err(&hr_dev->ib_dev,
			  "RQ config error, depth = %u, sge = %u\n",
			  cap->max_recv_wr, cap->max_recv_sge);
		वापस -EINVAL;
	पूर्ण

	cnt = roundup_घात_of_two(max(cap->max_recv_wr, hr_dev->caps.min_wqes));
	अगर (cnt > hr_dev->caps.max_wqes) अणु
		ibdev_err(&hr_dev->ib_dev, "rq depth %u too large\n",
			  cap->max_recv_wr);
		वापस -EINVAL;
	पूर्ण

	hr_qp->rq.max_gs = roundup_घात_of_two(max(1U, cap->max_recv_sge) +
					      hr_qp->rq.rsv_sge);

	अगर (hr_dev->caps.max_rq_sg <= HNS_ROCE_SGE_IN_WQE)
		hr_qp->rq.wqe_shअगरt = ilog2(hr_dev->caps.max_rq_desc_sz);
	अन्यथा
		hr_qp->rq.wqe_shअगरt = ilog2(hr_dev->caps.max_rq_desc_sz *
					    hr_qp->rq.max_gs);

	hr_qp->rq.wqe_cnt = cnt;
	अगर (hr_dev->caps.flags & HNS_ROCE_CAP_FLAG_RQ_INLINE &&
	    hr_qp->ibqp.qp_type != IB_QPT_UD &&
	    hr_qp->ibqp.qp_type != IB_QPT_GSI)
		hr_qp->rq_inl_buf.wqe_cnt = cnt;
	अन्यथा
		hr_qp->rq_inl_buf.wqe_cnt = 0;

	cap->max_recv_wr = cnt;
	cap->max_recv_sge = hr_qp->rq.max_gs - hr_qp->rq.rsv_sge;

	वापस 0;
पूर्ण

अटल u32 get_wqe_ext_sge_cnt(काष्ठा hns_roce_qp *qp)
अणु
	/* GSI/UD QP only has extended sge */
	अगर (qp->ibqp.qp_type == IB_QPT_GSI || qp->ibqp.qp_type == IB_QPT_UD)
		वापस qp->sq.max_gs;

	अगर (qp->sq.max_gs > HNS_ROCE_SGE_IN_WQE)
		वापस qp->sq.max_gs - HNS_ROCE_SGE_IN_WQE;

	वापस 0;
पूर्ण

अटल व्योम set_ext_sge_param(काष्ठा hns_roce_dev *hr_dev, u32 sq_wqe_cnt,
			      काष्ठा hns_roce_qp *hr_qp, काष्ठा ib_qp_cap *cap)
अणु
	u32 total_sge_cnt;
	u32 wqe_sge_cnt;

	hr_qp->sge.sge_shअगरt = HNS_ROCE_SGE_SHIFT;

	अगर (hr_dev->hw_rev == HNS_ROCE_HW_VER1) अणु
		hr_qp->sq.max_gs = HNS_ROCE_SGE_IN_WQE;
		वापस;
	पूर्ण

	hr_qp->sq.max_gs = max(1U, cap->max_send_sge);

	wqe_sge_cnt = get_wqe_ext_sge_cnt(hr_qp);

	/* If the number of extended sge is not zero, they MUST use the
	 * space of HNS_HW_PAGE_SIZE at least.
	 */
	अगर (wqe_sge_cnt) अणु
		total_sge_cnt = roundup_घात_of_two(sq_wqe_cnt * wqe_sge_cnt);
		hr_qp->sge.sge_cnt = max(total_sge_cnt,
				(u32)HNS_HW_PAGE_SIZE / HNS_ROCE_SGE_SIZE);
	पूर्ण
पूर्ण

अटल पूर्णांक check_sq_size_with_पूर्णांकegrity(काष्ठा hns_roce_dev *hr_dev,
					काष्ठा ib_qp_cap *cap,
					काष्ठा hns_roce_ib_create_qp *ucmd)
अणु
	u32 roundup_sq_stride = roundup_घात_of_two(hr_dev->caps.max_sq_desc_sz);
	u8 max_sq_stride = ilog2(roundup_sq_stride);

	/* Sanity check SQ size beक्रमe proceeding */
	अगर (ucmd->log_sq_stride > max_sq_stride ||
	    ucmd->log_sq_stride < HNS_ROCE_IB_MIN_SQ_STRIDE) अणु
		ibdev_err(&hr_dev->ib_dev, "failed to check SQ stride size.\n");
		वापस -EINVAL;
	पूर्ण

	अगर (cap->max_send_sge > hr_dev->caps.max_sq_sg) अणु
		ibdev_err(&hr_dev->ib_dev, "failed to check SQ SGE size %u.\n",
			  cap->max_send_sge);
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक set_user_sq_size(काष्ठा hns_roce_dev *hr_dev,
			    काष्ठा ib_qp_cap *cap, काष्ठा hns_roce_qp *hr_qp,
			    काष्ठा hns_roce_ib_create_qp *ucmd)
अणु
	काष्ठा ib_device *ibdev = &hr_dev->ib_dev;
	u32 cnt = 0;
	पूर्णांक ret;

	अगर (check_shl_overflow(1, ucmd->log_sq_bb_count, &cnt) ||
	    cnt > hr_dev->caps.max_wqes)
		वापस -EINVAL;

	ret = check_sq_size_with_पूर्णांकegrity(hr_dev, cap, ucmd);
	अगर (ret) अणु
		ibdev_err(ibdev, "failed to check user SQ size, ret = %d.\n",
			  ret);
		वापस ret;
	पूर्ण

	set_ext_sge_param(hr_dev, cnt, hr_qp, cap);

	hr_qp->sq.wqe_shअगरt = ucmd->log_sq_stride;
	hr_qp->sq.wqe_cnt = cnt;

	वापस 0;
पूर्ण

अटल पूर्णांक set_wqe_buf_attr(काष्ठा hns_roce_dev *hr_dev,
			    काष्ठा hns_roce_qp *hr_qp,
			    काष्ठा hns_roce_buf_attr *buf_attr)
अणु
	पूर्णांक buf_size;
	पूर्णांक idx = 0;

	hr_qp->buff_size = 0;

	/* SQ WQE */
	hr_qp->sq.offset = 0;
	buf_size = to_hr_hem_entries_size(hr_qp->sq.wqe_cnt,
					  hr_qp->sq.wqe_shअगरt);
	अगर (buf_size > 0 && idx < ARRAY_SIZE(buf_attr->region)) अणु
		buf_attr->region[idx].size = buf_size;
		buf_attr->region[idx].hopnum = hr_dev->caps.wqe_sq_hop_num;
		idx++;
		hr_qp->buff_size += buf_size;
	पूर्ण

	/* extend SGE WQE in SQ */
	hr_qp->sge.offset = hr_qp->buff_size;
	buf_size = to_hr_hem_entries_size(hr_qp->sge.sge_cnt,
					  hr_qp->sge.sge_shअगरt);
	अगर (buf_size > 0 && idx < ARRAY_SIZE(buf_attr->region)) अणु
		buf_attr->region[idx].size = buf_size;
		buf_attr->region[idx].hopnum = hr_dev->caps.wqe_sge_hop_num;
		idx++;
		hr_qp->buff_size += buf_size;
	पूर्ण

	/* RQ WQE */
	hr_qp->rq.offset = hr_qp->buff_size;
	buf_size = to_hr_hem_entries_size(hr_qp->rq.wqe_cnt,
					  hr_qp->rq.wqe_shअगरt);
	अगर (buf_size > 0 && idx < ARRAY_SIZE(buf_attr->region)) अणु
		buf_attr->region[idx].size = buf_size;
		buf_attr->region[idx].hopnum = hr_dev->caps.wqe_rq_hop_num;
		idx++;
		hr_qp->buff_size += buf_size;
	पूर्ण

	अगर (hr_qp->buff_size < 1)
		वापस -EINVAL;

	buf_attr->page_shअगरt = HNS_HW_PAGE_SHIFT + hr_dev->caps.mtt_buf_pg_sz;
	buf_attr->region_count = idx;

	वापस 0;
पूर्ण

अटल पूर्णांक set_kernel_sq_size(काष्ठा hns_roce_dev *hr_dev,
			      काष्ठा ib_qp_cap *cap, काष्ठा hns_roce_qp *hr_qp)
अणु
	काष्ठा ib_device *ibdev = &hr_dev->ib_dev;
	u32 cnt;

	अगर (!cap->max_send_wr || cap->max_send_wr > hr_dev->caps.max_wqes ||
	    cap->max_send_sge > hr_dev->caps.max_sq_sg) अणु
		ibdev_err(ibdev,
			  "failed to check SQ WR or SGE num, ret = %d.\n",
			  -EINVAL);
		वापस -EINVAL;
	पूर्ण

	cnt = roundup_घात_of_two(max(cap->max_send_wr, hr_dev->caps.min_wqes));
	अगर (cnt > hr_dev->caps.max_wqes) अणु
		ibdev_err(ibdev, "failed to check WQE num, WQE num = %u.\n",
			  cnt);
		वापस -EINVAL;
	पूर्ण

	hr_qp->sq.wqe_shअगरt = ilog2(hr_dev->caps.max_sq_desc_sz);
	hr_qp->sq.wqe_cnt = cnt;

	set_ext_sge_param(hr_dev, cnt, hr_qp, cap);

	/* sync the parameters of kernel QP to user's configuration */
	cap->max_send_wr = cnt;
	cap->max_send_sge = hr_qp->sq.max_gs;

	वापस 0;
पूर्ण

अटल पूर्णांक hns_roce_qp_has_sq(काष्ठा ib_qp_init_attr *attr)
अणु
	अगर (attr->qp_type == IB_QPT_XRC_TGT || !attr->cap.max_send_wr)
		वापस 0;

	वापस 1;
पूर्ण

अटल पूर्णांक hns_roce_qp_has_rq(काष्ठा ib_qp_init_attr *attr)
अणु
	अगर (attr->qp_type == IB_QPT_XRC_INI ||
	    attr->qp_type == IB_QPT_XRC_TGT || attr->srq ||
	    !attr->cap.max_recv_wr)
		वापस 0;

	वापस 1;
पूर्ण

अटल पूर्णांक alloc_rq_अंतरभूत_buf(काष्ठा hns_roce_qp *hr_qp,
			       काष्ठा ib_qp_init_attr *init_attr)
अणु
	u32 max_recv_sge = init_attr->cap.max_recv_sge;
	u32 wqe_cnt = hr_qp->rq_inl_buf.wqe_cnt;
	काष्ठा hns_roce_rinl_wqe *wqe_list;
	पूर्णांक i;

	/* allocate recv अंतरभूत buf */
	wqe_list = kसुस्मृति(wqe_cnt, माप(काष्ठा hns_roce_rinl_wqe),
			   GFP_KERNEL);

	अगर (!wqe_list)
		जाओ err;

	/* Allocate a continuous buffer क्रम all अंतरभूत sge we need */
	wqe_list[0].sg_list = kसुस्मृति(wqe_cnt, (max_recv_sge *
				      माप(काष्ठा hns_roce_rinl_sge)),
				      GFP_KERNEL);
	अगर (!wqe_list[0].sg_list)
		जाओ err_wqe_list;

	/* Assign buffers of sg_list to each अंतरभूत wqe */
	क्रम (i = 1; i < wqe_cnt; i++)
		wqe_list[i].sg_list = &wqe_list[0].sg_list[i * max_recv_sge];

	hr_qp->rq_inl_buf.wqe_list = wqe_list;

	वापस 0;

err_wqe_list:
	kमुक्त(wqe_list);

err:
	वापस -ENOMEM;
पूर्ण

अटल व्योम मुक्त_rq_अंतरभूत_buf(काष्ठा hns_roce_qp *hr_qp)
अणु
	अगर (hr_qp->rq_inl_buf.wqe_list)
		kमुक्त(hr_qp->rq_inl_buf.wqe_list[0].sg_list);
	kमुक्त(hr_qp->rq_inl_buf.wqe_list);
पूर्ण

अटल पूर्णांक alloc_qp_buf(काष्ठा hns_roce_dev *hr_dev, काष्ठा hns_roce_qp *hr_qp,
			काष्ठा ib_qp_init_attr *init_attr,
			काष्ठा ib_udata *udata, अचिन्हित दीर्घ addr)
अणु
	काष्ठा ib_device *ibdev = &hr_dev->ib_dev;
	काष्ठा hns_roce_buf_attr buf_attr = अणुपूर्ण;
	पूर्णांक ret;

	अगर (!udata && hr_qp->rq_inl_buf.wqe_cnt) अणु
		ret = alloc_rq_अंतरभूत_buf(hr_qp, init_attr);
		अगर (ret) अणु
			ibdev_err(ibdev,
				  "failed to alloc inline buf, ret = %d.\n",
				  ret);
			वापस ret;
		पूर्ण
	पूर्ण अन्यथा अणु
		hr_qp->rq_inl_buf.wqe_list = शून्य;
	पूर्ण

	ret = set_wqe_buf_attr(hr_dev, hr_qp, &buf_attr);
	अगर (ret) अणु
		ibdev_err(ibdev, "failed to split WQE buf, ret = %d.\n", ret);
		जाओ err_अंतरभूत;
	पूर्ण
	ret = hns_roce_mtr_create(hr_dev, &hr_qp->mtr, &buf_attr,
				  HNS_HW_PAGE_SHIFT + hr_dev->caps.mtt_ba_pg_sz,
				  udata, addr);
	अगर (ret) अणु
		ibdev_err(ibdev, "failed to create WQE mtr, ret = %d.\n", ret);
		जाओ err_अंतरभूत;
	पूर्ण

	वापस 0;
err_अंतरभूत:
	मुक्त_rq_अंतरभूत_buf(hr_qp);

	वापस ret;
पूर्ण

अटल व्योम मुक्त_qp_buf(काष्ठा hns_roce_dev *hr_dev, काष्ठा hns_roce_qp *hr_qp)
अणु
	hns_roce_mtr_destroy(hr_dev, &hr_qp->mtr);
	मुक्त_rq_अंतरभूत_buf(hr_qp);
पूर्ण

अटल अंतरभूत bool user_qp_has_sdb(काष्ठा hns_roce_dev *hr_dev,
				   काष्ठा ib_qp_init_attr *init_attr,
				   काष्ठा ib_udata *udata,
				   काष्ठा hns_roce_ib_create_qp_resp *resp,
				   काष्ठा hns_roce_ib_create_qp *ucmd)
अणु
	वापस ((hr_dev->caps.flags & HNS_ROCE_CAP_FLAG_QP_RECORD_DB) &&
		udata->outlen >= दुरत्वend(typeof(*resp), cap_flags) &&
		hns_roce_qp_has_sq(init_attr) &&
		udata->inlen >= दुरत्वend(typeof(*ucmd), sdb_addr));
पूर्ण

अटल अंतरभूत bool user_qp_has_rdb(काष्ठा hns_roce_dev *hr_dev,
				   काष्ठा ib_qp_init_attr *init_attr,
				   काष्ठा ib_udata *udata,
				   काष्ठा hns_roce_ib_create_qp_resp *resp)
अणु
	वापस ((hr_dev->caps.flags & HNS_ROCE_CAP_FLAG_QP_RECORD_DB) &&
		udata->outlen >= दुरत्वend(typeof(*resp), cap_flags) &&
		hns_roce_qp_has_rq(init_attr));
पूर्ण

अटल अंतरभूत bool kernel_qp_has_rdb(काष्ठा hns_roce_dev *hr_dev,
				     काष्ठा ib_qp_init_attr *init_attr)
अणु
	वापस ((hr_dev->caps.flags & HNS_ROCE_CAP_FLAG_QP_RECORD_DB) &&
		hns_roce_qp_has_rq(init_attr));
पूर्ण

अटल पूर्णांक alloc_qp_db(काष्ठा hns_roce_dev *hr_dev, काष्ठा hns_roce_qp *hr_qp,
		       काष्ठा ib_qp_init_attr *init_attr,
		       काष्ठा ib_udata *udata,
		       काष्ठा hns_roce_ib_create_qp *ucmd,
		       काष्ठा hns_roce_ib_create_qp_resp *resp)
अणु
	काष्ठा hns_roce_ucontext *uctx = rdma_udata_to_drv_context(
		udata, काष्ठा hns_roce_ucontext, ibucontext);
	काष्ठा ib_device *ibdev = &hr_dev->ib_dev;
	पूर्णांक ret;

	अगर (hr_dev->caps.flags & HNS_ROCE_CAP_FLAG_SDI_MODE)
		hr_qp->en_flags |= HNS_ROCE_QP_CAP_OWNER_DB;

	अगर (udata) अणु
		अगर (user_qp_has_sdb(hr_dev, init_attr, udata, resp, ucmd)) अणु
			ret = hns_roce_db_map_user(uctx, udata, ucmd->sdb_addr,
						   &hr_qp->sdb);
			अगर (ret) अणु
				ibdev_err(ibdev,
					  "failed to map user SQ doorbell, ret = %d.\n",
					  ret);
				जाओ err_out;
			पूर्ण
			hr_qp->en_flags |= HNS_ROCE_QP_CAP_SQ_RECORD_DB;
			resp->cap_flags |= HNS_ROCE_QP_CAP_SQ_RECORD_DB;
		पूर्ण

		अगर (user_qp_has_rdb(hr_dev, init_attr, udata, resp)) अणु
			ret = hns_roce_db_map_user(uctx, udata, ucmd->db_addr,
						   &hr_qp->rdb);
			अगर (ret) अणु
				ibdev_err(ibdev,
					  "failed to map user RQ doorbell, ret = %d.\n",
					  ret);
				जाओ err_sdb;
			पूर्ण
			hr_qp->en_flags |= HNS_ROCE_QP_CAP_RQ_RECORD_DB;
			resp->cap_flags |= HNS_ROCE_QP_CAP_RQ_RECORD_DB;
		पूर्ण
	पूर्ण अन्यथा अणु
		अगर (hr_dev->pci_dev->revision >= PCI_REVISION_ID_HIP09)
			hr_qp->sq.db_reg = hr_dev->mem_base +
					   HNS_ROCE_DWQE_SIZE * hr_qp->qpn;
		अन्यथा
			hr_qp->sq.db_reg =
				hr_dev->reg_base + hr_dev->sdb_offset +
				DB_REG_OFFSET * hr_dev->priv_uar.index;

		hr_qp->rq.db_reg = hr_dev->reg_base + hr_dev->odb_offset +
				   DB_REG_OFFSET * hr_dev->priv_uar.index;

		अगर (kernel_qp_has_rdb(hr_dev, init_attr)) अणु
			ret = hns_roce_alloc_db(hr_dev, &hr_qp->rdb, 0);
			अगर (ret) अणु
				ibdev_err(ibdev,
					  "failed to alloc kernel RQ doorbell, ret = %d.\n",
					  ret);
				जाओ err_out;
			पूर्ण
			*hr_qp->rdb.db_record = 0;
			hr_qp->en_flags |= HNS_ROCE_QP_CAP_RQ_RECORD_DB;
		पूर्ण
	पूर्ण

	वापस 0;
err_sdb:
	अगर (udata && hr_qp->en_flags & HNS_ROCE_QP_CAP_SQ_RECORD_DB)
		hns_roce_db_unmap_user(uctx, &hr_qp->sdb);
err_out:
	वापस ret;
पूर्ण

अटल व्योम मुक्त_qp_db(काष्ठा hns_roce_dev *hr_dev, काष्ठा hns_roce_qp *hr_qp,
		       काष्ठा ib_udata *udata)
अणु
	काष्ठा hns_roce_ucontext *uctx = rdma_udata_to_drv_context(
		udata, काष्ठा hns_roce_ucontext, ibucontext);

	अगर (udata) अणु
		अगर (hr_qp->en_flags & HNS_ROCE_QP_CAP_RQ_RECORD_DB)
			hns_roce_db_unmap_user(uctx, &hr_qp->rdb);
		अगर (hr_qp->en_flags & HNS_ROCE_QP_CAP_SQ_RECORD_DB)
			hns_roce_db_unmap_user(uctx, &hr_qp->sdb);
	पूर्ण अन्यथा अणु
		अगर (hr_qp->en_flags & HNS_ROCE_QP_CAP_RQ_RECORD_DB)
			hns_roce_मुक्त_db(hr_dev, &hr_qp->rdb);
	पूर्ण
पूर्ण

अटल पूर्णांक alloc_kernel_wrid(काष्ठा hns_roce_dev *hr_dev,
			     काष्ठा hns_roce_qp *hr_qp)
अणु
	काष्ठा ib_device *ibdev = &hr_dev->ib_dev;
	u64 *sq_wrid = शून्य;
	u64 *rq_wrid = शून्य;
	पूर्णांक ret;

	sq_wrid = kसुस्मृति(hr_qp->sq.wqe_cnt, माप(u64), GFP_KERNEL);
	अगर (ZERO_OR_शून्य_PTR(sq_wrid)) अणु
		ibdev_err(ibdev, "failed to alloc SQ wrid.\n");
		वापस -ENOMEM;
	पूर्ण

	अगर (hr_qp->rq.wqe_cnt) अणु
		rq_wrid = kसुस्मृति(hr_qp->rq.wqe_cnt, माप(u64), GFP_KERNEL);
		अगर (ZERO_OR_शून्य_PTR(rq_wrid)) अणु
			ibdev_err(ibdev, "failed to alloc RQ wrid.\n");
			ret = -ENOMEM;
			जाओ err_sq;
		पूर्ण
	पूर्ण

	hr_qp->sq.wrid = sq_wrid;
	hr_qp->rq.wrid = rq_wrid;
	वापस 0;
err_sq:
	kमुक्त(sq_wrid);

	वापस ret;
पूर्ण

अटल व्योम मुक्त_kernel_wrid(काष्ठा hns_roce_qp *hr_qp)
अणु
	kमुक्त(hr_qp->rq.wrid);
	kमुक्त(hr_qp->sq.wrid);
पूर्ण

अटल पूर्णांक set_qp_param(काष्ठा hns_roce_dev *hr_dev, काष्ठा hns_roce_qp *hr_qp,
			काष्ठा ib_qp_init_attr *init_attr,
			काष्ठा ib_udata *udata,
			काष्ठा hns_roce_ib_create_qp *ucmd)
अणु
	काष्ठा ib_device *ibdev = &hr_dev->ib_dev;
	पूर्णांक ret;

	hr_qp->ibqp.qp_type = init_attr->qp_type;

	अगर (init_attr->cap.max_अंतरभूत_data > hr_dev->caps.max_sq_अंतरभूत)
		init_attr->cap.max_अंतरभूत_data = hr_dev->caps.max_sq_अंतरभूत;

	hr_qp->max_अंतरभूत_data = init_attr->cap.max_अंतरभूत_data;

	अगर (init_attr->sq_sig_type == IB_SIGNAL_ALL_WR)
		hr_qp->sq_संकेत_bits = IB_SIGNAL_ALL_WR;
	अन्यथा
		hr_qp->sq_संकेत_bits = IB_SIGNAL_REQ_WR;

	ret = set_rq_size(hr_dev, &init_attr->cap, hr_qp,
			  hns_roce_qp_has_rq(init_attr), !!udata);
	अगर (ret) अणु
		ibdev_err(ibdev, "failed to set user RQ size, ret = %d.\n",
			  ret);
		वापस ret;
	पूर्ण

	अगर (udata) अणु
		ret = ib_copy_from_udata(ucmd, udata,
					 min(udata->inlen, माप(*ucmd)));
		अगर (ret) अणु
			ibdev_err(ibdev,
				  "failed to copy QP ucmd, ret = %d\n", ret);
			वापस ret;
		पूर्ण

		ret = set_user_sq_size(hr_dev, &init_attr->cap, hr_qp, ucmd);
		अगर (ret)
			ibdev_err(ibdev,
				  "failed to set user SQ size, ret = %d.\n",
				  ret);
	पूर्ण अन्यथा अणु
		ret = set_kernel_sq_size(hr_dev, &init_attr->cap, hr_qp);
		अगर (ret)
			ibdev_err(ibdev,
				  "failed to set kernel SQ size, ret = %d.\n",
				  ret);
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक hns_roce_create_qp_common(काष्ठा hns_roce_dev *hr_dev,
				     काष्ठा ib_pd *ib_pd,
				     काष्ठा ib_qp_init_attr *init_attr,
				     काष्ठा ib_udata *udata,
				     काष्ठा hns_roce_qp *hr_qp)
अणु
	काष्ठा hns_roce_ib_create_qp_resp resp = अणुपूर्ण;
	काष्ठा ib_device *ibdev = &hr_dev->ib_dev;
	काष्ठा hns_roce_ib_create_qp ucmd;
	पूर्णांक ret;

	mutex_init(&hr_qp->mutex);
	spin_lock_init(&hr_qp->sq.lock);
	spin_lock_init(&hr_qp->rq.lock);

	hr_qp->state = IB_QPS_RESET;
	hr_qp->flush_flag = 0;

	अगर (init_attr->create_flags)
		वापस -EOPNOTSUPP;

	ret = set_qp_param(hr_dev, hr_qp, init_attr, udata, &ucmd);
	अगर (ret) अणु
		ibdev_err(ibdev, "failed to set QP param, ret = %d.\n", ret);
		वापस ret;
	पूर्ण

	अगर (!udata) अणु
		ret = alloc_kernel_wrid(hr_dev, hr_qp);
		अगर (ret) अणु
			ibdev_err(ibdev, "failed to alloc wrid, ret = %d.\n",
				  ret);
			वापस ret;
		पूर्ण
	पूर्ण

	ret = alloc_qp_buf(hr_dev, hr_qp, init_attr, udata, ucmd.buf_addr);
	अगर (ret) अणु
		ibdev_err(ibdev, "failed to alloc QP buffer, ret = %d.\n", ret);
		जाओ err_buf;
	पूर्ण

	ret = alloc_qpn(hr_dev, hr_qp);
	अगर (ret) अणु
		ibdev_err(ibdev, "failed to alloc QPN, ret = %d.\n", ret);
		जाओ err_qpn;
	पूर्ण

	ret = alloc_qp_db(hr_dev, hr_qp, init_attr, udata, &ucmd, &resp);
	अगर (ret) अणु
		ibdev_err(ibdev, "failed to alloc QP doorbell, ret = %d.\n",
			  ret);
		जाओ err_db;
	पूर्ण

	ret = alloc_qpc(hr_dev, hr_qp);
	अगर (ret) अणु
		ibdev_err(ibdev, "failed to alloc QP context, ret = %d.\n",
			  ret);
		जाओ err_qpc;
	पूर्ण

	ret = hns_roce_qp_store(hr_dev, hr_qp, init_attr);
	अगर (ret) अणु
		ibdev_err(ibdev, "failed to store QP, ret = %d.\n", ret);
		जाओ err_store;
	पूर्ण

	अगर (udata) अणु
		ret = ib_copy_to_udata(udata, &resp,
				       min(udata->outlen, माप(resp)));
		अगर (ret) अणु
			ibdev_err(ibdev, "copy qp resp failed!\n");
			जाओ err_store;
		पूर्ण
	पूर्ण

	अगर (hr_dev->caps.flags & HNS_ROCE_CAP_FLAG_QP_FLOW_CTRL) अणु
		ret = hr_dev->hw->qp_flow_control_init(hr_dev, hr_qp);
		अगर (ret)
			जाओ err_flow_ctrl;
	पूर्ण

	hr_qp->ibqp.qp_num = hr_qp->qpn;
	hr_qp->event = hns_roce_ib_qp_event;
	atomic_set(&hr_qp->refcount, 1);
	init_completion(&hr_qp->मुक्त);

	वापस 0;

err_flow_ctrl:
	hns_roce_qp_हटाओ(hr_dev, hr_qp);
err_store:
	मुक्त_qpc(hr_dev, hr_qp);
err_qpc:
	मुक्त_qp_db(hr_dev, hr_qp, udata);
err_db:
	मुक्त_qpn(hr_dev, hr_qp);
err_qpn:
	मुक्त_qp_buf(hr_dev, hr_qp);
err_buf:
	मुक्त_kernel_wrid(hr_qp);
	वापस ret;
पूर्ण

व्योम hns_roce_qp_destroy(काष्ठा hns_roce_dev *hr_dev, काष्ठा hns_roce_qp *hr_qp,
			 काष्ठा ib_udata *udata)
अणु
	अगर (atomic_dec_and_test(&hr_qp->refcount))
		complete(&hr_qp->मुक्त);
	रुको_क्रम_completion(&hr_qp->मुक्त);

	मुक्त_qpc(hr_dev, hr_qp);
	मुक्त_qpn(hr_dev, hr_qp);
	मुक्त_qp_buf(hr_dev, hr_qp);
	मुक्त_kernel_wrid(hr_qp);
	मुक्त_qp_db(hr_dev, hr_qp, udata);

	kमुक्त(hr_qp);
पूर्ण

अटल पूर्णांक check_qp_type(काष्ठा hns_roce_dev *hr_dev, क्रमागत ib_qp_type type,
			 bool is_user)
अणु
	चयन (type) अणु
	हाल IB_QPT_XRC_INI:
	हाल IB_QPT_XRC_TGT:
		अगर (!(hr_dev->caps.flags & HNS_ROCE_CAP_FLAG_XRC))
			जाओ out;
		अवरोध;
	हाल IB_QPT_UD:
		अगर (hr_dev->pci_dev->revision <= PCI_REVISION_ID_HIP08 &&
		    is_user)
			जाओ out;
		अवरोध;
	हाल IB_QPT_RC:
	हाल IB_QPT_GSI:
		अवरोध;
	शेष:
		जाओ out;
	पूर्ण

	वापस 0;

out:
	ibdev_err(&hr_dev->ib_dev, "not support QP type %d\n", type);

	वापस -EOPNOTSUPP;
पूर्ण

काष्ठा ib_qp *hns_roce_create_qp(काष्ठा ib_pd *pd,
				 काष्ठा ib_qp_init_attr *init_attr,
				 काष्ठा ib_udata *udata)
अणु
	काष्ठा ib_device *ibdev = pd ? pd->device : init_attr->xrcd->device;
	काष्ठा hns_roce_dev *hr_dev = to_hr_dev(ibdev);
	काष्ठा hns_roce_qp *hr_qp;
	पूर्णांक ret;

	ret = check_qp_type(hr_dev, init_attr->qp_type, !!udata);
	अगर (ret)
		वापस ERR_PTR(ret);

	hr_qp = kzalloc(माप(*hr_qp), GFP_KERNEL);
	अगर (!hr_qp)
		वापस ERR_PTR(-ENOMEM);

	अगर (init_attr->qp_type == IB_QPT_XRC_INI)
		init_attr->recv_cq = शून्य;

	अगर (init_attr->qp_type == IB_QPT_XRC_TGT) अणु
		hr_qp->xrcdn = to_hr_xrcd(init_attr->xrcd)->xrcdn;
		init_attr->recv_cq = शून्य;
		init_attr->send_cq = शून्य;
	पूर्ण

	अगर (init_attr->qp_type == IB_QPT_GSI) अणु
		hr_qp->port = init_attr->port_num - 1;
		hr_qp->phy_port = hr_dev->iboe.phy_port[hr_qp->port];
	पूर्ण

	ret = hns_roce_create_qp_common(hr_dev, pd, init_attr, udata, hr_qp);
	अगर (ret) अणु
		ibdev_err(ibdev, "Create QP type 0x%x failed(%d)\n",
			  init_attr->qp_type, ret);

		kमुक्त(hr_qp);
		वापस ERR_PTR(ret);
	पूर्ण

	वापस &hr_qp->ibqp;
पूर्ण

पूर्णांक to_hr_qp_type(पूर्णांक qp_type)
अणु
	चयन (qp_type) अणु
	हाल IB_QPT_RC:
		वापस SERV_TYPE_RC;
	हाल IB_QPT_UD:
	हाल IB_QPT_GSI:
		वापस SERV_TYPE_UD;
	हाल IB_QPT_XRC_INI:
	हाल IB_QPT_XRC_TGT:
		वापस SERV_TYPE_XRC;
	शेष:
		वापस -1;
	पूर्ण
पूर्ण

अटल पूर्णांक check_mtu_validate(काष्ठा hns_roce_dev *hr_dev,
			      काष्ठा hns_roce_qp *hr_qp,
			      काष्ठा ib_qp_attr *attr, पूर्णांक attr_mask)
अणु
	क्रमागत ib_mtu active_mtu;
	पूर्णांक p;

	p = attr_mask & IB_QP_PORT ? (attr->port_num - 1) : hr_qp->port;
	active_mtu = iboe_get_mtu(hr_dev->iboe.netdevs[p]->mtu);

	अगर ((hr_dev->caps.max_mtu >= IB_MTU_2048 &&
	    attr->path_mtu > hr_dev->caps.max_mtu) ||
	    attr->path_mtu < IB_MTU_256 || attr->path_mtu > active_mtu) अणु
		ibdev_err(&hr_dev->ib_dev,
			"attr path_mtu(%d)invalid while modify qp",
			attr->path_mtu);
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक hns_roce_check_qp_attr(काष्ठा ib_qp *ibqp, काष्ठा ib_qp_attr *attr,
				  पूर्णांक attr_mask)
अणु
	काष्ठा hns_roce_dev *hr_dev = to_hr_dev(ibqp->device);
	काष्ठा hns_roce_qp *hr_qp = to_hr_qp(ibqp);
	पूर्णांक p;

	अगर ((attr_mask & IB_QP_PORT) &&
	    (attr->port_num == 0 || attr->port_num > hr_dev->caps.num_ports)) अणु
		ibdev_err(&hr_dev->ib_dev, "invalid attr, port_num = %u.\n",
			  attr->port_num);
		वापस -EINVAL;
	पूर्ण

	अगर (attr_mask & IB_QP_PKEY_INDEX) अणु
		p = attr_mask & IB_QP_PORT ? (attr->port_num - 1) : hr_qp->port;
		अगर (attr->pkey_index >= hr_dev->caps.pkey_table_len[p]) अणु
			ibdev_err(&hr_dev->ib_dev,
				  "invalid attr, pkey_index = %u.\n",
				  attr->pkey_index);
			वापस -EINVAL;
		पूर्ण
	पूर्ण

	अगर (attr_mask & IB_QP_MAX_QP_RD_ATOMIC &&
	    attr->max_rd_atomic > hr_dev->caps.max_qp_init_rdma) अणु
		ibdev_err(&hr_dev->ib_dev,
			  "invalid attr, max_rd_atomic = %u.\n",
			  attr->max_rd_atomic);
		वापस -EINVAL;
	पूर्ण

	अगर (attr_mask & IB_QP_MAX_DEST_RD_ATOMIC &&
	    attr->max_dest_rd_atomic > hr_dev->caps.max_qp_dest_rdma) अणु
		ibdev_err(&hr_dev->ib_dev,
			  "invalid attr, max_dest_rd_atomic = %u.\n",
			  attr->max_dest_rd_atomic);
		वापस -EINVAL;
	पूर्ण

	अगर (attr_mask & IB_QP_PATH_MTU)
		वापस check_mtu_validate(hr_dev, hr_qp, attr, attr_mask);

	वापस 0;
पूर्ण

पूर्णांक hns_roce_modअगरy_qp(काष्ठा ib_qp *ibqp, काष्ठा ib_qp_attr *attr,
		       पूर्णांक attr_mask, काष्ठा ib_udata *udata)
अणु
	काष्ठा hns_roce_dev *hr_dev = to_hr_dev(ibqp->device);
	काष्ठा hns_roce_qp *hr_qp = to_hr_qp(ibqp);
	क्रमागत ib_qp_state cur_state, new_state;
	पूर्णांक ret = -EINVAL;

	mutex_lock(&hr_qp->mutex);

	अगर (attr_mask & IB_QP_CUR_STATE && attr->cur_qp_state != hr_qp->state)
		जाओ out;

	cur_state = hr_qp->state;
	new_state = attr_mask & IB_QP_STATE ? attr->qp_state : cur_state;

	अगर (ibqp->uobject &&
	    (attr_mask & IB_QP_STATE) && new_state == IB_QPS_ERR) अणु
		अगर (hr_qp->en_flags & HNS_ROCE_QP_CAP_SQ_RECORD_DB) अणु
			hr_qp->sq.head = *(पूर्णांक *)(hr_qp->sdb.virt_addr);

			अगर (hr_qp->en_flags & HNS_ROCE_QP_CAP_RQ_RECORD_DB)
				hr_qp->rq.head = *(पूर्णांक *)(hr_qp->rdb.virt_addr);
		पूर्ण अन्यथा अणु
			ibdev_warn(&hr_dev->ib_dev,
				  "flush cqe is not supported in userspace!\n");
			जाओ out;
		पूर्ण
	पूर्ण

	अगर (!ib_modअगरy_qp_is_ok(cur_state, new_state, ibqp->qp_type,
				attr_mask)) अणु
		ibdev_err(&hr_dev->ib_dev, "ib_modify_qp_is_ok failed\n");
		जाओ out;
	पूर्ण

	ret = hns_roce_check_qp_attr(ibqp, attr, attr_mask);
	अगर (ret)
		जाओ out;

	अगर (cur_state == new_state && cur_state == IB_QPS_RESET) अणु
		अगर (hr_dev->hw_rev == HNS_ROCE_HW_VER1) अणु
			ret = -EPERM;
			ibdev_err(&hr_dev->ib_dev,
				  "RST2RST state is not supported\n");
		पूर्ण अन्यथा अणु
			ret = 0;
		पूर्ण

		जाओ out;
	पूर्ण

	ret = hr_dev->hw->modअगरy_qp(ibqp, attr, attr_mask, cur_state,
				    new_state);

out:
	mutex_unlock(&hr_qp->mutex);

	वापस ret;
पूर्ण

व्योम hns_roce_lock_cqs(काष्ठा hns_roce_cq *send_cq, काष्ठा hns_roce_cq *recv_cq)
		       __acquires(&send_cq->lock) __acquires(&recv_cq->lock)
अणु
	अगर (unlikely(send_cq == शून्य && recv_cq == शून्य)) अणु
		__acquire(&send_cq->lock);
		__acquire(&recv_cq->lock);
	पूर्ण अन्यथा अगर (unlikely(send_cq != शून्य && recv_cq == शून्य)) अणु
		spin_lock_irq(&send_cq->lock);
		__acquire(&recv_cq->lock);
	पूर्ण अन्यथा अगर (unlikely(send_cq == शून्य && recv_cq != शून्य)) अणु
		spin_lock_irq(&recv_cq->lock);
		__acquire(&send_cq->lock);
	पूर्ण अन्यथा अगर (send_cq == recv_cq) अणु
		spin_lock_irq(&send_cq->lock);
		__acquire(&recv_cq->lock);
	पूर्ण अन्यथा अगर (send_cq->cqn < recv_cq->cqn) अणु
		spin_lock_irq(&send_cq->lock);
		spin_lock_nested(&recv_cq->lock, SINGLE_DEPTH_NESTING);
	पूर्ण अन्यथा अणु
		spin_lock_irq(&recv_cq->lock);
		spin_lock_nested(&send_cq->lock, SINGLE_DEPTH_NESTING);
	पूर्ण
पूर्ण

व्योम hns_roce_unlock_cqs(काष्ठा hns_roce_cq *send_cq,
			 काष्ठा hns_roce_cq *recv_cq) __releases(&send_cq->lock)
			 __releases(&recv_cq->lock)
अणु
	अगर (unlikely(send_cq == शून्य && recv_cq == शून्य)) अणु
		__release(&recv_cq->lock);
		__release(&send_cq->lock);
	पूर्ण अन्यथा अगर (unlikely(send_cq != शून्य && recv_cq == शून्य)) अणु
		__release(&recv_cq->lock);
		spin_unlock(&send_cq->lock);
	पूर्ण अन्यथा अगर (unlikely(send_cq == शून्य && recv_cq != शून्य)) अणु
		__release(&send_cq->lock);
		spin_unlock(&recv_cq->lock);
	पूर्ण अन्यथा अगर (send_cq == recv_cq) अणु
		__release(&recv_cq->lock);
		spin_unlock_irq(&send_cq->lock);
	पूर्ण अन्यथा अगर (send_cq->cqn < recv_cq->cqn) अणु
		spin_unlock(&recv_cq->lock);
		spin_unlock_irq(&send_cq->lock);
	पूर्ण अन्यथा अणु
		spin_unlock(&send_cq->lock);
		spin_unlock_irq(&recv_cq->lock);
	पूर्ण
पूर्ण

अटल अंतरभूत व्योम *get_wqe(काष्ठा hns_roce_qp *hr_qp, पूर्णांक offset)
अणु
	वापस hns_roce_buf_offset(hr_qp->mtr.kmem, offset);
पूर्ण

व्योम *hns_roce_get_recv_wqe(काष्ठा hns_roce_qp *hr_qp, अचिन्हित पूर्णांक n)
अणु
	वापस get_wqe(hr_qp, hr_qp->rq.offset + (n << hr_qp->rq.wqe_shअगरt));
पूर्ण

व्योम *hns_roce_get_send_wqe(काष्ठा hns_roce_qp *hr_qp, अचिन्हित पूर्णांक n)
अणु
	वापस get_wqe(hr_qp, hr_qp->sq.offset + (n << hr_qp->sq.wqe_shअगरt));
पूर्ण

व्योम *hns_roce_get_extend_sge(काष्ठा hns_roce_qp *hr_qp, अचिन्हित पूर्णांक n)
अणु
	वापस get_wqe(hr_qp, hr_qp->sge.offset + (n << hr_qp->sge.sge_shअगरt));
पूर्ण

bool hns_roce_wq_overflow(काष्ठा hns_roce_wq *hr_wq, u32 nreq,
			  काष्ठा ib_cq *ib_cq)
अणु
	काष्ठा hns_roce_cq *hr_cq;
	u32 cur;

	cur = hr_wq->head - hr_wq->tail;
	अगर (likely(cur + nreq < hr_wq->wqe_cnt))
		वापस false;

	hr_cq = to_hr_cq(ib_cq);
	spin_lock(&hr_cq->lock);
	cur = hr_wq->head - hr_wq->tail;
	spin_unlock(&hr_cq->lock);

	वापस cur + nreq >= hr_wq->wqe_cnt;
पूर्ण

पूर्णांक hns_roce_init_qp_table(काष्ठा hns_roce_dev *hr_dev)
अणु
	काष्ठा hns_roce_qp_table *qp_table = &hr_dev->qp_table;
	अचिन्हित पूर्णांक reserved_from_bot;
	अचिन्हित पूर्णांक i;

	mutex_init(&qp_table->scc_mutex);
	mutex_init(&qp_table->bank_mutex);
	xa_init(&hr_dev->qp_table_xa);

	reserved_from_bot = hr_dev->caps.reserved_qps;

	क्रम (i = 0; i < reserved_from_bot; i++) अणु
		hr_dev->qp_table.bank[get_qp_bankid(i)].inuse++;
		hr_dev->qp_table.bank[get_qp_bankid(i)].min++;
	पूर्ण

	क्रम (i = 0; i < HNS_ROCE_QP_BANK_NUM; i++) अणु
		ida_init(&hr_dev->qp_table.bank[i].ida);
		hr_dev->qp_table.bank[i].max = hr_dev->caps.num_qps /
					       HNS_ROCE_QP_BANK_NUM - 1;
		hr_dev->qp_table.bank[i].next = hr_dev->qp_table.bank[i].min;
	पूर्ण

	वापस 0;
पूर्ण

व्योम hns_roce_cleanup_qp_table(काष्ठा hns_roce_dev *hr_dev)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < HNS_ROCE_QP_BANK_NUM; i++)
		ida_destroy(&hr_dev->qp_table.bank[i].ida);
पूर्ण
