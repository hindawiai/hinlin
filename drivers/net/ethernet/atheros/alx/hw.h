<शैली गुरु>
/*
 * Copyright (c) 2013 Johannes Berg <johannes@sipsolutions.net>
 *
 *  This file is मुक्त software: you may copy, redistribute and/or modअगरy it
 *  under the terms of the GNU General Public License as published by the
 *  Free Software Foundation, either version 2 of the License, or (at your
 *  option) any later version.
 *
 *  This file is distributed in the hope that it will be useful, but
 *  WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 *  General Public License क्रम more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  aदीर्घ with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 * This file incorporates work covered by the following copyright and
 * permission notice:
 *
 * Copyright (c) 2012 Qualcomm Atheros, Inc.
 *
 * Permission to use, copy, modअगरy, and/or distribute this software क्रम any
 * purpose with or without fee is hereby granted, provided that the above
 * copyright notice and this permission notice appear in all copies.
 *
 * THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
 * WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR
 * ANY SPECIAL, सूचीECT, INसूचीECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
 * WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN
 * ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF
 * OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
 */

#अगर_अघोषित ALX_HW_H_
#घोषणा ALX_HW_H_
#समावेश <linux/types.h>
#समावेश <linux/mdपन.स>
#समावेश <linux/pci.h>
#समावेश <linux/अगर_vlan.h>
#समावेश "reg.h"

/* Transmit Packet Descriptor, contains 4 32-bit words.
 *
 *   31               16               0
 *   +----------------+----------------+
 *   |    vlan-tag    |   buf length   |
 *   +----------------+----------------+
 *   |              Word 1             |
 *   +----------------+----------------+
 *   |      Word 2: buf addr lo        |
 *   +----------------+----------------+
 *   |      Word 3: buf addr hi        |
 *   +----------------+----------------+
 *
 * Word 2 and 3 combine to क्रमm a 64-bit buffer address
 *
 * Word 1 has three क्रमms, depending on the state of bit 8/12/13:
 * अगर bit8 =='1', the definition is just क्रम custom checksum offload.
 * अगर bit8 == '0' && bit12 == '1' && bit13 == '1', the *FIRST* descriptor
 *     क्रम the skb is special क्रम LSO V2, Word 2 become total skb length ,
 *     Word 3 is meaningless.
 * other condition, the definition is क्रम general skb or ip/tcp/udp
 *     checksum or LSO(TSO) offload.
 *
 * Here is the depiction:
 *
 *   0-+                                  0-+
 *   1 |                                  1 |
 *   2 |                                  2 |
 *   3 |    Payload offset                3 |    L4 header offset
 *   4 |        (7:0)                     4 |        (7:0)
 *   5 |                                  5 |
 *   6 |                                  6 |
 *   7-+                                  7-+
 *   8      Custom csum enable = 1        8      Custom csum enable = 0
 *   9      General IPv4 checksum         9      General IPv4 checksum
 *   10     General TCP checksum          10     General TCP checksum
 *   11     General UDP checksum          11     General UDP checksum
 *   12     Large Send Segment enable     12     Large Send Segment enable
 *   13     Large Send Segment type       13     Large Send Segment type
 *   14     VLAN tagged                   14     VLAN tagged
 *   15     Insert VLAN tag               15     Insert VLAN tag
 *   16     IPv4 packet                   16     IPv4 packet
 *   17     Ethernet frame type           17     Ethernet frame type
 *   18-+                                 18-+
 *   19 |                                 19 |
 *   20 |                                 20 |
 *   21 |   Custom csum offset            21 |
 *   22 |       (25:18)                   22 |
 *   23 |                                 23 |   MSS (30:18)
 *   24 |                                 24 |
 *   25-+                                 25 |
 *   26-+                                 26 |
 *   27 |                                 27 |
 *   28 |   Reserved                      28 |
 *   29 |                                 29 |
 *   30-+                                 30-+
 *   31     End of packet                 31     End of packet
 */
