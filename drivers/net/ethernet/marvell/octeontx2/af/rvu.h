<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*  Marvell OcteonTx2 RVU Admin Function driver
 *
 * Copyright (C) 2018 Marvell International Ltd.
 *
 * This program is मुक्त software; you can redistribute it and/or modअगरy
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 */

#अगर_अघोषित RVU_H
#घोषणा RVU_H

#समावेश <linux/pci.h>
#समावेश <net/devlink.h>

#समावेश "rvu_struct.h"
#समावेश "rvu_devlink.h"
#समावेश "common.h"
#समावेश "mbox.h"
#समावेश "npc.h"
#समावेश "rvu_reg.h"

/* PCI device IDs */
#घोषणा	PCI_DEVID_OCTEONTX2_RVU_AF		0xA065
#घोषणा	PCI_DEVID_OCTEONTX2_LBK			0xA061

/* Subप्रणाली Device ID */
#घोषणा PCI_SUBSYS_DEVID_96XX                  0xB200
#घोषणा PCI_SUBSYS_DEVID_CN10K_A	       0xB900

/* PCI BAR nos */
#घोषणा	PCI_AF_REG_BAR_NUM			0
#घोषणा	PCI_PF_REG_BAR_NUM			2
#घोषणा	PCI_MBOX_BAR_NUM			4

#घोषणा NAME_SIZE				32
#घोषणा MAX_NIX_BLKS				2
#घोषणा MAX_CPT_BLKS				2

/* PF_FUNC */
#घोषणा RVU_PFVF_PF_SHIFT	10
#घोषणा RVU_PFVF_PF_MASK	0x3F
#घोषणा RVU_PFVF_FUNC_SHIFT	0
#घोषणा RVU_PFVF_FUNC_MASK	0x3FF

#अगर_घोषित CONFIG_DEBUG_FS
काष्ठा dump_ctx अणु
	पूर्णांक	lf;
	पूर्णांक	id;
	bool	all;
पूर्ण;

काष्ठा cpt_ctx अणु
	पूर्णांक blkaddr;
	काष्ठा rvu *rvu;
पूर्ण;

काष्ठा rvu_debugfs अणु
	काष्ठा dentry *root;
	काष्ठा dentry *cgx_root;
	काष्ठा dentry *cgx;
	काष्ठा dentry *lmac;
	काष्ठा dentry *npa;
	काष्ठा dentry *nix;
	काष्ठा dentry *npc;
	काष्ठा dentry *cpt;
	काष्ठा dump_ctx npa_aura_ctx;
	काष्ठा dump_ctx npa_pool_ctx;
	काष्ठा dump_ctx nix_cq_ctx;
	काष्ठा dump_ctx nix_rq_ctx;
	काष्ठा dump_ctx nix_sq_ctx;
	काष्ठा cpt_ctx cpt_ctx[MAX_CPT_BLKS];
	पूर्णांक npa_qsize_id;
	पूर्णांक nix_qsize_id;
पूर्ण;
#पूर्ण_अगर

काष्ठा rvu_work अणु
	काष्ठा	work_काष्ठा work;
	काष्ठा	rvu *rvu;
	पूर्णांक num_msgs;
	पूर्णांक up_num_msgs;
पूर्ण;

काष्ठा rsrc_bmap अणु
	अचिन्हित दीर्घ *bmap;	/* Poपूर्णांकer to resource biपंचांगap */
	u16  max;		/* Max resource id or count */
पूर्ण;

काष्ठा rvu_block अणु
	काष्ठा rsrc_bmap	lf;
	काष्ठा admin_queue	*aq; /* NIX/NPA AQ */
	u16  *fn_map; /* LF to pcअगरunc mapping */
	bool multislot;
	bool implemented;
	u8   addr;  /* RVU_BLOCK_ADDR_E */
	u8   type;  /* RVU_BLOCK_TYPE_E */
	u8   lfshअगरt;
	u64  lookup_reg;
	u64  pf_lfcnt_reg;
	u64  vf_lfcnt_reg;
	u64  lfcfg_reg;
	u64  msixcfg_reg;
	u64  lfreset_reg;
	अचिन्हित अक्षर name[NAME_SIZE];
पूर्ण;

काष्ठा nix_mcast अणु
	काष्ठा qmem	*mce_ctx;
	काष्ठा qmem	*mcast_buf;
	पूर्णांक		replay_pkind;
	पूर्णांक		next_मुक्त_mce;
	काष्ठा mutex	mce_lock; /* Serialize MCE updates */
पूर्ण;

काष्ठा nix_mce_list अणु
	काष्ठा hlist_head	head;
	पूर्णांक			count;
	पूर्णांक			max;
पूर्ण;

