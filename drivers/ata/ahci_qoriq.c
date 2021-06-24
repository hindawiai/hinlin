<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Freescale QorIQ AHCI SATA platक्रमm driver
 *
 * Copyright 2015 Freescale, Inc.
 *   Tang Yuantian <Yuantian.Tang@मुक्तscale.com>
 */

#समावेश <linux/acpi.h>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/pm.h>
#समावेश <linux/ahci_platक्रमm.h>
#समावेश <linux/device.h>
#समावेश <linux/of_address.h>
#समावेश <linux/of.h>
#समावेश <linux/of_device.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/libata.h>
#समावेश "ahci.h"

#घोषणा DRV_NAME "ahci-qoriq"

/* port रेजिस्टर definition */
#घोषणा PORT_PHY1	0xA8
#घोषणा PORT_PHY2	0xAC
#घोषणा PORT_PHY3	0xB0
#घोषणा PORT_PHY4	0xB4
#घोषणा PORT_PHY5	0xB8
#घोषणा PORT_AXICC	0xBC
#घोषणा PORT_TRANS	0xC8

/* port रेजिस्टर शेष value */
#घोषणा AHCI_PORT_PHY_1_CFG	0xa003fffe
#घोषणा AHCI_PORT_PHY2_CFG	0x28184d1f
#घोषणा AHCI_PORT_PHY3_CFG	0x0e081509
#घोषणा AHCI_PORT_TRANS_CFG	0x08000029
#घोषणा AHCI_PORT_AXICC_CFG	0x3fffffff

/* क्रम ls1021a */
#घोषणा LS1021A_PORT_PHY2	0x28183414
#घोषणा LS1021A_PORT_PHY3	0x0e080e06
#घोषणा LS1021A_PORT_PHY4	0x064a080b
#घोषणा LS1021A_PORT_PHY5	0x2aa86470
#घोषणा LS1021A_AXICC_ADDR	0xC0

#घोषणा SATA_ECC_DISABLE	0x00020000
#घोषणा ECC_DIS_ARMV8_CH2	0x80000000
#घोषणा ECC_DIS_LS1088A		0x40000000

क्रमागत ahci_qoriq_type अणु
	AHCI_LS1021A,
	AHCI_LS1028A,
	AHCI_LS1043A,
	AHCI_LS2080A,
	AHCI_LS1046A,
	AHCI_LS1088A,
	AHCI_LS2088A,
	AHCI_LX2160A,
पूर्ण;

काष्ठा ahci_qoriq_priv अणु
	काष्ठा ccsr_ahci *reg_base;
	क्रमागत ahci_qoriq_type type;
	व्योम __iomem *ecc_addr;
	bool is_dmacoherent;
पूर्ण;

अटल bool ecc_initialized;

अटल स्थिर काष्ठा of_device_id ahci_qoriq_of_match[] = अणु
	अणु .compatible = "fsl,ls1021a-ahci", .data = (व्योम *)AHCI_LS1021Aपूर्ण,
	अणु .compatible = "fsl,ls1028a-ahci", .data = (व्योम *)AHCI_LS1028Aपूर्ण,
	अणु .compatible = "fsl,ls1043a-ahci", .data = (व्योम *)AHCI_LS1043Aपूर्ण,
	अणु .compatible = "fsl,ls2080a-ahci", .data = (व्योम *)AHCI_LS2080Aपूर्ण,
	अणु .compatible = "fsl,ls1046a-ahci", .data = (व्योम *)AHCI_LS1046Aपूर्ण,
	अणु .compatible = "fsl,ls1088a-ahci", .data = (व्योम *)AHCI_LS1088Aपूर्ण,
	अणु .compatible = "fsl,ls2088a-ahci", .data = (व्योम *)AHCI_LS2088Aपूर्ण,
	अणु .compatible = "fsl,lx2160a-ahci", .data = (व्योम *)AHCI_LX2160Aपूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, ahci_qoriq_of_match);

अटल स्थिर काष्ठा acpi_device_id ahci_qoriq_acpi_match[] = अणु
	अणु"NXP0004", .driver_data = (kernel_uदीर्घ_t)AHCI_LX2160Aपूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(acpi, ahci_qoriq_acpi_match);

अटल पूर्णांक ahci_qoriq_hardreset(काष्ठा ata_link *link, अचिन्हित पूर्णांक *class,
			  अचिन्हित दीर्घ deadline)
