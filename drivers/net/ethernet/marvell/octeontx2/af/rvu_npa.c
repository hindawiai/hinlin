<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/* Marvell OcteonTx2 RVU Admin Function driver
 *
 * Copyright (C) 2018 Marvell International Ltd.
 *
 * This program is मुक्त software; you can redistribute it and/or modअगरy
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 */

#समावेश <linux/module.h>
#समावेश <linux/pci.h>

#समावेश "rvu_struct.h"
#समावेश "rvu_reg.h"
#समावेश "rvu.h"

अटल पूर्णांक npa_aq_enqueue_रुको(काष्ठा rvu *rvu, काष्ठा rvu_block *block,
			       काष्ठा npa_aq_inst_s *inst)
अणु
	काष्ठा admin_queue *aq = block->aq;
	काष्ठा npa_aq_res_s *result;
	पूर्णांक समयout = 1000;
	u64 reg, head;

	result = (काष्ठा npa_aq_res_s *)aq->res->base;

	/* Get current head poपूर्णांकer where to append this inकाष्ठाion */
	reg = rvu_पढ़ो64(rvu, block->addr, NPA_AF_AQ_STATUS);
	head = (reg >> 4) & AQ_PTR_MASK;

	स_नकल((व्योम *)(aq->inst->base + (head * aq->inst->entry_sz)),
	       (व्योम *)inst, aq->inst->entry_sz);
	स_रखो(result, 0, माप(*result));
	/* sync पूर्णांकo memory */
	wmb();

	/* Ring the करोorbell and रुको क्रम result */
	rvu_ग_लिखो64(rvu, block->addr, NPA_AF_AQ_DOOR, 1);
	जबतक (result->compcode == NPA_AQ_COMP_NOTDONE) अणु
		cpu_relax();
		udelay(1);
		समयout--;
		अगर (!समयout)
			वापस -EBUSY;
	पूर्ण

	अगर (result->compcode != NPA_AQ_COMP_GOOD)
		/* TODO: Replace this with some error code */
		वापस -EBUSY;

	वापस 0;
पूर्ण

पूर्णांक rvu_npa_aq_enq_inst(काष्ठा rvu *rvu, काष्ठा npa_aq_enq_req *req,
			काष्ठा npa_aq_enq_rsp *rsp)
