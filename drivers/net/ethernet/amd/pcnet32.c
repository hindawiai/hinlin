<शैली गुरु>
/* pcnet32.c: An AMD PCnet32 ethernet driver क्रम linux. */
/*
 *	Copyright 1996-1999 Thomas Bogenकरोerfer
 *
 *	Derived from the lance driver written 1993,1994,1995 by Donald Becker.
 *
 *	Copyright 1993 United States Government as represented by the
 *	Director, National Security Agency.
 *
 *	This software may be used and distributed according to the terms
 *	of the GNU General Public License, incorporated herein by reference.
 *
 *	This driver is क्रम PCnet32 and PCnetPCI based ethercards
 */
/**************************************************************************
 *  23 Oct, 2000.
 *  Fixed a few bugs, related to running the controller in 32bit mode.
 *
 *  Carsten Langgaard, carstenl@mips.com
 *  Copyright (C) 2000 MIPS Technologies, Inc.  All rights reserved.
 *
 *************************************************************************/

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#घोषणा DRV_NAME	"pcnet32"
#घोषणा DRV_RELDATE	"21.Apr.2008"
#घोषणा PFX		DRV_NAME ": "

#समावेश <linux/module.h>
#समावेश <linux/kernel.h>
#समावेश <linux/sched.h>
#समावेश <linux/माला.स>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/ioport.h>
#समावेश <linux/slab.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/pci.h>
#समावेश <linux/delay.h>
#समावेश <linux/init.h>
#समावेश <linux/ethtool.h>
#समावेश <linux/mii.h>
#समावेश <linux/crc32.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/etherdevice.h>
#समावेश <linux/अगर_ether.h>
#समावेश <linux/skbuff.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/moduleparam.h>
#समावेश <linux/bitops.h>
#समावेश <linux/पन.स>
#समावेश <linux/uaccess.h>

#समावेश <यंत्र/dma.h>
#समावेश <यंत्र/irq.h>

/*
 * PCI device identअगरiers क्रम "new style" Linux PCI Device Drivers
 */
अटल स्थिर काष्ठा pci_device_id pcnet32_pci_tbl[] = अणु
	अणु PCI_DEVICE(PCI_VENDOR_ID_AMD, PCI_DEVICE_ID_AMD_LANCE_HOME), पूर्ण,
	अणु PCI_DEVICE(PCI_VENDOR_ID_AMD, PCI_DEVICE_ID_AMD_LANCE), पूर्ण,

	/*
	 * Adapters that were sold with IBM's RS/6000 or pSeries hardware have
	 * the incorrect venकरोr id.
	 */
	अणु PCI_DEVICE(PCI_VENDOR_ID_TRIDENT, PCI_DEVICE_ID_AMD_LANCE),
	  .class = (PCI_CLASS_NETWORK_ETHERNET << 8), .class_mask = 0xffff00, पूर्ण,

	अणु पूर्ण	/* terminate list */
पूर्ण;

MODULE_DEVICE_TABLE(pci, pcnet32_pci_tbl);

अटल पूर्णांक cards_found;

/*
 * VLB I/O addresses
 */
अटल अचिन्हित पूर्णांक pcnet32_portlist[] =
    अणु 0x300, 0x320, 0x340, 0x360, 0 पूर्ण;

अटल पूर्णांक pcnet32_debug;
अटल पूर्णांक tx_start = 1;	/* Mapping -- 0:20, 1:64, 2:128, 3:~220 (depends on chip vers) */
अटल पूर्णांक pcnet32vlb;		/* check क्रम VLB cards ? */

अटल काष्ठा net_device *pcnet32_dev;

अटल पूर्णांक max_पूर्णांकerrupt_work = 2;
अटल पूर्णांक rx_copyअवरोध = 200;

#घोषणा PCNET32_PORT_AUI      0x00
#घोषणा PCNET32_PORT_10BT     0x01
#घोषणा PCNET32_PORT_GPSI     0x02
#घोषणा PCNET32_PORT_MII      0x03

#घोषणा PCNET32_PORT_PORTSEL  0x03
#घोषणा PCNET32_PORT_ASEL     0x04
#घोषणा PCNET32_PORT_100      0x40
#घोषणा PCNET32_PORT_FD	      0x80

#घोषणा PCNET32_DMA_MASK 0xffffffff

#घोषणा PCNET32_WATCHDOG_TIMEOUT (jअगरfies + (2 * HZ))
#घोषणा PCNET32_BLINK_TIMEOUT	(jअगरfies + (HZ/4))

/*
 * table to translate option values from tulip
 * to पूर्णांकernal options
 */
अटल स्थिर अचिन्हित अक्षर options_mapping[] = अणु
	PCNET32_PORT_ASEL,			/*  0 Auto-select      */
	PCNET32_PORT_AUI,			/*  1 BNC/AUI          */
	PCNET32_PORT_AUI,			/*  2 AUI/BNC          */
	PCNET32_PORT_ASEL,			/*  3 not supported    */
	PCNET32_PORT_10BT | PCNET32_PORT_FD,	/*  4 10baseT-FD       */
	PCNET32_PORT_ASEL,			/*  5 not supported    */
	PCNET32_PORT_ASEL,			/*  6 not supported    */
	PCNET32_PORT_ASEL,			/*  7 not supported    */
	PCNET32_PORT_ASEL,			/*  8 not supported    */
	PCNET32_PORT_MII,			/*  9 MII 10baseT      */
	PCNET32_PORT_MII | PCNET32_PORT_FD,	/* 10 MII 10baseT-FD   */
	PCNET32_PORT_MII,			/* 11 MII (स्वतःsel)    */
	PCNET32_PORT_10BT,			/* 12 10BaseT          */
	PCNET32_PORT_MII | PCNET32_PORT_100,	/* 13 MII 100BaseTx    */
						/* 14 MII 100BaseTx-FD */
	PCNET32_PORT_MII | PCNET32_PORT_100 | PCNET32_PORT_FD,
	PCNET32_PORT_ASEL			/* 15 not supported    */
पूर्ण;

अटल स्थिर अक्षर pcnet32_gstrings_test[][ETH_GSTRING_LEN] = अणु
	"Loopback test  (offline)"
पूर्ण;

#घोषणा PCNET32_TEST_LEN	ARRAY_SIZE(pcnet32_gstrings_test)

#घोषणा PCNET32_NUM_REGS 136

#घोषणा MAX_UNITS 8		/* More are supported, limit only on options */
अटल पूर्णांक options[MAX_UNITS];
अटल पूर्णांक full_duplex[MAX_UNITS];
अटल पूर्णांक homepna[MAX_UNITS];

/*
 *				Theory of Operation
 *
 * This driver uses the same software काष्ठाure as the normal lance
 * driver. So look क्रम a verbose description in lance.c. The dअगरferences
 * to the normal lance driver is the use of the 32bit mode of PCnet32
 * and PCnetPCI chips. Because these chips are 32bit chips, there is no
 * 16MB limitation and we करोn't need bounce buffers.
 */

/*
 * Set the number of Tx and Rx buffers, using Log_2(# buffers).
 * Reasonable शेष values are 4 Tx buffers, and 16 Rx buffers.
 * That translates to 2 (4 == 2^^2) and 4 (16 == 2^^4).
 */
#अगर_अघोषित PCNET32_LOG_TX_BUFFERS
#घोषणा PCNET32_LOG_TX_BUFFERS		4
#घोषणा PCNET32_LOG_RX_BUFFERS		5
#घोषणा PCNET32_LOG_MAX_TX_BUFFERS	9	/* 2^9 == 512 */
#घोषणा PCNET32_LOG_MAX_RX_BUFFERS	9
#पूर्ण_अगर

#घोषणा TX_RING_SIZE		(1 << (PCNET32_LOG_TX_BUFFERS))
#घोषणा TX_MAX_RING_SIZE	(1 << (PCNET32_LOG_MAX_TX_BUFFERS))

#घोषणा RX_RING_SIZE		(1 << (PCNET32_LOG_RX_BUFFERS))
#घोषणा RX_MAX_RING_SIZE	(1 << (PCNET32_LOG_MAX_RX_BUFFERS))

#घोषणा PKT_BUF_SKB		1544
/* actual buffer length after being aligned */
#घोषणा PKT_BUF_SIZE		(PKT_BUF_SKB - NET_IP_ALIGN)
/* chip wants twos complement of the (aligned) buffer length */
#घोषणा NEG_BUF_SIZE		(NET_IP_ALIGN - PKT_BUF_SKB)

/* Offsets from base I/O address. */
#घोषणा PCNET32_WIO_RDP		0x10
#घोषणा PCNET32_WIO_RAP		0x12
#घोषणा PCNET32_WIO_RESET	0x14
#घोषणा PCNET32_WIO_BDP		0x16

#घोषणा PCNET32_DWIO_RDP	0x10
#घोषणा PCNET32_DWIO_RAP	0x14
#घोषणा PCNET32_DWIO_RESET	0x18
#घोषणा PCNET32_DWIO_BDP	0x1C

#घोषणा PCNET32_TOTAL_SIZE	0x20

#घोषणा CSR0		0
#घोषणा CSR0_INIT	0x1
#घोषणा CSR0_START	0x2
#घोषणा CSR0_STOP	0x4
#घोषणा CSR0_TXPOLL	0x8
#घोषणा CSR0_INTEN	0x40
#घोषणा CSR0_IDON	0x0100
#घोषणा CSR0_NORMAL	(CSR0_START | CSR0_INTEN)
#घोषणा PCNET32_INIT_LOW	1
#घोषणा PCNET32_INIT_HIGH	2
#घोषणा CSR3		3
#घोषणा CSR4		4
#घोषणा CSR5		5
#घोषणा CSR5_SUSPEND	0x0001
#घोषणा CSR15		15
#घोषणा PCNET32_MC_FILTER	8

#घोषणा PCNET32_79C970A	0x2621

/* The PCNET32 Rx and Tx ring descriptors. */
काष्ठा pcnet32_rx_head अणु
	__le32	base;
	__le16	buf_length;	/* two`s complement of length */
	__le16	status;
	__le32	msg_length;
	__le32	reserved;
पूर्ण;

काष्ठा pcnet32_tx_head अणु
	__le32	base;
	__le16	length;		/* two`s complement of length */
	__le16	status;
	__le32	misc;
	__le32	reserved;
पूर्ण;

/* The PCNET32 32-Bit initialization block, described in databook. */
काष्ठा pcnet32_init_block अणु
	__le16	mode;
	__le16	tlen_rlen;
	u8	phys_addr[6];
	__le16	reserved;
	__le32	filter[2];
	/* Receive and transmit ring base, aदीर्घ with extra bits. */
	__le32	rx_ring;
	__le32	tx_ring;
पूर्ण;

/* PCnet32 access functions */
काष्ठा pcnet32_access अणु
	u16	(*पढ़ो_csr) (अचिन्हित दीर्घ, पूर्णांक);
	व्योम	(*ग_लिखो_csr) (अचिन्हित दीर्घ, पूर्णांक, u16);
	u16	(*पढ़ो_bcr) (अचिन्हित दीर्घ, पूर्णांक);
	व्योम	(*ग_लिखो_bcr) (अचिन्हित दीर्घ, पूर्णांक, u16);
	u16	(*पढ़ो_rap) (अचिन्हित दीर्घ);
	व्योम	(*ग_लिखो_rap) (अचिन्हित दीर्घ, u16);
	व्योम	(*reset) (अचिन्हित दीर्घ);
पूर्ण;

/*
 * The first field of pcnet32_निजी is पढ़ो by the ethernet device
 * so the काष्ठाure should be allocated using dma_alloc_coherent().
 */
काष्ठा pcnet32_निजी अणु
	काष्ठा pcnet32_init_block *init_block;
	/* The Tx and Rx ring entries must be aligned on 16-byte boundaries in 32bit mode. */
	काष्ठा pcnet32_rx_head	*rx_ring;
	काष्ठा pcnet32_tx_head	*tx_ring;
	dma_addr_t		init_dma_addr;/* DMA address of beginning of the init block,
				   वापसed by dma_alloc_coherent */
	काष्ठा pci_dev		*pci_dev;
	स्थिर अक्षर		*name;
	/* The saved address of a sent-in-place packet/buffer, क्रम skमुक्त(). */
	काष्ठा sk_buff		**tx_skbuff;
	काष्ठा sk_buff		**rx_skbuff;
	dma_addr_t		*tx_dma_addr;
	dma_addr_t		*rx_dma_addr;
	स्थिर काष्ठा pcnet32_access *a;
	spinlock_t		lock;		/* Guard lock */
	अचिन्हित पूर्णांक		cur_rx, cur_tx;	/* The next मुक्त ring entry */
	अचिन्हित पूर्णांक		rx_ring_size;	/* current rx ring size */
	अचिन्हित पूर्णांक		tx_ring_size;	/* current tx ring size */
	अचिन्हित पूर्णांक		rx_mod_mask;	/* rx ring modular mask */
	अचिन्हित पूर्णांक		tx_mod_mask;	/* tx ring modular mask */
	अचिन्हित लघु		rx_len_bits;
	अचिन्हित लघु		tx_len_bits;
	dma_addr_t		rx_ring_dma_addr;
	dma_addr_t		tx_ring_dma_addr;
	अचिन्हित पूर्णांक		dirty_rx,	/* ring entries to be मुक्तd. */
				dirty_tx;

	काष्ठा net_device	*dev;
	काष्ठा napi_काष्ठा	napi;
	अक्षर			tx_full;
	अक्षर			phycount;	/* number of phys found */
	पूर्णांक			options;
	अचिन्हित पूर्णांक		shared_irq:1,	/* shared irq possible */
				dxsuflo:1,   /* disable transmit stop on uflo */
				mii:1,		/* mii port available */
				स्वतःneg:1,	/* स्वतःneg enabled */
				port_tp:1,	/* port set to TP */
				fdx:1;		/* full duplex enabled */
	काष्ठा net_device	*next;
	काष्ठा mii_अगर_info	mii_अगर;
	काष्ठा समयr_list	watchकरोg_समयr;
	u32			msg_enable;	/* debug message level */

	/* each bit indicates an available PHY */
	u32			phymask;
	अचिन्हित लघु		chip_version;	/* which variant this is */

	/* saved रेजिस्टरs during ethtool blink */
	u16 			save_regs[4];
पूर्ण;

अटल पूर्णांक pcnet32_probe_pci(काष्ठा pci_dev *, स्थिर काष्ठा pci_device_id *);
अटल पूर्णांक pcnet32_probe1(अचिन्हित दीर्घ, पूर्णांक, काष्ठा pci_dev *);
अटल पूर्णांक pcnet32_खोलो(काष्ठा net_device *);
अटल पूर्णांक pcnet32_init_ring(काष्ठा net_device *);
अटल netdev_tx_t pcnet32_start_xmit(काष्ठा sk_buff *,
				      काष्ठा net_device *);
अटल व्योम pcnet32_tx_समयout(काष्ठा net_device *dev, अचिन्हित पूर्णांक txqueue);
अटल irqवापस_t pcnet32_पूर्णांकerrupt(पूर्णांक, व्योम *);
अटल पूर्णांक pcnet32_बंद(काष्ठा net_device *);
अटल काष्ठा net_device_stats *pcnet32_get_stats(काष्ठा net_device *);
अटल व्योम pcnet32_load_multicast(काष्ठा net_device *dev);
अटल व्योम pcnet32_set_multicast_list(काष्ठा net_device *);
अटल पूर्णांक pcnet32_ioctl(काष्ठा net_device *, काष्ठा अगरreq *, पूर्णांक);
अटल व्योम pcnet32_watchकरोg(काष्ठा समयr_list *);
अटल पूर्णांक mdio_पढ़ो(काष्ठा net_device *dev, पूर्णांक phy_id, पूर्णांक reg_num);
अटल व्योम mdio_ग_लिखो(काष्ठा net_device *dev, पूर्णांक phy_id, पूर्णांक reg_num,
		       पूर्णांक val);
अटल व्योम pcnet32_restart(काष्ठा net_device *dev, अचिन्हित पूर्णांक csr0_bits);
अटल व्योम pcnet32_ethtool_test(काष्ठा net_device *dev,
				 काष्ठा ethtool_test *eth_test, u64 * data);
अटल पूर्णांक pcnet32_loopback_test(काष्ठा net_device *dev, uपूर्णांक64_t * data1);
अटल पूर्णांक pcnet32_get_regs_len(काष्ठा net_device *dev);
अटल व्योम pcnet32_get_regs(काष्ठा net_device *dev, काष्ठा ethtool_regs *regs,
			     व्योम *ptr);
अटल व्योम pcnet32_purge_tx_ring(काष्ठा net_device *dev);
अटल पूर्णांक pcnet32_alloc_ring(काष्ठा net_device *dev, स्थिर अक्षर *name);
अटल व्योम pcnet32_मुक्त_ring(काष्ठा net_device *dev);
अटल व्योम pcnet32_check_media(काष्ठा net_device *dev, पूर्णांक verbose);

अटल u16 pcnet32_wio_पढ़ो_csr(अचिन्हित दीर्घ addr, पूर्णांक index)
अणु
	outw(index, addr + PCNET32_WIO_RAP);
	वापस inw(addr + PCNET32_WIO_RDP);
पूर्ण

