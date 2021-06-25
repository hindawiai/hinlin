<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Goramo PCI200SYN synchronous serial card driver क्रम Linux
 *
 * Copyright (C) 2002-2008 Krzysztof Halasa <khc@pm.waw.pl>
 *
 * For inक्रमmation see <https://www.kernel.org/pub/linux/utils/net/hdlc/>
 *
 * Sources of inक्रमmation:
 *    Hitachi HD64572 SCA-II User's Manual
 *    PLX Technology Inc. PCI9052 Data Book
 */

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#समावेश <linux/module.h>
#समावेश <linux/kernel.h>
#समावेश <linux/capability.h>
#समावेश <linux/slab.h>
#समावेश <linux/types.h>
#समावेश <linux/fcntl.h>
#समावेश <linux/in.h>
#समावेश <linux/माला.स>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/init.h>
#समावेश <linux/ioport.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/hdlc.h>
#समावेश <linux/pci.h>
#समावेश <linux/delay.h>
#समावेश <यंत्र/पन.स>

#समावेश "hd64572.h"

#अघोषित DEBUG_PKT
#घोषणा DEBUG_RINGS

#घोषणा PCI200SYN_PLX_SIZE	0x80	/* PLX control winकरोw size (128b) */
#घोषणा PCI200SYN_SCA_SIZE	0x400	/* SCA winकरोw size (1Kb) */
#घोषणा MAX_TX_BUFFERS		10

अटल पूर्णांक pci_घड़ी_freq = 33000000;
#घोषणा CLOCK_BASE pci_घड़ी_freq

/*
 *      PLX PCI9052 local configuration and shared runसमय रेजिस्टरs.
 *      This काष्ठाure can be used to access 9052 रेजिस्टरs (memory mapped).
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
पूर्णplx9052;



प्रकार काष्ठा port_s अणु
	काष्ठा napi_काष्ठा napi;
	काष्ठा net_device *netdev;
	काष्ठा card_s *card;
	spinlock_t lock;	/* TX lock */
	sync_serial_settings settings;
	पूर्णांक rxpart;		/* partial frame received, next frame invalid*/
	अचिन्हित लघु encoding;
	अचिन्हित लघु parity;
	u16 rxin;		/* rx ring buffer 'in' poपूर्णांकer */
	u16 txin;		/* tx ring buffer 'in' and 'last' poपूर्णांकers */
	u16 txlast;
	u8 rxs, txs, पंचांगc;	/* SCA रेजिस्टरs */
	u8 chan;		/* physical port # - 0 or 1 */
पूर्णport_t;



प्रकार काष्ठा card_s अणु
	u8 __iomem *rambase;	/* buffer memory base (भव) */
	u8 __iomem *scabase;	/* SCA memory base (भव) */
	plx9052 __iomem *plxbase;/* PLX रेजिस्टरs memory base (भव) */
	u16 rx_ring_buffers;	/* number of buffers in a ring */
	u16 tx_ring_buffers;
	u16 buff_offset;	/* offset of first buffer of first channel */
	u8 irq;			/* पूर्णांकerrupt request level */

	port_t ports[2];
पूर्णcard_t;


#घोषणा get_port(card, port)	     (&card->ports[port])
#घोषणा sca_flush(card)		     (sca_in(IER0, card))

अटल अंतरभूत व्योम new_स_नकल_toio(अक्षर __iomem *dest, अक्षर *src, पूर्णांक length)
अणु
	पूर्णांक len;
	करो अणु
		len = length > 256 ? 256 : length;
		स_नकल_toio(dest, src, len);
		dest += len;
		src += len;
		length -= len;
		पढ़ोb(dest);
	पूर्ण जबतक (len);
पूर्ण

#अघोषित स_नकल_toio
#घोषणा स_नकल_toio new_स_नकल_toio

#समावेश "hd64572.c"


अटल व्योम pci200_set_अगरace(port_t *port)
अणु
	card_t *card = port->card;
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
पूर्ण



अटल पूर्णांक pci200_खोलो(काष्ठा net_device *dev)
अणु
	port_t *port = dev_to_port(dev);

	पूर्णांक result = hdlc_खोलो(dev);
	अगर (result)
		वापस result;

	sca_खोलो(dev);
	pci200_set_अगरace(port);
	sca_flush(port->card);
	वापस 0;
पूर्ण



अटल पूर्णांक pci200_बंद(काष्ठा net_device *dev)
अणु
	sca_बंद(dev);
	sca_flush(dev_to_port(dev)->card);
	hdlc_बंद(dev);
	वापस 0;
