<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
// Copyright (c) 2018-2020, Intel Corporation
//
// sof-wm8804.c - ASoC machine driver क्रम Up and Up2 board
// based on WM8804/Hअगरiberry Digi+


#समावेश <linux/acpi.h>
#समावेश <linux/dmi.h>
#समावेश <linux/gpio/consumer.h>
#समावेश <linux/gpio/machine.h>
#समावेश <linux/module.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/slab.h>
#समावेश <sound/pcm.h>
#समावेश <sound/pcm_params.h>
#समावेश <sound/soc.h>
#समावेश <sound/soc-acpi.h>
#समावेश "../../codecs/wm8804.h"

काष्ठा sof_card_निजी अणु
	काष्ठा gpio_desc *gpio_44;
	काष्ठा gpio_desc *gpio_48;
	पूर्णांक sample_rate;
पूर्ण;

#घोषणा SOF_WM8804_UP2_QUIRK			BIT(0)

अटल अचिन्हित दीर्घ sof_wm8804_quirk;

अटल पूर्णांक sof_wm8804_quirk_cb(स्थिर काष्ठा dmi_प्रणाली_id *id)
अणु
	sof_wm8804_quirk = (अचिन्हित दीर्घ)id->driver_data;
	वापस 1;
पूर्ण

अटल स्थिर काष्ठा dmi_प्रणाली_id sof_wm8804_quirk_table[] = अणु
	अणु
		.callback = sof_wm8804_quirk_cb,
		.matches = अणु
			DMI_MATCH(DMI_SYS_VENDOR, "AAEON"),
			DMI_MATCH(DMI_PRODUCT_NAME, "UP-APL01"),
		पूर्ण,
		.driver_data = (व्योम *)SOF_WM8804_UP2_QUIRK,
	पूर्ण,
	अणुपूर्ण
पूर्ण;

अटल पूर्णांक sof_wm8804_hw_params(काष्ठा snd_pcm_substream *substream,
				काष्ठा snd_pcm_hw_params *params)
अणु
	काष्ठा snd_soc_pcm_runसमय *rtd = asoc_substream_to_rtd(substream);
	काष्ठा sof_card_निजी *ctx = snd_soc_card_get_drvdata(rtd->card);
	काष्ठा snd_soc_dai *codec_dai = asoc_rtd_to_codec(rtd, 0);
	काष्ठा snd_soc_component *codec = codec_dai->component;
	स्थिर पूर्णांक sysclk = 27000000; /* This is fixed on this board */
	पूर्णांक samplerate;
	दीर्घ mclk_freq;
	पूर्णांक mclk_भाग;
	पूर्णांक sampling_freq;
	bool clk_44;
	पूर्णांक ret;

	samplerate = params_rate(params);
	अगर (samplerate == ctx->sample_rate)
		वापस 0;

	ctx->sample_rate = 0;

	अगर (samplerate <= 96000) अणु
		mclk_freq = samplerate * 256;
		mclk_भाग = WM8804_MCLKDIV_256FS;
	पूर्ण अन्यथा अणु
		mclk_freq = samplerate * 128;
		mclk_भाग = WM8804_MCLKDIV_128FS;
	पूर्ण

	चयन (samplerate) अणु
	हाल 32000:
		sampling_freq = 0x03;
		अवरोध;
	हाल 44100:
		sampling_freq = 0x00;
		अवरोध;
	हाल 48000:
		sampling_freq = 0x02;
		अवरोध;
	हाल 88200:
		sampling_freq = 0x08;
		अवरोध;
	हाल 96000:
		sampling_freq = 0x0a;
		अवरोध;
	हाल 176400:
		sampling_freq = 0x0c;
		अवरोध;
	हाल 192000:
		sampling_freq = 0x0e;
		अवरोध;
	शेष:
		dev_err(rtd->card->dev,
			"unsupported samplerate %d\n", samplerate);
		वापस -EINVAL;
	पूर्ण

	अगर (samplerate % 16000)
		clk_44 = true; /* use 44.1 kHz root frequency */
	अन्यथा
		clk_44 = false;

	अगर (!(IS_ERR_OR_शून्य(ctx->gpio_44) ||
	      IS_ERR_OR_शून्य(ctx->gpio_48))) अणु
		/*
		 * ensure both GPIOs are LOW first, then drive the
		 * relevant one to HIGH
		 */
		अगर (clk_44) अणु
			gpiod_set_value_cansleep(ctx->gpio_48, !clk_44);
			gpiod_set_value_cansleep(ctx->gpio_44, clk_44);
		पूर्ण अन्यथा अणु
			gpiod_set_value_cansleep(ctx->gpio_44, clk_44);
			gpiod_set_value_cansleep(ctx->gpio_48, !clk_44);
		पूर्ण
	पूर्ण

	snd_soc_dai_set_clkभाग(codec_dai, WM8804_MCLK_DIV, mclk_भाग);
	ret = snd_soc_dai_set_pll(codec_dai, 0, 0, sysclk, mclk_freq);
	अगर (ret < 0) अणु
		dev_err(rtd->card->dev, "Failed to set WM8804 PLL\n");
		वापस ret;
	पूर्ण

	ret = snd_soc_dai_set_sysclk(codec_dai, WM8804_TX_CLKSRC_PLL,
				     sysclk, SND_SOC_CLOCK_OUT);
	अगर (ret < 0) अणु
		dev_err(rtd->card->dev,
			"Failed to set WM8804 SYSCLK: %d\n", ret);
		वापस ret;
	पूर्ण

	/* set sampling frequency status bits */
	snd_soc_component_update_bits(codec, WM8804_SPDTX4, 0x0f,
				      sampling_freq);

	ctx->sample_rate = samplerate;

	वापस 0;
