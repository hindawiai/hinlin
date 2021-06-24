<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *	Sealevel Systems 4021 driver.
 *
 *	(c) Copyright 1999, 2001 Alan Cox
 *	(c) Copyright 2001 Red Hat Inc.
 *	Generic HDLC port Copyright (C) 2008 Krzysztof Halasa <khc@pm.waw.pl>
 */

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#समावेश <linux/module.h>
#समावेश <linux/kernel.h>
#समावेश <linux/mm.h>
#समावेश <linux/net.h>
#समावेश <linux/skbuff.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/अगर_arp.h>
#समावेश <linux/delay.h>
#समावेश <linux/hdlc.h>
#समावेश <linux/ioport.h>
#समावेश <linux/init.h>
#समावेश <linux/slab.h>
#समावेश <net/arp.h>

#समावेश <यंत्र/irq.h>
#समावेश <यंत्र/पन.स>
#समावेश <यंत्र/dma.h>
#समावेश <यंत्र/byteorder.h>
#समावेश "z85230.h"


काष्ठा slvl_device
अणु
	काष्ठा z8530_channel *chan;
	पूर्णांक channel;
पूर्ण;


काष्ठा slvl_board
अणु
	काष्ठा slvl_device dev[2];
	काष्ठा z8530_dev board;
	पूर्णांक iobase;
पूर्ण;

/*
 *	Network driver support routines
 */

अटल अंतरभूत काष्ठा slvl_device* dev_to_chan(काष्ठा net_device *dev)
अणु
	वापस (काष्ठा slvl_device *)dev_to_hdlc(dev)->priv;
पूर्ण

/*
 *	Frame receive. Simple क्रम our card as we करो HDLC and there
 *	is no funny garbage involved
 */

अटल व्योम sealevel_input(काष्ठा z8530_channel *c, काष्ठा sk_buff *skb)
अणु
	/* Drop the CRC - it's not a good idea to try and negotiate it ;) */
	skb_trim(skb, skb->len - 2);
	skb->protocol = hdlc_type_trans(skb, c->netdevice);
	skb_reset_mac_header(skb);
	skb->dev = c->netdevice;
	netअगर_rx(skb);
पूर्ण

/*
 *	We've been placed in the UP state
 */

अटल पूर्णांक sealevel_खोलो(काष्ठा net_device *d)
अणु
	काष्ठा slvl_device *slvl = dev_to_chan(d);
	पूर्णांक err = -1;
	पूर्णांक unit = slvl->channel;

	/*
	 *	Link layer up.
	 */

	चयन (unit) अणु
		हाल 0:
			err = z8530_sync_dma_खोलो(d, slvl->chan);
			अवरोध;
		हाल 1:
			err = z8530_sync_खोलो(d, slvl->chan);
			अवरोध;
	पूर्ण

	अगर (err)
		वापस err;

	err = hdlc_खोलो(d);
	अगर (err) अणु
		चयन (unit) अणु
			हाल 0:
				z8530_sync_dma_बंद(d, slvl->chan);
				अवरोध;
			हाल 1:
				z8530_sync_बंद(d, slvl->chan);
				अवरोध;
		पूर्ण
		वापस err;
	पूर्ण

	slvl->chan->rx_function = sealevel_input;

	/*
	 *	Go go go
	 */
	netअगर_start_queue(d);
	वापस 0;
पूर्ण

अटल पूर्णांक sealevel_बंद(काष्ठा net_device *d)
अणु
	काष्ठा slvl_device *slvl = dev_to_chan(d);
	पूर्णांक unit = slvl->channel;

	/*
	 *	Discard new frames
	 */

	slvl->chan->rx_function = z8530_null_rx;

	hdlc_बंद(d);
	netअगर_stop_queue(d);

	चयन (unit) अणु
		हाल 0:
			z8530_sync_dma_बंद(d, slvl->chan);
			अवरोध;
		हाल 1:
			z8530_sync_बंद(d, slvl->chan);
			अवरोध;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक sealevel_ioctl(काष्ठा net_device *d, काष्ठा अगरreq *अगरr, पूर्णांक cmd)
अणु
	/* काष्ठा slvl_device *slvl=dev_to_chan(d);
	   z8530_ioctl(d,&slvl->sync.chanA,अगरr,cmd) */
	वापस hdlc_ioctl(d, अगरr, cmd);
