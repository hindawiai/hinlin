<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/* $Id: cosa.c,v 1.31 2000/03/08 17:47:16 kas Exp $ */

/*
 *  Copyright (C) 1995-1997  Jan "Yenya" Kasprzak <kas@fi.muni.cz>
 *  Generic HDLC port Copyright (C) 2008 Krzysztof Halasa <khc@pm.waw.pl>
 */

/*
 * The driver क्रम the SRP and COSA synchronous serial cards.
 *
 * HARDWARE INFO
 *
 * Both cards are developed at the Institute of Computer Science,
 * Masaryk University (https://www.ics.muni.cz/). The hardware is
 * developed by Jiri Novotny <novotny@ics.muni.cz>. More inक्रमmation
 * and the photo of both cards is available at
 * http://www.pavoucek.cz/cosa.hपंचांगl. The card करोcumentation, firmwares
 * and other goods can be करोwnloaded from ftp://ftp.ics.muni.cz/pub/cosa/.
 * For Linux-specअगरic utilities, see below in the "Software info" section.
 * If you want to order the card, contact Jiri Novotny.
 *
 * The SRP (serial port?, the Czech word "srp" means "sickle") card
 * is a 2-port पूर्णांकelligent (with its own 8-bit CPU) synchronous serial card
 * with V.24 पूर्णांकerfaces up to 80kb/s each.
 *
 * The COSA (communication serial adapter?, the Czech word "kosa" means
 * "scythe") is a next-generation sync/async board with two पूर्णांकerfaces
 * - currently any of V.24, X.21, V.35 and V.36 can be selected.
 * It has a 16-bit SAB80166 CPU and can करो up to 10 Mb/s per channel.
 * The 8-channels version is in development.
 *
 * Both types have करोwnloadable firmware and communicate via ISA DMA.
 * COSA can be also a bus-mastering device.
 *
 * SOFTWARE INFO
 *
 * The homepage of the Linux driver is at https://www.fi.muni.cz/~kas/cosa/.
 * The CVS tree of Linux driver can be viewed there, as well as the
 * firmware binaries and user-space utilities क्रम करोwnloading the firmware
 * पूर्णांकo the card and setting up the card.
 *
 * The Linux driver (unlike the present *BSD drivers :-) can work even
 * क्रम the COSA and SRP in one computer and allows each channel to work
 * in one of the two modes (अक्षरacter or network device).
 *
 * AUTHOR
 *
 * The Linux driver was written by Jan "Yenya" Kasprzak <kas@fi.muni.cz>.
 *
 * You can mail me bugfixes and even success reports. I am especially
 * पूर्णांकerested in the SMP and/or muliti-channel success/failure reports
 * (I wonder अगर I did the locking properly :-).
 *
 * THE AUTHOR USED THE FOLLOWING SOURCES WHEN PROGRAMMING THE DRIVER
 *
 * The COSA/SRP NetBSD driver by Zdenek Salvet and Ivos Cernohlavek
 * The skeleton.c by Donald Becker
 * The SDL Riscom/N2 driver by Mike Natale
 * The Comtrol Hostess SV11 driver by Alan Cox
 * The Sync PPP/Cisco HDLC layer (syncppp.c) ported to Linux by Alan Cox
 */

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#समावेश <linux/module.h>
#समावेश <linux/kernel.h>
#समावेश <linux/sched/संकेत.स>
#समावेश <linux/slab.h>
#समावेश <linux/poll.h>
#समावेश <linux/fs.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/delay.h>
#समावेश <linux/hdlc.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/ioport.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/mutex.h>
#समावेश <linux/device.h>
#समावेश <यंत्र/पन.स>
#समावेश <यंत्र/dma.h>
#समावेश <यंत्र/byteorder.h>

#अघोषित COSA_SLOW_IO	/* क्रम testing purposes only */

#समावेश "cosa.h"

/* Maximum length of the identअगरication string. */
#घोषणा COSA_MAX_ID_STRING	128

/* Maximum length of the channel name */
#घोषणा COSA_MAX_NAME		(माप("cosaXXXcXXX")+1)

/* Per-channel data काष्ठाure */

काष्ठा channel_data अणु
	पूर्णांक usage;	/* Usage count; >0 क्रम chrdev, -1 क्रम netdev */
	पूर्णांक num;	/* Number of the channel */
	काष्ठा cosa_data *cosa;	/* Poपूर्णांकer to the per-card काष्ठाure */
	पूर्णांक txsize;	/* Size of transmitted data */
	अक्षर *txbuf;	/* Transmit buffer */
	अक्षर name[COSA_MAX_NAME];	/* channel name */

	/* The HW layer पूर्णांकerface */
	/* routine called from the RX पूर्णांकerrupt */
	अक्षर *(*setup_rx)(काष्ठा channel_data *channel, पूर्णांक size);
	/* routine called when the RX is करोne (from the EOT पूर्णांकerrupt) */
	पूर्णांक (*rx_करोne)(काष्ठा channel_data *channel);
	/* routine called when the TX is करोne (from the EOT पूर्णांकerrupt) */
	पूर्णांक (*tx_करोne)(काष्ठा channel_data *channel, पूर्णांक size);

	/* Character device parts */
	काष्ठा mutex rlock;
	काष्ठा semaphore wsem;
	अक्षर *rxdata;
	पूर्णांक rxsize;
	रुको_queue_head_t txरुकोq, rxरुकोq;
	पूर्णांक tx_status, rx_status;

	/* generic HDLC device parts */
	काष्ठा net_device *netdev;
	काष्ठा sk_buff *rx_skb, *tx_skb;
पूर्ण;

/* cosa->firmware_status bits */
#घोषणा COSA_FW_RESET		(1<<0)	/* Is the ROM monitor active? */
#घोषणा COSA_FW_DOWNLOAD	(1<<1)	/* Is the microcode करोwnloaded? */
#घोषणा COSA_FW_START		(1<<2)	/* Is the microcode running? */

काष्ठा cosa_data अणु
	पूर्णांक num;			/* Card number */
	अक्षर name[COSA_MAX_NAME];	/* Card name - e.g "cosa0" */
	अचिन्हित पूर्णांक datareg, statusreg;	/* I/O ports */
	अचिन्हित लघु irq, dma;	/* IRQ and DMA number */
	अचिन्हित लघु startaddr;	/* Firmware start address */
	अचिन्हित लघु busmaster;	/* Use busmastering? */
	पूर्णांक nchannels;			/* # of channels on this card */
	पूर्णांक driver_status;		/* For communicating with firmware */
	पूर्णांक firmware_status;		/* Downloaded, reseted, etc. */
	अचिन्हित दीर्घ rxbiपंचांगap, txbiपंचांगap;/* Biपंचांगap of channels who are willing to send/receive data */
	अचिन्हित दीर्घ rxtx;		/* RX or TX in progress? */
	पूर्णांक enabled;
	पूर्णांक usage;				/* usage count */
	पूर्णांक txchan, txsize, rxsize;
	काष्ठा channel_data *rxchan;
	अक्षर *bouncebuf;
	अक्षर *txbuf, *rxbuf;
	काष्ठा channel_data *chan;
	spinlock_t lock;	/* For exclusive operations on this काष्ठाure */
	अक्षर id_string[COSA_MAX_ID_STRING];	/* ROM monitor ID string */
	अक्षर *type;				/* card type */
पूर्ण;

/*
 * Define this अगर you want all the possible ports to be स्वतःprobed.
 * It is here but it probably is not a good idea to use this.
 */
/* #घोषणा COSA_ISA_AUTOPROBE	1 */

/*
 * Character device major number. 117 was allocated क्रम us.
 * The value of 0 means to allocate a first मुक्त one.
 */
अटल DEFINE_MUTEX(cosa_अक्षरdev_mutex);
अटल पूर्णांक cosa_major = 117;

/*
 * Encoding of the minor numbers:
 * The lowest CARD_MINOR_BITS bits means the channel on the single card,
 * the highest bits means the card number.
 */
#घोषणा CARD_MINOR_BITS	4	/* How many bits in minor number are reserved
				 * क्रम the single card */
/*
 * The following depends on CARD_MINOR_BITS. Unक्रमtunately, the "MODULE_STRING"
 * macro करोesn't like anything other than the raw number as an argument :-(
 */
#घोषणा MAX_CARDS	16
/* #घोषणा MAX_CARDS	(1 << (8-CARD_MINOR_BITS)) */

#घोषणा DRIVER_RX_READY		0x0001
#घोषणा DRIVER_TX_READY		0x0002
#घोषणा DRIVER_TXMAP_SHIFT	2
#घोषणा DRIVER_TXMAP_MASK	0x0c	/* FIXME: 0xfc क्रम 8-channel version */

/*
 * क्रम cosa->rxtx - indicates whether either transmit or receive is
 * in progress. These values are mean number of the bit.
 */
#घोषणा TXBIT 0
#घोषणा RXBIT 1
#घोषणा IRQBIT 2

#घोषणा COSA_MTU 2000	/* FIXME: I करोn't know this exactly */

#अघोषित DEBUG_DATA //1	/* Dump the data पढ़ो or written to the channel */
#अघोषित DEBUG_IRQS //1	/* Prपूर्णांक the message when the IRQ is received */
#अघोषित DEBUG_IO   //1	/* Dump the I/O traffic */

#घोषणा TX_TIMEOUT	(5*HZ)

/* Maybe the following should be allocated dynamically */
अटल काष्ठा cosa_data cosa_cards[MAX_CARDS];
अटल पूर्णांक nr_cards;

#अगर_घोषित COSA_ISA_AUTOPROBE
अटल पूर्णांक io[MAX_CARDS+1]  = अणु 0x220, 0x228, 0x210, 0x218, 0, पूर्ण;
/* NOTE: DMA is not स्वतःprobed!!! */
अटल पूर्णांक dma[MAX_CARDS+1] = अणु 1, 7, 1, 7, 1, 7, 1, 7, 0, पूर्ण;
#अन्यथा
अटल पूर्णांक io[MAX_CARDS+1];
अटल पूर्णांक dma[MAX_CARDS+1];
#पूर्ण_अगर
/* IRQ can be safely स्वतःprobed */
अटल पूर्णांक irq[MAX_CARDS+1] = अणु -1, -1, -1, -1, -1, -1, 0, पूर्ण;

/* क्रम class stuff*/
अटल काष्ठा class *cosa_class;

#अगर_घोषित MODULE
module_param_hw_array(io, पूर्णांक, ioport, शून्य, 0);
MODULE_PARM_DESC(io, "The I/O bases of the COSA or SRP cards");
module_param_hw_array(irq, पूर्णांक, irq, शून्य, 0);
MODULE_PARM_DESC(irq, "The IRQ lines of the COSA or SRP cards");
module_param_hw_array(dma, पूर्णांक, dma, शून्य, 0);
MODULE_PARM_DESC(dma, "The DMA channels of the COSA or SRP cards");

MODULE_AUTHOR("Jan \"Yenya\" Kasprzak, <kas@fi.muni.cz>");
MODULE_DESCRIPTION("Modular driver for the COSA or SRP synchronous card");
MODULE_LICENSE("GPL");
#पूर्ण_अगर

/* I use this मुख्यly क्रम testing purposes */
#अगर_घोषित COSA_SLOW_IO
#घोषणा cosa_outb outb_p
#घोषणा cosa_outw outw_p
#घोषणा cosa_inb  inb_p
#घोषणा cosa_inw  inw_p
#अन्यथा
#घोषणा cosa_outb outb
#घोषणा cosa_outw outw
#घोषणा cosa_inb  inb
#घोषणा cosa_inw  inw
#पूर्ण_अगर

