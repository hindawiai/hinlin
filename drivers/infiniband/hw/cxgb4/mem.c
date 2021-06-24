<शैली गुरु>
/*
 * Copyright (c) 2009-2010 Chelsio, Inc. All rights reserved.
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

#समावेश <linux/module.h>
#समावेश <linux/moduleparam.h>
#समावेश <rdma/ib_uस्मृति.स>
#समावेश <linux/atomic.h>
#समावेश <rdma/ib_user_verbs.h>

#समावेश "iw_cxgb4.h"

पूर्णांक use_dsgl = 1;
module_param(use_dsgl, पूर्णांक, 0644);
MODULE_PARM_DESC(use_dsgl, "Use DSGL for PBL/FastReg (default=1) (DEPRECATED)");

#घोषणा T4_ULPTX_MIN_IO 32
#घोषणा C4IW_MAX_INLINE_SIZE 96
#घोषणा T4_ULPTX_MAX_DMA 1024
#घोषणा C4IW_INLINE_THRESHOLD 128

अटल पूर्णांक अंतरभूत_threshold = C4IW_INLINE_THRESHOLD;
module_param(अंतरभूत_threshold, पूर्णांक, 0644);
MODULE_PARM_DESC(अंतरभूत_threshold, "inline vs dsgl threshold (default=128)");

अटल पूर्णांक mr_exceeds_hw_limits(काष्ठा c4iw_dev *dev, u64 length)
अणु
	वापस (is_t4(dev->rdev.lldi.adapter_type) ||
		is_t5(dev->rdev.lldi.adapter_type)) &&
		length >= 8*1024*1024*1024ULL;
पूर्ण

अटल पूर्णांक _c4iw_ग_लिखो_mem_dma_aligned(काष्ठा c4iw_rdev *rdev, u32 addr,
				       u32 len, dma_addr_t data,
				       काष्ठा sk_buff *skb,
				       काष्ठा c4iw_wr_रुको *wr_रुकोp)
अणु
	काष्ठा ulp_mem_io *req;
	काष्ठा ulptx_sgl *sgl;
	u8 wr_len;
	पूर्णांक ret = 0;

	addr &= 0x7FFFFFF;

	अगर (wr_रुकोp)
		c4iw_init_wr_रुको(wr_रुकोp);
	wr_len = roundup(माप(*req) + माप(*sgl), 16);

	अगर (!skb) अणु
		skb = alloc_skb(wr_len, GFP_KERNEL | __GFP_NOFAIL);
		अगर (!skb)
			वापस -ENOMEM;
	पूर्ण
	set_wr_txq(skb, CPL_PRIORITY_CONTROL, 0);

	req = __skb_put_zero(skb, wr_len);
	INIT_ULPTX_WR(req, wr_len, 0, 0);
	req->wr.wr_hi = cpu_to_be32(FW_WR_OP_V(FW_ULPTX_WR) |
			(wr_रुकोp ? FW_WR_COMPL_F : 0));
	req->wr.wr_lo = wr_रुकोp ? (__क्रमce __be64)(अचिन्हित दीर्घ)wr_रुकोp : 0L;
	req->wr.wr_mid = cpu_to_be32(FW_WR_LEN16_V(DIV_ROUND_UP(wr_len, 16)));
	req->cmd = cpu_to_be32(ULPTX_CMD_V(ULP_TX_MEM_WRITE) |
			       T5_ULP_MEMIO_ORDER_V(1) |
			       T5_ULP_MEMIO_FID_V(rdev->lldi.rxq_ids[0]));
	req->dlen = cpu_to_be32(ULP_MEMIO_DATA_LEN_V(len>>5));
	req->len16 = cpu_to_be32(DIV_ROUND_UP(wr_len-माप(req->wr), 16));
	req->lock_addr = cpu_to_be32(ULP_MEMIO_ADDR_V(addr));

	sgl = (काष्ठा ulptx_sgl *)(req + 1);
	sgl->cmd_nsge = cpu_to_be32(ULPTX_CMD_V(ULP_TX_SC_DSGL) |
				    ULPTX_NSGE_V(1));
	sgl->len0 = cpu_to_be32(len);
	sgl->addr0 = cpu_to_be64(data);

	अगर (wr_रुकोp)
		ret = c4iw_ref_send_रुको(rdev, skb, wr_रुकोp, 0, 0, __func__);
	अन्यथा
		ret = c4iw_ofld_send(rdev, skb);
	वापस ret;
पूर्ण

अटल पूर्णांक _c4iw_ग_लिखो_mem_अंतरभूत(काष्ठा c4iw_rdev *rdev, u32 addr, u32 len,
				  व्योम *data, काष्ठा sk_buff *skb,
				  काष्ठा c4iw_wr_रुको *wr_रुकोp)
अणु
	काष्ठा ulp_mem_io *req;
	काष्ठा ulptx_idata *sc;
	u8 wr_len, *to_dp, *from_dp;
	पूर्णांक copy_len, num_wqe, i, ret = 0;
	__be32 cmd = cpu_to_be32(ULPTX_CMD_V(ULP_TX_MEM_WRITE));

	अगर (is_t4(rdev->lldi.adapter_type))
		cmd |= cpu_to_be32(ULP_MEMIO_ORDER_F);
	अन्यथा
		cmd |= cpu_to_be32(T5_ULP_MEMIO_IMM_F);

	addr &= 0x7FFFFFF;
	pr_debug("addr 0x%x len %u\n", addr, len);
	num_wqe = DIV_ROUND_UP(len, C4IW_MAX_INLINE_SIZE);
	c4iw_init_wr_रुको(wr_रुकोp);
	क्रम (i = 0; i < num_wqe; i++) अणु

		copy_len = len > C4IW_MAX_INLINE_SIZE ? C4IW_MAX_INLINE_SIZE :
			   len;
		wr_len = roundup(माप(*req) + माप(*sc) +
					 roundup(copy_len, T4_ULPTX_MIN_IO),
				 16);

		अगर (!skb) अणु
			skb = alloc_skb(wr_len, GFP_KERNEL | __GFP_NOFAIL);
			अगर (!skb)
				वापस -ENOMEM;
		पूर्ण
		set_wr_txq(skb, CPL_PRIORITY_CONTROL, 0);

		req = __skb_put_zero(skb, wr_len);
		INIT_ULPTX_WR(req, wr_len, 0, 0);

		अगर (i == (num_wqe-1)) अणु
			req->wr.wr_hi = cpu_to_be32(FW_WR_OP_V(FW_ULPTX_WR) |
						    FW_WR_COMPL_F);
			req->wr.wr_lo = (__क्रमce __be64)(अचिन्हित दीर्घ)wr_रुकोp;
		पूर्ण अन्यथा
			req->wr.wr_hi = cpu_to_be32(FW_WR_OP_V(FW_ULPTX_WR));
		req->wr.wr_mid = cpu_to_be32(
				       FW_WR_LEN16_V(DIV_ROUND_UP(wr_len, 16)));

		req->cmd = cmd;
		req->dlen = cpu_to_be32(ULP_MEMIO_DATA_LEN_V(
				DIV_ROUND_UP(copy_len, T4_ULPTX_MIN_IO)));
		req->len16 = cpu_to_be32(DIV_ROUND_UP(wr_len-माप(req->wr),
						      16));
		req->lock_addr = cpu_to_be32(ULP_MEMIO_ADDR_V(addr + i * 3));

		sc = (काष्ठा ulptx_idata *)(req + 1);
		sc->cmd_more = cpu_to_be32(ULPTX_CMD_V(ULP_TX_SC_IMM));
		sc->len = cpu_to_be32(roundup(copy_len, T4_ULPTX_MIN_IO));

		to_dp = (u8 *)(sc + 1);
		from_dp = (u8 *)data + i * C4IW_MAX_INLINE_SIZE;
		अगर (data)
			स_नकल(to_dp, from_dp, copy_len);
		अन्यथा
			स_रखो(to_dp, 0, copy_len);
		अगर (copy_len % T4_ULPTX_MIN_IO)
			स_रखो(to_dp + copy_len, 0, T4_ULPTX_MIN_IO -
			       (copy_len % T4_ULPTX_MIN_IO));
		अगर (i == (num_wqe-1))
			ret = c4iw_ref_send_रुको(rdev, skb, wr_रुकोp, 0, 0,
						 __func__);
		अन्यथा
			ret = c4iw_ofld_send(rdev, skb);
		अगर (ret)
			अवरोध;
		skb = शून्य;
		len -= C4IW_MAX_INLINE_SIZE;
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक _c4iw_ग_लिखो_mem_dma(काष्ठा c4iw_rdev *rdev, u32 addr, u32 len,
			       व्योम *data, काष्ठा sk_buff *skb,
			       काष्ठा c4iw_wr_रुको *wr_रुकोp)
अणु
	u32 reमुख्य = len;
	u32 dmalen;
	पूर्णांक ret = 0;
	dma_addr_t daddr;
	dma_addr_t save;

	daddr = dma_map_single(&rdev->lldi.pdev->dev, data, len, DMA_TO_DEVICE);
	अगर (dma_mapping_error(&rdev->lldi.pdev->dev, daddr))
		वापस -1;
	save = daddr;

	जबतक (reमुख्य > अंतरभूत_threshold) अणु
		अगर (reमुख्य < T4_ULPTX_MAX_DMA) अणु
			अगर (reमुख्य & ~T4_ULPTX_MIN_IO)
				dmalen = reमुख्य & ~(T4_ULPTX_MIN_IO-1);
			अन्यथा
				dmalen = reमुख्य;
		पूर्ण अन्यथा
			dmalen = T4_ULPTX_MAX_DMA;
		reमुख्य -= dmalen;
		ret = _c4iw_ग_लिखो_mem_dma_aligned(rdev, addr, dmalen, daddr,
						 skb, reमुख्य ? शून्य : wr_रुकोp);
		अगर (ret)
			जाओ out;
		addr += dmalen >> 5;
		data += dmalen;
		daddr += dmalen;
	पूर्ण
	अगर (reमुख्य)
		ret = _c4iw_ग_लिखो_mem_अंतरभूत(rdev, addr, reमुख्य, data, skb,
					     wr_रुकोp);
out:
	dma_unmap_single(&rdev->lldi.pdev->dev, save, len, DMA_TO_DEVICE);
	वापस ret;
पूर्ण

/*
 * ग_लिखो len bytes of data पूर्णांकo addr (32B aligned address)
 * If data is शून्य, clear len byte of memory to zero.
 */
