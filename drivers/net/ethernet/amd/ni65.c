<शैली गुरु>
/*
 * ni6510 (am7990 'lance' chip) driver क्रम Linux-net-3
 * BETAcode v0.71 (96/09/29) क्रम 2.0.0 (or later)
 * copyrights (c) 1994,1995,1996 by M.Hipp
 *
 * This driver can handle the old ni6510 board and the newer ni6510
 * EtherBlaster. (probably it also works with every full NE2100
 * compatible card)
 *
 * driver probes: io: 0x360,0x300,0x320,0x340 / dma: 3,5,6,7
 *
 * This is an extension to the Linux operating प्रणाली, and is covered by the
 * same GNU General Public License that covers the Linux-kernel.
 *
 * comments/bugs/suggestions can be sent to:
 *   Michael Hipp
 *   email: hippm@inक्रमmatik.uni-tuebingen.de
 *
 * sources:
 *   some things are from the 'ni6510-packet-driver for dos by Russ Nelson'
 *   and from the original drivers by D.Becker
 *
 * known problems:
 *   - on some PCI boards (including my own) the card/board/ISA-bridge has
 *     problems with bus master DMA. This results in lotsa overruns.
 *     It may help to '#define RCV_PARANOIA_CHECK' or try to #अघोषित
 *     the XMT and RCV_VIA_SKB option .. this reduces driver perक्रमmance.
 *     Or just play with your BIOS options to optimize ISA-DMA access.
 *     Maybe you also wanna play with the LOW_PERFORAMCE and MID_PERFORMANCE
 *     defines -> please report me your experience then
 *   - Harald reported क्रम ASUS SP3G मुख्यboards, that you should use
 *     the 'optimal settings' from the user's manual on page 3-12!
 *
 * credits:
 *   thanx to Jason Sullivan क्रम sending me a ni6510 card!
 *   lot of debug runs with ASUS SP3G Boards (Intel Saturn) by Harald Koenig
 *
 * simple perक्रमmance test: (486DX-33/Ni6510-EB receives from 486DX4-100/Ni6510-EB)
 *    average: FTP -> 8384421 bytes received in 8.5 seconds
 *           (no RCV_VIA_SKB,no XMT_VIA_SKB,PARANOIA_CHECK,4 XMIT BUFS, 8 RCV_BUFFS)
 *    peak: FTP -> 8384421 bytes received in 7.5 seconds
 *           (RCV_VIA_SKB,XMT_VIA_SKB,no PARANOIA_CHECK,1(!) XMIT BUF, 16 RCV BUFFS)
 */

/*
 * 99.Jun.8: added support क्रम /proc/net/dev byte count क्रम xosview (HK)
 * 96.Sept.29: virt_to_bus stuff added क्रम new memory modell
 * 96.April.29: Added Harald Koenig's Patches (MH)
 * 96.April.13: enhanced error handling .. more tests (MH)
 * 96.April.5/6: a lot of perक्रमmance tests. Got it stable now (hopefully) (MH)
 * 96.April.1: (no joke ;) .. added EtherBlaster and Module support (MH)
 * 96.Feb.19: fixed a few bugs .. cleanups .. tested क्रम 1.3.66 (MH)
 *            hopefully no more 16MB limit
 *
 * 95.Nov.18: multicast tweaked (AC).
 *
 * 94.Aug.22: changes in xmit_पूर्णांकr (ack more than one xmitted-packet), ni65_send_packet (p->lock) (MH)
 *
 * 94.July.16: fixed bugs in recv_skb and skb-alloc stuff  (MH)
 */

#समावेश <linux/kernel.h>
#समावेश <linux/माला.स>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/ioport.h>
#समावेश <linux/slab.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/delay.h>
#समावेश <linux/init.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/etherdevice.h>
#समावेश <linux/skbuff.h>
#समावेश <linux/module.h>
#समावेश <linux/bitops.h>

#समावेश <यंत्र/पन.स>
#समावेश <यंत्र/dma.h>

#समावेश "ni65.h"

/*
 * the current setting allows an acceptable perक्रमmance
 * क्रम 'RCV_PARANOIA_CHECK' read the 'known problems' part in
 * the header of this file
 * 'invert' the defines क्रम max. perक्रमmance. This may cause DMA problems
 * on some boards (e.g on my ASUS SP3G)
 */
#अघोषित XMT_VIA_SKB
#अघोषित RCV_VIA_SKB
#घोषणा RCV_PARANOIA_CHECK

#घोषणा MID_PERFORMANCE

#अगर   defined( LOW_PERFORMANCE )
 अटल पूर्णांक isa0=7,isa1=7,csr80=0x0c10;
#या_अगर defined( MID_PERFORMANCE )
 अटल पूर्णांक isa0=5,isa1=5,csr80=0x2810;
#अन्यथा	/* high perक्रमmance */
 अटल पूर्णांक isa0=4,isa1=4,csr80=0x0017;
#पूर्ण_अगर

/*
 * a few card/venकरोr specअगरic defines
 */
#घोषणा NI65_ID0    0x00
#घोषणा NI65_ID1    0x55
#घोषणा NI65_EB_ID0 0x52
#घोषणा NI65_EB_ID1 0x44
#घोषणा NE2100_ID0  0x57
#घोषणा NE2100_ID1  0x57

#घोषणा PORT p->cmdr_addr

/*
 * buffer configuration
 */
#अगर 1
#घोषणा RMDNUM 16
#घोषणा RMDNUMMASK 0x80000000
#अन्यथा
#घोषणा RMDNUM 8
#घोषणा RMDNUMMASK 0x60000000 /* log2(RMDNUM)<<29 */
#पूर्ण_अगर

#अगर 0
#घोषणा TMDNUM 1
#घोषणा TMDNUMMASK 0x00000000
#अन्यथा
#घोषणा TMDNUM 4
#घोषणा TMDNUMMASK 0x40000000 /* log2(TMDNUM)<<29 */
#पूर्ण_अगर

/* slightly oversized */
#घोषणा R_BUF_SIZE 1544
#घोषणा T_BUF_SIZE 1544

/*
 * lance रेजिस्टर defines
 */
#घोषणा L_DATAREG 0x00
#घोषणा L_ADDRREG 0x02
#घोषणा L_RESET   0x04
#घोषणा L_CONFIG  0x05
#घोषणा L_BUSIF   0x06

/*
 * to access the lance/am7990-regs, you have to ग_लिखो
 * reg-number पूर्णांकo L_ADDRREG, then you can access it using L_DATAREG
 */
#घोषणा CSR0  0x00
#घोषणा CSR1  0x01
#घोषणा CSR2  0x02
#घोषणा CSR3  0x03

#घोषणा INIT_RING_BEFORE_START	0x1
#घोषणा FULL_RESET_ON_ERROR	0x2

