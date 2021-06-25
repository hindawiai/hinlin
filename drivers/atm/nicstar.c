<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * nicstar.c
 *
 * Device driver supporting CBR क्रम IDT 77201/77211 "NICStAR" based cards.
 *
 * IMPORTANT: The included file nicstarmac.c was NOT WRITTEN BY ME.
 *            It was taken from the frle-0.22 device driver.
 *            As the file करोesn't have a copyright notice, in the file
 *            nicstarmac.copyright I put the copyright notice from the
 *            frle-0.22 device driver.
 *            Some code is based on the nicstar driver by M. Welsh.
 *
 * Author: Rui Prior (rprior@inescn.pt)
 * PowerPC support by Jay Talbott (jay_talbott@mcg.mot.com) April 1999
 *
 *
 * (C) INESC 1999
 */

/*
 * IMPORTANT INFORMATION
 *
 * There are currently three types of spinlocks:
 *
 * 1 - Per card पूर्णांकerrupt spinlock (to protect काष्ठाures and such)
 * 2 - Per SCQ scq spinlock
 * 3 - Per card resource spinlock (to access रेजिस्टरs, etc.)
 *
 * These must NEVER be grabbed in reverse order.
 *
 */

/* Header files */

#समावेश <linux/module.h>
#समावेश <linux/kernel.h>
#समावेश <linux/skbuff.h>
#समावेश <linux/aपंचांगdev.h>
#समावेश <linux/aपंचांग.h>
#समावेश <linux/pci.h>
#समावेश <linux/dma-mapping.h>
#समावेश <linux/types.h>
#समावेश <linux/माला.स>
#समावेश <linux/delay.h>
#समावेश <linux/init.h>
#समावेश <linux/sched.h>
#समावेश <linux/समयr.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/bitops.h>
#समावेश <linux/slab.h>
#समावेश <linux/idr.h>
#समावेश <यंत्र/पन.स>
#समावेश <linux/uaccess.h>
#समावेश <linux/atomic.h>
#समावेश <linux/etherdevice.h>
#समावेश "nicstar.h"
#अगर_घोषित CONFIG_ATM_NICSTAR_USE_SUNI
#समावेश "suni.h"
#पूर्ण_अगर /* CONFIG_ATM_NICSTAR_USE_SUNI */
#अगर_घोषित CONFIG_ATM_NICSTAR_USE_IDT77105
#समावेश "idt77105.h"
#पूर्ण_अगर /* CONFIG_ATM_NICSTAR_USE_IDT77105 */

/* Additional code */

#समावेश "nicstarmac.c"

/* Configurable parameters */

#अघोषित PHY_LOOPBACK
#अघोषित TX_DEBUG
#अघोषित RX_DEBUG
#अघोषित GENERAL_DEBUG
#अघोषित EXTRA_DEBUG

/* Do not touch these */

#अगर_घोषित TX_DEBUG
#घोषणा TXPRINTK(args...) prपूर्णांकk(args)
#अन्यथा
#घोषणा TXPRINTK(args...)
#पूर्ण_अगर /* TX_DEBUG */

#अगर_घोषित RX_DEBUG
#घोषणा RXPRINTK(args...) prपूर्णांकk(args)
#अन्यथा
#घोषणा RXPRINTK(args...)
#पूर्ण_अगर /* RX_DEBUG */

#अगर_घोषित GENERAL_DEBUG
#घोषणा PRINTK(args...) prपूर्णांकk(args)
#अन्यथा
#घोषणा PRINTK(args...) करो अणुपूर्ण जबतक (0)
#पूर्ण_अगर /* GENERAL_DEBUG */

#अगर_घोषित EXTRA_DEBUG
#घोषणा XPRINTK(args...) prपूर्णांकk(args)
#अन्यथा
#घोषणा XPRINTK(args...)
#पूर्ण_अगर /* EXTRA_DEBUG */

/* Macros */

#घोषणा CMD_BUSY(card) (पढ़ोl((card)->membase + STAT) & NS_STAT_CMDBZ)

#घोषणा NS_DELAY mdelay(1)

#घोषणा PTR_DIFF(a, b)	((u32)((अचिन्हित दीर्घ)(a) - (अचिन्हित दीर्घ)(b)))

#अगर_अघोषित ATM_SKB
#घोषणा ATM_SKB(s) (&(s)->aपंचांग)
#पूर्ण_अगर

#घोषणा scq_virt_to_bus(scq, p) \
		(scq->dma + ((अचिन्हित दीर्घ)(p) - (अचिन्हित दीर्घ)(scq)->org))

/* Function declarations */

अटल u32 ns_पढ़ो_sram(ns_dev * card, u32 sram_address);
अटल व्योम ns_ग_लिखो_sram(ns_dev * card, u32 sram_address, u32 * value,
			  पूर्णांक count);
अटल पूर्णांक ns_init_card(पूर्णांक i, काष्ठा pci_dev *pcidev);
अटल व्योम ns_init_card_error(ns_dev * card, पूर्णांक error);
अटल scq_info *get_scq(ns_dev *card, पूर्णांक size, u32 scd);
अटल व्योम मुक्त_scq(ns_dev *card, scq_info * scq, काष्ठा aपंचांग_vcc *vcc);
अटल व्योम push_rxbufs(ns_dev *, काष्ठा sk_buff *);
अटल irqवापस_t ns_irq_handler(पूर्णांक irq, व्योम *dev_id);
अटल पूर्णांक ns_खोलो(काष्ठा aपंचांग_vcc *vcc);
अटल व्योम ns_बंद(काष्ठा aपंचांग_vcc *vcc);
अटल व्योम fill_tst(ns_dev * card, पूर्णांक n, vc_map * vc);
अटल पूर्णांक ns_send(काष्ठा aपंचांग_vcc *vcc, काष्ठा sk_buff *skb);
अटल पूर्णांक ns_send_bh(काष्ठा aपंचांग_vcc *vcc, काष्ठा sk_buff *skb);
अटल पूर्णांक push_scqe(ns_dev * card, vc_map * vc, scq_info * scq, ns_scqe * tbd,
		     काष्ठा sk_buff *skb, bool may_sleep);
अटल व्योम process_tsq(ns_dev * card);
अटल व्योम drain_scq(ns_dev * card, scq_info * scq, पूर्णांक pos);
अटल व्योम process_rsq(ns_dev * card);
अटल व्योम dequeue_rx(ns_dev * card, ns_rsqe * rsqe);
अटल व्योम recycle_rx_buf(ns_dev * card, काष्ठा sk_buff *skb);
अटल व्योम recycle_iovec_rx_bufs(ns_dev * card, काष्ठा iovec *iov, पूर्णांक count);
अटल व्योम recycle_iov_buf(ns_dev * card, काष्ठा sk_buff *iovb);
अटल व्योम dequeue_sm_buf(ns_dev * card, काष्ठा sk_buff *sb);
अटल व्योम dequeue_lg_buf(ns_dev * card, काष्ठा sk_buff *lb);
अटल पूर्णांक ns_proc_पढ़ो(काष्ठा aपंचांग_dev *dev, loff_t * pos, अक्षर *page);
अटल पूर्णांक ns_ioctl(काष्ठा aपंचांग_dev *dev, अचिन्हित पूर्णांक cmd, व्योम __user * arg);
#अगर_घोषित EXTRA_DEBUG
अटल व्योम which_list(ns_dev * card, काष्ठा sk_buff *skb);
#पूर्ण_अगर
अटल व्योम ns_poll(काष्ठा समयr_list *unused);
अटल व्योम ns_phy_put(काष्ठा aपंचांग_dev *dev, अचिन्हित अक्षर value,
		       अचिन्हित दीर्घ addr);
अटल अचिन्हित अक्षर ns_phy_get(काष्ठा aपंचांग_dev *dev, अचिन्हित दीर्घ addr);

/* Global variables */

अटल काष्ठा ns_dev *cards[NS_MAX_CARDS];
अटल अचिन्हित num_cards;
अटल स्थिर काष्ठा aपंचांगdev_ops aपंचांग_ops = अणु
	.खोलो = ns_खोलो,
	.बंद = ns_बंद,
	.ioctl = ns_ioctl,
	.send = ns_send,
	.send_bh = ns_send_bh,
	.phy_put = ns_phy_put,
	.phy_get = ns_phy_get,
	.proc_पढ़ो = ns_proc_पढ़ो,
	.owner = THIS_MODULE,
पूर्ण;

अटल काष्ठा समयr_list ns_समयr;
अटल अक्षर *mac[NS_MAX_CARDS];
module_param_array(mac, अक्षरp, शून्य, 0);
MODULE_LICENSE("GPL");

/* Functions */

अटल पूर्णांक nicstar_init_one(काष्ठा pci_dev *pcidev,
			    स्थिर काष्ठा pci_device_id *ent)
अणु
	अटल पूर्णांक index = -1;
	अचिन्हित पूर्णांक error;

	index++;
	cards[index] = शून्य;

	error = ns_init_card(index, pcidev);
	अगर (error) अणु
		cards[index--] = शून्य;	/* करोn't increment index */
		जाओ err_out;
	पूर्ण

	वापस 0;
err_out:
	वापस -ENODEV;
पूर्ण

अटल व्योम nicstar_हटाओ_one(काष्ठा pci_dev *pcidev)
अणु
	पूर्णांक i, j;
	ns_dev *card = pci_get_drvdata(pcidev);
	काष्ठा sk_buff *hb;
	काष्ठा sk_buff *iovb;
	काष्ठा sk_buff *lb;
	काष्ठा sk_buff *sb;

	i = card->index;

	अगर (cards[i] == शून्य)
		वापस;

	अगर (card->aपंचांगdev->phy && card->aपंचांगdev->phy->stop)
		card->aपंचांगdev->phy->stop(card->aपंचांगdev);

	/* Stop everything */
	ग_लिखोl(0x00000000, card->membase + CFG);

	/* De-रेजिस्टर device */
	aपंचांग_dev_deरेजिस्टर(card->aपंचांगdev);

	/* Disable PCI device */
	pci_disable_device(pcidev);

	/* Free up resources */
	j = 0;
	PRINTK("nicstar%d: freeing %d huge buffers.\n", i, card->hbpool.count);
	जबतक ((hb = skb_dequeue(&card->hbpool.queue)) != शून्य) अणु
		dev_kमुक्त_skb_any(hb);
		j++;
	पूर्ण
	PRINTK("nicstar%d: %d huge buffers freed.\n", i, j);
	j = 0;
	PRINTK("nicstar%d: freeing %d iovec buffers.\n", i,
	       card->iovpool.count);
	जबतक ((iovb = skb_dequeue(&card->iovpool.queue)) != शून्य) अणु
		dev_kमुक्त_skb_any(iovb);
		j++;
	पूर्ण
	PRINTK("nicstar%d: %d iovec buffers freed.\n", i, j);
	जबतक ((lb = skb_dequeue(&card->lbpool.queue)) != शून्य)
		dev_kमुक्त_skb_any(lb);
	जबतक ((sb = skb_dequeue(&card->sbpool.queue)) != शून्य)
		dev_kमुक्त_skb_any(sb);
	मुक्त_scq(card, card->scq0, शून्य);
	क्रम (j = 0; j < NS_FRSCD_NUM; j++) अणु
		अगर (card->scd2vc[j] != शून्य)
			मुक्त_scq(card, card->scd2vc[j]->scq, card->scd2vc[j]->tx_vcc);
	पूर्ण
	idr_destroy(&card->idr);
	dma_मुक्त_coherent(&card->pcidev->dev, NS_RSQSIZE + NS_RSQ_ALIGNMENT,
			  card->rsq.org, card->rsq.dma);
	dma_मुक्त_coherent(&card->pcidev->dev, NS_TSQSIZE + NS_TSQ_ALIGNMENT,
			  card->tsq.org, card->tsq.dma);
	मुक्त_irq(card->pcidev->irq, card);
	iounmap(card->membase);
	kमुक्त(card);
पूर्ण

अटल स्थिर काष्ठा pci_device_id nicstar_pci_tbl[] = अणु
	अणु PCI_VDEVICE(IDT, PCI_DEVICE_ID_IDT_IDT77201), 0 पूर्ण,
	अणु0,पूर्ण			/* terminate list */
पूर्ण;

MODULE_DEVICE_TABLE(pci, nicstar_pci_tbl);

अटल काष्ठा pci_driver nicstar_driver = अणु
	.name = "nicstar",
	.id_table = nicstar_pci_tbl,
	.probe = nicstar_init_one,
	.हटाओ = nicstar_हटाओ_one,
पूर्ण;

अटल पूर्णांक __init nicstar_init(व्योम)
अणु
	अचिन्हित error = 0;	/* Initialized to हटाओ compile warning */

	XPRINTK("nicstar: nicstar_init() called.\n");

	error = pci_रेजिस्टर_driver(&nicstar_driver);

	TXPRINTK("nicstar: TX debug enabled.\n");
	RXPRINTK("nicstar: RX debug enabled.\n");
	PRINTK("nicstar: General debug enabled.\n");
#अगर_घोषित PHY_LOOPBACK
	prपूर्णांकk("nicstar: using PHY loopback.\n");
#पूर्ण_अगर /* PHY_LOOPBACK */
	XPRINTK("nicstar: nicstar_init() returned.\n");

	अगर (!error) अणु
		समयr_setup(&ns_समयr, ns_poll, 0);
		ns_समयr.expires = jअगरfies + NS_POLL_PERIOD;
		add_समयr(&ns_समयr);
	पूर्ण

	वापस error;
पूर्ण

अटल व्योम __निकास nicstar_cleanup(व्योम)
अणु
	XPRINTK("nicstar: nicstar_cleanup() called.\n");

	del_समयr(&ns_समयr);

	pci_unरेजिस्टर_driver(&nicstar_driver);

	XPRINTK("nicstar: nicstar_cleanup() returned.\n");
पूर्ण

अटल u32 ns_पढ़ो_sram(ns_dev * card, u32 sram_address)
अणु
	अचिन्हित दीर्घ flags;
	u32 data;
	sram_address <<= 2;
	sram_address &= 0x0007FFFC;	/* address must be dword aligned */
	sram_address |= 0x50000000;	/* SRAM पढ़ो command */
	spin_lock_irqsave(&card->res_lock, flags);
	जबतक (CMD_BUSY(card)) ;
	ग_लिखोl(sram_address, card->membase + CMD);
	जबतक (CMD_BUSY(card)) ;
	data = पढ़ोl(card->membase + DR0);
	spin_unlock_irqrestore(&card->res_lock, flags);
	वापस data;
पूर्ण

अटल व्योम ns_ग_लिखो_sram(ns_dev * card, u32 sram_address, u32 * value,
			  पूर्णांक count)
अणु
	अचिन्हित दीर्घ flags;
	पूर्णांक i, c;
	count--;		/* count range now is 0..3 instead of 1..4 */
	c = count;
	c <<= 2;		/* to use increments of 4 */
	spin_lock_irqsave(&card->res_lock, flags);
	जबतक (CMD_BUSY(card)) ;
	क्रम (i = 0; i <= c; i += 4)
		ग_लिखोl(*(value++), card->membase + i);
	/* Note: DR# रेजिस्टरs are the first 4 dwords in nicstar's memspace,
	   so card->membase + DR0 == card->membase */
	sram_address <<= 2;
	sram_address &= 0x0007FFFC;
	sram_address |= (0x40000000 | count);
	ग_लिखोl(sram_address, card->membase + CMD);
	spin_unlock_irqrestore(&card->res_lock, flags);
