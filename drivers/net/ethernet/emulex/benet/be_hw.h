<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Copyright (C) 2005-2016 Broadcom.
 * All rights reserved.
 *
 * Contact Inक्रमmation:
 * linux-drivers@emulex.com
 *
 * Emulex
 * 3333 Susan Street
 * Costa Mesa, CA 92626
 */

/********* Mailbox करोor bell *************/
/* Used क्रम driver communication with the FW.
 * The software must ग_लिखो this रेजिस्टर twice to post any command. First,
 * it ग_लिखोs the रेजिस्टर with hi=1 and the upper bits of the physical address
 * क्रम the MAILBOX काष्ठाure. Software must poll the पढ़ोy bit until this
 * is acknowledged. Then, sotware ग_लिखोs the रेजिस्टर with hi=0 with the lower
 * bits in the address. It must poll the पढ़ोy bit until the command is
 * complete. Upon completion, the MAILBOX will contain a valid completion
 * queue entry.
 */
#घोषणा MPU_MAILBOX_DB_OFFSET	0x160
#घोषणा MPU_MAILBOX_DB_RDY_MASK	0x1 	/* bit 0 */
#घोषणा MPU_MAILBOX_DB_HI_MASK	0x2	/* bit 1 */

#घोषणा MPU_EP_CONTROL 		0

/********** MPU semphore: used क्रम SH & BE  *************/
#घोषणा SLIPORT_SOFTRESET_OFFSET		0x5c	/* CSR BAR offset */
#घोषणा SLIPORT_SEMAPHORE_OFFSET_BEx		0xac  /* CSR BAR offset */
#घोषणा SLIPORT_SEMAPHORE_OFFSET_SH		0x94  /* PCI-CFG offset */
#घोषणा POST_STAGE_MASK				0x0000FFFF
#घोषणा POST_ERR_MASK				0x1
#घोषणा POST_ERR_SHIFT				31
#घोषणा POST_ERR_RECOVERY_CODE_MASK		0xFFF

/* Soft Reset रेजिस्टर masks */
#घोषणा SLIPORT_SOFTRESET_SR_MASK		0x00000080	/* SR bit */

/* MPU semphore POST stage values */
#घोषणा POST_STAGE_AWAITING_HOST_RDY 	0x1 /* FW aरुकोing goahead from host */
#घोषणा POST_STAGE_HOST_RDY 		0x2 /* Host has given go-ahed to FW */
#घोषणा POST_STAGE_BE_RESET		0x3 /* Host wants to reset chip */
#घोषणा POST_STAGE_ARMFW_RDY		0xc000	/* FW is करोne with POST */
#घोषणा POST_STAGE_RECOVERABLE_ERR	0xE000	/* Recoverable err detected */
/* FW has detected a UE and is dumping FAT log data */
#घोषणा POST_STAGE_FAT_LOG_START       0x0D00
#घोषणा POST_STAGE_ARMFW_UE            0xF000  /*FW has निश्चितed an UE*/

/* Lancer SLIPORT रेजिस्टरs */
#घोषणा SLIPORT_STATUS_OFFSET		0x404
#घोषणा SLIPORT_CONTROL_OFFSET		0x408
#घोषणा SLIPORT_ERROR1_OFFSET		0x40C
#घोषणा SLIPORT_ERROR2_OFFSET		0x410
#घोषणा PHYSDEV_CONTROL_OFFSET		0x414

#घोषणा SLIPORT_STATUS_ERR_MASK		0x80000000
#घोषणा SLIPORT_STATUS_DIP_MASK		0x02000000
#घोषणा SLIPORT_STATUS_RN_MASK		0x01000000
#घोषणा SLIPORT_STATUS_RDY_MASK		0x00800000
#घोषणा SLI_PORT_CONTROL_IP_MASK	0x08000000
#घोषणा PHYSDEV_CONTROL_FW_RESET_MASK	0x00000002
#घोषणा PHYSDEV_CONTROL_DD_MASK		0x00000004
#घोषणा PHYSDEV_CONTROL_INP_MASK	0x40000000

