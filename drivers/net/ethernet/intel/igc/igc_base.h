<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/* Copyright (c)  2018 Intel Corporation */

#अगर_अघोषित _IGC_BASE_H_
#घोषणा _IGC_BASE_H_

/* क्रमward declaration */
व्योम igc_rx_fअगरo_flush_base(काष्ठा igc_hw *hw);
व्योम igc_घातer_करोwn_phy_copper_base(काष्ठा igc_hw *hw);

/* Transmit Descriptor - Advanced */
जोड़ igc_adv_tx_desc अणु
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

/* Context descriptors */
काष्ठा igc_adv_tx_context_desc अणु
	__le32 vlan_macip_lens;
	__le32 launch_समय;
	__le32 type_tucmd_mlhl;
	__le32 mss_l4len_idx;
पूर्ण;

/* Adv Transmit Descriptor Config Masks */
#घोषणा IGC_ADVTXD_MAC_TSTAMP	0x00080000 /* IEEE1588 Timestamp packet */
#घोषणा IGC_ADVTXD_DTYP_CTXT	0x00200000 /* Advanced Context Descriptor */
#घोषणा IGC_ADVTXD_DTYP_DATA	0x00300000 /* Advanced Data Descriptor */
#घोषणा IGC_ADVTXD_DCMD_EOP	0x01000000 /* End of Packet */
#घोषणा IGC_ADVTXD_DCMD_IFCS	0x02000000 /* Insert FCS (Ethernet CRC) */
#घोषणा IGC_ADVTXD_DCMD_RS	0x08000000 /* Report Status */
#घोषणा IGC_ADVTXD_DCMD_DEXT	0x20000000 /* Descriptor extension (1=Adv) */
#घोषणा IGC_ADVTXD_DCMD_VLE	0x40000000 /* VLAN pkt enable */
#घोषणा IGC_ADVTXD_DCMD_TSE	0x80000000 /* TCP Seg enable */
#घोषणा IGC_ADVTXD_PAYLEN_SHIFT	14 /* Adv desc PAYLEN shअगरt */

#घोषणा IGC_RAR_ENTRIES		16

/* Receive Descriptor - Advanced */
जोड़ igc_adv_rx_desc अणु
	काष्ठा अणु
		__le64 pkt_addr; /* Packet buffer address */
		__le64 hdr_addr; /* Header buffer address */
	पूर्ण पढ़ो;
	काष्ठा अणु
		काष्ठा अणु
			जोड़ अणु
				__le32 data;
				काष्ठा अणु
					__le16 pkt_info; /*RSS type, Pkt type*/
					/* Split Header, header buffer len */
					__le16 hdr_info;
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

/* Additional Transmit Descriptor Control definitions */
#घोषणा IGC_TXDCTL_QUEUE_ENABLE	0x02000000 /* Ena specअगरic Tx Queue */

/* Additional Receive Descriptor Control definitions */
#घोषणा IGC_RXDCTL_QUEUE_ENABLE	0x02000000 /* Ena specअगरic Rx Queue */

/* SRRCTL bit definitions */
#घोषणा IGC_SRRCTL_BSIZEPKT_SHIFT		10 /* Shअगरt _right_ */
#घोषणा IGC_SRRCTL_BSIZEHDRSIZE_SHIFT		2  /* Shअगरt _left_ */
#घोषणा IGC_SRRCTL_DESCTYPE_ADV_ONEBUF	0x02000000

#पूर्ण_अगर /* _IGC_BASE_H */
