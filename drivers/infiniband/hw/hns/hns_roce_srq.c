<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0 OR Linux-OpenIB
/*
 * Copyright (c) 2018 Hisilicon Limited.
 */

#समावेश <linux/pci.h>
#समावेश <rdma/ib_uस्मृति.स>
#समावेश "hns_roce_device.h"
#समावेश "hns_roce_cmd.h"
#समावेश "hns_roce_hem.h"

व्योम hns_roce_srq_event(काष्ठा hns_roce_dev *hr_dev, u32 srqn, पूर्णांक event_type)
अणु
	काष्ठा hns_roce_srq_table *srq_table = &hr_dev->srq_table;
	काष्ठा hns_roce_srq *srq;

	xa_lock(&srq_table->xa);
	srq = xa_load(&srq_table->xa, srqn & (hr_dev->caps.num_srqs - 1));
	अगर (srq)
		atomic_inc(&srq->refcount);
	xa_unlock(&srq_table->xa);

	अगर (!srq) अणु
		dev_warn(hr_dev->dev, "Async event for bogus SRQ %08x\n", srqn);
		वापस;
	पूर्ण

	srq->event(srq, event_type);

	अगर (atomic_dec_and_test(&srq->refcount))
		complete(&srq->मुक्त);
पूर्ण

अटल व्योम hns_roce_ib_srq_event(काष्ठा hns_roce_srq *srq,
				  क्रमागत hns_roce_event event_type)
अणु
	काष्ठा hns_roce_dev *hr_dev = to_hr_dev(srq->ibsrq.device);
	काष्ठा ib_srq *ibsrq = &srq->ibsrq;
	काष्ठा ib_event event;

	अगर (ibsrq->event_handler) अणु
		event.device      = ibsrq->device;
		event.element.srq = ibsrq;
		चयन (event_type) अणु
		हाल HNS_ROCE_EVENT_TYPE_SRQ_LIMIT_REACH:
			event.event = IB_EVENT_SRQ_LIMIT_REACHED;
			अवरोध;
		हाल HNS_ROCE_EVENT_TYPE_SRQ_CATAS_ERROR:
			event.event = IB_EVENT_SRQ_ERR;
			अवरोध;
		शेष:
			dev_err(hr_dev->dev,
			   "hns_roce:Unexpected event type 0x%x on SRQ %06lx\n",
			   event_type, srq->srqn);
			वापस;
		पूर्ण

		ibsrq->event_handler(&event, ibsrq->srq_context);
	पूर्ण
पूर्ण

अटल पूर्णांक hns_roce_hw_create_srq(काष्ठा hns_roce_dev *dev,
				  काष्ठा hns_roce_cmd_mailbox *mailbox,
				  अचिन्हित दीर्घ srq_num)
अणु
	वापस hns_roce_cmd_mbox(dev, mailbox->dma, 0, srq_num, 0,
				 HNS_ROCE_CMD_CREATE_SRQ,
				 HNS_ROCE_CMD_TIMEOUT_MSECS);
पूर्ण

अटल पूर्णांक hns_roce_hw_destroy_srq(काष्ठा hns_roce_dev *dev,
				   काष्ठा hns_roce_cmd_mailbox *mailbox,
				   अचिन्हित दीर्घ srq_num)
अणु
	वापस hns_roce_cmd_mbox(dev, 0, mailbox ? mailbox->dma : 0, srq_num,
				 mailbox ? 0 : 1, HNS_ROCE_CMD_DESTROY_SRQ,
				 HNS_ROCE_CMD_TIMEOUT_MSECS);
पूर्ण

