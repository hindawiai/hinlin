<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * Copyright(c) 2007 Atheros Corporation. All rights reserved.
 * Copyright(c) 2007 xiong huang <xiong.huang@atheros.com>
 *
 * Derived from Intel e1000 driver
 * Copyright(c) 1999 - 2005 Intel Corporation. All rights reserved.
 */

#अगर_अघोषित _ATL1E_H_
#घोषणा _ATL1E_H_

#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/types.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/module.h>
#समावेश <linux/pci.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/etherdevice.h>
#समावेश <linux/skbuff.h>
#समावेश <linux/ioport.h>
#समावेश <linux/slab.h>
#समावेश <linux/list.h>
#समावेश <linux/delay.h>
#समावेश <linux/sched.h>
#समावेश <linux/in.h>
#समावेश <linux/ip.h>
#समावेश <linux/ipv6.h>
#समावेश <linux/udp.h>
#समावेश <linux/mii.h>
#समावेश <linux/पन.स>
#समावेश <linux/vदो_स्मृति.h>
#समावेश <linux/pagemap.h>
#समावेश <linux/tcp.h>
#समावेश <linux/ethtool.h>
#समावेश <linux/अगर_vlan.h>
#समावेश <linux/workqueue.h>
#समावेश <net/checksum.h>
#समावेश <net/ip6_checksum.h>

#समावेश "atl1e_hw.h"

#घोषणा PCI_REG_COMMAND	 0x04    /* PCI Command Register */
#घोषणा CMD_IO_SPACE	 0x0001
#घोषणा CMD_MEMORY_SPACE 0x0002
#घोषणा CMD_BUS_MASTER   0x0004

#घोषणा BAR_0   0
#घोषणा BAR_1   1
#घोषणा BAR_5   5

/* Wake Up Filter Control */
#घोषणा AT_WUFC_LNKC 0x00000001 /* Link Status Change Wakeup Enable */
#घोषणा AT_WUFC_MAG  0x00000002 /* Magic Packet Wakeup Enable */
#घोषणा AT_WUFC_EX   0x00000004 /* Directed Exact Wakeup Enable */
#घोषणा AT_WUFC_MC   0x00000008 /* Multicast Wakeup Enable */
#घोषणा AT_WUFC_BC   0x00000010 /* Broadcast Wakeup Enable */

#घोषणा SPEED_0		   0xffff
#घोषणा HALF_DUPLEX        1
#घोषणा FULL_DUPLEX        2

/* Error Codes */
#घोषणा AT_ERR_EEPROM      1
#घोषणा AT_ERR_PHY         2
#घोषणा AT_ERR_CONFIG      3
#घोषणा AT_ERR_PARAM       4
#घोषणा AT_ERR_MAC_TYPE    5
#घोषणा AT_ERR_PHY_TYPE    6
#घोषणा AT_ERR_PHY_SPEED   7
#घोषणा AT_ERR_PHY_RES     8
#घोषणा AT_ERR_TIMEOUT     9

#घोषणा MAX_JUMBO_FRAME_SIZE 0x2000

#घोषणा AT_VLAN_TAG_TO_TPD_TAG(_vlan, _tpd)    \
	_tpd = (((_vlan) << (4)) | (((_vlan) >> 13) & 7) |\
		 (((_vlan) >> 9) & 8))

#घोषणा AT_TPD_TAG_TO_VLAN_TAG(_tpd, _vlan)    \
	_vlan = (((_tpd) >> 8) | (((_tpd) & 0x77) << 9) |\
		   (((_tdp) & 0x88) << 5))

#घोषणा AT_MAX_RECEIVE_QUEUE    4
#घोषणा AT_PAGE_NUM_PER_QUEUE   2

#घोषणा AT_DMA_HI_ADDR_MASK     0xffffffff00000000ULL
#घोषणा AT_DMA_LO_ADDR_MASK     0x00000000ffffffffULL

#घोषणा AT_TX_WATCHDOG  (5 * HZ)
#घोषणा AT_MAX_INT_WORK		10
#घोषणा AT_TWSI_EEPROM_TIMEOUT 	100
#घोषणा AT_HW_MAX_IDLE_DELAY 	10
#घोषणा AT_SUSPEND_LINK_TIMEOUT 28

#घोषणा AT_REGS_LEN	75
#घोषणा AT_EEPROM_LEN 	512
#घोषणा AT_ADV_MASK	(ADVERTISE_10_HALF  |\
			 ADVERTISE_10_FULL  |\
			 ADVERTISE_100_HALF |\
			 ADVERTISE_100_FULL |\
			 ADVERTISE_1000_FULL)

