<शैली गुरु>
/*
 * Linux ARCnet driver - "RIM I" (entirely mem-mapped) cards
 *
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

अटल पूर्णांक arcrimi_probe(काष्ठा net_device *dev);
अटल पूर्णांक arcrimi_found(काष्ठा net_device *dev);
अटल व्योम arcrimi_command(काष्ठा net_device *dev, पूर्णांक command);
अटल पूर्णांक arcrimi_status(काष्ठा net_device *dev);
अटल व्योम arcrimi_seपंचांगask(काष्ठा net_device *dev, पूर्णांक mask);
अटल पूर्णांक arcrimi_reset(काष्ठा net_device *dev, पूर्णांक really_reset);
अटल व्योम arcrimi_copy_to_card(काष्ठा net_device *dev, पूर्णांक bufnum, पूर्णांक offset,
				 व्योम *buf, पूर्णांक count);
अटल व्योम arcrimi_copy_from_card(काष्ठा net_device *dev, पूर्णांक bufnum,
				   पूर्णांक offset, व्योम *buf, पूर्णांक count);

/* Handy defines क्रम ARCnet specअगरic stuff */

/* Amount of I/O memory used by the card */
#घोषणा BUFFER_SIZE	(512)
#घोषणा MIRROR_SIZE	(BUFFER_SIZE * 4)

/* We cannot probe क्रम a RIM I card; one reason is I करोn't know how to reset
 * them.  In fact, we can't even get their node ID स्वतःmatically.  So, we
 * need to be passed a specअगरic shmem address, IRQ, and node ID.
 */
अटल पूर्णांक __init arcrimi_probe(काष्ठा net_device *dev)
अणु
	अगर (BUGLVL(D_NORMAL)) अणु
		pr_info("%s\n", "RIM I (entirely mem-mapped) support");
		pr_info("E-mail me if you actually test the RIM I driver, please!\n");
		pr_info("Given: node %02Xh, shmem %lXh, irq %d\n",
			dev->dev_addr[0], dev->mem_start, dev->irq);
	पूर्ण

	अगर (dev->mem_start <= 0 || dev->irq <= 0) अणु
		अगर (BUGLVL(D_NORMAL))
			pr_err("No autoprobe for RIM I; you must specify the shmem and irq!\n");
		वापस -ENODEV;
	पूर्ण
	अगर (dev->dev_addr[0] == 0) अणु
		अगर (BUGLVL(D_NORMAL))
			pr_err("You need to specify your card's station ID!\n");
		वापस -ENODEV;
	पूर्ण
	/* Grab the memory region at mem_start क्रम MIRROR_SIZE bytes.
	 * Later in arcrimi_found() the real size will be determined
	 * and this reserve will be released and the correct size
	 * will be taken.
	 */
	अगर (!request_mem_region(dev->mem_start, MIRROR_SIZE, "arcnet (90xx)")) अणु
		अगर (BUGLVL(D_NORMAL))
			pr_notice("Card memory already allocated\n");
		वापस -ENODEV;
	पूर्ण
	वापस arcrimi_found(dev);
पूर्ण

अटल पूर्णांक check_mirror(अचिन्हित दीर्घ addr, माप_प्रकार size)
अणु
	व्योम __iomem *p;
	पूर्णांक res = -1;

	अगर (!request_mem_region(addr, size, "arcnet (90xx)"))
		वापस -1;

	p = ioremap(addr, size);
	अगर (p) अणु
		अगर (arcnet_पढ़ोb(p, COM9026_REG_R_STATUS) == TESTvalue)
			res = 1;
		अन्यथा
			res = 0;
		iounmap(p);
	पूर्ण

	release_mem_region(addr, size);
	वापस res;
पूर्ण

/* Set up the काष्ठा net_device associated with this card.
 * Called after probing succeeds.
 */