पूर्ण

अटल पूर्णांक ns_init_card(पूर्णांक i, काष्ठा pci_dev *pcidev)
अणु
	पूर्णांक j;
	काष्ठा ns_dev *card = शून्य;
	अचिन्हित अक्षर pci_latency;
	अचिन्हित error;
	u32 data;
	u32 u32d[4];
	u32 ns_cfg_rctsize;
	पूर्णांक bcount;
	अचिन्हित दीर्घ membase;

	error = 0;

	अगर (pci_enable_device(pcidev)) अणु
		prपूर्णांकk("nicstar%d: can't enable PCI device\n", i);
		error = 2;
		ns_init_card_error(card, error);
		वापस error;
	पूर्ण
        अगर (dma_set_mask_and_coherent(&pcidev->dev, DMA_BIT_MASK(32)) != 0) अणु
                prपूर्णांकk(KERN_WARNING
		       "nicstar%d: No suitable DMA available.\n", i);
		error = 2;
		ns_init_card_error(card, error);
		वापस error;
        पूर्ण

	card = kदो_स्मृति(माप(*card), GFP_KERNEL);
	अगर (!card) अणु
		prपूर्णांकk
		    ("nicstar%d: can't allocate memory for device structure.\n",
		     i);
		error = 2;
		ns_init_card_error(card, error);
		वापस error;
	पूर्ण
	cards[i] = card;
	spin_lock_init(&card->पूर्णांक_lock);
	spin_lock_init(&card->res_lock);

	pci_set_drvdata(pcidev, card);

	card->index = i;
	card->aपंचांगdev = शून्य;
	card->pcidev = pcidev;
	membase = pci_resource_start(pcidev, 1);
	card->membase = ioremap(membase, NS_IOREMAP_SIZE);
	अगर (!card->membase) अणु
		prपूर्णांकk("nicstar%d: can't ioremap() membase.\n", i);
		error = 3;
		ns_init_card_error(card, error);
		वापस error;
	पूर्ण
	PRINTK("nicstar%d: membase at 0x%p.\n", i, card->membase);

	pci_set_master(pcidev);

	अगर (pci_पढ़ो_config_byte(pcidev, PCI_LATENCY_TIMER, &pci_latency) != 0) अणु
		prपूर्णांकk("nicstar%d: can't read PCI latency timer.\n", i);
		error = 6;
		ns_init_card_error(card, error);
		वापस error;
	पूर्ण
#अगर_घोषित NS_PCI_LATENCY
	अगर (pci_latency < NS_PCI_LATENCY) अणु
		PRINTK("nicstar%d: setting PCI latency timer to %d.\n", i,
		       NS_PCI_LATENCY);
		क्रम (j = 1; j < 4; j++) अणु
			अगर (pci_ग_लिखो_config_byte
			    (pcidev, PCI_LATENCY_TIMER, NS_PCI_LATENCY) != 0)
				अवरोध;
		पूर्ण
		अगर (j == 4) अणु
			prपूर्णांकk
			    ("nicstar%d: can't set PCI latency timer to %d.\n",
			     i, NS_PCI_LATENCY);
			error = 7;
			ns_init_card_error(card, error);
			वापस error;
		पूर्ण
	पूर्ण
#पूर्ण_अगर /* NS_PCI_LATENCY */

	/* Clear समयr overflow */
	data = पढ़ोl(card->membase + STAT);
	अगर (data & NS_STAT_TMROF)
		ग_लिखोl(NS_STAT_TMROF, card->membase + STAT);

	/* Software reset */
	ग_लिखोl(NS_CFG_SWRST, card->membase + CFG);
	NS_DELAY;
	ग_लिखोl(0x00000000, card->membase + CFG);

	/* PHY reset */
	ग_लिखोl(0x00000008, card->membase + GP);
	NS_DELAY;
	ग_लिखोl(0x00000001, card->membase + GP);
	NS_DELAY;
	जबतक (CMD_BUSY(card)) ;
	ग_लिखोl(NS_CMD_WRITE_UTILITY | 0x00000100, card->membase + CMD);	/* Sync UTOPIA with SAR घड़ी */
	NS_DELAY;

	/* Detect PHY type */
	जबतक (CMD_BUSY(card)) ;
	ग_लिखोl(NS_CMD_READ_UTILITY | 0x00000200, card->membase + CMD);
	जबतक (CMD_BUSY(card)) ;
	data = पढ़ोl(card->membase + DR0);
	चयन (data) अणु
	हाल 0x00000009:
		prपूर्णांकk("nicstar%d: PHY seems to be 25 Mbps.\n", i);
		card->max_pcr = ATM_25_PCR;
		जबतक (CMD_BUSY(card)) ;
		ग_लिखोl(0x00000008, card->membase + DR0);
		ग_लिखोl(NS_CMD_WRITE_UTILITY | 0x00000200, card->membase + CMD);
		/* Clear an eventual pending पूर्णांकerrupt */
		ग_लिखोl(NS_STAT_SFBQF, card->membase + STAT);
#अगर_घोषित PHY_LOOPBACK
		जबतक (CMD_BUSY(card)) ;
		ग_लिखोl(0x00000022, card->membase + DR0);
		ग_लिखोl(NS_CMD_WRITE_UTILITY | 0x00000202, card->membase + CMD);
#पूर्ण_अगर /* PHY_LOOPBACK */
		अवरोध;
	हाल 0x00000030:
	हाल 0x00000031:
		prपूर्णांकk("nicstar%d: PHY seems to be 155 Mbps.\n", i);
		card->max_pcr = ATM_OC3_PCR;
#अगर_घोषित PHY_LOOPBACK
		जबतक (CMD_BUSY(card)) ;
		ग_लिखोl(0x00000002, card->membase + DR0);
		ग_लिखोl(NS_CMD_WRITE_UTILITY | 0x00000205, card->membase + CMD);
#पूर्ण_अगर /* PHY_LOOPBACK */
		अवरोध;
	शेष:
		prपूर्णांकk("nicstar%d: unknown PHY type (0x%08X).\n", i, data);
		error = 8;
		ns_init_card_error(card, error);
		वापस error;
	पूर्ण
	ग_लिखोl(0x00000000, card->membase + GP);

	/* Determine SRAM size */
	data = 0x76543210;
	ns_ग_लिखो_sram(card, 0x1C003, &data, 1);
	data = 0x89ABCDEF;
	ns_ग_लिखो_sram(card, 0x14003, &data, 1);
	अगर (ns_पढ़ो_sram(card, 0x14003) == 0x89ABCDEF &&
	    ns_पढ़ो_sram(card, 0x1C003) == 0x76543210)
		card->sram_size = 128;
	अन्यथा
		card->sram_size = 32;
	PRINTK("nicstar%d: %dK x 32bit SRAM size.\n", i, card->sram_size);

	card->rct_size = NS_MAX_RCTSIZE;

#अगर (NS_MAX_RCTSIZE == 4096)
	अगर (card->sram_size == 128)
		prपूर्णांकk
		    ("nicstar%d: limiting maximum VCI. See NS_MAX_RCTSIZE in nicstar.h\n",
		     i);
#या_अगर (NS_MAX_RCTSIZE == 16384)
	अगर (card->sram_size == 32) अणु
		prपूर्णांकk
		    ("nicstar%d: wasting memory. See NS_MAX_RCTSIZE in nicstar.h\n",
		     i);
		card->rct_size = 4096;
	पूर्ण
#अन्यथा
#त्रुटि NS_MAX_RCTSIZE must be either 4096 or 16384 in nicstar.c
#पूर्ण_अगर

	card->vpibits = NS_VPIBITS;
	अगर (card->rct_size == 4096)
		card->vcibits = 12 - NS_VPIBITS;
	अन्यथा			/* card->rct_size == 16384 */
		card->vcibits = 14 - NS_VPIBITS;

	/* Initialize the nicstar eeprom/eprom stuff, क्रम the MAC addr */
	अगर (mac[i] == शून्य)
		nicstar_init_eprom(card->membase);

	/* Set the VPI/VCI MSb mask to zero so we can receive OAM cells */
	ग_लिखोl(0x00000000, card->membase + VPM);

	/* Initialize TSQ */
	card->tsq.org = dma_alloc_coherent(&card->pcidev->dev,
					   NS_TSQSIZE + NS_TSQ_ALIGNMENT,
					   &card->tsq.dma, GFP_KERNEL);
	अगर (card->tsq.org == शून्य) अणु
		prपूर्णांकk("nicstar%d: can't allocate TSQ.\n", i);
		error = 10;
		ns_init_card_error(card, error);
		वापस error;
	पूर्ण
	card->tsq.base = PTR_ALIGN(card->tsq.org, NS_TSQ_ALIGNMENT);
	card->tsq.next = card->tsq.base;
	card->tsq.last = card->tsq.base + (NS_TSQ_NUM_ENTRIES - 1);
	क्रम (j = 0; j < NS_TSQ_NUM_ENTRIES; j++)
		ns_tsi_init(card->tsq.base + j);
	ग_लिखोl(0x00000000, card->membase + TSQH);
	ग_लिखोl(ALIGN(card->tsq.dma, NS_TSQ_ALIGNMENT), card->membase + TSQB);
	PRINTK("nicstar%d: TSQ base at 0x%p.\n", i, card->tsq.base);

	/* Initialize RSQ */
	card->rsq.org = dma_alloc_coherent(&card->pcidev->dev,
					   NS_RSQSIZE + NS_RSQ_ALIGNMENT,
					   &card->rsq.dma, GFP_KERNEL);
	अगर (card->rsq.org == शून्य) अणु
		prपूर्णांकk("nicstar%d: can't allocate RSQ.\n", i);
		error = 11;
		ns_init_card_error(card, error);
		वापस error;
	पूर्ण
	card->rsq.base = PTR_ALIGN(card->rsq.org, NS_RSQ_ALIGNMENT);
	card->rsq.next = card->rsq.base;
	card->rsq.last = card->rsq.base + (NS_RSQ_NUM_ENTRIES - 1);
	क्रम (j = 0; j < NS_RSQ_NUM_ENTRIES; j++)
		ns_rsqe_init(card->rsq.base + j);
	ग_लिखोl(0x00000000, card->membase + RSQH);
	ग_लिखोl(ALIGN(card->rsq.dma, NS_RSQ_ALIGNMENT), card->membase + RSQB);
	PRINTK("nicstar%d: RSQ base at 0x%p.\n", i, card->rsq.base);

	/* Initialize SCQ0, the only VBR SCQ used */
	card->scq1 = शून्य;
	card->scq2 = शून्य;
	card->scq0 = get_scq(card, VBR_SCQSIZE, NS_VRSCD0);
	अगर (card->scq0 == शून्य) अणु
		prपूर्णांकk("nicstar%d: can't get SCQ0.\n", i);
		error = 12;
		ns_init_card_error(card, error);
		वापस error;
	पूर्ण
	u32d[0] = scq_virt_to_bus(card->scq0, card->scq0->base);
	u32d[1] = (u32) 0x00000000;
	u32d[2] = (u32) 0xffffffff;
	u32d[3] = (u32) 0x00000000;
	ns_ग_लिखो_sram(card, NS_VRSCD0, u32d, 4);
	ns_ग_लिखो_sram(card, NS_VRSCD1, u32d, 4);	/* These last two won't be used */
	ns_ग_लिखो_sram(card, NS_VRSCD2, u32d, 4);	/* but are initialized, just in हाल... */
	card->scq0->scd = NS_VRSCD0;
	PRINTK("nicstar%d: VBR-SCQ0 base at 0x%p.\n", i, card->scq0->base);

	/* Initialize TSTs */
	card->tst_addr = NS_TST0;
	card->tst_मुक्त_entries = NS_TST_NUM_ENTRIES;
	data = NS_TST_OPCODE_VARIABLE;
	क्रम (j = 0; j < NS_TST_NUM_ENTRIES; j++)
		ns_ग_लिखो_sram(card, NS_TST0 + j, &data, 1);
	data = ns_tste_make(NS_TST_OPCODE_END, NS_TST0);
	ns_ग_लिखो_sram(card, NS_TST0 + NS_TST_NUM_ENTRIES, &data, 1);
	क्रम (j = 0; j < NS_TST_NUM_ENTRIES; j++)
		ns_ग_लिखो_sram(card, NS_TST1 + j, &data, 1);
	data = ns_tste_make(NS_TST_OPCODE_END, NS_TST1);
	ns_ग_लिखो_sram(card, NS_TST1 + NS_TST_NUM_ENTRIES, &data, 1);
	क्रम (j = 0; j < NS_TST_NUM_ENTRIES; j++)
		card->tste2vc[j] = शून्य;
	ग_लिखोl(NS_TST0 << 2, card->membase + TSTB);

	/* Initialize RCT. AAL type is set on खोलोing the VC. */
#अगर_घोषित RCQ_SUPPORT
	u32d[0] = NS_RCTE_RAWCELLINTEN;
#अन्यथा
	u32d[0] = 0x00000000;
