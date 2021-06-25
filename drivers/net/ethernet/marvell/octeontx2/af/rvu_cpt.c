<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/* Copyright (C) 2020 Marvell. */

#समावेश <linux/bitfield.h>
#समावेश <linux/pci.h>
#समावेश "rvu_struct.h"
#समावेश "rvu_reg.h"
#समावेश "mbox.h"
#समावेश "rvu.h"

/* CPT PF device id */
#घोषणा	PCI_DEVID_OTX2_CPT_PF	0xA0FD
#घोषणा	PCI_DEVID_OTX2_CPT10K_PF 0xA0F2

/* Length of initial context fetch in 128 byte words */
#घोषणा CPT_CTX_ILEN    2

#घोषणा cpt_get_eng_sts(e_min, e_max, rsp, etype)                   \
(अणु                                                                  \
	u64 मुक्त_sts = 0, busy_sts = 0;                             \
	typeof(rsp) _rsp = rsp;                                     \
	u32 e, i;                                                   \
								    \
	क्रम (e = (e_min), i = 0; e < (e_max); e++, i++) अणु           \
		reg = rvu_पढ़ो64(rvu, blkaddr, CPT_AF_EXEX_STS(e)); \
		अगर (reg & 0x1)                                      \
			busy_sts |= 1ULL << i;                      \
								    \
		अगर (reg & 0x2)                                      \
			मुक्त_sts |= 1ULL << i;                      \
	पूर्ण                                                           \
	(_rsp)->busy_sts_##etype = busy_sts;                        \
	(_rsp)->मुक्त_sts_##etype = मुक्त_sts;                        \
पूर्ण)

अटल पूर्णांक get_cpt_pf_num(काष्ठा rvu *rvu)
अणु
	पूर्णांक i, करोमुख्य_nr, cpt_pf_num = -1;
	काष्ठा pci_dev *pdev;

	करोमुख्य_nr = pci_करोमुख्य_nr(rvu->pdev->bus);
	क्रम (i = 0; i < rvu->hw->total_pfs; i++) अणु
		pdev = pci_get_करोमुख्य_bus_and_slot(करोमुख्य_nr, i + 1, 0);
		अगर (!pdev)
			जारी;

		अगर (pdev->device == PCI_DEVID_OTX2_CPT_PF ||
		    pdev->device == PCI_DEVID_OTX2_CPT10K_PF) अणु
			cpt_pf_num = i;
			put_device(&pdev->dev);
			अवरोध;
		पूर्ण
		put_device(&pdev->dev);
	पूर्ण
	वापस cpt_pf_num;
पूर्ण

अटल bool is_cpt_pf(काष्ठा rvu *rvu, u16 pcअगरunc)
अणु
	पूर्णांक cpt_pf_num = get_cpt_pf_num(rvu);

	अगर (rvu_get_pf(pcअगरunc) != cpt_pf_num)
		वापस false;
	अगर (pcअगरunc & RVU_PFVF_FUNC_MASK)
		वापस false;

	वापस true;
पूर्ण

अटल bool is_cpt_vf(काष्ठा rvu *rvu, u16 pcअगरunc)
अणु
	पूर्णांक cpt_pf_num = get_cpt_pf_num(rvu);

	अगर (rvu_get_pf(pcअगरunc) != cpt_pf_num)
		वापस false;
	अगर (!(pcअगरunc & RVU_PFVF_FUNC_MASK))
		वापस false;

	वापस true;
पूर्ण

अटल पूर्णांक validate_and_get_cpt_blkaddr(पूर्णांक req_blkaddr)
अणु
	पूर्णांक blkaddr;

	blkaddr = req_blkaddr ? req_blkaddr : BLKADDR_CPT0;
	अगर (blkaddr != BLKADDR_CPT0 && blkaddr != BLKADDR_CPT1)
		वापस -EINVAL;

	वापस blkaddr;
पूर्ण

पूर्णांक rvu_mbox_handler_cpt_lf_alloc(काष्ठा rvu *rvu,
				  काष्ठा cpt_lf_alloc_req_msg *req,
				  काष्ठा msg_rsp *rsp)