काष्ठा alx_txd अणु
	__le16 len;
	__le16 vlan_tag;
	__le32 word1;
	जोड़ अणु
		__le64 addr;
		काष्ठा अणु
			__le32 pkt_len;
			__le32 resvd;
		पूर्ण l;
	पूर्ण adrl;
पूर्ण __packed;

/* tpd word 1 */
#घोषणा TPD_CXSUMSTART_MASK		0x00FF
#घोषणा TPD_CXSUMSTART_SHIFT		0
#घोषणा TPD_L4HDROFFSET_MASK		0x00FF
#घोषणा TPD_L4HDROFFSET_SHIFT		0
#घोषणा TPD_CXSUM_EN_MASK		0x0001
#घोषणा TPD_CXSUM_EN_SHIFT		8
#घोषणा TPD_IP_XSUM_MASK		0x0001
#घोषणा TPD_IP_XSUM_SHIFT		9
#घोषणा TPD_TCP_XSUM_MASK		0x0001
#घोषणा TPD_TCP_XSUM_SHIFT		10
#घोषणा TPD_UDP_XSUM_MASK		0x0001
#घोषणा TPD_UDP_XSUM_SHIFT		11
#घोषणा TPD_LSO_EN_MASK			0x0001
#घोषणा TPD_LSO_EN_SHIFT		12
#घोषणा TPD_LSO_V2_MASK			0x0001
#घोषणा TPD_LSO_V2_SHIFT		13
#घोषणा TPD_VLTAGGED_MASK		0x0001
#घोषणा TPD_VLTAGGED_SHIFT		14
#घोषणा TPD_INS_VLTAG_MASK		0x0001
#घोषणा TPD_INS_VLTAG_SHIFT		15
#घोषणा TPD_IPV4_MASK			0x0001
#घोषणा TPD_IPV4_SHIFT			16
#घोषणा TPD_ETHTYPE_MASK		0x0001
#घोषणा TPD_ETHTYPE_SHIFT		17
#घोषणा TPD_CXSUMOFFSET_MASK		0x00FF
#घोषणा TPD_CXSUMOFFSET_SHIFT		18
#घोषणा TPD_MSS_MASK			0x1FFF
#घोषणा TPD_MSS_SHIFT			18
#घोषणा TPD_EOP_MASK			0x0001
#घोषणा TPD_EOP_SHIFT			31

#घोषणा DESC_GET(_x, _name) ((_x) >> _name##SHIFT & _name##MASK)

/* Receive Free Descriptor */
काष्ठा alx_rfd अणु
	__le64 addr;		/* data buffer address, length is
				 * declared in रेजिस्टर --- every
				 * buffer has the same size
				 */
पूर्ण __packed;

/* Receive Return Descriptor, contains 4 32-bit words.
 *
 *   31               16               0
 *   +----------------+----------------+
 *   |              Word 0             |
 *   +----------------+----------------+
 *   |     Word 1: RSS Hash value      |
 *   +----------------+----------------+
 *   |              Word 2             |
 *   +----------------+----------------+
 *   |              Word 3             |
 *   +----------------+----------------+
 *
 * Word 0 depiction         &            Word 2 depiction:
 *
 *   0--+                                 0--+
 *   1  |                                 1  |
 *   2  |                                 2  |
 *   3  |                                 3  |
 *   4  |                                 4  |
 *   5  |                                 5  |
 *   6  |                                 6  |
 *   7  |    IP payload checksum          7  |     VLAN tag
 *   8  |         (15:0)                  8  |      (15:0)
 *   9  |                                 9  |
 *   10 |                                 10 |
 *   11 |                                 11 |
 *   12 |                                 12 |
 *   13 |                                 13 |
 *   14 |                                 14 |
 *   15-+                                 15-+
 *   16-+                                 16-+
 *   17 |     Number of RFDs              17 |
 *   18 |        (19:16)                  18 |
 *   19-+                                 19 |     Protocol ID
 *   20-+                                 20 |      (23:16)
 *   21 |                                 21 |
 *   22 |                                 22 |
 *   23 |                                 23-+
 *   24 |                                 24 |     Reserved
 *   25 |     Start index of RFD-ring     25-+
 *   26 |         (31:20)                 26 |     RSS Q-num (27:25)
 *   27 |                                 27-+
 *   28 |                                 28-+
 *   29 |                                 29 |     RSS Hash algorithm
 *   30 |                                 30 |      (31:28)
 *   31-+                                 31-+
 *
 * Word 3 depiction:
 *
 *   0--+
 *   1  |
 *   2  |
 *   3  |
 *   4  |
 *   5  |
 *   6  |
 *   7  |    Packet length (include FCS)
 *   8  |         (13:0)
 *   9  |
 *   10 |
 *   11 |
 *   12 |
 *   13-+
 *   14      L4 Header checksum error
 *   15      IPv4 checksum error
 *   16      VLAN tagged
 *   17-+
 *   18 |    Protocol ID (19:17)
 *   19-+
 *   20      Receive error summary
 *   21      FCS(CRC) error
 *   22      Frame alignment error
 *   23      Truncated packet
 *   24      Runt packet
 *   25      Incomplete packet due to insufficient rx-desc
 *   26      Broadcast packet
 *   27      Multicast packet
 *   28      Ethernet type (EII or 802.3)
 *   29      FIFO overflow
 *   30      Length error (क्रम 802.3, length field mismatch with actual len)
 *   31      Updated, indicate to driver that this RRD is refreshed.
 */
