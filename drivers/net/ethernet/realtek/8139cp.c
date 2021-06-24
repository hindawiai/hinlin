<शैली गुरु>
/* 8139cp.c: A Linux PCI Ethernet driver क्रम the RealTek 8139C+ chips. */
/*
	Copyright 2001-2004 Jeff Garzik <jgarzik@pobox.com>

	Copyright (C) 2001, 2002 David S. Miller (davem@redhat.com) [tg3.c]
	Copyright (C) 2000, 2001 David S. Miller (davem@redhat.com) [sungem.c]
	Copyright 2001 Manfred Spraul				    [natsemi.c]
	Copyright 1999-2001 by Donald Becker.			    [natsemi.c]
       	Written 1997-2001 by Donald Becker.			    [8139too.c]
	Copyright 1998-2001 by Jes Sorensen, <jes@trained-monkey.org>. [acenic.c]

	This software may be used and distributed according to the terms of
	the GNU General Public License (GPL), incorporated herein by reference.
	Drivers based on or derived from this code fall under the GPL and must
	retain the authorship, copyright and license notice.  This file is not
	a complete program and may only be used when the entire operating
	प्रणाली is licensed under the GPL.

	See the file COPYING in this distribution क्रम more inक्रमmation.

	Contributors:

		Wake-on-LAN support - Felipe Damasio <felipewd@terra.com.br>
		PCI suspend/resume  - Felipe Damasio <felipewd@terra.com.br>
		LinkChg पूर्णांकerrupt   - Felipe Damasio <felipewd@terra.com.br>

	TODO:
	* Test Tx checksumming thoroughly

	Low priority TODO:
	* Complete reset on PciErr
	* Consider Rx पूर्णांकerrupt mitigation using TimerIntr
	* Investigate using skb->priority with h/w VLAN priority
	* Investigate using High Priority Tx Queue with skb->priority
	* Adjust Rx FIFO threshold and Max Rx DMA burst on Rx FIFO error
	* Adjust Tx FIFO threshold and Max Tx DMA burst on Tx FIFO error
	* Implement Tx software पूर्णांकerrupt mitigation via
	  Tx descriptor bit
	* The real minimum of CP_MIN_MTU is 4 bytes.  However,
	  क्रम this to be supported, one must(?) turn on packet padding.
	* Support बाह्यal MII transceivers (patch available)

	NOTES:
	* TX checksumming is considered experimental.  It is off by
	  शेष, use ethtool to turn it on.

 */

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#घोषणा DRV_NAME		"8139cp"
#घोषणा DRV_VERSION		"1.3"
#घोषणा DRV_RELDATE		"Mar 22, 2004"


#समावेश <linux/module.h>
#समावेश <linux/moduleparam.h>
#समावेश <linux/kernel.h>
#समावेश <linux/compiler.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/etherdevice.h>
#समावेश <linux/init.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/pci.h>
#समावेश <linux/dma-mapping.h>
#समावेश <linux/delay.h>
#समावेश <linux/ethtool.h>
#समावेश <linux/gfp.h>
#समावेश <linux/mii.h>
#समावेश <linux/अगर_vlan.h>
#समावेश <linux/crc32.h>
#समावेश <linux/in.h>
#समावेश <linux/ip.h>
#समावेश <linux/tcp.h>
#समावेश <linux/udp.h>
#समावेश <linux/cache.h>
#समावेश <यंत्र/पन.स>
#समावेश <यंत्र/irq.h>
#समावेश <linux/uaccess.h>

/* These identअगरy the driver base version and may not be हटाओd. */
अटल अक्षर version[] =
DRV_NAME ": 10/100 PCI Ethernet driver v" DRV_VERSION " (" DRV_RELDATE ")\n";

MODULE_AUTHOR("Jeff Garzik <jgarzik@pobox.com>");
MODULE_DESCRIPTION("RealTek RTL-8139C+ series 10/100 PCI Ethernet driver");
MODULE_VERSION(DRV_VERSION);
MODULE_LICENSE("GPL");

अटल पूर्णांक debug = -1;
module_param(debug, पूर्णांक, 0);
MODULE_PARM_DESC (debug, "8139cp: bitmapped message enable number");

/* Maximum number of multicast addresses to filter (vs. Rx-all-multicast).
   The RTL chips use a 64 element hash table based on the Ethernet CRC.  */
अटल पूर्णांक multicast_filter_limit = 32;
module_param(multicast_filter_limit, पूर्णांक, 0);
MODULE_PARM_DESC (multicast_filter_limit, "8139cp: maximum number of filtered multicast addresses");

#घोषणा CP_DEF_MSG_ENABLE	(NETIF_MSG_DRV		| \
				 NETIF_MSG_PROBE 	| \
				 NETIF_MSG_LINK)
#घोषणा CP_NUM_STATS		14	/* काष्ठा cp_dma_stats, plus one */
#घोषणा CP_STATS_SIZE		64	/* size in bytes of DMA stats block */
#घोषणा CP_REGS_SIZE		(0xff + 1)
#घोषणा CP_REGS_VER		1		/* version 1 */
#घोषणा CP_RX_RING_SIZE		64
#घोषणा CP_TX_RING_SIZE		64
#घोषणा CP_RING_BYTES		\
		((माप(काष्ठा cp_desc) * CP_RX_RING_SIZE) +	\
		 (माप(काष्ठा cp_desc) * CP_TX_RING_SIZE) +	\
		 CP_STATS_SIZE)
#घोषणा NEXT_TX(N)		(((N) + 1) & (CP_TX_RING_SIZE - 1))
#घोषणा NEXT_RX(N)		(((N) + 1) & (CP_RX_RING_SIZE - 1))
#घोषणा TX_BUFFS_AVAIL(CP)					\
	(((CP)->tx_tail <= (CP)->tx_head) ?			\
	  (CP)->tx_tail + (CP_TX_RING_SIZE - 1) - (CP)->tx_head :	\
	  (CP)->tx_tail - (CP)->tx_head - 1)

#घोषणा PKT_BUF_SZ		1536	/* Size of each temporary Rx buffer.*/
#घोषणा CP_INTERNAL_PHY		32

/* The following settings are log_2(bytes)-4:  0 == 16 bytes .. 6==1024, 7==end of packet. */
#घोषणा RX_FIFO_THRESH		5	/* Rx buffer level beक्रमe first PCI xfer.  */
#घोषणा RX_DMA_BURST		4	/* Maximum PCI burst, '4' is 256 */
#घोषणा TX_DMA_BURST		6	/* Maximum PCI burst, '6' is 1024 */
#घोषणा TX_EARLY_THRESH		256	/* Early Tx threshold, in bytes */

/* Time in jअगरfies beक्रमe concluding the transmitter is hung. */
#घोषणा TX_TIMEOUT		(6*HZ)

/* hardware minimum and maximum क्रम a single frame's data payload */
#घोषणा CP_MIN_MTU		60	/* TODO: allow lower, but pad */
#घोषणा CP_MAX_MTU		4096

