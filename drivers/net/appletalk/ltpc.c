<शैली गुरु>
/***    ltpc.c -- a driver क्रम the LocalTalk PC card.
 *
 *      Copyright (c) 1995,1996 Bradक्रमd W. Johnson <johns393@maroon.tc.umn.edu>
 *
 *      This software may be used and distributed according to the terms
 *      of the GNU General Public License, incorporated herein by reference.
 *
 *      This is ALPHA code at best.  It may not work क्रम you.  It may
 *      damage your equipment.  It may damage your relations with other
 *      users of your network.  Use it at your own risk!
 *
 *      Based in part on:
 *      skeleton.c      by Donald Becker
 *      dummy.c         by Nick Holloway and Alan Cox
 *      loopback.c      by Ross Biro, Fred van Kampen, Donald Becker
 *      the netatalk source code (UMICH)
 *      lots of work on the card...
 *
 *      I करो not have access to the (proprietary) SDK that goes with the card.
 *      If you करो, I करोn't want to know about it, and you can probably ग_लिखो
 *      a better driver yourself anyway.  This करोes mean that the pieces that
 *      talk to the card are guesswork on my part, so use at your own risk!
 *
 *      This is my first try at writing Linux networking code, and is also
 *      guesswork.  Again, use at your own risk!  (Although on this part, I'd
 *      welcome suggestions)
 *
 *      This is a loadable kernel module which seems to work at my site
 *      consisting of a 1.2.13 linux box running netatalk 1.3.3, and with
 *      the kernel support from 1.3.3b2 including patches routing.patch
 *      and ddp.disappears.from.chooser.  In order to run it, you will need
 *      to patch ddp.c and aarp.c in the kernel, but only a little...
 *
 *      I'm fairly confident that जबतक this is arguably badly written, the
 *      problems that people experience will be "higher level", that is, with
 *      complications in the netatalk code.  The driver itself करोesn't करो
 *      anything terribly complicated -- it pretends to be an ether device
 *      as far as netatalk is concerned, strips the DDP data out of the ether
 *      frame and builds a LLAP packet to send out the card.  In the other
 *      direction, it receives LLAP frames from the card and builds a fake
 *      ether packet that it then tosses up to the networking code.  You can
 *      argue (correctly) that this is an ugly way to करो things, but it
 *      requires a minimal amount of fooling with the code in ddp.c and aarp.c.
 *
 *      The card will करो a lot more than is used here -- I *think* it has the
 *      layers up through ATP.  Even अगर you knew how that part works (which I
 *      करोn't) it would be a big job to carve up the kernel ddp code to insert
 *      things at a higher level, and probably a bad idea...
 *
 *      There are a number of other cards that करो LocalTalk on the PC.  If
 *      nobody finds any insurmountable (at the netatalk level) problems
 *      here, this driver should encourage people to put some work पूर्णांकo the
 *      other cards (some of which I gather are still commercially available)
 *      and also to put hooks क्रम LocalTalk पूर्णांकo the official ddp code.
 *
 *      I welcome comments and suggestions.  This is my first try at Linux
 *      networking stuff, and there are probably lots of things that I did
 *      suboptimally.  
 *
 ***/

/***
 *
 * $Log: ltpc.c,v $
 * Revision 1.1.2.1  2000/03/01 05:35:07  jgarzik
 * at and tr cleanup
 *
 * Revision 1.8  1997/01/28 05:44:54  bradक्रमd
 * Clean up क्रम non-module a little.
 * Hacked about a bit to clean things up - Alan Cox 
 * Probably broken it from the origina 1.8
 *

 * 1998/11/09: David Huggins-Daines <dhd@debian.org>
 * Cleaned up the initialization code to use the standard स्वतःirq methods,
   and to probe क्रम things in the standard order of i/o, irq, dma.  This
   हटाओs the "reset the reset" hack, because I couldn't figure out an
   easy way to get the card to trigger an पूर्णांकerrupt after it.
 * Added support क्रम passing configuration parameters on the kernel command
   line and through insmod
 * Changed the device name from "ltalk0" to "lt0", both to conक्रमm with the
   other localtalk driver, and to clear up the inconsistency between the
   module and the non-module versions of the driver :-)
 * Added a bunch of comments (I was going to make some क्रमागतs क्रम the state
   codes and the रेजिस्टर offsets, but I'm still not sure exactly what their
   semantics are)
 * Don't poll anymore in पूर्णांकerrupt-driven mode
 * It seems to work as a module now (as of 2.1.127), but I करोn't think
   I'm responsible क्रम that...

 *
 * Revision 1.7  1996/12/12 03:42:33  bradक्रमd
 * DMA alloc cribbed from 3c505.c.
 *
 * Revision 1.6  1996/12/12 03:18:58  bradक्रमd
 * Added virt_to_bus; works in 2.1.13.
 *
 * Revision 1.5  1996/12/12 03:13:22  root
 * xmitQel initialization -- think through better though.
 *
 * Revision 1.4  1996/06/18 14:55:55  root
 * Change names to ltpc. Tअसल. Took a shot at dma alloc,
 * although more needs to be करोne eventually.
 *
 * Revision 1.3  1996/05/22 14:59:39  root
 * Change dev->खोलो, dev->बंद to track dummy.c in 1.99.(around 7)
 *
 * Revision 1.2  1996/05/22 14:58:24  root
 * Change tअसल mostly.
 *
 * Revision 1.1  1996/04/23 04:45:09  root
 * Initial revision
 *
 * Revision 0.16  1996/03/05 15:59:56  root
 * Change ARPHRD_LOCALTLK definition to the "real" one.
 *
 * Revision 0.15  1996/03/05 06:28:30  root
 * Changes क्रम kernel 1.3.70.  Still need a few patches to kernel, but
 * it's getting बंदr.
 *
 * Revision 0.14  1996/02/25 17:38:32  root
 * More cleanups.  Removed query to card on get_stats.
 *
 * Revision 0.13  1996/02/21  16:27:40  root
 * Refix debug_prपूर्णांक_skb.  Fix mac.raw gotcha that appeared in 1.3.65.
 * Clean up receive code a little.
 *
 * Revision 0.12  1996/02/19  16:34:53  root
 * Fix debug_prपूर्णांक_skb.  Kludge outgoing snet to 0 when using startup
 * range.  Change debug to mask: 1 क्रम verbose, 2 क्रम higher level stuff
 * including packet prपूर्णांकing, 4 क्रम lower level (card i/o) stuff.
 *
 * Revision 0.11  1996/02/12  15:53:38  root
 * Added router sends (requires new aarp.c patch)
 *
 * Revision 0.10  1996/02/11  00:19:35  root
 * Change source LTALK_LOGGING debug चयन to insmod ... debug=2.
 *
 * Revision 0.9  1996/02/10  23:59:35  root
 * Fixed those fixes क्रम 1.2 -- DANGER!  The at.h that comes with netatalk
 * has a *dअगरferent* definition of काष्ठा sockaddr_at than the Linux kernel
 * करोes.  This is an "insidious and invidious" bug...
 * (Actually the preceding comment is false -- it's the atalk.h in the
 * ancient atalk-0.06 that's the problem)
 *
 * Revision 0.8  1996/02/10 19:09:00  root
 * Merge 1.3 changes.  Tested OK under 1.3.60.
 *
 * Revision 0.7  1996/02/10 17:56:56  root
 * Added debug=1 parameter on insmod क्रम debugging prपूर्णांकs.  Tried
 * to fix समयr unload on rmmod, but I करोn't think that's the problem.
 *
 * Revision 0.6  1995/12/31  19:01:09  root
 * Clean up rmmod, irq comments per feedback from Corin Anderson (Thanks Corey!)
 * Clean up initial probing -- someबार the card wakes up latched in reset.
 *
 * Revision 0.5  1995/12/22  06:03:44  root
 * Added comments in front and cleaned up a bit.
 * This version sent out to people.
 *
 * Revision 0.4  1995/12/18  03:46:44  root
 * Return लघुDDP to दीर्घDDP fake to 0/0.  Added command काष्ठाs.
 *
 ***/

