<शैली गुरु>
/* de2104x.c: A Linux PCI Ethernet driver क्रम Intel/Digital 21040/1 chips. */
/*
	Copyright 2001,2003 Jeff Garzik <jgarzik@pobox.com>

	Copyright 1994, 1995 Digital Equipment Corporation.	    [de4x5.c]
	Written/copyright 1994-2001 by Donald Becker.		    [tulip.c]

	This software may be used and distributed according to the terms of
	the GNU General Public License (GPL), incorporated herein by reference.
	Drivers based on or derived from this code fall under the GPL and must
	retain the authorship, copyright and license notice.  This file is not
	a complete program and may only be used when the entire operating
	प्रणाली is licensed under the GPL.

	See the file COPYING in this distribution क्रम more inक्रमmation.

	TODO, in rough priority order:
	* Support क्रमcing media type with a module parameter,
	  like dl2k.c/sundance.c
	* Constants (module parms?) क्रम Rx work limit
	* Complete reset on PciErr
	* Jumbo frames / dev->change_mtu
	* Adjust Rx FIFO threshold and Max Rx DMA burst on Rx FIFO error
	* Adjust Tx FIFO threshold and Max Tx DMA burst on Tx FIFO error
	* Implement Tx software पूर्णांकerrupt mitigation via
	  Tx descriptor bit

 */

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#घोषणा DRV_NAME		"de2104x"
#घोषणा DRV_RELDATE		"Mar 17, 2004"

#समावेश <linux/module.h>
#समावेश <linux/kernel.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/etherdevice.h>
#समावेश <linux/init.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/pci.h>
#समावेश <linux/delay.h>
#समावेश <linux/ethtool.h>
#समावेश <linux/compiler.h>
#समावेश <linux/rtnetlink.h>
#समावेश <linux/crc32.h>
#समावेश <linux/slab.h>

#समावेश <यंत्र/पन.स>
#समावेश <यंत्र/irq.h>
#समावेश <linux/uaccess.h>
#समावेश <यंत्र/unaligned.h>

MODULE_AUTHOR("Jeff Garzik <jgarzik@pobox.com>");
MODULE_DESCRIPTION("Intel/Digital 21040/1 series PCI Ethernet driver");
MODULE_LICENSE("GPL");

अटल पूर्णांक debug = -1;
module_param (debug, पूर्णांक, 0);
MODULE_PARM_DESC (debug, "de2104x bitmapped message enable number");

/* Set the copy अवरोधpoपूर्णांक क्रम the copy-only-tiny-buffer Rx काष्ठाure. */
#अगर defined(__alpha__) || defined(__arm__) || defined(__hppa__) || \
        defined(CONFIG_SPARC) || defined(__ia64__) ||		   \
        defined(__sh__) || defined(__mips__)
अटल पूर्णांक rx_copyअवरोध = 1518;
#अन्यथा
अटल पूर्णांक rx_copyअवरोध = 100;
#पूर्ण_अगर
module_param (rx_copyअवरोध, पूर्णांक, 0);
MODULE_PARM_DESC (rx_copyअवरोध, "de2104x Breakpoint at which Rx packets are copied");

#घोषणा DE_DEF_MSG_ENABLE	(NETIF_MSG_DRV		| \
				 NETIF_MSG_PROBE 	| \
				 NETIF_MSG_LINK		| \
				 NETIF_MSG_IFDOWN	| \
				 NETIF_MSG_IFUP		| \
				 NETIF_MSG_RX_ERR	| \
				 NETIF_MSG_TX_ERR)

/* Descriptor skip length in 32 bit दीर्घwords. */
#अगर_अघोषित CONFIG_DE2104X_DSL
#घोषणा DSL			0
#अन्यथा
#घोषणा DSL			CONFIG_DE2104X_DSL
#पूर्ण_अगर

#घोषणा DE_RX_RING_SIZE		128
#घोषणा DE_TX_RING_SIZE		64
#घोषणा DE_RING_BYTES		\
		((माप(काष्ठा de_desc) * DE_RX_RING_SIZE) +	\
		(माप(काष्ठा de_desc) * DE_TX_RING_SIZE))
#घोषणा NEXT_TX(N)		(((N) + 1) & (DE_TX_RING_SIZE - 1))
#घोषणा NEXT_RX(N)		(((N) + 1) & (DE_RX_RING_SIZE - 1))
#घोषणा TX_BUFFS_AVAIL(CP)					\
	(((CP)->tx_tail <= (CP)->tx_head) ?			\
	  (CP)->tx_tail + (DE_TX_RING_SIZE - 1) - (CP)->tx_head :	\
	  (CP)->tx_tail - (CP)->tx_head - 1)

#घोषणा PKT_BUF_SZ		1536	/* Size of each temporary Rx buffer.*/
#घोषणा RX_OFFSET		2

#घोषणा DE_SETUP_SKB		((काष्ठा sk_buff *) 1)
#घोषणा DE_DUMMY_SKB		((काष्ठा sk_buff *) 2)
#घोषणा DE_SETUP_FRAME_WORDS	96
#घोषणा DE_EEPROM_WORDS		256
#घोषणा DE_EEPROM_SIZE		(DE_EEPROM_WORDS * माप(u16))
#घोषणा DE_MAX_MEDIA		5

#घोषणा DE_MEDIA_TP_AUTO	0
#घोषणा DE_MEDIA_BNC		1
#घोषणा DE_MEDIA_AUI		2
#घोषणा DE_MEDIA_TP		3
#घोषणा DE_MEDIA_TP_FD		4
#घोषणा DE_MEDIA_INVALID	DE_MAX_MEDIA
#घोषणा DE_MEDIA_FIRST		0
#घोषणा DE_MEDIA_LAST		(DE_MAX_MEDIA - 1)
#घोषणा DE_AUI_BNC		(SUPPORTED_AUI | SUPPORTED_BNC)

#घोषणा DE_TIMER_LINK		(60 * HZ)
#घोषणा DE_TIMER_NO_LINK	(5 * HZ)

#घोषणा DE_NUM_REGS		16
#घोषणा DE_REGS_SIZE		(DE_NUM_REGS * माप(u32))
#घोषणा DE_REGS_VER		1

/* Time in jअगरfies beक्रमe concluding the transmitter is hung. */
#घोषणा TX_TIMEOUT		(6*HZ)

/* This is a mysterious value that can be written to CSR11 in the 21040 (only)
   to support a pre-NWay full-duplex संकेतing mechanism using लघु frames.
   No one knows what it should be, but अगर left at its शेष value some
   10base2(!) packets trigger a full-duplex-request पूर्णांकerrupt. */
#घोषणा FULL_DUPLEX_MAGIC	0x6969

क्रमागत अणु
	/* NIC रेजिस्टरs */
	BusMode			= 0x00,
	TxPoll			= 0x08,
	RxPoll			= 0x10,
	RxRingAddr		= 0x18,
	TxRingAddr		= 0x20,
	MacStatus		= 0x28,
	MacMode			= 0x30,
	IntrMask		= 0x38,
	RxMissed		= 0x40,
	ROMCmd			= 0x48,
	CSR11			= 0x58,
	SIAStatus		= 0x60,
	CSR13			= 0x68,
	CSR14			= 0x70,
	CSR15			= 0x78,
	PCIPM			= 0x40,

	/* BusMode bits */
	CmdReset		= (1 << 0),
	CacheAlign16		= 0x00008000,
	BurstLen4		= 0x00000400,
	DescSkipLen		= (DSL << 2),

	/* Rx/TxPoll bits */
	NormalTxPoll		= (1 << 0),
	NormalRxPoll		= (1 << 0),

	/* Tx/Rx descriptor status bits */
	DescOwn			= (1 << 31),
	RxError			= (1 << 15),
	RxErrLong		= (1 << 7),
	RxErrCRC		= (1 << 1),
	RxErrFIFO		= (1 << 0),
	RxErrRunt		= (1 << 11),
	RxErrFrame		= (1 << 14),
	RingEnd			= (1 << 25),
	FirstFrag		= (1 << 29),
	LastFrag		= (1 << 30),
	TxError			= (1 << 15),
	TxFIFOUnder		= (1 << 1),
	TxLinkFail		= (1 << 2) | (1 << 10) | (1 << 11),
	TxMaxCol		= (1 << 8),
	TxOWC			= (1 << 9),
	TxJabber		= (1 << 14),
	SetupFrame		= (1 << 27),
	TxSwInt			= (1 << 31),

	/* MacStatus bits */
	IntrOK			= (1 << 16),
	IntrErr			= (1 << 15),
	RxIntr			= (1 << 6),
	RxEmpty			= (1 << 7),
	TxIntr			= (1 << 0),
	TxEmpty			= (1 << 2),
	PciErr			= (1 << 13),
	TxState			= (1 << 22) | (1 << 21) | (1 << 20),
	RxState			= (1 << 19) | (1 << 18) | (1 << 17),
	LinkFail		= (1 << 12),
	LinkPass		= (1 << 4),
	RxStopped		= (1 << 8),
	TxStopped		= (1 << 1),

	/* MacMode bits */
	TxEnable		= (1 << 13),
	RxEnable		= (1 << 1),
	RxTx			= TxEnable | RxEnable,
	FullDuplex		= (1 << 9),
	AcceptAllMulticast	= (1 << 7),
	AcceptAllPhys		= (1 << 6),
	BOCnt			= (1 << 5),
	MacModeClear		= (1<<12) | (1<<11) | (1<<10) | (1<<8) | (1<<3) |
				  RxTx | BOCnt | AcceptAllPhys | AcceptAllMulticast,

	/* ROMCmd bits */
	EE_SHIFT_CLK		= 0x02,	/* EEPROM shअगरt घड़ी. */
	EE_CS			= 0x01,	/* EEPROM chip select. */
	EE_DATA_WRITE		= 0x04,	/* Data from the Tulip to EEPROM. */
	EE_WRITE_0		= 0x01,
	EE_WRITE_1		= 0x05,
	EE_DATA_READ		= 0x08,	/* Data from the EEPROM chip. */
	EE_ENB			= (0x4800 | EE_CS),

	/* The EEPROM commands include the alway-set leading bit. */
	EE_READ_CMD		= 6,

	/* RxMissed bits */
	RxMissedOver		= (1 << 16),
	RxMissedMask		= 0xffff,

	/* SROM-related bits */
	SROMC0InfoLeaf		= 27,
	MediaBlockMask		= 0x3f,
	MediaCustomCSRs		= (1 << 6),

	/* PCIPM bits */
	PM_Sleep		= (1 << 31),
	PM_Snooze		= (1 << 30),
	PM_Mask			= PM_Sleep | PM_Snooze,

	/* SIAStatus bits */
	NWayState		= (1 << 14) | (1 << 13) | (1 << 12),
	NWayRestart		= (1 << 12),
	NonselPortActive	= (1 << 9),
	SelPortActive		= (1 << 8),
	LinkFailStatus		= (1 << 2),
	NetCxnErr		= (1 << 1),
