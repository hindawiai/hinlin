<शैली गुरु>
// SPDX-License-Identअगरier: (GPL-2.0 OR MIT)
//
// Copyright (c) 2018 BayLibre, SAS.
// Author: Jerome Brunet <jbrunet@baylibre.com>

#समावेश <linux/bitfield.h>
#समावेश <linux/clk.h>
#समावेश <linux/module.h>
#समावेश <linux/of_platक्रमm.h>
#समावेश <linux/regmap.h>
#समावेश <sound/soc.h>
#समावेश <sound/soc-dai.h>
#समावेश <sound/pcm_params.h>

#घोषणा SPDIFIN_CTRL0			0x00
#घोषणा  SPDIFIN_CTRL0_EN		BIT(31)
#घोषणा  SPDIFIN_CTRL0_RST_OUT		BIT(29)
#घोषणा  SPDIFIN_CTRL0_RST_IN		BIT(28)
#घोषणा  SPDIFIN_CTRL0_WIDTH_SEL	BIT(24)
#घोषणा  SPDIFIN_CTRL0_STATUS_CH_SHIFT	11
#घोषणा  SPDIFIN_CTRL0_STATUS_SEL	GENMASK(10, 8)
#घोषणा  SPDIFIN_CTRL0_SRC_SEL		GENMASK(5, 4)
#घोषणा  SPDIFIN_CTRL0_CHK_VALID	BIT(3)
#घोषणा SPDIFIN_CTRL1			0x04
#घोषणा  SPDIFIN_CTRL1_BASE_TIMER	GENMASK(19, 0)
#घोषणा  SPDIFIN_CTRL1_IRQ_MASK		GENMASK(27, 20)
#घोषणा SPDIFIN_CTRL2			0x08
#घोषणा  SPDIFIN_THRES_PER_REG		3
#घोषणा  SPDIFIN_THRES_WIDTH		10
#घोषणा SPDIFIN_CTRL3			0x0c
#घोषणा SPDIFIN_CTRL4			0x10
#घोषणा  SPDIFIN_TIMER_PER_REG		4
#घोषणा  SPDIFIN_TIMER_WIDTH		8
#घोषणा SPDIFIN_CTRL5			0x14
#घोषणा SPDIFIN_CTRL6			0x18
#घोषणा SPDIFIN_STAT0			0x1c
#घोषणा  SPDIFIN_STAT0_MODE		GENMASK(30, 28)
#घोषणा  SPDIFIN_STAT0_MAXW		GENMASK(17, 8)
#घोषणा  SPDIFIN_STAT0_IRQ		GENMASK(7, 0)
#घोषणा  SPDIFIN_IRQ_MODE_CHANGED	BIT(2)
#घोषणा SPDIFIN_STAT1			0x20
#घोषणा SPDIFIN_STAT2			0x24
#घोषणा SPDIFIN_MUTE_VAL		0x28

#घोषणा SPDIFIN_MODE_NUM		7

काष्ठा axg_spdअगरin_cfg अणु
	स्थिर अचिन्हित पूर्णांक *mode_rates;
	अचिन्हित पूर्णांक ref_rate;
पूर्ण;

काष्ठा axg_spdअगरin अणु
	स्थिर काष्ठा axg_spdअगरin_cfg *conf;
	काष्ठा regmap *map;
	काष्ठा clk *refclk;
	काष्ठा clk *pclk;
पूर्ण;

/*
 * TODO:
 * It would have been nice to check the actual rate against the sample rate
 * requested in hw_params(). Unक्रमtunately, I was not able to make the mode
 * detection and IRQ work reliably:
 *
 * 1. IRQs are generated on mode change only, so there is no notअगरication
 *    on transition between no संकेत and mode 0 (32kHz).
 * 2. Mode detection very often has glitches, and may detects the
 *    lowest or the highest mode beक्रमe zeroing in on the actual mode.
 *
 * This makes calling snd_pcm_stop() dअगरficult to get right. Even notअगरying
 * the kcontrol would be very unreliable at this poपूर्णांक.
 * Let's keep things simple until the magic spell that makes this work is
 * found.
 */

अटल अचिन्हित पूर्णांक axg_spdअगरin_get_rate(काष्ठा axg_spdअगरin *priv)
अणु
	अचिन्हित पूर्णांक stat, mode, rate = 0;

	regmap_पढ़ो(priv->map, SPDIFIN_STAT0, &stat);
	mode = FIELD_GET(SPDIFIN_STAT0_MODE, stat);

	/*
	 * If max width is zero, we are not capturing anything.
	 * Also Someबार, when the capture is on but there is no data,
	 * mode is SPDIFIN_MODE_NUM, but not always ...
	 */
	अगर (FIELD_GET(SPDIFIN_STAT0_MAXW, stat) &&
	    mode < SPDIFIN_MODE_NUM)
		rate = priv->conf->mode_rates[mode];

	वापस rate;
