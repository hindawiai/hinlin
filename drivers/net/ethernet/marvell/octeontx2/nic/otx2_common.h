<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/* Marvell OcteonTx2 RVU Ethernet driver
 *
 * Copyright (C) 2020 Marvell International Ltd.
 *
 * This program is मुक्त software; you can redistribute it and/or modअगरy
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 */

#अगर_अघोषित OTX2_COMMON_H
#घोषणा OTX2_COMMON_H

#समावेश <linux/ethtool.h>
#समावेश <linux/pci.h>
#समावेश <linux/iommu.h>
#समावेश <linux/net_tstamp.h>
#समावेश <linux/ptp_घड़ी_kernel.h>
#समावेश <linux/समयcounter.h>
#समावेश <linux/soc/marvell/octeontx2/यंत्र.h>
#समावेश <net/pkt_cls.h>

#समावेश <mbox.h>
#समावेश <npc.h>
#समावेश "otx2_reg.h"
#समावेश "otx2_txrx.h"
#समावेश <rvu_trace.h>

/* PCI device IDs */
#घोषणा PCI_DEVID_OCTEONTX2_RVU_PF              0xA063
#घोषणा PCI_DEVID_OCTEONTX2_RVU_VF		0xA064
#घोषणा PCI_DEVID_OCTEONTX2_RVU_AFVF		0xA0F8

#घोषणा PCI_SUBSYS_DEVID_96XX_RVU_PFVF		0xB200

/* PCI BAR nos */
#घोषणा PCI_CFG_REG_BAR_NUM                     2
#घोषणा PCI_MBOX_BAR_NUM                        4

#घोषणा NAME_SIZE                               32

क्रमागत arua_mapped_qtypes अणु
	AURA_NIX_RQ,
	AURA_NIX_SQ,
पूर्ण;

/* NIX LF पूर्णांकerrupts range*/
#घोषणा NIX_LF_QINT_VEC_START			0x00
#घोषणा NIX_LF_CINT_VEC_START			0x40
#घोषणा NIX_LF_GINT_VEC				0x80
#घोषणा NIX_LF_ERR_VEC				0x81
#घोषणा NIX_LF_POISON_VEC			0x82

/* Send skid of 2000 packets required क्रम CQ size of 4K CQEs. */
#घोषणा SEND_CQ_SKID	2000

/* RSS configuration */
काष्ठा otx2_rss_ctx अणु
	u8  ind_tbl[MAX_RSS_INसूची_TBL_SIZE];
पूर्ण;

काष्ठा otx2_rss_info अणु
	u8 enable;
	u32 flowkey_cfg;
	u16 rss_size;
#घोषणा RSS_HASH_KEY_SIZE	44   /* 352 bit key */
	u8  key[RSS_HASH_KEY_SIZE];
	काष्ठा otx2_rss_ctx	*rss_ctx[MAX_RSS_GROUPS];
पूर्ण;

/* NIX (or NPC) RX errors */
क्रमागत otx2_errlvl अणु
	NPC_ERRLVL_RE,
	NPC_ERRLVL_LID_LA,
	NPC_ERRLVL_LID_LB,
	NPC_ERRLVL_LID_LC,
	NPC_ERRLVL_LID_LD,
	NPC_ERRLVL_LID_LE,
	NPC_ERRLVL_LID_LF,
	NPC_ERRLVL_LID_LG,
	NPC_ERRLVL_LID_LH,
	NPC_ERRLVL_NIX = 0x0F,
पूर्ण;

क्रमागत otx2_errcodes_re अणु
	/* NPC_ERRLVL_RE errcodes */
	ERRCODE_FCS = 0x7,
	ERRCODE_FCS_RCV = 0x8,
	ERRCODE_UNDERSIZE = 0x10,
	ERRCODE_OVERSIZE = 0x11,
	ERRCODE_OL2_LEN_MISMATCH = 0x12,
	/* NPC_ERRLVL_NIX errcodes */
	ERRCODE_OL3_LEN = 0x10,
	ERRCODE_OL4_LEN = 0x11,
	ERRCODE_OL4_CSUM = 0x12,
	ERRCODE_IL3_LEN = 0x20,
	ERRCODE_IL4_LEN = 0x21,
	ERRCODE_IL4_CSUM = 0x22,
पूर्ण;

/* NIX TX stats */
क्रमागत nix_stat_lf_tx अणु
	TX_UCAST	= 0x0,
	TX_BCAST	= 0x1,
	TX_MCAST	= 0x2,
	TX_DROP		= 0x3,
	TX_OCTS		= 0x4,
	TX_STATS_ENUM_LAST,
पूर्ण;

/* NIX RX stats */
क्रमागत nix_stat_lf_rx अणु
	RX_OCTS		= 0x0,
	RX_UCAST	= 0x1,
	RX_BCAST	= 0x2,
	RX_MCAST	= 0x3,
	RX_DROP		= 0x4,
	RX_DROP_OCTS	= 0x5,
	RX_FCS		= 0x6,
	RX_ERR		= 0x7,
	RX_DRP_BCAST	= 0x8,
	RX_DRP_MCAST	= 0x9,
	RX_DRP_L3BCAST	= 0xa,
	RX_DRP_L3MCAST	= 0xb,
	RX_STATS_ENUM_LAST,