पूर्ण;

अटल स्थिर u32 de_पूर्णांकr_mask =
	IntrOK | IntrErr | RxIntr | RxEmpty | TxIntr | TxEmpty |
	LinkPass | LinkFail | PciErr;

/*
 * Set the programmable burst length to 4 दीर्घwords क्रम all:
 * DMA errors result without these values. Cache align 16 दीर्घ.
 */
अटल स्थिर u32 de_bus_mode = CacheAlign16 | BurstLen4 | DescSkipLen;

काष्ठा de_srom_media_block अणु
	u8			opts;
	u16			csr13;
	u16			csr14;
	u16			csr15;
पूर्ण __packed;

काष्ठा de_srom_info_leaf अणु
	u16			शेष_media;
	u8			n_blocks;
	u8			unused;
पूर्ण __packed;

काष्ठा de_desc अणु
	__le32			opts1;
	__le32			opts2;
	__le32			addr1;
	__le32			addr2;
#अगर DSL
	__le32			skip[DSL];
#पूर्ण_अगर
पूर्ण;

काष्ठा media_info अणु
	u16			type;	/* DE_MEDIA_xxx */
	u16			csr13;
	u16			csr14;
	u16			csr15;
पूर्ण;

काष्ठा ring_info अणु
	काष्ठा sk_buff		*skb;
	dma_addr_t		mapping;
पूर्ण;

काष्ठा de_निजी अणु
	अचिन्हित		tx_head;
	अचिन्हित		tx_tail;
	अचिन्हित		rx_tail;

	व्योम			__iomem *regs;
	काष्ठा net_device	*dev;
	spinlock_t		lock;

	काष्ठा de_desc		*rx_ring;
	काष्ठा de_desc		*tx_ring;
	काष्ठा ring_info	tx_skb[DE_TX_RING_SIZE];
	काष्ठा ring_info	rx_skb[DE_RX_RING_SIZE];
	अचिन्हित		rx_buf_sz;
	dma_addr_t		ring_dma;

	u32			msg_enable;

	काष्ठा pci_dev		*pdev;

	u16			setup_frame[DE_SETUP_FRAME_WORDS];

	u32			media_type;
	u32			media_supported;
	u32			media_advertise;
	काष्ठा media_info	media[DE_MAX_MEDIA];
	काष्ठा समयr_list	media_समयr;

	u8			*ee_data;
	अचिन्हित		board_idx;
	अचिन्हित		de21040 : 1;
	अचिन्हित		media_lock : 1;
पूर्ण;


अटल व्योम de_set_rx_mode (काष्ठा net_device *dev);
अटल व्योम de_tx (काष्ठा de_निजी *de);
अटल व्योम de_clean_rings (काष्ठा de_निजी *de);
अटल व्योम de_media_पूर्णांकerrupt (काष्ठा de_निजी *de, u32 status);
अटल व्योम de21040_media_समयr (काष्ठा समयr_list *t);
अटल व्योम de21041_media_समयr (काष्ठा समयr_list *t);
अटल अचिन्हित पूर्णांक de_ok_to_advertise (काष्ठा de_निजी *de, u32 new_media);


अटल स्थिर काष्ठा pci_device_id de_pci_tbl[] = अणु
	अणु PCI_VENDOR_ID_DEC, PCI_DEVICE_ID_DEC_TULIP,
	  PCI_ANY_ID, PCI_ANY_ID, 0, 0, 0 पूर्ण,
	अणु PCI_VENDOR_ID_DEC, PCI_DEVICE_ID_DEC_TULIP_PLUS,
	  PCI_ANY_ID, PCI_ANY_ID, 0, 0, 1 पूर्ण,
	अणु पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(pci, de_pci_tbl);

अटल स्थिर अक्षर * स्थिर media_name[DE_MAX_MEDIA] = अणु
	"10baseT auto",
	"BNC",
	"AUI",
	"10baseT-HD",
	"10baseT-FD"
पूर्ण;

/* 21040 transceiver रेजिस्टर settings:
 * TP AUTO(unused), BNC(unused), AUI, TP, TP FD*/
अटल u16 t21040_csr13[] = अणु 0, 0, 0x8F09, 0x8F01, 0x8F01, पूर्ण;
अटल u16 t21040_csr14[] = अणु 0, 0, 0x0705, 0xFFFF, 0xFFFD, पूर्ण;
अटल u16 t21040_csr15[] = अणु 0, 0, 0x0006, 0x0000, 0x0000, पूर्ण;

/* 21041 transceiver रेजिस्टर settings: TP AUTO, BNC, AUI, TP, TP FD*/
अटल u16 t21041_csr13[] = अणु 0xEF01, 0xEF09, 0xEF09, 0xEF01, 0xEF09, पूर्ण;
अटल u16 t21041_csr14[] = अणु 0xFFFF, 0xF7FD, 0xF7FD, 0x7F3F, 0x7F3D, पूर्ण;
/* If on-chip स्वतःnegotiation is broken, use half-duplex (FF3F) instead */
अटल u16 t21041_csr14_brk[] = अणु 0xFF3F, 0xF7FD, 0xF7FD, 0x7F3F, 0x7F3D, पूर्ण;
अटल u16 t21041_csr15[] = अणु 0x0008, 0x0006, 0x000E, 0x0008, 0x0008, पूर्ण;


#घोषणा dr32(reg)	ioपढ़ो32(de->regs + (reg))
#घोषणा dw32(reg, val)	ioग_लिखो32((val), de->regs + (reg))


अटल व्योम de_rx_err_acct (काष्ठा de_निजी *de, अचिन्हित rx_tail,
			    u32 status, u32 len)
अणु
	netअगर_dbg(de, rx_err, de->dev,
		  "rx err, slot %d status 0x%x len %d\n",
		  rx_tail, status, len);

	अगर ((status & 0x38000300) != 0x0300) अणु
		/* Ingore earlier buffers. */
		अगर ((status & 0xffff) != 0x7fff) अणु
			netअगर_warn(de, rx_err, de->dev,
				   "Oversized Ethernet frame spanned multiple buffers, status %08x!\n",
				   status);
			de->dev->stats.rx_length_errors++;
		पूर्ण
	पूर्ण अन्यथा अगर (status & RxError) अणु
		/* There was a fatal error. */
		de->dev->stats.rx_errors++; /* end of a packet.*/
		अगर (status & 0x0890) de->dev->stats.rx_length_errors++;
		अगर (status & RxErrCRC) de->dev->stats.rx_crc_errors++;
		अगर (status & RxErrFIFO) de->dev->stats.rx_fअगरo_errors++;
	पूर्ण
पूर्ण

अटल व्योम de_rx (काष्ठा de_निजी *de)
अणु
	अचिन्हित rx_tail = de->rx_tail;
	अचिन्हित rx_work = DE_RX_RING_SIZE;
	अचिन्हित drop = 0;
	पूर्णांक rc;

	जबतक (--rx_work) अणु
		u32 status, len;
		dma_addr_t mapping;
		काष्ठा sk_buff *skb, *copy_skb;
		अचिन्हित copying_skb, buflen;

		skb = de->rx_skb[rx_tail].skb;
		BUG_ON(!skb);
		rmb();
		status = le32_to_cpu(de->rx_ring[rx_tail].opts1);
		अगर (status & DescOwn)
			अवरोध;

		/* the length is actually a 15 bit value here according
		 * to Table 4-1 in the DE2104x spec so mask is 0x7fff
		 */
		len = ((status >> 16) & 0x7fff) - 4;
		mapping = de->rx_skb[rx_tail].mapping;

		अगर (unlikely(drop)) अणु
			de->dev->stats.rx_dropped++;
			जाओ rx_next;
		पूर्ण

		अगर (unlikely((status & 0x38008300) != 0x0300)) अणु
			de_rx_err_acct(de, rx_tail, status, len);
			जाओ rx_next;
		पूर्ण

		copying_skb = (len <= rx_copyअवरोध);

		netअगर_dbg(de, rx_status, de->dev,
			  "rx slot %d status 0x%x len %d copying? %d\n",
			  rx_tail, status, len, copying_skb);

		buflen = copying_skb ? (len + RX_OFFSET) : de->rx_buf_sz;
		copy_skb = netdev_alloc_skb(de->dev, buflen);
		अगर (unlikely(!copy_skb)) अणु
			de->dev->stats.rx_dropped++;
			drop = 1;
			rx_work = 100;
			जाओ rx_next;
		पूर्ण

		अगर (!copying_skb) अणु
			dma_unmap_single(&de->pdev->dev, mapping, buflen,
					 DMA_FROM_DEVICE);
			skb_put(skb, len);

			mapping =
			de->rx_skb[rx_tail].mapping =
				dma_map_single(&de->pdev->dev, copy_skb->data,
					       buflen, DMA_FROM_DEVICE);
			de->rx_skb[rx_tail].skb = copy_skb;
		पूर्ण अन्यथा अणु
			dma_sync_single_क्रम_cpu(&de->pdev->dev, mapping, len,
						DMA_FROM_DEVICE);
			skb_reserve(copy_skb, RX_OFFSET);
			skb_copy_from_linear_data(skb, skb_put(copy_skb, len),
						  len);
			dma_sync_single_क्रम_device(&de->pdev->dev, mapping,
						   len, DMA_FROM_DEVICE);

			/* We'll reuse the original ring buffer. */
			skb = copy_skb;
		पूर्ण

		skb->protocol = eth_type_trans (skb, de->dev);

		de->dev->stats.rx_packets++;
		de->dev->stats.rx_bytes += skb->len;
		rc = netअगर_rx (skb);
		अगर (rc == NET_RX_DROP)
			drop = 1;

rx_next:
		अगर (rx_tail == (DE_RX_RING_SIZE - 1))
			de->rx_ring[rx_tail].opts2 =
				cpu_to_le32(RingEnd | de->rx_buf_sz);
		अन्यथा
			de->rx_ring[rx_tail].opts2 = cpu_to_le32(de->rx_buf_sz);
		de->rx_ring[rx_tail].addr1 = cpu_to_le32(mapping);
		wmb();
		de->rx_ring[rx_tail].opts1 = cpu_to_le32(DescOwn);
		rx_tail = NEXT_RX(rx_tail);
	पूर्ण

	अगर (!rx_work)
		netdev_warn(de->dev, "rx work limit reached\n");

	de->rx_tail = rx_tail;
पूर्ण