#पूर्ण_अगर /* RCQ_SUPPORT */
	u32d[1] = 0x00000000;
	u32d[2] = 0x00000000;
	u32d[3] = 0xFFFFFFFF;
	क्रम (j = 0; j < card->rct_size; j++)
		ns_ग_लिखो_sram(card, j * 4, u32d, 4);

	स_रखो(card->vcmap, 0, माप(card->vcmap));

	क्रम (j = 0; j < NS_FRSCD_NUM; j++)
		card->scd2vc[j] = शून्य;

	/* Initialize buffer levels */
	card->sbnr.min = MIN_SB;
	card->sbnr.init = NUM_SB;
	card->sbnr.max = MAX_SB;
	card->lbnr.min = MIN_LB;
	card->lbnr.init = NUM_LB;
	card->lbnr.max = MAX_LB;
	card->iovnr.min = MIN_IOVB;
	card->iovnr.init = NUM_IOVB;
	card->iovnr.max = MAX_IOVB;
	card->hbnr.min = MIN_HB;
	card->hbnr.init = NUM_HB;
	card->hbnr.max = MAX_HB;

	card->sm_handle = शून्य;
	card->sm_addr = 0x00000000;
	card->lg_handle = शून्य;
	card->lg_addr = 0x00000000;

	card->efbie = 1;	/* To prevent push_rxbufs from enabling the पूर्णांकerrupt */

	idr_init(&card->idr);

	/* Pre-allocate some huge buffers */
	skb_queue_head_init(&card->hbpool.queue);
	card->hbpool.count = 0;
	क्रम (j = 0; j < NUM_HB; j++) अणु
		काष्ठा sk_buff *hb;
		hb = __dev_alloc_skb(NS_Hबफ_मानE, GFP_KERNEL);
		अगर (hb == शून्य) अणु
			prपूर्णांकk
			    ("nicstar%d: can't allocate %dth of %d huge buffers.\n",
			     i, j, NUM_HB);
			error = 13;
			ns_init_card_error(card, error);
			वापस error;
		पूर्ण
		NS_PRV_BUFTYPE(hb) = BUF_NONE;
		skb_queue_tail(&card->hbpool.queue, hb);
		card->hbpool.count++;
	पूर्ण

	/* Allocate large buffers */
	skb_queue_head_init(&card->lbpool.queue);
	card->lbpool.count = 0;	/* Not used */
	क्रम (j = 0; j < NUM_LB; j++) अणु
		काष्ठा sk_buff *lb;
		lb = __dev_alloc_skb(NS_LGSKBSIZE, GFP_KERNEL);
		अगर (lb == शून्य) अणु
			prपूर्णांकk
			    ("nicstar%d: can't allocate %dth of %d large buffers.\n",
			     i, j, NUM_LB);
			error = 14;
			ns_init_card_error(card, error);
			वापस error;
		पूर्ण
		NS_PRV_BUFTYPE(lb) = BUF_LG;
		skb_queue_tail(&card->lbpool.queue, lb);
		skb_reserve(lb, NS_SMबफ_मानE);
		push_rxbufs(card, lb);
		/* Due to the implementation of push_rxbufs() this is 1, not 0 */
		अगर (j == 1) अणु
			card->rcbuf = lb;
			card->rawcell = (काष्ठा ns_rcqe *) lb->data;
			card->rawch = NS_PRV_DMA(lb);
		पूर्ण
	पूर्ण
	/* Test क्रम strange behaviour which leads to crashes */
	अगर ((bcount =
	     ns_stat_lfbqc_get(पढ़ोl(card->membase + STAT))) < card->lbnr.min) अणु
		prपूर्णांकk
		    ("nicstar%d: Strange... Just allocated %d large buffers and lfbqc = %d.\n",
		     i, j, bcount);
		error = 14;
		ns_init_card_error(card, error);
		वापस error;
	पूर्ण

	/* Allocate small buffers */
	skb_queue_head_init(&card->sbpool.queue);
	card->sbpool.count = 0;	/* Not used */
	क्रम (j = 0; j < NUM_SB; j++) अणु
		काष्ठा sk_buff *sb;
		sb = __dev_alloc_skb(NS_SMSKBSIZE, GFP_KERNEL);
		अगर (sb == शून्य) अणु
			prपूर्णांकk
			    ("nicstar%d: can't allocate %dth of %d small buffers.\n",
			     i, j, NUM_SB);
			error = 15;
			ns_init_card_error(card, error);
			वापस error;
		पूर्ण
		NS_PRV_BUFTYPE(sb) = BUF_SM;
		skb_queue_tail(&card->sbpool.queue, sb);
		skb_reserve(sb, NS_AAL0_HEADER);
		push_rxbufs(card, sb);
	पूर्ण
	/* Test क्रम strange behaviour which leads to crashes */
	अगर ((bcount =
	     ns_stat_sfbqc_get(पढ़ोl(card->membase + STAT))) < card->sbnr.min) अणु
		prपूर्णांकk
		    ("nicstar%d: Strange... Just allocated %d small buffers and sfbqc = %d.\n",
		     i, j, bcount);
		error = 15;
		ns_init_card_error(card, error);
		वापस error;
	पूर्ण

	/* Allocate iovec buffers */
	skb_queue_head_init(&card->iovpool.queue);
	card->iovpool.count = 0;
	क्रम (j = 0; j < NUM_IOVB; j++) अणु
		काष्ठा sk_buff *iovb;
		iovb = alloc_skb(NS_IOVबफ_मानE, GFP_KERNEL);
		अगर (iovb == शून्य) अणु
			prपूर्णांकk
			    ("nicstar%d: can't allocate %dth of %d iovec buffers.\n",
			     i, j, NUM_IOVB);
			error = 16;
			ns_init_card_error(card, error);
			वापस error;
		पूर्ण
		NS_PRV_BUFTYPE(iovb) = BUF_NONE;
		skb_queue_tail(&card->iovpool.queue, iovb);
		card->iovpool.count++;
	पूर्ण

	/* Configure NICStAR */
	अगर (card->rct_size == 4096)
		ns_cfg_rctsize = NS_CFG_RCTSIZE_4096_ENTRIES;
	अन्यथा			/* (card->rct_size == 16384) */
		ns_cfg_rctsize = NS_CFG_RCTSIZE_16384_ENTRIES;

	card->efbie = 1;

	card->पूर्णांकcnt = 0;
	अगर (request_irq
	    (pcidev->irq, &ns_irq_handler, IRQF_SHARED, "nicstar", card) != 0) अणु
		prपूर्णांकk("nicstar%d: can't allocate IRQ %d.\n", i, pcidev->irq);
		error = 9;
		ns_init_card_error(card, error);
		वापस error;
	पूर्ण

	/* Register device */
	card->aपंचांगdev = aपंचांग_dev_रेजिस्टर("nicstar", &card->pcidev->dev, &aपंचांग_ops,
					-1, शून्य);
	अगर (card->aपंचांगdev == शून्य) अणु
		prपूर्णांकk("nicstar%d: can't register device.\n", i);
		error = 17;
		ns_init_card_error(card, error);
		वापस error;
	पूर्ण

	अगर (mac[i] == शून्य || !mac_pton(mac[i], card->aपंचांगdev->esi)) अणु
		nicstar_पढ़ो_eprom(card->membase, NICSTAR_EPROM_MAC_ADDR_OFFSET,
				   card->aपंचांगdev->esi, 6);
		अगर (ether_addr_equal(card->aपंचांगdev->esi, "\x00\x00\x00\x00\x00\x00")) अणु
			nicstar_पढ़ो_eprom(card->membase,
					   NICSTAR_EPROM_MAC_ADDR_OFFSET_ALT,
					   card->aपंचांगdev->esi, 6);
		पूर्ण
	पूर्ण

	prपूर्णांकk("nicstar%d: MAC address %pM\n", i, card->aपंचांगdev->esi);

	card->aपंचांगdev->dev_data = card;
	card->aपंचांगdev->ci_range.vpi_bits = card->vpibits;
	card->aपंचांगdev->ci_range.vci_bits = card->vcibits;
	card->aपंचांगdev->link_rate = card->max_pcr;
	card->aपंचांगdev->phy = शून्य;

#अगर_घोषित CONFIG_ATM_NICSTAR_USE_SUNI
	अगर (card->max_pcr == ATM_OC3_PCR)
		suni_init(card->aपंचांगdev);
#पूर्ण_अगर /* CONFIG_ATM_NICSTAR_USE_SUNI */

#अगर_घोषित CONFIG_ATM_NICSTAR_USE_IDT77105
	अगर (card->max_pcr == ATM_25_PCR)
		idt77105_init(card->aपंचांगdev);
#पूर्ण_अगर /* CONFIG_ATM_NICSTAR_USE_IDT77105 */

	अगर (card->aपंचांगdev->phy && card->aपंचांगdev->phy->start)
		card->aपंचांगdev->phy->start(card->aपंचांगdev);

	ग_लिखोl(NS_CFG_RXPATH | NS_CFG_SMबफ_मानE | NS_CFG_LGबफ_मानE | NS_CFG_EFBIE | NS_CFG_RSQSIZE | NS_CFG_VPIBITS | ns_cfg_rctsize | NS_CFG_RXINT_NODELAY | NS_CFG_RAWIE |	/* Only enabled अगर RCQ_SUPPORT */
	       NS_CFG_RSQAFIE | NS_CFG_TXEN | NS_CFG_TXIE | NS_CFG_TSQFIE_OPT |	/* Only enabled अगर ENABLE_TSQFIE */
	       NS_CFG_PHYIE, card->membase + CFG);

	num_cards++;

	वापस error;
पूर्ण

अटल व्योम ns_init_card_error(ns_dev *card, पूर्णांक error)
अणु
	अगर (error >= 17) अणु
		ग_लिखोl(0x00000000, card->membase + CFG);
	पूर्ण
	अगर (error >= 16) अणु
		काष्ठा sk_buff *iovb;
		जबतक ((iovb = skb_dequeue(&card->iovpool.queue)) != शून्य)
			dev_kमुक्त_skb_any(iovb);
	पूर्ण
	अगर (error >= 15) अणु
		काष्ठा sk_buff *sb;
		जबतक ((sb = skb_dequeue(&card->sbpool.queue)) != शून्य)
			dev_kमुक्त_skb_any(sb);
		मुक्त_scq(card, card->scq0, शून्य);
	पूर्ण
	अगर (error >= 14) अणु
		काष्ठा sk_buff *lb;
		जबतक ((lb = skb_dequeue(&card->lbpool.queue)) != शून्य)
			dev_kमुक्त_skb_any(lb);
	पूर्ण
	अगर (error >= 13) अणु
		काष्ठा sk_buff *hb;
		जबतक ((hb = skb_dequeue(&card->hbpool.queue)) != शून्य)
			dev_kमुक्त_skb_any(hb);
	पूर्ण
	अगर (error >= 12) अणु
		kमुक्त(card->rsq.org);
	पूर्ण
	अगर (error >= 11) अणु
		kमुक्त(card->tsq.org);
	पूर्ण
	अगर (error >= 10) अणु
		मुक्त_irq(card->pcidev->irq, card);
	पूर्ण
	अगर (error >= 4) अणु
		iounmap(card->membase);
	पूर्ण
	अगर (error >= 3) अणु
		pci_disable_device(card->pcidev);
		kमुक्त(card);
	पूर्ण
पूर्ण

अटल scq_info *get_scq(ns_dev *card, पूर्णांक size, u32 scd)
अणु
	scq_info *scq;
	पूर्णांक i;

	अगर (size != VBR_SCQSIZE && size != CBR_SCQSIZE)
		वापस शून्य;

	scq = kदो_स्मृति(माप(*scq), GFP_KERNEL);
	अगर (!scq)
		वापस शून्य;
        scq->org = dma_alloc_coherent(&card->pcidev->dev,
				      2 * size,  &scq->dma, GFP_KERNEL);
	अगर (!scq->org) अणु
		kमुक्त(scq);
		वापस शून्य;
	पूर्ण
	scq->skb = kदो_स्मृति_array(size / NS_SCQE_SIZE,
				 माप(*scq->skb),
				 GFP_KERNEL);
	अगर (!scq->skb) अणु
		dma_मुक्त_coherent(&card->pcidev->dev,
				  2 * size, scq->org, scq->dma);
		kमुक्त(scq);
		वापस शून्य;
	पूर्ण
	scq->num_entries = size / NS_SCQE_SIZE;
	scq->base = PTR_ALIGN(scq->org, size);
	scq->next = scq->base;
	scq->last = scq->base + (scq->num_entries - 1);
	scq->tail = scq->last;
	scq->scd = scd;
	scq->num_entries = size / NS_SCQE_SIZE;
	scq->tbd_count = 0;
	init_रुकोqueue_head(&scq->scqfull_रुकोq);
	scq->full = 0;
	spin_lock_init(&scq->lock);

	क्रम (i = 0; i < scq->num_entries; i++)
		scq->skb[i] = शून्य;

	वापस scq;
पूर्ण

/* For variable rate SCQ vcc must be शून्य */
अटल व्योम मुक्त_scq(ns_dev *card, scq_info *scq, काष्ठा aपंचांग_vcc *vcc)
अणु
	पूर्णांक i;

	अगर (scq->num_entries == VBR_SCQ_NUM_ENTRIES)
		क्रम (i = 0; i < scq->num_entries; i++) अणु
			अगर (scq->skb[i] != शून्य) अणु
				vcc = ATM_SKB(scq->skb[i])->vcc;
				अगर (vcc->pop != शून्य)
					vcc->pop(vcc, scq->skb[i]);
				अन्यथा
					dev_kमुक्त_skb_any(scq->skb[i]);
			पूर्ण
	पूर्ण अन्यथा अणु		/* vcc must be != शून्य */

		अगर (vcc == शून्य) अणु
			prपूर्णांकk
			    ("nicstar: free_scq() called with vcc == NULL for fixed rate scq.");
			क्रम (i = 0; i < scq->num_entries; i++)
				dev_kमुक्त_skb_any(scq->skb[i]);
		पूर्ण अन्यथा
			क्रम (i = 0; i < scq->num_entries; i++) अणु
				अगर (scq->skb[i] != शून्य) अणु
					अगर (vcc->pop != शून्य)
						vcc->pop(vcc, scq->skb[i]);
					अन्यथा
						dev_kमुक्त_skb_any(scq->skb[i]);
				पूर्ण
			पूर्ण
	पूर्ण
	kमुक्त(scq->skb);
	dma_मुक्त_coherent(&card->pcidev->dev,
			  2 * (scq->num_entries == VBR_SCQ_NUM_ENTRIES ?
			       VBR_SCQSIZE : CBR_SCQSIZE),
			  scq->org, scq->dma);
	kमुक्त(scq);
पूर्ण

/* The handles passed must be poपूर्णांकers to the sk_buff containing the small
   or large buffer(s) cast to u32. */
अटल व्योम push_rxbufs(ns_dev * card, काष्ठा sk_buff *skb)
अणु
	काष्ठा sk_buff *handle1, *handle2;
	पूर्णांक id1, id2;
	u32 addr1, addr2;
	u32 stat;
	अचिन्हित दीर्घ flags;

	/* *BARF* */
	handle2 = शून्य;
	addr2 = 0;
	handle1 = skb;
	addr1 = dma_map_single(&card->pcidev->dev,
			       skb->data,
			       (NS_PRV_BUFTYPE(skb) == BUF_SM
				? NS_SMSKBSIZE : NS_LGSKBSIZE),
			       DMA_TO_DEVICE);
	NS_PRV_DMA(skb) = addr1; /* save so we can unmap later */

#अगर_घोषित GENERAL_DEBUG
	अगर (!addr1)
		prपूर्णांकk("nicstar%d: push_rxbufs called with addr1 = 0.\n",
		       card->index);