अटल व्योम pcnet32_wio_ग_लिखो_csr(अचिन्हित दीर्घ addr, पूर्णांक index, u16 val)
अणु
	outw(index, addr + PCNET32_WIO_RAP);
	outw(val, addr + PCNET32_WIO_RDP);
पूर्ण

अटल u16 pcnet32_wio_पढ़ो_bcr(अचिन्हित दीर्घ addr, पूर्णांक index)
अणु
	outw(index, addr + PCNET32_WIO_RAP);
	वापस inw(addr + PCNET32_WIO_BDP);
पूर्ण

अटल व्योम pcnet32_wio_ग_लिखो_bcr(अचिन्हित दीर्घ addr, पूर्णांक index, u16 val)
अणु
	outw(index, addr + PCNET32_WIO_RAP);
	outw(val, addr + PCNET32_WIO_BDP);
पूर्ण

अटल u16 pcnet32_wio_पढ़ो_rap(अचिन्हित दीर्घ addr)
अणु
	वापस inw(addr + PCNET32_WIO_RAP);
पूर्ण

अटल व्योम pcnet32_wio_ग_लिखो_rap(अचिन्हित दीर्घ addr, u16 val)
अणु
	outw(val, addr + PCNET32_WIO_RAP);
पूर्ण

अटल व्योम pcnet32_wio_reset(अचिन्हित दीर्घ addr)
अणु
	inw(addr + PCNET32_WIO_RESET);
पूर्ण

अटल पूर्णांक pcnet32_wio_check(अचिन्हित दीर्घ addr)
अणु
	outw(88, addr + PCNET32_WIO_RAP);
	वापस inw(addr + PCNET32_WIO_RAP) == 88;
पूर्ण

अटल स्थिर काष्ठा pcnet32_access pcnet32_wio = अणु
	.पढ़ो_csr = pcnet32_wio_पढ़ो_csr,
	.ग_लिखो_csr = pcnet32_wio_ग_लिखो_csr,
	.पढ़ो_bcr = pcnet32_wio_पढ़ो_bcr,
	.ग_लिखो_bcr = pcnet32_wio_ग_लिखो_bcr,
	.पढ़ो_rap = pcnet32_wio_पढ़ो_rap,
	.ग_लिखो_rap = pcnet32_wio_ग_लिखो_rap,
	.reset = pcnet32_wio_reset
पूर्ण;

अटल u16 pcnet32_dwio_पढ़ो_csr(अचिन्हित दीर्घ addr, पूर्णांक index)
अणु
	outl(index, addr + PCNET32_DWIO_RAP);
	वापस inl(addr + PCNET32_DWIO_RDP) & 0xffff;
पूर्ण

अटल व्योम pcnet32_dwio_ग_लिखो_csr(अचिन्हित दीर्घ addr, पूर्णांक index, u16 val)
अणु
	outl(index, addr + PCNET32_DWIO_RAP);
	outl(val, addr + PCNET32_DWIO_RDP);
पूर्ण

अटल u16 pcnet32_dwio_पढ़ो_bcr(अचिन्हित दीर्घ addr, पूर्णांक index)
अणु
	outl(index, addr + PCNET32_DWIO_RAP);
	वापस inl(addr + PCNET32_DWIO_BDP) & 0xffff;
पूर्ण

अटल व्योम pcnet32_dwio_ग_लिखो_bcr(अचिन्हित दीर्घ addr, पूर्णांक index, u16 val)
अणु
	outl(index, addr + PCNET32_DWIO_RAP);
	outl(val, addr + PCNET32_DWIO_BDP);
पूर्ण

अटल u16 pcnet32_dwio_पढ़ो_rap(अचिन्हित दीर्घ addr)
अणु
	वापस inl(addr + PCNET32_DWIO_RAP) & 0xffff;
पूर्ण

अटल व्योम pcnet32_dwio_ग_लिखो_rap(अचिन्हित दीर्घ addr, u16 val)
अणु
	outl(val, addr + PCNET32_DWIO_RAP);
पूर्ण

अटल व्योम pcnet32_dwio_reset(अचिन्हित दीर्घ addr)
अणु
	inl(addr + PCNET32_DWIO_RESET);
पूर्ण

अटल पूर्णांक pcnet32_dwio_check(अचिन्हित दीर्घ addr)
अणु
	outl(88, addr + PCNET32_DWIO_RAP);
	वापस (inl(addr + PCNET32_DWIO_RAP) & 0xffff) == 88;
पूर्ण

अटल स्थिर काष्ठा pcnet32_access pcnet32_dwio = अणु
	.पढ़ो_csr = pcnet32_dwio_पढ़ो_csr,
	.ग_लिखो_csr = pcnet32_dwio_ग_लिखो_csr,
	.पढ़ो_bcr = pcnet32_dwio_पढ़ो_bcr,
	.ग_लिखो_bcr = pcnet32_dwio_ग_लिखो_bcr,
	.पढ़ो_rap = pcnet32_dwio_पढ़ो_rap,
	.ग_लिखो_rap = pcnet32_dwio_ग_लिखो_rap,
	.reset = pcnet32_dwio_reset
पूर्ण;

अटल व्योम pcnet32_netअगर_stop(काष्ठा net_device *dev)
अणु
	काष्ठा pcnet32_निजी *lp = netdev_priv(dev);

	netअगर_trans_update(dev); /* prevent tx समयout */
	napi_disable(&lp->napi);
	netअगर_tx_disable(dev);
पूर्ण

अटल व्योम pcnet32_netअगर_start(काष्ठा net_device *dev)
अणु
	काष्ठा pcnet32_निजी *lp = netdev_priv(dev);
	uदीर्घ ioaddr = dev->base_addr;
	u16 val;

	netअगर_wake_queue(dev);
	val = lp->a->पढ़ो_csr(ioaddr, CSR3);
	val &= 0x00ff;
	lp->a->ग_लिखो_csr(ioaddr, CSR3, val);
	napi_enable(&lp->napi);
पूर्ण

/*
 * Allocate space क्रम the new sized tx ring.
 * Free old resources
 * Save new resources.
 * Any failure keeps old resources.
 * Must be called with lp->lock held.
 */
अटल व्योम pcnet32_पुनः_स्मृति_tx_ring(काष्ठा net_device *dev,
				    काष्ठा pcnet32_निजी *lp,
				    अचिन्हित पूर्णांक size)
अणु
	dma_addr_t new_ring_dma_addr;
	dma_addr_t *new_dma_addr_list;
	काष्ठा pcnet32_tx_head *new_tx_ring;
	काष्ठा sk_buff **new_skb_list;
	अचिन्हित पूर्णांक entries = BIT(size);

	pcnet32_purge_tx_ring(dev);

	new_tx_ring =
		dma_alloc_coherent(&lp->pci_dev->dev,
				   माप(काष्ठा pcnet32_tx_head) * entries,
				   &new_ring_dma_addr, GFP_ATOMIC);
	अगर (new_tx_ring == शून्य)
		वापस;

	new_dma_addr_list = kसुस्मृति(entries, माप(dma_addr_t), GFP_ATOMIC);
	अगर (!new_dma_addr_list)
		जाओ मुक्त_new_tx_ring;

	new_skb_list = kसुस्मृति(entries, माप(काष्ठा sk_buff *), GFP_ATOMIC);
	अगर (!new_skb_list)
		जाओ मुक्त_new_lists;

	kमुक्त(lp->tx_skbuff);
	kमुक्त(lp->tx_dma_addr);
	dma_मुक्त_coherent(&lp->pci_dev->dev,
			  माप(काष्ठा pcnet32_tx_head) * lp->tx_ring_size,
			  lp->tx_ring, lp->tx_ring_dma_addr);

	lp->tx_ring_size = entries;
	lp->tx_mod_mask = lp->tx_ring_size - 1;
	lp->tx_len_bits = (size << 12);
	lp->tx_ring = new_tx_ring;
	lp->tx_ring_dma_addr = new_ring_dma_addr;
	lp->tx_dma_addr = new_dma_addr_list;
	lp->tx_skbuff = new_skb_list;
	वापस;

मुक्त_new_lists:
	kमुक्त(new_dma_addr_list);
मुक्त_new_tx_ring:
	dma_मुक्त_coherent(&lp->pci_dev->dev,
			  माप(काष्ठा pcnet32_tx_head) * entries,
			  new_tx_ring, new_ring_dma_addr);
पूर्ण

/*
 * Allocate space क्रम the new sized rx ring.
 * Re-use old receive buffers.
 *   alloc extra buffers
 *   मुक्त unneeded buffers
 *   मुक्त unneeded buffers
 * Save new resources.
 * Any failure keeps old resources.
 * Must be called with lp->lock held.
 */
अटल व्योम pcnet32_पुनः_स्मृति_rx_ring(काष्ठा net_device *dev,
				    काष्ठा pcnet32_निजी *lp,
				    अचिन्हित पूर्णांक size)
अणु
	dma_addr_t new_ring_dma_addr;
	dma_addr_t *new_dma_addr_list;
	काष्ठा pcnet32_rx_head *new_rx_ring;
	काष्ठा sk_buff **new_skb_list;
	पूर्णांक new, overlap;
	अचिन्हित पूर्णांक entries = BIT(size);

	new_rx_ring =
		dma_alloc_coherent(&lp->pci_dev->dev,
				   माप(काष्ठा pcnet32_rx_head) * entries,
				   &new_ring_dma_addr, GFP_ATOMIC);
	अगर (new_rx_ring == शून्य)
		वापस;

	new_dma_addr_list = kसुस्मृति(entries, माप(dma_addr_t), GFP_ATOMIC);
	अगर (!new_dma_addr_list)
		जाओ मुक्त_new_rx_ring;

	new_skb_list = kसुस्मृति(entries, माप(काष्ठा sk_buff *), GFP_ATOMIC);
	अगर (!new_skb_list)
		जाओ मुक्त_new_lists;

	/* first copy the current receive buffers */
	overlap = min(entries, lp->rx_ring_size);
	क्रम (new = 0; new < overlap; new++) अणु
		new_rx_ring[new] = lp->rx_ring[new];
		new_dma_addr_list[new] = lp->rx_dma_addr[new];
		new_skb_list[new] = lp->rx_skbuff[new];
	पूर्ण
	/* now allocate any new buffers needed */
	क्रम (; new < entries; new++) अणु
		काष्ठा sk_buff *rx_skbuff;
		new_skb_list[new] = netdev_alloc_skb(dev, PKT_BUF_SKB);
		rx_skbuff = new_skb_list[new];
		अगर (!rx_skbuff) अणु
			/* keep the original lists and buffers */
			netअगर_err(lp, drv, dev, "%s netdev_alloc_skb failed\n",
				  __func__);
			जाओ मुक्त_all_new;
		पूर्ण
		skb_reserve(rx_skbuff, NET_IP_ALIGN);

		new_dma_addr_list[new] =
			    dma_map_single(&lp->pci_dev->dev, rx_skbuff->data,
					   PKT_BUF_SIZE, DMA_FROM_DEVICE);
		अगर (dma_mapping_error(&lp->pci_dev->dev, new_dma_addr_list[new])) अणु
			netअगर_err(lp, drv, dev, "%s dma mapping failed\n",
				  __func__);
			dev_kमुक्त_skb(new_skb_list[new]);
			जाओ मुक्त_all_new;
		पूर्ण
		new_rx_ring[new].base = cpu_to_le32(new_dma_addr_list[new]);
		new_rx_ring[new].buf_length = cpu_to_le16(NEG_BUF_SIZE);
		new_rx_ring[new].status = cpu_to_le16(0x8000);
	पूर्ण
	/* and मुक्त any unneeded buffers */
	क्रम (; new < lp->rx_ring_size; new++) अणु
		अगर (lp->rx_skbuff[new]) अणु
			अगर (!dma_mapping_error(&lp->pci_dev->dev, lp->rx_dma_addr[new]))
				dma_unmap_single(&lp->pci_dev->dev,
						 lp->rx_dma_addr[new],
						 PKT_BUF_SIZE,
						 DMA_FROM_DEVICE);
			dev_kमुक्त_skb(lp->rx_skbuff[new]);
		पूर्ण
	पूर्ण

	kमुक्त(lp->rx_skbuff);
	kमुक्त(lp->rx_dma_addr);
	dma_मुक्त_coherent(&lp->pci_dev->dev,
			  माप(काष्ठा pcnet32_rx_head) * lp->rx_ring_size,
			  lp->rx_ring, lp->rx_ring_dma_addr);

	lp->rx_ring_size = entries;
	lp->rx_mod_mask = lp->rx_ring_size - 1;
	lp->rx_len_bits = (size << 4);
	lp->rx_ring = new_rx_ring;
	lp->rx_ring_dma_addr = new_ring_dma_addr;
	lp->rx_dma_addr = new_dma_addr_list;
	lp->rx_skbuff = new_skb_list;
	वापस;

मुक्त_all_new:
	जबतक (--new >= lp->rx_ring_size) अणु
		अगर (new_skb_list[new]) अणु
			अगर (!dma_mapping_error(&lp->pci_dev->dev, new_dma_addr_list[new]))
				dma_unmap_single(&lp->pci_dev->dev,
						 new_dma_addr_list[new],
						 PKT_BUF_SIZE,
						 DMA_FROM_DEVICE);
			dev_kमुक्त_skb(new_skb_list[new]);
		पूर्ण
	पूर्ण
	kमुक्त(new_skb_list);
मुक्त_new_lists:
	kमुक्त(new_dma_addr_list);
मुक्त_new_rx_ring:
	dma_मुक्त_coherent(&lp->pci_dev->dev,
			  माप(काष्ठा pcnet32_rx_head) * entries,
			  new_rx_ring, new_ring_dma_addr);
पूर्ण

अटल व्योम pcnet32_purge_rx_ring(काष्ठा net_device *dev)
अणु
	काष्ठा pcnet32_निजी *lp = netdev_priv(dev);
	पूर्णांक i;

	/* मुक्त all allocated skbuffs */
	क्रम (i = 0; i < lp->rx_ring_size; i++) अणु
		lp->rx_ring[i].status = 0;	/* CPU owns buffer */
		wmb();		/* Make sure adapter sees owner change */
		अगर (lp->rx_skbuff[i]) अणु
			अगर (!dma_mapping_error(&lp->pci_dev->dev, lp->rx_dma_addr[i]))
				dma_unmap_single(&lp->pci_dev->dev,
						 lp->rx_dma_addr[i],
						 PKT_BUF_SIZE,
						 DMA_FROM_DEVICE);
			dev_kमुक्त_skb_any(lp->rx_skbuff[i]);
		पूर्ण
		lp->rx_skbuff[i] = शून्य;
		lp->rx_dma_addr[i] = 0;
	पूर्ण
पूर्ण

#अगर_घोषित CONFIG_NET_POLL_CONTROLLER
अटल व्योम pcnet32_poll_controller(काष्ठा net_device *dev)
अणु
	disable_irq(dev->irq);
	pcnet32_पूर्णांकerrupt(0, dev);
	enable_irq(dev->irq);
पूर्ण
#पूर्ण_अगर

/*
 * lp->lock must be held.
 */
अटल पूर्णांक pcnet32_suspend(काष्ठा net_device *dev, अचिन्हित दीर्घ *flags,
			   पूर्णांक can_sleep)
अणु
	पूर्णांक csr5;
	काष्ठा pcnet32_निजी *lp = netdev_priv(dev);
	स्थिर काष्ठा pcnet32_access *a = lp->a;
	uदीर्घ ioaddr = dev->base_addr;
	पूर्णांक ticks;

	/* really old chips have to be stopped. */
	अगर (lp->chip_version < PCNET32_79C970A)
		वापस 0;

	/* set SUSPEND (SPND) - CSR5 bit 0 */
	csr5 = a->पढ़ो_csr(ioaddr, CSR5);
	a->ग_लिखो_csr(ioaddr, CSR5, csr5 | CSR5_SUSPEND);

	/* poll रुकोing क्रम bit to be set */
	ticks = 0;
	जबतक (!(a->पढ़ो_csr(ioaddr, CSR5) & CSR5_SUSPEND)) अणु
		spin_unlock_irqrestore(&lp->lock, *flags);
		अगर (can_sleep)
			msleep(1);
		अन्यथा
			mdelay(1);
		spin_lock_irqsave(&lp->lock, *flags);
		ticks++;
		अगर (ticks > 200) अणु
			netअगर_prपूर्णांकk(lp, hw, KERN_DEBUG, dev,
				     "Error getting into suspend!\n");
			वापस 0;
		पूर्ण
	पूर्ण
	वापस 1;
पूर्ण

अटल व्योम pcnet32_clr_suspend(काष्ठा pcnet32_निजी *lp, uदीर्घ ioaddr)
अणु
	पूर्णांक csr5 = lp->a->पढ़ो_csr(ioaddr, CSR5);
	/* clear SUSPEND (SPND) - CSR5 bit 0 */
	lp->a->ग_लिखो_csr(ioaddr, CSR5, csr5 & ~CSR5_SUSPEND);
पूर्ण

अटल पूर्णांक pcnet32_get_link_ksettings(काष्ठा net_device *dev,
				      काष्ठा ethtool_link_ksettings *cmd)