/* tpd word 2 */
#घोषणा TPD_BUFLEN_MASK 	0x3FFF
#घोषणा TPD_BUFLEN_SHIFT        0
#घोषणा TPD_DMAINT_MASK		0x0001
#घोषणा TPD_DMAINT_SHIFT        14
#घोषणा TPD_PKTNT_MASK          0x0001
#घोषणा TPD_PKTINT_SHIFT        15
#घोषणा TPD_VLANTAG_MASK        0xFFFF
#घोषणा TPD_VLAN_SHIFT          16

/* tpd word 3 bits 0:4 */
#घोषणा TPD_EOP_MASK            0x0001
#घोषणा TPD_EOP_SHIFT           0
#घोषणा TPD_IP_VERSION_MASK	0x0001
#घोषणा TPD_IP_VERSION_SHIFT	1	/* 0 : IPV4, 1 : IPV6 */
#घोषणा TPD_INS_VL_TAG_MASK	0x0001
#घोषणा TPD_INS_VL_TAG_SHIFT	2
#घोषणा TPD_CC_SEGMENT_EN_MASK	0x0001
#घोषणा TPD_CC_SEGMENT_EN_SHIFT	3
#घोषणा TPD_SEGMENT_EN_MASK     0x0001
#घोषणा TPD_SEGMENT_EN_SHIFT    4

/* tdp word 3 bits 5:7 अगर ip version is 0 */
#घोषणा TPD_IP_CSUM_MASK        0x0001
#घोषणा TPD_IP_CSUM_SHIFT       5
#घोषणा TPD_TCP_CSUM_MASK       0x0001
#घोषणा TPD_TCP_CSUM_SHIFT      6
#घोषणा TPD_UDP_CSUM_MASK       0x0001
#घोषणा TPD_UDP_CSUM_SHIFT      7

/* tdp word 3 bits 5:7 अगर ip version is 1 */
#घोषणा TPD_V6_IPHLLO_MASK	0x0007
#घोषणा TPD_V6_IPHLLO_SHIFT	7

/* tpd word 3 bits 8:9 bit */
#घोषणा TPD_VL_TAGGED_MASK      0x0001
#घोषणा TPD_VL_TAGGED_SHIFT     8
#घोषणा TPD_ETHTYPE_MASK        0x0001
#घोषणा TPD_ETHTYPE_SHIFT       9

/* tdp word 3 bits 10:13 अगर ip version is 0 */
#घोषणा TDP_V4_IPHL_MASK	0x000F
#घोषणा TPD_V4_IPHL_SHIFT	10

/* tdp word 3 bits 10:13 अगर ip version is 1 */
#घोषणा TPD_V6_IPHLHI_MASK	0x000F
#घोषणा TPD_V6_IPHLHI_SHIFT	10

/* tpd word 3 bit 14:31 अगर segment enabled */
#घोषणा TPD_TCPHDRLEN_MASK      0x000F
#घोषणा TPD_TCPHDRLEN_SHIFT     14
#घोषणा TPD_HDRFLAG_MASK        0x0001
#घोषणा TPD_HDRFLAG_SHIFT       18
#घोषणा TPD_MSS_MASK            0x1FFF
#घोषणा TPD_MSS_SHIFT           19

/* tdp word 3 bit 16:31 अगर custom csum enabled */
#घोषणा TPD_PLOADOFFSET_MASK    0x00FF
#घोषणा TPD_PLOADOFFSET_SHIFT   16
#घोषणा TPD_CCSUMOFFSET_MASK    0x00FF
#घोषणा TPD_CCSUMOFFSET_SHIFT   24

काष्ठा atl1e_tpd_desc अणु
	__le64 buffer_addr;
	__le32 word2;
	__le32 word3;
पूर्ण;

/* how about 0x2000 */
#घोषणा MAX_TX_BUF_LEN      0x2000
#घोषणा MAX_TX_BUF_SHIFT    13
#घोषणा MAX_TSO_SEG_SIZE    0x3c00

/* rrs word 1 bit 0:31 */
#घोषणा RRS_RX_CSUM_MASK	0xFFFF
#घोषणा RRS_RX_CSUM_SHIFT	0
#घोषणा RRS_PKT_SIZE_MASK	0x3FFF
#घोषणा RRS_PKT_SIZE_SHIFT	16
#घोषणा RRS_CPU_NUM_MASK	0x0003
#घोषणा	RRS_CPU_NUM_SHIFT	30

