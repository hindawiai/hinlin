<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
// Copyright (c) 2020 Intel Corporation

/*
 *  sof_sdw - ASOC Machine driver क्रम Intel SoundWire platक्रमms
 */

#समावेश <linux/device.h>
#समावेश <linux/dmi.h>
#समावेश <linux/module.h>
#समावेश <linux/soundwire/sdw.h>
#समावेश <linux/soundwire/sdw_type.h>
#समावेश <sound/soc.h>
#समावेश <sound/soc-acpi.h>
#समावेश "sof_sdw_common.h"

अचिन्हित दीर्घ sof_sdw_quirk = SOF_RT711_JD_SRC_JD1;
अटल पूर्णांक quirk_override = -1;
module_param_named(quirk, quirk_override, पूर्णांक, 0444);
MODULE_PARM_DESC(quirk, "Board-specific quirk override");

#घोषणा INC_ID(BE, CPU, LINK)	करो अणु (BE)++; (CPU)++; (LINK)++; पूर्ण जबतक (0)

अटल व्योम log_quirks(काष्ठा device *dev)
अणु
	अगर (SOF_RT711_JDSRC(sof_sdw_quirk))
		dev_dbg(dev, "quirk realtek,jack-detect-source %ld\n",
			SOF_RT711_JDSRC(sof_sdw_quirk));
	अगर (sof_sdw_quirk & SOF_SDW_FOUR_SPK)
		dev_dbg(dev, "quirk SOF_SDW_FOUR_SPK enabled\n");
	अगर (sof_sdw_quirk & SOF_SDW_TGL_HDMI)
		dev_dbg(dev, "quirk SOF_SDW_TGL_HDMI enabled\n");
	अगर (sof_sdw_quirk & SOF_SDW_PCH_DMIC)
		dev_dbg(dev, "quirk SOF_SDW_PCH_DMIC enabled\n");
	अगर (SOF_SSP_GET_PORT(sof_sdw_quirk))
		dev_dbg(dev, "SSP port %ld\n",
			SOF_SSP_GET_PORT(sof_sdw_quirk));
	अगर (sof_sdw_quirk & SOF_RT715_DAI_ID_FIX)
		dev_dbg(dev, "quirk SOF_RT715_DAI_ID_FIX enabled\n");
	अगर (sof_sdw_quirk & SOF_SDW_NO_AGGREGATION)
		dev_dbg(dev, "quirk SOF_SDW_NO_AGGREGATION enabled\n");
पूर्ण

अटल पूर्णांक sof_sdw_quirk_cb(स्थिर काष्ठा dmi_प्रणाली_id *id)
अणु
	sof_sdw_quirk = (अचिन्हित दीर्घ)id->driver_data;
	वापस 1;
पूर्ण

अटल स्थिर काष्ठा dmi_प्रणाली_id sof_sdw_quirk_table[] = अणु
	/* CometLake devices */
	अणु
		.callback = sof_sdw_quirk_cb,
		.matches = अणु
			DMI_MATCH(DMI_SYS_VENDOR, "Intel Corporation"),
			DMI_MATCH(DMI_PRODUCT_NAME, "CometLake Client"),
		पूर्ण,
		.driver_data = (व्योम *)SOF_SDW_PCH_DMIC,
	पूर्ण,
	अणु
		.callback = sof_sdw_quirk_cb,
		.matches = अणु
			DMI_MATCH(DMI_SYS_VENDOR, "Dell Inc"),
			DMI_EXACT_MATCH(DMI_PRODUCT_SKU, "09C6")
		पूर्ण,
		.driver_data = (व्योम *)(SOF_RT711_JD_SRC_JD2 |
					SOF_RT715_DAI_ID_FIX),
	पूर्ण,
	अणु
		/* early version of SKU 09C6 */
		.callback = sof_sdw_quirk_cb,
		.matches = अणु
			DMI_MATCH(DMI_SYS_VENDOR, "Dell Inc"),
			DMI_EXACT_MATCH(DMI_PRODUCT_SKU, "0983")
		पूर्ण,
		.driver_data = (व्योम *)(SOF_RT711_JD_SRC_JD2 |
					SOF_RT715_DAI_ID_FIX),
	पूर्ण,
	अणु
		.callback = sof_sdw_quirk_cb,
		.matches = अणु
			DMI_MATCH(DMI_SYS_VENDOR, "Dell Inc"),
			DMI_EXACT_MATCH(DMI_PRODUCT_SKU, "098F"),
		पूर्ण,
		.driver_data = (व्योम *)(SOF_RT711_JD_SRC_JD2 |
					SOF_RT715_DAI_ID_FIX |
					SOF_SDW_FOUR_SPK),
	पूर्ण,
	अणु
		.callback = sof_sdw_quirk_cb,
		.matches = अणु
			DMI_MATCH(DMI_SYS_VENDOR, "Dell Inc"),
			DMI_EXACT_MATCH(DMI_PRODUCT_SKU, "0990"),
		पूर्ण,
		.driver_data = (व्योम *)(SOF_RT711_JD_SRC_JD2 |
					SOF_RT715_DAI_ID_FIX |
					SOF_SDW_FOUR_SPK),
	पूर्ण,
	/* IceLake devices */
	अणु
		.callback = sof_sdw_quirk_cb,
		.matches = अणु
			DMI_MATCH(DMI_SYS_VENDOR, "Intel Corporation"),
			DMI_MATCH(DMI_PRODUCT_NAME, "Ice Lake Client"),
		पूर्ण,
		.driver_data = (व्योम *)SOF_SDW_PCH_DMIC,
	पूर्ण,
	/* TigerLake devices */
	अणु
		.callback = sof_sdw_quirk_cb,
		.matches = अणु
			DMI_MATCH(DMI_SYS_VENDOR, "Intel Corporation"),
			DMI_MATCH(DMI_PRODUCT_NAME,
				  "Tiger Lake Client Platform"),
		पूर्ण,
		.driver_data = (व्योम *)(SOF_SDW_TGL_HDMI |
					SOF_RT711_JD_SRC_JD1 |
					SOF_SDW_PCH_DMIC |
					SOF_SSP_PORT(SOF_I2S_SSP2)),
	पूर्ण,
	अणु
		.callback = sof_sdw_quirk_cb,
		.matches = अणु
			DMI_MATCH(DMI_SYS_VENDOR, "Dell Inc"),
			DMI_EXACT_MATCH(DMI_PRODUCT_SKU, "0A3E")
		पूर्ण,
		.driver_data = (व्योम *)(SOF_SDW_TGL_HDMI |
					SOF_RT711_JD_SRC_JD2 |
					SOF_RT715_DAI_ID_FIX),
	पूर्ण,
	अणु
		.callback = sof_sdw_quirk_cb,
		.matches = अणु
			DMI_MATCH(DMI_SYS_VENDOR, "Dell Inc"),
			DMI_EXACT_MATCH(DMI_PRODUCT_SKU, "0A5E")
		पूर्ण,
		.driver_data = (व्योम *)(SOF_SDW_TGL_HDMI |
					SOF_RT711_JD_SRC_JD2 |
					SOF_RT715_DAI_ID_FIX |
					SOF_SDW_FOUR_SPK),
	पूर्ण,
	अणु
		.callback = sof_sdw_quirk_cb,
		.matches = अणु
			DMI_MATCH(DMI_SYS_VENDOR, "Google"),
			DMI_MATCH(DMI_PRODUCT_NAME, "Volteer"),
		पूर्ण,
		.driver_data = (व्योम *)(SOF_SDW_TGL_HDMI |
					SOF_SDW_PCH_DMIC |
					SOF_SDW_FOUR_SPK),
	पूर्ण,
	अणु
		.callback = sof_sdw_quirk_cb,
		.matches = अणु
			DMI_MATCH(DMI_SYS_VENDOR, "Google"),
			DMI_MATCH(DMI_PRODUCT_NAME, "Ripto"),
		पूर्ण,
		.driver_data = (व्योम *)(SOF_SDW_TGL_HDMI |
					SOF_SDW_PCH_DMIC |
					SOF_SDW_FOUR_SPK),
	पूर्ण,
	अणु
		/*
		 * this entry covers multiple HP SKUs. The family name
		 * करोes not seem robust enough, so we use a partial
		 * match that ignores the product name suffix
		 * (e.g. 15-eb1xxx, 14t-ea000 or 13-aw2xxx)
		 */
		.callback = sof_sdw_quirk_cb,
		.matches = अणु
			DMI_MATCH(DMI_SYS_VENDOR, "HP"),
			DMI_MATCH(DMI_PRODUCT_NAME, "HP Spectre x360 Convertible"),
		पूर्ण,
		.driver_data = (व्योम *)(SOF_SDW_TGL_HDMI |
					SOF_SDW_PCH_DMIC |
					SOF_RT711_JD_SRC_JD2),
	पूर्ण,
	/* TigerLake-SDCA devices */
	अणु
		.callback = sof_sdw_quirk_cb,
		.matches = अणु
			DMI_MATCH(DMI_SYS_VENDOR, "Dell Inc"),
			DMI_EXACT_MATCH(DMI_PRODUCT_SKU, "0A32")
		पूर्ण,
		.driver_data = (व्योम *)(SOF_SDW_TGL_HDMI |
					SOF_RT711_JD_SRC_JD2 |
					SOF_RT715_DAI_ID_FIX |
					SOF_SDW_FOUR_SPK),
	पूर्ण,
	/* AlderLake devices */
	अणु
		.callback = sof_sdw_quirk_cb,
		.matches = अणु
			DMI_MATCH(DMI_SYS_VENDOR, "Intel Corporation"),
			DMI_MATCH(DMI_PRODUCT_NAME, "Alder Lake Client Platform"),
		पूर्ण,
		.driver_data = (व्योम *)(SOF_RT711_JD_SRC_JD1 |
					SOF_SDW_TGL_HDMI |
					SOF_SDW_PCH_DMIC),
	पूर्ण,
	अणुपूर्ण
