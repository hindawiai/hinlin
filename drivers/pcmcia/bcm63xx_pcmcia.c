<शैली गुरु>
/*
 * This file is subject to the terms and conditions of the GNU General Public
 * License.  See the file "COPYING" in the मुख्य directory of this archive
 * क्रम more details.
 *
 * Copyright (C) 2008 Maxime Bizon <mbizon@मुक्तbox.fr>
 */

#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/ioport.h>
#समावेश <linux/समयr.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/slab.h>
#समावेश <linux/delay.h>
#समावेश <linux/pci.h>
#समावेश <linux/gpपन.स>

#समावेश <bcm63xx_regs.h>
#समावेश <bcm63xx_पन.स>
#समावेश "bcm63xx_pcmcia.h"

#घोषणा PFX	"bcm63xx_pcmcia: "

#अगर_घोषित CONFIG_CARDBUS
/* अगर cardbus is used, platक्रमm device needs reference to actual pci
 * device */
अटल काष्ठा pci_dev *bcm63xx_cb_dev;
#पूर्ण_अगर

/*
 * पढ़ो/ग_लिखो helper क्रम pcmcia regs
 */
अटल अंतरभूत u32 pcmcia_पढ़ोl(काष्ठा bcm63xx_pcmcia_socket *skt, u32 off)
अणु
	वापस bcm_पढ़ोl(skt->base + off);
पूर्ण

अटल अंतरभूत व्योम pcmcia_ग_लिखोl(काष्ठा bcm63xx_pcmcia_socket *skt,
				 u32 val, u32 off)
अणु
	bcm_ग_लिखोl(val, skt->base + off);
पूर्ण

/*
 * This callback should (re-)initialise the socket, turn on status
 * पूर्णांकerrupts and PCMCIA bus, and रुको क्रम घातer to stabilise so that
 * the card status संकेतs report correctly.
 *
 * Hardware cannot करो that.
 */
अटल पूर्णांक bcm63xx_pcmcia_sock_init(काष्ठा pcmcia_socket *sock)
अणु
	वापस 0;
पूर्ण

/*
 * This callback should हटाओ घातer on the socket, disable IRQs from
 * the card, turn off status पूर्णांकerrupts, and disable the PCMCIA bus.
 *
 * Hardware cannot करो that.
 */
अटल पूर्णांक bcm63xx_pcmcia_suspend(काष्ठा pcmcia_socket *sock)
अणु
	वापस 0;
पूर्ण

/*
 * Implements the set_socket() operation क्रम the in-kernel PCMCIA
 * service (क्रमmerly SS_SetSocket in Card Services). We more or
 * less punt all of this work and let the kernel handle the details
 * of घातer configuration, reset, &c. We also record the value of
 * `state' in order to regurgitate it to the PCMCIA core later.
 */
अटल पूर्णांक bcm63xx_pcmcia_set_socket(काष्ठा pcmcia_socket *sock,
				     socket_state_t *state)
अणु
	काष्ठा bcm63xx_pcmcia_socket *skt;
	अचिन्हित दीर्घ flags;
	u32 val;

	skt = sock->driver_data;

	spin_lock_irqsave(&skt->lock, flags);

	/* note: hardware cannot control socket घातer, so we will
	 * always report SS_POWERON */

	/* apply socket reset */
	val = pcmcia_पढ़ोl(skt, PCMCIA_C1_REG);
	अगर (state->flags & SS_RESET)
		val |= PCMCIA_C1_RESET_MASK;
	अन्यथा
		val &= ~PCMCIA_C1_RESET_MASK;

	/* reverse reset logic क्रम cardbus card */
	अगर (skt->card_detected && (skt->card_type & CARD_CARDBUS))
		val ^= PCMCIA_C1_RESET_MASK;

	pcmcia_ग_लिखोl(skt, val, PCMCIA_C1_REG);

	/* keep requested state क्रम event reporting */
	skt->requested_state = *state;

	spin_unlock_irqrestore(&skt->lock, flags);

	वापस 0;
पूर्ण

/*
 * identity cardtype from VS[12] input, CD[12] input जबतक only VS2 is
 * भग्नing, and CD[12] input जबतक only VS1 is भग्नing
 */
क्रमागत अणु
	IN_VS1 = (1 << 0),
	IN_VS2 = (1 << 1),
	IN_CD1_VS2H = (1 << 2),
	IN_CD2_VS2H = (1 << 3),
	IN_CD1_VS1H = (1 << 4),
	IN_CD2_VS1H = (1 << 5),
