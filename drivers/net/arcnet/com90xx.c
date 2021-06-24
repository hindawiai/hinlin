<शैली गुरु>
/*
 * Linux ARCnet driver - COM90xx chipset (memory-mapped buffers)
 *
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
#समावेश <linux/moduleparam.h>
#समावेश <linux/init.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/ioport.h>
#समावेश <linux/delay.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/slab.h>
#समावेश <linux/पन.स>

#समावेश "arcdevice.h"
#समावेश "com9026.h"

/* Define this to speed up the स्वतःprobe by assuming अगर only one io port and
 * shmem are left in the list at Stage 5, they must correspond to each
 * other.
 *
 * This is undefined by शेष because it might not always be true, and the
 * extra check makes the स्वतःprobe even more careful.  Speed demons can turn
 * it on - I think it should be fine अगर you only have one ARCnet card
 * installed.
 *
 * If no ARCnet cards are installed, this delay never happens anyway and thus
 * the option has no effect.
 */
#अघोषित FAST_PROBE

/* Internal function declarations */
अटल पूर्णांक com90xx_found(पूर्णांक ioaddr, पूर्णांक airq, u_दीर्घ shmem, व्योम __iomem *);
अटल व्योम com90xx_command(काष्ठा net_device *dev, पूर्णांक command);
अटल पूर्णांक com90xx_status(काष्ठा net_device *dev);
अटल व्योम com90xx_seपंचांगask(काष्ठा net_device *dev, पूर्णांक mask);
अटल पूर्णांक com90xx_reset(काष्ठा net_device *dev, पूर्णांक really_reset);
अटल व्योम com90xx_copy_to_card(काष्ठा net_device *dev, पूर्णांक bufnum, पूर्णांक offset,
				 व्योम *buf, पूर्णांक count);
अटल व्योम com90xx_copy_from_card(काष्ठा net_device *dev, पूर्णांक bufnum,
				   पूर्णांक offset, व्योम *buf, पूर्णांक count);

/* Known ARCnet cards */

अटल काष्ठा net_device *cards[16];
अटल पूर्णांक numcards;

/* Handy defines क्रम ARCnet specअगरic stuff */

/* The number of low I/O ports used by the card */
#घोषणा ARCNET_TOTAL_SIZE	16

/* Amount of I/O memory used by the card */
#घोषणा BUFFER_SIZE (512)
#घोषणा MIRROR_SIZE (BUFFER_SIZE * 4)

अटल पूर्णांक com90xx_skip_probe __initdata = 0;

/* Module parameters */

अटल पूर्णांक io;			/* use the insmod io= irq= shmem= options */
अटल पूर्णांक irq;
अटल पूर्णांक shmem;
अटल अक्षर device[9];		/* use eg. device=arc1 to change name */

module_param_hw(io, पूर्णांक, ioport, 0);
module_param_hw(irq, पूर्णांक, irq, 0);
module_param(shmem, पूर्णांक, 0);
module_param_string(device, device, माप(device), 0);

