<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Copyright (c) 2013 Linaro Ltd.
 * Copyright (c) 2013 HiSilicon Limited.
 */

#समावेश <linux/bitops.h>
#समावेश <linux/bitfield.h>
#समावेश <linux/clk.h>
#समावेश <linux/mfd/syscon.h>
#समावेश <linux/mmc/host.h>
#समावेश <linux/module.h>
#समावेश <linux/of_address.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/pm_runसमय.स>
#समावेश <linux/regmap.h>
#समावेश <linux/regulator/consumer.h>

#समावेश "dw_mmc.h"
#समावेश "dw_mmc-pltfm.h"

/*
 * hi6220 sd only support io voltage 1.8v and 3v
 * Also need config AO_SCTRL_SEL18 accordingly
 */
#घोषणा AO_SCTRL_SEL18		BIT(10)
#घोषणा AO_SCTRL_CTRL3		0x40C

#घोषणा DWMMC_SDIO_ID 2

#घोषणा SOC_SCTRL_SCPERCTRL5    (0x314)
#घोषणा SDCARD_IO_SEL18         BIT(2)

#घोषणा SDCARD_RD_THRESHOLD  (512)

#घोषणा GENCLK_DIV (7)

#घोषणा GPIO_CLK_ENABLE                   BIT(16)
#घोषणा GPIO_CLK_DIV_MASK                 GENMASK(11, 8)
#घोषणा GPIO_USE_SAMPLE_DLY_MASK          GENMASK(13, 13)
#घोषणा UHS_REG_EXT_SAMPLE_PHASE_MASK     GENMASK(20, 16)
#घोषणा UHS_REG_EXT_SAMPLE_DRVPHASE_MASK  GENMASK(25, 21)
#घोषणा UHS_REG_EXT_SAMPLE_DLY_MASK       GENMASK(30, 26)

#घोषणा TIMING_MODE     3
#घोषणा TIMING_CFG_NUM 10

#घोषणा NUM_PHASES (40)

#घोषणा ENABLE_SHIFT_MIN_SMPL (4)
#घोषणा ENABLE_SHIFT_MAX_SMPL (12)
#घोषणा USE_DLY_MIN_SMPL (11)
#घोषणा USE_DLY_MAX_SMPL (14)

काष्ठा k3_priv अणु
	पूर्णांक ctrl_id;
	u32 cur_speed;
	काष्ठा regmap	*reg;
पूर्ण;

अटल अचिन्हित दीर्घ dw_mci_hi6220_caps[] = अणु
	MMC_CAP_CMD23,
	MMC_CAP_CMD23,
	0
पूर्ण;

काष्ठा hs_timing अणु
	u32 drv_phase;
	u32 smpl_dly;
	u32 smpl_phase_max;
	u32 smpl_phase_min;
पूर्ण;

अटल काष्ठा hs_timing hs_timing_cfg[TIMING_MODE][TIMING_CFG_NUM] = अणु
	अणु /* reserved */ पूर्ण,
	अणु /* SD */
		अणु7, 0, 15, 15,पूर्ण,  /* 0: LEGACY 400k */
		अणु6, 0,  4,  4,पूर्ण,  /* 1: MMC_HS */
		अणु6, 0,  3,  3,पूर्ण,  /* 2: SD_HS */
		अणु6, 0, 15, 15,पूर्ण,  /* 3: SDR12 */
		अणु6, 0,  2,  2,पूर्ण,  /* 4: SDR25 */
		अणु4, 0, 11,  0,पूर्ण,  /* 5: SDR50 */
		अणु6, 4, 15,  0,पूर्ण,  /* 6: SDR104 */
		अणु0पूर्ण,              /* 7: DDR50 */
		अणु0पूर्ण,              /* 8: DDR52 */
		अणु0पूर्ण,              /* 9: HS200 */
	पूर्ण,
	अणु /* SDIO */
		अणु7, 0, 15, 15,पूर्ण,  /* 0: LEGACY 400k */
		अणु0पूर्ण,              /* 1: MMC_HS */
		अणु6, 0, 15, 15,पूर्ण,  /* 2: SD_HS */
		अणु6, 0, 15, 15,पूर्ण,  /* 3: SDR12 */
		अणु6, 0,  0,  0,पूर्ण,  /* 4: SDR25 */
		अणु4, 0, 12,  0,पूर्ण,  /* 5: SDR50 */
		अणु5, 4, 15,  0,पूर्ण,  /* 6: SDR104 */
		अणु0पूर्ण,              /* 7: DDR50 */
		अणु0पूर्ण,              /* 8: DDR52 */
		अणु0पूर्ण,              /* 9: HS200 */
	पूर्ण
