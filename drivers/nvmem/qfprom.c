<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (C) 2015 Srinivas Kandagatla <srinivas.kandagatla@linaro.org>
 */

#समावेश <linux/clk.h>
#समावेश <linux/device.h>
#समावेश <linux/पन.स>
#समावेश <linux/iopoll.h>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/mod_devicetable.h>
#समावेश <linux/nvmem-provider.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/property.h>
#समावेश <linux/regulator/consumer.h>

/* Blow समयr घड़ी frequency in Mhz */
#घोषणा QFPROM_BLOW_TIMER_OFFSET 0x03c

/* Amount of समय required to hold अक्षरge to blow fuse in micro-seconds */
#घोषणा QFPROM_FUSE_BLOW_POLL_US	100
#घोषणा QFPROM_FUSE_BLOW_TIMEOUT_US	1000

#घोषणा QFPROM_BLOW_STATUS_OFFSET	0x048
#घोषणा QFPROM_BLOW_STATUS_BUSY		0x1
#घोषणा QFPROM_BLOW_STATUS_READY	0x0

#घोषणा QFPROM_ACCEL_OFFSET		0x044

#घोषणा QFPROM_VERSION_OFFSET		0x0
#घोषणा QFPROM_MAJOR_VERSION_SHIFT	28
#घोषणा QFPROM_MAJOR_VERSION_MASK	GENMASK(31, QFPROM_MAJOR_VERSION_SHIFT)
#घोषणा QFPROM_MINOR_VERSION_SHIFT	16
#घोषणा QFPROM_MINOR_VERSION_MASK	GENMASK(27, QFPROM_MINOR_VERSION_SHIFT)

अटल bool पढ़ो_raw_data;
module_param(पढ़ो_raw_data, bool, 0644);
MODULE_PARM_DESC(पढ़ो_raw_data, "Read raw instead of corrected data");

/**
 * काष्ठा qfprom_soc_data - config that varies from SoC to SoC.
 *
 * @accel_value:             Should contain qfprom accel value.
 * @qfprom_blow_समयr_value: The समयr value of qfprom when करोing efuse blow.
 * @qfprom_blow_set_freq:    The frequency required to set when we start the
 *                           fuse blowing.
 * @qfprom_blow_uV:          LDO voltage to be set when करोing efuse blow
 */
काष्ठा qfprom_soc_data अणु
	u32 accel_value;
	u32 qfprom_blow_समयr_value;
	u32 qfprom_blow_set_freq;
	पूर्णांक qfprom_blow_uV;
पूर्ण;

/**
 * काष्ठा qfprom_priv - काष्ठाure holding qfprom attributes
 *
 * @qfpraw:       iomapped memory space क्रम qfprom-efuse raw address space.
 * @qfpconf:      iomapped memory space क्रम qfprom-efuse configuration address
 *                space.
 * @qfpcorrected: iomapped memory space क्रम qfprom corrected address space.
 * @qfpsecurity:  iomapped memory space क्रम qfprom security control space.
 * @dev:          qfprom device काष्ठाure.
 * @secclk:       Clock supply.
 * @vcc:          Regulator supply.
 * @soc_data:     Data that क्रम things that varies from SoC to SoC.
 */
काष्ठा qfprom_priv अणु
	व्योम __iomem *qfpraw;
	व्योम __iomem *qfpconf;
	व्योम __iomem *qfpcorrected;
	व्योम __iomem *qfpsecurity;
	काष्ठा device *dev;
	काष्ठा clk *secclk;
	काष्ठा regulator *vcc;
	स्थिर काष्ठा qfprom_soc_data *soc_data;
पूर्ण;

/**
 * काष्ठा qfprom_touched_values - saved values to restore after blowing
 *
 * @clk_rate: The rate the घड़ी was at beक्रमe blowing.
 * @accel_val: The value of the accel reg beक्रमe blowing.
 * @समयr_val: The value of the समयr beक्रमe blowing.
 */
काष्ठा qfprom_touched_values अणु
	अचिन्हित दीर्घ clk_rate;
	u32 accel_val;
	u32 समयr_val;
पूर्ण;

/**
 * काष्ठा qfprom_soc_compatible_data - Data matched against the SoC
 * compatible string.
 *
 * @keepout: Array of keepout regions क्रम this SoC.
 * @nkeepout: Number of elements in the keepout array.
 */
काष्ठा qfprom_soc_compatible_data अणु
	स्थिर काष्ठा nvmem_keepout *keepout;
	अचिन्हित पूर्णांक nkeepout;
पूर्ण;

अटल स्थिर काष्ठा nvmem_keepout sc7180_qfprom_keepout[] = अणु
	अणु.start = 0x128, .end = 0x148पूर्ण,
	अणु.start = 0x220, .end = 0x228पूर्ण