#घोषणा is_8bit(cosa)		(!(cosa->datareg & 0x08))

#घोषणा cosa_माला_लोtatus(cosa)	(cosa_inb(cosa->statusreg))
#घोषणा cosa_माला_दोtatus(cosa, stat)	(cosa_outb(stat, cosa->statusreg))
#घोषणा cosa_getdata16(cosa)	(cosa_inw(cosa->datareg))
#घोषणा cosa_getdata8(cosa)	(cosa_inb(cosa->datareg))
#घोषणा cosa_putdata16(cosa, dt)	(cosa_outw(dt, cosa->datareg))
#घोषणा cosa_putdata8(cosa, dt)	(cosa_outb(dt, cosa->datareg))

/* Initialization stuff */
अटल पूर्णांक cosa_probe(पूर्णांक ioaddr, पूर्णांक irq, पूर्णांक dma);

/* HW पूर्णांकerface */
अटल व्योम cosa_enable_rx(काष्ठा channel_data *chan);
अटल व्योम cosa_disable_rx(काष्ठा channel_data *chan);
अटल पूर्णांक cosa_start_tx(काष्ठा channel_data *channel, अक्षर *buf, पूर्णांक size);
अटल व्योम cosa_kick(काष्ठा cosa_data *cosa);
अटल पूर्णांक cosa_dma_able(काष्ठा channel_data *chan, अक्षर *buf, पूर्णांक data);

/* Network device stuff */
अटल पूर्णांक cosa_net_attach(काष्ठा net_device *dev, अचिन्हित लघु encoding,
			   अचिन्हित लघु parity);
अटल पूर्णांक cosa_net_खोलो(काष्ठा net_device *d);
अटल पूर्णांक cosa_net_बंद(काष्ठा net_device *d);
अटल व्योम cosa_net_समयout(काष्ठा net_device *d, अचिन्हित पूर्णांक txqueue);
अटल netdev_tx_t cosa_net_tx(काष्ठा sk_buff *skb, काष्ठा net_device *d);
अटल अक्षर *cosa_net_setup_rx(काष्ठा channel_data *channel, पूर्णांक size);
अटल पूर्णांक cosa_net_rx_करोne(काष्ठा channel_data *channel);
अटल पूर्णांक cosa_net_tx_करोne(काष्ठा channel_data *channel, पूर्णांक size);
अटल पूर्णांक cosa_net_ioctl(काष्ठा net_device *dev, काष्ठा अगरreq *अगरr, पूर्णांक cmd);

/* Character device */
अटल अक्षर *chrdev_setup_rx(काष्ठा channel_data *channel, पूर्णांक size);
अटल पूर्णांक chrdev_rx_करोne(काष्ठा channel_data *channel);
अटल पूर्णांक chrdev_tx_करोne(काष्ठा channel_data *channel, पूर्णांक size);
अटल sमाप_प्रकार cosa_पढ़ो(काष्ठा file *file,
	अक्षर __user *buf, माप_प्रकार count, loff_t *ppos);
अटल sमाप_प्रकार cosa_ग_लिखो(काष्ठा file *file,
	स्थिर अक्षर __user *buf, माप_प्रकार count, loff_t *ppos);
अटल अचिन्हित पूर्णांक cosa_poll(काष्ठा file *file, poll_table *poll);
अटल पूर्णांक cosa_खोलो(काष्ठा inode *inode, काष्ठा file *file);
अटल पूर्णांक cosa_release(काष्ठा inode *inode, काष्ठा file *file);
अटल दीर्घ cosa_अक्षरdev_ioctl(काष्ठा file *file, अचिन्हित पूर्णांक cmd,
				अचिन्हित दीर्घ arg);
#अगर_घोषित COSA_FASYNC_WORKING
अटल पूर्णांक cosa_fasync(काष्ठा inode *inode, काष्ठा file *file, पूर्णांक on);
#पूर्ण_अगर

अटल स्थिर काष्ठा file_operations cosa_fops = अणु
	.owner		= THIS_MODULE,
	.llseek		= no_llseek,
	.पढ़ो		= cosa_पढ़ो,
	.ग_लिखो		= cosa_ग_लिखो,
	.poll		= cosa_poll,
	.unlocked_ioctl	= cosa_अक्षरdev_ioctl,
	.खोलो		= cosa_खोलो,
	.release	= cosa_release,
#अगर_घोषित COSA_FASYNC_WORKING
	.fasync		= cosa_fasync,
#पूर्ण_अगर
पूर्ण;

/* Ioctls */
अटल पूर्णांक cosa_start(काष्ठा cosa_data *cosa, पूर्णांक address);
अटल पूर्णांक cosa_reset(काष्ठा cosa_data *cosa);
अटल पूर्णांक cosa_करोwnload(काष्ठा cosa_data *cosa, व्योम __user *a);
अटल पूर्णांक cosa_पढ़ोmem(काष्ठा cosa_data *cosa, व्योम __user *a);

/* COSA/SRP ROM monitor */
अटल पूर्णांक करोwnload(काष्ठा cosa_data *cosa, स्थिर अक्षर __user *data, पूर्णांक addr, पूर्णांक len);
अटल पूर्णांक starपंचांगicrocode(काष्ठा cosa_data *cosa, पूर्णांक address);
अटल पूर्णांक पढ़ोmem(काष्ठा cosa_data *cosa, अक्षर __user *data, पूर्णांक addr, पूर्णांक len);
अटल पूर्णांक cosa_reset_and_पढ़ो_id(काष्ठा cosa_data *cosa, अक्षर *id);

/* Auxiliary functions */
अटल पूर्णांक get_रुको_data(काष्ठा cosa_data *cosa);
अटल पूर्णांक put_रुको_data(काष्ठा cosa_data *cosa, पूर्णांक data);
अटल पूर्णांक puthexnumber(काष्ठा cosa_data *cosa, पूर्णांक number);
अटल व्योम put_driver_status(काष्ठा cosa_data *cosa);
अटल व्योम put_driver_status_nolock(काष्ठा cosa_data *cosa);

/* Interrupt handling */
अटल irqवापस_t cosa_पूर्णांकerrupt(पूर्णांक irq, व्योम *cosa);

/* I/O ops debugging */
#अगर_घोषित DEBUG_IO
अटल व्योम debug_data_in(काष्ठा cosa_data *cosa, पूर्णांक data);
अटल व्योम debug_data_out(काष्ठा cosa_data *cosa, पूर्णांक data);
अटल व्योम debug_data_cmd(काष्ठा cosa_data *cosa, पूर्णांक data);
अटल व्योम debug_status_in(काष्ठा cosa_data *cosa, पूर्णांक status);
अटल व्योम debug_status_out(काष्ठा cosa_data *cosa, पूर्णांक status);
#पूर्ण_अगर

अटल अंतरभूत काष्ठा channel_data* dev_to_chan(काष्ठा net_device *dev)
अणु
	वापस (काष्ठा channel_data *)dev_to_hdlc(dev)->priv;
पूर्ण

/* ---------- Initialization stuff ---------- */

अटल पूर्णांक __init cosa_init(व्योम)
अणु
	पूर्णांक i, err = 0;

	अगर (cosa_major > 0) अणु
		अगर (रेजिस्टर_chrdev(cosa_major, "cosa", &cosa_fops)) अणु
			pr_warn("unable to get major %d\n", cosa_major);
			err = -EIO;
			जाओ out;
		पूर्ण
	पूर्ण अन्यथा अणु
		अगर (!(cosa_major=रेजिस्टर_chrdev(0, "cosa", &cosa_fops))) अणु
			pr_warn("unable to register chardev\n");
			err = -EIO;
			जाओ out;
		पूर्ण
	पूर्ण
	क्रम (i=0; i<MAX_CARDS; i++)
		cosa_cards[i].num = -1;
	क्रम (i=0; io[i] != 0 && i < MAX_CARDS; i++)
		cosa_probe(io[i], irq[i], dma[i]);
	अगर (!nr_cards) अणु
		pr_warn("no devices found\n");
		unरेजिस्टर_chrdev(cosa_major, "cosa");
		err = -ENODEV;
		जाओ out;
	पूर्ण
	cosa_class = class_create(THIS_MODULE, "cosa");
	अगर (IS_ERR(cosa_class)) अणु
		err = PTR_ERR(cosa_class);
		जाओ out_chrdev;
	पूर्ण
	क्रम (i = 0; i < nr_cards; i++)
		device_create(cosa_class, शून्य, MKDEV(cosa_major, i), शून्य,
			      "cosa%d", i);
	err = 0;
	जाओ out;

out_chrdev:
	unरेजिस्टर_chrdev(cosa_major, "cosa");
out:
	वापस err;
पूर्ण
module_init(cosa_init);

अटल व्योम __निकास cosa_निकास(व्योम)
अणु
	काष्ठा cosa_data *cosa;
	पूर्णांक i;

	क्रम (i = 0; i < nr_cards; i++)
		device_destroy(cosa_class, MKDEV(cosa_major, i));
	class_destroy(cosa_class);

	क्रम (cosa = cosa_cards; nr_cards--; cosa++) अणु
		/* Clean up the per-channel data */
		क्रम (i = 0; i < cosa->nchannels; i++) अणु
			/* Chardev driver has no alloc'd per-channel data */
			unरेजिस्टर_hdlc_device(cosa->chan[i].netdev);
			मुक्त_netdev(cosa->chan[i].netdev);
		पूर्ण
		/* Clean up the per-card data */
		kमुक्त(cosa->chan);
		kमुक्त(cosa->bouncebuf);
		मुक्त_irq(cosa->irq, cosa);
		मुक्त_dma(cosa->dma);
		release_region(cosa->datareg, is_8bit(cosa) ? 2 : 4);
	पूर्ण
	unरेजिस्टर_chrdev(cosa_major, "cosa");
पूर्ण
module_निकास(cosa_निकास);

अटल स्थिर काष्ठा net_device_ops cosa_ops = अणु
	.nकरो_खोलो       = cosa_net_खोलो,
	.nकरो_stop       = cosa_net_बंद,
	.nकरो_start_xmit = hdlc_start_xmit,
	.nकरो_करो_ioctl   = cosa_net_ioctl,
	.nकरो_tx_समयout = cosa_net_समयout,
पूर्ण;