पूर्ण

/* machine stream operations */
अटल काष्ठा snd_soc_ops sof_wm8804_ops = अणु
	.hw_params = sof_wm8804_hw_params,
पूर्ण;

SND_SOC_DAILINK_DEF(ssp5_pin,
	DAILINK_COMP_ARRAY(COMP_CPU("SSP5 Pin")));

SND_SOC_DAILINK_DEF(ssp5_codec,
	DAILINK_COMP_ARRAY(COMP_CODEC("i2c-1AEC8804:00", "wm8804-spdif")));

SND_SOC_DAILINK_DEF(platक्रमm,
	DAILINK_COMP_ARRAY(COMP_PLATFORM("0000:00:0e.0")));

अटल काष्ठा snd_soc_dai_link dailink[] = अणु
	/* back ends */
	अणु
		.name = "SSP5-Codec",
		.id = 0,
		.no_pcm = 1,
		.nonatomic = true,
		.dpcm_playback = 1,
		.dpcm_capture = 1,
		.ops = &sof_wm8804_ops,
		SND_SOC_DAILINK_REG(ssp5_pin, ssp5_codec, platक्रमm),
	पूर्ण,
पूर्ण;

/* SoC card */
अटल काष्ठा snd_soc_card sof_wm8804_card = अणु
	.name = "wm8804", /* sof- prefix added स्वतःmatically */
	.owner = THIS_MODULE,
	.dai_link = dailink,
	.num_links = ARRAY_SIZE(dailink),
पूर्ण;

 /* i2c-<HID>:00 with HID being 8 अक्षरs */
अटल अक्षर codec_name[SND_ACPI_I2C_ID_LEN];

/*
 * to control the HअगरiBerry Digi+ PRO, it's required to toggle GPIO to
 * select the घड़ी source. On the Up2 board, this means
 * Pin29/BCM5/Linux GPIO 430 and Pin 31/BCM6/ Linux GPIO 404.
 *
 * Using the ACPI device name is not very nice, but since we only use
 * the value क्रम the Up2 board there is no risk of conflict with other
 * platक्रमms.
 */