क्रमागत अणु
	/* NIC रेजिस्टर offsets */
	MAC0		= 0x00,	/* Ethernet hardware address. */
	MAR0		= 0x08,	/* Multicast filter. */
	StatsAddr	= 0x10,	/* 64-bit start addr of 64-byte DMA stats blk */
	TxRingAddr	= 0x20, /* 64-bit start addr of Tx ring */
	HiTxRingAddr	= 0x28, /* 64-bit start addr of high priority Tx ring */
	Cmd		= 0x37, /* Command रेजिस्टर */
	IntrMask	= 0x3C, /* Interrupt mask */
	IntrStatus	= 0x3E, /* Interrupt status */
	TxConfig	= 0x40, /* Tx configuration */
	ChipVersion	= 0x43, /* 8-bit chip version, inside TxConfig */
	RxConfig	= 0x44, /* Rx configuration */
	RxMissed	= 0x4C,	/* 24 bits valid, ग_लिखो clears */
	Cfg9346		= 0x50, /* EEPROM select/control; Cfg reg [un]lock */
	Config1		= 0x52, /* Config1 */
	Config3		= 0x59, /* Config3 */
	Config4		= 0x5A, /* Config4 */
	MultiIntr	= 0x5C, /* Multiple पूर्णांकerrupt select */
	BasicModeCtrl	= 0x62,	/* MII BMCR */
	BasicModeStatus	= 0x64, /* MII BMSR */
	NWayAdvert	= 0x66, /* MII ADVERTISE */
	NWayLPAR	= 0x68, /* MII LPA */
	NWayExpansion	= 0x6A, /* MII Expansion */
	TxDmaOkLowDesc  = 0x82, /* Low 16 bit address of a Tx descriptor. */
	Config5		= 0xD8,	/* Config5 */
	TxPoll		= 0xD9,	/* Tell chip to check Tx descriptors क्रम work */
	RxMaxSize	= 0xDA, /* Max size of an Rx packet (8169 only) */
	CpCmd		= 0xE0, /* C+ Command रेजिस्टर (C+ mode only) */
	IntrMitigate	= 0xE2,	/* rx/tx पूर्णांकerrupt mitigation control */
	RxRingAddr	= 0xE4, /* 64-bit start addr of Rx ring */
	TxThresh	= 0xEC, /* Early Tx threshold */
	OldRxBufAddr	= 0x30, /* DMA address of Rx ring buffer (C mode) */
	OldTSD0		= 0x10, /* DMA address of first Tx desc (C mode) */

	/* Tx and Rx status descriptors */
	DescOwn		= (1 << 31), /* Descriptor is owned by NIC */
	RingEnd		= (1 << 30), /* End of descriptor ring */
	FirstFrag	= (1 << 29), /* First segment of a packet */
	LastFrag	= (1 << 28), /* Final segment of a packet */
	LargeSend	= (1 << 27), /* TCP Large Send Offload (TSO) */
	MSSShअगरt	= 16,	     /* MSS value position */
	MSSMask		= 0x7ff,     /* MSS value: 11 bits */
	TxError		= (1 << 23), /* Tx error summary */
	RxError		= (1 << 20), /* Rx error summary */
	IPCS		= (1 << 18), /* Calculate IP checksum */
	UDPCS		= (1 << 17), /* Calculate UDP/IP checksum */
	TCPCS		= (1 << 16), /* Calculate TCP/IP checksum */
	TxVlanTag	= (1 << 17), /* Add VLAN tag */
	RxVlanTagged	= (1 << 16), /* Rx VLAN tag available */
	IPFail		= (1 << 15), /* IP checksum failed */
	UDPFail		= (1 << 14), /* UDP/IP checksum failed */
	TCPFail		= (1 << 13), /* TCP/IP checksum failed */
	NormalTxPoll	= (1 << 6),  /* One or more normal Tx packets to send */
	PID1		= (1 << 17), /* 2 protocol id bits:  0==non-IP, */
	PID0		= (1 << 16), /* 1==UDP/IP, 2==TCP/IP, 3==IP */
	RxProtoTCP	= 1,
	RxProtoUDP	= 2,
	RxProtoIP	= 3,
	TxFIFOUnder	= (1 << 25), /* Tx FIFO underrun */
	TxOWC		= (1 << 22), /* Tx Out-of-winकरोw collision */
	TxLinkFail	= (1 << 21), /* Link failed during Tx of packet */
	TxMaxCol	= (1 << 20), /* Tx पातed due to excessive collisions */
	TxColCntShअगरt	= 16,	     /* Shअगरt, to get 4-bit Tx collision cnt */
	TxColCntMask	= 0x01 | 0x02 | 0x04 | 0x08, /* 4-bit collision count */
	RxErrFrame	= (1 << 27), /* Rx frame alignment error */
	RxMcast		= (1 << 26), /* Rx multicast packet rcv'd */
	RxErrCRC	= (1 << 18), /* Rx CRC error */
	RxErrRunt	= (1 << 19), /* Rx error, packet < 64 bytes */
	RxErrLong	= (1 << 21), /* Rx error, packet > 4096 bytes */
	RxErrFIFO	= (1 << 22), /* Rx error, FIFO overflowed, pkt bad */

	/* StatsAddr रेजिस्टर */
	DumpStats	= (1 << 3),  /* Begin stats dump */

	/* RxConfig रेजिस्टर */
	RxCfgFIFOShअगरt	= 13,	     /* Shअगरt, to get Rx FIFO thresh value */
	RxCfgDMAShअगरt	= 8,	     /* Shअगरt, to get Rx Max DMA value */
	AcceptErr	= 0x20,	     /* Accept packets with CRC errors */
	AcceptRunt	= 0x10,	     /* Accept runt (<64 bytes) packets */
	AcceptBroadcast	= 0x08,	     /* Accept broadcast packets */
	AcceptMulticast	= 0x04,	     /* Accept multicast packets */
	AcceptMyPhys	= 0x02,	     /* Accept pkts with our MAC as dest */
	AcceptAllPhys	= 0x01,	     /* Accept all pkts w/ physical dest */

	/* IntrMask / IntrStatus रेजिस्टरs */
	PciErr		= (1 << 15), /* System error on the PCI bus */
	TimerIntr	= (1 << 14), /* Asserted when TCTR reaches TimerInt value */
	LenChg		= (1 << 13), /* Cable length change */
	SWInt		= (1 << 8),  /* Software-requested पूर्णांकerrupt */
	TxEmpty		= (1 << 7),  /* No Tx descriptors available */
	RxFIFOOvr	= (1 << 6),  /* Rx FIFO Overflow */
	LinkChg		= (1 << 5),  /* Packet underrun, or link change */
	RxEmpty		= (1 << 4),  /* No Rx descriptors available */
	TxErr		= (1 << 3),  /* Tx error */
	TxOK		= (1 << 2),  /* Tx packet sent */
	RxErr		= (1 << 1),  /* Rx error */
	RxOK		= (1 << 0),  /* Rx packet received */
	IntrResvd	= (1 << 10), /* reserved, according to RealTek engineers,
					but hardware likes to उठाओ it */

	IntrAll		= PciErr | TimerIntr | LenChg | SWInt | TxEmpty |
			  RxFIFOOvr | LinkChg | RxEmpty | TxErr | TxOK |
			  RxErr | RxOK | IntrResvd,

	/* C mode command रेजिस्टर */
	CmdReset	= (1 << 4),  /* Enable to reset; self-clearing */
	RxOn		= (1 << 3),  /* Rx mode enable */
	TxOn		= (1 << 2),  /* Tx mode enable */

	/* C+ mode command रेजिस्टर */
	RxVlanOn	= (1 << 6),  /* Rx VLAN de-tagging enable */
	RxChkSum	= (1 << 5),  /* Rx checksum offload enable */
	PCIDAC		= (1 << 4),  /* PCI Dual Address Cycle (64-bit PCI) */
	PCIMulRW	= (1 << 3),  /* Enable PCI पढ़ो/ग_लिखो multiple */
	CpRxOn		= (1 << 1),  /* Rx mode enable */
	CpTxOn		= (1 << 0),  /* Tx mode enable */

	/* Cfg9436 EEPROM control रेजिस्टर */
	Cfg9346_Lock	= 0x00,	     /* Lock ConfigX/MII रेजिस्टर access */
	Cfg9346_Unlock	= 0xC0,	     /* Unlock ConfigX/MII रेजिस्टर access */

	/* TxConfig रेजिस्टर */
	IFG		= (1 << 25) | (1 << 24), /* standard IEEE पूर्णांकerframe gap */
	TxDMAShअगरt	= 8,	     /* DMA burst value (0-7) is shअगरt this many bits */

	/* Early Tx Threshold रेजिस्टर */
	TxThreshMask	= 0x3f,	     /* Mask bits 5-0 */
	TxThreshMax	= 2048,	     /* Max early Tx threshold */

	/* Config1 रेजिस्टर */
	DriverLoaded	= (1 << 5),  /* Software marker, driver is loaded */
	LWACT           = (1 << 4),  /* LWAKE active mode */
	PMEnable	= (1 << 0),  /* Enable various PM features of chip */

	/* Config3 रेजिस्टर */
	PARMEnable	= (1 << 6),  /* Enable स्वतः-loading of PHY parms */
	MagicPacket     = (1 << 5),  /* Wake up when receives a Magic Packet */
	LinkUp          = (1 << 4),  /* Wake up when the cable connection is re-established */

	/* Config4 रेजिस्टर */
	LWPTN           = (1 << 1),  /* LWAKE Pattern */
	LWPME           = (1 << 4),  /* LANWAKE vs PMEB */

	/* Config5 रेजिस्टर */
	BWF             = (1 << 6),  /* Accept Broadcast wakeup frame */
	MWF             = (1 << 5),  /* Accept Multicast wakeup frame */
	UWF             = (1 << 4),  /* Accept Unicast wakeup frame */
	LANWake         = (1 << 1),  /* Enable LANWake संकेत */
	PMEStatus	= (1 << 0),  /* PME status can be reset by PCI RST# */

	cp_norx_पूर्णांकr_mask = PciErr | LinkChg | TxOK | TxErr | TxEmpty,
	cp_rx_पूर्णांकr_mask = RxOK | RxErr | RxEmpty | RxFIFOOvr,
	cp_पूर्णांकr_mask = cp_rx_पूर्णांकr_mask | cp_norx_पूर्णांकr_mask,
पूर्ण;

अटल स्थिर अचिन्हित पूर्णांक cp_rx_config =
	  (RX_FIFO_THRESH << RxCfgFIFOShअगरt) |
	  (RX_DMA_BURST << RxCfgDMAShअगरt);

काष्ठा cp_desc अणु
	__le32		opts1;
	__le32		opts2;
	__le64		addr;
पूर्ण;

काष्ठा cp_dma_stats अणु
	__le64			tx_ok;
	__le64			rx_ok;
	__le64			tx_err;
	__le32			rx_err;
	__le16			rx_fअगरo;
	__le16			frame_align;
	__le32			tx_ok_1col;
	__le32			tx_ok_mcol;
	__le64			rx_ok_phys;
	__le64			rx_ok_bcast;
	__le32			rx_ok_mcast;
	__le16			tx_पात;
	__le16			tx_underrun;
पूर्ण __packed;

काष्ठा cp_extra_stats अणु
	अचिन्हित दीर्घ		rx_frags;
पूर्ण;

काष्ठा cp_निजी अणु
	व्योम			__iomem *regs;
	काष्ठा net_device	*dev;
	spinlock_t		lock;
	u32			msg_enable;

	काष्ठा napi_काष्ठा	napi;

	काष्ठा pci_dev		*pdev;
	u32			rx_config;
	u16			cpcmd;

	काष्ठा cp_extra_stats	cp_stats;

	अचिन्हित		rx_head		____cacheline_aligned;
	अचिन्हित		rx_tail;
	काष्ठा cp_desc		*rx_ring;
	काष्ठा sk_buff		*rx_skb[CP_RX_RING_SIZE];

	अचिन्हित		tx_head		____cacheline_aligned;
	अचिन्हित		tx_tail;
	काष्ठा cp_desc		*tx_ring;
	काष्ठा sk_buff		*tx_skb[CP_TX_RING_SIZE];
	u32			tx_opts[CP_TX_RING_SIZE];

	अचिन्हित		rx_buf_sz;
	अचिन्हित		wol_enabled : 1; /* Is Wake-on-LAN enabled? */

	dma_addr_t		ring_dma;

	काष्ठा mii_अगर_info	mii_अगर;
पूर्ण;

#घोषणा cpr8(reg)	पढ़ोb(cp->regs + (reg))
#घोषणा cpr16(reg)	पढ़ोw(cp->regs + (reg))
#घोषणा cpr32(reg)	पढ़ोl(cp->regs + (reg))
#घोषणा cpw8(reg,val)	ग_लिखोb((val), cp->regs + (reg))
#घोषणा cpw16(reg,val)	ग_लिखोw((val), cp->regs + (reg))
#घोषणा cpw32(reg,val)	ग_लिखोl((val), cp->regs + (reg))
#घोषणा cpw8_f(reg,val) करो अणु			\
	ग_लिखोb((val), cp->regs + (reg));	\
	पढ़ोb(cp->regs + (reg));		\
	पूर्ण जबतक (0)
#घोषणा cpw16_f(reg,val) करो अणु			\
	ग_लिखोw((val), cp->regs + (reg));	\
	पढ़ोw(cp->regs + (reg));		\
	पूर्ण जबतक (0)
#घोषणा cpw32_f(reg,val) करो अणु			\
	ग_लिखोl((val), cp->regs + (reg));	\
	पढ़ोl(cp->regs + (reg));		\
	पूर्ण जबतक (0)


अटल व्योम __cp_set_rx_mode (काष्ठा net_device *dev);
अटल व्योम cp_tx (काष्ठा cp_निजी *cp);
अटल व्योम cp_clean_rings (काष्ठा cp_निजी *cp);
#अगर_घोषित CONFIG_NET_POLL_CONTROLLER
अटल व्योम cp_poll_controller(काष्ठा net_device *dev);
#पूर्ण_अगर
अटल पूर्णांक cp_get_eeprom_len(काष्ठा net_device *dev);
अटल पूर्णांक cp_get_eeprom(काष्ठा net_device *dev,
			 काष्ठा ethtool_eeprom *eeprom, u8 *data);
अटल पूर्णांक cp_set_eeprom(काष्ठा net_device *dev,
			 काष्ठा ethtool_eeprom *eeprom, u8 *data);

अटल काष्ठा अणु
	स्थिर अक्षर str[ETH_GSTRING_LEN];
पूर्ण ethtool_stats_keys[] = अणु
	अणु "tx_ok" पूर्ण,
	अणु "rx_ok" पूर्ण,
	अणु "tx_err" पूर्ण,
	अणु "rx_err" पूर्ण,
	अणु "rx_fifo" पूर्ण,
	अणु "frame_align" पूर्ण,
	अणु "tx_ok_1col" पूर्ण,
	अणु "tx_ok_mcol" पूर्ण,
	अणु "rx_ok_phys" पूर्ण,
	अणु "rx_ok_bcast" पूर्ण,
	अणु "rx_ok_mcast" पूर्ण,
	अणु "tx_abort" पूर्ण,
	अणु "tx_underrun" पूर्ण,
	अणु "rx_frags" पूर्ण,
पूर्ण;


अटल अंतरभूत व्योम cp_set_rxbufsize (काष्ठा cp_निजी *cp)
अणु
	अचिन्हित पूर्णांक mtu = cp->dev->mtu;

	अगर (mtu > ETH_DATA_LEN)
		/* MTU + ethernet header + FCS + optional VLAN tag */
		cp->rx_buf_sz = mtu + ETH_HLEN + 8;
	अन्यथा
		cp->rx_buf_sz = PKT_BUF_SZ;
पूर्ण

अटल अंतरभूत व्योम cp_rx_skb (काष्ठा cp_निजी *cp, काष्ठा sk_buff *skb,
			      काष्ठा cp_desc *desc)
