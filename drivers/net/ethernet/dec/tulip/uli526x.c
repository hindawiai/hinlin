<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*


*/

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#घोषणा DRV_NAME	"uli526x"

#समावेश <linux/module.h>

#समावेश <linux/kernel.h>
#समावेश <linux/माला.स>
#समावेश <linux/समयr.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/ioport.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/pci.h>
#समावेश <linux/init.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/etherdevice.h>
#समावेश <linux/ethtool.h>
#समावेश <linux/skbuff.h>
#समावेश <linux/delay.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/dma-mapping.h>
#समावेश <linux/bitops.h>

#समावेश <यंत्र/processor.h>
#समावेश <यंत्र/पन.स>
#समावेश <यंत्र/dma.h>
#समावेश <linux/uaccess.h>

#घोषणा uw32(reg, val)	ioग_लिखो32(val, ioaddr + (reg))
#घोषणा ur32(reg)	ioपढ़ो32(ioaddr + (reg))

/* Board/System/Debug inक्रमmation/definition ---------------- */
#घोषणा PCI_ULI5261_ID  0x526110B9	/* ULi M5261 ID*/
#घोषणा PCI_ULI5263_ID  0x526310B9	/* ULi M5263 ID*/

#घोषणा ULI526X_IO_SIZE 0x100
#घोषणा TX_DESC_CNT     0x20            /* Allocated Tx descriptors */
#घोषणा RX_DESC_CNT     0x30            /* Allocated Rx descriptors */
#घोषणा TX_FREE_DESC_CNT (TX_DESC_CNT - 2)	/* Max TX packet count */
#घोषणा TX_WAKE_DESC_CNT (TX_DESC_CNT - 3)	/* TX wakeup count */
#घोषणा DESC_ALL_CNT    (TX_DESC_CNT + RX_DESC_CNT)
#घोषणा TX_BUF_ALLOC    0x600
#घोषणा RX_ALLOC_SIZE   0x620
#घोषणा ULI526X_RESET    1
#घोषणा CR0_DEFAULT     0
#घोषणा CR6_DEFAULT     0x22200000
#घोषणा CR7_DEFAULT     0x180c1
#घोषणा CR15_DEFAULT    0x06            /* TxJabber RxWatchकरोg */
#घोषणा TDES0_ERR_MASK  0x4302          /* TXJT, LC, EC, FUE */
#घोषणा MAX_PACKET_SIZE 1514
#घोषणा ULI5261_MAX_MULTICAST 14
#घोषणा RX_COPY_SIZE	100
#घोषणा MAX_CHECK_PACKET 0x8000

#घोषणा ULI526X_10MHF      0
#घोषणा ULI526X_100MHF     1
#घोषणा ULI526X_10MFD      4
#घोषणा ULI526X_100MFD     5
#घोषणा ULI526X_AUTO       8

#घोषणा ULI526X_TXTH_72	0x400000	/* TX TH 72 byte */
#घोषणा ULI526X_TXTH_96	0x404000	/* TX TH 96 byte */
#घोषणा ULI526X_TXTH_128	0x0000		/* TX TH 128 byte */
#घोषणा ULI526X_TXTH_256	0x4000		/* TX TH 256 byte */
#घोषणा ULI526X_TXTH_512	0x8000		/* TX TH 512 byte */
#घोषणा ULI526X_TXTH_1K	0xC000		/* TX TH 1K  byte */

#घोषणा ULI526X_TIMER_WUT  (jअगरfies + HZ * 1)/* समयr wakeup समय : 1 second */
#घोषणा ULI526X_TX_TIMEOUT ((16*HZ)/2)	/* tx packet समय-out समय 8 s" */
#घोषणा ULI526X_TX_KICK 	(4*HZ/2)	/* tx packet Kick-out समय 2 s" */

#घोषणा ULI526X_DBUG(dbug_now, msg, value)			\
करो अणु								\
	अगर (uli526x_debug || (dbug_now))			\
		pr_err("%s %lx\n", (msg), (दीर्घ) (value));	\
पूर्ण जबतक (0)

#घोषणा SHOW_MEDIA_TYPE(mode)					\
	pr_err("Change Speed to %sMhz %s duplex\n",		\
	       mode & 1 ? "100" : "10",				\
	       mode & 4 ? "full" : "half");


/* CR9 definition: SROM/MII */
#घोषणा CR9_SROM_READ   0x4800
#घोषणा CR9_SRCS        0x1
#घोषणा CR9_SRCLK       0x2
#घोषणा CR9_CRDOUT      0x8
#घोषणा SROM_DATA_0     0x0
#घोषणा SROM_DATA_1     0x4
#घोषणा PHY_DATA_1      0x20000
#घोषणा PHY_DATA_0      0x00000
#घोषणा MDCLKH          0x10000

#घोषणा PHY_POWER_DOWN	0x800

#घोषणा SROM_V41_CODE   0x14

/* Structure/क्रमागत declaration ------------------------------- */
काष्ठा tx_desc अणु
        __le32 tdes0, tdes1, tdes2, tdes3; /* Data क्रम the card */
        अक्षर *tx_buf_ptr;               /* Data क्रम us */
        काष्ठा tx_desc *next_tx_desc;
पूर्ण __attribute__(( aligned(32) ));

काष्ठा rx_desc अणु
	__le32 rdes0, rdes1, rdes2, rdes3; /* Data क्रम the card */
	काष्ठा sk_buff *rx_skb_ptr;	/* Data क्रम us */
	काष्ठा rx_desc *next_rx_desc;
पूर्ण __attribute__(( aligned(32) ));

काष्ठा uli526x_board_info अणु
	काष्ठा uli_phy_ops अणु
		व्योम (*ग_लिखो)(काष्ठा uli526x_board_info *, u8, u8, u16);
		u16 (*पढ़ो)(काष्ठा uli526x_board_info *, u8, u8);
	पूर्ण phy;
	काष्ठा net_device *next_dev;	/* next device */
	काष्ठा pci_dev *pdev;		/* PCI device */
	spinlock_t lock;

	व्योम __iomem *ioaddr;		/* I/O base address */
	u32 cr0_data;
	u32 cr5_data;
	u32 cr6_data;
	u32 cr7_data;
	u32 cr15_data;

	/* poपूर्णांकer क्रम memory physical address */
	dma_addr_t buf_pool_dma_ptr;	/* Tx buffer pool memory */
	dma_addr_t buf_pool_dma_start;	/* Tx buffer pool align dword */
	dma_addr_t desc_pool_dma_ptr;	/* descriptor pool memory */
	dma_addr_t first_tx_desc_dma;
	dma_addr_t first_rx_desc_dma;

	/* descriptor poपूर्णांकer */
	अचिन्हित अक्षर *buf_pool_ptr;	/* Tx buffer pool memory */
	अचिन्हित अक्षर *buf_pool_start;	/* Tx buffer pool align dword */
	अचिन्हित अक्षर *desc_pool_ptr;	/* descriptor pool memory */
	काष्ठा tx_desc *first_tx_desc;
	काष्ठा tx_desc *tx_insert_ptr;
	काष्ठा tx_desc *tx_हटाओ_ptr;
	काष्ठा rx_desc *first_rx_desc;
	काष्ठा rx_desc *rx_insert_ptr;
	काष्ठा rx_desc *rx_पढ़ोy_ptr;	/* packet come poपूर्णांकer */
	अचिन्हित दीर्घ tx_packet_cnt;	/* transmitted packet count */
	अचिन्हित दीर्घ rx_avail_cnt;	/* available rx descriptor count */
	अचिन्हित दीर्घ पूर्णांकerval_rx_cnt;	/* rx packet count a callback समय */

	u16 dbug_cnt;
	u16 NIC_capability;		/* NIC media capability */
	u16 PHY_reg4;			/* Saved Phyxcer रेजिस्टर 4 value */

	u8 media_mode;			/* user specअगरy media mode */
	u8 op_mode;			/* real work media mode */
	u8 phy_addr;
	u8 link_failed;			/* Ever link failed */
	u8 रुको_reset;			/* Hardware failed, need to reset */
	काष्ठा समयr_list समयr;

	/* Driver defined statistic counter */
	अचिन्हित दीर्घ tx_fअगरo_underrun;
	अचिन्हित दीर्घ tx_loss_carrier;
	अचिन्हित दीर्घ tx_no_carrier;
	अचिन्हित दीर्घ tx_late_collision;
	अचिन्हित दीर्घ tx_excessive_collision;
	अचिन्हित दीर्घ tx_jabber_समयout;
	अचिन्हित दीर्घ reset_count;
	अचिन्हित दीर्घ reset_cr8;
	अचिन्हित दीर्घ reset_fatal;
	अचिन्हित दीर्घ reset_TXसमयout;

	/* NIC SROM data */
	अचिन्हित अक्षर srom[128];
	u8 init;
पूर्ण;

क्रमागत uli526x_offsets अणु
	DCR0 = 0x00, DCR1 = 0x08, DCR2 = 0x10, DCR3 = 0x18, DCR4 = 0x20,
	DCR5 = 0x28, DCR6 = 0x30, DCR7 = 0x38, DCR8 = 0x40, DCR9 = 0x48,
	DCR10 = 0x50, DCR11 = 0x58, DCR12 = 0x60, DCR13 = 0x68, DCR14 = 0x70,
	DCR15 = 0x78
