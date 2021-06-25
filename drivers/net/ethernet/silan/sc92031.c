<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*  Silan SC92031 PCI Fast Ethernet Adapter driver
 *
 *  Based on venकरोr drivers:
 *  Silan Fast Ethernet Netcard Driver:
 *    MODULE_AUTHOR ("gaoyonghong");
 *    MODULE_DESCRIPTION ("SILAN Fast Ethernet driver");
 *    MODULE_LICENSE("GPL");
 *  8139D Fast Ethernet driver:
 *    (C) 2002 by gaoyonghong
 *    MODULE_AUTHOR ("gaoyonghong");
 *    MODULE_DESCRIPTION ("Rsltek 8139D PCI Fast Ethernet Adapter driver");
 *    MODULE_LICENSE("GPL");
 *  Both are almost identical and seem to be based on pci-skeleton.c
 *
 *  Rewritten क्रम 2.6 by Cesar Eduarकरो Barros
 *
 *  A datasheet क्रम this chip can be found at
 *  http://www.silan.com.cn/english/product/pdf/SC92031AY.pdf 
 */

/* Note about set_mac_address: I करोn't know how to change the hardware
 * matching, so you need to enable IFF_PROMISC when using it.
 */

#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/module.h>
#समावेश <linux/kernel.h>
#समावेश <linux/delay.h>
#समावेश <linux/pci.h>
#समावेश <linux/dma-mapping.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/etherdevice.h>
#समावेश <linux/ethtool.h>
#समावेश <linux/mii.h>
#समावेश <linux/crc32.h>

#समावेश <यंत्र/irq.h>

#घोषणा SC92031_NAME "sc92031"

/* BAR 0 is MMIO, BAR 1 is PIO */
#घोषणा SC92031_USE_PIO	0

/* Maximum number of multicast addresses to filter (vs. Rx-all-multicast). */
अटल पूर्णांक multicast_filter_limit = 64;
module_param(multicast_filter_limit, पूर्णांक, 0);
MODULE_PARM_DESC(multicast_filter_limit,
	"Maximum number of filtered multicast addresses");

अटल पूर्णांक media;
module_param(media, पूर्णांक, 0);
MODULE_PARM_DESC(media, "Media type (0x00 = autodetect,"
	" 0x01 = 10M half, 0x02 = 10M full,"
	" 0x04 = 100M half, 0x08 = 100M full)");

/* Size of the in-memory receive ring. */
#घोषणा  RX_BUF_LEN_IDX  3 /* 0==8K, 1==16K, 2==32K, 3==64K ,4==128K*/
#घोषणा  RX_BUF_LEN	(8192 << RX_BUF_LEN_IDX)

/* Number of Tx descriptor रेजिस्टरs. */
#घोषणा  NUM_TX_DESC	   4

/* max supported ethernet frame size -- must be at least (dev->mtu+14+4).*/
#घोषणा  MAX_ETH_FRAME_SIZE	  1536

/* Size of the Tx bounce buffers -- must be at least (dev->mtu+14+4). */
#घोषणा  TX_BUF_SIZE       MAX_ETH_FRAME_SIZE
#घोषणा  TX_BUF_TOT_LEN    (TX_BUF_SIZE * NUM_TX_DESC)

/* The following settings are log_2(bytes)-4:  0 == 16 bytes .. 6==1024, 7==end of packet. */
#घोषणा  RX_FIFO_THRESH    7     /* Rx buffer level beक्रमe first PCI xfer.  */

/* Time in jअगरfies beक्रमe concluding the transmitter is hung. */
#घोषणा  TX_TIMEOUT     (4*HZ)

#घोषणा  SILAN_STATS_NUM    2    /* number of ETHTOOL_GSTATS */

/* media options */
#घोषणा  AUTOSELECT    0x00
#घोषणा  M10_HALF      0x01
#घोषणा  M10_FULL      0x02
#घोषणा  M100_HALF     0x04
#घोषणा  M100_FULL     0x08

 /* Symbolic offsets to रेजिस्टरs. */
क्रमागत  silan_रेजिस्टरs अणु
   Config0    = 0x00,         // Config0
   Config1    = 0x04,         // Config1
   RxBufWPtr  = 0x08,         // Rx buffer ग_लिखोr poiter
   IntrStatus = 0x0C,         // Interrupt status
   IntrMask   = 0x10,         // Interrupt mask
   RxbufAddr  = 0x14,         // Rx buffer start address
   RxBufRPtr  = 0x18,         // Rx buffer पढ़ो poपूर्णांकer
   Txstatusall = 0x1C,        // Transmit status of all descriptors
   TxStatus0  = 0x20,	      // Transmit status (Four 32bit रेजिस्टरs).
   TxAddr0    = 0x30,         // Tx descriptors (also four 32bit).
   RxConfig   = 0x40,         // Rx configuration
   MAC0	      = 0x44,	      // Ethernet hardware address.
   MAR0	      = 0x4C,	      // Multicast filter.
   RxStatus0  = 0x54,         // Rx status
   TxConfig   = 0x5C,         // Tx configuration
   PhyCtrl    = 0x60,         // physical control
   FlowCtrlConfig = 0x64,     // flow control
   Miicmd0    = 0x68,         // Mii command0 रेजिस्टर
   Miicmd1    = 0x6C,         // Mii command1 रेजिस्टर
   Miistatus  = 0x70,         // Mii status रेजिस्टर
   Timercnt   = 0x74,         // Timer counter रेजिस्टर
   TimerIntr  = 0x78,         // Timer पूर्णांकerrupt रेजिस्टर
   PMConfig   = 0x7C,         // Power Manager configuration
   CRC0       = 0x80,         // Power Manager CRC ( Two 32bit regisers)
   Wakeup0    = 0x88,         // घातer Manager wakeup( Eight 64bit regiser)
   LSBCRC0    = 0xC8,         // घातer Manager LSBCRC(Two 32bit regiser)
   TestD0     = 0xD0,
   TestD4     = 0xD4,
   TestD8     = 0xD8,
पूर्ण;

#घोषणा MII_JAB             16
#घोषणा MII_OutputStatus    24

#घोषणा PHY_16_JAB_ENB      0x1000
#घोषणा PHY_16_PORT_ENB     0x1

क्रमागत IntrStatusBits अणु
   LinkFail       = 0x80000000,
   LinkOK         = 0x40000000,
   TimeOut        = 0x20000000,
   RxOverflow     = 0x0040,
   RxOK           = 0x0020,
   TxOK           = 0x0001,
   IntrBits = LinkFail|LinkOK|TimeOut|RxOverflow|RxOK|TxOK,
पूर्ण;

क्रमागत TxStatusBits अणु
   TxCarrierLost = 0x20000000,
   TxAborted     = 0x10000000,
   TxOutOfWinकरोw = 0x08000000,
   TxNccShअगरt    = 22,
   EarlyTxThresShअगरt = 16,
   TxStatOK      = 0x8000,
   TxUnderrun    = 0x4000,
   TxOwn         = 0x2000,
पूर्ण;

क्रमागत RxStatusBits अणु
   RxStatesOK   = 0x80000,
   RxBadAlign   = 0x40000,
   RxHugeFrame  = 0x20000,
   RxSmallFrame = 0x10000,
   RxCRCOK      = 0x8000,
   RxCrlFrame   = 0x4000,
   Rx_Broadcast = 0x2000,
   Rx_Multicast = 0x1000,
   RxAddrMatch  = 0x0800,
   MiiErr       = 0x0400,
पूर्ण;

क्रमागत RxConfigBits अणु
   RxFullDx    = 0x80000000,
   RxEnb       = 0x40000000,
   RxSmall     = 0x20000000,
   RxHuge      = 0x10000000,
   RxErr       = 0x08000000,
   RxAllphys   = 0x04000000,
   RxMulticast = 0x02000000,
   RxBroadcast = 0x01000000,
   RxLoopBack  = (1 << 23) | (1 << 22),
   LowThresholdShअगरt  = 12,
   HighThresholdShअगरt = 2,
