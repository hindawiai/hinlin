<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Driver क्रम Digigram miXart soundcards
 *
 * मुख्य file with alsa callbacks
 *
 * Copyright (c) 2003 by Digigram <alsa@digigram.com>
 */


#समावेश <linux/init.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/pci.h>
#समावेश <linux/dma-mapping.h>
#समावेश <linux/module.h>
#समावेश <linux/mutex.h>
#समावेश <linux/slab.h>

#समावेश <sound/core.h>
#समावेश <sound/initval.h>
#समावेश <sound/info.h>
#समावेश <sound/control.h>
#समावेश <sound/pcm.h>
#समावेश <sound/pcm_params.h>
#समावेश "mixart.h"
#समावेश "mixart_hwdep.h"
#समावेश "mixart_core.h"
#समावेश "mixart_mixer.h"

#घोषणा CARD_NAME "miXart"

MODULE_AUTHOR("Digigram <alsa@digigram.com>");
MODULE_DESCRIPTION("Digigram " CARD_NAME);
MODULE_LICENSE("GPL");

अटल पूर्णांक index[SNDRV_CARDS] = SNDRV_DEFAULT_IDX;             /* Index 0-MAX */
अटल अक्षर *id[SNDRV_CARDS] = SNDRV_DEFAULT_STR;              /* ID क्रम this card */
अटल bool enable[SNDRV_CARDS] = SNDRV_DEFAULT_ENABLE_PNP;     /* Enable this card */

module_param_array(index, पूर्णांक, शून्य, 0444);
MODULE_PARM_DESC(index, "Index value for Digigram " CARD_NAME " soundcard.");
module_param_array(id, अक्षरp, शून्य, 0444);
MODULE_PARM_DESC(id, "ID string for Digigram " CARD_NAME " soundcard.");
module_param_array(enable, bool, शून्य, 0444);
MODULE_PARM_DESC(enable, "Enable Digigram " CARD_NAME " soundcard.");

/*
 */

अटल स्थिर काष्ठा pci_device_id snd_mixart_ids[] = अणु
	अणु PCI_VDEVICE(MOTOROLA, 0x0003), 0, पूर्ण, /* MC8240 */
	अणु 0, पूर्ण
पूर्ण;

MODULE_DEVICE_TABLE(pci, snd_mixart_ids);


अटल पूर्णांक mixart_set_pipe_state(काष्ठा mixart_mgr *mgr,
				 काष्ठा mixart_pipe *pipe, पूर्णांक start)
अणु
	काष्ठा mixart_group_state_req group_state;
	काष्ठा mixart_group_state_resp group_state_resp;
	काष्ठा mixart_msg request;
	पूर्णांक err;
	u32 प्रणाली_msg_uid;

	चयन(pipe->status) अणु
	हाल PIPE_RUNNING:
	हाल PIPE_CLOCK_SET:
		अगर(start) वापस 0; /* alपढ़ोy started */
		अवरोध;
	हाल PIPE_STOPPED:
		अगर(!start) वापस 0; /* alपढ़ोy stopped */
		अवरोध;
	शेष:
		dev_err(&mgr->pci->dev,
			"error mixart_set_pipe_state called with wrong pipe->status!\n");
		वापस -EINVAL;      /* function called with wrong pipe status */
	पूर्ण

	प्रणाली_msg_uid = 0x12345678; /* the event ! (take care: the MSB and two LSB's have to be 0) */

	/* रुको on the last MSG_SYSTEM_SEND_SYNCHRO_CMD command to be really finished */

	request.message_id = MSG_SYSTEM_WAIT_SYNCHRO_CMD;
	request.uid = (काष्ठा mixart_uid)अणु0,0पूर्ण;
	request.data = &प्रणाली_msg_uid;
	request.size = माप(प्रणाली_msg_uid);

	err = snd_mixart_send_msg_रुको_notअगर(mgr, &request, प्रणाली_msg_uid);
	अगर(err) अणु
		dev_err(&mgr->pci->dev,
			"error : MSG_SYSTEM_WAIT_SYNCHRO_CMD was not notified !\n");
		वापस err;
	पूर्ण

	/* start or stop the pipe (1 pipe) */

	स_रखो(&group_state, 0, माप(group_state));
	group_state.pipe_count = 1;
	group_state.pipe_uid[0] = pipe->group_uid;

	अगर(start)
		request.message_id = MSG_STREAM_START_STREAM_GRP_PACKET;
	अन्यथा
		request.message_id = MSG_STREAM_STOP_STREAM_GRP_PACKET;

	request.uid = pipe->group_uid; /*(काष्ठा mixart_uid)अणु0,0पूर्ण;*/
	request.data = &group_state;
	request.size = माप(group_state);

	err = snd_mixart_send_msg(mgr, &request, माप(group_state_resp), &group_state_resp);
	अगर (err < 0 || group_state_resp.txx_status != 0) अणु
		dev_err(&mgr->pci->dev,
			"error MSG_STREAM_ST***_STREAM_GRP_PACKET err=%x stat=%x !\n",
			err, group_state_resp.txx_status);
		वापस -EINVAL;
	पूर्ण

	अगर(start) अणु
		u32 stat = 0;

		group_state.pipe_count = 0; /* in हाल of start same command once again with pipe_count=0 */

		err = snd_mixart_send_msg(mgr, &request, माप(group_state_resp), &group_state_resp);
		अगर (err < 0 || group_state_resp.txx_status != 0) अणु
			dev_err(&mgr->pci->dev,
				"error MSG_STREAM_START_STREAM_GRP_PACKET err=%x stat=%x !\n",
				err, group_state_resp.txx_status);
 			वापस -EINVAL;
		पूर्ण

		/* in हाल of start send a synchro top */

		request.message_id = MSG_SYSTEM_SEND_SYNCHRO_CMD;
		request.uid = (काष्ठा mixart_uid)अणु0,0पूर्ण;
		request.data = शून्य;
		request.size = 0;

		err = snd_mixart_send_msg(mgr, &request, माप(stat), &stat);
		अगर (err < 0 || stat != 0) अणु
			dev_err(&mgr->pci->dev,
				"error MSG_SYSTEM_SEND_SYNCHRO_CMD err=%x stat=%x !\n",
				err, stat);
			वापस -EINVAL;
		पूर्ण

		pipe->status = PIPE_RUNNING;
	पूर्ण
	अन्यथा /* !start */
		pipe->status = PIPE_STOPPED;

	वापस 0;
पूर्ण


अटल पूर्णांक mixart_set_घड़ी(काष्ठा mixart_mgr *mgr,
			    काष्ठा mixart_pipe *pipe, अचिन्हित पूर्णांक rate)
