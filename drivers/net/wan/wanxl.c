<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * wanXL serial card driver क्रम Linux
 * host part
 *
 * Copyright (C) 2003 Krzysztof Halasa <khc@pm.waw.pl>
 *
 * Status:
 *   - Only DTE (बाह्यal घड़ी) support with NRZ and NRZI encodings
 *   - wanXL100 will require minor driver modअगरications, no access to hw
 */

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#समावेश <linux/module.h>
#समावेश <linux/kernel.h>
#समावेश <linux/slab.h>
#समावेश <linux/sched.h>
#समावेश <linux/types.h>
#समावेश <linux/fcntl.h>
#समावेश <linux/माला.स>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/init.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/ioport.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/hdlc.h>
#समावेश <linux/pci.h>
#समावेश <linux/dma-mapping.h>
#समावेश <linux/delay.h>
#समावेश <यंत्र/पन.स>

#समावेश "wanxl.h"

अटल स्थिर अक्षर* version = "wanXL serial card driver version: 0.48";

#घोषणा PLX_CTL_RESET   0x40000000 /* adapter reset */

#अघोषित DEBUG_PKT
#अघोषित DEBUG_PCI

/* MAILBOX #1 - PUTS COMMANDS */
#घोषणा MBX1_CMD_ABORTJ 0x85000000 /* Abort and Jump */
#अगर_घोषित __LITTLE_ENDIAN
#घोषणा MBX1_CMD_BSWAP  0x8C000001 /* little-endian Byte Swap Mode */
#अन्यथा
#घोषणा MBX1_CMD_BSWAP  0x8C000000 /* big-endian Byte Swap Mode */
#पूर्ण_अगर

/* MAILBOX #2 - DRAM SIZE */
#घोषणा MBX2_MEMSZ_MASK 0xFFFF0000 /* PUTS Memory Size Register mask */


काष्ठा port अणु
	काष्ठा net_device *dev;
	काष्ठा card *card;
	spinlock_t lock;	/* क्रम wanxl_xmit */
        पूर्णांक node;		/* physical port #0 - 3 */
	अचिन्हित पूर्णांक घड़ी_प्रकारype;
	पूर्णांक tx_in, tx_out;
	काष्ठा sk_buff *tx_skbs[TX_BUFFERS];
पूर्ण;


काष्ठा card_status अणु
	desc_t rx_descs[RX_QUEUE_LENGTH];
	port_status_t port_status[4];
पूर्ण;


काष्ठा card अणु
	पूर्णांक n_ports;		/* 1, 2 or 4 ports */
	u8 irq;

	u8 __iomem *plx;	/* PLX PCI9060 भव base address */
	काष्ठा pci_dev *pdev;	/* क्रम pci_name(pdev) */
	पूर्णांक rx_in;
	काष्ठा sk_buff *rx_skbs[RX_QUEUE_LENGTH];
	काष्ठा card_status *status;	/* shared between host and card */
	dma_addr_t status_address;
	काष्ठा port ports[];	/* 1 - 4 port काष्ठाures follow */
पूर्ण;



अटल अंतरभूत काष्ठा port *dev_to_port(काष्ठा net_device *dev)
अणु
	वापस (काष्ठा port *)dev_to_hdlc(dev)->priv;
पूर्ण


अटल अंतरभूत port_status_t *get_status(काष्ठा port *port)
अणु
	वापस &port->card->status->port_status[port->node];
पूर्ण


#अगर_घोषित DEBUG_PCI
अटल अंतरभूत dma_addr_t pci_map_single_debug(काष्ठा pci_dev *pdev, व्योम *ptr,
					      माप_प्रकार size, पूर्णांक direction)
अणु
	dma_addr_t addr = dma_map_single(&pdev->dev, ptr, size, direction);
	अगर (addr + size > 0x100000000LL)
		pr_crit("%s: pci_map_single() returned memory at 0x%llx!\n",
			pci_name(pdev), (अचिन्हित दीर्घ दीर्घ)addr);
	वापस addr;
पूर्ण

#अघोषित pci_map_single
#घोषणा pci_map_single pci_map_single_debug
#पूर्ण_अगर


