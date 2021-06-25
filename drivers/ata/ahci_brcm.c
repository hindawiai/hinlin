<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Broadcom SATA3 AHCI Controller Driver
 *
 * Copyright तऊ 2009-2015 Broadcom Corporation
 */

#समावेश <linux/ahci_platक्रमm.h>
#समावेश <linux/compiler.h>
#समावेश <linux/device.h>
#समावेश <linux/init.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/पन.स>
#समावेश <linux/kernel.h>
#समावेश <linux/libata.h>
#समावेश <linux/module.h>
#समावेश <linux/of.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/reset.h>
#समावेश <linux/माला.स>

#समावेश "ahci.h"

#घोषणा DRV_NAME					"brcm-ahci"

#घोषणा SATA_TOP_CTRL_VERSION				0x0
#घोषणा SATA_TOP_CTRL_BUS_CTRL				0x4
 #घोषणा MMIO_ENDIAN_SHIFT				0 /* CPU->AHCI */
 #घोषणा DMADESC_ENDIAN_SHIFT				2 /* AHCI->DDR */
 #घोषणा DMADATA_ENDIAN_SHIFT				4 /* AHCI->DDR */
 #घोषणा PIODATA_ENDIAN_SHIFT				6
  #घोषणा ENDIAN_SWAP_NONE				0
  #घोषणा ENDIAN_SWAP_FULL				2
#घोषणा SATA_TOP_CTRL_TP_CTRL				0x8
#घोषणा SATA_TOP_CTRL_PHY_CTRL				0xc
 #घोषणा SATA_TOP_CTRL_PHY_CTRL_1			0x0
  #घोषणा SATA_TOP_CTRL_1_PHY_DEFAULT_POWER_STATE	BIT(14)
 #घोषणा SATA_TOP_CTRL_PHY_CTRL_2			0x4
  #घोषणा SATA_TOP_CTRL_2_SW_RST_MDIOREG		BIT(0)
  #घोषणा SATA_TOP_CTRL_2_SW_RST_OOB			BIT(1)
  #घोषणा SATA_TOP_CTRL_2_SW_RST_RX			BIT(2)
  #घोषणा SATA_TOP_CTRL_2_SW_RST_TX			BIT(3)
  #घोषणा SATA_TOP_CTRL_2_PHY_GLOBAL_RESET		BIT(14)
 #घोषणा SATA_TOP_CTRL_PHY_OFFS				0x8
 #घोषणा SATA_TOP_MAX_PHYS				2

#घोषणा SATA_FIRST_PORT_CTRL				0x700
#घोषणा SATA_NEXT_PORT_CTRL_OFFSET			0x80
#घोषणा SATA_PORT_PCTRL6(reg_base)			(reg_base + 0x18)

/* On big-endian MIPS, buses are reversed to big endian, so चयन them back */
#अगर defined(CONFIG_MIPS) && defined(__BIG_ENDIAN)
#घोषणा DATA_ENDIAN			 2 /* AHCI->DDR inbound accesses */
#घोषणा MMIO_ENDIAN			 2 /* CPU->AHCI outbound accesses */
#अन्यथा
#घोषणा DATA_ENDIAN			 0
#घोषणा MMIO_ENDIAN			 0
#पूर्ण_अगर

#घोषणा BUS_CTRL_ENDIAN_CONF				\
	((DATA_ENDIAN << DMADATA_ENDIAN_SHIFT) |	\
	(DATA_ENDIAN << DMADESC_ENDIAN_SHIFT) |		\
	(MMIO_ENDIAN << MMIO_ENDIAN_SHIFT))

#घोषणा BUS_CTRL_ENDIAN_NSP_CONF			\
	(0x02 << DMADATA_ENDIAN_SHIFT | 0x02 << DMADESC_ENDIAN_SHIFT)

#घोषणा BUS_CTRL_ENDIAN_CONF_MASK			\
	(0x3 << MMIO_ENDIAN_SHIFT | 0x3 << DMADESC_ENDIAN_SHIFT |	\
	 0x3 << DMADATA_ENDIAN_SHIFT | 0x3 << PIODATA_ENDIAN_SHIFT)

क्रमागत brcm_ahci_version अणु
	BRCM_SATA_BCM7425 = 1,
	BRCM_SATA_BCM7445,
	BRCM_SATA_NSP,
	BRCM_SATA_BCM7216,
पूर्ण;

क्रमागत brcm_ahci_quirks अणु
	BRCM_AHCI_QUIRK_SKIP_PHY_ENABLE	= BIT(0),
