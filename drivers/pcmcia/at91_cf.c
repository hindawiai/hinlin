<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * at91_cf.c -- AT91 CompactFlash controller driver
 *
 * Copyright (C) 2005 David Brownell
 */

#समावेश <linux/module.h>
#समावेश <linux/kernel.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/init.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/slab.h>
#समावेश <linux/gpपन.स>
#समावेश <linux/पन.स>
#समावेश <linux/sizes.h>
#समावेश <linux/mfd/syscon.h>
#समावेश <linux/mfd/syscon/aपंचांगel-mc.h>
#समावेश <linux/of.h>
#समावेश <linux/of_device.h>
#समावेश <linux/of_gpपन.स>
#समावेश <linux/regmap.h>

#समावेश <pcmcia/ss.h>

/*
 * A0..A10 work in each range; A23 indicates I/O space;  A25 is CFRNW;
 * some other bit in अणुA24,A22..A11पूर्ण is nREG to flag memory access
 * (vs attributes).  So more than 2KB/region would just be waste.
 * Note: These are offsets from the physical base address.
 */
#घोषणा	CF_ATTR_PHYS	(0)
#घोषणा	CF_IO_PHYS	(1 << 23)
#घोषणा	CF_MEM_PHYS	(0x017ff800)

काष्ठा at91_cf_data अणु
	पूर्णांक	irq_pin;		/* I/O IRQ */
	पूर्णांक	det_pin;		/* Card detect */
	पूर्णांक	vcc_pin;		/* घातer चयनing */
	पूर्णांक	rst_pin;		/* card reset */
	u8	chipselect;		/* EBI Chip Select number */
	u8	flags;
#घोषणा AT91_CF_TRUE_IDE	0x01
#घोषणा AT91_IDE_SWAP_A0_A2	0x02
पूर्ण;

काष्ठा regmap *mc;

/*--------------------------------------------------------------------------*/

काष्ठा at91_cf_socket अणु
	काष्ठा pcmcia_socket	socket;

	अचिन्हित		present:1;

	काष्ठा platक्रमm_device	*pdev;
	काष्ठा at91_cf_data	*board;

	अचिन्हित दीर्घ		phys_baseaddr;
पूर्ण;

अटल अंतरभूत पूर्णांक at91_cf_present(काष्ठा at91_cf_socket *cf)
अणु
	वापस !gpio_get_value(cf->board->det_pin);
पूर्ण

/*--------------------------------------------------------------------------*/

अटल पूर्णांक at91_cf_ss_init(काष्ठा pcmcia_socket *s)
अणु
	वापस 0;
पूर्ण

अटल irqवापस_t at91_cf_irq(पूर्णांक irq, व्योम *_cf)
अणु
	काष्ठा at91_cf_socket *cf = _cf;

	अगर (irq == gpio_to_irq(cf->board->det_pin)) अणु
		अचिन्हित present = at91_cf_present(cf);

		/* kick pccard as needed */
		अगर (present != cf->present) अणु
			cf->present = present;
			dev_dbg(&cf->pdev->dev, "card %s\n",
					present ? "present" : "gone");
			pcmcia_parse_events(&cf->socket, SS_DETECT);
		पूर्ण
	पूर्ण

	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक at91_cf_get_status(काष्ठा pcmcia_socket *s, u_पूर्णांक *sp)
अणु
	काष्ठा at91_cf_socket	*cf;

	अगर (!sp)
		वापस -EINVAL;

	cf = container_of(s, काष्ठा at91_cf_socket, socket);

	/* NOTE: CF is always 3VCARD */
	अगर (at91_cf_present(cf)) अणु
		पूर्णांक rdy	= gpio_is_valid(cf->board->irq_pin);	/* RDY/nIRQ */
		पूर्णांक vcc	= gpio_is_valid(cf->board->vcc_pin);

		*sp = SS_DETECT | SS_3VCARD;
		अगर (!rdy || gpio_get_value(cf->board->irq_pin))
			*sp |= SS_READY;
		अगर (!vcc || gpio_get_value(cf->board->vcc_pin))
			*sp |= SS_POWERON;
	पूर्ण अन्यथा
		*sp = 0;

	वापस 0;