अणु
	u16 pcअगरunc = req->hdr.pcअगरunc;
	काष्ठा rvu_block *block;
	पूर्णांक cptlf, blkaddr;
	पूर्णांक num_lfs, slot;
	u64 val;

	blkaddr = validate_and_get_cpt_blkaddr(req->blkaddr);
	अगर (blkaddr < 0)
		वापस blkaddr;

	अगर (req->eng_grpmsk == 0x0)
		वापस CPT_AF_ERR_GRP_INVALID;

	block = &rvu->hw->block[blkaddr];
	num_lfs = rvu_get_rsrc_mapcount(rvu_get_pfvf(rvu, pcअगरunc),
					block->addr);
	अगर (!num_lfs)
		वापस CPT_AF_ERR_LF_INVALID;

	/* Check अगर requested 'CPTLF <=> NIXLF' mapping is valid */
	अगर (req->nix_pf_func) अणु
		/* If शेष, use 'this' CPTLF's PFFUNC */
		अगर (req->nix_pf_func == RVU_DEFAULT_PF_FUNC)
			req->nix_pf_func = pcअगरunc;
		अगर (!is_pffunc_map_valid(rvu, req->nix_pf_func, BLKTYPE_NIX))
			वापस CPT_AF_ERR_NIX_PF_FUNC_INVALID;
	पूर्ण

	/* Check अगर requested 'CPTLF <=> SSOLF' mapping is valid */
	अगर (req->sso_pf_func) अणु
		/* If शेष, use 'this' CPTLF's PFFUNC */
		अगर (req->sso_pf_func == RVU_DEFAULT_PF_FUNC)
			req->sso_pf_func = pcअगरunc;
		अगर (!is_pffunc_map_valid(rvu, req->sso_pf_func, BLKTYPE_SSO))
			वापस CPT_AF_ERR_SSO_PF_FUNC_INVALID;
	पूर्ण

	क्रम (slot = 0; slot < num_lfs; slot++) अणु
		cptlf = rvu_get_lf(rvu, block, pcअगरunc, slot);
		अगर (cptlf < 0)
			वापस CPT_AF_ERR_LF_INVALID;

		/* Set CPT LF group and priority */
		val = (u64)req->eng_grpmsk << 48 | 1;
		अगर (!is_rvu_otx2(rvu))
			val |= (CPT_CTX_ILEN << 17);

		rvu_ग_लिखो64(rvu, blkaddr, CPT_AF_LFX_CTL(cptlf), val);

		/* Set CPT LF NIX_PF_FUNC and SSO_PF_FUNC */
		val = (u64)req->nix_pf_func << 48 |
		      (u64)req->sso_pf_func << 32;
		rvu_ग_लिखो64(rvu, blkaddr, CPT_AF_LFX_CTL2(cptlf), val);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक cpt_lf_मुक्त(काष्ठा rvu *rvu, काष्ठा msg_req *req, पूर्णांक blkaddr)
अणु
	u16 pcअगरunc = req->hdr.pcअगरunc;
	पूर्णांक num_lfs, cptlf, slot;
	काष्ठा rvu_block *block;

	block = &rvu->hw->block[blkaddr];
	num_lfs = rvu_get_rsrc_mapcount(rvu_get_pfvf(rvu, pcअगरunc),
					block->addr);
	अगर (!num_lfs)
		वापस 0;

	क्रम (slot = 0; slot < num_lfs; slot++) अणु
		cptlf = rvu_get_lf(rvu, block, pcअगरunc, slot);
		अगर (cptlf < 0)
			वापस CPT_AF_ERR_LF_INVALID;

		/* Reset CPT LF group and priority */
		rvu_ग_लिखो64(rvu, blkaddr, CPT_AF_LFX_CTL(cptlf), 0x0);
		/* Reset CPT LF NIX_PF_FUNC and SSO_PF_FUNC */
		rvu_ग_लिखो64(rvu, blkaddr, CPT_AF_LFX_CTL2(cptlf), 0x0);
	पूर्ण

	वापस 0;
पूर्ण

पूर्णांक rvu_mbox_handler_cpt_lf_मुक्त(काष्ठा rvu *rvu, काष्ठा msg_req *req,
				 काष्ठा msg_rsp *rsp)
अणु
	पूर्णांक ret;

	ret = cpt_lf_मुक्त(rvu, req, BLKADDR_CPT0);
	अगर (ret)
		वापस ret;

	अगर (is_block_implemented(rvu->hw, BLKADDR_CPT1))
		ret = cpt_lf_मुक्त(rvu, req, BLKADDR_CPT1);

	वापस ret;
पूर्ण