#अगर 0
#घोषणा ग_लिखोreg(val,reg) अणुoutw(reg,PORT+L_ADDRREG);inw(PORT+L_ADDRREG); \
                           outw(val,PORT+L_DATAREG);inw(PORT+L_DATAREG);पूर्ण
#घोषणा पढ़ोreg(reg) (outw(reg,PORT+L_ADDRREG),inw(PORT+L_ADDRREG),\
                       inw(PORT+L_DATAREG))
#अगर 0
#घोषणा ग_लिखोdatareg(val) अणुoutw(val,PORT+L_DATAREG);inw(PORT+L_DATAREG);पूर्ण
#अन्यथा
#घोषणा ग_लिखोdatareg(val) अणु  ग_लिखोreg(val,CSR0); पूर्ण
#पूर्ण_अगर
#अन्यथा
#घोषणा ग_लिखोreg(val,reg) अणुoutw(reg,PORT+L_ADDRREG);outw(val,PORT+L_DATAREG);पूर्ण
#घोषणा पढ़ोreg(reg) (outw(reg,PORT+L_ADDRREG),inw(PORT+L_DATAREG))
#घोषणा ग_लिखोdatareg(val) अणु ग_लिखोreg(val,CSR0); पूर्ण
#पूर्ण_अगर

अटल अचिन्हित अक्षर ni_venकरोr[] = अणु 0x02,0x07,0x01 पूर्ण;

अटल काष्ठा card अणु
	अचिन्हित अक्षर id0,id1;
	लघु id_offset;
	लघु total_size;
	लघु cmd_offset;
	लघु addr_offset;
	अचिन्हित अक्षर *venकरोr_id;
	अक्षर *cardname;
	अचिन्हित दीर्घ config;
पूर्ण cards[] = अणु
	अणु
		.id0	     = NI65_ID0,
		.id1	     = NI65_ID1,
		.id_offset   = 0x0e,
		.total_size  = 0x10,
		.cmd_offset  = 0x0,
		.addr_offset = 0x8,
		.venकरोr_id   = ni_venकरोr,
		.cardname    = "ni6510",
		.config	     = 0x1,
       	पूर्ण,
	अणु
		.id0	     = NI65_EB_ID0,
		.id1	     = NI65_EB_ID1,
		.id_offset   = 0x0e,
		.total_size  = 0x18,
		.cmd_offset  = 0x10,
		.addr_offset = 0x0,
		.venकरोr_id   = ni_venकरोr,
		.cardname    = "ni6510 EtherBlaster",
		.config	     = 0x2,
       	पूर्ण,
	अणु
		.id0	     = NE2100_ID0,
		.id1	     = NE2100_ID1,
		.id_offset   = 0x0e,
		.total_size  = 0x18,
		.cmd_offset  = 0x10,
		.addr_offset = 0x0,
		.venकरोr_id   = शून्य,
		.cardname    = "generic NE2100",
		.config	     = 0x0,
	पूर्ण,
पूर्ण;
#घोषणा NUM_CARDS 3

काष्ठा priv
अणु
	काष्ठा rmd rmdhead[RMDNUM];
	काष्ठा पंचांगd पंचांगdhead[TMDNUM];
	काष्ठा init_block ib;
	पूर्णांक rmdnum;
	पूर्णांक पंचांगdnum,पंचांगdlast;
#अगर_घोषित RCV_VIA_SKB
	काष्ठा sk_buff *recv_skb[RMDNUM];
#अन्यथा
	व्योम *recvbounce[RMDNUM];
#पूर्ण_अगर
#अगर_घोषित XMT_VIA_SKB
	काष्ठा sk_buff *पंचांगd_skb[TMDNUM];
#पूर्ण_अगर
	व्योम *पंचांगdbounce[TMDNUM];
	पूर्णांक पंचांगdbouncक्रमागत;
	पूर्णांक lock,xmit_queued;

	व्योम *self;
	पूर्णांक cmdr_addr;
	पूर्णांक cardno;
	पूर्णांक features;
	spinlock_t ring_lock;
पूर्ण;

अटल पूर्णांक  ni65_probe1(काष्ठा net_device *dev,पूर्णांक);
अटल irqवापस_t ni65_पूर्णांकerrupt(पूर्णांक irq, व्योम * dev_id);
अटल व्योम ni65_recv_पूर्णांकr(काष्ठा net_device *dev,पूर्णांक);
अटल व्योम ni65_xmit_पूर्णांकr(काष्ठा net_device *dev,पूर्णांक);
अटल पूर्णांक  ni65_खोलो(काष्ठा net_device *dev);
अटल पूर्णांक  ni65_lance_reinit(काष्ठा net_device *dev);
अटल व्योम ni65_init_lance(काष्ठा priv *p,अचिन्हित अक्षर*,पूर्णांक,पूर्णांक);
अटल netdev_tx_t ni65_send_packet(काष्ठा sk_buff *skb,
				    काष्ठा net_device *dev);
अटल व्योम  ni65_समयout(काष्ठा net_device *dev, अचिन्हित पूर्णांक txqueue);
अटल पूर्णांक  ni65_बंद(काष्ठा net_device *dev);
अटल पूर्णांक  ni65_alloc_buffer(काष्ठा net_device *dev);
अटल व्योम ni65_मुक्त_buffer(काष्ठा priv *p);
अटल व्योम set_multicast_list(काष्ठा net_device *dev);

अटल पूर्णांक irqtab[] __initdata = अणु 9,12,15,5 पूर्ण; /* irq config-translate */
अटल पूर्णांक dmatab[] __initdata = अणु 0,3,5,6,7 पूर्ण; /* dma config-translate and स्वतःdetect */

अटल पूर्णांक debuglevel = 1;

/*
 * set 'performance' रेजिस्टरs .. we must STOP lance क्रम that
 */
अटल व्योम ni65_set_perक्रमmance(काष्ठा priv *p)
अणु
	ग_लिखोreg(CSR0_STOP | CSR0_CLRALL,CSR0); /* STOP */

	अगर( !(cards[p->cardno].config & 0x02) )
		वापस;

	outw(80,PORT+L_ADDRREG);
	अगर(inw(PORT+L_ADDRREG) != 80)
		वापस;

	ग_लिखोreg( (csr80 & 0x3fff) ,80); /* FIFO watermarks */
	outw(0,PORT+L_ADDRREG);
	outw((लघु)isa0,PORT+L_BUSIF); /* ग_लिखो ISA 0: DMA_R : isa0 * 50ns */
	outw(1,PORT+L_ADDRREG);
	outw((लघु)isa1,PORT+L_BUSIF); /* ग_लिखो ISA 1: DMA_W : isa1 * 50ns	*/

	outw(CSR0,PORT+L_ADDRREG);	/* चयन back to CSR0 */
पूर्ण