अणु
	काष्ठा rvu_hwinfo *hw = rvu->hw;
	u16 pcअगरunc = req->hdr.pcअगरunc;
	पूर्णांक blkaddr, npalf, rc = 0;
	काष्ठा npa_aq_inst_s inst;
	काष्ठा rvu_block *block;
	काष्ठा admin_queue *aq;
	काष्ठा rvu_pfvf *pfvf;
	व्योम *ctx, *mask;
	bool ena;

	pfvf = rvu_get_pfvf(rvu, pcअगरunc);
	अगर (!pfvf->aura_ctx || req->aura_id >= pfvf->aura_ctx->qsize)
		वापस NPA_AF_ERR_AQ_ENQUEUE;

	blkaddr = rvu_get_blkaddr(rvu, BLKTYPE_NPA, pcअगरunc);
	अगर (!pfvf->npalf || blkaddr < 0)
		वापस NPA_AF_ERR_AF_LF_INVALID;

	block = &hw->block[blkaddr];
	aq = block->aq;
	अगर (!aq) अणु
		dev_warn(rvu->dev, "%s: NPA AQ not initialized\n", __func__);
		वापस NPA_AF_ERR_AQ_ENQUEUE;
	पूर्ण

	npalf = rvu_get_lf(rvu, block, pcअगरunc, 0);
	अगर (npalf < 0)
		वापस NPA_AF_ERR_AF_LF_INVALID;

	स_रखो(&inst, 0, माप(काष्ठा npa_aq_inst_s));
	inst.cindex = req->aura_id;
	inst.lf = npalf;
	inst.ctype = req->ctype;
	inst.op = req->op;
	/* Currently we are not supporting enqueuing multiple inकाष्ठाions,
	 * so always choose first entry in result memory.
	 */
	inst.res_addr = (u64)aq->res->iova;

	/* Hardware uses same aq->res->base क्रम updating result of
	 * previous inकाष्ठाion hence रुको here till it is करोne.
	 */
	spin_lock(&aq->lock);

	/* Clean result + context memory */
	स_रखो(aq->res->base, 0, aq->res->entry_sz);
	/* Context needs to be written at RES_ADDR + 128 */
	ctx = aq->res->base + 128;
	/* Mask needs to be written at RES_ADDR + 256 */
	mask = aq->res->base + 256;

	चयन (req->op) अणु
	हाल NPA_AQ_INSTOP_WRITE:
		/* Copy context and ग_लिखो mask */
		अगर (req->ctype == NPA_AQ_CTYPE_AURA) अणु
			स_नकल(mask, &req->aura_mask,
			       माप(काष्ठा npa_aura_s));
			स_नकल(ctx, &req->aura, माप(काष्ठा npa_aura_s));
		पूर्ण अन्यथा अणु
			स_नकल(mask, &req->pool_mask,
			       माप(काष्ठा npa_pool_s));
			स_नकल(ctx, &req->pool, माप(काष्ठा npa_pool_s));
		पूर्ण
		अवरोध;
	हाल NPA_AQ_INSTOP_INIT:
		अगर (req->ctype == NPA_AQ_CTYPE_AURA) अणु
			अगर (req->aura.pool_addr >= pfvf->pool_ctx->qsize) अणु
				rc = NPA_AF_ERR_AQ_FULL;
				अवरोध;
			पूर्ण
			/* Set pool's context address */
			req->aura.pool_addr = pfvf->pool_ctx->iova +
			(req->aura.pool_addr * pfvf->pool_ctx->entry_sz);
			स_नकल(ctx, &req->aura, माप(काष्ठा npa_aura_s));
		पूर्ण अन्यथा अणु /* POOL's context */
			स_नकल(ctx, &req->pool, माप(काष्ठा npa_pool_s));
		पूर्ण
		अवरोध;
	हाल NPA_AQ_INSTOP_NOP:
	हाल NPA_AQ_INSTOP_READ:
	हाल NPA_AQ_INSTOP_LOCK:
	हाल NPA_AQ_INSTOP_UNLOCK:
		अवरोध;
	शेष:
		rc = NPA_AF_ERR_AQ_FULL;
		अवरोध;
	पूर्ण

	अगर (rc) अणु
		spin_unlock(&aq->lock);
		वापस rc;
	पूर्ण

	/* Submit the inकाष्ठाion to AQ */
	rc = npa_aq_enqueue_रुको(rvu, block, &inst);
	अगर (rc) अणु
		spin_unlock(&aq->lock);
		वापस rc;
	पूर्ण

	/* Set aura biपंचांगap अगर aura hw context is enabled */
	अगर (req->ctype == NPA_AQ_CTYPE_AURA) अणु
		अगर (req->op == NPA_AQ_INSTOP_INIT && req->aura.ena)
			__set_bit(req->aura_id, pfvf->aura_bmap);
		अगर (req->op == NPA_AQ_INSTOP_WRITE) अणु
			ena = (req->aura.ena & req->aura_mask.ena) |
				(test_bit(req->aura_id, pfvf->aura_bmap) &
				~req->aura_mask.ena);
			अगर (ena)
				__set_bit(req->aura_id, pfvf->aura_bmap);
			अन्यथा
				__clear_bit(req->aura_id, pfvf->aura_bmap);
		पूर्ण
	पूर्ण

	/* Set pool biपंचांगap अगर pool hw context is enabled */
	अगर (req->ctype == NPA_AQ_CTYPE_POOL) अणु
		अगर (req->op == NPA_AQ_INSTOP_INIT && req->pool.ena)
			__set_bit(req->aura_id, pfvf->pool_bmap);
		अगर (req->op == NPA_AQ_INSTOP_WRITE) अणु
			ena = (req->pool.ena & req->pool_mask.ena) |
				(test_bit(req->aura_id, pfvf->pool_bmap) &
				~req->pool_mask.ena);
			अगर (ena)
				__set_bit(req->aura_id, pfvf->pool_bmap);
			अन्यथा
				__clear_bit(req->aura_id, pfvf->pool_bmap);
		पूर्ण
	पूर्ण
	spin_unlock(&aq->lock);

	अगर (rsp) अणु
		/* Copy पढ़ो context पूर्णांकo mailbox */
		अगर (req->op == NPA_AQ_INSTOP_READ) अणु
			अगर (req->ctype == NPA_AQ_CTYPE_AURA)
				स_नकल(&rsp->aura, ctx,
				       माप(काष्ठा npa_aura_s));
			अन्यथा
				स_नकल(&rsp->pool, ctx,
				       माप(काष्ठा npa_pool_s));
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक npa_lf_hwctx_disable(काष्ठा rvu *rvu, काष्ठा hwctx_disable_req *req)
अणु
	काष्ठा rvu_pfvf *pfvf = rvu_get_pfvf(rvu, req->hdr.pcअगरunc);
	काष्ठा npa_aq_enq_req aq_req;
	अचिन्हित दीर्घ *bmap;
	पूर्णांक id, cnt = 0;
	पूर्णांक err = 0, rc;

	अगर (!pfvf->pool_ctx || !pfvf->aura_ctx)
		वापस NPA_AF_ERR_AQ_ENQUEUE;

	स_रखो(&aq_req, 0, माप(काष्ठा npa_aq_enq_req));
	aq_req.hdr.pcअगरunc = req->hdr.pcअगरunc;

	अगर (req->ctype == NPA_AQ_CTYPE_POOL) अणु
		aq_req.pool.ena = 0;
		aq_req.pool_mask.ena = 1;
		cnt = pfvf->pool_ctx->qsize;
		bmap = pfvf->pool_bmap;
	पूर्ण अन्यथा अगर (req->ctype == NPA_AQ_CTYPE_AURA) अणु
		aq_req.aura.ena = 0;
		aq_req.aura_mask.ena = 1;
		aq_req.aura.bp_ena = 0;
		aq_req.aura_mask.bp_ena = 1;
		cnt = pfvf->aura_ctx->qsize;
		bmap = pfvf->aura_bmap;
	पूर्ण

	aq_req.ctype = req->ctype;
	aq_req.op = NPA_AQ_INSTOP_WRITE;

	क्रम (id = 0; id < cnt; id++) अणु
		अगर (!test_bit(id, bmap))
			जारी;
		aq_req.aura_id = id;
		rc = rvu_npa_aq_enq_inst(rvu, &aq_req, शून्य);
		अगर (rc) अणु
			err = rc;
			dev_err(rvu->dev, "Failed to disable %s:%d context\n",
				(req->ctype == NPA_AQ_CTYPE_AURA) ?
				"Aura" : "Pool", id);
		पूर्ण
	पूर्ण

	वापस err;