#घोषणा	RRS_IS_RSS_IPV4		0x0001
#घोषणा RRS_IS_RSS_IPV4_TCP	0x0002
#घोषणा RRS_IS_RSS_IPV6		0x0004
#घोषणा RRS_IS_RSS_IPV6_TCP	0x0008
#घोषणा RRS_IS_IPV6		0x0010
#घोषणा RRS_IS_IP_FRAG		0x0020
#घोषणा RRS_IS_IP_DF		0x0040
#घोषणा RRS_IS_802_3		0x0080
#घोषणा RRS_IS_VLAN_TAG		0x0100
#घोषणा RRS_IS_ERR_FRAME	0x0200
#घोषणा RRS_IS_IPV4		0x0400
#घोषणा RRS_IS_UDP		0x0800
#घोषणा RRS_IS_TCP		0x1000
#घोषणा RRS_IS_BCAST		0x2000
#घोषणा RRS_IS_MCAST		0x4000
#घोषणा RRS_IS_PAUSE		0x8000

#घोषणा RRS_ERR_BAD_CRC		0x0001
#घोषणा RRS_ERR_CODE		0x0002
#घोषणा RRS_ERR_DRIBBLE		0x0004
#घोषणा RRS_ERR_RUNT		0x0008
#घोषणा RRS_ERR_RX_OVERFLOW	0x0010
#घोषणा RRS_ERR_TRUNC		0x0020
#घोषणा RRS_ERR_IP_CSUM		0x0040
#घोषणा RRS_ERR_L4_CSUM		0x0080
#घोषणा RRS_ERR_LENGTH		0x0100
#घोषणा RRS_ERR_DES_ADDR	0x0200

काष्ठा atl1e_recv_ret_status अणु
	u16 seq_num;
	u16 hash_lo;
	__le32	word1;
	u16 pkt_flag;
	u16 err_flag;
	u16 hash_hi;
	u16 vtag;
पूर्ण;

क्रमागत atl1e_dma_req_block अणु
	atl1e_dma_req_128 = 0,
	atl1e_dma_req_256 = 1,
	atl1e_dma_req_512 = 2,
	atl1e_dma_req_1024 = 3,
	atl1e_dma_req_2048 = 4,
	atl1e_dma_req_4096 = 5
पूर्ण;

क्रमागत atl1e_rrs_type अणु
	atl1e_rrs_disable = 0,
	atl1e_rrs_ipv4 = 1,
	atl1e_rrs_ipv4_tcp = 2,
	atl1e_rrs_ipv6 = 4,
	atl1e_rrs_ipv6_tcp = 8
पूर्ण;

क्रमागत atl1e_nic_type अणु
	athr_l1e = 0,
	athr_l2e_revA = 1,
	athr_l2e_revB = 2
पूर्ण;