अटल पूर्णांक ग_लिखो_adapter_mem(काष्ठा c4iw_rdev *rdev, u32 addr, u32 len,
			     व्योम *data, काष्ठा sk_buff *skb,
			     काष्ठा c4iw_wr_रुको *wr_रुकोp)
अणु
	पूर्णांक ret;

	अगर (!rdev->lldi.ulptx_memग_लिखो_dsgl || !use_dsgl) अणु
		ret = _c4iw_ग_लिखो_mem_अंतरभूत(rdev, addr, len, data, skb,
					      wr_रुकोp);
		जाओ out;
	पूर्ण

	अगर (len <= अंतरभूत_threshold) अणु
		ret = _c4iw_ग_लिखो_mem_अंतरभूत(rdev, addr, len, data, skb,
					      wr_रुकोp);
		जाओ out;
	पूर्ण

	ret = _c4iw_ग_लिखो_mem_dma(rdev, addr, len, data, skb, wr_रुकोp);
	अगर (ret) अणु
		pr_warn_ratelimited("%s: dma map failure (non fatal)\n",
				    pci_name(rdev->lldi.pdev));
		ret = _c4iw_ग_लिखो_mem_अंतरभूत(rdev, addr, len, data, skb,
					      wr_रुकोp);
	पूर्ण
