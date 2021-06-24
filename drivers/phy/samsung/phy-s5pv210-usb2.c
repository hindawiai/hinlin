<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Samsung SoC USB 1.1/2.0 PHY driver - S5PV210 support
 *
 * Copyright (C) 2013 Samsung Electronics Co., Ltd.
 * Authors: Kamil Debski <k.debski@samsung.com>
 */

#समावेश <linux/delay.h>
#समावेश <linux/पन.स>
#समावेश <linux/phy/phy.h>
#समावेश "phy-samsung-usb2.h"

/* Exynos USB PHY रेजिस्टरs */

/* PHY घातer control */
#घोषणा S5PV210_UPHYPWR			0x0

#घोषणा S5PV210_UPHYPWR_PHY0_SUSPEND	BIT(0)
#घोषणा S5PV210_UPHYPWR_PHY0_PWR	BIT(3)
#घोषणा S5PV210_UPHYPWR_PHY0_OTG_PWR	BIT(4)
#घोषणा S5PV210_UPHYPWR_PHY0	( \
	S5PV210_UPHYPWR_PHY0_SUSPEND | \
	S5PV210_UPHYPWR_PHY0_PWR | \
	S5PV210_UPHYPWR_PHY0_OTG_PWR)

#घोषणा S5PV210_UPHYPWR_PHY1_SUSPEND	BIT(6)
#घोषणा S5PV210_UPHYPWR_PHY1_PWR	BIT(7)
#घोषणा S5PV210_UPHYPWR_PHY1 ( \
	S5PV210_UPHYPWR_PHY1_SUSPEND | \
	S5PV210_UPHYPWR_PHY1_PWR)

/* PHY घड़ी control */
#घोषणा S5PV210_UPHYCLK			0x4

#घोषणा S5PV210_UPHYCLK_PHYFSEL_MASK	(0x3 << 0)
#घोषणा S5PV210_UPHYCLK_PHYFSEL_48MHZ	(0x0 << 0)
#घोषणा S5PV210_UPHYCLK_PHYFSEL_24MHZ	(0x3 << 0)
#घोषणा S5PV210_UPHYCLK_PHYFSEL_12MHZ	(0x2 << 0)

#घोषणा S5PV210_UPHYCLK_PHY0_ID_PULLUP	BIT(2)
#घोषणा S5PV210_UPHYCLK_PHY0_COMMON_ON	BIT(4)
#घोषणा S5PV210_UPHYCLK_PHY1_COMMON_ON	BIT(7)

/* PHY reset control */
#घोषणा S5PV210_UPHYRST			0x8

#घोषणा S5PV210_URSTCON_PHY0		BIT(0)
#घोषणा S5PV210_URSTCON_OTG_HLINK	BIT(1)
#घोषणा S5PV210_URSTCON_OTG_PHYLINK	BIT(2)
#घोषणा S5PV210_URSTCON_PHY1_ALL	BIT(3)
#घोषणा S5PV210_URSTCON_HOST_LINK_ALL	BIT(4)

/* Isolation, configured in the घातer management unit */
#घोषणा S5PV210_USB_ISOL_OFFSET		0x680c
#घोषणा S5PV210_USB_ISOL_DEVICE		BIT(0)
#घोषणा S5PV210_USB_ISOL_HOST		BIT(1)


क्रमागत s5pv210_phy_id अणु
	S5PV210_DEVICE,
	S5PV210_HOST,
	S5PV210_NUM_PHYS,
पूर्ण;

/*
 * s5pv210_rate_to_clk() converts the supplied घड़ी rate to the value that
 * can be written to the phy रेजिस्टर.
 */
अटल पूर्णांक s5pv210_rate_to_clk(अचिन्हित दीर्घ rate, u32 *reg)
अणु
	चयन (rate) अणु
	हाल 12 * MHZ:
		*reg = S5PV210_UPHYCLK_PHYFSEL_12MHZ;
		अवरोध;
	हाल 24 * MHZ:
		*reg = S5PV210_UPHYCLK_PHYFSEL_24MHZ;
		अवरोध;
	हाल 48 * MHZ:
		*reg = S5PV210_UPHYCLK_PHYFSEL_48MHZ;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम s5pv210_isol(काष्ठा samsung_usb2_phy_instance *inst, bool on)
