<शैली गुरु>
// SPDX-License-Identअगरier: (GPL-2.0 OR MIT)
//
// Copyright (c) 2018 BayLibre, SAS.
// Author: Jerome Brunet <jbrunet@baylibre.com>

#समावेश <linux/clk.h>
#समावेश <linux/module.h>
#समावेश <linux/of_platक्रमm.h>
#समावेश <linux/regmap.h>
#समावेश <linux/reset.h>
#समावेश <sound/soc.h>

#समावेश "axg-tdm-formatter.h"

काष्ठा axg_tdm_क्रमmatter अणु
	काष्ठा list_head list;
	काष्ठा axg_tdm_stream *stream;
	स्थिर काष्ठा axg_tdm_क्रमmatter_driver *drv;
	काष्ठा clk *pclk;
	काष्ठा clk *sclk;
	काष्ठा clk *lrclk;
	काष्ठा clk *sclk_sel;
	काष्ठा clk *lrclk_sel;
	काष्ठा reset_control *reset;
	bool enabled;
	काष्ठा regmap *map;
पूर्ण;

पूर्णांक axg_tdm_क्रमmatter_set_channel_masks(काष्ठा regmap *map,
					काष्ठा axg_tdm_stream *ts,
					अचिन्हित पूर्णांक offset)
अणु
	अचिन्हित पूर्णांक val, ch = ts->channels;
	अचिन्हित दीर्घ mask;
	पूर्णांक i, j;

	/*
	 * Distribute the channels of the stream over the available slots
	 * of each TDM lane
	 */
	क्रम (i = 0; i < AXG_TDM_NUM_LANES; i++) अणु
		val = 0;
		mask = ts->mask[i];

		क्रम (j = find_first_bit(&mask, 32);
		     (j < 32) && ch;
		     j = find_next_bit(&mask, 32, j + 1)) अणु
			val |= 1 << j;
			ch -= 1;
		पूर्ण

		regmap_ग_लिखो(map, offset, val);
		offset += regmap_get_reg_stride(map);
	पूर्ण

	/*
	 * If we still have channel left at the end of the process, it means
	 * the stream has more channels than we can accommodate and we should
	 * have caught this earlier.
	 */
	अगर (WARN_ON(ch != 0)) अणु
		pr_err("channel mask error\n");
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(axg_tdm_क्रमmatter_set_channel_masks);

अटल पूर्णांक axg_tdm_क्रमmatter_enable(काष्ठा axg_tdm_क्रमmatter *क्रमmatter)
अणु
	काष्ठा axg_tdm_stream *ts = क्रमmatter->stream;
	bool invert;
	पूर्णांक ret;

	/* Do nothing अगर the क्रमmatter is alपढ़ोy enabled */
	अगर (क्रमmatter->enabled)
		वापस 0;

	/*
	 * On the g12a (and possibly other SoCs), when a stream using
	 * multiple lanes is restarted, it will someबार not start
	 * from the first lane, but अक्रमomly from another used one.
	 * The result is an unexpected and अक्रमom channel shअगरt.
	 *
	 * The hypothesis is that an HW counter is not properly reset
	 * and the क्रमmatter simply starts on the lane it stopped
	 * beक्रमe. Unक्रमtunately, there करोes not seems to be a way to
	 * reset this through the रेजिस्टरs of the block.
	 *
	 * However, the g12a has indenpendent reset lines क्रम each audio
	 * devices. Using this reset beक्रमe each start solves the issue.
	 */
	ret = reset_control_reset(क्रमmatter->reset);
	अगर (ret)
		वापस ret;

	/*
	 * If sclk is inverted, it means the bit should latched on the
	 * rising edge which is what our HW expects. If not, we need to
	 * invert it beक्रमe the क्रमmatter.
	 */
	invert = axg_tdm_sclk_invert(ts->अगरace->fmt);
	ret = clk_set_phase(क्रमmatter->sclk, invert ? 0 : 180);
	अगर (ret)
		वापस ret;

	/* Setup the stream parameter in the क्रमmatter */
	ret = क्रमmatter->drv->ops->prepare(क्रमmatter->map,
					   क्रमmatter->drv->quirks,
					   क्रमmatter->stream);
	अगर (ret)
		वापस ret;

	/* Enable the संकेत घड़ीs feeding the क्रमmatter */
	ret = clk_prepare_enable(क्रमmatter->sclk);
	अगर (ret)
		वापस ret;

	ret = clk_prepare_enable(क्रमmatter->lrclk);
	अगर (ret) अणु
		clk_disable_unprepare(क्रमmatter->sclk);
		वापस ret;
	पूर्ण

	/* Finally, actually enable the क्रमmatter */
	क्रमmatter->drv->ops->enable(क्रमmatter->map);
	क्रमmatter->enabled = true;

	वापस 0;