out:
	वापस ret;

पूर्ण

/*
 * Build and ग_लिखो a TPT entry.
 * IN: stag key, pdid, perm, bind_enabled, zbva, to, len, page_size,
 *     pbl_size and pbl_addr
 * OUT: stag index
 */
अटल पूर्णांक ग_लिखो_tpt_entry(काष्ठा c4iw_rdev *rdev, u32 reset_tpt_entry,
			   u32 *stag, u8 stag_state, u32 pdid,
			   क्रमागत fw_ri_stag_type type, क्रमागत fw_ri_mem_perms perm,
			   पूर्णांक bind_enabled, u32 zbva, u64 to,
			   u64 len, u8 page_size, u32 pbl_size, u32 pbl_addr,
			   काष्ठा sk_buff *skb, काष्ठा c4iw_wr_रुको *wr_रुकोp)
अणु
	पूर्णांक err;
	काष्ठा fw_ri_tpte *tpt;
	u32 stag_idx;
	अटल atomic_t key;

	अगर (c4iw_fatal_error(rdev))
		वापस -EIO;

	tpt = kदो_स्मृति(माप(*tpt), GFP_KERNEL);
	अगर (!tpt)
		वापस -ENOMEM;

	stag_state = stag_state > 0;
	stag_idx = (*stag) >> 8;

	अगर ((!reset_tpt_entry) && (*stag == T4_STAG_UNSET)) अणु
		stag_idx = c4iw_get_resource(&rdev->resource.tpt_table);
		अगर (!stag_idx) अणु
			mutex_lock(&rdev->stats.lock);
			rdev->stats.stag.fail++;
			mutex_unlock(&rdev->stats.lock);
			kमुक्त(tpt);
			वापस -ENOMEM;
		पूर्ण
		mutex_lock(&rdev->stats.lock);
		rdev->stats.stag.cur += 32;
		अगर (rdev->stats.stag.cur > rdev->stats.stag.max)
			rdev->stats.stag.max = rdev->stats.stag.cur;
		mutex_unlock(&rdev->stats.lock);
		*stag = (stag_idx << 8) | (atomic_inc_वापस(&key) & 0xff);
	पूर्ण
	pr_debug("stag_state 0x%0x type 0x%0x pdid 0x%0x, stag_idx 0x%x\n",
		 stag_state, type, pdid, stag_idx);

	/* ग_लिखो TPT entry */
	अगर (reset_tpt_entry)
		स_रखो(tpt, 0, माप(*tpt));
	अन्यथा अणु
		tpt->valid_to_pdid = cpu_to_be32(FW_RI_TPTE_VALID_F |
			FW_RI_TPTE_STAGKEY_V((*stag & FW_RI_TPTE_STAGKEY_M)) |
			FW_RI_TPTE_STAGSTATE_V(stag_state) |
			FW_RI_TPTE_STAGTYPE_V(type) | FW_RI_TPTE_PDID_V(pdid));
		tpt->locपढ़ो_to_qpid = cpu_to_be32(FW_RI_TPTE_PERM_V(perm) |
			(bind_enabled ? FW_RI_TPTE_MWBINDEN_F : 0) |
			FW_RI_TPTE_ADDRTYPE_V((zbva ? FW_RI_ZERO_BASED_TO :
						      FW_RI_VA_BASED_TO))|
			FW_RI_TPTE_PS_V(page_size));
		tpt->nosnoop_pbladdr = !pbl_size ? 0 : cpu_to_be32(
			FW_RI_TPTE_PBLADDR_V(PBL_OFF(rdev, pbl_addr)>>3));
		tpt->len_lo = cpu_to_be32((u32)(len & 0xffffffffUL));
		tpt->va_hi = cpu_to_be32((u32)(to >> 32));
		tpt->va_lo_fbo = cpu_to_be32((u32)(to & 0xffffffffUL));
		tpt->dca_mwbcnt_pstag = cpu_to_be32(0);
		tpt->len_hi = cpu_to_be32((u32)(len >> 32));
	पूर्ण
	err = ग_लिखो_adapter_mem(rdev, stag_idx +
				(rdev->lldi.vr->stag.start >> 5),
				माप(*tpt), tpt, skb, wr_रुकोp);

	अगर (reset_tpt_entry) अणु
		c4iw_put_resource(&rdev->resource.tpt_table, stag_idx);
		mutex_lock(&rdev->stats.lock);
		rdev->stats.stag.cur -= 32;
		mutex_unlock(&rdev->stats.lock);
	पूर्ण
	kमुक्त(tpt);
	वापस err;
