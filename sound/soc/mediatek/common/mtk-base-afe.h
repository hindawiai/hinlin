<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * mtk-base-afe.h  --  Mediatek base afe काष्ठाure
 *
 * Copyright (c) 2016 MediaTek Inc.
 * Author: Garlic Tseng <garlic.tseng@mediatek.com>
 */

#अगर_अघोषित _MTK_BASE_AFE_H_
#घोषणा _MTK_BASE_AFE_H_

#घोषणा MTK_STREAM_NUM (SNDRV_PCM_STREAM_LAST + 1)

काष्ठा mtk_base_memअगर_data अणु
	पूर्णांक id;
	स्थिर अक्षर *name;
	पूर्णांक reg_ofs_base;
	पूर्णांक reg_ofs_cur;
	पूर्णांक reg_ofs_end;
	पूर्णांक reg_ofs_base_msb;
	पूर्णांक reg_ofs_cur_msb;
	पूर्णांक reg_ofs_end_msb;
	पूर्णांक fs_reg;
	पूर्णांक fs_shअगरt;
	पूर्णांक fs_maskbit;
	पूर्णांक mono_reg;
	पूर्णांक mono_shअगरt;
	पूर्णांक mono_invert;
	पूर्णांक quad_ch_reg;
	पूर्णांक quad_ch_mask;
	पूर्णांक quad_ch_shअगरt;
	पूर्णांक enable_reg;
	पूर्णांक enable_shअगरt;
	पूर्णांक hd_reg;
	पूर्णांक hd_shअगरt;
	पूर्णांक hd_align_reg;
	पूर्णांक hd_align_mshअगरt;
	पूर्णांक msb_reg;
	पूर्णांक msb_shअगरt;
	पूर्णांक msb2_reg;
	पूर्णांक msb2_shअगरt;
	पूर्णांक agent_disable_reg;
	पूर्णांक agent_disable_shअगरt;
	/* playback memअगर only */
	पूर्णांक pbuf_reg;
	पूर्णांक pbuf_mask;
	पूर्णांक pbuf_shअगरt;
	पूर्णांक minlen_reg;
	पूर्णांक minlen_mask;
	पूर्णांक minlen_shअगरt;
पूर्ण;

काष्ठा mtk_base_irq_data अणु
	पूर्णांक id;
	पूर्णांक irq_cnt_reg;
	पूर्णांक irq_cnt_shअगरt;
	पूर्णांक irq_cnt_maskbit;
	पूर्णांक irq_fs_reg;
	पूर्णांक irq_fs_shअगरt;
	पूर्णांक irq_fs_maskbit;
	पूर्णांक irq_en_reg;
	पूर्णांक irq_en_shअगरt;
	पूर्णांक irq_clr_reg;
	पूर्णांक irq_clr_shअगरt;
पूर्ण;

काष्ठा device;
काष्ठा list_head;
काष्ठा mtk_base_afe_memअगर;
काष्ठा mtk_base_afe_irq;
काष्ठा mtk_base_afe_dai;
काष्ठा regmap;
काष्ठा snd_pcm_substream;
काष्ठा snd_soc_dai;

काष्ठा mtk_base_afe अणु
	व्योम __iomem *base_addr;
	काष्ठा device *dev;
	काष्ठा regmap *regmap;
	काष्ठा mutex irq_alloc_lock; /* dynamic alloc irq lock */

	अचिन्हित पूर्णांक स्थिर *reg_back_up_list;
	अचिन्हित पूर्णांक *reg_back_up;
	अचिन्हित पूर्णांक reg_back_up_list_num;

	पूर्णांक (*runसमय_suspend)(काष्ठा device *dev);
	पूर्णांक (*runसमय_resume)(काष्ठा device *dev);
	bool suspended;

	काष्ठा mtk_base_afe_memअगर *memअगर;
	पूर्णांक memअगर_size;
	काष्ठा mtk_base_afe_irq *irqs;
	पूर्णांक irqs_size;
	पूर्णांक memअगर_32bit_supported;

	काष्ठा list_head sub_dais;
	काष्ठा snd_soc_dai_driver *dai_drivers;
	अचिन्हित पूर्णांक num_dai_drivers;

	स्थिर काष्ठा snd_pcm_hardware *mtk_afe_hardware;
	पूर्णांक (*memअगर_fs)(काष्ठा snd_pcm_substream *substream,
			अचिन्हित पूर्णांक rate);
	पूर्णांक (*irq_fs)(काष्ठा snd_pcm_substream *substream,
		      अचिन्हित पूर्णांक rate);
	पूर्णांक (*get_dai_fs)(काष्ठा mtk_base_afe *afe,
			  पूर्णांक dai_id, अचिन्हित पूर्णांक rate);
	पूर्णांक (*get_memअगर_pbuf_size)(काष्ठा snd_pcm_substream *substream);

	पूर्णांक (*request_dram_resource)(काष्ठा device *dev);
	पूर्णांक (*release_dram_resource)(काष्ठा device *dev);

	व्योम *platक्रमm_priv;
पूर्ण;

काष्ठा mtk_base_afe_memअगर अणु
	अचिन्हित पूर्णांक phys_buf_addr;
	पूर्णांक buffer_size;
	काष्ठा snd_pcm_substream *substream;
	स्थिर काष्ठा mtk_base_memअगर_data *data;
	पूर्णांक irq_usage;
	पूर्णांक स्थिर_irq;
	अचिन्हित अक्षर *dma_area;
	dma_addr_t dma_addr;
	माप_प्रकार dma_bytes;
पूर्ण;

काष्ठा mtk_base_afe_irq अणु
	स्थिर काष्ठा mtk_base_irq_data *irq_data;
	पूर्णांक irq_occupyed;
पूर्ण;

काष्ठा mtk_base_afe_dai अणु
	काष्ठा snd_soc_dai_driver *dai_drivers;
	अचिन्हित पूर्णांक num_dai_drivers;

	स्थिर काष्ठा snd_kcontrol_new *controls;
	अचिन्हित पूर्णांक num_controls;
	स्थिर काष्ठा snd_soc_dapm_widget *dapm_widमाला_लो;
	अचिन्हित पूर्णांक num_dapm_widमाला_लो;
	स्थिर काष्ठा snd_soc_dapm_route *dapm_routes;
	अचिन्हित पूर्णांक num_dapm_routes;

	काष्ठा list_head list;
पूर्ण;

#पूर्ण_अगर

