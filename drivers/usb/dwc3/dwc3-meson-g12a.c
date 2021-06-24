<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * USB Glue क्रम Amlogic G12A SoCs
 *
 * Copyright (c) 2019 BayLibre, SAS
 * Author: Neil Armstrong <narmstrong@baylibre.com>
 */

/*
 * The USB is organized with a glue around the DWC3 Controller IP as :
 * - Control रेजिस्टरs क्रम each USB2 Ports
 * - Control रेजिस्टरs क्रम the USB PHY layer
 * - SuperSpeed PHY can be enabled only अगर port is used
 * - Dynamic OTG चयनing with ID change पूर्णांकerrupt
 */

#समावेश <linux/module.h>
#समावेश <linux/kernel.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/clk.h>
#समावेश <linux/of.h>
#समावेश <linux/of_platक्रमm.h>
#समावेश <linux/pm_runसमय.स>
#समावेश <linux/regmap.h>
#समावेश <linux/bitfield.h>
#समावेश <linux/bitops.h>
#समावेश <linux/reset.h>
#समावेश <linux/phy/phy.h>
#समावेश <linux/usb/otg.h>
#समावेश <linux/usb/role.h>
#समावेश <linux/regulator/consumer.h>

/* USB2 Ports Control Registers, offsets are per-port */

#घोषणा U2P_REG_SIZE						0x20

#घोषणा U2P_R0							0x0
	#घोषणा U2P_R0_HOST_DEVICE				BIT(0)
	#घोषणा U2P_R0_POWER_OK					BIT(1)
	#घोषणा U2P_R0_HAST_MODE				BIT(2)
	#घोषणा U2P_R0_POWER_ON_RESET				BIT(3)
	#घोषणा U2P_R0_ID_PULLUP				BIT(4)
	#घोषणा U2P_R0_DRV_VBUS					BIT(5)

#घोषणा U2P_R1							0x4
	#घोषणा U2P_R1_PHY_READY				BIT(0)
	#घोषणा U2P_R1_ID_DIG					BIT(1)
	#घोषणा U2P_R1_OTG_SESSION_VALID			BIT(2)
	#घोषणा U2P_R1_VBUS_VALID				BIT(3)

/* USB Glue Control Registers */

#घोषणा G12A_GLUE_OFFSET					0x80

#घोषणा USB_R0							0x00
	#घोषणा USB_R0_P30_LANE0_TX2RX_LOOPBACK			BIT(17)
	#घोषणा USB_R0_P30_LANE0_EXT_PCLK_REQ			BIT(18)
	#घोषणा USB_R0_P30_PCS_RX_LOS_MASK_VAL_MASK		GENMASK(28, 19)
	#घोषणा USB_R0_U2D_SS_SCALEDOWN_MODE_MASK		GENMASK(30, 29)
	#घोषणा USB_R0_U2D_ACT					BIT(31)

#घोषणा USB_R1							0x04
	#घोषणा USB_R1_U3H_BIGENDIAN_GS				BIT(0)
	#घोषणा USB_R1_U3H_PME_ENABLE				BIT(1)
	#घोषणा USB_R1_U3H_HUB_PORT_OVERCURRENT_MASK		GENMASK(4, 2)
	#घोषणा USB_R1_U3H_HUB_PORT_PERM_ATTACH_MASK		GENMASK(9, 7)
	#घोषणा USB_R1_U3H_HOST_U2_PORT_DISABLE_MASK		GENMASK(13, 12)
	#घोषणा USB_R1_U3H_HOST_U3_PORT_DISABLE			BIT(16)
	#घोषणा USB_R1_U3H_HOST_PORT_POWER_CONTROL_PRESENT	BIT(17)
	#घोषणा USB_R1_U3H_HOST_MSI_ENABLE			BIT(18)
	#घोषणा USB_R1_U3H_FLADJ_30MHZ_REG_MASK			GENMASK(24, 19)
	#घोषणा USB_R1_P30_PCS_TX_SWING_FULL_MASK		GENMASK(31, 25)

#घोषणा USB_R2							0x08
	#घोषणा USB_R2_P30_PCS_TX_DEEMPH_3P5DB_MASK		GENMASK(25, 20)
	#घोषणा USB_R2_P30_PCS_TX_DEEMPH_6DB_MASK		GENMASK(31, 26)

#घोषणा USB_R3							0x0c
	#घोषणा USB_R3_P30_SSC_ENABLE				BIT(0)
	#घोषणा USB_R3_P30_SSC_RANGE_MASK			GENMASK(3, 1)
	#घोषणा USB_R3_P30_SSC_REF_CLK_SEL_MASK			GENMASK(12, 4)
	#घोषणा USB_R3_P30_REF_SSP_EN				BIT(13)

#घोषणा USB_R4							0x10
	#घोषणा USB_R4_P21_PORT_RESET_0				BIT(0)
	#घोषणा USB_R4_P21_SLEEP_M0				BIT(1)
	#घोषणा USB_R4_MEM_PD_MASK				GENMASK(3, 2)
	#घोषणा USB_R4_P21_ONLY					BIT(4)

#घोषणा USB_R5							0x14
	#घोषणा USB_R5_ID_DIG_SYNC				BIT(0)
	#घोषणा USB_R5_ID_DIG_REG				BIT(1)
	#घोषणा USB_R5_ID_DIG_CFG_MASK				GENMASK(3, 2)
	#घोषणा USB_R5_ID_DIG_EN_0				BIT(4)
	#घोषणा USB_R5_ID_DIG_EN_1				BIT(5)
	#घोषणा USB_R5_ID_DIG_CURR				BIT(6)
	#घोषणा USB_R5_ID_DIG_IRQ				BIT(7)
	#घोषणा USB_R5_ID_DIG_TH_MASK				GENMASK(15, 8)
	#घोषणा USB_R5_ID_DIG_CNT_MASK				GENMASK(23, 16)