अटल व्योम __init com90xx_probe(व्योम)
अणु
	पूर्णांक count, status, ioaddr, numprपूर्णांक, airq, खोलोparen = 0;
	अचिन्हित दीर्घ airqmask;
	पूर्णांक ports[(0x3f0 - 0x200) / 16 + 1] = अणु	0 पूर्ण;
	अचिन्हित दीर्घ *shmems;
	व्योम __iomem **iomem;
	पूर्णांक numports, numshmems, *port;
	u_दीर्घ *p;
	पूर्णांक index;

	अगर (!io && !irq && !shmem && !*device && com90xx_skip_probe)
		वापस;

	shmems = kzalloc(((0x100000 - 0xa0000) / 0x800) * माप(अचिन्हित दीर्घ),
			 GFP_KERNEL);
	अगर (!shmems)
		वापस;
	iomem = kzalloc(((0x100000 - 0xa0000) / 0x800) * माप(व्योम __iomem *),
			GFP_KERNEL);
	अगर (!iomem) अणु
		kमुक्त(shmems);
		वापस;
	पूर्ण

	अगर (BUGLVL(D_NORMAL))
		pr_info("%s\n", "COM90xx chipset support");

	/* set up the arrays where we'll store the possible probe addresses */
	numports = numshmems = 0;
	अगर (io)
		ports[numports++] = io;
	अन्यथा
		क्रम (count = 0x200; count <= 0x3f0; count += 16)
			ports[numports++] = count;
	अगर (shmem)
		shmems[numshmems++] = shmem;
	अन्यथा
		क्रम (count = 0xA0000; count <= 0xFF800; count += 2048)
			shmems[numshmems++] = count;

	/* Stage 1: abanकरोn any reserved ports, or ones with status==0xFF
	 * (empty), and reset any others by पढ़ोing the reset port.
	 */
	numprपूर्णांक = -1;
	क्रम (port = &ports[0]; port - ports < numports; port++) अणु
		numprपूर्णांक++;
		numprपूर्णांक %= 8;
		अगर (!numprपूर्णांक) अणु
			arc_cont(D_INIT, "\n");
			arc_cont(D_INIT, "S1: ");
		पूर्ण
		arc_cont(D_INIT, "%Xh ", *port);

		ioaddr = *port;

		अगर (!request_region(*port, ARCNET_TOTAL_SIZE,
				    "arcnet (90xx)")) अणु
			arc_cont(D_INIT_REASONS, "(request_region)\n");
			arc_cont(D_INIT_REASONS, "S1: ");
			अगर (BUGLVL(D_INIT_REASONS))
				numprपूर्णांक = 0;
			*port-- = ports[--numports];
			जारी;
		पूर्ण
		अगर (arcnet_inb(ioaddr, COM9026_REG_R_STATUS) == 0xFF) अणु
			arc_cont(D_INIT_REASONS, "(empty)\n");
			arc_cont(D_INIT_REASONS, "S1: ");
			अगर (BUGLVL(D_INIT_REASONS))
				numprपूर्णांक = 0;
			release_region(*port, ARCNET_TOTAL_SIZE);
			*port-- = ports[--numports];
			जारी;
		पूर्ण
		/* begin resetting card */
		arcnet_inb(ioaddr, COM9026_REG_R_RESET);

		arc_cont(D_INIT_REASONS, "\n");
		arc_cont(D_INIT_REASONS, "S1: ");
		अगर (BUGLVL(D_INIT_REASONS))
			numprपूर्णांक = 0;
	पूर्ण
	arc_cont(D_INIT, "\n");

	अगर (!numports) अणु
		arc_cont(D_NORMAL, "S1: No ARCnet cards found.\n");
		kमुक्त(shmems);
		kमुक्त(iomem);
		वापस;
	पूर्ण
	/* Stage 2: we have now reset any possible ARCnet cards, so we can't
	 * करो anything until they finish.  If D_INIT, prपूर्णांक the list of
	 * cards that are left.
	 */
	numprपूर्णांक = -1;
	क्रम (port = &ports[0]; port < ports + numports; port++) अणु
		numprपूर्णांक++;
		numprपूर्णांक %= 8;
		अगर (!numprपूर्णांक) अणु
			arc_cont(D_INIT, "\n");
			arc_cont(D_INIT, "S2: ");
		पूर्ण
		arc_cont(D_INIT, "%Xh ", *port);
	पूर्ण
	arc_cont(D_INIT, "\n");
	mdelay(RESETसमय);

	/* Stage 3: abanकरोn any shmem addresses that करोn't have the signature
	 * 0xD1 byte in the right place, or are पढ़ो-only.
	 */
	numprपूर्णांक = -1;
	क्रम (index = 0, p = &shmems[0]; index < numshmems; p++, index++) अणु
		व्योम __iomem *base;

		numprपूर्णांक++;
		numprपूर्णांक %= 8;
		अगर (!numprपूर्णांक) अणु
			arc_cont(D_INIT, "\n");
			arc_cont(D_INIT, "S3: ");
		पूर्ण
		arc_cont(D_INIT, "%lXh ", *p);

		अगर (!request_mem_region(*p, MIRROR_SIZE, "arcnet (90xx)")) अणु
			arc_cont(D_INIT_REASONS, "(request_mem_region)\n");
			arc_cont(D_INIT_REASONS, "Stage 3: ");
			अगर (BUGLVL(D_INIT_REASONS))
				numprपूर्णांक = 0;
			जाओ out;
		पूर्ण
		base = ioremap(*p, MIRROR_SIZE);
		अगर (!base) अणु
			arc_cont(D_INIT_REASONS, "(ioremap)\n");
			arc_cont(D_INIT_REASONS, "Stage 3: ");
			अगर (BUGLVL(D_INIT_REASONS))
				numprपूर्णांक = 0;
			जाओ out1;
		पूर्ण
		अगर (arcnet_पढ़ोb(base, COM9026_REG_R_STATUS) != TESTvalue) अणु
			arc_cont(D_INIT_REASONS, "(%02Xh != %02Xh)\n",
				 arcnet_पढ़ोb(base, COM9026_REG_R_STATUS),
				 TESTvalue);
			arc_cont(D_INIT_REASONS, "S3: ");
			अगर (BUGLVL(D_INIT_REASONS))
				numprपूर्णांक = 0;
			जाओ out2;
		पूर्ण
		/* By writing 0x42 to the TESTvalue location, we also make
		 * sure no "mirror" shmem areas show up - अगर they occur
		 * in another pass through this loop, they will be discarded
		 * because *cptr != TESTvalue.
		 */
		arcnet_ग_लिखोb(0x42, base, COM9026_REG_W_INTMASK);
		अगर (arcnet_पढ़ोb(base, COM9026_REG_R_STATUS) != 0x42) अणु
			arc_cont(D_INIT_REASONS, "(read only)\n");
			arc_cont(D_INIT_REASONS, "S3: ");
			जाओ out2;
		पूर्ण
		arc_cont(D_INIT_REASONS, "\n");
		arc_cont(D_INIT_REASONS, "S3: ");
		अगर (BUGLVL(D_INIT_REASONS))
			numprपूर्णांक = 0;
		iomem[index] = base;
		जारी;
	out2:
		iounmap(base);
	out1:
		release_mem_region(*p, MIRROR_SIZE);
	out:
		*p-- = shmems[--numshmems];
		index--;
	पूर्ण
	arc_cont(D_INIT, "\n");

	अगर (!numshmems) अणु
		arc_cont(D_NORMAL, "S3: No ARCnet cards found.\n");
		क्रम (port = &ports[0]; port < ports + numports; port++)
			release_region(*port, ARCNET_TOTAL_SIZE);
		kमुक्त(shmems);
		kमुक्त(iomem);
		वापस;
	पूर्ण
	/* Stage 4: something of a dummy, to report the shmems that are
	 * still possible after stage 3.
	 */
	numprपूर्णांक = -1;
	क्रम (p = &shmems[0]; p < shmems + numshmems; p++) अणु
		numprपूर्णांक++;
		numprपूर्णांक %= 8;
		अगर (!numprपूर्णांक) अणु
			arc_cont(D_INIT, "\n");
			arc_cont(D_INIT, "S4: ");
		पूर्ण
		arc_cont(D_INIT, "%lXh ", *p);
	पूर्ण
	arc_cont(D_INIT, "\n");

	/* Stage 5: क्रम any ports that have the correct status, can disable
	 * the RESET flag, and (अगर no irq is given) generate an स्वतःirq,
	 * रेजिस्टर an ARCnet device.
	 *
	 * Currently, we can only रेजिस्टर one device per probe, so quit
	 * after the first one is found.
	 */
	numprपूर्णांक = -1;
	क्रम (port = &ports[0]; port < ports + numports; port++) अणु
		पूर्णांक found = 0;

		numprपूर्णांक++;
		numprपूर्णांक %= 8;
		अगर (!numprपूर्णांक) अणु
			arc_cont(D_INIT, "\n");
			arc_cont(D_INIT, "S5: ");
		पूर्ण
		arc_cont(D_INIT, "%Xh ", *port);

		ioaddr = *port;
		status = arcnet_inb(ioaddr, COM9026_REG_R_STATUS);

		अगर ((status & 0x9D)
		    != (NORXflag | RECONflag | TXFREEflag | RESETflag)) अणु
			arc_cont(D_INIT_REASONS, "(status=%Xh)\n", status);
			arc_cont(D_INIT_REASONS, "S5: ");
			अगर (BUGLVL(D_INIT_REASONS))
				numprपूर्णांक = 0;
			release_region(*port, ARCNET_TOTAL_SIZE);
			*port-- = ports[--numports];
			जारी;
		पूर्ण
		arcnet_outb(CFLAGScmd | RESETclear | CONFIGclear,
			    ioaddr, COM9026_REG_W_COMMAND);
		status = arcnet_inb(ioaddr, COM9026_REG_R_STATUS);
		अगर (status & RESETflag) अणु
			arc_cont(D_INIT_REASONS, " (eternal reset, status=%Xh)\n",
				 status);
			arc_cont(D_INIT_REASONS, "S5: ");
			अगर (BUGLVL(D_INIT_REASONS))
				numprपूर्णांक = 0;
			release_region(*port, ARCNET_TOTAL_SIZE);
			*port-- = ports[--numports];
			जारी;
		पूर्ण
		/* skip this completely अगर an IRQ was given, because maybe
		 * we're on a machine that locks during स्वतःirq!
		 */
		अगर (!irq) अणु
			/* अगर we करो this, we're sure to get an IRQ since the
			 * card has just reset and the NORXflag is on until
			 * we tell it to start receiving.
			 */
			airqmask = probe_irq_on();
			arcnet_outb(NORXflag, ioaddr, COM9026_REG_W_INTMASK);
			udelay(1);
			arcnet_outb(0, ioaddr, COM9026_REG_W_INTMASK);
			airq = probe_irq_off(airqmask);

			अगर (airq <= 0) अणु
				arc_cont(D_INIT_REASONS, "(airq=%d)\n", airq);
				arc_cont(D_INIT_REASONS, "S5: ");
				अगर (BUGLVL(D_INIT_REASONS))
					numprपूर्णांक = 0;
				release_region(*port, ARCNET_TOTAL_SIZE);
				*port-- = ports[--numports];
				जारी;
			पूर्ण
		पूर्ण अन्यथा अणु
			airq = irq;
		पूर्ण

		arc_cont(D_INIT, "(%d,", airq);
		खोलोparen = 1;

		/* Everything seems okay.  But which shmem, अगर any, माला_दो
		 * back its signature byte when the card is reset?
		 *
		 * If there are multiple cards installed, there might be
		 * multiple shmems still in the list.
		 */
