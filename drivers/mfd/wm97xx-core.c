<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Wolfson WM97xx -- Core device
 *
 * Copyright (C) 2017 Robert Jarzmik
 *
 * Features:
 *  - an AC97 audio codec
 *  - a touchscreen driver
 *  - a GPIO block
 */

#समावेश <linux/device.h>
#समावेश <linux/mfd/core.h>
#समावेश <linux/mfd/wm97xx.h>
#समावेश <linux/module.h>
#समावेश <linux/regmap.h>
#समावेश <linux/slab.h>
#समावेश <linux/wm97xx.h>
#समावेश <sound/ac97/codec.h>
#समावेश <sound/ac97/compat.h>

#घोषणा WM9705_VENDOR_ID 0x574d4c05
#घोषणा WM9712_VENDOR_ID 0x574d4c12
#घोषणा WM9713_VENDOR_ID 0x574d4c13
#घोषणा WM97xx_VENDOR_ID_MASK 0xffffffff

काष्ठा wm97xx_priv अणु
	काष्ठा regmap *regmap;
	काष्ठा snd_ac97 *ac97;
	काष्ठा device *dev;
	काष्ठा wm97xx_platक्रमm_data codec_pdata;
पूर्ण;

अटल bool wm97xx_पढ़ोable_reg(काष्ठा device *dev, अचिन्हित पूर्णांक reg)
अणु
	चयन (reg) अणु
	हाल AC97_RESET ... AC97_PCM_SURR_DAC_RATE:
	हाल AC97_PCM_LR_ADC_RATE:
	हाल AC97_CENTER_LFE_MASTER:
	हाल AC97_SPDIF ... AC97_LINE1_LEVEL:
	हाल AC97_GPIO_CFG ... 0x5c:
	हाल AC97_CODEC_CLASS_REV ... AC97_PCI_SID:
	हाल 0x74 ... AC97_VENDOR_ID2:
		वापस true;
	शेष:
		वापस false;
	पूर्ण
पूर्ण

अटल bool wm97xx_ग_लिखोable_reg(काष्ठा device *dev, अचिन्हित पूर्णांक reg)
अणु
	चयन (reg) अणु
	हाल AC97_VENDOR_ID1:
	हाल AC97_VENDOR_ID2:
		वापस false;
	शेष:
		वापस wm97xx_पढ़ोable_reg(dev, reg);
	पूर्ण
पूर्ण

अटल स्थिर काष्ठा reg_शेष wm9705_reg_शेषs[] = अणु
	अणु 0x02, 0x8000 पूर्ण,
	अणु 0x04, 0x8000 पूर्ण,
	अणु 0x06, 0x8000 पूर्ण,
	अणु 0x0a, 0x8000 पूर्ण,
	अणु 0x0c, 0x8008 पूर्ण,
	अणु 0x0e, 0x8008 पूर्ण,
	अणु 0x10, 0x8808 पूर्ण,
	अणु 0x12, 0x8808 पूर्ण,
	अणु 0x14, 0x8808 पूर्ण,
	अणु 0x16, 0x8808 पूर्ण,
	अणु 0x18, 0x8808 पूर्ण,
	अणु 0x1a, 0x0000 पूर्ण,
	अणु 0x1c, 0x8000 पूर्ण,
	अणु 0x20, 0x0000 पूर्ण,
	अणु 0x22, 0x0000 पूर्ण,
	अणु 0x26, 0x000f पूर्ण,
	अणु 0x28, 0x0605 पूर्ण,
	अणु 0x2a, 0x0000 पूर्ण,
	अणु 0x2c, 0xbb80 पूर्ण,
	अणु 0x32, 0xbb80 पूर्ण,
	अणु 0x34, 0x2000 पूर्ण,
	अणु 0x5a, 0x0000 पूर्ण,
	अणु 0x5c, 0x0000 पूर्ण,
	अणु 0x72, 0x0808 पूर्ण,
	अणु 0x74, 0x0000 पूर्ण,
	अणु 0x76, 0x0006 पूर्ण,
	अणु 0x78, 0x0000 पूर्ण,
	अणु 0x7a, 0x0000 पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा regmap_config wm9705_regmap_config = अणु
	.reg_bits = 16,
	.reg_stride = 2,
	.val_bits = 16,
	.max_रेजिस्टर = 0x7e,
	.cache_type = REGCACHE_RBTREE,

	.reg_शेषs = wm9705_reg_शेषs,
	.num_reg_शेषs = ARRAY_SIZE(wm9705_reg_शेषs),
	.अस्थिर_reg = regmap_ac97_शेष_अस्थिर,
	.पढ़ोable_reg = wm97xx_पढ़ोable_reg,
	.ग_लिखोable_reg = wm97xx_ग_लिखोable_reg,
