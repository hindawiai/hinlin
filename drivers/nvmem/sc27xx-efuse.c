<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
// Copyright (C) 2018 Spपढ़ोtrum Communications Inc.

#समावेश <linux/hwspinlock.h>
#समावेश <linux/module.h>
#समावेश <linux/of.h>
#समावेश <linux/of_device.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/regmap.h>
#समावेश <linux/nvmem-provider.h>

/* PMIC global रेजिस्टरs definition */
#घोषणा SC27XX_MODULE_EN		0xc08
#घोषणा SC2730_MODULE_EN		0x1808
#घोषणा SC27XX_EFUSE_EN			BIT(6)

/* Efuse controller रेजिस्टरs definition */
#घोषणा SC27XX_EFUSE_GLB_CTRL		0x0
#घोषणा SC27XX_EFUSE_DATA_RD		0x4
#घोषणा SC27XX_EFUSE_DATA_WR		0x8
#घोषणा SC27XX_EFUSE_BLOCK_INDEX	0xc
#घोषणा SC27XX_EFUSE_MODE_CTRL		0x10
#घोषणा SC27XX_EFUSE_STATUS		0x14
#घोषणा SC27XX_EFUSE_WR_TIMING_CTRL	0x20
#घोषणा SC27XX_EFUSE_RD_TIMING_CTRL	0x24
#घोषणा SC27XX_EFUSE_EFUSE_DEB_CTRL	0x28

/* Mask definition क्रम SC27XX_EFUSE_BLOCK_INDEX रेजिस्टर */
#घोषणा SC27XX_EFUSE_BLOCK_MASK		GENMASK(4, 0)

/* Bits definitions क्रम SC27XX_EFUSE_MODE_CTRL रेजिस्टर */
#घोषणा SC27XX_EFUSE_PG_START		BIT(0)
#घोषणा SC27XX_EFUSE_RD_START		BIT(1)
#घोषणा SC27XX_EFUSE_CLR_RDDONE		BIT(2)

/* Bits definitions क्रम SC27XX_EFUSE_STATUS रेजिस्टर */
#घोषणा SC27XX_EFUSE_PGM_BUSY		BIT(0)
#घोषणा SC27XX_EFUSE_READ_BUSY		BIT(1)
#घोषणा SC27XX_EFUSE_STANDBY		BIT(2)
#घोषणा SC27XX_EFUSE_GLOBAL_PROT	BIT(3)
#घोषणा SC27XX_EFUSE_RD_DONE		BIT(4)

/* Block number and block width (bytes) definitions */
#घोषणा SC27XX_EFUSE_BLOCK_MAX		32
#घोषणा SC27XX_EFUSE_BLOCK_WIDTH	2

/* Timeout (ms) क्रम the trylock of hardware spinlocks */
#घोषणा SC27XX_EFUSE_HWLOCK_TIMEOUT	5000

/* Timeout (us) of polling the status */
#घोषणा SC27XX_EFUSE_POLL_TIMEOUT	3000000
#घोषणा SC27XX_EFUSE_POLL_DELAY_US	10000

/*
 * Since dअगरferent PMICs of SC27xx series can have dअगरferent
 * address , we should save address in the device data काष्ठाure.
 */
काष्ठा sc27xx_efuse_variant_data अणु
	u32 module_en;
पूर्ण;

काष्ठा sc27xx_efuse अणु
	काष्ठा device *dev;
	काष्ठा regmap *regmap;
	काष्ठा hwspinlock *hwlock;
	काष्ठा mutex mutex;
	u32 base;
	स्थिर काष्ठा sc27xx_efuse_variant_data *var_data;
पूर्ण;

अटल स्थिर काष्ठा sc27xx_efuse_variant_data sc2731_edata = अणु
	.module_en = SC27XX_MODULE_EN,
पूर्ण;

अटल स्थिर काष्ठा sc27xx_efuse_variant_data sc2730_edata = अणु
	.module_en = SC2730_MODULE_EN,
पूर्ण;