काष्ठा alx_rrd अणु
	__le32 word0;
	__le32 rss_hash;
	__le32 word2;
	__le32 word3;
पूर्ण __packed;

/* rrd word 0 */
#घोषणा RRD_XSUM_MASK		0xFFFF
#घोषणा RRD_XSUM_SHIFT		0
#घोषणा RRD_NOR_MASK		0x000F
#घोषणा RRD_NOR_SHIFT		16
#घोषणा RRD_SI_MASK		0x0FFF
#घोषणा RRD_SI_SHIFT		20

/* rrd word 2 */
#घोषणा RRD_VLTAG_MASK		0xFFFF
#घोषणा RRD_VLTAG_SHIFT		0
#घोषणा RRD_PID_MASK		0x00FF
#घोषणा RRD_PID_SHIFT		16
/* non-ip packet */
#घोषणा RRD_PID_NONIP		0
/* ipv4(only) */
#घोषणा RRD_PID_IPV4		1
/* tcp/ipv6 */
#घोषणा RRD_PID_IPV6TCP		2
/* tcp/ipv4 */
#घोषणा RRD_PID_IPV4TCP		3
/* udp/ipv6 */
#घोषणा RRD_PID_IPV6UDP		4
/* udp/ipv4 */
#घोषणा RRD_PID_IPV4UDP		5
/* ipv6(only) */
#घोषणा RRD_PID_IPV6		6
/* LLDP packet */
#घोषणा RRD_PID_LLDP		7
/* 1588 packet */
#घोषणा RRD_PID_1588		8
#घोषणा RRD_RSSQ_MASK		0x0007
#घोषणा RRD_RSSQ_SHIFT		25
#घोषणा RRD_RSSALG_MASK		0x000F
#घोषणा RRD_RSSALG_SHIFT	28
#घोषणा RRD_RSSALG_TCPV6	0x1
#घोषणा RRD_RSSALG_IPV6		0x2
#घोषणा RRD_RSSALG_TCPV4	0x4
#घोषणा RRD_RSSALG_IPV4		0x8