पूर्ण

अटल पूर्णांक
at91_cf_set_socket(काष्ठा pcmcia_socket *sock, काष्ठा socket_state_t *s)
अणु
	काष्ठा at91_cf_socket	*cf;

	cf = container_of(sock, काष्ठा at91_cf_socket, socket);

	/* चयन Vcc अगर needed and possible */
	अगर (gpio_is_valid(cf->board->vcc_pin)) अणु
		चयन (s->Vcc) अणु
		हाल 0:
			gpio_set_value(cf->board->vcc_pin, 0);
			अवरोध;
		हाल 33:
			gpio_set_value(cf->board->vcc_pin, 1);
			अवरोध;
		शेष:
			वापस -EINVAL;
		पूर्ण
	पूर्ण

	/* toggle reset अगर needed */
	gpio_set_value(cf->board->rst_pin, s->flags & SS_RESET);

	dev_dbg(&cf->pdev->dev, "Vcc %d, io_irq %d, flags %04x csc %04x\n",
				s->Vcc, s->io_irq, s->flags, s->csc_mask);

	वापस 0;
पूर्ण

अटल पूर्णांक at91_cf_ss_suspend(काष्ठा pcmcia_socket *s)
अणु
	वापस at91_cf_set_socket(s, &dead_socket);
पूर्ण

/* we alपढ़ोy mapped the I/O region */
अटल पूर्णांक at91_cf_set_io_map(काष्ठा pcmcia_socket *s, काष्ठा pccard_io_map *io)
अणु
	काष्ठा at91_cf_socket	*cf;
	u32			csr;

	cf = container_of(s, काष्ठा at91_cf_socket, socket);
	io->flags &= (MAP_ACTIVE | MAP_16BIT | MAP_AUTOSZ);

	/*
	 * Use 16 bit accesses unless/until we need 8-bit i/o space.
	 *
	 * NOTE: this CF controller ignores IOIS16, so we can't really करो
	 * MAP_AUTOSZ.  The 16bit mode allows single byte access on either
	 * D0-D7 (even addr) or D8-D15 (odd), so it's बंद enough क्रम many
	 * purposes (and handles ide-cs).
	 *
	 * The 8bit mode is needed क्रम odd byte access on D0-D7.  It seems
	 * some cards only like that way to get at the odd byte, despite
	 * CF 3.0 spec table 35 also giving the D8-D15 option.
	 */
	अगर (!(io->flags & (MAP_16BIT | MAP_AUTOSZ))) अणु
		csr = AT91_MC_SMC_DBW_8;
		dev_dbg(&cf->pdev->dev, "8bit i/o bus\n");
	पूर्ण अन्यथा अणु
		csr = AT91_MC_SMC_DBW_16;
		dev_dbg(&cf->pdev->dev, "16bit i/o bus\n");
	पूर्ण
	regmap_update_bits(mc, AT91_MC_SMC_CSR(cf->board->chipselect),
			   AT91_MC_SMC_DBW, csr);

	io->start = cf->socket.io_offset;
	io->stop = io->start + SZ_2K - 1;

	वापस 0;
पूर्ण

/* pcmcia layer maps/unmaps mem regions */
अटल पूर्णांक
at91_cf_set_mem_map(काष्ठा pcmcia_socket *s, काष्ठा pccard_mem_map *map)
अणु
	काष्ठा at91_cf_socket	*cf;

	अगर (map->card_start)
		वापस -EINVAL;

	cf = container_of(s, काष्ठा at91_cf_socket, socket);

	map->flags &= (MAP_ACTIVE | MAP_ATTRIB | MAP_16BIT);
	अगर (map->flags & MAP_ATTRIB)
		map->अटल_start = cf->phys_baseaddr + CF_ATTR_PHYS;
	अन्यथा
		map->अटल_start = cf->phys_baseaddr + CF_MEM_PHYS;

	वापस 0;
