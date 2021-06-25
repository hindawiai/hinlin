<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (C) 2018 Marvell
 *
 * Authors:
 *   Evan Wang <xswang@marvell.com>
 *   Miquथउl Raynal <miquel.raynal@bootlin.com>
 *
 * Structure inspired from phy-mvebu-cp110-comphy.c written by Antoine Tenart.
 * SMC call initial support करोne by Grzegorz Jaszczyk.
 */

#समावेश <linux/arm-smccc.h>
#समावेश <linux/पन.स>
#समावेश <linux/iopoll.h>
#समावेश <linux/mfd/syscon.h>
#समावेश <linux/module.h>
#समावेश <linux/phy.h>
#समावेश <linux/phy/phy.h>
#समावेश <linux/platक्रमm_device.h>

#घोषणा MVEBU_A3700_COMPHY_LANES		3
#घोषणा MVEBU_A3700_COMPHY_PORTS		2

/* COMPHY Fast SMC function identअगरiers */
#घोषणा COMPHY_SIP_POWER_ON			0x82000001
#घोषणा COMPHY_SIP_POWER_OFF			0x82000002
#घोषणा COMPHY_SIP_PLL_LOCK			0x82000003

#घोषणा COMPHY_FW_MODE_SATA			0x1
#घोषणा COMPHY_FW_MODE_SGMII			0x2
#घोषणा COMPHY_FW_MODE_HS_SGMII			0x3
#घोषणा COMPHY_FW_MODE_USB3H			0x4
#घोषणा COMPHY_FW_MODE_USB3D			0x5
#घोषणा COMPHY_FW_MODE_PCIE			0x6
#घोषणा COMPHY_FW_MODE_RXAUI			0x7
#घोषणा COMPHY_FW_MODE_XFI			0x8
#घोषणा COMPHY_FW_MODE_SFI			0x9
#घोषणा COMPHY_FW_MODE_USB3			0xa

#घोषणा COMPHY_FW_SPEED_1_25G			0 /* SGMII 1G */
#घोषणा COMPHY_FW_SPEED_2_5G			1
#घोषणा COMPHY_FW_SPEED_3_125G			2 /* SGMII 2.5G */
#घोषणा COMPHY_FW_SPEED_5G			3
#घोषणा COMPHY_FW_SPEED_5_15625G		4 /* XFI 5G */
#घोषणा COMPHY_FW_SPEED_6G			5
#घोषणा COMPHY_FW_SPEED_10_3125G		6 /* XFI 10G */
#घोषणा COMPHY_FW_SPEED_MAX			0x3F

#घोषणा COMPHY_FW_MODE(mode)			((mode) << 12)
#घोषणा COMPHY_FW_NET(mode, idx, speed)		(COMPHY_FW_MODE(mode) | \
						 ((idx) << 8) |	\
						 ((speed) << 2))
#घोषणा COMPHY_FW_PCIE(mode, idx, speed, width)	(COMPHY_FW_NET(mode, idx, speed) | \
						 ((width) << 18))

काष्ठा mvebu_a3700_comphy_conf अणु
	अचिन्हित पूर्णांक lane;
	क्रमागत phy_mode mode;
	पूर्णांक submode;
	अचिन्हित पूर्णांक port;
	u32 fw_mode;
पूर्ण;

#घोषणा MVEBU_A3700_COMPHY_CONF(_lane, _mode, _smode, _port, _fw)	\
	अणु								\
		.lane = _lane,						\
		.mode = _mode,						\
		.submode = _smode,					\
		.port = _port,						\
		.fw_mode = _fw,						\
	पूर्ण

#घोषणा MVEBU_A3700_COMPHY_CONF_GEN(_lane, _mode, _port, _fw) \
	MVEBU_A3700_COMPHY_CONF(_lane, _mode, PHY_INTERFACE_MODE_NA, _port, _fw)

#घोषणा MVEBU_A3700_COMPHY_CONF_ETH(_lane, _smode, _port, _fw) \
	MVEBU_A3700_COMPHY_CONF(_lane, PHY_MODE_ETHERNET, _smode, _port, _fw)

अटल स्थिर काष्ठा mvebu_a3700_comphy_conf mvebu_a3700_comphy_modes[] = अणु
	/* lane 0 */
	MVEBU_A3700_COMPHY_CONF_GEN(0, PHY_MODE_USB_HOST_SS, 0,
				    COMPHY_FW_MODE_USB3H),
	MVEBU_A3700_COMPHY_CONF_ETH(0, PHY_INTERFACE_MODE_SGMII, 1,
				    COMPHY_FW_MODE_SGMII),
	MVEBU_A3700_COMPHY_CONF_ETH(0, PHY_INTERFACE_MODE_2500BASEX, 1,
				    COMPHY_FW_MODE_HS_SGMII),
	/* lane 1 */
	MVEBU_A3700_COMPHY_CONF_GEN(1, PHY_MODE_PCIE, 0,
				    COMPHY_FW_MODE_PCIE),
	MVEBU_A3700_COMPHY_CONF_ETH(1, PHY_INTERFACE_MODE_SGMII, 0,
				    COMPHY_FW_MODE_SGMII),
	MVEBU_A3700_COMPHY_CONF_ETH(1, PHY_INTERFACE_MODE_2500BASEX, 0,
				    COMPHY_FW_MODE_HS_SGMII),
	/* lane 2 */
	MVEBU_A3700_COMPHY_CONF_GEN(2, PHY_MODE_SATA, 0,
				    COMPHY_FW_MODE_SATA),
	MVEBU_A3700_COMPHY_CONF_GEN(2, PHY_MODE_USB_HOST_SS, 0,
				    COMPHY_FW_MODE_USB3H),