पूर्ण

#अगर_घोषित CONFIG_NDC_DIS_DYNAMIC_CACHING
अटल पूर्णांक npa_lf_hwctx_lockकरोwn(काष्ठा rvu *rvu, काष्ठा npa_aq_enq_req *req)
अणु
	काष्ठा npa_aq_enq_req lock_ctx_req;
	पूर्णांक err;

	अगर (req->op != NPA_AQ_INSTOP_INIT)
		वापस 0;

	स_रखो(&lock_ctx_req, 0, माप(काष्ठा npa_aq_enq_req));
	lock_ctx_req.hdr.pcअगरunc = req->hdr.pcअगरunc;
	lock_ctx_req.ctype = req->ctype;
	lock_ctx_req.op = NPA_AQ_INSTOP_LOCK;
	lock_ctx_req.aura_id = req->aura_id;
	err = rvu_npa_aq_enq_inst(rvu, &lock_ctx_req, शून्य);
	अगर (err)
		dev_err(rvu->dev,
			"PFUNC 0x%x: Failed to lock NPA context %s:%d\n",
			req->hdr.pcअगरunc,
			(req->ctype == NPA_AQ_CTYPE_AURA) ?
			"Aura" : "Pool", req->aura_id);
	वापस err;
पूर्ण

पूर्णांक rvu_mbox_handler_npa_aq_enq(काष्ठा rvu *rvu,
				काष्ठा npa_aq_enq_req *req,
				काष्ठा npa_aq_enq_rsp *rsp)
