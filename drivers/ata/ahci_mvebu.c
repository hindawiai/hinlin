<शैली गुरु>
/*
 * AHCI glue platक्रमm driver क्रम Marvell EBU SOCs
 *
 * Copyright (C) 2014 Marvell
 *
 * Thomas Petazzoni <thomas.petazzoni@मुक्त-electrons.com>
 * Marcin Wojtas <mw@semihalf.com>
 *
 * This file is licensed under the terms of the GNU General Public
 * License version 2.  This program is licensed "as is" without any
 * warranty of any kind, whether express or implied.
 */

#समावेश <linux/ahci_platक्रमm.h>
#समावेश <linux/kernel.h>
#समावेश <linux/mbus.h>
#समावेश <linux/module.h>
#समावेश <linux/of_device.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश "ahci.h"

#घोषणा DRV_NAME "ahci-mvebu"

#घोषणा AHCI_VENDOR_SPECIFIC_0_ADDR  0xa0
#घोषणा AHCI_VENDOR_SPECIFIC_0_DATA  0xa4

#घोषणा AHCI_WINDOW_CTRL(win)	(0x60 + ((win) << 4))
#घोषणा AHCI_WINDOW_BASE(win)	(0x64 + ((win) << 4))
#घोषणा AHCI_WINDOW_SIZE(win)	(0x68 + ((win) << 4))

काष्ठा ahci_mvebu_plat_data अणु
	पूर्णांक (*plat_config)(काष्ठा ahci_host_priv *hpriv);
	अचिन्हित पूर्णांक flags;
पूर्ण;

अटल व्योम ahci_mvebu_mbus_config(काष्ठा ahci_host_priv *hpriv,
				   स्थिर काष्ठा mbus_dram_target_info *dram)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < 4; i++) अणु
		ग_लिखोl(0, hpriv->mmio + AHCI_WINDOW_CTRL(i));
		ग_लिखोl(0, hpriv->mmio + AHCI_WINDOW_BASE(i));
		ग_लिखोl(0, hpriv->mmio + AHCI_WINDOW_SIZE(i));
	पूर्ण

	क्रम (i = 0; i < dram->num_cs; i++) अणु
		स्थिर काष्ठा mbus_dram_winकरोw *cs = dram->cs + i;

		ग_लिखोl((cs->mbus_attr << 8) |
		       (dram->mbus_dram_target_id << 4) | 1,
		       hpriv->mmio + AHCI_WINDOW_CTRL(i));
		ग_लिखोl(cs->base >> 16, hpriv->mmio + AHCI_WINDOW_BASE(i));
		ग_लिखोl(((cs->size - 1) & 0xffff0000),
		       hpriv->mmio + AHCI_WINDOW_SIZE(i));
	पूर्ण
पूर्ण

अटल व्योम ahci_mvebu_regret_option(काष्ठा ahci_host_priv *hpriv)
अणु
	/*
	 * Enable the regret bit to allow the SATA unit to regret a
	 * request that didn't receive an acknowlegde and aव्योम a
	 * deadlock
	 */
	ग_लिखोl(0x4, hpriv->mmio + AHCI_VENDOR_SPECIFIC_0_ADDR);
	ग_लिखोl(0x80, hpriv->mmio + AHCI_VENDOR_SPECIFIC_0_DATA);
पूर्ण

अटल पूर्णांक ahci_mvebu_armada_380_config(काष्ठा ahci_host_priv *hpriv)
अणु
	स्थिर काष्ठा mbus_dram_target_info *dram;
	पूर्णांक rc = 0;

	dram = mv_mbus_dram_info();
	अगर (dram)
		ahci_mvebu_mbus_config(hpriv, dram);
	अन्यथा
		rc = -ENODEV;

	ahci_mvebu_regret_option(hpriv);

	वापस rc;
पूर्ण

अटल पूर्णांक ahci_mvebu_armada_3700_config(काष्ठा ahci_host_priv *hpriv)
अणु
	u32 reg;

	ग_लिखोl(0, hpriv->mmio + AHCI_VENDOR_SPECIFIC_0_ADDR);

	reg = पढ़ोl(hpriv->mmio + AHCI_VENDOR_SPECIFIC_0_DATA);
	reg |= BIT(6);
	ग_लिखोl(reg, hpriv->mmio + AHCI_VENDOR_SPECIFIC_0_DATA);

	वापस 0;
पूर्ण

/**
 * ahci_mvebu_stop_engine
 *
 * @ap:	Target ata port
 *
 * Errata Ref#226 - SATA Disk HOT swap issue when connected through
 * Port Multiplier in FIS-based Switching mode.
 *
 * To aव्योम the issue, according to design, the bits[11:8, 0] of
 * रेजिस्टर PxFBS are cleared when Port Command and Status (0x18) bit[0]
 * changes its value from 1 to 0, i.e. falling edge of Port
 * Command and Status bit[0] sends PULSE that resets PxFBS
 * bits[11:8; 0].
 *
 * This function is used to override function of "ahci_stop_engine"
 * from libahci.c by adding the mvebu work around(WA) to save PxFBS
 * value beक्रमe the PxCMD ST ग_लिखो of 0, then restore PxFBS value.
 *
 * Return: 0 on success; Error code otherwise.
 */
