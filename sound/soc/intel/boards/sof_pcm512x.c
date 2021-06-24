<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
// Copyright(c) 2018-2020 Intel Corporation.

/*
 * Intel SOF Machine Driver क्रम Intel platक्रमms with TI PCM512x codec,
 * e.g. Up or Up2 with Hअगरiberry DAC+ HAT
 */
#समावेश <linux/clk.h>
#समावेश <linux/dmi.h>
#समावेश <linux/i2c.h>
#समावेश <linux/input.h>
#समावेश <linux/module.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/types.h>
#समावेश <sound/core.h>
#समावेश <sound/jack.h>
#समावेश <sound/pcm.h>
#समावेश <sound/pcm_params.h>
#समावेश <sound/soc.h>
#समावेश <sound/soc-acpi.h>
#समावेश "../../codecs/pcm512x.h"
#समावेश "../common/soc-intel-quirks.h"
#समावेश "hda_dsp_common.h"

#घोषणा NAME_SIZE 32

#घोषणा SOF_PCM512X_SSP_CODEC(quirk)		((quirk) & GENMASK(3, 0))
#घोषणा SOF_PCM512X_SSP_CODEC_MASK			(GENMASK(3, 0))

#घोषणा IDISP_CODEC_MASK	0x4

/* Default: SSP5 */
अटल अचिन्हित दीर्घ sof_pcm512x_quirk = SOF_PCM512X_SSP_CODEC(5);

अटल bool is_legacy_cpu;

काष्ठा sof_hdmi_pcm अणु
	काष्ठा list_head head;
	काष्ठा snd_soc_dai *codec_dai;
	पूर्णांक device;
पूर्ण;

काष्ठा sof_card_निजी अणु
	काष्ठा list_head hdmi_pcm_list;
	bool idisp_codec;
पूर्ण;

अटल पूर्णांक sof_pcm512x_quirk_cb(स्थिर काष्ठा dmi_प्रणाली_id *id)
अणु
	sof_pcm512x_quirk = (अचिन्हित दीर्घ)id->driver_data;
	वापस 1;
पूर्ण

अटल स्थिर काष्ठा dmi_प्रणाली_id sof_pcm512x_quirk_table[] = अणु
	अणु
		.callback = sof_pcm512x_quirk_cb,
		.matches = अणु
			DMI_MATCH(DMI_SYS_VENDOR, "AAEON"),
			DMI_MATCH(DMI_PRODUCT_NAME, "UP-CHT01"),
		पूर्ण,
		.driver_data = (व्योम *)(SOF_PCM512X_SSP_CODEC(2)),
	पूर्ण,
	अणुपूर्ण
पूर्ण;

अटल पूर्णांक sof_hdmi_init(काष्ठा snd_soc_pcm_runसमय *rtd)
अणु
	काष्ठा sof_card_निजी *ctx = snd_soc_card_get_drvdata(rtd->card);
	काष्ठा snd_soc_dai *dai = asoc_rtd_to_codec(rtd, 0);
	काष्ठा sof_hdmi_pcm *pcm;

	pcm = devm_kzalloc(rtd->card->dev, माप(*pcm), GFP_KERNEL);
	अगर (!pcm)
		वापस -ENOMEM;

	/* dai_link id is 1:1 mapped to the PCM device */
	pcm->device = rtd->dai_link->id;
	pcm->codec_dai = dai;

	list_add_tail(&pcm->head, &ctx->hdmi_pcm_list);

	वापस 0;
पूर्ण

अटल पूर्णांक sof_pcm512x_codec_init(काष्ठा snd_soc_pcm_runसमय *rtd)
अणु
	काष्ठा snd_soc_component *codec = asoc_rtd_to_codec(rtd, 0)->component;

	snd_soc_component_update_bits(codec, PCM512x_GPIO_EN, 0x08, 0x08);
	snd_soc_component_update_bits(codec, PCM512x_GPIO_OUTPUT_4, 0x0f, 0x02);
	snd_soc_component_update_bits(codec, PCM512x_GPIO_CONTROL_1,
				      0x08, 0x08);

	वापस 0;
पूर्ण

