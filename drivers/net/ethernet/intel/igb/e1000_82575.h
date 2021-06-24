<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/* Copyright(c) 2007 - 2018 Intel Corporation. */

#अगर_अघोषित _E1000_82575_H_
#घोषणा _E1000_82575_H_

व्योम igb_shutकरोwn_serdes_link_82575(काष्ठा e1000_hw *hw);
व्योम igb_घातer_up_serdes_link_82575(काष्ठा e1000_hw *hw);
व्योम igb_घातer_करोwn_phy_copper_82575(काष्ठा e1000_hw *hw);
व्योम igb_rx_fअगरo_flush_82575(काष्ठा e1000_hw *hw);
s32 igb_पढ़ो_i2c_byte(काष्ठा e1000_hw *hw, u8 byte_offset, u8 dev_addr,
		      u8 *data);
s32 igb_ग_लिखो_i2c_byte(काष्ठा e1000_hw *hw, u8 byte_offset, u8 dev_addr,
		       u8 data);

#घोषणा ID_LED_DEFAULT_82575_SERDES ((ID_LED_DEF1_DEF2 << 12) | \
				     (ID_LED_DEF1_DEF2 <<  8) | \
				     (ID_LED_DEF1_DEF2 <<  4) | \
				     (ID_LED_OFF1_ON2))

#घोषणा E1000_RAR_ENTRIES_82575        16
#घोषणा E1000_RAR_ENTRIES_82576        24
#घोषणा E1000_RAR_ENTRIES_82580        24
#घोषणा E1000_RAR_ENTRIES_I350         32

#घोषणा E1000_SW_SYNCH_MB              0x00000100
#घोषणा E1000_STAT_DEV_RST_SET         0x00100000
#घोषणा E1000_CTRL_DEV_RST             0x20000000

/* SRRCTL bit definitions */
#घोषणा E1000_SRRCTL_BSIZEPKT_SHIFT                     10 /* Shअगरt _right_ */
#घोषणा E1000_SRRCTL_BSIZEHDRSIZE_SHIFT                 2  /* Shअगरt _left_ */
#घोषणा E1000_SRRCTL_DESCTYPE_ADV_ONEBUF                0x02000000
#घोषणा E1000_SRRCTL_DESCTYPE_HDR_SPLIT_ALWAYS          0x0A000000
#घोषणा E1000_SRRCTL_DROP_EN                            0x80000000
#घोषणा E1000_SRRCTL_TIMESTAMP                          0x40000000


#घोषणा E1000_MRQC_ENABLE_RSS_MQ            0x00000002
#घोषणा E1000_MRQC_ENABLE_VMDQ              0x00000003
#घोषणा E1000_MRQC_RSS_FIELD_IPV4_UDP       0x00400000
#घोषणा E1000_MRQC_ENABLE_VMDQ_RSS_MQ       0x00000005
#घोषणा E1000_MRQC_RSS_FIELD_IPV6_UDP       0x00800000
#घोषणा E1000_MRQC_RSS_FIELD_IPV6_UDP_EX    0x01000000

#घोषणा E1000_EICR_TX_QUEUE ( \
	E1000_EICR_TX_QUEUE0 |    \
	E1000_EICR_TX_QUEUE1 |    \
	E1000_EICR_TX_QUEUE2 |    \
	E1000_EICR_TX_QUEUE3)

#घोषणा E1000_EICR_RX_QUEUE ( \
	E1000_EICR_RX_QUEUE0 |    \
	E1000_EICR_RX_QUEUE1 |    \
	E1000_EICR_RX_QUEUE2 |    \
	E1000_EICR_RX_QUEUE3)

/* Immediate Interrupt Rx (A.K.A. Low Latency Interrupt) */
#घोषणा E1000_IMIREXT_SIZE_BP     0x00001000  /* Packet size bypass */
#घोषणा E1000_IMIREXT_CTRL_BP     0x00080000  /* Bypass check of ctrl bits */

/* Receive Descriptor - Advanced */
जोड़ e1000_adv_rx_desc अणु
	काष्ठा अणु
		__le64 pkt_addr;             /* Packet buffer address */
		__le64 hdr_addr;             /* Header buffer address */
	पूर्ण पढ़ो;
	काष्ठा अणु
		काष्ठा अणु
			काष्ठा अणु
				__le16 pkt_info;   /* RSS type, Packet type */
				__le16 hdr_info;   /* Split Head, buf len */
			पूर्ण lo_dword;
			जोड़ अणु
				__le32 rss;          /* RSS Hash */
				काष्ठा अणु
					__le16 ip_id;    /* IP id */
					__le16 csum;     /* Packet Checksum */
				पूर्ण csum_ip;
			पूर्ण hi_dword;
		पूर्ण lower;
		काष्ठा अणु
			__le32 status_error;     /* ext status/error */
			__le16 length;           /* Packet length */
			__le16 vlan;             /* VLAN tag */
		पूर्ण upper;
	पूर्ण wb;  /* ग_लिखोback */