#पूर्ण_अगर /* GENERAL_DEBUG */

	stat = पढ़ोl(card->membase + STAT);
	card->sbfqc = ns_stat_sfbqc_get(stat);
	card->lbfqc = ns_stat_lfbqc_get(stat);
	अगर (NS_PRV_BUFTYPE(skb) == BUF_SM) अणु
		अगर (!addr2) अणु
			अगर (card->sm_addr) अणु
				addr2 = card->sm_addr;
				handle2 = card->sm_handle;
				card->sm_addr = 0x00000000;
				card->sm_handle = शून्य;
			पूर्ण अन्यथा अणु	/* (!sm_addr) */

				card->sm_addr = addr1;
				card->sm_handle = handle1;
			पूर्ण
		पूर्ण
	पूर्ण अन्यथा अणु		/* buf_type == BUF_LG */

		अगर (!addr2) अणु
			अगर (card->lg_addr) अणु
				addr2 = card->lg_addr;
				handle2 = card->lg_handle;
				card->lg_addr = 0x00000000;
				card->lg_handle = शून्य;
			पूर्ण अन्यथा अणु	/* (!lg_addr) */

				card->lg_addr = addr1;
				card->lg_handle = handle1;
			पूर्ण
		पूर्ण
	पूर्ण

	अगर (addr2) अणु
		अगर (NS_PRV_BUFTYPE(skb) == BUF_SM) अणु
			अगर (card->sbfqc >= card->sbnr.max) अणु
				skb_unlink(handle1, &card->sbpool.queue);
				dev_kमुक्त_skb_any(handle1);
				skb_unlink(handle2, &card->sbpool.queue);
				dev_kमुक्त_skb_any(handle2);
				वापस;
			पूर्ण अन्यथा
				card->sbfqc += 2;
		पूर्ण अन्यथा अणु	/* (buf_type == BUF_LG) */

			अगर (card->lbfqc >= card->lbnr.max) अणु
				skb_unlink(handle1, &card->lbpool.queue);
				dev_kमुक्त_skb_any(handle1);
				skb_unlink(handle2, &card->lbpool.queue);
				dev_kमुक्त_skb_any(handle2);
				वापस;
			पूर्ण अन्यथा
				card->lbfqc += 2;
		पूर्ण

		id1 = idr_alloc(&card->idr, handle1, 0, 0, GFP_ATOMIC);
		अगर (id1 < 0)
			जाओ out;

		id2 = idr_alloc(&card->idr, handle2, 0, 0, GFP_ATOMIC);
		अगर (id2 < 0)
			जाओ out;

		spin_lock_irqsave(&card->res_lock, flags);
		जबतक (CMD_BUSY(card)) ;
		ग_लिखोl(addr2, card->membase + DR3);
		ग_लिखोl(id2, card->membase + DR2);
		ग_लिखोl(addr1, card->membase + DR1);
		ग_लिखोl(id1, card->membase + DR0);
		ग_लिखोl(NS_CMD_WRITE_FREEBUFQ | NS_PRV_BUFTYPE(skb),
		       card->membase + CMD);
		spin_unlock_irqrestore(&card->res_lock, flags);

		XPRINTK("nicstar%d: Pushing %s buffers at 0x%x and 0x%x.\n",
			card->index,
			(NS_PRV_BUFTYPE(skb) == BUF_SM ? "small" : "large"),
			addr1, addr2);
	पूर्ण

	अगर (!card->efbie && card->sbfqc >= card->sbnr.min &&
	    card->lbfqc >= card->lbnr.min) अणु
		card->efbie = 1;
		ग_लिखोl((पढ़ोl(card->membase + CFG) | NS_CFG_EFBIE),
		       card->membase + CFG);
	पूर्ण

out:
	वापस;
पूर्ण

अटल irqवापस_t ns_irq_handler(पूर्णांक irq, व्योम *dev_id)
अणु
	u32 stat_r;
	ns_dev *card;
	काष्ठा aपंचांग_dev *dev;
	अचिन्हित दीर्घ flags;

	card = (ns_dev *) dev_id;
	dev = card->aपंचांगdev;
	card->पूर्णांकcnt++;

	PRINTK("nicstar%d: NICStAR generated an interrupt\n", card->index);

	spin_lock_irqsave(&card->पूर्णांक_lock, flags);

	stat_r = पढ़ोl(card->membase + STAT);

	/* Transmit Status Indicator has been written to T. S. Queue */
	अगर (stat_r & NS_STAT_TSIF) अणु
		TXPRINTK("nicstar%d: TSI interrupt\n", card->index);
		process_tsq(card);
		ग_लिखोl(NS_STAT_TSIF, card->membase + STAT);
	पूर्ण

	/* Incomplete CS-PDU has been transmitted */
	अगर (stat_r & NS_STAT_TXICP) अणु
		ग_लिखोl(NS_STAT_TXICP, card->membase + STAT);
		TXPRINTK("nicstar%d: Incomplete CS-PDU transmitted.\n",
			 card->index);
	पूर्ण

	/* Transmit Status Queue 7/8 full */
	अगर (stat_r & NS_STAT_TSQF) अणु
		ग_लिखोl(NS_STAT_TSQF, card->membase + STAT);
		PRINTK("nicstar%d: TSQ full.\n", card->index);
		process_tsq(card);
	पूर्ण

	/* Timer overflow */
	अगर (stat_r & NS_STAT_TMROF) अणु
		ग_लिखोl(NS_STAT_TMROF, card->membase + STAT);
		PRINTK("nicstar%d: Timer overflow.\n", card->index);
	पूर्ण

	/* PHY device पूर्णांकerrupt संकेत active */
	अगर (stat_r & NS_STAT_PHYI) अणु
		ग_लिखोl(NS_STAT_PHYI, card->membase + STAT);
		PRINTK("nicstar%d: PHY interrupt.\n", card->index);
		अगर (dev->phy && dev->phy->पूर्णांकerrupt) अणु
			dev->phy->पूर्णांकerrupt(dev);
		पूर्ण
	पूर्ण

	/* Small Buffer Queue is full */
	अगर (stat_r & NS_STAT_SFBQF) अणु
		ग_लिखोl(NS_STAT_SFBQF, card->membase + STAT);
		prपूर्णांकk("nicstar%d: Small free buffer queue is full.\n",
		       card->index);
	पूर्ण

	/* Large Buffer Queue is full */
	अगर (stat_r & NS_STAT_LFBQF) अणु
		ग_लिखोl(NS_STAT_LFBQF, card->membase + STAT);
		prपूर्णांकk("nicstar%d: Large free buffer queue is full.\n",
		       card->index);
	पूर्ण

	/* Receive Status Queue is full */
	अगर (stat_r & NS_STAT_RSQF) अणु
		ग_लिखोl(NS_STAT_RSQF, card->membase + STAT);
		prपूर्णांकk("nicstar%d: RSQ full.\n", card->index);
		process_rsq(card);
	पूर्ण

	/* Complete CS-PDU received */
	अगर (stat_r & NS_STAT_EOPDU) अणु
		RXPRINTK("nicstar%d: End of CS-PDU received.\n", card->index);
		process_rsq(card);
		ग_लिखोl(NS_STAT_EOPDU, card->membase + STAT);
	पूर्ण

	/* Raw cell received */
	अगर (stat_r & NS_STAT_RAWCF) अणु
		ग_लिखोl(NS_STAT_RAWCF, card->membase + STAT);
#अगर_अघोषित RCQ_SUPPORT
		prपूर्णांकk("nicstar%d: Raw cell received and no support yet...\n",
		       card->index);
#पूर्ण_अगर /* RCQ_SUPPORT */
		/* NOTE: the following procedure may keep a raw cell pending until the
		   next पूर्णांकerrupt. As this preliminary support is only meant to
		   aव्योम buffer leakage, this is not an issue. */
		जबतक (पढ़ोl(card->membase + RAWCT) != card->rawch) अणु

			अगर (ns_rcqe_islast(card->rawcell)) अणु
				काष्ठा sk_buff *oldbuf;

				oldbuf = card->rcbuf;
				card->rcbuf = idr_find(&card->idr,
						       ns_rcqe_nextbufhandle(card->rawcell));
				card->rawch = NS_PRV_DMA(card->rcbuf);
				card->rawcell = (काष्ठा ns_rcqe *)
						card->rcbuf->data;
				recycle_rx_buf(card, oldbuf);
			पूर्ण अन्यथा अणु
				card->rawch += NS_RCQE_SIZE;
				card->rawcell++;
			पूर्ण
		पूर्ण
	पूर्ण

	/* Small buffer queue is empty */
	अगर (stat_r & NS_STAT_SFBQE) अणु
		पूर्णांक i;
		काष्ठा sk_buff *sb;

		ग_लिखोl(NS_STAT_SFBQE, card->membase + STAT);
		prपूर्णांकk("nicstar%d: Small free buffer queue empty.\n",
		       card->index);
		क्रम (i = 0; i < card->sbnr.min; i++) अणु
			sb = dev_alloc_skb(NS_SMSKBSIZE);
			अगर (sb == शून्य) अणु
				ग_लिखोl(पढ़ोl(card->membase + CFG) &
				       ~NS_CFG_EFBIE, card->membase + CFG);
				card->efbie = 0;
				अवरोध;
			पूर्ण
			NS_PRV_BUFTYPE(sb) = BUF_SM;
			skb_queue_tail(&card->sbpool.queue, sb);
			skb_reserve(sb, NS_AAL0_HEADER);
			push_rxbufs(card, sb);
		पूर्ण
		card->sbfqc = i;
		process_rsq(card);
	पूर्ण

	/* Large buffer queue empty */
	अगर (stat_r & NS_STAT_LFBQE) अणु
		पूर्णांक i;
		काष्ठा sk_buff *lb;

		ग_लिखोl(NS_STAT_LFBQE, card->membase + STAT);
		prपूर्णांकk("nicstar%d: Large free buffer queue empty.\n",
		       card->index);
		क्रम (i = 0; i < card->lbnr.min; i++) अणु
			lb = dev_alloc_skb(NS_LGSKBSIZE);
			अगर (lb == शून्य) अणु
				ग_लिखोl(पढ़ोl(card->membase + CFG) &
				       ~NS_CFG_EFBIE, card->membase + CFG);
				card->efbie = 0;
				अवरोध;
			पूर्ण
			NS_PRV_BUFTYPE(lb) = BUF_LG;
			skb_queue_tail(&card->lbpool.queue, lb);
			skb_reserve(lb, NS_SMबफ_मानE);
			push_rxbufs(card, lb);
		पूर्ण
		card->lbfqc = i;
		process_rsq(card);
	पूर्ण

	/* Receive Status Queue is 7/8 full */
	अगर (stat_r & NS_STAT_RSQAF) अणु
		ग_लिखोl(NS_STAT_RSQAF, card->membase + STAT);
		RXPRINTK("nicstar%d: RSQ almost full.\n", card->index);
		process_rsq(card);
	पूर्ण

	spin_unlock_irqrestore(&card->पूर्णांक_lock, flags);
	PRINTK("nicstar%d: end of interrupt service\n", card->index);
	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक ns_खोलो(काष्ठा aपंचांग_vcc *vcc)
अणु
	ns_dev *card;
	vc_map *vc;
	अचिन्हित दीर्घ पंचांगpl, modl;
	पूर्णांक tcr, tcra;		/* target cell rate, and असलolute value */
	पूर्णांक n = 0;		/* Number of entries in the TST. Initialized to हटाओ
				   the compiler warning. */
	u32 u32d[4];
	पूर्णांक frscdi = 0;		/* Index of the SCD. Initialized to हटाओ the compiler
				   warning. How I wish compilers were clever enough to
				   tell which variables can truly be used
				   uninitialized... */
	पूर्णांक inuse;		/* tx or rx vc alपढ़ोy in use by another vcc */
	लघु vpi = vcc->vpi;
	पूर्णांक vci = vcc->vci;

	card = (ns_dev *) vcc->dev->dev_data;
	PRINTK("nicstar%d: opening vpi.vci %d.%d \n", card->index, (पूर्णांक)vpi,
	       vci);
	अगर (vcc->qos.aal != ATM_AAL5 && vcc->qos.aal != ATM_AAL0) अणु
		PRINTK("nicstar%d: unsupported AAL.\n", card->index);
		वापस -EINVAL;
	पूर्ण

	vc = &(card->vcmap[vpi << card->vcibits | vci]);
	vcc->dev_data = vc;

	inuse = 0;
	अगर (vcc->qos.txtp.traffic_class != ATM_NONE && vc->tx)
		inuse = 1;
	अगर (vcc->qos.rxtp.traffic_class != ATM_NONE && vc->rx)
		inuse += 2;
	अगर (inuse) अणु
		prपूर्णांकk("nicstar%d: %s vci already in use.\n", card->index,
		       inuse == 1 ? "tx" : inuse == 2 ? "rx" : "tx and rx");
		वापस -EINVAL;
	पूर्ण

	set_bit(ATM_VF_ADDR, &vcc->flags);

	/* NOTE: You are not allowed to modअगरy an खोलो connection's QOS. To change
	   that, हटाओ the ATM_VF_PARTIAL flag checking. There may be other changes
	   needed to करो that. */
	अगर (!test_bit(ATM_VF_PARTIAL, &vcc->flags)) अणु
		scq_info *scq;

		set_bit(ATM_VF_PARTIAL, &vcc->flags);
		अगर (vcc->qos.txtp.traffic_class == ATM_CBR) अणु
			/* Check requested cell rate and availability of SCD */
			अगर (vcc->qos.txtp.max_pcr == 0 && vcc->qos.txtp.pcr == 0
			    && vcc->qos.txtp.min_pcr == 0) अणु
				PRINTK
				    ("nicstar%d: trying to open a CBR vc with cell rate = 0 \n",
				     card->index);
				clear_bit(ATM_VF_PARTIAL, &vcc->flags);
				clear_bit(ATM_VF_ADDR, &vcc->flags);
				वापस -EINVAL;
			पूर्ण

			tcr = aपंचांग_pcr_goal(&(vcc->qos.txtp));
			tcra = tcr >= 0 ? tcr : -tcr;

			PRINTK("nicstar%d: target cell rate = %d.\n",
			       card->index, vcc->qos.txtp.max_pcr);

			पंचांगpl =
			    (अचिन्हित दीर्घ)tcra *(अचिन्हित दीर्घ)
			    NS_TST_NUM_ENTRIES;
			modl = पंचांगpl % card->max_pcr;

			n = (पूर्णांक)(पंचांगpl / card->max_pcr);
			अगर (tcr > 0) अणु
				अगर (modl > 0)
					n++;
			पूर्ण अन्यथा अगर (tcr == 0) अणु
				अगर ((n =
				     (card->tst_मुक्त_entries -
				      NS_TST_RESERVED)) <= 0) अणु
					PRINTK
					    ("nicstar%d: no CBR bandwidth free.\n",
					     card->index);
					clear_bit(ATM_VF_PARTIAL, &vcc->flags);
					clear_bit(ATM_VF_ADDR, &vcc->flags);
					वापस -EINVAL;
				पूर्ण
			पूर्ण

			अगर (n == 0) अणु
				prपूर्णांकk
				    ("nicstar%d: selected bandwidth < granularity.\n",
				     card->index);
				clear_bit(ATM_VF_PARTIAL, &vcc->flags);
				clear_bit(ATM_VF_ADDR, &vcc->flags);
				वापस -EINVAL;
			पूर्ण

			अगर (n > (card->tst_मुक्त_entries - NS_TST_RESERVED)) अणु
				PRINTK
				    ("nicstar%d: not enough free CBR bandwidth.\n",
				     card->index);
				clear_bit(ATM_VF_PARTIAL, &vcc->flags);
				clear_bit(ATM_VF_ADDR, &vcc->flags);
				वापस -EINVAL;
			पूर्ण अन्यथा
				card->tst_मुक्त_entries -= n;

			XPRINTK("nicstar%d: writing %d tst entries.\n",
				card->index, n);
			क्रम (frscdi = 0; frscdi < NS_FRSCD_NUM; frscdi++) अणु
				अगर (card->scd2vc[frscdi] == शून्य) अणु
					card->scd2vc[frscdi] = vc;
					अवरोध;
				पूर्ण
			पूर्ण
			अगर (frscdi == NS_FRSCD_NUM) अणु
				PRINTK
				    ("nicstar%d: no SCD available for CBR channel.\n",
				     card->index);
				card->tst_मुक्त_entries += n;
				clear_bit(ATM_VF_PARTIAL, &vcc->flags);
				clear_bit(ATM_VF_ADDR, &vcc->flags);
				वापस -EBUSY;
			पूर्ण

			vc->cbr_scd = NS_FRSCD + frscdi * NS_FRSCD_SIZE;

			scq = get_scq(card, CBR_SCQSIZE, vc->cbr_scd);
			अगर (scq == शून्य) अणु
				PRINTK("nicstar%d: can't get fixed rate SCQ.\n",
				       card->index);
				card->scd2vc[frscdi] = शून्य;
				card->tst_मुक्त_entries += n;
				clear_bit(ATM_VF_PARTIAL, &vcc->flags);
				clear_bit(ATM_VF_ADDR, &vcc->flags);
				वापस -ENOMEM;
			पूर्ण
			vc->scq = scq;
			u32d[0] = scq_virt_to_bus(scq, scq->base);
			u32d[1] = (u32) 0x00000000;
			u32d[2] = (u32) 0xffffffff;
			u32d[3] = (u32) 0x00000000;
			ns_ग_लिखो_sram(card, vc->cbr_scd, u32d, 4);

			fill_tst(card, n, vc);
		पूर्ण अन्यथा अगर (vcc->qos.txtp.traffic_class == ATM_UBR) अणु
			vc->cbr_scd = 0x00000000;
			vc->scq = card->scq0;
		पूर्ण

		अगर (vcc->qos.txtp.traffic_class != ATM_NONE) अणु
			vc->tx = 1;
			vc->tx_vcc = vcc;
			vc->tbd_count = 0;
		पूर्ण
		अगर (vcc->qos.rxtp.traffic_class != ATM_NONE) अणु
			u32 status;

			vc->rx = 1;
			vc->rx_vcc = vcc;
			vc->rx_iov = शून्य;

			/* Open the connection in hardware */
			अगर (vcc->qos.aal == ATM_AAL5)
				status = NS_RCTE_AAL5 | NS_RCTE_CONNECTOPEN;
			अन्यथा	/* vcc->qos.aal == ATM_AAL0 */
				status = NS_RCTE_AAL0 | NS_RCTE_CONNECTOPEN;