अटल irqवापस_t de_पूर्णांकerrupt (पूर्णांक irq, व्योम *dev_instance)
अणु
	काष्ठा net_device *dev = dev_instance;
	काष्ठा de_निजी *de = netdev_priv(dev);
	u32 status;

	status = dr32(MacStatus);
	अगर ((!(status & (IntrOK|IntrErr))) || (status == 0xFFFF))
		वापस IRQ_NONE;

	netअगर_dbg(de, पूर्णांकr, dev, "intr, status %08x mode %08x desc %u/%u/%u\n",
		  status, dr32(MacMode),
		  de->rx_tail, de->tx_head, de->tx_tail);

	dw32(MacStatus, status);

	अगर (status & (RxIntr | RxEmpty)) अणु
		de_rx(de);
		अगर (status & RxEmpty)
			dw32(RxPoll, NormalRxPoll);
	पूर्ण

	spin_lock(&de->lock);

	अगर (status & (TxIntr | TxEmpty))
		de_tx(de);

	अगर (status & (LinkPass | LinkFail))
		de_media_पूर्णांकerrupt(de, status);

	spin_unlock(&de->lock);

	अगर (status & PciErr) अणु
		u16 pci_status;

		pci_पढ़ो_config_word(de->pdev, PCI_STATUS, &pci_status);
		pci_ग_लिखो_config_word(de->pdev, PCI_STATUS, pci_status);
		netdev_err(de->dev,
			   "PCI bus error, status=%08x, PCI status=%04x\n",
			   status, pci_status);
	पूर्ण

	वापस IRQ_HANDLED;
पूर्ण

अटल व्योम de_tx (काष्ठा de_निजी *de)
अणु
	अचिन्हित tx_head = de->tx_head;
	अचिन्हित tx_tail = de->tx_tail;

	जबतक (tx_tail != tx_head) अणु
		काष्ठा sk_buff *skb;
		u32 status;

		rmb();
		status = le32_to_cpu(de->tx_ring[tx_tail].opts1);
		अगर (status & DescOwn)
			अवरोध;

		skb = de->tx_skb[tx_tail].skb;
		BUG_ON(!skb);
		अगर (unlikely(skb == DE_DUMMY_SKB))
			जाओ next;

		अगर (unlikely(skb == DE_SETUP_SKB)) अणु
			dma_unmap_single(&de->pdev->dev,
					 de->tx_skb[tx_tail].mapping,
					 माप(de->setup_frame),
					 DMA_TO_DEVICE);
			जाओ next;
		पूर्ण

		dma_unmap_single(&de->pdev->dev, de->tx_skb[tx_tail].mapping,
				 skb->len, DMA_TO_DEVICE);

		अगर (status & LastFrag) अणु
			अगर (status & TxError) अणु
				netअगर_dbg(de, tx_err, de->dev,
					  "tx err, status 0x%x\n",
					  status);
				de->dev->stats.tx_errors++;
				अगर (status & TxOWC)
					de->dev->stats.tx_winकरोw_errors++;
				अगर (status & TxMaxCol)
					de->dev->stats.tx_पातed_errors++;
				अगर (status & TxLinkFail)
					de->dev->stats.tx_carrier_errors++;
				अगर (status & TxFIFOUnder)
					de->dev->stats.tx_fअगरo_errors++;
			पूर्ण अन्यथा अणु
				de->dev->stats.tx_packets++;
				de->dev->stats.tx_bytes += skb->len;
				netअगर_dbg(de, tx_करोne, de->dev,
					  "tx done, slot %d\n", tx_tail);
			पूर्ण
			dev_consume_skb_irq(skb);
		पूर्ण

next:
		de->tx_skb[tx_tail].skb = शून्य;

		tx_tail = NEXT_TX(tx_tail);
	पूर्ण

	de->tx_tail = tx_tail;

	अगर (netअगर_queue_stopped(de->dev) && (TX_BUFFS_AVAIL(de) > (DE_TX_RING_SIZE / 4)))
		netअगर_wake_queue(de->dev);
पूर्ण

अटल netdev_tx_t de_start_xmit (काष्ठा sk_buff *skb,
					काष्ठा net_device *dev)
अणु
	काष्ठा de_निजी *de = netdev_priv(dev);
	अचिन्हित पूर्णांक entry, tx_मुक्त;
	u32 mapping, len, flags = FirstFrag | LastFrag;
	काष्ठा de_desc *txd;

	spin_lock_irq(&de->lock);

	tx_मुक्त = TX_BUFFS_AVAIL(de);
	अगर (tx_मुक्त == 0) अणु
		netअगर_stop_queue(dev);
		spin_unlock_irq(&de->lock);
		वापस NETDEV_TX_BUSY;
	पूर्ण
	tx_मुक्त--;

	entry = de->tx_head;

	txd = &de->tx_ring[entry];

	len = skb->len;
	mapping = dma_map_single(&de->pdev->dev, skb->data, len,
				 DMA_TO_DEVICE);
	अगर (entry == (DE_TX_RING_SIZE - 1))
		flags |= RingEnd;
	अगर (!tx_मुक्त || (tx_मुक्त == (DE_TX_RING_SIZE / 2)))
		flags |= TxSwInt;
	flags |= len;
	txd->opts2 = cpu_to_le32(flags);
	txd->addr1 = cpu_to_le32(mapping);

	de->tx_skb[entry].skb = skb;
	de->tx_skb[entry].mapping = mapping;
	wmb();

	txd->opts1 = cpu_to_le32(DescOwn);
	wmb();

	de->tx_head = NEXT_TX(entry);
	netअगर_dbg(de, tx_queued, dev, "tx queued, slot %d, skblen %d\n",
		  entry, skb->len);

	अगर (tx_मुक्त == 0)
		netअगर_stop_queue(dev);

	spin_unlock_irq(&de->lock);

	/* Trigger an immediate transmit demand. */
	dw32(TxPoll, NormalTxPoll);

	वापस NETDEV_TX_OK;
पूर्ण

/* Set or clear the multicast filter क्रम this adaptor.
   Note that we only use exclusion around actually queueing the
   new frame, not around filling de->setup_frame.  This is non-deterministic
   when re-entered but still correct. */

अटल व्योम build_setup_frame_hash(u16 *setup_frm, काष्ठा net_device *dev)
अणु
	काष्ठा de_निजी *de = netdev_priv(dev);
	u16 hash_table[32];
	काष्ठा netdev_hw_addr *ha;
	पूर्णांक i;
	u16 *eaddrs;

	स_रखो(hash_table, 0, माप(hash_table));
	__set_bit_le(255, hash_table);			/* Broadcast entry */
	/* This should work on big-endian machines as well. */
	netdev_क्रम_each_mc_addr(ha, dev) अणु
		पूर्णांक index = ether_crc_le(ETH_ALEN, ha->addr) & 0x1ff;

		__set_bit_le(index, hash_table);
	पूर्ण

	क्रम (i = 0; i < 32; i++) अणु
		*setup_frm++ = hash_table[i];
		*setup_frm++ = hash_table[i];
	पूर्ण
	setup_frm = &de->setup_frame[13*6];

	/* Fill the final entry with our physical address. */
	eaddrs = (u16 *)dev->dev_addr;
	*setup_frm++ = eaddrs[0]; *setup_frm++ = eaddrs[0];
	*setup_frm++ = eaddrs[1]; *setup_frm++ = eaddrs[1];
	*setup_frm++ = eaddrs[2]; *setup_frm++ = eaddrs[2];
पूर्ण

अटल व्योम build_setup_frame_perfect(u16 *setup_frm, काष्ठा net_device *dev)
अणु
	काष्ठा de_निजी *de = netdev_priv(dev);
	काष्ठा netdev_hw_addr *ha;
	u16 *eaddrs;

	/* We have <= 14 addresses so we can use the wonderful
	   16 address perfect filtering of the Tulip. */
	netdev_क्रम_each_mc_addr(ha, dev) अणु
		eaddrs = (u16 *) ha->addr;
		*setup_frm++ = *eaddrs; *setup_frm++ = *eaddrs++;
		*setup_frm++ = *eaddrs; *setup_frm++ = *eaddrs++;
		*setup_frm++ = *eaddrs; *setup_frm++ = *eaddrs++;
	पूर्ण
	/* Fill the unused entries with the broadcast address. */
	स_रखो(setup_frm, 0xff, (15 - netdev_mc_count(dev)) * 12);
	setup_frm = &de->setup_frame[15*6];

	/* Fill the final entry with our physical address. */
	eaddrs = (u16 *)dev->dev_addr;
	*setup_frm++ = eaddrs[0]; *setup_frm++ = eaddrs[0];
	*setup_frm++ = eaddrs[1]; *setup_frm++ = eaddrs[1];
	*setup_frm++ = eaddrs[2]; *setup_frm++ = eaddrs[2];
पूर्ण


अटल व्योम __de_set_rx_mode (काष्ठा net_device *dev)
अणु
	काष्ठा de_निजी *de = netdev_priv(dev);
	u32 macmode;
	अचिन्हित पूर्णांक entry;
	u32 mapping;
	काष्ठा de_desc *txd;
	काष्ठा de_desc *dummy_txd = शून्य;

	macmode = dr32(MacMode) & ~(AcceptAllMulticast | AcceptAllPhys);

	अगर (dev->flags & IFF_PROMISC) अणु	/* Set promiscuous. */
		macmode |= AcceptAllMulticast | AcceptAllPhys;
		जाओ out;
	पूर्ण

	अगर ((netdev_mc_count(dev) > 1000) || (dev->flags & IFF_ALLMULTI)) अणु
		/* Too many to filter well -- accept all multicasts. */
		macmode |= AcceptAllMulticast;
		जाओ out;
	पूर्ण

	/* Note that only the low-address लघुword of setup_frame is valid!
	   The values are द्विगुनd क्रम big-endian architectures. */
	अगर (netdev_mc_count(dev) > 14)	/* Must use a multicast hash table. */
		build_setup_frame_hash (de->setup_frame, dev);
	अन्यथा
		build_setup_frame_perfect (de->setup_frame, dev);

	/*
	 * Now add this frame to the Tx list.
	 */

	entry = de->tx_head;

	/* Aव्योम a chip errata by prefixing a dummy entry. */
	अगर (entry != 0) अणु
		de->tx_skb[entry].skb = DE_DUMMY_SKB;

		dummy_txd = &de->tx_ring[entry];
		dummy_txd->opts2 = (entry == (DE_TX_RING_SIZE - 1)) ?
				   cpu_to_le32(RingEnd) : 0;
		dummy_txd->addr1 = 0;

		/* Must set DescOwned later to aव्योम race with chip */

		entry = NEXT_TX(entry);
	पूर्ण

	de->tx_skb[entry].skb = DE_SETUP_SKB;
	de->tx_skb[entry].mapping = mapping =
	    dma_map_single(&de->pdev->dev, de->setup_frame,
			   माप(de->setup_frame), DMA_TO_DEVICE);

	/* Put the setup frame on the Tx list. */
	txd = &de->tx_ring[entry];
	अगर (entry == (DE_TX_RING_SIZE - 1))
		txd->opts2 = cpu_to_le32(SetupFrame | RingEnd | माप (de->setup_frame));
	अन्यथा
		txd->opts2 = cpu_to_le32(SetupFrame | माप (de->setup_frame));
	txd->addr1 = cpu_to_le32(mapping);
	wmb();

	txd->opts1 = cpu_to_le32(DescOwn);
	wmb();

	अगर (dummy_txd) अणु
		dummy_txd->opts1 = cpu_to_le32(DescOwn);
		wmb();
	पूर्ण

	de->tx_head = NEXT_TX(entry);

	अगर (TX_BUFFS_AVAIL(de) == 0)
		netअगर_stop_queue(dev);

	/* Trigger an immediate transmit demand. */
	dw32(TxPoll, NormalTxPoll);

