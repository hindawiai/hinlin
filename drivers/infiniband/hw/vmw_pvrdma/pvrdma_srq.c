<शैली गुरु>
/*
 * Copyright (c) 2016-2017 VMware, Inc.  All rights reserved.
 *
 * This program is मुक्त software; you can redistribute it and/or
 * modअगरy it under the terms of EITHER the GNU General Public License
 * version 2 as published by the Free Software Foundation or the BSD
 * 2-Clause License. This program is distributed in the hope that it
 * will be useful, but WITHOUT ANY WARRANTY; WITHOUT EVEN THE IMPLIED
 * WARRANTY OF MERCHANTABILITY OR FITNESS FOR A PARTICULAR PURPOSE.
 * See the GNU General Public License version 2 क्रम more details at
 * http://www.gnu.org/licenses/old-licenses/gpl-2.0.en.hपंचांगl.
 *
 * You should have received a copy of the GNU General Public License
 * aदीर्घ with this program available in the file COPYING in the मुख्य
 * directory of this source tree.
 *
 * The BSD 2-Clause License
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
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
 * FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE
 * COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY सूचीECT,
 * INसूचीECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT,
 * STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED
 * OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#समावेश <यंत्र/page.h>
#समावेश <linux/पन.स>
#समावेश <linux/रुको.h>
#समावेश <rdma/ib_addr.h>
#समावेश <rdma/ib_smi.h>
#समावेश <rdma/ib_user_verbs.h>

#समावेश "pvrdma.h"

/**
 * pvrdma_query_srq - query shared receive queue
 * @ibsrq: the shared receive queue to query
 * @srq_attr: attributes to query and वापस to client
 *
 * @वापस: 0 क्रम success, otherwise वापसs an त्रुटि_सं.
 */
पूर्णांक pvrdma_query_srq(काष्ठा ib_srq *ibsrq, काष्ठा ib_srq_attr *srq_attr)
अणु
	काष्ठा pvrdma_dev *dev = to_vdev(ibsrq->device);
	काष्ठा pvrdma_srq *srq = to_vsrq(ibsrq);
	जोड़ pvrdma_cmd_req req;
	जोड़ pvrdma_cmd_resp rsp;
	काष्ठा pvrdma_cmd_query_srq *cmd = &req.query_srq;
	काष्ठा pvrdma_cmd_query_srq_resp *resp = &rsp.query_srq_resp;
	पूर्णांक ret;

	स_रखो(cmd, 0, माप(*cmd));
	cmd->hdr.cmd = PVRDMA_CMD_QUERY_SRQ;
	cmd->srq_handle = srq->srq_handle;

	ret = pvrdma_cmd_post(dev, &req, &rsp, PVRDMA_CMD_QUERY_SRQ_RESP);
	अगर (ret < 0) अणु
		dev_warn(&dev->pdev->dev,
			 "could not query shared receive queue, error: %d\n",
			 ret);
		वापस -EINVAL;
	पूर्ण

	srq_attr->srq_limit = resp->attrs.srq_limit;
	srq_attr->max_wr = resp->attrs.max_wr;
	srq_attr->max_sge = resp->attrs.max_sge;

	वापस 0;
पूर्ण

/**
 * pvrdma_create_srq - create shared receive queue
 * @ibsrq: the IB shared receive queue
 * @init_attr: shared receive queue attributes
 * @udata: user data
 *
 * @वापस: 0 on success, otherwise वापसs an त्रुटि_सं.
 */
पूर्णांक pvrdma_create_srq(काष्ठा ib_srq *ibsrq, काष्ठा ib_srq_init_attr *init_attr,
		      काष्ठा ib_udata *udata)
