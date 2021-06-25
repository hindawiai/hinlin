<शैली गुरु>
/*
 * Linux ARCnet driver - COM90xx chipset (IO-mapped buffers)
 *
 * Written 1997 by David Woodhouse.
 * Written 1994-1999 by Avery Pennarun.
 * Written 1999-2000 by Martin Mares <mj@ucw.cz>.
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

#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/moduleparam.h>
#समावेश <linux/ioport.h>
#समावेश <linux/delay.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/memblock.h>
#समावेश <linux/init.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/पन.स>

#समावेश "arcdevice.h"
#समावेश "com9026.h"

/* Internal function declarations */

अटल पूर्णांक com90io_found(काष्ठा net_device *dev);
अटल व्योम com90io_command(काष्ठा net_device *dev, पूर्णांक command);
अटल पूर्णांक com90io_status(काष्ठा net_device *dev);
अटल व्योम com90io_seपंचांगask(काष्ठा net_device *dev, पूर्णांक mask);
अटल पूर्णांक com90io_reset(काष्ठा net_device *dev, पूर्णांक really_reset);
अटल व्योम com90io_copy_to_card(काष्ठा net_device *dev, पूर्णांक bufnum, पूर्णांक offset,
				 व्योम *buf, पूर्णांक count);
अटल व्योम com90io_copy_from_card(काष्ठा net_device *dev, पूर्णांक bufnum,
				   पूर्णांक offset, व्योम *buf, पूर्णांक count);

/* Handy defines क्रम ARCnet specअगरic stuff */

/* The number of low I/O ports used by the card. */
#घोषणा ARCNET_TOTAL_SIZE 16

/****************************************************************************
 *                                                                          *
 * IO-mapped operation routines                                             *
 *                                                                          *
 ****************************************************************************/

#अघोषित ONE_AT_A_TIME_TX
#अघोषित ONE_AT_A_TIME_RX

अटल u_अक्षर get_buffer_byte(काष्ठा net_device *dev, अचिन्हित offset)
अणु
	पूर्णांक ioaddr = dev->base_addr;

	arcnet_outb(offset >> 8, ioaddr, COM9026_REG_W_ADDR_HI);
	arcnet_outb(offset & 0xff, ioaddr, COM9026_REG_W_ADDR_LO);

	वापस arcnet_inb(ioaddr, COM9026_REG_RW_MEMDATA);
पूर्ण

#अगर_घोषित ONE_AT_A_TIME_TX
अटल व्योम put_buffer_byte(काष्ठा net_device *dev, अचिन्हित offset,
			    u_अक्षर datum)
अणु
	पूर्णांक ioaddr = dev->base_addr;

	arcnet_outb(offset >> 8, ioaddr, COM9026_REG_W_ADDR_HI);
	arcnet_outb(offset & 0xff, ioaddr, COM9026_REG_W_ADDR_LO);

	arcnet_outb(datum, ioaddr, COM9026_REG_RW_MEMDATA);
पूर्ण

#पूर्ण_अगर

अटल व्योम get_whole_buffer(काष्ठा net_device *dev, अचिन्हित offset,
			     अचिन्हित length, अक्षर *dest)
अणु
	पूर्णांक ioaddr = dev->base_addr;

	arcnet_outb((offset >> 8) | AUTOINCflag, ioaddr, COM9026_REG_W_ADDR_HI);
	arcnet_outb(offset & 0xff, ioaddr, COM9026_REG_W_ADDR_LO);

	जबतक (length--)
#अगर_घोषित ONE_AT_A_TIME_RX
		*(dest++) = get_buffer_byte(dev, offset++);
#अन्यथा
		*(dest++) = arcnet_inb(ioaddr, COM9026_REG_RW_MEMDATA);
#पूर्ण_अगर
पूर्ण

अटल व्योम put_whole_buffer(काष्ठा net_device *dev, अचिन्हित offset,
			     अचिन्हित length, अक्षर *dest)
अणु
	पूर्णांक ioaddr = dev->base_addr;

	arcnet_outb((offset >> 8) | AUTOINCflag, ioaddr, COM9026_REG_W_ADDR_HI);
	arcnet_outb(offset & 0xff, ioaddr,COM9026_REG_W_ADDR_LO);

	जबतक (length--)
#अगर_घोषित ONE_AT_A_TIME_TX
		put_buffer_byte(dev, offset++, *(dest++));