out:
	अगर (macmode != dr32(MacMode))
		dw32(MacMode, macmode);
पूर्ण

अटल व्योम de_set_rx_mode (काष्ठा net_device *dev)
अणु
	अचिन्हित दीर्घ flags;
	काष्ठा de_निजी *de = netdev_priv(dev);

	spin_lock_irqsave (&de->lock, flags);
	__de_set_rx_mode(dev);
	spin_unlock_irqrestore (&de->lock, flags);
पूर्ण

अटल अंतरभूत व्योम de_rx_missed(काष्ठा de_निजी *de, u32 rx_missed)
अणु
	अगर (unlikely(rx_missed & RxMissedOver))
		de->dev->stats.rx_missed_errors += RxMissedMask;
	अन्यथा
		de->dev->stats.rx_missed_errors += (rx_missed & RxMissedMask);
पूर्ण

अटल व्योम __de_get_stats(काष्ठा de_निजी *de)
अणु
	u32 पंचांगp = dr32(RxMissed); /* self-clearing */

	de_rx_missed(de, पंचांगp);
पूर्ण

अटल काष्ठा net_device_stats *de_get_stats(काष्ठा net_device *dev)
अणु
	काष्ठा de_निजी *de = netdev_priv(dev);

	/* The chip only need report frame silently dropped. */
	spin_lock_irq(&de->lock);
 	अगर (netअगर_running(dev) && netअगर_device_present(dev))
 		__de_get_stats(de);
	spin_unlock_irq(&de->lock);

	वापस &dev->stats;
पूर्ण

अटल अंतरभूत पूर्णांक de_is_running (काष्ठा de_निजी *de)
अणु
	वापस (dr32(MacStatus) & (RxState | TxState)) ? 1 : 0;
पूर्ण

अटल व्योम de_stop_rxtx (काष्ठा de_निजी *de)
अणु
	u32 macmode;
	अचिन्हित पूर्णांक i = 1300/100;

	macmode = dr32(MacMode);
	अगर (macmode & RxTx) अणु
		dw32(MacMode, macmode & ~RxTx);
		dr32(MacMode);
	पूर्ण

	/* रुको until in-flight frame completes.
	 * Max समय @ 10BT: 1500*8b/10Mbps == 1200us (+ 100us margin)
	 * Typically expect this loop to end in < 50 us on 100BT.
	 */
	जबतक (--i) अणु
		अगर (!de_is_running(de))
			वापस;
		udelay(100);
	पूर्ण

	netdev_warn(de->dev, "timeout expired, stopping DMA\n");
पूर्ण

अटल अंतरभूत व्योम de_start_rxtx (काष्ठा de_निजी *de)
अणु
	u32 macmode;

	macmode = dr32(MacMode);
	अगर ((macmode & RxTx) != RxTx) अणु
		dw32(MacMode, macmode | RxTx);
		dr32(MacMode);
	पूर्ण
पूर्ण

अटल व्योम de_stop_hw (काष्ठा de_निजी *de)
अणु

	udelay(5);
	dw32(IntrMask, 0);

	de_stop_rxtx(de);

	dw32(MacStatus, dr32(MacStatus));

	udelay(10);

	de->rx_tail = 0;
	de->tx_head = de->tx_tail = 0;
पूर्ण

अटल व्योम de_link_up(काष्ठा de_निजी *de)
अणु
	अगर (!netअगर_carrier_ok(de->dev)) अणु
		netअगर_carrier_on(de->dev);
		netअगर_info(de, link, de->dev, "link up, media %s\n",
			   media_name[de->media_type]);
	पूर्ण
पूर्ण

अटल व्योम de_link_करोwn(काष्ठा de_निजी *de)
अणु
	अगर (netअगर_carrier_ok(de->dev)) अणु
		netअगर_carrier_off(de->dev);
		netअगर_info(de, link, de->dev, "link down\n");
	पूर्ण
पूर्ण

अटल व्योम de_set_media (काष्ठा de_निजी *de)
अणु
	अचिन्हित media = de->media_type;
	u32 macmode = dr32(MacMode);

	अगर (de_is_running(de))
		netdev_warn(de->dev, "chip is running while changing media!\n");

	अगर (de->de21040)
		dw32(CSR11, FULL_DUPLEX_MAGIC);
	dw32(CSR13, 0); /* Reset phy */
	dw32(CSR14, de->media[media].csr14);
	dw32(CSR15, de->media[media].csr15);
	dw32(CSR13, de->media[media].csr13);

	/* must delay 10ms beक्रमe writing to other रेजिस्टरs,
	 * especially CSR6
	 */
	mdelay(10);

	अगर (media == DE_MEDIA_TP_FD)
		macmode |= FullDuplex;
	अन्यथा
		macmode &= ~FullDuplex;

	netअगर_info(de, link, de->dev, "set link %s\n", media_name[media]);
	netअगर_info(de, hw, de->dev, "mode 0x%x, sia 0x%x,0x%x,0x%x,0x%x\n",
		   dr32(MacMode), dr32(SIAStatus),
		   dr32(CSR13), dr32(CSR14), dr32(CSR15));
	netअगर_info(de, hw, de->dev, "set mode 0x%x, set sia 0x%x,0x%x,0x%x\n",
		   macmode, de->media[media].csr13,
		   de->media[media].csr14, de->media[media].csr15);
	अगर (macmode != dr32(MacMode))
		dw32(MacMode, macmode);
पूर्ण

अटल व्योम de_next_media (काष्ठा de_निजी *de, स्थिर u32 *media,
			   अचिन्हित पूर्णांक n_media)
अणु
	अचिन्हित पूर्णांक i;

	क्रम (i = 0; i < n_media; i++) अणु
		अगर (de_ok_to_advertise(de, media[i])) अणु
			de->media_type = media[i];
			वापस;
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम de21040_media_समयr (काष्ठा समयr_list *t)
अणु
	काष्ठा de_निजी *de = from_समयr(de, t, media_समयr);
	काष्ठा net_device *dev = de->dev;
	u32 status = dr32(SIAStatus);
	अचिन्हित पूर्णांक carrier;
	अचिन्हित दीर्घ flags;

	carrier = (status & NetCxnErr) ? 0 : 1;

	अगर (carrier) अणु
		अगर (de->media_type != DE_MEDIA_AUI && (status & LinkFailStatus))
			जाओ no_link_yet;

		de->media_समयr.expires = jअगरfies + DE_TIMER_LINK;
		add_समयr(&de->media_समयr);
		अगर (!netअगर_carrier_ok(dev))
			de_link_up(de);
		अन्यथा
			netअगर_info(de, समयr, dev, "%s link ok, status %x\n",
				   media_name[de->media_type], status);
		वापस;
	पूर्ण

	de_link_करोwn(de);

	अगर (de->media_lock)
		वापस;

	अगर (de->media_type == DE_MEDIA_AUI) अणु
		अटल स्थिर u32 next_state = DE_MEDIA_TP;
		de_next_media(de, &next_state, 1);
	पूर्ण अन्यथा अणु
		अटल स्थिर u32 next_state = DE_MEDIA_AUI;
		de_next_media(de, &next_state, 1);
	पूर्ण

	spin_lock_irqsave(&de->lock, flags);
	de_stop_rxtx(de);
	spin_unlock_irqrestore(&de->lock, flags);
	de_set_media(de);
	de_start_rxtx(de);

no_link_yet:
	de->media_समयr.expires = jअगरfies + DE_TIMER_NO_LINK;
	add_समयr(&de->media_समयr);

	netअगर_info(de, समयr, dev, "no link, trying media %s, status %x\n",
		   media_name[de->media_type], status);
पूर्ण

अटल अचिन्हित पूर्णांक de_ok_to_advertise (काष्ठा de_निजी *de, u32 new_media)
अणु
	चयन (new_media) अणु
	हाल DE_MEDIA_TP_AUTO:
		अगर (!(de->media_advertise & ADVERTISED_Autoneg))
			वापस 0;
		अगर (!(de->media_advertise & (ADVERTISED_10baseT_Half | ADVERTISED_10baseT_Full)))
			वापस 0;
		अवरोध;
	हाल DE_MEDIA_BNC:
		अगर (!(de->media_advertise & ADVERTISED_BNC))
			वापस 0;
		अवरोध;
	हाल DE_MEDIA_AUI:
		अगर (!(de->media_advertise & ADVERTISED_AUI))
			वापस 0;
		अवरोध;
	हाल DE_MEDIA_TP:
		अगर (!(de->media_advertise & ADVERTISED_10baseT_Half))
			वापस 0;
		अवरोध;
	हाल DE_MEDIA_TP_FD:
		अगर (!(de->media_advertise & ADVERTISED_10baseT_Full))
			वापस 0;
		अवरोध;
	पूर्ण

	वापस 1;
पूर्ण

