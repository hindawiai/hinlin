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
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/delay.h>
#समावेश <linux/irq.h>
#समावेश <linux/pci.h>
#समावेश <linux/sysfs.h>

#समावेश "cgx.h"
#समावेश "rvu.h"
#समावेश "rvu_reg.h"
#समावेश "ptp.h"

#समावेश "rvu_trace.h"

#घोषणा DRV_NAME	"rvu_af"
#घोषणा DRV_STRING      "Marvell OcteonTX2 RVU Admin Function Driver"

अटल पूर्णांक rvu_get_hwvf(काष्ठा rvu *rvu, पूर्णांक pcअगरunc);

अटल व्योम rvu_set_msix_offset(काष्ठा rvu *rvu, काष्ठा rvu_pfvf *pfvf,
				काष्ठा rvu_block *block, पूर्णांक lf);
अटल व्योम rvu_clear_msix_offset(काष्ठा rvu *rvu, काष्ठा rvu_pfvf *pfvf,
				  काष्ठा rvu_block *block, पूर्णांक lf);
अटल व्योम __rvu_flr_handler(काष्ठा rvu *rvu, u16 pcअगरunc);

अटल पूर्णांक rvu_mbox_init(काष्ठा rvu *rvu, काष्ठा mbox_wq_info *mw,
			 पूर्णांक type, पूर्णांक num,
			 व्योम (mbox_handler)(काष्ठा work_काष्ठा *),
			 व्योम (mbox_up_handler)(काष्ठा work_काष्ठा *));
क्रमागत अणु
	TYPE_AFVF,
	TYPE_AFPF,
पूर्ण;

/* Supported devices */
अटल स्थिर काष्ठा pci_device_id rvu_id_table[] = अणु
	अणु PCI_DEVICE(PCI_VENDOR_ID_CAVIUM, PCI_DEVID_OCTEONTX2_RVU_AF) पूर्ण,
	अणु 0, पूर्ण  /* end of table */
पूर्ण;

MODULE_AUTHOR("Sunil Goutham <sgoutham@marvell.com>");
MODULE_DESCRIPTION(DRV_STRING);
MODULE_LICENSE("GPL v2");
MODULE_DEVICE_TABLE(pci, rvu_id_table);

अटल अक्षर *mkex_profile; /* MKEX profile name */
module_param(mkex_profile, अक्षरp, 0000);
MODULE_PARM_DESC(mkex_profile, "MKEX profile name string");

अटल व्योम rvu_setup_hw_capabilities(काष्ठा rvu *rvu)
अणु
	काष्ठा rvu_hwinfo *hw = rvu->hw;

	hw->cap.nix_tx_aggr_lvl = NIX_TXSCH_LVL_TL1;
	hw->cap.nix_fixed_txschq_mapping = false;
	hw->cap.nix_shaping = true;
	hw->cap.nix_tx_link_bp = true;
	hw->cap.nix_rx_multicast = true;
	hw->rvu = rvu;

	अगर (is_rvu_96xx_B0(rvu)) अणु
		hw->cap.nix_fixed_txschq_mapping = true;
		hw->cap.nix_txsch_per_cgx_lmac = 4;
		hw->cap.nix_txsch_per_lbk_lmac = 132;
		hw->cap.nix_txsch_per_sdp_lmac = 76;
		hw->cap.nix_shaping = false;
		hw->cap.nix_tx_link_bp = false;
		अगर (is_rvu_96xx_A0(rvu))
			hw->cap.nix_rx_multicast = false;
	पूर्ण

	अगर (!is_rvu_otx2(rvu))
		hw->cap.per_pf_mbox_regs = true;
पूर्ण

/* Poll a RVU block's register 'offset', for a 'zero'
 * or 'nonzero' at bits specified by 'mask'
 */
पूर्णांक rvu_poll_reg(काष्ठा rvu *rvu, u64 block, u64 offset, u64 mask, bool zero)
अणु
	अचिन्हित दीर्घ समयout = jअगरfies + usecs_to_jअगरfies(10000);
	व्योम __iomem *reg;
	u64 reg_val;

	reg = rvu->afreg_base + ((block << 28) | offset);
again:
	reg_val = पढ़ोq(reg);
	अगर (zero && !(reg_val & mask))
		वापस 0;
	अगर (!zero && (reg_val & mask))
		वापस 0;
	अगर (समय_beक्रमe(jअगरfies, समयout)) अणु
		usleep_range(1, 5);
		जाओ again;
	पूर्ण
	वापस -EBUSY;
पूर्ण

पूर्णांक rvu_alloc_rsrc(काष्ठा rsrc_bmap *rsrc)
अणु
	पूर्णांक id;

	अगर (!rsrc->bmap)
		वापस -EINVAL;

	id = find_first_zero_bit(rsrc->bmap, rsrc->max);
	अगर (id >= rsrc->max)
		वापस -ENOSPC;

	__set_bit(id, rsrc->bmap);

	वापस id;
पूर्ण

पूर्णांक rvu_alloc_rsrc_contig(काष्ठा rsrc_bmap *rsrc, पूर्णांक nrsrc)
अणु
	पूर्णांक start;

	अगर (!rsrc->bmap)
		वापस -EINVAL;

	start = biपंचांगap_find_next_zero_area(rsrc->bmap, rsrc->max, 0, nrsrc, 0);
	अगर (start >= rsrc->max)
		वापस -ENOSPC;

	biपंचांगap_set(rsrc->bmap, start, nrsrc);
	वापस start;
पूर्ण

अटल व्योम rvu_मुक्त_rsrc_contig(काष्ठा rsrc_bmap *rsrc, पूर्णांक nrsrc, पूर्णांक start)
अणु
	अगर (!rsrc->bmap)
		वापस;
	अगर (start >= rsrc->max)
		वापस;

	biपंचांगap_clear(rsrc->bmap, start, nrsrc);
पूर्ण

bool rvu_rsrc_check_contig(काष्ठा rsrc_bmap *rsrc, पूर्णांक nrsrc)
अणु
	पूर्णांक start;

	अगर (!rsrc->bmap)
		वापस false;

	start = biपंचांगap_find_next_zero_area(rsrc->bmap, rsrc->max, 0, nrsrc, 0);
	अगर (start >= rsrc->max)
		वापस false;

	वापस true;
पूर्ण

व्योम rvu_मुक्त_rsrc(काष्ठा rsrc_bmap *rsrc, पूर्णांक id)
अणु
	अगर (!rsrc->bmap)
		वापस;

	__clear_bit(id, rsrc->bmap);
पूर्ण

पूर्णांक rvu_rsrc_मुक्त_count(काष्ठा rsrc_bmap *rsrc)
अणु
	पूर्णांक used;

	अगर (!rsrc->bmap)
		वापस 0;

	used = biपंचांगap_weight(rsrc->bmap, rsrc->max);
	वापस (rsrc->max - used);
पूर्ण

पूर्णांक rvu_alloc_biपंचांगap(काष्ठा rsrc_bmap *rsrc)
अणु
	rsrc->bmap = kसुस्मृति(BITS_TO_LONGS(rsrc->max),
			     माप(दीर्घ), GFP_KERNEL);
	अगर (!rsrc->bmap)
		वापस -ENOMEM;
	वापस 0;
पूर्ण

/* Get block LF's HW index from a PF_FUNC's block slot number */
पूर्णांक rvu_get_lf(काष्ठा rvu *rvu, काष्ठा rvu_block *block, u16 pcअगरunc, u16 slot)
अणु
	u16 match = 0;
	पूर्णांक lf;

	mutex_lock(&rvu->rsrc_lock);
	क्रम (lf = 0; lf < block->lf.max; lf++) अणु
		अगर (block->fn_map[lf] == pcअगरunc) अणु
			अगर (slot == match) अणु
				mutex_unlock(&rvu->rsrc_lock);
				वापस lf;
			पूर्ण
			match++;
		पूर्ण
	पूर्ण
	mutex_unlock(&rvu->rsrc_lock);
	वापस -ENODEV;
पूर्ण

/* Convert BLOCK_TYPE_E to a BLOCK_ADDR_E.
 * Some silicon variants of OcteonTX2 supports
 * multiple blocks of same type.
 *
 * @pcअगरunc has to be zero when no LF is yet attached.
 *
 * For a pcअगरunc अगर LFs are attached from multiple blocks of same type, then
 * वापस blkaddr of first encountered block.
 */
पूर्णांक rvu_get_blkaddr(काष्ठा rvu *rvu, पूर्णांक blktype, u16 pcअगरunc)
अणु
	पूर्णांक devnum, blkaddr = -ENODEV;
	u64 cfg, reg;
	bool is_pf;

	चयन (blktype) अणु
	हाल BLKTYPE_NPC:
		blkaddr = BLKADDR_NPC;
		जाओ निकास;
	हाल BLKTYPE_NPA:
		blkaddr = BLKADDR_NPA;
		जाओ निकास;
	हाल BLKTYPE_NIX:
		/* For now assume NIX0 */
		अगर (!pcअगरunc) अणु
			blkaddr = BLKADDR_NIX0;
			जाओ निकास;
		पूर्ण
		अवरोध;
	हाल BLKTYPE_SSO:
		blkaddr = BLKADDR_SSO;
		जाओ निकास;
	हाल BLKTYPE_SSOW:
		blkaddr = BLKADDR_SSOW;
		जाओ निकास;
	हाल BLKTYPE_TIM:
		blkaddr = BLKADDR_TIM;
		जाओ निकास;
	हाल BLKTYPE_CPT:
		/* For now assume CPT0 */
		अगर (!pcअगरunc) अणु
			blkaddr = BLKADDR_CPT0;
			जाओ निकास;
		पूर्ण
		अवरोध;
	पूर्ण

	/* Check अगर this is a RVU PF or VF */
	अगर (pcअगरunc & RVU_PFVF_FUNC_MASK) अणु
		is_pf = false;
		devnum = rvu_get_hwvf(rvu, pcअगरunc);
	पूर्ण अन्यथा अणु
		is_pf = true;
		devnum = rvu_get_pf(pcअगरunc);
	पूर्ण

	/* Check अगर the 'pcifunc' has a NIX LF from 'BLKADDR_NIX0' or
	 * 'BLKADDR_NIX1'.
	 */
	अगर (blktype == BLKTYPE_NIX) अणु
		reg = is_pf ? RVU_PRIV_PFX_NIXX_CFG(0) :
			RVU_PRIV_HWVFX_NIXX_CFG(0);
		cfg = rvu_पढ़ो64(rvu, BLKADDR_RVUM, reg | (devnum << 16));
		अगर (cfg) अणु
			blkaddr = BLKADDR_NIX0;
			जाओ निकास;
		पूर्ण

		reg = is_pf ? RVU_PRIV_PFX_NIXX_CFG(1) :
			RVU_PRIV_HWVFX_NIXX_CFG(1);
		cfg = rvu_पढ़ो64(rvu, BLKADDR_RVUM, reg | (devnum << 16));
		अगर (cfg)
			blkaddr = BLKADDR_NIX1;
	पूर्ण

	अगर (blktype == BLKTYPE_CPT) अणु
		reg = is_pf ? RVU_PRIV_PFX_CPTX_CFG(0) :
			RVU_PRIV_HWVFX_CPTX_CFG(0);
		cfg = rvu_पढ़ो64(rvu, BLKADDR_RVUM, reg | (devnum << 16));
		अगर (cfg) अणु
			blkaddr = BLKADDR_CPT0;
			जाओ निकास;
		पूर्ण

		reg = is_pf ? RVU_PRIV_PFX_CPTX_CFG(1) :
			RVU_PRIV_HWVFX_CPTX_CFG(1);
		cfg = rvu_पढ़ो64(rvu, BLKADDR_RVUM, reg | (devnum << 16));
		अगर (cfg)
			blkaddr = BLKADDR_CPT1;
	पूर्ण

निकास:
	अगर (is_block_implemented(rvu->hw, blkaddr))
		वापस blkaddr;
	वापस -ENODEV;
पूर्ण

अटल व्योम rvu_update_rsrc_map(काष्ठा rvu *rvu, काष्ठा rvu_pfvf *pfvf,
				काष्ठा rvu_block *block, u16 pcअगरunc,
				u16 lf, bool attach)
अणु
	पूर्णांक devnum, num_lfs = 0;
	bool is_pf;
	u64 reg;

	अगर (lf >= block->lf.max) अणु
		dev_err(&rvu->pdev->dev,
			"%s: FATAL: LF %d is >= %s's max lfs i.e %d\n",
			__func__, lf, block->name, block->lf.max);
		वापस;
	पूर्ण

	/* Check अगर this is क्रम a RVU PF or VF */
	अगर (pcअगरunc & RVU_PFVF_FUNC_MASK) अणु
		is_pf = false;
		devnum = rvu_get_hwvf(rvu, pcअगरunc);
	पूर्ण अन्यथा अणु
		is_pf = true;
		devnum = rvu_get_pf(pcअगरunc);
	पूर्ण

	block->fn_map[lf] = attach ? pcअगरunc : 0;

	चयन (block->addr) अणु
	हाल BLKADDR_NPA:
		pfvf->npalf = attach ? true : false;
		num_lfs = pfvf->npalf;
		अवरोध;
	हाल BLKADDR_NIX0:
	हाल BLKADDR_NIX1:
		pfvf->nixlf = attach ? true : false;
		num_lfs = pfvf->nixlf;
		अवरोध;
	हाल BLKADDR_SSO:
		attach ? pfvf->sso++ : pfvf->sso--;
		num_lfs = pfvf->sso;
		अवरोध;
	हाल BLKADDR_SSOW:
		attach ? pfvf->ssow++ : pfvf->ssow--;
		num_lfs = pfvf->ssow;
		अवरोध;
	हाल BLKADDR_TIM:
		attach ? pfvf->timlfs++ : pfvf->timlfs--;
		num_lfs = pfvf->timlfs;
		अवरोध;
	हाल BLKADDR_CPT0:
		attach ? pfvf->cptlfs++ : pfvf->cptlfs--;
		num_lfs = pfvf->cptlfs;
		अवरोध;
	हाल BLKADDR_CPT1:
		attach ? pfvf->cpt1_lfs++ : pfvf->cpt1_lfs--;
		num_lfs = pfvf->cpt1_lfs;
		अवरोध;
	पूर्ण

	reg = is_pf ? block->pf_lfcnt_reg : block->vf_lfcnt_reg;
	rvu_ग_लिखो64(rvu, BLKADDR_RVUM, reg | (devnum << 16), num_lfs);
पूर्ण

अंतरभूत पूर्णांक rvu_get_pf(u16 pcअगरunc)
अणु
	वापस (pcअगरunc >> RVU_PFVF_PF_SHIFT) & RVU_PFVF_PF_MASK;
पूर्ण

व्योम rvu_get_pf_numvfs(काष्ठा rvu *rvu, पूर्णांक pf, पूर्णांक *numvfs, पूर्णांक *hwvf)
अणु
	u64 cfg;

	/* Get numVFs attached to this PF and first HWVF */
	cfg = rvu_पढ़ो64(rvu, BLKADDR_RVUM, RVU_PRIV_PFX_CFG(pf));
	*numvfs = (cfg >> 12) & 0xFF;
	*hwvf = cfg & 0xFFF;
पूर्ण

अटल पूर्णांक rvu_get_hwvf(काष्ठा rvu *rvu, पूर्णांक pcअगरunc)
अणु
	पूर्णांक pf, func;
	u64 cfg;

	pf = rvu_get_pf(pcअगरunc);
	func = pcअगरunc & RVU_PFVF_FUNC_MASK;

	/* Get first HWVF attached to this PF */
	cfg = rvu_पढ़ो64(rvu, BLKADDR_RVUM, RVU_PRIV_PFX_CFG(pf));

	वापस ((cfg & 0xFFF) + func - 1);
पूर्ण

काष्ठा rvu_pfvf *rvu_get_pfvf(काष्ठा rvu *rvu, पूर्णांक pcअगरunc)
अणु
	/* Check अगर it is a PF or VF */
	अगर (pcअगरunc & RVU_PFVF_FUNC_MASK)
		वापस &rvu->hwvf[rvu_get_hwvf(rvu, pcअगरunc)];
	अन्यथा
		वापस &rvu->pf[rvu_get_pf(pcअगरunc)];
पूर्ण

