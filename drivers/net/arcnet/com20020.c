<शैली गुरु>
/*
 * Linux ARCnet driver - COM20020 chipset support
 *
 * Written 1997 by David Woodhouse.
 * Written 1994-1999 by Avery Pennarun.
 * Written 1999 by Martin Mares <mj@ucw.cz>.
 * Derived from skeleton.c by Donald Becker.
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
 *
 * For more details, see drivers/net/arcnet.c
 *
 * **********************
 */

#घोषणा pr_fmt(fmt) "arcnet:" KBUILD_MODNAME ": " fmt

#समावेश <linux/module.h>
#समावेश <linux/kernel.h>
#समावेश <linux/types.h>
#समावेश <linux/ioport.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/delay.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/init.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/पन.स>

#समावेश "arcdevice.h"
#समावेश "com20020.h"

अटल स्थिर अक्षर * स्थिर घड़ीrates[] = अणु
	"XXXXXXX", "XXXXXXXX", "XXXXXX", "2.5 Mb/s",
	"1.25Mb/s", "625 Kb/s", "312.5 Kb/s", "156.25 Kb/s",
	"Reserved", "Reserved", "Reserved"
पूर्ण;

अटल व्योम com20020_command(काष्ठा net_device *dev, पूर्णांक command);
अटल पूर्णांक com20020_status(काष्ठा net_device *dev);
अटल व्योम com20020_seपंचांगask(काष्ठा net_device *dev, पूर्णांक mask);
अटल पूर्णांक com20020_reset(काष्ठा net_device *dev, पूर्णांक really_reset);
अटल व्योम com20020_copy_to_card(काष्ठा net_device *dev, पूर्णांक bufnum,
				  पूर्णांक offset, व्योम *buf, पूर्णांक count);
अटल व्योम com20020_copy_from_card(काष्ठा net_device *dev, पूर्णांक bufnum,
				    पूर्णांक offset, व्योम *buf, पूर्णांक count);
अटल व्योम com20020_set_mc_list(काष्ठा net_device *dev);
अटल व्योम com20020_बंद(काष्ठा net_device *);

अटल व्योम com20020_copy_from_card(काष्ठा net_device *dev, पूर्णांक bufnum,
				    पूर्णांक offset, व्योम *buf, पूर्णांक count)
अणु
	पूर्णांक ioaddr = dev->base_addr, ofs = 512 * bufnum + offset;

	/* set up the address रेजिस्टर */
	arcnet_outb((ofs >> 8) | RDDATAflag | AUTOINCflag,
		    ioaddr, COM20020_REG_W_ADDR_HI);
	arcnet_outb(ofs & 0xff, ioaddr, COM20020_REG_W_ADDR_LO);

	/* copy the data */
	TIME(dev, "insb", count,
	     arcnet_insb(ioaddr, COM20020_REG_RW_MEMDATA, buf, count));
पूर्ण

अटल व्योम com20020_copy_to_card(काष्ठा net_device *dev, पूर्णांक bufnum,
				  पूर्णांक offset, व्योम *buf, पूर्णांक count)
अणु
	पूर्णांक ioaddr = dev->base_addr, ofs = 512 * bufnum + offset;

	/* set up the address रेजिस्टर */
	arcnet_outb((ofs >> 8) | AUTOINCflag, ioaddr, COM20020_REG_W_ADDR_HI);
	arcnet_outb(ofs & 0xff, ioaddr, COM20020_REG_W_ADDR_LO);

	/* copy the data */
	TIME(dev, "outsb", count,
	     arcnet_outsb(ioaddr, COM20020_REG_RW_MEMDATA, buf, count));
पूर्ण

