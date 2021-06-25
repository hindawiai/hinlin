<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (C) 2015 Cavium, Inc.
 */

#समावेश <linux/module.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/pci.h>
#समावेश <linux/etherdevice.h>
#समावेश <linux/of.h>
#समावेश <linux/अगर_vlan.h>

#समावेश "nic_reg.h"
#समावेश "nic.h"
#समावेश "q_struct.h"
#समावेश "thunder_bgx.h"

#घोषणा DRV_NAME	"nicpf"
#घोषणा DRV_VERSION	"1.0"

#घोषणा NIC_VF_PER_MBX_REG      64

काष्ठा hw_info अणु
	u8		bgx_cnt;
	u8		chans_per_lmac;
	u8		chans_per_bgx; /* Rx/Tx chans */
	u8		chans_per_rgx;
	u8		chans_per_lbk;
	u16		cpi_cnt;
	u16		rssi_cnt;
	u16		rss_ind_tbl_size;
	u16		tl4_cnt;
	u16		tl3_cnt;
	u8		tl2_cnt;
	u8		tl1_cnt;
	bool		tl1_per_bgx; /* TL1 per BGX or per LMAC */
पूर्ण;

काष्ठा nicpf अणु
	काष्ठा pci_dev		*pdev;
	काष्ठा hw_info          *hw;
	u8			node;
	अचिन्हित पूर्णांक		flags;
	u8			num_vf_en;      /* No of VF enabled */
	bool			vf_enabled[MAX_NUM_VFS_SUPPORTED];
	व्योम __iomem		*reg_base;       /* Register start address */
	u8			num_sqs_en;	/* Secondary qsets enabled */
	u64			nicvf[MAX_NUM_VFS_SUPPORTED];
	u8			vf_sqs[MAX_NUM_VFS_SUPPORTED][MAX_SQS_PER_VF];
	u8			pqs_vf[MAX_NUM_VFS_SUPPORTED];
	bool			sqs_used[MAX_NUM_VFS_SUPPORTED];
	काष्ठा pkind_cfg	pkind;
#घोषणा	NIC_SET_VF_LMAC_MAP(bgx, lmac)	(((bgx & 0xF) << 4) | (lmac & 0xF))
#घोषणा	NIC_GET_BGX_FROM_VF_LMAC_MAP(map)	((map >> 4) & 0xF)
#घोषणा	NIC_GET_LMAC_FROM_VF_LMAC_MAP(map)	(map & 0xF)
	u8			*vf_lmac_map;
	u16			cpi_base[MAX_NUM_VFS_SUPPORTED];
	u16			rssi_base[MAX_NUM_VFS_SUPPORTED];

	/* MSI-X */
	u8			num_vec;
	bool			irq_allocated[NIC_PF_MSIX_VECTORS];
	अक्षर			irq_name[NIC_PF_MSIX_VECTORS][20];
पूर्ण;

/* Supported devices */
अटल स्थिर काष्ठा pci_device_id nic_id_table[] = अणु
	अणु PCI_DEVICE(PCI_VENDOR_ID_CAVIUM, PCI_DEVICE_ID_THUNDER_NIC_PF) पूर्ण,
	अणु 0, पूर्ण  /* end of table */
पूर्ण;

MODULE_AUTHOR("Sunil Goutham");
MODULE_DESCRIPTION("Cavium Thunder NIC Physical Function Driver");
MODULE_LICENSE("GPL v2");
MODULE_VERSION(DRV_VERSION);
MODULE_DEVICE_TABLE(pci, nic_id_table);

/* The Cavium ThunderX network controller can *only* be found in SoCs
 * containing the ThunderX ARM64 CPU implementation.  All accesses to the device
 * रेजिस्टरs on this platक्रमm are implicitly strongly ordered with respect
 * to memory accesses. So ग_लिखोq_relaxed() and पढ़ोq_relaxed() are safe to use
 * with no memory barriers in this driver.  The पढ़ोq()/ग_लिखोq() functions add
 * explicit ordering operation which in this हाल are redundant, and only
 * add overhead.
 */

/* Register पढ़ो/ग_लिखो APIs */
अटल व्योम nic_reg_ग_लिखो(काष्ठा nicpf *nic, u64 offset, u64 val)
अणु
	ग_लिखोq_relaxed(val, nic->reg_base + offset);
पूर्ण

अटल u64 nic_reg_पढ़ो(काष्ठा nicpf *nic, u64 offset)
अणु
	वापस पढ़ोq_relaxed(nic->reg_base + offset);
पूर्ण

/* PF -> VF mailbox communication APIs */
अटल व्योम nic_enable_mbx_पूर्णांकr(काष्ठा nicpf *nic)
अणु
	पूर्णांक vf_cnt = pci_sriov_get_totalvfs(nic->pdev);

#घोषणा INTR_MASK(vfs) ((vfs < 64) ? (BIT_ULL(vfs) - 1) : (~0ull))

	/* Clear it, to aव्योम spurious पूर्णांकerrupts (अगर any) */
	nic_reg_ग_लिखो(nic, NIC_PF_MAILBOX_INT, INTR_MASK(vf_cnt));

	/* Enable mailbox पूर्णांकerrupt क्रम all VFs */
	nic_reg_ग_लिखो(nic, NIC_PF_MAILBOX_ENA_W1S, INTR_MASK(vf_cnt));
	/* One mailbox पूर्णांकr enable reg per 64 VFs */
	अगर (vf_cnt > 64) अणु
		nic_reg_ग_लिखो(nic, NIC_PF_MAILBOX_INT + माप(u64),
			      INTR_MASK(vf_cnt - 64));
		nic_reg_ग_लिखो(nic, NIC_PF_MAILBOX_ENA_W1S + माप(u64),
			      INTR_MASK(vf_cnt - 64));
	पूर्ण
पूर्ण

अटल व्योम nic_clear_mbx_पूर्णांकr(काष्ठा nicpf *nic, पूर्णांक vf, पूर्णांक mbx_reg)
अणु
	nic_reg_ग_लिखो(nic, NIC_PF_MAILBOX_INT + (mbx_reg << 3), BIT_ULL(vf));
पूर्ण

अटल u64 nic_get_mbx_addr(पूर्णांक vf)
अणु
	वापस NIC_PF_VF_0_127_MAILBOX_0_1 + (vf << NIC_VF_NUM_SHIFT);
पूर्ण

/* Send a mailbox message to VF
 * @vf: vf to which this message to be sent
 * @mbx: Message to be sent
 */
अटल व्योम nic_send_msg_to_vf(काष्ठा nicpf *nic, पूर्णांक vf, जोड़ nic_mbx *mbx)
अणु
	व्योम __iomem *mbx_addr = nic->reg_base + nic_get_mbx_addr(vf);
	u64 *msg = (u64 *)mbx;

	/* In first revision HW, mbox पूर्णांकerrupt is triggerred
	 * when PF ग_लिखोs to MBOX(1), in next revisions when
	 * PF ग_लिखोs to MBOX(0)
	 */
	अगर (pass1_silicon(nic->pdev)) अणु
		/* see the comment क्रम nic_reg_ग_लिखो()/nic_reg_पढ़ो()
		 * functions above
		 */
		ग_लिखोq_relaxed(msg[0], mbx_addr);
		ग_लिखोq_relaxed(msg[1], mbx_addr + 8);
	पूर्ण अन्यथा अणु
		ग_लिखोq_relaxed(msg[1], mbx_addr + 8);
		ग_लिखोq_relaxed(msg[0], mbx_addr);
	पूर्ण
पूर्ण

/* Responds to VF's READY message with VF's
 * ID, node, MAC address e.t.c
 * @vf: VF which sent READY message
 */
अटल व्योम nic_mbx_send_पढ़ोy(काष्ठा nicpf *nic, पूर्णांक vf)
अणु
	जोड़ nic_mbx mbx = अणुपूर्ण;
	पूर्णांक bgx_idx, lmac;
	स्थिर अक्षर *mac;

	mbx.nic_cfg.msg = NIC_MBOX_MSG_READY;
	mbx.nic_cfg.vf_id = vf;

	mbx.nic_cfg.tns_mode = NIC_TNS_BYPASS_MODE;

	अगर (vf < nic->num_vf_en) अणु
		bgx_idx = NIC_GET_BGX_FROM_VF_LMAC_MAP(nic->vf_lmac_map[vf]);
		lmac = NIC_GET_LMAC_FROM_VF_LMAC_MAP(nic->vf_lmac_map[vf]);

		mac = bgx_get_lmac_mac(nic->node, bgx_idx, lmac);
		अगर (mac)
			ether_addr_copy((u8 *)&mbx.nic_cfg.mac_addr, mac);
	पूर्ण
	mbx.nic_cfg.sqs_mode = (vf >= nic->num_vf_en) ? true : false;
	mbx.nic_cfg.node_id = nic->node;

	mbx.nic_cfg.loopback_supported = vf < nic->num_vf_en;

	nic_send_msg_to_vf(nic, vf, &mbx);
