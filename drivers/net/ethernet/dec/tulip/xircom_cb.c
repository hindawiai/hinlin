<शैली गुरु>
/*
 * xircom_cb: A driver क्रम the (tulip-like) Xircom Cardbus ethernet cards
 *
 * This software is (C) by the respective authors, and licensed under the GPL
 * License.
 *
 * Written by Arjan van de Ven क्रम Red Hat, Inc.
 * Based on work by Jeff Garzik, Doug Ledक्रमd and Donald Becker
 *
 *  	This software may be used and distributed according to the terms
 *      of the GNU General Public License, incorporated herein by reference.
 *
 *
 * 	$Id: xircom_cb.c,v 1.33 2001/03/19 14:02:07 arjanv Exp $
 */

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#समावेश <linux/module.h>
#समावेश <linux/kernel.h>
#समावेश <linux/माला.स>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/ioport.h>
#समावेश <linux/slab.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/pci.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/etherdevice.h>
#समावेश <linux/skbuff.h>
#समावेश <linux/delay.h>
#समावेश <linux/bitops.h>

#समावेश <linux/uaccess.h>
#समावेश <यंत्र/पन.स>
#अगर_घोषित CONFIG_NET_POLL_CONTROLLER
#समावेश <यंत्र/irq.h>
#पूर्ण_अगर

MODULE_DESCRIPTION("Xircom Cardbus ethernet driver");
MODULE_AUTHOR("Arjan van de Ven <arjanv@redhat.com>");
MODULE_LICENSE("GPL");

#घोषणा xw32(reg, val)	ioग_लिखो32(val, ioaddr + (reg))
#घोषणा xr32(reg)	ioपढ़ो32(ioaddr + (reg))
#घोषणा xr8(reg)	ioपढ़ो8(ioaddr + (reg))

/* IO रेजिस्टरs on the card, offsets */
#घोषणा CSR0	0x00
#घोषणा CSR1	0x08
#घोषणा CSR2	0x10
#घोषणा CSR3	0x18
#घोषणा CSR4	0x20
#घोषणा CSR5	0x28
#घोषणा CSR6	0x30
#घोषणा CSR7	0x38
#घोषणा CSR8	0x40
#घोषणा CSR9	0x48
#घोषणा CSR10	0x50
#घोषणा CSR11	0x58
#घोषणा CSR12	0x60
#घोषणा CSR13	0x68
#घोषणा CSR14	0x70
#घोषणा CSR15	0x78
#घोषणा CSR16	0x80

/* PCI रेजिस्टरs */
#घोषणा PCI_POWERMGMT 	0x40

/* Offsets of the buffers within the descriptor pages, in bytes */

#घोषणा NUMDESCRIPTORS 4

अटल पूर्णांक bufferoffsets[NUMDESCRIPTORS] = अणु128,2048,4096,6144पूर्ण;


काष्ठा xircom_निजी अणु
	/* Send and receive buffers, kernel-addressable and dma addressable क्रमms */

	__le32 *rx_buffer;
	__le32 *tx_buffer;

	dma_addr_t rx_dma_handle;
	dma_addr_t tx_dma_handle;

	काष्ठा sk_buff *tx_skb[4];

	व्योम __iomem *ioaddr;
	पूर्णांक खोलो;

	/* transmit_used is the rotating counter that indicates which transmit
	   descriptor has to be used next */
	पूर्णांक transmit_used;

	/* Spinlock to serialize रेजिस्टर operations.
	   It must be helt जबतक manipulating the following रेजिस्टरs:
	   CSR0, CSR6, CSR7, CSR9, CSR10, CSR15
	 */
	spinlock_t lock;

	काष्ठा pci_dev *pdev;
	काष्ठा net_device *dev;
पूर्ण;


/* Function prototypes */
अटल पूर्णांक xircom_probe(काष्ठा pci_dev *pdev, स्थिर काष्ठा pci_device_id *id);
अटल व्योम xircom_हटाओ(काष्ठा pci_dev *pdev);
अटल irqवापस_t xircom_पूर्णांकerrupt(पूर्णांक irq, व्योम *dev_instance);
अटल netdev_tx_t xircom_start_xmit(काष्ठा sk_buff *skb,
					   काष्ठा net_device *dev);
अटल पूर्णांक xircom_खोलो(काष्ठा net_device *dev);
अटल पूर्णांक xircom_बंद(काष्ठा net_device *dev);
अटल व्योम xircom_up(काष्ठा xircom_निजी *card);
#अगर_घोषित CONFIG_NET_POLL_CONTROLLER
अटल व्योम xircom_poll_controller(काष्ठा net_device *dev);
#पूर्ण_अगर

