<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
    A Davicom DM9102/DM9102A/DM9102A+DM9801/DM9102A+DM9802 NIC fast
    ethernet driver क्रम Linux.
    Copyright (C) 1997  Sten Wang


    DAVICOM Web-Site: www.davicom.com.tw

    Author: Sten Wang, 886-3-5798797-8517, E-mail: sten_wang@davicom.com.tw
    Maपूर्णांकainer: Tobias Ringstrom <tori@unhappy.mine.nu>

    (C)Copyright 1997-1998 DAVICOM Semiconductor,Inc. All Rights Reserved.

    Marcelo Tosatti <marcelo@conectiva.com.br> :
    Made it compile in 2.3 (device to net_device)

    Alan Cox <alan@lxorguk.ukuu.org.uk> :
    Cleaned up क्रम kernel merge.
    Removed the back compatibility support
    Reक्रमmatted, fixing spelling etc as I went
    Removed IRQ 0-15 assumption

    Jeff Garzik <jgarzik@pobox.com> :
    Updated to use new PCI driver API.
    Resource usage cleanups.
    Report driver version to user.

    Tobias Ringstrom <tori@unhappy.mine.nu> :
    Cleaned up and added SMP safety.  Thanks go to Jeff Garzik,
    Andrew Morton and Frank Davis क्रम the SMP safety fixes.

    Vojtech Pavlik <vojtech@suse.cz> :
    Cleaned up poपूर्णांकer arithmetics.
    Fixed a lot of 64bit issues.
    Cleaned up prपूर्णांकk()s a bit.
    Fixed some obvious big endian problems.

    Tobias Ringstrom <tori@unhappy.mine.nu> :
    Use समय_after क्रम jअगरfies calculation.  Added ethtool
    support.  Updated PCI resource allocation.  Do not
    क्रमget to unmap PCI mapped skbs.

    Alan Cox <alan@lxorguk.ukuu.org.uk>
    Added new PCI identअगरiers provided by Clear Zhang at ALi
    क्रम their 1563 ethernet device.

    TODO

    Check on 64 bit boxes.
    Check and fix on big endian boxes.

    Test and make sure PCI latency is now correct क्रम all हालs.
*/

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#घोषणा DRV_NAME	"dmfe"

#समावेश <linux/module.h>
#समावेश <linux/kernel.h>
#समावेश <linux/माला.स>
#समावेश <linux/समयr.h>
#समावेश <linux/ptrace.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/ioport.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/pci.h>
#समावेश <linux/dma-mapping.h>
#समावेश <linux/init.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/etherdevice.h>
#समावेश <linux/ethtool.h>
#समावेश <linux/skbuff.h>
#समावेश <linux/delay.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/crc32.h>
#समावेश <linux/bitops.h>

#समावेश <यंत्र/processor.h>
#समावेश <यंत्र/पन.स>
#समावेश <यंत्र/dma.h>
#समावेश <linux/uaccess.h>
#समावेश <यंत्र/irq.h>

#अगर_घोषित CONFIG_TULIP_DM910X
#समावेश <linux/of.h>
#पूर्ण_अगर


/* Board/System/Debug inक्रमmation/definition ---------------- */
#घोषणा PCI_DM9132_ID   0x91321282      /* Davicom DM9132 ID */
#घोषणा PCI_DM9102_ID   0x91021282      /* Davicom DM9102 ID */
#घोषणा PCI_DM9100_ID   0x91001282      /* Davicom DM9100 ID */
#घोषणा PCI_DM9009_ID   0x90091282      /* Davicom DM9009 ID */

#घोषणा DM9102_IO_SIZE  0x80
#घोषणा DM9102A_IO_SIZE 0x100
#घोषणा TX_MAX_SEND_CNT 0x1             /* Maximum tx packet per समय */
#घोषणा TX_DESC_CNT     0x10            /* Allocated Tx descriptors */
#घोषणा RX_DESC_CNT     0x20            /* Allocated Rx descriptors */
#घोषणा TX_FREE_DESC_CNT (TX_DESC_CNT - 2)	/* Max TX packet count */
#घोषणा TX_WAKE_DESC_CNT (TX_DESC_CNT - 3)	/* TX wakeup count */
#घोषणा DESC_ALL_CNT    (TX_DESC_CNT + RX_DESC_CNT)
#घोषणा TX_BUF_ALLOC    0x600
#घोषणा RX_ALLOC_SIZE   0x620
#घोषणा DM910X_RESET    1
#घोषणा CR0_DEFAULT     0x00E00000      /* TX & RX burst mode */
#घोषणा CR6_DEFAULT     0x00080000      /* HD */
#घोषणा CR7_DEFAULT     0x180c1
#घोषणा CR15_DEFAULT    0x06            /* TxJabber RxWatchकरोg */
#घोषणा TDES0_ERR_MASK  0x4302          /* TXJT, LC, EC, FUE */
#घोषणा MAX_PACKET_SIZE 1514
#घोषणा DMFE_MAX_MULTICAST 14
#घोषणा RX_COPY_SIZE	100
#घोषणा MAX_CHECK_PACKET 0x8000
#घोषणा DM9801_NOISE_FLOOR 8
#घोषणा DM9802_NOISE_FLOOR 5

#घोषणा DMFE_WOL_LINKCHANGE	0x20000000
#घोषणा DMFE_WOL_SAMPLEPACKET	0x10000000
#घोषणा DMFE_WOL_MAGICPACKET	0x08000000


#घोषणा DMFE_10MHF      0
#घोषणा DMFE_100MHF     1
#घोषणा DMFE_10MFD      4
#घोषणा DMFE_100MFD     5
#घोषणा DMFE_AUTO       8
#घोषणा DMFE_1M_HPNA    0x10

#घोषणा DMFE_TXTH_72	0x400000	/* TX TH 72 byte */
#घोषणा DMFE_TXTH_96	0x404000	/* TX TH 96 byte */
#घोषणा DMFE_TXTH_128	0x0000		/* TX TH 128 byte */
#घोषणा DMFE_TXTH_256	0x4000		/* TX TH 256 byte */
#घोषणा DMFE_TXTH_512	0x8000		/* TX TH 512 byte */
#घोषणा DMFE_TXTH_1K	0xC000		/* TX TH 1K  byte */

#घोषणा DMFE_TIMER_WUT  (jअगरfies + HZ * 1)/* समयr wakeup समय : 1 second */
#घोषणा DMFE_TX_TIMEOUT ((3*HZ)/2)	/* tx packet समय-out समय 1.5 s" */
#घोषणा DMFE_TX_KICK 	(HZ/2)	/* tx packet Kick-out समय 0.5 s" */

#घोषणा dw32(reg, val)	ioग_लिखो32(val, ioaddr + (reg))
#घोषणा dw16(reg, val)	ioग_लिखो16(val, ioaddr + (reg))
#घोषणा dr32(reg)	ioपढ़ो32(ioaddr + (reg))
#घोषणा dr16(reg)	ioपढ़ो16(ioaddr + (reg))
#घोषणा dr8(reg)	ioपढ़ो8(ioaddr + (reg))

#घोषणा DMFE_DBUG(dbug_now, msg, value)			\
	करो अणु						\
		अगर (dmfe_debug || (dbug_now))		\
			pr_err("%s %lx\n",		\
			       (msg), (दीर्घ) (value));	\
	पूर्ण जबतक (0)

#घोषणा SHOW_MEDIA_TYPE(mode)				\
	pr_info("Change Speed to %sMhz %s duplex\n" ,	\
		(mode & 1) ? "100":"10",		\
		(mode & 4) ? "full":"half");


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

#घोषणा __CHK_IO_SIZE(pci_id, dev_rev) \
 (( ((pci_id)==PCI_DM9132_ID) || ((dev_rev) >= 0x30) ) ? \
	DM9102A_IO_SIZE: DM9102_IO_SIZE)

#घोषणा CHK_IO_SIZE(pci_dev) \
	(__CHK_IO_SIZE(((pci_dev)->device << 16) | (pci_dev)->venकरोr, \
	(pci_dev)->revision))

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

काष्ठा dmfe_board_info अणु
	u32 chip_id;			/* Chip venकरोr/Device ID */
	u8 chip_revision;		/* Chip revision */
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
	अचिन्हित दीर्घ tx_queue_cnt;	/* रुको to send packet count */
	अचिन्हित दीर्घ rx_avail_cnt;	/* available rx descriptor count */
	अचिन्हित दीर्घ पूर्णांकerval_rx_cnt;	/* rx packet count a callback समय */

	u16 HPNA_command;		/* For HPNA रेजिस्टर 16 */
	u16 HPNA_समयr;			/* For HPNA remote device check */
	u16 dbug_cnt;
	u16 NIC_capability;		/* NIC media capability */
	u16 PHY_reg4;			/* Saved Phyxcer रेजिस्टर 4 value */

	u8 HPNA_present;		/* 0:none, 1:DM9801, 2:DM9802 */
	u8 chip_type;			/* Keep DM9102A chip type */
	u8 media_mode;			/* user specअगरy media mode */
	u8 op_mode;			/* real work media mode */
	u8 phy_addr;
	u8 रुको_reset;			/* Hardware failed, need to reset */
	u8 dm910x_chk_mode;		/* Operating mode check */
	u8 first_in_callback;		/* Flag to record state */
	u8 wol_mode;			/* user WOL settings */
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
पूर्ण;

क्रमागत dmfe_offsets अणु
	DCR0 = 0x00, DCR1 = 0x08, DCR2 = 0x10, DCR3 = 0x18, DCR4 = 0x20,
	DCR5 = 0x28, DCR6 = 0x30, DCR7 = 0x38, DCR8 = 0x40, DCR9 = 0x48,
	DCR10 = 0x50, DCR11 = 0x58, DCR12 = 0x60, DCR13 = 0x68, DCR14 = 0x70,
	DCR15 = 0x78
पूर्ण;

क्रमागत dmfe_CR6_bits अणु
	CR6_RXSC = 0x2, CR6_PBF = 0x8, CR6_PM = 0x40, CR6_PAM = 0x80,
	CR6_FDM = 0x200, CR6_TXSC = 0x2000, CR6_STI = 0x100000,
	CR6_SFT = 0x200000, CR6_RXA = 0x40000000, CR6_NO_PURGE = 0x20000000
पूर्ण;

/* Global variable declaration ----------------------------- */
अटल पूर्णांक dmfe_debug;
अटल अचिन्हित अक्षर dmfe_media_mode = DMFE_AUTO;
अटल u32 dmfe_cr6_user_set;

