<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/* Copyright(c) 1999 - 2018 Intel Corporation. */

#अगर_अघोषित _IXGBEVF_DEFINES_H_
#घोषणा _IXGBEVF_DEFINES_H_

/* Device IDs */
#घोषणा IXGBE_DEV_ID_82599_VF		0x10ED
#घोषणा IXGBE_DEV_ID_X540_VF		0x1515
#घोषणा IXGBE_DEV_ID_X550_VF		0x1565
#घोषणा IXGBE_DEV_ID_X550EM_X_VF	0x15A8
#घोषणा IXGBE_DEV_ID_X550EM_A_VF	0x15C5

#घोषणा IXGBE_DEV_ID_82599_VF_HV	0x152E
#घोषणा IXGBE_DEV_ID_X540_VF_HV		0x1530
#घोषणा IXGBE_DEV_ID_X550_VF_HV		0x1564
#घोषणा IXGBE_DEV_ID_X550EM_X_VF_HV	0x15A9

#घोषणा IXGBE_VF_IRQ_CLEAR_MASK		7
#घोषणा IXGBE_VF_MAX_TX_QUEUES		8
#घोषणा IXGBE_VF_MAX_RX_QUEUES		8

/* DCB define */
#घोषणा IXGBE_VF_MAX_TRAFFIC_CLASS	8

/* Link speed */
प्रकार u32 ixgbe_link_speed;
#घोषणा IXGBE_LINK_SPEED_1GB_FULL	0x0020
#घोषणा IXGBE_LINK_SPEED_10GB_FULL	0x0080
#घोषणा IXGBE_LINK_SPEED_100_FULL	0x0008

#घोषणा IXGBE_CTRL_RST		0x04000000 /* Reset (SW) */
#घोषणा IXGBE_RXDCTL_ENABLE	0x02000000 /* Enable specअगरic Rx Queue */
#घोषणा IXGBE_TXDCTL_ENABLE	0x02000000 /* Enable specअगरic Tx Queue */
#घोषणा IXGBE_LINKS_UP		0x40000000
#घोषणा IXGBE_LINKS_SPEED_82599		0x30000000
#घोषणा IXGBE_LINKS_SPEED_10G_82599	0x30000000
#घोषणा IXGBE_LINKS_SPEED_1G_82599	0x20000000
#घोषणा IXGBE_LINKS_SPEED_100_82599	0x10000000

/* Number of Transmit and Receive Descriptors must be a multiple of 8 */
#घोषणा IXGBE_REQ_TX_DESCRIPTOR_MULTIPLE	8
#घोषणा IXGBE_REQ_RX_DESCRIPTOR_MULTIPLE	8
#घोषणा IXGBE_REQ_TX_BUFFER_GRANULARITY		1024

/* Interrupt Vector Allocation Registers */
#घोषणा IXGBE_IVAR_ALLOC_VAL	0x80 /* Interrupt Allocation valid */

#घोषणा IXGBE_VF_INIT_TIMEOUT	200 /* Number of retries to clear RSTI */

/* Receive Config masks */
#घोषणा IXGBE_RXCTRL_RXEN	0x00000001  /* Enable Receiver */
#घोषणा IXGBE_RXCTRL_DMBYPS	0x00000002  /* Descriptor Monitor Bypass */
#घोषणा IXGBE_RXDCTL_ENABLE	0x02000000  /* Enable specअगरic Rx Queue */
#घोषणा IXGBE_RXDCTL_VME	0x40000000  /* VLAN mode enable */
#घोषणा IXGBE_RXDCTL_RLPMLMASK	0x00003FFF  /* Only supported on the X540 */
#घोषणा IXGBE_RXDCTL_RLPML_EN	0x00008000

/* DCA Control */
#घोषणा IXGBE_DCA_TXCTRL_TX_WB_RO_EN BIT(11) /* Tx Desc ग_लिखोback RO bit */

