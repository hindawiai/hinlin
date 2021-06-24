<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
// Copyright(c) 2015-18 Intel Corporation.

/*
 * Machine Driver क्रम SKL+ platक्रमms with DSP and iDisp, HDA Codecs
 */

#समावेश <linux/module.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <sound/core.h>
#समावेश <sound/jack.h>
#समावेश <sound/pcm.h>
#समावेश <sound/pcm_params.h>
#समावेश <sound/soc.h>
#समावेश <sound/soc-acpi.h>
#समावेश "../../codecs/hdac_hdmi.h"
#समावेश "skl_hda_dsp_common.h"

अटल स्थिर काष्ठा snd_soc_dapm_widget skl_hda_widमाला_लो[] = अणु
	SND_SOC_DAPM_HP("Analog Out", शून्य),
	SND_SOC_DAPM_MIC("Analog In", शून्य),
	SND_SOC_DAPM_HP("Alt Analog Out", शून्य),
	SND_SOC_DAPM_MIC("Alt Analog In", शून्य),
	SND_SOC_DAPM_SPK("Digital Out", शून्य),
	SND_SOC_DAPM_MIC("Digital In", शून्य),
	SND_SOC_DAPM_MIC("SoC DMIC", शून्य),
पूर्ण;

अटल स्थिर काष्ठा snd_soc_dapm_route skl_hda_map[] = अणु
	अणु "hifi3", शून्य, "iDisp3 Tx"पूर्ण,
	अणु "iDisp3 Tx", शून्य, "iDisp3_out"पूर्ण,
	अणु "hifi2", शून्य, "iDisp2 Tx"पूर्ण,
	अणु "iDisp2 Tx", शून्य, "iDisp2_out"पूर्ण,
	अणु "hifi1", शून्य, "iDisp1 Tx"पूर्ण,
	अणु "iDisp1 Tx", शून्य, "iDisp1_out"पूर्ण,

	अणु "Analog Out", शून्य, "Codec Output Pin1" पूर्ण,
	अणु "Digital Out", शून्य, "Codec Output Pin2" पूर्ण,
	अणु "Alt Analog Out", शून्य, "Codec Output Pin3" पूर्ण,

	अणु "Codec Input Pin1", शून्य, "Analog In" पूर्ण,
	अणु "Codec Input Pin2", शून्य, "Digital In" पूर्ण,
	अणु "Codec Input Pin3", शून्य, "Alt Analog In" पूर्ण,

	/* digital mics */
	अणु"DMic", शून्य, "SoC DMIC"पूर्ण,

	/* CODEC BE connections */
	अणु "Analog Codec Playback", शून्य, "Analog CPU Playback" पूर्ण,
	अणु "Analog CPU Playback", शून्य, "codec0_out" पूर्ण,
	अणु "Digital Codec Playback", शून्य, "Digital CPU Playback" पूर्ण,
	अणु "Digital CPU Playback", शून्य, "codec1_out" पूर्ण,
	अणु "Alt Analog Codec Playback", शून्य, "Alt Analog CPU Playback" पूर्ण,
	अणु "Alt Analog CPU Playback", शून्य, "codec2_out" पूर्ण,

	अणु "codec0_in", शून्य, "Analog CPU Capture" पूर्ण,
	अणु "Analog CPU Capture", शून्य, "Analog Codec Capture" पूर्ण,
	अणु "codec1_in", शून्य, "Digital CPU Capture" पूर्ण,
	अणु "Digital CPU Capture", शून्य, "Digital Codec Capture" पूर्ण,
	अणु "codec2_in", शून्य, "Alt Analog CPU Capture" पूर्ण,
	अणु "Alt Analog CPU Capture", शून्य, "Alt Analog Codec Capture" पूर्ण,
पूर्ण;

SND_SOC_DAILINK_DEF(dummy_codec,
	DAILINK_COMP_ARRAY(COMP_CODEC("snd-soc-dummy", "snd-soc-dummy-dai")));

अटल पूर्णांक skl_hda_card_late_probe(काष्ठा snd_soc_card *card)
अणु
	वापस skl_hda_hdmi_jack_init(card);
