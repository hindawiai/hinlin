<शैली गुरु>
/*      cops.c: LocalTalk driver क्रम Linux.
 *
 *	Authors:
 *      - Jay Schulist <jschlst@samba.org>
 *
 *	With more than a little help from;
 *	- Alan Cox <alan@lxorguk.ukuu.org.uk>
 *
 *      Derived from:
 *      - skeleton.c: A network driver outline क्रम linux.
 *        Written 1993-94 by Donald Becker.
 *	- ltpc.c: A driver क्रम the LocalTalk PC card.
 *	  Written by Bradक्रमd W. Johnson.
 *
 *      Copyright 1993 United States Government as represented by the
 *      Director, National Security Agency.
 *
 *      This software may be used and distributed according to the terms
 *      of the GNU General Public License, incorporated herein by reference.
 *
 *	Changes:
 *	19970608	Alan Cox	Allowed dual card type support
 *					Can set board type in insmod
 *					Hooks क्रम cops_setup routine
 *					(not yet implemented).
 *	19971101	Jay Schulist	Fixes क्रम multiple lt* devices.
 *	19980607	Steven Hirsch	Fixed the badly broken support
 *					क्रम Tangent type cards. Only
 *                                      tested on Daystar LT200. Some
 *                                      cleanup of क्रमmatting and program
 *                                      logic.  Added emacs 'local-vars'
 *                                      setup क्रम Jay's brace style.
 *	20000211	Alan Cox	Cleaned up क्रम softnet
 */

अटल स्थिर अक्षर *version =
"cops.c:v0.04 6/7/98 Jay Schulist <jschlst@samba.org>\n";
/*
 *  Sources:
 *      COPS Localtalk SDK. This provides almost all of the inक्रमmation
 *      needed.
 */

/*
 * insmod/modprobe configurable stuff.
 *	- IO Port, choose one your card supports or 0 अगर you dare.
 *	- IRQ, also choose one your card supports or nothing and let
 *	  the driver figure it out.
 */

#समावेश <linux/module.h>
#समावेश <linux/kernel.h>
#समावेश <linux/types.h>
#समावेश <linux/fcntl.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/ptrace.h>
#समावेश <linux/ioport.h>
#समावेश <linux/in.h>
#समावेश <linux/माला.स>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/init.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/etherdevice.h>
#समावेश <linux/skbuff.h>
#समावेश <linux/अगर_arp.h>
#समावेश <linux/अगर_ltalk.h>
#समावेश <linux/delay.h>	/* For udelay() */
#समावेश <linux/atalk.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/bitops.h>
#समावेश <linux/jअगरfies.h>

#समावेश <net/Space.h>

#समावेश <यंत्र/पन.स>
#समावेश <यंत्र/dma.h>

#समावेश "cops.h"		/* Our Stuff */
#समावेश "cops_ltdrv.h"		/* Firmware code क्रम Tangent type cards. */
#समावेश "cops_ffdrv.h"		/* Firmware code क्रम Dayna type cards. */

/*
 *      The name of the card. Is used क्रम messages and in the requests क्रम
 *      io regions, irqs and dma channels
 */

अटल स्थिर अक्षर *cardname = "cops";

#अगर_घोषित CONFIG_COPS_DAYNA
अटल पूर्णांक board_type = DAYNA;	/* Module exported */
#अन्यथा
अटल पूर्णांक board_type = TANGENT;
#पूर्ण_अगर

अटल पूर्णांक io = 0x240;		/* Default IO क्रम Dayna */
अटल पूर्णांक irq = 5;		/* Default IRQ */

/*
 *	COPS Autoprobe inक्रमmation.
 *	Right now अगर port address is right but IRQ is not 5 this will
 *      वापस a 5 no matter what since we will still get a status response.
 *      Need one more additional check to narrow करोwn after we have gotten
 *      the ioaddr. But since only other possible IRQs is 3 and 4 so no real
 *	hurry on this. I *STRONGLY* recommend using IRQ 5 क्रम your card with
 *	this driver.
 * 
 *	This driver has 2 modes and they are: Dayna mode and Tangent mode.
 *	Each mode corresponds with the type of card. It has been found
 *	that there are 2 मुख्य types of cards and all other cards are
 *	the same and just have dअगरferent names or only have minor dअगरferences
 *	such as more IO ports. As this driver is tested it will
 *	become more clear on exactly what cards are supported. The driver
 *	शेषs to using Dayna mode. To change the drivers mode, simply
 *	select Dayna or Tangent mode when configuring the kernel.
 *
 *      This driver should support:
 *      TANGENT driver mode:
 *              Tangent ATB-II, Novell NL-1000, Daystar Digital LT-200,
 *		COPS LT-1
 *      DAYNA driver mode:
 *              Dayna DL2000/DaynaTalk PC (Half Length), COPS LT-95, 
 *		Farallon PhoneNET PC III, Farallon PhoneNET PC II
 *	Other cards possibly supported mode unknown though:
 *		Dayna DL2000 (Full length), COPS LT/M (Micro-Channel)
 *
 *	Cards NOT supported by this driver but supported by the ltpc.c
 *	driver written by Bradक्रमd W. Johnson <johns393@maroon.tc.umn.edu>
 *		Farallon PhoneNET PC
 *		Original Apple LocalTalk PC card
 * 
 *      N.B.
 *
 *      The Daystar Digital LT200 boards करो not support पूर्णांकerrupt-driven
 *      IO.  You must specअगरy 'irq=0xff' as a module parameter to invoke
 *      polled mode.  I also believe that the port probing logic is quite
 *      dangerous at best and certainly hopeless क्रम a polled card.  Best to 
 *      specअगरy both. - Steve H.
 *
 */

