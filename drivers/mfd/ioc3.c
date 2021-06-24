<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * SGI IOC3 multअगरunction device driver
 *
 * Copyright (C) 2018, 2019 Thomas Bogenकरोerfer <tbogenकरोerfer@suse.de>
 *
 * Based on work by:
 *   Stanislaw Skowronek <skylark@unaligned.org>
 *   Joshua Kinard <kumba@gentoo.org>
 *   Brent Casavant <bcasavan@sgi.com> - IOC4 master driver
 *   Pat Gefre <pfg@sgi.com> - IOC3 serial port IRQ demuxer
 */

#समावेश <linux/delay.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/mfd/core.h>
#समावेश <linux/module.h>
#समावेश <linux/pci.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/platक्रमm_data/sgi-w1.h>
#समावेश <linux/rtc/ds1685.h>

#समावेश <यंत्र/pci/bridge.h>
#समावेश <यंत्र/sn/ioc3.h>

#घोषणा IOC3_IRQ_SERIAL_A	6
#घोषणा IOC3_IRQ_SERIAL_B	15
#घोषणा IOC3_IRQ_KBD		22

/* Biपंचांगask क्रम selecting which IRQs are level triggered */
#घोषणा IOC3_LVL_MASK	(BIT(IOC3_IRQ_SERIAL_A) | BIT(IOC3_IRQ_SERIAL_B))

#घोषणा M48T35_REG_SIZE	32768	/* size of m48t35 रेजिस्टरs */

/* 1.2 us latency समयr (40 cycles at 33 MHz) */
#घोषणा IOC3_LATENCY	40

काष्ठा ioc3_priv_data अणु
	काष्ठा irq_करोमुख्य *करोमुख्य;
	काष्ठा ioc3 __iomem *regs;
	काष्ठा pci_dev *pdev;
	पूर्णांक करोमुख्य_irq;
पूर्ण;

अटल व्योम ioc3_irq_ack(काष्ठा irq_data *d)
अणु
	काष्ठा ioc3_priv_data *ipd = irq_data_get_irq_chip_data(d);
	अचिन्हित पूर्णांक hwirq = irqd_to_hwirq(d);

	ग_लिखोl(BIT(hwirq), &ipd->regs->sio_ir);
पूर्ण

अटल व्योम ioc3_irq_mask(काष्ठा irq_data *d)
अणु
	काष्ठा ioc3_priv_data *ipd = irq_data_get_irq_chip_data(d);
	अचिन्हित पूर्णांक hwirq = irqd_to_hwirq(d);

	ग_लिखोl(BIT(hwirq), &ipd->regs->sio_iec);
पूर्ण

अटल व्योम ioc3_irq_unmask(काष्ठा irq_data *d)
अणु
	काष्ठा ioc3_priv_data *ipd = irq_data_get_irq_chip_data(d);
	अचिन्हित पूर्णांक hwirq = irqd_to_hwirq(d);

	ग_लिखोl(BIT(hwirq), &ipd->regs->sio_ies);
पूर्ण

अटल काष्ठा irq_chip ioc3_irq_chip = अणु
	.name		= "IOC3",
	.irq_ack	= ioc3_irq_ack,
	.irq_mask	= ioc3_irq_mask,
	.irq_unmask	= ioc3_irq_unmask,
पूर्ण;

अटल पूर्णांक ioc3_irq_करोमुख्य_map(काष्ठा irq_करोमुख्य *d, अचिन्हित पूर्णांक irq,
			      irq_hw_number_t hwirq)
अणु
	/* Set level IRQs क्रम every पूर्णांकerrupt contained in IOC3_LVL_MASK */
	अगर (BIT(hwirq) & IOC3_LVL_MASK)
		irq_set_chip_and_handler(irq, &ioc3_irq_chip, handle_level_irq);
	अन्यथा
		irq_set_chip_and_handler(irq, &ioc3_irq_chip, handle_edge_irq);

	irq_set_chip_data(irq, d->host_data);
	वापस 0;
पूर्ण