अटल पूर्णांक cosa_probe(पूर्णांक base, पूर्णांक irq, पूर्णांक dma)
अणु
	काष्ठा cosa_data *cosa = cosa_cards+nr_cards;
	पूर्णांक i, err = 0;

	स_रखो(cosa, 0, माप(काष्ठा cosa_data));

	/* Checking validity of parameters: */
	/* IRQ should be 2-7 or 10-15; negative IRQ means स्वतःprobe */
	अगर ((irq >= 0  && irq < 2) || irq > 15 || (irq < 10 && irq > 7)) अणु
		pr_info("invalid IRQ %d\n", irq);
		वापस -1;
	पूर्ण
	/* I/O address should be between 0x100 and 0x3ff and should be
	 * multiple of 8. */
	अगर (base < 0x100 || base > 0x3ff || base & 0x7) अणु
		pr_info("invalid I/O address 0x%x\n", base);
		वापस -1;
	पूर्ण
	/* DMA should be 0,1 or 3-7 */
	अगर (dma < 0 || dma == 4 || dma > 7) अणु
		pr_info("invalid DMA %d\n", dma);
		वापस -1;
	पूर्ण
	/* and finally, on 16-bit COSA DMA should be 4-7 and 
	 * I/O base should not be multiple of 0x10 */
	अगर (((base & 0x8) && dma < 4) || (!(base & 0x8) && dma > 3)) अणु
		pr_info("8/16 bit base and DMA mismatch (base=0x%x, dma=%d)\n",
			base, dma);
		वापस -1;
	पूर्ण

	cosa->dma = dma;
	cosa->datareg = base;
	cosa->statusreg = is_8bit(cosa)?base+1:base+2;
	spin_lock_init(&cosa->lock);

	अगर (!request_region(base, is_8bit(cosa)?2:4,"cosa"))
		वापस -1;
	
	अगर (cosa_reset_and_पढ़ो_id(cosa, cosa->id_string) < 0) अणु
		prपूर्णांकk(KERN_DEBUG "probe at 0x%x failed.\n", base);
		err = -1;
		जाओ err_out;
	पूर्ण

	/* Test the validity of identअगरication string */
	अगर (!म_भेदन(cosa->id_string, "SRP", 3))
		cosa->type = "srp";
	अन्यथा अगर (!म_भेदन(cosa->id_string, "COSA", 4))
		cosa->type = is_8bit(cosa)? "cosa8": "cosa16";
	अन्यथा अणु
/* Prपूर्णांक a warning only अगर we are not स्वतःprobing */
#अगर_अघोषित COSA_ISA_AUTOPROBE
		pr_info("valid signature not found at 0x%x\n", base);
#पूर्ण_अगर
		err = -1;
		जाओ err_out;
	पूर्ण
	/* Update the name of the region now we know the type of card */ 
	release_region(base, is_8bit(cosa)?2:4);
	अगर (!request_region(base, is_8bit(cosa)?2:4, cosa->type)) अणु
		prपूर्णांकk(KERN_DEBUG "changing name at 0x%x failed.\n", base);
		वापस -1;
	पूर्ण

	/* Now करो IRQ स्वतःprobe */
	अगर (irq < 0) अणु
		अचिन्हित दीर्घ irqs;
/*		pr_info("IRQ autoprobe\n"); */
		irqs = probe_irq_on();
		/* 
		 * Enable पूर्णांकerrupt on tx buffer empty (it sure is) 
		 * really sure ?
		 * FIXME: When this code is not used as module, we should
		 * probably call udelay() instead of the पूर्णांकerruptible sleep.
		 */
		set_current_state(TASK_INTERRUPTIBLE);
		cosa_माला_दोtatus(cosa, SR_TX_INT_ENA);
		schedule_समयout(msecs_to_jअगरfies(300));
		irq = probe_irq_off(irqs);
		/* Disable all IRQs from the card */
		cosa_माला_दोtatus(cosa, 0);
		/* Empty the received data रेजिस्टर */
		cosa_getdata8(cosa);

		अगर (irq < 0) अणु
			pr_info("multiple interrupts obtained (%d, board at 0x%x)\n",
				irq, cosa->datareg);
			err = -1;
			जाओ err_out;
		पूर्ण
		अगर (irq == 0) अणु
			pr_info("no interrupt obtained (board at 0x%x)\n",
				cosa->datareg);
		/*	वापस -1; */
		पूर्ण
	पूर्ण

	cosa->irq = irq;
	cosa->num = nr_cards;
	cosa->usage = 0;
	cosa->nchannels = 2;	/* FIXME: how to determine this? */

	अगर (request_irq(cosa->irq, cosa_पूर्णांकerrupt, 0, cosa->type, cosa)) अणु
		err = -1;
		जाओ err_out;
	पूर्ण
	अगर (request_dma(cosa->dma, cosa->type)) अणु
		err = -1;
		जाओ err_out1;
	पूर्ण
	
	cosa->bouncebuf = kदो_स्मृति(COSA_MTU, GFP_KERNEL|GFP_DMA);
	अगर (!cosa->bouncebuf) अणु
		err = -ENOMEM;
		जाओ err_out2;
	पूर्ण
	प्र_लिखो(cosa->name, "cosa%d", cosa->num);

	/* Initialize the per-channel data */
	cosa->chan = kसुस्मृति(cosa->nchannels, माप(काष्ठा channel_data), GFP_KERNEL);
	अगर (!cosa->chan) अणु
		err = -ENOMEM;
		जाओ err_out3;
	पूर्ण

	क्रम (i = 0; i < cosa->nchannels; i++) अणु
		काष्ठा channel_data *chan = &cosa->chan[i];

		chan->cosa = cosa;
		chan->num = i;
		प्र_लिखो(chan->name, "cosa%dc%d", chan->cosa->num, i);

		/* Initialize the अक्षरdev data काष्ठाures */
		mutex_init(&chan->rlock);
		sema_init(&chan->wsem, 1);

		/* Register the network पूर्णांकerface */
		अगर (!(chan->netdev = alloc_hdlcdev(chan))) अणु
			pr_warn("%s: alloc_hdlcdev failed\n", chan->name);
			err = -ENOMEM;
			जाओ err_hdlcdev;
		पूर्ण
		dev_to_hdlc(chan->netdev)->attach = cosa_net_attach;
		dev_to_hdlc(chan->netdev)->xmit = cosa_net_tx;
		chan->netdev->netdev_ops = &cosa_ops;
		chan->netdev->watchकरोg_समयo = TX_TIMEOUT;
		chan->netdev->base_addr = chan->cosa->datareg;
		chan->netdev->irq = chan->cosa->irq;
		chan->netdev->dma = chan->cosa->dma;
		err = रेजिस्टर_hdlc_device(chan->netdev);
		अगर (err) अणु
			netdev_warn(chan->netdev,
				    "register_hdlc_device() failed\n");
			मुक्त_netdev(chan->netdev);
			जाओ err_hdlcdev;
		पूर्ण
	पूर्ण

	pr_info("cosa%d: %s (%s at 0x%x irq %d dma %d), %d channels\n",
		cosa->num, cosa->id_string, cosa->type,
		cosa->datareg, cosa->irq, cosa->dma, cosa->nchannels);

	वापस nr_cards++;

err_hdlcdev:
	जबतक (i-- > 0) अणु
		unरेजिस्टर_hdlc_device(cosa->chan[i].netdev);
		मुक्त_netdev(cosa->chan[i].netdev);
	पूर्ण
	kमुक्त(cosa->chan);
err_out3:
	kमुक्त(cosa->bouncebuf);
err_out2:
	मुक्त_dma(cosa->dma);
err_out1:
	मुक्त_irq(cosa->irq, cosa);
err_out:
	release_region(cosa->datareg,is_8bit(cosa)?2:4);
	pr_notice("cosa%d: allocating resources failed\n", cosa->num);
	वापस err;
पूर्ण


/*---------- network device ---------- */

अटल पूर्णांक cosa_net_attach(काष्ठा net_device *dev, अचिन्हित लघु encoding,
			   अचिन्हित लघु parity)
अणु
	अगर (encoding == ENCODING_NRZ && parity == PARITY_CRC16_PR1_CCITT)
		वापस 0;
	वापस -EINVAL;
पूर्ण

अटल पूर्णांक cosa_net_खोलो(काष्ठा net_device *dev)
अणु
	काष्ठा channel_data *chan = dev_to_chan(dev);
	पूर्णांक err;
	अचिन्हित दीर्घ flags;

	अगर (!(chan->cosa->firmware_status & COSA_FW_START)) अणु
		pr_notice("%s: start the firmware first (status %d)\n",
			  chan->cosa->name, chan->cosa->firmware_status);
		वापस -EPERM;
	पूर्ण
	spin_lock_irqsave(&chan->cosa->lock, flags);
	अगर (chan->usage != 0) अणु
		pr_warn("%s: cosa_net_open called with usage count %d\n",
			chan->name, chan->usage);
		spin_unlock_irqrestore(&chan->cosa->lock, flags);
		वापस -EBUSY;
	पूर्ण
	chan->setup_rx = cosa_net_setup_rx;
	chan->tx_करोne = cosa_net_tx_करोne;
	chan->rx_करोne = cosa_net_rx_करोne;
	chan->usage = -1;
	chan->cosa->usage++;
	spin_unlock_irqrestore(&chan->cosa->lock, flags);

	err = hdlc_खोलो(dev);
	अगर (err) अणु
		spin_lock_irqsave(&chan->cosa->lock, flags);
		chan->usage = 0;
		chan->cosa->usage--;
		spin_unlock_irqrestore(&chan->cosa->lock, flags);
		वापस err;
	पूर्ण

	netअगर_start_queue(dev);
	cosa_enable_rx(chan);
	वापस 0;
पूर्ण

अटल netdev_tx_t cosa_net_tx(काष्ठा sk_buff *skb,
				     काष्ठा net_device *dev)
अणु
	काष्ठा channel_data *chan = dev_to_chan(dev);

	netअगर_stop_queue(dev);

	chan->tx_skb = skb;
	cosa_start_tx(chan, skb->data, skb->len);
	वापस NETDEV_TX_OK;
पूर्ण

अटल व्योम cosa_net_समयout(काष्ठा net_device *dev, अचिन्हित पूर्णांक txqueue)
अणु
	काष्ठा channel_data *chan = dev_to_chan(dev);

	अगर (test_bit(RXBIT, &chan->cosa->rxtx)) अणु
		chan->netdev->stats.rx_errors++;
		chan->netdev->stats.rx_missed_errors++;
	पूर्ण अन्यथा अणु
		chan->netdev->stats.tx_errors++;
		chan->netdev->stats.tx_पातed_errors++;
	पूर्ण
	cosa_kick(chan->cosa);
	अगर (chan->tx_skb) अणु
		dev_kमुक्त_skb(chan->tx_skb);
		chan->tx_skb = शून्य;
	पूर्ण
	netअगर_wake_queue(dev);
पूर्ण

अटल पूर्णांक cosa_net_बंद(काष्ठा net_device *dev)
अणु
	काष्ठा channel_data *chan = dev_to_chan(dev);
	अचिन्हित दीर्घ flags;

	netअगर_stop_queue(dev);
	hdlc_बंद(dev);
	cosa_disable_rx(chan);
	spin_lock_irqsave(&chan->cosa->lock, flags);
	अगर (chan->rx_skb) अणु
		kमुक्त_skb(chan->rx_skb);
		chan->rx_skb = शून्य;
	पूर्ण
	अगर (chan->tx_skb) अणु
		kमुक्त_skb(chan->tx_skb);
		chan->tx_skb = शून्य;
	पूर्ण
	chan->usage = 0;
	chan->cosa->usage--;
	spin_unlock_irqrestore(&chan->cosa->lock, flags);
	वापस 0;
पूर्ण

अटल अक्षर *cosa_net_setup_rx(काष्ठा channel_data *chan, पूर्णांक size)
अणु
	/*
	 * We can safely fall back to non-dma-able memory, because we have
	 * the cosa->bouncebuf pre-allocated.
	 */
	kमुक्त_skb(chan->rx_skb);
	chan->rx_skb = dev_alloc_skb(size);
	अगर (chan->rx_skb == शून्य) अणु
		pr_notice("%s: Memory squeeze, dropping packet\n", chan->name);
		chan->netdev->stats.rx_dropped++;
		वापस शून्य;
	पूर्ण
	netअगर_trans_update(chan->netdev);
	वापस skb_put(chan->rx_skb, size);