/*
 * Zero terminated list of IO ports to probe.
 */

अटल अचिन्हित पूर्णांक ports[] = अणु 
	0x240, 0x340, 0x200, 0x210, 0x220, 0x230, 0x260, 
	0x2A0, 0x300, 0x310, 0x320, 0x330, 0x350, 0x360,
	0
पूर्ण;

/*
 * Zero terminated list of IRQ ports to probe.
 */

अटल पूर्णांक cops_irqlist[] = अणु
	5, 4, 3, 0 
पूर्ण;

अटल काष्ठा समयr_list cops_समयr;
अटल काष्ठा net_device *cops_समयr_dev;

/* use 0 क्रम production, 1 क्रम verअगरication, 2 क्रम debug, 3 क्रम verbose debug */
#अगर_अघोषित COPS_DEBUG
#घोषणा COPS_DEBUG 1 
#पूर्ण_अगर
अटल अचिन्हित पूर्णांक cops_debug = COPS_DEBUG;

/* The number of low I/O ports used by the card. */
#घोषणा COPS_IO_EXTENT       8

/* Inक्रमmation that needs to be kept क्रम each board. */

काष्ठा cops_local
अणु
        पूर्णांक board;			/* Holds what board type is. */
	पूर्णांक nodeid;			/* Set to 1 once have nodeid. */
        अचिन्हित अक्षर node_acquire;	/* Node ID when acquired. */
        काष्ठा atalk_addr node_addr;	/* Full node address */
	spinlock_t lock;		/* RX/TX lock */
पूर्ण;

/* Index to functions, as function prototypes. */
अटल पूर्णांक  cops_probe1 (काष्ठा net_device *dev, पूर्णांक ioaddr);
अटल पूर्णांक  cops_irq (पूर्णांक ioaddr, पूर्णांक board);

अटल पूर्णांक  cops_खोलो (काष्ठा net_device *dev);
अटल पूर्णांक  cops_jumpstart (काष्ठा net_device *dev);
अटल व्योम cops_reset (काष्ठा net_device *dev, पूर्णांक sleep);
अटल व्योम cops_load (काष्ठा net_device *dev);
अटल पूर्णांक  cops_nodeid (काष्ठा net_device *dev, पूर्णांक nodeid);

अटल irqवापस_t cops_पूर्णांकerrupt (पूर्णांक irq, व्योम *dev_id);
अटल व्योम cops_poll(काष्ठा समयr_list *t);
अटल व्योम cops_समयout(काष्ठा net_device *dev, अचिन्हित पूर्णांक txqueue);
अटल व्योम cops_rx (काष्ठा net_device *dev);
अटल netdev_tx_t  cops_send_packet (काष्ठा sk_buff *skb,
					    काष्ठा net_device *dev);
अटल व्योम set_multicast_list (काष्ठा net_device *dev);
अटल पूर्णांक  cops_ioctl (काष्ठा net_device *dev, काष्ठा अगरreq *rq, पूर्णांक cmd);
अटल पूर्णांक  cops_बंद (काष्ठा net_device *dev);

अटल व्योम cleanup_card(काष्ठा net_device *dev)
अणु
	अगर (dev->irq)
		मुक्त_irq(dev->irq, dev);
	release_region(dev->base_addr, COPS_IO_EXTENT);
पूर्ण

/*
 *      Check क्रम a network adaptor of this type, and वापस '0' अगरf one exists.
 *      If dev->base_addr == 0, probe all likely locations.
 *      If dev->base_addr in [1..0x1ff], always वापस failure.
 *        otherwise go with what we pass in.
 */
