<शैली गुरु>
/* mac8390.c: New driver क्रम 8390-based Nubus (or Nubus-alike)
   Ethernet cards on Linux */
/* Based on the क्रमmer daynaport.c driver, by Alan Cox.  Some code
   taken from or inspired by skeleton.c by Donald Becker, acenic.c by
   Jes Sorensen, and ne2k-pci.c by Donald Becker and Paul Gorपंचांगaker.

   This software may be used and distributed according to the terms of
   the GNU Public License, incorporated herein by reference.  */

/* 2000-02-28: support added क्रम Dayna and Kinetics cards by
   A.G.deWijn@phys.uu.nl */
/* 2000-04-04: support added क्रम Dayna2 by bart@etpmod.phys.tue.nl */
/* 2001-04-18: support क्रम DaynaPort E/LC-M by rayk@knightsmanor.org */
/* 2001-05-15: support क्रम Cabletron ported from old daynaport driver
 * and fixed access to Sonic Sys card which masquerades as a Farallon
 * by rayk@knightsmanor.org */
/* 2002-12-30: Try to support more cards, some clues from NetBSD driver */
/* 2003-12-26: Make sure Asante cards always work. */

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#समावेश <linux/module.h>
#समावेश <linux/kernel.h>
#समावेश <linux/types.h>
#समावेश <linux/fcntl.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/ptrace.h>
#समावेश <linux/ioport.h>
#समावेश <linux/nubus.h>
#समावेश <linux/in.h>
#समावेश <linux/माला.स>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/init.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/etherdevice.h>
#समावेश <linux/skbuff.h>
#समावेश <linux/bitops.h>
#समावेश <linux/पन.स>

#समावेश <यंत्र/dma.h>
#समावेश <यंत्र/hwtest.h>
#समावेश <यंत्र/macपूर्णांकs.h>

अटल अक्षर version[] =
	"v0.4 2001-05-15 David Huggins-Daines <dhd@debian.org> and others\n";

#घोषणा EI_SHIFT(x)	(ei_local->reg_offset[x])
#घोषणा ei_inb(port)	in_8(port)
#घोषणा ei_outb(val, port)	out_8(port, val)
#घोषणा ei_inb_p(port)	in_8(port)
#घोषणा ei_outb_p(val, port)	out_8(port, val)

#समावेश "lib8390.c"

#घोषणा WD_START_PG			0x00	/* First page of TX buffer */
#घोषणा CABLETRON_RX_START_PG		0x00    /* First page of RX buffer */
#घोषणा CABLETRON_RX_STOP_PG		0x30    /* Last page +1 of RX ring */
#घोषणा CABLETRON_TX_START_PG		CABLETRON_RX_STOP_PG
						/* First page of TX buffer */

/*
 * Unक्रमtunately it seems we have to hardcode these क्रम the moment
 * Shouldn't the card know about this?
 * Does anyone know where to पढ़ो it off the card?
 * Do we trust the data provided by the card?
 */

#घोषणा DAYNA_8390_BASE		0x80000
#घोषणा DAYNA_8390_MEM		0x00000

#घोषणा CABLETRON_8390_BASE	0x90000
#घोषणा CABLETRON_8390_MEM	0x00000

#घोषणा INTERLAN_8390_BASE	0xE0000
#घोषणा INTERLAN_8390_MEM	0xD0000

क्रमागत mac8390_type अणु
	MAC8390_NONE = -1,
	MAC8390_APPLE,
	MAC8390_ASANTE,
	MAC8390_FARALLON,
	MAC8390_CABLETRON,
	MAC8390_DAYNA,
	MAC8390_INTERLAN,
	MAC8390_KINETICS,
पूर्ण;

अटल स्थिर अक्षर *cardname[] = अणु
	"apple",
	"asante",
	"farallon",
	"cabletron",
	"dayna",
	"interlan",
	"kinetics",
पूर्ण;

अटल स्थिर पूर्णांक word16[] = अणु
	1, /* apple */
	1, /* asante */
	1, /* farallon */
	1, /* cabletron */
	0, /* dayna */
	1, /* पूर्णांकerlan */
	0, /* kinetics */
पूर्ण;

/* on which cards करो we use NuBus resources? */
अटल स्थिर पूर्णांक useresources[] = अणु
	1, /* apple */
	1, /* asante */
	1, /* farallon */
	0, /* cabletron */
	0, /* dayna */
	0, /* पूर्णांकerlan */
	0, /* kinetics */
पूर्ण;