/* PSRTYPE bit definitions */
#घोषणा IXGBE_PSRTYPE_TCPHDR	0x00000010
#घोषणा IXGBE_PSRTYPE_UDPHDR	0x00000020
#घोषणा IXGBE_PSRTYPE_IPV4HDR	0x00000100
#घोषणा IXGBE_PSRTYPE_IPV6HDR	0x00000200
#घोषणा IXGBE_PSRTYPE_L2HDR	0x00001000

/* SRRCTL bit definitions */
#घोषणा IXGBE_SRRCTL_BSIZEPKT_SHIFT	10     /* so many KBs */
#घोषणा IXGBE_SRRCTL_RDMTS_SHIFT	22
#घोषणा IXGBE_SRRCTL_RDMTS_MASK		0x01C00000
#घोषणा IXGBE_SRRCTL_DROP_EN		0x10000000
#घोषणा IXGBE_SRRCTL_BSIZEPKT_MASK	0x0000007F
#घोषणा IXGBE_SRRCTL_BSIZEHDR_MASK	0x00003F00
#घोषणा IXGBE_SRRCTL_DESCTYPE_LEGACY	0x00000000
#घोषणा IXGBE_SRRCTL_DESCTYPE_ADV_ONEBUF 0x02000000
#घोषणा IXGBE_SRRCTL_DESCTYPE_HDR_SPLIT	0x04000000
#घोषणा IXGBE_SRRCTL_DESCTYPE_HDR_REPLICATION_LARGE_PKT 0x08000000
#घोषणा IXGBE_SRRCTL_DESCTYPE_HDR_SPLIT_ALWAYS 0x0A000000
#घोषणा IXGBE_SRRCTL_DESCTYPE_MASK	0x0E000000

/* Receive Descriptor bit definitions */
#घोषणा IXGBE_RXD_STAT_DD	0x01    /* Descriptor Done */
#घोषणा IXGBE_RXD_STAT_EOP	0x02    /* End of Packet */
#घोषणा IXGBE_RXD_STAT_FLM	0x04    /* FDir Match */
#घोषणा IXGBE_RXD_STAT_VP	0x08    /* IEEE VLAN Packet */
#घोषणा IXGBE_RXDADV_NEXTP_MASK	0x000FFFF0 /* Next Descriptor Index */
#घोषणा IXGBE_RXDADV_NEXTP_SHIFT	0x00000004
#घोषणा IXGBE_RXD_STAT_UDPCS	0x10    /* UDP xsum calculated */
#घोषणा IXGBE_RXD_STAT_L4CS	0x20    /* L4 xsum calculated */
#घोषणा IXGBE_RXD_STAT_IPCS	0x40    /* IP xsum calculated */
#घोषणा IXGBE_RXD_STAT_PIF	0x80    /* passed in-exact filter */
#घोषणा IXGBE_RXD_STAT_CRCV	0x100   /* Speculative CRC Valid */
#घोषणा IXGBE_RXD_STAT_VEXT	0x200   /* 1st VLAN found */
#घोषणा IXGBE_RXD_STAT_UDPV	0x400   /* Valid UDP checksum */
#घोषणा IXGBE_RXD_STAT_DYNINT	0x800   /* Pkt caused INT via DYNINT */
#घोषणा IXGBE_RXD_STAT_TS	0x10000 /* Time Stamp */
#घोषणा IXGBE_RXD_STAT_SECP	0x20000 /* Security Processing */
#घोषणा IXGBE_RXD_STAT_LB	0x40000 /* Loopback Status */
#घोषणा IXGBE_RXD_STAT_ACK	0x8000  /* ACK Packet indication */
#घोषणा IXGBE_RXD_ERR_CE	0x01    /* CRC Error */
#घोषणा IXGBE_RXD_ERR_LE	0x02    /* Length Error */
#घोषणा IXGBE_RXD_ERR_PE	0x08    /* Packet Error */
#घोषणा IXGBE_RXD_ERR_OSE	0x10    /* Oversize Error */
#घोषणा IXGBE_RXD_ERR_USE	0x20    /* Undersize Error */
#घोषणा IXGBE_RXD_ERR_TCPE	0x40    /* TCP/UDP Checksum Error */
#घोषणा IXGBE_RXD_ERR_IPE	0x80    /* IP Checksum Error */
#घोषणा IXGBE_RXDADV_ERR_MASK	0xFFF00000 /* RDESC.ERRORS mask */
#घोषणा IXGBE_RXDADV_ERR_SHIFT	20         /* RDESC.ERRORS shअगरt */
#घोषणा IXGBE_RXDADV_ERR_HBO	0x00800000 /*Header Buffer Overflow */
#घोषणा IXGBE_RXDADV_ERR_CE	0x01000000 /* CRC Error */
#घोषणा IXGBE_RXDADV_ERR_LE	0x02000000 /* Length Error */
#घोषणा IXGBE_RXDADV_ERR_PE	0x08000000 /* Packet Error */
#घोषणा IXGBE_RXDADV_ERR_OSE	0x10000000 /* Oversize Error */
#घोषणा IXGBE_RXDADV_ERR_USE	0x20000000 /* Undersize Error */
#घोषणा IXGBE_RXDADV_ERR_TCPE	0x40000000 /* TCP/UDP Checksum Error */
#घोषणा IXGBE_RXDADV_ERR_IPE	0x80000000 /* IP Checksum Error */
#घोषणा IXGBE_RXD_VLAN_ID_MASK	0x0FFF  /* VLAN ID is in lower 12 bits */
#घोषणा IXGBE_RXD_PRI_MASK	0xE000  /* Priority is in upper 3 bits */
#घोषणा IXGBE_RXD_PRI_SHIFT	13
#घोषणा IXGBE_RXD_CFI_MASK	0x1000  /* CFI is bit 12 */
#घोषणा IXGBE_RXD_CFI_SHIFT	12