अटल व्योम ioc3_irq_करोमुख्य_unmap(काष्ठा irq_करोमुख्य *d, अचिन्हित पूर्णांक irq)
अणु
	irq_set_chip_and_handler(irq, शून्य, शून्य);
	irq_set_chip_data(irq, शून्य);
पूर्ण

अटल स्थिर काष्ठा irq_करोमुख्य_ops ioc3_irq_करोमुख्य_ops = अणु
	.map = ioc3_irq_करोमुख्य_map,
	.unmap = ioc3_irq_करोमुख्य_unmap,
पूर्ण;

अटल व्योम ioc3_irq_handler(काष्ठा irq_desc *desc)
अणु
	काष्ठा irq_करोमुख्य *करोमुख्य = irq_desc_get_handler_data(desc);
	काष्ठा ioc3_priv_data *ipd = करोमुख्य->host_data;
	काष्ठा ioc3 __iomem *regs = ipd->regs;
	u32 pending, mask;
	अचिन्हित पूर्णांक irq;

	pending = पढ़ोl(&regs->sio_ir);
	mask = पढ़ोl(&regs->sio_ies);
	pending &= mask; /* Mask off not enabled पूर्णांकerrupts */

	अगर (pending) अणु
		irq = irq_find_mapping(करोमुख्य, __ffs(pending));
		अगर (irq)
			generic_handle_irq(irq);
	पूर्ण अन्यथा  अणु
		spurious_पूर्णांकerrupt();
	पूर्ण
पूर्ण

/*
 * System boards/BaseIOs use more पूर्णांकerrupt pins of the bridge ASIC
 * to which the IOC3 is connected. Since the IOC3 MFD driver
 * knows wiring of these extra pins, we use the map_irq function
 * to get पूर्णांकerrupts activated
 */
अटल पूर्णांक ioc3_map_irq(काष्ठा pci_dev *pdev, पूर्णांक slot, पूर्णांक pin)
अणु
	काष्ठा pci_host_bridge *hbrg = pci_find_host_bridge(pdev->bus);

	वापस hbrg->map_irq(pdev, slot, pin);
पूर्ण

अटल पूर्णांक ioc3_irq_करोमुख्य_setup(काष्ठा ioc3_priv_data *ipd, पूर्णांक irq)
अणु
	काष्ठा irq_करोमुख्य *करोमुख्य;
	काष्ठा fwnode_handle *fn;

	fn = irq_करोमुख्य_alloc_named_fwnode("IOC3");
	अगर (!fn)
		जाओ err;

	करोमुख्य = irq_करोमुख्य_create_linear(fn, 24, &ioc3_irq_करोमुख्य_ops, ipd);
	अगर (!करोमुख्य) अणु
		irq_करोमुख्य_मुक्त_fwnode(fn);
		जाओ err;
	पूर्ण

	ipd->करोमुख्य = करोमुख्य;

	irq_set_chained_handler_and_data(irq, ioc3_irq_handler, करोमुख्य);
	ipd->करोमुख्य_irq = irq;
	वापस 0;

err:
	dev_err(&ipd->pdev->dev, "irq domain setup failed\n");
	वापस -ENOMEM;
पूर्ण

अटल स्थिर काष्ठा resource ioc3_uarta_resources[] = अणु
	DEFINE_RES_MEM(दुरत्व(काष्ठा ioc3, sregs.uarta),
		       माप_field(काष्ठा ioc3, sregs.uarta)),
	DEFINE_RES_IRQ(IOC3_IRQ_SERIAL_A)
पूर्ण;

अटल स्थिर काष्ठा resource ioc3_uartb_resources[] = अणु
	DEFINE_RES_MEM(दुरत्व(काष्ठा ioc3, sregs.uartb),
		       माप_field(काष्ठा ioc3, sregs.uartb)),
	DEFINE_RES_IRQ(IOC3_IRQ_SERIAL_B)
पूर्ण;

अटल काष्ठा mfd_cell ioc3_serial_cells[] = अणु
	अणु
		.name = "ioc3-serial8250",
		.resources = ioc3_uarta_resources,
		.num_resources = ARRAY_SIZE(ioc3_uarta_resources),
	पूर्ण,
	अणु
		.name = "ioc3-serial8250",
		.resources = ioc3_uartb_resources,
		.num_resources = ARRAY_SIZE(ioc3_uartb_resources),
	पूर्ण