क्रमागत mac8390_access अणु
	ACCESS_UNKNOWN = 0,
	ACCESS_32,
	ACCESS_16,
पूर्ण;

बाह्य पूर्णांक mac8390_memtest(काष्ठा net_device *dev);
अटल पूर्णांक mac8390_initdev(काष्ठा net_device *dev, काष्ठा nubus_board *board,
			   क्रमागत mac8390_type type);

अटल पूर्णांक mac8390_खोलो(काष्ठा net_device *dev);
अटल पूर्णांक mac8390_बंद(काष्ठा net_device *dev);
अटल व्योम mac8390_no_reset(काष्ठा net_device *dev);
अटल व्योम पूर्णांकerlan_reset(काष्ठा net_device *dev);

/* Sane (32-bit chunk memory पढ़ो/ग_लिखो) - Some Farallon and Apple करो this*/
अटल व्योम sane_get_8390_hdr(काष्ठा net_device *dev,
			      काष्ठा e8390_pkt_hdr *hdr, पूर्णांक ring_page);
अटल व्योम sane_block_input(काष्ठा net_device *dev, पूर्णांक count,
			     काष्ठा sk_buff *skb, पूर्णांक ring_offset);
अटल व्योम sane_block_output(काष्ठा net_device *dev, पूर्णांक count,
			      स्थिर अचिन्हित अक्षर *buf, स्थिर पूर्णांक start_page);

/* dayna_स_नकल to and from card */
अटल व्योम dayna_स_नकल_fromcard(काष्ठा net_device *dev, व्योम *to,
				पूर्णांक from, पूर्णांक count);
अटल व्योम dayna_स_नकल_tocard(काष्ठा net_device *dev, पूर्णांक to,
			      स्थिर व्योम *from, पूर्णांक count);

/* Dayna - Dayna/Kinetics use this */
अटल व्योम dayna_get_8390_hdr(काष्ठा net_device *dev,
			       काष्ठा e8390_pkt_hdr *hdr, पूर्णांक ring_page);
अटल व्योम dayna_block_input(काष्ठा net_device *dev, पूर्णांक count,
			      काष्ठा sk_buff *skb, पूर्णांक ring_offset);
अटल व्योम dayna_block_output(काष्ठा net_device *dev, पूर्णांक count,
			       स्थिर अचिन्हित अक्षर *buf, पूर्णांक start_page);

/* Slow Sane (16-bit chunk memory पढ़ो/ग_लिखो) Cabletron uses this */
अटल व्योम slow_sane_get_8390_hdr(काष्ठा net_device *dev,
				   काष्ठा e8390_pkt_hdr *hdr, पूर्णांक ring_page);
अटल व्योम slow_sane_block_input(काष्ठा net_device *dev, पूर्णांक count,
				  काष्ठा sk_buff *skb, पूर्णांक ring_offset);
अटल व्योम slow_sane_block_output(काष्ठा net_device *dev, पूर्णांक count,
				   स्थिर अचिन्हित अक्षर *buf, पूर्णांक start_page);
अटल व्योम word_स_नकल_tocard(अचिन्हित दीर्घ tp, स्थिर व्योम *fp, पूर्णांक count);
अटल व्योम word_स_नकल_fromcard(व्योम *tp, अचिन्हित दीर्घ fp, पूर्णांक count);

अटल क्रमागत mac8390_type mac8390_ident(काष्ठा nubus_rsrc *fres)
अणु
	चयन (fres->dr_sw) अणु
	हाल NUBUS_DRSW_3COM:
		चयन (fres->dr_hw) अणु
		हाल NUBUS_DRHW_APPLE_SONIC_NB:
		हाल NUBUS_DRHW_APPLE_SONIC_LC:
		हाल NUBUS_DRHW_SONNET:
			वापस MAC8390_NONE;
		शेष:
			वापस MAC8390_APPLE;
		पूर्ण

	हाल NUBUS_DRSW_APPLE:
		चयन (fres->dr_hw) अणु
		हाल NUBUS_DRHW_ASANTE_LC:
			वापस MAC8390_NONE;
		हाल NUBUS_DRHW_CABLETRON:
			वापस MAC8390_CABLETRON;
		शेष:
			वापस MAC8390_APPLE;
		पूर्ण

	हाल NUBUS_DRSW_ASANTE:
		वापस MAC8390_ASANTE;

	हाल NUBUS_DRSW_TECHWORKS:
	हाल NUBUS_DRSW_DAYNA2:
	हाल NUBUS_DRSW_DAYNA_LC:
		अगर (fres->dr_hw == NUBUS_DRHW_CABLETRON)
			वापस MAC8390_CABLETRON;
		अन्यथा
			वापस MAC8390_APPLE;

	हाल NUBUS_DRSW_FARALLON:
		वापस MAC8390_FARALLON;

	हाल NUBUS_DRSW_KINETICS:
		चयन (fres->dr_hw) अणु
		हाल NUBUS_DRHW_INTERLAN:
			वापस MAC8390_INTERLAN;
		शेष:
			वापस MAC8390_KINETICS;
		पूर्ण

	हाल NUBUS_DRSW_DAYNA:
		/*
		 * These correspond to Dayna Sonic cards
		 * which use the macsonic driver
		 */
		अगर (fres->dr_hw == NUBUS_DRHW_SMC9194 ||
		    fres->dr_hw == NUBUS_DRHW_INTERLAN)
			वापस MAC8390_NONE;
		अन्यथा
			वापस MAC8390_DAYNA;
	पूर्ण
	वापस MAC8390_NONE;