/* rrd word 3 */
#घोषणा RRD_PKTLEN_MASK		0x3FFF
#घोषणा RRD_PKTLEN_SHIFT	0
#घोषणा RRD_ERR_L4_MASK		0x0001
#घोषणा RRD_ERR_L4_SHIFT	14
#घोषणा RRD_ERR_IPV4_MASK	0x0001
#घोषणा RRD_ERR_IPV4_SHIFT	15
#घोषणा RRD_VLTAGGED_MASK	0x0001
#घोषणा RRD_VLTAGGED_SHIFT	16
#घोषणा RRD_OLD_PID_MASK	0x0007
#घोषणा RRD_OLD_PID_SHIFT	17
#घोषणा RRD_ERR_RES_MASK	0x0001
#घोषणा RRD_ERR_RES_SHIFT	20
#घोषणा RRD_ERR_FCS_MASK	0x0001
#घोषणा RRD_ERR_FCS_SHIFT	21
#घोषणा RRD_ERR_FAE_MASK	0x0001
#घोषणा RRD_ERR_FAE_SHIFT	22
#घोषणा RRD_ERR_TRUNC_MASK	0x0001
#घोषणा RRD_ERR_TRUNC_SHIFT	23
#घोषणा RRD_ERR_RUNT_MASK	0x0001
#घोषणा RRD_ERR_RUNT_SHIFT	24
#घोषणा RRD_ERR_ICMP_MASK	0x0001
#घोषणा RRD_ERR_ICMP_SHIFT	25
#घोषणा RRD_BCAST_MASK		0x0001
#घोषणा RRD_BCAST_SHIFT		26
#घोषणा RRD_MCAST_MASK		0x0001
#घोषणा RRD_MCAST_SHIFT		27
#घोषणा RRD_ETHTYPE_MASK	0x0001
#घोषणा RRD_ETHTYPE_SHIFT	28
#घोषणा RRD_ERR_FIFOV_MASK	0x0001
#घोषणा RRD_ERR_FIFOV_SHIFT	29
#घोषणा RRD_ERR_LEN_MASK	0x0001
#घोषणा RRD_ERR_LEN_SHIFT	30
#घोषणा RRD_UPDATED_MASK	0x0001
#घोषणा RRD_UPDATED_SHIFT	31


#घोषणा ALX_MAX_SETUP_LNK_CYCLE	50

/* क्रम FlowControl */
#घोषणा ALX_FC_RX		0x01
#घोषणा ALX_FC_TX		0x02
#घोषणा ALX_FC_ANEG		0x04

/* क्रम sleep control */
#घोषणा ALX_SLEEP_WOL_PHY	0x00000001
#घोषणा ALX_SLEEP_WOL_MAGIC	0x00000002
#घोषणा ALX_SLEEP_CIFS		0x00000004
#घोषणा ALX_SLEEP_ACTIVE	(ALX_SLEEP_WOL_PHY | \
				 ALX_SLEEP_WOL_MAGIC | \
				 ALX_SLEEP_CIFS)

/* क्रम RSS hash type */
#घोषणा ALX_RSS_HASH_TYPE_IPV4		0x1
#घोषणा ALX_RSS_HASH_TYPE_IPV4_TCP	0x2
#घोषणा ALX_RSS_HASH_TYPE_IPV6		0x4
#घोषणा ALX_RSS_HASH_TYPE_IPV6_TCP	0x8
#घोषणा ALX_RSS_HASH_TYPE_ALL		(ALX_RSS_HASH_TYPE_IPV4 | \
					 ALX_RSS_HASH_TYPE_IPV4_TCP | \
					 ALX_RSS_HASH_TYPE_IPV6 | \
					 ALX_RSS_HASH_TYPE_IPV6_TCP)
#घोषणा ALX_FRAME_PAD		16
#घोषणा ALX_RAW_MTU(_mtu)	(_mtu + ETH_HLEN + ETH_FCS_LEN + VLAN_HLEN)
#घोषणा ALX_MAX_FRAME_LEN(_mtu)	(ALIGN((ALX_RAW_MTU(_mtu) + ALX_FRAME_PAD), 8))
#घोषणा ALX_DEF_RXBUF_SIZE	ALX_MAX_FRAME_LEN(1500)
#घोषणा ALX_MAX_JUMBO_PKT_SIZE	(9*1024)
#घोषणा ALX_MAX_TSO_PKT_SIZE	(7*1024)
#घोषणा ALX_MAX_FRAME_SIZE	ALX_MAX_JUMBO_PKT_SIZE

#घोषणा ALX_MAX_RX_QUEUES	8
#घोषणा ALX_MAX_TX_QUEUES	4
#घोषणा ALX_MAX_HANDLED_INTRS	5

