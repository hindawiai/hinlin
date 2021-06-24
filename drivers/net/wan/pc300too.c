<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Cyclades PC300 synchronous serial card driver क्रम Linux
 *
 * Copyright (C) 2000-2008 Krzysztof Halasa <khc@pm.waw.pl>
 *
 * For inक्रमmation see <https://www.kernel.org/pub/linux/utils/net/hdlc/>.
 *
 * Sources of inक्रमmation:
 *    Hitachi HD64572 SCA-II User's Manual
 *    Original Cyclades PC300 Linux driver
 *
 * This driver currently supports only PC300/RSV (V.24/V.35) and
 * PC300/X21 cards.
 */

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#समावेश <linux/module.h>
#समावेश <linux/kernel.h>
#समावेश <linux/slab.h>
#समावेश <linux/sched.h>
#समावेश <linux/types.h>
#समावेश <linux/fcntl.h>
#समावेश <linux/in.h>
#समावेश <linux/माला.स>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/init.h>
#समावेश <linux/ioport.h>
#समावेश <linux/moduleparam.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/hdlc.h>
#समावेश <linux/pci.h>
#समावेश <linux/delay.h>
#समावेश <यंत्र/पन.स>

#समावेश "hd64572.h"

#अघोषित DEBUG_PKT
#घोषणा DEBUG_RINGS

#घोषणा PC300_PLX_SIZE		0x80    /* PLX control winकरोw size (128 B) */
#घोषणा PC300_SCA_SIZE		0x400   /* SCA winकरोw size (1 KB) */
#घोषणा MAX_TX_BUFFERS		10

अटल पूर्णांक pci_घड़ी_freq = 33000000;
अटल पूर्णांक use_crystal_घड़ी = 0;
अटल अचिन्हित पूर्णांक CLOCK_BASE;

/* Masks to access the init_ctrl PLX रेजिस्टर */
#घोषणा PC300_CLKSEL_MASK	 (0x00000004UL)
#घोषणा PC300_CHMEDIA_MASK(port) (0x00000020UL << ((port) * 3))
#घोषणा PC300_CTYPE_MASK	 (0x00000800UL)


क्रमागत अणु PC300_RSV = 1, PC300_X21, PC300_TE पूर्ण; /* card types */

/*
 *      PLX PCI9050-1 local configuration and shared runसमय रेजिस्टरs.
 *      This काष्ठाure can be used to access 9050 रेजिस्टरs (memory mapped).
 */
प्रकार काष्ठा अणु
	u32 loc_addr_range[4];	/* 00-0Ch : Local Address Ranges */
	u32 loc_rom_range;	/* 10h : Local ROM Range */
	u32 loc_addr_base[4];	/* 14-20h : Local Address Base Addrs */
	u32 loc_rom_base;	/* 24h : Local ROM Base */
	u32 loc_bus_descr[4];	/* 28-34h : Local Bus Descriptors */
	u32 rom_bus_descr;	/* 38h : ROM Bus Descriptor */
	u32 cs_base[4];		/* 3C-48h : Chip Select Base Addrs */
	u32 पूर्णांकr_ctrl_stat;	/* 4Ch : Interrupt Control/Status */
	u32 init_ctrl;		/* 50h : EEPROM ctrl, Init Ctrl, etc */
पूर्णplx9050;



प्रकार काष्ठा port_s अणु
	काष्ठा napi_काष्ठा napi;
	काष्ठा net_device *netdev;
	काष्ठा card_s *card;
	spinlock_t lock;	/* TX lock */
	sync_serial_settings settings;
	पूर्णांक rxpart;		/* partial frame received, next frame invalid*/
	अचिन्हित लघु encoding;
	अचिन्हित लघु parity;
	अचिन्हित पूर्णांक अगरace;
	u16 rxin;		/* rx ring buffer 'in' poपूर्णांकer */
	u16 txin;		/* tx ring buffer 'in' and 'last' poपूर्णांकers */
	u16 txlast;
	u8 rxs, txs, पंचांगc;	/* SCA रेजिस्टरs */
	u8 chan;		/* physical port # - 0 or 1 */
पूर्णport_t;



प्रकार काष्ठा card_s अणु
	पूर्णांक type;		/* RSV, X21, etc. */
	पूर्णांक n_ports;		/* 1 or 2 ports */
	u8 __iomem *rambase;	/* buffer memory base (भव) */
	u8 __iomem *scabase;	/* SCA memory base (भव) */
	plx9050 __iomem *plxbase; /* PLX रेजिस्टरs memory base (भव) */
	u32 init_ctrl_value;	/* Saved value - 9050 bug workaround */
	u16 rx_ring_buffers;	/* number of buffers in a ring */
	u16 tx_ring_buffers;
	u16 buff_offset;	/* offset of first buffer of first channel */
	u8 irq;			/* पूर्णांकerrupt request level */

	port_t ports[2];
