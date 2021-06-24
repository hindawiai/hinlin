<शैली गुरु>
/*
   sis190.c: Silicon Integrated Systems SiS190 ethernet driver

   Copyright (c) 2003 K.M. Liu <kmliu@sis.com>
   Copyright (c) 2003, 2004 Jeff Garzik <jgarzik@pobox.com>
   Copyright (c) 2003, 2004, 2005 Francois Romieu <romieu@fr.zoreil.com>

   Based on r8169.c, tg3.c, 8139cp.c, skge.c, epic100.c and SiS 190/191
   genuine driver.

   This software may be used and distributed according to the terms of
   the GNU General Public License (GPL), incorporated herein by reference.
   Drivers based on or derived from this code fall under the GPL and must
   retain the authorship, copyright and license notice.  This file is not
   a complete program and may only be used when the entire operating
   प्रणाली is licensed under the GPL.

   See the file COPYING in this distribution क्रम more inक्रमmation.

*/

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/module.h>
#समावेश <linux/moduleparam.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/rtnetlink.h>
#समावेश <linux/etherdevice.h>
#समावेश <linux/ethtool.h>
#समावेश <linux/pci.h>
#समावेश <linux/mii.h>
#समावेश <linux/delay.h>
#समावेश <linux/crc32.h>
#समावेश <linux/dma-mapping.h>
#समावेश <linux/slab.h>
#समावेश <यंत्र/irq.h>

#घोषणा PHY_MAX_ADDR		32
#घोषणा PHY_ID_ANY		0x1f
#घोषणा MII_REG_ANY		0x1f

#घोषणा DRV_VERSION		"1.4"
#घोषणा DRV_NAME		"sis190"
#घोषणा SIS190_DRIVER_NAME	DRV_NAME " Gigabit Ethernet driver " DRV_VERSION

#घोषणा sis190_rx_skb			netअगर_rx
#घोषणा sis190_rx_quota(count, quota)	count

#घोषणा NUM_TX_DESC		64	/* [8..1024] */
#घोषणा NUM_RX_DESC		64	/* [8..8192] */
#घोषणा TX_RING_BYTES		(NUM_TX_DESC * माप(काष्ठा TxDesc))
#घोषणा RX_RING_BYTES		(NUM_RX_DESC * माप(काष्ठा RxDesc))
#घोषणा RX_BUF_SIZE		1536
#घोषणा RX_BUF_MASK		0xfff8

#घोषणा SIS190_REGS_SIZE	0x80
#घोषणा SIS190_TX_TIMEOUT	(6*HZ)
#घोषणा SIS190_PHY_TIMEOUT	(10*HZ)
#घोषणा SIS190_MSG_DEFAULT	(NETIF_MSG_DRV | NETIF_MSG_PROBE | \
				 NETIF_MSG_LINK | NETIF_MSG_IFUP | \
				 NETIF_MSG_IFDOWN)

/* Enhanced PHY access रेजिस्टर bit definitions */
#घोषणा EhnMIIपढ़ो		0x0000
#घोषणा EhnMIIग_लिखो		0x0020
#घोषणा EhnMIIdataShअगरt		16
#घोषणा EhnMIIpmdShअगरt		6	/* 7016 only */
#घोषणा EhnMIIregShअगरt		11
#घोषणा EhnMIIreq		0x0010
#घोषणा EhnMIInotDone		0x0010

/* Write/पढ़ो MMIO रेजिस्टर */
#घोषणा SIS_W8(reg, val)	ग_लिखोb ((val), ioaddr + (reg))
#घोषणा SIS_W16(reg, val)	ग_लिखोw ((val), ioaddr + (reg))
#घोषणा SIS_W32(reg, val)	ग_लिखोl ((val), ioaddr + (reg))
#घोषणा SIS_R8(reg)		पढ़ोb (ioaddr + (reg))
#घोषणा SIS_R16(reg)		पढ़ोw (ioaddr + (reg))
#घोषणा SIS_R32(reg)		पढ़ोl (ioaddr + (reg))

#घोषणा SIS_PCI_COMMIT()	SIS_R32(IntrControl)

क्रमागत sis190_रेजिस्टरs अणु
	TxControl		= 0x00,
	TxDescStartAddr		= 0x04,
	rsv0			= 0x08,	// reserved
	TxSts			= 0x0c,	// unused (Control/Status)
	RxControl		= 0x10,
	RxDescStartAddr		= 0x14,
	rsv1			= 0x18,	// reserved
	RxSts			= 0x1c,	// unused
	IntrStatus		= 0x20,
	IntrMask		= 0x24,
	IntrControl		= 0x28,
	IntrTimer		= 0x2c,	// unused (Interrupt Timer)
	PMControl		= 0x30,	// unused (Power Mgmt Control/Status)
	rsv2			= 0x34,	// reserved
	ROMControl		= 0x38,
	ROMInterface		= 0x3c,
	StationControl		= 0x40,
	GMIIControl		= 0x44,
	GIoCR			= 0x48, // unused (GMAC IO Compensation)
	GIoCtrl			= 0x4c, // unused (GMAC IO Control)
	TxMacControl		= 0x50,
	TxLimit			= 0x54, // unused (Tx MAC Timer/TryLimit)
	RGDelay			= 0x58, // unused (RGMII Tx Internal Delay)
	rsv3			= 0x5c, // reserved
	RxMacControl		= 0x60,
	RxMacAddr		= 0x62,
	RxHashTable		= 0x68,
	// Unकरोcumented		= 0x6c,
	RxWolCtrl		= 0x70,
	RxWolData		= 0x74, // unused (Rx WOL Data Access)
	RxMPSControl		= 0x78,	// unused (Rx MPS Control)
	rsv4			= 0x7c, // reserved
पूर्ण;

क्रमागत sis190_रेजिस्टर_content अणु
	/* IntrStatus */
	SoftInt			= 0x40000000,	// unused
	Timeup			= 0x20000000,	// unused
	PauseFrame		= 0x00080000,	// unused
	MagicPacket		= 0x00040000,	// unused
	WakeupFrame		= 0x00020000,	// unused
	LinkChange		= 0x00010000,
	RxQEmpty		= 0x00000080,
	RxQInt			= 0x00000040,
	TxQ1Empty		= 0x00000020,	// unused
	TxQ1Int			= 0x00000010,
	TxQ0Empty		= 0x00000008,	// unused
	TxQ0Int			= 0x00000004,
	RxHalt			= 0x00000002,
	TxHalt			= 0x00000001,

	/* अणुRx/Txपूर्णCmdBits */
	CmdReset		= 0x10,
	CmdRxEnb		= 0x08,		// unused
	CmdTxEnb		= 0x01,
	RxBufEmpty		= 0x01,		// unused

	/* Cfg9346Bits */
	Cfg9346_Lock		= 0x00,		// unused
	Cfg9346_Unlock		= 0xc0,		// unused

	/* RxMacControl */
	AcceptErr		= 0x20,		// unused
	AcceptRunt		= 0x10,		// unused
	AcceptBroadcast		= 0x0800,
	AcceptMulticast		= 0x0400,
	AcceptMyPhys		= 0x0200,
	AcceptAllPhys		= 0x0100,

	/* RxConfigBits */
	RxCfgFIFOShअगरt		= 13,
	RxCfgDMAShअगरt		= 8,		// 0x1a in RxControl ?

	/* TxConfigBits */
	TxInterFrameGapShअगरt	= 24,
	TxDMAShअगरt		= 8, /* DMA burst value (0-7) is shअगरt this many bits */

	LinkStatus		= 0x02,		// unused
	FullDup			= 0x01,		// unused

	/* TBICSRBit */
	TBILinkOK		= 0x02000000,	// unused
पूर्ण;

काष्ठा TxDesc अणु
	__le32 PSize;
	__le32 status;
	__le32 addr;
	__le32 size;
पूर्ण;

काष्ठा RxDesc अणु
	__le32 PSize;
	__le32 status;
	__le32 addr;
	__le32 size;
पूर्ण;

क्रमागत _DescStatusBit अणु
	/* _Desc.status */
	OWNbit		= 0x80000000, // RXOWN/TXOWN
	INTbit		= 0x40000000, // RXINT/TXINT
	CRCbit		= 0x00020000, // CRCOFF/CRCEN
	PADbit		= 0x00010000, // PREADD/PADEN
	/* _Desc.size */
	RingEnd		= 0x80000000,
	/* TxDesc.status */
	LSEN		= 0x08000000, // TSO ? -- FR
	IPCS		= 0x04000000,
	TCPCS		= 0x02000000,
	UDPCS		= 0x01000000,
	BSTEN		= 0x00800000,
	EXTEN		= 0x00400000,
	DEFEN		= 0x00200000,
	BKFEN		= 0x00100000,
	CRSEN		= 0x00080000,
	COLEN		= 0x00040000,
	THOL3		= 0x30000000,
	THOL2		= 0x20000000,
	THOL1		= 0x10000000,
	THOL0		= 0x00000000,

	WND		= 0x00080000,
	TABRT		= 0x00040000,
	FIFO		= 0x00020000,
	LINK		= 0x00010000,
	ColCountMask	= 0x0000ffff,
	/* RxDesc.status */
	IPON		= 0x20000000,
	TCPON		= 0x10000000,
	UDPON		= 0x08000000,
	Wakup		= 0x00400000,
	Magic		= 0x00200000,
	Pause		= 0x00100000,
	DEFbit		= 0x00200000,
	BCAST		= 0x000c0000,
	MCAST		= 0x00080000,
	UCAST		= 0x00040000,
	/* RxDesc.PSize */
	TAGON		= 0x80000000,
	RxDescCountMask	= 0x7f000000, // multi-desc pkt when > 1 ? -- FR
	ABORT		= 0x00800000,
	SHORT		= 0x00400000,
	LIMIT		= 0x00200000,
	MIIER		= 0x00100000,
	OVRUN		= 0x00080000,
	NIBON		= 0x00040000,
	COLON		= 0x00020000,
	CRCOK		= 0x00010000,
	RxSizeMask	= 0x0000ffff
	/*
	 * The asic could apparently करो vlan, TSO, jumbo (sis191 only) and
	 * provide two (unused with Linux) Tx queues. No खुलाly
	 * available करोcumentation alas.
	 */
