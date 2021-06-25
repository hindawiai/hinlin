<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/* Copyright (c)  2018 Intel Corporation */

#अगर_अघोषित _IGC_DEFINES_H_
#घोषणा _IGC_DEFINES_H_

/* Number of Transmit and Receive Descriptors must be a multiple of 8 */
#घोषणा REQ_TX_DESCRIPTOR_MULTIPLE	8
#घोषणा REQ_RX_DESCRIPTOR_MULTIPLE	8

#घोषणा IGC_CTRL_EXT_SDP2_सूची	0x00000400 /* SDP2 Data direction */
#घोषणा IGC_CTRL_EXT_SDP3_सूची	0x00000800 /* SDP3 Data direction */
#घोषणा IGC_CTRL_EXT_DRV_LOAD	0x10000000 /* Drv loaded bit क्रम FW */

/* Definitions क्रम घातer management and wakeup रेजिस्टरs */
/* Wake Up Control */
#घोषणा IGC_WUC_PME_EN	0x00000002 /* PME Enable */

/* Wake Up Filter Control */
#घोषणा IGC_WUFC_LNKC	0x00000001 /* Link Status Change Wakeup Enable */
#घोषणा IGC_WUFC_MAG	0x00000002 /* Magic Packet Wakeup Enable */
#घोषणा IGC_WUFC_EX	0x00000004 /* Directed Exact Wakeup Enable */
#घोषणा IGC_WUFC_MC	0x00000008 /* Directed Multicast Wakeup Enable */
#घोषणा IGC_WUFC_BC	0x00000010 /* Broadcast Wakeup Enable */

#घोषणा IGC_CTRL_ADVD3WUC	0x00100000  /* D3 WUC */

/* Wake Up Status */
#घोषणा IGC_WUS_EX	0x00000004 /* Directed Exact */
#घोषणा IGC_WUS_ARPD	0x00000020 /* Directed ARP Request */
#घोषणा IGC_WUS_IPV4	0x00000040 /* Directed IPv4 */
#घोषणा IGC_WUS_IPV6	0x00000080 /* Directed IPv6 */
#घोषणा IGC_WUS_NSD	0x00000400 /* Directed IPv6 Neighbor Solicitation */

/* Packet types that are enabled क्रम wake packet delivery */
#घोषणा WAKE_PKT_WUS ( \
	IGC_WUS_EX   | \
	IGC_WUS_ARPD | \
	IGC_WUS_IPV4 | \
	IGC_WUS_IPV6 | \
	IGC_WUS_NSD)

/* Wake Up Packet Length */
#घोषणा IGC_WUPL_MASK	0x00000FFF

/* Wake Up Packet Memory stores the first 128 bytes of the wake up packet */
#घोषणा IGC_WUPM_BYTES	128

/* Loop limit on how दीर्घ we रुको क्रम स्वतः-negotiation to complete */
#घोषणा COPPER_LINK_UP_LIMIT		10
#घोषणा PHY_AUTO_NEG_LIMIT		45

/* Number of 100 microseconds we रुको क्रम PCI Express master disable */
#घोषणा MASTER_DISABLE_TIMEOUT		800
/*Blocks new Master requests */
#घोषणा IGC_CTRL_GIO_MASTER_DISABLE	0x00000004
/* Status of Master requests. */
#घोषणा IGC_STATUS_GIO_MASTER_ENABLE	0x00080000

/* Receive Address
 * Number of high/low रेजिस्टर pairs in the RAR. The RAR (Receive Address
 * Registers) holds the directed and multicast addresses that we monitor.
 * Technically, we have 16 spots.  However, we reserve one of these spots
 * (RAR[15]) क्रम our directed address used by controllers with
 * manageability enabled, allowing us room क्रम 15 multicast addresses.
 */
#घोषणा IGC_RAH_RAH_MASK	0x0000FFFF
#घोषणा IGC_RAH_ASEL_MASK	0x00030000
#घोषणा IGC_RAH_ASEL_SRC_ADDR	BIT(16)
#घोषणा IGC_RAH_QSEL_MASK	0x000C0000
#घोषणा IGC_RAH_QSEL_SHIFT	18
#घोषणा IGC_RAH_QSEL_ENABLE	BIT(28)
#घोषणा IGC_RAH_AV		0x80000000 /* Receive descriptor valid */

#घोषणा IGC_RAL_MAC_ADDR_LEN	4
#घोषणा IGC_RAH_MAC_ADDR_LEN	2

/* Error Codes */
#घोषणा IGC_SUCCESS			0
#घोषणा IGC_ERR_NVM			1
#घोषणा IGC_ERR_PHY			2
#घोषणा IGC_ERR_CONFIG			3
#घोषणा IGC_ERR_PARAM			4
#घोषणा IGC_ERR_MAC_INIT		5
#घोषणा IGC_ERR_RESET			9
#घोषणा IGC_ERR_MASTER_REQUESTS_PENDING	10
#घोषणा IGC_ERR_BLK_PHY_RESET		12
#घोषणा IGC_ERR_SWFW_SYNC		13

/* Device Control */
#घोषणा IGC_CTRL_DEV_RST	0x20000000  /* Device reset */

#घोषणा IGC_CTRL_PHY_RST	0x80000000  /* PHY Reset */
#घोषणा IGC_CTRL_SLU		0x00000040  /* Set link up (Force Link) */
#घोषणा IGC_CTRL_FRCSPD		0x00000800  /* Force Speed */
#घोषणा IGC_CTRL_FRCDPX		0x00001000  /* Force Duplex */

