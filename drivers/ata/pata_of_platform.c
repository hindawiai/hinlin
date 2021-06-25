<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * OF-platक्रमm PATA driver
 *
 * Copyright (c) 2007  MontaVista Software, Inc.
 *                     Anton Vorontsov <avorontsov@ru.mvista.com>
 */

#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/of_address.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/ata_platक्रमm.h>
#समावेश <linux/libata.h>

#घोषणा DRV_NAME "pata_of_platform"

अटल काष्ठा scsi_host_ढाँचा pata_platक्रमm_sht = अणु
	ATA_PIO_SHT(DRV_NAME),
पूर्ण;

अटल पूर्णांक pata_of_platक्रमm_probe(काष्ठा platक्रमm_device *ofdev)
अणु
	पूर्णांक ret;
	काष्ठा device_node *dn = ofdev->dev.of_node;
	काष्ठा resource io_res;
	काष्ठा resource ctl_res;
	काष्ठा resource *irq_res;
	अचिन्हित पूर्णांक reg_shअगरt = 0;
	पूर्णांक pio_mode = 0;
	पूर्णांक pio_mask;
	bool use16bit;

	ret = of_address_to_resource(dn, 0, &io_res);
	अगर (ret) अणु
		dev_err(&ofdev->dev, "can't get IO address from "
			"device tree\n");
		वापस -EINVAL;
	पूर्ण

	ret = of_address_to_resource(dn, 1, &ctl_res);
	अगर (ret) अणु
		dev_err(&ofdev->dev, "can't get CTL address from "
			"device tree\n");
		वापस -EINVAL;
	पूर्ण

	irq_res = platक्रमm_get_resource(ofdev, IORESOURCE_IRQ, 0);

	of_property_पढ़ो_u32(dn, "reg-shift", &reg_shअगरt);

	अगर (!of_property_पढ़ो_u32(dn, "pio-mode", &pio_mode)) अणु
		अगर (pio_mode > 6) अणु
			dev_err(&ofdev->dev, "invalid pio-mode\n");
			वापस -EINVAL;
		पूर्ण
	पूर्ण अन्यथा अणु
		dev_info(&ofdev->dev, "pio-mode unspecified, assuming PIO0\n");
	पूर्ण

	use16bit = of_property_पढ़ो_bool(dn, "ata-generic,use16bit");

	pio_mask = 1 << pio_mode;
	pio_mask |= (1 << pio_mode) - 1;

	वापस __pata_platक्रमm_probe(&ofdev->dev, &io_res, &ctl_res, irq_res,
				     reg_shअगरt, pio_mask, &pata_platक्रमm_sht,
				     use16bit);
पूर्ण

अटल स्थिर काष्ठा of_device_id pata_of_platक्रमm_match[] = अणु
	अणु .compatible = "ata-generic", पूर्ण,
	अणु पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, pata_of_platक्रमm_match);

अटल काष्ठा platक्रमm_driver pata_of_platक्रमm_driver = अणु
	.driver = अणु
		.name = DRV_NAME,
		.of_match_table = pata_of_platक्रमm_match,
	पूर्ण,
	.probe		= pata_of_platक्रमm_probe,
	.हटाओ		= ata_platक्रमm_हटाओ_one,
पूर्ण;

module_platक्रमm_driver(pata_of_platक्रमm_driver);

MODULE_DESCRIPTION("OF-platform PATA driver");
MODULE_AUTHOR("Anton Vorontsov <avorontsov@ru.mvista.com>");
MODULE_LICENSE("GPL");