अणु
	काष्ठा mixart_msg request;
	काष्ठा mixart_घड़ी_properties घड़ी_properties;
	काष्ठा mixart_घड़ी_properties_resp घड़ी_prop_resp;
	पूर्णांक err;

	चयन(pipe->status) अणु
	हाल PIPE_CLOCK_SET:
		अवरोध;
	हाल PIPE_RUNNING:
		अगर(rate != 0)
			अवरोध;
		fallthrough;
	शेष:
		अगर(rate == 0)
			वापस 0; /* nothing to करो */
		अन्यथा अणु
			dev_err(&mgr->pci->dev,
				"error mixart_set_clock(%d) called with wrong pipe->status !\n",
				rate);
			वापस -EINVAL;
		पूर्ण
	पूर्ण

	स_रखो(&घड़ी_properties, 0, माप(घड़ी_properties));
	घड़ी_properties.घड़ी_generic_type = (rate != 0) ? CGT_INTERNAL_CLOCK : CGT_NO_CLOCK;
	घड़ी_properties.घड़ी_mode = CM_STANDALONE;
	घड़ी_properties.frequency = rate;
	घड़ी_properties.nb_callers = 1; /* only one entry in uid_caller ! */
	घड़ी_properties.uid_caller[0] = pipe->group_uid;

	dev_dbg(&mgr->pci->dev, "mixart_set_clock to %d kHz\n", rate);

	request.message_id = MSG_CLOCK_SET_PROPERTIES;
	request.uid = mgr->uid_console_manager;
	request.data = &घड़ी_properties;
	request.size = माप(घड़ी_properties);

	err = snd_mixart_send_msg(mgr, &request, माप(घड़ी_prop_resp), &घड़ी_prop_resp);
	अगर (err < 0 || घड़ी_prop_resp.status != 0 || घड़ी_prop_resp.घड़ी_mode != CM_STANDALONE) अणु
		dev_err(&mgr->pci->dev,
			"error MSG_CLOCK_SET_PROPERTIES err=%x stat=%x mod=%x !\n",
			err, घड़ी_prop_resp.status, घड़ी_prop_resp.घड़ी_mode);
		वापस -EINVAL;
	पूर्ण

	अगर(rate)  pipe->status = PIPE_CLOCK_SET;
	अन्यथा      pipe->status = PIPE_RUNNING;

	वापस 0;
पूर्ण


/*
 *  Allocate or reference output pipe क्रम analog IOs (pcmp0/1)
 */
काष्ठा mixart_pipe *
snd_mixart_add_ref_pipe(काष्ठा snd_mixart *chip, पूर्णांक pcm_number, पूर्णांक capture,
			पूर्णांक monitoring)
अणु
	पूर्णांक stream_count;
	काष्ठा mixart_pipe *pipe;
	काष्ठा mixart_msg request;

	अगर(capture) अणु
		अगर (pcm_number == MIXART_PCM_ANALOG) अणु
			pipe = &(chip->pipe_in_ana);  /* analog inमाला_दो */
		पूर्ण अन्यथा अणु
			pipe = &(chip->pipe_in_dig); /* digital inमाला_दो */
		पूर्ण
		request.message_id = MSG_STREAM_ADD_OUTPUT_GROUP;
		stream_count = MIXART_CAPTURE_STREAMS;
	पूर्ण अन्यथा अणु
		अगर (pcm_number == MIXART_PCM_ANALOG) अणु
			pipe = &(chip->pipe_out_ana);  /* analog outमाला_दो */
		पूर्ण अन्यथा अणु
			pipe = &(chip->pipe_out_dig);  /* digital outमाला_दो */
		पूर्ण
		request.message_id = MSG_STREAM_ADD_INPUT_GROUP;
		stream_count = MIXART_PLAYBACK_STREAMS;
	पूर्ण

	/* a new stream is खोलोed and there are alपढ़ोy all streams in use */
	अगर( (monitoring == 0) && (pipe->references >= stream_count) ) अणु
		वापस शून्य;
	पूर्ण

	/* pipe is not yet defined */
	अगर( pipe->status == PIPE_UNDEFINED ) अणु
		पूर्णांक err, i;
		काष्ठा अणु
			काष्ठा mixart_streaming_group_req sgroup_req;
			काष्ठा mixart_streaming_group sgroup_resp;
		पूर्ण *buf;

		dev_dbg(chip->card->dev,
			"add_ref_pipe audio chip(%d) pcm(%d)\n",
			chip->chip_idx, pcm_number);

		buf = kदो_स्मृति(माप(*buf), GFP_KERNEL);
		अगर (!buf)
			वापस शून्य;

		request.uid = (काष्ठा mixart_uid)अणु0,0पूर्ण;      /* should be StreamManagerUID, but zero is OK अगर there is only one ! */
		request.data = &buf->sgroup_req;
		request.size = माप(buf->sgroup_req);

		स_रखो(&buf->sgroup_req, 0, माप(buf->sgroup_req));

		buf->sgroup_req.stream_count = stream_count;
		buf->sgroup_req.channel_count = 2;
		buf->sgroup_req.latency = 256;
		buf->sgroup_req.connector = pipe->uid_left_connector;  /* the left connector */

		क्रम (i=0; i<stream_count; i++) अणु
			पूर्णांक j;
			काष्ठा mixart_flowinfo *flowinfo;
			काष्ठा mixart_bufferinfo *bufferinfo;
			
			/* we करोn't yet know the क्रमmat, so config 16 bit pcm audio क्रम instance */
			buf->sgroup_req.stream_info[i].size_max_byte_frame = 1024;
			buf->sgroup_req.stream_info[i].size_max_sample_frame = 256;
			buf->sgroup_req.stream_info[i].nb_bytes_max_per_sample = MIXART_FLOAT_P__4_0_TO_HEX; /* is 4.0f */

			/* find the right bufferinfo_array */
			j = (chip->chip_idx * MIXART_MAX_STREAM_PER_CARD) + (pcm_number * (MIXART_PLAYBACK_STREAMS + MIXART_CAPTURE_STREAMS)) + i;
			अगर(capture) j += MIXART_PLAYBACK_STREAMS; /* in the array capture is behind playback */

			buf->sgroup_req.flow_entry[i] = j;

			flowinfo = (काष्ठा mixart_flowinfo *)chip->mgr->flowinfo.area;
			flowinfo[j].bufferinfo_array_phy_address = (u32)chip->mgr->bufferinfo.addr + (j * माप(काष्ठा mixart_bufferinfo));
			flowinfo[j].bufferinfo_count = 1;               /* 1 will set the miXart to ring-buffer mode ! */

			bufferinfo = (काष्ठा mixart_bufferinfo *)chip->mgr->bufferinfo.area;
			bufferinfo[j].buffer_address = 0;               /* buffer is not yet allocated */
			bufferinfo[j].available_length = 0;             /* buffer is not yet allocated */

			/* स्थिरruct the identअगरier of the stream buffer received in the पूर्णांकerrupts ! */
			bufferinfo[j].buffer_id = (chip->chip_idx << MIXART_NOTIFY_CARD_OFFSET) + (pcm_number << MIXART_NOTIFY_PCM_OFFSET ) + i;
			अगर(capture) अणु
				bufferinfo[j].buffer_id |= MIXART_NOTIFY_CAPT_MASK;
			पूर्ण
		पूर्ण

		err = snd_mixart_send_msg(chip->mgr, &request, माप(buf->sgroup_resp), &buf->sgroup_resp);
		अगर((err < 0) || (buf->sgroup_resp.status != 0)) अणु
			dev_err(chip->card->dev,
				"error MSG_STREAM_ADD_**PUT_GROUP err=%x stat=%x !\n",
				err, buf->sgroup_resp.status);
			kमुक्त(buf);
			वापस शून्य;
		पूर्ण

		pipe->group_uid = buf->sgroup_resp.group;     /* id of the pipe, as वापसed by embedded */
		pipe->stream_count = buf->sgroup_resp.stream_count;
		/* pipe->stream_uid[i] = buf->sgroup_resp.stream[i].stream_uid; */

		pipe->status = PIPE_STOPPED;
		kमुक्त(buf);
	पूर्ण

	अगर(monitoring)	pipe->monitoring = 1;
	अन्यथा		pipe->references++;

	वापस pipe;
पूर्ण


पूर्णांक snd_mixart_समाप्त_ref_pipe(काष्ठा mixart_mgr *mgr,
			     काष्ठा mixart_pipe *pipe, पूर्णांक monitoring)