पूर्ण;

काष्ठा otx2_dev_stats अणु
	u64 rx_bytes;
	u64 rx_frames;
	u64 rx_ucast_frames;
	u64 rx_bcast_frames;
	u64 rx_mcast_frames;
	u64 rx_drops;

	u64 tx_bytes;
	u64 tx_frames;
	u64 tx_ucast_frames;
	u64 tx_bcast_frames;
	u64 tx_mcast_frames;
	u64 tx_drops;
पूर्ण;

/* Driver counted stats */
काष्ठा otx2_drv_stats अणु
	atomic_t rx_fcs_errs;
	atomic_t rx_oversize_errs;
	atomic_t rx_undersize_errs;
	atomic_t rx_csum_errs;
	atomic_t rx_len_errs;
	atomic_t rx_other_errs;
पूर्ण;

काष्ठा mbox अणु
	काष्ठा otx2_mbox	mbox;
	काष्ठा work_काष्ठा	mbox_wrk;
	काष्ठा otx2_mbox	mbox_up;
	काष्ठा work_काष्ठा	mbox_up_wrk;
	काष्ठा otx2_nic		*pfvf;
	व्योम			*bbuf_base; /* Bounce buffer क्रम mbox memory */
	काष्ठा mutex		lock;	/* serialize mailbox access */
	पूर्णांक			num_msgs; /* mbox number of messages */
	पूर्णांक			up_num_msgs; /* mbox_up number of messages */
पूर्ण;

काष्ठा otx2_hw अणु
	काष्ठा pci_dev		*pdev;
	काष्ठा otx2_rss_info	rss_info;
	u16                     rx_queues;
	u16                     tx_queues;
	u16			max_queues;
	u16			pool_cnt;
	u16			rqpool_cnt;
	u16			sqpool_cnt;

	/* NPA */
	u32			stack_pg_ptrs;  /* No of ptrs per stack page */
	u32			stack_pg_bytes; /* Size of stack page */
	u16			sqb_size;

	/* NIX */
	u16		txschq_list[NIX_TXSCH_LVL_CNT][MAX_TXSCHQ_PER_FUNC];

	/* HW settings, coalescing etc */
	u16			rx_chan_base;
	u16			tx_chan_base;
	u16			cq_qcount_रुको;
	u16			cq_ecount_रुको;
	u16			rq_skid;
	u8			cq_समय_रुको;

	/* Segmentation */
	u8			lso_tsov4_idx;
	u8			lso_tsov6_idx;
	u8			lso_udpv4_idx;
	u8			lso_udpv6_idx;

	/* MSI-X */
	u8			cपूर्णांक_cnt; /* CQ पूर्णांकerrupt count */
	u16			npa_msixoff; /* Offset of NPA vectors */
	u16			nix_msixoff; /* Offset of NIX vectors */
	अक्षर			*irq_name;
	cpumask_var_t           *affinity_mask;

	/* Stats */
	काष्ठा otx2_dev_stats	dev_stats;
	काष्ठा otx2_drv_stats	drv_stats;
	u64			cgx_rx_stats[CGX_RX_STATS_COUNT];
	u64			cgx_tx_stats[CGX_TX_STATS_COUNT];
	u64			cgx_fec_corr_blks;
	u64			cgx_fec_uncorr_blks;
	u8			cgx_links;  /* No. of CGX links present in HW */
	u8			lbk_links;  /* No. of LBK links present in HW */
#घोषणा HW_TSO			0
#घोषणा CN10K_MBOX		1
#घोषणा CN10K_LMTST		2
	अचिन्हित दीर्घ		cap_flag;

#घोषणा LMT_LINE_SIZE		128
#घोषणा NIX_LMTID_BASE		72 /* RX + TX + XDP */
	व्योम __iomem		*lmt_base;
	u64			*npa_lmt_base;
	u64			*nix_lmt_base;
पूर्ण;

काष्ठा otx2_vf_config अणु
	काष्ठा otx2_nic *pf;
	काष्ठा delayed_work link_event_work;
	bool पूर्णांकf_करोwn; /* पूर्णांकerface was either configured or not */
	u8 mac[ETH_ALEN];
	u16 vlan;
	पूर्णांक tx_vtag_idx;
पूर्ण;

काष्ठा flr_work अणु
	काष्ठा work_काष्ठा work;
	काष्ठा otx2_nic *pf;
पूर्ण;

काष्ठा refill_work अणु
	काष्ठा delayed_work pool_refill_work;
	काष्ठा otx2_nic *pf;
पूर्ण;

काष्ठा otx2_ptp अणु
	काष्ठा ptp_घड़ी_info ptp_info;
	काष्ठा ptp_घड़ी *ptp_घड़ी;
	काष्ठा otx2_nic *nic;

	काष्ठा cyclecounter cycle_counter;
	काष्ठा समयcounter समय_counter;
पूर्ण;

#घोषणा OTX2_HW_TIMESTAMP_LEN	8

