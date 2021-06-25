<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * macsonic.c
 *
 * (C) 2005 Finn Thain
 *
 * Converted to DMA API, converted to unअगरied driver model, made it work as
 * a module again, and from the mac68k project, पूर्णांकroduced more 32-bit cards
 * and dhd's support क्रम 16-bit cards.
 *
 * (C) 1998 Alan Cox
 *
 * Debugging Andreas Ehliar, Michael Schmitz
 *
 * Based on code
 * (C) 1996 by Thomas Bogenकरोerfer (tsbogend@bigbug.franken.de)
 *
 * This driver is based on work from Andreas Busse, but most of
 * the code is rewritten.
 *
 * (C) 1995 by Andreas Busse (andy@walकरोrf-gmbh.de)
 *
 * A driver क्रम the Mac onboard Sonic ethernet chip.
 *
 * 98/12/21 MSch: judged from tests on Q800, it's basically working,
 *		  but eating up both receive and transmit resources
 *		  and duplicating packets. Needs more testing.
 *
 * 99/01/03 MSch: upgraded to version 0.92 of the core driver, fixed.
 *
 * 00/10/31 sammy@oh.verio.com: Updated driver क्रम 2.4 kernels, fixed problems
 *          on centris.
 */

#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/types.h>
#समावेश <linux/fcntl.h>
#समावेश <linux/gfp.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/ioport.h>
#समावेश <linux/in.h>
#समावेश <linux/माला.स>
#समावेश <linux/delay.h>
#समावेश <linux/nubus.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/netdevice.h>
#समावेश <linux/etherdevice.h>
#समावेश <linux/skbuff.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/dma-mapping.h>
#समावेश <linux/bitrev.h>
#समावेश <linux/slab.h>
#समावेश <linux/pgtable.h>

#समावेश <यंत्र/पन.स>
#समावेश <यंत्र/hwtest.h>
#समावेश <यंत्र/dma.h>
#समावेश <यंत्र/macपूर्णांकosh.h>
#समावेश <यंत्र/macपूर्णांकs.h>
#समावेश <यंत्र/mac_via.h>

#समावेश "sonic.h"

/* These should basically be bus-size and endian independent (since
   the SONIC is at least smart enough that it uses the same endianness
   as the host, unlike certain less enlightened Macपूर्णांकosh NICs) */
#घोषणा SONIC_READ(reg) (nubus_पढ़ोw(dev->base_addr + (reg * 4) \
	      + lp->reg_offset))
#घोषणा SONIC_WRITE(reg,val) (nubus_ग_लिखोw(val, dev->base_addr + (reg * 4) \
	      + lp->reg_offset))

/* For onboard SONIC */
#घोषणा ONBOARD_SONIC_REGISTERS	0x50F0A000
#घोषणा ONBOARD_SONIC_PROM_BASE	0x50f08000

क्रमागत macsonic_type अणु
	MACSONIC_DUODOCK,
	MACSONIC_APPLE,
	MACSONIC_APPLE16,
	MACSONIC_DAYNA,
	MACSONIC_DAYNALINK
पूर्ण;

/* For the built-in SONIC in the Duo Dock */
#घोषणा DUODOCK_SONIC_REGISTERS 0xe10000
#घोषणा DUODOCK_SONIC_PROM_BASE 0xe12000

/* For Apple-style NuBus SONIC */
#घोषणा APPLE_SONIC_REGISTERS	0
#घोषणा APPLE_SONIC_PROM_BASE	0x40000

/* Daynalink LC SONIC */
#घोषणा DAYNALINK_PROM_BASE 0x400000

/* For Dayna-style NuBus SONIC (haven't seen one yet) */
#घोषणा DAYNA_SONIC_REGISTERS   0x180000
/* This is what OpenBSD says.  However, this is definitely in NuBus
   ROM space so we should be able to get it by walking the NuBus
   resource directories */
#घोषणा DAYNA_SONIC_MAC_ADDR	0xffe004