पूर्ण

/*
 *	Passed network frames, fire them करोwnwind.
 */

अटल netdev_tx_t sealevel_queue_xmit(काष्ठा sk_buff *skb,
					     काष्ठा net_device *d)
अणु
	वापस z8530_queue_xmit(dev_to_chan(d)->chan, skb);
पूर्ण

अटल पूर्णांक sealevel_attach(काष्ठा net_device *dev, अचिन्हित लघु encoding,
			   अचिन्हित लघु parity)
अणु
	अगर (encoding == ENCODING_NRZ && parity == PARITY_CRC16_PR1_CCITT)
		वापस 0;
	वापस -EINVAL;
पूर्ण

अटल स्थिर काष्ठा net_device_ops sealevel_ops = अणु
	.nकरो_खोलो       = sealevel_खोलो,
	.nकरो_stop       = sealevel_बंद,
	.nकरो_start_xmit = hdlc_start_xmit,
	.nकरो_करो_ioctl   = sealevel_ioctl,
पूर्ण;

अटल पूर्णांक slvl_setup(काष्ठा slvl_device *sv, पूर्णांक iobase, पूर्णांक irq)
अणु
	काष्ठा net_device *dev = alloc_hdlcdev(sv);
	अगर (!dev)
		वापस -1;

	dev_to_hdlc(dev)->attach = sealevel_attach;
	dev_to_hdlc(dev)->xmit = sealevel_queue_xmit;
	dev->netdev_ops = &sealevel_ops;
	dev->base_addr = iobase;
	dev->irq = irq;

	अगर (रेजिस्टर_hdlc_device(dev)) अणु
		pr_err("unable to register HDLC device\n");
		मुक्त_netdev(dev);
		वापस -1;
	पूर्ण

	sv->chan->netdevice = dev;
	वापस 0;
पूर्ण


/*
 *	Allocate and setup Sealevel board.
 */

अटल __init काष्ठा slvl_board *slvl_init(पूर्णांक iobase, पूर्णांक irq,
					   पूर्णांक txdma, पूर्णांक rxdma, पूर्णांक slow)
अणु
	काष्ठा z8530_dev *dev;
	काष्ठा slvl_board *b;

	/*
	 *	Get the needed I/O space
	 */

	अगर (!request_region(iobase, 8, "Sealevel 4021")) अणु
		pr_warn("I/O 0x%X already in use\n", iobase);
		वापस शून्य;
	पूर्ण

	b = kzalloc(माप(काष्ठा slvl_board), GFP_KERNEL);
	अगर (!b)
		जाओ err_kzalloc;

	b->dev[0].chan = &b->board.chanA;
	b->dev[0].channel = 0;

	b->dev[1].chan = &b->board.chanB;
	b->dev[1].channel = 1;

	dev = &b->board;

	/*
	 *	Stuff in the I/O addressing
	 */

	dev->active = 0;

	b->iobase = iobase;

	/*
	 *	Select 8530 delays क्रम the old board
	 */

	अगर (slow)
		iobase |= Z8530_PORT_SLEEP;

	dev->chanA.ctrlio = iobase + 1;
	dev->chanA.dataio = iobase;
	dev->chanB.ctrlio = iobase + 3;
	dev->chanB.dataio = iobase + 2;

	dev->chanA.irqs = &z8530_nop;
	dev->chanB.irqs = &z8530_nop;

	/*
	 *	Assert DTR enable DMA
	 */

	outb(3 | (1 << 7), b->iobase + 4);


	/* We want a fast IRQ क्रम this device. Actually we'd like an even faster
	   IRQ ;) - This is one driver RtLinux is made क्रम */

	अगर (request_irq(irq, z8530_पूर्णांकerrupt, 0,
			"SeaLevel", dev) < 0) अणु
		pr_warn("IRQ %d already in use\n", irq);
		जाओ err_request_irq;
	पूर्ण

	dev->irq = irq;
	dev->chanA.निजी = &b->dev[0];
	dev->chanB.निजी = &b->dev[1];
	dev->chanA.dev = dev;
	dev->chanB.dev = dev;

	dev->chanA.txdma = 3;
	dev->chanA.rxdma = 1;
	अगर (request_dma(dev->chanA.txdma, "SeaLevel (TX)"))
		जाओ err_dma_tx;

	अगर (request_dma(dev->chanA.rxdma, "SeaLevel (RX)"))
		जाओ err_dma_rx;

	disable_irq(irq);

	/*
	 *	Begin normal initialise
	 */

	अगर (z8530_init(dev) != 0) अणु
		pr_err("Z8530 series device not found\n");
		enable_irq(irq);
		जाओ मुक्त_hw;
	पूर्ण
	अगर (dev->type == Z85C30) अणु
		z8530_channel_load(&dev->chanA, z8530_hdlc_kilostream);
		z8530_channel_load(&dev->chanB, z8530_hdlc_kilostream);
	पूर्ण अन्यथा अणु
		z8530_channel_load(&dev->chanA, z8530_hdlc_kilostream_85230);
		z8530_channel_load(&dev->chanB, z8530_hdlc_kilostream_85230);
	पूर्ण

	/*
	 *	Now we can take the IRQ
	 */

	enable_irq(irq);

	अगर (slvl_setup(&b->dev[0], iobase, irq))
		जाओ मुक्त_hw;
	अगर (slvl_setup(&b->dev[1], iobase, irq))
		जाओ मुक्त_netdev0;

	z8530_describe(dev, "I/O", iobase);
	dev->active = 1;
	वापस b;