काष्ठा otx2_mac_table अणु
	u8 addr[ETH_ALEN];
	u16 mcam_entry;
	bool inuse;
पूर्ण;

काष्ठा otx2_flow_config अणु
	u16			entry[NPC_MAX_NONCONTIG_ENTRIES];
	u32			nr_flows;
#घोषणा OTX2_MAX_NTUPLE_FLOWS	32
#घोषणा OTX2_MAX_UNICAST_FLOWS	8
#घोषणा OTX2_MAX_VLAN_FLOWS	1
#घोषणा OTX2_MAX_TC_FLOWS	OTX2_MAX_NTUPLE_FLOWS
#घोषणा OTX2_MCAM_COUNT		(OTX2_MAX_NTUPLE_FLOWS + \
				 OTX2_MAX_UNICAST_FLOWS + \
				 OTX2_MAX_VLAN_FLOWS)
	u32			ntuple_offset;
	u32			unicast_offset;
	u32			rx_vlan_offset;
	u32			vf_vlan_offset;
#घोषणा OTX2_PER_VF_VLAN_FLOWS	2 /* rx+tx per VF */
#घोषणा OTX2_VF_VLAN_RX_INDEX	0
#घोषणा OTX2_VF_VLAN_TX_INDEX	1
	u32			tc_flower_offset;
	u32                     ntuple_max_flows;
	u32			tc_max_flows;
	काष्ठा list_head	flow_list;
पूर्ण;

काष्ठा otx2_tc_info अणु
	/* hash table to store TC offloaded flows */
	काष्ठा rhashtable		flow_table;
	काष्ठा rhashtable_params	flow_ht_params;
	DECLARE_BITMAP(tc_entries_biपंचांगap, OTX2_MAX_TC_FLOWS);
	अचिन्हित दीर्घ			num_entries;
पूर्ण;

काष्ठा dev_hw_ops अणु
	पूर्णांक	(*sq_aq_init)(व्योम *dev, u16 qidx, u16 sqb_aura);
	व्योम	(*sqe_flush)(व्योम *dev, काष्ठा otx2_snd_queue *sq,
			     पूर्णांक size, पूर्णांक qidx);
	व्योम	(*refill_pool_ptrs)(व्योम *dev, काष्ठा otx2_cq_queue *cq);
	व्योम	(*aura_मुक्तptr)(व्योम *dev, पूर्णांक aura, u64 buf);
पूर्ण;

काष्ठा otx2_nic अणु
	व्योम __iomem		*reg_base;
	काष्ठा net_device	*netdev;
	काष्ठा dev_hw_ops	*hw_ops;
	व्योम			*iommu_करोमुख्य;
	u16			max_frs;
	u16			rbsize; /* Receive buffer size */

#घोषणा OTX2_FLAG_RX_TSTAMP_ENABLED		BIT_ULL(0)
#घोषणा OTX2_FLAG_TX_TSTAMP_ENABLED		BIT_ULL(1)
#घोषणा OTX2_FLAG_INTF_DOWN			BIT_ULL(2)
#घोषणा OTX2_FLAG_MCAM_ENTRIES_ALLOC		BIT_ULL(3)
#घोषणा OTX2_FLAG_NTUPLE_SUPPORT		BIT_ULL(4)
#घोषणा OTX2_FLAG_UCAST_FLTR_SUPPORT		BIT_ULL(5)
#घोषणा OTX2_FLAG_RX_VLAN_SUPPORT		BIT_ULL(6)
#घोषणा OTX2_FLAG_VF_VLAN_SUPPORT		BIT_ULL(7)
#घोषणा OTX2_FLAG_PF_SHUTDOWN			BIT_ULL(8)
#घोषणा OTX2_FLAG_RX_PAUSE_ENABLED		BIT_ULL(9)
#घोषणा OTX2_FLAG_TX_PAUSE_ENABLED		BIT_ULL(10)
#घोषणा OTX2_FLAG_TC_FLOWER_SUPPORT		BIT_ULL(11)
#घोषणा OTX2_FLAG_TC_MATCHALL_EGRESS_ENABLED	BIT_ULL(12)
	u64			flags;

	काष्ठा otx2_qset	qset;
	काष्ठा otx2_hw		hw;
	काष्ठा pci_dev		*pdev;
	काष्ठा device		*dev;

	/* Mbox */
	काष्ठा mbox		mbox;
	काष्ठा mbox		*mbox_pfvf;
	काष्ठा workqueue_काष्ठा *mbox_wq;
	काष्ठा workqueue_काष्ठा *mbox_pfvf_wq;

	u8			total_vfs;
	u16			pcअगरunc; /* RVU PF_FUNC */
	u16			bpid[NIX_MAX_BPID_CHAN];
	काष्ठा otx2_vf_config	*vf_configs;
	काष्ठा cgx_link_user_info linfo;

	u64			reset_count;
	काष्ठा work_काष्ठा	reset_task;
	काष्ठा workqueue_काष्ठा	*flr_wq;
	काष्ठा flr_work		*flr_wrk;
	काष्ठा refill_work	*refill_wrk;
	काष्ठा workqueue_काष्ठा	*otx2_wq;
	काष्ठा work_काष्ठा	rx_mode_work;
	काष्ठा otx2_mac_table	*mac_table;

	/* Ethtool stuff */
	u32			msg_enable;

	/* Block address of NIX either BLKADDR_NIX0 or BLKADDR_NIX1 */
	पूर्णांक			nix_blkaddr;
	/* LMTST Lines info */
	u16			tot_lmt_lines;
	u16			nix_lmt_lines;
	u32			nix_lmt_size;

	काष्ठा otx2_ptp		*ptp;
	काष्ठा hwtstamp_config	tstamp;

	काष्ठा otx2_flow_config	*flow_cfg;
	काष्ठा otx2_tc_info	tc_info;