/*
 * On Spपढ़ोtrum platक्रमm, we have multi-subप्रणालीs will access the unique
 * efuse controller, so we need one hardware spinlock to synchronize between
 * the multiple subप्रणालीs.
 */
अटल पूर्णांक sc27xx_efuse_lock(काष्ठा sc27xx_efuse *efuse)
अणु
	पूर्णांक ret;

	mutex_lock(&efuse->mutex);

	ret = hwspin_lock_समयout_raw(efuse->hwlock,
				      SC27XX_EFUSE_HWLOCK_TIMEOUT);
	अगर (ret) अणु
		dev_err(efuse->dev, "timeout to get the hwspinlock\n");
		mutex_unlock(&efuse->mutex);
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम sc27xx_efuse_unlock(काष्ठा sc27xx_efuse *efuse)
अणु
	hwspin_unlock_raw(efuse->hwlock);
	mutex_unlock(&efuse->mutex);
पूर्ण

अटल पूर्णांक sc27xx_efuse_poll_status(काष्ठा sc27xx_efuse *efuse, u32 bits)
अणु
	पूर्णांक ret;
	u32 val;

	ret = regmap_पढ़ो_poll_समयout(efuse->regmap,
				       efuse->base + SC27XX_EFUSE_STATUS,
				       val, (val & bits),
				       SC27XX_EFUSE_POLL_DELAY_US,
				       SC27XX_EFUSE_POLL_TIMEOUT);
	अगर (ret) अणु
		dev_err(efuse->dev, "timeout to update the efuse status\n");
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक sc27xx_efuse_पढ़ो(व्योम *context, u32 offset, व्योम *val, माप_प्रकार bytes)
अणु
	काष्ठा sc27xx_efuse *efuse = context;
	u32 buf, blk_index = offset / SC27XX_EFUSE_BLOCK_WIDTH;
	u32 blk_offset = (offset % SC27XX_EFUSE_BLOCK_WIDTH) * BITS_PER_BYTE;
	पूर्णांक ret;

	अगर (blk_index > SC27XX_EFUSE_BLOCK_MAX ||
	    bytes > SC27XX_EFUSE_BLOCK_WIDTH)
		वापस -EINVAL;

	ret = sc27xx_efuse_lock(efuse);
	अगर (ret)
		वापस ret;

	/* Enable the efuse controller. */
	ret = regmap_update_bits(efuse->regmap, efuse->var_data->module_en,
				 SC27XX_EFUSE_EN, SC27XX_EFUSE_EN);
	अगर (ret)
		जाओ unlock_efuse;

	/*
	 * Beक्रमe पढ़ोing, we should ensure the efuse controller is in
	 * standby state.
	 */
	ret = sc27xx_efuse_poll_status(efuse, SC27XX_EFUSE_STANDBY);
	अगर (ret)
		जाओ disable_efuse;

	/* Set the block address to be पढ़ो. */
	ret = regmap_ग_लिखो(efuse->regmap,
			   efuse->base + SC27XX_EFUSE_BLOCK_INDEX,
			   blk_index & SC27XX_EFUSE_BLOCK_MASK);
	अगर (ret)
		जाओ disable_efuse;

	/* Start पढ़ोing process from efuse memory. */
	ret = regmap_update_bits(efuse->regmap,
				 efuse->base + SC27XX_EFUSE_MODE_CTRL,
				 SC27XX_EFUSE_RD_START,
				 SC27XX_EFUSE_RD_START);
	अगर (ret)
		जाओ disable_efuse;

	/*
	 * Polling the पढ़ो करोne status to make sure the पढ़ोing process
	 * is completed, that means the data can be पढ़ो out now.
	 */
	ret = sc27xx_efuse_poll_status(efuse, SC27XX_EFUSE_RD_DONE);
	अगर (ret)
		जाओ disable_efuse;

	/* Read data from efuse memory. */
	ret = regmap_पढ़ो(efuse->regmap, efuse->base + SC27XX_EFUSE_DATA_RD,
			  &buf);
	अगर (ret)
		जाओ disable_efuse;

	/* Clear the पढ़ो करोne flag. */
	ret = regmap_update_bits(efuse->regmap,
				 efuse->base + SC27XX_EFUSE_MODE_CTRL,
				 SC27XX_EFUSE_CLR_RDDONE,
				 SC27XX_EFUSE_CLR_RDDONE);

