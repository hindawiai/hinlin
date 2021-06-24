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
#समावेश "npc.h"
#समावेश "cgx.h"
#समावेश "lmac_common.h"

अटल व्योम nix_मुक्त_tx_vtag_entries(काष्ठा rvu *rvu, u16 pcअगरunc);
अटल पूर्णांक rvu_nix_get_bpid(काष्ठा rvu *rvu, काष्ठा nix_bp_cfg_req *req,
			    पूर्णांक type, पूर्णांक chan_id);

क्रमागत mc_tbl_sz अणु
	MC_TBL_SZ_256,
	MC_TBL_SZ_512,
	MC_TBL_SZ_1K,
	MC_TBL_SZ_2K,
	MC_TBL_SZ_4K,
	MC_TBL_SZ_8K,
	MC_TBL_SZ_16K,
	MC_TBL_SZ_32K,
	MC_TBL_SZ_64K,
पूर्ण;

क्रमागत mc_buf_cnt अणु
	MC_BUF_CNT_8,
	MC_BUF_CNT_16,
	MC_BUF_CNT_32,
	MC_BUF_CNT_64,
	MC_BUF_CNT_128,
	MC_BUF_CNT_256,
	MC_BUF_CNT_512,
	MC_BUF_CNT_1024,
	MC_BUF_CNT_2048,
पूर्ण;

क्रमागत nix_makr_fmt_indexes अणु
	NIX_MARK_CFG_IP_DSCP_RED,
	NIX_MARK_CFG_IP_DSCP_YELLOW,
	NIX_MARK_CFG_IP_DSCP_YELLOW_RED,
	NIX_MARK_CFG_IP_ECN_RED,
	NIX_MARK_CFG_IP_ECN_YELLOW,
	NIX_MARK_CFG_IP_ECN_YELLOW_RED,
	NIX_MARK_CFG_VLAN_DEI_RED,
	NIX_MARK_CFG_VLAN_DEI_YELLOW,
	NIX_MARK_CFG_VLAN_DEI_YELLOW_RED,
	NIX_MARK_CFG_MAX,
पूर्ण;

/* For now considering MC resources needed क्रम broadcast
 * pkt replication only. i.e 256 HWVFs + 12 PFs.
 */
#घोषणा MC_TBL_SIZE	MC_TBL_SZ_512
#घोषणा MC_BUF_CNT	MC_BUF_CNT_128

काष्ठा mce अणु
	काष्ठा hlist_node	node;
	u16			pcअगरunc;
पूर्ण;

पूर्णांक rvu_get_next_nix_blkaddr(काष्ठा rvu *rvu, पूर्णांक blkaddr)
अणु
	पूर्णांक i = 0;

	/*If blkaddr is 0, वापस the first nix block address*/
	अगर (blkaddr == 0)
		वापस rvu->nix_blkaddr[blkaddr];

	जबतक (i + 1 < MAX_NIX_BLKS) अणु
		अगर (rvu->nix_blkaddr[i] == blkaddr)
			वापस rvu->nix_blkaddr[i + 1];
		i++;
	पूर्ण

	वापस 0;
पूर्ण

bool is_nixlf_attached(काष्ठा rvu *rvu, u16 pcअगरunc)
अणु
	काष्ठा rvu_pfvf *pfvf = rvu_get_pfvf(rvu, pcअगरunc);
	पूर्णांक blkaddr;

	blkaddr = rvu_get_blkaddr(rvu, BLKTYPE_NIX, pcअगरunc);
	अगर (!pfvf->nixlf || blkaddr < 0)
		वापस false;
	वापस true;
पूर्ण

पूर्णांक rvu_get_nixlf_count(काष्ठा rvu *rvu)
अणु
	पूर्णांक blkaddr = 0, max = 0;
	काष्ठा rvu_block *block;

	blkaddr = rvu_get_next_nix_blkaddr(rvu, blkaddr);
	जबतक (blkaddr) अणु
		block = &rvu->hw->block[blkaddr];
		max += block->lf.max;
		blkaddr = rvu_get_next_nix_blkaddr(rvu, blkaddr);
	पूर्ण
	वापस max;
पूर्ण

पूर्णांक nix_get_nixlf(काष्ठा rvu *rvu, u16 pcअगरunc, पूर्णांक *nixlf, पूर्णांक *nix_blkaddr)
अणु
	काष्ठा rvu_pfvf *pfvf = rvu_get_pfvf(rvu, pcअगरunc);
	काष्ठा rvu_hwinfo *hw = rvu->hw;
	पूर्णांक blkaddr;

	blkaddr = rvu_get_blkaddr(rvu, BLKTYPE_NIX, pcअगरunc);
	अगर (!pfvf->nixlf || blkaddr < 0)
		वापस NIX_AF_ERR_AF_LF_INVALID;

	*nixlf = rvu_get_lf(rvu, &hw->block[blkaddr], pcअगरunc, 0);
	अगर (*nixlf < 0)
		वापस NIX_AF_ERR_AF_LF_INVALID;

	अगर (nix_blkaddr)
		*nix_blkaddr = blkaddr;

	वापस 0;
पूर्ण

अटल व्योम nix_mce_list_init(काष्ठा nix_mce_list *list, पूर्णांक max)
अणु
	INIT_HLIST_HEAD(&list->head);
	list->count = 0;
	list->max = max;
पूर्ण

अटल u16 nix_alloc_mce_list(काष्ठा nix_mcast *mcast, पूर्णांक count)
अणु
	पूर्णांक idx;

	अगर (!mcast)
		वापस 0;

	idx = mcast->next_मुक्त_mce;
	mcast->next_मुक्त_mce += count;
	वापस idx;
पूर्ण

काष्ठा nix_hw *get_nix_hw(काष्ठा rvu_hwinfo *hw, पूर्णांक blkaddr)
अणु
	पूर्णांक nix_blkaddr = 0, i = 0;
	काष्ठा rvu *rvu = hw->rvu;

	nix_blkaddr = rvu_get_next_nix_blkaddr(rvu, nix_blkaddr);
	जबतक (nix_blkaddr) अणु
		अगर (blkaddr == nix_blkaddr && hw->nix)
			वापस &hw->nix[i];
		nix_blkaddr = rvu_get_next_nix_blkaddr(rvu, nix_blkaddr);
		i++;
	पूर्ण
	वापस शून्य;
पूर्ण

अटल व्योम nix_rx_sync(काष्ठा rvu *rvu, पूर्णांक blkaddr)
अणु
	पूर्णांक err;

	/*Sync all in flight RX packets to LLC/DRAM */
	rvu_ग_लिखो64(rvu, blkaddr, NIX_AF_RX_SW_SYNC, BIT_ULL(0));
	err = rvu_poll_reg(rvu, blkaddr, NIX_AF_RX_SW_SYNC, BIT_ULL(0), true);
	अगर (err)
		dev_err(rvu->dev, "NIX RX software sync failed\n");
पूर्ण

अटल bool is_valid_txschq(काष्ठा rvu *rvu, पूर्णांक blkaddr,
			    पूर्णांक lvl, u16 pcअगरunc, u16 schq)
अणु
	काष्ठा rvu_hwinfo *hw = rvu->hw;
	काष्ठा nix_txsch *txsch;
	काष्ठा nix_hw *nix_hw;
	u16 map_func;

	nix_hw = get_nix_hw(rvu->hw, blkaddr);
	अगर (!nix_hw)
		वापस false;

	txsch = &nix_hw->txsch[lvl];
	/* Check out of bounds */
	अगर (schq >= txsch->schq.max)
		वापस false;

	mutex_lock(&rvu->rsrc_lock);
	map_func = TXSCH_MAP_FUNC(txsch->pfvf_map[schq]);
	mutex_unlock(&rvu->rsrc_lock);

	/* TLs aggegating traffic are shared across PF and VFs */
	अगर (lvl >= hw->cap.nix_tx_aggr_lvl) अणु
		अगर (rvu_get_pf(map_func) != rvu_get_pf(pcअगरunc))
			वापस false;
		अन्यथा
			वापस true;
	पूर्ण

	अगर (map_func != pcअगरunc)
		वापस false;

	वापस true;
पूर्ण

अटल पूर्णांक nix_पूर्णांकerface_init(काष्ठा rvu *rvu, u16 pcअगरunc, पूर्णांक type, पूर्णांक nixlf)
अणु
	काष्ठा rvu_pfvf *pfvf = rvu_get_pfvf(rvu, pcअगरunc);
	काष्ठा mac_ops *mac_ops;
	पूर्णांक pkind, pf, vf, lbkid;
	u8 cgx_id, lmac_id;
	पूर्णांक err;

	pf = rvu_get_pf(pcअगरunc);
	अगर (!is_pf_cgxmapped(rvu, pf) && type != NIX_INTF_TYPE_LBK)
		वापस 0;

	चयन (type) अणु
	हाल NIX_INTF_TYPE_CGX:
		pfvf->cgx_lmac = rvu->pf2cgxlmac_map[pf];
		rvu_get_cgx_lmac_id(pfvf->cgx_lmac, &cgx_id, &lmac_id);

		pkind = rvu_npc_get_pkind(rvu, pf);
		अगर (pkind < 0) अणु
			dev_err(rvu->dev,
				"PF_Func 0x%x: Invalid pkind\n", pcअगरunc);
			वापस -EINVAL;
		पूर्ण
		pfvf->rx_chan_base = rvu_nix_chan_cgx(rvu, cgx_id, lmac_id, 0);
		pfvf->tx_chan_base = pfvf->rx_chan_base;
		pfvf->rx_chan_cnt = 1;
		pfvf->tx_chan_cnt = 1;
		cgx_set_pkind(rvu_cgx_pdata(cgx_id, rvu), lmac_id, pkind);
		rvu_npc_set_pkind(rvu, pkind, pfvf);

		mac_ops = get_mac_ops(rvu_cgx_pdata(cgx_id, rvu));
		/* By शेष we enable छोड़ो frames */
		अगर ((pcअगरunc & RVU_PFVF_FUNC_MASK) == 0)
			mac_ops->mac_enadis_छोड़ो_frm(rvu_cgx_pdata(cgx_id,
								    rvu),
						      lmac_id, true, true);
		अवरोध;
	हाल NIX_INTF_TYPE_LBK:
		vf = (pcअगरunc & RVU_PFVF_FUNC_MASK) - 1;

		/* If NIX1 block is present on the silicon then NIXes are
		 * asचिन्हित alternatively क्रम lbk पूर्णांकerfaces. NIX0 should
		 * send packets on lbk link 1 channels and NIX1 should send
		 * on lbk link 0 channels क्रम the communication between
		 * NIX0 and NIX1.
		 */
		lbkid = 0;
		अगर (rvu->hw->lbk_links > 1)
			lbkid = vf & 0x1 ? 0 : 1;

		/* Note that AF's VFs work in pairs and talk over consecutive
		 * loopback channels.Thereक्रमe अगर odd number of AF VFs are
		 * enabled then the last VF reमुख्यs with no pair.
		 */
		pfvf->rx_chan_base = rvu_nix_chan_lbk(rvu, lbkid, vf);
		pfvf->tx_chan_base = vf & 0x1 ?
					rvu_nix_chan_lbk(rvu, lbkid, vf - 1) :
					rvu_nix_chan_lbk(rvu, lbkid, vf + 1);
		pfvf->rx_chan_cnt = 1;
		pfvf->tx_chan_cnt = 1;
		rvu_npc_install_promisc_entry(rvu, pcअगरunc, nixlf,
					      pfvf->rx_chan_base,
					      pfvf->rx_chan_cnt, false);
		अवरोध;
	पूर्ण

	/* Add a UCAST क्रमwarding rule in MCAM with this NIXLF attached
	 * RVU PF/VF's MAC address.
	 */
	rvu_npc_install_ucast_entry(rvu, pcअगरunc, nixlf,
				    pfvf->rx_chan_base, pfvf->mac_addr);

	/* Add this PF_FUNC to bcast pkt replication list */
	err = nix_update_bcast_mce_list(rvu, pcअगरunc, true);
	अगर (err) अणु
		dev_err(rvu->dev,
			"Bcast list, failed to enable PF_FUNC 0x%x\n",
			pcअगरunc);
		वापस err;
	पूर्ण

	rvu_npc_install_bcast_match_entry(rvu, pcअगरunc,
					  nixlf, pfvf->rx_chan_base);
	pfvf->maxlen = NIC_HW_MIN_FRS;
	pfvf->minlen = NIC_HW_MIN_FRS;

	वापस 0;
पूर्ण

अटल व्योम nix_पूर्णांकerface_deinit(काष्ठा rvu *rvu, u16 pcअगरunc, u8 nixlf)
अणु
	काष्ठा rvu_pfvf *pfvf = rvu_get_pfvf(rvu, pcअगरunc);
	पूर्णांक err;

	pfvf->maxlen = 0;
	pfvf->minlen = 0;

	/* Remove this PF_FUNC from bcast pkt replication list */
	err = nix_update_bcast_mce_list(rvu, pcअगरunc, false);
	अगर (err) अणु
		dev_err(rvu->dev,
			"Bcast list, failed to disable PF_FUNC 0x%x\n",
			pcअगरunc);
	पूर्ण

	/* Free and disable any MCAM entries used by this NIX LF */
	rvu_npc_disable_mcam_entries(rvu, pcअगरunc, nixlf);
पूर्ण

पूर्णांक rvu_mbox_handler_nix_bp_disable(काष्ठा rvu *rvu,
				    काष्ठा nix_bp_cfg_req *req,
				    काष्ठा msg_rsp *rsp)
अणु
	u16 pcअगरunc = req->hdr.pcअगरunc;
	काष्ठा rvu_pfvf *pfvf;
	पूर्णांक blkaddr, pf, type;
	u16 chan_base, chan;
	u64 cfg;

	pf = rvu_get_pf(pcअगरunc);
	type = is_afvf(pcअगरunc) ? NIX_INTF_TYPE_LBK : NIX_INTF_TYPE_CGX;
	अगर (!is_pf_cgxmapped(rvu, pf) && type != NIX_INTF_TYPE_LBK)
		वापस 0;

	pfvf = rvu_get_pfvf(rvu, pcअगरunc);
	blkaddr = rvu_get_blkaddr(rvu, BLKTYPE_NIX, pcअगरunc);

	chan_base = pfvf->rx_chan_base + req->chan_base;
	क्रम (chan = chan_base; chan < (chan_base + req->chan_cnt); chan++) अणु
		cfg = rvu_पढ़ो64(rvu, blkaddr, NIX_AF_RX_CHANX_CFG(chan));
		rvu_ग_लिखो64(rvu, blkaddr, NIX_AF_RX_CHANX_CFG(chan),
			    cfg & ~BIT_ULL(16));
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक rvu_nix_get_bpid(काष्ठा rvu *rvu, काष्ठा nix_bp_cfg_req *req,
			    पूर्णांक type, पूर्णांक chan_id)
अणु
	पूर्णांक bpid, blkaddr, lmac_chan_cnt;
	काष्ठा rvu_hwinfo *hw = rvu->hw;
	u16 cgx_bpid_cnt, lbk_bpid_cnt;
	काष्ठा rvu_pfvf *pfvf;
	u8 cgx_id, lmac_id;
	u64 cfg;

	blkaddr = rvu_get_blkaddr(rvu, BLKTYPE_NIX, req->hdr.pcअगरunc);
	cfg = rvu_पढ़ो64(rvu, blkaddr, NIX_AF_CONST);
	lmac_chan_cnt = cfg & 0xFF;

	cgx_bpid_cnt = hw->cgx_links * lmac_chan_cnt;
	lbk_bpid_cnt = hw->lbk_links * ((cfg >> 16) & 0xFF);

	pfvf = rvu_get_pfvf(rvu, req->hdr.pcअगरunc);

	/* Backpressure IDs range भागision
	 * CGX channles are mapped to (0 - 191) BPIDs
	 * LBK channles are mapped to (192 - 255) BPIDs
	 * SDP channles are mapped to (256 - 511) BPIDs
	 *
	 * Lmac channles and bpids mapped as follows
	 * cgx(0)_lmac(0)_chan(0 - 15) = bpid(0 - 15)
	 * cgx(0)_lmac(1)_chan(0 - 15) = bpid(16 - 31) ....
	 * cgx(1)_lmac(0)_chan(0 - 15) = bpid(64 - 79) ....
	 */
	चयन (type) अणु
	हाल NIX_INTF_TYPE_CGX:
		अगर ((req->chan_base + req->chan_cnt) > 15)
			वापस -EINVAL;
		rvu_get_cgx_lmac_id(pfvf->cgx_lmac, &cgx_id, &lmac_id);
		/* Assign bpid based on cgx, lmac and chan id */
		bpid = (cgx_id * hw->lmac_per_cgx * lmac_chan_cnt) +
			(lmac_id * lmac_chan_cnt) + req->chan_base;

		अगर (req->bpid_per_chan)
			bpid += chan_id;
		अगर (bpid > cgx_bpid_cnt)
			वापस -EINVAL;
		अवरोध;

	हाल NIX_INTF_TYPE_LBK:
		अगर ((req->chan_base + req->chan_cnt) > 63)
			वापस -EINVAL;
		bpid = cgx_bpid_cnt + req->chan_base;
		अगर (req->bpid_per_chan)
			bpid += chan_id;
		अगर (bpid > (cgx_bpid_cnt + lbk_bpid_cnt))
			वापस -EINVAL;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण
	वापस bpid;
पूर्ण

पूर्णांक rvu_mbox_handler_nix_bp_enable(काष्ठा rvu *rvu,
				   काष्ठा nix_bp_cfg_req *req,
				   काष्ठा nix_bp_cfg_rsp *rsp)
अणु
	पूर्णांक blkaddr, pf, type, chan_id = 0;
	u16 pcअगरunc = req->hdr.pcअगरunc;
	काष्ठा rvu_pfvf *pfvf;
	u16 chan_base, chan;
	s16 bpid, bpid_base;
	u64 cfg;

	pf = rvu_get_pf(pcअगरunc);
	type = is_afvf(pcअगरunc) ? NIX_INTF_TYPE_LBK : NIX_INTF_TYPE_CGX;

	/* Enable backpressure only क्रम CGX mapped PFs and LBK पूर्णांकerface */
	अगर (!is_pf_cgxmapped(rvu, pf) && type != NIX_INTF_TYPE_LBK)
		वापस 0;

	pfvf = rvu_get_pfvf(rvu, pcअगरunc);
	blkaddr = rvu_get_blkaddr(rvu, BLKTYPE_NIX, pcअगरunc);

	bpid_base = rvu_nix_get_bpid(rvu, req, type, chan_id);
	chan_base = pfvf->rx_chan_base + req->chan_base;
	bpid = bpid_base;

	क्रम (chan = chan_base; chan < (chan_base + req->chan_cnt); chan++) अणु
		अगर (bpid < 0) अणु
			dev_warn(rvu->dev, "Fail to enable backpressure\n");
			वापस -EINVAL;
		पूर्ण

		cfg = rvu_पढ़ो64(rvu, blkaddr, NIX_AF_RX_CHANX_CFG(chan));
		rvu_ग_लिखो64(rvu, blkaddr, NIX_AF_RX_CHANX_CFG(chan),
			    cfg | (bpid & 0xFF) | BIT_ULL(16));
		chan_id++;
		bpid = rvu_nix_get_bpid(rvu, req, type, chan_id);
	पूर्ण

	क्रम (chan = 0; chan < req->chan_cnt; chan++) अणु
		/* Map channel and bpid assign to it */
		rsp->chan_bpid[chan] = ((req->chan_base + chan) & 0x7F) << 10 |
					(bpid_base & 0x3FF);
		अगर (req->bpid_per_chan)
			bpid_base++;
	पूर्ण
	rsp->chan_cnt = req->chan_cnt;

	वापस 0;
पूर्ण

अटल व्योम nix_setup_lso_tso_l3(काष्ठा rvu *rvu, पूर्णांक blkaddr,
				 u64 क्रमmat, bool v4, u64 *fidx)
अणु
	काष्ठा nix_lso_क्रमmat field = अणु0पूर्ण;

	/* IP's Length field */
	field.layer = NIX_TXLAYER_OL3;
	/* In ipv4, length field is at offset 2 bytes, क्रम ipv6 it's 4 */
	field.offset = v4 ? 2 : 4;
	field.sizem1 = 1; /* i.e 2 bytes */
	field.alg = NIX_LSOALG_ADD_PAYLEN;
	rvu_ग_लिखो64(rvu, blkaddr,
		    NIX_AF_LSO_FORMATX_FIELDX(क्रमmat, (*fidx)++),
		    *(u64 *)&field);

	/* No ID field in IPv6 header */
	अगर (!v4)
		वापस;

	/* IP's ID field */
	field.layer = NIX_TXLAYER_OL3;
	field.offset = 4;
	field.sizem1 = 1; /* i.e 2 bytes */
	field.alg = NIX_LSOALG_ADD_SEGNUM;
	rvu_ग_लिखो64(rvu, blkaddr,
		    NIX_AF_LSO_FORMATX_FIELDX(क्रमmat, (*fidx)++),
		    *(u64 *)&field);
पूर्ण

अटल व्योम nix_setup_lso_tso_l4(काष्ठा rvu *rvu, पूर्णांक blkaddr,
				 u64 क्रमmat, u64 *fidx)
अणु
	काष्ठा nix_lso_क्रमmat field = अणु0पूर्ण;

	/* TCP's sequence number field */
	field.layer = NIX_TXLAYER_OL4;
	field.offset = 4;
	field.sizem1 = 3; /* i.e 4 bytes */
	field.alg = NIX_LSOALG_ADD_OFFSET;
	rvu_ग_लिखो64(rvu, blkaddr,
		    NIX_AF_LSO_FORMATX_FIELDX(क्रमmat, (*fidx)++),
		    *(u64 *)&field);

	/* TCP's flags field */
	field.layer = NIX_TXLAYER_OL4;
	field.offset = 12;
	field.sizem1 = 1; /* 2 bytes */
	field.alg = NIX_LSOALG_TCP_FLAGS;
	rvu_ग_लिखो64(rvu, blkaddr,
		    NIX_AF_LSO_FORMATX_FIELDX(क्रमmat, (*fidx)++),
		    *(u64 *)&field);
