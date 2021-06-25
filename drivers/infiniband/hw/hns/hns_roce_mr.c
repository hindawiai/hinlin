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

#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/vदो_स्मृति.h>
#समावेश <rdma/ib_uस्मृति.स>
#समावेश "hns_roce_device.h"
#समावेश "hns_roce_cmd.h"
#समावेश "hns_roce_hem.h"

अटल u32 hw_index_to_key(अचिन्हित दीर्घ ind)
अणु
	वापस (u32)(ind >> 24) | (ind << 8);
पूर्ण

अचिन्हित दीर्घ key_to_hw_index(u32 key)
अणु
	वापस (key << 24) | (key >> 8);
पूर्ण

अटल पूर्णांक hns_roce_hw_create_mpt(काष्ठा hns_roce_dev *hr_dev,
				  काष्ठा hns_roce_cmd_mailbox *mailbox,
				  अचिन्हित दीर्घ mpt_index)
अणु
	वापस hns_roce_cmd_mbox(hr_dev, mailbox->dma, 0, mpt_index, 0,
				 HNS_ROCE_CMD_CREATE_MPT,
				 HNS_ROCE_CMD_TIMEOUT_MSECS);
पूर्ण

पूर्णांक hns_roce_hw_destroy_mpt(काष्ठा hns_roce_dev *hr_dev,
			    काष्ठा hns_roce_cmd_mailbox *mailbox,
			    अचिन्हित दीर्घ mpt_index)
अणु
	वापस hns_roce_cmd_mbox(hr_dev, 0, mailbox ? mailbox->dma : 0,
				 mpt_index, !mailbox, HNS_ROCE_CMD_DESTROY_MPT,
				 HNS_ROCE_CMD_TIMEOUT_MSECS);
पूर्ण

अटल पूर्णांक alloc_mr_key(काष्ठा hns_roce_dev *hr_dev, काष्ठा hns_roce_mr *mr)
अणु
	काष्ठा ib_device *ibdev = &hr_dev->ib_dev;
	अचिन्हित दीर्घ obj = 0;
	पूर्णांक err;

	/* Allocate a key क्रम mr from mr_table */
	err = hns_roce_biपंचांगap_alloc(&hr_dev->mr_table.mtpt_biपंचांगap, &obj);
	अगर (err) अणु
		ibdev_err(ibdev,
			  "failed to alloc bitmap for MR key, ret = %d.\n",
			  err);
		वापस -ENOMEM;
	पूर्ण

	mr->key = hw_index_to_key(obj);		/* MR key */

	err = hns_roce_table_get(hr_dev, &hr_dev->mr_table.mtpt_table, obj);
	अगर (err) अणु
		ibdev_err(ibdev, "failed to alloc mtpt, ret = %d.\n", err);
		जाओ err_मुक्त_biपंचांगap;
	पूर्ण

	वापस 0;
err_मुक्त_biपंचांगap:
	hns_roce_biपंचांगap_मुक्त(&hr_dev->mr_table.mtpt_biपंचांगap, obj, BITMAP_NO_RR);
	वापस err;
पूर्ण

अटल व्योम मुक्त_mr_key(काष्ठा hns_roce_dev *hr_dev, काष्ठा hns_roce_mr *mr)
अणु
	अचिन्हित दीर्घ obj = key_to_hw_index(mr->key);

	hns_roce_table_put(hr_dev, &hr_dev->mr_table.mtpt_table, obj);
	hns_roce_biपंचांगap_मुक्त(&hr_dev->mr_table.mtpt_biपंचांगap, obj, BITMAP_NO_RR);
पूर्ण

अटल पूर्णांक alloc_mr_pbl(काष्ठा hns_roce_dev *hr_dev, काष्ठा hns_roce_mr *mr,
			काष्ठा ib_udata *udata, u64 start)
अणु
	काष्ठा ib_device *ibdev = &hr_dev->ib_dev;
	bool is_fast = mr->type == MR_TYPE_FRMR;
	काष्ठा hns_roce_buf_attr buf_attr = अणुपूर्ण;
	पूर्णांक err;

	mr->pbl_hop_num = is_fast ? 1 : hr_dev->caps.pbl_hop_num;
	buf_attr.page_shअगरt = is_fast ? PAGE_SHIFT :
			      hr_dev->caps.pbl_buf_pg_sz + PAGE_SHIFT;
	buf_attr.region[0].size = mr->size;
	buf_attr.region[0].hopnum = mr->pbl_hop_num;
	buf_attr.region_count = 1;
	buf_attr.user_access = mr->access;
	/* fast MR's buffer is alloced beक्रमe mapping, not at creation */
	buf_attr.mtt_only = is_fast;

	err = hns_roce_mtr_create(hr_dev, &mr->pbl_mtr, &buf_attr,
				  hr_dev->caps.pbl_ba_pg_sz + HNS_HW_PAGE_SHIFT,
				  udata, start);
	अगर (err)
		ibdev_err(ibdev, "failed to alloc pbl mtr, ret = %d.\n", err);
	अन्यथा
		mr->npages = mr->pbl_mtr.hem_cfg.buf_pg_count;

	वापस err;
पूर्ण

अटल व्योम मुक्त_mr_pbl(काष्ठा hns_roce_dev *hr_dev, काष्ठा hns_roce_mr *mr)
अणु
	hns_roce_mtr_destroy(hr_dev, &mr->pbl_mtr);