/* Cable and/or personality module change पूर्णांकerrupt service */
अटल अंतरभूत व्योम wanxl_cable_पूर्णांकr(काष्ठा port *port)
अणु
	u32 value = get_status(port)->cable;
	पूर्णांक valid = 1;
	स्थिर अक्षर *cable, *pm, *dte = "", *dsr = "", *dcd = "";

	चयन(value & 0x7) अणु
	हाल STATUS_CABLE_V35: cable = "V.35"; अवरोध;
	हाल STATUS_CABLE_X21: cable = "X.21"; अवरोध;
	हाल STATUS_CABLE_V24: cable = "V.24"; अवरोध;
	हाल STATUS_CABLE_EIA530: cable = "EIA530"; अवरोध;
	हाल STATUS_CABLE_NONE: cable = "no"; अवरोध;
	शेष: cable = "invalid";
	पूर्ण

	चयन((value >> STATUS_CABLE_PM_SHIFT) & 0x7) अणु
	हाल STATUS_CABLE_V35: pm = "V.35"; अवरोध;
	हाल STATUS_CABLE_X21: pm = "X.21"; अवरोध;
	हाल STATUS_CABLE_V24: pm = "V.24"; अवरोध;
	हाल STATUS_CABLE_EIA530: pm = "EIA530"; अवरोध;
	हाल STATUS_CABLE_NONE: pm = "no personality"; valid = 0; अवरोध;
	शेष: pm = "invalid personality"; valid = 0;
	पूर्ण

	अगर (valid) अणु
		अगर ((value & 7) == ((value >> STATUS_CABLE_PM_SHIFT) & 7)) अणु
			dsr = (value & STATUS_CABLE_DSR) ? ", DSR ON" :
				", DSR off";
			dcd = (value & STATUS_CABLE_DCD) ? ", carrier ON" :
				", carrier off";
		पूर्ण
		dte = (value & STATUS_CABLE_DCE) ? " DCE" : " DTE";
	पूर्ण
	netdev_info(port->dev, "%s%s module, %s cable%s%s\n",
		    pm, dte, cable, dsr, dcd);

	अगर (value & STATUS_CABLE_DCD)
		netअगर_carrier_on(port->dev);
	अन्यथा
		netअगर_carrier_off(port->dev);
पूर्ण



/* Transmit complete पूर्णांकerrupt service */
अटल अंतरभूत व्योम wanxl_tx_पूर्णांकr(काष्ठा port *port)
अणु
	काष्ठा net_device *dev = port->dev;
	जबतक (1) अणु
                desc_t *desc = &get_status(port)->tx_descs[port->tx_in];
		काष्ठा sk_buff *skb = port->tx_skbs[port->tx_in];

		चयन (desc->stat) अणु
		हाल PACKET_FULL:
		हाल PACKET_EMPTY:
			netअगर_wake_queue(dev);
			वापस;

		हाल PACKET_UNDERRUN:
			dev->stats.tx_errors++;
			dev->stats.tx_fअगरo_errors++;
			अवरोध;

		शेष:
			dev->stats.tx_packets++;
			dev->stats.tx_bytes += skb->len;
		पूर्ण
                desc->stat = PACKET_EMPTY; /* Free descriptor */
		dma_unmap_single(&port->card->pdev->dev, desc->address,
				 skb->len, DMA_TO_DEVICE);
		dev_consume_skb_irq(skb);
                port->tx_in = (port->tx_in + 1) % TX_BUFFERS;
        पूर्ण
पूर्ण



/* Receive complete पूर्णांकerrupt service */
अटल अंतरभूत व्योम wanxl_rx_पूर्णांकr(काष्ठा card *card)
अणु
	desc_t *desc;
	जबतक (desc = &card->status->rx_descs[card->rx_in],
	       desc->stat != PACKET_EMPTY) अणु
		अगर ((desc->stat & PACKET_PORT_MASK) > card->n_ports)
			pr_crit("%s: received packet for nonexistent port\n",
				pci_name(card->pdev));
		अन्यथा अणु
			काष्ठा sk_buff *skb = card->rx_skbs[card->rx_in];
			काष्ठा port *port = &card->ports[desc->stat &
						    PACKET_PORT_MASK];
			काष्ठा net_device *dev = port->dev;

			अगर (!skb)
				dev->stats.rx_dropped++;
			अन्यथा अणु
				dma_unmap_single(&card->pdev->dev,
						 desc->address, BUFFER_LENGTH,
						 DMA_FROM_DEVICE);
				skb_put(skb, desc->length);

