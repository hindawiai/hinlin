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

#अगर_अघोषित __SOF_PROBE_H
#घोषणा __SOF_PROBE_H

#समावेश <sound/sof/header.h>

काष्ठा snd_sof_dev;

#घोषणा SOF_PROBE_INVALID_NODE_ID अच_पूर्णांक_उच्च

काष्ठा sof_probe_dma अणु
	अचिन्हित पूर्णांक stream_tag;
	अचिन्हित पूर्णांक dma_buffer_size;
पूर्ण __packed;

क्रमागत sof_connection_purpose अणु
	SOF_CONNECTION_PURPOSE_EXTRACT = 1,
	SOF_CONNECTION_PURPOSE_INJECT,
पूर्ण;

काष्ठा sof_probe_poपूर्णांक_desc अणु
	अचिन्हित पूर्णांक buffer_id;
	अचिन्हित पूर्णांक purpose;
	अचिन्हित पूर्णांक stream_tag;
पूर्ण __packed;

काष्ठा sof_ipc_probe_dma_add_params अणु
	काष्ठा sof_ipc_cmd_hdr hdr;
	अचिन्हित पूर्णांक num_elems;
	काष्ठा sof_probe_dma dma[];
पूर्ण __packed;

काष्ठा sof_ipc_probe_info_params अणु
	काष्ठा sof_ipc_reply rhdr;
	अचिन्हित पूर्णांक num_elems;
	जोड़ अणु
		काष्ठा sof_probe_dma dma[0];
		काष्ठा sof_probe_poपूर्णांक_desc desc[0];
	पूर्ण;
पूर्ण __packed;

काष्ठा sof_ipc_probe_dma_हटाओ_params अणु
	काष्ठा sof_ipc_cmd_hdr hdr;
	अचिन्हित पूर्णांक num_elems;
	अचिन्हित पूर्णांक stream_tag[];
पूर्ण __packed;

काष्ठा sof_ipc_probe_poपूर्णांक_add_params अणु
	काष्ठा sof_ipc_cmd_hdr hdr;
	अचिन्हित पूर्णांक num_elems;
	काष्ठा sof_probe_poपूर्णांक_desc desc[];
पूर्ण __packed;

काष्ठा sof_ipc_probe_poपूर्णांक_हटाओ_params अणु
	काष्ठा sof_ipc_cmd_hdr hdr;
	अचिन्हित पूर्णांक num_elems;
	अचिन्हित पूर्णांक buffer_id[];
पूर्ण __packed;

पूर्णांक sof_ipc_probe_init(काष्ठा snd_sof_dev *sdev,
		u32 stream_tag, माप_प्रकार buffer_size);
पूर्णांक sof_ipc_probe_deinit(काष्ठा snd_sof_dev *sdev);
पूर्णांक sof_ipc_probe_dma_info(काष्ठा snd_sof_dev *sdev,
		काष्ठा sof_probe_dma **dma, माप_प्रकार *num_dma);
पूर्णांक sof_ipc_probe_dma_add(काष्ठा snd_sof_dev *sdev,
		काष्ठा sof_probe_dma *dma, माप_प्रकार num_dma);
पूर्णांक sof_ipc_probe_dma_हटाओ(काष्ठा snd_sof_dev *sdev,
		अचिन्हित पूर्णांक *stream_tag, माप_प्रकार num_stream_tag);
पूर्णांक sof_ipc_probe_poपूर्णांकs_info(काष्ठा snd_sof_dev *sdev,
		काष्ठा sof_probe_poपूर्णांक_desc **desc, माप_प्रकार *num_desc);
पूर्णांक sof_ipc_probe_poपूर्णांकs_add(काष्ठा snd_sof_dev *sdev,
		काष्ठा sof_probe_poपूर्णांक_desc *desc, माप_प्रकार num_desc);
पूर्णांक sof_ipc_probe_poपूर्णांकs_हटाओ(काष्ठा snd_sof_dev *sdev,
		अचिन्हित पूर्णांक *buffer_id, माप_प्रकार num_buffer_id);

#पूर्ण_अगर