पूर्ण

अटल क्रमागत mac8390_access mac8390_testio(अचिन्हित दीर्घ membase)
अणु
	u32 outdata = 0xA5A0B5B0;
	u32 indata = 0;

	/* Try writing 32 bits */
	nubus_ग_लिखोl(outdata, membase);
	/* Now पढ़ो it back */
	indata = nubus_पढ़ोl(membase);
	अगर (outdata == indata)
		वापस ACCESS_32;

	outdata = 0xC5C0D5D0;
	indata = 0;

	/* Write 16 bit output */
	word_स_नकल_tocard(membase, &outdata, 4);
	/* Now पढ़ो it back */
	word_स_नकल_fromcard(&indata, membase, 4);
	अगर (outdata == indata)
		वापस ACCESS_16;

	वापस ACCESS_UNKNOWN;
पूर्ण

अटल पूर्णांक mac8390_memsize(अचिन्हित दीर्घ membase)
अणु
	अचिन्हित दीर्घ flags;
	पूर्णांक i, j;

	local_irq_save(flags);
	/* Check up to 32K in 4K increments */
	क्रम (i = 0; i < 8; i++) अणु
		अस्थिर अचिन्हित लघु *m = (अचिन्हित लघु *)(membase + (i * 0x1000));

		/* Unग_लिखोable - we have a fully decoded card and the
		   RAM end located */
		अगर (hwreg_present(m) == 0)
			अवरोध;

		/* ग_लिखो a distinctive byte */
		*m = 0xA5A0 | i;
		/* check that we पढ़ो back what we wrote */
		अगर (*m != (0xA5A0 | i))
			अवरोध;

		/* check क्रम partial decode and wrap */
		क्रम (j = 0; j < i; j++) अणु
			अस्थिर अचिन्हित लघु *p = (अचिन्हित लघु *)(membase + (j * 0x1000));
			अगर (*p != (0xA5A0 | j))
				अवरोध;
		पूर्ण
	पूर्ण
	local_irq_restore(flags);
	/*
	 * in any हाल, we stopped once we tried one block too many,
	 * or once we reached 32K
	 */
	वापस i * 0x1000;
पूर्ण

अटल bool mac8390_rsrc_init(काष्ठा net_device *dev,
			      काष्ठा nubus_rsrc *fres,
			      क्रमागत mac8390_type cardtype)