#अन्यथा
		arcnet_outb(*(dest++), ioaddr, COM9026_REG_RW_MEMDATA);
#पूर्ण_अगर
पूर्ण

/* We cannot probe क्रम an IO mapped card either, although we can check that
 * it's where we were told it was, and even स्वतःirq
 */
अटल पूर्णांक __init com90io_probe(काष्ठा net_device *dev)
अणु
	पूर्णांक ioaddr = dev->base_addr, status;
	अचिन्हित दीर्घ airqmask;

	अगर (BUGLVL(D_NORMAL)) अणु
		pr_info("%s\n", "COM90xx IO-mapped mode support (by David Woodhouse et el.)");
		pr_info("E-mail me if you actually test this driver, please!\n");
	पूर्ण

	अगर (!ioaddr) अणु
		arc_prपूर्णांकk(D_NORMAL, dev, "No autoprobe for IO mapped cards; you must specify the base address!\n");
		वापस -ENODEV;
	पूर्ण
	अगर (!request_region(ioaddr, ARCNET_TOTAL_SIZE, "com90io probe")) अणु
		arc_prपूर्णांकk(D_INIT_REASONS, dev, "IO request_region %x-%x failed\n",
			   ioaddr, ioaddr + ARCNET_TOTAL_SIZE - 1);
		वापस -ENXIO;
	पूर्ण
	अगर (arcnet_inb(ioaddr, COM9026_REG_R_STATUS) == 0xFF) अणु
		arc_prपूर्णांकk(D_INIT_REASONS, dev, "IO address %x empty\n",
			   ioaddr);
		जाओ err_out;
	पूर्ण
	arcnet_inb(ioaddr, COM9026_REG_R_RESET);
	mdelay(RESETसमय);

	status = arcnet_inb(ioaddr, COM9026_REG_R_STATUS);

	अगर ((status & 0x9D) != (NORXflag | RECONflag | TXFREEflag | RESETflag)) अणु
		arc_prपूर्णांकk(D_INIT_REASONS, dev, "Status invalid (%Xh)\n",
			   status);
		जाओ err_out;
	पूर्ण
	arc_prपूर्णांकk(D_INIT_REASONS, dev, "Status after reset: %X\n", status);

	arcnet_outb(CFLAGScmd | RESETclear | CONFIGclear,
		    ioaddr, COM9026_REG_W_COMMAND);

	arc_prपूर्णांकk(D_INIT_REASONS, dev, "Status after reset acknowledged: %X\n",
		   status);

	status = arcnet_inb(ioaddr, COM9026_REG_R_STATUS);

	अगर (status & RESETflag) अणु
		arc_prपूर्णांकk(D_INIT_REASONS, dev, "Eternal reset (status=%Xh)\n",
			   status);
		जाओ err_out;
	पूर्ण
	arcnet_outb((0x16 | IOMAPflag) & ~ENABLE16flag,
		    ioaddr, COM9026_REG_RW_CONFIG);

	/* Read first loc'n of memory */

	arcnet_outb(AUTOINCflag, ioaddr, COM9026_REG_W_ADDR_HI);
	arcnet_outb(0, ioaddr,  COM9026_REG_W_ADDR_LO);

	status = arcnet_inb(ioaddr, COM9026_REG_RW_MEMDATA);
	अगर (status != 0xd1) अणु
		arc_prपूर्णांकk(D_INIT_REASONS, dev, "Signature byte not found (%Xh instead).\n",
			   status);
		जाओ err_out;
	पूर्ण
	अगर (!dev->irq) अणु
		/* अगर we करो this, we're sure to get an IRQ since the
		 * card has just reset and the NORXflag is on until
		 * we tell it to start receiving.
		 */

		airqmask = probe_irq_on();
		arcnet_outb(NORXflag, ioaddr, COM9026_REG_W_INTMASK);
		udelay(1);
		arcnet_outb(0, ioaddr, COM9026_REG_W_INTMASK);
		dev->irq = probe_irq_off(airqmask);

		अगर ((पूर्णांक)dev->irq <= 0) अणु
			arc_prपूर्णांकk(D_INIT_REASONS, dev, "Autoprobe IRQ failed\n");
			जाओ err_out;
		पूर्ण
	पूर्ण
	release_region(ioaddr, ARCNET_TOTAL_SIZE); /* end of probing */
	वापस com90io_found(dev);