#अगर_घोषित RCQ_SUPPORT
			status |= NS_RCTE_RAWCELLINTEN;
#पूर्ण_अगर /* RCQ_SUPPORT */
			ns_ग_लिखो_sram(card,
				      NS_RCT +
				      (vpi << card->vcibits | vci) *
				      NS_RCT_ENTRY_SIZE, &status, 1);
		पूर्ण

	पूर्ण

	set_bit(ATM_VF_READY, &vcc->flags);
	वापस 0;
पूर्ण

अटल व्योम ns_बंद(काष्ठा aपंचांग_vcc *vcc)
अणु
	vc_map *vc;
	ns_dev *card;
	u32 data;
	पूर्णांक i;

	vc = vcc->dev_data;
	card = vcc->dev->dev_data;
	PRINTK("nicstar%d: closing vpi.vci %d.%d \n", card->index,
	       (पूर्णांक)vcc->vpi, vcc->vci);

	clear_bit(ATM_VF_READY, &vcc->flags);

	अगर (vcc->qos.rxtp.traffic_class != ATM_NONE) अणु
		u32 addr;
		अचिन्हित दीर्घ flags;

		addr =
		    NS_RCT +
		    (vcc->vpi << card->vcibits | vcc->vci) * NS_RCT_ENTRY_SIZE;
		spin_lock_irqsave(&card->res_lock, flags);
		जबतक (CMD_BUSY(card)) ;
		ग_लिखोl(NS_CMD_CLOSE_CONNECTION | addr << 2,
		       card->membase + CMD);
		spin_unlock_irqrestore(&card->res_lock, flags);

		vc->rx = 0;
		अगर (vc->rx_iov != शून्य) अणु
			काष्ठा sk_buff *iovb;
			u32 stat;

			stat = पढ़ोl(card->membase + STAT);
			card->sbfqc = ns_stat_sfbqc_get(stat);
			card->lbfqc = ns_stat_lfbqc_get(stat);

			PRINTK
			    ("nicstar%d: closing a VC with pending rx buffers.\n",
			     card->index);
			iovb = vc->rx_iov;
			recycle_iovec_rx_bufs(card, (काष्ठा iovec *)iovb->data,
					      NS_PRV_IOVCNT(iovb));
			NS_PRV_IOVCNT(iovb) = 0;
			spin_lock_irqsave(&card->पूर्णांक_lock, flags);
			recycle_iov_buf(card, iovb);
			spin_unlock_irqrestore(&card->पूर्णांक_lock, flags);
			vc->rx_iov = शून्य;
		पूर्ण
	पूर्ण

	अगर (vcc->qos.txtp.traffic_class != ATM_NONE) अणु
		vc->tx = 0;
	पूर्ण

	अगर (vcc->qos.txtp.traffic_class == ATM_CBR) अणु
		अचिन्हित दीर्घ flags;
		ns_scqe *scqep;
		scq_info *scq;

		scq = vc->scq;

		क्रम (;;) अणु
			spin_lock_irqsave(&scq->lock, flags);
			scqep = scq->next;
			अगर (scqep == scq->base)
				scqep = scq->last;
			अन्यथा
				scqep--;
			अगर (scqep == scq->tail) अणु
				spin_unlock_irqrestore(&scq->lock, flags);
				अवरोध;
			पूर्ण
			/* If the last entry is not a TSR, place one in the SCQ in order to
			   be able to completely drain it and then बंद. */
			अगर (!ns_scqe_is_tsr(scqep) && scq->tail != scq->next) अणु
				ns_scqe tsr;
				u32 scdi, scqi;
				u32 data;
				पूर्णांक index;

				tsr.word_1 = ns_tsr_mkword_1(NS_TSR_INTENABLE);
				scdi = (vc->cbr_scd - NS_FRSCD) / NS_FRSCD_SIZE;
				scqi = scq->next - scq->base;
				tsr.word_2 = ns_tsr_mkword_2(scdi, scqi);
				tsr.word_3 = 0x00000000;
				tsr.word_4 = 0x00000000;
				*scq->next = tsr;
				index = (पूर्णांक)scqi;
				scq->skb[index] = शून्य;
				अगर (scq->next == scq->last)
					scq->next = scq->base;
				अन्यथा
					scq->next++;
				data = scq_virt_to_bus(scq, scq->next);
				ns_ग_लिखो_sram(card, scq->scd, &data, 1);
			पूर्ण
			spin_unlock_irqrestore(&scq->lock, flags);
			schedule();
		पूर्ण

		/* Free all TST entries */
		data = NS_TST_OPCODE_VARIABLE;
		क्रम (i = 0; i < NS_TST_NUM_ENTRIES; i++) अणु
			अगर (card->tste2vc[i] == vc) अणु
				ns_ग_लिखो_sram(card, card->tst_addr + i, &data,
					      1);
				card->tste2vc[i] = शून्य;
				card->tst_मुक्त_entries++;
			पूर्ण
		पूर्ण

		card->scd2vc[(vc->cbr_scd - NS_FRSCD) / NS_FRSCD_SIZE] = शून्य;
		मुक्त_scq(card, vc->scq, vcc);
	पूर्ण

	/* हटाओ all references to vcc beक्रमe deleting it */
	अगर (vcc->qos.txtp.traffic_class != ATM_NONE) अणु
		अचिन्हित दीर्घ flags;
		scq_info *scq = card->scq0;

		spin_lock_irqsave(&scq->lock, flags);

		क्रम (i = 0; i < scq->num_entries; i++) अणु
			अगर (scq->skb[i] && ATM_SKB(scq->skb[i])->vcc == vcc) अणु
				ATM_SKB(scq->skb[i])->vcc = शून्य;
				aपंचांग_वापस(vcc, scq->skb[i]->truesize);
				PRINTK
				    ("nicstar: deleted pending vcc mapping\n");
			पूर्ण
		पूर्ण

		spin_unlock_irqrestore(&scq->lock, flags);
	पूर्ण

	vcc->dev_data = शून्य;
	clear_bit(ATM_VF_PARTIAL, &vcc->flags);
	clear_bit(ATM_VF_ADDR, &vcc->flags);

#अगर_घोषित RX_DEBUG
	अणु
		u32 stat, cfg;
		stat = पढ़ोl(card->membase + STAT);
		cfg = पढ़ोl(card->membase + CFG);
		prपूर्णांकk("STAT = 0x%08X  CFG = 0x%08X  \n", stat, cfg);
		prपूर्णांकk
		    ("TSQ: base = 0x%p  next = 0x%p  last = 0x%p  TSQT = 0x%08X \n",
		     card->tsq.base, card->tsq.next,
		     card->tsq.last, पढ़ोl(card->membase + TSQT));
		prपूर्णांकk
		    ("RSQ: base = 0x%p  next = 0x%p  last = 0x%p  RSQT = 0x%08X \n",
		     card->rsq.base, card->rsq.next,
		     card->rsq.last, पढ़ोl(card->membase + RSQT));
		prपूर्णांकk("Empty free buffer queue interrupt %s \n",
		       card->efbie ? "enabled" : "disabled");
		prपूर्णांकk("SBCNT = %d  count = %d   LBCNT = %d count = %d \n",
		       ns_stat_sfbqc_get(stat), card->sbpool.count,
		       ns_stat_lfbqc_get(stat), card->lbpool.count);
		prपूर्णांकk("hbpool.count = %d  iovpool.count = %d \n",
		       card->hbpool.count, card->iovpool.count);
	पूर्ण
#पूर्ण_अगर /* RX_DEBUG */
पूर्ण

अटल व्योम fill_tst(ns_dev * card, पूर्णांक n, vc_map * vc)
अणु
	u32 new_tst;
	अचिन्हित दीर्घ cl;
	पूर्णांक e, r;
	u32 data;

	/* It would be very complicated to keep the two TSTs synchronized जबतक
	   assuring that ग_लिखोs are only made to the inactive TST. So, क्रम now I
	   will use only one TST. If problems occur, I will change this again */

	new_tst = card->tst_addr;

	/* Fill procedure */

	क्रम (e = 0; e < NS_TST_NUM_ENTRIES; e++) अणु
		अगर (card->tste2vc[e] == शून्य)
			अवरोध;
	पूर्ण
	अगर (e == NS_TST_NUM_ENTRIES) अणु
		prपूर्णांकk("nicstar%d: No free TST entries found. \n", card->index);
		वापस;
	पूर्ण

	r = n;
	cl = NS_TST_NUM_ENTRIES;
	data = ns_tste_make(NS_TST_OPCODE_FIXED, vc->cbr_scd);

	जबतक (r > 0) अणु
		अगर (cl >= NS_TST_NUM_ENTRIES && card->tste2vc[e] == शून्य) अणु
			card->tste2vc[e] = vc;
			ns_ग_लिखो_sram(card, new_tst + e, &data, 1);
			cl -= NS_TST_NUM_ENTRIES;
			r--;
		पूर्ण

		अगर (++e == NS_TST_NUM_ENTRIES) अणु
			e = 0;
		पूर्ण
		cl += n;
	पूर्ण

	/* End of fill procedure */

	data = ns_tste_make(NS_TST_OPCODE_END, new_tst);
	ns_ग_लिखो_sram(card, new_tst + NS_TST_NUM_ENTRIES, &data, 1);
	ns_ग_लिखो_sram(card, card->tst_addr + NS_TST_NUM_ENTRIES, &data, 1);
	card->tst_addr = new_tst;
पूर्ण

अटल पूर्णांक _ns_send(काष्ठा aपंचांग_vcc *vcc, काष्ठा sk_buff *skb, bool may_sleep)
अणु
	ns_dev *card;
	vc_map *vc;
	scq_info *scq;
	अचिन्हित दीर्घ buflen;
	ns_scqe scqe;
	u32 flags;		/* TBD flags, not CPU flags */

	card = vcc->dev->dev_data;
	TXPRINTK("nicstar%d: ns_send() called.\n", card->index);
	अगर ((vc = (vc_map *) vcc->dev_data) == शून्य) अणु
		prपूर्णांकk("nicstar%d: vcc->dev_data == NULL on ns_send().\n",
		       card->index);
		atomic_inc(&vcc->stats->tx_err);
		dev_kमुक्त_skb_any(skb);
		वापस -EINVAL;
	पूर्ण

	अगर (!vc->tx) अणु
		prपूर्णांकk("nicstar%d: Trying to transmit on a non-tx VC.\n",
		       card->index);
		atomic_inc(&vcc->stats->tx_err);
		dev_kमुक्त_skb_any(skb);
		वापस -EINVAL;
	पूर्ण

	अगर (vcc->qos.aal != ATM_AAL5 && vcc->qos.aal != ATM_AAL0) अणु
		prपूर्णांकk("nicstar%d: Only AAL0 and AAL5 are supported.\n",
		       card->index);
		atomic_inc(&vcc->stats->tx_err);
		dev_kमुक्त_skb_any(skb);
		वापस -EINVAL;
	पूर्ण

	अगर (skb_shinfo(skb)->nr_frags != 0) अणु
		prपूर्णांकk("nicstar%d: No scatter-gather yet.\n", card->index);
		atomic_inc(&vcc->stats->tx_err);
		dev_kमुक्त_skb_any(skb);
		वापस -EINVAL;
	पूर्ण

	ATM_SKB(skb)->vcc = vcc;

	NS_PRV_DMA(skb) = dma_map_single(&card->pcidev->dev, skb->data,
					 skb->len, DMA_TO_DEVICE);

	अगर (vcc->qos.aal == ATM_AAL5) अणु
		buflen = (skb->len + 47 + 8) / 48 * 48;	/* Multiple of 48 */
		flags = NS_TBD_AAL5;
		scqe.word_2 = cpu_to_le32(NS_PRV_DMA(skb));
		scqe.word_3 = cpu_to_le32(skb->len);
		scqe.word_4 =
		    ns_tbd_mkword_4(0, (u32) vcc->vpi, (u32) vcc->vci, 0,
				    ATM_SKB(skb)->
				    aपंचांग_options & ATM_ATMOPT_CLP ? 1 : 0);
		flags |= NS_TBD_EOPDU;
	पूर्ण अन्यथा अणु		/* (vcc->qos.aal == ATM_AAL0) */

		buflen = ATM_CELL_PAYLOAD;	/* i.e., 48 bytes */
		flags = NS_TBD_AAL0;
		scqe.word_2 = cpu_to_le32(NS_PRV_DMA(skb) + NS_AAL0_HEADER);
		scqe.word_3 = cpu_to_le32(0x00000000);
		अगर (*skb->data & 0x02)	/* Payload type 1 - end of pdu */
			flags |= NS_TBD_EOPDU;
		scqe.word_4 =
		    cpu_to_le32(*((u32 *) skb->data) & ~NS_TBD_VC_MASK);
		/* Force the VPI/VCI to be the same as in VCC काष्ठा */
		scqe.word_4 |=
		    cpu_to_le32((((u32) vcc->
				  vpi) << NS_TBD_VPI_SHIFT | ((u32) vcc->
							      vci) <<
				 NS_TBD_VCI_SHIFT) & NS_TBD_VC_MASK);
	पूर्ण

	अगर (vcc->qos.txtp.traffic_class == ATM_CBR) अणु
		scqe.word_1 = ns_tbd_mkword_1_novbr(flags, (u32) buflen);
		scq = ((vc_map *) vcc->dev_data)->scq;
	पूर्ण अन्यथा अणु
		scqe.word_1 =
		    ns_tbd_mkword_1(flags, (u32) 1, (u32) 1, (u32) buflen);
		scq = card->scq0;
	पूर्ण

	अगर (push_scqe(card, vc, scq, &scqe, skb, may_sleep) != 0) अणु
		atomic_inc(&vcc->stats->tx_err);
		dma_unmap_single(&card->pcidev->dev, NS_PRV_DMA(skb), skb->len,
				 DMA_TO_DEVICE);
		dev_kमुक्त_skb_any(skb);
		वापस -EIO;
	पूर्ण
	atomic_inc(&vcc->stats->tx);

	वापस 0;
