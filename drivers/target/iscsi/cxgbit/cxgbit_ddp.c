<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (c) 2016 Chelsio Communications, Inc.
 */

#समावेश "cxgbit.h"

अटल व्योम
cxgbit_set_one_ppod(काष्ठा cxgbi_pagepod *ppod,
		    काष्ठा cxgbi_task_tag_info *ttinfo,
		    काष्ठा scatterlist **sg_pp, अचिन्हित पूर्णांक *sg_off)
अणु
	काष्ठा scatterlist *sg = sg_pp ? *sg_pp : शून्य;
	अचिन्हित पूर्णांक offset = sg_off ? *sg_off : 0;
	dma_addr_t addr = 0UL;
	अचिन्हित पूर्णांक len = 0;
	पूर्णांक i;

	स_नकल(ppod, &ttinfo->hdr, माप(काष्ठा cxgbi_pagepod_hdr));

	अगर (sg) अणु
		addr = sg_dma_address(sg);
		len = sg_dma_len(sg);
	पूर्ण

	क्रम (i = 0; i < PPOD_PAGES_MAX; i++) अणु
		अगर (sg) अणु
			ppod->addr[i] = cpu_to_be64(addr + offset);
			offset += PAGE_SIZE;
			अगर (offset == (len + sg->offset)) अणु
				offset = 0;
				sg = sg_next(sg);
				अगर (sg) अणु
					addr = sg_dma_address(sg);
					len = sg_dma_len(sg);
				पूर्ण
			पूर्ण
		पूर्ण अन्यथा अणु
			ppod->addr[i] = 0ULL;
		पूर्ण
	पूर्ण

	/*
	 * the fअगरth address needs to be repeated in the next ppod, so करो
	 * not move sg
	 */
	अगर (sg_pp) अणु
		*sg_pp = sg;
		*sg_off = offset;
	पूर्ण

	अगर (offset == len) अणु
		offset = 0;
		अगर (sg) अणु
			sg = sg_next(sg);
			अगर (sg)
				addr = sg_dma_address(sg);
		पूर्ण
	पूर्ण
	ppod->addr[i] = sg ? cpu_to_be64(addr + offset) : 0ULL;
पूर्ण

अटल काष्ठा sk_buff *
cxgbit_ppod_init_idata(काष्ठा cxgbit_device *cdev, काष्ठा cxgbi_ppm *ppm,
		       अचिन्हित पूर्णांक idx, अचिन्हित पूर्णांक npods, अचिन्हित पूर्णांक tid)
अणु
	काष्ठा ulp_mem_io *req;
	काष्ठा ulptx_idata *idata;
	अचिन्हित पूर्णांक pm_addr = (idx << PPOD_SIZE_SHIFT) + ppm->llimit;
	अचिन्हित पूर्णांक dlen = npods << PPOD_SIZE_SHIFT;
	अचिन्हित पूर्णांक wr_len = roundup(माप(काष्ठा ulp_mem_io) +
				माप(काष्ठा ulptx_idata) + dlen, 16);
	काष्ठा sk_buff *skb;

	skb  = alloc_skb(wr_len, GFP_KERNEL);
	अगर (!skb)
		वापस शून्य;

	req = __skb_put(skb, wr_len);
	INIT_ULPTX_WR(req, wr_len, 0, tid);
	req->wr.wr_hi = htonl(FW_WR_OP_V(FW_ULPTX_WR) |
		FW_WR_ATOMIC_V(0));
	req->cmd = htonl(ULPTX_CMD_V(ULP_TX_MEM_WRITE) |
		ULP_MEMIO_ORDER_V(0) |
		T5_ULP_MEMIO_IMM_V(1));
	req->dlen = htonl(ULP_MEMIO_DATA_LEN_V(dlen >> 5));
	req->lock_addr = htonl(ULP_MEMIO_ADDR_V(pm_addr >> 5));
	req->len16 = htonl(DIV_ROUND_UP(wr_len - माप(req->wr), 16));

	idata = (काष्ठा ulptx_idata *)(req + 1);
	idata->cmd_more = htonl(ULPTX_CMD_V(ULP_TX_SC_IMM));
	idata->len = htonl(dlen);

	वापस skb;
पूर्ण

अटल पूर्णांक
cxgbit_ppod_ग_लिखो_idata(काष्ठा cxgbi_ppm *ppm, काष्ठा cxgbit_sock *csk,
			काष्ठा cxgbi_task_tag_info *ttinfo, अचिन्हित पूर्णांक idx,
			अचिन्हित पूर्णांक npods, काष्ठा scatterlist **sg_pp,
			अचिन्हित पूर्णांक *sg_off)