पूर्ण;

काष्ठा mvebu_a3700_comphy_lane अणु
	काष्ठा device *dev;
	अचिन्हित पूर्णांक id;
	क्रमागत phy_mode mode;
	पूर्णांक submode;
	पूर्णांक port;
पूर्ण;

अटल पूर्णांक mvebu_a3700_comphy_smc(अचिन्हित दीर्घ function, अचिन्हित दीर्घ lane,
				  अचिन्हित दीर्घ mode)
अणु
	काष्ठा arm_smccc_res res;
	s32 ret;

	arm_smccc_smc(function, lane, mode, 0, 0, 0, 0, 0, &res);
	ret = res.a0;

	चयन (ret) अणु
	हाल SMCCC_RET_SUCCESS:
		वापस 0;
	हाल SMCCC_RET_NOT_SUPPORTED:
		वापस -EOPNOTSUPP;
	शेष:
		वापस -EINVAL;
	पूर्ण
पूर्ण

अटल पूर्णांक mvebu_a3700_comphy_get_fw_mode(पूर्णांक lane, पूर्णांक port,
					  क्रमागत phy_mode mode,
					  पूर्णांक submode)
अणु
	पूर्णांक i, n = ARRAY_SIZE(mvebu_a3700_comphy_modes);

	/* Unused PHY mux value is 0x0 */
	अगर (mode == PHY_MODE_INVALID)
		वापस -EINVAL;

	क्रम (i = 0; i < n; i++) अणु
		अगर (mvebu_a3700_comphy_modes[i].lane == lane &&
		    mvebu_a3700_comphy_modes[i].port == port &&
		    mvebu_a3700_comphy_modes[i].mode == mode &&
		    mvebu_a3700_comphy_modes[i].submode == submode)
			अवरोध;
	पूर्ण

	अगर (i == n)
		वापस -EINVAL;

	वापस mvebu_a3700_comphy_modes[i].fw_mode;
पूर्ण

अटल पूर्णांक mvebu_a3700_comphy_set_mode(काष्ठा phy *phy, क्रमागत phy_mode mode,
				       पूर्णांक submode)
अणु
	काष्ठा mvebu_a3700_comphy_lane *lane = phy_get_drvdata(phy);
	पूर्णांक fw_mode;

	अगर (submode == PHY_INTERFACE_MODE_1000BASEX)
		submode = PHY_INTERFACE_MODE_SGMII;

	fw_mode = mvebu_a3700_comphy_get_fw_mode(lane->id, lane->port, mode,
						 submode);
	अगर (fw_mode < 0) अणु
		dev_err(lane->dev, "invalid COMPHY mode\n");
		वापस fw_mode;
	पूर्ण

	/* Just remember the mode, ->घातer_on() will करो the real setup */
	lane->mode = mode;
	lane->submode = submode;

	वापस 0;
पूर्ण

अटल पूर्णांक mvebu_a3700_comphy_घातer_on(काष्ठा phy *phy)
अणु
	काष्ठा mvebu_a3700_comphy_lane *lane = phy_get_drvdata(phy);
	u32 fw_param;
	पूर्णांक fw_mode;
	पूर्णांक ret;

	fw_mode = mvebu_a3700_comphy_get_fw_mode(lane->id, lane->port,
						 lane->mode, lane->submode);
	अगर (fw_mode < 0) अणु
		dev_err(lane->dev, "invalid COMPHY mode\n");
		वापस fw_mode;
	पूर्ण

	चयन (lane->mode) अणु
	हाल PHY_MODE_USB_HOST_SS:
		dev_dbg(lane->dev, "set lane %d to USB3 host mode\n", lane->id);
		fw_param = COMPHY_FW_MODE(fw_mode);
		अवरोध;
	हाल PHY_MODE_SATA:
		dev_dbg(lane->dev, "set lane %d to SATA mode\n", lane->id);
		fw_param = COMPHY_FW_MODE(fw_mode);
		अवरोध;
	हाल PHY_MODE_ETHERNET:
		चयन (lane->submode) अणु
		हाल PHY_INTERFACE_MODE_SGMII:
			dev_dbg(lane->dev, "set lane %d to SGMII mode\n",
				lane->id);
			fw_param = COMPHY_FW_NET(fw_mode, lane->port,
						 COMPHY_FW_SPEED_1_25G);
			अवरोध;
		हाल PHY_INTERFACE_MODE_2500BASEX:
			dev_dbg(lane->dev, "set lane %d to HS SGMII mode\n",
				lane->id);
			fw_param = COMPHY_FW_NET(fw_mode, lane->port,
						 COMPHY_FW_SPEED_3_125G);
			अवरोध;
		शेष:
			dev_err(lane->dev, "unsupported PHY submode (%d)\n",
				lane->submode);
			वापस -ENOTSUPP;
		पूर्ण
		अवरोध;
	हाल PHY_MODE_PCIE:
		dev_dbg(lane->dev, "set lane %d to PCIe mode\n", lane->id);
		fw_param = COMPHY_FW_PCIE(fw_mode, lane->port,
					  COMPHY_FW_SPEED_5G,
					  phy->attrs.bus_width);
		अवरोध;
	शेष:
		dev_err(lane->dev, "unsupported PHY mode (%d)\n", lane->mode);
		वापस -ENOTSUPP;
	पूर्ण

	ret = mvebu_a3700_comphy_smc(COMPHY_SIP_POWER_ON, lane->id, fw_param);
	अगर (ret == -EOPNOTSUPP)
		dev_err(lane->dev,
			"unsupported SMC call, try updating your firmware\n");

	वापस ret;