#घोषणा IXGBE_RXDADV_STAT_DD		IXGBE_RXD_STAT_DD  /* Done */
#घोषणा IXGBE_RXDADV_STAT_EOP		IXGBE_RXD_STAT_EOP /* End of Packet */
#घोषणा IXGBE_RXDADV_STAT_FLM		IXGBE_RXD_STAT_FLM /* FDir Match */
#घोषणा IXGBE_RXDADV_STAT_VP		IXGBE_RXD_STAT_VP  /* IEEE VLAN Pkt */
#घोषणा IXGBE_RXDADV_STAT_MASK		0x000FFFFF /* Stat/NEXTP: bit 0-19 */
#घोषणा IXGBE_RXDADV_STAT_FCखातापूर्णS	0x00000040 /* FCoE खातापूर्ण/SOF Stat */
#घोषणा IXGBE_RXDADV_STAT_FCSTAT	0x00000030 /* FCoE Pkt Stat */
#घोषणा IXGBE_RXDADV_STAT_FCSTAT_NOMTCH	0x00000000 /* 00: No Ctxt Match */
#घोषणा IXGBE_RXDADV_STAT_FCSTAT_NODDP	0x00000010 /* 01: Ctxt w/o DDP */
#घोषणा IXGBE_RXDADV_STAT_FCSTAT_FCPRSP	0x00000020 /* 10: Recv. FCP_RSP */
#घोषणा IXGBE_RXDADV_STAT_FCSTAT_DDP	0x00000030 /* 11: Ctxt w/ DDP */
#घोषणा IXGBE_RXDADV_STAT_SECP		0x00020000 /* IPsec/MACsec pkt found */