पूर्ण

अटल पूर्णांक
skl_hda_add_dai_link(काष्ठा snd_soc_card *card, काष्ठा snd_soc_dai_link *link)
अणु
	काष्ठा skl_hda_निजी *ctx = snd_soc_card_get_drvdata(card);
	पूर्णांक ret = 0;

	dev_dbg(card->dev, "%s: dai link name - %s\n", __func__, link->name);
	link->platक्रमms->name = ctx->platक्रमm_name;
	link->nonatomic = 1;

	अगर (!ctx->idisp_codec)
		वापस 0;

	अगर (म_माला(link->name, "HDMI")) अणु
		ret = skl_hda_hdmi_add_pcm(card, ctx->pcm_count);

		अगर (ret < 0)
			वापस ret;

		ctx->dai_index++;
	पूर्ण

	ctx->pcm_count++;
	वापस ret;
पूर्ण

अटल काष्ठा snd_soc_card hda_soc_card = अणु
	.name = "hda-dsp",
	.owner = THIS_MODULE,
	.dai_link = skl_hda_be_dai_links,
	.dapm_widमाला_लो = skl_hda_widमाला_लो,
	.dapm_routes = skl_hda_map,
	.add_dai_link = skl_hda_add_dai_link,
	.fully_routed = true,
	.late_probe = skl_hda_card_late_probe,
पूर्ण;

अटल अक्षर hda_soc_components[30];

#घोषणा IDISP_DAI_COUNT		3
#घोषणा HDAC_DAI_COUNT		2
#घोषणा DMIC_DAI_COUNT		2

/* there are two routes per iDisp output */
#घोषणा IDISP_ROUTE_COUNT	(IDISP_DAI_COUNT * 2)
#घोषणा IDISP_CODEC_MASK	0x4

#घोषणा HDA_CODEC_AUTOSUSPEND_DELAY_MS 1000

अटल पूर्णांक skl_hda_fill_card_info(काष्ठा snd_soc_acpi_mach_params *mach_params)
अणु
	काष्ठा snd_soc_card *card = &hda_soc_card;
	काष्ठा skl_hda_निजी *ctx = snd_soc_card_get_drvdata(card);
	काष्ठा snd_soc_dai_link *dai_link;
	u32 codec_count, codec_mask;
	पूर्णांक i, num_links, num_route;

	codec_mask = mach_params->codec_mask;
	codec_count = hweight_दीर्घ(codec_mask);
	ctx->idisp_codec = !!(codec_mask & IDISP_CODEC_MASK);

	अगर (!codec_count || codec_count > 2 ||
	    (codec_count == 2 && !ctx->idisp_codec))
		वापस -EINVAL;

	अगर (codec_mask == IDISP_CODEC_MASK) अणु
		/* topology with iDisp as the only HDA codec */
		num_links = IDISP_DAI_COUNT + DMIC_DAI_COUNT;
		num_route = IDISP_ROUTE_COUNT;

		/*
		 * rearrange the dai link array and make the
		 * dmic dai links follow idsp dai links क्रम only
		 * num_links of dai links need to be रेजिस्टरed
		 * to ASoC.
		 */
		क्रम (i = 0; i < DMIC_DAI_COUNT; i++) अणु
			skl_hda_be_dai_links[IDISP_DAI_COUNT + i] =
				skl_hda_be_dai_links[IDISP_DAI_COUNT +
					HDAC_DAI_COUNT + i];
		पूर्ण
	पूर्ण अन्यथा अणु
		/* topology with बाह्यal and iDisp HDA codecs */
		num_links = ARRAY_SIZE(skl_hda_be_dai_links);
		num_route = ARRAY_SIZE(skl_hda_map);
		card->dapm_widमाला_लो = skl_hda_widमाला_लो;
		card->num_dapm_widमाला_लो = ARRAY_SIZE(skl_hda_widमाला_लो);
		अगर (!ctx->idisp_codec) अणु
			क्रम (i = 0; i < IDISP_DAI_COUNT; i++) अणु
				skl_hda_be_dai_links[i].codecs = dummy_codec;
				skl_hda_be_dai_links[i].num_codecs =
					ARRAY_SIZE(dummy_codec);
			पूर्ण
		पूर्ण
	पूर्ण

	card->num_links = num_links;
	card->num_dapm_routes = num_route;

	क्रम_each_card_prelinks(card, i, dai_link)
		dai_link->platक्रमms->name = mach_params->platक्रमm;

	वापस 0;