पूर्ण;

क्रमागत TxConfigBits अणु
   TxFullDx       = 0x80000000,
   TxEnb          = 0x40000000,
   TxEnbPad       = 0x20000000,
   TxEnbHuge      = 0x10000000,
   TxEnbFCS       = 0x08000000,
   TxNoBackOff    = 0x04000000,
   TxEnbPrem      = 0x02000000,
   TxCareLostCrs  = 0x1000000,
   TxExdCollNum   = 0xf00000,
   TxDataRate     = 0x80000,
पूर्ण;

क्रमागत PhyCtrlconfigbits अणु
   PhyCtrlAne         = 0x80000000,
   PhyCtrlSpd100      = 0x40000000,
   PhyCtrlSpd10       = 0x20000000,
   PhyCtrlPhyBaseAddr = 0x1f000000,
   PhyCtrlDux         = 0x800000,
   PhyCtrlReset       = 0x400000,
पूर्ण;

क्रमागत FlowCtrlConfigBits अणु
   FlowCtrlFullDX = 0x80000000,
   FlowCtrlEnb    = 0x40000000,
पूर्ण;

क्रमागत Config0Bits अणु
   Cfg0_Reset  = 0x80000000,
   Cfg0_Anaoff = 0x40000000,
   Cfg0_LDPS   = 0x20000000,
पूर्ण;

क्रमागत Config1Bits अणु
   Cfg1_EarlyRx = 1 << 31,
   Cfg1_EarlyTx = 1 << 30,

   //rx buffer size
   Cfg1_Rcv8K   = 0x0,
   Cfg1_Rcv16K  = 0x1,
   Cfg1_Rcv32K  = 0x3,
   Cfg1_Rcv64K  = 0x7,
   Cfg1_Rcv128K = 0xf,
पूर्ण;

क्रमागत MiiCmd0Bits अणु
   Mii_Divider = 0x20000000,
   Mii_WRITE   = 0x400000,
   Mii_READ    = 0x200000,
   Mii_SCAN    = 0x100000,
   Mii_Tamod   = 0x80000,
   Mii_Drvmod  = 0x40000,
   Mii_mdc     = 0x20000,
   Mii_mकरोen   = 0x10000,
   Mii_mकरो     = 0x8000,
   Mii_mdi     = 0x4000,
पूर्ण;

क्रमागत MiiStatusBits अणु
    Mii_StatusBusy = 0x80000000,
पूर्ण;

क्रमागत PMConfigBits अणु
   PM_Enable  = 1 << 31,
   PM_LongWF  = 1 << 30,
   PM_Magic   = 1 << 29,
   PM_LANWake = 1 << 28,
   PM_LWPTN   = (1 << 27 | 1<< 26),
   PM_LinkUp  = 1 << 25,
   PM_WakeUp  = 1 << 24,
पूर्ण;

/* Locking rules:
 * priv->lock protects most of the fields of priv and most of the
 * hardware रेजिस्टरs. It करोes not have to protect against softirqs
 * between sc92031_disable_पूर्णांकerrupts and sc92031_enable_पूर्णांकerrupts;
 * it also करोes not need to be used in ->खोलो and ->stop जबतक the
 * device पूर्णांकerrupts are off.
 * Not having to protect against softirqs is very useful due to heavy
 * use of mdelay() at _sc92031_reset.
 * Functions prefixed with _sc92031_ must be called with the lock held;
 * functions prefixed with sc92031_ must be called without the lock held.
 */

/* Locking rules क्रम the पूर्णांकerrupt:
 * - the पूर्णांकerrupt and the tasklet never run at the same समय
 * - neither run between sc92031_disable_पूर्णांकerrupts and
 *   sc92031_enable_पूर्णांकerrupt
 */

काष्ठा sc92031_priv अणु
	spinlock_t		lock;
	/* iomap.h cookie */
	व्योम __iomem		*port_base;
	/* pci device काष्ठाure */
	काष्ठा pci_dev		*pdev;
	/* tasklet */
	काष्ठा tasklet_काष्ठा	tasklet;

	/* CPU address of rx ring */
	व्योम			*rx_ring;
	/* PCI address of rx ring */
	dma_addr_t		rx_ring_dma_addr;
	/* PCI address of rx ring पढ़ो poपूर्णांकer */
	dma_addr_t		rx_ring_tail;

	/* tx ring ग_लिखो index */
	अचिन्हित		tx_head;
	/* tx ring पढ़ो index */
	अचिन्हित		tx_tail;
	/* CPU address of tx bounce buffer */
	व्योम			*tx_bufs;
	/* PCI address of tx bounce buffer */
	dma_addr_t		tx_bufs_dma_addr;

	/* copies of some hardware रेजिस्टरs */
	u32			पूर्णांकr_status;
	atomic_t		पूर्णांकr_mask;
	u32			rx_config;
	u32			tx_config;
	u32			pm_config;

	/* copy of some flags from dev->flags */
	अचिन्हित पूर्णांक		mc_flags;

	/* क्रम ETHTOOL_GSTATS */
	u64			tx_समयouts;
	u64			rx_loss;

	/* क्रम dev->get_stats */
	दीर्घ			rx_value;
	काष्ठा net_device	*ndev;
पूर्ण;

/* I करोn't know which रेजिस्टरs can be safely पढ़ो; however, I can guess
 * MAC0 is one of them. */
अटल अंतरभूत व्योम _sc92031_dummy_पढ़ो(व्योम __iomem *port_base)
अणु
	ioपढ़ो32(port_base + MAC0);
पूर्ण

अटल u32 _sc92031_mii_रुको(व्योम __iomem *port_base)
अणु
	u32 mii_status;

	करो अणु
		udelay(10);
		mii_status = ioपढ़ो32(port_base + Miistatus);
	पूर्ण जबतक (mii_status & Mii_StatusBusy);

	वापस mii_status;
पूर्ण

अटल u32 _sc92031_mii_cmd(व्योम __iomem *port_base, u32 cmd0, u32 cmd1)
अणु
	ioग_लिखो32(Mii_Divider, port_base + Miicmd0);

	_sc92031_mii_रुको(port_base);

	ioग_लिखो32(cmd1, port_base + Miicmd1);
	ioग_लिखो32(Mii_Divider | cmd0, port_base + Miicmd0);

	वापस _sc92031_mii_रुको(port_base);
पूर्ण

अटल व्योम _sc92031_mii_scan(व्योम __iomem *port_base)
अणु
	_sc92031_mii_cmd(port_base, Mii_SCAN, 0x1 << 6);
पूर्ण

अटल u16 _sc92031_mii_पढ़ो(व्योम __iomem *port_base, अचिन्हित reg)
अणु
	वापस _sc92031_mii_cmd(port_base, Mii_READ, reg << 6) >> 13;
पूर्ण

अटल व्योम _sc92031_mii_ग_लिखो(व्योम __iomem *port_base, अचिन्हित reg, u16 val)
अणु
	_sc92031_mii_cmd(port_base, Mii_WRITE, (reg << 6) | ((u32)val << 11));
पूर्ण

अटल व्योम sc92031_disable_पूर्णांकerrupts(काष्ठा net_device *dev)
अणु
	काष्ठा sc92031_priv *priv = netdev_priv(dev);
	व्योम __iomem *port_base = priv->port_base;

	/* tell the tasklet/पूर्णांकerrupt not to enable पूर्णांकerrupts */
	atomic_set(&priv->पूर्णांकr_mask, 0);
	wmb();

	/* stop पूर्णांकerrupts */
	ioग_लिखो32(0, port_base + IntrMask);
	_sc92031_dummy_पढ़ो(port_base);

	/* रुको क्रम any concurrent पूर्णांकerrupt/tasklet to finish */
	synchronize_irq(priv->pdev->irq);
	tasklet_disable(&priv->tasklet);
पूर्ण