पूर्ण;

अटल अंतरभूत bool is_otx2_lbkvf(काष्ठा pci_dev *pdev)
अणु
	वापस pdev->device == PCI_DEVID_OCTEONTX2_RVU_AFVF;
पूर्ण

अटल अंतरभूत bool is_96xx_A0(काष्ठा pci_dev *pdev)
अणु
	वापस (pdev->revision == 0x00) &&
		(pdev->subप्रणाली_device == PCI_SUBSYS_DEVID_96XX_RVU_PFVF);
पूर्ण

अटल अंतरभूत bool is_96xx_B0(काष्ठा pci_dev *pdev)
अणु
	वापस (pdev->revision == 0x01) &&
		(pdev->subप्रणाली_device == PCI_SUBSYS_DEVID_96XX_RVU_PFVF);
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

अटल अंतरभूत bool is_dev_otx2(काष्ठा pci_dev *pdev)
अणु
	u8 midr = pdev->revision & 0xF0;

	वापस (midr == PCI_REVISION_ID_96XX || midr == PCI_REVISION_ID_95XX ||
		midr == PCI_REVISION_ID_LOKI || midr == PCI_REVISION_ID_98XX ||
		midr == PCI_REVISION_ID_95XXMM);
पूर्ण

अटल अंतरभूत व्योम otx2_setup_dev_hw_settings(काष्ठा otx2_nic *pfvf)
अणु
	काष्ठा otx2_hw *hw = &pfvf->hw;

	pfvf->hw.cq_समय_रुको = CQ_TIMER_THRESH_DEFAULT;
	pfvf->hw.cq_ecount_रुको = CQ_CQE_THRESH_DEFAULT;
	pfvf->hw.cq_qcount_रुको = CQ_QCOUNT_DEFAULT;

	__set_bit(HW_TSO, &hw->cap_flag);

	अगर (is_96xx_A0(pfvf->pdev)) अणु
		__clear_bit(HW_TSO, &hw->cap_flag);

		/* Time based irq coalescing is not supported */
		pfvf->hw.cq_qcount_रुको = 0x0;

		/* Due to HW issue previous silicons required minimum
		 * 600 unused CQE to aव्योम CQ overflow.
		 */
		pfvf->hw.rq_skid = 600;
		pfvf->qset.rqe_cnt = Q_COUNT(Q_SIZE_1K);
	पूर्ण
	अगर (is_96xx_B0(pfvf->pdev))
		__clear_bit(HW_TSO, &hw->cap_flag);

	अगर (!is_dev_otx2(pfvf->pdev)) अणु
		__set_bit(CN10K_MBOX, &hw->cap_flag);
		__set_bit(CN10K_LMTST, &hw->cap_flag);
	पूर्ण
पूर्ण

/* Register पढ़ो/ग_लिखो APIs */
अटल अंतरभूत व्योम __iomem *otx2_get_regaddr(काष्ठा otx2_nic *nic, u64 offset)
अणु
	u64 blkaddr;

	चयन ((offset >> RVU_FUNC_BLKADDR_SHIFT) & RVU_FUNC_BLKADDR_MASK) अणु
	हाल BLKTYPE_NIX:
		blkaddr = nic->nix_blkaddr;
		अवरोध;
	हाल BLKTYPE_NPA:
		blkaddr = BLKADDR_NPA;
		अवरोध;
	शेष:
		blkaddr = BLKADDR_RVUM;
		अवरोध;
	पूर्ण

	offset &= ~(RVU_FUNC_BLKADDR_MASK << RVU_FUNC_BLKADDR_SHIFT);
	offset |= (blkaddr << RVU_FUNC_BLKADDR_SHIFT);

	वापस nic->reg_base + offset;
पूर्ण

अटल अंतरभूत व्योम otx2_ग_लिखो64(काष्ठा otx2_nic *nic, u64 offset, u64 val)
अणु
	व्योम __iomem *addr = otx2_get_regaddr(nic, offset);

	ग_लिखोq(val, addr);
पूर्ण

अटल अंतरभूत u64 otx2_पढ़ो64(काष्ठा otx2_nic *nic, u64 offset)
अणु
	व्योम __iomem *addr = otx2_get_regaddr(nic, offset);

	वापस पढ़ोq(addr);
पूर्ण