पूर्ण

अटल व्योम nix_setup_lso(काष्ठा rvu *rvu, काष्ठा nix_hw *nix_hw, पूर्णांक blkaddr)
अणु
	u64 cfg, idx, fidx = 0;

	/* Get max HW supported क्रमmat indices */
	cfg = (rvu_पढ़ो64(rvu, blkaddr, NIX_AF_CONST1) >> 48) & 0xFF;
	nix_hw->lso.total = cfg;

	/* Enable LSO */
	cfg = rvu_पढ़ो64(rvu, blkaddr, NIX_AF_LSO_CFG);
	/* For TSO, set first and middle segment flags to
	 * mask out PSH, RST & FIN flags in TCP packet
	 */
	cfg &= ~((0xFFFFULL << 32) | (0xFFFFULL << 16));
	cfg |= (0xFFF2ULL << 32) | (0xFFF2ULL << 16);
	rvu_ग_लिखो64(rvu, blkaddr, NIX_AF_LSO_CFG, cfg | BIT_ULL(63));

	/* Setup शेष अटल LSO क्रमmats
	 *
	 * Configure क्रमmat fields क्रम TCPv4 segmentation offload
	 */
	idx = NIX_LSO_FORMAT_IDX_TSOV4;
	nix_setup_lso_tso_l3(rvu, blkaddr, idx, true, &fidx);
	nix_setup_lso_tso_l4(rvu, blkaddr, idx, &fidx);

	/* Set rest of the fields to NOP */
	क्रम (; fidx < 8; fidx++) अणु
		rvu_ग_लिखो64(rvu, blkaddr,
			    NIX_AF_LSO_FORMATX_FIELDX(idx, fidx), 0x0ULL);
	पूर्ण
	nix_hw->lso.in_use++;

	/* Configure क्रमmat fields क्रम TCPv6 segmentation offload */
	idx = NIX_LSO_FORMAT_IDX_TSOV6;
	fidx = 0;
	nix_setup_lso_tso_l3(rvu, blkaddr, idx, false, &fidx);
	nix_setup_lso_tso_l4(rvu, blkaddr, idx, &fidx);

	/* Set rest of the fields to NOP */
	क्रम (; fidx < 8; fidx++) अणु
		rvu_ग_लिखो64(rvu, blkaddr,
			    NIX_AF_LSO_FORMATX_FIELDX(idx, fidx), 0x0ULL);
	पूर्ण
	nix_hw->lso.in_use++;
पूर्ण

अटल व्योम nix_ctx_मुक्त(काष्ठा rvu *rvu, काष्ठा rvu_pfvf *pfvf)
अणु
	kमुक्त(pfvf->rq_bmap);
	kमुक्त(pfvf->sq_bmap);
	kमुक्त(pfvf->cq_bmap);
	अगर (pfvf->rq_ctx)
		qmem_मुक्त(rvu->dev, pfvf->rq_ctx);
	अगर (pfvf->sq_ctx)
		qmem_मुक्त(rvu->dev, pfvf->sq_ctx);
	अगर (pfvf->cq_ctx)
		qmem_मुक्त(rvu->dev, pfvf->cq_ctx);
	अगर (pfvf->rss_ctx)
		qmem_मुक्त(rvu->dev, pfvf->rss_ctx);
	अगर (pfvf->nix_qपूर्णांकs_ctx)
		qmem_मुक्त(rvu->dev, pfvf->nix_qपूर्णांकs_ctx);
	अगर (pfvf->cq_पूर्णांकs_ctx)
		qmem_मुक्त(rvu->dev, pfvf->cq_पूर्णांकs_ctx);

	pfvf->rq_bmap = शून्य;
	pfvf->cq_bmap = शून्य;
	pfvf->sq_bmap = शून्य;
	pfvf->rq_ctx = शून्य;
	pfvf->sq_ctx = शून्य;
	pfvf->cq_ctx = शून्य;
	pfvf->rss_ctx = शून्य;
	pfvf->nix_qपूर्णांकs_ctx = शून्य;
	pfvf->cq_पूर्णांकs_ctx = शून्य;
पूर्ण

अटल पूर्णांक nixlf_rss_ctx_init(काष्ठा rvu *rvu, पूर्णांक blkaddr,
			      काष्ठा rvu_pfvf *pfvf, पूर्णांक nixlf,
			      पूर्णांक rss_sz, पूर्णांक rss_grps, पूर्णांक hwctx_size,
			      u64 way_mask)
अणु
	पूर्णांक err, grp, num_indices;

	/* RSS is not requested क्रम this NIXLF */
	अगर (!rss_sz)
		वापस 0;
	num_indices = rss_sz * rss_grps;

	/* Alloc NIX RSS HW context memory and config the base */
	err = qmem_alloc(rvu->dev, &pfvf->rss_ctx, num_indices, hwctx_size);
	अगर (err)
		वापस err;

	rvu_ग_लिखो64(rvu, blkaddr, NIX_AF_LFX_RSS_BASE(nixlf),
		    (u64)pfvf->rss_ctx->iova);

	/* Config full RSS table size, enable RSS and caching */
	rvu_ग_लिखो64(rvu, blkaddr, NIX_AF_LFX_RSS_CFG(nixlf),
		    BIT_ULL(36) | BIT_ULL(4) |
		    ilog2(num_indices / MAX_RSS_INसूची_TBL_SIZE) |
		    way_mask << 20);
	/* Config RSS group offset and sizes */
	क्रम (grp = 0; grp < rss_grps; grp++)
		rvu_ग_लिखो64(rvu, blkaddr, NIX_AF_LFX_RSS_GRPX(nixlf, grp),
			    ((ilog2(rss_sz) - 1) << 16) | (rss_sz * grp));
	वापस 0;
पूर्ण

अटल पूर्णांक nix_aq_enqueue_रुको(काष्ठा rvu *rvu, काष्ठा rvu_block *block,
			       काष्ठा nix_aq_inst_s *inst)
अणु
	काष्ठा admin_queue *aq = block->aq;
	काष्ठा nix_aq_res_s *result;
	पूर्णांक समयout = 1000;
	u64 reg, head;

	result = (काष्ठा nix_aq_res_s *)aq->res->base;

	/* Get current head poपूर्णांकer where to append this inकाष्ठाion */
	reg = rvu_पढ़ो64(rvu, block->addr, NIX_AF_AQ_STATUS);
	head = (reg >> 4) & AQ_PTR_MASK;

	स_नकल((व्योम *)(aq->inst->base + (head * aq->inst->entry_sz)),
	       (व्योम *)inst, aq->inst->entry_sz);
	स_रखो(result, 0, माप(*result));
	/* sync पूर्णांकo memory */
	wmb();

	/* Ring the करोorbell and रुको क्रम result */
	rvu_ग_लिखो64(rvu, block->addr, NIX_AF_AQ_DOOR, 1);
	जबतक (result->compcode == NIX_AQ_COMP_NOTDONE) अणु
		cpu_relax();
		udelay(1);
		समयout--;
		अगर (!समयout)
			वापस -EBUSY;
	पूर्ण

	अगर (result->compcode != NIX_AQ_COMP_GOOD)
		/* TODO: Replace this with some error code */
		वापस -EBUSY;

	वापस 0;
पूर्ण

अटल पूर्णांक rvu_nix_blk_aq_enq_inst(काष्ठा rvu *rvu, काष्ठा nix_hw *nix_hw,
				   काष्ठा nix_aq_enq_req *req,
				   काष्ठा nix_aq_enq_rsp *rsp)
अणु
	काष्ठा rvu_hwinfo *hw = rvu->hw;
	u16 pcअगरunc = req->hdr.pcअगरunc;
	पूर्णांक nixlf, blkaddr, rc = 0;
	काष्ठा nix_aq_inst_s inst;
	काष्ठा rvu_block *block;
	काष्ठा admin_queue *aq;
	काष्ठा rvu_pfvf *pfvf;
	व्योम *ctx, *mask;
	bool ena;
	u64 cfg;

	blkaddr = nix_hw->blkaddr;
	block = &hw->block[blkaddr];
	aq = block->aq;
	अगर (!aq) अणु
		dev_warn(rvu->dev, "%s: NIX AQ not initialized\n", __func__);
		वापस NIX_AF_ERR_AQ_ENQUEUE;
	पूर्ण

	pfvf = rvu_get_pfvf(rvu, pcअगरunc);
	nixlf = rvu_get_lf(rvu, block, pcअगरunc, 0);

	/* Skip NIXLF check क्रम broadcast MCE entry init */
	अगर (!(!rsp && req->ctype == NIX_AQ_CTYPE_MCE)) अणु
		अगर (!pfvf->nixlf || nixlf < 0)
			वापस NIX_AF_ERR_AF_LF_INVALID;
	पूर्ण

	चयन (req->ctype) अणु
	हाल NIX_AQ_CTYPE_RQ:
		/* Check अगर index exceeds max no of queues */
		अगर (!pfvf->rq_ctx || req->qidx >= pfvf->rq_ctx->qsize)
			rc = NIX_AF_ERR_AQ_ENQUEUE;
		अवरोध;
	हाल NIX_AQ_CTYPE_SQ:
		अगर (!pfvf->sq_ctx || req->qidx >= pfvf->sq_ctx->qsize)
			rc = NIX_AF_ERR_AQ_ENQUEUE;
		अवरोध;
	हाल NIX_AQ_CTYPE_CQ:
		अगर (!pfvf->cq_ctx || req->qidx >= pfvf->cq_ctx->qsize)
			rc = NIX_AF_ERR_AQ_ENQUEUE;
		अवरोध;
	हाल NIX_AQ_CTYPE_RSS:
		/* Check अगर RSS is enabled and qidx is within range */
		cfg = rvu_पढ़ो64(rvu, blkaddr, NIX_AF_LFX_RSS_CFG(nixlf));
		अगर (!(cfg & BIT_ULL(4)) || !pfvf->rss_ctx ||
		    (req->qidx >= (256UL << (cfg & 0xF))))
			rc = NIX_AF_ERR_AQ_ENQUEUE;
		अवरोध;
	हाल NIX_AQ_CTYPE_MCE:
		cfg = rvu_पढ़ो64(rvu, blkaddr, NIX_AF_RX_MCAST_CFG);

		/* Check अगर index exceeds MCE list length */
		अगर (!nix_hw->mcast.mce_ctx ||
		    (req->qidx >= (256UL << (cfg & 0xF))))
			rc = NIX_AF_ERR_AQ_ENQUEUE;

		/* Adding multicast lists क्रम requests from PF/VFs is not
		 * yet supported, so ignore this.
		 */
		अगर (rsp)
			rc = NIX_AF_ERR_AQ_ENQUEUE;
		अवरोध;
	शेष:
		rc = NIX_AF_ERR_AQ_ENQUEUE;
	पूर्ण

	अगर (rc)
		वापस rc;

	/* Check अगर SQ poपूर्णांकed SMQ beदीर्घs to this PF/VF or not */
	अगर (req->ctype == NIX_AQ_CTYPE_SQ &&
	    ((req->op == NIX_AQ_INSTOP_INIT && req->sq.ena) ||
	     (req->op == NIX_AQ_INSTOP_WRITE &&
	      req->sq_mask.ena && req->sq_mask.smq && req->sq.ena))) अणु
		अगर (!is_valid_txschq(rvu, blkaddr, NIX_TXSCH_LVL_SMQ,
				     pcअगरunc, req->sq.smq))
			वापस NIX_AF_ERR_AQ_ENQUEUE;
	पूर्ण

	स_रखो(&inst, 0, माप(काष्ठा nix_aq_inst_s));
	inst.lf = nixlf;
	inst.cindex = req->qidx;
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
	हाल NIX_AQ_INSTOP_WRITE:
		अगर (req->ctype == NIX_AQ_CTYPE_RQ)
			स_नकल(mask, &req->rq_mask,
			       माप(काष्ठा nix_rq_ctx_s));
		अन्यथा अगर (req->ctype == NIX_AQ_CTYPE_SQ)
			स_नकल(mask, &req->sq_mask,
			       माप(काष्ठा nix_sq_ctx_s));
		अन्यथा अगर (req->ctype == NIX_AQ_CTYPE_CQ)
			स_नकल(mask, &req->cq_mask,
			       माप(काष्ठा nix_cq_ctx_s));
		अन्यथा अगर (req->ctype == NIX_AQ_CTYPE_RSS)
			स_नकल(mask, &req->rss_mask,
			       माप(काष्ठा nix_rsse_s));
		अन्यथा अगर (req->ctype == NIX_AQ_CTYPE_MCE)
			स_नकल(mask, &req->mce_mask,
			       माप(काष्ठा nix_rx_mce_s));
		fallthrough;
	हाल NIX_AQ_INSTOP_INIT:
		अगर (req->ctype == NIX_AQ_CTYPE_RQ)
			स_नकल(ctx, &req->rq, माप(काष्ठा nix_rq_ctx_s));
		अन्यथा अगर (req->ctype == NIX_AQ_CTYPE_SQ)
			स_नकल(ctx, &req->sq, माप(काष्ठा nix_sq_ctx_s));
		अन्यथा अगर (req->ctype == NIX_AQ_CTYPE_CQ)
			स_नकल(ctx, &req->cq, माप(काष्ठा nix_cq_ctx_s));
		अन्यथा अगर (req->ctype == NIX_AQ_CTYPE_RSS)
			स_नकल(ctx, &req->rss, माप(काष्ठा nix_rsse_s));
		अन्यथा अगर (req->ctype == NIX_AQ_CTYPE_MCE)
			स_नकल(ctx, &req->mce, माप(काष्ठा nix_rx_mce_s));
		अवरोध;
	हाल NIX_AQ_INSTOP_NOP:
	हाल NIX_AQ_INSTOP_READ:
	हाल NIX_AQ_INSTOP_LOCK:
	हाल NIX_AQ_INSTOP_UNLOCK:
		अवरोध;
	शेष:
		rc = NIX_AF_ERR_AQ_ENQUEUE;
		spin_unlock(&aq->lock);
		वापस rc;
	पूर्ण

	/* Submit the inकाष्ठाion to AQ */
	rc = nix_aq_enqueue_रुको(rvu, block, &inst);
	अगर (rc) अणु
		spin_unlock(&aq->lock);
		वापस rc;
	पूर्ण

	/* Set RQ/SQ/CQ biपंचांगap अगर respective queue hw context is enabled */
	अगर (req->op == NIX_AQ_INSTOP_INIT) अणु
		अगर (req->ctype == NIX_AQ_CTYPE_RQ && req->rq.ena)
			__set_bit(req->qidx, pfvf->rq_bmap);
		अगर (req->ctype == NIX_AQ_CTYPE_SQ && req->sq.ena)
			__set_bit(req->qidx, pfvf->sq_bmap);
		अगर (req->ctype == NIX_AQ_CTYPE_CQ && req->cq.ena)
			__set_bit(req->qidx, pfvf->cq_bmap);
	पूर्ण

	अगर (req->op == NIX_AQ_INSTOP_WRITE) अणु
		अगर (req->ctype == NIX_AQ_CTYPE_RQ) अणु
			ena = (req->rq.ena & req->rq_mask.ena) |
				(test_bit(req->qidx, pfvf->rq_bmap) &
				~req->rq_mask.ena);
			अगर (ena)
				__set_bit(req->qidx, pfvf->rq_bmap);
			अन्यथा
				__clear_bit(req->qidx, pfvf->rq_bmap);
		पूर्ण
		अगर (req->ctype == NIX_AQ_CTYPE_SQ) अणु
			ena = (req->rq.ena & req->sq_mask.ena) |
				(test_bit(req->qidx, pfvf->sq_bmap) &
				~req->sq_mask.ena);
			अगर (ena)
				__set_bit(req->qidx, pfvf->sq_bmap);
			अन्यथा
				__clear_bit(req->qidx, pfvf->sq_bmap);
		पूर्ण
		अगर (req->ctype == NIX_AQ_CTYPE_CQ) अणु
			ena = (req->rq.ena & req->cq_mask.ena) |
				(test_bit(req->qidx, pfvf->cq_bmap) &
				~req->cq_mask.ena);
			अगर (ena)
				__set_bit(req->qidx, pfvf->cq_bmap);
			अन्यथा
				__clear_bit(req->qidx, pfvf->cq_bmap);
		पूर्ण
	पूर्ण

	अगर (rsp) अणु
		/* Copy पढ़ो context पूर्णांकo mailbox */
		अगर (req->op == NIX_AQ_INSTOP_READ) अणु
			अगर (req->ctype == NIX_AQ_CTYPE_RQ)
				स_नकल(&rsp->rq, ctx,
				       माप(काष्ठा nix_rq_ctx_s));
			अन्यथा अगर (req->ctype == NIX_AQ_CTYPE_SQ)
				स_नकल(&rsp->sq, ctx,
				       माप(काष्ठा nix_sq_ctx_s));
			अन्यथा अगर (req->ctype == NIX_AQ_CTYPE_CQ)
				स_नकल(&rsp->cq, ctx,
				       माप(काष्ठा nix_cq_ctx_s));
			अन्यथा अगर (req->ctype == NIX_AQ_CTYPE_RSS)
				स_नकल(&rsp->rss, ctx,
				       माप(काष्ठा nix_rsse_s));
			अन्यथा अगर (req->ctype == NIX_AQ_CTYPE_MCE)
				स_नकल(&rsp->mce, ctx,
				       माप(काष्ठा nix_rx_mce_s));
		पूर्ण
	पूर्ण

	spin_unlock(&aq->lock);
	वापस 0;
पूर्ण

अटल पूर्णांक rvu_nix_aq_enq_inst(काष्ठा rvu *rvu, काष्ठा nix_aq_enq_req *req,
			       काष्ठा nix_aq_enq_rsp *rsp)
अणु
	काष्ठा nix_hw *nix_hw;
	पूर्णांक blkaddr;

	blkaddr = rvu_get_blkaddr(rvu, BLKTYPE_NIX, req->hdr.pcअगरunc);
	अगर (blkaddr < 0)
		वापस NIX_AF_ERR_AF_LF_INVALID;

	nix_hw =  get_nix_hw(rvu->hw, blkaddr);
	अगर (!nix_hw)
		वापस -EINVAL;

	वापस rvu_nix_blk_aq_enq_inst(rvu, nix_hw, req, rsp);
पूर्ण

अटल स्थिर अक्षर *nix_get_ctx_name(पूर्णांक ctype)
अणु
	चयन (ctype) अणु
	हाल NIX_AQ_CTYPE_CQ:
		वापस "CQ";
	हाल NIX_AQ_CTYPE_SQ:
		वापस "SQ";
	हाल NIX_AQ_CTYPE_RQ:
		वापस "RQ";
	हाल NIX_AQ_CTYPE_RSS:
		वापस "RSS";
	पूर्ण
	वापस "";
पूर्ण

अटल पूर्णांक nix_lf_hwctx_disable(काष्ठा rvu *rvu, काष्ठा hwctx_disable_req *req)
अणु
	काष्ठा rvu_pfvf *pfvf = rvu_get_pfvf(rvu, req->hdr.pcअगरunc);
	काष्ठा nix_aq_enq_req aq_req;
	अचिन्हित दीर्घ *bmap;
	पूर्णांक qidx, q_cnt = 0;
	पूर्णांक err = 0, rc;

	अगर (!pfvf->cq_ctx || !pfvf->sq_ctx || !pfvf->rq_ctx)
		वापस NIX_AF_ERR_AQ_ENQUEUE;

	स_रखो(&aq_req, 0, माप(काष्ठा nix_aq_enq_req));
	aq_req.hdr.pcअगरunc = req->hdr.pcअगरunc;

	अगर (req->ctype == NIX_AQ_CTYPE_CQ) अणु
		aq_req.cq.ena = 0;
		aq_req.cq_mask.ena = 1;
		aq_req.cq.bp_ena = 0;
		aq_req.cq_mask.bp_ena = 1;
		q_cnt = pfvf->cq_ctx->qsize;
		bmap = pfvf->cq_bmap;
	पूर्ण
	अगर (req->ctype == NIX_AQ_CTYPE_SQ) अणु
		aq_req.sq.ena = 0;
		aq_req.sq_mask.ena = 1;
		q_cnt = pfvf->sq_ctx->qsize;
		bmap = pfvf->sq_bmap;
	पूर्ण
	अगर (req->ctype == NIX_AQ_CTYPE_RQ) अणु
		aq_req.rq.ena = 0;
		aq_req.rq_mask.ena = 1;
		q_cnt = pfvf->rq_ctx->qsize;
		bmap = pfvf->rq_bmap;
	पूर्ण

	aq_req.ctype = req->ctype;
	aq_req.op = NIX_AQ_INSTOP_WRITE;

	क्रम (qidx = 0; qidx < q_cnt; qidx++) अणु
		अगर (!test_bit(qidx, bmap))
			जारी;
		aq_req.qidx = qidx;
		rc = rvu_nix_aq_enq_inst(rvu, &aq_req, शून्य);
		अगर (rc) अणु
			err = rc;
			dev_err(rvu->dev, "Failed to disable %s:%d context\n",
				nix_get_ctx_name(req->ctype), qidx);
		पूर्ण
	पूर्ण

	वापस err;
पूर्ण

#अगर_घोषित CONFIG_NDC_DIS_DYNAMIC_CACHING
अटल पूर्णांक nix_lf_hwctx_lockकरोwn(काष्ठा rvu *rvu, काष्ठा nix_aq_enq_req *req)
अणु
	काष्ठा nix_aq_enq_req lock_ctx_req;
	पूर्णांक err;

	अगर (req->op != NIX_AQ_INSTOP_INIT)
		वापस 0;

	अगर (req->ctype == NIX_AQ_CTYPE_MCE ||
	    req->ctype == NIX_AQ_CTYPE_DYNO)
		वापस 0;

	स_रखो(&lock_ctx_req, 0, माप(काष्ठा nix_aq_enq_req));
	lock_ctx_req.hdr.pcअगरunc = req->hdr.pcअगरunc;
	lock_ctx_req.ctype = req->ctype;
	lock_ctx_req.op = NIX_AQ_INSTOP_LOCK;
	lock_ctx_req.qidx = req->qidx;
	err = rvu_nix_aq_enq_inst(rvu, &lock_ctx_req, शून्य);
	अगर (err)
		dev_err(rvu->dev,
			"PFUNC 0x%x: Failed to lock NIX %s:%d context\n",
			req->hdr.pcअगरunc,
			nix_get_ctx_name(req->ctype), req->qidx);
	वापस err;
