<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/* sunhme.c: Sparc HME/BigMac 10/100baseT half/full duplex स्वतः चयनing,
 *           स्वतः carrier detecting ethernet driver.  Also known as the
 *           "Happy Meal Ethernet" found on SunSwअगरt SBUS cards.
 *
 * Copyright (C) 1996, 1998, 1999, 2002, 2003,
 *		2006, 2008 David S. Miller (davem@davemloft.net)
 *
 * Changes :
 * 2000/11/11 Willy Tarreau <willy AT meta-x.org>
 *   - port to non-sparc architectures. Tested only on x86 and
 *     only currently works with QFE PCI cards.
 *   - ability to specअगरy the MAC address at module load समय by passing this
 *     argument : macaddr=0x00,0x10,0x20,0x30,0x40,0x50
 */

#समावेश <linux/module.h>
#समावेश <linux/kernel.h>
#समावेश <linux/types.h>
#समावेश <linux/fcntl.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/ioport.h>
#समावेश <linux/in.h>
#समावेश <linux/slab.h>
#समावेश <linux/माला.स>
#समावेश <linux/delay.h>
#समावेश <linux/init.h>
#समावेश <linux/ethtool.h>
#समावेश <linux/mii.h>
#समावेश <linux/crc32.h>
#समावेश <linux/अक्रमom.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/netdevice.h>
#समावेश <linux/etherdevice.h>
#समावेश <linux/skbuff.h>
#समावेश <linux/mm.h>
#समावेश <linux/bitops.h>
#समावेश <linux/dma-mapping.h>

#समावेश <यंत्र/पन.स>
#समावेश <यंत्र/dma.h>
#समावेश <यंत्र/byteorder.h>

#अगर_घोषित CONFIG_SPARC
#समावेश <linux/of.h>
#समावेश <linux/of_device.h>
#समावेश <यंत्र/idprom.h>
#समावेश <यंत्र/खोलोprom.h>
#समावेश <यंत्र/oplib.h>
#समावेश <यंत्र/prom.h>
#समावेश <यंत्र/auxपन.स>
#पूर्ण_अगर
#समावेश <linux/uaccess.h>

#समावेश <यंत्र/irq.h>

#अगर_घोषित CONFIG_PCI
#समावेश <linux/pci.h>
#पूर्ण_अगर

#समावेश "sunhme.h"

#घोषणा DRV_NAME	"sunhme"
#घोषणा DRV_VERSION	"3.10"
#घोषणा DRV_RELDATE	"August 26, 2008"
#घोषणा DRV_AUTHOR	"David S. Miller (davem@davemloft.net)"

अटल अक्षर version[] =
	DRV_NAME ".c:v" DRV_VERSION " " DRV_RELDATE " " DRV_AUTHOR "\n";

MODULE_VERSION(DRV_VERSION);
MODULE_AUTHOR(DRV_AUTHOR);
MODULE_DESCRIPTION("Sun HappyMealEthernet(HME) 10/100baseT ethernet driver");
MODULE_LICENSE("GPL");

अटल पूर्णांक macaddr[6];

/* accept MAC address of the क्रमm macaddr=0x08,0x00,0x20,0x30,0x40,0x50 */
module_param_array(macaddr, पूर्णांक, शून्य, 0);
MODULE_PARM_DESC(macaddr, "Happy Meal MAC address to set");

#अगर_घोषित CONFIG_SBUS
अटल काष्ठा quattro *qfe_sbus_list;
#पूर्ण_अगर

#अगर_घोषित CONFIG_PCI
अटल काष्ठा quattro *qfe_pci_list;
#पूर्ण_अगर

#अघोषित HMEDEBUG
#अघोषित SXDEBUG
#अघोषित RXDEBUG
#अघोषित TXDEBUG
#अघोषित TXLOGGING

#अगर_घोषित TXLOGGING
काष्ठा hme_tx_logent अणु
	अचिन्हित पूर्णांक tstamp;
	पूर्णांक tx_new, tx_old;
	अचिन्हित पूर्णांक action;
#घोषणा TXLOG_ACTION_IRQ	0x01
#घोषणा TXLOG_ACTION_TXMIT	0x02
#घोषणा TXLOG_ACTION_TBUSY	0x04
#घोषणा TXLOG_ACTION_NBUFS	0x08
	अचिन्हित पूर्णांक status;
पूर्ण;
#घोषणा TX_LOG_LEN	128
अटल काष्ठा hme_tx_logent tx_log[TX_LOG_LEN];
अटल पूर्णांक txlog_cur_entry;
अटल __अंतरभूत__ व्योम tx_add_log(काष्ठा happy_meal *hp, अचिन्हित पूर्णांक a, अचिन्हित पूर्णांक s)
अणु
	काष्ठा hme_tx_logent *tlp;
	अचिन्हित दीर्घ flags;

	local_irq_save(flags);
	tlp = &tx_log[txlog_cur_entry];
	tlp->tstamp = (अचिन्हित पूर्णांक)jअगरfies;
	tlp->tx_new = hp->tx_new;
	tlp->tx_old = hp->tx_old;
	tlp->action = a;
	tlp->status = s;
	txlog_cur_entry = (txlog_cur_entry + 1) & (TX_LOG_LEN - 1);
	local_irq_restore(flags);
पूर्ण
अटल __अंतरभूत__ व्योम tx_dump_log(व्योम)
अणु
	पूर्णांक i, this;

	this = txlog_cur_entry;
	क्रम (i = 0; i < TX_LOG_LEN; i++) अणु
		prपूर्णांकk("TXLOG[%d]: j[%08x] tx[N(%d)O(%d)] action[%08x] stat[%08x]\n", i,
		       tx_log[this].tstamp,
		       tx_log[this].tx_new, tx_log[this].tx_old,
		       tx_log[this].action, tx_log[this].status);
		this = (this + 1) & (TX_LOG_LEN - 1);
	पूर्ण
पूर्ण
अटल __अंतरभूत__ व्योम tx_dump_ring(काष्ठा happy_meal *hp)
अणु
	काष्ठा hmeal_init_block *hb = hp->happy_block;
	काष्ठा happy_meal_txd *tp = &hb->happy_meal_txd[0];
	पूर्णांक i;

	क्रम (i = 0; i < TX_RING_SIZE; i+=4) अणु
		prपूर्णांकk("TXD[%d..%d]: [%08x:%08x] [%08x:%08x] [%08x:%08x] [%08x:%08x]\n",
		       i, i + 4,
		       le32_to_cpu(tp[i].tx_flags), le32_to_cpu(tp[i].tx_addr),
		       le32_to_cpu(tp[i + 1].tx_flags), le32_to_cpu(tp[i + 1].tx_addr),
		       le32_to_cpu(tp[i + 2].tx_flags), le32_to_cpu(tp[i + 2].tx_addr),
		       le32_to_cpu(tp[i + 3].tx_flags), le32_to_cpu(tp[i + 3].tx_addr));
	पूर्ण
पूर्ण
#अन्यथा
#घोषणा tx_add_log(hp, a, s)		करो अणु पूर्ण जबतक(0)
#घोषणा tx_dump_log()			करो अणु पूर्ण जबतक(0)
#घोषणा tx_dump_ring(hp)		करो अणु पूर्ण जबतक(0)
#पूर्ण_अगर

#अगर_घोषित HMEDEBUG
#घोषणा HMD(x)  prपूर्णांकk x
#अन्यथा
#घोषणा HMD(x)
#पूर्ण_अगर

/* #घोषणा AUTO_SWITCH_DEBUG */

#अगर_घोषित AUTO_SWITCH_DEBUG
#घोषणा ASD(x)  prपूर्णांकk x
#अन्यथा
#घोषणा ASD(x)
#पूर्ण_अगर

#घोषणा DEFAULT_IPG0      16 /* For lance-mode only */
#घोषणा DEFAULT_IPG1       8 /* For all modes */
#घोषणा DEFAULT_IPG2       4 /* For all modes */
#घोषणा DEFAULT_JAMSIZE    4 /* Toe jam */

/* NOTE: In the descriptor ग_लिखोs one _must_ ग_लिखो the address
 *	 member _first_.  The card must not be allowed to see
 *	 the updated descriptor flags until the address is
 *	 correct.  I've added a ग_लिखो memory barrier between
 *	 the two stores so that I can sleep well at night... -DaveM
 */

#अगर defined(CONFIG_SBUS) && defined(CONFIG_PCI)
अटल व्योम sbus_hme_ग_लिखो32(व्योम __iomem *reg, u32 val)
अणु
	sbus_ग_लिखोl(val, reg);
पूर्ण

अटल u32 sbus_hme_पढ़ो32(व्योम __iomem *reg)
अणु
	वापस sbus_पढ़ोl(reg);
पूर्ण

अटल व्योम sbus_hme_ग_लिखो_rxd(काष्ठा happy_meal_rxd *rxd, u32 flags, u32 addr)
अणु
	rxd->rx_addr = (__क्रमce hme32)addr;
	dma_wmb();
	rxd->rx_flags = (__क्रमce hme32)flags;
पूर्ण

अटल व्योम sbus_hme_ग_लिखो_txd(काष्ठा happy_meal_txd *txd, u32 flags, u32 addr)
अणु
	txd->tx_addr = (__क्रमce hme32)addr;
	dma_wmb();
	txd->tx_flags = (__क्रमce hme32)flags;
पूर्ण

अटल u32 sbus_hme_पढ़ो_desc32(hme32 *p)
अणु
	वापस (__क्रमce u32)*p;
पूर्ण

अटल व्योम pci_hme_ग_लिखो32(व्योम __iomem *reg, u32 val)
अणु
	ग_लिखोl(val, reg);
पूर्ण

अटल u32 pci_hme_पढ़ो32(व्योम __iomem *reg)
अणु
	वापस पढ़ोl(reg);
पूर्ण

अटल व्योम pci_hme_ग_लिखो_rxd(काष्ठा happy_meal_rxd *rxd, u32 flags, u32 addr)
अणु
	rxd->rx_addr = (__क्रमce hme32)cpu_to_le32(addr);
	dma_wmb();
	rxd->rx_flags = (__क्रमce hme32)cpu_to_le32(flags);
पूर्ण

अटल व्योम pci_hme_ग_लिखो_txd(काष्ठा happy_meal_txd *txd, u32 flags, u32 addr)
अणु
	txd->tx_addr = (__क्रमce hme32)cpu_to_le32(addr);
	dma_wmb();
	txd->tx_flags = (__क्रमce hme32)cpu_to_le32(flags);
पूर्ण

अटल u32 pci_hme_पढ़ो_desc32(hme32 *p)
अणु
	वापस le32_to_cpup((__le32 *)p);
पूर्ण

#घोषणा hme_ग_लिखो32(__hp, __reg, __val) \
	((__hp)->ग_लिखो32((__reg), (__val)))
#घोषणा hme_पढ़ो32(__hp, __reg) \
	((__hp)->पढ़ो32(__reg))
#घोषणा hme_ग_लिखो_rxd(__hp, __rxd, __flags, __addr) \
	((__hp)->ग_लिखो_rxd((__rxd), (__flags), (__addr)))
#घोषणा hme_ग_लिखो_txd(__hp, __txd, __flags, __addr) \
	((__hp)->ग_लिखो_txd((__txd), (__flags), (__addr)))
#घोषणा hme_पढ़ो_desc32(__hp, __p) \
	((__hp)->पढ़ो_desc32(__p))
#घोषणा hme_dma_map(__hp, __ptr, __size, __dir) \
	((__hp)->dma_map((__hp)->dma_dev, (__ptr), (__size), (__dir)))
#घोषणा hme_dma_unmap(__hp, __addr, __size, __dir) \
	((__hp)->dma_unmap((__hp)->dma_dev, (__addr), (__size), (__dir)))
#घोषणा hme_dma_sync_क्रम_cpu(__hp, __addr, __size, __dir) \
	((__hp)->dma_sync_क्रम_cpu((__hp)->dma_dev, (__addr), (__size), (__dir)))
#घोषणा hme_dma_sync_क्रम_device(__hp, __addr, __size, __dir) \
	((__hp)->dma_sync_क्रम_device((__hp)->dma_dev, (__addr), (__size), (__dir)))
#अन्यथा
#अगर_घोषित CONFIG_SBUS
/* SBUS only compilation */
#घोषणा hme_ग_लिखो32(__hp, __reg, __val) \
	sbus_ग_लिखोl((__val), (__reg))
#घोषणा hme_पढ़ो32(__hp, __reg) \
	sbus_पढ़ोl(__reg)
#घोषणा hme_ग_लिखो_rxd(__hp, __rxd, __flags, __addr) \
करो अणु	(__rxd)->rx_addr = (__क्रमce hme32)(u32)(__addr); \
	dma_wmb(); \
	(__rxd)->rx_flags = (__क्रमce hme32)(u32)(__flags); \
पूर्ण जबतक(0)
#घोषणा hme_ग_लिखो_txd(__hp, __txd, __flags, __addr) \
करो अणु	(__txd)->tx_addr = (__क्रमce hme32)(u32)(__addr); \
	dma_wmb(); \
	(__txd)->tx_flags = (__क्रमce hme32)(u32)(__flags); \
पूर्ण जबतक(0)
#घोषणा hme_पढ़ो_desc32(__hp, __p)	((__क्रमce u32)(hme32)*(__p))
#घोषणा hme_dma_map(__hp, __ptr, __size, __dir) \
	dma_map_single((__hp)->dma_dev, (__ptr), (__size), (__dir))
#घोषणा hme_dma_unmap(__hp, __addr, __size, __dir) \
	dma_unmap_single((__hp)->dma_dev, (__addr), (__size), (__dir))
#घोषणा hme_dma_sync_क्रम_cpu(__hp, __addr, __size, __dir) \
	dma_dma_sync_single_क्रम_cpu((__hp)->dma_dev, (__addr), (__size), (__dir))
#घोषणा hme_dma_sync_क्रम_device(__hp, __addr, __size, __dir) \
	dma_dma_sync_single_क्रम_device((__hp)->dma_dev, (__addr), (__size), (__dir))
#अन्यथा
/* PCI only compilation */
#घोषणा hme_ग_लिखो32(__hp, __reg, __val) \
	ग_लिखोl((__val), (__reg))
#घोषणा hme_पढ़ो32(__hp, __reg) \
	पढ़ोl(__reg)
#घोषणा hme_ग_लिखो_rxd(__hp, __rxd, __flags, __addr) \
करो अणु	(__rxd)->rx_addr = (__क्रमce hme32)cpu_to_le32(__addr); \
	dma_wmb(); \
	(__rxd)->rx_flags = (__क्रमce hme32)cpu_to_le32(__flags); \
पूर्ण जबतक(0)
#घोषणा hme_ग_लिखो_txd(__hp, __txd, __flags, __addr) \
करो अणु	(__txd)->tx_addr = (__क्रमce hme32)cpu_to_le32(__addr); \
	dma_wmb(); \
	(__txd)->tx_flags = (__क्रमce hme32)cpu_to_le32(__flags); \
पूर्ण जबतक(0)
अटल अंतरभूत u32 hme_पढ़ो_desc32(काष्ठा happy_meal *hp, hme32 *p)
अणु
	वापस le32_to_cpup((__le32 *)p);
पूर्ण
#घोषणा hme_dma_map(__hp, __ptr, __size, __dir) \
	pci_map_single((__hp)->dma_dev, (__ptr), (__size), (__dir))
#घोषणा hme_dma_unmap(__hp, __addr, __size, __dir) \
	pci_unmap_single((__hp)->dma_dev, (__addr), (__size), (__dir))
#घोषणा hme_dma_sync_क्रम_cpu(__hp, __addr, __size, __dir) \
	pci_dma_sync_single_क्रम_cpu((__hp)->dma_dev, (__addr), (__size), (__dir))
#घोषणा hme_dma_sync_क्रम_device(__hp, __addr, __size, __dir) \
	pci_dma_sync_single_क्रम_device((__hp)->dma_dev, (__addr), (__size), (__dir))
#पूर्ण_अगर
#पूर्ण_अगर


/* Oh yes, the MIF BitBang is mighty fun to program.  BitBucket is more like it. */
अटल व्योम BB_PUT_BIT(काष्ठा happy_meal *hp, व्योम __iomem *tregs, पूर्णांक bit)
अणु
	hme_ग_लिखो32(hp, tregs + TCVR_BBDATA, bit);
	hme_ग_लिखो32(hp, tregs + TCVR_BBCLOCK, 0);
	hme_ग_लिखो32(hp, tregs + TCVR_BBCLOCK, 1);
पूर्ण

#अगर 0
अटल u32 BB_GET_BIT(काष्ठा happy_meal *hp, व्योम __iomem *tregs, पूर्णांक पूर्णांकernal)
अणु
	u32 ret;

	hme_ग_लिखो32(hp, tregs + TCVR_BBCLOCK, 0);
	hme_ग_लिखो32(hp, tregs + TCVR_BBCLOCK, 1);
	ret = hme_पढ़ो32(hp, tregs + TCVR_CFG);
	अगर (पूर्णांकernal)
		ret &= TCV_CFG_MDIO0;
	अन्यथा
		ret &= TCV_CFG_MDIO1;

	वापस ret;
पूर्ण
#पूर्ण_अगर

अटल u32 BB_GET_BIT2(काष्ठा happy_meal *hp, व्योम __iomem *tregs, पूर्णांक पूर्णांकernal)
अणु
	u32 retval;

	hme_ग_लिखो32(hp, tregs + TCVR_BBCLOCK, 0);
	udelay(1);
	retval = hme_पढ़ो32(hp, tregs + TCVR_CFG);
	अगर (पूर्णांकernal)
		retval &= TCV_CFG_MDIO0;
	अन्यथा
		retval &= TCV_CFG_MDIO1;
	hme_ग_लिखो32(hp, tregs + TCVR_BBCLOCK, 1);

	वापस retval;
पूर्ण

#घोषणा TCVR_FAILURE      0x80000000     /* Impossible MIF पढ़ो value */

अटल पूर्णांक happy_meal_bb_पढ़ो(काष्ठा happy_meal *hp,
			      व्योम __iomem *tregs, पूर्णांक reg)
अणु
	u32 पंचांगp;
	पूर्णांक retval = 0;
	पूर्णांक i;

	ASD(("happy_meal_bb_read: reg=%d ", reg));

	/* Enable the MIF BitBang outमाला_दो. */
	hme_ग_लिखो32(hp, tregs + TCVR_BBOENAB, 1);

	/* Force BitBang पूर्णांकo the idle state. */
	क्रम (i = 0; i < 32; i++)
		BB_PUT_BIT(hp, tregs, 1);

	/* Give it the पढ़ो sequence. */
	BB_PUT_BIT(hp, tregs, 0);
	BB_PUT_BIT(hp, tregs, 1);
	BB_PUT_BIT(hp, tregs, 1);
	BB_PUT_BIT(hp, tregs, 0);

	/* Give it the PHY address. */
	पंचांगp = hp->paddr & 0xff;
	क्रम (i = 4; i >= 0; i--)
		BB_PUT_BIT(hp, tregs, ((पंचांगp >> i) & 1));

	/* Tell it what रेजिस्टर we want to पढ़ो. */
	पंचांगp = (reg & 0xff);
	क्रम (i = 4; i >= 0; i--)
		BB_PUT_BIT(hp, tregs, ((पंचांगp >> i) & 1));

	/* Close करोwn the MIF BitBang outमाला_दो. */
	hme_ग_लिखो32(hp, tregs + TCVR_BBOENAB, 0);

	/* Now पढ़ो in the value. */
	(व्योम) BB_GET_BIT2(hp, tregs, (hp->tcvr_type == पूर्णांकernal));
	क्रम (i = 15; i >= 0; i--)
		retval |= BB_GET_BIT2(hp, tregs, (hp->tcvr_type == पूर्णांकernal));
	(व्योम) BB_GET_BIT2(hp, tregs, (hp->tcvr_type == पूर्णांकernal));
	(व्योम) BB_GET_BIT2(hp, tregs, (hp->tcvr_type == पूर्णांकernal));
	(व्योम) BB_GET_BIT2(hp, tregs, (hp->tcvr_type == पूर्णांकernal));
	ASD(("value=%x\n", retval));
	वापस retval;