पूर्णcard_t;


#घोषणा get_port(card, port)	     ((port) < (card)->n_ports ? \
					 (&(card)->ports[port]) : (शून्य))

#समावेश "hd64572.c"


अटल व्योम pc300_set_अगरace(port_t *port)
अणु
	card_t *card = port->card;
	u32 __iomem * init_ctrl = &card->plxbase->init_ctrl;
	u16 msci = get_msci(port);
	u8 rxs = port->rxs & CLK_BRG_MASK;
	u8 txs = port->txs & CLK_BRG_MASK;

	sca_out(EXS_TES1, (port->chan ? MSCI1_OFFSET : MSCI0_OFFSET) + EXS,
		port->card);
	चयन(port->settings.घड़ी_प्रकारype) अणु
	हाल CLOCK_INT:
		rxs |= CLK_BRG; /* BRG output */
		txs |= CLK_PIN_OUT | CLK_TX_RXCLK; /* RX घड़ी */
		अवरोध;

	हाल CLOCK_TXINT:
		rxs |= CLK_LINE; /* RXC input */
		txs |= CLK_PIN_OUT | CLK_BRG; /* BRG output */
		अवरोध;

	हाल CLOCK_TXFROMRX:
		rxs |= CLK_LINE; /* RXC input */
		txs |= CLK_PIN_OUT | CLK_TX_RXCLK; /* RX घड़ी */
		अवरोध;

	शेष:		/* EXTernal घड़ी */
		rxs |= CLK_LINE; /* RXC input */
		txs |= CLK_PIN_OUT | CLK_LINE; /* TXC input */
		अवरोध;
	पूर्ण

	port->rxs = rxs;
	port->txs = txs;
	sca_out(rxs, msci + RXS, card);
	sca_out(txs, msci + TXS, card);
	sca_set_port(port);

	अगर (port->card->type == PC300_RSV) अणु
		अगर (port->अगरace == IF_IFACE_V35)
			ग_लिखोl(card->init_ctrl_value |
			       PC300_CHMEDIA_MASK(port->chan), init_ctrl);
		अन्यथा
			ग_लिखोl(card->init_ctrl_value &
			       ~PC300_CHMEDIA_MASK(port->chan), init_ctrl);
	पूर्ण
पूर्ण



अटल पूर्णांक pc300_खोलो(काष्ठा net_device *dev)
अणु
	port_t *port = dev_to_port(dev);

	पूर्णांक result = hdlc_खोलो(dev);
	अगर (result)
		वापस result;

	sca_खोलो(dev);
	pc300_set_अगरace(port);
	वापस 0;
पूर्ण



अटल पूर्णांक pc300_बंद(काष्ठा net_device *dev)
अणु
	sca_बंद(dev);
	hdlc_बंद(dev);
	वापस 0;
पूर्ण



अटल पूर्णांक pc300_ioctl(काष्ठा net_device *dev, काष्ठा अगरreq *अगरr, पूर्णांक cmd)
अणु
	स्थिर माप_प्रकार size = माप(sync_serial_settings);
	sync_serial_settings new_line;
	sync_serial_settings __user *line = अगरr->अगरr_settings.अगरs_अगरsu.sync;
	पूर्णांक new_type;
	port_t *port = dev_to_port(dev);

#अगर_घोषित DEBUG_RINGS
	अगर (cmd == SIOCDEVPRIVATE) अणु
		sca_dump_rings(dev);
		वापस 0;
	पूर्ण