अटल व्योम de21041_media_समयr (काष्ठा समयr_list *t)
अणु
	काष्ठा de_निजी *de = from_समयr(de, t, media_समयr);
	काष्ठा net_device *dev = de->dev;
	u32 status = dr32(SIAStatus);
	अचिन्हित पूर्णांक carrier;
	अचिन्हित दीर्घ flags;

	/* clear port active bits */
	dw32(SIAStatus, NonselPortActive | SelPortActive);

	carrier = (status & NetCxnErr) ? 0 : 1;

	अगर (carrier) अणु
		अगर ((de->media_type == DE_MEDIA_TP_AUTO ||
		     de->media_type == DE_MEDIA_TP ||
		     de->media_type == DE_MEDIA_TP_FD) &&
		    (status & LinkFailStatus))
			जाओ no_link_yet;

		de->media_समयr.expires = jअगरfies + DE_TIMER_LINK;
		add_समयr(&de->media_समयr);
		अगर (!netअगर_carrier_ok(dev))
			de_link_up(de);
		अन्यथा
			netअगर_info(de, समयr, dev,
				   "%s link ok, mode %x status %x\n",
				   media_name[de->media_type],
				   dr32(MacMode), status);
		वापस;
	पूर्ण

	de_link_करोwn(de);

	/* अगर media type locked, करोn't चयन media */
	अगर (de->media_lock)
		जाओ set_media;

	/* अगर activity detected, use that as hपूर्णांक क्रम new media type */
	अगर (status & NonselPortActive) अणु
		अचिन्हित पूर्णांक have_media = 1;

		/* अगर AUI/BNC selected, then activity is on TP port */
		अगर (de->media_type == DE_MEDIA_AUI ||
		    de->media_type == DE_MEDIA_BNC) अणु
			अगर (de_ok_to_advertise(de, DE_MEDIA_TP_AUTO))
				de->media_type = DE_MEDIA_TP_AUTO;
			अन्यथा
				have_media = 0;
		पूर्ण

		/* TP selected.  If there is only TP and BNC, then it's BNC */
		अन्यथा अगर (((de->media_supported & DE_AUI_BNC) == SUPPORTED_BNC) &&
			 de_ok_to_advertise(de, DE_MEDIA_BNC))
			de->media_type = DE_MEDIA_BNC;

		/* TP selected.  If there is only TP and AUI, then it's AUI */
		अन्यथा अगर (((de->media_supported & DE_AUI_BNC) == SUPPORTED_AUI) &&
			 de_ok_to_advertise(de, DE_MEDIA_AUI))
			de->media_type = DE_MEDIA_AUI;

		/* otherwise, ignore the hपूर्णांक */
		अन्यथा
			have_media = 0;

		अगर (have_media)
			जाओ set_media;
	पूर्ण

	/*
	 * Absent or ambiguous activity hपूर्णांक, move to next advertised
	 * media state.  If de->media_type is left unchanged, this
	 * simply resets the PHY and reloads the current media settings.
	 */
	अगर (de->media_type == DE_MEDIA_AUI) अणु
		अटल स्थिर u32 next_states[] = अणु
			DE_MEDIA_BNC, DE_MEDIA_TP_AUTO
		पूर्ण;
		de_next_media(de, next_states, ARRAY_SIZE(next_states));
	पूर्ण अन्यथा अगर (de->media_type == DE_MEDIA_BNC) अणु
		अटल स्थिर u32 next_states[] = अणु
			DE_MEDIA_TP_AUTO, DE_MEDIA_AUI
		पूर्ण;
		de_next_media(de, next_states, ARRAY_SIZE(next_states));
	पूर्ण अन्यथा अणु
		अटल स्थिर u32 next_states[] = अणु
			DE_MEDIA_AUI, DE_MEDIA_BNC, DE_MEDIA_TP_AUTO
		पूर्ण;
		de_next_media(de, next_states, ARRAY_SIZE(next_states));
	पूर्ण

set_media:
	spin_lock_irqsave(&de->lock, flags);
	de_stop_rxtx(de);
	spin_unlock_irqrestore(&de->lock, flags);
	de_set_media(de);
	de_start_rxtx(de);

no_link_yet:
	de->media_समयr.expires = jअगरfies + DE_TIMER_NO_LINK;
	add_समयr(&de->media_समयr);

	netअगर_info(de, समयr, dev, "no link, trying media %s, status %x\n",
		   media_name[de->media_type], status);
पूर्ण

अटल व्योम de_media_पूर्णांकerrupt (काष्ठा de_निजी *de, u32 status)
अणु
	अगर (status & LinkPass) अणु
		/* Ignore अगर current media is AUI or BNC and we can't use TP */
		अगर ((de->media_type == DE_MEDIA_AUI ||
		     de->media_type == DE_MEDIA_BNC) &&
		    (de->media_lock ||
		     !de_ok_to_advertise(de, DE_MEDIA_TP_AUTO)))
			वापस;
		/* If current media is not TP, change it to TP */
		अगर ((de->media_type == DE_MEDIA_AUI ||
		     de->media_type == DE_MEDIA_BNC)) अणु
			de->media_type = DE_MEDIA_TP_AUTO;
			de_stop_rxtx(de);
			de_set_media(de);
			de_start_rxtx(de);
		पूर्ण
		de_link_up(de);
		mod_समयr(&de->media_समयr, jअगरfies + DE_TIMER_LINK);
		वापस;
	पूर्ण

	BUG_ON(!(status & LinkFail));
	/* Mark the link as करोwn only अगर current media is TP */
	अगर (netअगर_carrier_ok(de->dev) && de->media_type != DE_MEDIA_AUI &&
	    de->media_type != DE_MEDIA_BNC) अणु
		de_link_करोwn(de);
		mod_समयr(&de->media_समयr, jअगरfies + DE_TIMER_NO_LINK);
	पूर्ण
पूर्ण

अटल पूर्णांक de_reset_mac (काष्ठा de_निजी *de)
अणु
	u32 status, पंचांगp;

	/*
	 * Reset MAC.  de4x5.c and tulip.c examined क्रम "advice"
	 * in this area.
	 */

	अगर (dr32(BusMode) == 0xffffffff)
		वापस -EBUSY;

	/* Reset the chip, holding bit 0 set at least 50 PCI cycles. */
	dw32 (BusMode, CmdReset);
	mdelay (1);

	dw32 (BusMode, de_bus_mode);
	mdelay (1);

	क्रम (पंचांगp = 0; पंचांगp < 5; पंचांगp++) अणु
		dr32 (BusMode);
		mdelay (1);
	पूर्ण

	mdelay (1);

	status = dr32(MacStatus);
	अगर (status & (RxState | TxState))
		वापस -EBUSY;
	अगर (status == 0xffffffff)
		वापस -ENODEV;
	वापस 0;
पूर्ण

अटल व्योम de_adapter_wake (काष्ठा de_निजी *de)
अणु
	u32 pmctl;

	अगर (de->de21040)
		वापस;

	pci_पढ़ो_config_dword(de->pdev, PCIPM, &pmctl);
	अगर (pmctl & PM_Mask) अणु
		pmctl &= ~PM_Mask;
		pci_ग_लिखो_config_dword(de->pdev, PCIPM, pmctl);

		/* de4x5.c delays, so we करो too */
		msleep(10);
	पूर्ण
पूर्ण

अटल व्योम de_adapter_sleep (काष्ठा de_निजी *de)
अणु
	u32 pmctl;

	अगर (de->de21040)
		वापस;

	dw32(CSR13, 0); /* Reset phy */
	pci_पढ़ो_config_dword(de->pdev, PCIPM, &pmctl);
	pmctl |= PM_Sleep;
	pci_ग_लिखो_config_dword(de->pdev, PCIPM, pmctl);
पूर्ण

अटल पूर्णांक de_init_hw (काष्ठा de_निजी *de)
अणु
	काष्ठा net_device *dev = de->dev;
	u32 macmode;
	पूर्णांक rc;

	de_adapter_wake(de);

	macmode = dr32(MacMode) & ~MacModeClear;

	rc = de_reset_mac(de);
	अगर (rc)
		वापस rc;

	de_set_media(de); /* reset phy */

	dw32(RxRingAddr, de->ring_dma);
	dw32(TxRingAddr, de->ring_dma + (माप(काष्ठा de_desc) * DE_RX_RING_SIZE));

	dw32(MacMode, RxTx | macmode);

	dr32(RxMissed); /* self-clearing */

	dw32(IntrMask, de_पूर्णांकr_mask);

	de_set_rx_mode(dev);

	वापस 0;
पूर्ण

अटल पूर्णांक de_refill_rx (काष्ठा de_निजी *de)
अणु
	अचिन्हित i;

	क्रम (i = 0; i < DE_RX_RING_SIZE; i++) अणु
		काष्ठा sk_buff *skb;

		skb = netdev_alloc_skb(de->dev, de->rx_buf_sz);
		अगर (!skb)
			जाओ err_out;

		de->rx_skb[i].mapping = dma_map_single(&de->pdev->dev,
						       skb->data,
						       de->rx_buf_sz,
						       DMA_FROM_DEVICE);
		de->rx_skb[i].skb = skb;

		de->rx_ring[i].opts1 = cpu_to_le32(DescOwn);
		अगर (i == (DE_RX_RING_SIZE - 1))
			de->rx_ring[i].opts2 =
				cpu_to_le32(RingEnd | de->rx_buf_sz);
		अन्यथा
			de->rx_ring[i].opts2 = cpu_to_le32(de->rx_buf_sz);
		de->rx_ring[i].addr1 = cpu_to_le32(de->rx_skb[i].mapping);
		de->rx_ring[i].addr2 = 0;
	पूर्ण

	वापस 0;

err_out:
	de_clean_rings(de);
	वापस -ENOMEM;
पूर्ण

अटल पूर्णांक de_init_rings (काष्ठा de_निजी *de)
अणु
	स_रखो(de->tx_ring, 0, माप(काष्ठा de_desc) * DE_TX_RING_SIZE);
	de->tx_ring[DE_TX_RING_SIZE - 1].opts2 = cpu_to_le32(RingEnd);

	de->rx_tail = 0;
	de->tx_head = de->tx_tail = 0;

	वापस de_refill_rx (de);
पूर्ण

अटल पूर्णांक de_alloc_rings (काष्ठा de_निजी *de)
अणु
	de->rx_ring = dma_alloc_coherent(&de->pdev->dev, DE_RING_BYTES,
					 &de->ring_dma, GFP_KERNEL);
	अगर (!de->rx_ring)
		वापस -ENOMEM;
	de->tx_ring = &de->rx_ring[DE_RX_RING_SIZE];
	वापस de_init_rings(de);
पूर्ण

अटल व्योम de_clean_rings (काष्ठा de_निजी *de)
अणु
	अचिन्हित i;

	स_रखो(de->rx_ring, 0, माप(काष्ठा de_desc) * DE_RX_RING_SIZE);
	de->rx_ring[DE_RX_RING_SIZE - 1].opts2 = cpu_to_le32(RingEnd);
	wmb();
	स_रखो(de->tx_ring, 0, माप(काष्ठा de_desc) * DE_TX_RING_SIZE);
	de->tx_ring[DE_TX_RING_SIZE - 1].opts2 = cpu_to_le32(RingEnd);
	wmb();

	क्रम (i = 0; i < DE_RX_RING_SIZE; i++) अणु
		अगर (de->rx_skb[i].skb) अणु
			dma_unmap_single(&de->pdev->dev,
					 de->rx_skb[i].mapping, de->rx_buf_sz,
					 DMA_FROM_DEVICE);
			dev_kमुक्त_skb(de->rx_skb[i].skb);
		पूर्ण
	पूर्ण

	क्रम (i = 0; i < DE_TX_RING_SIZE; i++) अणु
		काष्ठा sk_buff *skb = de->tx_skb[i].skb;
		अगर ((skb) && (skb != DE_DUMMY_SKB)) अणु
			अगर (skb != DE_SETUP_SKB) अणु
				de->dev->stats.tx_dropped++;
				dma_unmap_single(&de->pdev->dev,
						 de->tx_skb[i].mapping,
						 skb->len, DMA_TO_DEVICE);
				dev_kमुक्त_skb(skb);
			पूर्ण अन्यथा अणु
				dma_unmap_single(&de->pdev->dev,
						 de->tx_skb[i].mapping,
						 माप(de->setup_frame),
						 DMA_TO_DEVICE);
			पूर्ण
		पूर्ण
	पूर्ण

	स_रखो(&de->rx_skb, 0, माप(काष्ठा ring_info) * DE_RX_RING_SIZE);
	स_रखो(&de->tx_skb, 0, माप(काष्ठा ring_info) * DE_TX_RING_SIZE);
