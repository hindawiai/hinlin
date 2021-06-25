<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 *  skl-i2s.h - i2s blob mapping
 *
 *  Copyright (C) 2017 Intel Corp
 *  Author: Subhransu S. Prusty < subhransu.s.prusty@पूर्णांकel.com>
 * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 *
 * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 */

#अगर_अघोषित __SOUND_SOC_SKL_I2S_H
#घोषणा __SOUND_SOC_SKL_I2S_H

#घोषणा SKL_I2S_MAX_TIME_SLOTS		8
#घोषणा SKL_MCLK_DIV_CLK_SRC_MASK	GENMASK(17, 16)

#घोषणा SKL_MNDSS_DIV_CLK_SRC_MASK	GENMASK(21, 20)
#घोषणा SKL_SHIFT(x)			(ffs(x) - 1)
#घोषणा SKL_MCLK_DIV_RATIO_MASK		GENMASK(11, 0)

#घोषणा is_legacy_blob(x) (x.signature != 0xEE)
#घोषणा ext_to_legacy_blob(i2s_config_blob_ext) \
	((काष्ठा skl_i2s_config_blob_legacy *) i2s_config_blob_ext)

#घोषणा get_clk_src(mclk, mask) \
		((mclk.mभागctrl & mask) >> SKL_SHIFT(mask))
काष्ठा skl_i2s_config अणु
	u32 ssc0;
	u32 ssc1;
	u32 sscto;
	u32 sspsp;
	u32 sstsa;
	u32 ssrsa;
	u32 ssc2;
	u32 sspsp2;
	u32 ssc3;
	u32 ssioc;
पूर्ण __packed;

काष्ठा skl_i2s_config_mclk अणु
	u32 mभागctrl;
	u32 mभागr;
पूर्ण;

काष्ठा skl_i2s_config_mclk_ext अणु
	u32 mभागctrl;
	u32 mभागr_count;
	u32 mभागr[];
पूर्ण __packed;

काष्ठा skl_i2s_config_blob_signature अणु
	u32 minor_ver : 8;
	u32 major_ver : 8;
	u32 resvdz : 8;
	u32 signature : 8;
पूर्ण __packed;

काष्ठा skl_i2s_config_blob_header अणु
	काष्ठा skl_i2s_config_blob_signature sig;
	u32 size;
पूर्ण;

/**
 * काष्ठा skl_i2s_config_blob_legacy - Structure defines I2S Gateway
 * configuration legacy blob
 *
 * @gtw_attr:		Gateway attribute क्रम the I2S Gateway
 * @tdm_ts_group:	TDM slot mapping against channels in the Gateway.
 * @i2s_cfg:		I2S HW रेजिस्टरs
 * @mclk:		MCLK घड़ी source and भागider values
 */
काष्ठा skl_i2s_config_blob_legacy अणु
	u32 gtw_attr;
	u32 tdm_ts_group[SKL_I2S_MAX_TIME_SLOTS];
	काष्ठा skl_i2s_config i2s_cfg;
	काष्ठा skl_i2s_config_mclk mclk;
पूर्ण;

काष्ठा skl_i2s_config_blob_ext अणु
	u32 gtw_attr;
	काष्ठा skl_i2s_config_blob_header hdr;
	u32 tdm_ts_group[SKL_I2S_MAX_TIME_SLOTS];
	काष्ठा skl_i2s_config i2s_cfg;
	काष्ठा skl_i2s_config_mclk_ext mclk;
पूर्ण __packed;
#पूर्ण_अगर /* __SOUND_SOC_SKL_I2S_H */