/* ltpc jumpers are:
*
*	Interrupts -- set at most one.  If none are set, the driver uses
*	polled mode.  Because the card was developed in the XT era, the
*	original करोcumentation refers to IRQ2.  Since you'll be running
*	this on an AT (or later) class machine, that really means IRQ9.
*
*	SW1	IRQ 4
*	SW2	IRQ 3
*	SW3	IRQ 9 (2 in original card करोcumentation only applies to XT)
*
*
*	DMA -- choose DMA 1 or 3, and set both corresponding चयनes.
*
*	SW4	DMA 3
*	SW5	DMA 1
*	SW6	DMA 3
*	SW7	DMA 1
*
*
*	I/O address -- choose one.  
*
*	SW8	220 / 240
*/

/*	To have some stuff logged, करो 
*	insmod ltpc.o debug=1
*
*	For a whole bunch of stuff, use higher numbers.
*
*	The शेष is 0, i.e. no messages except क्रम the probe results.
*/

/* insmod-tweakable variables */
अटल पूर्णांक debug;
#घोषणा DEBUG_VERBOSE 1
#घोषणा DEBUG_UPPER 2
#घोषणा DEBUG_LOWER 4

अटल पूर्णांक io;
अटल पूर्णांक irq;
अटल पूर्णांक dma;

#समावेश <linux/module.h>
#समावेश <linux/kernel.h>
#समावेश <linux/types.h>
#समावेश <linux/fcntl.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/ptrace.h>
#समावेश <linux/ioport.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/in.h>
#समावेश <linux/माला.स>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/init.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/etherdevice.h>
#समावेश <linux/skbuff.h>
#समावेश <linux/अगर_arp.h>
#समावेश <linux/अगर_ltalk.h>
#समावेश <linux/delay.h>
#समावेश <linux/समयr.h>
#समावेश <linux/atalk.h>
#समावेश <linux/bitops.h>
#समावेश <linux/gfp.h>

#समावेश <net/Space.h>

#समावेश <यंत्र/dma.h>
#समावेश <यंत्र/पन.स>

/* our stuff */
#समावेश "ltpc.h"

अटल DEFINE_SPINLOCK(txqueue_lock);
अटल DEFINE_SPINLOCK(mbox_lock);

/* function prototypes */
अटल पूर्णांक करो_पढ़ो(काष्ठा net_device *dev, व्योम *cbuf, पूर्णांक cbuflen,
	व्योम *dbuf, पूर्णांक dbuflen);
अटल पूर्णांक sendup_buffer (काष्ठा net_device *dev);

/* Dma Memory related stuff, cribbed directly from 3c505.c */

अटल अचिन्हित दीर्घ dma_mem_alloc(पूर्णांक size)
अणु
        पूर्णांक order = get_order(size);

        वापस __get_dma_pages(GFP_KERNEL, order);
पूर्ण

/* DMA data buffer, DMA command buffer */
अटल अचिन्हित अक्षर *ltdmabuf;
अटल अचिन्हित अक्षर *ltdmacbuf;

/* निजी काष्ठा, holds our appletalk address */

काष्ठा ltpc_निजी
अणु
	काष्ठा atalk_addr my_addr;
पूर्ण;

/* transmit queue element काष्ठा */

काष्ठा xmitQel अणु
	काष्ठा xmitQel *next;
	/* command buffer */
	अचिन्हित अक्षर *cbuf;
	लघु cbuflen;
	/* data buffer */
	अचिन्हित अक्षर *dbuf;
	लघु dbuflen;
	अचिन्हित अक्षर QWrite;	/* पढ़ो or ग_लिखो data */
	अचिन्हित अक्षर mailbox;
पूर्ण;

/* the transmit queue itself */

अटल काष्ठा xmitQel *xmQhd, *xmQtl;