पूर्ण;

#घोषणा E1000_RXDADV_HDRBUFLEN_MASK      0x7FE0
#घोषणा E1000_RXDADV_HDRBUFLEN_SHIFT     5
#घोषणा E1000_RXDADV_STAT_TS             0x10000 /* Pkt was समय stamped */
#घोषणा E1000_RXDADV_STAT_TSIP           0x08000 /* बारtamp in packet */

/* Transmit Descriptor - Advanced */
जोड़ e1000_adv_tx_desc अणु
	काष्ठा अणु
		__le64 buffer_addr;    /* Address of descriptor's data buf */
		__le32 cmd_type_len;
		__le32 olinfo_status;
	पूर्ण पढ़ो;
	काष्ठा अणु
		__le64 rsvd;       /* Reserved */
		__le32 nxtseq_seed;
		__le32 status;
	पूर्ण wb;
पूर्ण;

/* Adv Transmit Descriptor Config Masks */
#घोषणा E1000_ADVTXD_MAC_TSTAMP   0x00080000 /* IEEE1588 Timestamp packet */
#घोषणा E1000_ADVTXD_DTYP_CTXT    0x00200000 /* Advanced Context Descriptor */
#घोषणा E1000_ADVTXD_DTYP_DATA    0x00300000 /* Advanced Data Descriptor */
#घोषणा E1000_ADVTXD_DCMD_EOP     0x01000000 /* End of Packet */
#घोषणा E1000_ADVTXD_DCMD_IFCS    0x02000000 /* Insert FCS (Ethernet CRC) */
#घोषणा E1000_ADVTXD_DCMD_RS      0x08000000 /* Report Status */
#घोषणा E1000_ADVTXD_DCMD_DEXT    0x20000000 /* Descriptor extension (1=Adv) */
#घोषणा E1000_ADVTXD_DCMD_VLE     0x40000000 /* VLAN pkt enable */
#घोषणा E1000_ADVTXD_DCMD_TSE     0x80000000 /* TCP Seg enable */
#घोषणा E1000_ADVTXD_PAYLEN_SHIFT    14 /* Adv desc PAYLEN shअगरt */

/* Context descriptors */
काष्ठा e1000_adv_tx_context_desc अणु
	__le32 vlan_macip_lens;
	__le32 seqnum_seed;
	__le32 type_tucmd_mlhl;
	__le32 mss_l4len_idx;
पूर्ण;

#घोषणा E1000_ADVTXD_MACLEN_SHIFT    9  /* Adv ctxt desc mac len shअगरt */
#घोषणा E1000_ADVTXD_TUCMD_L4T_UDP 0x00000000  /* L4 Packet TYPE of UDP */
#घोषणा E1000_ADVTXD_TUCMD_IPV4    0x00000400  /* IP Packet Type: 1=IPv4 */
#घोषणा E1000_ADVTXD_TUCMD_L4T_TCP 0x00000800  /* L4 Packet TYPE of TCP */
#घोषणा E1000_ADVTXD_TUCMD_L4T_SCTP 0x00001000 /* L4 packet TYPE of SCTP */
/* IPSec Encrypt Enable क्रम ESP */
#घोषणा E1000_ADVTXD_L4LEN_SHIFT     8  /* Adv ctxt L4LEN shअगरt */
#घोषणा E1000_ADVTXD_MSS_SHIFT      16  /* Adv ctxt MSS shअगरt */
/* Adv ctxt IPSec SA IDX mask */
/* Adv ctxt IPSec ESP len mask */

/* Additional Transmit Descriptor Control definitions */
#घोषणा E1000_TXDCTL_QUEUE_ENABLE  0x02000000 /* Enable specअगरic Tx Queue */
/* Tx Queue Arbitration Priority 0=low, 1=high */

/* Additional Receive Descriptor Control definitions */
#घोषणा E1000_RXDCTL_QUEUE_ENABLE  0x02000000 /* Enable specअगरic Rx Queue */

/* Direct Cache Access (DCA) definitions */
#घोषणा E1000_DCA_CTRL_DCA_MODE_DISABLE 0x01 /* DCA Disable */
#घोषणा E1000_DCA_CTRL_DCA_MODE_CB2     0x02 /* DCA Mode CB2 */