अणु
	काष्ठा nubus_board *board = fres->board;
	काष्ठा nubus_dir dir;
	काष्ठा nubus_dirent ent;
	पूर्णांक offset;
	अस्थिर अचिन्हित लघु *i;

	dev->irq = SLOT2IRQ(board->slot);
	/* This is getting to be a habit */
	dev->base_addr = board->slot_addr | ((board->slot & 0xf) << 20);

	/*
	 * Get some Nubus info - we will trust the card's idea
	 * of where its memory and रेजिस्टरs are.
	 */

	अगर (nubus_get_func_dir(fres, &dir) == -1) अणु
		dev_err(&board->dev,
			"Unable to get Nubus functional directory\n");
		वापस false;
	पूर्ण

	/* Get the MAC address */
	अगर (nubus_find_rsrc(&dir, NUBUS_RESID_MAC_ADDRESS, &ent) == -1) अणु
		dev_info(&board->dev, "MAC address resource not found\n");
		वापस false;
	पूर्ण

	nubus_get_rsrc_mem(dev->dev_addr, &ent, 6);

	अगर (useresources[cardtype] == 1) अणु
		nubus_सूची_शुरु(&dir);
		अगर (nubus_find_rsrc(&dir, NUBUS_RESID_MINOR_BASEOS,
				    &ent) == -1) अणु
			dev_err(&board->dev,
				"Memory offset resource not found\n");
			वापस false;
		पूर्ण
		nubus_get_rsrc_mem(&offset, &ent, 4);
		dev->mem_start = dev->base_addr + offset;
		/* yes, this is how the Apple driver करोes it */
		dev->base_addr = dev->mem_start + 0x10000;
		nubus_सूची_शुरु(&dir);
		अगर (nubus_find_rsrc(&dir, NUBUS_RESID_MINOR_LENGTH,
				    &ent) == -1) अणु
			dev_info(&board->dev,
				 "Memory length resource not found, probing\n");
			offset = mac8390_memsize(dev->mem_start);
		पूर्ण अन्यथा अणु
			nubus_get_rsrc_mem(&offset, &ent, 4);
		पूर्ण
		dev->mem_end = dev->mem_start + offset;
	पूर्ण अन्यथा अणु
		चयन (cardtype) अणु
		हाल MAC8390_KINETICS:
		हाल MAC8390_DAYNA: /* it's the same */
			dev->base_addr = (पूर्णांक)(board->slot_addr +
					       DAYNA_8390_BASE);
			dev->mem_start = (पूर्णांक)(board->slot_addr +
					       DAYNA_8390_MEM);
			dev->mem_end = dev->mem_start +
				       mac8390_memsize(dev->mem_start);
			अवरोध;
		हाल MAC8390_INTERLAN:
			dev->base_addr = (पूर्णांक)(board->slot_addr +
					       INTERLAN_8390_BASE);
			dev->mem_start = (पूर्णांक)(board->slot_addr +
					       INTERLAN_8390_MEM);
			dev->mem_end = dev->mem_start +
				       mac8390_memsize(dev->mem_start);
			अवरोध;
		हाल MAC8390_CABLETRON:
			dev->base_addr = (पूर्णांक)(board->slot_addr +
					       CABLETRON_8390_BASE);
			dev->mem_start = (पूर्णांक)(board->slot_addr +
					       CABLETRON_8390_MEM);
			/* The base address is unपढ़ोable अगर 0x00
			 * has been written to the command रेजिस्टर
			 * Reset the chip by writing E8390_NODMA +
			 *   E8390_PAGE0 + E8390_STOP just to be
			 *   sure
			 */
			i = (व्योम *)dev->base_addr;
			*i = 0x21;
			dev->mem_end = dev->mem_start +
				       mac8390_memsize(dev->mem_start);
			अवरोध;

		शेष:
			dev_err(&board->dev,
				"No known base address for card type\n");
			वापस false;
		पूर्ण
	पूर्ण

	वापस true;
पूर्ण

अटल पूर्णांक mac8390_device_probe(काष्ठा nubus_board *board)
अणु
	काष्ठा net_device *dev;
	पूर्णांक err = -ENODEV;
	काष्ठा nubus_rsrc *fres;
	क्रमागत mac8390_type cardtype = MAC8390_NONE;

	dev = ____alloc_ei_netdev(0);
	अगर (!dev)
		वापस -ENOMEM;

	SET_NETDEV_DEV(dev, &board->dev);

	क्रम_each_board_func_rsrc(board, fres) अणु
		अगर (fres->category != NUBUS_CAT_NETWORK ||
		    fres->type != NUBUS_TYPE_ETHERNET)
			जारी;

		cardtype = mac8390_ident(fres);
		अगर (cardtype == MAC8390_NONE)
			जारी;

		अगर (mac8390_rsrc_init(dev, fres, cardtype))
			अवरोध;
	पूर्ण
	अगर (!fres)
		जाओ out;

	err = mac8390_initdev(dev, board, cardtype);
	अगर (err)
		जाओ out;

	err = रेजिस्टर_netdev(dev);
	अगर (err)
		जाओ out;

	nubus_set_drvdata(board, dev);
	वापस 0;

out:
	मुक्त_netdev(dev);
	वापस err;
पूर्ण

अटल पूर्णांक mac8390_device_हटाओ(काष्ठा nubus_board *board)
अणु
	काष्ठा net_device *dev = nubus_get_drvdata(board);

	unरेजिस्टर_netdev(dev);
	मुक्त_netdev(dev);
	वापस 0;