पूर्ण;

काष्ठा brcm_ahci_priv अणु
	काष्ठा device *dev;
	व्योम __iomem *top_ctrl;
	u32 port_mask;
	u32 quirks;
	क्रमागत brcm_ahci_version version;
	काष्ठा reset_control *rcdev_rescal;
	काष्ठा reset_control *rcdev_ahci;
पूर्ण;

अटल अंतरभूत u32 brcm_sata_पढ़ोreg(व्योम __iomem *addr)
अणु
	/*
	 * MIPS endianness is configured by boot strap, which also reverses all
	 * bus endianness (i.e., big-endian CPU + big endian bus ==> native
	 * endian I/O).
	 *
	 * Other architectures (e.g., ARM) either करो not support big endian, or
	 * अन्यथा leave I/O in little endian mode.
	 */
	अगर (IS_ENABLED(CONFIG_MIPS) && IS_ENABLED(CONFIG_CPU_BIG_ENDIAN))
		वापस __raw_पढ़ोl(addr);
	अन्यथा
		वापस पढ़ोl_relaxed(addr);
पूर्ण

अटल अंतरभूत व्योम brcm_sata_ग_लिखोreg(u32 val, व्योम __iomem *addr)
अणु
	/* See brcm_sata_पढ़ोreg() comments */
	अगर (IS_ENABLED(CONFIG_MIPS) && IS_ENABLED(CONFIG_CPU_BIG_ENDIAN))
		__raw_ग_लिखोl(val, addr);
	अन्यथा
		ग_लिखोl_relaxed(val, addr);
पूर्ण

अटल व्योम brcm_sata_alpm_init(काष्ठा ahci_host_priv *hpriv)
अणु
	काष्ठा brcm_ahci_priv *priv = hpriv->plat_data;
	u32 port_ctrl, host_caps;
	पूर्णांक i;

	/* Enable support क्रम ALPM */
	host_caps = पढ़ोl(hpriv->mmio + HOST_CAP);
	अगर (!(host_caps & HOST_CAP_ALPM))
		hpriv->flags |= AHCI_HFLAG_YES_ALPM;

	/*
	 * Adjust समयout to allow PLL sufficient समय to lock जबतक waking
	 * up from slumber mode.
	 */
	क्रम (i = 0, port_ctrl = SATA_FIRST_PORT_CTRL;
	     i < SATA_TOP_MAX_PHYS;
	     i++, port_ctrl += SATA_NEXT_PORT_CTRL_OFFSET) अणु
		अगर (priv->port_mask & BIT(i))
			ग_लिखोl(0xff1003fc,
			       hpriv->mmio + SATA_PORT_PCTRL6(port_ctrl));
	पूर्ण
पूर्ण

अटल व्योम brcm_sata_phy_enable(काष्ठा brcm_ahci_priv *priv, पूर्णांक port)
अणु
	व्योम __iomem *phyctrl = priv->top_ctrl + SATA_TOP_CTRL_PHY_CTRL +
				(port * SATA_TOP_CTRL_PHY_OFFS);
	व्योम __iomem *p;
	u32 reg;

	अगर (priv->quirks & BRCM_AHCI_QUIRK_SKIP_PHY_ENABLE)
		वापस;

	/* clear PHY_DEFAULT_POWER_STATE */
	p = phyctrl + SATA_TOP_CTRL_PHY_CTRL_1;
	reg = brcm_sata_पढ़ोreg(p);
	reg &= ~SATA_TOP_CTRL_1_PHY_DEFAULT_POWER_STATE;
	brcm_sata_ग_लिखोreg(reg, p);

	/* reset the PHY digital logic */
	p = phyctrl + SATA_TOP_CTRL_PHY_CTRL_2;
	reg = brcm_sata_पढ़ोreg(p);
	reg &= ~(SATA_TOP_CTRL_2_SW_RST_MDIOREG | SATA_TOP_CTRL_2_SW_RST_OOB |
		 SATA_TOP_CTRL_2_SW_RST_RX);
	reg |= SATA_TOP_CTRL_2_SW_RST_TX;
	brcm_sata_ग_लिखोreg(reg, p);
	reg = brcm_sata_पढ़ोreg(p);
	reg |= SATA_TOP_CTRL_2_PHY_GLOBAL_RESET;
	brcm_sata_ग_लिखोreg(reg, p);
	reg = brcm_sata_पढ़ोreg(p);
	reg &= ~SATA_TOP_CTRL_2_PHY_GLOBAL_RESET;
	brcm_sata_ग_लिखोreg(reg, p);
	(व्योम)brcm_sata_पढ़ोreg(p);