पूर्ण

अटल काष्ठा pccard_operations at91_cf_ops = अणु
	.init			= at91_cf_ss_init,
	.suspend		= at91_cf_ss_suspend,
	.get_status		= at91_cf_get_status,
	.set_socket		= at91_cf_set_socket,
	.set_io_map		= at91_cf_set_io_map,
	.set_mem_map		= at91_cf_set_mem_map,
पूर्ण;

/*--------------------------------------------------------------------------*/

अटल स्थिर काष्ठा of_device_id at91_cf_dt_ids[] = अणु
	अणु .compatible = "atmel,at91rm9200-cf" पूर्ण,
	अणु /* sentinel */ पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, at91_cf_dt_ids);

अटल पूर्णांक at91_cf_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा at91_cf_socket	*cf;
	काष्ठा at91_cf_data	*board;
	काष्ठा resource		*io;
	पूर्णांक			status;

	board = devm_kzalloc(&pdev->dev, माप(*board), GFP_KERNEL);
	अगर (!board)
		वापस -ENOMEM;

	board->irq_pin = of_get_gpio(pdev->dev.of_node, 0);
	board->det_pin = of_get_gpio(pdev->dev.of_node, 1);
	board->vcc_pin = of_get_gpio(pdev->dev.of_node, 2);
	board->rst_pin = of_get_gpio(pdev->dev.of_node, 3);

	mc = syscon_regmap_lookup_by_compatible("atmel,at91rm9200-sdramc");
	अगर (IS_ERR(mc))
		वापस PTR_ERR(mc);

	अगर (!gpio_is_valid(board->det_pin) || !gpio_is_valid(board->rst_pin))
		वापस -ENODEV;

	io = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);
	अगर (!io)
		वापस -ENODEV;

	cf = devm_kzalloc(&pdev->dev, माप(*cf), GFP_KERNEL);
	अगर (!cf)
		वापस -ENOMEM;

	cf->board = board;
	cf->pdev = pdev;
	cf->phys_baseaddr = io->start;
	platक्रमm_set_drvdata(pdev, cf);

	/* must be a GPIO; ergo must trigger on both edges */
	status = devm_gpio_request(&pdev->dev, board->det_pin, "cf_det");
	अगर (status < 0)
		वापस status;

	status = devm_request_irq(&pdev->dev, gpio_to_irq(board->det_pin),
					at91_cf_irq, 0, "at91_cf detect", cf);
	अगर (status < 0)
		वापस status;

	device_init_wakeup(&pdev->dev, 1);

	status = devm_gpio_request(&pdev->dev, board->rst_pin, "cf_rst");
	अगर (status < 0)
		जाओ fail0a;

	अगर (gpio_is_valid(board->vcc_pin)) अणु
		status = devm_gpio_request(&pdev->dev, board->vcc_pin, "cf_vcc");
		अगर (status < 0)
			जाओ fail0a;
	पूर्ण

	/*
	 * The card driver will request this irq later as needed.
	 * but it causes lots of "irqNN: nobody cared" messages
	 * unless we report that we handle everything (sigh).
	 * (Note:  DK board करोesn't wire the IRQ pin...)
	 */
	अगर (gpio_is_valid(board->irq_pin)) अणु
		status = devm_gpio_request(&pdev->dev, board->irq_pin, "cf_irq");
		अगर (status < 0)
			जाओ fail0a;

		status = devm_request_irq(&pdev->dev, gpio_to_irq(board->irq_pin),
					at91_cf_irq, IRQF_SHARED, "at91_cf", cf);
		अगर (status < 0)
			जाओ fail0a;
		cf->socket.pci_irq = gpio_to_irq(board->irq_pin);
	पूर्ण अन्यथा
		cf->socket.pci_irq = nr_irqs + 1;

	/*
	 * pcmcia layer only remaps "real" memory not iospace
	 * io_offset is set to 0x10000 to aव्योम the check in अटल_find_io().
	 * */
	cf->socket.io_offset = 0x10000;
	status = pci_ioremap_io(0x10000, cf->phys_baseaddr + CF_IO_PHYS);
	अगर (status)
		जाओ fail0a;

	/* reserve chip-select regions */
	अगर (!devm_request_mem_region(&pdev->dev, io->start, resource_size(io), "at91_cf")) अणु
		status = -ENXIO;
		जाओ fail0a;
	पूर्ण

	dev_info(&pdev->dev, "irqs det #%d, io #%d\n",
		gpio_to_irq(board->det_pin), gpio_to_irq(board->irq_pin));

	cf->socket.owner = THIS_MODULE;
	cf->socket.dev.parent = &pdev->dev;
	cf->socket.ops = &at91_cf_ops;
	cf->socket.resource_ops = &pccard_अटल_ops;
	cf->socket.features = SS_CAP_PCCARD | SS_CAP_STATIC_MAP
				| SS_CAP_MEM_ALIGN;
	cf->socket.map_size = SZ_2K;
	cf->socket.io[0].res = io;

	status = pcmcia_रेजिस्टर_socket(&cf->socket);
	अगर (status < 0)
		जाओ fail0a;

	वापस 0;