अटल पूर्णांक __init arcrimi_found(काष्ठा net_device *dev)
अणु
	काष्ठा arcnet_local *lp;
	अचिन्हित दीर्घ first_mirror, last_mirror, shmem;
	व्योम __iomem *p;
	पूर्णांक mirror_size;
	पूर्णांक err;

	p = ioremap(dev->mem_start, MIRROR_SIZE);
	अगर (!p) अणु
		release_mem_region(dev->mem_start, MIRROR_SIZE);
		arc_prपूर्णांकk(D_NORMAL, dev, "Can't ioremap\n");
		वापस -ENODEV;
	पूर्ण

	/* reserve the irq */
	अगर (request_irq(dev->irq, arcnet_पूर्णांकerrupt, 0, "arcnet (RIM I)", dev)) अणु
		iounmap(p);
		release_mem_region(dev->mem_start, MIRROR_SIZE);
		arc_prपूर्णांकk(D_NORMAL, dev, "Can't get IRQ %d!\n", dev->irq);
		वापस -ENODEV;
	पूर्ण

	shmem = dev->mem_start;
	arcnet_ग_लिखोb(TESTvalue, p, COM9026_REG_W_INTMASK);
	arcnet_ग_लिखोb(TESTvalue, p, COM9026_REG_W_COMMAND);
					/* actually the station/node ID */

	/* find the real shared memory start/end poपूर्णांकs, including mirrors */

	/* guess the actual size of one "memory mirror" - the number of
	 * bytes between copies of the shared memory.  On most cards, it's
	 * 2k (or there are no mirrors at all) but on some, it's 4k.
	 */
	mirror_size = MIRROR_SIZE;
	अगर (arcnet_पढ़ोb(p, COM9026_REG_R_STATUS) == TESTvalue &&
	    check_mirror(shmem - MIRROR_SIZE, MIRROR_SIZE) == 0 &&
	    check_mirror(shmem - 2 * MIRROR_SIZE, MIRROR_SIZE) == 1)
		mirror_size = 2 * MIRROR_SIZE;

	first_mirror = shmem - mirror_size;
	जबतक (check_mirror(first_mirror, mirror_size) == 1)
		first_mirror -= mirror_size;
	first_mirror += mirror_size;

	last_mirror = shmem + mirror_size;
	जबतक (check_mirror(last_mirror, mirror_size) == 1)
		last_mirror += mirror_size;
	last_mirror -= mirror_size;

	dev->mem_start = first_mirror;
	dev->mem_end = last_mirror + MIRROR_SIZE - 1;

	/* initialize the rest of the device काष्ठाure. */

	lp = netdev_priv(dev);
	lp->card_name = "RIM I";
	lp->hw.command = arcrimi_command;
	lp->hw.status = arcrimi_status;
	lp->hw.पूर्णांकmask = arcrimi_seपंचांगask;
	lp->hw.reset = arcrimi_reset;
	lp->hw.owner = THIS_MODULE;
	lp->hw.copy_to_card = arcrimi_copy_to_card;
	lp->hw.copy_from_card = arcrimi_copy_from_card;

	/* re-reserve the memory region - arcrimi_probe() alloced this reqion
	 * but didn't know the real size.  Free that region and then re-get
	 * with the correct size.  There is a VERY slim chance this could
	 * fail.
	 */
	iounmap(p);
	release_mem_region(shmem, MIRROR_SIZE);
	अगर (!request_mem_region(dev->mem_start,
				dev->mem_end - dev->mem_start + 1,
				"arcnet (90xx)")) अणु
		arc_prपूर्णांकk(D_NORMAL, dev, "Card memory already allocated\n");
		जाओ err_मुक्त_irq;
	पूर्ण

	lp->mem_start = ioremap(dev->mem_start,
				dev->mem_end - dev->mem_start + 1);
	अगर (!lp->mem_start) अणु
		arc_prपूर्णांकk(D_NORMAL, dev, "Can't remap device memory!\n");
		जाओ err_release_mem;
	पूर्ण

	/* get and check the station ID from offset 1 in shmem */
	dev->dev_addr[0] = arcnet_पढ़ोb(lp->mem_start, COM9026_REG_R_STATION);

	arc_prपूर्णांकk(D_NORMAL, dev, "ARCnet RIM I: station %02Xh found at IRQ %d, ShMem %lXh (%ld*%d bytes)\n",
		   dev->dev_addr[0],
		   dev->irq, dev->mem_start,
		   (dev->mem_end - dev->mem_start + 1) / mirror_size,
		   mirror_size);

	err = रेजिस्टर_netdev(dev);
	अगर (err)
		जाओ err_unmap;

	वापस 0;

err_unmap:
	iounmap(lp->mem_start);
err_release_mem:
	release_mem_region(dev->mem_start, dev->mem_end - dev->mem_start + 1);
err_मुक्त_irq:
	मुक्त_irq(dev->irq, dev);
	वापस -EIO;
पूर्ण

/* Do a hardware reset on the card, and set up necessary रेजिस्टरs.
 *
 * This should be called as little as possible, because it disrupts the
 * token on the network (causes a RECON) and requires a signअगरicant delay.
 *
 * However, it करोes make sure the card is in a defined state.
 */
अटल पूर्णांक arcrimi_reset(काष्ठा net_device *dev, पूर्णांक really_reset)
अणु
	काष्ठा arcnet_local *lp = netdev_priv(dev);
	व्योम __iomem *ioaddr = lp->mem_start + 0x800;

	arc_prपूर्णांकk(D_INIT, dev, "Resetting %s (status=%02Xh)\n",
		   dev->name, arcnet_पढ़ोb(ioaddr, COM9026_REG_R_STATUS));

	अगर (really_reset) अणु
		arcnet_ग_लिखोb(TESTvalue, ioaddr, -0x800);	/* fake reset */
		वापस 0;
	पूर्ण
	/* clear flags & end reset */
	arcnet_ग_लिखोb(CFLAGScmd | RESETclear, ioaddr, COM9026_REG_W_COMMAND);
	arcnet_ग_लिखोb(CFLAGScmd | CONFIGclear, ioaddr, COM9026_REG_W_COMMAND);

	/* enable extended (512-byte) packets */
	arcnet_ग_लिखोb(CONFIGcmd | EXTconf, ioaddr, COM9026_REG_W_COMMAND);

	/* करोne!  वापस success. */
	वापस 0;
