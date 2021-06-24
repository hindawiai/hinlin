<शैली गुरु>
/*
 * Copyright (c) 2012-2016 VMware, Inc.  All rights reserved.
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

#समावेश <linux/list.h>
#समावेश <linux/slab.h>

#समावेश "pvrdma.h"

/**
 * pvrdma_get_dma_mr - get a DMA memory region
 * @pd: protection करोमुख्य
 * @acc: access flags
 *
 * @वापस: ib_mr poपूर्णांकer on success, otherwise वापसs an त्रुटि_सं.
 */
काष्ठा ib_mr *pvrdma_get_dma_mr(काष्ठा ib_pd *pd, पूर्णांक acc)
अणु
	काष्ठा pvrdma_dev *dev = to_vdev(pd->device);
	काष्ठा pvrdma_user_mr *mr;
	जोड़ pvrdma_cmd_req req;
	जोड़ pvrdma_cmd_resp rsp;
	काष्ठा pvrdma_cmd_create_mr *cmd = &req.create_mr;
	काष्ठा pvrdma_cmd_create_mr_resp *resp = &rsp.create_mr_resp;
	पूर्णांक ret;

	/* Support only LOCAL_WRITE flag क्रम DMA MRs */
	अगर (acc & ~IB_ACCESS_LOCAL_WRITE) अणु
		dev_warn(&dev->pdev->dev,
			 "unsupported dma mr access flags %#x\n", acc);
		वापस ERR_PTR(-EOPNOTSUPP);
	पूर्ण

	mr = kzalloc(माप(*mr), GFP_KERNEL);
	अगर (!mr)
		वापस ERR_PTR(-ENOMEM);

	स_रखो(cmd, 0, माप(*cmd));
	cmd->hdr.cmd = PVRDMA_CMD_CREATE_MR;
	cmd->pd_handle = to_vpd(pd)->pd_handle;
	cmd->access_flags = acc;
	cmd->flags = PVRDMA_MR_FLAG_DMA;

	ret = pvrdma_cmd_post(dev, &req, &rsp, PVRDMA_CMD_CREATE_MR_RESP);
	अगर (ret < 0) अणु
		dev_warn(&dev->pdev->dev,
			 "could not get DMA mem region, error: %d\n", ret);
		kमुक्त(mr);
		वापस ERR_PTR(ret);
	पूर्ण

	mr->mmr.mr_handle = resp->mr_handle;
	mr->ibmr.lkey = resp->lkey;
	mr->ibmr.rkey = resp->rkey;

	वापस &mr->ibmr;
पूर्ण

/**
 * pvrdma_reg_user_mr - रेजिस्टर a userspace memory region
 * @pd: protection करोमुख्य
 * @start: starting address
 * @length: length of region
 * @virt_addr: I/O भव address
 * @access_flags: access flags क्रम memory region
 * @udata: user data
 *
 * @वापस: ib_mr poपूर्णांकer on success, otherwise वापसs an त्रुटि_सं.
 */
काष्ठा ib_mr *pvrdma_reg_user_mr(काष्ठा ib_pd *pd, u64 start, u64 length,
				 u64 virt_addr, पूर्णांक access_flags,
				 काष्ठा ib_udata *udata)