अणु
	u32 opts2 = le32_to_cpu(desc->opts2);

	skb->protocol = eth_type_trans (skb, cp->dev);

	cp->dev->stats.rx_packets++;
	cp->dev->stats.rx_bytes += skb->len;

	अगर (opts2 & RxVlanTagged)
		__vlan_hwaccel_put_tag(skb, htons(ETH_P_8021Q), swab16(opts2 & 0xffff));

	napi_gro_receive(&cp->napi, skb);
पूर्ण

अटल व्योम cp_rx_err_acct (काष्ठा cp_निजी *cp, अचिन्हित rx_tail,
			    u32 status, u32 len)
अणु
	netअगर_dbg(cp, rx_err, cp->dev, "rx err, slot %d status 0x%x len %d\n",
		  rx_tail, status, len);
	cp->dev->stats.rx_errors++;
	अगर (status & RxErrFrame)
		cp->dev->stats.rx_frame_errors++;
	अगर (status & RxErrCRC)
		cp->dev->stats.rx_crc_errors++;
	अगर ((status & RxErrRunt) || (status & RxErrLong))
		cp->dev->stats.rx_length_errors++;
	अगर ((status & (FirstFrag | LastFrag)) != (FirstFrag | LastFrag))
		cp->dev->stats.rx_length_errors++;
	अगर (status & RxErrFIFO)
		cp->dev->stats.rx_fअगरo_errors++;
पूर्ण

अटल अंतरभूत अचिन्हित पूर्णांक cp_rx_csum_ok (u32 status)
अणु
	अचिन्हित पूर्णांक protocol = (status >> 16) & 0x3;

	अगर (((protocol == RxProtoTCP) && !(status & TCPFail)) ||
	    ((protocol == RxProtoUDP) && !(status & UDPFail)))
		वापस 1;
	अन्यथा
		वापस 0;
पूर्ण

अटल पूर्णांक cp_rx_poll(काष्ठा napi_काष्ठा *napi, पूर्णांक budget)
अणु
	काष्ठा cp_निजी *cp = container_of(napi, काष्ठा cp_निजी, napi);
	काष्ठा net_device *dev = cp->dev;
	अचिन्हित पूर्णांक rx_tail = cp->rx_tail;
	पूर्णांक rx = 0;

	cpw16(IntrStatus, cp_rx_पूर्णांकr_mask);

	जबतक (rx < budget) अणु
		u32 status, len;
		dma_addr_t mapping, new_mapping;
		काष्ठा sk_buff *skb, *new_skb;
		काष्ठा cp_desc *desc;
		स्थिर अचिन्हित buflen = cp->rx_buf_sz;

		skb = cp->rx_skb[rx_tail];
		BUG_ON(!skb);

		desc = &cp->rx_ring[rx_tail];
		status = le32_to_cpu(desc->opts1);
		अगर (status & DescOwn)
			अवरोध;

		len = (status & 0x1fff) - 4;
		mapping = le64_to_cpu(desc->addr);

		अगर ((status & (FirstFrag | LastFrag)) != (FirstFrag | LastFrag)) अणु
			/* we करोn't support incoming fragmented frames.
			 * instead, we attempt to ensure that the
			 * pre-allocated RX skbs are properly sized such
			 * that RX fragments are never encountered
			 */
			cp_rx_err_acct(cp, rx_tail, status, len);
			dev->stats.rx_dropped++;
			cp->cp_stats.rx_frags++;
			जाओ rx_next;
		पूर्ण

		अगर (status & (RxError | RxErrFIFO)) अणु
			cp_rx_err_acct(cp, rx_tail, status, len);
			जाओ rx_next;
		पूर्ण

		netअगर_dbg(cp, rx_status, dev, "rx slot %d status 0x%x len %d\n",
			  rx_tail, status, len);

		new_skb = napi_alloc_skb(napi, buflen);
		अगर (!new_skb) अणु
			dev->stats.rx_dropped++;
			जाओ rx_next;
		पूर्ण

		new_mapping = dma_map_single(&cp->pdev->dev, new_skb->data, buflen,
					 PCI_DMA_FROMDEVICE);
		अगर (dma_mapping_error(&cp->pdev->dev, new_mapping)) अणु
			dev->stats.rx_dropped++;
			kमुक्त_skb(new_skb);
			जाओ rx_next;
		पूर्ण

		dma_unmap_single(&cp->pdev->dev, mapping,
				 buflen, PCI_DMA_FROMDEVICE);

		/* Handle checksum offloading क्रम incoming packets. */
		अगर (cp_rx_csum_ok(status))
			skb->ip_summed = CHECKSUM_UNNECESSARY;
		अन्यथा
			skb_checksum_none_निश्चित(skb);

		skb_put(skb, len);

		cp->rx_skb[rx_tail] = new_skb;

		cp_rx_skb(cp, skb, desc);
		rx++;
		mapping = new_mapping;

rx_next:
		cp->rx_ring[rx_tail].opts2 = 0;
		cp->rx_ring[rx_tail].addr = cpu_to_le64(mapping);
		अगर (rx_tail == (CP_RX_RING_SIZE - 1))
			desc->opts1 = cpu_to_le32(DescOwn | RingEnd |
						  cp->rx_buf_sz);
		अन्यथा
			desc->opts1 = cpu_to_le32(DescOwn | cp->rx_buf_sz);
		rx_tail = NEXT_RX(rx_tail);
	पूर्ण

	cp->rx_tail = rx_tail;

	/* अगर we did not reach work limit, then we're करोne with
	 * this round of polling
	 */
	अगर (rx < budget && napi_complete_करोne(napi, rx)) अणु
		अचिन्हित दीर्घ flags;

		spin_lock_irqsave(&cp->lock, flags);
		cpw16_f(IntrMask, cp_पूर्णांकr_mask);
		spin_unlock_irqrestore(&cp->lock, flags);
	पूर्ण

	वापस rx;
पूर्ण

अटल irqवापस_t cp_पूर्णांकerrupt (पूर्णांक irq, व्योम *dev_instance)
अणु
	काष्ठा net_device *dev = dev_instance;
	काष्ठा cp_निजी *cp;
	पूर्णांक handled = 0;
	u16 status;
	u16 mask;

	अगर (unlikely(dev == शून्य))
		वापस IRQ_NONE;
	cp = netdev_priv(dev);

	spin_lock(&cp->lock);

	mask = cpr16(IntrMask);
	अगर (!mask)
		जाओ out_unlock;

	status = cpr16(IntrStatus);
	अगर (!status || (status == 0xFFFF))
		जाओ out_unlock;

	handled = 1;

	netअगर_dbg(cp, पूर्णांकr, dev, "intr, status %04x cmd %02x cpcmd %04x\n",
		  status, cpr8(Cmd), cpr16(CpCmd));

	cpw16(IntrStatus, status & ~cp_rx_पूर्णांकr_mask);

	/* बंद possible race's with dev_बंद */
	अगर (unlikely(!netअगर_running(dev))) अणु
		cpw16(IntrMask, 0);
		जाओ out_unlock;
	पूर्ण

	अगर (status & (RxOK | RxErr | RxEmpty | RxFIFOOvr))
		अगर (napi_schedule_prep(&cp->napi)) अणु
			cpw16_f(IntrMask, cp_norx_पूर्णांकr_mask);
			__napi_schedule(&cp->napi);
		पूर्ण

	अगर (status & (TxOK | TxErr | TxEmpty | SWInt))
		cp_tx(cp);
	अगर (status & LinkChg)
		mii_check_media(&cp->mii_अगर, netअगर_msg_link(cp), false);


	अगर (status & PciErr) अणु
		u16 pci_status;

		pci_पढ़ो_config_word(cp->pdev, PCI_STATUS, &pci_status);
		pci_ग_लिखो_config_word(cp->pdev, PCI_STATUS, pci_status);
		netdev_err(dev, "PCI bus error, status=%04x, PCI status=%04x\n",
			   status, pci_status);

		/* TODO: reset hardware */
	पूर्ण

out_unlock:
	spin_unlock(&cp->lock);

	वापस IRQ_RETVAL(handled);
पूर्ण

#अगर_घोषित CONFIG_NET_POLL_CONTROLLER
/*
 * Polling receive - used by netconsole and other diagnostic tools
 * to allow network i/o with पूर्णांकerrupts disabled.
 */
अटल व्योम cp_poll_controller(काष्ठा net_device *dev)
अणु
	काष्ठा cp_निजी *cp = netdev_priv(dev);
	स्थिर पूर्णांक irq = cp->pdev->irq;

	disable_irq(irq);
	cp_पूर्णांकerrupt(irq, dev);
	enable_irq(irq);
पूर्ण
#पूर्ण_अगर

अटल व्योम cp_tx (काष्ठा cp_निजी *cp)
अणु
	अचिन्हित tx_head = cp->tx_head;
	अचिन्हित tx_tail = cp->tx_tail;
	अचिन्हित bytes_compl = 0, pkts_compl = 0;

	जबतक (tx_tail != tx_head) अणु
		काष्ठा cp_desc *txd = cp->tx_ring + tx_tail;
		काष्ठा sk_buff *skb;
		u32 status;

		rmb();
		status = le32_to_cpu(txd->opts1);
		अगर (status & DescOwn)
			अवरोध;

		skb = cp->tx_skb[tx_tail];
		BUG_ON(!skb);

		dma_unmap_single(&cp->pdev->dev, le64_to_cpu(txd->addr),
				 cp->tx_opts[tx_tail] & 0xffff,
				 PCI_DMA_TODEVICE);

		अगर (status & LastFrag) अणु
			अगर (status & (TxError | TxFIFOUnder)) अणु
				netअगर_dbg(cp, tx_err, cp->dev,
					  "tx err, status 0x%x\n", status);
				cp->dev->stats.tx_errors++;
				अगर (status & TxOWC)
					cp->dev->stats.tx_winकरोw_errors++;
				अगर (status & TxMaxCol)
					cp->dev->stats.tx_पातed_errors++;
				अगर (status & TxLinkFail)
					cp->dev->stats.tx_carrier_errors++;
				अगर (status & TxFIFOUnder)
					cp->dev->stats.tx_fअगरo_errors++;
			पूर्ण अन्यथा अणु
				cp->dev->stats.collisions +=
					((status >> TxColCntShअगरt) & TxColCntMask);
				cp->dev->stats.tx_packets++;
				cp->dev->stats.tx_bytes += skb->len;
				netअगर_dbg(cp, tx_करोne, cp->dev,
					  "tx done, slot %d\n", tx_tail);
			पूर्ण
			bytes_compl += skb->len;
			pkts_compl++;
			dev_consume_skb_irq(skb);
		पूर्ण

		cp->tx_skb[tx_tail] = शून्य;

		tx_tail = NEXT_TX(tx_tail);
	पूर्ण

	cp->tx_tail = tx_tail;

	netdev_completed_queue(cp->dev, pkts_compl, bytes_compl);
	अगर (TX_BUFFS_AVAIL(cp) > (MAX_SKB_FRAGS + 1))
		netअगर_wake_queue(cp->dev);
पूर्ण

अटल अंतरभूत u32 cp_tx_vlan_tag(काष्ठा sk_buff *skb)
अणु
	वापस skb_vlan_tag_present(skb) ?
		TxVlanTag | swab16(skb_vlan_tag_get(skb)) : 0x00;
पूर्ण

अटल व्योम unwind_tx_frag_mapping(काष्ठा cp_निजी *cp, काष्ठा sk_buff *skb,
				   पूर्णांक first, पूर्णांक entry_last)