पूर्ण

/* ACKs VF's mailbox message
 * @vf: VF to which ACK to be sent
 */
अटल व्योम nic_mbx_send_ack(काष्ठा nicpf *nic, पूर्णांक vf)
अणु
	जोड़ nic_mbx mbx = अणुपूर्ण;

	mbx.msg.msg = NIC_MBOX_MSG_ACK;
	nic_send_msg_to_vf(nic, vf, &mbx);
पूर्ण

/* NACKs VF's mailbox message that PF is not able to
 * complete the action
 * @vf: VF to which ACK to be sent
 */
अटल व्योम nic_mbx_send_nack(काष्ठा nicpf *nic, पूर्णांक vf)
अणु
	जोड़ nic_mbx mbx = अणुपूर्ण;

	mbx.msg.msg = NIC_MBOX_MSG_NACK;
	nic_send_msg_to_vf(nic, vf, &mbx);
पूर्ण

/* Flush all in flight receive packets to memory and
 * bring करोwn an active RQ
 */
अटल पूर्णांक nic_rcv_queue_sw_sync(काष्ठा nicpf *nic)
अणु
	u16 समयout = ~0x00;

	nic_reg_ग_लिखो(nic, NIC_PF_SW_SYNC_RX, 0x01);
	/* Wait till sync cycle is finished */
	जबतक (समयout) अणु
		अगर (nic_reg_पढ़ो(nic, NIC_PF_SW_SYNC_RX_DONE) & 0x1)
			अवरोध;
		समयout--;
	पूर्ण
	nic_reg_ग_लिखो(nic, NIC_PF_SW_SYNC_RX, 0x00);
	अगर (!समयout) अणु
		dev_err(&nic->pdev->dev, "Receive queue software sync failed");
		वापस 1;
	पूर्ण
	वापस 0;
पूर्ण

/* Get BGX Rx/Tx stats and respond to VF's request */
अटल व्योम nic_get_bgx_stats(काष्ठा nicpf *nic, काष्ठा bgx_stats_msg *bgx)
अणु
	पूर्णांक bgx_idx, lmac;
	जोड़ nic_mbx mbx = अणुपूर्ण;

	bgx_idx = NIC_GET_BGX_FROM_VF_LMAC_MAP(nic->vf_lmac_map[bgx->vf_id]);
	lmac = NIC_GET_LMAC_FROM_VF_LMAC_MAP(nic->vf_lmac_map[bgx->vf_id]);

	mbx.bgx_stats.msg = NIC_MBOX_MSG_BGX_STATS;
	mbx.bgx_stats.vf_id = bgx->vf_id;
	mbx.bgx_stats.rx = bgx->rx;
	mbx.bgx_stats.idx = bgx->idx;
	अगर (bgx->rx)
		mbx.bgx_stats.stats = bgx_get_rx_stats(nic->node, bgx_idx,
							    lmac, bgx->idx);
	अन्यथा
		mbx.bgx_stats.stats = bgx_get_tx_stats(nic->node, bgx_idx,
							    lmac, bgx->idx);
	nic_send_msg_to_vf(nic, bgx->vf_id, &mbx);
पूर्ण

/* Update hardware min/max frame size */
अटल पूर्णांक nic_update_hw_frs(काष्ठा nicpf *nic, पूर्णांक new_frs, पूर्णांक vf)
अणु
	पूर्णांक bgx, lmac, lmac_cnt;
	u64 lmac_credits;

	अगर ((new_frs > NIC_HW_MAX_FRS) || (new_frs < NIC_HW_MIN_FRS))
		वापस 1;

	bgx = NIC_GET_BGX_FROM_VF_LMAC_MAP(nic->vf_lmac_map[vf]);
	lmac = NIC_GET_LMAC_FROM_VF_LMAC_MAP(nic->vf_lmac_map[vf]);
	lmac += bgx * MAX_LMAC_PER_BGX;

	new_frs += VLAN_ETH_HLEN + ETH_FCS_LEN + 4;

	/* Update corresponding LMAC credits */
	lmac_cnt = bgx_get_lmac_count(nic->node, bgx);
	lmac_credits = nic_reg_पढ़ो(nic, NIC_PF_LMAC_0_7_CREDIT + (lmac * 8));
	lmac_credits &= ~(0xFFFFFULL << 12);
	lmac_credits |= (((((48 * 1024) / lmac_cnt) - new_frs) / 16) << 12);
	nic_reg_ग_लिखो(nic, NIC_PF_LMAC_0_7_CREDIT + (lmac * 8), lmac_credits);

	/* Enक्रमce MTU in HW
	 * This config is supported only from 88xx pass 2.0 onwards.
	 */
	अगर (!pass1_silicon(nic->pdev))
		nic_reg_ग_लिखो(nic,
			      NIC_PF_LMAC_0_7_CFG2 + (lmac * 8), new_frs);
	वापस 0;
पूर्ण

/* Set minimum transmit packet size */
अटल व्योम nic_set_tx_pkt_pad(काष्ठा nicpf *nic, पूर्णांक size)
अणु
	पूर्णांक lmac, max_lmac;
	u16 sdevid;
	u64 lmac_cfg;

	/* There is a issue in HW where-in जबतक sending GSO sized
	 * pkts as part of TSO, अगर pkt len falls below this size
	 * NIC will zero PAD packet and also updates IP total length.
	 * Hence set this value to lessthan min pkt size of MAC+IP+TCP
	 * headers, BGX will करो the padding to transmit 64 byte pkt.
	 */
	अगर (size > 52)
		size = 52;

	pci_पढ़ो_config_word(nic->pdev, PCI_SUBSYSTEM_ID, &sdevid);
	/* 81xx's RGX has only one LMAC */
	अगर (sdevid == PCI_SUBSYS_DEVID_81XX_NIC_PF)
		max_lmac = ((nic->hw->bgx_cnt - 1) * MAX_LMAC_PER_BGX) + 1;
	अन्यथा
		max_lmac = nic->hw->bgx_cnt * MAX_LMAC_PER_BGX;

	क्रम (lmac = 0; lmac < max_lmac; lmac++) अणु
		lmac_cfg = nic_reg_पढ़ो(nic, NIC_PF_LMAC_0_7_CFG | (lmac << 3));
		lmac_cfg &= ~(0xF << 2);
		lmac_cfg |= ((size / 4) << 2);
		nic_reg_ग_लिखो(nic, NIC_PF_LMAC_0_7_CFG | (lmac << 3), lmac_cfg);
	पूर्ण
पूर्ण

/* Function to check number of LMACs present and set VF::LMAC mapping.
 * Mapping will be used जबतक initializing channels.
 */
