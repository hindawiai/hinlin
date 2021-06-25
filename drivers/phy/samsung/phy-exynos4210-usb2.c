<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Samsung SoC USB 1.1/2.0 PHY driver - Exynos 4210 support
 *
 * Copyright (C) 2013 Samsung Electronics Co., Ltd.
 * Author: Kamil Debski <k.debski@samsung.com>
 */

#समावेश <linux/delay.h>
#समावेश <linux/पन.स>
#समावेश <linux/phy/phy.h>
#समावेश <linux/regmap.h>
#समावेश "phy-samsung-usb2.h"

/* Exynos USB PHY रेजिस्टरs */

/* PHY घातer control */
#घोषणा EXYNOS_4210_UPHYPWR			0x0

#घोषणा EXYNOS_4210_UPHYPWR_PHY0_SUSPEND	BIT(0)
#घोषणा EXYNOS_4210_UPHYPWR_PHY0_PWR		BIT(3)
#घोषणा EXYNOS_4210_UPHYPWR_PHY0_OTG_PWR	BIT(4)
#घोषणा EXYNOS_4210_UPHYPWR_PHY0_SLEEP		BIT(5)
#घोषणा EXYNOS_4210_UPHYPWR_PHY0	( \
	EXYNOS_4210_UPHYPWR_PHY0_SUSPEND | \
	EXYNOS_4210_UPHYPWR_PHY0_PWR | \
	EXYNOS_4210_UPHYPWR_PHY0_OTG_PWR | \
	EXYNOS_4210_UPHYPWR_PHY0_SLEEP)

#घोषणा EXYNOS_4210_UPHYPWR_PHY1_SUSPEND	BIT(6)
#घोषणा EXYNOS_4210_UPHYPWR_PHY1_PWR		BIT(7)
#घोषणा EXYNOS_4210_UPHYPWR_PHY1_SLEEP		BIT(8)
#घोषणा EXYNOS_4210_UPHYPWR_PHY1 ( \
	EXYNOS_4210_UPHYPWR_PHY1_SUSPEND | \
	EXYNOS_4210_UPHYPWR_PHY1_PWR | \
	EXYNOS_4210_UPHYPWR_PHY1_SLEEP)

#घोषणा EXYNOS_4210_UPHYPWR_HSIC0_SUSPEND	BIT(9)
#घोषणा EXYNOS_4210_UPHYPWR_HSIC0_SLEEP		BIT(10)
#घोषणा EXYNOS_4210_UPHYPWR_HSIC0 ( \
	EXYNOS_4210_UPHYPWR_HSIC0_SUSPEND | \
	EXYNOS_4210_UPHYPWR_HSIC0_SLEEP)

#घोषणा EXYNOS_4210_UPHYPWR_HSIC1_SUSPEND	BIT(11)
#घोषणा EXYNOS_4210_UPHYPWR_HSIC1_SLEEP		BIT(12)
#घोषणा EXYNOS_4210_UPHYPWR_HSIC1 ( \
	EXYNOS_4210_UPHYPWR_HSIC1_SUSPEND | \
	EXYNOS_4210_UPHYPWR_HSIC1_SLEEP)

/* PHY घड़ी control */
#घोषणा EXYNOS_4210_UPHYCLK			0x4

#घोषणा EXYNOS_4210_UPHYCLK_PHYFSEL_MASK	(0x3 << 0)
#घोषणा EXYNOS_4210_UPHYCLK_PHYFSEL_OFFSET	0
#घोषणा EXYNOS_4210_UPHYCLK_PHYFSEL_48MHZ	(0x0 << 0)
#घोषणा EXYNOS_4210_UPHYCLK_PHYFSEL_24MHZ	(0x3 << 0)
#घोषणा EXYNOS_4210_UPHYCLK_PHYFSEL_12MHZ	(0x2 << 0)

#घोषणा EXYNOS_4210_UPHYCLK_PHY0_ID_PULLUP	BIT(2)
#घोषणा EXYNOS_4210_UPHYCLK_PHY0_COMMON_ON	BIT(4)
#घोषणा EXYNOS_4210_UPHYCLK_PHY1_COMMON_ON	BIT(7)

/* PHY reset control */
#घोषणा EXYNOS_4210_UPHYRST			0x8