#घोषणा SLIPORT_ERROR_NO_RESOURCE1	0x2
#घोषणा SLIPORT_ERROR_NO_RESOURCE2	0x9

#घोषणा SLIPORT_ERROR_FW_RESET1		0x2
#घोषणा SLIPORT_ERROR_FW_RESET2		0x0

/********* Memory BAR रेजिस्टर ************/
#घोषणा PCICFG_MEMBAR_CTRL_INT_CTRL_OFFSET 	0xfc
/* Host Interrupt Enable, अगर set पूर्णांकerrupts are enabled although "PCI Interrupt
 * Disable" may still globally block पूर्णांकerrupts in addition to inभागidual
 * पूर्णांकerrupt masks; a mechanism क्रम the device driver to block all पूर्णांकerrupts
 * atomically without having to arbitrate क्रम the PCI Interrupt Disable bit
 * with the OS.
 */
#घोषणा MEMBAR_CTRL_INT_CTRL_HOSTINTR_MASK	BIT(29) /* bit 29 */

/********* PCI Function Capability *********/
#घोषणा BE_FUNCTION_CAPS_RSS			0x2
#घोषणा BE_FUNCTION_CAPS_SUPER_NIC		0x40

/********* Power management (WOL) **********/
#घोषणा PCICFG_PM_CONTROL_OFFSET		0x44
#घोषणा PCICFG_PM_CONTROL_MASK			0x108	/* bits 3 & 8 */

/********* Online Control Registers *******/
#घोषणा PCICFG_ONLINE0				0xB0
#घोषणा PCICFG_ONLINE1				0xB4

/********* UE Status and Mask Registers ***/
#घोषणा PCICFG_UE_STATUS_LOW			0xA0
#घोषणा PCICFG_UE_STATUS_HIGH			0xA4
#घोषणा PCICFG_UE_STATUS_LOW_MASK		0xA8
#घोषणा PCICFG_UE_STATUS_HI_MASK		0xAC

/******** SLI_INTF ***********************/
#घोषणा SLI_INTF_REG_OFFSET			0x58
#घोषणा SLI_INTF_VALID_MASK			0xE0000000
#घोषणा SLI_INTF_VALID				0xC0000000
#घोषणा SLI_INTF_HINT2_MASK			0x1F000000
#घोषणा SLI_INTF_HINT2_SHIFT			24
#घोषणा SLI_INTF_HINT1_MASK			0x00FF0000
#घोषणा SLI_INTF_HINT1_SHIFT			16
#घोषणा SLI_INTF_FAMILY_MASK			0x00000F00
#घोषणा SLI_INTF_FAMILY_SHIFT			8
#घोषणा SLI_INTF_IF_TYPE_MASK			0x0000F000
#घोषणा SLI_INTF_IF_TYPE_SHIFT			12
#घोषणा SLI_INTF_REV_MASK			0x000000F0
#घोषणा SLI_INTF_REV_SHIFT			4
#घोषणा SLI_INTF_FT_MASK			0x00000001

#घोषणा SLI_INTF_TYPE_2		2
#घोषणा SLI_INTF_TYPE_3		3

/********* ISR0 Register offset **********/
#घोषणा CEV_ISR0_OFFSET 			0xC18
#घोषणा CEV_ISR_SIZE				4

/********* Event Q करोor bell *************/
#घोषणा DB_EQ_OFFSET			DB_CQ_OFFSET
#घोषणा DB_EQ_RING_ID_MASK		0x1FF	/* bits 0 - 8 */
#घोषणा DB_EQ_RING_ID_EXT_MASK		0x3e00  /* bits 9-13 */
#घोषणा DB_EQ_RING_ID_EXT_MASK_SHIFT	(2) /* qid bits 9-13 placing at 11-15 */