अणु
	पूर्णांक err;

	err = rvu_npa_aq_enq_inst(rvu, req, rsp);
	अगर (!err)
		err = npa_lf_hwctx_lockकरोwn(rvu, req);
	वापस err;
पूर्ण
#अन्यथा

पूर्णांक rvu_mbox_handler_npa_aq_enq(काष्ठा rvu *rvu,
				काष्ठा npa_aq_enq_req *req,
				काष्ठा npa_aq_enq_rsp *rsp)
अणु
	वापस rvu_npa_aq_enq_inst(rvu, req, rsp);
पूर्ण
#पूर्ण_अगर

पूर्णांक rvu_mbox_handler_npa_hwctx_disable(काष्ठा rvu *rvu,
				       काष्ठा hwctx_disable_req *req,
				       काष्ठा msg_rsp *rsp)
अणु
	वापस npa_lf_hwctx_disable(rvu, req);
पूर्ण

अटल व्योम npa_ctx_मुक्त(काष्ठा rvu *rvu, काष्ठा rvu_pfvf *pfvf)
अणु
	kमुक्त(pfvf->aura_bmap);
	pfvf->aura_bmap = शून्य;

	qmem_मुक्त(rvu->dev, pfvf->aura_ctx);
	pfvf->aura_ctx = शून्य;

	kमुक्त(pfvf->pool_bmap);
	pfvf->pool_bmap = शून्य;

	qmem_मुक्त(rvu->dev, pfvf->pool_ctx);
	pfvf->pool_ctx = शून्य;

	qmem_मुक्त(rvu->dev, pfvf->npa_qपूर्णांकs_ctx);
	pfvf->npa_qपूर्णांकs_ctx = शून्य;
पूर्ण

पूर्णांक rvu_mbox_handler_npa_lf_alloc(काष्ठा rvu *rvu,
				  काष्ठा npa_lf_alloc_req *req,
				  काष्ठा npa_lf_alloc_rsp *rsp)