#घोषणा IGC_CTRL_RFCE		0x08000000  /* Receive Flow Control enable */
#घोषणा IGC_CTRL_TFCE		0x10000000  /* Transmit flow control enable */

#घोषणा IGC_CTRL_SDP0_सूची 0x00400000	/* SDP0 Data direction */
#घोषणा IGC_CTRL_SDP1_सूची 0x00800000	/* SDP1 Data direction */

/* As per the EAS the maximum supported size is 9.5KB (9728 bytes) */
#घोषणा MAX_JUMBO_FRAME_SIZE	0x2600

/* PBA स्थिरants */
#घोषणा IGC_PBA_34K		0x0022

/* SW Semaphore Register */
#घोषणा IGC_SWSM_SMBI		0x00000001 /* Driver Semaphore bit */
#घोषणा IGC_SWSM_SWESMBI	0x00000002 /* FW Semaphore bit */

/* SWFW_SYNC Definitions */
#घोषणा IGC_SWFW_EEP_SM		0x1
#घोषणा IGC_SWFW_PHY0_SM	0x2

/* Autoneg Advertisement Register */
#घोषणा NWAY_AR_10T_HD_CAPS	0x0020   /* 10T   Half Duplex Capable */
#घोषणा NWAY_AR_10T_FD_CAPS	0x0040   /* 10T   Full Duplex Capable */
#घोषणा NWAY_AR_100TX_HD_CAPS	0x0080   /* 100TX Half Duplex Capable */
#घोषणा NWAY_AR_100TX_FD_CAPS	0x0100   /* 100TX Full Duplex Capable */
#घोषणा NWAY_AR_PAUSE		0x0400   /* Pause operation desired */
#घोषणा NWAY_AR_ASM_सूची		0x0800   /* Asymmetric Pause Direction bit */

/* Link Partner Ability Register (Base Page) */
#घोषणा NWAY_LPAR_PAUSE		0x0400 /* LP Pause operation desired */
#घोषणा NWAY_LPAR_ASM_सूची	0x0800 /* LP Asymmetric Pause Direction bit */

/* 1000BASE-T Control Register */
#घोषणा CR_1000T_ASYM_PAUSE	0x0080 /* Advertise asymmetric छोड़ो bit */
#घोषणा CR_1000T_HD_CAPS	0x0100 /* Advertise 1000T HD capability */
#घोषणा CR_1000T_FD_CAPS	0x0200 /* Advertise 1000T FD capability  */

/* 1000BASE-T Status Register */
#घोषणा SR_1000T_REMOTE_RX_STATUS	0x1000 /* Remote receiver OK */

/* PHY GPY 211 रेजिस्टरs */
#घोषणा STANDARD_AN_REG_MASK	0x0007 /* MMD */
#घोषणा ANEG_MULTIGBT_AN_CTRL	0x0020 /* MULTI GBT AN Control Register */
#घोषणा MMD_DEVADDR_SHIFT	16     /* Shअगरt MMD to higher bits */
#घोषणा CR_2500T_FD_CAPS	0x0080 /* Advertise 2500T FD capability */

/* NVM Control */
/* Number of milliseconds क्रम NVM स्वतः पढ़ो करोne after MAC reset. */
#घोषणा AUTO_READ_DONE_TIMEOUT		10
#घोषणा IGC_EECD_AUTO_RD		0x00000200  /* NVM Auto Read करोne */
#घोषणा IGC_EECD_REQ		0x00000040 /* NVM Access Request */
#घोषणा IGC_EECD_GNT		0x00000080 /* NVM Access Grant */
/* NVM Addressing bits based on type 0=small, 1=large */
#घोषणा IGC_EECD_ADDR_BITS		0x00000400
#घोषणा IGC_NVM_GRANT_ATTEMPTS		1000 /* NVM # attempts to gain grant */
#घोषणा IGC_EECD_SIZE_EX_MASK		0x00007800  /* NVM Size */
#घोषणा IGC_EECD_SIZE_EX_SHIFT		11
#घोषणा IGC_EECD_FLUPD_I225		0x00800000 /* Update FLASH */
#घोषणा IGC_EECD_FLUDONE_I225		0x04000000 /* Update FLASH करोne*/
#घोषणा IGC_EECD_FLASH_DETECTED_I225	0x00080000 /* FLASH detected */
#घोषणा IGC_FLUDONE_ATTEMPTS		20000
#घोषणा IGC_EERD_EEWR_MAX_COUNT		512 /* buffered EEPROM words rw */

/* Offset to data in NVM पढ़ो/ग_लिखो रेजिस्टरs */
#घोषणा IGC_NVM_RW_REG_DATA	16
#घोषणा IGC_NVM_RW_REG_DONE	2    /* Offset to READ/WRITE करोne bit */
#घोषणा IGC_NVM_RW_REG_START	1    /* Start operation */
#घोषणा IGC_NVM_RW_ADDR_SHIFT	2    /* Shअगरt to the address bits */
#घोषणा IGC_NVM_POLL_READ	0    /* Flag क्रम polling क्रम पढ़ो complete */
#घोषणा IGC_NVM_DEV_STARTER	5    /* Dev_starter Version */

/* NVM Word Offsets */
#घोषणा NVM_CHECKSUM_REG		0x003F

/* For checksumming, the sum of all words in the NVM should equal 0xBABA. */
#घोषणा NVM_SUM				0xBABA
#घोषणा NVM_WORD_SIZE_BASE_SHIFT	6