#घोषणा PHY_COUNT						3
#घोषणा USB2_OTG_PHY						1

अटल काष्ठा clk_bulk_data meson_gxl_घड़ीs[] = अणु
	अणु .id = "usb_ctrl" पूर्ण,
	अणु .id = "ddr" पूर्ण,
पूर्ण;

अटल काष्ठा clk_bulk_data meson_g12a_घड़ीs[] = अणु
	अणु .id = शून्य पूर्ण,
पूर्ण;

अटल काष्ठा clk_bulk_data meson_a1_घड़ीs[] = अणु
	अणु .id = "usb_ctrl" पूर्ण,
	अणु .id = "usb_bus" पूर्ण,
	अणु .id = "xtal_usb_ctrl" पूर्ण,
पूर्ण;

अटल स्थिर अक्षर * स्थिर meson_gxm_phy_names[] = अणु
	"usb2-phy0", "usb2-phy1", "usb2-phy2",
पूर्ण;

अटल स्थिर अक्षर * स्थिर meson_g12a_phy_names[] = अणु
	"usb2-phy0", "usb2-phy1", "usb3-phy0",
पूर्ण;

/*
 * Amlogic A1 has a single physical PHY, in slot 1, but still has the
 * two U2 PHY controls रेजिस्टर blocks like G12A.
 * AXG has the similar scheme, thus needs the same tweak.
 * Handling the first PHY on slot 1 would need a large amount of code
 * changes, and the current management is generic enough to handle it
 * correctly when only the "usb2-phy1" phy is specअगरied on-par with the
 * DT bindings.
 */
अटल स्थिर अक्षर * स्थिर meson_a1_phy_names[] = अणु
	"usb2-phy0", "usb2-phy1"
पूर्ण;

काष्ठा dwc3_meson_g12a;

काष्ठा dwc3_meson_g12a_drvdata अणु
	bool otg_चयन_supported;
	bool otg_phy_host_port_disable;
	काष्ठा clk_bulk_data *clks;
	पूर्णांक num_clks;
	स्थिर अक्षर * स्थिर *phy_names;
	पूर्णांक num_phys;
	पूर्णांक (*setup_regmaps)(काष्ठा dwc3_meson_g12a *priv, व्योम __iomem *base);
	पूर्णांक (*usb2_init_phy)(काष्ठा dwc3_meson_g12a *priv, पूर्णांक i,
			     क्रमागत phy_mode mode);
	पूर्णांक (*set_phy_mode)(काष्ठा dwc3_meson_g12a *priv, पूर्णांक i,
			    क्रमागत phy_mode mode);
	पूर्णांक (*usb_init)(काष्ठा dwc3_meson_g12a *priv);
	पूर्णांक (*usb_post_init)(काष्ठा dwc3_meson_g12a *priv);
पूर्ण;

अटल पूर्णांक dwc3_meson_gxl_setup_regmaps(काष्ठा dwc3_meson_g12a *priv,
					व्योम __iomem *base);
अटल पूर्णांक dwc3_meson_g12a_setup_regmaps(काष्ठा dwc3_meson_g12a *priv,
					 व्योम __iomem *base);

अटल पूर्णांक dwc3_meson_g12a_usb2_init_phy(काष्ठा dwc3_meson_g12a *priv, पूर्णांक i,
					 क्रमागत phy_mode mode);
अटल पूर्णांक dwc3_meson_gxl_usb2_init_phy(काष्ठा dwc3_meson_g12a *priv, पूर्णांक i,
					क्रमागत phy_mode mode);

अटल पूर्णांक dwc3_meson_g12a_set_phy_mode(काष्ठा dwc3_meson_g12a *priv,
					पूर्णांक i, क्रमागत phy_mode mode);
अटल पूर्णांक dwc3_meson_gxl_set_phy_mode(काष्ठा dwc3_meson_g12a *priv,
				       पूर्णांक i, क्रमागत phy_mode mode);

अटल पूर्णांक dwc3_meson_g12a_usb_init(काष्ठा dwc3_meson_g12a *priv);
अटल पूर्णांक dwc3_meson_gxl_usb_init(काष्ठा dwc3_meson_g12a *priv);

अटल पूर्णांक dwc3_meson_gxl_usb_post_init(काष्ठा dwc3_meson_g12a *priv);

/*
 * For GXL and GXM SoCs:
 * USB Phy muxing between the DWC2 Device controller and the DWC3 Host
 * controller is buggy when चयनing from Device to Host when USB port
 * is unpopulated, it causes the DWC3 to hard crash.
 * When populated (including OTG चयनing with ID pin), the चयन works
 * like a अक्षरm like on the G12A platक्रमms.
 * In order to still चयन from Host to Device on an USB Type-A port,
 * an U2_PORT_DISABLE bit has been added to disconnect the DWC3 Host
 * controller from the port, but when used the DWC3 controller must be
 * reset to recover usage of the port.
 */

