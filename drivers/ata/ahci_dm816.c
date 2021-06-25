<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * DaVinci DM816 AHCI SATA platक्रमm driver
 *
 * Copyright (C) 2017 BayLibre SAS
 */

#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/device.h>
#समावेश <linux/pm.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/libata.h>
#समावेश <linux/ahci_platक्रमm.h>

#समावेश "ahci.h"

#घोषणा AHCI_DM816_DRV_NAME		"ahci-dm816"

#घोषणा AHCI_DM816_PHY_ENPLL(x)		((x) << 0)
#घोषणा AHCI_DM816_PHY_MPY(x)		((x) << 1)
#घोषणा AHCI_DM816_PHY_LOS(x)		((x) << 12)
#घोषणा AHCI_DM816_PHY_RXCDR(x)		((x) << 13)
#घोषणा AHCI_DM816_PHY_RXEQ(x)		((x) << 16)
#घोषणा AHCI_DM816_PHY_TXSWING(x)	((x) << 23)

#घोषणा AHCI_DM816_P0PHYCR_REG		0x178
#घोषणा AHCI_DM816_P1PHYCR_REG		0x1f8

#घोषणा AHCI_DM816_PLL_OUT		1500000000LU

अटल स्थिर अचिन्हित दीर्घ pll_mpy_table[] = अणु
	  400,  500,  600,  800,  825, 1000, 1200,
	 1250, 1500, 1600, 1650, 2000, 2200, 2500
पूर्ण;

अटल पूर्णांक ahci_dm816_get_mpy_bits(अचिन्हित दीर्घ refclk_rate)
अणु
	अचिन्हित दीर्घ pll_multiplier;
	पूर्णांक i;

	/*
	 * We need to determine the value of the multiplier (MPY) bits.
	 * In order to include the 8.25 multiplier we need to first भागide
	 * the refclk rate by 100.
	 */
	pll_multiplier = AHCI_DM816_PLL_OUT / (refclk_rate / 100);

	क्रम (i = 0; i < ARRAY_SIZE(pll_mpy_table); i++) अणु
		अगर (pll_mpy_table[i] == pll_multiplier)
			वापस i;
	पूर्ण

	/*
	 * We should have भागided evenly - अगर not, वापस an invalid
	 * value.
	 */
	वापस -1;
पूर्ण

अटल पूर्णांक ahci_dm816_phy_init(काष्ठा ahci_host_priv *hpriv, काष्ठा device *dev)
अणु
	अचिन्हित दीर्घ refclk_rate;
	पूर्णांक mpy;
	u32 val;

	/*
	 * We should have been supplied two घड़ीs: the functional and
	 * keep-alive घड़ी and the बाह्यal reference घड़ी. We need the
	 * rate of the latter to calculate the correct value of MPY bits.
	 */
	अगर (!hpriv->clks[1]) अणु
		dev_err(dev, "reference clock not supplied\n");
		वापस -EINVAL;
	पूर्ण

	refclk_rate = clk_get_rate(hpriv->clks[1]);
	अगर ((refclk_rate % 100) != 0) अणु
		dev_err(dev, "reference clock rate must be divisible by 100\n");
		वापस -EINVAL;
	पूर्ण

	mpy = ahci_dm816_get_mpy_bits(refclk_rate);
	अगर (mpy < 0) अणु
		dev_err(dev, "can't calculate the MPY bits value\n");
		वापस -EINVAL;
	पूर्ण

	/* Enable the PHY and configure the first HBA port. */
	val = AHCI_DM816_PHY_MPY(mpy) | AHCI_DM816_PHY_LOS(1) |
	      AHCI_DM816_PHY_RXCDR(4) | AHCI_DM816_PHY_RXEQ(1) |
	      AHCI_DM816_PHY_TXSWING(3) | AHCI_DM816_PHY_ENPLL(1);
	ग_लिखोl(val, hpriv->mmio + AHCI_DM816_P0PHYCR_REG);

	/* Configure the second HBA port. */
	val = AHCI_DM816_PHY_LOS(1) | AHCI_DM816_PHY_RXCDR(4) |
	      AHCI_DM816_PHY_RXEQ(1) | AHCI_DM816_PHY_TXSWING(3);
	ग_लिखोl(val, hpriv->mmio + AHCI_DM816_P1PHYCR_REG);

	वापस 0;
पूर्ण

अटल पूर्णांक ahci_dm816_softreset(काष्ठा ata_link *link,
				अचिन्हित पूर्णांक *class, अचिन्हित दीर्घ deadline)
अणु
	पूर्णांक pmp, ret;

	pmp = sata_srst_pmp(link);

	/*
	 * There's an issue with the SATA controller on DM816 SoC: अगर we
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

अटल काष्ठा ata_port_operations ahci_dm816_port_ops = अणु
	.inherits = &ahci_platक्रमm_ops,
	.softreset = ahci_dm816_softreset,
पूर्ण;

अटल स्थिर काष्ठा ata_port_info ahci_dm816_port_info = अणु
	.flags		= AHCI_FLAG_COMMON,
	.pio_mask	= ATA_PIO4,
	.udma_mask	= ATA_UDMA6,
	.port_ops	= &ahci_dm816_port_ops,
पूर्ण;

अटल काष्ठा scsi_host_ढाँचा ahci_dm816_platक्रमm_sht = अणु
	AHCI_SHT(AHCI_DM816_DRV_NAME),
पूर्ण;

अटल पूर्णांक ahci_dm816_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device *dev = &pdev->dev;
	काष्ठा ahci_host_priv *hpriv;
	पूर्णांक rc;

	hpriv = ahci_platक्रमm_get_resources(pdev, 0);
	अगर (IS_ERR(hpriv))
		वापस PTR_ERR(hpriv);

	rc = ahci_platक्रमm_enable_resources(hpriv);
	अगर (rc)
		वापस rc;

	rc = ahci_dm816_phy_init(hpriv, dev);
	अगर (rc)
		जाओ disable_resources;

	rc = ahci_platक्रमm_init_host(pdev, hpriv,
				     &ahci_dm816_port_info,
				     &ahci_dm816_platक्रमm_sht);
	अगर (rc)
		जाओ disable_resources;

	वापस 0;

disable_resources:
	ahci_platक्रमm_disable_resources(hpriv);

	वापस rc;
पूर्ण

अटल SIMPLE_DEV_PM_OPS(ahci_dm816_pm_ops,
			 ahci_platक्रमm_suspend,
			 ahci_platक्रमm_resume);

अटल स्थिर काष्ठा of_device_id ahci_dm816_of_match[] = अणु
	अणु .compatible = "ti,dm816-ahci", पूर्ण,
	अणु पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, ahci_dm816_of_match);

अटल काष्ठा platक्रमm_driver ahci_dm816_driver = अणु
	.probe = ahci_dm816_probe,
	.हटाओ = ata_platक्रमm_हटाओ_one,
	.driver = अणु
		.name = AHCI_DM816_DRV_NAME,
		.of_match_table = ahci_dm816_of_match,
		.pm = &ahci_dm816_pm_ops,
	पूर्ण,
पूर्ण;
module_platक्रमm_driver(ahci_dm816_driver);

MODULE_DESCRIPTION("DaVinci DM816 AHCI SATA platform driver");
MODULE_AUTHOR("Bartosz Golaszewski <bgolaszewski@baylibre.com>");
MODULE_LICENSE("GPL");