पूर्ण;

क्रमागत uli526x_CR6_bits अणु
	CR6_RXSC = 0x2, CR6_PBF = 0x8, CR6_PM = 0x40, CR6_PAM = 0x80,
	CR6_FDM = 0x200, CR6_TXSC = 0x2000, CR6_STI = 0x100000,
	CR6_SFT = 0x200000, CR6_RXA = 0x40000000, CR6_NO_PURGE = 0x20000000
पूर्ण;

/* Global variable declaration ----------------------------- */
अटल पूर्णांक uli526x_debug;
अटल अचिन्हित अक्षर uli526x_media_mode = ULI526X_AUTO;
अटल u32 uli526x_cr6_user_set;

/* For module input parameter */
अटल पूर्णांक debug;
अटल u32 cr6set;
अटल पूर्णांक mode = 8;

/* function declaration ------------------------------------- */
अटल पूर्णांक uli526x_खोलो(काष्ठा net_device *);
अटल netdev_tx_t uli526x_start_xmit(काष्ठा sk_buff *,
					    काष्ठा net_device *);
अटल पूर्णांक uli526x_stop(काष्ठा net_device *);
अटल व्योम uli526x_set_filter_mode(काष्ठा net_device *);
अटल स्थिर काष्ठा ethtool_ops netdev_ethtool_ops;
अटल u16 पढ़ो_srom_word(काष्ठा uli526x_board_info *, पूर्णांक);
अटल irqवापस_t uli526x_पूर्णांकerrupt(पूर्णांक, व्योम *);
#अगर_घोषित CONFIG_NET_POLL_CONTROLLER
अटल व्योम uli526x_poll(काष्ठा net_device *dev);
#पूर्ण_अगर
अटल व्योम uli526x_descriptor_init(काष्ठा net_device *, व्योम __iomem *);
अटल व्योम allocate_rx_buffer(काष्ठा net_device *);
अटल व्योम update_cr6(u32, व्योम __iomem *);
अटल व्योम send_filter_frame(काष्ठा net_device *, पूर्णांक);
अटल u16 phy_पढ़ोby_cr9(काष्ठा uli526x_board_info *, u8, u8);
अटल u16 phy_पढ़ोby_cr10(काष्ठा uli526x_board_info *, u8, u8);
अटल व्योम phy_ग_लिखोby_cr9(काष्ठा uli526x_board_info *, u8, u8, u16);
अटल व्योम phy_ग_लिखोby_cr10(काष्ठा uli526x_board_info *, u8, u8, u16);
अटल व्योम phy_ग_लिखो_1bit(काष्ठा uli526x_board_info *db, u32);
अटल u16 phy_पढ़ो_1bit(काष्ठा uli526x_board_info *db);
अटल u8 uli526x_sense_speed(काष्ठा uli526x_board_info *);
अटल व्योम uli526x_process_mode(काष्ठा uli526x_board_info *);
अटल व्योम uli526x_समयr(काष्ठा समयr_list *t);
अटल व्योम uli526x_rx_packet(काष्ठा net_device *, काष्ठा uli526x_board_info *);
अटल व्योम uli526x_मुक्त_tx_pkt(काष्ठा net_device *, काष्ठा uli526x_board_info *);
अटल व्योम uli526x_reuse_skb(काष्ठा uli526x_board_info *, काष्ठा sk_buff *);
अटल व्योम uli526x_dynamic_reset(काष्ठा net_device *);
अटल व्योम uli526x_मुक्त_rxbuffer(काष्ठा uli526x_board_info *);
अटल व्योम uli526x_init(काष्ठा net_device *);
अटल व्योम uli526x_set_phyxcer(काष्ठा uli526x_board_info *);

अटल व्योम srom_clk_ग_लिखो(काष्ठा uli526x_board_info *db, u32 data)
अणु
	व्योम __iomem *ioaddr = db->ioaddr;

	uw32(DCR9, data | CR9_SROM_READ | CR9_SRCS);
	udelay(5);
	uw32(DCR9, data | CR9_SROM_READ | CR9_SRCS | CR9_SRCLK);
	udelay(5);
	uw32(DCR9, data | CR9_SROM_READ | CR9_SRCS);
	udelay(5);
पूर्ण

/* ULI526X network board routine ---------------------------- */

अटल स्थिर काष्ठा net_device_ops netdev_ops = अणु
	.nकरो_खोलो		= uli526x_खोलो,
	.nकरो_stop		= uli526x_stop,
	.nकरो_start_xmit		= uli526x_start_xmit,
	.nकरो_set_rx_mode	= uli526x_set_filter_mode,
	.nकरो_set_mac_address	= eth_mac_addr,
	.nकरो_validate_addr	= eth_validate_addr,
#अगर_घोषित CONFIG_NET_POLL_CONTROLLER
	.nकरो_poll_controller 	= uli526x_poll,
#पूर्ण_अगर
पूर्ण;

/*
 *	Search ULI526X board, allocate space and रेजिस्टर it
 */

अटल पूर्णांक uli526x_init_one(काष्ठा pci_dev *pdev,
			    स्थिर काष्ठा pci_device_id *ent)
अणु
	काष्ठा uli526x_board_info *db;	/* board inक्रमmation काष्ठाure */
	काष्ठा net_device *dev;
	व्योम __iomem *ioaddr;
	पूर्णांक i, err;

	ULI526X_DBUG(0, "uli526x_init_one()", 0);

	/* Init network device */
	dev = alloc_etherdev(माप(*db));
	अगर (dev == शून्य)
		वापस -ENOMEM;
	SET_NETDEV_DEV(dev, &pdev->dev);

	अगर (dma_set_mask(&pdev->dev, DMA_BIT_MASK(32))) अणु
		pr_warn("32-bit PCI DMA not available\n");
		err = -ENODEV;
		जाओ err_out_मुक्त;
	पूर्ण

	/* Enable Master/IO access, Disable memory access */
	err = pci_enable_device(pdev);
	अगर (err)
		जाओ err_out_मुक्त;

	अगर (!pci_resource_start(pdev, 0)) अणु
		pr_err("I/O base is zero\n");
		err = -ENODEV;
		जाओ err_out_disable;
	पूर्ण

	अगर (pci_resource_len(pdev, 0) < (ULI526X_IO_SIZE) ) अणु
		pr_err("Allocated I/O size too small\n");
		err = -ENODEV;
		जाओ err_out_disable;
	पूर्ण

	err = pci_request_regions(pdev, DRV_NAME);
	अगर (err < 0) अणु
		pr_err("Failed to request PCI regions\n");
		जाओ err_out_disable;
	पूर्ण

	/* Init प्रणाली & device */
	db = netdev_priv(dev);

	/* Allocate Tx/Rx descriptor memory */
	err = -ENOMEM;

	db->desc_pool_ptr = dma_alloc_coherent(&pdev->dev,
					       माप(काष्ठा tx_desc) * DESC_ALL_CNT + 0x20,
					       &db->desc_pool_dma_ptr, GFP_KERNEL);
	अगर (!db->desc_pool_ptr)
		जाओ err_out_release;

	db->buf_pool_ptr = dma_alloc_coherent(&pdev->dev,
					      TX_BUF_ALLOC * TX_DESC_CNT + 4,
					      &db->buf_pool_dma_ptr, GFP_KERNEL);
	अगर (!db->buf_pool_ptr)
		जाओ err_out_मुक्त_tx_desc;

	db->first_tx_desc = (काष्ठा tx_desc *) db->desc_pool_ptr;
	db->first_tx_desc_dma = db->desc_pool_dma_ptr;
	db->buf_pool_start = db->buf_pool_ptr;
	db->buf_pool_dma_start = db->buf_pool_dma_ptr;

	चयन (ent->driver_data) अणु
	हाल PCI_ULI5263_ID:
		db->phy.ग_लिखो	= phy_ग_लिखोby_cr10;
		db->phy.पढ़ो	= phy_पढ़ोby_cr10;
		अवरोध;
	शेष:
		db->phy.ग_लिखो	= phy_ग_लिखोby_cr9;
		db->phy.पढ़ो	= phy_पढ़ोby_cr9;
		अवरोध;
	पूर्ण

	/* IO region. */
	ioaddr = pci_iomap(pdev, 0, 0);
	अगर (!ioaddr)
		जाओ err_out_मुक्त_tx_buf;

	db->ioaddr = ioaddr;
	db->pdev = pdev;
	db->init = 1;

	pci_set_drvdata(pdev, dev);

	/* Register some necessary functions */
	dev->netdev_ops = &netdev_ops;
	dev->ethtool_ops = &netdev_ethtool_ops;

	spin_lock_init(&db->lock);


	/* पढ़ो 64 word srom data */
	क्रम (i = 0; i < 64; i++)
		((__le16 *) db->srom)[i] = cpu_to_le16(पढ़ो_srom_word(db, i));

	/* Set Node address */
	अगर(((u16 *) db->srom)[0] == 0xffff || ((u16 *) db->srom)[0] == 0)		/* SROM असलent, so पढ़ो MAC address from ID Table */
	अणु
		uw32(DCR0, 0x10000);	//Diagnosis mode
		uw32(DCR13, 0x1c0);	//Reset dianostic poपूर्णांकer port
		uw32(DCR14, 0);		//Clear reset port
		uw32(DCR14, 0x10);	//Reset ID Table poपूर्णांकer
		uw32(DCR14, 0);		//Clear reset port
		uw32(DCR13, 0);		//Clear CR13
		uw32(DCR13, 0x1b0);	//Select ID Table access port
		//Read MAC address from CR14
		क्रम (i = 0; i < 6; i++)
			dev->dev_addr[i] = ur32(DCR14);
		//Read end
		uw32(DCR13, 0);		//Clear CR13
		uw32(DCR0, 0);		//Clear CR0
		udelay(10);
	पूर्ण
	अन्यथा		/*Exist SROM*/
	अणु
		क्रम (i = 0; i < 6; i++)
			dev->dev_addr[i] = db->srom[20 + i];
	पूर्ण
	err = रेजिस्टर_netdev (dev);
	अगर (err)
		जाओ err_out_unmap;

	netdev_info(dev, "ULi M%04lx at pci%s, %pM, irq %d\n",
		    ent->driver_data >> 16, pci_name(pdev),
		    dev->dev_addr, pdev->irq);

	pci_set_master(pdev);

	वापस 0;