/* Collision related configuration parameters */
#घोषणा IGC_COLLISION_THRESHOLD		15
#घोषणा IGC_CT_SHIFT			4
#घोषणा IGC_COLLISION_DISTANCE		63
#घोषणा IGC_COLD_SHIFT			12

/* Device Status */
#घोषणा IGC_STATUS_FD		0x00000001      /* Full duplex.0=half,1=full */
#घोषणा IGC_STATUS_LU		0x00000002      /* Link up.0=no,1=link */
#घोषणा IGC_STATUS_FUNC_MASK	0x0000000C      /* PCI Function Mask */
#घोषणा IGC_STATUS_FUNC_SHIFT	2
#घोषणा IGC_STATUS_TXOFF	0x00000010      /* transmission छोड़ोd */
#घोषणा IGC_STATUS_SPEED_100	0x00000040      /* Speed 100Mb/s */
#घोषणा IGC_STATUS_SPEED_1000	0x00000080      /* Speed 1000Mb/s */
#घोषणा IGC_STATUS_SPEED_2500	0x00400000	/* Speed 2.5Gb/s */

#घोषणा SPEED_10		10
#घोषणा SPEED_100		100
#घोषणा SPEED_1000		1000
#घोषणा SPEED_2500		2500
#घोषणा HALF_DUPLEX		1
#घोषणा FULL_DUPLEX		2

/* 1Gbps and 2.5Gbps half duplex is not supported, nor spec-compliant. */
#घोषणा ADVERTISE_10_HALF		0x0001
#घोषणा ADVERTISE_10_FULL		0x0002
#घोषणा ADVERTISE_100_HALF		0x0004
#घोषणा ADVERTISE_100_FULL		0x0008
#घोषणा ADVERTISE_1000_HALF		0x0010 /* Not used, just FYI */
#घोषणा ADVERTISE_1000_FULL		0x0020
#घोषणा ADVERTISE_2500_HALF		0x0040 /* Not used, just FYI */
#घोषणा ADVERTISE_2500_FULL		0x0080

#घोषणा IGC_ALL_SPEED_DUPLEX_2500 ( \
	ADVERTISE_10_HALF | ADVERTISE_10_FULL | ADVERTISE_100_HALF | \
	ADVERTISE_100_FULL | ADVERTISE_1000_FULL | ADVERTISE_2500_FULL)

#घोषणा AUTONEG_ADVERTISE_SPEED_DEFAULT_2500	IGC_ALL_SPEED_DUPLEX_2500

/* Interrupt Cause Read */
#घोषणा IGC_ICR_TXDW		BIT(0)	/* Transmit desc written back */
#घोषणा IGC_ICR_TXQE		BIT(1)	/* Transmit Queue empty */
#घोषणा IGC_ICR_LSC		BIT(2)	/* Link Status Change */
#घोषणा IGC_ICR_RXSEQ		BIT(3)	/* Rx sequence error */
#घोषणा IGC_ICR_RXDMT0		BIT(4)	/* Rx desc min. threshold (0) */
#घोषणा IGC_ICR_RXO		BIT(6)	/* Rx overrun */
#घोषणा IGC_ICR_RXT0		BIT(7)	/* Rx समयr पूर्णांकr (ring 0) */
#घोषणा IGC_ICR_TS		BIT(19)	/* Time Sync Interrupt */
#घोषणा IGC_ICR_DRSTA		BIT(30)	/* Device Reset Asserted */

/* If this bit निश्चितed, the driver should claim the पूर्णांकerrupt */
#घोषणा IGC_ICR_INT_ASSERTED	BIT(31)

#घोषणा IGC_ICS_RXT0		IGC_ICR_RXT0 /* Rx समयr पूर्णांकr */

#घोषणा IMS_ENABLE_MASK ( \
	IGC_IMS_RXT0   |    \
	IGC_IMS_TXDW   |    \
	IGC_IMS_RXDMT0 |    \
	IGC_IMS_RXSEQ  |    \
	IGC_IMS_LSC)

/* Interrupt Mask Set */
#घोषणा IGC_IMS_TXDW		IGC_ICR_TXDW	/* Tx desc written back */
#घोषणा IGC_IMS_RXSEQ		IGC_ICR_RXSEQ	/* Rx sequence error */
#घोषणा IGC_IMS_LSC		IGC_ICR_LSC	/* Link Status Change */
#घोषणा IGC_IMS_DOUTSYNC	IGC_ICR_DOUTSYNC /* NIC DMA out of sync */
#घोषणा IGC_IMS_DRSTA		IGC_ICR_DRSTA	/* Device Reset Asserted */
#घोषणा IGC_IMS_RXT0		IGC_ICR_RXT0	/* Rx समयr पूर्णांकr */
#घोषणा IGC_IMS_RXDMT0		IGC_ICR_RXDMT0	/* Rx desc min. threshold */
#घोषणा IGC_IMS_TS		IGC_ICR_TS	/* Time Sync Interrupt */

#घोषणा IGC_QVECTOR_MASK	0x7FFC		/* Q-vector mask */
#घोषणा IGC_ITR_VAL_MASK	0x04		/* ITR value mask */

/* Interrupt Cause Set */
#घोषणा IGC_ICS_LSC		IGC_ICR_LSC       /* Link Status Change */
#घोषणा IGC_ICS_RXDMT0		IGC_ICR_RXDMT0    /* rx desc min. threshold */

