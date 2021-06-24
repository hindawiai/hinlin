<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (C) 2015 Xilinx, Inc.
 * CEVA AHCI SATA platक्रमm driver
 *
 * based on the AHCI SATA platक्रमm driver by Jeff Garzik and Anton Vorontsov
 */

#समावेश <linux/ahci_platक्रमm.h>
#समावेश <linux/kernel.h>
#समावेश <linux/libata.h>
#समावेश <linux/module.h>
#समावेश <linux/of_device.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/reset.h>
#समावेश "ahci.h"

/* Venकरोr Specअगरic Register Offsets */
#घोषणा AHCI_VEND_PCFG  0xA4
#घोषणा AHCI_VEND_PPCFG 0xA8
#घोषणा AHCI_VEND_PP2C  0xAC
#घोषणा AHCI_VEND_PP3C  0xB0
#घोषणा AHCI_VEND_PP4C  0xB4
#घोषणा AHCI_VEND_PP5C  0xB8
#घोषणा AHCI_VEND_AXICC 0xBC
#घोषणा AHCI_VEND_PAXIC 0xC0
#घोषणा AHCI_VEND_PTC   0xC8

/* Venकरोr Specअगरic Register bit definitions */
#घोषणा PAXIC_ADBW_BW64 0x1
#घोषणा PAXIC_MAWID(i)	(((i) * 2) << 4)
#घोषणा PAXIC_MARID(i)	(((i) * 2) << 12)
#घोषणा PAXIC_MARIDD(i)	((((i) * 2) + 1) << 16)
#घोषणा PAXIC_MAWIDD(i)	((((i) * 2) + 1) << 8)
#घोषणा PAXIC_OTL	(0x4 << 20)

/* Register bit definitions क्रम cache control */
#घोषणा AXICC_ARCA_VAL  (0xF << 0)
#घोषणा AXICC_ARCF_VAL  (0xF << 4)
#घोषणा AXICC_ARCH_VAL  (0xF << 8)
#घोषणा AXICC_ARCP_VAL  (0xF << 12)
#घोषणा AXICC_AWCFD_VAL (0xF << 16)
#घोषणा AXICC_AWCD_VAL  (0xF << 20)
#घोषणा AXICC_AWCF_VAL  (0xF << 24)

#घोषणा PCFG_TPSS_VAL	(0x32 << 16)
#घोषणा PCFG_TPRS_VAL	(0x2 << 12)
#घोषणा PCFG_PAD_VAL	0x2

#घोषणा PPCFG_TTA	0x1FFFE
#घोषणा PPCFG_PSSO_EN	(1 << 28)
#घोषणा PPCFG_PSS_EN	(1 << 29)
#घोषणा PPCFG_ESDF_EN	(1 << 31)

#घोषणा PP5C_RIT	0x60216
#घोषणा PP5C_RCT	(0x7f0 << 20)

#घोषणा PTC_RX_WM_VAL	0x40
#घोषणा PTC_RSVD	(1 << 27)

#घोषणा PORT0_BASE	0x100
#घोषणा PORT1_BASE	0x180

/* Port Control Register Bit Definitions */
#घोषणा PORT_SCTL_SPD_GEN3	(0x3 << 4)
#घोषणा PORT_SCTL_SPD_GEN2	(0x2 << 4)
#घोषणा PORT_SCTL_SPD_GEN1	(0x1 << 4)
#घोषणा PORT_SCTL_IPM		(0x3 << 8)

#घोषणा PORT_BASE	0x100
#घोषणा PORT_OFFSET	0x80
#घोषणा NR_PORTS	2
#घोषणा DRV_NAME	"ahci-ceva"
#घोषणा CEVA_FLAG_BROKEN_GEN2	1

अटल अचिन्हित पूर्णांक rx_watermark = PTC_RX_WM_VAL;
module_param(rx_watermark, uपूर्णांक, 0644);
MODULE_PARM_DESC(rx_watermark, "RxWaterMark value (0 - 0x80)");

काष्ठा ceva_ahci_priv अणु
	काष्ठा platक्रमm_device *ahci_pdev;
	/* Port Phy2Cfg Register */
	u32 pp2c[NR_PORTS];
	u32 pp3c[NR_PORTS];
	u32 pp4c[NR_PORTS];
	u32 pp5c[NR_PORTS];
	/* Axi Cache Control Register */
	u32 axicc;
	bool is_cci_enabled;
	पूर्णांक flags;
	काष्ठा reset_control *rst;