/* Reset the card and check some basic stuff during the detection stage. */
पूर्णांक com20020_check(काष्ठा net_device *dev)
अणु
	पूर्णांक ioaddr = dev->base_addr, status;
	काष्ठा arcnet_local *lp = netdev_priv(dev);

	arcnet_outb(XTOcfg(3) | RESETcfg, ioaddr, COM20020_REG_W_CONFIG);
	udelay(5);
	arcnet_outb(XTOcfg(3), ioaddr, COM20020_REG_W_CONFIG);
	mdelay(RESETसमय);

	lp->setup = lp->घड़ीm ? 0 : (lp->घड़ीp << 1);
	lp->setup2 = (lp->घड़ीm << 4) | 8;

	/* CHECK: should we करो this क्रम SOHARD cards ? */
	/* Enable P1Mode क्रम backplane mode */
	lp->setup = lp->setup | P1MODE;

	com20020_set_subaddress(lp, ioaddr, SUB_SETUP1);
	arcnet_outb(lp->setup, ioaddr, COM20020_REG_W_XREG);

	अगर (lp->घड़ीm != 0) अणु
		com20020_set_subaddress(lp, ioaddr, SUB_SETUP2);
		arcnet_outb(lp->setup2, ioaddr, COM20020_REG_W_XREG);

		/* must now ग_लिखो the magic "restart operation" command */
		mdelay(1);
		arcnet_outb(STARTIOcmd, ioaddr, COM20020_REG_W_COMMAND);
	पूर्ण

	lp->config = (lp->समयout << 3) | (lp->backplane << 2) | SUB_NODE;
	/* set node ID to 0x42 (but transmitter is disabled, so it's okay) */
	arcnet_outb(lp->config, ioaddr, COM20020_REG_W_CONFIG);
	arcnet_outb(0x42, ioaddr, COM20020_REG_W_XREG);

	status = arcnet_inb(ioaddr, COM20020_REG_R_STATUS);

	अगर ((status & 0x99) != (NORXflag | TXFREEflag | RESETflag)) अणु
		arc_prपूर्णांकk(D_NORMAL, dev, "status invalid (%Xh).\n", status);
		वापस -ENODEV;
	पूर्ण
	arc_prपूर्णांकk(D_INIT_REASONS, dev, "status after reset: %X\n", status);

	arcnet_outb(CFLAGScmd | RESETclear | CONFIGclear,
		    ioaddr, COM20020_REG_W_COMMAND);
	status = arcnet_inb(ioaddr, COM20020_REG_R_STATUS);
	arc_prपूर्णांकk(D_INIT_REASONS, dev, "status after reset acknowledged: %X\n",
		   status);

	/* Read first location of memory */
	arcnet_outb(0 | RDDATAflag | AUTOINCflag,
		    ioaddr, COM20020_REG_W_ADDR_HI);
	arcnet_outb(0, ioaddr, COM20020_REG_W_ADDR_LO);

	status = arcnet_inb(ioaddr, COM20020_REG_RW_MEMDATA);
	अगर (status != TESTvalue) अणु
		arc_prपूर्णांकk(D_NORMAL, dev, "Signature byte not found (%02Xh != D1h).\n",
			   status);
		वापस -ENODEV;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक com20020_set_hwaddr(काष्ठा net_device *dev, व्योम *addr)
अणु
	पूर्णांक ioaddr = dev->base_addr;
	काष्ठा arcnet_local *lp = netdev_priv(dev);
	काष्ठा sockaddr *hwaddr = addr;

	स_नकल(dev->dev_addr, hwaddr->sa_data, 1);
	com20020_set_subaddress(lp, ioaddr, SUB_NODE);
	arcnet_outb(dev->dev_addr[0], ioaddr, COM20020_REG_W_XREG);

	वापस 0;
पूर्ण

अटल पूर्णांक com20020_netdev_खोलो(काष्ठा net_device *dev)
अणु
	पूर्णांक ioaddr = dev->base_addr;
	काष्ठा arcnet_local *lp = netdev_priv(dev);

	lp->config |= TXENcfg;
	arcnet_outb(lp->config, ioaddr, COM20020_REG_W_CONFIG);

	वापस arcnet_खोलो(dev);
