<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Copyright(c) 2019 Intel Corporation.
 */

/*
 * This file defines helper functions used by multiple
 * Intel HDA based machine drivers.
 */

#अगर_अघोषित __HDA_DSP_COMMON_H
#घोषणा __HDA_DSP_COMMON_H

#समावेश <sound/hda_codec.h>
#समावेश <sound/hda_i915.h>
#समावेश "../../codecs/hdac_hda.h"

#अगर IS_ENABLED(CONFIG_SND_SOC_SOF_HDA_AUDIO_CODEC)
पूर्णांक hda_dsp_hdmi_build_controls(काष्ठा snd_soc_card *card,
				काष्ठा snd_soc_component *comp);
#अन्यथा
अटल अंतरभूत पूर्णांक hda_dsp_hdmi_build_controls(काष्ठा snd_soc_card *card,
					      काष्ठा snd_soc_component *comp)
अणु
	वापस -EINVAL;
पूर्ण
#पूर्ण_अगर

#पूर्ण_अगर /* __HDA_DSP_COMMON_H */