/* Mbox bounce buffer APIs */
अटल अंतरभूत पूर्णांक otx2_mbox_bbuf_init(काष्ठा mbox *mbox, काष्ठा pci_dev *pdev)
अणु
	काष्ठा otx2_mbox *otx2_mbox;
	काष्ठा otx2_mbox_dev *mdev;

	mbox->bbuf_base = devm_kदो_स्मृति(&pdev->dev, MBOX_SIZE, GFP_KERNEL);
	अगर (!mbox->bbuf_base)
		वापस -ENOMEM;

	/* Overग_लिखो mbox mbase to poपूर्णांक to bounce buffer, so that PF/VF
	 * prepare all mbox messages in bounce buffer instead of directly
	 * in hw mbox memory.
	 */
	otx2_mbox = &mbox->mbox;
	mdev = &otx2_mbox->dev[0];
	mdev->mbase = mbox->bbuf_base;

	otx2_mbox = &mbox->mbox_up;
	mdev = &otx2_mbox->dev[0];
	mdev->mbase = mbox->bbuf_base;
	वापस 0;
पूर्ण

अटल अंतरभूत व्योम otx2_sync_mbox_bbuf(काष्ठा otx2_mbox *mbox, पूर्णांक devid)
अणु
	u16 msgs_offset = ALIGN(माप(काष्ठा mbox_hdr), MBOX_MSG_ALIGN);
	व्योम *hw_mbase = mbox->hwbase + (devid * MBOX_SIZE);
	काष्ठा otx2_mbox_dev *mdev = &mbox->dev[devid];
	काष्ठा mbox_hdr *hdr;
	u64 msg_size;

	अगर (mdev->mbase == hw_mbase)
		वापस;

	hdr = hw_mbase + mbox->rx_start;
	msg_size = hdr->msg_size;

	अगर (msg_size > mbox->rx_size - msgs_offset)
		msg_size = mbox->rx_size - msgs_offset;

	/* Copy mbox messages from mbox memory to bounce buffer */
	स_नकल(mdev->mbase + mbox->rx_start,
	       hw_mbase + mbox->rx_start, msg_size + msgs_offset);
पूर्ण

/* With the असलence of API क्रम 128-bit IO memory access क्रम arm64,
 * implement required operations at place.
 */
#अगर defined(CONFIG_ARM64)
अटल अंतरभूत व्योम otx2_ग_लिखो128(u64 lo, u64 hi, व्योम __iomem *addr)
अणु
	__यंत्र__ अस्थिर("stp %x[x0], %x[x1], [%x[p1],#0]!"
			 ::[x0]"r"(lo), [x1]"r"(hi), [p1]"r"(addr));
पूर्ण

अटल अंतरभूत u64 otx2_atomic64_add(u64 incr, u64 *ptr)
अणु
	u64 result;

	__यंत्र__ अस्थिर(".cpu   generic+lse\n"
			 "ldadd %x[i], %x[r], [%[b]]"
			 : [r]"=r"(result), "+m"(*ptr)
			 : [i]"r"(incr), [b]"r"(ptr)
			 : "memory");
	वापस result;
पूर्ण

#अन्यथा
#घोषणा otx2_ग_लिखो128(lo, hi, addr)		ग_लिखोq((hi) | (lo), addr)
#घोषणा otx2_atomic64_add(incr, ptr)		(अणु *ptr += incr; पूर्ण)
#पूर्ण_अगर

अटल अंतरभूत व्योम __cn10k_aura_मुक्तptr(काष्ठा otx2_nic *pfvf, u64 aura,
					u64 *ptrs, u64 num_ptrs,
					u64 *lmt_addr)
अणु
	u64 size = 0, count_eot = 0;
	u64 tar_addr, val = 0;

	tar_addr = (__क्रमce u64)otx2_get_regaddr(pfvf, NPA_LF_AURA_BATCH_FREE0);
	/* LMTID is same as AURA Id */
	val = (aura & 0x7FF) | BIT_ULL(63);
	/* Set अगर [127:64] of last 128bit word has a valid poपूर्णांकer */
	count_eot = (num_ptrs % 2) ? 0ULL : 1ULL;
	/* Set AURA ID to मुक्त poपूर्णांकer */
	ptrs[0] = (count_eot << 32) | (aura & 0xFFFFF);
	/* Target address क्रम LMTST flush tells HW how many 128bit
	 * words are valid from NPA_LF_AURA_BATCH_FREE0.
	 *
	 * tar_addr[6:4] is LMTST size-1 in units of 128b.
	 */
	अगर (num_ptrs > 2) अणु
		size = (माप(u64) * num_ptrs) / 16;
		अगर (!count_eot)
			size++;
		tar_addr |=  ((size - 1) & 0x7) << 4;
	पूर्ण
	स_नकल(lmt_addr, ptrs, माप(u64) * num_ptrs);
	/* Perक्रमm LMTST flush */
	cn10k_lmt_flush(val, tar_addr);
पूर्ण