/* For module input parameter */
अटल पूर्णांक debug;
अटल u32 cr6set;
अटल अचिन्हित अक्षर mode = 8;
अटल u8 chkmode = 1;
अटल u8 HPNA_mode;		/* Default: Low Power/High Speed */
अटल u8 HPNA_rx_cmd;		/* Default: Disable Rx remote command */
अटल u8 HPNA_tx_cmd;		/* Default: Don't issue remote command */
अटल u8 HPNA_NoiseFloor;	/* Default: HPNA NoiseFloor */
अटल u8 SF_mode;		/* Special Function: 1:VLAN, 2:RX Flow Control
				   4: TX छोड़ो packet */


/* function declaration ------------------------------------- */
अटल पूर्णांक dmfe_खोलो(काष्ठा net_device *);
अटल netdev_tx_t dmfe_start_xmit(काष्ठा sk_buff *, काष्ठा net_device *);
अटल पूर्णांक dmfe_stop(काष्ठा net_device *);
अटल व्योम dmfe_set_filter_mode(काष्ठा net_device *);
अटल स्थिर काष्ठा ethtool_ops netdev_ethtool_ops;
अटल u16 पढ़ो_srom_word(व्योम __iomem *, पूर्णांक);
अटल irqवापस_t dmfe_पूर्णांकerrupt(पूर्णांक , व्योम *);
#अगर_घोषित CONFIG_NET_POLL_CONTROLLER
अटल व्योम poll_dmfe (काष्ठा net_device *dev);
#पूर्ण_अगर
अटल व्योम dmfe_descriptor_init(काष्ठा net_device *);
अटल व्योम allocate_rx_buffer(काष्ठा net_device *);
अटल व्योम update_cr6(u32, व्योम __iomem *);
अटल व्योम send_filter_frame(काष्ठा net_device *);
अटल व्योम dm9132_id_table(काष्ठा net_device *);
अटल u16 dmfe_phy_पढ़ो(व्योम __iomem *, u8, u8, u32);
अटल व्योम dmfe_phy_ग_लिखो(व्योम __iomem *, u8, u8, u16, u32);
अटल व्योम dmfe_phy_ग_लिखो_1bit(व्योम __iomem *, u32);
अटल u16 dmfe_phy_पढ़ो_1bit(व्योम __iomem *);
अटल u8 dmfe_sense_speed(काष्ठा dmfe_board_info *);
अटल व्योम dmfe_process_mode(काष्ठा dmfe_board_info *);
अटल व्योम dmfe_समयr(काष्ठा समयr_list *);
अटल अंतरभूत u32 cal_CRC(अचिन्हित अक्षर *, अचिन्हित पूर्णांक, u8);
अटल व्योम dmfe_rx_packet(काष्ठा net_device *, काष्ठा dmfe_board_info *);
अटल व्योम dmfe_मुक्त_tx_pkt(काष्ठा net_device *, काष्ठा dmfe_board_info *);
अटल व्योम dmfe_reuse_skb(काष्ठा dmfe_board_info *, काष्ठा sk_buff *);
अटल व्योम dmfe_dynamic_reset(काष्ठा net_device *);
अटल व्योम dmfe_मुक्त_rxbuffer(काष्ठा dmfe_board_info *);
अटल व्योम dmfe_init_dm910x(काष्ठा net_device *);
अटल व्योम dmfe_parse_srom(काष्ठा dmfe_board_info *);
अटल व्योम dmfe_program_DM9801(काष्ठा dmfe_board_info *, पूर्णांक);
अटल व्योम dmfe_program_DM9802(काष्ठा dmfe_board_info *);
अटल व्योम dmfe_HPNA_remote_cmd_chk(काष्ठा dmfe_board_info * );
अटल व्योम dmfe_set_phyxcer(काष्ठा dmfe_board_info *);

/* DM910X network board routine ---------------------------- */

अटल स्थिर काष्ठा net_device_ops netdev_ops = अणु
	.nकरो_खोलो 		= dmfe_खोलो,
	.nकरो_stop		= dmfe_stop,
	.nकरो_start_xmit		= dmfe_start_xmit,
	.nकरो_set_rx_mode	= dmfe_set_filter_mode,
	.nकरो_set_mac_address	= eth_mac_addr,
	.nकरो_validate_addr	= eth_validate_addr,
#अगर_घोषित CONFIG_NET_POLL_CONTROLLER
	.nकरो_poll_controller	= poll_dmfe,
#पूर्ण_अगर
पूर्ण;

/*
 *	Search DM910X board ,allocate space and रेजिस्टर it
 */

अटल पूर्णांक dmfe_init_one(काष्ठा pci_dev *pdev, स्थिर काष्ठा pci_device_id *ent)
अणु
	काष्ठा dmfe_board_info *db;	/* board inक्रमmation काष्ठाure */
	काष्ठा net_device *dev;
	u32 pci_pmr;
	पूर्णांक i, err;

	DMFE_DBUG(0, "dmfe_init_one()", 0);

	/*
	 *	SPARC on-board DM910x chips should be handled by the मुख्य
	 *	tulip driver, except क्रम early DM9100s.
	 */
#अगर_घोषित CONFIG_TULIP_DM910X
	अगर ((ent->driver_data == PCI_DM9100_ID && pdev->revision >= 0x30) ||
	    ent->driver_data == PCI_DM9102_ID) अणु
		काष्ठा device_node *dp = pci_device_to_OF_node(pdev);

		अगर (dp && of_get_property(dp, "local-mac-address", शून्य)) अणु
			pr_info("skipping on-board DM910x (use tulip)\n");
			वापस -ENODEV;
		पूर्ण
	पूर्ण
#पूर्ण_अगर

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

	अगर (pci_resource_len(pdev, 0) < (CHK_IO_SIZE(pdev)) ) अणु
		pr_err("Allocated I/O size too small\n");
		err = -ENODEV;
		जाओ err_out_disable;
	पूर्ण

#अगर 0	/* pci_अणुenable_device,set_masterपूर्ण sets minimum latency क्रम us now */

	/* Set Latency Timer 80h */
	/* FIXME: setting values > 32 अवरोधs some SiS 559x stuff.
	   Need a PCI quirk.. */

	pci_ग_लिखो_config_byte(pdev, PCI_LATENCY_TIMER, 0x80);
#पूर्ण_अगर

	अगर (pci_request_regions(pdev, DRV_NAME)) अणु
		pr_err("Failed to request PCI regions\n");
		err = -ENODEV;
		जाओ err_out_disable;
	पूर्ण

	/* Init प्रणाली & device */
	db = netdev_priv(dev);

	/* Allocate Tx/Rx descriptor memory */
	db->desc_pool_ptr = dma_alloc_coherent(&pdev->dev,
					       माप(काष्ठा tx_desc) * DESC_ALL_CNT + 0x20,
					       &db->desc_pool_dma_ptr, GFP_KERNEL);
	अगर (!db->desc_pool_ptr) अणु
		err = -ENOMEM;
		जाओ err_out_res;
	पूर्ण

	db->buf_pool_ptr = dma_alloc_coherent(&pdev->dev,
					      TX_BUF_ALLOC * TX_DESC_CNT + 4,
					      &db->buf_pool_dma_ptr, GFP_KERNEL);
	अगर (!db->buf_pool_ptr) अणु
		err = -ENOMEM;
		जाओ err_out_मुक्त_desc;
	पूर्ण

	db->first_tx_desc = (काष्ठा tx_desc *) db->desc_pool_ptr;
	db->first_tx_desc_dma = db->desc_pool_dma_ptr;
	db->buf_pool_start = db->buf_pool_ptr;
	db->buf_pool_dma_start = db->buf_pool_dma_ptr;

	db->chip_id = ent->driver_data;
	/* IO type range. */
	db->ioaddr = pci_iomap(pdev, 0, 0);
	अगर (!db->ioaddr) अणु
		err = -ENOMEM;
		जाओ err_out_मुक्त_buf;
	पूर्ण

	db->chip_revision = pdev->revision;
	db->wol_mode = 0;

	db->pdev = pdev;

	pci_set_drvdata(pdev, dev);
	dev->netdev_ops = &netdev_ops;
	dev->ethtool_ops = &netdev_ethtool_ops;
	netअगर_carrier_off(dev);
	spin_lock_init(&db->lock);

	pci_पढ़ो_config_dword(pdev, 0x50, &pci_pmr);
	pci_pmr &= 0x70000;
	अगर ( (pci_pmr == 0x10000) && (db->chip_revision == 0x31) )
		db->chip_type = 1;	/* DM9102A E3 */
	अन्यथा
		db->chip_type = 0;

	/* पढ़ो 64 word srom data */
	क्रम (i = 0; i < 64; i++) अणु
		((__le16 *) db->srom)[i] =
			cpu_to_le16(पढ़ो_srom_word(db->ioaddr, i));
	पूर्ण

	/* Set Node address */
	क्रम (i = 0; i < 6; i++)
		dev->dev_addr[i] = db->srom[20 + i];

	err = रेजिस्टर_netdev (dev);
	अगर (err)
		जाओ err_out_unmap;

	dev_info(&dev->dev, "Davicom DM%04lx at pci%s, %pM, irq %d\n",
		 ent->driver_data >> 16,
		 pci_name(pdev), dev->dev_addr, pdev->irq);

	pci_set_master(pdev);

	वापस 0;

err_out_unmap:
	pci_iounmap(pdev, db->ioaddr);
err_out_मुक्त_buf:
	dma_मुक्त_coherent(&pdev->dev, TX_BUF_ALLOC * TX_DESC_CNT + 4,
			  db->buf_pool_ptr, db->buf_pool_dma_ptr);
err_out_मुक्त_desc:
	dma_मुक्त_coherent(&pdev->dev,
			  माप(काष्ठा tx_desc) * DESC_ALL_CNT + 0x20,
			  db->desc_pool_ptr, db->desc_pool_dma_ptr);
err_out_res:
	pci_release_regions(pdev);
err_out_disable:
	pci_disable_device(pdev);
err_out_मुक्त:
	मुक्त_netdev(dev);

	वापस err;
पूर्ण


अटल व्योम dmfe_हटाओ_one(काष्ठा pci_dev *pdev)
अणु
	काष्ठा net_device *dev = pci_get_drvdata(pdev);
	काष्ठा dmfe_board_info *db = netdev_priv(dev);

	DMFE_DBUG(0, "dmfe_remove_one()", 0);

 	अगर (dev) अणु

		unरेजिस्टर_netdev(dev);
		pci_iounmap(db->pdev, db->ioaddr);
		dma_मुक्त_coherent(&db->pdev->dev,
				  माप(काष्ठा tx_desc) * DESC_ALL_CNT + 0x20,
				  db->desc_pool_ptr, db->desc_pool_dma_ptr);
		dma_मुक्त_coherent(&db->pdev->dev,
				  TX_BUF_ALLOC * TX_DESC_CNT + 4,
				  db->buf_pool_ptr, db->buf_pool_dma_ptr);
		pci_release_regions(pdev);
		मुक्त_netdev(dev);	/* मुक्त board inक्रमmation */
	पूर्ण

	DMFE_DBUG(0, "dmfe_remove_one() exit", 0);