पूर्ण;

अटल स्थिर काष्ठा qfprom_soc_compatible_data sc7180_qfprom = अणु
	.keepout = sc7180_qfprom_keepout,
	.nkeepout = ARRAY_SIZE(sc7180_qfprom_keepout)
पूर्ण;

अटल स्थिर काष्ठा nvmem_keepout sc7280_qfprom_keepout[] = अणु
	अणु.start = 0x128, .end = 0x148पूर्ण,
	अणु.start = 0x238, .end = 0x248पूर्ण
पूर्ण;

अटल स्थिर काष्ठा qfprom_soc_compatible_data sc7280_qfprom = अणु
	.keepout = sc7280_qfprom_keepout,
	.nkeepout = ARRAY_SIZE(sc7280_qfprom_keepout)
पूर्ण;
/**
 * qfprom_disable_fuse_blowing() - Unकरो enabling of fuse blowing.
 * @priv: Our driver data.
 * @old:  The data that was stashed from beक्रमe fuse blowing.
 *
 * Resets the value of the blow समयr, accel रेजिस्टर and the घड़ी
 * and voltage settings.
 *
 * Prपूर्णांकs messages अगर there are errors but करोesn't वापस an error code
 * since there's not much we can करो upon failure.
 */
अटल व्योम qfprom_disable_fuse_blowing(स्थिर काष्ठा qfprom_priv *priv,
					स्थिर काष्ठा qfprom_touched_values *old)
अणु
	पूर्णांक ret;

	/*
	 * This may be a shared rail and may be able to run at a lower rate
	 * when we're not blowing fuses.  At the moment, the regulator framework
	 * applies voltage स्थिरraपूर्णांकs even on disabled rails, so हटाओ our
	 * स्थिरraपूर्णांकs and allow the rail to be adjusted by other users.
	 */
	ret = regulator_set_voltage(priv->vcc, 0, पूर्णांक_उच्च);
	अगर (ret)
		dev_warn(priv->dev, "Failed to set 0 voltage (ignoring)\n");

	ret = regulator_disable(priv->vcc);
	अगर (ret)
		dev_warn(priv->dev, "Failed to disable regulator (ignoring)\n");

	ret = clk_set_rate(priv->secclk, old->clk_rate);
	अगर (ret)
		dev_warn(priv->dev,
			 "Failed to set clock rate for disable (ignoring)\n");

	clk_disable_unprepare(priv->secclk);

	ग_लिखोl(old->समयr_val, priv->qfpconf + QFPROM_BLOW_TIMER_OFFSET);
	ग_लिखोl(old->accel_val, priv->qfpconf + QFPROM_ACCEL_OFFSET);
पूर्ण

/**
 * qfprom_enable_fuse_blowing() - Enable fuse blowing.
 * @priv: Our driver data.
 * @old:  We'll stash stuff here to use when disabling.
 *
 * Sets the value of the blow समयr, accel रेजिस्टर and the घड़ी
 * and voltage settings.
 *
 * Prपूर्णांकs messages अगर there are errors so caller करोesn't need to.
 *
 * Return: 0 or -err.
 */
अटल पूर्णांक qfprom_enable_fuse_blowing(स्थिर काष्ठा qfprom_priv *priv,
				      काष्ठा qfprom_touched_values *old)
अणु
	पूर्णांक ret;
	पूर्णांक qfprom_blow_uV = priv->soc_data->qfprom_blow_uV;

	ret = clk_prepare_enable(priv->secclk);
	अगर (ret) अणु
		dev_err(priv->dev, "Failed to enable clock\n");
		वापस ret;
	पूर्ण

	old->clk_rate = clk_get_rate(priv->secclk);
	ret = clk_set_rate(priv->secclk, priv->soc_data->qfprom_blow_set_freq);
	अगर (ret) अणु
		dev_err(priv->dev, "Failed to set clock rate for enable\n");
		जाओ err_clk_prepared;
	पूर्ण

	/*
	 * Hardware requires 1.8V min क्रम fuse blowing; this may be
	 * a rail shared करो करोn't specअगरy a max--regulator स्थिरraपूर्णांकs
	 * will handle.
	 */
	ret = regulator_set_voltage(priv->vcc, qfprom_blow_uV, पूर्णांक_उच्च);
	अगर (ret) अणु
		dev_err(priv->dev, "Failed to set %duV\n", qfprom_blow_uV);
		जाओ err_clk_rate_set;
	पूर्ण

	ret = regulator_enable(priv->vcc);
	अगर (ret) अणु
		dev_err(priv->dev, "Failed to enable regulator\n");
		जाओ err_clk_rate_set;
	पूर्ण

	old->समयr_val = पढ़ोl(priv->qfpconf + QFPROM_BLOW_TIMER_OFFSET);
	old->accel_val = पढ़ोl(priv->qfpconf + QFPROM_ACCEL_OFFSET);
	ग_लिखोl(priv->soc_data->qfprom_blow_समयr_value,
	       priv->qfpconf + QFPROM_BLOW_TIMER_OFFSET);
	ग_लिखोl(priv->soc_data->accel_value,
	       priv->qfpconf + QFPROM_ACCEL_OFFSET);

	वापस 0;