अटल अंतरभूत व्योम cn10k_aura_मुक्तptr(व्योम *dev, पूर्णांक aura, u64 buf)
अणु
	काष्ठा otx2_nic *pfvf = dev;
	काष्ठा otx2_pool *pool;
	u64 ptrs[2];

	pool = &pfvf->qset.pool[aura];
	ptrs[1] = buf;
	__cn10k_aura_मुक्तptr(pfvf, aura, ptrs, 2, pool->lmt_addr);
पूर्ण

/* Alloc poपूर्णांकer from pool/aura */
अटल अंतरभूत u64 otx2_aura_allocptr(काष्ठा otx2_nic *pfvf, पूर्णांक aura)
अणु
	u64 *ptr = (u64 *)otx2_get_regaddr(pfvf,
			   NPA_LF_AURA_OP_ALLOCX(0));
	u64 incr = (u64)aura | BIT_ULL(63);

	वापस otx2_atomic64_add(incr, ptr);
पूर्ण

/* Free poपूर्णांकer to a pool/aura */
अटल अंतरभूत व्योम otx2_aura_मुक्तptr(व्योम *dev, पूर्णांक aura, u64 buf)
अणु
	काष्ठा otx2_nic *pfvf = dev;
	व्योम __iomem *addr = otx2_get_regaddr(pfvf, NPA_LF_AURA_OP_FREE0);

	otx2_ग_लिखो128(buf, (u64)aura | BIT_ULL(63), addr);
पूर्ण

अटल अंतरभूत पूर्णांक otx2_get_pool_idx(काष्ठा otx2_nic *pfvf, पूर्णांक type, पूर्णांक idx)
अणु
	अगर (type == AURA_NIX_SQ)
		वापस pfvf->hw.rqpool_cnt + idx;

	 /* AURA_NIX_RQ */
	वापस idx;
पूर्ण

/* Mbox APIs */
अटल अंतरभूत पूर्णांक otx2_sync_mbox_msg(काष्ठा mbox *mbox)
अणु
	पूर्णांक err;

	अगर (!otx2_mbox_nonempty(&mbox->mbox, 0))
		वापस 0;
	otx2_mbox_msg_send(&mbox->mbox, 0);
	err = otx2_mbox_रुको_क्रम_rsp(&mbox->mbox, 0);
	अगर (err)
		वापस err;

	वापस otx2_mbox_check_rsp_msgs(&mbox->mbox, 0);
पूर्ण

अटल अंतरभूत पूर्णांक otx2_sync_mbox_up_msg(काष्ठा mbox *mbox, पूर्णांक devid)
अणु
	पूर्णांक err;

	अगर (!otx2_mbox_nonempty(&mbox->mbox_up, devid))
		वापस 0;
	otx2_mbox_msg_send(&mbox->mbox_up, devid);
	err = otx2_mbox_रुको_क्रम_rsp(&mbox->mbox_up, devid);
	अगर (err)
		वापस err;

	वापस otx2_mbox_check_rsp_msgs(&mbox->mbox_up, devid);
पूर्ण

/* Use this API to send mbox msgs in atomic context
 * where sleeping is not allowed
 */
अटल अंतरभूत पूर्णांक otx2_sync_mbox_msg_busy_poll(काष्ठा mbox *mbox)
अणु
	पूर्णांक err;

	अगर (!otx2_mbox_nonempty(&mbox->mbox, 0))
		वापस 0;
	otx2_mbox_msg_send(&mbox->mbox, 0);
	err = otx2_mbox_busy_poll_क्रम_rsp(&mbox->mbox, 0);
	अगर (err)
		वापस err;

	वापस otx2_mbox_check_rsp_msgs(&mbox->mbox, 0);
पूर्ण

#घोषणा M(_name, _id, _fn_name, _req_type, _rsp_type)                   \
अटल काष्ठा _req_type __maybe_unused					\
*otx2_mbox_alloc_msg_ ## _fn_name(काष्ठा mbox *mbox)                    \
अणु									\
	काष्ठा _req_type *req;						\
									\
	req = (काष्ठा _req_type *)otx2_mbox_alloc_msg_rsp(		\
		&mbox->mbox, 0, माप(काष्ठा _req_type),		\
		माप(काष्ठा _rsp_type));				\
	अगर (!req)							\
		वापस शून्य;						\
	req->hdr.sig = OTX2_MBOX_REQ_SIG;				\
	req->hdr.id = _id;						\
	trace_otx2_msg_alloc(mbox->mbox.pdev, _id, माप(*req));	\
	वापस req;							\
पूर्ण

MBOX_MESSAGES
#अघोषित M

#घोषणा M(_name, _id, _fn_name, _req_type, _rsp_type)			\
पूर्णांक									\
otx2_mbox_up_handler_ ## _fn_name(काष्ठा otx2_nic *pfvf,		\
				काष्ठा _req_type *req,			\
				काष्ठा _rsp_type *rsp);			\

MBOX_UP_CGX_MESSAGES
#अघोषित M

/* Time to रुको beक्रमe watchकरोg kicks off */
#घोषणा OTX2_TX_TIMEOUT		(100 * HZ)

#घोषणा	RVU_PFVF_PF_SHIFT	10
#घोषणा	RVU_PFVF_PF_MASK	0x3F
#घोषणा	RVU_PFVF_FUNC_SHIFT	0
#घोषणा	RVU_PFVF_FUNC_MASK	0x3FF