#अगर_घोषित DEBUG_PKT
				prपूर्णांकk(KERN_DEBUG "%s RX(%i):", dev->name,
				       skb->len);
				debug_frame(skb);
#पूर्ण_अगर
				dev->stats.rx_packets++;
				dev->stats.rx_bytes += skb->len;
				skb->protocol = hdlc_type_trans(skb, dev);
				netअगर_rx(skb);
				skb = शून्य;
			पूर्ण

			अगर (!skb) अणु
				skb = dev_alloc_skb(BUFFER_LENGTH);
				desc->address = skb ?
					dma_map_single(&card->pdev->dev,
						       skb->data,
						       BUFFER_LENGTH,
						       DMA_FROM_DEVICE) : 0;
				card->rx_skbs[card->rx_in] = skb;
			पूर्ण
		पूर्ण
		desc->stat = PACKET_EMPTY; /* Free descriptor */
		card->rx_in = (card->rx_in + 1) % RX_QUEUE_LENGTH;
	पूर्ण
पूर्ण



अटल irqवापस_t wanxl_पूर्णांकr(पूर्णांक irq, व्योम* dev_id)
अणु
	काष्ठा card *card = dev_id;
        पूर्णांक i;
        u32 stat;
        पूर्णांक handled = 0;


        जबतक((stat = पढ़ोl(card->plx + PLX_DOORBELL_FROM_CARD)) != 0) अणु
                handled = 1;
		ग_लिखोl(stat, card->plx + PLX_DOORBELL_FROM_CARD);

                क्रम (i = 0; i < card->n_ports; i++) अणु
			अगर (stat & (1 << (DOORBELL_FROM_CARD_TX_0 + i)))
				wanxl_tx_पूर्णांकr(&card->ports[i]);
			अगर (stat & (1 << (DOORBELL_FROM_CARD_CABLE_0 + i)))
				wanxl_cable_पूर्णांकr(&card->ports[i]);
		पूर्ण
		अगर (stat & (1 << DOORBELL_FROM_CARD_RX))
			wanxl_rx_पूर्णांकr(card);
        पूर्ण

        वापस IRQ_RETVAL(handled);
पूर्ण



अटल netdev_tx_t wanxl_xmit(काष्ठा sk_buff *skb, काष्ठा net_device *dev)
अणु
	काष्ठा port *port = dev_to_port(dev);
	desc_t *desc;

        spin_lock(&port->lock);

	desc = &get_status(port)->tx_descs[port->tx_out];
        अगर (desc->stat != PACKET_EMPTY) अणु
                /* should never happen - previous xmit should stop queue */
#अगर_घोषित DEBUG_PKT
                prपूर्णांकk(KERN_DEBUG "%s: transmitter buffer full\n", dev->name);
#पूर्ण_अगर
		netअगर_stop_queue(dev);
		spin_unlock(&port->lock);
		वापस NETDEV_TX_BUSY;       /* request packet to be queued */
	पूर्ण

#अगर_घोषित DEBUG_PKT
	prपूर्णांकk(KERN_DEBUG "%s TX(%i):", dev->name, skb->len);
	debug_frame(skb);
#पूर्ण_अगर

	port->tx_skbs[port->tx_out] = skb;
	desc->address = dma_map_single(&port->card->pdev->dev, skb->data,
				       skb->len, DMA_TO_DEVICE);
	desc->length = skb->len;
	desc->stat = PACKET_FULL;
	ग_लिखोl(1 << (DOORBELL_TO_CARD_TX_0 + port->node),
	       port->card->plx + PLX_DOORBELL_TO_CARD);

	port->tx_out = (port->tx_out + 1) % TX_BUFFERS;

	अगर (get_status(port)->tx_descs[port->tx_out].stat != PACKET_EMPTY) अणु
		netअगर_stop_queue(dev);
#अगर_घोषित DEBUG_PKT
		prपूर्णांकk(KERN_DEBUG "%s: transmitter buffer full\n", dev->name);
#पूर्ण_अगर
	पूर्ण

	spin_unlock(&port->lock);
	वापस NETDEV_TX_OK;
पूर्ण