काष्ठा net_device * __init cops_probe(पूर्णांक unit)
अणु
	काष्ठा net_device *dev;
	अचिन्हित *port;
	पूर्णांक base_addr;
	पूर्णांक err = 0;

	dev = alloc_ltalkdev(माप(काष्ठा cops_local));
	अगर (!dev)
		वापस ERR_PTR(-ENOMEM);

	अगर (unit >= 0) अणु
		प्र_लिखो(dev->name, "lt%d", unit);
		netdev_boot_setup_check(dev);
		irq = dev->irq;
		base_addr = dev->base_addr;
	पूर्ण अन्यथा अणु
		base_addr = dev->base_addr = io;
	पूर्ण

	अगर (base_addr > 0x1ff) अणु    /* Check a single specअगरied location. */
		err = cops_probe1(dev, base_addr);
	पूर्ण अन्यथा अगर (base_addr != 0) अणु /* Don't probe at all. */
		err = -ENXIO;
	पूर्ण अन्यथा अणु
		/* FIXME  Does this really work क्रम cards which generate irq?
		 * It's definitely N.G. क्रम polled Tangent. sh
		 * Dayna cards करोn't स्वतःprobe well at all, but अगर your card is
		 * at IRQ 5 & IO 0x240 we find it every समय. ;) JS
		 */
		क्रम (port = ports; *port && cops_probe1(dev, *port) < 0; port++)
			;
		अगर (!*port)
			err = -ENODEV;
	पूर्ण
	अगर (err)
		जाओ out;
	err = रेजिस्टर_netdev(dev);
	अगर (err)
		जाओ out1;
	वापस dev;
out1:
	cleanup_card(dev);
out:
	मुक्त_netdev(dev);
	वापस ERR_PTR(err);
पूर्ण

अटल स्थिर काष्ठा net_device_ops cops_netdev_ops = अणु
	.nकरो_खोलो               = cops_खोलो,
        .nकरो_stop               = cops_बंद,
	.nकरो_start_xmit   	= cops_send_packet,
	.nकरो_tx_समयout		= cops_समयout,
        .nकरो_करो_ioctl           = cops_ioctl,
	.nकरो_set_rx_mode	= set_multicast_list,
पूर्ण;

/*
 *      This is the real probe routine. Linux has a history of मित्रly device
 *      probes on the ISA bus. A good device probes aव्योमs करोing ग_लिखोs, and
 *      verअगरies that the correct device exists and functions.
 */
अटल पूर्णांक __init cops_probe1(काष्ठा net_device *dev, पूर्णांक ioaddr)
अणु
        काष्ठा cops_local *lp;
	अटल अचिन्हित version_prपूर्णांकed;
	पूर्णांक board = board_type;
	पूर्णांक retval;
	
        अगर(cops_debug && version_prपूर्णांकed++ == 0)
		prपूर्णांकk("%s", version);

	/* Grab the region so no one अन्यथा tries to probe our ioports. */
	अगर (!request_region(ioaddr, COPS_IO_EXTENT, dev->name))
		वापस -EBUSY;

        /*
         * Since this board has jumpered पूर्णांकerrupts, allocate the पूर्णांकerrupt
         * vector now. There is no poपूर्णांक in रुकोing since no other device
         * can use the पूर्णांकerrupt, and this marks the irq as busy. Jumpered
         * पूर्णांकerrupts are typically not reported by the boards, and we must
         * used AutoIRQ to find them.
	 */
	dev->irq = irq;
	चयन (dev->irq)
	अणु
		हाल 0:
			/* COPS AutoIRQ routine */
			dev->irq = cops_irq(ioaddr, board);
			अगर (dev->irq)
				अवरोध;
			fallthrough;	/* Once no IRQ found on this port */
		हाल 1:
			retval = -EINVAL;
			जाओ err_out;

		/* Fixup क्रम users that करोn't know that IRQ 2 is really
		 * IRQ 9, or करोn't know which one to set.
		 */
		हाल 2:
			dev->irq = 9;
			अवरोध;

		/* Polled operation requested. Although irq of zero passed as
		 * a parameter tells the init routines to probe, we'll
		 * overload it to denote polled operation at runसमय.
		 */
		हाल 0xff:
			dev->irq = 0;
			अवरोध;

		शेष:
			अवरोध;
	पूर्ण

	dev->base_addr = ioaddr;

	/* Reserve any actual पूर्णांकerrupt. */
	अगर (dev->irq) अणु
		retval = request_irq(dev->irq, cops_पूर्णांकerrupt, 0, dev->name, dev);
		अगर (retval)
			जाओ err_out;
	पूर्ण

        lp = netdev_priv(dev);
        spin_lock_init(&lp->lock);

	/* Copy local board variable to lp काष्ठा. */
	lp->board               = board;

	dev->netdev_ops 	= &cops_netdev_ops;
	dev->watchकरोg_समयo	= HZ * 2;


	/* Tell the user where the card is and what mode we're in. */
	अगर(board==DAYNA)
		prपूर्णांकk("%s: %s at %#3x, using IRQ %d, in Dayna mode.\n", 
			dev->name, cardname, ioaddr, dev->irq);
	अगर(board==TANGENT) अणु
		अगर(dev->irq)
			prपूर्णांकk("%s: %s at %#3x, IRQ %d, in Tangent mode\n", 
				dev->name, cardname, ioaddr, dev->irq);
		अन्यथा
			prपूर्णांकk("%s: %s at %#3x, using polled IO, in Tangent mode.\n", 
				dev->name, cardname, ioaddr);

	पूर्ण
        वापस 0;

