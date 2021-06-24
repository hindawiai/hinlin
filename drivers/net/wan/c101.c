<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Moxa C101 synchronous serial card driver क्रम Linux
 *
 * Copyright (C) 2000-2003 Krzysztof Halasa <khc@pm.waw.pl>
 *
 * For inक्रमmation see <https://www.kernel.org/pub/linux/utils/net/hdlc/>
 *
 * Sources of inक्रमmation:
 *    Hitachi HD64570 SCA User's Manual
 *    Moxa C101 User's Manual
 */

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#समावेश <linux/module.h>
#समावेश <linux/kernel.h>
#समावेश <linux/capability.h>
#समावेश <linux/slab.h>
#समावेश <linux/types.h>
#समावेश <linux/माला.स>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/init.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/hdlc.h>
#समावेश <linux/delay.h>
#समावेश <यंत्र/पन.स>

#समावेश "hd64570.h"


अटल स्थिर अक्षर* version = "Moxa C101 driver version: 1.15";
अटल स्थिर अक्षर* devname = "C101";

#अघोषित DEBUG_PKT
#घोषणा DEBUG_RINGS

#घोषणा C101_PAGE 0x1D00
#घोषणा C101_DTR 0x1E00
#घोषणा C101_SCA 0x1F00
#घोषणा C101_WINDOW_SIZE 0x2000
#घोषणा C101_MAPPED_RAM_SIZE 0x4000

#घोषणा RAM_SIZE (256 * 1024)
#घोषणा TX_RING_BUFFERS 10
#घोषणा RX_RING_BUFFERS ((RAM_SIZE - C101_WINDOW_SIZE) /		\
			 (माप(pkt_desc) + HDLC_MAX_MRU) - TX_RING_BUFFERS)

#घोषणा CLOCK_BASE 9830400	/* 9.8304 MHz */
#घोषणा PAGE0_ALWAYS_MAPPED

अटल अक्षर *hw;		/* poपूर्णांकer to hw=xxx command line string */


प्रकार काष्ठा card_s अणु
	काष्ठा net_device *dev;
	spinlock_t lock;	/* TX lock */
	u8 __iomem *win0base;	/* ISA winकरोw base address */
	u32 phy_winbase;	/* ISA physical base address */
	sync_serial_settings settings;
	पूर्णांक rxpart;		/* partial frame received, next frame invalid*/
	अचिन्हित लघु encoding;
	अचिन्हित लघु parity;
	u16 rx_ring_buffers;	/* number of buffers in a ring */
	u16 tx_ring_buffers;
	u16 buff_offset;	/* offset of first buffer of first channel */
	u16 rxin;		/* rx ring buffer 'in' poपूर्णांकer */
	u16 txin;		/* tx ring buffer 'in' and 'last' poपूर्णांकers */
	u16 txlast;
	u8 rxs, txs, पंचांगc;	/* SCA रेजिस्टरs */
	u8 irq;			/* IRQ (3-15) */
	u8 page;

	काष्ठा card_s *next_card;
पूर्णcard_t;

प्रकार card_t port_t;

अटल card_t *first_card;
अटल card_t **new_card = &first_card;


#घोषणा sca_in(reg, card)	   पढ़ोb((card)->win0base + C101_SCA + (reg))
#घोषणा sca_out(value, reg, card)  ग_लिखोb(value, (card)->win0base + C101_SCA + (reg))
#घोषणा sca_inw(reg, card)	   पढ़ोw((card)->win0base + C101_SCA + (reg))

/* EDA address रेजिस्टर must be set in EDAL, EDAH order - 8 bit ISA bus */
#घोषणा sca_outw(value, reg, card) करो अणु \
	ग_लिखोb(value & 0xFF, (card)->win0base + C101_SCA + (reg)); \
	ग_लिखोb((value >> 8 ) & 0xFF, (card)->win0base + C101_SCA + (reg + 1));\
पूर्ण जबतक(0)