अटल पूर्णांक alloc_srqc(काष्ठा hns_roce_dev *hr_dev, काष्ठा hns_roce_srq *srq)
अणु
	काष्ठा hns_roce_srq_table *srq_table = &hr_dev->srq_table;
	काष्ठा ib_device *ibdev = &hr_dev->ib_dev;
	काष्ठा hns_roce_cmd_mailbox *mailbox;
	पूर्णांक ret;

	ret = hns_roce_biपंचांगap_alloc(&srq_table->biपंचांगap, &srq->srqn);
	अगर (ret) अणु
		ibdev_err(ibdev, "failed to alloc SRQ number.\n");
		वापस -ENOMEM;
	पूर्ण

	ret = hns_roce_table_get(hr_dev, &srq_table->table, srq->srqn);
	अगर (ret) अणु
		ibdev_err(ibdev, "failed to get SRQC table, ret = %d.\n", ret);
		जाओ err_out;
	पूर्ण

	ret = xa_err(xa_store(&srq_table->xa, srq->srqn, srq, GFP_KERNEL));
	अगर (ret) अणु
		ibdev_err(ibdev, "failed to store SRQC, ret = %d.\n", ret);
		जाओ err_put;
	पूर्ण

	mailbox = hns_roce_alloc_cmd_mailbox(hr_dev);
	अगर (IS_ERR_OR_शून्य(mailbox)) अणु
		ibdev_err(ibdev, "failed to alloc mailbox for SRQC.\n");
		ret = -ENOMEM;
		जाओ err_xa;
	पूर्ण

	ret = hr_dev->hw->ग_लिखो_srqc(srq, mailbox->buf);
	अगर (ret) अणु
		ibdev_err(ibdev, "failed to write SRQC.\n");
		जाओ err_mbox;
	पूर्ण

	ret = hns_roce_hw_create_srq(hr_dev, mailbox, srq->srqn);
	अगर (ret) अणु
		ibdev_err(ibdev, "failed to config SRQC, ret = %d.\n", ret);
		जाओ err_mbox;
	पूर्ण

	hns_roce_मुक्त_cmd_mailbox(hr_dev, mailbox);

	वापस 0;

err_mbox:
	hns_roce_मुक्त_cmd_mailbox(hr_dev, mailbox);
err_xa:
	xa_erase(&srq_table->xa, srq->srqn);
err_put:
	hns_roce_table_put(hr_dev, &srq_table->table, srq->srqn);
err_out:
	hns_roce_biपंचांगap_मुक्त(&srq_table->biपंचांगap, srq->srqn, BITMAP_NO_RR);

	वापस ret;
पूर्ण

अटल व्योम मुक्त_srqc(काष्ठा hns_roce_dev *hr_dev, काष्ठा hns_roce_srq *srq)
अणु
	काष्ठा hns_roce_srq_table *srq_table = &hr_dev->srq_table;
	पूर्णांक ret;

	ret = hns_roce_hw_destroy_srq(hr_dev, शून्य, srq->srqn);
	अगर (ret)
		dev_err(hr_dev->dev, "DESTROY_SRQ failed (%d) for SRQN %06lx\n",
			ret, srq->srqn);

	xa_erase(&srq_table->xa, srq->srqn);

	अगर (atomic_dec_and_test(&srq->refcount))
		complete(&srq->मुक्त);
	रुको_क्रम_completion(&srq->मुक्त);

	hns_roce_table_put(hr_dev, &srq_table->table, srq->srqn);
	hns_roce_biपंचांगap_मुक्त(&srq_table->biपंचांगap, srq->srqn, BITMAP_NO_RR);
पूर्ण

अटल पूर्णांक alloc_srq_idx(काष्ठा hns_roce_dev *hr_dev, काष्ठा hns_roce_srq *srq,
			 काष्ठा ib_udata *udata, अचिन्हित दीर्घ addr)