अटल व्योम enQ(काष्ठा xmitQel *qel)
अणु
	अचिन्हित दीर्घ flags;
	qel->next = शून्य;
	
	spin_lock_irqsave(&txqueue_lock, flags);
	अगर (xmQtl) अणु
		xmQtl->next = qel;
	पूर्ण अन्यथा अणु
		xmQhd = qel;
	पूर्ण
	xmQtl = qel;
	spin_unlock_irqrestore(&txqueue_lock, flags);

	अगर (debug & DEBUG_LOWER)
		prपूर्णांकk("enqueued a 0x%02x command\n",qel->cbuf[0]);
पूर्ण

अटल काष्ठा xmitQel *deQ(व्योम)
अणु
	अचिन्हित दीर्घ flags;
	पूर्णांक i;
	काष्ठा xmitQel *qel=शून्य;
	
	spin_lock_irqsave(&txqueue_lock, flags);
	अगर (xmQhd) अणु
		qel = xmQhd;
		xmQhd = qel->next;
		अगर(!xmQhd) xmQtl = शून्य;
	पूर्ण
	spin_unlock_irqrestore(&txqueue_lock, flags);

	अगर ((debug & DEBUG_LOWER) && qel) अणु
		पूर्णांक n;
		prपूर्णांकk(KERN_DEBUG "ltpc: dequeued command ");
		n = qel->cbuflen;
		अगर (n>100) n=100;
		क्रम(i=0;i<n;i++) prपूर्णांकk("%02x ",qel->cbuf[i]);
		prपूर्णांकk("\n");
	पूर्ण

	वापस qel;
पूर्ण

/* and... the queue elements we'll be using */
अटल काष्ठा xmitQel qels[16];

/* and their corresponding mailboxes */
अटल अचिन्हित अक्षर mailbox[16];
अटल अचिन्हित अक्षर mboxinuse[16] = अणु0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0पूर्ण;

अटल पूर्णांक रुको_समयout(काष्ठा net_device *dev, पूर्णांक c)
अणु
	/* वापसs true अगर it stayed c */
	/* this uses base+6, but it's ok */
	पूर्णांक i;

	/* twenty second or so total */

	क्रम(i=0;i<200000;i++) अणु
		अगर ( c != inb_p(dev->base_addr+6) ) वापस 0;
		udelay(100);
	पूर्ण
	वापस 1; /* समयd out */
पूर्ण

/* get the first मुक्त mailbox */

अटल पूर्णांक geपंचांगbox(व्योम)
अणु
	अचिन्हित दीर्घ flags;
	पूर्णांक i;

	spin_lock_irqsave(&mbox_lock, flags);
	क्रम(i=1;i<16;i++) अगर(!mboxinuse[i]) अणु
		mboxinuse[i]=1;
		spin_unlock_irqrestore(&mbox_lock, flags);
		वापस i;
	पूर्ण
	spin_unlock_irqrestore(&mbox_lock, flags);
	वापस 0;
पूर्ण

/* पढ़ो a command from the card */
अटल व्योम handlefc(काष्ठा net_device *dev)
अणु
	/* called *only* from idle, non-reentrant */
	पूर्णांक dma = dev->dma;
	पूर्णांक base = dev->base_addr;
	अचिन्हित दीर्घ flags;


	flags=claim_dma_lock();
	disable_dma(dma);
	clear_dma_ff(dma);
	set_dma_mode(dma,DMA_MODE_READ);
	set_dma_addr(dma,virt_to_bus(ltdmacbuf));
	set_dma_count(dma,50);
	enable_dma(dma);
	release_dma_lock(flags);

	inb_p(base+3);
	inb_p(base+2);

	अगर ( रुको_समयout(dev,0xfc) ) prपूर्णांकk("timed out in handlefc\n");
पूर्ण

/* पढ़ो data from the card */
अटल व्योम handlefd(काष्ठा net_device *dev)
अणु
	पूर्णांक dma = dev->dma;
	पूर्णांक base = dev->base_addr;
	अचिन्हित दीर्घ flags;

	flags=claim_dma_lock();
	disable_dma(dma);
	clear_dma_ff(dma);
	set_dma_mode(dma,DMA_MODE_READ);
	set_dma_addr(dma,virt_to_bus(ltdmabuf));
	set_dma_count(dma,800);
	enable_dma(dma);
	release_dma_lock(flags);

	inb_p(base+3);
	inb_p(base+2);

	अगर ( रुको_समयout(dev,0xfd) ) prपूर्णांकk("timed out in handlefd\n");
	sendup_buffer(dev);
पूर्ण 

अटल व्योम handleग_लिखो(काष्ठा net_device *dev)
अणु
	/* called *only* from idle, non-reentrant */
	/* on entry, 0xfb and ltdmabuf holds data */
	पूर्णांक dma = dev->dma;
	पूर्णांक base = dev->base_addr;
	अचिन्हित दीर्घ flags;
	
	flags=claim_dma_lock();
	disable_dma(dma);
	clear_dma_ff(dma);
	set_dma_mode(dma,DMA_MODE_WRITE);
	set_dma_addr(dma,virt_to_bus(ltdmabuf));
	set_dma_count(dma,800);
	enable_dma(dma);
	release_dma_lock(flags);
	
	inb_p(base+3);
	inb_p(base+2);

	अगर ( रुको_समयout(dev,0xfb) ) अणु
		flags=claim_dma_lock();
		prपूर्णांकk("timed out in handlewrite, dma res %d\n",
			get_dma_residue(dev->dma) );
		release_dma_lock(flags);
	पूर्ण
पूर्ण

अटल व्योम handleपढ़ो(काष्ठा net_device *dev)
अणु
	/* on entry, 0xfb */
	/* on निकास, ltdmabuf holds data */
	पूर्णांक dma = dev->dma;
	पूर्णांक base = dev->base_addr;
	अचिन्हित दीर्घ flags;

	
	flags=claim_dma_lock();
	disable_dma(dma);
	clear_dma_ff(dma);
	set_dma_mode(dma,DMA_MODE_READ);
	set_dma_addr(dma,virt_to_bus(ltdmabuf));
	set_dma_count(dma,800);
	enable_dma(dma);
	release_dma_lock(flags);

	inb_p(base+3);
	inb_p(base+2);
	अगर ( रुको_समयout(dev,0xfb) ) prपूर्णांकk("timed out in handleread\n");