#घोषणा EXYNOS_4210_URSTCON_PHY0		BIT(0)
#घोषणा EXYNOS_4210_URSTCON_OTG_HLINK		BIT(1)
#घोषणा EXYNOS_4210_URSTCON_OTG_PHYLINK		BIT(2)
#घोषणा EXYNOS_4210_URSTCON_PHY1_ALL		BIT(3)
#घोषणा EXYNOS_4210_URSTCON_PHY1_P0		BIT(4)
#घोषणा EXYNOS_4210_URSTCON_PHY1_P1P2		BIT(5)
#घोषणा EXYNOS_4210_URSTCON_HOST_LINK_ALL	BIT(6)
#घोषणा EXYNOS_4210_URSTCON_HOST_LINK_P0	BIT(7)
#घोषणा EXYNOS_4210_URSTCON_HOST_LINK_P1	BIT(8)
#घोषणा EXYNOS_4210_URSTCON_HOST_LINK_P2	BIT(9)

/* Isolation, configured in the घातer management unit */
#घोषणा EXYNOS_4210_USB_ISOL_DEVICE_OFFSET	0x704
#घोषणा EXYNOS_4210_USB_ISOL_DEVICE		BIT(0)
#घोषणा EXYNOS_4210_USB_ISOL_HOST_OFFSET	0x708
#घोषणा EXYNOS_4210_USB_ISOL_HOST		BIT(0)

/* USBYPHY1 Floating prevention */
#घोषणा EXYNOS_4210_UPHY1CON			0x34
#घोषणा EXYNOS_4210_UPHY1CON_FLOAT_PREVENTION	0x1

/* Mode चयनing SUB Device <-> Host */
#घोषणा EXYNOS_4210_MODE_SWITCH_OFFSET		0x21c
#घोषणा EXYNOS_4210_MODE_SWITCH_MASK		1
#घोषणा EXYNOS_4210_MODE_SWITCH_DEVICE		0
#घोषणा EXYNOS_4210_MODE_SWITCH_HOST		1

क्रमागत exynos4210_phy_id अणु
	EXYNOS4210_DEVICE,
	EXYNOS4210_HOST,
	EXYNOS4210_HSIC0,
	EXYNOS4210_HSIC1,
	EXYNOS4210_NUM_PHYS,
पूर्ण;

/*
 * exynos4210_rate_to_clk() converts the supplied घड़ी rate to the value that
 * can be written to the phy रेजिस्टर.
 */
अटल पूर्णांक exynos4210_rate_to_clk(अचिन्हित दीर्घ rate, u32 *reg)
अणु
	चयन (rate) अणु
	हाल 12 * MHZ:
		*reg = EXYNOS_4210_UPHYCLK_PHYFSEL_12MHZ;
		अवरोध;
	हाल 24 * MHZ:
		*reg = EXYNOS_4210_UPHYCLK_PHYFSEL_24MHZ;
		अवरोध;
	हाल 48 * MHZ:
		*reg = EXYNOS_4210_UPHYCLK_PHYFSEL_48MHZ;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम exynos4210_isol(काष्ठा samsung_usb2_phy_instance *inst, bool on)
अणु
	काष्ठा samsung_usb2_phy_driver *drv = inst->drv;
	u32 offset;
	u32 mask;

	चयन (inst->cfg->id) अणु
	हाल EXYNOS4210_DEVICE:
		offset = EXYNOS_4210_USB_ISOL_DEVICE_OFFSET;
		mask = EXYNOS_4210_USB_ISOL_DEVICE;
		अवरोध;
	हाल EXYNOS4210_HOST:
		offset = EXYNOS_4210_USB_ISOL_HOST_OFFSET;
		mask = EXYNOS_4210_USB_ISOL_HOST;
		अवरोध;
	शेष:
		वापस;
	पूर्ण

	regmap_update_bits(drv->reg_pmu, offset, mask, on ? 0 : mask);
पूर्ण

