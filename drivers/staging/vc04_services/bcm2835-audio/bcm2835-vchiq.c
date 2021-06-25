<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/* Copyright 2011 Broadcom Corporation.  All rights reserved. */

#समावेश <linux/slab.h>
#समावेश <linux/module.h>
#समावेश <linux/completion.h>
#समावेश "bcm2835.h"
#समावेश "vc_vchi_audioserv_defs.h"

काष्ठा bcm2835_audio_instance अणु
	काष्ठा device *dev;
	अचिन्हित पूर्णांक service_handle;
	काष्ठा completion msg_avail_comp;
	काष्ठा mutex vchi_mutex;
	काष्ठा bcm2835_alsa_stream *alsa_stream;
	पूर्णांक result;
	अचिन्हित पूर्णांक max_packet;
	लघु peer_version;
पूर्ण;

अटल bool क्रमce_bulk;
module_param(क्रमce_bulk, bool, 0444);
MODULE_PARM_DESC(क्रमce_bulk, "Force use of vchiq bulk for audio");

अटल व्योम bcm2835_audio_lock(काष्ठा bcm2835_audio_instance *instance)
अणु
	mutex_lock(&instance->vchi_mutex);
	vchiq_use_service(instance->service_handle);
पूर्ण

अटल व्योम bcm2835_audio_unlock(काष्ठा bcm2835_audio_instance *instance)
अणु
	vchiq_release_service(instance->service_handle);
	mutex_unlock(&instance->vchi_mutex);
पूर्ण

अटल पूर्णांक bcm2835_audio_send_msg_locked(काष्ठा bcm2835_audio_instance *instance,
					 काष्ठा vc_audio_msg *m, bool रुको)
अणु
	पूर्णांक status;

	अगर (रुको) अणु
		instance->result = -1;
		init_completion(&instance->msg_avail_comp);
	पूर्ण

	status = vchiq_queue_kernel_message(instance->service_handle,
					    m, माप(*m));
	अगर (status) अणु
		dev_err(instance->dev,
			"vchi message queue failed: %d, msg=%d\n",
			status, m->type);
		वापस -EIO;
	पूर्ण

	अगर (रुको) अणु
		अगर (!रुको_क्रम_completion_समयout(&instance->msg_avail_comp,
						 msecs_to_jअगरfies(10 * 1000))) अणु
			dev_err(instance->dev,
				"vchi message timeout, msg=%d\n", m->type);
			वापस -ETIMEDOUT;
		पूर्ण अन्यथा अगर (instance->result) अणु
			dev_err(instance->dev,
				"vchi message response error:%d, msg=%d\n",
				instance->result, m->type);
			वापस -EIO;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक bcm2835_audio_send_msg(काष्ठा bcm2835_audio_instance *instance,
				  काष्ठा vc_audio_msg *m, bool रुको)
अणु
	पूर्णांक err;

	bcm2835_audio_lock(instance);
	err = bcm2835_audio_send_msg_locked(instance, m, रुको);
	bcm2835_audio_unlock(instance);
	वापस err;
पूर्ण

अटल पूर्णांक bcm2835_audio_send_simple(काष्ठा bcm2835_audio_instance *instance,
				     पूर्णांक type, bool रुको)
अणु
	काष्ठा vc_audio_msg m = अणु .type = type पूर्ण;

	वापस bcm2835_audio_send_msg(instance, &m, रुको);
पूर्ण

अटल क्रमागत vchiq_status audio_vchi_callback(क्रमागत vchiq_reason reason,
					     काष्ठा vchiq_header *header,
					     अचिन्हित पूर्णांक handle, व्योम *userdata)
अणु
	काष्ठा bcm2835_audio_instance *instance = vchiq_get_service_userdata(handle);
	काष्ठा vc_audio_msg *m;

	अगर (reason != VCHIQ_MESSAGE_AVAILABLE)
		वापस VCHIQ_SUCCESS;

	m = (व्योम *)header->data;
	अगर (m->type == VC_AUDIO_MSG_TYPE_RESULT) अणु
		instance->result = m->result.success;
		complete(&instance->msg_avail_comp);
	पूर्ण अन्यथा अगर (m->type == VC_AUDIO_MSG_TYPE_COMPLETE) अणु
		अगर (m->complete.cookie1 != VC_AUDIO_WRITE_COOKIE1 ||
		    m->complete.cookie2 != VC_AUDIO_WRITE_COOKIE2)
			dev_err(instance->dev, "invalid cookie\n");
		अन्यथा
			bcm2835_playback_fअगरo(instance->alsa_stream,
					      m->complete.count);
	पूर्ण अन्यथा अणु
		dev_err(instance->dev, "unexpected callback type=%d\n", m->type);
	पूर्ण

	vchiq_release_message(handle, header);
	वापस VCHIQ_SUCCESS;