अणु
	काष्ठा samsung_usb2_phy_driver *drv = inst->drv;
	u32 mask;

	चयन (inst->cfg->id) अणु
	हाल S5PV210_DEVICE:
		mask = S5PV210_USB_ISOL_DEVICE;
		अवरोध;
	हाल S5PV210_HOST:
		mask = S5PV210_USB_ISOL_HOST;
		अवरोध;
	शेष:
		वापस;
	पूर्ण

	regmap_update_bits(drv->reg_pmu, S5PV210_USB_ISOL_OFFSET,
							mask, on ? 0 : mask);
पूर्ण

अटल व्योम s5pv210_phy_pwr(काष्ठा samsung_usb2_phy_instance *inst, bool on)
अणु
	काष्ठा samsung_usb2_phy_driver *drv = inst->drv;
	u32 rstbits = 0;
	u32 phypwr = 0;
	u32 rst;
	u32 pwr;

	चयन (inst->cfg->id) अणु
	हाल S5PV210_DEVICE:
		phypwr =	S5PV210_UPHYPWR_PHY0;
		rstbits =	S5PV210_URSTCON_PHY0;
		अवरोध;
	हाल S5PV210_HOST:
		phypwr =	S5PV210_UPHYPWR_PHY1;
		rstbits =	S5PV210_URSTCON_PHY1_ALL |
				S5PV210_URSTCON_HOST_LINK_ALL;
		अवरोध;
	पूर्ण

	अगर (on) अणु
		ग_लिखोl(drv->ref_reg_val, drv->reg_phy + S5PV210_UPHYCLK);

		pwr = पढ़ोl(drv->reg_phy + S5PV210_UPHYPWR);
		pwr &= ~phypwr;
		ग_लिखोl(pwr, drv->reg_phy + S5PV210_UPHYPWR);

		rst = पढ़ोl(drv->reg_phy + S5PV210_UPHYRST);
		rst |= rstbits;
		ग_लिखोl(rst, drv->reg_phy + S5PV210_UPHYRST);
		udelay(10);
		rst &= ~rstbits;
		ग_लिखोl(rst, drv->reg_phy + S5PV210_UPHYRST);
		/* The following delay is necessary क्रम the reset sequence to be
		 * completed
		 */
		udelay(80);
	पूर्ण अन्यथा अणु
		pwr = पढ़ोl(drv->reg_phy + S5PV210_UPHYPWR);
		pwr |= phypwr;
		ग_लिखोl(pwr, drv->reg_phy + S5PV210_UPHYPWR);
	पूर्ण
पूर्ण

अटल पूर्णांक s5pv210_घातer_on(काष्ठा samsung_usb2_phy_instance *inst)
अणु
	s5pv210_isol(inst, 0);
	s5pv210_phy_pwr(inst, 1);

	वापस 0;
पूर्ण

अटल पूर्णांक s5pv210_घातer_off(काष्ठा samsung_usb2_phy_instance *inst)
अणु
	s5pv210_phy_pwr(inst, 0);
	s5pv210_isol(inst, 1);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा samsung_usb2_common_phy s5pv210_phys[S5PV210_NUM_PHYS] = अणु
	[S5PV210_DEVICE] = अणु
		.label		= "device",
		.id		= S5PV210_DEVICE,
		.घातer_on	= s5pv210_घातer_on,
		.घातer_off	= s5pv210_घातer_off,
	पूर्ण,
	[S5PV210_HOST] = अणु
		.label		= "host",
		.id		= S5PV210_HOST,
		.घातer_on	= s5pv210_घातer_on,
		.घातer_off	= s5pv210_घातer_off,
	पूर्ण,
पूर्ण;

स्थिर काष्ठा samsung_usb2_phy_config s5pv210_usb2_phy_config = अणु
	.num_phys	= ARRAY_SIZE(s5pv210_phys),
	.phys		= s5pv210_phys,
	.rate_to_clk	= s5pv210_rate_to_clk,
पूर्ण;