पूर्ण

अटल व्योम happy_meal_bb_ग_लिखो(काष्ठा happy_meal *hp,
				व्योम __iomem *tregs, पूर्णांक reg,
				अचिन्हित लघु value)
अणु
	u32 पंचांगp;
	पूर्णांक i;

	ASD(("happy_meal_bb_write: reg=%d value=%x\n", reg, value));

	/* Enable the MIF BitBang outमाला_दो. */
	hme_ग_लिखो32(hp, tregs + TCVR_BBOENAB, 1);

	/* Force BitBang पूर्णांकo the idle state. */
	क्रम (i = 0; i < 32; i++)
		BB_PUT_BIT(hp, tregs, 1);

	/* Give it ग_लिखो sequence. */
	BB_PUT_BIT(hp, tregs, 0);
	BB_PUT_BIT(hp, tregs, 1);
	BB_PUT_BIT(hp, tregs, 0);
	BB_PUT_BIT(hp, tregs, 1);

	/* Give it the PHY address. */
	पंचांगp = (hp->paddr & 0xff);
	क्रम (i = 4; i >= 0; i--)
		BB_PUT_BIT(hp, tregs, ((पंचांगp >> i) & 1));

	/* Tell it what रेजिस्टर we will be writing. */
	पंचांगp = (reg & 0xff);
	क्रम (i = 4; i >= 0; i--)
		BB_PUT_BIT(hp, tregs, ((पंचांगp >> i) & 1));

	/* Tell it to become पढ़ोy क्रम the bits. */
	BB_PUT_BIT(hp, tregs, 1);
	BB_PUT_BIT(hp, tregs, 0);

	क्रम (i = 15; i >= 0; i--)
		BB_PUT_BIT(hp, tregs, ((value >> i) & 1));

	/* Close करोwn the MIF BitBang outमाला_दो. */
	hme_ग_लिखो32(hp, tregs + TCVR_BBOENAB, 0);
पूर्ण

#घोषणा TCVR_READ_TRIES   16

अटल पूर्णांक happy_meal_tcvr_पढ़ो(काष्ठा happy_meal *hp,
				व्योम __iomem *tregs, पूर्णांक reg)
अणु
	पूर्णांक tries = TCVR_READ_TRIES;
	पूर्णांक retval;

	ASD(("happy_meal_tcvr_read: reg=0x%02x ", reg));
	अगर (hp->tcvr_type == none) अणु
		ASD(("no transceiver, value=TCVR_FAILURE\n"));
		वापस TCVR_FAILURE;
	पूर्ण

	अगर (!(hp->happy_flags & HFLAG_FENABLE)) अणु
		ASD(("doing bit bang\n"));
		वापस happy_meal_bb_पढ़ो(hp, tregs, reg);
	पूर्ण

	hme_ग_लिखो32(hp, tregs + TCVR_FRAME,
		    (FRAME_READ | (hp->paddr << 23) | ((reg & 0xff) << 18)));
	जबतक (!(hme_पढ़ो32(hp, tregs + TCVR_FRAME) & 0x10000) && --tries)
		udelay(20);
	अगर (!tries) अणु
		prपूर्णांकk(KERN_ERR "happy meal: Aieee, transceiver MIF read bolixed\n");
		वापस TCVR_FAILURE;
	पूर्ण
	retval = hme_पढ़ो32(hp, tregs + TCVR_FRAME) & 0xffff;
	ASD(("value=%04x\n", retval));
	वापस retval;
पूर्ण

#घोषणा TCVR_WRITE_TRIES  16

अटल व्योम happy_meal_tcvr_ग_लिखो(काष्ठा happy_meal *hp,
				  व्योम __iomem *tregs, पूर्णांक reg,
				  अचिन्हित लघु value)
अणु
	पूर्णांक tries = TCVR_WRITE_TRIES;

	ASD(("happy_meal_tcvr_write: reg=0x%02x value=%04x\n", reg, value));

	/* Welcome to Sun Microप्रणालीs, can I take your order please? */
	अगर (!(hp->happy_flags & HFLAG_FENABLE)) अणु
		happy_meal_bb_ग_लिखो(hp, tregs, reg, value);
		वापस;
	पूर्ण

	/* Would you like fries with that? */
	hme_ग_लिखो32(hp, tregs + TCVR_FRAME,
		    (FRAME_WRITE | (hp->paddr << 23) |
		     ((reg & 0xff) << 18) | (value & 0xffff)));
	जबतक (!(hme_पढ़ो32(hp, tregs + TCVR_FRAME) & 0x10000) && --tries)
		udelay(20);

	/* Anything अन्यथा? */
	अगर (!tries)
		prपूर्णांकk(KERN_ERR "happy meal: Aieee, transceiver MIF write bolixed\n");

	/* Fअगरty-two cents is your change, have a nice day. */
पूर्ण

/* Auto negotiation.  The scheme is very simple.  We have a समयr routine
 * that keeps watching the स्वतः negotiation process as it progresses.
 * The DP83840 is first told to start करोing it's thing, we set up the समय
 * and place the समयr state machine in it's initial state.
 *
 * Here the समयr peeks at the DP83840 status रेजिस्टरs at each click to see
 * अगर the स्वतः negotiation has completed, we assume here that the DP83840 PHY
 * will समय out at some poपूर्णांक and just tell us what (didn't) happen.  For
 * complete coverage we only allow so many of the ticks at this level to run,
 * when this has expired we prपूर्णांक a warning message and try another strategy.
 * This "other" strategy is to क्रमce the पूर्णांकerface पूर्णांकo various speed/duplex
 * configurations and we stop when we see a link-up condition beक्रमe the
 * maximum number of "peek" ticks have occurred.
 *
 * Once a valid link status has been detected we configure the BigMAC and
 * the rest of the Happy Meal to speak the most efficient protocol we could
 * get a clean link क्रम.  The priority क्रम link configurations, highest first
 * is:
 *                 100 Base-T Full Duplex
 *                 100 Base-T Half Duplex
 *                 10 Base-T Full Duplex
 *                 10 Base-T Half Duplex
 *
 * We start a new समयr now, after a successful स्वतः negotiation status has
 * been detected.  This समयr just रुकोs क्रम the link-up bit to get set in
 * the BMCR of the DP83840.  When this occurs we prपूर्णांक a kernel log message
 * describing the link type in use and the fact that it is up.
 *
 * If a fatal error of some sort is संकेतled and detected in the पूर्णांकerrupt
 * service routine, and the chip is reset, or the link is अगरconfig'd करोwn
 * and then back up, this entire process repeats itself all over again.
 */
अटल पूर्णांक try_next_permutation(काष्ठा happy_meal *hp, व्योम __iomem *tregs)
अणु
	hp->sw_bmcr = happy_meal_tcvr_पढ़ो(hp, tregs, MII_BMCR);

	/* Downgrade from full to half duplex.  Only possible
	 * via ethtool.
	 */
	अगर (hp->sw_bmcr & BMCR_FULLDPLX) अणु
		hp->sw_bmcr &= ~(BMCR_FULLDPLX);
		happy_meal_tcvr_ग_लिखो(hp, tregs, MII_BMCR, hp->sw_bmcr);
		वापस 0;
	पूर्ण

	/* Downgrade from 100 to 10. */
	अगर (hp->sw_bmcr & BMCR_SPEED100) अणु
		hp->sw_bmcr &= ~(BMCR_SPEED100);
		happy_meal_tcvr_ग_लिखो(hp, tregs, MII_BMCR, hp->sw_bmcr);
		वापस 0;
	पूर्ण

	/* We've tried everything. */
	वापस -1;
पूर्ण

अटल व्योम display_link_mode(काष्ठा happy_meal *hp, व्योम __iomem *tregs)
अणु
	prपूर्णांकk(KERN_INFO "%s: Link is up using ", hp->dev->name);
	अगर (hp->tcvr_type == बाह्यal)
		prपूर्णांकk("external ");
	अन्यथा
		prपूर्णांकk("internal ");
	prपूर्णांकk("transceiver at ");
	hp->sw_lpa = happy_meal_tcvr_पढ़ो(hp, tregs, MII_LPA);
	अगर (hp->sw_lpa & (LPA_100HALF | LPA_100FULL)) अणु
		अगर (hp->sw_lpa & LPA_100FULL)
			prपूर्णांकk("100Mb/s, Full Duplex.\n");
		अन्यथा
			prपूर्णांकk("100Mb/s, Half Duplex.\n");
	पूर्ण अन्यथा अणु
		अगर (hp->sw_lpa & LPA_10FULL)
			prपूर्णांकk("10Mb/s, Full Duplex.\n");
		अन्यथा
			prपूर्णांकk("10Mb/s, Half Duplex.\n");
	पूर्ण
पूर्ण

अटल व्योम display_क्रमced_link_mode(काष्ठा happy_meal *hp, व्योम __iomem *tregs)
अणु
	prपूर्णांकk(KERN_INFO "%s: Link has been forced up using ", hp->dev->name);
	अगर (hp->tcvr_type == बाह्यal)
		prपूर्णांकk("external ");
	अन्यथा
		prपूर्णांकk("internal ");
	prपूर्णांकk("transceiver at ");
	hp->sw_bmcr = happy_meal_tcvr_पढ़ो(hp, tregs, MII_BMCR);
	अगर (hp->sw_bmcr & BMCR_SPEED100)
		prपूर्णांकk("100Mb/s, ");
	अन्यथा
		prपूर्णांकk("10Mb/s, ");
	अगर (hp->sw_bmcr & BMCR_FULLDPLX)
		prपूर्णांकk("Full Duplex.\n");
	अन्यथा
		prपूर्णांकk("Half Duplex.\n");
पूर्ण

अटल पूर्णांक set_happy_link_modes(काष्ठा happy_meal *hp, व्योम __iomem *tregs)
अणु
	पूर्णांक full;

	/* All we care about is making sure the bigmac tx_cfg has a
	 * proper duplex setting.
	 */
	अगर (hp->समयr_state == arbरुको) अणु
		hp->sw_lpa = happy_meal_tcvr_पढ़ो(hp, tregs, MII_LPA);
		अगर (!(hp->sw_lpa & (LPA_10HALF | LPA_10FULL | LPA_100HALF | LPA_100FULL)))
			जाओ no_response;
		अगर (hp->sw_lpa & LPA_100FULL)
			full = 1;
		अन्यथा अगर (hp->sw_lpa & LPA_100HALF)
			full = 0;
		अन्यथा अगर (hp->sw_lpa & LPA_10FULL)
			full = 1;
		अन्यथा
			full = 0;
	पूर्ण अन्यथा अणु
		/* Forcing a link mode. */
		hp->sw_bmcr = happy_meal_tcvr_पढ़ो(hp, tregs, MII_BMCR);
		अगर (hp->sw_bmcr & BMCR_FULLDPLX)
			full = 1;
		अन्यथा
			full = 0;
	पूर्ण

	/* Beक्रमe changing other bits in the tx_cfg रेजिस्टर, and in
	 * general any of other the TX config रेजिस्टरs too, you
	 * must:
	 * 1) Clear Enable
	 * 2) Poll with पढ़ोs until that bit पढ़ोs back as zero
	 * 3) Make TX configuration changes
	 * 4) Set Enable once more
	 */
	hme_ग_लिखो32(hp, hp->bigmacregs + BMAC_TXCFG,
		    hme_पढ़ो32(hp, hp->bigmacregs + BMAC_TXCFG) &
		    ~(BIGMAC_TXCFG_ENABLE));
	जबतक (hme_पढ़ो32(hp, hp->bigmacregs + BMAC_TXCFG) & BIGMAC_TXCFG_ENABLE)
		barrier();
	अगर (full) अणु
		hp->happy_flags |= HFLAG_FULL;
		hme_ग_लिखो32(hp, hp->bigmacregs + BMAC_TXCFG,
			    hme_पढ़ो32(hp, hp->bigmacregs + BMAC_TXCFG) |
			    BIGMAC_TXCFG_FULLDPLX);
	पूर्ण अन्यथा अणु
		hp->happy_flags &= ~(HFLAG_FULL);
		hme_ग_लिखो32(hp, hp->bigmacregs + BMAC_TXCFG,
			    hme_पढ़ो32(hp, hp->bigmacregs + BMAC_TXCFG) &
			    ~(BIGMAC_TXCFG_FULLDPLX));
	पूर्ण
	hme_ग_लिखो32(hp, hp->bigmacregs + BMAC_TXCFG,
		    hme_पढ़ो32(hp, hp->bigmacregs + BMAC_TXCFG) |
		    BIGMAC_TXCFG_ENABLE);
	वापस 0;
no_response:
	वापस 1;
पूर्ण

अटल पूर्णांक happy_meal_init(काष्ठा happy_meal *hp);

अटल पूर्णांक is_lucent_phy(काष्ठा happy_meal *hp)
अणु
	व्योम __iomem *tregs = hp->tcvregs;
	अचिन्हित लघु mr2, mr3;
	पूर्णांक ret = 0;

	mr2 = happy_meal_tcvr_पढ़ो(hp, tregs, 2);
	mr3 = happy_meal_tcvr_पढ़ो(hp, tregs, 3);
	अगर ((mr2 & 0xffff) == 0x0180 &&
	    ((mr3 & 0xffff) >> 10) == 0x1d)
		ret = 1;

	वापस ret;
पूर्ण

अटल व्योम happy_meal_समयr(काष्ठा समयr_list *t)
अणु
	काष्ठा happy_meal *hp = from_समयr(hp, t, happy_समयr);
	व्योम __iomem *tregs = hp->tcvregs;
	पूर्णांक restart_समयr = 0;

	spin_lock_irq(&hp->happy_lock);

	hp->समयr_ticks++;
	चयन(hp->समयr_state) अणु
	हाल arbरुको:
		/* Only allow क्रम 5 ticks, thats 10 seconds and much too
		 * दीर्घ to रुको क्रम arbitration to complete.
		 */
		अगर (hp->समयr_ticks >= 10) अणु
			/* Enter क्रमce mode. */
	करो_क्रमce_mode:
			hp->sw_bmcr = happy_meal_tcvr_पढ़ो(hp, tregs, MII_BMCR);
			prपूर्णांकk(KERN_NOTICE "%s: Auto-Negotiation unsuccessful, trying force link mode\n",
			       hp->dev->name);
			hp->sw_bmcr = BMCR_SPEED100;
			happy_meal_tcvr_ग_लिखो(hp, tregs, MII_BMCR, hp->sw_bmcr);

			अगर (!is_lucent_phy(hp)) अणु
				/* OK, seems we need करो disable the transceiver क्रम the first
				 * tick to make sure we get an accurate link state at the
				 * second tick.
				 */
				hp->sw_csconfig = happy_meal_tcvr_पढ़ो(hp, tregs, DP83840_CSCONFIG);
				hp->sw_csconfig &= ~(CSCONFIG_TCVDISAB);
				happy_meal_tcvr_ग_लिखो(hp, tregs, DP83840_CSCONFIG, hp->sw_csconfig);
			पूर्ण
			hp->समयr_state = ltryरुको;
			hp->समयr_ticks = 0;
			restart_समयr = 1;
		पूर्ण अन्यथा अणु
			/* Anything पूर्णांकeresting happen? */
			hp->sw_bmsr = happy_meal_tcvr_पढ़ो(hp, tregs, MII_BMSR);
			अगर (hp->sw_bmsr & BMSR_ANEGCOMPLETE) अणु
				पूर्णांक ret;

				/* Just what we've been रुकोing क्रम... */
				ret = set_happy_link_modes(hp, tregs);
				अगर (ret) अणु
					/* Ooops, something bad happened, go to क्रमce
					 * mode.
					 *
					 * XXX Broken hubs which करोn't support 802.3u
					 * XXX स्वतः-negotiation make this happen as well.
					 */
					जाओ करो_क्रमce_mode;
				पूर्ण

				/* Success, at least so far, advance our state engine. */
				hp->समयr_state = lupरुको;
				restart_समयr = 1;
			पूर्ण अन्यथा अणु
				restart_समयr = 1;
			पूर्ण
		पूर्ण
		अवरोध;

	हाल lupरुको:
		/* Auto negotiation was successful and we are aरुकोing a
		 * link up status.  I have decided to let this समयr run
		 * क्रमever until some sort of error is संकेतled, reporting
		 * a message to the user at 10 second पूर्णांकervals.
		 */
		hp->sw_bmsr = happy_meal_tcvr_पढ़ो(hp, tregs, MII_BMSR);
		अगर (hp->sw_bmsr & BMSR_LSTATUS) अणु
			/* Wheee, it's up, display the link mode in use and put
			 * the समयr to sleep.
			 */
			display_link_mode(hp, tregs);
			hp->समयr_state = asleep;
			restart_समयr = 0;
		पूर्ण अन्यथा अणु
			अगर (hp->समयr_ticks >= 10) अणु
				prपूर्णांकk(KERN_NOTICE "%s: Auto negotiation successful, link still "
				       "not completely up.\n", hp->dev->name);
				hp->समयr_ticks = 0;
				restart_समयr = 1;
			पूर्ण अन्यथा अणु
				restart_समयr = 1;
			पूर्ण
		पूर्ण
		अवरोध;

	हाल ltryरुको:
		/* Making the समयout here too दीर्घ can make it take
		 * annoyingly दीर्घ to attempt all of the link mode
		 * permutations, but then again this is essentially
		 * error recovery code क्रम the most part.
		 */
		hp->sw_bmsr = happy_meal_tcvr_पढ़ो(hp, tregs, MII_BMSR);
		hp->sw_csconfig = happy_meal_tcvr_पढ़ो(hp, tregs, DP83840_CSCONFIG);
		अगर (hp->समयr_ticks == 1) अणु
			अगर (!is_lucent_phy(hp)) अणु
				/* Re-enable transceiver, we'll re-enable the transceiver next
				 * tick, then check link state on the following tick.
				 */
				hp->sw_csconfig |= CSCONFIG_TCVDISAB;
				happy_meal_tcvr_ग_लिखो(hp, tregs,
						      DP83840_CSCONFIG, hp->sw_csconfig);
			पूर्ण
			restart_समयr = 1;
			अवरोध;
		पूर्ण
		अगर (hp->समयr_ticks == 2) अणु
			अगर (!is_lucent_phy(hp)) अणु
				hp->sw_csconfig &= ~(CSCONFIG_TCVDISAB);
				happy_meal_tcvr_ग_लिखो(hp, tregs,
						      DP83840_CSCONFIG, hp->sw_csconfig);
			पूर्ण
			restart_समयr = 1;
			अवरोध;
		पूर्ण
		अगर (hp->sw_bmsr & BMSR_LSTATUS) अणु
			/* Force mode selection success. */
			display_क्रमced_link_mode(hp, tregs);
			set_happy_link_modes(hp, tregs); /* XXX error? then what? */
			hp->समयr_state = asleep;
			restart_समयr = 0;
		पूर्ण अन्यथा अणु
			अगर (hp->समयr_ticks >= 4) अणु /* 6 seconds or so... */
				पूर्णांक ret;

				ret = try_next_permutation(hp, tregs);
				अगर (ret == -1) अणु
					/* Aieee, tried them all, reset the
					 * chip and try all over again.
					 */

					/* Let the user know... */
					prपूर्णांकk(KERN_NOTICE "%s: Link down, cable problem?\n",
					       hp->dev->name);

					ret = happy_meal_init(hp);
					अगर (ret) अणु
						/* ho hum... */
						prपूर्णांकk(KERN_ERR "%s: Error, cannot re-init the "
						       "Happy Meal.\n", hp->dev->name);
					पूर्ण
					जाओ out;
				पूर्ण
				अगर (!is_lucent_phy(hp)) अणु
					hp->sw_csconfig = happy_meal_tcvr_पढ़ो(hp, tregs,
									       DP83840_CSCONFIG);
					hp->sw_csconfig |= CSCONFIG_TCVDISAB;
					happy_meal_tcvr_ग_लिखो(hp, tregs,
							      DP83840_CSCONFIG, hp->sw_csconfig);
				पूर्ण
				hp->समयr_ticks = 0;
				restart_समयr = 1;
			पूर्ण अन्यथा अणु
				restart_समयr = 1;
			पूर्ण
		पूर्ण
		अवरोध;

	हाल asleep:
	शेष:
		/* Can't happens.... */
		prपूर्णांकk(KERN_ERR "%s: Aieee, link timer is asleep but we got one anyways!\n",
		       hp->dev->name);
		restart_समयr = 0;
		hp->समयr_ticks = 0;
		hp->समयr_state = asleep; /* foo on you */
		अवरोध;
	पूर्ण

	अगर (restart_समयr) अणु
		hp->happy_समयr.expires = jअगरfies + ((12 * HZ)/10); /* 1.2 sec. */
		add_समयr(&hp->happy_समयr);
	पूर्ण