पूर्ण;

अटल अचिन्हित पूर्णांक ceva_ahci_पढ़ो_id(काष्ठा ata_device *dev,
					काष्ठा ata_taskfile *tf, u16 *id)
अणु
	u32 err_mask;

	err_mask = ata_करो_dev_पढ़ो_id(dev, tf, id);
	अगर (err_mask)
		वापस err_mask;
	/*
	 * Since CEVA controller करोes not support device sleep feature, we
	 * need to clear DEVSLP (bit 8) in word78 of the IDENTIFY DEVICE data.
	 */
	id[ATA_ID_FEATURE_SUPP] &= cpu_to_le16(~(1 << 8));

	वापस 0;
पूर्ण

अटल काष्ठा ata_port_operations ahci_ceva_ops = अणु
	.inherits = &ahci_platक्रमm_ops,
	.पढ़ो_id = ceva_ahci_पढ़ो_id,
पूर्ण;

अटल स्थिर काष्ठा ata_port_info ahci_ceva_port_info = अणु
	.flags          = AHCI_FLAG_COMMON,
	.pio_mask       = ATA_PIO4,
	.udma_mask      = ATA_UDMA6,
	.port_ops	= &ahci_ceva_ops,
पूर्ण;

अटल व्योम ahci_ceva_setup(काष्ठा ahci_host_priv *hpriv)
अणु
	व्योम __iomem *mmio = hpriv->mmio;
	काष्ठा ceva_ahci_priv *cevapriv = hpriv->plat_data;
	u32 पंचांगp;
	पूर्णांक i;

	/* Set AHCI Enable */
	पंचांगp = पढ़ोl(mmio + HOST_CTL);
	पंचांगp |= HOST_AHCI_EN;
	ग_लिखोl(पंचांगp, mmio + HOST_CTL);

	क्रम (i = 0; i < NR_PORTS; i++) अणु
		/* TPSS TPRS scalars, CISE and Port Addr */
		पंचांगp = PCFG_TPSS_VAL | PCFG_TPRS_VAL | (PCFG_PAD_VAL + i);
		ग_लिखोl(पंचांगp, mmio + AHCI_VEND_PCFG);

		/*
		 * AXI Data bus width to 64
		 * Set Mem Addr Read, Write ID क्रम data transfers
		 * Set Mem Addr Read ID, Write ID क्रम non-data transfers
		 * Transfer limit to 72 DWord
		 */
		पंचांगp = PAXIC_ADBW_BW64 | PAXIC_MAWIDD(i) | PAXIC_MARIDD(i) |
			PAXIC_MAWID(i) | PAXIC_MARID(i) | PAXIC_OTL;
		ग_लिखोl(पंचांगp, mmio + AHCI_VEND_PAXIC);

		/* Set AXI cache control रेजिस्टर अगर CCi is enabled */
		अगर (cevapriv->is_cci_enabled) अणु
			पंचांगp = पढ़ोl(mmio + AHCI_VEND_AXICC);
			पंचांगp |= AXICC_ARCA_VAL | AXICC_ARCF_VAL |
				AXICC_ARCH_VAL | AXICC_ARCP_VAL |
				AXICC_AWCFD_VAL | AXICC_AWCD_VAL |
				AXICC_AWCF_VAL;
			ग_लिखोl(पंचांगp, mmio + AHCI_VEND_AXICC);
		पूर्ण

		/* Port Phy Cfg रेजिस्टर enables */
		पंचांगp = PPCFG_TTA | PPCFG_PSS_EN | PPCFG_ESDF_EN;
		ग_लिखोl(पंचांगp, mmio + AHCI_VEND_PPCFG);

		/* Phy Control OOB timing parameters COMINIT */
		ग_लिखोl(cevapriv->pp2c[i], mmio + AHCI_VEND_PP2C);

		/* Phy Control OOB timing parameters COMWAKE */
		ग_लिखोl(cevapriv->pp3c[i], mmio + AHCI_VEND_PP3C);

		/* Phy Control Burst timing setting */
		ग_लिखोl(cevapriv->pp4c[i], mmio + AHCI_VEND_PP4C);

		/* Rate Change Timer and Retry Interval Timer setting */
		ग_लिखोl(cevapriv->pp5c[i], mmio + AHCI_VEND_PP5C);

		/* Rx Watermark setting  */
		पंचांगp = rx_watermark | PTC_RSVD;
		ग_लिखोl(पंचांगp, mmio + AHCI_VEND_PTC);

		/* Default to Gen 3 Speed and Gen 1 अगर Gen2 is broken */
		पंचांगp = PORT_SCTL_SPD_GEN3 | PORT_SCTL_IPM;
		अगर (cevapriv->flags & CEVA_FLAG_BROKEN_GEN2)
			पंचांगp = PORT_SCTL_SPD_GEN1 | PORT_SCTL_IPM;
		ग_लिखोl(पंचांगp, mmio + PORT_SCR_CTL + PORT_BASE + PORT_OFFSET * i);
	पूर्ण