#घोषणा IGC_ICR_DOUTSYNC	0x10000000 /* NIC DMA out of sync */
#घोषणा IGC_EITR_CNT_IGNR	0x80000000 /* Don't reset counters on ग_लिखो */
#घोषणा IGC_IVAR_VALID		0x80
#घोषणा IGC_GPIE_NSICR		0x00000001
#घोषणा IGC_GPIE_MSIX_MODE	0x00000010
#घोषणा IGC_GPIE_EIAME		0x40000000
#घोषणा IGC_GPIE_PBA		0x80000000

/* Receive Descriptor bit definitions */
#घोषणा IGC_RXD_STAT_DD		0x01    /* Descriptor Done */

/* Transmit Descriptor bit definitions */
#घोषणा IGC_TXD_DTYP_D		0x00100000 /* Data Descriptor */
#घोषणा IGC_TXD_DTYP_C		0x00000000 /* Context Descriptor */
#घोषणा IGC_TXD_POPTS_IXSM	0x01       /* Insert IP checksum */
#घोषणा IGC_TXD_POPTS_TXSM	0x02       /* Insert TCP/UDP checksum */
#घोषणा IGC_TXD_CMD_EOP		0x01000000 /* End of Packet */
#घोषणा IGC_TXD_CMD_IC		0x04000000 /* Insert Checksum */
#घोषणा IGC_TXD_CMD_DEXT	0x20000000 /* Desc extension (0 = legacy) */
#घोषणा IGC_TXD_CMD_VLE		0x40000000 /* Add VLAN tag */
#घोषणा IGC_TXD_STAT_DD		0x00000001 /* Descriptor Done */
#घोषणा IGC_TXD_CMD_TCP		0x01000000 /* TCP packet */
#घोषणा IGC_TXD_CMD_IP		0x02000000 /* IP packet */
#घोषणा IGC_TXD_CMD_TSE		0x04000000 /* TCP Seg enable */
#घोषणा IGC_TXD_EXTCMD_TSTAMP	0x00000010 /* IEEE1588 Timestamp packet */

/* IPSec Encrypt Enable */
#घोषणा IGC_ADVTXD_L4LEN_SHIFT	8  /* Adv ctxt L4LEN shअगरt */
#घोषणा IGC_ADVTXD_MSS_SHIFT	16 /* Adv ctxt MSS shअगरt */

/* Transmit Control */
#घोषणा IGC_TCTL_EN		0x00000002 /* enable Tx */
#घोषणा IGC_TCTL_PSP		0x00000008 /* pad लघु packets */
#घोषणा IGC_TCTL_CT		0x00000ff0 /* collision threshold */
#घोषणा IGC_TCTL_COLD		0x003ff000 /* collision distance */
#घोषणा IGC_TCTL_RTLC		0x01000000 /* Re-transmit on late collision */

/* Flow Control Constants */
#घोषणा FLOW_CONTROL_ADDRESS_LOW	0x00C28001
#घोषणा FLOW_CONTROL_ADDRESS_HIGH	0x00000100
#घोषणा FLOW_CONTROL_TYPE		0x8808
/* Enable XON frame transmission */
#घोषणा IGC_FCRTL_XONE			0x80000000

/* Management Control */
#घोषणा IGC_MANC_RCV_TCO_EN	0x00020000 /* Receive TCO Packets Enabled */
#घोषणा IGC_MANC_BLK_PHY_RST_ON_IDE	0x00040000 /* Block phy resets */

/* Receive Control */
#घोषणा IGC_RCTL_RST		0x00000001 /* Software reset */
#घोषणा IGC_RCTL_EN		0x00000002 /* enable */
#घोषणा IGC_RCTL_SBP		0x00000004 /* store bad packet */
#घोषणा IGC_RCTL_UPE		0x00000008 /* unicast promisc enable */
#घोषणा IGC_RCTL_MPE		0x00000010 /* multicast promisc enable */
#घोषणा IGC_RCTL_LPE		0x00000020 /* दीर्घ packet enable */
#घोषणा IGC_RCTL_LBM_MAC	0x00000040 /* MAC loopback mode */
#घोषणा IGC_RCTL_LBM_TCVR	0x000000C0 /* tcvr loopback mode */

#घोषणा IGC_RCTL_RDMTS_HALF	0x00000000 /* Rx desc min thresh size */
#घोषणा IGC_RCTL_BAM		0x00008000 /* broadcast enable */

/* Split Replication Receive Control */
#घोषणा IGC_SRRCTL_TIMESTAMP		0x40000000
#घोषणा IGC_SRRCTL_TIMER1SEL(समयr)	(((समयr) & 0x3) << 14)
#घोषणा IGC_SRRCTL_TIMER0SEL(समयr)	(((समयr) & 0x3) << 17)

/* Receive Descriptor bit definitions */
#घोषणा IGC_RXD_STAT_EOP	0x02	/* End of Packet */
#घोषणा IGC_RXD_STAT_IXSM	0x04	/* Ignore checksum */
#घोषणा IGC_RXD_STAT_UDPCS	0x10	/* UDP xsum calculated */
#घोषणा IGC_RXD_STAT_TCPCS	0x20	/* TCP xsum calculated */

/* Advanced Receive Descriptor bit definitions */
#घोषणा IGC_RXDADV_STAT_TSIP	0x08000 /* बारtamp in packet */

#घोषणा IGC_RXDEXT_STATERR_L4E		0x20000000
#घोषणा IGC_RXDEXT_STATERR_IPE		0x40000000
#घोषणा IGC_RXDEXT_STATERR_RXE		0x80000000