अणु
	काष्ठा cxgbit_device *cdev = csk->com.cdev;
	काष्ठा sk_buff *skb;
	काष्ठा ulp_mem_io *req;
	काष्ठा ulptx_idata *idata;
	काष्ठा cxgbi_pagepod *ppod;
	अचिन्हित पूर्णांक i;

	skb = cxgbit_ppod_init_idata(cdev, ppm, idx, npods, csk->tid);
	अगर (!skb)
		वापस -ENOMEM;

	req = (काष्ठा ulp_mem_io *)skb->data;
	idata = (काष्ठा ulptx_idata *)(req + 1);
	ppod = (काष्ठा cxgbi_pagepod *)(idata + 1);

	क्रम (i = 0; i < npods; i++, ppod++)
		cxgbit_set_one_ppod(ppod, ttinfo, sg_pp, sg_off);

	__skb_queue_tail(&csk->ppodq, skb);

	वापस 0;
पूर्ण

अटल पूर्णांक
cxgbit_ddp_set_map(काष्ठा cxgbi_ppm *ppm, काष्ठा cxgbit_sock *csk,
		   काष्ठा cxgbi_task_tag_info *ttinfo)
अणु
	अचिन्हित पूर्णांक pidx = ttinfo->idx;
	अचिन्हित पूर्णांक npods = ttinfo->npods;
	अचिन्हित पूर्णांक i, cnt;
	काष्ठा scatterlist *sg = ttinfo->sgl;
	अचिन्हित पूर्णांक offset = 0;
	पूर्णांक ret = 0;

	क्रम (i = 0; i < npods; i += cnt, pidx += cnt) अणु
		cnt = npods - i;

		अगर (cnt > ULPMEM_IDATA_MAX_NPPODS)
			cnt = ULPMEM_IDATA_MAX_NPPODS;

		ret = cxgbit_ppod_ग_लिखो_idata(ppm, csk, ttinfo, pidx, cnt,
					      &sg, &offset);
		अगर (ret < 0)
			अवरोध;
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक cxgbit_ddp_sgl_check(काष्ठा scatterlist *sg,
				अचिन्हित पूर्णांक nents)
अणु
	अचिन्हित पूर्णांक last_sgidx = nents - 1;
	अचिन्हित पूर्णांक i;

	क्रम (i = 0; i < nents; i++, sg = sg_next(sg)) अणु
		अचिन्हित पूर्णांक len = sg->length + sg->offset;

		अगर ((sg->offset & 0x3) || (i && sg->offset) ||
		    ((i != last_sgidx) && (len != PAGE_SIZE))) अणु
			वापस -EINVAL;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक
cxgbit_ddp_reserve(काष्ठा cxgbit_sock *csk, काष्ठा cxgbi_task_tag_info *ttinfo,
		   अचिन्हित पूर्णांक xferlen)
अणु
	काष्ठा cxgbit_device *cdev = csk->com.cdev;
	काष्ठा cxgbi_ppm *ppm = cdev2ppm(cdev);
	काष्ठा scatterlist *sgl = ttinfo->sgl;
	अचिन्हित पूर्णांक sgcnt = ttinfo->nents;
	अचिन्हित पूर्णांक sg_offset = sgl->offset;
	पूर्णांक ret;

	अगर ((xferlen < DDP_THRESHOLD) || (!sgcnt)) अणु
		pr_debug("ppm 0x%p, pgidx %u, xfer %u, sgcnt %u, NO ddp.\n",
			 ppm, ppm->tक्रमmat.pgsz_idx_dflt,
			 xferlen, ttinfo->nents);
		वापस -EINVAL;
	पूर्ण

	अगर (cxgbit_ddp_sgl_check(sgl, sgcnt) < 0)
		वापस -EINVAL;

	ttinfo->nr_pages = (xferlen + sgl->offset +
			    (1 << PAGE_SHIFT) - 1) >> PAGE_SHIFT;

	/*
	 * the ddp tag will be used क्रम the ttt in the outgoing r2t pdu
	 */
	ret = cxgbi_ppm_ppods_reserve(ppm, ttinfo->nr_pages, 0, &ttinfo->idx,
				      &ttinfo->tag, 0);
	अगर (ret < 0)
		वापस ret;
	ttinfo->npods = ret;

	sgl->offset = 0;
	ret = dma_map_sg(&ppm->pdev->dev, sgl, sgcnt, DMA_FROM_DEVICE);
	sgl->offset = sg_offset;
	अगर (!ret) अणु
		pr_debug("%s: 0x%x, xfer %u, sgl %u dma mapping err.\n",
			 __func__, 0, xferlen, sgcnt);
		जाओ rel_ppods;
	पूर्ण

	cxgbi_ppm_make_ppod_hdr(ppm, ttinfo->tag, csk->tid, sgl->offset,
				xferlen, &ttinfo->hdr);

	ret = cxgbit_ddp_set_map(ppm, csk, ttinfo);
	अगर (ret < 0) अणु
		__skb_queue_purge(&csk->ppodq);
		dma_unmap_sg(&ppm->pdev->dev, sgl, sgcnt, DMA_FROM_DEVICE);
		जाओ rel_ppods;
	पूर्ण

	वापस 0;

rel_ppods:
	cxgbi_ppm_ppod_release(ppm, ttinfo->idx);
	वापस -EINVAL;
