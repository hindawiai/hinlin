<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * SDL Inc. RISCom/N2 synchronous serial card driver क्रम Linux
 *
 * Copyright (C) 1998-2003 Krzysztof Halasa <khc@pm.waw.pl>
 *
 * For inक्रमmation see <https://www.kernel.org/pub/linux/utils/net/hdlc/>
 *
 * Note: पूर्णांकegrated CSU/DSU/DDS are not supported by this driver
 *
 * Sources of inक्रमmation:
 *    Hitachi HD64570 SCA User's Manual
 *    SDL Inc. PPP/HDLC/CISCO driver
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
#समावेश <linux/moduleparam.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/hdlc.h>
#समावेश <यंत्र/पन.स>
#समावेश "hd64570.h"


अटल स्थिर अक्षर* version = "SDL RISCom/N2 driver version: 1.15";
अटल स्थिर अक्षर* devname = "RISCom/N2";

#अघोषित DEBUG_PKT
#घोषणा DEBUG_RINGS

#घोषणा USE_WINDOWSIZE 16384
#घोषणा USE_BUS16BITS 1
#घोषणा CLOCK_BASE 9830400	/* 9.8304 MHz */
#घोषणा MAX_PAGES      16	/* 16 RAM pages at max */
#घोषणा MAX_RAM_SIZE 0x80000	/* 512 KB */
#अगर MAX_RAM_SIZE > MAX_PAGES * USE_WINDOWSIZE
#अघोषित MAX_RAM_SIZE
#घोषणा MAX_RAM_SIZE (MAX_PAGES * USE_WINDOWSIZE)
#पूर्ण_अगर
#घोषणा N2_IOPORTS 0x10
#घोषणा NEED_DETECT_RAM
#घोषणा NEED_SCA_MSCI_INTR
#घोषणा MAX_TX_BUFFERS 10

अटल अक्षर *hw;	/* poपूर्णांकer to hw=xxx command line string */

/* RISCom/N2 Board Registers */

/* PC Control Register */
#घोषणा N2_PCR 0
#घोषणा PCR_RUNSCA 1     /* Run 64570 */
#घोषणा PCR_VPM    2     /* Enable VPM - needed अगर using RAM above 1 MB */
#घोषणा PCR_ENWIN  4     /* Open winकरोw */
#घोषणा PCR_BUS16  8     /* 16-bit bus */


/* Memory Base Address Register */
#घोषणा N2_BAR 2


/* Page Scan Register  */
#घोषणा N2_PSR 4
#घोषणा WIN16K       0x00
#घोषणा WIN32K       0x20
#घोषणा WIN64K       0x40
#घोषणा PSR_WINBITS  0x60
#घोषणा PSR_DMAEN    0x80
#घोषणा PSR_PAGEBITS 0x0F


/* Modem Control Reg */
#घोषणा N2_MCR 6
#घोषणा CLOCK_OUT_PORT1 0x80
#घोषणा CLOCK_OUT_PORT0 0x40
#घोषणा TX422_PORT1     0x20
#घोषणा TX422_PORT0     0x10
#घोषणा DSR_PORT1       0x08
#घोषणा DSR_PORT0       0x04
#घोषणा DTR_PORT1       0x02
#घोषणा DTR_PORT0       0x01


प्रकार काष्ठा port_s अणु
	काष्ठा net_device *dev;
	काष्ठा card_s *card;
	spinlock_t lock;	/* TX lock */
	sync_serial_settings settings;
	पूर्णांक valid;		/* port enabled */
	पूर्णांक rxpart;		/* partial frame received, next frame invalid*/
	अचिन्हित लघु encoding;
	अचिन्हित लघु parity;
	u16 rxin;		/* rx ring buffer 'in' poपूर्णांकer */
	u16 txin;		/* tx ring buffer 'in' and 'last' poपूर्णांकers */
	u16 txlast;
	u8 rxs, txs, पंचांगc;	/* SCA रेजिस्टरs */
	u8 phy_node;		/* physical port # - 0 or 1 */
	u8 log_node;		/* logical port # */