अटल पूर्णांक wanxl_attach(काष्ठा net_device *dev, अचिन्हित लघु encoding,
			अचिन्हित लघु parity)
अणु
	काष्ठा port *port = dev_to_port(dev);

	अगर (encoding != ENCODING_NRZ &&
	    encoding != ENCODING_NRZI)
		वापस -EINVAL;

	अगर (parity != PARITY_NONE &&
	    parity != PARITY_CRC32_PR1_CCITT &&
	    parity != PARITY_CRC16_PR1_CCITT &&
	    parity != PARITY_CRC32_PR0_CCITT &&
	    parity != PARITY_CRC16_PR0_CCITT)
		वापस -EINVAL;

	get_status(port)->encoding = encoding;
	get_status(port)->parity = parity;
	वापस 0;
पूर्ण



अटल पूर्णांक wanxl_ioctl(काष्ठा net_device *dev, काष्ठा अगरreq *अगरr, पूर्णांक cmd)
अणु
	स्थिर माप_प्रकार size = माप(sync_serial_settings);
	sync_serial_settings line;
	काष्ठा port *port = dev_to_port(dev);

	अगर (cmd != SIOCWANDEV)
		वापस hdlc_ioctl(dev, अगरr, cmd);

	चयन (अगरr->अगरr_settings.type) अणु
	हाल IF_GET_IFACE:
		अगरr->अगरr_settings.type = IF_IFACE_SYNC_SERIAL;
		अगर (अगरr->अगरr_settings.size < size) अणु
			अगरr->अगरr_settings.size = size; /* data size wanted */
			वापस -ENOBUFS;
		पूर्ण
		स_रखो(&line, 0, माप(line));
		line.घड़ी_प्रकारype = get_status(port)->घड़ीing;
		line.घड़ी_rate = 0;
		line.loopback = 0;

		अगर (copy_to_user(अगरr->अगरr_settings.अगरs_अगरsu.sync, &line, size))
			वापस -EFAULT;
		वापस 0;

	हाल IF_IFACE_SYNC_SERIAL:
		अगर (!capable(CAP_NET_ADMIN))
			वापस -EPERM;
		अगर (dev->flags & IFF_UP)
			वापस -EBUSY;

		अगर (copy_from_user(&line, अगरr->अगरr_settings.अगरs_अगरsu.sync,
				   size))
			वापस -EFAULT;

		अगर (line.घड़ी_प्रकारype != CLOCK_EXT &&
		    line.घड़ी_प्रकारype != CLOCK_TXFROMRX)
			वापस -EINVAL; /* No such घड़ी setting */

		अगर (line.loopback != 0)
			वापस -EINVAL;

		get_status(port)->घड़ीing = line.घड़ी_प्रकारype;
		वापस 0;

	शेष:
		वापस hdlc_ioctl(dev, अगरr, cmd);
        पूर्ण
पूर्ण



अटल पूर्णांक wanxl_खोलो(काष्ठा net_device *dev)
अणु
	काष्ठा port *port = dev_to_port(dev);
	u8 __iomem *dbr = port->card->plx + PLX_DOORBELL_TO_CARD;
	अचिन्हित दीर्घ समयout;
	पूर्णांक i;

	अगर (get_status(port)->खोलो) अणु
		netdev_err(dev, "port already open\n");
		वापस -EIO;
	पूर्ण
	अगर ((i = hdlc_खोलो(dev)) != 0)
		वापस i;

	port->tx_in = port->tx_out = 0;
	क्रम (i = 0; i < TX_BUFFERS; i++)
		get_status(port)->tx_descs[i].stat = PACKET_EMPTY;
	/* संकेत the card */
	ग_लिखोl(1 << (DOORBELL_TO_CARD_OPEN_0 + port->node), dbr);

	समयout = jअगरfies + HZ;
	करो अणु
		अगर (get_status(port)->खोलो) अणु
			netअगर_start_queue(dev);
			वापस 0;
		पूर्ण
	पूर्ण जबतक (समय_after(समयout, jअगरfies));

	netdev_err(dev, "unable to open port\n");
	/* ask the card to बंद the port, should it be still alive */
	ग_लिखोl(1 << (DOORBELL_TO_CARD_CLOSE_0 + port->node), dbr);
	वापस -EFAULT;
