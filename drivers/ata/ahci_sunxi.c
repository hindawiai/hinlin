<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Allwinner sunxi AHCI SATA platक्रमm driver
 * Copyright 2013 Olliver Schinagl <oliver@schinagl.nl>
 * Copyright 2014 Hans de Goede <hdegoede@redhat.com>
 *
 * based on the AHCI SATA platक्रमm driver by Jeff Garzik and Anton Vorontsov
 * Based on code from Allwinner Technology Co., Ltd. <www.allwinnertech.com>,
 * Daniel Wang <danielwang@allwinnertech.com>
 */

#समावेश <linux/ahci_platक्रमm.h>
#समावेश <linux/clk.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/of_device.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/regulator/consumer.h>
#समावेश "ahci.h"

#घोषणा DRV_NAME "ahci-sunxi"

/* Insmod parameters */
अटल bool enable_pmp;
module_param(enable_pmp, bool, 0);
MODULE_PARM_DESC(enable_pmp,
	"Enable support for sata port multipliers, only use if you use a pmp!");

#घोषणा AHCI_BISTAFR	0x00a0
#घोषणा AHCI_BISTCR	0x00a4
#घोषणा AHCI_BISTFCTR	0x00a8
#घोषणा AHCI_BISTSR	0x00ac
#घोषणा AHCI_BISTDECR	0x00b0
#घोषणा AHCI_DIAGNR0	0x00b4
#घोषणा AHCI_DIAGNR1	0x00b8
#घोषणा AHCI_OOBR	0x00bc
#घोषणा AHCI_PHYCS0R	0x00c0
#घोषणा AHCI_PHYCS1R	0x00c4
#घोषणा AHCI_PHYCS2R	0x00c8
#घोषणा AHCI_TIMER1MS	0x00e0
#घोषणा AHCI_GPARAM1R	0x00e8
#घोषणा AHCI_GPARAM2R	0x00ec
#घोषणा AHCI_PPARAMR	0x00f0
#घोषणा AHCI_TESTR	0x00f4
#घोषणा AHCI_VERSIONR	0x00f8
#घोषणा AHCI_IDR	0x00fc
#घोषणा AHCI_RWCR	0x00fc
#घोषणा AHCI_P0DMACR	0x0170
#घोषणा AHCI_P0PHYCR	0x0178
#घोषणा AHCI_P0PHYSR	0x017c

अटल व्योम sunxi_clrbits(व्योम __iomem *reg, u32 clr_val)
अणु
	u32 reg_val;

	reg_val = पढ़ोl(reg);
	reg_val &= ~(clr_val);
	ग_लिखोl(reg_val, reg);
पूर्ण

अटल व्योम sunxi_setbits(व्योम __iomem *reg, u32 set_val)
अणु
	u32 reg_val;

	reg_val = पढ़ोl(reg);
	reg_val |= set_val;
	ग_लिखोl(reg_val, reg);
पूर्ण

अटल व्योम sunxi_clrsetbits(व्योम __iomem *reg, u32 clr_val, u32 set_val)
अणु
	u32 reg_val;

	reg_val = पढ़ोl(reg);
	reg_val &= ~(clr_val);
	reg_val |= set_val;
	ग_लिखोl(reg_val, reg);
पूर्ण

अटल u32 sunxi_getbits(व्योम __iomem *reg, u8 mask, u8 shअगरt)
अणु
	वापस (पढ़ोl(reg) >> shअगरt) & mask;
पूर्ण