/*
 * खोलो पूर्णांकerface (up)
 */
अटल पूर्णांक ni65_खोलो(काष्ठा net_device *dev)
अणु
	काष्ठा priv *p = dev->ml_priv;
	पूर्णांक irqval = request_irq(dev->irq, ni65_पूर्णांकerrupt,0,
                        cards[p->cardno].cardname,dev);
	अगर (irqval) अणु
		prपूर्णांकk(KERN_ERR "%s: unable to get IRQ %d (irqval=%d).\n",
		          dev->name,dev->irq, irqval);
		वापस -EAGAIN;
	पूर्ण

	अगर(ni65_lance_reinit(dev))
	अणु
		netअगर_start_queue(dev);
		वापस 0;
	पूर्ण
	अन्यथा
	अणु
		मुक्त_irq(dev->irq,dev);
		वापस -EAGAIN;
	पूर्ण
पूर्ण

/*
 * बंद पूर्णांकerface (करोwn)
 */
अटल पूर्णांक ni65_बंद(काष्ठा net_device *dev)
अणु
	काष्ठा priv *p = dev->ml_priv;

	netअगर_stop_queue(dev);

	outw(inw(PORT+L_RESET),PORT+L_RESET); /* that's the hard way */

#अगर_घोषित XMT_VIA_SKB
	अणु
		पूर्णांक i;
		क्रम(i=0;i<TMDNUM;i++)
		अणु
			अगर(p->पंचांगd_skb[i]) अणु
				dev_kमुक्त_skb(p->पंचांगd_skb[i]);
				p->पंचांगd_skb[i] = शून्य;
			पूर्ण
		पूर्ण
	पूर्ण
#पूर्ण_अगर
	मुक्त_irq(dev->irq,dev);
	वापस 0;
पूर्ण

अटल व्योम cleanup_card(काष्ठा net_device *dev)
अणु
	काष्ठा priv *p = dev->ml_priv;
	disable_dma(dev->dma);
	मुक्त_dma(dev->dma);
	release_region(dev->base_addr, cards[p->cardno].total_size);
	ni65_मुक्त_buffer(p);
पूर्ण

/* set: io,irq,dma or set it when calling insmod */
अटल पूर्णांक irq;
अटल पूर्णांक io;
अटल पूर्णांक dma;

/*
 * Probe The Card (not the lance-chip)
 */
काष्ठा net_device * __init ni65_probe(पूर्णांक unit)
अणु
	काष्ठा net_device *dev = alloc_etherdev(0);
	अटल स्थिर पूर्णांक ports[] = अणु 0x360, 0x300, 0x320, 0x340, 0 पूर्ण;
	स्थिर पूर्णांक *port;
	पूर्णांक err = 0;

	अगर (!dev)
		वापस ERR_PTR(-ENOMEM);

	अगर (unit >= 0) अणु
		प्र_लिखो(dev->name, "eth%d", unit);
		netdev_boot_setup_check(dev);
		irq = dev->irq;
		dma = dev->dma;
	पूर्ण अन्यथा अणु
		dev->base_addr = io;
	पूर्ण

	अगर (dev->base_addr > 0x1ff) अणु /* Check a single specअगरied location. */
		err = ni65_probe1(dev, dev->base_addr);
	पूर्ण अन्यथा अगर (dev->base_addr > 0) अणु /* Don't probe at all. */
		err = -ENXIO;
	पूर्ण अन्यथा अणु
		क्रम (port = ports; *port && ni65_probe1(dev, *port); port++)
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

अटल स्थिर काष्ठा net_device_ops ni65_netdev_ops = अणु
	.nकरो_खोलो		= ni65_खोलो,
	.nकरो_stop		= ni65_बंद,
	.nकरो_start_xmit		= ni65_send_packet,
	.nकरो_tx_समयout		= ni65_समयout,
	.nकरो_set_rx_mode	= set_multicast_list,
	.nकरो_set_mac_address 	= eth_mac_addr,
	.nकरो_validate_addr	= eth_validate_addr,
पूर्ण;

/*
 * this is the real card probe ..
 */