#घोषणा IGC_MRQC_RSS_FIELD_IPV4_TCP	0x00010000
#घोषणा IGC_MRQC_RSS_FIELD_IPV4		0x00020000
#घोषणा IGC_MRQC_RSS_FIELD_IPV6_TCP_EX	0x00040000
#घोषणा IGC_MRQC_RSS_FIELD_IPV6		0x00100000
#घोषणा IGC_MRQC_RSS_FIELD_IPV6_TCP	0x00200000

/* Header split receive */
#घोषणा IGC_RFCTL_IPV6_EX_DIS	0x00010000
#घोषणा IGC_RFCTL_LEF		0x00040000

#घोषणा IGC_RCTL_SZ_256		0x00030000 /* Rx buffer size 256 */

#घोषणा IGC_RCTL_MO_SHIFT	12 /* multicast offset shअगरt */
#घोषणा IGC_RCTL_CFIEN		0x00080000 /* canonical क्रमm enable */
#घोषणा IGC_RCTL_DPF		0x00400000 /* discard छोड़ो frames */
#घोषणा IGC_RCTL_PMCF		0x00800000 /* pass MAC control frames */
#घोषणा IGC_RCTL_SECRC		0x04000000 /* Strip Ethernet CRC */

#घोषणा I225_RXPBSIZE_DEFAULT	0x000000A2 /* RXPBSIZE शेष */
#घोषणा I225_TXPBSIZE_DEFAULT	0x04000014 /* TXPBSIZE शेष */
#घोषणा IGC_RXPBS_CFG_TS_EN	0x80000000 /* Timestamp in Rx buffer */

#घोषणा IGC_TXPBSIZE_TSN	0x04145145 /* 5k bytes buffer क्रम each queue */

#घोषणा IGC_DTXMXPKTSZ_TSN	0x19 /* 1600 bytes of max TX DMA packet size */
#घोषणा IGC_DTXMXPKTSZ_DEFAULT	0x98 /* 9728-byte Jumbo frames */

/* Time Sync Interrupt Causes */
#घोषणा IGC_TSICR_SYS_WRAP	BIT(0) /* SYSTIM Wrap around. */
#घोषणा IGC_TSICR_TXTS		BIT(1) /* Transmit Timestamp. */
#घोषणा IGC_TSICR_TT0		BIT(3) /* Target Time 0 Trigger. */
#घोषणा IGC_TSICR_TT1		BIT(4) /* Target Time 1 Trigger. */
#घोषणा IGC_TSICR_AUTT0		BIT(5) /* Auxiliary Timestamp 0 Taken. */
#घोषणा IGC_TSICR_AUTT1		BIT(6) /* Auxiliary Timestamp 1 Taken. */

#घोषणा IGC_TSICR_INTERRUPTS	IGC_TSICR_TXTS

#घोषणा IGC_FTQF_VF_BP		0x00008000
#घोषणा IGC_FTQF_1588_TIME_STAMP	0x08000000
#घोषणा IGC_FTQF_MASK			0xF0000000
#घोषणा IGC_FTQF_MASK_PROTO_BP	0x10000000

/* Time Sync Receive Control bit definitions */
#घोषणा IGC_TSYNCRXCTL_TYPE_MASK	0x0000000E  /* Rx type mask */
#घोषणा IGC_TSYNCRXCTL_TYPE_L2_V2	0x00
#घोषणा IGC_TSYNCRXCTL_TYPE_L4_V1	0x02
#घोषणा IGC_TSYNCRXCTL_TYPE_L2_L4_V2	0x04
#घोषणा IGC_TSYNCRXCTL_TYPE_ALL		0x08
#घोषणा IGC_TSYNCRXCTL_TYPE_EVENT_V2	0x0A
#घोषणा IGC_TSYNCRXCTL_ENABLED		0x00000010  /* enable Rx बारtamping */
#घोषणा IGC_TSYNCRXCTL_SYSCFI		0x00000020  /* Sys घड़ी frequency */
#घोषणा IGC_TSYNCRXCTL_RXSYNSIG		0x00000400  /* Sample RX tstamp in PHY sop */

/* Time Sync Receive Configuration */
#घोषणा IGC_TSYNCRXCFG_PTP_V1_CTRLT_MASK	0x000000FF
#घोषणा IGC_TSYNCRXCFG_PTP_V1_SYNC_MESSAGE	0x00
#घोषणा IGC_TSYNCRXCFG_PTP_V1_DELAY_REQ_MESSAGE	0x01

/* Immediate Interrupt Receive */
#घोषणा IGC_IMIR_CLEAR_MASK	0xF001FFFF /* IMIR Reg Clear Mask */
#घोषणा IGC_IMIR_PORT_BYPASS	0x20000 /* IMIR Port Bypass Bit */
#घोषणा IGC_IMIR_PRIORITY_SHIFT	29 /* IMIR Priority Shअगरt */
#घोषणा IGC_IMIREXT_CLEAR_MASK	0x7FFFF /* IMIREXT Reg Clear Mask */

/* Immediate Interrupt Receive Extended */
#घोषणा IGC_IMIREXT_CTRL_BP	0x00080000  /* Bypass check of ctrl bits */
#घोषणा IGC_IMIREXT_SIZE_BP	0x00001000  /* Packet size bypass */