#पूर्ण_अगर
	अगर (cmd != SIOCWANDEV)
		वापस hdlc_ioctl(dev, अगरr, cmd);

	अगर (अगरr->अगरr_settings.type == IF_GET_IFACE) अणु
		अगरr->अगरr_settings.type = port->अगरace;
		अगर (अगरr->अगरr_settings.size < size) अणु
			अगरr->अगरr_settings.size = size; /* data size wanted */
			वापस -ENOBUFS;
		पूर्ण
		अगर (copy_to_user(line, &port->settings, size))
			वापस -EFAULT;
		वापस 0;

	पूर्ण

	अगर (port->card->type == PC300_X21 &&
	    (अगरr->अगरr_settings.type == IF_IFACE_SYNC_SERIAL ||
	     अगरr->अगरr_settings.type == IF_IFACE_X21))
		new_type = IF_IFACE_X21;

	अन्यथा अगर (port->card->type == PC300_RSV &&
		 (अगरr->अगरr_settings.type == IF_IFACE_SYNC_SERIAL ||
		  अगरr->अगरr_settings.type == IF_IFACE_V35))
		new_type = IF_IFACE_V35;

	अन्यथा अगर (port->card->type == PC300_RSV &&
		 अगरr->अगरr_settings.type == IF_IFACE_V24)
		new_type = IF_IFACE_V24;

	अन्यथा
		वापस hdlc_ioctl(dev, अगरr, cmd);

	अगर (!capable(CAP_NET_ADMIN))
		वापस -EPERM;

	अगर (copy_from_user(&new_line, line, size))
		वापस -EFAULT;

	अगर (new_line.घड़ी_प्रकारype != CLOCK_EXT &&
	    new_line.घड़ी_प्रकारype != CLOCK_TXFROMRX &&
	    new_line.घड़ी_प्रकारype != CLOCK_INT &&
	    new_line.घड़ी_प्रकारype != CLOCK_TXINT)
		वापस -EINVAL;	/* No such घड़ी setting */

	अगर (new_line.loopback != 0 && new_line.loopback != 1)
		वापस -EINVAL;

	स_नकल(&port->settings, &new_line, size); /* Update settings */
	port->अगरace = new_type;
	pc300_set_अगरace(port);
	वापस 0;
पूर्ण



अटल व्योम pc300_pci_हटाओ_one(काष्ठा pci_dev *pdev)
अणु
	पूर्णांक i;
	card_t *card = pci_get_drvdata(pdev);

	क्रम (i = 0; i < 2; i++)
		अगर (card->ports[i].card)
			unरेजिस्टर_hdlc_device(card->ports[i].netdev);

	अगर (card->irq)
		मुक्त_irq(card->irq, card);

	अगर (card->rambase)
		iounmap(card->rambase);
	अगर (card->scabase)
		iounmap(card->scabase);
	अगर (card->plxbase)
		iounmap(card->plxbase);

	pci_release_regions(pdev);
	pci_disable_device(pdev);
	अगर (card->ports[0].netdev)
		मुक्त_netdev(card->ports[0].netdev);
	अगर (card->ports[1].netdev)
		मुक्त_netdev(card->ports[1].netdev);
	kमुक्त(card);
पूर्ण

अटल स्थिर काष्ठा net_device_ops pc300_ops = अणु
	.nकरो_खोलो       = pc300_खोलो,
	.nकरो_stop       = pc300_बंद,
	.nकरो_start_xmit = hdlc_start_xmit,
	.nकरो_करो_ioctl   = pc300_ioctl,
पूर्ण;

अटल पूर्णांक pc300_pci_init_one(काष्ठा pci_dev *pdev,
			      स्थिर काष्ठा pci_device_id *ent)