अटल पूर्णांक __init ni65_probe1(काष्ठा net_device *dev,पूर्णांक ioaddr)
अणु
	पूर्णांक i,j;
	काष्ठा priv *p;
	अचिन्हित दीर्घ flags;

	dev->irq = irq;
	dev->dma = dma;

	क्रम(i=0;i<NUM_CARDS;i++) अणु
		अगर(!request_region(ioaddr, cards[i].total_size, cards[i].cardname))
			जारी;
		अगर(cards[i].id_offset >= 0) अणु
			अगर(inb(ioaddr+cards[i].id_offset+0) != cards[i].id0 ||
				 inb(ioaddr+cards[i].id_offset+1) != cards[i].id1) अणु
				 release_region(ioaddr, cards[i].total_size);
				 जारी;
			पूर्ण
		पूर्ण
		अगर(cards[i].venकरोr_id) अणु
			क्रम(j=0;j<3;j++)
				अगर(inb(ioaddr+cards[i].addr_offset+j) != cards[i].venकरोr_id[j])
					release_region(ioaddr, cards[i].total_size);
		पूर्ण
		अवरोध;
	पूर्ण
	अगर(i == NUM_CARDS)
		वापस -ENODEV;

	क्रम(j=0;j<6;j++)
		dev->dev_addr[j] = inb(ioaddr+cards[i].addr_offset+j);

	अगर( (j=ni65_alloc_buffer(dev)) < 0) अणु
		release_region(ioaddr, cards[i].total_size);
		वापस j;
	पूर्ण
	p = dev->ml_priv;
	p->cmdr_addr = ioaddr + cards[i].cmd_offset;
	p->cardno = i;
	spin_lock_init(&p->ring_lock);

	prपूर्णांकk(KERN_INFO "%s: %s found at %#3x, ", dev->name, cards[p->cardno].cardname , ioaddr);

	outw(inw(PORT+L_RESET),PORT+L_RESET); /* first: reset the card */
	अगर( (j=पढ़ोreg(CSR0)) != 0x4) अणु
		 prपूर्णांकk("failed.\n");
		 prपूर्णांकk(KERN_ERR "%s: Can't RESET card: %04x\n", dev->name, j);
		 ni65_मुक्त_buffer(p);
		 release_region(ioaddr, cards[p->cardno].total_size);
		 वापस -EAGAIN;
	पूर्ण

	outw(88,PORT+L_ADDRREG);
	अगर(inw(PORT+L_ADDRREG) == 88) अणु
		अचिन्हित दीर्घ v;
		v = inw(PORT+L_DATAREG);
		v <<= 16;
		outw(89,PORT+L_ADDRREG);
		v |= inw(PORT+L_DATAREG);
		prपूर्णांकk("Version %#08lx, ",v);
		p->features = INIT_RING_BEFORE_START;
	पूर्ण
	अन्यथा अणु
		prपूर्णांकk("ancient LANCE, ");
		p->features = 0x0;
	पूर्ण

	अगर(test_bit(0,&cards[i].config)) अणु
		dev->irq = irqtab[(inw(ioaddr+L_CONFIG)>>2)&3];
		dev->dma = dmatab[inw(ioaddr+L_CONFIG)&3];
		prपूर्णांकk("IRQ %d (from card), DMA %d (from card).\n",dev->irq,dev->dma);
	पूर्ण
	अन्यथा अणु
		अगर(dev->dma == 0) अणु
		/* 'stuck test' from lance.c */
			अचिन्हित दीर्घ dma_channels =
				((inb(DMA1_STAT_REG) >> 4) & 0x0f)
				| (inb(DMA2_STAT_REG) & 0xf0);
			क्रम(i=1;i<5;i++) अणु
				पूर्णांक dma = dmatab[i];
				अगर(test_bit(dma,&dma_channels) || request_dma(dma,"ni6510"))
					जारी;

				flags=claim_dma_lock();
				disable_dma(dma);
				set_dma_mode(dma,DMA_MODE_CASCADE);
				enable_dma(dma);
				release_dma_lock(flags);

				ni65_init_lance(p,dev->dev_addr,0,0); /* trigger memory access */

				flags=claim_dma_lock();
				disable_dma(dma);
				मुक्त_dma(dma);
				release_dma_lock(flags);

				अगर(पढ़ोreg(CSR0) & CSR0_IDON)
					अवरोध;
			पूर्ण
			अगर(i == 5) अणु
				prपूर्णांकk("failed.\n");
				prपूर्णांकk(KERN_ERR "%s: Can't detect DMA channel!\n", dev->name);
				ni65_मुक्त_buffer(p);
				release_region(ioaddr, cards[p->cardno].total_size);
				वापस -EAGAIN;
			पूर्ण
			dev->dma = dmatab[i];
			prपूर्णांकk("DMA %d (autodetected), ",dev->dma);
		पूर्ण
		अन्यथा
			prपूर्णांकk("DMA %d (assigned), ",dev->dma);

		अगर(dev->irq < 2)
		अणु
			अचिन्हित दीर्घ irq_mask;

			ni65_init_lance(p,dev->dev_addr,0,0);
			irq_mask = probe_irq_on();
			ग_लिखोreg(CSR0_INIT|CSR0_INEA,CSR0); /* trigger पूर्णांकerrupt */
			msleep(20);
			dev->irq = probe_irq_off(irq_mask);
			अगर(!dev->irq)
			अणु
				prपूर्णांकk("Failed to detect IRQ line!\n");
				ni65_मुक्त_buffer(p);
				release_region(ioaddr, cards[p->cardno].total_size);
				वापस -EAGAIN;
			पूर्ण
			prपूर्णांकk("IRQ %d (autodetected).\n",dev->irq);
		पूर्ण
		अन्यथा
			prपूर्णांकk("IRQ %d (assigned).\n",dev->irq);
	पूर्ण

	अगर(request_dma(dev->dma, cards[p->cardno].cardname ) != 0)
	अणु
		prपूर्णांकk(KERN_ERR "%s: Can't request dma-channel %d\n",dev->name,(पूर्णांक) dev->dma);
		ni65_मुक्त_buffer(p);
		release_region(ioaddr, cards[p->cardno].total_size);
		वापस -EAGAIN;
	पूर्ण

	dev->base_addr = ioaddr;
	dev->netdev_ops = &ni65_netdev_ops;
	dev->watchकरोg_समयo	= HZ/2;

	वापस 0; /* everything is OK */
पूर्ण

/*
 * set lance रेजिस्टर and trigger init
 */
अटल व्योम ni65_init_lance(काष्ठा priv *p,अचिन्हित अक्षर *daddr,पूर्णांक filter,पूर्णांक mode)
अणु
	पूर्णांक i;
	u32 pib;

	ग_लिखोreg(CSR0_CLRALL|CSR0_STOP,CSR0);

	क्रम(i=0;i<6;i++)
		p->ib.eaddr[i] = daddr[i];

	क्रम(i=0;i<8;i++)
		p->ib.filter[i] = filter;
	p->ib.mode = mode;

	p->ib.trp = (u32) isa_virt_to_bus(p->पंचांगdhead) | TMDNUMMASK;
	p->ib.rrp = (u32) isa_virt_to_bus(p->rmdhead) | RMDNUMMASK;
	ग_लिखोreg(0,CSR3);	/* busmaster/no word-swap */
	pib = (u32) isa_virt_to_bus(&p->ib);
	ग_लिखोreg(pib & 0xffff,CSR1);
	ग_लिखोreg(pib >> 16,CSR2);

	ग_लिखोreg(CSR0_INIT,CSR0); /* this changes L_ADDRREG to CSR0 */

	क्रम(i=0;i<32;i++)
	अणु
		mdelay(4);
		अगर(inw(PORT+L_DATAREG) & (CSR0_IDON | CSR0_MERR) )
			अवरोध; /* init ok ? */
	पूर्ण
पूर्ण

/*
 * allocate memory area and check the 16MB border
 */
अटल व्योम *ni65_alloc_mem(काष्ठा net_device *dev,अक्षर *what,पूर्णांक size,पूर्णांक type)
अणु
	काष्ठा sk_buff *skb=शून्य;
	अचिन्हित अक्षर *ptr;
	व्योम *ret;

	अगर(type) अणु
		ret = skb = alloc_skb(2+16+size,GFP_KERNEL|GFP_DMA);
		अगर(!skb) अणु
			prपूर्णांकk(KERN_WARNING "%s: unable to allocate %s memory.\n",dev->name,what);
			वापस शून्य;
		पूर्ण
		skb_reserve(skb,2+16);
		skb_put(skb,R_BUF_SIZE);	 /* grab the whole space .. (not necessary) */
		ptr = skb->data;
	पूर्ण
	अन्यथा अणु
		ret = ptr = kदो_स्मृति(T_BUF_SIZE,GFP_KERNEL | GFP_DMA);
		अगर(!ret)
			वापस शून्य;
	पूर्ण
	अगर( (u32) virt_to_phys(ptr+size) > 0x1000000) अणु
		prपूर्णांकk(KERN_WARNING "%s: unable to allocate %s memory in lower 16MB!\n",dev->name,what);
		अगर(type)
			kमुक्त_skb(skb);
		अन्यथा
			kमुक्त(ptr);
		वापस शून्य;
	पूर्ण
	वापस ret;
पूर्ण

/*
 * allocate all memory काष्ठाures .. send/recv buffers etc ...
 */