पूर्ण;

अटल स्थिर u8 vscd_to_cardtype[] = अणु

	/* VS1 भग्न, VS2 भग्न */
	[IN_VS1 | IN_VS2] = (CARD_PCCARD | CARD_5V),

	/* VS1 grounded, VS2 भग्न */
	[IN_VS2] = (CARD_PCCARD | CARD_5V | CARD_3V),

	/* VS1 grounded, VS2 grounded */
	[0] = (CARD_PCCARD | CARD_5V | CARD_3V | CARD_XV),

	/* VS1 tied to CD1, VS2 भग्न */
	[IN_VS1 | IN_VS2 | IN_CD1_VS1H] = (CARD_CARDBUS | CARD_3V),

	/* VS1 grounded, VS2 tied to CD2 */
	[IN_VS2 | IN_CD2_VS2H] = (CARD_CARDBUS | CARD_3V | CARD_XV),

	/* VS1 tied to CD2, VS2 grounded */
	[IN_VS1 | IN_CD2_VS1H] = (CARD_CARDBUS | CARD_3V | CARD_XV | CARD_YV),

	/* VS1 भग्न, VS2 grounded */
	[IN_VS1] = (CARD_PCCARD | CARD_XV),

	/* VS1 भग्न, VS2 tied to CD2 */
	[IN_VS1 | IN_VS2 | IN_CD2_VS2H] = (CARD_CARDBUS | CARD_3V),

	/* VS1 भग्न, VS2 tied to CD1 */
	[IN_VS1 | IN_VS2 | IN_CD1_VS2H] = (CARD_CARDBUS | CARD_XV | CARD_YV),

	/* VS1 tied to CD2, VS2 भग्न */
	[IN_VS1 | IN_VS2 | IN_CD2_VS1H] = (CARD_CARDBUS | CARD_YV),

	/* VS2 grounded, VS1 is tied to CD1, CD2 is grounded */
	[IN_VS1 | IN_CD1_VS1H] = 0, /* ignore cardbay */
पूर्ण;

/*
 * poll hardware to check card insertion status
 */
अटल अचिन्हित पूर्णांक __get_socket_status(काष्ठा bcm63xx_pcmcia_socket *skt)
अणु
	अचिन्हित पूर्णांक stat;
	u32 val;

	stat = 0;

	/* check CD क्रम card presence */
	val = pcmcia_पढ़ोl(skt, PCMCIA_C1_REG);

	अगर (!(val & PCMCIA_C1_CD1_MASK) && !(val & PCMCIA_C1_CD2_MASK))
		stat |= SS_DETECT;

	/* अगर new insertion, detect cardtype */
	अगर ((stat & SS_DETECT) && !skt->card_detected) अणु
		अचिन्हित पूर्णांक stat = 0;

		/* भग्न VS1, भग्न VS2 */
		val |= PCMCIA_C1_VS1OE_MASK;
		val |= PCMCIA_C1_VS2OE_MASK;
		pcmcia_ग_लिखोl(skt, val, PCMCIA_C1_REG);

		/* रुको क्रम output to stabilize and पढ़ो VS[12] */
		udelay(10);
		val = pcmcia_पढ़ोl(skt, PCMCIA_C1_REG);
		stat |= (val & PCMCIA_C1_VS1_MASK) ? IN_VS1 : 0;
		stat |= (val & PCMCIA_C1_VS2_MASK) ? IN_VS2 : 0;

		/* drive VS1 low, भग्न VS2 */
		val &= ~PCMCIA_C1_VS1OE_MASK;
		val |= PCMCIA_C1_VS2OE_MASK;
		pcmcia_ग_लिखोl(skt, val, PCMCIA_C1_REG);

		/* रुको क्रम output to stabilize and पढ़ो CD[12] */
		udelay(10);
		val = pcmcia_पढ़ोl(skt, PCMCIA_C1_REG);
		stat |= (val & PCMCIA_C1_CD1_MASK) ? IN_CD1_VS2H : 0;
		stat |= (val & PCMCIA_C1_CD2_MASK) ? IN_CD2_VS2H : 0;

		/* भग्न VS1, drive VS2 low */
		val |= PCMCIA_C1_VS1OE_MASK;
		val &= ~PCMCIA_C1_VS2OE_MASK;
		pcmcia_ग_लिखोl(skt, val, PCMCIA_C1_REG);

		/* रुको क्रम output to stabilize and पढ़ो CD[12] */
		udelay(10);
		val = pcmcia_पढ़ोl(skt, PCMCIA_C1_REG);
		stat |= (val & PCMCIA_C1_CD1_MASK) ? IN_CD1_VS1H : 0;
		stat |= (val & PCMCIA_C1_CD2_MASK) ? IN_CD2_VS1H : 0;

		/* guess cardtype from all this */
		skt->card_type = vscd_to_cardtype[stat];
		अगर (!skt->card_type)
			dev_err(&skt->socket.dev, "unsupported card type\n");

		/* drive both VS pin to 0 again */
		val &= ~(PCMCIA_C1_VS1OE_MASK | PCMCIA_C1_VS2OE_MASK);

		/* enable correct logic */
		val &= ~(PCMCIA_C1_EN_PCMCIA_MASK | PCMCIA_C1_EN_CARDBUS_MASK);
		अगर (skt->card_type & CARD_PCCARD)
			val |= PCMCIA_C1_EN_PCMCIA_MASK;
		अन्यथा
			val |= PCMCIA_C1_EN_CARDBUS_MASK;

		pcmcia_ग_लिखोl(skt, val, PCMCIA_C1_REG);
	पूर्ण
	skt->card_detected = (stat & SS_DETECT) ? 1 : 0;

	/* report card type/voltage */
	अगर (skt->card_type & CARD_CARDBUS)
		stat |= SS_CARDBUS;
	अगर (skt->card_type & CARD_3V)
		stat |= SS_3VCARD;
	अगर (skt->card_type & CARD_XV)
		stat |= SS_XVCARD;
	stat |= SS_POWERON;

	अगर (gpio_get_value(skt->pd->पढ़ोy_gpio))
		stat |= SS_READY;

	वापस stat;