पूर्ण;

अटल व्योम dw_mci_k3_set_ios(काष्ठा dw_mci *host, काष्ठा mmc_ios *ios)
अणु
	पूर्णांक ret;

	ret = clk_set_rate(host->ciu_clk, ios->घड़ी);
	अगर (ret)
		dev_warn(host->dev, "failed to set rate %uHz\n", ios->घड़ी);

	host->bus_hz = clk_get_rate(host->ciu_clk);
पूर्ण

अटल स्थिर काष्ठा dw_mci_drv_data k3_drv_data = अणु
	.set_ios		= dw_mci_k3_set_ios,
पूर्ण;

अटल पूर्णांक dw_mci_hi6220_parse_dt(काष्ठा dw_mci *host)
अणु
	काष्ठा k3_priv *priv;

	priv = devm_kzalloc(host->dev, माप(*priv), GFP_KERNEL);
	अगर (!priv)
		वापस -ENOMEM;

	priv->reg = syscon_regmap_lookup_by_phandle(host->dev->of_node,
					 "hisilicon,peripheral-syscon");
	अगर (IS_ERR(priv->reg))
		priv->reg = शून्य;

	priv->ctrl_id = of_alias_get_id(host->dev->of_node, "mshc");
	अगर (priv->ctrl_id < 0)
		priv->ctrl_id = 0;

	अगर (priv->ctrl_id >= TIMING_MODE)
		वापस -EINVAL;

	host->priv = priv;
	वापस 0;
पूर्ण

अटल पूर्णांक dw_mci_hi6220_चयन_voltage(काष्ठा mmc_host *mmc, काष्ठा mmc_ios *ios)
अणु
	काष्ठा dw_mci_slot *slot = mmc_priv(mmc);
	काष्ठा k3_priv *priv;
	काष्ठा dw_mci *host;
	पूर्णांक min_uv, max_uv;
	पूर्णांक ret;

	host = slot->host;
	priv = host->priv;

	अगर (!priv || !priv->reg)
		वापस 0;

	अगर (ios->संकेत_voltage == MMC_SIGNAL_VOLTAGE_330) अणु
		ret = regmap_update_bits(priv->reg, AO_SCTRL_CTRL3,
					 AO_SCTRL_SEL18, 0);
		min_uv = 3000000;
		max_uv = 3000000;
	पूर्ण अन्यथा अगर (ios->संकेत_voltage == MMC_SIGNAL_VOLTAGE_180) अणु
		ret = regmap_update_bits(priv->reg, AO_SCTRL_CTRL3,
					 AO_SCTRL_SEL18, AO_SCTRL_SEL18);
		min_uv = 1800000;
		max_uv = 1800000;
	पूर्ण अन्यथा अणु
		dev_dbg(host->dev, "voltage not supported\n");
		वापस -EINVAL;
	पूर्ण

	अगर (ret) अणु
		dev_dbg(host->dev, "switch voltage failed\n");
		वापस ret;
	पूर्ण

	अगर (IS_ERR_OR_शून्य(mmc->supply.vqmmc))
		वापस 0;

	ret = regulator_set_voltage(mmc->supply.vqmmc, min_uv, max_uv);
	अगर (ret) अणु
		dev_dbg(host->dev, "Regulator set error %d: %d - %d\n",
				 ret, min_uv, max_uv);
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम dw_mci_hi6220_set_ios(काष्ठा dw_mci *host, काष्ठा mmc_ios *ios)
अणु
	पूर्णांक ret;
	अचिन्हित पूर्णांक घड़ी;

	घड़ी = (ios->घड़ी <= 25000000) ? 25000000 : ios->घड़ी;

	ret = clk_set_rate(host->biu_clk, घड़ी);
	अगर (ret)
		dev_warn(host->dev, "failed to set rate %uHz\n", घड़ी);

	host->bus_hz = clk_get_rate(host->biu_clk);