अणु
	काष्ठा pvrdma_dev *dev = to_vdev(pd->device);
	काष्ठा pvrdma_user_mr *mr = शून्य;
	काष्ठा ib_umem *umem;
	जोड़ pvrdma_cmd_req req;
	जोड़ pvrdma_cmd_resp rsp;
	काष्ठा pvrdma_cmd_create_mr *cmd = &req.create_mr;
	काष्ठा pvrdma_cmd_create_mr_resp *resp = &rsp.create_mr_resp;
	पूर्णांक ret, npages;

	अगर (length == 0 || length > dev->dsr->caps.max_mr_size) अणु
		dev_warn(&dev->pdev->dev, "invalid mem region length\n");
		वापस ERR_PTR(-EINVAL);
	पूर्ण

	umem = ib_umem_get(pd->device, start, length, access_flags);
	अगर (IS_ERR(umem)) अणु
		dev_warn(&dev->pdev->dev,
			 "could not get umem for mem region\n");
		वापस ERR_CAST(umem);
	पूर्ण

	npages = ib_umem_num_dma_blocks(umem, PAGE_SIZE);
	अगर (npages < 0 || npages > PVRDMA_PAGE_सूची_MAX_PAGES) अणु
		dev_warn(&dev->pdev->dev, "overflow %d pages in mem region\n",
			 npages);
		ret = -EINVAL;
		जाओ err_umem;
	पूर्ण

	mr = kzalloc(माप(*mr), GFP_KERNEL);
	अगर (!mr) अणु
		ret = -ENOMEM;
		जाओ err_umem;
	पूर्ण

	mr->mmr.iova = virt_addr;
	mr->mmr.size = length;
	mr->umem = umem;

	ret = pvrdma_page_dir_init(dev, &mr->pdir, npages, false);
	अगर (ret) अणु
		dev_warn(&dev->pdev->dev,
			 "could not allocate page directory\n");
		जाओ err_umem;
	पूर्ण

	ret = pvrdma_page_dir_insert_umem(&mr->pdir, mr->umem, 0);
	अगर (ret)
		जाओ err_pdir;

	स_रखो(cmd, 0, माप(*cmd));
	cmd->hdr.cmd = PVRDMA_CMD_CREATE_MR;
	cmd->start = start;
	cmd->length = length;
	cmd->pd_handle = to_vpd(pd)->pd_handle;
	cmd->access_flags = access_flags;
	cmd->nchunks = npages;
	cmd->pdir_dma = mr->pdir.dir_dma;

	ret = pvrdma_cmd_post(dev, &req, &rsp, PVRDMA_CMD_CREATE_MR_RESP);
	अगर (ret < 0) अणु
		dev_warn(&dev->pdev->dev,
			 "could not register mem region, error: %d\n", ret);
		जाओ err_pdir;
	पूर्ण

	mr->mmr.mr_handle = resp->mr_handle;
	mr->ibmr.lkey = resp->lkey;
	mr->ibmr.rkey = resp->rkey;

	वापस &mr->ibmr;

err_pdir:
	pvrdma_page_dir_cleanup(dev, &mr->pdir);
err_umem:
	ib_umem_release(umem);
	kमुक्त(mr);

	वापस ERR_PTR(ret);
पूर्ण

/**
 * pvrdma_alloc_mr - allocate a memory region
 * @pd: protection करोमुख्य
 * @mr_type: type of memory region
 * @max_num_sg: maximum number of pages
 *
 * @वापस: ib_mr poपूर्णांकer on success, otherwise वापसs an त्रुटि_सं.
 */
काष्ठा ib_mr *pvrdma_alloc_mr(काष्ठा ib_pd *pd, क्रमागत ib_mr_type mr_type,
			      u32 max_num_sg)