पूर्ण

अटल व्योम arcrimi_seपंचांगask(काष्ठा net_device *dev, पूर्णांक mask)
अणु
	काष्ठा arcnet_local *lp = netdev_priv(dev);
	व्योम __iomem *ioaddr = lp->mem_start + 0x800;

	arcnet_ग_लिखोb(mask, ioaddr, COM9026_REG_W_INTMASK);
पूर्ण

अटल पूर्णांक arcrimi_status(काष्ठा net_device *dev)
अणु
	काष्ठा arcnet_local *lp = netdev_priv(dev);
	व्योम __iomem *ioaddr = lp->mem_start + 0x800;

	वापस arcnet_पढ़ोb(ioaddr, COM9026_REG_R_STATUS);
पूर्ण

अटल व्योम arcrimi_command(काष्ठा net_device *dev, पूर्णांक cmd)
अणु
	काष्ठा arcnet_local *lp = netdev_priv(dev);
	व्योम __iomem *ioaddr = lp->mem_start + 0x800;

	arcnet_ग_लिखोb(cmd, ioaddr, COM9026_REG_W_COMMAND);
पूर्ण

अटल व्योम arcrimi_copy_to_card(काष्ठा net_device *dev, पूर्णांक bufnum, पूर्णांक offset,
				 व्योम *buf, पूर्णांक count)
अणु
	काष्ठा arcnet_local *lp = netdev_priv(dev);
	व्योम __iomem *memaddr = lp->mem_start + 0x800 + bufnum * 512 + offset;

	TIME(dev, "memcpy_toio", count, स_नकल_toio(memaddr, buf, count));
पूर्ण

अटल व्योम arcrimi_copy_from_card(काष्ठा net_device *dev, पूर्णांक bufnum,
				   पूर्णांक offset, व्योम *buf, पूर्णांक count)
अणु
	काष्ठा arcnet_local *lp = netdev_priv(dev);
	व्योम __iomem *memaddr = lp->mem_start + 0x800 + bufnum * 512 + offset;

	TIME(dev, "memcpy_fromio", count, स_नकल_fromio(buf, memaddr, count));
पूर्ण

अटल पूर्णांक node;
अटल पूर्णांक io;			/* use the insmod io= irq= node= options */
अटल पूर्णांक irq;
अटल अक्षर device[9];		/* use eg. device=arc1 to change name */

module_param(node, पूर्णांक, 0);
module_param(io, पूर्णांक, 0);
module_param(irq, पूर्णांक, 0);
module_param_string(device, device, माप(device), 0);
MODULE_LICENSE("GPL");

अटल काष्ठा net_device *my_dev;

अटल पूर्णांक __init arc_rimi_init(व्योम)
अणु
	काष्ठा net_device *dev;

	dev = alloc_arcdev(device);
	अगर (!dev)
		वापस -ENOMEM;

	अगर (node && node != 0xff)
		dev->dev_addr[0] = node;

	dev->mem_start = io;
	dev->irq = irq;
	अगर (dev->irq == 2)
		dev->irq = 9;

	अगर (arcrimi_probe(dev)) अणु
		मुक्त_arcdev(dev);
		वापस -EIO;
	पूर्ण

	my_dev = dev;
	वापस 0;
पूर्ण

अटल व्योम __निकास arc_rimi_निकास(व्योम)
अणु
	काष्ठा net_device *dev = my_dev;
	काष्ठा arcnet_local *lp = netdev_priv(dev);

	unरेजिस्टर_netdev(dev);
	iounmap(lp->mem_start);
	release_mem_region(dev->mem_start, dev->mem_end - dev->mem_start + 1);
	मुक्त_irq(dev->irq, dev);
	मुक्त_arcdev(dev);
पूर्ण

#अगर_अघोषित MODULE
अटल पूर्णांक __init arcrimi_setup(अक्षर *s)
अणु
	पूर्णांक पूर्णांकs[8];

	s = get_options(s, 8, पूर्णांकs);
	अगर (!पूर्णांकs[0])
		वापस 1;
	चयन (पूर्णांकs[0]) अणु
	शेष:		/* ERROR */
		pr_err("Too many arguments\n");
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
__setup("arcrimi=", arcrimi_setup);
#पूर्ण_अगर				/* MODULE */

module_init(arc_rimi_init)
module_निकास(arc_rimi_निकास)