पूर्ण

अटल काष्ठा nubus_driver mac8390_driver = अणु
	.probe = mac8390_device_probe,
	.हटाओ = mac8390_device_हटाओ,
	.driver = अणु
		.name = KBUILD_MODNAME,
		.owner = THIS_MODULE,
	पूर्ण
पूर्ण;

MODULE_AUTHOR("David Huggins-Daines <dhd@debian.org> and others");
MODULE_DESCRIPTION("Macintosh NS8390-based Nubus Ethernet driver");
MODULE_LICENSE("GPL");

अटल पूर्णांक __init mac8390_init(व्योम)
अणु
	वापस nubus_driver_रेजिस्टर(&mac8390_driver);
पूर्ण
module_init(mac8390_init);

अटल व्योम __निकास mac8390_निकास(व्योम)
अणु
	nubus_driver_unरेजिस्टर(&mac8390_driver);
पूर्ण
module_निकास(mac8390_निकास);

अटल स्थिर काष्ठा net_device_ops mac8390_netdev_ops = अणु
	.nकरो_खोलो 		= mac8390_खोलो,
	.nकरो_stop		= mac8390_बंद,
	.nकरो_start_xmit		= __ei_start_xmit,
	.nकरो_tx_समयout		= __ei_tx_समयout,
	.nकरो_get_stats		= __ei_get_stats,
	.nकरो_set_rx_mode	= __ei_set_multicast_list,
	.nकरो_validate_addr	= eth_validate_addr,
	.nकरो_set_mac_address 	= eth_mac_addr,
#अगर_घोषित CONFIG_NET_POLL_CONTROLLER
	.nकरो_poll_controller	= __ei_poll,
#पूर्ण_अगर
पूर्ण;

अटल पूर्णांक mac8390_initdev(काष्ठा net_device *dev, काष्ठा nubus_board *board,
			   क्रमागत mac8390_type type)