अटल bool is_pf_func_valid(काष्ठा rvu *rvu, u16 pcअगरunc)
अणु
	पूर्णांक pf, vf, nvfs;
	u64 cfg;

	pf = rvu_get_pf(pcअगरunc);
	अगर (pf >= rvu->hw->total_pfs)
		वापस false;

	अगर (!(pcअगरunc & RVU_PFVF_FUNC_MASK))
		वापस true;

	/* Check अगर VF is within number of VFs attached to this PF */
	vf = (pcअगरunc & RVU_PFVF_FUNC_MASK) - 1;
	cfg = rvu_पढ़ो64(rvu, BLKADDR_RVUM, RVU_PRIV_PFX_CFG(pf));
	nvfs = (cfg >> 12) & 0xFF;
	अगर (vf >= nvfs)
		वापस false;

	वापस true;
पूर्ण

bool is_block_implemented(काष्ठा rvu_hwinfo *hw, पूर्णांक blkaddr)
अणु
	काष्ठा rvu_block *block;

	अगर (blkaddr < BLKADDR_RVUM || blkaddr >= BLK_COUNT)
		वापस false;

	block = &hw->block[blkaddr];
	वापस block->implemented;
पूर्ण

अटल व्योम rvu_check_block_implemented(काष्ठा rvu *rvu)
अणु
	काष्ठा rvu_hwinfo *hw = rvu->hw;
	काष्ठा rvu_block *block;
	पूर्णांक blkid;
	u64 cfg;

	/* For each block check अगर 'implemented' bit is set */
	क्रम (blkid = 0; blkid < BLK_COUNT; blkid++) अणु
		block = &hw->block[blkid];
		cfg = rvupf_पढ़ो64(rvu, RVU_PF_BLOCK_ADDRX_DISC(blkid));
		अगर (cfg & BIT_ULL(11))
			block->implemented = true;
	पूर्ण
पूर्ण

अटल व्योम rvu_setup_rvum_blk_revid(काष्ठा rvu *rvu)
अणु
	rvu_ग_लिखो64(rvu, BLKADDR_RVUM,
		    RVU_PRIV_BLOCK_TYPEX_REV(BLKTYPE_RVUM),
		    RVU_BLK_RVUM_REVID);
पूर्ण

अटल व्योम rvu_clear_rvum_blk_revid(काष्ठा rvu *rvu)
अणु
	rvu_ग_लिखो64(rvu, BLKADDR_RVUM,
		    RVU_PRIV_BLOCK_TYPEX_REV(BLKTYPE_RVUM), 0x00);
पूर्ण

पूर्णांक rvu_lf_reset(काष्ठा rvu *rvu, काष्ठा rvu_block *block, पूर्णांक lf)
अणु
	पूर्णांक err;

	अगर (!block->implemented)
		वापस 0;

	rvu_ग_लिखो64(rvu, block->addr, block->lfreset_reg, lf | BIT_ULL(12));
	err = rvu_poll_reg(rvu, block->addr, block->lfreset_reg, BIT_ULL(12),
			   true);
	वापस err;
पूर्ण

अटल व्योम rvu_block_reset(काष्ठा rvu *rvu, पूर्णांक blkaddr, u64 rst_reg)
अणु
	काष्ठा rvu_block *block = &rvu->hw->block[blkaddr];

	अगर (!block->implemented)
		वापस;

	rvu_ग_लिखो64(rvu, blkaddr, rst_reg, BIT_ULL(0));
	rvu_poll_reg(rvu, blkaddr, rst_reg, BIT_ULL(63), true);
पूर्ण

अटल व्योम rvu_reset_all_blocks(काष्ठा rvu *rvu)
अणु
	/* Do a HW reset of all RVU blocks */
	rvu_block_reset(rvu, BLKADDR_NPA, NPA_AF_BLK_RST);
	rvu_block_reset(rvu, BLKADDR_NIX0, NIX_AF_BLK_RST);
	rvu_block_reset(rvu, BLKADDR_NIX1, NIX_AF_BLK_RST);
	rvu_block_reset(rvu, BLKADDR_NPC, NPC_AF_BLK_RST);
	rvu_block_reset(rvu, BLKADDR_SSO, SSO_AF_BLK_RST);
	rvu_block_reset(rvu, BLKADDR_TIM, TIM_AF_BLK_RST);
	rvu_block_reset(rvu, BLKADDR_CPT0, CPT_AF_BLK_RST);
	rvu_block_reset(rvu, BLKADDR_CPT1, CPT_AF_BLK_RST);
	rvu_block_reset(rvu, BLKADDR_NDC_NIX0_RX, NDC_AF_BLK_RST);
	rvu_block_reset(rvu, BLKADDR_NDC_NIX0_TX, NDC_AF_BLK_RST);
	rvu_block_reset(rvu, BLKADDR_NDC_NIX1_RX, NDC_AF_BLK_RST);
	rvu_block_reset(rvu, BLKADDR_NDC_NIX1_TX, NDC_AF_BLK_RST);
	rvu_block_reset(rvu, BLKADDR_NDC_NPA0, NDC_AF_BLK_RST);
पूर्ण

अटल व्योम rvu_scan_block(काष्ठा rvu *rvu, काष्ठा rvu_block *block)
अणु
	काष्ठा rvu_pfvf *pfvf;
	u64 cfg;
	पूर्णांक lf;

	क्रम (lf = 0; lf < block->lf.max; lf++) अणु
		cfg = rvu_पढ़ो64(rvu, block->addr,
				 block->lfcfg_reg | (lf << block->lfshअगरt));
		अगर (!(cfg & BIT_ULL(63)))
			जारी;

		/* Set this resource as being used */
		__set_bit(lf, block->lf.bmap);

		/* Get, to whom this LF is attached */
		pfvf = rvu_get_pfvf(rvu, (cfg >> 8) & 0xFFFF);
		rvu_update_rsrc_map(rvu, pfvf, block,
				    (cfg >> 8) & 0xFFFF, lf, true);

		/* Set start MSIX vector क्रम this LF within this PF/VF */
		rvu_set_msix_offset(rvu, pfvf, block, lf);
	पूर्ण
पूर्ण

अटल व्योम rvu_check_min_msix_vec(काष्ठा rvu *rvu, पूर्णांक nvecs, पूर्णांक pf, पूर्णांक vf)
अणु
	पूर्णांक min_vecs;

	अगर (!vf)
		जाओ check_pf;

	अगर (!nvecs) अणु
		dev_warn(rvu->dev,
			 "PF%d:VF%d is configured with zero msix vectors, %d\n",
			 pf, vf - 1, nvecs);
	पूर्ण
	वापस;

check_pf:
	अगर (pf == 0)
		min_vecs = RVU_AF_INT_VEC_CNT + RVU_PF_INT_VEC_CNT;
	अन्यथा
		min_vecs = RVU_PF_INT_VEC_CNT;

	अगर (!(nvecs < min_vecs))
		वापस;
	dev_warn(rvu->dev,
		 "PF%d is configured with too few vectors, %d, min is %d\n",
		 pf, nvecs, min_vecs);
पूर्ण

अटल पूर्णांक rvu_setup_msix_resources(काष्ठा rvu *rvu)
अणु
	काष्ठा rvu_hwinfo *hw = rvu->hw;
	पूर्णांक pf, vf, numvfs, hwvf, err;
	पूर्णांक nvecs, offset, max_msix;
	काष्ठा rvu_pfvf *pfvf;
	u64 cfg, phy_addr;
	dma_addr_t iova;

	क्रम (pf = 0; pf < hw->total_pfs; pf++) अणु
		cfg = rvu_पढ़ो64(rvu, BLKADDR_RVUM, RVU_PRIV_PFX_CFG(pf));
		/* If PF is not enabled, nothing to करो */
		अगर (!((cfg >> 20) & 0x01))
			जारी;

		rvu_get_pf_numvfs(rvu, pf, &numvfs, &hwvf);

		pfvf = &rvu->pf[pf];
		/* Get num of MSIX vectors attached to this PF */
		cfg = rvu_पढ़ो64(rvu, BLKADDR_RVUM, RVU_PRIV_PFX_MSIX_CFG(pf));
		pfvf->msix.max = ((cfg >> 32) & 0xFFF) + 1;
		rvu_check_min_msix_vec(rvu, pfvf->msix.max, pf, 0);

		/* Alloc msix biपंचांगap क्रम this PF */
		err = rvu_alloc_biपंचांगap(&pfvf->msix);
		अगर (err)
			वापस err;

		/* Allocate memory क्रम MSIX vector to RVU block LF mapping */
		pfvf->msix_lfmap = devm_kसुस्मृति(rvu->dev, pfvf->msix.max,
						माप(u16), GFP_KERNEL);
		अगर (!pfvf->msix_lfmap)
			वापस -ENOMEM;

		/* For PF0 (AF) firmware will set msix vector offsets क्रम
		 * AF, block AF and PF0_INT vectors, so jump to VFs.
		 */
		अगर (!pf)
			जाओ setup_vfmsix;

		/* Set MSIX offset क्रम PF's 'RVU_PF_INT_VEC' vectors.
		 * These are allocated on driver init and never मुक्तd,
		 * so no need to set 'msix_lfmap' क्रम these.
		 */
		cfg = rvu_पढ़ो64(rvu, BLKADDR_RVUM, RVU_PRIV_PFX_INT_CFG(pf));
		nvecs = (cfg >> 12) & 0xFF;
		cfg &= ~0x7FFULL;
		offset = rvu_alloc_rsrc_contig(&pfvf->msix, nvecs);
		rvu_ग_लिखो64(rvu, BLKADDR_RVUM,
			    RVU_PRIV_PFX_INT_CFG(pf), cfg | offset);
setup_vfmsix:
		/* Alloc msix biपंचांगap क्रम VFs */
		क्रम (vf = 0; vf < numvfs; vf++) अणु
			pfvf =  &rvu->hwvf[hwvf + vf];
			/* Get num of MSIX vectors attached to this VF */
			cfg = rvu_पढ़ो64(rvu, BLKADDR_RVUM,
					 RVU_PRIV_PFX_MSIX_CFG(pf));
			pfvf->msix.max = (cfg & 0xFFF) + 1;
			rvu_check_min_msix_vec(rvu, pfvf->msix.max, pf, vf + 1);

			/* Alloc msix biपंचांगap क्रम this VF */
			err = rvu_alloc_biपंचांगap(&pfvf->msix);
			अगर (err)
				वापस err;

			pfvf->msix_lfmap =
				devm_kसुस्मृति(rvu->dev, pfvf->msix.max,
					     माप(u16), GFP_KERNEL);
			अगर (!pfvf->msix_lfmap)
				वापस -ENOMEM;

			/* Set MSIX offset क्रम HWVF's 'RVU_VF_INT_VEC' vectors.
			 * These are allocated on driver init and never मुक्तd,
			 * so no need to set 'msix_lfmap' क्रम these.
			 */
			cfg = rvu_पढ़ो64(rvu, BLKADDR_RVUM,
					 RVU_PRIV_HWVFX_INT_CFG(hwvf + vf));
			nvecs = (cfg >> 12) & 0xFF;
			cfg &= ~0x7FFULL;
			offset = rvu_alloc_rsrc_contig(&pfvf->msix, nvecs);
			rvu_ग_लिखो64(rvu, BLKADDR_RVUM,
				    RVU_PRIV_HWVFX_INT_CFG(hwvf + vf),
				    cfg | offset);
		पूर्ण
	पूर्ण

	/* HW पूर्णांकerprets RVU_AF_MSIXTR_BASE address as an IOVA, hence
	 * create an IOMMU mapping क्रम the physical address configured by
	 * firmware and reconfig RVU_AF_MSIXTR_BASE with IOVA.
	 */
	cfg = rvu_पढ़ो64(rvu, BLKADDR_RVUM, RVU_PRIV_CONST);
	max_msix = cfg & 0xFFFFF;
	अगर (rvu->fwdata && rvu->fwdata->msixtr_base)
		phy_addr = rvu->fwdata->msixtr_base;
	अन्यथा
		phy_addr = rvu_पढ़ो64(rvu, BLKADDR_RVUM, RVU_AF_MSIXTR_BASE);

	iova = dma_map_resource(rvu->dev, phy_addr,
				max_msix * PCI_MSIX_ENTRY_SIZE,
				DMA_BIसूचीECTIONAL, 0);

	अगर (dma_mapping_error(rvu->dev, iova))
		वापस -ENOMEM;

	rvu_ग_लिखो64(rvu, BLKADDR_RVUM, RVU_AF_MSIXTR_BASE, (u64)iova);
	rvu->msix_base_iova = iova;
	rvu->msixtr_base_phy = phy_addr;

	वापस 0;
पूर्ण

अटल व्योम rvu_reset_msix(काष्ठा rvu *rvu)
अणु
	/* Restore msixtr base रेजिस्टर */
	rvu_ग_लिखो64(rvu, BLKADDR_RVUM, RVU_AF_MSIXTR_BASE,
		    rvu->msixtr_base_phy);
पूर्ण

अटल व्योम rvu_मुक्त_hw_resources(काष्ठा rvu *rvu)
अणु
	काष्ठा rvu_hwinfo *hw = rvu->hw;
	काष्ठा rvu_block *block;
	काष्ठा rvu_pfvf  *pfvf;
	पूर्णांक id, max_msix;
	u64 cfg;

	rvu_npa_मुक्तmem(rvu);
	rvu_npc_मुक्तmem(rvu);
	rvu_nix_मुक्तmem(rvu);

	/* Free block LF biपंचांगaps */
	क्रम (id = 0; id < BLK_COUNT; id++) अणु
		block = &hw->block[id];
		kमुक्त(block->lf.bmap);
	पूर्ण

	/* Free MSIX biपंचांगaps */
	क्रम (id = 0; id < hw->total_pfs; id++) अणु
		pfvf = &rvu->pf[id];
		kमुक्त(pfvf->msix.bmap);
	पूर्ण

	क्रम (id = 0; id < hw->total_vfs; id++) अणु
		pfvf = &rvu->hwvf[id];
		kमुक्त(pfvf->msix.bmap);
	पूर्ण

	/* Unmap MSIX vector base IOVA mapping */
	अगर (!rvu->msix_base_iova)
		वापस;
	cfg = rvu_पढ़ो64(rvu, BLKADDR_RVUM, RVU_PRIV_CONST);
	max_msix = cfg & 0xFFFFF;
	dma_unmap_resource(rvu->dev, rvu->msix_base_iova,
			   max_msix * PCI_MSIX_ENTRY_SIZE,
			   DMA_BIसूचीECTIONAL, 0);

	rvu_reset_msix(rvu);
	mutex_destroy(&rvu->rsrc_lock);
पूर्ण

अटल व्योम rvu_setup_pfvf_macaddress(काष्ठा rvu *rvu)
अणु
	काष्ठा rvu_hwinfo *hw = rvu->hw;
	पूर्णांक pf, vf, numvfs, hwvf;
	काष्ठा rvu_pfvf *pfvf;
	u64 *mac;

	क्रम (pf = 0; pf < hw->total_pfs; pf++) अणु
		/* For PF0(AF), Assign MAC address to only VFs (LBKVFs) */
		अगर (!pf)
			जाओ lbkvf;

		अगर (!is_pf_cgxmapped(rvu, pf))
			जारी;
		/* Assign MAC address to PF */
		pfvf = &rvu->pf[pf];
		अगर (rvu->fwdata && pf < PF_MACNUM_MAX) अणु
			mac = &rvu->fwdata->pf_macs[pf];
			अगर (*mac)
				u64_to_ether_addr(*mac, pfvf->mac_addr);
			अन्यथा
				eth_अक्रमom_addr(pfvf->mac_addr);
		पूर्ण अन्यथा अणु
			eth_अक्रमom_addr(pfvf->mac_addr);
		पूर्ण
		ether_addr_copy(pfvf->शेष_mac, pfvf->mac_addr);

lbkvf:
		/* Assign MAC address to VFs*/
		rvu_get_pf_numvfs(rvu, pf, &numvfs, &hwvf);
		क्रम (vf = 0; vf < numvfs; vf++, hwvf++) अणु
			pfvf = &rvu->hwvf[hwvf];
			अगर (rvu->fwdata && hwvf < VF_MACNUM_MAX) अणु
				mac = &rvu->fwdata->vf_macs[hwvf];
				अगर (*mac)
					u64_to_ether_addr(*mac, pfvf->mac_addr);
				अन्यथा
					eth_अक्रमom_addr(pfvf->mac_addr);
			पूर्ण अन्यथा अणु
				eth_अक्रमom_addr(pfvf->mac_addr);
			पूर्ण
			ether_addr_copy(pfvf->शेष_mac, pfvf->mac_addr);
		पूर्ण
	पूर्ण
पूर्ण