अणु
	काष्ठा pcnet32_निजी *lp = netdev_priv(dev);
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&lp->lock, flags);
	अगर (lp->mii) अणु
		mii_ethtool_get_link_ksettings(&lp->mii_अगर, cmd);
	पूर्ण अन्यथा अगर (lp->chip_version == PCNET32_79C970A) अणु
		अगर (lp->स्वतःneg) अणु
			cmd->base.स्वतःneg = AUTONEG_ENABLE;
			अगर (lp->a->पढ़ो_bcr(dev->base_addr, 4) == 0xc0)
				cmd->base.port = PORT_AUI;
			अन्यथा
				cmd->base.port = PORT_TP;
		पूर्ण अन्यथा अणु
			cmd->base.स्वतःneg = AUTONEG_DISABLE;
			cmd->base.port = lp->port_tp ? PORT_TP : PORT_AUI;
		पूर्ण
		cmd->base.duplex = lp->fdx ? DUPLEX_FULL : DUPLEX_HALF;
		cmd->base.speed = SPEED_10;
		ethtool_convert_legacy_u32_to_link_mode(
						cmd->link_modes.supported,
						SUPPORTED_TP | SUPPORTED_AUI);
	पूर्ण
	spin_unlock_irqrestore(&lp->lock, flags);
	वापस 0;
पूर्ण

अटल पूर्णांक pcnet32_set_link_ksettings(काष्ठा net_device *dev,
				      स्थिर काष्ठा ethtool_link_ksettings *cmd)
अणु
	काष्ठा pcnet32_निजी *lp = netdev_priv(dev);
	uदीर्घ ioaddr = dev->base_addr;
	अचिन्हित दीर्घ flags;
	पूर्णांक r = -EOPNOTSUPP;
	पूर्णांक suspended, bcr2, bcr9, csr15;

	spin_lock_irqsave(&lp->lock, flags);
	अगर (lp->mii) अणु
		r = mii_ethtool_set_link_ksettings(&lp->mii_अगर, cmd);
	पूर्ण अन्यथा अगर (lp->chip_version == PCNET32_79C970A) अणु
		suspended = pcnet32_suspend(dev, &flags, 0);
		अगर (!suspended)
			lp->a->ग_लिखो_csr(ioaddr, CSR0, CSR0_STOP);

		lp->स्वतःneg = cmd->base.स्वतःneg == AUTONEG_ENABLE;
		bcr2 = lp->a->पढ़ो_bcr(ioaddr, 2);
		अगर (cmd->base.स्वतःneg == AUTONEG_ENABLE) अणु
			lp->a->ग_लिखो_bcr(ioaddr, 2, bcr2 | 0x0002);
		पूर्ण अन्यथा अणु
			lp->a->ग_लिखो_bcr(ioaddr, 2, bcr2 & ~0x0002);

			lp->port_tp = cmd->base.port == PORT_TP;
			csr15 = lp->a->पढ़ो_csr(ioaddr, CSR15) & ~0x0180;
			अगर (cmd->base.port == PORT_TP)
				csr15 |= 0x0080;
			lp->a->ग_लिखो_csr(ioaddr, CSR15, csr15);
			lp->init_block->mode = cpu_to_le16(csr15);

			lp->fdx = cmd->base.duplex == DUPLEX_FULL;
			bcr9 = lp->a->पढ़ो_bcr(ioaddr, 9) & ~0x0003;
			अगर (cmd->base.duplex == DUPLEX_FULL)
				bcr9 |= 0x0003;
			lp->a->ग_लिखो_bcr(ioaddr, 9, bcr9);
		पूर्ण
		अगर (suspended)
			pcnet32_clr_suspend(lp, ioaddr);
		अन्यथा अगर (netअगर_running(dev))
			pcnet32_restart(dev, CSR0_NORMAL);
		r = 0;
	पूर्ण
	spin_unlock_irqrestore(&lp->lock, flags);
	वापस r;
पूर्ण

अटल व्योम pcnet32_get_drvinfo(काष्ठा net_device *dev,
				काष्ठा ethtool_drvinfo *info)
अणु
	काष्ठा pcnet32_निजी *lp = netdev_priv(dev);

	strlcpy(info->driver, DRV_NAME, माप(info->driver));
	अगर (lp->pci_dev)
		strlcpy(info->bus_info, pci_name(lp->pci_dev),
			माप(info->bus_info));
	अन्यथा
		snम_लिखो(info->bus_info, माप(info->bus_info),
			"VLB 0x%lx", dev->base_addr);
पूर्ण

अटल u32 pcnet32_get_link(काष्ठा net_device *dev)
अणु
	काष्ठा pcnet32_निजी *lp = netdev_priv(dev);
	अचिन्हित दीर्घ flags;
	पूर्णांक r;

	spin_lock_irqsave(&lp->lock, flags);
	अगर (lp->mii) अणु
		r = mii_link_ok(&lp->mii_अगर);
	पूर्ण अन्यथा अगर (lp->chip_version == PCNET32_79C970A) अणु
		uदीर्घ ioaddr = dev->base_addr;	/* card base I/O address */
		/* only पढ़ो link अगर port is set to TP */
		अगर (!lp->स्वतःneg && lp->port_tp)
			r = (lp->a->पढ़ो_bcr(ioaddr, 4) != 0xc0);
		अन्यथा /* link always up क्रम AUI port or port स्वतः select */
			r = 1;
	पूर्ण अन्यथा अगर (lp->chip_version > PCNET32_79C970A) अणु
		uदीर्घ ioaddr = dev->base_addr;	/* card base I/O address */
		r = (lp->a->पढ़ो_bcr(ioaddr, 4) != 0xc0);
	पूर्ण अन्यथा अणु	/* can not detect link on really old chips */
		r = 1;
	पूर्ण
	spin_unlock_irqrestore(&lp->lock, flags);

	वापस r;
पूर्ण

अटल u32 pcnet32_get_msglevel(काष्ठा net_device *dev)
अणु
	काष्ठा pcnet32_निजी *lp = netdev_priv(dev);
	वापस lp->msg_enable;
पूर्ण

अटल व्योम pcnet32_set_msglevel(काष्ठा net_device *dev, u32 value)
अणु
	काष्ठा pcnet32_निजी *lp = netdev_priv(dev);
	lp->msg_enable = value;
पूर्ण

अटल पूर्णांक pcnet32_nway_reset(काष्ठा net_device *dev)
अणु
	काष्ठा pcnet32_निजी *lp = netdev_priv(dev);
	अचिन्हित दीर्घ flags;
	पूर्णांक r = -EOPNOTSUPP;

	अगर (lp->mii) अणु
		spin_lock_irqsave(&lp->lock, flags);
		r = mii_nway_restart(&lp->mii_अगर);
		spin_unlock_irqrestore(&lp->lock, flags);
	पूर्ण
	वापस r;
पूर्ण

अटल व्योम pcnet32_get_ringparam(काष्ठा net_device *dev,
				  काष्ठा ethtool_ringparam *ering)
अणु
	काष्ठा pcnet32_निजी *lp = netdev_priv(dev);

	ering->tx_max_pending = TX_MAX_RING_SIZE;
	ering->tx_pending = lp->tx_ring_size;
	ering->rx_max_pending = RX_MAX_RING_SIZE;
	ering->rx_pending = lp->rx_ring_size;
पूर्ण

अटल पूर्णांक pcnet32_set_ringparam(काष्ठा net_device *dev,
				 काष्ठा ethtool_ringparam *ering)
अणु
	काष्ठा pcnet32_निजी *lp = netdev_priv(dev);
	अचिन्हित दीर्घ flags;
	अचिन्हित पूर्णांक size;
	uदीर्घ ioaddr = dev->base_addr;
	पूर्णांक i;

	अगर (ering->rx_mini_pending || ering->rx_jumbo_pending)
		वापस -EINVAL;

	अगर (netअगर_running(dev))
		pcnet32_netअगर_stop(dev);

	spin_lock_irqsave(&lp->lock, flags);
	lp->a->ग_लिखो_csr(ioaddr, CSR0, CSR0_STOP);	/* stop the chip */

	size = min(ering->tx_pending, (अचिन्हित पूर्णांक)TX_MAX_RING_SIZE);

	/* set the minimum ring size to 4, to allow the loopback test to work
	 * unchanged.
	 */
	क्रम (i = 2; i <= PCNET32_LOG_MAX_TX_BUFFERS; i++) अणु
		अगर (size <= (1 << i))
			अवरोध;
	पूर्ण
	अगर ((1 << i) != lp->tx_ring_size)
		pcnet32_पुनः_स्मृति_tx_ring(dev, lp, i);

	size = min(ering->rx_pending, (अचिन्हित पूर्णांक)RX_MAX_RING_SIZE);
	क्रम (i = 2; i <= PCNET32_LOG_MAX_RX_BUFFERS; i++) अणु
		अगर (size <= (1 << i))
			अवरोध;
	पूर्ण
	अगर ((1 << i) != lp->rx_ring_size)
		pcnet32_पुनः_स्मृति_rx_ring(dev, lp, i);

	lp->napi.weight = lp->rx_ring_size / 2;

	अगर (netअगर_running(dev)) अणु
		pcnet32_netअगर_start(dev);
		pcnet32_restart(dev, CSR0_NORMAL);
	पूर्ण

	spin_unlock_irqrestore(&lp->lock, flags);

	netअगर_info(lp, drv, dev, "Ring Param Settings: RX: %d, TX: %d\n",
		   lp->rx_ring_size, lp->tx_ring_size);

	वापस 0;
पूर्ण

अटल व्योम pcnet32_get_strings(काष्ठा net_device *dev, u32 stringset,
				u8 *data)
अणु
	स_नकल(data, pcnet32_gstrings_test, माप(pcnet32_gstrings_test));
पूर्ण

अटल पूर्णांक pcnet32_get_sset_count(काष्ठा net_device *dev, पूर्णांक sset)
अणु
	चयन (sset) अणु
	हाल ETH_SS_TEST:
		वापस PCNET32_TEST_LEN;
	शेष:
		वापस -EOPNOTSUPP;
	पूर्ण
पूर्ण

अटल व्योम pcnet32_ethtool_test(काष्ठा net_device *dev,
				 काष्ठा ethtool_test *test, u64 * data)
अणु
	काष्ठा pcnet32_निजी *lp = netdev_priv(dev);
	पूर्णांक rc;

	अगर (test->flags == ETH_TEST_FL_OFFLINE) अणु
		rc = pcnet32_loopback_test(dev, data);
		अगर (rc) अणु
			netअगर_prपूर्णांकk(lp, hw, KERN_DEBUG, dev,
				     "Loopback test failed\n");
			test->flags |= ETH_TEST_FL_FAILED;
		पूर्ण अन्यथा
			netअगर_prपूर्णांकk(lp, hw, KERN_DEBUG, dev,
				     "Loopback test passed\n");
	पूर्ण अन्यथा
		netअगर_prपूर्णांकk(lp, hw, KERN_DEBUG, dev,
			     "No tests to run (specify 'Offline' on ethtool)\n");
पूर्ण				/* end pcnet32_ethtool_test */

अटल पूर्णांक pcnet32_loopback_test(काष्ठा net_device *dev, uपूर्णांक64_t * data1)
अणु
	काष्ठा pcnet32_निजी *lp = netdev_priv(dev);
	स्थिर काष्ठा pcnet32_access *a = lp->a;	/* access to रेजिस्टरs */
	uदीर्घ ioaddr = dev->base_addr;	/* card base I/O address */
	काष्ठा sk_buff *skb;	/* sk buff */
	पूर्णांक x, i;		/* counters */
	पूर्णांक numbuffs = 4;	/* number of TX/RX buffers and descs */
	u16 status = 0x8300;	/* TX ring status */
	__le16 teststatus;	/* test of ring status */
	पूर्णांक rc;			/* वापस code */
	पूर्णांक size;		/* size of packets */
	अचिन्हित अक्षर *packet;	/* source packet data */
	अटल स्थिर पूर्णांक data_len = 60;	/* length of source packets */
	अचिन्हित दीर्घ flags;
	अचिन्हित दीर्घ ticks;

	rc = 1;			/* शेष to fail */

	अगर (netअगर_running(dev))
		pcnet32_netअगर_stop(dev);

	spin_lock_irqsave(&lp->lock, flags);
	lp->a->ग_लिखो_csr(ioaddr, CSR0, CSR0_STOP);	/* stop the chip */

	numbuffs = min(numbuffs, (पूर्णांक)min(lp->rx_ring_size, lp->tx_ring_size));

	/* Reset the PCNET32 */
	lp->a->reset(ioaddr);
	lp->a->ग_लिखो_csr(ioaddr, CSR4, 0x0915);	/* स्वतः tx pad */

	/* चयन pcnet32 to 32bit mode */
	lp->a->ग_लिखो_bcr(ioaddr, 20, 2);

	/* purge & init rings but करोn't actually restart */
	pcnet32_restart(dev, 0x0000);

	lp->a->ग_लिखो_csr(ioaddr, CSR0, CSR0_STOP);	/* Set STOP bit */

	/* Initialize Transmit buffers. */
	size = data_len + 15;
	क्रम (x = 0; x < numbuffs; x++) अणु
		skb = netdev_alloc_skb(dev, size);
		अगर (!skb) अणु
			netअगर_prपूर्णांकk(lp, hw, KERN_DEBUG, dev,
				     "Cannot allocate skb at line: %d!\n",
				     __LINE__);
			जाओ clean_up;
		पूर्ण
		packet = skb->data;
		skb_put(skb, size);	/* create space क्रम data */
		lp->tx_skbuff[x] = skb;
		lp->tx_ring[x].length = cpu_to_le16(-skb->len);
		lp->tx_ring[x].misc = 0;

		/* put DA and SA पूर्णांकo the skb */
		क्रम (i = 0; i < 6; i++)
			*packet++ = dev->dev_addr[i];
		क्रम (i = 0; i < 6; i++)
			*packet++ = dev->dev_addr[i];
		/* type */
		*packet++ = 0x08;
		*packet++ = 0x06;
		/* packet number */
		*packet++ = x;
		/* fill packet with data */
		क्रम (i = 0; i < data_len; i++)
			*packet++ = i;

		lp->tx_dma_addr[x] =
			dma_map_single(&lp->pci_dev->dev, skb->data, skb->len,
				       DMA_TO_DEVICE);
		अगर (dma_mapping_error(&lp->pci_dev->dev, lp->tx_dma_addr[x])) अणु
			netअगर_prपूर्णांकk(lp, hw, KERN_DEBUG, dev,
				     "DMA mapping error at line: %d!\n",
				     __LINE__);
			जाओ clean_up;
		पूर्ण
		lp->tx_ring[x].base = cpu_to_le32(lp->tx_dma_addr[x]);
		wmb();	/* Make sure owner changes after all others are visible */
		lp->tx_ring[x].status = cpu_to_le16(status);
	पूर्ण

	x = a->पढ़ो_bcr(ioaddr, 32);	/* set पूर्णांकernal loopback in BCR32 */
	a->ग_लिखो_bcr(ioaddr, 32, x | 0x0002);

	/* set पूर्णांक loopback in CSR15 */
	x = a->पढ़ो_csr(ioaddr, CSR15) & 0xfffc;
	lp->a->ग_लिखो_csr(ioaddr, CSR15, x | 0x0044);

	teststatus = cpu_to_le16(0x8000);
	lp->a->ग_लिखो_csr(ioaddr, CSR0, CSR0_START);	/* Set STRT bit */

	/* Check status of descriptors */
	क्रम (x = 0; x < numbuffs; x++) अणु
		ticks = 0;
		rmb();
		जबतक ((lp->rx_ring[x].status & teststatus) && (ticks < 200)) अणु
			spin_unlock_irqrestore(&lp->lock, flags);
			msleep(1);
			spin_lock_irqsave(&lp->lock, flags);
			rmb();
			ticks++;
		पूर्ण
		अगर (ticks == 200) अणु
			netअगर_err(lp, hw, dev, "Desc %d failed to reset!\n", x);
			अवरोध;
		पूर्ण
	पूर्ण

	lp->a->ग_लिखो_csr(ioaddr, CSR0, CSR0_STOP);	/* Set STOP bit */
	wmb();
	अगर (netअगर_msg_hw(lp) && netअगर_msg_pktdata(lp)) अणु
		netdev_prपूर्णांकk(KERN_DEBUG, dev, "RX loopback packets:\n");

		क्रम (x = 0; x < numbuffs; x++) अणु
			netdev_prपूर्णांकk(KERN_DEBUG, dev, "Packet %d: ", x);
			skb = lp->rx_skbuff[x];
			क्रम (i = 0; i < size; i++)
				pr_cont(" %02x", *(skb->data + i));
			pr_cont("\n");
		पूर्ण
	पूर्ण

	x = 0;
	rc = 0;
	जबतक (x < numbuffs && !rc) अणु
		skb = lp->rx_skbuff[x];
		packet = lp->tx_skbuff[x]->data;
		क्रम (i = 0; i < size; i++) अणु
			अगर (*(skb->data + i) != packet[i]) अणु
				netअगर_prपूर्णांकk(lp, hw, KERN_DEBUG, dev,
					     "Error in compare! %2x - %02x %02x\n",
					     i, *(skb->data + i), packet[i]);
				rc = 1;
				अवरोध;
			पूर्ण
		पूर्ण
		x++;
	पूर्ण