err_out:
	release_region(ioaddr, ARCNET_TOTAL_SIZE);
	वापस -ENODEV;
पूर्ण

/* Set up the काष्ठा net_device associated with this card.  Called after
 * probing succeeds.
 */
अटल पूर्णांक __init com90io_found(काष्ठा net_device *dev)
अणु
	काष्ठा arcnet_local *lp;
	पूर्णांक ioaddr = dev->base_addr;
	पूर्णांक err;

	/* Reserve the irq */
	अगर (request_irq(dev->irq, arcnet_पूर्णांकerrupt, 0,
			"arcnet (COM90xx-IO)", dev)) अणु
		arc_prपूर्णांकk(D_NORMAL, dev, "Can't get IRQ %d!\n", dev->irq);
		वापस -ENODEV;
	पूर्ण
	/* Reserve the I/O region */
	अगर (!request_region(dev->base_addr, ARCNET_TOTAL_SIZE,
			    "arcnet (COM90xx-IO)")) अणु
		मुक्त_irq(dev->irq, dev);
		वापस -EBUSY;
	पूर्ण

	lp = netdev_priv(dev);
	lp->card_name = "COM90xx I/O";
	lp->hw.command = com90io_command;
	lp->hw.status = com90io_status;
	lp->hw.पूर्णांकmask = com90io_seपंचांगask;
	lp->hw.reset = com90io_reset;
	lp->hw.owner = THIS_MODULE;
	lp->hw.copy_to_card = com90io_copy_to_card;
	lp->hw.copy_from_card = com90io_copy_from_card;

	lp->config = (0x16 | IOMAPflag) & ~ENABLE16flag;
	arcnet_outb(lp->config, ioaddr, COM9026_REG_RW_CONFIG);

	/* get and check the station ID from offset 1 in shmem */

	dev->dev_addr[0] = get_buffer_byte(dev, 1);

	err = रेजिस्टर_netdev(dev);
	अगर (err) अणु
		arcnet_outb(arcnet_inb(ioaddr, COM9026_REG_RW_CONFIG) & ~IOMAPflag,
			    ioaddr, COM9026_REG_RW_CONFIG);
		मुक्त_irq(dev->irq, dev);
		release_region(dev->base_addr, ARCNET_TOTAL_SIZE);
		वापस err;
	पूर्ण

	arc_prपूर्णांकk(D_NORMAL, dev, "COM90IO: station %02Xh found at %03lXh, IRQ %d.\n",
		   dev->dev_addr[0], dev->base_addr, dev->irq);

	वापस 0;
पूर्ण

/* Do a hardware reset on the card, and set up necessary रेजिस्टरs.
 *
 * This should be called as little as possible, because it disrupts the
 * token on the network (causes a RECON) and requires a signअगरicant delay.
 *
 * However, it करोes make sure the card is in a defined state.
 */
अटल पूर्णांक com90io_reset(काष्ठा net_device *dev, पूर्णांक really_reset)
अणु
	काष्ठा arcnet_local *lp = netdev_priv(dev);
	लघु ioaddr = dev->base_addr;

	arc_prपूर्णांकk(D_INIT, dev, "Resetting %s (status=%02Xh)\n",
		   dev->name, arcnet_inb(ioaddr, COM9026_REG_R_STATUS));

	अगर (really_reset) अणु
		/* reset the card */
		arcnet_inb(ioaddr, COM9026_REG_R_RESET);
		mdelay(RESETसमय);
	पूर्ण
	/* Set the thing to IO-mapped, 8-bit  mode */
	lp->config = (0x1C | IOMAPflag) & ~ENABLE16flag;
	arcnet_outb(lp->config, ioaddr, COM9026_REG_RW_CONFIG);

	arcnet_outb(CFLAGScmd | RESETclear, ioaddr, COM9026_REG_W_COMMAND);
					/* clear flags & end reset */
	arcnet_outb(CFLAGScmd | CONFIGclear, ioaddr, COM9026_REG_W_COMMAND);

	/* verअगरy that the ARCnet signature byte is present */
	अगर (get_buffer_byte(dev, 0) != TESTvalue) अणु
		arc_prपूर्णांकk(D_NORMAL, dev, "reset failed: TESTvalue not present.\n");
		वापस 1;
	पूर्ण
	/* enable extended (512-byte) packets */
	arcnet_outb(CONFIGcmd | EXTconf, ioaddr, COM9026_REG_W_COMMAND);
	/* करोne!  वापस success. */
	वापस 0;
