<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 *	Comtrol SV11 card driver
 *
 *	This is a slightly odd Z85230 synchronous driver. All you need to
 *	know basically is
 *
 *	Its a genuine Z85230
 *
 *	It supports DMA using two DMA channels in SYNC mode. The driver करोesn't
 *	use these facilities
 *	
 *	The control port is at io+1, the data at io+3 and turning off the DMA
 *	is करोne by writing 0 to io+4
 *
 *	The hardware करोes the bus handling to aव्योम the need क्रम delays between
 *	touching control रेजिस्टरs.
 *
 *	Port B isn't wired (why - beats me)
 *
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
#समावेश <linux/slab.h>
#समावेश <net/arp.h>

#समावेश <यंत्र/irq.h>
#समावेश <यंत्र/पन.स>
#समावेश <यंत्र/dma.h>
#समावेश <यंत्र/byteorder.h>
#समावेश "z85230.h"

अटल पूर्णांक dma;

/*
 *	Network driver support routines
 */

अटल अंतरभूत काष्ठा z8530_dev* dev_to_sv(काष्ठा net_device *dev)
अणु
	वापस (काष्ठा z8530_dev *)dev_to_hdlc(dev)->priv;
पूर्ण

/*
 *	Frame receive. Simple क्रम our card as we करो HDLC and there
 *	is no funny garbage involved
 */

अटल व्योम hostess_input(काष्ठा z8530_channel *c, काष्ठा sk_buff *skb)
अणु
	/* Drop the CRC - it's not a good idea to try and negotiate it ;) */
	skb_trim(skb, skb->len - 2);
	skb->protocol = hdlc_type_trans(skb, c->netdevice);
	skb_reset_mac_header(skb);
	skb->dev = c->netdevice;
	/*
	 *	Send it to the PPP layer. We करोn't have समय to process
	 *	it right now.
	 */
	netअगर_rx(skb);
पूर्ण

/*
 *	We've been placed in the UP state
 */

अटल पूर्णांक hostess_खोलो(काष्ठा net_device *d)
अणु
	काष्ठा z8530_dev *sv11 = dev_to_sv(d);
	पूर्णांक err = -1;

	/*
	 *	Link layer up
	 */
	चयन (dma) अणु
		हाल 0:
			err = z8530_sync_खोलो(d, &sv11->chanA);
			अवरोध;
		हाल 1:
			err = z8530_sync_dma_खोलो(d, &sv11->chanA);
			अवरोध;
		हाल 2:
			err = z8530_sync_txdma_खोलो(d, &sv11->chanA);
			अवरोध;
	पूर्ण

	अगर (err)
		वापस err;

	err = hdlc_खोलो(d);
	अगर (err) अणु
		चयन (dma) अणु
			हाल 0:
				z8530_sync_बंद(d, &sv11->chanA);
				अवरोध;
			हाल 1:
				z8530_sync_dma_बंद(d, &sv11->chanA);
				अवरोध;
			हाल 2:
				z8530_sync_txdma_बंद(d, &sv11->chanA);
				अवरोध;
		पूर्ण
		वापस err;
	पूर्ण
	sv11->chanA.rx_function = hostess_input;

	/*
	 *	Go go go
	 */

	netअगर_start_queue(d);
	वापस 0;
पूर्ण

अटल पूर्णांक hostess_बंद(काष्ठा net_device *d)
अणु
	काष्ठा z8530_dev *sv11 = dev_to_sv(d);
	/*
	 *	Discard new frames
	 */
	sv11->chanA.rx_function = z8530_null_rx;

	hdlc_बंद(d);
	netअगर_stop_queue(d);

	चयन (dma) अणु
		हाल 0:
			z8530_sync_बंद(d, &sv11->chanA);
			अवरोध;
		हाल 1:
			z8530_sync_dma_बंद(d, &sv11->chanA);
			अवरोध;
		हाल 2:
			z8530_sync_txdma_बंद(d, &sv11->chanA);
			अवरोध;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक hostess_ioctl(काष्ठा net_device *d, काष्ठा अगरreq *अगरr, पूर्णांक cmd)
अणु
	/* काष्ठा z8530_dev *sv11=dev_to_sv(d);
	   z8530_ioctl(d,&sv11->chanA,अगरr,cmd) */
	वापस hdlc_ioctl(d, अगरr, cmd);
पूर्ण

/*
 *	Passed network frames, fire them करोwnwind.
 */

अटल netdev_tx_t hostess_queue_xmit(काष्ठा sk_buff *skb,
					    काष्ठा net_device *d)
अणु
	वापस z8530_queue_xmit(&dev_to_sv(d)->chanA, skb);
पूर्ण

अटल पूर्णांक hostess_attach(काष्ठा net_device *dev, अचिन्हित लघु encoding,
			  अचिन्हित लघु parity)
अणु
	अगर (encoding == ENCODING_NRZ && parity == PARITY_CRC16_PR1_CCITT)
		वापस 0;
	वापस -EINVAL;
पूर्ण

/*
 *	Description block क्रम a Comtrol Hostess SV11 card
 */

अटल स्थिर काष्ठा net_device_ops hostess_ops = अणु
	.nकरो_खोलो       = hostess_खोलो,
	.nकरो_stop       = hostess_बंद,
	.nकरो_start_xmit = hdlc_start_xmit,
	.nकरो_करो_ioctl   = hostess_ioctl,
पूर्ण;