पूर्ण;

अटल काष्ठा mfd_cell wm9705_cells[] = अणु
	अणु .name = "wm9705-codec", पूर्ण,
	अणु .name = "wm97xx-ts", पूर्ण,
पूर्ण;

अटल bool wm9712_अस्थिर_reg(काष्ठा device *dev, अचिन्हित पूर्णांक reg)
अणु
	चयन (reg) अणु
	हाल AC97_REC_GAIN:
		वापस true;
	शेष:
		वापस regmap_ac97_शेष_अस्थिर(dev, reg);
	पूर्ण
पूर्ण

अटल स्थिर काष्ठा reg_शेष wm9712_reg_शेषs[] = अणु
	अणु 0x02, 0x8000 पूर्ण,
	अणु 0x04, 0x8000 पूर्ण,
	अणु 0x06, 0x8000 पूर्ण,
	अणु 0x08, 0x0f0f पूर्ण,
	अणु 0x0a, 0xaaa0 पूर्ण,
	अणु 0x0c, 0xc008 पूर्ण,
	अणु 0x0e, 0x6808 पूर्ण,
	अणु 0x10, 0xe808 पूर्ण,
	अणु 0x12, 0xaaa0 पूर्ण,
	अणु 0x14, 0xad00 पूर्ण,
	अणु 0x16, 0x8000 पूर्ण,
	अणु 0x18, 0xe808 पूर्ण,
	अणु 0x1a, 0x3000 पूर्ण,
	अणु 0x1c, 0x8000 पूर्ण,
	अणु 0x20, 0x0000 पूर्ण,
	अणु 0x22, 0x0000 पूर्ण,
	अणु 0x26, 0x000f पूर्ण,
	अणु 0x28, 0x0605 पूर्ण,
	अणु 0x2a, 0x0410 पूर्ण,
	अणु 0x2c, 0xbb80 पूर्ण,
	अणु 0x2e, 0xbb80 पूर्ण,
	अणु 0x32, 0xbb80 पूर्ण,
	अणु 0x34, 0x2000 पूर्ण,
	अणु 0x4c, 0xf83e पूर्ण,
	अणु 0x4e, 0xffff पूर्ण,
	अणु 0x50, 0x0000 पूर्ण,
	अणु 0x52, 0x0000 पूर्ण,
	अणु 0x56, 0xf83e पूर्ण,
	अणु 0x58, 0x0008 पूर्ण,
	अणु 0x5c, 0x0000 पूर्ण,
	अणु 0x60, 0xb032 पूर्ण,
	अणु 0x62, 0x3e00 पूर्ण,
	अणु 0x64, 0x0000 पूर्ण,
	अणु 0x76, 0x0006 पूर्ण,
	अणु 0x78, 0x0001 पूर्ण,
	अणु 0x7a, 0x0000 पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा regmap_config wm9712_regmap_config = अणु
	.reg_bits = 16,
	.reg_stride = 2,
	.val_bits = 16,
	.max_रेजिस्टर = 0x7e,
	.cache_type = REGCACHE_RBTREE,

	.reg_शेषs = wm9712_reg_शेषs,
	.num_reg_शेषs = ARRAY_SIZE(wm9712_reg_शेषs),
	.अस्थिर_reg = wm9712_अस्थिर_reg,
	.पढ़ोable_reg = wm97xx_पढ़ोable_reg,
	.ग_लिखोable_reg = wm97xx_ग_लिखोable_reg,
पूर्ण;

