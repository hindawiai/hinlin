<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only
 *  Copyright (c) 2020 Intel Corporation
 */

/*
 *  sof_sdw_common.h - prototypes क्रम common helpers
 */

#अगर_अघोषित SND_SOC_SOF_SDW_COMMON_H
#घोषणा SND_SOC_SOF_SDW_COMMON_H

#समावेश <linux/bits.h>
#समावेश <linux/types.h>
#समावेश <sound/soc.h>

#घोषणा MAX_NO_PROPS 2
#घोषणा MAX_HDMI_NUM 4
#घोषणा SDW_DMIC_DAI_ID 4
#घोषणा SDW_MAX_CPU_DAIS 16
#घोषणा SDW_INTEL_BIसूची_PDI_BASE 2

/* 8 combinations with 4 links + unused group 0 */
#घोषणा SDW_MAX_GROUPS 9

क्रमागत अणु
	SOF_RT711_JD_SRC_JD1 = 1,
	SOF_RT711_JD_SRC_JD2 = 2,
पूर्ण;

क्रमागत अणु
	SOF_PRE_TGL_HDMI_COUNT = 3,
	SOF_TGL_HDMI_COUNT = 4,
पूर्ण;

क्रमागत अणु
	SOF_I2S_SSP0 = BIT(0),
	SOF_I2S_SSP1 = BIT(1),
	SOF_I2S_SSP2 = BIT(2),
	SOF_I2S_SSP3 = BIT(3),
	SOF_I2S_SSP4 = BIT(4),
	SOF_I2S_SSP5 = BIT(5),
पूर्ण;

#घोषणा SOF_RT711_JDSRC(quirk)		((quirk) & GENMASK(1, 0))
#घोषणा SOF_SDW_FOUR_SPK		BIT(2)
#घोषणा SOF_SDW_TGL_HDMI		BIT(3)
#घोषणा SOF_SDW_PCH_DMIC		BIT(4)
#घोषणा SOF_SSP_PORT(x)		(((x) & GENMASK(5, 0)) << 5)
#घोषणा SOF_SSP_GET_PORT(quirk)	(((quirk) >> 5) & GENMASK(5, 0))
#घोषणा SOF_RT715_DAI_ID_FIX		BIT(11)
#घोषणा SOF_SDW_NO_AGGREGATION		BIT(12)

काष्ठा sof_sdw_codec_info अणु
	स्थिर पूर्णांक part_id;
	स्थिर पूर्णांक version_id;
	पूर्णांक amp_num;
	स्थिर u8 acpi_id[ACPI_ID_LEN];
	स्थिर bool direction[2]; // playback & capture support
	स्थिर अक्षर *dai_name;
	स्थिर काष्ठा snd_soc_ops *ops;

	पूर्णांक  (*init)(स्थिर काष्ठा snd_soc_acpi_link_adr *link,
		     काष्ठा snd_soc_dai_link *dai_links,
		     काष्ठा sof_sdw_codec_info *info,
		     bool playback);

	पूर्णांक (*निकास)(काष्ठा device *dev, काष्ठा snd_soc_dai_link *dai_link);
	bool late_probe;
	पूर्णांक (*codec_card_late_probe)(काष्ठा snd_soc_card *card);
पूर्ण;

काष्ठा mc_निजी अणु
	काष्ठा list_head hdmi_pcm_list;
	bool common_hdmi_codec_drv;
	bool idisp_codec;
	काष्ठा snd_soc_jack sdw_headset;
पूर्ण;

बाह्य अचिन्हित दीर्घ sof_sdw_quirk;

पूर्णांक sdw_startup(काष्ठा snd_pcm_substream *substream);
पूर्णांक sdw_prepare(काष्ठा snd_pcm_substream *substream);
पूर्णांक sdw_trigger(काष्ठा snd_pcm_substream *substream, पूर्णांक cmd);
पूर्णांक sdw_hw_मुक्त(काष्ठा snd_pcm_substream *substream);
व्योम sdw_shutकरोwn(काष्ठा snd_pcm_substream *substream);

/* generic HDMI support */
पूर्णांक sof_sdw_hdmi_init(काष्ठा snd_soc_pcm_runसमय *rtd);

पूर्णांक sof_sdw_hdmi_card_late_probe(काष्ठा snd_soc_card *card);

/* DMIC support */
पूर्णांक sof_sdw_dmic_init(काष्ठा snd_soc_pcm_runसमय *rtd);

/* RT711 support */
पूर्णांक sof_sdw_rt711_init(स्थिर काष्ठा snd_soc_acpi_link_adr *link,
		       काष्ठा snd_soc_dai_link *dai_links,
		       काष्ठा sof_sdw_codec_info *info,
		       bool playback);
पूर्णांक sof_sdw_rt711_निकास(काष्ठा device *dev, काष्ठा snd_soc_dai_link *dai_link);

/* RT711-SDCA support */
पूर्णांक sof_sdw_rt711_sdca_init(स्थिर काष्ठा snd_soc_acpi_link_adr *link,
			    काष्ठा snd_soc_dai_link *dai_links,
			    काष्ठा sof_sdw_codec_info *info,
			    bool playback);
पूर्णांक sof_sdw_rt711_sdca_निकास(काष्ठा device *dev, काष्ठा snd_soc_dai_link *dai_link);

/* RT700 support */
पूर्णांक sof_sdw_rt700_init(स्थिर काष्ठा snd_soc_acpi_link_adr *link,
		       काष्ठा snd_soc_dai_link *dai_links,
		       काष्ठा sof_sdw_codec_info *info,
		       bool playback);

/* RT1308 support */
बाह्य काष्ठा snd_soc_ops sof_sdw_rt1308_i2s_ops;

पूर्णांक sof_sdw_rt1308_init(स्थिर काष्ठा snd_soc_acpi_link_adr *link,
			काष्ठा snd_soc_dai_link *dai_links,
			काष्ठा sof_sdw_codec_info *info,
			bool playback);

/* RT1316 support */
पूर्णांक sof_sdw_rt1316_init(स्थिर काष्ठा snd_soc_acpi_link_adr *link,
			काष्ठा snd_soc_dai_link *dai_links,
			काष्ठा sof_sdw_codec_info *info,
			bool playback);

/* RT715 support */
पूर्णांक sof_sdw_rt715_init(स्थिर काष्ठा snd_soc_acpi_link_adr *link,
		       काष्ठा snd_soc_dai_link *dai_links,
		       काष्ठा sof_sdw_codec_info *info,
		       bool playback);

/* RT715-SDCA support */
पूर्णांक sof_sdw_rt715_sdca_init(स्थिर काष्ठा snd_soc_acpi_link_adr *link,
			    काष्ठा snd_soc_dai_link *dai_links,
			    काष्ठा sof_sdw_codec_info *info,
			    bool playback);

/* MAX98373 support */
पूर्णांक sof_sdw_mx8373_init(स्थिर काष्ठा snd_soc_acpi_link_adr *link,
			काष्ठा snd_soc_dai_link *dai_links,
			काष्ठा sof_sdw_codec_info *info,
			bool playback);

पूर्णांक sof_sdw_mx8373_late_probe(काष्ठा snd_soc_card *card);

/* RT5682 support */
पूर्णांक sof_sdw_rt5682_init(स्थिर काष्ठा snd_soc_acpi_link_adr *link,
			काष्ठा snd_soc_dai_link *dai_links,
			काष्ठा sof_sdw_codec_info *info,
			bool playback);

#पूर्ण_अगर