पूर्ण



अटल पूर्णांक wanxl_बंद(काष्ठा net_device *dev)
अणु
	काष्ठा port *port = dev_to_port(dev);
	अचिन्हित दीर्घ समयout;
	पूर्णांक i;

	hdlc_बंद(dev);
	/* संकेत the card */
	ग_लिखोl(1 << (DOORBELL_TO_CARD_CLOSE_0 + port->node),
	       port->card->plx + PLX_DOORBELL_TO_CARD);

	समयout = jअगरfies + HZ;
	करो अणु
		अगर (!get_status(port)->खोलो)
			अवरोध;
	पूर्ण जबतक (समय_after(समयout, jअगरfies));

	अगर (get_status(port)->खोलो)
		netdev_err(dev, "unable to close port\n");

	netअगर_stop_queue(dev);

	क्रम (i = 0; i < TX_BUFFERS; i++) अणु
		desc_t *desc = &get_status(port)->tx_descs[i];

		अगर (desc->stat != PACKET_EMPTY) अणु
			desc->stat = PACKET_EMPTY;
			dma_unmap_single(&port->card->pdev->dev,
					 desc->address, port->tx_skbs[i]->len,
					 DMA_TO_DEVICE);
			dev_kमुक्त_skb(port->tx_skbs[i]);
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण



अटल काष्ठा net_device_stats *wanxl_get_stats(काष्ठा net_device *dev)
अणु
	काष्ठा port *port = dev_to_port(dev);

	dev->stats.rx_over_errors = get_status(port)->rx_overruns;
	dev->stats.rx_frame_errors = get_status(port)->rx_frame_errors;
	dev->stats.rx_errors = dev->stats.rx_over_errors +
		dev->stats.rx_frame_errors;
	वापस &dev->stats;
पूर्ण



अटल पूर्णांक wanxl_माला_दो_command(काष्ठा card *card, u32 cmd)
अणु
	अचिन्हित दीर्घ समयout = jअगरfies + 5 * HZ;

	ग_लिखोl(cmd, card->plx + PLX_MAILBOX_1);
	करो अणु
		अगर (पढ़ोl(card->plx + PLX_MAILBOX_1) == 0)
			वापस 0;

		schedule();
	पूर्णजबतक (समय_after(समयout, jअगरfies));

	वापस -1;
पूर्ण



अटल व्योम wanxl_reset(काष्ठा card *card)
अणु
	u32 old_value = पढ़ोl(card->plx + PLX_CONTROL) & ~PLX_CTL_RESET;

	ग_लिखोl(0x80, card->plx + PLX_MAILBOX_0);
	ग_लिखोl(old_value | PLX_CTL_RESET, card->plx + PLX_CONTROL);
	पढ़ोl(card->plx + PLX_CONTROL); /* रुको क्रम posted ग_लिखो */
	udelay(1);
	ग_लिखोl(old_value, card->plx + PLX_CONTROL);
	पढ़ोl(card->plx + PLX_CONTROL); /* रुको क्रम posted ग_लिखो */
पूर्ण



अटल व्योम wanxl_pci_हटाओ_one(काष्ठा pci_dev *pdev)
अणु
	काष्ठा card *card = pci_get_drvdata(pdev);
	पूर्णांक i;

	क्रम (i = 0; i < card->n_ports; i++) अणु
		unरेजिस्टर_hdlc_device(card->ports[i].dev);
		मुक्त_netdev(card->ports[i].dev);
	पूर्ण

	/* unरेजिस्टर and मुक्त all host resources */
	अगर (card->irq)
		मुक्त_irq(card->irq, card);

	wanxl_reset(card);

	क्रम (i = 0; i < RX_QUEUE_LENGTH; i++)
		अगर (card->rx_skbs[i]) अणु
			dma_unmap_single(&card->pdev->dev,
					 card->status->rx_descs[i].address,
					 BUFFER_LENGTH, DMA_FROM_DEVICE);
			dev_kमुक्त_skb(card->rx_skbs[i]);
		पूर्ण

	अगर (card->plx)
		iounmap(card->plx);

	अगर (card->status)
		dma_मुक्त_coherent(&pdev->dev, माप(काष्ठा card_status),
				  card->status, card->status_address);

	pci_release_regions(pdev);
	pci_disable_device(pdev);
	kमुक्त(card);