/* Clear the पूर्णांकerrupt क्रम this eq */
#घोषणा DB_EQ_CLR_SHIFT			(9)	/* bit 9 */
/* Must be 1 */
#घोषणा DB_EQ_EVNT_SHIFT		(10)	/* bit 10 */
/* Number of event entries processed */
#घोषणा DB_EQ_NUM_POPPED_SHIFT		(16)	/* bits 16 - 28 */
/* Rearm bit */
#घोषणा DB_EQ_REARM_SHIFT		(29)	/* bit 29 */
/* Rearm to पूर्णांकerrupt delay encoding */
#घोषणा DB_EQ_R2I_DLY_SHIFT		(30)    /* bits 30 - 31 */

/* Rearm to पूर्णांकerrupt (R2I) delay multiplier encoding represents 3 dअगरferent
 * values configured in CEV_REARM2IRPT_DLY_MULT_CSR रेजिस्टर. This value is
 * programmed by host driver जबतक ringing an EQ करोorbell(EQ_DB) अगर a delay
 * between rearming the EQ and next पूर्णांकerrupt on this EQ is desired.
 */
#घोषणा	R2I_DLY_ENC_0			0	/* No delay */
#घोषणा	R2I_DLY_ENC_1			1	/* maps to 160us EQ delay */
#घोषणा	R2I_DLY_ENC_2			2	/* maps to 96us EQ delay */
#घोषणा	R2I_DLY_ENC_3			3	/* maps to 48us EQ delay */

/********* Compl Q करोor bell *************/
#घोषणा DB_CQ_OFFSET 			0x120
#घोषणा DB_CQ_RING_ID_MASK		0x3FF	/* bits 0 - 9 */
#घोषणा DB_CQ_RING_ID_EXT_MASK		0x7C00	/* bits 10-14 */
#घोषणा DB_CQ_RING_ID_EXT_MASK_SHIFT	(1)	/* qid bits 10-14
						 placing at 11-15 */

/* Number of event entries processed */
#घोषणा DB_CQ_NUM_POPPED_SHIFT		(16) 	/* bits 16 - 28 */
/* Rearm bit */
#घोषणा DB_CQ_REARM_SHIFT		(29) 	/* bit 29 */

/********** TX ULP करोor bell *************/
#घोषणा DB_TXULP1_OFFSET		0x60
#घोषणा DB_TXULP_RING_ID_MASK		0x7FF	/* bits 0 - 10 */
/* Number of tx entries posted */
#घोषणा DB_TXULP_NUM_POSTED_SHIFT	(16)	/* bits 16 - 29 */
#घोषणा DB_TXULP_NUM_POSTED_MASK	0x3FFF	/* bits 16 - 29 */

/********** RQ(erx) करोor bell ************/
#घोषणा DB_RQ_OFFSET 			0x100
#घोषणा DB_RQ_RING_ID_MASK		0x3FF	/* bits 0 - 9 */
/* Number of rx frags posted */
#घोषणा DB_RQ_NUM_POSTED_SHIFT		(24)	/* bits 24 - 31 */

/********** MCC करोor bell ************/
#घोषणा DB_MCCQ_OFFSET 			0x140
#घोषणा DB_MCCQ_RING_ID_MASK		0x7FF	/* bits 0 - 10 */
/* Number of entries posted */
#घोषणा DB_MCCQ_NUM_POSTED_SHIFT	(16)	/* bits 16 - 29 */

/********** SRIOV VF PCICFG OFFSET ********/
#घोषणा SRIOV_VF_PCICFG_OFFSET		(4096)

/********** FAT TABLE  ********/
#घोषणा RETRIEVE_FAT	0
#घोषणा QUERY_FAT	1

/************* Rx Packet Type Encoding **************/
#घोषणा BE_UNICAST_PACKET		0
#घोषणा BE_MULTICAST_PACKET		1
#घोषणा BE_BROADCAST_PACKET		2
#घोषणा BE_RSVD_PACKET			3

/*
 * BE descriptors: host memory data काष्ठाures whose क्रमmats
 * are hardwired in BE silicon.
 */