पूर्ण

व्योम
cxgbit_get_r2t_ttt(काष्ठा iscsi_conn *conn, काष्ठा iscsi_cmd *cmd,
		   काष्ठा iscsi_r2t *r2t)
अणु
	काष्ठा cxgbit_sock *csk = conn->context;
	काष्ठा cxgbit_device *cdev = csk->com.cdev;
	काष्ठा cxgbit_cmd *ccmd = iscsit_priv_cmd(cmd);
	काष्ठा cxgbi_task_tag_info *ttinfo = &ccmd->ttinfo;
	पूर्णांक ret = -EINVAL;

	अगर ((!ccmd->setup_ddp) ||
	    (!test_bit(CSK_DDP_ENABLE, &csk->com.flags)))
		जाओ out;

	ccmd->setup_ddp = false;

	ttinfo->sgl = cmd->se_cmd.t_data_sg;
	ttinfo->nents = cmd->se_cmd.t_data_nents;

	ret = cxgbit_ddp_reserve(csk, ttinfo, cmd->se_cmd.data_length);
	अगर (ret < 0) अणु
		pr_debug("csk 0x%p, cmd 0x%p, xfer len %u, sgcnt %u no ddp.\n",
			 csk, cmd, cmd->se_cmd.data_length, ttinfo->nents);

		ttinfo->sgl = शून्य;
		ttinfo->nents = 0;
	पूर्ण अन्यथा अणु
		ccmd->release = true;
	पूर्ण
out:
	pr_debug("cdev 0x%p, cmd 0x%p, tag 0x%x\n", cdev, cmd, ttinfo->tag);
	r2t->targ_xfer_tag = ttinfo->tag;
पूर्ण

व्योम cxgbit_unmap_cmd(काष्ठा iscsi_conn *conn, काष्ठा iscsi_cmd *cmd)
अणु
	काष्ठा cxgbit_cmd *ccmd = iscsit_priv_cmd(cmd);

	अगर (ccmd->release) अणु
		काष्ठा cxgbi_task_tag_info *ttinfo = &ccmd->ttinfo;

		अगर (ttinfo->sgl) अणु
			काष्ठा cxgbit_sock *csk = conn->context;
			काष्ठा cxgbit_device *cdev = csk->com.cdev;
			काष्ठा cxgbi_ppm *ppm = cdev2ppm(cdev);

			/* Abort the TCP conn अगर DDP is not complete to
			 * aव्योम any possibility of DDP after मुक्तing
			 * the cmd.
			 */
			अगर (unlikely(cmd->ग_लिखो_data_करोne !=
				     cmd->se_cmd.data_length))
				cxgbit_पात_conn(csk);

			cxgbi_ppm_ppod_release(ppm, ttinfo->idx);

			dma_unmap_sg(&ppm->pdev->dev, ttinfo->sgl,
				     ttinfo->nents, DMA_FROM_DEVICE);
		पूर्ण अन्यथा अणु
			put_page(sg_page(&ccmd->sg));
		पूर्ण

		ccmd->release = false;
	पूर्ण
पूर्ण

पूर्णांक cxgbit_ddp_init(काष्ठा cxgbit_device *cdev)
अणु
	काष्ठा cxgb4_lld_info *lldi = &cdev->lldi;
	काष्ठा net_device *ndev = cdev->lldi.ports[0];
	काष्ठा cxgbi_tag_क्रमmat tक्रमmat;
	पूर्णांक ret, i;

	अगर (!lldi->vr->iscsi.size) अणु
		pr_warn("%s, iscsi NOT enabled, check config!\n", ndev->name);
		वापस -EACCES;
	पूर्ण

	स_रखो(&tक्रमmat, 0, माप(काष्ठा cxgbi_tag_क्रमmat));
	क्रम (i = 0; i < 4; i++)
		tक्रमmat.pgsz_order[i] = (lldi->iscsi_pgsz_order >> (i << 3))
					 & 0xF;
	cxgbi_tagmask_check(lldi->iscsi_tagmask, &tक्रमmat);

	ret = cxgbi_ppm_init(lldi->iscsi_ppm, cdev->lldi.ports[0],
			     cdev->lldi.pdev, &cdev->lldi, &tक्रमmat,
			     lldi->vr->iscsi.size, lldi->iscsi_llimit,
			     lldi->vr->iscsi.start, 2,
			     lldi->vr->ppod_edram.start,
			     lldi->vr->ppod_edram.size);
	अगर (ret >= 0) अणु
		काष्ठा cxgbi_ppm *ppm = (काष्ठा cxgbi_ppm *)(*lldi->iscsi_ppm);

		अगर ((ppm->tक्रमmat.pgsz_idx_dflt < DDP_PGIDX_MAX) &&
		    (ppm->ppmax >= 1024))
			set_bit(CDEV_DDP_ENABLE, &cdev->flags);
		ret = 0;
	पूर्ण

	वापस ret;
पूर्ण