अटल व्योम sc92031_enable_पूर्णांकerrupts(काष्ठा net_device *dev)
अणु
	काष्ठा sc92031_priv *priv = netdev_priv(dev);
	व्योम __iomem *port_base = priv->port_base;

	tasklet_enable(&priv->tasklet);

	atomic_set(&priv->पूर्णांकr_mask, IntrBits);
	wmb();

	ioग_लिखो32(IntrBits, port_base + IntrMask);
पूर्ण

अटल व्योम _sc92031_disable_tx_rx(काष्ठा net_device *dev)
अणु
	काष्ठा sc92031_priv *priv = netdev_priv(dev);
	व्योम __iomem *port_base = priv->port_base;

	priv->rx_config &= ~RxEnb;
	priv->tx_config &= ~TxEnb;
	ioग_लिखो32(priv->rx_config, port_base + RxConfig);
	ioग_लिखो32(priv->tx_config, port_base + TxConfig);
पूर्ण

अटल व्योम _sc92031_enable_tx_rx(काष्ठा net_device *dev)
अणु
	काष्ठा sc92031_priv *priv = netdev_priv(dev);
	व्योम __iomem *port_base = priv->port_base;

	priv->rx_config |= RxEnb;
	priv->tx_config |= TxEnb;
	ioग_लिखो32(priv->rx_config, port_base + RxConfig);
	ioग_लिखो32(priv->tx_config, port_base + TxConfig);
पूर्ण

अटल व्योम _sc92031_tx_clear(काष्ठा net_device *dev)
अणु
	काष्ठा sc92031_priv *priv = netdev_priv(dev);

	जबतक (priv->tx_head - priv->tx_tail > 0) अणु
		priv->tx_tail++;
		dev->stats.tx_dropped++;
	पूर्ण
	priv->tx_head = priv->tx_tail = 0;
पूर्ण

अटल व्योम _sc92031_set_mar(काष्ठा net_device *dev)
अणु
	काष्ठा sc92031_priv *priv = netdev_priv(dev);
	व्योम __iomem *port_base = priv->port_base;
	u32 mar0 = 0, mar1 = 0;

	अगर ((dev->flags & IFF_PROMISC) ||
	    netdev_mc_count(dev) > multicast_filter_limit ||
	    (dev->flags & IFF_ALLMULTI))
		mar0 = mar1 = 0xffffffff;
	अन्यथा अगर (dev->flags & IFF_MULTICAST) अणु
		काष्ठा netdev_hw_addr *ha;

		netdev_क्रम_each_mc_addr(ha, dev) अणु
			u32 crc;
			अचिन्हित bit = 0;

			crc = ~ether_crc(ETH_ALEN, ha->addr);
			crc >>= 24;

			अगर (crc & 0x01)	bit |= 0x02;
			अगर (crc & 0x02)	bit |= 0x01;
			अगर (crc & 0x10)	bit |= 0x20;
			अगर (crc & 0x20)	bit |= 0x10;
			अगर (crc & 0x40)	bit |= 0x08;
			अगर (crc & 0x80)	bit |= 0x04;

			अगर (bit > 31)
				mar0 |= 0x1 << (bit - 32);
			अन्यथा
				mar1 |= 0x1 << bit;
		पूर्ण
	पूर्ण

	ioग_लिखो32(mar0, port_base + MAR0);
	ioग_लिखो32(mar1, port_base + MAR0 + 4);
पूर्ण

अटल व्योम _sc92031_set_rx_config(काष्ठा net_device *dev)
अणु
	काष्ठा sc92031_priv *priv = netdev_priv(dev);
	व्योम __iomem *port_base = priv->port_base;
	अचिन्हित पूर्णांक old_mc_flags;
	u32 rx_config_bits = 0;

	old_mc_flags = priv->mc_flags;

	अगर (dev->flags & IFF_PROMISC)
		rx_config_bits |= RxSmall | RxHuge | RxErr | RxBroadcast
				| RxMulticast | RxAllphys;

	अगर (dev->flags & (IFF_ALLMULTI | IFF_MULTICAST))
		rx_config_bits |= RxMulticast;

	अगर (dev->flags & IFF_BROADCAST)
		rx_config_bits |= RxBroadcast;

	priv->rx_config &= ~(RxSmall | RxHuge | RxErr | RxBroadcast
			| RxMulticast | RxAllphys);
	priv->rx_config |= rx_config_bits;

	priv->mc_flags = dev->flags & (IFF_PROMISC | IFF_ALLMULTI
			| IFF_MULTICAST | IFF_BROADCAST);

	अगर (netअगर_carrier_ok(dev) && priv->mc_flags != old_mc_flags)
		ioग_लिखो32(priv->rx_config, port_base + RxConfig);
पूर्ण

अटल bool _sc92031_check_media(काष्ठा net_device *dev)
अणु
	काष्ठा sc92031_priv *priv = netdev_priv(dev);
	व्योम __iomem *port_base = priv->port_base;
	u16 bmsr;

	bmsr = _sc92031_mii_पढ़ो(port_base, MII_BMSR);
	rmb();
	अगर (bmsr & BMSR_LSTATUS) अणु
		bool speed_100, duplex_full;
		u32 flow_ctrl_config = 0;
		u16 output_status = _sc92031_mii_पढ़ो(port_base,
				MII_OutputStatus);
		_sc92031_mii_scan(port_base);

		speed_100 = output_status & 0x2;
		duplex_full = output_status & 0x4;

		/* Initial Tx/Rx configuration */
		priv->rx_config = (0x40 << LowThresholdShअगरt) | (0x1c0 << HighThresholdShअगरt);
		priv->tx_config = 0x48800000;

		/* NOTE: venकरोr driver had dead code here to enable tx padding */

		अगर (!speed_100)
			priv->tx_config |= 0x80000;

		// configure rx mode
		_sc92031_set_rx_config(dev);

		अगर (duplex_full) अणु
			priv->rx_config |= RxFullDx;
			priv->tx_config |= TxFullDx;
			flow_ctrl_config = FlowCtrlFullDX | FlowCtrlEnb;
		पूर्ण अन्यथा अणु
			priv->rx_config &= ~RxFullDx;
			priv->tx_config &= ~TxFullDx;
		पूर्ण

		_sc92031_set_mar(dev);
		_sc92031_set_rx_config(dev);
		_sc92031_enable_tx_rx(dev);
		ioग_लिखो32(flow_ctrl_config, port_base + FlowCtrlConfig);

		netअगर_carrier_on(dev);

		अगर (prपूर्णांकk_ratelimit())
			prपूर्णांकk(KERN_INFO "%s: link up, %sMbps, %s-duplex\n",
				dev->name,
				speed_100 ? "100" : "10",
				duplex_full ? "full" : "half");
		वापस true;
	पूर्ण अन्यथा अणु
		_sc92031_mii_scan(port_base);

		netअगर_carrier_off(dev);

		_sc92031_disable_tx_rx(dev);

		अगर (prपूर्णांकk_ratelimit())
			prपूर्णांकk(KERN_INFO "%s: link down\n", dev->name);
		वापस false;
	पूर्ण
पूर्ण