अटल काष्ठा dwc3_meson_g12a_drvdata gxl_drvdata = अणु
	.otg_चयन_supported = true,
	.otg_phy_host_port_disable = true,
	.clks = meson_gxl_घड़ीs,
	.num_clks = ARRAY_SIZE(meson_g12a_घड़ीs),
	.phy_names = meson_a1_phy_names,
	.num_phys = ARRAY_SIZE(meson_a1_phy_names),
	.setup_regmaps = dwc3_meson_gxl_setup_regmaps,
	.usb2_init_phy = dwc3_meson_gxl_usb2_init_phy,
	.set_phy_mode = dwc3_meson_gxl_set_phy_mode,
	.usb_init = dwc3_meson_gxl_usb_init,
	.usb_post_init = dwc3_meson_gxl_usb_post_init,
पूर्ण;

अटल काष्ठा dwc3_meson_g12a_drvdata gxm_drvdata = अणु
	.otg_चयन_supported = true,
	.otg_phy_host_port_disable = true,
	.clks = meson_gxl_घड़ीs,
	.num_clks = ARRAY_SIZE(meson_g12a_घड़ीs),
	.phy_names = meson_gxm_phy_names,
	.num_phys = ARRAY_SIZE(meson_gxm_phy_names),
	.setup_regmaps = dwc3_meson_gxl_setup_regmaps,
	.usb2_init_phy = dwc3_meson_gxl_usb2_init_phy,
	.set_phy_mode = dwc3_meson_gxl_set_phy_mode,
	.usb_init = dwc3_meson_gxl_usb_init,
	.usb_post_init = dwc3_meson_gxl_usb_post_init,
पूर्ण;

अटल काष्ठा dwc3_meson_g12a_drvdata axg_drvdata = अणु
	.otg_चयन_supported = true,
	.clks = meson_gxl_घड़ीs,
	.num_clks = ARRAY_SIZE(meson_gxl_घड़ीs),
	.phy_names = meson_a1_phy_names,
	.num_phys = ARRAY_SIZE(meson_a1_phy_names),
	.setup_regmaps = dwc3_meson_gxl_setup_regmaps,
	.usb2_init_phy = dwc3_meson_gxl_usb2_init_phy,
	.set_phy_mode = dwc3_meson_gxl_set_phy_mode,
	.usb_init = dwc3_meson_g12a_usb_init,
	.usb_post_init = dwc3_meson_gxl_usb_post_init,
पूर्ण;

अटल काष्ठा dwc3_meson_g12a_drvdata g12a_drvdata = अणु
	.otg_चयन_supported = true,
	.clks = meson_g12a_घड़ीs,
	.num_clks = ARRAY_SIZE(meson_g12a_घड़ीs),
	.phy_names = meson_g12a_phy_names,
	.num_phys = ARRAY_SIZE(meson_g12a_phy_names),
	.setup_regmaps = dwc3_meson_g12a_setup_regmaps,
	.usb2_init_phy = dwc3_meson_g12a_usb2_init_phy,
	.set_phy_mode = dwc3_meson_g12a_set_phy_mode,
	.usb_init = dwc3_meson_g12a_usb_init,
पूर्ण;

अटल काष्ठा dwc3_meson_g12a_drvdata a1_drvdata = अणु
	.otg_चयन_supported = false,
	.clks = meson_a1_घड़ीs,
	.num_clks = ARRAY_SIZE(meson_a1_घड़ीs),
	.phy_names = meson_a1_phy_names,
	.num_phys = ARRAY_SIZE(meson_a1_phy_names),
	.setup_regmaps = dwc3_meson_g12a_setup_regmaps,
	.usb2_init_phy = dwc3_meson_g12a_usb2_init_phy,
	.set_phy_mode = dwc3_meson_g12a_set_phy_mode,
	.usb_init = dwc3_meson_g12a_usb_init,
पूर्ण;

काष्ठा dwc3_meson_g12a अणु
	काष्ठा device		*dev;
	काष्ठा regmap		*u2p_regmap[PHY_COUNT];
	काष्ठा regmap		*usb_glue_regmap;
	काष्ठा reset_control	*reset;
	काष्ठा phy		*phys[PHY_COUNT];
	क्रमागत usb_dr_mode	otg_mode;
	क्रमागत phy_mode		otg_phy_mode;
	अचिन्हित पूर्णांक		usb2_ports;
	अचिन्हित पूर्णांक		usb3_ports;
	काष्ठा regulator	*vbus;
	काष्ठा usb_role_चयन_desc चयन_desc;
	काष्ठा usb_role_चयन	*role_चयन;
	स्थिर काष्ठा dwc3_meson_g12a_drvdata *drvdata;
पूर्ण;

अटल पूर्णांक dwc3_meson_gxl_set_phy_mode(काष्ठा dwc3_meson_g12a *priv,
					 पूर्णांक i, क्रमागत phy_mode mode)
अणु
	वापस phy_set_mode(priv->phys[i], mode);
पूर्ण

अटल पूर्णांक dwc3_meson_gxl_usb2_init_phy(काष्ठा dwc3_meson_g12a *priv, पूर्णांक i,
					क्रमागत phy_mode mode)
अणु
	/* On GXL PHY must be started in device mode क्रम DWC2 init */
	वापस priv->drvdata->set_phy_mode(priv, i,
				(i == USB2_OTG_PHY) ? PHY_MODE_USB_DEVICE
						    : PHY_MODE_USB_HOST);
पूर्ण

अटल पूर्णांक dwc3_meson_g12a_set_phy_mode(काष्ठा dwc3_meson_g12a *priv,
					 पूर्णांक i, क्रमागत phy_mode mode)
