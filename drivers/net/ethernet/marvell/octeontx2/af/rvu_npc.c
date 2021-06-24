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

#समावेश <linux/bitfield.h>
#समावेश <linux/module.h>
#समावेश <linux/pci.h>

#समावेश "rvu_struct.h"
#समावेश "rvu_reg.h"
#समावेश "rvu.h"
#समावेश "npc.h"
#समावेश "cgx.h"
#समावेश "npc_profile.h"

#घोषणा RSVD_MCAM_ENTRIES_PER_PF	2 /* Bcast & Promisc */
#घोषणा RSVD_MCAM_ENTRIES_PER_NIXLF	1 /* Ucast क्रम LFs */

#घोषणा NPC_PARSE_RESULT_DMAC_OFFSET	8
#घोषणा NPC_HW_TSTAMP_OFFSET		8
#घोषणा NPC_KEX_CHAN_MASK		0xFFFULL
#घोषणा NPC_KEX_PF_FUNC_MASK		0xFFFFULL

अटल स्थिर अक्षर def_pfl_name[] = "default";

अटल व्योम npc_mcam_मुक्त_all_entries(काष्ठा rvu *rvu, काष्ठा npc_mcam *mcam,
				      पूर्णांक blkaddr, u16 pcअगरunc);
अटल व्योम npc_mcam_मुक्त_all_counters(काष्ठा rvu *rvu, काष्ठा npc_mcam *mcam,
				       u16 pcअगरunc);

bool is_npc_पूर्णांकf_tx(u8 पूर्णांकf)
अणु
	वापस !!(पूर्णांकf & 0x1);
पूर्ण

bool is_npc_पूर्णांकf_rx(u8 पूर्णांकf)
अणु
	वापस !(पूर्णांकf & 0x1);
पूर्ण

bool is_npc_पूर्णांकerface_valid(काष्ठा rvu *rvu, u8 पूर्णांकf)
अणु
	काष्ठा rvu_hwinfo *hw = rvu->hw;

	वापस पूर्णांकf < hw->npc_पूर्णांकfs;
पूर्ण

पूर्णांक rvu_npc_get_tx_nibble_cfg(काष्ठा rvu *rvu, u64 nibble_ena)
अणु
	/* Due to a HW issue in these silicon versions, parse nibble enable
	 * configuration has to be identical क्रम both Rx and Tx पूर्णांकerfaces.
	 */
	अगर (is_rvu_96xx_B0(rvu))
		वापस nibble_ena;
	वापस 0;
पूर्ण

अटल पूर्णांक npc_mcam_verअगरy_pf_func(काष्ठा rvu *rvu,
				   काष्ठा mcam_entry *entry_data, u8 पूर्णांकf,
				   u16 pcअगरunc)
अणु
	u16 pf_func, pf_func_mask;

	अगर (is_npc_पूर्णांकf_rx(पूर्णांकf))
		वापस 0;

	pf_func_mask = (entry_data->kw_mask[0] >> 32) &
		NPC_KEX_PF_FUNC_MASK;
	pf_func = (entry_data->kw[0] >> 32) & NPC_KEX_PF_FUNC_MASK;

	pf_func = be16_to_cpu((__क्रमce __be16)pf_func);
	अगर (pf_func_mask != NPC_KEX_PF_FUNC_MASK ||
	    ((pf_func & ~RVU_PFVF_FUNC_MASK) !=
	     (pcअगरunc & ~RVU_PFVF_FUNC_MASK)))
		वापस -EINVAL;

	वापस 0;
पूर्ण

पूर्णांक npc_mcam_verअगरy_channel(काष्ठा rvu *rvu, u16 pcअगरunc, u8 पूर्णांकf, u16 channel)
अणु
	पूर्णांक pf = rvu_get_pf(pcअगरunc);
	u8 cgx_id, lmac_id;
	पूर्णांक base = 0, end;

	अगर (is_npc_पूर्णांकf_tx(पूर्णांकf))
		वापस 0;

	/* वापस in हाल of AF installed rules */
	अगर (is_pffunc_af(pcअगरunc))
		वापस 0;

	अगर (is_afvf(pcअगरunc)) अणु
		end = rvu_get_num_lbk_chans();
		अगर (end < 0)
			वापस -EINVAL;
	पूर्ण अन्यथा अणु
		rvu_get_cgx_lmac_id(rvu->pf2cgxlmac_map[pf], &cgx_id, &lmac_id);
		base = rvu_nix_chan_cgx(rvu, cgx_id, lmac_id, 0x0);
		/* CGX mapped functions has maximum of 16 channels */
		end = rvu_nix_chan_cgx(rvu, cgx_id, lmac_id, 0xF);
	पूर्ण

	अगर (channel < base || channel > end)
		वापस -EINVAL;

	वापस 0;
पूर्ण

व्योम rvu_npc_set_pkind(काष्ठा rvu *rvu, पूर्णांक pkind, काष्ठा rvu_pfvf *pfvf)
अणु
	पूर्णांक blkaddr;
	u64 val = 0;

	blkaddr = rvu_get_blkaddr(rvu, BLKTYPE_NPC, 0);
	अगर (blkaddr < 0)
		वापस;

	/* Config CPI base क्रम the PKIND */
	val = pkind | 1ULL << 62;
	rvu_ग_लिखो64(rvu, blkaddr, NPC_AF_PKINDX_CPI_DEFX(pkind, 0), val);
पूर्ण

पूर्णांक rvu_npc_get_pkind(काष्ठा rvu *rvu, u16 pf)
अणु
	काष्ठा npc_pkind *pkind = &rvu->hw->pkind;
	u32 map;
	पूर्णांक i;

	क्रम (i = 0; i < pkind->rsrc.max; i++) अणु
		map = pkind->pfchan_map[i];
		अगर (((map >> 16) & 0x3F) == pf)
			वापस i;
	पूर्ण
	वापस -1;
पूर्ण

#घोषणा NPC_AF_ACTION0_PTR_ADVANCE	GENMASK_ULL(27, 20)

पूर्णांक npc_config_ts_kpuaction(काष्ठा rvu *rvu, पूर्णांक pf, u16 pcअगरunc, bool enable)
अणु
	पूर्णांक pkind, blkaddr;
	u64 val;

	pkind = rvu_npc_get_pkind(rvu, pf);
	अगर (pkind < 0) अणु
		dev_err(rvu->dev, "%s: pkind not mapped\n", __func__);
		वापस -EINVAL;
	पूर्ण

	blkaddr = rvu_get_blkaddr(rvu, BLKTYPE_NPC, pcअगरunc);
	अगर (blkaddr < 0) अणु
		dev_err(rvu->dev, "%s: NPC block not implemented\n", __func__);
		वापस -EINVAL;
	पूर्ण

	val = rvu_पढ़ो64(rvu, blkaddr, NPC_AF_PKINDX_ACTION0(pkind));
	val &= ~NPC_AF_ACTION0_PTR_ADVANCE;
	/* If बारtamp is enabled then configure NPC to shअगरt 8 bytes */
	अगर (enable)
		val |= FIELD_PREP(NPC_AF_ACTION0_PTR_ADVANCE,
				  NPC_HW_TSTAMP_OFFSET);
	rvu_ग_लिखो64(rvu, blkaddr, NPC_AF_PKINDX_ACTION0(pkind), val);

	वापस 0;
पूर्ण

अटल पूर्णांक npc_get_ucast_mcam_index(काष्ठा npc_mcam *mcam, u16 pcअगरunc,
				    पूर्णांक nixlf)
अणु
	काष्ठा rvu_hwinfo *hw = container_of(mcam, काष्ठा rvu_hwinfo, mcam);
	काष्ठा rvu *rvu = hw->rvu;
	पूर्णांक blkaddr = 0, max = 0;
	काष्ठा rvu_block *block;
	काष्ठा rvu_pfvf *pfvf;

	pfvf = rvu_get_pfvf(rvu, pcअगरunc);
	/* Given a PF/VF and NIX LF number calculate the unicast mcam
	 * entry index based on the NIX block asचिन्हित to the PF/VF.
	 */
	blkaddr = rvu_get_next_nix_blkaddr(rvu, blkaddr);
	जबतक (blkaddr) अणु
		अगर (pfvf->nix_blkaddr == blkaddr)
			अवरोध;
		block = &rvu->hw->block[blkaddr];
		max += block->lf.max;
		blkaddr = rvu_get_next_nix_blkaddr(rvu, blkaddr);
	पूर्ण

	वापस mcam->nixlf_offset + (max + nixlf) * RSVD_MCAM_ENTRIES_PER_NIXLF;
पूर्ण

पूर्णांक npc_get_nixlf_mcam_index(काष्ठा npc_mcam *mcam,
			     u16 pcअगरunc, पूर्णांक nixlf, पूर्णांक type)
अणु
	पूर्णांक pf = rvu_get_pf(pcअगरunc);
	पूर्णांक index;

	/* Check अगर this is क्रम a PF */
	अगर (pf && !(pcअगरunc & RVU_PFVF_FUNC_MASK)) अणु
		/* Reserved entries exclude PF0 */
		pf--;
		index = mcam->pf_offset + (pf * RSVD_MCAM_ENTRIES_PER_PF);
		/* Broadcast address matching entry should be first so
		 * that the packet can be replicated to all VFs.
		 */
		अगर (type == NIXLF_BCAST_ENTRY)
			वापस index;
		अन्यथा अगर (type == NIXLF_PROMISC_ENTRY)
			वापस index + 1;
	पूर्ण

	वापस npc_get_ucast_mcam_index(mcam, pcअगरunc, nixlf);
पूर्ण

पूर्णांक npc_get_bank(काष्ठा npc_mcam *mcam, पूर्णांक index)
अणु
	पूर्णांक bank = index / mcam->banksize;

	/* 0,1 & 2,3 banks are combined क्रम this keysize */
	अगर (mcam->keysize == NPC_MCAM_KEY_X2)
		वापस bank ? 2 : 0;

	वापस bank;
पूर्ण

bool is_mcam_entry_enabled(काष्ठा rvu *rvu, काष्ठा npc_mcam *mcam,
			   पूर्णांक blkaddr, पूर्णांक index)
अणु
	पूर्णांक bank = npc_get_bank(mcam, index);
	u64 cfg;

	index &= (mcam->banksize - 1);
	cfg = rvu_पढ़ो64(rvu, blkaddr, NPC_AF_MCAMEX_BANKX_CFG(index, bank));
	वापस (cfg & 1);
पूर्ण

व्योम npc_enable_mcam_entry(काष्ठा rvu *rvu, काष्ठा npc_mcam *mcam,
			   पूर्णांक blkaddr, पूर्णांक index, bool enable)
अणु
	पूर्णांक bank = npc_get_bank(mcam, index);
	पूर्णांक actbank = bank;

	index &= (mcam->banksize - 1);
	क्रम (; bank < (actbank + mcam->banks_per_entry); bank++) अणु
		rvu_ग_लिखो64(rvu, blkaddr,
			    NPC_AF_MCAMEX_BANKX_CFG(index, bank),
			    enable ? 1 : 0);
	पूर्ण
पूर्ण

अटल व्योम npc_clear_mcam_entry(काष्ठा rvu *rvu, काष्ठा npc_mcam *mcam,
				 पूर्णांक blkaddr, पूर्णांक index)
अणु
	पूर्णांक bank = npc_get_bank(mcam, index);
	पूर्णांक actbank = bank;

	index &= (mcam->banksize - 1);
	क्रम (; bank < (actbank + mcam->banks_per_entry); bank++) अणु
		rvu_ग_लिखो64(rvu, blkaddr,
			    NPC_AF_MCAMEX_BANKX_CAMX_INTF(index, bank, 1), 0);
		rvu_ग_लिखो64(rvu, blkaddr,
			    NPC_AF_MCAMEX_BANKX_CAMX_INTF(index, bank, 0), 0);

		rvu_ग_लिखो64(rvu, blkaddr,
			    NPC_AF_MCAMEX_BANKX_CAMX_W0(index, bank, 1), 0);
		rvu_ग_लिखो64(rvu, blkaddr,
			    NPC_AF_MCAMEX_BANKX_CAMX_W0(index, bank, 0), 0);

		rvu_ग_लिखो64(rvu, blkaddr,
			    NPC_AF_MCAMEX_BANKX_CAMX_W1(index, bank, 1), 0);
		rvu_ग_लिखो64(rvu, blkaddr,
			    NPC_AF_MCAMEX_BANKX_CAMX_W1(index, bank, 0), 0);
	पूर्ण
पूर्ण

अटल व्योम npc_get_keyword(काष्ठा mcam_entry *entry, पूर्णांक idx,
			    u64 *cam0, u64 *cam1)
अणु
	u64 kw_mask = 0x00;

#घोषणा CAM_MASK(n)	(BIT_ULL(n) - 1)

	/* 0, 2, 4, 6 indices refer to BANKX_CAMX_W0 and
	 * 1, 3, 5, 7 indices refer to BANKX_CAMX_W1.
	 *
	 * Also, only 48 bits of BANKX_CAMX_W1 are valid.
	 */
	चयन (idx) अणु
	हाल 0:
		/* BANK(X)_CAM_W0<63:0> = MCAM_KEY[KW0]<63:0> */
		*cam1 = entry->kw[0];
		kw_mask = entry->kw_mask[0];
		अवरोध;
	हाल 1:
		/* BANK(X)_CAM_W1<47:0> = MCAM_KEY[KW1]<47:0> */
		*cam1 = entry->kw[1] & CAM_MASK(48);
		kw_mask = entry->kw_mask[1] & CAM_MASK(48);
		अवरोध;
	हाल 2:
		/* BANK(X + 1)_CAM_W0<15:0> = MCAM_KEY[KW1]<63:48>
		 * BANK(X + 1)_CAM_W0<63:16> = MCAM_KEY[KW2]<47:0>
		 */
		*cam1 = (entry->kw[1] >> 48) & CAM_MASK(16);
		*cam1 |= ((entry->kw[2] & CAM_MASK(48)) << 16);
		kw_mask = (entry->kw_mask[1] >> 48) & CAM_MASK(16);
		kw_mask |= ((entry->kw_mask[2] & CAM_MASK(48)) << 16);
		अवरोध;
	हाल 3:
		/* BANK(X + 1)_CAM_W1<15:0> = MCAM_KEY[KW2]<63:48>
		 * BANK(X + 1)_CAM_W1<47:16> = MCAM_KEY[KW3]<31:0>
		 */
		*cam1 = (entry->kw[2] >> 48) & CAM_MASK(16);
		*cam1 |= ((entry->kw[3] & CAM_MASK(32)) << 16);
		kw_mask = (entry->kw_mask[2] >> 48) & CAM_MASK(16);
		kw_mask |= ((entry->kw_mask[3] & CAM_MASK(32)) << 16);
		अवरोध;
	हाल 4:
		/* BANK(X + 2)_CAM_W0<31:0> = MCAM_KEY[KW3]<63:32>
		 * BANK(X + 2)_CAM_W0<63:32> = MCAM_KEY[KW4]<31:0>
		 */
		*cam1 = (entry->kw[3] >> 32) & CAM_MASK(32);
		*cam1 |= ((entry->kw[4] & CAM_MASK(32)) << 32);
		kw_mask = (entry->kw_mask[3] >> 32) & CAM_MASK(32);
		kw_mask |= ((entry->kw_mask[4] & CAM_MASK(32)) << 32);
		अवरोध;
	हाल 5:
		/* BANK(X + 2)_CAM_W1<31:0> = MCAM_KEY[KW4]<63:32>
		 * BANK(X + 2)_CAM_W1<47:32> = MCAM_KEY[KW5]<15:0>
		 */
		*cam1 = (entry->kw[4] >> 32) & CAM_MASK(32);
		*cam1 |= ((entry->kw[5] & CAM_MASK(16)) << 32);
		kw_mask = (entry->kw_mask[4] >> 32) & CAM_MASK(32);
		kw_mask |= ((entry->kw_mask[5] & CAM_MASK(16)) << 32);
		अवरोध;
	हाल 6:
		/* BANK(X + 3)_CAM_W0<47:0> = MCAM_KEY[KW5]<63:16>
		 * BANK(X + 3)_CAM_W0<63:48> = MCAM_KEY[KW6]<15:0>
		 */
		*cam1 = (entry->kw[5] >> 16) & CAM_MASK(48);
		*cam1 |= ((entry->kw[6] & CAM_MASK(16)) << 48);
		kw_mask = (entry->kw_mask[5] >> 16) & CAM_MASK(48);
		kw_mask |= ((entry->kw_mask[6] & CAM_MASK(16)) << 48);
		अवरोध;
	हाल 7:
		/* BANK(X + 3)_CAM_W1<47:0> = MCAM_KEY[KW6]<63:16> */
		*cam1 = (entry->kw[6] >> 16) & CAM_MASK(48);
		kw_mask = (entry->kw_mask[6] >> 16) & CAM_MASK(48);
		अवरोध;
	पूर्ण

	*cam1 &= kw_mask;
	*cam0 = ~*cam1 & kw_mask;
