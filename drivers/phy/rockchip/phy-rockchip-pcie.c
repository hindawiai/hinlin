<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Rockchip PCIe PHY driver
 *
 * Copyright (C) 2016 Shawn Lin <shawn.lin@rock-chips.com>
 * Copyright (C) 2016 ROCKCHIP, Inc.
 */

#समावेश <linux/clk.h>
#समावेश <linux/delay.h>
#समावेश <linux/पन.स>
#समावेश <linux/mfd/syscon.h>
#समावेश <linux/module.h>
#समावेश <linux/of.h>
#समावेश <linux/of_address.h>
#समावेश <linux/of_platक्रमm.h>
#समावेश <linux/phy/phy.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/regmap.h>
#समावेश <linux/reset.h>

/*
 * The higher 16-bit of this रेजिस्टर is used क्रम ग_लिखो protection
 * only अगर BIT(x + 16) set to 1 the BIT(x) can be written.
 */
#घोषणा HIWORD_UPDATE(val, mask, shअगरt) \
		((val) << (shअगरt) | (mask) << ((shअगरt) + 16))

#घोषणा PHY_MAX_LANE_NUM      4
#घोषणा PHY_CFG_DATA_SHIFT    7
#घोषणा PHY_CFG_ADDR_SHIFT    1
#घोषणा PHY_CFG_DATA_MASK     0xf
#घोषणा PHY_CFG_ADDR_MASK     0x3f
#घोषणा PHY_CFG_RD_MASK       0x3ff
#घोषणा PHY_CFG_WR_ENABLE     1
#घोषणा PHY_CFG_WR_DISABLE    1
#घोषणा PHY_CFG_WR_SHIFT      0
#घोषणा PHY_CFG_WR_MASK       1
#घोषणा PHY_CFG_PLL_LOCK      0x10
#घोषणा PHY_CFG_CLK_TEST      0x10
#घोषणा PHY_CFG_CLK_SCC       0x12
#घोषणा PHY_CFG_SEPE_RATE     BIT(3)
#घोषणा PHY_CFG_PLL_100M      BIT(3)
#घोषणा PHY_PLL_LOCKED        BIT(9)
#घोषणा PHY_PLL_OUTPUT        BIT(10)
#घोषणा PHY_LANE_A_STATUS     0x30
#घोषणा PHY_LANE_B_STATUS     0x31
#घोषणा PHY_LANE_C_STATUS     0x32
#घोषणा PHY_LANE_D_STATUS     0x33
#घोषणा PHY_LANE_RX_DET_SHIFT 11
#घोषणा PHY_LANE_RX_DET_TH    0x1
#घोषणा PHY_LANE_IDLE_OFF     0x1
#घोषणा PHY_LANE_IDLE_MASK    0x1
#घोषणा PHY_LANE_IDLE_A_SHIFT 3
#घोषणा PHY_LANE_IDLE_B_SHIFT 4
#घोषणा PHY_LANE_IDLE_C_SHIFT 5
#घोषणा PHY_LANE_IDLE_D_SHIFT 6

काष्ठा rockchip_pcie_data अणु
	अचिन्हित पूर्णांक pcie_conf;
	अचिन्हित पूर्णांक pcie_status;
	अचिन्हित पूर्णांक pcie_laneoff;
पूर्ण;

काष्ठा rockchip_pcie_phy अणु
	काष्ठा rockchip_pcie_data *phy_data;
	काष्ठा regmap *reg_base;
	काष्ठा phy_pcie_instance अणु
		काष्ठा phy *phy;
		u32 index;
	पूर्ण phys[PHY_MAX_LANE_NUM];
	काष्ठा mutex pcie_mutex;
	काष्ठा reset_control *phy_rst;
	काष्ठा clk *clk_pciephy_ref;
	पूर्णांक pwr_cnt;
	पूर्णांक init_cnt;
पूर्ण;

अटल काष्ठा rockchip_pcie_phy *to_pcie_phy(काष्ठा phy_pcie_instance *inst)
अणु
	वापस container_of(inst, काष्ठा rockchip_pcie_phy,
					phys[inst->index]);
पूर्ण

अटल काष्ठा phy *rockchip_pcie_phy_of_xlate(काष्ठा device *dev,
					      काष्ठा of_phandle_args *args)
अणु
	काष्ठा rockchip_pcie_phy *rk_phy = dev_get_drvdata(dev);

	अगर (args->args_count == 0)
		वापस rk_phy->phys[0].phy;

	अगर (WARN_ON(args->args[0] >= PHY_MAX_LANE_NUM))
		वापस ERR_PTR(-ENODEV);

	वापस rk_phy->phys[args->args[0]].phy;
पूर्ण