अणु
	पूर्णांक frag, index;
	काष्ठा cp_desc *txd;
	skb_frag_t *this_frag;
	क्रम (frag = 0; frag+first < entry_last; frag++) अणु
		index = first+frag;
		cp->tx_skb[index] = शून्य;
		txd = &cp->tx_ring[index];
		this_frag = &skb_shinfo(skb)->frags[frag];
		dma_unmap_single(&cp->pdev->dev, le64_to_cpu(txd->addr),
				 skb_frag_size(this_frag), PCI_DMA_TODEVICE);
	पूर्ण
पूर्ण

अटल netdev_tx_t cp_start_xmit (काष्ठा sk_buff *skb,
					काष्ठा net_device *dev)
अणु
	काष्ठा cp_निजी *cp = netdev_priv(dev);
	अचिन्हित entry;
	u32 eor, opts1;
	अचिन्हित दीर्घ पूर्णांकr_flags;
	__le32 opts2;
	पूर्णांक mss = 0;

	spin_lock_irqsave(&cp->lock, पूर्णांकr_flags);

	/* This is a hard error, log it. */
	अगर (TX_BUFFS_AVAIL(cp) <= (skb_shinfo(skb)->nr_frags + 1)) अणु
		netअगर_stop_queue(dev);
		spin_unlock_irqrestore(&cp->lock, पूर्णांकr_flags);
		netdev_err(dev, "BUG! Tx Ring full when queue awake!\n");
		वापस NETDEV_TX_BUSY;
	पूर्ण

	entry = cp->tx_head;
	eor = (entry == (CP_TX_RING_SIZE - 1)) ? RingEnd : 0;
	mss = skb_shinfo(skb)->gso_size;

	अगर (mss > MSSMask) अणु
		netdev_WARN_ONCE(dev, "Net bug: GSO size %d too large for 8139CP\n",
				 mss);
		जाओ out_dma_error;
	पूर्ण

	opts2 = cpu_to_le32(cp_tx_vlan_tag(skb));
	opts1 = DescOwn;
	अगर (mss)
		opts1 |= LargeSend | (mss << MSSShअगरt);
	अन्यथा अगर (skb->ip_summed == CHECKSUM_PARTIAL) अणु
		स्थिर काष्ठा iphdr *ip = ip_hdr(skb);
		अगर (ip->protocol == IPPROTO_TCP)
			opts1 |= IPCS | TCPCS;
		अन्यथा अगर (ip->protocol == IPPROTO_UDP)
			opts1 |= IPCS | UDPCS;
		अन्यथा अणु
			WARN_ONCE(1,
				  "Net bug: asked to checksum invalid Legacy IP packet\n");
			जाओ out_dma_error;
		पूर्ण
	पूर्ण

	अगर (skb_shinfo(skb)->nr_frags == 0) अणु
		काष्ठा cp_desc *txd = &cp->tx_ring[entry];
		u32 len;
		dma_addr_t mapping;

		len = skb->len;
		mapping = dma_map_single(&cp->pdev->dev, skb->data, len, PCI_DMA_TODEVICE);
		अगर (dma_mapping_error(&cp->pdev->dev, mapping))
			जाओ out_dma_error;

		txd->opts2 = opts2;
		txd->addr = cpu_to_le64(mapping);
		wmb();

		opts1 |= eor | len | FirstFrag | LastFrag;

		txd->opts1 = cpu_to_le32(opts1);
		wmb();

		cp->tx_skb[entry] = skb;
		cp->tx_opts[entry] = opts1;
		netअगर_dbg(cp, tx_queued, cp->dev, "tx queued, slot %d, skblen %d\n",
			  entry, skb->len);
	पूर्ण अन्यथा अणु
		काष्ठा cp_desc *txd;
		u32 first_len, first_eor, ctrl;
		dma_addr_t first_mapping;
		पूर्णांक frag, first_entry = entry;

		/* We must give this initial chunk to the device last.
		 * Otherwise we could race with the device.
		 */
		first_eor = eor;
		first_len = skb_headlen(skb);
		first_mapping = dma_map_single(&cp->pdev->dev, skb->data,
					       first_len, PCI_DMA_TODEVICE);
		अगर (dma_mapping_error(&cp->pdev->dev, first_mapping))
			जाओ out_dma_error;

		cp->tx_skb[entry] = skb;

		क्रम (frag = 0; frag < skb_shinfo(skb)->nr_frags; frag++) अणु
			स्थिर skb_frag_t *this_frag = &skb_shinfo(skb)->frags[frag];
			u32 len;
			dma_addr_t mapping;

			entry = NEXT_TX(entry);

			len = skb_frag_size(this_frag);
			mapping = dma_map_single(&cp->pdev->dev,
						 skb_frag_address(this_frag),
						 len, PCI_DMA_TODEVICE);
			अगर (dma_mapping_error(&cp->pdev->dev, mapping)) अणु
				unwind_tx_frag_mapping(cp, skb, first_entry, entry);
				जाओ out_dma_error;
			पूर्ण

			eor = (entry == (CP_TX_RING_SIZE - 1)) ? RingEnd : 0;

			ctrl = opts1 | eor | len;

			अगर (frag == skb_shinfo(skb)->nr_frags - 1)
				ctrl |= LastFrag;

			txd = &cp->tx_ring[entry];
			txd->opts2 = opts2;
			txd->addr = cpu_to_le64(mapping);
			wmb();

			txd->opts1 = cpu_to_le32(ctrl);
			wmb();

			cp->tx_opts[entry] = ctrl;
			cp->tx_skb[entry] = skb;
		पूर्ण

		txd = &cp->tx_ring[first_entry];
		txd->opts2 = opts2;
		txd->addr = cpu_to_le64(first_mapping);
		wmb();

		ctrl = opts1 | first_eor | first_len | FirstFrag;
		txd->opts1 = cpu_to_le32(ctrl);
		wmb();

		cp->tx_opts[first_entry] = ctrl;
		netअगर_dbg(cp, tx_queued, cp->dev, "tx queued, slots %d-%d, skblen %d\n",
			  first_entry, entry, skb->len);
	पूर्ण
	cp->tx_head = NEXT_TX(entry);

	netdev_sent_queue(dev, skb->len);
	अगर (TX_BUFFS_AVAIL(cp) <= (MAX_SKB_FRAGS + 1))
		netअगर_stop_queue(dev);

out_unlock:
	spin_unlock_irqrestore(&cp->lock, पूर्णांकr_flags);

	cpw8(TxPoll, NormalTxPoll);

	वापस NETDEV_TX_OK;
out_dma_error:
	dev_kमुक्त_skb_any(skb);
	cp->dev->stats.tx_dropped++;
	जाओ out_unlock;
पूर्ण

/* Set or clear the multicast filter क्रम this adaptor.
   This routine is not state sensitive and need not be SMP locked. */

अटल व्योम __cp_set_rx_mode (काष्ठा net_device *dev)
अणु
	काष्ठा cp_निजी *cp = netdev_priv(dev);
	u32 mc_filter[2];	/* Multicast hash filter */
	पूर्णांक rx_mode;

	/* Note: करो not reorder, GCC is clever about common statements. */
	अगर (dev->flags & IFF_PROMISC) अणु
		/* Unconditionally log net taps. */
		rx_mode =
		    AcceptBroadcast | AcceptMulticast | AcceptMyPhys |
		    AcceptAllPhys;
		mc_filter[1] = mc_filter[0] = 0xffffffff;
	पूर्ण अन्यथा अगर ((netdev_mc_count(dev) > multicast_filter_limit) ||
		   (dev->flags & IFF_ALLMULTI)) अणु
		/* Too many to filter perfectly -- accept all multicasts. */
		rx_mode = AcceptBroadcast | AcceptMulticast | AcceptMyPhys;
		mc_filter[1] = mc_filter[0] = 0xffffffff;
	पूर्ण अन्यथा अणु
		काष्ठा netdev_hw_addr *ha;
		rx_mode = AcceptBroadcast | AcceptMyPhys;
		mc_filter[1] = mc_filter[0] = 0;
		netdev_क्रम_each_mc_addr(ha, dev) अणु
			पूर्णांक bit_nr = ether_crc(ETH_ALEN, ha->addr) >> 26;

			mc_filter[bit_nr >> 5] |= 1 << (bit_nr & 31);
			rx_mode |= AcceptMulticast;
		पूर्ण
	पूर्ण

	/* We can safely update without stopping the chip. */
	cp->rx_config = cp_rx_config | rx_mode;
	cpw32_f(RxConfig, cp->rx_config);

	cpw32_f (MAR0 + 0, mc_filter[0]);
	cpw32_f (MAR0 + 4, mc_filter[1]);
पूर्ण

अटल व्योम cp_set_rx_mode (काष्ठा net_device *dev)
अणु
	अचिन्हित दीर्घ flags;
	काष्ठा cp_निजी *cp = netdev_priv(dev);

	spin_lock_irqsave (&cp->lock, flags);
	__cp_set_rx_mode(dev);
	spin_unlock_irqrestore (&cp->lock, flags);
पूर्ण

अटल व्योम __cp_get_stats(काष्ठा cp_निजी *cp)
अणु
	/* only lower 24 bits valid; ग_लिखो any value to clear */
	cp->dev->stats.rx_missed_errors += (cpr32 (RxMissed) & 0xffffff);
	cpw32 (RxMissed, 0);
पूर्ण

अटल काष्ठा net_device_stats *cp_get_stats(काष्ठा net_device *dev)
अणु
	काष्ठा cp_निजी *cp = netdev_priv(dev);
	अचिन्हित दीर्घ flags;

	/* The chip only need report frame silently dropped. */
	spin_lock_irqsave(&cp->lock, flags);
 	अगर (netअगर_running(dev) && netअगर_device_present(dev))
 		__cp_get_stats(cp);
	spin_unlock_irqrestore(&cp->lock, flags);

	वापस &dev->stats;
पूर्ण

अटल व्योम cp_stop_hw (काष्ठा cp_निजी *cp)
अणु
	cpw16(IntrStatus, ~(cpr16(IntrStatus)));
	cpw16_f(IntrMask, 0);
	cpw8(Cmd, 0);
	cpw16_f(CpCmd, 0);
	cpw16_f(IntrStatus, ~(cpr16(IntrStatus)));

	cp->rx_tail = 0;
	cp->tx_head = cp->tx_tail = 0;

	netdev_reset_queue(cp->dev);
पूर्ण

अटल व्योम cp_reset_hw (काष्ठा cp_निजी *cp)
अणु
	अचिन्हित work = 1000;

	cpw8(Cmd, CmdReset);

	जबतक (work--) अणु
		अगर (!(cpr8(Cmd) & CmdReset))
			वापस;

		schedule_समयout_unपूर्णांकerruptible(10);
	पूर्ण

	netdev_err(cp->dev, "hardware reset timeout\n");
पूर्ण

