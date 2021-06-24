<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/* cassini.c: Sun Microप्रणालीs Cassini(+) ethernet driver.
 *
 * Copyright (C) 2004 Sun Microप्रणालीs Inc.
 * Copyright (C) 2003 Adrian Sun (asun@darksunrising.com)
 *
 * This driver uses the sungem driver (c) David Miller
 * (davem@redhat.com) as its basis.
 *
 * The cassini chip has a number of features that distinguish it from
 * the gem chip:
 *  4 transmit descriptor rings that are used क्रम either QoS (VLAN) or
 *      load balancing (non-VLAN mode)
 *  batching of multiple packets
 *  multiple CPU dispatching
 *  page-based RX descriptor engine with separate completion rings
 *  Gigabit support (GMII and PCS पूर्णांकerface)
 *  MIF link up/करोwn detection works
 *
 * RX is handled by page sized buffers that are attached as fragments to
 * the skb. here's what's करोne:
 *  -- driver allocates pages at a समय and keeps reference counts
 *     on them.
 *  -- the upper protocol layers assume that the header is in the skb
 *     itself. as a result, cassini will copy a small amount (64 bytes)
 *     to make them happy.
 *  -- driver appends the rest of the data pages as frags to skbuffs
 *     and increments the reference count
 *  -- on page reclamation, the driver swaps the page with a spare page.
 *     अगर that page is still in use, it मुक्तs its reference to that page,
 *     and allocates a new page क्रम use. otherwise, it just recycles the
 *     the page.
 *
 * NOTE: cassini can parse the header. however, it's not worth it
 *       as दीर्घ as the network stack requires a header copy.
 *
 * TX has 4 queues. currently these queues are used in a round-robin
 * fashion क्रम load balancing. They can also be used क्रम QoS. क्रम that
 * to work, however, QoS inक्रमmation needs to be exposed करोwn to the driver
 * level so that subqueues get targeted to particular transmit rings.
 * alternatively, the queues can be configured via use of the all-purpose
 * ioctl.
 *
 * RX DATA: the rx completion ring has all the info, but the rx desc
 * ring has all of the data. RX can conceivably come in under multiple
 * पूर्णांकerrupts, but the INT# assignment needs to be set up properly by
 * the BIOS and conveyed to the driver. PCI BIOSes करोn't know how to करो
 * that. also, the two descriptor rings are deचिन्हित to distinguish between
 * encrypted and non-encrypted packets, but we use them क्रम buffering
 * instead.
 *
 * by शेष, the selective clear mask is set up to process rx packets.
 */

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#समावेश <linux/module.h>
#समावेश <linux/kernel.h>
#समावेश <linux/types.h>
#समावेश <linux/compiler.h>
#समावेश <linux/slab.h>
#समावेश <linux/delay.h>
#समावेश <linux/init.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/vदो_स्मृति.h>
#समावेश <linux/ioport.h>
#समावेश <linux/pci.h>
#समावेश <linux/mm.h>
#समावेश <linux/highस्मृति.स>
#समावेश <linux/list.h>
#समावेश <linux/dma-mapping.h>

#समावेश <linux/netdevice.h>
#समावेश <linux/etherdevice.h>
#समावेश <linux/skbuff.h>
#समावेश <linux/ethtool.h>
#समावेश <linux/crc32.h>
#समावेश <linux/अक्रमom.h>
#समावेश <linux/mii.h>
#समावेश <linux/ip.h>
#समावेश <linux/tcp.h>
#समावेश <linux/mutex.h>
#समावेश <linux/firmware.h>

#समावेश <net/checksum.h>

#समावेश <linux/atomic.h>
#समावेश <यंत्र/पन.स>
#समावेश <यंत्र/byteorder.h>
#समावेश <linux/uaccess.h>

#घोषणा cas_page_map(x)      kmap_atomic((x))
#घोषणा cas_page_unmap(x)    kunmap_atomic((x))
#घोषणा CAS_NCPUS            num_online_cpus()

#घोषणा cas_skb_release(x)  netअगर_rx(x)

/* select which firmware to use */
#घोषणा USE_HP_WORKAROUND
#घोषणा HP_WORKAROUND_DEFAULT /* select which firmware to use as शेष */
#घोषणा CAS_HP_ALT_FIRMWARE   cas_prog_null /* alternate firmware */

#समावेश "cassini.h"

#घोषणा USE_TX_COMPWB      /* use completion ग_लिखोback रेजिस्टरs */
#घोषणा USE_CSMA_CD_PROTO  /* standard CSMA/CD */
#घोषणा USE_RX_BLANK       /* hw पूर्णांकerrupt mitigation */
#अघोषित USE_ENTROPY_DEV     /* करोn't test क्रम entropy device */

/* NOTE: these aren't useable unless PCI पूर्णांकerrupts can be asचिन्हित.
 * also, we need to make cp->lock finer-grained.
 */
#अघोषित  USE_PCI_INTB
#अघोषित  USE_PCI_INTC
#अघोषित  USE_PCI_INTD
#अघोषित  USE_QOS

#अघोषित  USE_VPD_DEBUG       /* debug vpd inक्रमmation अगर defined */

/* rx processing options */
#घोषणा USE_PAGE_ORDER      /* specअगरy to allocate large rx pages */
#घोषणा RX_DONT_BATCH  0    /* अगर 1, करोn't batch flows */
#घोषणा RX_COPY_ALWAYS 0    /* अगर 0, use frags */
#घोषणा RX_COPY_MIN    64   /* copy a little to make upper layers happy */
#अघोषित  RX_COUNT_BUFFERS    /* define to calculate RX buffer stats */

#घोषणा DRV_MODULE_NAME		"cassini"
#घोषणा DRV_MODULE_VERSION	"1.6"
#घोषणा DRV_MODULE_RELDATE	"21 May 2008"

#घोषणा CAS_DEF_MSG_ENABLE	  \
	(NETIF_MSG_DRV		| \
	 NETIF_MSG_PROBE	| \
	 NETIF_MSG_LINK		| \
	 NETIF_MSG_TIMER	| \
	 NETIF_MSG_IFDOWN	| \
	 NETIF_MSG_IFUP		| \
	 NETIF_MSG_RX_ERR	| \
	 NETIF_MSG_TX_ERR)

/* length of समय beक्रमe we decide the hardware is borked,
 * and dev->tx_समयout() should be called to fix the problem
 */
#घोषणा CAS_TX_TIMEOUT			(HZ)
#घोषणा CAS_LINK_TIMEOUT                (22*HZ/10)
#घोषणा CAS_LINK_FAST_TIMEOUT           (1)

/* समयout values क्रम state changing. these specअगरy the number
 * of 10us delays to be used beक्रमe giving up.
 */
#घोषणा STOP_TRIES_PHY 1000
#घोषणा STOP_TRIES     5000

/* specअगरy a minimum frame size to deal with some fअगरo issues
 * max mtu == 2 * page size - ethernet header - 64 - swivel =
 *            2 * page_size - 0x50
 */
#घोषणा CAS_MIN_FRAME			97
#घोषणा CAS_1000MB_MIN_FRAME            255
#घोषणा CAS_MIN_MTU                     60
#घोषणा CAS_MAX_MTU                     min(((cp->page_size << 1) - 0x50), 9000)

#अगर 1
/*
 * Eliminate these and use separate atomic counters क्रम each, to
 * aव्योम a race condition.
 */
#अन्यथा
#घोषणा CAS_RESET_MTU                   1
#घोषणा CAS_RESET_ALL                   2
#घोषणा CAS_RESET_SPARE                 3
#पूर्ण_अगर

अटल अक्षर version[] =
	DRV_MODULE_NAME ".c:v" DRV_MODULE_VERSION " (" DRV_MODULE_RELDATE ")\n";

अटल पूर्णांक cassini_debug = -1;	/* -1 == use CAS_DEF_MSG_ENABLE as value */
अटल पूर्णांक link_mode;

MODULE_AUTHOR("Adrian Sun (asun@darksunrising.com)");
MODULE_DESCRIPTION("Sun Cassini(+) ethernet driver");
MODULE_LICENSE("GPL");
MODULE_FIRMWARE("sun/cassini.bin");
module_param(cassini_debug, पूर्णांक, 0);
MODULE_PARM_DESC(cassini_debug, "Cassini bitmapped debugging message enable value");
module_param(link_mode, पूर्णांक, 0);
MODULE_PARM_DESC(link_mode, "default link mode");

/*
 * Work around क्रम a PCS bug in which the link goes करोwn due to the chip
 * being confused and never showing a link status of "up."
 */
#घोषणा DEFAULT_LINKDOWN_TIMEOUT 5
/*
 * Value in seconds, क्रम user input.
 */
अटल पूर्णांक linkकरोwn_समयout = DEFAULT_LINKDOWN_TIMEOUT;
module_param(linkकरोwn_समयout, पूर्णांक, 0);
MODULE_PARM_DESC(linkकरोwn_समयout,
"min reset interval in sec. for PCS linkdown issue; disabled if not positive");

/*
 * value in 'ticks' (units used by jअगरfies). Set when we init the
 * module because 'HZ' in actually a function call on some flavors of
 * Linux.  This will शेष to DEFAULT_LINKDOWN_TIMEOUT * HZ.
 */
अटल पूर्णांक link_transition_समयout;



अटल u16 link_modes[] = अणु
	BMCR_ANENABLE,			 /* 0 : स्वतःneg */
	0,				 /* 1 : 10bt half duplex */
	BMCR_SPEED100,			 /* 2 : 100bt half duplex */
	BMCR_FULLDPLX,			 /* 3 : 10bt full duplex */
	BMCR_SPEED100|BMCR_FULLDPLX,	 /* 4 : 100bt full duplex */
	CAS_BMCR_SPEED1000|BMCR_FULLDPLX /* 5 : 1000bt full duplex */
पूर्ण;

अटल स्थिर काष्ठा pci_device_id cas_pci_tbl[] = अणु
	अणु PCI_VENDOR_ID_SUN, PCI_DEVICE_ID_SUN_CASSINI,
	  PCI_ANY_ID, PCI_ANY_ID, 0, 0, 0UL पूर्ण,
	अणु PCI_VENDOR_ID_NS, PCI_DEVICE_ID_NS_SATURN,
	  PCI_ANY_ID, PCI_ANY_ID, 0, 0, 0UL पूर्ण,
	अणु 0, पूर्ण
पूर्ण;

MODULE_DEVICE_TABLE(pci, cas_pci_tbl);

अटल व्योम cas_set_link_modes(काष्ठा cas *cp);

अटल अंतरभूत व्योम cas_lock_tx(काष्ठा cas *cp)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < N_TX_RINGS; i++)
		spin_lock_nested(&cp->tx_lock[i], i);
पूर्ण

/* WTZ: QA was finding deadlock problems with the previous
 * versions after दीर्घ test runs with multiple cards per machine.
 * See अगर replacing cas_lock_all with safer versions helps. The
 * symptoms QA is reporting match those we'd expect अगर पूर्णांकerrupts
 * aren't being properly restored, and we fixed a previous deadlock
 * with similar symptoms by using save/restore versions in other
 * places.
 */
#घोषणा cas_lock_all_save(cp, flags) \
करो अणु \
	काष्ठा cas *xxxcp = (cp); \
	spin_lock_irqsave(&xxxcp->lock, flags); \
	cas_lock_tx(xxxcp); \
पूर्ण जबतक (0)

अटल अंतरभूत व्योम cas_unlock_tx(काष्ठा cas *cp)
अणु
	पूर्णांक i;

	क्रम (i = N_TX_RINGS; i > 0; i--)
		spin_unlock(&cp->tx_lock[i - 1]);
पूर्ण

#घोषणा cas_unlock_all_restore(cp, flags) \
करो अणु \
	काष्ठा cas *xxxcp = (cp); \
	cas_unlock_tx(xxxcp); \
	spin_unlock_irqrestore(&xxxcp->lock, flags); \
पूर्ण जबतक (0)

अटल व्योम cas_disable_irq(काष्ठा cas *cp, स्थिर पूर्णांक ring)
अणु
	/* Make sure we won't get any more पूर्णांकerrupts */
	अगर (ring == 0) अणु
		ग_लिखोl(0xFFFFFFFF, cp->regs + REG_INTR_MASK);
		वापस;
	पूर्ण

	/* disable completion पूर्णांकerrupts and selectively mask */
	अगर (cp->cas_flags & CAS_FLAG_REG_PLUS) अणु
		चयन (ring) अणु
#अगर defined (USE_PCI_INTB) || defined(USE_PCI_INTC) || defined(USE_PCI_INTD)
#अगर_घोषित USE_PCI_INTB
		हाल 1:
#पूर्ण_अगर
#अगर_घोषित USE_PCI_INTC
		हाल 2:
#पूर्ण_अगर
#अगर_घोषित USE_PCI_INTD
		हाल 3:
#पूर्ण_अगर
			ग_लिखोl(INTRN_MASK_CLEAR_ALL | INTRN_MASK_RX_EN,
			       cp->regs + REG_PLUS_INTRN_MASK(ring));
			अवरोध;
#पूर्ण_अगर
		शेष:
			ग_लिखोl(INTRN_MASK_CLEAR_ALL, cp->regs +
			       REG_PLUS_INTRN_MASK(ring));
			अवरोध;
		पूर्ण
	पूर्ण
पूर्ण

अटल अंतरभूत व्योम cas_mask_पूर्णांकr(काष्ठा cas *cp)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < N_RX_COMP_RINGS; i++)
		cas_disable_irq(cp, i);
पूर्ण

अटल व्योम cas_enable_irq(काष्ठा cas *cp, स्थिर पूर्णांक ring)
अणु
	अगर (ring == 0) अणु /* all but TX_DONE */
		ग_लिखोl(INTR_TX_DONE, cp->regs + REG_INTR_MASK);
		वापस;
	पूर्ण

	अगर (cp->cas_flags & CAS_FLAG_REG_PLUS) अणु
		चयन (ring) अणु
#अगर defined (USE_PCI_INTB) || defined(USE_PCI_INTC) || defined(USE_PCI_INTD)
#अगर_घोषित USE_PCI_INTB
		हाल 1:
#पूर्ण_अगर
#अगर_घोषित USE_PCI_INTC
		हाल 2:
#पूर्ण_अगर
#अगर_घोषित USE_PCI_INTD
		हाल 3:
#पूर्ण_अगर
			ग_लिखोl(INTRN_MASK_RX_EN, cp->regs +
			       REG_PLUS_INTRN_MASK(ring));
			अवरोध;
#पूर्ण_अगर
		शेष:
			अवरोध;
		पूर्ण
	पूर्ण
पूर्ण

अटल अंतरभूत व्योम cas_unmask_पूर्णांकr(काष्ठा cas *cp)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < N_RX_COMP_RINGS; i++)
		cas_enable_irq(cp, i);
पूर्ण

अटल अंतरभूत व्योम cas_entropy_gather(काष्ठा cas *cp)
अणु
#अगर_घोषित USE_ENTROPY_DEV
	अगर ((cp->cas_flags & CAS_FLAG_ENTROPY_DEV) == 0)
		वापस;

	batch_entropy_store(पढ़ोl(cp->regs + REG_ENTROPY_IV),
			    पढ़ोl(cp->regs + REG_ENTROPY_IV),
			    माप(uपूर्णांक64_t)*8);
#पूर्ण_अगर
पूर्ण

अटल अंतरभूत व्योम cas_entropy_reset(काष्ठा cas *cp)
अणु
#अगर_घोषित USE_ENTROPY_DEV
	अगर ((cp->cas_flags & CAS_FLAG_ENTROPY_DEV) == 0)
		वापस;

	ग_लिखोl(BIM_LOCAL_DEV_PAD | BIM_LOCAL_DEV_PROM | BIM_LOCAL_DEV_EXT,
	       cp->regs + REG_BIM_LOCAL_DEV_EN);
	ग_लिखोb(ENTROPY_RESET_STC_MODE, cp->regs + REG_ENTROPY_RESET);
	ग_लिखोb(0x55, cp->regs + REG_ENTROPY_RAND_REG);

	/* अगर we पढ़ो back 0x0, we करोn't have an entropy device */
	अगर (पढ़ोb(cp->regs + REG_ENTROPY_RAND_REG) == 0)
		cp->cas_flags &= ~CAS_FLAG_ENTROPY_DEV;
#पूर्ण_अगर
पूर्ण

/* access to the phy. the following assumes that we've initialized the MIF to
 * be in frame rather than bit-bang mode
 */
अटल u16 cas_phy_पढ़ो(काष्ठा cas *cp, पूर्णांक reg)
अणु
	u32 cmd;
	पूर्णांक limit = STOP_TRIES_PHY;

	cmd = MIF_FRAME_ST | MIF_FRAME_OP_READ;
	cmd |= CAS_BASE(MIF_FRAME_PHY_ADDR, cp->phy_addr);
	cmd |= CAS_BASE(MIF_FRAME_REG_ADDR, reg);
	cmd |= MIF_FRAME_TURN_AROUND_MSB;
	ग_लिखोl(cmd, cp->regs + REG_MIF_FRAME);

	/* poll क्रम completion */
	जबतक (limit-- > 0) अणु
		udelay(10);
		cmd = पढ़ोl(cp->regs + REG_MIF_FRAME);
		अगर (cmd & MIF_FRAME_TURN_AROUND_LSB)
			वापस cmd & MIF_FRAME_DATA_MASK;
	पूर्ण
	वापस 0xFFFF; /* -1 */
पूर्ण

अटल पूर्णांक cas_phy_ग_लिखो(काष्ठा cas *cp, पूर्णांक reg, u16 val)
अणु
	पूर्णांक limit = STOP_TRIES_PHY;
	u32 cmd;

	cmd = MIF_FRAME_ST | MIF_FRAME_OP_WRITE;
	cmd |= CAS_BASE(MIF_FRAME_PHY_ADDR, cp->phy_addr);
	cmd |= CAS_BASE(MIF_FRAME_REG_ADDR, reg);
	cmd |= MIF_FRAME_TURN_AROUND_MSB;
	cmd |= val & MIF_FRAME_DATA_MASK;
	ग_लिखोl(cmd, cp->regs + REG_MIF_FRAME);

	/* poll क्रम completion */
	जबतक (limit-- > 0) अणु
		udelay(10);
		cmd = पढ़ोl(cp->regs + REG_MIF_FRAME);
		अगर (cmd & MIF_FRAME_TURN_AROUND_LSB)
			वापस 0;
	पूर्ण
	वापस -1;
पूर्ण

अटल व्योम cas_phy_घातerup(काष्ठा cas *cp)
अणु
	u16 ctl = cas_phy_पढ़ो(cp, MII_BMCR);

	अगर ((ctl & BMCR_PDOWN) == 0)
		वापस;
	ctl &= ~BMCR_PDOWN;
	cas_phy_ग_लिखो(cp, MII_BMCR, ctl);
पूर्ण

अटल व्योम cas_phy_घातerकरोwn(काष्ठा cas *cp)
अणु
	u16 ctl = cas_phy_पढ़ो(cp, MII_BMCR);

	अगर (ctl & BMCR_PDOWN)
		वापस;
	ctl |= BMCR_PDOWN;
	cas_phy_ग_लिखो(cp, MII_BMCR, ctl);
पूर्ण

/* cp->lock held. note: the last put_page will मुक्त the buffer */
अटल पूर्णांक cas_page_मुक्त(काष्ठा cas *cp, cas_page_t *page)
अणु
	dma_unmap_page(&cp->pdev->dev, page->dma_addr, cp->page_size,
		       DMA_FROM_DEVICE);
	__मुक्त_pages(page->buffer, cp->page_order);
	kमुक्त(page);
	वापस 0;
पूर्ण

#अगर_घोषित RX_COUNT_BUFFERS
#घोषणा RX_USED_ADD(x, y)       ((x)->used += (y))
#घोषणा RX_USED_SET(x, y)       ((x)->used  = (y))
#अन्यथा
#घोषणा RX_USED_ADD(x, y) करो अणु पूर्ण जबतक(0)
#घोषणा RX_USED_SET(x, y) करो अणु पूर्ण जबतक(0)
#पूर्ण_अगर

/* local page allocation routines क्रम the receive buffers. jumbo pages
 * require at least 8K contiguous and 8K aligned buffers.
 */
अटल cas_page_t *cas_page_alloc(काष्ठा cas *cp, स्थिर gfp_t flags)
अणु
	cas_page_t *page;

	page = kदो_स्मृति(माप(cas_page_t), flags);
	अगर (!page)
		वापस शून्य;

	INIT_LIST_HEAD(&page->list);
	RX_USED_SET(page, 0);
	page->buffer = alloc_pages(flags, cp->page_order);
	अगर (!page->buffer)
		जाओ page_err;
	page->dma_addr = dma_map_page(&cp->pdev->dev, page->buffer, 0,
				      cp->page_size, DMA_FROM_DEVICE);
	वापस page;

page_err:
	kमुक्त(page);
	वापस शून्य;
पूर्ण

/* initialize spare pool of rx buffers, but allocate during the खोलो */
अटल व्योम cas_spare_init(काष्ठा cas *cp)
अणु
  	spin_lock(&cp->rx_inuse_lock);
	INIT_LIST_HEAD(&cp->rx_inuse_list);
	spin_unlock(&cp->rx_inuse_lock);

	spin_lock(&cp->rx_spare_lock);
	INIT_LIST_HEAD(&cp->rx_spare_list);
	cp->rx_spares_needed = RX_SPARE_COUNT;
	spin_unlock(&cp->rx_spare_lock);
पूर्ण

/* used on बंद. मुक्त all the spare buffers. */
अटल व्योम cas_spare_मुक्त(काष्ठा cas *cp)
अणु
	काष्ठा list_head list, *elem, *पंचांगp;

	/* मुक्त spare buffers */
	INIT_LIST_HEAD(&list);
	spin_lock(&cp->rx_spare_lock);
	list_splice_init(&cp->rx_spare_list, &list);
	spin_unlock(&cp->rx_spare_lock);
	list_क्रम_each_safe(elem, पंचांगp, &list) अणु
		cas_page_मुक्त(cp, list_entry(elem, cas_page_t, list));
	पूर्ण

	INIT_LIST_HEAD(&list);
#अगर 1
	/*
	 * Looks like Adrian had रक्षित this with a dअगरferent
	 * lock than used everywhere अन्यथा to manipulate this list.
	 */
	spin_lock(&cp->rx_inuse_lock);
	list_splice_init(&cp->rx_inuse_list, &list);
	spin_unlock(&cp->rx_inuse_lock);
#अन्यथा
	spin_lock(&cp->rx_spare_lock);
	list_splice_init(&cp->rx_inuse_list, &list);
	spin_unlock(&cp->rx_spare_lock);
#पूर्ण_अगर
	list_क्रम_each_safe(elem, पंचांगp, &list) अणु
		cas_page_मुक्त(cp, list_entry(elem, cas_page_t, list));
	पूर्ण
पूर्ण

/* replenish spares अगर needed */
अटल व्योम cas_spare_recover(काष्ठा cas *cp, स्थिर gfp_t flags)
अणु
	काष्ठा list_head list, *elem, *पंचांगp;
	पूर्णांक needed, i;

	/* check inuse list. अगर we करोn't need any more मुक्त buffers,
	 * just मुक्त it
	 */

	/* make a local copy of the list */
	INIT_LIST_HEAD(&list);
	spin_lock(&cp->rx_inuse_lock);
	list_splice_init(&cp->rx_inuse_list, &list);
	spin_unlock(&cp->rx_inuse_lock);

	list_क्रम_each_safe(elem, पंचांगp, &list) अणु
		cas_page_t *page = list_entry(elem, cas_page_t, list);

		/*
		 * With the lockless pagecache, cassini buffering scheme माला_लो
		 * slightly less accurate: we might find that a page has an
		 * elevated reference count here, due to a speculative ref,
		 * and skip it as in-use. Ideally we would be able to reclaim
		 * it. However this would be such a rare हाल, it करोesn't
		 * matter too much as we should pick it up the next समय round.
		 *
		 * Importantly, अगर we find that the page has a refcount of 1
		 * here (our refcount), then we know it is definitely not inuse
		 * so we can reuse it.
		 */
		अगर (page_count(page->buffer) > 1)
			जारी;

		list_del(elem);
		spin_lock(&cp->rx_spare_lock);
		अगर (cp->rx_spares_needed > 0) अणु
			list_add(elem, &cp->rx_spare_list);
			cp->rx_spares_needed--;
			spin_unlock(&cp->rx_spare_lock);
		पूर्ण अन्यथा अणु
			spin_unlock(&cp->rx_spare_lock);
			cas_page_मुक्त(cp, page);
		पूर्ण
	पूर्ण

	/* put any inuse buffers back on the list */
	अगर (!list_empty(&list)) अणु
		spin_lock(&cp->rx_inuse_lock);
		list_splice(&list, &cp->rx_inuse_list);
		spin_unlock(&cp->rx_inuse_lock);
	पूर्ण

	spin_lock(&cp->rx_spare_lock);
	needed = cp->rx_spares_needed;
	spin_unlock(&cp->rx_spare_lock);
	अगर (!needed)
		वापस;

	/* we still need spares, so try to allocate some */
	INIT_LIST_HEAD(&list);
	i = 0;
	जबतक (i < needed) अणु
		cas_page_t *spare = cas_page_alloc(cp, flags);
		अगर (!spare)
			अवरोध;
		list_add(&spare->list, &list);
		i++;
	पूर्ण

	spin_lock(&cp->rx_spare_lock);
	list_splice(&list, &cp->rx_spare_list);
	cp->rx_spares_needed -= i;
	spin_unlock(&cp->rx_spare_lock);
पूर्ण

/* pull a page from the list. */
अटल cas_page_t *cas_page_dequeue(काष्ठा cas *cp)
अणु
	काष्ठा list_head *entry;
	पूर्णांक recover;

	spin_lock(&cp->rx_spare_lock);
	अगर (list_empty(&cp->rx_spare_list)) अणु
		/* try to करो a quick recovery */
		spin_unlock(&cp->rx_spare_lock);
		cas_spare_recover(cp, GFP_ATOMIC);
		spin_lock(&cp->rx_spare_lock);
		अगर (list_empty(&cp->rx_spare_list)) अणु
			netअगर_err(cp, rx_err, cp->dev,
				  "no spare buffers available\n");
			spin_unlock(&cp->rx_spare_lock);
			वापस शून्य;
		पूर्ण
	पूर्ण

	entry = cp->rx_spare_list.next;
	list_del(entry);
	recover = ++cp->rx_spares_needed;
	spin_unlock(&cp->rx_spare_lock);

	/* trigger the समयr to करो the recovery */
	अगर ((recover & (RX_SPARE_RECOVER_VAL - 1)) == 0) अणु
#अगर 1
		atomic_inc(&cp->reset_task_pending);
		atomic_inc(&cp->reset_task_pending_spare);
		schedule_work(&cp->reset_task);
#अन्यथा
		atomic_set(&cp->reset_task_pending, CAS_RESET_SPARE);
		schedule_work(&cp->reset_task);
#पूर्ण_अगर
	पूर्ण
	वापस list_entry(entry, cas_page_t, list);
पूर्ण


अटल व्योम cas_mअगर_poll(काष्ठा cas *cp, स्थिर पूर्णांक enable)
अणु
	u32 cfg;

	cfg  = पढ़ोl(cp->regs + REG_MIF_CFG);
	cfg &= (MIF_CFG_MDIO_0 | MIF_CFG_MDIO_1);

	अगर (cp->phy_type & CAS_PHY_MII_MDIO1)
		cfg |= MIF_CFG_PHY_SELECT;

	/* poll and पूर्णांकerrupt on link status change. */
	अगर (enable) अणु
		cfg |= MIF_CFG_POLL_EN;
		cfg |= CAS_BASE(MIF_CFG_POLL_REG, MII_BMSR);
		cfg |= CAS_BASE(MIF_CFG_POLL_PHY, cp->phy_addr);
	पूर्ण
	ग_लिखोl((enable) ? ~(BMSR_LSTATUS | BMSR_ANEGCOMPLETE) : 0xFFFF,
	       cp->regs + REG_MIF_MASK);
	ग_लिखोl(cfg, cp->regs + REG_MIF_CFG);
पूर्ण

/* Must be invoked under cp->lock */
अटल व्योम cas_begin_स्वतः_negotiation(काष्ठा cas *cp,
				       स्थिर काष्ठा ethtool_link_ksettings *ep)
अणु
	u16 ctl;