अटल व्योम investigate_पढ़ो_descriptor(काष्ठा net_device *dev,काष्ठा xircom_निजी *card, पूर्णांक descnr, अचिन्हित पूर्णांक bufferoffset);
अटल व्योम investigate_ग_लिखो_descriptor(काष्ठा net_device *dev, काष्ठा xircom_निजी *card, पूर्णांक descnr, अचिन्हित पूर्णांक bufferoffset);
अटल व्योम पढ़ो_mac_address(काष्ठा xircom_निजी *card);
अटल व्योम transceiver_vooकरोo(काष्ठा xircom_निजी *card);
अटल व्योम initialize_card(काष्ठा xircom_निजी *card);
अटल व्योम trigger_transmit(काष्ठा xircom_निजी *card);
अटल व्योम trigger_receive(काष्ठा xircom_निजी *card);
अटल व्योम setup_descriptors(काष्ठा xircom_निजी *card);
अटल व्योम हटाओ_descriptors(काष्ठा xircom_निजी *card);
अटल पूर्णांक link_status_changed(काष्ठा xircom_निजी *card);
अटल व्योम activate_receiver(काष्ठा xircom_निजी *card);
अटल व्योम deactivate_receiver(काष्ठा xircom_निजी *card);
अटल व्योम activate_transmitter(काष्ठा xircom_निजी *card);
अटल व्योम deactivate_transmitter(काष्ठा xircom_निजी *card);
अटल व्योम enable_transmit_पूर्णांकerrupt(काष्ठा xircom_निजी *card);
अटल व्योम enable_receive_पूर्णांकerrupt(काष्ठा xircom_निजी *card);
अटल व्योम enable_link_पूर्णांकerrupt(काष्ठा xircom_निजी *card);
अटल व्योम disable_all_पूर्णांकerrupts(काष्ठा xircom_निजी *card);
अटल पूर्णांक link_status(काष्ठा xircom_निजी *card);



अटल स्थिर काष्ठा pci_device_id xircom_pci_table[] = अणु
	अणु PCI_VDEVICE(XIRCOM, 0x0003), पूर्ण,
	अणु0,पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(pci, xircom_pci_table);

अटल काष्ठा pci_driver xircom_ops = अणु
	.name		= "xircom_cb",
	.id_table	= xircom_pci_table,
	.probe		= xircom_probe,
	.हटाओ		= xircom_हटाओ,
पूर्ण;


#अगर defined DEBUG && DEBUG > 1
अटल व्योम prपूर्णांक_binary(अचिन्हित पूर्णांक number)
अणु
	पूर्णांक i,i2;
	अक्षर buffer[64];
	स_रखो(buffer,0,64);
	i2=0;
	क्रम (i=31;i>=0;i--) अणु
		अगर (number & (1<<i))
			buffer[i2++]='1';
		अन्यथा
			buffer[i2++]='0';
		अगर ((i&3)==0)
			buffer[i2++]=' ';
	पूर्ण
	pr_debug("%s\n",buffer);
पूर्ण
#पूर्ण_अगर

अटल स्थिर काष्ठा net_device_ops netdev_ops = अणु
	.nकरो_खोलो		= xircom_खोलो,
	.nकरो_stop		= xircom_बंद,
	.nकरो_start_xmit		= xircom_start_xmit,
	.nकरो_set_mac_address	= eth_mac_addr,
	.nकरो_validate_addr	= eth_validate_addr,
#अगर_घोषित CONFIG_NET_POLL_CONTROLLER
	.nकरो_poll_controller	= xircom_poll_controller,
#पूर्ण_अगर
पूर्ण;

/* xircom_probe is the code that माला_लो called on device insertion.
   it sets up the hardware and रेजिस्टरs the device to the networklayer.

   TODO: Send 1 or 2 "dummy" packets here as the card seems to discard the
         first two packets that get send, and pump hates that.

 */
अटल पूर्णांक xircom_probe(काष्ठा pci_dev *pdev, स्थिर काष्ठा pci_device_id *id)
अणु
	काष्ठा device *d = &pdev->dev;
	काष्ठा net_device *dev = शून्य;
	काष्ठा xircom_निजी *निजी;
	अचिन्हित दीर्घ flags;
	अचिन्हित लघु पंचांगp16;
	पूर्णांक rc;

	/* First करो the PCI initialisation */

	rc = pci_enable_device(pdev);
	अगर (rc < 0)
		जाओ out;

	/* disable all घातermanagement */
	pci_ग_लिखो_config_dword(pdev, PCI_POWERMGMT, 0x0000);

	pci_set_master(pdev); /* Why isn't this करोne by pci_enable_device ?*/

	/* clear PCI status, अगर any */
	pci_पढ़ो_config_word (pdev,PCI_STATUS, &पंचांगp16);
	pci_ग_लिखो_config_word (pdev, PCI_STATUS,पंचांगp16);

	rc = pci_request_regions(pdev, "xircom_cb");
	अगर (rc < 0) अणु
		pr_err("%s: failed to allocate io-region\n", __func__);
		जाओ err_disable;
	पूर्ण

	rc = -ENOMEM;
	/*
	   Beक्रमe changing the hardware, allocate the memory.
	   This way, we can fail gracefully अगर not enough memory
	   is available.
	 */
	dev = alloc_etherdev(माप(काष्ठा xircom_निजी));
	अगर (!dev)
		जाओ err_release;

	निजी = netdev_priv(dev);

	/* Allocate the send/receive buffers */
	निजी->rx_buffer = dma_alloc_coherent(d, 8192,
						&निजी->rx_dma_handle,
						GFP_KERNEL);
	अगर (निजी->rx_buffer == शून्य)
		जाओ rx_buf_fail;

	निजी->tx_buffer = dma_alloc_coherent(d, 8192,
						&निजी->tx_dma_handle,
						GFP_KERNEL);
	अगर (निजी->tx_buffer == शून्य)
		जाओ tx_buf_fail;

	SET_NETDEV_DEV(dev, &pdev->dev);


	निजी->dev = dev;
	निजी->pdev = pdev;

	/* IO range. */
	निजी->ioaddr = pci_iomap(pdev, 0, 0);
	अगर (!निजी->ioaddr)
		जाओ reg_fail;

	spin_lock_init(&निजी->lock);

	initialize_card(निजी);
	पढ़ो_mac_address(निजी);
	setup_descriptors(निजी);

	dev->netdev_ops = &netdev_ops;
	pci_set_drvdata(pdev, dev);

	rc = रेजिस्टर_netdev(dev);
	अगर (rc < 0) अणु
		pr_err("%s: netdevice registration failed\n", __func__);
		जाओ err_unmap;
	पूर्ण

	netdev_info(dev, "Xircom cardbus revision %i at irq %i\n",
		    pdev->revision, pdev->irq);
	/* start the transmitter to get a heartbeat */
	/* TODO: send 2 dummy packets here */
	transceiver_vooकरोo(निजी);

	spin_lock_irqsave(&निजी->lock,flags);
	activate_transmitter(निजी);
	activate_receiver(निजी);
	spin_unlock_irqrestore(&निजी->lock,flags);

	trigger_receive(निजी);
