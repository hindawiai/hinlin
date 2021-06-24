<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Platक्रमm IDE driver
 *
 * Copyright (C) 2007 MontaVista Software
 *
 * Maपूर्णांकainer: Kumar Gala <galak@kernel.crashing.org>
 */

#समावेश <linux/types.h>
#समावेश <linux/init.h>
#समावेश <linux/kernel.h>
#समावेश <linux/ide.h>
#समावेश <linux/ioport.h>
#समावेश <linux/module.h>
#समावेश <linux/ata_platक्रमm.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/पन.स>

अटल व्योम plat_ide_setup_ports(काष्ठा ide_hw *hw, व्योम __iomem *base,
				 व्योम __iomem *ctrl,
				 काष्ठा pata_platक्रमm_info *pdata, पूर्णांक irq)
अणु
	अचिन्हित दीर्घ port = (अचिन्हित दीर्घ)base;
	पूर्णांक i;

	hw->io_ports.data_addr = port;

	port += (1 << pdata->ioport_shअगरt);
	क्रम (i = 1; i <= 7;
	     i++, port += (1 << pdata->ioport_shअगरt))
		hw->io_ports_array[i] = port;

	hw->io_ports.ctl_addr = (अचिन्हित दीर्घ)ctrl;

	hw->irq = irq;
पूर्ण

अटल स्थिर काष्ठा ide_port_info platक्रमm_ide_port_info = अणु
	.host_flags		= IDE_HFLAG_NO_DMA,
	.chipset		= ide_generic,
पूर्ण;

अटल पूर्णांक plat_ide_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा resource *res_base, *res_alt, *res_irq;
	व्योम __iomem *base, *alt_base;
	काष्ठा pata_platक्रमm_info *pdata;
	काष्ठा ide_host *host;
	पूर्णांक ret = 0, mmio = 0;
	काष्ठा ide_hw hw, *hws[] = अणु &hw पूर्ण;
	काष्ठा ide_port_info d = platक्रमm_ide_port_info;

	pdata = dev_get_platdata(&pdev->dev);

	/* get a poपूर्णांकer to the रेजिस्टर memory */
	res_base = platक्रमm_get_resource(pdev, IORESOURCE_IO, 0);
	res_alt = platक्रमm_get_resource(pdev, IORESOURCE_IO, 1);

	अगर (!res_base || !res_alt) अणु
		res_base = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);
		res_alt = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 1);
		अगर (!res_base || !res_alt) अणु
			ret = -ENOMEM;
			जाओ out;
		पूर्ण
		mmio = 1;
	पूर्ण

	res_irq = platक्रमm_get_resource(pdev, IORESOURCE_IRQ, 0);
	अगर (!res_irq) अणु
		ret = -EINVAL;
		जाओ out;
	पूर्ण

	अगर (mmio) अणु
		base = devm_ioremap(&pdev->dev,
			res_base->start, resource_size(res_base));
		alt_base = devm_ioremap(&pdev->dev,
			res_alt->start, resource_size(res_alt));
	पूर्ण अन्यथा अणु
		base = devm_ioport_map(&pdev->dev,
			res_base->start, resource_size(res_base));
		alt_base = devm_ioport_map(&pdev->dev,
			res_alt->start, resource_size(res_alt));
	पूर्ण

	स_रखो(&hw, 0, माप(hw));
	plat_ide_setup_ports(&hw, base, alt_base, pdata, res_irq->start);
	hw.dev = &pdev->dev;

	d.irq_flags = res_irq->flags & IRQF_TRIGGER_MASK;
	अगर (res_irq->flags & IORESOURCE_IRQ_SHAREABLE)
		d.irq_flags |= IRQF_SHARED;

	अगर (mmio)
		d.host_flags |= IDE_HFLAG_MMIO;

	ret = ide_host_add(&d, hws, 1, &host);
	अगर (ret)
		जाओ out;

	platक्रमm_set_drvdata(pdev, host);

	वापस 0;

out:
	वापस ret;
पूर्ण

अटल पूर्णांक plat_ide_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा ide_host *host = dev_get_drvdata(&pdev->dev);

	ide_host_हटाओ(host);

	वापस 0;
पूर्ण

अटल काष्ठा platक्रमm_driver platक्रमm_ide_driver = अणु
	.driver = अणु
		.name = "pata_platform",
	पूर्ण,
	.probe = plat_ide_probe,
	.हटाओ = plat_ide_हटाओ,
पूर्ण;

module_platक्रमm_driver(platक्रमm_ide_driver);

MODULE_DESCRIPTION("Platform IDE driver");
MODULE_LICENSE("GPL");
MODULE_ALIAS("platform:pata_platform");