err_out:
	release_region(ioaddr, COPS_IO_EXTENT);
	वापस retval;
पूर्ण

अटल पूर्णांक __init cops_irq (पूर्णांक ioaddr, पूर्णांक board)
अणु       /*
         * This करोes not use the IRQ to determine where the IRQ is. We just
         * assume that when we get a correct status response that it's the IRQ.
         * This really just verअगरies the IO port but since we only have access
         * to such a small number of IRQs (5, 4, 3) this is not bad.
         * This will probably not work क्रम more than one card.
         */
        पूर्णांक irqaddr=0;
        पूर्णांक i, x, status;

        अगर(board==DAYNA)
        अणु
                outb(0, ioaddr+DAYNA_RESET);
                inb(ioaddr+DAYNA_RESET);
                mdelay(333);
        पूर्ण
        अगर(board==TANGENT)
        अणु
                inb(ioaddr);
                outb(0, ioaddr);
                outb(0, ioaddr+TANG_RESET);
        पूर्ण

        क्रम(i=0; cops_irqlist[i] !=0; i++)
        अणु
                irqaddr = cops_irqlist[i];
                क्रम(x = 0xFFFF; x>0; x --)    /* रुको क्रम response */
                अणु
                        अगर(board==DAYNA)
                        अणु
                                status = (inb(ioaddr+DAYNA_CARD_STATUS)&3);
                                अगर(status == 1)
                                        वापस irqaddr;
                        पूर्ण
                        अगर(board==TANGENT)
                        अणु
                                अगर((inb(ioaddr+TANG_CARD_STATUS)& TANG_TX_READY) !=0)
                                        वापस irqaddr;
                        पूर्ण
                पूर्ण
        पूर्ण
        वापस 0;       /* no IRQ found */
पूर्ण

/*
 * Open/initialize the board. This is called (in the current kernel)
 * someसमय after booting when the 'ifconfig' program is run.
 */
अटल पूर्णांक cops_खोलो(काष्ठा net_device *dev)
अणु
    काष्ठा cops_local *lp = netdev_priv(dev);

	अगर(dev->irq==0)
	अणु
		/*
		 * I करोn't know अगर the Dayna-style boards support polled 
		 * operation.  For now, only allow it क्रम Tangent.
		 */
		अगर(lp->board==TANGENT)	/* Poll 20 बार per second */
		अणु
		    cops_समयr_dev = dev;
		    समयr_setup(&cops_समयr, cops_poll, 0);
		    cops_समयr.expires 	= jअगरfies + HZ/20;
		    add_समयr(&cops_समयr);
		पूर्ण 
		अन्यथा 
		अणु
			prपूर्णांकk(KERN_WARNING "%s: No irq line set\n", dev->name);
			वापस -EAGAIN;
		पूर्ण
	पूर्ण

	cops_jumpstart(dev);	/* Start the card up. */

	netअगर_start_queue(dev);
        वापस 0;
पूर्ण

/*
 *	This allows क्रम a dynamic start/restart of the entire card.
 */
अटल पूर्णांक cops_jumpstart(काष्ठा net_device *dev)
अणु
	काष्ठा cops_local *lp = netdev_priv(dev);

	/*
         *      Once the card has the firmware loaded and has acquired
         *      the nodeid, अगर it is reset it will lose it all.
         */
        cops_reset(dev,1);	/* Need to reset card beक्रमe load firmware. */
        cops_load(dev);		/* Load the firmware. */

	/*
	 *	If atalkd alपढ़ोy gave us a nodeid we will use that
	 *	one again, अन्यथा we रुको क्रम atalkd to give us a nodeid
	 *	in cops_ioctl. This may cause a problem अगर someone steals
	 *	our nodeid जबतक we are resetting.
	 */	
	अगर(lp->nodeid == 1)
		cops_nodeid(dev,lp->node_acquire);

	वापस 0;
पूर्ण

अटल व्योम tangent_रुको_reset(पूर्णांक ioaddr)
अणु
	पूर्णांक समयout=0;

	जबतक(समयout++ < 5 && (inb(ioaddr+TANG_CARD_STATUS)&TANG_TX_READY)==0)
		mdelay(1);   /* Wait 1 second */
पूर्ण

/*
 *      Reset the LocalTalk board.
 */