#घोषणा port_to_card(port)	   (port)
#घोषणा log_node(port)		   (0)
#घोषणा phy_node(port)		   (0)
#घोषणा winsize(card)		   (C101_WINDOW_SIZE)
#घोषणा win0base(card)		   ((card)->win0base)
#घोषणा winbase(card)      	   ((card)->win0base + 0x2000)
#घोषणा get_port(card, port)	   (card)
अटल व्योम sca_msci_पूर्णांकr(port_t *port);


अटल अंतरभूत u8 sca_get_page(card_t *card)
अणु
	वापस card->page;
पूर्ण

अटल अंतरभूत व्योम खोलोwin(card_t *card, u8 page)
अणु
	card->page = page;
	ग_लिखोb(page, card->win0base + C101_PAGE);
पूर्ण


#समावेश "hd64570.c"


अटल अंतरभूत व्योम set_carrier(port_t *port)
अणु
	अगर (!(sca_in(MSCI1_OFFSET + ST3, port) & ST3_DCD))
		netअगर_carrier_on(port_to_dev(port));
	अन्यथा
		netअगर_carrier_off(port_to_dev(port));
पूर्ण


अटल व्योम sca_msci_पूर्णांकr(port_t *port)
अणु
	u8 stat = sca_in(MSCI0_OFFSET + ST1, port); /* पढ़ो MSCI ST1 status */

	/* Reset MSCI TX underrun and CDCD (ignored) status bit */
	sca_out(stat & (ST1_UDRN | ST1_CDCD), MSCI0_OFFSET + ST1, port);

	अगर (stat & ST1_UDRN) अणु
		/* TX Underrun error detected */
		port_to_dev(port)->stats.tx_errors++;
		port_to_dev(port)->stats.tx_fअगरo_errors++;
	पूर्ण

	stat = sca_in(MSCI1_OFFSET + ST1, port); /* पढ़ो MSCI1 ST1 status */
	/* Reset MSCI CDCD status bit - uses ch#2 DCD input */
	sca_out(stat & ST1_CDCD, MSCI1_OFFSET + ST1, port);

	अगर (stat & ST1_CDCD)
		set_carrier(port);
पूर्ण


अटल व्योम c101_set_अगरace(port_t *port)
अणु
	u8 rxs = port->rxs & CLK_BRG_MASK;
	u8 txs = port->txs & CLK_BRG_MASK;

	चयन(port->settings.घड़ी_प्रकारype) अणु
	हाल CLOCK_INT:
		rxs |= CLK_BRG_RX; /* TX घड़ी */
		txs |= CLK_RXCLK_TX; /* BRG output */
		अवरोध;

	हाल CLOCK_TXINT:
		rxs |= CLK_LINE_RX; /* RXC input */
		txs |= CLK_BRG_TX; /* BRG output */
		अवरोध;

	हाल CLOCK_TXFROMRX:
		rxs |= CLK_LINE_RX; /* RXC input */
		txs |= CLK_RXCLK_TX; /* RX घड़ी */
		अवरोध;

	शेष:	/* EXTernal घड़ी */
		rxs |= CLK_LINE_RX; /* RXC input */
		txs |= CLK_LINE_TX; /* TXC input */
	पूर्ण

	port->rxs = rxs;
	port->txs = txs;
	sca_out(rxs, MSCI1_OFFSET + RXS, port);
	sca_out(txs, MSCI1_OFFSET + TXS, port);
	sca_set_port(port);
पूर्ण


अटल पूर्णांक c101_खोलो(काष्ठा net_device *dev)
अणु
	port_t *port = dev_to_port(dev);
	पूर्णांक result;

	result = hdlc_खोलो(dev);
	अगर (result)
		वापस result;

	ग_लिखोb(1, port->win0base + C101_DTR);
	sca_out(0, MSCI1_OFFSET + CTL, port); /* RTS uses ch#2 output */
	sca_खोलो(dev);
	/* DCD is connected to port 2 !@#$%^& - disable MSCI0 CDCD पूर्णांकerrupt */
	sca_out(IE1_UDRN, MSCI0_OFFSET + IE1, port);
	sca_out(IE0_TXINT, MSCI0_OFFSET + IE0, port);

	set_carrier(port);

	/* enable MSCI1 CDCD पूर्णांकerrupt */
	sca_out(IE1_CDCD, MSCI1_OFFSET + IE1, port);
	sca_out(IE0_RXINTA, MSCI1_OFFSET + IE0, port);
	sca_out(0x48, IER0, port); /* TXINT #0 and RXINT #1 */
	c101_set_अगरace(port);
	वापस 0;
