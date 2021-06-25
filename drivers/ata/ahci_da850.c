<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * DaVinci DA850 AHCI SATA platक्रमm driver
 */

#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/pm.h>
#समावेश <linux/device.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/libata.h>
#समावेश <linux/ahci_platक्रमm.h>
#समावेश "ahci.h"

#घोषणा DRV_NAME		"ahci_da850"
#घोषणा HARDRESET_RETRIES	5

/* SATA PHY Control Register offset from AHCI base */
#घोषणा SATA_P0PHYCR_REG	0x178

#घोषणा SATA_PHY_MPY(x)		((x) << 0)
#घोषणा SATA_PHY_LOS(x)		((x) << 6)
#घोषणा SATA_PHY_RXCDR(x)	((x) << 10)
#घोषणा SATA_PHY_RXEQ(x)	((x) << 13)
#घोषणा SATA_PHY_TXSWING(x)	((x) << 19)
#घोषणा SATA_PHY_ENPLL(x)	((x) << 31)

अटल व्योम da850_sata_init(काष्ठा device *dev, व्योम __iomem *pwrdn_reg,
			    व्योम __iomem *ahci_base, u32 mpy)
अणु
	अचिन्हित पूर्णांक val;

	/* Enable SATA घड़ी receiver */
	val = पढ़ोl(pwrdn_reg);
	val &= ~BIT(0);
	ग_लिखोl(val, pwrdn_reg);

	val = SATA_PHY_MPY(mpy) | SATA_PHY_LOS(1) | SATA_PHY_RXCDR(4) |
	      SATA_PHY_RXEQ(1) | SATA_PHY_TXSWING(3) | SATA_PHY_ENPLL(1);

	ग_लिखोl(val, ahci_base + SATA_P0PHYCR_REG);
पूर्ण

अटल u32 ahci_da850_calculate_mpy(अचिन्हित दीर्घ refclk_rate)
अणु
	u32 pll_output = 1500000000, needed;

	/*
	 * We need to determine the value of the multiplier (MPY) bits.
	 * In order to include the 12.5 multiplier we need to first भागide
	 * the refclk rate by ten.
	 *
	 * __भाग64_32() turned out to be unreliable, someबार वापसing
	 * false results.
	 */
	WARN((refclk_rate % 10) != 0, "refclk must be divisible by 10");
	needed = pll_output / (refclk_rate / 10);

	/*
	 * What we have now is (multiplier * 10).
	 *
	 * Let's determine the actual रेजिस्टर value we need to ग_लिखो.
	 */

	चयन (needed) अणु
	हाल 50:
		वापस 0x1;
	हाल 60:
		वापस 0x2;
	हाल 80:
		वापस 0x4;
	हाल 100:
		वापस 0x5;
	हाल 120:
		वापस 0x6;
	हाल 125:
		वापस 0x7;
	हाल 150:
		वापस 0x8;
	हाल 200:
		वापस 0x9;
	हाल 250:
		वापस 0xa;
	शेष:
		/*
		 * We should have भागided evenly - अगर not, वापस an invalid
		 * value.
		 */
		वापस 0;
	पूर्ण
पूर्ण

अटल पूर्णांक ahci_da850_softreset(काष्ठा ata_link *link,
				अचिन्हित पूर्णांक *class, अचिन्हित दीर्घ deadline)
अणु
	पूर्णांक pmp, ret;

	pmp = sata_srst_pmp(link);

	/*
	 * There's an issue with the SATA controller on da850 SoCs: अगर we
	 * enable Port Multiplier support, but the drive is connected directly
	 * to the board, it can't be detected. As a workaround: अगर PMP is
	 * enabled, we first call ahci_करो_softreset() and pass it the result of
	 * sata_srst_pmp(). If this call fails, we retry with pmp = 0.
	 */
	ret = ahci_करो_softreset(link, class, pmp, deadline, ahci_check_पढ़ोy);
	अगर (pmp && ret == -EBUSY)
		वापस ahci_करो_softreset(link, class, 0,
					 deadline, ahci_check_पढ़ोy);

	वापस ret;
पूर्ण

अटल पूर्णांक ahci_da850_hardreset(काष्ठा ata_link *link,
				अचिन्हित पूर्णांक *class, अचिन्हित दीर्घ deadline)
अणु
	पूर्णांक ret, retry = HARDRESET_RETRIES;
	bool online;

	/*
	 * In order to correctly service the LCD controller of the da850 SoC,
	 * we increased the PLL0 frequency to 456MHz from the शेष 300MHz.
	 *
	 * This made the SATA controller unstable and the hardreset operation
	 * करोes not always succeed the first समय. Beक्रमe really giving up to
	 * bring up the link, retry the reset a couple बार.
	 */
	करो अणु
		ret = ahci_करो_hardreset(link, class, deadline, &online);
		अगर (online)
			वापस ret;
	पूर्ण जबतक (retry--);

	वापस ret;