अटल व्योम cops_reset(काष्ठा net_device *dev, पूर्णांक sleep)
अणु
        काष्ठा cops_local *lp = netdev_priv(dev);
        पूर्णांक ioaddr=dev->base_addr;

        अगर(lp->board==TANGENT)
        अणु
                inb(ioaddr);		/* Clear request latch. */
                outb(0,ioaddr);		/* Clear the TANG_TX_READY flop. */
                outb(0, ioaddr+TANG_RESET);	/* Reset the adapter. */

		tangent_रुको_reset(ioaddr);
                outb(0, ioaddr+TANG_CLEAR_INT);
        पूर्ण
        अगर(lp->board==DAYNA)
        अणु
                outb(0, ioaddr+DAYNA_RESET);	/* Assert the reset port */
                inb(ioaddr+DAYNA_RESET);	/* Clear the reset */
		अगर (sleep)
			msleep(333);
		अन्यथा
			mdelay(333);
        पूर्ण

	netअगर_wake_queue(dev);
पूर्ण

अटल व्योम cops_load (काष्ठा net_device *dev)
अणु
        काष्ठा अगरreq अगरr;
        काष्ठा ltfirmware *ltf= (काष्ठा ltfirmware *)&अगरr.अगरr_अगरru;
        काष्ठा cops_local *lp = netdev_priv(dev);
        पूर्णांक ioaddr=dev->base_addr;
	पूर्णांक length, i = 0;

        म_नकल(अगरr.अगरr_name,"lt0");

        /* Get card's firmware code and करो some checks on it. */
#अगर_घोषित CONFIG_COPS_DAYNA        
        अगर(lp->board==DAYNA)
        अणु
                ltf->length=माप(ffdrv_code);
                ltf->data=ffdrv_code;
        पूर्ण
        अन्यथा
#पूर्ण_अगर        
#अगर_घोषित CONFIG_COPS_TANGENT
        अगर(lp->board==TANGENT)
        अणु
                ltf->length=माप(ltdrv_code);
                ltf->data=ltdrv_code;
        पूर्ण
        अन्यथा
#पूर्ण_अगर
	अणु
		prपूर्णांकk(KERN_INFO "%s; unsupported board type.\n", dev->name);
		वापस;
	पूर्ण
	
        /* Check to make sure firmware is correct length. */
        अगर(lp->board==DAYNA && ltf->length!=5983)
        अणु
                prपूर्णांकk(KERN_WARNING "%s: Firmware is not length of FFDRV.BIN.\n", dev->name);
                वापस;
        पूर्ण
        अगर(lp->board==TANGENT && ltf->length!=2501)
        अणु
                prपूर्णांकk(KERN_WARNING "%s: Firmware is not length of DRVCODE.BIN.\n", dev->name);
                वापस;
        पूर्ण

        अगर(lp->board==DAYNA)
        अणु
                /*
                 *      We must रुको क्रम a status response
                 *      with the DAYNA board.
                 */
                जबतक(++i<65536)
                अणु
                       अगर((inb(ioaddr+DAYNA_CARD_STATUS)&3)==1)
                                अवरोध;
                पूर्ण

                अगर(i==65536)
                        वापस;
        पूर्ण

        /*
         *      Upload the firmware and kick. Byte-by-byte works nicely here.
         */
	i=0;
        length = ltf->length;
        जबतक(length--)
        अणु
                outb(ltf->data[i], ioaddr);
                i++;
        पूर्ण

	अगर(cops_debug > 1)
		prपूर्णांकk("%s: Uploaded firmware - %d bytes of %d bytes.\n", 
			dev->name, i, ltf->length);

        अगर(lp->board==DAYNA) 	/* Tell Dayna to run the firmware code. */
                outb(1, ioaddr+DAYNA_INT_CARD);
	अन्यथा			/* Tell Tang to run the firmware code. */
		inb(ioaddr);

        अगर(lp->board==TANGENT)
        अणु
                tangent_रुको_reset(ioaddr);
                inb(ioaddr);	/* Clear initial पढ़ोy संकेत. */
        पूर्ण
पूर्ण

/*
 * 	Get the LocalTalk Nodeid from the card. We can suggest
 *	any nodeid 1-254. The card will try and get that exact
 *	address अन्यथा we can specअगरy 0 as the nodeid and the card
 *	will स्वतःprobe क्रम a nodeid.
 */