पूर्ण

अटल व्योम axg_tdm_क्रमmatter_disable(काष्ठा axg_tdm_क्रमmatter *क्रमmatter)
अणु
	/* Do nothing अगर the क्रमmatter is alपढ़ोy disabled */
	अगर (!क्रमmatter->enabled)
		वापस;

	क्रमmatter->drv->ops->disable(क्रमmatter->map);
	clk_disable_unprepare(क्रमmatter->lrclk);
	clk_disable_unprepare(क्रमmatter->sclk);
	क्रमmatter->enabled = false;
पूर्ण

अटल पूर्णांक axg_tdm_क्रमmatter_attach(काष्ठा axg_tdm_क्रमmatter *क्रमmatter)
अणु
	काष्ठा axg_tdm_stream *ts = क्रमmatter->stream;
	पूर्णांक ret = 0;

	mutex_lock(&ts->lock);

	/* Catch up अगर the stream is alपढ़ोy running when we attach */
	अगर (ts->पढ़ोy) अणु
		ret = axg_tdm_क्रमmatter_enable(क्रमmatter);
		अगर (ret) अणु
			pr_err("failed to enable formatter\n");
			जाओ out;
		पूर्ण
	पूर्ण

	list_add_tail(&क्रमmatter->list, &ts->क्रमmatter_list);
out:
	mutex_unlock(&ts->lock);
	वापस ret;
पूर्ण

अटल व्योम axg_tdm_क्रमmatter_dettach(काष्ठा axg_tdm_क्रमmatter *क्रमmatter)
अणु
	काष्ठा axg_tdm_stream *ts = क्रमmatter->stream;

	mutex_lock(&ts->lock);
	list_del(&क्रमmatter->list);
	mutex_unlock(&ts->lock);

	axg_tdm_क्रमmatter_disable(क्रमmatter);
पूर्ण

अटल पूर्णांक axg_tdm_क्रमmatter_घातer_up(काष्ठा axg_tdm_क्रमmatter *क्रमmatter,
				      काष्ठा snd_soc_dapm_widget *w)
अणु
	काष्ठा axg_tdm_stream *ts = क्रमmatter->drv->ops->get_stream(w);
	पूर्णांक ret;

	/*
	 * If we करोn't get a stream at this stage, it would mean that the
	 * widget is घातering up but is not attached to any backend DAI.
	 * It should not happen, ever !
	 */
	अगर (WARN_ON(!ts))
		वापस -ENODEV;

	/* Clock our device */
	ret = clk_prepare_enable(क्रमmatter->pclk);
	अगर (ret)
		वापस ret;

	/* Reparent the bit घड़ी to the TDM पूर्णांकerface */
	ret = clk_set_parent(क्रमmatter->sclk_sel, ts->अगरace->sclk);
	अगर (ret)
		जाओ disable_pclk;

	/* Reparent the sample घड़ी to the TDM पूर्णांकerface */
	ret = clk_set_parent(क्रमmatter->lrclk_sel, ts->अगरace->lrclk);
	अगर (ret)
		जाओ disable_pclk;

	क्रमmatter->stream = ts;
	ret = axg_tdm_क्रमmatter_attach(क्रमmatter);
	अगर (ret)
		जाओ disable_pclk;

	वापस 0;

disable_pclk:
	clk_disable_unprepare(क्रमmatter->pclk);
	वापस ret;
पूर्ण