पूर्णport_t;



प्रकार काष्ठा card_s अणु
	u8 __iomem *winbase;		/* ISA winकरोw base address */
	u32 phy_winbase;	/* ISA physical base address */
	u32 ram_size;		/* number of bytes */
	u16 io;			/* IO Base address */
	u16 buff_offset;	/* offset of first buffer of first channel */
	u16 rx_ring_buffers;	/* number of buffers in a ring */
	u16 tx_ring_buffers;
	u8 irq;			/* IRQ (3-15) */

	port_t ports[2];
	काष्ठा card_s *next_card;
पूर्णcard_t;


अटल card_t *first_card;
अटल card_t **new_card = &first_card;


#घोषणा sca_reg(reg, card) (0x8000 | (card)->io | \
			    ((reg) & 0x0F) | (((reg) & 0xF0) << 6))
#घोषणा sca_in(reg, card)		inb(sca_reg(reg, card))
#घोषणा sca_out(value, reg, card)	outb(value, sca_reg(reg, card))
#घोषणा sca_inw(reg, card)		inw(sca_reg(reg, card))
#घोषणा sca_outw(value, reg, card)	outw(value, sca_reg(reg, card))

#घोषणा port_to_card(port)		((port)->card)
#घोषणा log_node(port)			((port)->log_node)
#घोषणा phy_node(port)			((port)->phy_node)
#घोषणा winsize(card)			(USE_WINDOWSIZE)
#घोषणा winbase(card)      	     	((card)->winbase)
#घोषणा get_port(card, port)		((card)->ports[port].valid ? \
					 &(card)->ports[port] : शून्य)


अटल __अंतरभूत__ u8 sca_get_page(card_t *card)
अणु
	वापस inb(card->io + N2_PSR) & PSR_PAGEBITS;
पूर्ण


अटल __अंतरभूत__ व्योम खोलोwin(card_t *card, u8 page)
अणु
	u8 psr = inb(card->io + N2_PSR);
	outb((psr & ~PSR_PAGEBITS) | page, card->io + N2_PSR);
पूर्ण


#समावेश "hd64570.c"


अटल व्योम n2_set_अगरace(port_t *port)
अणु
	card_t *card = port->card;
	पूर्णांक io = card->io;
	u8 mcr = inb(io + N2_MCR);
	u8 msci = get_msci(port);
	u8 rxs = port->rxs & CLK_BRG_MASK;
	u8 txs = port->txs & CLK_BRG_MASK;

	चयन(port->settings.घड़ी_प्रकारype) अणु
	हाल CLOCK_INT:
		mcr |= port->phy_node ? CLOCK_OUT_PORT1 : CLOCK_OUT_PORT0;
		rxs |= CLK_BRG_RX; /* BRG output */
		txs |= CLK_RXCLK_TX; /* RX घड़ी */
		अवरोध;

	हाल CLOCK_TXINT:
		mcr |= port->phy_node ? CLOCK_OUT_PORT1 : CLOCK_OUT_PORT0;
		rxs |= CLK_LINE_RX; /* RXC input */
		txs |= CLK_BRG_TX; /* BRG output */
		अवरोध;

	हाल CLOCK_TXFROMRX:
		mcr |= port->phy_node ? CLOCK_OUT_PORT1 : CLOCK_OUT_PORT0;
		rxs |= CLK_LINE_RX; /* RXC input */
		txs |= CLK_RXCLK_TX; /* RX घड़ी */
		अवरोध;

	शेष:		/* Clock EXTernal */
		mcr &= port->phy_node ? ~CLOCK_OUT_PORT1 : ~CLOCK_OUT_PORT0;
		rxs |= CLK_LINE_RX; /* RXC input */
		txs |= CLK_LINE_TX; /* TXC input */
	पूर्ण

	outb(mcr, io + N2_MCR);
	port->rxs = rxs;
	port->txs = txs;
	sca_out(rxs, msci + RXS, card);
	sca_out(txs, msci + TXS, card);
	sca_set_port(port);