पूर्ण

अटल व्योम brcm_sata_phy_disable(काष्ठा brcm_ahci_priv *priv, पूर्णांक port)
अणु
	व्योम __iomem *phyctrl = priv->top_ctrl + SATA_TOP_CTRL_PHY_CTRL +
				(port * SATA_TOP_CTRL_PHY_OFFS);
	व्योम __iomem *p;
	u32 reg;

	अगर (priv->quirks & BRCM_AHCI_QUIRK_SKIP_PHY_ENABLE)
		वापस;

	/* घातer-off the PHY digital logic */
	p = phyctrl + SATA_TOP_CTRL_PHY_CTRL_2;
	reg = brcm_sata_पढ़ोreg(p);
	reg |= (SATA_TOP_CTRL_2_SW_RST_MDIOREG | SATA_TOP_CTRL_2_SW_RST_OOB |
		SATA_TOP_CTRL_2_SW_RST_RX | SATA_TOP_CTRL_2_SW_RST_TX |
		SATA_TOP_CTRL_2_PHY_GLOBAL_RESET);
	brcm_sata_ग_लिखोreg(reg, p);

	/* set PHY_DEFAULT_POWER_STATE */
	p = phyctrl + SATA_TOP_CTRL_PHY_CTRL_1;
	reg = brcm_sata_पढ़ोreg(p);
	reg |= SATA_TOP_CTRL_1_PHY_DEFAULT_POWER_STATE;
	brcm_sata_ग_लिखोreg(reg, p);
पूर्ण

अटल व्योम brcm_sata_phys_enable(काष्ठा brcm_ahci_priv *priv)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < SATA_TOP_MAX_PHYS; i++)
		अगर (priv->port_mask & BIT(i))
			brcm_sata_phy_enable(priv, i);
पूर्ण

अटल व्योम brcm_sata_phys_disable(काष्ठा brcm_ahci_priv *priv)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < SATA_TOP_MAX_PHYS; i++)
		अगर (priv->port_mask & BIT(i))
			brcm_sata_phy_disable(priv, i);
पूर्ण

अटल u32 brcm_ahci_get_porपंचांगask(काष्ठा ahci_host_priv *hpriv,
				  काष्ठा brcm_ahci_priv *priv)
अणु
	u32 impl;

	impl = पढ़ोl(hpriv->mmio + HOST_PORTS_IMPL);

	अगर (fls(impl) > SATA_TOP_MAX_PHYS)
		dev_warn(priv->dev, "warning: more ports than PHYs (%#x)\n",
			 impl);
	अन्यथा अगर (!impl)
		dev_info(priv->dev, "no ports found\n");

	वापस impl;
पूर्ण

अटल व्योम brcm_sata_init(काष्ठा brcm_ahci_priv *priv)
अणु
	व्योम __iomem *ctrl = priv->top_ctrl + SATA_TOP_CTRL_BUS_CTRL;
	u32 data;

	/* Configure endianness */
	data = brcm_sata_पढ़ोreg(ctrl);
	data &= ~BUS_CTRL_ENDIAN_CONF_MASK;
	अगर (priv->version == BRCM_SATA_NSP)
		data |= BUS_CTRL_ENDIAN_NSP_CONF;
	अन्यथा
		data |= BUS_CTRL_ENDIAN_CONF;
	brcm_sata_ग_लिखोreg(data, ctrl);
पूर्ण

अटल अचिन्हित पूर्णांक brcm_ahci_पढ़ो_id(काष्ठा ata_device *dev,
				      काष्ठा ata_taskfile *tf, u16 *id)