#अगर 1
	पूर्णांक lcntl;
	पूर्णांक changed = 0;
	पूर्णांक oldstate = cp->lstate;
	पूर्णांक link_was_not_करोwn = !(oldstate == link_करोwn);
#पूर्ण_अगर
	/* Setup link parameters */
	अगर (!ep)
		जाओ start_aneg;
	lcntl = cp->link_cntl;
	अगर (ep->base.स्वतःneg == AUTONEG_ENABLE) अणु
		cp->link_cntl = BMCR_ANENABLE;
	पूर्ण अन्यथा अणु
		u32 speed = ep->base.speed;
		cp->link_cntl = 0;
		अगर (speed == SPEED_100)
			cp->link_cntl |= BMCR_SPEED100;
		अन्यथा अगर (speed == SPEED_1000)
			cp->link_cntl |= CAS_BMCR_SPEED1000;
		अगर (ep->base.duplex == DUPLEX_FULL)
			cp->link_cntl |= BMCR_FULLDPLX;
	पूर्ण
#अगर 1
	changed = (lcntl != cp->link_cntl);
#पूर्ण_अगर
start_aneg:
	अगर (cp->lstate == link_up) अणु
		netdev_info(cp->dev, "PCS link down\n");
	पूर्ण अन्यथा अणु
		अगर (changed) अणु
			netdev_info(cp->dev, "link configuration changed\n");
		पूर्ण
	पूर्ण
	cp->lstate = link_करोwn;
	cp->link_transition = LINK_TRANSITION_LINK_DOWN;
	अगर (!cp->hw_running)
		वापस;
#अगर 1
	/*
	 * WTZ: If the old state was link_up, we turn off the carrier
	 * to replicate everything we करो अन्यथाwhere on a link-करोwn
	 * event when we were alपढ़ोy in a link-up state..
	 */
	अगर (oldstate == link_up)
		netअगर_carrier_off(cp->dev);
	अगर (changed  && link_was_not_करोwn) अणु
		/*
		 * WTZ: This branch will simply schedule a full reset after
		 * we explicitly changed link modes in an ioctl. See अगर this
		 * fixes the link-problems we were having क्रम क्रमced mode.
		 */
		atomic_inc(&cp->reset_task_pending);
		atomic_inc(&cp->reset_task_pending_all);
		schedule_work(&cp->reset_task);
		cp->समयr_ticks = 0;
		mod_समयr(&cp->link_समयr, jअगरfies + CAS_LINK_TIMEOUT);
		वापस;
	पूर्ण
#पूर्ण_अगर
	अगर (cp->phy_type & CAS_PHY_SERDES) अणु
		u32 val = पढ़ोl(cp->regs + REG_PCS_MII_CTRL);

		अगर (cp->link_cntl & BMCR_ANENABLE) अणु
			val |= (PCS_MII_RESTART_AUTONEG | PCS_MII_AUTONEG_EN);
			cp->lstate = link_aneg;
		पूर्ण अन्यथा अणु
			अगर (cp->link_cntl & BMCR_FULLDPLX)
				val |= PCS_MII_CTRL_DUPLEX;
			val &= ~PCS_MII_AUTONEG_EN;
			cp->lstate = link_क्रमce_ok;
		पूर्ण
		cp->link_transition = LINK_TRANSITION_LINK_CONFIG;
		ग_लिखोl(val, cp->regs + REG_PCS_MII_CTRL);

	पूर्ण अन्यथा अणु
		cas_mअगर_poll(cp, 0);
		ctl = cas_phy_पढ़ो(cp, MII_BMCR);
		ctl &= ~(BMCR_FULLDPLX | BMCR_SPEED100 |
			 CAS_BMCR_SPEED1000 | BMCR_ANENABLE);
		ctl |= cp->link_cntl;
		अगर (ctl & BMCR_ANENABLE) अणु
			ctl |= BMCR_ANRESTART;
			cp->lstate = link_aneg;
		पूर्ण अन्यथा अणु
			cp->lstate = link_क्रमce_ok;
		पूर्ण
		cp->link_transition = LINK_TRANSITION_LINK_CONFIG;
		cas_phy_ग_लिखो(cp, MII_BMCR, ctl);
		cas_mअगर_poll(cp, 1);
	पूर्ण

	cp->समयr_ticks = 0;
	mod_समयr(&cp->link_समयr, jअगरfies + CAS_LINK_TIMEOUT);
पूर्ण

/* Must be invoked under cp->lock. */
अटल पूर्णांक cas_reset_mii_phy(काष्ठा cas *cp)
अणु
	पूर्णांक limit = STOP_TRIES_PHY;
	u16 val;

	cas_phy_ग_लिखो(cp, MII_BMCR, BMCR_RESET);
	udelay(100);
	जबतक (--limit) अणु
		val = cas_phy_पढ़ो(cp, MII_BMCR);
		अगर ((val & BMCR_RESET) == 0)
			अवरोध;
		udelay(10);
	पूर्ण
	वापस limit <= 0;
पूर्ण

अटल व्योम cas_saturn_firmware_init(काष्ठा cas *cp)
अणु
	स्थिर काष्ठा firmware *fw;
	स्थिर अक्षर fw_name[] = "sun/cassini.bin";
	पूर्णांक err;

	अगर (PHY_NS_DP83065 != cp->phy_id)
		वापस;

	err = request_firmware(&fw, fw_name, &cp->pdev->dev);
	अगर (err) अणु
		pr_err("Failed to load firmware \"%s\"\n",
		       fw_name);
		वापस;
	पूर्ण
	अगर (fw->size < 2) अणु
		pr_err("bogus length %zu in \"%s\"\n",
		       fw->size, fw_name);
		जाओ out;
	पूर्ण
	cp->fw_load_addr= fw->data[1] << 8 | fw->data[0];
	cp->fw_size = fw->size - 2;
	cp->fw_data = vदो_स्मृति(cp->fw_size);
	अगर (!cp->fw_data)
		जाओ out;
	स_नकल(cp->fw_data, &fw->data[2], cp->fw_size);
out:
	release_firmware(fw);
पूर्ण

अटल व्योम cas_saturn_firmware_load(काष्ठा cas *cp)
अणु
	पूर्णांक i;

	अगर (!cp->fw_data)
		वापस;

	cas_phy_घातerकरोwn(cp);

	/* expanded memory access mode */
	cas_phy_ग_लिखो(cp, DP83065_MII_MEM, 0x0);

	/* poपूर्णांकer configuration क्रम new firmware */
	cas_phy_ग_लिखो(cp, DP83065_MII_REGE, 0x8ff9);
	cas_phy_ग_लिखो(cp, DP83065_MII_REGD, 0xbd);
	cas_phy_ग_लिखो(cp, DP83065_MII_REGE, 0x8ffa);
	cas_phy_ग_लिखो(cp, DP83065_MII_REGD, 0x82);
	cas_phy_ग_लिखो(cp, DP83065_MII_REGE, 0x8ffb);
	cas_phy_ग_लिखो(cp, DP83065_MII_REGD, 0x0);
	cas_phy_ग_लिखो(cp, DP83065_MII_REGE, 0x8ffc);
	cas_phy_ग_लिखो(cp, DP83065_MII_REGD, 0x39);

	/* करोwnload new firmware */
	cas_phy_ग_लिखो(cp, DP83065_MII_MEM, 0x1);
	cas_phy_ग_लिखो(cp, DP83065_MII_REGE, cp->fw_load_addr);
	क्रम (i = 0; i < cp->fw_size; i++)
		cas_phy_ग_लिखो(cp, DP83065_MII_REGD, cp->fw_data[i]);

	/* enable firmware */
	cas_phy_ग_लिखो(cp, DP83065_MII_REGE, 0x8ff8);
	cas_phy_ग_लिखो(cp, DP83065_MII_REGD, 0x1);
पूर्ण


/* phy initialization */
अटल व्योम cas_phy_init(काष्ठा cas *cp)
अणु
	u16 val;

	/* अगर we're in MII/GMII mode, set up phy */
	अगर (CAS_PHY_MII(cp->phy_type)) अणु
		ग_लिखोl(PCS_DATAPATH_MODE_MII,
		       cp->regs + REG_PCS_DATAPATH_MODE);

		cas_mअगर_poll(cp, 0);
		cas_reset_mii_phy(cp); /* take out of isolate mode */

		अगर (PHY_LUCENT_B0 == cp->phy_id) अणु
			/* workaround link up/करोwn issue with lucent */
			cas_phy_ग_लिखो(cp, LUCENT_MII_REG, 0x8000);
			cas_phy_ग_लिखो(cp, MII_BMCR, 0x00f1);
			cas_phy_ग_लिखो(cp, LUCENT_MII_REG, 0x0);

		पूर्ण अन्यथा अगर (PHY_BROADCOM_B0 == (cp->phy_id & 0xFFFFFFFC)) अणु
			/* workarounds क्रम broadcom phy */
			cas_phy_ग_लिखो(cp, BROADCOM_MII_REG8, 0x0C20);
			cas_phy_ग_लिखो(cp, BROADCOM_MII_REG7, 0x0012);
			cas_phy_ग_लिखो(cp, BROADCOM_MII_REG5, 0x1804);
			cas_phy_ग_लिखो(cp, BROADCOM_MII_REG7, 0x0013);
			cas_phy_ग_लिखो(cp, BROADCOM_MII_REG5, 0x1204);
			cas_phy_ग_लिखो(cp, BROADCOM_MII_REG7, 0x8006);
			cas_phy_ग_लिखो(cp, BROADCOM_MII_REG5, 0x0132);
			cas_phy_ग_लिखो(cp, BROADCOM_MII_REG7, 0x8006);
			cas_phy_ग_लिखो(cp, BROADCOM_MII_REG5, 0x0232);
			cas_phy_ग_लिखो(cp, BROADCOM_MII_REG7, 0x201F);
			cas_phy_ग_लिखो(cp, BROADCOM_MII_REG5, 0x0A20);

		पूर्ण अन्यथा अगर (PHY_BROADCOM_5411 == cp->phy_id) अणु
			val = cas_phy_पढ़ो(cp, BROADCOM_MII_REG4);
			val = cas_phy_पढ़ो(cp, BROADCOM_MII_REG4);
			अगर (val & 0x0080) अणु
				/* link workaround */
				cas_phy_ग_लिखो(cp, BROADCOM_MII_REG4,
					      val & ~0x0080);
			पूर्ण

		पूर्ण अन्यथा अगर (cp->cas_flags & CAS_FLAG_SATURN) अणु
			ग_लिखोl((cp->phy_type & CAS_PHY_MII_MDIO0) ?
			       SATURN_PCFG_FSI : 0x0,
			       cp->regs + REG_SATURN_PCFG);

			/* load firmware to address 10Mbps स्वतः-negotiation
			 * issue. NOTE: this will need to be changed अगर the
			 * शेष firmware माला_लो fixed.
			 */
			अगर (PHY_NS_DP83065 == cp->phy_id) अणु
				cas_saturn_firmware_load(cp);
			पूर्ण
			cas_phy_घातerup(cp);
		पूर्ण

		/* advertise capabilities */
		val = cas_phy_पढ़ो(cp, MII_BMCR);
		val &= ~BMCR_ANENABLE;
		cas_phy_ग_लिखो(cp, MII_BMCR, val);
		udelay(10);

		cas_phy_ग_लिखो(cp, MII_ADVERTISE,
			      cas_phy_पढ़ो(cp, MII_ADVERTISE) |
			      (ADVERTISE_10HALF | ADVERTISE_10FULL |
			       ADVERTISE_100HALF | ADVERTISE_100FULL |
			       CAS_ADVERTISE_PAUSE |
			       CAS_ADVERTISE_ASYM_PAUSE));

		अगर (cp->cas_flags & CAS_FLAG_1000MB_CAP) अणु
			/* make sure that we करोn't advertise half
			 * duplex to aव्योम a chip issue
			 */
			val  = cas_phy_पढ़ो(cp, CAS_MII_1000_CTRL);
			val &= ~CAS_ADVERTISE_1000HALF;
			val |= CAS_ADVERTISE_1000FULL;
			cas_phy_ग_लिखो(cp, CAS_MII_1000_CTRL, val);
		पूर्ण

	पूर्ण अन्यथा अणु
		/* reset pcs क्रम serdes */
		u32 val;
		पूर्णांक limit;

		ग_लिखोl(PCS_DATAPATH_MODE_SERDES,
		       cp->regs + REG_PCS_DATAPATH_MODE);

		/* enable serdes pins on saturn */
		अगर (cp->cas_flags & CAS_FLAG_SATURN)
			ग_लिखोl(0, cp->regs + REG_SATURN_PCFG);

		/* Reset PCS unit. */
		val = पढ़ोl(cp->regs + REG_PCS_MII_CTRL);
		val |= PCS_MII_RESET;
		ग_लिखोl(val, cp->regs + REG_PCS_MII_CTRL);

		limit = STOP_TRIES;
		जबतक (--limit > 0) अणु
			udelay(10);
			अगर ((पढ़ोl(cp->regs + REG_PCS_MII_CTRL) &
			     PCS_MII_RESET) == 0)
				अवरोध;
		पूर्ण
		अगर (limit <= 0)
			netdev_warn(cp->dev, "PCS reset bit would not clear [%08x]\n",
				    पढ़ोl(cp->regs + REG_PCS_STATE_MACHINE));

		/* Make sure PCS is disabled जबतक changing advertisement
		 * configuration.
		 */
		ग_लिखोl(0x0, cp->regs + REG_PCS_CFG);

		/* Advertise all capabilities except half-duplex. */
		val  = पढ़ोl(cp->regs + REG_PCS_MII_ADVERT);
		val &= ~PCS_MII_ADVERT_HD;
		val |= (PCS_MII_ADVERT_FD | PCS_MII_ADVERT_SYM_PAUSE |
			PCS_MII_ADVERT_ASYM_PAUSE);
		ग_लिखोl(val, cp->regs + REG_PCS_MII_ADVERT);

		/* enable PCS */
		ग_लिखोl(PCS_CFG_EN, cp->regs + REG_PCS_CFG);

		/* pcs workaround: enable sync detect */
		ग_लिखोl(PCS_SERDES_CTRL_SYNCD_EN,
		       cp->regs + REG_PCS_SERDES_CTRL);
	पूर्ण
पूर्ण


अटल पूर्णांक cas_pcs_link_check(काष्ठा cas *cp)
अणु
	u32 stat, state_machine;
	पूर्णांक retval = 0;

	/* The link status bit latches on zero, so you must
	 * पढ़ो it twice in such a हाल to see a transition
	 * to the link being up.
	 */
	stat = पढ़ोl(cp->regs + REG_PCS_MII_STATUS);
	अगर ((stat & PCS_MII_STATUS_LINK_STATUS) == 0)
		stat = पढ़ोl(cp->regs + REG_PCS_MII_STATUS);

	/* The remote-fault indication is only valid
	 * when स्वतःneg has completed.
	 */
	अगर ((stat & (PCS_MII_STATUS_AUTONEG_COMP |
		     PCS_MII_STATUS_REMOTE_FAULT)) ==
	    (PCS_MII_STATUS_AUTONEG_COMP | PCS_MII_STATUS_REMOTE_FAULT))
		netअगर_info(cp, link, cp->dev, "PCS RemoteFault\n");

	/* work around link detection issue by querying the PCS state
	 * machine directly.
	 */
	state_machine = पढ़ोl(cp->regs + REG_PCS_STATE_MACHINE);
	अगर ((state_machine & PCS_SM_LINK_STATE_MASK) != SM_LINK_STATE_UP) अणु
		stat &= ~PCS_MII_STATUS_LINK_STATUS;
	पूर्ण अन्यथा अगर (state_machine & PCS_SM_WORD_SYNC_STATE_MASK) अणु
		stat |= PCS_MII_STATUS_LINK_STATUS;
	पूर्ण

	अगर (stat & PCS_MII_STATUS_LINK_STATUS) अणु
		अगर (cp->lstate != link_up) अणु
			अगर (cp->खोलोed) अणु
				cp->lstate = link_up;
				cp->link_transition = LINK_TRANSITION_LINK_UP;

				cas_set_link_modes(cp);
				netअगर_carrier_on(cp->dev);
			पूर्ण
		पूर्ण
	पूर्ण अन्यथा अगर (cp->lstate == link_up) अणु
		cp->lstate = link_करोwn;
		अगर (link_transition_समयout != 0 &&
		    cp->link_transition != LINK_TRANSITION_REQUESTED_RESET &&
		    !cp->link_transition_jअगरfies_valid) अणु
			/*
			 * क्रमce a reset, as a workaround क्रम the
			 * link-failure problem. May want to move this to a
			 * poपूर्णांक a bit earlier in the sequence. If we had
			 * generated a reset a लघु समय ago, we'll रुको क्रम
			 * the link समयr to check the status until a
			 * समयr expires (link_transistion_jअगरfies_valid is
			 * true when the समयr is running.)  Instead of using
			 * a प्रणाली समयr, we just करो a check whenever the
			 * link समयr is running - this clears the flag after
			 * a suitable delay.
			 */
			retval = 1;
			cp->link_transition = LINK_TRANSITION_REQUESTED_RESET;
			cp->link_transition_jअगरfies = jअगरfies;
			cp->link_transition_jअगरfies_valid = 1;
		पूर्ण अन्यथा अणु
			cp->link_transition = LINK_TRANSITION_ON_FAILURE;
		पूर्ण
		netअगर_carrier_off(cp->dev);
		अगर (cp->खोलोed)
			netअगर_info(cp, link, cp->dev, "PCS link down\n");

		/* Cassini only: अगर you क्रमce a mode, there can be
		 * sync problems on link करोwn. to fix that, the following
		 * things need to be checked:
		 * 1) पढ़ो serialink state रेजिस्टर
		 * 2) पढ़ो pcs status रेजिस्टर to verअगरy link करोwn.
		 * 3) अगर link करोwn and serial link == 0x03, then you need
		 *    to global reset the chip.
		 */
		अगर ((cp->cas_flags & CAS_FLAG_REG_PLUS) == 0) अणु
			/* should check to see अगर we're in a क्रमced mode */
			stat = पढ़ोl(cp->regs + REG_PCS_SERDES_STATE);
			अगर (stat == 0x03)
				वापस 1;
		पूर्ण
	पूर्ण अन्यथा अगर (cp->lstate == link_करोwn) अणु
		अगर (link_transition_समयout != 0 &&
		    cp->link_transition != LINK_TRANSITION_REQUESTED_RESET &&
		    !cp->link_transition_jअगरfies_valid) अणु
			/* क्रमce a reset, as a workaround क्रम the
			 * link-failure problem.  May want to move
			 * this to a poपूर्णांक a bit earlier in the
			 * sequence.
			 */
			retval = 1;
			cp->link_transition = LINK_TRANSITION_REQUESTED_RESET;
			cp->link_transition_jअगरfies = jअगरfies;
			cp->link_transition_jअगरfies_valid = 1;
		पूर्ण अन्यथा अणु
			cp->link_transition = LINK_TRANSITION_STILL_FAILED;
		पूर्ण
	पूर्ण

	वापस retval;
पूर्ण

अटल पूर्णांक cas_pcs_पूर्णांकerrupt(काष्ठा net_device *dev,
			     काष्ठा cas *cp, u32 status)
अणु
	u32 stat = पढ़ोl(cp->regs + REG_PCS_INTR_STATUS);

	अगर ((stat & PCS_INTR_STATUS_LINK_CHANGE) == 0)
		वापस 0;
	वापस cas_pcs_link_check(cp);
पूर्ण

अटल पूर्णांक cas_txmac_पूर्णांकerrupt(काष्ठा net_device *dev,
			       काष्ठा cas *cp, u32 status)
अणु
	u32 txmac_stat = पढ़ोl(cp->regs + REG_MAC_TX_STATUS);

	अगर (!txmac_stat)
		वापस 0;

	netअगर_prपूर्णांकk(cp, पूर्णांकr, KERN_DEBUG, cp->dev,
		     "txmac interrupt, txmac_stat: 0x%x\n", txmac_stat);

	/* Defer समयr expiration is quite normal,
	 * करोn't even log the event.
	 */
	अगर ((txmac_stat & MAC_TX_DEFER_TIMER) &&
	    !(txmac_stat & ~MAC_TX_DEFER_TIMER))
		वापस 0;

	spin_lock(&cp->stat_lock[0]);
	अगर (txmac_stat & MAC_TX_UNDERRUN) अणु
		netdev_err(dev, "TX MAC xmit underrun\n");
		cp->net_stats[0].tx_fअगरo_errors++;
	पूर्ण

	अगर (txmac_stat & MAC_TX_MAX_PACKET_ERR) अणु
		netdev_err(dev, "TX MAC max packet size error\n");
		cp->net_stats[0].tx_errors++;
	पूर्ण

	/* The rest are all हालs of one of the 16-bit TX
	 * counters expiring.
	 */
	अगर (txmac_stat & MAC_TX_COLL_NORMAL)
		cp->net_stats[0].collisions += 0x10000;

	अगर (txmac_stat & MAC_TX_COLL_EXCESS) अणु
		cp->net_stats[0].tx_पातed_errors += 0x10000;
		cp->net_stats[0].collisions += 0x10000;
	पूर्ण

	अगर (txmac_stat & MAC_TX_COLL_LATE) अणु
		cp->net_stats[0].tx_पातed_errors += 0x10000;
		cp->net_stats[0].collisions += 0x10000;
	पूर्ण
	spin_unlock(&cp->stat_lock[0]);

	/* We करो not keep track of MAC_TX_COLL_FIRST and
	 * MAC_TX_PEAK_ATTEMPTS events.
	 */
	वापस 0;
पूर्ण

अटल व्योम cas_load_firmware(काष्ठा cas *cp, cas_hp_inst_t *firmware)
अणु
	cas_hp_inst_t *inst;
	u32 val;
	पूर्णांक i;

	i = 0;
	जबतक ((inst = firmware) && inst->note) अणु
		ग_लिखोl(i, cp->regs + REG_HP_INSTR_RAM_ADDR);

		val = CAS_BASE(HP_INSTR_RAM_HI_VAL, inst->val);
		val |= CAS_BASE(HP_INSTR_RAM_HI_MASK, inst->mask);
		ग_लिखोl(val, cp->regs + REG_HP_INSTR_RAM_DATA_HI);

		val = CAS_BASE(HP_INSTR_RAM_MID_OUTARG, inst->outarg >> 10);
		val |= CAS_BASE(HP_INSTR_RAM_MID_OUTOP, inst->outop);
		val |= CAS_BASE(HP_INSTR_RAM_MID_FNEXT, inst->fnext);
		val |= CAS_BASE(HP_INSTR_RAM_MID_FOFF, inst->foff);
		val |= CAS_BASE(HP_INSTR_RAM_MID_SNEXT, inst->snext);
		val |= CAS_BASE(HP_INSTR_RAM_MID_SOFF, inst->soff);
		val |= CAS_BASE(HP_INSTR_RAM_MID_OP, inst->op);
		ग_लिखोl(val, cp->regs + REG_HP_INSTR_RAM_DATA_MID);

		val = CAS_BASE(HP_INSTR_RAM_LOW_OUTMASK, inst->ouपंचांगask);
		val |= CAS_BASE(HP_INSTR_RAM_LOW_OUTSHIFT, inst->outshअगरt);
		val |= CAS_BASE(HP_INSTR_RAM_LOW_OUTEN, inst->outenab);
		val |= CAS_BASE(HP_INSTR_RAM_LOW_OUTARG, inst->outarg);
		ग_लिखोl(val, cp->regs + REG_HP_INSTR_RAM_DATA_LOW);
		++firmware;
		++i;
	पूर्ण
पूर्ण

अटल व्योम cas_init_rx_dma(काष्ठा cas *cp)
अणु
	u64 desc_dma = cp->block_dvma;
	u32 val;
	पूर्णांक i, size;

	/* rx मुक्त descriptors */
	val = CAS_BASE(RX_CFG_SWIVEL, RX_SWIVEL_OFF_VAL);
	val |= CAS_BASE(RX_CFG_DESC_RING, RX_DESC_RINGN_INDEX(0));
	val |= CAS_BASE(RX_CFG_COMP_RING, RX_COMP_RINGN_INDEX(0));
	अगर ((N_RX_DESC_RINGS > 1) &&
	    (cp->cas_flags & CAS_FLAG_REG_PLUS))  /* करो desc 2 */
		val |= CAS_BASE(RX_CFG_DESC_RING1, RX_DESC_RINGN_INDEX(1));
	ग_लिखोl(val, cp->regs + REG_RX_CFG);

	val = (अचिन्हित दीर्घ) cp->init_rxds[0] -
		(अचिन्हित दीर्घ) cp->init_block;
	ग_लिखोl((desc_dma + val) >> 32, cp->regs + REG_RX_DB_HI);
	ग_लिखोl((desc_dma + val) & 0xffffffff, cp->regs + REG_RX_DB_LOW);
	ग_लिखोl(RX_DESC_RINGN_SIZE(0) - 4, cp->regs + REG_RX_KICK);

	अगर (cp->cas_flags & CAS_FLAG_REG_PLUS) अणु
		/* rx desc 2 is क्रम IPSEC packets. however,
		 * we करोn't it that क्रम that purpose.
		 */
		val = (अचिन्हित दीर्घ) cp->init_rxds[1] -
			(अचिन्हित दीर्घ) cp->init_block;
		ग_लिखोl((desc_dma + val) >> 32, cp->regs + REG_PLUS_RX_DB1_HI);
		ग_लिखोl((desc_dma + val) & 0xffffffff, cp->regs +
		       REG_PLUS_RX_DB1_LOW);
		ग_लिखोl(RX_DESC_RINGN_SIZE(1) - 4, cp->regs +
		       REG_PLUS_RX_KICK1);
	पूर्ण

	/* rx completion रेजिस्टरs */
	val = (अचिन्हित दीर्घ) cp->init_rxcs[0] -
		(अचिन्हित दीर्घ) cp->init_block;
	ग_लिखोl((desc_dma + val) >> 32, cp->regs + REG_RX_CB_HI);
	ग_लिखोl((desc_dma + val) & 0xffffffff, cp->regs + REG_RX_CB_LOW);

	अगर (cp->cas_flags & CAS_FLAG_REG_PLUS) अणु
		/* rx comp 2-4 */
		क्रम (i = 1; i < MAX_RX_COMP_RINGS; i++) अणु
			val = (अचिन्हित दीर्घ) cp->init_rxcs[i] -
				(अचिन्हित दीर्घ) cp->init_block;
			ग_लिखोl((desc_dma + val) >> 32, cp->regs +
			       REG_PLUS_RX_CBN_HI(i));
			ग_लिखोl((desc_dma + val) & 0xffffffff, cp->regs +
			       REG_PLUS_RX_CBN_LOW(i));
		पूर्ण
	पूर्ण

	/* पढ़ो selective clear regs to prevent spurious पूर्णांकerrupts
	 * on reset because complete == kick.
	 * selective clear set up to prevent पूर्णांकerrupts on resets
	 */
	पढ़ोl(cp->regs + REG_INTR_STATUS_ALIAS);
	ग_लिखोl(INTR_RX_DONE | INTR_RX_BUF_UNAVAIL, cp->regs + REG_ALIAS_CLEAR);
	अगर (cp->cas_flags & CAS_FLAG_REG_PLUS) अणु
		क्रम (i = 1; i < N_RX_COMP_RINGS; i++)
			पढ़ोl(cp->regs + REG_PLUS_INTRN_STATUS_ALIAS(i));

		/* 2 is dअगरferent from 3 and 4 */
		अगर (N_RX_COMP_RINGS > 1)
			ग_लिखोl(INTR_RX_DONE_ALT | INTR_RX_BUF_UNAVAIL_1,
			       cp->regs + REG_PLUS_ALIASN_CLEAR(1));

		क्रम (i = 2; i < N_RX_COMP_RINGS; i++)
			ग_लिखोl(INTR_RX_DONE_ALT,
			       cp->regs + REG_PLUS_ALIASN_CLEAR(i));
	पूर्ण

	/* set up छोड़ो thresholds */
	val  = CAS_BASE(RX_PAUSE_THRESH_OFF,
			cp->rx_छोड़ो_off / RX_PAUSE_THRESH_QUANTUM);
	val |= CAS_BASE(RX_PAUSE_THRESH_ON,
			cp->rx_छोड़ो_on / RX_PAUSE_THRESH_QUANTUM);
	ग_लिखोl(val, cp->regs + REG_RX_PAUSE_THRESH);

	/* zero out dma reassembly buffers */
	क्रम (i = 0; i < 64; i++) अणु
		ग_लिखोl(i, cp->regs + REG_RX_TABLE_ADDR);
		ग_लिखोl(0x0, cp->regs + REG_RX_TABLE_DATA_LOW);
		ग_लिखोl(0x0, cp->regs + REG_RX_TABLE_DATA_MID);
		ग_लिखोl(0x0, cp->regs + REG_RX_TABLE_DATA_HI);
	पूर्ण

	/* make sure address रेजिस्टर is 0 क्रम normal operation */
	ग_लिखोl(0x0, cp->regs + REG_RX_CTRL_FIFO_ADDR);
	ग_लिखोl(0x0, cp->regs + REG_RX_IPP_FIFO_ADDR);

	/* पूर्णांकerrupt mitigation */