पूर्ण

पूर्णांक rvu_mbox_handler_nix_aq_enq(काष्ठा rvu *rvu,
				काष्ठा nix_aq_enq_req *req,
				काष्ठा nix_aq_enq_rsp *rsp)
अणु
	पूर्णांक err;

	err = rvu_nix_aq_enq_inst(rvu, req, rsp);
	अगर (!err)
		err = nix_lf_hwctx_lockकरोwn(rvu, req);
	वापस err;
पूर्ण
#अन्यथा

पूर्णांक rvu_mbox_handler_nix_aq_enq(काष्ठा rvu *rvu,
				काष्ठा nix_aq_enq_req *req,
				काष्ठा nix_aq_enq_rsp *rsp)
अणु
	वापस rvu_nix_aq_enq_inst(rvu, req, rsp);
पूर्ण
#पूर्ण_अगर
/* CN10K mbox handler */
पूर्णांक rvu_mbox_handler_nix_cn10k_aq_enq(काष्ठा rvu *rvu,
				      काष्ठा nix_cn10k_aq_enq_req *req,
				      काष्ठा nix_cn10k_aq_enq_rsp *rsp)
अणु
	वापस rvu_nix_aq_enq_inst(rvu, (काष्ठा nix_aq_enq_req *)req,
				  (काष्ठा nix_aq_enq_rsp *)rsp);
पूर्ण

पूर्णांक rvu_mbox_handler_nix_hwctx_disable(काष्ठा rvu *rvu,
				       काष्ठा hwctx_disable_req *req,
				       काष्ठा msg_rsp *rsp)
अणु
	वापस nix_lf_hwctx_disable(rvu, req);
पूर्ण

पूर्णांक rvu_mbox_handler_nix_lf_alloc(काष्ठा rvu *rvu,
				  काष्ठा nix_lf_alloc_req *req,
				  काष्ठा nix_lf_alloc_rsp *rsp)
अणु
	पूर्णांक nixlf, qपूर्णांकs, hwctx_size, पूर्णांकf, err, rc = 0;
	काष्ठा rvu_hwinfo *hw = rvu->hw;
	u16 pcअगरunc = req->hdr.pcअगरunc;
	काष्ठा rvu_block *block;
	काष्ठा rvu_pfvf *pfvf;
	u64 cfg, ctx_cfg;
	पूर्णांक blkaddr;

	अगर (!req->rq_cnt || !req->sq_cnt || !req->cq_cnt)
		वापस NIX_AF_ERR_PARAM;

	अगर (req->way_mask)
		req->way_mask &= 0xFFFF;

	pfvf = rvu_get_pfvf(rvu, pcअगरunc);
	blkaddr = rvu_get_blkaddr(rvu, BLKTYPE_NIX, pcअगरunc);
	अगर (!pfvf->nixlf || blkaddr < 0)
		वापस NIX_AF_ERR_AF_LF_INVALID;

	block = &hw->block[blkaddr];
	nixlf = rvu_get_lf(rvu, block, pcअगरunc, 0);
	अगर (nixlf < 0)
		वापस NIX_AF_ERR_AF_LF_INVALID;

	/* Check अगर requested 'NIXLF <=> NPALF' mapping is valid */
	अगर (req->npa_func) अणु
		/* If शेष, use 'this' NIXLF's PFFUNC */
		अगर (req->npa_func == RVU_DEFAULT_PF_FUNC)
			req->npa_func = pcअगरunc;
		अगर (!is_pffunc_map_valid(rvu, req->npa_func, BLKTYPE_NPA))
			वापस NIX_AF_INVAL_NPA_PF_FUNC;
	पूर्ण

	/* Check अगर requested 'NIXLF <=> SSOLF' mapping is valid */
	अगर (req->sso_func) अणु
		/* If शेष, use 'this' NIXLF's PFFUNC */
		अगर (req->sso_func == RVU_DEFAULT_PF_FUNC)
			req->sso_func = pcअगरunc;
		अगर (!is_pffunc_map_valid(rvu, req->sso_func, BLKTYPE_SSO))
			वापस NIX_AF_INVAL_SSO_PF_FUNC;
	पूर्ण

	/* If RSS is being enabled, check अगर requested config is valid.
	 * RSS table size should be घातer of two, otherwise
	 * RSS_GRP::OFFSET + adder might go beyond that group or
	 * won't be able to use entire table.
	 */
	अगर (req->rss_sz && (req->rss_sz > MAX_RSS_INसूची_TBL_SIZE ||
			    !is_घातer_of_2(req->rss_sz)))
		वापस NIX_AF_ERR_RSS_SIZE_INVALID;

	अगर (req->rss_sz &&
	    (!req->rss_grps || req->rss_grps > MAX_RSS_GROUPS))
		वापस NIX_AF_ERR_RSS_GRPS_INVALID;

	/* Reset this NIX LF */
	err = rvu_lf_reset(rvu, block, nixlf);
	अगर (err) अणु
		dev_err(rvu->dev, "Failed to reset NIX%d LF%d\n",
			block->addr - BLKADDR_NIX0, nixlf);
		वापस NIX_AF_ERR_LF_RESET;
	पूर्ण

	ctx_cfg = rvu_पढ़ो64(rvu, blkaddr, NIX_AF_CONST3);

	/* Alloc NIX RQ HW context memory and config the base */
	hwctx_size = 1UL << ((ctx_cfg >> 4) & 0xF);
	err = qmem_alloc(rvu->dev, &pfvf->rq_ctx, req->rq_cnt, hwctx_size);
	अगर (err)
		जाओ मुक्त_mem;

	pfvf->rq_bmap = kसुस्मृति(req->rq_cnt, माप(दीर्घ), GFP_KERNEL);
	अगर (!pfvf->rq_bmap)
		जाओ मुक्त_mem;

	rvu_ग_लिखो64(rvu, blkaddr, NIX_AF_LFX_RQS_BASE(nixlf),
		    (u64)pfvf->rq_ctx->iova);

	/* Set caching and queue count in HW */
	cfg = BIT_ULL(36) | (req->rq_cnt - 1) | req->way_mask << 20;
	rvu_ग_लिखो64(rvu, blkaddr, NIX_AF_LFX_RQS_CFG(nixlf), cfg);

	/* Alloc NIX SQ HW context memory and config the base */
	hwctx_size = 1UL << (ctx_cfg & 0xF);
	err = qmem_alloc(rvu->dev, &pfvf->sq_ctx, req->sq_cnt, hwctx_size);
	अगर (err)
		जाओ मुक्त_mem;

	pfvf->sq_bmap = kसुस्मृति(req->sq_cnt, माप(दीर्घ), GFP_KERNEL);
	अगर (!pfvf->sq_bmap)
		जाओ मुक्त_mem;

	rvu_ग_लिखो64(rvu, blkaddr, NIX_AF_LFX_SQS_BASE(nixlf),
		    (u64)pfvf->sq_ctx->iova);

	cfg = BIT_ULL(36) | (req->sq_cnt - 1) | req->way_mask << 20;
	rvu_ग_लिखो64(rvu, blkaddr, NIX_AF_LFX_SQS_CFG(nixlf), cfg);

	/* Alloc NIX CQ HW context memory and config the base */
	hwctx_size = 1UL << ((ctx_cfg >> 8) & 0xF);
	err = qmem_alloc(rvu->dev, &pfvf->cq_ctx, req->cq_cnt, hwctx_size);
	अगर (err)
		जाओ मुक्त_mem;

	pfvf->cq_bmap = kसुस्मृति(req->cq_cnt, माप(दीर्घ), GFP_KERNEL);
	अगर (!pfvf->cq_bmap)
		जाओ मुक्त_mem;

	rvu_ग_लिखो64(rvu, blkaddr, NIX_AF_LFX_CQS_BASE(nixlf),
		    (u64)pfvf->cq_ctx->iova);

	cfg = BIT_ULL(36) | (req->cq_cnt - 1) | req->way_mask << 20;
	rvu_ग_लिखो64(rvu, blkaddr, NIX_AF_LFX_CQS_CFG(nixlf), cfg);

	/* Initialize receive side scaling (RSS) */
	hwctx_size = 1UL << ((ctx_cfg >> 12) & 0xF);
	err = nixlf_rss_ctx_init(rvu, blkaddr, pfvf, nixlf, req->rss_sz,
				 req->rss_grps, hwctx_size, req->way_mask);
	अगर (err)
		जाओ मुक्त_mem;

	/* Alloc memory क्रम CQINT's HW contexts */
	cfg = rvu_पढ़ो64(rvu, blkaddr, NIX_AF_CONST2);
	qपूर्णांकs = (cfg >> 24) & 0xFFF;
	hwctx_size = 1UL << ((ctx_cfg >> 24) & 0xF);
	err = qmem_alloc(rvu->dev, &pfvf->cq_पूर्णांकs_ctx, qपूर्णांकs, hwctx_size);
	अगर (err)
		जाओ मुक्त_mem;

	rvu_ग_लिखो64(rvu, blkaddr, NIX_AF_LFX_CINTS_BASE(nixlf),
		    (u64)pfvf->cq_पूर्णांकs_ctx->iova);

	rvu_ग_लिखो64(rvu, blkaddr, NIX_AF_LFX_CINTS_CFG(nixlf),
		    BIT_ULL(36) | req->way_mask << 20);

	/* Alloc memory क्रम QINT's HW contexts */
	cfg = rvu_पढ़ो64(rvu, blkaddr, NIX_AF_CONST2);
	qपूर्णांकs = (cfg >> 12) & 0xFFF;
	hwctx_size = 1UL << ((ctx_cfg >> 20) & 0xF);
	err = qmem_alloc(rvu->dev, &pfvf->nix_qपूर्णांकs_ctx, qपूर्णांकs, hwctx_size);
	अगर (err)
		जाओ मुक्त_mem;

	rvu_ग_लिखो64(rvu, blkaddr, NIX_AF_LFX_QINTS_BASE(nixlf),
		    (u64)pfvf->nix_qपूर्णांकs_ctx->iova);
	rvu_ग_लिखो64(rvu, blkaddr, NIX_AF_LFX_QINTS_CFG(nixlf),
		    BIT_ULL(36) | req->way_mask << 20);

	/* Setup VLANX TPID's.
	 * Use VLAN1 क्रम 802.1Q
	 * and VLAN0 क्रम 802.1AD.
	 */
	cfg = (0x8100ULL << 16) | 0x88A8ULL;
	rvu_ग_लिखो64(rvu, blkaddr, NIX_AF_LFX_TX_CFG(nixlf), cfg);

	/* Enable LMTST क्रम this NIX LF */
	rvu_ग_लिखो64(rvu, blkaddr, NIX_AF_LFX_TX_CFG2(nixlf), BIT_ULL(0));

	/* Set CQE/WQE size, NPA_PF_FUNC क्रम SQBs and also SSO_PF_FUNC */
	अगर (req->npa_func)
		cfg = req->npa_func;
	अगर (req->sso_func)
		cfg |= (u64)req->sso_func << 16;

	cfg |= (u64)req->xqe_sz << 33;
	rvu_ग_लिखो64(rvu, blkaddr, NIX_AF_LFX_CFG(nixlf), cfg);

	/* Config Rx pkt length, csum checks and apad  enable / disable */
	rvu_ग_लिखो64(rvu, blkaddr, NIX_AF_LFX_RX_CFG(nixlf), req->rx_cfg);

	/* Configure pkind क्रम TX parse config */
	cfg = NPC_TX_DEF_PKIND;
	rvu_ग_लिखो64(rvu, blkaddr, NIX_AF_LFX_TX_PARSE_CFG(nixlf), cfg);

	पूर्णांकf = is_afvf(pcअगरunc) ? NIX_INTF_TYPE_LBK : NIX_INTF_TYPE_CGX;
	err = nix_पूर्णांकerface_init(rvu, pcअगरunc, पूर्णांकf, nixlf);
	अगर (err)
		जाओ मुक्त_mem;

	/* Disable NPC entries as NIXLF's contexts are not initialized yet */
	rvu_npc_disable_शेष_entries(rvu, pcअगरunc, nixlf);

	/* Configure RX VTAG Type 7 (strip) क्रम vf vlan */
	rvu_ग_लिखो64(rvu, blkaddr,
		    NIX_AF_LFX_RX_VTAG_TYPEX(nixlf, NIX_AF_LFX_RX_VTAG_TYPE7),
		    VTAGSIZE_T4 | VTAG_STRIP);

	जाओ निकास;

मुक्त_mem:
	nix_ctx_मुक्त(rvu, pfvf);
	rc = -ENOMEM;

निकास:
	/* Set macaddr of this PF/VF */
	ether_addr_copy(rsp->mac_addr, pfvf->mac_addr);

	/* set SQB size info */
	cfg = rvu_पढ़ो64(rvu, blkaddr, NIX_AF_SQ_CONST);
	rsp->sqb_size = (cfg >> 34) & 0xFFFF;
	rsp->rx_chan_base = pfvf->rx_chan_base;
	rsp->tx_chan_base = pfvf->tx_chan_base;
	rsp->rx_chan_cnt = pfvf->rx_chan_cnt;
	rsp->tx_chan_cnt = pfvf->tx_chan_cnt;
	rsp->lso_tsov4_idx = NIX_LSO_FORMAT_IDX_TSOV4;
	rsp->lso_tsov6_idx = NIX_LSO_FORMAT_IDX_TSOV6;
	/* Get HW supported stat count */
	cfg = rvu_पढ़ो64(rvu, blkaddr, NIX_AF_CONST1);
	rsp->lf_rx_stats = ((cfg >> 32) & 0xFF);
	rsp->lf_tx_stats = ((cfg >> 24) & 0xFF);
	/* Get count of CQ IRQs and error IRQs supported per LF */
	cfg = rvu_पढ़ो64(rvu, blkaddr, NIX_AF_CONST2);
	rsp->qपूर्णांकs = ((cfg >> 12) & 0xFFF);
	rsp->cपूर्णांकs = ((cfg >> 24) & 0xFFF);
	rsp->cgx_links = hw->cgx_links;
	rsp->lbk_links = hw->lbk_links;
	rsp->sdp_links = hw->sdp_links;

	वापस rc;
पूर्ण

पूर्णांक rvu_mbox_handler_nix_lf_मुक्त(काष्ठा rvu *rvu, काष्ठा nix_lf_मुक्त_req *req,
				 काष्ठा msg_rsp *rsp)
अणु
	काष्ठा rvu_hwinfo *hw = rvu->hw;
	u16 pcअगरunc = req->hdr.pcअगरunc;
	काष्ठा rvu_block *block;
	पूर्णांक blkaddr, nixlf, err;
	काष्ठा rvu_pfvf *pfvf;

	pfvf = rvu_get_pfvf(rvu, pcअगरunc);
	blkaddr = rvu_get_blkaddr(rvu, BLKTYPE_NIX, pcअगरunc);
	अगर (!pfvf->nixlf || blkaddr < 0)
		वापस NIX_AF_ERR_AF_LF_INVALID;

	block = &hw->block[blkaddr];
	nixlf = rvu_get_lf(rvu, block, pcअगरunc, 0);
	अगर (nixlf < 0)
		वापस NIX_AF_ERR_AF_LF_INVALID;

	अगर (req->flags & NIX_LF_DISABLE_FLOWS)
		rvu_npc_disable_mcam_entries(rvu, pcअगरunc, nixlf);
	अन्यथा
		rvu_npc_मुक्त_mcam_entries(rvu, pcअगरunc, nixlf);

	/* Free any tx vtag def entries used by this NIX LF */
	अगर (!(req->flags & NIX_LF_DONT_FREE_TX_VTAG))
		nix_मुक्त_tx_vtag_entries(rvu, pcअगरunc);

	nix_पूर्णांकerface_deinit(rvu, pcअगरunc, nixlf);

	/* Reset this NIX LF */
	err = rvu_lf_reset(rvu, block, nixlf);
	अगर (err) अणु
		dev_err(rvu->dev, "Failed to reset NIX%d LF%d\n",
			block->addr - BLKADDR_NIX0, nixlf);
		वापस NIX_AF_ERR_LF_RESET;
	पूर्ण

	nix_ctx_मुक्त(rvu, pfvf);

	वापस 0;
पूर्ण

पूर्णांक rvu_mbox_handler_nix_mark_क्रमmat_cfg(काष्ठा rvu *rvu,
					 काष्ठा nix_mark_क्रमmat_cfg  *req,
					 काष्ठा nix_mark_क्रमmat_cfg_rsp *rsp)
अणु
	u16 pcअगरunc = req->hdr.pcअगरunc;
	काष्ठा nix_hw *nix_hw;
	काष्ठा rvu_pfvf *pfvf;
	पूर्णांक blkaddr, rc;
	u32 cfg;

	pfvf = rvu_get_pfvf(rvu, pcअगरunc);
	blkaddr = rvu_get_blkaddr(rvu, BLKTYPE_NIX, pcअगरunc);
	अगर (!pfvf->nixlf || blkaddr < 0)
		वापस NIX_AF_ERR_AF_LF_INVALID;

	nix_hw = get_nix_hw(rvu->hw, blkaddr);
	अगर (!nix_hw)
		वापस -EINVAL;

	cfg = (((u32)req->offset & 0x7) << 16) |
	      (((u32)req->y_mask & 0xF) << 12) |
	      (((u32)req->y_val & 0xF) << 8) |
	      (((u32)req->r_mask & 0xF) << 4) | ((u32)req->r_val & 0xF);

	rc = rvu_nix_reserve_mark_क्रमmat(rvu, nix_hw, blkaddr, cfg);
	अगर (rc < 0) अणु
		dev_err(rvu->dev, "No mark_format_ctl for (pf:%d, vf:%d)",
			rvu_get_pf(pcअगरunc), pcअगरunc & RVU_PFVF_FUNC_MASK);
		वापस NIX_AF_ERR_MARK_CFG_FAIL;
	पूर्ण

	rsp->mark_क्रमmat_idx = rc;
	वापस 0;
पूर्ण

/* Disable shaping of pkts by a scheduler queue
 * at a given scheduler level.
 */
अटल व्योम nix_reset_tx_shaping(काष्ठा rvu *rvu, पूर्णांक blkaddr,
				 पूर्णांक lvl, पूर्णांक schq)
अणु
	u64  cir_reg = 0, pir_reg = 0;
	u64  cfg;

	चयन (lvl) अणु
	हाल NIX_TXSCH_LVL_TL1:
		cir_reg = NIX_AF_TL1X_CIR(schq);
		pir_reg = 0; /* PIR not available at TL1 */
		अवरोध;
	हाल NIX_TXSCH_LVL_TL2:
		cir_reg = NIX_AF_TL2X_CIR(schq);
		pir_reg = NIX_AF_TL2X_PIR(schq);
		अवरोध;
	हाल NIX_TXSCH_LVL_TL3:
		cir_reg = NIX_AF_TL3X_CIR(schq);
		pir_reg = NIX_AF_TL3X_PIR(schq);
		अवरोध;
	हाल NIX_TXSCH_LVL_TL4:
		cir_reg = NIX_AF_TL4X_CIR(schq);
		pir_reg = NIX_AF_TL4X_PIR(schq);
		अवरोध;
	पूर्ण

	अगर (!cir_reg)
		वापस;
	cfg = rvu_पढ़ो64(rvu, blkaddr, cir_reg);
	rvu_ग_लिखो64(rvu, blkaddr, cir_reg, cfg & ~BIT_ULL(0));

	अगर (!pir_reg)
		वापस;
	cfg = rvu_पढ़ो64(rvu, blkaddr, pir_reg);
	rvu_ग_लिखो64(rvu, blkaddr, pir_reg, cfg & ~BIT_ULL(0));
पूर्ण

अटल व्योम nix_reset_tx_linkcfg(काष्ठा rvu *rvu, पूर्णांक blkaddr,
				 पूर्णांक lvl, पूर्णांक schq)
अणु
	काष्ठा rvu_hwinfo *hw = rvu->hw;
	पूर्णांक link;

	अगर (lvl >= hw->cap.nix_tx_aggr_lvl)
		वापस;

	/* Reset TL4's SDP link config */
	अगर (lvl == NIX_TXSCH_LVL_TL4)
		rvu_ग_लिखो64(rvu, blkaddr, NIX_AF_TL4X_SDP_LINK_CFG(schq), 0x00);

	अगर (lvl != NIX_TXSCH_LVL_TL2)
		वापस;

	/* Reset TL2's CGX or LBK link config */
	क्रम (link = 0; link < (hw->cgx_links + hw->lbk_links); link++)
		rvu_ग_लिखो64(rvu, blkaddr,
			    NIX_AF_TL3_TL2X_LINKX_CFG(schq, link), 0x00);
पूर्ण

अटल पूर्णांक nix_get_tx_link(काष्ठा rvu *rvu, u16 pcअगरunc)
अणु
	काष्ठा rvu_hwinfo *hw = rvu->hw;
	पूर्णांक pf = rvu_get_pf(pcअगरunc);
	u8 cgx_id = 0, lmac_id = 0;

	अगर (is_afvf(pcअगरunc)) अणु/* LBK links */
		वापस hw->cgx_links;
	पूर्ण अन्यथा अगर (is_pf_cgxmapped(rvu, pf)) अणु
		rvu_get_cgx_lmac_id(rvu->pf2cgxlmac_map[pf], &cgx_id, &lmac_id);
		वापस (cgx_id * hw->lmac_per_cgx) + lmac_id;
	पूर्ण

	/* SDP link */
	वापस hw->cgx_links + hw->lbk_links;
पूर्ण