#घोषणा SONIC_READ_PROM(addr) nubus_पढ़ोb(prom_addr+addr)

/*
 * For reversing the PROM address
 */

अटल अंतरभूत व्योम bit_reverse_addr(अचिन्हित अक्षर addr[6])
अणु
	पूर्णांक i;

	क्रम(i = 0; i < 6; i++)
		addr[i] = bitrev8(addr[i]);
पूर्ण

अटल पूर्णांक macsonic_खोलो(काष्ठा net_device* dev)
अणु
	पूर्णांक retval;

	retval = request_irq(dev->irq, sonic_पूर्णांकerrupt, 0, "sonic", dev);
	अगर (retval) अणु
		prपूर्णांकk(KERN_ERR "%s: unable to get IRQ %d.\n",
				dev->name, dev->irq);
		जाओ err;
	पूर्ण
	/* Under the A/UX पूर्णांकerrupt scheme, the onboard SONIC पूर्णांकerrupt माला_लो
	 * moved from level 2 to level 3. Unक्रमtunately we still get some
	 * level 2 पूर्णांकerrupts so रेजिस्टर the handler क्रम both.
	 */
	अगर (dev->irq == IRQ_AUTO_3) अणु
		retval = request_irq(IRQ_NUBUS_9, sonic_पूर्णांकerrupt, 0,
				     "sonic", dev);
		अगर (retval) अणु
			prपूर्णांकk(KERN_ERR "%s: unable to get IRQ %d.\n",
					dev->name, IRQ_NUBUS_9);
			जाओ err_irq;
		पूर्ण
	पूर्ण
	retval = sonic_खोलो(dev);
	अगर (retval)
		जाओ err_irq_nubus;
	वापस 0;

err_irq_nubus:
	अगर (dev->irq == IRQ_AUTO_3)
		मुक्त_irq(IRQ_NUBUS_9, dev);
err_irq:
	मुक्त_irq(dev->irq, dev);
err:
	वापस retval;
पूर्ण

अटल पूर्णांक macsonic_बंद(काष्ठा net_device* dev)
अणु
	पूर्णांक err;
	err = sonic_बंद(dev);
	मुक्त_irq(dev->irq, dev);
	अगर (dev->irq == IRQ_AUTO_3)
		मुक्त_irq(IRQ_NUBUS_9, dev);
	वापस err;
पूर्ण

अटल स्थिर काष्ठा net_device_ops macsonic_netdev_ops = अणु
	.nकरो_खोलो		= macsonic_खोलो,
	.nकरो_stop		= macsonic_बंद,
	.nकरो_start_xmit		= sonic_send_packet,
	.nकरो_set_rx_mode	= sonic_multicast_list,
	.nकरो_tx_समयout		= sonic_tx_समयout,
	.nकरो_get_stats		= sonic_get_stats,
	.nकरो_validate_addr	= eth_validate_addr,
	.nकरो_set_mac_address	= eth_mac_addr,
पूर्ण;

अटल पूर्णांक macsonic_init(काष्ठा net_device *dev)
अणु
	काष्ठा sonic_local* lp = netdev_priv(dev);
	पूर्णांक err = sonic_alloc_descriptors(dev);

	अगर (err)
		वापस err;

	dev->netdev_ops = &macsonic_netdev_ops;
	dev->watchकरोg_समयo = TX_TIMEOUT;

	/*
	 * clear tally counter
	 */
	SONIC_WRITE(SONIC_CRCT, 0xffff);
	SONIC_WRITE(SONIC_FAET, 0xffff);
	SONIC_WRITE(SONIC_MPT, 0xffff);

	वापस 0;
पूर्ण

#घोषणा INVALID_MAC(mac) (स_भेद(mac, "\x08\x00\x07", 3) && \
                          स_भेद(mac, "\x00\xA0\x40", 3) && \
                          स_भेद(mac, "\x00\x80\x19", 3) && \
                          स_भेद(mac, "\x00\x05\x02", 3))