काष्ठा atl1e_hw_stats अणु
	/* rx */
	अचिन्हित दीर्घ rx_ok;	      /* The number of good packet received. */
	अचिन्हित दीर्घ rx_bcast;       /* The number of good broadcast packet received. */
	अचिन्हित दीर्घ rx_mcast;       /* The number of good multicast packet received. */
	अचिन्हित दीर्घ rx_छोड़ो;       /* The number of Pause packet received. */
	अचिन्हित दीर्घ rx_ctrl;        /* The number of Control packet received other than Pause frame. */
	अचिन्हित दीर्घ rx_fcs_err;     /* The number of packets with bad FCS. */
	अचिन्हित दीर्घ rx_len_err;     /* The number of packets with mismatch of length field and actual size. */
	अचिन्हित दीर्घ rx_byte_cnt;    /* The number of bytes of good packet received. FCS is NOT included. */
	अचिन्हित दीर्घ rx_runt;        /* The number of packets received that are less than 64 byte दीर्घ and with good FCS. */
	अचिन्हित दीर्घ rx_frag;        /* The number of packets received that are less than 64 byte दीर्घ and with bad FCS. */
	अचिन्हित दीर्घ rx_sz_64;       /* The number of good and bad packets received that are 64 byte दीर्घ. */
	अचिन्हित दीर्घ rx_sz_65_127;   /* The number of good and bad packets received that are between 65 and 127-byte दीर्घ. */
	अचिन्हित दीर्घ rx_sz_128_255;  /* The number of good and bad packets received that are between 128 and 255-byte दीर्घ. */
	अचिन्हित दीर्घ rx_sz_256_511;  /* The number of good and bad packets received that are between 256 and 511-byte दीर्घ. */
	अचिन्हित दीर्घ rx_sz_512_1023; /* The number of good and bad packets received that are between 512 and 1023-byte दीर्घ. */
	अचिन्हित दीर्घ rx_sz_1024_1518;    /* The number of good and bad packets received that are between 1024 and 1518-byte दीर्घ. */
	अचिन्हित दीर्घ rx_sz_1519_max; /* The number of good and bad packets received that are between 1519-byte and MTU. */
	अचिन्हित दीर्घ rx_sz_ov;       /* The number of good and bad packets received that are more than MTU size truncated by Selene. */
	अचिन्हित दीर्घ rx_rxf_ov;      /* The number of frame dropped due to occurrence of RX FIFO overflow. */
	अचिन्हित दीर्घ rx_rrd_ov;      /* The number of frame dropped due to occurrence of RRD overflow. */
	अचिन्हित दीर्घ rx_align_err;   /* Alignment Error */
	अचिन्हित दीर्घ rx_bcast_byte_cnt;  /* The byte count of broadcast packet received, excluding FCS. */
	अचिन्हित दीर्घ rx_mcast_byte_cnt;  /* The byte count of multicast packet received, excluding FCS. */
	अचिन्हित दीर्घ rx_err_addr;    /* The number of packets dropped due to address filtering. */

	/* tx */
	अचिन्हित दीर्घ tx_ok;      /* The number of good packet transmitted. */
	अचिन्हित दीर्घ tx_bcast;       /* The number of good broadcast packet transmitted. */
	अचिन्हित दीर्घ tx_mcast;       /* The number of good multicast packet transmitted. */
	अचिन्हित दीर्घ tx_छोड़ो;       /* The number of Pause packet transmitted. */
	अचिन्हित दीर्घ tx_exc_defer;   /* The number of packets transmitted with excessive deferral. */
	अचिन्हित दीर्घ tx_ctrl;        /* The number of packets transmitted is a control frame, excluding Pause frame. */
	अचिन्हित दीर्घ tx_defer;       /* The number of packets transmitted that is deferred. */
	अचिन्हित दीर्घ tx_byte_cnt;    /* The number of bytes of data transmitted. FCS is NOT included. */
	अचिन्हित दीर्घ tx_sz_64;       /* The number of good and bad packets transmitted that are 64 byte दीर्घ. */
	अचिन्हित दीर्घ tx_sz_65_127;   /* The number of good and bad packets transmitted that are between 65 and 127-byte दीर्घ. */
	अचिन्हित दीर्घ tx_sz_128_255;  /* The number of good and bad packets transmitted that are between 128 and 255-byte दीर्घ. */
	अचिन्हित दीर्घ tx_sz_256_511;  /* The number of good and bad packets transmitted that are between 256 and 511-byte दीर्घ. */
	अचिन्हित दीर्घ tx_sz_512_1023; /* The number of good and bad packets transmitted that are between 512 and 1023-byte दीर्घ. */
	अचिन्हित दीर्घ tx_sz_1024_1518;    /* The number of good and bad packets transmitted that are between 1024 and 1518-byte दीर्घ. */
	अचिन्हित दीर्घ tx_sz_1519_max; /* The number of good and bad packets transmitted that are between 1519-byte and MTU. */
	अचिन्हित दीर्घ tx_1_col;       /* The number of packets subsequently transmitted successfully with a single prior collision. */
	अचिन्हित दीर्घ tx_2_col;       /* The number of packets subsequently transmitted successfully with multiple prior collisions. */
	अचिन्हित दीर्घ tx_late_col;    /* The number of packets transmitted with late collisions. */
	अचिन्हित दीर्घ tx_पात_col;   /* The number of transmit packets पातed due to excessive collisions. */
	अचिन्हित दीर्घ tx_underrun;    /* The number of transmit packets पातed due to transmit FIFO underrun, or TRD FIFO underrun */
	अचिन्हित दीर्घ tx_rd_eop;      /* The number of बार that पढ़ो beyond the EOP पूर्णांकo the next frame area when TRD was not written समयly */
	अचिन्हित दीर्घ tx_len_err;     /* The number of transmit packets with length field करोes NOT match the actual frame size. */
	अचिन्हित दीर्घ tx_trunc;       /* The number of transmit packets truncated due to size exceeding MTU. */
	अचिन्हित दीर्घ tx_bcast_byte;  /* The byte count of broadcast packet transmitted, excluding FCS. */
	अचिन्हित दीर्घ tx_mcast_byte;  /* The byte count of multicast packet transmitted, excluding FCS. */