पूर्ण

अटल व्योम de_मुक्त_rings (काष्ठा de_निजी *de)
अणु
	de_clean_rings(de);
	dma_मुक्त_coherent(&de->pdev->dev, DE_RING_BYTES, de->rx_ring,
			  de->ring_dma);
	de->rx_ring = शून्य;
	de->tx_ring = शून्य;
पूर्ण

अटल पूर्णांक de_खोलो (काष्ठा net_device *dev)
अणु
	काष्ठा de_निजी *de = netdev_priv(dev);
	स्थिर पूर्णांक irq = de->pdev->irq;
	पूर्णांक rc;

	netअगर_dbg(de, अगरup, dev, "enabling interface\n");

	de->rx_buf_sz = (dev->mtu <= 1500 ? PKT_BUF_SZ : dev->mtu + 32);

	rc = de_alloc_rings(de);
	अगर (rc) अणु
		netdev_err(dev, "ring allocation failure, err=%d\n", rc);
		वापस rc;
	पूर्ण

	dw32(IntrMask, 0);

	rc = request_irq(irq, de_पूर्णांकerrupt, IRQF_SHARED, dev->name, dev);
	अगर (rc) अणु
		netdev_err(dev, "IRQ %d request failure, err=%d\n", irq, rc);
		जाओ err_out_मुक्त;
	पूर्ण

	rc = de_init_hw(de);
	अगर (rc) अणु
		netdev_err(dev, "h/w init failure, err=%d\n", rc);
		जाओ err_out_मुक्त_irq;
	पूर्ण

	netअगर_start_queue(dev);
	mod_समयr(&de->media_समयr, jअगरfies + DE_TIMER_NO_LINK);

	वापस 0;

err_out_मुक्त_irq:
	मुक्त_irq(irq, dev);
err_out_मुक्त:
	de_मुक्त_rings(de);
	वापस rc;
पूर्ण

अटल पूर्णांक de_बंद (काष्ठा net_device *dev)
अणु
	काष्ठा de_निजी *de = netdev_priv(dev);
	अचिन्हित दीर्घ flags;

	netअगर_dbg(de, अगरकरोwn, dev, "disabling interface\n");

	del_समयr_sync(&de->media_समयr);

	spin_lock_irqsave(&de->lock, flags);
	de_stop_hw(de);
	netअगर_stop_queue(dev);
	netअगर_carrier_off(dev);
	spin_unlock_irqrestore(&de->lock, flags);

	मुक्त_irq(de->pdev->irq, dev);

	de_मुक्त_rings(de);
	de_adapter_sleep(de);
	वापस 0;
पूर्ण

अटल व्योम de_tx_समयout (काष्ठा net_device *dev, अचिन्हित पूर्णांक txqueue)
अणु
	काष्ठा de_निजी *de = netdev_priv(dev);
	स्थिर पूर्णांक irq = de->pdev->irq;

	netdev_dbg(dev, "NIC status %08x mode %08x sia %08x desc %u/%u/%u\n",
		   dr32(MacStatus), dr32(MacMode), dr32(SIAStatus),
		   de->rx_tail, de->tx_head, de->tx_tail);

	del_समयr_sync(&de->media_समयr);

	disable_irq(irq);
	spin_lock_irq(&de->lock);

	de_stop_hw(de);
	netअगर_stop_queue(dev);
	netअगर_carrier_off(dev);

	spin_unlock_irq(&de->lock);
	enable_irq(irq);

	/* Update the error counts. */
	__de_get_stats(de);

	synchronize_irq(irq);
	de_clean_rings(de);

	de_init_rings(de);

	de_init_hw(de);

	netअगर_wake_queue(dev);
पूर्ण

अटल व्योम __de_get_regs(काष्ठा de_निजी *de, u8 *buf)
अणु
	पूर्णांक i;
	u32 *rbuf = (u32 *)buf;

	/* पढ़ो all CSRs */
	क्रम (i = 0; i < DE_NUM_REGS; i++)
		rbuf[i] = dr32(i * 8);

	/* handle self-clearing RxMissed counter, CSR8 */
	de_rx_missed(de, rbuf[8]);
पूर्ण

अटल व्योम __de_get_link_ksettings(काष्ठा de_निजी *de,
				    काष्ठा ethtool_link_ksettings *cmd)
अणु
	ethtool_convert_legacy_u32_to_link_mode(cmd->link_modes.supported,
						de->media_supported);
	cmd->base.phy_address = 0;
	ethtool_convert_legacy_u32_to_link_mode(cmd->link_modes.advertising,
						de->media_advertise);

	चयन (de->media_type) अणु
	हाल DE_MEDIA_AUI:
		cmd->base.port = PORT_AUI;
		अवरोध;
	हाल DE_MEDIA_BNC:
		cmd->base.port = PORT_BNC;
		अवरोध;
	शेष:
		cmd->base.port = PORT_TP;
		अवरोध;
	पूर्ण

	cmd->base.speed = 10;

	अगर (dr32(MacMode) & FullDuplex)
		cmd->base.duplex = DUPLEX_FULL;
	अन्यथा
		cmd->base.duplex = DUPLEX_HALF;

	अगर (de->media_lock)
		cmd->base.स्वतःneg = AUTONEG_DISABLE;
	अन्यथा
		cmd->base.स्वतःneg = AUTONEG_ENABLE;

	/* ignore maxtxpkt, maxrxpkt क्रम now */
पूर्ण

अटल पूर्णांक __de_set_link_ksettings(काष्ठा de_निजी *de,
				   स्थिर काष्ठा ethtool_link_ksettings *cmd)
अणु
	u32 new_media;
	अचिन्हित पूर्णांक media_lock;
	u8 duplex = cmd->base.duplex;
	u8 port = cmd->base.port;
	u8 स्वतःneg = cmd->base.स्वतःneg;
	u32 advertising;

	ethtool_convert_link_mode_to_legacy_u32(&advertising,
						cmd->link_modes.advertising);

	अगर (cmd->base.speed != 10)
		वापस -EINVAL;
	अगर (duplex != DUPLEX_HALF && duplex != DUPLEX_FULL)
		वापस -EINVAL;
	अगर (port != PORT_TP && port != PORT_AUI && port != PORT_BNC)
		वापस -EINVAL;
	अगर (de->de21040 && port == PORT_BNC)
		वापस -EINVAL;
	अगर (स्वतःneg != AUTONEG_DISABLE && स्वतःneg != AUTONEG_ENABLE)
		वापस -EINVAL;
	अगर (advertising & ~de->media_supported)
		वापस -EINVAL;
	अगर (स्वतःneg == AUTONEG_ENABLE &&
	    (!(advertising & ADVERTISED_Autoneg)))
		वापस -EINVAL;

	चयन (port) अणु
	हाल PORT_AUI:
		new_media = DE_MEDIA_AUI;
		अगर (!(advertising & ADVERTISED_AUI))
			वापस -EINVAL;
		अवरोध;
	हाल PORT_BNC:
		new_media = DE_MEDIA_BNC;
		अगर (!(advertising & ADVERTISED_BNC))
			वापस -EINVAL;
		अवरोध;
	शेष:
		अगर (स्वतःneg == AUTONEG_ENABLE)
			new_media = DE_MEDIA_TP_AUTO;
		अन्यथा अगर (duplex == DUPLEX_FULL)
			new_media = DE_MEDIA_TP_FD;
		अन्यथा
			new_media = DE_MEDIA_TP;
		अगर (!(advertising & ADVERTISED_TP))
			वापस -EINVAL;
		अगर (!(advertising & (ADVERTISED_10baseT_Full |
				     ADVERTISED_10baseT_Half)))
			वापस -EINVAL;
		अवरोध;
	पूर्ण

	media_lock = (स्वतःneg == AUTONEG_ENABLE) ? 0 : 1;

	अगर ((new_media == de->media_type) &&
	    (media_lock == de->media_lock) &&
	    (advertising == de->media_advertise))
		वापस 0; /* nothing to change */

	de_link_करोwn(de);
	mod_समयr(&de->media_समयr, jअगरfies + DE_TIMER_NO_LINK);
	de_stop_rxtx(de);

	de->media_type = new_media;
	de->media_lock = media_lock;
	de->media_advertise = advertising;
	de_set_media(de);
	अगर (netअगर_running(de->dev))
		de_start_rxtx(de);

	वापस 0;
पूर्ण

अटल व्योम de_get_drvinfo (काष्ठा net_device *dev,काष्ठा ethtool_drvinfo *info)
अणु
	काष्ठा de_निजी *de = netdev_priv(dev);

	strlcpy(info->driver, DRV_NAME, माप(info->driver));
	strlcpy(info->bus_info, pci_name(de->pdev), माप(info->bus_info));
पूर्ण

अटल पूर्णांक de_get_regs_len(काष्ठा net_device *dev)
अणु
	वापस DE_REGS_SIZE;
पूर्ण

अटल पूर्णांक de_get_link_ksettings(काष्ठा net_device *dev,
				 काष्ठा ethtool_link_ksettings *cmd)
अणु
	काष्ठा de_निजी *de = netdev_priv(dev);

	spin_lock_irq(&de->lock);
	__de_get_link_ksettings(de, cmd);
	spin_unlock_irq(&de->lock);

	वापस 0;
पूर्ण

अटल पूर्णांक de_set_link_ksettings(काष्ठा net_device *dev,
				 स्थिर काष्ठा ethtool_link_ksettings *cmd)
अणु
	काष्ठा de_निजी *de = netdev_priv(dev);
	पूर्णांक rc;

	spin_lock_irq(&de->lock);
	rc = __de_set_link_ksettings(de, cmd);
	spin_unlock_irq(&de->lock);

	वापस rc;
पूर्ण