पूर्ण

अटल पूर्णांक
vc_vchi_audio_init(काष्ठा vchiq_instance *vchiq_instance,
		   काष्ठा bcm2835_audio_instance *instance)
अणु
	काष्ठा vchiq_service_params_kernel params = अणु
		.version		= VC_AUDIOSERV_VER,
		.version_min		= VC_AUDIOSERV_MIN_VER,
		.fourcc			= VCHIQ_MAKE_FOURCC('A', 'U', 'D', 'S'),
		.callback		= audio_vchi_callback,
		.userdata		= instance,
	पूर्ण;
	पूर्णांक status;

	/* Open the VCHI service connections */
	status = vchiq_खोलो_service(vchiq_instance, &params,
				    &instance->service_handle);

	अगर (status) अणु
		dev_err(instance->dev,
			"failed to open VCHI service connection (status=%d)\n",
			status);
		वापस -EPERM;
	पूर्ण

	/* Finished with the service क्रम now */
	vchiq_release_service(instance->service_handle);

	वापस 0;
पूर्ण

अटल व्योम vc_vchi_audio_deinit(काष्ठा bcm2835_audio_instance *instance)
अणु
	पूर्णांक status;

	mutex_lock(&instance->vchi_mutex);
	vchiq_use_service(instance->service_handle);

	/* Close all VCHI service connections */
	status = vchiq_बंद_service(instance->service_handle);
	अगर (status) अणु
		dev_err(instance->dev,
			"failed to close VCHI service connection (status=%d)\n",
			status);
	पूर्ण

	mutex_unlock(&instance->vchi_mutex);
पूर्ण

पूर्णांक bcm2835_new_vchi_ctx(काष्ठा device *dev, काष्ठा bcm2835_vchi_ctx *vchi_ctx)
अणु
	पूर्णांक ret;

	/* Initialize and create a VCHI connection */
	ret = vchiq_initialise(&vchi_ctx->instance);
	अगर (ret) अणु
		dev_err(dev, "failed to initialise VCHI instance (ret=%d)\n",
			ret);
		वापस -EIO;
	पूर्ण

	ret = vchiq_connect(vchi_ctx->instance);
	अगर (ret) अणु
		dev_dbg(dev, "failed to connect VCHI instance (ret=%d)\n",
			ret);

		kमुक्त(vchi_ctx->instance);
		vchi_ctx->instance = शून्य;

		वापस -EIO;
	पूर्ण

	वापस 0;
पूर्ण

व्योम bcm2835_मुक्त_vchi_ctx(काष्ठा bcm2835_vchi_ctx *vchi_ctx)
अणु
	/* Close the VCHI connection - it will also मुक्त vchi_ctx->instance */
	WARN_ON(vchiq_shutकरोwn(vchi_ctx->instance));

	vchi_ctx->instance = शून्य;
पूर्ण

पूर्णांक bcm2835_audio_खोलो(काष्ठा bcm2835_alsa_stream *alsa_stream)
अणु
	काष्ठा bcm2835_vchi_ctx *vchi_ctx = alsa_stream->chip->vchi_ctx;
	काष्ठा bcm2835_audio_instance *instance;
	पूर्णांक err;

	/* Allocate memory क्रम this instance */
	instance = kzalloc(माप(*instance), GFP_KERNEL);
	अगर (!instance)
		वापस -ENOMEM;
	mutex_init(&instance->vchi_mutex);
	instance->dev = alsa_stream->chip->dev;
	instance->alsa_stream = alsa_stream;
	alsa_stream->instance = instance;

	err = vc_vchi_audio_init(vchi_ctx->instance,
				 instance);
	अगर (err < 0)
		जाओ मुक्त_instance;

	err = bcm2835_audio_send_simple(instance, VC_AUDIO_MSG_TYPE_OPEN,
					false);
	अगर (err < 0)
		जाओ deinit;

	bcm2835_audio_lock(instance);
	vchiq_get_peer_version(instance->service_handle,
			       &instance->peer_version);
	bcm2835_audio_unlock(instance);
	अगर (instance->peer_version < 2 || क्रमce_bulk)
		instance->max_packet = 0; /* bulk transfer */
	अन्यथा
		instance->max_packet = 4000;

	वापस 0;

 deinit:
	vc_vchi_audio_deinit(instance);
 मुक्त_instance:
	alsa_stream->instance = शून्य;
	kमुक्त(instance);
	वापस err;
पूर्ण