err_out_unmap:
	pci_iounmap(pdev, db->ioaddr);
err_out_मुक्त_tx_buf:
	dma_मुक्त_coherent(&pdev->dev, TX_BUF_ALLOC * TX_DESC_CNT + 4,
			  db->buf_pool_ptr, db->buf_pool_dma_ptr);
err_out_मुक्त_tx_desc:
	dma_मुक्त_coherent(&pdev->dev,
			  माप(काष्ठा tx_desc) * DESC_ALL_CNT + 0x20,
			  db->desc_pool_ptr, db->desc_pool_dma_ptr);
err_out_release:
	pci_release_regions(pdev);
err_out_disable:
	pci_disable_device(pdev);
err_out_मुक्त:
	मुक्त_netdev(dev);

	वापस err;
पूर्ण


अटल व्योम uli526x_हटाओ_one(काष्ठा pci_dev *pdev)
अणु
	काष्ठा net_device *dev = pci_get_drvdata(pdev);
	काष्ठा uli526x_board_info *db = netdev_priv(dev);

	unरेजिस्टर_netdev(dev);
	pci_iounmap(pdev, db->ioaddr);
	dma_मुक्त_coherent(&db->pdev->dev,
			  माप(काष्ठा tx_desc) * DESC_ALL_CNT + 0x20,
			  db->desc_pool_ptr, db->desc_pool_dma_ptr);
	dma_मुक्त_coherent(&db->pdev->dev, TX_BUF_ALLOC * TX_DESC_CNT + 4,
			  db->buf_pool_ptr, db->buf_pool_dma_ptr);
	pci_release_regions(pdev);
	pci_disable_device(pdev);
	मुक्त_netdev(dev);
पूर्ण


/*
 *	Open the पूर्णांकerface.
 *	The पूर्णांकerface is खोलोed whenever "ifconfig" activates it.
 */

अटल पूर्णांक uli526x_खोलो(काष्ठा net_device *dev)
अणु
	पूर्णांक ret;
	काष्ठा uli526x_board_info *db = netdev_priv(dev);

	ULI526X_DBUG(0, "uli526x_open", 0);

	/* प्रणाली variable init */
	db->cr6_data = CR6_DEFAULT | uli526x_cr6_user_set;
	db->tx_packet_cnt = 0;
	db->rx_avail_cnt = 0;
	db->link_failed = 1;
	netअगर_carrier_off(dev);
	db->रुको_reset = 0;

	db->NIC_capability = 0xf;	/* All capability*/
	db->PHY_reg4 = 0x1e0;

	/* CR6 operation mode decision */
	db->cr6_data |= ULI526X_TXTH_256;
	db->cr0_data = CR0_DEFAULT;

	/* Initialize ULI526X board */
	uli526x_init(dev);

	ret = request_irq(db->pdev->irq, uli526x_पूर्णांकerrupt, IRQF_SHARED,
			  dev->name, dev);
	अगर (ret)
		वापस ret;

	/* Active System Interface */
	netअगर_wake_queue(dev);

	/* set and active a समयr process */
	समयr_setup(&db->समयr, uli526x_समयr, 0);
	db->समयr.expires = ULI526X_TIMER_WUT + HZ * 2;
	add_समयr(&db->समयr);

	वापस 0;
पूर्ण


/*	Initialize ULI526X board
 *	Reset ULI526X board
 *	Initialize TX/Rx descriptor chain काष्ठाure
 *	Send the set-up frame
 *	Enable Tx/Rx machine
 */

अटल व्योम uli526x_init(काष्ठा net_device *dev)
अणु
	काष्ठा uli526x_board_info *db = netdev_priv(dev);
	काष्ठा uli_phy_ops *phy = &db->phy;
	व्योम __iomem *ioaddr = db->ioaddr;
	u8	phy_पंचांगp;
	u8	समयout;
	u16 phy_reg_reset;


	ULI526X_DBUG(0, "uli526x_init()", 0);

	/* Reset M526x MAC controller */
	uw32(DCR0, ULI526X_RESET);	/* RESET MAC */
	udelay(100);
	uw32(DCR0, db->cr0_data);
	udelay(5);

	/* Phy addr : In some boards,M5261/M5263 phy address != 1 */
	db->phy_addr = 1;
	क्रम (phy_पंचांगp = 0; phy_पंचांगp < 32; phy_पंचांगp++) अणु
		u16 phy_value;

		phy_value = phy->पढ़ो(db, phy_पंचांगp, 3);	//peer add
		अगर (phy_value != 0xffff && phy_value != 0) अणु
			db->phy_addr = phy_पंचांगp;
			अवरोध;
		पूर्ण
	पूर्ण

	अगर (phy_पंचांगp == 32)
		pr_warn("Can not find the phy address!!!\n");
	/* Parser SROM and media mode */
	db->media_mode = uli526x_media_mode;

	/* phyxcer capability setting */
	phy_reg_reset = phy->पढ़ो(db, db->phy_addr, 0);
	phy_reg_reset = (phy_reg_reset | 0x8000);
	phy->ग_लिखो(db, db->phy_addr, 0, phy_reg_reset);

	/* See IEEE 802.3-2002.pdf (Section 2, Chapter "22.2.4 Management
	 * functions") or phy data sheet क्रम details on phy reset
	 */
	udelay(500);
	समयout = 10;
	जबतक (समयout-- && phy->पढ़ो(db, db->phy_addr, 0) & 0x8000)
		udelay(100);

	/* Process Phyxcer Media Mode */
	uli526x_set_phyxcer(db);

	/* Media Mode Process */
	अगर ( !(db->media_mode & ULI526X_AUTO) )
		db->op_mode = db->media_mode;		/* Force Mode */

	/* Initialize Transmit/Receive descriptor and CR3/4 */
	uli526x_descriptor_init(dev, ioaddr);

	/* Init CR6 to program M526X operation */
	update_cr6(db->cr6_data, ioaddr);

	/* Send setup frame */
	send_filter_frame(dev, netdev_mc_count(dev));	/* M5261/M5263 */

	/* Init CR7, पूर्णांकerrupt active bit */
	db->cr7_data = CR7_DEFAULT;
	uw32(DCR7, db->cr7_data);

	/* Init CR15, Tx jabber and Rx watchकरोg समयr */
	uw32(DCR15, db->cr15_data);

	/* Enable ULI526X Tx/Rx function */
	db->cr6_data |= CR6_RXSC | CR6_TXSC;
	update_cr6(db->cr6_data, ioaddr);
पूर्ण


/*
 *	Hardware start transmission.
 *	Send a packet to media from the upper layer.
 */

अटल netdev_tx_t uli526x_start_xmit(काष्ठा sk_buff *skb,
					    काष्ठा net_device *dev)
अणु
	काष्ठा uli526x_board_info *db = netdev_priv(dev);
	व्योम __iomem *ioaddr = db->ioaddr;
	काष्ठा tx_desc *txptr;
	अचिन्हित दीर्घ flags;

	ULI526X_DBUG(0, "uli526x_start_xmit", 0);

	/* Resource flag check */
	netअगर_stop_queue(dev);

	/* Too large packet check */
	अगर (skb->len > MAX_PACKET_SIZE) अणु
		netdev_err(dev, "big packet = %d\n", (u16)skb->len);
		dev_kमुक्त_skb_any(skb);
		वापस NETDEV_TX_OK;
	पूर्ण

	spin_lock_irqsave(&db->lock, flags);

	/* No Tx resource check, it never happen nromally */
	अगर (db->tx_packet_cnt >= TX_FREE_DESC_CNT) अणु
		spin_unlock_irqrestore(&db->lock, flags);
		netdev_err(dev, "No Tx resource %ld\n", db->tx_packet_cnt);
		वापस NETDEV_TX_BUSY;
	पूर्ण

	/* Disable NIC पूर्णांकerrupt */
	uw32(DCR7, 0);

	/* transmit this packet */
	txptr = db->tx_insert_ptr;
	skb_copy_from_linear_data(skb, txptr->tx_buf_ptr, skb->len);
	txptr->tdes1 = cpu_to_le32(0xe1000000 | skb->len);

	/* Poपूर्णांक to next transmit मुक्त descriptor */
	db->tx_insert_ptr = txptr->next_tx_desc;

	/* Transmit Packet Process */
	अगर (db->tx_packet_cnt < TX_DESC_CNT) अणु
		txptr->tdes0 = cpu_to_le32(0x80000000);	/* Set owner bit */
		db->tx_packet_cnt++;			/* Ready to send */
		uw32(DCR1, 0x1);			/* Issue Tx polling */
		netअगर_trans_update(dev);		/* saved समय stamp */
	पूर्ण

	/* Tx resource check */
	अगर ( db->tx_packet_cnt < TX_FREE_DESC_CNT )
		netअगर_wake_queue(dev);

	/* Restore CR7 to enable पूर्णांकerrupt */
	spin_unlock_irqrestore(&db->lock, flags);
	uw32(DCR7, db->cr7_data);

	/* मुक्त this SKB */
	dev_consume_skb_any(skb);

	वापस NETDEV_TX_OK;
