<शैली गुरु>
/*
 * Copyright (c) 2016 Hisilicon Limited.
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

#समावेश <linux/platक्रमm_device.h>
#समावेश <rdma/ib_uस्मृति.स>
#समावेश <rdma/uverbs_ioctl.h>
#समावेश "hns_roce_device.h"
#समावेश "hns_roce_cmd.h"
#समावेश "hns_roce_hem.h"
#समावेश "hns_roce_common.h"

अटल u8 get_least_load_bankid_क्रम_cq(काष्ठा hns_roce_bank *bank)
अणु
	u32 least_load = bank[0].inuse;
	u8 bankid = 0;
	u32 bankcnt;
	u8 i;

	क्रम (i = 1; i < HNS_ROCE_CQ_BANK_NUM; i++) अणु
		bankcnt = bank[i].inuse;
		अगर (bankcnt < least_load) अणु
			least_load = bankcnt;
			bankid = i;
		पूर्ण
	पूर्ण

	वापस bankid;
पूर्ण

अटल पूर्णांक alloc_cqn(काष्ठा hns_roce_dev *hr_dev, काष्ठा hns_roce_cq *hr_cq)
अणु
	काष्ठा hns_roce_cq_table *cq_table = &hr_dev->cq_table;
	काष्ठा hns_roce_bank *bank;
	u8 bankid;
	पूर्णांक id;

	mutex_lock(&cq_table->bank_mutex);
	bankid = get_least_load_bankid_क्रम_cq(cq_table->bank);
	bank = &cq_table->bank[bankid];

	id = ida_alloc_range(&bank->ida, bank->min, bank->max, GFP_KERNEL);
	अगर (id < 0) अणु
		mutex_unlock(&cq_table->bank_mutex);
		वापस id;
	पूर्ण

	/* the lower 2 bits is bankid */
	hr_cq->cqn = (id << CQ_BANKID_SHIFT) | bankid;
	bank->inuse++;
	mutex_unlock(&cq_table->bank_mutex);

	वापस 0;
पूर्ण

अटल अंतरभूत u8 get_cq_bankid(अचिन्हित दीर्घ cqn)
अणु
	/* The lower 2 bits of CQN are used to hash to dअगरferent banks */
	वापस (u8)(cqn & GENMASK(1, 0));
पूर्ण

अटल व्योम मुक्त_cqn(काष्ठा hns_roce_dev *hr_dev, अचिन्हित दीर्घ cqn)
अणु
	काष्ठा hns_roce_cq_table *cq_table = &hr_dev->cq_table;
	काष्ठा hns_roce_bank *bank;

	bank = &cq_table->bank[get_cq_bankid(cqn)];

	ida_मुक्त(&bank->ida, cqn >> CQ_BANKID_SHIFT);

	mutex_lock(&cq_table->bank_mutex);
	bank->inuse--;
	mutex_unlock(&cq_table->bank_mutex);
पूर्ण

अटल पूर्णांक alloc_cqc(काष्ठा hns_roce_dev *hr_dev, काष्ठा hns_roce_cq *hr_cq)
अणु
	काष्ठा hns_roce_cq_table *cq_table = &hr_dev->cq_table;
	काष्ठा ib_device *ibdev = &hr_dev->ib_dev;
	काष्ठा hns_roce_cmd_mailbox *mailbox;
	u64 mtts[MTT_MIN_COUNT] = अणु 0 पूर्ण;
	dma_addr_t dma_handle;
	पूर्णांक ret;

	ret = hns_roce_mtr_find(hr_dev, &hr_cq->mtr, 0, mtts, ARRAY_SIZE(mtts),
				&dma_handle);
	अगर (!ret) अणु
		ibdev_err(ibdev, "failed to find CQ mtr, ret = %d.\n", ret);
		वापस -EINVAL;
	पूर्ण

	/* Get CQC memory HEM(Hardware Entry Memory) table */
	ret = hns_roce_table_get(hr_dev, &cq_table->table, hr_cq->cqn);
	अगर (ret) अणु
		ibdev_err(ibdev, "failed to get CQ(0x%lx) context, ret = %d.\n",
			  hr_cq->cqn, ret);
		जाओ err_out;
	पूर्ण

	ret = xa_err(xa_store(&cq_table->array, hr_cq->cqn, hr_cq, GFP_KERNEL));
	अगर (ret) अणु
		ibdev_err(ibdev, "failed to xa_store CQ, ret = %d.\n", ret);
		जाओ err_put;
	पूर्ण

	/* Allocate mailbox memory */
	mailbox = hns_roce_alloc_cmd_mailbox(hr_dev);
	अगर (IS_ERR(mailbox)) अणु
		ret = PTR_ERR(mailbox);
		जाओ err_xa;
	पूर्ण

	hr_dev->hw->ग_लिखो_cqc(hr_dev, hr_cq, mailbox->buf, mtts, dma_handle);

	/* Send mailbox to hw */
	ret = hns_roce_cmd_mbox(hr_dev, mailbox->dma, 0, hr_cq->cqn, 0,
			HNS_ROCE_CMD_CREATE_CQC, HNS_ROCE_CMD_TIMEOUT_MSECS);
	hns_roce_मुक्त_cmd_mailbox(hr_dev, mailbox);
	अगर (ret) अणु
		ibdev_err(ibdev,
			  "failed to send create cmd for CQ(0x%lx), ret = %d.\n",
			  hr_cq->cqn, ret);
		जाओ err_xa;
	पूर्ण

	hr_cq->cons_index = 0;
	hr_cq->arm_sn = 1;

	atomic_set(&hr_cq->refcount, 1);
	init_completion(&hr_cq->मुक्त);

	वापस 0;