पूर्ण

अटल व्योम npc_fill_entryword(काष्ठा mcam_entry *entry, पूर्णांक idx,
			       u64 cam0, u64 cam1)
अणु
	/* Similar to npc_get_keyword, but fills mcam_entry काष्ठाure from
	 * CAM रेजिस्टरs.
	 */
	चयन (idx) अणु
	हाल 0:
		entry->kw[0] = cam1;
		entry->kw_mask[0] = cam1 ^ cam0;
		अवरोध;
	हाल 1:
		entry->kw[1] = cam1;
		entry->kw_mask[1] = cam1 ^ cam0;
		अवरोध;
	हाल 2:
		entry->kw[1] |= (cam1 & CAM_MASK(16)) << 48;
		entry->kw[2] = (cam1 >> 16) & CAM_MASK(48);
		entry->kw_mask[1] |= ((cam1 ^ cam0) & CAM_MASK(16)) << 48;
		entry->kw_mask[2] = ((cam1 ^ cam0) >> 16) & CAM_MASK(48);
		अवरोध;
	हाल 3:
		entry->kw[2] |= (cam1 & CAM_MASK(16)) << 48;
		entry->kw[3] = (cam1 >> 16) & CAM_MASK(32);
		entry->kw_mask[2] |= ((cam1 ^ cam0) & CAM_MASK(16)) << 48;
		entry->kw_mask[3] = ((cam1 ^ cam0) >> 16) & CAM_MASK(32);
		अवरोध;
	हाल 4:
		entry->kw[3] |= (cam1 & CAM_MASK(32)) << 32;
		entry->kw[4] = (cam1 >> 32) & CAM_MASK(32);
		entry->kw_mask[3] |= ((cam1 ^ cam0) & CAM_MASK(32)) << 32;
		entry->kw_mask[4] = ((cam1 ^ cam0) >> 32) & CAM_MASK(32);
		अवरोध;
	हाल 5:
		entry->kw[4] |= (cam1 & CAM_MASK(32)) << 32;
		entry->kw[5] = (cam1 >> 32) & CAM_MASK(16);
		entry->kw_mask[4] |= ((cam1 ^ cam0) & CAM_MASK(32)) << 32;
		entry->kw_mask[5] = ((cam1 ^ cam0) >> 32) & CAM_MASK(16);
		अवरोध;
	हाल 6:
		entry->kw[5] |= (cam1 & CAM_MASK(48)) << 16;
		entry->kw[6] = (cam1 >> 48) & CAM_MASK(16);
		entry->kw_mask[5] |= ((cam1 ^ cam0) & CAM_MASK(48)) << 16;
		entry->kw_mask[6] = ((cam1 ^ cam0) >> 48) & CAM_MASK(16);
		अवरोध;
	हाल 7:
		entry->kw[6] |= (cam1 & CAM_MASK(48)) << 16;
		entry->kw_mask[6] |= ((cam1 ^ cam0) & CAM_MASK(48)) << 16;
		अवरोध;
	पूर्ण
पूर्ण

अटल व्योम npc_get_शेष_entry_action(काष्ठा rvu *rvu, काष्ठा npc_mcam *mcam,
					 पूर्णांक blkaddr, पूर्णांक index,
					 काष्ठा mcam_entry *entry)
अणु
	u16 owner, target_func;
	काष्ठा rvu_pfvf *pfvf;
	पूर्णांक bank, nixlf;
	u64 rx_action;

	owner = mcam->entry2pfvf_map[index];
	target_func = (entry->action >> 4) & 0xffff;
	/* वापस inहाल target is PF or LBK or rule owner is not PF */
	अगर (is_afvf(target_func) || (owner & RVU_PFVF_FUNC_MASK) ||
	    !(target_func & RVU_PFVF_FUNC_MASK))
		वापस;

	pfvf = rvu_get_pfvf(rvu, target_func);
	mcam->entry2target_pffunc[index] = target_func;
	/* वापस अगर nixlf is not attached or initialized */
	अगर (!is_nixlf_attached(rvu, target_func) || !pfvf->def_ucast_rule)
		वापस;

	/* get VF ucast entry rule */
	nix_get_nixlf(rvu, target_func, &nixlf, शून्य);
	index = npc_get_nixlf_mcam_index(mcam, target_func,
					 nixlf, NIXLF_UCAST_ENTRY);
	bank = npc_get_bank(mcam, index);
	index &= (mcam->banksize - 1);

	rx_action = rvu_पढ़ो64(rvu, blkaddr,
			       NPC_AF_MCAMEX_BANKX_ACTION(index, bank));
	अगर (rx_action)
		entry->action = rx_action;
पूर्ण

अटल व्योम npc_config_mcam_entry(काष्ठा rvu *rvu, काष्ठा npc_mcam *mcam,
				  पूर्णांक blkaddr, पूर्णांक index, u8 पूर्णांकf,
				  काष्ठा mcam_entry *entry, bool enable)
अणु
	पूर्णांक bank = npc_get_bank(mcam, index);
	पूर्णांक kw = 0, actbank, actindex;
	u64 cam0, cam1;

	actbank = bank; /* Save bank id, to set action later on */
	actindex = index;
	index &= (mcam->banksize - 1);

	/* Disable beक्रमe mcam entry update */
	npc_enable_mcam_entry(rvu, mcam, blkaddr, actindex, false);

	/* Clear mcam entry to aव्योम ग_लिखोs being suppressed by NPC */
	npc_clear_mcam_entry(rvu, mcam, blkaddr, actindex);

	/* CAM1 takes the comparison value and
	 * CAM0 specअगरies match क्रम a bit in key being '0' or '1' or 'dontcare'.
	 * CAM1<n> = 0 & CAM0<n> = 1 => match अगर key<n> = 0
	 * CAM1<n> = 1 & CAM0<n> = 0 => match अगर key<n> = 1
	 * CAM1<n> = 0 & CAM0<n> = 0 => always match i.e करोntcare.
	 */
	क्रम (; bank < (actbank + mcam->banks_per_entry); bank++, kw = kw + 2) अणु
		/* Interface should be set in all banks */
		rvu_ग_लिखो64(rvu, blkaddr,
			    NPC_AF_MCAMEX_BANKX_CAMX_INTF(index, bank, 1),
			    पूर्णांकf);
		rvu_ग_लिखो64(rvu, blkaddr,
			    NPC_AF_MCAMEX_BANKX_CAMX_INTF(index, bank, 0),
			    ~पूर्णांकf & 0x3);

		/* Set the match key */
		npc_get_keyword(entry, kw, &cam0, &cam1);
		rvu_ग_लिखो64(rvu, blkaddr,
			    NPC_AF_MCAMEX_BANKX_CAMX_W0(index, bank, 1), cam1);
		rvu_ग_लिखो64(rvu, blkaddr,
			    NPC_AF_MCAMEX_BANKX_CAMX_W0(index, bank, 0), cam0);

		npc_get_keyword(entry, kw + 1, &cam0, &cam1);
		rvu_ग_लिखो64(rvu, blkaddr,
			    NPC_AF_MCAMEX_BANKX_CAMX_W1(index, bank, 1), cam1);
		rvu_ग_लिखो64(rvu, blkaddr,
			    NPC_AF_MCAMEX_BANKX_CAMX_W1(index, bank, 0), cam0);
	पूर्ण

	/* copy VF शेष entry action to the VF mcam entry */
	अगर (पूर्णांकf == NIX_INTF_RX && actindex < mcam->bmap_entries)
		npc_get_शेष_entry_action(rvu, mcam, blkaddr, actindex,
					     entry);

	/* Set 'action' */
	rvu_ग_लिखो64(rvu, blkaddr,
		    NPC_AF_MCAMEX_BANKX_ACTION(index, actbank), entry->action);

	/* Set TAG 'action' */
	rvu_ग_लिखो64(rvu, blkaddr, NPC_AF_MCAMEX_BANKX_TAG_ACT(index, actbank),
		    entry->vtag_action);

	/* Enable the entry */
	अगर (enable)
		npc_enable_mcam_entry(rvu, mcam, blkaddr, actindex, true);
पूर्ण

व्योम npc_पढ़ो_mcam_entry(काष्ठा rvu *rvu, काष्ठा npc_mcam *mcam,
			 पूर्णांक blkaddr, u16 src,
			 काष्ठा mcam_entry *entry, u8 *पूर्णांकf, u8 *ena)
अणु
	पूर्णांक sbank = npc_get_bank(mcam, src);
	पूर्णांक bank, kw = 0;
	u64 cam0, cam1;

	src &= (mcam->banksize - 1);
	bank = sbank;

	क्रम (; bank < (sbank + mcam->banks_per_entry); bank++, kw = kw + 2) अणु
		cam1 = rvu_पढ़ो64(rvu, blkaddr,
				  NPC_AF_MCAMEX_BANKX_CAMX_W0(src, bank, 1));
		cam0 = rvu_पढ़ो64(rvu, blkaddr,
				  NPC_AF_MCAMEX_BANKX_CAMX_W0(src, bank, 0));
		npc_fill_entryword(entry, kw, cam0, cam1);

		cam1 = rvu_पढ़ो64(rvu, blkaddr,
				  NPC_AF_MCAMEX_BANKX_CAMX_W1(src, bank, 1));
		cam0 = rvu_पढ़ो64(rvu, blkaddr,
				  NPC_AF_MCAMEX_BANKX_CAMX_W1(src, bank, 0));
		npc_fill_entryword(entry, kw + 1, cam0, cam1);
	पूर्ण

	entry->action = rvu_पढ़ो64(rvu, blkaddr,
				   NPC_AF_MCAMEX_BANKX_ACTION(src, sbank));
	entry->vtag_action =
		rvu_पढ़ो64(rvu, blkaddr,
			   NPC_AF_MCAMEX_BANKX_TAG_ACT(src, sbank));
	*पूर्णांकf = rvu_पढ़ो64(rvu, blkaddr,
			   NPC_AF_MCAMEX_BANKX_CAMX_INTF(src, sbank, 1)) & 3;
	*ena = rvu_पढ़ो64(rvu, blkaddr,
			  NPC_AF_MCAMEX_BANKX_CFG(src, sbank)) & 1;
पूर्ण

अटल व्योम npc_copy_mcam_entry(काष्ठा rvu *rvu, काष्ठा npc_mcam *mcam,
				पूर्णांक blkaddr, u16 src, u16 dest)
अणु
	पूर्णांक dbank = npc_get_bank(mcam, dest);
	पूर्णांक sbank = npc_get_bank(mcam, src);
	u64 cfg, sreg, dreg;
	पूर्णांक bank, i;

	src &= (mcam->banksize - 1);
	dest &= (mcam->banksize - 1);

	/* Copy INTF's, W0's, W1's CAM0 and CAM1 configuration */
	क्रम (bank = 0; bank < mcam->banks_per_entry; bank++) अणु
		sreg = NPC_AF_MCAMEX_BANKX_CAMX_INTF(src, sbank + bank, 0);
		dreg = NPC_AF_MCAMEX_BANKX_CAMX_INTF(dest, dbank + bank, 0);
		क्रम (i = 0; i < 6; i++) अणु
			cfg = rvu_पढ़ो64(rvu, blkaddr, sreg + (i * 8));
			rvu_ग_लिखो64(rvu, blkaddr, dreg + (i * 8), cfg);
		पूर्ण
	पूर्ण

	/* Copy action */
	cfg = rvu_पढ़ो64(rvu, blkaddr,
			 NPC_AF_MCAMEX_BANKX_ACTION(src, sbank));
	rvu_ग_लिखो64(rvu, blkaddr,
		    NPC_AF_MCAMEX_BANKX_ACTION(dest, dbank), cfg);

	/* Copy TAG action */
	cfg = rvu_पढ़ो64(rvu, blkaddr,
			 NPC_AF_MCAMEX_BANKX_TAG_ACT(src, sbank));
	rvu_ग_लिखो64(rvu, blkaddr,
		    NPC_AF_MCAMEX_BANKX_TAG_ACT(dest, dbank), cfg);

	/* Enable or disable */
	cfg = rvu_पढ़ो64(rvu, blkaddr,
			 NPC_AF_MCAMEX_BANKX_CFG(src, sbank));
	rvu_ग_लिखो64(rvu, blkaddr,
		    NPC_AF_MCAMEX_BANKX_CFG(dest, dbank), cfg);
पूर्ण

अटल u64 npc_get_mcam_action(काष्ठा rvu *rvu, काष्ठा npc_mcam *mcam,
			       पूर्णांक blkaddr, पूर्णांक index)
अणु
	पूर्णांक bank = npc_get_bank(mcam, index);

	index &= (mcam->banksize - 1);
	वापस rvu_पढ़ो64(rvu, blkaddr,
			  NPC_AF_MCAMEX_BANKX_ACTION(index, bank));
पूर्ण

व्योम rvu_npc_install_ucast_entry(काष्ठा rvu *rvu, u16 pcअगरunc,
				 पूर्णांक nixlf, u64 chan, u8 *mac_addr)
अणु
	काष्ठा rvu_pfvf *pfvf = rvu_get_pfvf(rvu, pcअगरunc);
	काष्ठा npc_install_flow_req req = अणु 0 पूर्ण;
	काष्ठा npc_install_flow_rsp rsp = अणु 0 पूर्ण;
	काष्ठा npc_mcam *mcam = &rvu->hw->mcam;
	काष्ठा nix_rx_action action;
	पूर्णांक blkaddr, index;

	/* AF's VFs work in promiscuous mode */
	अगर (is_afvf(pcअगरunc))
		वापस;

	blkaddr = rvu_get_blkaddr(rvu, BLKTYPE_NPC, 0);
	अगर (blkaddr < 0)
		वापस;

	index = npc_get_nixlf_mcam_index(mcam, pcअगरunc,
					 nixlf, NIXLF_UCAST_ENTRY);

	/* Don't change the action अगर entry is alपढ़ोy enabled
	 * Otherwise RSS action may get overwritten.
	 */
	अगर (is_mcam_entry_enabled(rvu, mcam, blkaddr, index)) अणु
		*(u64 *)&action = npc_get_mcam_action(rvu, mcam,
						      blkaddr, index);
	पूर्ण अन्यथा अणु
		*(u64 *)&action = 0x00;
		action.op = NIX_RX_ACTIONOP_UCAST;
		action.pf_func = pcअगरunc;
	पूर्ण

	req.शेष_rule = 1;
	ether_addr_copy(req.packet.dmac, mac_addr);
	eth_broadcast_addr((u8 *)&req.mask.dmac);
	req.features = BIT_ULL(NPC_DMAC);
	req.channel = chan;
	req.पूर्णांकf = pfvf->nix_rx_पूर्णांकf;
	req.op = action.op;
	req.hdr.pcअगरunc = 0; /* AF is requester */
	req.vf = action.pf_func;
	req.index = action.index;
	req.match_id = action.match_id;
	req.flow_key_alg = action.flow_key_alg;

	rvu_mbox_handler_npc_install_flow(rvu, &req, &rsp);
पूर्ण

व्योम rvu_npc_install_promisc_entry(काष्ठा rvu *rvu, u16 pcअगरunc,
				   पूर्णांक nixlf, u64 chan, u8 chan_cnt,
				   bool allmulti)