पूर्ण

अटल पूर्णांक ns_send(काष्ठा aपंचांग_vcc *vcc, काष्ठा sk_buff *skb)
अणु
	वापस _ns_send(vcc, skb, true);
पूर्ण

अटल पूर्णांक ns_send_bh(काष्ठा aपंचांग_vcc *vcc, काष्ठा sk_buff *skb)
अणु
	वापस _ns_send(vcc, skb, false);
पूर्ण

अटल पूर्णांक push_scqe(ns_dev * card, vc_map * vc, scq_info * scq, ns_scqe * tbd,
		     काष्ठा sk_buff *skb, bool may_sleep)
अणु
	अचिन्हित दीर्घ flags;
	ns_scqe tsr;
	u32 scdi, scqi;
	पूर्णांक scq_is_vbr;
	u32 data;
	पूर्णांक index;

	spin_lock_irqsave(&scq->lock, flags);
	जबतक (scq->tail == scq->next) अणु
		अगर (!may_sleep) अणु
			spin_unlock_irqrestore(&scq->lock, flags);
			prपूर्णांकk("nicstar%d: Error pushing TBD.\n", card->index);
			वापस 1;
		पूर्ण

		scq->full = 1;
		रुको_event_पूर्णांकerruptible_lock_irq_समयout(scq->scqfull_रुकोq,
							  scq->tail != scq->next,
							  scq->lock,
							  SCQFULL_TIMEOUT);

		अगर (scq->full) अणु
			spin_unlock_irqrestore(&scq->lock, flags);
			prपूर्णांकk("nicstar%d: Timeout pushing TBD.\n",
			       card->index);
			वापस 1;
		पूर्ण
	पूर्ण
	*scq->next = *tbd;
	index = (पूर्णांक)(scq->next - scq->base);
	scq->skb[index] = skb;
	XPRINTK("nicstar%d: sending skb at 0x%p (pos %d).\n",
		card->index, skb, index);
	XPRINTK("nicstar%d: TBD written:\n0x%x\n0x%x\n0x%x\n0x%x\n at 0x%p.\n",
		card->index, le32_to_cpu(tbd->word_1), le32_to_cpu(tbd->word_2),
		le32_to_cpu(tbd->word_3), le32_to_cpu(tbd->word_4),
		scq->next);
	अगर (scq->next == scq->last)
		scq->next = scq->base;
	अन्यथा
		scq->next++;

	vc->tbd_count++;
	अगर (scq->num_entries == VBR_SCQ_NUM_ENTRIES) अणु
		scq->tbd_count++;
		scq_is_vbr = 1;
	पूर्ण अन्यथा
		scq_is_vbr = 0;

	अगर (vc->tbd_count >= MAX_TBD_PER_VC
	    || scq->tbd_count >= MAX_TBD_PER_SCQ) अणु
		पूर्णांक has_run = 0;

		जबतक (scq->tail == scq->next) अणु
			अगर (!may_sleep) अणु
				data = scq_virt_to_bus(scq, scq->next);
				ns_ग_लिखो_sram(card, scq->scd, &data, 1);
				spin_unlock_irqrestore(&scq->lock, flags);
				prपूर्णांकk("nicstar%d: Error pushing TSR.\n",
				       card->index);
				वापस 0;
			पूर्ण

			scq->full = 1;
			अगर (has_run++)
				अवरोध;
			रुको_event_पूर्णांकerruptible_lock_irq_समयout(scq->scqfull_रुकोq,
								  scq->tail != scq->next,
								  scq->lock,
								  SCQFULL_TIMEOUT);
		पूर्ण

		अगर (!scq->full) अणु
			tsr.word_1 = ns_tsr_mkword_1(NS_TSR_INTENABLE);
			अगर (scq_is_vbr)
				scdi = NS_TSR_SCDISVBR;
			अन्यथा
				scdi = (vc->cbr_scd - NS_FRSCD) / NS_FRSCD_SIZE;
			scqi = scq->next - scq->base;
			tsr.word_2 = ns_tsr_mkword_2(scdi, scqi);
			tsr.word_3 = 0x00000000;
			tsr.word_4 = 0x00000000;

			*scq->next = tsr;
			index = (पूर्णांक)scqi;
			scq->skb[index] = शून्य;
			XPRINTK
			    ("nicstar%d: TSR written:\n0x%x\n0x%x\n0x%x\n0x%x\n at 0x%p.\n",
			     card->index, le32_to_cpu(tsr.word_1),
			     le32_to_cpu(tsr.word_2), le32_to_cpu(tsr.word_3),
			     le32_to_cpu(tsr.word_4), scq->next);
			अगर (scq->next == scq->last)
				scq->next = scq->base;
			अन्यथा
				scq->next++;
			vc->tbd_count = 0;
			scq->tbd_count = 0;
		पूर्ण अन्यथा
			PRINTK("nicstar%d: Timeout pushing TSR.\n",
			       card->index);
	पूर्ण
	data = scq_virt_to_bus(scq, scq->next);
	ns_ग_लिखो_sram(card, scq->scd, &data, 1);

	spin_unlock_irqrestore(&scq->lock, flags);

	वापस 0;
पूर्ण

अटल व्योम process_tsq(ns_dev * card)
अणु
	u32 scdi;
	scq_info *scq;
	ns_tsi *previous = शून्य, *one_ahead, *two_ahead;
	पूर्णांक serviced_entries;	/* flag indicating at least on entry was serviced */

	serviced_entries = 0;

	अगर (card->tsq.next == card->tsq.last)
		one_ahead = card->tsq.base;
	अन्यथा
		one_ahead = card->tsq.next + 1;

	अगर (one_ahead == card->tsq.last)
		two_ahead = card->tsq.base;
	अन्यथा
		two_ahead = one_ahead + 1;

	जबतक (!ns_tsi_isempty(card->tsq.next) || !ns_tsi_isempty(one_ahead) ||
	       !ns_tsi_isempty(two_ahead))
		/* At most two empty, as stated in the 77201 errata */
	अणु
		serviced_entries = 1;

		/* Skip the one or two possible empty entries */
		जबतक (ns_tsi_isempty(card->tsq.next)) अणु
			अगर (card->tsq.next == card->tsq.last)
				card->tsq.next = card->tsq.base;
			अन्यथा
				card->tsq.next++;
		पूर्ण

		अगर (!ns_tsi_पंचांगrof(card->tsq.next)) अणु
			scdi = ns_tsi_माला_लोcdindex(card->tsq.next);
			अगर (scdi == NS_TSI_SCDISVBR)
				scq = card->scq0;
			अन्यथा अणु
				अगर (card->scd2vc[scdi] == शून्य) अणु
					prपूर्णांकk
					    ("nicstar%d: could not find VC from SCD index.\n",
					     card->index);
					ns_tsi_init(card->tsq.next);
					वापस;
				पूर्ण
				scq = card->scd2vc[scdi]->scq;
			पूर्ण
			drain_scq(card, scq, ns_tsi_माला_लोcqpos(card->tsq.next));
			scq->full = 0;
			wake_up_पूर्णांकerruptible(&(scq->scqfull_रुकोq));
		पूर्ण

		ns_tsi_init(card->tsq.next);
		previous = card->tsq.next;
		अगर (card->tsq.next == card->tsq.last)
			card->tsq.next = card->tsq.base;
		अन्यथा
			card->tsq.next++;

		अगर (card->tsq.next == card->tsq.last)
			one_ahead = card->tsq.base;
		अन्यथा
			one_ahead = card->tsq.next + 1;

		अगर (one_ahead == card->tsq.last)
			two_ahead = card->tsq.base;
		अन्यथा
			two_ahead = one_ahead + 1;
	पूर्ण

	अगर (serviced_entries)
		ग_लिखोl(PTR_DIFF(previous, card->tsq.base),
		       card->membase + TSQH);
पूर्ण

अटल व्योम drain_scq(ns_dev * card, scq_info * scq, पूर्णांक pos)
अणु
	काष्ठा aपंचांग_vcc *vcc;
	काष्ठा sk_buff *skb;
	पूर्णांक i;
	अचिन्हित दीर्घ flags;

	XPRINTK("nicstar%d: drain_scq() called, scq at 0x%p, pos %d.\n",
		card->index, scq, pos);
	अगर (pos >= scq->num_entries) अणु
		prपूर्णांकk("nicstar%d: Bad index on drain_scq().\n", card->index);
		वापस;
	पूर्ण

	spin_lock_irqsave(&scq->lock, flags);
	i = (पूर्णांक)(scq->tail - scq->base);
	अगर (++i == scq->num_entries)
		i = 0;
	जबतक (i != pos) अणु
		skb = scq->skb[i];
		XPRINTK("nicstar%d: freeing skb at 0x%p (index %d).\n",
			card->index, skb, i);
		अगर (skb != शून्य) अणु
			dma_unmap_single(&card->pcidev->dev,
					 NS_PRV_DMA(skb),
					 skb->len,
					 DMA_TO_DEVICE);
			vcc = ATM_SKB(skb)->vcc;
			अगर (vcc && vcc->pop != शून्य) अणु
				vcc->pop(vcc, skb);
			पूर्ण अन्यथा अणु
				dev_kमुक्त_skb_irq(skb);
			पूर्ण
			scq->skb[i] = शून्य;
		पूर्ण
		अगर (++i == scq->num_entries)
			i = 0;
	पूर्ण
	scq->tail = scq->base + pos;
	spin_unlock_irqrestore(&scq->lock, flags);
पूर्ण

अटल व्योम process_rsq(ns_dev * card)
अणु
	ns_rsqe *previous;

	अगर (!ns_rsqe_valid(card->rsq.next))
		वापस;
	करो अणु
		dequeue_rx(card, card->rsq.next);
		ns_rsqe_init(card->rsq.next);
		previous = card->rsq.next;
		अगर (card->rsq.next == card->rsq.last)
			card->rsq.next = card->rsq.base;
		अन्यथा
			card->rsq.next++;
	पूर्ण जबतक (ns_rsqe_valid(card->rsq.next));
	ग_लिखोl(PTR_DIFF(previous, card->rsq.base), card->membase + RSQH);
पूर्ण

अटल व्योम dequeue_rx(ns_dev * card, ns_rsqe * rsqe)
अणु
	u32 vpi, vci;
	vc_map *vc;
	काष्ठा sk_buff *iovb;
	काष्ठा iovec *iov;
	काष्ठा aपंचांग_vcc *vcc;
	काष्ठा sk_buff *skb;
	अचिन्हित लघु aal5_len;
	पूर्णांक len;
	u32 stat;
	u32 id;

	stat = पढ़ोl(card->membase + STAT);
	card->sbfqc = ns_stat_sfbqc_get(stat);
	card->lbfqc = ns_stat_lfbqc_get(stat);

	id = le32_to_cpu(rsqe->buffer_handle);
	skb = idr_हटाओ(&card->idr, id);
	अगर (!skb) अणु
		RXPRINTK(KERN_ERR
			 "nicstar%d: skb not found!\n", card->index);
		वापस;
	पूर्ण
	dma_sync_single_क्रम_cpu(&card->pcidev->dev,
				NS_PRV_DMA(skb),
				(NS_PRV_BUFTYPE(skb) == BUF_SM
				 ? NS_SMSKBSIZE : NS_LGSKBSIZE),
				DMA_FROM_DEVICE);
	dma_unmap_single(&card->pcidev->dev,
			 NS_PRV_DMA(skb),
			 (NS_PRV_BUFTYPE(skb) == BUF_SM
			  ? NS_SMSKBSIZE : NS_LGSKBSIZE),
			 DMA_FROM_DEVICE);
	vpi = ns_rsqe_vpi(rsqe);
	vci = ns_rsqe_vci(rsqe);
	अगर (vpi >= 1UL << card->vpibits || vci >= 1UL << card->vcibits) अणु
		prपूर्णांकk("nicstar%d: SDU received for out-of-range vc %d.%d.\n",
		       card->index, vpi, vci);
		recycle_rx_buf(card, skb);
		वापस;
	पूर्ण

	vc = &(card->vcmap[vpi << card->vcibits | vci]);
	अगर (!vc->rx) अणु
		RXPRINTK("nicstar%d: SDU received on non-rx vc %d.%d.\n",
			 card->index, vpi, vci);
		recycle_rx_buf(card, skb);
		वापस;
	पूर्ण

	vcc = vc->rx_vcc;

	अगर (vcc->qos.aal == ATM_AAL0) अणु
		काष्ठा sk_buff *sb;
		अचिन्हित अक्षर *cell;
		पूर्णांक i;

		cell = skb->data;
		क्रम (i = ns_rsqe_cellcount(rsqe); i; i--) अणु
			sb = dev_alloc_skb(NS_SMSKBSIZE);
			अगर (!sb) अणु
				prपूर्णांकk
				    ("nicstar%d: Can't allocate buffers for aal0.\n",
				     card->index);
				atomic_add(i, &vcc->stats->rx_drop);
				अवरोध;
			पूर्ण
			अगर (!aपंचांग_अक्षरge(vcc, sb->truesize)) अणु
				RXPRINTK
				    ("nicstar%d: atm_charge() dropped aal0 packets.\n",
				     card->index);
				atomic_add(i - 1, &vcc->stats->rx_drop);	/* alपढ़ोy increased by 1 */
				dev_kमुक्त_skb_any(sb);
				अवरोध;
			पूर्ण
			/* Rebuild the header */
			*((u32 *) sb->data) = le32_to_cpu(rsqe->word_1) << 4 |
			    (ns_rsqe_clp(rsqe) ? 0x00000001 : 0x00000000);
			अगर (i == 1 && ns_rsqe_eopdu(rsqe))
				*((u32 *) sb->data) |= 0x00000002;
			skb_put(sb, NS_AAL0_HEADER);
			स_नकल(skb_tail_poपूर्णांकer(sb), cell, ATM_CELL_PAYLOAD);
			skb_put(sb, ATM_CELL_PAYLOAD);
			ATM_SKB(sb)->vcc = vcc;
			__net_बारtamp(sb);
			vcc->push(vcc, sb);
			atomic_inc(&vcc->stats->rx);
			cell += ATM_CELL_PAYLOAD;
		पूर्ण

		recycle_rx_buf(card, skb);
		वापस;
	पूर्ण

	/* To reach this poपूर्णांक, the AAL layer can only be AAL5 */

	अगर ((iovb = vc->rx_iov) == शून्य) अणु
		iovb = skb_dequeue(&(card->iovpool.queue));
		अगर (iovb == शून्य) अणु	/* No buffers in the queue */
			iovb = alloc_skb(NS_IOVबफ_मानE, GFP_ATOMIC);
			अगर (iovb == शून्य) अणु
				prपूर्णांकk("nicstar%d: Out of iovec buffers.\n",
				       card->index);
				atomic_inc(&vcc->stats->rx_drop);
				recycle_rx_buf(card, skb);
				वापस;
			पूर्ण
			NS_PRV_BUFTYPE(iovb) = BUF_NONE;
		पूर्ण अन्यथा अगर (--card->iovpool.count < card->iovnr.min) अणु
			काष्ठा sk_buff *new_iovb;
			अगर ((new_iovb =
			     alloc_skb(NS_IOVबफ_मानE, GFP_ATOMIC)) != शून्य) अणु
				NS_PRV_BUFTYPE(iovb) = BUF_NONE;
				skb_queue_tail(&card->iovpool.queue, new_iovb);
				card->iovpool.count++;
			पूर्ण
		पूर्ण
		vc->rx_iov = iovb;
		NS_PRV_IOVCNT(iovb) = 0;
		iovb->len = 0;
		iovb->data = iovb->head;
		skb_reset_tail_poपूर्णांकer(iovb);
		/* IMPORTANT: a poपूर्णांकer to the sk_buff containing the small or large
		   buffer is stored as iovec base, NOT a poपूर्णांकer to the
		   small or large buffer itself. */
	पूर्ण अन्यथा अगर (NS_PRV_IOVCNT(iovb) >= NS_MAX_IOVECS) अणु
		prपूर्णांकk("nicstar%d: received too big AAL5 SDU.\n", card->index);
		atomic_inc(&vcc->stats->rx_err);
		recycle_iovec_rx_bufs(card, (काष्ठा iovec *)iovb->data,
				      NS_MAX_IOVECS);
		NS_PRV_IOVCNT(iovb) = 0;
		iovb->len = 0;
		iovb->data = iovb->head;
		skb_reset_tail_poपूर्णांकer(iovb);
	पूर्ण
	iov = &((काष्ठा iovec *)iovb->data)[NS_PRV_IOVCNT(iovb)++];
	iov->iov_base = (व्योम *)skb;
	iov->iov_len = ns_rsqe_cellcount(rsqe) * 48;
	iovb->len += iov->iov_len;