पूर्ण;

क्रमागत sis190_eeprom_access_रेजिस्टर_bits अणु
	EECS	= 0x00000001,	// unused
	EECLK	= 0x00000002,	// unused
	EEDO	= 0x00000008,	// unused
	EEDI	= 0x00000004,	// unused
	EEREQ	= 0x00000080,
	EEROP	= 0x00000200,
	EEWOP	= 0x00000100	// unused
पूर्ण;

/* EEPROM Addresses */
क्रमागत sis190_eeprom_address अणु
	EEPROMSignature	= 0x00,
	EEPROMCLK	= 0x01,	// unused
	EEPROMInfo	= 0x02,
	EEPROMMACAddr	= 0x03
पूर्ण;

क्रमागत sis190_feature अणु
	F_HAS_RGMII	= 1,
	F_PHY_88E1111	= 2,
	F_PHY_BCM5461	= 4
पूर्ण;

काष्ठा sis190_निजी अणु
	व्योम __iomem *mmio_addr;
	काष्ठा pci_dev *pci_dev;
	काष्ठा net_device *dev;
	spinlock_t lock;
	u32 rx_buf_sz;
	u32 cur_rx;
	u32 cur_tx;
	u32 dirty_rx;
	u32 dirty_tx;
	dma_addr_t rx_dma;
	dma_addr_t tx_dma;
	काष्ठा RxDesc *RxDescRing;
	काष्ठा TxDesc *TxDescRing;
	काष्ठा sk_buff *Rx_skbuff[NUM_RX_DESC];
	काष्ठा sk_buff *Tx_skbuff[NUM_TX_DESC];
	काष्ठा work_काष्ठा phy_task;
	काष्ठा समयr_list समयr;
	u32 msg_enable;
	काष्ठा mii_अगर_info mii_अगर;
	काष्ठा list_head first_phy;
	u32 features;
	u32 negotiated_lpa;
	क्रमागत अणु
		LNK_OFF,
		LNK_ON,
		LNK_AUTONEG,
	पूर्ण link_status;
पूर्ण;

काष्ठा sis190_phy अणु
	काष्ठा list_head list;
	पूर्णांक phy_id;
	u16 id[2];
	u16 status;
	u8  type;
पूर्ण;

क्रमागत sis190_phy_type अणु
	UNKNOWN	= 0x00,
	HOME	= 0x01,
	LAN	= 0x02,
	MIX	= 0x03
पूर्ण;

अटल काष्ठा mii_chip_info अणु
        स्थिर अक्षर *name;
        u16 id[2];
        अचिन्हित पूर्णांक type;
	u32 feature;
पूर्ण mii_chip_table[] = अणु
	अणु "Atheros PHY",          अणु 0x004d, 0xd010 पूर्ण, LAN, 0 पूर्ण,
	अणु "Atheros PHY AR8012",   अणु 0x004d, 0xd020 पूर्ण, LAN, 0 पूर्ण,
	अणु "Broadcom PHY BCM5461", अणु 0x0020, 0x60c0 पूर्ण, LAN, F_PHY_BCM5461 पूर्ण,
	अणु "Broadcom PHY AC131",   अणु 0x0143, 0xbc70 पूर्ण, LAN, 0 पूर्ण,
	अणु "Agere PHY ET1101B",    अणु 0x0282, 0xf010 पूर्ण, LAN, 0 पूर्ण,
	अणु "Marvell PHY 88E1111",  अणु 0x0141, 0x0cc0 पूर्ण, LAN, F_PHY_88E1111 पूर्ण,
	अणु "Realtek PHY RTL8201",  अणु 0x0000, 0x8200 पूर्ण, LAN, 0 पूर्ण,
	अणु शून्य, पूर्ण
पूर्ण;

अटल स्थिर काष्ठा अणु
	स्थिर अक्षर *name;
पूर्ण sis_chip_info[] = अणु
	अणु "SiS 190 PCI Fast Ethernet adapter" पूर्ण,
	अणु "SiS 191 PCI Gigabit Ethernet adapter" पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा pci_device_id sis190_pci_tbl[] = अणु
	अणु PCI_DEVICE(PCI_VENDOR_ID_SI, 0x0190), 0, 0, 0 पूर्ण,
	अणु PCI_DEVICE(PCI_VENDOR_ID_SI, 0x0191), 0, 0, 1 पूर्ण,
	अणु 0, पूर्ण,
पूर्ण;

MODULE_DEVICE_TABLE(pci, sis190_pci_tbl);

अटल पूर्णांक rx_copyअवरोध = 200;

अटल काष्ठा अणु
	u32 msg_enable;
पूर्ण debug = अणु -1 पूर्ण;

MODULE_DESCRIPTION("SiS sis190/191 Gigabit Ethernet driver");
module_param(rx_copyअवरोध, पूर्णांक, 0);
MODULE_PARM_DESC(rx_copyअवरोध, "Copy breakpoint for copy-only-tiny-frames");
module_param_named(debug, debug.msg_enable, पूर्णांक, 0);
MODULE_PARM_DESC(debug, "Debug verbosity level (0=none, ..., 16=all)");
MODULE_AUTHOR("K.M. Liu <kmliu@sis.com>, Ueimor <romieu@fr.zoreil.com>");
MODULE_VERSION(DRV_VERSION);
MODULE_LICENSE("GPL");

अटल स्थिर u32 sis190_पूर्णांकr_mask =
	RxQEmpty | RxQInt | TxQ1Int | TxQ0Int | RxHalt | TxHalt | LinkChange;

/*
 * Maximum number of multicast addresses to filter (vs. Rx-all-multicast).
 * The chips use a 64 element hash table based on the Ethernet CRC.
 */
अटल स्थिर पूर्णांक multicast_filter_limit = 32;

अटल व्योम __mdio_cmd(व्योम __iomem *ioaddr, u32 ctl)
अणु
	अचिन्हित पूर्णांक i;

	SIS_W32(GMIIControl, ctl);

	msleep(1);

	क्रम (i = 0; i < 100; i++) अणु
		अगर (!(SIS_R32(GMIIControl) & EhnMIInotDone))
			अवरोध;
		msleep(1);
	पूर्ण

	अगर (i > 99)
		pr_err("PHY command failed !\n");
पूर्ण

अटल व्योम mdio_ग_लिखो(व्योम __iomem *ioaddr, पूर्णांक phy_id, पूर्णांक reg, पूर्णांक val)
अणु
	__mdio_cmd(ioaddr, EhnMIIreq | EhnMIIग_लिखो |
		(((u32) reg) << EhnMIIregShअगरt) | (phy_id << EhnMIIpmdShअगरt) |
		(((u32) val) << EhnMIIdataShअगरt));
पूर्ण

अटल पूर्णांक mdio_पढ़ो(व्योम __iomem *ioaddr, पूर्णांक phy_id, पूर्णांक reg)
अणु
	__mdio_cmd(ioaddr, EhnMIIreq | EhnMIIपढ़ो |
		(((u32) reg) << EhnMIIregShअगरt) | (phy_id << EhnMIIpmdShअगरt));

	वापस (u16) (SIS_R32(GMIIControl) >> EhnMIIdataShअगरt);
पूर्ण

अटल व्योम __mdio_ग_लिखो(काष्ठा net_device *dev, पूर्णांक phy_id, पूर्णांक reg, पूर्णांक val)
अणु
	काष्ठा sis190_निजी *tp = netdev_priv(dev);

	mdio_ग_लिखो(tp->mmio_addr, phy_id, reg, val);
पूर्ण

अटल पूर्णांक __mdio_पढ़ो(काष्ठा net_device *dev, पूर्णांक phy_id, पूर्णांक reg)
अणु
	काष्ठा sis190_निजी *tp = netdev_priv(dev);

	वापस mdio_पढ़ो(tp->mmio_addr, phy_id, reg);
पूर्ण

अटल u16 mdio_पढ़ो_latched(व्योम __iomem *ioaddr, पूर्णांक phy_id, पूर्णांक reg)
अणु
	mdio_पढ़ो(ioaddr, phy_id, reg);
	वापस mdio_पढ़ो(ioaddr, phy_id, reg);
पूर्ण

अटल u16 sis190_पढ़ो_eeprom(व्योम __iomem *ioaddr, u32 reg)
अणु
	u16 data = 0xffff;
	अचिन्हित पूर्णांक i;

	अगर (!(SIS_R32(ROMControl) & 0x0002))
		वापस 0;

	SIS_W32(ROMInterface, EEREQ | EEROP | (reg << 10));

	क्रम (i = 0; i < 200; i++) अणु
		अगर (!(SIS_R32(ROMInterface) & EEREQ)) अणु
			data = (SIS_R32(ROMInterface) & 0xffff0000) >> 16;
			अवरोध;
		पूर्ण
		msleep(1);
	पूर्ण

	वापस data;
पूर्ण

अटल व्योम sis190_irq_mask_and_ack(व्योम __iomem *ioaddr)
अणु
	SIS_W32(IntrMask, 0x00);
	SIS_W32(IntrStatus, 0xffffffff);
	SIS_PCI_COMMIT();
पूर्ण

अटल व्योम sis190_asic_करोwn(व्योम __iomem *ioaddr)
अणु
	/* Stop the chip's Tx and Rx DMA processes. */

	SIS_W32(TxControl, 0x1a00);
	SIS_W32(RxControl, 0x1a00);

	sis190_irq_mask_and_ack(ioaddr);