पूर्ण



अटल पूर्णांक n2_खोलो(काष्ठा net_device *dev)
अणु
	port_t *port = dev_to_port(dev);
	पूर्णांक io = port->card->io;
	u8 mcr = inb(io + N2_MCR) | (port->phy_node ? TX422_PORT1:TX422_PORT0);
	पूर्णांक result;

	result = hdlc_खोलो(dev);
	अगर (result)
		वापस result;

	mcr &= port->phy_node ? ~DTR_PORT1 : ~DTR_PORT0; /* set DTR ON */
	outb(mcr, io + N2_MCR);

	outb(inb(io + N2_PCR) | PCR_ENWIN, io + N2_PCR); /* खोलो winकरोw */
	outb(inb(io + N2_PSR) | PSR_DMAEN, io + N2_PSR); /* enable dma */
	sca_खोलो(dev);
	n2_set_अगरace(port);
	वापस 0;
पूर्ण



अटल पूर्णांक n2_बंद(काष्ठा net_device *dev)
अणु
	port_t *port = dev_to_port(dev);
	पूर्णांक io = port->card->io;
	u8 mcr = inb(io+N2_MCR) | (port->phy_node ? TX422_PORT1 : TX422_PORT0);

	sca_बंद(dev);
	mcr |= port->phy_node ? DTR_PORT1 : DTR_PORT0; /* set DTR OFF */
	outb(mcr, io + N2_MCR);
	hdlc_बंद(dev);
	वापस 0;
पूर्ण



अटल पूर्णांक n2_ioctl(काष्ठा net_device *dev, काष्ठा अगरreq *अगरr, पूर्णांक cmd)
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
		अगरr->अगरr_settings.type = IF_IFACE_SYNC_SERIAL;
		अगर (अगरr->अगरr_settings.size < size) अणु
			अगरr->अगरr_settings.size = size; /* data size wanted */
			वापस -ENOBUFS;
		पूर्ण
		अगर (copy_to_user(line, &port->settings, size))
			वापस -EFAULT;
		वापस 0;

	हाल IF_IFACE_SYNC_SERIAL:
		अगर(!capable(CAP_NET_ADMIN))
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
		n2_set_अगरace(port);
		वापस 0;

	शेष:
		वापस hdlc_ioctl(dev, अगरr, cmd);
	पूर्ण
पूर्ण



अटल व्योम n2_destroy_card(card_t *card)
अणु
	पूर्णांक cnt;

	क्रम (cnt = 0; cnt < 2; cnt++)
		अगर (card->ports[cnt].card) अणु
			काष्ठा net_device *dev = port_to_dev(&card->ports[cnt]);
			unरेजिस्टर_hdlc_device(dev);
		पूर्ण

	अगर (card->irq)
		मुक्त_irq(card->irq, card);

	अगर (card->winbase) अणु
		iounmap(card->winbase);
		release_mem_region(card->phy_winbase, USE_WINDOWSIZE);
	पूर्ण

	अगर (card->io)
		release_region(card->io, N2_IOPORTS);
	अगर (card->ports[0].dev)
		मुक्त_netdev(card->ports[0].dev);
	अगर (card->ports[1].dev)
		मुक्त_netdev(card->ports[1].dev);
	kमुक्त(card);
पूर्ण

अटल स्थिर काष्ठा net_device_ops n2_ops = अणु
	.nकरो_खोलो       = n2_खोलो,
	.nकरो_stop       = n2_बंद,
	.nकरो_start_xmit = hdlc_start_xmit,
	.nकरो_करो_ioctl   = n2_ioctl,
पूर्ण;

अटल पूर्णांक __init n2_run(अचिन्हित दीर्घ io, अचिन्हित दीर्घ irq,
			 अचिन्हित दीर्घ winbase, दीर्घ valid0, दीर्घ valid1)