अटल व्योम nic_set_lmac_vf_mapping(काष्ठा nicpf *nic)
अणु
	अचिन्हित bgx_map = bgx_get_map(nic->node);
	पूर्णांक bgx, next_bgx_lmac = 0;
	पूर्णांक lmac, lmac_cnt = 0;
	u64 lmac_credit;

	nic->num_vf_en = 0;

	क्रम (bgx = 0; bgx < nic->hw->bgx_cnt; bgx++) अणु
		अगर (!(bgx_map & (1 << bgx)))
			जारी;
		lmac_cnt = bgx_get_lmac_count(nic->node, bgx);
		क्रम (lmac = 0; lmac < lmac_cnt; lmac++)
			nic->vf_lmac_map[next_bgx_lmac++] =
						NIC_SET_VF_LMAC_MAP(bgx, lmac);
		nic->num_vf_en += lmac_cnt;

		/* Program LMAC credits */
		lmac_credit = (1ull << 1); /* channel credit enable */
		lmac_credit |= (0x1ff << 2); /* Max outstanding pkt count */
		/* 48KB BGX Tx buffer size, each unit is of size 16bytes */
		lmac_credit |= (((((48 * 1024) / lmac_cnt) -
				NIC_HW_MAX_FRS) / 16) << 12);
		lmac = bgx * MAX_LMAC_PER_BGX;
		क्रम (; lmac < lmac_cnt + (bgx * MAX_LMAC_PER_BGX); lmac++)
			nic_reg_ग_लिखो(nic,
				      NIC_PF_LMAC_0_7_CREDIT + (lmac * 8),
				      lmac_credit);

		/* On CN81XX there are only 8 VFs but max possible no of
		 * पूर्णांकerfaces are 9.
		 */
		अगर (nic->num_vf_en >= pci_sriov_get_totalvfs(nic->pdev)) अणु
			nic->num_vf_en = pci_sriov_get_totalvfs(nic->pdev);
			अवरोध;
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम nic_get_hw_info(काष्ठा nicpf *nic)
अणु
	u16 sdevid;
	काष्ठा hw_info *hw = nic->hw;

	pci_पढ़ो_config_word(nic->pdev, PCI_SUBSYSTEM_ID, &sdevid);

	चयन (sdevid) अणु
	हाल PCI_SUBSYS_DEVID_88XX_NIC_PF:
		hw->bgx_cnt = MAX_BGX_PER_CN88XX;
		hw->chans_per_lmac = 16;
		hw->chans_per_bgx = 128;
		hw->cpi_cnt = 2048;
		hw->rssi_cnt = 4096;
		hw->rss_ind_tbl_size = NIC_MAX_RSS_IDR_TBL_SIZE;
		hw->tl3_cnt = 256;
		hw->tl2_cnt = 64;
		hw->tl1_cnt = 2;
		hw->tl1_per_bgx = true;
		अवरोध;
	हाल PCI_SUBSYS_DEVID_81XX_NIC_PF:
		hw->bgx_cnt = MAX_BGX_PER_CN81XX;
		hw->chans_per_lmac = 8;
		hw->chans_per_bgx = 32;
		hw->chans_per_rgx = 8;
		hw->chans_per_lbk = 24;
		hw->cpi_cnt = 512;
		hw->rssi_cnt = 256;
		hw->rss_ind_tbl_size = 32; /* Max RSSI / Max पूर्णांकerfaces */
		hw->tl3_cnt = 64;
		hw->tl2_cnt = 16;
		hw->tl1_cnt = 10;
		hw->tl1_per_bgx = false;
		अवरोध;
	हाल PCI_SUBSYS_DEVID_83XX_NIC_PF:
		hw->bgx_cnt = MAX_BGX_PER_CN83XX;
		hw->chans_per_lmac = 8;
		hw->chans_per_bgx = 32;
		hw->chans_per_lbk = 64;
		hw->cpi_cnt = 2048;
		hw->rssi_cnt = 1024;
		hw->rss_ind_tbl_size = 64; /* Max RSSI / Max पूर्णांकerfaces */
		hw->tl3_cnt = 256;
		hw->tl2_cnt = 64;
		hw->tl1_cnt = 18;
		hw->tl1_per_bgx = false;
		अवरोध;
	पूर्ण
	hw->tl4_cnt = MAX_QUEUES_PER_QSET * pci_sriov_get_totalvfs(nic->pdev);
पूर्ण

#घोषणा BGX0_BLOCK 8
#घोषणा BGX1_BLOCK 9

अटल व्योम nic_init_hw(काष्ठा nicpf *nic)
अणु
	पूर्णांक i;
	u64 cqm_cfg;

	/* Enable NIC HW block */
	nic_reg_ग_लिखो(nic, NIC_PF_CFG, 0x3);

	/* Enable backpressure */
	nic_reg_ग_लिखो(nic, NIC_PF_BP_CFG, (1ULL << 6) | 0x03);

	/* TNS and TNS bypass modes are present only on 88xx
	 * Also offset of this CSR has changed in 81xx and 83xx.
	 */
	अगर (nic->pdev->subप्रणाली_device == PCI_SUBSYS_DEVID_88XX_NIC_PF) अणु
		/* Disable TNS mode on both पूर्णांकerfaces */
		nic_reg_ग_लिखो(nic, NIC_PF_INTF_0_1_SEND_CFG,
			      (NIC_TNS_BYPASS_MODE << 7) |
			      BGX0_BLOCK | (1ULL << 16));
		nic_reg_ग_लिखो(nic, NIC_PF_INTF_0_1_SEND_CFG | (1 << 8),
			      (NIC_TNS_BYPASS_MODE << 7) |
			      BGX1_BLOCK | (1ULL << 16));
	पूर्ण अन्यथा अणु
		/* Configure बारtamp generation समयout to 10us */
		क्रम (i = 0; i < nic->hw->bgx_cnt; i++)
			nic_reg_ग_लिखो(nic, NIC_PF_INTFX_SEND_CFG | (i << 3),
				      (1ULL << 16));
	पूर्ण

	nic_reg_ग_लिखो(nic, NIC_PF_INTF_0_1_BP_CFG,
		      (1ULL << 63) | BGX0_BLOCK);
	nic_reg_ग_लिखो(nic, NIC_PF_INTF_0_1_BP_CFG + (1 << 8),
		      (1ULL << 63) | BGX1_BLOCK);

	/* PKIND configuration */
	nic->pkind.minlen = 0;
	nic->pkind.maxlen = NIC_HW_MAX_FRS + VLAN_ETH_HLEN + ETH_FCS_LEN + 4;
	nic->pkind.lenerr_en = 1;
	nic->pkind.rx_hdr = 0;
	nic->pkind.hdr_sl = 0;

	क्रम (i = 0; i < NIC_MAX_PKIND; i++)
		nic_reg_ग_लिखो(nic, NIC_PF_PKIND_0_15_CFG | (i << 3),
			      *(u64 *)&nic->pkind);

	nic_set_tx_pkt_pad(nic, NIC_HW_MIN_FRS);

	/* Timer config */
	nic_reg_ग_लिखो(nic, NIC_PF_INTR_TIMER_CFG, NICPF_CLK_PER_INT_TICK);

	/* Enable VLAN ethertype matching and stripping */
	nic_reg_ग_लिखो(nic, NIC_PF_RX_ETYPE_0_7,
		      (2 << 19) | (ETYPE_ALG_VLAN_STRIP << 16) | ETH_P_8021Q);

	/* Check अगर HW expected value is higher (could be in future chips) */
	cqm_cfg = nic_reg_पढ़ो(nic, NIC_PF_CQM_CFG);
	अगर (cqm_cfg < NICPF_CQM_MIN_DROP_LEVEL)
		nic_reg_ग_लिखो(nic, NIC_PF_CQM_CFG, NICPF_CQM_MIN_DROP_LEVEL);
पूर्ण

/* Channel parse index configuration */
अटल व्योम nic_config_cpi(काष्ठा nicpf *nic, काष्ठा cpi_cfg_msg *cfg)
अणु
	काष्ठा hw_info *hw = nic->hw;
	u32 vnic, bgx, lmac, chan;
	u32 padd, cpi_count = 0;
	u64 cpi_base, cpi, rssi_base, rssi;
	u8  qset, rq_idx = 0;

	vnic = cfg->vf_id;
	bgx = NIC_GET_BGX_FROM_VF_LMAC_MAP(nic->vf_lmac_map[vnic]);
	lmac = NIC_GET_LMAC_FROM_VF_LMAC_MAP(nic->vf_lmac_map[vnic]);

	chan = (lmac * hw->chans_per_lmac) + (bgx * hw->chans_per_bgx);
	cpi_base = vnic * NIC_MAX_CPI_PER_LMAC;
	rssi_base = vnic * hw->rss_ind_tbl_size;

	/* Rx channel configuration */
	nic_reg_ग_लिखो(nic, NIC_PF_CHAN_0_255_RX_BP_CFG | (chan << 3),
		      (1ull << 63) | (vnic << 0));
	nic_reg_ग_लिखो(nic, NIC_PF_CHAN_0_255_RX_CFG | (chan << 3),
		      ((u64)cfg->cpi_alg << 62) | (cpi_base << 48));

	अगर (cfg->cpi_alg == CPI_ALG_NONE)
		cpi_count = 1;
	अन्यथा अगर (cfg->cpi_alg == CPI_ALG_VLAN) /* 3 bits of PCP */
		cpi_count = 8;
	अन्यथा अगर (cfg->cpi_alg == CPI_ALG_VLAN16) /* 3 bits PCP + DEI */
		cpi_count = 16;
	अन्यथा अगर (cfg->cpi_alg == CPI_ALG_DIFF) /* 6bits DSCP */
		cpi_count = NIC_MAX_CPI_PER_LMAC;

	/* RSS Qset, Qidx mapping */
	qset = cfg->vf_id;
	rssi = rssi_base;
	क्रम (; rssi < (rssi_base + cfg->rq_cnt); rssi++) अणु
		nic_reg_ग_लिखो(nic, NIC_PF_RSSI_0_4097_RQ | (rssi << 3),
			      (qset << 3) | rq_idx);
		rq_idx++;
	पूर्ण

	rssi = 0;
	cpi = cpi_base;
	क्रम (; cpi < (cpi_base + cpi_count); cpi++) अणु
		/* Determine port to channel adder */
		अगर (cfg->cpi_alg != CPI_ALG_DIFF)
			padd = cpi % cpi_count;
		अन्यथा
			padd = cpi % 8; /* 3 bits CS out of 6bits DSCP */

		/* Leave RSS_SIZE as '0' to disable RSS */
		अगर (pass1_silicon(nic->pdev)) अणु
			nic_reg_ग_लिखो(nic, NIC_PF_CPI_0_2047_CFG | (cpi << 3),
				      (vnic << 24) | (padd << 16) |
				      (rssi_base + rssi));
		पूर्ण अन्यथा अणु
			/* Set MPI_ALG to '0' to disable MCAM parsing */
			nic_reg_ग_लिखो(nic, NIC_PF_CPI_0_2047_CFG | (cpi << 3),
				      (padd << 16));
			/* MPI index is same as CPI अगर MPI_ALG is not enabled */
			nic_reg_ग_लिखो(nic, NIC_PF_MPI_0_2047_CFG | (cpi << 3),
				      (vnic << 24) | (rssi_base + rssi));
		पूर्ण

		अगर ((rssi + 1) >= cfg->rq_cnt)
			जारी;

		अगर (cfg->cpi_alg == CPI_ALG_VLAN)
			rssi++;
		अन्यथा अगर (cfg->cpi_alg == CPI_ALG_VLAN16)
			rssi = ((cpi - cpi_base) & 0xe) >> 1;
		अन्यथा अगर (cfg->cpi_alg == CPI_ALG_DIFF)
			rssi = ((cpi - cpi_base) & 0x38) >> 3;
	पूर्ण
	nic->cpi_base[cfg->vf_id] = cpi_base;
	nic->rssi_base[cfg->vf_id] = rssi_base;