#अगर_घोषित USE_RX_BLANK
	val = CAS_BASE(RX_BLANK_INTR_TIME, RX_BLANK_INTR_TIME_VAL);
	val |= CAS_BASE(RX_BLANK_INTR_PKT, RX_BLANK_INTR_PKT_VAL);
	ग_लिखोl(val, cp->regs + REG_RX_BLANK);
#अन्यथा
	ग_लिखोl(0x0, cp->regs + REG_RX_BLANK);
#पूर्ण_अगर

	/* पूर्णांकerrupt generation as a function of low water marks क्रम
	 * मुक्त desc and completion entries. these are used to trigger
	 * housekeeping क्रम rx descs. we करोn't use the मुक्त पूर्णांकerrupt
	 * as it's not very useful
	 */
	/* val = CAS_BASE(RX_AE_THRESH_FREE, RX_AE_FREEN_VAL(0)); */
	val = CAS_BASE(RX_AE_THRESH_COMP, RX_AE_COMP_VAL);
	ग_लिखोl(val, cp->regs + REG_RX_AE_THRESH);
	अगर (cp->cas_flags & CAS_FLAG_REG_PLUS) अणु
		val = CAS_BASE(RX_AE1_THRESH_FREE, RX_AE_FREEN_VAL(1));
		ग_लिखोl(val, cp->regs + REG_PLUS_RX_AE1_THRESH);
	पूर्ण

	/* Ranकरोm early detect रेजिस्टरs. useful क्रम congestion aव्योमance.
	 * this should be tunable.
	 */
	ग_लिखोl(0x0, cp->regs + REG_RX_RED);

	/* receive page sizes. शेष == 2K (0x800) */
	val = 0;
	अगर (cp->page_size == 0x1000)
		val = 0x1;
	अन्यथा अगर (cp->page_size == 0x2000)
		val = 0x2;
	अन्यथा अगर (cp->page_size == 0x4000)
		val = 0x3;

	/* round mtu + offset. स्थिरrain to page size. */
	size = cp->dev->mtu + 64;
	अगर (size > cp->page_size)
		size = cp->page_size;

	अगर (size <= 0x400)
		i = 0x0;
	अन्यथा अगर (size <= 0x800)
		i = 0x1;
	अन्यथा अगर (size <= 0x1000)
		i = 0x2;
	अन्यथा
		i = 0x3;

	cp->mtu_stride = 1 << (i + 10);
	val  = CAS_BASE(RX_PAGE_SIZE, val);
	val |= CAS_BASE(RX_PAGE_SIZE_MTU_STRIDE, i);
	val |= CAS_BASE(RX_PAGE_SIZE_MTU_COUNT, cp->page_size >> (i + 10));
	val |= CAS_BASE(RX_PAGE_SIZE_MTU_OFF, 0x1);
	ग_लिखोl(val, cp->regs + REG_RX_PAGE_SIZE);

	/* enable the header parser अगर desired */
	अगर (CAS_HP_FIRMWARE == cas_prog_null)
		वापस;

	val = CAS_BASE(HP_CFG_NUM_CPU, CAS_NCPUS > 63 ? 0 : CAS_NCPUS);
	val |= HP_CFG_PARSE_EN | HP_CFG_SYN_INC_MASK;
	val |= CAS_BASE(HP_CFG_TCP_THRESH, HP_TCP_THRESH_VAL);
	ग_लिखोl(val, cp->regs + REG_HP_CFG);
पूर्ण

अटल अंतरभूत व्योम cas_rxc_init(काष्ठा cas_rx_comp *rxc)
अणु
	स_रखो(rxc, 0, माप(*rxc));
	rxc->word4 = cpu_to_le64(RX_COMP4_ZERO);
पूर्ण

/* NOTE: we use the ENC RX DESC ring क्रम spares. the rx_page[0,1]
 * flipping is रक्षित by the fact that the chip will not
 * hand back the same page index जबतक it's being processed.
 */
अटल अंतरभूत cas_page_t *cas_page_spare(काष्ठा cas *cp, स्थिर पूर्णांक index)
अणु
	cas_page_t *page = cp->rx_pages[1][index];
	cas_page_t *new;

	अगर (page_count(page->buffer) == 1)
		वापस page;

	new = cas_page_dequeue(cp);
	अगर (new) अणु
		spin_lock(&cp->rx_inuse_lock);
		list_add(&page->list, &cp->rx_inuse_list);
		spin_unlock(&cp->rx_inuse_lock);
	पूर्ण
	वापस new;
पूर्ण

/* this needs to be changed अगर we actually use the ENC RX DESC ring */
अटल cas_page_t *cas_page_swap(काष्ठा cas *cp, स्थिर पूर्णांक ring,
				 स्थिर पूर्णांक index)
अणु
	cas_page_t **page0 = cp->rx_pages[0];
	cas_page_t **page1 = cp->rx_pages[1];

	/* swap अगर buffer is in use */
	अगर (page_count(page0[index]->buffer) > 1) अणु
		cas_page_t *new = cas_page_spare(cp, index);
		अगर (new) अणु
			page1[index] = page0[index];
			page0[index] = new;
		पूर्ण
	पूर्ण
	RX_USED_SET(page0[index], 0);
	वापस page0[index];
पूर्ण

अटल व्योम cas_clean_rxds(काष्ठा cas *cp)
अणु
	/* only clean ring 0 as ring 1 is used क्रम spare buffers */
        काष्ठा cas_rx_desc *rxd = cp->init_rxds[0];
	पूर्णांक i, size;

	/* release all rx flows */
	क्रम (i = 0; i < N_RX_FLOWS; i++) अणु
		काष्ठा sk_buff *skb;
		जबतक ((skb = __skb_dequeue(&cp->rx_flows[i]))) अणु
			cas_skb_release(skb);
		पूर्ण
	पूर्ण

	/* initialize descriptors */
	size = RX_DESC_RINGN_SIZE(0);
	क्रम (i = 0; i < size; i++) अणु
		cas_page_t *page = cas_page_swap(cp, 0, i);
		rxd[i].buffer = cpu_to_le64(page->dma_addr);
		rxd[i].index  = cpu_to_le64(CAS_BASE(RX_INDEX_NUM, i) |
					    CAS_BASE(RX_INDEX_RING, 0));
	पूर्ण

	cp->rx_old[0]  = RX_DESC_RINGN_SIZE(0) - 4;
	cp->rx_last[0] = 0;
	cp->cas_flags &= ~CAS_FLAG_RXD_POST(0);
पूर्ण

अटल व्योम cas_clean_rxcs(काष्ठा cas *cp)
अणु
	पूर्णांक i, j;

	/* take ownership of rx comp descriptors */
	स_रखो(cp->rx_cur, 0, माप(*cp->rx_cur)*N_RX_COMP_RINGS);
	स_रखो(cp->rx_new, 0, माप(*cp->rx_new)*N_RX_COMP_RINGS);
	क्रम (i = 0; i < N_RX_COMP_RINGS; i++) अणु
		काष्ठा cas_rx_comp *rxc = cp->init_rxcs[i];
		क्रम (j = 0; j < RX_COMP_RINGN_SIZE(i); j++) अणु
			cas_rxc_init(rxc + j);
		पूर्ण
	पूर्ण
पूर्ण

#अगर 0
/* When we get a RX fअगरo overflow, the RX unit is probably hung
 * so we करो the following.
 *
 * If any part of the reset goes wrong, we वापस 1 and that causes the
 * whole chip to be reset.
 */
अटल पूर्णांक cas_rxmac_reset(काष्ठा cas *cp)
अणु
	काष्ठा net_device *dev = cp->dev;
	पूर्णांक limit;
	u32 val;

	/* First, reset MAC RX. */
	ग_लिखोl(cp->mac_rx_cfg & ~MAC_RX_CFG_EN, cp->regs + REG_MAC_RX_CFG);
	क्रम (limit = 0; limit < STOP_TRIES; limit++) अणु
		अगर (!(पढ़ोl(cp->regs + REG_MAC_RX_CFG) & MAC_RX_CFG_EN))
			अवरोध;
		udelay(10);
	पूर्ण
	अगर (limit == STOP_TRIES) अणु
		netdev_err(dev, "RX MAC will not disable, resetting whole chip\n");
		वापस 1;
	पूर्ण

	/* Second, disable RX DMA. */
	ग_लिखोl(0, cp->regs + REG_RX_CFG);
	क्रम (limit = 0; limit < STOP_TRIES; limit++) अणु
		अगर (!(पढ़ोl(cp->regs + REG_RX_CFG) & RX_CFG_DMA_EN))
			अवरोध;
		udelay(10);
	पूर्ण
	अगर (limit == STOP_TRIES) अणु
		netdev_err(dev, "RX DMA will not disable, resetting whole chip\n");
		वापस 1;
	पूर्ण

	mdelay(5);

	/* Execute RX reset command. */
	ग_लिखोl(SW_RESET_RX, cp->regs + REG_SW_RESET);
	क्रम (limit = 0; limit < STOP_TRIES; limit++) अणु
		अगर (!(पढ़ोl(cp->regs + REG_SW_RESET) & SW_RESET_RX))
			अवरोध;
		udelay(10);
	पूर्ण
	अगर (limit == STOP_TRIES) अणु
		netdev_err(dev, "RX reset command will not execute, resetting whole chip\n");
		वापस 1;
	पूर्ण

	/* reset driver rx state */
	cas_clean_rxds(cp);
	cas_clean_rxcs(cp);

	/* Now, reprogram the rest of RX unit. */
	cas_init_rx_dma(cp);

	/* re-enable */
	val = पढ़ोl(cp->regs + REG_RX_CFG);
	ग_लिखोl(val | RX_CFG_DMA_EN, cp->regs + REG_RX_CFG);
	ग_लिखोl(MAC_RX_FRAME_RECV, cp->regs + REG_MAC_RX_MASK);
	val = पढ़ोl(cp->regs + REG_MAC_RX_CFG);
	ग_लिखोl(val | MAC_RX_CFG_EN, cp->regs + REG_MAC_RX_CFG);
	वापस 0;
पूर्ण
#पूर्ण_अगर

अटल पूर्णांक cas_rxmac_पूर्णांकerrupt(काष्ठा net_device *dev, काष्ठा cas *cp,
			       u32 status)
अणु
	u32 stat = पढ़ोl(cp->regs + REG_MAC_RX_STATUS);

	अगर (!stat)
		वापस 0;

	netअगर_dbg(cp, पूर्णांकr, cp->dev, "rxmac interrupt, stat: 0x%x\n", stat);

	/* these are all rollovers */
	spin_lock(&cp->stat_lock[0]);
	अगर (stat & MAC_RX_ALIGN_ERR)
		cp->net_stats[0].rx_frame_errors += 0x10000;

	अगर (stat & MAC_RX_CRC_ERR)
		cp->net_stats[0].rx_crc_errors += 0x10000;

	अगर (stat & MAC_RX_LEN_ERR)
		cp->net_stats[0].rx_length_errors += 0x10000;

	अगर (stat & MAC_RX_OVERFLOW) अणु
		cp->net_stats[0].rx_over_errors++;
		cp->net_stats[0].rx_fअगरo_errors++;
	पूर्ण

	/* We करो not track MAC_RX_FRAME_COUNT and MAC_RX_VIOL_ERR
	 * events.
	 */
	spin_unlock(&cp->stat_lock[0]);
	वापस 0;
पूर्ण

अटल पूर्णांक cas_mac_पूर्णांकerrupt(काष्ठा net_device *dev, काष्ठा cas *cp,
			     u32 status)
अणु
	u32 stat = पढ़ोl(cp->regs + REG_MAC_CTRL_STATUS);

	अगर (!stat)
		वापस 0;

	netअगर_prपूर्णांकk(cp, पूर्णांकr, KERN_DEBUG, cp->dev,
		     "mac interrupt, stat: 0x%x\n", stat);

	/* This पूर्णांकerrupt is just क्रम छोड़ो frame and छोड़ो
	 * tracking.  It is useful क्रम diagnostics and debug
	 * but probably by शेष we will mask these events.
	 */
	अगर (stat & MAC_CTRL_PAUSE_STATE)
		cp->छोड़ो_entered++;

	अगर (stat & MAC_CTRL_PAUSE_RECEIVED)
		cp->छोड़ो_last_समय_recvd = (stat >> 16);

	वापस 0;
पूर्ण


/* Must be invoked under cp->lock. */
अटल अंतरभूत पूर्णांक cas_mdio_link_not_up(काष्ठा cas *cp)
अणु
	u16 val;

	चयन (cp->lstate) अणु
	हाल link_क्रमce_ret:
		netअगर_info(cp, link, cp->dev, "Autoneg failed again, keeping forced mode\n");
		cas_phy_ग_लिखो(cp, MII_BMCR, cp->link_fcntl);
		cp->समयr_ticks = 5;
		cp->lstate = link_क्रमce_ok;
		cp->link_transition = LINK_TRANSITION_LINK_CONFIG;
		अवरोध;

	हाल link_aneg:
		val = cas_phy_पढ़ो(cp, MII_BMCR);

		/* Try क्रमced modes. we try things in the following order:
		 * 1000 full -> 100 full/half -> 10 half
		 */
		val &= ~(BMCR_ANRESTART | BMCR_ANENABLE);
		val |= BMCR_FULLDPLX;
		val |= (cp->cas_flags & CAS_FLAG_1000MB_CAP) ?
			CAS_BMCR_SPEED1000 : BMCR_SPEED100;
		cas_phy_ग_लिखो(cp, MII_BMCR, val);
		cp->समयr_ticks = 5;
		cp->lstate = link_क्रमce_try;
		cp->link_transition = LINK_TRANSITION_LINK_CONFIG;
		अवरोध;

	हाल link_क्रमce_try:
		/* Downgrade from 1000 to 100 to 10 Mbps अगर necessary. */
		val = cas_phy_पढ़ो(cp, MII_BMCR);
		cp->समयr_ticks = 5;
		अगर (val & CAS_BMCR_SPEED1000) अणु /* gigabit */
			val &= ~CAS_BMCR_SPEED1000;
			val |= (BMCR_SPEED100 | BMCR_FULLDPLX);
			cas_phy_ग_लिखो(cp, MII_BMCR, val);
			अवरोध;
		पूर्ण

		अगर (val & BMCR_SPEED100) अणु
			अगर (val & BMCR_FULLDPLX) /* fd failed */
				val &= ~BMCR_FULLDPLX;
			अन्यथा अणु /* 100Mbps failed */
				val &= ~BMCR_SPEED100;
			पूर्ण
			cas_phy_ग_लिखो(cp, MII_BMCR, val);
			अवरोध;
		पूर्ण
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण
	वापस 0;
पूर्ण


/* must be invoked with cp->lock held */
अटल पूर्णांक cas_mii_link_check(काष्ठा cas *cp, स्थिर u16 bmsr)
अणु
	पूर्णांक restart;

	अगर (bmsr & BMSR_LSTATUS) अणु
		/* Ok, here we got a link. If we had it due to a क्रमced
		 * fallback, and we were configured क्रम स्वतःneg, we
		 * retry a लघु स्वतःneg pass. If you know your hub is
		 * broken, use ethtool ;)
		 */
		अगर ((cp->lstate == link_क्रमce_try) &&
		    (cp->link_cntl & BMCR_ANENABLE)) अणु
			cp->lstate = link_क्रमce_ret;
			cp->link_transition = LINK_TRANSITION_LINK_CONFIG;
			cas_mअगर_poll(cp, 0);
			cp->link_fcntl = cas_phy_पढ़ो(cp, MII_BMCR);
			cp->समयr_ticks = 5;
			अगर (cp->खोलोed)
				netअगर_info(cp, link, cp->dev,
					   "Got link after fallback, retrying autoneg once...\n");
			cas_phy_ग_लिखो(cp, MII_BMCR,
				      cp->link_fcntl | BMCR_ANENABLE |
				      BMCR_ANRESTART);
			cas_mअगर_poll(cp, 1);

		पूर्ण अन्यथा अगर (cp->lstate != link_up) अणु
			cp->lstate = link_up;
			cp->link_transition = LINK_TRANSITION_LINK_UP;

			अगर (cp->खोलोed) अणु
				cas_set_link_modes(cp);
				netअगर_carrier_on(cp->dev);
			पूर्ण
		पूर्ण
		वापस 0;
	पूर्ण

	/* link not up. अगर the link was previously up, we restart the
	 * whole process
	 */
	restart = 0;
	अगर (cp->lstate == link_up) अणु
		cp->lstate = link_करोwn;
		cp->link_transition = LINK_TRANSITION_LINK_DOWN;

		netअगर_carrier_off(cp->dev);
		अगर (cp->खोलोed)
			netअगर_info(cp, link, cp->dev, "Link down\n");
		restart = 1;

	पूर्ण अन्यथा अगर (++cp->समयr_ticks > 10)
		cas_mdio_link_not_up(cp);

	वापस restart;
पूर्ण

अटल पूर्णांक cas_mअगर_पूर्णांकerrupt(काष्ठा net_device *dev, काष्ठा cas *cp,
			     u32 status)
अणु
	u32 stat = पढ़ोl(cp->regs + REG_MIF_STATUS);
	u16 bmsr;

	/* check क्रम a link change */
	अगर (CAS_VAL(MIF_STATUS_POLL_STATUS, stat) == 0)
		वापस 0;

	bmsr = CAS_VAL(MIF_STATUS_POLL_DATA, stat);
	वापस cas_mii_link_check(cp, bmsr);
पूर्ण

अटल पूर्णांक cas_pci_पूर्णांकerrupt(काष्ठा net_device *dev, काष्ठा cas *cp,
			     u32 status)
अणु
	u32 stat = पढ़ोl(cp->regs + REG_PCI_ERR_STATUS);

	अगर (!stat)
		वापस 0;

	netdev_err(dev, "PCI error [%04x:%04x]",
		   stat, पढ़ोl(cp->regs + REG_BIM_DIAG));

	/* cassini+ has this reserved */
	अगर ((stat & PCI_ERR_BADACK) &&
	    ((cp->cas_flags & CAS_FLAG_REG_PLUS) == 0))
		pr_cont(" <No ACK64# during ABS64 cycle>");

	अगर (stat & PCI_ERR_DTRTO)
		pr_cont(" <Delayed transaction timeout>");
	अगर (stat & PCI_ERR_OTHER)
		pr_cont(" <other>");
	अगर (stat & PCI_ERR_BIM_DMA_WRITE)
		pr_cont(" <BIM DMA 0 write req>");
	अगर (stat & PCI_ERR_BIM_DMA_READ)
		pr_cont(" <BIM DMA 0 read req>");
	pr_cont("\n");

	अगर (stat & PCI_ERR_OTHER) अणु
		पूर्णांक pci_errs;

		/* Interrogate PCI config space क्रम the
		 * true cause.
		 */
		pci_errs = pci_status_get_and_clear_errors(cp->pdev);

		netdev_err(dev, "PCI status errors[%04x]\n", pci_errs);
		अगर (pci_errs & PCI_STATUS_PARITY)
			netdev_err(dev, "PCI parity error detected\n");
		अगर (pci_errs & PCI_STATUS_SIG_TARGET_ABORT)
			netdev_err(dev, "PCI target abort\n");
		अगर (pci_errs & PCI_STATUS_REC_TARGET_ABORT)
			netdev_err(dev, "PCI master acks target abort\n");
		अगर (pci_errs & PCI_STATUS_REC_MASTER_ABORT)
			netdev_err(dev, "PCI master abort\n");
		अगर (pci_errs & PCI_STATUS_SIG_SYSTEM_ERROR)
			netdev_err(dev, "PCI system error SERR#\n");
		अगर (pci_errs & PCI_STATUS_DETECTED_PARITY)
			netdev_err(dev, "PCI parity error\n");
	पूर्ण

	/* For all PCI errors, we should reset the chip. */
	वापस 1;
पूर्ण

/* All non-normal पूर्णांकerrupt conditions get serviced here.
 * Returns non-zero अगर we should just निकास the पूर्णांकerrupt
 * handler right now (ie. अगर we reset the card which invalidates
 * all of the other original irq status bits).
 */
अटल पूर्णांक cas_abnormal_irq(काष्ठा net_device *dev, काष्ठा cas *cp,
			    u32 status)
अणु
	अगर (status & INTR_RX_TAG_ERROR) अणु
		/* corrupt RX tag framing */
		netअगर_prपूर्णांकk(cp, rx_err, KERN_DEBUG, cp->dev,
			     "corrupt rx tag framing\n");
		spin_lock(&cp->stat_lock[0]);
		cp->net_stats[0].rx_errors++;
		spin_unlock(&cp->stat_lock[0]);
		जाओ करो_reset;
	पूर्ण

	अगर (status & INTR_RX_LEN_MISMATCH) अणु
		/* length mismatch. */
		netअगर_prपूर्णांकk(cp, rx_err, KERN_DEBUG, cp->dev,
			     "length mismatch for rx frame\n");
		spin_lock(&cp->stat_lock[0]);
		cp->net_stats[0].rx_errors++;
		spin_unlock(&cp->stat_lock[0]);
		जाओ करो_reset;
	पूर्ण

	अगर (status & INTR_PCS_STATUS) अणु
		अगर (cas_pcs_पूर्णांकerrupt(dev, cp, status))
			जाओ करो_reset;
	पूर्ण

	अगर (status & INTR_TX_MAC_STATUS) अणु
		अगर (cas_txmac_पूर्णांकerrupt(dev, cp, status))
			जाओ करो_reset;
	पूर्ण

	अगर (status & INTR_RX_MAC_STATUS) अणु
		अगर (cas_rxmac_पूर्णांकerrupt(dev, cp, status))
			जाओ करो_reset;
	पूर्ण

	अगर (status & INTR_MAC_CTRL_STATUS) अणु
		अगर (cas_mac_पूर्णांकerrupt(dev, cp, status))
			जाओ करो_reset;
	पूर्ण

	अगर (status & INTR_MIF_STATUS) अणु
		अगर (cas_mअगर_पूर्णांकerrupt(dev, cp, status))
			जाओ करो_reset;
	पूर्ण

	अगर (status & INTR_PCI_ERROR_STATUS) अणु
		अगर (cas_pci_पूर्णांकerrupt(dev, cp, status))
			जाओ करो_reset;
	पूर्ण
	वापस 0;

करो_reset:
#अगर 1
	atomic_inc(&cp->reset_task_pending);
	atomic_inc(&cp->reset_task_pending_all);
	netdev_err(dev, "reset called in cas_abnormal_irq [0x%x]\n", status);
	schedule_work(&cp->reset_task);
#अन्यथा
	atomic_set(&cp->reset_task_pending, CAS_RESET_ALL);
	netdev_err(dev, "reset called in cas_abnormal_irq\n");
	schedule_work(&cp->reset_task);
#पूर्ण_अगर
	वापस 1;
पूर्ण

/* NOTE: CAS_TABORT वापसs 1 or 2 so that it can be used when
 *       determining whether to करो a netअगर_stop/wakeup
 */
#घोषणा CAS_TABORT(x)      (((x)->cas_flags & CAS_FLAG_TARGET_ABORT) ? 2 : 1)
#घोषणा CAS_ROUND_PAGE(x)  (((x) + PAGE_SIZE - 1) & PAGE_MASK)
अटल अंतरभूत पूर्णांक cas_calc_tपात(काष्ठा cas *cp, स्थिर अचिन्हित दीर्घ addr,
				  स्थिर पूर्णांक len)
अणु
	अचिन्हित दीर्घ off = addr + len;

	अगर (CAS_TABORT(cp) == 1)
		वापस 0;
	अगर ((CAS_ROUND_PAGE(off) - off) > TX_TARGET_ABORT_LEN)
		वापस 0;
	वापस TX_TARGET_ABORT_LEN;
पूर्ण

अटल अंतरभूत व्योम cas_tx_ringN(काष्ठा cas *cp, पूर्णांक ring, पूर्णांक limit)
अणु
	काष्ठा cas_tx_desc *txds;
	काष्ठा sk_buff **skbs;
	काष्ठा net_device *dev = cp->dev;
	पूर्णांक entry, count;

	spin_lock(&cp->tx_lock[ring]);
	txds = cp->init_txds[ring];
	skbs = cp->tx_skbs[ring];
	entry = cp->tx_old[ring];

	count = TX_BUFF_COUNT(ring, entry, limit);
	जबतक (entry != limit) अणु
		काष्ठा sk_buff *skb = skbs[entry];
		dma_addr_t daddr;
		u32 dlen;
		पूर्णांक frag;

		अगर (!skb) अणु
			/* this should never occur */
			entry = TX_DESC_NEXT(ring, entry);
			जारी;
		पूर्ण

		/* however, we might get only a partial skb release. */
		count -= skb_shinfo(skb)->nr_frags +
			+ cp->tx_tiny_use[ring][entry].nbufs + 1;
		अगर (count < 0)
			अवरोध;

		netअगर_prपूर्णांकk(cp, tx_करोne, KERN_DEBUG, cp->dev,
			     "tx[%d] done, slot %d\n", ring, entry);

		skbs[entry] = शून्य;
		cp->tx_tiny_use[ring][entry].nbufs = 0;

		क्रम (frag = 0; frag <= skb_shinfo(skb)->nr_frags; frag++) अणु
			काष्ठा cas_tx_desc *txd = txds + entry;

			daddr = le64_to_cpu(txd->buffer);
			dlen = CAS_VAL(TX_DESC_BUFLEN,
				       le64_to_cpu(txd->control));
			dma_unmap_page(&cp->pdev->dev, daddr, dlen,
				       DMA_TO_DEVICE);
			entry = TX_DESC_NEXT(ring, entry);

			/* tiny buffer may follow */
			अगर (cp->tx_tiny_use[ring][entry].used) अणु
				cp->tx_tiny_use[ring][entry].used = 0;
				entry = TX_DESC_NEXT(ring, entry);
			पूर्ण
		पूर्ण

		spin_lock(&cp->stat_lock[ring]);
		cp->net_stats[ring].tx_packets++;
		cp->net_stats[ring].tx_bytes += skb->len;
		spin_unlock(&cp->stat_lock[ring]);
		dev_consume_skb_irq(skb);
	पूर्ण
	cp->tx_old[ring] = entry;

	/* this is wrong क्रम multiple tx rings. the net device needs
	 * multiple queues क्रम this to करो the right thing.  we रुको
	 * क्रम 2*packets to be available when using tiny buffers
	 */
	अगर (netअगर_queue_stopped(dev) &&
	    (TX_BUFFS_AVAIL(cp, ring) > CAS_TABORT(cp)*(MAX_SKB_FRAGS + 1)))
		netअगर_wake_queue(dev);
	spin_unlock(&cp->tx_lock[ring]);
पूर्ण

अटल व्योम cas_tx(काष्ठा net_device *dev, काष्ठा cas *cp,
		   u32 status)
अणु
        पूर्णांक limit, ring;
#अगर_घोषित USE_TX_COMPWB
	u64 compwb = le64_to_cpu(cp->init_block->tx_compwb);
#पूर्ण_अगर
	netअगर_prपूर्णांकk(cp, पूर्णांकr, KERN_DEBUG, cp->dev,
		     "tx interrupt, status: 0x%x, %llx\n",
		     status, (अचिन्हित दीर्घ दीर्घ)compwb);
	/* process all the rings */
	क्रम (ring = 0; ring < N_TX_RINGS; ring++) अणु
#अगर_घोषित USE_TX_COMPWB
		/* use the completion ग_लिखोback रेजिस्टरs */
		limit = (CAS_VAL(TX_COMPWB_MSB, compwb) << 8) |
			CAS_VAL(TX_COMPWB_LSB, compwb);
		compwb = TX_COMPWB_NEXT(compwb);
#अन्यथा
		limit = पढ़ोl(cp->regs + REG_TX_COMPN(ring));
#पूर्ण_अगर
		अगर (cp->tx_old[ring] != limit)
			cas_tx_ringN(cp, ring, limit);
	पूर्ण