अणु
	काष्ठा ata_port *ap = dev->link->ap;
	काष्ठा ata_host *host = ap->host;
	काष्ठा ahci_host_priv *hpriv = host->निजी_data;
	काष्ठा brcm_ahci_priv *priv = hpriv->plat_data;
	व्योम __iomem *mmio = hpriv->mmio;
	अचिन्हित पूर्णांक err_mask;
	अचिन्हित दीर्घ flags;
	पूर्णांक i, rc;
	u32 ctl;

	/* Try to पढ़ो the device ID and, अगर this fails, proceed with the
	 * recovery sequence below
	 */
	err_mask = ata_करो_dev_पढ़ो_id(dev, tf, id);
	अगर (likely(!err_mask))
		वापस err_mask;

	/* Disable host पूर्णांकerrupts */
	spin_lock_irqsave(&host->lock, flags);
	ctl = पढ़ोl(mmio + HOST_CTL);
	ctl &= ~HOST_IRQ_EN;
	ग_लिखोl(ctl, mmio + HOST_CTL);
	पढ़ोl(mmio + HOST_CTL); /* flush */
	spin_unlock_irqrestore(&host->lock, flags);

	/* Perक्रमm the SATA PHY reset sequence */
	brcm_sata_phy_disable(priv, ap->port_no);

	/* Reset the SATA घड़ी */
	ahci_platक्रमm_disable_clks(hpriv);
	msleep(10);

	ahci_platक्रमm_enable_clks(hpriv);
	msleep(10);

	/* Bring the PHY back on */
	brcm_sata_phy_enable(priv, ap->port_no);

	/* Re-initialize and calibrate the PHY */
	क्रम (i = 0; i < hpriv->nports; i++) अणु
		rc = phy_init(hpriv->phys[i]);
		अगर (rc)
			जाओ disable_phys;

		rc = phy_calibrate(hpriv->phys[i]);
		अगर (rc) अणु
			phy_निकास(hpriv->phys[i]);
			जाओ disable_phys;
		पूर्ण
	पूर्ण

	/* Re-enable host पूर्णांकerrupts */
	spin_lock_irqsave(&host->lock, flags);
	ctl = पढ़ोl(mmio + HOST_CTL);
	ctl |= HOST_IRQ_EN;
	ग_लिखोl(ctl, mmio + HOST_CTL);
	पढ़ोl(mmio + HOST_CTL); /* flush */
	spin_unlock_irqrestore(&host->lock, flags);

	वापस ata_करो_dev_पढ़ो_id(dev, tf, id);

disable_phys:
	जबतक (--i >= 0) अणु
		phy_घातer_off(hpriv->phys[i]);
		phy_निकास(hpriv->phys[i]);
	पूर्ण

	वापस AC_ERR_OTHER;
पूर्ण

अटल व्योम brcm_ahci_host_stop(काष्ठा ata_host *host)
अणु
	काष्ठा ahci_host_priv *hpriv = host->निजी_data;

	ahci_platक्रमm_disable_resources(hpriv);
पूर्ण

अटल काष्ठा ata_port_operations ahci_brcm_platक्रमm_ops = अणु
	.inherits	= &ahci_ops,
	.host_stop	= brcm_ahci_host_stop,
	.पढ़ो_id	= brcm_ahci_पढ़ो_id,
पूर्ण;

अटल स्थिर काष्ठा ata_port_info ahci_brcm_port_info = अणु
	.flags		= AHCI_FLAG_COMMON | ATA_FLAG_NO_DIPM,
	.link_flags	= ATA_LFLAG_NO_DB_DELAY,
	.pio_mask	= ATA_PIO4,
	.udma_mask	= ATA_UDMA6,
	.port_ops	= &ahci_brcm_platक्रमm_ops,
पूर्ण;

अटल पूर्णांक brcm_ahci_suspend(काष्ठा device *dev)
अणु
	काष्ठा ata_host *host = dev_get_drvdata(dev);
	काष्ठा ahci_host_priv *hpriv = host->निजी_data;
	काष्ठा brcm_ahci_priv *priv = hpriv->plat_data;
	पूर्णांक ret;

	brcm_sata_phys_disable(priv);

	अगर (IS_ENABLED(CONFIG_PM_SLEEP))
		ret = ahci_platक्रमm_suspend(dev);
	अन्यथा
		ret = 0;

	reset_control_निश्चित(priv->rcdev_ahci);
	reset_control_rearm(priv->rcdev_rescal);

	वापस ret;
पूर्ण