पूर्ण


#समावेश "wanxlfw.inc"

अटल स्थिर काष्ठा net_device_ops wanxl_ops = अणु
	.nकरो_खोलो       = wanxl_खोलो,
	.nकरो_stop       = wanxl_बंद,
	.nकरो_start_xmit = hdlc_start_xmit,
	.nकरो_करो_ioctl   = wanxl_ioctl,
	.nकरो_get_stats  = wanxl_get_stats,
पूर्ण;

अटल पूर्णांक wanxl_pci_init_one(काष्ठा pci_dev *pdev,
			      स्थिर काष्ठा pci_device_id *ent)
अणु
	काष्ठा card *card;
	u32 ramsize, stat;
	अचिन्हित दीर्घ समयout;
	u32 plx_phy;		/* PLX PCI base address */
	u32 mem_phy;		/* memory PCI base addr */
	u8 __iomem *mem;	/* memory भव base addr */
	पूर्णांक i, ports;

#अगर_अघोषित MODULE
	pr_info_once("%s\n", version);
#पूर्ण_अगर

	i = pci_enable_device(pdev);
	अगर (i)
		वापस i;

	/* QUICC can only access first 256 MB of host RAM directly,
	   but PLX9060 DMA करोes 32-bits क्रम actual packet data transfers */

	/* FIXME when PCI/DMA subप्रणालीs are fixed.
	   We set both dma_mask and consistent_dma_mask to 28 bits
	   and pray pci_alloc_consistent() will use this info. It should
	   work on most platक्रमms */
	अगर (dma_set_coherent_mask(&pdev->dev, DMA_BIT_MASK(28)) ||
	    dma_set_mask(&pdev->dev, DMA_BIT_MASK(28))) अणु
		pr_err("No usable DMA configuration\n");
		pci_disable_device(pdev);
		वापस -EIO;
	पूर्ण

	i = pci_request_regions(pdev, "wanXL");
	अगर (i) अणु
		pci_disable_device(pdev);
		वापस i;
	पूर्ण

	चयन (pdev->device) अणु
	हाल PCI_DEVICE_ID_SBE_WANXL100: ports = 1; अवरोध;
	हाल PCI_DEVICE_ID_SBE_WANXL200: ports = 2; अवरोध;
	शेष: ports = 4;
	पूर्ण

	card = kzalloc(काष्ठा_size(card, ports, ports), GFP_KERNEL);
	अगर (card == शून्य) अणु
		pci_release_regions(pdev);
		pci_disable_device(pdev);
		वापस -ENOBUFS;
	पूर्ण

	pci_set_drvdata(pdev, card);
	card->pdev = pdev;

	card->status = dma_alloc_coherent(&pdev->dev,
					  माप(काष्ठा card_status),
					  &card->status_address, GFP_KERNEL);
	अगर (card->status == शून्य) अणु
		wanxl_pci_हटाओ_one(pdev);
		वापस -ENOBUFS;
	पूर्ण

#अगर_घोषित DEBUG_PCI
	prपूर्णांकk(KERN_DEBUG "wanXL %s: pci_alloc_consistent() returned memory"
	       " at 0x%LX\n", pci_name(pdev),
	       (अचिन्हित दीर्घ दीर्घ)card->status_address);
#पूर्ण_अगर

	/* FIXME when PCI/DMA subप्रणालीs are fixed.
	   We set both dma_mask and consistent_dma_mask back to 32 bits
	   to indicate the card can करो 32-bit DMA addressing */
	अगर (dma_set_coherent_mask(&pdev->dev, DMA_BIT_MASK(32)) ||
	    dma_set_mask(&pdev->dev, DMA_BIT_MASK(32))) अणु
		pr_err("No usable DMA configuration\n");
		wanxl_pci_हटाओ_one(pdev);
		वापस -EIO;
	पूर्ण

	/* set up PLX mapping */
	plx_phy = pci_resource_start(pdev, 0);

	card->plx = ioremap(plx_phy, 0x70);
	अगर (!card->plx) अणु
		pr_err("ioremap() failed\n");
 		wanxl_pci_हटाओ_one(pdev);
		वापस -EFAULT;
	पूर्ण

#अगर RESET_WHILE_LOADING
	wanxl_reset(card);