अटल पूर्णांक ni65_alloc_buffer(काष्ठा net_device *dev)
अणु
	अचिन्हित अक्षर *ptr;
	काष्ठा priv *p;
	पूर्णांक i;

	/*
	 * we need 8-aligned memory ..
	 */
	ptr = ni65_alloc_mem(dev,"BUFFER",माप(काष्ठा priv)+8,0);
	अगर(!ptr)
		वापस -ENOMEM;

	p = dev->ml_priv = (काष्ठा priv *) (((अचिन्हित दीर्घ) ptr + 7) & ~0x7);
	स_रखो((अक्षर *)p, 0, माप(काष्ठा priv));
	p->self = ptr;

	क्रम(i=0;i<TMDNUM;i++)
	अणु
#अगर_घोषित XMT_VIA_SKB
		p->पंचांगd_skb[i] = शून्य;
#पूर्ण_अगर
		p->पंचांगdbounce[i] = ni65_alloc_mem(dev,"XMIT",T_BUF_SIZE,0);
		अगर(!p->पंचांगdbounce[i]) अणु
			ni65_मुक्त_buffer(p);
			वापस -ENOMEM;
		पूर्ण
	पूर्ण

	क्रम(i=0;i<RMDNUM;i++)
	अणु
#अगर_घोषित RCV_VIA_SKB
		p->recv_skb[i] = ni65_alloc_mem(dev,"RECV",R_BUF_SIZE,1);
		अगर(!p->recv_skb[i]) अणु
			ni65_मुक्त_buffer(p);
			वापस -ENOMEM;
		पूर्ण
#अन्यथा
		p->recvbounce[i] = ni65_alloc_mem(dev,"RECV",R_BUF_SIZE,0);
		अगर(!p->recvbounce[i]) अणु
			ni65_मुक्त_buffer(p);
			वापस -ENOMEM;
		पूर्ण
#पूर्ण_अगर
	पूर्ण

	वापस 0; /* everything is OK */
पूर्ण

/*
 * मुक्त buffers and निजी काष्ठा
 */
अटल व्योम ni65_मुक्त_buffer(काष्ठा priv *p)
अणु
	पूर्णांक i;

	अगर(!p)
		वापस;

	क्रम(i=0;i<TMDNUM;i++) अणु
		kमुक्त(p->पंचांगdbounce[i]);
#अगर_घोषित XMT_VIA_SKB
		dev_kमुक्त_skb(p->पंचांगd_skb[i]);
#पूर्ण_अगर
	पूर्ण

	क्रम(i=0;i<RMDNUM;i++)
	अणु
#अगर_घोषित RCV_VIA_SKB
		dev_kमुक्त_skb(p->recv_skb[i]);
#अन्यथा
		kमुक्त(p->recvbounce[i]);
#पूर्ण_अगर
	पूर्ण
	kमुक्त(p->self);
पूर्ण


/*
 * stop and (re)start lance .. e.g after an error
 */
अटल व्योम ni65_stop_start(काष्ठा net_device *dev,काष्ठा priv *p)
अणु
	पूर्णांक csr0 = CSR0_INEA;

	ग_लिखोdatareg(CSR0_STOP);

	अगर(debuglevel > 1)
		prपूर्णांकk(KERN_DEBUG "ni65_stop_start\n");

	अगर(p->features & INIT_RING_BEFORE_START) अणु
		पूर्णांक i;
#अगर_घोषित XMT_VIA_SKB
		काष्ठा sk_buff *skb_save[TMDNUM];
#पूर्ण_अगर
		अचिन्हित दीर्घ buffer[TMDNUM];
		लघु blen[TMDNUM];

		अगर(p->xmit_queued) अणु
			जबतक(1) अणु
				अगर((p->पंचांगdhead[p->पंचांगdlast].u.s.status & XMIT_OWN))
					अवरोध;
				p->पंचांगdlast = (p->पंचांगdlast + 1) & (TMDNUM-1);
				अगर(p->पंचांगdlast == p->पंचांगdnum)
					अवरोध;
			पूर्ण
		पूर्ण

		क्रम(i=0;i<TMDNUM;i++) अणु
			काष्ठा पंचांगd *पंचांगdp = p->पंचांगdhead + i;
#अगर_घोषित XMT_VIA_SKB
			skb_save[i] = p->पंचांगd_skb[i];
#पूर्ण_अगर
			buffer[i] = (u32) isa_bus_to_virt(पंचांगdp->u.buffer);
			blen[i] = पंचांगdp->blen;
			पंचांगdp->u.s.status = 0x0;
		पूर्ण

		क्रम(i=0;i<RMDNUM;i++) अणु
			काष्ठा rmd *rmdp = p->rmdhead + i;
			rmdp->u.s.status = RCV_OWN;
		पूर्ण
		p->पंचांगdnum = p->xmit_queued = 0;
		ग_लिखोdatareg(CSR0_STRT | csr0);

		क्रम(i=0;i<TMDNUM;i++) अणु
			पूर्णांक num = (i + p->पंचांगdlast) & (TMDNUM-1);
			p->पंचांगdhead[i].u.buffer = (u32) isa_virt_to_bus((अक्षर *)buffer[num]); /* status is part of buffer field */
			p->पंचांगdhead[i].blen = blen[num];
			अगर(p->पंचांगdhead[i].u.s.status & XMIT_OWN) अणु
				 p->पंचांगdnum = (p->पंचांगdnum + 1) & (TMDNUM-1);
				 p->xmit_queued = 1;
	 ग_लिखोdatareg(CSR0_TDMD | CSR0_INEA | csr0);
			पूर्ण
#अगर_घोषित XMT_VIA_SKB
			p->पंचांगd_skb[i] = skb_save[num];
#पूर्ण_अगर
		पूर्ण
		p->rmdnum = p->पंचांगdlast = 0;
		अगर(!p->lock)
			अगर (p->पंचांगdnum || !p->xmit_queued)
				netअगर_wake_queue(dev);
		netअगर_trans_update(dev); /* prevent tx समयout */
	पूर्ण
	अन्यथा
		ग_लिखोdatareg(CSR0_STRT | csr0);
पूर्ण

/*
 * init lance (ग_लिखो init-values .. init-buffers) (खोलो-helper)
 */