अटल u32 de_get_msglevel(काष्ठा net_device *dev)
अणु
	काष्ठा de_निजी *de = netdev_priv(dev);

	वापस de->msg_enable;
पूर्ण

अटल व्योम de_set_msglevel(काष्ठा net_device *dev, u32 msglvl)
अणु
	काष्ठा de_निजी *de = netdev_priv(dev);

	de->msg_enable = msglvl;
पूर्ण

अटल पूर्णांक de_get_eeprom(काष्ठा net_device *dev,
			 काष्ठा ethtool_eeprom *eeprom, u8 *data)
अणु
	काष्ठा de_निजी *de = netdev_priv(dev);

	अगर (!de->ee_data)
		वापस -EOPNOTSUPP;
	अगर ((eeprom->offset != 0) || (eeprom->magic != 0) ||
	    (eeprom->len != DE_EEPROM_SIZE))
		वापस -EINVAL;
	स_नकल(data, de->ee_data, eeprom->len);

	वापस 0;
पूर्ण

अटल पूर्णांक de_nway_reset(काष्ठा net_device *dev)
अणु
	काष्ठा de_निजी *de = netdev_priv(dev);
	u32 status;

	अगर (de->media_type != DE_MEDIA_TP_AUTO)
		वापस -EINVAL;
	अगर (netअगर_carrier_ok(de->dev))
		de_link_करोwn(de);

	status = dr32(SIAStatus);
	dw32(SIAStatus, (status & ~NWayState) | NWayRestart);
	netअगर_info(de, link, dev, "link nway restart, status %x,%x\n",
		   status, dr32(SIAStatus));
	वापस 0;
पूर्ण

अटल व्योम de_get_regs(काष्ठा net_device *dev, काष्ठा ethtool_regs *regs,
			व्योम *data)
अणु
	काष्ठा de_निजी *de = netdev_priv(dev);

	regs->version = (DE_REGS_VER << 2) | de->de21040;

	spin_lock_irq(&de->lock);
	__de_get_regs(de, data);
	spin_unlock_irq(&de->lock);
पूर्ण

अटल स्थिर काष्ठा ethtool_ops de_ethtool_ops = अणु
	.get_link		= ethtool_op_get_link,
	.get_drvinfo		= de_get_drvinfo,
	.get_regs_len		= de_get_regs_len,
	.get_msglevel		= de_get_msglevel,
	.set_msglevel		= de_set_msglevel,
	.get_eeprom		= de_get_eeprom,
	.nway_reset		= de_nway_reset,
	.get_regs		= de_get_regs,
	.get_link_ksettings	= de_get_link_ksettings,
	.set_link_ksettings	= de_set_link_ksettings,
पूर्ण;

अटल व्योम de21040_get_mac_address(काष्ठा de_निजी *de)
अणु
	अचिन्हित i;

	dw32 (ROMCmd, 0);	/* Reset the poपूर्णांकer with a dummy ग_लिखो. */
	udelay(5);

	क्रम (i = 0; i < 6; i++) अणु
		पूर्णांक value, boguscnt = 100000;
		करो अणु
			value = dr32(ROMCmd);
			rmb();
		पूर्ण जबतक (value < 0 && --boguscnt > 0);
		de->dev->dev_addr[i] = value;
		udelay(1);
		अगर (boguscnt <= 0)
			pr_warn("timeout reading 21040 MAC address byte %u\n",
				i);
	पूर्ण
पूर्ण

अटल व्योम de21040_get_media_info(काष्ठा de_निजी *de)
अणु
	अचिन्हित पूर्णांक i;

	de->media_type = DE_MEDIA_TP;
	de->media_supported |= SUPPORTED_TP | SUPPORTED_10baseT_Full |
			       SUPPORTED_10baseT_Half | SUPPORTED_AUI;
	de->media_advertise = de->media_supported;

	क्रम (i = 0; i < DE_MAX_MEDIA; i++) अणु
		चयन (i) अणु
		हाल DE_MEDIA_AUI:
		हाल DE_MEDIA_TP:
		हाल DE_MEDIA_TP_FD:
			de->media[i].type = i;
			de->media[i].csr13 = t21040_csr13[i];
			de->media[i].csr14 = t21040_csr14[i];
			de->media[i].csr15 = t21040_csr15[i];
			अवरोध;
		शेष:
			de->media[i].type = DE_MEDIA_INVALID;
			अवरोध;
		पूर्ण
	पूर्ण
पूर्ण

/* Note: this routine वापसs extra data bits क्रम size detection. */
अटल अचिन्हित tulip_पढ़ो_eeprom(व्योम __iomem *regs, पूर्णांक location,
				  पूर्णांक addr_len)
अणु
	पूर्णांक i;
	अचिन्हित retval = 0;
	व्योम __iomem *ee_addr = regs + ROMCmd;
	पूर्णांक पढ़ो_cmd = location | (EE_READ_CMD << addr_len);

	ग_लिखोl(EE_ENB & ~EE_CS, ee_addr);
	ग_लिखोl(EE_ENB, ee_addr);

	/* Shअगरt the पढ़ो command bits out. */
	क्रम (i = 4 + addr_len; i >= 0; i--) अणु
		लघु dataval = (पढ़ो_cmd & (1 << i)) ? EE_DATA_WRITE : 0;
		ग_लिखोl(EE_ENB | dataval, ee_addr);
		पढ़ोl(ee_addr);
		ग_लिखोl(EE_ENB | dataval | EE_SHIFT_CLK, ee_addr);
		पढ़ोl(ee_addr);
		retval = (retval << 1) | ((पढ़ोl(ee_addr) & EE_DATA_READ) ? 1 : 0);
	पूर्ण
	ग_लिखोl(EE_ENB, ee_addr);
	पढ़ोl(ee_addr);

	क्रम (i = 16; i > 0; i--) अणु
		ग_लिखोl(EE_ENB | EE_SHIFT_CLK, ee_addr);
		पढ़ोl(ee_addr);
		retval = (retval << 1) | ((पढ़ोl(ee_addr) & EE_DATA_READ) ? 1 : 0);
		ग_लिखोl(EE_ENB, ee_addr);
		पढ़ोl(ee_addr);
	पूर्ण

	/* Terminate the EEPROM access. */
	ग_लिखोl(EE_ENB & ~EE_CS, ee_addr);
	वापस retval;
पूर्ण

अटल व्योम de21041_get_srom_info(काष्ठा de_निजी *de)
अणु
	अचिन्हित i, sa_offset = 0, ofs;
	u8 ee_data[DE_EEPROM_SIZE + 6] = अणुपूर्ण;
	अचिन्हित ee_addr_size = tulip_पढ़ो_eeprom(de->regs, 0xff, 8) & 0x40000 ? 8 : 6;
	काष्ठा de_srom_info_leaf *il;
	व्योम *bufp;

	/* करोwnload entire eeprom */
	क्रम (i = 0; i < DE_EEPROM_WORDS; i++)
		((__le16 *)ee_data)[i] =
			cpu_to_le16(tulip_पढ़ो_eeprom(de->regs, i, ee_addr_size));

	/* DEC now has a specअगरication but early board makers
	   just put the address in the first EEPROM locations. */
	/* This करोes  स_भेद(eedata, eedata+16, 8) */

#अगर_अघोषित CONFIG_MIPS_COBALT

	क्रम (i = 0; i < 8; i ++)
		अगर (ee_data[i] != ee_data[16+i])
			sa_offset = 20;

#पूर्ण_अगर

	/* store MAC address */
	क्रम (i = 0; i < 6; i ++)
		de->dev->dev_addr[i] = ee_data[i + sa_offset];

	/* get offset of controller 0 info leaf.  ignore 2nd byte. */
	ofs = ee_data[SROMC0InfoLeaf];
	अगर (ofs >= (माप(ee_data) - माप(काष्ठा de_srom_info_leaf) - माप(काष्ठा de_srom_media_block)))
		जाओ bad_srom;

	/* get poपूर्णांकer to info leaf */
	il = (काष्ठा de_srom_info_leaf *) &ee_data[ofs];

	/* paranoia checks */
	अगर (il->n_blocks == 0)
		जाओ bad_srom;
	अगर ((माप(ee_data) - ofs) <
	    (माप(काष्ठा de_srom_info_leaf) + (माप(काष्ठा de_srom_media_block) * il->n_blocks)))
		जाओ bad_srom;

	/* get शेष media type */
	चयन (get_unaligned(&il->शेष_media)) अणु
	हाल 0x0001:  de->media_type = DE_MEDIA_BNC; अवरोध;
	हाल 0x0002:  de->media_type = DE_MEDIA_AUI; अवरोध;
	हाल 0x0204:  de->media_type = DE_MEDIA_TP_FD; अवरोध;
	शेष: de->media_type = DE_MEDIA_TP_AUTO; अवरोध;
	पूर्ण

	अगर (netअगर_msg_probe(de))
		pr_info("de%d: SROM leaf offset %u, default media %s\n",
		       de->board_idx, ofs, media_name[de->media_type]);

	/* init SIA रेजिस्टर values to शेषs */
	क्रम (i = 0; i < DE_MAX_MEDIA; i++) अणु
		de->media[i].type = DE_MEDIA_INVALID;
		de->media[i].csr13 = 0xffff;
		de->media[i].csr14 = 0xffff;
		de->media[i].csr15 = 0xffff;
	पूर्ण

	/* parse media blocks to see what medias are supported,
	 * and अगर any custom CSR values are provided
	 */
	bufp = ((व्योम *)il) + माप(*il);
	क्रम (i = 0; i < il->n_blocks; i++) अणु
		काष्ठा de_srom_media_block *ib = bufp;
		अचिन्हित idx;

		/* index based on media type in media block */
		चयन(ib->opts & MediaBlockMask) अणु
		हाल 0: /* 10baseT */
			de->media_supported |= SUPPORTED_TP | SUPPORTED_10baseT_Half
					  | SUPPORTED_Autoneg;
			idx = DE_MEDIA_TP;
			de->media[DE_MEDIA_TP_AUTO].type = DE_MEDIA_TP_AUTO;
			अवरोध;
		हाल 1: /* BNC */
			de->media_supported |= SUPPORTED_BNC;
			idx = DE_MEDIA_BNC;
			अवरोध;
		हाल 2: /* AUI */
			de->media_supported |= SUPPORTED_AUI;
			idx = DE_MEDIA_AUI;
			अवरोध;
		हाल 4: /* 10baseT-FD */
			de->media_supported |= SUPPORTED_TP | SUPPORTED_10baseT_Full
					  | SUPPORTED_Autoneg;
			idx = DE_MEDIA_TP_FD;
			de->media[DE_MEDIA_TP_AUTO].type = DE_MEDIA_TP_AUTO;
			अवरोध;
		शेष:
			जाओ bad_srom;
		पूर्ण

		de->media[idx].type = idx;

		अगर (netअगर_msg_probe(de))
			pr_info("de%d:   media block #%u: %s",
				de->board_idx, i,
				media_name[de->media[idx].type]);

		bufp += माप (ib->opts);

		अगर (ib->opts & MediaCustomCSRs) अणु
			de->media[idx].csr13 = get_unaligned(&ib->csr13);
			de->media[idx].csr14 = get_unaligned(&ib->csr14);
			de->media[idx].csr15 = get_unaligned(&ib->csr15);
			bufp += माप(ib->csr13) + माप(ib->csr14) +
				माप(ib->csr15);

			अगर (netअगर_msg_probe(de))
				pr_cont(" (%x,%x,%x)\n",
					de->media[idx].csr13,
					de->media[idx].csr14,
					de->media[idx].csr15);

		पूर्ण अन्यथा अणु
			अगर (netअगर_msg_probe(de))
				pr_cont("\n");
		पूर्ण

		अगर (bufp > ((व्योम *)&ee_data[DE_EEPROM_SIZE - 3]))
			अवरोध;
	पूर्ण

	de->media_advertise = de->media_supported;