अणु
	पूर्णांक err = 0;

	अगर(pipe->status == PIPE_UNDEFINED)
		वापस 0;

	अगर(monitoring)
		pipe->monitoring = 0;
	अन्यथा
		pipe->references--;

	अगर((pipe->references <= 0) && (pipe->monitoring == 0)) अणु

		काष्ठा mixart_msg request;
		काष्ठा mixart_delete_group_resp delete_resp;

		/* release the घड़ी */
		err = mixart_set_घड़ी( mgr, pipe, 0);
		अगर( err < 0 ) अणु
			dev_err(&mgr->pci->dev,
				"mixart_set_clock(0) return error!\n");
		पूर्ण

		/* stop the pipe */
		err = mixart_set_pipe_state(mgr, pipe, 0);
		अगर( err < 0 ) अणु
			dev_err(&mgr->pci->dev, "error stopping pipe!\n");
		पूर्ण

		request.message_id = MSG_STREAM_DELETE_GROUP;
		request.uid = (काष्ठा mixart_uid)अणु0,0पूर्ण;
		request.data = &pipe->group_uid;            /* the streaming group ! */
		request.size = माप(pipe->group_uid);

		/* delete the pipe */
		err = snd_mixart_send_msg(mgr, &request, माप(delete_resp), &delete_resp);
		अगर ((err < 0) || (delete_resp.status != 0)) अणु
			dev_err(&mgr->pci->dev,
				"error MSG_STREAM_DELETE_GROUP err(%x), status(%x)\n",
				err, delete_resp.status);
		पूर्ण

		pipe->group_uid = (काष्ठा mixart_uid)अणु0,0पूर्ण;
		pipe->stream_count = 0;
		pipe->status = PIPE_UNDEFINED;
	पूर्ण

	वापस err;
पूर्ण

अटल पूर्णांक mixart_set_stream_state(काष्ठा mixart_stream *stream, पूर्णांक start)
अणु
	काष्ठा snd_mixart *chip;
	काष्ठा mixart_stream_state_req stream_state_req;
	काष्ठा mixart_msg request;

	अगर(!stream->substream)
		वापस -EINVAL;

	स_रखो(&stream_state_req, 0, माप(stream_state_req));
	stream_state_req.stream_count = 1;
	stream_state_req.stream_info.stream_desc.uid_pipe = stream->pipe->group_uid;
	stream_state_req.stream_info.stream_desc.stream_idx = stream->substream->number;

	अगर (stream->substream->stream == SNDRV_PCM_STREAM_PLAYBACK)
		request.message_id = start ? MSG_STREAM_START_INPUT_STAGE_PACKET : MSG_STREAM_STOP_INPUT_STAGE_PACKET;
	अन्यथा
		request.message_id = start ? MSG_STREAM_START_OUTPUT_STAGE_PACKET : MSG_STREAM_STOP_OUTPUT_STAGE_PACKET;

	request.uid = (काष्ठा mixart_uid)अणु0,0पूर्ण;
	request.data = &stream_state_req;
	request.size = माप(stream_state_req);

	stream->असल_period_elapsed = 0;            /* reset stream pos      */
	stream->buf_periods = 0;
	stream->buf_period_frag = 0;

	chip = snd_pcm_substream_chip(stream->substream);

	वापस snd_mixart_send_msg_nonblock(chip->mgr, &request);
पूर्ण

/*
 *  Trigger callback
 */

अटल पूर्णांक snd_mixart_trigger(काष्ठा snd_pcm_substream *subs, पूर्णांक cmd)
अणु
	काष्ठा mixart_stream *stream = subs->runसमय->निजी_data;

	चयन (cmd) अणु
	हाल SNDRV_PCM_TRIGGER_START:

		dev_dbg(subs->pcm->card->dev, "SNDRV_PCM_TRIGGER_START\n");

		/* START_STREAM */
		अगर( mixart_set_stream_state(stream, 1) )
			वापस -EINVAL;

		stream->status = MIXART_STREAM_STATUS_RUNNING;

		अवरोध;
	हाल SNDRV_PCM_TRIGGER_STOP:

		/* STOP_STREAM */
		अगर( mixart_set_stream_state(stream, 0) )
			वापस -EINVAL;

		stream->status = MIXART_STREAM_STATUS_OPEN;

		dev_dbg(subs->pcm->card->dev, "SNDRV_PCM_TRIGGER_STOP\n");

		अवरोध;

	हाल SNDRV_PCM_TRIGGER_PAUSE_PUSH:
		/* TODO */
		stream->status = MIXART_STREAM_STATUS_PAUSE;
		dev_dbg(subs->pcm->card->dev, "SNDRV_PCM_PAUSE_PUSH\n");
		अवरोध;
	हाल SNDRV_PCM_TRIGGER_PAUSE_RELEASE:
		/* TODO */
		stream->status = MIXART_STREAM_STATUS_RUNNING;
		dev_dbg(subs->pcm->card->dev, "SNDRV_PCM_PAUSE_RELEASE\n");
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक mixart_sync_nonblock_events(काष्ठा mixart_mgr *mgr)
अणु
	अचिन्हित दीर्घ समयout = jअगरfies + HZ;
	जबतक (atomic_पढ़ो(&mgr->msg_processed) > 0) अणु
		अगर (समय_after(jअगरfies, समयout)) अणु
			dev_err(&mgr->pci->dev,
				"mixart: cannot process nonblock events!\n");
			वापस -EBUSY;
		पूर्ण
		schedule_समयout_unपूर्णांकerruptible(1);
	पूर्ण
	वापस 0;
पूर्ण

/*
 *  prepare callback क्रम all pcms
 */
अटल पूर्णांक snd_mixart_prepare(काष्ठा snd_pcm_substream *subs)
अणु
	काष्ठा snd_mixart *chip = snd_pcm_substream_chip(subs);
	काष्ठा mixart_stream *stream = subs->runसमय->निजी_data;

	/* TODO de faथईon non bloquante, rथऊappliquer les hw_params (rate, bits, codec) */

	dev_dbg(chip->card->dev, "snd_mixart_prepare\n");

	mixart_sync_nonblock_events(chip->mgr);

	/* only the first stream can choose the sample rate */
	/* the further खोलोed streams will be limited to its frequency (see खोलो) */
	अगर(chip->mgr->ref_count_rate == 1)
		chip->mgr->sample_rate = subs->runसमय->rate;

	/* set the घड़ी only once (first stream) on the same pipe */
	अगर(stream->pipe->references == 1) अणु
		अगर( mixart_set_घड़ी(chip->mgr, stream->pipe, subs->runसमय->rate) )
			वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण


अटल पूर्णांक mixart_set_क्रमmat(काष्ठा mixart_stream *stream, snd_pcm_क्रमmat_t क्रमmat)
अणु
	पूर्णांक err;
	काष्ठा snd_mixart *chip;
	काष्ठा mixart_msg request;
	काष्ठा mixart_stream_param_desc stream_param;
	काष्ठा mixart_वापस_uid resp;

	chip = snd_pcm_substream_chip(stream->substream);

	स_रखो(&stream_param, 0, माप(stream_param));

	stream_param.coding_type = CT_LINEAR;
	stream_param.number_of_channel = stream->channels;

	stream_param.sampling_freq = chip->mgr->sample_rate;
	अगर(stream_param.sampling_freq == 0)
		stream_param.sampling_freq = 44100; /* अगर frequency not yet defined, use some शेष */

	चयन(क्रमmat)अणु
	हाल SNDRV_PCM_FORMAT_U8:
		stream_param.sample_type = ST_INTEGER_8;
		stream_param.sample_size = 8;
		अवरोध;
	हाल SNDRV_PCM_FORMAT_S16_LE:
		stream_param.sample_type = ST_INTEGER_16LE;
		stream_param.sample_size = 16;
		अवरोध;
	हाल SNDRV_PCM_FORMAT_S16_BE:
		stream_param.sample_type = ST_INTEGER_16BE;
		stream_param.sample_size = 16;
		अवरोध;
	हाल SNDRV_PCM_FORMAT_S24_3LE:
		stream_param.sample_type = ST_INTEGER_24LE;
		stream_param.sample_size = 24;
		अवरोध;
	हाल SNDRV_PCM_FORMAT_S24_3BE:
		stream_param.sample_type = ST_INTEGER_24BE;
		stream_param.sample_size = 24;
		अवरोध;
	हाल SNDRV_PCM_FORMAT_FLOAT_LE:
		stream_param.sample_type = ST_FLOATING_POINT_32LE;
		stream_param.sample_size = 32;
		अवरोध;
	हाल  SNDRV_PCM_FORMAT_FLOAT_BE:
		stream_param.sample_type = ST_FLOATING_POINT_32BE;
		stream_param.sample_size = 32;
		अवरोध;
	शेष:
		dev_err(chip->card->dev,
			"error mixart_set_format() : unknown format\n");
		वापस -EINVAL;
	पूर्ण

	dev_dbg(chip->card->dev,
		"set SNDRV_PCM_FORMAT sample_type(%d) sample_size(%d) freq(%d) channels(%d)\n",
		   stream_param.sample_type, stream_param.sample_size, stream_param.sampling_freq, stream->channels);

	/* TODO: what अन्यथा to configure ? */
	/* stream_param.samples_per_frame = 2; */
	/* stream_param.bytes_per_frame = 4; */
	/* stream_param.bytes_per_sample = 2; */

	stream_param.pipe_count = 1;      /* set to 1 */
	stream_param.stream_count = 1;    /* set to 1 */
	stream_param.stream_desc[0].uid_pipe = stream->pipe->group_uid;
	stream_param.stream_desc[0].stream_idx = stream->substream->number;

	request.message_id = MSG_STREAM_SET_INPUT_STAGE_PARAM;
	request.uid = (काष्ठा mixart_uid)अणु0,0पूर्ण;
	request.data = &stream_param;
	request.size = माप(stream_param);

	err = snd_mixart_send_msg(chip->mgr, &request, माप(resp), &resp);
	अगर((err < 0) || resp.error_code) अणु
		dev_err(chip->card->dev,
			"MSG_STREAM_SET_INPUT_STAGE_PARAM err=%x; resp=%x\n",
			err, resp.error_code);
		वापस -EINVAL;
	पूर्ण
	वापस 0;
पूर्ण


/*
 *  HW_PARAMS callback क्रम all pcms
 */
अटल पूर्णांक snd_mixart_hw_params(काष्ठा snd_pcm_substream *subs,
                                काष्ठा snd_pcm_hw_params *hw)
अणु
	काष्ठा snd_mixart *chip = snd_pcm_substream_chip(subs);
	काष्ठा mixart_mgr *mgr = chip->mgr;
	काष्ठा mixart_stream *stream = subs->runसमय->निजी_data;
	snd_pcm_क्रमmat_t क्रमmat;
	पूर्णांक err;
	पूर्णांक channels;

	/* set up channels */
	channels = params_channels(hw);

	/*  set up क्रमmat क्रम the stream */
	क्रमmat = params_क्रमmat(hw);

	mutex_lock(&mgr->setup_mutex);

	/* update the stream levels */
	अगर( stream->pcm_number <= MIXART_PCM_DIGITAL ) अणु
		पूर्णांक is_aes = stream->pcm_number > MIXART_PCM_ANALOG;
		अगर( subs->stream == SNDRV_PCM_STREAM_PLAYBACK )
			mixart_update_playback_stream_level(chip, is_aes, subs->number);
		अन्यथा
			mixart_update_capture_stream_level( chip, is_aes);
	पूर्ण

	stream->channels = channels;

	/* set the क्रमmat to the board */
	err = mixart_set_क्रमmat(stream, क्रमmat);
	अगर(err < 0) अणु
		mutex_unlock(&mgr->setup_mutex);
		वापस err;
	पूर्ण

	अगर (subs->runसमय->buffer_changed) अणु
		काष्ठा mixart_bufferinfo *bufferinfo;
		पूर्णांक i = (chip->chip_idx * MIXART_MAX_STREAM_PER_CARD) + (stream->pcm_number * (MIXART_PLAYBACK_STREAMS+MIXART_CAPTURE_STREAMS)) + subs->number;
		अगर( subs->stream == SNDRV_PCM_STREAM_CAPTURE ) अणु
			i += MIXART_PLAYBACK_STREAMS; /* in array capture is behind playback */
		पूर्ण
		
		bufferinfo = (काष्ठा mixart_bufferinfo *)chip->mgr->bufferinfo.area;
		bufferinfo[i].buffer_address = subs->runसमय->dma_addr;
		bufferinfo[i].available_length = subs->runसमय->dma_bytes;
		/* bufferinfo[i].buffer_id  is alपढ़ोy defined */

		dev_dbg(chip->card->dev,
			"snd_mixart_hw_params(pcm %d) : dma_addr(%x) dma_bytes(%x) subs-number(%d)\n",
			i, bufferinfo[i].buffer_address,
				bufferinfo[i].available_length,
				subs->number);
	पूर्ण
	mutex_unlock(&mgr->setup_mutex);

	वापस 0;
पूर्ण

अटल पूर्णांक snd_mixart_hw_मुक्त(काष्ठा snd_pcm_substream *subs)
अणु
	काष्ठा snd_mixart *chip = snd_pcm_substream_chip(subs);
	mixart_sync_nonblock_events(chip->mgr);
	वापस 0;
पूर्ण



/*
 *  TODO CONFIGURATION SPACE क्रम all pcms, mono pcm must update channels_max
 */
अटल स्थिर काष्ठा snd_pcm_hardware snd_mixart_analog_caps =
अणु
	.info             = ( SNDRV_PCM_INFO_MMAP | SNDRV_PCM_INFO_INTERLEAVED |
			      SNDRV_PCM_INFO_MMAP_VALID |
			      SNDRV_PCM_INFO_PAUSE),
	.क्रमmats	  = ( SNDRV_PCM_FMTBIT_U8 |
			      SNDRV_PCM_FMTBIT_S16_LE | SNDRV_PCM_FMTBIT_S16_BE |
			      SNDRV_PCM_FMTBIT_S24_3LE | SNDRV_PCM_FMTBIT_S24_3BE |
			      SNDRV_PCM_FMTBIT_FLOAT_LE | SNDRV_PCM_FMTBIT_FLOAT_BE ),
	.rates            = SNDRV_PCM_RATE_CONTINUOUS | SNDRV_PCM_RATE_8000_48000,
	.rate_min         = 8000,
	.rate_max         = 48000,
	.channels_min     = 1,
	.channels_max     = 2,
	.buffer_bytes_max = (32*1024),
	.period_bytes_min = 256,                  /* 256 frames U8 mono*/
	.period_bytes_max = (16*1024),
	.periods_min      = 2,
	.periods_max      = (32*1024/256),
पूर्ण;