पूर्ण

अटल पूर्णांक mvebu_a3700_comphy_घातer_off(काष्ठा phy *phy)
अणु
	काष्ठा mvebu_a3700_comphy_lane *lane = phy_get_drvdata(phy);

	वापस mvebu_a3700_comphy_smc(COMPHY_SIP_POWER_OFF, lane->id, 0);
पूर्ण

अटल स्थिर काष्ठा phy_ops mvebu_a3700_comphy_ops = अणु
	.घातer_on	= mvebu_a3700_comphy_घातer_on,
	.घातer_off	= mvebu_a3700_comphy_घातer_off,
	.set_mode	= mvebu_a3700_comphy_set_mode,
	.owner		= THIS_MODULE,
पूर्ण;

अटल काष्ठा phy *mvebu_a3700_comphy_xlate(काष्ठा device *dev,
					    काष्ठा of_phandle_args *args)
अणु
	काष्ठा mvebu_a3700_comphy_lane *lane;
	काष्ठा phy *phy;

	अगर (WARN_ON(args->args[0] >= MVEBU_A3700_COMPHY_PORTS))
		वापस ERR_PTR(-EINVAL);

	phy = of_phy_simple_xlate(dev, args);
	अगर (IS_ERR(phy))
		वापस phy;

	lane = phy_get_drvdata(phy);
	lane->port = args->args[0];

	वापस phy;
पूर्ण

अटल पूर्णांक mvebu_a3700_comphy_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा phy_provider *provider;
	काष्ठा device_node *child;

	क्रम_each_available_child_of_node(pdev->dev.of_node, child) अणु
		काष्ठा mvebu_a3700_comphy_lane *lane;
		काष्ठा phy *phy;
		पूर्णांक ret;
		u32 lane_id;

		ret = of_property_पढ़ो_u32(child, "reg", &lane_id);
		अगर (ret < 0) अणु
			dev_err(&pdev->dev, "missing 'reg' property (%d)\n",
				ret);
			जारी;
		पूर्ण

		अगर (lane_id >= MVEBU_A3700_COMPHY_LANES) अणु
			dev_err(&pdev->dev, "invalid 'reg' property\n");
			जारी;
		पूर्ण

		lane = devm_kzalloc(&pdev->dev, माप(*lane), GFP_KERNEL);
		अगर (!lane) अणु
			of_node_put(child);
			वापस -ENOMEM;
		पूर्ण

		phy = devm_phy_create(&pdev->dev, child,
				      &mvebu_a3700_comphy_ops);
		अगर (IS_ERR(phy)) अणु
			of_node_put(child);
			वापस PTR_ERR(phy);
		पूर्ण

		lane->dev = &pdev->dev;
		lane->mode = PHY_MODE_INVALID;
		lane->submode = PHY_INTERFACE_MODE_NA;
		lane->id = lane_id;
		lane->port = -1;
		phy_set_drvdata(phy, lane);
	पूर्ण

	provider = devm_of_phy_provider_रेजिस्टर(&pdev->dev,
						 mvebu_a3700_comphy_xlate);
	वापस PTR_ERR_OR_ZERO(provider);
पूर्ण

अटल स्थिर काष्ठा of_device_id mvebu_a3700_comphy_of_match_table[] = अणु
	अणु .compatible = "marvell,comphy-a3700" पूर्ण,
	अणु पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, mvebu_a3700_comphy_of_match_table);

अटल काष्ठा platक्रमm_driver mvebu_a3700_comphy_driver = अणु
	.probe	= mvebu_a3700_comphy_probe,
	.driver	= अणु
		.name = "mvebu-a3700-comphy",
		.of_match_table = mvebu_a3700_comphy_of_match_table,
	पूर्ण,
पूर्ण;
module_platक्रमm_driver(mvebu_a3700_comphy_driver);

MODULE_AUTHOR("Miquथउl Raynal <miquel.raynal@bootlin.com>");
MODULE_DESCRIPTION("Common PHY driver for A3700");
MODULE_LICENSE("GPL v2");