अटल पूर्णांक rvu_fwdata_init(काष्ठा rvu *rvu)
अणु
	u64 fwdbase;
	पूर्णांक err;

	/* Get firmware data base address */
	err = cgx_get_fwdata_base(&fwdbase);
	अगर (err)
		जाओ fail;
	rvu->fwdata = ioremap_wc(fwdbase, माप(काष्ठा rvu_fwdata));
	अगर (!rvu->fwdata)
		जाओ fail;
	अगर (!is_rvu_fwdata_valid(rvu)) अणु
		dev_err(rvu->dev,
			"Mismatch in 'fwdata' struct btw kernel and firmware\n");
		iounmap(rvu->fwdata);
		rvu->fwdata = शून्य;
		वापस -EINVAL;
	पूर्ण
	वापस 0;
fail:
	dev_info(rvu->dev, "Unable to fetch 'fwdata' from firmware\n");
	वापस -EIO;
पूर्ण

अटल व्योम rvu_fwdata_निकास(काष्ठा rvu *rvu)
अणु
	अगर (rvu->fwdata)
		iounmap(rvu->fwdata);
पूर्ण

अटल पूर्णांक rvu_setup_nix_hw_resource(काष्ठा rvu *rvu, पूर्णांक blkaddr)
अणु
	काष्ठा rvu_hwinfo *hw = rvu->hw;
	काष्ठा rvu_block *block;
	पूर्णांक blkid;
	u64 cfg;

	/* Init NIX LF's biपंचांगap */
	block = &hw->block[blkaddr];
	अगर (!block->implemented)
		वापस 0;
	blkid = (blkaddr == BLKADDR_NIX0) ? 0 : 1;
	cfg = rvu_पढ़ो64(rvu, blkaddr, NIX_AF_CONST2);
	block->lf.max = cfg & 0xFFF;
	block->addr = blkaddr;
	block->type = BLKTYPE_NIX;
	block->lfshअगरt = 8;
	block->lookup_reg = NIX_AF_RVU_LF_CFG_DEBUG;
	block->pf_lfcnt_reg = RVU_PRIV_PFX_NIXX_CFG(blkid);
	block->vf_lfcnt_reg = RVU_PRIV_HWVFX_NIXX_CFG(blkid);
	block->lfcfg_reg = NIX_PRIV_LFX_CFG;
	block->msixcfg_reg = NIX_PRIV_LFX_INT_CFG;
	block->lfreset_reg = NIX_AF_LF_RST;
	प्र_लिखो(block->name, "NIX%d", blkid);
	rvu->nix_blkaddr[blkid] = blkaddr;
	वापस rvu_alloc_biपंचांगap(&block->lf);
पूर्ण

अटल पूर्णांक rvu_setup_cpt_hw_resource(काष्ठा rvu *rvu, पूर्णांक blkaddr)
अणु
	काष्ठा rvu_hwinfo *hw = rvu->hw;
	काष्ठा rvu_block *block;
	पूर्णांक blkid;
	u64 cfg;

	/* Init CPT LF's biपंचांगap */
	block = &hw->block[blkaddr];
	अगर (!block->implemented)
		वापस 0;
	blkid = (blkaddr == BLKADDR_CPT0) ? 0 : 1;
	cfg = rvu_पढ़ो64(rvu, blkaddr, CPT_AF_CONSTANTS0);
	block->lf.max = cfg & 0xFF;
	block->addr = blkaddr;
	block->type = BLKTYPE_CPT;
	block->multislot = true;
	block->lfshअगरt = 3;
	block->lookup_reg = CPT_AF_RVU_LF_CFG_DEBUG;
	block->pf_lfcnt_reg = RVU_PRIV_PFX_CPTX_CFG(blkid);
	block->vf_lfcnt_reg = RVU_PRIV_HWVFX_CPTX_CFG(blkid);
	block->lfcfg_reg = CPT_PRIV_LFX_CFG;
	block->msixcfg_reg = CPT_PRIV_LFX_INT_CFG;
	block->lfreset_reg = CPT_AF_LF_RST;
	प्र_लिखो(block->name, "CPT%d", blkid);
	वापस rvu_alloc_biपंचांगap(&block->lf);
पूर्ण

अटल व्योम rvu_get_lbk_bufsize(काष्ठा rvu *rvu)
अणु
	काष्ठा pci_dev *pdev = शून्य;
	व्योम __iomem *base;
	u64 lbk_स्थिर;

	pdev = pci_get_device(PCI_VENDOR_ID_CAVIUM,
			      PCI_DEVID_OCTEONTX2_LBK, pdev);
	अगर (!pdev)
		वापस;

	base = pci_ioremap_bar(pdev, 0);
	अगर (!base)
		जाओ err_put;

	lbk_स्थिर = पढ़ोq(base + LBK_CONST);

	/* cache fअगरo size */
	rvu->hw->lbk_bufsize = FIELD_GET(LBK_CONST_BUF_SIZE, lbk_स्थिर);

	iounmap(base);
err_put:
	pci_dev_put(pdev);
पूर्ण

अटल पूर्णांक rvu_setup_hw_resources(काष्ठा rvu *rvu)
अणु
	काष्ठा rvu_hwinfo *hw = rvu->hw;
	काष्ठा rvu_block *block;
	पूर्णांक blkid, err;
	u64 cfg;

	/* Get HW supported max RVU PF & VF count */
	cfg = rvu_पढ़ो64(rvu, BLKADDR_RVUM, RVU_PRIV_CONST);
	hw->total_pfs = (cfg >> 32) & 0xFF;
	hw->total_vfs = (cfg >> 20) & 0xFFF;
	hw->max_vfs_per_pf = (cfg >> 40) & 0xFF;

	/* Init NPA LF's biपंचांगap */
	block = &hw->block[BLKADDR_NPA];
	अगर (!block->implemented)
		जाओ nix;
	cfg = rvu_पढ़ो64(rvu, BLKADDR_NPA, NPA_AF_CONST);
	block->lf.max = (cfg >> 16) & 0xFFF;
	block->addr = BLKADDR_NPA;
	block->type = BLKTYPE_NPA;
	block->lfshअगरt = 8;
	block->lookup_reg = NPA_AF_RVU_LF_CFG_DEBUG;
	block->pf_lfcnt_reg = RVU_PRIV_PFX_NPA_CFG;
	block->vf_lfcnt_reg = RVU_PRIV_HWVFX_NPA_CFG;
	block->lfcfg_reg = NPA_PRIV_LFX_CFG;
	block->msixcfg_reg = NPA_PRIV_LFX_INT_CFG;
	block->lfreset_reg = NPA_AF_LF_RST;
	प्र_लिखो(block->name, "NPA");
	err = rvu_alloc_biपंचांगap(&block->lf);
	अगर (err)
		वापस err;

nix:
	err = rvu_setup_nix_hw_resource(rvu, BLKADDR_NIX0);
	अगर (err)
		वापस err;
	err = rvu_setup_nix_hw_resource(rvu, BLKADDR_NIX1);
	अगर (err)
		वापस err;

	/* Init SSO group's biपंचांगap */
	block = &hw->block[BLKADDR_SSO];
	अगर (!block->implemented)
		जाओ ssow;
	cfg = rvu_पढ़ो64(rvu, BLKADDR_SSO, SSO_AF_CONST);
	block->lf.max = cfg & 0xFFFF;
	block->addr = BLKADDR_SSO;
	block->type = BLKTYPE_SSO;
	block->multislot = true;
	block->lfshअगरt = 3;
	block->lookup_reg = SSO_AF_RVU_LF_CFG_DEBUG;
	block->pf_lfcnt_reg = RVU_PRIV_PFX_SSO_CFG;
	block->vf_lfcnt_reg = RVU_PRIV_HWVFX_SSO_CFG;
	block->lfcfg_reg = SSO_PRIV_LFX_HWGRP_CFG;
	block->msixcfg_reg = SSO_PRIV_LFX_HWGRP_INT_CFG;
	block->lfreset_reg = SSO_AF_LF_HWGRP_RST;
	प्र_लिखो(block->name, "SSO GROUP");
	err = rvu_alloc_biपंचांगap(&block->lf);
	अगर (err)
		वापस err;

ssow:
	/* Init SSO workslot's biपंचांगap */
	block = &hw->block[BLKADDR_SSOW];
	अगर (!block->implemented)
		जाओ tim;
	block->lf.max = (cfg >> 56) & 0xFF;
	block->addr = BLKADDR_SSOW;
	block->type = BLKTYPE_SSOW;
	block->multislot = true;
	block->lfshअगरt = 3;
	block->lookup_reg = SSOW_AF_RVU_LF_HWS_CFG_DEBUG;
	block->pf_lfcnt_reg = RVU_PRIV_PFX_SSOW_CFG;
	block->vf_lfcnt_reg = RVU_PRIV_HWVFX_SSOW_CFG;
	block->lfcfg_reg = SSOW_PRIV_LFX_HWS_CFG;
	block->msixcfg_reg = SSOW_PRIV_LFX_HWS_INT_CFG;
	block->lfreset_reg = SSOW_AF_LF_HWS_RST;
	प्र_लिखो(block->name, "SSOWS");
	err = rvu_alloc_biपंचांगap(&block->lf);
	अगर (err)
		वापस err;

tim:
	/* Init TIM LF's biपंचांगap */
	block = &hw->block[BLKADDR_TIM];
	अगर (!block->implemented)
		जाओ cpt;
	cfg = rvu_पढ़ो64(rvu, BLKADDR_TIM, TIM_AF_CONST);
	block->lf.max = cfg & 0xFFFF;
	block->addr = BLKADDR_TIM;
	block->type = BLKTYPE_TIM;
	block->multislot = true;
	block->lfshअगरt = 3;
	block->lookup_reg = TIM_AF_RVU_LF_CFG_DEBUG;
	block->pf_lfcnt_reg = RVU_PRIV_PFX_TIM_CFG;
	block->vf_lfcnt_reg = RVU_PRIV_HWVFX_TIM_CFG;
	block->lfcfg_reg = TIM_PRIV_LFX_CFG;
	block->msixcfg_reg = TIM_PRIV_LFX_INT_CFG;
	block->lfreset_reg = TIM_AF_LF_RST;
	प्र_लिखो(block->name, "TIM");
	err = rvu_alloc_biपंचांगap(&block->lf);
	अगर (err)
		वापस err;

cpt:
	err = rvu_setup_cpt_hw_resource(rvu, BLKADDR_CPT0);
	अगर (err)
		वापस err;
	err = rvu_setup_cpt_hw_resource(rvu, BLKADDR_CPT1);
	अगर (err)
		वापस err;

	/* Allocate memory क्रम PFVF data */
	rvu->pf = devm_kसुस्मृति(rvu->dev, hw->total_pfs,
			       माप(काष्ठा rvu_pfvf), GFP_KERNEL);
	अगर (!rvu->pf)
		वापस -ENOMEM;

	rvu->hwvf = devm_kसुस्मृति(rvu->dev, hw->total_vfs,
				 माप(काष्ठा rvu_pfvf), GFP_KERNEL);
	अगर (!rvu->hwvf)
		वापस -ENOMEM;

	mutex_init(&rvu->rsrc_lock);

	rvu_fwdata_init(rvu);

	err = rvu_setup_msix_resources(rvu);
	अगर (err)
		वापस err;

	क्रम (blkid = 0; blkid < BLK_COUNT; blkid++) अणु
		block = &hw->block[blkid];
		अगर (!block->lf.bmap)
			जारी;

		/* Allocate memory क्रम block LF/slot to pcअगरunc mapping info */
		block->fn_map = devm_kसुस्मृति(rvu->dev, block->lf.max,
					     माप(u16), GFP_KERNEL);
		अगर (!block->fn_map) अणु
			err = -ENOMEM;
			जाओ msix_err;
		पूर्ण

		/* Scan all blocks to check अगर low level firmware has
		 * alपढ़ोy provisioned any of the resources to a PF/VF.
		 */
		rvu_scan_block(rvu, block);
	पूर्ण

	err = rvu_set_channels_base(rvu);
	अगर (err)
		जाओ msix_err;

	err = rvu_npc_init(rvu);
	अगर (err)
		जाओ npc_err;

	err = rvu_cgx_init(rvu);
	अगर (err)
		जाओ cgx_err;

	/* Assign MACs क्रम CGX mapped functions */
	rvu_setup_pfvf_macaddress(rvu);

	err = rvu_npa_init(rvu);
	अगर (err)
		जाओ npa_err;

	rvu_get_lbk_bufsize(rvu);

	err = rvu_nix_init(rvu);
	अगर (err)
		जाओ nix_err;

	rvu_program_channels(rvu);

	वापस 0;

nix_err:
	rvu_nix_मुक्तmem(rvu);
npa_err:
	rvu_npa_मुक्तmem(rvu);
cgx_err:
	rvu_cgx_निकास(rvu);
npc_err:
	rvu_npc_मुक्तmem(rvu);
	rvu_fwdata_निकास(rvu);
msix_err:
	rvu_reset_msix(rvu);
	वापस err;
पूर्ण

/* NPA and NIX admin queue APIs */
व्योम rvu_aq_मुक्त(काष्ठा rvu *rvu, काष्ठा admin_queue *aq)
अणु
	अगर (!aq)
		वापस;

	qmem_मुक्त(rvu->dev, aq->inst);
	qmem_मुक्त(rvu->dev, aq->res);
	devm_kमुक्त(rvu->dev, aq);
पूर्ण

पूर्णांक rvu_aq_alloc(काष्ठा rvu *rvu, काष्ठा admin_queue **ad_queue,
		 पूर्णांक qsize, पूर्णांक inst_size, पूर्णांक res_size)
अणु
	काष्ठा admin_queue *aq;
	पूर्णांक err;

	*ad_queue = devm_kzalloc(rvu->dev, माप(*aq), GFP_KERNEL);
	अगर (!*ad_queue)
		वापस -ENOMEM;
	aq = *ad_queue;

	/* Alloc memory क्रम inकाष्ठाions i.e AQ */
	err = qmem_alloc(rvu->dev, &aq->inst, qsize, inst_size);
	अगर (err) अणु
		devm_kमुक्त(rvu->dev, aq);
		वापस err;
	पूर्ण

	/* Alloc memory क्रम results */
	err = qmem_alloc(rvu->dev, &aq->res, qsize, res_size);
	अगर (err) अणु
		rvu_aq_मुक्त(rvu, aq);
		वापस err;
	पूर्ण

	spin_lock_init(&aq->lock);
	वापस 0;
पूर्ण

पूर्णांक rvu_mbox_handler_पढ़ोy(काष्ठा rvu *rvu, काष्ठा msg_req *req,
			   काष्ठा पढ़ोy_msg_rsp *rsp)
अणु
	अगर (rvu->fwdata) अणु
		rsp->rclk_freq = rvu->fwdata->rclk;
		rsp->sclk_freq = rvu->fwdata->sclk;
	पूर्ण
	वापस 0;
पूर्ण

/* Get current count of a RVU block's LF/slots
 * provisioned to a given RVU func.
 */
u16 rvu_get_rsrc_mapcount(काष्ठा rvu_pfvf *pfvf, पूर्णांक blkaddr)
अणु
	चयन (blkaddr) अणु
	हाल BLKADDR_NPA:
		वापस pfvf->npalf ? 1 : 0;
	हाल BLKADDR_NIX0:
	हाल BLKADDR_NIX1:
		वापस pfvf->nixlf ? 1 : 0;
	हाल BLKADDR_SSO:
		वापस pfvf->sso;
	हाल BLKADDR_SSOW:
		वापस pfvf->ssow;
	हाल BLKADDR_TIM:
		वापस pfvf->timlfs;
	हाल BLKADDR_CPT0:
		वापस pfvf->cptlfs;
	हाल BLKADDR_CPT1:
		वापस pfvf->cpt1_lfs;
	पूर्ण
	वापस 0;
पूर्ण

/* Return true अगर LFs of block type are attached to pcअगरunc */
अटल bool is_blktype_attached(काष्ठा rvu_pfvf *pfvf, पूर्णांक blktype)
अणु
	चयन (blktype) अणु
	हाल BLKTYPE_NPA:
		वापस pfvf->npalf ? 1 : 0;
	हाल BLKTYPE_NIX:
		वापस pfvf->nixlf ? 1 : 0;
	हाल BLKTYPE_SSO:
		वापस !!pfvf->sso;
	हाल BLKTYPE_SSOW:
		वापस !!pfvf->ssow;
	हाल BLKTYPE_TIM:
		वापस !!pfvf->timlfs;
	हाल BLKTYPE_CPT:
		वापस pfvf->cptlfs || pfvf->cpt1_lfs;
	पूर्ण

	वापस false;