अणु
	काष्ठा hns_roce_idx_que *idx_que = &srq->idx_que;
	काष्ठा ib_device *ibdev = &hr_dev->ib_dev;
	काष्ठा hns_roce_buf_attr buf_attr = अणुपूर्ण;
	पूर्णांक ret;

	srq->idx_que.entry_shअगरt = ilog2(HNS_ROCE_IDX_QUE_ENTRY_SZ);

	buf_attr.page_shअगरt = hr_dev->caps.idx_buf_pg_sz + HNS_HW_PAGE_SHIFT;
	buf_attr.region[0].size = to_hr_hem_entries_size(srq->wqe_cnt,
					srq->idx_que.entry_shअगरt);
	buf_attr.region[0].hopnum = hr_dev->caps.idx_hop_num;
	buf_attr.region_count = 1;

	ret = hns_roce_mtr_create(hr_dev, &idx_que->mtr, &buf_attr,
				  hr_dev->caps.idx_ba_pg_sz + HNS_HW_PAGE_SHIFT,
				  udata, addr);
	अगर (ret) अणु
		ibdev_err(ibdev,
			  "failed to alloc SRQ idx mtr, ret = %d.\n", ret);
		वापस ret;
	पूर्ण

	अगर (!udata) अणु
		idx_que->biपंचांगap = biपंचांगap_zalloc(srq->wqe_cnt, GFP_KERNEL);
		अगर (!idx_que->biपंचांगap) अणु
			ibdev_err(ibdev, "failed to alloc SRQ idx bitmap.\n");
			ret = -ENOMEM;
			जाओ err_idx_mtr;
		पूर्ण
	पूर्ण

	idx_que->head = 0;
	idx_que->tail = 0;

	वापस 0;
err_idx_mtr:
	hns_roce_mtr_destroy(hr_dev, &idx_que->mtr);

	वापस ret;
पूर्ण

अटल व्योम मुक्त_srq_idx(काष्ठा hns_roce_dev *hr_dev, काष्ठा hns_roce_srq *srq)
अणु
	काष्ठा hns_roce_idx_que *idx_que = &srq->idx_que;

	biपंचांगap_मुक्त(idx_que->biपंचांगap);
	idx_que->biपंचांगap = शून्य;
	hns_roce_mtr_destroy(hr_dev, &idx_que->mtr);
पूर्ण

अटल पूर्णांक alloc_srq_wqe_buf(काष्ठा hns_roce_dev *hr_dev,
			     काष्ठा hns_roce_srq *srq,
			     काष्ठा ib_udata *udata, अचिन्हित दीर्घ addr)
अणु
	काष्ठा ib_device *ibdev = &hr_dev->ib_dev;
	काष्ठा hns_roce_buf_attr buf_attr = अणुपूर्ण;
	पूर्णांक ret;

	srq->wqe_shअगरt = ilog2(roundup_घात_of_two(max(HNS_ROCE_SGE_SIZE,
						      HNS_ROCE_SGE_SIZE *
						      srq->max_gs)));

	buf_attr.page_shअगरt = hr_dev->caps.srqwqe_buf_pg_sz + HNS_HW_PAGE_SHIFT;
	buf_attr.region[0].size = to_hr_hem_entries_size(srq->wqe_cnt,
							 srq->wqe_shअगरt);
	buf_attr.region[0].hopnum = hr_dev->caps.srqwqe_hop_num;
	buf_attr.region_count = 1;

	ret = hns_roce_mtr_create(hr_dev, &srq->buf_mtr, &buf_attr,
				  hr_dev->caps.srqwqe_ba_pg_sz +
				  HNS_HW_PAGE_SHIFT, udata, addr);
	अगर (ret)
		ibdev_err(ibdev,
			  "failed to alloc SRQ buf mtr, ret = %d.\n", ret);

	वापस ret;
पूर्ण

अटल व्योम मुक्त_srq_wqe_buf(काष्ठा hns_roce_dev *hr_dev,
			     काष्ठा hns_roce_srq *srq)
अणु
	hns_roce_mtr_destroy(hr_dev, &srq->buf_mtr);
पूर्ण