/* Event Queue Descriptor */
#घोषणा EQ_ENTRY_VALID_MASK 		0x1	/* bit 0 */
#घोषणा EQ_ENTRY_RES_ID_MASK 		0xFFFF	/* bits 16 - 31 */
#घोषणा EQ_ENTRY_RES_ID_SHIFT 		16

काष्ठा be_eq_entry अणु
	u32 evt;
पूर्ण;

/* TX Queue Descriptor */
#घोषणा ETH_WRB_FRAG_LEN_MASK		0xFFFF
काष्ठा be_eth_wrb अणु
	__le32 frag_pa_hi;		/* dword 0 */
	__le32 frag_pa_lo;		/* dword 1 */
	u32 rsvd0;			/* dword 2 */
	__le32 frag_len;		/* dword 3: bits 0 - 15 */
पूर्ण __packed;

/* Pseuकरो amap definition क्रम eth_hdr_wrb in which each bit of the
 * actual काष्ठाure is defined as a byte : used to calculate
 * offset/shअगरt/mask of each field */
काष्ठा amap_eth_hdr_wrb अणु
	u8 rsvd0[32];		/* dword 0 */
	u8 rsvd1[32];		/* dword 1 */
	u8 complete;		/* dword 2 */
	u8 event;
	u8 crc;
	u8 क्रमward;
	u8 lso6;
	u8 mgmt;
	u8 ipcs;
	u8 udpcs;
	u8 tcpcs;
	u8 lso;
	u8 vlan;
	u8 gso[2];
	u8 num_wrb[5];
	u8 lso_mss[14];
	u8 len[16];		/* dword 3 */
	u8 vlan_tag[16];
पूर्ण __packed;

#घोषणा TX_HDR_WRB_COMPL		1		/* word 2 */
#घोषणा TX_HDR_WRB_EVT			BIT(1)		/* word 2 */
#घोषणा TX_HDR_WRB_NUM_SHIFT		13		/* word 2: bits 13:17 */
#घोषणा TX_HDR_WRB_NUM_MASK		0x1F		/* word 2: bits 13:17 */

काष्ठा be_eth_hdr_wrb अणु
	__le32 dw[4];
पूर्ण;

/********* Tx Compl Status Encoding *********/
#घोषणा BE_TX_COMP_HDR_PARSE_ERR	0x2
#घोषणा BE_TX_COMP_NDMA_ERR		0x3
#घोषणा BE_TX_COMP_ACL_ERR		0x5

#घोषणा LANCER_TX_COMP_LSO_ERR			0x1
#घोषणा LANCER_TX_COMP_HSW_DROP_MAC_ERR		0x3
#घोषणा LANCER_TX_COMP_HSW_DROP_VLAN_ERR	0x5
#घोषणा LANCER_TX_COMP_QINQ_ERR			0x7
#घोषणा LANCER_TX_COMP_SGE_ERR			0x9
#घोषणा LANCER_TX_COMP_PARITY_ERR		0xb
#घोषणा LANCER_TX_COMP_DMA_ERR			0xd

/* TX Compl Queue Descriptor */

/* Pseuकरो amap definition क्रम eth_tx_compl in which each bit of the
 * actual काष्ठाure is defined as a byte: used to calculate
 * offset/shअगरt/mask of each field */
काष्ठा amap_eth_tx_compl अणु
	u8 wrb_index[16];	/* dword 0 */
	u8 ct[2]; 		/* dword 0 */
	u8 port[2];		/* dword 0 */
	u8 rsvd0[8];		/* dword 0 */
	u8 status[4];		/* dword 0 */
	u8 user_bytes[16];	/* dword 1 */
	u8 nwh_bytes[8];	/* dword 1 */
	u8 lso;			/* dword 1 */
	u8 cast_enc[2];		/* dword 1 */
	u8 rsvd1[5];		/* dword 1 */
	u8 rsvd2[32];		/* dword 2 */
	u8 pkts[16];		/* dword 3 */
	u8 ringid[11];		/* dword 3 */
	u8 hash_val[4];		/* dword 3 */
	u8 valid;		/* dword 3 */