fill_शेषs:
	/* fill in शेषs, क्रम हालs where custom CSRs not used */
	क्रम (i = 0; i < DE_MAX_MEDIA; i++) अणु
		अगर (de->media[i].csr13 == 0xffff)
			de->media[i].csr13 = t21041_csr13[i];
		अगर (de->media[i].csr14 == 0xffff) अणु
			/* स्वतःnegotiation is broken at least on some chip
			   revisions - rev. 0x21 works, 0x11 करोes not */
			अगर (de->pdev->revision < 0x20)
				de->media[i].csr14 = t21041_csr14_brk[i];
			अन्यथा
				de->media[i].csr14 = t21041_csr14[i];
		पूर्ण
		अगर (de->media[i].csr15 == 0xffff)
			de->media[i].csr15 = t21041_csr15[i];
	पूर्ण

	de->ee_data = kmemdup(&ee_data[0], DE_EEPROM_SIZE, GFP_KERNEL);

	वापस;

bad_srom:
	/* क्रम error हालs, it's ok to assume we support all these */
	क्रम (i = 0; i < DE_MAX_MEDIA; i++)
		de->media[i].type = i;
	de->media_supported =
		SUPPORTED_10baseT_Half |
		SUPPORTED_10baseT_Full |
		SUPPORTED_Autoneg |
		SUPPORTED_TP |
		SUPPORTED_AUI |
		SUPPORTED_BNC;
	जाओ fill_शेषs;
पूर्ण

अटल स्थिर काष्ठा net_device_ops de_netdev_ops = अणु
	.nकरो_खोलो		= de_खोलो,
	.nकरो_stop		= de_बंद,
	.nकरो_set_rx_mode	= de_set_rx_mode,
	.nकरो_start_xmit		= de_start_xmit,
	.nकरो_get_stats		= de_get_stats,
	.nकरो_tx_समयout 	= de_tx_समयout,
	.nकरो_set_mac_address 	= eth_mac_addr,
	.nकरो_validate_addr	= eth_validate_addr,
पूर्ण;

अटल पूर्णांक de_init_one(काष्ठा pci_dev *pdev, स्थिर काष्ठा pci_device_id *ent)
अणु
	काष्ठा net_device *dev;
	काष्ठा de_निजी *de;
	पूर्णांक rc;
	व्योम __iomem *regs;
	अचिन्हित दीर्घ pciaddr;
	अटल पूर्णांक board_idx = -1;

	board_idx++;

	/* allocate a new ethernet device काष्ठाure, and fill in शेषs */
	dev = alloc_etherdev(माप(काष्ठा de_निजी));
	अगर (!dev)
		वापस -ENOMEM;

	dev->netdev_ops = &de_netdev_ops;
	SET_NETDEV_DEV(dev, &pdev->dev);
	dev->ethtool_ops = &de_ethtool_ops;
	dev->watchकरोg_समयo = TX_TIMEOUT;

	de = netdev_priv(dev);
	de->de21040 = ent->driver_data == 0 ? 1 : 0;
	de->pdev = pdev;
	de->dev = dev;
	de->msg_enable = (debug < 0 ? DE_DEF_MSG_ENABLE : debug);
	de->board_idx = board_idx;
	spin_lock_init (&de->lock);
	समयr_setup(&de->media_समयr,
		    de->de21040 ? de21040_media_समयr : de21041_media_समयr,
		    0);

	netअगर_carrier_off(dev);

	/* wake up device, assign resources */
	rc = pci_enable_device(pdev);
	अगर (rc)
		जाओ err_out_मुक्त;

	/* reserve PCI resources to ensure driver atomicity */
	rc = pci_request_regions(pdev, DRV_NAME);
	अगर (rc)
		जाओ err_out_disable;

	/* check क्रम invalid IRQ value */
	अगर (pdev->irq < 2) अणु
		rc = -EIO;
		pr_err("invalid irq (%d) for pci dev %s\n",
		       pdev->irq, pci_name(pdev));
		जाओ err_out_res;
	पूर्ण

	/* obtain and check validity of PCI I/O address */
	pciaddr = pci_resource_start(pdev, 1);
	अगर (!pciaddr) अणु
		rc = -EIO;
		pr_err("no MMIO resource for pci dev %s\n", pci_name(pdev));
		जाओ err_out_res;
	पूर्ण
	अगर (pci_resource_len(pdev, 1) < DE_REGS_SIZE) अणु
		rc = -EIO;
		pr_err("MMIO resource (%llx) too small on pci dev %s\n",
		       (अचिन्हित दीर्घ दीर्घ)pci_resource_len(pdev, 1),
		       pci_name(pdev));
		जाओ err_out_res;
	पूर्ण

	/* remap CSR रेजिस्टरs */
	regs = ioremap(pciaddr, DE_REGS_SIZE);
	अगर (!regs) अणु
		rc = -EIO;
		pr_err("Cannot map PCI MMIO (%llx@%lx) on pci dev %s\n",
		       (अचिन्हित दीर्घ दीर्घ)pci_resource_len(pdev, 1),
		       pciaddr, pci_name(pdev));
		जाओ err_out_res;
	पूर्ण
	de->regs = regs;

	de_adapter_wake(de);

	/* make sure hardware is not running */
	rc = de_reset_mac(de);
	अगर (rc) अणु
		pr_err("Cannot reset MAC, pci dev %s\n", pci_name(pdev));
		जाओ err_out_iomap;
	पूर्ण

	/* get MAC address, initialize शेष media type and
	 * get list of supported media
	 */
	अगर (de->de21040) अणु
		de21040_get_mac_address(de);
		de21040_get_media_info(de);
	पूर्ण अन्यथा अणु
		de21041_get_srom_info(de);
	पूर्ण

	/* रेजिस्टर new network पूर्णांकerface with kernel */
	rc = रेजिस्टर_netdev(dev);
	अगर (rc)
		जाओ err_out_iomap;

	/* prपूर्णांक info about board and पूर्णांकerface just रेजिस्टरed */
	netdev_info(dev, "%s at %p, %pM, IRQ %d\n",
		    de->de21040 ? "21040" : "21041",
		    regs, dev->dev_addr, pdev->irq);

	pci_set_drvdata(pdev, dev);

	/* enable busmastering */
	pci_set_master(pdev);

	/* put adapter to sleep */
	de_adapter_sleep(de);

	वापस 0;

err_out_iomap:
	kमुक्त(de->ee_data);
	iounmap(regs);
err_out_res:
	pci_release_regions(pdev);
err_out_disable:
	pci_disable_device(pdev);
err_out_मुक्त:
	मुक्त_netdev(dev);
	वापस rc;
पूर्ण

अटल व्योम de_हटाओ_one(काष्ठा pci_dev *pdev)
अणु
	काष्ठा net_device *dev = pci_get_drvdata(pdev);
	काष्ठा de_निजी *de = netdev_priv(dev);

	BUG_ON(!dev);
	unरेजिस्टर_netdev(dev);
	kमुक्त(de->ee_data);
	iounmap(de->regs);
	pci_release_regions(pdev);
	pci_disable_device(pdev);
	मुक्त_netdev(dev);
पूर्ण

अटल पूर्णांक __maybe_unused de_suspend(काष्ठा device *dev_d)
अणु
	काष्ठा pci_dev *pdev = to_pci_dev(dev_d);
	काष्ठा net_device *dev = pci_get_drvdata(pdev);
	काष्ठा de_निजी *de = netdev_priv(dev);

	rtnl_lock();
	अगर (netअगर_running (dev)) अणु
		स्थिर पूर्णांक irq = pdev->irq;

		del_समयr_sync(&de->media_समयr);

		disable_irq(irq);
		spin_lock_irq(&de->lock);

		de_stop_hw(de);
		netअगर_stop_queue(dev);
		netअगर_device_detach(dev);
		netअगर_carrier_off(dev);

		spin_unlock_irq(&de->lock);
		enable_irq(irq);

		/* Update the error counts. */
		__de_get_stats(de);

		synchronize_irq(irq);
		de_clean_rings(de);

		de_adapter_sleep(de);
	पूर्ण अन्यथा अणु
		netअगर_device_detach(dev);
	पूर्ण
	rtnl_unlock();
	वापस 0;
पूर्ण

अटल पूर्णांक __maybe_unused de_resume(काष्ठा device *dev_d)
अणु
	काष्ठा pci_dev *pdev = to_pci_dev(dev_d);
	काष्ठा net_device *dev = pci_get_drvdata(pdev);
	काष्ठा de_निजी *de = netdev_priv(dev);

	rtnl_lock();
	अगर (netअगर_device_present(dev))
		जाओ out;
	अगर (!netअगर_running(dev))
		जाओ out_attach;
	pci_set_master(pdev);
	de_init_rings(de);
	de_init_hw(de);
out_attach:
	netअगर_device_attach(dev);
out:
	rtnl_unlock();
	वापस 0;
पूर्ण

अटल SIMPLE_DEV_PM_OPS(de_pm_ops, de_suspend, de_resume);

अटल व्योम de_shutकरोwn(काष्ठा pci_dev *pdev)
अणु
	काष्ठा net_device *dev = pci_get_drvdata(pdev);

	rtnl_lock();
	dev_बंद(dev);
	rtnl_unlock();
पूर्ण

अटल काष्ठा pci_driver de_driver = अणु
	.name		= DRV_NAME,
	.id_table	= de_pci_tbl,
	.probe		= de_init_one,
	.हटाओ		= de_हटाओ_one,
	.shutकरोwn	= de_shutकरोwn,
	.driver.pm	= &de_pm_ops,
पूर्ण;

module_pci_driver(de_driver);