पूर्ण

अटल पूर्णांक dw_mci_hi6220_execute_tuning(काष्ठा dw_mci_slot *slot, u32 opcode)
अणु
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा dw_mci_drv_data hi6220_data = अणु
	.caps			= dw_mci_hi6220_caps,
	.num_caps		= ARRAY_SIZE(dw_mci_hi6220_caps),
	.चयन_voltage		= dw_mci_hi6220_चयन_voltage,
	.set_ios		= dw_mci_hi6220_set_ios,
	.parse_dt		= dw_mci_hi6220_parse_dt,
	.execute_tuning		= dw_mci_hi6220_execute_tuning,
पूर्ण;

अटल व्योम dw_mci_hs_set_timing(काष्ठा dw_mci *host, पूर्णांक timing,
				     पूर्णांक smpl_phase)
अणु
	u32 drv_phase;
	u32 smpl_dly;
	u32 use_smpl_dly = 0;
	u32 enable_shअगरt = 0;
	u32 reg_value;
	पूर्णांक ctrl_id;
	काष्ठा k3_priv *priv;

	priv = host->priv;
	ctrl_id = priv->ctrl_id;

	drv_phase = hs_timing_cfg[ctrl_id][timing].drv_phase;
	smpl_dly   = hs_timing_cfg[ctrl_id][timing].smpl_dly;
	अगर (smpl_phase == -1)
		smpl_phase = (hs_timing_cfg[ctrl_id][timing].smpl_phase_max +
			     hs_timing_cfg[ctrl_id][timing].smpl_phase_min) / 2;

	चयन (timing) अणु
	हाल MMC_TIMING_UHS_SDR104:
		अगर (smpl_phase >= USE_DLY_MIN_SMPL &&
				smpl_phase <= USE_DLY_MAX_SMPL)
			use_smpl_dly = 1;
		fallthrough;
	हाल MMC_TIMING_UHS_SDR50:
		अगर (smpl_phase >= ENABLE_SHIFT_MIN_SMPL &&
				smpl_phase <= ENABLE_SHIFT_MAX_SMPL)
			enable_shअगरt = 1;
		अवरोध;
	पूर्ण

	mci_ग_लिखोl(host, GPIO, 0x0);
	usleep_range(5, 10);

	reg_value = FIELD_PREP(UHS_REG_EXT_SAMPLE_PHASE_MASK, smpl_phase) |
		    FIELD_PREP(UHS_REG_EXT_SAMPLE_DLY_MASK, smpl_dly) |
		    FIELD_PREP(UHS_REG_EXT_SAMPLE_DRVPHASE_MASK, drv_phase);
	mci_ग_लिखोl(host, UHS_REG_EXT, reg_value);

	mci_ग_लिखोl(host, ENABLE_SHIFT, enable_shअगरt);

	reg_value = FIELD_PREP(GPIO_CLK_DIV_MASK, GENCLK_DIV) |
			     FIELD_PREP(GPIO_USE_SAMPLE_DLY_MASK, use_smpl_dly);
	mci_ग_लिखोl(host, GPIO, (अचिन्हित पूर्णांक)reg_value | GPIO_CLK_ENABLE);

	/* We should delay 1ms रुको क्रम timing setting finished. */
	usleep_range(1000, 2000);
पूर्ण

अटल पूर्णांक dw_mci_hi3660_init(काष्ठा dw_mci *host)
अणु
	mci_ग_लिखोl(host, CDTHRCTL, SDMMC_SET_THLD(SDCARD_RD_THRESHOLD,
		    SDMMC_CARD_RD_THR_EN));

	dw_mci_hs_set_timing(host, MMC_TIMING_LEGACY, -1);
	host->bus_hz /= (GENCLK_DIV + 1);

	वापस 0;