#पूर्ण_अगर

	समयout = jअगरfies + 20 * HZ;
	जबतक ((stat = पढ़ोl(card->plx + PLX_MAILBOX_0)) != 0) अणु
		अगर (समय_beक्रमe(समयout, jअगरfies)) अणु
			pr_warn("%s: timeout waiting for PUTS to complete\n",
				pci_name(pdev));
			wanxl_pci_हटाओ_one(pdev);
			वापस -ENODEV;
		पूर्ण

		चयन(stat & 0xC0) अणु
		हाल 0x00:	/* hmm - PUTS completed with non-zero code? */
		हाल 0x80:	/* PUTS still testing the hardware */
			अवरोध;

		शेष:
			pr_warn("%s: PUTS test 0x%X failed\n",
				pci_name(pdev), stat & 0x30);
			wanxl_pci_हटाओ_one(pdev);
			वापस -ENODEV;
		पूर्ण

		schedule();
	पूर्ण

	/* get on-board memory size (PUTS detects no more than 4 MB) */
	ramsize = पढ़ोl(card->plx + PLX_MAILBOX_2) & MBX2_MEMSZ_MASK;

	/* set up on-board RAM mapping */
	mem_phy = pci_resource_start(pdev, 2);


	/* sanity check the board's reported memory size */
	अगर (ramsize < BUFFERS_ADDR +
	    (TX_BUFFERS + RX_BUFFERS) * BUFFER_LENGTH * ports) अणु
		pr_warn("%s: no enough on-board RAM (%u bytes detected, %u bytes required)\n",
			pci_name(pdev), ramsize,
			BUFFERS_ADDR +
			(TX_BUFFERS + RX_BUFFERS) * BUFFER_LENGTH * ports);
		wanxl_pci_हटाओ_one(pdev);
		वापस -ENODEV;
	पूर्ण

	अगर (wanxl_माला_दो_command(card, MBX1_CMD_BSWAP)) अणु
		pr_warn("%s: unable to Set Byte Swap Mode\n", pci_name(pdev));
		wanxl_pci_हटाओ_one(pdev);
		वापस -ENODEV;
	पूर्ण

	क्रम (i = 0; i < RX_QUEUE_LENGTH; i++) अणु
		काष्ठा sk_buff *skb = dev_alloc_skb(BUFFER_LENGTH);
		card->rx_skbs[i] = skb;
		अगर (skb)
			card->status->rx_descs[i].address =
				dma_map_single(&card->pdev->dev, skb->data,
					       BUFFER_LENGTH, DMA_FROM_DEVICE);
	पूर्ण

	mem = ioremap(mem_phy, PDM_OFFSET + माप(firmware));
	अगर (!mem) अणु
		pr_err("ioremap() failed\n");
 		wanxl_pci_हटाओ_one(pdev);
		वापस -EFAULT;
	पूर्ण

	क्रम (i = 0; i < माप(firmware); i += 4)
		ग_लिखोl(ntohl(*(__be32*)(firmware + i)), mem + PDM_OFFSET + i);

	क्रम (i = 0; i < ports; i++)
		ग_लिखोl(card->status_address +
		       (व्योम *)&card->status->port_status[i] -
		       (व्योम *)card->status, mem + PDM_OFFSET + 4 + i * 4);
	ग_लिखोl(card->status_address, mem + PDM_OFFSET + 20);
	ग_लिखोl(PDM_OFFSET, mem);
	iounmap(mem);

	ग_लिखोl(0, card->plx + PLX_MAILBOX_5);

	अगर (wanxl_माला_दो_command(card, MBX1_CMD_ABORTJ)) अणु
		pr_warn("%s: unable to Abort and Jump\n", pci_name(pdev));
		wanxl_pci_हटाओ_one(pdev);
		वापस -ENODEV;
	पूर्ण

	समयout = jअगरfies + 5 * HZ;
	करो अणु
		अगर ((stat = पढ़ोl(card->plx + PLX_MAILBOX_5)) != 0)
			अवरोध;
		schedule();
	पूर्णजबतक (समय_after(समयout, jअगरfies));

	अगर (!stat) अणु
		pr_warn("%s: timeout while initializing card firmware\n",
			pci_name(pdev));
		wanxl_pci_हटाओ_one(pdev);
		वापस -ENODEV;
	पूर्ण