अटल पूर्णांक ahci_mvebu_stop_engine(काष्ठा ata_port *ap)
अणु
	व्योम __iomem *port_mmio = ahci_port_base(ap);
	u32 पंचांगp, port_fbs;

	पंचांगp = पढ़ोl(port_mmio + PORT_CMD);

	/* check अगर the HBA is idle */
	अगर ((पंचांगp & (PORT_CMD_START | PORT_CMD_LIST_ON)) == 0)
		वापस 0;

	/* save the port PxFBS रेजिस्टर क्रम later restore */
	port_fbs = पढ़ोl(port_mmio + PORT_FBS);

	/* setting HBA to idle */
	पंचांगp &= ~PORT_CMD_START;
	ग_लिखोl(पंचांगp, port_mmio + PORT_CMD);

	/*
	 * bit #15 PxCMD संकेत करोesn't clear PxFBS,
	 * restore the PxFBS रेजिस्टर right after clearing the PxCMD ST,
	 * no need to रुको क्रम the PxCMD bit #15.
	 */
	ग_लिखोl(port_fbs, port_mmio + PORT_FBS);

	/* रुको क्रम engine to stop. This could be as दीर्घ as 500 msec */
	पंचांगp = ata_रुको_रेजिस्टर(ap, port_mmio + PORT_CMD,
				PORT_CMD_LIST_ON, PORT_CMD_LIST_ON, 1, 500);
	अगर (पंचांगp & PORT_CMD_LIST_ON)
		वापस -EIO;

	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_PM_SLEEP
अटल पूर्णांक ahci_mvebu_suspend(काष्ठा platक्रमm_device *pdev, pm_message_t state)
अणु
	वापस ahci_platक्रमm_suspend_host(&pdev->dev);
पूर्ण

अटल पूर्णांक ahci_mvebu_resume(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा ata_host *host = platक्रमm_get_drvdata(pdev);
	काष्ठा ahci_host_priv *hpriv = host->निजी_data;
	स्थिर काष्ठा ahci_mvebu_plat_data *pdata = hpriv->plat_data;

	pdata->plat_config(hpriv);

	वापस ahci_platक्रमm_resume_host(&pdev->dev);
पूर्ण
#अन्यथा
#घोषणा ahci_mvebu_suspend शून्य
#घोषणा ahci_mvebu_resume शून्य
#पूर्ण_अगर

अटल स्थिर काष्ठा ata_port_info ahci_mvebu_port_info = अणु
	.flags	   = AHCI_FLAG_COMMON,
	.pio_mask  = ATA_PIO4,
	.udma_mask = ATA_UDMA6,
	.port_ops  = &ahci_platक्रमm_ops,
पूर्ण;

अटल काष्ठा scsi_host_ढाँचा ahci_platक्रमm_sht = अणु
	AHCI_SHT(DRV_NAME),
पूर्ण;

अटल पूर्णांक ahci_mvebu_probe(काष्ठा platक्रमm_device *pdev)
अणु
	स्थिर काष्ठा ahci_mvebu_plat_data *pdata;
	काष्ठा ahci_host_priv *hpriv;
	पूर्णांक rc;

	pdata = of_device_get_match_data(&pdev->dev);
	अगर (!pdata)
		वापस -EINVAL;

	hpriv = ahci_platक्रमm_get_resources(pdev, 0);
	अगर (IS_ERR(hpriv))
		वापस PTR_ERR(hpriv);

	hpriv->flags |= pdata->flags;
	hpriv->plat_data = (व्योम *)pdata;

	rc = ahci_platक्रमm_enable_resources(hpriv);
	अगर (rc)
		वापस rc;

	hpriv->stop_engine = ahci_mvebu_stop_engine;

	rc = pdata->plat_config(hpriv);
	अगर (rc)
		जाओ disable_resources;

	rc = ahci_platक्रमm_init_host(pdev, hpriv, &ahci_mvebu_port_info,
				     &ahci_platक्रमm_sht);
	अगर (rc)
		जाओ disable_resources;

	वापस 0;

disable_resources:
	ahci_platक्रमm_disable_resources(hpriv);
	वापस rc;
पूर्ण

अटल स्थिर काष्ठा ahci_mvebu_plat_data ahci_mvebu_armada_380_plat_data = अणु
	.plat_config = ahci_mvebu_armada_380_config,
पूर्ण;

अटल स्थिर काष्ठा ahci_mvebu_plat_data ahci_mvebu_armada_3700_plat_data = अणु
	.plat_config = ahci_mvebu_armada_3700_config,
	.flags = AHCI_HFLAG_SUSPEND_PHYS | AHCI_HFLAG_IGN_NOTSUPP_POWER_ON,
पूर्ण;

अटल स्थिर काष्ठा of_device_id ahci_mvebu_of_match[] = अणु
	अणु
		.compatible = "marvell,armada-380-ahci",
		.data = &ahci_mvebu_armada_380_plat_data,
	पूर्ण,
	अणु
		.compatible = "marvell,armada-3700-ahci",
		.data = &ahci_mvebu_armada_3700_plat_data,
	पूर्ण,
	अणु पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, ahci_mvebu_of_match);

अटल काष्ठा platक्रमm_driver ahci_mvebu_driver = अणु
	.probe = ahci_mvebu_probe,
	.हटाओ = ata_platक्रमm_हटाओ_one,
	.suspend = ahci_mvebu_suspend,
	.resume = ahci_mvebu_resume,
	.driver = अणु
		.name = DRV_NAME,
		.of_match_table = ahci_mvebu_of_match,
	पूर्ण,
पूर्ण;
module_platक्रमm_driver(ahci_mvebu_driver);

MODULE_DESCRIPTION("Marvell EBU AHCI SATA driver");
MODULE_AUTHOR("Thomas Petazzoni <thomas.petazzoni@free-electrons.com>, Marcin Wojtas <mw@semihalf.com>");
MODULE_LICENSE("GPL");
MODULE_ALIAS("platform:ahci_mvebu");