पूर्ण

/*
 * core request to get current socket status
 */
अटल पूर्णांक bcm63xx_pcmcia_get_status(काष्ठा pcmcia_socket *sock,
				     अचिन्हित पूर्णांक *status)
अणु
	काष्ठा bcm63xx_pcmcia_socket *skt;

	skt = sock->driver_data;

	spin_lock_bh(&skt->lock);
	*status = __get_socket_status(skt);
	spin_unlock_bh(&skt->lock);

	वापस 0;
पूर्ण

/*
 * socket polling समयr callback
 */
अटल व्योम bcm63xx_pcmcia_poll(काष्ठा समयr_list *t)
अणु
	काष्ठा bcm63xx_pcmcia_socket *skt;
	अचिन्हित पूर्णांक stat, events;

	skt = from_समयr(skt, t, समयr);

	spin_lock_bh(&skt->lock);

	stat = __get_socket_status(skt);

	/* keep only changed bits, and mask with required one from the
	 * core */
	events = (stat ^ skt->old_status) & skt->requested_state.csc_mask;
	skt->old_status = stat;
	spin_unlock_bh(&skt->lock);

	अगर (events)
		pcmcia_parse_events(&skt->socket, events);

	mod_समयr(&skt->समयr,
		  jअगरfies + msecs_to_jअगरfies(BCM63XX_PCMCIA_POLL_RATE));
पूर्ण

अटल पूर्णांक bcm63xx_pcmcia_set_io_map(काष्ठा pcmcia_socket *sock,
				     काष्ठा pccard_io_map *map)
अणु
	/* this करोesn't seem to be called by pcmcia layer अगर अटल
	 * mapping is used */
	वापस 0;
पूर्ण

अटल पूर्णांक bcm63xx_pcmcia_set_mem_map(काष्ठा pcmcia_socket *sock,
				      काष्ठा pccard_mem_map *map)
अणु
	काष्ठा bcm63xx_pcmcia_socket *skt;
	काष्ठा resource *res;

	skt = sock->driver_data;
	अगर (map->flags & MAP_ATTRIB)
		res = skt->attr_res;
	अन्यथा
		res = skt->common_res;

	map->अटल_start = res->start + map->card_start;
	वापस 0;
पूर्ण

अटल काष्ठा pccard_operations bcm63xx_pcmcia_operations = अणु
	.init			= bcm63xx_pcmcia_sock_init,
	.suspend		= bcm63xx_pcmcia_suspend,
	.get_status		= bcm63xx_pcmcia_get_status,
	.set_socket		= bcm63xx_pcmcia_set_socket,
	.set_io_map		= bcm63xx_pcmcia_set_io_map,
	.set_mem_map		= bcm63xx_pcmcia_set_mem_map,