#अगर_घोषित EXTRA_DEBUG
	अगर (NS_PRV_IOVCNT(iovb) == 1) अणु
		अगर (NS_PRV_BUFTYPE(skb) != BUF_SM) अणु
			prपूर्णांकk
			    ("nicstar%d: Expected a small buffer, and this is not one.\n",
			     card->index);
			which_list(card, skb);
			atomic_inc(&vcc->stats->rx_err);
			recycle_rx_buf(card, skb);
			vc->rx_iov = शून्य;
			recycle_iov_buf(card, iovb);
			वापस;
		पूर्ण
	पूर्ण अन्यथा अणु		/* NS_PRV_IOVCNT(iovb) >= 2 */

		अगर (NS_PRV_BUFTYPE(skb) != BUF_LG) अणु
			prपूर्णांकk
			    ("nicstar%d: Expected a large buffer, and this is not one.\n",
			     card->index);
			which_list(card, skb);
			atomic_inc(&vcc->stats->rx_err);
			recycle_iovec_rx_bufs(card, (काष्ठा iovec *)iovb->data,
					      NS_PRV_IOVCNT(iovb));
			vc->rx_iov = शून्य;
			recycle_iov_buf(card, iovb);
			वापस;
		पूर्ण
	पूर्ण
#पूर्ण_अगर /* EXTRA_DEBUG */

	अगर (ns_rsqe_eopdu(rsqe)) अणु
		/* This works correctly regardless of the endianness of the host */
		अचिन्हित अक्षर *L1L2 = (अचिन्हित अक्षर *)
						(skb->data + iov->iov_len - 6);
		aal5_len = L1L2[0] << 8 | L1L2[1];
		len = (aal5_len == 0x0000) ? 0x10000 : aal5_len;
		अगर (ns_rsqe_crcerr(rsqe) ||
		    len + 8 > iovb->len || len + (47 + 8) < iovb->len) अणु
			prपूर्णांकk("nicstar%d: AAL5 CRC error", card->index);
			अगर (len + 8 > iovb->len || len + (47 + 8) < iovb->len)
				prपूर्णांकk(" - PDU size mismatch.\n");
			अन्यथा
				prपूर्णांकk(".\n");
			atomic_inc(&vcc->stats->rx_err);
			recycle_iovec_rx_bufs(card, (काष्ठा iovec *)iovb->data,
					      NS_PRV_IOVCNT(iovb));
			vc->rx_iov = शून्य;
			recycle_iov_buf(card, iovb);
			वापस;
		पूर्ण

		/* By this poपूर्णांक we (hopefully) have a complete SDU without errors. */

		अगर (NS_PRV_IOVCNT(iovb) == 1) अणु	/* Just a small buffer */
			/* skb poपूर्णांकs to a small buffer */
			अगर (!aपंचांग_अक्षरge(vcc, skb->truesize)) अणु
				push_rxbufs(card, skb);
				atomic_inc(&vcc->stats->rx_drop);
			पूर्ण अन्यथा अणु
				skb_put(skb, len);
				dequeue_sm_buf(card, skb);
				ATM_SKB(skb)->vcc = vcc;
				__net_बारtamp(skb);
				vcc->push(vcc, skb);
				atomic_inc(&vcc->stats->rx);
			पूर्ण
		पूर्ण अन्यथा अगर (NS_PRV_IOVCNT(iovb) == 2) अणु	/* One small plus one large buffer */
			काष्ठा sk_buff *sb;

			sb = (काष्ठा sk_buff *)(iov - 1)->iov_base;
			/* skb poपूर्णांकs to a large buffer */

			अगर (len <= NS_SMबफ_मानE) अणु
				अगर (!aपंचांग_अक्षरge(vcc, sb->truesize)) अणु
					push_rxbufs(card, sb);
					atomic_inc(&vcc->stats->rx_drop);
				पूर्ण अन्यथा अणु
					skb_put(sb, len);
					dequeue_sm_buf(card, sb);
					ATM_SKB(sb)->vcc = vcc;
					__net_बारtamp(sb);
					vcc->push(vcc, sb);
					atomic_inc(&vcc->stats->rx);
				पूर्ण

				push_rxbufs(card, skb);

			पूर्ण अन्यथा अणु	/* len > NS_SMबफ_मानE, the usual हाल */

				अगर (!aपंचांग_अक्षरge(vcc, skb->truesize)) अणु
					push_rxbufs(card, skb);
					atomic_inc(&vcc->stats->rx_drop);
				पूर्ण अन्यथा अणु
					dequeue_lg_buf(card, skb);
					skb_push(skb, NS_SMबफ_मानE);
					skb_copy_from_linear_data(sb, skb->data,
								  NS_SMबफ_मानE);
					skb_put(skb, len - NS_SMबफ_मानE);
					ATM_SKB(skb)->vcc = vcc;
					__net_बारtamp(skb);
					vcc->push(vcc, skb);
					atomic_inc(&vcc->stats->rx);
				पूर्ण

				push_rxbufs(card, sb);

			पूर्ण

		पूर्ण अन्यथा अणु	/* Must push a huge buffer */

			काष्ठा sk_buff *hb, *sb, *lb;
			पूर्णांक reमुख्यing, tocopy;
			पूर्णांक j;

			hb = skb_dequeue(&(card->hbpool.queue));
			अगर (hb == शून्य) अणु	/* No buffers in the queue */

				hb = dev_alloc_skb(NS_Hबफ_मानE);
				अगर (hb == शून्य) अणु
					prपूर्णांकk
					    ("nicstar%d: Out of huge buffers.\n",
					     card->index);
					atomic_inc(&vcc->stats->rx_drop);
					recycle_iovec_rx_bufs(card,
							      (काष्ठा iovec *)
							      iovb->data,
							      NS_PRV_IOVCNT(iovb));
					vc->rx_iov = शून्य;
					recycle_iov_buf(card, iovb);
					वापस;
				पूर्ण अन्यथा अगर (card->hbpool.count < card->hbnr.min) अणु
					काष्ठा sk_buff *new_hb;
					अगर ((new_hb =
					     dev_alloc_skb(NS_Hबफ_मानE)) !=
					    शून्य) अणु
						skb_queue_tail(&card->hbpool.
							       queue, new_hb);
						card->hbpool.count++;
					पूर्ण
				पूर्ण
				NS_PRV_BUFTYPE(hb) = BUF_NONE;
			पूर्ण अन्यथा अगर (--card->hbpool.count < card->hbnr.min) अणु
				काष्ठा sk_buff *new_hb;
				अगर ((new_hb =
				     dev_alloc_skb(NS_Hबफ_मानE)) != शून्य) अणु
					NS_PRV_BUFTYPE(new_hb) = BUF_NONE;
					skb_queue_tail(&card->hbpool.queue,
						       new_hb);
					card->hbpool.count++;
				पूर्ण
				अगर (card->hbpool.count < card->hbnr.min) अणु
					अगर ((new_hb =
					     dev_alloc_skb(NS_Hबफ_मानE)) !=
					    शून्य) अणु
						NS_PRV_BUFTYPE(new_hb) =
						    BUF_NONE;
						skb_queue_tail(&card->hbpool.
							       queue, new_hb);
						card->hbpool.count++;
					पूर्ण
				पूर्ण
			पूर्ण

			iov = (काष्ठा iovec *)iovb->data;

			अगर (!aपंचांग_अक्षरge(vcc, hb->truesize)) अणु
				recycle_iovec_rx_bufs(card, iov,
						      NS_PRV_IOVCNT(iovb));
				अगर (card->hbpool.count < card->hbnr.max) अणु
					skb_queue_tail(&card->hbpool.queue, hb);
					card->hbpool.count++;
				पूर्ण अन्यथा
					dev_kमुक्त_skb_any(hb);
				atomic_inc(&vcc->stats->rx_drop);
			पूर्ण अन्यथा अणु
				/* Copy the small buffer to the huge buffer */
				sb = (काष्ठा sk_buff *)iov->iov_base;
				skb_copy_from_linear_data(sb, hb->data,
							  iov->iov_len);
				skb_put(hb, iov->iov_len);
				reमुख्यing = len - iov->iov_len;
				iov++;
				/* Free the small buffer */
				push_rxbufs(card, sb);

				/* Copy all large buffers to the huge buffer and मुक्त them */
				क्रम (j = 1; j < NS_PRV_IOVCNT(iovb); j++) अणु
					lb = (काष्ठा sk_buff *)iov->iov_base;
					tocopy =
					    min_t(पूर्णांक, reमुख्यing, iov->iov_len);
					skb_copy_from_linear_data(lb,
								  skb_tail_poपूर्णांकer
								  (hb), tocopy);
					skb_put(hb, tocopy);
					iov++;
					reमुख्यing -= tocopy;
					push_rxbufs(card, lb);
				पूर्ण
#अगर_घोषित EXTRA_DEBUG
				अगर (reमुख्यing != 0 || hb->len != len)
					prपूर्णांकk
					    ("nicstar%d: Huge buffer len mismatch.\n",
					     card->index);
#पूर्ण_अगर /* EXTRA_DEBUG */
				ATM_SKB(hb)->vcc = vcc;
				__net_बारtamp(hb);
				vcc->push(vcc, hb);
				atomic_inc(&vcc->stats->rx);
			पूर्ण
		पूर्ण

		vc->rx_iov = शून्य;
		recycle_iov_buf(card, iovb);
	पूर्ण

पूर्ण

अटल व्योम recycle_rx_buf(ns_dev * card, काष्ठा sk_buff *skb)
अणु
	अगर (unlikely(NS_PRV_BUFTYPE(skb) == BUF_NONE)) अणु
		prपूर्णांकk("nicstar%d: What kind of rx buffer is this?\n",
		       card->index);
		dev_kमुक्त_skb_any(skb);
	पूर्ण अन्यथा
		push_rxbufs(card, skb);
पूर्ण

अटल व्योम recycle_iovec_rx_bufs(ns_dev * card, काष्ठा iovec *iov, पूर्णांक count)
अणु
	जबतक (count-- > 0)
		recycle_rx_buf(card, (काष्ठा sk_buff *)(iov++)->iov_base);
पूर्ण

अटल व्योम recycle_iov_buf(ns_dev * card, काष्ठा sk_buff *iovb)
अणु
	अगर (card->iovpool.count < card->iovnr.max) अणु
		skb_queue_tail(&card->iovpool.queue, iovb);
		card->iovpool.count++;
	पूर्ण अन्यथा
		dev_kमुक्त_skb_any(iovb);
पूर्ण

अटल व्योम dequeue_sm_buf(ns_dev * card, काष्ठा sk_buff *sb)
अणु
	skb_unlink(sb, &card->sbpool.queue);
	अगर (card->sbfqc < card->sbnr.init) अणु
		काष्ठा sk_buff *new_sb;
		अगर ((new_sb = dev_alloc_skb(NS_SMSKBSIZE)) != शून्य) अणु
			NS_PRV_BUFTYPE(new_sb) = BUF_SM;
			skb_queue_tail(&card->sbpool.queue, new_sb);
			skb_reserve(new_sb, NS_AAL0_HEADER);
			push_rxbufs(card, new_sb);
		पूर्ण
	पूर्ण
	अगर (card->sbfqc < card->sbnr.init)
	अणु
		काष्ठा sk_buff *new_sb;
		अगर ((new_sb = dev_alloc_skb(NS_SMSKBSIZE)) != शून्य) अणु
			NS_PRV_BUFTYPE(new_sb) = BUF_SM;
			skb_queue_tail(&card->sbpool.queue, new_sb);
			skb_reserve(new_sb, NS_AAL0_HEADER);
			push_rxbufs(card, new_sb);
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम dequeue_lg_buf(ns_dev * card, काष्ठा sk_buff *lb)
अणु
	skb_unlink(lb, &card->lbpool.queue);
	अगर (card->lbfqc < card->lbnr.init) अणु
		काष्ठा sk_buff *new_lb;
		अगर ((new_lb = dev_alloc_skb(NS_LGSKBSIZE)) != शून्य) अणु
			NS_PRV_BUFTYPE(new_lb) = BUF_LG;
			skb_queue_tail(&card->lbpool.queue, new_lb);
			skb_reserve(new_lb, NS_SMबफ_मानE);
			push_rxbufs(card, new_lb);
		पूर्ण
	पूर्ण
	अगर (card->lbfqc < card->lbnr.init)
	अणु
		काष्ठा sk_buff *new_lb;
		अगर ((new_lb = dev_alloc_skb(NS_LGSKBSIZE)) != शून्य) अणु
			NS_PRV_BUFTYPE(new_lb) = BUF_LG;
			skb_queue_tail(&card->lbpool.queue, new_lb);
			skb_reserve(new_lb, NS_SMबफ_मानE);
			push_rxbufs(card, new_lb);
		पूर्ण
	पूर्ण