पूर्ण

अटल काष्ठा scsi_host_ढाँचा ahci_platक्रमm_sht = अणु
	AHCI_SHT(DRV_NAME),
पूर्ण;

अटल पूर्णांक ceva_ahci_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device_node *np = pdev->dev.of_node;
	काष्ठा device *dev = &pdev->dev;
	काष्ठा ahci_host_priv *hpriv;
	काष्ठा ceva_ahci_priv *cevapriv;
	क्रमागत dev_dma_attr attr;
	पूर्णांक rc;

	cevapriv = devm_kzalloc(dev, माप(*cevapriv), GFP_KERNEL);
	अगर (!cevapriv)
		वापस -ENOMEM;

	cevapriv->ahci_pdev = pdev;

	cevapriv->rst = devm_reset_control_get_optional_exclusive(&pdev->dev,
								  शून्य);
	अगर (IS_ERR(cevapriv->rst))
		dev_err_probe(&pdev->dev, PTR_ERR(cevapriv->rst),
			      "failed to get reset\n");

	hpriv = ahci_platक्रमm_get_resources(pdev, 0);
	अगर (IS_ERR(hpriv))
		वापस PTR_ERR(hpriv);

	अगर (!cevapriv->rst) अणु
		rc = ahci_platक्रमm_enable_resources(hpriv);
		अगर (rc)
			वापस rc;
	पूर्ण अन्यथा अणु
		पूर्णांक i;

		rc = ahci_platक्रमm_enable_clks(hpriv);
		अगर (rc)
			वापस rc;
		/* Assert the controller reset */
		reset_control_निश्चित(cevapriv->rst);

		क्रम (i = 0; i < hpriv->nports; i++) अणु
			rc = phy_init(hpriv->phys[i]);
			अगर (rc)
				वापस rc;
		पूर्ण

		/* De-निश्चित the controller reset */
		reset_control_deनिश्चित(cevapriv->rst);

		क्रम (i = 0; i < hpriv->nports; i++) अणु
			rc = phy_घातer_on(hpriv->phys[i]);
			अगर (rc) अणु
				phy_निकास(hpriv->phys[i]);
				वापस rc;
			पूर्ण
		पूर्ण
	पूर्ण

	अगर (of_property_पढ़ो_bool(np, "ceva,broken-gen2"))
		cevapriv->flags = CEVA_FLAG_BROKEN_GEN2;

	/* Read OOB timing value क्रम COMINIT from device-tree */
	अगर (of_property_पढ़ो_u8_array(np, "ceva,p0-cominit-params",
					(u8 *)&cevapriv->pp2c[0], 4) < 0) अणु
		dev_warn(dev, "ceva,p0-cominit-params property not defined\n");
		वापस -EINVAL;
	पूर्ण

	अगर (of_property_पढ़ो_u8_array(np, "ceva,p1-cominit-params",
					(u8 *)&cevapriv->pp2c[1], 4) < 0) अणु
		dev_warn(dev, "ceva,p1-cominit-params property not defined\n");
		वापस -EINVAL;
	पूर्ण

	/* Read OOB timing value क्रम COMWAKE from device-tree*/
	अगर (of_property_पढ़ो_u8_array(np, "ceva,p0-comwake-params",
					(u8 *)&cevapriv->pp3c[0], 4) < 0) अणु
		dev_warn(dev, "ceva,p0-comwake-params property not defined\n");
		वापस -EINVAL;
	पूर्ण

	अगर (of_property_पढ़ो_u8_array(np, "ceva,p1-comwake-params",
					(u8 *)&cevapriv->pp3c[1], 4) < 0) अणु
		dev_warn(dev, "ceva,p1-comwake-params property not defined\n");
		वापस -EINVAL;
	पूर्ण

	/* Read phy BURST timing value from device-tree */
	अगर (of_property_पढ़ो_u8_array(np, "ceva,p0-burst-params",
					(u8 *)&cevapriv->pp4c[0], 4) < 0) अणु
		dev_warn(dev, "ceva,p0-burst-params property not defined\n");
		वापस -EINVAL;
	पूर्ण

	अगर (of_property_पढ़ो_u8_array(np, "ceva,p1-burst-params",
					(u8 *)&cevapriv->pp4c[1], 4) < 0) अणु
		dev_warn(dev, "ceva,p1-burst-params property not defined\n");
		वापस -EINVAL;
	पूर्ण

	/* Read phy RETRY पूर्णांकerval timing value from device-tree */
	अगर (of_property_पढ़ो_u16_array(np, "ceva,p0-retry-params",
					(u16 *)&cevapriv->pp5c[0], 2) < 0) अणु
		dev_warn(dev, "ceva,p0-retry-params property not defined\n");
		वापस -EINVAL;
	पूर्ण

	अगर (of_property_पढ़ो_u16_array(np, "ceva,p1-retry-params",
					(u16 *)&cevapriv->pp5c[1], 2) < 0) अणु
		dev_warn(dev, "ceva,p1-retry-params property not defined\n");
		वापस -EINVAL;
	पूर्ण

	/*
	 * Check अगर CCI is enabled क्रम SATA. The DEV_DMA_COHERENT is वापसed
	 * अगर CCI is enabled, so check क्रम DEV_DMA_COHERENT.
	 */
	attr = device_get_dma_attr(dev);
	cevapriv->is_cci_enabled = (attr == DEV_DMA_COHERENT);

	hpriv->plat_data = cevapriv;

	/* CEVA specअगरic initialization */
	ahci_ceva_setup(hpriv);

	rc = ahci_platक्रमm_init_host(pdev, hpriv, &ahci_ceva_port_info,
					&ahci_platक्रमm_sht);
	अगर (rc)
		जाओ disable_resources;

	वापस 0;