#घोषणा E1000_DCA_RXCTRL_CPUID_MASK 0x0000001F /* Rx CPUID Mask */
#घोषणा E1000_DCA_RXCTRL_DESC_DCA_EN BIT(5) /* DCA Rx Desc enable */
#घोषणा E1000_DCA_RXCTRL_HEAD_DCA_EN BIT(6) /* DCA Rx Desc header enable */
#घोषणा E1000_DCA_RXCTRL_DATA_DCA_EN BIT(7) /* DCA Rx Desc payload enable */
#घोषणा E1000_DCA_RXCTRL_DESC_RRO_EN BIT(9) /* DCA Rx rd Desc Relax Order */

#घोषणा E1000_DCA_TXCTRL_CPUID_MASK 0x0000001F /* Tx CPUID Mask */
#घोषणा E1000_DCA_TXCTRL_DESC_DCA_EN BIT(5) /* DCA Tx Desc enable */
#घोषणा E1000_DCA_TXCTRL_DESC_RRO_EN BIT(9) /* Tx rd Desc Relax Order */
#घोषणा E1000_DCA_TXCTRL_TX_WB_RO_EN BIT(11) /* Tx Desc ग_लिखोback RO bit */
#घोषणा E1000_DCA_TXCTRL_DATA_RRO_EN BIT(13) /* Tx rd data Relax Order */

/* Additional DCA related definitions, note change in position of CPUID */
#घोषणा E1000_DCA_TXCTRL_CPUID_MASK_82576 0xFF000000 /* Tx CPUID Mask */
#घोषणा E1000_DCA_RXCTRL_CPUID_MASK_82576 0xFF000000 /* Rx CPUID Mask */
#घोषणा E1000_DCA_TXCTRL_CPUID_SHIFT 24 /* Tx CPUID now in the last byte */
#घोषणा E1000_DCA_RXCTRL_CPUID_SHIFT 24 /* Rx CPUID now in the last byte */

/* ETQF रेजिस्टर bit definitions */
#घोषणा E1000_ETQF_FILTER_ENABLE   BIT(26)
#घोषणा E1000_ETQF_1588            BIT(30)
#घोषणा E1000_ETQF_IMM_INT         BIT(29)
#घोषणा E1000_ETQF_QUEUE_ENABLE    BIT(31)
#घोषणा E1000_ETQF_QUEUE_SHIFT     16
#घोषणा E1000_ETQF_QUEUE_MASK      0x00070000
#घोषणा E1000_ETQF_ETYPE_MASK      0x0000FFFF

/* FTQF रेजिस्टर bit definitions */
#घोषणा E1000_FTQF_VF_BP               0x00008000
#घोषणा E1000_FTQF_1588_TIME_STAMP     0x08000000
#घोषणा E1000_FTQF_MASK                0xF0000000
#घोषणा E1000_FTQF_MASK_PROTO_BP       0x10000000
#घोषणा E1000_FTQF_MASK_SOURCE_PORT_BP 0x80000000

#घोषणा E1000_NVM_APME_82575          0x0400
#घोषणा MAX_NUM_VFS                   8

#घोषणा E1000_DTXSWC_MAC_SPOOF_MASK   0x000000FF /* Per VF MAC spoof control */
#घोषणा E1000_DTXSWC_VLAN_SPOOF_MASK  0x0000FF00 /* Per VF VLAN spoof control */
#घोषणा E1000_DTXSWC_LLE_MASK         0x00FF0000 /* Per VF Local LB enables */
#घोषणा E1000_DTXSWC_VLAN_SPOOF_SHIFT 8
#घोषणा E1000_DTXSWC_VMDQ_LOOPBACK_EN BIT(31)  /* global VF LB enable */

/* Easy defines क्रम setting शेष pool, would normally be left a zero */
#घोषणा E1000_VT_CTL_DEFAULT_POOL_SHIFT 7
#घोषणा E1000_VT_CTL_DEFAULT_POOL_MASK  (0x7 << E1000_VT_CTL_DEFAULT_POOL_SHIFT)

/* Other useful VMD_CTL रेजिस्टर defines */
#घोषणा E1000_VT_CTL_IGNORE_MAC         BIT(28)
#घोषणा E1000_VT_CTL_DISABLE_DEF_POOL   BIT(29)
#घोषणा E1000_VT_CTL_VM_REPL_EN         BIT(30)