पूर्ण;

अटल पूर्णांक ioc3_serial_setup(काष्ठा ioc3_priv_data *ipd)
अणु
	पूर्णांक ret;

	/* Set gpio pins क्रम RS232/RS422 mode selection */
	ग_लिखोl(GPCR_UARTA_MODESEL | GPCR_UARTB_MODESEL,
		&ipd->regs->gpcr_s);
	/* Select RS232 mode क्रम uart a */
	ग_लिखोl(0, &ipd->regs->gppr[6]);
	/* Select RS232 mode क्रम uart b */
	ग_लिखोl(0, &ipd->regs->gppr[7]);

	/* Switch both ports to 16650 mode */
	ग_लिखोl(पढ़ोl(&ipd->regs->port_a.sscr) & ~SSCR_DMA_EN,
	       &ipd->regs->port_a.sscr);
	ग_लिखोl(पढ़ोl(&ipd->regs->port_b.sscr) & ~SSCR_DMA_EN,
	       &ipd->regs->port_b.sscr);
	udelay(1000); /* Wait until mode चयन is करोne */

	ret = mfd_add_devices(&ipd->pdev->dev, PLATFORM_DEVID_AUTO,
			      ioc3_serial_cells, ARRAY_SIZE(ioc3_serial_cells),
			      &ipd->pdev->resource[0], 0, ipd->करोमुख्य);
	अगर (ret) अणु
		dev_err(&ipd->pdev->dev, "Failed to add 16550 subdevs\n");
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा resource ioc3_kbd_resources[] = अणु
	DEFINE_RES_MEM(दुरत्व(काष्ठा ioc3, serio),
		       माप_field(काष्ठा ioc3, serio)),
	DEFINE_RES_IRQ(IOC3_IRQ_KBD)
पूर्ण;

अटल काष्ठा mfd_cell ioc3_kbd_cells[] = अणु
	अणु
		.name = "ioc3-kbd",
		.resources = ioc3_kbd_resources,
		.num_resources = ARRAY_SIZE(ioc3_kbd_resources),
	पूर्ण
पूर्ण;

अटल पूर्णांक ioc3_kbd_setup(काष्ठा ioc3_priv_data *ipd)
अणु
	पूर्णांक ret;

	ret = mfd_add_devices(&ipd->pdev->dev, PLATFORM_DEVID_AUTO,
			      ioc3_kbd_cells, ARRAY_SIZE(ioc3_kbd_cells),
			      &ipd->pdev->resource[0], 0, ipd->करोमुख्य);
	अगर (ret) अणु
		dev_err(&ipd->pdev->dev, "Failed to add 16550 subdevs\n");
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा resource ioc3_eth_resources[] = अणु
	DEFINE_RES_MEM(दुरत्व(काष्ठा ioc3, eth),
		       माप_field(काष्ठा ioc3, eth)),
	DEFINE_RES_MEM(दुरत्व(काष्ठा ioc3, ssram),
		       माप_field(काष्ठा ioc3, ssram)),
	DEFINE_RES_IRQ(0)
पूर्ण;

अटल स्थिर काष्ठा resource ioc3_w1_resources[] = अणु
	DEFINE_RES_MEM(दुरत्व(काष्ठा ioc3, mcr),
		       माप_field(काष्ठा ioc3, mcr)),
पूर्ण;
अटल काष्ठा sgi_w1_platक्रमm_data ioc3_w1_platक्रमm_data;

अटल काष्ठा mfd_cell ioc3_eth_cells[] = अणु
	अणु
		.name = "ioc3-eth",
		.resources = ioc3_eth_resources,
		.num_resources = ARRAY_SIZE(ioc3_eth_resources),
	पूर्ण,
	अणु
		.name = "sgi_w1",
		.resources = ioc3_w1_resources,
		.num_resources = ARRAY_SIZE(ioc3_w1_resources),
		.platक्रमm_data = &ioc3_w1_platक्रमm_data,
		.pdata_size = माप(ioc3_w1_platक्रमm_data),
	पूर्ण