अणु
	स्थिर अचिन्हित दीर्घ *timing = sata_ehc_deb_timing(&link->eh_context);
	व्योम __iomem *port_mmio = ahci_port_base(link->ap);
	u32 px_cmd, px_is, px_val;
	काष्ठा ata_port *ap = link->ap;
	काष्ठा ahci_port_priv *pp = ap->निजी_data;
	काष्ठा ahci_host_priv *hpriv = ap->host->निजी_data;
	काष्ठा ahci_qoriq_priv *qoriq_priv = hpriv->plat_data;
	u8 *d2h_fis = pp->rx_fis + RX_FIS_D2H_REG;
	काष्ठा ata_taskfile tf;
	bool online;
	पूर्णांक rc;
	bool ls1021a_workaround = (qoriq_priv->type == AHCI_LS1021A);

	DPRINTK("ENTER\n");

	hpriv->stop_engine(ap);

	/*
	 * There is a errata on ls1021a Rev1.0 and Rev2.0 which is:
	 * A-009042: The device detection initialization sequence
	 * mistakenly resets some रेजिस्टरs.
	 *
	 * Workaround क्रम this is:
	 * The software should पढ़ो and store PxCMD and PxIS values
	 * beक्रमe issuing the device detection initialization sequence.
	 * After the sequence is complete, software should restore the
	 * PxCMD and PxIS with the stored values.
	 */
	अगर (ls1021a_workaround) अणु
		px_cmd = पढ़ोl(port_mmio + PORT_CMD);
		px_is = पढ़ोl(port_mmio + PORT_IRQ_STAT);
	पूर्ण

	/* clear D2H reception area to properly रुको क्रम D2H FIS */
	ata_tf_init(link->device, &tf);
	tf.command = ATA_BUSY;
	ata_tf_to_fis(&tf, 0, 0, d2h_fis);

	rc = sata_link_hardreset(link, timing, deadline, &online,
				 ahci_check_पढ़ोy);

	/* restore the PxCMD and PxIS on ls1021 */
	अगर (ls1021a_workaround) अणु
		px_val = पढ़ोl(port_mmio + PORT_CMD);
		अगर (px_val != px_cmd)
			ग_लिखोl(px_cmd, port_mmio + PORT_CMD);

		px_val = पढ़ोl(port_mmio + PORT_IRQ_STAT);
		अगर (px_val != px_is)
			ग_लिखोl(px_is, port_mmio + PORT_IRQ_STAT);
	पूर्ण

	hpriv->start_engine(ap);

	अगर (online)
		*class = ahci_dev_classअगरy(ap);

	DPRINTK("EXIT, rc=%d, class=%u\n", rc, *class);
	वापस rc;
पूर्ण

अटल काष्ठा ata_port_operations ahci_qoriq_ops = अणु
	.inherits	= &ahci_ops,
	.hardreset	= ahci_qoriq_hardreset,
पूर्ण;

अटल स्थिर काष्ठा ata_port_info ahci_qoriq_port_info = अणु
	.flags		= AHCI_FLAG_COMMON | ATA_FLAG_NCQ,
	.pio_mask	= ATA_PIO4,
	.udma_mask	= ATA_UDMA6,
	.port_ops	= &ahci_qoriq_ops,
पूर्ण;

अटल काष्ठा scsi_host_ढाँचा ahci_qoriq_sht = अणु
	AHCI_SHT(DRV_NAME),
पूर्ण;