पूर्ण


/*
 *	Stop the पूर्णांकerface.
 *	The पूर्णांकerface is stopped when it is brought.
 */

अटल पूर्णांक uli526x_stop(काष्ठा net_device *dev)
अणु
	काष्ठा uli526x_board_info *db = netdev_priv(dev);
	व्योम __iomem *ioaddr = db->ioaddr;

	/* disable प्रणाली */
	netअगर_stop_queue(dev);

	/* deleted समयr */
	del_समयr_sync(&db->समयr);

	/* Reset & stop ULI526X board */
	uw32(DCR0, ULI526X_RESET);
	udelay(5);
	db->phy.ग_लिखो(db, db->phy_addr, 0, 0x8000);

	/* मुक्त पूर्णांकerrupt */
	मुक्त_irq(db->pdev->irq, dev);

	/* मुक्त allocated rx buffer */
	uli526x_मुक्त_rxbuffer(db);

	वापस 0;
पूर्ण


/*
 *	M5261/M5263 insterrupt handler
 *	receive the packet to upper layer, मुक्त the transmitted packet
 */

अटल irqवापस_t uli526x_पूर्णांकerrupt(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा net_device *dev = dev_id;
	काष्ठा uli526x_board_info *db = netdev_priv(dev);
	व्योम __iomem *ioaddr = db->ioaddr;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&db->lock, flags);
	uw32(DCR7, 0);

	/* Got ULI526X status */
	db->cr5_data = ur32(DCR5);
	uw32(DCR5, db->cr5_data);
	अगर ( !(db->cr5_data & 0x180c1) ) अणु
		/* Restore CR7 to enable पूर्णांकerrupt mask */
		uw32(DCR7, db->cr7_data);
		spin_unlock_irqrestore(&db->lock, flags);
		वापस IRQ_HANDLED;
	पूर्ण

	/* Check प्रणाली status */
	अगर (db->cr5_data & 0x2000) अणु
		/* प्रणाली bus error happen */
		ULI526X_DBUG(1, "System bus error happen. CR5=", db->cr5_data);
		db->reset_fatal++;
		db->रुको_reset = 1;	/* Need to RESET */
		spin_unlock_irqrestore(&db->lock, flags);
		वापस IRQ_HANDLED;
	पूर्ण

	 /* Received the coming packet */
	अगर ( (db->cr5_data & 0x40) && db->rx_avail_cnt )
		uli526x_rx_packet(dev, db);

	/* पुनः_स्मृतिate rx descriptor buffer */
	अगर (db->rx_avail_cnt<RX_DESC_CNT)
		allocate_rx_buffer(dev);

	/* Free the transmitted descriptor */
	अगर ( db->cr5_data & 0x01)
		uli526x_मुक्त_tx_pkt(dev, db);

	/* Restore CR7 to enable पूर्णांकerrupt mask */
	uw32(DCR7, db->cr7_data);

	spin_unlock_irqrestore(&db->lock, flags);
	वापस IRQ_HANDLED;
पूर्ण

#अगर_घोषित CONFIG_NET_POLL_CONTROLLER
अटल व्योम uli526x_poll(काष्ठा net_device *dev)
अणु
	काष्ठा uli526x_board_info *db = netdev_priv(dev);

	/* ISR grअसल the irqsave lock, so this should be safe */
	uli526x_पूर्णांकerrupt(db->pdev->irq, dev);
पूर्ण
#पूर्ण_अगर

/*
 *	Free TX resource after TX complete
 */

अटल व्योम uli526x_मुक्त_tx_pkt(काष्ठा net_device *dev,
				काष्ठा uli526x_board_info * db)
अणु
	काष्ठा tx_desc *txptr;
	u32 tdes0;

	txptr = db->tx_हटाओ_ptr;
	जबतक(db->tx_packet_cnt) अणु
		tdes0 = le32_to_cpu(txptr->tdes0);
		अगर (tdes0 & 0x80000000)
			अवरोध;

		/* A packet sent completed */
		db->tx_packet_cnt--;
		dev->stats.tx_packets++;

		/* Transmit statistic counter */
		अगर ( tdes0 != 0x7fffffff ) अणु
			dev->stats.collisions += (tdes0 >> 3) & 0xf;
			dev->stats.tx_bytes += le32_to_cpu(txptr->tdes1) & 0x7ff;
			अगर (tdes0 & TDES0_ERR_MASK) अणु
				dev->stats.tx_errors++;
				अगर (tdes0 & 0x0002) अणु	/* UnderRun */
					db->tx_fअगरo_underrun++;
					अगर ( !(db->cr6_data & CR6_SFT) ) अणु
						db->cr6_data = db->cr6_data | CR6_SFT;
						update_cr6(db->cr6_data, db->ioaddr);
					पूर्ण
				पूर्ण
				अगर (tdes0 & 0x0100)
					db->tx_excessive_collision++;
				अगर (tdes0 & 0x0200)
					db->tx_late_collision++;
				अगर (tdes0 & 0x0400)
					db->tx_no_carrier++;
				अगर (tdes0 & 0x0800)
					db->tx_loss_carrier++;
				अगर (tdes0 & 0x4000)
					db->tx_jabber_समयout++;
			पूर्ण
		पूर्ण

    		txptr = txptr->next_tx_desc;
	पूर्ण/* End of जबतक */

	/* Update TX हटाओ poपूर्णांकer to next */
	db->tx_हटाओ_ptr = txptr;

	/* Resource available check */
	अगर ( db->tx_packet_cnt < TX_WAKE_DESC_CNT )
		netअगर_wake_queue(dev);	/* Active upper layer, send again */
पूर्ण


/*
 *	Receive the come packet and pass to upper layer
 */

अटल व्योम uli526x_rx_packet(काष्ठा net_device *dev, काष्ठा uli526x_board_info * db)
अणु
	काष्ठा rx_desc *rxptr;
	काष्ठा sk_buff *skb;
	पूर्णांक rxlen;
	u32 rdes0;

	rxptr = db->rx_पढ़ोy_ptr;

	जबतक(db->rx_avail_cnt) अणु
		rdes0 = le32_to_cpu(rxptr->rdes0);
		अगर (rdes0 & 0x80000000)	/* packet owner check */
		अणु
			अवरोध;
		पूर्ण

		db->rx_avail_cnt--;
		db->पूर्णांकerval_rx_cnt++;

		dma_unmap_single(&db->pdev->dev, le32_to_cpu(rxptr->rdes2),
				 RX_ALLOC_SIZE, DMA_FROM_DEVICE);
		अगर ( (rdes0 & 0x300) != 0x300) अणु
			/* A packet without First/Last flag */
			/* reuse this SKB */
			ULI526X_DBUG(0, "Reuse SK buffer, rdes0", rdes0);
			uli526x_reuse_skb(db, rxptr->rx_skb_ptr);
		पूर्ण अन्यथा अणु
			/* A packet with First/Last flag */
			rxlen = ( (rdes0 >> 16) & 0x3fff) - 4;

			/* error summary bit check */
			अगर (rdes0 & 0x8000) अणु
				/* This is a error packet */
				dev->stats.rx_errors++;
				अगर (rdes0 & 1)
					dev->stats.rx_fअगरo_errors++;
				अगर (rdes0 & 2)
					dev->stats.rx_crc_errors++;
				अगर (rdes0 & 0x80)
					dev->stats.rx_length_errors++;
			पूर्ण

			अगर ( !(rdes0 & 0x8000) ||
				((db->cr6_data & CR6_PM) && (rxlen>6)) ) अणु
				काष्ठा sk_buff *new_skb = शून्य;

				skb = rxptr->rx_skb_ptr;

				/* Good packet, send to upper layer */
				/* Shorst packet used new SKB */
				अगर ((rxlen < RX_COPY_SIZE) &&
				    (((new_skb = netdev_alloc_skb(dev, rxlen + 2)) != शून्य))) अणु
					skb = new_skb;
					/* size less than COPY_SIZE, allocate a rxlen SKB */
					skb_reserve(skb, 2); /* 16byte align */
					skb_put_data(skb,
						     skb_tail_poपूर्णांकer(rxptr->rx_skb_ptr),
						     rxlen);
					uli526x_reuse_skb(db, rxptr->rx_skb_ptr);
				पूर्ण अन्यथा
					skb_put(skb, rxlen);

				skb->protocol = eth_type_trans(skb, dev);
				netअगर_rx(skb);
				dev->stats.rx_packets++;
				dev->stats.rx_bytes += rxlen;

			पूर्ण अन्यथा अणु
				/* Reuse SKB buffer when the packet is error */
				ULI526X_DBUG(0, "Reuse SK buffer, rdes0", rdes0);
				uli526x_reuse_skb(db, rxptr->rx_skb_ptr);
			पूर्ण
		पूर्ण

		rxptr = rxptr->next_rx_desc;
	पूर्ण

	db->rx_पढ़ोy_ptr = rxptr;