अटल पूर्णांक __maybe_unused brcm_ahci_resume(काष्ठा device *dev)
अणु
	काष्ठा ata_host *host = dev_get_drvdata(dev);
	काष्ठा ahci_host_priv *hpriv = host->निजी_data;
	काष्ठा brcm_ahci_priv *priv = hpriv->plat_data;
	पूर्णांक ret = 0;

	ret = reset_control_deनिश्चित(priv->rcdev_ahci);
	अगर (ret)
		वापस ret;
	ret = reset_control_reset(priv->rcdev_rescal);
	अगर (ret)
		वापस ret;

	/* Make sure घड़ीs are turned on beक्रमe re-configuration */
	ret = ahci_platक्रमm_enable_clks(hpriv);
	अगर (ret)
		वापस ret;

	ret = ahci_platक्रमm_enable_regulators(hpriv);
	अगर (ret)
		जाओ out_disable_clks;

	brcm_sata_init(priv);
	brcm_sata_phys_enable(priv);
	brcm_sata_alpm_init(hpriv);

	/* Since we had to enable घड़ीs earlier on, we cannot use
	 * ahci_platक्रमm_resume() as-is since a second call to
	 * ahci_platक्रमm_enable_resources() would bump up the resources
	 * (regulators, घड़ीs, PHYs) count artअगरicially so we copy the part
	 * after ahci_platक्रमm_enable_resources().
	 */
	ret = ahci_platक्रमm_enable_phys(hpriv);
	अगर (ret)
		जाओ out_disable_phys;

	ret = ahci_platक्रमm_resume_host(dev);
	अगर (ret)
		जाओ out_disable_platक्रमm_phys;

	/* We resumed so update PM runसमय state */
	pm_runसमय_disable(dev);
	pm_runसमय_set_active(dev);
	pm_runसमय_enable(dev);

	वापस 0;

out_disable_platक्रमm_phys:
	ahci_platक्रमm_disable_phys(hpriv);
out_disable_phys:
	brcm_sata_phys_disable(priv);
	ahci_platक्रमm_disable_regulators(hpriv);
out_disable_clks:
	ahci_platक्रमm_disable_clks(hpriv);
	वापस ret;
पूर्ण

अटल काष्ठा scsi_host_ढाँचा ahci_platक्रमm_sht = अणु
	AHCI_SHT(DRV_NAME),
पूर्ण;

अटल स्थिर काष्ठा of_device_id ahci_of_match[] = अणु
	अणु.compatible = "brcm,bcm7425-ahci", .data = (व्योम *)BRCM_SATA_BCM7425पूर्ण,
	अणु.compatible = "brcm,bcm7445-ahci", .data = (व्योम *)BRCM_SATA_BCM7445पूर्ण,
	अणु.compatible = "brcm,bcm63138-ahci", .data = (व्योम *)BRCM_SATA_BCM7445पूर्ण,
	अणु.compatible = "brcm,bcm-nsp-ahci", .data = (व्योम *)BRCM_SATA_NSPपूर्ण,
	अणु.compatible = "brcm,bcm7216-ahci", .data = (व्योम *)BRCM_SATA_BCM7216पूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, ahci_of_match);