अणु
	काष्ठा rvu_pfvf *pfvf = rvu_get_pfvf(rvu, pcअगरunc);
	काष्ठा npc_install_flow_req req = अणु 0 पूर्ण;
	काष्ठा npc_install_flow_rsp rsp = अणु 0 पूर्ण;
	काष्ठा npc_mcam *mcam = &rvu->hw->mcam;
	पूर्णांक blkaddr, ucast_idx, index;
	u8 mac_addr[ETH_ALEN] = अणु 0 पूर्ण;
	काष्ठा nix_rx_action action;
	u64 relaxed_mask;

	/* Only PF or AF VF can add a promiscuous entry */
	अगर ((pcअगरunc & RVU_PFVF_FUNC_MASK) && !is_afvf(pcअगरunc))
		वापस;

	blkaddr = rvu_get_blkaddr(rvu, BLKTYPE_NPC, 0);
	अगर (blkaddr < 0)
		वापस;

	*(u64 *)&action = 0x00;
	index = npc_get_nixlf_mcam_index(mcam, pcअगरunc,
					 nixlf, NIXLF_PROMISC_ENTRY);

	/* If the corresponding PF's ucast action is RSS,
	 * use the same action क्रम promisc also
	 */
	ucast_idx = npc_get_nixlf_mcam_index(mcam, pcअगरunc,
					     nixlf, NIXLF_UCAST_ENTRY);
	अगर (is_mcam_entry_enabled(rvu, mcam, blkaddr, ucast_idx))
		*(u64 *)&action = npc_get_mcam_action(rvu, mcam,
							blkaddr, ucast_idx);

	अगर (action.op != NIX_RX_ACTIONOP_RSS) अणु
		*(u64 *)&action = 0x00;
		action.op = NIX_RX_ACTIONOP_UCAST;
		action.pf_func = pcअगरunc;
	पूर्ण

	अगर (allmulti) अणु
		mac_addr[0] = 0x01;	/* LSB bit of 1st byte in DMAC */
		ether_addr_copy(req.packet.dmac, mac_addr);
		ether_addr_copy(req.mask.dmac, mac_addr);
		req.features = BIT_ULL(NPC_DMAC);
	पूर्ण

	req.chan_mask = 0xFFFU;
	अगर (chan_cnt > 1) अणु
		अगर (!is_घातer_of_2(chan_cnt)) अणु
			dev_err(rvu->dev,
				"%s: channel count more than 1, must be power of 2\n", __func__);
			वापस;
		पूर्ण
		relaxed_mask = GENMASK_ULL(BITS_PER_LONG_LONG - 1,
					   ilog2(chan_cnt));
		req.chan_mask &= relaxed_mask;
	पूर्ण

	req.channel = chan;
	req.पूर्णांकf = pfvf->nix_rx_पूर्णांकf;
	req.entry = index;
	req.op = action.op;
	req.hdr.pcअगरunc = 0; /* AF is requester */
	req.vf = pcअगरunc;
	req.index = action.index;
	req.match_id = action.match_id;
	req.flow_key_alg = action.flow_key_alg;

	rvu_mbox_handler_npc_install_flow(rvu, &req, &rsp);
पूर्ण

अटल व्योम npc_enadis_promisc_entry(काष्ठा rvu *rvu, u16 pcअगरunc,
				     पूर्णांक nixlf, bool enable)
अणु
	काष्ठा npc_mcam *mcam = &rvu->hw->mcam;
	पूर्णांक blkaddr, index;

	blkaddr = rvu_get_blkaddr(rvu, BLKTYPE_NPC, 0);
	अगर (blkaddr < 0)
		वापस;

	/* Only PF's have a promiscuous entry */
	अगर (pcअगरunc & RVU_PFVF_FUNC_MASK)
		वापस;

	index = npc_get_nixlf_mcam_index(mcam, pcअगरunc,
					 nixlf, NIXLF_PROMISC_ENTRY);
	npc_enable_mcam_entry(rvu, mcam, blkaddr, index, enable);
पूर्ण

व्योम rvu_npc_disable_promisc_entry(काष्ठा rvu *rvu, u16 pcअगरunc, पूर्णांक nixlf)
अणु
	npc_enadis_promisc_entry(rvu, pcअगरunc, nixlf, false);
पूर्ण

व्योम rvu_npc_enable_promisc_entry(काष्ठा rvu *rvu, u16 pcअगरunc, पूर्णांक nixlf)
अणु
	npc_enadis_promisc_entry(rvu, pcअगरunc, nixlf, true);
पूर्ण

व्योम rvu_npc_install_bcast_match_entry(काष्ठा rvu *rvu, u16 pcअगरunc,
				       पूर्णांक nixlf, u64 chan)
अणु
	काष्ठा rvu_pfvf *pfvf;
	काष्ठा npc_install_flow_req req = अणु 0 पूर्ण;
	काष्ठा npc_install_flow_rsp rsp = अणु 0 पूर्ण;
	काष्ठा npc_mcam *mcam = &rvu->hw->mcam;
	काष्ठा rvu_hwinfo *hw = rvu->hw;
	पूर्णांक blkaddr, index;
	u32 req_index = 0;
	u8 op;

	blkaddr = rvu_get_blkaddr(rvu, BLKTYPE_NPC, 0);
	अगर (blkaddr < 0)
		वापस;

	/* Skip LBK VFs */
	अगर (is_afvf(pcअगरunc))
		वापस;

	/* If pkt replication is not supported,
	 * then only PF is allowed to add a bcast match entry.
	 */
	अगर (!hw->cap.nix_rx_multicast && pcअगरunc & RVU_PFVF_FUNC_MASK)
		वापस;

	/* Get 'pcifunc' of PF device */
	pcअगरunc = pcअगरunc & ~RVU_PFVF_FUNC_MASK;
	pfvf = rvu_get_pfvf(rvu, pcअगरunc);
	index = npc_get_nixlf_mcam_index(mcam, pcअगरunc,
					 nixlf, NIXLF_BCAST_ENTRY);

	अगर (!hw->cap.nix_rx_multicast) अणु
		/* Early silicon करोesn't support pkt replication,
		 * so install entry with UCAST action, so that PF
		 * receives all broadcast packets.
		 */
		op = NIX_RX_ACTIONOP_UCAST;
	पूर्ण अन्यथा अणु
		op = NIX_RX_ACTIONOP_MCAST;
		req_index = pfvf->bcast_mce_idx;
	पूर्ण

	eth_broadcast_addr((u8 *)&req.packet.dmac);
	eth_broadcast_addr((u8 *)&req.mask.dmac);
	req.features = BIT_ULL(NPC_DMAC);
	req.channel = chan;
	req.पूर्णांकf = pfvf->nix_rx_पूर्णांकf;
	req.entry = index;
	req.op = op;
	req.hdr.pcअगरunc = 0; /* AF is requester */
	req.vf = pcअगरunc;
	req.index = req_index;

	rvu_mbox_handler_npc_install_flow(rvu, &req, &rsp);
पूर्ण

व्योम rvu_npc_enable_bcast_entry(काष्ठा rvu *rvu, u16 pcअगरunc, bool enable)
अणु
	काष्ठा npc_mcam *mcam = &rvu->hw->mcam;
	पूर्णांक blkaddr, index;

	blkaddr = rvu_get_blkaddr(rvu, BLKTYPE_NPC, 0);
	अगर (blkaddr < 0)
		वापस;

	/* Get 'pcifunc' of PF device */
	pcअगरunc = pcअगरunc & ~RVU_PFVF_FUNC_MASK;

	index = npc_get_nixlf_mcam_index(mcam, pcअगरunc, 0, NIXLF_BCAST_ENTRY);
	npc_enable_mcam_entry(rvu, mcam, blkaddr, index, enable);
पूर्ण

अटल व्योम npc_update_vf_flow_entry(काष्ठा rvu *rvu, काष्ठा npc_mcam *mcam,
				     पूर्णांक blkaddr, u16 pcअगरunc, u64 rx_action)
अणु
	पूर्णांक actindex, index, bank;
	bool enable;

	अगर (!(pcअगरunc & RVU_PFVF_FUNC_MASK))
		वापस;

	mutex_lock(&mcam->lock);
	क्रम (index = 0; index < mcam->bmap_entries; index++) अणु
		अगर (mcam->entry2target_pffunc[index] == pcअगरunc) अणु
			bank = npc_get_bank(mcam, index);
			actindex = index;
			index &= (mcam->banksize - 1);

			/* पढ़ो vf flow entry enable status */
			enable = is_mcam_entry_enabled(rvu, mcam, blkaddr,
						       actindex);
			/* disable beक्रमe mcam entry update */
			npc_enable_mcam_entry(rvu, mcam, blkaddr, actindex,
					      false);
			/* update 'action' */
			rvu_ग_लिखो64(rvu, blkaddr,
				    NPC_AF_MCAMEX_BANKX_ACTION(index, bank),
				    rx_action);
			अगर (enable)
				npc_enable_mcam_entry(rvu, mcam, blkaddr,
						      actindex, true);
		पूर्ण
	पूर्ण
	mutex_unlock(&mcam->lock);
पूर्ण

व्योम rvu_npc_update_flowkey_alg_idx(काष्ठा rvu *rvu, u16 pcअगरunc, पूर्णांक nixlf,
				    पूर्णांक group, पूर्णांक alg_idx, पूर्णांक mcam_index)
अणु
	काष्ठा npc_mcam *mcam = &rvu->hw->mcam;
	काष्ठा nix_rx_action action;
	पूर्णांक blkaddr, index, bank;
	काष्ठा rvu_pfvf *pfvf;

	blkaddr = rvu_get_blkaddr(rvu, BLKTYPE_NPC, 0);
	अगर (blkaddr < 0)
		वापस;

	/* Check अगर this is क्रम reserved शेष entry */
	अगर (mcam_index < 0) अणु
		अगर (group != DEFAULT_RSS_CONTEXT_GROUP)
			वापस;
		index = npc_get_nixlf_mcam_index(mcam, pcअगरunc,
						 nixlf, NIXLF_UCAST_ENTRY);
	पूर्ण अन्यथा अणु
		/* TODO: validate this mcam index */
		index = mcam_index;
	पूर्ण

	अगर (index >= mcam->total_entries)
		वापस;

	bank = npc_get_bank(mcam, index);
	index &= (mcam->banksize - 1);

	*(u64 *)&action = rvu_पढ़ो64(rvu, blkaddr,
				     NPC_AF_MCAMEX_BANKX_ACTION(index, bank));
	/* Ignore अगर no action was set earlier */
	अगर (!*(u64 *)&action)
		वापस;

	action.op = NIX_RX_ACTIONOP_RSS;
	action.pf_func = pcअगरunc;
	action.index = group;
	action.flow_key_alg = alg_idx;

	rvu_ग_लिखो64(rvu, blkaddr,
		    NPC_AF_MCAMEX_BANKX_ACTION(index, bank), *(u64 *)&action);

	/* update the VF flow rule action with the VF शेष entry action */
	अगर (mcam_index < 0)
		npc_update_vf_flow_entry(rvu, mcam, blkaddr, pcअगरunc,
					 *(u64 *)&action);

	/* update the action change in शेष rule */
	pfvf = rvu_get_pfvf(rvu, pcअगरunc);
	अगर (pfvf->def_ucast_rule)
		pfvf->def_ucast_rule->rx_action = action;

	index = npc_get_nixlf_mcam_index(mcam, pcअगरunc,
					 nixlf, NIXLF_PROMISC_ENTRY);

	/* If PF's promiscuous entry is enabled,
	 * Set RSS action क्रम that entry as well
	 */
	अगर (is_mcam_entry_enabled(rvu, mcam, blkaddr, index)) अणु
		bank = npc_get_bank(mcam, index);
		index &= (mcam->banksize - 1);

		rvu_ग_लिखो64(rvu, blkaddr,
			    NPC_AF_MCAMEX_BANKX_ACTION(index, bank),
			    *(u64 *)&action);
	पूर्ण
पूर्ण

अटल व्योम npc_enadis_शेष_entries(काष्ठा rvu *rvu, u16 pcअगरunc,
				       पूर्णांक nixlf, bool enable)
अणु
	काष्ठा npc_mcam *mcam = &rvu->hw->mcam;
	काष्ठा nix_rx_action action;
	पूर्णांक index, bank, blkaddr;

	blkaddr = rvu_get_blkaddr(rvu, BLKTYPE_NPC, 0);
	अगर (blkaddr < 0)
		वापस;

	/* Ucast MCAM match entry of this PF/VF */
	index = npc_get_nixlf_mcam_index(mcam, pcअगरunc,
					 nixlf, NIXLF_UCAST_ENTRY);
	npc_enable_mcam_entry(rvu, mcam, blkaddr, index, enable);

	/* For PF, ena/dis promisc and bcast MCAM match entries.
	 * For VFs add/delete from bcast list when RX multicast
	 * feature is present.
	 */
	अगर (pcअगरunc & RVU_PFVF_FUNC_MASK && !rvu->hw->cap.nix_rx_multicast)
		वापस;

	/* For bcast, enable/disable only अगर it's action is not
	 * packet replication, inहाल अगर action is replication
	 * then this PF/VF's nixlf is हटाओd from bcast replication
	 * list.
	 */
	index = npc_get_nixlf_mcam_index(mcam, pcअगरunc & ~RVU_PFVF_FUNC_MASK,
					 nixlf, NIXLF_BCAST_ENTRY);
	bank = npc_get_bank(mcam, index);
	*(u64 *)&action = rvu_पढ़ो64(rvu, blkaddr,
	     NPC_AF_MCAMEX_BANKX_ACTION(index & (mcam->banksize - 1), bank));

	/* VFs will not have BCAST entry */
	अगर (action.op != NIX_RX_ACTIONOP_MCAST &&
	    !(pcअगरunc & RVU_PFVF_FUNC_MASK)) अणु
		npc_enable_mcam_entry(rvu, mcam,
				      blkaddr, index, enable);
	पूर्ण अन्यथा अणु
		nix_update_bcast_mce_list(rvu, pcअगरunc, enable);
		/* Enable PF's BCAST entry क्रम packet replication */
		rvu_npc_enable_bcast_entry(rvu, pcअगरunc, enable);
	पूर्ण

	अगर (enable)
		rvu_npc_enable_promisc_entry(rvu, pcअगरunc, nixlf);
	अन्यथा
		rvu_npc_disable_promisc_entry(rvu, pcअगरunc, nixlf);
पूर्ण

व्योम rvu_npc_disable_शेष_entries(काष्ठा rvu *rvu, u16 pcअगरunc, पूर्णांक nixlf)
अणु
	npc_enadis_शेष_entries(rvu, pcअगरunc, nixlf, false);
पूर्ण

व्योम rvu_npc_enable_शेष_entries(काष्ठा rvu *rvu, u16 pcअगरunc, पूर्णांक nixlf)
अणु
	npc_enadis_शेष_entries(rvu, pcअगरunc, nixlf, true);
पूर्ण

व्योम rvu_npc_disable_mcam_entries(काष्ठा rvu *rvu, u16 pcअगरunc, पूर्णांक nixlf)
अणु
	काष्ठा rvu_pfvf *pfvf = rvu_get_pfvf(rvu, pcअगरunc);
	काष्ठा npc_mcam *mcam = &rvu->hw->mcam;
	काष्ठा rvu_npc_mcam_rule *rule, *पंचांगp;
	पूर्णांक blkaddr;

	blkaddr = rvu_get_blkaddr(rvu, BLKTYPE_NPC, 0);
	अगर (blkaddr < 0)
		वापस;

	mutex_lock(&mcam->lock);

	/* Disable MCAM entries directing traffic to this 'pcifunc' */
	list_क्रम_each_entry_safe(rule, पंचांगp, &mcam->mcam_rules, list) अणु
		अगर (is_npc_पूर्णांकf_rx(rule->पूर्णांकf) &&
		    rule->rx_action.pf_func == pcअगरunc) अणु
			npc_enable_mcam_entry(rvu, mcam, blkaddr,
					      rule->entry, false);
			rule->enable = false;
			/* Indicate that शेष rule is disabled */
			अगर (rule->शेष_rule) अणु
				pfvf->def_ucast_rule = शून्य;
				list_del(&rule->list);
				kमुक्त(rule);
			पूर्ण
		पूर्ण
	पूर्ण

	mutex_unlock(&mcam->lock);

	npc_mcam_disable_flows(rvu, pcअगरunc);

	rvu_npc_disable_शेष_entries(rvu, pcअगरunc, nixlf);
पूर्ण