अटल व्योम _sc92031_phy_reset(काष्ठा net_device *dev)
अणु
	काष्ठा sc92031_priv *priv = netdev_priv(dev);
	व्योम __iomem *port_base = priv->port_base;
	u32 phy_ctrl;

	phy_ctrl = ioपढ़ो32(port_base + PhyCtrl);
	phy_ctrl &= ~(PhyCtrlDux | PhyCtrlSpd100 | PhyCtrlSpd10);
	phy_ctrl |= PhyCtrlAne | PhyCtrlReset;

	चयन (media) अणु
	शेष:
	हाल AUTOSELECT:
		phy_ctrl |= PhyCtrlDux | PhyCtrlSpd100 | PhyCtrlSpd10;
		अवरोध;
	हाल M10_HALF:
		phy_ctrl |= PhyCtrlSpd10;
		अवरोध;
	हाल M10_FULL:
		phy_ctrl |= PhyCtrlDux | PhyCtrlSpd10;
		अवरोध;
	हाल M100_HALF:
		phy_ctrl |= PhyCtrlSpd100;
		अवरोध;
	हाल M100_FULL:
		phy_ctrl |= PhyCtrlDux | PhyCtrlSpd100;
		अवरोध;
	पूर्ण

	ioग_लिखो32(phy_ctrl, port_base + PhyCtrl);
	mdelay(10);

	phy_ctrl &= ~PhyCtrlReset;
	ioग_लिखो32(phy_ctrl, port_base + PhyCtrl);
	mdelay(1);

	_sc92031_mii_ग_लिखो(port_base, MII_JAB,
			PHY_16_JAB_ENB | PHY_16_PORT_ENB);
	_sc92031_mii_scan(port_base);

	netअगर_carrier_off(dev);
	netअगर_stop_queue(dev);
पूर्ण

अटल व्योम _sc92031_reset(काष्ठा net_device *dev)
अणु
	काष्ठा sc92031_priv *priv = netdev_priv(dev);
	व्योम __iomem *port_base = priv->port_base;

	/* disable PM */
	ioग_लिखो32(0, port_base + PMConfig);

	/* soft reset the chip */
	ioग_लिखो32(Cfg0_Reset, port_base + Config0);
	mdelay(200);

	ioग_लिखो32(0, port_base + Config0);
	mdelay(10);

	/* disable पूर्णांकerrupts */
	ioग_लिखो32(0, port_base + IntrMask);

	/* clear multicast address */
	ioग_लिखो32(0, port_base + MAR0);
	ioग_लिखो32(0, port_base + MAR0 + 4);

	/* init rx ring */
	ioग_लिखो32(priv->rx_ring_dma_addr, port_base + RxbufAddr);
	priv->rx_ring_tail = priv->rx_ring_dma_addr;

	/* init tx ring */
	_sc92031_tx_clear(dev);

	/* clear old रेजिस्टर values */
	priv->पूर्णांकr_status = 0;
	atomic_set(&priv->पूर्णांकr_mask, 0);
	priv->rx_config = 0;
	priv->tx_config = 0;
	priv->mc_flags = 0;

	/* configure rx buffer size */
	/* NOTE: venकरोr driver had dead code here to enable early tx/rx */
	ioग_लिखो32(Cfg1_Rcv64K, port_base + Config1);

	_sc92031_phy_reset(dev);
	_sc92031_check_media(dev);

	/* calculate rx fअगरo overflow */
	priv->rx_value = 0;

	/* enable PM */
	ioग_लिखो32(priv->pm_config, port_base + PMConfig);

	/* clear पूर्णांकr रेजिस्टर */
	ioपढ़ो32(port_base + IntrStatus);
पूर्ण

अटल व्योम _sc92031_tx_tasklet(काष्ठा net_device *dev)
अणु
	काष्ठा sc92031_priv *priv = netdev_priv(dev);
	व्योम __iomem *port_base = priv->port_base;

	अचिन्हित old_tx_tail;
	अचिन्हित entry;
	u32 tx_status;

	old_tx_tail = priv->tx_tail;
	जबतक (priv->tx_head - priv->tx_tail > 0) अणु
		entry = priv->tx_tail % NUM_TX_DESC;
		tx_status = ioपढ़ो32(port_base + TxStatus0 + entry * 4);

		अगर (!(tx_status & (TxStatOK | TxUnderrun | TxAborted)))
			अवरोध;

		priv->tx_tail++;

		अगर (tx_status & TxStatOK) अणु
			dev->stats.tx_bytes += tx_status & 0x1fff;
			dev->stats.tx_packets++;
			/* Note: TxCarrierLost is always निश्चितed at 100mbps. */
			dev->stats.collisions += (tx_status >> 22) & 0xf;
		पूर्ण

		अगर (tx_status & (TxOutOfWinकरोw | TxAborted)) अणु
			dev->stats.tx_errors++;

			अगर (tx_status & TxAborted)
				dev->stats.tx_पातed_errors++;

			अगर (tx_status & TxCarrierLost)
				dev->stats.tx_carrier_errors++;

			अगर (tx_status & TxOutOfWinकरोw)
				dev->stats.tx_winकरोw_errors++;
		पूर्ण

		अगर (tx_status & TxUnderrun)
			dev->stats.tx_fअगरo_errors++;
	पूर्ण

	अगर (priv->tx_tail != old_tx_tail)
		अगर (netअगर_queue_stopped(dev))
			netअगर_wake_queue(dev);
पूर्ण

अटल व्योम _sc92031_rx_tasklet_error(काष्ठा net_device *dev,
				      u32 rx_status, अचिन्हित rx_size)
अणु
	अगर(rx_size > (MAX_ETH_FRAME_SIZE + 4) || rx_size < 16) अणु
		dev->stats.rx_errors++;
		dev->stats.rx_length_errors++;
	पूर्ण

	अगर (!(rx_status & RxStatesOK)) अणु
		dev->stats.rx_errors++;

		अगर (rx_status & (RxHugeFrame | RxSmallFrame))
			dev->stats.rx_length_errors++;

		अगर (rx_status & RxBadAlign)
			dev->stats.rx_frame_errors++;

		अगर (!(rx_status & RxCRCOK))
			dev->stats.rx_crc_errors++;
	पूर्ण अन्यथा अणु
		काष्ठा sc92031_priv *priv = netdev_priv(dev);
		priv->rx_loss++;
	पूर्ण
पूर्ण

अटल व्योम _sc92031_rx_tasklet(काष्ठा net_device *dev)
अणु
	काष्ठा sc92031_priv *priv = netdev_priv(dev);
	व्योम __iomem *port_base = priv->port_base;

	dma_addr_t rx_ring_head;
	अचिन्हित rx_len;
	अचिन्हित rx_ring_offset;
	व्योम *rx_ring = priv->rx_ring;

	rx_ring_head = ioपढ़ो32(port_base + RxBufWPtr);
	rmb();

	/* rx_ring_head is only 17 bits in the RxBufWPtr रेजिस्टर.
	 * we need to change it to 32 bits physical address
	 */
	rx_ring_head &= (dma_addr_t)(RX_BUF_LEN - 1);
	rx_ring_head |= priv->rx_ring_dma_addr & ~(dma_addr_t)(RX_BUF_LEN - 1);
	अगर (rx_ring_head < priv->rx_ring_dma_addr)
		rx_ring_head += RX_BUF_LEN;

	अगर (rx_ring_head >= priv->rx_ring_tail)
		rx_len = rx_ring_head - priv->rx_ring_tail;
	अन्यथा
		rx_len = RX_BUF_LEN - (priv->rx_ring_tail - rx_ring_head);

	अगर (!rx_len)
		वापस;

	अगर (unlikely(rx_len > RX_BUF_LEN)) अणु
		अगर (prपूर्णांकk_ratelimit())
			prपूर्णांकk(KERN_ERR "%s: rx packets length > rx buffer\n",
					dev->name);
		वापस;
	पूर्ण

	rx_ring_offset = (priv->rx_ring_tail - priv->rx_ring_dma_addr) % RX_BUF_LEN;

	जबतक (rx_len) अणु
		u32 rx_status;
		अचिन्हित rx_size, rx_size_align, pkt_size;
		काष्ठा sk_buff *skb;

		rx_status = le32_to_cpup((__le32 *)(rx_ring + rx_ring_offset));
		rmb();

		rx_size = rx_status >> 20;
		rx_size_align = (rx_size + 3) & ~3;	// क्रम 4 bytes aligned
		pkt_size = rx_size - 4;	// Omit the four octet CRC from the length.

		rx_ring_offset = (rx_ring_offset + 4) % RX_BUF_LEN;

		अगर (unlikely(rx_status == 0 ||
			     rx_size > (MAX_ETH_FRAME_SIZE + 4) ||
			     rx_size < 16 ||
			     !(rx_status & RxStatesOK))) अणु
			_sc92031_rx_tasklet_error(dev, rx_status, rx_size);
			अवरोध;
		पूर्ण

		अगर (unlikely(rx_size_align + 4 > rx_len)) अणु
			अगर (prपूर्णांकk_ratelimit())
				prपूर्णांकk(KERN_ERR "%s: rx_len is too small\n", dev->name);
			अवरोध;
		पूर्ण

		rx_len -= rx_size_align + 4;

		skb = netdev_alloc_skb_ip_align(dev, pkt_size);
		अगर (unlikely(!skb)) अणु
			अगर (prपूर्णांकk_ratelimit())
				prपूर्णांकk(KERN_ERR "%s: Couldn't allocate a skb_buff for a packet of size %u\n",
						dev->name, pkt_size);
			जाओ next;
		पूर्ण

		अगर ((rx_ring_offset + pkt_size) > RX_BUF_LEN) अणु
			skb_put_data(skb, rx_ring + rx_ring_offset,
				     RX_BUF_LEN - rx_ring_offset);
			skb_put_data(skb, rx_ring,
				     pkt_size - (RX_BUF_LEN - rx_ring_offset));
		पूर्ण अन्यथा अणु
			skb_put_data(skb, rx_ring + rx_ring_offset, pkt_size);
		पूर्ण

		skb->protocol = eth_type_trans(skb, dev);
		netअगर_rx(skb);

		dev->stats.rx_bytes += pkt_size;
		dev->stats.rx_packets++;

		अगर (rx_status & Rx_Multicast)
			dev->stats.multicast++;

	next:
		rx_ring_offset = (rx_ring_offset + rx_size_align) % RX_BUF_LEN;
	पूर्ण
	mb();

	priv->rx_ring_tail = rx_ring_head;
	ioग_लिखो32(priv->rx_ring_tail, port_base + RxBufRPtr);