पूर्ण

अटल पूर्णांक cosa_net_rx_करोne(काष्ठा channel_data *chan)
अणु
	अगर (!chan->rx_skb) अणु
		pr_warn("%s: rx_done with empty skb!\n", chan->name);
		chan->netdev->stats.rx_errors++;
		chan->netdev->stats.rx_frame_errors++;
		वापस 0;
	पूर्ण
	chan->rx_skb->protocol = hdlc_type_trans(chan->rx_skb, chan->netdev);
	chan->rx_skb->dev = chan->netdev;
	skb_reset_mac_header(chan->rx_skb);
	chan->netdev->stats.rx_packets++;
	chan->netdev->stats.rx_bytes += chan->cosa->rxsize;
	netअगर_rx(chan->rx_skb);
	chan->rx_skb = शून्य;
	वापस 0;
पूर्ण

/* ARGSUSED */
अटल पूर्णांक cosa_net_tx_करोne(काष्ठा channel_data *chan, पूर्णांक size)
अणु
	अगर (!chan->tx_skb) अणु
		pr_warn("%s: tx_done with empty skb!\n", chan->name);
		chan->netdev->stats.tx_errors++;
		chan->netdev->stats.tx_पातed_errors++;
		वापस 1;
	पूर्ण
	dev_consume_skb_irq(chan->tx_skb);
	chan->tx_skb = शून्य;
	chan->netdev->stats.tx_packets++;
	chan->netdev->stats.tx_bytes += size;
	netअगर_wake_queue(chan->netdev);
	वापस 1;
पूर्ण

/*---------- Character device ---------- */

अटल sमाप_प्रकार cosa_पढ़ो(काष्ठा file *file,
	अक्षर __user *buf, माप_प्रकार count, loff_t *ppos)
अणु
	DECLARE_WAITQUEUE(रुको, current);
	अचिन्हित दीर्घ flags;
	काष्ठा channel_data *chan = file->निजी_data;
	काष्ठा cosa_data *cosa = chan->cosa;
	अक्षर *kbuf;

	अगर (!(cosa->firmware_status & COSA_FW_START)) अणु
		pr_notice("%s: start the firmware first (status %d)\n",
			  cosa->name, cosa->firmware_status);
		वापस -EPERM;
	पूर्ण
	अगर (mutex_lock_पूर्णांकerruptible(&chan->rlock))
		वापस -ERESTARTSYS;
	
	chan->rxdata = kदो_स्मृति(COSA_MTU, GFP_DMA|GFP_KERNEL);
	अगर (chan->rxdata == शून्य) अणु
		mutex_unlock(&chan->rlock);
		वापस -ENOMEM;
	पूर्ण

	chan->rx_status = 0;
	cosa_enable_rx(chan);
	spin_lock_irqsave(&cosa->lock, flags);
	add_रुको_queue(&chan->rxरुकोq, &रुको);
	जबतक (!chan->rx_status) अणु
		set_current_state(TASK_INTERRUPTIBLE);
		spin_unlock_irqrestore(&cosa->lock, flags);
		schedule();
		spin_lock_irqsave(&cosa->lock, flags);
		अगर (संकेत_pending(current) && chan->rx_status == 0) अणु
			chan->rx_status = 1;
			हटाओ_रुको_queue(&chan->rxरुकोq, &रुको);
			__set_current_state(TASK_RUNNING);
			spin_unlock_irqrestore(&cosa->lock, flags);
			mutex_unlock(&chan->rlock);
			वापस -ERESTARTSYS;
		पूर्ण
	पूर्ण
	हटाओ_रुको_queue(&chan->rxरुकोq, &रुको);
	__set_current_state(TASK_RUNNING);
	kbuf = chan->rxdata;
	count = chan->rxsize;
	spin_unlock_irqrestore(&cosa->lock, flags);
	mutex_unlock(&chan->rlock);

	अगर (copy_to_user(buf, kbuf, count)) अणु
		kमुक्त(kbuf);
		वापस -EFAULT;
	पूर्ण
	kमुक्त(kbuf);
	वापस count;
पूर्ण

अटल अक्षर *chrdev_setup_rx(काष्ठा channel_data *chan, पूर्णांक size)
अणु
	/* Expect size <= COSA_MTU */
	chan->rxsize = size;
	वापस chan->rxdata;
पूर्ण

अटल पूर्णांक chrdev_rx_करोne(काष्ठा channel_data *chan)
अणु
	अगर (chan->rx_status) अणु /* Reader has died */
		kमुक्त(chan->rxdata);
		up(&chan->wsem);
	पूर्ण
	chan->rx_status = 1;
	wake_up_पूर्णांकerruptible(&chan->rxरुकोq);
	वापस 1;
पूर्ण


अटल sमाप_प्रकार cosa_ग_लिखो(काष्ठा file *file,
	स्थिर अक्षर __user *buf, माप_प्रकार count, loff_t *ppos)
अणु
	DECLARE_WAITQUEUE(रुको, current);
	काष्ठा channel_data *chan = file->निजी_data;
	काष्ठा cosa_data *cosa = chan->cosa;
	अचिन्हित दीर्घ flags;
	अक्षर *kbuf;

	अगर (!(cosa->firmware_status & COSA_FW_START)) अणु
		pr_notice("%s: start the firmware first (status %d)\n",
			  cosa->name, cosa->firmware_status);
		वापस -EPERM;
	पूर्ण
	अगर (करोwn_पूर्णांकerruptible(&chan->wsem))
		वापस -ERESTARTSYS;

	अगर (count > COSA_MTU)
		count = COSA_MTU;
	
	/* Allocate the buffer */
	kbuf = kदो_स्मृति(count, GFP_KERNEL|GFP_DMA);
	अगर (kbuf == शून्य) अणु
		up(&chan->wsem);
		वापस -ENOMEM;
	पूर्ण
	अगर (copy_from_user(kbuf, buf, count)) अणु
		up(&chan->wsem);
		kमुक्त(kbuf);
		वापस -EFAULT;
	पूर्ण
	chan->tx_status=0;
	cosa_start_tx(chan, kbuf, count);

	spin_lock_irqsave(&cosa->lock, flags);
	add_रुको_queue(&chan->txरुकोq, &रुको);
	जबतक (!chan->tx_status) अणु
		set_current_state(TASK_INTERRUPTIBLE);
		spin_unlock_irqrestore(&cosa->lock, flags);
		schedule();
		spin_lock_irqsave(&cosa->lock, flags);
		अगर (संकेत_pending(current) && chan->tx_status == 0) अणु
			chan->tx_status = 1;
			हटाओ_रुको_queue(&chan->txरुकोq, &रुको);
			__set_current_state(TASK_RUNNING);
			chan->tx_status = 1;
			spin_unlock_irqrestore(&cosa->lock, flags);
			up(&chan->wsem);
			kमुक्त(kbuf);
			वापस -ERESTARTSYS;
		पूर्ण
	पूर्ण
	हटाओ_रुको_queue(&chan->txरुकोq, &रुको);
	__set_current_state(TASK_RUNNING);
	up(&chan->wsem);
	spin_unlock_irqrestore(&cosa->lock, flags);
	kमुक्त(kbuf);
	वापस count;
पूर्ण

अटल पूर्णांक chrdev_tx_करोne(काष्ठा channel_data *chan, पूर्णांक size)
अणु
	अगर (chan->tx_status) अणु /* Writer was पूर्णांकerrupted */
		kमुक्त(chan->txbuf);
		up(&chan->wsem);
	पूर्ण
	chan->tx_status = 1;
	wake_up_पूर्णांकerruptible(&chan->txरुकोq);
	वापस 1;
पूर्ण

अटल __poll_t cosa_poll(काष्ठा file *file, poll_table *poll)
अणु
	pr_info("cosa_poll is here\n");
	वापस 0;
पूर्ण

अटल पूर्णांक cosa_खोलो(काष्ठा inode *inode, काष्ठा file *file)
अणु
	काष्ठा cosa_data *cosa;
	काष्ठा channel_data *chan;
	अचिन्हित दीर्घ flags;
	पूर्णांक n;
	पूर्णांक ret = 0;

	mutex_lock(&cosa_अक्षरdev_mutex);
	अगर ((n=iminor(file_inode(file))>>CARD_MINOR_BITS)
		>= nr_cards) अणु
		ret = -ENODEV;
		जाओ out;
	पूर्ण
	cosa = cosa_cards+n;

	अगर ((n=iminor(file_inode(file))
		& ((1<<CARD_MINOR_BITS)-1)) >= cosa->nchannels) अणु
		ret = -ENODEV;
		जाओ out;
	पूर्ण
	chan = cosa->chan + n;
	
	file->निजी_data = chan;

	spin_lock_irqsave(&cosa->lock, flags);

	अगर (chan->usage < 0) अणु /* in netdev mode */
		spin_unlock_irqrestore(&cosa->lock, flags);
		ret = -EBUSY;
		जाओ out;
	पूर्ण
	cosa->usage++;
	chan->usage++;

	chan->tx_करोne = chrdev_tx_करोne;
	chan->setup_rx = chrdev_setup_rx;
	chan->rx_करोne = chrdev_rx_करोne;
	spin_unlock_irqrestore(&cosa->lock, flags);
out:
	mutex_unlock(&cosa_अक्षरdev_mutex);
	वापस ret;
पूर्ण

अटल पूर्णांक cosa_release(काष्ठा inode *inode, काष्ठा file *file)
अणु
	काष्ठा channel_data *channel = file->निजी_data;
	काष्ठा cosa_data *cosa;
	अचिन्हित दीर्घ flags;

	cosa = channel->cosa;
	spin_lock_irqsave(&cosa->lock, flags);
	cosa->usage--;
	channel->usage--;
	spin_unlock_irqrestore(&cosa->lock, flags);
	वापस 0;
पूर्ण

#अगर_घोषित COSA_FASYNC_WORKING
अटल काष्ठा fasync_काष्ठा *fasync[256] = अणु शून्य, पूर्ण;

/* To be करोne ... */
अटल पूर्णांक cosa_fasync(काष्ठा inode *inode, काष्ठा file *file, पूर्णांक on)
अणु
        पूर्णांक port = iminor(inode);

	वापस fasync_helper(inode, file, on, &fasync[port]);
पूर्ण
#पूर्ण_अगर


/* ---------- Ioctls ---------- */

/*
 * Ioctl subroutines can safely be made अंतरभूत, because they are called
 * only from cosa_ioctl().
 */
अटल अंतरभूत पूर्णांक cosa_reset(काष्ठा cosa_data *cosa)
अणु
	अक्षर idstring[COSA_MAX_ID_STRING];
	अगर (cosa->usage > 1)
		pr_info("cosa%d: WARNING: reset requested with cosa->usage > 1 (%d). Odd things may happen.\n",
			cosa->num, cosa->usage);
	cosa->firmware_status &= ~(COSA_FW_RESET|COSA_FW_START);
	अगर (cosa_reset_and_पढ़ो_id(cosa, idstring) < 0) अणु
		pr_notice("cosa%d: reset failed\n", cosa->num);
		वापस -EIO;
	पूर्ण
	pr_info("cosa%d: resetting device: %s\n", cosa->num, idstring);
	cosa->firmware_status |= COSA_FW_RESET;
	वापस 0;