disable_resources:
	ahci_platक्रमm_disable_resources(hpriv);
	वापस rc;
पूर्ण

अटल पूर्णांक __maybe_unused ceva_ahci_suspend(काष्ठा device *dev)
अणु
	वापस ahci_platक्रमm_suspend(dev);
पूर्ण

अटल पूर्णांक __maybe_unused ceva_ahci_resume(काष्ठा device *dev)
अणु
	काष्ठा ata_host *host = dev_get_drvdata(dev);
	काष्ठा ahci_host_priv *hpriv = host->निजी_data;
	पूर्णांक rc;

	rc = ahci_platक्रमm_enable_resources(hpriv);
	अगर (rc)
		वापस rc;

	/* Configure CEVA specअगरic config beक्रमe resuming HBA */
	ahci_ceva_setup(hpriv);

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

अटल SIMPLE_DEV_PM_OPS(ahci_ceva_pm_ops, ceva_ahci_suspend, ceva_ahci_resume);

अटल स्थिर काष्ठा of_device_id ceva_ahci_of_match[] = अणु
	अणु .compatible = "ceva,ahci-1v84" पूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, ceva_ahci_of_match);

अटल काष्ठा platक्रमm_driver ceva_ahci_driver = अणु
	.probe = ceva_ahci_probe,
	.हटाओ = ata_platक्रमm_हटाओ_one,
	.driver = अणु
		.name = DRV_NAME,
		.of_match_table = ceva_ahci_of_match,
		.pm = &ahci_ceva_pm_ops,
	पूर्ण,
पूर्ण;
module_platक्रमm_driver(ceva_ahci_driver);

MODULE_DESCRIPTION("CEVA AHCI SATA platform driver");
MODULE_AUTHOR("Xilinx Inc.");
MODULE_LICENSE("GPL v2");
