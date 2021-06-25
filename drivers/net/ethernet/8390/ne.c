<शैली गुरु>
/* ne.c: A general non-shared-memory NS8390 ethernet driver क्रम linux. */
/*
    Written 1992-94 by Donald Becker.

    Copyright 1993 United States Government as represented by the
    Director, National Security Agency.

    This software may be used and distributed according to the terms
    of the GNU General Public License, incorporated herein by reference.

    The author may be reached as becker@scyld.com, or C/O
    Scyld Computing Corporation, 410 Severn Ave., Suite 210, Annapolis MD 21403

    This driver should work with many programmed-I/O 8390-based ethernet
    boards.  Currently it supports the NE1000, NE2000, many clones,
    and some Cabletron products.

    Changelog:

    Paul Gorपंचांगaker	: use ENISR_RDC to monitor Tx PIO uploads, made
			  sanity checks and bad clone support optional.
    Paul Gorपंचांगaker	: new reset code, reset card after probe at boot.
    Paul Gorपंचांगaker	: multiple card support क्रम module users.
    Paul Gorपंचांगaker	: Support क्रम PCI ne2k clones, similar to lance.c
    Paul Gorपंचांगaker	: Allow users with bad cards to aव्योम full probe.
    Paul Gorपंचांगaker	: PCI probe changes, more PCI cards supported.
    rjohnson@analogic.com : Changed init order so an पूर्णांकerrupt will only
    occur after memory is allocated क्रम dev->priv. Deallocated memory
    last in cleanup_modue()
    Riअक्षरd Guenther    : Added support क्रम ISAPnP cards
    Paul Gorपंचांगaker	: Disजारीd PCI support - use ne2k-pci.c instead.
    Hayato Fujiwara	: Add m32r support.

*/

/* Routines क्रम the NatSemi-based designs (NE[12]000). */

अटल स्थिर अक्षर version1[] =
"ne.c:v1.10 9/23/94 Donald Becker (becker@scyld.com)\n";
अटल स्थिर अक्षर version2[] =
"Last modified Nov 1, 2000 by Paul Gortmaker\n";


#समावेश <linux/module.h>
#समावेश <linux/kernel.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/isapnp.h>
#समावेश <linux/init.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/delay.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/etherdevice.h>
#समावेश <linux/jअगरfies.h>
#समावेश <linux/platक्रमm_device.h>

#समावेश <यंत्र/पन.स>

#समावेश "8390.h"

#घोषणा DRV_NAME "ne"

/* Some defines that people can play with अगर so inclined. */

/* Do we support clones that करोn't adhere to 14,15 of the SAprom ? */
#घोषणा SUPPORT_NE_BAD_CLONES
/* 0xbad = bad sig or no reset ack */
#घोषणा BAD 0xbad

#घोषणा MAX_NE_CARDS	4	/* Max number of NE cards per module */
अटल काष्ठा platक्रमm_device *pdev_ne[MAX_NE_CARDS];
अटल पूर्णांक io[MAX_NE_CARDS];
अटल पूर्णांक irq[MAX_NE_CARDS];
अटल पूर्णांक bad[MAX_NE_CARDS];
अटल u32 ne_msg_enable;

#अगर_घोषित MODULE
module_param_hw_array(io, पूर्णांक, ioport, शून्य, 0);
module_param_hw_array(irq, पूर्णांक, irq, शून्य, 0);
module_param_array(bad, पूर्णांक, शून्य, 0);
module_param_named(msg_enable, ne_msg_enable, uपूर्णांक, 0444);
MODULE_PARM_DESC(io, "I/O base address(es),required");
MODULE_PARM_DESC(irq, "IRQ number(s)");
MODULE_PARM_DESC(bad, "Accept card(s) with bad signatures");
MODULE_PARM_DESC(msg_enable, "Debug message level (see linux/netdevice.h for bitmap)");
MODULE_DESCRIPTION("NE1000/NE2000 ISA/PnP Ethernet driver");
MODULE_LICENSE("GPL");
#पूर्ण_अगर /* MODULE */

/* Do we perक्रमm extra sanity checks on stuff ? */
/* #घोषणा NE_SANITY_CHECK */

/* Do we implement the पढ़ो beक्रमe ग_लिखो bugfix ? */
/* #घोषणा NE_RW_BUGFIX */

/* Do we have a non std. amount of memory? (in units of 256 byte pages) */
/* #घोषणा PACKETBUF_MEMSIZE	0x40 */

/* This is set up so that no ISA स्वतःprobe takes place. We can't guarantee
that the ne2k probe is the last 8390 based probe to take place (as it
is at boot) and so the probe will get confused by any other 8390 cards.
ISA device स्वतःprobes on a running machine are not recommended anyway. */
#अगर !defined(MODULE) && defined(CONFIG_ISA)
/* Do we need a portlist क्रम the ISA स्वतः-probe ? */
#घोषणा NEEDS_PORTLIST
#पूर्ण_अगर

/* A zero-terminated list of I/O addresses to be probed at boot. */
#अगर_घोषित NEEDS_PORTLIST
अटल अचिन्हित पूर्णांक netcard_portlist[] __initdata = अणु
	0x300, 0x280, 0x320, 0x340, 0x360, 0x380, 0
पूर्ण;
#पूर्ण_अगर

अटल काष्ठा isapnp_device_id isapnp_clone_list[] __initdata = अणु
	अणु	ISAPNP_CARD_ID('A','X','E',0x2011),
		ISAPNP_VENDOR('A','X','E'), ISAPNP_FUNCTION(0x2011),
		(दीर्घ) "NetGear EA201" पूर्ण,
	अणु	ISAPNP_ANY_ID, ISAPNP_ANY_ID,
		ISAPNP_VENDOR('E','D','I'), ISAPNP_FUNCTION(0x0216),
		(दीर्घ) "NN NE2000" पूर्ण,
	अणु	ISAPNP_ANY_ID, ISAPNP_ANY_ID,
		ISAPNP_VENDOR('P','N','P'), ISAPNP_FUNCTION(0x80d6),
		(दीर्घ) "Generic PNP" पूर्ण,
	अणु पूर्ण	/* terminate list */