/* Time Sync Transmit Control bit definitions */
#घोषणा IGC_TSYNCTXCTL_TXTT_0			0x00000001  /* Tx बारtamp reg 0 valid */
#घोषणा IGC_TSYNCTXCTL_ENABLED			0x00000010  /* enable Tx बारtamping */
#घोषणा IGC_TSYNCTXCTL_MAX_ALLOWED_DLY_MASK	0x0000F000  /* max delay */
#घोषणा IGC_TSYNCTXCTL_SYNC_COMP_ERR		0x20000000  /* sync err */
#घोषणा IGC_TSYNCTXCTL_SYNC_COMP		0x40000000  /* sync complete */
#घोषणा IGC_TSYNCTXCTL_START_SYNC		0x80000000  /* initiate sync */
#घोषणा IGC_TSYNCTXCTL_TXSYNSIG			0x00000020  /* Sample TX tstamp in PHY sop */

/* Timer selection bits */
#घोषणा IGC_AUX_IO_TIMER_SEL_SYSTIM0	(0u << 30) /* Select SYSTIM0 क्रम auxiliary समय stamp */
#घोषणा IGC_AUX_IO_TIMER_SEL_SYSTIM1	(1u << 30) /* Select SYSTIM1 क्रम auxiliary समय stamp */
#घोषणा IGC_AUX_IO_TIMER_SEL_SYSTIM2	(2u << 30) /* Select SYSTIM2 क्रम auxiliary समय stamp */
#घोषणा IGC_AUX_IO_TIMER_SEL_SYSTIM3	(3u << 30) /* Select SYSTIM3 क्रम auxiliary समय stamp */
#घोषणा IGC_TT_IO_TIMER_SEL_SYSTIM0	(0u << 30) /* Select SYSTIM0 क्रम target समय stamp */
#घोषणा IGC_TT_IO_TIMER_SEL_SYSTIM1	(1u << 30) /* Select SYSTIM1 क्रम target समय stamp */
#घोषणा IGC_TT_IO_TIMER_SEL_SYSTIM2	(2u << 30) /* Select SYSTIM2 क्रम target समय stamp */
#घोषणा IGC_TT_IO_TIMER_SEL_SYSTIM3	(3u << 30) /* Select SYSTIM3 क्रम target समय stamp */

/* TSAUXC Configuration Bits */
#घोषणा IGC_TSAUXC_EN_TT0	BIT(0)  /* Enable target समय 0. */
#घोषणा IGC_TSAUXC_EN_TT1	BIT(1)  /* Enable target समय 1. */
#घोषणा IGC_TSAUXC_EN_CLK0	BIT(2)  /* Enable Configurable Frequency Clock 0. */
#घोषणा IGC_TSAUXC_EN_CLK1	BIT(5)  /* Enable Configurable Frequency Clock 1. */
#घोषणा IGC_TSAUXC_EN_TS0	BIT(8)  /* Enable hardware बारtamp 0. */
#घोषणा IGC_TSAUXC_AUTT0	BIT(9)  /* Auxiliary Timestamp Taken. */
#घोषणा IGC_TSAUXC_EN_TS1	BIT(10) /* Enable hardware बारtamp 0. */
#घोषणा IGC_TSAUXC_AUTT1	BIT(11) /* Auxiliary Timestamp Taken. */
#घोषणा IGC_TSAUXC_PLSG		BIT(17) /* Generate a pulse. */
#घोषणा IGC_TSAUXC_DISABLE1	BIT(27) /* Disable SYSTIM0 Count Operation. */
#घोषणा IGC_TSAUXC_DISABLE2	BIT(28) /* Disable SYSTIM1 Count Operation. */
#घोषणा IGC_TSAUXC_DISABLE3	BIT(29) /* Disable SYSTIM2 Count Operation. */
#घोषणा IGC_TSAUXC_DIS_TS_CLEAR	BIT(30) /* Disable EN_TT0/1 स्वतः clear. */
#घोषणा IGC_TSAUXC_DISABLE0	BIT(31) /* Disable SYSTIM0 Count Operation. */