पूर्ण


/*
 * Set ULI526X multicast address
 */

अटल व्योम uli526x_set_filter_mode(काष्ठा net_device * dev)
अणु
	काष्ठा uli526x_board_info *db = netdev_priv(dev);
	अचिन्हित दीर्घ flags;

	ULI526X_DBUG(0, "uli526x_set_filter_mode()", 0);
	spin_lock_irqsave(&db->lock, flags);

	अगर (dev->flags & IFF_PROMISC) अणु
		ULI526X_DBUG(0, "Enable PROM Mode", 0);
		db->cr6_data |= CR6_PM | CR6_PBF;
		update_cr6(db->cr6_data, db->ioaddr);
		spin_unlock_irqrestore(&db->lock, flags);
		वापस;
	पूर्ण

	अगर (dev->flags & IFF_ALLMULTI ||
	    netdev_mc_count(dev) > ULI5261_MAX_MULTICAST) अणु
		ULI526X_DBUG(0, "Pass all multicast address",
			     netdev_mc_count(dev));
		db->cr6_data &= ~(CR6_PM | CR6_PBF);
		db->cr6_data |= CR6_PAM;
		spin_unlock_irqrestore(&db->lock, flags);
		वापस;
	पूर्ण

	ULI526X_DBUG(0, "Set multicast address", netdev_mc_count(dev));
	send_filter_frame(dev, netdev_mc_count(dev)); 	/* M5261/M5263 */
	spin_unlock_irqrestore(&db->lock, flags);
पूर्ण

अटल व्योम
ULi_ethtool_get_link_ksettings(काष्ठा uli526x_board_info *db,
			       काष्ठा ethtool_link_ksettings *cmd)
अणु
	u32 supported, advertising;

	supported = (SUPPORTED_10baseT_Half |
	                   SUPPORTED_10baseT_Full |
	                   SUPPORTED_100baseT_Half |
	                   SUPPORTED_100baseT_Full |
	                   SUPPORTED_Autoneg |
	                   SUPPORTED_MII);

	advertising = (ADVERTISED_10baseT_Half |
	                   ADVERTISED_10baseT_Full |
	                   ADVERTISED_100baseT_Half |
	                   ADVERTISED_100baseT_Full |
	                   ADVERTISED_Autoneg |
	                   ADVERTISED_MII);

	ethtool_convert_legacy_u32_to_link_mode(cmd->link_modes.supported,
						supported);
	ethtool_convert_legacy_u32_to_link_mode(cmd->link_modes.advertising,
						advertising);

	cmd->base.port = PORT_MII;
	cmd->base.phy_address = db->phy_addr;

	cmd->base.speed = SPEED_10;
	cmd->base.duplex = DUPLEX_HALF;

	अगर(db->op_mode==ULI526X_100MHF || db->op_mode==ULI526X_100MFD)
	अणु
		cmd->base.speed = SPEED_100;
	पूर्ण
	अगर(db->op_mode==ULI526X_10MFD || db->op_mode==ULI526X_100MFD)
	अणु
		cmd->base.duplex = DUPLEX_FULL;
	पूर्ण
	अगर(db->link_failed)
	अणु
		cmd->base.speed = SPEED_UNKNOWN;
		cmd->base.duplex = DUPLEX_UNKNOWN;
	पूर्ण

	अगर (db->media_mode & ULI526X_AUTO)
	अणु
		cmd->base.स्वतःneg = AUTONEG_ENABLE;
	पूर्ण
पूर्ण

अटल व्योम netdev_get_drvinfo(काष्ठा net_device *dev,
			       काष्ठा ethtool_drvinfo *info)
अणु
	काष्ठा uli526x_board_info *np = netdev_priv(dev);

	strlcpy(info->driver, DRV_NAME, माप(info->driver));
	strlcpy(info->bus_info, pci_name(np->pdev), माप(info->bus_info));
पूर्ण

अटल पूर्णांक netdev_get_link_ksettings(काष्ठा net_device *dev,
				     काष्ठा ethtool_link_ksettings *cmd)
अणु
	काष्ठा uli526x_board_info *np = netdev_priv(dev);

	ULi_ethtool_get_link_ksettings(np, cmd);

	वापस 0;
पूर्ण

अटल u32 netdev_get_link(काष्ठा net_device *dev) अणु
	काष्ठा uli526x_board_info *np = netdev_priv(dev);

	अगर(np->link_failed)
		वापस 0;
	अन्यथा
		वापस 1;
पूर्ण

अटल व्योम uli526x_get_wol(काष्ठा net_device *dev, काष्ठा ethtool_wolinfo *wol)
अणु
	wol->supported = WAKE_PHY | WAKE_MAGIC;
	wol->wolopts = 0;
पूर्ण

अटल स्थिर काष्ठा ethtool_ops netdev_ethtool_ops = अणु
	.get_drvinfo		= netdev_get_drvinfo,
	.get_link		= netdev_get_link,
	.get_wol		= uli526x_get_wol,
	.get_link_ksettings	= netdev_get_link_ksettings,
पूर्ण;

/*
 *	A periodic समयr routine
 *	Dynamic media sense, allocate Rx buffer...
 */

अटल व्योम uli526x_समयr(काष्ठा समयr_list *t)
अणु
	काष्ठा uli526x_board_info *db = from_समयr(db, t, समयr);
	काष्ठा net_device *dev = pci_get_drvdata(db->pdev);
	काष्ठा uli_phy_ops *phy = &db->phy;
	व्योम __iomem *ioaddr = db->ioaddr;
 	अचिन्हित दीर्घ flags;
	u8 पंचांगp_cr12 = 0;
	u32 पंचांगp_cr8;

	//ULI526X_DBUG(0, "uli526x_timer()", 0);
	spin_lock_irqsave(&db->lock, flags);


	/* Dynamic reset ULI526X : प्रणाली error or transmit समय-out */
	पंचांगp_cr8 = ur32(DCR8);
	अगर ( (db->पूर्णांकerval_rx_cnt==0) && (पंचांगp_cr8) ) अणु
		db->reset_cr8++;
		db->रुको_reset = 1;
	पूर्ण
	db->पूर्णांकerval_rx_cnt = 0;

	/* TX polling kick monitor */
	अगर ( db->tx_packet_cnt &&
	     समय_after(jअगरfies, dev_trans_start(dev) + ULI526X_TX_KICK) ) अणु
		uw32(DCR1, 0x1);   // Tx polling again

		// TX Timeout
		अगर ( समय_after(jअगरfies, dev_trans_start(dev) + ULI526X_TX_TIMEOUT) ) अणु
			db->reset_TXसमयout++;
			db->रुको_reset = 1;
			netdev_err(dev, " Tx timeout - resetting\n");
		पूर्ण
	पूर्ण

	अगर (db->रुको_reset) अणु
		ULI526X_DBUG(0, "Dynamic Reset device", db->tx_packet_cnt);
		db->reset_count++;
		uli526x_dynamic_reset(dev);
		db->समयr.expires = ULI526X_TIMER_WUT;
		add_समयr(&db->समयr);
		spin_unlock_irqrestore(&db->lock, flags);
		वापस;
	पूर्ण

	/* Link status check, Dynamic media type change */
	अगर ((phy->पढ़ो(db, db->phy_addr, 5) & 0x01e0)!=0)
		पंचांगp_cr12 = 3;

	अगर ( !(पंचांगp_cr12 & 0x3) && !db->link_failed ) अणु
		/* Link Failed */
		ULI526X_DBUG(0, "Link Failed", पंचांगp_cr12);
		netअगर_carrier_off(dev);
		netdev_info(dev, "NIC Link is Down\n");
		db->link_failed = 1;

		/* For Force 10/100M Half/Full mode: Enable Auto-Nego mode */
		/* AUTO करोn't need */
		अगर ( !(db->media_mode & 0x8) )
			phy->ग_लिखो(db, db->phy_addr, 0, 0x1000);

		/* AUTO mode, अगर INT phyxcer link failed, select EXT device */
		अगर (db->media_mode & ULI526X_AUTO) अणु
			db->cr6_data&=~0x00000200;	/* bit9=0, HD mode */
			update_cr6(db->cr6_data, db->ioaddr);
		पूर्ण
	पूर्ण अन्यथा
		अगर ((पंचांगp_cr12 & 0x3) && db->link_failed) अणु
			ULI526X_DBUG(0, "Link link OK", पंचांगp_cr12);
			db->link_failed = 0;

			/* Auto Sense Speed */
			अगर ( (db->media_mode & ULI526X_AUTO) &&
				uli526x_sense_speed(db) )
				db->link_failed = 1;
			uli526x_process_mode(db);

			अगर(db->link_failed==0)
			अणु
				netdev_info(dev, "NIC Link is Up %d Mbps %s duplex\n",
					    (db->op_mode == ULI526X_100MHF ||
					     db->op_mode == ULI526X_100MFD)
					    ? 100 : 10,
					    (db->op_mode == ULI526X_10MFD ||
					     db->op_mode == ULI526X_100MFD)
					    ? "Full" : "Half");
				netअगर_carrier_on(dev);
			पूर्ण
			/* SHOW_MEDIA_TYPE(db->op_mode); */
		पूर्ण
		अन्यथा अगर(!(पंचांगp_cr12 & 0x3) && db->link_failed)
		अणु
			अगर(db->init==1)
			अणु
				netdev_info(dev, "NIC Link is Down\n");
				netअगर_carrier_off(dev);
			पूर्ण
		पूर्ण
	db->init = 0;

	/* Timer active again */
	db->समयr.expires = ULI526X_TIMER_WUT;
	add_समयr(&db->समयr);
	spin_unlock_irqrestore(&db->lock, flags);