अटल स्थिर काष्ठा snd_pcm_hardware snd_mixart_digital_caps =
अणु
	.info             = ( SNDRV_PCM_INFO_MMAP | SNDRV_PCM_INFO_INTERLEAVED |
			      SNDRV_PCM_INFO_MMAP_VALID |
			      SNDRV_PCM_INFO_PAUSE),
	.क्रमmats	  = ( SNDRV_PCM_FMTBIT_U8 |
			      SNDRV_PCM_FMTBIT_S16_LE | SNDRV_PCM_FMTBIT_S16_BE |
			      SNDRV_PCM_FMTBIT_S24_3LE | SNDRV_PCM_FMTBIT_S24_3BE |
			      SNDRV_PCM_FMTBIT_FLOAT_LE | SNDRV_PCM_FMTBIT_FLOAT_BE ),
	.rates            = SNDRV_PCM_RATE_32000 | SNDRV_PCM_RATE_44100 | SNDRV_PCM_RATE_48000,
	.rate_min         = 32000,
	.rate_max         = 48000,
	.channels_min     = 1,
	.channels_max     = 2,
	.buffer_bytes_max = (32*1024),
	.period_bytes_min = 256,                  /* 256 frames U8 mono*/
	.period_bytes_max = (16*1024),
	.periods_min      = 2,
	.periods_max      = (32*1024/256),
पूर्ण;


अटल पूर्णांक snd_mixart_playback_खोलो(काष्ठा snd_pcm_substream *subs)
अणु
	काष्ठा snd_mixart            *chip = snd_pcm_substream_chip(subs);
	काष्ठा mixart_mgr        *mgr = chip->mgr;
	काष्ठा snd_pcm_runसमय *runसमय = subs->runसमय;
	काष्ठा snd_pcm *pcm = subs->pcm;
	काष्ठा mixart_stream     *stream;
	काष्ठा mixart_pipe       *pipe;
	पूर्णांक err = 0;
	पूर्णांक pcm_number;

	mutex_lock(&mgr->setup_mutex);

	अगर ( pcm == chip->pcm ) अणु
		pcm_number = MIXART_PCM_ANALOG;
		runसमय->hw = snd_mixart_analog_caps;
	पूर्ण अन्यथा अणु
		snd_BUG_ON(pcm != chip->pcm_dig);
		pcm_number = MIXART_PCM_DIGITAL;
		runसमय->hw = snd_mixart_digital_caps;
	पूर्ण
	dev_dbg(chip->card->dev,
		"snd_mixart_playback_open C%d/P%d/Sub%d\n",
		chip->chip_idx, pcm_number, subs->number);

	/* get stream info */
	stream = &(chip->playback_stream[pcm_number][subs->number]);

	अगर (stream->status != MIXART_STREAM_STATUS_FREE)अणु
		/* streams in use */
		dev_err(chip->card->dev,
			"snd_mixart_playback_open C%d/P%d/Sub%d in use\n",
			chip->chip_idx, pcm_number, subs->number);
		err = -EBUSY;
		जाओ _निकास_खोलो;
	पूर्ण

	/* get pipe poपूर्णांकer (out pipe) */
	pipe = snd_mixart_add_ref_pipe(chip, pcm_number, 0, 0);

	अगर (pipe == शून्य) अणु
		err = -EINVAL;
		जाओ _निकास_खोलो;
	पूर्ण

	/* start the pipe अगर necessary */
	err = mixart_set_pipe_state(chip->mgr, pipe, 1);
	अगर( err < 0 ) अणु
		dev_err(chip->card->dev, "error starting pipe!\n");
		snd_mixart_समाप्त_ref_pipe(chip->mgr, pipe, 0);
		err = -EINVAL;
		जाओ _निकास_खोलो;
	पूर्ण

	stream->pipe        = pipe;
	stream->pcm_number  = pcm_number;
	stream->status      = MIXART_STREAM_STATUS_OPEN;
	stream->substream   = subs;
	stream->channels    = 0; /* not configured yet */

	runसमय->निजी_data = stream;

	snd_pcm_hw_स्थिरraपूर्णांक_step(runसमय, 0, SNDRV_PCM_HW_PARAM_PERIOD_BYTES, 32);
	snd_pcm_hw_स्थिरraपूर्णांक_step(runसमय, 0, SNDRV_PCM_HW_PARAM_BUFFER_SIZE, 64);

	/* अगर a sample rate is alपढ़ोy used, another stream cannot change */
	अगर(mgr->ref_count_rate++) अणु
		अगर(mgr->sample_rate) अणु
			runसमय->hw.rate_min = runसमय->hw.rate_max = mgr->sample_rate;
		पूर्ण
	पूर्ण

 _निकास_खोलो:
	mutex_unlock(&mgr->setup_mutex);

	वापस err;
पूर्ण


अटल पूर्णांक snd_mixart_capture_खोलो(काष्ठा snd_pcm_substream *subs)
अणु
	काष्ठा snd_mixart            *chip = snd_pcm_substream_chip(subs);
	काष्ठा mixart_mgr        *mgr = chip->mgr;
	काष्ठा snd_pcm_runसमय *runसमय = subs->runसमय;
	काष्ठा snd_pcm *pcm = subs->pcm;
	काष्ठा mixart_stream     *stream;
	काष्ठा mixart_pipe       *pipe;
	पूर्णांक err = 0;
	पूर्णांक pcm_number;

	mutex_lock(&mgr->setup_mutex);

	अगर ( pcm == chip->pcm ) अणु
		pcm_number = MIXART_PCM_ANALOG;
		runसमय->hw = snd_mixart_analog_caps;
	पूर्ण अन्यथा अणु
		snd_BUG_ON(pcm != chip->pcm_dig);
		pcm_number = MIXART_PCM_DIGITAL;
		runसमय->hw = snd_mixart_digital_caps;
	पूर्ण

	runसमय->hw.channels_min = 2; /* क्रम instance, no mono */

	dev_dbg(chip->card->dev, "snd_mixart_capture_open C%d/P%d/Sub%d\n",
		chip->chip_idx, pcm_number, subs->number);

	/* get stream info */
	stream = &(chip->capture_stream[pcm_number]);

	अगर (stream->status != MIXART_STREAM_STATUS_FREE)अणु
		/* streams in use */
		dev_err(chip->card->dev,
			"snd_mixart_capture_open C%d/P%d/Sub%d in use\n",
			chip->chip_idx, pcm_number, subs->number);
		err = -EBUSY;
		जाओ _निकास_खोलो;
	पूर्ण

	/* get pipe poपूर्णांकer (in pipe) */
	pipe = snd_mixart_add_ref_pipe(chip, pcm_number, 1, 0);

	अगर (pipe == शून्य) अणु
		err = -EINVAL;
		जाओ _निकास_खोलो;
	पूर्ण

	/* start the pipe अगर necessary */
	err = mixart_set_pipe_state(chip->mgr, pipe, 1);
	अगर( err < 0 ) अणु
		dev_err(chip->card->dev, "error starting pipe!\n");
		snd_mixart_समाप्त_ref_pipe(chip->mgr, pipe, 0);
		err = -EINVAL;
		जाओ _निकास_खोलो;
	पूर्ण

	stream->pipe        = pipe;
	stream->pcm_number  = pcm_number;
	stream->status      = MIXART_STREAM_STATUS_OPEN;
	stream->substream   = subs;
	stream->channels    = 0; /* not configured yet */

	runसमय->निजी_data = stream;

	snd_pcm_hw_स्थिरraपूर्णांक_step(runसमय, 0, SNDRV_PCM_HW_PARAM_PERIOD_BYTES, 32);
	snd_pcm_hw_स्थिरraपूर्णांक_step(runसमय, 0, SNDRV_PCM_HW_PARAM_BUFFER_SIZE, 64);

	/* अगर a sample rate is alपढ़ोy used, another stream cannot change */
	अगर(mgr->ref_count_rate++) अणु
		अगर(mgr->sample_rate) अणु
			runसमय->hw.rate_min = runसमय->hw.rate_max = mgr->sample_rate;
		पूर्ण
	पूर्ण

 _निकास_खोलो:
	mutex_unlock(&mgr->setup_mutex);

	वापस err;