पूर्ण

अटल व्योम _sc92031_link_tasklet(काष्ठा net_device *dev)
अणु
	अगर (_sc92031_check_media(dev))
		netअगर_wake_queue(dev);
	अन्यथा अणु
		netअगर_stop_queue(dev);
		dev->stats.tx_carrier_errors++;
	पूर्ण
पूर्ण

अटल व्योम sc92031_tasklet(काष्ठा tasklet_काष्ठा *t)
अणु
	काष्ठा  sc92031_priv *priv = from_tasklet(priv, t, tasklet);
	काष्ठा net_device *dev = priv->ndev;
	व्योम __iomem *port_base = priv->port_base;
	u32 पूर्णांकr_status, पूर्णांकr_mask;

	पूर्णांकr_status = priv->पूर्णांकr_status;

	spin_lock(&priv->lock);

	अगर (unlikely(!netअगर_running(dev)))
		जाओ out;

	अगर (पूर्णांकr_status & TxOK)
		_sc92031_tx_tasklet(dev);

	अगर (पूर्णांकr_status & RxOK)
		_sc92031_rx_tasklet(dev);

	अगर (पूर्णांकr_status & RxOverflow)
		dev->stats.rx_errors++;

	अगर (पूर्णांकr_status & TimeOut) अणु
		dev->stats.rx_errors++;
		dev->stats.rx_length_errors++;
	पूर्ण

	अगर (पूर्णांकr_status & (LinkFail | LinkOK))
		_sc92031_link_tasklet(dev);

out:
	पूर्णांकr_mask = atomic_पढ़ो(&priv->पूर्णांकr_mask);
	rmb();

	ioग_लिखो32(पूर्णांकr_mask, port_base + IntrMask);

	spin_unlock(&priv->lock);
पूर्ण