पूर्ण;

MODULE_DEVICE_TABLE(isapnp, isapnp_clone_list);

#अगर_घोषित SUPPORT_NE_BAD_CLONES
/* A list of bad clones that we none-the-less recognize. */
अटल काष्ठा अणु स्थिर अक्षर *name8, *name16; अचिन्हित अक्षर SAprefix[4];पूर्ण
bad_clone_list[] __initdata = अणु
    अणु"DE100", "DE200", अणु0x00, 0xDE, 0x01,पूर्णपूर्ण,
    अणु"DE120", "DE220", अणु0x00, 0x80, 0xc8,पूर्णपूर्ण,
    अणु"DFI1000", "DFI2000", अणु'D', 'F', 'I',पूर्णपूर्ण, /* Original, eh?  */
    अणु"EtherNext UTP8", "EtherNext UTP16", अणु0x00, 0x00, 0x79पूर्णपूर्ण,
    अणु"NE1000","NE2000-invalid", अणु0x00, 0x00, 0xd8पूर्णपूर्ण, /* Ancient real NE1000. */
    अणु"NN1000", "NN2000",  अणु0x08, 0x03, 0x08पूर्णपूर्ण, /* Outlaw no-name clone. */
    अणु"4-DIM8","4-DIM16", अणु0x00,0x00,0x4d,पूर्णपूर्ण,  /* Outlaw 4-Dimension cards. */
    अणु"Con-Intl_8", "Con-Intl_16", अणु0x00, 0x00, 0x24पूर्णपूर्ण, /* Connect Int'nl */
    अणु"ET-100","ET-200", अणु0x00, 0x45, 0x54पूर्णपूर्ण, /* YANG and YA clone */
    अणु"COMPEX","COMPEX16",अणु0x00,0x80,0x48पूर्णपूर्ण, /* Broken ISA Compex cards */
    अणु"E-LAN100", "E-LAN200", अणु0x00, 0x00, 0x5dपूर्णपूर्ण, /* Broken ne1000 clones */
    अणु"PCM-4823", "PCM-4823", अणु0x00, 0xc0, 0x6cपूर्णपूर्ण, /* Broken Advantech MoBo */
    अणु"REALTEK", "RTL8019", अणु0x00, 0x00, 0xe8पूर्णपूर्ण, /* no-name with Realtek chip */
#अगर_घोषित CONFIG_MACH_TX49XX
    अणु"RBHMA4X00-RTL8019", "RBHMA4X00-RTL8019", अणु0x00, 0x60, 0x0aपूर्णपूर्ण,  /* Toshiba built-in */
#पूर्ण_अगर
    अणु"LCS-8834", "LCS-8836", अणु0x04, 0x04, 0x37पूर्णपूर्ण, /* ShinyNet (SET) */
    अणुशून्य,पूर्ण
पूर्ण;
#पूर्ण_अगर

/* ---- No user-serviceable parts below ---- */

#घोषणा NE_BASE	 (dev->base_addr)
#घोषणा NE_CMD	 	0x00
#घोषणा NE_DATAPORT	0x10	/* NatSemi-defined port winकरोw offset. */
#घोषणा NE_RESET	0x1f	/* Issue a पढ़ो to reset, a ग_लिखो to clear. */
#घोषणा NE_IO_EXTENT	0x20

#घोषणा NE1SM_START_PG	0x20	/* First page of TX buffer */
#घोषणा NE1SM_STOP_PG 	0x40	/* Last page +1 of RX ring */
#घोषणा NESM_START_PG	0x40	/* First page of TX buffer */
#घोषणा NESM_STOP_PG	0x80	/* Last page +1 of RX ring */

#अगर defined(CONFIG_MACH_TX49XX)
#  define DCR_VAL 0x48		/* 8-bit mode */
#या_अगर defined(CONFIG_ATARI)	/* 8-bit mode on Atari, normal on Q40 */
#  define DCR_VAL (MACH_IS_ATARI ? 0x48 : 0x49)
#अन्यथा
#  define DCR_VAL 0x49
#पूर्ण_अगर

अटल पूर्णांक ne_probe1(काष्ठा net_device *dev, अचिन्हित दीर्घ ioaddr);
अटल पूर्णांक ne_probe_isapnp(काष्ठा net_device *dev);

अटल व्योम ne_reset_8390(काष्ठा net_device *dev);
अटल व्योम ne_get_8390_hdr(काष्ठा net_device *dev, काष्ठा e8390_pkt_hdr *hdr,
			  पूर्णांक ring_page);
अटल व्योम ne_block_input(काष्ठा net_device *dev, पूर्णांक count,
			  काष्ठा sk_buff *skb, पूर्णांक ring_offset);
अटल व्योम ne_block_output(काष्ठा net_device *dev, स्थिर पूर्णांक count,
		स्थिर अचिन्हित अक्षर *buf, स्थिर पूर्णांक start_page);


/*  Probe क्रम various non-shared-memory ethercards.

   NEx000-clone boards have a Station Address PROM (SAPROM) in the packet
   buffer memory space.  NE2000 clones have 0x57,0x57 in bytes 0x0e,0x0f of
   the SAPROM, जबतक other supposed NE2000 clones must be detected by their
   SA prefix.

   Reading the SAPROM from a word-wide card with the 8390 set in byte-wide
   mode results in द्विगुनd values, which can be detected and compensated क्रम.

   The probe is also responsible क्रम initializing the card and filling
   in the 'dev' and 'ei_status' काष्ठाures.

   We use the minimum memory size क्रम some ethercard product lines, अगरf we can't
   distinguish models.  You can increase the packet buffer size by setting
   PACKETBUF_MEMSIZE.  Reported Cabletron packet buffer locations are:
	E1010   starts at 0x100 and ends at 0x2000.
	E1010-x starts at 0x100 and ends at 0x8000. ("-x" means "more memory")
	E2010	 starts at 0x100 and ends at 0x4000.
	E2010-x starts at 0x100 and ends at 0xffff.  */