पूर्ण;

अटल पूर्णांक ioc3_eth_setup(काष्ठा ioc3_priv_data *ipd)
अणु
	पूर्णांक ret;

	/* Enable One-Wire bus */
	ग_लिखोl(GPCR_MLAN_EN, &ipd->regs->gpcr_s);

	/* Generate unique identअगरier */
	snम_लिखो(ioc3_w1_platक्रमm_data.dev_id,
		 माप(ioc3_w1_platक्रमm_data.dev_id), "ioc3-%012llx",
		 ipd->pdev->resource->start);

	ret = mfd_add_devices(&ipd->pdev->dev, PLATFORM_DEVID_AUTO,
			      ioc3_eth_cells, ARRAY_SIZE(ioc3_eth_cells),
			      &ipd->pdev->resource[0], ipd->pdev->irq, शून्य);
	अगर (ret) अणु
		dev_err(&ipd->pdev->dev, "Failed to add ETH/W1 subdev\n");
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा resource ioc3_m48t35_resources[] = अणु
	DEFINE_RES_MEM(IOC3_BYTEBUS_DEV0, M48T35_REG_SIZE)
पूर्ण;

अटल काष्ठा mfd_cell ioc3_m48t35_cells[] = अणु
	अणु
		.name = "rtc-m48t35",
		.resources = ioc3_m48t35_resources,
		.num_resources = ARRAY_SIZE(ioc3_m48t35_resources),
	पूर्ण
पूर्ण;

अटल पूर्णांक ioc3_m48t35_setup(काष्ठा ioc3_priv_data *ipd)
अणु
	पूर्णांक ret;

	ret = mfd_add_devices(&ipd->pdev->dev, PLATFORM_DEVID_AUTO,
			      ioc3_m48t35_cells, ARRAY_SIZE(ioc3_m48t35_cells),
			      &ipd->pdev->resource[0], 0, ipd->करोमुख्य);
	अगर (ret)
		dev_err(&ipd->pdev->dev, "Failed to add M48T35 subdev\n");

	वापस ret;
पूर्ण

अटल काष्ठा ds1685_rtc_platक्रमm_data ip30_rtc_platक्रमm_data = अणु
	.bcd_mode = false,
	.no_irq = false,
	.uie_unsupported = true,
	.access_type = ds1685_reg_indirect,
पूर्ण;

अटल स्थिर काष्ठा resource ioc3_rtc_ds1685_resources[] = अणु
	DEFINE_RES_MEM(IOC3_BYTEBUS_DEV1, 1),
	DEFINE_RES_MEM(IOC3_BYTEBUS_DEV2, 1),
	DEFINE_RES_IRQ(0)
पूर्ण;

अटल काष्ठा mfd_cell ioc3_ds1685_cells[] = अणु
	अणु
		.name = "rtc-ds1685",
		.resources = ioc3_rtc_ds1685_resources,
		.num_resources = ARRAY_SIZE(ioc3_rtc_ds1685_resources),
		.platक्रमm_data = &ip30_rtc_platक्रमm_data,
		.pdata_size = माप(ip30_rtc_platक्रमm_data),
		.id = PLATFORM_DEVID_NONE,
	पूर्ण
पूर्ण;

अटल पूर्णांक ioc3_ds1685_setup(काष्ठा ioc3_priv_data *ipd)
अणु
	पूर्णांक ret, irq;

	irq = ioc3_map_irq(ipd->pdev, 6, 0);

	ret = mfd_add_devices(&ipd->pdev->dev, 0, ioc3_ds1685_cells,
			      ARRAY_SIZE(ioc3_ds1685_cells),
			      &ipd->pdev->resource[0], irq, शून्य);
	अगर (ret)
		dev_err(&ipd->pdev->dev, "Failed to add DS1685 subdev\n");

	वापस ret;
पूर्ण;


