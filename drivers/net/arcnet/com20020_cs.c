<शैली गुरु>
/*
 * Linux ARCnet driver - COM20020 PCMCIA support
 *
 * Written 1994-1999 by Avery Pennarun,
 *    based on an ISA version by David Woodhouse.
 * Derived from ibmtr_cs.c by Steve Kipisz (pcmcia-cs 3.1.4)
 *    which was derived from pcnet_cs.c by David Hinds.
 * Some additional portions derived from skeleton.c by Donald Becker.
 *
 * Special thanks to Contemporary Controls, Inc. (www.ccontrols.com)
 *  क्रम sponsoring the further development of this driver.
 *
 * **********************
 *
 * The original copyright of skeleton.c was as follows:
 *
 * skeleton.c Written 1993 by Donald Becker.
 * Copyright 1993 United States Government as represented by the
 * Director, National Security Agency.  This software may only be used
 * and distributed according to the terms of the GNU General Public License as
 * modअगरied by SRC, incorporated herein by reference.
 *
 * **********************
 * Changes:
 * Arnalकरो Carvalho de Melo <acme@conectiva.com.br> - 08/08/2000
 * - reorganize kदो_स्मृतिs in com20020_attach, checking all क्रम failure
 *   and releasing the previous allocations अगर one fails
 * **********************
 *
 * For more details, see drivers/net/arcnet.c
 *
 * **********************
 */

#घोषणा pr_fmt(fmt) "arcnet:" KBUILD_MODNAME ": " fmt

#समावेश <linux/kernel.h>
#समावेश <linux/ptrace.h>
#समावेश <linux/slab.h>
#समावेश <linux/माला.स>
#समावेश <linux/समयr.h>
#समावेश <linux/delay.h>
#समावेश <linux/module.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/पन.स>
#समावेश <pcmcia/cistpl.h>
#समावेश <pcmcia/ds.h>

#समावेश "arcdevice.h"
#समावेश "com20020.h"

अटल व्योम regdump(काष्ठा net_device *dev)
अणु
#अगर_घोषित DEBUG
	पूर्णांक ioaddr = dev->base_addr;
	पूर्णांक count;

	netdev_dbg(dev, "register dump:\n");
	क्रम (count = 0; count < 16; count++) अणु
		अगर (!(count % 16))
			pr_cont("%04X:", ioaddr + count);
		pr_cont(" %02X", arcnet_inb(ioaddr, count));
	पूर्ण
	pr_cont("\n");

	netdev_dbg(dev, "buffer0 dump:\n");
	/* set up the address रेजिस्टर */
	count = 0;
	arcnet_outb((count >> 8) | RDDATAflag | AUTOINCflag,
		    ioaddr, COM20020_REG_W_ADDR_HI);
	arcnet_outb(count & 0xff, ioaddr, COM20020_REG_W_ADDR_LO);

	क्रम (count = 0; count < 256 + 32; count++) अणु
		अगर (!(count % 16))
			pr_cont("%04X:", count);

		/* copy the data */
		pr_cont(" %02X", arcnet_inb(ioaddr, COM20020_REG_RW_MEMDATA));
	पूर्ण
	pr_cont("\n");
#पूर्ण_अगर
पूर्ण

/*====================================================================*/

/* Parameters that can be set with 'insmod' */

अटल पूर्णांक node;
अटल पूर्णांक समयout = 3;
अटल पूर्णांक backplane;
अटल पूर्णांक घड़ीp;
अटल पूर्णांक घड़ीm;

module_param(node, पूर्णांक, 0);
module_param(समयout, पूर्णांक, 0);
module_param(backplane, पूर्णांक, 0);
module_param(घड़ीp, पूर्णांक, 0);
module_param(घड़ीm, पूर्णांक, 0);

MODULE_LICENSE("GPL");

/*====================================================================*/

अटल पूर्णांक com20020_config(काष्ठा pcmcia_device *link);
अटल व्योम com20020_release(काष्ठा pcmcia_device *link);

अटल व्योम com20020_detach(काष्ठा pcmcia_device *p_dev);

/*====================================================================*/

अटल पूर्णांक com20020_probe(काष्ठा pcmcia_device *p_dev)
अणु
	काष्ठा com20020_dev *info;
	काष्ठा net_device *dev;
	काष्ठा arcnet_local *lp;

	dev_dbg(&p_dev->dev, "com20020_attach()\n");

	/* Create new network device */
	info = kzalloc(माप(*info), GFP_KERNEL);
	अगर (!info)
		जाओ fail_alloc_info;

	dev = alloc_arcdev("");
	अगर (!dev)
		जाओ fail_alloc_dev;

	lp = netdev_priv(dev);
	lp->समयout = समयout;
	lp->backplane = backplane;
	lp->घड़ीp = घड़ीp;
	lp->घड़ीm = घड़ीm & 3;
	lp->hw.owner = THIS_MODULE;

	/* fill in our module parameters as शेषs */
	dev->dev_addr[0] = node;

	p_dev->resource[0]->flags |= IO_DATA_PATH_WIDTH_8;
	p_dev->resource[0]->end = 16;
	p_dev->config_flags |= CONF_ENABLE_IRQ;

	info->dev = dev;
	p_dev->priv = info;

	वापस com20020_config(p_dev);

fail_alloc_dev:
	kमुक्त(info);
fail_alloc_info:
	वापस -ENOMEM;
पूर्ण /* com20020_attach */