/* layer metadata to uniquely identअगरy a packet header field */
काष्ठा npc_layer_mdata अणु
	u8 lid;
	u8 ltype;
	u8 hdr;
	u8 key;
	u8 len;
पूर्ण;

/* Structure to represent a field present in the
 * generated key. A key field may present anywhere and can
 * be of any size in the generated key. Once this काष्ठाure
 * is populated क्रम fields of पूर्णांकerest then field's presence
 * and location (अगर present) can be known.
 */
काष्ठा npc_key_field अणु
	/* Masks where all set bits indicate position
	 * of a field in the key
	 */
	u64 kw_mask[NPC_MAX_KWS_IN_KEY];
	/* Number of words in the key a field spans. If a field is
	 * of 16 bytes and key offset is 4 then the field will use
	 * 4 bytes in KW0, 8 bytes in KW1 and 4 bytes in KW2 and
	 * nr_kws will be 3(KW0, KW1 and KW2).
	 */
	पूर्णांक nr_kws;
	/* used by packet header fields */
	काष्ठा npc_layer_mdata layer_mdata;
पूर्ण;

काष्ठा npc_mcam अणु
	काष्ठा rsrc_bmap counters;
	काष्ठा mutex	lock;	/* MCAM entries and counters update lock */
	अचिन्हित दीर्घ	*bmap;		/* biपंचांगap, 0 => bmap_entries */
	अचिन्हित दीर्घ	*bmap_reverse;	/* Reverse biपंचांगap, bmap_entries => 0 */
	u16	bmap_entries;	/* Number of unreserved MCAM entries */
	u16	bmap_fcnt;	/* MCAM entries मुक्त count */
	u16	*entry2pfvf_map;
	u16	*entry2cntr_map;
	u16	*cntr2pfvf_map;
	u16	*cntr_refcnt;
	u16	*entry2target_pffunc;
	u8	keysize;	/* MCAM keysize 112/224/448 bits */
	u8	banks;		/* Number of MCAM banks */
	u8	banks_per_entry;/* Number of keywords in key */
	u16	banksize;	/* Number of MCAM entries in each bank */
	u16	total_entries;	/* Total number of MCAM entries */
	u16	nixlf_offset;	/* Offset of nixlf rsvd uncast entries */
	u16	pf_offset;	/* Offset of PF's rsvd bcast, promisc entries */
	u16	lprio_count;
	u16	lprio_start;
	u16	hprio_count;
	u16	hprio_end;
	u16     rx_miss_act_cntr; /* Counter क्रम RX MISS action */
	/* fields present in the generated key */
	काष्ठा npc_key_field	tx_key_fields[NPC_KEY_FIELDS_MAX];
	काष्ठा npc_key_field	rx_key_fields[NPC_KEY_FIELDS_MAX];
	u64	tx_features;
	u64	rx_features;
	काष्ठा list_head mcam_rules;
पूर्ण;

/* Structure क्रम per RVU func info ie PF/VF */
काष्ठा rvu_pfvf अणु
	bool		npalf; /* Only one NPALF per RVU_FUNC */
	bool		nixlf; /* Only one NIXLF per RVU_FUNC */
	u16		sso;
	u16		ssow;
	u16		cptlfs;
	u16		timlfs;
	u16		cpt1_lfs;
	u8		cgx_lmac;

	/* Block LF's MSIX vector info */
	काष्ठा rsrc_bmap msix;      /* Biपंचांगap क्रम MSIX vector alloc */
#घोषणा MSIX_BLKLF(blkaddr, lf) (((blkaddr) << 8) | ((lf) & 0xFF))
	u16		 *msix_lfmap; /* Vector to block LF mapping */

	/* NPA contexts */
	काष्ठा qmem	*aura_ctx;
	काष्ठा qmem	*pool_ctx;
	काष्ठा qmem	*npa_qपूर्णांकs_ctx;
	अचिन्हित दीर्घ	*aura_bmap;
	अचिन्हित दीर्घ	*pool_bmap;

	/* NIX contexts */
	काष्ठा qmem	*rq_ctx;
	काष्ठा qmem	*sq_ctx;
	काष्ठा qmem	*cq_ctx;
	काष्ठा qmem	*rss_ctx;
	काष्ठा qmem	*cq_पूर्णांकs_ctx;
	काष्ठा qmem	*nix_qपूर्णांकs_ctx;
	अचिन्हित दीर्घ	*sq_bmap;
	अचिन्हित दीर्घ	*rq_bmap;
	अचिन्हित दीर्घ	*cq_bmap;

	u16		rx_chan_base;
	u16		tx_chan_base;
	u8              rx_chan_cnt; /* total number of RX channels */
	u8              tx_chan_cnt; /* total number of TX channels */
	u16		maxlen;
	u16		minlen;

	u8		pf_set_vf_cfg;
	u8		mac_addr[ETH_ALEN]; /* MAC address of this PF/VF */
	u8		शेष_mac[ETH_ALEN]; /* MAC address from FWdata */

	/* Broadcast pkt replication info */
	u16			bcast_mce_idx;
	काष्ठा nix_mce_list	bcast_mce_list;

	काष्ठा rvu_npc_mcam_rule *def_ucast_rule;

	bool	cgx_in_use; /* this PF/VF using CGX? */
	पूर्णांक	cgx_users;  /* number of cgx users - used only by PFs */

	u8	nix_blkaddr; /* BLKADDR_NIX0/1 asचिन्हित to this PF */
	u8	nix_rx_पूर्णांकf; /* NIX0_RX/NIX1_RX पूर्णांकerface to NPC */
	u8	nix_tx_पूर्णांकf; /* NIX0_TX/NIX1_TX पूर्णांकerface to NPC */