पूर्ण

/* Responsds to VF with its RSS indirection table size */
अटल व्योम nic_send_rss_size(काष्ठा nicpf *nic, पूर्णांक vf)
अणु
	जोड़ nic_mbx mbx = अणुपूर्ण;

	mbx.rss_size.msg = NIC_MBOX_MSG_RSS_SIZE;
	mbx.rss_size.ind_tbl_size = nic->hw->rss_ind_tbl_size;
	nic_send_msg_to_vf(nic, vf, &mbx);
पूर्ण

/* Receive side scaling configuration
 * configure:
 * - RSS index
 * - indir table i.e hash::RQ mapping
 * - no of hash bits to consider
 */
अटल व्योम nic_config_rss(काष्ठा nicpf *nic, काष्ठा rss_cfg_msg *cfg)
अणु
	u8  qset, idx = 0;
	u64 cpi_cfg, cpi_base, rssi_base, rssi;
	u64 idx_addr;

	rssi_base = nic->rssi_base[cfg->vf_id] + cfg->tbl_offset;

	rssi = rssi_base;

	क्रम (; rssi < (rssi_base + cfg->tbl_len); rssi++) अणु
		u8 svf = cfg->ind_tbl[idx] >> 3;

		अगर (svf)
			qset = nic->vf_sqs[cfg->vf_id][svf - 1];
		अन्यथा
			qset = cfg->vf_id;
		nic_reg_ग_लिखो(nic, NIC_PF_RSSI_0_4097_RQ | (rssi << 3),
			      (qset << 3) | (cfg->ind_tbl[idx] & 0x7));
		idx++;
	पूर्ण

	cpi_base = nic->cpi_base[cfg->vf_id];
	अगर (pass1_silicon(nic->pdev))
		idx_addr = NIC_PF_CPI_0_2047_CFG;
	अन्यथा
		idx_addr = NIC_PF_MPI_0_2047_CFG;
	cpi_cfg = nic_reg_पढ़ो(nic, idx_addr | (cpi_base << 3));
	cpi_cfg &= ~(0xFULL << 20);
	cpi_cfg |= (cfg->hash_bits << 20);
	nic_reg_ग_लिखो(nic, idx_addr | (cpi_base << 3), cpi_cfg);
पूर्ण

/* 4 level transmit side scheduler configutation
 * क्रम TNS bypass mode
 *
 * Sample configuration क्रम SQ0 on 88xx
 * VNIC0-SQ0 -> TL4(0)   -> TL3[0]   -> TL2[0]  -> TL1[0] -> BGX0
 * VNIC1-SQ0 -> TL4(8)   -> TL3[2]   -> TL2[0]  -> TL1[0] -> BGX0
 * VNIC2-SQ0 -> TL4(16)  -> TL3[4]   -> TL2[1]  -> TL1[0] -> BGX0
 * VNIC3-SQ0 -> TL4(24)  -> TL3[6]   -> TL2[1]  -> TL1[0] -> BGX0
 * VNIC4-SQ0 -> TL4(512) -> TL3[128] -> TL2[32] -> TL1[1] -> BGX1
 * VNIC5-SQ0 -> TL4(520) -> TL3[130] -> TL2[32] -> TL1[1] -> BGX1
 * VNIC6-SQ0 -> TL4(528) -> TL3[132] -> TL2[33] -> TL1[1] -> BGX1
 * VNIC7-SQ0 -> TL4(536) -> TL3[134] -> TL2[33] -> TL1[1] -> BGX1
 */
अटल व्योम nic_tx_channel_cfg(काष्ठा nicpf *nic, u8 vnic,
			       काष्ठा sq_cfg_msg *sq)
अणु
	काष्ठा hw_info *hw = nic->hw;
	u32 bgx, lmac, chan;
	u32 tl2, tl3, tl4;
	u32 rr_quantum;
	u8 sq_idx = sq->sq_num;
	u8 pqs_vnic;
	पूर्णांक svf;

	अगर (sq->sqs_mode)
		pqs_vnic = nic->pqs_vf[vnic];
	अन्यथा
		pqs_vnic = vnic;

	bgx = NIC_GET_BGX_FROM_VF_LMAC_MAP(nic->vf_lmac_map[pqs_vnic]);
	lmac = NIC_GET_LMAC_FROM_VF_LMAC_MAP(nic->vf_lmac_map[pqs_vnic]);

	/* 24 bytes क्रम FCS, IPG and preamble */
	rr_quantum = ((NIC_HW_MAX_FRS + 24) / 4);

	/* For 88xx 0-511 TL4 transmits via BGX0 and
	 * 512-1023 TL4s transmit via BGX1.
	 */
	अगर (hw->tl1_per_bgx) अणु
		tl4 = bgx * (hw->tl4_cnt / hw->bgx_cnt);
		अगर (!sq->sqs_mode) अणु
			tl4 += (lmac * MAX_QUEUES_PER_QSET);
		पूर्ण अन्यथा अणु
			क्रम (svf = 0; svf < MAX_SQS_PER_VF; svf++) अणु
				अगर (nic->vf_sqs[pqs_vnic][svf] == vnic)
					अवरोध;
			पूर्ण
			tl4 += (MAX_LMAC_PER_BGX * MAX_QUEUES_PER_QSET);
			tl4 += (lmac * MAX_QUEUES_PER_QSET * MAX_SQS_PER_VF);
			tl4 += (svf * MAX_QUEUES_PER_QSET);
		पूर्ण
	पूर्ण अन्यथा अणु
		tl4 = (vnic * MAX_QUEUES_PER_QSET);
	पूर्ण
	tl4 += sq_idx;

	tl3 = tl4 / (hw->tl4_cnt / hw->tl3_cnt);
	nic_reg_ग_लिखो(nic, NIC_PF_QSET_0_127_SQ_0_7_CFG2 |
		      ((u64)vnic << NIC_QS_ID_SHIFT) |
		      ((u32)sq_idx << NIC_Q_NUM_SHIFT), tl4);
	nic_reg_ग_लिखो(nic, NIC_PF_TL4_0_1023_CFG | (tl4 << 3),
		      ((u64)vnic << 27) | ((u32)sq_idx << 24) | rr_quantum);

	nic_reg_ग_लिखो(nic, NIC_PF_TL3_0_255_CFG | (tl3 << 3), rr_quantum);

	/* On 88xx 0-127 channels are क्रम BGX0 and
	 * 127-255 channels क्रम BGX1.
	 *
	 * On 81xx/83xx TL3_CHAN reg should be configured with channel
	 * within LMAC i.e 0-7 and not the actual channel number like on 88xx
	 */
	chan = (lmac * hw->chans_per_lmac) + (bgx * hw->chans_per_bgx);
	अगर (hw->tl1_per_bgx)
		nic_reg_ग_लिखो(nic, NIC_PF_TL3_0_255_CHAN | (tl3 << 3), chan);
	अन्यथा
		nic_reg_ग_लिखो(nic, NIC_PF_TL3_0_255_CHAN | (tl3 << 3), 0);

	/* Enable backpressure on the channel */
	nic_reg_ग_लिखो(nic, NIC_PF_CHAN_0_255_TX_CFG | (chan << 3), 1);

	tl2 = tl3 >> 2;
	nic_reg_ग_लिखो(nic, NIC_PF_TL3A_0_63_CFG | (tl2 << 3), tl2);
	nic_reg_ग_लिखो(nic, NIC_PF_TL2_0_63_CFG | (tl2 << 3), rr_quantum);
	/* No priorities as of now */
	nic_reg_ग_लिखो(nic, NIC_PF_TL2_0_63_PRI | (tl2 << 3), 0x00);

	/* Unlike 88xx where TL2s 0-31 transmits to TL1 '0' and rest to TL1 '1'
	 * on 81xx/83xx TL2 needs to be configured to transmit to one of the
	 * possible LMACs.
	 *
	 * This रेजिस्टर करोesn't exist on 88xx.
	 */
	अगर (!hw->tl1_per_bgx)
		nic_reg_ग_लिखो(nic, NIC_PF_TL2_LMAC | (tl2 << 3),
			      lmac + (bgx * MAX_LMAC_PER_BGX));