पूर्ण

अटल पूर्णांक com20020_netdev_बंद(काष्ठा net_device *dev)
अणु
	पूर्णांक ioaddr = dev->base_addr;
	काष्ठा arcnet_local *lp = netdev_priv(dev);

	arcnet_बंद(dev);

	/* disable transmitter */
	lp->config &= ~TXENcfg;
	arcnet_outb(lp->config, ioaddr, COM20020_REG_W_CONFIG);
	वापस 0;
पूर्ण

स्थिर काष्ठा net_device_ops com20020_netdev_ops = अणु
	.nकरो_खोलो	= com20020_netdev_खोलो,
	.nकरो_stop	= com20020_netdev_बंद,
	.nकरो_start_xmit = arcnet_send_packet,
	.nकरो_tx_समयout = arcnet_समयout,
	.nकरो_set_mac_address = com20020_set_hwaddr,
	.nकरो_set_rx_mode = com20020_set_mc_list,
पूर्ण;

/* Set up the काष्ठा net_device associated with this card.  Called after
 * probing succeeds.
 */
पूर्णांक com20020_found(काष्ठा net_device *dev, पूर्णांक shared)
अणु
	काष्ठा arcnet_local *lp;
	पूर्णांक ioaddr = dev->base_addr;

	/* Initialize the rest of the device काष्ठाure. */

	lp = netdev_priv(dev);

	lp->hw.owner = THIS_MODULE;
	lp->hw.command = com20020_command;
	lp->hw.status = com20020_status;
	lp->hw.पूर्णांकmask = com20020_seपंचांगask;
	lp->hw.reset = com20020_reset;
	lp->hw.copy_to_card = com20020_copy_to_card;
	lp->hw.copy_from_card = com20020_copy_from_card;
	lp->hw.बंद = com20020_बंद;

	/* FIXME: करो this some other way! */
	अगर (!dev->dev_addr[0])
		dev->dev_addr[0] = arcnet_inb(ioaddr, 8);

	com20020_set_subaddress(lp, ioaddr, SUB_SETUP1);
	arcnet_outb(lp->setup, ioaddr, COM20020_REG_W_XREG);

	अगर (lp->card_flags & ARC_CAN_10MBIT) अणु
		com20020_set_subaddress(lp, ioaddr, SUB_SETUP2);
		arcnet_outb(lp->setup2, ioaddr, COM20020_REG_W_XREG);

		/* must now ग_लिखो the magic "restart operation" command */
		mdelay(1);
		arcnet_outb(STARTIOcmd, ioaddr, COM20020_REG_W_COMMAND);
	पूर्ण

	lp->config = (lp->समयout << 3) | (lp->backplane << 2) | SUB_NODE;
	/* Default 0x38 + रेजिस्टर: Node ID */
	arcnet_outb(lp->config, ioaddr, COM20020_REG_W_CONFIG);
	arcnet_outb(dev->dev_addr[0], ioaddr, COM20020_REG_W_XREG);

	/* reserve the irq */
	अगर (request_irq(dev->irq, arcnet_पूर्णांकerrupt, shared,
			"arcnet (COM20020)", dev)) अणु
		arc_prपूर्णांकk(D_NORMAL, dev, "Can't get IRQ %d!\n", dev->irq);
		वापस -ENODEV;
	पूर्ण

	arc_prपूर्णांकk(D_NORMAL, dev, "%s: station %02Xh found at %03lXh, IRQ %d.\n",
		   lp->card_name, dev->dev_addr[0], dev->base_addr, dev->irq);

	अगर (lp->backplane)
		arc_prपूर्णांकk(D_NORMAL, dev, "Using backplane mode.\n");

	अगर (lp->समयout != 3)
		arc_prपूर्णांकk(D_NORMAL, dev, "Using extended timeout value of %d\n",
			   lp->समयout);

	arc_prपूर्णांकk(D_NORMAL, dev, "Using CKP %d - data rate %s\n",
		   lp->setup >> 1,
		   घड़ीrates[3 -
			      ((lp->setup2 & 0xF0) >> 4) +
			      ((lp->setup & 0x0F) >> 1)]);
			/* The घड़ीrates array index looks very fragile.
			 * It seems like it could have negative indexing.
			 */

	अगर (रेजिस्टर_netdev(dev)) अणु
		मुक्त_irq(dev->irq, dev);
		वापस -EIO;
	पूर्ण
	वापस 0;
