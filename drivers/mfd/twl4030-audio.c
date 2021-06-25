<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * MFD driver क्रम twl4030 audio submodule, which contains an audio codec, and
 * the vibra control.
 *
 * Author: Peter Ujfalusi <peter.ujfalusi@ti.com>
 *
 * Copyright:   (C) 2009 Nokia Corporation
 */

#समावेश <linux/module.h>
#समावेश <linux/types.h>
#समावेश <linux/slab.h>
#समावेश <linux/kernel.h>
#समावेश <linux/fs.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/of.h>
#समावेश <linux/of_platक्रमm.h>
#समावेश <linux/mfd/twl.h>
#समावेश <linux/mfd/core.h>
#समावेश <linux/mfd/twl4030-audपन.स>

#घोषणा TWL4030_AUDIO_CELLS	2

अटल काष्ठा platक्रमm_device *twl4030_audio_dev;

काष्ठा twl4030_audio_resource अणु
	पूर्णांक request_count;
	u8 reg;
	u8 mask;
पूर्ण;

काष्ठा twl4030_audio अणु
	अचिन्हित पूर्णांक audio_mclk;
	काष्ठा mutex mutex;
	काष्ठा twl4030_audio_resource resource[TWL4030_AUDIO_RES_MAX];
	काष्ठा mfd_cell cells[TWL4030_AUDIO_CELLS];
पूर्ण;

/*
 * Modअगरy the resource, the function वापसs the content of the रेजिस्टर
 * after the modअगरication.
 */
अटल पूर्णांक twl4030_audio_set_resource(क्रमागत twl4030_audio_res id, पूर्णांक enable)
अणु
	काष्ठा twl4030_audio *audio = platक्रमm_get_drvdata(twl4030_audio_dev);
	u8 val;

	twl_i2c_पढ़ो_u8(TWL4030_MODULE_AUDIO_VOICE, &val,
			audio->resource[id].reg);

	अगर (enable)
		val |= audio->resource[id].mask;
	अन्यथा
		val &= ~audio->resource[id].mask;

	twl_i2c_ग_लिखो_u8(TWL4030_MODULE_AUDIO_VOICE,
					val, audio->resource[id].reg);

	वापस val;
पूर्ण

अटल अंतरभूत पूर्णांक twl4030_audio_get_resource(क्रमागत twl4030_audio_res id)
अणु
	काष्ठा twl4030_audio *audio = platक्रमm_get_drvdata(twl4030_audio_dev);
	u8 val;

	twl_i2c_पढ़ो_u8(TWL4030_MODULE_AUDIO_VOICE, &val,
			audio->resource[id].reg);

	वापस val;
पूर्ण

/*
 * Enable the resource.
 * The function वापसs with error or the content of the रेजिस्टर
 */
पूर्णांक twl4030_audio_enable_resource(क्रमागत twl4030_audio_res id)
अणु
	काष्ठा twl4030_audio *audio = platक्रमm_get_drvdata(twl4030_audio_dev);
	पूर्णांक val;

	अगर (id >= TWL4030_AUDIO_RES_MAX) अणु
		dev_err(&twl4030_audio_dev->dev,
				"Invalid resource ID (%u)\n", id);
		वापस -EINVAL;
	पूर्ण

	mutex_lock(&audio->mutex);
	अगर (!audio->resource[id].request_count)
		/* Resource was disabled, enable it */
		val = twl4030_audio_set_resource(id, 1);
	अन्यथा
		val = twl4030_audio_get_resource(id);

	audio->resource[id].request_count++;
	mutex_unlock(&audio->mutex);

	वापस val;
पूर्ण
EXPORT_SYMBOL_GPL(twl4030_audio_enable_resource);

/*
 * Disable the resource.
 * The function वापसs with error or the content of the रेजिस्टर
 */
पूर्णांक twl4030_audio_disable_resource(क्रमागत twl4030_audio_res id)
अणु
	काष्ठा twl4030_audio *audio = platक्रमm_get_drvdata(twl4030_audio_dev);
	पूर्णांक val;

	अगर (id >= TWL4030_AUDIO_RES_MAX) अणु
		dev_err(&twl4030_audio_dev->dev,
				"Invalid resource ID (%u)\n", id);
		वापस -EINVAL;
	पूर्ण

	mutex_lock(&audio->mutex);
	अगर (!audio->resource[id].request_count) अणु
		dev_err(&twl4030_audio_dev->dev,
			"Resource has been disabled already (%u)\n", id);
		mutex_unlock(&audio->mutex);
		वापस -EPERM;
	पूर्ण
	audio->resource[id].request_count--;

	अगर (!audio->resource[id].request_count)
		/* Resource can be disabled now */
		val = twl4030_audio_set_resource(id, 0);
	अन्यथा
		val = twl4030_audio_get_resource(id);

	mutex_unlock(&audio->mutex);

	वापस val;
पूर्ण
EXPORT_SYMBOL_GPL(twl4030_audio_disable_resource);

अचिन्हित पूर्णांक twl4030_audio_get_mclk(व्योम)
अणु
	काष्ठा twl4030_audio *audio = platक्रमm_get_drvdata(twl4030_audio_dev);

	वापस audio->audio_mclk;