अटल पूर्णांक ahci_sunxi_phy_init(काष्ठा device *dev, व्योम __iomem *reg_base)
अणु
	u32 reg_val;
	पूर्णांक समयout;

	/* This magic is from the original code */
	ग_लिखोl(0, reg_base + AHCI_RWCR);
	msleep(5);

	sunxi_setbits(reg_base + AHCI_PHYCS1R, BIT(19));
	sunxi_clrsetbits(reg_base + AHCI_PHYCS0R,
			 (0x7 << 24),
			 (0x5 << 24) | BIT(23) | BIT(18));
	sunxi_clrsetbits(reg_base + AHCI_PHYCS1R,
			 (0x3 << 16) | (0x1f << 8) | (0x3 << 6),
			 (0x2 << 16) | (0x6 << 8) | (0x2 << 6));
	sunxi_setbits(reg_base + AHCI_PHYCS1R, BIT(28) | BIT(15));
	sunxi_clrbits(reg_base + AHCI_PHYCS1R, BIT(19));
	sunxi_clrsetbits(reg_base + AHCI_PHYCS0R,
			 (0x7 << 20), (0x3 << 20));
	sunxi_clrsetbits(reg_base + AHCI_PHYCS2R,
			 (0x1f << 5), (0x19 << 5));
	msleep(5);

	sunxi_setbits(reg_base + AHCI_PHYCS0R, (0x1 << 19));

	समयout = 250; /* Power up takes aprox 50 us */
	करो अणु
		reg_val = sunxi_getbits(reg_base + AHCI_PHYCS0R, 0x7, 28);
		अगर (reg_val == 0x02)
			अवरोध;

		अगर (--समयout == 0) अणु
			dev_err(dev, "PHY power up failed.\n");
			वापस -EIO;
		पूर्ण
		udelay(1);
	पूर्ण जबतक (1);

	sunxi_setbits(reg_base + AHCI_PHYCS2R, (0x1 << 24));

	समयout = 100; /* Calibration takes aprox 10 us */
	करो अणु
		reg_val = sunxi_getbits(reg_base + AHCI_PHYCS2R, 0x1, 24);
		अगर (reg_val == 0x00)
			अवरोध;

		अगर (--समयout == 0) अणु
			dev_err(dev, "PHY calibration failed.\n");
			वापस -EIO;
		पूर्ण
		udelay(1);
	पूर्ण जबतक (1);

	msleep(15);

	ग_लिखोl(0x7, reg_base + AHCI_RWCR);

	वापस 0;
पूर्ण

अटल व्योम ahci_sunxi_start_engine(काष्ठा ata_port *ap)
अणु
	व्योम __iomem *port_mmio = ahci_port_base(ap);
	काष्ठा ahci_host_priv *hpriv = ap->host->निजी_data;

	/* Setup DMA beक्रमe DMA start
	 *
	 * NOTE: A similar SoC with SATA/AHCI by Texas Instruments करोcuments
	 *   this Venकरोr Specअगरic Port (P0DMACR, aka PxDMACR) in its
	 *   User's Guide करोcument (TMS320C674x/OMAP-L1x Processor
	 *   Serial ATA (SATA) Controller, Literature Number: SPRUGJ8C,
	 *   March 2011, Chapter 4.33 Port DMA Control Register (P0DMACR),
	 *   p.68, https://www.ti.com/lit/ug/sprugj8c/sprugj8c.pdf)
	 *   as equivalent to the following काष्ठा:
	 *
	 *   काष्ठा AHCI_P0DMACR_t
	 *   अणु
	 *     अचिन्हित TXTS     : 4;
	 *     अचिन्हित RXTS     : 4;
	 *     अचिन्हित TXABL    : 4;
	 *     अचिन्हित RXABL    : 4;
	 *     अचिन्हित Reserved : 16;
	 *   पूर्ण;
	 *
	 *   TXTS: Transmit Transaction Size (TX_TRANSACTION_SIZE).
	 *     This field defines the DMA transaction size in DWORDs क्रम
	 *     transmit (प्रणाली bus पढ़ो, device ग_लिखो) operation. [...]
	 *
	 *   RXTS: Receive Transaction Size (RX_TRANSACTION_SIZE).
	 *     This field defines the Port DMA transaction size in DWORDs
	 *     क्रम receive (प्रणाली bus ग_लिखो, device पढ़ो) operation. [...]
	 *
	 *   TXABL: Transmit Burst Limit.
	 *     This field allows software to limit the VBUSP master पढ़ो
	 *     burst size. [...]
	 *
	 *   RXABL: Receive Burst Limit.
	 *     Allows software to limit the VBUSP master ग_लिखो burst
	 *     size. [...]
	 *
	 *   Reserved: Reserved.
	 *
	 *
	 * NOTE: According to the above करोcument, the following alternative
	 *   to the code below could perhaps be a better option
	 *   (or preparation) क्रम possible further improvements later:
	 *     sunxi_clrsetbits(hpriv->mmio + AHCI_P0DMACR, 0x0000ffff,
	 *		0x00000033);
	 */
	sunxi_clrsetbits(hpriv->mmio + AHCI_P0DMACR, 0x0000ffff, 0x00004433);

	/* Start DMA */
	sunxi_setbits(port_mmio + PORT_CMD, PORT_CMD_START);