पूर्ण


अटल पूर्णांक c101_बंद(काष्ठा net_device *dev)
अणु
	port_t *port = dev_to_port(dev);

	sca_बंद(dev);
	ग_लिखोb(0, port->win0base + C101_DTR);
	sca_out(CTL_NORTS, MSCI1_OFFSET + CTL, port);
	hdlc_बंद(dev);
	वापस 0;
पूर्ण


अटल पूर्णांक c101_ioctl(काष्ठा net_device *dev, काष्ठा अगरreq *अगरr, पूर्णांक cmd)
अणु
	स्थिर माप_प्रकार size = माप(sync_serial_settings);
	sync_serial_settings new_line;
	sync_serial_settings __user *line = अगरr->अगरr_settings.अगरs_अगरsu.sync;
	port_t *port = dev_to_port(dev);

#अगर_घोषित DEBUG_RINGS
	अगर (cmd == SIOCDEVPRIVATE) अणु
		sca_dump_rings(dev);
		prपूर्णांकk(KERN_DEBUG "MSCI1: ST: %02x %02x %02x %02x\n",
		       sca_in(MSCI1_OFFSET + ST0, port),
		       sca_in(MSCI1_OFFSET + ST1, port),
		       sca_in(MSCI1_OFFSET + ST2, port),
		       sca_in(MSCI1_OFFSET + ST3, port));
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
		c101_set_अगरace(port);
		वापस 0;

	शेष:
		वापस hdlc_ioctl(dev, अगरr, cmd);
	पूर्ण
पूर्ण



अटल व्योम c101_destroy_card(card_t *card)
अणु
	पढ़ोb(card->win0base + C101_PAGE); /* Resets SCA? */

	अगर (card->irq)
		मुक्त_irq(card->irq, card);

	अगर (card->win0base) अणु
		iounmap(card->win0base);
		release_mem_region(card->phy_winbase, C101_MAPPED_RAM_SIZE);
	पूर्ण

	मुक्त_netdev(card->dev);

	kमुक्त(card);
पूर्ण

अटल स्थिर काष्ठा net_device_ops c101_ops = अणु
	.nकरो_खोलो       = c101_खोलो,
	.nकरो_stop       = c101_बंद,
	.nकरो_start_xmit = hdlc_start_xmit,
	.nकरो_करो_ioctl   = c101_ioctl,
पूर्ण;