पूर्ण

अटल पूर्णांक axg_spdअगरin_prepare(काष्ठा snd_pcm_substream *substream,
			       काष्ठा snd_soc_dai *dai)
अणु
	काष्ठा axg_spdअगरin *priv = snd_soc_dai_get_drvdata(dai);

	/* Apply both reset */
	regmap_update_bits(priv->map, SPDIFIN_CTRL0,
			   SPDIFIN_CTRL0_RST_OUT |
			   SPDIFIN_CTRL0_RST_IN,
			   0);

	/* Clear out reset beक्रमe in reset */
	regmap_update_bits(priv->map, SPDIFIN_CTRL0,
			   SPDIFIN_CTRL0_RST_OUT, SPDIFIN_CTRL0_RST_OUT);
	regmap_update_bits(priv->map, SPDIFIN_CTRL0,
			   SPDIFIN_CTRL0_RST_IN,  SPDIFIN_CTRL0_RST_IN);

	वापस 0;
पूर्ण

अटल पूर्णांक axg_spdअगरin_startup(काष्ठा snd_pcm_substream *substream,
			       काष्ठा snd_soc_dai *dai)
अणु
	काष्ठा axg_spdअगरin *priv = snd_soc_dai_get_drvdata(dai);
	पूर्णांक ret;

	ret = clk_prepare_enable(priv->refclk);
	अगर (ret) अणु
		dev_err(dai->dev,
			"failed to enable spdifin reference clock\n");
		वापस ret;
	पूर्ण

	regmap_update_bits(priv->map, SPDIFIN_CTRL0, SPDIFIN_CTRL0_EN,
			   SPDIFIN_CTRL0_EN);

	वापस 0;
पूर्ण

अटल व्योम axg_spdअगरin_shutकरोwn(काष्ठा snd_pcm_substream *substream,
				 काष्ठा snd_soc_dai *dai)
अणु
	काष्ठा axg_spdअगरin *priv = snd_soc_dai_get_drvdata(dai);

	regmap_update_bits(priv->map, SPDIFIN_CTRL0, SPDIFIN_CTRL0_EN, 0);
	clk_disable_unprepare(priv->refclk);
पूर्ण

अटल व्योम axg_spdअगरin_ग_लिखो_mode_param(काष्ठा regmap *map, पूर्णांक mode,
					 अचिन्हित पूर्णांक val,
					 अचिन्हित पूर्णांक num_per_reg,
					 अचिन्हित पूर्णांक base_reg,
					 अचिन्हित पूर्णांक width)
अणु
	uपूर्णांक64_t offset = mode;
	अचिन्हित पूर्णांक reg, shअगरt, rem;

	rem = करो_भाग(offset, num_per_reg);

	reg = offset * regmap_get_reg_stride(map) + base_reg;
	shअगरt = width * (num_per_reg - 1 - rem);

	regmap_update_bits(map, reg, GENMASK(width - 1, 0) << shअगरt,
			   val << shअगरt);
पूर्ण

अटल व्योम axg_spdअगरin_ग_लिखो_समयr(काष्ठा regmap *map, पूर्णांक mode,
				    अचिन्हित पूर्णांक val)
अणु
	axg_spdअगरin_ग_लिखो_mode_param(map, mode, val, SPDIFIN_TIMER_PER_REG,
				     SPDIFIN_CTRL4, SPDIFIN_TIMER_WIDTH);
पूर्ण

अटल व्योम axg_spdअगरin_ग_लिखो_threshold(काष्ठा regmap *map, पूर्णांक mode,
					अचिन्हित पूर्णांक val)
अणु
	axg_spdअगरin_ग_लिखो_mode_param(map, mode, val, SPDIFIN_THRES_PER_REG,
				     SPDIFIN_CTRL2, SPDIFIN_THRES_WIDTH);
पूर्ण

अटल अचिन्हित पूर्णांक axg_spdअगरin_mode_समयr(काष्ठा axg_spdअगरin *priv,
					   पूर्णांक mode,
					   अचिन्हित पूर्णांक rate)
अणु
	/*
	 * Number of period of the reference घड़ी during a period of the
	 * input संकेत reference घड़ी
	 */
	वापस rate / (128 * priv->conf->mode_rates[mode]);
पूर्ण

अटल पूर्णांक axg_spdअगरin_sample_mode_config(काष्ठा snd_soc_dai *dai,
					  काष्ठा axg_spdअगरin *priv)