पूर्ण

अटल व्योम hns_roce_mr_मुक्त(काष्ठा hns_roce_dev *hr_dev,
			     काष्ठा hns_roce_mr *mr)
अणु
	काष्ठा ib_device *ibdev = &hr_dev->ib_dev;
	पूर्णांक ret;

	अगर (mr->enabled) अणु
		ret = hns_roce_hw_destroy_mpt(hr_dev, शून्य,
					      key_to_hw_index(mr->key) &
					      (hr_dev->caps.num_mtpts - 1));
		अगर (ret)
			ibdev_warn(ibdev, "failed to destroy mpt, ret = %d.\n",
				   ret);
	पूर्ण

	मुक्त_mr_pbl(hr_dev, mr);
	मुक्त_mr_key(hr_dev, mr);
पूर्ण

अटल पूर्णांक hns_roce_mr_enable(काष्ठा hns_roce_dev *hr_dev,
			      काष्ठा hns_roce_mr *mr)
अणु
	अचिन्हित दीर्घ mtpt_idx = key_to_hw_index(mr->key);
	काष्ठा hns_roce_cmd_mailbox *mailbox;
	काष्ठा device *dev = hr_dev->dev;
	पूर्णांक ret;

	/* Allocate mailbox memory */
	mailbox = hns_roce_alloc_cmd_mailbox(hr_dev);
	अगर (IS_ERR(mailbox)) अणु
		ret = PTR_ERR(mailbox);
		वापस ret;
	पूर्ण

	अगर (mr->type != MR_TYPE_FRMR)
		ret = hr_dev->hw->ग_लिखो_mtpt(hr_dev, mailbox->buf, mr,
					     mtpt_idx);
	अन्यथा
		ret = hr_dev->hw->frmr_ग_लिखो_mtpt(hr_dev, mailbox->buf, mr);
	अगर (ret) अणु
		dev_err(dev, "failed to write mtpt, ret = %d.\n", ret);
		जाओ err_page;
	पूर्ण

	ret = hns_roce_hw_create_mpt(hr_dev, mailbox,
				     mtpt_idx & (hr_dev->caps.num_mtpts - 1));
	अगर (ret) अणु
		dev_err(dev, "failed to create mpt, ret = %d.\n", ret);
		जाओ err_page;
	पूर्ण

	mr->enabled = 1;

err_page:
	hns_roce_मुक्त_cmd_mailbox(hr_dev, mailbox);

	वापस ret;
पूर्ण

पूर्णांक hns_roce_init_mr_table(काष्ठा hns_roce_dev *hr_dev)
अणु
	काष्ठा hns_roce_mr_table *mr_table = &hr_dev->mr_table;
	पूर्णांक ret;

	ret = hns_roce_biपंचांगap_init(&mr_table->mtpt_biपंचांगap,
				   hr_dev->caps.num_mtpts,
				   hr_dev->caps.num_mtpts - 1,
				   hr_dev->caps.reserved_mrws, 0);
	वापस ret;
पूर्ण

व्योम hns_roce_cleanup_mr_table(काष्ठा hns_roce_dev *hr_dev)
अणु
	काष्ठा hns_roce_mr_table *mr_table = &hr_dev->mr_table;

	hns_roce_biपंचांगap_cleanup(&mr_table->mtpt_biपंचांगap);
पूर्ण

काष्ठा ib_mr *hns_roce_get_dma_mr(काष्ठा ib_pd *pd, पूर्णांक acc)
अणु
	काष्ठा hns_roce_dev *hr_dev = to_hr_dev(pd->device);
	काष्ठा hns_roce_mr *mr;
	पूर्णांक ret;

	mr = kzalloc(माप(*mr), GFP_KERNEL);
	अगर (mr == शून्य)
		वापस  ERR_PTR(-ENOMEM);

	mr->type = MR_TYPE_DMA;
	mr->pd = to_hr_pd(pd)->pdn;
	mr->access = acc;

	/* Allocate memory region key */
	hns_roce_hem_list_init(&mr->pbl_mtr.hem_list);
	ret = alloc_mr_key(hr_dev, mr);
	अगर (ret)
		जाओ err_मुक्त;

	ret = hns_roce_mr_enable(hr_dev, mr);
	अगर (ret)
		जाओ err_mr;

	mr->ibmr.rkey = mr->ibmr.lkey = mr->key;

	वापस &mr->ibmr;
err_mr:
	मुक्त_mr_key(hr_dev, mr);

err_मुक्त:
	kमुक्त(mr);
	वापस ERR_PTR(ret);
पूर्ण

काष्ठा ib_mr *hns_roce_reg_user_mr(काष्ठा ib_pd *pd, u64 start, u64 length,
				   u64 virt_addr, पूर्णांक access_flags,
				   काष्ठा ib_udata *udata)