पूर्ण


/*
 *	Open the पूर्णांकerface.
 *	The पूर्णांकerface is खोलोed whenever "ifconfig" actives it.
 */

अटल पूर्णांक dmfe_खोलो(काष्ठा net_device *dev)
अणु
	काष्ठा dmfe_board_info *db = netdev_priv(dev);
	स्थिर पूर्णांक irq = db->pdev->irq;
	पूर्णांक ret;

	DMFE_DBUG(0, "dmfe_open", 0);

	ret = request_irq(irq, dmfe_पूर्णांकerrupt, IRQF_SHARED, dev->name, dev);
	अगर (ret)
		वापस ret;

	/* प्रणाली variable init */
	db->cr6_data = CR6_DEFAULT | dmfe_cr6_user_set;
	db->tx_packet_cnt = 0;
	db->tx_queue_cnt = 0;
	db->rx_avail_cnt = 0;
	db->रुको_reset = 0;

	db->first_in_callback = 0;
	db->NIC_capability = 0xf;	/* All capability*/
	db->PHY_reg4 = 0x1e0;

	/* CR6 operation mode decision */
	अगर ( !chkmode || (db->chip_id == PCI_DM9132_ID) ||
		(db->chip_revision >= 0x30) ) अणु
    		db->cr6_data |= DMFE_TXTH_256;
		db->cr0_data = CR0_DEFAULT;
		db->dm910x_chk_mode=4;		/* Enter the normal mode */
 	पूर्ण अन्यथा अणु
		db->cr6_data |= CR6_SFT;	/* Store & Forward mode */
		db->cr0_data = 0;
		db->dm910x_chk_mode = 1;	/* Enter the check mode */
	पूर्ण

	/* Initialize DM910X board */
	dmfe_init_dm910x(dev);

	/* Active System Interface */
	netअगर_wake_queue(dev);

	/* set and active a समयr process */
	समयr_setup(&db->समयr, dmfe_समयr, 0);
	db->समयr.expires = DMFE_TIMER_WUT + HZ * 2;
	add_समयr(&db->समयr);

	वापस 0;
पूर्ण


/*	Initialize DM910X board
 *	Reset DM910X board
 *	Initialize TX/Rx descriptor chain काष्ठाure
 *	Send the set-up frame
 *	Enable Tx/Rx machine
 */

अटल व्योम dmfe_init_dm910x(काष्ठा net_device *dev)
अणु
	काष्ठा dmfe_board_info *db = netdev_priv(dev);
	व्योम __iomem *ioaddr = db->ioaddr;

	DMFE_DBUG(0, "dmfe_init_dm910x()", 0);

	/* Reset DM910x MAC controller */
	dw32(DCR0, DM910X_RESET);	/* RESET MAC */
	udelay(100);
	dw32(DCR0, db->cr0_data);
	udelay(5);

	/* Phy addr : DM910(A)2/DM9132/9801, phy address = 1 */
	db->phy_addr = 1;

	/* Parser SROM and media mode */
	dmfe_parse_srom(db);
	db->media_mode = dmfe_media_mode;

	/* RESET Phyxcer Chip by GPR port bit 7 */
	dw32(DCR12, 0x180);		/* Let bit 7 output port */
	अगर (db->chip_id == PCI_DM9009_ID) अणु
		dw32(DCR12, 0x80);	/* Issue RESET संकेत */
		mdelay(300);			/* Delay 300 ms */
	पूर्ण
	dw32(DCR12, 0x0);	/* Clear RESET संकेत */

	/* Process Phyxcer Media Mode */
	अगर ( !(db->media_mode & 0x10) )	/* Force 1M mode */
		dmfe_set_phyxcer(db);

	/* Media Mode Process */
	अगर ( !(db->media_mode & DMFE_AUTO) )
		db->op_mode = db->media_mode; 	/* Force Mode */

	/* Initialize Transmit/Receive descriptor and CR3/4 */
	dmfe_descriptor_init(dev);

	/* Init CR6 to program DM910x operation */
	update_cr6(db->cr6_data, ioaddr);

	/* Send setup frame */
	अगर (db->chip_id == PCI_DM9132_ID)
		dm9132_id_table(dev);	/* DM9132 */
	अन्यथा
		send_filter_frame(dev);	/* DM9102/DM9102A */

	/* Init CR7, पूर्णांकerrupt active bit */
	db->cr7_data = CR7_DEFAULT;
	dw32(DCR7, db->cr7_data);

	/* Init CR15, Tx jabber and Rx watchकरोg समयr */
	dw32(DCR15, db->cr15_data);

	/* Enable DM910X Tx/Rx function */
	db->cr6_data |= CR6_RXSC | CR6_TXSC | 0x40000;
	update_cr6(db->cr6_data, ioaddr);
पूर्ण


/*
 *	Hardware start transmission.
 *	Send a packet to media from the upper layer.
 */

अटल netdev_tx_t dmfe_start_xmit(काष्ठा sk_buff *skb,
					 काष्ठा net_device *dev)
अणु
	काष्ठा dmfe_board_info *db = netdev_priv(dev);
	व्योम __iomem *ioaddr = db->ioaddr;
	काष्ठा tx_desc *txptr;
	अचिन्हित दीर्घ flags;

	DMFE_DBUG(0, "dmfe_start_xmit", 0);

	/* Too large packet check */
	अगर (skb->len > MAX_PACKET_SIZE) अणु
		pr_err("big packet = %d\n", (u16)skb->len);
		dev_kमुक्त_skb_any(skb);
		वापस NETDEV_TX_OK;
	पूर्ण

	/* Resource flag check */
	netअगर_stop_queue(dev);

	spin_lock_irqsave(&db->lock, flags);

	/* No Tx resource check, it never happen nromally */
	अगर (db->tx_queue_cnt >= TX_FREE_DESC_CNT) अणु
		spin_unlock_irqrestore(&db->lock, flags);
		pr_err("No Tx resource %ld\n", db->tx_queue_cnt);
		वापस NETDEV_TX_BUSY;
	पूर्ण

	/* Disable NIC पूर्णांकerrupt */
	dw32(DCR7, 0);

	/* transmit this packet */
	txptr = db->tx_insert_ptr;
	skb_copy_from_linear_data(skb, txptr->tx_buf_ptr, skb->len);
	txptr->tdes1 = cpu_to_le32(0xe1000000 | skb->len);

	/* Poपूर्णांक to next transmit मुक्त descriptor */
	db->tx_insert_ptr = txptr->next_tx_desc;

	/* Transmit Packet Process */
	अगर ( (!db->tx_queue_cnt) && (db->tx_packet_cnt < TX_MAX_SEND_CNT) ) अणु
		txptr->tdes0 = cpu_to_le32(0x80000000);	/* Set owner bit */
		db->tx_packet_cnt++;			/* Ready to send */
		dw32(DCR1, 0x1);			/* Issue Tx polling */
		netअगर_trans_update(dev);		/* saved समय stamp */
	पूर्ण अन्यथा अणु
		db->tx_queue_cnt++;			/* queue TX packet */
		dw32(DCR1, 0x1);			/* Issue Tx polling */
	पूर्ण

	/* Tx resource check */
	अगर ( db->tx_queue_cnt < TX_FREE_DESC_CNT )
		netअगर_wake_queue(dev);

	/* Restore CR7 to enable पूर्णांकerrupt */
	spin_unlock_irqrestore(&db->lock, flags);
	dw32(DCR7, db->cr7_data);

	/* मुक्त this SKB */
	dev_consume_skb_any(skb);

	वापस NETDEV_TX_OK;
पूर्ण


/*
 *	Stop the पूर्णांकerface.
 *	The पूर्णांकerface is stopped when it is brought.
 */

अटल पूर्णांक dmfe_stop(काष्ठा net_device *dev)
अणु
	काष्ठा dmfe_board_info *db = netdev_priv(dev);
	व्योम __iomem *ioaddr = db->ioaddr;

	DMFE_DBUG(0, "dmfe_stop", 0);

	/* disable प्रणाली */
	netअगर_stop_queue(dev);

	/* deleted समयr */
	del_समयr_sync(&db->समयr);

	/* Reset & stop DM910X board */
	dw32(DCR0, DM910X_RESET);
	udelay(100);
	dmfe_phy_ग_लिखो(ioaddr, db->phy_addr, 0, 0x8000, db->chip_id);

	/* मुक्त पूर्णांकerrupt */
	मुक्त_irq(db->pdev->irq, dev);

	/* मुक्त allocated rx buffer */
	dmfe_मुक्त_rxbuffer(db);

#अगर 0
	/* show statistic counter */
	prपूर्णांकk("FU:%lx EC:%lx LC:%lx NC:%lx LOC:%lx TXJT:%lx RESET:%lx RCR8:%lx FAL:%lx TT:%lx\n",
	       db->tx_fअगरo_underrun, db->tx_excessive_collision,
	       db->tx_late_collision, db->tx_no_carrier, db->tx_loss_carrier,
	       db->tx_jabber_समयout, db->reset_count, db->reset_cr8,
	       db->reset_fatal, db->reset_TXसमयout);
#पूर्ण_अगर

	वापस 0;
पूर्ण


/*
 *	DM9102 insterrupt handler
 *	receive the packet to upper layer, मुक्त the transmitted packet
 */