अटल पूर्णांक __init करो_ne_probe(काष्ठा net_device *dev)
अणु
	अचिन्हित दीर्घ base_addr = dev->base_addr;
#अगर_घोषित NEEDS_PORTLIST
	पूर्णांक orig_irq = dev->irq;
#पूर्ण_अगर

	/* First check any supplied i/o locations. User knows best. <cough> */
	अगर (base_addr > 0x1ff) अणु	/* Check a single specअगरied location. */
		पूर्णांक ret = ne_probe1(dev, base_addr);
		अगर (ret)
			netdev_warn(dev, "ne.c: No NE*000 card found at "
				    "i/o = %#lx\n", base_addr);
		वापस ret;
	पूर्ण
	अन्यथा अगर (base_addr != 0)	/* Don't probe at all. */
		वापस -ENXIO;

	/* Then look क्रम any installed ISAPnP clones */
	अगर (isapnp_present() && (ne_probe_isapnp(dev) == 0))
		वापस 0;

#अगर_घोषित NEEDS_PORTLIST
	/* Last resort. The semi-risky ISA स्वतः-probe. */
	क्रम (base_addr = 0; netcard_portlist[base_addr] != 0; base_addr++) अणु
		पूर्णांक ioaddr = netcard_portlist[base_addr];
		dev->irq = orig_irq;
		अगर (ne_probe1(dev, ioaddr) == 0)
			वापस 0;
	पूर्ण
#पूर्ण_अगर

	वापस -ENODEV;
पूर्ण

अटल पूर्णांक __init ne_probe_isapnp(काष्ठा net_device *dev)
अणु
	पूर्णांक i;

	क्रम (i = 0; isapnp_clone_list[i].venकरोr != 0; i++) अणु
		काष्ठा pnp_dev *idev = शून्य;

		जबतक ((idev = pnp_find_dev(शून्य,
					    isapnp_clone_list[i].venकरोr,
					    isapnp_clone_list[i].function,
					    idev))) अणु
			/* Aव्योम alपढ़ोy found cards from previous calls */
			अगर (pnp_device_attach(idev) < 0)
				जारी;
			अगर (pnp_activate_dev(idev) < 0) अणु
			      	pnp_device_detach(idev);
			      	जारी;
			पूर्ण
			/* अगर no io and irq, search क्रम next */
			अगर (!pnp_port_valid(idev, 0) || !pnp_irq_valid(idev, 0)) अणु
				pnp_device_detach(idev);
				जारी;
			पूर्ण
			/* found it */
			dev->base_addr = pnp_port_start(idev, 0);
			dev->irq = pnp_irq(idev, 0);
			netdev_info(dev,
				    "ne.c: ISAPnP reports %s at i/o %#lx, irq %d.\n",
				    (अक्षर *) isapnp_clone_list[i].driver_data,
				    dev->base_addr, dev->irq);
			अगर (ne_probe1(dev, dev->base_addr) != 0) अणु	/* Shouldn't happen. */
				netdev_err(dev,
					   "ne.c: Probe of ISAPnP card at %#lx failed.\n",
					   dev->base_addr);
				pnp_device_detach(idev);
				वापस -ENXIO;
			पूर्ण
			ei_status.priv = (अचिन्हित दीर्घ)idev;
			अवरोध;
		पूर्ण
		अगर (!idev)
			जारी;
		वापस 0;
	पूर्ण

	वापस -ENODEV;
पूर्ण