out:
	spin_unlock_irq(&hp->happy_lock);
पूर्ण

#घोषणा TX_RESET_TRIES     32
#घोषणा RX_RESET_TRIES     32

/* hp->happy_lock must be held */
अटल व्योम happy_meal_tx_reset(काष्ठा happy_meal *hp, व्योम __iomem *bregs)
अणु
	पूर्णांक tries = TX_RESET_TRIES;

	HMD(("happy_meal_tx_reset: reset, "));

	/* Would you like to try our SMCC Delux? */
	hme_ग_लिखो32(hp, bregs + BMAC_TXSWRESET, 0);
	जबतक ((hme_पढ़ो32(hp, bregs + BMAC_TXSWRESET) & 1) && --tries)
		udelay(20);

	/* Lettuce, tomato, buggy hardware (no extra अक्षरge)? */
	अगर (!tries)
		prपूर्णांकk(KERN_ERR "happy meal: Transceiver BigMac ATTACK!");

	/* Take care. */
	HMD(("done\n"));
पूर्ण

/* hp->happy_lock must be held */
अटल व्योम happy_meal_rx_reset(काष्ठा happy_meal *hp, व्योम __iomem *bregs)
अणु
	पूर्णांक tries = RX_RESET_TRIES;

	HMD(("happy_meal_rx_reset: reset, "));

	/* We have a special on GNU/Viking hardware bugs today. */
	hme_ग_लिखो32(hp, bregs + BMAC_RXSWRESET, 0);
	जबतक ((hme_पढ़ो32(hp, bregs + BMAC_RXSWRESET) & 1) && --tries)
		udelay(20);

	/* Will that be all? */
	अगर (!tries)
		prपूर्णांकk(KERN_ERR "happy meal: Receiver BigMac ATTACK!");

	/* Don't क्रमget your vik_1137125_wa.  Have a nice day. */
	HMD(("done\n"));
पूर्ण

#घोषणा STOP_TRIES         16

/* hp->happy_lock must be held */
अटल व्योम happy_meal_stop(काष्ठा happy_meal *hp, व्योम __iomem *gregs)
अणु
	पूर्णांक tries = STOP_TRIES;

	HMD(("happy_meal_stop: reset, "));

	/* We're consolidating our STB products, it's your lucky day. */
	hme_ग_लिखो32(hp, gregs + GREG_SWRESET, GREG_RESET_ALL);
	जबतक (hme_पढ़ो32(hp, gregs + GREG_SWRESET) && --tries)
		udelay(20);

	/* Come back next week when we are "Sun Microelectronics". */
	अगर (!tries)
		prपूर्णांकk(KERN_ERR "happy meal: Fry guys.");

	/* Remember: "Different name, same old buggy as shit hardware." */
	HMD(("done\n"));
पूर्ण

/* hp->happy_lock must be held */
अटल व्योम happy_meal_get_counters(काष्ठा happy_meal *hp, व्योम __iomem *bregs)
अणु
	काष्ठा net_device_stats *stats = &hp->dev->stats;

	stats->rx_crc_errors += hme_पढ़ो32(hp, bregs + BMAC_RCRCECTR);
	hme_ग_लिखो32(hp, bregs + BMAC_RCRCECTR, 0);

	stats->rx_frame_errors += hme_पढ़ो32(hp, bregs + BMAC_UNALECTR);
	hme_ग_लिखो32(hp, bregs + BMAC_UNALECTR, 0);

	stats->rx_length_errors += hme_पढ़ो32(hp, bregs + BMAC_GLECTR);
	hme_ग_लिखो32(hp, bregs + BMAC_GLECTR, 0);

	stats->tx_पातed_errors += hme_पढ़ो32(hp, bregs + BMAC_EXCTR);

	stats->collisions +=
		(hme_पढ़ो32(hp, bregs + BMAC_EXCTR) +
		 hme_पढ़ो32(hp, bregs + BMAC_LTCTR));
	hme_ग_लिखो32(hp, bregs + BMAC_EXCTR, 0);
	hme_ग_लिखो32(hp, bregs + BMAC_LTCTR, 0);
पूर्ण

/* hp->happy_lock must be held */
अटल व्योम happy_meal_poll_stop(काष्ठा happy_meal *hp, व्योम __iomem *tregs)
अणु
	ASD(("happy_meal_poll_stop: "));

	/* If polling disabled or not polling alपढ़ोy, nothing to करो. */
	अगर ((hp->happy_flags & (HFLAG_POLLENABLE | HFLAG_POLL)) !=
	   (HFLAG_POLLENABLE | HFLAG_POLL)) अणु
		HMD(("not polling, return\n"));
		वापस;
	पूर्ण

	/* Shut up the MIF. */
	ASD(("were polling, mif ints off, "));
	hme_ग_लिखो32(hp, tregs + TCVR_IMASK, 0xffff);

	/* Turn off polling. */
	ASD(("polling off, "));
	hme_ग_लिखो32(hp, tregs + TCVR_CFG,
		    hme_पढ़ो32(hp, tregs + TCVR_CFG) & ~(TCV_CFG_PENABLE));

	/* We are no दीर्घer polling. */
	hp->happy_flags &= ~(HFLAG_POLL);

	/* Let the bits set. */
	udelay(200);
	ASD(("done\n"));
पूर्ण

/* Only Sun can take such nice parts and fuck up the programming पूर्णांकerface
 * like this.  Good job guys...
 */
#घोषणा TCVR_RESET_TRIES       16 /* It should reset quickly        */
#घोषणा TCVR_UNISOLATE_TRIES   32 /* Dis-isolation can take दीर्घer. */

/* hp->happy_lock must be held */
अटल पूर्णांक happy_meal_tcvr_reset(काष्ठा happy_meal *hp, व्योम __iomem *tregs)
अणु
	u32 tconfig;
	पूर्णांक result, tries = TCVR_RESET_TRIES;

	tconfig = hme_पढ़ो32(hp, tregs + TCVR_CFG);
	ASD(("happy_meal_tcvr_reset: tcfg<%08lx> ", tconfig));
	अगर (hp->tcvr_type == बाह्यal) अणु
		ASD(("external<"));
		hme_ग_लिखो32(hp, tregs + TCVR_CFG, tconfig & ~(TCV_CFG_PSELECT));
		hp->tcvr_type = पूर्णांकernal;
		hp->paddr = TCV_PADDR_ITX;
		ASD(("ISOLATE,"));
		happy_meal_tcvr_ग_लिखो(hp, tregs, MII_BMCR,
				      (BMCR_LOOPBACK|BMCR_PDOWN|BMCR_ISOLATE));
		result = happy_meal_tcvr_पढ़ो(hp, tregs, MII_BMCR);
		अगर (result == TCVR_FAILURE) अणु
			ASD(("phyread_fail>\n"));
			वापस -1;
		पूर्ण
		ASD(("phyread_ok,PSELECT>"));
		hme_ग_लिखो32(hp, tregs + TCVR_CFG, tconfig | TCV_CFG_PSELECT);
		hp->tcvr_type = बाह्यal;
		hp->paddr = TCV_PADDR_ETX;
	पूर्ण अन्यथा अणु
		अगर (tconfig & TCV_CFG_MDIO1) अणु
			ASD(("internal<PSELECT,"));
			hme_ग_लिखो32(hp, tregs + TCVR_CFG, (tconfig | TCV_CFG_PSELECT));
			ASD(("ISOLATE,"));
			happy_meal_tcvr_ग_लिखो(hp, tregs, MII_BMCR,
					      (BMCR_LOOPBACK|BMCR_PDOWN|BMCR_ISOLATE));
			result = happy_meal_tcvr_पढ़ो(hp, tregs, MII_BMCR);
			अगर (result == TCVR_FAILURE) अणु
				ASD(("phyread_fail>\n"));
				वापस -1;
			पूर्ण
			ASD(("phyread_ok,~PSELECT>"));
			hme_ग_लिखो32(hp, tregs + TCVR_CFG, (tconfig & ~(TCV_CFG_PSELECT)));
			hp->tcvr_type = पूर्णांकernal;
			hp->paddr = TCV_PADDR_ITX;
		पूर्ण
	पूर्ण

	ASD(("BMCR_RESET "));
	happy_meal_tcvr_ग_लिखो(hp, tregs, MII_BMCR, BMCR_RESET);

	जबतक (--tries) अणु
		result = happy_meal_tcvr_पढ़ो(hp, tregs, MII_BMCR);
		अगर (result == TCVR_FAILURE)
			वापस -1;
		hp->sw_bmcr = result;
		अगर (!(result & BMCR_RESET))
			अवरोध;
		udelay(20);
	पूर्ण
	अगर (!tries) अणु
		ASD(("BMCR RESET FAILED!\n"));
		वापस -1;
	पूर्ण
	ASD(("RESET_OK\n"));

	/* Get fresh copies of the PHY रेजिस्टरs. */
	hp->sw_bmsr      = happy_meal_tcvr_पढ़ो(hp, tregs, MII_BMSR);
	hp->sw_physid1   = happy_meal_tcvr_पढ़ो(hp, tregs, MII_PHYSID1);
	hp->sw_physid2   = happy_meal_tcvr_पढ़ो(hp, tregs, MII_PHYSID2);
	hp->sw_advertise = happy_meal_tcvr_पढ़ो(hp, tregs, MII_ADVERTISE);

	ASD(("UNISOLATE"));
	hp->sw_bmcr &= ~(BMCR_ISOLATE);
	happy_meal_tcvr_ग_लिखो(hp, tregs, MII_BMCR, hp->sw_bmcr);

	tries = TCVR_UNISOLATE_TRIES;
	जबतक (--tries) अणु
		result = happy_meal_tcvr_पढ़ो(hp, tregs, MII_BMCR);
		अगर (result == TCVR_FAILURE)
			वापस -1;
		अगर (!(result & BMCR_ISOLATE))
			अवरोध;
		udelay(20);
	पूर्ण
	अगर (!tries) अणु
		ASD((" FAILED!\n"));
		वापस -1;
	पूर्ण
	ASD((" SUCCESS and CSCONFIG_DFBYPASS\n"));
	अगर (!is_lucent_phy(hp)) अणु
		result = happy_meal_tcvr_पढ़ो(hp, tregs,
					      DP83840_CSCONFIG);
		happy_meal_tcvr_ग_लिखो(hp, tregs,
				      DP83840_CSCONFIG, (result | CSCONFIG_DFBYPASS));
	पूर्ण
	वापस 0;
पूर्ण

/* Figure out whether we have an पूर्णांकernal or बाह्यal transceiver.
 *
 * hp->happy_lock must be held
 */
अटल व्योम happy_meal_transceiver_check(काष्ठा happy_meal *hp, व्योम __iomem *tregs)
अणु
	अचिन्हित दीर्घ tconfig = hme_पढ़ो32(hp, tregs + TCVR_CFG);

	ASD(("happy_meal_transceiver_check: tcfg=%08lx ", tconfig));
	अगर (hp->happy_flags & HFLAG_POLL) अणु
		/* If we are polling, we must stop to get the transceiver type. */
		ASD(("<polling> "));
		अगर (hp->tcvr_type == पूर्णांकernal) अणु
			अगर (tconfig & TCV_CFG_MDIO1) अणु
				ASD(("<internal> <poll stop> "));
				happy_meal_poll_stop(hp, tregs);
				hp->paddr = TCV_PADDR_ETX;
				hp->tcvr_type = बाह्यal;
				ASD(("<external>\n"));
				tconfig &= ~(TCV_CFG_PENABLE);
				tconfig |= TCV_CFG_PSELECT;
				hme_ग_लिखो32(hp, tregs + TCVR_CFG, tconfig);
			पूर्ण
		पूर्ण अन्यथा अणु
			अगर (hp->tcvr_type == बाह्यal) अणु
				ASD(("<external> "));
				अगर (!(hme_पढ़ो32(hp, tregs + TCVR_STATUS) >> 16)) अणु
					ASD(("<poll stop> "));
					happy_meal_poll_stop(hp, tregs);
					hp->paddr = TCV_PADDR_ITX;
					hp->tcvr_type = पूर्णांकernal;
					ASD(("<internal>\n"));
					hme_ग_लिखो32(hp, tregs + TCVR_CFG,
						    hme_पढ़ो32(hp, tregs + TCVR_CFG) &
						    ~(TCV_CFG_PSELECT));
				पूर्ण
				ASD(("\n"));
			पूर्ण अन्यथा अणु
				ASD(("<none>\n"));
			पूर्ण
		पूर्ण
	पूर्ण अन्यथा अणु
		u32 reपढ़ो = hme_पढ़ो32(hp, tregs + TCVR_CFG);

		/* Else we can just work off of the MDIO bits. */
		ASD(("<not polling> "));
		अगर (reपढ़ो & TCV_CFG_MDIO1) अणु
			hme_ग_लिखो32(hp, tregs + TCVR_CFG, tconfig | TCV_CFG_PSELECT);
			hp->paddr = TCV_PADDR_ETX;
			hp->tcvr_type = बाह्यal;
			ASD(("<external>\n"));
		पूर्ण अन्यथा अणु
			अगर (reपढ़ो & TCV_CFG_MDIO0) अणु
				hme_ग_लिखो32(hp, tregs + TCVR_CFG,
					    tconfig & ~(TCV_CFG_PSELECT));
				hp->paddr = TCV_PADDR_ITX;
				hp->tcvr_type = पूर्णांकernal;
				ASD(("<internal>\n"));
			पूर्ण अन्यथा अणु
				prपूर्णांकk(KERN_ERR "happy meal: Transceiver and a coke please.");
				hp->tcvr_type = none; /* Grrr... */
				ASD(("<none>\n"));
			पूर्ण
		पूर्ण
	पूर्ण
पूर्ण

/* The receive ring buffers are a bit tricky to get right.  Here goes...
 *
 * The buffers we dma पूर्णांकo must be 64 byte aligned.  So we use a special
 * alloc_skb() routine क्रम the happy meal to allocate 64 bytes more than
 * we really need.
 *
 * We use skb_reserve() to align the data block we get in the skb.  We
 * also program the etxregs->cfg रेजिस्टर to use an offset of 2.  This
 * imperical स्थिरant plus the ethernet header size will always leave
 * us with a nicely aligned ip header once we pass things up to the
 * protocol layers.
 *
 * The numbers work out to:
 *
 *         Max ethernet frame size         1518
 *         Ethernet header size              14
 *         Happy Meal base offset             2
 *
 * Say a skb data area is at 0xf001b010, and its size alloced is
 * (ETH_FRAME_LEN + 64 + 2) = (1514 + 64 + 2) = 1580 bytes.
 *
 * First our alloc_skb() routine aligns the data base to a 64 byte
 * boundary.  We now have 0xf001b040 as our skb data address.  We
 * plug this पूर्णांकo the receive descriptor address.
 *
 * Next, we skb_reserve() 2 bytes to account क्रम the Happy Meal offset.
 * So now the data we will end up looking at starts at 0xf001b042.  When
 * the packet arrives, we will check out the size received and subtract
 * this from the skb->length.  Then we just pass the packet up to the
 * protocols as is, and allocate a new skb to replace this slot we have
 * just received from.
 *
 * The ethernet layer will strip the ether header from the front of the
 * skb we just sent to it, this leaves us with the ip header sitting
 * nicely aligned at 0xf001b050.  Also, क्रम tcp and udp packets the
 * Happy Meal has even checksummed the tcp/udp data क्रम us.  The 16
 * bit checksum is obtained from the low bits of the receive descriptor
 * flags, thus:
 *
 * 	skb->csum = rxd->rx_flags & 0xffff;
 * 	skb->ip_summed = CHECKSUM_COMPLETE;
 *
 * beक्रमe sending off the skb to the protocols, and we are good as gold.
 */