पूर्ण

अटल व्योम handlecommand(काष्ठा net_device *dev)
अणु
	/* on entry, 0xfa and ltdmacbuf holds command */
	पूर्णांक dma = dev->dma;
	पूर्णांक base = dev->base_addr;
	अचिन्हित दीर्घ flags;

	flags=claim_dma_lock();
	disable_dma(dma);
	clear_dma_ff(dma);
	set_dma_mode(dma,DMA_MODE_WRITE);
	set_dma_addr(dma,virt_to_bus(ltdmacbuf));
	set_dma_count(dma,50);
	enable_dma(dma);
	release_dma_lock(flags);
	inb_p(base+3);
	inb_p(base+2);
	अगर ( रुको_समयout(dev,0xfa) ) prपूर्णांकk("timed out in handlecommand\n");
पूर्ण 

/* पढ़ोy made command क्रम getting the result from the card */
अटल अचिन्हित अक्षर rescbuf[2] = अणुLT_GETRESULT,0पूर्ण;
अटल अचिन्हित अक्षर resdbuf[2];

अटल पूर्णांक QInIdle;

/* idle expects to be called with the IRQ line high -- either because of
 * an पूर्णांकerrupt, or because the line is tri-stated
 */

अटल व्योम idle(काष्ठा net_device *dev)
अणु
	अचिन्हित दीर्घ flags;
	पूर्णांक state;
	/* FIXME This is initialized to shut the warning up, but I need to
	 * think this through again.
	 */
	काष्ठा xmitQel *q = शून्य;
	पूर्णांक oops;
	पूर्णांक i;
	पूर्णांक base = dev->base_addr;

	spin_lock_irqsave(&txqueue_lock, flags);
	अगर(QInIdle) अणु
		spin_unlock_irqrestore(&txqueue_lock, flags);
		वापस;
	पूर्ण
	QInIdle = 1;
	spin_unlock_irqrestore(&txqueue_lock, flags);

	/* this tri-states the IRQ line */
	(व्योम) inb_p(base+6);

	oops = 100;

loop:
	अगर (0>oops--) अणु 
		prपूर्णांकk("idle: looped too many times\n");
		जाओ करोne;
	पूर्ण

	state = inb_p(base+6);
	अगर (state != inb_p(base+6)) जाओ loop;

	चयन(state) अणु
		हाल 0xfc:
			/* incoming command */
			अगर (debug & DEBUG_LOWER) prपूर्णांकk("idle: fc\n");
			handlefc(dev); 
			अवरोध;
		हाल 0xfd:
			/* incoming data */
			अगर(debug & DEBUG_LOWER) prपूर्णांकk("idle: fd\n");
			handlefd(dev); 
			अवरोध;
		हाल 0xf9:
			/* result पढ़ोy */
			अगर (debug & DEBUG_LOWER) prपूर्णांकk("idle: f9\n");
			अगर(!mboxinuse[0]) अणु
				mboxinuse[0] = 1;
				qels[0].cbuf = rescbuf;
				qels[0].cbuflen = 2;
				qels[0].dbuf = resdbuf;
				qels[0].dbuflen = 2;
				qels[0].QWrite = 0;
				qels[0].mailbox = 0;
				enQ(&qels[0]);
			पूर्ण
			inb_p(dev->base_addr+1);
			inb_p(dev->base_addr+0);
			अगर( रुको_समयout(dev,0xf9) )
				prपूर्णांकk("timed out idle f9\n");
			अवरोध;
		हाल 0xf8:
			/* ?? */
			अगर (xmQhd) अणु
				inb_p(dev->base_addr+1);
				inb_p(dev->base_addr+0);
				अगर(रुको_समयout(dev,0xf8) )
					prपूर्णांकk("timed out idle f8\n");
			पूर्ण अन्यथा अणु
				जाओ करोne;
			पूर्ण
			अवरोध;
		हाल 0xfa:
			/* रुकोing क्रम command */
			अगर(debug & DEBUG_LOWER) prपूर्णांकk("idle: fa\n");
			अगर (xmQhd) अणु
				q=deQ();
				स_नकल(ltdmacbuf,q->cbuf,q->cbuflen);
				ltdmacbuf[1] = q->mailbox;
				अगर (debug>1) अणु 
					पूर्णांक n;
					prपूर्णांकk("ltpc: sent command     ");
					n = q->cbuflen;
					अगर (n>100) n=100;
					क्रम(i=0;i<n;i++)
						prपूर्णांकk("%02x ",ltdmacbuf[i]);
					prपूर्णांकk("\n");
				पूर्ण
				handlecommand(dev);
					अगर(0xfa==inb_p(base+6)) अणु
						/* we समयd out, so वापस */
						जाओ करोne;
					पूर्ण 
			पूर्ण अन्यथा अणु
				/* we करोn't seem to have a command */
				अगर (!mboxinuse[0]) अणु
					mboxinuse[0] = 1;
					qels[0].cbuf = rescbuf;
					qels[0].cbuflen = 2;
					qels[0].dbuf = resdbuf;
					qels[0].dbuflen = 2;
					qels[0].QWrite = 0;
					qels[0].mailbox = 0;
					enQ(&qels[0]);
				पूर्ण अन्यथा अणु
					prपूर्णांकk("trouble: response command already queued\n");
					जाओ करोne;
				पूर्ण
			पूर्ण 
			अवरोध;
		हाल 0Xfb:
			/* data transfer पढ़ोy */
			अगर(debug & DEBUG_LOWER) prपूर्णांकk("idle: fb\n");
			अगर(q->QWrite) अणु
				स_नकल(ltdmabuf,q->dbuf,q->dbuflen);
				handleग_लिखो(dev);
			पूर्ण अन्यथा अणु
				handleपढ़ो(dev);
				/* non-zero mailbox numbers are क्रम
				   commmands, 0 is क्रम GETRESULT
				   requests */
				अगर(q->mailbox) अणु
					स_नकल(q->dbuf,ltdmabuf,q->dbuflen);
				पूर्ण अन्यथा अणु 
					/* this was a result */
					mailbox[ 0x0f & ltdmabuf[0] ] = ltdmabuf[1];
					mboxinuse[0]=0;
				पूर्ण
			पूर्ण
			अवरोध;
	पूर्ण
	जाओ loop;