अणु
	अगर (mode == PHY_MODE_USB_HOST)
		regmap_update_bits(priv->u2p_regmap[i], U2P_R0,
				U2P_R0_HOST_DEVICE,
				U2P_R0_HOST_DEVICE);
	अन्यथा
		regmap_update_bits(priv->u2p_regmap[i], U2P_R0,
				U2P_R0_HOST_DEVICE, 0);

	वापस 0;
पूर्ण

अटल पूर्णांक dwc3_meson_g12a_usb2_init_phy(काष्ठा dwc3_meson_g12a *priv, पूर्णांक i,
					 क्रमागत phy_mode mode)
अणु
	पूर्णांक ret;

	regmap_update_bits(priv->u2p_regmap[i], U2P_R0,
			U2P_R0_POWER_ON_RESET,
			U2P_R0_POWER_ON_RESET);

	अगर (priv->drvdata->otg_चयन_supported && i == USB2_OTG_PHY) अणु
		regmap_update_bits(priv->u2p_regmap[i], U2P_R0,
				   U2P_R0_ID_PULLUP | U2P_R0_DRV_VBUS,
				   U2P_R0_ID_PULLUP | U2P_R0_DRV_VBUS);

		ret = priv->drvdata->set_phy_mode(priv, i, mode);
	पूर्ण अन्यथा
		ret = priv->drvdata->set_phy_mode(priv, i,
						  PHY_MODE_USB_HOST);

	अगर (ret)
		वापस ret;

	regmap_update_bits(priv->u2p_regmap[i], U2P_R0,
			U2P_R0_POWER_ON_RESET, 0);

	वापस 0;
पूर्ण

अटल पूर्णांक dwc3_meson_g12a_usb2_init(काष्ठा dwc3_meson_g12a *priv,
				     क्रमागत phy_mode mode)
अणु
	पूर्णांक i, ret;

	क्रम (i = 0; i < priv->drvdata->num_phys; ++i) अणु
		अगर (!priv->phys[i])
			जारी;

		अगर (!म_माला(priv->drvdata->phy_names[i], "usb2"))
			जारी;

		ret = priv->drvdata->usb2_init_phy(priv, i, mode);
		अगर (ret)
			वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम dwc3_meson_g12a_usb3_init(काष्ठा dwc3_meson_g12a *priv)
अणु
	regmap_update_bits(priv->usb_glue_regmap, USB_R3,
			USB_R3_P30_SSC_RANGE_MASK |
			USB_R3_P30_REF_SSP_EN,
			USB_R3_P30_SSC_ENABLE |
			FIELD_PREP(USB_R3_P30_SSC_RANGE_MASK, 2) |
			USB_R3_P30_REF_SSP_EN);
	udelay(2);

	regmap_update_bits(priv->usb_glue_regmap, USB_R2,
			USB_R2_P30_PCS_TX_DEEMPH_3P5DB_MASK,
			FIELD_PREP(USB_R2_P30_PCS_TX_DEEMPH_3P5DB_MASK, 0x15));

	regmap_update_bits(priv->usb_glue_regmap, USB_R2,
			USB_R2_P30_PCS_TX_DEEMPH_6DB_MASK,
			FIELD_PREP(USB_R2_P30_PCS_TX_DEEMPH_6DB_MASK, 0x20));

	udelay(2);

	regmap_update_bits(priv->usb_glue_regmap, USB_R1,
			USB_R1_U3H_HOST_PORT_POWER_CONTROL_PRESENT,
			USB_R1_U3H_HOST_PORT_POWER_CONTROL_PRESENT);

	regmap_update_bits(priv->usb_glue_regmap, USB_R1,
			USB_R1_P30_PCS_TX_SWING_FULL_MASK,
			FIELD_PREP(USB_R1_P30_PCS_TX_SWING_FULL_MASK, 127));
पूर्ण

अटल व्योम dwc3_meson_g12a_usb_otg_apply_mode(काष्ठा dwc3_meson_g12a *priv,
					       क्रमागत phy_mode mode)
अणु
	अगर (mode == PHY_MODE_USB_DEVICE) अणु
		अगर (priv->otg_mode != USB_DR_MODE_OTG &&
		    priv->drvdata->otg_phy_host_port_disable)
			/* Isolate the OTG PHY port from the Host Controller */
			regmap_update_bits(priv->usb_glue_regmap, USB_R1,
				USB_R1_U3H_HOST_U2_PORT_DISABLE_MASK,
				FIELD_PREP(USB_R1_U3H_HOST_U2_PORT_DISABLE_MASK,
					   BIT(USB2_OTG_PHY)));

		regmap_update_bits(priv->usb_glue_regmap, USB_R0,
				USB_R0_U2D_ACT, USB_R0_U2D_ACT);
		regmap_update_bits(priv->usb_glue_regmap, USB_R0,
				USB_R0_U2D_SS_SCALEDOWN_MODE_MASK, 0);
		regmap_update_bits(priv->usb_glue_regmap, USB_R4,
				USB_R4_P21_SLEEP_M0, USB_R4_P21_SLEEP_M0);
	पूर्ण अन्यथा अणु
		अगर (priv->otg_mode != USB_DR_MODE_OTG &&
		    priv->drvdata->otg_phy_host_port_disable) अणु
			regmap_update_bits(priv->usb_glue_regmap, USB_R1,
				USB_R1_U3H_HOST_U2_PORT_DISABLE_MASK, 0);
			msleep(500);
		पूर्ण
		regmap_update_bits(priv->usb_glue_regmap, USB_R0,
				USB_R0_U2D_ACT, 0);
		regmap_update_bits(priv->usb_glue_regmap, USB_R4,
				USB_R4_P21_SLEEP_M0, 0);
	पूर्ण