अटल व्योम happy_meal_clean_rings(काष्ठा happy_meal *hp)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < RX_RING_SIZE; i++) अणु
		अगर (hp->rx_skbs[i] != शून्य) अणु
			काष्ठा sk_buff *skb = hp->rx_skbs[i];
			काष्ठा happy_meal_rxd *rxd;
			u32 dma_addr;

			rxd = &hp->happy_block->happy_meal_rxd[i];
			dma_addr = hme_पढ़ो_desc32(hp, &rxd->rx_addr);
			dma_unmap_single(hp->dma_dev, dma_addr,
					 RX_BUF_ALLOC_SIZE, DMA_FROM_DEVICE);
			dev_kमुक्त_skb_any(skb);
			hp->rx_skbs[i] = शून्य;
		पूर्ण
	पूर्ण

	क्रम (i = 0; i < TX_RING_SIZE; i++) अणु
		अगर (hp->tx_skbs[i] != शून्य) अणु
			काष्ठा sk_buff *skb = hp->tx_skbs[i];
			काष्ठा happy_meal_txd *txd;
			u32 dma_addr;
			पूर्णांक frag;

			hp->tx_skbs[i] = शून्य;

			क्रम (frag = 0; frag <= skb_shinfo(skb)->nr_frags; frag++) अणु
				txd = &hp->happy_block->happy_meal_txd[i];
				dma_addr = hme_पढ़ो_desc32(hp, &txd->tx_addr);
				अगर (!frag)
					dma_unmap_single(hp->dma_dev, dma_addr,
							 (hme_पढ़ो_desc32(hp, &txd->tx_flags)
							  & TXFLAG_SIZE),
							 DMA_TO_DEVICE);
				अन्यथा
					dma_unmap_page(hp->dma_dev, dma_addr,
							 (hme_पढ़ो_desc32(hp, &txd->tx_flags)
							  & TXFLAG_SIZE),
							 DMA_TO_DEVICE);

				अगर (frag != skb_shinfo(skb)->nr_frags)
					i++;
			पूर्ण

			dev_kमुक्त_skb_any(skb);
		पूर्ण
	पूर्ण
पूर्ण

/* hp->happy_lock must be held */
अटल व्योम happy_meal_init_rings(काष्ठा happy_meal *hp)
अणु
	काष्ठा hmeal_init_block *hb = hp->happy_block;
	पूर्णांक i;

	HMD(("happy_meal_init_rings: counters to zero, "));
	hp->rx_new = hp->rx_old = hp->tx_new = hp->tx_old = 0;

	/* Free any skippy bufs left around in the rings. */
	HMD(("clean, "));
	happy_meal_clean_rings(hp);

	/* Now get new skippy bufs क्रम the receive ring. */
	HMD(("init rxring, "));
	क्रम (i = 0; i < RX_RING_SIZE; i++) अणु
		काष्ठा sk_buff *skb;
		u32 mapping;

		skb = happy_meal_alloc_skb(RX_BUF_ALLOC_SIZE, GFP_ATOMIC);
		अगर (!skb) अणु
			hme_ग_लिखो_rxd(hp, &hb->happy_meal_rxd[i], 0, 0);
			जारी;
		पूर्ण
		hp->rx_skbs[i] = skb;

		/* Because we reserve afterwards. */
		skb_put(skb, (ETH_FRAME_LEN + RX_OFFSET + 4));
		mapping = dma_map_single(hp->dma_dev, skb->data, RX_BUF_ALLOC_SIZE,
					 DMA_FROM_DEVICE);
		अगर (dma_mapping_error(hp->dma_dev, mapping)) अणु
			dev_kमुक्त_skb_any(skb);
			hme_ग_लिखो_rxd(hp, &hb->happy_meal_rxd[i], 0, 0);
			जारी;
		पूर्ण
		hme_ग_लिखो_rxd(hp, &hb->happy_meal_rxd[i],
			      (RXFLAG_OWN | ((RX_BUF_ALLOC_SIZE - RX_OFFSET) << 16)),
			      mapping);
		skb_reserve(skb, RX_OFFSET);
	पूर्ण

	HMD(("init txring, "));
	क्रम (i = 0; i < TX_RING_SIZE; i++)
		hme_ग_लिखो_txd(hp, &hb->happy_meal_txd[i], 0, 0);

	HMD(("done\n"));
पूर्ण

/* hp->happy_lock must be held */
अटल व्योम
happy_meal_begin_स्वतः_negotiation(काष्ठा happy_meal *hp,
				  व्योम __iomem *tregs,
				  स्थिर काष्ठा ethtool_link_ksettings *ep)
अणु
	पूर्णांक समयout;

	/* Read all of the रेजिस्टरs we are पूर्णांकerested in now. */
	hp->sw_bmsr      = happy_meal_tcvr_पढ़ो(hp, tregs, MII_BMSR);
	hp->sw_bmcr      = happy_meal_tcvr_पढ़ो(hp, tregs, MII_BMCR);
	hp->sw_physid1   = happy_meal_tcvr_पढ़ो(hp, tregs, MII_PHYSID1);
	hp->sw_physid2   = happy_meal_tcvr_पढ़ो(hp, tregs, MII_PHYSID2);

	/* XXX Check BMSR_ANEGCAPABLE, should not be necessary though. */

	hp->sw_advertise = happy_meal_tcvr_पढ़ो(hp, tregs, MII_ADVERTISE);
	अगर (!ep || ep->base.स्वतःneg == AUTONEG_ENABLE) अणु
		/* Advertise everything we can support. */
		अगर (hp->sw_bmsr & BMSR_10HALF)
			hp->sw_advertise |= (ADVERTISE_10HALF);
		अन्यथा
			hp->sw_advertise &= ~(ADVERTISE_10HALF);

		अगर (hp->sw_bmsr & BMSR_10FULL)
			hp->sw_advertise |= (ADVERTISE_10FULL);
		अन्यथा
			hp->sw_advertise &= ~(ADVERTISE_10FULL);
		अगर (hp->sw_bmsr & BMSR_100HALF)
			hp->sw_advertise |= (ADVERTISE_100HALF);
		अन्यथा
			hp->sw_advertise &= ~(ADVERTISE_100HALF);
		अगर (hp->sw_bmsr & BMSR_100FULL)
			hp->sw_advertise |= (ADVERTISE_100FULL);
		अन्यथा
			hp->sw_advertise &= ~(ADVERTISE_100FULL);
		happy_meal_tcvr_ग_लिखो(hp, tregs, MII_ADVERTISE, hp->sw_advertise);

		/* XXX Currently no Happy Meal cards I know off support 100BaseT4,
		 * XXX and this is because the DP83840 करोes not support it, changes
		 * XXX would need to be made to the tx/rx logic in the driver as well
		 * XXX so I completely skip checking क्रम it in the BMSR क्रम now.
		 */

#अगर_घोषित AUTO_SWITCH_DEBUG
		ASD(("%s: Advertising [ ", hp->dev->name));
		अगर (hp->sw_advertise & ADVERTISE_10HALF)
			ASD(("10H "));
		अगर (hp->sw_advertise & ADVERTISE_10FULL)
			ASD(("10F "));
		अगर (hp->sw_advertise & ADVERTISE_100HALF)
			ASD(("100H "));
		अगर (hp->sw_advertise & ADVERTISE_100FULL)
			ASD(("100F "));
#पूर्ण_अगर

		/* Enable Auto-Negotiation, this is usually on alपढ़ोy... */
		hp->sw_bmcr |= BMCR_ANENABLE;
		happy_meal_tcvr_ग_लिखो(hp, tregs, MII_BMCR, hp->sw_bmcr);

		/* Restart it to make sure it is going. */
		hp->sw_bmcr |= BMCR_ANRESTART;
		happy_meal_tcvr_ग_लिखो(hp, tregs, MII_BMCR, hp->sw_bmcr);

		/* BMCR_ANRESTART self clears when the process has begun. */

		समयout = 64;  /* More than enough. */
		जबतक (--समयout) अणु
			hp->sw_bmcr = happy_meal_tcvr_पढ़ो(hp, tregs, MII_BMCR);
			अगर (!(hp->sw_bmcr & BMCR_ANRESTART))
				अवरोध; /* got it. */
			udelay(10);
		पूर्ण
		अगर (!समयout) अणु
			prपूर्णांकk(KERN_ERR "%s: Happy Meal would not start auto negotiation "
			       "BMCR=0x%04x\n", hp->dev->name, hp->sw_bmcr);
			prपूर्णांकk(KERN_NOTICE "%s: Performing force link detection.\n",
			       hp->dev->name);
			जाओ क्रमce_link;
		पूर्ण अन्यथा अणु
			hp->समयr_state = arbरुको;
		पूर्ण
	पूर्ण अन्यथा अणु
क्रमce_link:
		/* Force the link up, trying first a particular mode.
		 * Either we are here at the request of ethtool or
		 * because the Happy Meal would not start to स्वतःneg.
		 */

		/* Disable स्वतः-negotiation in BMCR, enable the duplex and
		 * speed setting, init the समयr state machine, and fire it off.
		 */
		अगर (!ep || ep->base.स्वतःneg == AUTONEG_ENABLE) अणु
			hp->sw_bmcr = BMCR_SPEED100;
		पूर्ण अन्यथा अणु
			अगर (ep->base.speed == SPEED_100)
				hp->sw_bmcr = BMCR_SPEED100;
			अन्यथा
				hp->sw_bmcr = 0;
			अगर (ep->base.duplex == DUPLEX_FULL)
				hp->sw_bmcr |= BMCR_FULLDPLX;
		पूर्ण
		happy_meal_tcvr_ग_लिखो(hp, tregs, MII_BMCR, hp->sw_bmcr);

		अगर (!is_lucent_phy(hp)) अणु
			/* OK, seems we need करो disable the transceiver क्रम the first
			 * tick to make sure we get an accurate link state at the
			 * second tick.
			 */
			hp->sw_csconfig = happy_meal_tcvr_पढ़ो(hp, tregs,
							       DP83840_CSCONFIG);
			hp->sw_csconfig &= ~(CSCONFIG_TCVDISAB);
			happy_meal_tcvr_ग_लिखो(hp, tregs, DP83840_CSCONFIG,
					      hp->sw_csconfig);
		पूर्ण
		hp->समयr_state = ltryरुको;
	पूर्ण

	hp->समयr_ticks = 0;
	hp->happy_समयr.expires = jअगरfies + (12 * HZ)/10;  /* 1.2 sec. */
	add_समयr(&hp->happy_समयr);
पूर्ण

/* hp->happy_lock must be held */
अटल पूर्णांक happy_meal_init(काष्ठा happy_meal *hp)
अणु
	व्योम __iomem *gregs        = hp->gregs;
	व्योम __iomem *etxregs      = hp->etxregs;
	व्योम __iomem *erxregs      = hp->erxregs;
	व्योम __iomem *bregs        = hp->bigmacregs;
	व्योम __iomem *tregs        = hp->tcvregs;
	u32 regपंचांगp, rxcfg;
	अचिन्हित अक्षर *e = &hp->dev->dev_addr[0];

	/* If स्वतः-negotiation समयr is running, समाप्त it. */
	del_समयr(&hp->happy_समयr);

	HMD(("happy_meal_init: happy_flags[%08x] ",
	     hp->happy_flags));
	अगर (!(hp->happy_flags & HFLAG_INIT)) अणु
		HMD(("set HFLAG_INIT, "));
		hp->happy_flags |= HFLAG_INIT;
		happy_meal_get_counters(hp, bregs);
	पूर्ण

	/* Stop polling. */
	HMD(("to happy_meal_poll_stop\n"));
	happy_meal_poll_stop(hp, tregs);

	/* Stop transmitter and receiver. */
	HMD(("happy_meal_init: to happy_meal_stop\n"));
	happy_meal_stop(hp, gregs);

	/* Alloc and reset the tx/rx descriptor chains. */
	HMD(("happy_meal_init: to happy_meal_init_rings\n"));
	happy_meal_init_rings(hp);

	/* Shut up the MIF. */
	HMD(("happy_meal_init: Disable all MIF irqs (old[%08x]), ",
	     hme_पढ़ो32(hp, tregs + TCVR_IMASK)));
	hme_ग_लिखो32(hp, tregs + TCVR_IMASK, 0xffff);

	/* See अगर we can enable the MIF frame on this card to speak to the DP83840. */
	अगर (hp->happy_flags & HFLAG_FENABLE) अणु
		HMD(("use frame old[%08x], ",
		     hme_पढ़ो32(hp, tregs + TCVR_CFG)));
		hme_ग_लिखो32(hp, tregs + TCVR_CFG,
			    hme_पढ़ो32(hp, tregs + TCVR_CFG) & ~(TCV_CFG_BENABLE));
	पूर्ण अन्यथा अणु
		HMD(("use bitbang old[%08x], ",
		     hme_पढ़ो32(hp, tregs + TCVR_CFG)));
		hme_ग_लिखो32(hp, tregs + TCVR_CFG,
			    hme_पढ़ो32(hp, tregs + TCVR_CFG) | TCV_CFG_BENABLE);
	पूर्ण

	/* Check the state of the transceiver. */
	HMD(("to happy_meal_transceiver_check\n"));
	happy_meal_transceiver_check(hp, tregs);

	/* Put the Big Mac पूर्णांकo a sane state. */
	HMD(("happy_meal_init: "));
	चयन(hp->tcvr_type) अणु
	हाल none:
		/* Cannot operate अगर we करोn't know the transceiver type! */
		HMD(("AAIEEE no transceiver type, EAGAIN"));
		वापस -EAGAIN;

	हाल पूर्णांकernal:
		/* Using the MII buffers. */
		HMD(("internal, using MII, "));
		hme_ग_लिखो32(hp, bregs + BMAC_XIFCFG, 0);
		अवरोध;

	हाल बाह्यal:
		/* Not using the MII, disable it. */
		HMD(("external, disable MII, "));
		hme_ग_लिखो32(hp, bregs + BMAC_XIFCFG, BIGMAC_XCFG_MIIDISAB);
		अवरोध;
	पूर्ण

	अगर (happy_meal_tcvr_reset(hp, tregs))
		वापस -EAGAIN;

	/* Reset the Happy Meal Big Mac transceiver and the receiver. */
	HMD(("tx/rx reset, "));
	happy_meal_tx_reset(hp, bregs);
	happy_meal_rx_reset(hp, bregs);

	/* Set jam size and पूर्णांकer-packet gaps to reasonable शेषs. */
	HMD(("jsize/ipg1/ipg2, "));
	hme_ग_लिखो32(hp, bregs + BMAC_JSIZE, DEFAULT_JAMSIZE);
	hme_ग_लिखो32(hp, bregs + BMAC_IGAP1, DEFAULT_IPG1);
	hme_ग_लिखो32(hp, bregs + BMAC_IGAP2, DEFAULT_IPG2);

	/* Load up the MAC address and अक्रमom seed. */
	HMD(("rseed/macaddr, "));

	/* The करोcs recommend to use the 10LSB of our MAC here. */
	hme_ग_लिखो32(hp, bregs + BMAC_RSEED, ((e[5] | e[4]<<8)&0x3ff));

	hme_ग_लिखो32(hp, bregs + BMAC_MACADDR2, ((e[4] << 8) | e[5]));
	hme_ग_लिखो32(hp, bregs + BMAC_MACADDR1, ((e[2] << 8) | e[3]));
	hme_ग_लिखो32(hp, bregs + BMAC_MACADDR0, ((e[0] << 8) | e[1]));

	HMD(("htable, "));
	अगर ((hp->dev->flags & IFF_ALLMULTI) ||
	    (netdev_mc_count(hp->dev) > 64)) अणु
		hme_ग_लिखो32(hp, bregs + BMAC_HTABLE0, 0xffff);
		hme_ग_लिखो32(hp, bregs + BMAC_HTABLE1, 0xffff);
		hme_ग_लिखो32(hp, bregs + BMAC_HTABLE2, 0xffff);
		hme_ग_लिखो32(hp, bregs + BMAC_HTABLE3, 0xffff);
	पूर्ण अन्यथा अगर ((hp->dev->flags & IFF_PROMISC) == 0) अणु
		u16 hash_table[4];
		काष्ठा netdev_hw_addr *ha;
		u32 crc;

		स_रखो(hash_table, 0, माप(hash_table));
		netdev_क्रम_each_mc_addr(ha, hp->dev) अणु
			crc = ether_crc_le(6, ha->addr);
			crc >>= 26;
			hash_table[crc >> 4] |= 1 << (crc & 0xf);
		पूर्ण
		hme_ग_लिखो32(hp, bregs + BMAC_HTABLE0, hash_table[0]);
		hme_ग_लिखो32(hp, bregs + BMAC_HTABLE1, hash_table[1]);
		hme_ग_लिखो32(hp, bregs + BMAC_HTABLE2, hash_table[2]);
		hme_ग_लिखो32(hp, bregs + BMAC_HTABLE3, hash_table[3]);
	पूर्ण अन्यथा अणु
		hme_ग_लिखो32(hp, bregs + BMAC_HTABLE3, 0);
		hme_ग_लिखो32(hp, bregs + BMAC_HTABLE2, 0);
		hme_ग_लिखो32(hp, bregs + BMAC_HTABLE1, 0);
		hme_ग_लिखो32(hp, bregs + BMAC_HTABLE0, 0);
	पूर्ण

	/* Set the RX and TX ring ptrs. */
	HMD(("ring ptrs rxr[%08x] txr[%08x]\n",
	     ((__u32)hp->hblock_dvma + hblock_offset(happy_meal_rxd, 0)),
	     ((__u32)hp->hblock_dvma + hblock_offset(happy_meal_txd, 0))));
	hme_ग_लिखो32(hp, erxregs + ERX_RING,
		    ((__u32)hp->hblock_dvma + hblock_offset(happy_meal_rxd, 0)));
	hme_ग_लिखो32(hp, etxregs + ETX_RING,
		    ((__u32)hp->hblock_dvma + hblock_offset(happy_meal_txd, 0)));

	/* Parity issues in the ERX unit of some HME revisions can cause some
	 * रेजिस्टरs to not be written unless their parity is even.  Detect such
	 * lost ग_लिखोs and simply reग_लिखो with a low bit set (which will be ignored
	 * since the rxring needs to be 2K aligned).
	 */
	अगर (hme_पढ़ो32(hp, erxregs + ERX_RING) !=
	    ((__u32)hp->hblock_dvma + hblock_offset(happy_meal_rxd, 0)))
		hme_ग_लिखो32(hp, erxregs + ERX_RING,
			    ((__u32)hp->hblock_dvma + hblock_offset(happy_meal_rxd, 0))
			    | 0x4);

	/* Set the supported burst sizes. */
	HMD(("happy_meal_init: old[%08x] bursts<",
	     hme_पढ़ो32(hp, gregs + GREG_CFG)));

#अगर_अघोषित CONFIG_SPARC
	/* It is always PCI and can handle 64byte bursts. */
	hme_ग_लिखो32(hp, gregs + GREG_CFG, GREG_CFG_BURST64);
#अन्यथा
	अगर ((hp->happy_bursts & DMA_BURST64) &&
	    ((hp->happy_flags & HFLAG_PCI) != 0
#अगर_घोषित CONFIG_SBUS
	     || sbus_can_burst64()
#पूर्ण_अगर
	     || 0)) अणु
		u32 gcfg = GREG_CFG_BURST64;

		/* I have no idea अगर I should set the extended
		 * transfer mode bit क्रम Cheerio, so क्रम now I
		 * करो not.  -DaveM
		 */
#अगर_घोषित CONFIG_SBUS
		अगर ((hp->happy_flags & HFLAG_PCI) == 0) अणु
			काष्ठा platक्रमm_device *op = hp->happy_dev;
			अगर (sbus_can_dma_64bit()) अणु
				sbus_set_sbus64(&op->dev,
						hp->happy_bursts);
				gcfg |= GREG_CFG_64BIT;
			पूर्ण
		पूर्ण