पूर्ण

/* High-level function to करोwnload data पूर्णांकo COSA memory. Calls करोwnload() */
अटल अंतरभूत पूर्णांक cosa_करोwnload(काष्ठा cosa_data *cosa, व्योम __user *arg)
अणु
	काष्ठा cosa_करोwnload d;
	पूर्णांक i;

	अगर (cosa->usage > 1)
		pr_info("%s: WARNING: download of microcode requested with cosa->usage > 1 (%d). Odd things may happen.\n",
			cosa->name, cosa->usage);
	अगर (!(cosa->firmware_status & COSA_FW_RESET)) अणु
		pr_notice("%s: reset the card first (status %d)\n",
			  cosa->name, cosa->firmware_status);
		वापस -EPERM;
	पूर्ण
	
	अगर (copy_from_user(&d, arg, माप(d)))
		वापस -EFAULT;

	अगर (d.addr < 0 || d.addr > COSA_MAX_FIRMWARE_SIZE)
		वापस -EINVAL;
	अगर (d.len < 0 || d.len > COSA_MAX_FIRMWARE_SIZE)
		वापस -EINVAL;


	/* If something fails, क्रमce the user to reset the card */
	cosa->firmware_status &= ~(COSA_FW_RESET|COSA_FW_DOWNLOAD);

	i = करोwnload(cosa, d.code, d.len, d.addr);
	अगर (i < 0) अणु
		pr_notice("cosa%d: microcode download failed: %d\n",
			  cosa->num, i);
		वापस -EIO;
	पूर्ण
	pr_info("cosa%d: downloading microcode - 0x%04x bytes at 0x%04x\n",
		cosa->num, d.len, d.addr);
	cosa->firmware_status |= COSA_FW_RESET|COSA_FW_DOWNLOAD;
	वापस 0;
पूर्ण

/* High-level function to पढ़ो COSA memory. Calls पढ़ोmem() */
अटल अंतरभूत पूर्णांक cosa_पढ़ोmem(काष्ठा cosa_data *cosa, व्योम __user *arg)
अणु
	काष्ठा cosa_करोwnload d;
	पूर्णांक i;

	अगर (cosa->usage > 1)
		pr_info("cosa%d: WARNING: readmem requested with cosa->usage > 1 (%d). Odd things may happen.\n",
			cosa->num, cosa->usage);
	अगर (!(cosa->firmware_status & COSA_FW_RESET)) अणु
		pr_notice("%s: reset the card first (status %d)\n",
			  cosa->name, cosa->firmware_status);
		वापस -EPERM;
	पूर्ण

	अगर (copy_from_user(&d, arg, माप(d)))
		वापस -EFAULT;

	/* If something fails, क्रमce the user to reset the card */
	cosa->firmware_status &= ~COSA_FW_RESET;

	i = पढ़ोmem(cosa, d.code, d.len, d.addr);
	अगर (i < 0) अणु
		pr_notice("cosa%d: reading memory failed: %d\n", cosa->num, i);
		वापस -EIO;
	पूर्ण
	pr_info("cosa%d: reading card memory - 0x%04x bytes at 0x%04x\n",
		cosa->num, d.len, d.addr);
	cosa->firmware_status |= COSA_FW_RESET;
	वापस 0;
पूर्ण

/* High-level function to start microcode. Calls starपंचांगicrocode(). */
अटल अंतरभूत पूर्णांक cosa_start(काष्ठा cosa_data *cosa, पूर्णांक address)
अणु
	पूर्णांक i;

	अगर (cosa->usage > 1)
		pr_info("cosa%d: WARNING: start microcode requested with cosa->usage > 1 (%d). Odd things may happen.\n",
			cosa->num, cosa->usage);

	अगर ((cosa->firmware_status & (COSA_FW_RESET|COSA_FW_DOWNLOAD))
		!= (COSA_FW_RESET|COSA_FW_DOWNLOAD)) अणु
		pr_notice("%s: download the microcode and/or reset the card first (status %d)\n",
			  cosa->name, cosa->firmware_status);
		वापस -EPERM;
	पूर्ण
	cosa->firmware_status &= ~COSA_FW_RESET;
	अगर ((i=starपंचांगicrocode(cosa, address)) < 0) अणु
		pr_notice("cosa%d: start microcode at 0x%04x failed: %d\n",
			  cosa->num, address, i);
		वापस -EIO;
	पूर्ण
	pr_info("cosa%d: starting microcode at 0x%04x\n", cosa->num, address);
	cosa->startaddr = address;
	cosa->firmware_status |= COSA_FW_START;
	वापस 0;
पूर्ण
		
/* Buffer of size at least COSA_MAX_ID_STRING is expected */
अटल अंतरभूत पूर्णांक cosa_getidstr(काष्ठा cosa_data *cosa, अक्षर __user *string)
अणु
	पूर्णांक l = म_माप(cosa->id_string)+1;
	अगर (copy_to_user(string, cosa->id_string, l))
		वापस -EFAULT;
	वापस l;
पूर्ण

/* Buffer of size at least COSA_MAX_ID_STRING is expected */
अटल अंतरभूत पूर्णांक cosa_gettype(काष्ठा cosa_data *cosa, अक्षर __user *string)
अणु
	पूर्णांक l = म_माप(cosa->type)+1;
	अगर (copy_to_user(string, cosa->type, l))
		वापस -EFAULT;
	वापस l;
पूर्ण

अटल पूर्णांक cosa_ioctl_common(काष्ठा cosa_data *cosa,
	काष्ठा channel_data *channel, अचिन्हित पूर्णांक cmd, अचिन्हित दीर्घ arg)
अणु
	व्योम __user *argp = (व्योम __user *)arg;
	चयन (cmd) अणु
	हाल COSAIORSET:	/* Reset the device */
		अगर (!capable(CAP_NET_ADMIN))
			वापस -EACCES;
		वापस cosa_reset(cosa);
	हाल COSAIOSTRT:	/* Start the firmware */
		अगर (!capable(CAP_SYS_RAWIO))
			वापस -EACCES;
		वापस cosa_start(cosa, arg);
	हाल COSAIODOWNLD:	/* Download the firmware */
		अगर (!capable(CAP_SYS_RAWIO))
			वापस -EACCES;
		
		वापस cosa_करोwnload(cosa, argp);
	हाल COSAIORMEM:
		अगर (!capable(CAP_SYS_RAWIO))
			वापस -EACCES;
		वापस cosa_पढ़ोmem(cosa, argp);
	हाल COSAIORTYPE:
		वापस cosa_gettype(cosa, argp);
	हाल COSAIORIDSTR:
		वापस cosa_getidstr(cosa, argp);
	हाल COSAIONRCARDS:
		वापस nr_cards;
	हाल COSAIONRCHANS:
		वापस cosa->nchannels;
	हाल COSAIOBMSET:
		अगर (!capable(CAP_SYS_RAWIO))
			वापस -EACCES;
		अगर (is_8bit(cosa))
			वापस -EINVAL;
		अगर (arg != COSA_BM_OFF && arg != COSA_BM_ON)
			वापस -EINVAL;
		cosa->busmaster = arg;
		वापस 0;
	हाल COSAIOBMGET:
		वापस cosa->busmaster;
	पूर्ण
	वापस -ENOIOCTLCMD;
पूर्ण

अटल पूर्णांक cosa_net_ioctl(काष्ठा net_device *dev, काष्ठा अगरreq *अगरr, पूर्णांक cmd)
अणु
	पूर्णांक rv;
	काष्ठा channel_data *chan = dev_to_chan(dev);
	rv = cosa_ioctl_common(chan->cosa, chan, cmd,
			       (अचिन्हित दीर्घ)अगरr->अगरr_data);
	अगर (rv != -ENOIOCTLCMD)
		वापस rv;
	वापस hdlc_ioctl(dev, अगरr, cmd);
पूर्ण

अटल दीर्घ cosa_अक्षरdev_ioctl(काष्ठा file *file, अचिन्हित पूर्णांक cmd,
							अचिन्हित दीर्घ arg)
अणु
	काष्ठा channel_data *channel = file->निजी_data;
	काष्ठा cosa_data *cosa;
	दीर्घ ret;

	mutex_lock(&cosa_अक्षरdev_mutex);
	cosa = channel->cosa;
	ret = cosa_ioctl_common(cosa, channel, cmd, arg);
	mutex_unlock(&cosa_अक्षरdev_mutex);
	वापस ret;
पूर्ण


/*---------- HW layer पूर्णांकerface ---------- */

/*
 * The higher layer can bind itself to the HW layer by setting the callbacks
 * in the channel_data काष्ठाure and by using these routines.
 */
अटल व्योम cosa_enable_rx(काष्ठा channel_data *chan)
अणु
	काष्ठा cosa_data *cosa = chan->cosa;

	अगर (!test_and_set_bit(chan->num, &cosa->rxbiपंचांगap))
		put_driver_status(cosa);
पूर्ण

अटल व्योम cosa_disable_rx(काष्ठा channel_data *chan)
अणु
	काष्ठा cosa_data *cosa = chan->cosa;

	अगर (test_and_clear_bit(chan->num, &cosa->rxbiपंचांगap))
		put_driver_status(cosa);
पूर्ण

/*
 * FIXME: This routine probably should check क्रम cosa_start_tx() called when
 * the previous transmit is still unfinished. In this हाल the non-zero
 * वापस value should indicate to the caller that the queuing(sp?) up
 * the transmit has failed.
 */
अटल पूर्णांक cosa_start_tx(काष्ठा channel_data *chan, अक्षर *buf, पूर्णांक len)
अणु
	काष्ठा cosa_data *cosa = chan->cosa;
	अचिन्हित दीर्घ flags;
#अगर_घोषित DEBUG_DATA
	पूर्णांक i;

	pr_info("cosa%dc%d: starting tx(0x%x)",
		chan->cosa->num, chan->num, len);
	क्रम (i=0; i<len; i++)
		pr_cont(" %02x", buf[i]&0xff);
	pr_cont("\n");
#पूर्ण_अगर
	spin_lock_irqsave(&cosa->lock, flags);
	chan->txbuf = buf;
	chan->txsize = len;
	अगर (len > COSA_MTU)
		chan->txsize = COSA_MTU;
	spin_unlock_irqrestore(&cosa->lock, flags);

	/* Tell the firmware we are पढ़ोy */
	set_bit(chan->num, &cosa->txbiपंचांगap);
	put_driver_status(cosa);

	वापस 0;
पूर्ण

अटल व्योम put_driver_status(काष्ठा cosa_data *cosa)
अणु
	अचिन्हित दीर्घ flags;
	पूर्णांक status;

	spin_lock_irqsave(&cosa->lock, flags);

	status = (cosa->rxbiपंचांगap ? DRIVER_RX_READY : 0)
		| (cosa->txbiपंचांगap ? DRIVER_TX_READY : 0)
		| (cosa->txbiपंचांगap? ~(cosa->txbiपंचांगap<<DRIVER_TXMAP_SHIFT)
			&DRIVER_TXMAP_MASK : 0);
	अगर (!cosa->rxtx) अणु
		अगर (cosa->rxbiपंचांगap|cosa->txbiपंचांगap) अणु
			अगर (!cosa->enabled) अणु
				cosa_माला_दोtatus(cosa, SR_RX_INT_ENA);
#अगर_घोषित DEBUG_IO
				debug_status_out(cosa, SR_RX_INT_ENA);