अटल स्थिर काष्ठा resource ioc3_leds_resources[] = अणु
	DEFINE_RES_MEM(दुरत्व(काष्ठा ioc3, gppr[0]),
		       माप_field(काष्ठा ioc3, gppr[0])),
	DEFINE_RES_MEM(दुरत्व(काष्ठा ioc3, gppr[1]),
		       माप_field(काष्ठा ioc3, gppr[1])),
पूर्ण;

अटल काष्ठा mfd_cell ioc3_led_cells[] = अणु
	अणु
		.name = "ip30-leds",
		.resources = ioc3_leds_resources,
		.num_resources = ARRAY_SIZE(ioc3_leds_resources),
		.id = PLATFORM_DEVID_NONE,
	पूर्ण
पूर्ण;

अटल पूर्णांक ioc3_led_setup(काष्ठा ioc3_priv_data *ipd)
अणु
	पूर्णांक ret;

	ret = mfd_add_devices(&ipd->pdev->dev, 0, ioc3_led_cells,
			      ARRAY_SIZE(ioc3_led_cells),
			      &ipd->pdev->resource[0], 0, ipd->करोमुख्य);
	अगर (ret)
		dev_err(&ipd->pdev->dev, "Failed to add LED subdev\n");

	वापस ret;
पूर्ण

अटल पूर्णांक ip27_baseio_setup(काष्ठा ioc3_priv_data *ipd)
अणु
	पूर्णांक ret, io_irq;

	io_irq = ioc3_map_irq(ipd->pdev, PCI_SLOT(ipd->pdev->devfn),
			      PCI_INTERRUPT_INTB);
	ret = ioc3_irq_करोमुख्य_setup(ipd, io_irq);
	अगर (ret)
		वापस ret;

	ret = ioc3_eth_setup(ipd);
	अगर (ret)
		वापस ret;

	ret = ioc3_serial_setup(ipd);
	अगर (ret)
		वापस ret;

	वापस ioc3_m48t35_setup(ipd);
पूर्ण

अटल पूर्णांक ip27_baseio6g_setup(काष्ठा ioc3_priv_data *ipd)
अणु
	पूर्णांक ret, io_irq;

	io_irq = ioc3_map_irq(ipd->pdev, PCI_SLOT(ipd->pdev->devfn),
			      PCI_INTERRUPT_INTB);
	ret = ioc3_irq_करोमुख्य_setup(ipd, io_irq);
	अगर (ret)
		वापस ret;

	ret = ioc3_eth_setup(ipd);
	अगर (ret)
		वापस ret;

	ret = ioc3_serial_setup(ipd);
	अगर (ret)
		वापस ret;

	ret = ioc3_m48t35_setup(ipd);
	अगर (ret)
		वापस ret;

	वापस ioc3_kbd_setup(ipd);
पूर्ण

अटल पूर्णांक ip27_mio_setup(काष्ठा ioc3_priv_data *ipd)
अणु
	पूर्णांक ret;

	ret = ioc3_irq_करोमुख्य_setup(ipd, ipd->pdev->irq);
	अगर (ret)
		वापस ret;

	ret = ioc3_serial_setup(ipd);
	अगर (ret)
		वापस ret;

	वापस ioc3_kbd_setup(ipd);
पूर्ण

अटल पूर्णांक ip30_sysboard_setup(काष्ठा ioc3_priv_data *ipd)
अणु
	पूर्णांक ret, io_irq;

	io_irq = ioc3_map_irq(ipd->pdev, PCI_SLOT(ipd->pdev->devfn),
			      PCI_INTERRUPT_INTB);
	ret = ioc3_irq_करोमुख्य_setup(ipd, io_irq);
	अगर (ret)
		वापस ret;

	ret = ioc3_eth_setup(ipd);
	अगर (ret)
		वापस ret;

	ret = ioc3_serial_setup(ipd);
	अगर (ret)
		वापस ret;

	ret = ioc3_kbd_setup(ipd);
	अगर (ret)
		वापस ret;

	ret = ioc3_ds1685_setup(ipd);
	अगर (ret)
		वापस ret;

	वापस ioc3_led_setup(ipd);
पूर्ण