अटल व्योम nix_get_txschq_range(काष्ठा rvu *rvu, u16 pcअगरunc,
				 पूर्णांक link, पूर्णांक *start, पूर्णांक *end)
अणु
	काष्ठा rvu_hwinfo *hw = rvu->hw;
	पूर्णांक pf = rvu_get_pf(pcअगरunc);

	अगर (is_afvf(pcअगरunc)) अणु /* LBK links */
		*start = hw->cap.nix_txsch_per_cgx_lmac * link;
		*end = *start + hw->cap.nix_txsch_per_lbk_lmac;
	पूर्ण अन्यथा अगर (is_pf_cgxmapped(rvu, pf)) अणु /* CGX links */
		*start = hw->cap.nix_txsch_per_cgx_lmac * link;
		*end = *start + hw->cap.nix_txsch_per_cgx_lmac;
	पूर्ण अन्यथा अणु /* SDP link */
		*start = (hw->cap.nix_txsch_per_cgx_lmac * hw->cgx_links) +
			(hw->cap.nix_txsch_per_lbk_lmac * hw->lbk_links);
		*end = *start + hw->cap.nix_txsch_per_sdp_lmac;
	पूर्ण
पूर्ण

अटल पूर्णांक nix_check_txschq_alloc_req(काष्ठा rvu *rvu, पूर्णांक lvl, u16 pcअगरunc,
				      काष्ठा nix_hw *nix_hw,
				      काष्ठा nix_txsch_alloc_req *req)
अणु
	काष्ठा rvu_hwinfo *hw = rvu->hw;
	पूर्णांक schq, req_schq, मुक्त_cnt;
	काष्ठा nix_txsch *txsch;
	पूर्णांक link, start, end;

	txsch = &nix_hw->txsch[lvl];
	req_schq = req->schq_contig[lvl] + req->schq[lvl];

	अगर (!req_schq)
		वापस 0;

	link = nix_get_tx_link(rvu, pcअगरunc);

	/* For traffic aggregating scheduler level, one queue is enough */
	अगर (lvl >= hw->cap.nix_tx_aggr_lvl) अणु
		अगर (req_schq != 1)
			वापस NIX_AF_ERR_TLX_ALLOC_FAIL;
		वापस 0;
	पूर्ण

	/* Get मुक्त SCHQ count and check अगर request can be accomodated */
	अगर (hw->cap.nix_fixed_txschq_mapping) अणु
		nix_get_txschq_range(rvu, pcअगरunc, link, &start, &end);
		schq = start + (pcअगरunc & RVU_PFVF_FUNC_MASK);
		अगर (end <= txsch->schq.max && schq < end &&
		    !test_bit(schq, txsch->schq.bmap))
			मुक्त_cnt = 1;
		अन्यथा
			मुक्त_cnt = 0;
	पूर्ण अन्यथा अणु
		मुक्त_cnt = rvu_rsrc_मुक्त_count(&txsch->schq);
	पूर्ण

	अगर (मुक्त_cnt < req_schq || req_schq > MAX_TXSCHQ_PER_FUNC)
		वापस NIX_AF_ERR_TLX_ALLOC_FAIL;

	/* If contiguous queues are needed, check क्रम availability */
	अगर (!hw->cap.nix_fixed_txschq_mapping && req->schq_contig[lvl] &&
	    !rvu_rsrc_check_contig(&txsch->schq, req->schq_contig[lvl]))
		वापस NIX_AF_ERR_TLX_ALLOC_FAIL;

	वापस 0;
पूर्ण

अटल व्योम nix_txsch_alloc(काष्ठा rvu *rvu, काष्ठा nix_txsch *txsch,
			    काष्ठा nix_txsch_alloc_rsp *rsp,
			    पूर्णांक lvl, पूर्णांक start, पूर्णांक end)
अणु
	काष्ठा rvu_hwinfo *hw = rvu->hw;
	u16 pcअगरunc = rsp->hdr.pcअगरunc;
	पूर्णांक idx, schq;

	/* For traffic aggregating levels, queue alloc is based
	 * on transmit link to which PF_FUNC is mapped to.
	 */
	अगर (lvl >= hw->cap.nix_tx_aggr_lvl) अणु
		/* A single TL queue is allocated */
		अगर (rsp->schq_contig[lvl]) अणु
			rsp->schq_contig[lvl] = 1;
			rsp->schq_contig_list[lvl][0] = start;
		पूर्ण

		/* Both contig and non-contig reqs करोesn't make sense here */
		अगर (rsp->schq_contig[lvl])
			rsp->schq[lvl] = 0;

		अगर (rsp->schq[lvl]) अणु
			rsp->schq[lvl] = 1;
			rsp->schq_list[lvl][0] = start;
		पूर्ण
		वापस;
	पूर्ण

	/* Adjust the queue request count अगर HW supports
	 * only one queue per level configuration.
	 */
	अगर (hw->cap.nix_fixed_txschq_mapping) अणु
		idx = pcअगरunc & RVU_PFVF_FUNC_MASK;
		schq = start + idx;
		अगर (idx >= (end - start) || test_bit(schq, txsch->schq.bmap)) अणु
			rsp->schq_contig[lvl] = 0;
			rsp->schq[lvl] = 0;
			वापस;
		पूर्ण

		अगर (rsp->schq_contig[lvl]) अणु
			rsp->schq_contig[lvl] = 1;
			set_bit(schq, txsch->schq.bmap);
			rsp->schq_contig_list[lvl][0] = schq;
			rsp->schq[lvl] = 0;
		पूर्ण अन्यथा अगर (rsp->schq[lvl]) अणु
			rsp->schq[lvl] = 1;
			set_bit(schq, txsch->schq.bmap);
			rsp->schq_list[lvl][0] = schq;
		पूर्ण
		वापस;
	पूर्ण

	/* Allocate contiguous queue indices requesty first */
	अगर (rsp->schq_contig[lvl]) अणु
		schq = biपंचांगap_find_next_zero_area(txsch->schq.bmap,
						  txsch->schq.max, start,
						  rsp->schq_contig[lvl], 0);
		अगर (schq >= end)
			rsp->schq_contig[lvl] = 0;
		क्रम (idx = 0; idx < rsp->schq_contig[lvl]; idx++) अणु
			set_bit(schq, txsch->schq.bmap);
			rsp->schq_contig_list[lvl][idx] = schq;
			schq++;
		पूर्ण
	पूर्ण

	/* Allocate non-contiguous queue indices */
	अगर (rsp->schq[lvl]) अणु
		idx = 0;
		क्रम (schq = start; schq < end; schq++) अणु
			अगर (!test_bit(schq, txsch->schq.bmap)) अणु
				set_bit(schq, txsch->schq.bmap);
				rsp->schq_list[lvl][idx++] = schq;
			पूर्ण
			अगर (idx == rsp->schq[lvl])
				अवरोध;
		पूर्ण
		/* Update how many were allocated */
		rsp->schq[lvl] = idx;
	पूर्ण
पूर्ण

पूर्णांक rvu_mbox_handler_nix_txsch_alloc(काष्ठा rvu *rvu,
				     काष्ठा nix_txsch_alloc_req *req,
				     काष्ठा nix_txsch_alloc_rsp *rsp)
अणु
	काष्ठा rvu_hwinfo *hw = rvu->hw;
	u16 pcअगरunc = req->hdr.pcअगरunc;
	पूर्णांक link, blkaddr, rc = 0;
	पूर्णांक lvl, idx, start, end;
	काष्ठा nix_txsch *txsch;
	काष्ठा rvu_pfvf *pfvf;
	काष्ठा nix_hw *nix_hw;
	u32 *pfvf_map;
	u16 schq;

	pfvf = rvu_get_pfvf(rvu, pcअगरunc);
	blkaddr = rvu_get_blkaddr(rvu, BLKTYPE_NIX, pcअगरunc);
	अगर (!pfvf->nixlf || blkaddr < 0)
		वापस NIX_AF_ERR_AF_LF_INVALID;

	nix_hw = get_nix_hw(rvu->hw, blkaddr);
	अगर (!nix_hw)
		वापस -EINVAL;

	mutex_lock(&rvu->rsrc_lock);

	/* Check अगर request is valid as per HW capabilities
	 * and can be accomodated.
	 */
	क्रम (lvl = 0; lvl < NIX_TXSCH_LVL_CNT; lvl++) अणु
		rc = nix_check_txschq_alloc_req(rvu, lvl, pcअगरunc, nix_hw, req);
		अगर (rc)
			जाओ err;
	पूर्ण

	/* Allocate requested Tx scheduler queues */
	क्रम (lvl = 0; lvl < NIX_TXSCH_LVL_CNT; lvl++) अणु
		txsch = &nix_hw->txsch[lvl];
		pfvf_map = txsch->pfvf_map;

		अगर (!req->schq[lvl] && !req->schq_contig[lvl])
			जारी;

		rsp->schq[lvl] = req->schq[lvl];
		rsp->schq_contig[lvl] = req->schq_contig[lvl];

		link = nix_get_tx_link(rvu, pcअगरunc);

		अगर (lvl >= hw->cap.nix_tx_aggr_lvl) अणु
			start = link;
			end = link;
		पूर्ण अन्यथा अगर (hw->cap.nix_fixed_txschq_mapping) अणु
			nix_get_txschq_range(rvu, pcअगरunc, link, &start, &end);
		पूर्ण अन्यथा अणु
			start = 0;
			end = txsch->schq.max;
		पूर्ण

		nix_txsch_alloc(rvu, txsch, rsp, lvl, start, end);

		/* Reset queue config */
		क्रम (idx = 0; idx < req->schq_contig[lvl]; idx++) अणु
			schq = rsp->schq_contig_list[lvl][idx];
			अगर (!(TXSCH_MAP_FLAGS(pfvf_map[schq]) &
			    NIX_TXSCHQ_CFG_DONE))
				pfvf_map[schq] = TXSCH_MAP(pcअगरunc, 0);
			nix_reset_tx_linkcfg(rvu, blkaddr, lvl, schq);
			nix_reset_tx_shaping(rvu, blkaddr, lvl, schq);
		पूर्ण

		क्रम (idx = 0; idx < req->schq[lvl]; idx++) अणु
			schq = rsp->schq_list[lvl][idx];
			अगर (!(TXSCH_MAP_FLAGS(pfvf_map[schq]) &
			    NIX_TXSCHQ_CFG_DONE))
				pfvf_map[schq] = TXSCH_MAP(pcअगरunc, 0);
			nix_reset_tx_linkcfg(rvu, blkaddr, lvl, schq);
			nix_reset_tx_shaping(rvu, blkaddr, lvl, schq);
		पूर्ण
	पूर्ण

	rsp->aggr_level = hw->cap.nix_tx_aggr_lvl;
	rsp->aggr_lvl_rr_prio = TXSCH_TL1_DFLT_RR_PRIO;
	rsp->link_cfg_lvl = rvu_पढ़ो64(rvu, blkaddr,
				       NIX_AF_PSE_CHANNEL_LEVEL) & 0x01 ?
				       NIX_TXSCH_LVL_TL3 : NIX_TXSCH_LVL_TL2;
	जाओ निकास;
err:
	rc = NIX_AF_ERR_TLX_ALLOC_FAIL;
निकास:
	mutex_unlock(&rvu->rsrc_lock);
	वापस rc;
पूर्ण

अटल व्योम nix_smq_flush(काष्ठा rvu *rvu, पूर्णांक blkaddr,
			  पूर्णांक smq, u16 pcअगरunc, पूर्णांक nixlf)
अणु
	पूर्णांक pf = rvu_get_pf(pcअगरunc);
	u8 cgx_id = 0, lmac_id = 0;
	पूर्णांक err, restore_tx_en = 0;
	u64 cfg;

	/* enable cgx tx अगर disabled */
	अगर (is_pf_cgxmapped(rvu, pf)) अणु
		rvu_get_cgx_lmac_id(rvu->pf2cgxlmac_map[pf], &cgx_id, &lmac_id);
		restore_tx_en = !cgx_lmac_tx_enable(rvu_cgx_pdata(cgx_id, rvu),
						    lmac_id, true);
	पूर्ण

	cfg = rvu_पढ़ो64(rvu, blkaddr, NIX_AF_SMQX_CFG(smq));
	/* Do SMQ flush and set enqueue xoff */
	cfg |= BIT_ULL(50) | BIT_ULL(49);
	rvu_ग_लिखो64(rvu, blkaddr, NIX_AF_SMQX_CFG(smq), cfg);

	/* Disable backpressure from physical link,
	 * otherwise SMQ flush may stall.
	 */
	rvu_cgx_enadis_rx_bp(rvu, pf, false);

	/* Wait क्रम flush to complete */
	err = rvu_poll_reg(rvu, blkaddr,
			   NIX_AF_SMQX_CFG(smq), BIT_ULL(49), true);
	अगर (err)
		dev_err(rvu->dev,
			"NIXLF%d: SMQ%d flush failed\n", nixlf, smq);

	rvu_cgx_enadis_rx_bp(rvu, pf, true);
	/* restore cgx tx state */
	अगर (restore_tx_en)
		cgx_lmac_tx_enable(rvu_cgx_pdata(cgx_id, rvu), lmac_id, false);
पूर्ण

अटल पूर्णांक nix_txschq_मुक्त(काष्ठा rvu *rvu, u16 pcअगरunc)
अणु
	पूर्णांक blkaddr, nixlf, lvl, schq, err;
	काष्ठा rvu_hwinfo *hw = rvu->hw;
	काष्ठा nix_txsch *txsch;
	काष्ठा nix_hw *nix_hw;

	blkaddr = rvu_get_blkaddr(rvu, BLKTYPE_NIX, pcअगरunc);
	अगर (blkaddr < 0)
		वापस NIX_AF_ERR_AF_LF_INVALID;

	nix_hw = get_nix_hw(rvu->hw, blkaddr);
	अगर (!nix_hw)
		वापस -EINVAL;

	nixlf = rvu_get_lf(rvu, &hw->block[blkaddr], pcअगरunc, 0);
	अगर (nixlf < 0)
		वापस NIX_AF_ERR_AF_LF_INVALID;

	/* Disable TL2/3 queue links beक्रमe SMQ flush*/
	mutex_lock(&rvu->rsrc_lock);
	क्रम (lvl = NIX_TXSCH_LVL_TL4; lvl < NIX_TXSCH_LVL_CNT; lvl++) अणु
		अगर (lvl != NIX_TXSCH_LVL_TL2 && lvl != NIX_TXSCH_LVL_TL4)
			जारी;

		txsch = &nix_hw->txsch[lvl];
		क्रम (schq = 0; schq < txsch->schq.max; schq++) अणु
			अगर (TXSCH_MAP_FUNC(txsch->pfvf_map[schq]) != pcअगरunc)
				जारी;
			nix_reset_tx_linkcfg(rvu, blkaddr, lvl, schq);
		पूर्ण
	पूर्ण

	/* Flush SMQs */
	txsch = &nix_hw->txsch[NIX_TXSCH_LVL_SMQ];
	क्रम (schq = 0; schq < txsch->schq.max; schq++) अणु
		अगर (TXSCH_MAP_FUNC(txsch->pfvf_map[schq]) != pcअगरunc)
			जारी;
		nix_smq_flush(rvu, blkaddr, schq, pcअगरunc, nixlf);
	पूर्ण

	/* Now मुक्त scheduler queues to मुक्त pool */
	क्रम (lvl = 0; lvl < NIX_TXSCH_LVL_CNT; lvl++) अणु
		 /* TLs above aggregation level are shared across all PF
		  * and it's VFs, hence skip मुक्तing them.
		  */
		अगर (lvl >= hw->cap.nix_tx_aggr_lvl)
			जारी;

		txsch = &nix_hw->txsch[lvl];
		क्रम (schq = 0; schq < txsch->schq.max; schq++) अणु
			अगर (TXSCH_MAP_FUNC(txsch->pfvf_map[schq]) != pcअगरunc)
				जारी;
			rvu_मुक्त_rsrc(&txsch->schq, schq);
			txsch->pfvf_map[schq] = TXSCH_MAP(0, NIX_TXSCHQ_FREE);
		पूर्ण
	पूर्ण
	mutex_unlock(&rvu->rsrc_lock);

	/* Sync cached info क्रम this LF in NDC-TX to LLC/DRAM */
	rvu_ग_लिखो64(rvu, blkaddr, NIX_AF_NDC_TX_SYNC, BIT_ULL(12) | nixlf);
	err = rvu_poll_reg(rvu, blkaddr, NIX_AF_NDC_TX_SYNC, BIT_ULL(12), true);
	अगर (err)
		dev_err(rvu->dev, "NDC-TX sync failed for NIXLF %d\n", nixlf);

	वापस 0;
पूर्ण

अटल पूर्णांक nix_txschq_मुक्त_one(काष्ठा rvu *rvu,
			       काष्ठा nix_txsch_मुक्त_req *req)
अणु
	काष्ठा rvu_hwinfo *hw = rvu->hw;
	u16 pcअगरunc = req->hdr.pcअगरunc;
	पूर्णांक lvl, schq, nixlf, blkaddr;
	काष्ठा nix_txsch *txsch;
	काष्ठा nix_hw *nix_hw;
	u32 *pfvf_map;

	blkaddr = rvu_get_blkaddr(rvu, BLKTYPE_NIX, pcअगरunc);
	अगर (blkaddr < 0)
		वापस NIX_AF_ERR_AF_LF_INVALID;

	nix_hw = get_nix_hw(rvu->hw, blkaddr);
	अगर (!nix_hw)
		वापस -EINVAL;

	nixlf = rvu_get_lf(rvu, &hw->block[blkaddr], pcअगरunc, 0);
	अगर (nixlf < 0)
		वापस NIX_AF_ERR_AF_LF_INVALID;

	lvl = req->schq_lvl;
	schq = req->schq;
	txsch = &nix_hw->txsch[lvl];

	अगर (lvl >= hw->cap.nix_tx_aggr_lvl || schq >= txsch->schq.max)
		वापस 0;

	pfvf_map = txsch->pfvf_map;
	mutex_lock(&rvu->rsrc_lock);

	अगर (TXSCH_MAP_FUNC(pfvf_map[schq]) != pcअगरunc) अणु
		mutex_unlock(&rvu->rsrc_lock);
		जाओ err;
	पूर्ण

	/* Flush अगर it is a SMQ. Onus of disabling
	 * TL2/3 queue links beक्रमe SMQ flush is on user
	 */
	अगर (lvl == NIX_TXSCH_LVL_SMQ)
		nix_smq_flush(rvu, blkaddr, schq, pcअगरunc, nixlf);

	/* Free the resource */
	rvu_मुक्त_rsrc(&txsch->schq, schq);
	txsch->pfvf_map[schq] = TXSCH_MAP(0, NIX_TXSCHQ_FREE);
	mutex_unlock(&rvu->rsrc_lock);
	वापस 0;
err:
	वापस NIX_AF_ERR_TLX_INVALID;
पूर्ण

पूर्णांक rvu_mbox_handler_nix_txsch_मुक्त(काष्ठा rvu *rvu,
				    काष्ठा nix_txsch_मुक्त_req *req,
				    काष्ठा msg_rsp *rsp)
अणु
	अगर (req->flags & TXSCHQ_FREE_ALL)
		वापस nix_txschq_मुक्त(rvu, req->hdr.pcअगरunc);
	अन्यथा
		वापस nix_txschq_मुक्त_one(rvu, req);
पूर्ण

अटल bool is_txschq_hierarchy_valid(काष्ठा rvu *rvu, u16 pcअगरunc, पूर्णांक blkaddr,
				      पूर्णांक lvl, u64 reg, u64 regval)
अणु
	u64 regbase = reg & 0xFFFF;
	u16 schq, parent;

	अगर (!rvu_check_valid_reg(TXSCHQ_HWREGMAP, lvl, reg))
		वापस false;

	schq = TXSCHQ_IDX(reg, TXSCHQ_IDX_SHIFT);
	/* Check अगर this schq beदीर्घs to this PF/VF or not */
	अगर (!is_valid_txschq(rvu, blkaddr, lvl, pcअगरunc, schq))
		वापस false;

	parent = (regval >> 16) & 0x1FF;
	/* Validate MDQ's TL4 parent */
	अगर (regbase == NIX_AF_MDQX_PARENT(0) &&
	    !is_valid_txschq(rvu, blkaddr, NIX_TXSCH_LVL_TL4, pcअगरunc, parent))
		वापस false;

	/* Validate TL4's TL3 parent */
	अगर (regbase == NIX_AF_TL4X_PARENT(0) &&
	    !is_valid_txschq(rvu, blkaddr, NIX_TXSCH_LVL_TL3, pcअगरunc, parent))
		वापस false;

	/* Validate TL3's TL2 parent */
	अगर (regbase == NIX_AF_TL3X_PARENT(0) &&
	    !is_valid_txschq(rvu, blkaddr, NIX_TXSCH_LVL_TL2, pcअगरunc, parent))
		वापस false;

	/* Validate TL2's TL1 parent */
	अगर (regbase == NIX_AF_TL2X_PARENT(0) &&
	    !is_valid_txschq(rvu, blkaddr, NIX_TXSCH_LVL_TL1, pcअगरunc, parent))
		वापस false;

	वापस true;
पूर्ण

अटल bool is_txschq_shaping_valid(काष्ठा rvu_hwinfo *hw, पूर्णांक lvl, u64 reg)
अणु
	u64 regbase;

	अगर (hw->cap.nix_shaping)
		वापस true;

	/* If shaping and coloring is not supported, then
	 * *_CIR and *_PIR रेजिस्टरs should not be configured.
	 */
	regbase = reg & 0xFFFF;

	चयन (lvl) अणु
	हाल NIX_TXSCH_LVL_TL1:
		अगर (regbase == NIX_AF_TL1X_CIR(0))
			वापस false;
		अवरोध;
	हाल NIX_TXSCH_LVL_TL2:
		अगर (regbase == NIX_AF_TL2X_CIR(0) ||
		    regbase == NIX_AF_TL2X_PIR(0))
			वापस false;
		अवरोध;
	हाल NIX_TXSCH_LVL_TL3:
		अगर (regbase == NIX_AF_TL3X_CIR(0) ||
		    regbase == NIX_AF_TL3X_PIR(0))
			वापस false;
		अवरोध;
	हाल NIX_TXSCH_LVL_TL4:
		अगर (regbase == NIX_AF_TL4X_CIR(0) ||
		    regbase == NIX_AF_TL4X_PIR(0))
			वापस false;
		अवरोध;
	पूर्ण
	वापस true;