व्योम rvu_npc_मुक्त_mcam_entries(काष्ठा rvu *rvu, u16 pcअगरunc, पूर्णांक nixlf)
अणु
	काष्ठा npc_mcam *mcam = &rvu->hw->mcam;
	काष्ठा rvu_npc_mcam_rule *rule, *पंचांगp;
	पूर्णांक blkaddr;

	blkaddr = rvu_get_blkaddr(rvu, BLKTYPE_NPC, 0);
	अगर (blkaddr < 0)
		वापस;

	mutex_lock(&mcam->lock);

	/* Free all MCAM entries owned by this 'pcifunc' */
	npc_mcam_मुक्त_all_entries(rvu, mcam, blkaddr, pcअगरunc);

	/* Free all MCAM counters owned by this 'pcifunc' */
	npc_mcam_मुक्त_all_counters(rvu, mcam, pcअगरunc);

	/* Delete MCAM entries owned by this 'pcifunc' */
	list_क्रम_each_entry_safe(rule, पंचांगp, &mcam->mcam_rules, list) अणु
		अगर (rule->owner == pcअगरunc && !rule->शेष_rule) अणु
			list_del(&rule->list);
			kमुक्त(rule);
		पूर्ण
	पूर्ण

	mutex_unlock(&mcam->lock);

	rvu_npc_disable_शेष_entries(rvu, pcअगरunc, nixlf);
पूर्ण

#घोषणा SET_KEX_LD(पूर्णांकf, lid, ltype, ld, cfg)	\
	rvu_ग_लिखो64(rvu, blkaddr,			\
		NPC_AF_INTFX_LIDX_LTX_LDX_CFG(पूर्णांकf, lid, ltype, ld), cfg)

#घोषणा SET_KEX_LDFLAGS(पूर्णांकf, ld, flags, cfg)	\
	rvu_ग_लिखो64(rvu, blkaddr,			\
		NPC_AF_INTFX_LDATAX_FLAGSX_CFG(पूर्णांकf, ld, flags), cfg)

अटल व्योम npc_program_mkex_rx(काष्ठा rvu *rvu, पूर्णांक blkaddr,
				काष्ठा npc_mcam_kex *mkex, u8 पूर्णांकf)
अणु
	पूर्णांक lid, lt, ld, fl;

	अगर (is_npc_पूर्णांकf_tx(पूर्णांकf))
		वापस;

	rvu_ग_लिखो64(rvu, blkaddr, NPC_AF_INTFX_KEX_CFG(पूर्णांकf),
		    mkex->keyx_cfg[NIX_INTF_RX]);

	/* Program LDATA */
	क्रम (lid = 0; lid < NPC_MAX_LID; lid++) अणु
		क्रम (lt = 0; lt < NPC_MAX_LT; lt++) अणु
			क्रम (ld = 0; ld < NPC_MAX_LD; ld++)
				SET_KEX_LD(पूर्णांकf, lid, lt, ld,
					   mkex->पूर्णांकf_lid_lt_ld[NIX_INTF_RX]
					   [lid][lt][ld]);
		पूर्ण
	पूर्ण
	/* Program LFLAGS */
	क्रम (ld = 0; ld < NPC_MAX_LD; ld++) अणु
		क्रम (fl = 0; fl < NPC_MAX_LFL; fl++)
			SET_KEX_LDFLAGS(पूर्णांकf, ld, fl,
					mkex->पूर्णांकf_ld_flags[NIX_INTF_RX]
					[ld][fl]);
	पूर्ण
पूर्ण

अटल व्योम npc_program_mkex_tx(काष्ठा rvu *rvu, पूर्णांक blkaddr,
				काष्ठा npc_mcam_kex *mkex, u8 पूर्णांकf)
अणु
	पूर्णांक lid, lt, ld, fl;

	अगर (is_npc_पूर्णांकf_rx(पूर्णांकf))
		वापस;

	rvu_ग_लिखो64(rvu, blkaddr, NPC_AF_INTFX_KEX_CFG(पूर्णांकf),
		    mkex->keyx_cfg[NIX_INTF_TX]);

	/* Program LDATA */
	क्रम (lid = 0; lid < NPC_MAX_LID; lid++) अणु
		क्रम (lt = 0; lt < NPC_MAX_LT; lt++) अणु
			क्रम (ld = 0; ld < NPC_MAX_LD; ld++)
				SET_KEX_LD(पूर्णांकf, lid, lt, ld,
					   mkex->पूर्णांकf_lid_lt_ld[NIX_INTF_TX]
					   [lid][lt][ld]);
		पूर्ण
	पूर्ण
	/* Program LFLAGS */
	क्रम (ld = 0; ld < NPC_MAX_LD; ld++) अणु
		क्रम (fl = 0; fl < NPC_MAX_LFL; fl++)
			SET_KEX_LDFLAGS(पूर्णांकf, ld, fl,
					mkex->पूर्णांकf_ld_flags[NIX_INTF_TX]
					[ld][fl]);
	पूर्ण
पूर्ण

अटल व्योम npc_program_mkex_profile(काष्ठा rvu *rvu, पूर्णांक blkaddr,
				     काष्ठा npc_mcam_kex *mkex)
अणु
	काष्ठा rvu_hwinfo *hw = rvu->hw;
	u8 पूर्णांकf;
	पूर्णांक ld;

	क्रम (ld = 0; ld < NPC_MAX_LD; ld++)
		rvu_ग_लिखो64(rvu, blkaddr, NPC_AF_KEX_LDATAX_FLAGS_CFG(ld),
			    mkex->kex_ld_flags[ld]);

	क्रम (पूर्णांकf = 0; पूर्णांकf < hw->npc_पूर्णांकfs; पूर्णांकf++) अणु
		npc_program_mkex_rx(rvu, blkaddr, mkex, पूर्णांकf);
		npc_program_mkex_tx(rvu, blkaddr, mkex, पूर्णांकf);
	पूर्ण
पूर्ण

#घोषणा MKEX_END_SIGN  0xdeadbeef

अटल व्योम npc_load_mkex_profile(काष्ठा rvu *rvu, पूर्णांक blkaddr,
				  स्थिर अक्षर *mkex_profile)
अणु
	काष्ठा device *dev = &rvu->pdev->dev;
	काष्ठा npc_mcam_kex *mcam_kex;
	व्योम *mkex_prfl_addr = शून्य;
	u64 prfl_addr, prfl_sz;

	/* If user not selected mkex profile */
	अगर (!म_भेदन(mkex_profile, def_pfl_name, MKEX_NAME_LEN))
		जाओ program_mkex;

	अगर (!rvu->fwdata)
		जाओ program_mkex;
	prfl_addr = rvu->fwdata->mcam_addr;
	prfl_sz = rvu->fwdata->mcam_sz;

	अगर (!prfl_addr || !prfl_sz)
		जाओ program_mkex;

	mkex_prfl_addr = memremap(prfl_addr, prfl_sz, MEMREMAP_WC);
	अगर (!mkex_prfl_addr)
		जाओ program_mkex;

	mcam_kex = (काष्ठा npc_mcam_kex *)mkex_prfl_addr;

	जबतक (((s64)prfl_sz > 0) && (mcam_kex->mkex_sign != MKEX_END_SIGN)) अणु
		/* Compare with mkex mod_param name string */
		अगर (mcam_kex->mkex_sign == MKEX_SIGN &&
		    !म_भेदन(mcam_kex->name, mkex_profile, MKEX_NAME_LEN)) अणु
			/* Due to an errata (35786) in A0/B0 pass silicon,
			 * parse nibble enable configuration has to be
			 * identical क्रम both Rx and Tx पूर्णांकerfaces.
			 */
			अगर (!is_rvu_96xx_B0(rvu) ||
			    mcam_kex->keyx_cfg[NIX_INTF_RX] == mcam_kex->keyx_cfg[NIX_INTF_TX])
				rvu->kpu.mkex = mcam_kex;
			जाओ program_mkex;
		पूर्ण

		mcam_kex++;
		prfl_sz -= माप(काष्ठा npc_mcam_kex);
	पूर्ण
	dev_warn(dev, "Failed to load requested profile: %s\n", mkex_profile);

program_mkex:
	dev_info(rvu->dev, "Using %s mkex profile\n", rvu->kpu.mkex->name);
	/* Program selected mkex profile */
	npc_program_mkex_profile(rvu, blkaddr, rvu->kpu.mkex);
	अगर (mkex_prfl_addr)
		memunmap(mkex_prfl_addr);
पूर्ण

अटल व्योम npc_config_kpuaction(काष्ठा rvu *rvu, पूर्णांक blkaddr,
				 स्थिर काष्ठा npc_kpu_profile_action *kpuaction,
				 पूर्णांक kpu, पूर्णांक entry, bool pkind)
अणु
	काष्ठा npc_kpu_action0 action0 = अणु0पूर्ण;
	काष्ठा npc_kpu_action1 action1 = अणु0पूर्ण;
	u64 reg;

	action1.errlev = kpuaction->errlev;
	action1.errcode = kpuaction->errcode;
	action1.dp0_offset = kpuaction->dp0_offset;
	action1.dp1_offset = kpuaction->dp1_offset;
	action1.dp2_offset = kpuaction->dp2_offset;

	अगर (pkind)
		reg = NPC_AF_PKINDX_ACTION1(entry);
	अन्यथा
		reg = NPC_AF_KPUX_ENTRYX_ACTION1(kpu, entry);

	rvu_ग_लिखो64(rvu, blkaddr, reg, *(u64 *)&action1);

	action0.byp_count = kpuaction->bypass_count;
	action0.capture_ena = kpuaction->cap_ena;
	action0.parse_करोne = kpuaction->parse_करोne;
	action0.next_state = kpuaction->next_state;
	action0.capture_lid = kpuaction->lid;
	action0.capture_ltype = kpuaction->ltype;
	action0.capture_flags = kpuaction->flags;
	action0.ptr_advance = kpuaction->ptr_advance;
	action0.var_len_offset = kpuaction->offset;
	action0.var_len_mask = kpuaction->mask;
	action0.var_len_right = kpuaction->right;
	action0.var_len_shअगरt = kpuaction->shअगरt;

	अगर (pkind)
		reg = NPC_AF_PKINDX_ACTION0(entry);
	अन्यथा
		reg = NPC_AF_KPUX_ENTRYX_ACTION0(kpu, entry);

	rvu_ग_लिखो64(rvu, blkaddr, reg, *(u64 *)&action0);
पूर्ण

अटल व्योम npc_config_kpucam(काष्ठा rvu *rvu, पूर्णांक blkaddr,
			      स्थिर काष्ठा npc_kpu_profile_cam *kpucam,
			      पूर्णांक kpu, पूर्णांक entry)
अणु
	काष्ठा npc_kpu_cam cam0 = अणु0पूर्ण;
	काष्ठा npc_kpu_cam cam1 = अणु0पूर्ण;

	cam1.state = kpucam->state & kpucam->state_mask;
	cam1.dp0_data = kpucam->dp0 & kpucam->dp0_mask;
	cam1.dp1_data = kpucam->dp1 & kpucam->dp1_mask;
	cam1.dp2_data = kpucam->dp2 & kpucam->dp2_mask;

	cam0.state = ~kpucam->state & kpucam->state_mask;
	cam0.dp0_data = ~kpucam->dp0 & kpucam->dp0_mask;
	cam0.dp1_data = ~kpucam->dp1 & kpucam->dp1_mask;
	cam0.dp2_data = ~kpucam->dp2 & kpucam->dp2_mask;

	rvu_ग_लिखो64(rvu, blkaddr,
		    NPC_AF_KPUX_ENTRYX_CAMX(kpu, entry, 0), *(u64 *)&cam0);
	rvu_ग_लिखो64(rvu, blkaddr,
		    NPC_AF_KPUX_ENTRYX_CAMX(kpu, entry, 1), *(u64 *)&cam1);
पूर्ण

अटल अंतरभूत u64 enable_mask(पूर्णांक count)
अणु
	वापस (((count) < 64) ? ~(BIT_ULL(count) - 1) : (0x00ULL));
पूर्ण

अटल व्योम npc_program_kpu_profile(काष्ठा rvu *rvu, पूर्णांक blkaddr, पूर्णांक kpu,
				    स्थिर काष्ठा npc_kpu_profile *profile)
अणु
	पूर्णांक entry, num_entries, max_entries;

	अगर (profile->cam_entries != profile->action_entries) अणु
		dev_err(rvu->dev,
			"KPU%d: CAM and action entries [%d != %d] not equal\n",
			kpu, profile->cam_entries, profile->action_entries);
	पूर्ण

	max_entries = rvu->hw->npc_kpu_entries;

	/* Program CAM match entries क्रम previous KPU extracted data */
	num_entries = min_t(पूर्णांक, profile->cam_entries, max_entries);
	क्रम (entry = 0; entry < num_entries; entry++)
		npc_config_kpucam(rvu, blkaddr,
				  &profile->cam[entry], kpu, entry);

	/* Program this KPU's actions */
	num_entries = min_t(पूर्णांक, profile->action_entries, max_entries);
	क्रम (entry = 0; entry < num_entries; entry++)
		npc_config_kpuaction(rvu, blkaddr, &profile->action[entry],
				     kpu, entry, false);

	/* Enable all programmed entries */
	num_entries = min_t(पूर्णांक, profile->action_entries, profile->cam_entries);
	rvu_ग_लिखो64(rvu, blkaddr,
		    NPC_AF_KPUX_ENTRY_DISX(kpu, 0), enable_mask(num_entries));
	अगर (num_entries > 64) अणु
		rvu_ग_लिखो64(rvu, blkaddr,
			    NPC_AF_KPUX_ENTRY_DISX(kpu, 1),
			    enable_mask(num_entries - 64));
	पूर्ण

	/* Enable this KPU */
	rvu_ग_लिखो64(rvu, blkaddr, NPC_AF_KPUX_CFG(kpu), 0x01);
पूर्ण

अटल पूर्णांक npc_prepare_शेष_kpu(काष्ठा npc_kpu_profile_adapter *profile)
अणु
	profile->name = def_pfl_name;
	profile->version = NPC_KPU_PROखाता_VER;
	profile->ikpu = ikpu_action_entries;
	profile->pkinds = ARRAY_SIZE(ikpu_action_entries);
	profile->kpu = npc_kpu_profiles;
	profile->kpus = ARRAY_SIZE(npc_kpu_profiles);
	profile->lt_def = &npc_lt_शेषs;
	profile->mkex = &npc_mkex_शेष;

	वापस 0;
पूर्ण

अटल व्योम npc_load_kpu_profile(काष्ठा rvu *rvu)
अणु
	काष्ठा npc_kpu_profile_adapter *profile = &rvu->kpu;

	npc_prepare_शेष_kpu(profile);
पूर्ण

अटल व्योम npc_parser_profile_init(काष्ठा rvu *rvu, पूर्णांक blkaddr)
अणु
	काष्ठा rvu_hwinfo *hw = rvu->hw;
	पूर्णांक num_pkinds, num_kpus, idx;
	काष्ठा npc_pkind *pkind;

	/* Disable all KPUs and their entries */
	क्रम (idx = 0; idx < hw->npc_kpus; idx++) अणु
		rvu_ग_लिखो64(rvu, blkaddr,
			    NPC_AF_KPUX_ENTRY_DISX(idx, 0), ~0ULL);
		rvu_ग_लिखो64(rvu, blkaddr,
			    NPC_AF_KPUX_ENTRY_DISX(idx, 1), ~0ULL);
		rvu_ग_लिखो64(rvu, blkaddr, NPC_AF_KPUX_CFG(idx), 0x00);
	पूर्ण

	/* Load and customize KPU profile. */
	npc_load_kpu_profile(rvu);

	/* First program IKPU profile i.e PKIND configs.
	 * Check HW max count to aव्योम configuring junk or
	 * writing to unsupported CSR addresses.
	 */
	pkind = &hw->pkind;
	num_pkinds = rvu->kpu.pkinds;
	num_pkinds = min_t(पूर्णांक, pkind->rsrc.max, num_pkinds);

	क्रम (idx = 0; idx < num_pkinds; idx++)
		npc_config_kpuaction(rvu, blkaddr, &rvu->kpu.ikpu[idx], 0, idx, true);

	/* Program KPU CAM and Action profiles */
	num_kpus = rvu->kpu.kpus;
	num_kpus = min_t(पूर्णांक, hw->npc_kpus, num_kpus);

	क्रम (idx = 0; idx < num_kpus; idx++)
		npc_program_kpu_profile(rvu, blkaddr, idx, &rvu->kpu.kpu[idx]);