अटल पूर्णांक alloc_srq_wrid(काष्ठा hns_roce_dev *hr_dev, काष्ठा hns_roce_srq *srq)
अणु
	srq->wrid = kvदो_स्मृति_array(srq->wqe_cnt, माप(u64), GFP_KERNEL);
	अगर (!srq->wrid)
		वापस -ENOMEM;

	वापस 0;
पूर्ण

अटल व्योम मुक्त_srq_wrid(काष्ठा hns_roce_srq *srq)
अणु
	kमुक्त(srq->wrid);
	srq->wrid = शून्य;
पूर्ण

अटल u32 proc_srq_sge(काष्ठा hns_roce_dev *dev, काष्ठा hns_roce_srq *hr_srq,
			bool user)
अणु
	u32 max_sge = dev->caps.max_srq_sges;

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
		hr_srq->rsv_sge = 1;

	वापस max_sge;
पूर्ण

अटल पूर्णांक set_srq_basic_param(काष्ठा hns_roce_srq *srq,
			       काष्ठा ib_srq_init_attr *init_attr,
			       काष्ठा ib_udata *udata)
अणु
	काष्ठा hns_roce_dev *hr_dev = to_hr_dev(srq->ibsrq.device);
	काष्ठा ib_srq_attr *attr = &init_attr->attr;
	u32 max_sge;

	max_sge = proc_srq_sge(hr_dev, srq, !!udata);
	अगर (attr->max_wr > hr_dev->caps.max_srq_wrs ||
	    attr->max_sge > max_sge) अणु
		ibdev_err(&hr_dev->ib_dev,
			  "invalid SRQ attr, depth = %u, sge = %u.\n",
			  attr->max_wr, attr->max_sge);
		वापस -EINVAL;
	पूर्ण

	attr->max_wr = max_t(u32, attr->max_wr, HNS_ROCE_MIN_SRQ_WQE_NUM);
	srq->wqe_cnt = roundup_घात_of_two(attr->max_wr);
	srq->max_gs = roundup_घात_of_two(attr->max_sge + srq->rsv_sge);

	attr->max_wr = srq->wqe_cnt;
	attr->max_sge = srq->max_gs - srq->rsv_sge;
	attr->srq_limit = 0;

	वापस 0;
पूर्ण

अटल व्योम set_srq_ext_param(काष्ठा hns_roce_srq *srq,
			      काष्ठा ib_srq_init_attr *init_attr)
अणु
	srq->cqn = ib_srq_has_cq(init_attr->srq_type) ?
		   to_hr_cq(init_attr->ext.cq)->cqn : 0;

	srq->xrcdn = (init_attr->srq_type == IB_SRQT_XRC) ?
		     to_hr_xrcd(init_attr->ext.xrc.xrcd)->xrcdn : 0;
पूर्ण

अटल पूर्णांक set_srq_param(काष्ठा hns_roce_srq *srq,
			 काष्ठा ib_srq_init_attr *init_attr,
			 काष्ठा ib_udata *udata)
अणु
	पूर्णांक ret;

	ret = set_srq_basic_param(srq, init_attr, udata);
	अगर (ret)
		वापस ret;

	set_srq_ext_param(srq, init_attr);

	वापस 0;
पूर्ण

अटल पूर्णांक alloc_srq_buf(काष्ठा hns_roce_dev *hr_dev, काष्ठा hns_roce_srq *srq,
			 काष्ठा ib_udata *udata)
अणु
	काष्ठा hns_roce_ib_create_srq ucmd = अणुपूर्ण;
	पूर्णांक ret;

	अगर (udata) अणु
		ret = ib_copy_from_udata(&ucmd, udata,
					 min(udata->inlen, माप(ucmd)));
		अगर (ret) अणु
			ibdev_err(&hr_dev->ib_dev,
				  "failed to copy SRQ udata, ret = %d.\n",
				  ret);
			वापस ret;
		पूर्ण
	पूर्ण

	ret = alloc_srq_idx(hr_dev, srq, udata, ucmd.que_addr);
	अगर (ret)
		वापस ret;

	ret = alloc_srq_wqe_buf(hr_dev, srq, udata, ucmd.buf_addr);
	अगर (ret)
		जाओ err_idx;

	अगर (!udata) अणु
		ret = alloc_srq_wrid(hr_dev, srq);
		अगर (ret)
			जाओ err_wqe_buf;
	पूर्ण

	वापस 0;