पूर्ण

अटल स्थिर काष्ठा ata_port_info ahci_sunxi_port_info = अणु
	.flags		= AHCI_FLAG_COMMON | ATA_FLAG_NCQ,
	.pio_mask	= ATA_PIO4,
	.udma_mask	= ATA_UDMA6,
	.port_ops	= &ahci_platक्रमm_ops,
पूर्ण;

अटल काष्ठा scsi_host_ढाँचा ahci_platक्रमm_sht = अणु
	AHCI_SHT(DRV_NAME),
पूर्ण;

अटल पूर्णांक ahci_sunxi_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device *dev = &pdev->dev;
	काष्ठा ahci_host_priv *hpriv;
	पूर्णांक rc;

	hpriv = ahci_platक्रमm_get_resources(pdev, AHCI_PLATFORM_GET_RESETS);
	अगर (IS_ERR(hpriv))
		वापस PTR_ERR(hpriv);

	hpriv->start_engine = ahci_sunxi_start_engine;

	rc = ahci_platक्रमm_enable_resources(hpriv);
	अगर (rc)
		वापस rc;

	rc = ahci_sunxi_phy_init(dev, hpriv->mmio);
	अगर (rc)
		जाओ disable_resources;

	hpriv->flags = AHCI_HFLAG_32BIT_ONLY | AHCI_HFLAG_NO_MSI |
		       AHCI_HFLAG_YES_NCQ;

	/*
	 * The sunxi sata controller seems to be unable to successfully करो a
	 * soft reset अगर no pmp is attached, so disable pmp use unless
	 * requested, otherwise directly attached disks करो not work.
	 */
	अगर (!enable_pmp)
		hpriv->flags |= AHCI_HFLAG_NO_PMP;

	rc = ahci_platक्रमm_init_host(pdev, hpriv, &ahci_sunxi_port_info,
				     &ahci_platक्रमm_sht);
	अगर (rc)
		जाओ disable_resources;

	वापस 0;

disable_resources:
	ahci_platक्रमm_disable_resources(hpriv);
	वापस rc;
पूर्ण

#अगर_घोषित CONFIG_PM_SLEEP
अटल पूर्णांक ahci_sunxi_resume(काष्ठा device *dev)
अणु
	काष्ठा ata_host *host = dev_get_drvdata(dev);
	काष्ठा ahci_host_priv *hpriv = host->निजी_data;
	पूर्णांक rc;

	rc = ahci_platक्रमm_enable_resources(hpriv);
	अगर (rc)
		वापस rc;

	rc = ahci_sunxi_phy_init(dev, hpriv->mmio);
	अगर (rc)
		जाओ disable_resources;

	rc = ahci_platक्रमm_resume_host(dev);
	अगर (rc)
		जाओ disable_resources;

	वापस 0;

disable_resources:
	ahci_platक्रमm_disable_resources(hpriv);
	वापस rc;
पूर्ण
#पूर्ण_अगर

अटल SIMPLE_DEV_PM_OPS(ahci_sunxi_pm_ops, ahci_platक्रमm_suspend,
			 ahci_sunxi_resume);

अटल स्थिर काष्ठा of_device_id ahci_sunxi_of_match[] = अणु
	अणु .compatible = "allwinner,sun4i-a10-ahci", पूर्ण,
	अणु .compatible = "allwinner,sun8i-r40-ahci", पूर्ण,
	अणु पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, ahci_sunxi_of_match);

अटल काष्ठा platक्रमm_driver ahci_sunxi_driver = अणु
	.probe = ahci_sunxi_probe,
	.हटाओ = ata_platक्रमm_हटाओ_one,
	.driver = अणु
		.name = DRV_NAME,
		.of_match_table = ahci_sunxi_of_match,
		.pm = &ahci_sunxi_pm_ops,
	पूर्ण,
पूर्ण;
module_platक्रमm_driver(ahci_sunxi_driver);

MODULE_DESCRIPTION("Allwinner sunxi AHCI SATA driver");
MODULE_AUTHOR("Olliver Schinagl <oliver@schinagl.nl>");
MODULE_LICENSE("GPL");