अणु
	card_t *card;
	u8 cnt, pcr;
	पूर्णांक i;

	अगर (io < 0x200 || io > 0x3FF || (io % N2_IOPORTS) != 0) अणु
		pr_err("invalid I/O port value\n");
		वापस -ENODEV;
	पूर्ण

	अगर (irq < 3 || irq > 15 || irq == 6) /* FIXME */ अणु
		pr_err("invalid IRQ value\n");
		वापस -ENODEV;
	पूर्ण

	अगर (winbase < 0xA0000 || winbase > 0xFFFFF || (winbase & 0xFFF) != 0) अणु
		pr_err("invalid RAM value\n");
		वापस -ENODEV;
	पूर्ण

	card = kzalloc(माप(card_t), GFP_KERNEL);
	अगर (card == शून्य)
		वापस -ENOBUFS;

	card->ports[0].dev = alloc_hdlcdev(&card->ports[0]);
	card->ports[1].dev = alloc_hdlcdev(&card->ports[1]);
	अगर (!card->ports[0].dev || !card->ports[1].dev) अणु
		pr_err("unable to allocate memory\n");
		n2_destroy_card(card);
		वापस -ENOMEM;
	पूर्ण

	अगर (!request_region(io, N2_IOPORTS, devname)) अणु
		pr_err("I/O port region in use\n");
		n2_destroy_card(card);
		वापस -EBUSY;
	पूर्ण
	card->io = io;

	अगर (request_irq(irq, sca_पूर्णांकr, 0, devname, card)) अणु
		pr_err("could not allocate IRQ\n");
		n2_destroy_card(card);
		वापस -EBUSY;
	पूर्ण
	card->irq = irq;

	अगर (!request_mem_region(winbase, USE_WINDOWSIZE, devname)) अणु
		pr_err("could not request RAM window\n");
		n2_destroy_card(card);
		वापस -EBUSY;
	पूर्ण
	card->phy_winbase = winbase;
	card->winbase = ioremap(winbase, USE_WINDOWSIZE);
	अगर (!card->winbase) अणु
		pr_err("ioremap() failed\n");
		n2_destroy_card(card);
		वापस -EFAULT;
	पूर्ण

	outb(0, io + N2_PCR);
	outb(winbase >> 12, io + N2_BAR);

	चयन (USE_WINDOWSIZE) अणु
	हाल 16384:
		outb(WIN16K, io + N2_PSR);
		अवरोध;

	हाल 32768:
		outb(WIN32K, io + N2_PSR);
		अवरोध;

	हाल 65536:
		outb(WIN64K, io + N2_PSR);
		अवरोध;

	शेष:
		pr_err("invalid window size\n");
		n2_destroy_card(card);
		वापस -ENODEV;
	पूर्ण

	pcr = PCR_ENWIN | PCR_VPM | (USE_BUS16BITS ? PCR_BUS16 : 0);
	outb(pcr, io + N2_PCR);

	card->ram_size = sca_detect_ram(card, card->winbase, MAX_RAM_SIZE);

	/* number of TX + RX buffers क्रम one port */
	i = card->ram_size / ((valid0 + valid1) * (माप(pkt_desc) +
						   HDLC_MAX_MRU));

	card->tx_ring_buffers = min(i / 2, MAX_TX_BUFFERS);
	card->rx_ring_buffers = i - card->tx_ring_buffers;

	card->buff_offset = (valid0 + valid1) * माप(pkt_desc) *
		(card->tx_ring_buffers + card->rx_ring_buffers);

	pr_info("RISCom/N2 %u KB RAM, IRQ%u, using %u TX + %u RX packets rings\n",
		card->ram_size / 1024, card->irq,
		card->tx_ring_buffers, card->rx_ring_buffers);

	अगर (card->tx_ring_buffers < 1) अणु
		pr_err("RAM test failed\n");
		n2_destroy_card(card);
		वापस -EIO;
	पूर्ण

	pcr |= PCR_RUNSCA;		/* run SCA */
	outb(pcr, io + N2_PCR);
	outb(0, io + N2_MCR);

	sca_init(card, 0);
	क्रम (cnt = 0; cnt < 2; cnt++) अणु
		port_t *port = &card->ports[cnt];
		काष्ठा net_device *dev = port_to_dev(port);
		hdlc_device *hdlc = dev_to_hdlc(dev);

		अगर ((cnt == 0 && !valid0) || (cnt == 1 && !valid1))
			जारी;

		port->phy_node = cnt;
		port->valid = 1;

		अगर ((cnt == 1) && valid0)
			port->log_node = 1;

		spin_lock_init(&port->lock);
		dev->irq = irq;
		dev->mem_start = winbase;
		dev->mem_end = winbase + USE_WINDOWSIZE - 1;
		dev->tx_queue_len = 50;
		dev->netdev_ops = &n2_ops;
		hdlc->attach = sca_attach;
		hdlc->xmit = sca_xmit;
		port->settings.घड़ी_प्रकारype = CLOCK_EXT;
		port->card = card;

		अगर (रेजिस्टर_hdlc_device(dev)) अणु
			pr_warn("unable to register hdlc device\n");
			port->card = शून्य;
			n2_destroy_card(card);
			वापस -ENOBUFS;
		पूर्ण
		sca_init_port(port); /* Set up SCA memory */

		netdev_info(dev, "RISCom/N2 node %d\n", port->phy_node);
	पूर्ण

	*new_card = card;
	new_card = &card->next_card;

	वापस 0;