अणु
	काष्ठा hns_roce_dev *hr_dev = to_hr_dev(pd->device);
	काष्ठा hns_roce_mr *mr;
	पूर्णांक ret;

	mr = kzalloc(माप(*mr), GFP_KERNEL);
	अगर (!mr)
		वापस ERR_PTR(-ENOMEM);

	mr->iova = virt_addr;
	mr->size = length;
	mr->pd = to_hr_pd(pd)->pdn;
	mr->access = access_flags;
	mr->type = MR_TYPE_MR;

	ret = alloc_mr_key(hr_dev, mr);
	अगर (ret)
		जाओ err_alloc_mr;

	ret = alloc_mr_pbl(hr_dev, mr, udata, start);
	अगर (ret)
		जाओ err_alloc_key;

	ret = hns_roce_mr_enable(hr_dev, mr);
	अगर (ret)
		जाओ err_alloc_pbl;

	mr->ibmr.rkey = mr->ibmr.lkey = mr->key;
	mr->ibmr.length = length;

	वापस &mr->ibmr;

err_alloc_pbl:
	मुक्त_mr_pbl(hr_dev, mr);
err_alloc_key:
	मुक्त_mr_key(hr_dev, mr);
err_alloc_mr:
	kमुक्त(mr);
	वापस ERR_PTR(ret);
पूर्ण

काष्ठा ib_mr *hns_roce_rereg_user_mr(काष्ठा ib_mr *ibmr, पूर्णांक flags, u64 start,
				     u64 length, u64 virt_addr,
				     पूर्णांक mr_access_flags, काष्ठा ib_pd *pd,
				     काष्ठा ib_udata *udata)
अणु
	काष्ठा hns_roce_dev *hr_dev = to_hr_dev(ibmr->device);
	काष्ठा ib_device *ib_dev = &hr_dev->ib_dev;
	काष्ठा hns_roce_mr *mr = to_hr_mr(ibmr);
	काष्ठा hns_roce_cmd_mailbox *mailbox;
	अचिन्हित दीर्घ mtpt_idx;
	पूर्णांक ret;

	अगर (!mr->enabled)
		वापस ERR_PTR(-EINVAL);

	mailbox = hns_roce_alloc_cmd_mailbox(hr_dev);
	अगर (IS_ERR(mailbox))
		वापस ERR_CAST(mailbox);

	mtpt_idx = key_to_hw_index(mr->key) & (hr_dev->caps.num_mtpts - 1);
	ret = hns_roce_cmd_mbox(hr_dev, 0, mailbox->dma, mtpt_idx, 0,
				HNS_ROCE_CMD_QUERY_MPT,
				HNS_ROCE_CMD_TIMEOUT_MSECS);
	अगर (ret)
		जाओ मुक्त_cmd_mbox;

	ret = hns_roce_hw_destroy_mpt(hr_dev, शून्य, mtpt_idx);
	अगर (ret)
		ibdev_warn(ib_dev, "failed to destroy MPT, ret = %d.\n", ret);

	mr->enabled = 0;
	mr->iova = virt_addr;
	mr->size = length;

	अगर (flags & IB_MR_REREG_PD)
		mr->pd = to_hr_pd(pd)->pdn;

	अगर (flags & IB_MR_REREG_ACCESS)
		mr->access = mr_access_flags;

	अगर (flags & IB_MR_REREG_TRANS) अणु
		मुक्त_mr_pbl(hr_dev, mr);
		ret = alloc_mr_pbl(hr_dev, mr, udata, start);
		अगर (ret) अणु
			ibdev_err(ib_dev, "failed to alloc mr PBL, ret = %d.\n",
				  ret);
			जाओ मुक्त_cmd_mbox;
		पूर्ण
	पूर्ण

	ret = hr_dev->hw->rereg_ग_लिखो_mtpt(hr_dev, mr, flags, mailbox->buf);
	अगर (ret) अणु
		ibdev_err(ib_dev, "failed to write mtpt, ret = %d.\n", ret);
		जाओ मुक्त_cmd_mbox;
	पूर्ण

	ret = hns_roce_hw_create_mpt(hr_dev, mailbox, mtpt_idx);
	अगर (ret) अणु
		ibdev_err(ib_dev, "failed to create MPT, ret = %d.\n", ret);
		जाओ मुक्त_cmd_mbox;
	पूर्ण

	mr->enabled = 1;

मुक्त_cmd_mbox:
	hns_roce_मुक्त_cmd_mailbox(hr_dev, mailbox);

	वापस ERR_PTR(ret);
पूर्ण

पूर्णांक hns_roce_dereg_mr(काष्ठा ib_mr *ibmr, काष्ठा ib_udata *udata)
अणु
	काष्ठा hns_roce_dev *hr_dev = to_hr_dev(ibmr->device);
	काष्ठा hns_roce_mr *mr = to_hr_mr(ibmr);
	पूर्णांक ret = 0;

	अगर (hr_dev->hw->dereg_mr) अणु
		ret = hr_dev->hw->dereg_mr(hr_dev, mr, udata);
	पूर्ण अन्यथा अणु
		hns_roce_mr_मुक्त(hr_dev, mr);
		kमुक्त(mr);
	पूर्ण

	वापस ret;
पूर्ण

काष्ठा ib_mr *hns_roce_alloc_mr(काष्ठा ib_pd *pd, क्रमागत ib_mr_type mr_type,
				u32 max_num_sg)