पूर्ण



अटल पूर्णांक snd_mixart_बंद(काष्ठा snd_pcm_substream *subs)
अणु
	काष्ठा snd_mixart *chip = snd_pcm_substream_chip(subs);
	काष्ठा mixart_mgr *mgr = chip->mgr;
	काष्ठा mixart_stream *stream = subs->runसमय->निजी_data;

	mutex_lock(&mgr->setup_mutex);

	dev_dbg(chip->card->dev, "snd_mixart_close C%d/P%d/Sub%d\n",
		chip->chip_idx, stream->pcm_number, subs->number);

	/* sample rate released */
	अगर(--mgr->ref_count_rate == 0) अणु
		mgr->sample_rate = 0;
	पूर्ण

	/* delete pipe */
	अगर (snd_mixart_समाप्त_ref_pipe(mgr, stream->pipe, 0 ) < 0) अणु

		dev_err(chip->card->dev,
			"error snd_mixart_kill_ref_pipe C%dP%d\n",
			chip->chip_idx, stream->pcm_number);
	पूर्ण

	stream->pipe      = शून्य;
	stream->status    = MIXART_STREAM_STATUS_FREE;
	stream->substream = शून्य;

	mutex_unlock(&mgr->setup_mutex);
	वापस 0;
पूर्ण


अटल snd_pcm_uframes_t snd_mixart_stream_poपूर्णांकer(काष्ठा snd_pcm_substream *subs)
अणु
	काष्ठा snd_pcm_runसमय *runसमय = subs->runसमय;
	काष्ठा mixart_stream   *stream  = runसमय->निजी_data;

	वापस (snd_pcm_uframes_t)((stream->buf_periods * runसमय->period_size) + stream->buf_period_frag);
पूर्ण



अटल स्थिर काष्ठा snd_pcm_ops snd_mixart_playback_ops = अणु
	.खोलो      = snd_mixart_playback_खोलो,
	.बंद     = snd_mixart_बंद,
	.prepare   = snd_mixart_prepare,
	.hw_params = snd_mixart_hw_params,
	.hw_मुक्त   = snd_mixart_hw_मुक्त,
	.trigger   = snd_mixart_trigger,
	.poपूर्णांकer   = snd_mixart_stream_poपूर्णांकer,
पूर्ण;

अटल स्थिर काष्ठा snd_pcm_ops snd_mixart_capture_ops = अणु
	.खोलो      = snd_mixart_capture_खोलो,
	.बंद     = snd_mixart_बंद,
	.prepare   = snd_mixart_prepare,
	.hw_params = snd_mixart_hw_params,
	.hw_मुक्त   = snd_mixart_hw_मुक्त,
	.trigger   = snd_mixart_trigger,
	.poपूर्णांकer   = snd_mixart_stream_poपूर्णांकer,
पूर्ण;

अटल व्योम pपुनः_स्मृतिate_buffers(काष्ठा snd_mixart *chip, काष्ठा snd_pcm *pcm)
अणु
#अगर 0
	काष्ठा snd_pcm_substream *subs;
	पूर्णांक stream;

	क्रम (stream = 0; stream < 2; stream++) अणु
		पूर्णांक idx = 0;
		क्रम (subs = pcm->streams[stream].substream; subs; subs = subs->next, idx++)
			/* set up the unique device id with the chip index */
			subs->dma_device.id = subs->pcm->device << 16 |
				subs->stream << 8 | (subs->number + 1) |
				(chip->chip_idx + 1) << 24;
	पूर्ण
#पूर्ण_अगर
	snd_pcm_set_managed_buffer_all(pcm, SNDRV_DMA_TYPE_DEV,
				       &chip->mgr->pci->dev,
				       32*1024, 32*1024);
पूर्ण

/*
 */
अटल पूर्णांक snd_mixart_pcm_analog(काष्ठा snd_mixart *chip)
अणु
	पूर्णांक err;
	काष्ठा snd_pcm *pcm;
	अक्षर name[32];

	प्र_लिखो(name, "miXart analog %d", chip->chip_idx);
	अगर ((err = snd_pcm_new(chip->card, name, MIXART_PCM_ANALOG,
			       MIXART_PLAYBACK_STREAMS,
			       MIXART_CAPTURE_STREAMS, &pcm)) < 0) अणु
		dev_err(chip->card->dev,
			"cannot create the analog pcm %d\n", chip->chip_idx);
		वापस err;
	पूर्ण

	pcm->निजी_data = chip;

	snd_pcm_set_ops(pcm, SNDRV_PCM_STREAM_PLAYBACK, &snd_mixart_playback_ops);
	snd_pcm_set_ops(pcm, SNDRV_PCM_STREAM_CAPTURE, &snd_mixart_capture_ops);

	pcm->info_flags = 0;
	pcm->nonatomic = true;
	म_नकल(pcm->name, name);

	pपुनः_स्मृतिate_buffers(chip, pcm);

	chip->pcm = pcm;
	वापस 0;
पूर्ण


/*
 */
अटल पूर्णांक snd_mixart_pcm_digital(काष्ठा snd_mixart *chip)
अणु
	पूर्णांक err;
	काष्ठा snd_pcm *pcm;
	अक्षर name[32];

	प्र_लिखो(name, "miXart AES/EBU %d", chip->chip_idx);
	अगर ((err = snd_pcm_new(chip->card, name, MIXART_PCM_DIGITAL,
			       MIXART_PLAYBACK_STREAMS,
			       MIXART_CAPTURE_STREAMS, &pcm)) < 0) अणु
		dev_err(chip->card->dev,
			"cannot create the digital pcm %d\n", chip->chip_idx);
		वापस err;
	पूर्ण

	pcm->निजी_data = chip;

	snd_pcm_set_ops(pcm, SNDRV_PCM_STREAM_PLAYBACK, &snd_mixart_playback_ops);
	snd_pcm_set_ops(pcm, SNDRV_PCM_STREAM_CAPTURE, &snd_mixart_capture_ops);

	pcm->info_flags = 0;
	pcm->nonatomic = true;
	म_नकल(pcm->name, name);

	pपुनः_स्मृतिate_buffers(chip, pcm);

	chip->pcm_dig = pcm;
	वापस 0;
पूर्ण

अटल पूर्णांक snd_mixart_chip_मुक्त(काष्ठा snd_mixart *chip)
अणु
	kमुक्त(chip);
	वापस 0;
पूर्ण

अटल पूर्णांक snd_mixart_chip_dev_मुक्त(काष्ठा snd_device *device)
अणु
	काष्ठा snd_mixart *chip = device->device_data;
	वापस snd_mixart_chip_मुक्त(chip);
पूर्ण


/*
 */
अटल पूर्णांक snd_mixart_create(काष्ठा mixart_mgr *mgr, काष्ठा snd_card *card, पूर्णांक idx)
अणु
	पूर्णांक err;
	काष्ठा snd_mixart *chip;
	अटल स्थिर काष्ठा snd_device_ops ops = अणु
		.dev_मुक्त = snd_mixart_chip_dev_मुक्त,
	पूर्ण;

	chip = kzalloc(माप(*chip), GFP_KERNEL);
	अगर (!chip)
		वापस -ENOMEM;

	chip->card = card;
	chip->chip_idx = idx;
	chip->mgr = mgr;
	card->sync_irq = mgr->irq;

	अगर ((err = snd_device_new(card, SNDRV_DEV_LOWLEVEL, chip, &ops)) < 0) अणु
		snd_mixart_chip_मुक्त(chip);
		वापस err;
	पूर्ण

	mgr->chip[idx] = chip;
	वापस 0;