अटल व्योम mac_onboard_sonic_ethernet_addr(काष्ठा net_device *dev)
अणु
	काष्ठा sonic_local *lp = netdev_priv(dev);
	स्थिर पूर्णांक prom_addr = ONBOARD_SONIC_PROM_BASE;
	अचिन्हित लघु val;

	/*
	 * On NuBus boards we can someबार look in the ROM resources.
	 * No such luck क्रम comm-slot/onboard.
	 * On the PowerBook 520, the PROM base address is a mystery.
	 */
	अगर (hwreg_present((व्योम *)prom_addr)) अणु
		पूर्णांक i;

		क्रम (i = 0; i < 6; i++)
			dev->dev_addr[i] = SONIC_READ_PROM(i);
		अगर (!INVALID_MAC(dev->dev_addr))
			वापस;

		/*
		 * Most of the समय, the address is bit-reversed. The NetBSD
		 * source has a rather दीर्घ and detailed historical account of
		 * why this is so.
		 */
		bit_reverse_addr(dev->dev_addr);
		अगर (!INVALID_MAC(dev->dev_addr))
			वापस;

		/*
		 * If we still have what seems to be a bogus address, we'll
		 * look in the CAM. The top entry should be ours.
		 */
		prपूर्णांकk(KERN_WARNING "macsonic: MAC address in PROM seems "
		                    "to be invalid, trying CAM\n");
	पूर्ण अन्यथा अणु
		prपूर्णांकk(KERN_WARNING "macsonic: cannot read MAC address from "
		                    "PROM, trying CAM\n");
	पूर्ण

	/* This only works अगर MacOS has alपढ़ोy initialized the card. */

	SONIC_WRITE(SONIC_CMD, SONIC_CR_RST);
	SONIC_WRITE(SONIC_CEP, 15);

	val = SONIC_READ(SONIC_CAP2);
	dev->dev_addr[5] = val >> 8;
	dev->dev_addr[4] = val & 0xff;
	val = SONIC_READ(SONIC_CAP1);
	dev->dev_addr[3] = val >> 8;
	dev->dev_addr[2] = val & 0xff;
	val = SONIC_READ(SONIC_CAP0);
	dev->dev_addr[1] = val >> 8;
	dev->dev_addr[0] = val & 0xff;

	अगर (!INVALID_MAC(dev->dev_addr))
		वापस;

	/* Still nonsense ... messed up someplace! */

	prपूर्णांकk(KERN_WARNING "macsonic: MAC address in CAM entry 15 "
	                    "seems invalid, will use a random MAC\n");
	eth_hw_addr_अक्रमom(dev);
पूर्ण