पूर्ण;

काष्ठा nix_txsch अणु
	काष्ठा rsrc_bmap schq;
	u8   lvl;
#घोषणा NIX_TXSCHQ_FREE		      BIT_ULL(1)
#घोषणा NIX_TXSCHQ_CFG_DONE	      BIT_ULL(0)
#घोषणा TXSCH_MAP_FUNC(__pfvf_map)    ((__pfvf_map) & 0xFFFF)
#घोषणा TXSCH_MAP_FLAGS(__pfvf_map)   ((__pfvf_map) >> 16)
#घोषणा TXSCH_MAP(__func, __flags)    (((__func) & 0xFFFF) | ((__flags) << 16))
#घोषणा TXSCH_SET_FLAG(__pfvf_map, flag)    ((__pfvf_map) | ((flag) << 16))
	u32  *pfvf_map;
पूर्ण;

काष्ठा nix_mark_क्रमmat अणु
	u8 total;
	u8 in_use;
	u32 *cfg;
पूर्ण;

काष्ठा npc_pkind अणु
	काष्ठा rsrc_bmap rsrc;
	u32	*pfchan_map;
पूर्ण;

काष्ठा nix_flowkey अणु
#घोषणा NIX_FLOW_KEY_ALG_MAX 32
	u32 flowkey[NIX_FLOW_KEY_ALG_MAX];
	पूर्णांक in_use;
पूर्ण;

काष्ठा nix_lso अणु
	u8 total;
	u8 in_use;
पूर्ण;

काष्ठा nix_txvlan अणु
#घोषणा NIX_TX_VTAG_DEF_MAX 0x400
	काष्ठा rsrc_bmap rsrc;
	u16 *entry2pfvf_map;
	काष्ठा mutex rsrc_lock; /* Serialize resource alloc/मुक्त */
पूर्ण;

काष्ठा nix_hw अणु
	पूर्णांक blkaddr;
	काष्ठा rvu *rvu;
	काष्ठा nix_txsch txsch[NIX_TXSCH_LVL_CNT]; /* Tx schedulers */
	काष्ठा nix_mcast mcast;
	काष्ठा nix_flowkey flowkey;
	काष्ठा nix_mark_क्रमmat mark_क्रमmat;
	काष्ठा nix_lso lso;
	काष्ठा nix_txvlan txvlan;
पूर्ण;

/* RVU block's capabilities or functionality,
 * which vary by silicon version/skew.
 */
काष्ठा hw_cap अणु
	/* Transmit side supported functionality */
	u8	nix_tx_aggr_lvl; /* Tx link's traffic aggregation level */
	u16	nix_txsch_per_cgx_lmac; /* Max Q's transmitting to CGX LMAC */
	u16	nix_txsch_per_lbk_lmac; /* Max Q's transmitting to LBK LMAC */
	u16	nix_txsch_per_sdp_lmac; /* Max Q's transmitting to SDP LMAC */
	bool	nix_fixed_txschq_mapping; /* Schq mapping fixed or flexible */
	bool	nix_shaping;		 /* Is shaping and coloring supported */
	bool	nix_tx_link_bp;		 /* Can link backpressure TL queues ? */
	bool	nix_rx_multicast;	 /* Rx packet replication support */
	bool	per_pf_mbox_regs; /* PF mbox specअगरied in per PF रेजिस्टरs ? */
	bool	programmable_chans; /* Channels programmable ? */
पूर्ण;