अटल irqवापस_t dmfe_पूर्णांकerrupt(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा net_device *dev = dev_id;
	काष्ठा dmfe_board_info *db = netdev_priv(dev);
	व्योम __iomem *ioaddr = db->ioaddr;
	अचिन्हित दीर्घ flags;

	DMFE_DBUG(0, "dmfe_interrupt()", 0);

	spin_lock_irqsave(&db->lock, flags);

	/* Got DM910X status */
	db->cr5_data = dr32(DCR5);
	dw32(DCR5, db->cr5_data);
	अगर ( !(db->cr5_data & 0xc1) ) अणु
		spin_unlock_irqrestore(&db->lock, flags);
		वापस IRQ_HANDLED;
	पूर्ण

	/* Disable all पूर्णांकerrupt in CR7 to solve the पूर्णांकerrupt edge problem */
	dw32(DCR7, 0);

	/* Check प्रणाली status */
	अगर (db->cr5_data & 0x2000) अणु
		/* प्रणाली bus error happen */
		DMFE_DBUG(1, "System bus error happen. CR5=", db->cr5_data);
		db->reset_fatal++;
		db->रुको_reset = 1;	/* Need to RESET */
		spin_unlock_irqrestore(&db->lock, flags);
		वापस IRQ_HANDLED;
	पूर्ण

	 /* Received the coming packet */
	अगर ( (db->cr5_data & 0x40) && db->rx_avail_cnt )
		dmfe_rx_packet(dev, db);

	/* पुनः_स्मृतिate rx descriptor buffer */
	अगर (db->rx_avail_cnt<RX_DESC_CNT)
		allocate_rx_buffer(dev);

	/* Free the transmitted descriptor */
	अगर ( db->cr5_data & 0x01)
		dmfe_मुक्त_tx_pkt(dev, db);

	/* Mode Check */
	अगर (db->dm910x_chk_mode & 0x2) अणु
		db->dm910x_chk_mode = 0x4;
		db->cr6_data |= 0x100;
		update_cr6(db->cr6_data, ioaddr);
	पूर्ण

	/* Restore CR7 to enable पूर्णांकerrupt mask */
	dw32(DCR7, db->cr7_data);

	spin_unlock_irqrestore(&db->lock, flags);
	वापस IRQ_HANDLED;
पूर्ण


#अगर_घोषित CONFIG_NET_POLL_CONTROLLER
/*
 * Polling 'interrupt' - used by things like netconsole to send skbs
 * without having to re-enable पूर्णांकerrupts. It's not called जबतक
 * the पूर्णांकerrupt routine is executing.
 */

अटल व्योम poll_dmfe (काष्ठा net_device *dev)
अणु
	काष्ठा dmfe_board_info *db = netdev_priv(dev);
	स्थिर पूर्णांक irq = db->pdev->irq;

	/* disable_irq here is not very nice, but with the lockless
	   पूर्णांकerrupt handler we have no other choice. */
	disable_irq(irq);
	dmfe_पूर्णांकerrupt (irq, dev);
	enable_irq(irq);
पूर्ण
#पूर्ण_अगर

/*
 *	Free TX resource after TX complete
 */

अटल व्योम dmfe_मुक्त_tx_pkt(काष्ठा net_device *dev, काष्ठा dmfe_board_info *db)
अणु
	काष्ठा tx_desc *txptr;
	व्योम __iomem *ioaddr = db->ioaddr;
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
						update_cr6(db->cr6_data, ioaddr);
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

	/* Send the Tx packet in queue */
	अगर ( (db->tx_packet_cnt < TX_MAX_SEND_CNT) && db->tx_queue_cnt ) अणु
		txptr->tdes0 = cpu_to_le32(0x80000000);	/* Set owner bit */
		db->tx_packet_cnt++;			/* Ready to send */
		db->tx_queue_cnt--;
		dw32(DCR1, 0x1);			/* Issue Tx polling */
		netअगर_trans_update(dev);		/* saved समय stamp */
	पूर्ण

	/* Resource available check */
	अगर ( db->tx_queue_cnt < TX_WAKE_DESC_CNT )
		netअगर_wake_queue(dev);	/* Active upper layer, send again */
पूर्ण


/*
 *	Calculate the CRC valude of the Rx packet
 *	flag = 	1 : वापस the reverse CRC (क्रम the received packet CRC)
 *		0 : वापस the normal CRC (क्रम Hash Table index)
 */

अटल अंतरभूत u32 cal_CRC(अचिन्हित अक्षर * Data, अचिन्हित पूर्णांक Len, u8 flag)
अणु
	u32 crc = crc32(~0, Data, Len);
	अगर (flag) crc = ~crc;
	वापस crc;
पूर्ण


/*
 *	Receive the come packet and pass to upper layer
 */

अटल व्योम dmfe_rx_packet(काष्ठा net_device *dev, काष्ठा dmfe_board_info *db)
अणु
	काष्ठा rx_desc *rxptr;
	काष्ठा sk_buff *skb, *newskb;
	पूर्णांक rxlen;
	u32 rdes0;

	rxptr = db->rx_पढ़ोy_ptr;

	जबतक(db->rx_avail_cnt) अणु
		rdes0 = le32_to_cpu(rxptr->rdes0);
		अगर (rdes0 & 0x80000000)	/* packet owner check */
			अवरोध;

		db->rx_avail_cnt--;
		db->पूर्णांकerval_rx_cnt++;

		dma_unmap_single(&db->pdev->dev, le32_to_cpu(rxptr->rdes2),
				 RX_ALLOC_SIZE, DMA_FROM_DEVICE);

		अगर ( (rdes0 & 0x300) != 0x300) अणु
			/* A packet without First/Last flag */
			/* reuse this SKB */
			DMFE_DBUG(0, "Reuse SK buffer, rdes0", rdes0);
			dmfe_reuse_skb(db, rxptr->rx_skb_ptr);
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
				skb = rxptr->rx_skb_ptr;

				/* Received Packet CRC check need or not */
				अगर ( (db->dm910x_chk_mode & 1) &&
					(cal_CRC(skb->data, rxlen, 1) !=
					(*(u32 *) (skb->data+rxlen) ))) अणु /* FIXME (?) */
					/* Found a error received packet */
					dmfe_reuse_skb(db, rxptr->rx_skb_ptr);
					db->dm910x_chk_mode = 3;
				पूर्ण अन्यथा अणु
					/* Good packet, send to upper layer */
					/* Shorst packet used new SKB */
					अगर ((rxlen < RX_COPY_SIZE) &&
						((newskb = netdev_alloc_skb(dev, rxlen + 2))
						!= शून्य)) अणु

						skb = newskb;
						/* size less than COPY_SIZE, allocate a rxlen SKB */
						skb_reserve(skb, 2); /* 16byte align */
						skb_copy_from_linear_data(rxptr->rx_skb_ptr,
							  skb_put(skb, rxlen),
									  rxlen);
						dmfe_reuse_skb(db, rxptr->rx_skb_ptr);
					पूर्ण अन्यथा
						skb_put(skb, rxlen);

					skb->protocol = eth_type_trans(skb, dev);
					netअगर_rx(skb);
					dev->stats.rx_packets++;
					dev->stats.rx_bytes += rxlen;
				पूर्ण
			पूर्ण अन्यथा अणु
				/* Reuse SKB buffer when the packet is error */
				DMFE_DBUG(0, "Reuse SK buffer, rdes0", rdes0);
				dmfe_reuse_skb(db, rxptr->rx_skb_ptr);
			पूर्ण
		पूर्ण

		rxptr = rxptr->next_rx_desc;
	पूर्ण

	db->rx_पढ़ोy_ptr = rxptr;
पूर्ण

/*
 * Set DM910X multicast address
 */

अटल व्योम dmfe_set_filter_mode(काष्ठा net_device *dev)
अणु
	काष्ठा dmfe_board_info *db = netdev_priv(dev);
	अचिन्हित दीर्घ flags;
	पूर्णांक mc_count = netdev_mc_count(dev);

	DMFE_DBUG(0, "dmfe_set_filter_mode()", 0);
	spin_lock_irqsave(&db->lock, flags);

	अगर (dev->flags & IFF_PROMISC) अणु
		DMFE_DBUG(0, "Enable PROM Mode", 0);
		db->cr6_data |= CR6_PM | CR6_PBF;
		update_cr6(db->cr6_data, db->ioaddr);
		spin_unlock_irqrestore(&db->lock, flags);
		वापस;
	पूर्ण

	अगर (dev->flags & IFF_ALLMULTI || mc_count > DMFE_MAX_MULTICAST) अणु
		DMFE_DBUG(0, "Pass all multicast address", mc_count);
		db->cr6_data &= ~(CR6_PM | CR6_PBF);
		db->cr6_data |= CR6_PAM;
		spin_unlock_irqrestore(&db->lock, flags);
		वापस;
	पूर्ण

	DMFE_DBUG(0, "Set multicast address", mc_count);
	अगर (db->chip_id == PCI_DM9132_ID)
		dm9132_id_table(dev);	/* DM9132 */
	अन्यथा
		send_filter_frame(dev);	/* DM9102/DM9102A */
	spin_unlock_irqrestore(&db->lock, flags);
पूर्ण

/*
 * 	Ethtool पूर्णांकerace
 */

अटल व्योम dmfe_ethtool_get_drvinfo(काष्ठा net_device *dev,
			       काष्ठा ethtool_drvinfo *info)
अणु
	काष्ठा dmfe_board_info *np = netdev_priv(dev);

	strlcpy(info->driver, DRV_NAME, माप(info->driver));
	strlcpy(info->bus_info, pci_name(np->pdev), माप(info->bus_info));
पूर्ण

अटल पूर्णांक dmfe_ethtool_set_wol(काष्ठा net_device *dev,
				काष्ठा ethtool_wolinfo *wolinfo)
अणु
	काष्ठा dmfe_board_info *db = netdev_priv(dev);

	अगर (wolinfo->wolopts & (WAKE_UCAST | WAKE_MCAST | WAKE_BCAST |
		   		WAKE_ARP | WAKE_MAGICSECURE))
		   वापस -EOPNOTSUPP;

	db->wol_mode = wolinfo->wolopts;
	वापस 0;
पूर्ण

अटल व्योम dmfe_ethtool_get_wol(काष्ठा net_device *dev,
				 काष्ठा ethtool_wolinfo *wolinfo)
अणु
	काष्ठा dmfe_board_info *db = netdev_priv(dev);

	wolinfo->supported = WAKE_PHY | WAKE_MAGIC;
	wolinfo->wolopts = db->wol_mode;
पूर्ण


अटल स्थिर काष्ठा ethtool_ops netdev_ethtool_ops = अणु
	.get_drvinfo		= dmfe_ethtool_get_drvinfo,
	.get_link               = ethtool_op_get_link,
	.set_wol		= dmfe_ethtool_set_wol,
	.get_wol		= dmfe_ethtool_get_wol,
पूर्ण;

/*
 *	A periodic समयr routine
 *	Dynamic media sense, allocate Rx buffer...
 */

अटल व्योम dmfe_समयr(काष्ठा समयr_list *t)
अणु
	काष्ठा dmfe_board_info *db = from_समयr(db, t, समयr);
	काष्ठा net_device *dev = pci_get_drvdata(db->pdev);
	व्योम __iomem *ioaddr = db->ioaddr;
	u32 पंचांगp_cr8;
	अचिन्हित अक्षर पंचांगp_cr12;
 	अचिन्हित दीर्घ flags;

	पूर्णांक link_ok, link_ok_phy;

	DMFE_DBUG(0, "dmfe_timer()", 0);
	spin_lock_irqsave(&db->lock, flags);

	/* Media mode process when Link OK beक्रमe enter this route */
	अगर (db->first_in_callback == 0) अणु
		db->first_in_callback = 1;
		अगर (db->chip_type && (db->chip_id==PCI_DM9102_ID)) अणु
			db->cr6_data &= ~0x40000;
			update_cr6(db->cr6_data, ioaddr);
			dmfe_phy_ग_लिखो(ioaddr, db->phy_addr, 0, 0x1000, db->chip_id);
			db->cr6_data |= 0x40000;
			update_cr6(db->cr6_data, ioaddr);
			db->समयr.expires = DMFE_TIMER_WUT + HZ * 2;
			add_समयr(&db->समयr);
			spin_unlock_irqrestore(&db->lock, flags);
			वापस;
		पूर्ण
	पूर्ण


	/* Operating Mode Check */
	अगर ( (db->dm910x_chk_mode & 0x1) &&
		(dev->stats.rx_packets > MAX_CHECK_PACKET) )
		db->dm910x_chk_mode = 0x4;

	/* Dynamic reset DM910X : प्रणाली error or transmit समय-out */
	पंचांगp_cr8 = dr32(DCR8);
	अगर ( (db->पूर्णांकerval_rx_cnt==0) && (पंचांगp_cr8) ) अणु
		db->reset_cr8++;
		db->रुको_reset = 1;
	पूर्ण
	db->पूर्णांकerval_rx_cnt = 0;

	/* TX polling kick monitor */
	अगर ( db->tx_packet_cnt &&
	     समय_after(jअगरfies, dev_trans_start(dev) + DMFE_TX_KICK) ) अणु
		dw32(DCR1, 0x1);   /* Tx polling again */

		/* TX Timeout */
		अगर (समय_after(jअगरfies, dev_trans_start(dev) + DMFE_TX_TIMEOUT) ) अणु
			db->reset_TXसमयout++;
			db->रुको_reset = 1;
			dev_warn(&dev->dev, "Tx timeout - resetting\n");
		पूर्ण
	पूर्ण

	अगर (db->रुको_reset) अणु
		DMFE_DBUG(0, "Dynamic Reset device", db->tx_packet_cnt);
		db->reset_count++;
		dmfe_dynamic_reset(dev);
		db->first_in_callback = 0;
		db->समयr.expires = DMFE_TIMER_WUT;
		add_समयr(&db->समयr);
		spin_unlock_irqrestore(&db->lock, flags);
		वापस;
	पूर्ण

	/* Link status check, Dynamic media type change */
	अगर (db->chip_id == PCI_DM9132_ID)
		पंचांगp_cr12 = dr8(DCR9 + 3);	/* DM9132 */
	अन्यथा
		पंचांगp_cr12 = dr8(DCR12);		/* DM9102/DM9102A */

	अगर ( ((db->chip_id == PCI_DM9102_ID) &&
		(db->chip_revision == 0x30)) ||
		((db->chip_id == PCI_DM9132_ID) &&
		(db->chip_revision == 0x10)) ) अणु
		/* DM9102A Chip */
		अगर (पंचांगp_cr12 & 2)
			link_ok = 0;
		अन्यथा
			link_ok = 1;
	पूर्ण
	अन्यथा
		/*0x43 is used instead of 0x3 because bit 6 should represent
			link status of बाह्यal PHY */
		link_ok = (पंचांगp_cr12 & 0x43) ? 1 : 0;


	/* If chip reports that link is failed it could be because बाह्यal
		PHY link status pin is not connected correctly to chip
		To be sure ask PHY too.
	*/

	/* need a dummy पढ़ो because of PHY's रेजिस्टर latch*/
	dmfe_phy_पढ़ो (db->ioaddr, db->phy_addr, 1, db->chip_id);
	link_ok_phy = (dmfe_phy_पढ़ो (db->ioaddr,
				      db->phy_addr, 1, db->chip_id) & 0x4) ? 1 : 0;

	अगर (link_ok_phy != link_ok) अणु
		DMFE_DBUG (0, "PHY and chip report different link status", 0);
		link_ok = link_ok | link_ok_phy;
 	पूर्ण

	अगर ( !link_ok && netअगर_carrier_ok(dev)) अणु
		/* Link Failed */
		DMFE_DBUG(0, "Link Failed", पंचांगp_cr12);
		netअगर_carrier_off(dev);

		/* For Force 10/100M Half/Full mode: Enable Auto-Nego mode */
		/* AUTO or क्रमce 1M Homerun/Longrun करोn't need */
		अगर ( !(db->media_mode & 0x38) )
			dmfe_phy_ग_लिखो(db->ioaddr, db->phy_addr,
				       0, 0x1000, db->chip_id);

		/* AUTO mode, अगर INT phyxcer link failed, select EXT device */
		अगर (db->media_mode & DMFE_AUTO) अणु
			/* 10/100M link failed, used 1M Home-Net */
			db->cr6_data|=0x00040000;	/* bit18=1, MII */
			db->cr6_data&=~0x00000200;	/* bit9=0, HD mode */
			update_cr6(db->cr6_data, ioaddr);
		पूर्ण
	पूर्ण अन्यथा अगर (!netअगर_carrier_ok(dev)) अणु

		DMFE_DBUG(0, "Link link OK", पंचांगp_cr12);

		/* Auto Sense Speed */
		अगर ( !(db->media_mode & DMFE_AUTO) || !dmfe_sense_speed(db)) अणु
			netअगर_carrier_on(dev);
			SHOW_MEDIA_TYPE(db->op_mode);
		पूर्ण

		dmfe_process_mode(db);
	पूर्ण

	/* HPNA remote command check */
	अगर (db->HPNA_command & 0xf00) अणु
		db->HPNA_समयr--;
		अगर (!db->HPNA_समयr)
			dmfe_HPNA_remote_cmd_chk(db);
	पूर्ण

	/* Timer active again */
	db->समयr.expires = DMFE_TIMER_WUT;
	add_समयr(&db->समयr);
	spin_unlock_irqrestore(&db->lock, flags);
पूर्ण


/*
 *	Dynamic reset the DM910X board
 *	Stop DM910X board
 *	Free Tx/Rx allocated memory
 *	Reset DM910X board
 *	Re-initialize DM910X board
 */

अटल व्योम dmfe_dynamic_reset(काष्ठा net_device *dev)
अणु
	काष्ठा dmfe_board_info *db = netdev_priv(dev);
	व्योम __iomem *ioaddr = db->ioaddr;

	DMFE_DBUG(0, "dmfe_dynamic_reset()", 0);

	/* Sopt MAC controller */
	db->cr6_data &= ~(CR6_RXSC | CR6_TXSC);	/* Disable Tx/Rx */
	update_cr6(db->cr6_data, ioaddr);
	dw32(DCR7, 0);				/* Disable Interrupt */
	dw32(DCR5, dr32(DCR5));

	/* Disable upper layer पूर्णांकerface */
	netअगर_stop_queue(dev);

	/* Free Rx Allocate buffer */
	dmfe_मुक्त_rxbuffer(db);

	/* प्रणाली variable init */
	db->tx_packet_cnt = 0;
	db->tx_queue_cnt = 0;
	db->rx_avail_cnt = 0;
	netअगर_carrier_off(dev);
	db->रुको_reset = 0;

	/* Re-initialize DM910X board */
	dmfe_init_dm910x(dev);

	/* Restart upper layer पूर्णांकerface */
	netअगर_wake_queue(dev);
पूर्ण


/*
 *	मुक्त all allocated rx buffer
 */

अटल व्योम dmfe_मुक्त_rxbuffer(काष्ठा dmfe_board_info * db)
अणु
	DMFE_DBUG(0, "dmfe_free_rxbuffer()", 0);

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

अटल व्योम dmfe_reuse_skb(काष्ठा dmfe_board_info *db, काष्ठा sk_buff * skb)
अणु
	काष्ठा rx_desc *rxptr = db->rx_insert_ptr;

	अगर (!(rxptr->rdes0 & cpu_to_le32(0x80000000))) अणु
		rxptr->rx_skb_ptr = skb;
		rxptr->rdes2 = cpu_to_le32(dma_map_single(&db->pdev->dev, skb->data,
							  RX_ALLOC_SIZE, DMA_FROM_DEVICE));
		wmb();
		rxptr->rdes0 = cpu_to_le32(0x80000000);
		db->rx_avail_cnt++;
		db->rx_insert_ptr = rxptr->next_rx_desc;
	पूर्ण अन्यथा
		DMFE_DBUG(0, "SK Buffer reuse method error", db->rx_avail_cnt);
पूर्ण


/*
 *	Initialize transmit/Receive descriptor
 *	Using Chain काष्ठाure, and allocate Tx/Rx buffer
 */

अटल व्योम dmfe_descriptor_init(काष्ठा net_device *dev)
अणु
	काष्ठा dmfe_board_info *db = netdev_priv(dev);
	व्योम __iomem *ioaddr = db->ioaddr;
	काष्ठा tx_desc *पंचांगp_tx;
	काष्ठा rx_desc *पंचांगp_rx;
	अचिन्हित अक्षर *पंचांगp_buf;
	dma_addr_t पंचांगp_tx_dma, पंचांगp_rx_dma;
	dma_addr_t पंचांगp_buf_dma;
	पूर्णांक i;

	DMFE_DBUG(0, "dmfe_descriptor_init()", 0);

	/* tx descriptor start poपूर्णांकer */
	db->tx_insert_ptr = db->first_tx_desc;
	db->tx_हटाओ_ptr = db->first_tx_desc;
	dw32(DCR4, db->first_tx_desc_dma);     /* TX DESC address */

	/* rx descriptor start poपूर्णांकer */
	db->first_rx_desc = (व्योम *)db->first_tx_desc +
			माप(काष्ठा tx_desc) * TX_DESC_CNT;

	db->first_rx_desc_dma =  db->first_tx_desc_dma +
			माप(काष्ठा tx_desc) * TX_DESC_CNT;
	db->rx_insert_ptr = db->first_rx_desc;
	db->rx_पढ़ोy_ptr = db->first_rx_desc;
	dw32(DCR3, db->first_rx_desc_dma);		/* RX DESC address */

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
 *	Firstly stop DM910X , then written value and start
 */

अटल व्योम update_cr6(u32 cr6_data, व्योम __iomem *ioaddr)
अणु
	u32 cr6_पंचांगp;

	cr6_पंचांगp = cr6_data & ~0x2002;           /* stop Tx/Rx */
	dw32(DCR6, cr6_पंचांगp);
	udelay(5);
	dw32(DCR6, cr6_data);
	udelay(5);
पूर्ण


/*
 *	Send a setup frame क्रम DM9132
 *	This setup frame initialize DM910X address filter mode
*/

अटल व्योम dm9132_id_table(काष्ठा net_device *dev)
अणु
	काष्ठा dmfe_board_info *db = netdev_priv(dev);
	व्योम __iomem *ioaddr = db->ioaddr + 0xc0;
	u16 *addrptr = (u16 *)dev->dev_addr;
	काष्ठा netdev_hw_addr *ha;
	u16 i, hash_table[4];

	/* Node address */
	क्रम (i = 0; i < 3; i++) अणु
		dw16(0, addrptr[i]);
		ioaddr += 4;
	पूर्ण

	/* Clear Hash Table */
	स_रखो(hash_table, 0, माप(hash_table));

	/* broadcast address */
	hash_table[3] = 0x8000;

	/* the multicast address in Hash Table : 64 bits */
	netdev_क्रम_each_mc_addr(ha, dev) अणु
		u32 hash_val = cal_CRC((अक्षर *)ha->addr, 6, 0) & 0x3f;

		hash_table[hash_val / 16] |= (u16) 1 << (hash_val % 16);
	पूर्ण

	/* Write the hash table to MAC MD table */
	क्रम (i = 0; i < 4; i++, ioaddr += 4)
		dw16(0, hash_table[i]);
पूर्ण


/*
 *	Send a setup frame क्रम DM9102/DM9102A
 *	This setup frame initialize DM910X address filter mode
 */

अटल व्योम send_filter_frame(काष्ठा net_device *dev)
अणु
	काष्ठा dmfe_board_info *db = netdev_priv(dev);
	काष्ठा netdev_hw_addr *ha;
	काष्ठा tx_desc *txptr;
	u16 * addrptr;
	u32 * suptr;
	पूर्णांक i;

	DMFE_DBUG(0, "send_filter_frame()", 0);

	txptr = db->tx_insert_ptr;
	suptr = (u32 *) txptr->tx_buf_ptr;

	/* Node address */
	addrptr = (u16 *) dev->dev_addr;
	*suptr++ = addrptr[0];
	*suptr++ = addrptr[1];
	*suptr++ = addrptr[2];

	/* broadcast address */
	*suptr++ = 0xffff;
	*suptr++ = 0xffff;
	*suptr++ = 0xffff;

	/* fit the multicast address */
	netdev_क्रम_each_mc_addr(ha, dev) अणु
		addrptr = (u16 *) ha->addr;
		*suptr++ = addrptr[0];
		*suptr++ = addrptr[1];
		*suptr++ = addrptr[2];
	पूर्ण

	क्रम (i = netdev_mc_count(dev); i < 14; i++) अणु
		*suptr++ = 0xffff;
		*suptr++ = 0xffff;
		*suptr++ = 0xffff;
	पूर्ण

	/* prepare the setup frame */
	db->tx_insert_ptr = txptr->next_tx_desc;
	txptr->tdes1 = cpu_to_le32(0x890000c0);

	/* Resource Check and Send the setup packet */
	अगर (!db->tx_packet_cnt) अणु
		व्योम __iomem *ioaddr = db->ioaddr;

		/* Resource Empty */
		db->tx_packet_cnt++;
		txptr->tdes0 = cpu_to_le32(0x80000000);
		update_cr6(db->cr6_data | 0x2000, ioaddr);
		dw32(DCR1, 0x1);	/* Issue Tx polling */
		update_cr6(db->cr6_data, ioaddr);
		netअगर_trans_update(dev);
	पूर्ण अन्यथा
		db->tx_queue_cnt++;	/* Put in TX queue */
पूर्ण


/*
 *	Allocate rx buffer,
 *	As possible as allocate maxiumn Rx buffer
 */

अटल व्योम allocate_rx_buffer(काष्ठा net_device *dev)
अणु
	काष्ठा dmfe_board_info *db = netdev_priv(dev);
	काष्ठा rx_desc *rxptr;
	काष्ठा sk_buff *skb;

	rxptr = db->rx_insert_ptr;

	जबतक(db->rx_avail_cnt < RX_DESC_CNT) अणु
		अगर ( ( skb = netdev_alloc_skb(dev, RX_ALLOC_SIZE) ) == शून्य )
			अवरोध;
		rxptr->rx_skb_ptr = skb; /* FIXME (?) */
		rxptr->rdes2 = cpu_to_le32(dma_map_single(&db->pdev->dev, skb->data,
							  RX_ALLOC_SIZE, DMA_FROM_DEVICE));
		wmb();
		rxptr->rdes0 = cpu_to_le32(0x80000000);
		rxptr = rxptr->next_rx_desc;
		db->rx_avail_cnt++;
	पूर्ण

	db->rx_insert_ptr = rxptr;
पूर्ण

अटल व्योम srom_clk_ग_लिखो(व्योम __iomem *ioaddr, u32 data)
अणु
	अटल स्थिर u32 cmd[] = अणु
		CR9_SROM_READ | CR9_SRCS,
		CR9_SROM_READ | CR9_SRCS | CR9_SRCLK,
		CR9_SROM_READ | CR9_SRCS
	पूर्ण;
	पूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(cmd); i++) अणु
		dw32(DCR9, data | cmd[i]);
		udelay(5);
	पूर्ण