err_xa:
	xa_erase(&cq_table->array, hr_cq->cqn);

err_put:
	hns_roce_table_put(hr_dev, &cq_table->table, hr_cq->cqn);

err_out:
	वापस ret;
पूर्ण

अटल व्योम मुक्त_cqc(काष्ठा hns_roce_dev *hr_dev, काष्ठा hns_roce_cq *hr_cq)
अणु
	काष्ठा hns_roce_cq_table *cq_table = &hr_dev->cq_table;
	काष्ठा device *dev = hr_dev->dev;
	पूर्णांक ret;

	ret = hns_roce_cmd_mbox(hr_dev, 0, 0, hr_cq->cqn, 1,
				HNS_ROCE_CMD_DESTROY_CQC,
				HNS_ROCE_CMD_TIMEOUT_MSECS);
	अगर (ret)
		dev_err(dev, "DESTROY_CQ failed (%d) for CQN %06lx\n", ret,
			hr_cq->cqn);

	xa_erase(&cq_table->array, hr_cq->cqn);

	/* Waiting पूर्णांकerrupt process procedure carried out */
	synchronize_irq(hr_dev->eq_table.eq[hr_cq->vector].irq);

	/* रुको क्रम all पूर्णांकerrupt processed */
	अगर (atomic_dec_and_test(&hr_cq->refcount))
		complete(&hr_cq->मुक्त);
	रुको_क्रम_completion(&hr_cq->मुक्त);

	hns_roce_table_put(hr_dev, &cq_table->table, hr_cq->cqn);
पूर्ण

अटल पूर्णांक alloc_cq_buf(काष्ठा hns_roce_dev *hr_dev, काष्ठा hns_roce_cq *hr_cq,
			काष्ठा ib_udata *udata, अचिन्हित दीर्घ addr)
अणु
	काष्ठा ib_device *ibdev = &hr_dev->ib_dev;
	काष्ठा hns_roce_buf_attr buf_attr = अणुपूर्ण;
	पूर्णांक ret;

	buf_attr.page_shअगरt = hr_dev->caps.cqe_buf_pg_sz + HNS_HW_PAGE_SHIFT;
	buf_attr.region[0].size = hr_cq->cq_depth * hr_cq->cqe_size;
	buf_attr.region[0].hopnum = hr_dev->caps.cqe_hop_num;
	buf_attr.region_count = 1;

	ret = hns_roce_mtr_create(hr_dev, &hr_cq->mtr, &buf_attr,
				  hr_dev->caps.cqe_ba_pg_sz + HNS_HW_PAGE_SHIFT,
				  udata, addr);
	अगर (ret)
		ibdev_err(ibdev, "failed to alloc CQ mtr, ret = %d.\n", ret);

	वापस ret;
पूर्ण

अटल व्योम मुक्त_cq_buf(काष्ठा hns_roce_dev *hr_dev, काष्ठा hns_roce_cq *hr_cq)
अणु
	hns_roce_mtr_destroy(hr_dev, &hr_cq->mtr);
पूर्ण