अटल पूर्णांक __init ne_probe1(काष्ठा net_device *dev, अचिन्हित दीर्घ ioaddr)
अणु
	पूर्णांक i;
	अचिन्हित अक्षर SA_prom[32];
	पूर्णांक wordlength = 2;
	स्थिर अक्षर *name = शून्य;
	पूर्णांक start_page, stop_page;
	पूर्णांक neX000, ctron, copam, bad_card;
	पूर्णांक reg0, ret;
	अटल अचिन्हित version_prपूर्णांकed;
	काष्ठा ei_device *ei_local = netdev_priv(dev);

	अगर (!request_region(ioaddr, NE_IO_EXTENT, DRV_NAME))
		वापस -EBUSY;

	reg0 = inb_p(ioaddr);
	अगर (reg0 == 0xFF) अणु
		ret = -ENODEV;
		जाओ err_out;
	पूर्ण

	/* Do a preliminary verअगरication that we have a 8390. */
	अणु
		पूर्णांक regd;
		outb_p(E8390_NODMA+E8390_PAGE1+E8390_STOP, ioaddr + E8390_CMD);
		regd = inb_p(ioaddr + 0x0d);
		outb_p(0xff, ioaddr + 0x0d);
		outb_p(E8390_NODMA+E8390_PAGE0, ioaddr + E8390_CMD);
		inb_p(ioaddr + EN0_COUNTER0); /* Clear the counter by पढ़ोing. */
		अगर (inb_p(ioaddr + EN0_COUNTER0) != 0) अणु
			outb_p(reg0, ioaddr);
			outb_p(regd, ioaddr + 0x0d);	/* Restore the old values. */
			ret = -ENODEV;
			जाओ err_out;
		पूर्ण
	पूर्ण

	अगर ((ne_msg_enable & NETIF_MSG_DRV) && (version_prपूर्णांकed++ == 0))
		netdev_info(dev, "%s%s", version1, version2);

	netdev_info(dev, "NE*000 ethercard probe at %#3lx:", ioaddr);

	/* A user with a poor card that fails to ack the reset, or that
	   करोes not have a valid 0x57,0x57 signature can still use this
	   without having to recompile. Specअगरying an i/o address aदीर्घ
	   with an otherwise unused dev->mem_end value of "0xBAD" will
	   cause the driver to skip these parts of the probe. */

	bad_card = ((dev->base_addr != 0) && (dev->mem_end == BAD));

	/* Reset card. Who knows what dain-bramaged state it was left in. */

	अणु
		अचिन्हित दीर्घ reset_start_समय = jअगरfies;

		/* DON'T change these to inb_p/outb_p or reset will fail on clones. */
		outb(inb(ioaddr + NE_RESET), ioaddr + NE_RESET);

		जबतक ((inb_p(ioaddr + EN0_ISR) & ENISR_RESET) == 0)
		अगर (समय_after(jअगरfies, reset_start_समय + 2*HZ/100)) अणु
			अगर (bad_card) अणु
				pr_cont(" (warning: no reset ack)");
				अवरोध;
			पूर्ण अन्यथा अणु
				pr_cont(" not found (no reset ack).\n");
				ret = -ENODEV;
				जाओ err_out;
			पूर्ण
		पूर्ण

		outb_p(0xff, ioaddr + EN0_ISR);		/* Ack all पूर्णांकr. */
	पूर्ण

	/* Read the 16 bytes of station address PROM.
	   We must first initialize रेजिस्टरs, similar to NS8390p_init(eअगरdev, 0).
	   We can't reliably पढ़ो the SAPROM address without this.
	   (I learned the hard way!). */
	अणु
		काष्ठा अणुअचिन्हित अक्षर value, offset; पूर्ण program_seq[] =
		अणु
			अणुE8390_NODMA+E8390_PAGE0+E8390_STOP, E8390_CMDपूर्ण, /* Select page 0*/
			अणु0x48,	EN0_DCFGपूर्ण,	/* Set byte-wide (0x48) access. */
			अणु0x00,	EN0_RCNTLOपूर्ण,	/* Clear the count regs. */
			अणु0x00,	EN0_RCNTHIपूर्ण,
			अणु0x00,	EN0_IMRपूर्ण,	/* Mask completion irq. */
			अणु0xFF,	EN0_ISRपूर्ण,
			अणुE8390_RXOFF, EN0_RXCRपूर्ण,	/* 0x20  Set to monitor */
			अणुE8390_TXOFF, EN0_TXCRपूर्ण,	/* 0x02  and loopback mode. */
			अणु32,	EN0_RCNTLOपूर्ण,
			अणु0x00,	EN0_RCNTHIपूर्ण,
			अणु0x00,	EN0_RSARLOपूर्ण,	/* DMA starting at 0x0000. */
			अणु0x00,	EN0_RSARHIपूर्ण,
			अणुE8390_RREAD+E8390_START, E8390_CMDपूर्ण,
		पूर्ण;

		क्रम (i = 0; i < ARRAY_SIZE(program_seq); i++)
			outb_p(program_seq[i].value, ioaddr + program_seq[i].offset);

	पूर्ण
	क्रम(i = 0; i < 32 /*माप(SA_prom)*/; i+=2) अणु
		SA_prom[i] = inb(ioaddr + NE_DATAPORT);
		SA_prom[i+1] = inb(ioaddr + NE_DATAPORT);
		अगर (SA_prom[i] != SA_prom[i+1])
			wordlength = 1;
	पूर्ण

	अगर (wordlength == 2)
	अणु
		क्रम (i = 0; i < 16; i++)
			SA_prom[i] = SA_prom[i+i];
		/* We must set the 8390 क्रम word mode. */
		outb_p(DCR_VAL, ioaddr + EN0_DCFG);
		start_page = NESM_START_PG;

		/*
		 * Realtek RTL8019AS datasheet says that the PSTOP रेजिस्टर
		 * shouldn't exceed 0x60 in 8-bit mode.
		 * This chip can be identअगरied by पढ़ोing the signature from
		 * the  remote byte count रेजिस्टरs (otherwise ग_लिखो-only)...
		 */
		अगर ((DCR_VAL & 0x01) == 0 &&		/* 8-bit mode */
		    inb(ioaddr + EN0_RCNTLO) == 0x50 &&
		    inb(ioaddr + EN0_RCNTHI) == 0x70)
			stop_page = 0x60;
		अन्यथा
			stop_page = NESM_STOP_PG;
	पूर्ण अन्यथा अणु
		start_page = NE1SM_START_PG;
		stop_page  = NE1SM_STOP_PG;
	पूर्ण

	neX000 = (SA_prom[14] == 0x57  &&  SA_prom[15] == 0x57);
	ctron =  (SA_prom[0] == 0x00 && SA_prom[1] == 0x00 && SA_prom[2] == 0x1d);
	copam =  (SA_prom[14] == 0x49 && SA_prom[15] == 0x00);

	/* Set up the rest of the parameters. */
	अगर (neX000 || bad_card || copam) अणु
		name = (wordlength == 2) ? "NE2000" : "NE1000";
	पूर्ण
	अन्यथा अगर (ctron)
	अणु
		name = (wordlength == 2) ? "Ctron-8" : "Ctron-16";
		start_page = 0x01;
		stop_page = (wordlength == 2) ? 0x40 : 0x20;
	पूर्ण
	अन्यथा
	अणु