अटल पूर्णांक brcm_ahci_probe(काष्ठा platक्रमm_device *pdev)
अणु
	स्थिर काष्ठा of_device_id *of_id;
	काष्ठा device *dev = &pdev->dev;
	काष्ठा brcm_ahci_priv *priv;
	काष्ठा ahci_host_priv *hpriv;
	काष्ठा resource *res;
	पूर्णांक ret;

	priv = devm_kzalloc(dev, माप(*priv), GFP_KERNEL);
	अगर (!priv)
		वापस -ENOMEM;

	of_id = of_match_node(ahci_of_match, pdev->dev.of_node);
	अगर (!of_id)
		वापस -ENODEV;

	priv->version = (क्रमागत brcm_ahci_version)of_id->data;
	priv->dev = dev;

	res = platक्रमm_get_resource_byname(pdev, IORESOURCE_MEM, "top-ctrl");
	priv->top_ctrl = devm_ioremap_resource(dev, res);
	अगर (IS_ERR(priv->top_ctrl))
		वापस PTR_ERR(priv->top_ctrl);

	अगर (priv->version == BRCM_SATA_BCM7216) अणु
		priv->rcdev_rescal = devm_reset_control_get_optional_shared(
			&pdev->dev, "rescal");
		अगर (IS_ERR(priv->rcdev_rescal))
			वापस PTR_ERR(priv->rcdev_rescal);
	पूर्ण
	priv->rcdev_ahci = devm_reset_control_get_optional(&pdev->dev, "ahci");
	अगर (IS_ERR(priv->rcdev_ahci))
		वापस PTR_ERR(priv->rcdev_ahci);

	hpriv = ahci_platक्रमm_get_resources(pdev, 0);
	अगर (IS_ERR(hpriv))
		वापस PTR_ERR(hpriv);

	hpriv->plat_data = priv;
	hpriv->flags = AHCI_HFLAG_WAKE_BEFORE_STOP | AHCI_HFLAG_NO_WRITE_TO_RO;

	चयन (priv->version) अणु
	हाल BRCM_SATA_BCM7425:
		hpriv->flags |= AHCI_HFLAG_DELAY_ENGINE;
		fallthrough;
	हाल BRCM_SATA_NSP:
		hpriv->flags |= AHCI_HFLAG_NO_NCQ;
		priv->quirks |= BRCM_AHCI_QUIRK_SKIP_PHY_ENABLE;
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	ret = reset_control_reset(priv->rcdev_rescal);
	अगर (ret)
		वापस ret;
	ret = reset_control_deनिश्चित(priv->rcdev_ahci);
	अगर (ret)
		वापस ret;

	ret = ahci_platक्रमm_enable_clks(hpriv);
	अगर (ret)
		जाओ out_reset;

	ret = ahci_platक्रमm_enable_regulators(hpriv);
	अगर (ret)
		जाओ out_disable_clks;

	/* Must be first so as to configure endianness including that
	 * of the standard AHCI रेजिस्टर space.
	 */
	brcm_sata_init(priv);

	/* Initializes priv->port_mask which is used below */
	priv->port_mask = brcm_ahci_get_porपंचांगask(hpriv, priv);
	अगर (!priv->port_mask) अणु
		ret = -ENODEV;
		जाओ out_disable_regulators;
	पूर्ण

	/* Must be करोne beक्रमe ahci_platक्रमm_enable_phys() */
	brcm_sata_phys_enable(priv);

	brcm_sata_alpm_init(hpriv);

	ret = ahci_platक्रमm_enable_phys(hpriv);
	अगर (ret)
		जाओ out_disable_phys;

	ret = ahci_platक्रमm_init_host(pdev, hpriv, &ahci_brcm_port_info,
				      &ahci_platक्रमm_sht);
	अगर (ret)
		जाओ out_disable_platक्रमm_phys;

	dev_info(dev, "Broadcom AHCI SATA3 registered\n");

	वापस 0;

out_disable_platक्रमm_phys:
	ahci_platक्रमm_disable_phys(hpriv);
out_disable_phys:
	brcm_sata_phys_disable(priv);
out_disable_regulators:
	ahci_platक्रमm_disable_regulators(hpriv);
out_disable_clks:
	ahci_platक्रमm_disable_clks(hpriv);
out_reset:
	reset_control_निश्चित(priv->rcdev_ahci);
	reset_control_rearm(priv->rcdev_rescal);
	वापस ret;
पूर्ण

अटल पूर्णांक brcm_ahci_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा ata_host *host = dev_get_drvdata(&pdev->dev);
	काष्ठा ahci_host_priv *hpriv = host->निजी_data;
	काष्ठा brcm_ahci_priv *priv = hpriv->plat_data;
	पूर्णांक ret;

	brcm_sata_phys_disable(priv);

	ret = ata_platक्रमm_हटाओ_one(pdev);
	अगर (ret)
		वापस ret;

	वापस 0;
पूर्ण

अटल व्योम brcm_ahci_shutकरोwn(काष्ठा platक्रमm_device *pdev)
अणु
	पूर्णांक ret;

	/* All resources releasing happens via devres, but our device, unlike a
	 * proper हटाओ is not disappearing, thereक्रमe using
	 * brcm_ahci_suspend() here which करोes explicit घातer management is
	 * appropriate.
	 */
	ret = brcm_ahci_suspend(&pdev->dev);
	अगर (ret)
		dev_err(&pdev->dev, "failed to shutdown\n");
पूर्ण

अटल SIMPLE_DEV_PM_OPS(ahci_brcm_pm_ops, brcm_ahci_suspend, brcm_ahci_resume);

अटल काष्ठा platक्रमm_driver brcm_ahci_driver = अणु
	.probe = brcm_ahci_probe,
	.हटाओ = brcm_ahci_हटाओ,
	.shutकरोwn = brcm_ahci_shutकरोwn,
	.driver = अणु
		.name = DRV_NAME,
		.of_match_table = ahci_of_match,
		.pm = &ahci_brcm_pm_ops,
	पूर्ण,
पूर्ण;
module_platक्रमm_driver(brcm_ahci_driver);

MODULE_DESCRIPTION("Broadcom SATA3 AHCI Controller Driver");
MODULE_AUTHOR("Brian Norris");
MODULE_LICENSE("GPL");
MODULE_ALIAS("platform:sata-brcmstb");