अटल पूर्णांक cops_nodeid (काष्ठा net_device *dev, पूर्णांक nodeid)
अणु
	काष्ठा cops_local *lp = netdev_priv(dev);
	पूर्णांक ioaddr = dev->base_addr;

	अगर(lp->board == DAYNA)
        अणु
        	/* Empty any pending adapter responses. */
                जबतक((inb(ioaddr+DAYNA_CARD_STATUS)&DAYNA_TX_READY)==0)
                अणु
			outb(0, ioaddr+COPS_CLEAR_INT);	/* Clear पूर्णांकerrupts. */
        		अगर((inb(ioaddr+DAYNA_CARD_STATUS)&0x03)==DAYNA_RX_REQUEST)
                		cops_rx(dev);	/* Kick any packets रुकोing. */
			schedule();
                पूर्ण

                outb(2, ioaddr);       	/* Output command packet length as 2. */
                outb(0, ioaddr);
                outb(LAP_INIT, ioaddr);	/* Send LAP_INIT command byte. */
                outb(nodeid, ioaddr);  	/* Suggest node address. */
        पूर्ण

	अगर(lp->board == TANGENT)
        अणु
                /* Empty any pending adapter responses. */
                जबतक(inb(ioaddr+TANG_CARD_STATUS)&TANG_RX_READY)
                अणु
			outb(0, ioaddr+COPS_CLEAR_INT);	/* Clear पूर्णांकerrupt. */
                	cops_rx(dev);          	/* Kick out packets रुकोing. */
			schedule();
                पूर्ण

		/* Not sure what Tangent करोes अगर nodeid picked is used. */
                अगर(nodeid == 0)	         		/* Seed. */
                	nodeid = jअगरfies&0xFF;		/* Get a अक्रमom try */
                outb(2, ioaddr);        		/* Command length LSB */
                outb(0, ioaddr);       			/* Command length MSB */
                outb(LAP_INIT, ioaddr); 		/* Send LAP_INIT byte */
                outb(nodeid, ioaddr); 		  	/* LAP address hपूर्णांक. */
                outb(0xFF, ioaddr);     		/* Int. level to use */
        पूर्ण

	lp->node_acquire=0;		/* Set nodeid holder to 0. */
        जबतक(lp->node_acquire==0)	/* Get *True* nodeid finally. */
	अणु
		outb(0, ioaddr+COPS_CLEAR_INT);	/* Clear any पूर्णांकerrupt. */

		अगर(lp->board == DAYNA)
		अणु
                	अगर((inb(ioaddr+DAYNA_CARD_STATUS)&0x03)==DAYNA_RX_REQUEST)
                		cops_rx(dev);	/* Grab the nodeid put in lp->node_acquire. */
		पूर्ण
		अगर(lp->board == TANGENT)
		अणु	
			अगर(inb(ioaddr+TANG_CARD_STATUS)&TANG_RX_READY)
                                cops_rx(dev);   /* Grab the nodeid put in lp->node_acquire. */
		पूर्ण
		schedule();
	पूर्ण

	अगर(cops_debug > 1)
		prपूर्णांकk(KERN_DEBUG "%s: Node ID %d has been acquired.\n", 
			dev->name, lp->node_acquire);

	lp->nodeid=1;	/* Set got nodeid to 1. */

        वापस 0;
पूर्ण

/*
 *	Poll the Tangent type cards to see अगर we have work.
 */
 
अटल व्योम cops_poll(काष्ठा समयr_list *unused)
अणु
	पूर्णांक ioaddr, status;
	पूर्णांक boguscount = 0;
	काष्ठा net_device *dev = cops_समयr_dev;

	del_समयr(&cops_समयr);

	अगर(dev == शून्य)
		वापस;	/* We've been करोwned */

	ioaddr = dev->base_addr;
	करो अणु
		status=inb(ioaddr+TANG_CARD_STATUS);
		अगर(status & TANG_RX_READY)
			cops_rx(dev);
		अगर(status & TANG_TX_READY)
			netअगर_wake_queue(dev);
		status = inb(ioaddr+TANG_CARD_STATUS);
	पूर्ण जबतक((++boguscount < 20) && (status&(TANG_RX_READY|TANG_TX_READY)));

	/* poll 20 बार per second */
	cops_समयr.expires = jअगरfies + HZ/20;
	add_समयr(&cops_समयr);
पूर्ण

/*
 *      The typical workload of the driver:
 *      Handle the network पूर्णांकerface पूर्णांकerrupts.
 */
अटल irqवापस_t cops_पूर्णांकerrupt(पूर्णांक irq, व्योम *dev_id)
अणु
        काष्ठा net_device *dev = dev_id;
        काष्ठा cops_local *lp;
        पूर्णांक ioaddr, status;
        पूर्णांक boguscount = 0;

        ioaddr = dev->base_addr;
        lp = netdev_priv(dev);

	अगर(lp->board==DAYNA)
	अणु
		करो अणु
			outb(0, ioaddr + COPS_CLEAR_INT);
                       	status=inb(ioaddr+DAYNA_CARD_STATUS);
                       	अगर((status&0x03)==DAYNA_RX_REQUEST)
                       	        cops_rx(dev);
                	netअगर_wake_queue(dev);
		पूर्ण जबतक(++boguscount < 20);
	पूर्ण
	अन्यथा
	अणु
		करो अणु
                       	status=inb(ioaddr+TANG_CARD_STATUS);
			अगर(status & TANG_RX_READY)
				cops_rx(dev);
			अगर(status & TANG_TX_READY)
				netअगर_wake_queue(dev);
			status=inb(ioaddr+TANG_CARD_STATUS);
		पूर्ण जबतक((++boguscount < 20) && (status&(TANG_RX_READY|TANG_TX_READY)));
	पूर्ण

        वापस IRQ_HANDLED;
पूर्ण

/*
 *      We have a good packet(s), get it/them out of the buffers.
 */