अटल पूर्णांक mac_onboard_sonic_probe(काष्ठा net_device *dev)
अणु
	काष्ठा sonic_local* lp = netdev_priv(dev);
	पूर्णांक sr;
	bool commslot = macपूर्णांकosh_config->expansion_type == MAC_EXP_PDS_COMM;

	/* Bogus probing, on the models which may or may not have
	   Ethernet (BTW, the Ethernet *is* always at the same
	   address, and nothing अन्यथा lives there, at least अगर Apple's
	   करोcumentation is to be believed) */
	अगर (commslot || macपूर्णांकosh_config->ident == MAC_MODEL_C610) अणु
		पूर्णांक card_present;

		card_present = hwreg_present((व्योम*)ONBOARD_SONIC_REGISTERS);
		अगर (!card_present) अणु
			pr_info("Onboard/comm-slot SONIC not found\n");
			वापस -ENODEV;
		पूर्ण
	पूर्ण

	/* Danger!  My arms are flailing wildly!  You *must* set lp->reg_offset
	 * and dev->base_addr beक्रमe using SONIC_READ() or SONIC_WRITE() */
	dev->base_addr = ONBOARD_SONIC_REGISTERS;
	अगर (via_alt_mapping)
		dev->irq = IRQ_AUTO_3;
	अन्यथा
		dev->irq = IRQ_NUBUS_9;

	/* The PowerBook's SONIC is 16 bit always. */
	अगर (macपूर्णांकosh_config->ident == MAC_MODEL_PB520) अणु
		lp->reg_offset = 0;
		lp->dma_biपंचांगode = SONIC_BITMODE16;
	पूर्ण अन्यथा अगर (commslot) अणु
		/* Some of the comm-slot cards are 16 bit.  But some
		   of them are not.  The 32-bit cards use offset 2 and
		   have known revisions, we try पढ़ोing the revision
		   रेजिस्टर at offset 2, अगर we करोn't get a known revision
		   we assume 16 bit at offset 0.  */
		lp->reg_offset = 2;
		lp->dma_biपंचांगode = SONIC_BITMODE16;

		sr = SONIC_READ(SONIC_SR);
		अगर (sr == 0x0004 || sr == 0x0006 || sr == 0x0100 || sr == 0x0101)
			/* 83932 is 0x0004 or 0x0006, 83934 is 0x0100 or 0x0101 */
			lp->dma_biपंचांगode = SONIC_BITMODE32;
		अन्यथा अणु
			lp->dma_biपंचांगode = SONIC_BITMODE16;
			lp->reg_offset = 0;
		पूर्ण
	पूर्ण अन्यथा अणु
		/* All onboard cards are at offset 2 with 32 bit DMA. */
		lp->reg_offset = 2;
		lp->dma_biपंचांगode = SONIC_BITMODE32;
	पूर्ण

	pr_info("Onboard/comm-slot SONIC, revision 0x%04x, %d bit DMA, register offset %d\n",
		SONIC_READ(SONIC_SR), lp->dma_biपंचांगode ? 32 : 16,
		lp->reg_offset);

	/* This is someबार useful to find out how MacOS configured the card */
	pr_debug("%s: DCR=0x%04x, DCR2=0x%04x\n", __func__,
		 SONIC_READ(SONIC_DCR) & 0xffff,
		 SONIC_READ(SONIC_DCR2) & 0xffff);

	/* Software reset, then initialize control रेजिस्टरs. */
	SONIC_WRITE(SONIC_CMD, SONIC_CR_RST);

	SONIC_WRITE(SONIC_DCR, SONIC_DCR_EXBUS | SONIC_DCR_BMS |
	                       SONIC_DCR_RFT1  | SONIC_DCR_TFT0 |
	                       (lp->dma_biपंचांगode ? SONIC_DCR_DW : 0));

	/* This *must* be written back to in order to restore the
	 * extended programmable output bits, as it may not have been
	 * initialised since the hardware reset. */
	SONIC_WRITE(SONIC_DCR2, 0);

	/* Clear *and* disable पूर्णांकerrupts to be on the safe side */
	SONIC_WRITE(SONIC_IMR, 0);
	SONIC_WRITE(SONIC_ISR, 0x7fff);

	/* Now look क्रम the MAC address. */
	mac_onboard_sonic_ethernet_addr(dev);

	pr_info("SONIC ethernet @%08lx, MAC %pM, IRQ %d\n",
		dev->base_addr, dev->dev_addr, dev->irq);

	/* Shared init code */
	वापस macsonic_init(dev);
पूर्ण

अटल पूर्णांक mac_sonic_nubus_ethernet_addr(काष्ठा net_device *dev,
					 अचिन्हित दीर्घ prom_addr, पूर्णांक id)
अणु
	पूर्णांक i;
	क्रम(i = 0; i < 6; i++)
		dev->dev_addr[i] = SONIC_READ_PROM(i);

	/* Some of the addresses are bit-reversed */
	अगर (id != MACSONIC_DAYNA)
		bit_reverse_addr(dev->dev_addr);

	वापस 0;
पूर्ण