अटल अंतरभूत व्योम cp_start_hw (काष्ठा cp_निजी *cp)
अणु
	dma_addr_t ring_dma;

	cpw16(CpCmd, cp->cpcmd);

	/*
	 * These (at least TxRingAddr) need to be configured after the
	 * corresponding bits in CpCmd are enabled. Datasheet v1.6 तई6.33
	 * (C+ Command Register) recommends that these and more be configured
	 * *after* the [RT]xEnable bits in CpCmd are set. And on some hardware
	 * it's been observed that the TxRingAddr is actually reset to garbage
	 * when C+ mode Tx is enabled in CpCmd.
	 */
	cpw32_f(HiTxRingAddr, 0);
	cpw32_f(HiTxRingAddr + 4, 0);

	ring_dma = cp->ring_dma;
	cpw32_f(RxRingAddr, ring_dma & 0xffffffff);
	cpw32_f(RxRingAddr + 4, (ring_dma >> 16) >> 16);

	ring_dma += माप(काष्ठा cp_desc) * CP_RX_RING_SIZE;
	cpw32_f(TxRingAddr, ring_dma & 0xffffffff);
	cpw32_f(TxRingAddr + 4, (ring_dma >> 16) >> 16);

	/*
	 * Strictly speaking, the datasheet says this should be enabled
	 * *beक्रमe* setting the descriptor addresses. But what, then, would
	 * prevent it from करोing DMA to अक्रमom unconfigured addresses?
	 * This variant appears to work fine.
	 */
	cpw8(Cmd, RxOn | TxOn);

	netdev_reset_queue(cp->dev);
पूर्ण

अटल व्योम cp_enable_irq(काष्ठा cp_निजी *cp)
अणु
	cpw16_f(IntrMask, cp_पूर्णांकr_mask);
पूर्ण

अटल व्योम cp_init_hw (काष्ठा cp_निजी *cp)
अणु
	काष्ठा net_device *dev = cp->dev;

	cp_reset_hw(cp);

	cpw8_f (Cfg9346, Cfg9346_Unlock);

	/* Restore our idea of the MAC address. */
	cpw32_f (MAC0 + 0, le32_to_cpu (*(__le32 *) (dev->dev_addr + 0)));
	cpw32_f (MAC0 + 4, le32_to_cpu (*(__le32 *) (dev->dev_addr + 4)));

	cp_start_hw(cp);
	cpw8(TxThresh, 0x06); /* XXX convert magic num to a स्थिरant */

	__cp_set_rx_mode(dev);
	cpw32_f (TxConfig, IFG | (TX_DMA_BURST << TxDMAShअगरt));

	cpw8(Config1, cpr8(Config1) | DriverLoaded | PMEnable);
	/* Disable Wake-on-LAN. Can be turned on with ETHTOOL_SWOL */
	cpw8(Config3, PARMEnable);
	cp->wol_enabled = 0;

	cpw8(Config5, cpr8(Config5) & PMEStatus);

	cpw16(MultiIntr, 0);

	cpw8_f(Cfg9346, Cfg9346_Lock);
पूर्ण

अटल पूर्णांक cp_refill_rx(काष्ठा cp_निजी *cp)
अणु
	काष्ठा net_device *dev = cp->dev;
	अचिन्हित i;

	क्रम (i = 0; i < CP_RX_RING_SIZE; i++) अणु
		काष्ठा sk_buff *skb;
		dma_addr_t mapping;

		skb = netdev_alloc_skb_ip_align(dev, cp->rx_buf_sz);
		अगर (!skb)
			जाओ err_out;

		mapping = dma_map_single(&cp->pdev->dev, skb->data,
					 cp->rx_buf_sz, PCI_DMA_FROMDEVICE);
		अगर (dma_mapping_error(&cp->pdev->dev, mapping)) अणु
			kमुक्त_skb(skb);
			जाओ err_out;
		पूर्ण
		cp->rx_skb[i] = skb;

		cp->rx_ring[i].opts2 = 0;
		cp->rx_ring[i].addr = cpu_to_le64(mapping);
		अगर (i == (CP_RX_RING_SIZE - 1))
			cp->rx_ring[i].opts1 =
				cpu_to_le32(DescOwn | RingEnd | cp->rx_buf_sz);
		अन्यथा
			cp->rx_ring[i].opts1 =
				cpu_to_le32(DescOwn | cp->rx_buf_sz);
	पूर्ण

	वापस 0;

err_out:
	cp_clean_rings(cp);
	वापस -ENOMEM;
पूर्ण

अटल व्योम cp_init_rings_index (काष्ठा cp_निजी *cp)
अणु
	cp->rx_tail = 0;
	cp->tx_head = cp->tx_tail = 0;
पूर्ण

अटल पूर्णांक cp_init_rings (काष्ठा cp_निजी *cp)
अणु
	स_रखो(cp->tx_ring, 0, माप(काष्ठा cp_desc) * CP_TX_RING_SIZE);
	cp->tx_ring[CP_TX_RING_SIZE - 1].opts1 = cpu_to_le32(RingEnd);
	स_रखो(cp->tx_opts, 0, माप(cp->tx_opts));

	cp_init_rings_index(cp);

	वापस cp_refill_rx (cp);
पूर्ण

अटल पूर्णांक cp_alloc_rings (काष्ठा cp_निजी *cp)
अणु
	काष्ठा device *d = &cp->pdev->dev;
	व्योम *mem;
	पूर्णांक rc;

	mem = dma_alloc_coherent(d, CP_RING_BYTES, &cp->ring_dma, GFP_KERNEL);
	अगर (!mem)
		वापस -ENOMEM;

	cp->rx_ring = mem;
	cp->tx_ring = &cp->rx_ring[CP_RX_RING_SIZE];

	rc = cp_init_rings(cp);
	अगर (rc < 0)
		dma_मुक्त_coherent(d, CP_RING_BYTES, cp->rx_ring, cp->ring_dma);

	वापस rc;
पूर्ण

अटल व्योम cp_clean_rings (काष्ठा cp_निजी *cp)
अणु
	काष्ठा cp_desc *desc;
	अचिन्हित i;

	क्रम (i = 0; i < CP_RX_RING_SIZE; i++) अणु
		अगर (cp->rx_skb[i]) अणु
			desc = cp->rx_ring + i;
			dma_unmap_single(&cp->pdev->dev,le64_to_cpu(desc->addr),
					 cp->rx_buf_sz, PCI_DMA_FROMDEVICE);
			dev_kमुक्त_skb_any(cp->rx_skb[i]);
		पूर्ण
	पूर्ण

	क्रम (i = 0; i < CP_TX_RING_SIZE; i++) अणु
		अगर (cp->tx_skb[i]) अणु
			काष्ठा sk_buff *skb = cp->tx_skb[i];

			desc = cp->tx_ring + i;
			dma_unmap_single(&cp->pdev->dev,le64_to_cpu(desc->addr),
					 le32_to_cpu(desc->opts1) & 0xffff,
					 PCI_DMA_TODEVICE);
			अगर (le32_to_cpu(desc->opts1) & LastFrag)
				dev_kमुक्त_skb_any(skb);
			cp->dev->stats.tx_dropped++;
		पूर्ण
	पूर्ण
	netdev_reset_queue(cp->dev);

	स_रखो(cp->rx_ring, 0, माप(काष्ठा cp_desc) * CP_RX_RING_SIZE);
	स_रखो(cp->tx_ring, 0, माप(काष्ठा cp_desc) * CP_TX_RING_SIZE);
	स_रखो(cp->tx_opts, 0, माप(cp->tx_opts));

	स_रखो(cp->rx_skb, 0, माप(काष्ठा sk_buff *) * CP_RX_RING_SIZE);
	स_रखो(cp->tx_skb, 0, माप(काष्ठा sk_buff *) * CP_TX_RING_SIZE);
पूर्ण

अटल व्योम cp_मुक्त_rings (काष्ठा cp_निजी *cp)
अणु
	cp_clean_rings(cp);
	dma_मुक्त_coherent(&cp->pdev->dev, CP_RING_BYTES, cp->rx_ring,
			  cp->ring_dma);
	cp->rx_ring = शून्य;
	cp->tx_ring = शून्य;
पूर्ण

अटल पूर्णांक cp_खोलो (काष्ठा net_device *dev)
अणु
	काष्ठा cp_निजी *cp = netdev_priv(dev);
	स्थिर पूर्णांक irq = cp->pdev->irq;
	पूर्णांक rc;

	netअगर_dbg(cp, अगरup, dev, "enabling interface\n");

	rc = cp_alloc_rings(cp);
	अगर (rc)
		वापस rc;

	napi_enable(&cp->napi);

	cp_init_hw(cp);

	rc = request_irq(irq, cp_पूर्णांकerrupt, IRQF_SHARED, dev->name, dev);
	अगर (rc)
		जाओ err_out_hw;

	cp_enable_irq(cp);

	netअगर_carrier_off(dev);
	mii_check_media(&cp->mii_अगर, netअगर_msg_link(cp), true);
	netअगर_start_queue(dev);

	वापस 0;

err_out_hw:
	napi_disable(&cp->napi);
	cp_stop_hw(cp);
	cp_मुक्त_rings(cp);
	वापस rc;
पूर्ण

अटल पूर्णांक cp_बंद (काष्ठा net_device *dev)
अणु
	काष्ठा cp_निजी *cp = netdev_priv(dev);
	अचिन्हित दीर्घ flags;

	napi_disable(&cp->napi);

	netअगर_dbg(cp, अगरकरोwn, dev, "disabling interface\n");

	spin_lock_irqsave(&cp->lock, flags);

	netअगर_stop_queue(dev);
	netअगर_carrier_off(dev);

	cp_stop_hw(cp);

	spin_unlock_irqrestore(&cp->lock, flags);

	मुक्त_irq(cp->pdev->irq, dev);

	cp_मुक्त_rings(cp);
	वापस 0;
पूर्ण

अटल व्योम cp_tx_समयout(काष्ठा net_device *dev, अचिन्हित पूर्णांक txqueue)
अणु
	काष्ठा cp_निजी *cp = netdev_priv(dev);
	अचिन्हित दीर्घ flags;
	पूर्णांक i;

	netdev_warn(dev, "Transmit timeout, status %2x %4x %4x %4x\n",
		    cpr8(Cmd), cpr16(CpCmd),
		    cpr16(IntrStatus), cpr16(IntrMask));

	spin_lock_irqsave(&cp->lock, flags);

	netअगर_dbg(cp, tx_err, cp->dev, "TX ring head %d tail %d desc %x\n",
		  cp->tx_head, cp->tx_tail, cpr16(TxDmaOkLowDesc));
	क्रम (i = 0; i < CP_TX_RING_SIZE; i++) अणु
		netअगर_dbg(cp, tx_err, cp->dev,
			  "TX slot %d @%p: %08x (%08x) %08x %llx %p\n",
			  i, &cp->tx_ring[i], le32_to_cpu(cp->tx_ring[i].opts1),
			  cp->tx_opts[i], le32_to_cpu(cp->tx_ring[i].opts2),
			  le64_to_cpu(cp->tx_ring[i].addr),
			  cp->tx_skb[i]);
	पूर्ण

	cp_stop_hw(cp);
	cp_clean_rings(cp);
	cp_init_rings(cp);
	cp_start_hw(cp);
	__cp_set_rx_mode(dev);
	cpw16_f(IntrMask, cp_norx_पूर्णांकr_mask);

	netअगर_wake_queue(dev);
	napi_schedule_irqoff(&cp->napi);

	spin_unlock_irqrestore(&cp->lock, flags);
पूर्ण

अटल पूर्णांक cp_change_mtu(काष्ठा net_device *dev, पूर्णांक new_mtu)
अणु
	काष्ठा cp_निजी *cp = netdev_priv(dev);

	/* अगर network पूर्णांकerface not up, no need क्रम complनिकासy */
	अगर (!netअगर_running(dev)) अणु
		dev->mtu = new_mtu;
		cp_set_rxbufsize(cp);	/* set new rx buf size */
		वापस 0;
	पूर्ण

	/* network IS up, बंद it, reset MTU, and come up again. */
	cp_बंद(dev);
	dev->mtu = new_mtu;
	cp_set_rxbufsize(cp);
	वापस cp_खोलो(dev);