पूर्ण

अटल व्योम nix_tl1_शेष_cfg(काष्ठा rvu *rvu, काष्ठा nix_hw *nix_hw,
				u16 pcअगरunc, पूर्णांक blkaddr)
अणु
	u32 *pfvf_map;
	पूर्णांक schq;

	schq = nix_get_tx_link(rvu, pcअगरunc);
	pfvf_map = nix_hw->txsch[NIX_TXSCH_LVL_TL1].pfvf_map;
	/* Skip अगर PF has alपढ़ोy करोne the config */
	अगर (TXSCH_MAP_FLAGS(pfvf_map[schq]) & NIX_TXSCHQ_CFG_DONE)
		वापस;
	rvu_ग_लिखो64(rvu, blkaddr, NIX_AF_TL1X_TOPOLOGY(schq),
		    (TXSCH_TL1_DFLT_RR_PRIO << 1));
	rvu_ग_लिखो64(rvu, blkaddr, NIX_AF_TL1X_SCHEDULE(schq),
		    TXSCH_TL1_DFLT_RR_QTM);
	rvu_ग_लिखो64(rvu, blkaddr, NIX_AF_TL1X_CIR(schq), 0x00);
	pfvf_map[schq] = TXSCH_SET_FLAG(pfvf_map[schq], NIX_TXSCHQ_CFG_DONE);
पूर्ण

पूर्णांक rvu_mbox_handler_nix_txschq_cfg(काष्ठा rvu *rvu,
				    काष्ठा nix_txschq_config *req,
				    काष्ठा msg_rsp *rsp)
अणु
	काष्ठा rvu_hwinfo *hw = rvu->hw;
	u16 pcअगरunc = req->hdr.pcअगरunc;
	u64 reg, regval, schq_regbase;
	काष्ठा nix_txsch *txsch;
	काष्ठा nix_hw *nix_hw;
	पूर्णांक blkaddr, idx, err;
	पूर्णांक nixlf, schq;
	u32 *pfvf_map;

	अगर (req->lvl >= NIX_TXSCH_LVL_CNT ||
	    req->num_regs > MAX_REGS_PER_MBOX_MSG)
		वापस NIX_AF_INVAL_TXSCHQ_CFG;

	err = nix_get_nixlf(rvu, pcअगरunc, &nixlf, &blkaddr);
	अगर (err)
		वापस err;

	nix_hw = get_nix_hw(rvu->hw, blkaddr);
	अगर (!nix_hw)
		वापस -EINVAL;

	txsch = &nix_hw->txsch[req->lvl];
	pfvf_map = txsch->pfvf_map;

	अगर (req->lvl >= hw->cap.nix_tx_aggr_lvl &&
	    pcअगरunc & RVU_PFVF_FUNC_MASK) अणु
		mutex_lock(&rvu->rsrc_lock);
		अगर (req->lvl == NIX_TXSCH_LVL_TL1)
			nix_tl1_शेष_cfg(rvu, nix_hw, pcअगरunc, blkaddr);
		mutex_unlock(&rvu->rsrc_lock);
		वापस 0;
	पूर्ण

	क्रम (idx = 0; idx < req->num_regs; idx++) अणु
		reg = req->reg[idx];
		regval = req->regval[idx];
		schq_regbase = reg & 0xFFFF;

		अगर (!is_txschq_hierarchy_valid(rvu, pcअगरunc, blkaddr,
					       txsch->lvl, reg, regval))
			वापस NIX_AF_INVAL_TXSCHQ_CFG;

		/* Check अगर shaping and coloring is supported */
		अगर (!is_txschq_shaping_valid(hw, req->lvl, reg))
			जारी;

		/* Replace PF/VF visible NIXLF slot with HW NIXLF id */
		अगर (schq_regbase == NIX_AF_SMQX_CFG(0)) अणु
			nixlf = rvu_get_lf(rvu, &hw->block[blkaddr],
					   pcअगरunc, 0);
			regval &= ~(0x7FULL << 24);
			regval |= ((u64)nixlf << 24);
		पूर्ण

		/* Clear 'BP_ENA' config, if it's not allowed */
		अगर (!hw->cap.nix_tx_link_bp) अणु
			अगर (schq_regbase == NIX_AF_TL4X_SDP_LINK_CFG(0) ||
			    (schq_regbase & 0xFF00) ==
			    NIX_AF_TL3_TL2X_LINKX_CFG(0, 0))
				regval &= ~BIT_ULL(13);
		पूर्ण

		/* Mark config as करोne क्रम TL1 by PF */
		अगर (schq_regbase >= NIX_AF_TL1X_SCHEDULE(0) &&
		    schq_regbase <= NIX_AF_TL1X_GREEN_BYTES(0)) अणु
			schq = TXSCHQ_IDX(reg, TXSCHQ_IDX_SHIFT);
			mutex_lock(&rvu->rsrc_lock);
			pfvf_map[schq] = TXSCH_SET_FLAG(pfvf_map[schq],
							NIX_TXSCHQ_CFG_DONE);
			mutex_unlock(&rvu->rsrc_lock);
		पूर्ण

		/* SMQ flush is special hence split रेजिस्टर ग_लिखोs such
		 * that flush first and ग_लिखो rest of the bits later.
		 */
		अगर (schq_regbase == NIX_AF_SMQX_CFG(0) &&
		    (regval & BIT_ULL(49))) अणु
			schq = TXSCHQ_IDX(reg, TXSCHQ_IDX_SHIFT);
			nix_smq_flush(rvu, blkaddr, schq, pcअगरunc, nixlf);
			regval &= ~BIT_ULL(49);
		पूर्ण
		rvu_ग_लिखो64(rvu, blkaddr, reg, regval);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक nix_rx_vtag_cfg(काष्ठा rvu *rvu, पूर्णांक nixlf, पूर्णांक blkaddr,
			   काष्ठा nix_vtag_config *req)
अणु
	u64 regval = req->vtag_size;

	अगर (req->rx.vtag_type > NIX_AF_LFX_RX_VTAG_TYPE7 ||
	    req->vtag_size > VTAGSIZE_T8)
		वापस -EINVAL;

	/* RX VTAG Type 7 reserved क्रम vf vlan */
	अगर (req->rx.vtag_type == NIX_AF_LFX_RX_VTAG_TYPE7)
		वापस NIX_AF_ERR_RX_VTAG_INUSE;

	अगर (req->rx.capture_vtag)
		regval |= BIT_ULL(5);
	अगर (req->rx.strip_vtag)
		regval |= BIT_ULL(4);

	rvu_ग_लिखो64(rvu, blkaddr,
		    NIX_AF_LFX_RX_VTAG_TYPEX(nixlf, req->rx.vtag_type), regval);
	वापस 0;
पूर्ण

अटल पूर्णांक nix_tx_vtag_मुक्त(काष्ठा rvu *rvu, पूर्णांक blkaddr,
			    u16 pcअगरunc, पूर्णांक index)
अणु
	काष्ठा nix_hw *nix_hw = get_nix_hw(rvu->hw, blkaddr);
	काष्ठा nix_txvlan *vlan = &nix_hw->txvlan;

	अगर (vlan->entry2pfvf_map[index] != pcअगरunc)
		वापस NIX_AF_ERR_PARAM;

	rvu_ग_लिखो64(rvu, blkaddr,
		    NIX_AF_TX_VTAG_DEFX_DATA(index), 0x0ull);
	rvu_ग_लिखो64(rvu, blkaddr,
		    NIX_AF_TX_VTAG_DEFX_CTL(index), 0x0ull);

	vlan->entry2pfvf_map[index] = 0;
	rvu_मुक्त_rsrc(&vlan->rsrc, index);

	वापस 0;
पूर्ण

अटल व्योम nix_मुक्त_tx_vtag_entries(काष्ठा rvu *rvu, u16 pcअगरunc)
अणु
	काष्ठा nix_txvlan *vlan;
	काष्ठा nix_hw *nix_hw;
	पूर्णांक index, blkaddr;

	blkaddr = rvu_get_blkaddr(rvu, BLKTYPE_NIX, pcअगरunc);
	अगर (blkaddr < 0)
		वापस;

	nix_hw = get_nix_hw(rvu->hw, blkaddr);
	vlan = &nix_hw->txvlan;

	mutex_lock(&vlan->rsrc_lock);
	/* Scan all the entries and मुक्त the ones mapped to 'pcifunc' */
	क्रम (index = 0; index < vlan->rsrc.max; index++) अणु
		अगर (vlan->entry2pfvf_map[index] == pcअगरunc)
			nix_tx_vtag_मुक्त(rvu, blkaddr, pcअगरunc, index);
	पूर्ण
	mutex_unlock(&vlan->rsrc_lock);
पूर्ण

अटल पूर्णांक nix_tx_vtag_alloc(काष्ठा rvu *rvu, पूर्णांक blkaddr,
			     u64 vtag, u8 size)
अणु
	काष्ठा nix_hw *nix_hw = get_nix_hw(rvu->hw, blkaddr);
	काष्ठा nix_txvlan *vlan = &nix_hw->txvlan;
	u64 regval;
	पूर्णांक index;

	mutex_lock(&vlan->rsrc_lock);

	index = rvu_alloc_rsrc(&vlan->rsrc);
	अगर (index < 0) अणु
		mutex_unlock(&vlan->rsrc_lock);
		वापस index;
	पूर्ण

	mutex_unlock(&vlan->rsrc_lock);

	regval = size ? vtag : vtag << 32;

	rvu_ग_लिखो64(rvu, blkaddr,
		    NIX_AF_TX_VTAG_DEFX_DATA(index), regval);
	rvu_ग_लिखो64(rvu, blkaddr,
		    NIX_AF_TX_VTAG_DEFX_CTL(index), size);

	वापस index;
पूर्ण

अटल पूर्णांक nix_tx_vtag_decfg(काष्ठा rvu *rvu, पूर्णांक blkaddr,
			     काष्ठा nix_vtag_config *req)
अणु
	काष्ठा nix_hw *nix_hw = get_nix_hw(rvu->hw, blkaddr);
	काष्ठा nix_txvlan *vlan = &nix_hw->txvlan;
	u16 pcअगरunc = req->hdr.pcअगरunc;
	पूर्णांक idx0 = req->tx.vtag0_idx;
	पूर्णांक idx1 = req->tx.vtag1_idx;
	पूर्णांक err = 0;

	अगर (req->tx.मुक्त_vtag0 && req->tx.मुक्त_vtag1)
		अगर (vlan->entry2pfvf_map[idx0] != pcअगरunc ||
		    vlan->entry2pfvf_map[idx1] != pcअगरunc)
			वापस NIX_AF_ERR_PARAM;

	mutex_lock(&vlan->rsrc_lock);

	अगर (req->tx.मुक्त_vtag0) अणु
		err = nix_tx_vtag_मुक्त(rvu, blkaddr, pcअगरunc, idx0);
		अगर (err)
			जाओ निकास;
	पूर्ण

	अगर (req->tx.मुक्त_vtag1)
		err = nix_tx_vtag_मुक्त(rvu, blkaddr, pcअगरunc, idx1);

निकास:
	mutex_unlock(&vlan->rsrc_lock);
	वापस err;
पूर्ण

अटल पूर्णांक nix_tx_vtag_cfg(काष्ठा rvu *rvu, पूर्णांक blkaddr,
			   काष्ठा nix_vtag_config *req,
			   काष्ठा nix_vtag_config_rsp *rsp)
अणु
	काष्ठा nix_hw *nix_hw = get_nix_hw(rvu->hw, blkaddr);
	काष्ठा nix_txvlan *vlan = &nix_hw->txvlan;
	u16 pcअगरunc = req->hdr.pcअगरunc;

	अगर (req->tx.cfg_vtag0) अणु
		rsp->vtag0_idx =
			nix_tx_vtag_alloc(rvu, blkaddr,
					  req->tx.vtag0, req->vtag_size);

		अगर (rsp->vtag0_idx < 0)
			वापस NIX_AF_ERR_TX_VTAG_NOSPC;

		vlan->entry2pfvf_map[rsp->vtag0_idx] = pcअगरunc;
	पूर्ण

	अगर (req->tx.cfg_vtag1) अणु
		rsp->vtag1_idx =
			nix_tx_vtag_alloc(rvu, blkaddr,
					  req->tx.vtag1, req->vtag_size);

		अगर (rsp->vtag1_idx < 0)
			जाओ err_मुक्त;

		vlan->entry2pfvf_map[rsp->vtag1_idx] = pcअगरunc;
	पूर्ण

	वापस 0;

err_मुक्त:
	अगर (req->tx.cfg_vtag0)
		nix_tx_vtag_मुक्त(rvu, blkaddr, pcअगरunc, rsp->vtag0_idx);

	वापस NIX_AF_ERR_TX_VTAG_NOSPC;
पूर्ण

पूर्णांक rvu_mbox_handler_nix_vtag_cfg(काष्ठा rvu *rvu,
				  काष्ठा nix_vtag_config *req,
				  काष्ठा nix_vtag_config_rsp *rsp)
अणु
	u16 pcअगरunc = req->hdr.pcअगरunc;
	पूर्णांक blkaddr, nixlf, err;

	err = nix_get_nixlf(rvu, pcअगरunc, &nixlf, &blkaddr);
	अगर (err)
		वापस err;

	अगर (req->cfg_type) अणु
		/* rx vtag configuration */
		err = nix_rx_vtag_cfg(rvu, nixlf, blkaddr, req);
		अगर (err)
			वापस NIX_AF_ERR_PARAM;
	पूर्ण अन्यथा अणु
		/* tx vtag configuration */
		अगर ((req->tx.cfg_vtag0 || req->tx.cfg_vtag1) &&
		    (req->tx.मुक्त_vtag0 || req->tx.मुक्त_vtag1))
			वापस NIX_AF_ERR_PARAM;

		अगर (req->tx.cfg_vtag0 || req->tx.cfg_vtag1)
			वापस nix_tx_vtag_cfg(rvu, blkaddr, req, rsp);

		अगर (req->tx.मुक्त_vtag0 || req->tx.मुक्त_vtag1)
			वापस nix_tx_vtag_decfg(rvu, blkaddr, req);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक nix_blk_setup_mce(काष्ठा rvu *rvu, काष्ठा nix_hw *nix_hw,
			     पूर्णांक mce, u8 op, u16 pcअगरunc, पूर्णांक next, bool eol)
अणु
	काष्ठा nix_aq_enq_req aq_req;
	पूर्णांक err;

	aq_req.hdr.pcअगरunc = 0;
	aq_req.ctype = NIX_AQ_CTYPE_MCE;
	aq_req.op = op;
	aq_req.qidx = mce;

	/* Forward bcast pkts to RQ0, RSS not needed */
	aq_req.mce.op = 0;
	aq_req.mce.index = 0;
	aq_req.mce.eol = eol;
	aq_req.mce.pf_func = pcअगरunc;
	aq_req.mce.next = next;

	/* All fields valid */
	*(u64 *)(&aq_req.mce_mask) = ~0ULL;

	err = rvu_nix_blk_aq_enq_inst(rvu, nix_hw, &aq_req, शून्य);
	अगर (err) अणु
		dev_err(rvu->dev, "Failed to setup Bcast MCE for PF%d:VF%d\n",
			rvu_get_pf(pcअगरunc), pcअगरunc & RVU_PFVF_FUNC_MASK);
		वापस err;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक nix_update_mce_list(काष्ठा nix_mce_list *mce_list,
			       u16 pcअगरunc, bool add)
अणु
	काष्ठा mce *mce, *tail = शून्य;
	bool delete = false;

	/* Scan through the current list */
	hlist_क्रम_each_entry(mce, &mce_list->head, node) अणु
		/* If alपढ़ोy exists, then delete */
		अगर (mce->pcअगरunc == pcअगरunc && !add) अणु
			delete = true;
			अवरोध;
		पूर्ण
		tail = mce;
	पूर्ण

	अगर (delete) अणु
		hlist_del(&mce->node);
		kमुक्त(mce);
		mce_list->count--;
		वापस 0;
	पूर्ण

	अगर (!add)
		वापस 0;

	/* Add a new one to the list, at the tail */
	mce = kzalloc(माप(*mce), GFP_KERNEL);
	अगर (!mce)
		वापस -ENOMEM;
	mce->pcअगरunc = pcअगरunc;
	अगर (!tail)
		hlist_add_head(&mce->node, &mce_list->head);
	अन्यथा
		hlist_add_behind(&mce->node, &tail->node);
	mce_list->count++;
	वापस 0;
पूर्ण

पूर्णांक nix_update_bcast_mce_list(काष्ठा rvu *rvu, u16 pcअगरunc, bool add)
अणु
	पूर्णांक err = 0, idx, next_idx, last_idx;
	काष्ठा nix_mce_list *mce_list;
	काष्ठा nix_mcast *mcast;
	काष्ठा nix_hw *nix_hw;
	काष्ठा rvu_pfvf *pfvf;
	काष्ठा mce *mce;
	पूर्णांक blkaddr;

	/* Broadcast pkt replication is not needed क्रम AF's VFs, hence skip */
	अगर (is_afvf(pcअगरunc))
		वापस 0;

	blkaddr = rvu_get_blkaddr(rvu, BLKTYPE_NIX, pcअगरunc);
	अगर (blkaddr < 0)
		वापस 0;

	nix_hw = get_nix_hw(rvu->hw, blkaddr);
	अगर (!nix_hw)
		वापस 0;

	mcast = &nix_hw->mcast;

	/* Get this PF/VF func's MCE index */
	pfvf = rvu_get_pfvf(rvu, pcअगरunc & ~RVU_PFVF_FUNC_MASK);
	idx = pfvf->bcast_mce_idx + (pcअगरunc & RVU_PFVF_FUNC_MASK);

	mce_list = &pfvf->bcast_mce_list;
	अगर (idx > (pfvf->bcast_mce_idx + mce_list->max)) अणु
		dev_err(rvu->dev,
			"%s: Idx %d > max MCE idx %d, for PF%d bcast list\n",
			__func__, idx, mce_list->max,
			pcअगरunc >> RVU_PFVF_PF_SHIFT);
		वापस -EINVAL;
	पूर्ण

	mutex_lock(&mcast->mce_lock);

	err = nix_update_mce_list(mce_list, pcअगरunc, add);
	अगर (err)
		जाओ end;

	/* Disable MCAM entry in NPC */
	अगर (!mce_list->count) अणु
		rvu_npc_enable_bcast_entry(rvu, pcअगरunc, false);
		जाओ end;
	पूर्ण

	/* Dump the updated list to HW */
	idx = pfvf->bcast_mce_idx;
	last_idx = idx + mce_list->count - 1;
	hlist_क्रम_each_entry(mce, &mce_list->head, node) अणु
		अगर (idx > last_idx)
			अवरोध;

		next_idx = idx + 1;
		/* EOL should be set in last MCE */
		err = nix_blk_setup_mce(rvu, nix_hw, idx, NIX_AQ_INSTOP_WRITE,
					mce->pcअगरunc, next_idx,
					(next_idx > last_idx) ? true : false);
		अगर (err)
			जाओ end;
		idx++;
	पूर्ण

end:
	mutex_unlock(&mcast->mce_lock);
	वापस err;
पूर्ण

अटल पूर्णांक nix_setup_bcast_tables(काष्ठा rvu *rvu, काष्ठा nix_hw *nix_hw)
अणु
	काष्ठा nix_mcast *mcast = &nix_hw->mcast;
	पूर्णांक err, pf, numvfs, idx;
	काष्ठा rvu_pfvf *pfvf;
	u16 pcअगरunc;
	u64 cfg;

	/* Skip PF0 (i.e AF) */
	क्रम (pf = 1; pf < (rvu->cgx_mapped_pfs + 1); pf++) अणु
		cfg = rvu_पढ़ो64(rvu, BLKADDR_RVUM, RVU_PRIV_PFX_CFG(pf));
		/* If PF is not enabled, nothing to करो */
		अगर (!((cfg >> 20) & 0x01))
			जारी;
		/* Get numVFs attached to this PF */
		numvfs = (cfg >> 12) & 0xFF;

		pfvf = &rvu->pf[pf];

		/* This NIX0/1 block mapped to PF ? */
		अगर (pfvf->nix_blkaddr != nix_hw->blkaddr)
			जारी;

		/* Save the start MCE */
		pfvf->bcast_mce_idx = nix_alloc_mce_list(mcast, numvfs + 1);

		nix_mce_list_init(&pfvf->bcast_mce_list, numvfs + 1);

		क्रम (idx = 0; idx < (numvfs + 1); idx++) अणु
			/* idx-0 is क्रम PF, followed by VFs */
			pcअगरunc = (pf << RVU_PFVF_PF_SHIFT);
			pcअगरunc |= idx;
			/* Add dummy entries now, so that we करोn't have to check
			 * क्रम whether AQ_OP should be INIT/WRITE later on.
			 * Will be updated when a NIXLF is attached/detached to
			 * these PF/VFs.
			 */
			err = nix_blk_setup_mce(rvu, nix_hw,
						pfvf->bcast_mce_idx + idx,
						NIX_AQ_INSTOP_INIT,
						pcअगरunc, 0, true);
			अगर (err)
				वापस err;
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक nix_setup_mcast(काष्ठा rvu *rvu, काष्ठा nix_hw *nix_hw, पूर्णांक blkaddr)
अणु
	काष्ठा nix_mcast *mcast = &nix_hw->mcast;
	काष्ठा rvu_hwinfo *hw = rvu->hw;
	पूर्णांक err, size;

	size = (rvu_पढ़ो64(rvu, blkaddr, NIX_AF_CONST3) >> 16) & 0x0F;
	size = (1ULL << size);

	/* Alloc memory क्रम multicast/mirror replication entries */
	err = qmem_alloc(rvu->dev, &mcast->mce_ctx,
			 (256UL << MC_TBL_SIZE), size);
	अगर (err)
		वापस -ENOMEM;

	rvu_ग_लिखो64(rvu, blkaddr, NIX_AF_RX_MCAST_BASE,
		    (u64)mcast->mce_ctx->iova);

	/* Set max list length equal to max no of VFs per PF  + PF itself */
	rvu_ग_लिखो64(rvu, blkaddr, NIX_AF_RX_MCAST_CFG,
		    BIT_ULL(36) | (hw->max_vfs_per_pf << 4) | MC_TBL_SIZE);

	/* Alloc memory क्रम multicast replication buffers */
	size = rvu_पढ़ो64(rvu, blkaddr, NIX_AF_MC_MIRROR_CONST) & 0xFFFF;
	err = qmem_alloc(rvu->dev, &mcast->mcast_buf,
			 (8UL << MC_BUF_CNT), size);
	अगर (err)
		वापस -ENOMEM;

	rvu_ग_लिखो64(rvu, blkaddr, NIX_AF_RX_MCAST_BUF_BASE,
		    (u64)mcast->mcast_buf->iova);

	/* Alloc pkind क्रम NIX पूर्णांकernal RX multicast/mirror replay */
	mcast->replay_pkind = rvu_alloc_rsrc(&hw->pkind.rsrc);

	rvu_ग_लिखो64(rvu, blkaddr, NIX_AF_RX_MCAST_BUF_CFG,
		    BIT_ULL(63) | (mcast->replay_pkind << 24) |
		    BIT_ULL(20) | MC_BUF_CNT);

	mutex_init(&mcast->mce_lock);

	वापस nix_setup_bcast_tables(rvu, nix_hw);