अटल व्योम com20020_detach(काष्ठा pcmcia_device *link)
अणु
	काष्ठा com20020_dev *info = link->priv;
	काष्ठा net_device *dev = info->dev;

	dev_dbg(&link->dev, "detach...\n");

	dev_dbg(&link->dev, "com20020_detach\n");

	dev_dbg(&link->dev, "unregister...\n");

	unरेजिस्टर_netdev(dev);

	/* this is necessary because we रेजिस्टर our IRQ separately
	 * from card services.
	 */
	अगर (dev->irq)
		मुक्त_irq(dev->irq, dev);

	com20020_release(link);

	/* Unlink device काष्ठाure, मुक्त bits */
	dev_dbg(&link->dev, "unlinking...\n");
	अगर (link->priv) अणु
		dev = info->dev;
		अगर (dev) अणु
			dev_dbg(&link->dev, "kfree...\n");
			मुक्त_arcdev(dev);
		पूर्ण
		dev_dbg(&link->dev, "kfree2...\n");
		kमुक्त(info);
	पूर्ण

पूर्ण /* com20020_detach */

अटल पूर्णांक com20020_config(काष्ठा pcmcia_device *link)
अणु
	काष्ठा arcnet_local *lp;
	काष्ठा com20020_dev *info;
	काष्ठा net_device *dev;
	पूर्णांक i, ret;
	पूर्णांक ioaddr;

	info = link->priv;
	dev = info->dev;

	dev_dbg(&link->dev, "config...\n");

	dev_dbg(&link->dev, "com20020_config\n");

	dev_dbg(&link->dev, "baseport1 is %Xh\n",
		(अचिन्हित पूर्णांक)link->resource[0]->start);

	i = -ENODEV;
	link->io_lines = 16;

	अगर (!link->resource[0]->start) अणु
		क्रम (ioaddr = 0x100; ioaddr < 0x400; ioaddr += 0x10) अणु
			link->resource[0]->start = ioaddr;
			i = pcmcia_request_io(link);
			अगर (i == 0)
				अवरोध;
		पूर्ण
	पूर्ण अन्यथा अणु
		i = pcmcia_request_io(link);
	पूर्ण

	अगर (i != 0) अणु
		dev_dbg(&link->dev, "requestIO failed totally!\n");
		जाओ failed;
	पूर्ण

	ioaddr = dev->base_addr = link->resource[0]->start;
	dev_dbg(&link->dev, "got ioaddr %Xh\n", ioaddr);

	dev_dbg(&link->dev, "request IRQ %d\n",
		link->irq);
	अगर (!link->irq) अणु
		dev_dbg(&link->dev, "requestIRQ failed totally!\n");
		जाओ failed;
	पूर्ण

	dev->irq = link->irq;

	ret = pcmcia_enable_device(link);
	अगर (ret)
		जाओ failed;

	अगर (com20020_check(dev)) अणु
		regdump(dev);
		जाओ failed;
	पूर्ण

	lp = netdev_priv(dev);
	lp->card_name = "PCMCIA COM20020";
	lp->card_flags = ARC_CAN_10MBIT; /* pretend all of them can 10Mbit */

	SET_NETDEV_DEV(dev, &link->dev);

	i = com20020_found(dev, 0);	/* calls रेजिस्टर_netdev */

	अगर (i != 0) अणु
		dev_notice(&link->dev,
			   "com20020_found() failed\n");
		जाओ failed;
	पूर्ण

	netdev_dbg(dev, "port %#3lx, irq %d\n",
		   dev->base_addr, dev->irq);
	वापस 0;

failed:
	dev_dbg(&link->dev, "com20020_config failed...\n");
	com20020_release(link);
	वापस -ENODEV;
पूर्ण /* com20020_config */

अटल व्योम com20020_release(काष्ठा pcmcia_device *link)
अणु
	dev_dbg(&link->dev, "com20020_release\n");
	pcmcia_disable_device(link);
पूर्ण

अटल पूर्णांक com20020_suspend(काष्ठा pcmcia_device *link)
अणु
	काष्ठा com20020_dev *info = link->priv;
	काष्ठा net_device *dev = info->dev;

	अगर (link->खोलो)
		netअगर_device_detach(dev);

	वापस 0;
पूर्ण

अटल पूर्णांक com20020_resume(काष्ठा pcmcia_device *link)
अणु
	काष्ठा com20020_dev *info = link->priv;
	काष्ठा net_device *dev = info->dev;

	अगर (link->खोलो) अणु
		पूर्णांक ioaddr = dev->base_addr;
		काष्ठा arcnet_local *lp = netdev_priv(dev);

		arcnet_outb(lp->config | 0x80, ioaddr, COM20020_REG_W_CONFIG);
		udelay(5);
		arcnet_outb(lp->config, ioaddr, COM20020_REG_W_CONFIG);
	पूर्ण

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा pcmcia_device_id com20020_ids[] = अणु
	PCMCIA_DEVICE_PROD_ID12("Contemporary Control Systems, Inc.",
				"PCM20 Arcnet Adapter", 0x59991666, 0x95dfffaf),
	PCMCIA_DEVICE_PROD_ID12("SoHard AG",
				"SH ARC PCMCIA", 0xf8991729, 0x69dff0c7),
	PCMCIA_DEVICE_शून्य
पूर्ण;
MODULE_DEVICE_TABLE(pcmcia, com20020_ids);

अटल काष्ठा pcmcia_driver com20020_cs_driver = अणु
	.owner		= THIS_MODULE,
	.name		= "com20020_cs",
	.probe		= com20020_probe,
	.हटाओ		= com20020_detach,
	.id_table	= com20020_ids,
	.suspend	= com20020_suspend,
	.resume		= com20020_resume,
पूर्ण;
module_pcmcia_driver(com20020_cs_driver);