पूर्ण

अटल स्थिर अक्षर mii_2_8139_map[8] = अणु
	BasicModeCtrl,
	BasicModeStatus,
	0,
	0,
	NWayAdvert,
	NWayLPAR,
	NWayExpansion,
	0
पूर्ण;

अटल पूर्णांक mdio_पढ़ो(काष्ठा net_device *dev, पूर्णांक phy_id, पूर्णांक location)
अणु
	काष्ठा cp_निजी *cp = netdev_priv(dev);

	वापस location < 8 && mii_2_8139_map[location] ?
	       पढ़ोw(cp->regs + mii_2_8139_map[location]) : 0;
पूर्ण


अटल व्योम mdio_ग_लिखो(काष्ठा net_device *dev, पूर्णांक phy_id, पूर्णांक location,
		       पूर्णांक value)
अणु
	काष्ठा cp_निजी *cp = netdev_priv(dev);

	अगर (location == 0) अणु
		cpw8(Cfg9346, Cfg9346_Unlock);
		cpw16(BasicModeCtrl, value);
		cpw8(Cfg9346, Cfg9346_Lock);
	पूर्ण अन्यथा अगर (location < 8 && mii_2_8139_map[location])
		cpw16(mii_2_8139_map[location], value);
पूर्ण

/* Set the ethtool Wake-on-LAN settings */
अटल पूर्णांक netdev_set_wol (काष्ठा cp_निजी *cp,
			   स्थिर काष्ठा ethtool_wolinfo *wol)
अणु
	u8 options;

	options = cpr8 (Config3) & ~(LinkUp | MagicPacket);
	/* If WOL is being disabled, no need क्रम complनिकासy */
	अगर (wol->wolopts) अणु
		अगर (wol->wolopts & WAKE_PHY)	options |= LinkUp;
		अगर (wol->wolopts & WAKE_MAGIC)	options |= MagicPacket;
	पूर्ण

	cpw8 (Cfg9346, Cfg9346_Unlock);
	cpw8 (Config3, options);
	cpw8 (Cfg9346, Cfg9346_Lock);

	options = 0; /* Paranoia setting */
	options = cpr8 (Config5) & ~(UWF | MWF | BWF);
	/* If WOL is being disabled, no need क्रम complनिकासy */
	अगर (wol->wolopts) अणु
		अगर (wol->wolopts & WAKE_UCAST)  options |= UWF;
		अगर (wol->wolopts & WAKE_BCAST)	options |= BWF;
		अगर (wol->wolopts & WAKE_MCAST)	options |= MWF;
	पूर्ण

	cpw8 (Config5, options);

	cp->wol_enabled = (wol->wolopts) ? 1 : 0;

	वापस 0;
पूर्ण

/* Get the ethtool Wake-on-LAN settings */
अटल व्योम netdev_get_wol (काष्ठा cp_निजी *cp,
	             काष्ठा ethtool_wolinfo *wol)
अणु
	u8 options;

	wol->wolopts   = 0; /* Start from scratch */
	wol->supported = WAKE_PHY   | WAKE_BCAST | WAKE_MAGIC |
		         WAKE_MCAST | WAKE_UCAST;
	/* We करोn't need to go on अगर WOL is disabled */
	अगर (!cp->wol_enabled) वापस;

	options        = cpr8 (Config3);
	अगर (options & LinkUp)        wol->wolopts |= WAKE_PHY;
	अगर (options & MagicPacket)   wol->wolopts |= WAKE_MAGIC;

	options        = 0; /* Paranoia setting */
	options        = cpr8 (Config5);
	अगर (options & UWF)           wol->wolopts |= WAKE_UCAST;
	अगर (options & BWF)           wol->wolopts |= WAKE_BCAST;
	अगर (options & MWF)           wol->wolopts |= WAKE_MCAST;
पूर्ण

अटल व्योम cp_get_drvinfo (काष्ठा net_device *dev, काष्ठा ethtool_drvinfo *info)
अणु
	काष्ठा cp_निजी *cp = netdev_priv(dev);

	strlcpy(info->driver, DRV_NAME, माप(info->driver));
	strlcpy(info->version, DRV_VERSION, माप(info->version));
	strlcpy(info->bus_info, pci_name(cp->pdev), माप(info->bus_info));
पूर्ण

अटल व्योम cp_get_ringparam(काष्ठा net_device *dev,
				काष्ठा ethtool_ringparam *ring)
अणु
	ring->rx_max_pending = CP_RX_RING_SIZE;
	ring->tx_max_pending = CP_TX_RING_SIZE;
	ring->rx_pending = CP_RX_RING_SIZE;
	ring->tx_pending = CP_TX_RING_SIZE;
पूर्ण

अटल पूर्णांक cp_get_regs_len(काष्ठा net_device *dev)
अणु
	वापस CP_REGS_SIZE;
पूर्ण

अटल पूर्णांक cp_get_sset_count (काष्ठा net_device *dev, पूर्णांक sset)
अणु
	चयन (sset) अणु
	हाल ETH_SS_STATS:
		वापस CP_NUM_STATS;
	शेष:
		वापस -EOPNOTSUPP;
	पूर्ण
पूर्ण

अटल पूर्णांक cp_get_link_ksettings(काष्ठा net_device *dev,
				 काष्ठा ethtool_link_ksettings *cmd)
अणु
	काष्ठा cp_निजी *cp = netdev_priv(dev);
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&cp->lock, flags);
	mii_ethtool_get_link_ksettings(&cp->mii_अगर, cmd);
	spin_unlock_irqrestore(&cp->lock, flags);

	वापस 0;
पूर्ण

अटल पूर्णांक cp_set_link_ksettings(काष्ठा net_device *dev,
				 स्थिर काष्ठा ethtool_link_ksettings *cmd)
अणु
	काष्ठा cp_निजी *cp = netdev_priv(dev);
	पूर्णांक rc;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&cp->lock, flags);
	rc = mii_ethtool_set_link_ksettings(&cp->mii_अगर, cmd);
	spin_unlock_irqrestore(&cp->lock, flags);

	वापस rc;
पूर्ण

अटल पूर्णांक cp_nway_reset(काष्ठा net_device *dev)
अणु
	काष्ठा cp_निजी *cp = netdev_priv(dev);
	वापस mii_nway_restart(&cp->mii_अगर);
पूर्ण

अटल u32 cp_get_msglevel(काष्ठा net_device *dev)
अणु
	काष्ठा cp_निजी *cp = netdev_priv(dev);
	वापस cp->msg_enable;
पूर्ण

अटल व्योम cp_set_msglevel(काष्ठा net_device *dev, u32 value)
अणु
	काष्ठा cp_निजी *cp = netdev_priv(dev);
	cp->msg_enable = value;
पूर्ण

अटल पूर्णांक cp_set_features(काष्ठा net_device *dev, netdev_features_t features)
अणु
	काष्ठा cp_निजी *cp = netdev_priv(dev);
	अचिन्हित दीर्घ flags;

	अगर (!((dev->features ^ features) & NETIF_F_RXCSUM))
		वापस 0;

	spin_lock_irqsave(&cp->lock, flags);

	अगर (features & NETIF_F_RXCSUM)
		cp->cpcmd |= RxChkSum;
	अन्यथा
		cp->cpcmd &= ~RxChkSum;

	अगर (features & NETIF_F_HW_VLAN_CTAG_RX)
		cp->cpcmd |= RxVlanOn;
	अन्यथा
		cp->cpcmd &= ~RxVlanOn;

	cpw16_f(CpCmd, cp->cpcmd);
	spin_unlock_irqrestore(&cp->lock, flags);

	वापस 0;
पूर्ण

अटल व्योम cp_get_regs(काष्ठा net_device *dev, काष्ठा ethtool_regs *regs,
		        व्योम *p)
अणु
	काष्ठा cp_निजी *cp = netdev_priv(dev);
	अचिन्हित दीर्घ flags;

	अगर (regs->len < CP_REGS_SIZE)
		वापस /* -EINVAL */;

	regs->version = CP_REGS_VER;

	spin_lock_irqsave(&cp->lock, flags);
	स_नकल_fromio(p, cp->regs, CP_REGS_SIZE);
	spin_unlock_irqrestore(&cp->lock, flags);
पूर्ण

अटल व्योम cp_get_wol (काष्ठा net_device *dev, काष्ठा ethtool_wolinfo *wol)
अणु
	काष्ठा cp_निजी *cp = netdev_priv(dev);
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave (&cp->lock, flags);
	netdev_get_wol (cp, wol);
	spin_unlock_irqrestore (&cp->lock, flags);
पूर्ण

अटल पूर्णांक cp_set_wol (काष्ठा net_device *dev, काष्ठा ethtool_wolinfo *wol)
अणु
	काष्ठा cp_निजी *cp = netdev_priv(dev);
	अचिन्हित दीर्घ flags;
	पूर्णांक rc;

	spin_lock_irqsave (&cp->lock, flags);
	rc = netdev_set_wol (cp, wol);
	spin_unlock_irqrestore (&cp->lock, flags);

	वापस rc;
पूर्ण

अटल व्योम cp_get_strings (काष्ठा net_device *dev, u32 stringset, u8 *buf)
अणु
	चयन (stringset) अणु
	हाल ETH_SS_STATS:
		स_नकल(buf, &ethtool_stats_keys, माप(ethtool_stats_keys));
		अवरोध;
	शेष:
		BUG();
		अवरोध;
	पूर्ण
पूर्ण

अटल व्योम cp_get_ethtool_stats (काष्ठा net_device *dev,
				  काष्ठा ethtool_stats *estats, u64 *पंचांगp_stats)
अणु
	काष्ठा cp_निजी *cp = netdev_priv(dev);
	काष्ठा cp_dma_stats *nic_stats;
	dma_addr_t dma;
	पूर्णांक i;

	nic_stats = dma_alloc_coherent(&cp->pdev->dev, माप(*nic_stats),
				       &dma, GFP_KERNEL);
	अगर (!nic_stats)
		वापस;

	/* begin NIC statistics dump */
	cpw32(StatsAddr + 4, (u64)dma >> 32);
	cpw32(StatsAddr, ((u64)dma & DMA_BIT_MASK(32)) | DumpStats);
	cpr32(StatsAddr);

	क्रम (i = 0; i < 1000; i++) अणु
		अगर ((cpr32(StatsAddr) & DumpStats) == 0)
			अवरोध;
		udelay(10);
	पूर्ण
	cpw32(StatsAddr, 0);
	cpw32(StatsAddr + 4, 0);
	cpr32(StatsAddr);

	i = 0;
	पंचांगp_stats[i++] = le64_to_cpu(nic_stats->tx_ok);
	पंचांगp_stats[i++] = le64_to_cpu(nic_stats->rx_ok);
	पंचांगp_stats[i++] = le64_to_cpu(nic_stats->tx_err);
	पंचांगp_stats[i++] = le32_to_cpu(nic_stats->rx_err);
	पंचांगp_stats[i++] = le16_to_cpu(nic_stats->rx_fअगरo);
	पंचांगp_stats[i++] = le16_to_cpu(nic_stats->frame_align);
	पंचांगp_stats[i++] = le32_to_cpu(nic_stats->tx_ok_1col);
	पंचांगp_stats[i++] = le32_to_cpu(nic_stats->tx_ok_mcol);
	पंचांगp_stats[i++] = le64_to_cpu(nic_stats->rx_ok_phys);
	पंचांगp_stats[i++] = le64_to_cpu(nic_stats->rx_ok_bcast);
	पंचांगp_stats[i++] = le32_to_cpu(nic_stats->rx_ok_mcast);
	पंचांगp_stats[i++] = le16_to_cpu(nic_stats->tx_पात);
	पंचांगp_stats[i++] = le16_to_cpu(nic_stats->tx_underrun);
	पंचांगp_stats[i++] = cp->cp_stats.rx_frags;
	BUG_ON(i != CP_NUM_STATS);

	dma_मुक्त_coherent(&cp->pdev->dev, माप(*nic_stats), nic_stats, dma);