पूर्ण

अटल व्योम sis190_mark_as_last_descriptor(काष्ठा RxDesc *desc)
अणु
	desc->size |= cpu_to_le32(RingEnd);
पूर्ण

अटल अंतरभूत व्योम sis190_give_to_asic(काष्ठा RxDesc *desc, u32 rx_buf_sz)
अणु
	u32 eor = le32_to_cpu(desc->size) & RingEnd;

	desc->PSize = 0x0;
	desc->size = cpu_to_le32((rx_buf_sz & RX_BUF_MASK) | eor);
	wmb();
	desc->status = cpu_to_le32(OWNbit | INTbit);
पूर्ण

अटल अंतरभूत व्योम sis190_map_to_asic(काष्ठा RxDesc *desc, dma_addr_t mapping,
				      u32 rx_buf_sz)
अणु
	desc->addr = cpu_to_le32(mapping);
	sis190_give_to_asic(desc, rx_buf_sz);
पूर्ण

अटल अंतरभूत व्योम sis190_make_unusable_by_asic(काष्ठा RxDesc *desc)
अणु
	desc->PSize = 0x0;
	desc->addr = cpu_to_le32(0xdeadbeef);
	desc->size &= cpu_to_le32(RingEnd);
	wmb();
	desc->status = 0x0;
पूर्ण

अटल काष्ठा sk_buff *sis190_alloc_rx_skb(काष्ठा sis190_निजी *tp,
					   काष्ठा RxDesc *desc)
अणु
	u32 rx_buf_sz = tp->rx_buf_sz;
	काष्ठा sk_buff *skb;
	dma_addr_t mapping;

	skb = netdev_alloc_skb(tp->dev, rx_buf_sz);
	अगर (unlikely(!skb))
		जाओ skb_alloc_failed;
	mapping = dma_map_single(&tp->pci_dev->dev, skb->data, tp->rx_buf_sz,
				 DMA_FROM_DEVICE);
	अगर (dma_mapping_error(&tp->pci_dev->dev, mapping))
		जाओ out;
	sis190_map_to_asic(desc, mapping, rx_buf_sz);

	वापस skb;

out:
	dev_kमुक्त_skb_any(skb);
skb_alloc_failed:
	sis190_make_unusable_by_asic(desc);
	वापस शून्य;
पूर्ण

अटल u32 sis190_rx_fill(काष्ठा sis190_निजी *tp, काष्ठा net_device *dev,
			  u32 start, u32 end)
अणु
	u32 cur;

	क्रम (cur = start; cur < end; cur++) अणु
		अचिन्हित पूर्णांक i = cur % NUM_RX_DESC;

		अगर (tp->Rx_skbuff[i])
			जारी;

		tp->Rx_skbuff[i] = sis190_alloc_rx_skb(tp, tp->RxDescRing + i);

		अगर (!tp->Rx_skbuff[i])
			अवरोध;
	पूर्ण
	वापस cur - start;
पूर्ण

अटल bool sis190_try_rx_copy(काष्ठा sis190_निजी *tp,
			       काष्ठा sk_buff **sk_buff, पूर्णांक pkt_size,
			       dma_addr_t addr)
अणु
	काष्ठा sk_buff *skb;
	bool करोne = false;

	अगर (pkt_size >= rx_copyअवरोध)
		जाओ out;

	skb = netdev_alloc_skb_ip_align(tp->dev, pkt_size);
	अगर (!skb)
		जाओ out;

	dma_sync_single_क्रम_cpu(&tp->pci_dev->dev, addr, tp->rx_buf_sz,
				DMA_FROM_DEVICE);
	skb_copy_to_linear_data(skb, sk_buff[0]->data, pkt_size);
	*sk_buff = skb;
	करोne = true;
out:
	वापस करोne;
पूर्ण

अटल अंतरभूत पूर्णांक sis190_rx_pkt_err(u32 status, काष्ठा net_device_stats *stats)
अणु
#घोषणा ErrMask	(OVRUN | SHORT | LIMIT | MIIER | NIBON | COLON | ABORT)

	अगर ((status & CRCOK) && !(status & ErrMask))
		वापस 0;

	अगर (!(status & CRCOK))
		stats->rx_crc_errors++;
	अन्यथा अगर (status & OVRUN)
		stats->rx_over_errors++;
	अन्यथा अगर (status & (SHORT | LIMIT))
		stats->rx_length_errors++;
	अन्यथा अगर (status & (MIIER | NIBON | COLON))
		stats->rx_frame_errors++;

	stats->rx_errors++;
	वापस -1;
पूर्ण

अटल पूर्णांक sis190_rx_पूर्णांकerrupt(काष्ठा net_device *dev,
			       काष्ठा sis190_निजी *tp, व्योम __iomem *ioaddr)
अणु
	काष्ठा net_device_stats *stats = &dev->stats;
	u32 rx_left, cur_rx = tp->cur_rx;
	u32 delta, count;

	rx_left = NUM_RX_DESC + tp->dirty_rx - cur_rx;
	rx_left = sis190_rx_quota(rx_left, (u32) dev->quota);

	क्रम (; rx_left > 0; rx_left--, cur_rx++) अणु
		अचिन्हित पूर्णांक entry = cur_rx % NUM_RX_DESC;
		काष्ठा RxDesc *desc = tp->RxDescRing + entry;
		u32 status;

		अगर (le32_to_cpu(desc->status) & OWNbit)
			अवरोध;

		status = le32_to_cpu(desc->PSize);

		//netअगर_info(tp, पूर्णांकr, dev, "Rx PSize = %08x\n", status);

		अगर (sis190_rx_pkt_err(status, stats) < 0)
			sis190_give_to_asic(desc, tp->rx_buf_sz);
		अन्यथा अणु
			काष्ठा sk_buff *skb = tp->Rx_skbuff[entry];
			dma_addr_t addr = le32_to_cpu(desc->addr);
			पूर्णांक pkt_size = (status & RxSizeMask) - 4;
			काष्ठा pci_dev *pdev = tp->pci_dev;

			अगर (unlikely(pkt_size > tp->rx_buf_sz)) अणु
				netअगर_info(tp, पूर्णांकr, dev,
					   "(frag) status = %08x\n", status);
				stats->rx_dropped++;
				stats->rx_length_errors++;
				sis190_give_to_asic(desc, tp->rx_buf_sz);
				जारी;
			पूर्ण


			अगर (sis190_try_rx_copy(tp, &skb, pkt_size, addr)) अणु
				dma_sync_single_क्रम_device(&pdev->dev, addr,
							   tp->rx_buf_sz,
							   DMA_FROM_DEVICE);
				sis190_give_to_asic(desc, tp->rx_buf_sz);
			पूर्ण अन्यथा अणु
				dma_unmap_single(&pdev->dev, addr,
						 tp->rx_buf_sz,
						 DMA_FROM_DEVICE);
				tp->Rx_skbuff[entry] = शून्य;
				sis190_make_unusable_by_asic(desc);
			पूर्ण

			skb_put(skb, pkt_size);
			skb->protocol = eth_type_trans(skb, dev);

			sis190_rx_skb(skb);

			stats->rx_packets++;
			stats->rx_bytes += pkt_size;
			अगर ((status & BCAST) == MCAST)
				stats->multicast++;
		पूर्ण
	पूर्ण
	count = cur_rx - tp->cur_rx;
	tp->cur_rx = cur_rx;

	delta = sis190_rx_fill(tp, dev, tp->dirty_rx, tp->cur_rx);
	अगर (!delta && count)
		netअगर_info(tp, पूर्णांकr, dev, "no Rx buffer allocated\n");
	tp->dirty_rx += delta;

	अगर ((tp->dirty_rx + NUM_RX_DESC) == tp->cur_rx)
		netअगर_emerg(tp, पूर्णांकr, dev, "Rx buffers exhausted\n");

	वापस count;
पूर्ण

अटल व्योम sis190_unmap_tx_skb(काष्ठा pci_dev *pdev, काष्ठा sk_buff *skb,
				काष्ठा TxDesc *desc)
अणु
	अचिन्हित पूर्णांक len;

	len = skb->len < ETH_ZLEN ? ETH_ZLEN : skb->len;

	dma_unmap_single(&pdev->dev, le32_to_cpu(desc->addr), len,
			 DMA_TO_DEVICE);

	स_रखो(desc, 0x00, माप(*desc));
पूर्ण

अटल अंतरभूत पूर्णांक sis190_tx_pkt_err(u32 status, काष्ठा net_device_stats *stats)
अणु
#घोषणा TxErrMask	(WND | TABRT | FIFO | LINK)

	अगर (!unlikely(status & TxErrMask))
		वापस 0;

	अगर (status & WND)
		stats->tx_winकरोw_errors++;
	अगर (status & TABRT)
		stats->tx_पातed_errors++;
	अगर (status & FIFO)
		stats->tx_fअगरo_errors++;
	अगर (status & LINK)
		stats->tx_carrier_errors++;

	stats->tx_errors++;

	वापस -1;
पूर्ण

अटल व्योम sis190_tx_पूर्णांकerrupt(काष्ठा net_device *dev,
				काष्ठा sis190_निजी *tp, व्योम __iomem *ioaddr)