#अगर_घोषित SUPPORT_NE_BAD_CLONES
		/* Ack!  Well, there might be a *bad* NE*000 clone there.
		   Check क्रम total bogus addresses. */
		क्रम (i = 0; bad_clone_list[i].name8; i++)
		अणु
			अगर (SA_prom[0] == bad_clone_list[i].SAprefix[0] &&
				SA_prom[1] == bad_clone_list[i].SAprefix[1] &&
				SA_prom[2] == bad_clone_list[i].SAprefix[2])
			अणु
				अगर (wordlength == 2)
				अणु
					name = bad_clone_list[i].name16;
				पूर्ण अन्यथा अणु
					name = bad_clone_list[i].name8;
				पूर्ण
				अवरोध;
			पूर्ण
		पूर्ण
		अगर (bad_clone_list[i].name8 == शून्य)
		अणु
			pr_cont(" not found (invalid signature %2.2x %2.2x).\n",
				SA_prom[14], SA_prom[15]);
			ret = -ENXIO;
			जाओ err_out;
		पूर्ण
#अन्यथा
		pr_cont(" not found.\n");
		ret = -ENXIO;
		जाओ err_out;
#पूर्ण_अगर
	पूर्ण

	अगर (dev->irq < 2)
	अणु
		अचिन्हित दीर्घ cookie = probe_irq_on();
		outb_p(0x50, ioaddr + EN0_IMR);	/* Enable one पूर्णांकerrupt. */
		outb_p(0x00, ioaddr + EN0_RCNTLO);
		outb_p(0x00, ioaddr + EN0_RCNTHI);
		outb_p(E8390_RREAD+E8390_START, ioaddr); /* Trigger it... */
		mdelay(10);		/* रुको 10ms क्रम पूर्णांकerrupt to propagate */
		outb_p(0x00, ioaddr + EN0_IMR); 		/* Mask it again. */
		dev->irq = probe_irq_off(cookie);
		अगर (ne_msg_enable & NETIF_MSG_PROBE)
			pr_cont(" autoirq is %d", dev->irq);
	पूर्ण अन्यथा अगर (dev->irq == 2)
		/* Fixup क्रम users that करोn't know that IRQ 2 is really IRQ 9,
		   or करोn't know which one to set. */
		dev->irq = 9;

	अगर (! dev->irq) अणु
		pr_cont(" failed to detect IRQ line.\n");
		ret = -EAGAIN;
		जाओ err_out;
	पूर्ण

	/* Snarf the पूर्णांकerrupt now.  There's no poपूर्णांक in रुकोing since we cannot
	   share and the board will usually be enabled. */
	ret = request_irq(dev->irq, eip_पूर्णांकerrupt, 0, name, dev);
	अगर (ret) अणु
		pr_cont(" unable to get IRQ %d (errno=%d).\n", dev->irq, ret);
		जाओ err_out;
	पूर्ण

	dev->base_addr = ioaddr;

	क्रम (i = 0; i < ETH_ALEN; i++) अणु
		dev->dev_addr[i] = SA_prom[i];
	पूर्ण

	pr_cont("%pM\n", dev->dev_addr);

	ei_status.name = name;
	ei_status.tx_start_page = start_page;
	ei_status.stop_page = stop_page;

	/* Use 16-bit mode only अगर this wasn't overridden by DCR_VAL */
	ei_status.word16 = (wordlength == 2 && (DCR_VAL & 0x01));

	ei_status.rx_start_page = start_page + TX_PAGES;
#अगर_घोषित PACKETBUF_MEMSIZE
	 /* Allow the packet buffer size to be overridden by know-it-alls. */
	ei_status.stop_page = ei_status.tx_start_page + PACKETBUF_MEMSIZE;
#पूर्ण_अगर

	ei_status.reset_8390 = &ne_reset_8390;
	ei_status.block_input = &ne_block_input;
	ei_status.block_output = &ne_block_output;
	ei_status.get_8390_hdr = &ne_get_8390_hdr;
	ei_status.priv = 0;

	dev->netdev_ops = &eip_netdev_ops;
	NS8390p_init(dev, 0);

	ei_local->msg_enable = ne_msg_enable;
	ret = रेजिस्टर_netdev(dev);
	अगर (ret)
		जाओ out_irq;
	netdev_info(dev, "%s found at %#lx, using IRQ %d.\n",
		    name, ioaddr, dev->irq);
	वापस 0;

out_irq:
	मुक्त_irq(dev->irq, dev);
err_out:
	release_region(ioaddr, NE_IO_EXTENT);
	वापस ret;
पूर्ण

/* Hard reset the card.  This used to छोड़ो क्रम the same period that a
   8390 reset command required, but that shouldn't be necessary. */

अटल व्योम ne_reset_8390(काष्ठा net_device *dev)
अणु
	अचिन्हित दीर्घ reset_start_समय = jअगरfies;
	काष्ठा ei_device *ei_local = netdev_priv(dev);

	netअगर_dbg(ei_local, hw, dev, "resetting the 8390 t=%ld...\n", jअगरfies);

	/* DON'T change these to inb_p/outb_p or reset will fail on clones. */
	outb(inb(NE_BASE + NE_RESET), NE_BASE + NE_RESET);

	ei_status.txing = 0;
	ei_status.dमुख्यg = 0;

	/* This check _should_not_ be necessary, omit eventually. */
	जबतक ((inb_p(NE_BASE+EN0_ISR) & ENISR_RESET) == 0)
		अगर (समय_after(jअगरfies, reset_start_समय + 2*HZ/100)) अणु
			netdev_err(dev, "ne_reset_8390() did not complete.\n");
			अवरोध;
		पूर्ण
	outb_p(ENISR_RESET, NE_BASE + EN0_ISR);	/* Ack पूर्णांकr. */
पूर्ण

/* Grab the 8390 specअगरic header. Similar to the block_input routine, but
   we करोn't need to be concerned with ring wrap as the header will be at
   the start of a page, so we optimize accordingly. */