clean_up:
	*data1 = rc;
	pcnet32_purge_tx_ring(dev);

	x = a->पढ़ो_csr(ioaddr, CSR15);
	a->ग_लिखो_csr(ioaddr, CSR15, (x & ~0x0044));	/* reset bits 6 and 2 */

	x = a->पढ़ो_bcr(ioaddr, 32);	/* reset पूर्णांकernal loopback */
	a->ग_लिखो_bcr(ioaddr, 32, (x & ~0x0002));

	अगर (netअगर_running(dev)) अणु
		pcnet32_netअगर_start(dev);
		pcnet32_restart(dev, CSR0_NORMAL);
	पूर्ण अन्यथा अणु
		pcnet32_purge_rx_ring(dev);
		lp->a->ग_लिखो_bcr(ioaddr, 20, 4);	/* वापस to 16bit mode */
	पूर्ण
	spin_unlock_irqrestore(&lp->lock, flags);

	वापस rc;
पूर्ण				/* end pcnet32_loopback_test  */

अटल पूर्णांक pcnet32_set_phys_id(काष्ठा net_device *dev,
			       क्रमागत ethtool_phys_id_state state)
अणु
	काष्ठा pcnet32_निजी *lp = netdev_priv(dev);
	स्थिर काष्ठा pcnet32_access *a = lp->a;
	uदीर्घ ioaddr = dev->base_addr;
	अचिन्हित दीर्घ flags;
	पूर्णांक i;

	चयन (state) अणु
	हाल ETHTOOL_ID_ACTIVE:
		/* Save the current value of the bcrs */
		spin_lock_irqsave(&lp->lock, flags);
		क्रम (i = 4; i < 8; i++)
			lp->save_regs[i - 4] = a->पढ़ो_bcr(ioaddr, i);
		spin_unlock_irqrestore(&lp->lock, flags);
		वापस 2;	/* cycle on/off twice per second */

	हाल ETHTOOL_ID_ON:
	हाल ETHTOOL_ID_OFF:
		/* Blink the led */
		spin_lock_irqsave(&lp->lock, flags);
		क्रम (i = 4; i < 8; i++)
			a->ग_लिखो_bcr(ioaddr, i, a->पढ़ो_bcr(ioaddr, i) ^ 0x4000);
		spin_unlock_irqrestore(&lp->lock, flags);
		अवरोध;

	हाल ETHTOOL_ID_INACTIVE:
		/* Restore the original value of the bcrs */
		spin_lock_irqsave(&lp->lock, flags);
		क्रम (i = 4; i < 8; i++)
			a->ग_लिखो_bcr(ioaddr, i, lp->save_regs[i - 4]);
		spin_unlock_irqrestore(&lp->lock, flags);
	पूर्ण
	वापस 0;
पूर्ण

/*
 * process one receive descriptor entry
 */

अटल व्योम pcnet32_rx_entry(काष्ठा net_device *dev,
			     काष्ठा pcnet32_निजी *lp,
			     काष्ठा pcnet32_rx_head *rxp,
			     पूर्णांक entry)
अणु
	पूर्णांक status = (लघु)le16_to_cpu(rxp->status) >> 8;
	पूर्णांक rx_in_place = 0;
	काष्ठा sk_buff *skb;
	लघु pkt_len;

	अगर (status != 0x03) अणु	/* There was an error. */
		/*
		 * There is a tricky error noted by John Murphy,
		 * <murf@perftech.com> to Russ Nelson: Even with full-sized
		 * buffers it's possible क्रम a jabber packet to use two
		 * buffers, with only the last correctly noting the error.
		 */
		अगर (status & 0x01)	/* Only count a general error at the */
			dev->stats.rx_errors++;	/* end of a packet. */
		अगर (status & 0x20)
			dev->stats.rx_frame_errors++;
		अगर (status & 0x10)
			dev->stats.rx_over_errors++;
		अगर (status & 0x08)
			dev->stats.rx_crc_errors++;
		अगर (status & 0x04)
			dev->stats.rx_fअगरo_errors++;
		वापस;
	पूर्ण

	pkt_len = (le32_to_cpu(rxp->msg_length) & 0xfff) - 4;

	/* Discard oversize frames. */
	अगर (unlikely(pkt_len > PKT_BUF_SIZE)) अणु
		netअगर_err(lp, drv, dev, "Impossible packet size %d!\n",
			  pkt_len);
		dev->stats.rx_errors++;
		वापस;
	पूर्ण
	अगर (pkt_len < 60) अणु
		netअगर_err(lp, rx_err, dev, "Runt packet!\n");
		dev->stats.rx_errors++;
		वापस;
	पूर्ण

	अगर (pkt_len > rx_copyअवरोध) अणु
		काष्ठा sk_buff *newskb;
		dma_addr_t new_dma_addr;

		newskb = netdev_alloc_skb(dev, PKT_BUF_SKB);
		/*
		 * map the new buffer, अगर mapping fails, drop the packet and
		 * reuse the old buffer
		 */
		अगर (newskb) अणु
			skb_reserve(newskb, NET_IP_ALIGN);
			new_dma_addr = dma_map_single(&lp->pci_dev->dev,
						      newskb->data,
						      PKT_BUF_SIZE,
						      DMA_FROM_DEVICE);
			अगर (dma_mapping_error(&lp->pci_dev->dev, new_dma_addr)) अणु
				netअगर_err(lp, rx_err, dev,
					  "DMA mapping error.\n");
				dev_kमुक्त_skb(newskb);
				skb = शून्य;
			पूर्ण अन्यथा अणु
				skb = lp->rx_skbuff[entry];
				dma_unmap_single(&lp->pci_dev->dev,
						 lp->rx_dma_addr[entry],
						 PKT_BUF_SIZE,
						 DMA_FROM_DEVICE);
				skb_put(skb, pkt_len);
				lp->rx_skbuff[entry] = newskb;
				lp->rx_dma_addr[entry] = new_dma_addr;
				rxp->base = cpu_to_le32(new_dma_addr);
				rx_in_place = 1;
			पूर्ण
		पूर्ण अन्यथा
			skb = शून्य;
	पूर्ण अन्यथा
		skb = netdev_alloc_skb(dev, pkt_len + NET_IP_ALIGN);

	अगर (skb == शून्य) अणु
		dev->stats.rx_dropped++;
		वापस;
	पूर्ण
	अगर (!rx_in_place) अणु
		skb_reserve(skb, NET_IP_ALIGN);
		skb_put(skb, pkt_len);	/* Make room */
		dma_sync_single_क्रम_cpu(&lp->pci_dev->dev,
					lp->rx_dma_addr[entry], pkt_len,
					DMA_FROM_DEVICE);
		skb_copy_to_linear_data(skb,
				 (अचिन्हित अक्षर *)(lp->rx_skbuff[entry]->data),
				 pkt_len);
		dma_sync_single_क्रम_device(&lp->pci_dev->dev,
					   lp->rx_dma_addr[entry], pkt_len,
					   DMA_FROM_DEVICE);
	पूर्ण
	dev->stats.rx_bytes += skb->len;
	skb->protocol = eth_type_trans(skb, dev);
	netअगर_receive_skb(skb);
	dev->stats.rx_packets++;
पूर्ण

अटल पूर्णांक pcnet32_rx(काष्ठा net_device *dev, पूर्णांक budget)
अणु
	काष्ठा pcnet32_निजी *lp = netdev_priv(dev);
	पूर्णांक entry = lp->cur_rx & lp->rx_mod_mask;
	काष्ठा pcnet32_rx_head *rxp = &lp->rx_ring[entry];
	पूर्णांक npackets = 0;

	/* If we own the next entry, it's a new packet. Send it up. */
	जबतक (npackets < budget && (लघु)le16_to_cpu(rxp->status) >= 0) अणु
		pcnet32_rx_entry(dev, lp, rxp, entry);
		npackets += 1;
		/*
		 * The करोcs say that the buffer length isn't touched, but Andrew
		 * Boyd of QNX reports that some revs of the 79C965 clear it.
		 */
		rxp->buf_length = cpu_to_le16(NEG_BUF_SIZE);
		wmb();	/* Make sure owner changes after others are visible */
		rxp->status = cpu_to_le16(0x8000);
		entry = (++lp->cur_rx) & lp->rx_mod_mask;
		rxp = &lp->rx_ring[entry];
	पूर्ण

	वापस npackets;
पूर्ण

अटल पूर्णांक pcnet32_tx(काष्ठा net_device *dev)
अणु
	काष्ठा pcnet32_निजी *lp = netdev_priv(dev);
	अचिन्हित पूर्णांक dirty_tx = lp->dirty_tx;
	पूर्णांक delta;
	पूर्णांक must_restart = 0;

	जबतक (dirty_tx != lp->cur_tx) अणु
		पूर्णांक entry = dirty_tx & lp->tx_mod_mask;
		पूर्णांक status = (लघु)le16_to_cpu(lp->tx_ring[entry].status);

		अगर (status < 0)
			अवरोध;	/* It still hasn't been Txed */

		lp->tx_ring[entry].base = 0;

		अगर (status & 0x4000) अणु
			/* There was a major error, log it. */
			पूर्णांक err_status = le32_to_cpu(lp->tx_ring[entry].misc);
			dev->stats.tx_errors++;
			netअगर_err(lp, tx_err, dev,
				  "Tx error status=%04x err_status=%08x\n",
				  status, err_status);
			अगर (err_status & 0x04000000)
				dev->stats.tx_पातed_errors++;
			अगर (err_status & 0x08000000)
				dev->stats.tx_carrier_errors++;
			अगर (err_status & 0x10000000)
				dev->stats.tx_winकरोw_errors++;
#अगर_अघोषित DO_DXSUFLO
			अगर (err_status & 0x40000000) अणु
				dev->stats.tx_fअगरo_errors++;
				/* Ackk!  On FIFO errors the Tx unit is turned off! */
				/* Remove this verbosity later! */
				netअगर_err(lp, tx_err, dev, "Tx FIFO error!\n");
				must_restart = 1;
			पूर्ण
#अन्यथा
			अगर (err_status & 0x40000000) अणु
				dev->stats.tx_fअगरo_errors++;
				अगर (!lp->dxsuflo) अणु	/* If controller करोesn't recover ... */
					/* Ackk!  On FIFO errors the Tx unit is turned off! */
					/* Remove this verbosity later! */
					netअगर_err(lp, tx_err, dev, "Tx FIFO error!\n");
					must_restart = 1;
				पूर्ण
			पूर्ण
#पूर्ण_अगर
		पूर्ण अन्यथा अणु
			अगर (status & 0x1800)
				dev->stats.collisions++;
			dev->stats.tx_packets++;
		पूर्ण

		/* We must मुक्त the original skb */
		अगर (lp->tx_skbuff[entry]) अणु
			dma_unmap_single(&lp->pci_dev->dev,
					 lp->tx_dma_addr[entry],
					 lp->tx_skbuff[entry]->len,
					 DMA_TO_DEVICE);
			dev_kमुक्त_skb_any(lp->tx_skbuff[entry]);
			lp->tx_skbuff[entry] = शून्य;
			lp->tx_dma_addr[entry] = 0;
		पूर्ण
		dirty_tx++;
	पूर्ण

	delta = (lp->cur_tx - dirty_tx) & (lp->tx_mod_mask + lp->tx_ring_size);
	अगर (delta > lp->tx_ring_size) अणु
		netअगर_err(lp, drv, dev, "out-of-sync dirty pointer, %d vs. %d, full=%d\n",
			  dirty_tx, lp->cur_tx, lp->tx_full);
		dirty_tx += lp->tx_ring_size;
		delta -= lp->tx_ring_size;
	पूर्ण

	अगर (lp->tx_full &&
	    netअगर_queue_stopped(dev) &&
	    delta < lp->tx_ring_size - 2) अणु
		/* The ring is no दीर्घer full, clear tbusy. */
		lp->tx_full = 0;
		netअगर_wake_queue(dev);
	पूर्ण
	lp->dirty_tx = dirty_tx;

	वापस must_restart;
पूर्ण

अटल पूर्णांक pcnet32_poll(काष्ठा napi_काष्ठा *napi, पूर्णांक budget)
अणु
	काष्ठा pcnet32_निजी *lp = container_of(napi, काष्ठा pcnet32_निजी, napi);
	काष्ठा net_device *dev = lp->dev;
	अचिन्हित दीर्घ ioaddr = dev->base_addr;
	अचिन्हित दीर्घ flags;
	पूर्णांक work_करोne;
	u16 val;

	work_करोne = pcnet32_rx(dev, budget);

	spin_lock_irqsave(&lp->lock, flags);
	अगर (pcnet32_tx(dev)) अणु
		/* reset the chip to clear the error condition, then restart */
		lp->a->reset(ioaddr);
		lp->a->ग_लिखो_csr(ioaddr, CSR4, 0x0915);	/* स्वतः tx pad */
		pcnet32_restart(dev, CSR0_START);
		netअगर_wake_queue(dev);
	पूर्ण

	अगर (work_करोne < budget && napi_complete_करोne(napi, work_करोne)) अणु
		/* clear पूर्णांकerrupt masks */
		val = lp->a->पढ़ो_csr(ioaddr, CSR3);
		val &= 0x00ff;
		lp->a->ग_लिखो_csr(ioaddr, CSR3, val);

		/* Set पूर्णांकerrupt enable. */
		lp->a->ग_लिखो_csr(ioaddr, CSR0, CSR0_INTEN);
	पूर्ण

	spin_unlock_irqrestore(&lp->lock, flags);
	वापस work_करोne;
पूर्ण

#घोषणा PCNET32_REGS_PER_PHY	32
#घोषणा PCNET32_MAX_PHYS	32
अटल पूर्णांक pcnet32_get_regs_len(काष्ठा net_device *dev)
अणु
	काष्ठा pcnet32_निजी *lp = netdev_priv(dev);
	पूर्णांक j = lp->phycount * PCNET32_REGS_PER_PHY;

	वापस (PCNET32_NUM_REGS + j) * माप(u16);
पूर्ण

अटल व्योम pcnet32_get_regs(काष्ठा net_device *dev, काष्ठा ethtool_regs *regs,
			     व्योम *ptr)
अणु
	पूर्णांक i, csr0;
	u16 *buff = ptr;
	काष्ठा pcnet32_निजी *lp = netdev_priv(dev);
	स्थिर काष्ठा pcnet32_access *a = lp->a;
	uदीर्घ ioaddr = dev->base_addr;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&lp->lock, flags);

	csr0 = a->पढ़ो_csr(ioaddr, CSR0);
	अगर (!(csr0 & CSR0_STOP))	/* If not stopped */
		pcnet32_suspend(dev, &flags, 1);

	/* पढ़ो address PROM */
	क्रम (i = 0; i < 16; i += 2)
		*buff++ = inw(ioaddr + i);

	/* पढ़ो control and status रेजिस्टरs */
	क्रम (i = 0; i < 90; i++)
		*buff++ = a->पढ़ो_csr(ioaddr, i);

	*buff++ = a->पढ़ो_csr(ioaddr, 112);
	*buff++ = a->पढ़ो_csr(ioaddr, 114);

	/* पढ़ो bus configuration रेजिस्टरs */
	क्रम (i = 0; i < 30; i++)
		*buff++ = a->पढ़ो_bcr(ioaddr, i);

	*buff++ = 0;		/* skip bcr30 so as not to hang 79C976 */

	क्रम (i = 31; i < 36; i++)
		*buff++ = a->पढ़ो_bcr(ioaddr, i);

	/* पढ़ो mii phy रेजिस्टरs */
	अगर (lp->mii) अणु
		पूर्णांक j;
		क्रम (j = 0; j < PCNET32_MAX_PHYS; j++) अणु
			अगर (lp->phymask & (1 << j)) अणु
				क्रम (i = 0; i < PCNET32_REGS_PER_PHY; i++) अणु
					lp->a->ग_लिखो_bcr(ioaddr, 33,
							(j << 5) | i);
					*buff++ = lp->a->पढ़ो_bcr(ioaddr, 34);
				पूर्ण
			पूर्ण
		पूर्ण
	पूर्ण

	अगर (!(csr0 & CSR0_STOP))	/* If not stopped */
		pcnet32_clr_suspend(lp, ioaddr);

	spin_unlock_irqrestore(&lp->lock, flags);
पूर्ण

अटल स्थिर काष्ठा ethtool_ops pcnet32_ethtool_ops = अणु
	.get_drvinfo		= pcnet32_get_drvinfo,
	.get_msglevel		= pcnet32_get_msglevel,
	.set_msglevel		= pcnet32_set_msglevel,
	.nway_reset		= pcnet32_nway_reset,
	.get_link		= pcnet32_get_link,
	.get_ringparam		= pcnet32_get_ringparam,
	.set_ringparam		= pcnet32_set_ringparam,
	.get_strings		= pcnet32_get_strings,
	.self_test		= pcnet32_ethtool_test,
	.set_phys_id		= pcnet32_set_phys_id,
	.get_regs_len		= pcnet32_get_regs_len,
	.get_regs		= pcnet32_get_regs,
	.get_sset_count		= pcnet32_get_sset_count,
	.get_link_ksettings	= pcnet32_get_link_ksettings,
	.set_link_ksettings	= pcnet32_set_link_ksettings,
पूर्ण;

/* only probes क्रम non-PCI devices, the rest are handled by
 * pci_रेजिस्टर_driver via pcnet32_probe_pci */