पूर्ण;

/*
 * रेजिस्टर pcmcia socket to core
 */
अटल पूर्णांक bcm63xx_drv_pcmcia_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा bcm63xx_pcmcia_socket *skt;
	काष्ठा pcmcia_socket *sock;
	काष्ठा resource *res, *irq_res;
	अचिन्हित पूर्णांक regmem_size = 0, iomem_size = 0;
	u32 val;
	पूर्णांक ret;

	skt = kzalloc(माप(*skt), GFP_KERNEL);
	अगर (!skt)
		वापस -ENOMEM;
	spin_lock_init(&skt->lock);
	sock = &skt->socket;
	sock->driver_data = skt;

	/* make sure we have all resources we need */
	skt->common_res = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 1);
	skt->attr_res = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 2);
	irq_res = platक्रमm_get_resource(pdev, IORESOURCE_IRQ, 0);
	skt->pd = pdev->dev.platक्रमm_data;
	अगर (!skt->common_res || !skt->attr_res || !irq_res || !skt->pd) अणु
		ret = -EINVAL;
		जाओ err;
	पूर्ण

	/* remap pcmcia रेजिस्टरs */
	res = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);
	regmem_size = resource_size(res);
	अगर (!request_mem_region(res->start, regmem_size, "bcm63xx_pcmcia")) अणु
		ret = -EINVAL;
		जाओ err;
	पूर्ण
	skt->reg_res = res;

	skt->base = ioremap(res->start, regmem_size);
	अगर (!skt->base) अणु
		ret = -ENOMEM;
		जाओ err;
	पूर्ण

	/* remap io रेजिस्टरs */
	res = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 3);
	iomem_size = resource_size(res);
	skt->io_base = ioremap(res->start, iomem_size);
	अगर (!skt->io_base) अणु
		ret = -ENOMEM;
		जाओ err;
	पूर्ण

	/* resources are अटल */
	sock->resource_ops = &pccard_अटल_ops;
	sock->ops = &bcm63xx_pcmcia_operations;
	sock->owner = THIS_MODULE;
	sock->dev.parent = &pdev->dev;
	sock->features = SS_CAP_STATIC_MAP | SS_CAP_PCCARD;
	sock->io_offset = (अचिन्हित दीर्घ)skt->io_base;
	sock->pci_irq = irq_res->start;

#अगर_घोषित CONFIG_CARDBUS
	sock->cb_dev = bcm63xx_cb_dev;
	अगर (bcm63xx_cb_dev)
		sock->features |= SS_CAP_CARDBUS;
#पूर्ण_अगर

	/* assume common & attribute memory have the same size */
	sock->map_size = resource_size(skt->common_res);

	/* initialize polling समयr */
	समयr_setup(&skt->समयr, bcm63xx_pcmcia_poll, 0);

	/* initialize  pcmcia  control रेजिस्टर,  drive  VS[12] to  0,
	 * leave CB IDSEL to the old  value since it is set by the PCI
	 * layer */
	val = pcmcia_पढ़ोl(skt, PCMCIA_C1_REG);
	val &= PCMCIA_C1_CBIDSEL_MASK;
	val |= PCMCIA_C1_EN_PCMCIA_GPIO_MASK;
	pcmcia_ग_लिखोl(skt, val, PCMCIA_C1_REG);

	/*
	 * Hardware has only one set of timings रेजिस्टरs, not one क्रम
	 * each memory access type, so we configure them क्रम the
	 * slowest one: attribute memory.
	 */
	val = PCMCIA_C2_DATA16_MASK;
	val |= 10 << PCMCIA_C2_RWCOUNT_SHIFT;
	val |= 6 << PCMCIA_C2_INACTIVE_SHIFT;
	val |= 3 << PCMCIA_C2_SETUP_SHIFT;
	val |= 3 << PCMCIA_C2_HOLD_SHIFT;
	pcmcia_ग_लिखोl(skt, val, PCMCIA_C2_REG);

	ret = pcmcia_रेजिस्टर_socket(sock);
	अगर (ret)
		जाओ err;

	/* start polling socket */
	mod_समयr(&skt->समयr,
		  jअगरfies + msecs_to_jअगरfies(BCM63XX_PCMCIA_POLL_RATE));

	platक्रमm_set_drvdata(pdev, skt);
	वापस 0;