अणु
	काष्ठा pvrdma_srq *srq = to_vsrq(ibsrq);
	काष्ठा pvrdma_dev *dev = to_vdev(ibsrq->device);
	जोड़ pvrdma_cmd_req req;
	जोड़ pvrdma_cmd_resp rsp;
	काष्ठा pvrdma_cmd_create_srq *cmd = &req.create_srq;
	काष्ठा pvrdma_cmd_create_srq_resp *resp = &rsp.create_srq_resp;
	काष्ठा pvrdma_create_srq_resp srq_resp = अणुपूर्ण;
	काष्ठा pvrdma_create_srq ucmd;
	अचिन्हित दीर्घ flags;
	पूर्णांक ret;

	अगर (!udata) अणु
		/* No support क्रम kernel clients. */
		dev_warn(&dev->pdev->dev,
			 "no shared receive queue support for kernel client\n");
		वापस -EOPNOTSUPP;
	पूर्ण

	अगर (init_attr->srq_type != IB_SRQT_BASIC) अणु
		dev_warn(&dev->pdev->dev,
			 "shared receive queue type %d not supported\n",
			 init_attr->srq_type);
		वापस -EOPNOTSUPP;
	पूर्ण

	अगर (init_attr->attr.max_wr  > dev->dsr->caps.max_srq_wr ||
	    init_attr->attr.max_sge > dev->dsr->caps.max_srq_sge) अणु
		dev_warn(&dev->pdev->dev,
			 "shared receive queue size invalid\n");
		वापस -EINVAL;
	पूर्ण

	अगर (!atomic_add_unless(&dev->num_srqs, 1, dev->dsr->caps.max_srq))
		वापस -ENOMEM;

	spin_lock_init(&srq->lock);
	refcount_set(&srq->refcnt, 1);
	init_completion(&srq->मुक्त);

	dev_dbg(&dev->pdev->dev,
		"create shared receive queue from user space\n");

	अगर (ib_copy_from_udata(&ucmd, udata, माप(ucmd))) अणु
		ret = -EFAULT;
		जाओ err_srq;
	पूर्ण

	srq->umem = ib_umem_get(ibsrq->device, ucmd.buf_addr, ucmd.buf_size, 0);
	अगर (IS_ERR(srq->umem)) अणु
		ret = PTR_ERR(srq->umem);
		जाओ err_srq;
	पूर्ण

	srq->npages = ib_umem_num_dma_blocks(srq->umem, PAGE_SIZE);

	अगर (srq->npages < 0 || srq->npages > PVRDMA_PAGE_सूची_MAX_PAGES) अणु
		dev_warn(&dev->pdev->dev,
			 "overflow pages in shared receive queue\n");
		ret = -EINVAL;
		जाओ err_umem;
	पूर्ण

	ret = pvrdma_page_dir_init(dev, &srq->pdir, srq->npages, false);
	अगर (ret) अणु
		dev_warn(&dev->pdev->dev,
			 "could not allocate page directory\n");
		जाओ err_umem;
	पूर्ण

	pvrdma_page_dir_insert_umem(&srq->pdir, srq->umem, 0);

	स_रखो(cmd, 0, माप(*cmd));
	cmd->hdr.cmd = PVRDMA_CMD_CREATE_SRQ;
	cmd->srq_type = init_attr->srq_type;
	cmd->nchunks = srq->npages;
	cmd->pd_handle = to_vpd(ibsrq->pd)->pd_handle;
	cmd->attrs.max_wr = init_attr->attr.max_wr;
	cmd->attrs.max_sge = init_attr->attr.max_sge;
	cmd->attrs.srq_limit = init_attr->attr.srq_limit;
	cmd->pdir_dma = srq->pdir.dir_dma;

	ret = pvrdma_cmd_post(dev, &req, &rsp, PVRDMA_CMD_CREATE_SRQ_RESP);
	अगर (ret < 0) अणु
		dev_warn(&dev->pdev->dev,
			 "could not create shared receive queue, error: %d\n",
			 ret);
		जाओ err_page_dir;
	पूर्ण

	srq->srq_handle = resp->srqn;
	srq_resp.srqn = resp->srqn;
	spin_lock_irqsave(&dev->srq_tbl_lock, flags);
	dev->srq_tbl[srq->srq_handle % dev->dsr->caps.max_srq] = srq;
	spin_unlock_irqrestore(&dev->srq_tbl_lock, flags);

	/* Copy udata back. */
	अगर (ib_copy_to_udata(udata, &srq_resp, माप(srq_resp))) अणु
		dev_warn(&dev->pdev->dev, "failed to copy back udata\n");
		pvrdma_destroy_srq(&srq->ibsrq, udata);
		वापस -EINVAL;
	पूर्ण

	वापस 0;