पूर्ण


/*
 *	Stop ULI526X board
 *	Free Tx/Rx allocated memory
 *	Init प्रणाली variable
 */

अटल व्योम uli526x_reset_prepare(काष्ठा net_device *dev)
अणु
	काष्ठा uli526x_board_info *db = netdev_priv(dev);
	व्योम __iomem *ioaddr = db->ioaddr;

	/* Sopt MAC controller */
	db->cr6_data &= ~(CR6_RXSC | CR6_TXSC);	/* Disable Tx/Rx */
	update_cr6(db->cr6_data, ioaddr);
	uw32(DCR7, 0);				/* Disable Interrupt */
	uw32(DCR5, ur32(DCR5));

	/* Disable upper layer पूर्णांकerface */
	netअगर_stop_queue(dev);

	/* Free Rx Allocate buffer */
	uli526x_मुक्त_rxbuffer(db);

	/* प्रणाली variable init */
	db->tx_packet_cnt = 0;
	db->rx_avail_cnt = 0;
	db->link_failed = 1;
	db->init=1;
	db->रुको_reset = 0;
पूर्ण


/*
 *	Dynamic reset the ULI526X board
 *	Stop ULI526X board
 *	Free Tx/Rx allocated memory
 *	Reset ULI526X board
 *	Re-initialize ULI526X board
 */

अटल व्योम uli526x_dynamic_reset(काष्ठा net_device *dev)
अणु
	ULI526X_DBUG(0, "uli526x_dynamic_reset()", 0);

	uli526x_reset_prepare(dev);

	/* Re-initialize ULI526X board */
	uli526x_init(dev);

	/* Restart upper layer पूर्णांकerface */
	netअगर_wake_queue(dev);
पूर्ण

/*
 *	Suspend the पूर्णांकerface.
 */

अटल पूर्णांक __maybe_unused uli526x_suspend(काष्ठा device *dev_d)
अणु
	काष्ठा net_device *dev = dev_get_drvdata(dev_d);

	ULI526X_DBUG(0, "uli526x_suspend", 0);

	अगर (!netअगर_running(dev))
		वापस 0;

	netअगर_device_detach(dev);
	uli526x_reset_prepare(dev);

	device_set_wakeup_enable(dev_d, 0);

	वापस 0;
पूर्ण

/*
 *	Resume the पूर्णांकerface.
 */

अटल पूर्णांक __maybe_unused uli526x_resume(काष्ठा device *dev_d)
अणु
	काष्ठा net_device *dev = dev_get_drvdata(dev_d);

	ULI526X_DBUG(0, "uli526x_resume", 0);


	अगर (!netअगर_running(dev))
		वापस 0;

	netअगर_device_attach(dev);
	/* Re-initialize ULI526X board */
	uli526x_init(dev);
	/* Restart upper layer पूर्णांकerface */
	netअगर_wake_queue(dev);

	वापस 0;
पूर्ण

/*
 *	मुक्त all allocated rx buffer
 */

अटल व्योम uli526x_मुक्त_rxbuffer(काष्ठा uli526x_board_info * db)
अणु
	ULI526X_DBUG(0, "uli526x_free_rxbuffer()", 0);

	/* मुक्त allocated rx buffer */
	जबतक (db->rx_avail_cnt) अणु
		dev_kमुक्त_skb(db->rx_पढ़ोy_ptr->rx_skb_ptr);
		db->rx_पढ़ोy_ptr = db->rx_पढ़ोy_ptr->next_rx_desc;
		db->rx_avail_cnt--;
	पूर्ण
पूर्ण


/*
 *	Reuse the SK buffer
 */

अटल व्योम uli526x_reuse_skb(काष्ठा uli526x_board_info *db, काष्ठा sk_buff * skb)
अणु
	काष्ठा rx_desc *rxptr = db->rx_insert_ptr;

	अगर (!(rxptr->rdes0 & cpu_to_le32(0x80000000))) अणु
		rxptr->rx_skb_ptr = skb;
		rxptr->rdes2 = cpu_to_le32(dma_map_single(&db->pdev->dev, skb_tail_poपूर्णांकer(skb),
							  RX_ALLOC_SIZE, DMA_FROM_DEVICE));
		wmb();
		rxptr->rdes0 = cpu_to_le32(0x80000000);
		db->rx_avail_cnt++;
		db->rx_insert_ptr = rxptr->next_rx_desc;
	पूर्ण अन्यथा
		ULI526X_DBUG(0, "SK Buffer reuse method error", db->rx_avail_cnt);
पूर्ण


/*
 *	Initialize transmit/Receive descriptor
 *	Using Chain काष्ठाure, and allocate Tx/Rx buffer
 */

अटल व्योम uli526x_descriptor_init(काष्ठा net_device *dev, व्योम __iomem *ioaddr)
अणु
	काष्ठा uli526x_board_info *db = netdev_priv(dev);
	काष्ठा tx_desc *पंचांगp_tx;
	काष्ठा rx_desc *पंचांगp_rx;
	अचिन्हित अक्षर *पंचांगp_buf;
	dma_addr_t पंचांगp_tx_dma, पंचांगp_rx_dma;
	dma_addr_t पंचांगp_buf_dma;
	पूर्णांक i;

	ULI526X_DBUG(0, "uli526x_descriptor_init()", 0);

	/* tx descriptor start poपूर्णांकer */
	db->tx_insert_ptr = db->first_tx_desc;
	db->tx_हटाओ_ptr = db->first_tx_desc;
	uw32(DCR4, db->first_tx_desc_dma);	/* TX DESC address */

	/* rx descriptor start poपूर्णांकer */
	db->first_rx_desc = (व्योम *)db->first_tx_desc + माप(काष्ठा tx_desc) * TX_DESC_CNT;
	db->first_rx_desc_dma =  db->first_tx_desc_dma + माप(काष्ठा tx_desc) * TX_DESC_CNT;
	db->rx_insert_ptr = db->first_rx_desc;
	db->rx_पढ़ोy_ptr = db->first_rx_desc;
	uw32(DCR3, db->first_rx_desc_dma);	/* RX DESC address */

	/* Init Transmit chain */
	पंचांगp_buf = db->buf_pool_start;
	पंचांगp_buf_dma = db->buf_pool_dma_start;
	पंचांगp_tx_dma = db->first_tx_desc_dma;
	क्रम (पंचांगp_tx = db->first_tx_desc, i = 0; i < TX_DESC_CNT; i++, पंचांगp_tx++) अणु
		पंचांगp_tx->tx_buf_ptr = पंचांगp_buf;
		पंचांगp_tx->tdes0 = cpu_to_le32(0);
		पंचांगp_tx->tdes1 = cpu_to_le32(0x81000000);	/* IC, chain */
		पंचांगp_tx->tdes2 = cpu_to_le32(पंचांगp_buf_dma);
		पंचांगp_tx_dma += माप(काष्ठा tx_desc);
		पंचांगp_tx->tdes3 = cpu_to_le32(पंचांगp_tx_dma);
		पंचांगp_tx->next_tx_desc = पंचांगp_tx + 1;
		पंचांगp_buf = पंचांगp_buf + TX_BUF_ALLOC;
		पंचांगp_buf_dma = पंचांगp_buf_dma + TX_BUF_ALLOC;
	पूर्ण
	(--पंचांगp_tx)->tdes3 = cpu_to_le32(db->first_tx_desc_dma);
	पंचांगp_tx->next_tx_desc = db->first_tx_desc;

	 /* Init Receive descriptor chain */
	पंचांगp_rx_dma=db->first_rx_desc_dma;
	क्रम (पंचांगp_rx = db->first_rx_desc, i = 0; i < RX_DESC_CNT; i++, पंचांगp_rx++) अणु
		पंचांगp_rx->rdes0 = cpu_to_le32(0);
		पंचांगp_rx->rdes1 = cpu_to_le32(0x01000600);
		पंचांगp_rx_dma += माप(काष्ठा rx_desc);
		पंचांगp_rx->rdes3 = cpu_to_le32(पंचांगp_rx_dma);
		पंचांगp_rx->next_rx_desc = पंचांगp_rx + 1;
	पूर्ण
	(--पंचांगp_rx)->rdes3 = cpu_to_le32(db->first_rx_desc_dma);
	पंचांगp_rx->next_rx_desc = db->first_rx_desc;

	/* pre-allocate Rx buffer */
	allocate_rx_buffer(dev);
पूर्ण


/*
 *	Update CR6 value
 *	Firstly stop ULI526X, then written value and start
 */
अटल व्योम update_cr6(u32 cr6_data, व्योम __iomem *ioaddr)
अणु
	uw32(DCR6, cr6_data);
	udelay(5);
पूर्ण