#घोषणा IXGBE_RXDADV_RSSTYPE_MASK	0x0000000F
#घोषणा IXGBE_RXDADV_PKTTYPE_MASK	0x0000FFF0
#घोषणा IXGBE_RXDADV_PKTTYPE_IPV4	0x00000010 /* IPv4 hdr present */
#घोषणा IXGBE_RXDADV_PKTTYPE_IPV6	0x00000040 /* IPv6 hdr present */
#घोषणा IXGBE_RXDADV_PKTTYPE_IPSEC_ESP	0x00001000 /* IPSec ESP */
#घोषणा IXGBE_RXDADV_PKTTYPE_IPSEC_AH	0x00002000 /* IPSec AH */
#घोषणा IXGBE_RXDADV_PKTTYPE_MASK_EX	0x0001FFF0
#घोषणा IXGBE_RXDADV_HDRBUFLEN_MASK	0x00007FE0
#घोषणा IXGBE_RXDADV_RSCCNT_MASK	0x001E0000
#घोषणा IXGBE_RXDADV_RSCCNT_SHIFT	17
#घोषणा IXGBE_RXDADV_HDRBUFLEN_SHIFT	5
#घोषणा IXGBE_RXDADV_SPLITHEADER_EN	0x00001000
#घोषणा IXGBE_RXDADV_SPH		0x8000

/* RSS Hash results */
#घोषणा IXGBE_RXDADV_RSSTYPE_NONE		0x00000000
#घोषणा IXGBE_RXDADV_RSSTYPE_IPV4_TCP		0x00000001
#घोषणा IXGBE_RXDADV_RSSTYPE_IPV4		0x00000002
#घोषणा IXGBE_RXDADV_RSSTYPE_IPV6_TCP		0x00000003
#घोषणा IXGBE_RXDADV_RSSTYPE_IPV6_EX		0x00000004
#घोषणा IXGBE_RXDADV_RSSTYPE_IPV6		0x00000005
#घोषणा IXGBE_RXDADV_RSSTYPE_IPV6_TCP_EX	0x00000006
#घोषणा IXGBE_RXDADV_RSSTYPE_IPV4_UDP		0x00000007
#घोषणा IXGBE_RXDADV_RSSTYPE_IPV6_UDP		0x00000008
#घोषणा IXGBE_RXDADV_RSSTYPE_IPV6_UDP_EX	0x00000009

#घोषणा IXGBE_RXD_ERR_FRAME_ERR_MASK ( \
				      IXGBE_RXD_ERR_CE |  \
				      IXGBE_RXD_ERR_LE |  \
				      IXGBE_RXD_ERR_PE |  \
				      IXGBE_RXD_ERR_OSE | \
				      IXGBE_RXD_ERR_USE)

#घोषणा IXGBE_RXDADV_ERR_FRAME_ERR_MASK ( \
					 IXGBE_RXDADV_ERR_CE |  \
					 IXGBE_RXDADV_ERR_LE |  \
					 IXGBE_RXDADV_ERR_PE |  \
					 IXGBE_RXDADV_ERR_OSE | \
					 IXGBE_RXDADV_ERR_USE)

#घोषणा IXGBE_TXD_POPTS_IXSM	0x01       /* Insert IP checksum */
#घोषणा IXGBE_TXD_POPTS_TXSM	0x02       /* Insert TCP/UDP checksum */
#घोषणा IXGBE_TXD_CMD_EOP	0x01000000 /* End of Packet */
#घोषणा IXGBE_TXD_CMD_IFCS	0x02000000 /* Insert FCS (Ethernet CRC) */
#घोषणा IXGBE_TXD_CMD_IC	0x04000000 /* Insert Checksum */
#घोषणा IXGBE_TXD_CMD_RS	0x08000000 /* Report Status */
#घोषणा IXGBE_TXD_CMD_DEXT	0x20000000 /* Descriptor ext (0 = legacy) */
#घोषणा IXGBE_TXD_CMD_VLE	0x40000000 /* Add VLAN tag */
#घोषणा IXGBE_TXD_STAT_DD	0x00000001 /* Descriptor Done */
#घोषणा IXGBE_TXD_CMD		(IXGBE_TXD_CMD_EOP | IXGBE_TXD_CMD_RS)

/* Transmit Descriptor - Advanced */
जोड़ ixgbe_adv_tx_desc अणु
	काष्ठा अणु
		__le64 buffer_addr;      /* Address of descriptor's data buf */
		__le32 cmd_type_len;
		__le32 olinfo_status;
	पूर्ण पढ़ो;
	काष्ठा अणु
		__le64 rsvd;       /* Reserved */
		__le32 nxtseq_seed;
		__le32 status;
	पूर्ण wb;
