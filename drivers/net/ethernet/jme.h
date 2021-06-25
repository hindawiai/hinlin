<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * JMicron JMC2x0 series PCIe Ethernet Linux Device Driver
 *
 * Copyright 2008 JMicron Technology Corporation
 * https://www.jmicron.com/
 * Copyright (c) 2009 - 2010 Guo-Fu Tseng <cooldavid@cooldavid.org>
 *
 * Author: Guo-Fu Tseng <cooldavid@cooldavid.org>
 */

#अगर_अघोषित __JME_H_INCLUDED__
#घोषणा __JME_H_INCLUDED__
#समावेश <linux/पूर्णांकerrupt.h>

#घोषणा DRV_NAME	"jme"
#घोषणा DRV_VERSION	"1.0.8"

#घोषणा PCI_DEVICE_ID_JMICRON_JMC250	0x0250
#घोषणा PCI_DEVICE_ID_JMICRON_JMC260	0x0260

/*
 * Message related definitions
 */
#घोषणा JME_DEF_MSG_ENABLE \
	(NETIF_MSG_PROBE | \
	NETIF_MSG_LINK | \
	NETIF_MSG_RX_ERR | \
	NETIF_MSG_TX_ERR | \
	NETIF_MSG_HW)

#अगर_घोषित TX_DEBUG
#घोषणा tx_dbg(priv, fmt, args...)					\
	prपूर्णांकk(KERN_DEBUG "%s: " fmt, (priv)->dev->name, ##args)
#अन्यथा
#घोषणा tx_dbg(priv, fmt, args...)					\
करो अणु									\
	अगर (0)								\
		prपूर्णांकk(KERN_DEBUG "%s: " fmt, (priv)->dev->name, ##args); \
पूर्ण जबतक (0)
#पूर्ण_अगर

/*
 * Extra PCI Configuration space पूर्णांकerface
 */
#घोषणा PCI_DCSR_MRRS		0x59
#घोषणा PCI_DCSR_MRRS_MASK	0x70

क्रमागत pci_dcsr_mrrs_vals अणु
	MRRS_128B	= 0x00,
	MRRS_256B	= 0x10,
	MRRS_512B	= 0x20,
	MRRS_1024B	= 0x30,
	MRRS_2048B	= 0x40,
	MRRS_4096B	= 0x50,
पूर्ण;

#घोषणा PCI_SPI			0xB0

क्रमागत pci_spi_bits अणु
	SPI_EN		= 0x10,
	SPI_MISO	= 0x08,
	SPI_MOSI	= 0x04,
	SPI_SCLK	= 0x02,
	SPI_CS		= 0x01,
पूर्ण;

काष्ठा jme_spi_op अणु
	व्योम __user *uwbuf;
	व्योम __user *urbuf;
	__u8	wn;	/* Number of ग_लिखो actions */
	__u8	rn;	/* Number of पढ़ो actions */
	__u8	bitn;	/* Number of bits per action */
	__u8	spd;	/* The maxim acceptable speed of controller, in MHz.*/
	__u8	mode;	/* CPOL, CPHA, and Duplex mode of SPI */

	/* Internal use only */
	u8	*kwbuf;
	u8	*krbuf;
	u8	sr;
	u16	halfclk; /* Half of घड़ी cycle calculated from spd, in ns */
पूर्ण;

क्रमागत jme_spi_op_bits अणु
	SPI_MODE_CPHA	= 0x01,
	SPI_MODE_CPOL	= 0x02,
	SPI_MODE_DUP	= 0x80,
पूर्ण;

#घोषणा HALF_US 500	/* 500 ns */

#घोषणा PCI_PRIV_PE1		0xE4

क्रमागत pci_priv_pe1_bit_masks अणु
	PE1_ASPMSUPRT	= 0x00000003, /*
				       * RW:
				       * Aspm_support[1:0]
				       * (R/W Port of 5C[11:10])
				       */
	PE1_MULTIFUN	= 0x00000004, /* RW: Multi_fun_bit */
	PE1_RDYDMA	= 0x00000008, /* RO: ~link.rdy_क्रम_dma */
	PE1_ASPMOPTL	= 0x00000030, /* RW: link.rx10s_option[1:0] */
	PE1_ASPMOPTH	= 0x000000C0, /* RW: 10_req=[3]?HW:[2] */
	PE1_GPREG0	= 0x0000FF00, /*
				       * SRW:
				       * Cfg_gp_reg0
				       * [7:6] phy_giga BG control
				       * [5] CREQ_N as CREQ_N1 (CPPE# as CREQ#)
				       * [4:0] Reserved
				       */
	PE1_GPREG0_PBG	= 0x0000C000, /* phy_giga BG control */
	PE1_GPREG1	= 0x00FF0000, /* RW: Cfg_gp_reg1 */
	PE1_REVID	= 0xFF000000, /* RO: Rev ID */
पूर्ण;

क्रमागत pci_priv_pe1_values अणु
	PE1_GPREG0_ENBG		= 0x00000000, /* en BG */
	PE1_GPREG0_PDD3COLD	= 0x00004000, /* giga_PD + d3cold */
	PE1_GPREG0_PDPCIESD	= 0x00008000, /* giga_PD + pcie_shutकरोwn */
	PE1_GPREG0_PDPCIEIDDQ	= 0x0000C000, /* giga_PD + pcie_iddq */
पूर्ण;

/*
 * Dynamic(adaptive)/Static PCC values
 */
क्रमागत dynamic_pcc_values अणु
	PCC_OFF		= 0,
	PCC_P1		= 1,
	PCC_P2		= 2,
	PCC_P3		= 3,

	PCC_OFF_TO	= 0,
	PCC_P1_TO	= 1,
	PCC_P2_TO	= 64,
	PCC_P3_TO	= 128,

	PCC_OFF_CNT	= 0,
	PCC_P1_CNT	= 1,
	PCC_P2_CNT	= 16,
	PCC_P3_CNT	= 32,
पूर्ण;
काष्ठा dynpcc_info अणु
	अचिन्हित दीर्घ	last_bytes;
	अचिन्हित दीर्घ	last_pkts;
	अचिन्हित दीर्घ	पूर्णांकr_cnt;
	अचिन्हित अक्षर	cur;
	अचिन्हित अक्षर	attempt;
	अचिन्हित अक्षर	cnt;
पूर्ण;
#घोषणा PCC_INTERVAL_US	100000
#घोषणा PCC_INTERVAL (HZ / (1000000 / PCC_INTERVAL_US))
#घोषणा PCC_P3_THRESHOLD (2 * 1024 * 1024)
#घोषणा PCC_P2_THRESHOLD 800
#घोषणा PCC_INTR_THRESHOLD 800
#घोषणा PCC_TX_TO 1000
#घोषणा PCC_TX_CNT 8

/*
 * TX/RX Descriptors
 *
 * TX/RX Ring DESC Count Must be multiple of 16 and <= 1024
 */
#घोषणा RING_DESC_ALIGN		16	/* Descriptor alignment */
#घोषणा TX_DESC_SIZE		16
#घोषणा TX_RING_NR		8
#घोषणा TX_RING_ALLOC_SIZE(s)	((s * TX_DESC_SIZE) + RING_DESC_ALIGN)

काष्ठा txdesc अणु
	जोड़ अणु
		__u8	all[16];
		__le32	dw[4];
		काष्ठा अणु
			/* DW0 */
			__le16	vlan;
			__u8	rsv1;
			__u8	flags;

			/* DW1 */
			__le16	datalen;
			__le16	mss;

			/* DW2 */
			__le16	pktsize;
			__le16	rsv2;

			/* DW3 */
			__le32	bufaddr;
		पूर्ण desc1;
		काष्ठा अणु
			/* DW0 */
			__le16	rsv1;
			__u8	rsv2;
			__u8	flags;

			/* DW1 */
			__le16	datalen;
			__le16	rsv3;

			/* DW2 */
			__le32	bufaddrh;

			/* DW3 */
			__le32	bufaddrl;
		पूर्ण desc2;
		काष्ठा अणु
			/* DW0 */
			__u8	ehdrsz;
			__u8	rsv1;
			__u8	rsv2;
			__u8	flags;

			/* DW1 */
			__le16	trycnt;
			__le16	segcnt;

			/* DW2 */
			__le16	pktsz;
			__le16	rsv3;

			/* DW3 */
			__le32	bufaddrl;
		पूर्ण descwb;
	पूर्ण;
पूर्ण;

क्रमागत jme_txdesc_flags_bits अणु
	TXFLAG_OWN	= 0x80,
	TXFLAG_INT	= 0x40,
	TXFLAG_64BIT	= 0x20,
	TXFLAG_TCPCS	= 0x10,
	TXFLAG_UDPCS	= 0x08,
	TXFLAG_IPCS	= 0x04,
	TXFLAG_LSEN	= 0x02,
	TXFLAG_TAGON	= 0x01,
पूर्ण;

#घोषणा TXDESC_MSS_SHIFT	2
क्रमागत jme_txwbdesc_flags_bits अणु
	TXWBFLAG_OWN	= 0x80,
	TXWBFLAG_INT	= 0x40,
	TXWBFLAG_TMOUT	= 0x20,
	TXWBFLAG_TRYOUT	= 0x10,
	TXWBFLAG_COL	= 0x08,

	TXWBFLAG_ALLERR	= TXWBFLAG_TMOUT |
			  TXWBFLAG_TRYOUT |
			  TXWBFLAG_COL,
पूर्ण;

#घोषणा RX_DESC_SIZE		16
#घोषणा RX_RING_NR		4
#घोषणा RX_RING_ALLOC_SIZE(s)	((s * RX_DESC_SIZE) + RING_DESC_ALIGN)
#घोषणा RX_BUF_DMA_ALIGN	8
#घोषणा RX_PREPAD_SIZE		10
#घोषणा ETH_CRC_LEN		2
#घोषणा RX_VLANHDR_LEN		2
#घोषणा RX_EXTRA_LEN		(RX_PREPAD_SIZE + \
				ETH_HLEN + \
				ETH_CRC_LEN + \
				RX_VLANHDR_LEN + \
				RX_BUF_DMA_ALIGN)

काष्ठा rxdesc अणु
	जोड़ अणु
		__u8	all[16];
		__le32	dw[4];
		काष्ठा अणु
			/* DW0 */
			__le16	rsv2;
			__u8	rsv1;
			__u8	flags;

			/* DW1 */
			__le16	datalen;
			__le16	wbcpl;

			/* DW2 */
			__le32	bufaddrh;

			/* DW3 */
			__le32	bufaddrl;
		पूर्ण desc1;
		काष्ठा अणु
			/* DW0 */
			__le16	vlan;
			__le16	flags;

			/* DW1 */
			__le16	framesize;
			__u8	errstat;
			__u8	desccnt;

			/* DW2 */
			__le32	rsshash;

			/* DW3 */
			__u8	hashfun;
			__u8	hashtype;
			__le16	resrv;
		पूर्ण descwb;
	पूर्ण;
पूर्ण;

क्रमागत jme_rxdesc_flags_bits अणु
	RXFLAG_OWN	= 0x80,
	RXFLAG_INT	= 0x40,
	RXFLAG_64BIT	= 0x20,
पूर्ण;

क्रमागत jme_rxwbdesc_flags_bits अणु
	RXWBFLAG_OWN		= 0x8000,
	RXWBFLAG_INT		= 0x4000,
	RXWBFLAG_MF		= 0x2000,
	RXWBFLAG_64BIT		= 0x2000,
	RXWBFLAG_TCPON		= 0x1000,
	RXWBFLAG_UDPON		= 0x0800,
	RXWBFLAG_IPCS		= 0x0400,
	RXWBFLAG_TCPCS		= 0x0200,
	RXWBFLAG_UDPCS		= 0x0100,
	RXWBFLAG_TAGON		= 0x0080,
	RXWBFLAG_IPV4		= 0x0040,
	RXWBFLAG_IPV6		= 0x0020,
	RXWBFLAG_PAUSE		= 0x0010,
	RXWBFLAG_MAGIC		= 0x0008,
	RXWBFLAG_WAKEUP		= 0x0004,
	RXWBFLAG_DEST		= 0x0003,
	RXWBFLAG_DEST_UNI	= 0x0001,
	RXWBFLAG_DEST_MUL	= 0x0002,
	RXWBFLAG_DEST_BRO	= 0x0003,
पूर्ण;

क्रमागत jme_rxwbdesc_desccnt_mask अणु
	RXWBDCNT_WBCPL	= 0x80,
	RXWBDCNT_DCNT	= 0x7F,
पूर्ण;

क्रमागत jme_rxwbdesc_errstat_bits अणु
	RXWBERR_LIMIT	= 0x80,
	RXWBERR_MIIER	= 0x40,
	RXWBERR_NIBON	= 0x20,
	RXWBERR_COLON	= 0x10,
	RXWBERR_ABORT	= 0x08,
	RXWBERR_SHORT	= 0x04,
	RXWBERR_OVERUN	= 0x02,
	RXWBERR_CRCERR	= 0x01,
	RXWBERR_ALLERR	= 0xFF,
पूर्ण;

/*
 * Buffer inक्रमmation corresponding to ring descriptors.
 */
काष्ठा jme_buffer_info अणु
	काष्ठा sk_buff *skb;
	dma_addr_t mapping;
	पूर्णांक len;
	पूर्णांक nr_desc;
	अचिन्हित दीर्घ start_xmit;
पूर्ण;

/*
 * The काष्ठाure holding buffer inक्रमmation and ring descriptors all together.
 */
काष्ठा jme_ring अणु
	व्योम *alloc;		/* poपूर्णांकer to allocated memory */
	व्योम *desc;		/* poपूर्णांकer to ring memory  */
	dma_addr_t dmaalloc;	/* phys address of ring alloc */
	dma_addr_t dma;		/* phys address क्रम ring dma */

	/* Buffer inक्रमmation corresponding to each descriptor */
	काष्ठा jme_buffer_info *bufinf;

	पूर्णांक next_to_use;
	atomic_t next_to_clean;
	atomic_t nr_मुक्त;
पूर्ण;

#घोषणा NET_STAT(priv) (priv->dev->stats)
#घोषणा NETDEV_GET_STATS(netdev, fun_ptr)
#घोषणा DECLARE_NET_DEVICE_STATS

#घोषणा DECLARE_NAPI_STRUCT काष्ठा napi_काष्ठा napi;
#घोषणा NETIF_NAPI_SET(dev, napis, pollfn, q) \
	netअगर_napi_add(dev, napis, pollfn, q);
#घोषणा JME_NAPI_HOLDER(holder) काष्ठा napi_काष्ठा *holder
#घोषणा JME_NAPI_WEIGHT(w) पूर्णांक w
#घोषणा JME_NAPI_WEIGHT_VAL(w) w
#घोषणा JME_NAPI_WEIGHT_SET(w, r)
#घोषणा JME_RX_COMPLETE(dev, napis) napi_complete(napis)
#घोषणा JME_NAPI_ENABLE(priv) napi_enable(&priv->napi);
#घोषणा JME_NAPI_DISABLE(priv) \
	अगर (!napi_disable_pending(&priv->napi)) \
		napi_disable(&priv->napi);
#घोषणा JME_RX_SCHEDULE_PREP(priv) \
	napi_schedule_prep(&priv->napi)
#घोषणा JME_RX_SCHEDULE(priv) \
	__napi_schedule(&priv->napi);

/*
 * Jmac Adapter Private data
 */
काष्ठा jme_adapter अणु
	काष्ठा pci_dev          *pdev;
	काष्ठा net_device       *dev;
	व्योम __iomem            *regs;
	काष्ठा mii_अगर_info	mii_अगर;
	काष्ठा jme_ring		rxring[RX_RING_NR];
	काष्ठा jme_ring		txring[TX_RING_NR];
	spinlock_t		phy_lock;
	spinlock_t		macaddr_lock;
	spinlock_t		rxmcs_lock;
	काष्ठा tasklet_काष्ठा	rxempty_task;
	काष्ठा tasklet_काष्ठा	rxclean_task;
	काष्ठा tasklet_काष्ठा	txclean_task;
	काष्ठा work_काष्ठा	linkch_task;
	काष्ठा tasklet_काष्ठा	pcc_task;
	अचिन्हित दीर्घ		flags;
	u32			reg_txcs;
	u32			reg_txpfc;
	u32			reg_rxcs;
	u32			reg_rxmcs;
	u32			reg_ghc;
	u32			reg_pmcs;
	u32			reg_gpreg1;
	u32			phylink;
	u32			tx_ring_size;
	u32			tx_ring_mask;
	u32			tx_wake_threshold;
	u32			rx_ring_size;
	u32			rx_ring_mask;
	u8			mrrs;
	अचिन्हित पूर्णांक		fpgaver;
	u8			chiprev;
	u8			chip_मुख्य_rev;
	u8			chip_sub_rev;
	u8			pcirev;
	u32			msg_enable;
	काष्ठा ethtool_link_ksettings old_cmd;
	अचिन्हित पूर्णांक		old_mtu;
	काष्ठा dynpcc_info	dpi;
	atomic_t		पूर्णांकr_sem;
	atomic_t		link_changing;
	atomic_t		tx_cleaning;
	atomic_t		rx_cleaning;
	atomic_t		rx_empty;
	पूर्णांक			(*jme_rx)(काष्ठा sk_buff *skb);
	DECLARE_NAPI_STRUCT
	DECLARE_NET_DEVICE_STATS
पूर्ण;

क्रमागत jme_flags_bits अणु
	JME_FLAG_MSI		= 1,
	JME_FLAG_SSET		= 2,
	JME_FLAG_POLL		= 5,
	JME_FLAG_SHUTDOWN	= 6,
पूर्ण;

#घोषणा TX_TIMEOUT		(5 * HZ)
#घोषणा JME_REG_LEN		0x500
#घोषणा MAX_ETHERNET_JUMBO_PACKET_SIZE 9216

अटल अंतरभूत काष्ठा jme_adapter*
jme_napi_priv(काष्ठा napi_काष्ठा *napi)
अणु
	काष्ठा jme_adapter *jme;
	jme = container_of(napi, काष्ठा jme_adapter, napi);
	वापस jme;
पूर्ण

/*
 * MMaped I/O Resters
 */
क्रमागत jme_iomap_offsets अणु
	JME_MAC		= 0x0000,
	JME_PHY		= 0x0400,
	JME_MISC	= 0x0800,
	JME_RSS		= 0x0C00,
पूर्ण;

क्रमागत jme_iomap_lens अणु
	JME_MAC_LEN	= 0x80,
	JME_PHY_LEN	= 0x58,
	JME_MISC_LEN	= 0x98,
	JME_RSS_LEN	= 0xFF,
पूर्ण;

क्रमागत jme_iomap_regs अणु
	JME_TXCS	= JME_MAC | 0x00, /* Transmit Control and Status */
	JME_TXDBA_LO	= JME_MAC | 0x04, /* Transmit Queue Desc Base Addr */
	JME_TXDBA_HI	= JME_MAC | 0x08, /* Transmit Queue Desc Base Addr */
	JME_TXQDC	= JME_MAC | 0x0C, /* Transmit Queue Desc Count */
	JME_TXNDA	= JME_MAC | 0x10, /* Transmit Queue Next Desc Addr */
	JME_TXMCS	= JME_MAC | 0x14, /* Transmit MAC Control Status */
	JME_TXPFC	= JME_MAC | 0x18, /* Transmit Pause Frame Control */
	JME_TXTRHD	= JME_MAC | 0x1C, /* Transmit Timer/Retry@Half-Dup */

	JME_RXCS	= JME_MAC | 0x20, /* Receive Control and Status */
	JME_RXDBA_LO	= JME_MAC | 0x24, /* Receive Queue Desc Base Addr */
	JME_RXDBA_HI	= JME_MAC | 0x28, /* Receive Queue Desc Base Addr */
	JME_RXQDC	= JME_MAC | 0x2C, /* Receive Queue Desc Count */
	JME_RXNDA	= JME_MAC | 0x30, /* Receive Queue Next Desc Addr */
	JME_RXMCS	= JME_MAC | 0x34, /* Receive MAC Control Status */
	JME_RXUMA_LO	= JME_MAC | 0x38, /* Receive Unicast MAC Address */
	JME_RXUMA_HI	= JME_MAC | 0x3C, /* Receive Unicast MAC Address */
	JME_RXMCHT_LO	= JME_MAC | 0x40, /* Recv Multicast Addr HashTable */
	JME_RXMCHT_HI	= JME_MAC | 0x44, /* Recv Multicast Addr HashTable */
	JME_WFODP	= JME_MAC | 0x48, /* Wakeup Frame Output Data Port */
	JME_WFOI	= JME_MAC | 0x4C, /* Wakeup Frame Output Interface */

	JME_SMI		= JME_MAC | 0x50, /* Station Management Interface */
	JME_GHC		= JME_MAC | 0x54, /* Global Host Control */
	JME_PMCS	= JME_MAC | 0x60, /* Power Management Control/Stat */


	JME_PHY_PWR	= JME_PHY | 0x24, /* New PHY Power Ctrl Register */
	JME_PHY_CS	= JME_PHY | 0x28, /* PHY Ctrl and Status Register */
	JME_PHY_LINK	= JME_PHY | 0x30, /* PHY Link Status Register */
	JME_SMBCSR	= JME_PHY | 0x40, /* SMB Control and Status */
	JME_SMBINTF	= JME_PHY | 0x44, /* SMB Interface */


	JME_TMCSR	= JME_MISC | 0x00, /* Timer Control/Status Register */
	JME_GPREG0	= JME_MISC | 0x08, /* General purpose REG-0 */
	JME_GPREG1	= JME_MISC | 0x0C, /* General purpose REG-1 */
	JME_IEVE	= JME_MISC | 0x20, /* Interrupt Event Status */
	JME_IREQ	= JME_MISC | 0x24, /* Intr Req Status(For Debug) */
	JME_IENS	= JME_MISC | 0x28, /* Intr Enable - Setting Port */
	JME_IENC	= JME_MISC | 0x2C, /* Interrupt Enable - Clear Port */
	JME_PCCRX0	= JME_MISC | 0x30, /* PCC Control क्रम RX Queue 0 */
	JME_PCCTX	= JME_MISC | 0x40, /* PCC Control क्रम TX Queues */
	JME_CHIPMODE	= JME_MISC | 0x44, /* Identअगरy FPGA Version */
	JME_SHBA_HI	= JME_MISC | 0x48, /* Shaकरोw Register Base HI */
	JME_SHBA_LO	= JME_MISC | 0x4C, /* Shaकरोw Register Base LO */
	JME_TIMER1	= JME_MISC | 0x70, /* Timer1 */
	JME_TIMER2	= JME_MISC | 0x74, /* Timer2 */
	JME_APMC	= JME_MISC | 0x7C, /* Aggressive Power Mode Control */
	JME_PCCSRX0	= JME_MISC | 0x80, /* PCC Status of RX0 */
पूर्ण;

/*
 * TX Control/Status Bits
 */
क्रमागत jme_txcs_bits अणु
	TXCS_QUEUE7S	= 0x00008000,
	TXCS_QUEUE6S	= 0x00004000,
	TXCS_QUEUE5S	= 0x00002000,
	TXCS_QUEUE4S	= 0x00001000,
	TXCS_QUEUE3S	= 0x00000800,
	TXCS_QUEUE2S	= 0x00000400,
	TXCS_QUEUE1S	= 0x00000200,
	TXCS_QUEUE0S	= 0x00000100,
	TXCS_FIFOTH	= 0x000000C0,
	TXCS_DMASIZE	= 0x00000030,
	TXCS_BURST	= 0x00000004,
	TXCS_ENABLE	= 0x00000001,
पूर्ण;

क्रमागत jme_txcs_value अणु
	TXCS_FIFOTH_16QW	= 0x000000C0,
	TXCS_FIFOTH_12QW	= 0x00000080,
	TXCS_FIFOTH_8QW		= 0x00000040,
	TXCS_FIFOTH_4QW		= 0x00000000,

	TXCS_DMASIZE_64B	= 0x00000000,
	TXCS_DMASIZE_128B	= 0x00000010,
	TXCS_DMASIZE_256B	= 0x00000020,
	TXCS_DMASIZE_512B	= 0x00000030,

	TXCS_SELECT_QUEUE0	= 0x00000000,
	TXCS_SELECT_QUEUE1	= 0x00010000,
	TXCS_SELECT_QUEUE2	= 0x00020000,
	TXCS_SELECT_QUEUE3	= 0x00030000,
	TXCS_SELECT_QUEUE4	= 0x00040000,
	TXCS_SELECT_QUEUE5	= 0x00050000,
	TXCS_SELECT_QUEUE6	= 0x00060000,
	TXCS_SELECT_QUEUE7	= 0x00070000,

	TXCS_DEFAULT		= TXCS_FIFOTH_4QW |
				  TXCS_BURST,
पूर्ण;

#घोषणा JME_TX_DISABLE_TIMEOUT 10 /* 10 msec */

/*
 * TX MAC Control/Status Bits
 */
क्रमागत jme_txmcs_bit_masks अणु
	TXMCS_IFG2		= 0xC0000000,
	TXMCS_IFG1		= 0x30000000,
	TXMCS_TTHOLD		= 0x00000300,
	TXMCS_FBURST		= 0x00000080,
	TXMCS_CARRIEREXT	= 0x00000040,
	TXMCS_DEFER		= 0x00000020,
	TXMCS_BACKOFF		= 0x00000010,
	TXMCS_CARRIERSENSE	= 0x00000008,
	TXMCS_COLLISION		= 0x00000004,
	TXMCS_CRC		= 0x00000002,
	TXMCS_PADDING		= 0x00000001,
पूर्ण;

क्रमागत jme_txmcs_values अणु
	TXMCS_IFG2_6_4		= 0x00000000,
	TXMCS_IFG2_8_5		= 0x40000000,
	TXMCS_IFG2_10_6		= 0x80000000,
	TXMCS_IFG2_12_7		= 0xC0000000,

	TXMCS_IFG1_8_4		= 0x00000000,
	TXMCS_IFG1_12_6		= 0x10000000,
	TXMCS_IFG1_16_8		= 0x20000000,
	TXMCS_IFG1_20_10	= 0x30000000,

	TXMCS_TTHOLD_1_8	= 0x00000000,
	TXMCS_TTHOLD_1_4	= 0x00000100,
	TXMCS_TTHOLD_1_2	= 0x00000200,
	TXMCS_TTHOLD_FULL	= 0x00000300,

	TXMCS_DEFAULT		= TXMCS_IFG2_8_5 |
				  TXMCS_IFG1_16_8 |
				  TXMCS_TTHOLD_FULL |
				  TXMCS_DEFER |
				  TXMCS_CRC |
				  TXMCS_PADDING,
पूर्ण;

क्रमागत jme_txpfc_bits_masks अणु
	TXPFC_VLAN_TAG		= 0xFFFF0000,
	TXPFC_VLAN_EN		= 0x00008000,
	TXPFC_PF_EN		= 0x00000001,
पूर्ण;

क्रमागत jme_txtrhd_bits_masks अणु
	TXTRHD_TXPEN		= 0x80000000,
	TXTRHD_TXP		= 0x7FFFFF00,
	TXTRHD_TXREN		= 0x00000080,
	TXTRHD_TXRL		= 0x0000007F,
पूर्ण;

क्रमागत jme_txtrhd_shअगरts अणु
	TXTRHD_TXP_SHIFT	= 8,
	TXTRHD_TXRL_SHIFT	= 0,
पूर्ण;

क्रमागत jme_txtrhd_values अणु
	TXTRHD_FULLDUPLEX	= 0x00000000,
	TXTRHD_HALFDUPLEX	= TXTRHD_TXPEN |
				  ((0x2000 << TXTRHD_TXP_SHIFT) & TXTRHD_TXP) |
				  TXTRHD_TXREN |
				  ((8 << TXTRHD_TXRL_SHIFT) & TXTRHD_TXRL),
पूर्ण;

/*
 * RX Control/Status Bits
 */
क्रमागत jme_rxcs_bit_masks अणु
	/* FIFO full threshold क्रम transmitting Tx Pause Packet */
	RXCS_FIFOTHTP	= 0x30000000,
	/* FIFO threshold क्रम processing next packet */
	RXCS_FIFOTHNP	= 0x0C000000,
	RXCS_DMAREQSZ	= 0x03000000, /* DMA Request Size */
	RXCS_QUEUESEL	= 0x00030000, /* Queue selection */
	RXCS_RETRYGAP	= 0x0000F000, /* RX Desc full retry gap */
	RXCS_RETRYCNT	= 0x00000F00, /* RX Desc full retry counter */
	RXCS_WAKEUP	= 0x00000040, /* Enable receive wakeup packet */
	RXCS_MAGIC	= 0x00000020, /* Enable receive magic packet */
	RXCS_SHORT	= 0x00000010, /* Enable receive लघु packet */
	RXCS_ABORT	= 0x00000008, /* Enable receive errorr packet */
	RXCS_QST	= 0x00000004, /* Receive queue start */
	RXCS_SUSPEND	= 0x00000002,
	RXCS_ENABLE	= 0x00000001,
पूर्ण;

क्रमागत jme_rxcs_values अणु
	RXCS_FIFOTHTP_16T	= 0x00000000,
	RXCS_FIFOTHTP_32T	= 0x10000000,
	RXCS_FIFOTHTP_64T	= 0x20000000,
	RXCS_FIFOTHTP_128T	= 0x30000000,

	RXCS_FIFOTHNP_16QW	= 0x00000000,
	RXCS_FIFOTHNP_32QW	= 0x04000000,
	RXCS_FIFOTHNP_64QW	= 0x08000000,
	RXCS_FIFOTHNP_128QW	= 0x0C000000,

	RXCS_DMAREQSZ_16B	= 0x00000000,
	RXCS_DMAREQSZ_32B	= 0x01000000,
	RXCS_DMAREQSZ_64B	= 0x02000000,
	RXCS_DMAREQSZ_128B	= 0x03000000,

	RXCS_QUEUESEL_Q0	= 0x00000000,
	RXCS_QUEUESEL_Q1	= 0x00010000,
	RXCS_QUEUESEL_Q2	= 0x00020000,
	RXCS_QUEUESEL_Q3	= 0x00030000,

	RXCS_RETRYGAP_256ns	= 0x00000000,
	RXCS_RETRYGAP_512ns	= 0x00001000,
	RXCS_RETRYGAP_1024ns	= 0x00002000,
	RXCS_RETRYGAP_2048ns	= 0x00003000,
	RXCS_RETRYGAP_4096ns	= 0x00004000,
	RXCS_RETRYGAP_8192ns	= 0x00005000,
	RXCS_RETRYGAP_16384ns	= 0x00006000,
	RXCS_RETRYGAP_32768ns	= 0x00007000,

	RXCS_RETRYCNT_0		= 0x00000000,
	RXCS_RETRYCNT_4		= 0x00000100,
	RXCS_RETRYCNT_8		= 0x00000200,
	RXCS_RETRYCNT_12	= 0x00000300,
	RXCS_RETRYCNT_16	= 0x00000400,
	RXCS_RETRYCNT_20	= 0x00000500,
	RXCS_RETRYCNT_24	= 0x00000600,
	RXCS_RETRYCNT_28	= 0x00000700,
	RXCS_RETRYCNT_32	= 0x00000800,
	RXCS_RETRYCNT_36	= 0x00000900,
	RXCS_RETRYCNT_40	= 0x00000A00,
	RXCS_RETRYCNT_44	= 0x00000B00,
	RXCS_RETRYCNT_48	= 0x00000C00,
	RXCS_RETRYCNT_52	= 0x00000D00,
	RXCS_RETRYCNT_56	= 0x00000E00,
	RXCS_RETRYCNT_60	= 0x00000F00,

	RXCS_DEFAULT		= RXCS_FIFOTHTP_128T |
				  RXCS_FIFOTHNP_16QW |
				  RXCS_DMAREQSZ_128B |
				  RXCS_RETRYGAP_256ns |
				  RXCS_RETRYCNT_32,
पूर्ण;

#घोषणा JME_RX_DISABLE_TIMEOUT 10 /* 10 msec */

/*
 * RX MAC Control/Status Bits
 */
क्रमागत jme_rxmcs_bits अणु
	RXMCS_ALLFRAME		= 0x00000800,
	RXMCS_BRDFRAME		= 0x00000400,
	RXMCS_MULFRAME		= 0x00000200,
	RXMCS_UNIFRAME		= 0x00000100,
	RXMCS_ALLMULFRAME	= 0x00000080,
	RXMCS_MULFILTERED	= 0x00000040,
	RXMCS_RXCOLLDEC		= 0x00000020,
	RXMCS_FLOWCTRL		= 0x00000008,
	RXMCS_VTAGRM		= 0x00000004,
	RXMCS_PREPAD		= 0x00000002,
	RXMCS_CHECKSUM		= 0x00000001,

	RXMCS_DEFAULT		= RXMCS_VTAGRM |
				  RXMCS_PREPAD |
				  RXMCS_FLOWCTRL |
				  RXMCS_CHECKSUM,
पूर्ण;

/*	Extern PHY common रेजिस्टर 2	*/

#घोषणा PHY_GAD_TEST_MODE_1			0x00002000
#घोषणा PHY_GAD_TEST_MODE_MSK			0x0000E000
#घोषणा JM_PHY_SPEC_REG_READ			0x00004000
#घोषणा JM_PHY_SPEC_REG_WRITE			0x00008000
#घोषणा PHY_CALIBRATION_DELAY			20
#घोषणा JM_PHY_SPEC_ADDR_REG			0x1E
#घोषणा JM_PHY_SPEC_DATA_REG			0x1F

#घोषणा JM_PHY_EXT_COMM_0_REG			0x30
#घोषणा JM_PHY_EXT_COMM_1_REG			0x31
#घोषणा JM_PHY_EXT_COMM_2_REG			0x32
#घोषणा JM_PHY_EXT_COMM_2_CALI_ENABLE		0x01
#घोषणा JM_PHY_EXT_COMM_2_CALI_MODE_0		0x02
#घोषणा JM_PHY_EXT_COMM_2_CALI_LATCH		0x10
#घोषणा PCI_PRIV_SHARE_NICCTRL			0xF5
#घोषणा JME_FLAG_PHYEA_ENABLE			0x2

/*
 * Wakeup Frame setup पूर्णांकerface रेजिस्टरs
 */
#घोषणा WAKEUP_FRAME_NR	8
#घोषणा WAKEUP_FRAME_MASK_DWNR	4

क्रमागत jme_wfoi_bit_masks अणु
	WFOI_MASK_SEL		= 0x00000070,
	WFOI_CRC_SEL		= 0x00000008,
	WFOI_FRAME_SEL		= 0x00000007,
पूर्ण;

क्रमागत jme_wfoi_shअगरts अणु
	WFOI_MASK_SHIFT		= 4,
पूर्ण;

/*
 * SMI Related definitions
 */
क्रमागत jme_smi_bit_mask अणु
	SMI_DATA_MASK		= 0xFFFF0000,
	SMI_REG_ADDR_MASK	= 0x0000F800,
	SMI_PHY_ADDR_MASK	= 0x000007C0,
	SMI_OP_WRITE		= 0x00000020,
	/* Set to 1, after req करोne it'll be cleared to 0 */
	SMI_OP_REQ		= 0x00000010,
	SMI_OP_MDIO		= 0x00000008, /* Software assess In/Out */
	SMI_OP_MDOE		= 0x00000004, /* Software Output Enable */
	SMI_OP_MDC		= 0x00000002, /* Software CLK Control */
	SMI_OP_MDEN		= 0x00000001, /* Software access Enable */
पूर्ण;

क्रमागत jme_smi_bit_shअगरt अणु
	SMI_DATA_SHIFT		= 16,
	SMI_REG_ADDR_SHIFT	= 11,
	SMI_PHY_ADDR_SHIFT	= 6,
पूर्ण;

अटल अंतरभूत u32 smi_reg_addr(पूर्णांक x)
अणु
	वापस (x << SMI_REG_ADDR_SHIFT) & SMI_REG_ADDR_MASK;
पूर्ण

अटल अंतरभूत u32 smi_phy_addr(पूर्णांक x)
अणु
	वापस (x << SMI_PHY_ADDR_SHIFT) & SMI_PHY_ADDR_MASK;
पूर्ण

#घोषणा JME_PHY_TIMEOUT 100 /* 100 msec */
#घोषणा JME_PHY_REG_NR 32

/*
 * Global Host Control
 */
क्रमागत jme_ghc_bit_mask अणु
	GHC_SWRST		= 0x40000000,
	GHC_TO_CLK_SRC		= 0x00C00000,
	GHC_TXMAC_CLK_SRC	= 0x00300000,
	GHC_DPX			= 0x00000040,
	GHC_SPEED		= 0x00000030,
	GHC_LINK_POLL		= 0x00000001,
पूर्ण;

क्रमागत jme_ghc_speed_val अणु
	GHC_SPEED_10M		= 0x00000010,
	GHC_SPEED_100M		= 0x00000020,
	GHC_SPEED_1000M		= 0x00000030,
पूर्ण;

क्रमागत jme_ghc_to_clk अणु
	GHC_TO_CLK_OFF		= 0x00000000,
	GHC_TO_CLK_GPHY		= 0x00400000,
	GHC_TO_CLK_PCIE		= 0x00800000,
	GHC_TO_CLK_INVALID	= 0x00C00000,
पूर्ण;

क्रमागत jme_ghc_txmac_clk अणु
	GHC_TXMAC_CLK_OFF	= 0x00000000,
	GHC_TXMAC_CLK_GPHY	= 0x00100000,
	GHC_TXMAC_CLK_PCIE	= 0x00200000,
	GHC_TXMAC_CLK_INVALID	= 0x00300000,
पूर्ण;

/*
 * Power management control and status रेजिस्टर
 */
क्रमागत jme_pmcs_bit_masks अणु
	PMCS_STMASK	= 0xFFFF0000,
	PMCS_WF7DET	= 0x80000000,
	PMCS_WF6DET	= 0x40000000,
	PMCS_WF5DET	= 0x20000000,
	PMCS_WF4DET	= 0x10000000,
	PMCS_WF3DET	= 0x08000000,
	PMCS_WF2DET	= 0x04000000,
	PMCS_WF1DET	= 0x02000000,
	PMCS_WF0DET	= 0x01000000,
	PMCS_LFDET	= 0x00040000,
	PMCS_LRDET	= 0x00020000,
	PMCS_MFDET	= 0x00010000,
	PMCS_ENMASK	= 0x0000FFFF,
	PMCS_WF7EN	= 0x00008000,
	PMCS_WF6EN	= 0x00004000,
	PMCS_WF5EN	= 0x00002000,
	PMCS_WF4EN	= 0x00001000,
	PMCS_WF3EN	= 0x00000800,
	PMCS_WF2EN	= 0x00000400,
	PMCS_WF1EN	= 0x00000200,
	PMCS_WF0EN	= 0x00000100,
	PMCS_LFEN	= 0x00000004,
	PMCS_LREN	= 0x00000002,
	PMCS_MFEN	= 0x00000001,
पूर्ण;

/*
 * New PHY Power Control Register
 */
क्रमागत jme_phy_pwr_bit_masks अणु
	PHY_PWR_DWN1SEL	= 0x01000000, /* Phy_giga.p_PWR_DOWN1_SEL */
	PHY_PWR_DWN1SW	= 0x02000000, /* Phy_giga.p_PWR_DOWN1_SW */
	PHY_PWR_DWN2	= 0x04000000, /* Phy_giga.p_PWR_DOWN2 */
	PHY_PWR_CLKSEL	= 0x08000000, /*
				       * XTL_OUT Clock select
				       * (an पूर्णांकernal मुक्त-running घड़ी)
				       * 0: xtl_out = phy_giga.A_XTL25_O
				       * 1: xtl_out = phy_giga.PD_OSC
				       */
पूर्ण;

/*
 * Giga PHY Status Registers
 */
क्रमागत jme_phy_link_bit_mask अणु
	PHY_LINK_SPEED_MASK		= 0x0000C000,
	PHY_LINK_DUPLEX			= 0x00002000,
	PHY_LINK_SPEEDDPU_RESOLVED	= 0x00000800,
	PHY_LINK_UP			= 0x00000400,
	PHY_LINK_AUTONEG_COMPLETE	= 0x00000200,
	PHY_LINK_MDI_STAT		= 0x00000040,
पूर्ण;

क्रमागत jme_phy_link_speed_val अणु
	PHY_LINK_SPEED_10M		= 0x00000000,
	PHY_LINK_SPEED_100M		= 0x00004000,
	PHY_LINK_SPEED_1000M		= 0x00008000,
पूर्ण;

#घोषणा JME_SPDRSV_TIMEOUT	500	/* 500 us */

/*
 * SMB Control and Status
 */
क्रमागत jme_smbcsr_bit_mask अणु
	SMBCSR_CNACK	= 0x00020000,
	SMBCSR_RELOAD	= 0x00010000,
	SMBCSR_EEPROMD	= 0x00000020,
	SMBCSR_INITDONE	= 0x00000010,
	SMBCSR_BUSY	= 0x0000000F,
पूर्ण;

क्रमागत jme_smbपूर्णांकf_bit_mask अणु
	SMBINTF_HWDATR	= 0xFF000000,
	SMBINTF_HWDATW	= 0x00FF0000,
	SMBINTF_HWADDR	= 0x0000FF00,
	SMBINTF_HWRWN	= 0x00000020,
	SMBINTF_HWCMD	= 0x00000010,
	SMBINTF_FASTM	= 0x00000008,
	SMBINTF_GPIOSCL	= 0x00000004,
	SMBINTF_GPIOSDA	= 0x00000002,
	SMBINTF_GPIOEN	= 0x00000001,
पूर्ण;

क्रमागत jme_smbपूर्णांकf_vals अणु
	SMBINTF_HWRWN_READ	= 0x00000020,
	SMBINTF_HWRWN_WRITE	= 0x00000000,
पूर्ण;

क्रमागत jme_smbपूर्णांकf_shअगरts अणु
	SMBINTF_HWDATR_SHIFT	= 24,
	SMBINTF_HWDATW_SHIFT	= 16,
	SMBINTF_HWADDR_SHIFT	= 8,
पूर्ण;

#घोषणा JME_EEPROM_RELOAD_TIMEOUT 2000 /* 2000 msec */
#घोषणा JME_SMB_BUSY_TIMEOUT 20 /* 20 msec */
#घोषणा JME_SMB_LEN 256
#घोषणा JME_EEPROM_MAGIC 0x250

/*
 * Timer Control/Status Register
 */
क्रमागत jme_पंचांगcsr_bit_masks अणु
	TMCSR_SWIT	= 0x80000000,
	TMCSR_EN	= 0x01000000,
	TMCSR_CNT	= 0x00FFFFFF,
पूर्ण;

/*
 * General Purpose REG-0
 */
क्रमागत jme_gpreg0_masks अणु
	GPREG0_DISSH		= 0xFF000000,
	GPREG0_PCIRLMT		= 0x00300000,
	GPREG0_PCCNOMUTCLR	= 0x00040000,
	GPREG0_LNKINTPOLL	= 0x00001000,
	GPREG0_PCCTMR		= 0x00000300,
	GPREG0_PHYADDR		= 0x0000001F,
पूर्ण;

क्रमागत jme_gpreg0_vals अणु
	GPREG0_DISSH_DW7	= 0x80000000,
	GPREG0_DISSH_DW6	= 0x40000000,
	GPREG0_DISSH_DW5	= 0x20000000,
	GPREG0_DISSH_DW4	= 0x10000000,
	GPREG0_DISSH_DW3	= 0x08000000,
	GPREG0_DISSH_DW2	= 0x04000000,
	GPREG0_DISSH_DW1	= 0x02000000,
	GPREG0_DISSH_DW0	= 0x01000000,
	GPREG0_DISSH_ALL	= 0xFF000000,

	GPREG0_PCIRLMT_8	= 0x00000000,
	GPREG0_PCIRLMT_6	= 0x00100000,
	GPREG0_PCIRLMT_5	= 0x00200000,
	GPREG0_PCIRLMT_4	= 0x00300000,

	GPREG0_PCCTMR_16ns	= 0x00000000,
	GPREG0_PCCTMR_256ns	= 0x00000100,
	GPREG0_PCCTMR_1us	= 0x00000200,
	GPREG0_PCCTMR_1ms	= 0x00000300,

	GPREG0_PHYADDR_1	= 0x00000001,

	GPREG0_DEFAULT		= GPREG0_PCIRLMT_4 |
				  GPREG0_PCCTMR_1us |
				  GPREG0_PHYADDR_1,
पूर्ण;

/*
 * General Purpose REG-1
 */
क्रमागत jme_gpreg1_bit_masks अणु
	GPREG1_RXCLKOFF		= 0x04000000,
	GPREG1_PCREQN		= 0x00020000,
	GPREG1_HALFMODEPATCH	= 0x00000040, /* For Chip revision 0x11 only */
	GPREG1_RSSPATCH		= 0x00000020, /* For Chip revision 0x11 only */
	GPREG1_INTRDELAYUNIT	= 0x00000018,
	GPREG1_INTRDELAYENABLE	= 0x00000007,
पूर्ण;

क्रमागत jme_gpreg1_vals अणु
	GPREG1_INTDLYUNIT_16NS	= 0x00000000,
	GPREG1_INTDLYUNIT_256NS	= 0x00000008,
	GPREG1_INTDLYUNIT_1US	= 0x00000010,
	GPREG1_INTDLYUNIT_16US	= 0x00000018,

	GPREG1_INTDLYEN_1U	= 0x00000001,
	GPREG1_INTDLYEN_2U	= 0x00000002,
	GPREG1_INTDLYEN_3U	= 0x00000003,
	GPREG1_INTDLYEN_4U	= 0x00000004,
	GPREG1_INTDLYEN_5U	= 0x00000005,
	GPREG1_INTDLYEN_6U	= 0x00000006,
	GPREG1_INTDLYEN_7U	= 0x00000007,

	GPREG1_DEFAULT		= GPREG1_PCREQN,
पूर्ण;

/*
 * Interrupt Status Bits
 */
क्रमागत jme_पूर्णांकerrupt_bits अणु
	INTR_SWINTR	= 0x80000000,
	INTR_TMINTR	= 0x40000000,
	INTR_LINKCH	= 0x20000000,
	INTR_PAUSERCV	= 0x10000000,
	INTR_MAGICRCV	= 0x08000000,
	INTR_WAKERCV	= 0x04000000,
	INTR_PCCRX0TO	= 0x02000000,
	INTR_PCCRX1TO	= 0x01000000,
	INTR_PCCRX2TO	= 0x00800000,
	INTR_PCCRX3TO	= 0x00400000,
	INTR_PCCTXTO	= 0x00200000,
	INTR_PCCRX0	= 0x00100000,
	INTR_PCCRX1	= 0x00080000,
	INTR_PCCRX2	= 0x00040000,
	INTR_PCCRX3	= 0x00020000,
	INTR_PCCTX	= 0x00010000,
	INTR_RX3EMP	= 0x00008000,
	INTR_RX2EMP	= 0x00004000,
	INTR_RX1EMP	= 0x00002000,
	INTR_RX0EMP	= 0x00001000,
	INTR_RX3	= 0x00000800,
	INTR_RX2	= 0x00000400,
	INTR_RX1	= 0x00000200,
	INTR_RX0	= 0x00000100,
	INTR_TX7	= 0x00000080,
	INTR_TX6	= 0x00000040,
	INTR_TX5	= 0x00000020,
	INTR_TX4	= 0x00000010,
	INTR_TX3	= 0x00000008,
	INTR_TX2	= 0x00000004,
	INTR_TX1	= 0x00000002,
	INTR_TX0	= 0x00000001,
पूर्ण;

अटल स्थिर u32 INTR_ENABLE = INTR_SWINTR |
				 INTR_TMINTR |
				 INTR_LINKCH |
				 INTR_PCCRX0TO |
				 INTR_PCCRX0 |
				 INTR_PCCTXTO |
				 INTR_PCCTX |
				 INTR_RX0EMP;

/*
 * PCC Control Registers
 */
क्रमागत jme_pccrx_masks अणु
	PCCRXTO_MASK	= 0xFFFF0000,
	PCCRX_MASK	= 0x0000FF00,
पूर्ण;

क्रमागत jme_pcctx_masks अणु
	PCCTXTO_MASK	= 0xFFFF0000,
	PCCTX_MASK	= 0x0000FF00,
	PCCTX_QS_MASK	= 0x000000FF,
पूर्ण;

क्रमागत jme_pccrx_shअगरts अणु
	PCCRXTO_SHIFT	= 16,
	PCCRX_SHIFT	= 8,
पूर्ण;

क्रमागत jme_pcctx_shअगरts अणु
	PCCTXTO_SHIFT	= 16,
	PCCTX_SHIFT	= 8,
पूर्ण;

क्रमागत jme_pcctx_bits अणु
	PCCTXQ0_EN	= 0x00000001,
	PCCTXQ1_EN	= 0x00000002,
	PCCTXQ2_EN	= 0x00000004,
	PCCTXQ3_EN	= 0x00000008,
	PCCTXQ4_EN	= 0x00000010,
	PCCTXQ5_EN	= 0x00000020,
	PCCTXQ6_EN	= 0x00000040,
	PCCTXQ7_EN	= 0x00000080,
पूर्ण;

/*
 * Chip Mode Register
 */
क्रमागत jme_chipmode_bit_masks अणु
	CM_FPGAVER_MASK		= 0xFFFF0000,
	CM_CHIPREV_MASK		= 0x0000FF00,
	CM_CHIPMODE_MASK	= 0x0000000F,
पूर्ण;

क्रमागत jme_chipmode_shअगरts अणु
	CM_FPGAVER_SHIFT	= 16,
	CM_CHIPREV_SHIFT	= 8,
पूर्ण;

/*
 * Aggressive Power Mode Control
 */
क्रमागत jme_apmc_bits अणु
	JME_APMC_PCIE_SD_EN	= 0x40000000,
	JME_APMC_PSEUDO_HP_EN	= 0x20000000,
	JME_APMC_EPIEN		= 0x04000000,
	JME_APMC_EPIEN_CTRL	= 0x03000000,
पूर्ण;

क्रमागत jme_apmc_values अणु
	JME_APMC_EPIEN_CTRL_EN	= 0x02000000,
	JME_APMC_EPIEN_CTRL_DIS	= 0x01000000,
पूर्ण;

#घोषणा APMC_PHP_SHUTDOWN_DELAY	(10 * 1000 * 1000)

#अगर_घोषित REG_DEBUG
अटल अक्षर *MAC_REG_NAME[] = अणु
	"JME_TXCS",      "JME_TXDBA_LO",  "JME_TXDBA_HI", "JME_TXQDC",
	"JME_TXNDA",     "JME_TXMCS",     "JME_TXPFC",    "JME_TXTRHD",
	"JME_RXCS",      "JME_RXDBA_LO",  "JME_RXDBA_HI", "JME_RXQDC",
	"JME_RXNDA",     "JME_RXMCS",     "JME_RXUMA_LO", "JME_RXUMA_HI",
	"JME_RXMCHT_LO", "JME_RXMCHT_HI", "JME_WFODP",    "JME_WFOI",
	"JME_SMI",       "JME_GHC",       "UNKNOWN",      "UNKNOWN",
	"JME_PMCS"पूर्ण;

अटल अक्षर *PE_REG_NAME[] = अणु
	"UNKNOWN",      "UNKNOWN",     "UNKNOWN",    "UNKNOWN",
	"UNKNOWN",      "UNKNOWN",     "UNKNOWN",    "UNKNOWN",
	"UNKNOWN",      "UNKNOWN",     "JME_PHY_CS", "UNKNOWN",
	"JME_PHY_LINK", "UNKNOWN",     "UNKNOWN",    "UNKNOWN",
	"JME_SMBCSR",   "JME_SMBINTF"पूर्ण;

अटल अक्षर *MISC_REG_NAME[] = अणु
	"JME_TMCSR",  "JME_GPIO",     "JME_GPREG0",  "JME_GPREG1",
	"JME_IEVE",   "JME_IREQ",     "JME_IENS",    "JME_IENC",
	"JME_PCCRX0", "JME_PCCRX1",   "JME_PCCRX2",  "JME_PCCRX3",
	"JME_PCCTX0", "JME_CHIPMODE", "JME_SHBA_HI", "JME_SHBA_LO",
	"UNKNOWN",    "UNKNOWN",      "UNKNOWN",     "UNKNOWN",
	"UNKNOWN",    "UNKNOWN",      "UNKNOWN",     "UNKNOWN",
	"UNKNOWN",    "UNKNOWN",      "UNKNOWN",     "UNKNOWN",
	"JME_TIMER1", "JME_TIMER2",   "UNKNOWN",     "JME_APMC",
	"JME_PCCSRX0"पूर्ण;

अटल अंतरभूत व्योम reg_dbg(स्थिर काष्ठा jme_adapter *jme,
		स्थिर अक्षर *msg, u32 val, u32 reg)
अणु
	स्थिर अक्षर *regname;
	चयन (reg & 0xF00) अणु
	हाल 0x000:
		regname = MAC_REG_NAME[(reg & 0xFF) >> 2];
		अवरोध;
	हाल 0x400:
		regname = PE_REG_NAME[(reg & 0xFF) >> 2];
		अवरोध;
	हाल 0x800:
		regname = MISC_REG_NAME[(reg & 0xFF) >> 2];
		अवरोध;
	शेष:
		regname = PE_REG_NAME[0];
	पूर्ण
	prपूर्णांकk(KERN_DEBUG "%s: %-20s %08x@%s\n", jme->dev->name,
			msg, val, regname);
पूर्ण
#अन्यथा
अटल अंतरभूत व्योम reg_dbg(स्थिर काष्ठा jme_adapter *jme,
		स्थिर अक्षर *msg, u32 val, u32 reg) अणुपूर्ण
#पूर्ण_अगर

/*
 * Read/Write MMaped I/O Registers
 */
अटल अंतरभूत u32 jपढ़ो32(काष्ठा jme_adapter *jme, u32 reg)
अणु
	वापस पढ़ोl(jme->regs + reg);
पूर्ण

अटल अंतरभूत व्योम jग_लिखो32(काष्ठा jme_adapter *jme, u32 reg, u32 val)
अणु
	reg_dbg(jme, "REG WRITE", val, reg);
	ग_लिखोl(val, jme->regs + reg);
	reg_dbg(jme, "VAL AFTER WRITE", पढ़ोl(jme->regs + reg), reg);
पूर्ण

अटल अंतरभूत व्योम jग_लिखो32f(काष्ठा jme_adapter *jme, u32 reg, u32 val)
अणु
	/*
	 * Read after ग_लिखो should cause flush
	 */
	reg_dbg(jme, "REG WRITE FLUSH", val, reg);
	ग_लिखोl(val, jme->regs + reg);
	पढ़ोl(jme->regs + reg);
	reg_dbg(jme, "VAL AFTER WRITE", पढ़ोl(jme->regs + reg), reg);
पूर्ण

/*
 * PHY Regs
 */
क्रमागत jme_phy_reg17_bit_masks अणु
	PREG17_SPEED		= 0xC000,
	PREG17_DUPLEX		= 0x2000,
	PREG17_SPDRSV		= 0x0800,
	PREG17_LNKUP		= 0x0400,
	PREG17_MDI		= 0x0040,
पूर्ण;

क्रमागत jme_phy_reg17_vals अणु
	PREG17_SPEED_10M	= 0x0000,
	PREG17_SPEED_100M	= 0x4000,
	PREG17_SPEED_1000M	= 0x8000,
पूर्ण;

#घोषणा BMSR_ANCOMP               0x0020

/*
 * Workaround
 */
अटल अंतरभूत पूर्णांक is_buggy250(अचिन्हित लघु device, u8 chiprev)
अणु
	वापस device == PCI_DEVICE_ID_JMICRON_JMC250 && chiprev == 0x11;
पूर्ण

अटल अंतरभूत पूर्णांक new_phy_घातer_ctrl(u8 chip_मुख्य_rev)
अणु
	वापस chip_मुख्य_rev >= 5;
पूर्ण

/*
 * Function prototypes
 */
अटल पूर्णांक jme_set_link_ksettings(काष्ठा net_device *netdev,
				  स्थिर काष्ठा ethtool_link_ksettings *cmd);
अटल व्योम jme_set_unicastaddr(काष्ठा net_device *netdev);
अटल व्योम jme_set_multi(काष्ठा net_device *netdev);

#पूर्ण_अगर