अणु
	card_t *card;
	u32 __iomem *p;
	पूर्णांक i;
	u32 ramsize;
	u32 ramphys;		/* buffer memory base */
	u32 scaphys;		/* SCA memory base */
	u32 plxphys;		/* PLX रेजिस्टरs memory base */

	i = pci_enable_device(pdev);
	अगर (i)
		वापस i;

	i = pci_request_regions(pdev, "PC300");
	अगर (i) अणु
		pci_disable_device(pdev);
		वापस i;
	पूर्ण

	card = kzalloc(माप(card_t), GFP_KERNEL);
	अगर (card == शून्य) अणु
		pci_release_regions(pdev);
		pci_disable_device(pdev);
		वापस -ENOBUFS;
	पूर्ण
	pci_set_drvdata(pdev, card);

	अगर (pci_resource_len(pdev, 0) != PC300_PLX_SIZE ||
	    pci_resource_len(pdev, 2) != PC300_SCA_SIZE ||
	    pci_resource_len(pdev, 3) < 16384) अणु
		pr_err("invalid card EEPROM parameters\n");
		pc300_pci_हटाओ_one(pdev);
		वापस -EFAULT;
	पूर्ण

	plxphys = pci_resource_start(pdev, 0) & PCI_BASE_ADDRESS_MEM_MASK;
	card->plxbase = ioremap(plxphys, PC300_PLX_SIZE);

	scaphys = pci_resource_start(pdev, 2) & PCI_BASE_ADDRESS_MEM_MASK;
	card->scabase = ioremap(scaphys, PC300_SCA_SIZE);

	ramphys = pci_resource_start(pdev, 3) & PCI_BASE_ADDRESS_MEM_MASK;
	card->rambase = pci_ioremap_bar(pdev, 3);

	अगर (card->plxbase == शून्य ||
	    card->scabase == शून्य ||
	    card->rambase == शून्य) अणु
		pr_err("ioremap() failed\n");
		pc300_pci_हटाओ_one(pdev);
		वापस -ENOMEM;
	पूर्ण

	/* PLX PCI 9050 workaround क्रम local configuration रेजिस्टर पढ़ो bug */
	pci_ग_लिखो_config_dword(pdev, PCI_BASE_ADDRESS_0, scaphys);
	card->init_ctrl_value = पढ़ोl(&((plx9050 __iomem *)card->scabase)->init_ctrl);
	pci_ग_लिखो_config_dword(pdev, PCI_BASE_ADDRESS_0, plxphys);

	अगर (pdev->device == PCI_DEVICE_ID_PC300_TE_1 ||
	    pdev->device == PCI_DEVICE_ID_PC300_TE_2)
		card->type = PC300_TE; /* not fully supported */
	अन्यथा अगर (card->init_ctrl_value & PC300_CTYPE_MASK)
		card->type = PC300_X21;
	अन्यथा
		card->type = PC300_RSV;

	अगर (pdev->device == PCI_DEVICE_ID_PC300_RX_1 ||
	    pdev->device == PCI_DEVICE_ID_PC300_TE_1)
		card->n_ports = 1;
	अन्यथा
		card->n_ports = 2;

	क्रम (i = 0; i < card->n_ports; i++)
		अगर (!(card->ports[i].netdev = alloc_hdlcdev(&card->ports[i]))) अणु
			pr_err("unable to allocate memory\n");
			pc300_pci_हटाओ_one(pdev);
			वापस -ENOMEM;
		पूर्ण

	/* Reset PLX */
	p = &card->plxbase->init_ctrl;
	ग_लिखोl(card->init_ctrl_value | 0x40000000, p);
	पढ़ोl(p);		/* Flush the ग_लिखो - करो not use sca_flush */
	udelay(1);

	ग_लिखोl(card->init_ctrl_value, p);
	पढ़ोl(p);		/* Flush the ग_लिखो - करो not use sca_flush */
	udelay(1);

	/* Reload Config. Registers from EEPROM */
	ग_लिखोl(card->init_ctrl_value | 0x20000000, p);
	पढ़ोl(p);		/* Flush the ग_लिखो - करो not use sca_flush */
	udelay(1);

	ग_लिखोl(card->init_ctrl_value, p);
	पढ़ोl(p);		/* Flush the ग_लिखो - करो not use sca_flush */
	udelay(1);

	ramsize = sca_detect_ram(card, card->rambase,
				 pci_resource_len(pdev, 3));

	अगर (use_crystal_घड़ी)
		card->init_ctrl_value &= ~PC300_CLKSEL_MASK;
	अन्यथा
		card->init_ctrl_value |= PC300_CLKSEL_MASK;

	ग_लिखोl(card->init_ctrl_value, &card->plxbase->init_ctrl);
	/* number of TX + RX buffers क्रम one port */
	i = ramsize / (card->n_ports * (माप(pkt_desc) + HDLC_MAX_MRU));
	card->tx_ring_buffers = min(i / 2, MAX_TX_BUFFERS);
	card->rx_ring_buffers = i - card->tx_ring_buffers;

	card->buff_offset = card->n_ports * माप(pkt_desc) *
		(card->tx_ring_buffers + card->rx_ring_buffers);

	pr_info("PC300/%s, %u KB RAM at 0x%x, IRQ%u, using %u TX + %u RX packets rings\n",
		card->type == PC300_X21 ? "X21" :
		card->type == PC300_TE ? "TE" : "RSV",
		ramsize / 1024, ramphys, pdev->irq,
		card->tx_ring_buffers, card->rx_ring_buffers);

	अगर (card->tx_ring_buffers < 1) अणु
		pr_err("RAM test failed\n");
		pc300_pci_हटाओ_one(pdev);
		वापस -EFAULT;
	पूर्ण

	/* Enable पूर्णांकerrupts on the PCI bridge, LINTi1 active low */
	ग_लिखोw(0x0041, &card->plxbase->पूर्णांकr_ctrl_stat);

	/* Allocate IRQ */
	अगर (request_irq(pdev->irq, sca_पूर्णांकr, IRQF_SHARED, "pc300", card)) अणु
		pr_warn("could not allocate IRQ%d\n", pdev->irq);
		pc300_pci_हटाओ_one(pdev);
		वापस -EBUSY;
	पूर्ण
	card->irq = pdev->irq;

	sca_init(card, 0);

	// COTE not set - allows better TX DMA settings
	// sca_out(sca_in(PCR, card) | PCR_COTE, PCR, card);

	sca_out(0x10, BTCR, card);

	क्रम (i = 0; i < card->n_ports; i++) अणु
		port_t *port = &card->ports[i];
		काष्ठा net_device *dev = port->netdev;
		hdlc_device *hdlc = dev_to_hdlc(dev);
		port->chan = i;

		spin_lock_init(&port->lock);
		dev->irq = card->irq;
		dev->mem_start = ramphys;
		dev->mem_end = ramphys + ramsize - 1;
		dev->tx_queue_len = 50;
		dev->netdev_ops = &pc300_ops;
		hdlc->attach = sca_attach;
		hdlc->xmit = sca_xmit;
		port->settings.घड़ी_प्रकारype = CLOCK_EXT;
		port->card = card;
		अगर (card->type == PC300_X21)
			port->अगरace = IF_IFACE_X21;
		अन्यथा
			port->अगरace = IF_IFACE_V35;

		sca_init_port(port);
		अगर (रेजिस्टर_hdlc_device(dev)) अणु
			pr_err("unable to register hdlc device\n");
			port->card = शून्य;
			pc300_pci_हटाओ_one(pdev);
			वापस -ENOBUFS;
		पूर्ण

		netdev_info(dev, "PC300 channel %d\n", port->chan);
	पूर्ण
	वापस 0;
