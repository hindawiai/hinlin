<शैली गुरु>
/*
 * Linux ARCnet driver - COM20020 chipset support
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

#समावेश <linux/module.h>
#समावेश <linux/moduleparam.h>
#समावेश <linux/kernel.h>
#समावेश <linux/types.h>
#समावेश <linux/ioport.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/delay.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/init.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/memblock.h>
#समावेश <linux/पन.स>

#समावेश "arcdevice.h"
#समावेश "com20020.h"

/* We cannot (yet) probe क्रम an IO mapped card, although we can check that
 * it's where we were told it was, and even करो स्वतःirq.
 */
अटल पूर्णांक __init com20020isa_probe(काष्ठा net_device *dev)
अणु
	पूर्णांक ioaddr;
	अचिन्हित दीर्घ airqmask;
	काष्ठा arcnet_local *lp = netdev_priv(dev);
	पूर्णांक err;

	अगर (BUGLVL(D_NORMAL))
		pr_info("%s\n", "COM20020 ISA support (by David Woodhouse et al.)");

	ioaddr = dev->base_addr;
	अगर (!ioaddr) अणु
		arc_prपूर्णांकk(D_NORMAL, dev, "No autoprobe (yet) for IO mapped cards; you must specify the base address!\n");
		वापस -ENODEV;
	पूर्ण
	अगर (!request_region(ioaddr, ARCNET_TOTAL_SIZE, "arcnet (COM20020)")) अणु
		arc_prपूर्णांकk(D_NORMAL, dev, "IO region %xh-%xh already allocated.\n",
			   ioaddr, ioaddr + ARCNET_TOTAL_SIZE - 1);
		वापस -ENXIO;
	पूर्ण
	अगर (arcnet_inb(ioaddr, COM20020_REG_R_STATUS) == 0xFF) अणु
		arc_prपूर्णांकk(D_NORMAL, dev, "IO address %x empty\n", ioaddr);
		err = -ENODEV;
		जाओ out;
	पूर्ण
	अगर (com20020_check(dev)) अणु
		err = -ENODEV;
		जाओ out;
	पूर्ण

	अगर (!dev->irq) अणु
		/* अगर we करो this, we're sure to get an IRQ since the
		 * card has just reset and the NORXflag is on until
		 * we tell it to start receiving.
		 */
		arc_prपूर्णांकk(D_INIT_REASONS, dev, "intmask was %02Xh\n",
			   arcnet_inb(ioaddr, COM20020_REG_R_STATUS));
		arcnet_outb(0, ioaddr, COM20020_REG_W_INTMASK);
		airqmask = probe_irq_on();
		arcnet_outb(NORXflag, ioaddr, COM20020_REG_W_INTMASK);
		udelay(1);
		arcnet_outb(0, ioaddr, COM20020_REG_W_INTMASK);
		dev->irq = probe_irq_off(airqmask);

		अगर ((पूर्णांक)dev->irq <= 0) अणु
			arc_prपूर्णांकk(D_INIT_REASONS, dev, "Autoprobe IRQ failed first time\n");
			airqmask = probe_irq_on();
			arcnet_outb(NORXflag, ioaddr, COM20020_REG_W_INTMASK);
			udelay(5);
			arcnet_outb(0, ioaddr, COM20020_REG_W_INTMASK);
			dev->irq = probe_irq_off(airqmask);
			अगर ((पूर्णांक)dev->irq <= 0) अणु
				arc_prपूर्णांकk(D_NORMAL, dev, "Autoprobe IRQ failed.\n");
				err = -ENODEV;
				जाओ out;
			पूर्ण
		पूर्ण
	पूर्ण

	lp->card_name = "ISA COM20020";

	err = com20020_found(dev, 0);
	अगर (err != 0)
		जाओ out;

	वापस 0;

out:
	release_region(ioaddr, ARCNET_TOTAL_SIZE);
	वापस err;
पूर्ण

अटल पूर्णांक node = 0;
अटल पूर्णांक io = 0x0;		/* <--- EDIT THESE LINES FOR YOUR CONFIGURATION */
अटल पूर्णांक irq = 0;		/* or use the insmod io= irq= shmem= options */
अटल अक्षर device[9];		/* use eg. device="arc1" to change name */
अटल पूर्णांक समयout = 3;
अटल पूर्णांक backplane = 0;
अटल पूर्णांक घड़ीp = 0;
अटल पूर्णांक घड़ीm = 0;

module_param(node, पूर्णांक, 0);
module_param_hw(io, पूर्णांक, ioport, 0);
module_param_hw(irq, पूर्णांक, irq, 0);
module_param_string(device, device, माप(device), 0);
module_param(समयout, पूर्णांक, 0);
module_param(backplane, पूर्णांक, 0);
module_param(घड़ीp, पूर्णांक, 0);
module_param(घड़ीm, पूर्णांक, 0);

MODULE_LICENSE("GPL");

अटल काष्ठा net_device *my_dev;

अटल पूर्णांक __init com20020_init(व्योम)
अणु
	काष्ठा net_device *dev;
	काष्ठा arcnet_local *lp;

	dev = alloc_arcdev(device);
	अगर (!dev)
		वापस -ENOMEM;

	अगर (node && node != 0xff)
		dev->dev_addr[0] = node;

	dev->netdev_ops = &com20020_netdev_ops;

	lp = netdev_priv(dev);
	lp->backplane = backplane;
	lp->घड़ीp = घड़ीp & 7;
	lp->घड़ीm = घड़ीm & 3;
	lp->समयout = समयout & 3;
	lp->hw.owner = THIS_MODULE;

	dev->base_addr = io;
	dev->irq = irq;

	अगर (dev->irq == 2)
		dev->irq = 9;

	अगर (com20020isa_probe(dev)) अणु
		मुक्त_arcdev(dev);
		वापस -EIO;
	पूर्ण

	my_dev = dev;
	वापस 0;
पूर्ण

अटल व्योम __निकास com20020_निकास(व्योम)
अणु
	unरेजिस्टर_netdev(my_dev);
	मुक्त_irq(my_dev->irq, my_dev);
	release_region(my_dev->base_addr, ARCNET_TOTAL_SIZE);
	मुक्त_arcdev(my_dev);
पूर्ण

#अगर_अघोषित MODULE
अटल पूर्णांक __init com20020isa_setup(अक्षर *s)
अणु
	पूर्णांक पूर्णांकs[8];

	s = get_options(s, 8, पूर्णांकs);
	अगर (!पूर्णांकs[0])
		वापस 1;

	चयन (पूर्णांकs[0]) अणु
	शेष:		/* ERROR */
		pr_info("Too many arguments\n");
		fallthrough;
	हाल 6:		/* Timeout */
		समयout = पूर्णांकs[6];
		fallthrough;
	हाल 5:		/* CKP value */
		घड़ीp = पूर्णांकs[5];
		fallthrough;
	हाल 4:		/* Backplane flag */
		backplane = पूर्णांकs[4];
		fallthrough;
	हाल 3:		/* Node ID */
		node = पूर्णांकs[3];
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

__setup("com20020=", com20020isa_setup);

#पूर्ण_अगर				/* MODULE */

module_init(com20020_init)
module_निकास(com20020_निकास)