पूर्ण


अटल पूर्णांक cas_rx_process_pkt(काष्ठा cas *cp, काष्ठा cas_rx_comp *rxc,
			      पूर्णांक entry, स्थिर u64 *words,
			      काष्ठा sk_buff **skbref)
अणु
	पूर्णांक dlen, hlen, len, i, alloclen;
	पूर्णांक off, swivel = RX_SWIVEL_OFF_VAL;
	काष्ठा cas_page *page;
	काष्ठा sk_buff *skb;
	व्योम *addr, *crcaddr;
	__sum16 csum;
	अक्षर *p;

	hlen = CAS_VAL(RX_COMP2_HDR_SIZE, words[1]);
	dlen = CAS_VAL(RX_COMP1_DATA_SIZE, words[0]);
	len  = hlen + dlen;

	अगर (RX_COPY_ALWAYS || (words[2] & RX_COMP3_SMALL_PKT))
		alloclen = len;
	अन्यथा
		alloclen = max(hlen, RX_COPY_MIN);

	skb = netdev_alloc_skb(cp->dev, alloclen + swivel + cp->crc_size);
	अगर (skb == शून्य)
		वापस -1;

	*skbref = skb;
	skb_reserve(skb, swivel);

	p = skb->data;
	addr = crcaddr = शून्य;
	अगर (hlen) अणु /* always copy header pages */
		i = CAS_VAL(RX_COMP2_HDR_INDEX, words[1]);
		page = cp->rx_pages[CAS_VAL(RX_INDEX_RING, i)][CAS_VAL(RX_INDEX_NUM, i)];
		off = CAS_VAL(RX_COMP2_HDR_OFF, words[1]) * 0x100 +
			swivel;

		i = hlen;
		अगर (!dlen) /* attach FCS */
			i += cp->crc_size;
		dma_sync_single_क्रम_cpu(&cp->pdev->dev, page->dma_addr + off,
					i, DMA_FROM_DEVICE);
		addr = cas_page_map(page->buffer);
		स_नकल(p, addr + off, i);
		dma_sync_single_क्रम_device(&cp->pdev->dev,
					   page->dma_addr + off, i,
					   DMA_FROM_DEVICE);
		cas_page_unmap(addr);
		RX_USED_ADD(page, 0x100);
		p += hlen;
		swivel = 0;
	पूर्ण


	अगर (alloclen < (hlen + dlen)) अणु
		skb_frag_t *frag = skb_shinfo(skb)->frags;

		/* normal or jumbo packets. we use frags */
		i = CAS_VAL(RX_COMP1_DATA_INDEX, words[0]);
		page = cp->rx_pages[CAS_VAL(RX_INDEX_RING, i)][CAS_VAL(RX_INDEX_NUM, i)];
		off = CAS_VAL(RX_COMP1_DATA_OFF, words[0]) + swivel;

		hlen = min(cp->page_size - off, dlen);
		अगर (hlen < 0) अणु
			netअगर_prपूर्णांकk(cp, rx_err, KERN_DEBUG, cp->dev,
				     "rx page overflow: %d\n", hlen);
			dev_kमुक्त_skb_irq(skb);
			वापस -1;
		पूर्ण
		i = hlen;
		अगर (i == dlen)  /* attach FCS */
			i += cp->crc_size;
		dma_sync_single_क्रम_cpu(&cp->pdev->dev, page->dma_addr + off,
					i, DMA_FROM_DEVICE);

		/* make sure we always copy a header */
		swivel = 0;
		अगर (p == (अक्षर *) skb->data) अणु /* not split */
			addr = cas_page_map(page->buffer);
			स_नकल(p, addr + off, RX_COPY_MIN);
			dma_sync_single_क्रम_device(&cp->pdev->dev,
						   page->dma_addr + off, i,
						   DMA_FROM_DEVICE);
			cas_page_unmap(addr);
			off += RX_COPY_MIN;
			swivel = RX_COPY_MIN;
			RX_USED_ADD(page, cp->mtu_stride);
		पूर्ण अन्यथा अणु
			RX_USED_ADD(page, hlen);
		पूर्ण
		skb_put(skb, alloclen);

		skb_shinfo(skb)->nr_frags++;
		skb->data_len += hlen - swivel;
		skb->truesize += hlen - swivel;
		skb->len      += hlen - swivel;

		__skb_frag_set_page(frag, page->buffer);
		__skb_frag_ref(frag);
		skb_frag_off_set(frag, off);
		skb_frag_size_set(frag, hlen - swivel);

		/* any more data? */
		अगर ((words[0] & RX_COMP1_SPLIT_PKT) && ((dlen -= hlen) > 0)) अणु
			hlen = dlen;
			off = 0;

			i = CAS_VAL(RX_COMP2_NEXT_INDEX, words[1]);
			page = cp->rx_pages[CAS_VAL(RX_INDEX_RING, i)][CAS_VAL(RX_INDEX_NUM, i)];
			dma_sync_single_क्रम_cpu(&cp->pdev->dev,
						page->dma_addr,
						hlen + cp->crc_size,
						DMA_FROM_DEVICE);
			dma_sync_single_क्रम_device(&cp->pdev->dev,
						   page->dma_addr,
						   hlen + cp->crc_size,
						   DMA_FROM_DEVICE);

			skb_shinfo(skb)->nr_frags++;
			skb->data_len += hlen;
			skb->len      += hlen;
			frag++;

			__skb_frag_set_page(frag, page->buffer);
			__skb_frag_ref(frag);
			skb_frag_off_set(frag, 0);
			skb_frag_size_set(frag, hlen);
			RX_USED_ADD(page, hlen + cp->crc_size);
		पूर्ण

		अगर (cp->crc_size) अणु
			addr = cas_page_map(page->buffer);
			crcaddr  = addr + off + hlen;
		पूर्ण

	पूर्ण अन्यथा अणु
		/* copying packet */
		अगर (!dlen)
			जाओ end_copy_pkt;

		i = CAS_VAL(RX_COMP1_DATA_INDEX, words[0]);
		page = cp->rx_pages[CAS_VAL(RX_INDEX_RING, i)][CAS_VAL(RX_INDEX_NUM, i)];
		off = CAS_VAL(RX_COMP1_DATA_OFF, words[0]) + swivel;
		hlen = min(cp->page_size - off, dlen);
		अगर (hlen < 0) अणु
			netअगर_prपूर्णांकk(cp, rx_err, KERN_DEBUG, cp->dev,
				     "rx page overflow: %d\n", hlen);
			dev_kमुक्त_skb_irq(skb);
			वापस -1;
		पूर्ण
		i = hlen;
		अगर (i == dlen) /* attach FCS */
			i += cp->crc_size;
		dma_sync_single_क्रम_cpu(&cp->pdev->dev, page->dma_addr + off,
					i, DMA_FROM_DEVICE);
		addr = cas_page_map(page->buffer);
		स_नकल(p, addr + off, i);
		dma_sync_single_क्रम_device(&cp->pdev->dev,
					   page->dma_addr + off, i,
					   DMA_FROM_DEVICE);
		cas_page_unmap(addr);
		अगर (p == (अक्षर *) skb->data) /* not split */
			RX_USED_ADD(page, cp->mtu_stride);
		अन्यथा
			RX_USED_ADD(page, i);

		/* any more data? */
		अगर ((words[0] & RX_COMP1_SPLIT_PKT) && ((dlen -= hlen) > 0)) अणु
			p += hlen;
			i = CAS_VAL(RX_COMP2_NEXT_INDEX, words[1]);
			page = cp->rx_pages[CAS_VAL(RX_INDEX_RING, i)][CAS_VAL(RX_INDEX_NUM, i)];
			dma_sync_single_क्रम_cpu(&cp->pdev->dev,
						page->dma_addr,
						dlen + cp->crc_size,
						DMA_FROM_DEVICE);
			addr = cas_page_map(page->buffer);
			स_नकल(p, addr, dlen + cp->crc_size);
			dma_sync_single_क्रम_device(&cp->pdev->dev,
						   page->dma_addr,
						   dlen + cp->crc_size,
						   DMA_FROM_DEVICE);
			cas_page_unmap(addr);
			RX_USED_ADD(page, dlen + cp->crc_size);
		पूर्ण
end_copy_pkt:
		अगर (cp->crc_size) अणु
			addr    = शून्य;
			crcaddr = skb->data + alloclen;
		पूर्ण
		skb_put(skb, alloclen);
	पूर्ण

	csum = (__क्रमce __sum16)htons(CAS_VAL(RX_COMP4_TCP_CSUM, words[3]));
	अगर (cp->crc_size) अणु
		/* checksum includes FCS. strip it out. */
		csum = csum_fold(csum_partial(crcaddr, cp->crc_size,
					      csum_unfold(csum)));
		अगर (addr)
			cas_page_unmap(addr);
	पूर्ण
	skb->protocol = eth_type_trans(skb, cp->dev);
	अगर (skb->protocol == htons(ETH_P_IP)) अणु
		skb->csum = csum_unfold(~csum);
		skb->ip_summed = CHECKSUM_COMPLETE;
	पूर्ण अन्यथा
		skb_checksum_none_निश्चित(skb);
	वापस len;
पूर्ण


/* we can handle up to 64 rx flows at a समय. we करो the same thing
 * as nonreassm except that we batch up the buffers.
 * NOTE: we currently just treat each flow as a bunch of packets that
 *       we pass up. a better way would be to coalesce the packets
 *       पूर्णांकo a jumbo packet. to करो that, we need to करो the following:
 *       1) the first packet will have a clean split between header and
 *          data. save both.
 *       2) each समय the next flow packet comes in, extend the
 *          data length and merge the checksums.
 *       3) on flow release, fix up the header.
 *       4) make sure the higher layer करोesn't care.
 * because packets get coalesced, we shouldn't run पूर्णांकo fragment count
 * issues.
 */
अटल अंतरभूत व्योम cas_rx_flow_pkt(काष्ठा cas *cp, स्थिर u64 *words,
				   काष्ठा sk_buff *skb)
अणु
	पूर्णांक flowid = CAS_VAL(RX_COMP3_FLOWID, words[2]) & (N_RX_FLOWS - 1);
	काष्ठा sk_buff_head *flow = &cp->rx_flows[flowid];

	/* this is रक्षित at a higher layer, so no need to
	 * करो any additional locking here. stick the buffer
	 * at the end.
	 */
	__skb_queue_tail(flow, skb);
	अगर (words[0] & RX_COMP1_RELEASE_FLOW) अणु
		जबतक ((skb = __skb_dequeue(flow))) अणु
			cas_skb_release(skb);
		पूर्ण
	पूर्ण
पूर्ण

/* put rx descriptor back on ring. अगर a buffer is in use by a higher
 * layer, this will need to put in a replacement.
 */
अटल व्योम cas_post_page(काष्ठा cas *cp, स्थिर पूर्णांक ring, स्थिर पूर्णांक index)
अणु
	cas_page_t *new;
	पूर्णांक entry;

	entry = cp->rx_old[ring];

	new = cas_page_swap(cp, ring, index);
	cp->init_rxds[ring][entry].buffer = cpu_to_le64(new->dma_addr);
	cp->init_rxds[ring][entry].index  =
		cpu_to_le64(CAS_BASE(RX_INDEX_NUM, index) |
			    CAS_BASE(RX_INDEX_RING, ring));

	entry = RX_DESC_ENTRY(ring, entry + 1);
	cp->rx_old[ring] = entry;

	अगर (entry % 4)
		वापस;

	अगर (ring == 0)
		ग_लिखोl(entry, cp->regs + REG_RX_KICK);
	अन्यथा अगर ((N_RX_DESC_RINGS > 1) &&
		 (cp->cas_flags & CAS_FLAG_REG_PLUS))
		ग_लिखोl(entry, cp->regs + REG_PLUS_RX_KICK1);
पूर्ण


/* only when things are bad */
अटल पूर्णांक cas_post_rxds_ringN(काष्ठा cas *cp, पूर्णांक ring, पूर्णांक num)
अणु
	अचिन्हित पूर्णांक entry, last, count, released;
	पूर्णांक cluster;
	cas_page_t **page = cp->rx_pages[ring];

	entry = cp->rx_old[ring];

	netअगर_prपूर्णांकk(cp, पूर्णांकr, KERN_DEBUG, cp->dev,
		     "rxd[%d] interrupt, done: %d\n", ring, entry);

	cluster = -1;
	count = entry & 0x3;
	last = RX_DESC_ENTRY(ring, num ? entry + num - 4: entry - 4);
	released = 0;
	जबतक (entry != last) अणु
		/* make a new buffer अगर it's still in use */
		अगर (page_count(page[entry]->buffer) > 1) अणु
			cas_page_t *new = cas_page_dequeue(cp);
			अगर (!new) अणु
				/* let the समयr know that we need to
				 * करो this again
				 */
				cp->cas_flags |= CAS_FLAG_RXD_POST(ring);
				अगर (!समयr_pending(&cp->link_समयr))
					mod_समयr(&cp->link_समयr, jअगरfies +
						  CAS_LINK_FAST_TIMEOUT);
				cp->rx_old[ring]  = entry;
				cp->rx_last[ring] = num ? num - released : 0;
				वापस -ENOMEM;
			पूर्ण
			spin_lock(&cp->rx_inuse_lock);
			list_add(&page[entry]->list, &cp->rx_inuse_list);
			spin_unlock(&cp->rx_inuse_lock);
			cp->init_rxds[ring][entry].buffer =
				cpu_to_le64(new->dma_addr);
			page[entry] = new;

		पूर्ण

		अगर (++count == 4) अणु
			cluster = entry;
			count = 0;
		पूर्ण
		released++;
		entry = RX_DESC_ENTRY(ring, entry + 1);
	पूर्ण
	cp->rx_old[ring] = entry;

	अगर (cluster < 0)
		वापस 0;

	अगर (ring == 0)
		ग_लिखोl(cluster, cp->regs + REG_RX_KICK);
	अन्यथा अगर ((N_RX_DESC_RINGS > 1) &&
		 (cp->cas_flags & CAS_FLAG_REG_PLUS))
		ग_लिखोl(cluster, cp->regs + REG_PLUS_RX_KICK1);
	वापस 0;
पूर्ण


/* process a completion ring. packets are set up in three basic ways:
 * small packets: should be copied header + data in single buffer.
 * large packets: header and data in a single buffer.
 * split packets: header in a separate buffer from data.
 *                data may be in multiple pages. data may be > 256
 *                bytes but in a single page.
 *
 * NOTE: RX page posting is करोne in this routine as well. जबतक there's
 *       the capability of using multiple RX completion rings, it isn't
 *       really worthजबतक due to the fact that the page posting will
 *       क्रमce serialization on the single descriptor ring.
 */
अटल पूर्णांक cas_rx_ringN(काष्ठा cas *cp, पूर्णांक ring, पूर्णांक budget)
अणु
	काष्ठा cas_rx_comp *rxcs = cp->init_rxcs[ring];
	पूर्णांक entry, drops;
	पूर्णांक npackets = 0;

	netअगर_prपूर्णांकk(cp, पूर्णांकr, KERN_DEBUG, cp->dev,
		     "rx[%d] interrupt, done: %d/%d\n",
		     ring,
		     पढ़ोl(cp->regs + REG_RX_COMP_HEAD), cp->rx_new[ring]);

	entry = cp->rx_new[ring];
	drops = 0;
	जबतक (1) अणु
		काष्ठा cas_rx_comp *rxc = rxcs + entry;
		काष्ठा sk_buff *skb;
		पूर्णांक type, len;
		u64 words[4];
		पूर्णांक i, dring;

		words[0] = le64_to_cpu(rxc->word1);
		words[1] = le64_to_cpu(rxc->word2);
		words[2] = le64_to_cpu(rxc->word3);
		words[3] = le64_to_cpu(rxc->word4);

		/* करोn't touch अगर still owned by hw */
		type = CAS_VAL(RX_COMP1_TYPE, words[0]);
		अगर (type == 0)
			अवरोध;

		/* hw hasn't cleared the zero bit yet */
		अगर (words[3] & RX_COMP4_ZERO) अणु
			अवरोध;
		पूर्ण

		/* get info on the packet */
		अगर (words[3] & (RX_COMP4_LEN_MISMATCH | RX_COMP4_BAD)) अणु
			spin_lock(&cp->stat_lock[ring]);
			cp->net_stats[ring].rx_errors++;
			अगर (words[3] & RX_COMP4_LEN_MISMATCH)
				cp->net_stats[ring].rx_length_errors++;
			अगर (words[3] & RX_COMP4_BAD)
				cp->net_stats[ring].rx_crc_errors++;
			spin_unlock(&cp->stat_lock[ring]);

			/* We'll just वापस it to Cassini. */
		drop_it:
			spin_lock(&cp->stat_lock[ring]);
			++cp->net_stats[ring].rx_dropped;
			spin_unlock(&cp->stat_lock[ring]);
			जाओ next;
		पूर्ण

		len = cas_rx_process_pkt(cp, rxc, entry, words, &skb);
		अगर (len < 0) अणु
			++drops;
			जाओ drop_it;
		पूर्ण

		/* see अगर it's a flow re-assembly or not. the driver
		 * itself handles release back up.
		 */
		अगर (RX_DONT_BATCH || (type == 0x2)) अणु
			/* non-reassm: these always get released */
			cas_skb_release(skb);
		पूर्ण अन्यथा अणु
			cas_rx_flow_pkt(cp, words, skb);
		पूर्ण

		spin_lock(&cp->stat_lock[ring]);
		cp->net_stats[ring].rx_packets++;
		cp->net_stats[ring].rx_bytes += len;
		spin_unlock(&cp->stat_lock[ring]);

	next:
		npackets++;

		/* should it be released? */
		अगर (words[0] & RX_COMP1_RELEASE_HDR) अणु
			i = CAS_VAL(RX_COMP2_HDR_INDEX, words[1]);
			dring = CAS_VAL(RX_INDEX_RING, i);
			i = CAS_VAL(RX_INDEX_NUM, i);
			cas_post_page(cp, dring, i);
		पूर्ण

		अगर (words[0] & RX_COMP1_RELEASE_DATA) अणु
			i = CAS_VAL(RX_COMP1_DATA_INDEX, words[0]);
			dring = CAS_VAL(RX_INDEX_RING, i);
			i = CAS_VAL(RX_INDEX_NUM, i);
			cas_post_page(cp, dring, i);
		पूर्ण

		अगर (words[0] & RX_COMP1_RELEASE_NEXT) अणु
			i = CAS_VAL(RX_COMP2_NEXT_INDEX, words[1]);
			dring = CAS_VAL(RX_INDEX_RING, i);
			i = CAS_VAL(RX_INDEX_NUM, i);
			cas_post_page(cp, dring, i);
		पूर्ण

		/* skip to the next entry */
		entry = RX_COMP_ENTRY(ring, entry + 1 +
				      CAS_VAL(RX_COMP1_SKIP, words[0]));
#अगर_घोषित USE_NAPI
		अगर (budget && (npackets >= budget))
			अवरोध;
#पूर्ण_अगर
	पूर्ण
	cp->rx_new[ring] = entry;

	अगर (drops)
		netdev_info(cp->dev, "Memory squeeze, deferring packet\n");
	वापस npackets;
पूर्ण


/* put completion entries back on the ring */
अटल व्योम cas_post_rxcs_ringN(काष्ठा net_device *dev,
				काष्ठा cas *cp, पूर्णांक ring)
अणु
	काष्ठा cas_rx_comp *rxc = cp->init_rxcs[ring];
	पूर्णांक last, entry;

	last = cp->rx_cur[ring];
	entry = cp->rx_new[ring];
	netअगर_prपूर्णांकk(cp, पूर्णांकr, KERN_DEBUG, dev,
		     "rxc[%d] interrupt, done: %d/%d\n",
		     ring, पढ़ोl(cp->regs + REG_RX_COMP_HEAD), entry);

	/* zero and re-mark descriptors */
	जबतक (last != entry) अणु
		cas_rxc_init(rxc + last);
		last = RX_COMP_ENTRY(ring, last + 1);
	पूर्ण
	cp->rx_cur[ring] = last;

	अगर (ring == 0)
		ग_लिखोl(last, cp->regs + REG_RX_COMP_TAIL);
	अन्यथा अगर (cp->cas_flags & CAS_FLAG_REG_PLUS)
		ग_लिखोl(last, cp->regs + REG_PLUS_RX_COMPN_TAIL(ring));
पूर्ण



/* cassini can use all four PCI पूर्णांकerrupts क्रम the completion ring.
 * rings 3 and 4 are identical
 */
#अगर defined(USE_PCI_INTC) || defined(USE_PCI_INTD)
अटल अंतरभूत व्योम cas_handle_irqN(काष्ठा net_device *dev,
				   काष्ठा cas *cp, स्थिर u32 status,
				   स्थिर पूर्णांक ring)
अणु
	अगर (status & (INTR_RX_COMP_FULL_ALT | INTR_RX_COMP_AF_ALT))
		cas_post_rxcs_ringN(dev, cp, ring);
पूर्ण