पूर्ण

अटल स्थिर काष्ठा ethtool_ops cp_ethtool_ops = अणु
	.get_drvinfo		= cp_get_drvinfo,
	.get_regs_len		= cp_get_regs_len,
	.get_sset_count		= cp_get_sset_count,
	.nway_reset		= cp_nway_reset,
	.get_link		= ethtool_op_get_link,
	.get_msglevel		= cp_get_msglevel,
	.set_msglevel		= cp_set_msglevel,
	.get_regs		= cp_get_regs,
	.get_wol		= cp_get_wol,
	.set_wol		= cp_set_wol,
	.get_strings		= cp_get_strings,
	.get_ethtool_stats	= cp_get_ethtool_stats,
	.get_eeprom_len		= cp_get_eeprom_len,
	.get_eeprom		= cp_get_eeprom,
	.set_eeprom		= cp_set_eeprom,
	.get_ringparam		= cp_get_ringparam,
	.get_link_ksettings	= cp_get_link_ksettings,
	.set_link_ksettings	= cp_set_link_ksettings,
पूर्ण;

अटल पूर्णांक cp_ioctl (काष्ठा net_device *dev, काष्ठा अगरreq *rq, पूर्णांक cmd)
अणु
	काष्ठा cp_निजी *cp = netdev_priv(dev);
	पूर्णांक rc;
	अचिन्हित दीर्घ flags;

	अगर (!netअगर_running(dev))
		वापस -EINVAL;

	spin_lock_irqsave(&cp->lock, flags);
	rc = generic_mii_ioctl(&cp->mii_अगर, अगर_mii(rq), cmd, शून्य);
	spin_unlock_irqrestore(&cp->lock, flags);
	वापस rc;
पूर्ण

अटल पूर्णांक cp_set_mac_address(काष्ठा net_device *dev, व्योम *p)
अणु
	काष्ठा cp_निजी *cp = netdev_priv(dev);
	काष्ठा sockaddr *addr = p;

	अगर (!is_valid_ether_addr(addr->sa_data))
		वापस -EADDRNOTAVAIL;

	स_नकल(dev->dev_addr, addr->sa_data, dev->addr_len);

	spin_lock_irq(&cp->lock);

	cpw8_f(Cfg9346, Cfg9346_Unlock);
	cpw32_f(MAC0 + 0, le32_to_cpu (*(__le32 *) (dev->dev_addr + 0)));
	cpw32_f(MAC0 + 4, le32_to_cpu (*(__le32 *) (dev->dev_addr + 4)));
	cpw8_f(Cfg9346, Cfg9346_Lock);

	spin_unlock_irq(&cp->lock);

	वापस 0;
पूर्ण

/* Serial EEPROM section. */

/*  EEPROM_Ctrl bits. */
#घोषणा EE_SHIFT_CLK	0x04	/* EEPROM shअगरt घड़ी. */
#घोषणा EE_CS			0x08	/* EEPROM chip select. */
#घोषणा EE_DATA_WRITE	0x02	/* EEPROM chip data in. */
#घोषणा EE_WRITE_0		0x00
#घोषणा EE_WRITE_1		0x02
#घोषणा EE_DATA_READ	0x01	/* EEPROM chip data out. */
#घोषणा EE_ENB			(0x80 | EE_CS)

/* Delay between EEPROM घड़ी transitions.
   No extra delay is needed with 33Mhz PCI, but 66Mhz may change this.
 */

#घोषणा eeprom_delay()	पढ़ोb(ee_addr)

/* The EEPROM commands include the alway-set leading bit. */
#घोषणा EE_EXTEND_CMD	(4)
#घोषणा EE_WRITE_CMD	(5)
#घोषणा EE_READ_CMD		(6)
#घोषणा EE_ERASE_CMD	(7)

#घोषणा EE_EWDS_ADDR	(0)
#घोषणा EE_WRAL_ADDR	(1)
#घोषणा EE_ERAL_ADDR	(2)
#घोषणा EE_EWEN_ADDR	(3)

#घोषणा CP_EEPROM_MAGIC PCI_DEVICE_ID_REALTEK_8139

अटल व्योम eeprom_cmd_start(व्योम __iomem *ee_addr)
अणु
	ग_लिखोb (EE_ENB & ~EE_CS, ee_addr);
	ग_लिखोb (EE_ENB, ee_addr);
	eeprom_delay ();
पूर्ण

अटल व्योम eeprom_cmd(व्योम __iomem *ee_addr, पूर्णांक cmd, पूर्णांक cmd_len)
अणु
	पूर्णांक i;

	/* Shअगरt the command bits out. */
	क्रम (i = cmd_len - 1; i >= 0; i--) अणु
		पूर्णांक dataval = (cmd & (1 << i)) ? EE_DATA_WRITE : 0;
		ग_लिखोb (EE_ENB | dataval, ee_addr);
		eeprom_delay ();
		ग_लिखोb (EE_ENB | dataval | EE_SHIFT_CLK, ee_addr);
		eeprom_delay ();
	पूर्ण
	ग_लिखोb (EE_ENB, ee_addr);
	eeprom_delay ();
पूर्ण

अटल व्योम eeprom_cmd_end(व्योम __iomem *ee_addr)
अणु
	ग_लिखोb(0, ee_addr);
	eeprom_delay ();
पूर्ण

अटल व्योम eeprom_extend_cmd(व्योम __iomem *ee_addr, पूर्णांक extend_cmd,
			      पूर्णांक addr_len)
अणु
	पूर्णांक cmd = (EE_EXTEND_CMD << addr_len) | (extend_cmd << (addr_len - 2));

	eeprom_cmd_start(ee_addr);
	eeprom_cmd(ee_addr, cmd, 3 + addr_len);
	eeprom_cmd_end(ee_addr);
पूर्ण

अटल u16 पढ़ो_eeprom (व्योम __iomem *ioaddr, पूर्णांक location, पूर्णांक addr_len)
अणु
	पूर्णांक i;
	u16 retval = 0;
	व्योम __iomem *ee_addr = ioaddr + Cfg9346;
	पूर्णांक पढ़ो_cmd = location | (EE_READ_CMD << addr_len);

	eeprom_cmd_start(ee_addr);
	eeprom_cmd(ee_addr, पढ़ो_cmd, 3 + addr_len);

	क्रम (i = 16; i > 0; i--) अणु
		ग_लिखोb (EE_ENB | EE_SHIFT_CLK, ee_addr);
		eeprom_delay ();
		retval =
		    (retval << 1) | ((पढ़ोb (ee_addr) & EE_DATA_READ) ? 1 :
				     0);
		ग_लिखोb (EE_ENB, ee_addr);
		eeprom_delay ();
	पूर्ण

	eeprom_cmd_end(ee_addr);

	वापस retval;
पूर्ण

अटल व्योम ग_लिखो_eeprom(व्योम __iomem *ioaddr, पूर्णांक location, u16 val,
			 पूर्णांक addr_len)
अणु
	पूर्णांक i;
	व्योम __iomem *ee_addr = ioaddr + Cfg9346;
	पूर्णांक ग_लिखो_cmd = location | (EE_WRITE_CMD << addr_len);

	eeprom_extend_cmd(ee_addr, EE_EWEN_ADDR, addr_len);

	eeprom_cmd_start(ee_addr);
	eeprom_cmd(ee_addr, ग_लिखो_cmd, 3 + addr_len);
	eeprom_cmd(ee_addr, val, 16);
	eeprom_cmd_end(ee_addr);

	eeprom_cmd_start(ee_addr);
	क्रम (i = 0; i < 20000; i++)
		अगर (पढ़ोb(ee_addr) & EE_DATA_READ)
			अवरोध;
	eeprom_cmd_end(ee_addr);

	eeprom_extend_cmd(ee_addr, EE_EWDS_ADDR, addr_len);
पूर्ण

अटल पूर्णांक cp_get_eeprom_len(काष्ठा net_device *dev)
अणु
	काष्ठा cp_निजी *cp = netdev_priv(dev);
	पूर्णांक size;

	spin_lock_irq(&cp->lock);
	size = पढ़ो_eeprom(cp->regs, 0, 8) == 0x8129 ? 256 : 128;
	spin_unlock_irq(&cp->lock);

	वापस size;
पूर्ण

अटल पूर्णांक cp_get_eeprom(काष्ठा net_device *dev,
			 काष्ठा ethtool_eeprom *eeprom, u8 *data)
अणु
	काष्ठा cp_निजी *cp = netdev_priv(dev);
	अचिन्हित पूर्णांक addr_len;
	u16 val;
	u32 offset = eeprom->offset >> 1;
	u32 len = eeprom->len;
	u32 i = 0;

	eeprom->magic = CP_EEPROM_MAGIC;

	spin_lock_irq(&cp->lock);

	addr_len = पढ़ो_eeprom(cp->regs, 0, 8) == 0x8129 ? 8 : 6;

	अगर (eeprom->offset & 1) अणु
		val = पढ़ो_eeprom(cp->regs, offset, addr_len);
		data[i++] = (u8)(val >> 8);
		offset++;
	पूर्ण

	जबतक (i < len - 1) अणु
		val = पढ़ो_eeprom(cp->regs, offset, addr_len);
		data[i++] = (u8)val;
		data[i++] = (u8)(val >> 8);
		offset++;
	पूर्ण

	अगर (i < len) अणु
		val = पढ़ो_eeprom(cp->regs, offset, addr_len);
		data[i] = (u8)val;
	पूर्ण

	spin_unlock_irq(&cp->lock);
	वापस 0;
पूर्ण

अटल पूर्णांक cp_set_eeprom(काष्ठा net_device *dev,
			 काष्ठा ethtool_eeprom *eeprom, u8 *data)
अणु
	काष्ठा cp_निजी *cp = netdev_priv(dev);
	अचिन्हित पूर्णांक addr_len;
	u16 val;
	u32 offset = eeprom->offset >> 1;
	u32 len = eeprom->len;
	u32 i = 0;

	अगर (eeprom->magic != CP_EEPROM_MAGIC)
		वापस -EINVAL;

	spin_lock_irq(&cp->lock);

	addr_len = पढ़ो_eeprom(cp->regs, 0, 8) == 0x8129 ? 8 : 6;

	अगर (eeprom->offset & 1) अणु
		val = पढ़ो_eeprom(cp->regs, offset, addr_len) & 0xff;
		val |= (u16)data[i++] << 8;
		ग_लिखो_eeprom(cp->regs, offset, val, addr_len);
		offset++;
	पूर्ण

	जबतक (i < len - 1) अणु
		val = (u16)data[i++];
		val |= (u16)data[i++] << 8;
		ग_लिखो_eeprom(cp->regs, offset, val, addr_len);
		offset++;
	पूर्ण

	अगर (i < len) अणु
		val = पढ़ो_eeprom(cp->regs, offset, addr_len) & 0xff00;
		val |= (u16)data[i];
		ग_लिखो_eeprom(cp->regs, offset, val, addr_len);
	पूर्ण

	spin_unlock_irq(&cp->lock);
	वापस 0;