पूर्ण

अटल पूर्णांक nix_setup_txvlan(काष्ठा rvu *rvu, काष्ठा nix_hw *nix_hw)
अणु
	काष्ठा nix_txvlan *vlan = &nix_hw->txvlan;
	पूर्णांक err;

	/* Allocate resource bimap क्रम tx vtag def रेजिस्टरs*/
	vlan->rsrc.max = NIX_TX_VTAG_DEF_MAX;
	err = rvu_alloc_biपंचांगap(&vlan->rsrc);
	अगर (err)
		वापस -ENOMEM;

	/* Alloc memory क्रम saving entry to RVU PFFUNC allocation mapping */
	vlan->entry2pfvf_map = devm_kसुस्मृति(rvu->dev, vlan->rsrc.max,
					    माप(u16), GFP_KERNEL);
	अगर (!vlan->entry2pfvf_map)
		जाओ मुक्त_mem;

	mutex_init(&vlan->rsrc_lock);
	वापस 0;

मुक्त_mem:
	kमुक्त(vlan->rsrc.bmap);
	वापस -ENOMEM;
पूर्ण

अटल पूर्णांक nix_setup_txschq(काष्ठा rvu *rvu, काष्ठा nix_hw *nix_hw, पूर्णांक blkaddr)
अणु
	काष्ठा nix_txsch *txsch;
	पूर्णांक err, lvl, schq;
	u64 cfg, reg;

	/* Get scheduler queue count of each type and alloc
	 * biपंचांगap क्रम each क्रम alloc/मुक्त/attach operations.
	 */
	क्रम (lvl = 0; lvl < NIX_TXSCH_LVL_CNT; lvl++) अणु
		txsch = &nix_hw->txsch[lvl];
		txsch->lvl = lvl;
		चयन (lvl) अणु
		हाल NIX_TXSCH_LVL_SMQ:
			reg = NIX_AF_MDQ_CONST;
			अवरोध;
		हाल NIX_TXSCH_LVL_TL4:
			reg = NIX_AF_TL4_CONST;
			अवरोध;
		हाल NIX_TXSCH_LVL_TL3:
			reg = NIX_AF_TL3_CONST;
			अवरोध;
		हाल NIX_TXSCH_LVL_TL2:
			reg = NIX_AF_TL2_CONST;
			अवरोध;
		हाल NIX_TXSCH_LVL_TL1:
			reg = NIX_AF_TL1_CONST;
			अवरोध;
		पूर्ण
		cfg = rvu_पढ़ो64(rvu, blkaddr, reg);
		txsch->schq.max = cfg & 0xFFFF;
		err = rvu_alloc_biपंचांगap(&txsch->schq);
		अगर (err)
			वापस err;

		/* Allocate memory क्रम scheduler queues to
		 * PF/VF pcअगरunc mapping info.
		 */
		txsch->pfvf_map = devm_kसुस्मृति(rvu->dev, txsch->schq.max,
					       माप(u32), GFP_KERNEL);
		अगर (!txsch->pfvf_map)
			वापस -ENOMEM;
		क्रम (schq = 0; schq < txsch->schq.max; schq++)
			txsch->pfvf_map[schq] = TXSCH_MAP(0, NIX_TXSCHQ_FREE);
	पूर्ण
	वापस 0;
पूर्ण

पूर्णांक rvu_nix_reserve_mark_क्रमmat(काष्ठा rvu *rvu, काष्ठा nix_hw *nix_hw,
				पूर्णांक blkaddr, u32 cfg)
अणु
	पूर्णांक fmt_idx;

	क्रम (fmt_idx = 0; fmt_idx < nix_hw->mark_क्रमmat.in_use; fmt_idx++) अणु
		अगर (nix_hw->mark_क्रमmat.cfg[fmt_idx] == cfg)
			वापस fmt_idx;
	पूर्ण
	अगर (fmt_idx >= nix_hw->mark_क्रमmat.total)
		वापस -दुस्फल;

	rvu_ग_लिखो64(rvu, blkaddr, NIX_AF_MARK_FORMATX_CTL(fmt_idx), cfg);
	nix_hw->mark_क्रमmat.cfg[fmt_idx] = cfg;
	nix_hw->mark_क्रमmat.in_use++;
	वापस fmt_idx;
पूर्ण

अटल पूर्णांक nix_af_mark_क्रमmat_setup(काष्ठा rvu *rvu, काष्ठा nix_hw *nix_hw,
				    पूर्णांक blkaddr)
अणु
	u64 cfgs[] = अणु
		[NIX_MARK_CFG_IP_DSCP_RED]         = 0x10003,
		[NIX_MARK_CFG_IP_DSCP_YELLOW]      = 0x11200,
		[NIX_MARK_CFG_IP_DSCP_YELLOW_RED]  = 0x11203,
		[NIX_MARK_CFG_IP_ECN_RED]          = 0x6000c,
		[NIX_MARK_CFG_IP_ECN_YELLOW]       = 0x60c00,
		[NIX_MARK_CFG_IP_ECN_YELLOW_RED]   = 0x60c0c,
		[NIX_MARK_CFG_VLAN_DEI_RED]        = 0x30008,
		[NIX_MARK_CFG_VLAN_DEI_YELLOW]     = 0x30800,
		[NIX_MARK_CFG_VLAN_DEI_YELLOW_RED] = 0x30808,
	पूर्ण;
	पूर्णांक i, rc;
	u64 total;

	total = (rvu_पढ़ो64(rvu, blkaddr, NIX_AF_PSE_CONST) & 0xFF00) >> 8;
	nix_hw->mark_क्रमmat.total = (u8)total;
	nix_hw->mark_क्रमmat.cfg = devm_kसुस्मृति(rvu->dev, total, माप(u32),
					       GFP_KERNEL);
	अगर (!nix_hw->mark_क्रमmat.cfg)
		वापस -ENOMEM;
	क्रम (i = 0; i < NIX_MARK_CFG_MAX; i++) अणु
		rc = rvu_nix_reserve_mark_क्रमmat(rvu, nix_hw, blkaddr, cfgs[i]);
		अगर (rc < 0)
			dev_err(rvu->dev, "Err %d in setup mark format %d\n",
				i, rc);
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम rvu_get_lbk_link_max_frs(काष्ठा rvu *rvu,  u16 *max_mtu)
अणु
	/* CN10K supports LBK FIFO size 72 KB */
	अगर (rvu->hw->lbk_bufsize == 0x12000)
		*max_mtu = CN10K_LBK_LINK_MAX_FRS;
	अन्यथा
		*max_mtu = NIC_HW_MAX_FRS;
पूर्ण

अटल व्योम rvu_get_lmac_link_max_frs(काष्ठा rvu *rvu, u16 *max_mtu)
अणु
	/* RPM supports FIFO len 128 KB */
	अगर (rvu_cgx_get_fअगरolen(rvu) == 0x20000)
		*max_mtu = CN10K_LMAC_LINK_MAX_FRS;
	अन्यथा
		*max_mtu = NIC_HW_MAX_FRS;
पूर्ण

पूर्णांक rvu_mbox_handler_nix_get_hw_info(काष्ठा rvu *rvu, काष्ठा msg_req *req,
				     काष्ठा nix_hw_info *rsp)
अणु
	u16 pcअगरunc = req->hdr.pcअगरunc;
	पूर्णांक blkaddr;

	blkaddr = rvu_get_blkaddr(rvu, BLKTYPE_NIX, pcअगरunc);
	अगर (blkaddr < 0)
		वापस NIX_AF_ERR_AF_LF_INVALID;

	अगर (is_afvf(pcअगरunc))
		rvu_get_lbk_link_max_frs(rvu, &rsp->max_mtu);
	अन्यथा
		rvu_get_lmac_link_max_frs(rvu, &rsp->max_mtu);

	rsp->min_mtu = NIC_HW_MIN_FRS;
	वापस 0;
पूर्ण

पूर्णांक rvu_mbox_handler_nix_stats_rst(काष्ठा rvu *rvu, काष्ठा msg_req *req,
				   काष्ठा msg_rsp *rsp)
अणु
	u16 pcअगरunc = req->hdr.pcअगरunc;
	पूर्णांक i, nixlf, blkaddr, err;
	u64 stats;

	err = nix_get_nixlf(rvu, pcअगरunc, &nixlf, &blkaddr);
	अगर (err)
		वापस err;

	/* Get stats count supported by HW */
	stats = rvu_पढ़ो64(rvu, blkaddr, NIX_AF_CONST1);

	/* Reset tx stats */
	क्रम (i = 0; i < ((stats >> 24) & 0xFF); i++)
		rvu_ग_लिखो64(rvu, blkaddr, NIX_AF_LFX_TX_STATX(nixlf, i), 0);

	/* Reset rx stats */
	क्रम (i = 0; i < ((stats >> 32) & 0xFF); i++)
		rvu_ग_लिखो64(rvu, blkaddr, NIX_AF_LFX_RX_STATX(nixlf, i), 0);

	वापस 0;
पूर्ण

/* Returns the ALG index to be set पूर्णांकo NPC_RX_ACTION */
अटल पूर्णांक get_flowkey_alg_idx(काष्ठा nix_hw *nix_hw, u32 flow_cfg)
अणु
	पूर्णांक i;

	/* Scan over निकासing algo entries to find a match */
	क्रम (i = 0; i < nix_hw->flowkey.in_use; i++)
		अगर (nix_hw->flowkey.flowkey[i] == flow_cfg)
			वापस i;

	वापस -दुस्फल;
पूर्ण

अटल पूर्णांक set_flowkey_fields(काष्ठा nix_rx_flowkey_alg *alg, u32 flow_cfg)
अणु
	पूर्णांक idx, nr_field, key_off, field_marker, keyoff_marker;
	पूर्णांक max_key_off, max_bit_pos, group_member;
	काष्ठा nix_rx_flowkey_alg *field;
	काष्ठा nix_rx_flowkey_alg पंचांगp;
	u32 key_type, valid_key;
	पूर्णांक l4_key_offset = 0;

	अगर (!alg)
		वापस -EINVAL;

#घोषणा FIELDS_PER_ALG  5
#घोषणा MAX_KEY_OFF	40
	/* Clear all fields */
	स_रखो(alg, 0, माप(uपूर्णांक64_t) * FIELDS_PER_ALG);

	/* Each of the 32 possible flow key algorithm definitions should
	 * fall पूर्णांकo above incremental config (except ALG0). Otherwise a
	 * single NPC MCAM entry is not sufficient क्रम supporting RSS.
	 *
	 * If a dअगरferent definition or combination needed then NPC MCAM
	 * has to be programmed to filter such pkts and it's action should
	 * poपूर्णांक to this definition to calculate flowtag or hash.
	 *
	 * The `क्रम loop` goes over _all_ protocol field and the following
	 * variables depicts the state machine क्रमward progress logic.
	 *
	 * keyoff_marker - Enabled when hash byte length needs to be accounted
	 * in field->key_offset update.
	 * field_marker - Enabled when a new field needs to be selected.
	 * group_member - Enabled when protocol is part of a group.
	 */

	keyoff_marker = 0; max_key_off = 0; group_member = 0;
	nr_field = 0; key_off = 0; field_marker = 1;
	field = &पंचांगp; max_bit_pos = fls(flow_cfg);
	क्रम (idx = 0;
	     idx < max_bit_pos && nr_field < FIELDS_PER_ALG &&
	     key_off < MAX_KEY_OFF; idx++) अणु
		key_type = BIT(idx);
		valid_key = flow_cfg & key_type;
		/* Found a field marker, reset the field values */
		अगर (field_marker)
			स_रखो(&पंचांगp, 0, माप(पंचांगp));

		field_marker = true;
		keyoff_marker = true;
		चयन (key_type) अणु
		हाल NIX_FLOW_KEY_TYPE_PORT:
			field->sel_chan = true;
			/* This should be set to 1, when SEL_CHAN is set */
			field->bytesm1 = 1;
			अवरोध;
		हाल NIX_FLOW_KEY_TYPE_IPV4_PROTO:
			field->lid = NPC_LID_LC;
			field->hdr_offset = 9; /* offset */
			field->bytesm1 = 0; /* 1 byte */
			field->ltype_match = NPC_LT_LC_IP;
			field->ltype_mask = 0xF;
			अवरोध;
		हाल NIX_FLOW_KEY_TYPE_IPV4:
		हाल NIX_FLOW_KEY_TYPE_INNR_IPV4:
			field->lid = NPC_LID_LC;
			field->ltype_match = NPC_LT_LC_IP;
			अगर (key_type == NIX_FLOW_KEY_TYPE_INNR_IPV4) अणु
				field->lid = NPC_LID_LG;
				field->ltype_match = NPC_LT_LG_TU_IP;
			पूर्ण
			field->hdr_offset = 12; /* SIP offset */
			field->bytesm1 = 7; /* SIP + DIP, 8 bytes */
			field->ltype_mask = 0xF; /* Match only IPv4 */
			keyoff_marker = false;
			अवरोध;
		हाल NIX_FLOW_KEY_TYPE_IPV6:
		हाल NIX_FLOW_KEY_TYPE_INNR_IPV6:
			field->lid = NPC_LID_LC;
			field->ltype_match = NPC_LT_LC_IP6;
			अगर (key_type == NIX_FLOW_KEY_TYPE_INNR_IPV6) अणु
				field->lid = NPC_LID_LG;
				field->ltype_match = NPC_LT_LG_TU_IP6;
			पूर्ण
			field->hdr_offset = 8; /* SIP offset */
			field->bytesm1 = 31; /* SIP + DIP, 32 bytes */
			field->ltype_mask = 0xF; /* Match only IPv6 */
			अवरोध;
		हाल NIX_FLOW_KEY_TYPE_TCP:
		हाल NIX_FLOW_KEY_TYPE_UDP:
		हाल NIX_FLOW_KEY_TYPE_SCTP:
		हाल NIX_FLOW_KEY_TYPE_INNR_TCP:
		हाल NIX_FLOW_KEY_TYPE_INNR_UDP:
		हाल NIX_FLOW_KEY_TYPE_INNR_SCTP:
			field->lid = NPC_LID_LD;
			अगर (key_type == NIX_FLOW_KEY_TYPE_INNR_TCP ||
			    key_type == NIX_FLOW_KEY_TYPE_INNR_UDP ||
			    key_type == NIX_FLOW_KEY_TYPE_INNR_SCTP)
				field->lid = NPC_LID_LH;
			field->bytesm1 = 3; /* Sport + Dport, 4 bytes */

			/* Enum values क्रम NPC_LID_LD and NPC_LID_LG are same,
			 * so no need to change the ltype_match, just change
			 * the lid क्रम inner protocols
			 */
			BUILD_BUG_ON((पूर्णांक)NPC_LT_LD_TCP !=
				     (पूर्णांक)NPC_LT_LH_TU_TCP);
			BUILD_BUG_ON((पूर्णांक)NPC_LT_LD_UDP !=
				     (पूर्णांक)NPC_LT_LH_TU_UDP);
			BUILD_BUG_ON((पूर्णांक)NPC_LT_LD_SCTP !=
				     (पूर्णांक)NPC_LT_LH_TU_SCTP);

			अगर ((key_type == NIX_FLOW_KEY_TYPE_TCP ||
			     key_type == NIX_FLOW_KEY_TYPE_INNR_TCP) &&
			    valid_key) अणु
				field->ltype_match |= NPC_LT_LD_TCP;
				group_member = true;
			पूर्ण अन्यथा अगर ((key_type == NIX_FLOW_KEY_TYPE_UDP ||
				    key_type == NIX_FLOW_KEY_TYPE_INNR_UDP) &&
				   valid_key) अणु
				field->ltype_match |= NPC_LT_LD_UDP;
				group_member = true;
			पूर्ण अन्यथा अगर ((key_type == NIX_FLOW_KEY_TYPE_SCTP ||
				    key_type == NIX_FLOW_KEY_TYPE_INNR_SCTP) &&
				   valid_key) अणु
				field->ltype_match |= NPC_LT_LD_SCTP;
				group_member = true;
			पूर्ण
			field->ltype_mask = ~field->ltype_match;
			अगर (key_type == NIX_FLOW_KEY_TYPE_SCTP ||
			    key_type == NIX_FLOW_KEY_TYPE_INNR_SCTP) अणु
				/* Handle the हाल where any of the group item
				 * is enabled in the group but not the final one
				 */
				अगर (group_member) अणु
					valid_key = true;
					group_member = false;
				पूर्ण
			पूर्ण अन्यथा अणु
				field_marker = false;
				keyoff_marker = false;
			पूर्ण

			/* TCP/UDP/SCTP and ESP/AH falls at same offset so
			 * remember the TCP key offset of 40 byte hash key.
			 */
			अगर (key_type == NIX_FLOW_KEY_TYPE_TCP)
				l4_key_offset = key_off;
			अवरोध;
		हाल NIX_FLOW_KEY_TYPE_NVGRE:
			field->lid = NPC_LID_LD;
			field->hdr_offset = 4; /* VSID offset */
			field->bytesm1 = 2;
			field->ltype_match = NPC_LT_LD_NVGRE;
			field->ltype_mask = 0xF;
			अवरोध;
		हाल NIX_FLOW_KEY_TYPE_VXLAN:
		हाल NIX_FLOW_KEY_TYPE_GENEVE:
			field->lid = NPC_LID_LE;
			field->bytesm1 = 2;
			field->hdr_offset = 4;
			field->ltype_mask = 0xF;
			field_marker = false;
			keyoff_marker = false;

			अगर (key_type == NIX_FLOW_KEY_TYPE_VXLAN && valid_key) अणु
				field->ltype_match |= NPC_LT_LE_VXLAN;
				group_member = true;
			पूर्ण

			अगर (key_type == NIX_FLOW_KEY_TYPE_GENEVE && valid_key) अणु
				field->ltype_match |= NPC_LT_LE_GENEVE;
				group_member = true;
			पूर्ण

			अगर (key_type == NIX_FLOW_KEY_TYPE_GENEVE) अणु
				अगर (group_member) अणु
					field->ltype_mask = ~field->ltype_match;
					field_marker = true;
					keyoff_marker = true;
					valid_key = true;
					group_member = false;
				पूर्ण
			पूर्ण
			अवरोध;
		हाल NIX_FLOW_KEY_TYPE_ETH_DMAC:
		हाल NIX_FLOW_KEY_TYPE_INNR_ETH_DMAC:
			field->lid = NPC_LID_LA;
			field->ltype_match = NPC_LT_LA_ETHER;
			अगर (key_type == NIX_FLOW_KEY_TYPE_INNR_ETH_DMAC) अणु
				field->lid = NPC_LID_LF;
				field->ltype_match = NPC_LT_LF_TU_ETHER;
			पूर्ण
			field->hdr_offset = 0;
			field->bytesm1 = 5; /* DMAC 6 Byte */
			field->ltype_mask = 0xF;
			अवरोध;
		हाल NIX_FLOW_KEY_TYPE_IPV6_EXT:
			field->lid = NPC_LID_LC;
			field->hdr_offset = 40; /* IPV6 hdr */
			field->bytesm1 = 0; /* 1 Byte ext hdr*/
			field->ltype_match = NPC_LT_LC_IP6_EXT;
			field->ltype_mask = 0xF;
			अवरोध;
		हाल NIX_FLOW_KEY_TYPE_GTPU:
			field->lid = NPC_LID_LE;
			field->hdr_offset = 4;
			field->bytesm1 = 3; /* 4 bytes TID*/
			field->ltype_match = NPC_LT_LE_GTPU;
			field->ltype_mask = 0xF;
			अवरोध;
		हाल NIX_FLOW_KEY_TYPE_VLAN:
			field->lid = NPC_LID_LB;
			field->hdr_offset = 2; /* Skip TPID (2-bytes) */
			field->bytesm1 = 1; /* 2 Bytes (Actually 12 bits) */
			field->ltype_match = NPC_LT_LB_CTAG;
			field->ltype_mask = 0xF;
			field->fn_mask = 1; /* Mask out the first nibble */
			अवरोध;
		हाल NIX_FLOW_KEY_TYPE_AH:
		हाल NIX_FLOW_KEY_TYPE_ESP:
			field->hdr_offset = 0;
			field->bytesm1 = 7; /* SPI + sequence number */
			field->ltype_mask = 0xF;
			field->lid = NPC_LID_LE;
			field->ltype_match = NPC_LT_LE_ESP;
			अगर (key_type == NIX_FLOW_KEY_TYPE_AH) अणु
				field->lid = NPC_LID_LD;
				field->ltype_match = NPC_LT_LD_AH;
				field->hdr_offset = 4;
				keyoff_marker = false;
			पूर्ण
			अवरोध;
		पूर्ण
		field->ena = 1;

		/* Found a valid flow key type */
		अगर (valid_key) अणु
			/* Use the key offset of TCP/UDP/SCTP fields
			 * क्रम ESP/AH fields.
			 */
			अगर (key_type == NIX_FLOW_KEY_TYPE_ESP ||
			    key_type == NIX_FLOW_KEY_TYPE_AH)
				key_off = l4_key_offset;
			field->key_offset = key_off;
			स_नकल(&alg[nr_field], field, माप(*field));
			max_key_off = max(max_key_off, field->bytesm1 + 1);

			/* Found a field marker, get the next field */
			अगर (field_marker)
				nr_field++;
		पूर्ण

		/* Found a keyoff marker, update the new key_off */
		अगर (keyoff_marker) अणु
			key_off += max_key_off;
			max_key_off = 0;
		पूर्ण
	पूर्ण
	/* Processed all the flow key types */
	अगर (idx == max_bit_pos && key_off <= MAX_KEY_OFF)
		वापस 0;
	अन्यथा
		वापस NIX_AF_ERR_RSS_NOSPC_FIELD;