पूर्ण;

काष्ठा atl1e_hw अणु
	u8 __iomem      *hw_addr;            /* inner रेजिस्टर address */
	resource_माप_प्रकार mem_rang;
	काष्ठा atl1e_adapter *adapter;
	क्रमागत atl1e_nic_type  nic_type;
	u16 device_id;
	u16 venकरोr_id;
	u16 subप्रणाली_id;
	u16 subप्रणाली_venकरोr_id;
	u8  revision_id;
	u16 pci_cmd_word;
	u8 mac_addr[ETH_ALEN];
	u8 perm_mac_addr[ETH_ALEN];
	u8 preamble_len;
	u16 max_frame_size;
	u16 rx_jumbo_th;
	u16 tx_jumbo_th;

	u16 media_type;
#घोषणा MEDIA_TYPE_AUTO_SENSOR  0
#घोषणा MEDIA_TYPE_100M_FULL    1
#घोषणा MEDIA_TYPE_100M_HALF    2
#घोषणा MEDIA_TYPE_10M_FULL     3
#घोषणा MEDIA_TYPE_10M_HALF     4

	u16 स्वतःneg_advertised;
#घोषणा ADVERTISE_10_HALF               0x0001
#घोषणा ADVERTISE_10_FULL               0x0002
#घोषणा ADVERTISE_100_HALF              0x0004
#घोषणा ADVERTISE_100_FULL              0x0008
#घोषणा ADVERTISE_1000_HALF             0x0010 /* Not used, just FYI */
#घोषणा ADVERTISE_1000_FULL             0x0020
	u16 mii_स्वतःneg_adv_reg;
	u16 mii_1000t_ctrl_reg;

	u16 imt;        /* Interrupt Moderator समयr ( 2us resolution) */
	u16 ict;        /* Interrupt Clear समयr (2us resolution) */
	u32 smb_समयr;
	u16 rrd_thresh; /* Threshold of number of RRD produced to trigger
			  पूर्णांकerrupt request */
	u16 tpd_thresh;
	u16 rx_count_करोwn; /* 2us resolution */
	u16 tx_count_करोwn;

	u8 tpd_burst;   /* Number of TPD to prefetch in cache-aligned burst. */
	क्रमागत atl1e_rrs_type rrs_type;
	u32 base_cpu;
	u32 indirect_tab;

	क्रमागत atl1e_dma_req_block dmar_block;
	क्रमागत atl1e_dma_req_block dmaw_block;
	u8 dmaw_dly_cnt;
	u8 dmar_dly_cnt;

	bool phy_configured;
	bool re_स्वतःneg;
	bool emi_ca;
पूर्ण;

/*
 * wrapper around a poपूर्णांकer to a socket buffer,
 * so a DMA handle can be stored aदीर्घ with the buffer
 */
काष्ठा atl1e_tx_buffer अणु
	काष्ठा sk_buff *skb;
	u16 flags;
#घोषणा ATL1E_TX_PCIMAP_SINGLE		0x0001
#घोषणा ATL1E_TX_PCIMAP_PAGE		0x0002
#घोषणा ATL1E_TX_PCIMAP_TYPE_MASK	0x0003
	u16 length;
	dma_addr_t dma;
पूर्ण;

#घोषणा ATL1E_SET_PCIMAP_TYPE(tx_buff, type) करो अणु		\
	((tx_buff)->flags) &= ~ATL1E_TX_PCIMAP_TYPE_MASK;	\
	((tx_buff)->flags) |= (type);				\
	पूर्ण जबतक (0)

काष्ठा atl1e_rx_page अणु
	dma_addr_t	dma;    /* receive rage DMA address */
	u8		*addr;   /* receive rage भव address */
	dma_addr_t	ग_लिखो_offset_dma;  /* the DMA address which contain the
					      receive data offset in the page */
	u32		*ग_लिखो_offset_addr; /* the virtaul address which contain
					     the receive data offset in the page */
	u32		पढ़ो_offset;       /* the offset where we have पढ़ो */
पूर्ण;

काष्ठा atl1e_rx_page_desc अणु
	काष्ठा atl1e_rx_page   rx_page[AT_PAGE_NUM_PER_QUEUE];
	u8  rx_using;
	u16 rx_nxseq;