अटल काष्ठा mfd_cell wm9712_cells[] = अणु
	अणु .name = "wm9712-codec", पूर्ण,
	अणु .name = "wm97xx-ts", पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा reg_शेष wm9713_reg_शेषs[] = अणु
	अणु 0x02, 0x8080 पूर्ण,	/* Speaker Output Volume */
	अणु 0x04, 0x8080 पूर्ण,	/* Headphone Output Volume */
	अणु 0x06, 0x8080 पूर्ण,	/* Out3/OUT4 Volume */
	अणु 0x08, 0xc880 पूर्ण,	/* Mono Volume */
	अणु 0x0a, 0xe808 पूर्ण,	/* LINEIN Volume */
	अणु 0x0c, 0xe808 पूर्ण,	/* DAC PGA Volume */
	अणु 0x0e, 0x0808 पूर्ण,	/* MIC PGA Volume */
	अणु 0x10, 0x00da पूर्ण,	/* MIC Routing Control */
	अणु 0x12, 0x8000 पूर्ण,	/* Record PGA Volume */
	अणु 0x14, 0xd600 पूर्ण,	/* Record Routing */
	अणु 0x16, 0xaaa0 पूर्ण,	/* PCBEEP Volume */
	अणु 0x18, 0xaaa0 पूर्ण,	/* VxDAC Volume */
	अणु 0x1a, 0xaaa0 पूर्ण,	/* AUXDAC Volume */
	अणु 0x1c, 0x0000 पूर्ण,	/* Output PGA Mux */
	अणु 0x1e, 0x0000 पूर्ण,	/* DAC 3D control */
	अणु 0x20, 0x0f0f पूर्ण,	/* DAC Tone Control*/
	अणु 0x22, 0x0040 पूर्ण,	/* MIC Input Select & Bias */
	अणु 0x24, 0x0000 पूर्ण,	/* Output Volume Mapping & Jack */
	अणु 0x26, 0x7f00 पूर्ण,	/* Powerकरोwn Ctrl/Stat*/
	अणु 0x28, 0x0405 पूर्ण,	/* Extended Audio ID */
	अणु 0x2a, 0x0410 पूर्ण,	/* Extended Audio Start/Ctrl */
	अणु 0x2c, 0xbb80 पूर्ण,	/* Audio DACs Sample Rate */
	अणु 0x2e, 0xbb80 पूर्ण,	/* AUXDAC Sample Rate */
	अणु 0x32, 0xbb80 पूर्ण,	/* Audio ADCs Sample Rate */
	अणु 0x36, 0x4523 पूर्ण,	/* PCM codec control */
	अणु 0x3a, 0x2000 पूर्ण,	/* SPDIF control */
	अणु 0x3c, 0xfdff पूर्ण,	/* Powerकरोwn 1 */
	अणु 0x3e, 0xffff पूर्ण,	/* Powerकरोwn 2 */
	अणु 0x40, 0x0000 पूर्ण,	/* General Purpose */
	अणु 0x42, 0x0000 पूर्ण,	/* Fast Power-Up Control */
	अणु 0x44, 0x0080 पूर्ण,	/* MCLK/PLL Control */
	अणु 0x46, 0x0000 पूर्ण,	/* MCLK/PLL Control */

	अणु 0x4c, 0xfffe पूर्ण,	/* GPIO Pin Configuration */
	अणु 0x4e, 0xffff पूर्ण,	/* GPIO Pin Polarity / Type */
	अणु 0x50, 0x0000 पूर्ण,	/* GPIO Pin Sticky */
	अणु 0x52, 0x0000 पूर्ण,	/* GPIO Pin Wake-Up */
				/* GPIO Pin Status */
	अणु 0x56, 0xfffe पूर्ण,	/* GPIO Pin Sharing */
	अणु 0x58, 0x4000 पूर्ण,	/* GPIO PullUp/PullDown */
	अणु 0x5a, 0x0000 पूर्ण,	/* Additional Functions 1 */
	अणु 0x5c, 0x0000 पूर्ण,	/* Additional Functions 2 */
	अणु 0x60, 0xb032 पूर्ण,	/* ALC Control */
	अणु 0x62, 0x3e00 पूर्ण,	/* ALC / Noise Gate Control */
	अणु 0x64, 0x0000 पूर्ण,	/* AUXDAC input control */
	अणु 0x74, 0x0000 पूर्ण,	/* Digitiser Reg 1 */
	अणु 0x76, 0x0006 पूर्ण,	/* Digitiser Reg 2 */
	अणु 0x78, 0x0001 पूर्ण,	/* Digitiser Reg 3 */
	अणु 0x7a, 0x0000 पूर्ण,	/* Digitiser Read Back */
पूर्ण;

अटल स्थिर काष्ठा regmap_config wm9713_regmap_config = अणु
	.reg_bits = 16,
	.reg_stride = 2,
	.val_bits = 16,
	.max_रेजिस्टर = 0x7e,
	.cache_type = REGCACHE_RBTREE,

	.reg_शेषs = wm9713_reg_शेषs,
	.num_reg_शेषs = ARRAY_SIZE(wm9713_reg_शेषs),
	.अस्थिर_reg = regmap_ac97_शेष_अस्थिर,
	.पढ़ोable_reg = wm97xx_पढ़ोable_reg,
	.ग_लिखोable_reg = wm97xx_ग_लिखोable_reg,
पूर्ण;

अटल काष्ठा mfd_cell wm9713_cells[] = अणु
	अणु .name = "wm9713-codec", पूर्ण,
	अणु .name = "wm97xx-ts", पूर्ण,
पूर्ण;