err_clk_rate_set:
	clk_set_rate(priv->secclk, old->clk_rate);
err_clk_prepared:
	clk_disable_unprepare(priv->secclk);
	वापस ret;
पूर्ण

/**
 * qfprom_efuse_reg_ग_लिखो() - Write to fuses.
 * @context: Our driver data.
 * @reg:     The offset to ग_लिखो at.
 * @_val:    Poपूर्णांकer to data to ग_लिखो.
 * @bytes:   The number of bytes to ग_लिखो.
 *
 * Writes to fuses.  WARNING: THIS IS PERMANENT.
 *
 * Return: 0 or -err.
 */
अटल पूर्णांक qfprom_reg_ग_लिखो(व्योम *context, अचिन्हित पूर्णांक reg, व्योम *_val,
			    माप_प्रकार bytes)
अणु
	काष्ठा qfprom_priv *priv = context;
	काष्ठा qfprom_touched_values old;
	पूर्णांक words = bytes / 4;
	u32 *value = _val;
	u32 blow_status;
	पूर्णांक ret;
	पूर्णांक i;

	dev_dbg(priv->dev,
		"Writing to raw qfprom region : %#010x of size: %zu\n",
		reg, bytes);

	/*
	 * The hardware only allows us to ग_लिखो word at a समय, but we can
	 * पढ़ो byte at a समय.  Until the nvmem framework allows a separate
	 * word_size and stride क्रम पढ़ोing vs. writing, we'll enक्रमce here.
	 */
	अगर (bytes % 4) अणु
		dev_err(priv->dev,
			"%zu is not an integral number of words\n", bytes);
		वापस -EINVAL;
	पूर्ण
	अगर (reg % 4) अणु
		dev_err(priv->dev,
			"Invalid offset: %#x.  Must be word aligned\n", reg);
		वापस -EINVAL;
	पूर्ण

	ret = qfprom_enable_fuse_blowing(priv, &old);
	अगर (ret)
		वापस ret;

	ret = पढ़ोl_relaxed_poll_समयout(
		priv->qfpconf + QFPROM_BLOW_STATUS_OFFSET,
		blow_status, blow_status == QFPROM_BLOW_STATUS_READY,
		QFPROM_FUSE_BLOW_POLL_US, QFPROM_FUSE_BLOW_TIMEOUT_US);

	अगर (ret) अणु
		dev_err(priv->dev,
			"Timeout waiting for initial ready; aborting.\n");
		जाओ निकास_enabled_fuse_blowing;
	पूर्ण

	क्रम (i = 0; i < words; i++)
		ग_लिखोl(value[i], priv->qfpraw + reg + (i * 4));

	ret = पढ़ोl_relaxed_poll_समयout(
		priv->qfpconf + QFPROM_BLOW_STATUS_OFFSET,
		blow_status, blow_status == QFPROM_BLOW_STATUS_READY,
		QFPROM_FUSE_BLOW_POLL_US, QFPROM_FUSE_BLOW_TIMEOUT_US);

	/* Give an error, but not much we can करो in this हाल */
	अगर (ret)
		dev_err(priv->dev, "Timeout waiting for finish.\n");

निकास_enabled_fuse_blowing:
	qfprom_disable_fuse_blowing(priv, &old);

	वापस ret;
पूर्ण

अटल पूर्णांक qfprom_reg_पढ़ो(व्योम *context,
			अचिन्हित पूर्णांक reg, व्योम *_val, माप_प्रकार bytes)
अणु
	काष्ठा qfprom_priv *priv = context;
	u8 *val = _val;
	पूर्णांक i = 0, words = bytes;
	व्योम __iomem *base = priv->qfpcorrected;

	अगर (पढ़ो_raw_data && priv->qfpraw)
		base = priv->qfpraw;

	जबतक (words--)
		*val++ = पढ़ोb(base + reg + i++);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा qfprom_soc_data qfprom_7_8_data = अणु
	.accel_value = 0xD10,
	.qfprom_blow_समयr_value = 25,
	.qfprom_blow_set_freq = 4800000,
	.qfprom_blow_uV = 1800000,
पूर्ण;