करोne:
	QInIdle=0;

	/* now set the पूर्णांकerrupts back as appropriate */
	/* the first पढ़ो takes it out of tri-state (but still high) */
	/* the second resets it */
	/* note that after this poपूर्णांक, any पढ़ो of base+6 will
	   trigger an पूर्णांकerrupt */

	अगर (dev->irq) अणु
		inb_p(base+7);
		inb_p(base+7);
	पूर्ण
पूर्ण


अटल पूर्णांक करो_ग_लिखो(काष्ठा net_device *dev, व्योम *cbuf, पूर्णांक cbuflen,
	व्योम *dbuf, पूर्णांक dbuflen)
अणु

	पूर्णांक i = geपंचांगbox();
	पूर्णांक ret;

	अगर(i) अणु
		qels[i].cbuf = cbuf;
		qels[i].cbuflen = cbuflen;
		qels[i].dbuf = dbuf;
		qels[i].dbuflen = dbuflen;
		qels[i].QWrite = 1;
		qels[i].mailbox = i;  /* this should be initted rather */
		enQ(&qels[i]);
		idle(dev);
		ret = mailbox[i];
		mboxinuse[i]=0;
		वापस ret;
	पूर्ण
	prपूर्णांकk("ltpc: could not allocate mbox\n");
	वापस -1;
पूर्ण

अटल पूर्णांक करो_पढ़ो(काष्ठा net_device *dev, व्योम *cbuf, पूर्णांक cbuflen,
	व्योम *dbuf, पूर्णांक dbuflen)
अणु

	पूर्णांक i = geपंचांगbox();
	पूर्णांक ret;

	अगर(i) अणु
		qels[i].cbuf = cbuf;
		qels[i].cbuflen = cbuflen;
		qels[i].dbuf = dbuf;
		qels[i].dbuflen = dbuflen;
		qels[i].QWrite = 0;
		qels[i].mailbox = i;  /* this should be initted rather */
		enQ(&qels[i]);
		idle(dev);
		ret = mailbox[i];
		mboxinuse[i]=0;
		वापस ret;
	पूर्ण
	prपूर्णांकk("ltpc: could not allocate mbox\n");
	वापस -1;
पूर्ण

/* end of idle handlers -- what should be seen is करो_पढ़ो, करो_ग_लिखो */

अटल काष्ठा समयr_list ltpc_समयr;
अटल काष्ठा net_device *ltpc_समयr_dev;

अटल netdev_tx_t ltpc_xmit(काष्ठा sk_buff *skb, काष्ठा net_device *dev);

अटल पूर्णांक पढ़ो_30 ( काष्ठा net_device *dev)
अणु
	lt_command c;
	c.getflags.command = LT_GETFLAGS;
	वापस करो_पढ़ो(dev, &c, माप(c.getflags),&c,0);
पूर्ण

अटल पूर्णांक set_30 (काष्ठा net_device *dev,पूर्णांक x)
अणु
	lt_command c;
	c.setflags.command = LT_SETFLAGS;
	c.setflags.flags = x;
	वापस करो_ग_लिखो(dev, &c, माप(c.setflags),&c,0);
पूर्ण

/* LLAP to DDP translation */

अटल पूर्णांक sendup_buffer (काष्ठा net_device *dev)
अणु
	/* on entry, command is in ltdmacbuf, data in ltdmabuf */
	/* called from idle, non-reentrant */

	पूर्णांक dnode, snode, llaptype, len; 
	पूर्णांक sklen;
	काष्ठा sk_buff *skb;
	काष्ठा lt_rcvlap *ltc = (काष्ठा lt_rcvlap *) ltdmacbuf;

	अगर (ltc->command != LT_RCVLAP) अणु
		prपूर्णांकk("unknown command 0x%02x from ltpc card\n",ltc->command);
		वापस -1;
	पूर्ण
	dnode = ltc->dnode;
	snode = ltc->snode;
	llaptype = ltc->laptype;
	len = ltc->length; 

	sklen = len;
	अगर (llaptype == 1) 
		sklen += 8;  /* correct क्रम लघु ddp */
	अगर(sklen > 800) अणु
		prपूर्णांकk(KERN_INFO "%s: nonsense length in ltpc command 0x14: 0x%08x\n",
			dev->name,sklen);
		वापस -1;
	पूर्ण

	अगर ( (llaptype==0) || (llaptype>2) ) अणु
		prपूर्णांकk(KERN_INFO "%s: unknown LLAP type: %d\n",dev->name,llaptype);
		वापस -1;
	पूर्ण


	skb = dev_alloc_skb(3+sklen);
	अगर (skb == शून्य) 
	अणु
		prपूर्णांकk("%s: dropping packet due to memory squeeze.\n",
			dev->name);
		वापस -1;
	पूर्ण
	skb->dev = dev;

	अगर (sklen > len)
		skb_reserve(skb,8);
	skb_put(skb,len+3);
	skb->protocol = htons(ETH_P_LOCALTALK);
	/* add LLAP header */
	skb->data[0] = dnode;
	skb->data[1] = snode;
	skb->data[2] = llaptype;
	skb_reset_mac_header(skb);	/* save poपूर्णांकer to llap header */
	skb_pull(skb,3);

	/* copy ddp(s,e)hdr + contents */
	skb_copy_to_linear_data(skb, ltdmabuf, len);

	skb_reset_transport_header(skb);

	dev->stats.rx_packets++;
	dev->stats.rx_bytes += skb->len;

	/* toss it onwards */
	netअगर_rx(skb);
	वापस 0;
पूर्ण

/* the handler क्रम the board पूर्णांकerrupt */
 
