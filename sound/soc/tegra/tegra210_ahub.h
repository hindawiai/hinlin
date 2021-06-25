<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * tegra210_ahub.h - TEGRA210 AHUB
 *
 * Copyright (c) 2020 NVIDIA CORPORATION.  All rights reserved.
 *
 */

#अगर_अघोषित __TEGRA210_AHUB__H__
#घोषणा __TEGRA210_AHUB__H__

/* Tegra210 specअगरic */
#घोषणा TEGRA210_XBAR_PART1_RX				0x200
#घोषणा TEGRA210_XBAR_PART2_RX				0x400
#घोषणा TEGRA210_XBAR_RX_STRIDE				0x4
#घोषणा TEGRA210_XBAR_AUDIO_RX_COUNT			90
#घोषणा TEGRA210_XBAR_REG_MASK_0			0xf1f03ff
#घोषणा TEGRA210_XBAR_REG_MASK_1			0x3f30031f
#घोषणा TEGRA210_XBAR_REG_MASK_2			0xff1cf313
#घोषणा TEGRA210_XBAR_REG_MASK_3			0x0
#घोषणा TEGRA210_XBAR_UPDATE_MAX_REG			3
/* Tegra186 specअगरic */
#घोषणा TEGRA186_XBAR_PART3_RX				0x600
#घोषणा TEGRA186_XBAR_AUDIO_RX_COUNT			115
#घोषणा TEGRA186_XBAR_REG_MASK_0			0xf3fffff
#घोषणा TEGRA186_XBAR_REG_MASK_1			0x3f310f1f
#घोषणा TEGRA186_XBAR_REG_MASK_2			0xff3cf311
#घोषणा TEGRA186_XBAR_REG_MASK_3			0x3f0f00ff
#घोषणा TEGRA186_XBAR_UPDATE_MAX_REG			4

#घोषणा TEGRA_XBAR_UPDATE_MAX_REG (TEGRA186_XBAR_UPDATE_MAX_REG)

#घोषणा TEGRA186_MAX_REGISTER_ADDR (TEGRA186_XBAR_PART3_RX +		\
	(TEGRA210_XBAR_RX_STRIDE * (TEGRA186_XBAR_AUDIO_RX_COUNT - 1)))

#घोषणा TEGRA210_MAX_REGISTER_ADDR (TEGRA210_XBAR_PART2_RX +		\
	(TEGRA210_XBAR_RX_STRIDE * (TEGRA210_XBAR_AUDIO_RX_COUNT - 1)))

#घोषणा MUX_REG(id) (TEGRA210_XBAR_RX_STRIDE * (id))

#घोषणा MUX_VALUE(npart, nbit) (1 + (nbit) + (npart) * 32)

#घोषणा SOC_VALUE_ENUM_WIDE(xreg, shअगरt, xmax, xtexts, xvalues)		\
	अणु								\
		.reg = xreg,						\
		.shअगरt_l = shअगरt,					\
		.shअगरt_r = shअगरt,					\
		.items = xmax,						\
		.texts = xtexts,					\
		.values = xvalues,					\
		.mask = xmax ? roundup_घात_of_two(xmax) - 1 : 0		\
	पूर्ण

#घोषणा SOC_VALUE_ENUM_WIDE_DECL(name, xreg, shअगरt, xtexts, xvalues)	\
	अटल काष्ठा soc_क्रमागत name =					\
		SOC_VALUE_ENUM_WIDE(xreg, shअगरt, ARRAY_SIZE(xtexts),	\
				    xtexts, xvalues)

#घोषणा MUX_ENUM_CTRL_DECL(ename, id)					\
	SOC_VALUE_ENUM_WIDE_DECL(ename##_क्रमागत, MUX_REG(id), 0,		\
				 tegra210_ahub_mux_texts,		\
				 tegra210_ahub_mux_values);		\
	अटल स्थिर काष्ठा snd_kcontrol_new ename##_control =		\
		SOC_DAPM_ENUM_EXT("Route", ename##_क्रमागत,		\
				  tegra_ahub_get_value_क्रमागत,		\
				  tegra_ahub_put_value_क्रमागत)

#घोषणा MUX_ENUM_CTRL_DECL_186(ename, id)				\
	SOC_VALUE_ENUM_WIDE_DECL(ename##_क्रमागत, MUX_REG(id), 0,		\
				 tegra186_ahub_mux_texts,		\
				 tegra186_ahub_mux_values);		\
	अटल स्थिर काष्ठा snd_kcontrol_new ename##_control =		\
		SOC_DAPM_ENUM_EXT("Route", ename##_क्रमागत,		\
				  tegra_ahub_get_value_क्रमागत,		\
				  tegra_ahub_put_value_क्रमागत)

#घोषणा WIDGETS(sname, ename)						     \
	SND_SOC_DAPM_AIF_IN(sname " XBAR-RX", शून्य, 0, SND_SOC_NOPM, 0, 0),  \
	SND_SOC_DAPM_AIF_OUT(sname " XBAR-TX", शून्य, 0, SND_SOC_NOPM, 0, 0), \
	SND_SOC_DAPM_MUX(sname " Mux", SND_SOC_NOPM, 0, 0,		     \
			 &ename##_control)

#घोषणा TX_WIDGETS(sname)						    \
	SND_SOC_DAPM_AIF_IN(sname " XBAR-RX", शून्य, 0, SND_SOC_NOPM, 0, 0), \
	SND_SOC_DAPM_AIF_OUT(sname " XBAR-TX", शून्य, 0, SND_SOC_NOPM, 0, 0)

#घोषणा DAI(sname)							\
	अणु								\
		.name = "XBAR-" #sname,					\
		.playback = अणु						\
			.stream_name = #sname " XBAR-Playback",		\
			.channels_min = 1,				\
			.channels_max = 16,				\
			.rates = SNDRV_PCM_RATE_8000_192000,		\
			.क्रमmats = SNDRV_PCM_FMTBIT_S8 |		\
				SNDRV_PCM_FMTBIT_S16_LE |		\
				SNDRV_PCM_FMTBIT_S24_LE |		\
				SNDRV_PCM_FMTBIT_S32_LE,		\
		पूर्ण,							\
		.capture = अणु						\
			.stream_name = #sname " XBAR-Capture",		\
			.channels_min = 1,				\
			.channels_max = 16,				\
			.rates = SNDRV_PCM_RATE_8000_192000,		\
			.क्रमmats = SNDRV_PCM_FMTBIT_S8 |		\
				SNDRV_PCM_FMTBIT_S16_LE |		\
				SNDRV_PCM_FMTBIT_S24_LE |		\
				SNDRV_PCM_FMTBIT_S32_LE,		\
		पूर्ण,							\
	पूर्ण

काष्ठा tegra_ahub_soc_data अणु
	स्थिर काष्ठा regmap_config *regmap_config;
	स्थिर काष्ठा snd_soc_component_driver *cmpnt_drv;
	काष्ठा snd_soc_dai_driver *dai_drv;
	अचिन्हित पूर्णांक mask[4];
	अचिन्हित पूर्णांक reg_count;
	अचिन्हित पूर्णांक num_dais;
पूर्ण;

काष्ठा tegra_ahub अणु
	स्थिर काष्ठा tegra_ahub_soc_data *soc_data;
	काष्ठा regmap *regmap;
	काष्ठा clk *clk;
पूर्ण;

#पूर्ण_अगर
