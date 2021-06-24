<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/* Copyright Altera Corporation (C) 2016. All rights reserved.
 *
 * Author: Tien Hock Loh <thloh@altera.com>
 */

#समावेश <linux/mfd/syscon.h>
#समावेश <linux/of.h>
#समावेश <linux/of_address.h>
#समावेश <linux/of_net.h>
#समावेश <linux/phy.h>
#समावेश <linux/regmap.h>
#समावेश <linux/reset.h>
#समावेश <linux/sपंचांगmac.h>

#समावेश "stmmac.h"
#समावेश "stmmac_platform.h"
#समावेश "altr_tse_pcs.h"

#घोषणा SYSMGR_EMACGRP_CTRL_PHYSEL_ENUM_GMII_MII	0
#घोषणा SYSMGR_EMACGRP_CTRL_PHYSEL_ENUM_RGMII		BIT(1)
#घोषणा SYSMGR_EMACGRP_CTRL_PHYSEL_ENUM_RMII		BIT(2)
#घोषणा SYSMGR_EMACGRP_CTRL_PHYSEL_WIDTH		2
#घोषणा SYSMGR_EMACGRP_CTRL_PHYSEL_MASK			GENMASK(1, 0)

#घोषणा TSE_PCS_CONTROL_AN_EN_MASK			BIT(12)
#घोषणा TSE_PCS_CONTROL_REG				0x00
#घोषणा TSE_PCS_CONTROL_RESTART_AN_MASK			BIT(9)
#घोषणा TSE_PCS_CTRL_AUTONEG_SGMII			0x1140
#घोषणा TSE_PCS_IF_MODE_REG				0x28
#घोषणा TSE_PCS_LINK_TIMER_0_REG			0x24
#घोषणा TSE_PCS_LINK_TIMER_1_REG			0x26
#घोषणा TSE_PCS_SIZE					0x40
#घोषणा TSE_PCS_STATUS_AN_COMPLETED_MASK		BIT(5)
#घोषणा TSE_PCS_STATUS_LINK_MASK			0x0004
#घोषणा TSE_PCS_STATUS_REG				0x02
#घोषणा TSE_PCS_SGMII_SPEED_1000			BIT(3)
#घोषणा TSE_PCS_SGMII_SPEED_100				BIT(2)
#घोषणा TSE_PCS_SGMII_SPEED_10				0x0
#घोषणा TSE_PCS_SW_RST_MASK				0x8000
#घोषणा TSE_PCS_PARTNER_ABILITY_REG			0x0A
#घोषणा TSE_PCS_PARTNER_DUPLEX_FULL			0x1000
#घोषणा TSE_PCS_PARTNER_DUPLEX_HALF			0x0000
#घोषणा TSE_PCS_PARTNER_DUPLEX_MASK			0x1000
#घोषणा TSE_PCS_PARTNER_SPEED_MASK			GENMASK(11, 10)
#घोषणा TSE_PCS_PARTNER_SPEED_1000			BIT(11)
#घोषणा TSE_PCS_PARTNER_SPEED_100			BIT(10)
#घोषणा TSE_PCS_PARTNER_SPEED_10			0x0000
#घोषणा TSE_PCS_PARTNER_SPEED_1000			BIT(11)
#घोषणा TSE_PCS_PARTNER_SPEED_100			BIT(10)
#घोषणा TSE_PCS_PARTNER_SPEED_10			0x0000
#घोषणा TSE_PCS_SGMII_SPEED_MASK			GENMASK(3, 2)
#घोषणा TSE_PCS_SGMII_LINK_TIMER_0			0x0D40
#घोषणा TSE_PCS_SGMII_LINK_TIMER_1			0x0003
#घोषणा TSE_PCS_SW_RESET_TIMEOUT			100
#घोषणा TSE_PCS_USE_SGMII_AN_MASK			BIT(1)
#घोषणा TSE_PCS_USE_SGMII_ENA				BIT(0)
#घोषणा TSE_PCS_IF_USE_SGMII				0x03

#घोषणा SGMII_ADAPTER_CTRL_REG				0x00
#घोषणा SGMII_ADAPTER_DISABLE				0x0001
#घोषणा SGMII_ADAPTER_ENABLE				0x0000

#घोषणा AUTONEGO_LINK_TIMER				20

अटल पूर्णांक tse_pcs_reset(व्योम __iomem *base, काष्ठा tse_pcs *pcs)
अणु
	पूर्णांक counter = 0;
	u16 val;

	val = पढ़ोw(base + TSE_PCS_CONTROL_REG);
	val |= TSE_PCS_SW_RST_MASK;
	ग_लिखोw(val, base + TSE_PCS_CONTROL_REG);

	जबतक (counter < TSE_PCS_SW_RESET_TIMEOUT) अणु
		val = पढ़ोw(base + TSE_PCS_CONTROL_REG);
		val &= TSE_PCS_SW_RST_MASK;
		अगर (val == 0)
			अवरोध;
		counter++;
		udelay(1);
	पूर्ण
	अगर (counter >= TSE_PCS_SW_RESET_TIMEOUT) अणु
		dev_err(pcs->dev, "PCS could not get out of sw reset\n");
		वापस -ETIMEDOUT;
	पूर्ण

	वापस 0;