पूर्णांक bcm2835_audio_set_ctls(काष्ठा bcm2835_alsa_stream *alsa_stream)
अणु
	काष्ठा bcm2835_chip *chip = alsa_stream->chip;
	काष्ठा vc_audio_msg m = अणुपूर्ण;

	m.type = VC_AUDIO_MSG_TYPE_CONTROL;
	m.control.dest = chip->dest;
	अगर (!chip->mute)
		m.control.volume = CHIP_MIN_VOLUME;
	अन्यथा
		m.control.volume = alsa2chip(chip->volume);

	वापस bcm2835_audio_send_msg(alsa_stream->instance, &m, true);
पूर्ण

पूर्णांक bcm2835_audio_set_params(काष्ठा bcm2835_alsa_stream *alsa_stream,
			     अचिन्हित पूर्णांक channels, अचिन्हित पूर्णांक samplerate,
			     अचिन्हित पूर्णांक bps)
अणु
	काष्ठा vc_audio_msg m = अणु
		 .type = VC_AUDIO_MSG_TYPE_CONFIG,
		 .config.channels = channels,
		 .config.samplerate = samplerate,
		 .config.bps = bps,
	पूर्ण;
	पूर्णांक err;

	/* resend ctls - alsa_stream may not have been खोलो when first send */
	err = bcm2835_audio_set_ctls(alsa_stream);
	अगर (err)
		वापस err;

	वापस bcm2835_audio_send_msg(alsa_stream->instance, &m, true);
पूर्ण

पूर्णांक bcm2835_audio_start(काष्ठा bcm2835_alsa_stream *alsa_stream)
अणु
	वापस bcm2835_audio_send_simple(alsa_stream->instance,
					 VC_AUDIO_MSG_TYPE_START, false);
पूर्ण

पूर्णांक bcm2835_audio_stop(काष्ठा bcm2835_alsa_stream *alsa_stream)
अणु
	वापस bcm2835_audio_send_simple(alsa_stream->instance,
					 VC_AUDIO_MSG_TYPE_STOP, false);
पूर्ण

/* FIXME: this करोesn't seem working as expected क्रम "draining" */
पूर्णांक bcm2835_audio_drain(काष्ठा bcm2835_alsa_stream *alsa_stream)
अणु
	काष्ठा vc_audio_msg m = अणु
		.type = VC_AUDIO_MSG_TYPE_STOP,
		.stop.draining = 1,
	पूर्ण;

	वापस bcm2835_audio_send_msg(alsa_stream->instance, &m, false);
पूर्ण

पूर्णांक bcm2835_audio_बंद(काष्ठा bcm2835_alsa_stream *alsa_stream)
अणु
	काष्ठा bcm2835_audio_instance *instance = alsa_stream->instance;
	पूर्णांक err;

	err = bcm2835_audio_send_simple(alsa_stream->instance,
					VC_AUDIO_MSG_TYPE_CLOSE, true);

	/* Stop the audio service */
	vc_vchi_audio_deinit(instance);
	alsa_stream->instance = शून्य;
	kमुक्त(instance);

	वापस err;
पूर्ण

पूर्णांक bcm2835_audio_ग_लिखो(काष्ठा bcm2835_alsa_stream *alsa_stream,
			अचिन्हित पूर्णांक size, व्योम *src)
अणु
	काष्ठा bcm2835_audio_instance *instance = alsa_stream->instance;
	काष्ठा vc_audio_msg m = अणु
		.type = VC_AUDIO_MSG_TYPE_WRITE,
		.ग_लिखो.count = size,
		.ग_लिखो.max_packet = instance->max_packet,
		.ग_लिखो.cookie1 = VC_AUDIO_WRITE_COOKIE1,
		.ग_लिखो.cookie2 = VC_AUDIO_WRITE_COOKIE2,
	पूर्ण;
	अचिन्हित पूर्णांक count;
	पूर्णांक err, status;

	अगर (!size)
		वापस 0;

	bcm2835_audio_lock(instance);
	err = bcm2835_audio_send_msg_locked(instance, &m, false);
	अगर (err < 0)
		जाओ unlock;

	count = size;
	अगर (!instance->max_packet) अणु
		/* Send the message to the videocore */
		status = vchiq_bulk_transmit(instance->service_handle, src,
					     count, शून्य,
					     VCHIQ_BULK_MODE_BLOCKING);
	पूर्ण अन्यथा अणु
		जबतक (count > 0) अणु
			पूर्णांक bytes = min(instance->max_packet, count);

			status = vchiq_queue_kernel_message(instance->service_handle,
							    src, bytes);
			src += bytes;
			count -= bytes;
		पूर्ण
	पूर्ण

	अगर (status) अणु
		dev_err(instance->dev,
			"failed on %d bytes transfer (status=%d)\n",
			size, status);
		err = -EIO;
	पूर्ण

 unlock:
	bcm2835_audio_unlock(instance);
	वापस err;
पूर्ण