/* SDP Configuration Bits */
#घोषणा IGC_AUX0_SEL_SDP0	(0u << 0)  /* Assign SDP0 to auxiliary समय stamp 0. */
#घोषणा IGC_AUX0_SEL_SDP1	(1u << 0)  /* Assign SDP1 to auxiliary समय stamp 0. */
#घोषणा IGC_AUX0_SEL_SDP2	(2u << 0)  /* Assign SDP2 to auxiliary समय stamp 0. */
#घोषणा IGC_AUX0_SEL_SDP3	(3u << 0)  /* Assign SDP3 to auxiliary समय stamp 0. */
#घोषणा IGC_AUX0_TS_SDP_EN	(1u << 2)  /* Enable auxiliary समय stamp trigger 0. */
#घोषणा IGC_AUX1_SEL_SDP0	(0u << 3)  /* Assign SDP0 to auxiliary समय stamp 1. */
#घोषणा IGC_AUX1_SEL_SDP1	(1u << 3)  /* Assign SDP1 to auxiliary समय stamp 1. */
#घोषणा IGC_AUX1_SEL_SDP2	(2u << 3)  /* Assign SDP2 to auxiliary समय stamp 1. */
#घोषणा IGC_AUX1_SEL_SDP3	(3u << 3)  /* Assign SDP3 to auxiliary समय stamp 1. */
#घोषणा IGC_AUX1_TS_SDP_EN	(1u << 5)  /* Enable auxiliary समय stamp trigger 1. */
#घोषणा IGC_TS_SDP0_SEL_TT0	(0u << 6)  /* Target समय 0 is output on SDP0. */
#घोषणा IGC_TS_SDP0_SEL_TT1	(1u << 6)  /* Target समय 1 is output on SDP0. */
#घोषणा IGC_TS_SDP0_SEL_FC0	(2u << 6)  /* Freq घड़ी  0 is output on SDP0. */
#घोषणा IGC_TS_SDP0_SEL_FC1	(3u << 6)  /* Freq घड़ी  1 is output on SDP0. */
#घोषणा IGC_TS_SDP0_EN		(1u << 8)  /* SDP0 is asचिन्हित to Tsync. */
#घोषणा IGC_TS_SDP1_SEL_TT0	(0u << 9)  /* Target समय 0 is output on SDP1. */
#घोषणा IGC_TS_SDP1_SEL_TT1	(1u << 9)  /* Target समय 1 is output on SDP1. */
#घोषणा IGC_TS_SDP1_SEL_FC0	(2u << 9)  /* Freq घड़ी  0 is output on SDP1. */
#घोषणा IGC_TS_SDP1_SEL_FC1	(3u << 9)  /* Freq घड़ी  1 is output on SDP1. */
#घोषणा IGC_TS_SDP1_EN		(1u << 11) /* SDP1 is asचिन्हित to Tsync. */
#घोषणा IGC_TS_SDP2_SEL_TT0	(0u << 12) /* Target समय 0 is output on SDP2. */
#घोषणा IGC_TS_SDP2_SEL_TT1	(1u << 12) /* Target समय 1 is output on SDP2. */
#घोषणा IGC_TS_SDP2_SEL_FC0	(2u << 12) /* Freq घड़ी  0 is output on SDP2. */
#घोषणा IGC_TS_SDP2_SEL_FC1	(3u << 12) /* Freq घड़ी  1 is output on SDP2. */
#घोषणा IGC_TS_SDP2_EN		(1u << 14) /* SDP2 is asचिन्हित to Tsync. */
#घोषणा IGC_TS_SDP3_SEL_TT0	(0u << 15) /* Target समय 0 is output on SDP3. */
#घोषणा IGC_TS_SDP3_SEL_TT1	(1u << 15) /* Target समय 1 is output on SDP3. */
#घोषणा IGC_TS_SDP3_SEL_FC0	(2u << 15) /* Freq घड़ी  0 is output on SDP3. */
#घोषणा IGC_TS_SDP3_SEL_FC1	(3u << 15) /* Freq घड़ी  1 is output on SDP3. */
#घोषणा IGC_TS_SDP3_EN		(1u << 17) /* SDP3 is asचिन्हित to Tsync. */

/* Transmit Scheduling */
#घोषणा IGC_TQAVCTRL_TRANSMIT_MODE_TSN	0x00000001
#घोषणा IGC_TQAVCTRL_ENHANCED_QAV	0x00000008

#घोषणा IGC_TXQCTL_QUEUE_MODE_LAUNCHT	0x00000001
#घोषणा IGC_TXQCTL_STRICT_CYCLE		0x00000002
#घोषणा IGC_TXQCTL_STRICT_END		0x00000004

/* Receive Checksum Control */
#घोषणा IGC_RXCSUM_CRCOFL	0x00000800   /* CRC32 offload enable */
#घोषणा IGC_RXCSUM_PCSD		0x00002000   /* packet checksum disabled */

/* GPY211 - I225 defines */
#घोषणा GPY_MMD_MASK		0xFFFF0000
#घोषणा GPY_MMD_SHIFT		16
#घोषणा GPY_REG_MASK		0x0000FFFF

#घोषणा IGC_MMDAC_FUNC_DATA	0x4000 /* Data, no post increment */

/* MAC definitions */
#घोषणा IGC_FACTPS_MNGCG	0x20000000
#घोषणा IGC_FWSM_MODE_MASK	0xE
#घोषणा IGC_FWSM_MODE_SHIFT	1

/* Management Control */
#घोषणा IGC_MANC_SMBUS_EN	0x00000001 /* SMBus Enabled - RO */
#घोषणा IGC_MANC_ASF_EN		0x00000002 /* ASF Enabled - RO */

/* PHY */
#घोषणा PHY_REVISION_MASK	0xFFFFFFF0
#घोषणा MAX_PHY_REG_ADDRESS	0x1F  /* 5 bit address bus (0-0x1F) */
#घोषणा IGC_GEN_POLL_TIMEOUT	1920

/* PHY Control Register */
#घोषणा MII_CR_FULL_DUPLEX	0x0100  /* FDX =1, half duplex =0 */
#घोषणा MII_CR_RESTART_AUTO_NEG	0x0200  /* Restart स्वतः negotiation */
#घोषणा MII_CR_POWER_DOWN	0x0800  /* Power करोwn */
#घोषणा MII_CR_AUTO_NEG_EN	0x1000  /* Auto Neg Enable */

/* PHY Status Register */
#घोषणा MII_SR_LINK_STATUS	0x0004 /* Link Status 1 = link */
#घोषणा MII_SR_AUTONEG_COMPLETE	0x0020 /* Auto Neg Complete */
#घोषणा IGC_PHY_RST_COMP	0x0100 /* Internal PHY reset completion */