अणु
	काष्ठा hns_roce_dev *hr_dev = to_hr_dev(pd->device);
	काष्ठा device *dev = hr_dev->dev;
	काष्ठा hns_roce_mr *mr;
	पूर्णांक ret;

	अगर (mr_type != IB_MR_TYPE_MEM_REG)
		वापस ERR_PTR(-EINVAL);

	अगर (max_num_sg > HNS_ROCE_FRMR_MAX_PA) अणु
		dev_err(dev, "max_num_sg larger than %d\n",
			HNS_ROCE_FRMR_MAX_PA);
		वापस ERR_PTR(-EINVAL);
	पूर्ण

	mr = kzalloc(माप(*mr), GFP_KERNEL);
	अगर (!mr)
		वापस ERR_PTR(-ENOMEM);

	mr->type = MR_TYPE_FRMR;
	mr->pd = to_hr_pd(pd)->pdn;
	mr->size = max_num_sg * (1 << PAGE_SHIFT);

	/* Allocate memory region key */
	ret = alloc_mr_key(hr_dev, mr);
	अगर (ret)
		जाओ err_मुक्त;

	ret = alloc_mr_pbl(hr_dev, mr, शून्य, 0);
	अगर (ret)
		जाओ err_key;

	ret = hns_roce_mr_enable(hr_dev, mr);
	अगर (ret)
		जाओ err_pbl;

	mr->ibmr.rkey = mr->ibmr.lkey = mr->key;
	mr->ibmr.length = mr->size;

	वापस &mr->ibmr;

err_key:
	मुक्त_mr_key(hr_dev, mr);
err_pbl:
	मुक्त_mr_pbl(hr_dev, mr);
err_मुक्त:
	kमुक्त(mr);
	वापस ERR_PTR(ret);
पूर्ण

अटल पूर्णांक hns_roce_set_page(काष्ठा ib_mr *ibmr, u64 addr)
अणु
	काष्ठा hns_roce_mr *mr = to_hr_mr(ibmr);

	अगर (likely(mr->npages < mr->pbl_mtr.hem_cfg.buf_pg_count)) अणु
		mr->page_list[mr->npages++] = addr;
		वापस 0;
	पूर्ण

	वापस -ENOBUFS;
पूर्ण

पूर्णांक hns_roce_map_mr_sg(काष्ठा ib_mr *ibmr, काष्ठा scatterlist *sg, पूर्णांक sg_nents,
		       अचिन्हित पूर्णांक *sg_offset)
अणु
	काष्ठा hns_roce_dev *hr_dev = to_hr_dev(ibmr->device);
	काष्ठा ib_device *ibdev = &hr_dev->ib_dev;
	काष्ठा hns_roce_mr *mr = to_hr_mr(ibmr);
	काष्ठा hns_roce_mtr *mtr = &mr->pbl_mtr;
	पूर्णांक ret = 0;

	mr->npages = 0;
	mr->page_list = kvसुस्मृति(mr->pbl_mtr.hem_cfg.buf_pg_count,
				 माप(dma_addr_t), GFP_KERNEL);
	अगर (!mr->page_list)
		वापस ret;

	ret = ib_sg_to_pages(ibmr, sg, sg_nents, sg_offset, hns_roce_set_page);
	अगर (ret < 1) अणु
		ibdev_err(ibdev, "failed to store sg pages %u %u, cnt = %d.\n",
			  mr->npages, mr->pbl_mtr.hem_cfg.buf_pg_count, ret);
		जाओ err_page_list;
	पूर्ण

	mtr->hem_cfg.region[0].offset = 0;
	mtr->hem_cfg.region[0].count = mr->npages;
	mtr->hem_cfg.region[0].hopnum = mr->pbl_hop_num;
	mtr->hem_cfg.region_count = 1;
	ret = hns_roce_mtr_map(hr_dev, mtr, mr->page_list, mr->npages);
	अगर (ret) अणु
		ibdev_err(ibdev, "failed to map sg mtr, ret = %d.\n", ret);
		ret = 0;
	पूर्ण अन्यथा अणु
		mr->pbl_mtr.hem_cfg.buf_pg_shअगरt = (u32)ilog2(ibmr->page_size);
		ret = mr->npages;
	पूर्ण

err_page_list:
	kvमुक्त(mr->page_list);
	mr->page_list = शून्य;

	वापस ret;
पूर्ण

अटल व्योम hns_roce_mw_मुक्त(काष्ठा hns_roce_dev *hr_dev,
			     काष्ठा hns_roce_mw *mw)
अणु
	काष्ठा device *dev = hr_dev->dev;
	पूर्णांक ret;

	अगर (mw->enabled) अणु
		ret = hns_roce_hw_destroy_mpt(hr_dev, शून्य,
					      key_to_hw_index(mw->rkey) &
					      (hr_dev->caps.num_mtpts - 1));
		अगर (ret)
			dev_warn(dev, "MW DESTROY_MPT failed (%d)\n", ret);

		hns_roce_table_put(hr_dev, &hr_dev->mr_table.mtpt_table,
				   key_to_hw_index(mw->rkey));
	पूर्ण

	hns_roce_biपंचांगap_मुक्त(&hr_dev->mr_table.mtpt_biपंचांगap,
			     key_to_hw_index(mw->rkey), BITMAP_NO_RR);
पूर्ण

अटल पूर्णांक hns_roce_mw_enable(काष्ठा hns_roce_dev *hr_dev,
			      काष्ठा hns_roce_mw *mw)