पूर्ण

/* Send primary nicvf poपूर्णांकer to secondary QS's VF */
अटल व्योम nic_send_pnicvf(काष्ठा nicpf *nic, पूर्णांक sqs)
अणु
	जोड़ nic_mbx mbx = अणुपूर्ण;

	mbx.nicvf.msg = NIC_MBOX_MSG_PNICVF_PTR;
	mbx.nicvf.nicvf = nic->nicvf[nic->pqs_vf[sqs]];
	nic_send_msg_to_vf(nic, sqs, &mbx);
पूर्ण

/* Send SQS's nicvf pointer to primary QS's VF */
अटल व्योम nic_send_snicvf(काष्ठा nicpf *nic, काष्ठा nicvf_ptr *nicvf)
अणु
	जोड़ nic_mbx mbx = अणुपूर्ण;
	पूर्णांक sqs_id = nic->vf_sqs[nicvf->vf_id][nicvf->sqs_id];

	mbx.nicvf.msg = NIC_MBOX_MSG_SNICVF_PTR;
	mbx.nicvf.sqs_id = nicvf->sqs_id;
	mbx.nicvf.nicvf = nic->nicvf[sqs_id];
	nic_send_msg_to_vf(nic, nicvf->vf_id, &mbx);
पूर्ण

/* Find next available Qset that can be asचिन्हित as a
 * secondary Qset to a VF.
 */
अटल पूर्णांक nic_nxt_avail_sqs(काष्ठा nicpf *nic)
अणु
	पूर्णांक sqs;

	क्रम (sqs = 0; sqs < nic->num_sqs_en; sqs++) अणु
		अगर (!nic->sqs_used[sqs])
			nic->sqs_used[sqs] = true;
		अन्यथा
			जारी;
		वापस sqs + nic->num_vf_en;
	पूर्ण
	वापस -1;
पूर्ण

/* Allocate additional Qsets क्रम requested VF */
अटल व्योम nic_alloc_sqs(काष्ठा nicpf *nic, काष्ठा sqs_alloc *sqs)
अणु
	जोड़ nic_mbx mbx = अणुपूर्ण;
	पूर्णांक idx, alloc_qs = 0;
	पूर्णांक sqs_id;

	अगर (!nic->num_sqs_en)
		जाओ send_mbox;

	क्रम (idx = 0; idx < sqs->qs_count; idx++) अणु
		sqs_id = nic_nxt_avail_sqs(nic);
		अगर (sqs_id < 0)
			अवरोध;
		nic->vf_sqs[sqs->vf_id][idx] = sqs_id;
		nic->pqs_vf[sqs_id] = sqs->vf_id;
		alloc_qs++;
	पूर्ण

send_mbox:
	mbx.sqs_alloc.msg = NIC_MBOX_MSG_ALLOC_SQS;
	mbx.sqs_alloc.vf_id = sqs->vf_id;
	mbx.sqs_alloc.qs_count = alloc_qs;
	nic_send_msg_to_vf(nic, sqs->vf_id, &mbx);
पूर्ण

अटल पूर्णांक nic_config_loopback(काष्ठा nicpf *nic, काष्ठा set_loopback *lbk)
अणु
	पूर्णांक bgx_idx, lmac_idx;

	अगर (lbk->vf_id >= nic->num_vf_en)
		वापस -1;

	bgx_idx = NIC_GET_BGX_FROM_VF_LMAC_MAP(nic->vf_lmac_map[lbk->vf_id]);
	lmac_idx = NIC_GET_LMAC_FROM_VF_LMAC_MAP(nic->vf_lmac_map[lbk->vf_id]);

	bgx_lmac_पूर्णांकernal_loopback(nic->node, bgx_idx, lmac_idx, lbk->enable);

	/* Enable moving average calculation.
	 * Keep the LVL/AVG delay to HW enक्रमced minimum so that, not too many
	 * packets sneek in between average calculations.
	 */
	nic_reg_ग_लिखो(nic, NIC_PF_CQ_AVG_CFG,
		      (BIT_ULL(20) | 0x2ull << 14 | 0x1));
	nic_reg_ग_लिखो(nic, NIC_PF_RRM_AVG_CFG,
		      (BIT_ULL(20) | 0x3ull << 14 | 0x1));

	वापस 0;
पूर्ण

/* Reset statistics counters */
अटल पूर्णांक nic_reset_stat_counters(काष्ठा nicpf *nic,
				   पूर्णांक vf, काष्ठा reset_stat_cfg *cfg)
अणु
	पूर्णांक i, stat, qnum;
	u64 reg_addr;

	क्रम (i = 0; i < RX_STATS_ENUM_LAST; i++) अणु
		अगर (cfg->rx_stat_mask & BIT(i)) अणु
			reg_addr = NIC_PF_VNIC_0_127_RX_STAT_0_13 |
				   (vf << NIC_QS_ID_SHIFT) |
				   (i << 3);
			nic_reg_ग_लिखो(nic, reg_addr, 0);
		पूर्ण
	पूर्ण

	क्रम (i = 0; i < TX_STATS_ENUM_LAST; i++) अणु
		अगर (cfg->tx_stat_mask & BIT(i)) अणु
			reg_addr = NIC_PF_VNIC_0_127_TX_STAT_0_4 |
				   (vf << NIC_QS_ID_SHIFT) |
				   (i << 3);
			nic_reg_ग_लिखो(nic, reg_addr, 0);
		पूर्ण
	पूर्ण

	क्रम (i = 0; i <= 15; i++) अणु
		qnum = i >> 1;
		stat = i & 1 ? 1 : 0;
		reg_addr = (vf << NIC_QS_ID_SHIFT) |
			   (qnum << NIC_Q_NUM_SHIFT) | (stat << 3);
		अगर (cfg->rq_stat_mask & BIT(i)) अणु
			reg_addr |= NIC_PF_QSET_0_127_RQ_0_7_STAT_0_1;
			nic_reg_ग_लिखो(nic, reg_addr, 0);
		पूर्ण
		अगर (cfg->sq_stat_mask & BIT(i)) अणु
			reg_addr |= NIC_PF_QSET_0_127_SQ_0_7_STAT_0_1;
			nic_reg_ग_लिखो(nic, reg_addr, 0);
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम nic_enable_tunnel_parsing(काष्ठा nicpf *nic, पूर्णांक vf)
अणु
	u64 prot_def = (IPV6_PROT << 32) | (IPV4_PROT << 16) | ET_PROT;
	u64 vxlan_prot_def = (IPV6_PROT_DEF << 32) |
			      (IPV4_PROT_DEF) << 16 | ET_PROT_DEF;

	/* Configure tunnel parsing parameters */
	nic_reg_ग_लिखो(nic, NIC_PF_RX_GENEVE_DEF,
		      (1ULL << 63 | UDP_GENEVE_PORT_NUM));
	nic_reg_ग_लिखो(nic, NIC_PF_RX_GENEVE_PROT_DEF,
		      ((7ULL << 61) | prot_def));
	nic_reg_ग_लिखो(nic, NIC_PF_RX_NVGRE_PROT_DEF,
		      ((7ULL << 61) | prot_def));
	nic_reg_ग_लिखो(nic, NIC_PF_RX_VXLAN_DEF_0_1,
		      ((1ULL << 63) | UDP_VXLAN_PORT_NUM));
	nic_reg_ग_लिखो(nic, NIC_PF_RX_VXLAN_PROT_DEF,
		      ((0xfULL << 60) | vxlan_prot_def));
पूर्ण

अटल व्योम nic_enable_vf(काष्ठा nicpf *nic, पूर्णांक vf, bool enable)
अणु
	पूर्णांक bgx, lmac;

	nic->vf_enabled[vf] = enable;

	अगर (vf >= nic->num_vf_en)
		वापस;

	bgx = NIC_GET_BGX_FROM_VF_LMAC_MAP(nic->vf_lmac_map[vf]);
	lmac = NIC_GET_LMAC_FROM_VF_LMAC_MAP(nic->vf_lmac_map[vf]);

	bgx_lmac_rx_tx_enable(nic->node, bgx, lmac, enable);