पूर्ण

/* Do a hardware reset on the card, and set up necessary रेजिस्टरs.
 *
 * This should be called as little as possible, because it disrupts the
 * token on the network (causes a RECON) and requires a signअगरicant delay.
 *
 * However, it करोes make sure the card is in a defined state.
 */
अटल पूर्णांक com20020_reset(काष्ठा net_device *dev, पूर्णांक really_reset)
अणु
	काष्ठा arcnet_local *lp = netdev_priv(dev);
	u_पूर्णांक ioaddr = dev->base_addr;
	u_अक्षर inbyte;

	arc_prपूर्णांकk(D_DEBUG, dev, "%s: %d: %s: dev: %p, lp: %p, dev->name: %s\n",
		   __खाता__, __LINE__, __func__, dev, lp, dev->name);
	arc_prपूर्णांकk(D_INIT, dev, "Resetting %s (status=%02Xh)\n",
		   dev->name, arcnet_inb(ioaddr, COM20020_REG_R_STATUS));

	arc_prपूर्णांकk(D_DEBUG, dev, "%s: %d: %s\n", __खाता__, __LINE__, __func__);
	lp->config |= (lp->समयout << 3) | (lp->backplane << 2);
	/* घातer-up शेषs */
	arcnet_outb(lp->config, ioaddr, COM20020_REG_W_CONFIG);
	arc_prपूर्णांकk(D_DEBUG, dev, "%s: %d: %s\n", __खाता__, __LINE__, __func__);

	अगर (really_reset) अणु
		/* reset the card */
		arcnet_outb(lp->config | RESETcfg, ioaddr, COM20020_REG_W_CONFIG);
		udelay(5);
		arcnet_outb(lp->config, ioaddr, COM20020_REG_W_CONFIG);
		mdelay(RESETसमय * 2);
				/* COM20020 seems to be slower someबार */
	पूर्ण
	/* clear flags & end reset */
	arc_prपूर्णांकk(D_DEBUG, dev, "%s: %d: %s\n", __खाता__, __LINE__, __func__);
	arcnet_outb(CFLAGScmd | RESETclear | CONFIGclear,
		    ioaddr, COM20020_REG_W_COMMAND);

	/* verअगरy that the ARCnet signature byte is present */
	arc_prपूर्णांकk(D_DEBUG, dev, "%s: %d: %s\n", __खाता__, __LINE__, __func__);

	com20020_copy_from_card(dev, 0, 0, &inbyte, 1);
	arc_prपूर्णांकk(D_DEBUG, dev, "%s: %d: %s\n", __खाता__, __LINE__, __func__);
	अगर (inbyte != TESTvalue) अणु
		arc_prपूर्णांकk(D_DEBUG, dev, "%s: %d: %s\n",
			   __खाता__, __LINE__, __func__);
		arc_prपूर्णांकk(D_NORMAL, dev, "reset failed: TESTvalue not present.\n");
		वापस 1;
	पूर्ण
	/* enable extended (512-byte) packets */
	arcnet_outb(CONFIGcmd | EXTconf, ioaddr, COM20020_REG_W_COMMAND);

	arc_prपूर्णांकk(D_DEBUG, dev, "%s: %d: %s\n", __खाता__, __LINE__, __func__);

	/* करोne!  वापस success. */
	वापस 0;
पूर्ण