अटल व्योम ne_get_8390_hdr(काष्ठा net_device *dev, काष्ठा e8390_pkt_hdr *hdr, पूर्णांक ring_page)
अणु
	पूर्णांक nic_base = dev->base_addr;

	/* This *shouldn't* happen. If it does, it's the last thing you'll see */

	अगर (ei_status.dमुख्यg)
	अणु
		netdev_err(dev, "DMAing conflict in ne_get_8390_hdr "
			   "[DMAstat:%d][irqlock:%d].\n",
			   ei_status.dमुख्यg, ei_status.irqlock);
		वापस;
	पूर्ण

	ei_status.dमुख्यg |= 0x01;
	outb_p(E8390_NODMA+E8390_PAGE0+E8390_START, nic_base+ NE_CMD);
	outb_p(माप(काष्ठा e8390_pkt_hdr), nic_base + EN0_RCNTLO);
	outb_p(0, nic_base + EN0_RCNTHI);
	outb_p(0, nic_base + EN0_RSARLO);		/* On page boundary */
	outb_p(ring_page, nic_base + EN0_RSARHI);
	outb_p(E8390_RREAD+E8390_START, nic_base + NE_CMD);

	अगर (ei_status.word16)
		insw(NE_BASE + NE_DATAPORT, hdr, माप(काष्ठा e8390_pkt_hdr)>>1);
	अन्यथा
		insb(NE_BASE + NE_DATAPORT, hdr, माप(काष्ठा e8390_pkt_hdr));

	outb_p(ENISR_RDC, nic_base + EN0_ISR);	/* Ack पूर्णांकr. */
	ei_status.dमुख्यg &= ~0x01;

	le16_to_cpus(&hdr->count);
पूर्ण

/* Block input and output, similar to the Crynwr packet driver.  If you
   are porting to a new ethercard, look at the packet driver source क्रम hपूर्णांकs.
   The NEx000 करोesn't share the on-board packet memory -- you have to put
   the packet out through the "remote DMA" dataport using outb. */

अटल व्योम ne_block_input(काष्ठा net_device *dev, पूर्णांक count, काष्ठा sk_buff *skb, पूर्णांक ring_offset)
अणु
#अगर_घोषित NE_SANITY_CHECK
	पूर्णांक xfer_count = count;
	काष्ठा ei_device *ei_local = netdev_priv(dev);
#पूर्ण_अगर
	पूर्णांक nic_base = dev->base_addr;
	अक्षर *buf = skb->data;

	/* This *shouldn't* happen. If it does, it's the last thing you'll see */
	अगर (ei_status.dमुख्यg)
	अणु
		netdev_err(dev, "DMAing conflict in ne_block_input "
			   "[DMAstat:%d][irqlock:%d].\n",
			   ei_status.dमुख्यg, ei_status.irqlock);
		वापस;
	पूर्ण
	ei_status.dमुख्यg |= 0x01;
	outb_p(E8390_NODMA+E8390_PAGE0+E8390_START, nic_base+ NE_CMD);
	outb_p(count & 0xff, nic_base + EN0_RCNTLO);
	outb_p(count >> 8, nic_base + EN0_RCNTHI);
	outb_p(ring_offset & 0xff, nic_base + EN0_RSARLO);
	outb_p(ring_offset >> 8, nic_base + EN0_RSARHI);
	outb_p(E8390_RREAD+E8390_START, nic_base + NE_CMD);
	अगर (ei_status.word16)
	अणु
		insw(NE_BASE + NE_DATAPORT,buf,count>>1);
		अगर (count & 0x01)
		अणु
			buf[count-1] = inb(NE_BASE + NE_DATAPORT);
#अगर_घोषित NE_SANITY_CHECK
			xfer_count++;
#पूर्ण_अगर
		पूर्ण
	पूर्ण अन्यथा अणु
		insb(NE_BASE + NE_DATAPORT, buf, count);
	पूर्ण

#अगर_घोषित NE_SANITY_CHECK
	/* This was क्रम the ALPHA version only, but enough people have
	   been encountering problems so it is still here.  If you see
	   this message you either 1) have a slightly incompatible clone
	   or 2) have noise/speed problems with your bus. */

	अगर (netअगर_msg_rx_status(ei_local))
	अणु
		/* DMA termination address check... */
		पूर्णांक addr, tries = 20;
		करो अणु
			/* DON'T check for 'inb_p(EN0_ISR) & ENISR_RDC' here
			   -- it's broken क्रम Rx on some cards! */
			पूर्णांक high = inb_p(nic_base + EN0_RSARHI);
			पूर्णांक low = inb_p(nic_base + EN0_RSARLO);
			addr = (high << 8) + low;
			अगर (((ring_offset + xfer_count) & 0xff) == low)
				अवरोध;
		पूर्ण जबतक (--tries > 0);
	 	अगर (tries <= 0)
			netdev_warn(dev, "RX transfer address mismatch,"
				    "%#4.4x (expected) vs. %#4.4x (actual).\n",
				    ring_offset + xfer_count, addr);
	पूर्ण
#पूर्ण_अगर
	outb_p(ENISR_RDC, nic_base + EN0_ISR);	/* Ack पूर्णांकr. */
	ei_status.dमुख्यg &= ~0x01;
पूर्ण

अटल व्योम ne_block_output(काष्ठा net_device *dev, पूर्णांक count,
		स्थिर अचिन्हित अक्षर *buf, स्थिर पूर्णांक start_page)
अणु
	पूर्णांक nic_base = NE_BASE;
	अचिन्हित दीर्घ dma_start;
#अगर_घोषित NE_SANITY_CHECK
	पूर्णांक retries = 0;
	काष्ठा ei_device *ei_local = netdev_priv(dev);