पूर्ण

पूर्णांक tse_pcs_init(व्योम __iomem *base, काष्ठा tse_pcs *pcs)
अणु
	पूर्णांक ret = 0;

	ग_लिखोw(TSE_PCS_IF_USE_SGMII, base + TSE_PCS_IF_MODE_REG);

	ग_लिखोw(TSE_PCS_CTRL_AUTONEG_SGMII, base + TSE_PCS_CONTROL_REG);

	ग_लिखोw(TSE_PCS_SGMII_LINK_TIMER_0, base + TSE_PCS_LINK_TIMER_0_REG);
	ग_लिखोw(TSE_PCS_SGMII_LINK_TIMER_1, base + TSE_PCS_LINK_TIMER_1_REG);

	ret = tse_pcs_reset(base, pcs);
	अगर (ret == 0)
		ग_लिखोw(SGMII_ADAPTER_ENABLE,
		       pcs->sgmii_adapter_base + SGMII_ADAPTER_CTRL_REG);

	वापस ret;
पूर्ण

अटल व्योम pcs_link_समयr_callback(काष्ठा tse_pcs *pcs)
अणु
	u16 val = 0;
	व्योम __iomem *tse_pcs_base = pcs->tse_pcs_base;
	व्योम __iomem *sgmii_adapter_base = pcs->sgmii_adapter_base;

	val = पढ़ोw(tse_pcs_base + TSE_PCS_STATUS_REG);
	val &= TSE_PCS_STATUS_LINK_MASK;

	अगर (val != 0) अणु
		dev_dbg(pcs->dev, "Adapter: Link is established\n");
		ग_लिखोw(SGMII_ADAPTER_ENABLE,
		       sgmii_adapter_base + SGMII_ADAPTER_CTRL_REG);
	पूर्ण अन्यथा अणु
		mod_समयr(&pcs->aneg_link_समयr, jअगरfies +
			  msecs_to_jअगरfies(AUTONEGO_LINK_TIMER));
	पूर्ण
पूर्ण

अटल व्योम स्वतः_nego_समयr_callback(काष्ठा tse_pcs *pcs)
अणु
	u16 val = 0;
	u16 speed = 0;
	u16 duplex = 0;
	व्योम __iomem *tse_pcs_base = pcs->tse_pcs_base;
	व्योम __iomem *sgmii_adapter_base = pcs->sgmii_adapter_base;

	val = पढ़ोw(tse_pcs_base + TSE_PCS_STATUS_REG);
	val &= TSE_PCS_STATUS_AN_COMPLETED_MASK;

	अगर (val != 0) अणु
		dev_dbg(pcs->dev, "Adapter: Auto Negotiation is completed\n");
		val = पढ़ोw(tse_pcs_base + TSE_PCS_PARTNER_ABILITY_REG);
		speed = val & TSE_PCS_PARTNER_SPEED_MASK;
		duplex = val & TSE_PCS_PARTNER_DUPLEX_MASK;

		अगर (speed == TSE_PCS_PARTNER_SPEED_10 &&
		    duplex == TSE_PCS_PARTNER_DUPLEX_FULL)
			dev_dbg(pcs->dev,
				"Adapter: Link Partner is Up - 10/Full\n");
		अन्यथा अगर (speed == TSE_PCS_PARTNER_SPEED_100 &&
			 duplex == TSE_PCS_PARTNER_DUPLEX_FULL)
			dev_dbg(pcs->dev,
				"Adapter: Link Partner is Up - 100/Full\n");
		अन्यथा अगर (speed == TSE_PCS_PARTNER_SPEED_1000 &&
			 duplex == TSE_PCS_PARTNER_DUPLEX_FULL)
			dev_dbg(pcs->dev,
				"Adapter: Link Partner is Up - 1000/Full\n");
		अन्यथा अगर (speed == TSE_PCS_PARTNER_SPEED_10 &&
			 duplex == TSE_PCS_PARTNER_DUPLEX_HALF)
			dev_err(pcs->dev,
				"Adapter does not support Half Duplex\n");
		अन्यथा अगर (speed == TSE_PCS_PARTNER_SPEED_100 &&
			 duplex == TSE_PCS_PARTNER_DUPLEX_HALF)
			dev_err(pcs->dev,
				"Adapter does not support Half Duplex\n");
		अन्यथा अगर (speed == TSE_PCS_PARTNER_SPEED_1000 &&
			 duplex == TSE_PCS_PARTNER_DUPLEX_HALF)
			dev_err(pcs->dev,
				"Adapter does not support Half Duplex\n");
		अन्यथा
			dev_err(pcs->dev,
				"Adapter: Invalid Partner Speed and Duplex\n");

		अगर (duplex == TSE_PCS_PARTNER_DUPLEX_FULL &&
		    (speed == TSE_PCS_PARTNER_SPEED_10 ||
		     speed == TSE_PCS_PARTNER_SPEED_100 ||
		     speed == TSE_PCS_PARTNER_SPEED_1000))
			ग_लिखोw(SGMII_ADAPTER_ENABLE,
			       sgmii_adapter_base + SGMII_ADAPTER_CTRL_REG);
	पूर्ण अन्यथा अणु
		val = पढ़ोw(tse_pcs_base + TSE_PCS_CONTROL_REG);
		val |= TSE_PCS_CONTROL_RESTART_AN_MASK;
		ग_लिखोw(val, tse_pcs_base + TSE_PCS_CONTROL_REG);

		tse_pcs_reset(tse_pcs_base, pcs);
		mod_समयr(&pcs->aneg_link_समयr, jअगरfies +
			  msecs_to_jअगरfies(AUTONEGO_LINK_TIMER));
	पूर्ण