मुक्त_netdev0:
	unरेजिस्टर_hdlc_device(b->dev[0].chan->netdevice);
	मुक्त_netdev(b->dev[0].chan->netdevice);
मुक्त_hw:
	मुक्त_dma(dev->chanA.rxdma);
err_dma_rx:
	मुक्त_dma(dev->chanA.txdma);
err_dma_tx:
	मुक्त_irq(irq, dev);
err_request_irq:
	kमुक्त(b);
err_kzalloc:
	release_region(iobase, 8);
	वापस शून्य;
पूर्ण

अटल व्योम __निकास slvl_shutकरोwn(काष्ठा slvl_board *b)
अणु
	पूर्णांक u;

	z8530_shutकरोwn(&b->board);

	क्रम (u = 0; u < 2; u++) अणु
		काष्ठा net_device *d = b->dev[u].chan->netdevice;
		unरेजिस्टर_hdlc_device(d);
		मुक्त_netdev(d);
	पूर्ण

	मुक्त_irq(b->board.irq, &b->board);
	मुक्त_dma(b->board.chanA.rxdma);
	मुक्त_dma(b->board.chanA.txdma);
	/* DMA off on the card, drop DTR */
	outb(0, b->iobase);
	release_region(b->iobase, 8);
	kमुक्त(b);
पूर्ण


अटल पूर्णांक io=0x238;
अटल पूर्णांक txdma=1;
अटल पूर्णांक rxdma=3;
अटल पूर्णांक irq=5;
अटल bool slow=false;

module_param_hw(io, पूर्णांक, ioport, 0);
MODULE_PARM_DESC(io, "The I/O base of the Sealevel card");
module_param_hw(txdma, पूर्णांक, dma, 0);
MODULE_PARM_DESC(txdma, "Transmit DMA channel");
module_param_hw(rxdma, पूर्णांक, dma, 0);
MODULE_PARM_DESC(rxdma, "Receive DMA channel");
module_param_hw(irq, पूर्णांक, irq, 0);
MODULE_PARM_DESC(irq, "The interrupt line setting for the SeaLevel card");
module_param(slow, bool, 0);
MODULE_PARM_DESC(slow, "Set this for an older Sealevel card such as the 4012");

MODULE_AUTHOR("Alan Cox");
MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("Modular driver for the SeaLevel 4021");

अटल काष्ठा slvl_board *slvl_unit;

अटल पूर्णांक __init slvl_init_module(व्योम)
अणु
	slvl_unit = slvl_init(io, irq, txdma, rxdma, slow);

	वापस slvl_unit ? 0 : -ENODEV;
पूर्ण

अटल व्योम __निकास slvl_cleanup_module(व्योम)
अणु
	अगर (slvl_unit)
		slvl_shutकरोwn(slvl_unit);
पूर्ण

module_init(slvl_init_module);
module_निकास(slvl_cleanup_module);