अटल काष्ठा gpiod_lookup_table up2_gpios_table = अणु
	/* .dev_id is set during probe */
	.table = अणु
		GPIO_LOOKUP("INT3452:01", 73, "BCM-GPIO5", GPIO_ACTIVE_HIGH),
		GPIO_LOOKUP("INT3452:01", 74, "BCM-GPIO6", GPIO_ACTIVE_HIGH),
		अणु पूर्ण,
	पूर्ण,
पूर्ण;

अटल पूर्णांक sof_wm8804_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा snd_soc_card *card;
	काष्ठा snd_soc_acpi_mach *mach;
	काष्ठा sof_card_निजी *ctx;
	काष्ठा acpi_device *adev;
	पूर्णांक dai_index = 0;
	पूर्णांक ret;
	पूर्णांक i;

	ctx = devm_kzalloc(&pdev->dev, माप(*ctx), GFP_KERNEL);
	अगर (!ctx)
		वापस -ENOMEM;

	mach = pdev->dev.platक्रमm_data;
	card = &sof_wm8804_card;
	card->dev = &pdev->dev;

	dmi_check_प्रणाली(sof_wm8804_quirk_table);

	अगर (sof_wm8804_quirk & SOF_WM8804_UP2_QUIRK) अणु
		up2_gpios_table.dev_id = dev_name(&pdev->dev);
		gpiod_add_lookup_table(&up2_gpios_table);

		/*
		 * The gpios are required क्रम specअगरic boards with
		 * local oscillators, and optional in other हालs.
		 * Since we can't identअगरy when they are needed, use
		 * the GPIO as non-optional
		 */

		ctx->gpio_44 = devm_gpiod_get(&pdev->dev, "BCM-GPIO5",
					      GPIOD_OUT_LOW);
		अगर (IS_ERR(ctx->gpio_44)) अणु
			ret = PTR_ERR(ctx->gpio_44);
			dev_err(&pdev->dev,
				"could not get BCM-GPIO5: %d\n",
				ret);
			वापस ret;
		पूर्ण

		ctx->gpio_48 = devm_gpiod_get(&pdev->dev, "BCM-GPIO6",
					      GPIOD_OUT_LOW);
		अगर (IS_ERR(ctx->gpio_48)) अणु
			ret = PTR_ERR(ctx->gpio_48);
			dev_err(&pdev->dev,
				"could not get BCM-GPIO6: %d\n",
				ret);
			वापस ret;
		पूर्ण
	पूर्ण

	/* fix index of codec dai */
	क्रम (i = 0; i < ARRAY_SIZE(dailink); i++) अणु
		अगर (!म_भेद(dailink[i].codecs->name, "i2c-1AEC8804:00")) अणु
			dai_index = i;
			अवरोध;
		पूर्ण
	पूर्ण

	/* fixup codec name based on HID */
	adev = acpi_dev_get_first_match_dev(mach->id, शून्य, -1);
	अगर (adev) अणु
		snम_लिखो(codec_name, माप(codec_name),
			 "%s%s", "i2c-", acpi_dev_name(adev));
		put_device(&adev->dev);
		dailink[dai_index].codecs->name = codec_name;
	पूर्ण

	snd_soc_card_set_drvdata(card, ctx);

	वापस devm_snd_soc_रेजिस्टर_card(&pdev->dev, card);
पूर्ण

अटल पूर्णांक sof_wm8804_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	अगर (sof_wm8804_quirk & SOF_WM8804_UP2_QUIRK)
		gpiod_हटाओ_lookup_table(&up2_gpios_table);
	वापस 0;
पूर्ण

अटल काष्ठा platक्रमm_driver sof_wm8804_driver = अणु
	.driver = अणु
		.name = "sof-wm8804",
		.pm = &snd_soc_pm_ops,
	पूर्ण,
	.probe = sof_wm8804_probe,
	.हटाओ = sof_wm8804_हटाओ,
पूर्ण;
module_platक्रमm_driver(sof_wm8804_driver);

MODULE_DESCRIPTION("ASoC Intel(R) SOF + WM8804 Machine driver");
MODULE_AUTHOR("Pierre-Louis Bossart");
MODULE_LICENSE("GPL v2");
MODULE_ALIAS("platform:sof-wm8804");