पूर्ण

अटल पूर्णांक ग_लिखो_pbl(काष्ठा c4iw_rdev *rdev, __be64 *pbl,
		     u32 pbl_addr, u32 pbl_size, काष्ठा c4iw_wr_रुको *wr_रुकोp)
अणु
	पूर्णांक err;

	pr_debug("*pdb_addr 0x%x, pbl_base 0x%x, pbl_size %d\n",
		 pbl_addr, rdev->lldi.vr->pbl.start,
		 pbl_size);

	err = ग_लिखो_adapter_mem(rdev, pbl_addr >> 5, pbl_size << 3, pbl, शून्य,
				wr_रुकोp);
	वापस err;
पूर्ण

अटल पूर्णांक dereg_mem(काष्ठा c4iw_rdev *rdev, u32 stag, u32 pbl_size,
		     u32 pbl_addr, काष्ठा sk_buff *skb,
		     काष्ठा c4iw_wr_रुको *wr_रुकोp)
अणु
	वापस ग_लिखो_tpt_entry(rdev, 1, &stag, 0, 0, 0, 0, 0, 0, 0UL, 0, 0,
			       pbl_size, pbl_addr, skb, wr_रुकोp);
पूर्ण

अटल पूर्णांक allocate_stag(काष्ठा c4iw_rdev *rdev, u32 *stag, u32 pdid,
			 u32 pbl_size, u32 pbl_addr,
			 काष्ठा c4iw_wr_रुको *wr_रुकोp)
