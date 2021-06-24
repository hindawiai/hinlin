<शैली गुरु>
// SPDX-License-Identअगरier: (GPL-2.0-only OR BSD-3-Clause)
//
// This file is provided under a dual BSD/GPLv2 license.  When using or
// redistributing this file, you may करो so under either license.
//
// Copyright(c) 2019-2020 Intel Corporation. All rights reserved.
//
// Author: Cezary Rojewski <cezary.rojewski@पूर्णांकel.com>
//

#समावेश "sof-priv.h"
#समावेश "probe.h"

/**
 * sof_ipc_probe_init - initialize data probing
 * @sdev:		SOF sound device
 * @stream_tag:		Extractor stream tag
 * @buffer_size:	DMA buffer size to set क्रम extractor
 *
 * Host chooses whether extraction is supported or not by providing
 * valid stream tag to DSP. Once specअगरied, stream described by that
 * tag will be tied to DSP क्रम extraction क्रम the entire lअगरeसमय of
 * probe.
 *
 * Probing is initialized only once and each INIT request must be
 * matched by DEINIT call.
 */
पूर्णांक sof_ipc_probe_init(काष्ठा snd_sof_dev *sdev,
		u32 stream_tag, माप_प्रकार buffer_size)
अणु
	काष्ठा sof_ipc_probe_dma_add_params *msg;
	काष्ठा sof_ipc_reply reply;
	माप_प्रकार size = काष्ठा_size(msg, dma, 1);
	पूर्णांक ret;

	msg = kदो_स्मृति(size, GFP_KERNEL);
	अगर (!msg)
		वापस -ENOMEM;
	msg->hdr.size = size;
	msg->hdr.cmd = SOF_IPC_GLB_PROBE | SOF_IPC_PROBE_INIT;
	msg->num_elems = 1;
	msg->dma[0].stream_tag = stream_tag;
	msg->dma[0].dma_buffer_size = buffer_size;

	ret = sof_ipc_tx_message(sdev->ipc, msg->hdr.cmd, msg, msg->hdr.size,
			&reply, माप(reply));
	kमुक्त(msg);
	वापस ret;
पूर्ण
EXPORT_SYMBOL(sof_ipc_probe_init);

/**
 * sof_ipc_probe_deinit - cleanup after data probing
 * @sdev:	SOF sound device
 *
 * Host sends DEINIT request to मुक्त previously initialized probe
 * on DSP side once it is no दीर्घer needed. DEINIT only when there
 * are no probes connected and with all injectors detached.
 */
पूर्णांक sof_ipc_probe_deinit(काष्ठा snd_sof_dev *sdev)
अणु
	काष्ठा sof_ipc_cmd_hdr msg;
	काष्ठा sof_ipc_reply reply;

	msg.size = माप(msg);
	msg.cmd = SOF_IPC_GLB_PROBE | SOF_IPC_PROBE_DEINIT;

	वापस sof_ipc_tx_message(sdev->ipc, msg.cmd, &msg, msg.size,
			&reply, माप(reply));
पूर्ण
EXPORT_SYMBOL(sof_ipc_probe_deinit);

अटल पूर्णांक sof_ipc_probe_info(काष्ठा snd_sof_dev *sdev, अचिन्हित पूर्णांक cmd,
		व्योम **params, माप_प्रकार *num_params)
अणु
	काष्ठा sof_ipc_probe_info_params msg = अणुअणुअणु0पूर्णपूर्णपूर्ण;
	काष्ठा sof_ipc_probe_info_params *reply;
	माप_प्रकार bytes;
	पूर्णांक ret;

	*params = शून्य;
	*num_params = 0;

	reply = kzalloc(SOF_IPC_MSG_MAX_SIZE, GFP_KERNEL);
	अगर (!reply)
		वापस -ENOMEM;
	msg.rhdr.hdr.size = माप(msg);
	msg.rhdr.hdr.cmd = SOF_IPC_GLB_PROBE | cmd;

	ret = sof_ipc_tx_message(sdev->ipc, msg.rhdr.hdr.cmd, &msg,
			msg.rhdr.hdr.size, reply, SOF_IPC_MSG_MAX_SIZE);
	अगर (ret < 0 || reply->rhdr.error < 0)
		जाओ निकास;

	अगर (!reply->num_elems)
		जाओ निकास;

	अगर (cmd == SOF_IPC_PROBE_DMA_INFO)
		bytes = माप(reply->dma[0]);
	अन्यथा
		bytes = माप(reply->desc[0]);
	bytes *= reply->num_elems;
	*params = kmemdup(&reply->dma[0], bytes, GFP_KERNEL);
	अगर (!*params) अणु
		ret = -ENOMEM;
		जाओ निकास;
	पूर्ण
	*num_params = reply->num_elems;