पूर्ण

अटल काष्ठा ata_port_operations ahci_da850_port_ops = अणु
	.inherits = &ahci_platक्रमm_ops,
	.softreset = ahci_da850_softreset,
	/*
	 * No need to override .pmp_softreset - it's only used क्रम actual
	 * PMP-enabled ports.
	 */
	.hardreset = ahci_da850_hardreset,
	.pmp_hardreset = ahci_da850_hardreset,
पूर्ण;

अटल स्थिर काष्ठा ata_port_info ahci_da850_port_info = अणु
	.flags		= AHCI_FLAG_COMMON,
	.pio_mask	= ATA_PIO4,
	.udma_mask	= ATA_UDMA6,
	.port_ops	= &ahci_da850_port_ops,
पूर्ण;

अटल काष्ठा scsi_host_ढाँचा ahci_platक्रमm_sht = अणु
	AHCI_SHT(DRV_NAME),
पूर्ण;

अटल पूर्णांक ahci_da850_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device *dev = &pdev->dev;
	काष्ठा ahci_host_priv *hpriv;
	व्योम __iomem *pwrdn_reg;
	काष्ठा resource *res;
	काष्ठा clk *clk;
	u32 mpy;
	पूर्णांक rc;

	hpriv = ahci_platक्रमm_get_resources(pdev, 0);
	अगर (IS_ERR(hpriv))
		वापस PTR_ERR(hpriv);

	/*
	 * Internally ahci_platक्रमm_get_resources() calls clk_get(dev, शून्य)
	 * when trying to obtain the functional घड़ी. This SATA controller
	 * uses two घड़ीs क्रम which we specअगरy two connection ids. If we करोn't
	 * have the functional घड़ी at this poपूर्णांक - call clk_get() again with
	 * con_id = "fck".
	 */
	अगर (!hpriv->clks[0]) अणु
		clk = clk_get(dev, "fck");
		अगर (IS_ERR(clk))
			वापस PTR_ERR(clk);

		hpriv->clks[0] = clk;
	पूर्ण

	/*
	 * The second घड़ी used by ahci-da850 is the बाह्यal REFCLK. If we
	 * didn't get it from ahci_platform_get_resources(), let's try to
	 * specअगरy the con_id in clk_get().
	 */
	अगर (!hpriv->clks[1]) अणु
		clk = clk_get(dev, "refclk");
		अगर (IS_ERR(clk)) अणु
			dev_err(dev, "unable to obtain the reference clock");
			वापस -ENODEV;
		पूर्ण

		hpriv->clks[1] = clk;
	पूर्ण

	mpy = ahci_da850_calculate_mpy(clk_get_rate(hpriv->clks[1]));
	अगर (mpy == 0) अणु
		dev_err(dev, "invalid REFCLK multiplier value: 0x%x", mpy);
		वापस -EINVAL;
	पूर्ण

	rc = ahci_platक्रमm_enable_resources(hpriv);
	अगर (rc)
		वापस rc;

	res = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 1);
	अगर (!res) अणु
		rc = -ENODEV;
		जाओ disable_resources;
	पूर्ण

	pwrdn_reg = devm_ioremap(dev, res->start, resource_size(res));
	अगर (!pwrdn_reg) अणु
		rc = -ENOMEM;
		जाओ disable_resources;
	पूर्ण

	da850_sata_init(dev, pwrdn_reg, hpriv->mmio, mpy);

	rc = ahci_platक्रमm_init_host(pdev, hpriv, &ahci_da850_port_info,
				     &ahci_platक्रमm_sht);
	अगर (rc)
		जाओ disable_resources;

	वापस 0;
disable_resources:
	ahci_platक्रमm_disable_resources(hpriv);
	वापस rc;
पूर्ण

अटल SIMPLE_DEV_PM_OPS(ahci_da850_pm_ops, ahci_platक्रमm_suspend,
			 ahci_platक्रमm_resume);

अटल स्थिर काष्ठा of_device_id ahci_da850_of_match[] = अणु
	अणु .compatible = "ti,da850-ahci", पूर्ण,
	अणु पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, ahci_da850_of_match);

अटल काष्ठा platक्रमm_driver ahci_da850_driver = अणु
	.probe = ahci_da850_probe,
	.हटाओ = ata_platक्रमm_हटाओ_one,
	.driver = अणु
		.name = DRV_NAME,
		.of_match_table = ahci_da850_of_match,
		.pm = &ahci_da850_pm_ops,
	पूर्ण,
पूर्ण;
module_platक्रमm_driver(ahci_da850_driver);

MODULE_DESCRIPTION("DaVinci DA850 AHCI SATA platform driver");
MODULE_AUTHOR("Bartlomiej Zolnierkiewicz <b.zolnierkie@samsung.com>");
MODULE_LICENSE("GPL");