पूर्ण

/*
 *	Read one word data from the serial ROM
 */
अटल u16 पढ़ो_srom_word(व्योम __iomem *ioaddr, पूर्णांक offset)
अणु
	u16 srom_data;
	पूर्णांक i;

	dw32(DCR9, CR9_SROM_READ);
	udelay(5);
	dw32(DCR9, CR9_SROM_READ | CR9_SRCS);
	udelay(5);

	/* Send the Read Command 110b */
	srom_clk_ग_लिखो(ioaddr, SROM_DATA_1);
	srom_clk_ग_लिखो(ioaddr, SROM_DATA_1);
	srom_clk_ग_लिखो(ioaddr, SROM_DATA_0);

	/* Send the offset */
	क्रम (i = 5; i >= 0; i--) अणु
		srom_data = (offset & (1 << i)) ? SROM_DATA_1 : SROM_DATA_0;
		srom_clk_ग_लिखो(ioaddr, srom_data);
	पूर्ण

	dw32(DCR9, CR9_SROM_READ | CR9_SRCS);
	udelay(5);

	क्रम (i = 16; i > 0; i--) अणु
		dw32(DCR9, CR9_SROM_READ | CR9_SRCS | CR9_SRCLK);
		udelay(5);
		srom_data = (srom_data << 1) |
				((dr32(DCR9) & CR9_CRDOUT) ? 1 : 0);
		dw32(DCR9, CR9_SROM_READ | CR9_SRCS);
		udelay(5);
	पूर्ण

	dw32(DCR9, CR9_SROM_READ);
	udelay(5);
	वापस srom_data;