पूर्ण

/* Put the board पूर्णांकo D3cold state and रुको क्रम WakeUp संकेत */
अटल व्योम cp_set_d3_state (काष्ठा cp_निजी *cp)
अणु
	pci_enable_wake(cp->pdev, PCI_D0, 1); /* Enable PME# generation */
	pci_set_घातer_state (cp->pdev, PCI_D3hot);
पूर्ण

अटल netdev_features_t cp_features_check(काष्ठा sk_buff *skb,
					   काष्ठा net_device *dev,
					   netdev_features_t features)
अणु
	अगर (skb_shinfo(skb)->gso_size > MSSMask)
		features &= ~NETIF_F_TSO;

	वापस vlan_features_check(skb, features);
पूर्ण
अटल स्थिर काष्ठा net_device_ops cp_netdev_ops = अणु
	.nकरो_खोलो		= cp_खोलो,
	.nकरो_stop		= cp_बंद,
	.nकरो_validate_addr	= eth_validate_addr,
	.nकरो_set_mac_address 	= cp_set_mac_address,
	.nकरो_set_rx_mode	= cp_set_rx_mode,
	.nकरो_get_stats		= cp_get_stats,
	.nकरो_करो_ioctl		= cp_ioctl,
	.nकरो_start_xmit		= cp_start_xmit,
	.nकरो_tx_समयout		= cp_tx_समयout,
	.nकरो_set_features	= cp_set_features,
	.nकरो_change_mtu		= cp_change_mtu,
	.nकरो_features_check	= cp_features_check,

#अगर_घोषित CONFIG_NET_POLL_CONTROLLER
	.nकरो_poll_controller	= cp_poll_controller,
#पूर्ण_अगर
पूर्ण;

अटल पूर्णांक cp_init_one (काष्ठा pci_dev *pdev, स्थिर काष्ठा pci_device_id *ent)
अणु
	काष्ठा net_device *dev;
	काष्ठा cp_निजी *cp;
	पूर्णांक rc;
	व्योम __iomem *regs;
	resource_माप_प्रकार pciaddr;
	अचिन्हित पूर्णांक addr_len, i, pci_using_dac;

	pr_info_once("%s", version);

	अगर (pdev->venकरोr == PCI_VENDOR_ID_REALTEK &&
	    pdev->device == PCI_DEVICE_ID_REALTEK_8139 && pdev->revision < 0x20) अणु
		dev_info(&pdev->dev,
			 "This (id %04x:%04x rev %02x) is not an 8139C+ compatible chip, use 8139too\n",
			 pdev->venकरोr, pdev->device, pdev->revision);
		वापस -ENODEV;
	पूर्ण

	dev = alloc_etherdev(माप(काष्ठा cp_निजी));
	अगर (!dev)
		वापस -ENOMEM;
	SET_NETDEV_DEV(dev, &pdev->dev);

	cp = netdev_priv(dev);
	cp->pdev = pdev;
	cp->dev = dev;
	cp->msg_enable = (debug < 0 ? CP_DEF_MSG_ENABLE : debug);
	spin_lock_init (&cp->lock);
	cp->mii_अगर.dev = dev;
	cp->mii_अगर.mdio_पढ़ो = mdio_पढ़ो;
	cp->mii_अगर.mdio_ग_लिखो = mdio_ग_लिखो;
	cp->mii_अगर.phy_id = CP_INTERNAL_PHY;
	cp->mii_अगर.phy_id_mask = 0x1f;
	cp->mii_अगर.reg_num_mask = 0x1f;
	cp_set_rxbufsize(cp);

	rc = pci_enable_device(pdev);
	अगर (rc)
		जाओ err_out_मुक्त;

	rc = pci_set_mwi(pdev);
	अगर (rc)
		जाओ err_out_disable;

	rc = pci_request_regions(pdev, DRV_NAME);
	अगर (rc)
		जाओ err_out_mwi;

	pciaddr = pci_resource_start(pdev, 1);
	अगर (!pciaddr) अणु
		rc = -EIO;
		dev_err(&pdev->dev, "no MMIO resource\n");
		जाओ err_out_res;
	पूर्ण
	अगर (pci_resource_len(pdev, 1) < CP_REGS_SIZE) अणु
		rc = -EIO;
		dev_err(&pdev->dev, "MMIO resource (%llx) too small\n",
		       (अचिन्हित दीर्घ दीर्घ)pci_resource_len(pdev, 1));
		जाओ err_out_res;
	पूर्ण

	/* Configure DMA attributes. */
	अगर ((माप(dma_addr_t) > 4) &&
	    !pci_set_consistent_dma_mask(pdev, DMA_BIT_MASK(64)) &&
	    !pci_set_dma_mask(pdev, DMA_BIT_MASK(64))) अणु
		pci_using_dac = 1;
	पूर्ण अन्यथा अणु
		pci_using_dac = 0;

		rc = pci_set_dma_mask(pdev, DMA_BIT_MASK(32));
		अगर (rc) अणु
			dev_err(&pdev->dev,
				"No usable DMA configuration, aborting\n");
			जाओ err_out_res;
		पूर्ण
		rc = pci_set_consistent_dma_mask(pdev, DMA_BIT_MASK(32));
		अगर (rc) अणु
			dev_err(&pdev->dev,
				"No usable consistent DMA configuration, aborting\n");
			जाओ err_out_res;
		पूर्ण
	पूर्ण

	cp->cpcmd = (pci_using_dac ? PCIDAC : 0) |
		    PCIMulRW | RxChkSum | CpRxOn | CpTxOn;

	dev->features |= NETIF_F_RXCSUM;
	dev->hw_features |= NETIF_F_RXCSUM;

	regs = ioremap(pciaddr, CP_REGS_SIZE);
	अगर (!regs) अणु
		rc = -EIO;
		dev_err(&pdev->dev, "Cannot map PCI MMIO (%Lx@%Lx)\n",
			(अचिन्हित दीर्घ दीर्घ)pci_resource_len(pdev, 1),
		       (अचिन्हित दीर्घ दीर्घ)pciaddr);
		जाओ err_out_res;
	पूर्ण
	cp->regs = regs;

	cp_stop_hw(cp);

	/* पढ़ो MAC address from EEPROM */
	addr_len = पढ़ो_eeprom (regs, 0, 8) == 0x8129 ? 8 : 6;
	क्रम (i = 0; i < 3; i++)
		((__le16 *) (dev->dev_addr))[i] =
		    cpu_to_le16(पढ़ो_eeprom (regs, i + 7, addr_len));

	dev->netdev_ops = &cp_netdev_ops;
	netअगर_napi_add(dev, &cp->napi, cp_rx_poll, 16);
	dev->ethtool_ops = &cp_ethtool_ops;
	dev->watchकरोg_समयo = TX_TIMEOUT;

	dev->features |= NETIF_F_SG | NETIF_F_IP_CSUM | NETIF_F_TSO |
		NETIF_F_HW_VLAN_CTAG_TX | NETIF_F_HW_VLAN_CTAG_RX;

	अगर (pci_using_dac)
		dev->features |= NETIF_F_HIGHDMA;

	dev->hw_features |= NETIF_F_SG | NETIF_F_IP_CSUM | NETIF_F_TSO |
		NETIF_F_HW_VLAN_CTAG_TX | NETIF_F_HW_VLAN_CTAG_RX;
	dev->vlan_features = NETIF_F_SG | NETIF_F_IP_CSUM | NETIF_F_TSO |
		NETIF_F_HIGHDMA;

	/* MTU range: 60 - 4096 */
	dev->min_mtu = CP_MIN_MTU;
	dev->max_mtu = CP_MAX_MTU;

	rc = रेजिस्टर_netdev(dev);
	अगर (rc)
		जाओ err_out_iomap;

	netdev_info(dev, "RTL-8139C+ at 0x%p, %pM, IRQ %d\n",
		    regs, dev->dev_addr, pdev->irq);

	pci_set_drvdata(pdev, dev);

	/* enable busmastering and memory-ग_लिखो-invalidate */
	pci_set_master(pdev);

	अगर (cp->wol_enabled)
		cp_set_d3_state (cp);

	वापस 0;

err_out_iomap:
	iounmap(regs);
err_out_res:
	pci_release_regions(pdev);
err_out_mwi:
	pci_clear_mwi(pdev);
err_out_disable:
	pci_disable_device(pdev);
err_out_मुक्त:
	मुक्त_netdev(dev);
	वापस rc;
पूर्ण

अटल व्योम cp_हटाओ_one (काष्ठा pci_dev *pdev)
अणु
	काष्ठा net_device *dev = pci_get_drvdata(pdev);
	काष्ठा cp_निजी *cp = netdev_priv(dev);

	unरेजिस्टर_netdev(dev);
	iounmap(cp->regs);
	अगर (cp->wol_enabled)
		pci_set_घातer_state (pdev, PCI_D0);
	pci_release_regions(pdev);
	pci_clear_mwi(pdev);
	pci_disable_device(pdev);
	मुक्त_netdev(dev);
पूर्ण

अटल पूर्णांक __maybe_unused cp_suspend(काष्ठा device *device)
अणु
	काष्ठा net_device *dev = dev_get_drvdata(device);
	काष्ठा cp_निजी *cp = netdev_priv(dev);
	अचिन्हित दीर्घ flags;

	अगर (!netअगर_running(dev))
		वापस 0;

	netअगर_device_detach (dev);
	netअगर_stop_queue (dev);

	spin_lock_irqsave (&cp->lock, flags);

	/* Disable Rx and Tx */
	cpw16 (IntrMask, 0);
	cpw8  (Cmd, cpr8 (Cmd) & (~RxOn | ~TxOn));

	spin_unlock_irqrestore (&cp->lock, flags);

	device_set_wakeup_enable(device, cp->wol_enabled);

	वापस 0;
पूर्ण

अटल पूर्णांक __maybe_unused cp_resume(काष्ठा device *device)
अणु
	काष्ठा net_device *dev = dev_get_drvdata(device);
	काष्ठा cp_निजी *cp = netdev_priv(dev);
	अचिन्हित दीर्घ flags;

	अगर (!netअगर_running(dev))
		वापस 0;

	netअगर_device_attach (dev);

	/* FIXME: sh*t may happen अगर the Rx ring buffer is depleted */
	cp_init_rings_index (cp);
	cp_init_hw (cp);
	cp_enable_irq(cp);
	netअगर_start_queue (dev);

	spin_lock_irqsave (&cp->lock, flags);

	mii_check_media(&cp->mii_अगर, netअगर_msg_link(cp), false);

	spin_unlock_irqrestore (&cp->lock, flags);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा pci_device_id cp_pci_tbl[] = अणु
        अणु PCI_DEVICE(PCI_VENDOR_ID_REALTEK,     PCI_DEVICE_ID_REALTEK_8139), पूर्ण,
        अणु PCI_DEVICE(PCI_VENDOR_ID_TTTECH,      PCI_DEVICE_ID_TTTECH_MC322), पूर्ण,
        अणु पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(pci, cp_pci_tbl);

अटल SIMPLE_DEV_PM_OPS(cp_pm_ops, cp_suspend, cp_resume);

अटल काष्ठा pci_driver cp_driver = अणु
	.name         = DRV_NAME,
	.id_table     = cp_pci_tbl,
	.probe        =	cp_init_one,
	.हटाओ       = cp_हटाओ_one,
	.driver.pm    = &cp_pm_ops,
पूर्ण;

module_pci_driver(cp_driver);