अटल व्योम pcnet32_probe_vlbus(अचिन्हित पूर्णांक *pcnet32_portlist)
अणु
	अचिन्हित पूर्णांक *port, ioaddr;

	/* search क्रम PCnet32 VLB cards at known addresses */
	क्रम (port = pcnet32_portlist; (ioaddr = *port); port++) अणु
		अगर (request_region
		    (ioaddr, PCNET32_TOTAL_SIZE, "pcnet32_probe_vlbus")) अणु
			/* check अगर there is really a pcnet chip on that ioaddr */
			अगर ((inb(ioaddr + 14) == 0x57) &&
			    (inb(ioaddr + 15) == 0x57)) अणु
				pcnet32_probe1(ioaddr, 0, शून्य);
			पूर्ण अन्यथा अणु
				release_region(ioaddr, PCNET32_TOTAL_SIZE);
			पूर्ण
		पूर्ण
	पूर्ण
पूर्ण

अटल पूर्णांक
pcnet32_probe_pci(काष्ठा pci_dev *pdev, स्थिर काष्ठा pci_device_id *ent)
अणु
	अचिन्हित दीर्घ ioaddr;
	पूर्णांक err;

	err = pci_enable_device(pdev);
	अगर (err < 0) अणु
		अगर (pcnet32_debug & NETIF_MSG_PROBE)
			pr_err("failed to enable device -- err=%d\n", err);
		वापस err;
	पूर्ण
	pci_set_master(pdev);

	अगर (!pci_resource_len(pdev, 0)) अणु
		अगर (pcnet32_debug & NETIF_MSG_PROBE)
			pr_err("card has no PCI IO resources, aborting\n");
		err = -ENODEV;
		जाओ err_disable_dev;
	पूर्ण

	err = dma_set_mask(&pdev->dev, PCNET32_DMA_MASK);
	अगर (err) अणु
		अगर (pcnet32_debug & NETIF_MSG_PROBE)
			pr_err("architecture does not support 32bit PCI busmaster DMA\n");
		जाओ err_disable_dev;
	पूर्ण

	ioaddr = pci_resource_start(pdev, 0);
	अगर (!request_region(ioaddr, PCNET32_TOTAL_SIZE, "pcnet32_probe_pci")) अणु
		अगर (pcnet32_debug & NETIF_MSG_PROBE)
			pr_err("io address range already allocated\n");
		err = -EBUSY;
		जाओ err_disable_dev;
	पूर्ण

	err = pcnet32_probe1(ioaddr, 1, pdev);

err_disable_dev:
	अगर (err < 0)
		pci_disable_device(pdev);

	वापस err;
पूर्ण

अटल स्थिर काष्ठा net_device_ops pcnet32_netdev_ops = अणु
	.nकरो_खोलो		= pcnet32_खोलो,
	.nकरो_stop 		= pcnet32_बंद,
	.nकरो_start_xmit		= pcnet32_start_xmit,
	.nकरो_tx_समयout		= pcnet32_tx_समयout,
	.nकरो_get_stats		= pcnet32_get_stats,
	.nकरो_set_rx_mode	= pcnet32_set_multicast_list,
	.nकरो_करो_ioctl		= pcnet32_ioctl,
	.nकरो_set_mac_address 	= eth_mac_addr,
	.nकरो_validate_addr	= eth_validate_addr,
#अगर_घोषित CONFIG_NET_POLL_CONTROLLER
	.nकरो_poll_controller	= pcnet32_poll_controller,
#पूर्ण_अगर
पूर्ण;

/* pcnet32_probe1
 *  Called from both pcnet32_probe_vlbus and pcnet_probe_pci.
 *  pdev will be शून्य when called from pcnet32_probe_vlbus.
 */
अटल पूर्णांक
pcnet32_probe1(अचिन्हित दीर्घ ioaddr, पूर्णांक shared, काष्ठा pci_dev *pdev)
अणु
	काष्ठा pcnet32_निजी *lp;
	पूर्णांक i, media;
	पूर्णांक fdx, mii, fset, dxsuflo, sram;
	पूर्णांक chip_version;
	अक्षर *chipname;
	काष्ठा net_device *dev;
	स्थिर काष्ठा pcnet32_access *a = शून्य;
	u8 promaddr[ETH_ALEN];
	पूर्णांक ret = -ENODEV;

	/* reset the chip */
	pcnet32_wio_reset(ioaddr);

	/* NOTE: 16-bit check is first, otherwise some older PCnet chips fail */
	अगर (pcnet32_wio_पढ़ो_csr(ioaddr, 0) == 4 && pcnet32_wio_check(ioaddr)) अणु
		a = &pcnet32_wio;
	पूर्ण अन्यथा अणु
		pcnet32_dwio_reset(ioaddr);
		अगर (pcnet32_dwio_पढ़ो_csr(ioaddr, 0) == 4 &&
		    pcnet32_dwio_check(ioaddr)) अणु
			a = &pcnet32_dwio;
		पूर्ण अन्यथा अणु
			अगर (pcnet32_debug & NETIF_MSG_PROBE)
				pr_err("No access methods\n");
			जाओ err_release_region;
		पूर्ण
	पूर्ण

	chip_version =
	    a->पढ़ो_csr(ioaddr, 88) | (a->पढ़ो_csr(ioaddr, 89) << 16);
	अगर ((pcnet32_debug & NETIF_MSG_PROBE) && (pcnet32_debug & NETIF_MSG_HW))
		pr_info("  PCnet chip version is %#x\n", chip_version);
	अगर ((chip_version & 0xfff) != 0x003) अणु
		अगर (pcnet32_debug & NETIF_MSG_PROBE)
			pr_info("Unsupported chip version\n");
		जाओ err_release_region;
	पूर्ण

	/* initialize variables */
	fdx = mii = fset = dxsuflo = sram = 0;
	chip_version = (chip_version >> 12) & 0xffff;

	चयन (chip_version) अणु
	हाल 0x2420:
		chipname = "PCnet/PCI 79C970";	/* PCI */
		अवरोध;
	हाल 0x2430:
		अगर (shared)
			chipname = "PCnet/PCI 79C970";	/* 970 gives the wrong chip id back */
		अन्यथा
			chipname = "PCnet/32 79C965";	/* 486/VL bus */
		अवरोध;
	हाल 0x2621:
		chipname = "PCnet/PCI II 79C970A";	/* PCI */
		fdx = 1;
		अवरोध;
	हाल 0x2623:
		chipname = "PCnet/FAST 79C971";	/* PCI */
		fdx = 1;
		mii = 1;
		fset = 1;
		अवरोध;
	हाल 0x2624:
		chipname = "PCnet/FAST+ 79C972";	/* PCI */
		fdx = 1;
		mii = 1;
		fset = 1;
		अवरोध;
	हाल 0x2625:
		chipname = "PCnet/FAST III 79C973";	/* PCI */
		fdx = 1;
		mii = 1;
		sram = 1;
		अवरोध;
	हाल 0x2626:
		chipname = "PCnet/Home 79C978";	/* PCI */
		fdx = 1;
		/*
		 * This is based on specs published at www.amd.com.  This section
		 * assumes that a card with a 79C978 wants to go पूर्णांकo standard
		 * ethernet mode.  The 79C978 can also go पूर्णांकo 1Mb HomePNA mode,
		 * and the module option homepna=1 can select this instead.
		 */
		media = a->पढ़ो_bcr(ioaddr, 49);
		media &= ~3;	/* शेष to 10Mb ethernet */
		अगर (cards_found < MAX_UNITS && homepna[cards_found])
			media |= 1;	/* चयन to home wiring mode */
		अगर (pcnet32_debug & NETIF_MSG_PROBE)
			prपूर्णांकk(KERN_DEBUG PFX "media set to %sMbit mode\n",
			       (media & 1) ? "1" : "10");
		a->ग_लिखो_bcr(ioaddr, 49, media);
		अवरोध;
	हाल 0x2627:
		chipname = "PCnet/FAST III 79C975";	/* PCI */
		fdx = 1;
		mii = 1;
		sram = 1;
		अवरोध;
	हाल 0x2628:
		chipname = "PCnet/PRO 79C976";
		fdx = 1;
		mii = 1;
		अवरोध;
	शेष:
		अगर (pcnet32_debug & NETIF_MSG_PROBE)
			pr_info("PCnet version %#x, no PCnet32 chip\n",
				chip_version);
		जाओ err_release_region;
	पूर्ण

	/*
	 *  On selected chips turn on the BCR18:NOUFLO bit. This stops transmit
	 *  starting until the packet is loaded. Strike one क्रम reliability, lose
	 *  one क्रम latency - although on PCI this isn't a big loss. Older chips
	 *  have FIFO's smaller than a packet, so you can't करो this.
	 *  Turn on BCR18:BurstRdEn and BCR18:BurstWrEn.
	 */

	अगर (fset) अणु
		a->ग_लिखो_bcr(ioaddr, 18, (a->पढ़ो_bcr(ioaddr, 18) | 0x0860));
		a->ग_लिखो_csr(ioaddr, 80,
			     (a->पढ़ो_csr(ioaddr, 80) & 0x0C00) | 0x0c00);
		dxsuflo = 1;
	पूर्ण

	/*
	 * The Am79C973/Am79C975 controllers come with 12K of SRAM
	 * which we can use क्रम the Tx/Rx buffers but most importantly,
	 * the use of SRAM allow us to use the BCR18:NOUFLO bit to aव्योम
	 * Tx fअगरo underflows.
	 */
	अगर (sram) अणु
		/*
		 * The SRAM is being configured in two steps. First we
		 * set the SRAM size in the BCR25:SRAM_SIZE bits. According
		 * to the datasheet, each bit corresponds to a 512-byte
		 * page so we can have at most 24 pages. The SRAM_SIZE
		 * holds the value of the upper 8 bits of the 16-bit SRAM size.
		 * The low 8-bits start at 0x00 and end at 0xff. So the
		 * address range is from 0x0000 up to 0x17ff. Thereक्रमe,
		 * the SRAM_SIZE is set to 0x17. The next step is to set
		 * the BCR26:SRAM_BND midway through so the Tx and Rx
		 * buffers can share the SRAM equally.
		 */
		a->ग_लिखो_bcr(ioaddr, 25, 0x17);
		a->ग_लिखो_bcr(ioaddr, 26, 0xc);
		/* And finally enable the NOUFLO bit */
		a->ग_लिखो_bcr(ioaddr, 18, a->पढ़ो_bcr(ioaddr, 18) | (1 << 11));
	पूर्ण

	dev = alloc_etherdev(माप(*lp));
	अगर (!dev) अणु
		ret = -ENOMEM;
		जाओ err_release_region;
	पूर्ण

	अगर (pdev)
		SET_NETDEV_DEV(dev, &pdev->dev);

	अगर (pcnet32_debug & NETIF_MSG_PROBE)
		pr_info("%s at %#3lx,", chipname, ioaddr);

	/* In most chips, after a chip reset, the ethernet address is पढ़ो from the
	 * station address PROM at the base address and programmed पूर्णांकo the
	 * "Physical Address Registers" CSR12-14.
	 * As a precautionary measure, we पढ़ो the PROM values and complain अगर
	 * they disagree with the CSRs.  If they miscompare, and the PROM addr
	 * is valid, then the PROM addr is used.
	 */
	क्रम (i = 0; i < 3; i++) अणु
		अचिन्हित पूर्णांक val;
		val = a->पढ़ो_csr(ioaddr, i + 12) & 0x0ffff;
		/* There may be endianness issues here. */
		dev->dev_addr[2 * i] = val & 0x0ff;
		dev->dev_addr[2 * i + 1] = (val >> 8) & 0x0ff;
	पूर्ण

	/* पढ़ो PROM address and compare with CSR address */
	क्रम (i = 0; i < ETH_ALEN; i++)
		promaddr[i] = inb(ioaddr + i);

	अगर (!ether_addr_equal(promaddr, dev->dev_addr) ||
	    !is_valid_ether_addr(dev->dev_addr)) अणु
		अगर (is_valid_ether_addr(promaddr)) अणु
			अगर (pcnet32_debug & NETIF_MSG_PROBE) अणु
				pr_cont(" warning: CSR address invalid,\n");
				pr_info("    using instead PROM address of");
			पूर्ण
			स_नकल(dev->dev_addr, promaddr, ETH_ALEN);
		पूर्ण
	पूर्ण

	/* अगर the ethernet address is not valid, क्रमce to 00:00:00:00:00:00 */
	अगर (!is_valid_ether_addr(dev->dev_addr))
		eth_zero_addr(dev->dev_addr);

	अगर (pcnet32_debug & NETIF_MSG_PROBE) अणु
		pr_cont(" %pM", dev->dev_addr);

		/* Version 0x2623 and 0x2624 */
		अगर (((chip_version + 1) & 0xfffe) == 0x2624) अणु
			i = a->पढ़ो_csr(ioaddr, 80) & 0x0C00;	/* Check tx_start_pt */
			pr_info("    tx_start_pt(0x%04x):", i);
			चयन (i >> 10) अणु
			हाल 0:
				pr_cont("  20 bytes,");
				अवरोध;
			हाल 1:
				pr_cont("  64 bytes,");
				अवरोध;
			हाल 2:
				pr_cont(" 128 bytes,");
				अवरोध;
			हाल 3:
				pr_cont("~220 bytes,");
				अवरोध;
			पूर्ण
			i = a->पढ़ो_bcr(ioaddr, 18);	/* Check Burst/Bus control */
			pr_cont(" BCR18(%x):", i & 0xffff);
			अगर (i & (1 << 5))
				pr_cont("BurstWrEn ");
			अगर (i & (1 << 6))
				pr_cont("BurstRdEn ");
			अगर (i & (1 << 7))
				pr_cont("DWordIO ");
			अगर (i & (1 << 11))
				pr_cont("NoUFlow ");
			i = a->पढ़ो_bcr(ioaddr, 25);
			pr_info("    SRAMSIZE=0x%04x,", i << 8);
			i = a->पढ़ो_bcr(ioaddr, 26);
			pr_cont(" SRAM_BND=0x%04x,", i << 8);
			i = a->पढ़ो_bcr(ioaddr, 27);
			अगर (i & (1 << 14))
				pr_cont("LowLatRx");
		पूर्ण
	पूर्ण

	dev->base_addr = ioaddr;
	lp = netdev_priv(dev);
	/* dma_alloc_coherent वापसs page-aligned memory, so we करो not have to check the alignment */
	lp->init_block = dma_alloc_coherent(&pdev->dev,
					    माप(*lp->init_block),
					    &lp->init_dma_addr, GFP_KERNEL);
	अगर (!lp->init_block) अणु
		अगर (pcnet32_debug & NETIF_MSG_PROBE)
			pr_err("Coherent memory allocation failed\n");
		ret = -ENOMEM;
		जाओ err_मुक्त_netdev;
	पूर्ण
	lp->pci_dev = pdev;

	lp->dev = dev;

	spin_lock_init(&lp->lock);

	lp->name = chipname;
	lp->shared_irq = shared;
	lp->tx_ring_size = TX_RING_SIZE;	/* शेष tx ring size */
	lp->rx_ring_size = RX_RING_SIZE;	/* शेष rx ring size */
	lp->tx_mod_mask = lp->tx_ring_size - 1;
	lp->rx_mod_mask = lp->rx_ring_size - 1;
	lp->tx_len_bits = (PCNET32_LOG_TX_BUFFERS << 12);
	lp->rx_len_bits = (PCNET32_LOG_RX_BUFFERS << 4);
	lp->mii_अगर.full_duplex = fdx;
	lp->mii_अगर.phy_id_mask = 0x1f;
	lp->mii_अगर.reg_num_mask = 0x1f;
	lp->dxsuflo = dxsuflo;
	lp->mii = mii;
	lp->chip_version = chip_version;
	lp->msg_enable = pcnet32_debug;
	अगर ((cards_found >= MAX_UNITS) ||
	    (options[cards_found] >= माप(options_mapping)))
		lp->options = PCNET32_PORT_ASEL;
	अन्यथा
		lp->options = options_mapping[options[cards_found]];
	/* क्रमce शेष port to TP on 79C970A so link detection can work */
	अगर (lp->chip_version == PCNET32_79C970A)
		lp->options = PCNET32_PORT_10BT;
	lp->mii_अगर.dev = dev;
	lp->mii_अगर.mdio_पढ़ो = mdio_पढ़ो;
	lp->mii_अगर.mdio_ग_लिखो = mdio_ग_लिखो;

	/* napi.weight is used in both the napi and non-napi हालs */
	lp->napi.weight = lp->rx_ring_size / 2;

	netअगर_napi_add(dev, &lp->napi, pcnet32_poll, lp->rx_ring_size / 2);

	अगर (fdx && !(lp->options & PCNET32_PORT_ASEL) &&
	    ((cards_found >= MAX_UNITS) || full_duplex[cards_found]))
		lp->options |= PCNET32_PORT_FD;

	lp->a = a;

	/* prior to रेजिस्टर_netdev, dev->name is not yet correct */
	अगर (pcnet32_alloc_ring(dev, pci_name(lp->pci_dev))) अणु
		ret = -ENOMEM;
		जाओ err_मुक्त_ring;
	पूर्ण
	/* detect special T1/E1 WAN card by checking क्रम MAC address */
	अगर (dev->dev_addr[0] == 0x00 && dev->dev_addr[1] == 0xe0 &&
	    dev->dev_addr[2] == 0x75)
		lp->options = PCNET32_PORT_FD | PCNET32_PORT_GPSI;

	lp->init_block->mode = cpu_to_le16(0x0003);	/* Disable Rx and Tx. */
	lp->init_block->tlen_rlen =
	    cpu_to_le16(lp->tx_len_bits | lp->rx_len_bits);
	क्रम (i = 0; i < 6; i++)
		lp->init_block->phys_addr[i] = dev->dev_addr[i];
	lp->init_block->filter[0] = 0x00000000;
	lp->init_block->filter[1] = 0x00000000;
	lp->init_block->rx_ring = cpu_to_le32(lp->rx_ring_dma_addr);
	lp->init_block->tx_ring = cpu_to_le32(lp->tx_ring_dma_addr);

	/* चयन pcnet32 to 32bit mode */
	a->ग_लिखो_bcr(ioaddr, 20, 2);

	a->ग_लिखो_csr(ioaddr, 1, (lp->init_dma_addr & 0xffff));
	a->ग_लिखो_csr(ioaddr, 2, (lp->init_dma_addr >> 16));

	अगर (pdev) अणु		/* use the IRQ provided by PCI */
		dev->irq = pdev->irq;
		अगर (pcnet32_debug & NETIF_MSG_PROBE)
			pr_cont(" assigned IRQ %d\n", dev->irq);
	पूर्ण अन्यथा अणु
		अचिन्हित दीर्घ irq_mask = probe_irq_on();

		/*
		 * To स्वतः-IRQ we enable the initialization-करोne and DMA error
		 * पूर्णांकerrupts. For ISA boards we get a DMA error, but VLB and PCI
		 * boards will work.
		 */
		/* Trigger an initialization just क्रम the पूर्णांकerrupt. */
		a->ग_लिखो_csr(ioaddr, CSR0, CSR0_INTEN | CSR0_INIT);
		mdelay(1);

		dev->irq = probe_irq_off(irq_mask);
		अगर (!dev->irq) अणु
			अगर (pcnet32_debug & NETIF_MSG_PROBE)
				pr_cont(", failed to detect IRQ line\n");
			ret = -ENODEV;
			जाओ err_मुक्त_ring;
		पूर्ण
		अगर (pcnet32_debug & NETIF_MSG_PROBE)
			pr_cont(", probed IRQ %d\n", dev->irq);
	पूर्ण

	/* Set the mii phy_id so that we can query the link state */
	अगर (lp->mii) अणु
		/* lp->phycount and lp->phymask are set to 0 by स_रखो above */

		lp->mii_अगर.phy_id = ((lp->a->पढ़ो_bcr(ioaddr, 33)) >> 5) & 0x1f;
		/* scan क्रम PHYs */
		क्रम (i = 0; i < PCNET32_MAX_PHYS; i++) अणु
			अचिन्हित लघु id1, id2;

			id1 = mdio_पढ़ो(dev, i, MII_PHYSID1);
			अगर (id1 == 0xffff)
				जारी;
			id2 = mdio_पढ़ो(dev, i, MII_PHYSID2);
			अगर (id2 == 0xffff)
				जारी;
			अगर (i == 31 && ((chip_version + 1) & 0xfffe) == 0x2624)
				जारी;	/* 79C971 & 79C972 have phantom phy at id 31 */
			lp->phycount++;
			lp->phymask |= (1 << i);
			lp->mii_अगर.phy_id = i;
			अगर (pcnet32_debug & NETIF_MSG_PROBE)
				pr_info("Found PHY %04x:%04x at address %d\n",
					id1, id2, i);
		पूर्ण
		lp->a->ग_लिखो_bcr(ioaddr, 33, (lp->mii_अगर.phy_id) << 5);
		अगर (lp->phycount > 1)
			lp->options |= PCNET32_PORT_MII;
	पूर्ण

	समयr_setup(&lp->watchकरोg_समयr, pcnet32_watchकरोg, 0);

	/* The PCNET32-specअगरic entries in the device काष्ठाure. */
	dev->netdev_ops = &pcnet32_netdev_ops;
	dev->ethtool_ops = &pcnet32_ethtool_ops;
	dev->watchकरोg_समयo = (5 * HZ);

	/* Fill in the generic fields of the device काष्ठाure. */
	अगर (रेजिस्टर_netdev(dev))
		जाओ err_मुक्त_ring;

	अगर (pdev) अणु
		pci_set_drvdata(pdev, dev);
	पूर्ण अन्यथा अणु
		lp->next = pcnet32_dev;
		pcnet32_dev = dev;
	पूर्ण

	अगर (pcnet32_debug & NETIF_MSG_PROBE)
		pr_info("%s: registered as %s\n", dev->name, lp->name);
	cards_found++;

	/* enable LED ग_लिखोs */
	a->ग_लिखो_bcr(ioaddr, 2, a->पढ़ो_bcr(ioaddr, 2) | 0x1000);

	वापस 0;