#घोषणा ALX_ISR_MISC		(ALX_ISR_PCIE_LNKDOWN | \
				 ALX_ISR_DMAW | \
				 ALX_ISR_DMAR | \
				 ALX_ISR_SMB | \
				 ALX_ISR_MANU | \
				 ALX_ISR_TIMER)

#घोषणा ALX_ISR_FATAL		(ALX_ISR_PCIE_LNKDOWN | \
				 ALX_ISR_DMAW | ALX_ISR_DMAR)

#घोषणा ALX_ISR_ALERT		(ALX_ISR_RXF_OV | \
				 ALX_ISR_TXF_UR | \
				 ALX_ISR_RFD_UR)

#घोषणा ALX_ISR_ALL_QUEUES	(ALX_ISR_TX_Q0 | \
				 ALX_ISR_TX_Q1 | \
				 ALX_ISR_TX_Q2 | \
				 ALX_ISR_TX_Q3 | \
				 ALX_ISR_RX_Q0 | \
				 ALX_ISR_RX_Q1 | \
				 ALX_ISR_RX_Q2 | \
				 ALX_ISR_RX_Q3 | \
				 ALX_ISR_RX_Q4 | \
				 ALX_ISR_RX_Q5 | \
				 ALX_ISR_RX_Q6 | \
				 ALX_ISR_RX_Q7)

/* Statistics counters collected by the MAC
 *
 * The order of the fields must match the strings in alx_gstrings_stats
 * All stats fields should be u64
 * See ethtool.c
 */
काष्ठा alx_hw_stats अणु
	/* rx */
	u64 rx_ok;		/* good RX packets */
	u64 rx_bcast;		/* good RX broadcast packets */
	u64 rx_mcast;		/* good RX multicast packets */
	u64 rx_छोड़ो;		/* RX छोड़ो frames */
	u64 rx_ctrl;		/* RX control packets other than छोड़ो frames */
	u64 rx_fcs_err;		/* RX packets with bad FCS */
	u64 rx_len_err;		/* RX packets with length != actual size */
	u64 rx_byte_cnt;	/* good bytes received. FCS is NOT included */
	u64 rx_runt;		/* RX packets < 64 bytes with good FCS */
	u64 rx_frag;		/* RX packets < 64 bytes with bad FCS */
	u64 rx_sz_64B;		/* 64 byte RX packets */
	u64 rx_sz_127B;		/* 65-127 byte RX packets */
	u64 rx_sz_255B;		/* 128-255 byte RX packets */
	u64 rx_sz_511B;		/* 256-511 byte RX packets */
	u64 rx_sz_1023B;	/* 512-1023 byte RX packets */
	u64 rx_sz_1518B;	/* 1024-1518 byte RX packets */
	u64 rx_sz_max;		/* 1519 byte to MTU RX packets */
	u64 rx_ov_sz;		/* truncated RX packets, size > MTU */
	u64 rx_ov_rxf;		/* frames dropped due to RX FIFO overflow */
	u64 rx_ov_rrd;		/* frames dropped due to RRD overflow */
	u64 rx_align_err;	/* alignment errors */
	u64 rx_bc_byte_cnt;	/* RX broadcast bytes, excluding FCS */
	u64 rx_mc_byte_cnt;	/* RX multicast bytes, excluding FCS */
	u64 rx_err_addr;	/* packets dropped due to address filtering */

	/* tx */
	u64 tx_ok;		/* good TX packets */
	u64 tx_bcast;		/* good TX broadcast packets */
	u64 tx_mcast;		/* good TX multicast packets */
	u64 tx_छोड़ो;		/* TX छोड़ो frames */
	u64 tx_exc_defer;	/* TX packets deferred excessively */
	u64 tx_ctrl;		/* TX control frames, excluding छोड़ो frames */
	u64 tx_defer;		/* TX packets deferred */
	u64 tx_byte_cnt;	/* bytes transmitted, FCS is NOT included */
	u64 tx_sz_64B;		/* 64 byte TX packets */
	u64 tx_sz_127B;		/* 65-127 byte TX packets */
	u64 tx_sz_255B;		/* 128-255 byte TX packets */
	u64 tx_sz_511B;		/* 256-511 byte TX packets */
	u64 tx_sz_1023B;	/* 512-1023 byte TX packets */
	u64 tx_sz_1518B;	/* 1024-1518 byte TX packets */
	u64 tx_sz_max;		/* 1519 byte to MTU TX packets */
	u64 tx_single_col;	/* packets TX after a single collision */
	u64 tx_multi_col;	/* packets TX after multiple collisions */
	u64 tx_late_col;	/* TX packets with late collisions */
	u64 tx_पात_col;	/* TX packets पातed w/excessive collisions */
	u64 tx_underrun;	/* TX packets पातed due to TX FIFO underrun
				 * or TRD FIFO underrun
				 */
	u64 tx_trd_eop;		/* पढ़ोs beyond the EOP पूर्णांकo the next frame
				 * when TRD was not written समयly
				 */
	u64 tx_len_err;		/* TX packets where length != actual size */
	u64 tx_trunc;		/* TX packets truncated due to size > MTU */
	u64 tx_bc_byte_cnt;	/* broadcast bytes transmitted, excluding FCS */
	u64 tx_mc_byte_cnt;	/* multicast bytes transmitted, excluding FCS */
	u64 update;