#पूर्ण_अगर

	/* Round the count up क्रम word ग_लिखोs.  Do we need to करो this?
	   What effect will an odd byte count have on the 8390?
	   I should check someday. */

	अगर (ei_status.word16 && (count & 0x01))
		count++;

	/* This *shouldn't* happen. If it does, it's the last thing you'll see */
	अगर (ei_status.dमुख्यg)
	अणु
		netdev_err(dev, "DMAing conflict in ne_block_output."
			   "[DMAstat:%d][irqlock:%d]\n",
			   ei_status.dमुख्यg, ei_status.irqlock);
		वापस;
	पूर्ण
	ei_status.dमुख्यg |= 0x01;
	/* We should alपढ़ोy be in page 0, but to be safe... */
	outb_p(E8390_PAGE0+E8390_START+E8390_NODMA, nic_base + NE_CMD);

#अगर_घोषित NE_SANITY_CHECK
retry:
#पूर्ण_अगर

#अगर_घोषित NE_RW_BUGFIX
	/* Handle the पढ़ो-beक्रमe-ग_लिखो bug the same way as the
	   Crynwr packet driver -- the NatSemi method करोesn't work.
	   Actually this करोesn't always work either, but अगर you have
	   problems with your NEx000 this is better than nothing! */

	outb_p(0x42, nic_base + EN0_RCNTLO);
	outb_p(0x00,   nic_base + EN0_RCNTHI);
	outb_p(0x42, nic_base + EN0_RSARLO);
	outb_p(0x00, nic_base + EN0_RSARHI);
	outb_p(E8390_RREAD+E8390_START, nic_base + NE_CMD);
	/* Make certain that the dummy पढ़ो has occurred. */
	udelay(6);
#पूर्ण_अगर

	outb_p(ENISR_RDC, nic_base + EN0_ISR);

	/* Now the normal output. */
	outb_p(count & 0xff, nic_base + EN0_RCNTLO);
	outb_p(count >> 8,   nic_base + EN0_RCNTHI);
	outb_p(0x00, nic_base + EN0_RSARLO);
	outb_p(start_page, nic_base + EN0_RSARHI);

	outb_p(E8390_RWRITE+E8390_START, nic_base + NE_CMD);
	अगर (ei_status.word16) अणु
		outsw(NE_BASE + NE_DATAPORT, buf, count>>1);
	पूर्ण अन्यथा अणु
		outsb(NE_BASE + NE_DATAPORT, buf, count);
	पूर्ण

	dma_start = jअगरfies;

#अगर_घोषित NE_SANITY_CHECK
	/* This was क्रम the ALPHA version only, but enough people have
	   been encountering problems so it is still here. */

	अगर (netअगर_msg_tx_queued(ei_local))
	अणु
		/* DMA termination address check... */
		पूर्णांक addr, tries = 20;
		करो अणु
			पूर्णांक high = inb_p(nic_base + EN0_RSARHI);
			पूर्णांक low = inb_p(nic_base + EN0_RSARLO);
			addr = (high << 8) + low;
			अगर ((start_page << 8) + count == addr)
				अवरोध;
		पूर्ण जबतक (--tries > 0);

		अगर (tries <= 0)
		अणु
			netdev_warn(dev, "Tx packet transfer address mismatch,"
				    "%#4.4x (expected) vs. %#4.4x (actual).\n",
				    (start_page << 8) + count, addr);
			अगर (retries++ == 0)
				जाओ retry;
		पूर्ण
	पूर्ण
#पूर्ण_अगर

	जबतक ((inb_p(nic_base + EN0_ISR) & ENISR_RDC) == 0)
		अगर (समय_after(jअगरfies, dma_start + 2*HZ/100)) अणु		/* 20ms */
			netdev_warn(dev, "timeout waiting for Tx RDC.\n");
			ne_reset_8390(dev);
			NS8390p_init(dev, 1);
			अवरोध;
		पूर्ण

	outb_p(ENISR_RDC, nic_base + EN0_ISR);	/* Ack पूर्णांकr. */
	ei_status.dमुख्यg &= ~0x01;
पूर्ण

अटल पूर्णांक __init ne_drv_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा net_device *dev;
	पूर्णांक err, this_dev = pdev->id;
	काष्ठा resource *res;

	dev = alloc_eip_netdev();
	अगर (!dev)
		वापस -ENOMEM;

	/* ne.c करोesn't populate resources in platक्रमm_device, but
	 * rbtx4927_ne_init and rbtx4938_ne_init करो रेजिस्टर devices
	 * with resources.
	 */
	res = platक्रमm_get_resource(pdev, IORESOURCE_IO, 0);
	अगर (res) अणु
		dev->base_addr = res->start;
		dev->irq = platक्रमm_get_irq(pdev, 0);
	पूर्ण अन्यथा अणु
		अगर (this_dev < 0 || this_dev >= MAX_NE_CARDS) अणु
			मुक्त_netdev(dev);
			वापस -EINVAL;
		पूर्ण
		dev->base_addr = io[this_dev];
		dev->irq = irq[this_dev];
		dev->mem_end = bad[this_dev];
	पूर्ण
	SET_NETDEV_DEV(dev, &pdev->dev);
	err = करो_ne_probe(dev);
	अगर (err) अणु
		मुक्त_netdev(dev);
		वापस err;
	पूर्ण
	platक्रमm_set_drvdata(pdev, dev);

	/* Update with any values found by probing, करोn't update अगर
	 * resources were specअगरied.
	 */
	अगर (!res) अणु
		io[this_dev] = dev->base_addr;
		irq[this_dev] = dev->irq;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक ne_drv_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा net_device *dev = platक्रमm_get_drvdata(pdev);

	अगर (dev) अणु
		काष्ठा pnp_dev *idev = (काष्ठा pnp_dev *)ei_status.priv;
		netअगर_device_detach(dev);
		unरेजिस्टर_netdev(dev);
		अगर (idev)
			pnp_device_detach(idev);
		/* Careful ne_drv_हटाओ can be called twice, once from
		 * the platक्रमm_driver.हटाओ and again when the
		 * platक्रमm_device is being हटाओd.
		 */
		ei_status.priv = 0;
		मुक्त_irq(dev->irq, dev);
		release_region(dev->base_addr, NE_IO_EXTENT);
		मुक्त_netdev(dev);
	पूर्ण
	वापस 0;