पूर्ण;

/* Receive Descriptor - Advanced */
जोड़ ixgbe_adv_rx_desc अणु
	काष्ठा अणु
		__le64 pkt_addr; /* Packet buffer address */
		__le64 hdr_addr; /* Header buffer address */
	पूर्ण पढ़ो;
	काष्ठा अणु
		काष्ठा अणु
			जोड़ अणु
				__le32 data;
				काष्ठा अणु
					__le16 pkt_info; /* RSS, Pkt type */
					__le16 hdr_info; /* Splithdr, hdrlen */
				पूर्ण hs_rss;
			पूर्ण lo_dword;
			जोड़ अणु
				__le32 rss; /* RSS Hash */
				काष्ठा अणु
					__le16 ip_id; /* IP id */
					__le16 csum; /* Packet Checksum */
				पूर्ण csum_ip;
			पूर्ण hi_dword;
		पूर्ण lower;
		काष्ठा अणु
			__le32 status_error; /* ext status/error */
			__le16 length; /* Packet length */
			__le16 vlan; /* VLAN tag */
		पूर्ण upper;
	पूर्ण wb;  /* ग_लिखोback */
पूर्ण;

/* Context descriptors */
काष्ठा ixgbe_adv_tx_context_desc अणु
	__le32 vlan_macip_lens;
	__le32 fceof_saidx;
	__le32 type_tucmd_mlhl;
	__le32 mss_l4len_idx;
पूर्ण;

/* Adv Transmit Descriptor Config Masks */
#घोषणा IXGBE_ADVTXD_DTYP_MASK	0x00F00000 /* DTYP mask */
#घोषणा IXGBE_ADVTXD_DTYP_CTXT	0x00200000 /* Advanced Context Desc */
#घोषणा IXGBE_ADVTXD_DTYP_DATA	0x00300000 /* Advanced Data Descriptor */
#घोषणा IXGBE_ADVTXD_DCMD_EOP	IXGBE_TXD_CMD_EOP  /* End of Packet */
#घोषणा IXGBE_ADVTXD_DCMD_IFCS	IXGBE_TXD_CMD_IFCS /* Insert FCS */
#घोषणा IXGBE_ADVTXD_DCMD_RS	IXGBE_TXD_CMD_RS   /* Report Status */
#घोषणा IXGBE_ADVTXD_DCMD_DEXT	IXGBE_TXD_CMD_DEXT /* Desc ext (1=Adv) */
#घोषणा IXGBE_ADVTXD_DCMD_VLE	IXGBE_TXD_CMD_VLE  /* VLAN pkt enable */
#घोषणा IXGBE_ADVTXD_DCMD_TSE	0x80000000 /* TCP Seg enable */
#घोषणा IXGBE_ADVTXD_STAT_DD	IXGBE_TXD_STAT_DD  /* Descriptor Done */
#घोषणा IXGBE_ADVTXD_TUCMD_IPV4	0x00000400  /* IP Packet Type: 1=IPv4 */
#घोषणा IXGBE_ADVTXD_TUCMD_IPV6	0x00000000  /* IP Packet Type: 0=IPv6 */
#घोषणा IXGBE_ADVTXD_TUCMD_L4T_UDP	0x00000000  /* L4 Packet TYPE of UDP */
#घोषणा IXGBE_ADVTXD_TUCMD_L4T_TCP	0x00000800  /* L4 Packet TYPE of TCP */
#घोषणा IXGBE_ADVTXD_TUCMD_L4T_SCTP	0x00001000  /* L4 Packet TYPE of SCTP */
#घोषणा IXGBE_ADVTXD_TUCMD_IPSEC_TYPE_ESP   0x00002000 /* IPSec Type ESP */
#घोषणा IXGBE_ADVTXD_TUCMD_IPSEC_ENCRYPT_EN 0x00004000 /* ESP Encrypt Enable */
#घोषणा IXGBE_ADVTXD_IDX_SHIFT	4 /* Adv desc Index shअगरt */
#घोषणा IXGBE_ADVTXD_CC		0x00000080 /* Check Context */
#घोषणा IXGBE_ADVTXD_POPTS_SHIFT	8  /* Adv desc POPTS shअगरt */
#घोषणा IXGBE_ADVTXD_POPTS_IPSEC	0x00000400 /* IPSec offload request */
#घोषणा IXGBE_ADVTXD_POPTS_IXSM	(IXGBE_TXD_POPTS_IXSM << \
				 IXGBE_ADVTXD_POPTS_SHIFT)