अटल irqवापस_t sc92031_पूर्णांकerrupt(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा net_device *dev = dev_id;
	काष्ठा sc92031_priv *priv = netdev_priv(dev);
	व्योम __iomem *port_base = priv->port_base;
	u32 पूर्णांकr_status, पूर्णांकr_mask;

	/* mask पूर्णांकerrupts beक्रमe clearing IntrStatus */
	ioग_लिखो32(0, port_base + IntrMask);
	_sc92031_dummy_पढ़ो(port_base);

	पूर्णांकr_status = ioपढ़ो32(port_base + IntrStatus);
	अगर (unlikely(पूर्णांकr_status == 0xffffffff))
		वापस IRQ_NONE;	// hardware has gone missing

	पूर्णांकr_status &= IntrBits;
	अगर (!पूर्णांकr_status)
		जाओ out_none;

	priv->पूर्णांकr_status = पूर्णांकr_status;
	tasklet_schedule(&priv->tasklet);

	वापस IRQ_HANDLED;

out_none:
	पूर्णांकr_mask = atomic_पढ़ो(&priv->पूर्णांकr_mask);
	rmb();

	ioग_लिखो32(पूर्णांकr_mask, port_base + IntrMask);

	वापस IRQ_NONE;
पूर्ण

अटल काष्ठा net_device_stats *sc92031_get_stats(काष्ठा net_device *dev)
अणु
	काष्ठा sc92031_priv *priv = netdev_priv(dev);
	व्योम __iomem *port_base = priv->port_base;

	// FIXME I करो not understand what is this trying to करो.
	अगर (netअगर_running(dev)) अणु
		पूर्णांक temp;

		spin_lock_bh(&priv->lock);

		/* Update the error count. */
		temp = (ioपढ़ो32(port_base + RxStatus0) >> 16) & 0xffff;

		अगर (temp == 0xffff) अणु
			priv->rx_value += temp;
			dev->stats.rx_fअगरo_errors = priv->rx_value;
		पूर्ण अन्यथा
			dev->stats.rx_fअगरo_errors = temp + priv->rx_value;

		spin_unlock_bh(&priv->lock);
	पूर्ण

	वापस &dev->stats;
पूर्ण

अटल netdev_tx_t sc92031_start_xmit(काष्ठा sk_buff *skb,
				      काष्ठा net_device *dev)
अणु
	काष्ठा sc92031_priv *priv = netdev_priv(dev);
	व्योम __iomem *port_base = priv->port_base;
	अचिन्हित len;
	अचिन्हित entry;
	u32 tx_status;

	अगर (unlikely(skb->len > TX_BUF_SIZE)) अणु
		dev->stats.tx_dropped++;
		जाओ out;
	पूर्ण

	spin_lock(&priv->lock);

	अगर (unlikely(!netअगर_carrier_ok(dev))) अणु
		dev->stats.tx_dropped++;
		जाओ out_unlock;
	पूर्ण

	BUG_ON(priv->tx_head - priv->tx_tail >= NUM_TX_DESC);

	entry = priv->tx_head++ % NUM_TX_DESC;

	skb_copy_and_csum_dev(skb, priv->tx_bufs + entry * TX_BUF_SIZE);

	len = skb->len;
	अगर (len < ETH_ZLEN) अणु
		स_रखो(priv->tx_bufs + entry * TX_BUF_SIZE + len,
				0, ETH_ZLEN - len);
		len = ETH_ZLEN;
	पूर्ण

	wmb();

	अगर (len < 100)
		tx_status = len;
	अन्यथा अगर (len < 300)
		tx_status = 0x30000 | len;
	अन्यथा
		tx_status = 0x50000 | len;

	ioग_लिखो32(priv->tx_bufs_dma_addr + entry * TX_BUF_SIZE,
			port_base + TxAddr0 + entry * 4);
	ioग_लिखो32(tx_status, port_base + TxStatus0 + entry * 4);

	अगर (priv->tx_head - priv->tx_tail >= NUM_TX_DESC)
		netअगर_stop_queue(dev);

out_unlock:
	spin_unlock(&priv->lock);

out:
	dev_consume_skb_any(skb);

	वापस NETDEV_TX_OK;
पूर्ण

अटल पूर्णांक sc92031_खोलो(काष्ठा net_device *dev)
अणु
	पूर्णांक err;
	काष्ठा sc92031_priv *priv = netdev_priv(dev);
	काष्ठा pci_dev *pdev = priv->pdev;

	priv->rx_ring = dma_alloc_coherent(&pdev->dev, RX_BUF_LEN,
					   &priv->rx_ring_dma_addr, GFP_KERNEL);
	अगर (unlikely(!priv->rx_ring)) अणु
		err = -ENOMEM;
		जाओ out_alloc_rx_ring;
	पूर्ण

	priv->tx_bufs = dma_alloc_coherent(&pdev->dev, TX_BUF_TOT_LEN,
					   &priv->tx_bufs_dma_addr, GFP_KERNEL);
	अगर (unlikely(!priv->tx_bufs)) अणु
		err = -ENOMEM;
		जाओ out_alloc_tx_bufs;
	पूर्ण
	priv->tx_head = priv->tx_tail = 0;

	err = request_irq(pdev->irq, sc92031_पूर्णांकerrupt,
			IRQF_SHARED, dev->name, dev);
	अगर (unlikely(err < 0))
		जाओ out_request_irq;

	priv->pm_config = 0;

	/* Interrupts alपढ़ोy disabled by sc92031_stop or sc92031_probe */
	spin_lock_bh(&priv->lock);

	_sc92031_reset(dev);

	spin_unlock_bh(&priv->lock);
	sc92031_enable_पूर्णांकerrupts(dev);

	अगर (netअगर_carrier_ok(dev))
		netअगर_start_queue(dev);
	अन्यथा
		netअगर_tx_disable(dev);

	वापस 0;

out_request_irq:
	dma_मुक्त_coherent(&pdev->dev, TX_BUF_TOT_LEN, priv->tx_bufs,
			  priv->tx_bufs_dma_addr);
out_alloc_tx_bufs:
	dma_मुक्त_coherent(&pdev->dev, RX_BUF_LEN, priv->rx_ring,
			  priv->rx_ring_dma_addr);
out_alloc_rx_ring:
	वापस err;
पूर्ण

अटल पूर्णांक sc92031_stop(काष्ठा net_device *dev)
अणु
	काष्ठा sc92031_priv *priv = netdev_priv(dev);
	काष्ठा pci_dev *pdev = priv->pdev;

	netअगर_tx_disable(dev);

	/* Disable पूर्णांकerrupts, stop Tx and Rx. */
	sc92031_disable_पूर्णांकerrupts(dev);

	spin_lock_bh(&priv->lock);

	_sc92031_disable_tx_rx(dev);
	_sc92031_tx_clear(dev);

	spin_unlock_bh(&priv->lock);

	मुक्त_irq(pdev->irq, dev);
	dma_मुक्त_coherent(&pdev->dev, TX_BUF_TOT_LEN, priv->tx_bufs,
			  priv->tx_bufs_dma_addr);
	dma_मुक्त_coherent(&pdev->dev, RX_BUF_LEN, priv->rx_ring,
			  priv->rx_ring_dma_addr);

	वापस 0;
पूर्ण

अटल व्योम sc92031_set_multicast_list(काष्ठा net_device *dev)
अणु
	काष्ठा sc92031_priv *priv = netdev_priv(dev);

	spin_lock_bh(&priv->lock);

	_sc92031_set_mar(dev);
	_sc92031_set_rx_config(dev);

	spin_unlock_bh(&priv->lock);
पूर्ण

अटल व्योम sc92031_tx_समयout(काष्ठा net_device *dev, अचिन्हित पूर्णांक txqueue)
अणु
	काष्ठा sc92031_priv *priv = netdev_priv(dev);

	/* Disable पूर्णांकerrupts by clearing the पूर्णांकerrupt mask.*/
	sc92031_disable_पूर्णांकerrupts(dev);

	spin_lock(&priv->lock);

	priv->tx_समयouts++;

	_sc92031_reset(dev);

	spin_unlock(&priv->lock);

	/* enable पूर्णांकerrupts */
	sc92031_enable_पूर्णांकerrupts(dev);

	अगर (netअगर_carrier_ok(dev))
		netअगर_wake_queue(dev);
पूर्ण

#अगर_घोषित CONFIG_NET_POLL_CONTROLLER
अटल व्योम sc92031_poll_controller(काष्ठा net_device *dev)
अणु
	काष्ठा sc92031_priv *priv = netdev_priv(dev);
	स्थिर पूर्णांक irq = priv->pdev->irq;

	disable_irq(irq);
	अगर (sc92031_पूर्णांकerrupt(irq, dev) != IRQ_NONE)
		sc92031_tasklet(&priv->tasklet);
	enable_irq(irq);
पूर्ण
#पूर्ण_अगर

अटल पूर्णांक
sc92031_ethtool_get_link_ksettings(काष्ठा net_device *dev,
				   काष्ठा ethtool_link_ksettings *cmd)
अणु
	काष्ठा sc92031_priv *priv = netdev_priv(dev);
	व्योम __iomem *port_base = priv->port_base;
	u8 phy_address;
	u32 phy_ctrl;
	u16 output_status;
	u32 supported, advertising;

	spin_lock_bh(&priv->lock);

	phy_address = ioपढ़ो32(port_base + Miicmd1) >> 27;
	phy_ctrl = ioपढ़ो32(port_base + PhyCtrl);

	output_status = _sc92031_mii_पढ़ो(port_base, MII_OutputStatus);
	_sc92031_mii_scan(port_base);

	spin_unlock_bh(&priv->lock);

	supported = SUPPORTED_10baseT_Half | SUPPORTED_10baseT_Full
			| SUPPORTED_100baseT_Half | SUPPORTED_100baseT_Full
			| SUPPORTED_Autoneg | SUPPORTED_TP | SUPPORTED_MII;

	advertising = ADVERTISED_TP | ADVERTISED_MII;

	अगर ((phy_ctrl & (PhyCtrlDux | PhyCtrlSpd100 | PhyCtrlSpd10))
			== (PhyCtrlDux | PhyCtrlSpd100 | PhyCtrlSpd10))
		advertising |= ADVERTISED_Autoneg;

	अगर ((phy_ctrl & PhyCtrlSpd10) == PhyCtrlSpd10)
		advertising |= ADVERTISED_10baseT_Half;

	अगर ((phy_ctrl & (PhyCtrlSpd10 | PhyCtrlDux))
			== (PhyCtrlSpd10 | PhyCtrlDux))
		advertising |= ADVERTISED_10baseT_Full;

	अगर ((phy_ctrl & PhyCtrlSpd100) == PhyCtrlSpd100)
		advertising |= ADVERTISED_100baseT_Half;

	अगर ((phy_ctrl & (PhyCtrlSpd100 | PhyCtrlDux))
			== (PhyCtrlSpd100 | PhyCtrlDux))
		advertising |= ADVERTISED_100baseT_Full;

	अगर (phy_ctrl & PhyCtrlAne)
		advertising |= ADVERTISED_Autoneg;

	cmd->base.speed = (output_status & 0x2) ? SPEED_100 : SPEED_10;
	cmd->base.duplex = (output_status & 0x4) ? DUPLEX_FULL : DUPLEX_HALF;
	cmd->base.port = PORT_MII;
	cmd->base.phy_address = phy_address;
	cmd->base.स्वतःneg = (phy_ctrl & PhyCtrlAne) ?
		AUTONEG_ENABLE : AUTONEG_DISABLE;

	ethtool_convert_legacy_u32_to_link_mode(cmd->link_modes.supported,
						supported);
	ethtool_convert_legacy_u32_to_link_mode(cmd->link_modes.advertising,
						advertising);

	वापस 0;
पूर्ण

अटल पूर्णांक
sc92031_ethtool_set_link_ksettings(काष्ठा net_device *dev,
				   स्थिर काष्ठा ethtool_link_ksettings *cmd)
अणु
	काष्ठा sc92031_priv *priv = netdev_priv(dev);
	व्योम __iomem *port_base = priv->port_base;
	u32 speed = cmd->base.speed;
	u32 phy_ctrl;
	u32 old_phy_ctrl;
	u32 advertising;

	ethtool_convert_link_mode_to_legacy_u32(&advertising,
						cmd->link_modes.advertising);

	अगर (!(speed == SPEED_10 || speed == SPEED_100))
		वापस -EINVAL;
	अगर (!(cmd->base.duplex == DUPLEX_HALF ||
	      cmd->base.duplex == DUPLEX_FULL))
		वापस -EINVAL;
	अगर (!(cmd->base.port == PORT_MII))
		वापस -EINVAL;
	अगर (!(cmd->base.phy_address == 0x1f))
		वापस -EINVAL;
	अगर (!(cmd->base.स्वतःneg == AUTONEG_DISABLE ||
	      cmd->base.स्वतःneg == AUTONEG_ENABLE))
		वापस -EINVAL;

	अगर (cmd->base.स्वतःneg == AUTONEG_ENABLE) अणु
		अगर (!(advertising & (ADVERTISED_Autoneg
				| ADVERTISED_100baseT_Full
				| ADVERTISED_100baseT_Half
				| ADVERTISED_10baseT_Full
				| ADVERTISED_10baseT_Half)))
			वापस -EINVAL;

		phy_ctrl = PhyCtrlAne;

		// FIXME: I'm not sure what the original code was trying to करो
		अगर (advertising & ADVERTISED_Autoneg)
			phy_ctrl |= PhyCtrlDux | PhyCtrlSpd100 | PhyCtrlSpd10;
		अगर (advertising & ADVERTISED_100baseT_Full)
			phy_ctrl |= PhyCtrlDux | PhyCtrlSpd100;
		अगर (advertising & ADVERTISED_100baseT_Half)
			phy_ctrl |= PhyCtrlSpd100;
		अगर (advertising & ADVERTISED_10baseT_Full)
			phy_ctrl |= PhyCtrlSpd10 | PhyCtrlDux;
		अगर (advertising & ADVERTISED_10baseT_Half)
			phy_ctrl |= PhyCtrlSpd10;
	पूर्ण अन्यथा अणु
		// FIXME: Whole branch guessed
		phy_ctrl = 0;

		अगर (speed == SPEED_10)
			phy_ctrl |= PhyCtrlSpd10;
		अन्यथा /* cmd->speed == SPEED_100 */
			phy_ctrl |= PhyCtrlSpd100;

		अगर (cmd->base.duplex == DUPLEX_FULL)
			phy_ctrl |= PhyCtrlDux;
	पूर्ण

	spin_lock_bh(&priv->lock);

	old_phy_ctrl = ioपढ़ो32(port_base + PhyCtrl);
	phy_ctrl |= old_phy_ctrl & ~(PhyCtrlAne | PhyCtrlDux
			| PhyCtrlSpd100 | PhyCtrlSpd10);
	अगर (phy_ctrl != old_phy_ctrl)
		ioग_लिखो32(phy_ctrl, port_base + PhyCtrl);

	spin_unlock_bh(&priv->lock);

	वापस 0;
पूर्ण

अटल व्योम sc92031_ethtool_get_wol(काष्ठा net_device *dev,
		काष्ठा ethtool_wolinfo *wolinfo)
अणु
	काष्ठा sc92031_priv *priv = netdev_priv(dev);
	व्योम __iomem *port_base = priv->port_base;
	u32 pm_config;

	spin_lock_bh(&priv->lock);
	pm_config = ioपढ़ो32(port_base + PMConfig);
	spin_unlock_bh(&priv->lock);

	// FIXME: Guessed
	wolinfo->supported = WAKE_PHY | WAKE_MAGIC
			| WAKE_UCAST | WAKE_MCAST | WAKE_BCAST;
	wolinfo->wolopts = 0;

	अगर (pm_config & PM_LinkUp)
		wolinfo->wolopts |= WAKE_PHY;

	अगर (pm_config & PM_Magic)
		wolinfo->wolopts |= WAKE_MAGIC;

	अगर (pm_config & PM_WakeUp)
		// FIXME: Guessed
		wolinfo->wolopts |= WAKE_UCAST | WAKE_MCAST | WAKE_BCAST;
पूर्ण

अटल पूर्णांक sc92031_ethtool_set_wol(काष्ठा net_device *dev,
		काष्ठा ethtool_wolinfo *wolinfo)
अणु
	काष्ठा sc92031_priv *priv = netdev_priv(dev);
	व्योम __iomem *port_base = priv->port_base;
	u32 pm_config;

	spin_lock_bh(&priv->lock);

	pm_config = ioपढ़ो32(port_base + PMConfig)
			& ~(PM_LinkUp | PM_Magic | PM_WakeUp);

	अगर (wolinfo->wolopts & WAKE_PHY)
		pm_config |= PM_LinkUp;

	अगर (wolinfo->wolopts & WAKE_MAGIC)
		pm_config |= PM_Magic;

	// FIXME: Guessed
	अगर (wolinfo->wolopts & (WAKE_UCAST | WAKE_MCAST | WAKE_BCAST))
		pm_config |= PM_WakeUp;

	priv->pm_config = pm_config;
	ioग_लिखो32(pm_config, port_base + PMConfig);

	spin_unlock_bh(&priv->lock);

	वापस 0;
पूर्ण

अटल पूर्णांक sc92031_ethtool_nway_reset(काष्ठा net_device *dev)
अणु
	पूर्णांक err = 0;
	काष्ठा sc92031_priv *priv = netdev_priv(dev);
	व्योम __iomem *port_base = priv->port_base;
	u16 bmcr;

	spin_lock_bh(&priv->lock);

	bmcr = _sc92031_mii_पढ़ो(port_base, MII_BMCR);
	अगर (!(bmcr & BMCR_ANENABLE)) अणु
		err = -EINVAL;
		जाओ out;
	पूर्ण

	_sc92031_mii_ग_लिखो(port_base, MII_BMCR, bmcr | BMCR_ANRESTART);

out:
	_sc92031_mii_scan(port_base);

	spin_unlock_bh(&priv->lock);

	वापस err;
पूर्ण

अटल स्थिर अक्षर sc92031_ethtool_stats_strings[SILAN_STATS_NUM][ETH_GSTRING_LEN] = अणु
	"tx_timeout",
	"rx_loss",
पूर्ण;

अटल व्योम sc92031_ethtool_get_strings(काष्ठा net_device *dev,
		u32 stringset, u8 *data)
अणु
	अगर (stringset == ETH_SS_STATS)
		स_नकल(data, sc92031_ethtool_stats_strings,
				SILAN_STATS_NUM * ETH_GSTRING_LEN);
पूर्ण

अटल पूर्णांक sc92031_ethtool_get_sset_count(काष्ठा net_device *dev, पूर्णांक sset)
अणु
	चयन (sset) अणु
	हाल ETH_SS_STATS:
		वापस SILAN_STATS_NUM;
	शेष:
		वापस -EOPNOTSUPP;
	पूर्ण
पूर्ण

अटल व्योम sc92031_ethtool_get_ethtool_stats(काष्ठा net_device *dev,
		काष्ठा ethtool_stats *stats, u64 *data)
अणु
	काष्ठा sc92031_priv *priv = netdev_priv(dev);

	spin_lock_bh(&priv->lock);
	data[0] = priv->tx_समयouts;
	data[1] = priv->rx_loss;
	spin_unlock_bh(&priv->lock);
पूर्ण

अटल स्थिर काष्ठा ethtool_ops sc92031_ethtool_ops = अणु
	.get_wol		= sc92031_ethtool_get_wol,
	.set_wol		= sc92031_ethtool_set_wol,
	.nway_reset		= sc92031_ethtool_nway_reset,
	.get_link		= ethtool_op_get_link,
	.get_strings		= sc92031_ethtool_get_strings,
	.get_sset_count		= sc92031_ethtool_get_sset_count,
	.get_ethtool_stats	= sc92031_ethtool_get_ethtool_stats,
	.get_link_ksettings	= sc92031_ethtool_get_link_ksettings,
	.set_link_ksettings	= sc92031_ethtool_set_link_ksettings,
पूर्ण;


अटल स्थिर काष्ठा net_device_ops sc92031_netdev_ops = अणु
	.nकरो_get_stats		= sc92031_get_stats,
	.nकरो_start_xmit		= sc92031_start_xmit,
	.nकरो_खोलो		= sc92031_खोलो,
	.nकरो_stop		= sc92031_stop,
	.nकरो_set_rx_mode	= sc92031_set_multicast_list,
	.nकरो_validate_addr	= eth_validate_addr,
	.nकरो_set_mac_address 	= eth_mac_addr,
	.nकरो_tx_समयout		= sc92031_tx_समयout,
#अगर_घोषित CONFIG_NET_POLL_CONTROLLER
	.nकरो_poll_controller	= sc92031_poll_controller,
#पूर्ण_अगर
पूर्ण;

अटल पूर्णांक sc92031_probe(काष्ठा pci_dev *pdev, स्थिर काष्ठा pci_device_id *id)
अणु
	पूर्णांक err;
	व्योम __iomem* port_base;
	काष्ठा net_device *dev;
	काष्ठा sc92031_priv *priv;
	u32 mac0, mac1;

	err = pci_enable_device(pdev);
	अगर (unlikely(err < 0))
		जाओ out_enable_device;

	pci_set_master(pdev);

	err = dma_set_mask(&pdev->dev, DMA_BIT_MASK(32));
	अगर (unlikely(err < 0))
		जाओ out_set_dma_mask;

	err = dma_set_coherent_mask(&pdev->dev, DMA_BIT_MASK(32));
	अगर (unlikely(err < 0))
		जाओ out_set_dma_mask;

	err = pci_request_regions(pdev, SC92031_NAME);
	अगर (unlikely(err < 0))
		जाओ out_request_regions;

	port_base = pci_iomap(pdev, SC92031_USE_PIO, 0);
	अगर (unlikely(!port_base)) अणु
		err = -EIO;
		जाओ out_iomap;
	पूर्ण

	dev = alloc_etherdev(माप(काष्ठा sc92031_priv));
	अगर (unlikely(!dev)) अणु
		err = -ENOMEM;
		जाओ out_alloc_etherdev;
	पूर्ण

	pci_set_drvdata(pdev, dev);
	SET_NETDEV_DEV(dev, &pdev->dev);

	/* faked with skb_copy_and_csum_dev */
	dev->features = NETIF_F_SG | NETIF_F_HIGHDMA |
		NETIF_F_IP_CSUM | NETIF_F_IPV6_CSUM;

	dev->netdev_ops		= &sc92031_netdev_ops;
	dev->watchकरोg_समयo	= TX_TIMEOUT;
	dev->ethtool_ops	= &sc92031_ethtool_ops;

	priv = netdev_priv(dev);
	priv->ndev = dev;
	spin_lock_init(&priv->lock);
	priv->port_base = port_base;
	priv->pdev = pdev;
	tasklet_setup(&priv->tasklet, sc92031_tasklet);
	/* Fudge tasklet count so the call to sc92031_enable_पूर्णांकerrupts at
	 * sc92031_खोलो will work correctly */
	tasklet_disable_nosync(&priv->tasklet);

	/* PCI PM Wakeup */
	ioग_लिखो32((~PM_LongWF & ~PM_LWPTN) | PM_Enable, port_base + PMConfig);

	mac0 = ioपढ़ो32(port_base + MAC0);
	mac1 = ioपढ़ो32(port_base + MAC0 + 4);
	dev->dev_addr[0] = mac0 >> 24;
	dev->dev_addr[1] = mac0 >> 16;
	dev->dev_addr[2] = mac0 >> 8;
	dev->dev_addr[3] = mac0;
	dev->dev_addr[4] = mac1 >> 8;
	dev->dev_addr[5] = mac1;

	err = रेजिस्टर_netdev(dev);
	अगर (err < 0)
		जाओ out_रेजिस्टर_netdev;

	prपूर्णांकk(KERN_INFO "%s: SC92031 at 0x%lx, %pM, IRQ %d\n", dev->name,
	       (दीर्घ)pci_resource_start(pdev, SC92031_USE_PIO), dev->dev_addr,
	       pdev->irq);

	वापस 0;

out_रेजिस्टर_netdev:
	मुक्त_netdev(dev);
out_alloc_etherdev:
	pci_iounmap(pdev, port_base);
out_iomap:
	pci_release_regions(pdev);
out_request_regions:
out_set_dma_mask:
	pci_disable_device(pdev);
out_enable_device:
	वापस err;
पूर्ण

अटल व्योम sc92031_हटाओ(काष्ठा pci_dev *pdev)
अणु
	काष्ठा net_device *dev = pci_get_drvdata(pdev);
	काष्ठा sc92031_priv *priv = netdev_priv(dev);
	व्योम __iomem* port_base = priv->port_base;

	unरेजिस्टर_netdev(dev);
	मुक्त_netdev(dev);
	pci_iounmap(pdev, port_base);
	pci_release_regions(pdev);
	pci_disable_device(pdev);
पूर्ण

अटल पूर्णांक __maybe_unused sc92031_suspend(काष्ठा device *dev_d)
अणु
	काष्ठा net_device *dev = dev_get_drvdata(dev_d);
	काष्ठा sc92031_priv *priv = netdev_priv(dev);

	अगर (!netअगर_running(dev))
		वापस 0;

	netअगर_device_detach(dev);

	/* Disable पूर्णांकerrupts, stop Tx and Rx. */
	sc92031_disable_पूर्णांकerrupts(dev);

	spin_lock_bh(&priv->lock);

	_sc92031_disable_tx_rx(dev);
	_sc92031_tx_clear(dev);

	spin_unlock_bh(&priv->lock);

	वापस 0;
पूर्ण

अटल पूर्णांक __maybe_unused sc92031_resume(काष्ठा device *dev_d)
अणु
	काष्ठा net_device *dev = dev_get_drvdata(dev_d);
	काष्ठा sc92031_priv *priv = netdev_priv(dev);

	अगर (!netअगर_running(dev))
		वापस 0;

	/* Interrupts alपढ़ोy disabled by sc92031_suspend */
	spin_lock_bh(&priv->lock);

	_sc92031_reset(dev);

	spin_unlock_bh(&priv->lock);
	sc92031_enable_पूर्णांकerrupts(dev);

	netअगर_device_attach(dev);

	अगर (netअगर_carrier_ok(dev))
		netअगर_wake_queue(dev);
	अन्यथा
		netअगर_tx_disable(dev);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा pci_device_id sc92031_pci_device_id_table[] = अणु
	अणु PCI_DEVICE(PCI_VENDOR_ID_SILAN, 0x2031) पूर्ण,
	अणु PCI_DEVICE(PCI_VENDOR_ID_SILAN, 0x8139) पूर्ण,
	अणु PCI_DEVICE(0x1088, 0x2031) पूर्ण,
	अणु 0, पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(pci, sc92031_pci_device_id_table);

अटल SIMPLE_DEV_PM_OPS(sc92031_pm_ops, sc92031_suspend, sc92031_resume);

अटल काष्ठा pci_driver sc92031_pci_driver = अणु
	.name		= SC92031_NAME,
	.id_table	= sc92031_pci_device_id_table,
	.probe		= sc92031_probe,
	.हटाओ		= sc92031_हटाओ,
	.driver.pm	= &sc92031_pm_ops,
पूर्ण;

module_pci_driver(sc92031_pci_driver);
MODULE_LICENSE("GPL");
MODULE_AUTHOR("Cesar Eduardo Barros <cesarb@cesarb.net>");
MODULE_DESCRIPTION("Silan SC92031 PCI Fast Ethernet Adapter driver");