पूर्ण

/* Remove unused devices or all अगर true. */
अटल व्योम ne_loop_rm_unreg(पूर्णांक all)
अणु
	पूर्णांक this_dev;
	काष्ठा platक्रमm_device *pdev;
	क्रम (this_dev = 0; this_dev < MAX_NE_CARDS; this_dev++) अणु
		pdev = pdev_ne[this_dev];
		/* No network device == unused */
		अगर (pdev && (!platक्रमm_get_drvdata(pdev) || all)) अणु
			ne_drv_हटाओ(pdev);
			platक्रमm_device_unरेजिस्टर(pdev);
			pdev_ne[this_dev] = शून्य;
		पूर्ण
	पूर्ण
पूर्ण

#अगर_घोषित CONFIG_PM
अटल पूर्णांक ne_drv_suspend(काष्ठा platक्रमm_device *pdev, pm_message_t state)
अणु
	काष्ठा net_device *dev = platक्रमm_get_drvdata(pdev);

	अगर (netअगर_running(dev)) अणु
		काष्ठा pnp_dev *idev = (काष्ठा pnp_dev *)ei_status.priv;
		netअगर_device_detach(dev);
		अगर (idev)
			pnp_stop_dev(idev);
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक ne_drv_resume(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा net_device *dev = platक्रमm_get_drvdata(pdev);

	अगर (netअगर_running(dev)) अणु
		काष्ठा pnp_dev *idev = (काष्ठा pnp_dev *)ei_status.priv;
		अगर (idev)
			pnp_start_dev(idev);
		ne_reset_8390(dev);
		NS8390p_init(dev, 1);
		netअगर_device_attach(dev);
	पूर्ण
	वापस 0;
पूर्ण
#अन्यथा
#घोषणा ne_drv_suspend शून्य
#घोषणा ne_drv_resume शून्य
#पूर्ण_अगर

अटल काष्ठा platक्रमm_driver ne_driver = अणु
	.हटाओ		= ne_drv_हटाओ,
	.suspend	= ne_drv_suspend,
	.resume		= ne_drv_resume,
	.driver		= अणु
		.name	= DRV_NAME,
	पूर्ण,
पूर्ण;

अटल व्योम __init ne_add_devices(व्योम)
अणु
	पूर्णांक this_dev;
	काष्ठा platक्रमm_device *pdev;

	क्रम (this_dev = 0; this_dev < MAX_NE_CARDS; this_dev++) अणु
		अगर (pdev_ne[this_dev])
			जारी;
		pdev = platक्रमm_device_रेजिस्टर_simple(
			DRV_NAME, this_dev, शून्य, 0);
		अगर (IS_ERR(pdev))
			जारी;
		pdev_ne[this_dev] = pdev;
	पूर्ण
पूर्ण

#अगर_घोषित MODULE
पूर्णांक __init init_module(व्योम)
अणु
	पूर्णांक retval;
	ne_add_devices();
	retval = platक्रमm_driver_probe(&ne_driver, ne_drv_probe);
	अगर (retval) अणु
		अगर (io[0] == 0)
			pr_notice("ne.c: You must supply \"io=0xNNN\""
			       " value(s) for ISA cards.\n");
		ne_loop_rm_unreg(1);
		वापस retval;
	पूर्ण

	/* Unरेजिस्टर unused platक्रमm_devices. */
	ne_loop_rm_unreg(0);
	वापस retval;
पूर्ण
#अन्यथा /* MODULE */
अटल पूर्णांक __init ne_init(व्योम)
अणु
	पूर्णांक retval = platक्रमm_driver_probe(&ne_driver, ne_drv_probe);

	/* Unरेजिस्टर unused platक्रमm_devices. */
	ne_loop_rm_unreg(0);
	वापस retval;
पूर्ण
module_init(ne_init);

काष्ठा net_device * __init ne_probe(पूर्णांक unit)
अणु
	पूर्णांक this_dev;
	काष्ठा net_device *dev;

	/* Find an empty slot, that is no net_device and zero io port. */
	this_dev = 0;
	जबतक ((pdev_ne[this_dev] && platक्रमm_get_drvdata(pdev_ne[this_dev])) ||
		io[this_dev]) अणु
		अगर (++this_dev == MAX_NE_CARDS)
			वापस ERR_PTR(-ENOMEM);
	पूर्ण

	/* Get irq, io from kernel command line */
	dev = alloc_eip_netdev();
	अगर (!dev)
		वापस ERR_PTR(-ENOMEM);

	प्र_लिखो(dev->name, "eth%d", unit);
	netdev_boot_setup_check(dev);

	io[this_dev] = dev->base_addr;
	irq[this_dev] = dev->irq;
	bad[this_dev] = dev->mem_end;

	मुक्त_netdev(dev);

	ne_add_devices();

	/* वापस the first device found */
	क्रम (this_dev = 0; this_dev < MAX_NE_CARDS; this_dev++) अणु
		अगर (pdev_ne[this_dev]) अणु
			dev = platक्रमm_get_drvdata(pdev_ne[this_dev]);
			अगर (dev)
				वापस dev;
		पूर्ण
	पूर्ण

	वापस ERR_PTR(-ENODEV);
पूर्ण
#पूर्ण_अगर /* MODULE */

अटल व्योम __निकास ne_निकास(व्योम)
अणु
	platक्रमm_driver_unरेजिस्टर(&ne_driver);
	ne_loop_rm_unreg(1);
पूर्ण
module_निकास(ne_निकास);