err_मुक्त_ring:
	pcnet32_मुक्त_ring(dev);
	dma_मुक्त_coherent(&lp->pci_dev->dev, माप(*lp->init_block),
			  lp->init_block, lp->init_dma_addr);
err_मुक्त_netdev:
	मुक्त_netdev(dev);
err_release_region:
	release_region(ioaddr, PCNET32_TOTAL_SIZE);
	वापस ret;
पूर्ण

/* अगर any allocation fails, caller must also call pcnet32_मुक्त_ring */
अटल पूर्णांक pcnet32_alloc_ring(काष्ठा net_device *dev, स्थिर अक्षर *name)
अणु
	काष्ठा pcnet32_निजी *lp = netdev_priv(dev);

	lp->tx_ring = dma_alloc_coherent(&lp->pci_dev->dev,
					 माप(काष्ठा pcnet32_tx_head) * lp->tx_ring_size,
					 &lp->tx_ring_dma_addr, GFP_KERNEL);
	अगर (lp->tx_ring == शून्य) अणु
		netअगर_err(lp, drv, dev, "Coherent memory allocation failed\n");
		वापस -ENOMEM;
	पूर्ण

	lp->rx_ring = dma_alloc_coherent(&lp->pci_dev->dev,
					 माप(काष्ठा pcnet32_rx_head) * lp->rx_ring_size,
					 &lp->rx_ring_dma_addr, GFP_KERNEL);
	अगर (lp->rx_ring == शून्य) अणु
		netअगर_err(lp, drv, dev, "Coherent memory allocation failed\n");
		वापस -ENOMEM;
	पूर्ण

	lp->tx_dma_addr = kसुस्मृति(lp->tx_ring_size, माप(dma_addr_t),
				  GFP_KERNEL);
	अगर (!lp->tx_dma_addr)
		वापस -ENOMEM;

	lp->rx_dma_addr = kसुस्मृति(lp->rx_ring_size, माप(dma_addr_t),
				  GFP_KERNEL);
	अगर (!lp->rx_dma_addr)
		वापस -ENOMEM;

	lp->tx_skbuff = kसुस्मृति(lp->tx_ring_size, माप(काष्ठा sk_buff *),
				GFP_KERNEL);
	अगर (!lp->tx_skbuff)
		वापस -ENOMEM;

	lp->rx_skbuff = kसुस्मृति(lp->rx_ring_size, माप(काष्ठा sk_buff *),
				GFP_KERNEL);
	अगर (!lp->rx_skbuff)
		वापस -ENOMEM;

	वापस 0;
पूर्ण

अटल व्योम pcnet32_मुक्त_ring(काष्ठा net_device *dev)
अणु
	काष्ठा pcnet32_निजी *lp = netdev_priv(dev);

	kमुक्त(lp->tx_skbuff);
	lp->tx_skbuff = शून्य;

	kमुक्त(lp->rx_skbuff);
	lp->rx_skbuff = शून्य;

	kमुक्त(lp->tx_dma_addr);
	lp->tx_dma_addr = शून्य;

	kमुक्त(lp->rx_dma_addr);
	lp->rx_dma_addr = शून्य;

	अगर (lp->tx_ring) अणु
		dma_मुक्त_coherent(&lp->pci_dev->dev,
				  माप(काष्ठा pcnet32_tx_head) * lp->tx_ring_size,
				  lp->tx_ring, lp->tx_ring_dma_addr);
		lp->tx_ring = शून्य;
	पूर्ण

	अगर (lp->rx_ring) अणु
		dma_मुक्त_coherent(&lp->pci_dev->dev,
				  माप(काष्ठा pcnet32_rx_head) * lp->rx_ring_size,
				  lp->rx_ring, lp->rx_ring_dma_addr);
		lp->rx_ring = शून्य;
	पूर्ण
पूर्ण

अटल पूर्णांक pcnet32_खोलो(काष्ठा net_device *dev)
अणु
	काष्ठा pcnet32_निजी *lp = netdev_priv(dev);
	काष्ठा pci_dev *pdev = lp->pci_dev;
	अचिन्हित दीर्घ ioaddr = dev->base_addr;
	u16 val;
	पूर्णांक i;
	पूर्णांक rc;
	अचिन्हित दीर्घ flags;

	अगर (request_irq(dev->irq, pcnet32_पूर्णांकerrupt,
			lp->shared_irq ? IRQF_SHARED : 0, dev->name,
			(व्योम *)dev)) अणु
		वापस -EAGAIN;
	पूर्ण

	spin_lock_irqsave(&lp->lock, flags);
	/* Check क्रम a valid station address */
	अगर (!is_valid_ether_addr(dev->dev_addr)) अणु
		rc = -EINVAL;
		जाओ err_मुक्त_irq;
	पूर्ण

	/* Reset the PCNET32 */
	lp->a->reset(ioaddr);

	/* चयन pcnet32 to 32bit mode */
	lp->a->ग_लिखो_bcr(ioaddr, 20, 2);

	netअगर_prपूर्णांकk(lp, अगरup, KERN_DEBUG, dev,
		     "%s() irq %d tx/rx rings %#x/%#x init %#x\n",
		     __func__, dev->irq, (u32) (lp->tx_ring_dma_addr),
		     (u32) (lp->rx_ring_dma_addr),
		     (u32) (lp->init_dma_addr));

	lp->स्वतःneg = !!(lp->options & PCNET32_PORT_ASEL);
	lp->port_tp = !!(lp->options & PCNET32_PORT_10BT);
	lp->fdx = !!(lp->options & PCNET32_PORT_FD);

	/* set/reset स्वतःselect bit */
	val = lp->a->पढ़ो_bcr(ioaddr, 2) & ~2;
	अगर (lp->options & PCNET32_PORT_ASEL)
		val |= 2;
	lp->a->ग_लिखो_bcr(ioaddr, 2, val);

	/* handle full duplex setting */
	अगर (lp->mii_अगर.full_duplex) अणु
		val = lp->a->पढ़ो_bcr(ioaddr, 9) & ~3;
		अगर (lp->options & PCNET32_PORT_FD) अणु
			val |= 1;
			अगर (lp->options == (PCNET32_PORT_FD | PCNET32_PORT_AUI))
				val |= 2;
		पूर्ण अन्यथा अगर (lp->options & PCNET32_PORT_ASEL) अणु
			/* workaround of xSeries250, turn on क्रम 79C975 only */
			अगर (lp->chip_version == 0x2627)
				val |= 3;
		पूर्ण
		lp->a->ग_लिखो_bcr(ioaddr, 9, val);
	पूर्ण

	/* set/reset GPSI bit in test रेजिस्टर */
	val = lp->a->पढ़ो_csr(ioaddr, 124) & ~0x10;
	अगर ((lp->options & PCNET32_PORT_PORTSEL) == PCNET32_PORT_GPSI)
		val |= 0x10;
	lp->a->ग_लिखो_csr(ioaddr, 124, val);

	/* Allied Telesyn AT 2700/2701 FX are 100Mbit only and करो not negotiate */
	अगर (pdev && pdev->subप्रणाली_venकरोr == PCI_VENDOR_ID_AT &&
	    (pdev->subप्रणाली_device == PCI_SUBDEVICE_ID_AT_2700FX ||
	     pdev->subप्रणाली_device == PCI_SUBDEVICE_ID_AT_2701FX)) अणु
		अगर (lp->options & PCNET32_PORT_ASEL) अणु
			lp->options = PCNET32_PORT_FD | PCNET32_PORT_100;
			netअगर_prपूर्णांकk(lp, link, KERN_DEBUG, dev,
				     "Setting 100Mb-Full Duplex\n");
		पूर्ण
	पूर्ण
	अगर (lp->phycount < 2) अणु
		/*
		 * 24 Jun 2004 according AMD, in order to change the PHY,
		 * DANAS (or DISPM क्रम 79C976) must be set; then select the speed,
		 * duplex, and/or enable स्वतः negotiation, and clear DANAS
		 */
		अगर (lp->mii && !(lp->options & PCNET32_PORT_ASEL)) अणु
			lp->a->ग_लिखो_bcr(ioaddr, 32,
					lp->a->पढ़ो_bcr(ioaddr, 32) | 0x0080);
			/* disable Auto Negotiation, set 10Mpbs, HD */
			val = lp->a->पढ़ो_bcr(ioaddr, 32) & ~0xb8;
			अगर (lp->options & PCNET32_PORT_FD)
				val |= 0x10;
			अगर (lp->options & PCNET32_PORT_100)
				val |= 0x08;
			lp->a->ग_लिखो_bcr(ioaddr, 32, val);
		पूर्ण अन्यथा अणु
			अगर (lp->options & PCNET32_PORT_ASEL) अणु
				lp->a->ग_लिखो_bcr(ioaddr, 32,
						lp->a->पढ़ो_bcr(ioaddr,
							       32) | 0x0080);
				/* enable स्वतः negotiate, setup, disable fd */
				val = lp->a->पढ़ो_bcr(ioaddr, 32) & ~0x98;
				val |= 0x20;
				lp->a->ग_लिखो_bcr(ioaddr, 32, val);
			पूर्ण
		पूर्ण
	पूर्ण अन्यथा अणु
		पूर्णांक first_phy = -1;
		u16 bmcr;
		u32 bcr9;
		काष्ठा ethtool_cmd ecmd = अणु .cmd = ETHTOOL_GSET पूर्ण;

		/*
		 * There is really no good other way to handle multiple PHYs
		 * other than turning off all स्वतःmatics
		 */
		val = lp->a->पढ़ो_bcr(ioaddr, 2);
		lp->a->ग_लिखो_bcr(ioaddr, 2, val & ~2);
		val = lp->a->पढ़ो_bcr(ioaddr, 32);
		lp->a->ग_लिखो_bcr(ioaddr, 32, val & ~(1 << 7));	/* stop MII manager */

		अगर (!(lp->options & PCNET32_PORT_ASEL)) अणु
			/* setup ecmd */
			ecmd.port = PORT_MII;
			ecmd.transceiver = XCVR_INTERNAL;
			ecmd.स्वतःneg = AUTONEG_DISABLE;
			ethtool_cmd_speed_set(&ecmd,
					      (lp->options & PCNET32_PORT_100) ?
					      SPEED_100 : SPEED_10);
			bcr9 = lp->a->पढ़ो_bcr(ioaddr, 9);

			अगर (lp->options & PCNET32_PORT_FD) अणु
				ecmd.duplex = DUPLEX_FULL;
				bcr9 |= (1 << 0);
			पूर्ण अन्यथा अणु
				ecmd.duplex = DUPLEX_HALF;
				bcr9 |= ~(1 << 0);
			पूर्ण
			lp->a->ग_लिखो_bcr(ioaddr, 9, bcr9);
		पूर्ण

		क्रम (i = 0; i < PCNET32_MAX_PHYS; i++) अणु
			अगर (lp->phymask & (1 << i)) अणु
				/* isolate all but the first PHY */
				bmcr = mdio_पढ़ो(dev, i, MII_BMCR);
				अगर (first_phy == -1) अणु
					first_phy = i;
					mdio_ग_लिखो(dev, i, MII_BMCR,
						   bmcr & ~BMCR_ISOLATE);
				पूर्ण अन्यथा अणु
					mdio_ग_लिखो(dev, i, MII_BMCR,
						   bmcr | BMCR_ISOLATE);
				पूर्ण
				/* use mii_ethtool_sset to setup PHY */
				lp->mii_अगर.phy_id = i;
				ecmd.phy_address = i;
				अगर (lp->options & PCNET32_PORT_ASEL) अणु
					mii_ethtool_gset(&lp->mii_अगर, &ecmd);
					ecmd.स्वतःneg = AUTONEG_ENABLE;
				पूर्ण
				mii_ethtool_sset(&lp->mii_अगर, &ecmd);
			पूर्ण
		पूर्ण
		lp->mii_अगर.phy_id = first_phy;
		netअगर_info(lp, link, dev, "Using PHY number %d\n", first_phy);
	पूर्ण

#अगर_घोषित DO_DXSUFLO
	अगर (lp->dxsuflo) अणु	/* Disable transmit stop on underflow */
		val = lp->a->पढ़ो_csr(ioaddr, CSR3);
		val |= 0x40;
		lp->a->ग_लिखो_csr(ioaddr, CSR3, val);
	पूर्ण