अणु
	अटल u32 fwrd4_offsets[16] = अणु
		0,      4,      8,      12,
		16,     20,     24,     28,
		32,     36,     40,     44,
		48,     52,     56,     60
	पूर्ण;
	अटल u32 back4_offsets[16] = अणु
		60,     56,     52,     48,
		44,     40,     36,     32,
		28,     24,     20,     16,
		12,     8,      4,      0
	पूर्ण;
	अटल u32 fwrd2_offsets[16] = अणु
		0,      2,      4,      6,
		8,     10,     12,     14,
		16,    18,     20,     22,
		24,    26,     28,     30
	पूर्ण;

	पूर्णांक access_biपंचांगode = 0;

	/* Now fill in our stuff */
	dev->netdev_ops = &mac8390_netdev_ops;

	/* GAR, ei_status is actually a macro even though it looks global */
	ei_status.name = cardname[type];
	ei_status.word16 = word16[type];

	/* Cabletron's TX/RX buffers are backwards */
	अगर (type == MAC8390_CABLETRON) अणु
		ei_status.tx_start_page = CABLETRON_TX_START_PG;
		ei_status.rx_start_page = CABLETRON_RX_START_PG;
		ei_status.stop_page = CABLETRON_RX_STOP_PG;
		ei_status.rmem_start = dev->mem_start;
		ei_status.rmem_end = dev->mem_start + CABLETRON_RX_STOP_PG*256;
	पूर्ण अन्यथा अणु
		ei_status.tx_start_page = WD_START_PG;
		ei_status.rx_start_page = WD_START_PG + TX_PAGES;
		ei_status.stop_page = (dev->mem_end - dev->mem_start)/256;
		ei_status.rmem_start = dev->mem_start + TX_PAGES*256;
		ei_status.rmem_end = dev->mem_end;
	पूर्ण

	/* Fill in model-specअगरic inक्रमmation and functions */
	चयन (type) अणु
	हाल MAC8390_FARALLON:
	हाल MAC8390_APPLE:
		चयन (mac8390_testio(dev->mem_start)) अणु
		हाल ACCESS_UNKNOWN:
			dev_err(&board->dev,
				"Don't know how to access card memory\n");
			वापस -ENODEV;

		हाल ACCESS_16:
			/* 16 bit card, रेजिस्टर map is reversed */
			ei_status.reset_8390 = mac8390_no_reset;
			ei_status.block_input = slow_sane_block_input;
			ei_status.block_output = slow_sane_block_output;
			ei_status.get_8390_hdr = slow_sane_get_8390_hdr;
			ei_status.reg_offset = back4_offsets;
			अवरोध;

		हाल ACCESS_32:
			/* 32 bit card, रेजिस्टर map is reversed */
			ei_status.reset_8390 = mac8390_no_reset;
			ei_status.block_input = sane_block_input;
			ei_status.block_output = sane_block_output;
			ei_status.get_8390_hdr = sane_get_8390_hdr;
			ei_status.reg_offset = back4_offsets;
			access_biपंचांगode = 1;
			अवरोध;
		पूर्ण
		अवरोध;

	हाल MAC8390_ASANTE:
		/* Some Asante cards pass the 32 bit test
		 * but overग_लिखो प्रणाली memory when run at 32 bit.
		 * so we run them all at 16 bit.
		 */
		ei_status.reset_8390 = mac8390_no_reset;
		ei_status.block_input = slow_sane_block_input;
		ei_status.block_output = slow_sane_block_output;
		ei_status.get_8390_hdr = slow_sane_get_8390_hdr;
		ei_status.reg_offset = back4_offsets;
		अवरोध;

	हाल MAC8390_CABLETRON:
		/* 16 bit card, रेजिस्टर map is लघु क्रमward */
		ei_status.reset_8390 = mac8390_no_reset;
		ei_status.block_input = slow_sane_block_input;
		ei_status.block_output = slow_sane_block_output;
		ei_status.get_8390_hdr = slow_sane_get_8390_hdr;
		ei_status.reg_offset = fwrd2_offsets;
		अवरोध;

	हाल MAC8390_DAYNA:
	हाल MAC8390_KINETICS:
		/* 16 bit memory, रेजिस्टर map is क्रमward */
		/* dayna and similar */
		ei_status.reset_8390 = mac8390_no_reset;
		ei_status.block_input = dayna_block_input;
		ei_status.block_output = dayna_block_output;
		ei_status.get_8390_hdr = dayna_get_8390_hdr;
		ei_status.reg_offset = fwrd4_offsets;
		अवरोध;

	हाल MAC8390_INTERLAN:
		/* 16 bit memory, रेजिस्टर map is क्रमward */
		ei_status.reset_8390 = पूर्णांकerlan_reset;
		ei_status.block_input = slow_sane_block_input;
		ei_status.block_output = slow_sane_block_output;
		ei_status.get_8390_hdr = slow_sane_get_8390_hdr;
		ei_status.reg_offset = fwrd4_offsets;
		अवरोध;

	शेष:
		dev_err(&board->dev, "Unsupported card type\n");
		वापस -ENODEV;
	पूर्ण

	__NS8390_init(dev, 0);

	/* Good, करोne, now spit out some messages */
	dev_info(&board->dev, "%s (type %s)\n", board->name, cardname[type]);
	dev_info(&board->dev, "MAC %pM, IRQ %d, %d KB shared memory at %#lx, %d-bit access.\n",
		 dev->dev_addr, dev->irq,
		 (अचिन्हित पूर्णांक)(dev->mem_end - dev->mem_start) >> 10,
		 dev->mem_start, access_biपंचांगode ? 32 : 16);
	वापस 0;
पूर्ण

अटल पूर्णांक mac8390_खोलो(काष्ठा net_device *dev)
अणु
	पूर्णांक err;

	__ei_खोलो(dev);
	err = request_irq(dev->irq, __ei_पूर्णांकerrupt, 0, "8390 Ethernet", dev);
	अगर (err)
		pr_err("%s: unable to get IRQ %d\n", dev->name, dev->irq);
	वापस err;
पूर्ण

अटल पूर्णांक mac8390_बंद(काष्ठा net_device *dev)
अणु
	मुक्त_irq(dev->irq, dev);
	__ei_बंद(dev);
	वापस 0;
पूर्ण

अटल व्योम mac8390_no_reset(काष्ठा net_device *dev)
अणु
	काष्ठा ei_device *ei_local = netdev_priv(dev);

	ei_status.txing = 0;
	netअगर_info(ei_local, hw, dev, "reset not supported\n");
पूर्ण

अटल व्योम पूर्णांकerlan_reset(काष्ठा net_device *dev)
अणु
	अचिन्हित अक्षर *target = nubus_slot_addr(IRQ2SLOT(dev->irq));
	काष्ठा ei_device *ei_local = netdev_priv(dev);

	netअगर_info(ei_local, hw, dev, "Need to reset the NS8390 t=%lu...",
		   jअगरfies);
	ei_status.txing = 0;
	target[0xC0000] = 0;
	अगर (netअगर_msg_hw(ei_local))
		pr_cont("reset complete\n");