अटल bool is_valid_offset(काष्ठा rvu *rvu, काष्ठा cpt_rd_wr_reg_msg *req)
अणु
	u64 offset = req->reg_offset;
	पूर्णांक blkaddr, num_lfs, lf;
	काष्ठा rvu_block *block;
	काष्ठा rvu_pfvf *pfvf;

	blkaddr = validate_and_get_cpt_blkaddr(req->blkaddr);
	अगर (blkaddr < 0)
		वापस blkaddr;

	/* Registers that can be accessed from PF/VF */
	अगर ((offset & 0xFF000) ==  CPT_AF_LFX_CTL(0) ||
	    (offset & 0xFF000) ==  CPT_AF_LFX_CTL2(0)) अणु
		अगर (offset & 7)
			वापस false;

		lf = (offset & 0xFFF) >> 3;
		block = &rvu->hw->block[blkaddr];
		pfvf = rvu_get_pfvf(rvu, req->hdr.pcअगरunc);
		num_lfs = rvu_get_rsrc_mapcount(pfvf, block->addr);
		अगर (lf >= num_lfs)
			/* Slot is not valid क्रम that PF/VF */
			वापस false;

		/* Translate local LF used by VFs to global CPT LF */
		lf = rvu_get_lf(rvu, &rvu->hw->block[blkaddr],
				req->hdr.pcअगरunc, lf);
		अगर (lf < 0)
			वापस false;

		वापस true;
	पूर्ण अन्यथा अगर (!(req->hdr.pcअगरunc & RVU_PFVF_FUNC_MASK)) अणु
		/* Registers that can be accessed from PF */
		चयन (offset) अणु
		हाल CPT_AF_CTL:
		हाल CPT_AF_PF_FUNC:
		हाल CPT_AF_BLK_RST:
		हाल CPT_AF_CONSTANTS1:
		हाल CPT_AF_CTX_FLUSH_TIMER:
			वापस true;
		पूर्ण

		चयन (offset & 0xFF000) अणु
		हाल CPT_AF_EXEX_STS(0):
		हाल CPT_AF_EXEX_CTL(0):
		हाल CPT_AF_EXEX_CTL2(0):
		हाल CPT_AF_EXEX_UCODE_BASE(0):
			अगर (offset & 7)
				वापस false;
			अवरोध;
		शेष:
			वापस false;
		पूर्ण
		वापस true;
	पूर्ण
	वापस false;
पूर्ण

पूर्णांक rvu_mbox_handler_cpt_rd_wr_रेजिस्टर(काष्ठा rvu *rvu,
					काष्ठा cpt_rd_wr_reg_msg *req,
					काष्ठा cpt_rd_wr_reg_msg *rsp)
अणु
	पूर्णांक blkaddr;

	blkaddr = validate_and_get_cpt_blkaddr(req->blkaddr);
	अगर (blkaddr < 0)
		वापस blkaddr;

	/* This message is accepted only अगर sent from CPT PF/VF */
	अगर (!is_cpt_pf(rvu, req->hdr.pcअगरunc) &&
	    !is_cpt_vf(rvu, req->hdr.pcअगरunc))
		वापस CPT_AF_ERR_ACCESS_DENIED;

	rsp->reg_offset = req->reg_offset;
	rsp->ret_val = req->ret_val;
	rsp->is_ग_लिखो = req->is_ग_लिखो;

	अगर (!is_valid_offset(rvu, req))
		वापस CPT_AF_ERR_ACCESS_DENIED;

	अगर (req->is_ग_लिखो)
		rvu_ग_लिखो64(rvu, blkaddr, req->reg_offset, req->val);
	अन्यथा
		rsp->val = rvu_पढ़ो64(rvu, blkaddr, req->reg_offset);

	वापस 0;
पूर्ण