पूर्ण;

/* transmit packet descriptor (tpd) ring */
काष्ठा atl1e_tx_ring अणु
	काष्ठा atl1e_tpd_desc *desc;  /* descriptor ring भव address  */
	dma_addr_t	   dma;    /* descriptor ring physical address */
	u16       	   count;  /* the count of transmit rings  */
	rwlock_t	   tx_lock;
	u16		   next_to_use;
	atomic_t	   next_to_clean;
	काष्ठा atl1e_tx_buffer *tx_buffer;
	dma_addr_t	   cmb_dma;
	u32		   *cmb;
पूर्ण;

/* receive packet descriptor ring */
काष्ठा atl1e_rx_ring अणु
	व्योम        	*desc;
	dma_addr_t  	dma;
	पूर्णांक         	size;
	u32	    	page_size; /* bytes length of rxf page */
	u32		real_page_size; /* real_page_size = page_size + jumbo + aliagn */
	काष्ठा atl1e_rx_page_desc	rx_page_desc[AT_MAX_RECEIVE_QUEUE];
पूर्ण;

/* board specअगरic निजी data काष्ठाure */
काष्ठा atl1e_adapter अणु
	काष्ठा net_device   *netdev;
	काष्ठा pci_dev      *pdev;
	काष्ठा napi_काष्ठा  napi;
	काष्ठा mii_अगर_info  mii;    /* MII पूर्णांकerface info */
	काष्ठा atl1e_hw        hw;
	काष्ठा atl1e_hw_stats  hw_stats;

	u32 wol;
	u16 link_speed;
	u16 link_duplex;

	spinlock_t mdio_lock;
	atomic_t irq_sem;

	काष्ठा work_काष्ठा reset_task;
	काष्ठा work_काष्ठा link_chg_task;
	काष्ठा समयr_list watchकरोg_समयr;
	काष्ठा समयr_list phy_config_समयr;

	/* All Descriptor memory */
	dma_addr_t  	ring_dma;
	व्योम     	*ring_vir_addr;
	u32             ring_size;

	काष्ठा atl1e_tx_ring tx_ring;
	काष्ठा atl1e_rx_ring rx_ring;
	पूर्णांक num_rx_queues;
	अचिन्हित दीर्घ flags;
#घोषणा __AT_TESTING        0x0001
#घोषणा __AT_RESETTING      0x0002
#घोषणा __AT_DOWN           0x0003

	u32 bd_number;     /* board number;*/
	u32 pci_state[16];
	u32 *config_space;
पूर्ण;

#घोषणा AT_WRITE_REG(a, reg, value) ( \
		ग_लिखोl((value), ((a)->hw_addr + reg)))

#घोषणा AT_WRITE_FLUSH(a) (\
		पढ़ोl((a)->hw_addr))

#घोषणा AT_READ_REG(a, reg) ( \
		पढ़ोl((a)->hw_addr + reg))

#घोषणा AT_WRITE_REGB(a, reg, value) (\
		ग_लिखोb((value), ((a)->hw_addr + reg)))

#घोषणा AT_READ_REGB(a, reg) (\
		पढ़ोb((a)->hw_addr + reg))

#घोषणा AT_WRITE_REGW(a, reg, value) (\
		ग_लिखोw((value), ((a)->hw_addr + reg)))

#घोषणा AT_READ_REGW(a, reg) (\
		पढ़ोw((a)->hw_addr + reg))

#घोषणा AT_WRITE_REG_ARRAY(a, reg, offset, value) ( \
		ग_लिखोl((value), (((a)->hw_addr + reg) + ((offset) << 2))))

#घोषणा AT_READ_REG_ARRAY(a, reg, offset) ( \
		पढ़ोl(((a)->hw_addr + reg) + ((offset) << 2)))

बाह्य अक्षर atl1e_driver_name[];

व्योम atl1e_check_options(काष्ठा atl1e_adapter *adapter);
पूर्णांक atl1e_up(काष्ठा atl1e_adapter *adapter);
व्योम atl1e_करोwn(काष्ठा atl1e_adapter *adapter);
व्योम atl1e_reinit_locked(काष्ठा atl1e_adapter *adapter);
s32 atl1e_reset_hw(काष्ठा atl1e_hw *hw);
व्योम atl1e_set_ethtool_ops(काष्ठा net_device *netdev);
#पूर्ण_अगर /* _ATL1_E_H_ */