अणु
	काष्ठा net_device_stats *stats = &dev->stats;
	u32 pending, dirty_tx = tp->dirty_tx;
	/*
	 * It would not be needed अगर queueing was allowed to be enabled
	 * again too early (hपूर्णांक: think preempt and unघड़ीed smp प्रणालीs).
	 */
	अचिन्हित पूर्णांक queue_stopped;

	smp_rmb();
	pending = tp->cur_tx - dirty_tx;
	queue_stopped = (pending == NUM_TX_DESC);

	क्रम (; pending; pending--, dirty_tx++) अणु
		अचिन्हित पूर्णांक entry = dirty_tx % NUM_TX_DESC;
		काष्ठा TxDesc *txd = tp->TxDescRing + entry;
		u32 status = le32_to_cpu(txd->status);
		काष्ठा sk_buff *skb;

		अगर (status & OWNbit)
			अवरोध;

		skb = tp->Tx_skbuff[entry];

		अगर (likely(sis190_tx_pkt_err(status, stats) == 0)) अणु
			stats->tx_packets++;
			stats->tx_bytes += skb->len;
			stats->collisions += ((status & ColCountMask) - 1);
		पूर्ण

		sis190_unmap_tx_skb(tp->pci_dev, skb, txd);
		tp->Tx_skbuff[entry] = शून्य;
		dev_consume_skb_irq(skb);
	पूर्ण

	अगर (tp->dirty_tx != dirty_tx) अणु
		tp->dirty_tx = dirty_tx;
		smp_wmb();
		अगर (queue_stopped)
			netअगर_wake_queue(dev);
	पूर्ण
पूर्ण

/*
 * The पूर्णांकerrupt handler करोes all of the Rx thपढ़ो work and cleans up after
 * the Tx thपढ़ो.
 */
अटल irqवापस_t sis190_irq(पूर्णांक irq, व्योम *__dev)
अणु
	काष्ठा net_device *dev = __dev;
	काष्ठा sis190_निजी *tp = netdev_priv(dev);
	व्योम __iomem *ioaddr = tp->mmio_addr;
	अचिन्हित पूर्णांक handled = 0;
	u32 status;

	status = SIS_R32(IntrStatus);

	अगर ((status == 0xffffffff) || !status)
		जाओ out;

	handled = 1;

	अगर (unlikely(!netअगर_running(dev))) अणु
		sis190_asic_करोwn(ioaddr);
		जाओ out;
	पूर्ण

	SIS_W32(IntrStatus, status);

//	netअगर_info(tp, पूर्णांकr, dev, "status = %08x\n", status);

	अगर (status & LinkChange) अणु
		netअगर_info(tp, पूर्णांकr, dev, "link change\n");
		del_समयr(&tp->समयr);
		schedule_work(&tp->phy_task);
	पूर्ण

	अगर (status & RxQInt)
		sis190_rx_पूर्णांकerrupt(dev, tp, ioaddr);

	अगर (status & TxQ0Int)
		sis190_tx_पूर्णांकerrupt(dev, tp, ioaddr);
out:
	वापस IRQ_RETVAL(handled);
पूर्ण

#अगर_घोषित CONFIG_NET_POLL_CONTROLLER
अटल व्योम sis190_netpoll(काष्ठा net_device *dev)
अणु
	काष्ठा sis190_निजी *tp = netdev_priv(dev);
	स्थिर पूर्णांक irq = tp->pci_dev->irq;

	disable_irq(irq);
	sis190_irq(irq, dev);
	enable_irq(irq);
पूर्ण
#पूर्ण_अगर

अटल व्योम sis190_मुक्त_rx_skb(काष्ठा sis190_निजी *tp,
			       काष्ठा sk_buff **sk_buff, काष्ठा RxDesc *desc)
अणु
	काष्ठा pci_dev *pdev = tp->pci_dev;

	dma_unmap_single(&pdev->dev, le32_to_cpu(desc->addr), tp->rx_buf_sz,
			 DMA_FROM_DEVICE);
	dev_kमुक्त_skb(*sk_buff);
	*sk_buff = शून्य;
	sis190_make_unusable_by_asic(desc);
पूर्ण

अटल व्योम sis190_rx_clear(काष्ठा sis190_निजी *tp)
अणु
	अचिन्हित पूर्णांक i;

	क्रम (i = 0; i < NUM_RX_DESC; i++) अणु
		अगर (!tp->Rx_skbuff[i])
			जारी;
		sis190_मुक्त_rx_skb(tp, tp->Rx_skbuff + i, tp->RxDescRing + i);
	पूर्ण
पूर्ण

अटल व्योम sis190_init_ring_indexes(काष्ठा sis190_निजी *tp)
अणु
	tp->dirty_tx = tp->dirty_rx = tp->cur_tx = tp->cur_rx = 0;
पूर्ण

अटल पूर्णांक sis190_init_ring(काष्ठा net_device *dev)
अणु
	काष्ठा sis190_निजी *tp = netdev_priv(dev);

	sis190_init_ring_indexes(tp);

	स_रखो(tp->Tx_skbuff, 0x0, NUM_TX_DESC * माप(काष्ठा sk_buff *));
	स_रखो(tp->Rx_skbuff, 0x0, NUM_RX_DESC * माप(काष्ठा sk_buff *));

	अगर (sis190_rx_fill(tp, dev, 0, NUM_RX_DESC) != NUM_RX_DESC)
		जाओ err_rx_clear;

	sis190_mark_as_last_descriptor(tp->RxDescRing + NUM_RX_DESC - 1);

	वापस 0;

err_rx_clear:
	sis190_rx_clear(tp);
	वापस -ENOMEM;
पूर्ण

अटल व्योम sis190_set_rx_mode(काष्ठा net_device *dev)
अणु
	काष्ठा sis190_निजी *tp = netdev_priv(dev);
	व्योम __iomem *ioaddr = tp->mmio_addr;
	अचिन्हित दीर्घ flags;
	u32 mc_filter[2];	/* Multicast hash filter */
	u16 rx_mode;

	अगर (dev->flags & IFF_PROMISC) अणु
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
			पूर्णांक bit_nr =
				ether_crc(ETH_ALEN, ha->addr) & 0x3f;
			mc_filter[bit_nr >> 5] |= 1 << (bit_nr & 31);
			rx_mode |= AcceptMulticast;
		पूर्ण
	पूर्ण

	spin_lock_irqsave(&tp->lock, flags);

	SIS_W16(RxMacControl, rx_mode | 0x2);
	SIS_W32(RxHashTable, mc_filter[0]);
	SIS_W32(RxHashTable + 4, mc_filter[1]);

	spin_unlock_irqrestore(&tp->lock, flags);
पूर्ण

अटल व्योम sis190_soft_reset(व्योम __iomem *ioaddr)
अणु
	SIS_W32(IntrControl, 0x8000);
	SIS_PCI_COMMIT();
	SIS_W32(IntrControl, 0x0);
	sis190_asic_करोwn(ioaddr);
पूर्ण

अटल व्योम sis190_hw_start(काष्ठा net_device *dev)
अणु
	काष्ठा sis190_निजी *tp = netdev_priv(dev);
	व्योम __iomem *ioaddr = tp->mmio_addr;

	sis190_soft_reset(ioaddr);

	SIS_W32(TxDescStartAddr, tp->tx_dma);
	SIS_W32(RxDescStartAddr, tp->rx_dma);

	SIS_W32(IntrStatus, 0xffffffff);
	SIS_W32(IntrMask, 0x0);
	SIS_W32(GMIIControl, 0x0);
	SIS_W32(TxMacControl, 0x60);
	SIS_W16(RxMacControl, 0x02);
	SIS_W32(RxHashTable, 0x0);
	SIS_W32(0x6c, 0x0);
	SIS_W32(RxWolCtrl, 0x0);
	SIS_W32(RxWolData, 0x0);

	SIS_PCI_COMMIT();

	sis190_set_rx_mode(dev);

	/* Enable all known पूर्णांकerrupts by setting the पूर्णांकerrupt mask. */
	SIS_W32(IntrMask, sis190_पूर्णांकr_mask);

	SIS_W32(TxControl, 0x1a00 | CmdTxEnb);
	SIS_W32(RxControl, 0x1a1d);

	netअगर_start_queue(dev);
पूर्ण