अणु
	*stag = T4_STAG_UNSET;
	वापस ग_लिखो_tpt_entry(rdev, 0, stag, 0, pdid, FW_RI_STAG_NSMR, 0, 0, 0,
			       0UL, 0, 0, pbl_size, pbl_addr, शून्य, wr_रुकोp);
पूर्ण

अटल पूर्णांक finish_mem_reg(काष्ठा c4iw_mr *mhp, u32 stag)
अणु
	u32 mmid;

	mhp->attr.state = 1;
	mhp->attr.stag = stag;
	mmid = stag >> 8;
	mhp->ibmr.rkey = mhp->ibmr.lkey = stag;
	mhp->ibmr.length = mhp->attr.len;
	mhp->ibmr.page_size = 1U << (mhp->attr.page_size + 12);
	pr_debug("mmid 0x%x mhp %p\n", mmid, mhp);
	वापस xa_insert_irq(&mhp->rhp->mrs, mmid, mhp, GFP_KERNEL);
पूर्ण

अटल पूर्णांक रेजिस्टर_mem(काष्ठा c4iw_dev *rhp, काष्ठा c4iw_pd *php,
		      काष्ठा c4iw_mr *mhp, पूर्णांक shअगरt)
अणु
	u32 stag = T4_STAG_UNSET;
	पूर्णांक ret;

	ret = ग_लिखो_tpt_entry(&rhp->rdev, 0, &stag, 1, mhp->attr.pdid,
			      FW_RI_STAG_NSMR, mhp->attr.len ?
			      mhp->attr.perms : 0,
			      mhp->attr.mw_bind_enable, mhp->attr.zbva,
			      mhp->attr.va_fbo, mhp->attr.len ?
			      mhp->attr.len : -1, shअगरt - 12,
			      mhp->attr.pbl_size, mhp->attr.pbl_addr, शून्य,
			      mhp->wr_रुकोp);
	अगर (ret)
		वापस ret;

	ret = finish_mem_reg(mhp, stag);
	अगर (ret) अणु
		dereg_mem(&rhp->rdev, mhp->attr.stag, mhp->attr.pbl_size,
			  mhp->attr.pbl_addr, mhp->dereg_skb, mhp->wr_रुकोp);
		mhp->dereg_skb = शून्य;
	पूर्ण
	वापस ret;
पूर्ण

अटल पूर्णांक alloc_pbl(काष्ठा c4iw_mr *mhp, पूर्णांक npages)
अणु
	mhp->attr.pbl_addr = c4iw_pblpool_alloc(&mhp->rhp->rdev,
						    npages << 3);

	अगर (!mhp->attr.pbl_addr)
		वापस -ENOMEM;

	mhp->attr.pbl_size = npages;

	वापस 0;
पूर्ण