पूर्ण

अटल पूर्णांक ns_proc_पढ़ो(काष्ठा aपंचांग_dev *dev, loff_t * pos, अक्षर *page)
अणु
	u32 stat;
	ns_dev *card;
	पूर्णांक left;

	left = (पूर्णांक)*pos;
	card = (ns_dev *) dev->dev_data;
	stat = पढ़ोl(card->membase + STAT);
	अगर (!left--)
		वापस प्र_लिखो(page, "Pool   count    min   init    max \n");
	अगर (!left--)
		वापस प्र_लिखो(page, "Small  %5d  %5d  %5d  %5d \n",
			       ns_stat_sfbqc_get(stat), card->sbnr.min,
			       card->sbnr.init, card->sbnr.max);
	अगर (!left--)
		वापस प्र_लिखो(page, "Large  %5d  %5d  %5d  %5d \n",
			       ns_stat_lfbqc_get(stat), card->lbnr.min,
			       card->lbnr.init, card->lbnr.max);
	अगर (!left--)
		वापस प्र_लिखो(page, "Huge   %5d  %5d  %5d  %5d \n",
			       card->hbpool.count, card->hbnr.min,
			       card->hbnr.init, card->hbnr.max);
	अगर (!left--)
		वापस प्र_लिखो(page, "Iovec  %5d  %5d  %5d  %5d \n",
			       card->iovpool.count, card->iovnr.min,
			       card->iovnr.init, card->iovnr.max);
	अगर (!left--) अणु
		पूर्णांक retval;
		retval =
		    प्र_लिखो(page, "Interrupt counter: %u \n", card->पूर्णांकcnt);
		card->पूर्णांकcnt = 0;
		वापस retval;
	पूर्ण
#अगर 0
	/* Dump 25.6 Mbps PHY रेजिस्टरs */
	/* Now there's a 25.6 Mbps PHY driver this code isn't needed. I left it
	   here just in हाल it's needed क्रम debugging. */
	अगर (card->max_pcr == ATM_25_PCR && !left--) अणु
		u32 phy_regs[4];
		u32 i;

		क्रम (i = 0; i < 4; i++) अणु
			जबतक (CMD_BUSY(card)) ;
			ग_लिखोl(NS_CMD_READ_UTILITY | 0x00000200 | i,
			       card->membase + CMD);
			जबतक (CMD_BUSY(card)) ;
			phy_regs[i] = पढ़ोl(card->membase + DR0) & 0x000000FF;
		पूर्ण

		वापस प्र_लिखो(page, "PHY regs: 0x%02X 0x%02X 0x%02X 0x%02X \n",
			       phy_regs[0], phy_regs[1], phy_regs[2],
			       phy_regs[3]);
	पूर्ण
#पूर्ण_अगर /* 0 - Dump 25.6 Mbps PHY रेजिस्टरs */
#अगर 0
	/* Dump TST */
	अगर (left-- < NS_TST_NUM_ENTRIES) अणु
		अगर (card->tste2vc[left + 1] == शून्य)
			वापस प्र_लिखो(page, "%5d - VBR/UBR \n", left + 1);
		अन्यथा
			वापस प्र_लिखो(page, "%5d - %d %d \n", left + 1,
				       card->tste2vc[left + 1]->tx_vcc->vpi,
				       card->tste2vc[left + 1]->tx_vcc->vci);
	पूर्ण
#पूर्ण_अगर /* 0 */
	वापस 0;
पूर्ण

अटल पूर्णांक ns_ioctl(काष्ठा aपंचांग_dev *dev, अचिन्हित पूर्णांक cmd, व्योम __user * arg)
अणु
	ns_dev *card;
	pool_levels pl;
	दीर्घ btype;
	अचिन्हित दीर्घ flags;

	card = dev->dev_data;
	चयन (cmd) अणु
	हाल NS_GETPSTAT:
		अगर (get_user
		    (pl.buftype, &((pool_levels __user *) arg)->buftype))
			वापस -EFAULT;
		चयन (pl.buftype) अणु
		हाल NS_BUFTYPE_SMALL:
			pl.count =
			    ns_stat_sfbqc_get(पढ़ोl(card->membase + STAT));
			pl.level.min = card->sbnr.min;
			pl.level.init = card->sbnr.init;
			pl.level.max = card->sbnr.max;
			अवरोध;

		हाल NS_BUFTYPE_LARGE:
			pl.count =
			    ns_stat_lfbqc_get(पढ़ोl(card->membase + STAT));
			pl.level.min = card->lbnr.min;
			pl.level.init = card->lbnr.init;
			pl.level.max = card->lbnr.max;
			अवरोध;

		हाल NS_BUFTYPE_HUGE:
			pl.count = card->hbpool.count;
			pl.level.min = card->hbnr.min;
			pl.level.init = card->hbnr.init;
			pl.level.max = card->hbnr.max;
			अवरोध;

		हाल NS_BUFTYPE_IOVEC:
			pl.count = card->iovpool.count;
			pl.level.min = card->iovnr.min;
			pl.level.init = card->iovnr.init;
			pl.level.max = card->iovnr.max;
			अवरोध;

		शेष:
			वापस -ENOIOCTLCMD;

		पूर्ण
		अगर (!copy_to_user((pool_levels __user *) arg, &pl, माप(pl)))
			वापस (माप(pl));
		अन्यथा
			वापस -EFAULT;

	हाल NS_SETBUFLEV:
		अगर (!capable(CAP_NET_ADMIN))
			वापस -EPERM;
		अगर (copy_from_user(&pl, (pool_levels __user *) arg, माप(pl)))
			वापस -EFAULT;
		अगर (pl.level.min >= pl.level.init
		    || pl.level.init >= pl.level.max)
			वापस -EINVAL;
		अगर (pl.level.min == 0)
			वापस -EINVAL;
		चयन (pl.buftype) अणु
		हाल NS_BUFTYPE_SMALL:
			अगर (pl.level.max > TOP_SB)
				वापस -EINVAL;
			card->sbnr.min = pl.level.min;
			card->sbnr.init = pl.level.init;
			card->sbnr.max = pl.level.max;
			अवरोध;

		हाल NS_BUFTYPE_LARGE:
			अगर (pl.level.max > TOP_LB)
				वापस -EINVAL;
			card->lbnr.min = pl.level.min;
			card->lbnr.init = pl.level.init;
			card->lbnr.max = pl.level.max;
			अवरोध;

		हाल NS_BUFTYPE_HUGE:
			अगर (pl.level.max > TOP_HB)
				वापस -EINVAL;
			card->hbnr.min = pl.level.min;
			card->hbnr.init = pl.level.init;
			card->hbnr.max = pl.level.max;
			अवरोध;

		हाल NS_BUFTYPE_IOVEC:
			अगर (pl.level.max > TOP_IOVB)
				वापस -EINVAL;
			card->iovnr.min = pl.level.min;
			card->iovnr.init = pl.level.init;
			card->iovnr.max = pl.level.max;
			अवरोध;

		शेष:
			वापस -EINVAL;

		पूर्ण
		वापस 0;

	हाल NS_ADJBUFLEV:
		अगर (!capable(CAP_NET_ADMIN))
			वापस -EPERM;
		btype = (दीर्घ)arg;	/* a दीर्घ is the same size as a poपूर्णांकer or bigger */
		चयन (btype) अणु
		हाल NS_BUFTYPE_SMALL:
			जबतक (card->sbfqc < card->sbnr.init) अणु
				काष्ठा sk_buff *sb;

				sb = __dev_alloc_skb(NS_SMSKBSIZE, GFP_KERNEL);
				अगर (sb == शून्य)
					वापस -ENOMEM;
				NS_PRV_BUFTYPE(sb) = BUF_SM;
				skb_queue_tail(&card->sbpool.queue, sb);
				skb_reserve(sb, NS_AAL0_HEADER);
				push_rxbufs(card, sb);
			पूर्ण
			अवरोध;

		हाल NS_BUFTYPE_LARGE:
			जबतक (card->lbfqc < card->lbnr.init) अणु
				काष्ठा sk_buff *lb;

				lb = __dev_alloc_skb(NS_LGSKBSIZE, GFP_KERNEL);
				अगर (lb == शून्य)
					वापस -ENOMEM;
				NS_PRV_BUFTYPE(lb) = BUF_LG;
				skb_queue_tail(&card->lbpool.queue, lb);
				skb_reserve(lb, NS_SMबफ_मानE);
				push_rxbufs(card, lb);
			पूर्ण
			अवरोध;

		हाल NS_BUFTYPE_HUGE:
			जबतक (card->hbpool.count > card->hbnr.init) अणु
				काष्ठा sk_buff *hb;

				spin_lock_irqsave(&card->पूर्णांक_lock, flags);
				hb = skb_dequeue(&card->hbpool.queue);
				card->hbpool.count--;
				spin_unlock_irqrestore(&card->पूर्णांक_lock, flags);
				अगर (hb == शून्य)
					prपूर्णांकk
					    ("nicstar%d: huge buffer count inconsistent.\n",
					     card->index);
				अन्यथा
					dev_kमुक्त_skb_any(hb);

			पूर्ण
			जबतक (card->hbpool.count < card->hbnr.init) अणु
				काष्ठा sk_buff *hb;

				hb = __dev_alloc_skb(NS_Hबफ_मानE, GFP_KERNEL);
				अगर (hb == शून्य)
					वापस -ENOMEM;
				NS_PRV_BUFTYPE(hb) = BUF_NONE;
				spin_lock_irqsave(&card->पूर्णांक_lock, flags);
				skb_queue_tail(&card->hbpool.queue, hb);
				card->hbpool.count++;
				spin_unlock_irqrestore(&card->पूर्णांक_lock, flags);
			पूर्ण
			अवरोध;

		हाल NS_BUFTYPE_IOVEC:
			जबतक (card->iovpool.count > card->iovnr.init) अणु
				काष्ठा sk_buff *iovb;

				spin_lock_irqsave(&card->पूर्णांक_lock, flags);
				iovb = skb_dequeue(&card->iovpool.queue);
				card->iovpool.count--;
				spin_unlock_irqrestore(&card->पूर्णांक_lock, flags);
				अगर (iovb == शून्य)
					prपूर्णांकk
					    ("nicstar%d: iovec buffer count inconsistent.\n",
					     card->index);
				अन्यथा
					dev_kमुक्त_skb_any(iovb);

			पूर्ण
			जबतक (card->iovpool.count < card->iovnr.init) अणु
				काष्ठा sk_buff *iovb;

				iovb = alloc_skb(NS_IOVबफ_मानE, GFP_KERNEL);
				अगर (iovb == शून्य)
					वापस -ENOMEM;
				NS_PRV_BUFTYPE(iovb) = BUF_NONE;
				spin_lock_irqsave(&card->पूर्णांक_lock, flags);
				skb_queue_tail(&card->iovpool.queue, iovb);
				card->iovpool.count++;
				spin_unlock_irqrestore(&card->पूर्णांक_lock, flags);
			पूर्ण
			अवरोध;

		शेष:
			वापस -EINVAL;

		पूर्ण
		वापस 0;

	शेष:
		अगर (dev->phy && dev->phy->ioctl) अणु
			वापस dev->phy->ioctl(dev, cmd, arg);
		पूर्ण अन्यथा अणु
			prपूर्णांकk("nicstar%d: %s == NULL \n", card->index,
			       dev->phy ? "dev->phy->ioctl" : "dev->phy");
			वापस -ENOIOCTLCMD;
		पूर्ण
	पूर्ण
पूर्ण

#अगर_घोषित EXTRA_DEBUG
अटल व्योम which_list(ns_dev * card, काष्ठा sk_buff *skb)
अणु
	prपूर्णांकk("skb buf_type: 0x%08x\n", NS_PRV_BUFTYPE(skb));
पूर्ण
#पूर्ण_अगर /* EXTRA_DEBUG */

अटल व्योम ns_poll(काष्ठा समयr_list *unused)
अणु
	पूर्णांक i;
	ns_dev *card;
	अचिन्हित दीर्घ flags;
	u32 stat_r, stat_w;

	PRINTK("nicstar: Entering ns_poll().\n");
	क्रम (i = 0; i < num_cards; i++) अणु
		card = cards[i];
		अगर (!spin_trylock_irqsave(&card->पूर्णांक_lock, flags)) अणु
			/* Probably it isn't worth spinning */
			जारी;
		पूर्ण

		stat_w = 0;
		stat_r = पढ़ोl(card->membase + STAT);
		अगर (stat_r & NS_STAT_TSIF)
			stat_w |= NS_STAT_TSIF;
		अगर (stat_r & NS_STAT_EOPDU)
			stat_w |= NS_STAT_EOPDU;

		process_tsq(card);
		process_rsq(card);

		ग_लिखोl(stat_w, card->membase + STAT);
		spin_unlock_irqrestore(&card->पूर्णांक_lock, flags);
	पूर्ण
	mod_समयr(&ns_समयr, jअगरfies + NS_POLL_PERIOD);
	PRINTK("nicstar: Leaving ns_poll().\n");
पूर्ण

अटल व्योम ns_phy_put(काष्ठा aपंचांग_dev *dev, अचिन्हित अक्षर value,
		       अचिन्हित दीर्घ addr)
अणु
	ns_dev *card;
	अचिन्हित दीर्घ flags;

	card = dev->dev_data;
	spin_lock_irqsave(&card->res_lock, flags);
	जबतक (CMD_BUSY(card)) ;
	ग_लिखोl((u32) value, card->membase + DR0);
	ग_लिखोl(NS_CMD_WRITE_UTILITY | 0x00000200 | (addr & 0x000000FF),
	       card->membase + CMD);
	spin_unlock_irqrestore(&card->res_lock, flags);
पूर्ण

अटल अचिन्हित अक्षर ns_phy_get(काष्ठा aपंचांग_dev *dev, अचिन्हित दीर्घ addr)
अणु
	ns_dev *card;
	अचिन्हित दीर्घ flags;
	u32 data;

	card = dev->dev_data;
	spin_lock_irqsave(&card->res_lock, flags);
	जबतक (CMD_BUSY(card)) ;
	ग_लिखोl(NS_CMD_READ_UTILITY | 0x00000200 | (addr & 0x000000FF),
	       card->membase + CMD);
	जबतक (CMD_BUSY(card)) ;
	data = पढ़ोl(card->membase + DR0) & 0x000000FF;
	spin_unlock_irqrestore(&card->res_lock, flags);
	वापस (अचिन्हित अक्षर)data;
पूर्ण

module_init(nicstar_init);
module_निकास(nicstar_cleanup);