अटल काष्ठा z8530_dev *sv11_init(पूर्णांक iobase, पूर्णांक irq)
अणु
	काष्ठा z8530_dev *sv;
	काष्ठा net_device *netdev;
	/*
	 *	Get the needed I/O space
	 */

	अगर (!request_region(iobase, 8, "Comtrol SV11")) अणु
		pr_warn("I/O 0x%X already in use\n", iobase);
		वापस शून्य;
	पूर्ण

	sv = kzalloc(माप(काष्ठा z8530_dev), GFP_KERNEL);
	अगर (!sv)
		जाओ err_kzalloc;

	/*
	 *	Stuff in the I/O addressing
	 */

	sv->active = 0;

	sv->chanA.ctrlio = iobase + 1;
	sv->chanA.dataio = iobase + 3;
	sv->chanB.ctrlio = -1;
	sv->chanB.dataio = -1;
	sv->chanA.irqs = &z8530_nop;
	sv->chanB.irqs = &z8530_nop;

	outb(0, iobase + 4);		/* DMA off */

	/* We want a fast IRQ क्रम this device. Actually we'd like an even faster
	   IRQ ;) - This is one driver RtLinux is made क्रम */

	अगर (request_irq(irq, z8530_पूर्णांकerrupt, 0,
			"Hostess SV11", sv) < 0) अणु
		pr_warn("IRQ %d already in use\n", irq);
		जाओ err_irq;
	पूर्ण

	sv->irq = irq;
	sv->chanA.निजी = sv;
	sv->chanA.dev = sv;
	sv->chanB.dev = sv;

	अगर (dma) अणु
		/*
		 *	You can have DMA off or 1 and 3 thats the lot
		 *	on the Comtrol.
		 */
		sv->chanA.txdma = 3;
		sv->chanA.rxdma = 1;
		outb(0x03 | 0x08, iobase + 4);		/* DMA on */
		अगर (request_dma(sv->chanA.txdma, "Hostess SV/11 (TX)"))
			जाओ err_txdma;

		अगर (dma == 1)
			अगर (request_dma(sv->chanA.rxdma, "Hostess SV/11 (RX)"))
				जाओ err_rxdma;
	पूर्ण

	/* Kill our निजी IRQ line the hostess can end up chattering
	   until the configuration is set */
	disable_irq(irq);

	/*
	 *	Begin normal initialise
	 */

	अगर (z8530_init(sv)) अणु
		pr_err("Z8530 series device not found\n");
		enable_irq(irq);
		जाओ मुक्त_dma;
	पूर्ण
	z8530_channel_load(&sv->chanB, z8530_dead_port);
	अगर (sv->type == Z85C30)
		z8530_channel_load(&sv->chanA, z8530_hdlc_kilostream);
	अन्यथा
		z8530_channel_load(&sv->chanA, z8530_hdlc_kilostream_85230);

	enable_irq(irq);

	/*
	 *	Now we can take the IRQ
	 */

	sv->chanA.netdevice = netdev = alloc_hdlcdev(sv);
	अगर (!netdev)
		जाओ मुक्त_dma;

	dev_to_hdlc(netdev)->attach = hostess_attach;
	dev_to_hdlc(netdev)->xmit = hostess_queue_xmit;
	netdev->netdev_ops = &hostess_ops;
	netdev->base_addr = iobase;
	netdev->irq = irq;

	अगर (रेजिस्टर_hdlc_device(netdev)) अणु
		pr_err("unable to register HDLC device\n");
		मुक्त_netdev(netdev);
		जाओ मुक्त_dma;
	पूर्ण

	z8530_describe(sv, "I/O", iobase);
	sv->active = 1;
	वापस sv;

मुक्त_dma:
	अगर (dma == 1)
		मुक्त_dma(sv->chanA.rxdma);
err_rxdma:
	अगर (dma)
		मुक्त_dma(sv->chanA.txdma);
err_txdma:
	मुक्त_irq(irq, sv);
err_irq:
	kमुक्त(sv);
err_kzalloc:
	release_region(iobase, 8);
	वापस शून्य;
पूर्ण

अटल व्योम sv11_shutकरोwn(काष्ठा z8530_dev *dev)
अणु
	unरेजिस्टर_hdlc_device(dev->chanA.netdevice);
	z8530_shutकरोwn(dev);
	मुक्त_irq(dev->irq, dev);
	अगर (dma) अणु
		अगर (dma == 1)
			मुक्त_dma(dev->chanA.rxdma);
		मुक्त_dma(dev->chanA.txdma);
	पूर्ण
	release_region(dev->chanA.ctrlio - 1, 8);
	मुक्त_netdev(dev->chanA.netdevice);
	kमुक्त(dev);
पूर्ण

अटल पूर्णांक io = 0x200;
अटल पूर्णांक irq = 9;

module_param_hw(io, पूर्णांक, ioport, 0);
MODULE_PARM_DESC(io, "The I/O base of the Comtrol Hostess SV11 card");
module_param_hw(dma, पूर्णांक, dma, 0);
MODULE_PARM_DESC(dma, "Set this to 1 to use DMA1/DMA3 for TX/RX");
module_param_hw(irq, पूर्णांक, irq, 0);
MODULE_PARM_DESC(irq, "The interrupt line setting for the Comtrol Hostess SV11 card");

MODULE_AUTHOR("Alan Cox");
MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("Modular driver for the Comtrol Hostess SV11");

अटल काष्ठा z8530_dev *sv11_unit;

पूर्णांक init_module(व्योम)
अणु
	अगर ((sv11_unit = sv11_init(io, irq)) == शून्य)
		वापस -ENODEV;
	वापस 0;
पूर्ण

व्योम cleanup_module(व्योम)
अणु
	अगर (sv11_unit)
		sv11_shutकरोwn(sv11_unit);
पूर्ण