पूर्ण

/* dayna_स_नकल_fromio/dayna_स_नकल_toio */
/* directly from daynaport.c by Alan Cox */
अटल व्योम dayna_स_नकल_fromcard(काष्ठा net_device *dev, व्योम *to, पूर्णांक from,
				  पूर्णांक count)
अणु
	अस्थिर अचिन्हित अक्षर *ptr;
	अचिन्हित अक्षर *target = to;
	from <<= 1;	/* word, skip overhead */
	ptr = (अचिन्हित अक्षर *)(dev->mem_start+from);
	/* Leading byte? */
	अगर (from & 2) अणु
		*target++ = ptr[-1];
		ptr += 2;
		count--;
	पूर्ण
	जबतक (count >= 2) अणु
		*(अचिन्हित लघु *)target = *(अचिन्हित लघु अस्थिर *)ptr;
		ptr += 4;			/* skip cruft */
		target += 2;
		count -= 2;
	पूर्ण
	/* Trailing byte? */
	अगर (count)
		*target = *ptr;
पूर्ण

अटल व्योम dayna_स_नकल_tocard(काष्ठा net_device *dev, पूर्णांक to,
				स्थिर व्योम *from, पूर्णांक count)
अणु
	अस्थिर अचिन्हित लघु *ptr;
	स्थिर अचिन्हित अक्षर *src = from;
	to <<= 1;	/* word, skip overhead */
	ptr = (अचिन्हित लघु *)(dev->mem_start+to);
	/* Leading byte? */
	अगर (to & 2) अणु		/* aव्योम a byte ग_लिखो (stomps on other data) */
		ptr[-1] = (ptr[-1]&0xFF00)|*src++;
		ptr++;
		count--;
	पूर्ण
	जबतक (count >= 2) अणु
		*ptr++ = *(अचिन्हित लघु *)src;	/* Copy and */
		ptr++;			/* skip cruft */
		src += 2;
		count -= 2;
	पूर्ण
	/* Trailing byte? */
	अगर (count) अणु
		/* card करोesn't like byte ग_लिखोs */
		*ptr = (*ptr & 0x00FF) | (*src << 8);
	पूर्ण
पूर्ण

/* sane block input/output */
अटल व्योम sane_get_8390_hdr(काष्ठा net_device *dev,
			      काष्ठा e8390_pkt_hdr *hdr, पूर्णांक ring_page)
अणु
	अचिन्हित दीर्घ hdr_start = (ring_page - WD_START_PG)<<8;
	स_नकल_fromio(hdr, (व्योम __iomem *)dev->mem_start + hdr_start, 4);
	/* Fix endianness */
	hdr->count = swab16(hdr->count);
पूर्ण

अटल व्योम sane_block_input(काष्ठा net_device *dev, पूर्णांक count,
			     काष्ठा sk_buff *skb, पूर्णांक ring_offset)
अणु
	अचिन्हित दीर्घ xfer_base = ring_offset - (WD_START_PG<<8);
	अचिन्हित दीर्घ xfer_start = xfer_base + dev->mem_start;

	अगर (xfer_start + count > ei_status.rmem_end) अणु
		/* We must wrap the input move. */
		पूर्णांक semi_count = ei_status.rmem_end - xfer_start;
		स_नकल_fromio(skb->data,
			      (व्योम __iomem *)dev->mem_start + xfer_base,
			      semi_count);
		count -= semi_count;
		स_नकल_fromio(skb->data + semi_count,
			      (व्योम __iomem *)ei_status.rmem_start, count);
	पूर्ण अन्यथा अणु
		स_नकल_fromio(skb->data,
			      (व्योम __iomem *)dev->mem_start + xfer_base,
			      count);
	पूर्ण
पूर्ण

अटल व्योम sane_block_output(काष्ठा net_device *dev, पूर्णांक count,
			      स्थिर अचिन्हित अक्षर *buf, पूर्णांक start_page)
अणु
	दीर्घ shmem = (start_page - WD_START_PG)<<8;

	स_नकल_toio((व्योम __iomem *)dev->mem_start + shmem, buf, count);
पूर्ण

/* dayna block input/output */
अटल व्योम dayna_get_8390_hdr(काष्ठा net_device *dev,
			       काष्ठा e8390_pkt_hdr *hdr, पूर्णांक ring_page)