अटल व्योम sis190_phy_task(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा sis190_निजी *tp =
		container_of(work, काष्ठा sis190_निजी, phy_task);
	काष्ठा net_device *dev = tp->dev;
	व्योम __iomem *ioaddr = tp->mmio_addr;
	पूर्णांक phy_id = tp->mii_अगर.phy_id;
	u16 val;

	rtnl_lock();

	अगर (!netअगर_running(dev))
		जाओ out_unlock;

	val = mdio_पढ़ो(ioaddr, phy_id, MII_BMCR);
	अगर (val & BMCR_RESET) अणु
		// FIXME: needlessly high ?  -- FR 02/07/2005
		mod_समयr(&tp->समयr, jअगरfies + HZ/10);
		जाओ out_unlock;
	पूर्ण

	val = mdio_पढ़ो_latched(ioaddr, phy_id, MII_BMSR);
	अगर (!(val & BMSR_ANEGCOMPLETE) && tp->link_status != LNK_AUTONEG) अणु
		netअगर_carrier_off(dev);
		netअगर_warn(tp, link, dev, "auto-negotiating...\n");
		tp->link_status = LNK_AUTONEG;
	पूर्ण अन्यथा अगर ((val & BMSR_LSTATUS) && tp->link_status != LNK_ON) अणु
		/* Rejoice ! */
		काष्ठा अणु
			पूर्णांक val;
			u32 ctl;
			स्थिर अक्षर *msg;
		पूर्ण reg31[] = अणु
			अणु LPA_1000FULL, 0x07000c00 | 0x00001000,
				"1000 Mbps Full Duplex" पूर्ण,
			अणु LPA_1000HALF, 0x07000c00,
				"1000 Mbps Half Duplex" पूर्ण,
			अणु LPA_100FULL, 0x04000800 | 0x00001000,
				"100 Mbps Full Duplex" पूर्ण,
			अणु LPA_100HALF, 0x04000800,
				"100 Mbps Half Duplex" पूर्ण,
			अणु LPA_10FULL, 0x04000400 | 0x00001000,
				"10 Mbps Full Duplex" पूर्ण,
			अणु LPA_10HALF, 0x04000400,
				"10 Mbps Half Duplex" पूर्ण,
			अणु 0, 0x04000400, "unknown" पूर्ण
		पूर्ण, *p = शून्य;
		u16 adv, स्वतःexp, gigadv, gigrec;

		val = mdio_पढ़ो(ioaddr, phy_id, 0x1f);
		netअगर_info(tp, link, dev, "mii ext = %04x\n", val);

		val = mdio_पढ़ो(ioaddr, phy_id, MII_LPA);
		adv = mdio_पढ़ो(ioaddr, phy_id, MII_ADVERTISE);
		स्वतःexp = mdio_पढ़ो(ioaddr, phy_id, MII_EXPANSION);
		netअगर_info(tp, link, dev, "mii lpa=%04x adv=%04x exp=%04x\n",
			   val, adv, स्वतःexp);

		अगर (val & LPA_NPAGE && स्वतःexp & EXPANSION_NWAY) अणु
			/* check क्रम gigabit speed */
			gigadv = mdio_पढ़ो(ioaddr, phy_id, MII_CTRL1000);
			gigrec = mdio_पढ़ो(ioaddr, phy_id, MII_STAT1000);
			val = (gigadv & (gigrec >> 2));
			अगर (val & ADVERTISE_1000FULL)
				p = reg31;
			अन्यथा अगर (val & ADVERTISE_1000HALF)
				p = reg31 + 1;
		पूर्ण
		अगर (!p) अणु
			val &= adv;

			क्रम (p = reg31; p->val; p++) अणु
				अगर ((val & p->val) == p->val)
					अवरोध;
			पूर्ण
		पूर्ण

		p->ctl |= SIS_R32(StationControl) & ~0x0f001c00;

		अगर ((tp->features & F_HAS_RGMII) &&
		    (tp->features & F_PHY_BCM5461)) अणु
			// Set Tx Delay in RGMII mode.
			mdio_ग_लिखो(ioaddr, phy_id, 0x18, 0xf1c7);
			udelay(200);
			mdio_ग_लिखो(ioaddr, phy_id, 0x1c, 0x8c00);
			p->ctl |= 0x03000000;
		पूर्ण

		SIS_W32(StationControl, p->ctl);

		अगर (tp->features & F_HAS_RGMII) अणु
			SIS_W32(RGDelay, 0x0441);
			SIS_W32(RGDelay, 0x0440);
		पूर्ण

		tp->negotiated_lpa = p->val;

		netअगर_info(tp, link, dev, "link on %s mode\n", p->msg);
		netअगर_carrier_on(dev);
		tp->link_status = LNK_ON;
	पूर्ण अन्यथा अगर (!(val & BMSR_LSTATUS) && tp->link_status != LNK_AUTONEG)
		tp->link_status = LNK_OFF;
	mod_समयr(&tp->समयr, jअगरfies + SIS190_PHY_TIMEOUT);

out_unlock:
	rtnl_unlock();
पूर्ण

अटल व्योम sis190_phy_समयr(काष्ठा समयr_list *t)
अणु
	काष्ठा sis190_निजी *tp = from_समयr(tp, t, समयr);
	काष्ठा net_device *dev = tp->dev;

	अगर (likely(netअगर_running(dev)))
		schedule_work(&tp->phy_task);
पूर्ण

अटल अंतरभूत व्योम sis190_delete_समयr(काष्ठा net_device *dev)
अणु
	काष्ठा sis190_निजी *tp = netdev_priv(dev);

	del_समयr_sync(&tp->समयr);
पूर्ण

अटल अंतरभूत व्योम sis190_request_समयr(काष्ठा net_device *dev)
अणु
	काष्ठा sis190_निजी *tp = netdev_priv(dev);
	काष्ठा समयr_list *समयr = &tp->समयr;

	समयr_setup(समयr, sis190_phy_समयr, 0);
	समयr->expires = jअगरfies + SIS190_PHY_TIMEOUT;
	add_समयr(समयr);
पूर्ण

अटल व्योम sis190_set_rxbufsize(काष्ठा sis190_निजी *tp,
				 काष्ठा net_device *dev)
अणु
	अचिन्हित पूर्णांक mtu = dev->mtu;

	tp->rx_buf_sz = (mtu > RX_BUF_SIZE) ? mtu + ETH_HLEN + 8 : RX_BUF_SIZE;
	/* RxDesc->size has a licence to समाप्त the lower bits */
	अगर (tp->rx_buf_sz & 0x07) अणु
		tp->rx_buf_sz += 8;
		tp->rx_buf_sz &= RX_BUF_MASK;
	पूर्ण
पूर्ण

अटल पूर्णांक sis190_खोलो(काष्ठा net_device *dev)
अणु
	काष्ठा sis190_निजी *tp = netdev_priv(dev);
	काष्ठा pci_dev *pdev = tp->pci_dev;
	पूर्णांक rc = -ENOMEM;

	sis190_set_rxbufsize(tp, dev);

	/*
	 * Rx and Tx descriptors need 256 bytes alignment.
	 * pci_alloc_consistent() guarantees a stronger alignment.
	 */
	tp->TxDescRing = dma_alloc_coherent(&pdev->dev, TX_RING_BYTES,
					    &tp->tx_dma, GFP_KERNEL);
	अगर (!tp->TxDescRing)
		जाओ out;

	tp->RxDescRing = dma_alloc_coherent(&pdev->dev, RX_RING_BYTES,
					    &tp->rx_dma, GFP_KERNEL);
	अगर (!tp->RxDescRing)
		जाओ err_मुक्त_tx_0;

	rc = sis190_init_ring(dev);
	अगर (rc < 0)
		जाओ err_मुक्त_rx_1;

	sis190_request_समयr(dev);

	rc = request_irq(pdev->irq, sis190_irq, IRQF_SHARED, dev->name, dev);
	अगर (rc < 0)
		जाओ err_release_समयr_2;

	sis190_hw_start(dev);
out:
	वापस rc;

err_release_समयr_2:
	sis190_delete_समयr(dev);
	sis190_rx_clear(tp);
err_मुक्त_rx_1:
	dma_मुक्त_coherent(&pdev->dev, RX_RING_BYTES, tp->RxDescRing,
			  tp->rx_dma);
err_मुक्त_tx_0:
	dma_मुक्त_coherent(&pdev->dev, TX_RING_BYTES, tp->TxDescRing,
			  tp->tx_dma);
	जाओ out;
पूर्ण

अटल व्योम sis190_tx_clear(काष्ठा sis190_निजी *tp)
अणु
	अचिन्हित पूर्णांक i;

	क्रम (i = 0; i < NUM_TX_DESC; i++) अणु
		काष्ठा sk_buff *skb = tp->Tx_skbuff[i];

		अगर (!skb)
			जारी;

		sis190_unmap_tx_skb(tp->pci_dev, skb, tp->TxDescRing + i);
		tp->Tx_skbuff[i] = शून्य;
		dev_kमुक्त_skb(skb);

		tp->dev->stats.tx_dropped++;
	पूर्ण
	tp->cur_tx = tp->dirty_tx = 0;
पूर्ण

अटल व्योम sis190_करोwn(काष्ठा net_device *dev)
अणु
	काष्ठा sis190_निजी *tp = netdev_priv(dev);
	व्योम __iomem *ioaddr = tp->mmio_addr;
	अचिन्हित पूर्णांक poll_locked = 0;

	sis190_delete_समयr(dev);

	netअगर_stop_queue(dev);

	करो अणु
		spin_lock_irq(&tp->lock);

		sis190_asic_करोwn(ioaddr);

		spin_unlock_irq(&tp->lock);

		synchronize_irq(tp->pci_dev->irq);

		अगर (!poll_locked)
			poll_locked++;

		synchronize_rcu();

	पूर्ण जबतक (SIS_R32(IntrMask));

	sis190_tx_clear(tp);
	sis190_rx_clear(tp);
पूर्ण

अटल पूर्णांक sis190_बंद(काष्ठा net_device *dev)
अणु
	काष्ठा sis190_निजी *tp = netdev_priv(dev);
	काष्ठा pci_dev *pdev = tp->pci_dev;

	sis190_करोwn(dev);

	मुक्त_irq(pdev->irq, dev);

	dma_मुक्त_coherent(&pdev->dev, TX_RING_BYTES, tp->TxDescRing,
			  tp->tx_dma);
	dma_मुक्त_coherent(&pdev->dev, RX_RING_BYTES, tp->RxDescRing,
			  tp->rx_dma);

	tp->TxDescRing = शून्य;
	tp->RxDescRing = शून्य;

	वापस 0;
पूर्ण

अटल netdev_tx_t sis190_start_xmit(काष्ठा sk_buff *skb,
				     काष्ठा net_device *dev)
अणु
	काष्ठा sis190_निजी *tp = netdev_priv(dev);
	व्योम __iomem *ioaddr = tp->mmio_addr;
	u32 len, entry, dirty_tx;
	काष्ठा TxDesc *desc;
	dma_addr_t mapping;

	अगर (unlikely(skb->len < ETH_ZLEN)) अणु
		अगर (skb_padto(skb, ETH_ZLEN)) अणु
			dev->stats.tx_dropped++;
			जाओ out;
		पूर्ण
		len = ETH_ZLEN;
	पूर्ण अन्यथा अणु
		len = skb->len;
	पूर्ण

	entry = tp->cur_tx % NUM_TX_DESC;
	desc = tp->TxDescRing + entry;

	अगर (unlikely(le32_to_cpu(desc->status) & OWNbit)) अणु
		netअगर_stop_queue(dev);
		netअगर_err(tp, tx_err, dev,
			  "BUG! Tx Ring full when queue awake!\n");
		वापस NETDEV_TX_BUSY;
	पूर्ण

	mapping = dma_map_single(&tp->pci_dev->dev, skb->data, len,
				 DMA_TO_DEVICE);
	अगर (dma_mapping_error(&tp->pci_dev->dev, mapping)) अणु
		netअगर_err(tp, tx_err, dev,
				"PCI mapping failed, dropping packet");
		वापस NETDEV_TX_BUSY;
	पूर्ण

	tp->Tx_skbuff[entry] = skb;

	desc->PSize = cpu_to_le32(len);
	desc->addr = cpu_to_le32(mapping);

	desc->size = cpu_to_le32(len);
	अगर (entry == (NUM_TX_DESC - 1))
		desc->size |= cpu_to_le32(RingEnd);

	wmb();

	desc->status = cpu_to_le32(OWNbit | INTbit | DEFbit | CRCbit | PADbit);
	अगर (tp->negotiated_lpa & (LPA_1000HALF | LPA_100HALF | LPA_10HALF)) अणु
		/* Half Duplex */
		desc->status |= cpu_to_le32(COLEN | CRSEN | BKFEN);
		अगर (tp->negotiated_lpa & (LPA_1000HALF | LPA_1000FULL))
			desc->status |= cpu_to_le32(EXTEN | BSTEN); /* gigabit HD */
	पूर्ण

	tp->cur_tx++;

	smp_wmb();

	SIS_W32(TxControl, 0x1a00 | CmdReset | CmdTxEnb);

	dirty_tx = tp->dirty_tx;
	अगर ((tp->cur_tx - NUM_TX_DESC) == dirty_tx) अणु
		netअगर_stop_queue(dev);
		smp_rmb();
		अगर (dirty_tx != tp->dirty_tx)
			netअगर_wake_queue(dev);
	पूर्ण
out:
	वापस NETDEV_TX_OK;
पूर्ण

अटल व्योम sis190_मुक्त_phy(काष्ठा list_head *first_phy)
अणु
	काष्ठा sis190_phy *cur, *next;

	list_क्रम_each_entry_safe(cur, next, first_phy, list) अणु
		kमुक्त(cur);
	पूर्ण
पूर्ण

/**
 *	sis190_शेष_phy - Select शेष PHY क्रम sis190 mac.
 *	@dev: the net device to probe क्रम
 *
 *	Select first detected PHY with link as शेष.
 *	If no one is link on, select PHY whose types is HOME as शेष.
 *	If HOME करोesn't exist, select LAN.
 */
अटल u16 sis190_शेष_phy(काष्ठा net_device *dev)
अणु
	काष्ठा sis190_phy *phy, *phy_home, *phy_शेष, *phy_lan;
	काष्ठा sis190_निजी *tp = netdev_priv(dev);
	काष्ठा mii_अगर_info *mii_अगर = &tp->mii_अगर;
	व्योम __iomem *ioaddr = tp->mmio_addr;
	u16 status;

	phy_home = phy_शेष = phy_lan = शून्य;

	list_क्रम_each_entry(phy, &tp->first_phy, list) अणु
		status = mdio_पढ़ो_latched(ioaddr, phy->phy_id, MII_BMSR);

		// Link ON & Not select शेष PHY & not ghost PHY.
		अगर ((status & BMSR_LSTATUS) &&
		    !phy_शेष &&
		    (phy->type != UNKNOWN)) अणु
			phy_शेष = phy;
		पूर्ण अन्यथा अणु
			status = mdio_पढ़ो(ioaddr, phy->phy_id, MII_BMCR);
			mdio_ग_लिखो(ioaddr, phy->phy_id, MII_BMCR,
				   status | BMCR_ANENABLE | BMCR_ISOLATE);
			अगर (phy->type == HOME)
				phy_home = phy;
			अन्यथा अगर (phy->type == LAN)
				phy_lan = phy;
		पूर्ण
	पूर्ण

	अगर (!phy_शेष) अणु
		अगर (phy_home)
			phy_शेष = phy_home;
		अन्यथा अगर (phy_lan)
			phy_शेष = phy_lan;
		अन्यथा
			phy_शेष = list_first_entry(&tp->first_phy,
						 काष्ठा sis190_phy, list);
	पूर्ण

	अगर (mii_अगर->phy_id != phy_शेष->phy_id) अणु
		mii_अगर->phy_id = phy_शेष->phy_id;
		अगर (netअगर_msg_probe(tp))
			pr_info("%s: Using transceiver at address %d as default\n",
				pci_name(tp->pci_dev), mii_अगर->phy_id);
	पूर्ण

	status = mdio_पढ़ो(ioaddr, mii_अगर->phy_id, MII_BMCR);
	status &= (~BMCR_ISOLATE);

	mdio_ग_लिखो(ioaddr, mii_अगर->phy_id, MII_BMCR, status);
	status = mdio_पढ़ो_latched(ioaddr, mii_अगर->phy_id, MII_BMSR);

	वापस status;
पूर्ण

अटल व्योम sis190_init_phy(काष्ठा net_device *dev, काष्ठा sis190_निजी *tp,
			    काष्ठा sis190_phy *phy, अचिन्हित पूर्णांक phy_id,
			    u16 mii_status)
अणु
	व्योम __iomem *ioaddr = tp->mmio_addr;
	काष्ठा mii_chip_info *p;

	INIT_LIST_HEAD(&phy->list);
	phy->status = mii_status;
	phy->phy_id = phy_id;

	phy->id[0] = mdio_पढ़ो(ioaddr, phy_id, MII_PHYSID1);
	phy->id[1] = mdio_पढ़ो(ioaddr, phy_id, MII_PHYSID2);

	क्रम (p = mii_chip_table; p->type; p++) अणु
		अगर ((p->id[0] == phy->id[0]) &&
		    (p->id[1] == (phy->id[1] & 0xfff0))) अणु
			अवरोध;
		पूर्ण
	पूर्ण

	अगर (p->id[1]) अणु
		phy->type = (p->type == MIX) ?
			((mii_status & (BMSR_100FULL | BMSR_100HALF)) ?
				LAN : HOME) : p->type;
		tp->features |= p->feature;
		अगर (netअगर_msg_probe(tp))
			pr_info("%s: %s transceiver at address %d\n",
				pci_name(tp->pci_dev), p->name, phy_id);
	पूर्ण अन्यथा अणु
		phy->type = UNKNOWN;
		अगर (netअगर_msg_probe(tp))
			pr_info("%s: unknown PHY 0x%x:0x%x transceiver at address %d\n",
				pci_name(tp->pci_dev),
				phy->id[0], (phy->id[1] & 0xfff0), phy_id);
	पूर्ण
पूर्ण

अटल व्योम sis190_mii_probe_88e1111_fixup(काष्ठा sis190_निजी *tp)
अणु
	अगर (tp->features & F_PHY_88E1111) अणु
		व्योम __iomem *ioaddr = tp->mmio_addr;
		पूर्णांक phy_id = tp->mii_अगर.phy_id;
		u16 reg[2][2] = अणु
			अणु 0x808b, 0x0ce1 पूर्ण,
			अणु 0x808f, 0x0c60 पूर्ण
		पूर्ण, *p;

		p = (tp->features & F_HAS_RGMII) ? reg[0] : reg[1];

		mdio_ग_लिखो(ioaddr, phy_id, 0x1b, p[0]);
		udelay(200);
		mdio_ग_लिखो(ioaddr, phy_id, 0x14, p[1]);
		udelay(200);
	पूर्ण
पूर्ण

/**
 *	sis190_mii_probe - Probe MII PHY क्रम sis190
 *	@dev: the net device to probe क्रम
 *
 *	Search क्रम total of 32 possible mii phy addresses.
 *	Identअगरy and set current phy अगर found one,
 *	वापस error अगर it failed to found.
 */
अटल पूर्णांक sis190_mii_probe(काष्ठा net_device *dev)
अणु
	काष्ठा sis190_निजी *tp = netdev_priv(dev);
	काष्ठा mii_अगर_info *mii_अगर = &tp->mii_अगर;
	व्योम __iomem *ioaddr = tp->mmio_addr;
	पूर्णांक phy_id;
	पूर्णांक rc = 0;

	INIT_LIST_HEAD(&tp->first_phy);

	क्रम (phy_id = 0; phy_id < PHY_MAX_ADDR; phy_id++) अणु
		काष्ठा sis190_phy *phy;
		u16 status;

		status = mdio_पढ़ो_latched(ioaddr, phy_id, MII_BMSR);

		// Try next mii अगर the current one is not accessible.
		अगर (status == 0xffff || status == 0x0000)
			जारी;

		phy = kदो_स्मृति(माप(*phy), GFP_KERNEL);
		अगर (!phy) अणु
			sis190_मुक्त_phy(&tp->first_phy);
			rc = -ENOMEM;
			जाओ out;
		पूर्ण

		sis190_init_phy(dev, tp, phy, phy_id, status);

		list_add(&tp->first_phy, &phy->list);
	पूर्ण

	अगर (list_empty(&tp->first_phy)) अणु
		अगर (netअगर_msg_probe(tp))
			pr_info("%s: No MII transceivers found!\n",
				pci_name(tp->pci_dev));
		rc = -EIO;
		जाओ out;
	पूर्ण

	/* Select शेष PHY क्रम mac */
	sis190_शेष_phy(dev);

	sis190_mii_probe_88e1111_fixup(tp);

	mii_अगर->dev = dev;
	mii_अगर->mdio_पढ़ो = __mdio_पढ़ो;
	mii_अगर->mdio_ग_लिखो = __mdio_ग_लिखो;
	mii_अगर->phy_id_mask = PHY_ID_ANY;
	mii_अगर->reg_num_mask = MII_REG_ANY;
out:
	वापस rc;
पूर्ण

अटल व्योम sis190_mii_हटाओ(काष्ठा net_device *dev)
अणु
	काष्ठा sis190_निजी *tp = netdev_priv(dev);

	sis190_मुक्त_phy(&tp->first_phy);
पूर्ण

अटल व्योम sis190_release_board(काष्ठा pci_dev *pdev)
अणु
	काष्ठा net_device *dev = pci_get_drvdata(pdev);
	काष्ठा sis190_निजी *tp = netdev_priv(dev);

	iounmap(tp->mmio_addr);
	pci_release_regions(pdev);
	pci_disable_device(pdev);
	मुक्त_netdev(dev);
पूर्ण

अटल काष्ठा net_device *sis190_init_board(काष्ठा pci_dev *pdev)
अणु
	काष्ठा sis190_निजी *tp;
	काष्ठा net_device *dev;
	व्योम __iomem *ioaddr;
	पूर्णांक rc;

	dev = alloc_etherdev(माप(*tp));
	अगर (!dev) अणु
		rc = -ENOMEM;
		जाओ err_out_0;
	पूर्ण

	SET_NETDEV_DEV(dev, &pdev->dev);

	tp = netdev_priv(dev);
	tp->dev = dev;
	tp->msg_enable = netअगर_msg_init(debug.msg_enable, SIS190_MSG_DEFAULT);

	rc = pci_enable_device(pdev);
	अगर (rc < 0) अणु
		अगर (netअगर_msg_probe(tp))
			pr_err("%s: enable failure\n", pci_name(pdev));
		जाओ err_मुक्त_dev_1;
	पूर्ण

	rc = -ENODEV;

	अगर (!(pci_resource_flags(pdev, 0) & IORESOURCE_MEM)) अणु
		अगर (netअगर_msg_probe(tp))
			pr_err("%s: region #0 is no MMIO resource\n",
			       pci_name(pdev));
		जाओ err_pci_disable_2;
	पूर्ण
	अगर (pci_resource_len(pdev, 0) < SIS190_REGS_SIZE) अणु
		अगर (netअगर_msg_probe(tp))
			pr_err("%s: invalid PCI region size(s)\n",
			       pci_name(pdev));
		जाओ err_pci_disable_2;
	पूर्ण

	rc = pci_request_regions(pdev, DRV_NAME);
	अगर (rc < 0) अणु
		अगर (netअगर_msg_probe(tp))
			pr_err("%s: could not request regions\n",
			       pci_name(pdev));
		जाओ err_pci_disable_2;
	पूर्ण

	rc = dma_set_mask(&pdev->dev, DMA_BIT_MASK(32));
	अगर (rc < 0) अणु
		अगर (netअगर_msg_probe(tp))
			pr_err("%s: DMA configuration failed\n",
			       pci_name(pdev));
		जाओ err_मुक्त_res_3;
	पूर्ण

	pci_set_master(pdev);

	ioaddr = ioremap(pci_resource_start(pdev, 0), SIS190_REGS_SIZE);
	अगर (!ioaddr) अणु
		अगर (netअगर_msg_probe(tp))
			pr_err("%s: cannot remap MMIO, aborting\n",
			       pci_name(pdev));
		rc = -EIO;
		जाओ err_मुक्त_res_3;
	पूर्ण

	tp->pci_dev = pdev;
	tp->mmio_addr = ioaddr;
	tp->link_status = LNK_OFF;

	sis190_irq_mask_and_ack(ioaddr);

	sis190_soft_reset(ioaddr);
out:
	वापस dev;

err_मुक्त_res_3:
	pci_release_regions(pdev);
err_pci_disable_2:
	pci_disable_device(pdev);
err_मुक्त_dev_1:
	मुक्त_netdev(dev);
err_out_0:
	dev = ERR_PTR(rc);
	जाओ out;
पूर्ण

अटल व्योम sis190_tx_समयout(काष्ठा net_device *dev, अचिन्हित पूर्णांक txqueue)
अणु
	काष्ठा sis190_निजी *tp = netdev_priv(dev);
	व्योम __iomem *ioaddr = tp->mmio_addr;
	u8 पंचांगp8;

	/* Disable Tx, अगर not alपढ़ोy */
	पंचांगp8 = SIS_R8(TxControl);
	अगर (पंचांगp8 & CmdTxEnb)
		SIS_W8(TxControl, पंचांगp8 & ~CmdTxEnb);

	netअगर_info(tp, tx_err, dev, "Transmit timeout, status %08x %08x\n",
		   SIS_R32(TxControl), SIS_R32(TxSts));

	/* Disable पूर्णांकerrupts by clearing the पूर्णांकerrupt mask. */
	SIS_W32(IntrMask, 0x0000);

	/* Stop a shared पूर्णांकerrupt from scavenging जबतक we are. */
	spin_lock_irq(&tp->lock);
	sis190_tx_clear(tp);
	spin_unlock_irq(&tp->lock);

	/* ...and finally, reset everything. */
	sis190_hw_start(dev);

	netअगर_wake_queue(dev);
पूर्ण

अटल व्योम sis190_set_rgmii(काष्ठा sis190_निजी *tp, u8 reg)
अणु
	tp->features |= (reg & 0x80) ? F_HAS_RGMII : 0;
पूर्ण

अटल पूर्णांक sis190_get_mac_addr_from_eeprom(काष्ठा pci_dev *pdev,
					   काष्ठा net_device *dev)
अणु
	काष्ठा sis190_निजी *tp = netdev_priv(dev);
	व्योम __iomem *ioaddr = tp->mmio_addr;
	u16 sig;
	पूर्णांक i;

	अगर (netअगर_msg_probe(tp))
		pr_info("%s: Read MAC address from EEPROM\n", pci_name(pdev));

	/* Check to see अगर there is a sane EEPROM */
	sig = (u16) sis190_पढ़ो_eeprom(ioaddr, EEPROMSignature);

	अगर ((sig == 0xffff) || (sig == 0x0000)) अणु
		अगर (netअगर_msg_probe(tp))
			pr_info("%s: Error EEPROM read %x\n",
				pci_name(pdev), sig);
		वापस -EIO;
	पूर्ण

	/* Get MAC address from EEPROM */
	क्रम (i = 0; i < ETH_ALEN / 2; i++) अणु
		u16 w = sis190_पढ़ो_eeprom(ioaddr, EEPROMMACAddr + i);

		((__le16 *)dev->dev_addr)[i] = cpu_to_le16(w);
	पूर्ण

	sis190_set_rgmii(tp, sis190_पढ़ो_eeprom(ioaddr, EEPROMInfo));

	वापस 0;
पूर्ण

/**
 *	sis190_get_mac_addr_from_apc - Get MAC address क्रम SiS96x model
 *	@pdev: PCI device
 *	@dev:  network device to get address क्रम
 *
 *	SiS96x model, use APC CMOS RAM to store MAC address.
 *	APC CMOS RAM is accessed through ISA bridge.
 *	MAC address is पढ़ो पूर्णांकo @net_dev->dev_addr.
 */
अटल पूर्णांक sis190_get_mac_addr_from_apc(काष्ठा pci_dev *pdev,
					काष्ठा net_device *dev)
अणु
	अटल स्थिर u16 ids[] = अणु 0x0965, 0x0966, 0x0968 पूर्ण;
	काष्ठा sis190_निजी *tp = netdev_priv(dev);
	काष्ठा pci_dev *isa_bridge;
	u8 reg, पंचांगp8;
	अचिन्हित पूर्णांक i;

	अगर (netअगर_msg_probe(tp))
		pr_info("%s: Read MAC address from APC\n", pci_name(pdev));

	क्रम (i = 0; i < ARRAY_SIZE(ids); i++) अणु
		isa_bridge = pci_get_device(PCI_VENDOR_ID_SI, ids[i], शून्य);
		अगर (isa_bridge)
			अवरोध;
	पूर्ण

	अगर (!isa_bridge) अणु
		अगर (netअगर_msg_probe(tp))
			pr_info("%s: Can not find ISA bridge\n",
				pci_name(pdev));
		वापस -EIO;
	पूर्ण

	/* Enable port 78h & 79h to access APC Registers. */
	pci_पढ़ो_config_byte(isa_bridge, 0x48, &पंचांगp8);
	reg = (पंचांगp8 & ~0x02);
	pci_ग_लिखो_config_byte(isa_bridge, 0x48, reg);
	udelay(50);
	pci_पढ़ो_config_byte(isa_bridge, 0x48, &reg);

        क्रम (i = 0; i < ETH_ALEN; i++) अणु
                outb(0x9 + i, 0x78);
                dev->dev_addr[i] = inb(0x79);
        पूर्ण

	outb(0x12, 0x78);
	reg = inb(0x79);

	sis190_set_rgmii(tp, reg);

	/* Restore the value to ISA Bridge */
	pci_ग_लिखो_config_byte(isa_bridge, 0x48, पंचांगp8);
	pci_dev_put(isa_bridge);

	वापस 0;
पूर्ण

/**
 *      sis190_init_rxfilter - Initialize the Rx filter
 *      @dev: network device to initialize
 *
 *      Set receive filter address to our MAC address
 *      and enable packet filtering.
 */
अटल अंतरभूत व्योम sis190_init_rxfilter(काष्ठा net_device *dev)
अणु
	काष्ठा sis190_निजी *tp = netdev_priv(dev);
	व्योम __iomem *ioaddr = tp->mmio_addr;
	u16 ctl;
	पूर्णांक i;

	ctl = SIS_R16(RxMacControl);
	/*
	 * Disable packet filtering beक्रमe setting filter.
	 * Note: SiS's driver ग_लिखोs 32 bits but RxMacControl is 16 bits
	 * only and followed by RxMacAddr (6 bytes). Strange. -- FR
	 */
	SIS_W16(RxMacControl, ctl & ~0x0f00);

	क्रम (i = 0; i < ETH_ALEN; i++)
		SIS_W8(RxMacAddr + i, dev->dev_addr[i]);

	SIS_W16(RxMacControl, ctl);
	SIS_PCI_COMMIT();
पूर्ण

अटल पूर्णांक sis190_get_mac_addr(काष्ठा pci_dev *pdev, काष्ठा net_device *dev)
अणु
	पूर्णांक rc;

	rc = sis190_get_mac_addr_from_eeprom(pdev, dev);
	अगर (rc < 0) अणु
		u8 reg;

		pci_पढ़ो_config_byte(pdev, 0x73, &reg);

		अगर (reg & 0x00000001)
			rc = sis190_get_mac_addr_from_apc(pdev, dev);
	पूर्ण
	वापस rc;
पूर्ण

अटल व्योम sis190_set_speed_स्वतः(काष्ठा net_device *dev)
अणु
	काष्ठा sis190_निजी *tp = netdev_priv(dev);
	व्योम __iomem *ioaddr = tp->mmio_addr;
	पूर्णांक phy_id = tp->mii_अगर.phy_id;
	पूर्णांक val;

	netअगर_info(tp, link, dev, "Enabling Auto-negotiation\n");

	val = mdio_पढ़ो(ioaddr, phy_id, MII_ADVERTISE);

	// Enable 10/100 Full/Half Mode, leave MII_ADVERTISE bit4:0
	// unchanged.
	mdio_ग_लिखो(ioaddr, phy_id, MII_ADVERTISE, (val & ADVERTISE_SLCT) |
		   ADVERTISE_100FULL | ADVERTISE_10FULL |
		   ADVERTISE_100HALF | ADVERTISE_10HALF);

	// Enable 1000 Full Mode.
	mdio_ग_लिखो(ioaddr, phy_id, MII_CTRL1000, ADVERTISE_1000FULL);

	// Enable स्वतः-negotiation and restart स्वतः-negotiation.
	mdio_ग_लिखो(ioaddr, phy_id, MII_BMCR,
		   BMCR_ANENABLE | BMCR_ANRESTART | BMCR_RESET);
पूर्ण

अटल पूर्णांक sis190_get_link_ksettings(काष्ठा net_device *dev,
				     काष्ठा ethtool_link_ksettings *cmd)
अणु
	काष्ठा sis190_निजी *tp = netdev_priv(dev);

	mii_ethtool_get_link_ksettings(&tp->mii_अगर, cmd);

	वापस 0;
पूर्ण

अटल पूर्णांक sis190_set_link_ksettings(काष्ठा net_device *dev,
				     स्थिर काष्ठा ethtool_link_ksettings *cmd)
अणु
	काष्ठा sis190_निजी *tp = netdev_priv(dev);

	वापस mii_ethtool_set_link_ksettings(&tp->mii_अगर, cmd);
पूर्ण

अटल व्योम sis190_get_drvinfo(काष्ठा net_device *dev,
			       काष्ठा ethtool_drvinfo *info)
अणु
	काष्ठा sis190_निजी *tp = netdev_priv(dev);

	strlcpy(info->driver, DRV_NAME, माप(info->driver));
	strlcpy(info->version, DRV_VERSION, माप(info->version));
	strlcpy(info->bus_info, pci_name(tp->pci_dev),
		माप(info->bus_info));
पूर्ण

अटल पूर्णांक sis190_get_regs_len(काष्ठा net_device *dev)
अणु
	वापस SIS190_REGS_SIZE;
पूर्ण

अटल व्योम sis190_get_regs(काष्ठा net_device *dev, काष्ठा ethtool_regs *regs,
			    व्योम *p)
अणु
	काष्ठा sis190_निजी *tp = netdev_priv(dev);
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&tp->lock, flags);
	स_नकल_fromio(p, tp->mmio_addr, regs->len);
	spin_unlock_irqrestore(&tp->lock, flags);