पूर्ण



अटल पूर्णांक __init n2_init(व्योम)
अणु
	अगर (hw==शून्य) अणु
#अगर_घोषित MODULE
		pr_info("no card initialized\n");
#पूर्ण_अगर
		वापस -EINVAL;	/* no parameters specअगरied, पात */
	पूर्ण

	pr_info("%s\n", version);

	करो अणु
		अचिन्हित दीर्घ io, irq, ram;
		दीर्घ valid[2] = अणु 0, 0 पूर्ण; /* Default = both ports disabled */

		io = simple_म_से_अदीर्घ(hw, &hw, 0);

		अगर (*hw++ != ',')
			अवरोध;
		irq = simple_म_से_अदीर्घ(hw, &hw, 0);

		अगर (*hw++ != ',')
			अवरोध;
		ram = simple_म_से_अदीर्घ(hw, &hw, 0);

		अगर (*hw++ != ',')
			अवरोध;
		जबतक(1) अणु
			अगर (*hw == '0' && !valid[0])
				valid[0] = 1; /* Port 0 enabled */
			अन्यथा अगर (*hw == '1' && !valid[1])
				valid[1] = 1; /* Port 1 enabled */
			अन्यथा
				अवरोध;
			hw++;
		पूर्ण

		अगर (!valid[0] && !valid[1])
			अवरोध;	/* at least one port must be used */

		अगर (*hw == ':' || *hw == '\x0')
			n2_run(io, irq, ram, valid[0], valid[1]);

		अगर (*hw == '\x0')
			वापस first_card ? 0 : -EINVAL;
	पूर्णजबतक(*hw++ == ':');

	pr_err("invalid hardware parameters\n");
	वापस first_card ? 0 : -EINVAL;
पूर्ण


अटल व्योम __निकास n2_cleanup(व्योम)
अणु
	card_t *card = first_card;

	जबतक (card) अणु
		card_t *ptr = card;
		card = card->next_card;
		n2_destroy_card(ptr);
	पूर्ण
पूर्ण


module_init(n2_init);
module_निकास(n2_cleanup);

MODULE_AUTHOR("Krzysztof Halasa <khc@pm.waw.pl>");
MODULE_DESCRIPTION("RISCom/N2 serial port driver");
MODULE_LICENSE("GPL v2");
module_param(hw, अक्षरp, 0444);
MODULE_PARM_DESC(hw, "io,irq,ram,ports:io,irq,...");