अटल irqवापस_t
ltpc_पूर्णांकerrupt(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा net_device *dev = dev_id;

	अगर (dev==शून्य) अणु
		prपूर्णांकk("ltpc_interrupt: unknown device.\n");
		वापस IRQ_NONE;
	पूर्ण

	inb_p(dev->base_addr+6);  /* disable further पूर्णांकerrupts from board */

	idle(dev); /* handle whatever is coming in */
 
	/* idle re-enables पूर्णांकerrupts from board */ 

	वापस IRQ_HANDLED;
पूर्ण

/***
 *
 *    The ioctls that the driver responds to are:
 *
 *    SIOCSIFADDR -- करो probe using the passed node hपूर्णांक.
 *    SIOCGIFADDR -- वापस net, node.
 *
 *    some of this stuff should be करोne अन्यथाwhere.
 *
 ***/

अटल पूर्णांक ltpc_ioctl(काष्ठा net_device *dev, काष्ठा अगरreq *अगरr, पूर्णांक cmd)
अणु
	काष्ठा sockaddr_at *sa = (काष्ठा sockaddr_at *) &अगरr->अगरr_addr;
	/* we'll keep the localtalk node address in dev->pa_addr */
	काष्ठा ltpc_निजी *ltpc_priv = netdev_priv(dev);
	काष्ठा atalk_addr *aa = &ltpc_priv->my_addr;
	काष्ठा lt_init c;
	पूर्णांक ltflags;

	अगर(debug & DEBUG_VERBOSE) prपूर्णांकk("ltpc_ioctl called\n");

	चयन(cmd) अणु
		हाल SIOCSIFADDR:

			aa->s_net  = sa->sat_addr.s_net;
      
			/* this करोes the probe and वापसs the node addr */
			c.command = LT_INIT;
			c.hपूर्णांक = sa->sat_addr.s_node;

			aa->s_node = करो_पढ़ो(dev,&c,माप(c),&c,0);

			/* get all llap frames raw */
			ltflags = पढ़ो_30(dev);
			ltflags |= LT_FLAG_ALLLAP;
			set_30 (dev,ltflags);  

			dev->broadcast[0] = 0xFF;
			dev->dev_addr[0] = aa->s_node;

			dev->addr_len=1;
   
			वापस 0;

		हाल SIOCGIFADDR:

			sa->sat_addr.s_net = aa->s_net;
			sa->sat_addr.s_node = aa->s_node;

			वापस 0;

		शेष: 
			वापस -EINVAL;
	पूर्ण
पूर्ण

अटल व्योम set_multicast_list(काष्ठा net_device *dev)
अणु
	/* This needs to be present to keep netatalk happy. */
	/* Actually netatalk needs fixing! */
पूर्ण

अटल पूर्णांक ltpc_poll_counter;

अटल व्योम ltpc_poll(काष्ठा समयr_list *unused)
अणु
	del_समयr(&ltpc_समयr);

	अगर(debug & DEBUG_VERBOSE) अणु
		अगर (!ltpc_poll_counter) अणु
			ltpc_poll_counter = 50;
			prपूर्णांकk("ltpc poll is alive\n");
		पूर्ण
		ltpc_poll_counter--;
	पूर्ण

	/* poll 20 बार per second */
	idle(ltpc_समयr_dev);
	ltpc_समयr.expires = jअगरfies + HZ/20;
	add_समयr(&ltpc_समयr);
पूर्ण

/* DDP to LLAP translation */

अटल netdev_tx_t ltpc_xmit(काष्ठा sk_buff *skb, काष्ठा net_device *dev)
अणु
	/* in kernel 1.3.xx, on entry skb->data poपूर्णांकs to ddp header,
	 * and skb->len is the length of the ddp data + ddp header
	 */
	पूर्णांक i;
	काष्ठा lt_sendlap cbuf;
	अचिन्हित अक्षर *hdr;

	cbuf.command = LT_SENDLAP;
	cbuf.dnode = skb->data[0];
	cbuf.laptype = skb->data[2];
	skb_pull(skb,3);	/* skip past LLAP header */
	cbuf.length = skb->len;	/* this is host order */
	skb_reset_transport_header(skb);

	अगर(debug & DEBUG_UPPER) अणु
		prपूर्णांकk("command ");
		क्रम(i=0;i<6;i++)
			prपूर्णांकk("%02x ",((अचिन्हित अक्षर *)&cbuf)[i]);
		prपूर्णांकk("\n");
	पूर्ण

	hdr = skb_transport_header(skb);
	करो_ग_लिखो(dev, &cbuf, माप(cbuf), hdr, skb->len);

	अगर(debug & DEBUG_UPPER) अणु
		prपूर्णांकk("sent %d ddp bytes\n",skb->len);
		क्रम (i = 0; i < skb->len; i++)
			prपूर्णांकk("%02x ", hdr[i]);
		prपूर्णांकk("\n");
	पूर्ण

	dev->stats.tx_packets++;
	dev->stats.tx_bytes += skb->len;

	dev_kमुक्त_skb(skb);
	वापस NETDEV_TX_OK;
पूर्ण

/* initialization stuff */
  
अटल पूर्णांक __init ltpc_probe_dma(पूर्णांक base, पूर्णांक dma)
अणु
	पूर्णांक want = (dma == 3) ? 2 : (dma == 1) ? 1 : 3;
  	अचिन्हित दीर्घ समयout;
  	अचिन्हित दीर्घ f;
  
  	अगर (want & 1) अणु
		अगर (request_dma(1,"ltpc")) अणु
			want &= ~1;
		पूर्ण अन्यथा अणु
			f=claim_dma_lock();
			disable_dma(1);
			clear_dma_ff(1);
			set_dma_mode(1,DMA_MODE_WRITE);
			set_dma_addr(1,virt_to_bus(ltdmabuf));
			set_dma_count(1,माप(काष्ठा lt_mem));
			enable_dma(1);
			release_dma_lock(f);
		पूर्ण
	पूर्ण
	अगर (want & 2) अणु
		अगर (request_dma(3,"ltpc")) अणु
			want &= ~2;
		पूर्ण अन्यथा अणु
			f=claim_dma_lock();
			disable_dma(3);
			clear_dma_ff(3);
			set_dma_mode(3,DMA_MODE_WRITE);
			set_dma_addr(3,virt_to_bus(ltdmabuf));
			set_dma_count(3,माप(काष्ठा lt_mem));
			enable_dma(3);
			release_dma_lock(f);
		पूर्ण
	पूर्ण
	/* set up request */

	/* FIXME -- करो timings better! */

	ltdmabuf[0] = LT_READMEM;
	ltdmabuf[1] = 1;  /* mailbox */
	ltdmabuf[2] = 0; ltdmabuf[3] = 0;  /* address */
	ltdmabuf[4] = 0; ltdmabuf[5] = 1;  /* पढ़ो 0x0100 bytes */
	ltdmabuf[6] = 0; /* dunno अगर this is necessary */

	inb_p(io+1);
	inb_p(io+0);
	समयout = jअगरfies+100*HZ/100;
	जबतक(समय_beक्रमe(jअगरfies, समयout)) अणु
		अगर ( 0xfa == inb_p(io+6) ) अवरोध;
	पूर्ण

	inb_p(io+3);
	inb_p(io+2);
	जबतक(समय_beक्रमe(jअगरfies, समयout)) अणु
		अगर ( 0xfb == inb_p(io+6) ) अवरोध;
	पूर्ण

	/* release the other dma channel (अगर we खोलोed both of them) */

	अगर ((want & 2) && (get_dma_residue(3)==माप(काष्ठा lt_mem))) अणु
		want &= ~2;
		मुक्त_dma(3);
	पूर्ण

	अगर ((want & 1) && (get_dma_residue(1)==माप(काष्ठा lt_mem))) अणु
		want &= ~1;
		मुक्त_dma(1);
	पूर्ण

	अगर (!want)
		वापस 0;

	वापस (want & 2) ? 3 : 1;
पूर्ण

अटल स्थिर काष्ठा net_device_ops ltpc_netdev = अणु
	.nकरो_start_xmit		= ltpc_xmit,
	.nकरो_करो_ioctl		= ltpc_ioctl,
	.nकरो_set_rx_mode	= set_multicast_list,
पूर्ण;

काष्ठा net_device * __init ltpc_probe(व्योम)
अणु
	काष्ठा net_device *dev;
	पूर्णांक err = -ENOMEM;
	पूर्णांक x=0,y=0;
	पूर्णांक स्वतःirq;
	अचिन्हित दीर्घ f;
	अचिन्हित दीर्घ समयout;

	dev = alloc_ltalkdev(माप(काष्ठा ltpc_निजी));
	अगर (!dev)
		जाओ out;

	/* probe क्रम the I/O port address */
	
	अगर (io != 0x240 && request_region(0x220,8,"ltpc")) अणु
		x = inb_p(0x220+6);
		अगर ( (x!=0xff) && (x>=0xf0) ) अणु
			io = 0x220;
			जाओ got_port;
		पूर्ण
		release_region(0x220,8);
	पूर्ण
	अगर (io != 0x220 && request_region(0x240,8,"ltpc")) अणु
		y = inb_p(0x240+6);
		अगर ( (y!=0xff) && (y>=0xf0) )अणु 
			io = 0x240;
			जाओ got_port;
		पूर्ण
		release_region(0x240,8);
	पूर्ण 

	/* give up in despair */
	prपूर्णांकk(KERN_ERR "LocalTalk card not found; 220 = %02x, 240 = %02x.\n", x,y);
	err = -ENODEV;
	जाओ out1;

 got_port:
	/* probe क्रम the IRQ line */
	अगर (irq < 2) अणु
		अचिन्हित दीर्घ irq_mask;

		irq_mask = probe_irq_on();
		/* reset the पूर्णांकerrupt line */
		inb_p(io+7);
		inb_p(io+7);
		/* trigger an पूर्णांकerrupt (I hope) */
		inb_p(io+6);
		mdelay(2);
		स्वतःirq = probe_irq_off(irq_mask);

		अगर (स्वतःirq == 0) अणु
			prपूर्णांकk(KERN_ERR "ltpc: probe at %#x failed to detect IRQ line.\n", io);
		पूर्ण अन्यथा अणु
			irq = स्वतःirq;
		पूर्ण
	पूर्ण

	/* allocate a DMA buffer */
	ltdmabuf = (अचिन्हित अक्षर *) dma_mem_alloc(1000);
	अगर (!ltdmabuf) अणु
		prपूर्णांकk(KERN_ERR "ltpc: mem alloc failed\n");
		err = -ENOMEM;
		जाओ out2;
	पूर्ण

	ltdmacbuf = &ltdmabuf[800];

	अगर(debug & DEBUG_VERBOSE) अणु
		prपूर्णांकk("ltdmabuf pointer %08lx\n",(अचिन्हित दीर्घ) ltdmabuf);
	पूर्ण

	/* reset the card */

	inb_p(io+1);
	inb_p(io+3);

	msleep(20);

	inb_p(io+0);
	inb_p(io+2);
	inb_p(io+7); /* clear reset */
	inb_p(io+4); 
	inb_p(io+5);
	inb_p(io+5); /* enable dma */
	inb_p(io+6); /* tri-state पूर्णांकerrupt line */

	ssleep(1);
	
	/* now, figure out which dma channel we're using, unless it's
	   alपढ़ोy been specअगरied */
	/* well, 0 is a legal DMA channel, but the LTPC card करोesn't
	   use it... */
	dma = ltpc_probe_dma(io, dma);
	अगर (!dma) अणु  /* no dma channel */
		prपूर्णांकk(KERN_ERR "No DMA channel found on ltpc card.\n");
		err = -ENODEV;
		जाओ out3;
	पूर्ण

	/* prपूर्णांक out मित्रly message */
	अगर(irq)
		prपूर्णांकk(KERN_INFO "Apple/Farallon LocalTalk-PC card at %03x, IR%d, DMA%d.\n",io,irq,dma);
	अन्यथा
		prपूर्णांकk(KERN_INFO "Apple/Farallon LocalTalk-PC card at %03x, DMA%d.  Using polled mode.\n",io,dma);

	dev->netdev_ops = &ltpc_netdev;
	dev->base_addr = io;
	dev->irq = irq;
	dev->dma = dma;

	/* the card will want to send a result at this poपूर्णांक */
	/* (I think... leaving out this part makes the kernel crash,
           so I put it back in...) */

	f=claim_dma_lock();
	disable_dma(dma);
	clear_dma_ff(dma);
	set_dma_mode(dma,DMA_MODE_READ);
	set_dma_addr(dma,virt_to_bus(ltdmabuf));
	set_dma_count(dma,0x100);
	enable_dma(dma);
	release_dma_lock(f);

	(व्योम) inb_p(io+3);
	(व्योम) inb_p(io+2);
	समयout = jअगरfies+100*HZ/100;

	जबतक(समय_beक्रमe(jअगरfies, समयout)) अणु
		अगर( 0xf9 == inb_p(io+6))
			अवरोध;
		schedule();
	पूर्ण

	अगर(debug & DEBUG_VERBOSE) अणु
		prपूर्णांकk("setting up timer and irq\n");
	पूर्ण

	/* grab it and करोn't let go :-) */
	अगर (irq && request_irq( irq, ltpc_पूर्णांकerrupt, 0, "ltpc", dev) >= 0)
	अणु
		(व्योम) inb_p(io+7);  /* enable पूर्णांकerrupts from board */
		(व्योम) inb_p(io+7);  /* and reset irq line */
	पूर्ण अन्यथा अणु
		अगर( irq )
			prपूर्णांकk(KERN_ERR "ltpc: IRQ already in use, using polled mode.\n");
		dev->irq = 0;
		/* polled mode -- 20 बार per second */
		/* this is really, really slow... should it poll more often? */
		ltpc_समयr_dev = dev;
		समयr_setup(&ltpc_समयr, ltpc_poll, 0);

		ltpc_समयr.expires = jअगरfies + HZ/20;
		add_समयr(&ltpc_समयr);
	पूर्ण
	err = रेजिस्टर_netdev(dev);
	अगर (err)
		जाओ out4;

	वापस शून्य;
out4:
	del_समयr_sync(&ltpc_समयr);
	अगर (dev->irq)
		मुक्त_irq(dev->irq, dev);
out3:
	मुक्त_pages((अचिन्हित दीर्घ)ltdmabuf, get_order(1000));
out2:
	release_region(io, 8);
out1:
	मुक्त_netdev(dev);
out:
	वापस ERR_PTR(err);
पूर्ण

#अगर_अघोषित MODULE
/* handles "ltpc=io,irq,dma" kernel command lines */
अटल पूर्णांक __init ltpc_setup(अक्षर *str)
अणु
	पूर्णांक पूर्णांकs[5];

	str = get_options(str, ARRAY_SIZE(पूर्णांकs), पूर्णांकs);

	अगर (पूर्णांकs[0] == 0) अणु
		अगर (str && !म_भेदन(str, "auto", 4)) अणु
			/* करो nothing :-) */
		पूर्ण
		अन्यथा अणु
			/* usage message */
			prपूर्णांकk (KERN_ERR
				"ltpc: usage: ltpc=auto|iobase[,irq[,dma]]\n");
			वापस 0;
		पूर्ण
	पूर्ण अन्यथा अणु
		io = पूर्णांकs[1];
		अगर (पूर्णांकs[0] > 1) अणु
			irq = पूर्णांकs[2];
		पूर्ण
		अगर (पूर्णांकs[0] > 2) अणु
			dma = पूर्णांकs[3];
		पूर्ण
		/* ignore any other parameters */
	पूर्ण
	वापस 1;
पूर्ण

__setup("ltpc=", ltpc_setup);
#पूर्ण_अगर /* MODULE */

अटल काष्ठा net_device *dev_ltpc;

#अगर_घोषित MODULE

MODULE_LICENSE("GPL");
module_param(debug, पूर्णांक, 0);
module_param_hw(io, पूर्णांक, ioport, 0);
module_param_hw(irq, पूर्णांक, irq, 0);
module_param_hw(dma, पूर्णांक, dma, 0);


अटल पूर्णांक __init ltpc_module_init(व्योम)
अणु
        अगर(io == 0)
		prपूर्णांकk(KERN_NOTICE
		       "ltpc: Autoprobing is not recommended for modules\n");

	dev_ltpc = ltpc_probe();
	वापस PTR_ERR_OR_ZERO(dev_ltpc);
पूर्ण
module_init(ltpc_module_init);
#पूर्ण_अगर

अटल व्योम __निकास ltpc_cleanup(व्योम)
अणु

	अगर(debug & DEBUG_VERBOSE) prपूर्णांकk("unregister_netdev\n");
	unरेजिस्टर_netdev(dev_ltpc);

	del_समयr_sync(&ltpc_समयr);

	अगर(debug & DEBUG_VERBOSE) prपूर्णांकk("freeing irq\n");

	अगर (dev_ltpc->irq)
		मुक्त_irq(dev_ltpc->irq, dev_ltpc);

	अगर(debug & DEBUG_VERBOSE) prपूर्णांकk("freeing dma\n");

	अगर (dev_ltpc->dma)
		मुक्त_dma(dev_ltpc->dma);

	अगर(debug & DEBUG_VERBOSE) prपूर्णांकk("freeing ioaddr\n");

	अगर (dev_ltpc->base_addr)
		release_region(dev_ltpc->base_addr,8);

	मुक्त_netdev(dev_ltpc);

	अगर(debug & DEBUG_VERBOSE) prपूर्णांकk("free_pages\n");

	मुक्त_pages( (अचिन्हित दीर्घ) ltdmabuf, get_order(1000));

	अगर(debug & DEBUG_VERBOSE) prपूर्णांकk("returning from cleanup_module\n");
पूर्ण

module_निकास(ltpc_cleanup);