अटल अंतरभूत व्योम phy_wr_cfg(काष्ठा rockchip_pcie_phy *rk_phy,
			      u32 addr, u32 data)
अणु
	regmap_ग_लिखो(rk_phy->reg_base, rk_phy->phy_data->pcie_conf,
		     HIWORD_UPDATE(data,
				   PHY_CFG_DATA_MASK,
				   PHY_CFG_DATA_SHIFT) |
		     HIWORD_UPDATE(addr,
				   PHY_CFG_ADDR_MASK,
				   PHY_CFG_ADDR_SHIFT));
	udelay(1);
	regmap_ग_लिखो(rk_phy->reg_base, rk_phy->phy_data->pcie_conf,
		     HIWORD_UPDATE(PHY_CFG_WR_ENABLE,
				   PHY_CFG_WR_MASK,
				   PHY_CFG_WR_SHIFT));
	udelay(1);
	regmap_ग_लिखो(rk_phy->reg_base, rk_phy->phy_data->pcie_conf,
		     HIWORD_UPDATE(PHY_CFG_WR_DISABLE,
				   PHY_CFG_WR_MASK,
				   PHY_CFG_WR_SHIFT));
पूर्ण

अटल अंतरभूत u32 phy_rd_cfg(काष्ठा rockchip_pcie_phy *rk_phy,
			     u32 addr)
अणु
	u32 val;

	regmap_ग_लिखो(rk_phy->reg_base, rk_phy->phy_data->pcie_conf,
		     HIWORD_UPDATE(addr,
				   PHY_CFG_RD_MASK,
				   PHY_CFG_ADDR_SHIFT));
	regmap_पढ़ो(rk_phy->reg_base,
		    rk_phy->phy_data->pcie_status,
		    &val);
	वापस val;
पूर्ण

अटल पूर्णांक rockchip_pcie_phy_घातer_off(काष्ठा phy *phy)
अणु
	काष्ठा phy_pcie_instance *inst = phy_get_drvdata(phy);
	काष्ठा rockchip_pcie_phy *rk_phy = to_pcie_phy(inst);
	पूर्णांक err = 0;

	mutex_lock(&rk_phy->pcie_mutex);

	regmap_ग_लिखो(rk_phy->reg_base,
		     rk_phy->phy_data->pcie_laneoff,
		     HIWORD_UPDATE(PHY_LANE_IDLE_OFF,
				   PHY_LANE_IDLE_MASK,
				   PHY_LANE_IDLE_A_SHIFT + inst->index));

	अगर (--rk_phy->pwr_cnt)
		जाओ err_out;

	err = reset_control_निश्चित(rk_phy->phy_rst);
	अगर (err) अणु
		dev_err(&phy->dev, "assert phy_rst err %d\n", err);
		जाओ err_restore;
	पूर्ण

err_out:
	mutex_unlock(&rk_phy->pcie_mutex);
	वापस 0;

err_restore:
	rk_phy->pwr_cnt++;
	regmap_ग_लिखो(rk_phy->reg_base,
		     rk_phy->phy_data->pcie_laneoff,
		     HIWORD_UPDATE(!PHY_LANE_IDLE_OFF,
				   PHY_LANE_IDLE_MASK,
				   PHY_LANE_IDLE_A_SHIFT + inst->index));
	mutex_unlock(&rk_phy->pcie_mutex);
	वापस err;
पूर्ण