काष्ठा rvu_hwinfo अणु
	u8	total_pfs;   /* MAX RVU PFs HW supports */
	u16	total_vfs;   /* Max RVU VFs HW supports */
	u16	max_vfs_per_pf; /* Max VFs that can be attached to a PF */
	u8	cgx;
	u8	lmac_per_cgx;
	u16	cgx_chan_base;	/* CGX base channel number */
	u16	lbk_chan_base;	/* LBK base channel number */
	u16	sdp_chan_base;	/* SDP base channel number */
	u16	cpt_chan_base;	/* CPT base channel number */
	u8	cgx_links;
	u8	lbk_links;
	u8	sdp_links;
	u8	cpt_links;	/* Number of CPT links */
	u8	npc_kpus;          /* No of parser units */
	u8	npc_pkinds;        /* No of port kinds */
	u8	npc_पूर्णांकfs;         /* No of पूर्णांकerfaces */
	u8	npc_kpu_entries;   /* No of KPU entries */
	u16	npc_counters;	   /* No of match stats counters */
	u32	lbk_bufsize;	   /* FIFO size supported by LBK */
	bool	npc_ext_set;	   /* Extended रेजिस्टर set */

	काष्ठा hw_cap    cap;
	काष्ठा rvu_block block[BLK_COUNT]; /* Block info */
	काष्ठा nix_hw    *nix;
	काष्ठा rvu	 *rvu;
	काष्ठा npc_pkind pkind;
	काष्ठा npc_mcam  mcam;
पूर्ण;

काष्ठा mbox_wq_info अणु
	काष्ठा otx2_mbox mbox;
	काष्ठा rvu_work *mbox_wrk;

	काष्ठा otx2_mbox mbox_up;
	काष्ठा rvu_work *mbox_wrk_up;

	काष्ठा workqueue_काष्ठा *mbox_wq;
पूर्ण;

काष्ठा rvu_fwdata अणु
#घोषणा RVU_FWDATA_HEADER_MAGIC	0xCFDA	/* Custom Firmware Data*/
#घोषणा RVU_FWDATA_VERSION	0x0001
	u32 header_magic;
	u32 version;		/* version id */

	/* MAC address */
#घोषणा PF_MACNUM_MAX	32
#घोषणा VF_MACNUM_MAX	256
	u64 pf_macs[PF_MACNUM_MAX];
	u64 vf_macs[VF_MACNUM_MAX];
	u64 sclk;
	u64 rclk;
	u64 mcam_addr;
	u64 mcam_sz;
	u64 msixtr_base;
#घोषणा FWDATA_RESERVED_MEM 1023
	u64 reserved[FWDATA_RESERVED_MEM];
#घोषणा CGX_MAX         5
#घोषणा CGX_LMACS_MAX   4
	काष्ठा cgx_lmac_fwdata_s cgx_fw_data[CGX_MAX][CGX_LMACS_MAX];
	/* Do not add new fields below this line */
पूर्ण;

काष्ठा ptp;

/* KPU profile adapter काष्ठाure gathering all KPU configuration data and असलtracting out the
 * source where it came from.
 */
काष्ठा npc_kpu_profile_adapter अणु
	स्थिर अक्षर			*name;
	u64				version;
	स्थिर काष्ठा npc_lt_def_cfg	*lt_def;
	स्थिर काष्ठा npc_kpu_profile_action	*ikpu; /* array[pkinds] */
	स्थिर काष्ठा npc_kpu_profile	*kpu; /* array[kpus] */
	काष्ठा npc_mcam_kex		*mkex;
	माप_प्रकार				pkinds;
	माप_प्रकार				kpus;
पूर्ण;

काष्ठा rvu अणु
	व्योम __iomem		*afreg_base;
	व्योम __iomem		*pfreg_base;
	काष्ठा pci_dev		*pdev;
	काष्ठा device		*dev;
	काष्ठा rvu_hwinfo       *hw;
	काष्ठा rvu_pfvf		*pf;
	काष्ठा rvu_pfvf		*hwvf;
	काष्ठा mutex		rsrc_lock; /* Serialize resource alloc/मुक्त */
	पूर्णांक			vfs; /* Number of VFs attached to RVU */
	पूर्णांक			nix_blkaddr[MAX_NIX_BLKS];

	/* Mbox */
	काष्ठा mbox_wq_info	afpf_wq_info;
	काष्ठा mbox_wq_info	afvf_wq_info;

	/* PF FLR */
	काष्ठा rvu_work		*flr_wrk;
	काष्ठा workqueue_काष्ठा *flr_wq;
	काष्ठा mutex		flr_lock; /* Serialize FLRs */

	/* MSI-X */
	u16			num_vec;
	अक्षर			*irq_name;
	bool			*irq_allocated;
	dma_addr_t		msix_base_iova;
	u64			msixtr_base_phy; /* Register reset value */

	/* CGX */