out:
	वापस rc;

err_unmap:
	pci_iounmap(pdev, निजी->ioaddr);
reg_fail:
	dma_मुक्त_coherent(d, 8192, निजी->tx_buffer, निजी->tx_dma_handle);
tx_buf_fail:
	dma_मुक्त_coherent(d, 8192, निजी->rx_buffer, निजी->rx_dma_handle);
rx_buf_fail:
	मुक्त_netdev(dev);
err_release:
	pci_release_regions(pdev);
err_disable:
	pci_disable_device(pdev);
	जाओ out;
पूर्ण


/*
 xircom_हटाओ is called on module-unload or on device-eject.
 it unरेजिस्टरs the irq, io-region and network device.
 Interrupts and such are alपढ़ोy stopped in the "ifconfig ethX down"
 code.
 */
अटल व्योम xircom_हटाओ(काष्ठा pci_dev *pdev)
अणु
	काष्ठा net_device *dev = pci_get_drvdata(pdev);
	काष्ठा xircom_निजी *card = netdev_priv(dev);
	काष्ठा device *d = &pdev->dev;

	unरेजिस्टर_netdev(dev);
	pci_iounmap(pdev, card->ioaddr);
	dma_मुक्त_coherent(d, 8192, card->tx_buffer, card->tx_dma_handle);
	dma_मुक्त_coherent(d, 8192, card->rx_buffer, card->rx_dma_handle);
	मुक्त_netdev(dev);
	pci_release_regions(pdev);
	pci_disable_device(pdev);
पूर्ण

अटल irqवापस_t xircom_पूर्णांकerrupt(पूर्णांक irq, व्योम *dev_instance)
अणु
	काष्ठा net_device *dev = (काष्ठा net_device *) dev_instance;
	काष्ठा xircom_निजी *card = netdev_priv(dev);
	व्योम __iomem *ioaddr = card->ioaddr;
	अचिन्हित पूर्णांक status;
	पूर्णांक i;

	spin_lock(&card->lock);
	status = xr32(CSR5);

#अगर defined DEBUG && DEBUG > 1
	prपूर्णांक_binary(status);
	pr_debug("tx status 0x%08x 0x%08x\n",
		 card->tx_buffer[0], card->tx_buffer[4]);
	pr_debug("rx status 0x%08x 0x%08x\n",
		 card->rx_buffer[0], card->rx_buffer[4]);
#पूर्ण_अगर
	/* Handle shared irq and hotplug */
	अगर (status == 0 || status == 0xffffffff) अणु
		spin_unlock(&card->lock);
		वापस IRQ_NONE;
	पूर्ण

	अगर (link_status_changed(card)) अणु
		पूर्णांक newlink;
		netdev_dbg(dev, "Link status has changed\n");
		newlink = link_status(card);
		netdev_info(dev, "Link is %d mbit\n", newlink);
		अगर (newlink)
			netअगर_carrier_on(dev);
		अन्यथा
			netअगर_carrier_off(dev);

	पूर्ण

	/* Clear all reमुख्यing पूर्णांकerrupts */
	status |= 0xffffffff; /* FIXME: make this clear only the
				        real existing bits */
	xw32(CSR5, status);


	क्रम (i=0;i<NUMDESCRIPTORS;i++)
		investigate_ग_लिखो_descriptor(dev,card,i,bufferoffsets[i]);
	क्रम (i=0;i<NUMDESCRIPTORS;i++)
		investigate_पढ़ो_descriptor(dev,card,i,bufferoffsets[i]);

	spin_unlock(&card->lock);
	वापस IRQ_HANDLED;
पूर्ण

अटल netdev_tx_t xircom_start_xmit(काष्ठा sk_buff *skb,
					   काष्ठा net_device *dev)