/*
 *	Send a setup frame क्रम M5261/M5263
 *	This setup frame initialize ULI526X address filter mode
 */

#अगर_घोषित __BIG_ENDIAN
#घोषणा FLT_SHIFT 16
#अन्यथा
#घोषणा FLT_SHIFT 0
#पूर्ण_अगर

अटल व्योम send_filter_frame(काष्ठा net_device *dev, पूर्णांक mc_cnt)
अणु
	काष्ठा uli526x_board_info *db = netdev_priv(dev);
	व्योम __iomem *ioaddr = db->ioaddr;
	काष्ठा netdev_hw_addr *ha;
	काष्ठा tx_desc *txptr;
	u16 * addrptr;
	u32 * suptr;
	पूर्णांक i;

	ULI526X_DBUG(0, "send_filter_frame()", 0);

	txptr = db->tx_insert_ptr;
	suptr = (u32 *) txptr->tx_buf_ptr;

	/* Node address */
	addrptr = (u16 *) dev->dev_addr;
	*suptr++ = addrptr[0] << FLT_SHIFT;
	*suptr++ = addrptr[1] << FLT_SHIFT;
	*suptr++ = addrptr[2] << FLT_SHIFT;

	/* broadcast address */
	*suptr++ = 0xffff << FLT_SHIFT;
	*suptr++ = 0xffff << FLT_SHIFT;
	*suptr++ = 0xffff << FLT_SHIFT;

	/* fit the multicast address */
	netdev_क्रम_each_mc_addr(ha, dev) अणु
		addrptr = (u16 *) ha->addr;
		*suptr++ = addrptr[0] << FLT_SHIFT;
		*suptr++ = addrptr[1] << FLT_SHIFT;
		*suptr++ = addrptr[2] << FLT_SHIFT;
	पूर्ण

	क्रम (i = netdev_mc_count(dev); i < 14; i++) अणु
		*suptr++ = 0xffff << FLT_SHIFT;
		*suptr++ = 0xffff << FLT_SHIFT;
		*suptr++ = 0xffff << FLT_SHIFT;
	पूर्ण

	/* prepare the setup frame */
	db->tx_insert_ptr = txptr->next_tx_desc;
	txptr->tdes1 = cpu_to_le32(0x890000c0);

	/* Resource Check and Send the setup packet */
	अगर (db->tx_packet_cnt < TX_DESC_CNT) अणु
		/* Resource Empty */
		db->tx_packet_cnt++;
		txptr->tdes0 = cpu_to_le32(0x80000000);
		update_cr6(db->cr6_data | 0x2000, ioaddr);
		uw32(DCR1, 0x1);	/* Issue Tx polling */
		update_cr6(db->cr6_data, ioaddr);
		netअगर_trans_update(dev);
	पूर्ण अन्यथा
		netdev_err(dev, "No Tx resource - Send_filter_frame!\n");
पूर्ण


/*
 *	Allocate rx buffer,
 *	As possible as allocate maxiumn Rx buffer
 */

अटल व्योम allocate_rx_buffer(काष्ठा net_device *dev)
अणु
	काष्ठा uli526x_board_info *db = netdev_priv(dev);
	काष्ठा rx_desc *rxptr;
	काष्ठा sk_buff *skb;

	rxptr = db->rx_insert_ptr;

	जबतक(db->rx_avail_cnt < RX_DESC_CNT) अणु
		skb = netdev_alloc_skb(dev, RX_ALLOC_SIZE);
		अगर (skb == शून्य)
			अवरोध;
		rxptr->rx_skb_ptr = skb; /* FIXME (?) */
		rxptr->rdes2 = cpu_to_le32(dma_map_single(&db->pdev->dev, skb_tail_poपूर्णांकer(skb),
							  RX_ALLOC_SIZE, DMA_FROM_DEVICE));
		wmb();
		rxptr->rdes0 = cpu_to_le32(0x80000000);
		rxptr = rxptr->next_rx_desc;
		db->rx_avail_cnt++;
	पूर्ण

	db->rx_insert_ptr = rxptr;
पूर्ण


/*
 *	Read one word data from the serial ROM
 */

अटल u16 पढ़ो_srom_word(काष्ठा uli526x_board_info *db, पूर्णांक offset)
अणु
	व्योम __iomem *ioaddr = db->ioaddr;
	u16 srom_data = 0;
	पूर्णांक i;

	uw32(DCR9, CR9_SROM_READ);
	uw32(DCR9, CR9_SROM_READ | CR9_SRCS);

	/* Send the Read Command 110b */
	srom_clk_ग_लिखो(db, SROM_DATA_1);
	srom_clk_ग_लिखो(db, SROM_DATA_1);
	srom_clk_ग_लिखो(db, SROM_DATA_0);

	/* Send the offset */
	क्रम (i = 5; i >= 0; i--) अणु
		srom_data = (offset & (1 << i)) ? SROM_DATA_1 : SROM_DATA_0;
		srom_clk_ग_लिखो(db, srom_data);
	पूर्ण

	uw32(DCR9, CR9_SROM_READ | CR9_SRCS);

	क्रम (i = 16; i > 0; i--) अणु
		uw32(DCR9, CR9_SROM_READ | CR9_SRCS | CR9_SRCLK);
		udelay(5);
		srom_data = (srom_data << 1) |
			    ((ur32(DCR9) & CR9_CRDOUT) ? 1 : 0);
		uw32(DCR9, CR9_SROM_READ | CR9_SRCS);
		udelay(5);
	पूर्ण

	uw32(DCR9, CR9_SROM_READ);
	वापस srom_data;
पूर्ण


/*
 *	Auto sense the media mode
 */

अटल u8 uli526x_sense_speed(काष्ठा uli526x_board_info * db)
अणु
	काष्ठा uli_phy_ops *phy = &db->phy;
	u8 ErrFlag = 0;
	u16 phy_mode;

	phy_mode = phy->पढ़ो(db, db->phy_addr, 1);
	phy_mode = phy->पढ़ो(db, db->phy_addr, 1);

	अगर ( (phy_mode & 0x24) == 0x24 ) अणु

		phy_mode = ((phy->पढ़ो(db, db->phy_addr, 5) & 0x01e0)<<7);
		अगर(phy_mode&0x8000)
			phy_mode = 0x8000;
		अन्यथा अगर(phy_mode&0x4000)
			phy_mode = 0x4000;
		अन्यथा अगर(phy_mode&0x2000)
			phy_mode = 0x2000;
		अन्यथा
			phy_mode = 0x1000;

		चयन (phy_mode) अणु
		हाल 0x1000: db->op_mode = ULI526X_10MHF; अवरोध;
		हाल 0x2000: db->op_mode = ULI526X_10MFD; अवरोध;
		हाल 0x4000: db->op_mode = ULI526X_100MHF; अवरोध;
		हाल 0x8000: db->op_mode = ULI526X_100MFD; अवरोध;
		शेष: db->op_mode = ULI526X_10MHF; ErrFlag = 1; अवरोध;
		पूर्ण
	पूर्ण अन्यथा अणु
		db->op_mode = ULI526X_10MHF;
		ULI526X_DBUG(0, "Link Failed :", phy_mode);
		ErrFlag = 1;
	पूर्ण

	वापस ErrFlag;
पूर्ण


/*
 *	Set 10/100 phyxcer capability
 *	AUTO mode : phyxcer रेजिस्टर4 is NIC capability
 *	Force mode: phyxcer रेजिस्टर4 is the क्रमce media
 */

अटल व्योम uli526x_set_phyxcer(काष्ठा uli526x_board_info *db)
अणु
	काष्ठा uli_phy_ops *phy = &db->phy;
	u16 phy_reg;

	/* Phyxcer capability setting */
	phy_reg = phy->पढ़ो(db, db->phy_addr, 4) & ~0x01e0;

	अगर (db->media_mode & ULI526X_AUTO) अणु
		/* AUTO Mode */
		phy_reg |= db->PHY_reg4;
	पूर्ण अन्यथा अणु
		/* Force Mode */
		चयन(db->media_mode) अणु
		हाल ULI526X_10MHF: phy_reg |= 0x20; अवरोध;
		हाल ULI526X_10MFD: phy_reg |= 0x40; अवरोध;
		हाल ULI526X_100MHF: phy_reg |= 0x80; अवरोध;
		हाल ULI526X_100MFD: phy_reg |= 0x100; अवरोध;
		पूर्ण

	पूर्ण

  	/* Write new capability to Phyxcer Reg4 */
	अगर ( !(phy_reg & 0x01e0)) अणु
		phy_reg|=db->PHY_reg4;
		db->media_mode|=ULI526X_AUTO;
	पूर्ण
	phy->ग_लिखो(db, db->phy_addr, 4, phy_reg);

 	/* Restart Auto-Negotiation */
	phy->ग_लिखो(db, db->phy_addr, 0, 0x1200);
	udelay(50);
पूर्ण


/*
 *	Process op-mode
 	AUTO mode : PHY controller in Auto-negotiation Mode
 *	Force mode: PHY controller in क्रमce mode with HUB
 *			N-way क्रमce capability with SWITCH
 */