पूर्ण

अटल व्योम aneg_link_समयr_callback(काष्ठा समयr_list *t)
अणु
	काष्ठा tse_pcs *pcs = from_समयr(pcs, t, aneg_link_समयr);

	अगर (pcs->स्वतःneg == AUTONEG_ENABLE)
		स्वतः_nego_समयr_callback(pcs);
	अन्यथा अगर (pcs->स्वतःneg == AUTONEG_DISABLE)
		pcs_link_समयr_callback(pcs);
पूर्ण

व्योम tse_pcs_fix_mac_speed(काष्ठा tse_pcs *pcs, काष्ठा phy_device *phy_dev,
			   अचिन्हित पूर्णांक speed)
अणु
	व्योम __iomem *tse_pcs_base = pcs->tse_pcs_base;
	व्योम __iomem *sgmii_adapter_base = pcs->sgmii_adapter_base;
	u32 val;

	ग_लिखोw(SGMII_ADAPTER_ENABLE,
	       sgmii_adapter_base + SGMII_ADAPTER_CTRL_REG);

	pcs->स्वतःneg = phy_dev->स्वतःneg;

	अगर (phy_dev->स्वतःneg == AUTONEG_ENABLE) अणु
		val = पढ़ोw(tse_pcs_base + TSE_PCS_CONTROL_REG);
		val |= TSE_PCS_CONTROL_AN_EN_MASK;
		ग_लिखोw(val, tse_pcs_base + TSE_PCS_CONTROL_REG);

		val = पढ़ोw(tse_pcs_base + TSE_PCS_IF_MODE_REG);
		val |= TSE_PCS_USE_SGMII_AN_MASK;
		ग_लिखोw(val, tse_pcs_base + TSE_PCS_IF_MODE_REG);

		val = पढ़ोw(tse_pcs_base + TSE_PCS_CONTROL_REG);
		val |= TSE_PCS_CONTROL_RESTART_AN_MASK;

		tse_pcs_reset(tse_pcs_base, pcs);

		समयr_setup(&pcs->aneg_link_समयr, aneg_link_समयr_callback,
			    0);
		mod_समयr(&pcs->aneg_link_समयr, jअगरfies +
			  msecs_to_jअगरfies(AUTONEGO_LINK_TIMER));
	पूर्ण अन्यथा अगर (phy_dev->स्वतःneg == AUTONEG_DISABLE) अणु
		val = पढ़ोw(tse_pcs_base + TSE_PCS_CONTROL_REG);
		val &= ~TSE_PCS_CONTROL_AN_EN_MASK;
		ग_लिखोw(val, tse_pcs_base + TSE_PCS_CONTROL_REG);

		val = पढ़ोw(tse_pcs_base + TSE_PCS_IF_MODE_REG);
		val &= ~TSE_PCS_USE_SGMII_AN_MASK;
		ग_लिखोw(val, tse_pcs_base + TSE_PCS_IF_MODE_REG);

		val = पढ़ोw(tse_pcs_base + TSE_PCS_IF_MODE_REG);
		val &= ~TSE_PCS_SGMII_SPEED_MASK;

		चयन (speed) अणु
		हाल 1000:
			val |= TSE_PCS_SGMII_SPEED_1000;
			अवरोध;
		हाल 100:
			val |= TSE_PCS_SGMII_SPEED_100;
			अवरोध;
		हाल 10:
			val |= TSE_PCS_SGMII_SPEED_10;
			अवरोध;
		शेष:
			वापस;
		पूर्ण
		ग_लिखोw(val, tse_pcs_base + TSE_PCS_IF_MODE_REG);

		tse_pcs_reset(tse_pcs_base, pcs);

		समयr_setup(&pcs->aneg_link_समयr, aneg_link_समयr_callback,
			    0);
		mod_समयr(&pcs->aneg_link_समयr, jअगरfies +
			  msecs_to_jअगरfies(AUTONEGO_LINK_TIMER));
	पूर्ण
पूर्ण