#घोषणा PF_CGXMAP_BASE		1 /* PF 0 is reserved क्रम RVU PF */
	u8			cgx_mapped_pfs;
	u8			cgx_cnt_max;	 /* CGX port count max */
	u8			*pf2cgxlmac_map; /* pf to cgx_lmac map */
	u16			*cgxlmac2pf_map; /* biपंचांगap of mapped pfs क्रम
						  * every cgx lmac port
						  */
	अचिन्हित दीर्घ		pf_notअगरy_bmap; /* Flags क्रम PF notअगरication */
	व्योम			**cgx_idmap; /* cgx id to cgx data map table */
	काष्ठा			work_काष्ठा cgx_evh_work;
	काष्ठा			workqueue_काष्ठा *cgx_evh_wq;
	spinlock_t		cgx_evq_lock; /* cgx event queue lock */
	काष्ठा list_head	cgx_evq_head; /* cgx event queue head */
	काष्ठा mutex		cgx_cfg_lock; /* serialize cgx configuration */

	अक्षर mkex_pfl_name[MKEX_NAME_LEN]; /* Configured MKEX profile name */

	/* Firmware data */
	काष्ठा rvu_fwdata	*fwdata;

	/* NPC KPU data */
	काष्ठा npc_kpu_profile_adapter kpu;

	काष्ठा ptp		*ptp;

#अगर_घोषित CONFIG_DEBUG_FS
	काष्ठा rvu_debugfs	rvu_dbg;
#पूर्ण_अगर
	काष्ठा rvu_devlink	*rvu_dl;
पूर्ण;

अटल अंतरभूत व्योम rvu_ग_लिखो64(काष्ठा rvu *rvu, u64 block, u64 offset, u64 val)
अणु
	ग_लिखोq(val, rvu->afreg_base + ((block << 28) | offset));
पूर्ण

अटल अंतरभूत u64 rvu_पढ़ो64(काष्ठा rvu *rvu, u64 block, u64 offset)
अणु
	वापस पढ़ोq(rvu->afreg_base + ((block << 28) | offset));
पूर्ण

अटल अंतरभूत व्योम rvupf_ग_लिखो64(काष्ठा rvu *rvu, u64 offset, u64 val)
अणु
	ग_लिखोq(val, rvu->pfreg_base + offset);
पूर्ण

अटल अंतरभूत u64 rvupf_पढ़ो64(काष्ठा rvu *rvu, u64 offset)
अणु
	वापस पढ़ोq(rvu->pfreg_base + offset);
पूर्ण

/* Silicon revisions */
अटल अंतरभूत bool is_rvu_96xx_A0(काष्ठा rvu *rvu)
अणु
	काष्ठा pci_dev *pdev = rvu->pdev;

	वापस (pdev->revision == 0x00) &&
		(pdev->subप्रणाली_device == PCI_SUBSYS_DEVID_96XX);
पूर्ण

अटल अंतरभूत bool is_rvu_96xx_B0(काष्ठा rvu *rvu)
अणु
	काष्ठा pci_dev *pdev = rvu->pdev;

	वापस ((pdev->revision == 0x00) || (pdev->revision == 0x01)) &&
		(pdev->subप्रणाली_device == PCI_SUBSYS_DEVID_96XX);
पूर्ण

/* REVID क्रम PCIe devices.
 * Bits 0..1: minor pass, bit 3..2: major pass
 * bits 7..4: midr id
 */
#घोषणा PCI_REVISION_ID_96XX		0x00
#घोषणा PCI_REVISION_ID_95XX		0x10
#घोषणा PCI_REVISION_ID_LOKI		0x20
#घोषणा PCI_REVISION_ID_98XX		0x30
#घोषणा PCI_REVISION_ID_95XXMM		0x40

अटल अंतरभूत bool is_rvu_otx2(काष्ठा rvu *rvu)
अणु
	काष्ठा pci_dev *pdev = rvu->pdev;

	u8 midr = pdev->revision & 0xF0;

	वापस (midr == PCI_REVISION_ID_96XX || midr == PCI_REVISION_ID_95XX ||
		midr == PCI_REVISION_ID_LOKI || midr == PCI_REVISION_ID_98XX ||
		midr == PCI_REVISION_ID_95XXMM);
पूर्ण

अटल अंतरभूत u16 rvu_nix_chan_cgx(काष्ठा rvu *rvu, u8 cgxid,
				   u8 lmacid, u8 chan)
अणु
	u64 nix_स्थिर = rvu_पढ़ो64(rvu, BLKADDR_NIX0, NIX_AF_CONST);
	u16 cgx_chans = nix_स्थिर & 0xFFULL;
	काष्ठा rvu_hwinfo *hw = rvu->hw;

	अगर (!hw->cap.programmable_chans)
		वापस NIX_CHAN_CGX_LMAC_CHX(cgxid, lmacid, chan);

	वापस rvu->hw->cgx_chan_base +
		(cgxid * hw->lmac_per_cgx + lmacid) * cgx_chans + chan;
पूर्ण