पूर्ण

अटल व्योम nic_छोड़ो_frame(काष्ठा nicpf *nic, पूर्णांक vf, काष्ठा pfc *cfg)
अणु
	पूर्णांक bgx, lmac;
	काष्ठा pfc pfc;
	जोड़ nic_mbx mbx = अणुपूर्ण;

	अगर (vf >= nic->num_vf_en)
		वापस;
	bgx = NIC_GET_BGX_FROM_VF_LMAC_MAP(nic->vf_lmac_map[vf]);
	lmac = NIC_GET_LMAC_FROM_VF_LMAC_MAP(nic->vf_lmac_map[vf]);

	अगर (cfg->get) अणु
		bgx_lmac_get_pfc(nic->node, bgx, lmac, &pfc);
		mbx.pfc.msg = NIC_MBOX_MSG_PFC;
		mbx.pfc.स्वतःneg = pfc.स्वतःneg;
		mbx.pfc.fc_rx = pfc.fc_rx;
		mbx.pfc.fc_tx = pfc.fc_tx;
		nic_send_msg_to_vf(nic, vf, &mbx);
	पूर्ण अन्यथा अणु
		bgx_lmac_set_pfc(nic->node, bgx, lmac, cfg);
		nic_mbx_send_ack(nic, vf);
	पूर्ण
पूर्ण

/* Enable or disable HW बारtamping by BGX क्रम pkts received on a LMAC */
अटल व्योम nic_config_बारtamp(काष्ठा nicpf *nic, पूर्णांक vf, काष्ठा set_ptp *ptp)
अणु
	काष्ठा pkind_cfg *pkind;
	u8 lmac, bgx_idx;
	u64 pkind_val, pkind_idx;

	अगर (vf >= nic->num_vf_en)
		वापस;

	bgx_idx = NIC_GET_BGX_FROM_VF_LMAC_MAP(nic->vf_lmac_map[vf]);
	lmac = NIC_GET_LMAC_FROM_VF_LMAC_MAP(nic->vf_lmac_map[vf]);

	pkind_idx = lmac + bgx_idx * MAX_LMAC_PER_BGX;
	pkind_val = nic_reg_पढ़ो(nic, NIC_PF_PKIND_0_15_CFG | (pkind_idx << 3));
	pkind = (काष्ठा pkind_cfg *)&pkind_val;

	अगर (ptp->enable && !pkind->hdr_sl) अणु
		/* Skiplen to exclude 8byte बारtamp जबतक parsing pkt
		 * If not configured, will result in L2 errors.
		 */
		pkind->hdr_sl = 4;
		/* Adjust max packet length allowed */
		pkind->maxlen += (pkind->hdr_sl * 2);
		bgx_config_बारtamping(nic->node, bgx_idx, lmac, true);
		nic_reg_ग_लिखो(nic, NIC_PF_RX_ETYPE_0_7 | (1 << 3),
			      (ETYPE_ALG_ENDPARSE << 16) | ETH_P_1588);
	पूर्ण अन्यथा अगर (!ptp->enable && pkind->hdr_sl) अणु
		pkind->maxlen -= (pkind->hdr_sl * 2);
		pkind->hdr_sl = 0;
		bgx_config_बारtamping(nic->node, bgx_idx, lmac, false);
		nic_reg_ग_लिखो(nic, NIC_PF_RX_ETYPE_0_7 | (1 << 3),
			      (ETYPE_ALG_SKIP << 16) | ETH_P_8021Q);
	पूर्ण

	nic_reg_ग_लिखो(nic, NIC_PF_PKIND_0_15_CFG | (pkind_idx << 3), pkind_val);
पूर्ण

/* Get BGX LMAC link status and update corresponding VF
 * अगर there is a change, valid only अगर पूर्णांकernal L2 चयन
 * is not present otherwise VF link is always treated as up
 */
अटल व्योम nic_link_status_get(काष्ठा nicpf *nic, u8 vf)
अणु
	जोड़ nic_mbx mbx = अणुपूर्ण;
	काष्ठा bgx_link_status link;
	u8 bgx, lmac;

	mbx.link_status.msg = NIC_MBOX_MSG_BGX_LINK_CHANGE;

	/* Get BGX, LMAC indices क्रम the VF */
	bgx = NIC_GET_BGX_FROM_VF_LMAC_MAP(nic->vf_lmac_map[vf]);
	lmac = NIC_GET_LMAC_FROM_VF_LMAC_MAP(nic->vf_lmac_map[vf]);

	/* Get पूर्णांकerface link status */
	bgx_get_lmac_link_state(nic->node, bgx, lmac, &link);

	/* Send a mbox message to VF with current link status */
	mbx.link_status.link_up = link.link_up;
	mbx.link_status.duplex = link.duplex;
	mbx.link_status.speed = link.speed;
	mbx.link_status.mac_type = link.mac_type;

	/* reply with link status */
	nic_send_msg_to_vf(nic, vf, &mbx);
पूर्ण