पूर्ण

अटल पूर्णांक dw_mci_set_sel18(काष्ठा dw_mci *host, bool set)
अणु
	पूर्णांक ret;
	अचिन्हित पूर्णांक val;
	काष्ठा k3_priv *priv;

	priv = host->priv;

	val = set ? SDCARD_IO_SEL18 : 0;
	ret = regmap_update_bits(priv->reg, SOC_SCTRL_SCPERCTRL5,
				 SDCARD_IO_SEL18, val);
	अगर (ret) अणु
		dev_err(host->dev, "sel18 %u error\n", val);
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम dw_mci_hi3660_set_ios(काष्ठा dw_mci *host, काष्ठा mmc_ios *ios)
अणु
	पूर्णांक ret;
	अचिन्हित दीर्घ wanted;
	अचिन्हित दीर्घ actual;
	काष्ठा k3_priv *priv = host->priv;

	अगर (!ios->घड़ी || ios->घड़ी == priv->cur_speed)
		वापस;

	wanted = ios->घड़ी * (GENCLK_DIV + 1);
	ret = clk_set_rate(host->ciu_clk, wanted);
	अगर (ret) अणु
		dev_err(host->dev, "failed to set rate %luHz\n", wanted);
		वापस;
	पूर्ण
	actual = clk_get_rate(host->ciu_clk);

	dw_mci_hs_set_timing(host, ios->timing, -1);
	host->bus_hz = actual / (GENCLK_DIV + 1);
	host->current_speed = 0;
	priv->cur_speed = host->bus_hz;
पूर्ण

अटल पूर्णांक dw_mci_get_best_clksmpl(अचिन्हित पूर्णांक sample_flag)
अणु
	पूर्णांक i;
	पूर्णांक पूर्णांकerval;
	अचिन्हित पूर्णांक v;
	अचिन्हित पूर्णांक len;
	अचिन्हित पूर्णांक range_start = 0;
	अचिन्हित पूर्णांक range_length = 0;
	अचिन्हित पूर्णांक middle_range = 0;

	अगर (!sample_flag)
		वापस -EIO;

	अगर (~sample_flag == 0)
		वापस 0;

	i = ffs(sample_flag) - 1;

	/*
	* A घड़ी cycle is भागided पूर्णांकo 32 phases,
	* each of which is represented by a bit,
	* finding the optimal phase.
	*/
	जबतक (i < 32) अणु
		v = ror32(sample_flag, i);
		len = ffs(~v) - 1;

		अगर (len > range_length) अणु
			range_length = len;
			range_start = i;
		पूर्ण

		पूर्णांकerval = ffs(v >> len) - 1;
		अगर (पूर्णांकerval < 0)
			अवरोध;

		i += len + पूर्णांकerval;
	पूर्ण

	middle_range = range_start + range_length / 2;
	अगर (middle_range >= 32)
		middle_range %= 32;

	वापस middle_range;
पूर्ण

अटल पूर्णांक dw_mci_hi3660_execute_tuning(काष्ठा dw_mci_slot *slot, u32 opcode)
अणु
	पूर्णांक i = 0;
	काष्ठा dw_mci *host = slot->host;
	काष्ठा mmc_host *mmc = slot->mmc;
	पूर्णांक smpl_phase = 0;
	u32 tuning_sample_flag = 0;
	पूर्णांक best_clksmpl = 0;

	क्रम (i = 0; i < NUM_PHASES; ++i, ++smpl_phase) अणु
		smpl_phase %= 32;

		mci_ग_लिखोl(host, TMOUT, ~0);
		dw_mci_hs_set_timing(host, mmc->ios.timing, smpl_phase);

		अगर (!mmc_send_tuning(mmc, opcode, शून्य))
			tuning_sample_flag |= (1 << smpl_phase);
		अन्यथा
			tuning_sample_flag &= ~(1 << smpl_phase);
	पूर्ण

	best_clksmpl = dw_mci_get_best_clksmpl(tuning_sample_flag);
	अगर (best_clksmpl < 0) अणु
		dev_err(host->dev, "All phases bad!\n");
		वापस -EIO;
	पूर्ण

	dw_mci_hs_set_timing(host, mmc->ios.timing, best_clksmpl);

	dev_info(host->dev, "tuning ok best_clksmpl %u tuning_sample_flag %x\n",
		 best_clksmpl, tuning_sample_flag);
	वापस 0;