पूर्ण

अटल पूर्णांक sis190_nway_reset(काष्ठा net_device *dev)
अणु
	काष्ठा sis190_निजी *tp = netdev_priv(dev);

	वापस mii_nway_restart(&tp->mii_अगर);
पूर्ण

अटल u32 sis190_get_msglevel(काष्ठा net_device *dev)
अणु
	काष्ठा sis190_निजी *tp = netdev_priv(dev);

	वापस tp->msg_enable;
पूर्ण

अटल व्योम sis190_set_msglevel(काष्ठा net_device *dev, u32 value)
अणु
	काष्ठा sis190_निजी *tp = netdev_priv(dev);

	tp->msg_enable = value;
पूर्ण

अटल स्थिर काष्ठा ethtool_ops sis190_ethtool_ops = अणु
	.get_drvinfo	= sis190_get_drvinfo,
	.get_regs_len	= sis190_get_regs_len,
	.get_regs	= sis190_get_regs,
	.get_link	= ethtool_op_get_link,
	.get_msglevel	= sis190_get_msglevel,
	.set_msglevel	= sis190_set_msglevel,
	.nway_reset	= sis190_nway_reset,
	.get_link_ksettings = sis190_get_link_ksettings,
	.set_link_ksettings = sis190_set_link_ksettings,