/* Interrupt handler to handle mailbox messages from VFs */
अटल व्योम nic_handle_mbx_पूर्णांकr(काष्ठा nicpf *nic, पूर्णांक vf)
अणु
	जोड़ nic_mbx mbx = अणुपूर्ण;
	u64 *mbx_data;
	u64 mbx_addr;
	u64 reg_addr;
	u64 cfg;
	पूर्णांक bgx, lmac;
	पूर्णांक i;
	पूर्णांक ret = 0;

	mbx_addr = nic_get_mbx_addr(vf);
	mbx_data = (u64 *)&mbx;

	क्रम (i = 0; i < NIC_PF_VF_MAILBOX_SIZE; i++) अणु
		*mbx_data = nic_reg_पढ़ो(nic, mbx_addr);
		mbx_data++;
		mbx_addr += माप(u64);
	पूर्ण

	dev_dbg(&nic->pdev->dev, "%s: Mailbox msg 0x%02x from VF%d\n",
		__func__, mbx.msg.msg, vf);
	चयन (mbx.msg.msg) अणु
	हाल NIC_MBOX_MSG_READY:
		nic_mbx_send_पढ़ोy(nic, vf);
		वापस;
	हाल NIC_MBOX_MSG_QS_CFG:
		reg_addr = NIC_PF_QSET_0_127_CFG |
			   (mbx.qs.num << NIC_QS_ID_SHIFT);
		cfg = mbx.qs.cfg;
		/* Check अगर its a secondary Qset */
		अगर (vf >= nic->num_vf_en) अणु
			cfg = cfg & (~0x7FULL);
			/* Assign this Qset to primary Qset's VF */
			cfg |= nic->pqs_vf[vf];
		पूर्ण
		nic_reg_ग_लिखो(nic, reg_addr, cfg);
		अवरोध;
	हाल NIC_MBOX_MSG_RQ_CFG:
		reg_addr = NIC_PF_QSET_0_127_RQ_0_7_CFG |
			   (mbx.rq.qs_num << NIC_QS_ID_SHIFT) |
			   (mbx.rq.rq_num << NIC_Q_NUM_SHIFT);
		nic_reg_ग_लिखो(nic, reg_addr, mbx.rq.cfg);
		/* Enable CQE_RX2_S extension in CQE_RX descriptor.
		 * This माला_लो appended by शेष on 81xx/83xx chips,
		 * क्रम consistency enabling the same on 88xx pass2
		 * where this is पूर्णांकroduced.
		 */
		अगर (pass2_silicon(nic->pdev))
			nic_reg_ग_लिखो(nic, NIC_PF_RX_CFG, 0x01);
		अगर (!pass1_silicon(nic->pdev))
			nic_enable_tunnel_parsing(nic, vf);
		अवरोध;
	हाल NIC_MBOX_MSG_RQ_BP_CFG:
		reg_addr = NIC_PF_QSET_0_127_RQ_0_7_BP_CFG |
			   (mbx.rq.qs_num << NIC_QS_ID_SHIFT) |
			   (mbx.rq.rq_num << NIC_Q_NUM_SHIFT);
		nic_reg_ग_लिखो(nic, reg_addr, mbx.rq.cfg);
		अवरोध;
	हाल NIC_MBOX_MSG_RQ_SW_SYNC:
		ret = nic_rcv_queue_sw_sync(nic);
		अवरोध;
	हाल NIC_MBOX_MSG_RQ_DROP_CFG:
		reg_addr = NIC_PF_QSET_0_127_RQ_0_7_DROP_CFG |
			   (mbx.rq.qs_num << NIC_QS_ID_SHIFT) |
			   (mbx.rq.rq_num << NIC_Q_NUM_SHIFT);
		nic_reg_ग_लिखो(nic, reg_addr, mbx.rq.cfg);
		अवरोध;
	हाल NIC_MBOX_MSG_SQ_CFG:
		reg_addr = NIC_PF_QSET_0_127_SQ_0_7_CFG |
			   (mbx.sq.qs_num << NIC_QS_ID_SHIFT) |
			   (mbx.sq.sq_num << NIC_Q_NUM_SHIFT);
		nic_reg_ग_लिखो(nic, reg_addr, mbx.sq.cfg);
		nic_tx_channel_cfg(nic, mbx.qs.num, &mbx.sq);
		अवरोध;
	हाल NIC_MBOX_MSG_SET_MAC:
		अगर (vf >= nic->num_vf_en) अणु
			ret = -1; /* NACK */
			अवरोध;
		पूर्ण
		lmac = mbx.mac.vf_id;
		bgx = NIC_GET_BGX_FROM_VF_LMAC_MAP(nic->vf_lmac_map[lmac]);
		lmac = NIC_GET_LMAC_FROM_VF_LMAC_MAP(nic->vf_lmac_map[lmac]);
		bgx_set_lmac_mac(nic->node, bgx, lmac, mbx.mac.mac_addr);
		अवरोध;
	हाल NIC_MBOX_MSG_SET_MAX_FRS:
		ret = nic_update_hw_frs(nic, mbx.frs.max_frs,
					mbx.frs.vf_id);
		अवरोध;
	हाल NIC_MBOX_MSG_CPI_CFG:
		nic_config_cpi(nic, &mbx.cpi_cfg);
		अवरोध;
	हाल NIC_MBOX_MSG_RSS_SIZE:
		nic_send_rss_size(nic, vf);
		वापस;
	हाल NIC_MBOX_MSG_RSS_CFG:
	हाल NIC_MBOX_MSG_RSS_CFG_CONT:
		nic_config_rss(nic, &mbx.rss_cfg);
		अवरोध;
	हाल NIC_MBOX_MSG_CFG_DONE:
		/* Last message of VF config msg sequence */
		nic_enable_vf(nic, vf, true);
		अवरोध;
	हाल NIC_MBOX_MSG_SHUTDOWN:
		/* First msg in VF tearकरोwn sequence */
		अगर (vf >= nic->num_vf_en)
			nic->sqs_used[vf - nic->num_vf_en] = false;
		nic->pqs_vf[vf] = 0;
		nic_enable_vf(nic, vf, false);
		अवरोध;
	हाल NIC_MBOX_MSG_ALLOC_SQS:
		nic_alloc_sqs(nic, &mbx.sqs_alloc);
		वापस;
	हाल NIC_MBOX_MSG_NICVF_PTR:
		nic->nicvf[vf] = mbx.nicvf.nicvf;
		अवरोध;
	हाल NIC_MBOX_MSG_PNICVF_PTR:
		nic_send_pnicvf(nic, vf);
		वापस;
	हाल NIC_MBOX_MSG_SNICVF_PTR:
		nic_send_snicvf(nic, &mbx.nicvf);
		वापस;
	हाल NIC_MBOX_MSG_BGX_STATS:
		nic_get_bgx_stats(nic, &mbx.bgx_stats);
		वापस;
	हाल NIC_MBOX_MSG_LOOPBACK:
		ret = nic_config_loopback(nic, &mbx.lbk);
		अवरोध;
	हाल NIC_MBOX_MSG_RESET_STAT_COUNTER:
		ret = nic_reset_stat_counters(nic, vf, &mbx.reset_stat);
		अवरोध;
	हाल NIC_MBOX_MSG_PFC:
		nic_छोड़ो_frame(nic, vf, &mbx.pfc);
		वापस;
	हाल NIC_MBOX_MSG_PTP_CFG:
		nic_config_बारtamp(nic, vf, &mbx.ptp);
		अवरोध;
	हाल NIC_MBOX_MSG_RESET_XCAST:
		अगर (vf >= nic->num_vf_en) अणु
			ret = -1; /* NACK */
			अवरोध;
		पूर्ण
		bgx = NIC_GET_BGX_FROM_VF_LMAC_MAP(nic->vf_lmac_map[vf]);
		lmac = NIC_GET_LMAC_FROM_VF_LMAC_MAP(nic->vf_lmac_map[vf]);
		bgx_reset_xcast_mode(nic->node, bgx, lmac,
				     vf < NIC_VF_PER_MBX_REG ? vf :
				     vf - NIC_VF_PER_MBX_REG);
		अवरोध;

	हाल NIC_MBOX_MSG_ADD_MCAST:
		अगर (vf >= nic->num_vf_en) अणु
			ret = -1; /* NACK */
			अवरोध;
		पूर्ण
		bgx = NIC_GET_BGX_FROM_VF_LMAC_MAP(nic->vf_lmac_map[vf]);
		lmac = NIC_GET_LMAC_FROM_VF_LMAC_MAP(nic->vf_lmac_map[vf]);
		bgx_set_dmac_cam_filter(nic->node, bgx, lmac,
					mbx.xcast.mac,
					vf < NIC_VF_PER_MBX_REG ? vf :
					vf - NIC_VF_PER_MBX_REG);
		अवरोध;

	हाल NIC_MBOX_MSG_SET_XCAST:
		अगर (vf >= nic->num_vf_en) अणु
			ret = -1; /* NACK */
			अवरोध;
		पूर्ण
		bgx = NIC_GET_BGX_FROM_VF_LMAC_MAP(nic->vf_lmac_map[vf]);
		lmac = NIC_GET_LMAC_FROM_VF_LMAC_MAP(nic->vf_lmac_map[vf]);
		bgx_set_xcast_mode(nic->node, bgx, lmac, mbx.xcast.mode);
		अवरोध;
	हाल NIC_MBOX_MSG_BGX_LINK_CHANGE:
		अगर (vf >= nic->num_vf_en) अणु
			ret = -1; /* NACK */
			अवरोध;
		पूर्ण
		nic_link_status_get(nic, vf);
		वापस;
	शेष:
		dev_err(&nic->pdev->dev,
			"Invalid msg from VF%d, msg 0x%x\n", vf, mbx.msg.msg);
		अवरोध;
	पूर्ण

	अगर (!ret) अणु
		nic_mbx_send_ack(nic, vf);
	पूर्ण अन्यथा अगर (mbx.msg.msg != NIC_MBOX_MSG_READY) अणु
		dev_err(&nic->pdev->dev, "NACK for MBOX 0x%02x from VF %d\n",
			mbx.msg.msg, vf);
		nic_mbx_send_nack(nic, vf);
	पूर्ण
पूर्ण

अटल irqवापस_t nic_mbx_पूर्णांकr_handler(पूर्णांक irq, व्योम *nic_irq)
अणु
	काष्ठा nicpf *nic = (काष्ठा nicpf *)nic_irq;
	पूर्णांक mbx;
	u64 पूर्णांकr;
	u8  vf;

	अगर (irq == pci_irq_vector(nic->pdev, NIC_PF_INTR_ID_MBOX0))
		mbx = 0;
	अन्यथा
		mbx = 1;

	पूर्णांकr = nic_reg_पढ़ो(nic, NIC_PF_MAILBOX_INT + (mbx << 3));
	dev_dbg(&nic->pdev->dev, "PF interrupt Mbox%d 0x%llx\n", mbx, पूर्णांकr);
	क्रम (vf = 0; vf < NIC_VF_PER_MBX_REG; vf++) अणु
		अगर (पूर्णांकr & (1ULL << vf)) अणु
			dev_dbg(&nic->pdev->dev, "Intr from VF %d\n",
				vf + (mbx * NIC_VF_PER_MBX_REG));

			nic_handle_mbx_पूर्णांकr(nic, vf +
					    (mbx * NIC_VF_PER_MBX_REG));
			nic_clear_mbx_पूर्णांकr(nic, vf, mbx);
		पूर्ण
	पूर्ण
	वापस IRQ_HANDLED;
पूर्ण

अटल व्योम nic_मुक्त_all_पूर्णांकerrupts(काष्ठा nicpf *nic)
अणु
	पूर्णांक irq;

	क्रम (irq = 0; irq < nic->num_vec; irq++) अणु
		अगर (nic->irq_allocated[irq])
			मुक्त_irq(pci_irq_vector(nic->pdev, irq), nic);
		nic->irq_allocated[irq] = false;
	पूर्ण
पूर्ण