अटल पूर्णांक alloc_cq_db(काष्ठा hns_roce_dev *hr_dev, काष्ठा hns_roce_cq *hr_cq,
		       काष्ठा ib_udata *udata, अचिन्हित दीर्घ addr,
		       काष्ठा hns_roce_ib_create_cq_resp *resp)
अणु
	bool has_db = hr_dev->caps.flags & HNS_ROCE_CAP_FLAG_CQ_RECORD_DB;
	काष्ठा hns_roce_ucontext *uctx;
	पूर्णांक err;

	अगर (udata) अणु
		अगर (has_db &&
		    udata->outlen >= दुरत्वend(typeof(*resp), cap_flags)) अणु
			uctx = rdma_udata_to_drv_context(udata,
					काष्ठा hns_roce_ucontext, ibucontext);
			err = hns_roce_db_map_user(uctx, udata, addr,
						   &hr_cq->db);
			अगर (err)
				वापस err;
			hr_cq->flags |= HNS_ROCE_CQ_FLAG_RECORD_DB;
			resp->cap_flags |= HNS_ROCE_CQ_FLAG_RECORD_DB;
		पूर्ण
	पूर्ण अन्यथा अणु
		अगर (has_db) अणु
			err = hns_roce_alloc_db(hr_dev, &hr_cq->db, 1);
			अगर (err)
				वापस err;
			hr_cq->set_ci_db = hr_cq->db.db_record;
			*hr_cq->set_ci_db = 0;
			hr_cq->flags |= HNS_ROCE_CQ_FLAG_RECORD_DB;
		पूर्ण
		hr_cq->db_reg = hr_dev->reg_base + hr_dev->odb_offset +
				DB_REG_OFFSET * hr_dev->priv_uar.index;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम मुक्त_cq_db(काष्ठा hns_roce_dev *hr_dev, काष्ठा hns_roce_cq *hr_cq,
		       काष्ठा ib_udata *udata)
अणु
	काष्ठा hns_roce_ucontext *uctx;

	अगर (!(hr_cq->flags & HNS_ROCE_CQ_FLAG_RECORD_DB))
		वापस;

	hr_cq->flags &= ~HNS_ROCE_CQ_FLAG_RECORD_DB;
	अगर (udata) अणु
		uctx = rdma_udata_to_drv_context(udata,
						 काष्ठा hns_roce_ucontext,
						 ibucontext);
		hns_roce_db_unmap_user(uctx, &hr_cq->db);
	पूर्ण अन्यथा अणु
		hns_roce_मुक्त_db(hr_dev, &hr_cq->db);
	पूर्ण
पूर्ण

अटल पूर्णांक verअगरy_cq_create_attr(काष्ठा hns_roce_dev *hr_dev,
				 स्थिर काष्ठा ib_cq_init_attr *attr)
अणु
	काष्ठा ib_device *ibdev = &hr_dev->ib_dev;

	अगर (!attr->cqe || attr->cqe > hr_dev->caps.max_cqes) अणु
		ibdev_err(ibdev, "failed to check CQ count %u, max = %u.\n",
			  attr->cqe, hr_dev->caps.max_cqes);
		वापस -EINVAL;
	पूर्ण

	अगर (attr->comp_vector >= hr_dev->caps.num_comp_vectors) अणु
		ibdev_err(ibdev, "failed to check CQ vector = %u, max = %d.\n",
			  attr->comp_vector, hr_dev->caps.num_comp_vectors);
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक get_cq_ucmd(काष्ठा hns_roce_cq *hr_cq, काष्ठा ib_udata *udata,
		       काष्ठा hns_roce_ib_create_cq *ucmd)
अणु
	काष्ठा ib_device *ibdev = hr_cq->ib_cq.device;
	पूर्णांक ret;

	ret = ib_copy_from_udata(ucmd, udata, min(udata->inlen, माप(*ucmd)));
	अगर (ret) अणु
		ibdev_err(ibdev, "failed to copy CQ udata, ret = %d.\n", ret);
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम set_cq_param(काष्ठा hns_roce_cq *hr_cq, u32 cq_entries, पूर्णांक vector,
			 काष्ठा hns_roce_ib_create_cq *ucmd)