अटल अंतरभूत पूर्णांक rvu_get_pf(u16 pcअगरunc)
अणु
	वापस (pcअगरunc >> RVU_PFVF_PF_SHIFT) & RVU_PFVF_PF_MASK;
पूर्ण

अटल अंतरभूत dma_addr_t otx2_dma_map_page(काष्ठा otx2_nic *pfvf,
					   काष्ठा page *page,
					   माप_प्रकार offset, माप_प्रकार size,
					   क्रमागत dma_data_direction dir)
अणु
	dma_addr_t iova;

	iova = dma_map_page_attrs(pfvf->dev, page,
				  offset, size, dir, DMA_ATTR_SKIP_CPU_SYNC);
	अगर (unlikely(dma_mapping_error(pfvf->dev, iova)))
		वापस (dma_addr_t)शून्य;
	वापस iova;
पूर्ण

अटल अंतरभूत व्योम otx2_dma_unmap_page(काष्ठा otx2_nic *pfvf,
				       dma_addr_t addr, माप_प्रकार size,
				       क्रमागत dma_data_direction dir)
अणु
	dma_unmap_page_attrs(pfvf->dev, addr, size,
			     dir, DMA_ATTR_SKIP_CPU_SYNC);
पूर्ण

/* MSI-X APIs */
व्योम otx2_मुक्त_cपूर्णांकs(काष्ठा otx2_nic *pfvf, पूर्णांक n);
व्योम otx2_set_cपूर्णांकs_affinity(काष्ठा otx2_nic *pfvf);
पूर्णांक otx2_set_mac_address(काष्ठा net_device *netdev, व्योम *p);
पूर्णांक otx2_hw_set_mtu(काष्ठा otx2_nic *pfvf, पूर्णांक mtu);
व्योम otx2_tx_समयout(काष्ठा net_device *netdev, अचिन्हित पूर्णांक txq);
व्योम otx2_get_mac_from_af(काष्ठा net_device *netdev);
व्योम otx2_config_irq_coalescing(काष्ठा otx2_nic *pfvf, पूर्णांक qidx);
पूर्णांक otx2_config_छोड़ो_frm(काष्ठा otx2_nic *pfvf);
व्योम otx2_setup_segmentation(काष्ठा otx2_nic *pfvf);

/* RVU block related APIs */
पूर्णांक otx2_attach_npa_nix(काष्ठा otx2_nic *pfvf);
पूर्णांक otx2_detach_resources(काष्ठा mbox *mbox);
पूर्णांक otx2_config_npa(काष्ठा otx2_nic *pfvf);
पूर्णांक otx2_sq_aura_pool_init(काष्ठा otx2_nic *pfvf);
पूर्णांक otx2_rq_aura_pool_init(काष्ठा otx2_nic *pfvf);
व्योम otx2_aura_pool_मुक्त(काष्ठा otx2_nic *pfvf);
व्योम otx2_मुक्त_aura_ptr(काष्ठा otx2_nic *pfvf, पूर्णांक type);
व्योम otx2_sq_मुक्त_sqbs(काष्ठा otx2_nic *pfvf);
पूर्णांक otx2_config_nix(काष्ठा otx2_nic *pfvf);
पूर्णांक otx2_config_nix_queues(काष्ठा otx2_nic *pfvf);
पूर्णांक otx2_txschq_config(काष्ठा otx2_nic *pfvf, पूर्णांक lvl);
पूर्णांक otx2_txsch_alloc(काष्ठा otx2_nic *pfvf);
पूर्णांक otx2_txschq_stop(काष्ठा otx2_nic *pfvf);
व्योम otx2_sqb_flush(काष्ठा otx2_nic *pfvf);
पूर्णांक __otx2_alloc_rbuf(काष्ठा otx2_nic *pfvf, काष्ठा otx2_pool *pool,
		      dma_addr_t *dma);
पूर्णांक otx2_rxtx_enable(काष्ठा otx2_nic *pfvf, bool enable);
व्योम otx2_ctx_disable(काष्ठा mbox *mbox, पूर्णांक type, bool npa);
पूर्णांक otx2_nix_config_bp(काष्ठा otx2_nic *pfvf, bool enable);
व्योम otx2_cleanup_rx_cqes(काष्ठा otx2_nic *pfvf, काष्ठा otx2_cq_queue *cq);
व्योम otx2_cleanup_tx_cqes(काष्ठा otx2_nic *pfvf, काष्ठा otx2_cq_queue *cq);
पूर्णांक otx2_sq_aq_init(व्योम *dev, u16 qidx, u16 sqb_aura);
पूर्णांक cn10k_sq_aq_init(व्योम *dev, u16 qidx, u16 sqb_aura);
पूर्णांक otx2_alloc_buffer(काष्ठा otx2_nic *pfvf, काष्ठा otx2_cq_queue *cq,
		      dma_addr_t *dma);