अटल पूर्णांक aअगर1_startup(काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा snd_soc_pcm_runसमय *rtd = asoc_substream_to_rtd(substream);
	काष्ठा snd_soc_component *codec = asoc_rtd_to_codec(rtd, 0)->component;

	snd_soc_component_update_bits(codec, PCM512x_GPIO_CONTROL_1,
				      0x08, 0x08);

	वापस 0;
पूर्ण

अटल व्योम aअगर1_shutकरोwn(काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा snd_soc_pcm_runसमय *rtd = asoc_substream_to_rtd(substream);
	काष्ठा snd_soc_component *codec = asoc_rtd_to_codec(rtd, 0)->component;

	snd_soc_component_update_bits(codec, PCM512x_GPIO_CONTROL_1,
				      0x08, 0x00);
पूर्ण

अटल स्थिर काष्ठा snd_soc_ops sof_pcm512x_ops = अणु
	.startup = aअगर1_startup,
	.shutकरोwn = aअगर1_shutकरोwn,
पूर्ण;

अटल काष्ठा snd_soc_dai_link_component platक्रमm_component[] = अणु
	अणु
		/* name might be overridden during probe */
		.name = "0000:00:1f.3"
	पूर्ण
पूर्ण;

अटल पूर्णांक sof_card_late_probe(काष्ठा snd_soc_card *card)
अणु
	काष्ठा sof_card_निजी *ctx = snd_soc_card_get_drvdata(card);
	काष्ठा sof_hdmi_pcm *pcm;

	/* HDMI is not supported by SOF on Baytrail/CherryTrail */
	अगर (is_legacy_cpu)
		वापस 0;

	अगर (list_empty(&ctx->hdmi_pcm_list))
		वापस -EINVAL;

	अगर (!ctx->idisp_codec)
		वापस 0;

	pcm = list_first_entry(&ctx->hdmi_pcm_list, काष्ठा sof_hdmi_pcm, head);

	वापस hda_dsp_hdmi_build_controls(card, pcm->codec_dai->component);
पूर्ण

अटल स्थिर काष्ठा snd_kcontrol_new sof_controls[] = अणु
	SOC_DAPM_PIN_SWITCH("Ext Spk"),
पूर्ण;

अटल स्थिर काष्ठा snd_soc_dapm_widget sof_widमाला_लो[] = अणु
	SND_SOC_DAPM_SPK("Ext Spk", शून्य),
पूर्ण;

अटल स्थिर काष्ठा snd_soc_dapm_widget dmic_widमाला_लो[] = अणु
	SND_SOC_DAPM_MIC("SoC DMIC", शून्य),
पूर्ण;

अटल स्थिर काष्ठा snd_soc_dapm_route sof_map[] = अणु
	/* Speaker */
	अणु"Ext Spk", शून्य, "OUTR"पूर्ण,
	अणु"Ext Spk", शून्य, "OUTL"पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा snd_soc_dapm_route dmic_map[] = अणु
	/* digital mics */
	अणु"DMic", शून्य, "SoC DMIC"पूर्ण,
पूर्ण;

अटल पूर्णांक dmic_init(काष्ठा snd_soc_pcm_runसमय *rtd)
अणु
	काष्ठा snd_soc_card *card = rtd->card;
	पूर्णांक ret;

	ret = snd_soc_dapm_new_controls(&card->dapm, dmic_widमाला_लो,
					ARRAY_SIZE(dmic_widमाला_लो));
	अगर (ret) अणु
		dev_err(card->dev, "DMic widget addition failed: %d\n", ret);
		/* Don't need to add routes अगर widget addition failed */
		वापस ret;
	पूर्ण

	ret = snd_soc_dapm_add_routes(&card->dapm, dmic_map,
				      ARRAY_SIZE(dmic_map));

	अगर (ret)
		dev_err(card->dev, "DMic map addition failed: %d\n", ret);

	वापस ret;
पूर्ण

/* sof audio machine driver क्रम pcm512x codec */
अटल काष्ठा snd_soc_card sof_audio_card_pcm512x = अणु
	.name = "pcm512x",
	.owner = THIS_MODULE,
	.controls = sof_controls,
	.num_controls = ARRAY_SIZE(sof_controls),
	.dapm_widमाला_लो = sof_widमाला_लो,
	.num_dapm_widमाला_लो = ARRAY_SIZE(sof_widमाला_लो),
	.dapm_routes = sof_map,
	.num_dapm_routes = ARRAY_SIZE(sof_map),
	.fully_routed = true,
	.late_probe = sof_card_late_probe,
पूर्ण;

SND_SOC_DAILINK_DEF(pcm512x_component,
	DAILINK_COMP_ARRAY(COMP_CODEC("i2c-104C5122:00", "pcm512x-hifi")));
SND_SOC_DAILINK_DEF(dmic_component,
	DAILINK_COMP_ARRAY(COMP_CODEC("dmic-codec", "dmic-hifi")));

अटल काष्ठा snd_soc_dai_link *sof_card_dai_links_create(काष्ठा device *dev,
							  पूर्णांक ssp_codec,
							  पूर्णांक dmic_be_num,
							  पूर्णांक hdmi_num,
							  bool idisp_codec)
अणु
	काष्ठा snd_soc_dai_link_component *idisp_components;
	काष्ठा snd_soc_dai_link_component *cpus;
	काष्ठा snd_soc_dai_link *links;
	पूर्णांक i, id = 0;

	links = devm_kसुस्मृति(dev, sof_audio_card_pcm512x.num_links,
			माप(काष्ठा snd_soc_dai_link), GFP_KERNEL);
	cpus = devm_kसुस्मृति(dev, sof_audio_card_pcm512x.num_links,
			माप(काष्ठा snd_soc_dai_link_component), GFP_KERNEL);
	अगर (!links || !cpus)
		जाओ devm_err;

	/* codec SSP */
	links[id].name = devm_kaप्र_लिखो(dev, GFP_KERNEL,
					"SSP%d-Codec", ssp_codec);
	अगर (!links[id].name)
		जाओ devm_err;

	links[id].id = id;
	links[id].codecs = pcm512x_component;
	links[id].num_codecs = ARRAY_SIZE(pcm512x_component);
	links[id].platक्रमms = platक्रमm_component;
	links[id].num_platक्रमms = ARRAY_SIZE(platक्रमm_component);
	links[id].init = sof_pcm512x_codec_init;
	links[id].ops = &sof_pcm512x_ops;
	links[id].nonatomic = true;
	links[id].dpcm_playback = 1;
	/*
	 * capture only supported with specअगरic versions of the Hअगरiberry DAC+
	 * links[id].dpcm_capture = 1;
	 */
	links[id].no_pcm = 1;
	links[id].cpus = &cpus[id];
	links[id].num_cpus = 1;
	अगर (is_legacy_cpu) अणु
		links[id].cpus->dai_name = devm_kaप्र_लिखो(dev, GFP_KERNEL,
							  "ssp%d-port",
							  ssp_codec);
		अगर (!links[id].cpus->dai_name)
			जाओ devm_err;
	पूर्ण अन्यथा अणु
		links[id].cpus->dai_name = devm_kaप्र_लिखो(dev, GFP_KERNEL,
							  "SSP%d Pin",
							  ssp_codec);
		अगर (!links[id].cpus->dai_name)
			जाओ devm_err;
	पूर्ण
	id++;

	/* dmic */
	अगर (dmic_be_num > 0) अणु
		/* at least we have dmic01 */
		links[id].name = "dmic01";
		links[id].cpus = &cpus[id];
		links[id].cpus->dai_name = "DMIC01 Pin";
		links[id].init = dmic_init;
		अगर (dmic_be_num > 1) अणु
			/* set up 2 BE links at most */
			links[id + 1].name = "dmic16k";
			links[id + 1].cpus = &cpus[id + 1];
			links[id + 1].cpus->dai_name = "DMIC16k Pin";
			dmic_be_num = 2;
		पूर्ण
	पूर्ण

	क्रम (i = 0; i < dmic_be_num; i++) अणु
		links[id].id = id;
		links[id].num_cpus = 1;
		links[id].codecs = dmic_component;
		links[id].num_codecs = ARRAY_SIZE(dmic_component);
		links[id].platक्रमms = platक्रमm_component;
		links[id].num_platक्रमms = ARRAY_SIZE(platक्रमm_component);
		links[id].ignore_suspend = 1;
		links[id].dpcm_capture = 1;
		links[id].no_pcm = 1;
		id++;
	पूर्ण

	/* HDMI */
	अगर (hdmi_num > 0) अणु
		idisp_components = devm_kसुस्मृति(dev, hdmi_num,
				माप(काष्ठा snd_soc_dai_link_component),
				GFP_KERNEL);
		अगर (!idisp_components)
			जाओ devm_err;
	पूर्ण
	क्रम (i = 1; i <= hdmi_num; i++) अणु
		links[id].name = devm_kaप्र_लिखो(dev, GFP_KERNEL,
						"iDisp%d", i);
		अगर (!links[id].name)
			जाओ devm_err;

		links[id].id = id;
		links[id].cpus = &cpus[id];
		links[id].num_cpus = 1;
		links[id].cpus->dai_name = devm_kaप्र_लिखो(dev, GFP_KERNEL,
							  "iDisp%d Pin", i);
		अगर (!links[id].cpus->dai_name)
			जाओ devm_err;

		/*
		 * topology cannot be loaded अगर codec is missing, so
		 * use the dummy codec अगर needed
		 */
		अगर (idisp_codec) अणु
			idisp_components[i - 1].name = "ehdaudio0D2";
			idisp_components[i - 1].dai_name =
				devm_kaप्र_लिखो(dev, GFP_KERNEL,
					       "intel-hdmi-hifi%d", i);
		पूर्ण अन्यथा अणु
			idisp_components[i - 1].name = "snd-soc-dummy";
			idisp_components[i - 1].dai_name = "snd-soc-dummy-dai";
		पूर्ण
		अगर (!idisp_components[i - 1].dai_name)
			जाओ devm_err;

		links[id].codecs = &idisp_components[i - 1];
		links[id].num_codecs = 1;
		links[id].platक्रमms = platक्रमm_component;
		links[id].num_platक्रमms = ARRAY_SIZE(platक्रमm_component);
		links[id].init = sof_hdmi_init;
		links[id].dpcm_playback = 1;
		links[id].no_pcm = 1;
		id++;
	पूर्ण

	वापस links;
devm_err:
	वापस शून्य;
पूर्ण

अटल पूर्णांक sof_audio_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा snd_soc_acpi_mach *mach = pdev->dev.platक्रमm_data;
	काष्ठा snd_soc_dai_link *dai_links;
	काष्ठा sof_card_निजी *ctx;
	पूर्णांक dmic_be_num, hdmi_num;
	पूर्णांक ret, ssp_codec;

	ctx = devm_kzalloc(&pdev->dev, माप(*ctx), GFP_KERNEL);
	अगर (!ctx)
		वापस -ENOMEM;

	hdmi_num = 0;
	अगर (soc_पूर्णांकel_is_byt() || soc_पूर्णांकel_is_cht()) अणु
		is_legacy_cpu = true;
		dmic_be_num = 0;
		/* शेष quirk क्रम legacy cpu */
		sof_pcm512x_quirk = SOF_PCM512X_SSP_CODEC(2);
	पूर्ण अन्यथा अणु
		dmic_be_num = 2;
		अगर (mach->mach_params.common_hdmi_codec_drv &&
		    (mach->mach_params.codec_mask & IDISP_CODEC_MASK))
			ctx->idisp_codec = true;

		/* links are always present in topology */
		hdmi_num = 3;
	पूर्ण

	dmi_check_प्रणाली(sof_pcm512x_quirk_table);

	dev_dbg(&pdev->dev, "sof_pcm512x_quirk = %lx\n", sof_pcm512x_quirk);

	ssp_codec = sof_pcm512x_quirk & SOF_PCM512X_SSP_CODEC_MASK;

	/* compute number of dai links */
	sof_audio_card_pcm512x.num_links = 1 + dmic_be_num + hdmi_num;

	dai_links = sof_card_dai_links_create(&pdev->dev, ssp_codec,
					      dmic_be_num, hdmi_num,
					      ctx->idisp_codec);
	अगर (!dai_links)
		वापस -ENOMEM;

	sof_audio_card_pcm512x.dai_link = dai_links;

	INIT_LIST_HEAD(&ctx->hdmi_pcm_list);

	sof_audio_card_pcm512x.dev = &pdev->dev;

	/* set platक्रमm name क्रम each dailink */
	ret = snd_soc_fixup_dai_links_platक्रमm_name(&sof_audio_card_pcm512x,
						    mach->mach_params.platक्रमm);
	अगर (ret)
		वापस ret;

	snd_soc_card_set_drvdata(&sof_audio_card_pcm512x, ctx);

	वापस devm_snd_soc_रेजिस्टर_card(&pdev->dev,
					  &sof_audio_card_pcm512x);
पूर्ण

अटल पूर्णांक sof_pcm512x_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा snd_soc_card *card = platक्रमm_get_drvdata(pdev);
	काष्ठा snd_soc_component *component = शून्य;

	क्रम_each_card_components(card, component) अणु
		अगर (!म_भेद(component->name, pcm512x_component[0].name)) अणु
			snd_soc_component_set_jack(component, शून्य, शून्य);
			अवरोध;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल काष्ठा platक्रमm_driver sof_audio = अणु
	.probe = sof_audio_probe,
	.हटाओ = sof_pcm512x_हटाओ,
	.driver = अणु
		.name = "sof_pcm512x",
		.pm = &snd_soc_pm_ops,
	पूर्ण,
पूर्ण;
module_platक्रमm_driver(sof_audio)

MODULE_DESCRIPTION("ASoC Intel(R) SOF + PCM512x Machine driver");
MODULE_AUTHOR("Pierre-Louis Bossart");
MODULE_LICENSE("GPL v2");
MODULE_ALIAS("platform:sof_pcm512x");