अटल व्योम com20020_seपंचांगask(काष्ठा net_device *dev, पूर्णांक mask)
अणु
	u_पूर्णांक ioaddr = dev->base_addr;

	arc_prपूर्णांकk(D_DURING, dev, "Setting mask to %x at %x\n", mask, ioaddr);
	arcnet_outb(mask, ioaddr, COM20020_REG_W_INTMASK);
पूर्ण

अटल व्योम com20020_command(काष्ठा net_device *dev, पूर्णांक cmd)
अणु
	u_पूर्णांक ioaddr = dev->base_addr;

	arcnet_outb(cmd, ioaddr, COM20020_REG_W_COMMAND);
पूर्ण

अटल पूर्णांक com20020_status(काष्ठा net_device *dev)
अणु
	u_पूर्णांक ioaddr = dev->base_addr;

	वापस arcnet_inb(ioaddr, COM20020_REG_R_STATUS) +
		(arcnet_inb(ioaddr, COM20020_REG_R_DIAGSTAT) << 8);
पूर्ण

अटल व्योम com20020_बंद(काष्ठा net_device *dev)
अणु
	काष्ठा arcnet_local *lp = netdev_priv(dev);
	पूर्णांक ioaddr = dev->base_addr;

	/* disable transmitter */
	lp->config &= ~TXENcfg;
	arcnet_outb(lp->config, ioaddr, COM20020_REG_W_CONFIG);
पूर्ण

/* Set or clear the multicast filter क्रम this adaptor.
 * num_addrs == -1    Promiscuous mode, receive all packets
 * num_addrs == 0       Normal mode, clear multicast list
 * num_addrs > 0        Multicast mode, receive normal and MC packets, and करो
 *                      best-efक्रमt filtering.
 *      FIXME - करो multicast stuff, not just promiscuous.
 */
अटल व्योम com20020_set_mc_list(काष्ठा net_device *dev)
अणु
	काष्ठा arcnet_local *lp = netdev_priv(dev);
	पूर्णांक ioaddr = dev->base_addr;

	अगर ((dev->flags & IFF_PROMISC) && (dev->flags & IFF_UP)) अणु
		/* Enable promiscuous mode */
		अगर (!(lp->setup & PROMISCset))
			arc_prपूर्णांकk(D_NORMAL, dev, "Setting promiscuous flag...\n");
		com20020_set_subaddress(lp, ioaddr, SUB_SETUP1);
		lp->setup |= PROMISCset;
		arcnet_outb(lp->setup, ioaddr, COM20020_REG_W_XREG);
	पूर्ण अन्यथा अणु
		/* Disable promiscuous mode, use normal mode */
		अगर ((lp->setup & PROMISCset))
			arc_prपूर्णांकk(D_NORMAL, dev, "Resetting promiscuous flag...\n");
		com20020_set_subaddress(lp, ioaddr, SUB_SETUP1);
		lp->setup &= ~PROMISCset;
		arcnet_outb(lp->setup, ioaddr, COM20020_REG_W_XREG);
	पूर्ण
पूर्ण

#अगर defined(CONFIG_ARCNET_COM20020_PCI_MODULE) || \
    defined(CONFIG_ARCNET_COM20020_ISA_MODULE) || \
    defined(CONFIG_ARCNET_COM20020_CS_MODULE)
EXPORT_SYMBOL(com20020_check);
EXPORT_SYMBOL(com20020_found);
EXPORT_SYMBOL(com20020_netdev_ops);
#पूर्ण_अगर

MODULE_LICENSE("GPL");

#अगर_घोषित MODULE

अटल पूर्णांक __init com20020_module_init(व्योम)
अणु
	अगर (BUGLVL(D_NORMAL))
		pr_info("%s\n", "COM20020 chipset support (by David Woodhouse et al.)");
	वापस 0;
पूर्ण

अटल व्योम __निकास com20020_module_निकास(व्योम)
अणु
पूर्ण
module_init(com20020_module_init);
module_निकास(com20020_module_निकास);
#पूर्ण_अगर				/* MODULE */