अणु
	काष्ठा hns_roce_mr_table *mr_table = &hr_dev->mr_table;
	काष्ठा hns_roce_cmd_mailbox *mailbox;
	काष्ठा device *dev = hr_dev->dev;
	अचिन्हित दीर्घ mtpt_idx = key_to_hw_index(mw->rkey);
	पूर्णांक ret;

	/* prepare HEM entry memory */
	ret = hns_roce_table_get(hr_dev, &mr_table->mtpt_table, mtpt_idx);
	अगर (ret)
		वापस ret;

	mailbox = hns_roce_alloc_cmd_mailbox(hr_dev);
	अगर (IS_ERR(mailbox)) अणु
		ret = PTR_ERR(mailbox);
		जाओ err_table;
	पूर्ण

	ret = hr_dev->hw->mw_ग_लिखो_mtpt(mailbox->buf, mw);
	अगर (ret) अणु
		dev_err(dev, "MW write mtpt fail!\n");
		जाओ err_page;
	पूर्ण

	ret = hns_roce_hw_create_mpt(hr_dev, mailbox,
				     mtpt_idx & (hr_dev->caps.num_mtpts - 1));
	अगर (ret) अणु
		dev_err(dev, "MW CREATE_MPT failed (%d)\n", ret);
		जाओ err_page;
	पूर्ण

	mw->enabled = 1;

	hns_roce_मुक्त_cmd_mailbox(hr_dev, mailbox);

	वापस 0;

err_page:
	hns_roce_मुक्त_cmd_mailbox(hr_dev, mailbox);

err_table:
	hns_roce_table_put(hr_dev, &mr_table->mtpt_table, mtpt_idx);

	वापस ret;
पूर्ण

पूर्णांक hns_roce_alloc_mw(काष्ठा ib_mw *ibmw, काष्ठा ib_udata *udata)
अणु
	काष्ठा hns_roce_dev *hr_dev = to_hr_dev(ibmw->device);
	काष्ठा hns_roce_mw *mw = to_hr_mw(ibmw);
	अचिन्हित दीर्घ index = 0;
	पूर्णांक ret;

	/* Allocate a key क्रम mw from biपंचांगap */
	ret = hns_roce_biपंचांगap_alloc(&hr_dev->mr_table.mtpt_biपंचांगap, &index);
	अगर (ret)
		वापस ret;

	mw->rkey = hw_index_to_key(index);

	ibmw->rkey = mw->rkey;
	mw->pdn = to_hr_pd(ibmw->pd)->pdn;
	mw->pbl_hop_num = hr_dev->caps.pbl_hop_num;
	mw->pbl_ba_pg_sz = hr_dev->caps.pbl_ba_pg_sz;
	mw->pbl_buf_pg_sz = hr_dev->caps.pbl_buf_pg_sz;

	ret = hns_roce_mw_enable(hr_dev, mw);
	अगर (ret)
		जाओ err_mw;

	वापस 0;

err_mw:
	hns_roce_mw_मुक्त(hr_dev, mw);
	वापस ret;
पूर्ण

पूर्णांक hns_roce_dealloc_mw(काष्ठा ib_mw *ibmw)
अणु
	काष्ठा hns_roce_dev *hr_dev = to_hr_dev(ibmw->device);
	काष्ठा hns_roce_mw *mw = to_hr_mw(ibmw);

	hns_roce_mw_मुक्त(hr_dev, mw);
	वापस 0;
पूर्ण

अटल पूर्णांक mtr_map_region(काष्ठा hns_roce_dev *hr_dev, काष्ठा hns_roce_mtr *mtr,
			  काष्ठा hns_roce_buf_region *region, dma_addr_t *pages,
			  पूर्णांक max_count)
अणु
	पूर्णांक count, npage;
	पूर्णांक offset, end;
	__le64 *mtts;
	u64 addr;
	पूर्णांक i;

	offset = region->offset;
	end = offset + region->count;
	npage = 0;
	जबतक (offset < end && npage < max_count) अणु
		count = 0;
		mtts = hns_roce_hem_list_find_mtt(hr_dev, &mtr->hem_list,
						  offset, &count, शून्य);
		अगर (!mtts)
			वापस -ENOBUFS;

		क्रम (i = 0; i < count && npage < max_count; i++) अणु
			अगर (hr_dev->hw_rev == HNS_ROCE_HW_VER1)
				addr = to_hr_hw_page_addr(pages[npage]);
			अन्यथा
				addr = pages[npage];

			mtts[i] = cpu_to_le64(addr);
			npage++;
		पूर्ण
		offset += count;
	पूर्ण

	वापस npage;
पूर्ण

अटल अंतरभूत bool mtr_has_mtt(काष्ठा hns_roce_buf_attr *attr)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < attr->region_count; i++)
		अगर (attr->region[i].hopnum != HNS_ROCE_HOP_NUM_0 &&
		    attr->region[i].hopnum > 0)
			वापस true;

	/* because the mtr only one root base address, when hopnum is 0 means
	 * root base address equals the first buffer address, thus all alloced
	 * memory must in a continuous space accessed by direct mode.
	 */
	वापस false;
पूर्ण

अटल अंतरभूत माप_प्रकार mtr_bufs_size(काष्ठा hns_roce_buf_attr *attr)
अणु
	माप_प्रकार size = 0;
	पूर्णांक i;

	क्रम (i = 0; i < attr->region_count; i++)
		size += attr->region[i].size;

	वापस size;
पूर्ण

/*
 * check the given pages in continuous address space
 * Returns 0 on success, or the error page num.
 */