पूर्ण

अटल पूर्णांक npc_mcam_rsrcs_init(काष्ठा rvu *rvu, पूर्णांक blkaddr)
अणु
	पूर्णांक nixlf_count = rvu_get_nixlf_count(rvu);
	काष्ठा npc_mcam *mcam = &rvu->hw->mcam;
	पूर्णांक rsvd, err;
	u64 cfg;

	/* Actual number of MCAM entries vary by entry size */
	cfg = (rvu_पढ़ो64(rvu, blkaddr,
			  NPC_AF_INTFX_KEX_CFG(0)) >> 32) & 0x07;
	mcam->total_entries = (mcam->banks / BIT_ULL(cfg)) * mcam->banksize;
	mcam->keysize = cfg;

	/* Number of banks combined per MCAM entry */
	अगर (cfg == NPC_MCAM_KEY_X4)
		mcam->banks_per_entry = 4;
	अन्यथा अगर (cfg == NPC_MCAM_KEY_X2)
		mcam->banks_per_entry = 2;
	अन्यथा
		mcam->banks_per_entry = 1;

	/* Reserve one MCAM entry क्रम each of the NIX LF to
	 * guarantee space to install शेष matching DMAC rule.
	 * Also reserve 2 MCAM entries क्रम each PF क्रम शेष
	 * channel based matching or 'bcast & promisc' matching to
	 * support BCAST and PROMISC modes of operation क्रम PFs.
	 * PF0 is excluded.
	 */
	rsvd = (nixlf_count * RSVD_MCAM_ENTRIES_PER_NIXLF) +
		((rvu->hw->total_pfs - 1) * RSVD_MCAM_ENTRIES_PER_PF);
	अगर (mcam->total_entries <= rsvd) अणु
		dev_warn(rvu->dev,
			 "Insufficient NPC MCAM size %d for pkt I/O, exiting\n",
			 mcam->total_entries);
		वापस -ENOMEM;
	पूर्ण

	mcam->bmap_entries = mcam->total_entries - rsvd;
	mcam->nixlf_offset = mcam->bmap_entries;
	mcam->pf_offset = mcam->nixlf_offset + nixlf_count;

	/* Allocate biपंचांगaps क्रम managing MCAM entries */
	mcam->bmap = devm_kसुस्मृति(rvu->dev, BITS_TO_LONGS(mcam->bmap_entries),
				  माप(दीर्घ), GFP_KERNEL);
	अगर (!mcam->bmap)
		वापस -ENOMEM;

	mcam->bmap_reverse = devm_kसुस्मृति(rvu->dev,
					  BITS_TO_LONGS(mcam->bmap_entries),
					  माप(दीर्घ), GFP_KERNEL);
	अगर (!mcam->bmap_reverse)
		वापस -ENOMEM;

	mcam->bmap_fcnt = mcam->bmap_entries;

	/* Alloc memory क्रम saving entry to RVU PFFUNC allocation mapping */
	mcam->entry2pfvf_map = devm_kसुस्मृति(rvu->dev, mcam->bmap_entries,
					    माप(u16), GFP_KERNEL);
	अगर (!mcam->entry2pfvf_map)
		वापस -ENOMEM;

	/* Reserve 1/8th of MCAM entries at the bottom क्रम low priority
	 * allocations and another 1/8th at the top क्रम high priority
	 * allocations.
	 */
	mcam->lprio_count = mcam->bmap_entries / 8;
	अगर (mcam->lprio_count > BITS_PER_LONG)
		mcam->lprio_count = round_करोwn(mcam->lprio_count,
					       BITS_PER_LONG);
	mcam->lprio_start = mcam->bmap_entries - mcam->lprio_count;
	mcam->hprio_count = mcam->lprio_count;
	mcam->hprio_end = mcam->hprio_count;


	/* Allocate biपंचांगap क्रम managing MCAM counters and memory
	 * क्रम saving counter to RVU PFFUNC allocation mapping.
	 */
	err = rvu_alloc_biपंचांगap(&mcam->counters);
	अगर (err)
		वापस err;

	mcam->cntr2pfvf_map = devm_kसुस्मृति(rvu->dev, mcam->counters.max,
					   माप(u16), GFP_KERNEL);
	अगर (!mcam->cntr2pfvf_map)
		जाओ मुक्त_mem;

	/* Alloc memory क्रम MCAM entry to counter mapping and क्रम tracking
	 * counter's reference count.
	 */
	mcam->entry2cntr_map = devm_kसुस्मृति(rvu->dev, mcam->bmap_entries,
					    माप(u16), GFP_KERNEL);
	अगर (!mcam->entry2cntr_map)
		जाओ मुक्त_mem;

	mcam->cntr_refcnt = devm_kसुस्मृति(rvu->dev, mcam->counters.max,
					 माप(u16), GFP_KERNEL);
	अगर (!mcam->cntr_refcnt)
		जाओ मुक्त_mem;

	/* Alloc memory क्रम saving target device of mcam rule */
	mcam->entry2target_pffunc = devm_kसुस्मृति(rvu->dev, mcam->total_entries,
						 माप(u16), GFP_KERNEL);
	अगर (!mcam->entry2target_pffunc)
		जाओ मुक्त_mem;

	mutex_init(&mcam->lock);

	वापस 0;

मुक्त_mem:
	kमुक्त(mcam->counters.bmap);
	वापस -ENOMEM;
पूर्ण

अटल व्योम rvu_npc_hw_init(काष्ठा rvu *rvu, पूर्णांक blkaddr)
अणु
	काष्ठा npc_pkind *pkind = &rvu->hw->pkind;
	काष्ठा npc_mcam *mcam = &rvu->hw->mcam;
	काष्ठा rvu_hwinfo *hw = rvu->hw;
	u64 npc_स्थिर, npc_स्थिर1;
	u64 npc_स्थिर2 = 0;

	npc_स्थिर = rvu_पढ़ो64(rvu, blkaddr, NPC_AF_CONST);
	npc_स्थिर1 = rvu_पढ़ो64(rvu, blkaddr, NPC_AF_CONST1);
	अगर (npc_स्थिर1 & BIT_ULL(63))
		npc_स्थिर2 = rvu_पढ़ो64(rvu, blkaddr, NPC_AF_CONST2);

	pkind->rsrc.max = (npc_स्थिर1 >> 12) & 0xFFULL;
	hw->npc_kpu_entries = npc_स्थिर1 & 0xFFFULL;
	hw->npc_kpus = (npc_स्थिर >> 8) & 0x1FULL;
	hw->npc_पूर्णांकfs = npc_स्थिर & 0xFULL;
	hw->npc_counters = (npc_स्थिर >> 48) & 0xFFFFULL;

	mcam->banks = (npc_स्थिर >> 44) & 0xFULL;
	mcam->banksize = (npc_स्थिर >> 28) & 0xFFFFULL;
	/* Extended set */
	अगर (npc_स्थिर2) अणु
		hw->npc_ext_set = true;
		hw->npc_counters = (npc_स्थिर2 >> 16) & 0xFFFFULL;
		mcam->banksize = npc_स्थिर2 & 0xFFFFULL;
	पूर्ण

	mcam->counters.max = hw->npc_counters;
पूर्ण

अटल व्योम rvu_npc_setup_पूर्णांकerfaces(काष्ठा rvu *rvu, पूर्णांक blkaddr)
अणु
	काष्ठा npc_mcam *mcam = &rvu->hw->mcam;
	काष्ठा rvu_hwinfo *hw = rvu->hw;
	u64 nibble_ena, rx_kex, tx_kex;
	u8 पूर्णांकf;

	/* Reserve last counter क्रम MCAM RX miss action which is set to
	 * drop packet. This way we will know how many pkts didn't match
	 * any MCAM entry.
	 */
	mcam->counters.max--;
	mcam->rx_miss_act_cntr = mcam->counters.max;

	rx_kex = npc_mkex_शेष.keyx_cfg[NIX_INTF_RX];
	tx_kex = npc_mkex_शेष.keyx_cfg[NIX_INTF_TX];
	nibble_ena = FIELD_GET(NPC_PARSE_NIBBLE, rx_kex);

	nibble_ena = rvu_npc_get_tx_nibble_cfg(rvu, nibble_ena);
	अगर (nibble_ena) अणु
		tx_kex &= ~NPC_PARSE_NIBBLE;
		tx_kex |= FIELD_PREP(NPC_PARSE_NIBBLE, nibble_ena);
		npc_mkex_शेष.keyx_cfg[NIX_INTF_TX] = tx_kex;
	पूर्ण

	/* Configure RX पूर्णांकerfaces */
	क्रम (पूर्णांकf = 0; पूर्णांकf < hw->npc_पूर्णांकfs; पूर्णांकf++) अणु
		अगर (is_npc_पूर्णांकf_tx(पूर्णांकf))
			जारी;

		/* Set RX MCAM search key size. LA..LE (ltype only) + Channel */
		rvu_ग_लिखो64(rvu, blkaddr, NPC_AF_INTFX_KEX_CFG(पूर्णांकf),
			    rx_kex);

		/* If MCAM lookup करोesn't result in a match, drop the received
		 * packet. And map this action to a counter to count dropped
		 * packets.
		 */
		rvu_ग_लिखो64(rvu, blkaddr,
			    NPC_AF_INTFX_MISS_ACT(पूर्णांकf), NIX_RX_ACTIONOP_DROP);

		/* NPC_AF_INTFX_MISS_STAT_ACT[14:12] - counter[11:9]
		 * NPC_AF_INTFX_MISS_STAT_ACT[8:0] - counter[8:0]
		 */
		rvu_ग_लिखो64(rvu, blkaddr,
			    NPC_AF_INTFX_MISS_STAT_ACT(पूर्णांकf),
			    ((mcam->rx_miss_act_cntr >> 9) << 12) |
			    BIT_ULL(9) | mcam->rx_miss_act_cntr);
	पूर्ण

	/* Configure TX पूर्णांकerfaces */
	क्रम (पूर्णांकf = 0; पूर्णांकf < hw->npc_पूर्णांकfs; पूर्णांकf++) अणु
		अगर (is_npc_पूर्णांकf_rx(पूर्णांकf))
			जारी;

		/* Extract Ltypes LID_LA to LID_LE */
		rvu_ग_लिखो64(rvu, blkaddr, NPC_AF_INTFX_KEX_CFG(पूर्णांकf),
			    tx_kex);

		/* Set TX miss action to UCAST_DEFAULT i.e
		 * transmit the packet on NIX LF SQ's शेष channel.
		 */
		rvu_ग_लिखो64(rvu, blkaddr,
			    NPC_AF_INTFX_MISS_ACT(पूर्णांकf),
			    NIX_TX_ACTIONOP_UCAST_DEFAULT);
	पूर्ण
पूर्ण

पूर्णांक rvu_npc_init(काष्ठा rvu *rvu)
अणु
	काष्ठा npc_kpu_profile_adapter *kpu = &rvu->kpu;
	काष्ठा npc_pkind *pkind = &rvu->hw->pkind;
	काष्ठा npc_mcam *mcam = &rvu->hw->mcam;
	पूर्णांक blkaddr, entry, bank, err;

	blkaddr = rvu_get_blkaddr(rvu, BLKTYPE_NPC, 0);
	अगर (blkaddr < 0) अणु
		dev_err(rvu->dev, "%s: NPC block not implemented\n", __func__);
		वापस -ENODEV;
	पूर्ण

	rvu_npc_hw_init(rvu, blkaddr);

	/* First disable all MCAM entries, to stop traffic towards NIXLFs */
	क्रम (bank = 0; bank < mcam->banks; bank++) अणु
		क्रम (entry = 0; entry < mcam->banksize; entry++)
			rvu_ग_लिखो64(rvu, blkaddr,
				    NPC_AF_MCAMEX_BANKX_CFG(entry, bank), 0);
	पूर्ण

	err = rvu_alloc_biपंचांगap(&pkind->rsrc);
	अगर (err)
		वापस err;

	/* Allocate mem क्रम pkind to PF and channel mapping info */
	pkind->pfchan_map = devm_kसुस्मृति(rvu->dev, pkind->rsrc.max,
					 माप(u32), GFP_KERNEL);
	अगर (!pkind->pfchan_map)
		वापस -ENOMEM;

	/* Configure KPU profile */
	npc_parser_profile_init(rvu, blkaddr);

	/* Config Outer L2, IPv4's NPC layer info */
	rvu_ग_लिखो64(rvu, blkaddr, NPC_AF_PCK_DEF_OL2,
		    (kpu->lt_def->pck_ol2.lid << 8) | (kpu->lt_def->pck_ol2.ltype_match << 4) |
		    kpu->lt_def->pck_ol2.ltype_mask);
	rvu_ग_लिखो64(rvu, blkaddr, NPC_AF_PCK_DEF_OIP4,
		    (kpu->lt_def->pck_oip4.lid << 8) | (kpu->lt_def->pck_oip4.ltype_match << 4) |
		    kpu->lt_def->pck_oip4.ltype_mask);

	/* Config Inner IPV4 NPC layer info */
	rvu_ग_लिखो64(rvu, blkaddr, NPC_AF_PCK_DEF_IIP4,
		    (kpu->lt_def->pck_iip4.lid << 8) | (kpu->lt_def->pck_iip4.ltype_match << 4) |
		    kpu->lt_def->pck_iip4.ltype_mask);

	/* Enable below क्रम Rx pkts.
	 * - Outer IPv4 header checksum validation.
	 * - Detect outer L2 broadcast address and set NPC_RESULT_S[L2M].
	 * - Inner IPv4 header checksum validation.
	 * - Set non zero checksum error code value
	 */
	rvu_ग_लिखो64(rvu, blkaddr, NPC_AF_PCK_CFG,
		    rvu_पढ़ो64(rvu, blkaddr, NPC_AF_PCK_CFG) |
		    BIT_ULL(32) | BIT_ULL(24) | BIT_ULL(6) |
		    BIT_ULL(2) | BIT_ULL(1));

	rvu_npc_setup_पूर्णांकerfaces(rvu, blkaddr);

	/* Configure MKEX profile */
	npc_load_mkex_profile(rvu, blkaddr, rvu->mkex_pfl_name);

	err = npc_mcam_rsrcs_init(rvu, blkaddr);
	अगर (err)
		वापस err;

	err = npc_flow_steering_init(rvu, blkaddr);
	अगर (err) अणु
		dev_err(rvu->dev,
			"Incorrect mkex profile loaded using default mkex\n");
		npc_load_mkex_profile(rvu, blkaddr, def_pfl_name);
	पूर्ण

	वापस 0;
पूर्ण

व्योम rvu_npc_मुक्तmem(काष्ठा rvu *rvu)
अणु
	काष्ठा npc_pkind *pkind = &rvu->hw->pkind;
	काष्ठा npc_mcam *mcam = &rvu->hw->mcam;

	kमुक्त(pkind->rsrc.bmap);
	kमुक्त(mcam->counters.bmap);
	mutex_destroy(&mcam->lock);
पूर्ण

व्योम rvu_npc_get_mcam_entry_alloc_info(काष्ठा rvu *rvu, u16 pcअगरunc,
				       पूर्णांक blkaddr, पूर्णांक *alloc_cnt,
				       पूर्णांक *enable_cnt)
अणु
	काष्ठा npc_mcam *mcam = &rvu->hw->mcam;
	पूर्णांक entry;

	*alloc_cnt = 0;
	*enable_cnt = 0;

	क्रम (entry = 0; entry < mcam->bmap_entries; entry++) अणु
		अगर (mcam->entry2pfvf_map[entry] == pcअगरunc) अणु
			(*alloc_cnt)++;
			अगर (is_mcam_entry_enabled(rvu, mcam, blkaddr, entry))
				(*enable_cnt)++;
		पूर्ण
	पूर्ण
पूर्ण

व्योम rvu_npc_get_mcam_counter_alloc_info(काष्ठा rvu *rvu, u16 pcअगरunc,
					 पूर्णांक blkaddr, पूर्णांक *alloc_cnt,
					 पूर्णांक *enable_cnt)