अटल पूर्णांक ioc3_menet_setup(काष्ठा ioc3_priv_data *ipd)
अणु
	पूर्णांक ret, io_irq;

	io_irq = ioc3_map_irq(ipd->pdev, PCI_SLOT(ipd->pdev->devfn),
			      PCI_INTERRUPT_INTB);
	ret = ioc3_irq_करोमुख्य_setup(ipd, io_irq);
	अगर (ret)
		वापस ret;

	ret = ioc3_eth_setup(ipd);
	अगर (ret)
		वापस ret;

	वापस ioc3_serial_setup(ipd);
पूर्ण

अटल पूर्णांक ioc3_menet4_setup(काष्ठा ioc3_priv_data *ipd)
अणु
	वापस ioc3_eth_setup(ipd);
पूर्ण

अटल पूर्णांक ioc3_cad_duo_setup(काष्ठा ioc3_priv_data *ipd)
अणु
	पूर्णांक ret, io_irq;

	io_irq = ioc3_map_irq(ipd->pdev, PCI_SLOT(ipd->pdev->devfn),
			      PCI_INTERRUPT_INTB);
	ret = ioc3_irq_करोमुख्य_setup(ipd, io_irq);
	अगर (ret)
		वापस ret;

	ret = ioc3_eth_setup(ipd);
	अगर (ret)
		वापस ret;

	वापस ioc3_kbd_setup(ipd);
पूर्ण

