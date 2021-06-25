<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (c) 2018 HiSilicon Technologies Co., Ltd.
 */

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

#घोषणा ALL_INT_CLR		0x1ffff

काष्ठा hi3798cv200_priv अणु
	काष्ठा clk *sample_clk;
	काष्ठा clk *drive_clk;
पूर्ण;

अटल अचिन्हित दीर्घ dw_mci_hi3798cv200_caps[] = अणु
	MMC_CAP_CMD23,
	MMC_CAP_CMD23,
	MMC_CAP_CMD23
पूर्ण;

अटल व्योम dw_mci_hi3798cv200_set_ios(काष्ठा dw_mci *host, काष्ठा mmc_ios *ios)
अणु
	काष्ठा hi3798cv200_priv *priv = host->priv;
	u32 val;

	val = mci_पढ़ोl(host, UHS_REG);
	अगर (ios->timing == MMC_TIMING_MMC_DDR52 ||
	    ios->timing == MMC_TIMING_UHS_DDR50)
		val |= SDMMC_UHS_DDR;
	अन्यथा
		val &= ~SDMMC_UHS_DDR;
	mci_ग_लिखोl(host, UHS_REG, val);

	val = mci_पढ़ोl(host, ENABLE_SHIFT);
	अगर (ios->timing == MMC_TIMING_MMC_DDR52)
		val |= SDMMC_ENABLE_PHASE;
	अन्यथा
		val &= ~SDMMC_ENABLE_PHASE;
	mci_ग_लिखोl(host, ENABLE_SHIFT, val);

	val = mci_पढ़ोl(host, DDR_REG);
	अगर (ios->timing == MMC_TIMING_MMC_HS400)
		val |= SDMMC_DDR_HS400;
	अन्यथा
		val &= ~SDMMC_DDR_HS400;
	mci_ग_लिखोl(host, DDR_REG, val);

	अगर (ios->timing == MMC_TIMING_MMC_HS ||
	    ios->timing == MMC_TIMING_LEGACY)
		clk_set_phase(priv->drive_clk, 180);
	अन्यथा अगर (ios->timing == MMC_TIMING_MMC_HS200)
		clk_set_phase(priv->drive_clk, 135);
पूर्ण

अटल पूर्णांक dw_mci_hi3798cv200_execute_tuning(काष्ठा dw_mci_slot *slot,
					     u32 opcode)
अणु
	अटल स्थिर पूर्णांक degrees[] = अणु 0, 45, 90, 135, 180, 225, 270, 315 पूर्ण;
	काष्ठा dw_mci *host = slot->host;
	काष्ठा hi3798cv200_priv *priv = host->priv;
	पूर्णांक उठाओ_poपूर्णांक = -1, fall_poपूर्णांक = -1;
	पूर्णांक err, prev_err = -1;
	पूर्णांक found = 0;
	पूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(degrees); i++) अणु
		clk_set_phase(priv->sample_clk, degrees[i]);
		mci_ग_लिखोl(host, RINTSTS, ALL_INT_CLR);

		err = mmc_send_tuning(slot->mmc, opcode, शून्य);
		अगर (!err)
			found = 1;

		अगर (i > 0) अणु
			अगर (err && !prev_err)
				fall_poपूर्णांक = i - 1;
			अगर (!err && prev_err)
				उठाओ_poपूर्णांक = i;
		पूर्ण

		अगर (उठाओ_poपूर्णांक != -1 && fall_poपूर्णांक != -1)
			जाओ tuning_out;

		prev_err = err;
		err = 0;
	पूर्ण

tuning_out:
	अगर (found) अणु
		अगर (उठाओ_poपूर्णांक == -1)
			उठाओ_poपूर्णांक = 0;
		अगर (fall_poपूर्णांक == -1)
			fall_poपूर्णांक = ARRAY_SIZE(degrees) - 1;
		अगर (fall_poपूर्णांक < उठाओ_poपूर्णांक) अणु
			अगर ((उठाओ_poपूर्णांक + fall_poपूर्णांक) >
			    (ARRAY_SIZE(degrees) - 1))
				i = fall_poपूर्णांक / 2;
			अन्यथा
				i = (उठाओ_poपूर्णांक + ARRAY_SIZE(degrees) - 1) / 2;
		पूर्ण अन्यथा अणु
			i = (उठाओ_poपूर्णांक + fall_poपूर्णांक) / 2;
		पूर्ण

		clk_set_phase(priv->sample_clk, degrees[i]);
		dev_dbg(host->dev, "Tuning clk_sample[%d, %d], set[%d]\n",
			उठाओ_poपूर्णांक, fall_poपूर्णांक, degrees[i]);
	पूर्ण अन्यथा अणु
		dev_err(host->dev, "No valid clk_sample shift! use default\n");
		err = -EINVAL;
	पूर्ण

	mci_ग_लिखोl(host, RINTSTS, ALL_INT_CLR);
	वापस err;