पूर्ण

अटल पूर्णांक dw_mci_hi3660_चयन_voltage(काष्ठा mmc_host *mmc,
					काष्ठा mmc_ios *ios)
अणु
	पूर्णांक ret = 0;
	काष्ठा dw_mci_slot *slot = mmc_priv(mmc);
	काष्ठा k3_priv *priv;
	काष्ठा dw_mci *host;

	host = slot->host;
	priv = host->priv;

	अगर (!priv || !priv->reg)
		वापस 0;

	अगर (priv->ctrl_id == DWMMC_SDIO_ID)
		वापस 0;

	अगर (ios->संकेत_voltage == MMC_SIGNAL_VOLTAGE_330)
		ret = dw_mci_set_sel18(host, 0);
	अन्यथा अगर (ios->संकेत_voltage == MMC_SIGNAL_VOLTAGE_180)
		ret = dw_mci_set_sel18(host, 1);
	अगर (ret)
		वापस ret;

	अगर (!IS_ERR(mmc->supply.vqmmc)) अणु
		ret = mmc_regulator_set_vqmmc(mmc, ios);
		अगर (ret < 0) अणु
			dev_err(host->dev, "Regulator set error %d\n", ret);
			वापस ret;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा dw_mci_drv_data hi3660_data = अणु
	.init = dw_mci_hi3660_init,
	.set_ios = dw_mci_hi3660_set_ios,
	.parse_dt = dw_mci_hi6220_parse_dt,
	.execute_tuning = dw_mci_hi3660_execute_tuning,
	.चयन_voltage  = dw_mci_hi3660_चयन_voltage,
पूर्ण;

अटल स्थिर काष्ठा of_device_id dw_mci_k3_match[] = अणु
	अणु .compatible = "hisilicon,hi3660-dw-mshc", .data = &hi3660_data, पूर्ण,
	अणु .compatible = "hisilicon,hi4511-dw-mshc", .data = &k3_drv_data, पूर्ण,
	अणु .compatible = "hisilicon,hi6220-dw-mshc", .data = &hi6220_data, पूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, dw_mci_k3_match);

अटल पूर्णांक dw_mci_k3_probe(काष्ठा platक्रमm_device *pdev)
अणु
	स्थिर काष्ठा dw_mci_drv_data *drv_data;
	स्थिर काष्ठा of_device_id *match;

	match = of_match_node(dw_mci_k3_match, pdev->dev.of_node);
	drv_data = match->data;

	वापस dw_mci_pltfm_रेजिस्टर(pdev, drv_data);
पूर्ण

अटल स्थिर काष्ठा dev_pm_ops dw_mci_k3_dev_pm_ops = अणु
	SET_SYSTEM_SLEEP_PM_OPS(pm_runसमय_क्रमce_suspend,
				pm_runसमय_क्रमce_resume)
	SET_RUNTIME_PM_OPS(dw_mci_runसमय_suspend,
			   dw_mci_runसमय_resume,
			   शून्य)
पूर्ण;

अटल काष्ठा platक्रमm_driver dw_mci_k3_pltfm_driver = अणु
	.probe		= dw_mci_k3_probe,
	.हटाओ		= dw_mci_pltfm_हटाओ,
	.driver		= अणु
		.name		= "dwmmc_k3",
		.probe_type	= PROBE_PREFER_ASYNCHRONOUS,
		.of_match_table	= dw_mci_k3_match,
		.pm		= &dw_mci_k3_dev_pm_ops,
	पूर्ण,
पूर्ण;

module_platक्रमm_driver(dw_mci_k3_pltfm_driver);

MODULE_DESCRIPTION("K3 Specific DW-MSHC Driver Extension");
MODULE_LICENSE("GPL v2");
MODULE_ALIAS("platform:dwmmc_k3");