अटल व्योम cops_rx(काष्ठा net_device *dev)
अणु
        पूर्णांक pkt_len = 0;
        पूर्णांक rsp_type = 0;
        काष्ठा sk_buff *skb = शून्य;
        काष्ठा cops_local *lp = netdev_priv(dev);
        पूर्णांक ioaddr = dev->base_addr;
        पूर्णांक boguscount = 0;
        अचिन्हित दीर्घ flags;


	spin_lock_irqsave(&lp->lock, flags);
	
        अगर(lp->board==DAYNA)
        अणु
                outb(0, ioaddr);                /* Send out Zero length. */
                outb(0, ioaddr);
                outb(DATA_READ, ioaddr);        /* Send पढ़ो command out. */

                /* Wait क्रम DMA to turn around. */
                जबतक(++boguscount<1000000)
                अणु
			barrier();
                        अगर((inb(ioaddr+DAYNA_CARD_STATUS)&0x03)==DAYNA_RX_READY)
                                अवरोध;
                पूर्ण

                अगर(boguscount==1000000)
                अणु
                        prपूर्णांकk(KERN_WARNING "%s: DMA timed out.\n",dev->name);
			spin_unlock_irqrestore(&lp->lock, flags);
                        वापस;
                पूर्ण
        पूर्ण

        /* Get response length. */
	pkt_len = inb(ioaddr);
        pkt_len |= (inb(ioaddr) << 8);
        /* Input IO code. */
        rsp_type=inb(ioaddr);

        /* Malloc up new buffer. */
        skb = dev_alloc_skb(pkt_len);
        अगर(skb == शून्य)
        अणु
                prपूर्णांकk(KERN_WARNING "%s: Memory squeeze, dropping packet.\n",
			dev->name);
                dev->stats.rx_dropped++;
                जबतक(pkt_len--)        /* Discard packet */
                        inb(ioaddr);
                spin_unlock_irqrestore(&lp->lock, flags);
                वापस;
        पूर्ण
        skb->dev = dev;
        skb_put(skb, pkt_len);
        skb->protocol = htons(ETH_P_LOCALTALK);

        insb(ioaddr, skb->data, pkt_len);               /* Eat the Data */

        अगर(lp->board==DAYNA)
                outb(1, ioaddr+DAYNA_INT_CARD);         /* Interrupt the card */

        spin_unlock_irqrestore(&lp->lock, flags);  /* Restore पूर्णांकerrupts. */

        /* Check क्रम bad response length */
        अगर(pkt_len < 0 || pkt_len > MAX_LLAP_SIZE)
        अणु
		prपूर्णांकk(KERN_WARNING "%s: Bad packet length of %d bytes.\n", 
			dev->name, pkt_len);
                dev->stats.tx_errors++;
                dev_kमुक्त_skb_any(skb);
                वापस;
        पूर्ण

        /* Set nodeid and then get out. */
        अगर(rsp_type == LAP_INIT_RSP)
        अणु	/* Nodeid taken from received packet. */
                lp->node_acquire = skb->data[0];
                dev_kमुक्त_skb_any(skb);
                वापस;
        पूर्ण

        /* One last check to make sure we have a good packet. */
        अगर(rsp_type != LAP_RESPONSE)
        अणु
                prपूर्णांकk(KERN_WARNING "%s: Bad packet type %d.\n", dev->name, rsp_type);
                dev->stats.tx_errors++;
                dev_kमुक्त_skb_any(skb);
                वापस;
        पूर्ण

        skb_reset_mac_header(skb);    /* Poपूर्णांक to entire packet. */
        skb_pull(skb,3);
        skb_reset_transport_header(skb);    /* Poपूर्णांक to data (Skip header). */

        /* Update the counters. */
        dev->stats.rx_packets++;
        dev->stats.rx_bytes += skb->len;

        /* Send packet to a higher place. */
        netअगर_rx(skb);
पूर्ण

अटल व्योम cops_समयout(काष्ठा net_device *dev, अचिन्हित पूर्णांक txqueue)
अणु
        काष्ठा cops_local *lp = netdev_priv(dev);
        पूर्णांक ioaddr = dev->base_addr;

	dev->stats.tx_errors++;
        अगर(lp->board==TANGENT)
        अणु
		अगर((inb(ioaddr+TANG_CARD_STATUS)&TANG_TX_READY)==0)
               		prपूर्णांकk(KERN_WARNING "%s: No TX complete interrupt.\n", dev->name);
	पूर्ण
	prपूर्णांकk(KERN_WARNING "%s: Transmit timed out.\n", dev->name);
	cops_jumpstart(dev);	/* Restart the card. */
	netअगर_trans_update(dev); /* prevent tx समयout */
	netअगर_wake_queue(dev);
पूर्ण


/*
 *	Make the card transmit a LocalTalk packet.
 */

अटल netdev_tx_t cops_send_packet(काष्ठा sk_buff *skb,
					  काष्ठा net_device *dev)