अटल irqवापस_t cas_पूर्णांकerruptN(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा net_device *dev = dev_id;
	काष्ठा cas *cp = netdev_priv(dev);
	अचिन्हित दीर्घ flags;
	पूर्णांक ring = (irq == cp->pci_irq_INTC) ? 2 : 3;
	u32 status = पढ़ोl(cp->regs + REG_PLUS_INTRN_STATUS(ring));

	/* check क्रम shared irq */
	अगर (status == 0)
		वापस IRQ_NONE;

	spin_lock_irqsave(&cp->lock, flags);
	अगर (status & INTR_RX_DONE_ALT) अणु /* handle rx separately */
#अगर_घोषित USE_NAPI
		cas_mask_पूर्णांकr(cp);
		napi_schedule(&cp->napi);
#अन्यथा
		cas_rx_ringN(cp, ring, 0);
#पूर्ण_अगर
		status &= ~INTR_RX_DONE_ALT;
	पूर्ण

	अगर (status)
		cas_handle_irqN(dev, cp, status, ring);
	spin_unlock_irqrestore(&cp->lock, flags);
	वापस IRQ_HANDLED;
पूर्ण
#पूर्ण_अगर

#अगर_घोषित USE_PCI_INTB
/* everything but rx packets */
अटल अंतरभूत व्योम cas_handle_irq1(काष्ठा cas *cp, स्थिर u32 status)
अणु
	अगर (status & INTR_RX_BUF_UNAVAIL_1) अणु
		/* Frame arrived, no मुक्त RX buffers available.
		 * NOTE: we can get this on a link transition. */
		cas_post_rxds_ringN(cp, 1, 0);
		spin_lock(&cp->stat_lock[1]);
		cp->net_stats[1].rx_dropped++;
		spin_unlock(&cp->stat_lock[1]);
	पूर्ण

	अगर (status & INTR_RX_BUF_AE_1)
		cas_post_rxds_ringN(cp, 1, RX_DESC_RINGN_SIZE(1) -
				    RX_AE_FREEN_VAL(1));

	अगर (status & (INTR_RX_COMP_AF | INTR_RX_COMP_FULL))
		cas_post_rxcs_ringN(cp, 1);
पूर्ण

/* ring 2 handles a few more events than 3 and 4 */
अटल irqवापस_t cas_पूर्णांकerrupt1(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा net_device *dev = dev_id;
	काष्ठा cas *cp = netdev_priv(dev);
	अचिन्हित दीर्घ flags;
	u32 status = पढ़ोl(cp->regs + REG_PLUS_INTRN_STATUS(1));

	/* check क्रम shared पूर्णांकerrupt */
	अगर (status == 0)
		वापस IRQ_NONE;

	spin_lock_irqsave(&cp->lock, flags);
	अगर (status & INTR_RX_DONE_ALT) अणु /* handle rx separately */
#अगर_घोषित USE_NAPI
		cas_mask_पूर्णांकr(cp);
		napi_schedule(&cp->napi);
#अन्यथा
		cas_rx_ringN(cp, 1, 0);
#पूर्ण_अगर
		status &= ~INTR_RX_DONE_ALT;
	पूर्ण
	अगर (status)
		cas_handle_irq1(cp, status);
	spin_unlock_irqrestore(&cp->lock, flags);
	वापस IRQ_HANDLED;
पूर्ण
#पूर्ण_अगर

अटल अंतरभूत व्योम cas_handle_irq(काष्ठा net_device *dev,
				  काष्ठा cas *cp, स्थिर u32 status)
अणु
	/* housekeeping पूर्णांकerrupts */
	अगर (status & INTR_ERROR_MASK)
		cas_abnormal_irq(dev, cp, status);

	अगर (status & INTR_RX_BUF_UNAVAIL) अणु
		/* Frame arrived, no मुक्त RX buffers available.
		 * NOTE: we can get this on a link transition.
		 */
		cas_post_rxds_ringN(cp, 0, 0);
		spin_lock(&cp->stat_lock[0]);
		cp->net_stats[0].rx_dropped++;
		spin_unlock(&cp->stat_lock[0]);
	पूर्ण अन्यथा अगर (status & INTR_RX_BUF_AE) अणु
		cas_post_rxds_ringN(cp, 0, RX_DESC_RINGN_SIZE(0) -
				    RX_AE_FREEN_VAL(0));
	पूर्ण

	अगर (status & (INTR_RX_COMP_AF | INTR_RX_COMP_FULL))
		cas_post_rxcs_ringN(dev, cp, 0);
पूर्ण

अटल irqवापस_t cas_पूर्णांकerrupt(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा net_device *dev = dev_id;
	काष्ठा cas *cp = netdev_priv(dev);
	अचिन्हित दीर्घ flags;
	u32 status = पढ़ोl(cp->regs + REG_INTR_STATUS);

	अगर (status == 0)
		वापस IRQ_NONE;

	spin_lock_irqsave(&cp->lock, flags);
	अगर (status & (INTR_TX_ALL | INTR_TX_INTME)) अणु
		cas_tx(dev, cp, status);
		status &= ~(INTR_TX_ALL | INTR_TX_INTME);
	पूर्ण

	अगर (status & INTR_RX_DONE) अणु
#अगर_घोषित USE_NAPI
		cas_mask_पूर्णांकr(cp);
		napi_schedule(&cp->napi);
#अन्यथा
		cas_rx_ringN(cp, 0, 0);
#पूर्ण_अगर
		status &= ~INTR_RX_DONE;
	पूर्ण

	अगर (status)
		cas_handle_irq(dev, cp, status);
	spin_unlock_irqrestore(&cp->lock, flags);
	वापस IRQ_HANDLED;
पूर्ण


#अगर_घोषित USE_NAPI
अटल पूर्णांक cas_poll(काष्ठा napi_काष्ठा *napi, पूर्णांक budget)
अणु
	काष्ठा cas *cp = container_of(napi, काष्ठा cas, napi);
	काष्ठा net_device *dev = cp->dev;
	पूर्णांक i, enable_पूर्णांकr, credits;
	u32 status = पढ़ोl(cp->regs + REG_INTR_STATUS);
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&cp->lock, flags);
	cas_tx(dev, cp, status);
	spin_unlock_irqrestore(&cp->lock, flags);

	/* NAPI rx packets. we spपढ़ो the credits across all of the
	 * rxc rings
	 *
	 * to make sure we're fair with the work we loop through each
	 * ring N_RX_COMP_RING बार with a request of
	 * budget / N_RX_COMP_RINGS
	 */
	enable_पूर्णांकr = 1;
	credits = 0;
	क्रम (i = 0; i < N_RX_COMP_RINGS; i++) अणु
		पूर्णांक j;
		क्रम (j = 0; j < N_RX_COMP_RINGS; j++) अणु
			credits += cas_rx_ringN(cp, j, budget / N_RX_COMP_RINGS);
			अगर (credits >= budget) अणु
				enable_पूर्णांकr = 0;
				जाओ rx_comp;
			पूर्ण
		पूर्ण
	पूर्ण

rx_comp:
	/* final rx completion */
	spin_lock_irqsave(&cp->lock, flags);
	अगर (status)
		cas_handle_irq(dev, cp, status);

#अगर_घोषित USE_PCI_INTB
	अगर (N_RX_COMP_RINGS > 1) अणु
		status = पढ़ोl(cp->regs + REG_PLUS_INTRN_STATUS(1));
		अगर (status)
			cas_handle_irq1(dev, cp, status);
	पूर्ण
#पूर्ण_अगर

#अगर_घोषित USE_PCI_INTC
	अगर (N_RX_COMP_RINGS > 2) अणु
		status = पढ़ोl(cp->regs + REG_PLUS_INTRN_STATUS(2));
		अगर (status)
			cas_handle_irqN(dev, cp, status, 2);
	पूर्ण
#पूर्ण_अगर

#अगर_घोषित USE_PCI_INTD
	अगर (N_RX_COMP_RINGS > 3) अणु
		status = पढ़ोl(cp->regs + REG_PLUS_INTRN_STATUS(3));
		अगर (status)
			cas_handle_irqN(dev, cp, status, 3);
	पूर्ण
#पूर्ण_अगर
	spin_unlock_irqrestore(&cp->lock, flags);
	अगर (enable_पूर्णांकr) अणु
		napi_complete(napi);
		cas_unmask_पूर्णांकr(cp);
	पूर्ण
	वापस credits;
पूर्ण
#पूर्ण_अगर

#अगर_घोषित CONFIG_NET_POLL_CONTROLLER
अटल व्योम cas_netpoll(काष्ठा net_device *dev)
अणु
	काष्ठा cas *cp = netdev_priv(dev);

	cas_disable_irq(cp, 0);
	cas_पूर्णांकerrupt(cp->pdev->irq, dev);
	cas_enable_irq(cp, 0);

#अगर_घोषित USE_PCI_INTB
	अगर (N_RX_COMP_RINGS > 1) अणु
		/* cas_पूर्णांकerrupt1(); */
	पूर्ण
#पूर्ण_अगर
#अगर_घोषित USE_PCI_INTC
	अगर (N_RX_COMP_RINGS > 2) अणु
		/* cas_पूर्णांकerruptN(); */
	पूर्ण
#पूर्ण_अगर
#अगर_घोषित USE_PCI_INTD
	अगर (N_RX_COMP_RINGS > 3) अणु
		/* cas_पूर्णांकerruptN(); */
	पूर्ण
#पूर्ण_अगर
पूर्ण
#पूर्ण_अगर

अटल व्योम cas_tx_समयout(काष्ठा net_device *dev, अचिन्हित पूर्णांक txqueue)
अणु
	काष्ठा cas *cp = netdev_priv(dev);

	netdev_err(dev, "transmit timed out, resetting\n");
	अगर (!cp->hw_running) अणु
		netdev_err(dev, "hrm.. hw not running!\n");
		वापस;
	पूर्ण

	netdev_err(dev, "MIF_STATE[%08x]\n",
		   पढ़ोl(cp->regs + REG_MIF_STATE_MACHINE));

	netdev_err(dev, "MAC_STATE[%08x]\n",
		   पढ़ोl(cp->regs + REG_MAC_STATE_MACHINE));

	netdev_err(dev, "TX_STATE[%08x:%08x:%08x] FIFO[%08x:%08x:%08x] SM1[%08x] SM2[%08x]\n",
		   पढ़ोl(cp->regs + REG_TX_CFG),
		   पढ़ोl(cp->regs + REG_MAC_TX_STATUS),
		   पढ़ोl(cp->regs + REG_MAC_TX_CFG),
		   पढ़ोl(cp->regs + REG_TX_FIFO_PKT_CNT),
		   पढ़ोl(cp->regs + REG_TX_FIFO_WRITE_PTR),
		   पढ़ोl(cp->regs + REG_TX_FIFO_READ_PTR),
		   पढ़ोl(cp->regs + REG_TX_SM_1),
		   पढ़ोl(cp->regs + REG_TX_SM_2));

	netdev_err(dev, "RX_STATE[%08x:%08x:%08x]\n",
		   पढ़ोl(cp->regs + REG_RX_CFG),
		   पढ़ोl(cp->regs + REG_MAC_RX_STATUS),
		   पढ़ोl(cp->regs + REG_MAC_RX_CFG));

	netdev_err(dev, "HP_STATE[%08x:%08x:%08x:%08x]\n",
		   पढ़ोl(cp->regs + REG_HP_STATE_MACHINE),
		   पढ़ोl(cp->regs + REG_HP_STATUS0),
		   पढ़ोl(cp->regs + REG_HP_STATUS1),
		   पढ़ोl(cp->regs + REG_HP_STATUS2));

#अगर 1
	atomic_inc(&cp->reset_task_pending);
	atomic_inc(&cp->reset_task_pending_all);
	schedule_work(&cp->reset_task);
#अन्यथा
	atomic_set(&cp->reset_task_pending, CAS_RESET_ALL);
	schedule_work(&cp->reset_task);
#पूर्ण_अगर
पूर्ण

अटल अंतरभूत पूर्णांक cas_पूर्णांकme(पूर्णांक ring, पूर्णांक entry)
अणु
	/* Algorithm: IRQ every 1/2 of descriptors. */
	अगर (!(entry & ((TX_DESC_RINGN_SIZE(ring) >> 1) - 1)))
		वापस 1;
	वापस 0;
पूर्ण


अटल व्योम cas_ग_लिखो_txd(काष्ठा cas *cp, पूर्णांक ring, पूर्णांक entry,
			  dma_addr_t mapping, पूर्णांक len, u64 ctrl, पूर्णांक last)
अणु
	काष्ठा cas_tx_desc *txd = cp->init_txds[ring] + entry;

	ctrl |= CAS_BASE(TX_DESC_BUFLEN, len);
	अगर (cas_पूर्णांकme(ring, entry))
		ctrl |= TX_DESC_INTME;
	अगर (last)
		ctrl |= TX_DESC_खातापूर्ण;
	txd->control = cpu_to_le64(ctrl);
	txd->buffer = cpu_to_le64(mapping);
पूर्ण

अटल अंतरभूत व्योम *tx_tiny_buf(काष्ठा cas *cp, स्थिर पूर्णांक ring,
				स्थिर पूर्णांक entry)
अणु
	वापस cp->tx_tiny_bufs[ring] + TX_TINY_BUF_LEN*entry;
पूर्ण

अटल अंतरभूत dma_addr_t tx_tiny_map(काष्ठा cas *cp, स्थिर पूर्णांक ring,
				     स्थिर पूर्णांक entry, स्थिर पूर्णांक tentry)
अणु
	cp->tx_tiny_use[ring][tentry].nbufs++;
	cp->tx_tiny_use[ring][entry].used = 1;
	वापस cp->tx_tiny_dvma[ring] + TX_TINY_BUF_LEN*entry;
पूर्ण

अटल अंतरभूत पूर्णांक cas_xmit_tx_ringN(काष्ठा cas *cp, पूर्णांक ring,
				    काष्ठा sk_buff *skb)
अणु
	काष्ठा net_device *dev = cp->dev;
	पूर्णांक entry, nr_frags, frag, tपात, tentry;
	dma_addr_t mapping;
	अचिन्हित दीर्घ flags;
	u64 ctrl;
	u32 len;

	spin_lock_irqsave(&cp->tx_lock[ring], flags);

	/* This is a hard error, log it. */
	अगर (TX_BUFFS_AVAIL(cp, ring) <=
	    CAS_TABORT(cp)*(skb_shinfo(skb)->nr_frags + 1)) अणु
		netअगर_stop_queue(dev);
		spin_unlock_irqrestore(&cp->tx_lock[ring], flags);
		netdev_err(dev, "BUG! Tx Ring full when queue awake!\n");
		वापस 1;
	पूर्ण

	ctrl = 0;
	अगर (skb->ip_summed == CHECKSUM_PARTIAL) अणु
		स्थिर u64 csum_start_off = skb_checksum_start_offset(skb);
		स्थिर u64 csum_stuff_off = csum_start_off + skb->csum_offset;

		ctrl =  TX_DESC_CSUM_EN |
			CAS_BASE(TX_DESC_CSUM_START, csum_start_off) |
			CAS_BASE(TX_DESC_CSUM_STUFF, csum_stuff_off);
	पूर्ण

	entry = cp->tx_new[ring];
	cp->tx_skbs[ring][entry] = skb;

	nr_frags = skb_shinfo(skb)->nr_frags;
	len = skb_headlen(skb);
	mapping = dma_map_page(&cp->pdev->dev, virt_to_page(skb->data),
			       offset_in_page(skb->data), len, DMA_TO_DEVICE);

	tentry = entry;
	tपात = cas_calc_tपात(cp, (अचिन्हित दीर्घ) skb->data, len);
	अगर (unlikely(tपात)) अणु
		/* NOTE: len is always >  tपात */
		cas_ग_लिखो_txd(cp, ring, entry, mapping, len - tपात,
			      ctrl | TX_DESC_SOF, 0);
		entry = TX_DESC_NEXT(ring, entry);

		skb_copy_from_linear_data_offset(skb, len - tपात,
			      tx_tiny_buf(cp, ring, entry), tपात);
		mapping = tx_tiny_map(cp, ring, entry, tentry);
		cas_ग_लिखो_txd(cp, ring, entry, mapping, tपात, ctrl,
			      (nr_frags == 0));
	पूर्ण अन्यथा अणु
		cas_ग_लिखो_txd(cp, ring, entry, mapping, len, ctrl |
			      TX_DESC_SOF, (nr_frags == 0));
	पूर्ण
	entry = TX_DESC_NEXT(ring, entry);

	क्रम (frag = 0; frag < nr_frags; frag++) अणु
		स्थिर skb_frag_t *fragp = &skb_shinfo(skb)->frags[frag];

		len = skb_frag_size(fragp);
		mapping = skb_frag_dma_map(&cp->pdev->dev, fragp, 0, len,
					   DMA_TO_DEVICE);

		tपात = cas_calc_tपात(cp, skb_frag_off(fragp), len);
		अगर (unlikely(tपात)) अणु
			व्योम *addr;

			/* NOTE: len is always > tपात */
			cas_ग_लिखो_txd(cp, ring, entry, mapping, len - tपात,
				      ctrl, 0);
			entry = TX_DESC_NEXT(ring, entry);

			addr = cas_page_map(skb_frag_page(fragp));
			स_नकल(tx_tiny_buf(cp, ring, entry),
			       addr + skb_frag_off(fragp) + len - tपात,
			       tपात);
			cas_page_unmap(addr);
			mapping = tx_tiny_map(cp, ring, entry, tentry);
			len     = tपात;
		पूर्ण

		cas_ग_लिखो_txd(cp, ring, entry, mapping, len, ctrl,
			      (frag + 1 == nr_frags));
		entry = TX_DESC_NEXT(ring, entry);
	पूर्ण

	cp->tx_new[ring] = entry;
	अगर (TX_BUFFS_AVAIL(cp, ring) <= CAS_TABORT(cp)*(MAX_SKB_FRAGS + 1))
		netअगर_stop_queue(dev);

	netअगर_prपूर्णांकk(cp, tx_queued, KERN_DEBUG, dev,
		     "tx[%d] queued, slot %d, skblen %d, avail %d\n",
		     ring, entry, skb->len, TX_BUFFS_AVAIL(cp, ring));
	ग_लिखोl(entry, cp->regs + REG_TX_KICKN(ring));
	spin_unlock_irqrestore(&cp->tx_lock[ring], flags);
	वापस 0;
पूर्ण

अटल netdev_tx_t cas_start_xmit(काष्ठा sk_buff *skb, काष्ठा net_device *dev)
अणु
	काष्ठा cas *cp = netdev_priv(dev);

	/* this is only used as a load-balancing hपूर्णांक, so it करोesn't
	 * need to be SMP safe
	 */
	अटल पूर्णांक ring;

	अगर (skb_padto(skb, cp->min_frame_size))
		वापस NETDEV_TX_OK;

	/* XXX: we need some higher-level QoS hooks to steer packets to
	 *      inभागidual queues.
	 */
	अगर (cas_xmit_tx_ringN(cp, ring++ & N_TX_RINGS_MASK, skb))
		वापस NETDEV_TX_BUSY;
	वापस NETDEV_TX_OK;
पूर्ण

अटल व्योम cas_init_tx_dma(काष्ठा cas *cp)
अणु
	u64 desc_dma = cp->block_dvma;
	अचिन्हित दीर्घ off;
	u32 val;
	पूर्णांक i;

	/* set up tx completion ग_लिखोback रेजिस्टरs. must be 8-byte aligned */
#अगर_घोषित USE_TX_COMPWB
	off = दुरत्व(काष्ठा cas_init_block, tx_compwb);
	ग_लिखोl((desc_dma + off) >> 32, cp->regs + REG_TX_COMPWB_DB_HI);
	ग_लिखोl((desc_dma + off) & 0xffffffff, cp->regs + REG_TX_COMPWB_DB_LOW);
#पूर्ण_अगर

	/* enable completion ग_लिखोbacks, enable paced mode,
	 * disable पढ़ो pipe, and disable pre-पूर्णांकerrupt compwbs
	 */
	val =   TX_CFG_COMPWB_Q1 | TX_CFG_COMPWB_Q2 |
		TX_CFG_COMPWB_Q3 | TX_CFG_COMPWB_Q4 |
		TX_CFG_DMA_RDPIPE_DIS | TX_CFG_PACED_MODE |
		TX_CFG_INTR_COMPWB_DIS;

	/* ग_लिखो out tx ring info and tx desc bases */
	क्रम (i = 0; i < MAX_TX_RINGS; i++) अणु
		off = (अचिन्हित दीर्घ) cp->init_txds[i] -
			(अचिन्हित दीर्घ) cp->init_block;

		val |= CAS_TX_RINGN_BASE(i);
		ग_लिखोl((desc_dma + off) >> 32, cp->regs + REG_TX_DBN_HI(i));
		ग_लिखोl((desc_dma + off) & 0xffffffff, cp->regs +
		       REG_TX_DBN_LOW(i));
		/* करोn't zero out the kick रेजिस्टर here as the प्रणाली
		 * will wedge
		 */
	पूर्ण
	ग_लिखोl(val, cp->regs + REG_TX_CFG);

	/* program max burst sizes. these numbers should be dअगरferent
	 * अगर करोing QoS.
	 */
#अगर_घोषित USE_QOS
	ग_लिखोl(0x800, cp->regs + REG_TX_MAXBURST_0);
	ग_लिखोl(0x1600, cp->regs + REG_TX_MAXBURST_1);
	ग_लिखोl(0x2400, cp->regs + REG_TX_MAXBURST_2);
	ग_लिखोl(0x4800, cp->regs + REG_TX_MAXBURST_3);
#अन्यथा
	ग_लिखोl(0x800, cp->regs + REG_TX_MAXBURST_0);
	ग_लिखोl(0x800, cp->regs + REG_TX_MAXBURST_1);
	ग_लिखोl(0x800, cp->regs + REG_TX_MAXBURST_2);
	ग_लिखोl(0x800, cp->regs + REG_TX_MAXBURST_3);
#पूर्ण_अगर
पूर्ण

/* Must be invoked under cp->lock. */
अटल अंतरभूत व्योम cas_init_dma(काष्ठा cas *cp)
अणु
	cas_init_tx_dma(cp);
	cas_init_rx_dma(cp);
पूर्ण

अटल व्योम cas_process_mc_list(काष्ठा cas *cp)
अणु
	u16 hash_table[16];
	u32 crc;
	काष्ठा netdev_hw_addr *ha;
	पूर्णांक i = 1;

	स_रखो(hash_table, 0, माप(hash_table));
	netdev_क्रम_each_mc_addr(ha, cp->dev) अणु
		अगर (i <= CAS_MC_EXACT_MATCH_SIZE) अणु
			/* use the alternate mac address रेजिस्टरs क्रम the
			 * first 15 multicast addresses
			 */
			ग_लिखोl((ha->addr[4] << 8) | ha->addr[5],
			       cp->regs + REG_MAC_ADDRN(i*3 + 0));
			ग_लिखोl((ha->addr[2] << 8) | ha->addr[3],
			       cp->regs + REG_MAC_ADDRN(i*3 + 1));
			ग_लिखोl((ha->addr[0] << 8) | ha->addr[1],
			       cp->regs + REG_MAC_ADDRN(i*3 + 2));
			i++;
		पूर्ण
		अन्यथा अणु
			/* use hw hash table क्रम the next series of
			 * multicast addresses
			 */
			crc = ether_crc_le(ETH_ALEN, ha->addr);
			crc >>= 24;
			hash_table[crc >> 4] |= 1 << (15 - (crc & 0xf));
		पूर्ण
	पूर्ण
	क्रम (i = 0; i < 16; i++)
		ग_लिखोl(hash_table[i], cp->regs + REG_MAC_HASH_TABLEN(i));
पूर्ण

/* Must be invoked under cp->lock. */
अटल u32 cas_setup_multicast(काष्ठा cas *cp)
अणु
	u32 rxcfg = 0;
	पूर्णांक i;

	अगर (cp->dev->flags & IFF_PROMISC) अणु
		rxcfg |= MAC_RX_CFG_PROMISC_EN;

	पूर्ण अन्यथा अगर (cp->dev->flags & IFF_ALLMULTI) अणु
	    	क्रम (i=0; i < 16; i++)
			ग_लिखोl(0xFFFF, cp->regs + REG_MAC_HASH_TABLEN(i));
		rxcfg |= MAC_RX_CFG_HASH_FILTER_EN;

	पूर्ण अन्यथा अणु
		cas_process_mc_list(cp);
		rxcfg |= MAC_RX_CFG_HASH_FILTER_EN;
	पूर्ण

	वापस rxcfg;
पूर्ण

/* must be invoked under cp->stat_lock[N_TX_RINGS] */
अटल व्योम cas_clear_mac_err(काष्ठा cas *cp)
अणु
	ग_लिखोl(0, cp->regs + REG_MAC_COLL_NORMAL);
	ग_लिखोl(0, cp->regs + REG_MAC_COLL_FIRST);
	ग_लिखोl(0, cp->regs + REG_MAC_COLL_EXCESS);
	ग_लिखोl(0, cp->regs + REG_MAC_COLL_LATE);
	ग_लिखोl(0, cp->regs + REG_MAC_TIMER_DEFER);
	ग_लिखोl(0, cp->regs + REG_MAC_ATTEMPTS_PEAK);
	ग_लिखोl(0, cp->regs + REG_MAC_RECV_FRAME);
	ग_लिखोl(0, cp->regs + REG_MAC_LEN_ERR);
	ग_लिखोl(0, cp->regs + REG_MAC_ALIGN_ERR);
	ग_लिखोl(0, cp->regs + REG_MAC_FCS_ERR);
	ग_लिखोl(0, cp->regs + REG_MAC_RX_CODE_ERR);
पूर्ण


अटल व्योम cas_mac_reset(काष्ठा cas *cp)
अणु
	पूर्णांक i;

	/* करो both TX and RX reset */
	ग_लिखोl(0x1, cp->regs + REG_MAC_TX_RESET);
	ग_लिखोl(0x1, cp->regs + REG_MAC_RX_RESET);

	/* रुको क्रम TX */
	i = STOP_TRIES;
	जबतक (i-- > 0) अणु
		अगर (पढ़ोl(cp->regs + REG_MAC_TX_RESET) == 0)
			अवरोध;
		udelay(10);
	पूर्ण

	/* रुको क्रम RX */
	i = STOP_TRIES;
	जबतक (i-- > 0) अणु
		अगर (पढ़ोl(cp->regs + REG_MAC_RX_RESET) == 0)
			अवरोध;
		udelay(10);
	पूर्ण

	अगर (पढ़ोl(cp->regs + REG_MAC_TX_RESET) |
	    पढ़ोl(cp->regs + REG_MAC_RX_RESET))
		netdev_err(cp->dev, "mac tx[%d]/rx[%d] reset failed [%08x]\n",
			   पढ़ोl(cp->regs + REG_MAC_TX_RESET),
			   पढ़ोl(cp->regs + REG_MAC_RX_RESET),
			   पढ़ोl(cp->regs + REG_MAC_STATE_MACHINE));
पूर्ण


/* Must be invoked under cp->lock. */
अटल व्योम cas_init_mac(काष्ठा cas *cp)
अणु
	अचिन्हित अक्षर *e = &cp->dev->dev_addr[0];
	पूर्णांक i;
	cas_mac_reset(cp);

	/* setup core arbitration weight रेजिस्टर */
	ग_लिखोl(CAWR_RR_DIS, cp->regs + REG_CAWR);

#अगर !defined(CONFIG_SPARC64) && !defined(CONFIG_ALPHA)
	/* set the infinite burst रेजिस्टर क्रम chips that करोn't have
	 * pci issues.
	 */
	अगर ((cp->cas_flags & CAS_FLAG_TARGET_ABORT) == 0)
		ग_लिखोl(INF_BURST_EN, cp->regs + REG_INF_BURST);
#पूर्ण_अगर

	ग_लिखोl(0x1BF0, cp->regs + REG_MAC_SEND_PAUSE);

	ग_लिखोl(0x00, cp->regs + REG_MAC_IPG0);
	ग_लिखोl(0x08, cp->regs + REG_MAC_IPG1);
	ग_लिखोl(0x04, cp->regs + REG_MAC_IPG2);

	/* change later क्रम 802.3z */
	ग_लिखोl(0x40, cp->regs + REG_MAC_SLOT_TIME);

	/* min frame + FCS */
	ग_लिखोl(ETH_ZLEN + 4, cp->regs + REG_MAC_FRAMESIZE_MIN);

	/* Ethernet payload + header + FCS + optional VLAN tag. NOTE: we
	 * specअगरy the maximum frame size to prevent RX tag errors on
	 * oversized frames.
	 */
	ग_लिखोl(CAS_BASE(MAC_FRAMESIZE_MAX_BURST, 0x2000) |
	       CAS_BASE(MAC_FRAMESIZE_MAX_FRAME,
			(CAS_MAX_MTU + ETH_HLEN + 4 + 4)),
	       cp->regs + REG_MAC_FRAMESIZE_MAX);

	/* NOTE: crc_size is used as a surrogate क्रम half-duplex.
	 * workaround saturn half-duplex issue by increasing preamble
	 * size to 65 bytes.
	 */
	अगर ((cp->cas_flags & CAS_FLAG_SATURN) && cp->crc_size)
		ग_लिखोl(0x41, cp->regs + REG_MAC_PA_SIZE);
	अन्यथा
		ग_लिखोl(0x07, cp->regs + REG_MAC_PA_SIZE);
	ग_लिखोl(0x04, cp->regs + REG_MAC_JAM_SIZE);
	ग_लिखोl(0x10, cp->regs + REG_MAC_ATTEMPT_LIMIT);
	ग_लिखोl(0x8808, cp->regs + REG_MAC_CTRL_TYPE);

	ग_लिखोl((e[5] | (e[4] << 8)) & 0x3ff, cp->regs + REG_MAC_RANDOM_SEED);

	ग_लिखोl(0, cp->regs + REG_MAC_ADDR_FILTER0);
	ग_लिखोl(0, cp->regs + REG_MAC_ADDR_FILTER1);
	ग_लिखोl(0, cp->regs + REG_MAC_ADDR_FILTER2);
	ग_लिखोl(0, cp->regs + REG_MAC_ADDR_FILTER2_1_MASK);
	ग_लिखोl(0, cp->regs + REG_MAC_ADDR_FILTER0_MASK);

	/* setup mac address in perfect filter array */
	क्रम (i = 0; i < 45; i++)
		ग_लिखोl(0x0, cp->regs + REG_MAC_ADDRN(i));

	ग_लिखोl((e[4] << 8) | e[5], cp->regs + REG_MAC_ADDRN(0));
	ग_लिखोl((e[2] << 8) | e[3], cp->regs + REG_MAC_ADDRN(1));
	ग_लिखोl((e[0] << 8) | e[1], cp->regs + REG_MAC_ADDRN(2));

	ग_लिखोl(0x0001, cp->regs + REG_MAC_ADDRN(42));
	ग_लिखोl(0xc200, cp->regs + REG_MAC_ADDRN(43));
	ग_लिखोl(0x0180, cp->regs + REG_MAC_ADDRN(44));

	cp->mac_rx_cfg = cas_setup_multicast(cp);

	spin_lock(&cp->stat_lock[N_TX_RINGS]);
	cas_clear_mac_err(cp);
	spin_unlock(&cp->stat_lock[N_TX_RINGS]);

	/* Setup MAC पूर्णांकerrupts.  We want to get all of the पूर्णांकeresting
	 * counter expiration events, but we करो not want to hear about
	 * normal rx/tx as the DMA engine tells us that.
	 */
	ग_लिखोl(MAC_TX_FRAME_XMIT, cp->regs + REG_MAC_TX_MASK);
	ग_लिखोl(MAC_RX_FRAME_RECV, cp->regs + REG_MAC_RX_MASK);

	/* Don't enable even the PAUSE पूर्णांकerrupts क्रम now, we
	 * make no use of those events other than to record them.
	 */
	ग_लिखोl(0xffffffff, cp->regs + REG_MAC_CTRL_MASK);
पूर्ण

/* Must be invoked under cp->lock. */
अटल व्योम cas_init_छोड़ो_thresholds(काष्ठा cas *cp)
अणु
	/* Calculate छोड़ो thresholds.  Setting the OFF threshold to the
	 * full RX fअगरo size effectively disables PAUSE generation
	 */
	अगर (cp->rx_fअगरo_size <= (2 * 1024)) अणु
		cp->rx_छोड़ो_off = cp->rx_छोड़ो_on = cp->rx_fअगरo_size;
	पूर्ण अन्यथा अणु
		पूर्णांक max_frame = (cp->dev->mtu + ETH_HLEN + 4 + 4 + 64) & ~63;
		अगर (max_frame * 3 > cp->rx_fअगरo_size) अणु
			cp->rx_छोड़ो_off = 7104;
			cp->rx_छोड़ो_on  = 960;
		पूर्ण अन्यथा अणु
			पूर्णांक off = (cp->rx_fअगरo_size - (max_frame * 2));
			पूर्णांक on = off - max_frame;
			cp->rx_छोड़ो_off = off;
			cp->rx_छोड़ो_on = on;
		पूर्ण
	पूर्ण
पूर्ण

अटल पूर्णांक cas_vpd_match(स्थिर व्योम __iomem *p, स्थिर अक्षर *str)
अणु
	पूर्णांक len = म_माप(str) + 1;
	पूर्णांक i;

	क्रम (i = 0; i < len; i++) अणु
		अगर (पढ़ोb(p + i) != str[i])
			वापस 0;
	पूर्ण
	वापस 1;
पूर्ण


/* get the mac address by पढ़ोing the vpd inक्रमmation in the rom.
 * also get the phy type and determine अगर there's an entropy generator.
 * NOTE: this is a bit convoluted क्रम the following reasons:
 *  1) vpd info has order-dependent mac addresses क्रम multinic cards
 *  2) the only way to determine the nic order is to use the slot
 *     number.
 *  3) fiber cards करोn't have bridges, so their slot numbers don't
 *     mean anything.
 *  4) we करोn't actually know we have a fiber card until after
 *     the mac addresses are parsed.
 */
अटल पूर्णांक cas_get_vpd_info(काष्ठा cas *cp, अचिन्हित अक्षर *dev_addr,
			    स्थिर पूर्णांक offset)
अणु
	व्योम __iomem *p = cp->regs + REG_EXPANSION_ROM_RUN_START;
	व्योम __iomem *base, *kstart;
	पूर्णांक i, len;
	पूर्णांक found = 0;
#घोषणा VPD_FOUND_MAC        0x01
#घोषणा VPD_FOUND_PHY        0x02

	पूर्णांक phy_type = CAS_PHY_MII_MDIO0; /* शेष phy type */
	पूर्णांक mac_off  = 0;

#अगर defined(CONFIG_SPARC)
	स्थिर अचिन्हित अक्षर *addr;
#पूर्ण_अगर

	/* give us access to the PROM */
	ग_लिखोl(BIM_LOCAL_DEV_PROM | BIM_LOCAL_DEV_PAD,
	       cp->regs + REG_BIM_LOCAL_DEV_EN);

	/* check क्रम an expansion rom */
	अगर (पढ़ोb(p) != 0x55 || पढ़ोb(p + 1) != 0xaa)
		जाओ use_अक्रमom_mac_addr;

	/* search क्रम beginning of vpd */
	base = शून्य;
	क्रम (i = 2; i < EXPANSION_ROM_SIZE; i++) अणु
		/* check क्रम PCIR */
		अगर ((पढ़ोb(p + i + 0) == 0x50) &&
		    (पढ़ोb(p + i + 1) == 0x43) &&
		    (पढ़ोb(p + i + 2) == 0x49) &&
		    (पढ़ोb(p + i + 3) == 0x52)) अणु
			base = p + (पढ़ोb(p + i + 8) |
				    (पढ़ोb(p + i + 9) << 8));
			अवरोध;
		पूर्ण
	पूर्ण

	अगर (!base || (पढ़ोb(base) != 0x82))
		जाओ use_अक्रमom_mac_addr;

	i = (पढ़ोb(base + 1) | (पढ़ोb(base + 2) << 8)) + 3;
	जबतक (i < EXPANSION_ROM_SIZE) अणु
		अगर (पढ़ोb(base + i) != 0x90) /* no vpd found */
			जाओ use_अक्रमom_mac_addr;

		/* found a vpd field */
		len = पढ़ोb(base + i + 1) | (पढ़ोb(base + i + 2) << 8);

		/* extract keywords */
		kstart = base + i + 3;
		p = kstart;
		जबतक ((p - kstart) < len) अणु
			पूर्णांक klen = पढ़ोb(p + 2);
			पूर्णांक j;
			अक्षर type;

			p += 3;

			/* look क्रम the following things:
			 * -- correct length == 29
			 * 3 (type) + 2 (size) +
			 * 18 (म_माप("local-mac-address") + 1) +
			 * 6 (mac addr)
			 * -- VPD Instance 'I'
			 * -- VPD Type Bytes 'B'
			 * -- VPD data length == 6
			 * -- property string == local-mac-address
			 *
			 * -- correct length == 24
			 * 3 (type) + 2 (size) +
			 * 12 (म_माप("entropy-dev") + 1) +
			 * 7 (म_माप("vms110") + 1)
			 * -- VPD Instance 'I'
			 * -- VPD Type String 'B'
			 * -- VPD data length == 7
			 * -- property string == entropy-dev
			 *
			 * -- correct length == 18
			 * 3 (type) + 2 (size) +
			 * 9 (म_माप("phy-type") + 1) +
			 * 4 (म_माप("pcs") + 1)
			 * -- VPD Instance 'I'
			 * -- VPD Type String 'S'
			 * -- VPD data length == 4
			 * -- property string == phy-type
			 *
			 * -- correct length == 23
			 * 3 (type) + 2 (size) +
			 * 14 (म_माप("phy-interface") + 1) +
			 * 4 (म_माप("pcs") + 1)
			 * -- VPD Instance 'I'
			 * -- VPD Type String 'S'
			 * -- VPD data length == 4
			 * -- property string == phy-पूर्णांकerface
			 */
			अगर (पढ़ोb(p) != 'I')
				जाओ next;

			/* finally, check string and length */
			type = पढ़ोb(p + 3);
			अगर (type == 'B') अणु
				अगर ((klen == 29) && पढ़ोb(p + 4) == 6 &&
				    cas_vpd_match(p + 5,
						  "local-mac-address")) अणु
					अगर (mac_off++ > offset)
						जाओ next;

					/* set mac address */
					क्रम (j = 0; j < 6; j++)
						dev_addr[j] =
							पढ़ोb(p + 23 + j);
					जाओ found_mac;
				पूर्ण
			पूर्ण

			अगर (type != 'S')
				जाओ next;

#अगर_घोषित USE_ENTROPY_DEV
			अगर ((klen == 24) &&
			    cas_vpd_match(p + 5, "entropy-dev") &&
			    cas_vpd_match(p + 17, "vms110")) अणु
				cp->cas_flags |= CAS_FLAG_ENTROPY_DEV;
				जाओ next;
			पूर्ण
#पूर्ण_अगर

			अगर (found & VPD_FOUND_PHY)
				जाओ next;

			अगर ((klen == 18) && पढ़ोb(p + 4) == 4 &&
			    cas_vpd_match(p + 5, "phy-type")) अणु
				अगर (cas_vpd_match(p + 14, "pcs")) अणु
					phy_type = CAS_PHY_SERDES;
					जाओ found_phy;
				पूर्ण
			पूर्ण

			अगर ((klen == 23) && पढ़ोb(p + 4) == 4 &&
			    cas_vpd_match(p + 5, "phy-interface")) अणु
				अगर (cas_vpd_match(p + 19, "pcs")) अणु
					phy_type = CAS_PHY_SERDES;
					जाओ found_phy;
				पूर्ण
			पूर्ण
found_mac:
			found |= VPD_FOUND_MAC;
			जाओ next;

found_phy:
			found |= VPD_FOUND_PHY;

next:
			p += klen;
		पूर्ण
		i += len + 3;
	पूर्ण

use_अक्रमom_mac_addr:
	अगर (found & VPD_FOUND_MAC)
		जाओ करोne;

#अगर defined(CONFIG_SPARC)
	addr = of_get_property(cp->of_node, "local-mac-address", शून्य);
	अगर (addr != शून्य) अणु
		स_नकल(dev_addr, addr, ETH_ALEN);
		जाओ करोne;
	पूर्ण
#पूर्ण_अगर

	/* Sun MAC prefix then 3 अक्रमom bytes. */
	pr_info("MAC address not found in ROM VPD\n");
	dev_addr[0] = 0x08;
	dev_addr[1] = 0x00;
	dev_addr[2] = 0x20;
	get_अक्रमom_bytes(dev_addr + 3, 3);

करोne:
	ग_लिखोl(0, cp->regs + REG_BIM_LOCAL_DEV_EN);
	वापस phy_type;
पूर्ण

/* check pci invariants */
अटल व्योम cas_check_pci_invariants(काष्ठा cas *cp)
अणु
	काष्ठा pci_dev *pdev = cp->pdev;

	cp->cas_flags = 0;
	अगर ((pdev->venकरोr == PCI_VENDOR_ID_SUN) &&
	    (pdev->device == PCI_DEVICE_ID_SUN_CASSINI)) अणु
		अगर (pdev->revision >= CAS_ID_REVPLUS)
			cp->cas_flags |= CAS_FLAG_REG_PLUS;
		अगर (pdev->revision < CAS_ID_REVPLUS02u)
			cp->cas_flags |= CAS_FLAG_TARGET_ABORT;

		/* Original Cassini supports HW CSUM, but it's not
		 * enabled by शेष as it can trigger TX hangs.
		 */
		अगर (pdev->revision < CAS_ID_REV2)
			cp->cas_flags |= CAS_FLAG_NO_HW_CSUM;
	पूर्ण अन्यथा अणु
		/* Only sun has original cassini chips.  */
		cp->cas_flags |= CAS_FLAG_REG_PLUS;

		/* We use a flag because the same phy might be बाह्यally
		 * connected.
		 */
		अगर ((pdev->venकरोr == PCI_VENDOR_ID_NS) &&
		    (pdev->device == PCI_DEVICE_ID_NS_SATURN))
			cp->cas_flags |= CAS_FLAG_SATURN;
	पूर्ण
पूर्ण


अटल पूर्णांक cas_check_invariants(काष्ठा cas *cp)
अणु
	काष्ठा pci_dev *pdev = cp->pdev;
	u32 cfg;
	पूर्णांक i;

	/* get page size क्रम rx buffers. */
	cp->page_order = 0;
#अगर_घोषित USE_PAGE_ORDER
	अगर (PAGE_SHIFT < CAS_JUMBO_PAGE_SHIFT) अणु
		/* see अगर we can allocate larger pages */
		काष्ठा page *page = alloc_pages(GFP_ATOMIC,
						CAS_JUMBO_PAGE_SHIFT -
						PAGE_SHIFT);
		अगर (page) अणु
			__मुक्त_pages(page, CAS_JUMBO_PAGE_SHIFT - PAGE_SHIFT);
			cp->page_order = CAS_JUMBO_PAGE_SHIFT - PAGE_SHIFT;
		पूर्ण अन्यथा अणु
			prपूर्णांकk("MTU limited to %d bytes\n", CAS_MAX_MTU);
		पूर्ण
	पूर्ण
#पूर्ण_अगर
	cp->page_size = (PAGE_SIZE << cp->page_order);

	/* Fetch the FIFO configurations. */
	cp->tx_fअगरo_size = पढ़ोl(cp->regs + REG_TX_FIFO_SIZE) * 64;
	cp->rx_fअगरo_size = RX_FIFO_SIZE;

	/* finish phy determination. MDIO1 takes precedence over MDIO0 अगर
	 * they're both connected.
	 */
	cp->phy_type = cas_get_vpd_info(cp, cp->dev->dev_addr,
					PCI_SLOT(pdev->devfn));
	अगर (cp->phy_type & CAS_PHY_SERDES) अणु
		cp->cas_flags |= CAS_FLAG_1000MB_CAP;
		वापस 0; /* no more checking needed */
	पूर्ण

	/* MII */
	cfg = पढ़ोl(cp->regs + REG_MIF_CFG);
	अगर (cfg & MIF_CFG_MDIO_1) अणु
		cp->phy_type = CAS_PHY_MII_MDIO1;
	पूर्ण अन्यथा अगर (cfg & MIF_CFG_MDIO_0) अणु
		cp->phy_type = CAS_PHY_MII_MDIO0;
	पूर्ण

	cas_mअगर_poll(cp, 0);
	ग_लिखोl(PCS_DATAPATH_MODE_MII, cp->regs + REG_PCS_DATAPATH_MODE);

	क्रम (i = 0; i < 32; i++) अणु
		u32 phy_id;
		पूर्णांक j;

		क्रम (j = 0; j < 3; j++) अणु
			cp->phy_addr = i;
			phy_id = cas_phy_पढ़ो(cp, MII_PHYSID1) << 16;
			phy_id |= cas_phy_पढ़ो(cp, MII_PHYSID2);
			अगर (phy_id && (phy_id != 0xFFFFFFFF)) अणु
				cp->phy_id = phy_id;
				जाओ करोne;
			पूर्ण
		पूर्ण
	पूर्ण
	pr_err("MII phy did not respond [%08x]\n",
	       पढ़ोl(cp->regs + REG_MIF_STATE_MACHINE));
	वापस -1;

करोne:
	/* see अगर we can करो gigabit */
	cfg = cas_phy_पढ़ो(cp, MII_BMSR);
	अगर ((cfg & CAS_BMSR_1000_EXTEND) &&
	    cas_phy_पढ़ो(cp, CAS_MII_1000_EXTEND))
		cp->cas_flags |= CAS_FLAG_1000MB_CAP;
	वापस 0;
पूर्ण

/* Must be invoked under cp->lock. */
अटल अंतरभूत व्योम cas_start_dma(काष्ठा cas *cp)
अणु
	पूर्णांक i;
	u32 val;
	पूर्णांक txfailed = 0;

	/* enable dma */
	val = पढ़ोl(cp->regs + REG_TX_CFG) | TX_CFG_DMA_EN;
	ग_लिखोl(val, cp->regs + REG_TX_CFG);
	val = पढ़ोl(cp->regs + REG_RX_CFG) | RX_CFG_DMA_EN;
	ग_लिखोl(val, cp->regs + REG_RX_CFG);

	/* enable the mac */
	val = पढ़ोl(cp->regs + REG_MAC_TX_CFG) | MAC_TX_CFG_EN;
	ग_लिखोl(val, cp->regs + REG_MAC_TX_CFG);
	val = पढ़ोl(cp->regs + REG_MAC_RX_CFG) | MAC_RX_CFG_EN;
	ग_लिखोl(val, cp->regs + REG_MAC_RX_CFG);

	i = STOP_TRIES;
	जबतक (i-- > 0) अणु
		val = पढ़ोl(cp->regs + REG_MAC_TX_CFG);
		अगर ((val & MAC_TX_CFG_EN))
			अवरोध;
		udelay(10);
	पूर्ण
	अगर (i < 0) txfailed = 1;
	i = STOP_TRIES;
	जबतक (i-- > 0) अणु
		val = पढ़ोl(cp->regs + REG_MAC_RX_CFG);
		अगर ((val & MAC_RX_CFG_EN)) अणु
			अगर (txfailed) अणु
				netdev_err(cp->dev,
					   "enabling mac failed [tx:%08x:%08x]\n",
					   पढ़ोl(cp->regs + REG_MIF_STATE_MACHINE),
					   पढ़ोl(cp->regs + REG_MAC_STATE_MACHINE));
			पूर्ण
			जाओ enable_rx_करोne;
		पूर्ण
		udelay(10);
	पूर्ण
	netdev_err(cp->dev, "enabling mac failed [%s:%08x:%08x]\n",
		   (txfailed ? "tx,rx" : "rx"),
		   पढ़ोl(cp->regs + REG_MIF_STATE_MACHINE),
		   पढ़ोl(cp->regs + REG_MAC_STATE_MACHINE));

enable_rx_करोne:
	cas_unmask_पूर्णांकr(cp); /* enable पूर्णांकerrupts */
	ग_लिखोl(RX_DESC_RINGN_SIZE(0) - 4, cp->regs + REG_RX_KICK);
	ग_लिखोl(0, cp->regs + REG_RX_COMP_TAIL);

	अगर (cp->cas_flags & CAS_FLAG_REG_PLUS) अणु
		अगर (N_RX_DESC_RINGS > 1)
			ग_लिखोl(RX_DESC_RINGN_SIZE(1) - 4,
			       cp->regs + REG_PLUS_RX_KICK1);

		क्रम (i = 1; i < N_RX_COMP_RINGS; i++)
			ग_लिखोl(0, cp->regs + REG_PLUS_RX_COMPN_TAIL(i));
	पूर्ण
पूर्ण

/* Must be invoked under cp->lock. */
अटल व्योम cas_पढ़ो_pcs_link_mode(काष्ठा cas *cp, पूर्णांक *fd, पूर्णांक *spd,
				   पूर्णांक *छोड़ो)
अणु
	u32 val = पढ़ोl(cp->regs + REG_PCS_MII_LPA);
	*fd     = (val & PCS_MII_LPA_FD) ? 1 : 0;
	*छोड़ो  = (val & PCS_MII_LPA_SYM_PAUSE) ? 0x01 : 0x00;
	अगर (val & PCS_MII_LPA_ASYM_PAUSE)
		*छोड़ो |= 0x10;
	*spd = 1000;
पूर्ण

/* Must be invoked under cp->lock. */
अटल व्योम cas_पढ़ो_mii_link_mode(काष्ठा cas *cp, पूर्णांक *fd, पूर्णांक *spd,
				   पूर्णांक *छोड़ो)
अणु
	u32 val;

	*fd = 0;
	*spd = 10;
	*छोड़ो = 0;

	/* use GMII रेजिस्टरs */
	val = cas_phy_पढ़ो(cp, MII_LPA);
	अगर (val & CAS_LPA_PAUSE)
		*छोड़ो = 0x01;

	अगर (val & CAS_LPA_ASYM_PAUSE)
		*छोड़ो |= 0x10;

	अगर (val & LPA_DUPLEX)
		*fd = 1;
	अगर (val & LPA_100)
		*spd = 100;

	अगर (cp->cas_flags & CAS_FLAG_1000MB_CAP) अणु
		val = cas_phy_पढ़ो(cp, CAS_MII_1000_STATUS);
		अगर (val & (CAS_LPA_1000FULL | CAS_LPA_1000HALF))
			*spd = 1000;
		अगर (val & CAS_LPA_1000FULL)
			*fd = 1;
	पूर्ण
पूर्ण

/* A link-up condition has occurred, initialize and enable the
 * rest of the chip.
 *
 * Must be invoked under cp->lock.
 */
अटल व्योम cas_set_link_modes(काष्ठा cas *cp)
अणु
	u32 val;
	पूर्णांक full_duplex, speed, छोड़ो;

	full_duplex = 0;
	speed = 10;
	छोड़ो = 0;

	अगर (CAS_PHY_MII(cp->phy_type)) अणु
		cas_mअगर_poll(cp, 0);
		val = cas_phy_पढ़ो(cp, MII_BMCR);
		अगर (val & BMCR_ANENABLE) अणु
			cas_पढ़ो_mii_link_mode(cp, &full_duplex, &speed,
					       &छोड़ो);
		पूर्ण अन्यथा अणु
			अगर (val & BMCR_FULLDPLX)
				full_duplex = 1;

			अगर (val & BMCR_SPEED100)
				speed = 100;
			अन्यथा अगर (val & CAS_BMCR_SPEED1000)
				speed = (cp->cas_flags & CAS_FLAG_1000MB_CAP) ?
					1000 : 100;
		पूर्ण
		cas_mअगर_poll(cp, 1);

	पूर्ण अन्यथा अणु
		val = पढ़ोl(cp->regs + REG_PCS_MII_CTRL);
		cas_पढ़ो_pcs_link_mode(cp, &full_duplex, &speed, &छोड़ो);
		अगर ((val & PCS_MII_AUTONEG_EN) == 0) अणु
			अगर (val & PCS_MII_CTRL_DUPLEX)
				full_duplex = 1;
		पूर्ण
	पूर्ण

	netअगर_info(cp, link, cp->dev, "Link up at %d Mbps, %s-duplex\n",
		   speed, full_duplex ? "full" : "half");

	val = MAC_XIF_TX_MII_OUTPUT_EN | MAC_XIF_LINK_LED;
	अगर (CAS_PHY_MII(cp->phy_type)) अणु
		val |= MAC_XIF_MII_BUFFER_OUTPUT_EN;
		अगर (!full_duplex)
			val |= MAC_XIF_DISABLE_ECHO;
	पूर्ण
	अगर (full_duplex)
		val |= MAC_XIF_FDPLX_LED;
	अगर (speed == 1000)
		val |= MAC_XIF_GMII_MODE;
	ग_लिखोl(val, cp->regs + REG_MAC_XIF_CFG);

	/* deal with carrier and collision detect. */
	val = MAC_TX_CFG_IPG_EN;
	अगर (full_duplex) अणु
		val |= MAC_TX_CFG_IGNORE_CARRIER;
		val |= MAC_TX_CFG_IGNORE_COLL;
	पूर्ण अन्यथा अणु
#अगर_अघोषित USE_CSMA_CD_PROTO
		val |= MAC_TX_CFG_NEVER_GIVE_UP_EN;
		val |= MAC_TX_CFG_NEVER_GIVE_UP_LIM;
#पूर्ण_अगर
	पूर्ण
	/* val now set up क्रम REG_MAC_TX_CFG */

	/* If gigabit and half-duplex, enable carrier extension
	 * mode.  increase slot समय to 512 bytes as well.
	 * अन्यथा, disable it and make sure slot समय is 64 bytes.
	 * also activate checksum bug workaround
	 */
	अगर ((speed == 1000) && !full_duplex) अणु
		ग_लिखोl(val | MAC_TX_CFG_CARRIER_EXTEND,
		       cp->regs + REG_MAC_TX_CFG);

		val = पढ़ोl(cp->regs + REG_MAC_RX_CFG);
		val &= ~MAC_RX_CFG_STRIP_FCS; /* checksum workaround */
		ग_लिखोl(val | MAC_RX_CFG_CARRIER_EXTEND,
		       cp->regs + REG_MAC_RX_CFG);

		ग_लिखोl(0x200, cp->regs + REG_MAC_SLOT_TIME);

		cp->crc_size = 4;
		/* minimum size gigabit frame at half duplex */
		cp->min_frame_size = CAS_1000MB_MIN_FRAME;

	पूर्ण अन्यथा अणु
		ग_लिखोl(val, cp->regs + REG_MAC_TX_CFG);

		/* checksum bug workaround. करोn't strip FCS when in
		 * half-duplex mode
		 */
		val = पढ़ोl(cp->regs + REG_MAC_RX_CFG);
		अगर (full_duplex) अणु
			val |= MAC_RX_CFG_STRIP_FCS;
			cp->crc_size = 0;
			cp->min_frame_size = CAS_MIN_MTU;
		पूर्ण अन्यथा अणु
			val &= ~MAC_RX_CFG_STRIP_FCS;
			cp->crc_size = 4;
			cp->min_frame_size = CAS_MIN_FRAME;
		पूर्ण
		ग_लिखोl(val & ~MAC_RX_CFG_CARRIER_EXTEND,
		       cp->regs + REG_MAC_RX_CFG);
		ग_लिखोl(0x40, cp->regs + REG_MAC_SLOT_TIME);
	पूर्ण

	अगर (netअगर_msg_link(cp)) अणु
		अगर (छोड़ो & 0x01) अणु
			netdev_info(cp->dev, "Pause is enabled (rxfifo: %d off: %d on: %d)\n",
				    cp->rx_fअगरo_size,
				    cp->rx_छोड़ो_off,
				    cp->rx_छोड़ो_on);
		पूर्ण अन्यथा अगर (छोड़ो & 0x10) अणु
			netdev_info(cp->dev, "TX pause enabled\n");
		पूर्ण अन्यथा अणु
			netdev_info(cp->dev, "Pause is disabled\n");
		पूर्ण
	पूर्ण

	val = पढ़ोl(cp->regs + REG_MAC_CTRL_CFG);
	val &= ~(MAC_CTRL_CFG_SEND_PAUSE_EN | MAC_CTRL_CFG_RECV_PAUSE_EN);
	अगर (छोड़ो) अणु /* symmetric or asymmetric छोड़ो */
		val |= MAC_CTRL_CFG_SEND_PAUSE_EN;
		अगर (छोड़ो & 0x01) अणु /* symmetric छोड़ो */
			val |= MAC_CTRL_CFG_RECV_PAUSE_EN;
		पूर्ण
	पूर्ण
	ग_लिखोl(val, cp->regs + REG_MAC_CTRL_CFG);
	cas_start_dma(cp);
पूर्ण

/* Must be invoked under cp->lock. */
अटल व्योम cas_init_hw(काष्ठा cas *cp, पूर्णांक restart_link)
अणु
	अगर (restart_link)
		cas_phy_init(cp);

	cas_init_छोड़ो_thresholds(cp);
	cas_init_mac(cp);
	cas_init_dma(cp);

	अगर (restart_link) अणु
		/* Default aneg parameters */
		cp->समयr_ticks = 0;
		cas_begin_स्वतः_negotiation(cp, शून्य);
	पूर्ण अन्यथा अगर (cp->lstate == link_up) अणु
		cas_set_link_modes(cp);
		netअगर_carrier_on(cp->dev);
	पूर्ण
पूर्ण

/* Must be invoked under cp->lock. on earlier cassini boards,
 * SOFT_0 is tied to PCI reset. we use this to क्रमce a pci reset,
 * let it settle out, and then restore pci state.
 */
अटल व्योम cas_hard_reset(काष्ठा cas *cp)
अणु
	ग_लिखोl(BIM_LOCAL_DEV_SOFT_0, cp->regs + REG_BIM_LOCAL_DEV_EN);
	udelay(20);
	pci_restore_state(cp->pdev);
पूर्ण


अटल व्योम cas_global_reset(काष्ठा cas *cp, पूर्णांक blkflag)
अणु
	पूर्णांक limit;

	/* issue a global reset. करोn't use RSTOUT. */
	अगर (blkflag && !CAS_PHY_MII(cp->phy_type)) अणु
		/* For PCS, when the blkflag is set, we should set the
		 * SW_REST_BLOCK_PCS_SLINK bit to prevent the results of
		 * the last स्वतःnegotiation from being cleared.  We'll
		 * need some special handling अगर the chip is set पूर्णांकo a
		 * loopback mode.
		 */
		ग_लिखोl((SW_RESET_TX | SW_RESET_RX | SW_RESET_BLOCK_PCS_SLINK),
		       cp->regs + REG_SW_RESET);
	पूर्ण अन्यथा अणु
		ग_लिखोl(SW_RESET_TX | SW_RESET_RX, cp->regs + REG_SW_RESET);
	पूर्ण

	/* need to रुको at least 3ms beक्रमe polling रेजिस्टर */
	mdelay(3);

	limit = STOP_TRIES;
	जबतक (limit-- > 0) अणु
		u32 val = पढ़ोl(cp->regs + REG_SW_RESET);
		अगर ((val & (SW_RESET_TX | SW_RESET_RX)) == 0)
			जाओ करोne;
		udelay(10);
	पूर्ण
	netdev_err(cp->dev, "sw reset failed\n");

करोne:
	/* enable various BIM पूर्णांकerrupts */
	ग_लिखोl(BIM_CFG_DPAR_INTR_ENABLE | BIM_CFG_RMA_INTR_ENABLE |
	       BIM_CFG_RTA_INTR_ENABLE, cp->regs + REG_BIM_CFG);

	/* clear out pci error status mask क्रम handled errors.
	 * we करोn't deal with DMA counter overflows as they happen
	 * all the समय.
	 */
	ग_लिखोl(0xFFFFFFFFU & ~(PCI_ERR_BADACK | PCI_ERR_DTRTO |
			       PCI_ERR_OTHER | PCI_ERR_BIM_DMA_WRITE |
			       PCI_ERR_BIM_DMA_READ), cp->regs +
	       REG_PCI_ERR_STATUS_MASK);

	/* set up क्रम MII by शेष to address mac rx reset समयout
	 * issue
	 */
	ग_लिखोl(PCS_DATAPATH_MODE_MII, cp->regs + REG_PCS_DATAPATH_MODE);
पूर्ण

अटल व्योम cas_reset(काष्ठा cas *cp, पूर्णांक blkflag)
अणु
	u32 val;

	cas_mask_पूर्णांकr(cp);
	cas_global_reset(cp, blkflag);
	cas_mac_reset(cp);
	cas_entropy_reset(cp);

	/* disable dma engines. */
	val = पढ़ोl(cp->regs + REG_TX_CFG);
	val &= ~TX_CFG_DMA_EN;
	ग_लिखोl(val, cp->regs + REG_TX_CFG);

	val = पढ़ोl(cp->regs + REG_RX_CFG);
	val &= ~RX_CFG_DMA_EN;
	ग_लिखोl(val, cp->regs + REG_RX_CFG);

	/* program header parser */
	अगर ((cp->cas_flags & CAS_FLAG_TARGET_ABORT) ||
	    (CAS_HP_ALT_FIRMWARE == cas_prog_null)) अणु
		cas_load_firmware(cp, CAS_HP_FIRMWARE);
	पूर्ण अन्यथा अणु
		cas_load_firmware(cp, CAS_HP_ALT_FIRMWARE);
	पूर्ण

	/* clear out error रेजिस्टरs */
	spin_lock(&cp->stat_lock[N_TX_RINGS]);
	cas_clear_mac_err(cp);
	spin_unlock(&cp->stat_lock[N_TX_RINGS]);
पूर्ण

/* Shut करोwn the chip, must be called with pm_mutex held.  */
अटल व्योम cas_shutकरोwn(काष्ठा cas *cp)
अणु
	अचिन्हित दीर्घ flags;

	/* Make us not-running to aव्योम समयrs respawning */
	cp->hw_running = 0;

	del_समयr_sync(&cp->link_समयr);

	/* Stop the reset task */
#अगर 0
	जबतक (atomic_पढ़ो(&cp->reset_task_pending_mtu) ||
	       atomic_पढ़ो(&cp->reset_task_pending_spare) ||
	       atomic_पढ़ो(&cp->reset_task_pending_all))
		schedule();

#अन्यथा
	जबतक (atomic_पढ़ो(&cp->reset_task_pending))
		schedule();
#पूर्ण_अगर
	/* Actually stop the chip */
	cas_lock_all_save(cp, flags);
	cas_reset(cp, 0);
	अगर (cp->cas_flags & CAS_FLAG_SATURN)
		cas_phy_घातerकरोwn(cp);
	cas_unlock_all_restore(cp, flags);
पूर्ण

अटल पूर्णांक cas_change_mtu(काष्ठा net_device *dev, पूर्णांक new_mtu)
अणु
	काष्ठा cas *cp = netdev_priv(dev);

	dev->mtu = new_mtu;
	अगर (!netअगर_running(dev) || !netअगर_device_present(dev))
		वापस 0;

	/* let the reset task handle it */
#अगर 1
	atomic_inc(&cp->reset_task_pending);
	अगर ((cp->phy_type & CAS_PHY_SERDES)) अणु
		atomic_inc(&cp->reset_task_pending_all);
	पूर्ण अन्यथा अणु
		atomic_inc(&cp->reset_task_pending_mtu);
	पूर्ण
	schedule_work(&cp->reset_task);
#अन्यथा
	atomic_set(&cp->reset_task_pending, (cp->phy_type & CAS_PHY_SERDES) ?
		   CAS_RESET_ALL : CAS_RESET_MTU);
	pr_err("reset called in cas_change_mtu\n");
	schedule_work(&cp->reset_task);
#पूर्ण_अगर

	flush_work(&cp->reset_task);
	वापस 0;
पूर्ण

अटल व्योम cas_clean_txd(काष्ठा cas *cp, पूर्णांक ring)
अणु
	काष्ठा cas_tx_desc *txd = cp->init_txds[ring];
	काष्ठा sk_buff *skb, **skbs = cp->tx_skbs[ring];
	u64 daddr, dlen;
	पूर्णांक i, size;

	size = TX_DESC_RINGN_SIZE(ring);
	क्रम (i = 0; i < size; i++) अणु
		पूर्णांक frag;

		अगर (skbs[i] == शून्य)
			जारी;

		skb = skbs[i];
		skbs[i] = शून्य;

		क्रम (frag = 0; frag <= skb_shinfo(skb)->nr_frags;  frag++) अणु
			पूर्णांक ent = i & (size - 1);

			/* first buffer is never a tiny buffer and so
			 * needs to be unmapped.
			 */
			daddr = le64_to_cpu(txd[ent].buffer);
			dlen  =  CAS_VAL(TX_DESC_BUFLEN,
					 le64_to_cpu(txd[ent].control));
			dma_unmap_page(&cp->pdev->dev, daddr, dlen,
				       DMA_TO_DEVICE);

			अगर (frag != skb_shinfo(skb)->nr_frags) अणु
				i++;

				/* next buffer might by a tiny buffer.
				 * skip past it.
				 */
				ent = i & (size - 1);
				अगर (cp->tx_tiny_use[ring][ent].used)
					i++;
			पूर्ण
		पूर्ण
		dev_kमुक्त_skb_any(skb);
	पूर्ण

	/* zero out tiny buf usage */
	स_रखो(cp->tx_tiny_use[ring], 0, size*माप(*cp->tx_tiny_use[ring]));
पूर्ण

/* मुक्तd on बंद */
अटल अंतरभूत व्योम cas_मुक्त_rx_desc(काष्ठा cas *cp, पूर्णांक ring)
अणु
	cas_page_t **page = cp->rx_pages[ring];
	पूर्णांक i, size;

	size = RX_DESC_RINGN_SIZE(ring);
	क्रम (i = 0; i < size; i++) अणु
		अगर (page[i]) अणु
			cas_page_मुक्त(cp, page[i]);
			page[i] = शून्य;
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम cas_मुक्त_rxds(काष्ठा cas *cp)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < N_RX_DESC_RINGS; i++)
		cas_मुक्त_rx_desc(cp, i);
पूर्ण

/* Must be invoked under cp->lock. */
अटल व्योम cas_clean_rings(काष्ठा cas *cp)
अणु
	पूर्णांक i;

	/* need to clean all tx rings */
	स_रखो(cp->tx_old, 0, माप(*cp->tx_old)*N_TX_RINGS);
	स_रखो(cp->tx_new, 0, माप(*cp->tx_new)*N_TX_RINGS);
	क्रम (i = 0; i < N_TX_RINGS; i++)
		cas_clean_txd(cp, i);

	/* zero out init block */
	स_रखो(cp->init_block, 0, माप(काष्ठा cas_init_block));
	cas_clean_rxds(cp);
	cas_clean_rxcs(cp);
पूर्ण

/* allocated on खोलो */
अटल अंतरभूत पूर्णांक cas_alloc_rx_desc(काष्ठा cas *cp, पूर्णांक ring)
अणु
	cas_page_t **page = cp->rx_pages[ring];
	पूर्णांक size, i = 0;

	size = RX_DESC_RINGN_SIZE(ring);
	क्रम (i = 0; i < size; i++) अणु
		अगर ((page[i] = cas_page_alloc(cp, GFP_KERNEL)) == शून्य)
			वापस -1;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक cas_alloc_rxds(काष्ठा cas *cp)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < N_RX_DESC_RINGS; i++) अणु
		अगर (cas_alloc_rx_desc(cp, i) < 0) अणु
			cas_मुक्त_rxds(cp);
			वापस -1;
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण

अटल व्योम cas_reset_task(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा cas *cp = container_of(work, काष्ठा cas, reset_task);
#अगर 0
	पूर्णांक pending = atomic_पढ़ो(&cp->reset_task_pending);
#अन्यथा
	पूर्णांक pending_all = atomic_पढ़ो(&cp->reset_task_pending_all);
	पूर्णांक pending_spare = atomic_पढ़ो(&cp->reset_task_pending_spare);
	पूर्णांक pending_mtu = atomic_पढ़ो(&cp->reset_task_pending_mtu);

	अगर (pending_all == 0 && pending_spare == 0 && pending_mtu == 0) अणु
		/* We can have more tasks scheduled than actually
		 * needed.
		 */
		atomic_dec(&cp->reset_task_pending);
		वापस;
	पूर्ण
#पूर्ण_अगर
	/* The link went करोwn, we reset the ring, but keep
	 * DMA stopped. Use this function क्रम reset
	 * on error as well.
	 */
	अगर (cp->hw_running) अणु
		अचिन्हित दीर्घ flags;

		/* Make sure we करोn't get पूर्णांकerrupts or tx packets */
		netअगर_device_detach(cp->dev);
		cas_lock_all_save(cp, flags);

		अगर (cp->खोलोed) अणु
			/* We call cas_spare_recover when we call cas_खोलो.
			 * but we करो not initialize the lists cas_spare_recover
			 * uses until cas_खोलो is called.
			 */
			cas_spare_recover(cp, GFP_ATOMIC);
		पूर्ण
#अगर 1
		/* test => only pending_spare set */
		अगर (!pending_all && !pending_mtu)
			जाओ करोne;
#अन्यथा
		अगर (pending == CAS_RESET_SPARE)
			जाओ करोne;
#पूर्ण_अगर
		/* when pending == CAS_RESET_ALL, the following
		 * call to cas_init_hw will restart स्वतः negotiation.
		 * Setting the second argument of cas_reset to
		 * !(pending == CAS_RESET_ALL) will set this argument
		 * to 1 (aव्योमing reinitializing the PHY क्रम the normal
		 * PCS हाल) when स्वतः negotiation is not restarted.
		 */
#अगर 1
		cas_reset(cp, !(pending_all > 0));
		अगर (cp->खोलोed)
			cas_clean_rings(cp);
		cas_init_hw(cp, (pending_all > 0));
#अन्यथा
		cas_reset(cp, !(pending == CAS_RESET_ALL));
		अगर (cp->खोलोed)
			cas_clean_rings(cp);
		cas_init_hw(cp, pending == CAS_RESET_ALL);
#पूर्ण_अगर

करोne:
		cas_unlock_all_restore(cp, flags);
		netअगर_device_attach(cp->dev);
	पूर्ण
#अगर 1
	atomic_sub(pending_all, &cp->reset_task_pending_all);
	atomic_sub(pending_spare, &cp->reset_task_pending_spare);
	atomic_sub(pending_mtu, &cp->reset_task_pending_mtu);
	atomic_dec(&cp->reset_task_pending);
#अन्यथा
	atomic_set(&cp->reset_task_pending, 0);
#पूर्ण_अगर
पूर्ण

अटल व्योम cas_link_समयr(काष्ठा समयr_list *t)
अणु
	काष्ठा cas *cp = from_समयr(cp, t, link_समयr);
	पूर्णांक mask, pending = 0, reset = 0;
	अचिन्हित दीर्घ flags;

	अगर (link_transition_समयout != 0 &&
	    cp->link_transition_jअगरfies_valid &&
	    ((jअगरfies - cp->link_transition_jअगरfies) >
	      (link_transition_समयout))) अणु
		/* One-second counter so link-करोwn workaround करोesn't
		 * cause resets to occur so fast as to fool the चयन
		 * पूर्णांकo thinking the link is करोwn.
		 */
		cp->link_transition_jअगरfies_valid = 0;
	पूर्ण

	अगर (!cp->hw_running)
		वापस;

	spin_lock_irqsave(&cp->lock, flags);
	cas_lock_tx(cp);
	cas_entropy_gather(cp);

	/* If the link task is still pending, we just
	 * reschedule the link समयr
	 */
#अगर 1
	अगर (atomic_पढ़ो(&cp->reset_task_pending_all) ||
	    atomic_पढ़ो(&cp->reset_task_pending_spare) ||
	    atomic_पढ़ो(&cp->reset_task_pending_mtu))
		जाओ करोne;
#अन्यथा
	अगर (atomic_पढ़ो(&cp->reset_task_pending))
		जाओ करोne;
#पूर्ण_अगर

	/* check क्रम rx cleaning */
	अगर ((mask = (cp->cas_flags & CAS_FLAG_RXD_POST_MASK))) अणु
		पूर्णांक i, rmask;

		क्रम (i = 0; i < MAX_RX_DESC_RINGS; i++) अणु
			rmask = CAS_FLAG_RXD_POST(i);
			अगर ((mask & rmask) == 0)
				जारी;

			/* post_rxds will करो a mod_समयr */
			अगर (cas_post_rxds_ringN(cp, i, cp->rx_last[i]) < 0) अणु
				pending = 1;
				जारी;
			पूर्ण
			cp->cas_flags &= ~rmask;
		पूर्ण
	पूर्ण

	अगर (CAS_PHY_MII(cp->phy_type)) अणु
		u16 bmsr;
		cas_mअगर_poll(cp, 0);
		bmsr = cas_phy_पढ़ो(cp, MII_BMSR);
		/* WTZ: Solaris driver पढ़ोs this twice, but that
		 * may be due to the PCS हाल and the use of a
		 * common implementation. Read it twice here to be
		 * safe.
		 */
		bmsr = cas_phy_पढ़ो(cp, MII_BMSR);
		cas_mअगर_poll(cp, 1);
		पढ़ोl(cp->regs + REG_MIF_STATUS); /* aव्योम dups */
		reset = cas_mii_link_check(cp, bmsr);
	पूर्ण अन्यथा अणु
		reset = cas_pcs_link_check(cp);
	पूर्ण

	अगर (reset)
		जाओ करोne;

	/* check क्रम tx state machine confusion */
	अगर ((पढ़ोl(cp->regs + REG_MAC_TX_STATUS) & MAC_TX_FRAME_XMIT) == 0) अणु
		u32 val = पढ़ोl(cp->regs + REG_MAC_STATE_MACHINE);
		u32 wptr, rptr;
		पूर्णांक tlm  = CAS_VAL(MAC_SM_TLM, val);

		अगर (((tlm == 0x5) || (tlm == 0x3)) &&
		    (CAS_VAL(MAC_SM_ENCAP_SM, val) == 0)) अणु
			netअगर_prपूर्णांकk(cp, tx_err, KERN_DEBUG, cp->dev,
				     "tx err: MAC_STATE[%08x]\n", val);
			reset = 1;
			जाओ करोne;
		पूर्ण

		val  = पढ़ोl(cp->regs + REG_TX_FIFO_PKT_CNT);
		wptr = पढ़ोl(cp->regs + REG_TX_FIFO_WRITE_PTR);
		rptr = पढ़ोl(cp->regs + REG_TX_FIFO_READ_PTR);
		अगर ((val == 0) && (wptr != rptr)) अणु
			netअगर_prपूर्णांकk(cp, tx_err, KERN_DEBUG, cp->dev,
				     "tx err: TX_FIFO[%08x:%08x:%08x]\n",
				     val, wptr, rptr);
			reset = 1;
		पूर्ण

		अगर (reset)
			cas_hard_reset(cp);
	पूर्ण

करोne:
	अगर (reset) अणु
#अगर 1
		atomic_inc(&cp->reset_task_pending);
		atomic_inc(&cp->reset_task_pending_all);
		schedule_work(&cp->reset_task);
#अन्यथा
		atomic_set(&cp->reset_task_pending, CAS_RESET_ALL);
		pr_err("reset called in cas_link_timer\n");
		schedule_work(&cp->reset_task);
#पूर्ण_अगर
	पूर्ण

	अगर (!pending)
		mod_समयr(&cp->link_समयr, jअगरfies + CAS_LINK_TIMEOUT);
	cas_unlock_tx(cp);
	spin_unlock_irqrestore(&cp->lock, flags);
पूर्ण

/* tiny buffers are used to aव्योम target पात issues with
 * older cassini's
 */
अटल व्योम cas_tx_tiny_मुक्त(काष्ठा cas *cp)
अणु
	काष्ठा pci_dev *pdev = cp->pdev;
	पूर्णांक i;

	क्रम (i = 0; i < N_TX_RINGS; i++) अणु
		अगर (!cp->tx_tiny_bufs[i])
			जारी;

		dma_मुक्त_coherent(&pdev->dev, TX_TINY_BUF_BLOCK,
				  cp->tx_tiny_bufs[i], cp->tx_tiny_dvma[i]);
		cp->tx_tiny_bufs[i] = शून्य;
	पूर्ण
पूर्ण

अटल पूर्णांक cas_tx_tiny_alloc(काष्ठा cas *cp)
अणु
	काष्ठा pci_dev *pdev = cp->pdev;
	पूर्णांक i;

	क्रम (i = 0; i < N_TX_RINGS; i++) अणु
		cp->tx_tiny_bufs[i] =
			dma_alloc_coherent(&pdev->dev, TX_TINY_BUF_BLOCK,
					   &cp->tx_tiny_dvma[i], GFP_KERNEL);
		अगर (!cp->tx_tiny_bufs[i]) अणु
			cas_tx_tiny_मुक्त(cp);
			वापस -1;
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण


अटल पूर्णांक cas_खोलो(काष्ठा net_device *dev)
अणु
	काष्ठा cas *cp = netdev_priv(dev);
	पूर्णांक hw_was_up, err;
	अचिन्हित दीर्घ flags;

	mutex_lock(&cp->pm_mutex);

	hw_was_up = cp->hw_running;

	/* The घातer-management mutex protects the hw_running
	 * etc. state so it is safe to करो this bit without cp->lock
	 */
	अगर (!cp->hw_running) अणु
		/* Reset the chip */
		cas_lock_all_save(cp, flags);
		/* We set the second arg to cas_reset to zero
		 * because cas_init_hw below will have its second
		 * argument set to non-zero, which will क्रमce
		 * स्वतःnegotiation to start.
		 */
		cas_reset(cp, 0);
		cp->hw_running = 1;
		cas_unlock_all_restore(cp, flags);
	पूर्ण

	err = -ENOMEM;
	अगर (cas_tx_tiny_alloc(cp) < 0)
		जाओ err_unlock;

	/* alloc rx descriptors */
	अगर (cas_alloc_rxds(cp) < 0)
		जाओ err_tx_tiny;

	/* allocate spares */
	cas_spare_init(cp);
	cas_spare_recover(cp, GFP_KERNEL);

	/* We can now request the पूर्णांकerrupt as we know it's masked
	 * on the controller. cassini+ has up to 4 पूर्णांकerrupts
	 * that can be used, but you need to करो explicit pci पूर्णांकerrupt
	 * mapping to expose them
	 */
	अगर (request_irq(cp->pdev->irq, cas_पूर्णांकerrupt,
			IRQF_SHARED, dev->name, (व्योम *) dev)) अणु
		netdev_err(cp->dev, "failed to request irq !\n");
		err = -EAGAIN;
		जाओ err_spare;
	पूर्ण

#अगर_घोषित USE_NAPI
	napi_enable(&cp->napi);
#पूर्ण_अगर
	/* init hw */
	cas_lock_all_save(cp, flags);
	cas_clean_rings(cp);
	cas_init_hw(cp, !hw_was_up);
	cp->खोलोed = 1;
	cas_unlock_all_restore(cp, flags);

	netअगर_start_queue(dev);
	mutex_unlock(&cp->pm_mutex);
	वापस 0;

err_spare:
	cas_spare_मुक्त(cp);
	cas_मुक्त_rxds(cp);
err_tx_tiny:
	cas_tx_tiny_मुक्त(cp);
err_unlock:
	mutex_unlock(&cp->pm_mutex);
	वापस err;
पूर्ण

अटल पूर्णांक cas_बंद(काष्ठा net_device *dev)
अणु
	अचिन्हित दीर्घ flags;
	काष्ठा cas *cp = netdev_priv(dev);

#अगर_घोषित USE_NAPI
	napi_disable(&cp->napi);
#पूर्ण_अगर
	/* Make sure we करोn't get distracted by suspend/resume */
	mutex_lock(&cp->pm_mutex);

	netअगर_stop_queue(dev);

	/* Stop traffic, mark us बंदd */
	cas_lock_all_save(cp, flags);
	cp->खोलोed = 0;
	cas_reset(cp, 0);
	cas_phy_init(cp);
	cas_begin_स्वतः_negotiation(cp, शून्य);
	cas_clean_rings(cp);
	cas_unlock_all_restore(cp, flags);

	मुक्त_irq(cp->pdev->irq, (व्योम *) dev);
	cas_spare_मुक्त(cp);
	cas_मुक्त_rxds(cp);
	cas_tx_tiny_मुक्त(cp);
	mutex_unlock(&cp->pm_mutex);
	वापस 0;
पूर्ण

अटल काष्ठा अणु
	स्थिर अक्षर name[ETH_GSTRING_LEN];
पूर्ण ethtool_cassini_statnames[] = अणु
	अणु"collisions"पूर्ण,
	अणु"rx_bytes"पूर्ण,
	अणु"rx_crc_errors"पूर्ण,
	अणु"rx_dropped"पूर्ण,
	अणु"rx_errors"पूर्ण,
	अणु"rx_fifo_errors"पूर्ण,
	अणु"rx_frame_errors"पूर्ण,
	अणु"rx_length_errors"पूर्ण,
	अणु"rx_over_errors"पूर्ण,
	अणु"rx_packets"पूर्ण,
	अणु"tx_aborted_errors"पूर्ण,
	अणु"tx_bytes"पूर्ण,
	अणु"tx_dropped"पूर्ण,
	अणु"tx_errors"पूर्ण,
	अणु"tx_fifo_errors"पूर्ण,
	अणु"tx_packets"पूर्ण
पूर्ण;
#घोषणा CAS_NUM_STAT_KEYS ARRAY_SIZE(ethtool_cassini_statnames)

अटल काष्ठा अणु
	स्थिर पूर्णांक offsets;	/* neg. values क्रम 2nd arg to cas_पढ़ो_phy */
पूर्ण ethtool_रेजिस्टर_table[] = अणु
	अणु-MII_BMSRपूर्ण,
	अणु-MII_BMCRपूर्ण,
	अणुREG_CAWRपूर्ण,
	अणुREG_INF_BURSTपूर्ण,
	अणुREG_BIM_CFGपूर्ण,
	अणुREG_RX_CFGपूर्ण,
	अणुREG_HP_CFGपूर्ण,
	अणुREG_MAC_TX_CFGपूर्ण,
	अणुREG_MAC_RX_CFGपूर्ण,
	अणुREG_MAC_CTRL_CFGपूर्ण,
	अणुREG_MAC_XIF_CFGपूर्ण,
	अणुREG_MIF_CFGपूर्ण,
	अणुREG_PCS_CFGपूर्ण,
	अणुREG_SATURN_PCFGपूर्ण,
	अणुREG_PCS_MII_STATUSपूर्ण,
	अणुREG_PCS_STATE_MACHINEपूर्ण,
	अणुREG_MAC_COLL_EXCESSपूर्ण,
	अणुREG_MAC_COLL_LATEपूर्ण
पूर्ण;
#घोषणा CAS_REG_LEN 	ARRAY_SIZE(ethtool_रेजिस्टर_table)
#घोषणा CAS_MAX_REGS 	(माप (u32)*CAS_REG_LEN)

अटल व्योम cas_पढ़ो_regs(काष्ठा cas *cp, u8 *ptr, पूर्णांक len)
अणु
	u8 *p;
	पूर्णांक i;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&cp->lock, flags);
	क्रम (i = 0, p = ptr; i < len ; i ++, p += माप(u32)) अणु
		u16 hval;
		u32 val;
		अगर (ethtool_रेजिस्टर_table[i].offsets < 0) अणु
			hval = cas_phy_पढ़ो(cp,
				    -ethtool_रेजिस्टर_table[i].offsets);
			val = hval;
		पूर्ण अन्यथा अणु
			val= पढ़ोl(cp->regs+ethtool_रेजिस्टर_table[i].offsets);
		पूर्ण
		स_नकल(p, (u8 *)&val, माप(u32));
	पूर्ण
	spin_unlock_irqrestore(&cp->lock, flags);