अणु
	काष्ठा xircom_निजी *card;
	अचिन्हित दीर्घ flags;
	पूर्णांक nextdescriptor;
	पूर्णांक desc;

	card = netdev_priv(dev);
	spin_lock_irqsave(&card->lock,flags);

	/* First see अगर we can मुक्त some descriptors */
	क्रम (desc=0;desc<NUMDESCRIPTORS;desc++)
		investigate_ग_लिखो_descriptor(dev,card,desc,bufferoffsets[desc]);


	nextdescriptor = (card->transmit_used +1) % (NUMDESCRIPTORS);
	desc = card->transmit_used;

	/* only send the packet अगर the descriptor is मुक्त */
	अगर (card->tx_buffer[4*desc]==0) अणु
			/* Copy the packet data; zero the memory first as the card
			   someबार sends more than you ask it to. */

			स_रखो(&card->tx_buffer[bufferoffsets[desc]/4],0,1536);
			skb_copy_from_linear_data(skb,
				  &(card->tx_buffer[bufferoffsets[desc] / 4]),
						  skb->len);
			/* FIXME: The specअगरication tells us that the length we send HAS to be a multiple of
			   4 bytes. */

			card->tx_buffer[4*desc+1] = cpu_to_le32(skb->len);
			अगर (desc == NUMDESCRIPTORS - 1) /* bit 25: last descriptor of the ring */
				card->tx_buffer[4*desc+1] |= cpu_to_le32(1<<25);  

			card->tx_buffer[4*desc+1] |= cpu_to_le32(0xF0000000);
						 /* 0xF0... means want पूर्णांकerrupts*/
			card->tx_skb[desc] = skb;

			wmb();
			/* This gives the descriptor to the card */
			card->tx_buffer[4*desc] = cpu_to_le32(0x80000000);
			trigger_transmit(card);
			अगर (card->tx_buffer[nextdescriptor*4] & cpu_to_le32(0x8000000)) अणु
				/* next descriptor is occupied... */
				netअगर_stop_queue(dev);
			पूर्ण
			card->transmit_used = nextdescriptor;
			spin_unlock_irqrestore(&card->lock,flags);
			वापस NETDEV_TX_OK;
	पूर्ण

	/* Uh oh... no मुक्त descriptor... drop the packet */
	netअगर_stop_queue(dev);
	spin_unlock_irqrestore(&card->lock,flags);
	trigger_transmit(card);

	वापस NETDEV_TX_BUSY;
पूर्ण




अटल पूर्णांक xircom_खोलो(काष्ठा net_device *dev)
अणु
	काष्ठा xircom_निजी *xp = netdev_priv(dev);
	स्थिर पूर्णांक irq = xp->pdev->irq;
	पूर्णांक retval;

	netdev_info(dev, "xircom cardbus adaptor found, using irq %i\n", irq);
	retval = request_irq(irq, xircom_पूर्णांकerrupt, IRQF_SHARED, dev->name, dev);
	अगर (retval)
		वापस retval;

	xircom_up(xp);
	xp->खोलो = 1;

	वापस 0;
पूर्ण

अटल पूर्णांक xircom_बंद(काष्ठा net_device *dev)
अणु
	काष्ठा xircom_निजी *card;
	अचिन्हित दीर्घ flags;

	card = netdev_priv(dev);
	netअगर_stop_queue(dev); /* we करोn't want new packets */


	spin_lock_irqsave(&card->lock,flags);

	disable_all_पूर्णांकerrupts(card);
#अगर 0
	/* We can enable this again once we send dummy packets on अगरconfig ethX up */
	deactivate_receiver(card);
	deactivate_transmitter(card);
#पूर्ण_अगर
	हटाओ_descriptors(card);

	spin_unlock_irqrestore(&card->lock,flags);

	card->खोलो = 0;
	मुक्त_irq(card->pdev->irq, dev);

	वापस 0;

पूर्ण


#अगर_घोषित CONFIG_NET_POLL_CONTROLLER
अटल व्योम xircom_poll_controller(काष्ठा net_device *dev)
अणु
	काष्ठा xircom_निजी *xp = netdev_priv(dev);
	स्थिर पूर्णांक irq = xp->pdev->irq;

	disable_irq(irq);
	xircom_पूर्णांकerrupt(irq, dev);
	enable_irq(irq);
पूर्ण
#पूर्ण_अगर


अटल व्योम initialize_card(काष्ठा xircom_निजी *card)
अणु
	व्योम __iomem *ioaddr = card->ioaddr;
	अचिन्हित दीर्घ flags;
	u32 val;

	spin_lock_irqsave(&card->lock, flags);

	/* First: reset the card */
	val = xr32(CSR0);
	val |= 0x01;		/* Software reset */
	xw32(CSR0, val);

	udelay(100);		/* give the card some समय to reset */

	val = xr32(CSR0);
	val &= ~0x01;		/* disable Software reset */
	xw32(CSR0, val);


	val = 0;		/* Value 0x00 is a safe and conservative value
				   क्रम the PCI configuration settings */
	xw32(CSR0, val);


	disable_all_पूर्णांकerrupts(card);
	deactivate_receiver(card);
	deactivate_transmitter(card);

	spin_unlock_irqrestore(&card->lock, flags);
पूर्ण

/*
trigger_transmit causes the card to check क्रम frames to be transmitted.
This is accomplished by writing to the CSR1 port. The करोcumentation
claims that the act of writing is sufficient and that the value is
ignored; I chose zero.
*/
अटल व्योम trigger_transmit(काष्ठा xircom_निजी *card)
अणु
	व्योम __iomem *ioaddr = card->ioaddr;

	xw32(CSR1, 0);
पूर्ण

/*
trigger_receive causes the card to check क्रम empty frames in the
descriptor list in which packets can be received.
This is accomplished by writing to the CSR2 port. The करोcumentation
claims that the act of writing is sufficient and that the value is
ignored; I chose zero.
*/
अटल व्योम trigger_receive(काष्ठा xircom_निजी *card)
अणु
	व्योम __iomem *ioaddr = card->ioaddr;

	xw32(CSR2, 0);