पूर्ण

अटल व्योम skl_set_hda_codec_स्वतःsuspend_delay(काष्ठा snd_soc_card *card)
अणु
	काष्ठा snd_soc_pcm_runसमय *rtd;
	काष्ठा hdac_hda_priv *hda_pvt;
	काष्ठा snd_soc_dai *dai;

	क्रम_each_card_rtds(card, rtd) अणु
		अगर (!म_माला(rtd->dai_link->codecs->name, "ehdaudio0D0"))
			जारी;
		dai = asoc_rtd_to_codec(rtd, 0);
		hda_pvt = snd_soc_component_get_drvdata(dai->component);
		अगर (hda_pvt) अणु
			/*
			 * all codecs are on the same bus, so it's sufficient
			 * to look up only the first one
			 */
			snd_hda_set_घातer_save(hda_pvt->codec.bus,
					       HDA_CODEC_AUTOSUSPEND_DELAY_MS);
			अवरोध;
		पूर्ण
	पूर्ण
पूर्ण

अटल पूर्णांक skl_hda_audio_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा snd_soc_acpi_mach *mach;
	काष्ठा skl_hda_निजी *ctx;
	पूर्णांक ret;

	dev_dbg(&pdev->dev, "%s: entry\n", __func__);

	ctx = devm_kzalloc(&pdev->dev, माप(*ctx), GFP_KERNEL);
	अगर (!ctx)
		वापस -ENOMEM;

	INIT_LIST_HEAD(&ctx->hdmi_pcm_list);

	mach = pdev->dev.platक्रमm_data;
	अगर (!mach)
		वापस -EINVAL;

	snd_soc_card_set_drvdata(&hda_soc_card, ctx);

	ret = skl_hda_fill_card_info(&mach->mach_params);
	अगर (ret < 0) अणु
		dev_err(&pdev->dev, "Unsupported HDAudio/iDisp configuration found\n");
		वापस ret;
	पूर्ण

	ctx->pcm_count = hda_soc_card.num_links;
	ctx->dai_index = 1; /* hdmi codec dai name starts from index 1 */
	ctx->platक्रमm_name = mach->mach_params.platक्रमm;
	ctx->common_hdmi_codec_drv = mach->mach_params.common_hdmi_codec_drv;

	hda_soc_card.dev = &pdev->dev;

	अगर (mach->mach_params.dmic_num > 0) अणु
		snम_लिखो(hda_soc_components, माप(hda_soc_components),
				"cfg-dmics:%d", mach->mach_params.dmic_num);
		hda_soc_card.components = hda_soc_components;
	पूर्ण

	ret = devm_snd_soc_रेजिस्टर_card(&pdev->dev, &hda_soc_card);
	अगर (!ret)
		skl_set_hda_codec_स्वतःsuspend_delay(&hda_soc_card);

	वापस ret;
पूर्ण

अटल काष्ठा platक्रमm_driver skl_hda_audio = अणु
	.probe = skl_hda_audio_probe,
	.driver = अणु
		.name = "skl_hda_dsp_generic",
		.pm = &snd_soc_pm_ops,
	पूर्ण,
पूर्ण;

module_platक्रमm_driver(skl_hda_audio)

/* Module inक्रमmation */
MODULE_DESCRIPTION("SKL/KBL/BXT/APL HDA Generic Machine driver");
MODULE_AUTHOR("Rakesh Ughreja <rakesh.a.ughreja@intel.com>");
MODULE_LICENSE("GPL v2");
MODULE_ALIAS("platform:skl_hda_dsp_generic");