पूर्ण

अटल काष्ठा net_device_stats *cas_get_stats(काष्ठा net_device *dev)
अणु
	काष्ठा cas *cp = netdev_priv(dev);
	काष्ठा net_device_stats *stats = cp->net_stats;
	अचिन्हित दीर्घ flags;
	पूर्णांक i;
	अचिन्हित दीर्घ पंचांगp;

	/* we collate all of the stats पूर्णांकo net_stats[N_TX_RING] */
	अगर (!cp->hw_running)
		वापस stats + N_TX_RINGS;

	/* collect outstanding stats */
	/* WTZ: the Cassini spec gives these as 16 bit counters but
	 * stored in 32-bit words.  Added a mask of 0xffff to be safe,
	 * in हाल the chip somehow माला_दो any garbage in the other bits.
	 * Also, counter usage didn't seem to mach what Adrian did
	 * in the parts of the code that set these quantities. Made
	 * that consistent.
	 */
	spin_lock_irqsave(&cp->stat_lock[N_TX_RINGS], flags);
	stats[N_TX_RINGS].rx_crc_errors +=
	  पढ़ोl(cp->regs + REG_MAC_FCS_ERR) & 0xffff;
	stats[N_TX_RINGS].rx_frame_errors +=
		पढ़ोl(cp->regs + REG_MAC_ALIGN_ERR) &0xffff;
	stats[N_TX_RINGS].rx_length_errors +=
		पढ़ोl(cp->regs + REG_MAC_LEN_ERR) & 0xffff;
#अगर 1
	पंचांगp = (पढ़ोl(cp->regs + REG_MAC_COLL_EXCESS) & 0xffff) +
		(पढ़ोl(cp->regs + REG_MAC_COLL_LATE) & 0xffff);
	stats[N_TX_RINGS].tx_पातed_errors += पंचांगp;
	stats[N_TX_RINGS].collisions +=
	  पंचांगp + (पढ़ोl(cp->regs + REG_MAC_COLL_NORMAL) & 0xffff);
#अन्यथा
	stats[N_TX_RINGS].tx_पातed_errors +=
		पढ़ोl(cp->regs + REG_MAC_COLL_EXCESS);
	stats[N_TX_RINGS].collisions += पढ़ोl(cp->regs + REG_MAC_COLL_EXCESS) +
		पढ़ोl(cp->regs + REG_MAC_COLL_LATE);
#पूर्ण_अगर
	cas_clear_mac_err(cp);

	/* saved bits that are unique to ring 0 */
	spin_lock(&cp->stat_lock[0]);
	stats[N_TX_RINGS].collisions        += stats[0].collisions;
	stats[N_TX_RINGS].rx_over_errors    += stats[0].rx_over_errors;
	stats[N_TX_RINGS].rx_frame_errors   += stats[0].rx_frame_errors;
	stats[N_TX_RINGS].rx_fअगरo_errors    += stats[0].rx_fअगरo_errors;
	stats[N_TX_RINGS].tx_पातed_errors += stats[0].tx_पातed_errors;
	stats[N_TX_RINGS].tx_fअगरo_errors    += stats[0].tx_fअगरo_errors;
	spin_unlock(&cp->stat_lock[0]);

	क्रम (i = 0; i < N_TX_RINGS; i++) अणु
		spin_lock(&cp->stat_lock[i]);
		stats[N_TX_RINGS].rx_length_errors +=
			stats[i].rx_length_errors;
		stats[N_TX_RINGS].rx_crc_errors += stats[i].rx_crc_errors;
		stats[N_TX_RINGS].rx_packets    += stats[i].rx_packets;
		stats[N_TX_RINGS].tx_packets    += stats[i].tx_packets;
		stats[N_TX_RINGS].rx_bytes      += stats[i].rx_bytes;
		stats[N_TX_RINGS].tx_bytes      += stats[i].tx_bytes;
		stats[N_TX_RINGS].rx_errors     += stats[i].rx_errors;
		stats[N_TX_RINGS].tx_errors     += stats[i].tx_errors;
		stats[N_TX_RINGS].rx_dropped    += stats[i].rx_dropped;
		stats[N_TX_RINGS].tx_dropped    += stats[i].tx_dropped;
		स_रखो(stats + i, 0, माप(काष्ठा net_device_stats));
		spin_unlock(&cp->stat_lock[i]);
	पूर्ण
	spin_unlock_irqrestore(&cp->stat_lock[N_TX_RINGS], flags);
	वापस stats + N_TX_RINGS;
पूर्ण


अटल व्योम cas_set_multicast(काष्ठा net_device *dev)
अणु
	काष्ठा cas *cp = netdev_priv(dev);
	u32 rxcfg, rxcfg_new;
	अचिन्हित दीर्घ flags;
	पूर्णांक limit = STOP_TRIES;

	अगर (!cp->hw_running)
		वापस;

	spin_lock_irqsave(&cp->lock, flags);
	rxcfg = पढ़ोl(cp->regs + REG_MAC_RX_CFG);

	/* disable RX MAC and रुको क्रम completion */
	ग_लिखोl(rxcfg & ~MAC_RX_CFG_EN, cp->regs + REG_MAC_RX_CFG);
	जबतक (पढ़ोl(cp->regs + REG_MAC_RX_CFG) & MAC_RX_CFG_EN) अणु
		अगर (!limit--)
			अवरोध;
		udelay(10);
	पूर्ण

	/* disable hash filter and रुको क्रम completion */
	limit = STOP_TRIES;
	rxcfg &= ~(MAC_RX_CFG_PROMISC_EN | MAC_RX_CFG_HASH_FILTER_EN);
	ग_लिखोl(rxcfg & ~MAC_RX_CFG_EN, cp->regs + REG_MAC_RX_CFG);
	जबतक (पढ़ोl(cp->regs + REG_MAC_RX_CFG) & MAC_RX_CFG_HASH_FILTER_EN) अणु
		अगर (!limit--)
			अवरोध;
		udelay(10);
	पूर्ण

	/* program hash filters */
	cp->mac_rx_cfg = rxcfg_new = cas_setup_multicast(cp);
	rxcfg |= rxcfg_new;
	ग_लिखोl(rxcfg, cp->regs + REG_MAC_RX_CFG);
	spin_unlock_irqrestore(&cp->lock, flags);
पूर्ण

अटल व्योम cas_get_drvinfo(काष्ठा net_device *dev, काष्ठा ethtool_drvinfo *info)
अणु
	काष्ठा cas *cp = netdev_priv(dev);
	strlcpy(info->driver, DRV_MODULE_NAME, माप(info->driver));
	strlcpy(info->version, DRV_MODULE_VERSION, माप(info->version));
	strlcpy(info->bus_info, pci_name(cp->pdev), माप(info->bus_info));
पूर्ण

अटल पूर्णांक cas_get_link_ksettings(काष्ठा net_device *dev,
				  काष्ठा ethtool_link_ksettings *cmd)