निकास:
	kमुक्त(reply);
	वापस ret;
पूर्ण

/**
 * sof_ipc_probe_dma_info - retrieve list of active injection dmas
 * @sdev:	SOF sound device
 * @dma:	Returned list of active dmas
 * @num_dma:	Returned count of active dmas
 *
 * Host sends DMA_INFO request to obtain list of injection dmas it
 * can use to transfer data over with.
 *
 * Note that list contains only injection dmas as there is only one
 * extractor (dma) and it is always asचिन्हित on probing init.
 * DSP knows exactly where data from extraction probes is going to,
 * which is not the हाल क्रम injection where multiple streams
 * could be engaged.
 */
पूर्णांक sof_ipc_probe_dma_info(काष्ठा snd_sof_dev *sdev,
		काष्ठा sof_probe_dma **dma, माप_प्रकार *num_dma)
अणु
	वापस sof_ipc_probe_info(sdev, SOF_IPC_PROBE_DMA_INFO,
			(व्योम **)dma, num_dma);
पूर्ण
EXPORT_SYMBOL(sof_ipc_probe_dma_info);

/**
 * sof_ipc_probe_dma_add - attach to specअगरied dmas
 * @sdev:	SOF sound device
 * @dma:	List of streams (dmas) to attach to
 * @num_dma:	Number of elements in @dma
 *
 * Contrary to extraction, injection streams are never asचिन्हित
 * on init. Beक्रमe attempting any data injection, host is responsible
 * क्रम specअगरying streams which will be later used to transfer data
 * to connected probe poपूर्णांकs.
 */
पूर्णांक sof_ipc_probe_dma_add(काष्ठा snd_sof_dev *sdev,
		काष्ठा sof_probe_dma *dma, माप_प्रकार num_dma)
अणु
	काष्ठा sof_ipc_probe_dma_add_params *msg;
	काष्ठा sof_ipc_reply reply;
	माप_प्रकार size = काष्ठा_size(msg, dma, num_dma);
	पूर्णांक ret;

	msg = kदो_स्मृति(size, GFP_KERNEL);
	अगर (!msg)
		वापस -ENOMEM;
	msg->hdr.size = size;
	msg->num_elems = num_dma;
	msg->hdr.cmd = SOF_IPC_GLB_PROBE | SOF_IPC_PROBE_DMA_ADD;
	स_नकल(&msg->dma[0], dma, size - माप(*msg));

	ret = sof_ipc_tx_message(sdev->ipc, msg->hdr.cmd, msg, msg->hdr.size,
			&reply, माप(reply));
	kमुक्त(msg);
	वापस ret;
पूर्ण
EXPORT_SYMBOL(sof_ipc_probe_dma_add);

/**
 * sof_ipc_probe_dma_हटाओ - detach from specअगरied dmas
 * @sdev:		SOF sound device
 * @stream_tag:		List of stream tags to detach from
 * @num_stream_tag:	Number of elements in @stream_tag
 *
 * Host sends DMA_REMOVE request to मुक्त previously attached stream
 * from being occupied क्रम injection. Each detach operation should
 * match equivalent DMA_ADD. Detach only when all probes tied to
 * given stream have been disconnected.
 */
पूर्णांक sof_ipc_probe_dma_हटाओ(काष्ठा snd_sof_dev *sdev,
		अचिन्हित पूर्णांक *stream_tag, माप_प्रकार num_stream_tag)
अणु
	काष्ठा sof_ipc_probe_dma_हटाओ_params *msg;
	काष्ठा sof_ipc_reply reply;
	माप_प्रकार size = काष्ठा_size(msg, stream_tag, num_stream_tag);
	पूर्णांक ret;

	msg = kदो_स्मृति(size, GFP_KERNEL);
	अगर (!msg)
		वापस -ENOMEM;
	msg->hdr.size = size;
	msg->num_elems = num_stream_tag;
	msg->hdr.cmd = SOF_IPC_GLB_PROBE | SOF_IPC_PROBE_DMA_REMOVE;
	स_नकल(&msg->stream_tag[0], stream_tag, size - माप(*msg));

	ret = sof_ipc_tx_message(sdev->ipc, msg->hdr.cmd, msg, msg->hdr.size,
			&reply, माप(reply));
	kमुक्त(msg);
	वापस ret;