/* Helper macro क्रम filling ioc3_info array */
#घोषणा IOC3_SID(_name, _sid, _setup) \
	अणु								   \
		.name = _name,						   \
		.sid = PCI_VENDOR_ID_SGI | (IOC3_SUBSYS_ ## _sid << 16),   \
		.setup = _setup,					   \
	पूर्ण

अटल काष्ठा अणु
	स्थिर अक्षर *name;
	u32 sid;
	पूर्णांक (*setup)(काष्ठा ioc3_priv_data *ipd);
पूर्ण ioc3_infos[] = अणु
	IOC3_SID("IP27 BaseIO6G", IP27_BASEIO6G, &ip27_baseio6g_setup),
	IOC3_SID("IP27 MIO", IP27_MIO, &ip27_mio_setup),
	IOC3_SID("IP27 BaseIO", IP27_BASEIO, &ip27_baseio_setup),
	IOC3_SID("IP29 System Board", IP29_SYSBOARD, &ip27_baseio6g_setup),
	IOC3_SID("IP30 System Board", IP30_SYSBOARD, &ip30_sysboard_setup),
	IOC3_SID("MENET", MENET, &ioc3_menet_setup),
	IOC3_SID("MENET4", MENET4, &ioc3_menet4_setup)
पूर्ण;
#अघोषित IOC3_SID

अटल पूर्णांक ioc3_setup(काष्ठा ioc3_priv_data *ipd)
अणु
	u32 sid;
	पूर्णांक i;

	/* Clear IRQs */
	ग_लिखोl(~0, &ipd->regs->sio_iec);
	ग_लिखोl(~0, &ipd->regs->sio_ir);
	ग_लिखोl(0, &ipd->regs->eth.eier);
	ग_लिखोl(~0, &ipd->regs->eth.eisr);

	/* Read subप्रणाली venकरोr id and subप्रणाली id */
	pci_पढ़ो_config_dword(ipd->pdev, PCI_SUBSYSTEM_VENDOR_ID, &sid);

	क्रम (i = 0; i < ARRAY_SIZE(ioc3_infos); i++)
		अगर (sid == ioc3_infos[i].sid) अणु
			pr_info("ioc3: %s\n", ioc3_infos[i].name);
			वापस ioc3_infos[i].setup(ipd);
		पूर्ण

	/* Treat everything not identअगरied by PCI subid as CAD DUO */
	pr_info("ioc3: CAD DUO\n");
	वापस ioc3_cad_duo_setup(ipd);
पूर्ण

अटल पूर्णांक ioc3_mfd_probe(काष्ठा pci_dev *pdev,
			  स्थिर काष्ठा pci_device_id *pci_id)
अणु
	काष्ठा ioc3_priv_data *ipd;
	काष्ठा ioc3 __iomem *regs;
	पूर्णांक ret;

	ret = pci_enable_device(pdev);
	अगर (ret)
		वापस ret;

	pci_ग_लिखो_config_byte(pdev, PCI_LATENCY_TIMER, IOC3_LATENCY);
	pci_set_master(pdev);

	ret = dma_set_mask_and_coherent(&pdev->dev, DMA_BIT_MASK(64));
	अगर (ret) अणु
		pr_err("%s: No usable DMA configuration, aborting.\n",
		       pci_name(pdev));
		जाओ out_disable_device;
	पूर्ण

	/* Set up per-IOC3 data */
	ipd = devm_kzalloc(&pdev->dev, माप(काष्ठा ioc3_priv_data),
			   GFP_KERNEL);
	अगर (!ipd) अणु
		ret = -ENOMEM;
		जाओ out_disable_device;
	पूर्ण
	ipd->pdev = pdev;

	/*
	 * Map all IOC3 रेजिस्टरs.  These are shared between subdevices
	 * so the मुख्य IOC3 module manages them.
	 */
	regs = pci_ioremap_bar(pdev, 0);
	अगर (!regs) अणु
		dev_warn(&pdev->dev, "ioc3: Unable to remap PCI BAR for %s.\n",
			 pci_name(pdev));
		ret = -ENOMEM;
		जाओ out_disable_device;
	पूर्ण
	ipd->regs = regs;

	/* Track PCI-device specअगरic data */
	pci_set_drvdata(pdev, ipd);

	ret = ioc3_setup(ipd);
	अगर (ret) अणु
		/* Remove all alपढ़ोy added MFD devices */
		mfd_हटाओ_devices(&ipd->pdev->dev);
		अगर (ipd->करोमुख्य) अणु
			काष्ठा fwnode_handle *fn = ipd->करोमुख्य->fwnode;

			irq_करोमुख्य_हटाओ(ipd->करोमुख्य);
			irq_करोमुख्य_मुक्त_fwnode(fn);
			मुक्त_irq(ipd->करोमुख्य_irq, (व्योम *)ipd);
		पूर्ण
		pci_iounmap(pdev, regs);
		जाओ out_disable_device;
	पूर्ण

	वापस 0;

out_disable_device:
	pci_disable_device(pdev);
	वापस ret;
पूर्ण

अटल व्योम ioc3_mfd_हटाओ(काष्ठा pci_dev *pdev)
अणु
	काष्ठा ioc3_priv_data *ipd;

	ipd = pci_get_drvdata(pdev);

	/* Clear and disable all IRQs */
	ग_लिखोl(~0, &ipd->regs->sio_iec);
	ग_लिखोl(~0, &ipd->regs->sio_ir);

	/* Release resources */
	mfd_हटाओ_devices(&ipd->pdev->dev);
	अगर (ipd->करोमुख्य) अणु
		काष्ठा fwnode_handle *fn = ipd->करोमुख्य->fwnode;

		irq_करोमुख्य_हटाओ(ipd->करोमुख्य);
		irq_करोमुख्य_मुक्त_fwnode(fn);
		मुक्त_irq(ipd->करोमुख्य_irq, (व्योम *)ipd);
	पूर्ण
	pci_iounmap(pdev, ipd->regs);
	pci_disable_device(pdev);
पूर्ण

अटल काष्ठा pci_device_id ioc3_mfd_id_table[] = अणु
	अणु PCI_VENDOR_ID_SGI, PCI_DEVICE_ID_SGI_IOC3, PCI_ANY_ID, PCI_ANY_ID पूर्ण,
	अणु 0, पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(pci, ioc3_mfd_id_table);

अटल काष्ठा pci_driver ioc3_mfd_driver = अणु
	.name = "IOC3",
	.id_table = ioc3_mfd_id_table,
	.probe = ioc3_mfd_probe,
	.हटाओ = ioc3_mfd_हटाओ,
पूर्ण;

module_pci_driver(ioc3_mfd_driver);

MODULE_AUTHOR("Thomas Bogendoerfer <tbogendoerfer@suse.de>");
MODULE_DESCRIPTION("SGI IOC3 MFD driver");
MODULE_LICENSE("GPL v2");