पूर्ण

अटल पूर्णांक dwc3_meson_g12a_usb_init_glue(काष्ठा dwc3_meson_g12a *priv,
					 क्रमागत phy_mode mode)
अणु
	पूर्णांक ret;

	ret = dwc3_meson_g12a_usb2_init(priv, mode);
	अगर (ret)
		वापस ret;

	regmap_update_bits(priv->usb_glue_regmap, USB_R1,
			USB_R1_U3H_FLADJ_30MHZ_REG_MASK,
			FIELD_PREP(USB_R1_U3H_FLADJ_30MHZ_REG_MASK, 0x20));

	regmap_update_bits(priv->usb_glue_regmap, USB_R5,
			USB_R5_ID_DIG_EN_0,
			USB_R5_ID_DIG_EN_0);
	regmap_update_bits(priv->usb_glue_regmap, USB_R5,
			USB_R5_ID_DIG_EN_1,
			USB_R5_ID_DIG_EN_1);
	regmap_update_bits(priv->usb_glue_regmap, USB_R5,
			USB_R5_ID_DIG_TH_MASK,
			FIELD_PREP(USB_R5_ID_DIG_TH_MASK, 0xff));

	/* If we have an actual SuperSpeed port, initialize it */
	अगर (priv->usb3_ports)
		dwc3_meson_g12a_usb3_init(priv);

	dwc3_meson_g12a_usb_otg_apply_mode(priv, mode);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा regmap_config phy_meson_g12a_usb_glue_regmap_conf = अणु
	.name = "usb-glue",
	.reg_bits = 8,
	.val_bits = 32,
	.reg_stride = 4,
	.max_रेजिस्टर = USB_R5,
पूर्ण;

अटल पूर्णांक dwc3_meson_g12a_get_phys(काष्ठा dwc3_meson_g12a *priv)
अणु
	स्थिर अक्षर *phy_name;
	पूर्णांक i;

	क्रम (i = 0 ; i < priv->drvdata->num_phys ; ++i) अणु
		phy_name = priv->drvdata->phy_names[i];
		priv->phys[i] = devm_phy_optional_get(priv->dev, phy_name);
		अगर (!priv->phys[i])
			जारी;

		अगर (IS_ERR(priv->phys[i]))
			वापस PTR_ERR(priv->phys[i]);

		अगर (म_माला(phy_name, "usb3"))
			priv->usb3_ports++;
		अन्यथा
			priv->usb2_ports++;
	पूर्ण

	dev_info(priv->dev, "USB2 ports: %d\n", priv->usb2_ports);
	dev_info(priv->dev, "USB3 ports: %d\n", priv->usb3_ports);

	वापस 0;
पूर्ण

अटल क्रमागत phy_mode dwc3_meson_g12a_get_id(काष्ठा dwc3_meson_g12a *priv)
अणु
	u32 reg;

	regmap_पढ़ो(priv->usb_glue_regmap, USB_R5, &reg);

	अगर (reg & (USB_R5_ID_DIG_SYNC | USB_R5_ID_DIG_REG))
		वापस PHY_MODE_USB_DEVICE;

	वापस PHY_MODE_USB_HOST;
पूर्ण

अटल पूर्णांक dwc3_meson_g12a_otg_mode_set(काष्ठा dwc3_meson_g12a *priv,
					क्रमागत phy_mode mode)
अणु
	पूर्णांक ret;

	अगर (!priv->drvdata->otg_चयन_supported || !priv->phys[USB2_OTG_PHY])
		वापस -EINVAL;

	अगर (mode == PHY_MODE_USB_HOST)
		dev_info(priv->dev, "switching to Host Mode\n");
	अन्यथा
		dev_info(priv->dev, "switching to Device Mode\n");

	अगर (priv->vbus) अणु
		अगर (mode == PHY_MODE_USB_DEVICE)
			ret = regulator_disable(priv->vbus);
		अन्यथा
			ret = regulator_enable(priv->vbus);
		अगर (ret)
			वापस ret;
	पूर्ण

	priv->otg_phy_mode = mode;

	ret = priv->drvdata->set_phy_mode(priv, USB2_OTG_PHY, mode);
	अगर (ret)
		वापस ret;

	dwc3_meson_g12a_usb_otg_apply_mode(priv, mode);

	वापस 0;
पूर्ण

अटल पूर्णांक dwc3_meson_g12a_role_set(काष्ठा usb_role_चयन *sw,
				    क्रमागत usb_role role)
अणु
	काष्ठा dwc3_meson_g12a *priv = usb_role_चयन_get_drvdata(sw);
	क्रमागत phy_mode mode;

	अगर (role == USB_ROLE_NONE)
		वापस 0;

	mode = (role == USB_ROLE_HOST) ? PHY_MODE_USB_HOST
				       : PHY_MODE_USB_DEVICE;

	अगर (mode == priv->otg_phy_mode)
		वापस 0;

	अगर (priv->drvdata->otg_phy_host_port_disable)
		dev_warn_once(priv->dev, "Broken manual OTG switch\n");

	वापस dwc3_meson_g12a_otg_mode_set(priv, mode);
पूर्ण

अटल क्रमागत usb_role dwc3_meson_g12a_role_get(काष्ठा usb_role_चयन *sw)
अणु
	काष्ठा dwc3_meson_g12a *priv = usb_role_चयन_get_drvdata(sw);

	वापस priv->otg_phy_mode == PHY_MODE_USB_HOST ?
		USB_ROLE_HOST : USB_ROLE_DEVICE;