अटल पूर्णांक ni65_lance_reinit(काष्ठा net_device *dev)
अणु
	 पूर्णांक i;
	 काष्ठा priv *p = dev->ml_priv;
	 अचिन्हित दीर्घ flags;

	 p->lock = 0;
	 p->xmit_queued = 0;

	 flags=claim_dma_lock();
	 disable_dma(dev->dma); /* I've never worked with dma, but we करो it like the packetdriver */
	 set_dma_mode(dev->dma,DMA_MODE_CASCADE);
	 enable_dma(dev->dma);
	 release_dma_lock(flags);

	 outw(inw(PORT+L_RESET),PORT+L_RESET); /* first: reset the card */
	 अगर( (i=पढ़ोreg(CSR0) ) != 0x4)
	 अणु
		 prपूर्णांकk(KERN_ERR "%s: can't RESET %s card: %04x\n",dev->name,
							cards[p->cardno].cardname,(पूर्णांक) i);
		 flags=claim_dma_lock();
		 disable_dma(dev->dma);
		 release_dma_lock(flags);
		 वापस 0;
	 पूर्ण

	 p->rmdnum = p->पंचांगdnum = p->पंचांगdlast = p->पंचांगdbouncक्रमागत = 0;
	 क्रम(i=0;i<TMDNUM;i++)
	 अणु
		 काष्ठा पंचांगd *पंचांगdp = p->पंचांगdhead + i;
#अगर_घोषित XMT_VIA_SKB
		 अगर(p->पंचांगd_skb[i]) अणु
			 dev_kमुक्त_skb(p->पंचांगd_skb[i]);
			 p->पंचांगd_skb[i] = शून्य;
		 पूर्ण
#पूर्ण_अगर
		 पंचांगdp->u.buffer = 0x0;
		 पंचांगdp->u.s.status = XMIT_START | XMIT_END;
		 पंचांगdp->blen = पंचांगdp->status2 = 0;
	 पूर्ण

	 क्रम(i=0;i<RMDNUM;i++)
	 अणु
		 काष्ठा rmd *rmdp = p->rmdhead + i;
#अगर_घोषित RCV_VIA_SKB
		 rmdp->u.buffer = (u32) isa_virt_to_bus(p->recv_skb[i]->data);
#अन्यथा
		 rmdp->u.buffer = (u32) isa_virt_to_bus(p->recvbounce[i]);
#पूर्ण_अगर
		 rmdp->blen = -(R_BUF_SIZE-8);
		 rmdp->mlen = 0;
		 rmdp->u.s.status = RCV_OWN;
	 पूर्ण

	 अगर(dev->flags & IFF_PROMISC)
		 ni65_init_lance(p,dev->dev_addr,0x00,M_PROM);
	 अन्यथा अगर (netdev_mc_count(dev) || dev->flags & IFF_ALLMULTI)
		 ni65_init_lance(p,dev->dev_addr,0xff,0x0);
	 अन्यथा
		 ni65_init_lance(p,dev->dev_addr,0x00,0x00);

	/*
	 * ni65_set_lance_mem() sets L_ADDRREG to CSR0
	 * NOW, WE WILL NEVER CHANGE THE L_ADDRREG, CSR0 IS ALWAYS SELECTED
	 */

	 अगर(inw(PORT+L_DATAREG) & CSR0_IDON)	अणु
		 ni65_set_perक्रमmance(p);
					 /* init OK: start lance , enable पूर्णांकerrupts */
		 ग_लिखोdatareg(CSR0_CLRALL | CSR0_INEA | CSR0_STRT);
		 वापस 1; /* ->OK */
	 पूर्ण
	 prपूर्णांकk(KERN_ERR "%s: can't init lance, status: %04x\n",dev->name,(पूर्णांक) inw(PORT+L_DATAREG));
	 flags=claim_dma_lock();
	 disable_dma(dev->dma);
	 release_dma_lock(flags);
	 वापस 0; /* ->Error */
पूर्ण

/*
 * पूर्णांकerrupt handler
 */
अटल irqवापस_t ni65_पूर्णांकerrupt(पूर्णांक irq, व्योम * dev_id)
अणु
	पूर्णांक csr0 = 0;
	काष्ठा net_device *dev = dev_id;
	काष्ठा priv *p;
	पूर्णांक bcnt = 32;

	p = dev->ml_priv;

	spin_lock(&p->ring_lock);

	जबतक(--bcnt) अणु
		csr0 = inw(PORT+L_DATAREG);

#अगर 0
		ग_लिखोdatareg( (csr0 & CSR0_CLRALL) ); /* ack पूर्णांकerrupts, disable पूर्णांक. */
#अन्यथा
		ग_लिखोdatareg( (csr0 & CSR0_CLRALL) | CSR0_INEA ); /* ack पूर्णांकerrupts, पूर्णांकerrupts enabled */
#पूर्ण_अगर

		अगर(!(csr0 & (CSR0_ERR | CSR0_RINT | CSR0_TINT)))
			अवरोध;

		अगर(csr0 & CSR0_RINT) /* RECV-पूर्णांक? */
			ni65_recv_पूर्णांकr(dev,csr0);
		अगर(csr0 & CSR0_TINT) /* XMIT-पूर्णांक? */
			ni65_xmit_पूर्णांकr(dev,csr0);

		अगर(csr0 & CSR0_ERR)
		अणु
			अगर(debuglevel > 1)
				prपूर्णांकk(KERN_ERR "%s: general error: %04x.\n",dev->name,csr0);
			अगर(csr0 & CSR0_BABL)
				dev->stats.tx_errors++;
			अगर(csr0 & CSR0_MISS) अणु
				पूर्णांक i;
				क्रम(i=0;i<RMDNUM;i++)
					prपूर्णांकk("%02x ",p->rmdhead[i].u.s.status);
				prपूर्णांकk("\n");
				dev->stats.rx_errors++;
			पूर्ण
			अगर(csr0 & CSR0_MERR) अणु
				अगर(debuglevel > 1)
					prपूर्णांकk(KERN_ERR "%s: Ooops .. memory error: %04x.\n",dev->name,csr0);
				ni65_stop_start(dev,p);
			पूर्ण
		पूर्ण
	पूर्ण

#अगर_घोषित RCV_PARANOIA_CHECK
अणु
 पूर्णांक j;
 क्रम(j=0;j<RMDNUM;j++)
 अणु
	पूर्णांक i, num2;
	क्रम(i=RMDNUM-1;i>0;i--) अणु
		 num2 = (p->rmdnum + i) & (RMDNUM-1);
		 अगर(!(p->rmdhead[num2].u.s.status & RCV_OWN))
				अवरोध;
	पूर्ण

	अगर(i) अणु
		पूर्णांक k, num1;
		क्रम(k=0;k<RMDNUM;k++) अणु
			num1 = (p->rmdnum + k) & (RMDNUM-1);
			अगर(!(p->rmdhead[num1].u.s.status & RCV_OWN))
				अवरोध;
		पूर्ण
		अगर(!k)
			अवरोध;

		अगर(debuglevel > 0)
		अणु
			अक्षर buf[256],*buf1;
			buf1 = buf;
			क्रम(k=0;k<RMDNUM;k++) अणु
				प्र_लिखो(buf1,"%02x ",(p->rmdhead[k].u.s.status)); /* & RCV_OWN) ); */
				buf1 += 3;
			पूर्ण
			*buf1 = 0;
			prपूर्णांकk(KERN_ERR "%s: Ooops, receive ring corrupted %2d %2d | %s\n",dev->name,p->rmdnum,i,buf);
		पूर्ण

		p->rmdnum = num1;
		ni65_recv_पूर्णांकr(dev,csr0);
		अगर((p->rmdhead[num2].u.s.status & RCV_OWN))
			अवरोध;	/* ok, we are 'in sync' again */
	पूर्ण
	अन्यथा
		अवरोध;
 पूर्ण