#घोषणा IXGBE_ADVTXD_POPTS_TXSM	(IXGBE_TXD_POPTS_TXSM << \
				 IXGBE_ADVTXD_POPTS_SHIFT)
#घोषणा IXGBE_ADVTXD_PAYLEN_SHIFT	14 /* Adv desc PAYLEN shअगरt */
#घोषणा IXGBE_ADVTXD_MACLEN_SHIFT	9  /* Adv ctxt desc mac len shअगरt */
#घोषणा IXGBE_ADVTXD_VLAN_SHIFT		16 /* Adv ctxt vlan tag shअगरt */
#घोषणा IXGBE_ADVTXD_L4LEN_SHIFT	8  /* Adv ctxt L4LEN shअगरt */
#घोषणा IXGBE_ADVTXD_MSS_SHIFT		16 /* Adv ctxt MSS shअगरt */

/* Interrupt रेजिस्टर biपंचांगasks */

#घोषणा IXGBE_EITR_CNT_WDIS	0x80000000
#घोषणा IXGBE_MAX_EITR		0x00000FF8
#घोषणा IXGBE_MIN_EITR		8

/* Error Codes */
#घोषणा IXGBE_ERR_INVALID_MAC_ADDR	-1
#घोषणा IXGBE_ERR_RESET_FAILED		-2
#घोषणा IXGBE_ERR_INVALID_ARGUMENT	-3

/* Transmit Config masks */
#घोषणा IXGBE_TXDCTL_ENABLE		0x02000000 /* Ena specअगरic Tx Queue */
#घोषणा IXGBE_TXDCTL_SWFLSH		0x04000000 /* Tx Desc. wr-bk flushing */
#घोषणा IXGBE_TXDCTL_WTHRESH_SHIFT	16	   /* shअगरt to WTHRESH bits */

#घोषणा IXGBE_DCA_RXCTRL_DESC_DCA_EN	BIT(5)  /* Rx Desc enable */
#घोषणा IXGBE_DCA_RXCTRL_HEAD_DCA_EN	BIT(6)  /* Rx Desc header ena */
#घोषणा IXGBE_DCA_RXCTRL_DATA_DCA_EN	BIT(7)  /* Rx Desc payload ena */
#घोषणा IXGBE_DCA_RXCTRL_DESC_RRO_EN	BIT(9)  /* Rx rd Desc Relax Order */
#घोषणा IXGBE_DCA_RXCTRL_DATA_WRO_EN	BIT(13) /* Rx wr data Relax Order */
#घोषणा IXGBE_DCA_RXCTRL_HEAD_WRO_EN	BIT(15) /* Rx wr header RO */

#घोषणा IXGBE_DCA_TXCTRL_DESC_DCA_EN	BIT(5)  /* DCA Tx Desc enable */
#घोषणा IXGBE_DCA_TXCTRL_DESC_RRO_EN	BIT(9)  /* Tx rd Desc Relax Order */
#घोषणा IXGBE_DCA_TXCTRL_DESC_WRO_EN	BIT(11) /* Tx Desc ग_लिखोback RO bit */
#घोषणा IXGBE_DCA_TXCTRL_DATA_RRO_EN	BIT(13) /* Tx rd data Relax Order */

#पूर्ण_अगर /* _IXGBEVF_DEFINES_H_ */