#अगर_घोषित FAST_PROBE
		अगर (numports > 1 || numshmems > 1) अणु
			arcnet_inb(ioaddr, COM9026_REG_R_RESET);
			mdelay(RESETसमय);
		पूर्ण अन्यथा अणु
			/* just one shmem and port, assume they match */
			arcnet_ग_लिखोb(TESTvalue, iomem[0],
				      COM9026_REG_W_INTMASK);
		पूर्ण
#अन्यथा
		arcnet_inb(ioaddr, COM9026_REG_R_RESET);
		mdelay(RESETसमय);
#पूर्ण_अगर

		क्रम (index = 0; index < numshmems; index++) अणु
			u_दीर्घ ptr = shmems[index];
			व्योम __iomem *base = iomem[index];

			अगर (arcnet_पढ़ोb(base, COM9026_REG_R_STATUS) == TESTvalue) अणु	/* found one */
				arc_cont(D_INIT, "%lXh)\n", *p);
				खोलोparen = 0;

				/* रेजिस्टर the card */
				अगर (com90xx_found(*port, airq, ptr, base) == 0)
					found = 1;
				numprपूर्णांक = -1;

				/* हटाओ shmem from the list */
				shmems[index] = shmems[--numshmems];
				iomem[index] = iomem[numshmems];
				अवरोध;	/* go to the next I/O port */
			पूर्ण अन्यथा अणु
				arc_cont(D_INIT_REASONS, "%Xh-",
					 arcnet_पढ़ोb(base, COM9026_REG_R_STATUS));
			पूर्ण
		पूर्ण

		अगर (खोलोparen) अणु
			अगर (BUGLVL(D_INIT))
				pr_cont("no matching shmem)\n");
			अगर (BUGLVL(D_INIT_REASONS)) अणु
				pr_cont("S5: ");
				numprपूर्णांक = 0;
			पूर्ण
		पूर्ण
		अगर (!found)
			release_region(*port, ARCNET_TOTAL_SIZE);
		*port-- = ports[--numports];
	पूर्ण

	अगर (BUGLVL(D_INIT_REASONS))
		pr_cont("\n");

	/* Now put back TESTvalue on all leftover shmems. */
	क्रम (index = 0; index < numshmems; index++) अणु
		arcnet_ग_लिखोb(TESTvalue, iomem[index], COM9026_REG_W_INTMASK);
		iounmap(iomem[index]);
		release_mem_region(shmems[index], MIRROR_SIZE);
	पूर्ण
	kमुक्त(shmems);
	kमुक्त(iomem);
