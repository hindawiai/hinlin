<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * xtsonic.c
 *
 * (C) 2001 - 2007 Tensilica Inc.
 *	Kevin Chea <kchea@yahoo.com>
 *	Marc Gauthier <marc@linux-xtensa.org>
 *	Chris Zankel <chris@zankel.net>
 *
 * (C) 1996,1998 by Thomas Bogenकरोerfer (tsbogend@alpha.franken.de)
 *
 * This driver is based on work from Andreas Busse, but most of
 * the code is rewritten.
 *
 * (C) 1995 by Andreas Busse (andy@walकरोrf-gmbh.de)
 *
 * A driver क्रम the onboard Sonic ethernet controller on the XT2000.
 */

#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/types.h>
#समावेश <linux/fcntl.h>
#समावेश <linux/gfp.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/init.h>
#समावेश <linux/ioport.h>
#समावेश <linux/in.h>
#समावेश <linux/माला.स>
#समावेश <linux/delay.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/netdevice.h>
#समावेश <linux/etherdevice.h>
#समावेश <linux/skbuff.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/dma-mapping.h>
#समावेश <linux/slab.h>
#समावेश <linux/pgtable.h>

#समावेश <यंत्र/पन.स>
#समावेश <यंत्र/dma.h>

अटल अक्षर xtsonic_string[] = "xtsonic";

बाह्य अचिन्हित xtboard_nvram_valid(व्योम);
बाह्य व्योम xtboard_get_ether_addr(अचिन्हित अक्षर *buf);

#समावेश "sonic.h"

/*
 * According to the करोcumentation क्रम the Sonic ethernet controller,
 * EOBC should be 760 words (1520 bytes) क्रम 32-bit applications, and,
 * as such, 2 words less than the buffer size. The value क्रम RBSIZE
 * defined in sonic.h, however is only 1520.
 *
 * (Note that in 16-bit configurations, EOBC is 759 words (1518 bytes) and
 * RBSIZE 1520 bytes)
 */
#अघोषित SONIC_RBSIZE
#घोषणा SONIC_RBSIZE	1524

/*
 * The chip provides 256 byte रेजिस्टर space.
 */
#घोषणा SONIC_MEM_SIZE	0x100

/*
 * Macros to access SONIC रेजिस्टरs
 */
#घोषणा SONIC_READ(reg) \
	(0xffff & *((अस्थिर अचिन्हित पूर्णांक *)dev->base_addr+reg))

#घोषणा SONIC_WRITE(reg,val) \
	*((अस्थिर अचिन्हित पूर्णांक *)dev->base_addr+reg) = val

/*
 * We cannot use station (ethernet) address prefixes to detect the
 * sonic controller since these are board manufacturer depended.
 * So we check क्रम known Silicon Revision IDs instead.
 */
अटल अचिन्हित लघु known_revisions[] =
अणु
	0x101,			/* SONIC 83934 */
	0xffff			/* end of list */
पूर्ण;

अटल पूर्णांक xtsonic_खोलो(काष्ठा net_device *dev)
अणु
	पूर्णांक retval;

	retval = request_irq(dev->irq, sonic_पूर्णांकerrupt, 0, "sonic", dev);
	अगर (retval) अणु
		prपूर्णांकk(KERN_ERR "%s: unable to get IRQ %d.\n",
		       dev->name, dev->irq);
		वापस -EAGAIN;
	पूर्ण

	retval = sonic_खोलो(dev);
	अगर (retval)
		मुक्त_irq(dev->irq, dev);
	वापस retval;
पूर्ण

अटल पूर्णांक xtsonic_बंद(काष्ठा net_device *dev)
अणु
	पूर्णांक err;
	err = sonic_बंद(dev);
	मुक्त_irq(dev->irq, dev);
	वापस err;
पूर्ण

अटल स्थिर काष्ठा net_device_ops xtsonic_netdev_ops = अणु
	.nकरो_खोलो		= xtsonic_खोलो,
	.nकरो_stop		= xtsonic_बंद,
	.nकरो_start_xmit		= sonic_send_packet,
	.nकरो_get_stats		= sonic_get_stats,
	.nकरो_set_rx_mode	= sonic_multicast_list,
	.nकरो_tx_समयout		= sonic_tx_समयout,
	.nकरो_validate_addr	= eth_validate_addr,
	.nकरो_set_mac_address	= eth_mac_addr,
पूर्ण;