अटल व्योम uli526x_process_mode(काष्ठा uli526x_board_info *db)
अणु
	काष्ठा uli_phy_ops *phy = &db->phy;
	u16 phy_reg;

	/* Full Duplex Mode Check */
	अगर (db->op_mode & 0x4)
		db->cr6_data |= CR6_FDM;	/* Set Full Duplex Bit */
	अन्यथा
		db->cr6_data &= ~CR6_FDM;	/* Clear Full Duplex Bit */

	update_cr6(db->cr6_data, db->ioaddr);

	/* 10/100M phyxcer क्रमce mode need */
	अगर (!(db->media_mode & 0x8)) अणु
		/* Forece Mode */
		phy_reg = phy->पढ़ो(db, db->phy_addr, 6);
		अगर (!(phy_reg & 0x1)) अणु
			/* parter without N-Way capability */
			phy_reg = 0x0;
			चयन(db->op_mode) अणु
			हाल ULI526X_10MHF: phy_reg = 0x0; अवरोध;
			हाल ULI526X_10MFD: phy_reg = 0x100; अवरोध;
			हाल ULI526X_100MHF: phy_reg = 0x2000; अवरोध;
			हाल ULI526X_100MFD: phy_reg = 0x2100; अवरोध;
			पूर्ण
			phy->ग_लिखो(db, db->phy_addr, 0, phy_reg);
		पूर्ण
	पूर्ण
पूर्ण


/* M5261/M5263 Chip */
अटल व्योम phy_ग_लिखोby_cr9(काष्ठा uli526x_board_info *db, u8 phy_addr,
			    u8 offset, u16 phy_data)
अणु
	u16 i;

	/* Send 33 synchronization घड़ी to Phy controller */
	क्रम (i = 0; i < 35; i++)
		phy_ग_लिखो_1bit(db, PHY_DATA_1);

	/* Send start command(01) to Phy */
	phy_ग_लिखो_1bit(db, PHY_DATA_0);
	phy_ग_लिखो_1bit(db, PHY_DATA_1);

	/* Send ग_लिखो command(01) to Phy */
	phy_ग_लिखो_1bit(db, PHY_DATA_0);
	phy_ग_लिखो_1bit(db, PHY_DATA_1);

	/* Send Phy address */
	क्रम (i = 0x10; i > 0; i = i >> 1)
		phy_ग_लिखो_1bit(db, phy_addr & i ? PHY_DATA_1 : PHY_DATA_0);

	/* Send रेजिस्टर address */
	क्रम (i = 0x10; i > 0; i = i >> 1)
		phy_ग_लिखो_1bit(db, offset & i ? PHY_DATA_1 : PHY_DATA_0);

	/* written trasnition */
	phy_ग_लिखो_1bit(db, PHY_DATA_1);
	phy_ग_लिखो_1bit(db, PHY_DATA_0);

	/* Write a word data to PHY controller */
	क्रम (i = 0x8000; i > 0; i >>= 1)
		phy_ग_लिखो_1bit(db, phy_data & i ? PHY_DATA_1 : PHY_DATA_0);
पूर्ण

अटल u16 phy_पढ़ोby_cr9(काष्ठा uli526x_board_info *db, u8 phy_addr, u8 offset)
अणु
	u16 phy_data;
	पूर्णांक i;

	/* Send 33 synchronization घड़ी to Phy controller */
	क्रम (i = 0; i < 35; i++)
		phy_ग_लिखो_1bit(db, PHY_DATA_1);

	/* Send start command(01) to Phy */
	phy_ग_लिखो_1bit(db, PHY_DATA_0);
	phy_ग_लिखो_1bit(db, PHY_DATA_1);

	/* Send पढ़ो command(10) to Phy */
	phy_ग_लिखो_1bit(db, PHY_DATA_1);
	phy_ग_लिखो_1bit(db, PHY_DATA_0);

	/* Send Phy address */
	क्रम (i = 0x10; i > 0; i = i >> 1)
		phy_ग_लिखो_1bit(db, phy_addr & i ? PHY_DATA_1 : PHY_DATA_0);

	/* Send रेजिस्टर address */
	क्रम (i = 0x10; i > 0; i = i >> 1)
		phy_ग_लिखो_1bit(db, offset & i ? PHY_DATA_1 : PHY_DATA_0);

	/* Skip transition state */
	phy_पढ़ो_1bit(db);

	/* पढ़ो 16bit data */
	क्रम (phy_data = 0, i = 0; i < 16; i++) अणु
		phy_data <<= 1;
		phy_data |= phy_पढ़ो_1bit(db);
	पूर्ण

	वापस phy_data;
पूर्ण

अटल u16 phy_पढ़ोby_cr10(काष्ठा uli526x_board_info *db, u8 phy_addr,
			   u8 offset)
अणु
	व्योम __iomem *ioaddr = db->ioaddr;
	u32 cr10_value = phy_addr;

	cr10_value = (cr10_value <<  5) + offset;
	cr10_value = (cr10_value << 16) + 0x08000000;
	uw32(DCR10, cr10_value);
	udelay(1);
	जबतक (1) अणु
		cr10_value = ur32(DCR10);
		अगर (cr10_value & 0x10000000)
			अवरोध;
	पूर्ण
	वापस cr10_value & 0x0ffff;
पूर्ण

अटल व्योम phy_ग_लिखोby_cr10(काष्ठा uli526x_board_info *db, u8 phy_addr,
			     u8 offset, u16 phy_data)
अणु
	व्योम __iomem *ioaddr = db->ioaddr;
	u32 cr10_value = phy_addr;

	cr10_value = (cr10_value <<  5) + offset;
	cr10_value = (cr10_value << 16) + 0x04000000 + phy_data;
	uw32(DCR10, cr10_value);
	udelay(1);
पूर्ण
/*
 *	Write one bit data to Phy Controller
 */

अटल व्योम phy_ग_लिखो_1bit(काष्ठा uli526x_board_info *db, u32 data)
अणु
	व्योम __iomem *ioaddr = db->ioaddr;

	uw32(DCR9, data);		/* MII Clock Low */
	udelay(1);
	uw32(DCR9, data | MDCLKH);	/* MII Clock High */
	udelay(1);
	uw32(DCR9, data);		/* MII Clock Low */
	udelay(1);
पूर्ण


/*
 *	Read one bit phy data from PHY controller
 */

अटल u16 phy_पढ़ो_1bit(काष्ठा uli526x_board_info *db)
अणु
	व्योम __iomem *ioaddr = db->ioaddr;
	u16 phy_data;

	uw32(DCR9, 0x50000);
	udelay(1);
	phy_data = (ur32(DCR9) >> 19) & 0x1;
	uw32(DCR9, 0x40000);
	udelay(1);

	वापस phy_data;
पूर्ण


अटल स्थिर काष्ठा pci_device_id uli526x_pci_tbl[] = अणु
	अणु 0x10B9, 0x5261, PCI_ANY_ID, PCI_ANY_ID, 0, 0, PCI_ULI5261_ID पूर्ण,
	अणु 0x10B9, 0x5263, PCI_ANY_ID, PCI_ANY_ID, 0, 0, PCI_ULI5263_ID पूर्ण,
	अणु 0, पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(pci, uli526x_pci_tbl);

अटल SIMPLE_DEV_PM_OPS(uli526x_pm_ops, uli526x_suspend, uli526x_resume);

अटल काष्ठा pci_driver uli526x_driver = अणु
	.name		= "uli526x",
	.id_table	= uli526x_pci_tbl,
	.probe		= uli526x_init_one,
	.हटाओ		= uli526x_हटाओ_one,
	.driver.pm	= &uli526x_pm_ops,
पूर्ण;

MODULE_AUTHOR("Peer Chen, peer.chen@uli.com.tw");
MODULE_DESCRIPTION("ULi M5261/M5263 fast ethernet driver");
MODULE_LICENSE("GPL");

module_param(debug, पूर्णांक, 0644);
module_param(mode, पूर्णांक, 0);
module_param(cr6set, पूर्णांक, 0);
MODULE_PARM_DESC(debug, "ULi M5261/M5263 enable debugging (0-1)");
MODULE_PARM_DESC(mode, "ULi M5261/M5263: Bit 0: 10/100Mbps, bit 2: duplex, bit 8: HomePNA");

/*	Description:
 *	when user used insmod to add module, प्रणाली invoked init_module()
 *	to रेजिस्टर the services.
 */

अटल पूर्णांक __init uli526x_init_module(व्योम)
अणु

	ULI526X_DBUG(0, "init_module() ", debug);

	अगर (debug)
		uli526x_debug = debug;	/* set debug flag */
	अगर (cr6set)
		uli526x_cr6_user_set = cr6set;

	चयन (mode) अणु
	हाल ULI526X_10MHF:
	हाल ULI526X_100MHF:
	हाल ULI526X_10MFD:
	हाल ULI526X_100MFD:
		uli526x_media_mode = mode;
		अवरोध;
	शेष:
		uli526x_media_mode = ULI526X_AUTO;
		अवरोध;
	पूर्ण

	वापस pci_रेजिस्टर_driver(&uli526x_driver);
पूर्ण


/*
 *	Description:
 *	when user used rmmod to delete module, प्रणाली invoked clean_module()
 *	to un-रेजिस्टर all रेजिस्टरed services.
 */

अटल व्योम __निकास uli526x_cleanup_module(व्योम)
अणु
	ULI526X_DBUG(0, "uli526x_cleanup_module() ", debug);
	pci_unरेजिस्टर_driver(&uli526x_driver);
पूर्ण

module_init(uli526x_init_module);
module_निकास(uli526x_cleanup_module);