पूर्ण

bool is_pffunc_map_valid(काष्ठा rvu *rvu, u16 pcअगरunc, पूर्णांक blktype)
अणु
	काष्ठा rvu_pfvf *pfvf;

	अगर (!is_pf_func_valid(rvu, pcअगरunc))
		वापस false;

	pfvf = rvu_get_pfvf(rvu, pcअगरunc);

	/* Check अगर this PFFUNC has a LF of type blktype attached */
	अगर (!is_blktype_attached(pfvf, blktype))
		वापस false;

	वापस true;
पूर्ण

अटल पूर्णांक rvu_lookup_rsrc(काष्ठा rvu *rvu, काष्ठा rvu_block *block,
			   पूर्णांक pcअगरunc, पूर्णांक slot)
अणु
	u64 val;

	val = ((u64)pcअगरunc << 24) | (slot << 16) | (1ULL << 13);
	rvu_ग_लिखो64(rvu, block->addr, block->lookup_reg, val);
	/* Wait क्रम the lookup to finish */
	/* TODO: put some समयout here */
	जबतक (rvu_पढ़ो64(rvu, block->addr, block->lookup_reg) & (1ULL << 13))
		;

	val = rvu_पढ़ो64(rvu, block->addr, block->lookup_reg);

	/* Check LF valid bit */
	अगर (!(val & (1ULL << 12)))
		वापस -1;

	वापस (val & 0xFFF);
पूर्ण

अटल व्योम rvu_detach_block(काष्ठा rvu *rvu, पूर्णांक pcअगरunc, पूर्णांक blktype)
अणु
	काष्ठा rvu_pfvf *pfvf = rvu_get_pfvf(rvu, pcअगरunc);
	काष्ठा rvu_hwinfo *hw = rvu->hw;
	काष्ठा rvu_block *block;
	पूर्णांक slot, lf, num_lfs;
	पूर्णांक blkaddr;

	blkaddr = rvu_get_blkaddr(rvu, blktype, pcअगरunc);
	अगर (blkaddr < 0)
		वापस;

	अगर (blktype == BLKTYPE_NIX)
		rvu_nix_reset_mac(pfvf, pcअगरunc);

	block = &hw->block[blkaddr];

	num_lfs = rvu_get_rsrc_mapcount(pfvf, block->addr);
	अगर (!num_lfs)
		वापस;

	क्रम (slot = 0; slot < num_lfs; slot++) अणु
		lf = rvu_lookup_rsrc(rvu, block, pcअगरunc, slot);
		अगर (lf < 0) /* This should never happen */
			जारी;

		/* Disable the LF */
		rvu_ग_लिखो64(rvu, blkaddr, block->lfcfg_reg |
			    (lf << block->lfshअगरt), 0x00ULL);

		/* Update SW मुख्यtained mapping info as well */
		rvu_update_rsrc_map(rvu, pfvf, block,
				    pcअगरunc, lf, false);

		/* Free the resource */
		rvu_मुक्त_rsrc(&block->lf, lf);

		/* Clear MSIX vector offset क्रम this LF */
		rvu_clear_msix_offset(rvu, pfvf, block, lf);
	पूर्ण
पूर्ण

अटल पूर्णांक rvu_detach_rsrcs(काष्ठा rvu *rvu, काष्ठा rsrc_detach *detach,
			    u16 pcअगरunc)
अणु
	काष्ठा rvu_hwinfo *hw = rvu->hw;
	bool detach_all = true;
	काष्ठा rvu_block *block;
	पूर्णांक blkid;

	mutex_lock(&rvu->rsrc_lock);

	/* Check क्रम partial resource detach */
	अगर (detach && detach->partial)
		detach_all = false;

	/* Check क्रम RVU block's LFs attached to this func,
	 * अगर so, detach them.
	 */
	क्रम (blkid = 0; blkid < BLK_COUNT; blkid++) अणु
		block = &hw->block[blkid];
		अगर (!block->lf.bmap)
			जारी;
		अगर (!detach_all && detach) अणु
			अगर (blkid == BLKADDR_NPA && !detach->npalf)
				जारी;
			अन्यथा अगर ((blkid == BLKADDR_NIX0) && !detach->nixlf)
				जारी;
			अन्यथा अगर ((blkid == BLKADDR_NIX1) && !detach->nixlf)
				जारी;
			अन्यथा अगर ((blkid == BLKADDR_SSO) && !detach->sso)
				जारी;
			अन्यथा अगर ((blkid == BLKADDR_SSOW) && !detach->ssow)
				जारी;
			अन्यथा अगर ((blkid == BLKADDR_TIM) && !detach->timlfs)
				जारी;
			अन्यथा अगर ((blkid == BLKADDR_CPT0) && !detach->cptlfs)
				जारी;
			अन्यथा अगर ((blkid == BLKADDR_CPT1) && !detach->cptlfs)
				जारी;
		पूर्ण
		rvu_detach_block(rvu, pcअगरunc, block->type);
	पूर्ण

	mutex_unlock(&rvu->rsrc_lock);
	वापस 0;
पूर्ण

पूर्णांक rvu_mbox_handler_detach_resources(काष्ठा rvu *rvu,
				      काष्ठा rsrc_detach *detach,
				      काष्ठा msg_rsp *rsp)
अणु
	वापस rvu_detach_rsrcs(rvu, detach, detach->hdr.pcअगरunc);
पूर्ण

अटल पूर्णांक rvu_get_nix_blkaddr(काष्ठा rvu *rvu, u16 pcअगरunc)
अणु
	काष्ठा rvu_pfvf *pfvf = rvu_get_pfvf(rvu, pcअगरunc);
	पूर्णांक blkaddr = BLKADDR_NIX0, vf;
	काष्ठा rvu_pfvf *pf;

	/* All CGX mapped PFs are set with asचिन्हित NIX block during init */
	अगर (is_pf_cgxmapped(rvu, rvu_get_pf(pcअगरunc))) अणु
		pf = rvu_get_pfvf(rvu, pcअगरunc & ~RVU_PFVF_FUNC_MASK);
		blkaddr = pf->nix_blkaddr;
	पूर्ण अन्यथा अगर (is_afvf(pcअगरunc)) अणु
		vf = pcअगरunc - 1;
		/* Assign NIX based on VF number. All even numbered VFs get
		 * NIX0 and odd numbered माला_लो NIX1
		 */
		blkaddr = (vf & 1) ? BLKADDR_NIX1 : BLKADDR_NIX0;
		/* NIX1 is not present on all silicons */
		अगर (!is_block_implemented(rvu->hw, BLKADDR_NIX1))
			blkaddr = BLKADDR_NIX0;
	पूर्ण

	चयन (blkaddr) अणु
	हाल BLKADDR_NIX1:
		pfvf->nix_blkaddr = BLKADDR_NIX1;
		pfvf->nix_rx_पूर्णांकf = NIX_INTFX_RX(1);
		pfvf->nix_tx_पूर्णांकf = NIX_INTFX_TX(1);
		अवरोध;
	हाल BLKADDR_NIX0:
	शेष:
		pfvf->nix_blkaddr = BLKADDR_NIX0;
		pfvf->nix_rx_पूर्णांकf = NIX_INTFX_RX(0);
		pfvf->nix_tx_पूर्णांकf = NIX_INTFX_TX(0);
		अवरोध;
	पूर्ण

	वापस pfvf->nix_blkaddr;
पूर्ण

अटल पूर्णांक rvu_get_attach_blkaddr(काष्ठा rvu *rvu, पूर्णांक blktype,
				  u16 pcअगरunc, काष्ठा rsrc_attach *attach)
अणु
	पूर्णांक blkaddr;

	चयन (blktype) अणु
	हाल BLKTYPE_NIX:
		blkaddr = rvu_get_nix_blkaddr(rvu, pcअगरunc);
		अवरोध;
	हाल BLKTYPE_CPT:
		अगर (attach->hdr.ver < RVU_MULTI_BLK_VER)
			वापस rvu_get_blkaddr(rvu, blktype, 0);
		blkaddr = attach->cpt_blkaddr ? attach->cpt_blkaddr :
			  BLKADDR_CPT0;
		अगर (blkaddr != BLKADDR_CPT0 && blkaddr != BLKADDR_CPT1)
			वापस -ENODEV;
		अवरोध;
	शेष:
		वापस rvu_get_blkaddr(rvu, blktype, 0);
	पूर्ण

	अगर (is_block_implemented(rvu->hw, blkaddr))
		वापस blkaddr;

	वापस -ENODEV;
पूर्ण

अटल व्योम rvu_attach_block(काष्ठा rvu *rvu, पूर्णांक pcअगरunc, पूर्णांक blktype,
			     पूर्णांक num_lfs, काष्ठा rsrc_attach *attach)
अणु
	काष्ठा rvu_pfvf *pfvf = rvu_get_pfvf(rvu, pcअगरunc);
	काष्ठा rvu_hwinfo *hw = rvu->hw;
	काष्ठा rvu_block *block;
	पूर्णांक slot, lf;
	पूर्णांक blkaddr;
	u64 cfg;

	अगर (!num_lfs)
		वापस;

	blkaddr = rvu_get_attach_blkaddr(rvu, blktype, pcअगरunc, attach);
	अगर (blkaddr < 0)
		वापस;

	block = &hw->block[blkaddr];
	अगर (!block->lf.bmap)
		वापस;

	क्रम (slot = 0; slot < num_lfs; slot++) अणु
		/* Allocate the resource */
		lf = rvu_alloc_rsrc(&block->lf);
		अगर (lf < 0)
			वापस;

		cfg = (1ULL << 63) | (pcअगरunc << 8) | slot;
		rvu_ग_लिखो64(rvu, blkaddr, block->lfcfg_reg |
			    (lf << block->lfshअगरt), cfg);
		rvu_update_rsrc_map(rvu, pfvf, block,
				    pcअगरunc, lf, true);

		/* Set start MSIX vector क्रम this LF within this PF/VF */
		rvu_set_msix_offset(rvu, pfvf, block, lf);
	पूर्ण
पूर्ण

अटल पूर्णांक rvu_check_rsrc_availability(काष्ठा rvu *rvu,
				       काष्ठा rsrc_attach *req, u16 pcअगरunc)
अणु
	काष्ठा rvu_pfvf *pfvf = rvu_get_pfvf(rvu, pcअगरunc);
	पूर्णांक मुक्त_lfs, mappedlfs, blkaddr;
	काष्ठा rvu_hwinfo *hw = rvu->hw;
	काष्ठा rvu_block *block;

	/* Only one NPA LF can be attached */
	अगर (req->npalf && !is_blktype_attached(pfvf, BLKTYPE_NPA)) अणु
		block = &hw->block[BLKADDR_NPA];
		मुक्त_lfs = rvu_rsrc_मुक्त_count(&block->lf);
		अगर (!मुक्त_lfs)
			जाओ fail;
	पूर्ण अन्यथा अगर (req->npalf) अणु
		dev_err(&rvu->pdev->dev,
			"Func 0x%x: Invalid req, already has NPA\n",
			 pcअगरunc);
		वापस -EINVAL;
	पूर्ण

	/* Only one NIX LF can be attached */
	अगर (req->nixlf && !is_blktype_attached(pfvf, BLKTYPE_NIX)) अणु
		blkaddr = rvu_get_attach_blkaddr(rvu, BLKTYPE_NIX,
						 pcअगरunc, req);
		अगर (blkaddr < 0)
			वापस blkaddr;
		block = &hw->block[blkaddr];
		मुक्त_lfs = rvu_rsrc_मुक्त_count(&block->lf);
		अगर (!मुक्त_lfs)
			जाओ fail;
	पूर्ण अन्यथा अगर (req->nixlf) अणु
		dev_err(&rvu->pdev->dev,
			"Func 0x%x: Invalid req, already has NIX\n",
			pcअगरunc);
		वापस -EINVAL;
	पूर्ण

	अगर (req->sso) अणु
		block = &hw->block[BLKADDR_SSO];
		/* Is request within limits ? */
		अगर (req->sso > block->lf.max) अणु
			dev_err(&rvu->pdev->dev,
				"Func 0x%x: Invalid SSO req, %d > max %d\n",
				 pcअगरunc, req->sso, block->lf.max);
			वापस -EINVAL;
		पूर्ण
		mappedlfs = rvu_get_rsrc_mapcount(pfvf, block->addr);
		मुक्त_lfs = rvu_rsrc_मुक्त_count(&block->lf);
		/* Check अगर additional resources are available */
		अगर (req->sso > mappedlfs &&
		    ((req->sso - mappedlfs) > मुक्त_lfs))
			जाओ fail;
	पूर्ण

	अगर (req->ssow) अणु
		block = &hw->block[BLKADDR_SSOW];
		अगर (req->ssow > block->lf.max) अणु
			dev_err(&rvu->pdev->dev,
				"Func 0x%x: Invalid SSOW req, %d > max %d\n",
				 pcअगरunc, req->sso, block->lf.max);
			वापस -EINVAL;
		पूर्ण
		mappedlfs = rvu_get_rsrc_mapcount(pfvf, block->addr);
		मुक्त_lfs = rvu_rsrc_मुक्त_count(&block->lf);
		अगर (req->ssow > mappedlfs &&
		    ((req->ssow - mappedlfs) > मुक्त_lfs))
			जाओ fail;
	पूर्ण

	अगर (req->timlfs) अणु
		block = &hw->block[BLKADDR_TIM];
		अगर (req->timlfs > block->lf.max) अणु
			dev_err(&rvu->pdev->dev,
				"Func 0x%x: Invalid TIMLF req, %d > max %d\n",
				 pcअगरunc, req->timlfs, block->lf.max);
			वापस -EINVAL;
		पूर्ण
		mappedlfs = rvu_get_rsrc_mapcount(pfvf, block->addr);
		मुक्त_lfs = rvu_rsrc_मुक्त_count(&block->lf);
		अगर (req->timlfs > mappedlfs &&
		    ((req->timlfs - mappedlfs) > मुक्त_lfs))
			जाओ fail;
	पूर्ण

	अगर (req->cptlfs) अणु
		blkaddr = rvu_get_attach_blkaddr(rvu, BLKTYPE_CPT,
						 pcअगरunc, req);
		अगर (blkaddr < 0)
			वापस blkaddr;
		block = &hw->block[blkaddr];
		अगर (req->cptlfs > block->lf.max) अणु
			dev_err(&rvu->pdev->dev,
				"Func 0x%x: Invalid CPTLF req, %d > max %d\n",
				 pcअगरunc, req->cptlfs, block->lf.max);
			वापस -EINVAL;
		पूर्ण
		mappedlfs = rvu_get_rsrc_mapcount(pfvf, block->addr);
		मुक्त_lfs = rvu_rsrc_मुक्त_count(&block->lf);
		अगर (req->cptlfs > mappedlfs &&
		    ((req->cptlfs - mappedlfs) > मुक्त_lfs))
			जाओ fail;
	पूर्ण

	वापस 0;

fail:
	dev_info(rvu->dev, "Request for %s failed\n", block->name);
	वापस -ENOSPC;
पूर्ण

अटल bool rvu_attach_from_same_block(काष्ठा rvu *rvu, पूर्णांक blktype,
				       काष्ठा rsrc_attach *attach)
अणु
	पूर्णांक blkaddr, num_lfs;

	blkaddr = rvu_get_attach_blkaddr(rvu, blktype,
					 attach->hdr.pcअगरunc, attach);
	अगर (blkaddr < 0)
		वापस false;

	num_lfs = rvu_get_rsrc_mapcount(rvu_get_pfvf(rvu, attach->hdr.pcअगरunc),
					blkaddr);
	/* Requester alपढ़ोy has LFs from given block ? */
	वापस !!num_lfs;
पूर्ण

पूर्णांक rvu_mbox_handler_attach_resources(काष्ठा rvu *rvu,
				      काष्ठा rsrc_attach *attach,
				      काष्ठा msg_rsp *rsp)