पूर्ण __packed;

काष्ठा be_eth_tx_compl अणु
	u32 dw[4];
पूर्ण;

/* RX Queue Descriptor */
काष्ठा be_eth_rx_d अणु
	u32 fragpa_hi;
	u32 fragpa_lo;
पूर्ण;

/* RX Compl Queue Descriptor */

/* Pseuकरो amap definition क्रम BE2 and BE3 legacy mode eth_rx_compl in which
 * each bit of the actual काष्ठाure is defined as a byte: used to calculate
 * offset/shअगरt/mask of each field */
काष्ठा amap_eth_rx_compl_v0 अणु
	u8 vlan_tag[16];	/* dword 0 */
	u8 pktsize[14];		/* dword 0 */
	u8 port;		/* dword 0 */
	u8 ip_opt;		/* dword 0 */
	u8 err;			/* dword 1 */
	u8 rsshp;		/* dword 1 */
	u8 ipf;			/* dword 1 */
	u8 tcpf;		/* dword 1 */
	u8 udpf;		/* dword 1 */
	u8 ipcksm;		/* dword 1 */
	u8 l4_cksm;		/* dword 1 */
	u8 ip_version;		/* dword 1 */
	u8 macdst[6];		/* dword 1 */
	u8 vtp;			/* dword 1 */
	u8 ip_frag;		/* dword 1 */
	u8 fragndx[10];		/* dword 1 */
	u8 ct[2];		/* dword 1 */
	u8 sw;			/* dword 1 */
	u8 numfrags[3];		/* dword 1 */
	u8 rss_flush;		/* dword 2 */
	u8 cast_enc[2];		/* dword 2 */
	u8 qnq;			/* dword 2 */
	u8 rss_bank;		/* dword 2 */
	u8 rsvd1[23];		/* dword 2 */
	u8 lro_pkt;		/* dword 2 */
	u8 rsvd2[2];		/* dword 2 */
	u8 valid;		/* dword 2 */
	u8 rsshash[32];		/* dword 3 */
पूर्ण __packed;

/* Pseuकरो amap definition क्रम BE3 native mode eth_rx_compl in which
 * each bit of the actual काष्ठाure is defined as a byte: used to calculate
 * offset/shअगरt/mask of each field */
काष्ठा amap_eth_rx_compl_v1 अणु
	u8 vlan_tag[16];	/* dword 0 */
	u8 pktsize[14];		/* dword 0 */
	u8 vtp;			/* dword 0 */
	u8 ip_opt;		/* dword 0 */
	u8 err;			/* dword 1 */
	u8 rsshp;		/* dword 1 */
	u8 ipf;			/* dword 1 */
	u8 tcpf;		/* dword 1 */
	u8 udpf;		/* dword 1 */
	u8 ipcksm;		/* dword 1 */
	u8 l4_cksm;		/* dword 1 */
	u8 ip_version;		/* dword 1 */
	u8 macdst[7];		/* dword 1 */
	u8 rsvd0;		/* dword 1 */
	u8 fragndx[10];		/* dword 1 */
	u8 ct[2];		/* dword 1 */
	u8 sw;			/* dword 1 */
	u8 numfrags[3];		/* dword 1 */
	u8 rss_flush;		/* dword 2 */
	u8 cast_enc[2];		/* dword 2 */
	u8 qnq;			/* dword 2 */
	u8 rss_bank;		/* dword 2 */
	u8 port[2];		/* dword 2 */
	u8 vntagp;		/* dword 2 */
	u8 header_len[8];	/* dword 2 */
	u8 header_split[2];	/* dword 2 */
	u8 rsvd1[12];		/* dword 2 */
	u8 tunneled;
	u8 valid;		/* dword 2 */
	u8 rsshash[32];		/* dword 3 */
पूर्ण __packed;

काष्ठा be_eth_rx_compl अणु
	u32 dw[4];
पूर्ण;