पूर्ण
#पूर्ण_अगर

	अगर( (csr0 & (CSR0_RXON | CSR0_TXON)) != (CSR0_RXON | CSR0_TXON) ) अणु
		prपूर्णांकk(KERN_DEBUG "%s: RX or TX was offline -> restart\n",dev->name);
		ni65_stop_start(dev,p);
	पूर्ण
	अन्यथा
		ग_लिखोdatareg(CSR0_INEA);

	spin_unlock(&p->ring_lock);
	वापस IRQ_HANDLED;
पूर्ण

/*
 * We have received an Xmit-Interrupt ..
 * send a new packet अगर necessary
 */
अटल व्योम ni65_xmit_पूर्णांकr(काष्ठा net_device *dev,पूर्णांक csr0)
अणु
	काष्ठा priv *p = dev->ml_priv;

	जबतक(p->xmit_queued)
	अणु
		काष्ठा पंचांगd *पंचांगdp = p->पंचांगdhead + p->पंचांगdlast;
		पूर्णांक पंचांगdstat = पंचांगdp->u.s.status;

		अगर(पंचांगdstat & XMIT_OWN)
			अवरोध;

		अगर(पंचांगdstat & XMIT_ERR)
		अणु
#अगर 0
			अगर(पंचांगdp->status2 & XMIT_TDRMASK && debuglevel > 3)
				prपूर्णांकk(KERN_ERR "%s: tdr-problems (e.g. no resistor)\n",dev->name);
#पूर्ण_अगर
		 /* checking some errors */
			अगर(पंचांगdp->status2 & XMIT_RTRY)
				dev->stats.tx_पातed_errors++;
			अगर(पंचांगdp->status2 & XMIT_LCAR)
				dev->stats.tx_carrier_errors++;
			अगर(पंचांगdp->status2 & (XMIT_BUFF | XMIT_UFLO )) अणु
		/* this stops the xmitter */
				dev->stats.tx_fअगरo_errors++;
				अगर(debuglevel > 0)
					prपूर्णांकk(KERN_ERR "%s: Xmit FIFO/BUFF error\n",dev->name);
				अगर(p->features & INIT_RING_BEFORE_START) अणु
					पंचांगdp->u.s.status = XMIT_OWN | XMIT_START | XMIT_END;	/* test: resend this frame */
					ni65_stop_start(dev,p);
					अवरोध;	/* no more Xmit processing .. */
				पूर्ण
				अन्यथा
				 ni65_stop_start(dev,p);
			पूर्ण
			अगर(debuglevel > 2)
				prपूर्णांकk(KERN_ERR "%s: xmit-error: %04x %02x-%04x\n",dev->name,csr0,(पूर्णांक) पंचांगdstat,(पूर्णांक) पंचांगdp->status2);
			अगर(!(csr0 & CSR0_BABL)) /* करोn't count errors twice */
				dev->stats.tx_errors++;
			पंचांगdp->status2 = 0;
		पूर्ण
		अन्यथा अणु
			dev->stats.tx_bytes -= (लघु)(पंचांगdp->blen);
			dev->stats.tx_packets++;
		पूर्ण

#अगर_घोषित XMT_VIA_SKB
		अगर(p->पंचांगd_skb[p->पंचांगdlast]) अणु
			 dev_consume_skb_irq(p->पंचांगd_skb[p->पंचांगdlast]);
			 p->पंचांगd_skb[p->पंचांगdlast] = शून्य;
		पूर्ण
#पूर्ण_अगर

		p->पंचांगdlast = (p->पंचांगdlast + 1) & (TMDNUM-1);
		अगर(p->पंचांगdlast == p->पंचांगdnum)
			p->xmit_queued = 0;
	पूर्ण
	netअगर_wake_queue(dev);
पूर्ण

/*
 * We have received a packet
 */
अटल व्योम ni65_recv_पूर्णांकr(काष्ठा net_device *dev,पूर्णांक csr0)
अणु
	काष्ठा rmd *rmdp;
	पूर्णांक rmdstat,len;
	पूर्णांक cnt=0;
	काष्ठा priv *p = dev->ml_priv;

	rmdp = p->rmdhead + p->rmdnum;
	जबतक(!( (rmdstat = rmdp->u.s.status) & RCV_OWN))
	अणु
		cnt++;
		अगर( (rmdstat & (RCV_START | RCV_END | RCV_ERR)) != (RCV_START | RCV_END) ) /* error or oversized? */
		अणु
			अगर(!(rmdstat & RCV_ERR)) अणु
				अगर(rmdstat & RCV_START)
				अणु
					dev->stats.rx_length_errors++;
					prपूर्णांकk(KERN_ERR "%s: recv, packet too long: %d\n",dev->name,rmdp->mlen & 0x0fff);
				पूर्ण
			पूर्ण
			अन्यथा अणु
				अगर(debuglevel > 2)
					prपूर्णांकk(KERN_ERR "%s: receive-error: %04x, lance-status: %04x/%04x\n",
									dev->name,(पूर्णांक) rmdstat,csr0,(पूर्णांक) inw(PORT+L_DATAREG) );
				अगर(rmdstat & RCV_FRAM)
					dev->stats.rx_frame_errors++;
				अगर(rmdstat & RCV_OFLO)
					dev->stats.rx_over_errors++;
				अगर(rmdstat & RCV_CRC)
					dev->stats.rx_crc_errors++;
				अगर(rmdstat & RCV_BUF_ERR)
					dev->stats.rx_fअगरo_errors++;
			पूर्ण
			अगर(!(csr0 & CSR0_MISS)) /* करोn't count errors twice */
				dev->stats.rx_errors++;
		पूर्ण
		अन्यथा अगर( (len = (rmdp->mlen & 0x0fff) - 4) >= 60)
		अणु
#अगर_घोषित RCV_VIA_SKB
			काष्ठा sk_buff *skb = alloc_skb(R_BUF_SIZE+2+16,GFP_ATOMIC);
			अगर (skb)
				skb_reserve(skb,16);
#अन्यथा
			काष्ठा sk_buff *skb = netdev_alloc_skb(dev, len + 2);
#पूर्ण_अगर
			अगर(skb)
			अणु
				skb_reserve(skb,2);