अटल व्योम axg_tdm_क्रमmatter_घातer_करोwn(काष्ठा axg_tdm_क्रमmatter *क्रमmatter)
अणु
	axg_tdm_क्रमmatter_dettach(क्रमmatter);
	clk_disable_unprepare(क्रमmatter->pclk);
	क्रमmatter->stream = शून्य;
पूर्ण

पूर्णांक axg_tdm_क्रमmatter_event(काष्ठा snd_soc_dapm_widget *w,
			    काष्ठा snd_kcontrol *control,
			    पूर्णांक event)
अणु
	काष्ठा snd_soc_component *c = snd_soc_dapm_to_component(w->dapm);
	काष्ठा axg_tdm_क्रमmatter *क्रमmatter = snd_soc_component_get_drvdata(c);
	पूर्णांक ret = 0;

	चयन (event) अणु
	हाल SND_SOC_DAPM_PRE_PMU:
		ret = axg_tdm_क्रमmatter_घातer_up(क्रमmatter, w);
		अवरोध;

	हाल SND_SOC_DAPM_PRE_PMD:
		axg_tdm_क्रमmatter_घातer_करोwn(क्रमmatter);
		अवरोध;

	शेष:
		dev_err(c->dev, "Unexpected event %d\n", event);
		वापस -EINVAL;
	पूर्ण

	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(axg_tdm_क्रमmatter_event);

पूर्णांक axg_tdm_क्रमmatter_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device *dev = &pdev->dev;
	स्थिर काष्ठा axg_tdm_क्रमmatter_driver *drv;
	काष्ठा axg_tdm_क्रमmatter *क्रमmatter;
	व्योम __iomem *regs;
	पूर्णांक ret;

	drv = of_device_get_match_data(dev);
	अगर (!drv) अणु
		dev_err(dev, "failed to match device\n");
		वापस -ENODEV;
	पूर्ण

	क्रमmatter = devm_kzalloc(dev, माप(*क्रमmatter), GFP_KERNEL);
	अगर (!क्रमmatter)
		वापस -ENOMEM;
	platक्रमm_set_drvdata(pdev, क्रमmatter);
	क्रमmatter->drv = drv;

	regs = devm_platक्रमm_ioremap_resource(pdev, 0);
	अगर (IS_ERR(regs))
		वापस PTR_ERR(regs);

	क्रमmatter->map = devm_regmap_init_mmio(dev, regs, drv->regmap_cfg);
	अगर (IS_ERR(क्रमmatter->map)) अणु
		dev_err(dev, "failed to init regmap: %ld\n",
			PTR_ERR(क्रमmatter->map));
		वापस PTR_ERR(क्रमmatter->map);
	पूर्ण

	/* Peripharal घड़ी */
	क्रमmatter->pclk = devm_clk_get(dev, "pclk");
	अगर (IS_ERR(क्रमmatter->pclk)) अणु
		ret = PTR_ERR(क्रमmatter->pclk);
		अगर (ret != -EPROBE_DEFER)
			dev_err(dev, "failed to get pclk: %d\n", ret);
		वापस ret;
	पूर्ण

	/* Formatter bit घड़ी */
	क्रमmatter->sclk = devm_clk_get(dev, "sclk");
	अगर (IS_ERR(क्रमmatter->sclk)) अणु
		ret = PTR_ERR(क्रमmatter->sclk);
		अगर (ret != -EPROBE_DEFER)
			dev_err(dev, "failed to get sclk: %d\n", ret);
		वापस ret;
	पूर्ण

	/* Formatter sample घड़ी */
	क्रमmatter->lrclk = devm_clk_get(dev, "lrclk");
	अगर (IS_ERR(क्रमmatter->lrclk)) अणु
		ret = PTR_ERR(क्रमmatter->lrclk);
		अगर (ret != -EPROBE_DEFER)
			dev_err(dev, "failed to get lrclk: %d\n", ret);
		वापस ret;
	पूर्ण

	/* Formatter bit घड़ी input multiplexer */
	क्रमmatter->sclk_sel = devm_clk_get(dev, "sclk_sel");
	अगर (IS_ERR(क्रमmatter->sclk_sel)) अणु
		ret = PTR_ERR(क्रमmatter->sclk_sel);
		अगर (ret != -EPROBE_DEFER)
			dev_err(dev, "failed to get sclk_sel: %d\n", ret);
		वापस ret;
	पूर्ण

	/* Formatter sample घड़ी input multiplexer */
	क्रमmatter->lrclk_sel = devm_clk_get(dev, "lrclk_sel");
	अगर (IS_ERR(क्रमmatter->lrclk_sel)) अणु
		ret = PTR_ERR(क्रमmatter->lrclk_sel);
		अगर (ret != -EPROBE_DEFER)
			dev_err(dev, "failed to get lrclk_sel: %d\n", ret);
		वापस ret;
	पूर्ण

	/* Formatter dedicated reset line */
	क्रमmatter->reset = devm_reset_control_get_optional_exclusive(dev, शून्य);
	अगर (IS_ERR(क्रमmatter->reset)) अणु
		ret = PTR_ERR(क्रमmatter->reset);
		अगर (ret != -EPROBE_DEFER)
			dev_err(dev, "failed to get reset: %d\n", ret);
		वापस ret;
	पूर्ण

	वापस devm_snd_soc_रेजिस्टर_component(dev, drv->component_drv,
					       शून्य, 0);