पूर्ण

अटल पूर्णांक reserve_flowkey_alg_idx(काष्ठा rvu *rvu, पूर्णांक blkaddr, u32 flow_cfg)
अणु
	u64 field[FIELDS_PER_ALG];
	काष्ठा nix_hw *hw;
	पूर्णांक fid, rc;

	hw = get_nix_hw(rvu->hw, blkaddr);
	अगर (!hw)
		वापस -EINVAL;

	/* No room to add new flow hash algoritham */
	अगर (hw->flowkey.in_use >= NIX_FLOW_KEY_ALG_MAX)
		वापस NIX_AF_ERR_RSS_NOSPC_ALGO;

	/* Generate algo fields क्रम the given flow_cfg */
	rc = set_flowkey_fields((काष्ठा nix_rx_flowkey_alg *)field, flow_cfg);
	अगर (rc)
		वापस rc;

	/* Update ALGX_FIELDX रेजिस्टर with generated fields */
	क्रम (fid = 0; fid < FIELDS_PER_ALG; fid++)
		rvu_ग_लिखो64(rvu, blkaddr,
			    NIX_AF_RX_FLOW_KEY_ALGX_FIELDX(hw->flowkey.in_use,
							   fid), field[fid]);

	/* Store the flow_cfg क्रम futher lookup */
	rc = hw->flowkey.in_use;
	hw->flowkey.flowkey[rc] = flow_cfg;
	hw->flowkey.in_use++;

	वापस rc;
पूर्ण

पूर्णांक rvu_mbox_handler_nix_rss_flowkey_cfg(काष्ठा rvu *rvu,
					 काष्ठा nix_rss_flowkey_cfg *req,
					 काष्ठा nix_rss_flowkey_cfg_rsp *rsp)
अणु
	u16 pcअगरunc = req->hdr.pcअगरunc;
	पूर्णांक alg_idx, nixlf, blkaddr;
	काष्ठा nix_hw *nix_hw;
	पूर्णांक err;

	err = nix_get_nixlf(rvu, pcअगरunc, &nixlf, &blkaddr);
	अगर (err)
		वापस err;

	nix_hw = get_nix_hw(rvu->hw, blkaddr);
	अगर (!nix_hw)
		वापस -EINVAL;

	alg_idx = get_flowkey_alg_idx(nix_hw, req->flowkey_cfg);
	/* Failed to get algo index from the निकासing list, reserve new  */
	अगर (alg_idx < 0) अणु
		alg_idx = reserve_flowkey_alg_idx(rvu, blkaddr,
						  req->flowkey_cfg);
		अगर (alg_idx < 0)
			वापस alg_idx;
	पूर्ण
	rsp->alg_idx = alg_idx;
	rvu_npc_update_flowkey_alg_idx(rvu, pcअगरunc, nixlf, req->group,
				       alg_idx, req->mcam_index);
	वापस 0;
पूर्ण

अटल पूर्णांक nix_rx_flowkey_alg_cfg(काष्ठा rvu *rvu, पूर्णांक blkaddr)
अणु
	u32 flowkey_cfg, minkey_cfg;
	पूर्णांक alg, fid, rc;

	/* Disable all flow key algx fieldx */
	क्रम (alg = 0; alg < NIX_FLOW_KEY_ALG_MAX; alg++) अणु
		क्रम (fid = 0; fid < FIELDS_PER_ALG; fid++)
			rvu_ग_लिखो64(rvu, blkaddr,
				    NIX_AF_RX_FLOW_KEY_ALGX_FIELDX(alg, fid),
				    0);
	पूर्ण

	/* IPv4/IPv6 SIP/DIPs */
	flowkey_cfg = NIX_FLOW_KEY_TYPE_IPV4 | NIX_FLOW_KEY_TYPE_IPV6;
	rc = reserve_flowkey_alg_idx(rvu, blkaddr, flowkey_cfg);
	अगर (rc < 0)
		वापस rc;

	/* TCPv4/v6 4-tuple, SIP, DIP, Sport, Dport */
	minkey_cfg = flowkey_cfg;
	flowkey_cfg = minkey_cfg | NIX_FLOW_KEY_TYPE_TCP;
	rc = reserve_flowkey_alg_idx(rvu, blkaddr, flowkey_cfg);
	अगर (rc < 0)
		वापस rc;

	/* UDPv4/v6 4-tuple, SIP, DIP, Sport, Dport */
	flowkey_cfg = minkey_cfg | NIX_FLOW_KEY_TYPE_UDP;
	rc = reserve_flowkey_alg_idx(rvu, blkaddr, flowkey_cfg);
	अगर (rc < 0)
		वापस rc;

	/* SCTPv4/v6 4-tuple, SIP, DIP, Sport, Dport */
	flowkey_cfg = minkey_cfg | NIX_FLOW_KEY_TYPE_SCTP;
	rc = reserve_flowkey_alg_idx(rvu, blkaddr, flowkey_cfg);
	अगर (rc < 0)
		वापस rc;

	/* TCP/UDP v4/v6 4-tuple, rest IP pkts 2-tuple */
	flowkey_cfg = minkey_cfg | NIX_FLOW_KEY_TYPE_TCP |
			NIX_FLOW_KEY_TYPE_UDP;
	rc = reserve_flowkey_alg_idx(rvu, blkaddr, flowkey_cfg);
	अगर (rc < 0)
		वापस rc;

	/* TCP/SCTP v4/v6 4-tuple, rest IP pkts 2-tuple */
	flowkey_cfg = minkey_cfg | NIX_FLOW_KEY_TYPE_TCP |
			NIX_FLOW_KEY_TYPE_SCTP;
	rc = reserve_flowkey_alg_idx(rvu, blkaddr, flowkey_cfg);
	अगर (rc < 0)
		वापस rc;

	/* UDP/SCTP v4/v6 4-tuple, rest IP pkts 2-tuple */
	flowkey_cfg = minkey_cfg | NIX_FLOW_KEY_TYPE_UDP |
			NIX_FLOW_KEY_TYPE_SCTP;
	rc = reserve_flowkey_alg_idx(rvu, blkaddr, flowkey_cfg);
	अगर (rc < 0)
		वापस rc;

	/* TCP/UDP/SCTP v4/v6 4-tuple, rest IP pkts 2-tuple */
	flowkey_cfg = minkey_cfg | NIX_FLOW_KEY_TYPE_TCP |
		      NIX_FLOW_KEY_TYPE_UDP | NIX_FLOW_KEY_TYPE_SCTP;
	rc = reserve_flowkey_alg_idx(rvu, blkaddr, flowkey_cfg);
	अगर (rc < 0)
		वापस rc;

	वापस 0;
पूर्ण

पूर्णांक rvu_mbox_handler_nix_set_mac_addr(काष्ठा rvu *rvu,
				      काष्ठा nix_set_mac_addr *req,
				      काष्ठा msg_rsp *rsp)
अणु
	bool from_vf = req->hdr.pcअगरunc & RVU_PFVF_FUNC_MASK;
	u16 pcअगरunc = req->hdr.pcअगरunc;
	पूर्णांक blkaddr, nixlf, err;
	काष्ठा rvu_pfvf *pfvf;

	err = nix_get_nixlf(rvu, pcअगरunc, &nixlf, &blkaddr);
	अगर (err)
		वापस err;

	pfvf = rvu_get_pfvf(rvu, pcअगरunc);

	/* VF can't overग_लिखो admin(PF) changes */
	अगर (from_vf && pfvf->pf_set_vf_cfg)
		वापस -EPERM;

	ether_addr_copy(pfvf->mac_addr, req->mac_addr);

	rvu_npc_install_ucast_entry(rvu, pcअगरunc, nixlf,
				    pfvf->rx_chan_base, req->mac_addr);

	वापस 0;
पूर्ण

पूर्णांक rvu_mbox_handler_nix_get_mac_addr(काष्ठा rvu *rvu,
				      काष्ठा msg_req *req,
				      काष्ठा nix_get_mac_addr_rsp *rsp)
अणु
	u16 pcअगरunc = req->hdr.pcअगरunc;
	काष्ठा rvu_pfvf *pfvf;

	अगर (!is_nixlf_attached(rvu, pcअगरunc))
		वापस NIX_AF_ERR_AF_LF_INVALID;

	pfvf = rvu_get_pfvf(rvu, pcअगरunc);

	ether_addr_copy(rsp->mac_addr, pfvf->mac_addr);

	वापस 0;
पूर्ण

पूर्णांक rvu_mbox_handler_nix_set_rx_mode(काष्ठा rvu *rvu, काष्ठा nix_rx_mode *req,
				     काष्ठा msg_rsp *rsp)
अणु
	bool allmulti = false, disable_promisc = false;
	u16 pcअगरunc = req->hdr.pcअगरunc;
	पूर्णांक blkaddr, nixlf, err;
	काष्ठा rvu_pfvf *pfvf;

	err = nix_get_nixlf(rvu, pcअगरunc, &nixlf, &blkaddr);
	अगर (err)
		वापस err;

	pfvf = rvu_get_pfvf(rvu, pcअगरunc);

	अगर (req->mode & NIX_RX_MODE_PROMISC)
		allmulti = false;
	अन्यथा अगर (req->mode & NIX_RX_MODE_ALLMULTI)
		allmulti = true;
	अन्यथा
		disable_promisc = true;

	अगर (disable_promisc)
		rvu_npc_disable_promisc_entry(rvu, pcअगरunc, nixlf);
	अन्यथा
		rvu_npc_install_promisc_entry(rvu, pcअगरunc, nixlf,
					      pfvf->rx_chan_base,
					      pfvf->rx_chan_cnt, allmulti);
	वापस 0;
पूर्ण

अटल व्योम nix_find_link_frs(काष्ठा rvu *rvu,
			      काष्ठा nix_frs_cfg *req, u16 pcअगरunc)
अणु
	पूर्णांक pf = rvu_get_pf(pcअगरunc);
	काष्ठा rvu_pfvf *pfvf;
	पूर्णांक maxlen, minlen;
	पूर्णांक numvfs, hwvf;
	पूर्णांक vf;

	/* Update with requester's min/max lengths */
	pfvf = rvu_get_pfvf(rvu, pcअगरunc);
	pfvf->maxlen = req->maxlen;
	अगर (req->update_minlen)
		pfvf->minlen = req->minlen;

	maxlen = req->maxlen;
	minlen = req->update_minlen ? req->minlen : 0;

	/* Get this PF's numVFs and starting hwvf */
	rvu_get_pf_numvfs(rvu, pf, &numvfs, &hwvf);

	/* For each VF, compare requested max/minlen */
	क्रम (vf = 0; vf < numvfs; vf++) अणु
		pfvf =  &rvu->hwvf[hwvf + vf];
		अगर (pfvf->maxlen > maxlen)
			maxlen = pfvf->maxlen;
		अगर (req->update_minlen &&
		    pfvf->minlen && pfvf->minlen < minlen)
			minlen = pfvf->minlen;
	पूर्ण

	/* Compare requested max/minlen with PF's max/minlen */
	pfvf = &rvu->pf[pf];
	अगर (pfvf->maxlen > maxlen)
		maxlen = pfvf->maxlen;
	अगर (req->update_minlen &&
	    pfvf->minlen && pfvf->minlen < minlen)
		minlen = pfvf->minlen;

	/* Update the request with max/min PF's and it's VF's max/min */
	req->maxlen = maxlen;
	अगर (req->update_minlen)
		req->minlen = minlen;
पूर्ण

पूर्णांक rvu_mbox_handler_nix_set_hw_frs(काष्ठा rvu *rvu, काष्ठा nix_frs_cfg *req,
				    काष्ठा msg_rsp *rsp)
अणु
	काष्ठा rvu_hwinfo *hw = rvu->hw;
	u16 pcअगरunc = req->hdr.pcअगरunc;
	पूर्णांक pf = rvu_get_pf(pcअगरunc);
	पूर्णांक blkaddr, schq, link = -1;
	काष्ठा nix_txsch *txsch;
	u64 cfg, lmac_fअगरo_len;
	काष्ठा nix_hw *nix_hw;
	u8 cgx = 0, lmac = 0;
	u16 max_mtu;

	blkaddr = rvu_get_blkaddr(rvu, BLKTYPE_NIX, pcअगरunc);
	अगर (blkaddr < 0)
		वापस NIX_AF_ERR_AF_LF_INVALID;

	nix_hw = get_nix_hw(rvu->hw, blkaddr);
	अगर (!nix_hw)
		वापस -EINVAL;

	अगर (is_afvf(pcअगरunc))
		rvu_get_lbk_link_max_frs(rvu, &max_mtu);
	अन्यथा
		rvu_get_lmac_link_max_frs(rvu, &max_mtu);

	अगर (!req->sdp_link && req->maxlen > max_mtu)
		वापस NIX_AF_ERR_FRS_INVALID;

	अगर (req->update_minlen && req->minlen < NIC_HW_MIN_FRS)
		वापस NIX_AF_ERR_FRS_INVALID;

	/* Check अगर requester wants to update SMQ's */
	अगर (!req->update_smq)
		जाओ rx_frscfg;

	/* Update min/maxlen in each of the SMQ attached to this PF/VF */
	txsch = &nix_hw->txsch[NIX_TXSCH_LVL_SMQ];
	mutex_lock(&rvu->rsrc_lock);
	क्रम (schq = 0; schq < txsch->schq.max; schq++) अणु
		अगर (TXSCH_MAP_FUNC(txsch->pfvf_map[schq]) != pcअगरunc)
			जारी;
		cfg = rvu_पढ़ो64(rvu, blkaddr, NIX_AF_SMQX_CFG(schq));
		cfg = (cfg & ~(0xFFFFULL << 8)) | ((u64)req->maxlen << 8);
		अगर (req->update_minlen)
			cfg = (cfg & ~0x7FULL) | ((u64)req->minlen & 0x7F);
		rvu_ग_लिखो64(rvu, blkaddr, NIX_AF_SMQX_CFG(schq), cfg);
	पूर्ण
	mutex_unlock(&rvu->rsrc_lock);

rx_frscfg:
	/* Check अगर config is क्रम SDP link */
	अगर (req->sdp_link) अणु
		अगर (!hw->sdp_links)
			वापस NIX_AF_ERR_RX_LINK_INVALID;
		link = hw->cgx_links + hw->lbk_links;
		जाओ linkcfg;
	पूर्ण

	/* Check अगर the request is from CGX mapped RVU PF */
	अगर (is_pf_cgxmapped(rvu, pf)) अणु
		/* Get CGX and LMAC to which this PF is mapped and find link */
		rvu_get_cgx_lmac_id(rvu->pf2cgxlmac_map[pf], &cgx, &lmac);
		link = (cgx * hw->lmac_per_cgx) + lmac;
	पूर्ण अन्यथा अगर (pf == 0) अणु
		/* For VFs of PF0 ingress is LBK port, so config LBK link */
		link = hw->cgx_links;
	पूर्ण

	अगर (link < 0)
		वापस NIX_AF_ERR_RX_LINK_INVALID;

	nix_find_link_frs(rvu, req, pcअगरunc);

linkcfg:
	cfg = rvu_पढ़ो64(rvu, blkaddr, NIX_AF_RX_LINKX_CFG(link));
	cfg = (cfg & ~(0xFFFFULL << 16)) | ((u64)req->maxlen << 16);
	अगर (req->update_minlen)
		cfg = (cfg & ~0xFFFFULL) | req->minlen;
	rvu_ग_लिखो64(rvu, blkaddr, NIX_AF_RX_LINKX_CFG(link), cfg);

	अगर (req->sdp_link || pf == 0)
		वापस 0;

	/* Update transmit credits क्रम CGX links */
	lmac_fअगरo_len =
		rvu_cgx_get_fअगरolen(rvu) /
		cgx_get_lmac_cnt(rvu_cgx_pdata(cgx, rvu));
	cfg = rvu_पढ़ो64(rvu, blkaddr, NIX_AF_TX_LINKX_NORM_CREDIT(link));
	cfg &= ~(0xFFFFFULL << 12);
	cfg |=  ((lmac_fअगरo_len - req->maxlen) / 16) << 12;
	rvu_ग_लिखो64(rvu, blkaddr, NIX_AF_TX_LINKX_NORM_CREDIT(link), cfg);
	वापस 0;
पूर्ण

पूर्णांक rvu_mbox_handler_nix_set_rx_cfg(काष्ठा rvu *rvu, काष्ठा nix_rx_cfg *req,
				    काष्ठा msg_rsp *rsp)
अणु
	पूर्णांक nixlf, blkaddr, err;
	u64 cfg;

	err = nix_get_nixlf(rvu, req->hdr.pcअगरunc, &nixlf, &blkaddr);
	अगर (err)
		वापस err;

	cfg = rvu_पढ़ो64(rvu, blkaddr, NIX_AF_LFX_RX_CFG(nixlf));
	/* Set the पूर्णांकerface configuration */
	अगर (req->len_verअगरy & BIT(0))
		cfg |= BIT_ULL(41);
	अन्यथा
		cfg &= ~BIT_ULL(41);

	अगर (req->len_verअगरy & BIT(1))
		cfg |= BIT_ULL(40);
	अन्यथा
		cfg &= ~BIT_ULL(40);

	अगर (req->csum_verअगरy & BIT(0))
		cfg |= BIT_ULL(37);
	अन्यथा
		cfg &= ~BIT_ULL(37);

	rvu_ग_लिखो64(rvu, blkaddr, NIX_AF_LFX_RX_CFG(nixlf), cfg);

	वापस 0;
पूर्ण

अटल u64 rvu_get_lbk_link_credits(काष्ठा rvu *rvu, u16 lbk_max_frs)
अणु
	/* CN10k supports 72KB FIFO size and max packet size of 64k */
	अगर (rvu->hw->lbk_bufsize == 0x12000)
		वापस (rvu->hw->lbk_bufsize - lbk_max_frs) / 16;

	वापस 1600; /* 16 * max LBK datarate = 16 * 100Gbps */
पूर्ण

अटल व्योम nix_link_config(काष्ठा rvu *rvu, पूर्णांक blkaddr)
अणु
	काष्ठा rvu_hwinfo *hw = rvu->hw;
	पूर्णांक cgx, lmac_cnt, slink, link;
	u16 lbk_max_frs, lmac_max_frs;
	u64 tx_credits;

	rvu_get_lbk_link_max_frs(rvu, &lbk_max_frs);
	rvu_get_lmac_link_max_frs(rvu, &lmac_max_frs);

	/* Set शेष min/max packet lengths allowed on NIX Rx links.
	 *
	 * With HW reset minlen value of 60byte, HW will treat ARP pkts
	 * as undersize and report them to SW as error pkts, hence
	 * setting it to 40 bytes.
	 */
	क्रम (link = 0; link < hw->cgx_links; link++) अणु
		rvu_ग_लिखो64(rvu, blkaddr, NIX_AF_RX_LINKX_CFG(link),
				((u64)lmac_max_frs << 16) | NIC_HW_MIN_FRS);
	पूर्ण

	क्रम (link = hw->cgx_links; link < hw->lbk_links; link++) अणु
		rvu_ग_लिखो64(rvu, blkaddr, NIX_AF_RX_LINKX_CFG(link),
			    ((u64)lbk_max_frs << 16) | NIC_HW_MIN_FRS);
	पूर्ण
	अगर (hw->sdp_links) अणु
		link = hw->cgx_links + hw->lbk_links;
		rvu_ग_लिखो64(rvu, blkaddr, NIX_AF_RX_LINKX_CFG(link),
			    SDP_HW_MAX_FRS << 16 | NIC_HW_MIN_FRS);
	पूर्ण

	/* Set credits क्रम Tx links assuming max packet length allowed.
	 * This will be reconfigured based on MTU set क्रम PF/VF.
	 */
	क्रम (cgx = 0; cgx < hw->cgx; cgx++) अणु
		lmac_cnt = cgx_get_lmac_cnt(rvu_cgx_pdata(cgx, rvu));
		tx_credits = ((rvu_cgx_get_fअगरolen(rvu) / lmac_cnt) -
			       lmac_max_frs) / 16;
		/* Enable credits and set credit pkt count to max allowed */
		tx_credits =  (tx_credits << 12) | (0x1FF << 2) | BIT_ULL(1);
		slink = cgx * hw->lmac_per_cgx;
		क्रम (link = slink; link < (slink + lmac_cnt); link++) अणु
			rvu_ग_लिखो64(rvu, blkaddr,
				    NIX_AF_TX_LINKX_NORM_CREDIT(link),
				    tx_credits);
		पूर्ण
	पूर्ण

	/* Set Tx credits क्रम LBK link */
	slink = hw->cgx_links;
	क्रम (link = slink; link < (slink + hw->lbk_links); link++) अणु
		tx_credits = rvu_get_lbk_link_credits(rvu, lbk_max_frs);
		/* Enable credits and set credit pkt count to max allowed */
		tx_credits =  (tx_credits << 12) | (0x1FF << 2) | BIT_ULL(1);
		rvu_ग_लिखो64(rvu, blkaddr,
			    NIX_AF_TX_LINKX_NORM_CREDIT(link), tx_credits);
	पूर्ण