पूर्ण



अटल पूर्णांक pci200_ioctl(काष्ठा net_device *dev, काष्ठा अगरreq *अगरr, पूर्णांक cmd)
अणु
	स्थिर माप_प्रकार size = माप(sync_serial_settings);
	sync_serial_settings new_line;
	sync_serial_settings __user *line = अगरr->अगरr_settings.अगरs_अगरsu.sync;
	port_t *port = dev_to_port(dev);

#अगर_घोषित DEBUG_RINGS
	अगर (cmd == SIOCDEVPRIVATE) अणु
		sca_dump_rings(dev);
		वापस 0;
	पूर्ण
#पूर्ण_अगर
	अगर (cmd != SIOCWANDEV)
		वापस hdlc_ioctl(dev, अगरr, cmd);

	चयन(अगरr->अगरr_settings.type) अणु
	हाल IF_GET_IFACE:
		अगरr->अगरr_settings.type = IF_IFACE_V35;
		अगर (अगरr->अगरr_settings.size < size) अणु
			अगरr->अगरr_settings.size = size; /* data size wanted */
			वापस -ENOBUFS;
		पूर्ण
		अगर (copy_to_user(line, &port->settings, size))
			वापस -EFAULT;
		वापस 0;

	हाल IF_IFACE_V35:
	हाल IF_IFACE_SYNC_SERIAL:
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
		pci200_set_अगरace(port);
		sca_flush(port->card);
		वापस 0;

	शेष:
		वापस hdlc_ioctl(dev, अगरr, cmd);
	पूर्ण
पूर्ण



अटल व्योम pci200_pci_हटाओ_one(काष्ठा pci_dev *pdev)
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

अटल स्थिर काष्ठा net_device_ops pci200_ops = अणु
	.nकरो_खोलो       = pci200_खोलो,
	.nकरो_stop       = pci200_बंद,
	.nकरो_start_xmit = hdlc_start_xmit,
	.nकरो_करो_ioctl   = pci200_ioctl,
पूर्ण;