अटल पूर्णांक ahci_qoriq_phy_init(काष्ठा ahci_host_priv *hpriv)
अणु
	काष्ठा ahci_qoriq_priv *qpriv = hpriv->plat_data;
	व्योम __iomem *reg_base = hpriv->mmio;

	चयन (qpriv->type) अणु
	हाल AHCI_LS1021A:
		अगर (!(qpriv->ecc_addr || ecc_initialized))
			वापस -EINVAL;
		अन्यथा अगर (qpriv->ecc_addr && !ecc_initialized)
			ग_लिखोl(SATA_ECC_DISABLE, qpriv->ecc_addr);
		ग_लिखोl(AHCI_PORT_PHY_1_CFG, reg_base + PORT_PHY1);
		ग_लिखोl(LS1021A_PORT_PHY2, reg_base + PORT_PHY2);
		ग_लिखोl(LS1021A_PORT_PHY3, reg_base + PORT_PHY3);
		ग_लिखोl(LS1021A_PORT_PHY4, reg_base + PORT_PHY4);
		ग_लिखोl(LS1021A_PORT_PHY5, reg_base + PORT_PHY5);
		ग_लिखोl(AHCI_PORT_TRANS_CFG, reg_base + PORT_TRANS);
		अगर (qpriv->is_dmacoherent)
			ग_लिखोl(AHCI_PORT_AXICC_CFG,
					reg_base + LS1021A_AXICC_ADDR);
		अवरोध;

	हाल AHCI_LS1043A:
		अगर (!(qpriv->ecc_addr || ecc_initialized))
			वापस -EINVAL;
		अन्यथा अगर (qpriv->ecc_addr && !ecc_initialized)
			ग_लिखोl(पढ़ोl(qpriv->ecc_addr) |
			       ECC_DIS_ARMV8_CH2,
			       qpriv->ecc_addr);
		ग_लिखोl(AHCI_PORT_PHY_1_CFG, reg_base + PORT_PHY1);
		ग_लिखोl(AHCI_PORT_PHY2_CFG, reg_base + PORT_PHY2);
		ग_लिखोl(AHCI_PORT_PHY3_CFG, reg_base + PORT_PHY3);
		ग_लिखोl(AHCI_PORT_TRANS_CFG, reg_base + PORT_TRANS);
		अगर (qpriv->is_dmacoherent)
			ग_लिखोl(AHCI_PORT_AXICC_CFG, reg_base + PORT_AXICC);
		अवरोध;

	हाल AHCI_LS2080A:
		ग_लिखोl(AHCI_PORT_PHY_1_CFG, reg_base + PORT_PHY1);
		ग_लिखोl(AHCI_PORT_PHY2_CFG, reg_base + PORT_PHY2);
		ग_लिखोl(AHCI_PORT_PHY3_CFG, reg_base + PORT_PHY3);
		ग_लिखोl(AHCI_PORT_TRANS_CFG, reg_base + PORT_TRANS);
		अगर (qpriv->is_dmacoherent)
			ग_लिखोl(AHCI_PORT_AXICC_CFG, reg_base + PORT_AXICC);
		अवरोध;

	हाल AHCI_LS1046A:
		अगर (!(qpriv->ecc_addr || ecc_initialized))
			वापस -EINVAL;
		अन्यथा अगर (qpriv->ecc_addr && !ecc_initialized)
			ग_लिखोl(पढ़ोl(qpriv->ecc_addr) |
			       ECC_DIS_ARMV8_CH2,
			       qpriv->ecc_addr);
		ग_लिखोl(AHCI_PORT_PHY_1_CFG, reg_base + PORT_PHY1);
		ग_लिखोl(AHCI_PORT_PHY2_CFG, reg_base + PORT_PHY2);
		ग_लिखोl(AHCI_PORT_PHY3_CFG, reg_base + PORT_PHY3);
		ग_लिखोl(AHCI_PORT_TRANS_CFG, reg_base + PORT_TRANS);
		अगर (qpriv->is_dmacoherent)
			ग_लिखोl(AHCI_PORT_AXICC_CFG, reg_base + PORT_AXICC);
		अवरोध;

	हाल AHCI_LS1028A:
	हाल AHCI_LS1088A:
	हाल AHCI_LX2160A:
		अगर (!(qpriv->ecc_addr || ecc_initialized))
			वापस -EINVAL;
		अन्यथा अगर (qpriv->ecc_addr && !ecc_initialized)
			ग_लिखोl(पढ़ोl(qpriv->ecc_addr) |
			       ECC_DIS_LS1088A,
			       qpriv->ecc_addr);
		ग_लिखोl(AHCI_PORT_PHY_1_CFG, reg_base + PORT_PHY1);
		ग_लिखोl(AHCI_PORT_PHY2_CFG, reg_base + PORT_PHY2);
		ग_लिखोl(AHCI_PORT_PHY3_CFG, reg_base + PORT_PHY3);
		ग_लिखोl(AHCI_PORT_TRANS_CFG, reg_base + PORT_TRANS);
		अगर (qpriv->is_dmacoherent)
			ग_लिखोl(AHCI_PORT_AXICC_CFG, reg_base + PORT_AXICC);
		अवरोध;

	हाल AHCI_LS2088A:
		ग_लिखोl(AHCI_PORT_PHY_1_CFG, reg_base + PORT_PHY1);
		ग_लिखोl(AHCI_PORT_PHY2_CFG, reg_base + PORT_PHY2);
		ग_लिखोl(AHCI_PORT_PHY3_CFG, reg_base + PORT_PHY3);
		ग_लिखोl(AHCI_PORT_TRANS_CFG, reg_base + PORT_TRANS);
		अगर (qpriv->is_dmacoherent)
			ग_लिखोl(AHCI_PORT_AXICC_CFG, reg_base + PORT_AXICC);
		अवरोध;
	पूर्ण

	ecc_initialized = true;
	वापस 0;