अटल पूर्णांक macsonic_ident(काष्ठा nubus_rsrc *fres)
अणु
	अगर (fres->dr_hw == NUBUS_DRHW_ASANTE_LC &&
	    fres->dr_sw == NUBUS_DRSW_SONIC_LC)
		वापस MACSONIC_DAYNALINK;
	अगर (fres->dr_hw == NUBUS_DRHW_SONIC &&
	    fres->dr_sw == NUBUS_DRSW_APPLE) अणु
		/* There has to be a better way to करो this... */
		अगर (म_माला(fres->board->name, "DuoDock"))
			वापस MACSONIC_DUODOCK;
		अन्यथा
			वापस MACSONIC_APPLE;
	पूर्ण

	अगर (fres->dr_hw == NUBUS_DRHW_SMC9194 &&
	    fres->dr_sw == NUBUS_DRSW_DAYNA)
		वापस MACSONIC_DAYNA;

	अगर (fres->dr_hw == NUBUS_DRHW_APPLE_SONIC_LC &&
	    fres->dr_sw == 0) अणु /* huh? */
		वापस MACSONIC_APPLE16;
	पूर्ण
	वापस -1;
पूर्ण

अटल पूर्णांक mac_sonic_nubus_probe_board(काष्ठा nubus_board *board, पूर्णांक id,
				       काष्ठा net_device *dev)
अणु
	काष्ठा sonic_local* lp = netdev_priv(dev);
	अचिन्हित दीर्घ base_addr, prom_addr;
	u16 sonic_dcr;
	पूर्णांक reg_offset, dma_biपंचांगode;

	चयन (id) अणु
	हाल MACSONIC_DUODOCK:
		base_addr = board->slot_addr + DUODOCK_SONIC_REGISTERS;
		prom_addr = board->slot_addr + DUODOCK_SONIC_PROM_BASE;
		sonic_dcr = SONIC_DCR_EXBUS | SONIC_DCR_RFT0 | SONIC_DCR_RFT1 |
		            SONIC_DCR_TFT0;
		reg_offset = 2;
		dma_biपंचांगode = SONIC_BITMODE32;
		अवरोध;
	हाल MACSONIC_APPLE:
		base_addr = board->slot_addr + APPLE_SONIC_REGISTERS;
		prom_addr = board->slot_addr + APPLE_SONIC_PROM_BASE;
		sonic_dcr = SONIC_DCR_BMS | SONIC_DCR_RFT1 | SONIC_DCR_TFT0;
		reg_offset = 0;
		dma_biपंचांगode = SONIC_BITMODE32;
		अवरोध;
	हाल MACSONIC_APPLE16:
		base_addr = board->slot_addr + APPLE_SONIC_REGISTERS;
		prom_addr = board->slot_addr + APPLE_SONIC_PROM_BASE;
		sonic_dcr = SONIC_DCR_EXBUS | SONIC_DCR_RFT1 | SONIC_DCR_TFT0 |
		            SONIC_DCR_PO1 | SONIC_DCR_BMS;
		reg_offset = 0;
		dma_biपंचांगode = SONIC_BITMODE16;
		अवरोध;
	हाल MACSONIC_DAYNALINK:
		base_addr = board->slot_addr + APPLE_SONIC_REGISTERS;
		prom_addr = board->slot_addr + DAYNALINK_PROM_BASE;
		sonic_dcr = SONIC_DCR_RFT1 | SONIC_DCR_TFT0 |
		            SONIC_DCR_PO1 | SONIC_DCR_BMS;
		reg_offset = 0;
		dma_biपंचांगode = SONIC_BITMODE16;
		अवरोध;
	हाल MACSONIC_DAYNA:
		base_addr = board->slot_addr + DAYNA_SONIC_REGISTERS;
		prom_addr = board->slot_addr + DAYNA_SONIC_MAC_ADDR;
		sonic_dcr = SONIC_DCR_BMS |
		            SONIC_DCR_RFT1 | SONIC_DCR_TFT0 | SONIC_DCR_PO1;
		reg_offset = 0;
		dma_biपंचांगode = SONIC_BITMODE16;
		अवरोध;
	शेष:
		prपूर्णांकk(KERN_ERR "macsonic: WTF, id is %d\n", id);
		वापस -ENODEV;
	पूर्ण

	/* Danger!  My arms are flailing wildly!  You *must* set lp->reg_offset
	 * and dev->base_addr beक्रमe using SONIC_READ() or SONIC_WRITE() */
	dev->base_addr = base_addr;
	lp->reg_offset = reg_offset;
	lp->dma_biपंचांगode = dma_biपंचांगode;
	dev->irq = SLOT2IRQ(board->slot);

	dev_info(&board->dev, "%s, revision 0x%04x, %d bit DMA, register offset %d\n",
		 board->name, SONIC_READ(SONIC_SR),
		 lp->dma_biपंचांगode ? 32 : 16, lp->reg_offset);

	/* This is someबार useful to find out how MacOS configured the card */
	dev_dbg(&board->dev, "%s: DCR=0x%04x, DCR2=0x%04x\n", __func__,
		SONIC_READ(SONIC_DCR) & 0xffff,
		SONIC_READ(SONIC_DCR2) & 0xffff);

	/* Software reset, then initialize control रेजिस्टरs. */
	SONIC_WRITE(SONIC_CMD, SONIC_CR_RST);
	SONIC_WRITE(SONIC_DCR, sonic_dcr | (dma_biपंचांगode ? SONIC_DCR_DW : 0));
	/* This *must* be written back to in order to restore the
	 * extended programmable output bits, since it may not have been
	 * initialised since the hardware reset. */
	SONIC_WRITE(SONIC_DCR2, 0);

	/* Clear *and* disable पूर्णांकerrupts to be on the safe side */
	SONIC_WRITE(SONIC_IMR, 0);
	SONIC_WRITE(SONIC_ISR, 0x7fff);

	/* Now look क्रम the MAC address. */
	अगर (mac_sonic_nubus_ethernet_addr(dev, prom_addr, id) != 0)
		वापस -ENODEV;

	dev_info(&board->dev, "SONIC ethernet @%08lx, MAC %pM, IRQ %d\n",
		 dev->base_addr, dev->dev_addr, dev->irq);

	/* Shared init code */
	वापस macsonic_init(dev);