पूर्ण

/*
setup_descriptors initializes the send and receive buffers to be valid
descriptors and programs the addresses पूर्णांकo the card.
*/
अटल व्योम setup_descriptors(काष्ठा xircom_निजी *card)
अणु
	व्योम __iomem *ioaddr = card->ioaddr;
	u32 address;
	पूर्णांक i;

	BUG_ON(card->rx_buffer == शून्य);
	BUG_ON(card->tx_buffer == शून्य);

	/* Receive descriptors */
	स_रखो(card->rx_buffer, 0, 128);	/* clear the descriptors */
	क्रम (i=0;i<NUMDESCRIPTORS;i++ ) अणु

		/* Rx Descr0: It's empty, let the card own it, no errors -> 0x80000000 */
		card->rx_buffer[i*4 + 0] = cpu_to_le32(0x80000000);
		/* Rx Descr1: buffer 1 is 1536 bytes, buffer 2 is 0 bytes */
		card->rx_buffer[i*4 + 1] = cpu_to_le32(1536);
		अगर (i == NUMDESCRIPTORS - 1) /* bit 25 is "last descriptor" */
			card->rx_buffer[i*4 + 1] |= cpu_to_le32(1 << 25);

		/* Rx Descr2: address of the buffer
		   we store the buffer at the 2nd half of the page */

		address = card->rx_dma_handle;
		card->rx_buffer[i*4 + 2] = cpu_to_le32(address + bufferoffsets[i]);
		/* Rx Desc3: address of 2nd buffer -> 0 */
		card->rx_buffer[i*4 + 3] = 0;
	पूर्ण

	wmb();
	/* Write the receive descriptor ring address to the card */
	address = card->rx_dma_handle;
	xw32(CSR3, address);	/* Receive descr list address */


	/* transmit descriptors */
	स_रखो(card->tx_buffer, 0, 128);	/* clear the descriptors */

	क्रम (i=0;i<NUMDESCRIPTORS;i++ ) अणु
		/* Tx Descr0: Empty, we own it, no errors -> 0x00000000 */
		card->tx_buffer[i*4 + 0] = 0x00000000;
		/* Tx Descr1: buffer 1 is 1536 bytes, buffer 2 is 0 bytes */
		card->tx_buffer[i*4 + 1] = cpu_to_le32(1536);
		अगर (i == NUMDESCRIPTORS - 1) /* bit 25 is "last descriptor" */
			card->tx_buffer[i*4 + 1] |= cpu_to_le32(1 << 25);

		/* Tx Descr2: address of the buffer
		   we store the buffer at the 2nd half of the page */
		address = card->tx_dma_handle;
		card->tx_buffer[i*4 + 2] = cpu_to_le32(address + bufferoffsets[i]);
		/* Tx Desc3: address of 2nd buffer -> 0 */
		card->tx_buffer[i*4 + 3] = 0;
	पूर्ण

	wmb();
	/* wite the transmit descriptor ring to the card */
	address = card->tx_dma_handle;
	xw32(CSR4, address);	/* xmit descr list address */
पूर्ण

/*
हटाओ_descriptors inक्रमms the card the descriptors are no दीर्घer
valid by setting the address in the card to 0x00.
*/
अटल व्योम हटाओ_descriptors(काष्ठा xircom_निजी *card)
अणु
	व्योम __iomem *ioaddr = card->ioaddr;
	अचिन्हित पूर्णांक val;

	val = 0;
	xw32(CSR3, val);	/* Receive descriptor address */
	xw32(CSR4, val);	/* Send descriptor address */
पूर्ण

/*
link_status_changed वापसs 1 अगर the card has indicated that
the link status has changed. The new link status has to be पढ़ो from CSR12.

This function also clears the status-bit.
*/
अटल पूर्णांक link_status_changed(काष्ठा xircom_निजी *card)
अणु
	व्योम __iomem *ioaddr = card->ioaddr;
	अचिन्हित पूर्णांक val;

	val = xr32(CSR5);	/* Status रेजिस्टर */
	अगर (!(val & (1 << 27)))	/* no change */
		वापस 0;

	/* clear the event by writing a 1 to the bit in the
	   status रेजिस्टर. */
	val = (1 << 27);
	xw32(CSR5, val);

	वापस 1;
पूर्ण


/*
transmit_active वापसs 1 अगर the transmitter on the card is
in a non-stopped state.
*/
अटल पूर्णांक transmit_active(काष्ठा xircom_निजी *card)
अणु
	व्योम __iomem *ioaddr = card->ioaddr;

	अगर (!(xr32(CSR5) & (7 << 20)))	/* transmitter disabled */
		वापस 0;

	वापस 1;
पूर्ण

/*
receive_active वापसs 1 अगर the receiver on the card is
in a non-stopped state.
*/
अटल पूर्णांक receive_active(काष्ठा xircom_निजी *card)
अणु
	व्योम __iomem *ioaddr = card->ioaddr;

	अगर (!(xr32(CSR5) & (7 << 17)))	/* receiver disabled */
		वापस 0;

	वापस 1;
पूर्ण