काष्ठा ib_mr *c4iw_get_dma_mr(काष्ठा ib_pd *pd, पूर्णांक acc)
अणु
	काष्ठा c4iw_dev *rhp;
	काष्ठा c4iw_pd *php;
	काष्ठा c4iw_mr *mhp;
	पूर्णांक ret;
	u32 stag = T4_STAG_UNSET;

	pr_debug("ib_pd %p\n", pd);
	php = to_c4iw_pd(pd);
	rhp = php->rhp;

	mhp = kzalloc(माप(*mhp), GFP_KERNEL);
	अगर (!mhp)
		वापस ERR_PTR(-ENOMEM);
	mhp->wr_रुकोp = c4iw_alloc_wr_रुको(GFP_KERNEL);
	अगर (!mhp->wr_रुकोp) अणु
		ret = -ENOMEM;
		जाओ err_मुक्त_mhp;
	पूर्ण
	c4iw_init_wr_रुको(mhp->wr_रुकोp);

	mhp->dereg_skb = alloc_skb(SGE_MAX_WR_LEN, GFP_KERNEL);
	अगर (!mhp->dereg_skb) अणु
		ret = -ENOMEM;
		जाओ err_मुक्त_wr_रुको;
	पूर्ण

	mhp->rhp = rhp;
	mhp->attr.pdid = php->pdid;
	mhp->attr.perms = c4iw_ib_to_tpt_access(acc);
	mhp->attr.mw_bind_enable = (acc&IB_ACCESS_MW_BIND) == IB_ACCESS_MW_BIND;
	mhp->attr.zbva = 0;
	mhp->attr.va_fbo = 0;
	mhp->attr.page_size = 0;
	mhp->attr.len = ~0ULL;
	mhp->attr.pbl_size = 0;

	ret = ग_लिखो_tpt_entry(&rhp->rdev, 0, &stag, 1, php->pdid,
			      FW_RI_STAG_NSMR, mhp->attr.perms,
			      mhp->attr.mw_bind_enable, 0, 0, ~0ULL, 0, 0, 0,
			      शून्य, mhp->wr_रुकोp);
	अगर (ret)
		जाओ err_मुक्त_skb;

	ret = finish_mem_reg(mhp, stag);
	अगर (ret)
		जाओ err_dereg_mem;
	वापस &mhp->ibmr;
err_dereg_mem:
	dereg_mem(&rhp->rdev, mhp->attr.stag, mhp->attr.pbl_size,
		  mhp->attr.pbl_addr, mhp->dereg_skb, mhp->wr_रुकोp);
err_मुक्त_skb:
	kमुक्त_skb(mhp->dereg_skb);
err_मुक्त_wr_रुको:
	c4iw_put_wr_रुको(mhp->wr_रुकोp);
err_मुक्त_mhp:
	kमुक्त(mhp);
	वापस ERR_PTR(ret);
पूर्ण

काष्ठा ib_mr *c4iw_reg_user_mr(काष्ठा ib_pd *pd, u64 start, u64 length,
			       u64 virt, पूर्णांक acc, काष्ठा ib_udata *udata)
अणु
	__be64 *pages;
	पूर्णांक shअगरt, n, i;
	पूर्णांक err = -ENOMEM;
	काष्ठा ib_block_iter biter;
	काष्ठा c4iw_dev *rhp;
	काष्ठा c4iw_pd *php;
	काष्ठा c4iw_mr *mhp;

	pr_debug("ib_pd %p\n", pd);

	अगर (length == ~0ULL)
		वापस ERR_PTR(-EINVAL);

	अगर ((length + start) < start)
		वापस ERR_PTR(-EINVAL);

	php = to_c4iw_pd(pd);
	rhp = php->rhp;

	अगर (mr_exceeds_hw_limits(rhp, length))
		वापस ERR_PTR(-EINVAL);

	mhp = kzalloc(माप(*mhp), GFP_KERNEL);
	अगर (!mhp)
		वापस ERR_PTR(-ENOMEM);
	mhp->wr_रुकोp = c4iw_alloc_wr_रुको(GFP_KERNEL);
	अगर (!mhp->wr_रुकोp)
		जाओ err_मुक्त_mhp;

	mhp->dereg_skb = alloc_skb(SGE_MAX_WR_LEN, GFP_KERNEL);
	अगर (!mhp->dereg_skb)
		जाओ err_मुक्त_wr_रुको;

	mhp->rhp = rhp;

	mhp->umem = ib_umem_get(pd->device, start, length, acc);
	अगर (IS_ERR(mhp->umem))
		जाओ err_मुक्त_skb;

	shअगरt = PAGE_SHIFT;

	n = ib_umem_num_dma_blocks(mhp->umem, 1 << shअगरt);
	err = alloc_pbl(mhp, n);
	अगर (err)
		जाओ err_umem_release;

	pages = (__be64 *) __get_मुक्त_page(GFP_KERNEL);
	अगर (!pages) अणु
		err = -ENOMEM;
		जाओ err_pbl_मुक्त;
	पूर्ण

	i = n = 0;

	rdma_umem_क्रम_each_dma_block(mhp->umem, &biter, 1 << shअगरt) अणु
		pages[i++] = cpu_to_be64(rdma_block_iter_dma_address(&biter));
		अगर (i == PAGE_SIZE / माप(*pages)) अणु
			err = ग_लिखो_pbl(&mhp->rhp->rdev, pages,
					mhp->attr.pbl_addr + (n << 3), i,
					mhp->wr_रुकोp);
			अगर (err)
				जाओ pbl_करोne;
			n += i;
			i = 0;
		पूर्ण
	पूर्ण

	अगर (i)
		err = ग_लिखो_pbl(&mhp->rhp->rdev, pages,
				mhp->attr.pbl_addr + (n << 3), i,
				mhp->wr_रुकोp);