अणु
	काष्ठा cas *cp = netdev_priv(dev);
	u16 bmcr;
	पूर्णांक full_duplex, speed, छोड़ो;
	अचिन्हित दीर्घ flags;
	क्रमागत link_state linkstate = link_up;
	u32 supported, advertising;

	advertising = 0;
	supported = SUPPORTED_Autoneg;
	अगर (cp->cas_flags & CAS_FLAG_1000MB_CAP) अणु
		supported |= SUPPORTED_1000baseT_Full;
		advertising |= ADVERTISED_1000baseT_Full;
	पूर्ण

	/* Record PHY settings अगर HW is on. */
	spin_lock_irqsave(&cp->lock, flags);
	bmcr = 0;
	linkstate = cp->lstate;
	अगर (CAS_PHY_MII(cp->phy_type)) अणु
		cmd->base.port = PORT_MII;
		cmd->base.phy_address = cp->phy_addr;
		advertising |= ADVERTISED_TP | ADVERTISED_MII |
			ADVERTISED_10baseT_Half |
			ADVERTISED_10baseT_Full |
			ADVERTISED_100baseT_Half |
			ADVERTISED_100baseT_Full;

		supported |=
			(SUPPORTED_10baseT_Half |
			 SUPPORTED_10baseT_Full |
			 SUPPORTED_100baseT_Half |
			 SUPPORTED_100baseT_Full |
			 SUPPORTED_TP | SUPPORTED_MII);

		अगर (cp->hw_running) अणु
			cas_mअगर_poll(cp, 0);
			bmcr = cas_phy_पढ़ो(cp, MII_BMCR);
			cas_पढ़ो_mii_link_mode(cp, &full_duplex,
					       &speed, &छोड़ो);
			cas_mअगर_poll(cp, 1);
		पूर्ण

	पूर्ण अन्यथा अणु
		cmd->base.port = PORT_FIBRE;
		cmd->base.phy_address = 0;
		supported   |= SUPPORTED_FIBRE;
		advertising |= ADVERTISED_FIBRE;

		अगर (cp->hw_running) अणु
			/* pcs uses the same bits as mii */
			bmcr = पढ़ोl(cp->regs + REG_PCS_MII_CTRL);
			cas_पढ़ो_pcs_link_mode(cp, &full_duplex,
					       &speed, &छोड़ो);
		पूर्ण
	पूर्ण
	spin_unlock_irqrestore(&cp->lock, flags);

	अगर (bmcr & BMCR_ANENABLE) अणु
		advertising |= ADVERTISED_Autoneg;
		cmd->base.स्वतःneg = AUTONEG_ENABLE;
		cmd->base.speed =  ((speed == 10) ?
					    SPEED_10 :
					    ((speed == 1000) ?
					     SPEED_1000 : SPEED_100));
		cmd->base.duplex = full_duplex ? DUPLEX_FULL : DUPLEX_HALF;
	पूर्ण अन्यथा अणु
		cmd->base.स्वतःneg = AUTONEG_DISABLE;
		cmd->base.speed = ((bmcr & CAS_BMCR_SPEED1000) ?
					    SPEED_1000 :
					    ((bmcr & BMCR_SPEED100) ?
					     SPEED_100 : SPEED_10));
		cmd->base.duplex = (bmcr & BMCR_FULLDPLX) ?
			DUPLEX_FULL : DUPLEX_HALF;
	पूर्ण
	अगर (linkstate != link_up) अणु
		/* Force these to "unknown" अगर the link is not up and
		 * स्वतःnogotiation in enabled. We can set the link
		 * speed to 0, but not cmd->duplex,
		 * because its legal values are 0 and 1.  Ethtool will
		 * prपूर्णांक the value reported in parentheses after the
		 * word "Unknown" क्रम unrecognized values.
		 *
		 * If in क्रमced mode, we report the speed and duplex
		 * settings that we configured.
		 */
		अगर (cp->link_cntl & BMCR_ANENABLE) अणु
			cmd->base.speed = 0;
			cmd->base.duplex = 0xff;
		पूर्ण अन्यथा अणु
			cmd->base.speed = SPEED_10;
			अगर (cp->link_cntl & BMCR_SPEED100) अणु
				cmd->base.speed = SPEED_100;
			पूर्ण अन्यथा अगर (cp->link_cntl & CAS_BMCR_SPEED1000) अणु
				cmd->base.speed = SPEED_1000;
			पूर्ण
			cmd->base.duplex = (cp->link_cntl & BMCR_FULLDPLX) ?
				DUPLEX_FULL : DUPLEX_HALF;
		पूर्ण
	पूर्ण

	ethtool_convert_legacy_u32_to_link_mode(cmd->link_modes.supported,
						supported);
	ethtool_convert_legacy_u32_to_link_mode(cmd->link_modes.advertising,
						advertising);

	वापस 0;
पूर्ण

अटल पूर्णांक cas_set_link_ksettings(काष्ठा net_device *dev,
				  स्थिर काष्ठा ethtool_link_ksettings *cmd)
अणु
	काष्ठा cas *cp = netdev_priv(dev);
	अचिन्हित दीर्घ flags;
	u32 speed = cmd->base.speed;

	/* Verअगरy the settings we care about. */
	अगर (cmd->base.स्वतःneg != AUTONEG_ENABLE &&
	    cmd->base.स्वतःneg != AUTONEG_DISABLE)
		वापस -EINVAL;

	अगर (cmd->base.स्वतःneg == AUTONEG_DISABLE &&
	    ((speed != SPEED_1000 &&
	      speed != SPEED_100 &&
	      speed != SPEED_10) ||
	     (cmd->base.duplex != DUPLEX_HALF &&
	      cmd->base.duplex != DUPLEX_FULL)))
		वापस -EINVAL;

	/* Apply settings and restart link process. */
	spin_lock_irqsave(&cp->lock, flags);
	cas_begin_स्वतः_negotiation(cp, cmd);
	spin_unlock_irqrestore(&cp->lock, flags);
	वापस 0;
पूर्ण

अटल पूर्णांक cas_nway_reset(काष्ठा net_device *dev)
अणु
	काष्ठा cas *cp = netdev_priv(dev);
	अचिन्हित दीर्घ flags;

	अगर ((cp->link_cntl & BMCR_ANENABLE) == 0)
		वापस -EINVAL;

	/* Restart link process. */
	spin_lock_irqsave(&cp->lock, flags);
	cas_begin_स्वतः_negotiation(cp, शून्य);
	spin_unlock_irqrestore(&cp->lock, flags);

	वापस 0;
पूर्ण

अटल u32 cas_get_link(काष्ठा net_device *dev)
अणु
	काष्ठा cas *cp = netdev_priv(dev);
	वापस cp->lstate == link_up;
पूर्ण

अटल u32 cas_get_msglevel(काष्ठा net_device *dev)
अणु
	काष्ठा cas *cp = netdev_priv(dev);
	वापस cp->msg_enable;
पूर्ण

अटल व्योम cas_set_msglevel(काष्ठा net_device *dev, u32 value)
अणु
	काष्ठा cas *cp = netdev_priv(dev);
	cp->msg_enable = value;
पूर्ण

अटल पूर्णांक cas_get_regs_len(काष्ठा net_device *dev)
अणु
	काष्ठा cas *cp = netdev_priv(dev);
	वापस cp->casreg_len < CAS_MAX_REGS ? cp->casreg_len: CAS_MAX_REGS;
पूर्ण

अटल व्योम cas_get_regs(काष्ठा net_device *dev, काष्ठा ethtool_regs *regs,
			     व्योम *p)
अणु
	काष्ठा cas *cp = netdev_priv(dev);
	regs->version = 0;
	/* cas_पढ़ो_regs handles locks (cp->lock).  */
	cas_पढ़ो_regs(cp, p, regs->len / माप(u32));
पूर्ण

अटल पूर्णांक cas_get_sset_count(काष्ठा net_device *dev, पूर्णांक sset)
अणु
	चयन (sset) अणु
	हाल ETH_SS_STATS:
		वापस CAS_NUM_STAT_KEYS;
	शेष:
		वापस -EOPNOTSUPP;
	पूर्ण
पूर्ण

अटल व्योम cas_get_strings(काष्ठा net_device *dev, u32 stringset, u8 *data)
अणु
	 स_नकल(data, &ethtool_cassini_statnames,
					 CAS_NUM_STAT_KEYS * ETH_GSTRING_LEN);
पूर्ण

अटल व्योम cas_get_ethtool_stats(काष्ठा net_device *dev,
				      काष्ठा ethtool_stats *estats, u64 *data)
अणु
	काष्ठा cas *cp = netdev_priv(dev);
	काष्ठा net_device_stats *stats = cas_get_stats(cp->dev);
	पूर्णांक i = 0;
	data[i++] = stats->collisions;
	data[i++] = stats->rx_bytes;
	data[i++] = stats->rx_crc_errors;
	data[i++] = stats->rx_dropped;
	data[i++] = stats->rx_errors;
	data[i++] = stats->rx_fअगरo_errors;
	data[i++] = stats->rx_frame_errors;
	data[i++] = stats->rx_length_errors;
	data[i++] = stats->rx_over_errors;
	data[i++] = stats->rx_packets;
	data[i++] = stats->tx_पातed_errors;
	data[i++] = stats->tx_bytes;
	data[i++] = stats->tx_dropped;
	data[i++] = stats->tx_errors;
	data[i++] = stats->tx_fअगरo_errors;
	data[i++] = stats->tx_packets;
	BUG_ON(i != CAS_NUM_STAT_KEYS);
पूर्ण

अटल स्थिर काष्ठा ethtool_ops cas_ethtool_ops = अणु
	.get_drvinfo		= cas_get_drvinfo,
	.nway_reset		= cas_nway_reset,
	.get_link		= cas_get_link,
	.get_msglevel		= cas_get_msglevel,
	.set_msglevel		= cas_set_msglevel,
	.get_regs_len		= cas_get_regs_len,
	.get_regs		= cas_get_regs,
	.get_sset_count		= cas_get_sset_count,
	.get_strings		= cas_get_strings,
	.get_ethtool_stats	= cas_get_ethtool_stats,
	.get_link_ksettings	= cas_get_link_ksettings,
	.set_link_ksettings	= cas_set_link_ksettings,
पूर्ण;

अटल पूर्णांक cas_ioctl(काष्ठा net_device *dev, काष्ठा अगरreq *अगरr, पूर्णांक cmd)
अणु
	काष्ठा cas *cp = netdev_priv(dev);
	काष्ठा mii_ioctl_data *data = अगर_mii(अगरr);
	अचिन्हित दीर्घ flags;
	पूर्णांक rc = -EOPNOTSUPP;

	/* Hold the PM mutex जबतक करोing ioctl's or we may collide
	 * with खोलो/बंद and घातer management and oops.
	 */
	mutex_lock(&cp->pm_mutex);
	चयन (cmd) अणु
	हाल SIOCGMIIPHY:		/* Get address of MII PHY in use. */
		data->phy_id = cp->phy_addr;
		fallthrough;

	हाल SIOCGMIIREG:		/* Read MII PHY रेजिस्टर. */
		spin_lock_irqsave(&cp->lock, flags);
		cas_mअगर_poll(cp, 0);
		data->val_out = cas_phy_पढ़ो(cp, data->reg_num & 0x1f);
		cas_mअगर_poll(cp, 1);
		spin_unlock_irqrestore(&cp->lock, flags);
		rc = 0;
		अवरोध;

	हाल SIOCSMIIREG:		/* Write MII PHY रेजिस्टर. */
		spin_lock_irqsave(&cp->lock, flags);
		cas_mअगर_poll(cp, 0);
		rc = cas_phy_ग_लिखो(cp, data->reg_num & 0x1f, data->val_in);
		cas_mअगर_poll(cp, 1);
		spin_unlock_irqrestore(&cp->lock, flags);
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	mutex_unlock(&cp->pm_mutex);
	वापस rc;
पूर्ण

/* When this chip sits underneath an Intel 31154 bridge, it is the
 * only subordinate device and we can tweak the bridge settings to
 * reflect that fact.
 */
अटल व्योम cas_program_bridge(काष्ठा pci_dev *cas_pdev)
अणु
	काष्ठा pci_dev *pdev = cas_pdev->bus->self;
	u32 val;

	अगर (!pdev)
		वापस;

	अगर (pdev->venकरोr != 0x8086 || pdev->device != 0x537c)
		वापस;

	/* Clear bit 10 (Bus Parking Control) in the Secondary
	 * Arbiter Control/Status Register which lives at offset
	 * 0x41.  Using a 32-bit word पढ़ो/modअगरy/ग_लिखो at 0x40
	 * is much simpler so that's how we करो this.
	 */
	pci_पढ़ो_config_dword(pdev, 0x40, &val);
	val &= ~0x00040000;
	pci_ग_लिखो_config_dword(pdev, 0x40, val);

	/* Max out the Multi-Transaction Timer settings since
	 * Cassini is the only device present.
	 *
	 * The रेजिस्टर is 16-bit and lives at 0x50.  When the
	 * settings are enabled, it extends the GRANT# संकेत
	 * क्रम a requestor after a transaction is complete.  This
	 * allows the next request to run without first needing
	 * to negotiate the GRANT# संकेत back.
	 *
	 * Bits 12:10 define the grant duration:
	 *
	 *	1	--	16 घड़ीs
	 *	2	--	32 घड़ीs
	 *	3	--	64 घड़ीs
	 *	4	--	128 घड़ीs
	 *	5	--	256 घड़ीs
	 *
	 * All other values are illegal.
	 *
	 * Bits 09:00 define which REQ/GNT संकेत pairs get the
	 * GRANT# संकेत treaपंचांगent.  We set them all.
	 */
	pci_ग_लिखो_config_word(pdev, 0x50, (5 << 10) | 0x3ff);

	/* The Read Prefecth Policy रेजिस्टर is 16-bit and sits at
	 * offset 0x52.  It enables a "smart" pre-fetch policy.  We
	 * enable it and max out all of the settings since only one
	 * device is sitting underneath and thus bandwidth sharing is
	 * not an issue.
	 *
	 * The रेजिस्टर has several 3 bit fields, which indicates a
	 * multiplier applied to the base amount of prefetching the
	 * chip would करो.  These fields are at:
	 *
	 *	15:13	---	ReRead Primary Bus
	 *	12:10	---	FirstRead Primary Bus
	 *	09:07	---	ReRead Secondary Bus
	 *	06:04	---	FirstRead Secondary Bus
	 *
	 * Bits 03:00 control which REQ/GNT pairs the prefetch settings
	 * get enabled on.  Bit 3 is a grouped enabler which controls
	 * all of the REQ/GNT pairs from [8:3].  Bits 2 to 0 control
	 * the inभागidual REQ/GNT pairs [2:0].
	 */
	pci_ग_लिखो_config_word(pdev, 0x52,
			      (0x7 << 13) |
			      (0x7 << 10) |
			      (0x7 <<  7) |
			      (0x7 <<  4) |
			      (0xf <<  0));

	/* Force cacheline size to 0x8 */
	pci_ग_लिखो_config_byte(pdev, PCI_CACHE_LINE_SIZE, 0x08);

	/* Force latency समयr to maximum setting so Cassini can
	 * sit on the bus as दीर्घ as it likes.
	 */
	pci_ग_लिखो_config_byte(pdev, PCI_LATENCY_TIMER, 0xff);
पूर्ण

अटल स्थिर काष्ठा net_device_ops cas_netdev_ops = अणु
	.nकरो_खोलो		= cas_खोलो,
	.nकरो_stop		= cas_बंद,
	.nकरो_start_xmit		= cas_start_xmit,
	.nकरो_get_stats 		= cas_get_stats,
	.nकरो_set_rx_mode	= cas_set_multicast,
	.nकरो_करो_ioctl		= cas_ioctl,
	.nकरो_tx_समयout		= cas_tx_समयout,
	.nकरो_change_mtu		= cas_change_mtu,
	.nकरो_set_mac_address	= eth_mac_addr,
	.nकरो_validate_addr	= eth_validate_addr,
#अगर_घोषित CONFIG_NET_POLL_CONTROLLER
	.nकरो_poll_controller	= cas_netpoll,
#पूर्ण_अगर
पूर्ण;

अटल पूर्णांक cas_init_one(काष्ठा pci_dev *pdev, स्थिर काष्ठा pci_device_id *ent)
अणु
	अटल पूर्णांक cas_version_prपूर्णांकed = 0;
	अचिन्हित दीर्घ casreg_len;
	काष्ठा net_device *dev;
	काष्ठा cas *cp;
	पूर्णांक i, err, pci_using_dac;
	u16 pci_cmd;
	u8 orig_cacheline_size = 0, cas_cacheline_size = 0;

	अगर (cas_version_prपूर्णांकed++ == 0)
		pr_info("%s", version);

	err = pci_enable_device(pdev);
	अगर (err) अणु
		dev_err(&pdev->dev, "Cannot enable PCI device, aborting\n");
		वापस err;
	पूर्ण

	अगर (!(pci_resource_flags(pdev, 0) & IORESOURCE_MEM)) अणु
		dev_err(&pdev->dev, "Cannot find proper PCI device "
		       "base address, aborting\n");
		err = -ENODEV;
		जाओ err_out_disable_pdev;
	पूर्ण

	dev = alloc_etherdev(माप(*cp));
	अगर (!dev) अणु
		err = -ENOMEM;
		जाओ err_out_disable_pdev;
	पूर्ण
	SET_NETDEV_DEV(dev, &pdev->dev);

	err = pci_request_regions(pdev, dev->name);
	अगर (err) अणु
		dev_err(&pdev->dev, "Cannot obtain PCI resources, aborting\n");
		जाओ err_out_मुक्त_netdev;
	पूर्ण
	pci_set_master(pdev);

	/* we must always turn on parity response or अन्यथा parity
	 * करोesn't get generated properly. disable SERR/PERR as well.
	 * in addition, we want to turn MWI on.
	 */
	pci_पढ़ो_config_word(pdev, PCI_COMMAND, &pci_cmd);
	pci_cmd &= ~PCI_COMMAND_SERR;
	pci_cmd |= PCI_COMMAND_PARITY;
	pci_ग_लिखो_config_word(pdev, PCI_COMMAND, pci_cmd);
	अगर (pci_try_set_mwi(pdev))
		pr_warn("Could not enable MWI for %s\n", pci_name(pdev));

	cas_program_bridge(pdev);

	/*
	 * On some architectures, the शेष cache line size set
	 * by pci_try_set_mwi reduces perक्रमamnce.  We have to increase
	 * it क्रम this हाल.  To start, we'll prपूर्णांक some configuration
	 * data.
	 */
#अगर 1
	pci_पढ़ो_config_byte(pdev, PCI_CACHE_LINE_SIZE,
			     &orig_cacheline_size);
	अगर (orig_cacheline_size < CAS_PREF_CACHELINE_SIZE) अणु
		cas_cacheline_size =
			(CAS_PREF_CACHELINE_SIZE < SMP_CACHE_BYTES) ?
			CAS_PREF_CACHELINE_SIZE : SMP_CACHE_BYTES;
		अगर (pci_ग_लिखो_config_byte(pdev,
					  PCI_CACHE_LINE_SIZE,
					  cas_cacheline_size)) अणु
			dev_err(&pdev->dev, "Could not set PCI cache "
			       "line size\n");
			जाओ err_out_मुक्त_res;
		पूर्ण
	पूर्ण
#पूर्ण_अगर


	/* Configure DMA attributes. */
	अगर (!dma_set_mask(&pdev->dev, DMA_BIT_MASK(64))) अणु
		pci_using_dac = 1;
		err = dma_set_coherent_mask(&pdev->dev, DMA_BIT_MASK(64));
		अगर (err < 0) अणु
			dev_err(&pdev->dev, "Unable to obtain 64-bit DMA "
			       "for consistent allocations\n");
			जाओ err_out_मुक्त_res;
		पूर्ण

	पूर्ण अन्यथा अणु
		err = dma_set_mask(&pdev->dev, DMA_BIT_MASK(32));
		अगर (err) अणु
			dev_err(&pdev->dev, "No usable DMA configuration, "
			       "aborting\n");
			जाओ err_out_मुक्त_res;
		पूर्ण
		pci_using_dac = 0;
	पूर्ण

	casreg_len = pci_resource_len(pdev, 0);

	cp = netdev_priv(dev);
	cp->pdev = pdev;
#अगर 1
	/* A value of 0 indicates we never explicitly set it */
	cp->orig_cacheline_size = cas_cacheline_size ? orig_cacheline_size: 0;
#पूर्ण_अगर
	cp->dev = dev;
	cp->msg_enable = (cassini_debug < 0) ? CAS_DEF_MSG_ENABLE :
	  cassini_debug;

#अगर defined(CONFIG_SPARC)
	cp->of_node = pci_device_to_OF_node(pdev);
#पूर्ण_अगर

	cp->link_transition = LINK_TRANSITION_UNKNOWN;
	cp->link_transition_jअगरfies_valid = 0;

	spin_lock_init(&cp->lock);
	spin_lock_init(&cp->rx_inuse_lock);
	spin_lock_init(&cp->rx_spare_lock);
	क्रम (i = 0; i < N_TX_RINGS; i++) अणु
		spin_lock_init(&cp->stat_lock[i]);
		spin_lock_init(&cp->tx_lock[i]);
	पूर्ण
	spin_lock_init(&cp->stat_lock[N_TX_RINGS]);
	mutex_init(&cp->pm_mutex);

	समयr_setup(&cp->link_समयr, cas_link_समयr, 0);

#अगर 1
	/* Just in हाल the implementation of atomic operations
	 * change so that an explicit initialization is necessary.
	 */
	atomic_set(&cp->reset_task_pending, 0);
	atomic_set(&cp->reset_task_pending_all, 0);
	atomic_set(&cp->reset_task_pending_spare, 0);
	atomic_set(&cp->reset_task_pending_mtu, 0);
#पूर्ण_अगर
	INIT_WORK(&cp->reset_task, cas_reset_task);

	/* Default link parameters */
	अगर (link_mode >= 0 && link_mode < 6)
		cp->link_cntl = link_modes[link_mode];
	अन्यथा
		cp->link_cntl = BMCR_ANENABLE;
	cp->lstate = link_करोwn;
	cp->link_transition = LINK_TRANSITION_LINK_DOWN;
	netअगर_carrier_off(cp->dev);
	cp->समयr_ticks = 0;

	/* give us access to cassini रेजिस्टरs */
	cp->regs = pci_iomap(pdev, 0, casreg_len);
	अगर (!cp->regs) अणु
		dev_err(&pdev->dev, "Cannot map device registers, aborting\n");
		जाओ err_out_मुक्त_res;
	पूर्ण
	cp->casreg_len = casreg_len;

	pci_save_state(pdev);
	cas_check_pci_invariants(cp);
	cas_hard_reset(cp);
	cas_reset(cp, 0);
	अगर (cas_check_invariants(cp))
		जाओ err_out_iounmap;
	अगर (cp->cas_flags & CAS_FLAG_SATURN)
		cas_saturn_firmware_init(cp);

	cp->init_block =
		dma_alloc_coherent(&pdev->dev, माप(काष्ठा cas_init_block),
				   &cp->block_dvma, GFP_KERNEL);
	अगर (!cp->init_block) अणु
		dev_err(&pdev->dev, "Cannot allocate init block, aborting\n");
		जाओ err_out_iounmap;
	पूर्ण

	क्रम (i = 0; i < N_TX_RINGS; i++)
		cp->init_txds[i] = cp->init_block->txds[i];

	क्रम (i = 0; i < N_RX_DESC_RINGS; i++)
		cp->init_rxds[i] = cp->init_block->rxds[i];

	क्रम (i = 0; i < N_RX_COMP_RINGS; i++)
		cp->init_rxcs[i] = cp->init_block->rxcs[i];

	क्रम (i = 0; i < N_RX_FLOWS; i++)
		skb_queue_head_init(&cp->rx_flows[i]);

	dev->netdev_ops = &cas_netdev_ops;
	dev->ethtool_ops = &cas_ethtool_ops;
	dev->watchकरोg_समयo = CAS_TX_TIMEOUT;

#अगर_घोषित USE_NAPI
	netअगर_napi_add(dev, &cp->napi, cas_poll, 64);
#पूर्ण_अगर
	dev->irq = pdev->irq;
	dev->dma = 0;

	/* Cassini features. */
	अगर ((cp->cas_flags & CAS_FLAG_NO_HW_CSUM) == 0)
		dev->features |= NETIF_F_HW_CSUM | NETIF_F_SG;

	अगर (pci_using_dac)
		dev->features |= NETIF_F_HIGHDMA;

	/* MTU range: 60 - varies or 9000 */
	dev->min_mtu = CAS_MIN_MTU;
	dev->max_mtu = CAS_MAX_MTU;

	अगर (रेजिस्टर_netdev(dev)) अणु
		dev_err(&pdev->dev, "Cannot register net device, aborting\n");
		जाओ err_out_मुक्त_consistent;
	पूर्ण

	i = पढ़ोl(cp->regs + REG_BIM_CFG);
	netdev_info(dev, "Sun Cassini%s (%sbit/%sMHz PCI/%s) Ethernet[%d] %pM\n",
		    (cp->cas_flags & CAS_FLAG_REG_PLUS) ? "+" : "",
		    (i & BIM_CFG_32BIT) ? "32" : "64",
		    (i & BIM_CFG_66MHZ) ? "66" : "33",
		    (cp->phy_type == CAS_PHY_SERDES) ? "Fi" : "Cu", pdev->irq,
		    dev->dev_addr);

	pci_set_drvdata(pdev, dev);
	cp->hw_running = 1;
	cas_entropy_reset(cp);
	cas_phy_init(cp);
	cas_begin_स्वतः_negotiation(cp, शून्य);
	वापस 0;

err_out_मुक्त_consistent:
	dma_मुक्त_coherent(&pdev->dev, माप(काष्ठा cas_init_block),
			  cp->init_block, cp->block_dvma);

err_out_iounmap:
	mutex_lock(&cp->pm_mutex);
	अगर (cp->hw_running)
		cas_shutकरोwn(cp);
	mutex_unlock(&cp->pm_mutex);

	pci_iounmap(pdev, cp->regs);


err_out_मुक्त_res:
	pci_release_regions(pdev);

	/* Try to restore it in हाल the error occurred after we
	 * set it.
	 */
	pci_ग_लिखो_config_byte(pdev, PCI_CACHE_LINE_SIZE, orig_cacheline_size);

err_out_मुक्त_netdev:
	मुक्त_netdev(dev);

err_out_disable_pdev:
	pci_disable_device(pdev);
	वापस -ENODEV;
पूर्ण

अटल व्योम cas_हटाओ_one(काष्ठा pci_dev *pdev)
अणु
	काष्ठा net_device *dev = pci_get_drvdata(pdev);
	काष्ठा cas *cp;
	अगर (!dev)
		वापस;

	cp = netdev_priv(dev);
	unरेजिस्टर_netdev(dev);

	vमुक्त(cp->fw_data);

	mutex_lock(&cp->pm_mutex);
	cancel_work_sync(&cp->reset_task);
	अगर (cp->hw_running)
		cas_shutकरोwn(cp);
	mutex_unlock(&cp->pm_mutex);

#अगर 1
	अगर (cp->orig_cacheline_size) अणु
		/* Restore the cache line size अगर we had modअगरied
		 * it.
		 */
		pci_ग_लिखो_config_byte(pdev, PCI_CACHE_LINE_SIZE,
				      cp->orig_cacheline_size);
	पूर्ण
#पूर्ण_अगर
	dma_मुक्त_coherent(&pdev->dev, माप(काष्ठा cas_init_block),
			  cp->init_block, cp->block_dvma);
	pci_iounmap(pdev, cp->regs);
	मुक्त_netdev(dev);
	pci_release_regions(pdev);
	pci_disable_device(pdev);
पूर्ण

अटल पूर्णांक __maybe_unused cas_suspend(काष्ठा device *dev_d)
अणु
	काष्ठा net_device *dev = dev_get_drvdata(dev_d);
	काष्ठा cas *cp = netdev_priv(dev);
	अचिन्हित दीर्घ flags;

	mutex_lock(&cp->pm_mutex);

	/* If the driver is खोलोed, we stop the DMA */
	अगर (cp->खोलोed) अणु
		netअगर_device_detach(dev);

		cas_lock_all_save(cp, flags);

		/* We can set the second arg of cas_reset to 0
		 * because on resume, we'll call cas_init_hw with
		 * its second arg set so that स्वतःnegotiation is
		 * restarted.
		 */
		cas_reset(cp, 0);
		cas_clean_rings(cp);
		cas_unlock_all_restore(cp, flags);
	पूर्ण

	अगर (cp->hw_running)
		cas_shutकरोwn(cp);
	mutex_unlock(&cp->pm_mutex);

	वापस 0;
पूर्ण

अटल पूर्णांक __maybe_unused cas_resume(काष्ठा device *dev_d)
अणु
	काष्ठा net_device *dev = dev_get_drvdata(dev_d);
	काष्ठा cas *cp = netdev_priv(dev);

	netdev_info(dev, "resuming\n");

	mutex_lock(&cp->pm_mutex);
	cas_hard_reset(cp);
	अगर (cp->खोलोed) अणु
		अचिन्हित दीर्घ flags;
		cas_lock_all_save(cp, flags);
		cas_reset(cp, 0);
		cp->hw_running = 1;
		cas_clean_rings(cp);
		cas_init_hw(cp, 1);
		cas_unlock_all_restore(cp, flags);

		netअगर_device_attach(dev);
	पूर्ण
	mutex_unlock(&cp->pm_mutex);
	वापस 0;
पूर्ण

अटल SIMPLE_DEV_PM_OPS(cas_pm_ops, cas_suspend, cas_resume);

अटल काष्ठा pci_driver cas_driver = अणु
	.name		= DRV_MODULE_NAME,
	.id_table	= cas_pci_tbl,
	.probe		= cas_init_one,
	.हटाओ		= cas_हटाओ_one,
	.driver.pm	= &cas_pm_ops,
पूर्ण;

अटल पूर्णांक __init cas_init(व्योम)
अणु
	अगर (linkकरोwn_समयout > 0)
		link_transition_समयout = linkकरोwn_समयout * HZ;
	अन्यथा
		link_transition_समयout = 0;

	वापस pci_रेजिस्टर_driver(&cas_driver);
पूर्ण

अटल व्योम __निकास cas_cleanup(व्योम)
अणु
	pci_unरेजिस्टर_driver(&cas_driver);
पूर्ण

module_init(cas_init);
module_निकास(cas_cleanup);