अणु
	काष्ठा hns_roce_dev *hr_dev = to_hr_dev(hr_cq->ib_cq.device);

	cq_entries = max(cq_entries, hr_dev->caps.min_cqes);
	cq_entries = roundup_घात_of_two(cq_entries);
	hr_cq->ib_cq.cqe = cq_entries - 1; /* used as cqe index */
	hr_cq->cq_depth = cq_entries;
	hr_cq->vector = vector;

	spin_lock_init(&hr_cq->lock);
	INIT_LIST_HEAD(&hr_cq->sq_list);
	INIT_LIST_HEAD(&hr_cq->rq_list);
पूर्ण

अटल व्योम set_cqe_size(काष्ठा hns_roce_cq *hr_cq, काष्ठा ib_udata *udata,
			 काष्ठा hns_roce_ib_create_cq *ucmd)
अणु
	काष्ठा hns_roce_dev *hr_dev = to_hr_dev(hr_cq->ib_cq.device);

	अगर (udata) अणु
		अगर (udata->inlen >= दुरत्वend(typeof(*ucmd), cqe_size))
			hr_cq->cqe_size = ucmd->cqe_size;
		अन्यथा
			hr_cq->cqe_size = HNS_ROCE_V2_CQE_SIZE;
	पूर्ण अन्यथा अणु
		hr_cq->cqe_size = hr_dev->caps.cqe_sz;
	पूर्ण
पूर्ण

पूर्णांक hns_roce_create_cq(काष्ठा ib_cq *ib_cq, स्थिर काष्ठा ib_cq_init_attr *attr,
		       काष्ठा ib_udata *udata)
अणु
	काष्ठा hns_roce_dev *hr_dev = to_hr_dev(ib_cq->device);
	काष्ठा hns_roce_ib_create_cq_resp resp = अणुपूर्ण;
	काष्ठा hns_roce_cq *hr_cq = to_hr_cq(ib_cq);
	काष्ठा ib_device *ibdev = &hr_dev->ib_dev;
	काष्ठा hns_roce_ib_create_cq ucmd = अणुपूर्ण;
	पूर्णांक ret;

	अगर (attr->flags)
		वापस -EOPNOTSUPP;

	ret = verअगरy_cq_create_attr(hr_dev, attr);
	अगर (ret)
		वापस ret;

	अगर (udata) अणु
		ret = get_cq_ucmd(hr_cq, udata, &ucmd);
		अगर (ret)
			वापस ret;
	पूर्ण

	set_cq_param(hr_cq, attr->cqe, attr->comp_vector, &ucmd);

	set_cqe_size(hr_cq, udata, &ucmd);

	ret = alloc_cq_buf(hr_dev, hr_cq, udata, ucmd.buf_addr);
	अगर (ret) अणु
		ibdev_err(ibdev, "failed to alloc CQ buf, ret = %d.\n", ret);
		वापस ret;
	पूर्ण

	ret = alloc_cq_db(hr_dev, hr_cq, udata, ucmd.db_addr, &resp);
	अगर (ret) अणु
		ibdev_err(ibdev, "failed to alloc CQ db, ret = %d.\n", ret);
		जाओ err_cq_buf;
	पूर्ण

	ret = alloc_cqn(hr_dev, hr_cq);
	अगर (ret) अणु
		ibdev_err(ibdev, "failed to alloc CQN, ret = %d.\n", ret);
		जाओ err_cq_db;
	पूर्ण

	ret = alloc_cqc(hr_dev, hr_cq);
	अगर (ret) अणु
		ibdev_err(ibdev,
			  "failed to alloc CQ context, ret = %d.\n", ret);
		जाओ err_cqn;
	पूर्ण

	/*
	 * For the QP created by kernel space, tptr value should be initialized
	 * to zero; For the QP created by user space, it will cause synchronous
	 * problems अगर tptr is set to zero here, so we initialize it in user
	 * space.
	 */
	अगर (!udata && hr_cq->tptr_addr)
		*hr_cq->tptr_addr = 0;

	अगर (udata) अणु
		resp.cqn = hr_cq->cqn;
		ret = ib_copy_to_udata(udata, &resp,
				       min(udata->outlen, माप(resp)));
		अगर (ret)
			जाओ err_cqc;
	पूर्ण

	वापस 0;

err_cqc:
	मुक्त_cqc(hr_dev, hr_cq);
err_cqn:
	मुक्त_cqn(hr_dev, hr_cq->cqn);
err_cq_db:
	मुक्त_cq_db(hr_dev, hr_cq, udata);
err_cq_buf:
	मुक्त_cq_buf(hr_dev, hr_cq);
	वापस ret;
पूर्ण