अटल पूर्णांक rockchip_pcie_phy_घातer_on(काष्ठा phy *phy)
अणु
	काष्ठा phy_pcie_instance *inst = phy_get_drvdata(phy);
	काष्ठा rockchip_pcie_phy *rk_phy = to_pcie_phy(inst);
	पूर्णांक err = 0;
	u32 status;
	अचिन्हित दीर्घ समयout;

	mutex_lock(&rk_phy->pcie_mutex);

	अगर (rk_phy->pwr_cnt++)
		जाओ err_out;

	err = reset_control_deनिश्चित(rk_phy->phy_rst);
	अगर (err) अणु
		dev_err(&phy->dev, "deassert phy_rst err %d\n", err);
		जाओ err_pwr_cnt;
	पूर्ण

	regmap_ग_लिखो(rk_phy->reg_base, rk_phy->phy_data->pcie_conf,
		     HIWORD_UPDATE(PHY_CFG_PLL_LOCK,
				   PHY_CFG_ADDR_MASK,
				   PHY_CFG_ADDR_SHIFT));

	regmap_ग_लिखो(rk_phy->reg_base,
		     rk_phy->phy_data->pcie_laneoff,
		     HIWORD_UPDATE(!PHY_LANE_IDLE_OFF,
				   PHY_LANE_IDLE_MASK,
				   PHY_LANE_IDLE_A_SHIFT + inst->index));

	/*
	 * No करोcumented समयout value क्रम phy operation below,
	 * so we make it large enough here. And we use loop-अवरोध
	 * method which should not be harmful.
	 */
	समयout = jअगरfies + msecs_to_jअगरfies(1000);

	err = -EINVAL;
	जबतक (समय_beक्रमe(jअगरfies, समयout)) अणु
		regmap_पढ़ो(rk_phy->reg_base,
			    rk_phy->phy_data->pcie_status,
			    &status);
		अगर (status & PHY_PLL_LOCKED) अणु
			dev_dbg(&phy->dev, "pll locked!\n");
			err = 0;
			अवरोध;
		पूर्ण
		msleep(20);
	पूर्ण

	अगर (err) अणु
		dev_err(&phy->dev, "pll lock timeout!\n");
		जाओ err_pll_lock;
	पूर्ण

	phy_wr_cfg(rk_phy, PHY_CFG_CLK_TEST, PHY_CFG_SEPE_RATE);
	phy_wr_cfg(rk_phy, PHY_CFG_CLK_SCC, PHY_CFG_PLL_100M);

	err = -ETIMEDOUT;
	जबतक (समय_beक्रमe(jअगरfies, समयout)) अणु
		regmap_पढ़ो(rk_phy->reg_base,
			    rk_phy->phy_data->pcie_status,
			    &status);
		अगर (!(status & PHY_PLL_OUTPUT)) अणु
			dev_dbg(&phy->dev, "pll output enable done!\n");
			err = 0;
			अवरोध;
		पूर्ण
		msleep(20);
	पूर्ण

	अगर (err) अणु
		dev_err(&phy->dev, "pll output enable timeout!\n");
		जाओ err_pll_lock;
	पूर्ण

	regmap_ग_लिखो(rk_phy->reg_base, rk_phy->phy_data->pcie_conf,
		     HIWORD_UPDATE(PHY_CFG_PLL_LOCK,
				   PHY_CFG_ADDR_MASK,
				   PHY_CFG_ADDR_SHIFT));
	err = -EINVAL;
	जबतक (समय_beक्रमe(jअगरfies, समयout)) अणु
		regmap_पढ़ो(rk_phy->reg_base,
			    rk_phy->phy_data->pcie_status,
			    &status);
		अगर (status & PHY_PLL_LOCKED) अणु
			dev_dbg(&phy->dev, "pll relocked!\n");
			err = 0;
			अवरोध;
		पूर्ण
		msleep(20);
	पूर्ण

	अगर (err) अणु
		dev_err(&phy->dev, "pll relock timeout!\n");
		जाओ err_pll_lock;
	पूर्ण

err_out:
	mutex_unlock(&rk_phy->pcie_mutex);
	वापस 0;

err_pll_lock:
	reset_control_निश्चित(rk_phy->phy_rst);
err_pwr_cnt:
	rk_phy->pwr_cnt--;
	mutex_unlock(&rk_phy->pcie_mutex);
	वापस err;
पूर्ण

अटल पूर्णांक rockchip_pcie_phy_init(काष्ठा phy *phy)
अणु
	काष्ठा phy_pcie_instance *inst = phy_get_drvdata(phy);
	काष्ठा rockchip_pcie_phy *rk_phy = to_pcie_phy(inst);
	पूर्णांक err = 0;

	mutex_lock(&rk_phy->pcie_mutex);

	अगर (rk_phy->init_cnt++)
		जाओ err_out;

	err = clk_prepare_enable(rk_phy->clk_pciephy_ref);
	अगर (err) अणु
		dev_err(&phy->dev, "Fail to enable pcie ref clock.\n");
		जाओ err_refclk;
	पूर्ण

	err = reset_control_निश्चित(rk_phy->phy_rst);
	अगर (err) अणु
		dev_err(&phy->dev, "assert phy_rst err %d\n", err);
		जाओ err_reset;
	पूर्ण

err_out:
	mutex_unlock(&rk_phy->pcie_mutex);
	वापस 0;

err_reset:

	clk_disable_unprepare(rk_phy->clk_pciephy_ref);
err_refclk:
	rk_phy->init_cnt--;
	mutex_unlock(&rk_phy->pcie_mutex);
	वापस err;
पूर्ण

अटल पूर्णांक rockchip_pcie_phy_निकास(काष्ठा phy *phy)
अणु
	काष्ठा phy_pcie_instance *inst = phy_get_drvdata(phy);
	काष्ठा rockchip_pcie_phy *rk_phy = to_pcie_phy(inst);

	mutex_lock(&rk_phy->pcie_mutex);

	अगर (--rk_phy->init_cnt)
		जाओ err_init_cnt;

	clk_disable_unprepare(rk_phy->clk_pciephy_ref);