पूर्ण



अटल स्थिर काष्ठा pci_device_id pc300_pci_tbl[] = अणु
	अणु PCI_VENDOR_ID_CYCLADES, PCI_DEVICE_ID_PC300_RX_1, PCI_ANY_ID,
	  PCI_ANY_ID, 0, 0, 0 पूर्ण,
	अणु PCI_VENDOR_ID_CYCLADES, PCI_DEVICE_ID_PC300_RX_2, PCI_ANY_ID,
	  PCI_ANY_ID, 0, 0, 0 पूर्ण,
	अणु PCI_VENDOR_ID_CYCLADES, PCI_DEVICE_ID_PC300_TE_1, PCI_ANY_ID,
	  PCI_ANY_ID, 0, 0, 0 पूर्ण,
	अणु PCI_VENDOR_ID_CYCLADES, PCI_DEVICE_ID_PC300_TE_2, PCI_ANY_ID,
	  PCI_ANY_ID, 0, 0, 0 पूर्ण,
	अणु 0, पूर्ण
पूर्ण;


अटल काष्ठा pci_driver pc300_pci_driver = अणु
	.name =          "PC300",
	.id_table =      pc300_pci_tbl,
	.probe =         pc300_pci_init_one,
	.हटाओ =        pc300_pci_हटाओ_one,
पूर्ण;


अटल पूर्णांक __init pc300_init_module(व्योम)
अणु
	अगर (pci_घड़ी_freq < 1000000 || pci_घड़ी_freq > 80000000) अणु
		pr_err("Invalid PCI clock frequency\n");
		वापस -EINVAL;
	पूर्ण
	अगर (use_crystal_घड़ी != 0 && use_crystal_घड़ी != 1) अणु
		pr_err("Invalid 'use_crystal_clock' value\n");
		वापस -EINVAL;
	पूर्ण

	CLOCK_BASE = use_crystal_घड़ी ? 24576000 : pci_घड़ी_freq;

	वापस pci_रेजिस्टर_driver(&pc300_pci_driver);
पूर्ण



अटल व्योम __निकास pc300_cleanup_module(व्योम)
अणु
	pci_unरेजिस्टर_driver(&pc300_pci_driver);
पूर्ण

MODULE_AUTHOR("Krzysztof Halasa <khc@pm.waw.pl>");
MODULE_DESCRIPTION("Cyclades PC300 serial port driver");
MODULE_LICENSE("GPL v2");
MODULE_DEVICE_TABLE(pci, pc300_pci_tbl);
module_param(pci_घड़ी_freq, पूर्णांक, 0444);
MODULE_PARM_DESC(pci_घड़ी_freq, "System PCI clock frequency in Hz");
module_param(use_crystal_घड़ी, पूर्णांक, 0444);
MODULE_PARM_DESC(use_crystal_घड़ी,
		 "Use 24.576 MHz clock instead of PCI clock");
module_init(pc300_init_module);
module_निकास(pc300_cleanup_module);