पूर्ण

अटल पूर्णांक mac_sonic_platक्रमm_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा net_device *dev;
	काष्ठा sonic_local *lp;
	पूर्णांक err;

	dev = alloc_etherdev(माप(काष्ठा sonic_local));
	अगर (!dev)
		वापस -ENOMEM;

	lp = netdev_priv(dev);
	lp->device = &pdev->dev;
	SET_NETDEV_DEV(dev, &pdev->dev);
	platक्रमm_set_drvdata(pdev, dev);

	err = mac_onboard_sonic_probe(dev);
	अगर (err)
		जाओ out;

	sonic_msg_init(dev);

	err = रेजिस्टर_netdev(dev);
	अगर (err)
		जाओ unकरो_probe;

	वापस 0;

unकरो_probe:
	dma_मुक्त_coherent(lp->device,
			  SIZखातापूर्ण_SONIC_DESC * SONIC_BUS_SCALE(lp->dma_biपंचांगode),
			  lp->descriptors, lp->descriptors_laddr);
out:
	मुक्त_netdev(dev);

	वापस err;
पूर्ण

MODULE_DESCRIPTION("Macintosh SONIC ethernet driver");
MODULE_ALIAS("platform:macsonic");

#समावेश "sonic.c"

अटल पूर्णांक mac_sonic_platक्रमm_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा net_device *dev = platक्रमm_get_drvdata(pdev);
	काष्ठा sonic_local* lp = netdev_priv(dev);

	unरेजिस्टर_netdev(dev);
	dma_मुक्त_coherent(lp->device, SIZखातापूर्ण_SONIC_DESC * SONIC_BUS_SCALE(lp->dma_biपंचांगode),
	                  lp->descriptors, lp->descriptors_laddr);
	मुक्त_netdev(dev);

	वापस 0;
पूर्ण