/*
activate_receiver enables the receiver on the card.
Beक्रमe being allowed to active the receiver, the receiver
must be completely de-activated. To achieve this,
this code actually disables the receiver first; then it रुकोs क्रम the
receiver to become inactive, then it activates the receiver and then
it रुकोs क्रम the receiver to be active.

must be called with the lock held and पूर्णांकerrupts disabled.
*/
अटल व्योम activate_receiver(काष्ठा xircom_निजी *card)
अणु
	व्योम __iomem *ioaddr = card->ioaddr;
	अचिन्हित पूर्णांक val;
	पूर्णांक counter;

	val = xr32(CSR6);	/* Operation mode */

	/* If the "active" bit is set and the receiver is alपढ़ोy
	   active, no need to करो the expensive thing */
	अगर ((val&2) && (receive_active(card)))
		वापस;


	val = val & ~2;		/* disable the receiver */
	xw32(CSR6, val);

	counter = 10;
	जबतक (counter > 0) अणु
		अगर (!receive_active(card))
			अवरोध;
		/* रुको a जबतक */
		udelay(50);
		counter--;
		अगर (counter <= 0)
			netdev_err(card->dev, "Receiver failed to deactivate\n");
	पूर्ण

	/* enable the receiver */
	val = xr32(CSR6);	/* Operation mode */
	val = val | 2;		/* enable the receiver */
	xw32(CSR6, val);

	/* now रुको क्रम the card to activate again */
	counter = 10;
	जबतक (counter > 0) अणु
		अगर (receive_active(card))
			अवरोध;
		/* रुको a जबतक */
		udelay(50);
		counter--;
		अगर (counter <= 0)
			netdev_err(card->dev,
				   "Receiver failed to re-activate\n");
	पूर्ण
पूर्ण

/*
deactivate_receiver disables the receiver on the card.
To achieve this this code disables the receiver first;
then it रुकोs क्रम the receiver to become inactive.

must be called with the lock held and पूर्णांकerrupts disabled.
*/
अटल व्योम deactivate_receiver(काष्ठा xircom_निजी *card)
अणु
	व्योम __iomem *ioaddr = card->ioaddr;
	अचिन्हित पूर्णांक val;
	पूर्णांक counter;

	val = xr32(CSR6);	/* Operation mode */
	val = val & ~2;		/* disable the receiver */
	xw32(CSR6, val);

	counter = 10;
	जबतक (counter > 0) अणु
		अगर (!receive_active(card))
			अवरोध;
		/* रुको a जबतक */
		udelay(50);
		counter--;
		अगर (counter <= 0)
			netdev_err(card->dev, "Receiver failed to deactivate\n");
	पूर्ण
पूर्ण


/*
activate_transmitter enables the transmitter on the card.
Beक्रमe being allowed to active the transmitter, the transmitter
must be completely de-activated. To achieve this,
this code actually disables the transmitter first; then it रुकोs क्रम the
transmitter to become inactive, then it activates the transmitter and then
it रुकोs क्रम the transmitter to be active again.

must be called with the lock held and पूर्णांकerrupts disabled.
*/
अटल व्योम activate_transmitter(काष्ठा xircom_निजी *card)
अणु
	व्योम __iomem *ioaddr = card->ioaddr;
	अचिन्हित पूर्णांक val;
	पूर्णांक counter;

	val = xr32(CSR6);	/* Operation mode */

	/* If the "active" bit is set and the receiver is alपढ़ोy
	   active, no need to करो the expensive thing */
	अगर ((val&(1<<13)) && (transmit_active(card)))
		वापस;

	val = val & ~(1 << 13);	/* disable the transmitter */
	xw32(CSR6, val);

	counter = 10;
	जबतक (counter > 0) अणु
		अगर (!transmit_active(card))
			अवरोध;
		/* रुको a जबतक */
		udelay(50);
		counter--;
		अगर (counter <= 0)
			netdev_err(card->dev,
				   "Transmitter failed to deactivate\n");
	पूर्ण

	/* enable the transmitter */
	val = xr32(CSR6);	/* Operation mode */
	val = val | (1 << 13);	/* enable the transmitter */
	xw32(CSR6, val);

	/* now रुको क्रम the card to activate again */
	counter = 10;
	जबतक (counter > 0) अणु
		अगर (transmit_active(card))
			अवरोध;
		/* रुको a जबतक */
		udelay(50);
		counter--;
		अगर (counter <= 0)
			netdev_err(card->dev,
				   "Transmitter failed to re-activate\n");
	पूर्ण
पूर्ण

/*
deactivate_transmitter disables the transmitter on the card.
To achieve this this code disables the transmitter first;
then it रुकोs क्रम the transmitter to become inactive.

must be called with the lock held and पूर्णांकerrupts disabled.
*/
अटल व्योम deactivate_transmitter(काष्ठा xircom_निजी *card)
अणु
	व्योम __iomem *ioaddr = card->ioaddr;
	अचिन्हित पूर्णांक val;
	पूर्णांक counter;

	val = xr32(CSR6);	/* Operation mode */
	val = val & ~2;		/* disable the transmitter */
	xw32(CSR6, val);

	counter = 20;
	जबतक (counter > 0) अणु
		अगर (!transmit_active(card))
			अवरोध;
		/* रुको a जबतक */
		udelay(50);
		counter--;
		अगर (counter <= 0)
			netdev_err(card->dev,
				   "Transmitter failed to deactivate\n");
	पूर्ण
पूर्ण