पूर्ण;


/* maximum पूर्णांकerrupt vectors क्रम msix */
#घोषणा ALX_MAX_MSIX_INTRS	16

#घोषणा ALX_GET_FIELD(_data, _field)					\
	(((_data) >> _field ## _SHIFT) & _field ## _MASK)

#घोषणा ALX_SET_FIELD(_data, _field, _value)	करो अणु			\
		(_data) &= ~(_field ## _MASK << _field ## _SHIFT);	\
		(_data) |= ((_value) & _field ## _MASK) << _field ## _SHIFT;\
	पूर्ण जबतक (0)

काष्ठा alx_hw अणु
	काष्ठा pci_dev *pdev;
	u8 __iomem *hw_addr;

	/* current & permanent mac addr */
	u8 mac_addr[ETH_ALEN];
	u8 perm_addr[ETH_ALEN];

	u16 mtu;
	u16 imt;
	u8 dma_chnl;
	u8 max_dma_chnl;
	/* tpd threshold to trig INT */
	u32 ith_tpd;
	u32 rx_ctrl;
	u32 mc_hash[2];

	u32 smb_समयr;
	/* SPEED_* + DUPLEX_*, SPEED_UNKNOWN अगर link is करोwn */
	पूर्णांक link_speed;
	u8 duplex;

	/* स्वतः-neg advertisement or क्रमce mode config */
	u8 flowctrl;
	u32 adv_cfg;

	spinlock_t mdio_lock;
	काष्ठा mdio_अगर_info mdio;
	u16 phy_id[2];

	/* PHY link patch flag */
	bool lnk_patch;

	/* cumulated stats from the hardware (रेजिस्टरs are cleared on पढ़ो) */
	काष्ठा alx_hw_stats stats;
पूर्ण;

अटल अंतरभूत पूर्णांक alx_hw_revision(काष्ठा alx_hw *hw)
अणु
	वापस hw->pdev->revision >> ALX_PCI_REVID_SHIFT;
पूर्ण

अटल अंतरभूत bool alx_hw_with_cr(काष्ठा alx_hw *hw)
अणु
	वापस hw->pdev->revision & 1;
पूर्ण

अटल अंतरभूत bool alx_hw_giga(काष्ठा alx_hw *hw)
अणु
	वापस hw->pdev->device & 1;
पूर्ण

अटल अंतरभूत व्योम alx_ग_लिखो_mem8(काष्ठा alx_hw *hw, u32 reg, u8 val)
अणु
	ग_लिखोb(val, hw->hw_addr + reg);
पूर्ण

अटल अंतरभूत व्योम alx_ग_लिखो_mem16(काष्ठा alx_hw *hw, u32 reg, u16 val)
अणु
	ग_लिखोw(val, hw->hw_addr + reg);
पूर्ण

अटल अंतरभूत u16 alx_पढ़ो_mem16(काष्ठा alx_hw *hw, u32 reg)
अणु
	वापस पढ़ोw(hw->hw_addr + reg);
पूर्ण

अटल अंतरभूत व्योम alx_ग_लिखो_mem32(काष्ठा alx_hw *hw, u32 reg, u32 val)
अणु
	ग_लिखोl(val, hw->hw_addr + reg);
पूर्ण

अटल अंतरभूत u32 alx_पढ़ो_mem32(काष्ठा alx_hw *hw, u32 reg)
अणु
	वापस पढ़ोl(hw->hw_addr + reg);
पूर्ण

अटल अंतरभूत व्योम alx_post_ग_लिखो(काष्ठा alx_hw *hw)
अणु
	पढ़ोl(hw->hw_addr);
पूर्ण

पूर्णांक alx_get_perm_macaddr(काष्ठा alx_hw *hw, u8 *addr);
व्योम alx_reset_phy(काष्ठा alx_hw *hw);
व्योम alx_reset_pcie(काष्ठा alx_hw *hw);
व्योम alx_enable_aspm(काष्ठा alx_hw *hw, bool l0s_en, bool l1_en);
पूर्णांक alx_setup_speed_duplex(काष्ठा alx_hw *hw, u32 ethadv, u8 flowctrl);
व्योम alx_post_phy_link(काष्ठा alx_hw *hw);
पूर्णांक alx_पढ़ो_phy_reg(काष्ठा alx_hw *hw, u16 reg, u16 *phy_data);
पूर्णांक alx_ग_लिखो_phy_reg(काष्ठा alx_hw *hw, u16 reg, u16 phy_data);
पूर्णांक alx_पढ़ो_phy_ext(काष्ठा alx_hw *hw, u8 dev, u16 reg, u16 *pdata);
पूर्णांक alx_ग_लिखो_phy_ext(काष्ठा alx_hw *hw, u8 dev, u16 reg, u16 data);
पूर्णांक alx_पढ़ो_phy_link(काष्ठा alx_hw *hw);
पूर्णांक alx_clear_phy_पूर्णांकr(काष्ठा alx_hw *hw);
व्योम alx_cfg_mac_flowcontrol(काष्ठा alx_hw *hw, u8 fc);
व्योम alx_start_mac(काष्ठा alx_hw *hw);
पूर्णांक alx_reset_mac(काष्ठा alx_hw *hw);
व्योम alx_set_macaddr(काष्ठा alx_hw *hw, स्थिर u8 *addr);
bool alx_phy_configured(काष्ठा alx_hw *hw);
व्योम alx_configure_basic(काष्ठा alx_hw *hw);
व्योम alx_mask_msix(काष्ठा alx_hw *hw, पूर्णांक index, bool mask);
व्योम alx_disable_rss(काष्ठा alx_hw *hw);
bool alx_get_phy_info(काष्ठा alx_hw *hw);
व्योम alx_update_hw_stats(काष्ठा alx_hw *hw);

अटल अंतरभूत u32 alx_speed_to_ethadv(पूर्णांक speed, u8 duplex)
अणु
	अगर (speed == SPEED_1000 && duplex == DUPLEX_FULL)
		वापस ADVERTISED_1000baseT_Full;
	अगर (speed == SPEED_100 && duplex == DUPLEX_FULL)
		वापस ADVERTISED_100baseT_Full;
	अगर (speed == SPEED_100 && duplex== DUPLEX_HALF)
		वापस ADVERTISED_100baseT_Half;
	अगर (speed == SPEED_10 && duplex == DUPLEX_FULL)
		वापस ADVERTISED_10baseT_Full;
	अगर (speed == SPEED_10 && duplex == DUPLEX_HALF)
		वापस ADVERTISED_10baseT_Half;
	वापस 0;
पूर्ण

#पूर्ण_अगर