पूर्ण

पूर्णांक snd_mixart_create_pcm(काष्ठा snd_mixart* chip)
अणु
	पूर्णांक err;

	err = snd_mixart_pcm_analog(chip);
	अगर (err < 0)
		वापस err;

	अगर(chip->mgr->board_type == MIXART_DAUGHTER_TYPE_AES) अणु

		err = snd_mixart_pcm_digital(chip);
		अगर (err < 0)
			वापस err;
	पूर्ण
	वापस err;
पूर्ण


/*
 * release all the cards asचिन्हित to a manager instance
 */
अटल पूर्णांक snd_mixart_मुक्त(काष्ठा mixart_mgr *mgr)
अणु
	अचिन्हित पूर्णांक i;

	क्रम (i = 0; i < mgr->num_cards; i++) अणु
		अगर (mgr->chip[i])
			snd_card_मुक्त(mgr->chip[i]->card);
	पूर्ण

	/* stop mailbox */
	snd_mixart_निकास_mailbox(mgr);

	/* release irq  */
	अगर (mgr->irq >= 0)
		मुक्त_irq(mgr->irq, mgr);

	/* reset board अगर some firmware was loaded */
	अगर(mgr->dsp_loaded) अणु
		snd_mixart_reset_board(mgr);
		dev_dbg(&mgr->pci->dev, "reset miXart !\n");
	पूर्ण

	/* release the i/o ports */
	क्रम (i = 0; i < 2; ++i)
		iounmap(mgr->mem[i].virt);

	pci_release_regions(mgr->pci);

	/* मुक्त flowarray */
	अगर(mgr->flowinfo.area) अणु
		snd_dma_मुक्त_pages(&mgr->flowinfo);
		mgr->flowinfo.area = शून्य;
	पूर्ण
	/* मुक्त bufferarray */
	अगर(mgr->bufferinfo.area) अणु
		snd_dma_मुक्त_pages(&mgr->bufferinfo);
		mgr->bufferinfo.area = शून्य;
	पूर्ण

	pci_disable_device(mgr->pci);
	kमुक्त(mgr);
	वापस 0;
पूर्ण

/*
 * proc पूर्णांकerface
 */

/*
  mixart_BA0 proc पूर्णांकerface क्रम BAR 0 - पढ़ो callback
 */
अटल sमाप_प्रकार snd_mixart_BA0_पढ़ो(काष्ठा snd_info_entry *entry,
				   व्योम *file_निजी_data,
				   काष्ठा file *file, अक्षर __user *buf,
				   माप_प्रकार count, loff_t pos)
अणु
	काष्ठा mixart_mgr *mgr = entry->निजी_data;

	count = count & ~3; /* make sure the पढ़ो size is a multiple of 4 bytes */
	अगर (copy_to_user_fromio(buf, MIXART_MEM(mgr, pos), count))
		वापस -EFAULT;
	वापस count;
पूर्ण

/*
  mixart_BA1 proc पूर्णांकerface क्रम BAR 1 - पढ़ो callback
 */
अटल sमाप_प्रकार snd_mixart_BA1_पढ़ो(काष्ठा snd_info_entry *entry,
				   व्योम *file_निजी_data,
				   काष्ठा file *file, अक्षर __user *buf,
				   माप_प्रकार count, loff_t pos)
अणु
	काष्ठा mixart_mgr *mgr = entry->निजी_data;

	count = count & ~3; /* make sure the पढ़ो size is a multiple of 4 bytes */
	अगर (copy_to_user_fromio(buf, MIXART_REG(mgr, pos), count))
		वापस -EFAULT;
	वापस count;
पूर्ण

अटल स्थिर काष्ठा snd_info_entry_ops snd_mixart_proc_ops_BA0 = अणु
	.पढ़ो   = snd_mixart_BA0_पढ़ो,
पूर्ण;

अटल स्थिर काष्ठा snd_info_entry_ops snd_mixart_proc_ops_BA1 = अणु
	.पढ़ो   = snd_mixart_BA1_पढ़ो,
पूर्ण;


अटल व्योम snd_mixart_proc_पढ़ो(काष्ठा snd_info_entry *entry, 
                                 काष्ठा snd_info_buffer *buffer)
अणु
	काष्ठा snd_mixart *chip = entry->निजी_data;        
	u32 ref; 

	snd_iम_लिखो(buffer, "Digigram miXart (alsa card %d)\n\n", chip->chip_idx);

	/* stats available when embedded OS is running */
	अगर (chip->mgr->dsp_loaded & ( 1 << MIXART_MOTHERBOARD_ELF_INDEX)) अणु
		snd_iम_लिखो(buffer, "- hardware -\n");
		चयन (chip->mgr->board_type ) अणु
		हाल MIXART_DAUGHTER_TYPE_NONE     : snd_iम_लिखो(buffer, "\tmiXart8 (no daughter board)\n\n"); अवरोध;
		हाल MIXART_DAUGHTER_TYPE_AES      : snd_iम_लिखो(buffer, "\tmiXart8 AES/EBU\n\n"); अवरोध;
		हाल MIXART_DAUGHTER_TYPE_COBRANET : snd_iम_लिखो(buffer, "\tmiXart8 Cobranet\n\n"); अवरोध;
		शेष:                             snd_iम_लिखो(buffer, "\tUNKNOWN!\n\n"); अवरोध;
		पूर्ण

		snd_iम_लिखो(buffer, "- system load -\n");	 

		/* get perf reference */

		ref = पढ़ोl_be( MIXART_MEM( chip->mgr, MIXART_PSEUDOREG_PERF_SYSTEM_LOAD_OFFSET));

		अगर (ref) अणु
			u32 mailbox   = 100 * पढ़ोl_be( MIXART_MEM( chip->mgr, MIXART_PSEUDOREG_PERF_MAILBX_LOAD_OFFSET)) / ref;
			u32 streaming = 100 * पढ़ोl_be( MIXART_MEM( chip->mgr, MIXART_PSEUDOREG_PERF_STREAM_LOAD_OFFSET)) / ref;
			u32 पूर्णांकerr    = 100 * पढ़ोl_be( MIXART_MEM( chip->mgr, MIXART_PSEUDOREG_PERF_INTERR_LOAD_OFFSET)) / ref;

			snd_iम_लिखो(buffer, "\tstreaming          : %d\n", streaming);
			snd_iम_लिखो(buffer, "\tmailbox            : %d\n", mailbox);
			snd_iम_लिखो(buffer, "\tinterrupts handling : %d\n\n", पूर्णांकerr);
		पूर्ण
	पूर्ण /* endअगर elf loaded */
पूर्ण

अटल व्योम snd_mixart_proc_init(काष्ठा snd_mixart *chip)
अणु
	काष्ठा snd_info_entry *entry;

	/* text पूर्णांकerface to पढ़ो perf and temp meters */
	snd_card_ro_proc_new(chip->card, "board_info", chip,
			     snd_mixart_proc_पढ़ो);

	अगर (! snd_card_proc_new(chip->card, "mixart_BA0", &entry)) अणु
		entry->content = SNDRV_INFO_CONTENT_DATA;
		entry->निजी_data = chip->mgr;	
		entry->c.ops = &snd_mixart_proc_ops_BA0;
		entry->size = MIXART_BA0_SIZE;
	पूर्ण
	अगर (! snd_card_proc_new(chip->card, "mixart_BA1", &entry)) अणु
		entry->content = SNDRV_INFO_CONTENT_DATA;
		entry->निजी_data = chip->mgr;
		entry->c.ops = &snd_mixart_proc_ops_BA1;
		entry->size = MIXART_BA1_SIZE;
	पूर्ण