/* PHY 1000 MII Register/Bit Definitions */
/* PHY Registers defined by IEEE */
#घोषणा PHY_CONTROL		0x00 /* Control Register */
#घोषणा PHY_STATUS		0x01 /* Status Register */
#घोषणा PHY_ID1			0x02 /* Phy Id Reg (word 1) */
#घोषणा PHY_ID2			0x03 /* Phy Id Reg (word 2) */
#घोषणा PHY_AUTONEG_ADV		0x04 /* Autoneg Advertisement */
#घोषणा PHY_LP_ABILITY		0x05 /* Link Partner Ability (Base Page) */
#घोषणा PHY_1000T_CTRL		0x09 /* 1000Base-T Control Reg */
#घोषणा PHY_1000T_STATUS	0x0A /* 1000Base-T Status Reg */

/* Bit definitions क्रम valid PHY IDs. I = Integrated E = External */
#घोषणा I225_I_PHY_ID		0x67C9DC00

/* MDI Control */
#घोषणा IGC_MDIC_DATA_MASK	0x0000FFFF
#घोषणा IGC_MDIC_REG_MASK	0x001F0000
#घोषणा IGC_MDIC_REG_SHIFT	16
#घोषणा IGC_MDIC_PHY_MASK	0x03E00000
#घोषणा IGC_MDIC_PHY_SHIFT	21
#घोषणा IGC_MDIC_OP_WRITE	0x04000000
#घोषणा IGC_MDIC_OP_READ	0x08000000
#घोषणा IGC_MDIC_READY		0x10000000
#घोषणा IGC_MDIC_INT_EN		0x20000000
#घोषणा IGC_MDIC_ERROR		0x40000000

#घोषणा IGC_N0_QUEUE		-1

#घोषणा IGC_MAX_MAC_HDR_LEN	127
#घोषणा IGC_MAX_NETWORK_HDR_LEN	511

#घोषणा IGC_VLANPQF_QSEL(_n, q_idx) ((q_idx) << ((_n) * 4))
#घोषणा IGC_VLANPQF_VALID(_n)	(0x1 << (3 + (_n) * 4))
#घोषणा IGC_VLANPQF_QUEUE_MASK	0x03

#घोषणा IGC_ADVTXD_MACLEN_SHIFT		9  /* Adv ctxt desc mac len shअगरt */
#घोषणा IGC_ADVTXD_TUCMD_IPV4		0x00000400  /* IP Packet Type:1=IPv4 */
#घोषणा IGC_ADVTXD_TUCMD_L4T_TCP	0x00000800  /* L4 Packet Type of TCP */
#घोषणा IGC_ADVTXD_TUCMD_L4T_SCTP	0x00001000 /* L4 packet TYPE of SCTP */

/* Maximum size of the MTA रेजिस्टर table in all supported adapters */
#घोषणा MAX_MTA_REG			128

/* EEE defines */
#घोषणा IGC_IPCNFG_EEE_2_5G_AN		0x00000010 /* IPCNFG EEE Ena 2.5G AN */
#घोषणा IGC_IPCNFG_EEE_1G_AN		0x00000008 /* IPCNFG EEE Ena 1G AN */
#घोषणा IGC_IPCNFG_EEE_100M_AN		0x00000004 /* IPCNFG EEE Ena 100M AN */
#घोषणा IGC_EEER_EEE_NEG		0x20000000 /* EEE capability nego */
#घोषणा IGC_EEER_TX_LPI_EN		0x00010000 /* EEER Tx LPI Enable */
#घोषणा IGC_EEER_RX_LPI_EN		0x00020000 /* EEER Rx LPI Enable */
#घोषणा IGC_EEER_LPI_FC			0x00040000 /* EEER Ena on Flow Cntrl */
#घोषणा IGC_EEE_SU_LPI_CLK_STP		0x00800000 /* EEE LPI Clock Stop */

/* LTR defines */
#घोषणा IGC_LTRC_EEEMS_EN		0x00000020 /* Enable EEE LTR max send */
#घोषणा IGC_RXPBS_SIZE_I225_MASK	0x0000003F /* Rx packet buffer size */
#घोषणा IGC_TW_SYSTEM_1000_MASK		0x000000FF
/* Minimum समय क्रम 100BASE-T where no data will be transmit following move out
 * of EEE LPI Tx state
 */
#घोषणा IGC_TW_SYSTEM_100_MASK		0x0000FF00
#घोषणा IGC_TW_SYSTEM_100_SHIFT		8
#घोषणा IGC_DMACR_DMAC_EN		0x80000000 /* Enable DMA Coalescing */
#घोषणा IGC_DMACR_DMACTHR_MASK		0x00FF0000
#घोषणा IGC_DMACR_DMACTHR_SHIFT		16
/* Reg val to set scale to 1024 nsec */
#घोषणा IGC_LTRMINV_SCALE_1024		2
/* Reg val to set scale to 32768 nsec */
#घोषणा IGC_LTRMINV_SCALE_32768		3
/* Reg val to set scale to 1024 nsec */
#घोषणा IGC_LTRMAXV_SCALE_1024		2
/* Reg val to set scale to 32768 nsec */
#घोषणा IGC_LTRMAXV_SCALE_32768		3
#घोषणा IGC_LTRMINV_LTRV_MASK		0x000003FF /* LTR minimum value */
#घोषणा IGC_LTRMAXV_LTRV_MASK		0x000003FF /* LTR maximum value */
#घोषणा IGC_LTRMINV_LSNP_REQ		0x00008000 /* LTR Snoop Requirement */
#घोषणा IGC_LTRMINV_SCALE_SHIFT		10
#घोषणा IGC_LTRMAXV_LSNP_REQ		0x00008000 /* LTR Snoop Requirement */
#घोषणा IGC_LTRMAXV_SCALE_SHIFT		10

#पूर्ण_अगर /* _IGC_DEFINES_H_ */