अणु
	काष्ठा npc_mcam *mcam = &rvu->hw->mcam;
	पूर्णांक cntr;

	*alloc_cnt = 0;
	*enable_cnt = 0;

	क्रम (cntr = 0; cntr < mcam->counters.max; cntr++) अणु
		अगर (mcam->cntr2pfvf_map[cntr] == pcअगरunc) अणु
			(*alloc_cnt)++;
			अगर (mcam->cntr_refcnt[cntr])
				(*enable_cnt)++;
		पूर्ण
	पूर्ण
पूर्ण

अटल पूर्णांक npc_mcam_verअगरy_entry(काष्ठा npc_mcam *mcam,
				 u16 pcअगरunc, पूर्णांक entry)
अणु
	/* verअगरy AF installed entries */
	अगर (is_pffunc_af(pcअगरunc))
		वापस 0;
	/* Verअगरy अगर entry is valid and अगर it is indeed
	 * allocated to the requesting PFFUNC.
	 */
	अगर (entry >= mcam->bmap_entries)
		वापस NPC_MCAM_INVALID_REQ;

	अगर (pcअगरunc != mcam->entry2pfvf_map[entry])
		वापस NPC_MCAM_PERM_DENIED;

	वापस 0;
पूर्ण

अटल पूर्णांक npc_mcam_verअगरy_counter(काष्ठा npc_mcam *mcam,
				   u16 pcअगरunc, पूर्णांक cntr)
अणु
	/* Verअगरy अगर counter is valid and अगर it is indeed
	 * allocated to the requesting PFFUNC.
	 */
	अगर (cntr >= mcam->counters.max)
		वापस NPC_MCAM_INVALID_REQ;

	अगर (pcअगरunc != mcam->cntr2pfvf_map[cntr])
		वापस NPC_MCAM_PERM_DENIED;

	वापस 0;
पूर्ण

अटल व्योम npc_map_mcam_entry_and_cntr(काष्ठा rvu *rvu, काष्ठा npc_mcam *mcam,
					पूर्णांक blkaddr, u16 entry, u16 cntr)
अणु
	u16 index = entry & (mcam->banksize - 1);
	u16 bank = npc_get_bank(mcam, entry);

	/* Set mapping and increment counter's refcnt */
	mcam->entry2cntr_map[entry] = cntr;
	mcam->cntr_refcnt[cntr]++;
	/* Enable stats
	 * NPC_AF_MCAMEX_BANKX_STAT_ACT[14:12] - counter[11:9]
	 * NPC_AF_MCAMEX_BANKX_STAT_ACT[8:0] - counter[8:0]
	 */
	rvu_ग_लिखो64(rvu, blkaddr,
		    NPC_AF_MCAMEX_BANKX_STAT_ACT(index, bank),
		    ((cntr >> 9) << 12) | BIT_ULL(9) | cntr);
पूर्ण

अटल व्योम npc_unmap_mcam_entry_and_cntr(काष्ठा rvu *rvu,
					  काष्ठा npc_mcam *mcam,
					  पूर्णांक blkaddr, u16 entry, u16 cntr)
अणु
	u16 index = entry & (mcam->banksize - 1);
	u16 bank = npc_get_bank(mcam, entry);

	/* Remove mapping and reduce counter's refcnt */
	mcam->entry2cntr_map[entry] = NPC_MCAM_INVALID_MAP;
	mcam->cntr_refcnt[cntr]--;
	/* Disable stats */
	rvu_ग_लिखो64(rvu, blkaddr,
		    NPC_AF_MCAMEX_BANKX_STAT_ACT(index, bank), 0x00);
पूर्ण

/* Sets MCAM entry in biपंचांगap as used. Update
 * reverse biपंचांगap too. Should be called with
 * 'mcam->lock' held.
 */
अटल व्योम npc_mcam_set_bit(काष्ठा npc_mcam *mcam, u16 index)
अणु
	u16 entry, rentry;

	entry = index;
	rentry = mcam->bmap_entries - index - 1;

	__set_bit(entry, mcam->bmap);
	__set_bit(rentry, mcam->bmap_reverse);
	mcam->bmap_fcnt--;
पूर्ण

/* Sets MCAM entry in biपंचांगap as मुक्त. Update
 * reverse biपंचांगap too. Should be called with
 * 'mcam->lock' held.
 */
अटल व्योम npc_mcam_clear_bit(काष्ठा npc_mcam *mcam, u16 index)
अणु
	u16 entry, rentry;

	entry = index;
	rentry = mcam->bmap_entries - index - 1;

	__clear_bit(entry, mcam->bmap);
	__clear_bit(rentry, mcam->bmap_reverse);
	mcam->bmap_fcnt++;
पूर्ण

अटल व्योम npc_mcam_मुक्त_all_entries(काष्ठा rvu *rvu, काष्ठा npc_mcam *mcam,
				      पूर्णांक blkaddr, u16 pcअगरunc)
अणु
	u16 index, cntr;

	/* Scan all MCAM entries and मुक्त the ones mapped to 'pcifunc' */
	क्रम (index = 0; index < mcam->bmap_entries; index++) अणु
		अगर (mcam->entry2pfvf_map[index] == pcअगरunc) अणु
			mcam->entry2pfvf_map[index] = NPC_MCAM_INVALID_MAP;
			/* Free the entry in biपंचांगap */
			npc_mcam_clear_bit(mcam, index);
			/* Disable the entry */
			npc_enable_mcam_entry(rvu, mcam, blkaddr, index, false);

			/* Update entry2counter mapping */
			cntr = mcam->entry2cntr_map[index];
			अगर (cntr != NPC_MCAM_INVALID_MAP)
				npc_unmap_mcam_entry_and_cntr(rvu, mcam,
							      blkaddr, index,
							      cntr);
			mcam->entry2target_pffunc[index] = 0x0;
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम npc_mcam_मुक्त_all_counters(काष्ठा rvu *rvu, काष्ठा npc_mcam *mcam,
				       u16 pcअगरunc)
अणु
	u16 cntr;

	/* Scan all MCAM counters and मुक्त the ones mapped to 'pcifunc' */
	क्रम (cntr = 0; cntr < mcam->counters.max; cntr++) अणु
		अगर (mcam->cntr2pfvf_map[cntr] == pcअगरunc) अणु
			mcam->cntr2pfvf_map[cntr] = NPC_MCAM_INVALID_MAP;
			mcam->cntr_refcnt[cntr] = 0;
			rvu_मुक्त_rsrc(&mcam->counters, cntr);
			/* This API is expected to be called after मुक्तing
			 * MCAM entries, which पूर्णांकurn will हटाओ
			 * 'entry to counter' mapping.
			 * No need to करो it again.
			 */
		पूर्ण
	पूर्ण
पूर्ण

/* Find area of contiguous मुक्त entries of size 'nr'.
 * If not found वापस max contiguous मुक्त entries available.
 */
अटल u16 npc_mcam_find_zero_area(अचिन्हित दीर्घ *map, u16 size, u16 start,
				   u16 nr, u16 *max_area)
अणु
	u16 max_area_start = 0;
	u16 index, next, end;

	*max_area = 0;

again:
	index = find_next_zero_bit(map, size, start);
	अगर (index >= size)
		वापस max_area_start;

	end = ((index + nr) >= size) ? size : index + nr;
	next = find_next_bit(map, end, index);
	अगर (*max_area < (next - index)) अणु
		*max_area = next - index;
		max_area_start = index;
	पूर्ण

	अगर (next < end) अणु
		start = next + 1;
		जाओ again;
	पूर्ण

	वापस max_area_start;
पूर्ण

/* Find number of मुक्त MCAM entries available
 * within range i.e in between 'start' and 'end'.
 */
अटल u16 npc_mcam_get_मुक्त_count(अचिन्हित दीर्घ *map, u16 start, u16 end)
अणु
	u16 index, next;
	u16 fcnt = 0;

again:
	अगर (start >= end)
		वापस fcnt;

	index = find_next_zero_bit(map, end, start);
	अगर (index >= end)
		वापस fcnt;

	next = find_next_bit(map, end, index);
	अगर (next <= end) अणु
		fcnt += next - index;
		start = next + 1;
		जाओ again;
	पूर्ण

	fcnt += end - index;
	वापस fcnt;
पूर्ण

अटल व्योम
npc_get_mcam_search_range_priority(काष्ठा npc_mcam *mcam,
				   काष्ठा npc_mcam_alloc_entry_req *req,
				   u16 *start, u16 *end, bool *reverse)
अणु
	u16 fcnt;

	अगर (req->priority == NPC_MCAM_HIGHER_PRIO)
		जाओ hprio;

	/* For a low priority entry allocation
	 * - If reference entry is not in hprio zone then
	 *      search range: ref_entry to end.
	 * - If reference entry is in hprio zone and अगर
	 *   request can be accomodated in non-hprio zone then
	 *      search range: 'start of middle zone' to 'end'
	 * - अन्यथा search in reverse, so that less number of hprio
	 *   zone entries are allocated.
	 */

	*reverse = false;
	*start = req->ref_entry + 1;
	*end = mcam->bmap_entries;

	अगर (req->ref_entry >= mcam->hprio_end)
		वापस;

	fcnt = npc_mcam_get_मुक्त_count(mcam->bmap,
				       mcam->hprio_end, mcam->bmap_entries);
	अगर (fcnt > req->count)
		*start = mcam->hprio_end;
	अन्यथा
		*reverse = true;
	वापस;

hprio:
	/* For a high priority entry allocation, search is always
	 * in reverse to preserve hprio zone entries.
	 * - If reference entry is not in lprio zone then
	 *      search range: 0 to ref_entry.
	 * - If reference entry is in lprio zone and अगर
	 *   request can be accomodated in middle zone then
	 *      search range: 'hprio_end' to 'lprio_start'
	 */

	*reverse = true;
	*start = 0;
	*end = req->ref_entry;

	अगर (req->ref_entry <= mcam->lprio_start)
		वापस;

	fcnt = npc_mcam_get_मुक्त_count(mcam->bmap,
				       mcam->hprio_end, mcam->lprio_start);
	अगर (fcnt < req->count)
		वापस;
	*start = mcam->hprio_end;
	*end = mcam->lprio_start;
पूर्ण

अटल पूर्णांक npc_mcam_alloc_entries(काष्ठा npc_mcam *mcam, u16 pcअगरunc,
				  काष्ठा npc_mcam_alloc_entry_req *req,
				  काष्ठा npc_mcam_alloc_entry_rsp *rsp)
अणु
	u16 entry_list[NPC_MAX_NONCONTIG_ENTRIES];
	u16 fcnt, hp_fcnt, lp_fcnt;
	u16 start, end, index;
	पूर्णांक entry, next_start;
	bool reverse = false;
	अचिन्हित दीर्घ *bmap;
	u16 max_contig;

	mutex_lock(&mcam->lock);

	/* Check अगर there are any मुक्त entries */
	अगर (!mcam->bmap_fcnt) अणु
		mutex_unlock(&mcam->lock);
		वापस NPC_MCAM_ALLOC_FAILED;
	पूर्ण

	/* MCAM entries are भागided पूर्णांकo high priority, middle and
	 * low priority zones. Idea is to not allocate top and lower
	 * most entries as much as possible, this is to increase
	 * probability of honouring priority allocation requests.
	 *
	 * Two biपंचांगaps are used क्रम mcam entry management,
	 * mcam->bmap क्रम क्रमward search i.e '0 to mcam->bmap_entries'.
	 * mcam->bmap_reverse क्रम reverse search i.e 'mcam->bmap_entries to 0'.
	 *
	 * Reverse biपंचांगap is used to allocate entries
	 * - when a higher priority entry is requested
	 * - when available मुक्त entries are less.
	 * Lower priority ones out of avaialble मुक्त entries are always
	 * chosen when 'high vs low' question arises.
	 */

	/* Get the search range क्रम priority allocation request */
	अगर (req->priority) अणु
		npc_get_mcam_search_range_priority(mcam, req,
						   &start, &end, &reverse);
		जाओ alloc;
	पूर्ण

	/* Find out the search range क्रम non-priority allocation request
	 *
	 * Get MCAM मुक्त entry count in middle zone.
	 */
	lp_fcnt = npc_mcam_get_मुक्त_count(mcam->bmap,
					  mcam->lprio_start,
					  mcam->bmap_entries);
	hp_fcnt = npc_mcam_get_मुक्त_count(mcam->bmap, 0, mcam->hprio_end);
	fcnt = mcam->bmap_fcnt - lp_fcnt - hp_fcnt;

	/* Check अगर request can be accomodated in the middle zone */
	अगर (fcnt > req->count) अणु
		start = mcam->hprio_end;
		end = mcam->lprio_start;
	पूर्ण अन्यथा अगर ((fcnt + (hp_fcnt / 2) + (lp_fcnt / 2)) > req->count) अणु
		/* Expand search zone from half of hprio zone to
		 * half of lprio zone.
		 */
		start = mcam->hprio_end / 2;
		end = mcam->bmap_entries - (mcam->lprio_count / 2);
		reverse = true;
	पूर्ण अन्यथा अणु
		/* Not enough मुक्त entries, search all entries in reverse,
		 * so that low priority ones will get used up.
		 */
		reverse = true;
		start = 0;
		end = mcam->bmap_entries;
	पूर्ण

alloc:
	अगर (reverse) अणु
		bmap = mcam->bmap_reverse;
		start = mcam->bmap_entries - start;
		end = mcam->bmap_entries - end;
		index = start;
		start = end;
		end = index;
	पूर्ण अन्यथा अणु
		bmap = mcam->bmap;
	पूर्ण

	अगर (req->contig) अणु
		/* Allocate requested number of contiguous entries, अगर
		 * unsuccessful find max contiguous entries available.
		 */
		index = npc_mcam_find_zero_area(bmap, end, start,
						req->count, &max_contig);
		rsp->count = max_contig;
		अगर (reverse)
			rsp->entry = mcam->bmap_entries - index - max_contig;
		अन्यथा
			rsp->entry = index;
	पूर्ण अन्यथा अणु
		/* Allocate requested number of non-contiguous entries,
		 * अगर unsuccessful allocate as many as possible.
		 */
		rsp->count = 0;
		next_start = start;
		क्रम (entry = 0; entry < req->count; entry++) अणु
			index = find_next_zero_bit(bmap, end, next_start);
			अगर (index >= end)
				अवरोध;

			next_start = start + (index - start) + 1;

			/* Save the entry's index */
			अगर (reverse)
				index = mcam->bmap_entries - index - 1;
			entry_list[entry] = index;
			rsp->count++;
		पूर्ण
	पूर्ण

	/* If allocating requested no of entries is unsucessful,
	 * expand the search range to full biपंचांगap length and retry.
	 */
	अगर (!req->priority && (rsp->count < req->count) &&
	    ((end - start) != mcam->bmap_entries)) अणु
		reverse = true;
		start = 0;
		end = mcam->bmap_entries;
		जाओ alloc;
	पूर्ण

	/* For priority entry allocation requests, अगर allocation is
	 * failed then expand search to max possible range and retry.
	 */
	अगर (req->priority && rsp->count < req->count) अणु
		अगर (req->priority == NPC_MCAM_LOWER_PRIO &&
		    (start != (req->ref_entry + 1))) अणु
			start = req->ref_entry + 1;
			end = mcam->bmap_entries;
			reverse = false;
			जाओ alloc;
		पूर्ण अन्यथा अगर ((req->priority == NPC_MCAM_HIGHER_PRIO) &&
			   ((end - start) != req->ref_entry)) अणु
			start = 0;
			end = req->ref_entry;
			reverse = true;
			जाओ alloc;
		पूर्ण
	पूर्ण

	/* Copy MCAM entry indices पूर्णांकo mbox response entry_list.
	 * Requester always expects indices in ascending order, so
	 * so reverse the list अगर reverse biपंचांगap is used क्रम allocation.
	 */
	अगर (!req->contig && rsp->count) अणु
		index = 0;
		क्रम (entry = rsp->count - 1; entry >= 0; entry--) अणु
			अगर (reverse)
				rsp->entry_list[index++] = entry_list[entry];
			अन्यथा
				rsp->entry_list[entry] = entry_list[entry];
		पूर्ण
	पूर्ण

	/* Mark the allocated entries as used and set nixlf mapping */
	क्रम (entry = 0; entry < rsp->count; entry++) अणु
		index = req->contig ?
			(rsp->entry + entry) : rsp->entry_list[entry];
		npc_mcam_set_bit(mcam, index);
		mcam->entry2pfvf_map[index] = pcअगरunc;
		mcam->entry2cntr_map[index] = NPC_MCAM_INVALID_MAP;
	पूर्ण

	/* Update available मुक्त count in mbox response */
	rsp->मुक्त_count = mcam->bmap_fcnt;

	mutex_unlock(&mcam->lock);
	वापस 0;