अणु
	अचिन्हित दीर्घ hdr_start = (ring_page - WD_START_PG)<<8;

	dayna_स_नकल_fromcard(dev, hdr, hdr_start, 4);
	/* Fix endianness */
	hdr->count = (hdr->count & 0xFF) << 8 | (hdr->count >> 8);
पूर्ण

अटल व्योम dayna_block_input(काष्ठा net_device *dev, पूर्णांक count,
			      काष्ठा sk_buff *skb, पूर्णांक ring_offset)
अणु
	अचिन्हित दीर्घ xfer_base = ring_offset - (WD_START_PG<<8);
	अचिन्हित दीर्घ xfer_start = xfer_base+dev->mem_start;

	/* Note the offset math is करोne in card memory space which is word
	   per दीर्घ onto our space. */

	अगर (xfer_start + count > ei_status.rmem_end) अणु
		/* We must wrap the input move. */
		पूर्णांक semi_count = ei_status.rmem_end - xfer_start;
		dayna_स_नकल_fromcard(dev, skb->data, xfer_base, semi_count);
		count -= semi_count;
		dayna_स_नकल_fromcard(dev, skb->data + semi_count,
				      ei_status.rmem_start - dev->mem_start,
				      count);
	पूर्ण अन्यथा अणु
		dayna_स_नकल_fromcard(dev, skb->data, xfer_base, count);
	पूर्ण
पूर्ण

अटल व्योम dayna_block_output(काष्ठा net_device *dev, पूर्णांक count,
			       स्थिर अचिन्हित अक्षर *buf,
			       पूर्णांक start_page)
अणु
	दीर्घ shmem = (start_page - WD_START_PG)<<8;

	dayna_स_नकल_tocard(dev, shmem, buf, count);
पूर्ण

/* Cabletron block I/O */
अटल व्योम slow_sane_get_8390_hdr(काष्ठा net_device *dev,
				   काष्ठा e8390_pkt_hdr *hdr,
				   पूर्णांक ring_page)
अणु
	अचिन्हित दीर्घ hdr_start = (ring_page - WD_START_PG)<<8;
	word_स_नकल_fromcard(hdr, dev->mem_start + hdr_start, 4);
	/* Register endianism - fix here rather than 8390.c */
	hdr->count = (hdr->count&0xFF)<<8|(hdr->count>>8);
पूर्ण

अटल व्योम slow_sane_block_input(काष्ठा net_device *dev, पूर्णांक count,
				  काष्ठा sk_buff *skb, पूर्णांक ring_offset)
अणु
	अचिन्हित दीर्घ xfer_base = ring_offset - (WD_START_PG<<8);
	अचिन्हित दीर्घ xfer_start = xfer_base+dev->mem_start;

	अगर (xfer_start + count > ei_status.rmem_end) अणु
		/* We must wrap the input move. */
		पूर्णांक semi_count = ei_status.rmem_end - xfer_start;
		word_स_नकल_fromcard(skb->data, dev->mem_start + xfer_base,
				     semi_count);
		count -= semi_count;
		word_स_नकल_fromcard(skb->data + semi_count,
				     ei_status.rmem_start, count);
	पूर्ण अन्यथा अणु
		word_स_नकल_fromcard(skb->data, dev->mem_start + xfer_base,
				     count);
	पूर्ण
पूर्ण

अटल व्योम slow_sane_block_output(काष्ठा net_device *dev, पूर्णांक count,
				   स्थिर अचिन्हित अक्षर *buf, पूर्णांक start_page)
अणु
	दीर्घ shmem = (start_page - WD_START_PG)<<8;

	word_स_नकल_tocard(dev->mem_start + shmem, buf, count);
पूर्ण

अटल व्योम word_स_नकल_tocard(अचिन्हित दीर्घ tp, स्थिर व्योम *fp, पूर्णांक count)
अणु
	अस्थिर अचिन्हित लघु *to = (व्योम *)tp;
	स्थिर अचिन्हित लघु *from = fp;

	count++;
	count /= 2;

	जबतक (count--)
		*to++ = *from++;
पूर्ण

अटल व्योम word_स_नकल_fromcard(व्योम *tp, अचिन्हित दीर्घ fp, पूर्णांक count)
अणु
	अचिन्हित लघु *to = tp;
	स्थिर अस्थिर अचिन्हित लघु *from = (स्थिर व्योम *)fp;

	count++;
	count /= 2;

	जबतक (count--)
		*to++ = *from++;
पूर्ण