पूर्ण

अटल पूर्णांक __init check_mirror(अचिन्हित दीर्घ addr, माप_प्रकार size)
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

/* Set up the काष्ठा net_device associated with this card.  Called after
 * probing succeeds.
 */
अटल पूर्णांक __init com90xx_found(पूर्णांक ioaddr, पूर्णांक airq, u_दीर्घ shmem,
				व्योम __iomem *p)
अणु
	काष्ठा net_device *dev = शून्य;
	काष्ठा arcnet_local *lp;
	u_दीर्घ first_mirror, last_mirror;
	पूर्णांक mirror_size;

	/* allocate काष्ठा net_device */
	dev = alloc_arcdev(device);
	अगर (!dev) अणु
		arc_cont(D_NORMAL, "com90xx: Can't allocate device!\n");
		iounmap(p);
		release_mem_region(shmem, MIRROR_SIZE);
		वापस -ENOMEM;
	पूर्ण
	lp = netdev_priv(dev);
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

	iounmap(p);
	release_mem_region(shmem, MIRROR_SIZE);

	अगर (!request_mem_region(dev->mem_start,
				dev->mem_end - dev->mem_start + 1,
				"arcnet (90xx)"))
		जाओ err_मुक्त_dev;

	/* reserve the irq */
	अगर (request_irq(airq, arcnet_पूर्णांकerrupt, 0, "arcnet (90xx)", dev)) अणु
		arc_prपूर्णांकk(D_NORMAL, dev, "Can't get IRQ %d!\n", airq);
		जाओ err_release_mem;
	पूर्ण
	dev->irq = airq;

	/* Initialize the rest of the device काष्ठाure. */
	lp->card_name = "COM90xx";
	lp->hw.command = com90xx_command;
	lp->hw.status = com90xx_status;
	lp->hw.पूर्णांकmask = com90xx_seपंचांगask;
	lp->hw.reset = com90xx_reset;
	lp->hw.owner = THIS_MODULE;
	lp->hw.copy_to_card = com90xx_copy_to_card;
	lp->hw.copy_from_card = com90xx_copy_from_card;
	lp->mem_start = ioremap(dev->mem_start,
				dev->mem_end - dev->mem_start + 1);
	अगर (!lp->mem_start) अणु
		arc_prपूर्णांकk(D_NORMAL, dev, "Can't remap device memory!\n");
		जाओ err_मुक्त_irq;
	पूर्ण

	/* get and check the station ID from offset 1 in shmem */
	dev->dev_addr[0] = arcnet_पढ़ोb(lp->mem_start, COM9026_REG_R_STATION);

	dev->base_addr = ioaddr;

	arc_prपूर्णांकk(D_NORMAL, dev, "COM90xx station %02Xh found at %03lXh, IRQ %d, ShMem %lXh (%ld*%xh).\n",
		   dev->dev_addr[0],
		   dev->base_addr, dev->irq, dev->mem_start,
		   (dev->mem_end - dev->mem_start + 1) / mirror_size,
		   mirror_size);

	अगर (रेजिस्टर_netdev(dev))
		जाओ err_unmap;

	cards[numcards++] = dev;
	वापस 0;