#पूर्ण_अगर

		HMD(("64>"));
		hme_ग_लिखो32(hp, gregs + GREG_CFG, gcfg);
	पूर्ण अन्यथा अगर (hp->happy_bursts & DMA_BURST32) अणु
		HMD(("32>"));
		hme_ग_लिखो32(hp, gregs + GREG_CFG, GREG_CFG_BURST32);
	पूर्ण अन्यथा अगर (hp->happy_bursts & DMA_BURST16) अणु
		HMD(("16>"));
		hme_ग_लिखो32(hp, gregs + GREG_CFG, GREG_CFG_BURST16);
	पूर्ण अन्यथा अणु
		HMD(("XXX>"));
		hme_ग_लिखो32(hp, gregs + GREG_CFG, 0);
	पूर्ण
#पूर्ण_अगर /* CONFIG_SPARC */

	/* Turn off पूर्णांकerrupts we करो not want to hear. */
	HMD((", enable global interrupts, "));
	hme_ग_लिखो32(hp, gregs + GREG_IMASK,
		    (GREG_IMASK_GOTFRAME | GREG_IMASK_RCNTEXP |
		     GREG_IMASK_SENTFRAME | GREG_IMASK_TXPERR));

	/* Set the transmit ring buffer size. */
	HMD(("tx rsize=%d oreg[%08x], ", (पूर्णांक)TX_RING_SIZE,
	     hme_पढ़ो32(hp, etxregs + ETX_RSIZE)));
	hme_ग_लिखो32(hp, etxregs + ETX_RSIZE, (TX_RING_SIZE >> ETX_RSIZE_SHIFT) - 1);

	/* Enable transmitter DVMA. */
	HMD(("tx dma enable old[%08x], ",
	     hme_पढ़ो32(hp, etxregs + ETX_CFG)));
	hme_ग_लिखो32(hp, etxregs + ETX_CFG,
		    hme_पढ़ो32(hp, etxregs + ETX_CFG) | ETX_CFG_DMAENABLE);

	/* This chip really rots, क्रम the receiver someबार when you
	 * ग_लिखो to its control रेजिस्टरs not all the bits get there
	 * properly.  I cannot think of a sane way to provide complete
	 * coverage क्रम this hardware bug yet.
	 */
	HMD(("erx regs bug old[%08x]\n",
	     hme_पढ़ो32(hp, erxregs + ERX_CFG)));
	hme_ग_लिखो32(hp, erxregs + ERX_CFG, ERX_CFG_DEFAULT(RX_OFFSET));
	regपंचांगp = hme_पढ़ो32(hp, erxregs + ERX_CFG);
	hme_ग_लिखो32(hp, erxregs + ERX_CFG, ERX_CFG_DEFAULT(RX_OFFSET));
	अगर (hme_पढ़ो32(hp, erxregs + ERX_CFG) != ERX_CFG_DEFAULT(RX_OFFSET)) अणु
		prपूर्णांकk(KERN_ERR "happy meal: Eieee, rx config register gets greasy fries.\n");
		prपूर्णांकk(KERN_ERR "happy meal: Trying to set %08x, reread gives %08x\n",
		       ERX_CFG_DEFAULT(RX_OFFSET), regपंचांगp);
		/* XXX Should वापस failure here... */
	पूर्ण

	/* Enable Big Mac hash table filter. */
	HMD(("happy_meal_init: enable hash rx_cfg_old[%08x], ",
	     hme_पढ़ो32(hp, bregs + BMAC_RXCFG)));
	rxcfg = BIGMAC_RXCFG_HENABLE | BIGMAC_RXCFG_REJME;
	अगर (hp->dev->flags & IFF_PROMISC)
		rxcfg |= BIGMAC_RXCFG_PMISC;
	hme_ग_लिखो32(hp, bregs + BMAC_RXCFG, rxcfg);

	/* Let the bits settle in the chip. */
	udelay(10);

	/* Ok, configure the Big Mac transmitter. */
	HMD(("BIGMAC init, "));
	regपंचांगp = 0;
	अगर (hp->happy_flags & HFLAG_FULL)
		regपंचांगp |= BIGMAC_TXCFG_FULLDPLX;

	/* Don't turn on the "don't give up" bit क्रम now.  It could cause hme
	 * to deadlock with the PHY अगर a Jabber occurs.
	 */
	hme_ग_लिखो32(hp, bregs + BMAC_TXCFG, regपंचांगp /*| BIGMAC_TXCFG_DGIVEUP*/);

	/* Give up after 16 TX attempts. */
	hme_ग_लिखो32(hp, bregs + BMAC_ALIMIT, 16);

	/* Enable the output drivers no matter what. */
	regपंचांगp = BIGMAC_XCFG_ODENABLE;

	/* If card can करो lance mode, enable it. */
	अगर (hp->happy_flags & HFLAG_LANCE)
		regपंचांगp |= (DEFAULT_IPG0 << 5) | BIGMAC_XCFG_LANCE;

	/* Disable the MII buffers अगर using बाह्यal transceiver. */
	अगर (hp->tcvr_type == बाह्यal)
		regपंचांगp |= BIGMAC_XCFG_MIIDISAB;

	HMD(("XIF config old[%08x], ",
	     hme_पढ़ो32(hp, bregs + BMAC_XIFCFG)));
	hme_ग_लिखो32(hp, bregs + BMAC_XIFCFG, regपंचांगp);

	/* Start things up. */
	HMD(("tx old[%08x] and rx [%08x] ON!\n",
	     hme_पढ़ो32(hp, bregs + BMAC_TXCFG),
	     hme_पढ़ो32(hp, bregs + BMAC_RXCFG)));

	/* Set larger TX/RX size to allow क्रम 802.1q */
	hme_ग_लिखो32(hp, bregs + BMAC_TXMAX, ETH_FRAME_LEN + 8);
	hme_ग_लिखो32(hp, bregs + BMAC_RXMAX, ETH_FRAME_LEN + 8);

	hme_ग_लिखो32(hp, bregs + BMAC_TXCFG,
		    hme_पढ़ो32(hp, bregs + BMAC_TXCFG) | BIGMAC_TXCFG_ENABLE);
	hme_ग_लिखो32(hp, bregs + BMAC_RXCFG,
		    hme_पढ़ो32(hp, bregs + BMAC_RXCFG) | BIGMAC_RXCFG_ENABLE);

	/* Get the स्वतःnegotiation started, and the watch समयr ticking. */
	happy_meal_begin_स्वतः_negotiation(hp, tregs, शून्य);

	/* Success. */
	वापस 0;
पूर्ण

/* hp->happy_lock must be held */
अटल व्योम happy_meal_set_initial_advertisement(काष्ठा happy_meal *hp)
अणु
	व्योम __iomem *tregs	= hp->tcvregs;
	व्योम __iomem *bregs	= hp->bigmacregs;
	व्योम __iomem *gregs	= hp->gregs;

	happy_meal_stop(hp, gregs);
	hme_ग_लिखो32(hp, tregs + TCVR_IMASK, 0xffff);
	अगर (hp->happy_flags & HFLAG_FENABLE)
		hme_ग_लिखो32(hp, tregs + TCVR_CFG,
			    hme_पढ़ो32(hp, tregs + TCVR_CFG) & ~(TCV_CFG_BENABLE));
	अन्यथा
		hme_ग_लिखो32(hp, tregs + TCVR_CFG,
			    hme_पढ़ो32(hp, tregs + TCVR_CFG) | TCV_CFG_BENABLE);
	happy_meal_transceiver_check(hp, tregs);
	चयन(hp->tcvr_type) अणु
	हाल none:
		वापस;
	हाल पूर्णांकernal:
		hme_ग_लिखो32(hp, bregs + BMAC_XIFCFG, 0);
		अवरोध;
	हाल बाह्यal:
		hme_ग_लिखो32(hp, bregs + BMAC_XIFCFG, BIGMAC_XCFG_MIIDISAB);
		अवरोध;
	पूर्ण
	अगर (happy_meal_tcvr_reset(hp, tregs))
		वापस;

	/* Latch PHY रेजिस्टरs as of now. */
	hp->sw_bmsr      = happy_meal_tcvr_पढ़ो(hp, tregs, MII_BMSR);
	hp->sw_advertise = happy_meal_tcvr_पढ़ो(hp, tregs, MII_ADVERTISE);

	/* Advertise everything we can support. */
	अगर (hp->sw_bmsr & BMSR_10HALF)
		hp->sw_advertise |= (ADVERTISE_10HALF);
	अन्यथा
		hp->sw_advertise &= ~(ADVERTISE_10HALF);

	अगर (hp->sw_bmsr & BMSR_10FULL)
		hp->sw_advertise |= (ADVERTISE_10FULL);
	अन्यथा
		hp->sw_advertise &= ~(ADVERTISE_10FULL);
	अगर (hp->sw_bmsr & BMSR_100HALF)
		hp->sw_advertise |= (ADVERTISE_100HALF);
	अन्यथा
		hp->sw_advertise &= ~(ADVERTISE_100HALF);
	अगर (hp->sw_bmsr & BMSR_100FULL)
		hp->sw_advertise |= (ADVERTISE_100FULL);
	अन्यथा
		hp->sw_advertise &= ~(ADVERTISE_100FULL);

	/* Update the PHY advertisement रेजिस्टर. */
	happy_meal_tcvr_ग_लिखो(hp, tregs, MII_ADVERTISE, hp->sw_advertise);
पूर्ण

/* Once status is latched (by happy_meal_पूर्णांकerrupt) it is cleared by
 * the hardware, so we cannot re-पढ़ो it and get a correct value.
 *
 * hp->happy_lock must be held
 */
अटल पूर्णांक happy_meal_is_not_so_happy(काष्ठा happy_meal *hp, u32 status)
अणु
	पूर्णांक reset = 0;

	/* Only prपूर्णांक messages क्रम non-counter related पूर्णांकerrupts. */
	अगर (status & (GREG_STAT_STSTERR | GREG_STAT_TFIFO_UND |
		      GREG_STAT_MAXPKTERR | GREG_STAT_RXERR |
		      GREG_STAT_RXPERR | GREG_STAT_RXTERR | GREG_STAT_EOPERR |
		      GREG_STAT_MIFIRQ | GREG_STAT_TXEACK | GREG_STAT_TXLERR |
		      GREG_STAT_TXPERR | GREG_STAT_TXTERR | GREG_STAT_SLVERR |
		      GREG_STAT_SLVPERR))
		prपूर्णांकk(KERN_ERR "%s: Error interrupt for happy meal, status = %08x\n",
		       hp->dev->name, status);

	अगर (status & GREG_STAT_RFIFOVF) अणु
		/* Receive FIFO overflow is harmless and the hardware will take
		   care of it, just some packets are lost. Who cares. */
		prपूर्णांकk(KERN_DEBUG "%s: Happy Meal receive FIFO overflow.\n", hp->dev->name);
	पूर्ण

	अगर (status & GREG_STAT_STSTERR) अणु
		/* BigMAC SQE link test failed. */
		prपूर्णांकk(KERN_ERR "%s: Happy Meal BigMAC SQE test failed.\n", hp->dev->name);
		reset = 1;
	पूर्ण

	अगर (status & GREG_STAT_TFIFO_UND) अणु
		/* Transmit FIFO underrun, again DMA error likely. */
		prपूर्णांकk(KERN_ERR "%s: Happy Meal transmitter FIFO underrun, DMA error.\n",
		       hp->dev->name);
		reset = 1;
	पूर्ण

	अगर (status & GREG_STAT_MAXPKTERR) अणु
		/* Driver error, tried to transmit something larger
		 * than ethernet max mtu.
		 */
		prपूर्णांकk(KERN_ERR "%s: Happy Meal MAX Packet size error.\n", hp->dev->name);
		reset = 1;
	पूर्ण

	अगर (status & GREG_STAT_NORXD) अणु
		/* This is harmless, it just means the प्रणाली is
		 * quite loaded and the incoming packet rate was
		 * faster than the पूर्णांकerrupt handler could keep up
		 * with.
		 */
		prपूर्णांकk(KERN_INFO "%s: Happy Meal out of receive "
		       "descriptors, packet dropped.\n",
		       hp->dev->name);
	पूर्ण

	अगर (status & (GREG_STAT_RXERR|GREG_STAT_RXPERR|GREG_STAT_RXTERR)) अणु
		/* All sorts of DMA receive errors. */
		prपूर्णांकk(KERN_ERR "%s: Happy Meal rx DMA errors [ ", hp->dev->name);
		अगर (status & GREG_STAT_RXERR)
			prपूर्णांकk("GenericError ");
		अगर (status & GREG_STAT_RXPERR)
			prपूर्णांकk("ParityError ");
		अगर (status & GREG_STAT_RXTERR)
			prपूर्णांकk("RxTagBotch ");
		prपूर्णांकk("]\n");
		reset = 1;
	पूर्ण

	अगर (status & GREG_STAT_EOPERR) अणु
		/* Driver bug, didn't set EOP bit in tx descriptor given
		 * to the happy meal.
		 */
		prपूर्णांकk(KERN_ERR "%s: EOP not set in happy meal transmit descriptor!\n",
		       hp->dev->name);
		reset = 1;
	पूर्ण

	अगर (status & GREG_STAT_MIFIRQ) अणु
		/* MIF संकेतled an पूर्णांकerrupt, were we polling it? */
		prपूर्णांकk(KERN_ERR "%s: Happy Meal MIF interrupt.\n", hp->dev->name);
	पूर्ण

	अगर (status &
	    (GREG_STAT_TXEACK|GREG_STAT_TXLERR|GREG_STAT_TXPERR|GREG_STAT_TXTERR)) अणु
		/* All sorts of transmit DMA errors. */
		prपूर्णांकk(KERN_ERR "%s: Happy Meal tx DMA errors [ ", hp->dev->name);
		अगर (status & GREG_STAT_TXEACK)
			prपूर्णांकk("GenericError ");
		अगर (status & GREG_STAT_TXLERR)
			prपूर्णांकk("LateError ");
		अगर (status & GREG_STAT_TXPERR)
			prपूर्णांकk("ParityError ");
		अगर (status & GREG_STAT_TXTERR)
			prपूर्णांकk("TagBotch ");
		prपूर्णांकk("]\n");
		reset = 1;
	पूर्ण

	अगर (status & (GREG_STAT_SLVERR|GREG_STAT_SLVPERR)) अणु
		/* Bus or parity error when cpu accessed happy meal रेजिस्टरs
		 * or it's internal FIFO's.  Should never see this.
		 */
		prपूर्णांकk(KERN_ERR "%s: Happy Meal register access SBUS slave (%s) error.\n",
		       hp->dev->name,
		       (status & GREG_STAT_SLVPERR) ? "parity" : "generic");
		reset = 1;
	पूर्ण

	अगर (reset) अणु
		prपूर्णांकk(KERN_NOTICE "%s: Resetting...\n", hp->dev->name);
		happy_meal_init(hp);
		वापस 1;
	पूर्ण
	वापस 0;
पूर्ण

/* hp->happy_lock must be held */
अटल व्योम happy_meal_mअगर_पूर्णांकerrupt(काष्ठा happy_meal *hp)
अणु
	व्योम __iomem *tregs = hp->tcvregs;

	prपूर्णांकk(KERN_INFO "%s: Link status change.\n", hp->dev->name);
	hp->sw_bmcr = happy_meal_tcvr_पढ़ो(hp, tregs, MII_BMCR);
	hp->sw_lpa = happy_meal_tcvr_पढ़ो(hp, tregs, MII_LPA);

	/* Use the fastest transmission protocol possible. */
	अगर (hp->sw_lpa & LPA_100FULL) अणु
		prपूर्णांकk(KERN_INFO "%s: Switching to 100Mbps at full duplex.", hp->dev->name);
		hp->sw_bmcr |= (BMCR_FULLDPLX | BMCR_SPEED100);
	पूर्ण अन्यथा अगर (hp->sw_lpa & LPA_100HALF) अणु
		prपूर्णांकk(KERN_INFO "%s: Switching to 100MBps at half duplex.", hp->dev->name);
		hp->sw_bmcr |= BMCR_SPEED100;
	पूर्ण अन्यथा अगर (hp->sw_lpa & LPA_10FULL) अणु
		prपूर्णांकk(KERN_INFO "%s: Switching to 10MBps at full duplex.", hp->dev->name);
		hp->sw_bmcr |= BMCR_FULLDPLX;
	पूर्ण अन्यथा अणु
		prपूर्णांकk(KERN_INFO "%s: Using 10Mbps at half duplex.", hp->dev->name);
	पूर्ण
	happy_meal_tcvr_ग_लिखो(hp, tregs, MII_BMCR, hp->sw_bmcr);

	/* Finally stop polling and shut up the MIF. */
	happy_meal_poll_stop(hp, tregs);
पूर्ण

#अगर_घोषित TXDEBUG
#घोषणा TXD(x) prपूर्णांकk x
#अन्यथा
#घोषणा TXD(x)
#पूर्ण_अगर

/* hp->happy_lock must be held */
अटल व्योम happy_meal_tx(काष्ठा happy_meal *hp)
अणु
	काष्ठा happy_meal_txd *txbase = &hp->happy_block->happy_meal_txd[0];
	काष्ठा happy_meal_txd *this;
	काष्ठा net_device *dev = hp->dev;
	पूर्णांक elem;

	elem = hp->tx_old;
	TXD(("TX<"));
	जबतक (elem != hp->tx_new) अणु
		काष्ठा sk_buff *skb;
		u32 flags, dma_addr, dma_len;
		पूर्णांक frag;

		TXD(("[%d]", elem));
		this = &txbase[elem];
		flags = hme_पढ़ो_desc32(hp, &this->tx_flags);
		अगर (flags & TXFLAG_OWN)
			अवरोध;
		skb = hp->tx_skbs[elem];
		अगर (skb_shinfo(skb)->nr_frags) अणु
			पूर्णांक last;

			last = elem + skb_shinfo(skb)->nr_frags;
			last &= (TX_RING_SIZE - 1);
			flags = hme_पढ़ो_desc32(hp, &txbase[last].tx_flags);
			अगर (flags & TXFLAG_OWN)
				अवरोध;
		पूर्ण
		hp->tx_skbs[elem] = शून्य;
		dev->stats.tx_bytes += skb->len;

		क्रम (frag = 0; frag <= skb_shinfo(skb)->nr_frags; frag++) अणु
			dma_addr = hme_पढ़ो_desc32(hp, &this->tx_addr);
			dma_len = hme_पढ़ो_desc32(hp, &this->tx_flags);

			dma_len &= TXFLAG_SIZE;
			अगर (!frag)
				dma_unmap_single(hp->dma_dev, dma_addr, dma_len, DMA_TO_DEVICE);
			अन्यथा
				dma_unmap_page(hp->dma_dev, dma_addr, dma_len, DMA_TO_DEVICE);

			elem = NEXT_TX(elem);
			this = &txbase[elem];
		पूर्ण

		dev_consume_skb_irq(skb);
		dev->stats.tx_packets++;
	पूर्ण
	hp->tx_old = elem;
	TXD((">"));

	अगर (netअगर_queue_stopped(dev) &&
	    TX_BUFFS_AVAIL(hp) > (MAX_SKB_FRAGS + 1))
		netअगर_wake_queue(dev);