अटल पूर्णांक wm97xx_ac97_probe(काष्ठा ac97_codec_device *adev)
अणु
	काष्ठा wm97xx_priv *wm97xx;
	स्थिर काष्ठा regmap_config *config;
	काष्ठा wm97xx_platक्रमm_data *codec_pdata;
	काष्ठा mfd_cell *cells;
	पूर्णांक ret = -ENODEV, nb_cells, i;
	काष्ठा wm97xx_pdata *pdata = snd_ac97_codec_get_platdata(adev);

	wm97xx = devm_kzalloc(ac97_codec_dev2dev(adev),
			      माप(*wm97xx), GFP_KERNEL);
	अगर (!wm97xx)
		वापस -ENOMEM;

	wm97xx->dev = ac97_codec_dev2dev(adev);
	wm97xx->ac97 = snd_ac97_compat_alloc(adev);
	अगर (IS_ERR(wm97xx->ac97))
		वापस PTR_ERR(wm97xx->ac97);


	ac97_set_drvdata(adev, wm97xx);
	dev_info(wm97xx->dev, "wm97xx core found, id=0x%x\n",
		 adev->venकरोr_id);

	codec_pdata = &wm97xx->codec_pdata;
	codec_pdata->ac97 = wm97xx->ac97;
	codec_pdata->batt_pdata = pdata ? pdata->batt_pdata : शून्य;

	चयन (adev->venकरोr_id) अणु
	हाल WM9705_VENDOR_ID:
		config = &wm9705_regmap_config;
		cells = wm9705_cells;
		nb_cells = ARRAY_SIZE(wm9705_cells);
		अवरोध;
	हाल WM9712_VENDOR_ID:
		config = &wm9712_regmap_config;
		cells = wm9712_cells;
		nb_cells = ARRAY_SIZE(wm9712_cells);
		अवरोध;
	हाल WM9713_VENDOR_ID:
		config = &wm9713_regmap_config;
		cells = wm9713_cells;
		nb_cells = ARRAY_SIZE(wm9713_cells);
		अवरोध;
	शेष:
		जाओ err_मुक्त_compat;
	पूर्ण

	क्रम (i = 0; i < nb_cells; i++) अणु
		cells[i].platक्रमm_data = codec_pdata;
		cells[i].pdata_size = माप(*codec_pdata);
	पूर्ण

	codec_pdata->regmap = devm_regmap_init_ac97(wm97xx->ac97, config);
	अगर (IS_ERR(codec_pdata->regmap)) अणु
		ret = PTR_ERR(codec_pdata->regmap);
		जाओ err_मुक्त_compat;
	पूर्ण

	ret = devm_mfd_add_devices(wm97xx->dev, PLATFORM_DEVID_NONE,
				   cells, nb_cells, शून्य, 0, शून्य);
	अगर (ret)
		जाओ err_मुक्त_compat;

	वापस ret;

err_मुक्त_compat:
	snd_ac97_compat_release(wm97xx->ac97);
	वापस ret;
पूर्ण

अटल पूर्णांक wm97xx_ac97_हटाओ(काष्ठा ac97_codec_device *adev)
अणु
	काष्ठा wm97xx_priv *wm97xx = ac97_get_drvdata(adev);

	snd_ac97_compat_release(wm97xx->ac97);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा ac97_id wm97xx_ac97_ids[] = अणु
	अणु .id = WM9705_VENDOR_ID, .mask = WM97xx_VENDOR_ID_MASK पूर्ण,
	अणु .id = WM9712_VENDOR_ID, .mask = WM97xx_VENDOR_ID_MASK पूर्ण,
	अणु .id = WM9713_VENDOR_ID, .mask = WM97xx_VENDOR_ID_MASK पूर्ण,
	अणु पूर्ण
पूर्ण;

अटल काष्ठा ac97_codec_driver wm97xx_ac97_driver = अणु
	.driver = अणु
		.name = "wm97xx-core",
	पूर्ण,
	.probe		= wm97xx_ac97_probe,
	.हटाओ		= wm97xx_ac97_हटाओ,
	.id_table	= wm97xx_ac97_ids,
पूर्ण;

अटल पूर्णांक __init wm97xx_module_init(व्योम)
अणु
	वापस snd_ac97_codec_driver_रेजिस्टर(&wm97xx_ac97_driver);
पूर्ण
module_init(wm97xx_module_init);

अटल व्योम __निकास wm97xx_module_निकास(व्योम)
अणु
	snd_ac97_codec_driver_unरेजिस्टर(&wm97xx_ac97_driver);
पूर्ण
module_निकास(wm97xx_module_निकास);

MODULE_DESCRIPTION("WM9712, WM9713 core driver");
MODULE_AUTHOR("Robert Jarzmik <robert.jarzmik@free.fr>");
MODULE_LICENSE("GPL");