#पूर्ण_अगर

	lp->init_block->mode =
	    cpu_to_le16((lp->options & PCNET32_PORT_PORTSEL) << 7);
	pcnet32_load_multicast(dev);

	अगर (pcnet32_init_ring(dev)) अणु
		rc = -ENOMEM;
		जाओ err_मुक्त_ring;
	पूर्ण

	napi_enable(&lp->napi);

	/* Re-initialize the PCNET32, and start it when करोne. */
	lp->a->ग_लिखो_csr(ioaddr, 1, (lp->init_dma_addr & 0xffff));
	lp->a->ग_लिखो_csr(ioaddr, 2, (lp->init_dma_addr >> 16));

	lp->a->ग_लिखो_csr(ioaddr, CSR4, 0x0915);	/* स्वतः tx pad */
	lp->a->ग_लिखो_csr(ioaddr, CSR0, CSR0_INIT);

	netअगर_start_queue(dev);

	अगर (lp->chip_version >= PCNET32_79C970A) अणु
		/* Prपूर्णांक the link status and start the watchकरोg */
		pcnet32_check_media(dev, 1);
		mod_समयr(&lp->watchकरोg_समयr, PCNET32_WATCHDOG_TIMEOUT);
	पूर्ण

	i = 0;
	जबतक (i++ < 100)
		अगर (lp->a->पढ़ो_csr(ioaddr, CSR0) & CSR0_IDON)
			अवरोध;
	/*
	 * We used to clear the InitDone bit, 0x0100, here but Mark Stockton
	 * reports that करोing so triggers a bug in the '974.
	 */
	lp->a->ग_लिखो_csr(ioaddr, CSR0, CSR0_NORMAL);

	netअगर_prपूर्णांकk(lp, अगरup, KERN_DEBUG, dev,
		     "pcnet32 open after %d ticks, init block %#x csr0 %4.4x\n",
		     i,
		     (u32) (lp->init_dma_addr),
		     lp->a->पढ़ो_csr(ioaddr, CSR0));

	spin_unlock_irqrestore(&lp->lock, flags);

	वापस 0;		/* Always succeed */

err_मुक्त_ring:
	/* मुक्त any allocated skbuffs */
	pcnet32_purge_rx_ring(dev);

	/*
	 * Switch back to 16bit mode to aव्योम problems with dumb
	 * DOS packet driver after a warm reboot
	 */
	lp->a->ग_लिखो_bcr(ioaddr, 20, 4);

err_मुक्त_irq:
	spin_unlock_irqrestore(&lp->lock, flags);
	मुक्त_irq(dev->irq, dev);
	वापस rc;
पूर्ण

/*
 * The LANCE has been halted क्रम one reason or another (busmaster memory
 * arbitration error, Tx FIFO underflow, driver stopped it to reconfigure,
 * etc.).  Modern LANCE variants always reload their ring-buffer
 * configuration when restarted, so we must reinitialize our ring
 * context beक्रमe restarting.  As part of this reinitialization,
 * find all packets still on the Tx ring and pretend that they had been
 * sent (in effect, drop the packets on the न्यूनमान) - the higher-level
 * protocols will समय out and retransmit.  It'd be better to shuffle
 * these skbs to a temp list and then actually re-Tx them after
 * restarting the chip, but I'm too lazy to करो so right now.  dplatt@3करो.com
 */

अटल व्योम pcnet32_purge_tx_ring(काष्ठा net_device *dev)
अणु
	काष्ठा pcnet32_निजी *lp = netdev_priv(dev);
	पूर्णांक i;

	क्रम (i = 0; i < lp->tx_ring_size; i++) अणु
		lp->tx_ring[i].status = 0;	/* CPU owns buffer */
		wmb();		/* Make sure adapter sees owner change */
		अगर (lp->tx_skbuff[i]) अणु
			अगर (!dma_mapping_error(&lp->pci_dev->dev, lp->tx_dma_addr[i]))
				dma_unmap_single(&lp->pci_dev->dev,
						 lp->tx_dma_addr[i],
						 lp->tx_skbuff[i]->len,
						 DMA_TO_DEVICE);
			dev_kमुक्त_skb_any(lp->tx_skbuff[i]);
		पूर्ण
		lp->tx_skbuff[i] = शून्य;
		lp->tx_dma_addr[i] = 0;
	पूर्ण
पूर्ण

/* Initialize the PCNET32 Rx and Tx rings. */
अटल पूर्णांक pcnet32_init_ring(काष्ठा net_device *dev)
अणु
	काष्ठा pcnet32_निजी *lp = netdev_priv(dev);
	पूर्णांक i;

	lp->tx_full = 0;
	lp->cur_rx = lp->cur_tx = 0;
	lp->dirty_rx = lp->dirty_tx = 0;

	क्रम (i = 0; i < lp->rx_ring_size; i++) अणु
		काष्ठा sk_buff *rx_skbuff = lp->rx_skbuff[i];
		अगर (rx_skbuff == शून्य) अणु
			lp->rx_skbuff[i] = netdev_alloc_skb(dev, PKT_BUF_SKB);
			rx_skbuff = lp->rx_skbuff[i];
			अगर (!rx_skbuff) अणु
				/* there is not much we can करो at this poपूर्णांक */
				netअगर_err(lp, drv, dev, "%s netdev_alloc_skb failed\n",
					  __func__);
				वापस -1;
			पूर्ण
			skb_reserve(rx_skbuff, NET_IP_ALIGN);
		पूर्ण

		rmb();
		अगर (lp->rx_dma_addr[i] == 0) अणु
			lp->rx_dma_addr[i] =
			    dma_map_single(&lp->pci_dev->dev, rx_skbuff->data,
					   PKT_BUF_SIZE, DMA_FROM_DEVICE);
			अगर (dma_mapping_error(&lp->pci_dev->dev, lp->rx_dma_addr[i])) अणु
				/* there is not much we can करो at this poपूर्णांक */
				netअगर_err(lp, drv, dev,
					  "%s pci dma mapping error\n",
					  __func__);
				वापस -1;
			पूर्ण
		पूर्ण
		lp->rx_ring[i].base = cpu_to_le32(lp->rx_dma_addr[i]);
		lp->rx_ring[i].buf_length = cpu_to_le16(NEG_BUF_SIZE);
		wmb();		/* Make sure owner changes after all others are visible */
		lp->rx_ring[i].status = cpu_to_le16(0x8000);
	पूर्ण
	/* The Tx buffer address is filled in as needed, but we करो need to clear
	 * the upper ownership bit. */
	क्रम (i = 0; i < lp->tx_ring_size; i++) अणु
		lp->tx_ring[i].status = 0;	/* CPU owns buffer */
		wmb();		/* Make sure adapter sees owner change */
		lp->tx_ring[i].base = 0;
		lp->tx_dma_addr[i] = 0;
	पूर्ण

	lp->init_block->tlen_rlen =
	    cpu_to_le16(lp->tx_len_bits | lp->rx_len_bits);
	क्रम (i = 0; i < 6; i++)
		lp->init_block->phys_addr[i] = dev->dev_addr[i];
	lp->init_block->rx_ring = cpu_to_le32(lp->rx_ring_dma_addr);
	lp->init_block->tx_ring = cpu_to_le32(lp->tx_ring_dma_addr);
	wmb();			/* Make sure all changes are visible */
	वापस 0;
पूर्ण

/* the pcnet32 has been issued a stop or reset.  Wait क्रम the stop bit
 * then flush the pending transmit operations, re-initialize the ring,
 * and tell the chip to initialize.
 */
अटल व्योम pcnet32_restart(काष्ठा net_device *dev, अचिन्हित पूर्णांक csr0_bits)
अणु
	काष्ठा pcnet32_निजी *lp = netdev_priv(dev);
	अचिन्हित दीर्घ ioaddr = dev->base_addr;
	पूर्णांक i;

	/* रुको क्रम stop */
	क्रम (i = 0; i < 100; i++)
		अगर (lp->a->पढ़ो_csr(ioaddr, CSR0) & CSR0_STOP)
			अवरोध;

	अगर (i >= 100)
		netअगर_err(lp, drv, dev, "%s timed out waiting for stop\n",
			  __func__);

	pcnet32_purge_tx_ring(dev);
	अगर (pcnet32_init_ring(dev))
		वापस;

	/* ReInit Ring */
	lp->a->ग_लिखो_csr(ioaddr, CSR0, CSR0_INIT);
	i = 0;
	जबतक (i++ < 1000)
		अगर (lp->a->पढ़ो_csr(ioaddr, CSR0) & CSR0_IDON)
			अवरोध;

	lp->a->ग_लिखो_csr(ioaddr, CSR0, csr0_bits);
पूर्ण

अटल व्योम pcnet32_tx_समयout(काष्ठा net_device *dev, अचिन्हित पूर्णांक txqueue)
अणु
	काष्ठा pcnet32_निजी *lp = netdev_priv(dev);
	अचिन्हित दीर्घ ioaddr = dev->base_addr, flags;

	spin_lock_irqsave(&lp->lock, flags);
	/* Transmitter समयout, serious problems. */
	अगर (pcnet32_debug & NETIF_MSG_DRV)
		pr_err("%s: transmit timed out, status %4.4x, resetting\n",
		       dev->name, lp->a->पढ़ो_csr(ioaddr, CSR0));
	lp->a->ग_लिखो_csr(ioaddr, CSR0, CSR0_STOP);
	dev->stats.tx_errors++;
	अगर (netअगर_msg_tx_err(lp)) अणु
		पूर्णांक i;
		prपूर्णांकk(KERN_DEBUG
		       " Ring data dump: dirty_tx %d cur_tx %d%s cur_rx %d.",
		       lp->dirty_tx, lp->cur_tx, lp->tx_full ? " (full)" : "",
		       lp->cur_rx);
		क्रम (i = 0; i < lp->rx_ring_size; i++)
			prपूर्णांकk("%s %08x %04x %08x %04x", i & 1 ? "" : "\n ",
			       le32_to_cpu(lp->rx_ring[i].base),
			       (-le16_to_cpu(lp->rx_ring[i].buf_length)) &
			       0xffff, le32_to_cpu(lp->rx_ring[i].msg_length),
			       le16_to_cpu(lp->rx_ring[i].status));
		क्रम (i = 0; i < lp->tx_ring_size; i++)
			prपूर्णांकk("%s %08x %04x %08x %04x", i & 1 ? "" : "\n ",
			       le32_to_cpu(lp->tx_ring[i].base),
			       (-le16_to_cpu(lp->tx_ring[i].length)) & 0xffff,
			       le32_to_cpu(lp->tx_ring[i].misc),
			       le16_to_cpu(lp->tx_ring[i].status));
		prपूर्णांकk("\n");
	पूर्ण
	pcnet32_restart(dev, CSR0_NORMAL);

	netअगर_trans_update(dev); /* prevent tx समयout */
	netअगर_wake_queue(dev);

	spin_unlock_irqrestore(&lp->lock, flags);
पूर्ण

अटल netdev_tx_t pcnet32_start_xmit(काष्ठा sk_buff *skb,
				      काष्ठा net_device *dev)
अणु
	काष्ठा pcnet32_निजी *lp = netdev_priv(dev);
	अचिन्हित दीर्घ ioaddr = dev->base_addr;
	u16 status;
	पूर्णांक entry;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&lp->lock, flags);

	netअगर_prपूर्णांकk(lp, tx_queued, KERN_DEBUG, dev,
		     "%s() called, csr0 %4.4x\n",
		     __func__, lp->a->पढ़ो_csr(ioaddr, CSR0));

	/* Default status -- will not enable Successful-TxDone
	 * पूर्णांकerrupt when that option is available to us.
	 */
	status = 0x8300;

	/* Fill in a Tx ring entry */

	/* Mask to ring buffer boundary. */
	entry = lp->cur_tx & lp->tx_mod_mask;

	/* Caution: the ग_लिखो order is important here, set the status
	 * with the "ownership" bits last. */

	lp->tx_ring[entry].length = cpu_to_le16(-skb->len);

	lp->tx_ring[entry].misc = 0x00000000;

	lp->tx_dma_addr[entry] =
	    dma_map_single(&lp->pci_dev->dev, skb->data, skb->len,
			   DMA_TO_DEVICE);
	अगर (dma_mapping_error(&lp->pci_dev->dev, lp->tx_dma_addr[entry])) अणु
		dev_kमुक्त_skb_any(skb);
		dev->stats.tx_dropped++;
		जाओ drop_packet;
	पूर्ण
	lp->tx_skbuff[entry] = skb;
	lp->tx_ring[entry].base = cpu_to_le32(lp->tx_dma_addr[entry]);
	wmb();			/* Make sure owner changes after all others are visible */
	lp->tx_ring[entry].status = cpu_to_le16(status);

	lp->cur_tx++;
	dev->stats.tx_bytes += skb->len;

	/* Trigger an immediate send poll. */
	lp->a->ग_लिखो_csr(ioaddr, CSR0, CSR0_INTEN | CSR0_TXPOLL);

	अगर (lp->tx_ring[(entry + 1) & lp->tx_mod_mask].base != 0) अणु
		lp->tx_full = 1;
		netअगर_stop_queue(dev);
	पूर्ण
drop_packet:
	spin_unlock_irqrestore(&lp->lock, flags);
	वापस NETDEV_TX_OK;
पूर्ण

/* The PCNET32 पूर्णांकerrupt handler. */
अटल irqवापस_t
pcnet32_पूर्णांकerrupt(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा net_device *dev = dev_id;
	काष्ठा pcnet32_निजी *lp;
	अचिन्हित दीर्घ ioaddr;
	u16 csr0;
	पूर्णांक boguscnt = max_पूर्णांकerrupt_work;

	ioaddr = dev->base_addr;
	lp = netdev_priv(dev);

	spin_lock(&lp->lock);

	csr0 = lp->a->पढ़ो_csr(ioaddr, CSR0);
	जबतक ((csr0 & 0x8f00) && --boguscnt >= 0) अणु
		अगर (csr0 == 0xffff)
			अवरोध;	/* PCMCIA हटाओ happened */
		/* Acknowledge all of the current पूर्णांकerrupt sources ASAP. */
		lp->a->ग_लिखो_csr(ioaddr, CSR0, csr0 & ~0x004f);

		netअगर_prपूर्णांकk(lp, पूर्णांकr, KERN_DEBUG, dev,
			     "interrupt  csr0=%#2.2x new csr=%#2.2x\n",
			     csr0, lp->a->पढ़ो_csr(ioaddr, CSR0));

		/* Log misc errors. */
		अगर (csr0 & 0x4000)
			dev->stats.tx_errors++;	/* Tx babble. */
		अगर (csr0 & 0x1000) अणु
			/*
			 * This happens when our receive ring is full. This
			 * shouldn't be a problem as we will see normal rx
			 * पूर्णांकerrupts क्रम the frames in the receive ring.  But
			 * there are some PCI chipsets (I can reproduce this
			 * on SP3G with Intel saturn chipset) which have
			 * someबार problems and will fill up the receive
			 * ring with error descriptors.  In this situation we
			 * करोn't get a rx पूर्णांकerrupt, but a missed frame
			 * पूर्णांकerrupt sooner or later.
			 */
			dev->stats.rx_errors++;	/* Missed a Rx frame. */
		पूर्ण
		अगर (csr0 & 0x0800) अणु
			netअगर_err(lp, drv, dev, "Bus master arbitration failure, status %4.4x\n",
				  csr0);
			/* unlike क्रम the lance, there is no restart needed */
		पूर्ण
		अगर (napi_schedule_prep(&lp->napi)) अणु
			u16 val;
			/* set पूर्णांकerrupt masks */
			val = lp->a->पढ़ो_csr(ioaddr, CSR3);
			val |= 0x5f00;
			lp->a->ग_लिखो_csr(ioaddr, CSR3, val);

			__napi_schedule(&lp->napi);
			अवरोध;
		पूर्ण
		csr0 = lp->a->पढ़ो_csr(ioaddr, CSR0);
	पूर्ण

	netअगर_prपूर्णांकk(lp, पूर्णांकr, KERN_DEBUG, dev,
		     "exiting interrupt, csr0=%#4.4x\n",
		     lp->a->पढ़ो_csr(ioaddr, CSR0));

	spin_unlock(&lp->lock);

	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक pcnet32_बंद(काष्ठा net_device *dev)
अणु
	अचिन्हित दीर्घ ioaddr = dev->base_addr;
	काष्ठा pcnet32_निजी *lp = netdev_priv(dev);
	अचिन्हित दीर्घ flags;

	del_समयr_sync(&lp->watchकरोg_समयr);

	netअगर_stop_queue(dev);
	napi_disable(&lp->napi);

	spin_lock_irqsave(&lp->lock, flags);

	dev->stats.rx_missed_errors = lp->a->पढ़ो_csr(ioaddr, 112);

	netअगर_prपूर्णांकk(lp, अगरकरोwn, KERN_DEBUG, dev,
		     "Shutting down ethercard, status was %2.2x\n",
		     lp->a->पढ़ो_csr(ioaddr, CSR0));

	/* We stop the PCNET32 here -- it occasionally polls memory अगर we करोn't. */
	lp->a->ग_लिखो_csr(ioaddr, CSR0, CSR0_STOP);

	/*
	 * Switch back to 16bit mode to aव्योम problems with dumb
	 * DOS packet driver after a warm reboot
	 */
	lp->a->ग_लिखो_bcr(ioaddr, 20, 4);

	spin_unlock_irqrestore(&lp->lock, flags);

	मुक्त_irq(dev->irq, dev);

	spin_lock_irqsave(&lp->lock, flags);

	pcnet32_purge_rx_ring(dev);
	pcnet32_purge_tx_ring(dev);

	spin_unlock_irqrestore(&lp->lock, flags);

	वापस 0;
पूर्ण

अटल काष्ठा net_device_stats *pcnet32_get_stats(काष्ठा net_device *dev)
अणु
	काष्ठा pcnet32_निजी *lp = netdev_priv(dev);
	अचिन्हित दीर्घ ioaddr = dev->base_addr;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&lp->lock, flags);
	dev->stats.rx_missed_errors = lp->a->पढ़ो_csr(ioaddr, 112);
	spin_unlock_irqrestore(&lp->lock, flags);

	वापस &dev->stats;