पूर्ण

अटल पूर्णांक ahci_qoriq_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device_node *np = pdev->dev.of_node;
	स्थिर काष्ठा acpi_device_id *acpi_id;
	काष्ठा device *dev = &pdev->dev;
	काष्ठा ahci_host_priv *hpriv;
	काष्ठा ahci_qoriq_priv *qoriq_priv;
	स्थिर काष्ठा of_device_id *of_id;
	काष्ठा resource *res;
	पूर्णांक rc;

	hpriv = ahci_platक्रमm_get_resources(pdev, 0);
	अगर (IS_ERR(hpriv))
		वापस PTR_ERR(hpriv);

	of_id = of_match_node(ahci_qoriq_of_match, np);
	acpi_id = acpi_match_device(ahci_qoriq_acpi_match, &pdev->dev);
	अगर (!(of_id || acpi_id))
		वापस -ENODEV;

	qoriq_priv = devm_kzalloc(dev, माप(*qoriq_priv), GFP_KERNEL);
	अगर (!qoriq_priv)
		वापस -ENOMEM;

	अगर (of_id)
		qoriq_priv->type = (क्रमागत ahci_qoriq_type)of_id->data;
	अन्यथा
		qoriq_priv->type = (क्रमागत ahci_qoriq_type)acpi_id->driver_data;

	अगर (unlikely(!ecc_initialized)) अणु
		res = platक्रमm_get_resource_byname(pdev,
						   IORESOURCE_MEM,
						   "sata-ecc");
		अगर (res) अणु
			qoriq_priv->ecc_addr =
				devm_ioremap_resource(dev, res);
			अगर (IS_ERR(qoriq_priv->ecc_addr))
				वापस PTR_ERR(qoriq_priv->ecc_addr);
		पूर्ण
	पूर्ण

	अगर (device_get_dma_attr(&pdev->dev) == DEV_DMA_COHERENT)
		qoriq_priv->is_dmacoherent = true;

	rc = ahci_platक्रमm_enable_resources(hpriv);
	अगर (rc)
		वापस rc;

	hpriv->plat_data = qoriq_priv;
	rc = ahci_qoriq_phy_init(hpriv);
	अगर (rc)
		जाओ disable_resources;

	rc = ahci_platक्रमm_init_host(pdev, hpriv, &ahci_qoriq_port_info,
				     &ahci_qoriq_sht);
	अगर (rc)
		जाओ disable_resources;

	वापस 0;

disable_resources:
	ahci_platक्रमm_disable_resources(hpriv);

	वापस rc;
पूर्ण

#अगर_घोषित CONFIG_PM_SLEEP
अटल पूर्णांक ahci_qoriq_resume(काष्ठा device *dev)
अणु
	काष्ठा ata_host *host = dev_get_drvdata(dev);
	काष्ठा ahci_host_priv *hpriv = host->निजी_data;
	पूर्णांक rc;

	rc = ahci_platक्रमm_enable_resources(hpriv);
	अगर (rc)
		वापस rc;

	rc = ahci_qoriq_phy_init(hpriv);
	अगर (rc)
		जाओ disable_resources;

	rc = ahci_platक्रमm_resume_host(dev);
	अगर (rc)
		जाओ disable_resources;

	/* We resumed so update PM runसमय state */
	pm_runसमय_disable(dev);
	pm_runसमय_set_active(dev);
	pm_runसमय_enable(dev);

	वापस 0;

disable_resources:
	ahci_platक्रमm_disable_resources(hpriv);

	वापस rc;
पूर्ण
#पूर्ण_अगर

अटल SIMPLE_DEV_PM_OPS(ahci_qoriq_pm_ops, ahci_platक्रमm_suspend,
			 ahci_qoriq_resume);

अटल काष्ठा platक्रमm_driver ahci_qoriq_driver = अणु
	.probe = ahci_qoriq_probe,
	.हटाओ = ata_platक्रमm_हटाओ_one,
	.driver = अणु
		.name = DRV_NAME,
		.of_match_table = ahci_qoriq_of_match,
		.acpi_match_table = ahci_qoriq_acpi_match,
		.pm = &ahci_qoriq_pm_ops,
	पूर्ण,
पूर्ण;
module_platक्रमm_driver(ahci_qoriq_driver);

MODULE_DESCRIPTION("Freescale QorIQ AHCI SATA platform driver");
MODULE_AUTHOR("Tang Yuantian <Yuantian.Tang@freescale.com>");
MODULE_LICENSE("GPL");