disable_efuse:
	/* Disable the efuse controller after पढ़ोing. */
	regmap_update_bits(efuse->regmap, efuse->var_data->module_en, SC27XX_EFUSE_EN, 0);
unlock_efuse:
	sc27xx_efuse_unlock(efuse);

	अगर (!ret) अणु
		buf >>= blk_offset;
		स_नकल(val, &buf, bytes);
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक sc27xx_efuse_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device_node *np = pdev->dev.of_node;
	काष्ठा nvmem_config econfig = अणु पूर्ण;
	काष्ठा nvmem_device *nvmem;
	काष्ठा sc27xx_efuse *efuse;
	पूर्णांक ret;

	efuse = devm_kzalloc(&pdev->dev, माप(*efuse), GFP_KERNEL);
	अगर (!efuse)
		वापस -ENOMEM;

	efuse->regmap = dev_get_regmap(pdev->dev.parent, शून्य);
	अगर (!efuse->regmap) अणु
		dev_err(&pdev->dev, "failed to get efuse regmap\n");
		वापस -ENODEV;
	पूर्ण

	ret = of_property_पढ़ो_u32(np, "reg", &efuse->base);
	अगर (ret) अणु
		dev_err(&pdev->dev, "failed to get efuse base address\n");
		वापस ret;
	पूर्ण

	ret = of_hwspin_lock_get_id(np, 0);
	अगर (ret < 0) अणु
		dev_err(&pdev->dev, "failed to get hwspinlock id\n");
		वापस ret;
	पूर्ण

	efuse->hwlock = devm_hwspin_lock_request_specअगरic(&pdev->dev, ret);
	अगर (!efuse->hwlock) अणु
		dev_err(&pdev->dev, "failed to request hwspinlock\n");
		वापस -ENXIO;
	पूर्ण

	mutex_init(&efuse->mutex);
	efuse->dev = &pdev->dev;
	efuse->var_data = of_device_get_match_data(&pdev->dev);

	econfig.stride = 1;
	econfig.word_size = 1;
	econfig.पढ़ो_only = true;
	econfig.name = "sc27xx-efuse";
	econfig.size = SC27XX_EFUSE_BLOCK_MAX * SC27XX_EFUSE_BLOCK_WIDTH;
	econfig.reg_पढ़ो = sc27xx_efuse_पढ़ो;
	econfig.priv = efuse;
	econfig.dev = &pdev->dev;
	nvmem = devm_nvmem_रेजिस्टर(&pdev->dev, &econfig);
	अगर (IS_ERR(nvmem)) अणु
		dev_err(&pdev->dev, "failed to register nvmem config\n");
		वापस PTR_ERR(nvmem);
	पूर्ण

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id sc27xx_efuse_of_match[] = अणु
	अणु .compatible = "sprd,sc2731-efuse", .data = &sc2731_edataपूर्ण,
	अणु .compatible = "sprd,sc2730-efuse", .data = &sc2730_edataपूर्ण,
	अणु पूर्ण
पूर्ण;

अटल काष्ठा platक्रमm_driver sc27xx_efuse_driver = अणु
	.probe = sc27xx_efuse_probe,
	.driver = अणु
		.name = "sc27xx-efuse",
		.of_match_table = sc27xx_efuse_of_match,
	पूर्ण,
पूर्ण;

module_platक्रमm_driver(sc27xx_efuse_driver);

MODULE_AUTHOR("Freeman Liu <freeman.liu@spreadtrum.com>");
MODULE_DESCRIPTION("Spreadtrum SC27xx efuse driver");
MODULE_LICENSE("GPL v2");