#पूर्ण_अगर
				cosa->enabled = 1;
			पूर्ण
		पूर्ण अन्यथा अगर (cosa->enabled) अणु
			cosa->enabled = 0;
			cosa_माला_दोtatus(cosa, 0);
#अगर_घोषित DEBUG_IO
			debug_status_out(cosa, 0);
#पूर्ण_अगर
		पूर्ण
		cosa_putdata8(cosa, status);
#अगर_घोषित DEBUG_IO
		debug_data_cmd(cosa, status);
#पूर्ण_अगर
	पूर्ण
	spin_unlock_irqrestore(&cosa->lock, flags);
पूर्ण

अटल व्योम put_driver_status_nolock(काष्ठा cosa_data *cosa)
अणु
	पूर्णांक status;

	status = (cosa->rxbiपंचांगap ? DRIVER_RX_READY : 0)
		| (cosa->txbiपंचांगap ? DRIVER_TX_READY : 0)
		| (cosa->txbiपंचांगap? ~(cosa->txbiपंचांगap<<DRIVER_TXMAP_SHIFT)
			&DRIVER_TXMAP_MASK : 0);

	अगर (cosa->rxbiपंचांगap|cosa->txbiपंचांगap) अणु
		cosa_माला_दोtatus(cosa, SR_RX_INT_ENA);
#अगर_घोषित DEBUG_IO
		debug_status_out(cosa, SR_RX_INT_ENA);
#पूर्ण_अगर
		cosa->enabled = 1;
	पूर्ण अन्यथा अणु
		cosa_माला_दोtatus(cosa, 0);
#अगर_घोषित DEBUG_IO
		debug_status_out(cosa, 0);
#पूर्ण_अगर
		cosa->enabled = 0;
	पूर्ण
	cosa_putdata8(cosa, status);
#अगर_घोषित DEBUG_IO
	debug_data_cmd(cosa, status);
#पूर्ण_अगर
पूर्ण

/*
 * The "kickme" function: When the DMA बार out, this is called to
 * clean up the driver status.
 * FIXME: Preliminary support, the पूर्णांकerface is probably wrong.
 */
अटल व्योम cosa_kick(काष्ठा cosa_data *cosa)
अणु
	अचिन्हित दीर्घ flags, flags1;
	अक्षर *s = "(probably) IRQ";

	अगर (test_bit(RXBIT, &cosa->rxtx))
		s = "RX DMA";
	अगर (test_bit(TXBIT, &cosa->rxtx))
		s = "TX DMA";

	pr_info("%s: %s timeout - restarting\n", cosa->name, s);
	spin_lock_irqsave(&cosa->lock, flags);
	cosa->rxtx = 0;

	flags1 = claim_dma_lock();
	disable_dma(cosa->dma);
	clear_dma_ff(cosa->dma);
	release_dma_lock(flags1);

	/* FIXME: Anything अन्यथा? */
	udelay(100);
	cosa_माला_दोtatus(cosa, 0);
	udelay(100);
	(व्योम) cosa_getdata8(cosa);
	udelay(100);
	cosa_putdata8(cosa, 0);
	udelay(100);
	put_driver_status_nolock(cosa);
	spin_unlock_irqrestore(&cosa->lock, flags);
पूर्ण

/*
 * Check अगर the whole buffer is DMA-able. It means it is below the 16M of
 * physical memory and करोesn't span the 64k boundary. For now it seems
 * SKB's never do this, but we'll check this anyway.
 */
अटल पूर्णांक cosa_dma_able(काष्ठा channel_data *chan, अक्षर *buf, पूर्णांक len)
अणु
	अटल पूर्णांक count;
	अचिन्हित दीर्घ b = (अचिन्हित दीर्घ)buf;
	अगर (b+len >= MAX_DMA_ADDRESS)
		वापस 0;
	अगर ((b^ (b+len)) & 0x10000) अणु
		अगर (count++ < 5)
			pr_info("%s: packet spanning a 64k boundary\n",
				chan->name);
		वापस 0;
	पूर्ण
	वापस 1;
पूर्ण


/* ---------- The SRP/COSA ROM monitor functions ---------- */

/*
 * Downloading SRP microcode: say "w" to SRP monitor, it answers by "w=",
 * drivers need to say 4-digit hex number meaning start address of the microcode
 * separated by a single space. Monitor replies by saying " =". Now driver
 * has to ग_लिखो 4-digit hex number meaning the last byte address ended
 * by a single space. Monitor has to reply with a space. Now the करोwnload
 * begins. After the करोwnload monitor replies with "\r\n." (CR LF करोt).
 */
अटल पूर्णांक करोwnload(काष्ठा cosa_data *cosa, स्थिर अक्षर __user *microcode, पूर्णांक length, पूर्णांक address)
अणु
	पूर्णांक i;

	अगर (put_रुको_data(cosa, 'w') == -1) वापस -1;
	अगर ((i=get_रुको_data(cosa)) != 'w') अणु prपूर्णांकk("dnld: 0x%04x\n",i); वापस -2;पूर्ण
	अगर (get_रुको_data(cosa) != '=') वापस -3;

	अगर (puthexnumber(cosa, address) < 0) वापस -4;
	अगर (put_रुको_data(cosa, ' ') == -1) वापस -10;
	अगर (get_रुको_data(cosa) != ' ') वापस -11;
	अगर (get_रुको_data(cosa) != '=') वापस -12;

	अगर (puthexnumber(cosa, address+length-1) < 0) वापस -13;
	अगर (put_रुको_data(cosa, ' ') == -1) वापस -18;
	अगर (get_रुको_data(cosa) != ' ') वापस -19;

	जबतक (length--) अणु
		अक्षर c;
#अगर_अघोषित SRP_DOWNLOAD_AT_BOOT
		अगर (get_user(c, microcode))
			वापस -23; /* ??? */
#अन्यथा
		c = *microcode;
#पूर्ण_अगर
		अगर (put_रुको_data(cosa, c) == -1)
			वापस -20;
		microcode++;
	पूर्ण

	अगर (get_रुको_data(cosa) != '\r') वापस -21;
	अगर (get_रुको_data(cosa) != '\n') वापस -22;
	अगर (get_रुको_data(cosa) != '.') वापस -23;
#अगर 0
	prपूर्णांकk(KERN_DEBUG "cosa%d: download completed.\n", cosa->num);
#पूर्ण_अगर
	वापस 0;
पूर्ण


/*
 * Starting microcode is करोne via the "g" command of the SRP monitor.
 * The chat should be the following: "g" "g=" "<addr><CR>"
 * "<CR><CR><LF><CR><LF>".
 */
अटल पूर्णांक starपंचांगicrocode(काष्ठा cosa_data *cosa, पूर्णांक address)
अणु
	अगर (put_रुको_data(cosa, 'g') == -1) वापस -1;
	अगर (get_रुको_data(cosa) != 'g') वापस -2;
	अगर (get_रुको_data(cosa) != '=') वापस -3;

	अगर (puthexnumber(cosa, address) < 0) वापस -4;
	अगर (put_रुको_data(cosa, '\r') == -1) वापस -5;
	
	अगर (get_रुको_data(cosa) != '\r') वापस -6;
	अगर (get_रुको_data(cosa) != '\r') वापस -7;
	अगर (get_रुको_data(cosa) != '\n') वापस -8;
	अगर (get_रुको_data(cosa) != '\r') वापस -9;
	अगर (get_रुको_data(cosa) != '\n') वापस -10;
#अगर 0
	prपूर्णांकk(KERN_DEBUG "cosa%d: microcode started\n", cosa->num);
#पूर्ण_अगर
	वापस 0;
पूर्ण

/*
 * Reading memory is करोne via the "r" command of the SRP monitor.
 * The chat is the following "r" "r=" "<addr> " " =" "<last_byte> " " "
 * Then driver can पढ़ो the data and the conversation is finished
 * by SRP monitor sending "<CR><LF>." (करोt at the end).
 *
 * This routine is not needed during the normal operation and serves
 * क्रम debugging purposes only.
 */
अटल पूर्णांक पढ़ोmem(काष्ठा cosa_data *cosa, अक्षर __user *microcode, पूर्णांक length, पूर्णांक address)
अणु
	अगर (put_रुको_data(cosa, 'r') == -1) वापस -1;
	अगर ((get_रुको_data(cosa)) != 'r') वापस -2;
	अगर ((get_रुको_data(cosa)) != '=') वापस -3;

	अगर (puthexnumber(cosa, address) < 0) वापस -4;
	अगर (put_रुको_data(cosa, ' ') == -1) वापस -5;
	अगर (get_रुको_data(cosa) != ' ') वापस -6;
	अगर (get_रुको_data(cosa) != '=') वापस -7;

	अगर (puthexnumber(cosa, address+length-1) < 0) वापस -8;
	अगर (put_रुको_data(cosa, ' ') == -1) वापस -9;
	अगर (get_रुको_data(cosa) != ' ') वापस -10;

	जबतक (length--) अणु
		अक्षर c;
		पूर्णांक i;
		अगर ((i=get_रुको_data(cosa)) == -1) अणु
			pr_info("0x%04x bytes remaining\n", length);
			वापस -11;
		पूर्ण
		c=i;
#अगर 1
		अगर (put_user(c, microcode))
			वापस -23; /* ??? */
#अन्यथा
		*microcode = c;
#पूर्ण_अगर
		microcode++;
	पूर्ण

	अगर (get_रुको_data(cosa) != '\r') वापस -21;
	अगर (get_रुको_data(cosa) != '\n') वापस -22;
	अगर (get_रुको_data(cosa) != '.') वापस -23;
#अगर 0
	prपूर्णांकk(KERN_DEBUG "cosa%d: readmem completed.\n", cosa->num);
#पूर्ण_अगर
	वापस 0;
पूर्ण

/*
 * This function resets the device and पढ़ोs the initial prompt
 * of the device's ROM monitor.
 */
अटल पूर्णांक cosa_reset_and_पढ़ो_id(काष्ठा cosa_data *cosa, अक्षर *idstring)
अणु
	पूर्णांक i=0, id=0, prev=0, curr=0;

	/* Reset the card ... */
	cosa_माला_दोtatus(cosa, 0);
	cosa_getdata8(cosa);
	cosa_माला_दोtatus(cosa, SR_RST);
	msleep(500);
	/* Disable all IRQs from the card */
	cosa_माला_दोtatus(cosa, 0);

	/*
	 * Try to पढ़ो the ID string. The card then prपूर्णांकs out the
	 * identअगरication string ended by the "\n\x2e".
	 *
	 * The following loop is indexed through i (instead of id)
	 * to aव्योम looping क्रमever when क्रम any reason
	 * the port वापसs '\r', '\n' or '\x2e' permanently.
	 */
	क्रम (i=0; i<COSA_MAX_ID_STRING-1; i++, prev=curr) अणु
		अगर ((curr = get_रुको_data(cosa)) == -1) अणु
			वापस -1;
		पूर्ण
		curr &= 0xff;
		अगर (curr != '\r' && curr != '\n' && curr != 0x2e)
			idstring[id++] = curr;
		अगर (curr == 0x2e && prev == '\n')
			अवरोध;
	पूर्ण
	/* Perhaps we should fail when i==COSA_MAX_ID_STRING-1 ? */
	idstring[id] = '\0';
	वापस id;
पूर्ण


/* ---------- Auxiliary routines क्रम COSA/SRP monitor ---------- */