अटल अंतरभूत u16 rvu_nix_chan_lbk(काष्ठा rvu *rvu, u8 lbkid,
				   u8 chan)
अणु
	u64 nix_स्थिर = rvu_पढ़ो64(rvu, BLKADDR_NIX0, NIX_AF_CONST);
	u16 lbk_chans = (nix_स्थिर >> 16) & 0xFFULL;
	काष्ठा rvu_hwinfo *hw = rvu->hw;

	अगर (!hw->cap.programmable_chans)
		वापस NIX_CHAN_LBK_CHX(lbkid, chan);

	वापस rvu->hw->lbk_chan_base + lbkid * lbk_chans + chan;
पूर्ण

अटल अंतरभूत u16 rvu_nix_chan_cpt(काष्ठा rvu *rvu, u8 chan)
अणु
	वापस rvu->hw->cpt_chan_base + chan;
पूर्ण

/* Function Prototypes
 * RVU
 */
अटल अंतरभूत पूर्णांक is_afvf(u16 pcअगरunc)
अणु
	वापस !(pcअगरunc & ~RVU_PFVF_FUNC_MASK);
पूर्ण

/* check अगर PF_FUNC is AF */
अटल अंतरभूत bool is_pffunc_af(u16 pcअगरunc)
अणु
	वापस !pcअगरunc;
पूर्ण

अटल अंतरभूत bool is_rvu_fwdata_valid(काष्ठा rvu *rvu)
अणु
	वापस (rvu->fwdata->header_magic == RVU_FWDATA_HEADER_MAGIC) &&
		(rvu->fwdata->version == RVU_FWDATA_VERSION);
पूर्ण

पूर्णांक rvu_alloc_biपंचांगap(काष्ठा rsrc_bmap *rsrc);
पूर्णांक rvu_alloc_rsrc(काष्ठा rsrc_bmap *rsrc);
व्योम rvu_मुक्त_rsrc(काष्ठा rsrc_bmap *rsrc, पूर्णांक id);
पूर्णांक rvu_rsrc_मुक्त_count(काष्ठा rsrc_bmap *rsrc);
पूर्णांक rvu_alloc_rsrc_contig(काष्ठा rsrc_bmap *rsrc, पूर्णांक nrsrc);
bool rvu_rsrc_check_contig(काष्ठा rsrc_bmap *rsrc, पूर्णांक nrsrc);
u16 rvu_get_rsrc_mapcount(काष्ठा rvu_pfvf *pfvf, पूर्णांक blkaddr);
पूर्णांक rvu_get_pf(u16 pcअगरunc);
काष्ठा rvu_pfvf *rvu_get_pfvf(काष्ठा rvu *rvu, पूर्णांक pcअगरunc);
व्योम rvu_get_pf_numvfs(काष्ठा rvu *rvu, पूर्णांक pf, पूर्णांक *numvfs, पूर्णांक *hwvf);
bool is_block_implemented(काष्ठा rvu_hwinfo *hw, पूर्णांक blkaddr);
bool is_pffunc_map_valid(काष्ठा rvu *rvu, u16 pcअगरunc, पूर्णांक blktype);
पूर्णांक rvu_get_lf(काष्ठा rvu *rvu, काष्ठा rvu_block *block, u16 pcअगरunc, u16 slot);
पूर्णांक rvu_lf_reset(काष्ठा rvu *rvu, काष्ठा rvu_block *block, पूर्णांक lf);
पूर्णांक rvu_get_blkaddr(काष्ठा rvu *rvu, पूर्णांक blktype, u16 pcअगरunc);
पूर्णांक rvu_poll_reg(काष्ठा rvu *rvu, u64 block, u64 offset, u64 mask, bool zero);
पूर्णांक rvu_get_num_lbk_chans(व्योम);

/* RVU HW reg validation */
क्रमागत regmap_block अणु
	TXSCHQ_HWREGMAP = 0,
	MAX_HWREGMAP,
पूर्ण;

bool rvu_check_valid_reg(पूर्णांक regmap, पूर्णांक regblk, u64 reg);

/* NPA/NIX AQ APIs */
पूर्णांक rvu_aq_alloc(काष्ठा rvu *rvu, काष्ठा admin_queue **ad_queue,
		 पूर्णांक qsize, पूर्णांक inst_size, पूर्णांक res_size);
व्योम rvu_aq_मुक्त(काष्ठा rvu *rvu, काष्ठा admin_queue *aq);

/* CGX APIs */
अटल अंतरभूत bool is_pf_cgxmapped(काष्ठा rvu *rvu, u8 pf)
अणु
	वापस (pf >= PF_CGXMAP_BASE && pf <= rvu->cgx_mapped_pfs);
पूर्ण