पूर्ण

पूर्णांक rvu_mbox_handler_npc_mcam_alloc_entry(काष्ठा rvu *rvu,
					  काष्ठा npc_mcam_alloc_entry_req *req,
					  काष्ठा npc_mcam_alloc_entry_rsp *rsp)
अणु
	काष्ठा npc_mcam *mcam = &rvu->hw->mcam;
	u16 pcअगरunc = req->hdr.pcअगरunc;
	पूर्णांक blkaddr;

	blkaddr = rvu_get_blkaddr(rvu, BLKTYPE_NPC, 0);
	अगर (blkaddr < 0)
		वापस NPC_MCAM_INVALID_REQ;

	rsp->entry = NPC_MCAM_ENTRY_INVALID;
	rsp->मुक्त_count = 0;

	/* Check अगर ref_entry is within range */
	अगर (req->priority && req->ref_entry >= mcam->bmap_entries)
		वापस NPC_MCAM_INVALID_REQ;

	/* ref_entry can't be '0' अगर requested priority is high.
	 * Can't be last entry अगर requested priority is low.
	 */
	अगर ((!req->ref_entry && req->priority == NPC_MCAM_HIGHER_PRIO) ||
	    ((req->ref_entry == (mcam->bmap_entries - 1)) &&
	     req->priority == NPC_MCAM_LOWER_PRIO))
		वापस NPC_MCAM_INVALID_REQ;

	/* Since list of allocated indices needs to be sent to requester,
	 * max number of non-contiguous entries per mbox msg is limited.
	 */
	अगर (!req->contig && req->count > NPC_MAX_NONCONTIG_ENTRIES)
		वापस NPC_MCAM_INVALID_REQ;

	/* Alloc request from PFFUNC with no NIXLF attached should be denied */
	अगर (!is_nixlf_attached(rvu, pcअगरunc))
		वापस NPC_MCAM_ALLOC_DENIED;

	वापस npc_mcam_alloc_entries(mcam, pcअगरunc, req, rsp);
पूर्ण

पूर्णांक rvu_mbox_handler_npc_mcam_मुक्त_entry(काष्ठा rvu *rvu,
					 काष्ठा npc_mcam_मुक्त_entry_req *req,
					 काष्ठा msg_rsp *rsp)
अणु
	काष्ठा npc_mcam *mcam = &rvu->hw->mcam;
	u16 pcअगरunc = req->hdr.pcअगरunc;
	पूर्णांक blkaddr, rc = 0;
	u16 cntr;

	blkaddr = rvu_get_blkaddr(rvu, BLKTYPE_NPC, 0);
	अगर (blkaddr < 0)
		वापस NPC_MCAM_INVALID_REQ;

	/* Free request from PFFUNC with no NIXLF attached, ignore */
	अगर (!is_nixlf_attached(rvu, pcअगरunc))
		वापस NPC_MCAM_INVALID_REQ;

	mutex_lock(&mcam->lock);

	अगर (req->all)
		जाओ मुक्त_all;

	rc = npc_mcam_verअगरy_entry(mcam, pcअगरunc, req->entry);
	अगर (rc)
		जाओ निकास;

	mcam->entry2pfvf_map[req->entry] = 0;
	mcam->entry2target_pffunc[req->entry] = 0x0;
	npc_mcam_clear_bit(mcam, req->entry);
	npc_enable_mcam_entry(rvu, mcam, blkaddr, req->entry, false);

	/* Update entry2counter mapping */
	cntr = mcam->entry2cntr_map[req->entry];
	अगर (cntr != NPC_MCAM_INVALID_MAP)
		npc_unmap_mcam_entry_and_cntr(rvu, mcam, blkaddr,
					      req->entry, cntr);

	जाओ निकास;

मुक्त_all:
	/* Free up all entries allocated to requesting PFFUNC */
	npc_mcam_मुक्त_all_entries(rvu, mcam, blkaddr, pcअगरunc);
निकास:
	mutex_unlock(&mcam->lock);
	वापस rc;
पूर्ण

पूर्णांक rvu_mbox_handler_npc_mcam_पढ़ो_entry(काष्ठा rvu *rvu,
					 काष्ठा npc_mcam_पढ़ो_entry_req *req,
					 काष्ठा npc_mcam_पढ़ो_entry_rsp *rsp)
अणु
	काष्ठा npc_mcam *mcam = &rvu->hw->mcam;
	u16 pcअगरunc = req->hdr.pcअगरunc;
	पूर्णांक blkaddr, rc;

	blkaddr = rvu_get_blkaddr(rvu, BLKTYPE_NPC, 0);
	अगर (blkaddr < 0)
		वापस NPC_MCAM_INVALID_REQ;

	mutex_lock(&mcam->lock);
	rc = npc_mcam_verअगरy_entry(mcam, pcअगरunc, req->entry);
	अगर (!rc) अणु
		npc_पढ़ो_mcam_entry(rvu, mcam, blkaddr, req->entry,
				    &rsp->entry_data,
				    &rsp->पूर्णांकf, &rsp->enable);
	पूर्ण

	mutex_unlock(&mcam->lock);
	वापस rc;
पूर्ण

पूर्णांक rvu_mbox_handler_npc_mcam_ग_लिखो_entry(काष्ठा rvu *rvu,
					  काष्ठा npc_mcam_ग_लिखो_entry_req *req,
					  काष्ठा msg_rsp *rsp)
अणु
	काष्ठा rvu_pfvf *pfvf = rvu_get_pfvf(rvu, req->hdr.pcअगरunc);
	काष्ठा npc_mcam *mcam = &rvu->hw->mcam;
	u16 pcअगरunc = req->hdr.pcअगरunc;
	u16 channel, chan_mask;
	पूर्णांक blkaddr, rc;
	u8 nix_पूर्णांकf;

	blkaddr = rvu_get_blkaddr(rvu, BLKTYPE_NPC, 0);
	अगर (blkaddr < 0)
		वापस NPC_MCAM_INVALID_REQ;

	chan_mask = req->entry_data.kw_mask[0] & NPC_KEX_CHAN_MASK;
	channel = req->entry_data.kw[0] & NPC_KEX_CHAN_MASK;
	channel &= chan_mask;

	mutex_lock(&mcam->lock);
	rc = npc_mcam_verअगरy_entry(mcam, pcअगरunc, req->entry);
	अगर (rc)
		जाओ निकास;

	अगर (req->set_cntr &&
	    npc_mcam_verअगरy_counter(mcam, pcअगरunc, req->cntr)) अणु
		rc = NPC_MCAM_INVALID_REQ;
		जाओ निकास;
	पूर्ण

	अगर (!is_npc_पूर्णांकerface_valid(rvu, req->पूर्णांकf)) अणु
		rc = NPC_MCAM_INVALID_REQ;
		जाओ निकास;
	पूर्ण

	अगर (is_npc_पूर्णांकf_tx(req->पूर्णांकf))
		nix_पूर्णांकf = pfvf->nix_tx_पूर्णांकf;
	अन्यथा
		nix_पूर्णांकf = pfvf->nix_rx_पूर्णांकf;

	अगर (npc_mcam_verअगरy_channel(rvu, pcअगरunc, req->पूर्णांकf, channel)) अणु
		rc = NPC_MCAM_INVALID_REQ;
		जाओ निकास;
	पूर्ण

	अगर (npc_mcam_verअगरy_pf_func(rvu, &req->entry_data, req->पूर्णांकf,
				    pcअगरunc)) अणु
		rc = NPC_MCAM_INVALID_REQ;
		जाओ निकास;
	पूर्ण

	/* For AF installed rules, the nix_पूर्णांकf should be set to target NIX */
	अगर (is_pffunc_af(req->hdr.pcअगरunc))
		nix_पूर्णांकf = req->पूर्णांकf;

	npc_config_mcam_entry(rvu, mcam, blkaddr, req->entry, nix_पूर्णांकf,
			      &req->entry_data, req->enable_entry);

	अगर (req->set_cntr)
		npc_map_mcam_entry_and_cntr(rvu, mcam, blkaddr,
					    req->entry, req->cntr);

	rc = 0;
निकास:
	mutex_unlock(&mcam->lock);
	वापस rc;
पूर्ण

पूर्णांक rvu_mbox_handler_npc_mcam_ena_entry(काष्ठा rvu *rvu,
					काष्ठा npc_mcam_ena_dis_entry_req *req,
					काष्ठा msg_rsp *rsp)
अणु
	काष्ठा npc_mcam *mcam = &rvu->hw->mcam;
	u16 pcअगरunc = req->hdr.pcअगरunc;
	पूर्णांक blkaddr, rc;

	blkaddr = rvu_get_blkaddr(rvu, BLKTYPE_NPC, 0);
	अगर (blkaddr < 0)
		वापस NPC_MCAM_INVALID_REQ;

	mutex_lock(&mcam->lock);
	rc = npc_mcam_verअगरy_entry(mcam, pcअगरunc, req->entry);
	mutex_unlock(&mcam->lock);
	अगर (rc)
		वापस rc;

	npc_enable_mcam_entry(rvu, mcam, blkaddr, req->entry, true);

	वापस 0;
पूर्ण

पूर्णांक rvu_mbox_handler_npc_mcam_dis_entry(काष्ठा rvu *rvu,
					काष्ठा npc_mcam_ena_dis_entry_req *req,
					काष्ठा msg_rsp *rsp)
अणु
	काष्ठा npc_mcam *mcam = &rvu->hw->mcam;
	u16 pcअगरunc = req->hdr.pcअगरunc;
	पूर्णांक blkaddr, rc;

	blkaddr = rvu_get_blkaddr(rvu, BLKTYPE_NPC, 0);
	अगर (blkaddr < 0)
		वापस NPC_MCAM_INVALID_REQ;

	mutex_lock(&mcam->lock);
	rc = npc_mcam_verअगरy_entry(mcam, pcअगरunc, req->entry);
	mutex_unlock(&mcam->lock);
	अगर (rc)
		वापस rc;

	npc_enable_mcam_entry(rvu, mcam, blkaddr, req->entry, false);

	वापस 0;
पूर्ण

पूर्णांक rvu_mbox_handler_npc_mcam_shअगरt_entry(काष्ठा rvu *rvu,
					  काष्ठा npc_mcam_shअगरt_entry_req *req,
					  काष्ठा npc_mcam_shअगरt_entry_rsp *rsp)
अणु
	काष्ठा npc_mcam *mcam = &rvu->hw->mcam;
	u16 pcअगरunc = req->hdr.pcअगरunc;
	u16 old_entry, new_entry;
	u16 index, cntr;
	पूर्णांक blkaddr, rc;

	blkaddr = rvu_get_blkaddr(rvu, BLKTYPE_NPC, 0);
	अगर (blkaddr < 0)
		वापस NPC_MCAM_INVALID_REQ;

	अगर (req->shअगरt_count > NPC_MCAM_MAX_SHIFTS)
		वापस NPC_MCAM_INVALID_REQ;

	mutex_lock(&mcam->lock);
	क्रम (index = 0; index < req->shअगरt_count; index++) अणु
		old_entry = req->curr_entry[index];
		new_entry = req->new_entry[index];

		/* Check अगर both old and new entries are valid and
		 * करोes beदीर्घ to this PFFUNC or not.
		 */
		rc = npc_mcam_verअगरy_entry(mcam, pcअगरunc, old_entry);
		अगर (rc)
			अवरोध;

		rc = npc_mcam_verअगरy_entry(mcam, pcअगरunc, new_entry);
		अगर (rc)
			अवरोध;

		/* new_entry should not have a counter mapped */
		अगर (mcam->entry2cntr_map[new_entry] != NPC_MCAM_INVALID_MAP) अणु
			rc = NPC_MCAM_PERM_DENIED;
			अवरोध;
		पूर्ण

		/* Disable the new_entry */
		npc_enable_mcam_entry(rvu, mcam, blkaddr, new_entry, false);

		/* Copy rule from old entry to new entry */
		npc_copy_mcam_entry(rvu, mcam, blkaddr, old_entry, new_entry);

		/* Copy counter mapping, अगर any */
		cntr = mcam->entry2cntr_map[old_entry];
		अगर (cntr != NPC_MCAM_INVALID_MAP) अणु
			npc_unmap_mcam_entry_and_cntr(rvu, mcam, blkaddr,
						      old_entry, cntr);
			npc_map_mcam_entry_and_cntr(rvu, mcam, blkaddr,
						    new_entry, cntr);
		पूर्ण

		/* Enable new_entry and disable old_entry */
		npc_enable_mcam_entry(rvu, mcam, blkaddr, new_entry, true);
		npc_enable_mcam_entry(rvu, mcam, blkaddr, old_entry, false);
	पूर्ण

	/* If shअगरt has failed then report the failed index */
	अगर (index != req->shअगरt_count) अणु
		rc = NPC_MCAM_PERM_DENIED;
		rsp->failed_entry_idx = index;
	पूर्ण

	mutex_unlock(&mcam->lock);
	वापस rc;
पूर्ण

पूर्णांक rvu_mbox_handler_npc_mcam_alloc_counter(काष्ठा rvu *rvu,
			काष्ठा npc_mcam_alloc_counter_req *req,
			काष्ठा npc_mcam_alloc_counter_rsp *rsp)
अणु
	काष्ठा npc_mcam *mcam = &rvu->hw->mcam;
	u16 pcअगरunc = req->hdr.pcअगरunc;
	u16 max_contig, cntr;
	पूर्णांक blkaddr, index;

	blkaddr = rvu_get_blkaddr(rvu, BLKTYPE_NPC, 0);
	अगर (blkaddr < 0)
		वापस NPC_MCAM_INVALID_REQ;

	/* If the request is from a PFFUNC with no NIXLF attached, ignore */
	अगर (!is_nixlf_attached(rvu, pcअगरunc))
		वापस NPC_MCAM_INVALID_REQ;

	/* Since list of allocated counter IDs needs to be sent to requester,
	 * max number of non-contiguous counters per mbox msg is limited.
	 */
	अगर (!req->contig && req->count > NPC_MAX_NONCONTIG_COUNTERS)
		वापस NPC_MCAM_INVALID_REQ;

	mutex_lock(&mcam->lock);

	/* Check अगर unused counters are available or not */
	अगर (!rvu_rsrc_मुक्त_count(&mcam->counters)) अणु
		mutex_unlock(&mcam->lock);
		वापस NPC_MCAM_ALLOC_FAILED;
	पूर्ण

	rsp->count = 0;

	अगर (req->contig) अणु
		/* Allocate requested number of contiguous counters, अगर
		 * unsuccessful find max contiguous entries available.
		 */
		index = npc_mcam_find_zero_area(mcam->counters.bmap,
						mcam->counters.max, 0,
						req->count, &max_contig);
		rsp->count = max_contig;
		rsp->cntr = index;
		क्रम (cntr = index; cntr < (index + max_contig); cntr++) अणु
			__set_bit(cntr, mcam->counters.bmap);
			mcam->cntr2pfvf_map[cntr] = pcअगरunc;
		पूर्ण
	पूर्ण अन्यथा अणु
		/* Allocate requested number of non-contiguous counters,
		 * अगर unsuccessful allocate as many as possible.
		 */
		क्रम (cntr = 0; cntr < req->count; cntr++) अणु
			index = rvu_alloc_rsrc(&mcam->counters);
			अगर (index < 0)
				अवरोध;
			rsp->cntr_list[cntr] = index;
			rsp->count++;
			mcam->cntr2pfvf_map[index] = pcअगरunc;
		पूर्ण
	पूर्ण

	mutex_unlock(&mcam->lock);
	वापस 0;
पूर्ण