/*
 * This routine माला_लो the data byte from the card रुकोing क्रम the SR_RX_RDY
 * bit to be set in a loop. It should be used in the exceptional हालs
 * only (क्रम example when resetting the card or करोwnloading the firmware.
 */
अटल पूर्णांक get_रुको_data(काष्ठा cosa_data *cosa)
अणु
	पूर्णांक retries = 1000;

	जबतक (--retries) अणु
		/* पढ़ो data and वापस them */
		अगर (cosa_माला_लोtatus(cosa) & SR_RX_RDY) अणु
			लघु r;
			r = cosa_getdata8(cosa);
#अगर 0
			pr_info("get_wait_data returning after %d retries\n",
				999-retries);
#पूर्ण_अगर
			वापस r;
		पूर्ण
		/* sleep अगर not पढ़ोy to पढ़ो */
		schedule_समयout_पूर्णांकerruptible(1);
	पूर्ण
	pr_info("timeout in get_wait_data (status 0x%x)\n",
		cosa_माला_लोtatus(cosa));
	वापस -1;
पूर्ण

/*
 * This routine माला_दो the data byte to the card रुकोing क्रम the SR_TX_RDY
 * bit to be set in a loop. It should be used in the exceptional हालs
 * only (क्रम example when resetting the card or करोwnloading the firmware).
 */
अटल पूर्णांक put_रुको_data(काष्ठा cosa_data *cosa, पूर्णांक data)
अणु
	पूर्णांक retries = 1000;
	जबतक (--retries) अणु
		/* पढ़ो data and वापस them */
		अगर (cosa_माला_लोtatus(cosa) & SR_TX_RDY) अणु
			cosa_putdata8(cosa, data);
#अगर 0
			pr_info("Putdata: %d retries\n", 999-retries);
#पूर्ण_अगर
			वापस 0;
		पूर्ण
#अगर 0
		/* sleep अगर not पढ़ोy to पढ़ो */
		schedule_समयout_पूर्णांकerruptible(1);
#पूर्ण_अगर
	पूर्ण
	pr_info("cosa%d: timeout in put_wait_data (status 0x%x)\n",
		cosa->num, cosa_माला_लोtatus(cosa));
	वापस -1;
पूर्ण
	
/* 
 * The following routine माला_दो the hexadecimal number पूर्णांकo the SRP monitor
 * and verअगरies the proper echo of the sent bytes. Returns 0 on success,
 * negative number on failure (-1,-3,-5,-7) means that put_रुको_data() failed,
 * (-2,-4,-6,-8) means that पढ़ोing echo failed.
 */
अटल पूर्णांक puthexnumber(काष्ठा cosa_data *cosa, पूर्णांक number)
अणु
	अक्षर temp[5];
	पूर्णांक i;

	/* Well, I should probably replace this by something faster. */
	प्र_लिखो(temp, "%04X", number);
	क्रम (i=0; i<4; i++) अणु
		अगर (put_रुको_data(cosa, temp[i]) == -1) अणु
			pr_notice("cosa%d: puthexnumber failed to write byte %d\n",
				  cosa->num, i);
			वापस -1-2*i;
		पूर्ण
		अगर (get_रुको_data(cosa) != temp[i]) अणु
			pr_notice("cosa%d: puthexhumber failed to read echo of byte %d\n",
				  cosa->num, i);
			वापस -2-2*i;
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण


/* ---------- Interrupt routines ---------- */

/*
 * There are three types of पूर्णांकerrupt:
 * At the beginning of transmit - this handled is in tx_पूर्णांकerrupt(),
 * at the beginning of receive - it is in rx_पूर्णांकerrupt() and
 * at the end of transmit/receive - it is the eot_पूर्णांकerrupt() function.
 * These functions are multiplexed by cosa_पूर्णांकerrupt() according to the
 * COSA status byte. I have moved the rx/tx/eot पूर्णांकerrupt handling पूर्णांकo
 * separate functions to make it more पढ़ोable. These functions are अंतरभूत,
 * so there should be no overhead of function call.
 * 
 * In the COSA bus-master mode, we need to tell the card the address of a
 * buffer. Unक्रमtunately, COSA may be too slow क्रम us, so we must busy-रुको.
 * It's समय to use the bottom half :-(
 */

/*
 * Transmit पूर्णांकerrupt routine - called when COSA is willing to obtain
 * data from the OS. The most tricky part of the routine is selection
 * of channel we (OS) want to send packet क्रम. For SRP we should probably
 * use the round-robin approach. The newer COSA firmwares have a simple
 * flow-control - in the status word has bits 2 and 3 set to 1 means that the
 * channel 0 or 1 करोesn't want to receive data.
 *
 * It seems there is a bug in COSA firmware (need to trace it further):
 * When the driver status says that the kernel has no more data क्रम transmit
 * (e.g. at the end of TX DMA) and then the kernel changes its mind
 * (e.g. new packet is queued to hard_start_xmit()), the card issues
 * the TX पूर्णांकerrupt but करोes not mark the channel as पढ़ोy-to-transmit.
 * The fix seems to be to push the packet to COSA despite its request.
 * We first try to obey the card's opinion, and then fall back to क्रमced TX.
 */
अटल अंतरभूत व्योम tx_पूर्णांकerrupt(काष्ठा cosa_data *cosa, पूर्णांक status)
अणु
	अचिन्हित दीर्घ flags, flags1;
#अगर_घोषित DEBUG_IRQS
	pr_info("cosa%d: SR_DOWN_REQUEST status=0x%04x\n", cosa->num, status);
#पूर्ण_अगर
	spin_lock_irqsave(&cosa->lock, flags);
	set_bit(TXBIT, &cosa->rxtx);
	अगर (!test_bit(IRQBIT, &cosa->rxtx)) अणु
		/* flow control, see the comment above */
		पूर्णांक i=0;
		अगर (!cosa->txbiपंचांगap) अणु
			pr_warn("%s: No channel wants data in TX IRQ. Expect DMA timeout.\n",
				cosa->name);
			put_driver_status_nolock(cosa);
			clear_bit(TXBIT, &cosa->rxtx);
			spin_unlock_irqrestore(&cosa->lock, flags);
			वापस;
		पूर्ण
		जबतक (1) अणु
			cosa->txchan++;
			i++;
			अगर (cosa->txchan >= cosa->nchannels)
				cosa->txchan = 0;
			अगर (!(cosa->txbiपंचांगap & (1<<cosa->txchan)))
				जारी;
			अगर (~status & (1 << (cosa->txchan+DRIVER_TXMAP_SHIFT)))
				अवरोध;
			/* in second pass, accept first पढ़ोy-to-TX channel */
			अगर (i > cosa->nchannels) अणु
				/* Can be safely ignored */
#अगर_घोषित DEBUG_IRQS
				prपूर्णांकk(KERN_DEBUG "%s: Forcing TX "
					"to not-ready channel %d\n",
					cosa->name, cosa->txchan);
#पूर्ण_अगर
				अवरोध;
			पूर्ण
		पूर्ण

		cosa->txsize = cosa->chan[cosa->txchan].txsize;
		अगर (cosa_dma_able(cosa->chan+cosa->txchan,
			cosa->chan[cosa->txchan].txbuf, cosa->txsize)) अणु
			cosa->txbuf = cosa->chan[cosa->txchan].txbuf;
		पूर्ण अन्यथा अणु
			स_नकल(cosa->bouncebuf, cosa->chan[cosa->txchan].txbuf,
				cosa->txsize);
			cosa->txbuf = cosa->bouncebuf;
		पूर्ण
	पूर्ण

	अगर (is_8bit(cosa)) अणु
		अगर (!test_bit(IRQBIT, &cosa->rxtx)) अणु
			cosa_माला_दोtatus(cosa, SR_TX_INT_ENA);
			cosa_putdata8(cosa, ((cosa->txchan << 5) & 0xe0)|
				((cosa->txsize >> 8) & 0x1f));
#अगर_घोषित DEBUG_IO
			debug_status_out(cosa, SR_TX_INT_ENA);
			debug_data_out(cosa, ((cosa->txchan << 5) & 0xe0)|
                                ((cosa->txsize >> 8) & 0x1f));
			debug_data_in(cosa, cosa_getdata8(cosa));
#अन्यथा
			cosa_getdata8(cosa);
#पूर्ण_अगर
			set_bit(IRQBIT, &cosa->rxtx);
			spin_unlock_irqrestore(&cosa->lock, flags);
			वापस;
		पूर्ण अन्यथा अणु
			clear_bit(IRQBIT, &cosa->rxtx);
			cosa_माला_दोtatus(cosa, 0);
			cosa_putdata8(cosa, cosa->txsize&0xff);
#अगर_घोषित DEBUG_IO
			debug_status_out(cosa, 0);
			debug_data_out(cosa, cosa->txsize&0xff);
#पूर्ण_अगर
		पूर्ण
	पूर्ण अन्यथा अणु
		cosa_माला_दोtatus(cosa, SR_TX_INT_ENA);
		cosa_putdata16(cosa, ((cosa->txchan<<13) & 0xe000)
			| (cosa->txsize & 0x1fff));
#अगर_घोषित DEBUG_IO
		debug_status_out(cosa, SR_TX_INT_ENA);
		debug_data_out(cosa, ((cosa->txchan<<13) & 0xe000)
                        | (cosa->txsize & 0x1fff));
		debug_data_in(cosa, cosa_getdata8(cosa));
		debug_status_out(cosa, 0);
#अन्यथा
		cosa_getdata8(cosa);
#पूर्ण_अगर
		cosa_माला_दोtatus(cosa, 0);
	पूर्ण

	अगर (cosa->busmaster) अणु
		अचिन्हित दीर्घ addr = virt_to_bus(cosa->txbuf);
		पूर्णांक count=0;
		pr_info("busmaster IRQ\n");
		जबतक (!(cosa_माला_लोtatus(cosa)&SR_TX_RDY)) अणु
			count++;
			udelay(10);
			अगर (count > 1000) अवरोध;
		पूर्ण
		pr_info("status %x\n", cosa_माला_लोtatus(cosa));
		pr_info("ready after %d loops\n", count);
		cosa_putdata16(cosa, (addr >> 16)&0xffff);

		count = 0;
		जबतक (!(cosa_माला_लोtatus(cosa)&SR_TX_RDY)) अणु
			count++;
			अगर (count > 1000) अवरोध;
			udelay(10);
		पूर्ण
		pr_info("ready after %d loops\n", count);
		cosa_putdata16(cosa, addr &0xffff);
		flags1 = claim_dma_lock();
		set_dma_mode(cosa->dma, DMA_MODE_CASCADE);
		enable_dma(cosa->dma);
		release_dma_lock(flags1);
	पूर्ण अन्यथा अणु
		/* start the DMA */
		flags1 = claim_dma_lock();
		disable_dma(cosa->dma);
		clear_dma_ff(cosa->dma);
		set_dma_mode(cosa->dma, DMA_MODE_WRITE);
		set_dma_addr(cosa->dma, virt_to_bus(cosa->txbuf));
		set_dma_count(cosa->dma, cosa->txsize);
		enable_dma(cosa->dma);
		release_dma_lock(flags1);
	पूर्ण
	cosa_माला_दोtatus(cosa, SR_TX_DMA_ENA|SR_USR_INT_ENA);
#अगर_घोषित DEBUG_IO
	debug_status_out(cosa, SR_TX_DMA_ENA|SR_USR_INT_ENA);