पूर्ण

अटल पूर्णांक dw_mci_hi3798cv200_init(काष्ठा dw_mci *host)
अणु
	काष्ठा hi3798cv200_priv *priv;
	पूर्णांक ret;

	priv = devm_kzalloc(host->dev, माप(*priv), GFP_KERNEL);
	अगर (!priv)
		वापस -ENOMEM;

	priv->sample_clk = devm_clk_get(host->dev, "ciu-sample");
	अगर (IS_ERR(priv->sample_clk)) अणु
		dev_err(host->dev, "failed to get ciu-sample clock\n");
		वापस PTR_ERR(priv->sample_clk);
	पूर्ण

	priv->drive_clk = devm_clk_get(host->dev, "ciu-drive");
	अगर (IS_ERR(priv->drive_clk)) अणु
		dev_err(host->dev, "failed to get ciu-drive clock\n");
		वापस PTR_ERR(priv->drive_clk);
	पूर्ण

	ret = clk_prepare_enable(priv->sample_clk);
	अगर (ret) अणु
		dev_err(host->dev, "failed to enable ciu-sample clock\n");
		वापस ret;
	पूर्ण

	ret = clk_prepare_enable(priv->drive_clk);
	अगर (ret) अणु
		dev_err(host->dev, "failed to enable ciu-drive clock\n");
		जाओ disable_sample_clk;
	पूर्ण

	host->priv = priv;
	वापस 0;

disable_sample_clk:
	clk_disable_unprepare(priv->sample_clk);
	वापस ret;
पूर्ण

अटल स्थिर काष्ठा dw_mci_drv_data hi3798cv200_data = अणु
	.caps = dw_mci_hi3798cv200_caps,
	.num_caps = ARRAY_SIZE(dw_mci_hi3798cv200_caps),
	.init = dw_mci_hi3798cv200_init,
	.set_ios = dw_mci_hi3798cv200_set_ios,
	.execute_tuning = dw_mci_hi3798cv200_execute_tuning,
पूर्ण;

अटल पूर्णांक dw_mci_hi3798cv200_probe(काष्ठा platक्रमm_device *pdev)
अणु
	वापस dw_mci_pltfm_रेजिस्टर(pdev, &hi3798cv200_data);
पूर्ण

अटल पूर्णांक dw_mci_hi3798cv200_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा dw_mci *host = platक्रमm_get_drvdata(pdev);
	काष्ठा hi3798cv200_priv *priv = host->priv;

	clk_disable_unprepare(priv->drive_clk);
	clk_disable_unprepare(priv->sample_clk);

	वापस dw_mci_pltfm_हटाओ(pdev);
पूर्ण

अटल स्थिर काष्ठा of_device_id dw_mci_hi3798cv200_match[] = अणु
	अणु .compatible = "hisilicon,hi3798cv200-dw-mshc", पूर्ण,
	अणुपूर्ण,
पूर्ण;

MODULE_DEVICE_TABLE(of, dw_mci_hi3798cv200_match);
अटल काष्ठा platक्रमm_driver dw_mci_hi3798cv200_driver = अणु
	.probe = dw_mci_hi3798cv200_probe,
	.हटाओ = dw_mci_hi3798cv200_हटाओ,
	.driver = अणु
		.name = "dwmmc_hi3798cv200",
		.probe_type = PROBE_PREFER_ASYNCHRONOUS,
		.of_match_table = dw_mci_hi3798cv200_match,
	पूर्ण,
पूर्ण;
module_platक्रमm_driver(dw_mci_hi3798cv200_driver);

MODULE_DESCRIPTION("HiSilicon Hi3798CV200 Specific DW-MSHC Driver Extension");
MODULE_LICENSE("GPL v2");
MODULE_ALIAS("platform:dwmmc_hi3798cv200");
