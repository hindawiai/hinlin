<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * AHCI SATA platक्रमm driver
 *
 * Copyright 2004-2005  Red Hat, Inc.
 *   Jeff Garzik <jgarzik@pobox.com>
 * Copyright 2010  MontaVista Software, LLC.
 *   Anton Vorontsov <avorontsov@ru.mvista.com>
 */

#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/pm.h>
#समावेश <linux/device.h>
#समावेश <linux/of_device.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/libata.h>
#समावेश <linux/ahci_platक्रमm.h>
#समावेश <linux/acpi.h>
#समावेश <linux/pci_ids.h>
#समावेश "ahci.h"

#घोषणा DRV_NAME "ahci"

अटल स्थिर काष्ठा ata_port_info ahci_port_info = अणु
	.flags		= AHCI_FLAG_COMMON,
	.pio_mask	= ATA_PIO4,
	.udma_mask	= ATA_UDMA6,
	.port_ops	= &ahci_platक्रमm_ops,
पूर्ण;

अटल स्थिर काष्ठा ata_port_info ahci_port_info_nolpm = अणु
	.flags		= AHCI_FLAG_COMMON | ATA_FLAG_NO_LPM,
	.pio_mask	= ATA_PIO4,
	.udma_mask	= ATA_UDMA6,
	.port_ops	= &ahci_platक्रमm_ops,
पूर्ण;

अटल काष्ठा scsi_host_ढाँचा ahci_platक्रमm_sht = अणु
	AHCI_SHT(DRV_NAME),
पूर्ण;

अटल पूर्णांक ahci_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device *dev = &pdev->dev;
	काष्ठा ahci_host_priv *hpriv;
	स्थिर काष्ठा ata_port_info *port;
	पूर्णांक rc;

	hpriv = ahci_platक्रमm_get_resources(pdev,
					    AHCI_PLATFORM_GET_RESETS);
	अगर (IS_ERR(hpriv))
		वापस PTR_ERR(hpriv);

	rc = ahci_platक्रमm_enable_resources(hpriv);
	अगर (rc)
		वापस rc;

	of_property_पढ़ो_u32(dev->of_node,
			     "ports-implemented", &hpriv->क्रमce_port_map);

	अगर (of_device_is_compatible(dev->of_node, "hisilicon,hisi-ahci"))
		hpriv->flags |= AHCI_HFLAG_NO_FBS | AHCI_HFLAG_NO_NCQ;

	port = acpi_device_get_match_data(dev);
	अगर (!port)
		port = &ahci_port_info;

	rc = ahci_platक्रमm_init_host(pdev, hpriv, port,
				     &ahci_platक्रमm_sht);
	अगर (rc)
		जाओ disable_resources;

	वापस 0;
disable_resources:
	ahci_platक्रमm_disable_resources(hpriv);
	वापस rc;
पूर्ण

अटल SIMPLE_DEV_PM_OPS(ahci_pm_ops, ahci_platक्रमm_suspend,
			 ahci_platक्रमm_resume);

अटल स्थिर काष्ठा of_device_id ahci_of_match[] = अणु
	अणु .compatible = "generic-ahci", पूर्ण,
	/* Keep the following compatibles क्रम device tree compatibility */
	अणु .compatible = "snps,spear-ahci", पूर्ण,
	अणु .compatible = "ibm,476gtr-ahci", पूर्ण,
	अणु .compatible = "snps,dwc-ahci", पूर्ण,
	अणु .compatible = "hisilicon,hisi-ahci", पूर्ण,
	अणु .compatible = "cavium,octeon-7130-ahci", पूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, ahci_of_match);

अटल स्थिर काष्ठा acpi_device_id ahci_acpi_match[] = अणु
	अणु "APMC0D33", (अचिन्हित दीर्घ)&ahci_port_info_nolpm पूर्ण,
	अणु ACPI_DEVICE_CLASS(PCI_CLASS_STORAGE_SATA_AHCI, 0xffffff) पूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(acpi, ahci_acpi_match);

अटल काष्ठा platक्रमm_driver ahci_driver = अणु
	.probe = ahci_probe,
	.हटाओ = ata_platक्रमm_हटाओ_one,
	.shutकरोwn = ahci_platक्रमm_shutकरोwn,
	.driver = अणु
		.name = DRV_NAME,
		.of_match_table = ahci_of_match,
		.acpi_match_table = ahci_acpi_match,
		.pm = &ahci_pm_ops,
	पूर्ण,
पूर्ण;
module_platक्रमm_driver(ahci_driver);

MODULE_DESCRIPTION("AHCI SATA platform driver");
MODULE_AUTHOR("Anton Vorontsov <avorontsov@ru.mvista.com>");
MODULE_LICENSE("GPL");
MODULE_ALIAS("platform:ahci");