अटल अंतरभूत पूर्णांक mtr_check_direct_pages(dma_addr_t *pages, पूर्णांक page_count,
					 अचिन्हित पूर्णांक page_shअगरt)
अणु
	माप_प्रकार page_size = 1 << page_shअगरt;
	पूर्णांक i;

	क्रम (i = 1; i < page_count; i++)
		अगर (pages[i] - pages[i - 1] != page_size)
			वापस i;

	वापस 0;
पूर्ण

अटल व्योम mtr_मुक्त_bufs(काष्ठा hns_roce_dev *hr_dev, काष्ठा hns_roce_mtr *mtr)
अणु
	/* release user buffers */
	अगर (mtr->umem) अणु
		ib_umem_release(mtr->umem);
		mtr->umem = शून्य;
	पूर्ण

	/* release kernel buffers */
	अगर (mtr->kmem) अणु
		hns_roce_buf_मुक्त(hr_dev, mtr->kmem);
		mtr->kmem = शून्य;
	पूर्ण
पूर्ण

अटल पूर्णांक mtr_alloc_bufs(काष्ठा hns_roce_dev *hr_dev, काष्ठा hns_roce_mtr *mtr,
			  काष्ठा hns_roce_buf_attr *buf_attr,
			  काष्ठा ib_udata *udata, अचिन्हित दीर्घ user_addr)
अणु
	काष्ठा ib_device *ibdev = &hr_dev->ib_dev;
	माप_प्रकार total_size;

	total_size = mtr_bufs_size(buf_attr);

	अगर (udata) अणु
		mtr->kmem = शून्य;
		mtr->umem = ib_umem_get(ibdev, user_addr, total_size,
					buf_attr->user_access);
		अगर (IS_ERR_OR_शून्य(mtr->umem)) अणु
			ibdev_err(ibdev, "failed to get umem, ret = %ld.\n",
				  PTR_ERR(mtr->umem));
			वापस -ENOMEM;
		पूर्ण
	पूर्ण अन्यथा अणु
		mtr->umem = शून्य;
		mtr->kmem = hns_roce_buf_alloc(hr_dev, total_size,
					       buf_attr->page_shअगरt,
					       mtr->hem_cfg.is_direct ?
					       HNS_ROCE_BUF_सूचीECT : 0);
		अगर (IS_ERR(mtr->kmem)) अणु
			ibdev_err(ibdev, "failed to alloc kmem, ret = %ld.\n",
				  PTR_ERR(mtr->kmem));
			वापस PTR_ERR(mtr->kmem);
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक mtr_map_bufs(काष्ठा hns_roce_dev *hr_dev, काष्ठा hns_roce_mtr *mtr,
			पूर्णांक page_count, अचिन्हित पूर्णांक page_shअगरt)
अणु
	काष्ठा ib_device *ibdev = &hr_dev->ib_dev;
	dma_addr_t *pages;
	पूर्णांक npage;
	पूर्णांक ret;

	/* alloc a पंचांगp array to store buffer's dma address */
	pages = kvसुस्मृति(page_count, माप(dma_addr_t), GFP_KERNEL);
	अगर (!pages)
		वापस -ENOMEM;

	अगर (mtr->umem)
		npage = hns_roce_get_umem_bufs(hr_dev, pages, page_count, 0,
					       mtr->umem, page_shअगरt);
	अन्यथा
		npage = hns_roce_get_kmem_bufs(hr_dev, pages, page_count, 0,
					       mtr->kmem);

	अगर (npage != page_count) अणु
		ibdev_err(ibdev, "failed to get mtr page %d != %d.\n", npage,
			  page_count);
		ret = -ENOBUFS;
		जाओ err_alloc_list;
	पूर्ण

	अगर (mtr->hem_cfg.is_direct && npage > 1) अणु
		ret = mtr_check_direct_pages(pages, npage, page_shअगरt);
		अगर (ret) अणु
			ibdev_err(ibdev, "failed to check %s mtr, idx = %d.\n",
				  mtr->umem ? "user" : "kernel", ret);
			ret = -ENOBUFS;
			जाओ err_alloc_list;
		पूर्ण
	पूर्ण

	ret = hns_roce_mtr_map(hr_dev, mtr, pages, page_count);
	अगर (ret)
		ibdev_err(ibdev, "failed to map mtr pages, ret = %d.\n", ret);

err_alloc_list:
	kvमुक्त(pages);

	वापस ret;
पूर्ण

पूर्णांक hns_roce_mtr_map(काष्ठा hns_roce_dev *hr_dev, काष्ठा hns_roce_mtr *mtr,
		     dma_addr_t *pages, अचिन्हित पूर्णांक page_cnt)