अटल पूर्णांक pci200_pci_init_one(काष्ठा pci_dev *pdev,
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

	i = pci_request_regions(pdev, "PCI200SYN");
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
	card->ports[0].netdev = alloc_hdlcdev(&card->ports[0]);
	card->ports[1].netdev = alloc_hdlcdev(&card->ports[1]);
	अगर (!card->ports[0].netdev || !card->ports[1].netdev) अणु
		pr_err("unable to allocate memory\n");
		pci200_pci_हटाओ_one(pdev);
		वापस -ENOMEM;
	पूर्ण

	अगर (pci_resource_len(pdev, 0) != PCI200SYN_PLX_SIZE ||
	    pci_resource_len(pdev, 2) != PCI200SYN_SCA_SIZE ||
	    pci_resource_len(pdev, 3) < 16384) अणु
		pr_err("invalid card EEPROM parameters\n");
		pci200_pci_हटाओ_one(pdev);
		वापस -EFAULT;
	पूर्ण

	plxphys = pci_resource_start(pdev,0) & PCI_BASE_ADDRESS_MEM_MASK;
	card->plxbase = ioremap(plxphys, PCI200SYN_PLX_SIZE);

	scaphys = pci_resource_start(pdev,2) & PCI_BASE_ADDRESS_MEM_MASK;
	card->scabase = ioremap(scaphys, PCI200SYN_SCA_SIZE);

	ramphys = pci_resource_start(pdev,3) & PCI_BASE_ADDRESS_MEM_MASK;
	card->rambase = pci_ioremap_bar(pdev, 3);

	अगर (card->plxbase == शून्य ||
	    card->scabase == शून्य ||
	    card->rambase == शून्य) अणु
		pr_err("ioremap() failed\n");
		pci200_pci_हटाओ_one(pdev);
		वापस -EFAULT;
	पूर्ण

	/* Reset PLX */
	p = &card->plxbase->init_ctrl;
	ग_लिखोl(पढ़ोl(p) | 0x40000000, p);
	पढ़ोl(p);		/* Flush the ग_लिखो - करो not use sca_flush */
	udelay(1);

	ग_लिखोl(पढ़ोl(p) & ~0x40000000, p);
	पढ़ोl(p);		/* Flush the ग_लिखो - करो not use sca_flush */
	udelay(1);

	ramsize = sca_detect_ram(card, card->rambase,
				 pci_resource_len(pdev, 3));

	/* number of TX + RX buffers क्रम one port - this is dual port card */
	i = ramsize / (2 * (माप(pkt_desc) + HDLC_MAX_MRU));
	card->tx_ring_buffers = min(i / 2, MAX_TX_BUFFERS);
	card->rx_ring_buffers = i - card->tx_ring_buffers;

	card->buff_offset = 2 * माप(pkt_desc) * (card->tx_ring_buffers +
						    card->rx_ring_buffers);

	pr_info("%u KB RAM at 0x%x, IRQ%u, using %u TX + %u RX packets rings\n",
		ramsize / 1024, ramphys,
		pdev->irq, card->tx_ring_buffers, card->rx_ring_buffers);

	अगर (card->tx_ring_buffers < 1) अणु
		pr_err("RAM test failed\n");
		pci200_pci_हटाओ_one(pdev);
		वापस -EFAULT;
	पूर्ण

	/* Enable पूर्णांकerrupts on the PCI bridge */
	p = &card->plxbase->पूर्णांकr_ctrl_stat;
	ग_लिखोw(पढ़ोw(p) | 0x0040, p);

	/* Allocate IRQ */
	अगर (request_irq(pdev->irq, sca_पूर्णांकr, IRQF_SHARED, "pci200syn", card)) अणु
		pr_warn("could not allocate IRQ%d\n", pdev->irq);
		pci200_pci_हटाओ_one(pdev);
		वापस -EBUSY;
	पूर्ण
	card->irq = pdev->irq;

	sca_init(card, 0);

	क्रम (i = 0; i < 2; i++) अणु
		port_t *port = &card->ports[i];
		काष्ठा net_device *dev = port->netdev;
		hdlc_device *hdlc = dev_to_hdlc(dev);
		port->chan = i;

		spin_lock_init(&port->lock);
		dev->irq = card->irq;
		dev->mem_start = ramphys;
		dev->mem_end = ramphys + ramsize - 1;
		dev->tx_queue_len = 50;
		dev->netdev_ops = &pci200_ops;
		hdlc->attach = sca_attach;
		hdlc->xmit = sca_xmit;
		port->settings.घड़ी_प्रकारype = CLOCK_EXT;
		port->card = card;
		sca_init_port(port);
		अगर (रेजिस्टर_hdlc_device(dev)) अणु
			pr_err("unable to register hdlc device\n");
			port->card = शून्य;
			pci200_pci_हटाओ_one(pdev);
			वापस -ENOBUFS;
		पूर्ण

		netdev_info(dev, "PCI200SYN channel %d\n", port->chan);
	पूर्ण

	sca_flush(card);
	वापस 0;
पूर्ण



अटल स्थिर काष्ठा pci_device_id pci200_pci_tbl[] = अणु
	अणु PCI_VENDOR_ID_PLX, PCI_DEVICE_ID_PLX_9050, PCI_VENDOR_ID_PLX,
	  PCI_DEVICE_ID_PLX_PCI200SYN, 0, 0, 0 पूर्ण,
	अणु 0, पूर्ण
पूर्ण;


अटल काष्ठा pci_driver pci200_pci_driver = अणु
	.name		= "PCI200SYN",
	.id_table	= pci200_pci_tbl,
	.probe		= pci200_pci_init_one,
	.हटाओ		= pci200_pci_हटाओ_one,
पूर्ण;


अटल पूर्णांक __init pci200_init_module(व्योम)
अणु
	अगर (pci_घड़ी_freq < 1000000 || pci_घड़ी_freq > 80000000) अणु
		pr_err("Invalid PCI clock frequency\n");
		वापस -EINVAL;
	पूर्ण
	वापस pci_रेजिस्टर_driver(&pci200_pci_driver);
पूर्ण



अटल व्योम __निकास pci200_cleanup_module(व्योम)
अणु
	pci_unरेजिस्टर_driver(&pci200_pci_driver);
पूर्ण

MODULE_AUTHOR("Krzysztof Halasa <khc@pm.waw.pl>");
MODULE_DESCRIPTION("Goramo PCI200SYN serial port driver");
MODULE_LICENSE("GPL v2");
MODULE_DEVICE_TABLE(pci, pci200_pci_tbl);
module_param(pci_घड़ी_freq, पूर्णांक, 0444);
MODULE_PARM_DESC(pci_घड़ी_freq, "System PCI clock frequency in Hz");
module_init(pci200_init_module);
module_निकास(pci200_cleanup_module);