पूर्णांक rvu_mbox_handler_npc_mcam_मुक्त_counter(काष्ठा rvu *rvu,
		काष्ठा npc_mcam_oper_counter_req *req, काष्ठा msg_rsp *rsp)
अणु
	काष्ठा npc_mcam *mcam = &rvu->hw->mcam;
	u16 index, entry = 0;
	पूर्णांक blkaddr, err;

	blkaddr = rvu_get_blkaddr(rvu, BLKTYPE_NPC, 0);
	अगर (blkaddr < 0)
		वापस NPC_MCAM_INVALID_REQ;

	mutex_lock(&mcam->lock);
	err = npc_mcam_verअगरy_counter(mcam, req->hdr.pcअगरunc, req->cntr);
	अगर (err) अणु
		mutex_unlock(&mcam->lock);
		वापस err;
	पूर्ण

	/* Mark counter as मुक्त/unused */
	mcam->cntr2pfvf_map[req->cntr] = NPC_MCAM_INVALID_MAP;
	rvu_मुक्त_rsrc(&mcam->counters, req->cntr);

	/* Disable all MCAM entry's stats which are using this counter */
	जबतक (entry < mcam->bmap_entries) अणु
		अगर (!mcam->cntr_refcnt[req->cntr])
			अवरोध;

		index = find_next_bit(mcam->bmap, mcam->bmap_entries, entry);
		अगर (index >= mcam->bmap_entries)
			अवरोध;
		entry = index + 1;
		अगर (mcam->entry2cntr_map[index] != req->cntr)
			जारी;

		npc_unmap_mcam_entry_and_cntr(rvu, mcam, blkaddr,
					      index, req->cntr);
	पूर्ण

	mutex_unlock(&mcam->lock);
	वापस 0;
पूर्ण

पूर्णांक rvu_mbox_handler_npc_mcam_unmap_counter(काष्ठा rvu *rvu,
		काष्ठा npc_mcam_unmap_counter_req *req, काष्ठा msg_rsp *rsp)
अणु
	काष्ठा npc_mcam *mcam = &rvu->hw->mcam;
	u16 index, entry = 0;
	पूर्णांक blkaddr, rc;

	blkaddr = rvu_get_blkaddr(rvu, BLKTYPE_NPC, 0);
	अगर (blkaddr < 0)
		वापस NPC_MCAM_INVALID_REQ;

	mutex_lock(&mcam->lock);
	rc = npc_mcam_verअगरy_counter(mcam, req->hdr.pcअगरunc, req->cntr);
	अगर (rc)
		जाओ निकास;

	/* Unmap the MCAM entry and counter */
	अगर (!req->all) अणु
		rc = npc_mcam_verअगरy_entry(mcam, req->hdr.pcअगरunc, req->entry);
		अगर (rc)
			जाओ निकास;
		npc_unmap_mcam_entry_and_cntr(rvu, mcam, blkaddr,
					      req->entry, req->cntr);
		जाओ निकास;
	पूर्ण

	/* Disable all MCAM entry's stats which are using this counter */
	जबतक (entry < mcam->bmap_entries) अणु
		अगर (!mcam->cntr_refcnt[req->cntr])
			अवरोध;

		index = find_next_bit(mcam->bmap, mcam->bmap_entries, entry);
		अगर (index >= mcam->bmap_entries)
			अवरोध;
		अगर (mcam->entry2cntr_map[index] != req->cntr)
			जारी;

		entry = index + 1;
		npc_unmap_mcam_entry_and_cntr(rvu, mcam, blkaddr,
					      index, req->cntr);
	पूर्ण
निकास:
	mutex_unlock(&mcam->lock);
	वापस rc;
पूर्ण

पूर्णांक rvu_mbox_handler_npc_mcam_clear_counter(काष्ठा rvu *rvu,
		काष्ठा npc_mcam_oper_counter_req *req, काष्ठा msg_rsp *rsp)
अणु
	काष्ठा npc_mcam *mcam = &rvu->hw->mcam;
	पूर्णांक blkaddr, err;

	blkaddr = rvu_get_blkaddr(rvu, BLKTYPE_NPC, 0);
	अगर (blkaddr < 0)
		वापस NPC_MCAM_INVALID_REQ;

	mutex_lock(&mcam->lock);
	err = npc_mcam_verअगरy_counter(mcam, req->hdr.pcअगरunc, req->cntr);
	mutex_unlock(&mcam->lock);
	अगर (err)
		वापस err;

	rvu_ग_लिखो64(rvu, blkaddr, NPC_AF_MATCH_STATX(req->cntr), 0x00);

	वापस 0;
पूर्ण

पूर्णांक rvu_mbox_handler_npc_mcam_counter_stats(काष्ठा rvu *rvu,
			काष्ठा npc_mcam_oper_counter_req *req,
			काष्ठा npc_mcam_oper_counter_rsp *rsp)
अणु
	काष्ठा npc_mcam *mcam = &rvu->hw->mcam;
	पूर्णांक blkaddr, err;

	blkaddr = rvu_get_blkaddr(rvu, BLKTYPE_NPC, 0);
	अगर (blkaddr < 0)
		वापस NPC_MCAM_INVALID_REQ;

	mutex_lock(&mcam->lock);
	err = npc_mcam_verअगरy_counter(mcam, req->hdr.pcअगरunc, req->cntr);
	mutex_unlock(&mcam->lock);
	अगर (err)
		वापस err;

	rsp->stat = rvu_पढ़ो64(rvu, blkaddr, NPC_AF_MATCH_STATX(req->cntr));
	rsp->stat &= BIT_ULL(48) - 1;

	वापस 0;
पूर्ण

पूर्णांक rvu_mbox_handler_npc_mcam_alloc_and_ग_लिखो_entry(काष्ठा rvu *rvu,
			  काष्ठा npc_mcam_alloc_and_ग_लिखो_entry_req *req,
			  काष्ठा npc_mcam_alloc_and_ग_लिखो_entry_rsp *rsp)
अणु
	काष्ठा rvu_pfvf *pfvf = rvu_get_pfvf(rvu, req->hdr.pcअगरunc);
	काष्ठा npc_mcam_alloc_counter_req cntr_req;
	काष्ठा npc_mcam_alloc_counter_rsp cntr_rsp;
	काष्ठा npc_mcam_alloc_entry_req entry_req;
	काष्ठा npc_mcam_alloc_entry_rsp entry_rsp;
	काष्ठा npc_mcam *mcam = &rvu->hw->mcam;
	u16 entry = NPC_MCAM_ENTRY_INVALID;
	u16 cntr = NPC_MCAM_ENTRY_INVALID;
	u16 channel, chan_mask;
	पूर्णांक blkaddr, rc;
	u8 nix_पूर्णांकf;

	blkaddr = rvu_get_blkaddr(rvu, BLKTYPE_NPC, 0);
	अगर (blkaddr < 0)
		वापस NPC_MCAM_INVALID_REQ;

	अगर (!is_npc_पूर्णांकerface_valid(rvu, req->पूर्णांकf))
		वापस NPC_MCAM_INVALID_REQ;

	chan_mask = req->entry_data.kw_mask[0] & NPC_KEX_CHAN_MASK;
	channel = req->entry_data.kw[0] & NPC_KEX_CHAN_MASK;
	channel &= chan_mask;

	अगर (npc_mcam_verअगरy_channel(rvu, req->hdr.pcअगरunc, req->पूर्णांकf, channel))
		वापस NPC_MCAM_INVALID_REQ;

	अगर (npc_mcam_verअगरy_pf_func(rvu, &req->entry_data, req->पूर्णांकf,
				    req->hdr.pcअगरunc))
		वापस NPC_MCAM_INVALID_REQ;

	/* Try to allocate a MCAM entry */
	entry_req.hdr.pcअगरunc = req->hdr.pcअगरunc;
	entry_req.contig = true;
	entry_req.priority = req->priority;
	entry_req.ref_entry = req->ref_entry;
	entry_req.count = 1;

	rc = rvu_mbox_handler_npc_mcam_alloc_entry(rvu,
						   &entry_req, &entry_rsp);
	अगर (rc)
		वापस rc;

	अगर (!entry_rsp.count)
		वापस NPC_MCAM_ALLOC_FAILED;

	entry = entry_rsp.entry;

	अगर (!req->alloc_cntr)
		जाओ ग_लिखो_entry;

	/* Now allocate counter */
	cntr_req.hdr.pcअगरunc = req->hdr.pcअगरunc;
	cntr_req.contig = true;
	cntr_req.count = 1;

	rc = rvu_mbox_handler_npc_mcam_alloc_counter(rvu, &cntr_req, &cntr_rsp);
	अगर (rc) अणु
		/* Free allocated MCAM entry */
		mutex_lock(&mcam->lock);
		mcam->entry2pfvf_map[entry] = 0;
		npc_mcam_clear_bit(mcam, entry);
		mutex_unlock(&mcam->lock);
		वापस rc;
	पूर्ण

	cntr = cntr_rsp.cntr;

ग_लिखो_entry:
	mutex_lock(&mcam->lock);

	अगर (is_npc_पूर्णांकf_tx(req->पूर्णांकf))
		nix_पूर्णांकf = pfvf->nix_tx_पूर्णांकf;
	अन्यथा
		nix_पूर्णांकf = pfvf->nix_rx_पूर्णांकf;

	npc_config_mcam_entry(rvu, mcam, blkaddr, entry, nix_पूर्णांकf,
			      &req->entry_data, req->enable_entry);

	अगर (req->alloc_cntr)
		npc_map_mcam_entry_and_cntr(rvu, mcam, blkaddr, entry, cntr);
	mutex_unlock(&mcam->lock);

	rsp->entry = entry;
	rsp->cntr = cntr;

	वापस 0;
पूर्ण

#घोषणा GET_KEX_CFG(पूर्णांकf) \
	rvu_पढ़ो64(rvu, BLKADDR_NPC, NPC_AF_INTFX_KEX_CFG(पूर्णांकf))

#घोषणा GET_KEX_FLAGS(ld) \
	rvu_पढ़ो64(rvu, BLKADDR_NPC, NPC_AF_KEX_LDATAX_FLAGS_CFG(ld))

#घोषणा GET_KEX_LD(पूर्णांकf, lid, lt, ld)	\
	rvu_पढ़ो64(rvu, BLKADDR_NPC,	\
		NPC_AF_INTFX_LIDX_LTX_LDX_CFG(पूर्णांकf, lid, lt, ld))

#घोषणा GET_KEX_LDFLAGS(पूर्णांकf, ld, fl)	\
	rvu_पढ़ो64(rvu, BLKADDR_NPC,	\
		NPC_AF_INTFX_LDATAX_FLAGSX_CFG(पूर्णांकf, ld, fl))

पूर्णांक rvu_mbox_handler_npc_get_kex_cfg(काष्ठा rvu *rvu, काष्ठा msg_req *req,
				     काष्ठा npc_get_kex_cfg_rsp *rsp)
अणु
	पूर्णांक lid, lt, ld, fl;

	rsp->rx_keyx_cfg = GET_KEX_CFG(NIX_INTF_RX);
	rsp->tx_keyx_cfg = GET_KEX_CFG(NIX_INTF_TX);
	क्रम (lid = 0; lid < NPC_MAX_LID; lid++) अणु
		क्रम (lt = 0; lt < NPC_MAX_LT; lt++) अणु
			क्रम (ld = 0; ld < NPC_MAX_LD; ld++) अणु
				rsp->पूर्णांकf_lid_lt_ld[NIX_INTF_RX][lid][lt][ld] =
					GET_KEX_LD(NIX_INTF_RX, lid, lt, ld);
				rsp->पूर्णांकf_lid_lt_ld[NIX_INTF_TX][lid][lt][ld] =
					GET_KEX_LD(NIX_INTF_TX, lid, lt, ld);
			पूर्ण
		पूर्ण
	पूर्ण
	क्रम (ld = 0; ld < NPC_MAX_LD; ld++)
		rsp->kex_ld_flags[ld] = GET_KEX_FLAGS(ld);

	क्रम (ld = 0; ld < NPC_MAX_LD; ld++) अणु
		क्रम (fl = 0; fl < NPC_MAX_LFL; fl++) अणु
			rsp->पूर्णांकf_ld_flags[NIX_INTF_RX][ld][fl] =
					GET_KEX_LDFLAGS(NIX_INTF_RX, ld, fl);
			rsp->पूर्णांकf_ld_flags[NIX_INTF_TX][ld][fl] =
					GET_KEX_LDFLAGS(NIX_INTF_TX, ld, fl);
		पूर्ण
	पूर्ण
	स_नकल(rsp->mkex_pfl_name, rvu->mkex_pfl_name, MKEX_NAME_LEN);
	वापस 0;
पूर्ण

पूर्णांक rvu_mbox_handler_npc_पढ़ो_base_steer_rule(काष्ठा rvu *rvu,
					      काष्ठा msg_req *req,
					      काष्ठा npc_mcam_पढ़ो_base_rule_rsp *rsp)
अणु
	काष्ठा npc_mcam *mcam = &rvu->hw->mcam;
	पूर्णांक index, blkaddr, nixlf, rc = 0;
	u16 pcअगरunc = req->hdr.pcअगरunc;
	काष्ठा rvu_pfvf *pfvf;
	u8 पूर्णांकf, enable;

	blkaddr = rvu_get_blkaddr(rvu, BLKTYPE_NPC, 0);
	अगर (blkaddr < 0)
		वापस NPC_MCAM_INVALID_REQ;

	/* Return the channel number in हाल of PF */
	अगर (!(pcअगरunc & RVU_PFVF_FUNC_MASK)) अणु
		pfvf = rvu_get_pfvf(rvu, pcअगरunc);
		rsp->entry.kw[0] = pfvf->rx_chan_base;
		rsp->entry.kw_mask[0] = 0xFFFULL;
		जाओ out;
	पूर्ण

	/* Find the pkt steering rule installed by PF to this VF */
	mutex_lock(&mcam->lock);
	क्रम (index = 0; index < mcam->bmap_entries; index++) अणु
		अगर (mcam->entry2target_pffunc[index] == pcअगरunc)
			जाओ पढ़ो_entry;
	पूर्ण

	rc = nix_get_nixlf(rvu, pcअगरunc, &nixlf, शून्य);
	अगर (rc < 0) अणु
		mutex_unlock(&mcam->lock);
		जाओ out;
	पूर्ण
	/* Read the शेष ucast entry अगर there is no pkt steering rule */
	index = npc_get_nixlf_mcam_index(mcam, pcअगरunc, nixlf,
					 NIXLF_UCAST_ENTRY);
पढ़ो_entry:
	/* Read the mcam entry */
	npc_पढ़ो_mcam_entry(rvu, mcam, blkaddr, index, &rsp->entry, &पूर्णांकf,
			    &enable);
	mutex_unlock(&mcam->lock);
out:
	वापस rc;
पूर्ण

पूर्णांक rvu_mbox_handler_npc_mcam_entry_stats(काष्ठा rvu *rvu,
					  काष्ठा npc_mcam_get_stats_req *req,
					  काष्ठा npc_mcam_get_stats_rsp *rsp)
अणु
	काष्ठा npc_mcam *mcam = &rvu->hw->mcam;
	u16 index, cntr;
	पूर्णांक blkaddr;
	u64 regval;
	u32 bank;

	blkaddr = rvu_get_blkaddr(rvu, BLKTYPE_NPC, 0);
	अगर (blkaddr < 0)
		वापस NPC_MCAM_INVALID_REQ;

	mutex_lock(&mcam->lock);

	index = req->entry & (mcam->banksize - 1);
	bank = npc_get_bank(mcam, req->entry);

	/* पढ़ो MCAM entry STAT_ACT रेजिस्टर */
	regval = rvu_पढ़ो64(rvu, blkaddr, NPC_AF_MCAMEX_BANKX_STAT_ACT(index, bank));

	अगर (!(regval & BIT_ULL(9))) अणु
		rsp->stat_ena = 0;
		mutex_unlock(&mcam->lock);
		वापस 0;
	पूर्ण

	cntr = regval & 0x1FF;

	rsp->stat_ena = 1;
	rsp->stat = rvu_पढ़ो64(rvu, blkaddr, NPC_AF_MATCH_STATX(cntr));
	rsp->stat &= BIT_ULL(48) - 1;

	mutex_unlock(&mcam->lock);

	वापस 0;
पूर्ण