पूर्ण;

अटल पूर्णांक sis190_ioctl(काष्ठा net_device *dev, काष्ठा अगरreq *अगरr, पूर्णांक cmd)
अणु
	काष्ठा sis190_निजी *tp = netdev_priv(dev);

	वापस !netअगर_running(dev) ? -EINVAL :
		generic_mii_ioctl(&tp->mii_अगर, अगर_mii(अगरr), cmd, शून्य);
पूर्ण

अटल पूर्णांक sis190_mac_addr(काष्ठा net_device  *dev, व्योम *p)
अणु
	पूर्णांक rc;

	rc = eth_mac_addr(dev, p);
	अगर (!rc)
		sis190_init_rxfilter(dev);
	वापस rc;
पूर्ण

अटल स्थिर काष्ठा net_device_ops sis190_netdev_ops = अणु
	.nकरो_खोलो		= sis190_खोलो,
	.nकरो_stop		= sis190_बंद,
	.nकरो_करो_ioctl		= sis190_ioctl,
	.nकरो_start_xmit		= sis190_start_xmit,
	.nकरो_tx_समयout		= sis190_tx_समयout,
	.nकरो_set_rx_mode	= sis190_set_rx_mode,
	.nकरो_set_mac_address	= sis190_mac_addr,
	.nकरो_validate_addr	= eth_validate_addr,