अणु
	पूर्णांक npalf, qपूर्णांकs, hwctx_size, err, rc = 0;
	काष्ठा rvu_hwinfo *hw = rvu->hw;
	u16 pcअगरunc = req->hdr.pcअगरunc;
	काष्ठा rvu_block *block;
	काष्ठा rvu_pfvf *pfvf;
	u64 cfg, ctx_cfg;
	पूर्णांक blkaddr;

	अगर (req->aura_sz > NPA_AURA_SZ_MAX ||
	    req->aura_sz == NPA_AURA_SZ_0 || !req->nr_pools)
		वापस NPA_AF_ERR_PARAM;

	अगर (req->way_mask)
		req->way_mask &= 0xFFFF;

	pfvf = rvu_get_pfvf(rvu, pcअगरunc);
	blkaddr = rvu_get_blkaddr(rvu, BLKTYPE_NPA, pcअगरunc);
	अगर (!pfvf->npalf || blkaddr < 0)
		वापस NPA_AF_ERR_AF_LF_INVALID;

	block = &hw->block[blkaddr];
	npalf = rvu_get_lf(rvu, block, pcअगरunc, 0);
	अगर (npalf < 0)
		वापस NPA_AF_ERR_AF_LF_INVALID;

	/* Reset this NPA LF */
	err = rvu_lf_reset(rvu, block, npalf);
	अगर (err) अणु
		dev_err(rvu->dev, "Failed to reset NPALF%d\n", npalf);
		वापस NPA_AF_ERR_LF_RESET;
	पूर्ण

	ctx_cfg = rvu_पढ़ो64(rvu, blkaddr, NPA_AF_CONST1);

	/* Alloc memory क्रम aura HW contexts */
	hwctx_size = 1UL << (ctx_cfg & 0xF);
	err = qmem_alloc(rvu->dev, &pfvf->aura_ctx,
			 NPA_AURA_COUNT(req->aura_sz), hwctx_size);
	अगर (err)
		जाओ मुक्त_mem;

	pfvf->aura_bmap = kसुस्मृति(NPA_AURA_COUNT(req->aura_sz), माप(दीर्घ),
				  GFP_KERNEL);
	अगर (!pfvf->aura_bmap)
		जाओ मुक्त_mem;

	/* Alloc memory क्रम pool HW contexts */
	hwctx_size = 1UL << ((ctx_cfg >> 4) & 0xF);
	err = qmem_alloc(rvu->dev, &pfvf->pool_ctx, req->nr_pools, hwctx_size);
	अगर (err)
		जाओ मुक्त_mem;

	pfvf->pool_bmap = kसुस्मृति(NPA_AURA_COUNT(req->aura_sz), माप(दीर्घ),
				  GFP_KERNEL);
	अगर (!pfvf->pool_bmap)
		जाओ मुक्त_mem;

	/* Get no of queue पूर्णांकerrupts supported */
	cfg = rvu_पढ़ो64(rvu, blkaddr, NPA_AF_CONST);
	qपूर्णांकs = (cfg >> 28) & 0xFFF;

	/* Alloc memory क्रम Qपूर्णांकs HW contexts */
	hwctx_size = 1UL << ((ctx_cfg >> 8) & 0xF);
	err = qmem_alloc(rvu->dev, &pfvf->npa_qपूर्णांकs_ctx, qपूर्णांकs, hwctx_size);
	अगर (err)
		जाओ मुक्त_mem;

	cfg = rvu_पढ़ो64(rvu, blkaddr, NPA_AF_LFX_AURAS_CFG(npalf));
	/* Clear way partition mask and set aura offset to '0' */
	cfg &= ~(BIT_ULL(34) - 1);
	/* Set aura size & enable caching of contexts */
	cfg |= (req->aura_sz << 16) | BIT_ULL(34) | req->way_mask;

	rvu_ग_लिखो64(rvu, blkaddr, NPA_AF_LFX_AURAS_CFG(npalf), cfg);

	/* Configure aura HW context's base */
	rvu_ग_लिखो64(rvu, blkaddr, NPA_AF_LFX_LOC_AURAS_BASE(npalf),
		    (u64)pfvf->aura_ctx->iova);

	/* Enable caching of qपूर्णांकs hw context */
	rvu_ग_लिखो64(rvu, blkaddr, NPA_AF_LFX_QINTS_CFG(npalf),
		    BIT_ULL(36) | req->way_mask << 20);
	rvu_ग_लिखो64(rvu, blkaddr, NPA_AF_LFX_QINTS_BASE(npalf),
		    (u64)pfvf->npa_qपूर्णांकs_ctx->iova);

	जाओ निकास;

मुक्त_mem:
	npa_ctx_मुक्त(rvu, pfvf);
	rc = -ENOMEM;

निकास:
	/* set stack page info */
	cfg = rvu_पढ़ो64(rvu, blkaddr, NPA_AF_CONST);
	rsp->stack_pg_ptrs = (cfg >> 8) & 0xFF;
	rsp->stack_pg_bytes = cfg & 0xFF;
	rsp->qपूर्णांकs = (cfg >> 28) & 0xFFF;
	वापस rc;
पूर्ण

पूर्णांक rvu_mbox_handler_npa_lf_मुक्त(काष्ठा rvu *rvu, काष्ठा msg_req *req,
				 काष्ठा msg_rsp *rsp)
अणु
	काष्ठा rvu_hwinfo *hw = rvu->hw;
	u16 pcअगरunc = req->hdr.pcअगरunc;
	काष्ठा rvu_block *block;
	काष्ठा rvu_pfvf *pfvf;
	पूर्णांक npalf, err;
	पूर्णांक blkaddr;

	pfvf = rvu_get_pfvf(rvu, pcअगरunc);
	blkaddr = rvu_get_blkaddr(rvu, BLKTYPE_NPA, pcअगरunc);
	अगर (!pfvf->npalf || blkaddr < 0)
		वापस NPA_AF_ERR_AF_LF_INVALID;

	block = &hw->block[blkaddr];
	npalf = rvu_get_lf(rvu, block, pcअगरunc, 0);
	अगर (npalf < 0)
		वापस NPA_AF_ERR_AF_LF_INVALID;

	/* Reset this NPA LF */
	err = rvu_lf_reset(rvu, block, npalf);
	अगर (err) अणु
		dev_err(rvu->dev, "Failed to reset NPALF%d\n", npalf);
		वापस NPA_AF_ERR_LF_RESET;
	पूर्ण

	npa_ctx_मुक्त(rvu, pfvf);

	वापस 0;