err:
	अगर (skt->io_base)
		iounmap(skt->io_base);
	अगर (skt->base)
		iounmap(skt->base);
	अगर (skt->reg_res)
		release_mem_region(skt->reg_res->start, regmem_size);
	kमुक्त(skt);
	वापस ret;
पूर्ण

अटल पूर्णांक bcm63xx_drv_pcmcia_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा bcm63xx_pcmcia_socket *skt;
	काष्ठा resource *res;

	skt = platक्रमm_get_drvdata(pdev);
	del_समयr_sync(&skt->समयr);
	iounmap(skt->base);
	iounmap(skt->io_base);
	res = skt->reg_res;
	release_mem_region(res->start, resource_size(res));
	kमुक्त(skt);
	वापस 0;
पूर्ण

काष्ठा platक्रमm_driver bcm63xx_pcmcia_driver = अणु
	.probe	= bcm63xx_drv_pcmcia_probe,
	.हटाओ	= bcm63xx_drv_pcmcia_हटाओ,
	.driver	= अणु
		.name	= "bcm63xx_pcmcia",
		.owner  = THIS_MODULE,
	पूर्ण,
पूर्ण;

#अगर_घोषित CONFIG_CARDBUS
अटल पूर्णांक bcm63xx_cb_probe(काष्ठा pci_dev *dev,
				      स्थिर काष्ठा pci_device_id *id)
अणु
	/* keep pci device */
	bcm63xx_cb_dev = dev;
	वापस platक्रमm_driver_रेजिस्टर(&bcm63xx_pcmcia_driver);
पूर्ण

अटल व्योम bcm63xx_cb_निकास(काष्ठा pci_dev *dev)
अणु
	platक्रमm_driver_unरेजिस्टर(&bcm63xx_pcmcia_driver);
	bcm63xx_cb_dev = शून्य;
पूर्ण

अटल स्थिर काष्ठा pci_device_id bcm63xx_cb_table[] = अणु
	अणु
		.venकरोr		= PCI_VENDOR_ID_BROADCOM,
		.device		= BCM6348_CPU_ID,
		.subvenकरोr	= PCI_VENDOR_ID_BROADCOM,
		.subdevice	= PCI_ANY_ID,
		.class		= PCI_CLASS_BRIDGE_CARDBUS << 8,
		.class_mask	= ~0,
	पूर्ण,

	अणु
		.venकरोr		= PCI_VENDOR_ID_BROADCOM,
		.device		= BCM6358_CPU_ID,
		.subvenकरोr	= PCI_VENDOR_ID_BROADCOM,
		.subdevice	= PCI_ANY_ID,
		.class		= PCI_CLASS_BRIDGE_CARDBUS << 8,
		.class_mask	= ~0,
	पूर्ण,

	अणु पूर्ण,
पूर्ण;

MODULE_DEVICE_TABLE(pci, bcm63xx_cb_table);

अटल काष्ठा pci_driver bcm63xx_cardbus_driver = अणु
	.name		= "bcm63xx_cardbus",
	.id_table	= bcm63xx_cb_table,
	.probe		= bcm63xx_cb_probe,
	.हटाओ		= bcm63xx_cb_निकास,
पूर्ण;
#पूर्ण_अगर

/*
 * अगर cardbus support is enabled, रेजिस्टर our platक्रमm device after
 * our fake cardbus bridge has been रेजिस्टरed
 */
अटल पूर्णांक __init bcm63xx_pcmcia_init(व्योम)
अणु
#अगर_घोषित CONFIG_CARDBUS
	वापस pci_रेजिस्टर_driver(&bcm63xx_cardbus_driver);
#अन्यथा
	वापस platक्रमm_driver_रेजिस्टर(&bcm63xx_pcmcia_driver);
#पूर्ण_अगर
पूर्ण

अटल व्योम __निकास bcm63xx_pcmcia_निकास(व्योम)
अणु
#अगर_घोषित CONFIG_CARDBUS
	वापस pci_unरेजिस्टर_driver(&bcm63xx_cardbus_driver);
#अन्यथा
	platक्रमm_driver_unरेजिस्टर(&bcm63xx_pcmcia_driver);
#पूर्ण_अगर
पूर्ण

module_init(bcm63xx_pcmcia_init);
module_निकास(bcm63xx_pcmcia_निकास);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Maxime Bizon <mbizon@freebox.fr>");
MODULE_DESCRIPTION("Linux PCMCIA Card Services: bcm63xx Socket Controller");