err_wqe_buf:
	मुक्त_srq_wqe_buf(hr_dev, srq);
err_idx:
	मुक्त_srq_idx(hr_dev, srq);

	वापस ret;
पूर्ण

अटल व्योम मुक्त_srq_buf(काष्ठा hns_roce_dev *hr_dev, काष्ठा hns_roce_srq *srq)
अणु
	मुक्त_srq_wrid(srq);
	मुक्त_srq_wqe_buf(hr_dev, srq);
	मुक्त_srq_idx(hr_dev, srq);
पूर्ण

पूर्णांक hns_roce_create_srq(काष्ठा ib_srq *ib_srq,
			काष्ठा ib_srq_init_attr *init_attr,
			काष्ठा ib_udata *udata)
अणु
	काष्ठा hns_roce_dev *hr_dev = to_hr_dev(ib_srq->device);
	काष्ठा hns_roce_ib_create_srq_resp resp = अणुपूर्ण;
	काष्ठा hns_roce_srq *srq = to_hr_srq(ib_srq);
	पूर्णांक ret;

	mutex_init(&srq->mutex);
	spin_lock_init(&srq->lock);

	ret = set_srq_param(srq, init_attr, udata);
	अगर (ret)
		वापस ret;

	ret = alloc_srq_buf(hr_dev, srq, udata);
	अगर (ret)
		वापस ret;

	ret = alloc_srqc(hr_dev, srq);
	अगर (ret)
		जाओ err_srq_buf;

	अगर (udata) अणु
		resp.srqn = srq->srqn;
		अगर (ib_copy_to_udata(udata, &resp,
				     min(udata->outlen, माप(resp)))) अणु
			ret = -EFAULT;
			जाओ err_srqc;
		पूर्ण
	पूर्ण

	srq->db_reg = hr_dev->reg_base + SRQ_DB_REG;
	srq->event = hns_roce_ib_srq_event;
	atomic_set(&srq->refcount, 1);
	init_completion(&srq->मुक्त);

	वापस 0;

err_srqc:
	मुक्त_srqc(hr_dev, srq);
err_srq_buf:
	मुक्त_srq_buf(hr_dev, srq);

	वापस ret;
पूर्ण

पूर्णांक hns_roce_destroy_srq(काष्ठा ib_srq *ibsrq, काष्ठा ib_udata *udata)
अणु
	काष्ठा hns_roce_dev *hr_dev = to_hr_dev(ibsrq->device);
	काष्ठा hns_roce_srq *srq = to_hr_srq(ibsrq);

	मुक्त_srqc(hr_dev, srq);
	मुक्त_srq_buf(hr_dev, srq);
	वापस 0;
पूर्ण

पूर्णांक hns_roce_init_srq_table(काष्ठा hns_roce_dev *hr_dev)
अणु
	काष्ठा hns_roce_srq_table *srq_table = &hr_dev->srq_table;

	xa_init(&srq_table->xa);

	वापस hns_roce_biपंचांगap_init(&srq_table->biपंचांगap, hr_dev->caps.num_srqs,
				    hr_dev->caps.num_srqs - 1,
				    hr_dev->caps.reserved_srqs, 0);
पूर्ण

व्योम hns_roce_cleanup_srq_table(काष्ठा hns_roce_dev *hr_dev)
अणु
	hns_roce_biपंचांगap_cleanup(&hr_dev->srq_table.biपंचांगap);
पूर्ण