पूर्ण

अटल irqवापस_t dwc3_meson_g12a_irq_thपढ़ो(पूर्णांक irq, व्योम *data)
अणु
	काष्ठा dwc3_meson_g12a *priv = data;
	क्रमागत phy_mode otg_id;

	otg_id = dwc3_meson_g12a_get_id(priv);
	अगर (otg_id != priv->otg_phy_mode) अणु
		अगर (dwc3_meson_g12a_otg_mode_set(priv, otg_id))
			dev_warn(priv->dev, "Failed to switch OTG mode\n");
	पूर्ण

	regmap_update_bits(priv->usb_glue_regmap, USB_R5,
			   USB_R5_ID_DIG_IRQ, 0);

	वापस IRQ_HANDLED;
पूर्ण

अटल काष्ठा device *dwc3_meson_g12_find_child(काष्ठा device *dev,
						स्थिर अक्षर *compatible)
अणु
	काष्ठा platक्रमm_device *pdev;
	काष्ठा device_node *np;

	np = of_get_compatible_child(dev->of_node, compatible);
	अगर (!np)
		वापस शून्य;

	pdev = of_find_device_by_node(np);
	of_node_put(np);
	अगर (!pdev)
		वापस शून्य;

	वापस &pdev->dev;
पूर्ण

अटल पूर्णांक dwc3_meson_g12a_otg_init(काष्ठा platक्रमm_device *pdev,
				    काष्ठा dwc3_meson_g12a *priv)
अणु
	क्रमागत phy_mode otg_id;
	पूर्णांक ret, irq;
	काष्ठा device *dev = &pdev->dev;

	अगर (!priv->drvdata->otg_चयन_supported)
		वापस 0;

	अगर (priv->otg_mode == USB_DR_MODE_OTG) अणु
		/* Ack irq beक्रमe रेजिस्टरing */
		regmap_update_bits(priv->usb_glue_regmap, USB_R5,
				   USB_R5_ID_DIG_IRQ, 0);

		irq = platक्रमm_get_irq(pdev, 0);
		ret = devm_request_thपढ़ोed_irq(&pdev->dev, irq, शून्य,
						dwc3_meson_g12a_irq_thपढ़ो,
						IRQF_ONESHOT, pdev->name, priv);
		अगर (ret)
			वापस ret;
	पूर्ण

	/* Setup OTG mode corresponding to the ID pin */
	अगर (priv->otg_mode == USB_DR_MODE_OTG) अणु
		otg_id = dwc3_meson_g12a_get_id(priv);
		अगर (otg_id != priv->otg_phy_mode) अणु
			अगर (dwc3_meson_g12a_otg_mode_set(priv, otg_id))
				dev_warn(dev, "Failed to switch OTG mode\n");
		पूर्ण
	पूर्ण

	/* Setup role चयनer */
	priv->चयन_desc.usb2_port = dwc3_meson_g12_find_child(dev,
								"snps,dwc3");
	priv->चयन_desc.udc = dwc3_meson_g12_find_child(dev, "snps,dwc2");
	priv->चयन_desc.allow_userspace_control = true;
	priv->चयन_desc.set = dwc3_meson_g12a_role_set;
	priv->चयन_desc.get = dwc3_meson_g12a_role_get;
	priv->चयन_desc.driver_data = priv;

	priv->role_चयन = usb_role_चयन_रेजिस्टर(dev, &priv->चयन_desc);
	अगर (IS_ERR(priv->role_चयन))
		dev_warn(dev, "Unable to register Role Switch\n");

	वापस 0;
पूर्ण

अटल पूर्णांक dwc3_meson_gxl_setup_regmaps(काष्ठा dwc3_meson_g12a *priv,
					व्योम __iomem *base)
अणु
	/* GXL controls the PHY mode in the PHY रेजिस्टरs unlike G12A */
	priv->usb_glue_regmap = devm_regmap_init_mmio(priv->dev, base,
					&phy_meson_g12a_usb_glue_regmap_conf);
	वापस PTR_ERR_OR_ZERO(priv->usb_glue_regmap);
पूर्ण

अटल पूर्णांक dwc3_meson_g12a_setup_regmaps(काष्ठा dwc3_meson_g12a *priv,
					 व्योम __iomem *base)
अणु
	पूर्णांक i;

	priv->usb_glue_regmap = devm_regmap_init_mmio(priv->dev,
					base + G12A_GLUE_OFFSET,
					&phy_meson_g12a_usb_glue_regmap_conf);
	अगर (IS_ERR(priv->usb_glue_regmap))
		वापस PTR_ERR(priv->usb_glue_regmap);

	/* Create a regmap क्रम each USB2 PHY control रेजिस्टर set */
	क्रम (i = 0; i < priv->drvdata->num_phys; i++) अणु
		काष्ठा regmap_config u2p_regmap_config = अणु
			.reg_bits = 8,
			.val_bits = 32,
			.reg_stride = 4,
			.max_रेजिस्टर = U2P_R1,
		पूर्ण;

		अगर (!म_माला(priv->drvdata->phy_names[i], "usb2"))
			जारी;

		u2p_regmap_config.name = devm_kaप्र_लिखो(priv->dev, GFP_KERNEL,
							"u2p-%d", i);
		अगर (!u2p_regmap_config.name)
			वापस -ENOMEM;

		priv->u2p_regmap[i] = devm_regmap_init_mmio(priv->dev,
						base + (i * U2P_REG_SIZE),
						&u2p_regmap_config);
		अगर (IS_ERR(priv->u2p_regmap[i]))
			वापस PTR_ERR(priv->u2p_regmap[i]);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक dwc3_meson_g12a_usb_init(काष्ठा dwc3_meson_g12a *priv)