pbl_करोne:
	मुक्त_page((अचिन्हित दीर्घ) pages);
	अगर (err)
		जाओ err_pbl_मुक्त;

	mhp->attr.pdid = php->pdid;
	mhp->attr.zbva = 0;
	mhp->attr.perms = c4iw_ib_to_tpt_access(acc);
	mhp->attr.va_fbo = virt;
	mhp->attr.page_size = shअगरt - 12;
	mhp->attr.len = length;

	err = रेजिस्टर_mem(rhp, php, mhp, shअगरt);
	अगर (err)
		जाओ err_pbl_मुक्त;

	वापस &mhp->ibmr;

err_pbl_मुक्त:
	c4iw_pblpool_मुक्त(&mhp->rhp->rdev, mhp->attr.pbl_addr,
			      mhp->attr.pbl_size << 3);
err_umem_release:
	ib_umem_release(mhp->umem);
err_मुक्त_skb:
	kमुक्त_skb(mhp->dereg_skb);
err_मुक्त_wr_रुको:
	c4iw_put_wr_रुको(mhp->wr_रुकोp);
err_मुक्त_mhp:
	kमुक्त(mhp);
	वापस ERR_PTR(err);
पूर्ण

काष्ठा ib_mr *c4iw_alloc_mr(काष्ठा ib_pd *pd, क्रमागत ib_mr_type mr_type,
			    u32 max_num_sg)
अणु
	काष्ठा c4iw_dev *rhp;
	काष्ठा c4iw_pd *php;
	काष्ठा c4iw_mr *mhp;
	u32 mmid;
	u32 stag = 0;
	पूर्णांक ret = 0;
	पूर्णांक length = roundup(max_num_sg * माप(u64), 32);

	php = to_c4iw_pd(pd);
	rhp = php->rhp;

	अगर (mr_type != IB_MR_TYPE_MEM_REG ||
	    max_num_sg > t4_max_fr_depth(rhp->rdev.lldi.ulptx_memग_लिखो_dsgl &&
					 use_dsgl))
		वापस ERR_PTR(-EINVAL);

	mhp = kzalloc(माप(*mhp), GFP_KERNEL);
	अगर (!mhp) अणु
		ret = -ENOMEM;
		जाओ err;
	पूर्ण

	mhp->wr_रुकोp = c4iw_alloc_wr_रुको(GFP_KERNEL);
	अगर (!mhp->wr_रुकोp) अणु
		ret = -ENOMEM;
		जाओ err_मुक्त_mhp;
	पूर्ण
	c4iw_init_wr_रुको(mhp->wr_रुकोp);

	mhp->mpl = dma_alloc_coherent(&rhp->rdev.lldi.pdev->dev,
				      length, &mhp->mpl_addr, GFP_KERNEL);
	अगर (!mhp->mpl) अणु
		ret = -ENOMEM;
		जाओ err_मुक्त_wr_रुको;
	पूर्ण
	mhp->max_mpl_len = length;

	mhp->rhp = rhp;
	ret = alloc_pbl(mhp, max_num_sg);
	अगर (ret)
		जाओ err_मुक्त_dma;
	mhp->attr.pbl_size = max_num_sg;
	ret = allocate_stag(&rhp->rdev, &stag, php->pdid,
			    mhp->attr.pbl_size, mhp->attr.pbl_addr,
			    mhp->wr_रुकोp);
	अगर (ret)
		जाओ err_मुक्त_pbl;
	mhp->attr.pdid = php->pdid;
	mhp->attr.type = FW_RI_STAG_NSMR;
	mhp->attr.stag = stag;
	mhp->attr.state = 0;
	mmid = (stag) >> 8;
	mhp->ibmr.rkey = mhp->ibmr.lkey = stag;
	अगर (xa_insert_irq(&rhp->mrs, mmid, mhp, GFP_KERNEL)) अणु
		ret = -ENOMEM;
		जाओ err_dereg;
	पूर्ण

	pr_debug("mmid 0x%x mhp %p stag 0x%x\n", mmid, mhp, stag);
	वापस &(mhp->ibmr);