/*
enable_transmit_पूर्णांकerrupt enables the transmit पूर्णांकerrupt

must be called with the lock held and पूर्णांकerrupts disabled.
*/
अटल व्योम enable_transmit_पूर्णांकerrupt(काष्ठा xircom_निजी *card)
अणु
	व्योम __iomem *ioaddr = card->ioaddr;
	अचिन्हित पूर्णांक val;

	val = xr32(CSR7);	/* Interrupt enable रेजिस्टर */
	val |= 1;		/* enable the transmit पूर्णांकerrupt */
	xw32(CSR7, val);
पूर्ण


/*
enable_receive_पूर्णांकerrupt enables the receive पूर्णांकerrupt

must be called with the lock held and पूर्णांकerrupts disabled.
*/
अटल व्योम enable_receive_पूर्णांकerrupt(काष्ठा xircom_निजी *card)
अणु
	व्योम __iomem *ioaddr = card->ioaddr;
	अचिन्हित पूर्णांक val;

	val = xr32(CSR7);	/* Interrupt enable रेजिस्टर */
	val = val | (1 << 6);	/* enable the receive पूर्णांकerrupt */
	xw32(CSR7, val);
पूर्ण

/*
enable_link_पूर्णांकerrupt enables the link status change पूर्णांकerrupt

must be called with the lock held and पूर्णांकerrupts disabled.
*/
अटल व्योम enable_link_पूर्णांकerrupt(काष्ठा xircom_निजी *card)
अणु
	व्योम __iomem *ioaddr = card->ioaddr;
	अचिन्हित पूर्णांक val;

	val = xr32(CSR7);	/* Interrupt enable रेजिस्टर */
	val = val | (1 << 27);	/* enable the link status chage पूर्णांकerrupt */
	xw32(CSR7, val);
पूर्ण



/*
disable_all_पूर्णांकerrupts disables all पूर्णांकerrupts

must be called with the lock held and पूर्णांकerrupts disabled.
*/
अटल व्योम disable_all_पूर्णांकerrupts(काष्ठा xircom_निजी *card)
अणु
	व्योम __iomem *ioaddr = card->ioaddr;

	xw32(CSR7, 0);
पूर्ण

/*
enable_common_पूर्णांकerrupts enables several weird पूर्णांकerrupts

must be called with the lock held and पूर्णांकerrupts disabled.
*/
अटल व्योम enable_common_पूर्णांकerrupts(काष्ठा xircom_निजी *card)
अणु
	व्योम __iomem *ioaddr = card->ioaddr;
	अचिन्हित पूर्णांक val;

	val = xr32(CSR7);	/* Interrupt enable रेजिस्टर */
	val |= (1<<16); /* Normal Interrupt Summary */
	val |= (1<<15); /* Abnormal Interrupt Summary */
	val |= (1<<13); /* Fatal bus error */
	val |= (1<<8);  /* Receive Process Stopped */
	val |= (1<<7);  /* Receive Buffer Unavailable */
	val |= (1<<5);  /* Transmit Underflow */
	val |= (1<<2);  /* Transmit Buffer Unavailable */
	val |= (1<<1);  /* Transmit Process Stopped */
	xw32(CSR7, val);
पूर्ण

/*
enable_promisc starts promisc mode

must be called with the lock held and पूर्णांकerrupts disabled.
*/
अटल पूर्णांक enable_promisc(काष्ठा xircom_निजी *card)
अणु
	व्योम __iomem *ioaddr = card->ioaddr;
	अचिन्हित पूर्णांक val;

	val = xr32(CSR6);
	val = val | (1 << 6);
	xw32(CSR6, val);

	वापस 1;
पूर्ण




/*
link_status() checks the links status and will वापस 0 क्रम no link, 10 क्रम 10mbit link and 100 क्रम.. guess what.

Must be called in locked state with पूर्णांकerrupts disabled
*/
अटल पूर्णांक link_status(काष्ठा xircom_निजी *card)
अणु
	व्योम __iomem *ioaddr = card->ioaddr;
	u8 val;

	val = xr8(CSR12);

	/* bit 2 is 0 क्रम 10mbit link, 1 क्रम not an 10mbit link */
	अगर (!(val & (1 << 2)))
		वापस 10;
	/* bit 1 is 0 क्रम 100mbit link, 1 क्रम not an 100mbit link */
	अगर (!(val & (1 << 1)))
		वापस 100;

	/* If we get here -> no link at all */

	वापस 0;
पूर्ण





/*
  पढ़ो_mac_address() पढ़ोs the MAC address from the NIC and stores it in the "dev" काष्ठाure.

  This function will take the spinlock itself and can, as a result, not be called with the lock helt.
 */
अटल व्योम पढ़ो_mac_address(काष्ठा xircom_निजी *card)
अणु
	व्योम __iomem *ioaddr = card->ioaddr;
	अचिन्हित दीर्घ flags;
	u8 link;
	पूर्णांक i;

	spin_lock_irqsave(&card->lock, flags);

	xw32(CSR9, 1 << 12);	/* enable boot rom access */
	क्रम (i = 0x100; i < 0x1f7; i += link + 2) अणु
		u8 tuple, data_id, data_count;

		xw32(CSR10, i);
		tuple = xr32(CSR9);
		xw32(CSR10, i + 1);
		link = xr32(CSR9);
		xw32(CSR10, i + 2);
		data_id = xr32(CSR9);
		xw32(CSR10, i + 3);
		data_count = xr32(CSR9);
		अगर ((tuple == 0x22) && (data_id == 0x04) && (data_count == 0x06)) अणु
			पूर्णांक j;

			क्रम (j = 0; j < 6; j++) अणु
				xw32(CSR10, i + j + 4);
				card->dev->dev_addr[j] = xr32(CSR9) & 0xff;
			पूर्ण
			अवरोध;
		पूर्ण अन्यथा अगर (link == 0) अणु
			अवरोध;
		पूर्ण
	पूर्ण
	spin_unlock_irqrestore(&card->lock, flags);
	pr_debug(" %pM\n", card->dev->dev_addr);