पूर्ण
EXPORT_SYMBOL(sof_ipc_probe_dma_हटाओ);

/**
 * sof_ipc_probe_poपूर्णांकs_info - retrieve list of active probe poपूर्णांकs
 * @sdev:	SOF sound device
 * @desc:	Returned list of active probes
 * @num_desc:	Returned count of active probes
 *
 * Host sends PROBE_POINT_INFO request to obtain list of active probe
 * poपूर्णांकs, valid क्रम disconnection when given probe is no दीर्घer
 * required.
 */
पूर्णांक sof_ipc_probe_poपूर्णांकs_info(काष्ठा snd_sof_dev *sdev,
		काष्ठा sof_probe_poपूर्णांक_desc **desc, माप_प्रकार *num_desc)
अणु
	वापस sof_ipc_probe_info(sdev, SOF_IPC_PROBE_POINT_INFO,
				 (व्योम **)desc, num_desc);
पूर्ण
EXPORT_SYMBOL(sof_ipc_probe_poपूर्णांकs_info);

/**
 * sof_ipc_probe_poपूर्णांकs_add - connect specअगरied probes
 * @sdev:	SOF sound device
 * @desc:	List of probe poपूर्णांकs to connect
 * @num_desc:	Number of elements in @desc
 *
 * Dynamically connects to provided set of endpoपूर्णांकs. Immediately
 * after connection is established, host must be prepared to
 * transfer data from or to target stream given the probing purpose.
 *
 * Each probe poपूर्णांक should be हटाओd using PROBE_POINT_REMOVE
 * request when no दीर्घer needed.
 */
पूर्णांक sof_ipc_probe_poपूर्णांकs_add(काष्ठा snd_sof_dev *sdev,
		काष्ठा sof_probe_poपूर्णांक_desc *desc, माप_प्रकार num_desc)
अणु
	काष्ठा sof_ipc_probe_poपूर्णांक_add_params *msg;
	काष्ठा sof_ipc_reply reply;
	माप_प्रकार size = काष्ठा_size(msg, desc, num_desc);
	पूर्णांक ret;

	msg = kदो_स्मृति(size, GFP_KERNEL);
	अगर (!msg)
		वापस -ENOMEM;
	msg->hdr.size = size;
	msg->num_elems = num_desc;
	msg->hdr.cmd = SOF_IPC_GLB_PROBE | SOF_IPC_PROBE_POINT_ADD;
	स_नकल(&msg->desc[0], desc, size - माप(*msg));

	ret = sof_ipc_tx_message(sdev->ipc, msg->hdr.cmd, msg, msg->hdr.size,
			&reply, माप(reply));
	kमुक्त(msg);
	वापस ret;
पूर्ण
EXPORT_SYMBOL(sof_ipc_probe_poपूर्णांकs_add);

/**
 * sof_ipc_probe_poपूर्णांकs_हटाओ - disconnect specअगरied probes
 * @sdev:		SOF sound device
 * @buffer_id:		List of probe poपूर्णांकs to disconnect
 * @num_buffer_id:	Number of elements in @desc
 *
 * Removes previously connected probes from list of active probe
 * poपूर्णांकs and मुक्तs all resources on DSP side.
 */
पूर्णांक sof_ipc_probe_poपूर्णांकs_हटाओ(काष्ठा snd_sof_dev *sdev,
		अचिन्हित पूर्णांक *buffer_id, माप_प्रकार num_buffer_id)
अणु
	काष्ठा sof_ipc_probe_poपूर्णांक_हटाओ_params *msg;
	काष्ठा sof_ipc_reply reply;
	माप_प्रकार size = काष्ठा_size(msg, buffer_id, num_buffer_id);
	पूर्णांक ret;

	msg = kदो_स्मृति(size, GFP_KERNEL);
	अगर (!msg)
		वापस -ENOMEM;
	msg->hdr.size = size;
	msg->num_elems = num_buffer_id;
	msg->hdr.cmd = SOF_IPC_GLB_PROBE | SOF_IPC_PROBE_POINT_REMOVE;
	स_नकल(&msg->buffer_id[0], buffer_id, size - माप(*msg));

	ret = sof_ipc_tx_message(sdev->ipc, msg->hdr.cmd, msg, msg->hdr.size,
			&reply, माप(reply));
	kमुक्त(msg);
	वापस ret;
पूर्ण
EXPORT_SYMBOL(sof_ipc_probe_poपूर्णांकs_हटाओ);