अणु
	अचिन्हित पूर्णांक rate, t_next;
	पूर्णांक ret, i = SPDIFIN_MODE_NUM - 1;

	/* Set spdअगर input reference घड़ी */
	ret = clk_set_rate(priv->refclk, priv->conf->ref_rate);
	अगर (ret) अणु
		dev_err(dai->dev, "reference clock rate set failed\n");
		वापस ret;
	पूर्ण

	/*
	 * The rate actually set might be slightly dअगरferent, get
	 * the actual rate क्रम the following mode calculation
	 */
	rate = clk_get_rate(priv->refclk);

	/* HW will update mode every 1ms */
	regmap_update_bits(priv->map, SPDIFIN_CTRL1,
			   SPDIFIN_CTRL1_BASE_TIMER,
			   FIELD_PREP(SPDIFIN_CTRL1_BASE_TIMER, rate / 1000));

	/* Threshold based on the minimum width between two edges */
	regmap_update_bits(priv->map, SPDIFIN_CTRL0,
			   SPDIFIN_CTRL0_WIDTH_SEL, SPDIFIN_CTRL0_WIDTH_SEL);

	/* Calculate the last समयr which has no threshold */
	t_next = axg_spdअगरin_mode_समयr(priv, i, rate);
	axg_spdअगरin_ग_लिखो_समयr(priv->map, i, t_next);

	करो अणु
		अचिन्हित पूर्णांक t;

		i -= 1;

		/* Calculate the समयr */
		t = axg_spdअगरin_mode_समयr(priv, i, rate);

		/* Set the समयr value */
		axg_spdअगरin_ग_लिखो_समयr(priv->map, i, t);

		/* Set the threshold value */
		axg_spdअगरin_ग_लिखो_threshold(priv->map, i, t + t_next);

		/* Save the current समयr क्रम the next threshold calculation */
		t_next = t;

	पूर्ण जबतक (i > 0);

	वापस 0;
पूर्ण

अटल पूर्णांक axg_spdअगरin_dai_probe(काष्ठा snd_soc_dai *dai)
अणु
	काष्ठा axg_spdअगरin *priv = snd_soc_dai_get_drvdata(dai);
	पूर्णांक ret;

	ret = clk_prepare_enable(priv->pclk);
	अगर (ret) अणु
		dev_err(dai->dev, "failed to enable pclk\n");
		वापस ret;
	पूर्ण

	ret = axg_spdअगरin_sample_mode_config(dai, priv);
	अगर (ret) अणु
		dev_err(dai->dev, "mode configuration failed\n");
		clk_disable_unprepare(priv->pclk);
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक axg_spdअगरin_dai_हटाओ(काष्ठा snd_soc_dai *dai)
अणु
	काष्ठा axg_spdअगरin *priv = snd_soc_dai_get_drvdata(dai);

	clk_disable_unprepare(priv->pclk);
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा snd_soc_dai_ops axg_spdअगरin_ops = अणु
	.prepare	= axg_spdअगरin_prepare,
	.startup	= axg_spdअगरin_startup,
	.shutकरोwn	= axg_spdअगरin_shutकरोwn,
पूर्ण;

अटल पूर्णांक axg_spdअगरin_iec958_info(काष्ठा snd_kcontrol *kcontrol,
				   काष्ठा snd_ctl_elem_info *uinfo)
अणु
	uinfo->type = SNDRV_CTL_ELEM_TYPE_IEC958;
	uinfo->count = 1;

	वापस 0;
पूर्ण

अटल पूर्णांक axg_spdअगरin_get_status_mask(काष्ठा snd_kcontrol *kcontrol,
				       काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < 24; i++)
		ucontrol->value.iec958.status[i] = 0xff;

	वापस 0;
पूर्ण