अटल पूर्णांक __init c101_run(अचिन्हित दीर्घ irq, अचिन्हित दीर्घ winbase)
अणु
	काष्ठा net_device *dev;
	hdlc_device *hdlc;
	card_t *card;
	पूर्णांक result;

	अगर (irq<3 || irq>15 || irq == 6) /* FIXME */ अणु
		pr_err("invalid IRQ value\n");
		वापस -ENODEV;
	पूर्ण

	अगर (winbase < 0xC0000 || winbase > 0xDFFFF || (winbase & 0x3FFF) !=0) अणु
		pr_err("invalid RAM value\n");
		वापस -ENODEV;
	पूर्ण

	card = kzalloc(माप(card_t), GFP_KERNEL);
	अगर (card == शून्य)
		वापस -ENOBUFS;

	card->dev = alloc_hdlcdev(card);
	अगर (!card->dev) अणु
		pr_err("unable to allocate memory\n");
		kमुक्त(card);
		वापस -ENOBUFS;
	पूर्ण

	अगर (request_irq(irq, sca_पूर्णांकr, 0, devname, card)) अणु
		pr_err("could not allocate IRQ\n");
		c101_destroy_card(card);
		वापस -EBUSY;
	पूर्ण
	card->irq = irq;

	अगर (!request_mem_region(winbase, C101_MAPPED_RAM_SIZE, devname)) अणु
		pr_err("could not request RAM window\n");
		c101_destroy_card(card);
		वापस -EBUSY;
	पूर्ण
	card->phy_winbase = winbase;
	card->win0base = ioremap(winbase, C101_MAPPED_RAM_SIZE);
	अगर (!card->win0base) अणु
		pr_err("could not map I/O address\n");
		c101_destroy_card(card);
		वापस -EFAULT;
	पूर्ण

	card->tx_ring_buffers = TX_RING_BUFFERS;
	card->rx_ring_buffers = RX_RING_BUFFERS;
	card->buff_offset = C101_WINDOW_SIZE; /* Bytes 1D00-1FFF reserved */

	पढ़ोb(card->win0base + C101_PAGE); /* Resets SCA? */
	udelay(100);
	ग_लिखोb(0, card->win0base + C101_PAGE);
	ग_लिखोb(0, card->win0base + C101_DTR); /* Power-up क्रम RAM? */

	sca_init(card, 0);

	dev = port_to_dev(card);
	hdlc = dev_to_hdlc(dev);

	spin_lock_init(&card->lock);
	dev->irq = irq;
	dev->mem_start = winbase;
	dev->mem_end = winbase + C101_MAPPED_RAM_SIZE - 1;
	dev->tx_queue_len = 50;
	dev->netdev_ops = &c101_ops;
	hdlc->attach = sca_attach;
	hdlc->xmit = sca_xmit;
	card->settings.घड़ी_प्रकारype = CLOCK_EXT;

	result = रेजिस्टर_hdlc_device(dev);
	अगर (result) अणु
		pr_warn("unable to register hdlc device\n");
		c101_destroy_card(card);
		वापस result;
	पूर्ण

	sca_init_port(card); /* Set up C101 memory */
	set_carrier(card);

	netdev_info(dev, "Moxa C101 on IRQ%u, using %u TX + %u RX packets rings\n",
		    card->irq, card->tx_ring_buffers, card->rx_ring_buffers);

	*new_card = card;
	new_card = &card->next_card;
	वापस 0;
पूर्ण



अटल पूर्णांक __init c101_init(व्योम)
अणु
	अगर (hw == शून्य) अणु
#अगर_घोषित MODULE
		pr_info("no card initialized\n");
#पूर्ण_अगर
		वापस -EINVAL;	/* no parameters specअगरied, पात */
	पूर्ण

	pr_info("%s\n", version);

	करो अणु
		अचिन्हित दीर्घ irq, ram;

		irq = simple_म_से_अदीर्घ(hw, &hw, 0);

		अगर (*hw++ != ',')
			अवरोध;
		ram = simple_म_से_अदीर्घ(hw, &hw, 0);

		अगर (*hw == ':' || *hw == '\x0')
			c101_run(irq, ram);

		अगर (*hw == '\x0')
			वापस first_card ? 0 : -EINVAL;
	पूर्णजबतक(*hw++ == ':');

	pr_err("invalid hardware parameters\n");
	वापस first_card ? 0 : -EINVAL;
पूर्ण


अटल व्योम __निकास c101_cleanup(व्योम)
अणु
	card_t *card = first_card;

	जबतक (card) अणु
		card_t *ptr = card;
		card = card->next_card;
		unरेजिस्टर_hdlc_device(port_to_dev(ptr));
		c101_destroy_card(ptr);
	पूर्ण
पूर्ण


module_init(c101_init);
module_निकास(c101_cleanup);

MODULE_AUTHOR("Krzysztof Halasa <khc@pm.waw.pl>");
MODULE_DESCRIPTION("Moxa C101 serial port driver");
MODULE_LICENSE("GPL v2");
module_param(hw, अक्षरp, 0444);
MODULE_PARM_DESC(hw, "irq,ram:irq,...");