अणु
	वापस dwc3_meson_g12a_usb_init_glue(priv, priv->otg_phy_mode);
पूर्ण

अटल पूर्णांक dwc3_meson_gxl_usb_init(काष्ठा dwc3_meson_g12a *priv)
अणु
	वापस dwc3_meson_g12a_usb_init_glue(priv, PHY_MODE_USB_DEVICE);
पूर्ण

अटल पूर्णांक dwc3_meson_gxl_usb_post_init(काष्ठा dwc3_meson_g12a *priv)
अणु
	पूर्णांक ret;

	ret = priv->drvdata->set_phy_mode(priv, USB2_OTG_PHY,
					  priv->otg_phy_mode);
	अगर (ret)
		वापस ret;

	dwc3_meson_g12a_usb_otg_apply_mode(priv, priv->otg_phy_mode);

	वापस 0;
पूर्ण

अटल पूर्णांक dwc3_meson_g12a_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा dwc3_meson_g12a	*priv;
	काष्ठा device		*dev = &pdev->dev;
	काष्ठा device_node	*np = dev->of_node;
	व्योम __iomem *base;
	पूर्णांक ret, i;

	priv = devm_kzalloc(dev, माप(*priv), GFP_KERNEL);
	अगर (!priv)
		वापस -ENOMEM;

	base = devm_platक्रमm_ioremap_resource(pdev, 0);
	अगर (IS_ERR(base))
		वापस PTR_ERR(base);

	priv->drvdata = of_device_get_match_data(&pdev->dev);
	priv->dev = dev;

	priv->vbus = devm_regulator_get_optional(dev, "vbus");
	अगर (IS_ERR(priv->vbus)) अणु
		अगर (PTR_ERR(priv->vbus) == -EPROBE_DEFER)
			वापस PTR_ERR(priv->vbus);
		priv->vbus = शून्य;
	पूर्ण

	ret = devm_clk_bulk_get(dev,
				priv->drvdata->num_clks,
				priv->drvdata->clks);
	अगर (ret)
		वापस ret;

	ret = clk_bulk_prepare_enable(priv->drvdata->num_clks,
				      priv->drvdata->clks);
	अगर (ret)
		वापस ret;

	platक्रमm_set_drvdata(pdev, priv);

	priv->reset = devm_reset_control_get_shared(dev, शून्य);
	अगर (IS_ERR(priv->reset)) अणु
		ret = PTR_ERR(priv->reset);
		dev_err(dev, "failed to get device reset, err=%d\n", ret);
		जाओ err_disable_clks;
	पूर्ण

	ret = reset_control_reset(priv->reset);
	अगर (ret)
		जाओ err_disable_clks;

	ret = dwc3_meson_g12a_get_phys(priv);
	अगर (ret)
		जाओ err_disable_clks;

	ret = priv->drvdata->setup_regmaps(priv, base);
	अगर (ret)
		जाओ err_disable_clks;

	अगर (priv->vbus) अणु
		ret = regulator_enable(priv->vbus);
		अगर (ret)
			जाओ err_disable_clks;
	पूर्ण

	/* Get dr_mode */
	priv->otg_mode = usb_get_dr_mode(dev);

	अगर (priv->otg_mode == USB_DR_MODE_PERIPHERAL)
		priv->otg_phy_mode = PHY_MODE_USB_DEVICE;
	अन्यथा
		priv->otg_phy_mode = PHY_MODE_USB_HOST;

	ret = priv->drvdata->usb_init(priv);
	अगर (ret)
		जाओ err_disable_regulator;

	/* Init PHYs */
	क्रम (i = 0 ; i < PHY_COUNT ; ++i) अणु
		ret = phy_init(priv->phys[i]);
		अगर (ret)
			जाओ err_disable_regulator;
	पूर्ण

	/* Set PHY Power */
	क्रम (i = 0 ; i < PHY_COUNT ; ++i) अणु
		ret = phy_घातer_on(priv->phys[i]);
		अगर (ret)
			जाओ err_phys_निकास;
	पूर्ण

	अगर (priv->drvdata->usb_post_init) अणु
		ret = priv->drvdata->usb_post_init(priv);
		अगर (ret)
			जाओ err_phys_घातer;
	पूर्ण

	ret = of_platक्रमm_populate(np, शून्य, शून्य, dev);
	अगर (ret)
		जाओ err_phys_घातer;

	ret = dwc3_meson_g12a_otg_init(pdev, priv);
	अगर (ret)
		जाओ err_phys_घातer;

	pm_runसमय_set_active(dev);
	pm_runसमय_enable(dev);
	pm_runसमय_get_sync(dev);

	वापस 0;

err_phys_घातer:
	क्रम (i = 0 ; i < PHY_COUNT ; ++i)
		phy_घातer_off(priv->phys[i]);

err_phys_निकास:
	क्रम (i = 0 ; i < PHY_COUNT ; ++i)
		phy_निकास(priv->phys[i]);

err_disable_regulator:
	अगर (priv->vbus)
		regulator_disable(priv->vbus);

err_disable_clks:
	clk_bulk_disable_unprepare(priv->drvdata->num_clks,
				   priv->drvdata->clks);

	वापस ret;
