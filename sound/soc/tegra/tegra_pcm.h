<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * tegra_pcm.h - Definitions क्रम Tegra PCM driver
 *
 * Author: Stephen Warren <swarren@nvidia.com>
 * Copyright (C) 2010,2012 - NVIDIA, Inc.
 *
 * Based on code copyright/by:
 *
 * Copyright (c) 2009-2010, NVIDIA Corporation.
 * Scott Peterson <speterson@nvidia.com>
 *
 * Copyright (C) 2010 Google, Inc.
 * Iliyan Malchev <malchev@google.com>
 */

#अगर_अघोषित __TEGRA_PCM_H__
#घोषणा __TEGRA_PCM_H__

#समावेश <sound/dmaengine_pcm.h>
#समावेश <sound/asound.h>

पूर्णांक tegra_pcm_स्थिरruct(काष्ठा snd_soc_component *component,
			काष्ठा snd_soc_pcm_runसमय *rtd);
व्योम tegra_pcm_deकाष्ठा(काष्ठा snd_soc_component *component,
			काष्ठा snd_pcm *pcm);
पूर्णांक tegra_pcm_खोलो(काष्ठा snd_soc_component *component,
		   काष्ठा snd_pcm_substream *substream);
पूर्णांक tegra_pcm_बंद(काष्ठा snd_soc_component *component,
		    काष्ठा snd_pcm_substream *substream);
पूर्णांक tegra_pcm_hw_params(काष्ठा snd_soc_component *component,
			काष्ठा snd_pcm_substream *substream,
			काष्ठा snd_pcm_hw_params *params);
पूर्णांक tegra_pcm_hw_मुक्त(काष्ठा snd_soc_component *component,
		      काष्ठा snd_pcm_substream *substream);
पूर्णांक tegra_pcm_mmap(काष्ठा snd_soc_component *component,
		   काष्ठा snd_pcm_substream *substream,
		   काष्ठा vm_area_काष्ठा *vma);
snd_pcm_uframes_t tegra_pcm_poपूर्णांकer(काष्ठा snd_soc_component *component,
				    काष्ठा snd_pcm_substream *substream);
पूर्णांक tegra_pcm_platक्रमm_रेजिस्टर(काष्ठा device *dev);
पूर्णांक tegra_pcm_platक्रमm_रेजिस्टर_with_chan_names(काष्ठा device *dev,
				काष्ठा snd_dmaengine_pcm_config *config,
				अक्षर *txdmachan, अक्षर *rxdmachan);
व्योम tegra_pcm_platक्रमm_unरेजिस्टर(काष्ठा device *dev);

#पूर्ण_अगर