पूर्ण

अटल पूर्णांक npa_aq_init(काष्ठा rvu *rvu, काष्ठा rvu_block *block)
अणु
	u64 cfg;
	पूर्णांक err;

	/* Set admin queue endianness */
	cfg = rvu_पढ़ो64(rvu, block->addr, NPA_AF_GEN_CFG);
#अगर_घोषित __BIG_ENDIAN
	cfg |= BIT_ULL(1);
	rvu_ग_लिखो64(rvu, block->addr, NPA_AF_GEN_CFG, cfg);
#अन्यथा
	cfg &= ~BIT_ULL(1);
	rvu_ग_लिखो64(rvu, block->addr, NPA_AF_GEN_CFG, cfg);
#पूर्ण_अगर

	/* Do not bypass NDC cache */
	cfg = rvu_पढ़ो64(rvu, block->addr, NPA_AF_NDC_CFG);
	cfg &= ~0x03DULL;
#अगर_घोषित CONFIG_NDC_DIS_DYNAMIC_CACHING
	/* Disable caching of stack pages */
	cfg |= 0x10ULL;
#पूर्ण_अगर
	rvu_ग_लिखो64(rvu, block->addr, NPA_AF_NDC_CFG, cfg);

	/* Result काष्ठाure can be followed by Aura/Pool context at
	 * RES + 128bytes and a ग_लिखो mask at RES + 256 bytes, depending on
	 * operation type. Alloc sufficient result memory क्रम all operations.
	 */
	err = rvu_aq_alloc(rvu, &block->aq,
			   Q_COUNT(AQ_SIZE), माप(काष्ठा npa_aq_inst_s),
			   ALIGN(माप(काष्ठा npa_aq_res_s), 128) + 256);
	अगर (err)
		वापस err;

	rvu_ग_लिखो64(rvu, block->addr, NPA_AF_AQ_CFG, AQ_SIZE);
	rvu_ग_लिखो64(rvu, block->addr,
		    NPA_AF_AQ_BASE, (u64)block->aq->inst->iova);
	वापस 0;
पूर्ण

पूर्णांक rvu_npa_init(काष्ठा rvu *rvu)
अणु
	काष्ठा rvu_hwinfo *hw = rvu->hw;
	पूर्णांक blkaddr;

	blkaddr = rvu_get_blkaddr(rvu, BLKTYPE_NPA, 0);
	अगर (blkaddr < 0)
		वापस 0;

	/* Initialize admin queue */
	वापस npa_aq_init(rvu, &hw->block[blkaddr]);
पूर्ण

व्योम rvu_npa_मुक्तmem(काष्ठा rvu *rvu)
अणु
	काष्ठा rvu_hwinfo *hw = rvu->hw;
	काष्ठा rvu_block *block;
	पूर्णांक blkaddr;

	blkaddr = rvu_get_blkaddr(rvu, BLKTYPE_NPA, 0);
	अगर (blkaddr < 0)
		वापस;

	block = &hw->block[blkaddr];
	rvu_aq_मुक्त(rvu, block->aq);
पूर्ण

व्योम rvu_npa_lf_tearकरोwn(काष्ठा rvu *rvu, u16 pcअगरunc, पूर्णांक npalf)
अणु
	काष्ठा rvu_pfvf *pfvf = rvu_get_pfvf(rvu, pcअगरunc);
	काष्ठा hwctx_disable_req ctx_req;

	/* Disable all pools */
	ctx_req.hdr.pcअगरunc = pcअगरunc;
	ctx_req.ctype = NPA_AQ_CTYPE_POOL;
	npa_lf_hwctx_disable(rvu, &ctx_req);

	/* Disable all auras */
	ctx_req.ctype = NPA_AQ_CTYPE_AURA;
	npa_lf_hwctx_disable(rvu, &ctx_req);

	npa_ctx_मुक्त(rvu, pfvf);
पूर्ण