अणु
	काष्ठा ib_device *ibdev = &hr_dev->ib_dev;
	काष्ठा hns_roce_buf_region *r;
	अचिन्हित पूर्णांक i, mapped_cnt;
	पूर्णांक ret;

	/*
	 * Only use the first page address as root ba when hopnum is 0, this
	 * is because the addresses of all pages are consecutive in this हाल.
	 */
	अगर (mtr->hem_cfg.is_direct) अणु
		mtr->hem_cfg.root_ba = pages[0];
		वापस 0;
	पूर्ण

	क्रम (i = 0, mapped_cnt = 0; i < mtr->hem_cfg.region_count &&
	     mapped_cnt < page_cnt; i++) अणु
		r = &mtr->hem_cfg.region[i];
		/* अगर hopnum is 0, no need to map pages in this region */
		अगर (!r->hopnum) अणु
			mapped_cnt += r->count;
			जारी;
		पूर्ण

		अगर (r->offset + r->count > page_cnt) अणु
			ret = -EINVAL;
			ibdev_err(ibdev,
				  "failed to check mtr%u end %u + %u, max %u.\n",
				  i, r->offset, r->count, page_cnt);
			वापस ret;
		पूर्ण

		ret = mtr_map_region(hr_dev, mtr, r, &pages[r->offset],
				     page_cnt - mapped_cnt);
		अगर (ret < 0) अणु
			ibdev_err(ibdev,
				  "failed to map mtr%u offset %u, ret = %d.\n",
				  i, r->offset, ret);
			वापस ret;
		पूर्ण
		mapped_cnt += ret;
		ret = 0;
	पूर्ण

	अगर (mapped_cnt < page_cnt) अणु
		ret = -ENOBUFS;
		ibdev_err(ibdev, "failed to map mtr pages count: %u < %u.\n",
			  mapped_cnt, page_cnt);
	पूर्ण

	वापस ret;
पूर्ण

पूर्णांक hns_roce_mtr_find(काष्ठा hns_roce_dev *hr_dev, काष्ठा hns_roce_mtr *mtr,
		      पूर्णांक offset, u64 *mtt_buf, पूर्णांक mtt_max, u64 *base_addr)
अणु
	काष्ठा hns_roce_hem_cfg *cfg = &mtr->hem_cfg;
	पूर्णांक mtt_count, left;
	पूर्णांक start_index;
	पूर्णांक total = 0;
	__le64 *mtts;
	u32 npage;
	u64 addr;

	अगर (!mtt_buf || mtt_max < 1)
		जाओ करोne;

	/* no mtt memory in direct mode, so just वापस the buffer address */
	अगर (cfg->is_direct) अणु
		start_index = offset >> HNS_HW_PAGE_SHIFT;
		क्रम (mtt_count = 0; mtt_count < cfg->region_count &&
		     total < mtt_max; mtt_count++) अणु
			npage = cfg->region[mtt_count].offset;
			अगर (npage < start_index)
				जारी;

			addr = cfg->root_ba + (npage << HNS_HW_PAGE_SHIFT);
			अगर (hr_dev->hw_rev == HNS_ROCE_HW_VER1)
				mtt_buf[total] = to_hr_hw_page_addr(addr);
			अन्यथा
				mtt_buf[total] = addr;

			total++;
		पूर्ण

		जाओ करोne;
	पूर्ण

	start_index = offset >> cfg->buf_pg_shअगरt;
	left = mtt_max;
	जबतक (left > 0) अणु
		mtt_count = 0;
		mtts = hns_roce_hem_list_find_mtt(hr_dev, &mtr->hem_list,
						  start_index + total,
						  &mtt_count, शून्य);
		अगर (!mtts || !mtt_count)
			जाओ करोne;

		npage = min(mtt_count, left);
		left -= npage;
		क्रम (mtt_count = 0; mtt_count < npage; mtt_count++)
			mtt_buf[total++] = le64_to_cpu(mtts[mtt_count]);
	पूर्ण

करोne:
	अगर (base_addr)
		*base_addr = cfg->root_ba;

	वापस total;
पूर्ण

अटल पूर्णांक mtr_init_buf_cfg(काष्ठा hns_roce_dev *hr_dev,
			    काष्ठा hns_roce_buf_attr *attr,
			    काष्ठा hns_roce_hem_cfg *cfg,
			    अचिन्हित पूर्णांक *buf_page_shअगरt, पूर्णांक unalinged_size)
अणु
	काष्ठा hns_roce_buf_region *r;
	पूर्णांक first_region_padding;
	पूर्णांक page_cnt, region_cnt;
	अचिन्हित पूर्णांक page_shअगरt;
	माप_प्रकार buf_size;

	/* If mtt is disabled, all pages must be within a continuous range */
	cfg->is_direct = !mtr_has_mtt(attr);
	buf_size = mtr_bufs_size(attr);
	अगर (cfg->is_direct) अणु
		/* When HEM buffer uses 0-level addressing, the page size is
		 * equal to the whole buffer size, and we split the buffer पूर्णांकo
		 * small pages which is used to check whether the adjacent
		 * units are in the continuous space and its size is fixed to
		 * 4K based on hns ROCEE's requirement.
		 */
		page_shअगरt = HNS_HW_PAGE_SHIFT;

		/* The ROCEE requires the page size to be 4K * 2 ^ N. */
		cfg->buf_pg_count = 1;
		cfg->buf_pg_shअगरt = HNS_HW_PAGE_SHIFT +
			order_base_2(DIV_ROUND_UP(buf_size, HNS_HW_PAGE_SIZE));
		first_region_padding = 0;
	पूर्ण अन्यथा अणु
		page_shअगरt = attr->page_shअगरt;
		cfg->buf_pg_count = DIV_ROUND_UP(buf_size + unalinged_size,
						 1 << page_shअगरt);
		cfg->buf_pg_shअगरt = page_shअगरt;
		first_region_padding = unalinged_size;
	पूर्ण

	/* Convert buffer size to page index and page count क्रम each region and
	 * the buffer's offset needs to be appended to the first region.
	 */
	क्रम (page_cnt = 0, region_cnt = 0; region_cnt < attr->region_count &&
	     region_cnt < ARRAY_SIZE(cfg->region); region_cnt++) अणु
		r = &cfg->region[region_cnt];
		r->offset = page_cnt;
		buf_size = hr_hw_page_align(attr->region[region_cnt].size +
					    first_region_padding);
		r->count = DIV_ROUND_UP(buf_size, 1 << page_shअगरt);
		first_region_padding = 0;
		page_cnt += r->count;
		r->hopnum = to_hr_hem_hopnum(attr->region[region_cnt].hopnum,
					     r->count);
	पूर्ण

	cfg->region_count = region_cnt;
	*buf_page_shअगरt = page_shअगरt;

	वापस page_cnt;