पूर्ण

/* taken from the sunlance driver, which it took from the depca driver */
अटल व्योम pcnet32_load_multicast(काष्ठा net_device *dev)
अणु
	काष्ठा pcnet32_निजी *lp = netdev_priv(dev);
	अस्थिर काष्ठा pcnet32_init_block *ib = lp->init_block;
	अस्थिर __le16 *mcast_table = (__le16 *)ib->filter;
	काष्ठा netdev_hw_addr *ha;
	अचिन्हित दीर्घ ioaddr = dev->base_addr;
	पूर्णांक i;
	u32 crc;

	/* set all multicast bits */
	अगर (dev->flags & IFF_ALLMULTI) अणु
		ib->filter[0] = cpu_to_le32(~0U);
		ib->filter[1] = cpu_to_le32(~0U);
		lp->a->ग_लिखो_csr(ioaddr, PCNET32_MC_FILTER, 0xffff);
		lp->a->ग_लिखो_csr(ioaddr, PCNET32_MC_FILTER+1, 0xffff);
		lp->a->ग_लिखो_csr(ioaddr, PCNET32_MC_FILTER+2, 0xffff);
		lp->a->ग_लिखो_csr(ioaddr, PCNET32_MC_FILTER+3, 0xffff);
		वापस;
	पूर्ण
	/* clear the multicast filter */
	ib->filter[0] = 0;
	ib->filter[1] = 0;

	/* Add addresses */
	netdev_क्रम_each_mc_addr(ha, dev) अणु
		crc = ether_crc_le(6, ha->addr);
		crc = crc >> 26;
		mcast_table[crc >> 4] |= cpu_to_le16(1 << (crc & 0xf));
	पूर्ण
	क्रम (i = 0; i < 4; i++)
		lp->a->ग_लिखो_csr(ioaddr, PCNET32_MC_FILTER + i,
				le16_to_cpu(mcast_table[i]));
पूर्ण

/*
 * Set or clear the multicast filter क्रम this adaptor.
 */
अटल व्योम pcnet32_set_multicast_list(काष्ठा net_device *dev)
अणु
	अचिन्हित दीर्घ ioaddr = dev->base_addr, flags;
	काष्ठा pcnet32_निजी *lp = netdev_priv(dev);
	पूर्णांक csr15, suspended;

	spin_lock_irqsave(&lp->lock, flags);
	suspended = pcnet32_suspend(dev, &flags, 0);
	csr15 = lp->a->पढ़ो_csr(ioaddr, CSR15);
	अगर (dev->flags & IFF_PROMISC) अणु
		/* Log any net taps. */
		netअगर_info(lp, hw, dev, "Promiscuous mode enabled\n");
		lp->init_block->mode =
		    cpu_to_le16(0x8000 | (lp->options & PCNET32_PORT_PORTSEL) <<
				7);
		lp->a->ग_लिखो_csr(ioaddr, CSR15, csr15 | 0x8000);
	पूर्ण अन्यथा अणु
		lp->init_block->mode =
		    cpu_to_le16((lp->options & PCNET32_PORT_PORTSEL) << 7);
		lp->a->ग_लिखो_csr(ioaddr, CSR15, csr15 & 0x7fff);
		pcnet32_load_multicast(dev);
	पूर्ण

	अगर (suspended) अणु
		pcnet32_clr_suspend(lp, ioaddr);
	पूर्ण अन्यथा अणु
		lp->a->ग_लिखो_csr(ioaddr, CSR0, CSR0_STOP);
		pcnet32_restart(dev, CSR0_NORMAL);
		netअगर_wake_queue(dev);
	पूर्ण

	spin_unlock_irqrestore(&lp->lock, flags);
पूर्ण

/* This routine assumes that the lp->lock is held */
अटल पूर्णांक mdio_पढ़ो(काष्ठा net_device *dev, पूर्णांक phy_id, पूर्णांक reg_num)
अणु
	काष्ठा pcnet32_निजी *lp = netdev_priv(dev);
	अचिन्हित दीर्घ ioaddr = dev->base_addr;
	u16 val_out;

	अगर (!lp->mii)
		वापस 0;

	lp->a->ग_लिखो_bcr(ioaddr, 33, ((phy_id & 0x1f) << 5) | (reg_num & 0x1f));
	val_out = lp->a->पढ़ो_bcr(ioaddr, 34);

	वापस val_out;
पूर्ण

/* This routine assumes that the lp->lock is held */
अटल व्योम mdio_ग_लिखो(काष्ठा net_device *dev, पूर्णांक phy_id, पूर्णांक reg_num, पूर्णांक val)
अणु
	काष्ठा pcnet32_निजी *lp = netdev_priv(dev);
	अचिन्हित दीर्घ ioaddr = dev->base_addr;

	अगर (!lp->mii)
		वापस;

	lp->a->ग_लिखो_bcr(ioaddr, 33, ((phy_id & 0x1f) << 5) | (reg_num & 0x1f));
	lp->a->ग_लिखो_bcr(ioaddr, 34, val);
पूर्ण

अटल पूर्णांक pcnet32_ioctl(काष्ठा net_device *dev, काष्ठा अगरreq *rq, पूर्णांक cmd)
अणु
	काष्ठा pcnet32_निजी *lp = netdev_priv(dev);
	पूर्णांक rc;
	अचिन्हित दीर्घ flags;

	/* SIOC[GS]MIIxxx ioctls */
	अगर (lp->mii) अणु
		spin_lock_irqsave(&lp->lock, flags);
		rc = generic_mii_ioctl(&lp->mii_अगर, अगर_mii(rq), cmd, शून्य);
		spin_unlock_irqrestore(&lp->lock, flags);
	पूर्ण अन्यथा अणु
		rc = -EOPNOTSUPP;
	पूर्ण

	वापस rc;
पूर्ण

अटल पूर्णांक pcnet32_check_otherphy(काष्ठा net_device *dev)
अणु
	काष्ठा pcnet32_निजी *lp = netdev_priv(dev);
	काष्ठा mii_अगर_info mii = lp->mii_अगर;
	u16 bmcr;
	पूर्णांक i;

	क्रम (i = 0; i < PCNET32_MAX_PHYS; i++) अणु
		अगर (i == lp->mii_अगर.phy_id)
			जारी;	/* skip active phy */
		अगर (lp->phymask & (1 << i)) अणु
			mii.phy_id = i;
			अगर (mii_link_ok(&mii)) अणु
				/* found PHY with active link */
				netअगर_info(lp, link, dev, "Using PHY number %d\n",
					   i);

				/* isolate inactive phy */
				bmcr =
				    mdio_पढ़ो(dev, lp->mii_अगर.phy_id, MII_BMCR);
				mdio_ग_लिखो(dev, lp->mii_अगर.phy_id, MII_BMCR,
					   bmcr | BMCR_ISOLATE);

				/* de-isolate new phy */
				bmcr = mdio_पढ़ो(dev, i, MII_BMCR);
				mdio_ग_लिखो(dev, i, MII_BMCR,
					   bmcr & ~BMCR_ISOLATE);

				/* set new phy address */
				lp->mii_अगर.phy_id = i;
				वापस 1;
			पूर्ण
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण

/*
 * Show the status of the media.  Similar to mii_check_media however it
 * correctly shows the link speed क्रम all (tested) pcnet32 variants.
 * Devices with no mii just report link state without speed.
 *
 * Caller is assumed to hold and release the lp->lock.
 */

अटल व्योम pcnet32_check_media(काष्ठा net_device *dev, पूर्णांक verbose)
अणु
	काष्ठा pcnet32_निजी *lp = netdev_priv(dev);
	पूर्णांक curr_link;
	पूर्णांक prev_link = netअगर_carrier_ok(dev) ? 1 : 0;
	u32 bcr9;

	अगर (lp->mii) अणु
		curr_link = mii_link_ok(&lp->mii_अगर);
	पूर्ण अन्यथा अगर (lp->chip_version == PCNET32_79C970A) अणु
		uदीर्घ ioaddr = dev->base_addr;	/* card base I/O address */
		/* only पढ़ो link अगर port is set to TP */
		अगर (!lp->स्वतःneg && lp->port_tp)
			curr_link = (lp->a->पढ़ो_bcr(ioaddr, 4) != 0xc0);
		अन्यथा /* link always up क्रम AUI port or port स्वतः select */
			curr_link = 1;
	पूर्ण अन्यथा अणु
		uदीर्घ ioaddr = dev->base_addr;	/* card base I/O address */
		curr_link = (lp->a->पढ़ो_bcr(ioaddr, 4) != 0xc0);
	पूर्ण
	अगर (!curr_link) अणु
		अगर (prev_link || verbose) अणु
			netअगर_carrier_off(dev);
			netअगर_info(lp, link, dev, "link down\n");
		पूर्ण
		अगर (lp->phycount > 1) अणु
			pcnet32_check_otherphy(dev);
		पूर्ण
	पूर्ण अन्यथा अगर (verbose || !prev_link) अणु
		netअगर_carrier_on(dev);
		अगर (lp->mii) अणु
			अगर (netअगर_msg_link(lp)) अणु
				काष्ठा ethtool_cmd ecmd = अणु
					.cmd = ETHTOOL_GSET पूर्ण;
				mii_ethtool_gset(&lp->mii_अगर, &ecmd);
				netdev_info(dev, "link up, %uMbps, %s-duplex\n",
					    ethtool_cmd_speed(&ecmd),
					    (ecmd.duplex == DUPLEX_FULL)
					    ? "full" : "half");
			पूर्ण
			bcr9 = lp->a->पढ़ो_bcr(dev->base_addr, 9);
			अगर ((bcr9 & (1 << 0)) != lp->mii_अगर.full_duplex) अणु
				अगर (lp->mii_अगर.full_duplex)
					bcr9 |= (1 << 0);
				अन्यथा
					bcr9 &= ~(1 << 0);
				lp->a->ग_लिखो_bcr(dev->base_addr, 9, bcr9);
			पूर्ण
		पूर्ण अन्यथा अणु
			netअगर_info(lp, link, dev, "link up\n");
		पूर्ण
	पूर्ण
पूर्ण

/*
 * Check क्रम loss of link and link establishment.
 * Could possibly be changed to use mii_check_media instead.
 */

अटल व्योम pcnet32_watchकरोg(काष्ठा समयr_list *t)
अणु
	काष्ठा pcnet32_निजी *lp = from_समयr(lp, t, watchकरोg_समयr);
	काष्ठा net_device *dev = lp->dev;
	अचिन्हित दीर्घ flags;

	/* Prपूर्णांक the link status अगर it has changed */
	spin_lock_irqsave(&lp->lock, flags);
	pcnet32_check_media(dev, 0);
	spin_unlock_irqrestore(&lp->lock, flags);

	mod_समयr(&lp->watchकरोg_समयr, round_jअगरfies(PCNET32_WATCHDOG_TIMEOUT));
पूर्ण

अटल पूर्णांक __maybe_unused pcnet32_pm_suspend(काष्ठा device *device_d)
अणु
	काष्ठा net_device *dev = dev_get_drvdata(device_d);

	अगर (netअगर_running(dev)) अणु
		netअगर_device_detach(dev);
		pcnet32_बंद(dev);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक __maybe_unused pcnet32_pm_resume(काष्ठा device *device_d)
अणु
	काष्ठा net_device *dev = dev_get_drvdata(device_d);

	अगर (netअगर_running(dev)) अणु
		pcnet32_खोलो(dev);
		netअगर_device_attach(dev);
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम pcnet32_हटाओ_one(काष्ठा pci_dev *pdev)
अणु
	काष्ठा net_device *dev = pci_get_drvdata(pdev);

	अगर (dev) अणु
		काष्ठा pcnet32_निजी *lp = netdev_priv(dev);

		unरेजिस्टर_netdev(dev);
		pcnet32_मुक्त_ring(dev);
		release_region(dev->base_addr, PCNET32_TOTAL_SIZE);
		dma_मुक्त_coherent(&lp->pci_dev->dev, माप(*lp->init_block),
				  lp->init_block, lp->init_dma_addr);
		मुक्त_netdev(dev);
		pci_disable_device(pdev);
	पूर्ण
पूर्ण

अटल SIMPLE_DEV_PM_OPS(pcnet32_pm_ops, pcnet32_pm_suspend, pcnet32_pm_resume);

अटल काष्ठा pci_driver pcnet32_driver = अणु
	.name = DRV_NAME,
	.probe = pcnet32_probe_pci,
	.हटाओ = pcnet32_हटाओ_one,
	.id_table = pcnet32_pci_tbl,
	.driver = अणु
		.pm = &pcnet32_pm_ops,
	पूर्ण,
पूर्ण;

/* An additional parameter that may be passed in... */
अटल पूर्णांक debug = -1;
अटल पूर्णांक tx_start_pt = -1;
अटल पूर्णांक pcnet32_have_pci;

module_param(debug, पूर्णांक, 0);
MODULE_PARM_DESC(debug, DRV_NAME " debug level");
module_param(max_पूर्णांकerrupt_work, पूर्णांक, 0);
MODULE_PARM_DESC(max_पूर्णांकerrupt_work,
		 DRV_NAME " maximum events handled per interrupt");
module_param(rx_copyअवरोध, पूर्णांक, 0);
MODULE_PARM_DESC(rx_copyअवरोध,
		 DRV_NAME " copy breakpoint for copy-only-tiny-frames");
module_param(tx_start_pt, पूर्णांक, 0);
MODULE_PARM_DESC(tx_start_pt, DRV_NAME " transmit start point (0-3)");
module_param(pcnet32vlb, पूर्णांक, 0);
MODULE_PARM_DESC(pcnet32vlb, DRV_NAME " Vesa local bus (VLB) support (0/1)");
module_param_array(options, पूर्णांक, शून्य, 0);
MODULE_PARM_DESC(options, DRV_NAME " initial option setting(s) (0-15)");
module_param_array(full_duplex, पूर्णांक, शून्य, 0);
MODULE_PARM_DESC(full_duplex, DRV_NAME " full duplex setting(s) (1)");
/* Module Parameter क्रम HomePNA cards added by Patrick Simmons, 2004 */
module_param_array(homepna, पूर्णांक, शून्य, 0);
MODULE_PARM_DESC(homepna,
		 DRV_NAME
		 " mode for 79C978 cards (1 for HomePNA, 0 for Ethernet, default Ethernet");

MODULE_AUTHOR("Thomas Bogendoerfer");
MODULE_DESCRIPTION("Driver for PCnet32 and PCnetPCI based ethercards");
MODULE_LICENSE("GPL");

#घोषणा PCNET32_MSG_DEFAULT (NETIF_MSG_DRV | NETIF_MSG_PROBE | NETIF_MSG_LINK)

अटल पूर्णांक __init pcnet32_init_module(व्योम)
अणु
	pcnet32_debug = netअगर_msg_init(debug, PCNET32_MSG_DEFAULT);

	अगर ((tx_start_pt >= 0) && (tx_start_pt <= 3))
		tx_start = tx_start_pt;

	/* find the PCI devices */
	अगर (!pci_रेजिस्टर_driver(&pcnet32_driver))
		pcnet32_have_pci = 1;

	/* should we find any reमुख्यing VLbus devices ? */
	अगर (pcnet32vlb)
		pcnet32_probe_vlbus(pcnet32_portlist);

	अगर (cards_found && (pcnet32_debug & NETIF_MSG_PROBE))
		pr_info("%d cards_found\n", cards_found);

	वापस (pcnet32_have_pci + cards_found) ? 0 : -ENODEV;
पूर्ण

अटल व्योम __निकास pcnet32_cleanup_module(व्योम)
अणु
	काष्ठा net_device *next_dev;

	जबतक (pcnet32_dev) अणु
		काष्ठा pcnet32_निजी *lp = netdev_priv(pcnet32_dev);
		next_dev = lp->next;
		unरेजिस्टर_netdev(pcnet32_dev);
		pcnet32_मुक्त_ring(pcnet32_dev);
		release_region(pcnet32_dev->base_addr, PCNET32_TOTAL_SIZE);
		dma_मुक्त_coherent(&lp->pci_dev->dev, माप(*lp->init_block),
				  lp->init_block, lp->init_dma_addr);
		मुक्त_netdev(pcnet32_dev);
		pcnet32_dev = next_dev;
	पूर्ण

	अगर (pcnet32_have_pci)
		pci_unरेजिस्टर_driver(&pcnet32_driver);
पूर्ण

module_init(pcnet32_init_module);
module_निकास(pcnet32_cleanup_module);