err_unmap:
	iounmap(lp->mem_start);
err_मुक्त_irq:
	मुक्त_irq(dev->irq, dev);
err_release_mem:
	release_mem_region(dev->mem_start, dev->mem_end - dev->mem_start + 1);
err_मुक्त_dev:
	मुक्त_arcdev(dev);
	वापस -EIO;
पूर्ण

अटल व्योम com90xx_command(काष्ठा net_device *dev, पूर्णांक cmd)
अणु
	लघु ioaddr = dev->base_addr;

	arcnet_outb(cmd, ioaddr, COM9026_REG_W_COMMAND);
पूर्ण

अटल पूर्णांक com90xx_status(काष्ठा net_device *dev)
अणु
	लघु ioaddr = dev->base_addr;

	वापस arcnet_inb(ioaddr, COM9026_REG_R_STATUS);
पूर्ण

अटल व्योम com90xx_seपंचांगask(काष्ठा net_device *dev, पूर्णांक mask)
अणु
	लघु ioaddr = dev->base_addr;

	arcnet_outb(mask, ioaddr, COM9026_REG_W_INTMASK);
पूर्ण

/* Do a hardware reset on the card, and set up necessary रेजिस्टरs.
 *
 * This should be called as little as possible, because it disrupts the
 * token on the network (causes a RECON) and requires a signअगरicant delay.
 *
 * However, it करोes make sure the card is in a defined state.
 */