/* RSS configuration APIs*/
पूर्णांक otx2_rss_init(काष्ठा otx2_nic *pfvf);
पूर्णांक otx2_set_flowkey_cfg(काष्ठा otx2_nic *pfvf);
व्योम otx2_set_rss_key(काष्ठा otx2_nic *pfvf);
पूर्णांक otx2_set_rss_table(काष्ठा otx2_nic *pfvf, पूर्णांक ctx_id);

/* Mbox handlers */
व्योम mbox_handler_msix_offset(काष्ठा otx2_nic *pfvf,
			      काष्ठा msix_offset_rsp *rsp);
व्योम mbox_handler_npa_lf_alloc(काष्ठा otx2_nic *pfvf,
			       काष्ठा npa_lf_alloc_rsp *rsp);
व्योम mbox_handler_nix_lf_alloc(काष्ठा otx2_nic *pfvf,
			       काष्ठा nix_lf_alloc_rsp *rsp);
व्योम mbox_handler_nix_txsch_alloc(काष्ठा otx2_nic *pf,
				  काष्ठा nix_txsch_alloc_rsp *rsp);
व्योम mbox_handler_cgx_stats(काष्ठा otx2_nic *pfvf,
			    काष्ठा cgx_stats_rsp *rsp);
व्योम mbox_handler_cgx_fec_stats(काष्ठा otx2_nic *pfvf,
				काष्ठा cgx_fec_stats_rsp *rsp);
व्योम otx2_set_fec_stats_count(काष्ठा otx2_nic *pfvf);
व्योम mbox_handler_nix_bp_enable(काष्ठा otx2_nic *pfvf,
				काष्ठा nix_bp_cfg_rsp *rsp);

/* Device stats APIs */
व्योम otx2_get_dev_stats(काष्ठा otx2_nic *pfvf);
व्योम otx2_get_stats64(काष्ठा net_device *netdev,
		      काष्ठा rtnl_link_stats64 *stats);
व्योम otx2_update_lmac_stats(काष्ठा otx2_nic *pfvf);
व्योम otx2_update_lmac_fec_stats(काष्ठा otx2_nic *pfvf);
पूर्णांक otx2_update_rq_stats(काष्ठा otx2_nic *pfvf, पूर्णांक qidx);
पूर्णांक otx2_update_sq_stats(काष्ठा otx2_nic *pfvf, पूर्णांक qidx);
व्योम otx2_set_ethtool_ops(काष्ठा net_device *netdev);
व्योम otx2vf_set_ethtool_ops(काष्ठा net_device *netdev);

पूर्णांक otx2_खोलो(काष्ठा net_device *netdev);
पूर्णांक otx2_stop(काष्ठा net_device *netdev);
पूर्णांक otx2_set_real_num_queues(काष्ठा net_device *netdev,
			     पूर्णांक tx_queues, पूर्णांक rx_queues);
/* MCAM filter related APIs */
पूर्णांक otx2_mcam_flow_init(काष्ठा otx2_nic *pf);
पूर्णांक otx2_alloc_mcam_entries(काष्ठा otx2_nic *pfvf);
व्योम otx2_mcam_flow_del(काष्ठा otx2_nic *pf);
पूर्णांक otx2_destroy_ntuple_flows(काष्ठा otx2_nic *pf);
पूर्णांक otx2_destroy_mcam_flows(काष्ठा otx2_nic *pfvf);
पूर्णांक otx2_get_flow(काष्ठा otx2_nic *pfvf,
		  काष्ठा ethtool_rxnfc *nfc, u32 location);
पूर्णांक otx2_get_all_flows(काष्ठा otx2_nic *pfvf,
		       काष्ठा ethtool_rxnfc *nfc, u32 *rule_locs);
पूर्णांक otx2_add_flow(काष्ठा otx2_nic *pfvf,
		  काष्ठा ethtool_rxnfc *nfc);
पूर्णांक otx2_हटाओ_flow(काष्ठा otx2_nic *pfvf, u32 location);
पूर्णांक otx2_prepare_flow_request(काष्ठा ethtool_rx_flow_spec *fsp,
			      काष्ठा npc_install_flow_req *req);
व्योम otx2_rss_ctx_flow_del(काष्ठा otx2_nic *pfvf, पूर्णांक ctx_id);
पूर्णांक otx2_del_macfilter(काष्ठा net_device *netdev, स्थिर u8 *mac);
पूर्णांक otx2_add_macfilter(काष्ठा net_device *netdev, स्थिर u8 *mac);
पूर्णांक otx2_enable_rxvlan(काष्ठा otx2_nic *pf, bool enable);
पूर्णांक otx2_install_rxvlan_offload_flow(काष्ठा otx2_nic *pfvf);
u16 otx2_get_max_mtu(काष्ठा otx2_nic *pfvf);
/* tc support */
पूर्णांक otx2_init_tc(काष्ठा otx2_nic *nic);
व्योम otx2_shutकरोwn_tc(काष्ठा otx2_nic *nic);
पूर्णांक otx2_setup_tc(काष्ठा net_device *netdev, क्रमागत tc_setup_type type,
		  व्योम *type_data);
#पूर्ण_अगर /* OTX2_COMMON_H */