#पूर्ण_अगर
	spin_unlock_irqrestore(&cosa->lock, flags);
पूर्ण

अटल अंतरभूत व्योम rx_पूर्णांकerrupt(काष्ठा cosa_data *cosa, पूर्णांक status)
अणु
	अचिन्हित दीर्घ flags;
#अगर_घोषित DEBUG_IRQS
	pr_info("cosa%d: SR_UP_REQUEST\n", cosa->num);
#पूर्ण_अगर

	spin_lock_irqsave(&cosa->lock, flags);
	set_bit(RXBIT, &cosa->rxtx);

	अगर (is_8bit(cosa)) अणु
		अगर (!test_bit(IRQBIT, &cosa->rxtx)) अणु
			set_bit(IRQBIT, &cosa->rxtx);
			put_driver_status_nolock(cosa);
			cosa->rxsize = cosa_getdata8(cosa) <<8;
#अगर_घोषित DEBUG_IO
			debug_data_in(cosa, cosa->rxsize >> 8);
#पूर्ण_अगर
			spin_unlock_irqrestore(&cosa->lock, flags);
			वापस;
		पूर्ण अन्यथा अणु
			clear_bit(IRQBIT, &cosa->rxtx);
			cosa->rxsize |= cosa_getdata8(cosa) & 0xff;
#अगर_घोषित DEBUG_IO
			debug_data_in(cosa, cosa->rxsize & 0xff);
#पूर्ण_अगर
#अगर 0
			pr_info("cosa%d: receive rxsize = (0x%04x)\n",
				cosa->num, cosa->rxsize);
#पूर्ण_अगर
		पूर्ण
	पूर्ण अन्यथा अणु
		cosa->rxsize = cosa_getdata16(cosa);
#अगर_घोषित DEBUG_IO
		debug_data_in(cosa, cosa->rxsize);
#पूर्ण_अगर
#अगर 0
		pr_info("cosa%d: receive rxsize = (0x%04x)\n",
			cosa->num, cosa->rxsize);
#पूर्ण_अगर
	पूर्ण
	अगर (((cosa->rxsize & 0xe000) >> 13) >= cosa->nchannels) अणु
		pr_warn("%s: rx for unknown channel (0x%04x)\n",
			cosa->name, cosa->rxsize);
		spin_unlock_irqrestore(&cosa->lock, flags);
		जाओ reject;
	पूर्ण
	cosa->rxchan = cosa->chan + ((cosa->rxsize & 0xe000) >> 13);
	cosa->rxsize &= 0x1fff;
	spin_unlock_irqrestore(&cosa->lock, flags);

	cosa->rxbuf = शून्य;
	अगर (cosa->rxchan->setup_rx)
		cosa->rxbuf = cosa->rxchan->setup_rx(cosa->rxchan, cosa->rxsize);

	अगर (!cosa->rxbuf) अणु
reject:		/* Reject the packet */
		pr_info("cosa%d: rejecting packet on channel %d\n",
			cosa->num, cosa->rxchan->num);
		cosa->rxbuf = cosa->bouncebuf;
	पूर्ण

	/* start the DMA */
	flags = claim_dma_lock();
	disable_dma(cosa->dma);
	clear_dma_ff(cosa->dma);
	set_dma_mode(cosa->dma, DMA_MODE_READ);
	अगर (cosa_dma_able(cosa->rxchan, cosa->rxbuf, cosa->rxsize & 0x1fff)) अणु
		set_dma_addr(cosa->dma, virt_to_bus(cosa->rxbuf));
	पूर्ण अन्यथा अणु
		set_dma_addr(cosa->dma, virt_to_bus(cosa->bouncebuf));
	पूर्ण
	set_dma_count(cosa->dma, (cosa->rxsize&0x1fff));
	enable_dma(cosa->dma);
	release_dma_lock(flags);
	spin_lock_irqsave(&cosa->lock, flags);
	cosa_माला_दोtatus(cosa, SR_RX_DMA_ENA|SR_USR_INT_ENA);
	अगर (!is_8bit(cosa) && (status & SR_TX_RDY))
		cosa_putdata8(cosa, DRIVER_RX_READY);
#अगर_घोषित DEBUG_IO
	debug_status_out(cosa, SR_RX_DMA_ENA|SR_USR_INT_ENA);
	अगर (!is_8bit(cosa) && (status & SR_TX_RDY))
		debug_data_cmd(cosa, DRIVER_RX_READY);
#पूर्ण_अगर
	spin_unlock_irqrestore(&cosa->lock, flags);
पूर्ण

अटल अंतरभूत व्योम eot_पूर्णांकerrupt(काष्ठा cosa_data *cosa, पूर्णांक status)
अणु
	अचिन्हित दीर्घ flags, flags1;
	spin_lock_irqsave(&cosa->lock, flags);
	flags1 = claim_dma_lock();
	disable_dma(cosa->dma);
	clear_dma_ff(cosa->dma);
	release_dma_lock(flags1);
	अगर (test_bit(TXBIT, &cosa->rxtx)) अणु
		काष्ठा channel_data *chan = cosa->chan+cosa->txchan;
		अगर (chan->tx_करोne)
			अगर (chan->tx_करोne(chan, cosa->txsize))
				clear_bit(chan->num, &cosa->txbiपंचांगap);
	पूर्ण अन्यथा अगर (test_bit(RXBIT, &cosa->rxtx)) अणु
#अगर_घोषित DEBUG_DATA
	अणु
		पूर्णांक i;
		pr_info("cosa%dc%d: done rx(0x%x)",
			cosa->num, cosa->rxchan->num, cosa->rxsize);
		क्रम (i=0; i<cosa->rxsize; i++)
			pr_cont(" %02x", cosa->rxbuf[i]&0xff);
		pr_cont("\n");
	पूर्ण
#पूर्ण_अगर
		/* Packet क्रम unknown channel? */
		अगर (cosa->rxbuf == cosa->bouncebuf)
			जाओ out;
		अगर (!cosa_dma_able(cosa->rxchan, cosa->rxbuf, cosa->rxsize))
			स_नकल(cosa->rxbuf, cosa->bouncebuf, cosa->rxsize);
		अगर (cosa->rxchan->rx_करोne)
			अगर (cosa->rxchan->rx_करोne(cosa->rxchan))
				clear_bit(cosa->rxchan->num, &cosa->rxbiपंचांगap);
	पूर्ण अन्यथा अणु
		pr_notice("cosa%d: unexpected EOT interrupt\n", cosa->num);
	पूर्ण
	/*
	 * Clear the RXBIT, TXBIT and IRQBIT (the latest should be
	 * cleared anyway). We should करो it as soon as possible
	 * so that we can tell the COSA we are करोne and to give it a समय
	 * क्रम recovery.
	 */
out:
	cosa->rxtx = 0;
	put_driver_status_nolock(cosa);
	spin_unlock_irqrestore(&cosa->lock, flags);
पूर्ण

अटल irqवापस_t cosa_पूर्णांकerrupt(पूर्णांक irq, व्योम *cosa_)
अणु
	अचिन्हित status;
	पूर्णांक count = 0;
	काष्ठा cosa_data *cosa = cosa_;
again:
	status = cosa_माला_लोtatus(cosa);
#अगर_घोषित DEBUG_IRQS
	pr_info("cosa%d: got IRQ, status 0x%02x\n", cosa->num, status & 0xff);
#पूर्ण_अगर
#अगर_घोषित DEBUG_IO
	debug_status_in(cosa, status);
#पूर्ण_अगर
	चयन (status & SR_CMD_FROM_SRP_MASK) अणु
	हाल SR_DOWN_REQUEST:
		tx_पूर्णांकerrupt(cosa, status);
		अवरोध;
	हाल SR_UP_REQUEST:
		rx_पूर्णांकerrupt(cosa, status);
		अवरोध;
	हाल SR_END_OF_TRANSFER:
		eot_पूर्णांकerrupt(cosa, status);
		अवरोध;
	शेष:
		/* We may be too fast क्रम SRP. Try to रुको a bit more. */
		अगर (count++ < 100) अणु
			udelay(100);
			जाओ again;
		पूर्ण
		pr_info("cosa%d: unknown status 0x%02x in IRQ after %d retries\n",
			cosa->num, status & 0xff, count);
	पूर्ण
#अगर_घोषित DEBUG_IRQS
	अगर (count)
		pr_info("%s: %d-times got unknown status in IRQ\n",
			cosa->name, count);
	अन्यथा
		pr_info("%s: returning from IRQ\n", cosa->name);
#पूर्ण_अगर
	वापस IRQ_HANDLED;
पूर्ण


/* ---------- I/O debugging routines ---------- */
/*
 * These routines can be used to monitor COSA/SRP I/O and to prपूर्णांकk()
 * the data being transferred on the data and status I/O port in a
 * पढ़ोable way.
 */

#अगर_घोषित DEBUG_IO
अटल व्योम debug_status_in(काष्ठा cosa_data *cosa, पूर्णांक status)
अणु
	अक्षर *s;
	चयन (status & SR_CMD_FROM_SRP_MASK) अणु
	हाल SR_UP_REQUEST:
		s = "RX_REQ";
		अवरोध;
	हाल SR_DOWN_REQUEST:
		s = "TX_REQ";
		अवरोध;
	हाल SR_END_OF_TRANSFER:
		s = "ET_REQ";
		अवरोध;
	शेष:
		s = "NO_REQ";
		अवरोध;
	पूर्ण
	pr_info("%s: IO: status -> 0x%02x (%s%s%s%s)\n",
		cosa->name,
		status,
		status & SR_USR_RQ ? "USR_RQ|" : "",
		status & SR_TX_RDY ? "TX_RDY|" : "",
		status & SR_RX_RDY ? "RX_RDY|" : "",
		s);
पूर्ण

अटल व्योम debug_status_out(काष्ठा cosa_data *cosa, पूर्णांक status)
अणु
	pr_info("%s: IO: status <- 0x%02x (%s%s%s%s%s%s)\n",
		cosa->name,
		status,
		status & SR_RX_DMA_ENA  ? "RXDMA|"  : "!rxdma|",
		status & SR_TX_DMA_ENA  ? "TXDMA|"  : "!txdma|",
		status & SR_RST         ? "RESET|"  : "",
		status & SR_USR_INT_ENA ? "USRINT|" : "!usrint|",
		status & SR_TX_INT_ENA  ? "TXINT|"  : "!txint|",
		status & SR_RX_INT_ENA  ? "RXINT"   : "!rxint");
पूर्ण

अटल व्योम debug_data_in(काष्ठा cosa_data *cosa, पूर्णांक data)
अणु
	pr_info("%s: IO: data -> 0x%04x\n", cosa->name, data);
पूर्ण

अटल व्योम debug_data_out(काष्ठा cosa_data *cosa, पूर्णांक data)
अणु
	pr_info("%s: IO: data <- 0x%04x\n", cosa->name, data);
पूर्ण

अटल व्योम debug_data_cmd(काष्ठा cosa_data *cosa, पूर्णांक data)
अणु
	pr_info("%s: IO: data <- 0x%04x (%s|%s)\n",
		cosa->name, data,
		data & SR_RDY_RCV ? "RX_RDY" : "!rx_rdy",
		data & SR_RDY_SND ? "TX_RDY" : "!tx_rdy");
पूर्ण
#पूर्ण_अगर

/* खातापूर्ण -- this file has not been truncated */