पूर्ण


/*
 transceiver_vooकरोo() enables the बाह्यal UTP plug thingy.
 it's called vooकरोo as I stole this code and cannot cross-reference
 it with the specअगरication.
 */
अटल व्योम transceiver_vooकरोo(काष्ठा xircom_निजी *card)
अणु
	व्योम __iomem *ioaddr = card->ioaddr;
	अचिन्हित दीर्घ flags;

	/* disable all घातermanagement */
	pci_ग_लिखो_config_dword(card->pdev, PCI_POWERMGMT, 0x0000);

	setup_descriptors(card);

	spin_lock_irqsave(&card->lock, flags);

	xw32(CSR15, 0x0008);
	udelay(25);
	xw32(CSR15, 0xa8050000);
	udelay(25);
	xw32(CSR15, 0xa00f0000);
	udelay(25);

	spin_unlock_irqrestore(&card->lock, flags);

	netअगर_start_queue(card->dev);
पूर्ण


अटल व्योम xircom_up(काष्ठा xircom_निजी *card)
अणु
	अचिन्हित दीर्घ flags;
	पूर्णांक i;

	/* disable all घातermanagement */
	pci_ग_लिखो_config_dword(card->pdev, PCI_POWERMGMT, 0x0000);

	setup_descriptors(card);

	spin_lock_irqsave(&card->lock, flags);


	enable_link_पूर्णांकerrupt(card);
	enable_transmit_पूर्णांकerrupt(card);
	enable_receive_पूर्णांकerrupt(card);
	enable_common_पूर्णांकerrupts(card);
	enable_promisc(card);

	/* The card can have received packets alपढ़ोy, पढ़ो them away now */
	क्रम (i=0;i<NUMDESCRIPTORS;i++)
		investigate_पढ़ो_descriptor(card->dev,card,i,bufferoffsets[i]);


	spin_unlock_irqrestore(&card->lock, flags);
	trigger_receive(card);
	trigger_transmit(card);
	netअगर_start_queue(card->dev);
पूर्ण

/* Bufferoffset is in BYTES */
अटल व्योम
investigate_पढ़ो_descriptor(काष्ठा net_device *dev, काष्ठा xircom_निजी *card,
			    पूर्णांक descnr, अचिन्हित पूर्णांक bufferoffset)
अणु
	पूर्णांक status;

	status = le32_to_cpu(card->rx_buffer[4*descnr]);

	अगर (status > 0) अणु		/* packet received */

		/* TODO: discard error packets */

		लघु pkt_len = ((status >> 16) & 0x7ff) - 4;
					/* minus 4, we करोn't want the CRC */
		काष्ठा sk_buff *skb;

		अगर (pkt_len > 1518) अणु
			netdev_err(dev, "Packet length %i is bogus\n", pkt_len);
			pkt_len = 1518;
		पूर्ण

		skb = netdev_alloc_skb(dev, pkt_len + 2);
		अगर (skb == शून्य) अणु
			dev->stats.rx_dropped++;
			जाओ out;
		पूर्ण
		skb_reserve(skb, 2);
		skb_copy_to_linear_data(skb,
					&card->rx_buffer[bufferoffset / 4],
					pkt_len);
		skb_put(skb, pkt_len);
		skb->protocol = eth_type_trans(skb, dev);
		netअगर_rx(skb);
		dev->stats.rx_packets++;
		dev->stats.rx_bytes += pkt_len;

out:
		/* give the buffer back to the card */
		card->rx_buffer[4*descnr] = cpu_to_le32(0x80000000);
		trigger_receive(card);
	पूर्ण
पूर्ण


/* Bufferoffset is in BYTES */
अटल व्योम
investigate_ग_लिखो_descriptor(काष्ठा net_device *dev,
			     काष्ठा xircom_निजी *card,
			     पूर्णांक descnr, अचिन्हित पूर्णांक bufferoffset)
अणु
	पूर्णांक status;

	status = le32_to_cpu(card->tx_buffer[4*descnr]);
#अगर 0
	अगर (status & 0x8000) अणु	/* Major error */
		pr_err("Major transmit error status %x\n", status);
		card->tx_buffer[4*descnr] = 0;
		netअगर_wake_queue (dev);
	पूर्ण
#पूर्ण_अगर
	अगर (status > 0) अणु	/* bit 31 is 0 when करोne */
		अगर (card->tx_skb[descnr]!=शून्य) अणु
			dev->stats.tx_bytes += card->tx_skb[descnr]->len;
			dev_kमुक्त_skb_irq(card->tx_skb[descnr]);
		पूर्ण
		card->tx_skb[descnr] = शून्य;
		/* Bit 8 in the status field is 1 अगर there was a collision */
		अगर (status & (1 << 8))
			dev->stats.collisions++;
		card->tx_buffer[4*descnr] = 0; /* descriptor is मुक्त again */
		netअगर_wake_queue (dev);
		dev->stats.tx_packets++;
	पूर्ण
पूर्ण

module_pci_driver(xircom_ops);