पूर्ण


/*
 *	Auto sense the media mode
 */

अटल u8 dmfe_sense_speed(काष्ठा dmfe_board_info *db)
अणु
	व्योम __iomem *ioaddr = db->ioaddr;
	u8 ErrFlag = 0;
	u16 phy_mode;

	/* CR6 bit18=0, select 10/100M */
	update_cr6(db->cr6_data & ~0x40000, ioaddr);

	phy_mode = dmfe_phy_पढ़ो(db->ioaddr, db->phy_addr, 1, db->chip_id);
	phy_mode = dmfe_phy_पढ़ो(db->ioaddr, db->phy_addr, 1, db->chip_id);

	अगर ( (phy_mode & 0x24) == 0x24 ) अणु
		अगर (db->chip_id == PCI_DM9132_ID)	/* DM9132 */
			phy_mode = dmfe_phy_पढ़ो(db->ioaddr,
						 db->phy_addr, 7, db->chip_id) & 0xf000;
		अन्यथा 				/* DM9102/DM9102A */
			phy_mode = dmfe_phy_पढ़ो(db->ioaddr,
						 db->phy_addr, 17, db->chip_id) & 0xf000;
		चयन (phy_mode) अणु
		हाल 0x1000: db->op_mode = DMFE_10MHF; अवरोध;
		हाल 0x2000: db->op_mode = DMFE_10MFD; अवरोध;
		हाल 0x4000: db->op_mode = DMFE_100MHF; अवरोध;
		हाल 0x8000: db->op_mode = DMFE_100MFD; अवरोध;
		शेष: db->op_mode = DMFE_10MHF;
			ErrFlag = 1;
			अवरोध;
		पूर्ण
	पूर्ण अन्यथा अणु
		db->op_mode = DMFE_10MHF;
		DMFE_DBUG(0, "Link Failed :", phy_mode);
		ErrFlag = 1;
	पूर्ण

	वापस ErrFlag;
पूर्ण


/*
 *	Set 10/100 phyxcer capability
 *	AUTO mode : phyxcer रेजिस्टर4 is NIC capability
 *	Force mode: phyxcer रेजिस्टर4 is the क्रमce media
 */

अटल व्योम dmfe_set_phyxcer(काष्ठा dmfe_board_info *db)
अणु
	व्योम __iomem *ioaddr = db->ioaddr;
	u16 phy_reg;

	/* Select 10/100M phyxcer */
	db->cr6_data &= ~0x40000;
	update_cr6(db->cr6_data, ioaddr);

	/* DM9009 Chip: Phyxcer reg18 bit12=0 */
	अगर (db->chip_id == PCI_DM9009_ID) अणु
		phy_reg = dmfe_phy_पढ़ो(db->ioaddr,
					db->phy_addr, 18, db->chip_id) & ~0x1000;

		dmfe_phy_ग_लिखो(db->ioaddr,
			       db->phy_addr, 18, phy_reg, db->chip_id);
	पूर्ण

	/* Phyxcer capability setting */
	phy_reg = dmfe_phy_पढ़ो(db->ioaddr, db->phy_addr, 4, db->chip_id) & ~0x01e0;

	अगर (db->media_mode & DMFE_AUTO) अणु
		/* AUTO Mode */
		phy_reg |= db->PHY_reg4;
	पूर्ण अन्यथा अणु
		/* Force Mode */
		चयन(db->media_mode) अणु
		हाल DMFE_10MHF: phy_reg |= 0x20; अवरोध;
		हाल DMFE_10MFD: phy_reg |= 0x40; अवरोध;
		हाल DMFE_100MHF: phy_reg |= 0x80; अवरोध;
		हाल DMFE_100MFD: phy_reg |= 0x100; अवरोध;
		पूर्ण
		अगर (db->chip_id == PCI_DM9009_ID) phy_reg &= 0x61;
	पूर्ण

  	/* Write new capability to Phyxcer Reg4 */
	अगर ( !(phy_reg & 0x01e0)) अणु
		phy_reg|=db->PHY_reg4;
		db->media_mode|=DMFE_AUTO;
	पूर्ण
	dmfe_phy_ग_लिखो(db->ioaddr, db->phy_addr, 4, phy_reg, db->chip_id);

 	/* Restart Auto-Negotiation */
	अगर ( db->chip_type && (db->chip_id == PCI_DM9102_ID) )
		dmfe_phy_ग_लिखो(db->ioaddr, db->phy_addr, 0, 0x1800, db->chip_id);
	अगर ( !db->chip_type )
		dmfe_phy_ग_लिखो(db->ioaddr, db->phy_addr, 0, 0x1200, db->chip_id);
पूर्ण


/*
 *	Process op-mode
 *	AUTO mode : PHY controller in Auto-negotiation Mode
 *	Force mode: PHY controller in क्रमce mode with HUB
 *			N-way क्रमce capability with SWITCH
 */