अटल व्योम exynos4210_phy_pwr(काष्ठा samsung_usb2_phy_instance *inst, bool on)
अणु
	काष्ठा samsung_usb2_phy_driver *drv = inst->drv;
	u32 rstbits = 0;
	u32 phypwr = 0;
	u32 rst;
	u32 pwr;
	u32 clk;

	चयन (inst->cfg->id) अणु
	हाल EXYNOS4210_DEVICE:
		phypwr =	EXYNOS_4210_UPHYPWR_PHY0;
		rstbits =	EXYNOS_4210_URSTCON_PHY0;
		अवरोध;
	हाल EXYNOS4210_HOST:
		phypwr =	EXYNOS_4210_UPHYPWR_PHY1;
		rstbits =	EXYNOS_4210_URSTCON_PHY1_ALL |
				EXYNOS_4210_URSTCON_PHY1_P0 |
				EXYNOS_4210_URSTCON_PHY1_P1P2 |
				EXYNOS_4210_URSTCON_HOST_LINK_ALL |
				EXYNOS_4210_URSTCON_HOST_LINK_P0;
		ग_लिखोl(on, drv->reg_phy + EXYNOS_4210_UPHY1CON);
		अवरोध;
	हाल EXYNOS4210_HSIC0:
		phypwr =	EXYNOS_4210_UPHYPWR_HSIC0;
		rstbits =	EXYNOS_4210_URSTCON_PHY1_P1P2 |
				EXYNOS_4210_URSTCON_HOST_LINK_P1;
		अवरोध;
	हाल EXYNOS4210_HSIC1:
		phypwr =	EXYNOS_4210_UPHYPWR_HSIC1;
		rstbits =	EXYNOS_4210_URSTCON_PHY1_P1P2 |
				EXYNOS_4210_URSTCON_HOST_LINK_P2;
		अवरोध;
	पूर्ण

	अगर (on) अणु
		clk = पढ़ोl(drv->reg_phy + EXYNOS_4210_UPHYCLK);
		clk &= ~EXYNOS_4210_UPHYCLK_PHYFSEL_MASK;
		clk |= drv->ref_reg_val << EXYNOS_4210_UPHYCLK_PHYFSEL_OFFSET;
		ग_लिखोl(clk, drv->reg_phy + EXYNOS_4210_UPHYCLK);

		pwr = पढ़ोl(drv->reg_phy + EXYNOS_4210_UPHYPWR);
		pwr &= ~phypwr;
		ग_लिखोl(pwr, drv->reg_phy + EXYNOS_4210_UPHYPWR);

		rst = पढ़ोl(drv->reg_phy + EXYNOS_4210_UPHYRST);
		rst |= rstbits;
		ग_लिखोl(rst, drv->reg_phy + EXYNOS_4210_UPHYRST);
		udelay(10);
		rst &= ~rstbits;
		ग_लिखोl(rst, drv->reg_phy + EXYNOS_4210_UPHYRST);
		/* The following delay is necessary क्रम the reset sequence to be
		 * completed */
		udelay(80);
	पूर्ण अन्यथा अणु
		pwr = पढ़ोl(drv->reg_phy + EXYNOS_4210_UPHYPWR);
		pwr |= phypwr;
		ग_लिखोl(pwr, drv->reg_phy + EXYNOS_4210_UPHYPWR);
	पूर्ण
पूर्ण

अटल पूर्णांक exynos4210_घातer_on(काष्ठा samsung_usb2_phy_instance *inst)
अणु
	/* Order of initialisation is important - first घातer then isolation */
	exynos4210_phy_pwr(inst, 1);
	exynos4210_isol(inst, 0);

	वापस 0;
पूर्ण

अटल पूर्णांक exynos4210_घातer_off(काष्ठा samsung_usb2_phy_instance *inst)
अणु
	exynos4210_isol(inst, 1);
	exynos4210_phy_pwr(inst, 0);

	वापस 0;
पूर्ण


अटल स्थिर काष्ठा samsung_usb2_common_phy exynos4210_phys[] = अणु
	अणु
		.label		= "device",
		.id		= EXYNOS4210_DEVICE,
		.घातer_on	= exynos4210_घातer_on,
		.घातer_off	= exynos4210_घातer_off,
	पूर्ण,
	अणु
		.label		= "host",
		.id		= EXYNOS4210_HOST,
		.घातer_on	= exynos4210_घातer_on,
		.घातer_off	= exynos4210_घातer_off,
	पूर्ण,
	अणु
		.label		= "hsic0",
		.id		= EXYNOS4210_HSIC0,
		.घातer_on	= exynos4210_घातer_on,
		.घातer_off	= exynos4210_घातer_off,
	पूर्ण,
	अणु
		.label		= "hsic1",
		.id		= EXYNOS4210_HSIC1,
		.घातer_on	= exynos4210_घातer_on,
		.घातer_off	= exynos4210_घातer_off,
	पूर्ण,
पूर्ण;

स्थिर काष्ठा samsung_usb2_phy_config exynos4210_usb2_phy_config = अणु
	.has_mode_चयन	= 0,
	.num_phys		= EXYNOS4210_NUM_PHYS,
	.phys			= exynos4210_phys,
	.rate_to_clk		= exynos4210_rate_to_clk,
पूर्ण;