#अगर_घोषित RCV_VIA_SKB
				अगर( (अचिन्हित दीर्घ) (skb->data + R_BUF_SIZE) > 0x1000000) अणु
					skb_put(skb,len);
					skb_copy_to_linear_data(skb, (अचिन्हित अक्षर *)(p->recv_skb[p->rmdnum]->data),len);
				पूर्ण
				अन्यथा अणु
					काष्ठा sk_buff *skb1 = p->recv_skb[p->rmdnum];
					skb_put(skb,R_BUF_SIZE);
					p->recv_skb[p->rmdnum] = skb;
					rmdp->u.buffer = (u32) isa_virt_to_bus(skb->data);
					skb = skb1;
					skb_trim(skb,len);
				पूर्ण
#अन्यथा
				skb_put(skb,len);
				skb_copy_to_linear_data(skb, (अचिन्हित अक्षर *) p->recvbounce[p->rmdnum],len);
#पूर्ण_अगर
				dev->stats.rx_packets++;
				dev->stats.rx_bytes += len;
				skb->protocol=eth_type_trans(skb,dev);
				netअगर_rx(skb);
			पूर्ण
			अन्यथा
			अणु
				prपूर्णांकk(KERN_ERR "%s: can't alloc new sk_buff\n",dev->name);
				dev->stats.rx_dropped++;
			पूर्ण
		पूर्ण
		अन्यथा अणु
			prपूर्णांकk(KERN_INFO "%s: received runt packet\n",dev->name);
			dev->stats.rx_errors++;
		पूर्ण
		rmdp->blen = -(R_BUF_SIZE-8);
		rmdp->mlen = 0;
		rmdp->u.s.status = RCV_OWN; /* change owner */
		p->rmdnum = (p->rmdnum + 1) & (RMDNUM-1);
		rmdp = p->rmdhead + p->rmdnum;
	पूर्ण
पूर्ण

/*
 * kick xmitter ..
 */

अटल व्योम ni65_समयout(काष्ठा net_device *dev, अचिन्हित पूर्णांक txqueue)
अणु
	पूर्णांक i;
	काष्ठा priv *p = dev->ml_priv;

	prपूर्णांकk(KERN_ERR "%s: xmitter timed out, try to restart!\n",dev->name);
	क्रम(i=0;i<TMDNUM;i++)
		prपूर्णांकk("%02x ",p->पंचांगdhead[i].u.s.status);
	prपूर्णांकk("\n");
	ni65_lance_reinit(dev);
	netअगर_trans_update(dev); /* prevent tx समयout */
	netअगर_wake_queue(dev);
पूर्ण

/*
 *	Send a packet
 */

अटल netdev_tx_t ni65_send_packet(काष्ठा sk_buff *skb,
				    काष्ठा net_device *dev)
अणु
	काष्ठा priv *p = dev->ml_priv;

	netअगर_stop_queue(dev);

	अगर (test_and_set_bit(0, (व्योम*)&p->lock)) अणु
		prपूर्णांकk(KERN_ERR "%s: Queue was locked.\n", dev->name);
		वापस NETDEV_TX_BUSY;
	पूर्ण

	अणु
		लघु len = ETH_ZLEN < skb->len ? skb->len : ETH_ZLEN;
		काष्ठा पंचांगd *पंचांगdp;
		अचिन्हित दीर्घ flags;

#अगर_घोषित XMT_VIA_SKB
		अगर( (अचिन्हित दीर्घ) (skb->data + skb->len) > 0x1000000) अणु
#पूर्ण_अगर

			skb_copy_from_linear_data(skb, p->पंचांगdbounce[p->पंचांगdbouncक्रमागत],
				      skb->len > T_BUF_SIZE ? T_BUF_SIZE :
							      skb->len);
			अगर (len > skb->len)
				स_रखो((अक्षर *)p->पंचांगdbounce[p->पंचांगdbouncक्रमागत]+skb->len, 0, len-skb->len);
			dev_kमुक्त_skb (skb);

			spin_lock_irqsave(&p->ring_lock, flags);
			पंचांगdp = p->पंचांगdhead + p->पंचांगdnum;
			पंचांगdp->u.buffer = (u32) isa_virt_to_bus(p->पंचांगdbounce[p->पंचांगdbouncक्रमागत]);
			p->पंचांगdbouncक्रमागत = (p->पंचांगdbouncक्रमागत + 1) & (TMDNUM - 1);

#अगर_घोषित XMT_VIA_SKB
		पूर्ण
		अन्यथा अणु
			spin_lock_irqsave(&p->ring_lock, flags);

			पंचांगdp = p->पंचांगdhead + p->पंचांगdnum;
			पंचांगdp->u.buffer = (u32) isa_virt_to_bus(skb->data);
			p->पंचांगd_skb[p->पंचांगdnum] = skb;
		पूर्ण
#पूर्ण_अगर
		पंचांगdp->blen = -len;

		पंचांगdp->u.s.status = XMIT_OWN | XMIT_START | XMIT_END;
		ग_लिखोdatareg(CSR0_TDMD | CSR0_INEA); /* enable xmit & पूर्णांकerrupt */

		p->xmit_queued = 1;
		p->पंचांगdnum = (p->पंचांगdnum + 1) & (TMDNUM-1);

		अगर(p->पंचांगdnum != p->पंचांगdlast)
			netअगर_wake_queue(dev);

		p->lock = 0;

		spin_unlock_irqrestore(&p->ring_lock, flags);
	पूर्ण

	वापस NETDEV_TX_OK;
पूर्ण

अटल व्योम set_multicast_list(काष्ठा net_device *dev)
अणु
	अगर(!ni65_lance_reinit(dev))
		prपूर्णांकk(KERN_ERR "%s: Can't switch card into MC mode!\n",dev->name);
	netअगर_wake_queue(dev);
पूर्ण

#अगर_घोषित MODULE
अटल काष्ठा net_device *dev_ni65;

module_param_hw(irq, पूर्णांक, irq, 0);
module_param_hw(io, पूर्णांक, ioport, 0);
module_param_hw(dma, पूर्णांक, dma, 0);
MODULE_PARM_DESC(irq, "ni6510 IRQ number (ignored for some cards)");
MODULE_PARM_DESC(io, "ni6510 I/O base address");
MODULE_PARM_DESC(dma, "ni6510 ISA DMA channel (ignored for some cards)");

पूर्णांक __init init_module(व्योम)
अणु
 	dev_ni65 = ni65_probe(-1);
	वापस PTR_ERR_OR_ZERO(dev_ni65);
पूर्ण

व्योम __निकास cleanup_module(व्योम)
अणु
 	unरेजिस्टर_netdev(dev_ni65);
 	cleanup_card(dev_ni65);
 	मुक्त_netdev(dev_ni65);
पूर्ण
#पूर्ण_अगर /* MODULE */

MODULE_LICENSE("GPL");