अटल व्योम dmfe_process_mode(काष्ठा dmfe_board_info *db)
अणु
	u16 phy_reg;

	/* Full Duplex Mode Check */
	अगर (db->op_mode & 0x4)
		db->cr6_data |= CR6_FDM;	/* Set Full Duplex Bit */
	अन्यथा
		db->cr6_data &= ~CR6_FDM;	/* Clear Full Duplex Bit */

	/* Transciver Selection */
	अगर (db->op_mode & 0x10)		/* 1M HomePNA */
		db->cr6_data |= 0x40000;/* External MII select */
	अन्यथा
		db->cr6_data &= ~0x40000;/* Internal 10/100 transciver */

	update_cr6(db->cr6_data, db->ioaddr);

	/* 10/100M phyxcer क्रमce mode need */
	अगर ( !(db->media_mode & 0x18)) अणु
		/* Forece Mode */
		phy_reg = dmfe_phy_पढ़ो(db->ioaddr, db->phy_addr, 6, db->chip_id);
		अगर ( !(phy_reg & 0x1) ) अणु
			/* parter without N-Way capability */
			phy_reg = 0x0;
			चयन(db->op_mode) अणु
			हाल DMFE_10MHF: phy_reg = 0x0; अवरोध;
			हाल DMFE_10MFD: phy_reg = 0x100; अवरोध;
			हाल DMFE_100MHF: phy_reg = 0x2000; अवरोध;
			हाल DMFE_100MFD: phy_reg = 0x2100; अवरोध;
			पूर्ण
			dmfe_phy_ग_लिखो(db->ioaddr,
				       db->phy_addr, 0, phy_reg, db->chip_id);
       			अगर ( db->chip_type && (db->chip_id == PCI_DM9102_ID) )
				mdelay(20);
			dmfe_phy_ग_लिखो(db->ioaddr,
				       db->phy_addr, 0, phy_reg, db->chip_id);
		पूर्ण
	पूर्ण
पूर्ण


/*
 *	Write a word to Phy रेजिस्टर
 */

अटल व्योम dmfe_phy_ग_लिखो(व्योम __iomem *ioaddr, u8 phy_addr, u8 offset,
			   u16 phy_data, u32 chip_id)
अणु
	u16 i;

	अगर (chip_id == PCI_DM9132_ID) अणु
		dw16(0x80 + offset * 4, phy_data);
	पूर्ण अन्यथा अणु
		/* DM9102/DM9102A Chip */

		/* Send 33 synchronization घड़ी to Phy controller */
		क्रम (i = 0; i < 35; i++)
			dmfe_phy_ग_लिखो_1bit(ioaddr, PHY_DATA_1);

		/* Send start command(01) to Phy */
		dmfe_phy_ग_लिखो_1bit(ioaddr, PHY_DATA_0);
		dmfe_phy_ग_लिखो_1bit(ioaddr, PHY_DATA_1);

		/* Send ग_लिखो command(01) to Phy */
		dmfe_phy_ग_लिखो_1bit(ioaddr, PHY_DATA_0);
		dmfe_phy_ग_लिखो_1bit(ioaddr, PHY_DATA_1);

		/* Send Phy address */
		क्रम (i = 0x10; i > 0; i = i >> 1)
			dmfe_phy_ग_लिखो_1bit(ioaddr,
					    phy_addr & i ? PHY_DATA_1 : PHY_DATA_0);

		/* Send रेजिस्टर address */
		क्रम (i = 0x10; i > 0; i = i >> 1)
			dmfe_phy_ग_लिखो_1bit(ioaddr,
					    offset & i ? PHY_DATA_1 : PHY_DATA_0);

		/* written trasnition */
		dmfe_phy_ग_लिखो_1bit(ioaddr, PHY_DATA_1);
		dmfe_phy_ग_लिखो_1bit(ioaddr, PHY_DATA_0);

		/* Write a word data to PHY controller */
		क्रम ( i = 0x8000; i > 0; i >>= 1)
			dmfe_phy_ग_लिखो_1bit(ioaddr,
					    phy_data & i ? PHY_DATA_1 : PHY_DATA_0);
	पूर्ण
पूर्ण


/*
 *	Read a word data from phy रेजिस्टर
 */

अटल u16 dmfe_phy_पढ़ो(व्योम __iomem *ioaddr, u8 phy_addr, u8 offset, u32 chip_id)
अणु
	पूर्णांक i;
	u16 phy_data;

	अगर (chip_id == PCI_DM9132_ID) अणु
		/* DM9132 Chip */
		phy_data = dr16(0x80 + offset * 4);
	पूर्ण अन्यथा अणु
		/* DM9102/DM9102A Chip */

		/* Send 33 synchronization घड़ी to Phy controller */
		क्रम (i = 0; i < 35; i++)
			dmfe_phy_ग_लिखो_1bit(ioaddr, PHY_DATA_1);

		/* Send start command(01) to Phy */
		dmfe_phy_ग_लिखो_1bit(ioaddr, PHY_DATA_0);
		dmfe_phy_ग_लिखो_1bit(ioaddr, PHY_DATA_1);

		/* Send पढ़ो command(10) to Phy */
		dmfe_phy_ग_लिखो_1bit(ioaddr, PHY_DATA_1);
		dmfe_phy_ग_लिखो_1bit(ioaddr, PHY_DATA_0);

		/* Send Phy address */
		क्रम (i = 0x10; i > 0; i = i >> 1)
			dmfe_phy_ग_लिखो_1bit(ioaddr,
					    phy_addr & i ? PHY_DATA_1 : PHY_DATA_0);

		/* Send रेजिस्टर address */
		क्रम (i = 0x10; i > 0; i = i >> 1)
			dmfe_phy_ग_लिखो_1bit(ioaddr,
					    offset & i ? PHY_DATA_1 : PHY_DATA_0);

		/* Skip transition state */
		dmfe_phy_पढ़ो_1bit(ioaddr);

		/* पढ़ो 16bit data */
		क्रम (phy_data = 0, i = 0; i < 16; i++) अणु
			phy_data <<= 1;
			phy_data |= dmfe_phy_पढ़ो_1bit(ioaddr);
		पूर्ण
	पूर्ण

	वापस phy_data;
पूर्ण


/*
 *	Write one bit data to Phy Controller
 */

अटल व्योम dmfe_phy_ग_लिखो_1bit(व्योम __iomem *ioaddr, u32 phy_data)
अणु
	dw32(DCR9, phy_data);		/* MII Clock Low */
	udelay(1);
	dw32(DCR9, phy_data | MDCLKH);	/* MII Clock High */
	udelay(1);
	dw32(DCR9, phy_data);		/* MII Clock Low */
	udelay(1);
पूर्ण


/*
 *	Read one bit phy data from PHY controller
 */

अटल u16 dmfe_phy_पढ़ो_1bit(व्योम __iomem *ioaddr)
अणु
	u16 phy_data;

	dw32(DCR9, 0x50000);
	udelay(1);
	phy_data = (dr32(DCR9) >> 19) & 0x1;
	dw32(DCR9, 0x40000);
	udelay(1);

	वापस phy_data;
पूर्ण


/*
 *	Parser SROM and media mode
 */

अटल व्योम dmfe_parse_srom(काष्ठा dmfe_board_info * db)
अणु
	अक्षर * srom = db->srom;
	पूर्णांक dmfe_mode, पंचांगp_reg;

	DMFE_DBUG(0, "dmfe_parse_srom() ", 0);

	/* Init CR15 */
	db->cr15_data = CR15_DEFAULT;

	/* Check SROM Version */
	अगर ( ( (पूर्णांक) srom[18] & 0xff) == SROM_V41_CODE) अणु
		/* SROM V4.01 */
		/* Get NIC support media mode */
		db->NIC_capability = le16_to_cpup((__le16 *) (srom + 34));
		db->PHY_reg4 = 0;
		क्रम (पंचांगp_reg = 1; पंचांगp_reg < 0x10; पंचांगp_reg <<= 1) अणु
			चयन( db->NIC_capability & पंचांगp_reg ) अणु
			हाल 0x1: db->PHY_reg4 |= 0x0020; अवरोध;
			हाल 0x2: db->PHY_reg4 |= 0x0040; अवरोध;
			हाल 0x4: db->PHY_reg4 |= 0x0080; अवरोध;
			हाल 0x8: db->PHY_reg4 |= 0x0100; अवरोध;
			पूर्ण
		पूर्ण

		/* Media Mode Force or not check */
		dmfe_mode = (le32_to_cpup((__le32 *) (srom + 34)) &
			     le32_to_cpup((__le32 *) (srom + 36)));
		चयन(dmfe_mode) अणु
		हाल 0x4: dmfe_media_mode = DMFE_100MHF; अवरोध;	/* 100MHF */
		हाल 0x2: dmfe_media_mode = DMFE_10MFD; अवरोध;	/* 10MFD */
		हाल 0x8: dmfe_media_mode = DMFE_100MFD; अवरोध;	/* 100MFD */
		हाल 0x100:
		हाल 0x200: dmfe_media_mode = DMFE_1M_HPNA; अवरोध;/* HomePNA */
		पूर्ण

		/* Special Function setting */
		/* VLAN function */
		अगर ( (SF_mode & 0x1) || (srom[43] & 0x80) )
			db->cr15_data |= 0x40;

		/* Flow Control */
		अगर ( (SF_mode & 0x2) || (srom[40] & 0x1) )
			db->cr15_data |= 0x400;

		/* TX छोड़ो packet */
		अगर ( (SF_mode & 0x4) || (srom[40] & 0xe) )
			db->cr15_data |= 0x9800;
	पूर्ण

	/* Parse HPNA parameter */
	db->HPNA_command = 1;

	/* Accept remote command or not */
	अगर (HPNA_rx_cmd == 0)
		db->HPNA_command |= 0x8000;

	 /* Issue remote command & operation mode */
	अगर (HPNA_tx_cmd == 1)
		चयन(HPNA_mode) अणु	/* Issue Remote Command */
		हाल 0: db->HPNA_command |= 0x0904; अवरोध;
		हाल 1: db->HPNA_command |= 0x0a00; अवरोध;
		हाल 2: db->HPNA_command |= 0x0506; अवरोध;
		हाल 3: db->HPNA_command |= 0x0602; अवरोध;
		पूर्ण
	अन्यथा
		चयन(HPNA_mode) अणु	/* Don't Issue */
		हाल 0: db->HPNA_command |= 0x0004; अवरोध;
		हाल 1: db->HPNA_command |= 0x0000; अवरोध;
		हाल 2: db->HPNA_command |= 0x0006; अवरोध;
		हाल 3: db->HPNA_command |= 0x0002; अवरोध;
		पूर्ण

	/* Check DM9801 or DM9802 present or not */
	db->HPNA_present = 0;
	update_cr6(db->cr6_data | 0x40000, db->ioaddr);
	पंचांगp_reg = dmfe_phy_पढ़ो(db->ioaddr, db->phy_addr, 3, db->chip_id);
	अगर ( ( पंचांगp_reg & 0xfff0 ) == 0xb900 ) अणु
		/* DM9801 or DM9802 present */
		db->HPNA_समयr = 8;
		अगर ( dmfe_phy_पढ़ो(db->ioaddr, db->phy_addr, 31, db->chip_id) == 0x4404) अणु
			/* DM9801 HomeRun */
			db->HPNA_present = 1;
			dmfe_program_DM9801(db, पंचांगp_reg);
		पूर्ण अन्यथा अणु
			/* DM9802 LongRun */
			db->HPNA_present = 2;
			dmfe_program_DM9802(db);
		पूर्ण
	पूर्ण