/* Per VM Offload रेजिस्टर setup */
#घोषणा E1000_VMOLR_RLPML_MASK 0x00003FFF /* Long Packet Maximum Length mask */
#घोषणा E1000_VMOLR_LPE        0x00010000 /* Accept Long packet */
#घोषणा E1000_VMOLR_RSSE       0x00020000 /* Enable RSS */
#घोषणा E1000_VMOLR_AUPE       0x01000000 /* Accept untagged packets */
#घोषणा E1000_VMOLR_ROMPE      0x02000000 /* Accept overflow multicast */
#घोषणा E1000_VMOLR_ROPE       0x04000000 /* Accept overflow unicast */
#घोषणा E1000_VMOLR_BAM        0x08000000 /* Accept Broadcast packets */
#घोषणा E1000_VMOLR_MPME       0x10000000 /* Multicast promiscuous mode */
#घोषणा E1000_VMOLR_STRVLAN    0x40000000 /* Vlan stripping enable */
#घोषणा E1000_VMOLR_STRCRC     0x80000000 /* CRC stripping enable */

#घोषणा E1000_DVMOLR_HIDEVLAN  0x20000000 /* Hide vlan enable */
#घोषणा E1000_DVMOLR_STRVLAN   0x40000000 /* Vlan stripping enable */
#घोषणा E1000_DVMOLR_STRCRC    0x80000000 /* CRC stripping enable */

#घोषणा E1000_VLVF_ARRAY_SIZE     32
#घोषणा E1000_VLVF_VLANID_MASK    0x00000FFF
#घोषणा E1000_VLVF_POOLSEL_SHIFT  12
#घोषणा E1000_VLVF_POOLSEL_MASK   (0xFF << E1000_VLVF_POOLSEL_SHIFT)
#घोषणा E1000_VLVF_LVLAN          0x00100000
#घोषणा E1000_VLVF_VLANID_ENABLE  0x80000000

#घोषणा E1000_VMVIR_VLANA_DEFAULT      0x40000000 /* Always use शेष VLAN */
#घोषणा E1000_VMVIR_VLANA_NEVER        0x80000000 /* Never insert VLAN tag */

#घोषणा E1000_IOVCTL 0x05BBC
#घोषणा E1000_IOVCTL_REUSE_VFQ 0x00000001

#घोषणा E1000_RPLOLR_STRVLAN   0x40000000
#घोषणा E1000_RPLOLR_STRCRC    0x80000000

#घोषणा E1000_DTXCTL_8023LL     0x0004
#घोषणा E1000_DTXCTL_VLAN_ADDED 0x0008
#घोषणा E1000_DTXCTL_OOS_ENABLE 0x0010
#घोषणा E1000_DTXCTL_MDP_EN     0x0020
#घोषणा E1000_DTXCTL_SPOOF_INT  0x0040

#घोषणा E1000_EEPROM_PCS_AUTONEG_DISABLE_BIT	BIT(14)

#घोषणा ALL_QUEUES   0xFFFF

/* RX packet buffer size defines */
#घोषणा E1000_RXPBS_SIZE_MASK_82576  0x0000007F
व्योम igb_vmdq_set_anti_spoofing_pf(काष्ठा e1000_hw *, bool, पूर्णांक);
व्योम igb_vmdq_set_loopback_pf(काष्ठा e1000_hw *, bool);
व्योम igb_vmdq_set_replication_pf(काष्ठा e1000_hw *, bool);
u16 igb_rxpbs_adjust_82580(u32 data);
s32 igb_पढ़ो_emi_reg(काष्ठा e1000_hw *, u16 addr, u16 *data);
s32 igb_set_eee_i350(काष्ठा e1000_hw *, bool adv1G, bool adv100M);
s32 igb_set_eee_i354(काष्ठा e1000_hw *, bool adv1G, bool adv100M);
s32 igb_get_eee_status_i354(काष्ठा e1000_hw *hw, bool *status);

#घोषणा E1000_I2C_THERMAL_SENSOR_ADDR	0xF8
#घोषणा E1000_EMC_INTERNAL_DATA		0x00
#घोषणा E1000_EMC_INTERNAL_THERM_LIMIT	0x20
#घोषणा E1000_EMC_DIODE1_DATA		0x01
#घोषणा E1000_EMC_DIODE1_THERM_LIMIT	0x19
#घोषणा E1000_EMC_DIODE2_DATA		0x23
#घोषणा E1000_EMC_DIODE2_THERM_LIMIT	0x1A
#घोषणा E1000_EMC_DIODE3_DATA		0x2A
#घोषणा E1000_EMC_DIODE3_THERM_LIMIT	0x30
#पूर्ण_अगर