पूर्ण
/* end of proc पूर्णांकerface */


/*
 *    probe function - creates the card manager
 */
अटल पूर्णांक snd_mixart_probe(काष्ठा pci_dev *pci,
			    स्थिर काष्ठा pci_device_id *pci_id)
अणु
	अटल पूर्णांक dev;
	काष्ठा mixart_mgr *mgr;
	अचिन्हित पूर्णांक i;
	पूर्णांक err;
	माप_प्रकार size;

	/*
	 */
	अगर (dev >= SNDRV_CARDS)
		वापस -ENODEV;
	अगर (! enable[dev]) अणु
		dev++;
		वापस -ENOENT;
	पूर्ण

	/* enable PCI device */
	अगर ((err = pci_enable_device(pci)) < 0)
		वापस err;
	pci_set_master(pci);

	/* check अगर we can restrict PCI DMA transfers to 32 bits */
	अगर (dma_set_mask(&pci->dev, DMA_BIT_MASK(32)) < 0) अणु
		dev_err(&pci->dev,
			"architecture does not support 32bit PCI busmaster DMA\n");
		pci_disable_device(pci);
		वापस -ENXIO;
	पूर्ण

	/*
	 */
	mgr = kzalloc(माप(*mgr), GFP_KERNEL);
	अगर (! mgr) अणु
		pci_disable_device(pci);
		वापस -ENOMEM;
	पूर्ण

	mgr->pci = pci;
	mgr->irq = -1;

	/* resource assignment */
	अगर ((err = pci_request_regions(pci, CARD_NAME)) < 0) अणु
		kमुक्त(mgr);
		pci_disable_device(pci);
		वापस err;
	पूर्ण
	क्रम (i = 0; i < 2; i++) अणु
		mgr->mem[i].phys = pci_resource_start(pci, i);
		mgr->mem[i].virt = pci_ioremap_bar(pci, i);
		अगर (!mgr->mem[i].virt) अणु
			dev_err(&pci->dev, "unable to remap resource 0x%lx\n",
			       mgr->mem[i].phys);
			snd_mixart_मुक्त(mgr);
			वापस -EBUSY;
		पूर्ण
	पूर्ण

	अगर (request_thपढ़ोed_irq(pci->irq, snd_mixart_पूर्णांकerrupt,
				 snd_mixart_thपढ़ोed_irq, IRQF_SHARED,
				 KBUILD_MODNAME, mgr)) अणु
		dev_err(&pci->dev, "unable to grab IRQ %d\n", pci->irq);
		snd_mixart_मुक्त(mgr);
		वापस -EBUSY;
	पूर्ण
	mgr->irq = pci->irq;

	/* init mailbox  */
	mgr->msg_fअगरo_पढ़ोptr = 0;
	mgr->msg_fअगरo_ग_लिखोptr = 0;

	mutex_init(&mgr->lock);
	mutex_init(&mgr->msg_lock);
	init_रुकोqueue_head(&mgr->msg_sleep);
	atomic_set(&mgr->msg_processed, 0);

	/* init setup mutex*/
	mutex_init(&mgr->setup_mutex);

	/* card assignment */
	mgr->num_cards = MIXART_MAX_CARDS; /* 4  FIXME: configurable? */
	क्रम (i = 0; i < mgr->num_cards; i++) अणु
		काष्ठा snd_card *card;
		अक्षर पंचांगpid[16];
		पूर्णांक idx;

		अगर (index[dev] < 0)
			idx = index[dev];
		अन्यथा
			idx = index[dev] + i;
		snम_लिखो(पंचांगpid, माप(पंचांगpid), "%s-%d", id[dev] ? id[dev] : "MIXART", i);
		err = snd_card_new(&pci->dev, idx, पंचांगpid, THIS_MODULE,
				   0, &card);

		अगर (err < 0) अणु
			dev_err(&pci->dev, "cannot allocate the card %d\n", i);
			snd_mixart_मुक्त(mgr);
			वापस err;
		पूर्ण

		म_नकल(card->driver, CARD_NAME);
		snम_लिखो(card->लघुname, माप(card->लघुname),
			 "Digigram miXart [PCM #%d]", i);
		snम_लिखो(card->दीर्घname, माप(card->दीर्घname),
			"Digigram miXart at 0x%lx & 0x%lx, irq %i [PCM #%d]",
			mgr->mem[0].phys, mgr->mem[1].phys, mgr->irq, i);

		अगर ((err = snd_mixart_create(mgr, card, i)) < 0) अणु
			snd_card_मुक्त(card);
			snd_mixart_मुक्त(mgr);
			वापस err;
		पूर्ण

		अगर(i==0) अणु
			/* init proc पूर्णांकerface only क्रम chip0 */
			snd_mixart_proc_init(mgr->chip[i]);
		पूर्ण

		अगर ((err = snd_card_रेजिस्टर(card)) < 0) अणु
			snd_mixart_मुक्त(mgr);
			वापस err;
		पूर्ण
	पूर्ण

	/* init firmware status (mgr->dsp_loaded reset in hwdep_new) */
	mgr->board_type = MIXART_DAUGHTER_TYPE_NONE;

	/* create array of streaminfo */
	size = PAGE_ALIGN( (MIXART_MAX_STREAM_PER_CARD * MIXART_MAX_CARDS *
			    माप(काष्ठा mixart_flowinfo)) );
	अगर (snd_dma_alloc_pages(SNDRV_DMA_TYPE_DEV, &pci->dev,
				size, &mgr->flowinfo) < 0) अणु
		snd_mixart_मुक्त(mgr);
		वापस -ENOMEM;
	पूर्ण
	/* init streaminfo_array */
	स_रखो(mgr->flowinfo.area, 0, size);

	/* create array of bufferinfo */
	size = PAGE_ALIGN( (MIXART_MAX_STREAM_PER_CARD * MIXART_MAX_CARDS *
			    माप(काष्ठा mixart_bufferinfo)) );
	अगर (snd_dma_alloc_pages(SNDRV_DMA_TYPE_DEV, &pci->dev,
				size, &mgr->bufferinfo) < 0) अणु
		snd_mixart_मुक्त(mgr);
		वापस -ENOMEM;
	पूर्ण
	/* init bufferinfo_array */
	स_रखो(mgr->bufferinfo.area, 0, size);

	/* set up firmware */
	err = snd_mixart_setup_firmware(mgr);
	अगर (err < 0) अणु
		snd_mixart_मुक्त(mgr);
		वापस err;
	पूर्ण

	pci_set_drvdata(pci, mgr);
	dev++;
	वापस 0;
पूर्ण

अटल व्योम snd_mixart_हटाओ(काष्ठा pci_dev *pci)
अणु
	snd_mixart_मुक्त(pci_get_drvdata(pci));
पूर्ण

अटल काष्ठा pci_driver mixart_driver = अणु
	.name = KBUILD_MODNAME,
	.id_table = snd_mixart_ids,
	.probe = snd_mixart_probe,
	.हटाओ = snd_mixart_हटाओ,
पूर्ण;

module_pci_driver(mixart_driver);