अणु
        काष्ठा cops_local *lp = netdev_priv(dev);
        पूर्णांक ioaddr = dev->base_addr;
        अचिन्हित दीर्घ flags;

        /*
         * Block a समयr-based transmit from overlapping. 
	 */
	 
	netअगर_stop_queue(dev);

	spin_lock_irqsave(&lp->lock, flags);
	अगर(lp->board == DAYNA)	 /* Wait क्रम adapter transmit buffer. */
		जबतक((inb(ioaddr+DAYNA_CARD_STATUS)&DAYNA_TX_READY)==0)
			cpu_relax();
	अगर(lp->board == TANGENT) /* Wait क्रम adapter transmit buffer. */
		जबतक((inb(ioaddr+TANG_CARD_STATUS)&TANG_TX_READY)==0)
			cpu_relax();

	/* Output IO length. */
	outb(skb->len, ioaddr);
	outb(skb->len >> 8, ioaddr);

	/* Output IO code. */
	outb(LAP_WRITE, ioaddr);

	अगर(lp->board == DAYNA)	/* Check the transmit buffer again. */
        	जबतक((inb(ioaddr+DAYNA_CARD_STATUS)&DAYNA_TX_READY)==0);

	outsb(ioaddr, skb->data, skb->len);	/* Send out the data. */

	अगर(lp->board==DAYNA)	/* Dayna requires you kick the card */
		outb(1, ioaddr+DAYNA_INT_CARD);

	spin_unlock_irqrestore(&lp->lock, flags);	/* Restore पूर्णांकerrupts. */

	/* Done sending packet, update counters and cleanup. */
	dev->stats.tx_packets++;
	dev->stats.tx_bytes += skb->len;
	dev_kमुक्त_skb (skb);
	वापस NETDEV_TX_OK;
पूर्ण

/*
 *	Dummy function to keep the Appletalk layer happy.
 */
 
अटल व्योम set_multicast_list(काष्ठा net_device *dev)
अणु
        अगर(cops_debug >= 3)
		prपूर्णांकk("%s: set_multicast_list executed\n", dev->name);
पूर्ण

/*
 *      System ioctls क्रम the COPS LocalTalk card.
 */
 
अटल पूर्णांक cops_ioctl(काष्ठा net_device *dev, काष्ठा अगरreq *अगरr, पूर्णांक cmd)
अणु
        काष्ठा cops_local *lp = netdev_priv(dev);
        काष्ठा sockaddr_at *sa = (काष्ठा sockaddr_at *)&अगरr->अगरr_addr;
        काष्ठा atalk_addr *aa = &lp->node_addr;

        चयन(cmd)
        अणु
                हाल SIOCSIFADDR:
			/* Get and set the nodeid and network # atalkd wants. */
			cops_nodeid(dev, sa->sat_addr.s_node);
			aa->s_net               = sa->sat_addr.s_net;
                        aa->s_node              = lp->node_acquire;

			/* Set broardcast address. */
                        dev->broadcast[0]       = 0xFF;
			
			/* Set hardware address. */
                        dev->dev_addr[0]        = aa->s_node;
                        dev->addr_len           = 1;
                        वापस 0;

                हाल SIOCGIFADDR:
                        sa->sat_addr.s_net      = aa->s_net;
                        sa->sat_addr.s_node     = aa->s_node;
                        वापस 0;

                शेष:
                        वापस -EOPNOTSUPP;
        पूर्ण
पूर्ण

/*
 *	The inverse routine to cops_खोलो().
 */
 
अटल पूर्णांक cops_बंद(काष्ठा net_device *dev)
अणु
	काष्ठा cops_local *lp = netdev_priv(dev);

	/* If we were running polled, yank the समयr.
	 */
	अगर(lp->board==TANGENT && dev->irq==0)
		del_समयr(&cops_समयr);

	netअगर_stop_queue(dev);
        वापस 0;
पूर्ण


#अगर_घोषित MODULE
अटल काष्ठा net_device *cops_dev;

MODULE_LICENSE("GPL");
module_param_hw(io, पूर्णांक, ioport, 0);
module_param_hw(irq, पूर्णांक, irq, 0);
module_param_hw(board_type, पूर्णांक, other, 0);

अटल पूर्णांक __init cops_module_init(व्योम)
अणु
	अगर (io == 0)
		prपूर्णांकk(KERN_WARNING "%s: You shouldn't autoprobe with insmod\n",
			cardname);
	cops_dev = cops_probe(-1);
	वापस PTR_ERR_OR_ZERO(cops_dev);
पूर्ण

अटल व्योम __निकास cops_module_निकास(व्योम)
अणु
	unरेजिस्टर_netdev(cops_dev);
	cleanup_card(cops_dev);
	मुक्त_netdev(cops_dev);
पूर्ण
module_init(cops_module_init);
module_निकास(cops_module_निकास);
#पूर्ण_अगर /* MODULE */