अटल स्थिर काष्ठा qfprom_soc_data qfprom_7_15_data = अणु
	.accel_value = 0xD08,
	.qfprom_blow_समयr_value = 24,
	.qfprom_blow_set_freq = 4800000,
	.qfprom_blow_uV = 1900000,
पूर्ण;

अटल पूर्णांक qfprom_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा nvmem_config econfig = अणु
		.name = "qfprom",
		.stride = 1,
		.word_size = 1,
		.id = NVMEM_DEVID_AUTO,
		.reg_पढ़ो = qfprom_reg_पढ़ो,
	पूर्ण;
	काष्ठा device *dev = &pdev->dev;
	काष्ठा resource *res;
	काष्ठा nvmem_device *nvmem;
	स्थिर काष्ठा qfprom_soc_compatible_data *soc_data;
	काष्ठा qfprom_priv *priv;
	पूर्णांक ret;

	priv = devm_kzalloc(dev, माप(*priv), GFP_KERNEL);
	अगर (!priv)
		वापस -ENOMEM;

	/* The corrected section is always provided */
	res = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);
	priv->qfpcorrected = devm_ioremap_resource(dev, res);
	अगर (IS_ERR(priv->qfpcorrected))
		वापस PTR_ERR(priv->qfpcorrected);

	econfig.size = resource_size(res);
	econfig.dev = dev;
	econfig.priv = priv;

	priv->dev = dev;
	soc_data = device_get_match_data(dev);
	अगर (soc_data) अणु
		econfig.keepout = soc_data->keepout;
		econfig.nkeepout = soc_data->nkeepout;
	पूर्ण

	/*
	 * If more than one region is provided then the OS has the ability
	 * to ग_लिखो.
	 */
	res = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 1);
	अगर (res) अणु
		u32 version;
		पूर्णांक major_version, minor_version;

		priv->qfpraw = devm_ioremap_resource(dev, res);
		अगर (IS_ERR(priv->qfpraw))
			वापस PTR_ERR(priv->qfpraw);
		res = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 2);
		priv->qfpconf = devm_ioremap_resource(dev, res);
		अगर (IS_ERR(priv->qfpconf))
			वापस PTR_ERR(priv->qfpconf);
		res = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 3);
		priv->qfpsecurity = devm_ioremap_resource(dev, res);
		अगर (IS_ERR(priv->qfpsecurity))
			वापस PTR_ERR(priv->qfpsecurity);

		version = पढ़ोl(priv->qfpsecurity + QFPROM_VERSION_OFFSET);
		major_version = (version & QFPROM_MAJOR_VERSION_MASK) >>
				QFPROM_MAJOR_VERSION_SHIFT;
		minor_version = (version & QFPROM_MINOR_VERSION_MASK) >>
				QFPROM_MINOR_VERSION_SHIFT;

		अगर (major_version == 7 && minor_version == 8)
			priv->soc_data = &qfprom_7_8_data;
		अगर (major_version == 7 && minor_version == 15)
			priv->soc_data = &qfprom_7_15_data;

		priv->vcc = devm_regulator_get(&pdev->dev, "vcc");
		अगर (IS_ERR(priv->vcc))
			वापस PTR_ERR(priv->vcc);

		priv->secclk = devm_clk_get(dev, "core");
		अगर (IS_ERR(priv->secclk)) अणु
			ret = PTR_ERR(priv->secclk);
			अगर (ret != -EPROBE_DEFER)
				dev_err(dev, "Error getting clock: %d\n", ret);
			वापस ret;
		पूर्ण

		/* Only enable writing अगर we have SoC data. */
		अगर (priv->soc_data)
			econfig.reg_ग_लिखो = qfprom_reg_ग_लिखो;
	पूर्ण

	nvmem = devm_nvmem_रेजिस्टर(dev, &econfig);

	वापस PTR_ERR_OR_ZERO(nvmem);
पूर्ण

अटल स्थिर काष्ठा of_device_id qfprom_of_match[] = अणु
	अणु .compatible = "qcom,qfprom",पूर्ण,
	अणु .compatible = "qcom,sc7180-qfprom", .data = &sc7180_qfpromपूर्ण,
	अणु .compatible = "qcom,sc7280-qfprom", .data = &sc7280_qfpromपूर्ण,
	अणु/* sentinel */पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, qfprom_of_match);

अटल काष्ठा platक्रमm_driver qfprom_driver = अणु
	.probe = qfprom_probe,
	.driver = अणु
		.name = "qcom,qfprom",
		.of_match_table = qfprom_of_match,
	पूर्ण,
पूर्ण;
module_platक्रमm_driver(qfprom_driver);
MODULE_AUTHOR("Srinivas Kandagatla <srinivas.kandagatla@linaro.org>");
MODULE_DESCRIPTION("Qualcomm QFPROM driver");
MODULE_LICENSE("GPL v2");