अटल पूर्णांक __init sonic_probe1(काष्ठा net_device *dev)
अणु
	अचिन्हित पूर्णांक silicon_revision;
	काष्ठा sonic_local *lp = netdev_priv(dev);
	अचिन्हित पूर्णांक base_addr = dev->base_addr;
	पूर्णांक i;
	पूर्णांक err = 0;

	अगर (!request_mem_region(base_addr, 0x100, xtsonic_string))
		वापस -EBUSY;

	/*
	 * get the Silicon Revision ID. If this is one of the known
	 * one assume that we found a SONIC ethernet controller at
	 * the expected location.
	 */
	silicon_revision = SONIC_READ(SONIC_SR);
	i = 0;
	जबतक ((known_revisions[i] != 0xffff) &&
			(known_revisions[i] != silicon_revision))
		i++;

	अगर (known_revisions[i] == 0xffff) अणु
		pr_info("SONIC ethernet controller not found (0x%4x)\n",
			silicon_revision);
		वापस -ENODEV;
	पूर्ण

	/*
	 * Put the sonic पूर्णांकo software reset, then retrieve ethernet address.
	 * Note: we are assuming that the boot-loader has initialized the cam.
	 */
	SONIC_WRITE(SONIC_CMD,SONIC_CR_RST);
	SONIC_WRITE(SONIC_DCR,
		    SONIC_DCR_WC0|SONIC_DCR_DW|SONIC_DCR_LBR|SONIC_DCR_SBUS);
	SONIC_WRITE(SONIC_CEP,0);
	SONIC_WRITE(SONIC_IMR,0);

	SONIC_WRITE(SONIC_CMD,SONIC_CR_RST);
	SONIC_WRITE(SONIC_CEP,0);

	क्रम (i=0; i<3; i++) अणु
		अचिन्हित पूर्णांक val = SONIC_READ(SONIC_CAP0-i);
		dev->dev_addr[i*2] = val;
		dev->dev_addr[i*2+1] = val >> 8;
	पूर्ण

	lp->dma_biपंचांगode = SONIC_BITMODE32;

	err = sonic_alloc_descriptors(dev);
	अगर (err)
		जाओ out;

	dev->netdev_ops		= &xtsonic_netdev_ops;
	dev->watchकरोg_समयo	= TX_TIMEOUT;

	/*
	 * clear tally counter
	 */
	SONIC_WRITE(SONIC_CRCT,0xffff);
	SONIC_WRITE(SONIC_FAET,0xffff);
	SONIC_WRITE(SONIC_MPT,0xffff);

	वापस 0;
out:
	release_region(dev->base_addr, SONIC_MEM_SIZE);
	वापस err;
पूर्ण


/*
 * Probe क्रम a SONIC ethernet controller on an XT2000 board.
 * Actually probing is superfluous but we're paranoid.
 */

पूर्णांक xtsonic_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा net_device *dev;
	काष्ठा sonic_local *lp;
	काष्ठा resource *resmem, *resirq;
	पूर्णांक err = 0;

	अगर ((resmem = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0)) == शून्य)
		वापस -ENODEV;

	अगर ((resirq = platक्रमm_get_resource(pdev, IORESOURCE_IRQ, 0)) == शून्य)
		वापस -ENODEV;

	अगर ((dev = alloc_etherdev(माप(काष्ठा sonic_local))) == शून्य)
		वापस -ENOMEM;

	lp = netdev_priv(dev);
	lp->device = &pdev->dev;
	platक्रमm_set_drvdata(pdev, dev);
	SET_NETDEV_DEV(dev, &pdev->dev);
	netdev_boot_setup_check(dev);

	dev->base_addr = resmem->start;
	dev->irq = resirq->start;

	अगर ((err = sonic_probe1(dev)))
		जाओ out;

	pr_info("SONIC ethernet @%08lx, MAC %pM, IRQ %d\n",
		dev->base_addr, dev->dev_addr, dev->irq);

	sonic_msg_init(dev);

	अगर ((err = रेजिस्टर_netdev(dev)))
		जाओ unकरो_probe1;

	वापस 0;

unकरो_probe1:
	dma_मुक्त_coherent(lp->device,
			  SIZखातापूर्ण_SONIC_DESC * SONIC_BUS_SCALE(lp->dma_biपंचांगode),
			  lp->descriptors, lp->descriptors_laddr);
	release_region(dev->base_addr, SONIC_MEM_SIZE);
out:
	मुक्त_netdev(dev);

	वापस err;
पूर्ण

MODULE_DESCRIPTION("Xtensa XT2000 SONIC ethernet driver");

#समावेश "sonic.c"

अटल पूर्णांक xtsonic_device_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा net_device *dev = platक्रमm_get_drvdata(pdev);
	काष्ठा sonic_local *lp = netdev_priv(dev);

	unरेजिस्टर_netdev(dev);
	dma_मुक्त_coherent(lp->device,
			  SIZखातापूर्ण_SONIC_DESC * SONIC_BUS_SCALE(lp->dma_biपंचांगode),
			  lp->descriptors, lp->descriptors_laddr);
	release_region (dev->base_addr, SONIC_MEM_SIZE);
	मुक्त_netdev(dev);

	वापस 0;
पूर्ण

अटल काष्ठा platक्रमm_driver xtsonic_driver = अणु
	.probe = xtsonic_probe,
	.हटाओ = xtsonic_device_हटाओ,
	.driver = अणु
		.name = xtsonic_string,
	पूर्ण,
पूर्ण;

module_platक्रमm_driver(xtsonic_driver);