अटल व्योम get_ctx_pc(काष्ठा rvu *rvu, काष्ठा cpt_sts_rsp *rsp, पूर्णांक blkaddr)
अणु
	अगर (is_rvu_otx2(rvu))
		वापस;

	rsp->ctx_mis_pc = rvu_पढ़ो64(rvu, blkaddr, CPT_AF_CTX_MIS_PC);
	rsp->ctx_hit_pc = rvu_पढ़ो64(rvu, blkaddr, CPT_AF_CTX_HIT_PC);
	rsp->ctx_aop_pc = rvu_पढ़ो64(rvu, blkaddr, CPT_AF_CTX_AOP_PC);
	rsp->ctx_aop_lat_pc = rvu_पढ़ो64(rvu, blkaddr,
					 CPT_AF_CTX_AOP_LATENCY_PC);
	rsp->ctx_अगरetch_pc = rvu_पढ़ो64(rvu, blkaddr, CPT_AF_CTX_IFETCH_PC);
	rsp->ctx_अगरetch_lat_pc = rvu_पढ़ो64(rvu, blkaddr,
					    CPT_AF_CTX_IFETCH_LATENCY_PC);
	rsp->ctx_ffetch_pc = rvu_पढ़ो64(rvu, blkaddr, CPT_AF_CTX_FFETCH_PC);
	rsp->ctx_ffetch_lat_pc = rvu_पढ़ो64(rvu, blkaddr,
					    CPT_AF_CTX_FFETCH_LATENCY_PC);
	rsp->ctx_wback_pc = rvu_पढ़ो64(rvu, blkaddr, CPT_AF_CTX_FFETCH_PC);
	rsp->ctx_wback_lat_pc = rvu_पढ़ो64(rvu, blkaddr,
					   CPT_AF_CTX_FFETCH_LATENCY_PC);
	rsp->ctx_psh_pc = rvu_पढ़ो64(rvu, blkaddr, CPT_AF_CTX_FFETCH_PC);
	rsp->ctx_psh_lat_pc = rvu_पढ़ो64(rvu, blkaddr,
					 CPT_AF_CTX_FFETCH_LATENCY_PC);
	rsp->ctx_err = rvu_पढ़ो64(rvu, blkaddr, CPT_AF_CTX_ERR);
	rsp->ctx_enc_id = rvu_पढ़ो64(rvu, blkaddr, CPT_AF_CTX_ENC_ID);
	rsp->ctx_flush_समयr = rvu_पढ़ो64(rvu, blkaddr, CPT_AF_CTX_FLUSH_TIMER);

	rsp->rxc_समय = rvu_पढ़ो64(rvu, blkaddr, CPT_AF_RXC_TIME);
	rsp->rxc_समय_cfg = rvu_पढ़ो64(rvu, blkaddr, CPT_AF_RXC_TIME_CFG);
	rsp->rxc_active_sts = rvu_पढ़ो64(rvu, blkaddr, CPT_AF_RXC_ACTIVE_STS);
	rsp->rxc_zombie_sts = rvu_पढ़ो64(rvu, blkaddr, CPT_AF_RXC_ZOMBIE_STS);
	rsp->rxc_dfrg = rvu_पढ़ो64(rvu, blkaddr, CPT_AF_RXC_DFRG);
	rsp->x2p_link_cfg0 = rvu_पढ़ो64(rvu, blkaddr, CPT_AF_X2PX_LINK_CFG(0));
	rsp->x2p_link_cfg1 = rvu_पढ़ो64(rvu, blkaddr, CPT_AF_X2PX_LINK_CFG(1));
पूर्ण

अटल व्योम get_eng_sts(काष्ठा rvu *rvu, काष्ठा cpt_sts_rsp *rsp, पूर्णांक blkaddr)
अणु
	u16 max_ses, max_ies, max_aes;
	u32 e_min = 0, e_max = 0;
	u64 reg;

	reg = rvu_पढ़ो64(rvu, blkaddr, CPT_AF_CONSTANTS1);
	max_ses = reg & 0xffff;
	max_ies = (reg >> 16) & 0xffff;
	max_aes = (reg >> 32) & 0xffff;

	/* Get AE status */
	e_min = max_ses + max_ies;
	e_max = max_ses + max_ies + max_aes;
	cpt_get_eng_sts(e_min, e_max, rsp, ae);
	/* Get SE status */
	e_min = 0;
	e_max = max_ses;
	cpt_get_eng_sts(e_min, e_max, rsp, se);
	/* Get IE status */
	e_min = max_ses;
	e_max = max_ses + max_ies;
	cpt_get_eng_sts(e_min, e_max, rsp, ie);
पूर्ण

पूर्णांक rvu_mbox_handler_cpt_sts(काष्ठा rvu *rvu, काष्ठा cpt_sts_req *req,
			     काष्ठा cpt_sts_rsp *rsp)