अणु
	काष्ठा pvrdma_dev *dev = to_vdev(pd->device);
	काष्ठा pvrdma_user_mr *mr;
	जोड़ pvrdma_cmd_req req;
	जोड़ pvrdma_cmd_resp rsp;
	काष्ठा pvrdma_cmd_create_mr *cmd = &req.create_mr;
	काष्ठा pvrdma_cmd_create_mr_resp *resp = &rsp.create_mr_resp;
	पूर्णांक size = max_num_sg * माप(u64);
	पूर्णांक ret;

	अगर (mr_type != IB_MR_TYPE_MEM_REG ||
	    max_num_sg > PVRDMA_MAX_FAST_REG_PAGES)
		वापस ERR_PTR(-EINVAL);

	mr = kzalloc(माप(*mr), GFP_KERNEL);
	अगर (!mr)
		वापस ERR_PTR(-ENOMEM);

	mr->pages = kzalloc(size, GFP_KERNEL);
	अगर (!mr->pages) अणु
		ret = -ENOMEM;
		जाओ मुक्तmr;
	पूर्ण

	ret = pvrdma_page_dir_init(dev, &mr->pdir, max_num_sg, false);
	अगर (ret) अणु
		dev_warn(&dev->pdev->dev,
			 "failed to allocate page dir for mr\n");
		ret = -ENOMEM;
		जाओ मुक्तpages;
	पूर्ण

	स_रखो(cmd, 0, माप(*cmd));
	cmd->hdr.cmd = PVRDMA_CMD_CREATE_MR;
	cmd->pd_handle = to_vpd(pd)->pd_handle;
	cmd->access_flags = 0;
	cmd->flags = PVRDMA_MR_FLAG_FRMR;
	cmd->nchunks = max_num_sg;

	ret = pvrdma_cmd_post(dev, &req, &rsp, PVRDMA_CMD_CREATE_MR_RESP);
	अगर (ret < 0) अणु
		dev_warn(&dev->pdev->dev,
			 "could not create FR mem region, error: %d\n", ret);
		जाओ मुक्तpdir;
	पूर्ण

	mr->max_pages = max_num_sg;
	mr->mmr.mr_handle = resp->mr_handle;
	mr->ibmr.lkey = resp->lkey;
	mr->ibmr.rkey = resp->rkey;
	mr->page_shअगरt = PAGE_SHIFT;
	mr->umem = शून्य;

	वापस &mr->ibmr;

मुक्तpdir:
	pvrdma_page_dir_cleanup(dev, &mr->pdir);
मुक्तpages:
	kमुक्त(mr->pages);
मुक्तmr:
	kमुक्त(mr);
	वापस ERR_PTR(ret);
पूर्ण

/**
 * pvrdma_dereg_mr - deरेजिस्टर a memory region
 * @ibmr: memory region
 * @udata: poपूर्णांकer to user data
 *
 * @वापस: 0 on success.
 */
पूर्णांक pvrdma_dereg_mr(काष्ठा ib_mr *ibmr, काष्ठा ib_udata *udata)
अणु
	काष्ठा pvrdma_user_mr *mr = to_vmr(ibmr);
	काष्ठा pvrdma_dev *dev = to_vdev(ibmr->device);
	जोड़ pvrdma_cmd_req req;
	काष्ठा pvrdma_cmd_destroy_mr *cmd = &req.destroy_mr;
	पूर्णांक ret;

	स_रखो(cmd, 0, माप(*cmd));
	cmd->hdr.cmd = PVRDMA_CMD_DESTROY_MR;
	cmd->mr_handle = mr->mmr.mr_handle;
	ret = pvrdma_cmd_post(dev, &req, शून्य, 0);
	अगर (ret < 0)
		dev_warn(&dev->pdev->dev,
			 "could not deregister mem region, error: %d\n", ret);

	pvrdma_page_dir_cleanup(dev, &mr->pdir);
	ib_umem_release(mr->umem);

	kमुक्त(mr->pages);
	kमुक्त(mr);

	वापस 0;
पूर्ण

अटल पूर्णांक pvrdma_set_page(काष्ठा ib_mr *ibmr, u64 addr)
अणु
	काष्ठा pvrdma_user_mr *mr = to_vmr(ibmr);

	अगर (mr->npages == mr->max_pages)
		वापस -ENOMEM;

	mr->pages[mr->npages++] = addr;
	वापस 0;
पूर्ण

पूर्णांक pvrdma_map_mr_sg(काष्ठा ib_mr *ibmr, काष्ठा scatterlist *sg, पूर्णांक sg_nents,
		     अचिन्हित पूर्णांक *sg_offset)
अणु
	काष्ठा pvrdma_user_mr *mr = to_vmr(ibmr);
	काष्ठा pvrdma_dev *dev = to_vdev(ibmr->device);
	पूर्णांक ret;

	mr->npages = 0;

	ret = ib_sg_to_pages(ibmr, sg, sg_nents, sg_offset, pvrdma_set_page);
	अगर (ret < 0)
		dev_warn(&dev->pdev->dev, "could not map sg to pages\n");

	वापस ret;
पूर्ण