अटल पूर्णांक nic_रेजिस्टर_पूर्णांकerrupts(काष्ठा nicpf *nic)
अणु
	पूर्णांक i, ret;
	nic->num_vec = pci_msix_vec_count(nic->pdev);

	/* Enable MSI-X */
	ret = pci_alloc_irq_vectors(nic->pdev, nic->num_vec, nic->num_vec,
				    PCI_IRQ_MSIX);
	अगर (ret < 0) अणु
		dev_err(&nic->pdev->dev,
			"Request for #%d msix vectors failed, returned %d\n",
			   nic->num_vec, ret);
		वापस 1;
	पूर्ण

	/* Register mailbox पूर्णांकerrupt handler */
	क्रम (i = NIC_PF_INTR_ID_MBOX0; i < nic->num_vec; i++) अणु
		प्र_लिखो(nic->irq_name[i],
			"NICPF Mbox%d", (i - NIC_PF_INTR_ID_MBOX0));

		ret = request_irq(pci_irq_vector(nic->pdev, i),
				  nic_mbx_पूर्णांकr_handler, 0,
				  nic->irq_name[i], nic);
		अगर (ret)
			जाओ fail;

		nic->irq_allocated[i] = true;
	पूर्ण

	/* Enable mailbox पूर्णांकerrupt */
	nic_enable_mbx_पूर्णांकr(nic);
	वापस 0;

fail:
	dev_err(&nic->pdev->dev, "Request irq failed\n");
	nic_मुक्त_all_पूर्णांकerrupts(nic);
	pci_मुक्त_irq_vectors(nic->pdev);
	nic->num_vec = 0;
	वापस ret;
पूर्ण

अटल व्योम nic_unरेजिस्टर_पूर्णांकerrupts(काष्ठा nicpf *nic)
अणु
	nic_मुक्त_all_पूर्णांकerrupts(nic);
	pci_मुक्त_irq_vectors(nic->pdev);
	nic->num_vec = 0;
पूर्ण

अटल पूर्णांक nic_num_sqs_en(काष्ठा nicpf *nic, पूर्णांक vf_en)
अणु
	पूर्णांक pos, sqs_per_vf = MAX_SQS_PER_VF_SINGLE_NODE;
	u16 total_vf;

	/* Secondary Qsets are needed only अगर CPU count is
	 * morethan MAX_QUEUES_PER_QSET.
	 */
	अगर (num_online_cpus() <= MAX_QUEUES_PER_QSET)
		वापस 0;

	/* Check अगर its a multi-node environment */
	अगर (nr_node_ids > 1)
		sqs_per_vf = MAX_SQS_PER_VF;

	pos = pci_find_ext_capability(nic->pdev, PCI_EXT_CAP_ID_SRIOV);
	pci_पढ़ो_config_word(nic->pdev, (pos + PCI_SRIOV_TOTAL_VF), &total_vf);
	वापस min(total_vf - vf_en, vf_en * sqs_per_vf);
पूर्ण

अटल पूर्णांक nic_sriov_init(काष्ठा pci_dev *pdev, काष्ठा nicpf *nic)
अणु
	पूर्णांक pos = 0;
	पूर्णांक vf_en;
	पूर्णांक err;
	u16 total_vf_cnt;

	pos = pci_find_ext_capability(pdev, PCI_EXT_CAP_ID_SRIOV);
	अगर (!pos) अणु
		dev_err(&pdev->dev, "SRIOV capability is not found in PCIe config space\n");
		वापस -ENODEV;
	पूर्ण

	pci_पढ़ो_config_word(pdev, (pos + PCI_SRIOV_TOTAL_VF), &total_vf_cnt);
	अगर (total_vf_cnt < nic->num_vf_en)
		nic->num_vf_en = total_vf_cnt;

	अगर (!total_vf_cnt)
		वापस 0;

	vf_en = nic->num_vf_en;
	nic->num_sqs_en = nic_num_sqs_en(nic, nic->num_vf_en);
	vf_en += nic->num_sqs_en;

	err = pci_enable_sriov(pdev, vf_en);
	अगर (err) अणु
		dev_err(&pdev->dev, "SRIOV enable failed, num VF is %d\n",
			vf_en);
		nic->num_vf_en = 0;
		वापस err;
	पूर्ण

	dev_info(&pdev->dev, "SRIOV enabled, number of VF available %d\n",
		 vf_en);

	nic->flags |= NIC_SRIOV_ENABLED;
	वापस 0;
पूर्ण

अटल पूर्णांक nic_probe(काष्ठा pci_dev *pdev, स्थिर काष्ठा pci_device_id *ent)
अणु
	काष्ठा device *dev = &pdev->dev;
	काष्ठा nicpf *nic;
	u8     max_lmac;
	पूर्णांक    err;

	BUILD_BUG_ON(माप(जोड़ nic_mbx) > 16);

	nic = devm_kzalloc(dev, माप(*nic), GFP_KERNEL);
	अगर (!nic)
		वापस -ENOMEM;

	nic->hw = devm_kzalloc(dev, माप(काष्ठा hw_info), GFP_KERNEL);
	अगर (!nic->hw)
		वापस -ENOMEM;

	pci_set_drvdata(pdev, nic);

	nic->pdev = pdev;

	err = pci_enable_device(pdev);
	अगर (err) अणु
		dev_err(dev, "Failed to enable PCI device\n");
		pci_set_drvdata(pdev, शून्य);
		वापस err;
	पूर्ण

	err = pci_request_regions(pdev, DRV_NAME);
	अगर (err) अणु
		dev_err(dev, "PCI request regions failed 0x%x\n", err);
		जाओ err_disable_device;
	पूर्ण

	err = pci_set_dma_mask(pdev, DMA_BIT_MASK(48));
	अगर (err) अणु
		dev_err(dev, "Unable to get usable DMA configuration\n");
		जाओ err_release_regions;
	पूर्ण

	err = pci_set_consistent_dma_mask(pdev, DMA_BIT_MASK(48));
	अगर (err) अणु
		dev_err(dev, "Unable to get 48-bit DMA for consistent allocations\n");
		जाओ err_release_regions;
	पूर्ण

	/* MAP PF's configuration रेजिस्टरs */
	nic->reg_base = pcim_iomap(pdev, PCI_CFG_REG_BAR_NUM, 0);
	अगर (!nic->reg_base) अणु
		dev_err(dev, "Cannot map config register space, aborting\n");
		err = -ENOMEM;
		जाओ err_release_regions;
	पूर्ण

	nic->node = nic_get_node_id(pdev);

	/* Get HW capability info */
	nic_get_hw_info(nic);

	/* Allocate memory क्रम LMAC tracking elements */
	err = -ENOMEM;
	max_lmac = nic->hw->bgx_cnt * MAX_LMAC_PER_BGX;

	nic->vf_lmac_map = devm_kदो_स्मृति_array(dev, max_lmac, माप(u8),
					      GFP_KERNEL);
	अगर (!nic->vf_lmac_map)
		जाओ err_release_regions;

	/* Initialize hardware */
	nic_init_hw(nic);

	nic_set_lmac_vf_mapping(nic);

	/* Register पूर्णांकerrupts */
	err = nic_रेजिस्टर_पूर्णांकerrupts(nic);
	अगर (err)
		जाओ err_release_regions;

	/* Configure SRIOV */
	err = nic_sriov_init(pdev, nic);
	अगर (err)
		जाओ err_unरेजिस्टर_पूर्णांकerrupts;

	वापस 0;

err_unरेजिस्टर_पूर्णांकerrupts:
	nic_unरेजिस्टर_पूर्णांकerrupts(nic);
err_release_regions:
	pci_release_regions(pdev);
err_disable_device:
	pci_disable_device(pdev);
	pci_set_drvdata(pdev, शून्य);
	वापस err;
पूर्ण

अटल व्योम nic_हटाओ(काष्ठा pci_dev *pdev)
अणु
	काष्ठा nicpf *nic = pci_get_drvdata(pdev);

	अगर (!nic)
		वापस;

	अगर (nic->flags & NIC_SRIOV_ENABLED)
		pci_disable_sriov(pdev);

	nic_unरेजिस्टर_पूर्णांकerrupts(nic);
	pci_release_regions(pdev);

	pci_disable_device(pdev);
	pci_set_drvdata(pdev, शून्य);
पूर्ण

अटल काष्ठा pci_driver nic_driver = अणु
	.name = DRV_NAME,
	.id_table = nic_id_table,
	.probe = nic_probe,
	.हटाओ = nic_हटाओ,
पूर्ण;

अटल पूर्णांक __init nic_init_module(व्योम)
अणु
	pr_info("%s, ver %s\n", DRV_NAME, DRV_VERSION);

	वापस pci_रेजिस्टर_driver(&nic_driver);
पूर्ण

अटल व्योम __निकास nic_cleanup_module(व्योम)
अणु
	pci_unरेजिस्टर_driver(&nic_driver);
पूर्ण

module_init(nic_init_module);
module_निकास(nic_cleanup_module);