पूर्ण

अटल पूर्णांक nix_calibrate_x2p(काष्ठा rvu *rvu, पूर्णांक blkaddr)
अणु
	पूर्णांक idx, err;
	u64 status;

	/* Start X2P bus calibration */
	rvu_ग_लिखो64(rvu, blkaddr, NIX_AF_CFG,
		    rvu_पढ़ो64(rvu, blkaddr, NIX_AF_CFG) | BIT_ULL(9));
	/* Wait क्रम calibration to complete */
	err = rvu_poll_reg(rvu, blkaddr,
			   NIX_AF_STATUS, BIT_ULL(10), false);
	अगर (err) अणु
		dev_err(rvu->dev, "NIX X2P bus calibration failed\n");
		वापस err;
	पूर्ण

	status = rvu_पढ़ो64(rvu, blkaddr, NIX_AF_STATUS);
	/* Check अगर CGX devices are पढ़ोy */
	क्रम (idx = 0; idx < rvu->cgx_cnt_max; idx++) अणु
		/* Skip when cgx port is not available */
		अगर (!rvu_cgx_pdata(idx, rvu) ||
		    (status & (BIT_ULL(16 + idx))))
			जारी;
		dev_err(rvu->dev,
			"CGX%d didn't respond to NIX X2P calibration\n", idx);
		err = -EBUSY;
	पूर्ण

	/* Check अगर LBK is पढ़ोy */
	अगर (!(status & BIT_ULL(19))) अणु
		dev_err(rvu->dev,
			"LBK didn't respond to NIX X2P calibration\n");
		err = -EBUSY;
	पूर्ण

	/* Clear 'calibrate_x2p' bit */
	rvu_ग_लिखो64(rvu, blkaddr, NIX_AF_CFG,
		    rvu_पढ़ो64(rvu, blkaddr, NIX_AF_CFG) & ~BIT_ULL(9));
	अगर (err || (status & 0x3FFULL))
		dev_err(rvu->dev,
			"NIX X2P calibration failed, status 0x%llx\n", status);
	अगर (err)
		वापस err;
	वापस 0;
पूर्ण

अटल पूर्णांक nix_aq_init(काष्ठा rvu *rvu, काष्ठा rvu_block *block)
अणु
	u64 cfg;
	पूर्णांक err;

	/* Set admin queue endianness */
	cfg = rvu_पढ़ो64(rvu, block->addr, NIX_AF_CFG);
#अगर_घोषित __BIG_ENDIAN
	cfg |= BIT_ULL(8);
	rvu_ग_लिखो64(rvu, block->addr, NIX_AF_CFG, cfg);
#अन्यथा
	cfg &= ~BIT_ULL(8);
	rvu_ग_लिखो64(rvu, block->addr, NIX_AF_CFG, cfg);
#पूर्ण_अगर

	/* Do not bypass NDC cache */
	cfg = rvu_पढ़ो64(rvu, block->addr, NIX_AF_NDC_CFG);
	cfg &= ~0x3FFEULL;
#अगर_घोषित CONFIG_NDC_DIS_DYNAMIC_CACHING
	/* Disable caching of SQB aka SQEs */
	cfg |= 0x04ULL;
#पूर्ण_अगर
	rvu_ग_लिखो64(rvu, block->addr, NIX_AF_NDC_CFG, cfg);

	/* Result काष्ठाure can be followed by RQ/SQ/CQ context at
	 * RES + 128bytes and a ग_लिखो mask at RES + 256 bytes, depending on
	 * operation type. Alloc sufficient result memory क्रम all operations.
	 */
	err = rvu_aq_alloc(rvu, &block->aq,
			   Q_COUNT(AQ_SIZE), माप(काष्ठा nix_aq_inst_s),
			   ALIGN(माप(काष्ठा nix_aq_res_s), 128) + 256);
	अगर (err)
		वापस err;

	rvu_ग_लिखो64(rvu, block->addr, NIX_AF_AQ_CFG, AQ_SIZE);
	rvu_ग_लिखो64(rvu, block->addr,
		    NIX_AF_AQ_BASE, (u64)block->aq->inst->iova);
	वापस 0;
पूर्ण

अटल पूर्णांक rvu_nix_block_init(काष्ठा rvu *rvu, काष्ठा nix_hw *nix_hw)
अणु
	स्थिर काष्ठा npc_lt_def_cfg *ltdefs;
	काष्ठा rvu_hwinfo *hw = rvu->hw;
	पूर्णांक blkaddr = nix_hw->blkaddr;
	काष्ठा rvu_block *block;
	पूर्णांक err;
	u64 cfg;

	block = &hw->block[blkaddr];

	अगर (is_rvu_96xx_B0(rvu)) अणु
		/* As per a HW errata in 96xx A0/B0 silicon, NIX may corrupt
		 * पूर्णांकernal state when conditional घड़ीs are turned off.
		 * Hence enable them.
		 */
		rvu_ग_लिखो64(rvu, blkaddr, NIX_AF_CFG,
			    rvu_पढ़ो64(rvu, blkaddr, NIX_AF_CFG) | 0x40ULL);

		/* Set chan/link to backpressure TL3 instead of TL2 */
		rvu_ग_लिखो64(rvu, blkaddr, NIX_AF_PSE_CHANNEL_LEVEL, 0x01);

		/* Disable SQ manager's sticky mode operation (set TM6 = 0)
		 * This sticky mode is known to cause SQ stalls when multiple
		 * SQs are mapped to same SMQ and transmitting pkts at a समय.
		 */
		cfg = rvu_पढ़ो64(rvu, blkaddr, NIX_AF_SQM_DBG_CTL_STATUS);
		cfg &= ~BIT_ULL(15);
		rvu_ग_लिखो64(rvu, blkaddr, NIX_AF_SQM_DBG_CTL_STATUS, cfg);
	पूर्ण

	ltdefs = rvu->kpu.lt_def;
	/* Calibrate X2P bus to check अगर CGX/LBK links are fine */
	err = nix_calibrate_x2p(rvu, blkaddr);
	अगर (err)
		वापस err;

	/* Initialize admin queue */
	err = nix_aq_init(rvu, block);
	अगर (err)
		वापस err;

	/* Restore CINT समयr delay to HW reset values */
	rvu_ग_लिखो64(rvu, blkaddr, NIX_AF_CINT_DELAY, 0x0ULL);

	अगर (is_block_implemented(hw, blkaddr)) अणु
		err = nix_setup_txschq(rvu, nix_hw, blkaddr);
		अगर (err)
			वापस err;

		err = nix_af_mark_क्रमmat_setup(rvu, nix_hw, blkaddr);
		अगर (err)
			वापस err;

		err = nix_setup_mcast(rvu, nix_hw, blkaddr);
		अगर (err)
			वापस err;

		err = nix_setup_txvlan(rvu, nix_hw);
		अगर (err)
			वापस err;

		/* Configure segmentation offload क्रमmats */
		nix_setup_lso(rvu, nix_hw, blkaddr);

		/* Config Outer/Inner L2, IP, TCP, UDP and SCTP NPC layer info.
		 * This helps HW protocol checker to identअगरy headers
		 * and validate length and checksums.
		 */
		rvu_ग_लिखो64(rvu, blkaddr, NIX_AF_RX_DEF_OL2,
			    (ltdefs->rx_ol2.lid << 8) | (ltdefs->rx_ol2.ltype_match << 4) |
			    ltdefs->rx_ol2.ltype_mask);
		rvu_ग_लिखो64(rvu, blkaddr, NIX_AF_RX_DEF_OIP4,
			    (ltdefs->rx_oip4.lid << 8) | (ltdefs->rx_oip4.ltype_match << 4) |
			    ltdefs->rx_oip4.ltype_mask);
		rvu_ग_लिखो64(rvu, blkaddr, NIX_AF_RX_DEF_IIP4,
			    (ltdefs->rx_iip4.lid << 8) | (ltdefs->rx_iip4.ltype_match << 4) |
			    ltdefs->rx_iip4.ltype_mask);
		rvu_ग_लिखो64(rvu, blkaddr, NIX_AF_RX_DEF_OIP6,
			    (ltdefs->rx_oip6.lid << 8) | (ltdefs->rx_oip6.ltype_match << 4) |
			    ltdefs->rx_oip6.ltype_mask);
		rvu_ग_लिखो64(rvu, blkaddr, NIX_AF_RX_DEF_IIP6,
			    (ltdefs->rx_iip6.lid << 8) | (ltdefs->rx_iip6.ltype_match << 4) |
			    ltdefs->rx_iip6.ltype_mask);
		rvu_ग_लिखो64(rvu, blkaddr, NIX_AF_RX_DEF_OTCP,
			    (ltdefs->rx_otcp.lid << 8) | (ltdefs->rx_otcp.ltype_match << 4) |
			    ltdefs->rx_otcp.ltype_mask);
		rvu_ग_लिखो64(rvu, blkaddr, NIX_AF_RX_DEF_ITCP,
			    (ltdefs->rx_itcp.lid << 8) | (ltdefs->rx_itcp.ltype_match << 4) |
			    ltdefs->rx_itcp.ltype_mask);
		rvu_ग_लिखो64(rvu, blkaddr, NIX_AF_RX_DEF_OUDP,
			    (ltdefs->rx_oudp.lid << 8) | (ltdefs->rx_oudp.ltype_match << 4) |
			    ltdefs->rx_oudp.ltype_mask);
		rvu_ग_लिखो64(rvu, blkaddr, NIX_AF_RX_DEF_IUDP,
			    (ltdefs->rx_iudp.lid << 8) | (ltdefs->rx_iudp.ltype_match << 4) |
			    ltdefs->rx_iudp.ltype_mask);
		rvu_ग_लिखो64(rvu, blkaddr, NIX_AF_RX_DEF_OSCTP,
			    (ltdefs->rx_osctp.lid << 8) | (ltdefs->rx_osctp.ltype_match << 4) |
			    ltdefs->rx_osctp.ltype_mask);
		rvu_ग_लिखो64(rvu, blkaddr, NIX_AF_RX_DEF_ISCTP,
			    (ltdefs->rx_isctp.lid << 8) | (ltdefs->rx_isctp.ltype_match << 4) |
			    ltdefs->rx_isctp.ltype_mask);

		err = nix_rx_flowkey_alg_cfg(rvu, blkaddr);
		अगर (err)
			वापस err;

		/* Initialize CGX/LBK/SDP link credits, min/max pkt lengths */
		nix_link_config(rvu, blkaddr);

		/* Enable Channel backpressure */
		rvu_ग_लिखो64(rvu, blkaddr, NIX_AF_RX_CFG, BIT_ULL(0));
	पूर्ण
	वापस 0;
पूर्ण

पूर्णांक rvu_nix_init(काष्ठा rvu *rvu)
अणु
	काष्ठा rvu_hwinfo *hw = rvu->hw;
	काष्ठा nix_hw *nix_hw;
	पूर्णांक blkaddr = 0, err;
	पूर्णांक i = 0;

	hw->nix = devm_kसुस्मृति(rvu->dev, MAX_NIX_BLKS, माप(काष्ठा nix_hw),
			       GFP_KERNEL);
	अगर (!hw->nix)
		वापस -ENOMEM;

	blkaddr = rvu_get_next_nix_blkaddr(rvu, blkaddr);
	जबतक (blkaddr) अणु
		nix_hw = &hw->nix[i];
		nix_hw->rvu = rvu;
		nix_hw->blkaddr = blkaddr;
		err = rvu_nix_block_init(rvu, nix_hw);
		अगर (err)
			वापस err;
		blkaddr = rvu_get_next_nix_blkaddr(rvu, blkaddr);
		i++;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम rvu_nix_block_मुक्तmem(काष्ठा rvu *rvu, पूर्णांक blkaddr,
				  काष्ठा rvu_block *block)
अणु
	काष्ठा nix_txsch *txsch;
	काष्ठा nix_mcast *mcast;
	काष्ठा nix_txvlan *vlan;
	काष्ठा nix_hw *nix_hw;
	पूर्णांक lvl;

	rvu_aq_मुक्त(rvu, block->aq);

	अगर (is_block_implemented(rvu->hw, blkaddr)) अणु
		nix_hw = get_nix_hw(rvu->hw, blkaddr);
		अगर (!nix_hw)
			वापस;

		क्रम (lvl = 0; lvl < NIX_TXSCH_LVL_CNT; lvl++) अणु
			txsch = &nix_hw->txsch[lvl];
			kमुक्त(txsch->schq.bmap);
		पूर्ण

		vlan = &nix_hw->txvlan;
		kमुक्त(vlan->rsrc.bmap);
		mutex_destroy(&vlan->rsrc_lock);
		devm_kमुक्त(rvu->dev, vlan->entry2pfvf_map);

		mcast = &nix_hw->mcast;
		qmem_मुक्त(rvu->dev, mcast->mce_ctx);
		qmem_मुक्त(rvu->dev, mcast->mcast_buf);
		mutex_destroy(&mcast->mce_lock);
	पूर्ण
पूर्ण

व्योम rvu_nix_मुक्तmem(काष्ठा rvu *rvu)
अणु
	काष्ठा rvu_hwinfo *hw = rvu->hw;
	काष्ठा rvu_block *block;
	पूर्णांक blkaddr = 0;

	blkaddr = rvu_get_next_nix_blkaddr(rvu, blkaddr);
	जबतक (blkaddr) अणु
		block = &hw->block[blkaddr];
		rvu_nix_block_मुक्तmem(rvu, blkaddr, block);
		blkaddr = rvu_get_next_nix_blkaddr(rvu, blkaddr);
	पूर्ण
पूर्ण

पूर्णांक rvu_mbox_handler_nix_lf_start_rx(काष्ठा rvu *rvu, काष्ठा msg_req *req,
				     काष्ठा msg_rsp *rsp)
अणु
	u16 pcअगरunc = req->hdr.pcअगरunc;
	पूर्णांक nixlf, err;

	err = nix_get_nixlf(rvu, pcअगरunc, &nixlf, शून्य);
	अगर (err)
		वापस err;

	rvu_npc_enable_शेष_entries(rvu, pcअगरunc, nixlf);

	npc_mcam_enable_flows(rvu, pcअगरunc);

	वापस rvu_cgx_start_stop_io(rvu, pcअगरunc, true);
पूर्ण

पूर्णांक rvu_mbox_handler_nix_lf_stop_rx(काष्ठा rvu *rvu, काष्ठा msg_req *req,
				    काष्ठा msg_rsp *rsp)
अणु
	u16 pcअगरunc = req->hdr.pcअगरunc;
	पूर्णांक nixlf, err;

	err = nix_get_nixlf(rvu, pcअगरunc, &nixlf, शून्य);
	अगर (err)
		वापस err;

	rvu_npc_disable_mcam_entries(rvu, pcअगरunc, nixlf);

	वापस rvu_cgx_start_stop_io(rvu, pcअगरunc, false);
पूर्ण

व्योम rvu_nix_lf_tearकरोwn(काष्ठा rvu *rvu, u16 pcअगरunc, पूर्णांक blkaddr, पूर्णांक nixlf)
अणु
	काष्ठा rvu_pfvf *pfvf = rvu_get_pfvf(rvu, pcअगरunc);
	काष्ठा hwctx_disable_req ctx_req;
	पूर्णांक err;

	ctx_req.hdr.pcअगरunc = pcअगरunc;

	/* Cleanup NPC MCAM entries, मुक्त Tx scheduler queues being used */
	rvu_npc_disable_mcam_entries(rvu, pcअगरunc, nixlf);
	rvu_npc_मुक्त_mcam_entries(rvu, pcअगरunc, nixlf);
	nix_पूर्णांकerface_deinit(rvu, pcअगरunc, nixlf);
	nix_rx_sync(rvu, blkaddr);
	nix_txschq_मुक्त(rvu, pcअगरunc);

	rvu_cgx_start_stop_io(rvu, pcअगरunc, false);

	अगर (pfvf->sq_ctx) अणु
		ctx_req.ctype = NIX_AQ_CTYPE_SQ;
		err = nix_lf_hwctx_disable(rvu, &ctx_req);
		अगर (err)
			dev_err(rvu->dev, "SQ ctx disable failed\n");
	पूर्ण

	अगर (pfvf->rq_ctx) अणु
		ctx_req.ctype = NIX_AQ_CTYPE_RQ;
		err = nix_lf_hwctx_disable(rvu, &ctx_req);
		अगर (err)
			dev_err(rvu->dev, "RQ ctx disable failed\n");
	पूर्ण

	अगर (pfvf->cq_ctx) अणु
		ctx_req.ctype = NIX_AQ_CTYPE_CQ;
		err = nix_lf_hwctx_disable(rvu, &ctx_req);
		अगर (err)
			dev_err(rvu->dev, "CQ ctx disable failed\n");
	पूर्ण

	nix_ctx_मुक्त(rvu, pfvf);
पूर्ण

#घोषणा NIX_AF_LFX_TX_CFG_PTP_EN	BIT_ULL(32)

अटल पूर्णांक rvu_nix_lf_ptp_tx_cfg(काष्ठा rvu *rvu, u16 pcअगरunc, bool enable)
अणु
	काष्ठा rvu_hwinfo *hw = rvu->hw;
	काष्ठा rvu_block *block;
	पूर्णांक blkaddr, pf;
	पूर्णांक nixlf;
	u64 cfg;

	pf = rvu_get_pf(pcअगरunc);
	अगर (!is_mac_feature_supported(rvu, pf, RVU_LMAC_FEAT_PTP))
		वापस 0;

	blkaddr = rvu_get_blkaddr(rvu, BLKTYPE_NIX, pcअगरunc);
	अगर (blkaddr < 0)
		वापस NIX_AF_ERR_AF_LF_INVALID;

	block = &hw->block[blkaddr];
	nixlf = rvu_get_lf(rvu, block, pcअगरunc, 0);
	अगर (nixlf < 0)
		वापस NIX_AF_ERR_AF_LF_INVALID;

	cfg = rvu_पढ़ो64(rvu, blkaddr, NIX_AF_LFX_TX_CFG(nixlf));

	अगर (enable)
		cfg |= NIX_AF_LFX_TX_CFG_PTP_EN;
	अन्यथा
		cfg &= ~NIX_AF_LFX_TX_CFG_PTP_EN;

	rvu_ग_लिखो64(rvu, blkaddr, NIX_AF_LFX_TX_CFG(nixlf), cfg);

	वापस 0;
पूर्ण

पूर्णांक rvu_mbox_handler_nix_lf_ptp_tx_enable(काष्ठा rvu *rvu, काष्ठा msg_req *req,
					  काष्ठा msg_rsp *rsp)
अणु
	वापस rvu_nix_lf_ptp_tx_cfg(rvu, req->hdr.pcअगरunc, true);
पूर्ण

पूर्णांक rvu_mbox_handler_nix_lf_ptp_tx_disable(काष्ठा rvu *rvu, काष्ठा msg_req *req,
					   काष्ठा msg_rsp *rsp)
अणु
	वापस rvu_nix_lf_ptp_tx_cfg(rvu, req->hdr.pcअगरunc, false);
पूर्ण

पूर्णांक rvu_mbox_handler_nix_lso_क्रमmat_cfg(काष्ठा rvu *rvu,
					काष्ठा nix_lso_क्रमmat_cfg *req,
					काष्ठा nix_lso_क्रमmat_cfg_rsp *rsp)
अणु
	u16 pcअगरunc = req->hdr.pcअगरunc;
	काष्ठा nix_hw *nix_hw;
	काष्ठा rvu_pfvf *pfvf;
	पूर्णांक blkaddr, idx, f;
	u64 reg;

	pfvf = rvu_get_pfvf(rvu, pcअगरunc);
	blkaddr = rvu_get_blkaddr(rvu, BLKTYPE_NIX, pcअगरunc);
	अगर (!pfvf->nixlf || blkaddr < 0)
		वापस NIX_AF_ERR_AF_LF_INVALID;

	nix_hw = get_nix_hw(rvu->hw, blkaddr);
	अगर (!nix_hw)
		वापस -EINVAL;

	/* Find existing matching LSO क्रमmat, अगर any */
	क्रम (idx = 0; idx < nix_hw->lso.in_use; idx++) अणु
		क्रम (f = 0; f < NIX_LSO_FIELD_MAX; f++) अणु
			reg = rvu_पढ़ो64(rvu, blkaddr,
					 NIX_AF_LSO_FORMATX_FIELDX(idx, f));
			अगर (req->fields[f] != (reg & req->field_mask))
				अवरोध;
		पूर्ण

		अगर (f == NIX_LSO_FIELD_MAX)
			अवरोध;
	पूर्ण

	अगर (idx < nix_hw->lso.in_use) अणु
		/* Match found */
		rsp->lso_क्रमmat_idx = idx;
		वापस 0;
	पूर्ण

	अगर (nix_hw->lso.in_use == nix_hw->lso.total)
		वापस NIX_AF_ERR_LSO_CFG_FAIL;

	rsp->lso_क्रमmat_idx = nix_hw->lso.in_use++;

	क्रम (f = 0; f < NIX_LSO_FIELD_MAX; f++)
		rvu_ग_लिखो64(rvu, blkaddr,
			    NIX_AF_LSO_FORMATX_FIELDX(rsp->lso_क्रमmat_idx, f),
			    req->fields[f]);

	वापस 0;
पूर्ण

व्योम rvu_nix_reset_mac(काष्ठा rvu_pfvf *pfvf, पूर्णांक pcअगरunc)
अणु
	bool from_vf = !!(pcअगरunc & RVU_PFVF_FUNC_MASK);

	/* overग_लिखो vf mac address with शेष_mac */
	अगर (from_vf)
		ether_addr_copy(pfvf->mac_addr, pfvf->शेष_mac);
पूर्ण