पूर्ण
EXPORT_SYMBOL_GPL(twl4030_audio_get_mclk);

अटल bool twl4030_audio_has_codec(काष्ठा twl4030_audio_data *pdata,
			      काष्ठा device_node *parent)
अणु
	काष्ठा device_node *node;

	अगर (pdata && pdata->codec)
		वापस true;

	node = of_get_child_by_name(parent, "codec");
	अगर (node) अणु
		of_node_put(node);
		वापस true;
	पूर्ण

	वापस false;
पूर्ण

अटल bool twl4030_audio_has_vibra(काष्ठा twl4030_audio_data *pdata,
			      काष्ठा device_node *node)
अणु
	पूर्णांक vibra;

	अगर (pdata && pdata->vibra)
		वापस true;

	अगर (!of_property_पढ़ो_u32(node, "ti,enable-vibra", &vibra) && vibra)
		वापस true;

	वापस false;
पूर्ण

अटल पूर्णांक twl4030_audio_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा twl4030_audio *audio;
	काष्ठा twl4030_audio_data *pdata = dev_get_platdata(&pdev->dev);
	काष्ठा device_node *node = pdev->dev.of_node;
	काष्ठा mfd_cell *cell = शून्य;
	पूर्णांक ret, childs = 0;
	u8 val;

	अगर (!pdata && !node) अणु
		dev_err(&pdev->dev, "Platform data is missing\n");
		वापस -EINVAL;
	पूर्ण

	audio = devm_kzalloc(&pdev->dev, माप(काष्ठा twl4030_audio),
			     GFP_KERNEL);
	अगर (!audio)
		वापस -ENOMEM;

	mutex_init(&audio->mutex);
	audio->audio_mclk = twl_get_hfclk_rate();

	/* Configure APLL_INFREQ and disable APLL अगर enabled */
	चयन (audio->audio_mclk) अणु
	हाल 19200000:
		val = TWL4030_APLL_INFREQ_19200KHZ;
		अवरोध;
	हाल 26000000:
		val = TWL4030_APLL_INFREQ_26000KHZ;
		अवरोध;
	हाल 38400000:
		val = TWL4030_APLL_INFREQ_38400KHZ;
		अवरोध;
	शेष:
		dev_err(&pdev->dev, "Invalid audio_mclk\n");
		वापस -EINVAL;
	पूर्ण
	twl_i2c_ग_लिखो_u8(TWL4030_MODULE_AUDIO_VOICE, val, TWL4030_REG_APLL_CTL);

	/* Codec घातer */
	audio->resource[TWL4030_AUDIO_RES_POWER].reg = TWL4030_REG_CODEC_MODE;
	audio->resource[TWL4030_AUDIO_RES_POWER].mask = TWL4030_CODECPDZ;

	/* PLL */
	audio->resource[TWL4030_AUDIO_RES_APLL].reg = TWL4030_REG_APLL_CTL;
	audio->resource[TWL4030_AUDIO_RES_APLL].mask = TWL4030_APLL_EN;

	अगर (twl4030_audio_has_codec(pdata, node)) अणु
		cell = &audio->cells[childs];
		cell->name = "twl4030-codec";
		अगर (pdata) अणु
			cell->platक्रमm_data = pdata->codec;
			cell->pdata_size = माप(*pdata->codec);
		पूर्ण
		childs++;
	पूर्ण
	अगर (twl4030_audio_has_vibra(pdata, node)) अणु
		cell = &audio->cells[childs];
		cell->name = "twl4030-vibra";
		अगर (pdata) अणु
			cell->platक्रमm_data = pdata->vibra;
			cell->pdata_size = माप(*pdata->vibra);
		पूर्ण
		childs++;
	पूर्ण

	platक्रमm_set_drvdata(pdev, audio);
	twl4030_audio_dev = pdev;

	अगर (childs)
		ret = mfd_add_devices(&pdev->dev, pdev->id, audio->cells,
				      childs, शून्य, 0, शून्य);
	अन्यथा अणु
		dev_err(&pdev->dev, "No platform data found for childs\n");
		ret = -ENODEV;
	पूर्ण

	अगर (ret)
		twl4030_audio_dev = शून्य;

	वापस ret;
पूर्ण

अटल पूर्णांक twl4030_audio_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	mfd_हटाओ_devices(&pdev->dev);
	twl4030_audio_dev = शून्य;

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id twl4030_audio_of_match[] = अणु
	अणु.compatible = "ti,twl4030-audio", पूर्ण,
	अणु पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, twl4030_audio_of_match);

अटल काष्ठा platक्रमm_driver twl4030_audio_driver = अणु
	.driver		= अणु
		.name	= "twl4030-audio",
		.of_match_table = twl4030_audio_of_match,
	पूर्ण,
	.probe		= twl4030_audio_probe,
	.हटाओ		= twl4030_audio_हटाओ,
पूर्ण;

module_platक्रमm_driver(twl4030_audio_driver);

MODULE_AUTHOR("Peter Ujfalusi <peter.ujfalusi@ti.com>");
MODULE_DESCRIPTION("TWL4030 audio block MFD driver");
MODULE_LICENSE("GPL");
MODULE_ALIAS("platform:twl4030-audio");
