<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 *  skl-ssp-clk.h - Skylake ssp घड़ी inक्रमmation and ipc काष्ठाure
 *
 *  Copyright (C) 2017 Intel Corp
 *  Author: Jaikrishna Nemallapudi <jaikrishnax.nemallapudi@पूर्णांकel.com>
 *  Author: Subhransu S. Prusty <subhransu.s.prusty@पूर्णांकel.com>
 *  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 *
 * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 */

#अगर_अघोषित SOUND_SOC_SKL_SSP_CLK_H
#घोषणा SOUND_SOC_SKL_SSP_CLK_H

#घोषणा SKL_MAX_SSP		6
/* xtal/cardinal/pll, parent of ssp घड़ीs and mclk */
#घोषणा SKL_MAX_CLK_SRC		3
#घोषणा SKL_MAX_SSP_CLK_TYPES	3 /* mclk, sclk, sclkfs */

#घोषणा SKL_MAX_CLK_CNT		(SKL_MAX_SSP * SKL_MAX_SSP_CLK_TYPES)

/* Max number of configurations supported क्रम each घड़ी */
#घोषणा SKL_MAX_CLK_RATES	10

#घोषणा SKL_SCLK_OFS		SKL_MAX_SSP
#घोषणा SKL_SCLKFS_OFS		(SKL_SCLK_OFS + SKL_MAX_SSP)

क्रमागत skl_clk_type अणु
	SKL_MCLK,
	SKL_SCLK,
	SKL_SCLK_FS,
पूर्ण;

क्रमागत skl_clk_src_type अणु
	SKL_XTAL,
	SKL_CARDINAL,
	SKL_PLL,
पूर्ण;

काष्ठा skl_clk_parent_src अणु
	u8 clk_id;
	स्थिर अक्षर *name;
	अचिन्हित दीर्घ rate;
	स्थिर अक्षर *parent_name;
पूर्ण;

काष्ठा skl_tlv_hdr अणु
	u32 type;
	u32 size;
पूर्ण;

काष्ठा skl_dmactrl_mclk_cfg अणु
	काष्ठा skl_tlv_hdr hdr;
	/* DMA Clk TLV params */
	u32 clk_warm_up:16;
	u32 mclk:1;
	u32 warm_up_over:1;
	u32 rsvd0:14;
	u32 clk_stop_delay:16;
	u32 keep_running:1;
	u32 clk_stop_over:1;
	u32 rsvd1:14;
पूर्ण;

काष्ठा skl_dmactrl_sclkfs_cfg अणु
	काष्ठा skl_tlv_hdr hdr;
	/* DMA SClk&FS  TLV params */
	u32 sampling_frequency;
	u32 bit_depth;
	u32 channel_map;
	u32 channel_config;
	u32 पूर्णांकerleaving_style;
	u32 number_of_channels : 8;
	u32 valid_bit_depth : 8;
	u32 sample_type : 8;
	u32 reserved : 8;
पूर्ण;

जोड़ skl_clk_ctrl_ipc अणु
	काष्ठा skl_dmactrl_mclk_cfg mclk;
	काष्ठा skl_dmactrl_sclkfs_cfg sclk_fs;
पूर्ण;

काष्ठा skl_clk_rate_cfg_table अणु
	अचिन्हित दीर्घ rate;
	जोड़ skl_clk_ctrl_ipc dma_ctl_ipc;
	व्योम *config;
पूर्ण;

/*
 * rate क्रम mclk will be in rates[0]. For sclk and sclkfs, rates[] store
 * all possible घड़ीs ssp can generate क्रम that platक्रमm.
 */
काष्ठा skl_ssp_clk अणु
	स्थिर अक्षर *name;
	स्थिर अक्षर *parent_name;
	काष्ठा skl_clk_rate_cfg_table rate_cfg[SKL_MAX_CLK_RATES];
पूर्ण;

काष्ठा skl_clk_pdata अणु
	काष्ठा skl_clk_parent_src *parent_clks;
	पूर्णांक num_clks;
	काष्ठा skl_ssp_clk *ssp_clks;
	व्योम *pvt_data;
पूर्ण;

#पूर्ण_अगर /* SOUND_SOC_SKL_SSP_CLK_H */