पूर्ण
EXPORT_SYMBOL_GPL(axg_tdm_क्रमmatter_probe);

पूर्णांक axg_tdm_stream_start(काष्ठा axg_tdm_stream *ts)
अणु
	काष्ठा axg_tdm_क्रमmatter *क्रमmatter;
	पूर्णांक ret = 0;

	mutex_lock(&ts->lock);
	ts->पढ़ोy = true;

	/* Start all the क्रमmatters attached to the stream */
	list_क्रम_each_entry(क्रमmatter, &ts->क्रमmatter_list, list) अणु
		ret = axg_tdm_क्रमmatter_enable(क्रमmatter);
		अगर (ret) अणु
			pr_err("failed to start tdm stream\n");
			जाओ out;
		पूर्ण
	पूर्ण

out:
	mutex_unlock(&ts->lock);
	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(axg_tdm_stream_start);

व्योम axg_tdm_stream_stop(काष्ठा axg_tdm_stream *ts)
अणु
	काष्ठा axg_tdm_क्रमmatter *क्रमmatter;

	mutex_lock(&ts->lock);
	ts->पढ़ोy = false;

	/* Stop all the क्रमmatters attached to the stream */
	list_क्रम_each_entry(क्रमmatter, &ts->क्रमmatter_list, list) अणु
		axg_tdm_क्रमmatter_disable(क्रमmatter);
	पूर्ण

	mutex_unlock(&ts->lock);
पूर्ण
EXPORT_SYMBOL_GPL(axg_tdm_stream_stop);

काष्ठा axg_tdm_stream *axg_tdm_stream_alloc(काष्ठा axg_tdm_अगरace *अगरace)
अणु
	काष्ठा axg_tdm_stream *ts;

	ts = kzalloc(माप(*ts), GFP_KERNEL);
	अगर (ts) अणु
		INIT_LIST_HEAD(&ts->क्रमmatter_list);
		mutex_init(&ts->lock);
		ts->अगरace = अगरace;
	पूर्ण

	वापस ts;
पूर्ण
EXPORT_SYMBOL_GPL(axg_tdm_stream_alloc);

व्योम axg_tdm_stream_मुक्त(काष्ठा axg_tdm_stream *ts)
अणु
	/*
	 * If the list is not empty, it would mean that one of the क्रमmatter
	 * widget is still घातered and attached to the पूर्णांकerface जबतक we
	 * are removing the TDM DAI. It should not be possible
	 */
	WARN_ON(!list_empty(&ts->क्रमmatter_list));
	mutex_destroy(&ts->lock);
	kमुक्त(ts);
पूर्ण
EXPORT_SYMBOL_GPL(axg_tdm_stream_मुक्त);

MODULE_DESCRIPTION("Amlogic AXG TDM formatter driver");
MODULE_AUTHOR("Jerome Brunet <jbrunet@baylibre.com>");
MODULE_LICENSE("GPL v2");