अटल अंतरभूत व्योम rvu_get_cgx_lmac_id(u8 map, u8 *cgx_id, u8 *lmac_id)
अणु
	*cgx_id = (map >> 4) & 0xF;
	*lmac_id = (map & 0xF);
पूर्ण

#घोषणा M(_name, _id, fn_name, req, rsp)				\
पूर्णांक rvu_mbox_handler_ ## fn_name(काष्ठा rvu *, काष्ठा req *, काष्ठा rsp *);
MBOX_MESSAGES
#अघोषित M

पूर्णांक rvu_cgx_init(काष्ठा rvu *rvu);
पूर्णांक rvu_cgx_निकास(काष्ठा rvu *rvu);
व्योम *rvu_cgx_pdata(u8 cgx_id, काष्ठा rvu *rvu);
पूर्णांक rvu_cgx_config_rxtx(काष्ठा rvu *rvu, u16 pcअगरunc, bool start);
व्योम rvu_cgx_enadis_rx_bp(काष्ठा rvu *rvu, पूर्णांक pf, bool enable);
पूर्णांक rvu_cgx_start_stop_io(काष्ठा rvu *rvu, u16 pcअगरunc, bool start);
पूर्णांक rvu_cgx_nix_cuml_stats(काष्ठा rvu *rvu, व्योम *cgxd, पूर्णांक lmac_id, पूर्णांक index,
			   पूर्णांक rxtxflag, u64 *stat);
/* NPA APIs */
पूर्णांक rvu_npa_init(काष्ठा rvu *rvu);
व्योम rvu_npa_मुक्तmem(काष्ठा rvu *rvu);
व्योम rvu_npa_lf_tearकरोwn(काष्ठा rvu *rvu, u16 pcअगरunc, पूर्णांक npalf);
पूर्णांक rvu_npa_aq_enq_inst(काष्ठा rvu *rvu, काष्ठा npa_aq_enq_req *req,
			काष्ठा npa_aq_enq_rsp *rsp);

/* NIX APIs */
bool is_nixlf_attached(काष्ठा rvu *rvu, u16 pcअगरunc);
पूर्णांक rvu_nix_init(काष्ठा rvu *rvu);
पूर्णांक rvu_nix_reserve_mark_क्रमmat(काष्ठा rvu *rvu, काष्ठा nix_hw *nix_hw,
				पूर्णांक blkaddr, u32 cfg);
व्योम rvu_nix_मुक्तmem(काष्ठा rvu *rvu);
पूर्णांक rvu_get_nixlf_count(काष्ठा rvu *rvu);
व्योम rvu_nix_lf_tearकरोwn(काष्ठा rvu *rvu, u16 pcअगरunc, पूर्णांक blkaddr, पूर्णांक npalf);
पूर्णांक nix_get_nixlf(काष्ठा rvu *rvu, u16 pcअगरunc, पूर्णांक *nixlf, पूर्णांक *nix_blkaddr);
पूर्णांक nix_update_bcast_mce_list(काष्ठा rvu *rvu, u16 pcअगरunc, bool add);
काष्ठा nix_hw *get_nix_hw(काष्ठा rvu_hwinfo *hw, पूर्णांक blkaddr);
पूर्णांक rvu_get_next_nix_blkaddr(काष्ठा rvu *rvu, पूर्णांक blkaddr);
व्योम rvu_nix_reset_mac(काष्ठा rvu_pfvf *pfvf, पूर्णांक pcअगरunc);

/* NPC APIs */
पूर्णांक rvu_npc_init(काष्ठा rvu *rvu);
व्योम rvu_npc_मुक्तmem(काष्ठा rvu *rvu);
पूर्णांक rvu_npc_get_pkind(काष्ठा rvu *rvu, u16 pf);
व्योम rvu_npc_set_pkind(काष्ठा rvu *rvu, पूर्णांक pkind, काष्ठा rvu_pfvf *pfvf);
पूर्णांक npc_config_ts_kpuaction(काष्ठा rvu *rvu, पूर्णांक pf, u16 pcअगरunc, bool en);
व्योम rvu_npc_install_ucast_entry(काष्ठा rvu *rvu, u16 pcअगरunc,
				 पूर्णांक nixlf, u64 chan, u8 *mac_addr);
व्योम rvu_npc_install_promisc_entry(काष्ठा rvu *rvu, u16 pcअगरunc,
				   पूर्णांक nixlf, u64 chan, u8 chan_cnt,
				   bool allmulti);
व्योम rvu_npc_disable_promisc_entry(काष्ठा rvu *rvu, u16 pcअगरunc, पूर्णांक nixlf);
व्योम rvu_npc_enable_promisc_entry(काष्ठा rvu *rvu, u16 pcअगरunc, पूर्णांक nixlf);
व्योम rvu_npc_install_bcast_match_entry(काष्ठा rvu *rvu, u16 pcअगरunc,
				       पूर्णांक nixlf, u64 chan);