अटल काष्ठा platक्रमm_driver mac_sonic_platक्रमm_driver = अणु
	.probe  = mac_sonic_platक्रमm_probe,
	.हटाओ = mac_sonic_platक्रमm_हटाओ,
	.driver = अणु
		.name = "macsonic",
	पूर्ण,
पूर्ण;

अटल पूर्णांक mac_sonic_nubus_probe(काष्ठा nubus_board *board)
अणु
	काष्ठा net_device *ndev;
	काष्ठा sonic_local *lp;
	काष्ठा nubus_rsrc *fres;
	पूर्णांक id = -1;
	पूर्णांक err;

	/* The platक्रमm driver will handle a PDS or Comm Slot card (even अगर
	 * it has a pseuकरोslot declaration ROM).
	 */
	अगर (macपूर्णांकosh_config->expansion_type == MAC_EXP_PDS_COMM)
		वापस -ENODEV;

	क्रम_each_board_func_rsrc(board, fres) अणु
		अगर (fres->category != NUBUS_CAT_NETWORK ||
		    fres->type != NUBUS_TYPE_ETHERNET)
			जारी;

		id = macsonic_ident(fres);
		अगर (id != -1)
			अवरोध;
	पूर्ण
	अगर (!fres)
		वापस -ENODEV;

	ndev = alloc_etherdev(माप(काष्ठा sonic_local));
	अगर (!ndev)
		वापस -ENOMEM;

	lp = netdev_priv(ndev);
	lp->device = &board->dev;
	SET_NETDEV_DEV(ndev, &board->dev);

	err = mac_sonic_nubus_probe_board(board, id, ndev);
	अगर (err)
		जाओ out;

	sonic_msg_init(ndev);

	err = रेजिस्टर_netdev(ndev);
	अगर (err)
		जाओ unकरो_probe;

	nubus_set_drvdata(board, ndev);

	वापस 0;

unकरो_probe:
	dma_मुक्त_coherent(lp->device,
			  SIZखातापूर्ण_SONIC_DESC * SONIC_BUS_SCALE(lp->dma_biपंचांगode),
			  lp->descriptors, lp->descriptors_laddr);
out:
	मुक्त_netdev(ndev);
	वापस err;
पूर्ण

अटल पूर्णांक mac_sonic_nubus_हटाओ(काष्ठा nubus_board *board)
अणु
	काष्ठा net_device *ndev = nubus_get_drvdata(board);
	काष्ठा sonic_local *lp = netdev_priv(ndev);

	unरेजिस्टर_netdev(ndev);
	dma_मुक्त_coherent(lp->device,
			  SIZखातापूर्ण_SONIC_DESC * SONIC_BUS_SCALE(lp->dma_biपंचांगode),
			  lp->descriptors, lp->descriptors_laddr);
	मुक्त_netdev(ndev);

	वापस 0;
पूर्ण

अटल काष्ठा nubus_driver mac_sonic_nubus_driver = अणु
	.probe  = mac_sonic_nubus_probe,
	.हटाओ = mac_sonic_nubus_हटाओ,
	.driver = अणु
		.name = "macsonic-nubus",
		.owner = THIS_MODULE,
	पूर्ण,
पूर्ण;

अटल पूर्णांक perr, nerr;

अटल पूर्णांक __init mac_sonic_init(व्योम)
अणु
	perr = platक्रमm_driver_रेजिस्टर(&mac_sonic_platक्रमm_driver);
	nerr = nubus_driver_रेजिस्टर(&mac_sonic_nubus_driver);
	वापस 0;
पूर्ण
module_init(mac_sonic_init);

अटल व्योम __निकास mac_sonic_निकास(व्योम)
अणु
	अगर (!perr)
		platक्रमm_driver_unरेजिस्टर(&mac_sonic_platक्रमm_driver);
	अगर (!nerr)
		nubus_driver_unरेजिस्टर(&mac_sonic_nubus_driver);
पूर्ण
module_निकास(mac_sonic_निकास);