अणु
	पूर्णांक blkaddr;

	blkaddr = validate_and_get_cpt_blkaddr(req->blkaddr);
	अगर (blkaddr < 0)
		वापस blkaddr;

	/* This message is accepted only अगर sent from CPT PF/VF */
	अगर (!is_cpt_pf(rvu, req->hdr.pcअगरunc) &&
	    !is_cpt_vf(rvu, req->hdr.pcअगरunc))
		वापस CPT_AF_ERR_ACCESS_DENIED;

	get_ctx_pc(rvu, rsp, blkaddr);

	/* Get CPT engines status */
	get_eng_sts(rvu, rsp, blkaddr);

	/* Read CPT inकाष्ठाion PC रेजिस्टरs */
	rsp->inst_req_pc = rvu_पढ़ो64(rvu, blkaddr, CPT_AF_INST_REQ_PC);
	rsp->inst_lat_pc = rvu_पढ़ो64(rvu, blkaddr, CPT_AF_INST_LATENCY_PC);
	rsp->rd_req_pc = rvu_पढ़ो64(rvu, blkaddr, CPT_AF_RD_REQ_PC);
	rsp->rd_lat_pc = rvu_पढ़ो64(rvu, blkaddr, CPT_AF_RD_LATENCY_PC);
	rsp->rd_uc_pc = rvu_पढ़ो64(rvu, blkaddr, CPT_AF_RD_UC_PC);
	rsp->active_cycles_pc = rvu_पढ़ो64(rvu, blkaddr,
					   CPT_AF_ACTIVE_CYCLES_PC);
	rsp->exe_err_info = rvu_पढ़ो64(rvu, blkaddr, CPT_AF_EXE_ERR_INFO);
	rsp->cptclk_cnt = rvu_पढ़ो64(rvu, blkaddr, CPT_AF_CPTCLK_CNT);
	rsp->diag = rvu_पढ़ो64(rvu, blkaddr, CPT_AF_DIAG);

	वापस 0;
पूर्ण

#घोषणा RXC_ZOMBIE_THRES  GENMASK_ULL(59, 48)
#घोषणा RXC_ZOMBIE_LIMIT  GENMASK_ULL(43, 32)
#घोषणा RXC_ACTIVE_THRES  GENMASK_ULL(27, 16)
#घोषणा RXC_ACTIVE_LIMIT  GENMASK_ULL(11, 0)
#घोषणा RXC_ACTIVE_COUNT  GENMASK_ULL(60, 48)
#घोषणा RXC_ZOMBIE_COUNT  GENMASK_ULL(60, 48)

अटल व्योम cpt_rxc_समय_cfg(काष्ठा rvu *rvu, काष्ठा cpt_rxc_समय_cfg_req *req,
			     पूर्णांक blkaddr)
अणु
	u64 dfrg_reg;

	dfrg_reg = FIELD_PREP(RXC_ZOMBIE_THRES, req->zombie_thres);
	dfrg_reg |= FIELD_PREP(RXC_ZOMBIE_LIMIT, req->zombie_limit);
	dfrg_reg |= FIELD_PREP(RXC_ACTIVE_THRES, req->active_thres);
	dfrg_reg |= FIELD_PREP(RXC_ACTIVE_LIMIT, req->active_limit);

	rvu_ग_लिखो64(rvu, blkaddr, CPT_AF_RXC_TIME_CFG, req->step);
	rvu_ग_लिखो64(rvu, blkaddr, CPT_AF_RXC_DFRG, dfrg_reg);
पूर्ण

पूर्णांक rvu_mbox_handler_cpt_rxc_समय_cfg(काष्ठा rvu *rvu,
				      काष्ठा cpt_rxc_समय_cfg_req *req,
				      काष्ठा msg_rsp *rsp)
अणु
	पूर्णांक blkaddr;

	blkaddr = validate_and_get_cpt_blkaddr(req->blkaddr);
	अगर (blkaddr < 0)
		वापस blkaddr;

	/* This message is accepted only अगर sent from CPT PF/VF */
	अगर (!is_cpt_pf(rvu, req->hdr.pcअगरunc) &&
	    !is_cpt_vf(rvu, req->hdr.pcअगरunc))
		वापस CPT_AF_ERR_ACCESS_DENIED;

	cpt_rxc_समय_cfg(rvu, req, blkaddr);

	वापस 0;
पूर्ण