व्योम rvu_npc_enable_bcast_entry(काष्ठा rvu *rvu, u16 pcअगरunc, bool enable);
व्योम rvu_npc_disable_mcam_entries(काष्ठा rvu *rvu, u16 pcअगरunc, पूर्णांक nixlf);
व्योम rvu_npc_मुक्त_mcam_entries(काष्ठा rvu *rvu, u16 pcअगरunc, पूर्णांक nixlf);
व्योम rvu_npc_disable_शेष_entries(काष्ठा rvu *rvu, u16 pcअगरunc, पूर्णांक nixlf);
व्योम rvu_npc_enable_शेष_entries(काष्ठा rvu *rvu, u16 pcअगरunc, पूर्णांक nixlf);
व्योम rvu_npc_update_flowkey_alg_idx(काष्ठा rvu *rvu, u16 pcअगरunc, पूर्णांक nixlf,
				    पूर्णांक group, पूर्णांक alg_idx, पूर्णांक mcam_index);
व्योम rvu_npc_get_mcam_entry_alloc_info(काष्ठा rvu *rvu, u16 pcअगरunc,
				       पूर्णांक blkaddr, पूर्णांक *alloc_cnt,
				       पूर्णांक *enable_cnt);
व्योम rvu_npc_get_mcam_counter_alloc_info(काष्ठा rvu *rvu, u16 pcअगरunc,
					 पूर्णांक blkaddr, पूर्णांक *alloc_cnt,
					 पूर्णांक *enable_cnt);
bool is_npc_पूर्णांकf_tx(u8 पूर्णांकf);
bool is_npc_पूर्णांकf_rx(u8 पूर्णांकf);
bool is_npc_पूर्णांकerface_valid(काष्ठा rvu *rvu, u8 पूर्णांकf);
पूर्णांक rvu_npc_get_tx_nibble_cfg(काष्ठा rvu *rvu, u64 nibble_ena);
पूर्णांक npc_mcam_verअगरy_channel(काष्ठा rvu *rvu, u16 pcअगरunc, u8 पूर्णांकf, u16 channel);
पूर्णांक npc_flow_steering_init(काष्ठा rvu *rvu, पूर्णांक blkaddr);
स्थिर अक्षर *npc_get_field_name(u8 hdr);
पूर्णांक npc_get_bank(काष्ठा npc_mcam *mcam, पूर्णांक index);
व्योम npc_mcam_enable_flows(काष्ठा rvu *rvu, u16 target);
व्योम npc_mcam_disable_flows(काष्ठा rvu *rvu, u16 target);
व्योम npc_enable_mcam_entry(काष्ठा rvu *rvu, काष्ठा npc_mcam *mcam,
			   पूर्णांक blkaddr, पूर्णांक index, bool enable);
व्योम npc_पढ़ो_mcam_entry(काष्ठा rvu *rvu, काष्ठा npc_mcam *mcam,
			 पूर्णांक blkaddr, u16 src, काष्ठा mcam_entry *entry,
			 u8 *पूर्णांकf, u8 *ena);
bool is_mac_feature_supported(काष्ठा rvu *rvu, पूर्णांक pf, पूर्णांक feature);
u32  rvu_cgx_get_fअगरolen(काष्ठा rvu *rvu);
व्योम *rvu_first_cgx_pdata(काष्ठा rvu *rvu);

पूर्णांक npc_get_nixlf_mcam_index(काष्ठा npc_mcam *mcam, u16 pcअगरunc, पूर्णांक nixlf,
			     पूर्णांक type);
bool is_mcam_entry_enabled(काष्ठा rvu *rvu, काष्ठा npc_mcam *mcam, पूर्णांक blkaddr,
			   पूर्णांक index);

/* CPT APIs */
पूर्णांक rvu_cpt_lf_tearकरोwn(काष्ठा rvu *rvu, u16 pcअगरunc, पूर्णांक lf, पूर्णांक slot);

/* CN10K RVU */
पूर्णांक rvu_set_channels_base(काष्ठा rvu *rvu);
व्योम rvu_program_channels(काष्ठा rvu *rvu);

#अगर_घोषित CONFIG_DEBUG_FS
व्योम rvu_dbg_init(काष्ठा rvu *rvu);
व्योम rvu_dbg_निकास(काष्ठा rvu *rvu);
#अन्यथा
अटल अंतरभूत व्योम rvu_dbg_init(काष्ठा rvu *rvu) अणुपूर्ण
अटल अंतरभूत व्योम rvu_dbg_निकास(काष्ठा rvu *rvu) अणुपूर्ण
#पूर्ण_अगर
#पूर्ण_अगर /* RVU_H */