#अगर_घोषित CONFIG_NET_POLL_CONTROLLER
	.nकरो_poll_controller	 = sis190_netpoll,
#पूर्ण_अगर
पूर्ण;

अटल पूर्णांक sis190_init_one(काष्ठा pci_dev *pdev,
			   स्थिर काष्ठा pci_device_id *ent)
अणु
	अटल पूर्णांक prपूर्णांकed_version = 0;
	काष्ठा sis190_निजी *tp;
	काष्ठा net_device *dev;
	व्योम __iomem *ioaddr;
	पूर्णांक rc;

	अगर (!prपूर्णांकed_version) अणु
		अगर (netअगर_msg_drv(&debug))
			pr_info(SIS190_DRIVER_NAME " loaded\n");
		prपूर्णांकed_version = 1;
	पूर्ण

	dev = sis190_init_board(pdev);
	अगर (IS_ERR(dev)) अणु
		rc = PTR_ERR(dev);
		जाओ out;
	पूर्ण

	pci_set_drvdata(pdev, dev);

	tp = netdev_priv(dev);
	ioaddr = tp->mmio_addr;

	rc = sis190_get_mac_addr(pdev, dev);
	अगर (rc < 0)
		जाओ err_release_board;

	sis190_init_rxfilter(dev);

	INIT_WORK(&tp->phy_task, sis190_phy_task);

	dev->netdev_ops = &sis190_netdev_ops;

	dev->ethtool_ops = &sis190_ethtool_ops;
	dev->watchकरोg_समयo = SIS190_TX_TIMEOUT;

	spin_lock_init(&tp->lock);

	rc = sis190_mii_probe(dev);
	अगर (rc < 0)
		जाओ err_release_board;

	rc = रेजिस्टर_netdev(dev);
	अगर (rc < 0)
		जाओ err_हटाओ_mii;

	अगर (netअगर_msg_probe(tp)) अणु
		netdev_info(dev, "%s: %s at %p (IRQ: %d), %pM\n",
			    pci_name(pdev),
			    sis_chip_info[ent->driver_data].name,
			    ioaddr, pdev->irq, dev->dev_addr);
		netdev_info(dev, "%s mode.\n",
			    (tp->features & F_HAS_RGMII) ? "RGMII" : "GMII");
	पूर्ण

	netअगर_carrier_off(dev);

	sis190_set_speed_स्वतः(dev);
out:
	वापस rc;

err_हटाओ_mii:
	sis190_mii_हटाओ(dev);
err_release_board:
	sis190_release_board(pdev);
	जाओ out;
पूर्ण

अटल व्योम sis190_हटाओ_one(काष्ठा pci_dev *pdev)
अणु
	काष्ठा net_device *dev = pci_get_drvdata(pdev);
	काष्ठा sis190_निजी *tp = netdev_priv(dev);

	sis190_mii_हटाओ(dev);
	cancel_work_sync(&tp->phy_task);
	unरेजिस्टर_netdev(dev);
	sis190_release_board(pdev);
पूर्ण

अटल काष्ठा pci_driver sis190_pci_driver = अणु
	.name		= DRV_NAME,
	.id_table	= sis190_pci_tbl,
	.probe		= sis190_init_one,
	.हटाओ		= sis190_हटाओ_one,
पूर्ण;

module_pci_driver(sis190_pci_driver);
