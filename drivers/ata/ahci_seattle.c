<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * AMD Seattle AHCI SATA driver
 *
 * Copyright (c) 2015, Advanced Micro Devices
 * Author: Brijesh Singh <brijesh.singh@amd.com>
 *
 * based on the AHCI SATA platक्रमm driver by Jeff Garzik and Anton Vorontsov
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

/* SGPIO Control Register definition
 *
 * Bit		Type		Description
 * 31		RW		OD7.2 (activity)
 * 30		RW		OD7.1 (locate)
 * 29		RW		OD7.0 (fault)
 * 28...8	RW		OD6.2...OD0.0 (3bits per port, 1 bit per LED)
 * 7		RO		SGPIO feature flag
 * 6:4		RO		Reserved
 * 3:0		RO		Number of ports (0 means no port supported)
 */
#घोषणा ACTIVITY_BIT_POS(x)		(8 + (3 * x))
#घोषणा LOCATE_BIT_POS(x)		(ACTIVITY_BIT_POS(x) + 1)
#घोषणा FAULT_BIT_POS(x)		(LOCATE_BIT_POS(x) + 1)

#घोषणा ACTIVITY_MASK			0x00010000
#घोषणा LOCATE_MASK			0x00080000
#घोषणा FAULT_MASK			0x00400000

#घोषणा DRV_NAME "ahci-seattle"

अटल sमाप_प्रकार seattle_transmit_led_message(काष्ठा ata_port *ap, u32 state,
					    sमाप_प्रकार size);

काष्ठा seattle_plat_data अणु
	व्योम __iomem *sgpio_ctrl;
पूर्ण;

अटल काष्ठा ata_port_operations ahci_port_ops = अणु
	.inherits		= &ahci_ops,
पूर्ण;

अटल स्थिर काष्ठा ata_port_info ahci_port_info = अणु
	.flags		= AHCI_FLAG_COMMON,
	.pio_mask	= ATA_PIO4,
	.udma_mask	= ATA_UDMA6,
	.port_ops	= &ahci_port_ops,
पूर्ण;

अटल काष्ठा ata_port_operations ahci_seattle_ops = अणु
	.inherits		= &ahci_ops,
	.transmit_led_message   = seattle_transmit_led_message,
पूर्ण;

अटल स्थिर काष्ठा ata_port_info ahci_port_seattle_info = अणु
	.flags		= AHCI_FLAG_COMMON | ATA_FLAG_EM | ATA_FLAG_SW_ACTIVITY,
	.link_flags	= ATA_LFLAG_SW_ACTIVITY,
	.pio_mask	= ATA_PIO4,
	.udma_mask	= ATA_UDMA6,
	.port_ops	= &ahci_seattle_ops,
पूर्ण;

अटल काष्ठा scsi_host_ढाँचा ahci_platक्रमm_sht = अणु
	AHCI_SHT(DRV_NAME),
पूर्ण;

अटल sमाप_प्रकार seattle_transmit_led_message(काष्ठा ata_port *ap, u32 state,
					    sमाप_प्रकार size)
अणु
	काष्ठा ahci_host_priv *hpriv = ap->host->निजी_data;
	काष्ठा ahci_port_priv *pp = ap->निजी_data;
	काष्ठा seattle_plat_data *plat_data = hpriv->plat_data;
	अचिन्हित दीर्घ flags;
	पूर्णांक pmp;
	काष्ठा ahci_em_priv *emp;
	u32 val;

	/* get the slot number from the message */
	pmp = (state & EM_MSG_LED_PMP_SLOT) >> 8;
	अगर (pmp >= EM_MAX_SLOTS)
		वापस -EINVAL;
	emp = &pp->em_priv[pmp];

	val = ioपढ़ो32(plat_data->sgpio_ctrl);
	अगर (state & ACTIVITY_MASK)
		val |= 1 << ACTIVITY_BIT_POS((ap->port_no));
	अन्यथा
		val &= ~(1 << ACTIVITY_BIT_POS((ap->port_no)));

	अगर (state & LOCATE_MASK)
		val |= 1 << LOCATE_BIT_POS((ap->port_no));
	अन्यथा
		val &= ~(1 << LOCATE_BIT_POS((ap->port_no)));

	अगर (state & FAULT_MASK)
		val |= 1 << FAULT_BIT_POS((ap->port_no));
	अन्यथा
		val &= ~(1 << FAULT_BIT_POS((ap->port_no)));

	ioग_लिखो32(val, plat_data->sgpio_ctrl);

	spin_lock_irqsave(ap->lock, flags);

	/* save off new led state क्रम port/slot */
	emp->led_state = state;

	spin_unlock_irqrestore(ap->lock, flags);

	वापस size;
पूर्ण

अटल स्थिर काष्ठा ata_port_info *ahci_seattle_get_port_info(
		काष्ठा platक्रमm_device *pdev, काष्ठा ahci_host_priv *hpriv)
अणु
	काष्ठा device *dev = &pdev->dev;
	काष्ठा seattle_plat_data *plat_data;
	u32 val;

	plat_data = devm_kzalloc(dev, माप(*plat_data), GFP_KERNEL);
	अगर (!plat_data)
		वापस &ahci_port_info;

	plat_data->sgpio_ctrl = devm_ioremap_resource(dev,
			      platक्रमm_get_resource(pdev, IORESOURCE_MEM, 1));
	अगर (IS_ERR(plat_data->sgpio_ctrl))
		वापस &ahci_port_info;

	val = ioपढ़ो32(plat_data->sgpio_ctrl);

	अगर (!(val & 0xf))
		वापस &ahci_port_info;

	hpriv->em_loc = 0;
	hpriv->em_buf_sz = 4;
	hpriv->em_msg_type = EM_MSG_TYPE_LED;
	hpriv->plat_data = plat_data;

	dev_info(dev, "SGPIO LED control is enabled.\n");
	वापस &ahci_port_seattle_info;
पूर्ण

अटल पूर्णांक ahci_seattle_probe(काष्ठा platक्रमm_device *pdev)
अणु
	पूर्णांक rc;
	काष्ठा ahci_host_priv *hpriv;

	hpriv = ahci_platक्रमm_get_resources(pdev, 0);
	अगर (IS_ERR(hpriv))
		वापस PTR_ERR(hpriv);

	rc = ahci_platक्रमm_enable_resources(hpriv);
	अगर (rc)
		वापस rc;

	rc = ahci_platक्रमm_init_host(pdev, hpriv,
				     ahci_seattle_get_port_info(pdev, hpriv),
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

अटल स्थिर काष्ठा acpi_device_id ahci_acpi_match[] = अणु
	अणु "AMDI0600", 0 पूर्ण,
	अणुपूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(acpi, ahci_acpi_match);

अटल काष्ठा platक्रमm_driver ahci_seattle_driver = अणु
	.probe = ahci_seattle_probe,
	.हटाओ = ata_platक्रमm_हटाओ_one,
	.driver = अणु
		.name = DRV_NAME,
		.acpi_match_table = ahci_acpi_match,
		.pm = &ahci_pm_ops,
	पूर्ण,
पूर्ण;
module_platक्रमm_driver(ahci_seattle_driver);

MODULE_DESCRIPTION("Seattle AHCI SATA platform driver");
MODULE_AUTHOR("Brijesh Singh <brijesh.singh@amd.com>");
MODULE_LICENSE("GPL");
MODULE_ALIAS("platform:" DRV_NAME);