fail0a:
	device_init_wakeup(&pdev->dev, 0);
	वापस status;
पूर्ण

अटल पूर्णांक at91_cf_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा at91_cf_socket	*cf = platक्रमm_get_drvdata(pdev);

	pcmcia_unरेजिस्टर_socket(&cf->socket);
	device_init_wakeup(&pdev->dev, 0);

	वापस 0;
पूर्ण

#अगर_घोषित	CONFIG_PM

अटल पूर्णांक at91_cf_suspend(काष्ठा platक्रमm_device *pdev, pm_message_t mesg)
अणु
	काष्ठा at91_cf_socket	*cf = platक्रमm_get_drvdata(pdev);
	काष्ठा at91_cf_data	*board = cf->board;

	अगर (device_may_wakeup(&pdev->dev)) अणु
		enable_irq_wake(gpio_to_irq(board->det_pin));
		अगर (gpio_is_valid(board->irq_pin))
			enable_irq_wake(gpio_to_irq(board->irq_pin));
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक at91_cf_resume(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा at91_cf_socket	*cf = platक्रमm_get_drvdata(pdev);
	काष्ठा at91_cf_data	*board = cf->board;

	अगर (device_may_wakeup(&pdev->dev)) अणु
		disable_irq_wake(gpio_to_irq(board->det_pin));
		अगर (gpio_is_valid(board->irq_pin))
			disable_irq_wake(gpio_to_irq(board->irq_pin));
	पूर्ण

	वापस 0;
पूर्ण

#अन्यथा
#घोषणा	at91_cf_suspend		शून्य
#घोषणा	at91_cf_resume		शून्य
#पूर्ण_अगर

अटल काष्ठा platक्रमm_driver at91_cf_driver = अणु
	.driver = अणु
		.name		= "at91_cf",
		.of_match_table = at91_cf_dt_ids,
	पूर्ण,
	.probe		= at91_cf_probe,
	.हटाओ		= at91_cf_हटाओ,
	.suspend	= at91_cf_suspend,
	.resume		= at91_cf_resume,
पूर्ण;

module_platक्रमm_driver(at91_cf_driver);

MODULE_DESCRIPTION("AT91 Compact Flash Driver");
MODULE_AUTHOR("David Brownell");
MODULE_LICENSE("GPL");
MODULE_ALIAS("platform:at91_cf");
