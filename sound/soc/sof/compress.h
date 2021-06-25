<शैली गुरु>
/* SPDX-License-Identअगरier: (GPL-2.0-only OR BSD-3-Clause) */
/*
 * This file is provided under a dual BSD/GPLv2 license.  When using or
 * redistributing this file, you may करो so under either license.
 *
 * Copyright(c) 2019-2020 Intel Corporation. All rights reserved.
 *
 * Author: Cezary Rojewski <cezary.rojewski@पूर्णांकel.com>
 */

#अगर_अघोषित __SOF_COMPRESS_H
#घोषणा __SOF_COMPRESS_H

#समावेश <sound/compress_driver.h>

बाह्य काष्ठा snd_compress_ops sof_probe_compressed_ops;

पूर्णांक sof_probe_compr_खोलो(काष्ठा snd_compr_stream *cstream,
		काष्ठा snd_soc_dai *dai);
पूर्णांक sof_probe_compr_मुक्त(काष्ठा snd_compr_stream *cstream,
		काष्ठा snd_soc_dai *dai);
पूर्णांक sof_probe_compr_set_params(काष्ठा snd_compr_stream *cstream,
		काष्ठा snd_compr_params *params, काष्ठा snd_soc_dai *dai);
पूर्णांक sof_probe_compr_trigger(काष्ठा snd_compr_stream *cstream, पूर्णांक cmd,
		काष्ठा snd_soc_dai *dai);
पूर्णांक sof_probe_compr_poपूर्णांकer(काष्ठा snd_compr_stream *cstream,
		काष्ठा snd_compr_tstamp *tstamp, काष्ठा snd_soc_dai *dai);
पूर्णांक sof_probe_compr_copy(काष्ठा snd_soc_component *component,
			 काष्ठा snd_compr_stream *cstream,
			 अक्षर __user *buf, माप_प्रकार count);

#पूर्ण_अगर