err_init_cnt:
	mutex_unlock(&rk_phy->pcie_mutex);
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा phy_ops ops = अणु
	.init		= rockchip_pcie_phy_init,
	.निकास		= rockchip_pcie_phy_निकास,
	.घातer_on	= rockchip_pcie_phy_घातer_on,
	.घातer_off	= rockchip_pcie_phy_घातer_off,
	.owner		= THIS_MODULE,
पूर्ण;

अटल स्थिर काष्ठा rockchip_pcie_data rk3399_pcie_data = अणु
	.pcie_conf = 0xe220,
	.pcie_status = 0xe2a4,
	.pcie_laneoff = 0xe214,
पूर्ण;

अटल स्थिर काष्ठा of_device_id rockchip_pcie_phy_dt_ids[] = अणु
	अणु
		.compatible = "rockchip,rk3399-pcie-phy",
		.data = &rk3399_pcie_data,
	पूर्ण,
	अणुपूर्ण
पूर्ण;

MODULE_DEVICE_TABLE(of, rockchip_pcie_phy_dt_ids);

अटल पूर्णांक rockchip_pcie_phy_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device *dev = &pdev->dev;
	काष्ठा rockchip_pcie_phy *rk_phy;
	काष्ठा phy_provider *phy_provider;
	काष्ठा regmap *grf;
	स्थिर काष्ठा of_device_id *of_id;
	पूर्णांक i;
	u32 phy_num;

	grf = syscon_node_to_regmap(dev->parent->of_node);
	अगर (IS_ERR(grf)) अणु
		dev_err(dev, "Cannot find GRF syscon\n");
		वापस PTR_ERR(grf);
	पूर्ण

	rk_phy = devm_kzalloc(dev, माप(*rk_phy), GFP_KERNEL);
	अगर (!rk_phy)
		वापस -ENOMEM;

	of_id = of_match_device(rockchip_pcie_phy_dt_ids, &pdev->dev);
	अगर (!of_id)
		वापस -EINVAL;

	rk_phy->phy_data = (काष्ठा rockchip_pcie_data *)of_id->data;
	rk_phy->reg_base = grf;

	mutex_init(&rk_phy->pcie_mutex);

	rk_phy->phy_rst = devm_reset_control_get(dev, "phy");
	अगर (IS_ERR(rk_phy->phy_rst)) अणु
		अगर (PTR_ERR(rk_phy->phy_rst) != -EPROBE_DEFER)
			dev_err(dev,
				"missing phy property for reset controller\n");
		वापस PTR_ERR(rk_phy->phy_rst);
	पूर्ण

	rk_phy->clk_pciephy_ref = devm_clk_get(dev, "refclk");
	अगर (IS_ERR(rk_phy->clk_pciephy_ref)) अणु
		dev_err(dev, "refclk not found.\n");
		वापस PTR_ERR(rk_phy->clk_pciephy_ref);
	पूर्ण

	/* parse #phy-cells to see अगर it's legacy PHY model */
	अगर (of_property_पढ़ो_u32(dev->of_node, "#phy-cells", &phy_num))
		वापस -ENOENT;

	phy_num = (phy_num == 0) ? 1 : PHY_MAX_LANE_NUM;
	dev_dbg(dev, "phy number is %d\n", phy_num);

	क्रम (i = 0; i < phy_num; i++) अणु
		rk_phy->phys[i].phy = devm_phy_create(dev, dev->of_node, &ops);
		अगर (IS_ERR(rk_phy->phys[i].phy)) अणु
			dev_err(dev, "failed to create PHY%d\n", i);
			वापस PTR_ERR(rk_phy->phys[i].phy);
		पूर्ण
		rk_phy->phys[i].index = i;
		phy_set_drvdata(rk_phy->phys[i].phy, &rk_phy->phys[i]);
	पूर्ण

	platक्रमm_set_drvdata(pdev, rk_phy);
	phy_provider = devm_of_phy_provider_रेजिस्टर(dev,
					rockchip_pcie_phy_of_xlate);

	वापस PTR_ERR_OR_ZERO(phy_provider);
पूर्ण

अटल काष्ठा platक्रमm_driver rockchip_pcie_driver = अणु
	.probe		= rockchip_pcie_phy_probe,
	.driver		= अणु
		.name	= "rockchip-pcie-phy",
		.of_match_table = rockchip_pcie_phy_dt_ids,
	पूर्ण,
पूर्ण;

module_platक्रमm_driver(rockchip_pcie_driver);

MODULE_AUTHOR("Shawn Lin <shawn.lin@rock-chips.com>");
MODULE_DESCRIPTION("Rockchip PCIe PHY driver");
MODULE_LICENSE("GPL v2");