पूर्ण;

अटल काष्ठा snd_soc_dai_link_component dmic_component[] = अणु
	अणु
		.name = "dmic-codec",
		.dai_name = "dmic-hifi",
	पूर्ण
पूर्ण;

अटल काष्ठा snd_soc_dai_link_component platक्रमm_component[] = अणु
	अणु
		/* name might be overridden during probe */
		.name = "0000:00:1f.3"
	पूर्ण
पूर्ण;

/* these wrappers are only needed to aव्योम typecast compilation errors */
पूर्णांक sdw_startup(काष्ठा snd_pcm_substream *substream)
अणु
	वापस sdw_startup_stream(substream);
पूर्ण

पूर्णांक sdw_prepare(काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा snd_soc_pcm_runसमय *rtd = asoc_substream_to_rtd(substream);
	काष्ठा sdw_stream_runसमय *sdw_stream;
	काष्ठा snd_soc_dai *dai;

	/* Find stream from first CPU DAI */
	dai = asoc_rtd_to_cpu(rtd, 0);

	sdw_stream = snd_soc_dai_get_sdw_stream(dai, substream->stream);

	अगर (IS_ERR(sdw_stream)) अणु
		dev_err(rtd->dev, "no stream found for DAI %s", dai->name);
		वापस PTR_ERR(sdw_stream);
	पूर्ण

	वापस sdw_prepare_stream(sdw_stream);
पूर्ण

पूर्णांक sdw_trigger(काष्ठा snd_pcm_substream *substream, पूर्णांक cmd)
अणु
	काष्ठा snd_soc_pcm_runसमय *rtd = asoc_substream_to_rtd(substream);
	काष्ठा sdw_stream_runसमय *sdw_stream;
	काष्ठा snd_soc_dai *dai;
	पूर्णांक ret;

	/* Find stream from first CPU DAI */
	dai = asoc_rtd_to_cpu(rtd, 0);

	sdw_stream = snd_soc_dai_get_sdw_stream(dai, substream->stream);

	अगर (IS_ERR(sdw_stream)) अणु
		dev_err(rtd->dev, "no stream found for DAI %s", dai->name);
		वापस PTR_ERR(sdw_stream);
	पूर्ण

	चयन (cmd) अणु
	हाल SNDRV_PCM_TRIGGER_START:
	हाल SNDRV_PCM_TRIGGER_PAUSE_RELEASE:
	हाल SNDRV_PCM_TRIGGER_RESUME:
		ret = sdw_enable_stream(sdw_stream);
		अवरोध;

	हाल SNDRV_PCM_TRIGGER_PAUSE_PUSH:
	हाल SNDRV_PCM_TRIGGER_SUSPEND:
	हाल SNDRV_PCM_TRIGGER_STOP:
		ret = sdw_disable_stream(sdw_stream);
		अवरोध;
	शेष:
		ret = -EINVAL;
		अवरोध;
	पूर्ण

	अगर (ret)
		dev_err(rtd->dev, "%s trigger %d failed: %d", __func__, cmd, ret);

	वापस ret;
पूर्ण

पूर्णांक sdw_hw_मुक्त(काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा snd_soc_pcm_runसमय *rtd = asoc_substream_to_rtd(substream);
	काष्ठा sdw_stream_runसमय *sdw_stream;
	काष्ठा snd_soc_dai *dai;

	/* Find stream from first CPU DAI */
	dai = asoc_rtd_to_cpu(rtd, 0);

	sdw_stream = snd_soc_dai_get_sdw_stream(dai, substream->stream);

	अगर (IS_ERR(sdw_stream)) अणु
		dev_err(rtd->dev, "no stream found for DAI %s", dai->name);
		वापस PTR_ERR(sdw_stream);
	पूर्ण

	वापस sdw_deprepare_stream(sdw_stream);
पूर्ण

व्योम sdw_shutकरोwn(काष्ठा snd_pcm_substream *substream)
अणु
	sdw_shutकरोwn_stream(substream);
पूर्ण

अटल स्थिर काष्ठा snd_soc_ops sdw_ops = अणु
	.startup = sdw_startup,
	.prepare = sdw_prepare,
	.trigger = sdw_trigger,
	.hw_मुक्त = sdw_hw_मुक्त,
	.shutकरोwn = sdw_shutकरोwn,
पूर्ण;

अटल काष्ठा sof_sdw_codec_info codec_info_list[] = अणु
	अणु
		.part_id = 0x700,
		.direction = अणुtrue, trueपूर्ण,
		.dai_name = "rt700-aif1",
		.init = sof_sdw_rt700_init,
	पूर्ण,
	अणु
		.part_id = 0x711,
		.version_id = 3,
		.direction = अणुtrue, trueपूर्ण,
		.dai_name = "rt711-sdca-aif1",
		.init = sof_sdw_rt711_sdca_init,
		.निकास = sof_sdw_rt711_sdca_निकास,
	पूर्ण,
	अणु
		.part_id = 0x711,
		.version_id = 2,
		.direction = अणुtrue, trueपूर्ण,
		.dai_name = "rt711-aif1",
		.init = sof_sdw_rt711_init,
		.निकास = sof_sdw_rt711_निकास,
	पूर्ण,
	अणु
		.part_id = 0x1308,
		.acpi_id = "10EC1308",
		.direction = अणुtrue, falseपूर्ण,
		.dai_name = "rt1308-aif",
		.ops = &sof_sdw_rt1308_i2s_ops,
		.init = sof_sdw_rt1308_init,
	पूर्ण,
	अणु
		.part_id = 0x1316,
		.direction = अणुtrue, trueपूर्ण,
		.dai_name = "rt1316-aif",
		.init = sof_sdw_rt1316_init,
	पूर्ण,
	अणु
		.part_id = 0x714,
		.version_id = 3,
		.direction = अणुfalse, trueपूर्ण,
		.dai_name = "rt715-aif2",
		.init = sof_sdw_rt715_sdca_init,
	पूर्ण,
	अणु
		.part_id = 0x715,
		.version_id = 3,
		.direction = अणुfalse, trueपूर्ण,
		.dai_name = "rt715-aif2",
		.init = sof_sdw_rt715_sdca_init,
	पूर्ण,
	अणु
		.part_id = 0x714,
		.version_id = 2,
		.direction = अणुfalse, trueपूर्ण,
		.dai_name = "rt715-aif2",
		.init = sof_sdw_rt715_init,
	पूर्ण,
	अणु
		.part_id = 0x715,
		.version_id = 2,
		.direction = अणुfalse, trueपूर्ण,
		.dai_name = "rt715-aif2",
		.init = sof_sdw_rt715_init,
	पूर्ण,
	अणु
		.part_id = 0x8373,
		.direction = अणुtrue, trueपूर्ण,
		.dai_name = "max98373-aif1",
		.init = sof_sdw_mx8373_init,
		.codec_card_late_probe = sof_sdw_mx8373_late_probe,
	पूर्ण,
	अणु
		.part_id = 0x5682,
		.direction = अणुtrue, trueपूर्ण,
		.dai_name = "rt5682-sdw",
		.init = sof_sdw_rt5682_init,
	पूर्ण,
पूर्ण;

अटल अंतरभूत पूर्णांक find_codec_info_part(u64 adr)
अणु
	अचिन्हित पूर्णांक part_id, sdw_version;
	पूर्णांक i;

	part_id = SDW_PART_ID(adr);
	sdw_version = SDW_VERSION(adr);
	क्रम (i = 0; i < ARRAY_SIZE(codec_info_list); i++)
		/*
		 * A codec info is क्रम all sdw version with the part id अगर
		 * version_id is not specअगरied in the codec info.
		 */
		अगर (part_id == codec_info_list[i].part_id &&
		    (!codec_info_list[i].version_id ||
		     sdw_version == codec_info_list[i].version_id))
			वापस i;

	वापस -EINVAL;

पूर्ण

अटल अंतरभूत पूर्णांक find_codec_info_acpi(स्थिर u8 *acpi_id)
अणु
	पूर्णांक i;

	अगर (!acpi_id[0])
		वापस -EINVAL;

	क्रम (i = 0; i < ARRAY_SIZE(codec_info_list); i++)
		अगर (!स_भेद(codec_info_list[i].acpi_id, acpi_id,
			    ACPI_ID_LEN))
			अवरोध;

	अगर (i == ARRAY_SIZE(codec_info_list))
		वापस -EINVAL;

	वापस i;
पूर्ण

/*
 * get BE dailink number and CPU DAI number based on sdw link adr.
 * Since some sdw slaves may be aggregated, the CPU DAI number
 * may be larger than the number of BE dailinks.
 */
अटल पूर्णांक get_sdw_dailink_info(स्थिर काष्ठा snd_soc_acpi_link_adr *links,
				पूर्णांक *sdw_be_num, पूर्णांक *sdw_cpu_dai_num)
अणु
	स्थिर काष्ठा snd_soc_acpi_link_adr *link;
	bool group_visited[SDW_MAX_GROUPS];
	bool no_aggregation;
	पूर्णांक i;

	no_aggregation = sof_sdw_quirk & SOF_SDW_NO_AGGREGATION;
	*sdw_cpu_dai_num = 0;
	*sdw_be_num  = 0;

	अगर (!links)
		वापस -EINVAL;

	क्रम (i = 0; i < SDW_MAX_GROUPS; i++)
		group_visited[i] = false;

	क्रम (link = links; link->num_adr; link++) अणु
		स्थिर काष्ठा snd_soc_acpi_endpoपूर्णांक *endpoपूर्णांक;
		पूर्णांक codec_index;
		पूर्णांक stream;
		u64 adr;

		adr = link->adr_d->adr;
		codec_index = find_codec_info_part(adr);
		अगर (codec_index < 0)
			वापस codec_index;

		endpoपूर्णांक = link->adr_d->endpoपूर्णांकs;

		/* count DAI number क्रम playback and capture */
		क्रम_each_pcm_streams(stream) अणु
			अगर (!codec_info_list[codec_index].direction[stream])
				जारी;

			(*sdw_cpu_dai_num)++;

			/* count BE क्रम each non-aggregated slave or group */
			अगर (!endpoपूर्णांक->aggregated || no_aggregation ||
			    !group_visited[endpoपूर्णांक->group_id])
				(*sdw_be_num)++;
		पूर्ण

		अगर (endpoपूर्णांक->aggregated)
			group_visited[endpoपूर्णांक->group_id] = true;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम init_dai_link(काष्ठा device *dev, काष्ठा snd_soc_dai_link *dai_links,
			  पूर्णांक be_id, अक्षर *name, पूर्णांक playback, पूर्णांक capture,
			  काष्ठा snd_soc_dai_link_component *cpus, पूर्णांक cpus_num,
			  काष्ठा snd_soc_dai_link_component *codecs, पूर्णांक codecs_num,
			  पूर्णांक (*init)(काष्ठा snd_soc_pcm_runसमय *rtd),
			  स्थिर काष्ठा snd_soc_ops *ops)
अणु
	dev_dbg(dev, "create dai link %s, id %d\n", name, be_id);
	dai_links->id = be_id;
	dai_links->name = name;
	dai_links->platक्रमms = platक्रमm_component;
	dai_links->num_platक्रमms = ARRAY_SIZE(platक्रमm_component);
	dai_links->nonatomic = true;
	dai_links->no_pcm = 1;
	dai_links->cpus = cpus;
	dai_links->num_cpus = cpus_num;
	dai_links->codecs = codecs;
	dai_links->num_codecs = codecs_num;
	dai_links->dpcm_playback = playback;
	dai_links->dpcm_capture = capture;
	dai_links->init = init;
	dai_links->ops = ops;
पूर्ण

अटल bool is_unique_device(स्थिर काष्ठा snd_soc_acpi_link_adr *link,
			     अचिन्हित पूर्णांक sdw_version,
			     अचिन्हित पूर्णांक mfg_id,
			     अचिन्हित पूर्णांक part_id,
			     अचिन्हित पूर्णांक class_id,
			     पूर्णांक index_in_link
			    )
अणु
	पूर्णांक i;

	क्रम (i = 0; i < link->num_adr; i++) अणु
		अचिन्हित पूर्णांक sdw1_version, mfg1_id, part1_id, class1_id;
		u64 adr;

		/* skip itself */
		अगर (i == index_in_link)
			जारी;

		adr = link->adr_d[i].adr;

		sdw1_version = SDW_VERSION(adr);
		mfg1_id = SDW_MFG_ID(adr);
		part1_id = SDW_PART_ID(adr);
		class1_id = SDW_CLASS_ID(adr);

		अगर (sdw_version == sdw1_version &&
		    mfg_id == mfg1_id &&
		    part_id == part1_id &&
		    class_id == class1_id)
			वापस false;
	पूर्ण

	वापस true;
पूर्ण

अटल पूर्णांक create_codec_dai_name(काष्ठा device *dev,
				 स्थिर काष्ठा snd_soc_acpi_link_adr *link,
				 काष्ठा snd_soc_dai_link_component *codec,
				 पूर्णांक offset,
				 काष्ठा snd_soc_codec_conf *codec_conf,
				 पूर्णांक codec_count,
				 पूर्णांक *codec_conf_index)
अणु
	पूर्णांक i;

	/* sanity check */
	अगर (*codec_conf_index + link->num_adr > codec_count) अणु
		dev_err(dev, "codec_conf: out-of-bounds access requested\n");
		वापस -EINVAL;
	पूर्ण

	क्रम (i = 0; i < link->num_adr; i++) अणु
		अचिन्हित पूर्णांक sdw_version, unique_id, mfg_id;
		अचिन्हित पूर्णांक link_id, part_id, class_id;
		पूर्णांक codec_index, comp_index;
		अक्षर *codec_str;
		u64 adr;

		adr = link->adr_d[i].adr;

		sdw_version = SDW_VERSION(adr);
		link_id = SDW_DISCO_LINK_ID(adr);
		unique_id = SDW_UNIQUE_ID(adr);
		mfg_id = SDW_MFG_ID(adr);
		part_id = SDW_PART_ID(adr);
		class_id = SDW_CLASS_ID(adr);

		comp_index = i + offset;
		अगर (is_unique_device(link, sdw_version, mfg_id, part_id,
				     class_id, i)) अणु
			codec_str = "sdw:%x:%x:%x:%x";
			codec[comp_index].name =
				devm_kaप्र_लिखो(dev, GFP_KERNEL, codec_str,
					       link_id, mfg_id, part_id,
					       class_id);
		पूर्ण अन्यथा अणु
			codec_str = "sdw:%x:%x:%x:%x:%x";
			codec[comp_index].name =
				devm_kaप्र_लिखो(dev, GFP_KERNEL, codec_str,
					       link_id, mfg_id, part_id,
					       class_id, unique_id);
		पूर्ण

		अगर (!codec[comp_index].name)
			वापस -ENOMEM;

		codec_index = find_codec_info_part(adr);
		अगर (codec_index < 0)
			वापस codec_index;

		codec[comp_index].dai_name =
			codec_info_list[codec_index].dai_name;

		codec_conf[*codec_conf_index].dlc = codec[comp_index];
		codec_conf[*codec_conf_index].name_prefix = link->adr_d[i].name_prefix;

		++*codec_conf_index;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक set_codec_init_func(स्थिर काष्ठा snd_soc_acpi_link_adr *link,
			       काष्ठा snd_soc_dai_link *dai_links,
			       bool playback, पूर्णांक group_id)
अणु
	पूर्णांक i;

	करो अणु
		/*
		 * Initialize the codec. If codec is part of an aggregated
		 * group (group_id>0), initialize all codecs beदीर्घing to
		 * same group.
		 */
		क्रम (i = 0; i < link->num_adr; i++) अणु
			पूर्णांक codec_index;

			codec_index = find_codec_info_part(link->adr_d[i].adr);

			अगर (codec_index < 0)
				वापस codec_index;
			/* The group_id is > 0 अगरf the codec is aggregated */
			अगर (link->adr_d[i].endpoपूर्णांकs->group_id != group_id)
				जारी;
			अगर (codec_info_list[codec_index].init)
				codec_info_list[codec_index].init(link,
						dai_links,
						&codec_info_list[codec_index],
						playback);
		पूर्ण
		link++;
	पूर्ण जबतक (link->mask && group_id);

	वापस 0;
पूर्ण

/*
 * check endpoपूर्णांक status in slaves and gather link ID क्रम all slaves in
 * the same group to generate dअगरferent CPU DAI. Now only support
 * one sdw link with all slaves set with only single group id.
 *
 * one slave on one sdw link with aggregated = 0
 * one sdw BE DAI <---> one-cpu DAI <---> one-codec DAI
 *
 * two or more slaves on one sdw link with aggregated = 0
 * one sdw BE DAI  <---> one-cpu DAI <---> multi-codec DAIs
 *
 * multiple links with multiple slaves with aggregated = 1
 * one sdw BE DAI  <---> 1 .. N CPU DAIs <----> 1 .. N codec DAIs
 */
अटल पूर्णांक get_slave_info(स्थिर काष्ठा snd_soc_acpi_link_adr *adr_link,
			  काष्ठा device *dev, पूर्णांक *cpu_dai_id, पूर्णांक *cpu_dai_num,
			  पूर्णांक *codec_num, पूर्णांक *group_id,
			  bool *group_generated)
अणु
	स्थिर काष्ठा snd_soc_acpi_adr_device *adr_d;
	स्थिर काष्ठा snd_soc_acpi_link_adr *adr_next;
	bool no_aggregation;
	पूर्णांक index = 0;

	no_aggregation = sof_sdw_quirk & SOF_SDW_NO_AGGREGATION;
	*codec_num = adr_link->num_adr;
	adr_d = adr_link->adr_d;

	/* make sure the link mask has a single bit set */
	अगर (!is_घातer_of_2(adr_link->mask))
		वापस -EINVAL;

	cpu_dai_id[index++] = ffs(adr_link->mask) - 1;
	अगर (!adr_d->endpoपूर्णांकs->aggregated || no_aggregation) अणु
		*cpu_dai_num = 1;
		*group_id = 0;
		वापस 0;
	पूर्ण

	*group_id = adr_d->endpoपूर्णांकs->group_id;

	/* gather other link ID of slaves in the same group */
	क्रम (adr_next = adr_link + 1; adr_next && adr_next->num_adr;
		adr_next++) अणु
		स्थिर काष्ठा snd_soc_acpi_endpoपूर्णांक *endpoपूर्णांक;

		endpoपूर्णांक = adr_next->adr_d->endpoपूर्णांकs;
		अगर (!endpoपूर्णांक->aggregated ||
		    endpoपूर्णांक->group_id != *group_id)
			जारी;

		/* make sure the link mask has a single bit set */
		अगर (!is_घातer_of_2(adr_next->mask))
			वापस -EINVAL;

		अगर (index >= SDW_MAX_CPU_DAIS) अणु
			dev_err(dev, " cpu_dai_id array overflows");
			वापस -EINVAL;
		पूर्ण

		cpu_dai_id[index++] = ffs(adr_next->mask) - 1;
		*codec_num += adr_next->num_adr;
	पूर्ण

	/*
	 * indicate CPU DAIs क्रम this group have been generated
	 * to aव्योम generating CPU DAIs क्रम this group again.
	 */
	group_generated[*group_id] = true;
	*cpu_dai_num = index;

	वापस 0;
पूर्ण

अटल पूर्णांक create_sdw_dailink(काष्ठा device *dev, पूर्णांक *be_index,
			      काष्ठा snd_soc_dai_link *dai_links,
			      पूर्णांक sdw_be_num, पूर्णांक sdw_cpu_dai_num,
			      काष्ठा snd_soc_dai_link_component *cpus,
			      स्थिर काष्ठा snd_soc_acpi_link_adr *link,
			      पूर्णांक *cpu_id, bool *group_generated,
			      काष्ठा snd_soc_codec_conf *codec_conf,
			      पूर्णांक codec_count,
			      पूर्णांक *codec_conf_index)
अणु
	स्थिर काष्ठा snd_soc_acpi_link_adr *link_next;
	काष्ठा snd_soc_dai_link_component *codecs;
	पूर्णांक cpu_dai_id[SDW_MAX_CPU_DAIS];
	पूर्णांक cpu_dai_num, cpu_dai_index;
	अचिन्हित पूर्णांक group_id;
	पूर्णांक codec_idx = 0;
	पूर्णांक i = 0, j = 0;
	पूर्णांक codec_index;
	पूर्णांक codec_num;
	पूर्णांक stream;
	पूर्णांक ret;
	पूर्णांक k;

	ret = get_slave_info(link, dev, cpu_dai_id, &cpu_dai_num, &codec_num,
			     &group_id, group_generated);
	अगर (ret)
		वापस ret;

	codecs = devm_kसुस्मृति(dev, codec_num, माप(*codecs), GFP_KERNEL);
	अगर (!codecs)
		वापस -ENOMEM;

	/* generate codec name on dअगरferent links in the same group */
	क्रम (link_next = link; link_next && link_next->num_adr &&
	     i < cpu_dai_num; link_next++) अणु
		स्थिर काष्ठा snd_soc_acpi_endpoपूर्णांक *endpoपूर्णांकs;

		endpoपूर्णांकs = link_next->adr_d->endpoपूर्णांकs;
		अगर (group_id && (!endpoपूर्णांकs->aggregated ||
				 endpoपूर्णांकs->group_id != group_id))
			जारी;

		/* skip the link excluded by this processed group */
		अगर (cpu_dai_id[i] != ffs(link_next->mask) - 1)
			जारी;

		ret = create_codec_dai_name(dev, link_next, codecs, codec_idx,
					    codec_conf, codec_count, codec_conf_index);
		अगर (ret < 0)
			वापस ret;

		/* check next link to create codec dai in the processed group */
		i++;
		codec_idx += link_next->num_adr;
	पूर्ण

	/* find codec info to create BE DAI */
	codec_index = find_codec_info_part(link->adr_d[0].adr);
	अगर (codec_index < 0)
		वापस codec_index;

	cpu_dai_index = *cpu_id;
	क्रम_each_pcm_streams(stream) अणु
		अक्षर *name, *cpu_name;
		पूर्णांक playback, capture;
		अटल स्थिर अक्षर * स्थिर sdw_stream_name[] = अणु
			"SDW%d-Playback",
			"SDW%d-Capture",
		पूर्ण;

		अगर (!codec_info_list[codec_index].direction[stream])
			जारी;

		/* create stream name according to first link id */
		name = devm_kaप्र_लिखो(dev, GFP_KERNEL,
				      sdw_stream_name[stream], cpu_dai_id[0]);
		अगर (!name)
			वापस -ENOMEM;

		/*
		 * generate CPU DAI name base on the sdw link ID and
		 * PIN ID with offset of 2 according to sdw dai driver.
		 */
		क्रम (k = 0; k < cpu_dai_num; k++) अणु
			cpu_name = devm_kaप्र_लिखो(dev, GFP_KERNEL,
						  "SDW%d Pin%d", cpu_dai_id[k],
						  j + SDW_INTEL_BIसूची_PDI_BASE);
			अगर (!cpu_name)
				वापस -ENOMEM;

			अगर (cpu_dai_index >= sdw_cpu_dai_num) अणु
				dev_err(dev, "invalid cpu dai index %d",
					cpu_dai_index);
				वापस -EINVAL;
			पूर्ण

			cpus[cpu_dai_index++].dai_name = cpu_name;
		पूर्ण

		अगर (*be_index >= sdw_be_num) अणु
			dev_err(dev, " invalid be dai index %d", *be_index);
			वापस -EINVAL;
		पूर्ण

		अगर (*cpu_id >= sdw_cpu_dai_num) अणु
			dev_err(dev, " invalid cpu dai index %d", *cpu_id);
			वापस -EINVAL;
		पूर्ण

		playback = (stream == SNDRV_PCM_STREAM_PLAYBACK);
		capture = (stream == SNDRV_PCM_STREAM_CAPTURE);
		init_dai_link(dev, dai_links + *be_index, *be_index, name,
			      playback, capture,
			      cpus + *cpu_id, cpu_dai_num,
			      codecs, codec_num,
			      शून्य, &sdw_ops);

		ret = set_codec_init_func(link, dai_links + (*be_index)++,
					  playback, group_id);
		अगर (ret < 0) अणु
			dev_err(dev, "failed to init codec %d", codec_index);
			वापस ret;
		पूर्ण

		*cpu_id += cpu_dai_num;
		j++;
	पूर्ण

	वापस 0;
पूर्ण

/*
 * DAI link ID of SSP & DMIC & HDMI are based on last
 * link ID used by sdw link. Since be_id may be changed
 * in init func of sdw codec, it is not equal to be_id
 */
अटल अंतरभूत पूर्णांक get_next_be_id(काष्ठा snd_soc_dai_link *links,
				 पूर्णांक be_id)
अणु
	वापस links[be_id - 1].id + 1;
पूर्ण

#घोषणा IDISP_CODEC_MASK	0x4

अटल पूर्णांक sof_card_codec_conf_alloc(काष्ठा device *dev,
				     काष्ठा snd_soc_acpi_mach_params *mach_params,
				     काष्ठा snd_soc_codec_conf **codec_conf,
				     पूर्णांक *codec_conf_count)
अणु
	स्थिर काष्ठा snd_soc_acpi_link_adr *adr_link;
	काष्ठा snd_soc_codec_conf *c_conf;
	पूर्णांक num_codecs = 0;
	पूर्णांक i;

	adr_link = mach_params->links;
	अगर (!adr_link)
		वापस -EINVAL;

	/* generate DAI links by each sdw link */
	क्रम (; adr_link->num_adr; adr_link++) अणु
		क्रम (i = 0; i < adr_link->num_adr; i++) अणु
			अगर (!adr_link->adr_d[i].name_prefix) अणु
				dev_err(dev, "codec 0x%llx does not have a name prefix\n",
					adr_link->adr_d[i].adr);
				वापस -EINVAL;
			पूर्ण
		पूर्ण
		num_codecs += adr_link->num_adr;
	पूर्ण

	c_conf = devm_kzalloc(dev, num_codecs * माप(*c_conf), GFP_KERNEL);
	अगर (!c_conf)
		वापस -ENOMEM;

	*codec_conf = c_conf;
	*codec_conf_count = num_codecs;

	वापस 0;
पूर्ण

अटल पूर्णांक sof_card_dai_links_create(काष्ठा device *dev,
				     काष्ठा snd_soc_acpi_mach *mach,
				     काष्ठा snd_soc_card *card)
अणु
	पूर्णांक ssp_num, sdw_be_num = 0, hdmi_num = 0, dmic_num;
	काष्ठा mc_निजी *ctx = snd_soc_card_get_drvdata(card);
	काष्ठा snd_soc_dai_link_component *idisp_components;
	काष्ठा snd_soc_dai_link_component *ssp_components;
	काष्ठा snd_soc_acpi_mach_params *mach_params;
	स्थिर काष्ठा snd_soc_acpi_link_adr *adr_link;
	काष्ठा snd_soc_dai_link_component *cpus;
	काष्ठा snd_soc_codec_conf *codec_conf;
	पूर्णांक codec_conf_count;
	पूर्णांक codec_conf_index = 0;
	bool group_generated[SDW_MAX_GROUPS];
	पूर्णांक ssp_codec_index, ssp_mask;
	काष्ठा snd_soc_dai_link *links;
	पूर्णांक num_links, link_id = 0;
	अक्षर *name, *cpu_name;
	पूर्णांक total_cpu_dai_num;
	पूर्णांक sdw_cpu_dai_num;
	पूर्णांक i, j, be_id = 0;
	पूर्णांक cpu_id = 0;
	पूर्णांक comp_num;
	पूर्णांक ret;

	mach_params = &mach->mach_params;

	/* allocate codec conf, will be populated when dailinks are created */
	ret = sof_card_codec_conf_alloc(dev, mach_params, &codec_conf, &codec_conf_count);
	अगर (ret < 0)
		वापस ret;

	/* reset amp_num to ensure amp_num++ starts from 0 in each probe */
	क्रम (i = 0; i < ARRAY_SIZE(codec_info_list); i++)
		codec_info_list[i].amp_num = 0;

	अगर (sof_sdw_quirk & SOF_SDW_TGL_HDMI)
		hdmi_num = SOF_TGL_HDMI_COUNT;
	अन्यथा
		hdmi_num = SOF_PRE_TGL_HDMI_COUNT;

	ssp_mask = SOF_SSP_GET_PORT(sof_sdw_quirk);
	/*
	 * on generic tgl platक्रमm, I2S or sdw mode is supported
	 * based on board rework. A ACPI device is रेजिस्टरed in
	 * प्रणाली only when I2S mode is supported, not sdw mode.
	 * Here check ACPI ID to confirm I2S is supported.
	 */
	ssp_codec_index = find_codec_info_acpi(mach->id);
	ssp_num = ssp_codec_index >= 0 ? hweight_दीर्घ(ssp_mask) : 0;
	comp_num = hdmi_num + ssp_num;

	ret = get_sdw_dailink_info(mach_params->links,
				   &sdw_be_num, &sdw_cpu_dai_num);
	अगर (ret < 0) अणु
		dev_err(dev, "failed to get sdw link info %d", ret);
		वापस ret;
	पूर्ण

	अगर (mach_params->codec_mask & IDISP_CODEC_MASK)
		ctx->idisp_codec = true;

	/* enable dmic01 & dmic16k */
	dmic_num = (sof_sdw_quirk & SOF_SDW_PCH_DMIC || mach_params->dmic_num) ? 2 : 0;
	comp_num += dmic_num;

	dev_dbg(dev, "sdw %d, ssp %d, dmic %d, hdmi %d", sdw_be_num, ssp_num,
		dmic_num, ctx->idisp_codec ? hdmi_num : 0);

	/* allocate BE dailinks */
	num_links = comp_num + sdw_be_num;
	links = devm_kसुस्मृति(dev, num_links, माप(*links), GFP_KERNEL);

	/* allocated CPU DAIs */
	total_cpu_dai_num = comp_num + sdw_cpu_dai_num;
	cpus = devm_kसुस्मृति(dev, total_cpu_dai_num, माप(*cpus),
			    GFP_KERNEL);

	अगर (!links || !cpus)
		वापस -ENOMEM;

	/* SDW */
	अगर (!sdw_be_num)
		जाओ SSP;

	adr_link = mach_params->links;
	अगर (!adr_link)
		वापस -EINVAL;

	/*
	 * SoundWire Slaves aggregated in the same group may be
	 * located on dअगरferent hardware links. Clear array to indicate
	 * CPU DAIs क्रम this group have not been generated.
	 */
	क्रम (i = 0; i < SDW_MAX_GROUPS; i++)
		group_generated[i] = false;

	/* generate DAI links by each sdw link */
	क्रम (; adr_link->num_adr; adr_link++) अणु
		स्थिर काष्ठा snd_soc_acpi_endpoपूर्णांक *endpoपूर्णांक;

		endpoपूर्णांक = adr_link->adr_d->endpoपूर्णांकs;
		अगर (endpoपूर्णांक->aggregated && !endpoपूर्णांक->group_id) अणु
			dev_err(dev, "invalid group id on link %x",
				adr_link->mask);
			जारी;
		पूर्ण

		/* this group has been generated */
		अगर (endpoपूर्णांक->aggregated &&
		    group_generated[endpoपूर्णांक->group_id])
			जारी;

		ret = create_sdw_dailink(dev, &be_id, links, sdw_be_num,
					 sdw_cpu_dai_num, cpus, adr_link,
					 &cpu_id, group_generated,
					 codec_conf, codec_conf_count,
					 &codec_conf_index);
		अगर (ret < 0) अणु
			dev_err(dev, "failed to create dai link %d", be_id);
			वापस -ENOMEM;
		पूर्ण
	पूर्ण

	/* non-sdw DAI follows sdw DAI */
	link_id = be_id;

	/* get BE ID क्रम non-sdw DAI */
	be_id = get_next_be_id(links, be_id);

SSP:
	/* SSP */
	अगर (!ssp_num)
		जाओ DMIC;

	क्रम (i = 0, j = 0; ssp_mask; i++, ssp_mask >>= 1) अणु
		काष्ठा sof_sdw_codec_info *info;
		पूर्णांक playback, capture;
		अक्षर *codec_name;

		अगर (!(ssp_mask & 0x1))
			जारी;

		name = devm_kaप्र_लिखो(dev, GFP_KERNEL,
				      "SSP%d-Codec", i);
		अगर (!name)
			वापस -ENOMEM;

		cpu_name = devm_kaप्र_लिखो(dev, GFP_KERNEL, "SSP%d Pin", i);
		अगर (!cpu_name)
			वापस -ENOMEM;

		ssp_components = devm_kzalloc(dev, माप(*ssp_components),
					      GFP_KERNEL);
		अगर (!ssp_components)
			वापस -ENOMEM;

		info = &codec_info_list[ssp_codec_index];
		codec_name = devm_kaप्र_लिखो(dev, GFP_KERNEL, "i2c-%s:0%d",
					    info->acpi_id, j++);
		अगर (!codec_name)
			वापस -ENOMEM;

		ssp_components->name = codec_name;
		ssp_components->dai_name = info->dai_name;
		cpus[cpu_id].dai_name = cpu_name;

		playback = info->direction[SNDRV_PCM_STREAM_PLAYBACK];
		capture = info->direction[SNDRV_PCM_STREAM_CAPTURE];
		init_dai_link(dev, links + link_id, be_id, name,
			      playback, capture,
			      cpus + cpu_id, 1,
			      ssp_components, 1,
			      शून्य, info->ops);

		ret = info->init(शून्य, links + link_id, info, 0);
		अगर (ret < 0)
			वापस ret;

		INC_ID(be_id, cpu_id, link_id);
	पूर्ण

DMIC:
	/* dmic */
	अगर (dmic_num > 0) अणु
		cpus[cpu_id].dai_name = "DMIC01 Pin";
		init_dai_link(dev, links + link_id, be_id, "dmic01",
			      0, 1, // DMIC only supports capture
			      cpus + cpu_id, 1,
			      dmic_component, 1,
			      sof_sdw_dmic_init, शून्य);
		INC_ID(be_id, cpu_id, link_id);

		cpus[cpu_id].dai_name = "DMIC16k Pin";
		init_dai_link(dev, links + link_id, be_id, "dmic16k",
			      0, 1, // DMIC only supports capture
			      cpus + cpu_id, 1,
			      dmic_component, 1,
			      /* करोn't call sof_sdw_dmic_init() twice */
			      शून्य, शून्य);
		INC_ID(be_id, cpu_id, link_id);
	पूर्ण

	/* HDMI */
	अगर (hdmi_num > 0) अणु
		idisp_components = devm_kसुस्मृति(dev, hdmi_num,
						माप(*idisp_components),
						GFP_KERNEL);
		अगर (!idisp_components)
			वापस -ENOMEM;
	पूर्ण

	क्रम (i = 0; i < hdmi_num; i++) अणु
		name = devm_kaप्र_लिखो(dev, GFP_KERNEL,
				      "iDisp%d", i + 1);
		अगर (!name)
			वापस -ENOMEM;

		अगर (ctx->idisp_codec) अणु
			idisp_components[i].name = "ehdaudio0D2";
			idisp_components[i].dai_name = devm_kaप्र_लिखो(dev,
								      GFP_KERNEL,
								      "intel-hdmi-hifi%d",
								      i + 1);
			अगर (!idisp_components[i].dai_name)
				वापस -ENOMEM;
		पूर्ण अन्यथा अणु
			idisp_components[i].name = "snd-soc-dummy";
			idisp_components[i].dai_name = "snd-soc-dummy-dai";
		पूर्ण

		cpu_name = devm_kaप्र_लिखो(dev, GFP_KERNEL,
					  "iDisp%d Pin", i + 1);
		अगर (!cpu_name)
			वापस -ENOMEM;

		cpus[cpu_id].dai_name = cpu_name;
		init_dai_link(dev, links + link_id, be_id, name,
			      1, 0, // HDMI only supports playback
			      cpus + cpu_id, 1,
			      idisp_components + i, 1,
			      sof_sdw_hdmi_init, शून्य);
		INC_ID(be_id, cpu_id, link_id);
	पूर्ण

	card->dai_link = links;
	card->num_links = num_links;

	card->codec_conf = codec_conf;
	card->num_configs = codec_conf_count;

	वापस 0;
पूर्ण

अटल पूर्णांक sof_sdw_card_late_probe(काष्ठा snd_soc_card *card)
अणु
	पूर्णांक i, ret;

	क्रम (i = 0; i < ARRAY_SIZE(codec_info_list); i++) अणु
		अगर (!codec_info_list[i].late_probe)
			जारी;

		ret = codec_info_list[i].codec_card_late_probe(card);
		अगर (ret < 0)
			वापस ret;
	पूर्ण

	वापस sof_sdw_hdmi_card_late_probe(card);
पूर्ण

/* SoC card */
अटल स्थिर अक्षर sdw_card_दीर्घ_name[] = "Intel Soundwire SOF";

अटल काष्ठा snd_soc_card card_sof_sdw = अणु
	.name = "soundwire",
	.owner = THIS_MODULE,
	.late_probe = sof_sdw_card_late_probe,
पूर्ण;

अटल पूर्णांक mc_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा snd_soc_card *card = &card_sof_sdw;
	काष्ठा snd_soc_acpi_mach *mach;
	काष्ठा mc_निजी *ctx;
	पूर्णांक amp_num = 0, i;
	पूर्णांक ret;

	dev_dbg(&pdev->dev, "Entry %s\n", __func__);

	ctx = devm_kzalloc(&pdev->dev, माप(*ctx), GFP_KERNEL);
	अगर (!ctx)
		वापस -ENOMEM;

	dmi_check_प्रणाली(sof_sdw_quirk_table);

	अगर (quirk_override != -1) अणु
		dev_info(&pdev->dev, "Overriding quirk 0x%lx => 0x%x\n",
			 sof_sdw_quirk, quirk_override);
		sof_sdw_quirk = quirk_override;
	पूर्ण
	log_quirks(&pdev->dev);

	INIT_LIST_HEAD(&ctx->hdmi_pcm_list);

	card->dev = &pdev->dev;
	snd_soc_card_set_drvdata(card, ctx);

	mach = pdev->dev.platक्रमm_data;
	ret = sof_card_dai_links_create(&pdev->dev, mach,
					card);
	अगर (ret < 0)
		वापस ret;

	ctx->common_hdmi_codec_drv = mach->mach_params.common_hdmi_codec_drv;

	/*
	 * the शेष amp_num is zero क्रम each codec and
	 * amp_num will only be increased क्रम active amp
	 * codecs on used platक्रमm
	 */
	क्रम (i = 0; i < ARRAY_SIZE(codec_info_list); i++)
		amp_num += codec_info_list[i].amp_num;

	card->components = devm_kaप्र_लिखो(card->dev, GFP_KERNEL,
					  "cfg-spk:%d cfg-amp:%d",
					  (sof_sdw_quirk & SOF_SDW_FOUR_SPK)
					  ? 4 : 2, amp_num);
	अगर (!card->components)
		वापस -ENOMEM;

	अगर (mach->mach_params.dmic_num) अणु
		card->components = devm_kaप्र_लिखो(card->dev, GFP_KERNEL,
						  "%s mic:dmic cfg-mics:%d",
						  card->components,
						  mach->mach_params.dmic_num);
		अगर (!card->components)
			वापस -ENOMEM;
	पूर्ण

	card->दीर्घ_name = sdw_card_दीर्घ_name;

	/* Register the card */
	ret = devm_snd_soc_रेजिस्टर_card(&pdev->dev, card);
	अगर (ret) अणु
		dev_err(card->dev, "snd_soc_register_card failed %d\n", ret);
		वापस ret;
	पूर्ण

	platक्रमm_set_drvdata(pdev, card);

	वापस ret;
पूर्ण

अटल पूर्णांक mc_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा snd_soc_card *card = platक्रमm_get_drvdata(pdev);
	काष्ठा snd_soc_dai_link *link;
	पूर्णांक ret;
	पूर्णांक i, j;

	क्रम (i = 0; i < ARRAY_SIZE(codec_info_list); i++) अणु
		अगर (!codec_info_list[i].निकास)
			जारी;
		/*
		 * We करोn't need to call .निकास function अगर there is no matched
		 * dai link found.
		 */
		क्रम_each_card_prelinks(card, j, link) अणु
			अगर (!म_भेद(link->codecs[0].dai_name,
				    codec_info_list[i].dai_name)) अणु
				ret = codec_info_list[i].निकास(&pdev->dev, link);
				अगर (ret)
					dev_warn(&pdev->dev,
						 "codec exit failed %d\n",
						 ret);
				अवरोध;
			पूर्ण
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल काष्ठा platक्रमm_driver sof_sdw_driver = अणु
	.driver = अणु
		.name = "sof_sdw",
		.pm = &snd_soc_pm_ops,
	पूर्ण,
	.probe = mc_probe,
	.हटाओ = mc_हटाओ,
पूर्ण;

module_platक्रमm_driver(sof_sdw_driver);

MODULE_DESCRIPTION("ASoC SoundWire Generic Machine driver");
MODULE_AUTHOR("Bard Liao <yung-chuan.liao@linux.intel.com>");
MODULE_AUTHOR("Rander Wang <rander.wang@linux.intel.com>");
MODULE_AUTHOR("Pierre-Louis Bossart <pierre-louis.bossart@linux.intel.com>");
MODULE_LICENSE("GPL v2");
MODULE_ALIAS("platform:sof_sdw");