err_dereg:
	dereg_mem(&rhp->rdev, stag, mhp->attr.pbl_size,
		  mhp->attr.pbl_addr, mhp->dereg_skb, mhp->wr_रुकोp);
err_मुक्त_pbl:
	c4iw_pblpool_मुक्त(&mhp->rhp->rdev, mhp->attr.pbl_addr,
			      mhp->attr.pbl_size << 3);
err_मुक्त_dma:
	dma_मुक्त_coherent(&mhp->rhp->rdev.lldi.pdev->dev,
			  mhp->max_mpl_len, mhp->mpl, mhp->mpl_addr);
err_मुक्त_wr_रुको:
	c4iw_put_wr_रुको(mhp->wr_रुकोp);
err_मुक्त_mhp:
	kमुक्त(mhp);
err:
	वापस ERR_PTR(ret);
पूर्ण

अटल पूर्णांक c4iw_set_page(काष्ठा ib_mr *ibmr, u64 addr)
अणु
	काष्ठा c4iw_mr *mhp = to_c4iw_mr(ibmr);

	अगर (unlikely(mhp->mpl_len == mhp->attr.pbl_size))
		वापस -ENOMEM;

	mhp->mpl[mhp->mpl_len++] = addr;

	वापस 0;
पूर्ण

पूर्णांक c4iw_map_mr_sg(काष्ठा ib_mr *ibmr, काष्ठा scatterlist *sg, पूर्णांक sg_nents,
		   अचिन्हित पूर्णांक *sg_offset)
अणु
	काष्ठा c4iw_mr *mhp = to_c4iw_mr(ibmr);

	mhp->mpl_len = 0;

	वापस ib_sg_to_pages(ibmr, sg, sg_nents, sg_offset, c4iw_set_page);
पूर्ण

पूर्णांक c4iw_dereg_mr(काष्ठा ib_mr *ib_mr, काष्ठा ib_udata *udata)
अणु
	काष्ठा c4iw_dev *rhp;
	काष्ठा c4iw_mr *mhp;
	u32 mmid;

	pr_debug("ib_mr %p\n", ib_mr);

	mhp = to_c4iw_mr(ib_mr);
	rhp = mhp->rhp;
	mmid = mhp->attr.stag >> 8;
	xa_erase_irq(&rhp->mrs, mmid);
	अगर (mhp->mpl)
		dma_मुक्त_coherent(&mhp->rhp->rdev.lldi.pdev->dev,
				  mhp->max_mpl_len, mhp->mpl, mhp->mpl_addr);
	dereg_mem(&rhp->rdev, mhp->attr.stag, mhp->attr.pbl_size,
		  mhp->attr.pbl_addr, mhp->dereg_skb, mhp->wr_रुकोp);
	अगर (mhp->attr.pbl_size)
		c4iw_pblpool_मुक्त(&mhp->rhp->rdev, mhp->attr.pbl_addr,
				  mhp->attr.pbl_size << 3);
	अगर (mhp->kva)
		kमुक्त((व्योम *) (अचिन्हित दीर्घ) mhp->kva);
	ib_umem_release(mhp->umem);
	pr_debug("mmid 0x%x ptr %p\n", mmid, mhp);
	c4iw_put_wr_रुको(mhp->wr_रुकोp);
	kमुक्त(mhp);
	वापस 0;
पूर्ण

व्योम c4iw_invalidate_mr(काष्ठा c4iw_dev *rhp, u32 rkey)
अणु
	काष्ठा c4iw_mr *mhp;
	अचिन्हित दीर्घ flags;

	xa_lock_irqsave(&rhp->mrs, flags);
	mhp = xa_load(&rhp->mrs, rkey >> 8);
	अगर (mhp)
		mhp->attr.state = 0;
	xa_unlock_irqrestore(&rhp->mrs, flags);
पूर्ण