अणु
	u16 pcअगरunc = attach->hdr.pcअगरunc;
	पूर्णांक err;

	/* If first request, detach all existing attached resources */
	अगर (!attach->modअगरy)
		rvu_detach_rsrcs(rvu, शून्य, pcअगरunc);

	mutex_lock(&rvu->rsrc_lock);

	/* Check अगर the request can be accommodated */
	err = rvu_check_rsrc_availability(rvu, attach, pcअगरunc);
	अगर (err)
		जाओ निकास;

	/* Now attach the requested resources */
	अगर (attach->npalf)
		rvu_attach_block(rvu, pcअगरunc, BLKTYPE_NPA, 1, attach);

	अगर (attach->nixlf)
		rvu_attach_block(rvu, pcअगरunc, BLKTYPE_NIX, 1, attach);

	अगर (attach->sso) अणु
		/* RVU func करोesn't know which exact LF or slot is attached
		 * to it, it always sees as slot 0,1,2. So क्रम a 'modify'
		 * request, simply detach all existing attached LFs/slots
		 * and attach a fresh.
		 */
		अगर (attach->modअगरy)
			rvu_detach_block(rvu, pcअगरunc, BLKTYPE_SSO);
		rvu_attach_block(rvu, pcअगरunc, BLKTYPE_SSO,
				 attach->sso, attach);
	पूर्ण

	अगर (attach->ssow) अणु
		अगर (attach->modअगरy)
			rvu_detach_block(rvu, pcअगरunc, BLKTYPE_SSOW);
		rvu_attach_block(rvu, pcअगरunc, BLKTYPE_SSOW,
				 attach->ssow, attach);
	पूर्ण

	अगर (attach->timlfs) अणु
		अगर (attach->modअगरy)
			rvu_detach_block(rvu, pcअगरunc, BLKTYPE_TIM);
		rvu_attach_block(rvu, pcअगरunc, BLKTYPE_TIM,
				 attach->timlfs, attach);
	पूर्ण

	अगर (attach->cptlfs) अणु
		अगर (attach->modअगरy &&
		    rvu_attach_from_same_block(rvu, BLKTYPE_CPT, attach))
			rvu_detach_block(rvu, pcअगरunc, BLKTYPE_CPT);
		rvu_attach_block(rvu, pcअगरunc, BLKTYPE_CPT,
				 attach->cptlfs, attach);
	पूर्ण

निकास:
	mutex_unlock(&rvu->rsrc_lock);
	वापस err;
पूर्ण

अटल u16 rvu_get_msix_offset(काष्ठा rvu *rvu, काष्ठा rvu_pfvf *pfvf,
			       पूर्णांक blkaddr, पूर्णांक lf)
अणु
	u16 vec;

	अगर (lf < 0)
		वापस MSIX_VECTOR_INVALID;

	क्रम (vec = 0; vec < pfvf->msix.max; vec++) अणु
		अगर (pfvf->msix_lfmap[vec] == MSIX_BLKLF(blkaddr, lf))
			वापस vec;
	पूर्ण
	वापस MSIX_VECTOR_INVALID;
पूर्ण

अटल व्योम rvu_set_msix_offset(काष्ठा rvu *rvu, काष्ठा rvu_pfvf *pfvf,
				काष्ठा rvu_block *block, पूर्णांक lf)
अणु
	u16 nvecs, vec, offset;
	u64 cfg;

	cfg = rvu_पढ़ो64(rvu, block->addr, block->msixcfg_reg |
			 (lf << block->lfshअगरt));
	nvecs = (cfg >> 12) & 0xFF;

	/* Check and alloc MSIX vectors, must be contiguous */
	अगर (!rvu_rsrc_check_contig(&pfvf->msix, nvecs))
		वापस;

	offset = rvu_alloc_rsrc_contig(&pfvf->msix, nvecs);

	/* Config MSIX offset in LF */
	rvu_ग_लिखो64(rvu, block->addr, block->msixcfg_reg |
		    (lf << block->lfshअगरt), (cfg & ~0x7FFULL) | offset);

	/* Update the biपंचांगap as well */
	क्रम (vec = 0; vec < nvecs; vec++)
		pfvf->msix_lfmap[offset + vec] = MSIX_BLKLF(block->addr, lf);
पूर्ण

अटल व्योम rvu_clear_msix_offset(काष्ठा rvu *rvu, काष्ठा rvu_pfvf *pfvf,
				  काष्ठा rvu_block *block, पूर्णांक lf)
अणु
	u16 nvecs, vec, offset;
	u64 cfg;

	cfg = rvu_पढ़ो64(rvu, block->addr, block->msixcfg_reg |
			 (lf << block->lfshअगरt));
	nvecs = (cfg >> 12) & 0xFF;

	/* Clear MSIX offset in LF */
	rvu_ग_लिखो64(rvu, block->addr, block->msixcfg_reg |
		    (lf << block->lfshअगरt), cfg & ~0x7FFULL);

	offset = rvu_get_msix_offset(rvu, pfvf, block->addr, lf);

	/* Update the mapping */
	क्रम (vec = 0; vec < nvecs; vec++)
		pfvf->msix_lfmap[offset + vec] = 0;

	/* Free the same in MSIX biपंचांगap */
	rvu_मुक्त_rsrc_contig(&pfvf->msix, nvecs, offset);
पूर्ण

पूर्णांक rvu_mbox_handler_msix_offset(काष्ठा rvu *rvu, काष्ठा msg_req *req,
				 काष्ठा msix_offset_rsp *rsp)
अणु
	काष्ठा rvu_hwinfo *hw = rvu->hw;
	u16 pcअगरunc = req->hdr.pcअगरunc;
	काष्ठा rvu_pfvf *pfvf;
	पूर्णांक lf, slot, blkaddr;

	pfvf = rvu_get_pfvf(rvu, pcअगरunc);
	अगर (!pfvf->msix.bmap)
		वापस 0;

	/* Set MSIX offsets क्रम each block's LFs attached to this PF/VF */
	lf = rvu_get_lf(rvu, &hw->block[BLKADDR_NPA], pcअगरunc, 0);
	rsp->npa_msixoff = rvu_get_msix_offset(rvu, pfvf, BLKADDR_NPA, lf);

	/* Get BLKADDR from which LFs are attached to pcअगरunc */
	blkaddr = rvu_get_blkaddr(rvu, BLKTYPE_NIX, pcअगरunc);
	अगर (blkaddr < 0) अणु
		rsp->nix_msixoff = MSIX_VECTOR_INVALID;
	पूर्ण अन्यथा अणु
		lf = rvu_get_lf(rvu, &hw->block[blkaddr], pcअगरunc, 0);
		rsp->nix_msixoff = rvu_get_msix_offset(rvu, pfvf, blkaddr, lf);
	पूर्ण

	rsp->sso = pfvf->sso;
	क्रम (slot = 0; slot < rsp->sso; slot++) अणु
		lf = rvu_get_lf(rvu, &hw->block[BLKADDR_SSO], pcअगरunc, slot);
		rsp->sso_msixoff[slot] =
			rvu_get_msix_offset(rvu, pfvf, BLKADDR_SSO, lf);
	पूर्ण

	rsp->ssow = pfvf->ssow;
	क्रम (slot = 0; slot < rsp->ssow; slot++) अणु
		lf = rvu_get_lf(rvu, &hw->block[BLKADDR_SSOW], pcअगरunc, slot);
		rsp->ssow_msixoff[slot] =
			rvu_get_msix_offset(rvu, pfvf, BLKADDR_SSOW, lf);
	पूर्ण

	rsp->timlfs = pfvf->timlfs;
	क्रम (slot = 0; slot < rsp->timlfs; slot++) अणु
		lf = rvu_get_lf(rvu, &hw->block[BLKADDR_TIM], pcअगरunc, slot);
		rsp->timlf_msixoff[slot] =
			rvu_get_msix_offset(rvu, pfvf, BLKADDR_TIM, lf);
	पूर्ण

	rsp->cptlfs = pfvf->cptlfs;
	क्रम (slot = 0; slot < rsp->cptlfs; slot++) अणु
		lf = rvu_get_lf(rvu, &hw->block[BLKADDR_CPT0], pcअगरunc, slot);
		rsp->cptlf_msixoff[slot] =
			rvu_get_msix_offset(rvu, pfvf, BLKADDR_CPT0, lf);
	पूर्ण

	rsp->cpt1_lfs = pfvf->cpt1_lfs;
	क्रम (slot = 0; slot < rsp->cpt1_lfs; slot++) अणु
		lf = rvu_get_lf(rvu, &hw->block[BLKADDR_CPT1], pcअगरunc, slot);
		rsp->cpt1_lf_msixoff[slot] =
			rvu_get_msix_offset(rvu, pfvf, BLKADDR_CPT1, lf);
	पूर्ण

	वापस 0;
पूर्ण

पूर्णांक rvu_mbox_handler_vf_flr(काष्ठा rvu *rvu, काष्ठा msg_req *req,
			    काष्ठा msg_rsp *rsp)
अणु
	u16 pcअगरunc = req->hdr.pcअगरunc;
	u16 vf, numvfs;
	u64 cfg;

	vf = pcअगरunc & RVU_PFVF_FUNC_MASK;
	cfg = rvu_पढ़ो64(rvu, BLKADDR_RVUM,
			 RVU_PRIV_PFX_CFG(rvu_get_pf(pcअगरunc)));
	numvfs = (cfg >> 12) & 0xFF;

	अगर (vf && vf <= numvfs)
		__rvu_flr_handler(rvu, pcअगरunc);
	अन्यथा
		वापस RVU_INVALID_VF_ID;

	वापस 0;
पूर्ण

पूर्णांक rvu_mbox_handler_get_hw_cap(काष्ठा rvu *rvu, काष्ठा msg_req *req,
				काष्ठा get_hw_cap_rsp *rsp)
अणु
	काष्ठा rvu_hwinfo *hw = rvu->hw;

	rsp->nix_fixed_txschq_mapping = hw->cap.nix_fixed_txschq_mapping;
	rsp->nix_shaping = hw->cap.nix_shaping;

	वापस 0;
पूर्ण

अटल पूर्णांक rvu_process_mbox_msg(काष्ठा otx2_mbox *mbox, पूर्णांक devid,
				काष्ठा mbox_msghdr *req)
अणु
	काष्ठा rvu *rvu = pci_get_drvdata(mbox->pdev);

	/* Check अगर valid, अगर not reply with a invalid msg */
	अगर (req->sig != OTX2_MBOX_REQ_SIG)
		जाओ bad_message;

	चयन (req->id) अणु
#घोषणा M(_name, _id, _fn_name, _req_type, _rsp_type)			\
	हाल _id: अणु							\
		काष्ठा _rsp_type *rsp;					\
		पूर्णांक err;						\
									\
		rsp = (काष्ठा _rsp_type *)otx2_mbox_alloc_msg(		\
			mbox, devid,					\
			माप(काष्ठा _rsp_type));			\
		/* some handlers should complete even अगर reply */	\
		/* could not be allocated */				\
		अगर (!rsp &&						\
		    _id != MBOX_MSG_DETACH_RESOURCES &&			\
		    _id != MBOX_MSG_NIX_TXSCH_FREE &&			\
		    _id != MBOX_MSG_VF_FLR)				\
			वापस -ENOMEM;					\
		अगर (rsp) अणु						\
			rsp->hdr.id = _id;				\
			rsp->hdr.sig = OTX2_MBOX_RSP_SIG;		\
			rsp->hdr.pcअगरunc = req->pcअगरunc;		\
			rsp->hdr.rc = 0;				\
		पूर्ण							\
									\
		err = rvu_mbox_handler_ ## _fn_name(rvu,		\
						    (काष्ठा _req_type *)req, \
						    rsp);		\
		अगर (rsp && err)						\
			rsp->hdr.rc = err;				\
									\
		trace_otx2_msg_process(mbox->pdev, _id, err);		\
		वापस rsp ? err : -ENOMEM;				\
	पूर्ण
MBOX_MESSAGES
#अघोषित M

bad_message:
	शेष:
		otx2_reply_invalid_msg(mbox, devid, req->pcअगरunc, req->id);
		वापस -ENODEV;
	पूर्ण
पूर्ण

अटल व्योम __rvu_mbox_handler(काष्ठा rvu_work *mwork, पूर्णांक type)
अणु
	काष्ठा rvu *rvu = mwork->rvu;
	पूर्णांक offset, err, id, devid;
	काष्ठा otx2_mbox_dev *mdev;
	काष्ठा mbox_hdr *req_hdr;
	काष्ठा mbox_msghdr *msg;
	काष्ठा mbox_wq_info *mw;
	काष्ठा otx2_mbox *mbox;

	चयन (type) अणु
	हाल TYPE_AFPF:
		mw = &rvu->afpf_wq_info;
		अवरोध;
	हाल TYPE_AFVF:
		mw = &rvu->afvf_wq_info;
		अवरोध;
	शेष:
		वापस;
	पूर्ण

	devid = mwork - mw->mbox_wrk;
	mbox = &mw->mbox;
	mdev = &mbox->dev[devid];

	/* Process received mbox messages */
	req_hdr = mdev->mbase + mbox->rx_start;
	अगर (mw->mbox_wrk[devid].num_msgs == 0)
		वापस;

	offset = mbox->rx_start + ALIGN(माप(*req_hdr), MBOX_MSG_ALIGN);

	क्रम (id = 0; id < mw->mbox_wrk[devid].num_msgs; id++) अणु
		msg = mdev->mbase + offset;

		/* Set which PF/VF sent this message based on mbox IRQ */
		चयन (type) अणु
		हाल TYPE_AFPF:
			msg->pcअगरunc &=
				~(RVU_PFVF_PF_MASK << RVU_PFVF_PF_SHIFT);
			msg->pcअगरunc |= (devid << RVU_PFVF_PF_SHIFT);
			अवरोध;
		हाल TYPE_AFVF:
			msg->pcअगरunc &=
				~(RVU_PFVF_FUNC_MASK << RVU_PFVF_FUNC_SHIFT);
			msg->pcअगरunc |= (devid << RVU_PFVF_FUNC_SHIFT) + 1;
			अवरोध;
		पूर्ण

		err = rvu_process_mbox_msg(mbox, devid, msg);
		अगर (!err) अणु
			offset = mbox->rx_start + msg->next_msgoff;
			जारी;
		पूर्ण

		अगर (msg->pcअगरunc & RVU_PFVF_FUNC_MASK)
			dev_warn(rvu->dev, "Error %d when processing message %s (0x%x) from PF%d:VF%d\n",
				 err, otx2_mbox_id2name(msg->id),
				 msg->id, rvu_get_pf(msg->pcअगरunc),
				 (msg->pcअगरunc & RVU_PFVF_FUNC_MASK) - 1);
		अन्यथा
			dev_warn(rvu->dev, "Error %d when processing message %s (0x%x) from PF%d\n",
				 err, otx2_mbox_id2name(msg->id),
				 msg->id, devid);
	पूर्ण
	mw->mbox_wrk[devid].num_msgs = 0;

	/* Send mbox responses to VF/PF */
	otx2_mbox_msg_send(mbox, devid);
पूर्ण