पूर्ण


/*
 *	Init HomeRun DM9801
 */

अटल व्योम dmfe_program_DM9801(काष्ठा dmfe_board_info * db, पूर्णांक HPNA_rev)
अणु
	uपूर्णांक reg17, reg25;

	अगर ( !HPNA_NoiseFloor ) HPNA_NoiseFloor = DM9801_NOISE_FLOOR;
	चयन(HPNA_rev) अणु
	हाल 0xb900: /* DM9801 E3 */
		db->HPNA_command |= 0x1000;
		reg25 = dmfe_phy_पढ़ो(db->ioaddr, db->phy_addr, 24, db->chip_id);
		reg25 = ( (reg25 + HPNA_NoiseFloor) & 0xff) | 0xf000;
		reg17 = dmfe_phy_पढ़ो(db->ioaddr, db->phy_addr, 17, db->chip_id);
		अवरोध;
	हाल 0xb901: /* DM9801 E4 */
		reg25 = dmfe_phy_पढ़ो(db->ioaddr, db->phy_addr, 25, db->chip_id);
		reg25 = (reg25 & 0xff00) + HPNA_NoiseFloor;
		reg17 = dmfe_phy_पढ़ो(db->ioaddr, db->phy_addr, 17, db->chip_id);
		reg17 = (reg17 & 0xfff0) + HPNA_NoiseFloor + 3;
		अवरोध;
	हाल 0xb902: /* DM9801 E5 */
	हाल 0xb903: /* DM9801 E6 */
	शेष:
		db->HPNA_command |= 0x1000;
		reg25 = dmfe_phy_पढ़ो(db->ioaddr, db->phy_addr, 25, db->chip_id);
		reg25 = (reg25 & 0xff00) + HPNA_NoiseFloor - 5;
		reg17 = dmfe_phy_पढ़ो(db->ioaddr, db->phy_addr, 17, db->chip_id);
		reg17 = (reg17 & 0xfff0) + HPNA_NoiseFloor;
		अवरोध;
	पूर्ण
	dmfe_phy_ग_लिखो(db->ioaddr, db->phy_addr, 16, db->HPNA_command, db->chip_id);
	dmfe_phy_ग_लिखो(db->ioaddr, db->phy_addr, 17, reg17, db->chip_id);
	dmfe_phy_ग_लिखो(db->ioaddr, db->phy_addr, 25, reg25, db->chip_id);
पूर्ण


/*
 *	Init HomeRun DM9802
 */

अटल व्योम dmfe_program_DM9802(काष्ठा dmfe_board_info * db)
अणु
	uपूर्णांक phy_reg;

	अगर ( !HPNA_NoiseFloor ) HPNA_NoiseFloor = DM9802_NOISE_FLOOR;
	dmfe_phy_ग_लिखो(db->ioaddr, db->phy_addr, 16, db->HPNA_command, db->chip_id);
	phy_reg = dmfe_phy_पढ़ो(db->ioaddr, db->phy_addr, 25, db->chip_id);
	phy_reg = ( phy_reg & 0xff00) + HPNA_NoiseFloor;
	dmfe_phy_ग_लिखो(db->ioaddr, db->phy_addr, 25, phy_reg, db->chip_id);
पूर्ण


/*
 *	Check remote HPNA घातer and speed status. If not correct,
 *	issue command again.
*/

अटल व्योम dmfe_HPNA_remote_cmd_chk(काष्ठा dmfe_board_info * db)
अणु
	uपूर्णांक phy_reg;

	/* Got remote device status */
	phy_reg = dmfe_phy_पढ़ो(db->ioaddr, db->phy_addr, 17, db->chip_id) & 0x60;
	चयन(phy_reg) अणु
	हाल 0x00: phy_reg = 0x0a00;अवरोध; /* LP/LS */
	हाल 0x20: phy_reg = 0x0900;अवरोध; /* LP/HS */
	हाल 0x40: phy_reg = 0x0600;अवरोध; /* HP/LS */
	हाल 0x60: phy_reg = 0x0500;अवरोध; /* HP/HS */
	पूर्ण

	/* Check remote device status match our setting ot not */
	अगर ( phy_reg != (db->HPNA_command & 0x0f00) ) अणु
		dmfe_phy_ग_लिखो(db->ioaddr, db->phy_addr, 16, db->HPNA_command,
			       db->chip_id);
		db->HPNA_समयr=8;
	पूर्ण अन्यथा
		db->HPNA_समयr=600;	/* Match, every 10 minutes, check */
पूर्ण



अटल स्थिर काष्ठा pci_device_id dmfe_pci_tbl[] = अणु
	अणु 0x1282, 0x9132, PCI_ANY_ID, PCI_ANY_ID, 0, 0, PCI_DM9132_ID पूर्ण,
	अणु 0x1282, 0x9102, PCI_ANY_ID, PCI_ANY_ID, 0, 0, PCI_DM9102_ID पूर्ण,
	अणु 0x1282, 0x9100, PCI_ANY_ID, PCI_ANY_ID, 0, 0, PCI_DM9100_ID पूर्ण,
	अणु 0x1282, 0x9009, PCI_ANY_ID, PCI_ANY_ID, 0, 0, PCI_DM9009_ID पूर्ण,
	अणु 0, पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(pci, dmfe_pci_tbl);

अटल पूर्णांक __maybe_unused dmfe_suspend(काष्ठा device *dev_d)
अणु
	काष्ठा net_device *dev = dev_get_drvdata(dev_d);
	काष्ठा dmfe_board_info *db = netdev_priv(dev);
	व्योम __iomem *ioaddr = db->ioaddr;

	/* Disable upper layer पूर्णांकerface */
	netअगर_device_detach(dev);

	/* Disable Tx/Rx */
	db->cr6_data &= ~(CR6_RXSC | CR6_TXSC);
	update_cr6(db->cr6_data, ioaddr);

	/* Disable Interrupt */
	dw32(DCR7, 0);
	dw32(DCR5, dr32(DCR5));

	/* Fre RX buffers */
	dmfe_मुक्त_rxbuffer(db);

	/* Enable WOL */
	device_wakeup_enable(dev_d);

	वापस 0;
पूर्ण

अटल पूर्णांक __maybe_unused dmfe_resume(काष्ठा device *dev_d)
अणु
	काष्ठा net_device *dev = dev_get_drvdata(dev_d);

	/* Re-initialize DM910X board */
	dmfe_init_dm910x(dev);

	/* Disable WOL */
	device_wakeup_disable(dev_d);

	/* Restart upper layer पूर्णांकerface */
	netअगर_device_attach(dev);

	वापस 0;
पूर्ण

अटल SIMPLE_DEV_PM_OPS(dmfe_pm_ops, dmfe_suspend, dmfe_resume);

अटल काष्ठा pci_driver dmfe_driver = अणु
	.name		= "dmfe",
	.id_table	= dmfe_pci_tbl,
	.probe		= dmfe_init_one,
	.हटाओ		= dmfe_हटाओ_one,
	.driver.pm	= &dmfe_pm_ops,
पूर्ण;

MODULE_AUTHOR("Sten Wang, sten_wang@davicom.com.tw");
MODULE_DESCRIPTION("Davicom DM910X fast ethernet driver");
MODULE_LICENSE("GPL");

module_param(debug, पूर्णांक, 0);
module_param(mode, byte, 0);
module_param(cr6set, पूर्णांक, 0);
module_param(chkmode, byte, 0);
module_param(HPNA_mode, byte, 0);
module_param(HPNA_rx_cmd, byte, 0);
module_param(HPNA_tx_cmd, byte, 0);
module_param(HPNA_NoiseFloor, byte, 0);
module_param(SF_mode, byte, 0);
MODULE_PARM_DESC(debug, "Davicom DM9xxx enable debugging (0-1)");
MODULE_PARM_DESC(mode, "Davicom DM9xxx: "
		"Bit 0: 10/100Mbps, bit 2: duplex, bit 8: HomePNA");

MODULE_PARM_DESC(SF_mode, "Davicom DM9xxx special function "
		"(bit 0: VLAN, bit 1 Flow Control, bit 2: TX pause packet)");

/*	Description:
 *	when user used insmod to add module, प्रणाली invoked init_module()
 *	to initialize and रेजिस्टर.
 */

अटल पूर्णांक __init dmfe_init_module(व्योम)
अणु
	पूर्णांक rc;

	DMFE_DBUG(0, "init_module() ", debug);

	अगर (debug)
		dmfe_debug = debug;	/* set debug flag */
	अगर (cr6set)
		dmfe_cr6_user_set = cr6set;

	चयन (mode) अणु
	हाल DMFE_10MHF:
	हाल DMFE_100MHF:
	हाल DMFE_10MFD:
	हाल DMFE_100MFD:
	हाल DMFE_1M_HPNA:
		dmfe_media_mode = mode;
		अवरोध;
	शेष:
		dmfe_media_mode = DMFE_AUTO;
		अवरोध;
	पूर्ण

	अगर (HPNA_mode > 4)
		HPNA_mode = 0;		/* Default: LP/HS */
	अगर (HPNA_rx_cmd > 1)
		HPNA_rx_cmd = 0;	/* Default: Ignored remote cmd */
	अगर (HPNA_tx_cmd > 1)
		HPNA_tx_cmd = 0;	/* Default: Don't issue remote cmd */
	अगर (HPNA_NoiseFloor > 15)
		HPNA_NoiseFloor = 0;

	rc = pci_रेजिस्टर_driver(&dmfe_driver);
	अगर (rc < 0)
		वापस rc;

	वापस 0;
पूर्ण


/*
 *	Description:
 *	when user used rmmod to delete module, प्रणाली invoked clean_module()
 *	to un-रेजिस्टर all रेजिस्टरed services.
 */

अटल व्योम __निकास dmfe_cleanup_module(व्योम)
अणु
	DMFE_DBUG(0, "dmfe_cleanup_module() ", debug);
	pci_unरेजिस्टर_driver(&dmfe_driver);
पूर्ण

module_init(dmfe_init_module);
module_निकास(dmfe_cleanup_module);