#घोषणा INPROG_INFLIGHT(reg)    ((reg) & 0x1FF)
#घोषणा INPROG_GRB_PARTIAL(reg) ((reg) & BIT_ULL(31))
#घोषणा INPROG_GRB(reg)         (((reg) >> 32) & 0xFF)
#घोषणा INPROG_GWB(reg)         (((reg) >> 40) & 0xFF)

अटल व्योम cpt_lf_disable_iqueue(काष्ठा rvu *rvu, पूर्णांक blkaddr, पूर्णांक slot)
अणु
	पूर्णांक i = 0, hard_lp_ctr = 100000;
	u64 inprog, grp_ptr;
	u16 nq_ptr, dq_ptr;

	/* Disable inकाष्ठाions enqueuing */
	rvu_ग_लिखो64(rvu, blkaddr, CPT_AF_BAR2_ALIASX(slot, CPT_LF_CTL), 0x0);

	/* Disable executions in the LF's queue */
	inprog = rvu_पढ़ो64(rvu, blkaddr,
			    CPT_AF_BAR2_ALIASX(slot, CPT_LF_INPROG));
	inprog &= ~BIT_ULL(16);
	rvu_ग_लिखो64(rvu, blkaddr,
		    CPT_AF_BAR2_ALIASX(slot, CPT_LF_INPROG), inprog);

	/* Wait क्रम CPT queue to become execution-quiescent */
	करो अणु
		inprog = rvu_पढ़ो64(rvu, blkaddr,
				    CPT_AF_BAR2_ALIASX(slot, CPT_LF_INPROG));
		अगर (INPROG_GRB_PARTIAL(inprog)) अणु
			i = 0;
			hard_lp_ctr--;
		पूर्ण अन्यथा अणु
			i++;
		पूर्ण

		grp_ptr = rvu_पढ़ो64(rvu, blkaddr,
				     CPT_AF_BAR2_ALIASX(slot,
							CPT_LF_Q_GRP_PTR));
		nq_ptr = (grp_ptr >> 32) & 0x7FFF;
		dq_ptr = grp_ptr & 0x7FFF;

	पूर्ण जबतक (hard_lp_ctr && (i < 10) && (nq_ptr != dq_ptr));

	अगर (hard_lp_ctr == 0)
		dev_warn(rvu->dev, "CPT FLR hits hard loop counter\n");

	i = 0;
	hard_lp_ctr = 100000;
	करो अणु
		inprog = rvu_पढ़ो64(rvu, blkaddr,
				    CPT_AF_BAR2_ALIASX(slot, CPT_LF_INPROG));

		अगर ((INPROG_INFLIGHT(inprog) == 0) &&
		    (INPROG_GWB(inprog) < 40) &&
		    ((INPROG_GRB(inprog) == 0) ||
		     (INPROG_GRB((inprog)) == 40))) अणु
			i++;
		पूर्ण अन्यथा अणु
			i = 0;
			hard_lp_ctr--;
		पूर्ण
	पूर्ण जबतक (hard_lp_ctr && (i < 10));

	अगर (hard_lp_ctr == 0)
		dev_warn(rvu->dev, "CPT FLR hits hard loop counter\n");
पूर्ण

पूर्णांक rvu_cpt_lf_tearकरोwn(काष्ठा rvu *rvu, u16 pcअगरunc, पूर्णांक lf, पूर्णांक slot)
अणु
	पूर्णांक blkaddr;
	u64 reg;

	blkaddr = rvu_get_blkaddr(rvu, BLKTYPE_CPT, pcअगरunc);
	अगर (blkaddr != BLKADDR_CPT0 && blkaddr != BLKADDR_CPT1)
		वापस -EINVAL;

	/* Enable BAR2 ALIAS क्रम this pcअगरunc. */
	reg = BIT_ULL(16) | pcअगरunc;
	rvu_ग_लिखो64(rvu, blkaddr, CPT_AF_BAR2_SEL, reg);

	cpt_lf_disable_iqueue(rvu, blkaddr, slot);

	/* Set group drop to help clear out hardware */
	reg = rvu_पढ़ो64(rvu, blkaddr, CPT_AF_BAR2_ALIASX(slot, CPT_LF_INPROG));
	reg |= BIT_ULL(17);
	rvu_ग_लिखो64(rvu, blkaddr, CPT_AF_BAR2_ALIASX(slot, CPT_LF_INPROG), reg);

	rvu_ग_लिखो64(rvu, blkaddr, CPT_AF_BAR2_SEL, 0);

	वापस 0;
पूर्ण