अटल अंतरभूत व्योम rvu_afpf_mbox_handler(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा rvu_work *mwork = container_of(work, काष्ठा rvu_work, work);

	__rvu_mbox_handler(mwork, TYPE_AFPF);
पूर्ण

अटल अंतरभूत व्योम rvu_afvf_mbox_handler(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा rvu_work *mwork = container_of(work, काष्ठा rvu_work, work);

	__rvu_mbox_handler(mwork, TYPE_AFVF);
पूर्ण

अटल व्योम __rvu_mbox_up_handler(काष्ठा rvu_work *mwork, पूर्णांक type)
अणु
	काष्ठा rvu *rvu = mwork->rvu;
	काष्ठा otx2_mbox_dev *mdev;
	काष्ठा mbox_hdr *rsp_hdr;
	काष्ठा mbox_msghdr *msg;
	काष्ठा mbox_wq_info *mw;
	काष्ठा otx2_mbox *mbox;
	पूर्णांक offset, id, devid;

	चयन (type) अणु
	हाल TYPE_AFPF:
		mw = &rvu->afpf_wq_info;
		अवरोध;
	हाल TYPE_AFVF:
		mw = &rvu->afvf_wq_info;
		अवरोध;
	शेष:
		वापस;
	पूर्ण

	devid = mwork - mw->mbox_wrk_up;
	mbox = &mw->mbox_up;
	mdev = &mbox->dev[devid];

	rsp_hdr = mdev->mbase + mbox->rx_start;
	अगर (mw->mbox_wrk_up[devid].up_num_msgs == 0) अणु
		dev_warn(rvu->dev, "mbox up handler: num_msgs = 0\n");
		वापस;
	पूर्ण

	offset = mbox->rx_start + ALIGN(माप(*rsp_hdr), MBOX_MSG_ALIGN);

	क्रम (id = 0; id < mw->mbox_wrk_up[devid].up_num_msgs; id++) अणु
		msg = mdev->mbase + offset;

		अगर (msg->id >= MBOX_MSG_MAX) अणु
			dev_err(rvu->dev,
				"Mbox msg with unknown ID 0x%x\n", msg->id);
			जाओ end;
		पूर्ण

		अगर (msg->sig != OTX2_MBOX_RSP_SIG) अणु
			dev_err(rvu->dev,
				"Mbox msg with wrong signature %x, ID 0x%x\n",
				msg->sig, msg->id);
			जाओ end;
		पूर्ण

		चयन (msg->id) अणु
		हाल MBOX_MSG_CGX_LINK_EVENT:
			अवरोध;
		शेष:
			अगर (msg->rc)
				dev_err(rvu->dev,
					"Mbox msg response has err %d, ID 0x%x\n",
					msg->rc, msg->id);
			अवरोध;
		पूर्ण
end:
		offset = mbox->rx_start + msg->next_msgoff;
		mdev->msgs_acked++;
	पूर्ण
	mw->mbox_wrk_up[devid].up_num_msgs = 0;

	otx2_mbox_reset(mbox, devid);
पूर्ण

अटल अंतरभूत व्योम rvu_afpf_mbox_up_handler(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा rvu_work *mwork = container_of(work, काष्ठा rvu_work, work);

	__rvu_mbox_up_handler(mwork, TYPE_AFPF);
पूर्ण

अटल अंतरभूत व्योम rvu_afvf_mbox_up_handler(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा rvu_work *mwork = container_of(work, काष्ठा rvu_work, work);

	__rvu_mbox_up_handler(mwork, TYPE_AFVF);
पूर्ण

अटल पूर्णांक rvu_get_mbox_regions(काष्ठा rvu *rvu, व्योम **mbox_addr,
				पूर्णांक num, पूर्णांक type)
अणु
	काष्ठा rvu_hwinfo *hw = rvu->hw;
	पूर्णांक region;
	u64 bar4;

	/* For cn10k platक्रमm VF mailbox regions of a PF follows after the
	 * PF <-> AF mailbox region. Whereas क्रम Octeontx2 it is पढ़ो from
	 * RVU_PF_VF_BAR4_ADDR रेजिस्टर.
	 */
	अगर (type == TYPE_AFVF) अणु
		क्रम (region = 0; region < num; region++) अणु
			अगर (hw->cap.per_pf_mbox_regs) अणु
				bar4 = rvu_पढ़ो64(rvu, BLKADDR_RVUM,
						  RVU_AF_PFX_BAR4_ADDR(0)) +
						  MBOX_SIZE;
				bar4 += region * MBOX_SIZE;
			पूर्ण अन्यथा अणु
				bar4 = rvupf_पढ़ो64(rvu, RVU_PF_VF_BAR4_ADDR);
				bar4 += region * MBOX_SIZE;
			पूर्ण
			mbox_addr[region] = (व्योम *)ioremap_wc(bar4, MBOX_SIZE);
			अगर (!mbox_addr[region])
				जाओ error;
		पूर्ण
		वापस 0;
	पूर्ण

	/* For cn10k platक्रमm AF <-> PF mailbox region of a PF is पढ़ो from per
	 * PF रेजिस्टरs. Whereas क्रम Octeontx2 it is पढ़ो from
	 * RVU_AF_PF_BAR4_ADDR रेजिस्टर.
	 */
	क्रम (region = 0; region < num; region++) अणु
		अगर (hw->cap.per_pf_mbox_regs) अणु
			bar4 = rvu_पढ़ो64(rvu, BLKADDR_RVUM,
					  RVU_AF_PFX_BAR4_ADDR(region));
		पूर्ण अन्यथा अणु
			bar4 = rvu_पढ़ो64(rvu, BLKADDR_RVUM,
					  RVU_AF_PF_BAR4_ADDR);
			bar4 += region * MBOX_SIZE;
		पूर्ण
		mbox_addr[region] = (व्योम *)ioremap_wc(bar4, MBOX_SIZE);
		अगर (!mbox_addr[region])
			जाओ error;
	पूर्ण
	वापस 0;

error:
	जबतक (region--)
		iounmap((व्योम __iomem *)mbox_addr[region]);
	वापस -ENOMEM;
पूर्ण

अटल पूर्णांक rvu_mbox_init(काष्ठा rvu *rvu, काष्ठा mbox_wq_info *mw,
			 पूर्णांक type, पूर्णांक num,
			 व्योम (mbox_handler)(काष्ठा work_काष्ठा *),
			 व्योम (mbox_up_handler)(काष्ठा work_काष्ठा *))
अणु
	पूर्णांक err = -EINVAL, i, dir, dir_up;
	व्योम __iomem *reg_base;
	काष्ठा rvu_work *mwork;
	व्योम **mbox_regions;
	स्थिर अक्षर *name;

	mbox_regions = kसुस्मृति(num, माप(व्योम *), GFP_KERNEL);
	अगर (!mbox_regions)
		वापस -ENOMEM;

	चयन (type) अणु
	हाल TYPE_AFPF:
		name = "rvu_afpf_mailbox";
		dir = MBOX_सूची_AFPF;
		dir_up = MBOX_सूची_AFPF_UP;
		reg_base = rvu->afreg_base;
		err = rvu_get_mbox_regions(rvu, mbox_regions, num, TYPE_AFPF);
		अगर (err)
			जाओ मुक्त_regions;
		अवरोध;
	हाल TYPE_AFVF:
		name = "rvu_afvf_mailbox";
		dir = MBOX_सूची_PFVF;
		dir_up = MBOX_सूची_PFVF_UP;
		reg_base = rvu->pfreg_base;
		err = rvu_get_mbox_regions(rvu, mbox_regions, num, TYPE_AFVF);
		अगर (err)
			जाओ मुक्त_regions;
		अवरोध;
	शेष:
		वापस err;
	पूर्ण

	mw->mbox_wq = alloc_workqueue(name,
				      WQ_UNBOUND | WQ_HIGHPRI | WQ_MEM_RECLAIM,
				      num);
	अगर (!mw->mbox_wq) अणु
		err = -ENOMEM;
		जाओ unmap_regions;
	पूर्ण

	mw->mbox_wrk = devm_kसुस्मृति(rvu->dev, num,
				    माप(काष्ठा rvu_work), GFP_KERNEL);
	अगर (!mw->mbox_wrk) अणु
		err = -ENOMEM;
		जाओ निकास;
	पूर्ण

	mw->mbox_wrk_up = devm_kसुस्मृति(rvu->dev, num,
				       माप(काष्ठा rvu_work), GFP_KERNEL);
	अगर (!mw->mbox_wrk_up) अणु
		err = -ENOMEM;
		जाओ निकास;
	पूर्ण

	err = otx2_mbox_regions_init(&mw->mbox, mbox_regions, rvu->pdev,
				     reg_base, dir, num);
	अगर (err)
		जाओ निकास;

	err = otx2_mbox_regions_init(&mw->mbox_up, mbox_regions, rvu->pdev,
				     reg_base, dir_up, num);
	अगर (err)
		जाओ निकास;

	क्रम (i = 0; i < num; i++) अणु
		mwork = &mw->mbox_wrk[i];
		mwork->rvu = rvu;
		INIT_WORK(&mwork->work, mbox_handler);

		mwork = &mw->mbox_wrk_up[i];
		mwork->rvu = rvu;
		INIT_WORK(&mwork->work, mbox_up_handler);
	पूर्ण
	kमुक्त(mbox_regions);
	वापस 0;

निकास:
	destroy_workqueue(mw->mbox_wq);
unmap_regions:
	जबतक (num--)
		iounmap((व्योम __iomem *)mbox_regions[num]);
मुक्त_regions:
	kमुक्त(mbox_regions);
	वापस err;
पूर्ण

अटल व्योम rvu_mbox_destroy(काष्ठा mbox_wq_info *mw)
अणु
	काष्ठा otx2_mbox *mbox = &mw->mbox;
	काष्ठा otx2_mbox_dev *mdev;
	पूर्णांक devid;

	अगर (mw->mbox_wq) अणु
		flush_workqueue(mw->mbox_wq);
		destroy_workqueue(mw->mbox_wq);
		mw->mbox_wq = शून्य;
	पूर्ण

	क्रम (devid = 0; devid < mbox->ndevs; devid++) अणु
		mdev = &mbox->dev[devid];
		अगर (mdev->hwbase)
			iounmap((व्योम __iomem *)mdev->hwbase);
	पूर्ण

	otx2_mbox_destroy(&mw->mbox);
	otx2_mbox_destroy(&mw->mbox_up);
पूर्ण

अटल व्योम rvu_queue_work(काष्ठा mbox_wq_info *mw, पूर्णांक first,
			   पूर्णांक mdevs, u64 पूर्णांकr)
अणु
	काष्ठा otx2_mbox_dev *mdev;
	काष्ठा otx2_mbox *mbox;
	काष्ठा mbox_hdr *hdr;
	पूर्णांक i;

	क्रम (i = first; i < mdevs; i++) अणु
		/* start from 0 */
		अगर (!(पूर्णांकr & BIT_ULL(i - first)))
			जारी;

		mbox = &mw->mbox;
		mdev = &mbox->dev[i];
		hdr = mdev->mbase + mbox->rx_start;

		/*The hdr->num_msgs is set to zero immediately in the पूर्णांकerrupt
		 * handler to  ensure that it holds a correct value next समय
		 * when the पूर्णांकerrupt handler is called.
		 * pf->mbox.num_msgs holds the data क्रम use in pfaf_mbox_handler
		 * pf>mbox.up_num_msgs holds the data क्रम use in
		 * pfaf_mbox_up_handler.
		 */

		अगर (hdr->num_msgs) अणु
			mw->mbox_wrk[i].num_msgs = hdr->num_msgs;
			hdr->num_msgs = 0;
			queue_work(mw->mbox_wq, &mw->mbox_wrk[i].work);
		पूर्ण
		mbox = &mw->mbox_up;
		mdev = &mbox->dev[i];
		hdr = mdev->mbase + mbox->rx_start;
		अगर (hdr->num_msgs) अणु
			mw->mbox_wrk_up[i].up_num_msgs = hdr->num_msgs;
			hdr->num_msgs = 0;
			queue_work(mw->mbox_wq, &mw->mbox_wrk_up[i].work);
		पूर्ण
	पूर्ण
पूर्ण

अटल irqवापस_t rvu_mbox_पूर्णांकr_handler(पूर्णांक irq, व्योम *rvu_irq)
अणु
	काष्ठा rvu *rvu = (काष्ठा rvu *)rvu_irq;
	पूर्णांक vfs = rvu->vfs;
	u64 पूर्णांकr;

	पूर्णांकr = rvu_पढ़ो64(rvu, BLKADDR_RVUM, RVU_AF_PFAF_MBOX_INT);
	/* Clear पूर्णांकerrupts */
	rvu_ग_लिखो64(rvu, BLKADDR_RVUM, RVU_AF_PFAF_MBOX_INT, पूर्णांकr);
	अगर (पूर्णांकr)
		trace_otx2_msg_पूर्णांकerrupt(rvu->pdev, "PF(s) to AF", पूर्णांकr);

	/* Sync with mbox memory region */
	rmb();

	rvu_queue_work(&rvu->afpf_wq_info, 0, rvu->hw->total_pfs, पूर्णांकr);

	/* Handle VF पूर्णांकerrupts */
	अगर (vfs > 64) अणु
		पूर्णांकr = rvupf_पढ़ो64(rvu, RVU_PF_VFPF_MBOX_INTX(1));
		rvupf_ग_लिखो64(rvu, RVU_PF_VFPF_MBOX_INTX(1), पूर्णांकr);

		rvu_queue_work(&rvu->afvf_wq_info, 64, vfs, पूर्णांकr);
		vfs -= 64;
	पूर्ण

	पूर्णांकr = rvupf_पढ़ो64(rvu, RVU_PF_VFPF_MBOX_INTX(0));
	rvupf_ग_लिखो64(rvu, RVU_PF_VFPF_MBOX_INTX(0), पूर्णांकr);
	अगर (पूर्णांकr)
		trace_otx2_msg_पूर्णांकerrupt(rvu->pdev, "VF(s) to AF", पूर्णांकr);

	rvu_queue_work(&rvu->afvf_wq_info, 0, vfs, पूर्णांकr);

	वापस IRQ_HANDLED;
पूर्ण

अटल व्योम rvu_enable_mbox_पूर्णांकr(काष्ठा rvu *rvu)
अणु
	काष्ठा rvu_hwinfo *hw = rvu->hw;

	/* Clear spurious irqs, अगर any */
	rvu_ग_लिखो64(rvu, BLKADDR_RVUM,
		    RVU_AF_PFAF_MBOX_INT, INTR_MASK(hw->total_pfs));

	/* Enable mailbox पूर्णांकerrupt क्रम all PFs except PF0 i.e AF itself */
	rvu_ग_लिखो64(rvu, BLKADDR_RVUM, RVU_AF_PFAF_MBOX_INT_ENA_W1S,
		    INTR_MASK(hw->total_pfs) & ~1ULL);
पूर्ण

अटल व्योम rvu_blklf_tearकरोwn(काष्ठा rvu *rvu, u16 pcअगरunc, u8 blkaddr)
अणु
	काष्ठा rvu_block *block;
	पूर्णांक slot, lf, num_lfs;
	पूर्णांक err;

	block = &rvu->hw->block[blkaddr];
	num_lfs = rvu_get_rsrc_mapcount(rvu_get_pfvf(rvu, pcअगरunc),
					block->addr);
	अगर (!num_lfs)
		वापस;
	क्रम (slot = 0; slot < num_lfs; slot++) अणु
		lf = rvu_get_lf(rvu, block, pcअगरunc, slot);
		अगर (lf < 0)
			जारी;

		/* Cleanup LF and reset it */
		अगर (block->addr == BLKADDR_NIX0 || block->addr == BLKADDR_NIX1)
			rvu_nix_lf_tearकरोwn(rvu, pcअगरunc, block->addr, lf);
		अन्यथा अगर (block->addr == BLKADDR_NPA)
			rvu_npa_lf_tearकरोwn(rvu, pcअगरunc, lf);
		अन्यथा अगर ((block->addr == BLKADDR_CPT0) ||
			 (block->addr == BLKADDR_CPT1))
			rvu_cpt_lf_tearकरोwn(rvu, pcअगरunc, lf, slot);

		err = rvu_lf_reset(rvu, block, lf);
		अगर (err) अणु
			dev_err(rvu->dev, "Failed to reset blkaddr %d LF%d\n",
				block->addr, lf);
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम __rvu_flr_handler(काष्ठा rvu *rvu, u16 pcअगरunc)
अणु
	mutex_lock(&rvu->flr_lock);
	/* Reset order should reflect पूर्णांकer-block dependencies:
	 * 1. Reset any packet/work sources (NIX, CPT, TIM)
	 * 2. Flush and reset SSO/SSOW
	 * 3. Cleanup pools (NPA)
	 */
	rvu_blklf_tearकरोwn(rvu, pcअगरunc, BLKADDR_NIX0);
	rvu_blklf_tearकरोwn(rvu, pcअगरunc, BLKADDR_NIX1);
	rvu_blklf_tearकरोwn(rvu, pcअगरunc, BLKADDR_CPT0);
	rvu_blklf_tearकरोwn(rvu, pcअगरunc, BLKADDR_CPT1);
	rvu_blklf_tearकरोwn(rvu, pcअगरunc, BLKADDR_TIM);
	rvu_blklf_tearकरोwn(rvu, pcअगरunc, BLKADDR_SSOW);
	rvu_blklf_tearकरोwn(rvu, pcअगरunc, BLKADDR_SSO);
	rvu_blklf_tearकरोwn(rvu, pcअगरunc, BLKADDR_NPA);
	rvu_detach_rsrcs(rvu, शून्य, pcअगरunc);
	mutex_unlock(&rvu->flr_lock);
पूर्ण

अटल व्योम rvu_afvf_flr_handler(काष्ठा rvu *rvu, पूर्णांक vf)
अणु
	पूर्णांक reg = 0;

	/* pcअगरunc = 0(PF0) | (vf + 1) */
	__rvu_flr_handler(rvu, vf + 1);

	अगर (vf >= 64) अणु
		reg = 1;
		vf = vf - 64;
	पूर्ण

	/* Signal FLR finish and enable IRQ */
	rvupf_ग_लिखो64(rvu, RVU_PF_VFTRPENDX(reg), BIT_ULL(vf));
	rvupf_ग_लिखो64(rvu, RVU_PF_VFFLR_INT_ENA_W1SX(reg), BIT_ULL(vf));
पूर्ण

अटल व्योम rvu_flr_handler(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा rvu_work *flrwork = container_of(work, काष्ठा rvu_work, work);
	काष्ठा rvu *rvu = flrwork->rvu;
	u16 pcअगरunc, numvfs, vf;
	u64 cfg;
	पूर्णांक pf;

	pf = flrwork - rvu->flr_wrk;
	अगर (pf >= rvu->hw->total_pfs) अणु
		rvu_afvf_flr_handler(rvu, pf - rvu->hw->total_pfs);
		वापस;
	पूर्ण

	cfg = rvu_पढ़ो64(rvu, BLKADDR_RVUM, RVU_PRIV_PFX_CFG(pf));
	numvfs = (cfg >> 12) & 0xFF;
	pcअगरunc  = pf << RVU_PFVF_PF_SHIFT;

	क्रम (vf = 0; vf < numvfs; vf++)
		__rvu_flr_handler(rvu, (pcअगरunc | (vf + 1)));

	__rvu_flr_handler(rvu, pcअगरunc);

	/* Signal FLR finish */
	rvu_ग_लिखो64(rvu, BLKADDR_RVUM, RVU_AF_PFTRPEND, BIT_ULL(pf));

	/* Enable पूर्णांकerrupt */
	rvu_ग_लिखो64(rvu, BLKADDR_RVUM, RVU_AF_PFFLR_INT_ENA_W1S,  BIT_ULL(pf));
पूर्ण

अटल व्योम rvu_afvf_queue_flr_work(काष्ठा rvu *rvu, पूर्णांक start_vf, पूर्णांक numvfs)
अणु
	पूर्णांक dev, vf, reg = 0;
	u64 पूर्णांकr;

	अगर (start_vf >= 64)
		reg = 1;

	पूर्णांकr = rvupf_पढ़ो64(rvu, RVU_PF_VFFLR_INTX(reg));
	अगर (!पूर्णांकr)
		वापस;

	क्रम (vf = 0; vf < numvfs; vf++) अणु
		अगर (!(पूर्णांकr & BIT_ULL(vf)))
			जारी;
		dev = vf + start_vf + rvu->hw->total_pfs;
		queue_work(rvu->flr_wq, &rvu->flr_wrk[dev].work);
		/* Clear and disable the पूर्णांकerrupt */
		rvupf_ग_लिखो64(rvu, RVU_PF_VFFLR_INTX(reg), BIT_ULL(vf));
		rvupf_ग_लिखो64(rvu, RVU_PF_VFFLR_INT_ENA_W1CX(reg), BIT_ULL(vf));
	पूर्ण
पूर्ण

अटल irqवापस_t rvu_flr_पूर्णांकr_handler(पूर्णांक irq, व्योम *rvu_irq)
अणु
	काष्ठा rvu *rvu = (काष्ठा rvu *)rvu_irq;
	u64 पूर्णांकr;
	u8  pf;

	पूर्णांकr = rvu_पढ़ो64(rvu, BLKADDR_RVUM, RVU_AF_PFFLR_INT);
	अगर (!पूर्णांकr)
		जाओ afvf_flr;

	क्रम (pf = 0; pf < rvu->hw->total_pfs; pf++) अणु
		अगर (पूर्णांकr & (1ULL << pf)) अणु
			/* PF is alपढ़ोy dead करो only AF related operations */
			queue_work(rvu->flr_wq, &rvu->flr_wrk[pf].work);
			/* clear पूर्णांकerrupt */
			rvu_ग_लिखो64(rvu, BLKADDR_RVUM, RVU_AF_PFFLR_INT,
				    BIT_ULL(pf));
			/* Disable the पूर्णांकerrupt */
			rvu_ग_लिखो64(rvu, BLKADDR_RVUM, RVU_AF_PFFLR_INT_ENA_W1C,
				    BIT_ULL(pf));
		पूर्ण
	पूर्ण

afvf_flr:
	rvu_afvf_queue_flr_work(rvu, 0, 64);
	अगर (rvu->vfs > 64)
		rvu_afvf_queue_flr_work(rvu, 64, rvu->vfs - 64);

	वापस IRQ_HANDLED;
पूर्ण

अटल व्योम rvu_me_handle_vfset(काष्ठा rvu *rvu, पूर्णांक idx, u64 पूर्णांकr)
अणु
	पूर्णांक vf;

	/* Nothing to be करोne here other than clearing the
	 * TRPEND bit.
	 */
	क्रम (vf = 0; vf < 64; vf++) अणु
		अगर (पूर्णांकr & (1ULL << vf)) अणु
			/* clear the trpend due to ME(master enable) */
			rvupf_ग_लिखो64(rvu, RVU_PF_VFTRPENDX(idx), BIT_ULL(vf));
			/* clear पूर्णांकerrupt */
			rvupf_ग_लिखो64(rvu, RVU_PF_VFME_INTX(idx), BIT_ULL(vf));
		पूर्ण
	पूर्ण
पूर्ण

/* Handles ME पूर्णांकerrupts from VFs of AF */
अटल irqवापस_t rvu_me_vf_पूर्णांकr_handler(पूर्णांक irq, व्योम *rvu_irq)
अणु
	काष्ठा rvu *rvu = (काष्ठा rvu *)rvu_irq;
	पूर्णांक vfset;
	u64 पूर्णांकr;

	पूर्णांकr = rvu_पढ़ो64(rvu, BLKADDR_RVUM, RVU_AF_PFME_INT);

	क्रम (vfset = 0; vfset <= 1; vfset++) अणु
		पूर्णांकr = rvupf_पढ़ो64(rvu, RVU_PF_VFME_INTX(vfset));
		अगर (पूर्णांकr)
			rvu_me_handle_vfset(rvu, vfset, पूर्णांकr);
	पूर्ण

	वापस IRQ_HANDLED;
पूर्ण

/* Handles ME पूर्णांकerrupts from PFs */
अटल irqवापस_t rvu_me_pf_पूर्णांकr_handler(पूर्णांक irq, व्योम *rvu_irq)
अणु
	काष्ठा rvu *rvu = (काष्ठा rvu *)rvu_irq;
	u64 पूर्णांकr;
	u8  pf;

	पूर्णांकr = rvu_पढ़ो64(rvu, BLKADDR_RVUM, RVU_AF_PFME_INT);

	/* Nothing to be करोne here other than clearing the
	 * TRPEND bit.
	 */
	क्रम (pf = 0; pf < rvu->hw->total_pfs; pf++) अणु
		अगर (पूर्णांकr & (1ULL << pf)) अणु
			/* clear the trpend due to ME(master enable) */
			rvu_ग_लिखो64(rvu, BLKADDR_RVUM, RVU_AF_PFTRPEND,
				    BIT_ULL(pf));
			/* clear पूर्णांकerrupt */
			rvu_ग_लिखो64(rvu, BLKADDR_RVUM, RVU_AF_PFME_INT,
				    BIT_ULL(pf));
		पूर्ण
	पूर्ण

	वापस IRQ_HANDLED;
पूर्ण

अटल व्योम rvu_unरेजिस्टर_पूर्णांकerrupts(काष्ठा rvu *rvu)
अणु
	पूर्णांक irq;

	/* Disable the Mbox पूर्णांकerrupt */
	rvu_ग_लिखो64(rvu, BLKADDR_RVUM, RVU_AF_PFAF_MBOX_INT_ENA_W1C,
		    INTR_MASK(rvu->hw->total_pfs) & ~1ULL);

	/* Disable the PF FLR पूर्णांकerrupt */
	rvu_ग_लिखो64(rvu, BLKADDR_RVUM, RVU_AF_PFFLR_INT_ENA_W1C,
		    INTR_MASK(rvu->hw->total_pfs) & ~1ULL);

	/* Disable the PF ME पूर्णांकerrupt */
	rvu_ग_लिखो64(rvu, BLKADDR_RVUM, RVU_AF_PFME_INT_ENA_W1C,
		    INTR_MASK(rvu->hw->total_pfs) & ~1ULL);

	क्रम (irq = 0; irq < rvu->num_vec; irq++) अणु
		अगर (rvu->irq_allocated[irq]) अणु
			मुक्त_irq(pci_irq_vector(rvu->pdev, irq), rvu);
			rvu->irq_allocated[irq] = false;
		पूर्ण
	पूर्ण

	pci_मुक्त_irq_vectors(rvu->pdev);
	rvu->num_vec = 0;
पूर्ण

अटल पूर्णांक rvu_afvf_msix_vectors_num_ok(काष्ठा rvu *rvu)
अणु
	काष्ठा rvu_pfvf *pfvf = &rvu->pf[0];
	पूर्णांक offset;

	pfvf = &rvu->pf[0];
	offset = rvu_पढ़ो64(rvu, BLKADDR_RVUM, RVU_PRIV_PFX_INT_CFG(0)) & 0x3ff;

	/* Make sure there are enough MSIX vectors configured so that
	 * VF पूर्णांकerrupts can be handled. Offset equal to zero means
	 * that PF vectors are not configured and overlapping AF vectors.
	 */
	वापस (pfvf->msix.max >= RVU_AF_INT_VEC_CNT + RVU_PF_INT_VEC_CNT) &&
	       offset;
पूर्ण

अटल पूर्णांक rvu_रेजिस्टर_पूर्णांकerrupts(काष्ठा rvu *rvu)
अणु
	पूर्णांक ret, offset, pf_vec_start;

	rvu->num_vec = pci_msix_vec_count(rvu->pdev);

	rvu->irq_name = devm_kदो_स्मृति_array(rvu->dev, rvu->num_vec,
					   NAME_SIZE, GFP_KERNEL);
	अगर (!rvu->irq_name)
		वापस -ENOMEM;

	rvu->irq_allocated = devm_kसुस्मृति(rvu->dev, rvu->num_vec,
					  माप(bool), GFP_KERNEL);
	अगर (!rvu->irq_allocated)
		वापस -ENOMEM;

	/* Enable MSI-X */
	ret = pci_alloc_irq_vectors(rvu->pdev, rvu->num_vec,
				    rvu->num_vec, PCI_IRQ_MSIX);
	अगर (ret < 0) अणु
		dev_err(rvu->dev,
			"RVUAF: Request for %d msix vectors failed, ret %d\n",
			rvu->num_vec, ret);
		वापस ret;
	पूर्ण

	/* Register mailbox पूर्णांकerrupt handler */
	प्र_लिखो(&rvu->irq_name[RVU_AF_INT_VEC_MBOX * NAME_SIZE], "RVUAF Mbox");
	ret = request_irq(pci_irq_vector(rvu->pdev, RVU_AF_INT_VEC_MBOX),
			  rvu_mbox_पूर्णांकr_handler, 0,
			  &rvu->irq_name[RVU_AF_INT_VEC_MBOX * NAME_SIZE], rvu);
	अगर (ret) अणु
		dev_err(rvu->dev,
			"RVUAF: IRQ registration failed for mbox irq\n");
		जाओ fail;
	पूर्ण

	rvu->irq_allocated[RVU_AF_INT_VEC_MBOX] = true;

	/* Enable mailbox पूर्णांकerrupts from all PFs */
	rvu_enable_mbox_पूर्णांकr(rvu);

	/* Register FLR पूर्णांकerrupt handler */
	प्र_लिखो(&rvu->irq_name[RVU_AF_INT_VEC_PFFLR * NAME_SIZE],
		"RVUAF FLR");
	ret = request_irq(pci_irq_vector(rvu->pdev, RVU_AF_INT_VEC_PFFLR),
			  rvu_flr_पूर्णांकr_handler, 0,
			  &rvu->irq_name[RVU_AF_INT_VEC_PFFLR * NAME_SIZE],
			  rvu);
	अगर (ret) अणु
		dev_err(rvu->dev,
			"RVUAF: IRQ registration failed for FLR\n");
		जाओ fail;
	पूर्ण
	rvu->irq_allocated[RVU_AF_INT_VEC_PFFLR] = true;

	/* Enable FLR पूर्णांकerrupt क्रम all PFs*/
	rvu_ग_लिखो64(rvu, BLKADDR_RVUM,
		    RVU_AF_PFFLR_INT, INTR_MASK(rvu->hw->total_pfs));

	rvu_ग_लिखो64(rvu, BLKADDR_RVUM, RVU_AF_PFFLR_INT_ENA_W1S,
		    INTR_MASK(rvu->hw->total_pfs) & ~1ULL);

	/* Register ME पूर्णांकerrupt handler */
	प्र_लिखो(&rvu->irq_name[RVU_AF_INT_VEC_PFME * NAME_SIZE],
		"RVUAF ME");
	ret = request_irq(pci_irq_vector(rvu->pdev, RVU_AF_INT_VEC_PFME),
			  rvu_me_pf_पूर्णांकr_handler, 0,
			  &rvu->irq_name[RVU_AF_INT_VEC_PFME * NAME_SIZE],
			  rvu);
	अगर (ret) अणु
		dev_err(rvu->dev,
			"RVUAF: IRQ registration failed for ME\n");
	पूर्ण
	rvu->irq_allocated[RVU_AF_INT_VEC_PFME] = true;

	/* Clear TRPEND bit क्रम all PF */
	rvu_ग_लिखो64(rvu, BLKADDR_RVUM,
		    RVU_AF_PFTRPEND, INTR_MASK(rvu->hw->total_pfs));
	/* Enable ME पूर्णांकerrupt क्रम all PFs*/
	rvu_ग_लिखो64(rvu, BLKADDR_RVUM,
		    RVU_AF_PFME_INT, INTR_MASK(rvu->hw->total_pfs));

	rvu_ग_लिखो64(rvu, BLKADDR_RVUM, RVU_AF_PFME_INT_ENA_W1S,
		    INTR_MASK(rvu->hw->total_pfs) & ~1ULL);

	अगर (!rvu_afvf_msix_vectors_num_ok(rvu))
		वापस 0;

	/* Get PF MSIX vectors offset. */
	pf_vec_start = rvu_पढ़ो64(rvu, BLKADDR_RVUM,
				  RVU_PRIV_PFX_INT_CFG(0)) & 0x3ff;

	/* Register MBOX0 पूर्णांकerrupt. */
	offset = pf_vec_start + RVU_PF_INT_VEC_VFPF_MBOX0;
	प्र_लिखो(&rvu->irq_name[offset * NAME_SIZE], "RVUAFVF Mbox0");
	ret = request_irq(pci_irq_vector(rvu->pdev, offset),
			  rvu_mbox_पूर्णांकr_handler, 0,
			  &rvu->irq_name[offset * NAME_SIZE],
			  rvu);
	अगर (ret)
		dev_err(rvu->dev,
			"RVUAF: IRQ registration failed for Mbox0\n");

	rvu->irq_allocated[offset] = true;

	/* Register MBOX1 पूर्णांकerrupt. MBOX1 IRQ number follows MBOX0 so
	 * simply increment current offset by 1.
	 */
	offset = pf_vec_start + RVU_PF_INT_VEC_VFPF_MBOX1;
	प्र_लिखो(&rvu->irq_name[offset * NAME_SIZE], "RVUAFVF Mbox1");
	ret = request_irq(pci_irq_vector(rvu->pdev, offset),
			  rvu_mbox_पूर्णांकr_handler, 0,
			  &rvu->irq_name[offset * NAME_SIZE],
			  rvu);
	अगर (ret)
		dev_err(rvu->dev,
			"RVUAF: IRQ registration failed for Mbox1\n");

	rvu->irq_allocated[offset] = true;

	/* Register FLR पूर्णांकerrupt handler क्रम AF's VFs */
	offset = pf_vec_start + RVU_PF_INT_VEC_VFFLR0;
	प्र_लिखो(&rvu->irq_name[offset * NAME_SIZE], "RVUAFVF FLR0");
	ret = request_irq(pci_irq_vector(rvu->pdev, offset),
			  rvu_flr_पूर्णांकr_handler, 0,
			  &rvu->irq_name[offset * NAME_SIZE], rvu);
	अगर (ret) अणु
		dev_err(rvu->dev,
			"RVUAF: IRQ registration failed for RVUAFVF FLR0\n");
		जाओ fail;
	पूर्ण
	rvu->irq_allocated[offset] = true;

	offset = pf_vec_start + RVU_PF_INT_VEC_VFFLR1;
	प्र_लिखो(&rvu->irq_name[offset * NAME_SIZE], "RVUAFVF FLR1");
	ret = request_irq(pci_irq_vector(rvu->pdev, offset),
			  rvu_flr_पूर्णांकr_handler, 0,
			  &rvu->irq_name[offset * NAME_SIZE], rvu);
	अगर (ret) अणु
		dev_err(rvu->dev,
			"RVUAF: IRQ registration failed for RVUAFVF FLR1\n");
		जाओ fail;
	पूर्ण
	rvu->irq_allocated[offset] = true;

	/* Register ME पूर्णांकerrupt handler क्रम AF's VFs */
	offset = pf_vec_start + RVU_PF_INT_VEC_VFME0;
	प्र_लिखो(&rvu->irq_name[offset * NAME_SIZE], "RVUAFVF ME0");
	ret = request_irq(pci_irq_vector(rvu->pdev, offset),
			  rvu_me_vf_पूर्णांकr_handler, 0,
			  &rvu->irq_name[offset * NAME_SIZE], rvu);
	अगर (ret) अणु
		dev_err(rvu->dev,
			"RVUAF: IRQ registration failed for RVUAFVF ME0\n");
		जाओ fail;
	पूर्ण
	rvu->irq_allocated[offset] = true;

	offset = pf_vec_start + RVU_PF_INT_VEC_VFME1;
	प्र_लिखो(&rvu->irq_name[offset * NAME_SIZE], "RVUAFVF ME1");
	ret = request_irq(pci_irq_vector(rvu->pdev, offset),
			  rvu_me_vf_पूर्णांकr_handler, 0,
			  &rvu->irq_name[offset * NAME_SIZE], rvu);
	अगर (ret) अणु
		dev_err(rvu->dev,
			"RVUAF: IRQ registration failed for RVUAFVF ME1\n");
		जाओ fail;
	पूर्ण
	rvu->irq_allocated[offset] = true;
	वापस 0;

fail:
	rvu_unरेजिस्टर_पूर्णांकerrupts(rvu);
	वापस ret;
पूर्ण

अटल व्योम rvu_flr_wq_destroy(काष्ठा rvu *rvu)
अणु
	अगर (rvu->flr_wq) अणु
		flush_workqueue(rvu->flr_wq);
		destroy_workqueue(rvu->flr_wq);
		rvu->flr_wq = शून्य;
	पूर्ण
पूर्ण

अटल पूर्णांक rvu_flr_init(काष्ठा rvu *rvu)
अणु
	पूर्णांक dev, num_devs;
	u64 cfg;
	पूर्णांक pf;

	/* Enable FLR क्रम all PFs*/
	क्रम (pf = 0; pf < rvu->hw->total_pfs; pf++) अणु
		cfg = rvu_पढ़ो64(rvu, BLKADDR_RVUM, RVU_PRIV_PFX_CFG(pf));
		rvu_ग_लिखो64(rvu, BLKADDR_RVUM, RVU_PRIV_PFX_CFG(pf),
			    cfg | BIT_ULL(22));
	पूर्ण

	rvu->flr_wq = alloc_workqueue("rvu_afpf_flr",
				      WQ_UNBOUND | WQ_HIGHPRI | WQ_MEM_RECLAIM,
				       1);
	अगर (!rvu->flr_wq)
		वापस -ENOMEM;

	num_devs = rvu->hw->total_pfs + pci_sriov_get_totalvfs(rvu->pdev);
	rvu->flr_wrk = devm_kसुस्मृति(rvu->dev, num_devs,
				    माप(काष्ठा rvu_work), GFP_KERNEL);
	अगर (!rvu->flr_wrk) अणु
		destroy_workqueue(rvu->flr_wq);
		वापस -ENOMEM;
	पूर्ण

	क्रम (dev = 0; dev < num_devs; dev++) अणु
		rvu->flr_wrk[dev].rvu = rvu;
		INIT_WORK(&rvu->flr_wrk[dev].work, rvu_flr_handler);
	पूर्ण

	mutex_init(&rvu->flr_lock);

	वापस 0;
पूर्ण

अटल व्योम rvu_disable_afvf_पूर्णांकr(काष्ठा rvu *rvu)
अणु
	पूर्णांक vfs = rvu->vfs;

	rvupf_ग_लिखो64(rvu, RVU_PF_VFPF_MBOX_INT_ENA_W1CX(0), INTR_MASK(vfs));
	rvupf_ग_लिखो64(rvu, RVU_PF_VFFLR_INT_ENA_W1CX(0), INTR_MASK(vfs));
	rvupf_ग_लिखो64(rvu, RVU_PF_VFME_INT_ENA_W1CX(0), INTR_MASK(vfs));
	अगर (vfs <= 64)
		वापस;

	rvupf_ग_लिखो64(rvu, RVU_PF_VFPF_MBOX_INT_ENA_W1CX(1),
		      INTR_MASK(vfs - 64));
	rvupf_ग_लिखो64(rvu, RVU_PF_VFFLR_INT_ENA_W1CX(1), INTR_MASK(vfs - 64));
	rvupf_ग_लिखो64(rvu, RVU_PF_VFME_INT_ENA_W1CX(1), INTR_MASK(vfs - 64));
पूर्ण

अटल व्योम rvu_enable_afvf_पूर्णांकr(काष्ठा rvu *rvu)
अणु
	पूर्णांक vfs = rvu->vfs;

	/* Clear any pending पूर्णांकerrupts and enable AF VF पूर्णांकerrupts क्रम
	 * the first 64 VFs.
	 */
	/* Mbox */
	rvupf_ग_लिखो64(rvu, RVU_PF_VFPF_MBOX_INTX(0), INTR_MASK(vfs));
	rvupf_ग_लिखो64(rvu, RVU_PF_VFPF_MBOX_INT_ENA_W1SX(0), INTR_MASK(vfs));

	/* FLR */
	rvupf_ग_लिखो64(rvu, RVU_PF_VFFLR_INTX(0), INTR_MASK(vfs));
	rvupf_ग_लिखो64(rvu, RVU_PF_VFFLR_INT_ENA_W1SX(0), INTR_MASK(vfs));
	rvupf_ग_लिखो64(rvu, RVU_PF_VFME_INT_ENA_W1SX(0), INTR_MASK(vfs));

	/* Same क्रम reमुख्यing VFs, अगर any. */
	अगर (vfs <= 64)
		वापस;

	rvupf_ग_लिखो64(rvu, RVU_PF_VFPF_MBOX_INTX(1), INTR_MASK(vfs - 64));
	rvupf_ग_लिखो64(rvu, RVU_PF_VFPF_MBOX_INT_ENA_W1SX(1),
		      INTR_MASK(vfs - 64));

	rvupf_ग_लिखो64(rvu, RVU_PF_VFFLR_INTX(1), INTR_MASK(vfs - 64));
	rvupf_ग_लिखो64(rvu, RVU_PF_VFFLR_INT_ENA_W1SX(1), INTR_MASK(vfs - 64));
	rvupf_ग_लिखो64(rvu, RVU_PF_VFME_INT_ENA_W1SX(1), INTR_MASK(vfs - 64));
पूर्ण

पूर्णांक rvu_get_num_lbk_chans(व्योम)
अणु
	काष्ठा pci_dev *pdev;
	व्योम __iomem *base;
	पूर्णांक ret = -EIO;

	pdev = pci_get_device(PCI_VENDOR_ID_CAVIUM, PCI_DEVID_OCTEONTX2_LBK,
			      शून्य);
	अगर (!pdev)
		जाओ err;

	base = pci_ioremap_bar(pdev, 0);
	अगर (!base)
		जाओ err_put;

	/* Read number of available LBK channels from LBK(0)_CONST रेजिस्टर. */
	ret = (पढ़ोq(base + 0x10) >> 32) & 0xffff;
	iounmap(base);
err_put:
	pci_dev_put(pdev);
err:
	वापस ret;
पूर्ण

अटल पूर्णांक rvu_enable_sriov(काष्ठा rvu *rvu)
अणु
	काष्ठा pci_dev *pdev = rvu->pdev;
	पूर्णांक err, chans, vfs;

	अगर (!rvu_afvf_msix_vectors_num_ok(rvu)) अणु
		dev_warn(&pdev->dev,
			 "Skipping SRIOV enablement since not enough IRQs are available\n");
		वापस 0;
	पूर्ण

	chans = rvu_get_num_lbk_chans();
	अगर (chans < 0)
		वापस chans;

	vfs = pci_sriov_get_totalvfs(pdev);

	/* Limit VFs in हाल we have more VFs than LBK channels available. */
	अगर (vfs > chans)
		vfs = chans;

	अगर (!vfs)
		वापस 0;

	/* Save VFs number क्रम reference in VF पूर्णांकerrupts handlers.
	 * Since पूर्णांकerrupts might start arriving during SRIOV enablement
	 * ordinary API cannot be used to get number of enabled VFs.
	 */
	rvu->vfs = vfs;

	err = rvu_mbox_init(rvu, &rvu->afvf_wq_info, TYPE_AFVF, vfs,
			    rvu_afvf_mbox_handler, rvu_afvf_mbox_up_handler);
	अगर (err)
		वापस err;

	rvu_enable_afvf_पूर्णांकr(rvu);
	/* Make sure IRQs are enabled beक्रमe SRIOV. */
	mb();

	err = pci_enable_sriov(pdev, vfs);
	अगर (err) अणु
		rvu_disable_afvf_पूर्णांकr(rvu);
		rvu_mbox_destroy(&rvu->afvf_wq_info);
		वापस err;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम rvu_disable_sriov(काष्ठा rvu *rvu)
अणु
	rvu_disable_afvf_पूर्णांकr(rvu);
	rvu_mbox_destroy(&rvu->afvf_wq_info);
	pci_disable_sriov(rvu->pdev);
पूर्ण

अटल व्योम rvu_update_module_params(काष्ठा rvu *rvu)
अणु
	स्थिर अक्षर *शेष_pfl_name = "default";

	strscpy(rvu->mkex_pfl_name,
		mkex_profile ? mkex_profile : शेष_pfl_name, MKEX_NAME_LEN);
पूर्ण

अटल पूर्णांक rvu_probe(काष्ठा pci_dev *pdev, स्थिर काष्ठा pci_device_id *id)
अणु
	काष्ठा device *dev = &pdev->dev;
	काष्ठा rvu *rvu;
	पूर्णांक    err;

	rvu = devm_kzalloc(dev, माप(*rvu), GFP_KERNEL);
	अगर (!rvu)
		वापस -ENOMEM;

	rvu->hw = devm_kzalloc(dev, माप(काष्ठा rvu_hwinfo), GFP_KERNEL);
	अगर (!rvu->hw) अणु
		devm_kमुक्त(dev, rvu);
		वापस -ENOMEM;
	पूर्ण

	pci_set_drvdata(pdev, rvu);
	rvu->pdev = pdev;
	rvu->dev = &pdev->dev;

	err = pci_enable_device(pdev);
	अगर (err) अणु
		dev_err(dev, "Failed to enable PCI device\n");
		जाओ err_मुक्तmem;
	पूर्ण

	err = pci_request_regions(pdev, DRV_NAME);
	अगर (err) अणु
		dev_err(dev, "PCI request regions failed 0x%x\n", err);
		जाओ err_disable_device;
	पूर्ण

	err = dma_set_mask_and_coherent(dev, DMA_BIT_MASK(48));
	अगर (err) अणु
		dev_err(dev, "DMA mask config failed, abort\n");
		जाओ err_release_regions;
	पूर्ण

	pci_set_master(pdev);

	rvu->ptp = ptp_get();
	अगर (IS_ERR(rvu->ptp)) अणु
		err = PTR_ERR(rvu->ptp);
		अगर (err == -EPROBE_DEFER)
			जाओ err_release_regions;
		rvu->ptp = शून्य;
	पूर्ण

	/* Map Admin function CSRs */
	rvu->afreg_base = pcim_iomap(pdev, PCI_AF_REG_BAR_NUM, 0);
	rvu->pfreg_base = pcim_iomap(pdev, PCI_PF_REG_BAR_NUM, 0);
	अगर (!rvu->afreg_base || !rvu->pfreg_base) अणु
		dev_err(dev, "Unable to map admin function CSRs, aborting\n");
		err = -ENOMEM;
		जाओ err_put_ptp;
	पूर्ण

	/* Store module params in rvu काष्ठाure */
	rvu_update_module_params(rvu);

	/* Check which blocks the HW supports */
	rvu_check_block_implemented(rvu);

	rvu_reset_all_blocks(rvu);

	rvu_setup_hw_capabilities(rvu);

	err = rvu_setup_hw_resources(rvu);
	अगर (err)
		जाओ err_put_ptp;

	/* Init mailbox btw AF and PFs */
	err = rvu_mbox_init(rvu, &rvu->afpf_wq_info, TYPE_AFPF,
			    rvu->hw->total_pfs, rvu_afpf_mbox_handler,
			    rvu_afpf_mbox_up_handler);
	अगर (err)
		जाओ err_hwsetup;

	err = rvu_flr_init(rvu);
	अगर (err)
		जाओ err_mbox;

	err = rvu_रेजिस्टर_पूर्णांकerrupts(rvu);
	अगर (err)
		जाओ err_flr;

	err = rvu_रेजिस्टर_dl(rvu);
	अगर (err)
		जाओ err_irq;

	rvu_setup_rvum_blk_revid(rvu);

	/* Enable AF's VFs (अगर any) */
	err = rvu_enable_sriov(rvu);
	अगर (err)
		जाओ err_dl;

	/* Initialize debugfs */
	rvu_dbg_init(rvu);

	वापस 0;
err_dl:
	rvu_unरेजिस्टर_dl(rvu);
err_irq:
	rvu_unरेजिस्टर_पूर्णांकerrupts(rvu);
err_flr:
	rvu_flr_wq_destroy(rvu);
err_mbox:
	rvu_mbox_destroy(&rvu->afpf_wq_info);
err_hwsetup:
	rvu_cgx_निकास(rvu);
	rvu_fwdata_निकास(rvu);
	rvu_reset_all_blocks(rvu);
	rvu_मुक्त_hw_resources(rvu);
	rvu_clear_rvum_blk_revid(rvu);
err_put_ptp:
	ptp_put(rvu->ptp);
err_release_regions:
	pci_release_regions(pdev);
err_disable_device:
	pci_disable_device(pdev);
err_मुक्तmem:
	pci_set_drvdata(pdev, शून्य);
	devm_kमुक्त(&pdev->dev, rvu->hw);
	devm_kमुक्त(dev, rvu);
	वापस err;
पूर्ण

अटल व्योम rvu_हटाओ(काष्ठा pci_dev *pdev)
अणु
	काष्ठा rvu *rvu = pci_get_drvdata(pdev);

	rvu_dbg_निकास(rvu);
	rvu_unरेजिस्टर_dl(rvu);
	rvu_unरेजिस्टर_पूर्णांकerrupts(rvu);
	rvu_flr_wq_destroy(rvu);
	rvu_cgx_निकास(rvu);
	rvu_fwdata_निकास(rvu);
	rvu_mbox_destroy(&rvu->afpf_wq_info);
	rvu_disable_sriov(rvu);
	rvu_reset_all_blocks(rvu);
	rvu_मुक्त_hw_resources(rvu);
	rvu_clear_rvum_blk_revid(rvu);
	ptp_put(rvu->ptp);
	pci_release_regions(pdev);
	pci_disable_device(pdev);
	pci_set_drvdata(pdev, शून्य);

	devm_kमुक्त(&pdev->dev, rvu->hw);
	devm_kमुक्त(&pdev->dev, rvu);
पूर्ण

अटल काष्ठा pci_driver rvu_driver = अणु
	.name = DRV_NAME,
	.id_table = rvu_id_table,
	.probe = rvu_probe,
	.हटाओ = rvu_हटाओ,
पूर्ण;

अटल पूर्णांक __init rvu_init_module(व्योम)
अणु
	पूर्णांक err;

	pr_info("%s: %s\n", DRV_NAME, DRV_STRING);

	err = pci_रेजिस्टर_driver(&cgx_driver);
	अगर (err < 0)
		वापस err;

	err = pci_रेजिस्टर_driver(&ptp_driver);
	अगर (err < 0)
		जाओ ptp_err;

	err =  pci_रेजिस्टर_driver(&rvu_driver);
	अगर (err < 0)
		जाओ rvu_err;

	वापस 0;
rvu_err:
	pci_unरेजिस्टर_driver(&ptp_driver);
ptp_err:
	pci_unरेजिस्टर_driver(&cgx_driver);

	वापस err;
पूर्ण

अटल व्योम __निकास rvu_cleanup_module(व्योम)
अणु
	pci_unरेजिस्टर_driver(&rvu_driver);
	pci_unरेजिस्टर_driver(&ptp_driver);
	pci_unरेजिस्टर_driver(&cgx_driver);
पूर्ण

module_init(rvu_init_module);
module_निकास(rvu_cleanup_module);