पूर्ण

#अगर_घोषित RXDEBUG
#घोषणा RXD(x) prपूर्णांकk x
#अन्यथा
#घोषणा RXD(x)
#पूर्ण_अगर

/* Originally I used to handle the allocation failure by just giving back just
 * that one ring buffer to the happy meal.  Problem is that usually when that
 * condition is triggered, the happy meal expects you to करो something reasonable
 * with all of the packets it has DMA'd in.  So now I just drop the entire
 * ring when we cannot get a new skb and give them all back to the happy meal,
 * maybe things will be "happier" now.
 *
 * hp->happy_lock must be held
 */
अटल व्योम happy_meal_rx(काष्ठा happy_meal *hp, काष्ठा net_device *dev)
अणु
	काष्ठा happy_meal_rxd *rxbase = &hp->happy_block->happy_meal_rxd[0];
	काष्ठा happy_meal_rxd *this;
	पूर्णांक elem = hp->rx_new, drops = 0;
	u32 flags;

	RXD(("RX<"));
	this = &rxbase[elem];
	जबतक (!((flags = hme_पढ़ो_desc32(hp, &this->rx_flags)) & RXFLAG_OWN)) अणु
		काष्ठा sk_buff *skb;
		पूर्णांक len = flags >> 16;
		u16 csum = flags & RXFLAG_CSUM;
		u32 dma_addr = hme_पढ़ो_desc32(hp, &this->rx_addr);

		RXD(("[%d ", elem));

		/* Check क्रम errors. */
		अगर ((len < ETH_ZLEN) || (flags & RXFLAG_OVERFLOW)) अणु
			RXD(("ERR(%08x)]", flags));
			dev->stats.rx_errors++;
			अगर (len < ETH_ZLEN)
				dev->stats.rx_length_errors++;
			अगर (len & (RXFLAG_OVERFLOW >> 16)) अणु
				dev->stats.rx_over_errors++;
				dev->stats.rx_fअगरo_errors++;
			पूर्ण

			/* Return it to the Happy meal. */
	drop_it:
			dev->stats.rx_dropped++;
			hme_ग_लिखो_rxd(hp, this,
				      (RXFLAG_OWN|((RX_BUF_ALLOC_SIZE-RX_OFFSET)<<16)),
				      dma_addr);
			जाओ next;
		पूर्ण
		skb = hp->rx_skbs[elem];
		अगर (len > RX_COPY_THRESHOLD) अणु
			काष्ठा sk_buff *new_skb;
			u32 mapping;

			/* Now refill the entry, अगर we can. */
			new_skb = happy_meal_alloc_skb(RX_BUF_ALLOC_SIZE, GFP_ATOMIC);
			अगर (new_skb == शून्य) अणु
				drops++;
				जाओ drop_it;
			पूर्ण
			skb_put(new_skb, (ETH_FRAME_LEN + RX_OFFSET + 4));
			mapping = dma_map_single(hp->dma_dev, new_skb->data,
						 RX_BUF_ALLOC_SIZE,
						 DMA_FROM_DEVICE);
			अगर (unlikely(dma_mapping_error(hp->dma_dev, mapping))) अणु
				dev_kमुक्त_skb_any(new_skb);
				drops++;
				जाओ drop_it;
			पूर्ण

			dma_unmap_single(hp->dma_dev, dma_addr, RX_BUF_ALLOC_SIZE, DMA_FROM_DEVICE);
			hp->rx_skbs[elem] = new_skb;
			hme_ग_लिखो_rxd(hp, this,
				      (RXFLAG_OWN|((RX_BUF_ALLOC_SIZE-RX_OFFSET)<<16)),
				      mapping);
			skb_reserve(new_skb, RX_OFFSET);

			/* Trim the original skb क्रम the netअगर. */
			skb_trim(skb, len);
		पूर्ण अन्यथा अणु
			काष्ठा sk_buff *copy_skb = netdev_alloc_skb(dev, len + 2);

			अगर (copy_skb == शून्य) अणु
				drops++;
				जाओ drop_it;
			पूर्ण

			skb_reserve(copy_skb, 2);
			skb_put(copy_skb, len);
			dma_sync_single_क्रम_cpu(hp->dma_dev, dma_addr, len, DMA_FROM_DEVICE);
			skb_copy_from_linear_data(skb, copy_skb->data, len);
			dma_sync_single_क्रम_device(hp->dma_dev, dma_addr, len, DMA_FROM_DEVICE);
			/* Reuse original ring buffer. */
			hme_ग_लिखो_rxd(hp, this,
				      (RXFLAG_OWN|((RX_BUF_ALLOC_SIZE-RX_OFFSET)<<16)),
				      dma_addr);

			skb = copy_skb;
		पूर्ण

		/* This card is _fucking_ hot... */
		skb->csum = csum_unfold(~(__क्रमce __sum16)htons(csum));
		skb->ip_summed = CHECKSUM_COMPLETE;

		RXD(("len=%d csum=%4x]", len, csum));
		skb->protocol = eth_type_trans(skb, dev);
		netअगर_rx(skb);

		dev->stats.rx_packets++;
		dev->stats.rx_bytes += len;
	next:
		elem = NEXT_RX(elem);
		this = &rxbase[elem];
	पूर्ण
	hp->rx_new = elem;
	अगर (drops)
		prपूर्णांकk(KERN_INFO "%s: Memory squeeze, deferring packet.\n", hp->dev->name);
	RXD((">"));
पूर्ण