पूर्णांक hns_roce_destroy_cq(काष्ठा ib_cq *ib_cq, काष्ठा ib_udata *udata)
अणु
	काष्ठा hns_roce_dev *hr_dev = to_hr_dev(ib_cq->device);
	काष्ठा hns_roce_cq *hr_cq = to_hr_cq(ib_cq);

	अगर (hr_dev->hw->destroy_cq)
		hr_dev->hw->destroy_cq(ib_cq, udata);

	मुक्त_cqc(hr_dev, hr_cq);
	मुक्त_cqn(hr_dev, hr_cq->cqn);
	मुक्त_cq_db(hr_dev, hr_cq, udata);
	मुक्त_cq_buf(hr_dev, hr_cq);

	वापस 0;
पूर्ण

व्योम hns_roce_cq_completion(काष्ठा hns_roce_dev *hr_dev, u32 cqn)
अणु
	काष्ठा hns_roce_cq *hr_cq;
	काष्ठा ib_cq *ibcq;

	hr_cq = xa_load(&hr_dev->cq_table.array,
			cqn & (hr_dev->caps.num_cqs - 1));
	अगर (!hr_cq) अणु
		dev_warn(hr_dev->dev, "Completion event for bogus CQ 0x%06x\n",
			 cqn);
		वापस;
	पूर्ण

	++hr_cq->arm_sn;
	ibcq = &hr_cq->ib_cq;
	अगर (ibcq->comp_handler)
		ibcq->comp_handler(ibcq, ibcq->cq_context);
पूर्ण

व्योम hns_roce_cq_event(काष्ठा hns_roce_dev *hr_dev, u32 cqn, पूर्णांक event_type)
अणु
	काष्ठा device *dev = hr_dev->dev;
	काष्ठा hns_roce_cq *hr_cq;
	काष्ठा ib_event event;
	काष्ठा ib_cq *ibcq;

	hr_cq = xa_load(&hr_dev->cq_table.array,
			cqn & (hr_dev->caps.num_cqs - 1));
	अगर (!hr_cq) अणु
		dev_warn(dev, "Async event for bogus CQ 0x%06x\n", cqn);
		वापस;
	पूर्ण

	अगर (event_type != HNS_ROCE_EVENT_TYPE_CQ_ID_INVALID &&
	    event_type != HNS_ROCE_EVENT_TYPE_CQ_ACCESS_ERROR &&
	    event_type != HNS_ROCE_EVENT_TYPE_CQ_OVERFLOW) अणु
		dev_err(dev, "Unexpected event type 0x%x on CQ 0x%06x\n",
			event_type, cqn);
		वापस;
	पूर्ण

	atomic_inc(&hr_cq->refcount);

	ibcq = &hr_cq->ib_cq;
	अगर (ibcq->event_handler) अणु
		event.device = ibcq->device;
		event.element.cq = ibcq;
		event.event = IB_EVENT_CQ_ERR;
		ibcq->event_handler(&event, ibcq->cq_context);
	पूर्ण

	अगर (atomic_dec_and_test(&hr_cq->refcount))
		complete(&hr_cq->मुक्त);
पूर्ण

व्योम hns_roce_init_cq_table(काष्ठा hns_roce_dev *hr_dev)
अणु
	काष्ठा hns_roce_cq_table *cq_table = &hr_dev->cq_table;
	अचिन्हित पूर्णांक reserved_from_bot;
	अचिन्हित पूर्णांक i;

	mutex_init(&cq_table->bank_mutex);
	xa_init(&cq_table->array);

	reserved_from_bot = hr_dev->caps.reserved_cqs;

	क्रम (i = 0; i < reserved_from_bot; i++) अणु
		cq_table->bank[get_cq_bankid(i)].inuse++;
		cq_table->bank[get_cq_bankid(i)].min++;
	पूर्ण

	क्रम (i = 0; i < HNS_ROCE_CQ_BANK_NUM; i++) अणु
		ida_init(&cq_table->bank[i].ida);
		cq_table->bank[i].max = hr_dev->caps.num_cqs /
					HNS_ROCE_CQ_BANK_NUM - 1;
	पूर्ण
पूर्ण

व्योम hns_roce_cleanup_cq_table(काष्ठा hns_roce_dev *hr_dev)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < HNS_ROCE_CQ_BANK_NUM; i++)
		ida_destroy(&hr_dev->cq_table.bank[i].ida);
पूर्ण