पूर्ण

अटल व्योम com90io_command(काष्ठा net_device *dev, पूर्णांक cmd)
अणु
	लघु ioaddr = dev->base_addr;

	arcnet_outb(cmd, ioaddr, COM9026_REG_W_COMMAND);
पूर्ण

अटल पूर्णांक com90io_status(काष्ठा net_device *dev)
अणु
	लघु ioaddr = dev->base_addr;

	वापस arcnet_inb(ioaddr, COM9026_REG_R_STATUS);
पूर्ण

अटल व्योम com90io_seपंचांगask(काष्ठा net_device *dev, पूर्णांक mask)
अणु
	लघु ioaddr = dev->base_addr;

	arcnet_outb(mask, ioaddr, COM9026_REG_W_INTMASK);
पूर्ण

अटल व्योम com90io_copy_to_card(काष्ठा net_device *dev, पूर्णांक bufnum,
				 पूर्णांक offset, व्योम *buf, पूर्णांक count)
अणु
	TIME(dev, "put_whole_buffer", count,
	     put_whole_buffer(dev, bufnum * 512 + offset, count, buf));
पूर्ण

अटल व्योम com90io_copy_from_card(काष्ठा net_device *dev, पूर्णांक bufnum,
				   पूर्णांक offset, व्योम *buf, पूर्णांक count)
अणु
	TIME(dev, "get_whole_buffer", count,
	     get_whole_buffer(dev, bufnum * 512 + offset, count, buf));
पूर्ण

अटल पूर्णांक io;			/* use the insmod io= irq= shmem= options */
अटल पूर्णांक irq;
अटल अक्षर device[9];		/* use eg. device=arc1 to change name */

module_param_hw(io, पूर्णांक, ioport, 0);
module_param_hw(irq, पूर्णांक, irq, 0);
module_param_string(device, device, माप(device), 0);
MODULE_LICENSE("GPL");

#अगर_अघोषित MODULE
अटल पूर्णांक __init com90io_setup(अक्षर *s)
अणु
	पूर्णांक पूर्णांकs[4];

	s = get_options(s, 4, पूर्णांकs);
	अगर (!पूर्णांकs[0])
		वापस 0;
	चयन (पूर्णांकs[0]) अणु
	शेष:		/* ERROR */
		pr_err("Too many arguments\n");
		fallthrough;
	हाल 2:		/* IRQ */
		irq = पूर्णांकs[2];
		fallthrough;
	हाल 1:		/* IO address */
		io = पूर्णांकs[1];
	पूर्ण
	अगर (*s)
		snम_लिखो(device, माप(device), "%s", s);
	वापस 1;
पूर्ण
__setup("com90io=", com90io_setup);
#पूर्ण_अगर

अटल काष्ठा net_device *my_dev;

अटल पूर्णांक __init com90io_init(व्योम)
अणु
	काष्ठा net_device *dev;
	पूर्णांक err;

	dev = alloc_arcdev(device);
	अगर (!dev)
		वापस -ENOMEM;

	dev->base_addr = io;
	dev->irq = irq;
	अगर (dev->irq == 2)
		dev->irq = 9;

	err = com90io_probe(dev);

	अगर (err) अणु
		मुक्त_arcdev(dev);
		वापस err;
	पूर्ण

	my_dev = dev;
	वापस 0;
पूर्ण

अटल व्योम __निकास com90io_निकास(व्योम)
अणु
	काष्ठा net_device *dev = my_dev;
	पूर्णांक ioaddr = dev->base_addr;

	unरेजिस्टर_netdev(dev);

	/* In हाल the old driver is loaded later,
	 * set the thing back to MMAP mode
	 */
	arcnet_outb(arcnet_inb(ioaddr, COM9026_REG_RW_CONFIG) & ~IOMAPflag,
		    ioaddr, COM9026_REG_RW_CONFIG);

	मुक्त_irq(dev->irq, dev);
	release_region(dev->base_addr, ARCNET_TOTAL_SIZE);
	मुक्त_arcdev(dev);
पूर्ण

module_init(com90io_init)
module_निकास(com90io_निकास)