पूर्ण

अटल पूर्णांक dwc3_meson_g12a_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा dwc3_meson_g12a *priv = platक्रमm_get_drvdata(pdev);
	काष्ठा device *dev = &pdev->dev;
	पूर्णांक i;

	अगर (priv->drvdata->otg_चयन_supported)
		usb_role_चयन_unरेजिस्टर(priv->role_चयन);

	of_platक्रमm_depopulate(dev);

	क्रम (i = 0 ; i < PHY_COUNT ; ++i) अणु
		phy_घातer_off(priv->phys[i]);
		phy_निकास(priv->phys[i]);
	पूर्ण

	pm_runसमय_disable(dev);
	pm_runसमय_put_noidle(dev);
	pm_runसमय_set_suspended(dev);

	clk_bulk_disable_unprepare(priv->drvdata->num_clks,
				   priv->drvdata->clks);

	वापस 0;
पूर्ण

अटल पूर्णांक __maybe_unused dwc3_meson_g12a_runसमय_suspend(काष्ठा device *dev)
अणु
	काष्ठा dwc3_meson_g12a	*priv = dev_get_drvdata(dev);

	clk_bulk_disable_unprepare(priv->drvdata->num_clks,
				   priv->drvdata->clks);

	वापस 0;
पूर्ण

अटल पूर्णांक __maybe_unused dwc3_meson_g12a_runसमय_resume(काष्ठा device *dev)
अणु
	काष्ठा dwc3_meson_g12a	*priv = dev_get_drvdata(dev);

	वापस clk_bulk_prepare_enable(priv->drvdata->num_clks,
				       priv->drvdata->clks);
पूर्ण

अटल पूर्णांक __maybe_unused dwc3_meson_g12a_suspend(काष्ठा device *dev)
अणु
	काष्ठा dwc3_meson_g12a *priv = dev_get_drvdata(dev);
	पूर्णांक i, ret;

	अगर (priv->vbus && priv->otg_phy_mode == PHY_MODE_USB_HOST) अणु
		ret = regulator_disable(priv->vbus);
		अगर (ret)
			वापस ret;
	पूर्ण

	क्रम (i = 0 ; i < PHY_COUNT ; ++i) अणु
		phy_घातer_off(priv->phys[i]);
		phy_निकास(priv->phys[i]);
	पूर्ण

	reset_control_निश्चित(priv->reset);

	वापस 0;
पूर्ण

अटल पूर्णांक __maybe_unused dwc3_meson_g12a_resume(काष्ठा device *dev)
अणु
	काष्ठा dwc3_meson_g12a *priv = dev_get_drvdata(dev);
	पूर्णांक i, ret;

	reset_control_deनिश्चित(priv->reset);

	ret = priv->drvdata->usb_init(priv);
	अगर (ret)
		वापस ret;

	/* Init PHYs */
	क्रम (i = 0 ; i < PHY_COUNT ; ++i) अणु
		ret = phy_init(priv->phys[i]);
		अगर (ret)
			वापस ret;
	पूर्ण

	/* Set PHY Power */
	क्रम (i = 0 ; i < PHY_COUNT ; ++i) अणु
		ret = phy_घातer_on(priv->phys[i]);
		अगर (ret)
			वापस ret;
	पूर्ण

	अगर (priv->vbus && priv->otg_phy_mode == PHY_MODE_USB_HOST) अणु
		ret = regulator_enable(priv->vbus);
		अगर (ret)
			वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा dev_pm_ops dwc3_meson_g12a_dev_pm_ops = अणु
	SET_SYSTEM_SLEEP_PM_OPS(dwc3_meson_g12a_suspend, dwc3_meson_g12a_resume)
	SET_RUNTIME_PM_OPS(dwc3_meson_g12a_runसमय_suspend,
			   dwc3_meson_g12a_runसमय_resume, शून्य)
पूर्ण;

अटल स्थिर काष्ठा of_device_id dwc3_meson_g12a_match[] = अणु
	अणु
		.compatible = "amlogic,meson-gxl-usb-ctrl",
		.data = &gxl_drvdata,
	पूर्ण,
	अणु
		.compatible = "amlogic,meson-gxm-usb-ctrl",
		.data = &gxm_drvdata,
	पूर्ण,
	अणु
		.compatible = "amlogic,meson-axg-usb-ctrl",
		.data = &axg_drvdata,
	पूर्ण,
	अणु
		.compatible = "amlogic,meson-g12a-usb-ctrl",
		.data = &g12a_drvdata,
	पूर्ण,
	अणु
		.compatible = "amlogic,meson-a1-usb-ctrl",
		.data = &a1_drvdata,
	पूर्ण,
	अणु /* Sentinel */ पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, dwc3_meson_g12a_match);

अटल काष्ठा platक्रमm_driver dwc3_meson_g12a_driver = अणु
	.probe		= dwc3_meson_g12a_probe,
	.हटाओ		= dwc3_meson_g12a_हटाओ,
	.driver		= अणु
		.name	= "dwc3-meson-g12a",
		.of_match_table = dwc3_meson_g12a_match,
		.pm	= &dwc3_meson_g12a_dev_pm_ops,
	पूर्ण,
पूर्ण;

module_platक्रमm_driver(dwc3_meson_g12a_driver);
MODULE_LICENSE("GPL v2");
MODULE_DESCRIPTION("Amlogic Meson G12A USB Glue Layer");
MODULE_AUTHOR("Neil Armstrong <narmstrong@baylibre.com>");