अटल पूर्णांक com90xx_reset(काष्ठा net_device *dev, पूर्णांक really_reset)
अणु
	काष्ठा arcnet_local *lp = netdev_priv(dev);
	लघु ioaddr = dev->base_addr;

	arc_prपूर्णांकk(D_INIT, dev, "Resetting (status=%02Xh)\n",
		   arcnet_inb(ioaddr, COM9026_REG_R_STATUS));

	अगर (really_reset) अणु
		/* reset the card */
		arcnet_inb(ioaddr, COM9026_REG_R_RESET);
		mdelay(RESETसमय);
	पूर्ण
	/* clear flags & end reset */
	arcnet_outb(CFLAGScmd | RESETclear, ioaddr, COM9026_REG_W_COMMAND);
	arcnet_outb(CFLAGScmd | CONFIGclear, ioaddr, COM9026_REG_W_COMMAND);

#अगर 0
	/* करोn't do this until we verify that it doesn't hurt older cards! */
	arcnet_outb(arcnet_inb(ioaddr, COM9026_REG_RW_CONFIG) | ENABLE16flag,
		    ioaddr, COM9026_REG_RW_CONFIG);
#पूर्ण_अगर

	/* verअगरy that the ARCnet signature byte is present */
	अगर (arcnet_पढ़ोb(lp->mem_start, COM9026_REG_R_STATUS) != TESTvalue) अणु
		अगर (really_reset)
			arc_prपूर्णांकk(D_NORMAL, dev, "reset failed: TESTvalue not present.\n");
		वापस 1;
	पूर्ण
	/* enable extended (512-byte) packets */
	arcnet_outb(CONFIGcmd | EXTconf, ioaddr, COM9026_REG_W_COMMAND);

	/* clean out all the memory to make debugging make more sense :) */
	अगर (BUGLVL(D_DURING))
		स_रखो_io(lp->mem_start, 0x42, 2048);

	/* करोne!  वापस success. */
	वापस 0;
पूर्ण

अटल व्योम com90xx_copy_to_card(काष्ठा net_device *dev, पूर्णांक bufnum,
				 पूर्णांक offset, व्योम *buf, पूर्णांक count)
अणु
	काष्ठा arcnet_local *lp = netdev_priv(dev);
	व्योम __iomem *memaddr = lp->mem_start + bufnum * 512 + offset;

	TIME(dev, "memcpy_toio", count, स_नकल_toio(memaddr, buf, count));
पूर्ण

अटल व्योम com90xx_copy_from_card(काष्ठा net_device *dev, पूर्णांक bufnum,
				   पूर्णांक offset, व्योम *buf, पूर्णांक count)
अणु
	काष्ठा arcnet_local *lp = netdev_priv(dev);
	व्योम __iomem *memaddr = lp->mem_start + bufnum * 512 + offset;

	TIME(dev, "memcpy_fromio", count, स_नकल_fromio(buf, memaddr, count));
पूर्ण

MODULE_LICENSE("GPL");

अटल पूर्णांक __init com90xx_init(व्योम)
अणु
	अगर (irq == 2)
		irq = 9;
	com90xx_probe();
	अगर (!numcards)
		वापस -EIO;
	वापस 0;
पूर्ण

अटल व्योम __निकास com90xx_निकास(व्योम)
अणु
	काष्ठा net_device *dev;
	काष्ठा arcnet_local *lp;
	पूर्णांक count;

	क्रम (count = 0; count < numcards; count++) अणु
		dev = cards[count];
		lp = netdev_priv(dev);

		unरेजिस्टर_netdev(dev);
		मुक्त_irq(dev->irq, dev);
		iounmap(lp->mem_start);
		release_region(dev->base_addr, ARCNET_TOTAL_SIZE);
		release_mem_region(dev->mem_start,
				   dev->mem_end - dev->mem_start + 1);
		मुक्त_arcdev(dev);
	पूर्ण
पूर्ण

module_init(com90xx_init);
module_निकास(com90xx_निकास);

#अगर_अघोषित MODULE
अटल पूर्णांक __init com90xx_setup(अक्षर *s)
अणु
	पूर्णांक पूर्णांकs[8];

	s = get_options(s, 8, पूर्णांकs);
	अगर (!पूर्णांकs[0] && !*s) अणु
		pr_notice("Disabled\n");
		वापस 1;
	पूर्ण

	चयन (पूर्णांकs[0]) अणु
	शेष:		/* ERROR */
		pr_err("Too many arguments\n");
		fallthrough;
	हाल 3:		/* Mem address */
		shmem = पूर्णांकs[3];
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

__setup("com90xx=", com90xx_setup);
#पूर्ण_अगर