अटल irqवापस_t happy_meal_पूर्णांकerrupt(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा net_device *dev = dev_id;
	काष्ठा happy_meal *hp  = netdev_priv(dev);
	u32 happy_status       = hme_पढ़ो32(hp, hp->gregs + GREG_STAT);

	HMD(("happy_meal_interrupt: status=%08x ", happy_status));

	spin_lock(&hp->happy_lock);

	अगर (happy_status & GREG_STAT_ERRORS) अणु
		HMD(("ERRORS "));
		अगर (happy_meal_is_not_so_happy(hp, /* un- */ happy_status))
			जाओ out;
	पूर्ण

	अगर (happy_status & GREG_STAT_MIFIRQ) अणु
		HMD(("MIFIRQ "));
		happy_meal_mअगर_पूर्णांकerrupt(hp);
	पूर्ण

	अगर (happy_status & GREG_STAT_TXALL) अणु
		HMD(("TXALL "));
		happy_meal_tx(hp);
	पूर्ण

	अगर (happy_status & GREG_STAT_RXTOHOST) अणु
		HMD(("RXTOHOST "));
		happy_meal_rx(hp, dev);
	पूर्ण

	HMD(("done\n"));
out:
	spin_unlock(&hp->happy_lock);

	वापस IRQ_HANDLED;
पूर्ण

#अगर_घोषित CONFIG_SBUS
अटल irqवापस_t quattro_sbus_पूर्णांकerrupt(पूर्णांक irq, व्योम *cookie)
अणु
	काष्ठा quattro *qp = (काष्ठा quattro *) cookie;
	पूर्णांक i;

	क्रम (i = 0; i < 4; i++) अणु
		काष्ठा net_device *dev = qp->happy_meals[i];
		काष्ठा happy_meal *hp  = netdev_priv(dev);
		u32 happy_status       = hme_पढ़ो32(hp, hp->gregs + GREG_STAT);

		HMD(("quattro_interrupt: status=%08x ", happy_status));

		अगर (!(happy_status & (GREG_STAT_ERRORS |
				      GREG_STAT_MIFIRQ |
				      GREG_STAT_TXALL |
				      GREG_STAT_RXTOHOST)))
			जारी;

		spin_lock(&hp->happy_lock);

		अगर (happy_status & GREG_STAT_ERRORS) अणु
			HMD(("ERRORS "));
			अगर (happy_meal_is_not_so_happy(hp, happy_status))
				जाओ next;
		पूर्ण

		अगर (happy_status & GREG_STAT_MIFIRQ) अणु
			HMD(("MIFIRQ "));
			happy_meal_mअगर_पूर्णांकerrupt(hp);
		पूर्ण

		अगर (happy_status & GREG_STAT_TXALL) अणु
			HMD(("TXALL "));
			happy_meal_tx(hp);
		पूर्ण

		अगर (happy_status & GREG_STAT_RXTOHOST) अणु
			HMD(("RXTOHOST "));
			happy_meal_rx(hp, dev);
		पूर्ण

	next:
		spin_unlock(&hp->happy_lock);
	पूर्ण
	HMD(("done\n"));

	वापस IRQ_HANDLED;
पूर्ण
#पूर्ण_अगर

अटल पूर्णांक happy_meal_खोलो(काष्ठा net_device *dev)
अणु
	काष्ठा happy_meal *hp = netdev_priv(dev);
	पूर्णांक res;

	HMD(("happy_meal_open: "));

	/* On SBUS Quattro QFE cards, all hme पूर्णांकerrupts are concentrated
	 * पूर्णांकo a single source which we रेजिस्टर handling at probe समय.
	 */
	अगर ((hp->happy_flags & (HFLAG_QUATTRO|HFLAG_PCI)) != HFLAG_QUATTRO) अणु
		res = request_irq(hp->irq, happy_meal_पूर्णांकerrupt, IRQF_SHARED,
				  dev->name, dev);
		अगर (res) अणु
			HMD(("EAGAIN\n"));
			prपूर्णांकk(KERN_ERR "happy_meal(SBUS): Can't order irq %d to go.\n",
			       hp->irq);

			वापस -EAGAIN;
		पूर्ण
	पूर्ण

	HMD(("to happy_meal_init\n"));

	spin_lock_irq(&hp->happy_lock);
	res = happy_meal_init(hp);
	spin_unlock_irq(&hp->happy_lock);

	अगर (res && ((hp->happy_flags & (HFLAG_QUATTRO|HFLAG_PCI)) != HFLAG_QUATTRO))
		मुक्त_irq(hp->irq, dev);
	वापस res;
पूर्ण

अटल पूर्णांक happy_meal_बंद(काष्ठा net_device *dev)
अणु
	काष्ठा happy_meal *hp = netdev_priv(dev);

	spin_lock_irq(&hp->happy_lock);
	happy_meal_stop(hp, hp->gregs);
	happy_meal_clean_rings(hp);

	/* If स्वतः-negotiation समयr is running, समाप्त it. */
	del_समयr(&hp->happy_समयr);

	spin_unlock_irq(&hp->happy_lock);

	/* On Quattro QFE cards, all hme पूर्णांकerrupts are concentrated
	 * पूर्णांकo a single source which we रेजिस्टर handling at probe
	 * समय and never unरेजिस्टर.
	 */
	अगर ((hp->happy_flags & (HFLAG_QUATTRO|HFLAG_PCI)) != HFLAG_QUATTRO)
		मुक्त_irq(hp->irq, dev);

	वापस 0;
पूर्ण

#अगर_घोषित SXDEBUG
#घोषणा SXD(x) prपूर्णांकk x
#अन्यथा
#घोषणा SXD(x)
#पूर्ण_अगर

अटल व्योम happy_meal_tx_समयout(काष्ठा net_device *dev, अचिन्हित पूर्णांक txqueue)
अणु
	काष्ठा happy_meal *hp = netdev_priv(dev);

	prपूर्णांकk (KERN_ERR "%s: transmit timed out, resetting\n", dev->name);
	tx_dump_log();
	prपूर्णांकk (KERN_ERR "%s: Happy Status %08x TX[%08x:%08x]\n", dev->name,
		hme_पढ़ो32(hp, hp->gregs + GREG_STAT),
		hme_पढ़ो32(hp, hp->etxregs + ETX_CFG),
		hme_पढ़ो32(hp, hp->bigmacregs + BMAC_TXCFG));

	spin_lock_irq(&hp->happy_lock);
	happy_meal_init(hp);
	spin_unlock_irq(&hp->happy_lock);

	netअगर_wake_queue(dev);
पूर्ण

अटल व्योम unmap_partial_tx_skb(काष्ठा happy_meal *hp, u32 first_mapping,
				 u32 first_len, u32 first_entry, u32 entry)
अणु
	काष्ठा happy_meal_txd *txbase = &hp->happy_block->happy_meal_txd[0];

	dma_unmap_single(hp->dma_dev, first_mapping, first_len, DMA_TO_DEVICE);

	first_entry = NEXT_TX(first_entry);
	जबतक (first_entry != entry) अणु
		काष्ठा happy_meal_txd *this = &txbase[first_entry];
		u32 addr, len;

		addr = hme_पढ़ो_desc32(hp, &this->tx_addr);
		len = hme_पढ़ो_desc32(hp, &this->tx_flags);
		len &= TXFLAG_SIZE;
		dma_unmap_page(hp->dma_dev, addr, len, DMA_TO_DEVICE);
	पूर्ण
पूर्ण

अटल netdev_tx_t happy_meal_start_xmit(काष्ठा sk_buff *skb,
					 काष्ठा net_device *dev)
अणु
	काष्ठा happy_meal *hp = netdev_priv(dev);
 	पूर्णांक entry;
 	u32 tx_flags;

	tx_flags = TXFLAG_OWN;
	अगर (skb->ip_summed == CHECKSUM_PARTIAL) अणु
		स्थिर u32 csum_start_off = skb_checksum_start_offset(skb);
		स्थिर u32 csum_stuff_off = csum_start_off + skb->csum_offset;

		tx_flags = (TXFLAG_OWN | TXFLAG_CSENABLE |
			    ((csum_start_off << 14) & TXFLAG_CSBUFBEGIN) |
			    ((csum_stuff_off << 20) & TXFLAG_CSLOCATION));
	पूर्ण

	spin_lock_irq(&hp->happy_lock);

 	अगर (TX_BUFFS_AVAIL(hp) <= (skb_shinfo(skb)->nr_frags + 1)) अणु
		netअगर_stop_queue(dev);
		spin_unlock_irq(&hp->happy_lock);
		prपूर्णांकk(KERN_ERR "%s: BUG! Tx Ring full when queue awake!\n",
		       dev->name);
		वापस NETDEV_TX_BUSY;
	पूर्ण

	entry = hp->tx_new;
	SXD(("SX<l[%d]e[%d]>", len, entry));
	hp->tx_skbs[entry] = skb;

	अगर (skb_shinfo(skb)->nr_frags == 0) अणु
		u32 mapping, len;

		len = skb->len;
		mapping = dma_map_single(hp->dma_dev, skb->data, len, DMA_TO_DEVICE);
		अगर (unlikely(dma_mapping_error(hp->dma_dev, mapping)))
			जाओ out_dma_error;
		tx_flags |= (TXFLAG_SOP | TXFLAG_EOP);
		hme_ग_लिखो_txd(hp, &hp->happy_block->happy_meal_txd[entry],
			      (tx_flags | (len & TXFLAG_SIZE)),
			      mapping);
		entry = NEXT_TX(entry);
	पूर्ण अन्यथा अणु
		u32 first_len, first_mapping;
		पूर्णांक frag, first_entry = entry;

		/* We must give this initial chunk to the device last.
		 * Otherwise we could race with the device.
		 */
		first_len = skb_headlen(skb);
		first_mapping = dma_map_single(hp->dma_dev, skb->data, first_len,
					       DMA_TO_DEVICE);
		अगर (unlikely(dma_mapping_error(hp->dma_dev, first_mapping)))
			जाओ out_dma_error;
		entry = NEXT_TX(entry);

		क्रम (frag = 0; frag < skb_shinfo(skb)->nr_frags; frag++) अणु
			स्थिर skb_frag_t *this_frag = &skb_shinfo(skb)->frags[frag];
			u32 len, mapping, this_txflags;

			len = skb_frag_size(this_frag);
			mapping = skb_frag_dma_map(hp->dma_dev, this_frag,
						   0, len, DMA_TO_DEVICE);
			अगर (unlikely(dma_mapping_error(hp->dma_dev, mapping))) अणु
				unmap_partial_tx_skb(hp, first_mapping, first_len,
						     first_entry, entry);
				जाओ out_dma_error;
			पूर्ण
			this_txflags = tx_flags;
			अगर (frag == skb_shinfo(skb)->nr_frags - 1)
				this_txflags |= TXFLAG_EOP;
			hme_ग_लिखो_txd(hp, &hp->happy_block->happy_meal_txd[entry],
				      (this_txflags | (len & TXFLAG_SIZE)),
				      mapping);
			entry = NEXT_TX(entry);
		पूर्ण
		hme_ग_लिखो_txd(hp, &hp->happy_block->happy_meal_txd[first_entry],
			      (tx_flags | TXFLAG_SOP | (first_len & TXFLAG_SIZE)),
			      first_mapping);
	पूर्ण

	hp->tx_new = entry;

	अगर (TX_BUFFS_AVAIL(hp) <= (MAX_SKB_FRAGS + 1))
		netअगर_stop_queue(dev);

	/* Get it going. */
	hme_ग_लिखो32(hp, hp->etxregs + ETX_PENDING, ETX_TP_DMAWAKEUP);

	spin_unlock_irq(&hp->happy_lock);

	tx_add_log(hp, TXLOG_ACTION_TXMIT, 0);
	वापस NETDEV_TX_OK;

out_dma_error:
	hp->tx_skbs[hp->tx_new] = शून्य;
	spin_unlock_irq(&hp->happy_lock);

	dev_kमुक्त_skb_any(skb);
	dev->stats.tx_dropped++;
	वापस NETDEV_TX_OK;
पूर्ण

अटल काष्ठा net_device_stats *happy_meal_get_stats(काष्ठा net_device *dev)
अणु
	काष्ठा happy_meal *hp = netdev_priv(dev);

	spin_lock_irq(&hp->happy_lock);
	happy_meal_get_counters(hp, hp->bigmacregs);
	spin_unlock_irq(&hp->happy_lock);

	वापस &dev->stats;
पूर्ण

अटल व्योम happy_meal_set_multicast(काष्ठा net_device *dev)
अणु
	काष्ठा happy_meal *hp = netdev_priv(dev);
	व्योम __iomem *bregs = hp->bigmacregs;
	काष्ठा netdev_hw_addr *ha;
	u32 crc;

	spin_lock_irq(&hp->happy_lock);

	अगर ((dev->flags & IFF_ALLMULTI) || (netdev_mc_count(dev) > 64)) अणु
		hme_ग_लिखो32(hp, bregs + BMAC_HTABLE0, 0xffff);
		hme_ग_लिखो32(hp, bregs + BMAC_HTABLE1, 0xffff);
		hme_ग_लिखो32(hp, bregs + BMAC_HTABLE2, 0xffff);
		hme_ग_लिखो32(hp, bregs + BMAC_HTABLE3, 0xffff);
	पूर्ण अन्यथा अगर (dev->flags & IFF_PROMISC) अणु
		hme_ग_लिखो32(hp, bregs + BMAC_RXCFG,
			    hme_पढ़ो32(hp, bregs + BMAC_RXCFG) | BIGMAC_RXCFG_PMISC);
	पूर्ण अन्यथा अणु
		u16 hash_table[4];

		स_रखो(hash_table, 0, माप(hash_table));
		netdev_क्रम_each_mc_addr(ha, dev) अणु
			crc = ether_crc_le(6, ha->addr);
			crc >>= 26;
			hash_table[crc >> 4] |= 1 << (crc & 0xf);
		पूर्ण
		hme_ग_लिखो32(hp, bregs + BMAC_HTABLE0, hash_table[0]);
		hme_ग_लिखो32(hp, bregs + BMAC_HTABLE1, hash_table[1]);
		hme_ग_लिखो32(hp, bregs + BMAC_HTABLE2, hash_table[2]);
		hme_ग_लिखो32(hp, bregs + BMAC_HTABLE3, hash_table[3]);
	पूर्ण

	spin_unlock_irq(&hp->happy_lock);
पूर्ण

/* Ethtool support... */
अटल पूर्णांक hme_get_link_ksettings(काष्ठा net_device *dev,
				  काष्ठा ethtool_link_ksettings *cmd)
अणु
	काष्ठा happy_meal *hp = netdev_priv(dev);
	u32 speed;
	u32 supported;

	supported =
		(SUPPORTED_10baseT_Half | SUPPORTED_10baseT_Full |
		 SUPPORTED_100baseT_Half | SUPPORTED_100baseT_Full |
		 SUPPORTED_Autoneg | SUPPORTED_TP | SUPPORTED_MII);

	/* XXX hardcoded stuff क्रम now */
	cmd->base.port = PORT_TP; /* XXX no MII support */
	cmd->base.phy_address = 0; /* XXX fixed PHYAD */

	/* Record PHY settings. */
	spin_lock_irq(&hp->happy_lock);
	hp->sw_bmcr = happy_meal_tcvr_पढ़ो(hp, hp->tcvregs, MII_BMCR);
	hp->sw_lpa = happy_meal_tcvr_पढ़ो(hp, hp->tcvregs, MII_LPA);
	spin_unlock_irq(&hp->happy_lock);

	अगर (hp->sw_bmcr & BMCR_ANENABLE) अणु
		cmd->base.स्वतःneg = AUTONEG_ENABLE;
		speed = ((hp->sw_lpa & (LPA_100HALF | LPA_100FULL)) ?
			 SPEED_100 : SPEED_10);
		अगर (speed == SPEED_100)
			cmd->base.duplex =
				(hp->sw_lpa & (LPA_100FULL)) ?
				DUPLEX_FULL : DUPLEX_HALF;
		अन्यथा
			cmd->base.duplex =
				(hp->sw_lpa & (LPA_10FULL)) ?
				DUPLEX_FULL : DUPLEX_HALF;
	पूर्ण अन्यथा अणु
		cmd->base.स्वतःneg = AUTONEG_DISABLE;
		speed = (hp->sw_bmcr & BMCR_SPEED100) ? SPEED_100 : SPEED_10;
		cmd->base.duplex =
			(hp->sw_bmcr & BMCR_FULLDPLX) ?
			DUPLEX_FULL : DUPLEX_HALF;
	पूर्ण
	cmd->base.speed = speed;
	ethtool_convert_legacy_u32_to_link_mode(cmd->link_modes.supported,
						supported);

	वापस 0;
पूर्ण

अटल पूर्णांक hme_set_link_ksettings(काष्ठा net_device *dev,
				  स्थिर काष्ठा ethtool_link_ksettings *cmd)
अणु
	काष्ठा happy_meal *hp = netdev_priv(dev);

	/* Verअगरy the settings we care about. */
	अगर (cmd->base.स्वतःneg != AUTONEG_ENABLE &&
	    cmd->base.स्वतःneg != AUTONEG_DISABLE)
		वापस -EINVAL;
	अगर (cmd->base.स्वतःneg == AUTONEG_DISABLE &&
	    ((cmd->base.speed != SPEED_100 &&
	      cmd->base.speed != SPEED_10) ||
	     (cmd->base.duplex != DUPLEX_HALF &&
	      cmd->base.duplex != DUPLEX_FULL)))
		वापस -EINVAL;

	/* Ok, करो it to it. */
	spin_lock_irq(&hp->happy_lock);
	del_समयr(&hp->happy_समयr);
	happy_meal_begin_स्वतः_negotiation(hp, hp->tcvregs, cmd);
	spin_unlock_irq(&hp->happy_lock);

	वापस 0;
पूर्ण

अटल व्योम hme_get_drvinfo(काष्ठा net_device *dev, काष्ठा ethtool_drvinfo *info)
अणु
	काष्ठा happy_meal *hp = netdev_priv(dev);

	strlcpy(info->driver, "sunhme", माप(info->driver));
	strlcpy(info->version, "2.02", माप(info->version));
	अगर (hp->happy_flags & HFLAG_PCI) अणु
		काष्ठा pci_dev *pdev = hp->happy_dev;
		strlcpy(info->bus_info, pci_name(pdev), माप(info->bus_info));
	पूर्ण
#अगर_घोषित CONFIG_SBUS
	अन्यथा अणु
		स्थिर काष्ठा linux_prom_रेजिस्टरs *regs;
		काष्ठा platक्रमm_device *op = hp->happy_dev;
		regs = of_get_property(op->dev.of_node, "regs", शून्य);
		अगर (regs)
			snम_लिखो(info->bus_info, माप(info->bus_info),
				"SBUS:%d",
				regs->which_io);
	पूर्ण
#पूर्ण_अगर
पूर्ण

अटल u32 hme_get_link(काष्ठा net_device *dev)
अणु
	काष्ठा happy_meal *hp = netdev_priv(dev);

	spin_lock_irq(&hp->happy_lock);
	hp->sw_bmcr = happy_meal_tcvr_पढ़ो(hp, hp->tcvregs, MII_BMCR);
	spin_unlock_irq(&hp->happy_lock);

	वापस hp->sw_bmsr & BMSR_LSTATUS;
पूर्ण

अटल स्थिर काष्ठा ethtool_ops hme_ethtool_ops = अणु
	.get_drvinfo		= hme_get_drvinfo,
	.get_link		= hme_get_link,
	.get_link_ksettings	= hme_get_link_ksettings,
	.set_link_ksettings	= hme_set_link_ksettings,
पूर्ण;

अटल पूर्णांक hme_version_prपूर्णांकed;

#अगर_घोषित CONFIG_SBUS
/* Given a happy meal sbus device, find it's quattro parent.
 * If none exist, allocate and वापस a new one.
 *
 * Return शून्य on failure.
 */
अटल काष्ठा quattro *quattro_sbus_find(काष्ठा platक्रमm_device *child)
अणु
	काष्ठा device *parent = child->dev.parent;
	काष्ठा platक्रमm_device *op;
	काष्ठा quattro *qp;

	op = to_platक्रमm_device(parent);
	qp = platक्रमm_get_drvdata(op);
	अगर (qp)
		वापस qp;

	qp = kदो_स्मृति(माप(काष्ठा quattro), GFP_KERNEL);
	अगर (qp != शून्य) अणु
		पूर्णांक i;

		क्रम (i = 0; i < 4; i++)
			qp->happy_meals[i] = शून्य;

		qp->quattro_dev = child;
		qp->next = qfe_sbus_list;
		qfe_sbus_list = qp;

		platक्रमm_set_drvdata(op, qp);
	पूर्ण
	वापस qp;
पूर्ण

/* After all quattro cards have been probed, we call these functions
 * to रेजिस्टर the IRQ handlers क्रम the cards that have been
 * successfully probed and skip the cards that failed to initialize
 */
अटल पूर्णांक __init quattro_sbus_रेजिस्टर_irqs(व्योम)
अणु
	काष्ठा quattro *qp;

	क्रम (qp = qfe_sbus_list; qp != शून्य; qp = qp->next) अणु
		काष्ठा platक्रमm_device *op = qp->quattro_dev;
		पूर्णांक err, qfe_slot, skip = 0;

		क्रम (qfe_slot = 0; qfe_slot < 4; qfe_slot++) अणु
			अगर (!qp->happy_meals[qfe_slot])
				skip = 1;
		पूर्ण
		अगर (skip)
			जारी;

		err = request_irq(op->archdata.irqs[0],
				  quattro_sbus_पूर्णांकerrupt,
				  IRQF_SHARED, "Quattro",
				  qp);
		अगर (err != 0) अणु
			prपूर्णांकk(KERN_ERR "Quattro HME: IRQ registration "
			       "error %d.\n", err);
			वापस err;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम quattro_sbus_मुक्त_irqs(व्योम)
अणु
	काष्ठा quattro *qp;

	क्रम (qp = qfe_sbus_list; qp != शून्य; qp = qp->next) अणु
		काष्ठा platक्रमm_device *op = qp->quattro_dev;
		पूर्णांक qfe_slot, skip = 0;

		क्रम (qfe_slot = 0; qfe_slot < 4; qfe_slot++) अणु
			अगर (!qp->happy_meals[qfe_slot])
				skip = 1;
		पूर्ण
		अगर (skip)
			जारी;

		मुक्त_irq(op->archdata.irqs[0], qp);
	पूर्ण
पूर्ण
#पूर्ण_अगर /* CONFIG_SBUS */

#अगर_घोषित CONFIG_PCI
अटल काष्ठा quattro *quattro_pci_find(काष्ठा pci_dev *pdev)
अणु
	काष्ठा pci_dev *bdev = pdev->bus->self;
	काष्ठा quattro *qp;

	अगर (!bdev) वापस शून्य;
	क्रम (qp = qfe_pci_list; qp != शून्य; qp = qp->next) अणु
		काष्ठा pci_dev *qpdev = qp->quattro_dev;

		अगर (qpdev == bdev)
			वापस qp;
	पूर्ण
	qp = kदो_स्मृति(माप(काष्ठा quattro), GFP_KERNEL);
	अगर (qp != शून्य) अणु
		पूर्णांक i;

		क्रम (i = 0; i < 4; i++)
			qp->happy_meals[i] = शून्य;

		qp->quattro_dev = bdev;
		qp->next = qfe_pci_list;
		qfe_pci_list = qp;

		/* No range tricks necessary on PCI. */
		qp->nranges = 0;
	पूर्ण
	वापस qp;
पूर्ण
#पूर्ण_अगर /* CONFIG_PCI */

अटल स्थिर काष्ठा net_device_ops hme_netdev_ops = अणु
	.nकरो_खोलो		= happy_meal_खोलो,
	.nकरो_stop		= happy_meal_बंद,
	.nकरो_start_xmit		= happy_meal_start_xmit,
	.nकरो_tx_समयout		= happy_meal_tx_समयout,
	.nकरो_get_stats		= happy_meal_get_stats,
	.nकरो_set_rx_mode	= happy_meal_set_multicast,
	.nकरो_set_mac_address 	= eth_mac_addr,
	.nकरो_validate_addr	= eth_validate_addr,
पूर्ण;

#अगर_घोषित CONFIG_SBUS
अटल पूर्णांक happy_meal_sbus_probe_one(काष्ठा platक्रमm_device *op, पूर्णांक is_qfe)
अणु
	काष्ठा device_node *dp = op->dev.of_node, *sbus_dp;
	काष्ठा quattro *qp = शून्य;
	काष्ठा happy_meal *hp;
	काष्ठा net_device *dev;
	पूर्णांक i, qfe_slot = -1;
	पूर्णांक err = -ENODEV;

	sbus_dp = op->dev.parent->of_node;

	/* We can match PCI devices too, करो not accept those here. */
	अगर (!of_node_name_eq(sbus_dp, "sbus") && !of_node_name_eq(sbus_dp, "sbi"))
		वापस err;

	अगर (is_qfe) अणु
		qp = quattro_sbus_find(op);
		अगर (qp == शून्य)
			जाओ err_out;
		क्रम (qfe_slot = 0; qfe_slot < 4; qfe_slot++)
			अगर (qp->happy_meals[qfe_slot] == शून्य)
				अवरोध;
		अगर (qfe_slot == 4)
			जाओ err_out;
	पूर्ण

	err = -ENOMEM;
	dev = alloc_etherdev(माप(काष्ठा happy_meal));
	अगर (!dev)
		जाओ err_out;
	SET_NETDEV_DEV(dev, &op->dev);

	अगर (hme_version_prपूर्णांकed++ == 0)
		prपूर्णांकk(KERN_INFO "%s", version);

	/* If user did not specअगरy a MAC address specअगरically, use
	 * the Quattro local-mac-address property...
	 */
	क्रम (i = 0; i < 6; i++) अणु
		अगर (macaddr[i] != 0)
			अवरोध;
	पूर्ण
	अगर (i < 6) अणु /* a mac address was given */
		क्रम (i = 0; i < 6; i++)
			dev->dev_addr[i] = macaddr[i];
		macaddr[5]++;
	पूर्ण अन्यथा अणु
		स्थिर अचिन्हित अक्षर *addr;
		पूर्णांक len;

		addr = of_get_property(dp, "local-mac-address", &len);

		अगर (qfe_slot != -1 && addr && len == ETH_ALEN)
			स_नकल(dev->dev_addr, addr, ETH_ALEN);
		अन्यथा
			स_नकल(dev->dev_addr, idprom->id_ethaddr, ETH_ALEN);
	पूर्ण

	hp = netdev_priv(dev);

	hp->happy_dev = op;
	hp->dma_dev = &op->dev;

	spin_lock_init(&hp->happy_lock);

	err = -ENODEV;
	अगर (qp != शून्य) अणु
		hp->qfe_parent = qp;
		hp->qfe_ent = qfe_slot;
		qp->happy_meals[qfe_slot] = dev;
	पूर्ण

	hp->gregs = of_ioremap(&op->resource[0], 0,
			       GREG_REG_SIZE, "HME Global Regs");
	अगर (!hp->gregs) अणु
		prपूर्णांकk(KERN_ERR "happymeal: Cannot map global registers.\n");
		जाओ err_out_मुक्त_netdev;
	पूर्ण

	hp->etxregs = of_ioremap(&op->resource[1], 0,
				 ETX_REG_SIZE, "HME TX Regs");
	अगर (!hp->etxregs) अणु
		prपूर्णांकk(KERN_ERR "happymeal: Cannot map MAC TX registers.\n");
		जाओ err_out_iounmap;
	पूर्ण

	hp->erxregs = of_ioremap(&op->resource[2], 0,
				 ERX_REG_SIZE, "HME RX Regs");
	अगर (!hp->erxregs) अणु
		prपूर्णांकk(KERN_ERR "happymeal: Cannot map MAC RX registers.\n");
		जाओ err_out_iounmap;
	पूर्ण

	hp->bigmacregs = of_ioremap(&op->resource[3], 0,
				    BMAC_REG_SIZE, "HME BIGMAC Regs");
	अगर (!hp->bigmacregs) अणु
		prपूर्णांकk(KERN_ERR "happymeal: Cannot map BIGMAC registers.\n");
		जाओ err_out_iounmap;
	पूर्ण

	hp->tcvregs = of_ioremap(&op->resource[4], 0,
				 TCVR_REG_SIZE, "HME Tranceiver Regs");
	अगर (!hp->tcvregs) अणु
		prपूर्णांकk(KERN_ERR "happymeal: Cannot map TCVR registers.\n");
		जाओ err_out_iounmap;
	पूर्ण

	hp->hm_revision = of_getपूर्णांकprop_शेष(dp, "hm-rev", 0xff);
	अगर (hp->hm_revision == 0xff)
		hp->hm_revision = 0xa0;

	/* Now enable the feature flags we can. */
	अगर (hp->hm_revision == 0x20 || hp->hm_revision == 0x21)
		hp->happy_flags = HFLAG_20_21;
	अन्यथा अगर (hp->hm_revision != 0xa0)
		hp->happy_flags = HFLAG_NOT_A0;

	अगर (qp != शून्य)
		hp->happy_flags |= HFLAG_QUATTRO;

	/* Get the supported DVMA burst sizes from our Happy SBUS. */
	hp->happy_bursts = of_getपूर्णांकprop_शेष(sbus_dp,
						 "burst-sizes", 0x00);

	hp->happy_block = dma_alloc_coherent(hp->dma_dev,
					     PAGE_SIZE,
					     &hp->hblock_dvma,
					     GFP_ATOMIC);
	err = -ENOMEM;
	अगर (!hp->happy_block)
		जाओ err_out_iounmap;

	/* Force check of the link first समय we are brought up. */
	hp->linkcheck = 0;

	/* Force समयr state to 'asleep' with count of zero. */
	hp->समयr_state = asleep;
	hp->समयr_ticks = 0;

	समयr_setup(&hp->happy_समयr, happy_meal_समयr, 0);

	hp->dev = dev;
	dev->netdev_ops = &hme_netdev_ops;
	dev->watchकरोg_समयo = 5*HZ;
	dev->ethtool_ops = &hme_ethtool_ops;

	/* Happy Meal can करो it all... */
	dev->hw_features = NETIF_F_SG | NETIF_F_HW_CSUM;
	dev->features |= dev->hw_features | NETIF_F_RXCSUM;

	hp->irq = op->archdata.irqs[0];

#अगर defined(CONFIG_SBUS) && defined(CONFIG_PCI)
	/* Hook up SBUS रेजिस्टर/descriptor accessors. */
	hp->पढ़ो_desc32 = sbus_hme_पढ़ो_desc32;
	hp->ग_लिखो_txd = sbus_hme_ग_लिखो_txd;
	hp->ग_लिखो_rxd = sbus_hme_ग_लिखो_rxd;
	hp->पढ़ो32 = sbus_hme_पढ़ो32;
	hp->ग_लिखो32 = sbus_hme_ग_लिखो32;
#पूर्ण_अगर

	/* Grrr, Happy Meal comes up by शेष not advertising
	 * full duplex 100baseT capabilities, fix this.
	 */
	spin_lock_irq(&hp->happy_lock);
	happy_meal_set_initial_advertisement(hp);
	spin_unlock_irq(&hp->happy_lock);

	err = रेजिस्टर_netdev(hp->dev);
	अगर (err) अणु
		prपूर्णांकk(KERN_ERR "happymeal: Cannot register net device, "
		       "aborting.\n");
		जाओ err_out_मुक्त_coherent;
	पूर्ण

	platक्रमm_set_drvdata(op, hp);

	अगर (qfe_slot != -1)
		prपूर्णांकk(KERN_INFO "%s: Quattro HME slot %d (SBUS) 10/100baseT Ethernet ",
		       dev->name, qfe_slot);
	अन्यथा
		prपूर्णांकk(KERN_INFO "%s: HAPPY MEAL (SBUS) 10/100baseT Ethernet ",
		       dev->name);

	prपूर्णांकk("%pM\n", dev->dev_addr);

	वापस 0;

err_out_मुक्त_coherent:
	dma_मुक्त_coherent(hp->dma_dev,
			  PAGE_SIZE,
			  hp->happy_block,
			  hp->hblock_dvma);

err_out_iounmap:
	अगर (hp->gregs)
		of_iounmap(&op->resource[0], hp->gregs, GREG_REG_SIZE);
	अगर (hp->etxregs)
		of_iounmap(&op->resource[1], hp->etxregs, ETX_REG_SIZE);
	अगर (hp->erxregs)
		of_iounmap(&op->resource[2], hp->erxregs, ERX_REG_SIZE);
	अगर (hp->bigmacregs)
		of_iounmap(&op->resource[3], hp->bigmacregs, BMAC_REG_SIZE);
	अगर (hp->tcvregs)
		of_iounmap(&op->resource[4], hp->tcvregs, TCVR_REG_SIZE);

	अगर (qp)
		qp->happy_meals[qfe_slot] = शून्य;

err_out_मुक्त_netdev:
	मुक्त_netdev(dev);

err_out:
	वापस err;
पूर्ण
#पूर्ण_अगर

#अगर_घोषित CONFIG_PCI
#अगर_अघोषित CONFIG_SPARC
अटल पूर्णांक is_quattro_p(काष्ठा pci_dev *pdev)
अणु
	काष्ठा pci_dev *busdev = pdev->bus->self;
	काष्ठा pci_dev *this_pdev;
	पूर्णांक n_hmes;

	अगर (busdev == शून्य ||
	    busdev->venकरोr != PCI_VENDOR_ID_DEC ||
	    busdev->device != PCI_DEVICE_ID_DEC_21153)
		वापस 0;

	n_hmes = 0;
	list_क्रम_each_entry(this_pdev, &pdev->bus->devices, bus_list) अणु
		अगर (this_pdev->venकरोr == PCI_VENDOR_ID_SUN &&
		    this_pdev->device == PCI_DEVICE_ID_SUN_HAPPYMEAL)
			n_hmes++;
	पूर्ण

	अगर (n_hmes != 4)
		वापस 0;

	वापस 1;
पूर्ण

/* Fetch MAC address from vital product data of PCI ROM. */
अटल पूर्णांक find_eth_addr_in_vpd(व्योम __iomem *rom_base, पूर्णांक len, पूर्णांक index, अचिन्हित अक्षर *dev_addr)
अणु
	पूर्णांक this_offset;

	क्रम (this_offset = 0x20; this_offset < len; this_offset++) अणु
		व्योम __iomem *p = rom_base + this_offset;

		अगर (पढ़ोb(p + 0) != 0x90 ||
		    पढ़ोb(p + 1) != 0x00 ||
		    पढ़ोb(p + 2) != 0x09 ||
		    पढ़ोb(p + 3) != 0x4e ||
		    पढ़ोb(p + 4) != 0x41 ||
		    पढ़ोb(p + 5) != 0x06)
			जारी;

		this_offset += 6;
		p += 6;

		अगर (index == 0) अणु
			पूर्णांक i;

			क्रम (i = 0; i < 6; i++)
				dev_addr[i] = पढ़ोb(p + i);
			वापस 1;
		पूर्ण
		index--;
	पूर्ण
	वापस 0;
पूर्ण

अटल व्योम get_hme_mac_nonsparc(काष्ठा pci_dev *pdev, अचिन्हित अक्षर *dev_addr)
अणु
	माप_प्रकार size;
	व्योम __iomem *p = pci_map_rom(pdev, &size);

	अगर (p) अणु
		पूर्णांक index = 0;
		पूर्णांक found;

		अगर (is_quattro_p(pdev))
			index = PCI_SLOT(pdev->devfn);

		found = पढ़ोb(p) == 0x55 &&
			पढ़ोb(p + 1) == 0xaa &&
			find_eth_addr_in_vpd(p, (64 * 1024), index, dev_addr);
		pci_unmap_rom(pdev, p);
		अगर (found)
			वापस;
	पूर्ण

	/* Sun MAC prefix then 3 अक्रमom bytes. */
	dev_addr[0] = 0x08;
	dev_addr[1] = 0x00;
	dev_addr[2] = 0x20;
	get_अक्रमom_bytes(&dev_addr[3], 3);
पूर्ण
#पूर्ण_अगर /* !(CONFIG_SPARC) */

अटल पूर्णांक happy_meal_pci_probe(काष्ठा pci_dev *pdev,
				स्थिर काष्ठा pci_device_id *ent)
अणु
	काष्ठा quattro *qp = शून्य;
#अगर_घोषित CONFIG_SPARC
	काष्ठा device_node *dp;
#पूर्ण_अगर
	काष्ठा happy_meal *hp;
	काष्ठा net_device *dev;
	व्योम __iomem *hpreg_base;
	अचिन्हित दीर्घ hpreg_res;
	पूर्णांक i, qfe_slot = -1;
	अक्षर prom_name[64];
	पूर्णांक err;

	/* Now make sure pci_dev cookie is there. */
#अगर_घोषित CONFIG_SPARC
	dp = pci_device_to_OF_node(pdev);
	snम_लिखो(prom_name, माप(prom_name), "%pOFn", dp);
#अन्यथा
	अगर (is_quattro_p(pdev))
		म_नकल(prom_name, "SUNW,qfe");
	अन्यथा
		म_नकल(prom_name, "SUNW,hme");
#पूर्ण_अगर

	err = -ENODEV;

	अगर (pci_enable_device(pdev))
		जाओ err_out;
	pci_set_master(pdev);

	अगर (!म_भेद(prom_name, "SUNW,qfe") || !म_भेद(prom_name, "qfe")) अणु
		qp = quattro_pci_find(pdev);
		अगर (qp == शून्य)
			जाओ err_out;
		क्रम (qfe_slot = 0; qfe_slot < 4; qfe_slot++)
			अगर (qp->happy_meals[qfe_slot] == शून्य)
				अवरोध;
		अगर (qfe_slot == 4)
			जाओ err_out;
	पूर्ण

	dev = alloc_etherdev(माप(काष्ठा happy_meal));
	err = -ENOMEM;
	अगर (!dev)
		जाओ err_out;
	SET_NETDEV_DEV(dev, &pdev->dev);

	अगर (hme_version_prपूर्णांकed++ == 0)
		prपूर्णांकk(KERN_INFO "%s", version);

	hp = netdev_priv(dev);

	hp->happy_dev = pdev;
	hp->dma_dev = &pdev->dev;

	spin_lock_init(&hp->happy_lock);

	अगर (qp != शून्य) अणु
		hp->qfe_parent = qp;
		hp->qfe_ent = qfe_slot;
		qp->happy_meals[qfe_slot] = dev;
	पूर्ण

	hpreg_res = pci_resource_start(pdev, 0);
	err = -ENODEV;
	अगर ((pci_resource_flags(pdev, 0) & IORESOURCE_IO) != 0) अणु
		prपूर्णांकk(KERN_ERR "happymeal(PCI): Cannot find proper PCI device base address.\n");
		जाओ err_out_clear_quattro;
	पूर्ण
	अगर (pci_request_regions(pdev, DRV_NAME)) अणु
		prपूर्णांकk(KERN_ERR "happymeal(PCI): Cannot obtain PCI resources, "
		       "aborting.\n");
		जाओ err_out_clear_quattro;
	पूर्ण

	अगर ((hpreg_base = ioremap(hpreg_res, 0x8000)) == शून्य) अणु
		prपूर्णांकk(KERN_ERR "happymeal(PCI): Unable to remap card memory.\n");
		जाओ err_out_मुक्त_res;
	पूर्ण

	क्रम (i = 0; i < 6; i++) अणु
		अगर (macaddr[i] != 0)
			अवरोध;
	पूर्ण
	अगर (i < 6) अणु /* a mac address was given */
		क्रम (i = 0; i < 6; i++)
			dev->dev_addr[i] = macaddr[i];
		macaddr[5]++;
	पूर्ण अन्यथा अणु
#अगर_घोषित CONFIG_SPARC
		स्थिर अचिन्हित अक्षर *addr;
		पूर्णांक len;

		अगर (qfe_slot != -1 &&
		    (addr = of_get_property(dp, "local-mac-address", &len))
			!= शून्य &&
		    len == 6) अणु
			स_नकल(dev->dev_addr, addr, ETH_ALEN);
		पूर्ण अन्यथा अणु
			स_नकल(dev->dev_addr, idprom->id_ethaddr, ETH_ALEN);
		पूर्ण
#अन्यथा
		get_hme_mac_nonsparc(pdev, &dev->dev_addr[0]);
#पूर्ण_अगर
	पूर्ण

	/* Layout रेजिस्टरs. */
	hp->gregs      = (hpreg_base + 0x0000UL);
	hp->etxregs    = (hpreg_base + 0x2000UL);
	hp->erxregs    = (hpreg_base + 0x4000UL);
	hp->bigmacregs = (hpreg_base + 0x6000UL);
	hp->tcvregs    = (hpreg_base + 0x7000UL);

#अगर_घोषित CONFIG_SPARC
	hp->hm_revision = of_getपूर्णांकprop_शेष(dp, "hm-rev", 0xff);
	अगर (hp->hm_revision == 0xff)
		hp->hm_revision = 0xc0 | (pdev->revision & 0x0f);
#अन्यथा
	/* works with this on non-sparc hosts */
	hp->hm_revision = 0x20;
#पूर्ण_अगर

	/* Now enable the feature flags we can. */
	अगर (hp->hm_revision == 0x20 || hp->hm_revision == 0x21)
		hp->happy_flags = HFLAG_20_21;
	अन्यथा अगर (hp->hm_revision != 0xa0 && hp->hm_revision != 0xc0)
		hp->happy_flags = HFLAG_NOT_A0;

	अगर (qp != शून्य)
		hp->happy_flags |= HFLAG_QUATTRO;

	/* And of course, indicate this is PCI. */
	hp->happy_flags |= HFLAG_PCI;

#अगर_घोषित CONFIG_SPARC
	/* Assume PCI happy meals can handle all burst sizes. */
	hp->happy_bursts = DMA_BURSTBITS;
#पूर्ण_अगर

	hp->happy_block = dma_alloc_coherent(&pdev->dev, PAGE_SIZE,
					     &hp->hblock_dvma, GFP_KERNEL);
	err = -ENODEV;
	अगर (!hp->happy_block)
		जाओ err_out_iounmap;

	hp->linkcheck = 0;
	hp->समयr_state = asleep;
	hp->समयr_ticks = 0;

	समयr_setup(&hp->happy_समयr, happy_meal_समयr, 0);

	hp->irq = pdev->irq;
	hp->dev = dev;
	dev->netdev_ops = &hme_netdev_ops;
	dev->watchकरोg_समयo = 5*HZ;
	dev->ethtool_ops = &hme_ethtool_ops;

	/* Happy Meal can करो it all... */
	dev->hw_features = NETIF_F_SG | NETIF_F_HW_CSUM;
	dev->features |= dev->hw_features | NETIF_F_RXCSUM;

#अगर defined(CONFIG_SBUS) && defined(CONFIG_PCI)
	/* Hook up PCI रेजिस्टर/descriptor accessors. */
	hp->पढ़ो_desc32 = pci_hme_पढ़ो_desc32;
	hp->ग_लिखो_txd = pci_hme_ग_लिखो_txd;
	hp->ग_लिखो_rxd = pci_hme_ग_लिखो_rxd;
	hp->पढ़ो32 = pci_hme_पढ़ो32;
	hp->ग_लिखो32 = pci_hme_ग_लिखो32;
#पूर्ण_अगर

	/* Grrr, Happy Meal comes up by शेष not advertising
	 * full duplex 100baseT capabilities, fix this.
	 */
	spin_lock_irq(&hp->happy_lock);
	happy_meal_set_initial_advertisement(hp);
	spin_unlock_irq(&hp->happy_lock);

	err = रेजिस्टर_netdev(hp->dev);
	अगर (err) अणु
		prपूर्णांकk(KERN_ERR "happymeal(PCI): Cannot register net device, "
		       "aborting.\n");
		जाओ err_out_iounmap;
	पूर्ण

	pci_set_drvdata(pdev, hp);

	अगर (!qfe_slot) अणु
		काष्ठा pci_dev *qpdev = qp->quattro_dev;

		prom_name[0] = 0;
		अगर (!म_भेदन(dev->name, "eth", 3)) अणु
			पूर्णांक i = simple_म_से_अदीर्घ(dev->name + 3, शून्य, 10);
			प्र_लिखो(prom_name, "-%d", i + 3);
		पूर्ण
		prपूर्णांकk(KERN_INFO "%s%s: Quattro HME (PCI/CheerIO) 10/100baseT Ethernet ", dev->name, prom_name);
		अगर (qpdev->venकरोr == PCI_VENDOR_ID_DEC &&
		    qpdev->device == PCI_DEVICE_ID_DEC_21153)
			prपूर्णांकk("DEC 21153 PCI Bridge\n");
		अन्यथा
			prपूर्णांकk("unknown bridge %04x.%04x\n",
				qpdev->venकरोr, qpdev->device);
	पूर्ण

	अगर (qfe_slot != -1)
		prपूर्णांकk(KERN_INFO "%s: Quattro HME slot %d (PCI/CheerIO) 10/100baseT Ethernet ",
		       dev->name, qfe_slot);
	अन्यथा
		prपूर्णांकk(KERN_INFO "%s: HAPPY MEAL (PCI/CheerIO) 10/100BaseT Ethernet ",
		       dev->name);

	prपूर्णांकk("%pM\n", dev->dev_addr);

	वापस 0;

err_out_iounmap:
	iounmap(hp->gregs);

err_out_मुक्त_res:
	pci_release_regions(pdev);

err_out_clear_quattro:
	अगर (qp != शून्य)
		qp->happy_meals[qfe_slot] = शून्य;

	मुक्त_netdev(dev);

err_out:
	वापस err;
पूर्ण

अटल व्योम happy_meal_pci_हटाओ(काष्ठा pci_dev *pdev)
अणु
	काष्ठा happy_meal *hp = pci_get_drvdata(pdev);
	काष्ठा net_device *net_dev = hp->dev;

	unरेजिस्टर_netdev(net_dev);

	dma_मुक्त_coherent(hp->dma_dev, PAGE_SIZE,
			  hp->happy_block, hp->hblock_dvma);
	iounmap(hp->gregs);
	pci_release_regions(hp->happy_dev);

	मुक्त_netdev(net_dev);
पूर्ण

अटल स्थिर काष्ठा pci_device_id happymeal_pci_ids[] = अणु
	अणु PCI_DEVICE(PCI_VENDOR_ID_SUN, PCI_DEVICE_ID_SUN_HAPPYMEAL) पूर्ण,
	अणु पूर्ण			/* Terminating entry */
पूर्ण;

MODULE_DEVICE_TABLE(pci, happymeal_pci_ids);

अटल काष्ठा pci_driver hme_pci_driver = अणु
	.name		= "hme",
	.id_table	= happymeal_pci_ids,
	.probe		= happy_meal_pci_probe,
	.हटाओ		= happy_meal_pci_हटाओ,
पूर्ण;

अटल पूर्णांक __init happy_meal_pci_init(व्योम)
अणु
	वापस pci_रेजिस्टर_driver(&hme_pci_driver);
पूर्ण

अटल व्योम happy_meal_pci_निकास(व्योम)
अणु
	pci_unरेजिस्टर_driver(&hme_pci_driver);

	जबतक (qfe_pci_list) अणु
		काष्ठा quattro *qfe = qfe_pci_list;
		काष्ठा quattro *next = qfe->next;

		kमुक्त(qfe);

		qfe_pci_list = next;
	पूर्ण
पूर्ण

#पूर्ण_अगर

#अगर_घोषित CONFIG_SBUS
अटल स्थिर काष्ठा of_device_id hme_sbus_match[];
अटल पूर्णांक hme_sbus_probe(काष्ठा platक्रमm_device *op)
अणु
	स्थिर काष्ठा of_device_id *match;
	काष्ठा device_node *dp = op->dev.of_node;
	स्थिर अक्षर *model = of_get_property(dp, "model", शून्य);
	पूर्णांक is_qfe;

	match = of_match_device(hme_sbus_match, &op->dev);
	अगर (!match)
		वापस -EINVAL;
	is_qfe = (match->data != शून्य);

	अगर (!is_qfe && model && !म_भेद(model, "SUNW,sbus-qfe"))
		is_qfe = 1;

	वापस happy_meal_sbus_probe_one(op, is_qfe);
पूर्ण

अटल पूर्णांक hme_sbus_हटाओ(काष्ठा platक्रमm_device *op)
अणु
	काष्ठा happy_meal *hp = platक्रमm_get_drvdata(op);
	काष्ठा net_device *net_dev = hp->dev;

	unरेजिस्टर_netdev(net_dev);

	/* XXX qfe parent पूर्णांकerrupt... */

	of_iounmap(&op->resource[0], hp->gregs, GREG_REG_SIZE);
	of_iounmap(&op->resource[1], hp->etxregs, ETX_REG_SIZE);
	of_iounmap(&op->resource[2], hp->erxregs, ERX_REG_SIZE);
	of_iounmap(&op->resource[3], hp->bigmacregs, BMAC_REG_SIZE);
	of_iounmap(&op->resource[4], hp->tcvregs, TCVR_REG_SIZE);
	dma_मुक्त_coherent(hp->dma_dev,
			  PAGE_SIZE,
			  hp->happy_block,
			  hp->hblock_dvma);

	मुक्त_netdev(net_dev);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id hme_sbus_match[] = अणु
	अणु
		.name = "SUNW,hme",
	पूर्ण,
	अणु
		.name = "SUNW,qfe",
		.data = (व्योम *) 1,
	पूर्ण,
	अणु
		.name = "qfe",
		.data = (व्योम *) 1,
	पूर्ण,
	अणुपूर्ण,
पूर्ण;

MODULE_DEVICE_TABLE(of, hme_sbus_match);

अटल काष्ठा platक्रमm_driver hme_sbus_driver = अणु
	.driver = अणु
		.name = "hme",
		.of_match_table = hme_sbus_match,
	पूर्ण,
	.probe		= hme_sbus_probe,
	.हटाओ		= hme_sbus_हटाओ,
पूर्ण;

अटल पूर्णांक __init happy_meal_sbus_init(व्योम)
अणु
	पूर्णांक err;

	err = platक्रमm_driver_रेजिस्टर(&hme_sbus_driver);
	अगर (!err)
		err = quattro_sbus_रेजिस्टर_irqs();

	वापस err;
पूर्ण

अटल व्योम happy_meal_sbus_निकास(व्योम)
अणु
	platक्रमm_driver_unरेजिस्टर(&hme_sbus_driver);
	quattro_sbus_मुक्त_irqs();

	जबतक (qfe_sbus_list) अणु
		काष्ठा quattro *qfe = qfe_sbus_list;
		काष्ठा quattro *next = qfe->next;

		kमुक्त(qfe);

		qfe_sbus_list = next;
	पूर्ण
पूर्ण
#पूर्ण_अगर

अटल पूर्णांक __init happy_meal_probe(व्योम)
अणु
	पूर्णांक err = 0;

#अगर_घोषित CONFIG_SBUS
	err = happy_meal_sbus_init();
#पूर्ण_अगर
#अगर_घोषित CONFIG_PCI
	अगर (!err) अणु
		err = happy_meal_pci_init();
#अगर_घोषित CONFIG_SBUS
		अगर (err)
			happy_meal_sbus_निकास();
#पूर्ण_अगर
	पूर्ण
#पूर्ण_अगर

	वापस err;
पूर्ण


अटल व्योम __निकास happy_meal_निकास(व्योम)
अणु
#अगर_घोषित CONFIG_SBUS
	happy_meal_sbus_निकास();
#पूर्ण_अगर
#अगर_घोषित CONFIG_PCI
	happy_meal_pci_निकास();
#पूर्ण_अगर
पूर्ण

module_init(happy_meal_probe);
module_निकास(happy_meal_निकास);
