<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
//
// MediaTek ALSA SoC Audio Control
//
// Copyright (c) 2020 MediaTek Inc.
// Author: Shane Chien <shane.chien@mediatek.com>
//

#समावेश <linux/pm_runसमय.स>

#समावेश "mt8192-afe-common.h"

क्रमागत अणु
	MTK_AFE_RATE_8K = 0,
	MTK_AFE_RATE_11K = 1,
	MTK_AFE_RATE_12K = 2,
	MTK_AFE_RATE_384K = 3,
	MTK_AFE_RATE_16K = 4,
	MTK_AFE_RATE_22K = 5,
	MTK_AFE_RATE_24K = 6,
	MTK_AFE_RATE_352K = 7,
	MTK_AFE_RATE_32K = 8,
	MTK_AFE_RATE_44K = 9,
	MTK_AFE_RATE_48K = 10,
	MTK_AFE_RATE_88K = 11,
	MTK_AFE_RATE_96K = 12,
	MTK_AFE_RATE_176K = 13,
	MTK_AFE_RATE_192K = 14,
	MTK_AFE_RATE_260K = 15,
पूर्ण;

क्रमागत अणु
	MTK_AFE_DAI_MEMIF_RATE_8K = 0,
	MTK_AFE_DAI_MEMIF_RATE_16K = 1,
	MTK_AFE_DAI_MEMIF_RATE_32K = 2,
	MTK_AFE_DAI_MEMIF_RATE_48K = 3,
पूर्ण;

क्रमागत अणु
	MTK_AFE_PCM_RATE_8K = 0,
	MTK_AFE_PCM_RATE_16K = 1,
	MTK_AFE_PCM_RATE_32K = 2,
	MTK_AFE_PCM_RATE_48K = 3,
पूर्ण;

अचिन्हित पूर्णांक mt8192_general_rate_transक्रमm(काष्ठा device *dev,
					   अचिन्हित पूर्णांक rate)
अणु
	चयन (rate) अणु
	हाल 8000:
		वापस MTK_AFE_RATE_8K;
	हाल 11025:
		वापस MTK_AFE_RATE_11K;
	हाल 12000:
		वापस MTK_AFE_RATE_12K;
	हाल 16000:
		वापस MTK_AFE_RATE_16K;
	हाल 22050:
		वापस MTK_AFE_RATE_22K;
	हाल 24000:
		वापस MTK_AFE_RATE_24K;
	हाल 32000:
		वापस MTK_AFE_RATE_32K;
	हाल 44100:
		वापस MTK_AFE_RATE_44K;
	हाल 48000:
		वापस MTK_AFE_RATE_48K;
	हाल 88200:
		वापस MTK_AFE_RATE_88K;
	हाल 96000:
		वापस MTK_AFE_RATE_96K;
	हाल 176400:
		वापस MTK_AFE_RATE_176K;
	हाल 192000:
		वापस MTK_AFE_RATE_192K;
	हाल 260000:
		वापस MTK_AFE_RATE_260K;
	हाल 352800:
		वापस MTK_AFE_RATE_352K;
	हाल 384000:
		वापस MTK_AFE_RATE_384K;
	शेष:
		dev_warn(dev, "%s(), rate %u invalid, use %d!!!\n",
			 __func__,
			 rate, MTK_AFE_RATE_48K);
		वापस MTK_AFE_RATE_48K;
	पूर्ण
पूर्ण

अटल अचिन्हित पूर्णांक dai_memअगर_rate_transक्रमm(काष्ठा device *dev,
					     अचिन्हित पूर्णांक rate)
अणु
	चयन (rate) अणु
	हाल 8000:
		वापस MTK_AFE_DAI_MEMIF_RATE_8K;
	हाल 16000:
		वापस MTK_AFE_DAI_MEMIF_RATE_16K;
	हाल 32000:
		वापस MTK_AFE_DAI_MEMIF_RATE_32K;
	हाल 48000:
		वापस MTK_AFE_DAI_MEMIF_RATE_48K;
	शेष:
		dev_warn(dev, "%s(), rate %u invalid, use %d!!!\n",
			 __func__,
			 rate, MTK_AFE_DAI_MEMIF_RATE_16K);
		वापस MTK_AFE_DAI_MEMIF_RATE_16K;
	पूर्ण
पूर्ण

अटल अचिन्हित पूर्णांक pcm_rate_transक्रमm(काष्ठा device *dev,
				       अचिन्हित पूर्णांक rate)
अणु
	चयन (rate) अणु
	हाल 8000:
		वापस MTK_AFE_PCM_RATE_8K;
	हाल 16000:
		वापस MTK_AFE_PCM_RATE_16K;
	हाल 32000:
		वापस MTK_AFE_PCM_RATE_32K;
	हाल 48000:
		वापस MTK_AFE_PCM_RATE_48K;
	शेष:
		dev_warn(dev, "%s(), rate %u invalid, use %d!!!\n",
			 __func__,
			 rate, MTK_AFE_PCM_RATE_32K);
		वापस MTK_AFE_PCM_RATE_32K;
	पूर्ण
पूर्ण

अचिन्हित पूर्णांक mt8192_rate_transक्रमm(काष्ठा device *dev,
				   अचिन्हित पूर्णांक rate, पूर्णांक aud_blk)
अणु
	चयन (aud_blk) अणु
	हाल MT8192_MEMIF_DAI:
	हाल MT8192_MEMIF_MOD_DAI:
		वापस dai_memअगर_rate_transक्रमm(dev, rate);
	हाल MT8192_DAI_PCM_1:
	हाल MT8192_DAI_PCM_2:
		वापस pcm_rate_transक्रमm(dev, rate);
	शेष:
		वापस mt8192_general_rate_transक्रमm(dev, rate);
	पूर्ण
पूर्ण

पूर्णांक mt8192_dai_set_priv(काष्ठा mtk_base_afe *afe, पूर्णांक id,
			पूर्णांक priv_size, स्थिर व्योम *priv_data)
अणु
	काष्ठा mt8192_afe_निजी *afe_priv = afe->platक्रमm_priv;
	व्योम *temp_data;

	temp_data = devm_kzalloc(afe->dev,
				 priv_size,
				 GFP_KERNEL);
	अगर (!temp_data)
		वापस -ENOMEM;

	अगर (priv_data)
		स_नकल(temp_data, priv_data, priv_size);

	afe_priv->dai_priv[id] = temp_data;

	वापस 0;
पूर्ण