पूर्ण

अटल पूर्णांक mtr_alloc_mtt(काष्ठा hns_roce_dev *hr_dev, काष्ठा hns_roce_mtr *mtr,
			 अचिन्हित पूर्णांक ba_page_shअगरt)
अणु
	काष्ठा hns_roce_hem_cfg *cfg = &mtr->hem_cfg;
	पूर्णांक ret;

	hns_roce_hem_list_init(&mtr->hem_list);
	अगर (!cfg->is_direct) अणु
		ret = hns_roce_hem_list_request(hr_dev, &mtr->hem_list,
						cfg->region, cfg->region_count,
						ba_page_shअगरt);
		अगर (ret)
			वापस ret;
		cfg->root_ba = mtr->hem_list.root_ba;
		cfg->ba_pg_shअगरt = ba_page_shअगरt;
	पूर्ण अन्यथा अणु
		cfg->ba_pg_shअगरt = cfg->buf_pg_shअगरt;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम mtr_मुक्त_mtt(काष्ठा hns_roce_dev *hr_dev, काष्ठा hns_roce_mtr *mtr)
अणु
	hns_roce_hem_list_release(hr_dev, &mtr->hem_list);
पूर्ण

/**
 * hns_roce_mtr_create - Create hns memory translate region.
 *
 * @hr_dev: RoCE device काष्ठा poपूर्णांकer
 * @mtr: memory translate region
 * @buf_attr: buffer attribute क्रम creating mtr
 * @ba_page_shअगरt: page shअगरt क्रम multi-hop base address table
 * @udata: user space context, अगर it's शून्य, means kernel space
 * @user_addr: userspace भव address to start at
 */
पूर्णांक hns_roce_mtr_create(काष्ठा hns_roce_dev *hr_dev, काष्ठा hns_roce_mtr *mtr,
			काष्ठा hns_roce_buf_attr *buf_attr,
			अचिन्हित पूर्णांक ba_page_shअगरt, काष्ठा ib_udata *udata,
			अचिन्हित दीर्घ user_addr)
अणु
	काष्ठा ib_device *ibdev = &hr_dev->ib_dev;
	अचिन्हित पूर्णांक buf_page_shअगरt = 0;
	पूर्णांक buf_page_cnt;
	पूर्णांक ret;

	buf_page_cnt = mtr_init_buf_cfg(hr_dev, buf_attr, &mtr->hem_cfg,
					&buf_page_shअगरt,
					udata ? user_addr & ~PAGE_MASK : 0);
	अगर (buf_page_cnt < 1 || buf_page_shअगरt < HNS_HW_PAGE_SHIFT) अणु
		ibdev_err(ibdev, "failed to init mtr cfg, count %d shift %d.\n",
			  buf_page_cnt, buf_page_shअगरt);
		वापस -EINVAL;
	पूर्ण

	ret = mtr_alloc_mtt(hr_dev, mtr, ba_page_shअगरt);
	अगर (ret) अणु
		ibdev_err(ibdev, "failed to alloc mtr mtt, ret = %d.\n", ret);
		वापस ret;
	पूर्ण

	/* The caller has its own buffer list and invokes the hns_roce_mtr_map()
	 * to finish the MTT configuration.
	 */
	अगर (buf_attr->mtt_only) अणु
		mtr->umem = शून्य;
		mtr->kmem = शून्य;
		वापस 0;
	पूर्ण

	ret = mtr_alloc_bufs(hr_dev, mtr, buf_attr, udata, user_addr);
	अगर (ret) अणु
		ibdev_err(ibdev, "failed to alloc mtr bufs, ret = %d.\n", ret);
		जाओ err_alloc_mtt;
	पूर्ण

	/* Write buffer's dma address to MTT */
	ret = mtr_map_bufs(hr_dev, mtr, buf_page_cnt, buf_page_shअगरt);
	अगर (ret)
		ibdev_err(ibdev, "failed to map mtr bufs, ret = %d.\n", ret);
	अन्यथा
		वापस 0;

	mtr_मुक्त_bufs(hr_dev, mtr);
err_alloc_mtt:
	mtr_मुक्त_mtt(hr_dev, mtr);
	वापस ret;
पूर्ण

व्योम hns_roce_mtr_destroy(काष्ठा hns_roce_dev *hr_dev, काष्ठा hns_roce_mtr *mtr)
अणु
	/* release multi-hop addressing resource */
	hns_roce_hem_list_release(hr_dev, &mtr->hem_list);

	/* मुक्त buffers */
	mtr_मुक्त_bufs(hr_dev, mtr);
पूर्ण