#अगर DETECT_RAM
	ramsize = stat;
#पूर्ण_अगर

	pr_info("%s: at 0x%X, %u KB of RAM at 0x%X, irq %u\n",
		pci_name(pdev), plx_phy, ramsize / 1024, mem_phy, pdev->irq);

	/* Allocate IRQ */
	अगर (request_irq(pdev->irq, wanxl_पूर्णांकr, IRQF_SHARED, "wanXL", card)) अणु
		pr_warn("%s: could not allocate IRQ%i\n",
			pci_name(pdev), pdev->irq);
		wanxl_pci_हटाओ_one(pdev);
		वापस -EBUSY;
	पूर्ण
	card->irq = pdev->irq;

	क्रम (i = 0; i < ports; i++) अणु
		hdlc_device *hdlc;
		काष्ठा port *port = &card->ports[i];
		काष्ठा net_device *dev = alloc_hdlcdev(port);
		अगर (!dev) अणु
			pr_err("%s: unable to allocate memory\n",
			       pci_name(pdev));
			wanxl_pci_हटाओ_one(pdev);
			वापस -ENOMEM;
		पूर्ण

		port->dev = dev;
		hdlc = dev_to_hdlc(dev);
		spin_lock_init(&port->lock);
		dev->tx_queue_len = 50;
		dev->netdev_ops = &wanxl_ops;
		hdlc->attach = wanxl_attach;
		hdlc->xmit = wanxl_xmit;
		port->card = card;
		port->node = i;
		get_status(port)->घड़ीing = CLOCK_EXT;
		अगर (रेजिस्टर_hdlc_device(dev)) अणु
			pr_err("%s: unable to register hdlc device\n",
			       pci_name(pdev));
			मुक्त_netdev(dev);
			wanxl_pci_हटाओ_one(pdev);
			वापस -ENOBUFS;
		पूर्ण
		card->n_ports++;
	पूर्ण

	pr_info("%s: port", pci_name(pdev));
	क्रम (i = 0; i < ports; i++)
		pr_cont("%s #%i: %s",
			i ? "," : "", i, card->ports[i].dev->name);
	pr_cont("\n");

	क्रम (i = 0; i < ports; i++)
		wanxl_cable_पूर्णांकr(&card->ports[i]); /* get carrier status etc.*/

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा pci_device_id wanxl_pci_tbl[] = अणु
	अणु PCI_VENDOR_ID_SBE, PCI_DEVICE_ID_SBE_WANXL100, PCI_ANY_ID,
	  PCI_ANY_ID, 0, 0, 0 पूर्ण,
	अणु PCI_VENDOR_ID_SBE, PCI_DEVICE_ID_SBE_WANXL200, PCI_ANY_ID,
	  PCI_ANY_ID, 0, 0, 0 पूर्ण,
	अणु PCI_VENDOR_ID_SBE, PCI_DEVICE_ID_SBE_WANXL400, PCI_ANY_ID,
	  PCI_ANY_ID, 0, 0, 0 पूर्ण,
	अणु 0, पूर्ण
पूर्ण;


अटल काष्ठा pci_driver wanxl_pci_driver = अणु
	.name		= "wanXL",
	.id_table	= wanxl_pci_tbl,
	.probe		= wanxl_pci_init_one,
	.हटाओ		= wanxl_pci_हटाओ_one,
पूर्ण;


अटल पूर्णांक __init wanxl_init_module(व्योम)
अणु
#अगर_घोषित MODULE
	pr_info("%s\n", version);
#पूर्ण_अगर
	वापस pci_रेजिस्टर_driver(&wanxl_pci_driver);
पूर्ण

अटल व्योम __निकास wanxl_cleanup_module(व्योम)
अणु
	pci_unरेजिस्टर_driver(&wanxl_pci_driver);
पूर्ण


MODULE_AUTHOR("Krzysztof Halasa <khc@pm.waw.pl>");
MODULE_DESCRIPTION("SBE Inc. wanXL serial port driver");
MODULE_LICENSE("GPL v2");
MODULE_DEVICE_TABLE(pci, wanxl_pci_tbl);

module_init(wanxl_init_module);
module_निकास(wanxl_cleanup_module);
