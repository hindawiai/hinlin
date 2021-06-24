<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0

#अगर_अघोषित __SPRD_PCM_DMA_H
#घोषणा __SPRD_PCM_DMA_H

#घोषणा DRV_NAME		"sprd_pcm_dma"
#घोषणा SPRD_PCM_CHANNEL_MAX	2

बाह्य स्थिर काष्ठा snd_compress_ops sprd_platक्रमm_compress_ops;

काष्ठा sprd_pcm_dma_params अणु
	dma_addr_t dev_phys[SPRD_PCM_CHANNEL_MAX];
	u32 datawidth[SPRD_PCM_CHANNEL_MAX];
	u32 fragment_len[SPRD_PCM_CHANNEL_MAX];
	स्थिर अक्षर *chan_name[SPRD_PCM_CHANNEL_MAX];
पूर्ण;

काष्ठा sprd_compr_playinfo अणु
	पूर्णांक total_समय;
	पूर्णांक current_समय;
	पूर्णांक total_data_length;
	पूर्णांक current_data_offset;
पूर्ण;

काष्ठा sprd_compr_params अणु
	u32 direction;
	u32 rate;
	u32 sample_rate;
	u32 channels;
	u32 क्रमmat;
	u32 period;
	u32 periods;
	u32 info_phys;
	u32 info_size;
पूर्ण;

काष्ठा sprd_compr_callback अणु
	व्योम (*drain_notअगरy)(व्योम *data);
	व्योम *drain_data;
पूर्ण;

काष्ठा sprd_compr_ops अणु
	पूर्णांक (*खोलो)(पूर्णांक str_id, काष्ठा sprd_compr_callback *cb);
	पूर्णांक (*बंद)(पूर्णांक str_id);
	पूर्णांक (*start)(पूर्णांक str_id);
	पूर्णांक (*stop)(पूर्णांक str_id);
	पूर्णांक (*छोड़ो)(पूर्णांक str_id);
	पूर्णांक (*छोड़ो_release)(पूर्णांक str_id);
	पूर्णांक (*drain)(पूर्णांक received_total);
	पूर्णांक (*set_params)(पूर्णांक str_id, काष्ठा sprd_compr_params *params);
पूर्ण;

काष्ठा sprd_compr_data अणु
	काष्ठा sprd_compr_ops *ops;
	काष्ठा sprd_pcm_dma_params *dma_params;
पूर्ण;

#पूर्ण_अगर /* __SPRD_PCM_DMA_H */