err_page_dir:
	pvrdma_page_dir_cleanup(dev, &srq->pdir);
err_umem:
	ib_umem_release(srq->umem);
err_srq:
	atomic_dec(&dev->num_srqs);

	वापस ret;
पूर्ण

अटल व्योम pvrdma_मुक्त_srq(काष्ठा pvrdma_dev *dev, काष्ठा pvrdma_srq *srq)
अणु
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&dev->srq_tbl_lock, flags);
	dev->srq_tbl[srq->srq_handle] = शून्य;
	spin_unlock_irqrestore(&dev->srq_tbl_lock, flags);

	अगर (refcount_dec_and_test(&srq->refcnt))
		complete(&srq->मुक्त);
	रुको_क्रम_completion(&srq->मुक्त);

	/* There is no support क्रम kernel clients, so this is safe. */
	ib_umem_release(srq->umem);

	pvrdma_page_dir_cleanup(dev, &srq->pdir);

	atomic_dec(&dev->num_srqs);
पूर्ण

/**
 * pvrdma_destroy_srq - destroy shared receive queue
 * @srq: the shared receive queue to destroy
 * @udata: user data or null क्रम kernel object
 *
 * @वापस: 0 क्रम success.
 */
पूर्णांक pvrdma_destroy_srq(काष्ठा ib_srq *srq, काष्ठा ib_udata *udata)
अणु
	काष्ठा pvrdma_srq *vsrq = to_vsrq(srq);
	जोड़ pvrdma_cmd_req req;
	काष्ठा pvrdma_cmd_destroy_srq *cmd = &req.destroy_srq;
	काष्ठा pvrdma_dev *dev = to_vdev(srq->device);
	पूर्णांक ret;

	स_रखो(cmd, 0, माप(*cmd));
	cmd->hdr.cmd = PVRDMA_CMD_DESTROY_SRQ;
	cmd->srq_handle = vsrq->srq_handle;

	ret = pvrdma_cmd_post(dev, &req, शून्य, 0);
	अगर (ret < 0)
		dev_warn(&dev->pdev->dev,
			 "destroy shared receive queue failed, error: %d\n",
			 ret);

	pvrdma_मुक्त_srq(dev, vsrq);
	वापस 0;
पूर्ण

/**
 * pvrdma_modअगरy_srq - modअगरy shared receive queue attributes
 * @ibsrq: the shared receive queue to modअगरy
 * @attr: the shared receive queue's new attributes
 * @attr_mask: attributes mask
 * @udata: user data
 *
 * @वापसs 0 on success, otherwise वापसs an त्रुटि_सं.
 */
पूर्णांक pvrdma_modअगरy_srq(काष्ठा ib_srq *ibsrq, काष्ठा ib_srq_attr *attr,
		      क्रमागत ib_srq_attr_mask attr_mask, काष्ठा ib_udata *udata)
अणु
	काष्ठा pvrdma_srq *vsrq = to_vsrq(ibsrq);
	जोड़ pvrdma_cmd_req req;
	काष्ठा pvrdma_cmd_modअगरy_srq *cmd = &req.modअगरy_srq;
	काष्ठा pvrdma_dev *dev = to_vdev(ibsrq->device);
	पूर्णांक ret;

	/* Only support SRQ limit. */
	अगर (!(attr_mask & IB_SRQ_LIMIT))
		वापस -EINVAL;

	स_रखो(cmd, 0, माप(*cmd));
	cmd->hdr.cmd = PVRDMA_CMD_MODIFY_SRQ;
	cmd->srq_handle = vsrq->srq_handle;
	cmd->attrs.srq_limit = attr->srq_limit;
	cmd->attr_mask = attr_mask;

	ret = pvrdma_cmd_post(dev, &req, शून्य, 0);
	अगर (ret < 0) अणु
		dev_warn(&dev->pdev->dev,
			 "could not modify shared receive queue, error: %d\n",
			 ret);

		वापस -EINVAL;
	पूर्ण

	वापस ret;
पूर्ण