अटल पूर्णांक axg_spdअगरin_get_status(काष्ठा snd_kcontrol *kcontrol,
				  काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_soc_component *c = snd_kcontrol_chip(kcontrol);
	काष्ठा axg_spdअगरin *priv = snd_soc_component_get_drvdata(c);
	पूर्णांक i, j;

	क्रम (i = 0; i < 6; i++) अणु
		अचिन्हित पूर्णांक val;

		regmap_update_bits(priv->map, SPDIFIN_CTRL0,
				   SPDIFIN_CTRL0_STATUS_SEL,
				   FIELD_PREP(SPDIFIN_CTRL0_STATUS_SEL, i));

		regmap_पढ़ो(priv->map, SPDIFIN_STAT1, &val);

		क्रम (j = 0; j < 4; j++) अणु
			अचिन्हित पूर्णांक offset = i * 4 + j;

			ucontrol->value.iec958.status[offset] =
				(val >> (j * 8)) & 0xff;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

#घोषणा AXG_SPDIFIN_IEC958_MASK						\
	अणु								\
		.access = SNDRV_CTL_ELEM_ACCESS_READ,			\
		.अगरace = SNDRV_CTL_ELEM_IFACE_PCM,			\
		.name = SNDRV_CTL_NAME_IEC958("", CAPTURE, MASK),	\
		.info = axg_spdअगरin_iec958_info,			\
		.get = axg_spdअगरin_get_status_mask,			\
	पूर्ण

#घोषणा AXG_SPDIFIN_IEC958_STATUS					\
	अणु								\
		.access = (SNDRV_CTL_ELEM_ACCESS_READ |			\
			   SNDRV_CTL_ELEM_ACCESS_VOLATILE),		\
		.अगरace = SNDRV_CTL_ELEM_IFACE_PCM,			\
		.name =	SNDRV_CTL_NAME_IEC958("", CAPTURE, NONE),	\
		.info = axg_spdअगरin_iec958_info,			\
		.get = axg_spdअगरin_get_status,				\
	पूर्ण

अटल स्थिर अक्षर * स्थिर spdअगरin_chsts_src_texts[] = अणु
	"A", "B",
पूर्ण;

अटल SOC_ENUM_SINGLE_DECL(axg_spdअगरin_chsts_src_क्रमागत, SPDIFIN_CTRL0,
			    SPDIFIN_CTRL0_STATUS_CH_SHIFT,
			    spdअगरin_chsts_src_texts);

अटल पूर्णांक axg_spdअगरin_rate_lock_info(काष्ठा snd_kcontrol *kcontrol,
				      काष्ठा snd_ctl_elem_info *uinfo)
अणु
	uinfo->type = SNDRV_CTL_ELEM_TYPE_INTEGER;
	uinfo->count = 1;
	uinfo->value.पूर्णांकeger.min = 0;
	uinfo->value.पूर्णांकeger.max = 192000;

	वापस 0;
पूर्ण

अटल पूर्णांक axg_spdअगरin_rate_lock_get(काष्ठा snd_kcontrol *kcontrol,
				     काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_soc_component *c = snd_kcontrol_chip(kcontrol);
	काष्ठा axg_spdअगरin *priv = snd_soc_component_get_drvdata(c);

	ucontrol->value.पूर्णांकeger.value[0] = axg_spdअगरin_get_rate(priv);

	वापस 0;
पूर्ण

#घोषणा AXG_SPDIFIN_LOCK_RATE(xname)				\
	अणु							\
		.अगरace = SNDRV_CTL_ELEM_IFACE_PCM,		\
		.access = (SNDRV_CTL_ELEM_ACCESS_READ |		\
			   SNDRV_CTL_ELEM_ACCESS_VOLATILE),	\
		.get = axg_spdअगरin_rate_lock_get,		\
		.info = axg_spdअगरin_rate_lock_info,		\
		.name = xname,					\
	पूर्ण

अटल स्थिर काष्ठा snd_kcontrol_new axg_spdअगरin_controls[] = अणु
	AXG_SPDIFIN_LOCK_RATE("Capture Rate Lock"),
	SOC_DOUBLE("Capture Switch", SPDIFIN_CTRL0, 7, 6, 1, 1),
	SOC_ENUM(SNDRV_CTL_NAME_IEC958("", CAPTURE, NONE) "Src",
		 axg_spdअगरin_chsts_src_क्रमागत),
	AXG_SPDIFIN_IEC958_MASK,
	AXG_SPDIFIN_IEC958_STATUS,
पूर्ण;

अटल स्थिर काष्ठा snd_soc_component_driver axg_spdअगरin_component_drv = अणु
	.controls		= axg_spdअगरin_controls,
	.num_controls		= ARRAY_SIZE(axg_spdअगरin_controls),
पूर्ण;

अटल स्थिर काष्ठा regmap_config axg_spdअगरin_regmap_cfg = अणु
	.reg_bits	= 32,
	.val_bits	= 32,
	.reg_stride	= 4,
	.max_रेजिस्टर	= SPDIFIN_MUTE_VAL,
पूर्ण;

अटल स्थिर अचिन्हित पूर्णांक axg_spdअगरin_mode_rates[SPDIFIN_MODE_NUM] = अणु
	32000, 44100, 48000, 88200, 96000, 176400, 192000,
पूर्ण;

अटल स्थिर काष्ठा axg_spdअगरin_cfg axg_cfg = अणु
	.mode_rates = axg_spdअगरin_mode_rates,
	.ref_rate = 333333333,
पूर्ण;

अटल स्थिर काष्ठा of_device_id axg_spdअगरin_of_match[] = अणु
	अणु
		.compatible = "amlogic,axg-spdifin",
		.data = &axg_cfg,
	पूर्ण, अणुपूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, axg_spdअगरin_of_match);

अटल काष्ठा snd_soc_dai_driver *
axg_spdअगरin_get_dai_drv(काष्ठा device *dev, काष्ठा axg_spdअगरin *priv)
अणु
	काष्ठा snd_soc_dai_driver *drv;
	पूर्णांक i;

	drv = devm_kzalloc(dev, माप(*drv), GFP_KERNEL);
	अगर (!drv)
		वापस ERR_PTR(-ENOMEM);

	drv->name = "SPDIF Input";
	drv->ops = &axg_spdअगरin_ops;
	drv->probe = axg_spdअगरin_dai_probe;
	drv->हटाओ = axg_spdअगरin_dai_हटाओ;
	drv->capture.stream_name = "Capture";
	drv->capture.channels_min = 1;
	drv->capture.channels_max = 2;
	drv->capture.क्रमmats = SNDRV_PCM_FMTBIT_IEC958_SUBFRAME_LE;

	क्रम (i = 0; i < SPDIFIN_MODE_NUM; i++) अणु
		अचिन्हित पूर्णांक rb =
			snd_pcm_rate_to_rate_bit(priv->conf->mode_rates[i]);

		अगर (rb == SNDRV_PCM_RATE_KNOT)
			वापस ERR_PTR(-EINVAL);

		drv->capture.rates |= rb;
	पूर्ण

	वापस drv;
पूर्ण

अटल पूर्णांक axg_spdअगरin_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device *dev = &pdev->dev;
	काष्ठा axg_spdअगरin *priv;
	काष्ठा snd_soc_dai_driver *dai_drv;
	व्योम __iomem *regs;
	पूर्णांक ret;

	priv = devm_kzalloc(dev, माप(*priv), GFP_KERNEL);
	अगर (!priv)
		वापस -ENOMEM;
	platक्रमm_set_drvdata(pdev, priv);

	priv->conf = of_device_get_match_data(dev);
	अगर (!priv->conf) अणु
		dev_err(dev, "failed to match device\n");
		वापस -ENODEV;
	पूर्ण

	regs = devm_platक्रमm_ioremap_resource(pdev, 0);
	अगर (IS_ERR(regs))
		वापस PTR_ERR(regs);

	priv->map = devm_regmap_init_mmio(dev, regs, &axg_spdअगरin_regmap_cfg);
	अगर (IS_ERR(priv->map)) अणु
		dev_err(dev, "failed to init regmap: %ld\n",
			PTR_ERR(priv->map));
		वापस PTR_ERR(priv->map);
	पूर्ण

	priv->pclk = devm_clk_get(dev, "pclk");
	अगर (IS_ERR(priv->pclk)) अणु
		ret = PTR_ERR(priv->pclk);
		अगर (ret != -EPROBE_DEFER)
			dev_err(dev, "failed to get pclk: %d\n", ret);
		वापस ret;
	पूर्ण

	priv->refclk = devm_clk_get(dev, "refclk");
	अगर (IS_ERR(priv->refclk)) अणु
		ret = PTR_ERR(priv->refclk);
		अगर (ret != -EPROBE_DEFER)
			dev_err(dev, "failed to get mclk: %d\n", ret);
		वापस ret;
	पूर्ण

	dai_drv = axg_spdअगरin_get_dai_drv(dev, priv);
	अगर (IS_ERR(dai_drv)) अणु
		dev_err(dev, "failed to get dai driver: %ld\n",
			PTR_ERR(dai_drv));
		वापस PTR_ERR(dai_drv);
	पूर्ण

	वापस devm_snd_soc_रेजिस्टर_component(dev, &axg_spdअगरin_component_drv,
					       dai_drv, 1);
पूर्ण

अटल काष्ठा platक्रमm_driver axg_spdअगरin_pdrv = अणु
	.probe = axg_spdअगरin_probe,
	.driver = अणु
		.name = "axg-spdifin",
		.of_match_table = axg_spdअगरin_of_match,
	पूर्ण,
पूर्ण;
module_platक्रमm_driver(axg_spdअगरin_pdrv);

MODULE_DESCRIPTION("Amlogic AXG SPDIF Input driver");
MODULE_AUTHOR("Jerome Brunet <jbrunet@baylibre.com>");
MODULE_LICENSE("GPL v2");
