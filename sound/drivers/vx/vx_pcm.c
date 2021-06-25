<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Driver क्रम Digigram VX soundcards
 *
 * PCM part
 *
 * Copyright (c) 2002,2003 by Takashi Iwai <tiwai@suse.de>
 *
 * STRATEGY
 *  क्रम playback, we send series of "chunks", which size is equal with the
 *  IBL size, typically 126 samples.  at each end of chunk, the end-of-buffer
 *  पूर्णांकerrupt is notअगरied, and the पूर्णांकerrupt handler will feed the next chunk.
 *
 *  the current position is calculated from the sample count RMH.
 *  pipe->transferred is the counter of data which has been alपढ़ोy transferred.
 *  अगर this counter reaches to the period size, snd_pcm_period_elapsed() will
 *  be issued.
 *
 *  क्रम capture, the situation is much easier.
 *  to get a low latency response, we'll check the capture streams at each
 *  पूर्णांकerrupt (capture stream has no EOB notअगरication).  अगर the pending
 *  data is accumulated to the period size, snd_pcm_period_elapsed() is
 *  called and the poपूर्णांकer is updated.
 *
 *  the current poपूर्णांक of पढ़ो buffer is kept in pipe->hw_ptr.  note that
 *  this is in bytes.
 *
 * TODO
 *  - linked trigger क्रम full-duplex mode.
 *  - scheduled action on the stream.
 */

#समावेश <linux/slab.h>
#समावेश <linux/delay.h>
#समावेश <sound/core.h>
#समावेश <sound/asoundef.h>
#समावेश <sound/pcm.h>
#समावेश <sound/vx_core.h>
#समावेश "vx_cmd.h"


/*
 * पढ़ो three pending pcm bytes via inb()
 */
अटल व्योम vx_pcm_पढ़ो_per_bytes(काष्ठा vx_core *chip, काष्ठा snd_pcm_runसमय *runसमय,
				  काष्ठा vx_pipe *pipe)
अणु
	पूर्णांक offset = pipe->hw_ptr;
	अचिन्हित अक्षर *buf = (अचिन्हित अक्षर *)(runसमय->dma_area + offset);
	*buf++ = vx_inb(chip, RXH);
	अगर (++offset >= pipe->buffer_bytes) अणु
		offset = 0;
		buf = (अचिन्हित अक्षर *)runसमय->dma_area;
	पूर्ण
	*buf++ = vx_inb(chip, RXM);
	अगर (++offset >= pipe->buffer_bytes) अणु
		offset = 0;
		buf = (अचिन्हित अक्षर *)runसमय->dma_area;
	पूर्ण
	*buf++ = vx_inb(chip, RXL);
	अगर (++offset >= pipe->buffer_bytes) अणु
		offset = 0;
	पूर्ण
	pipe->hw_ptr = offset;
पूर्ण

/*
 * vx_set_pcx_समय - convert from the PC समय to the RMH status समय.
 * @pc_समय: the poपूर्णांकer क्रम the PC-समय to set
 * @dsp_समय: the poपूर्णांकer क्रम RMH status समय array
 */
अटल व्योम vx_set_pcx_समय(काष्ठा vx_core *chip, pcx_समय_प्रकार *pc_समय,
			    अचिन्हित पूर्णांक *dsp_समय)
अणु
	dsp_समय[0] = (अचिन्हित पूर्णांक)((*pc_समय) >> 24) & PCX_TIME_HI_MASK;
	dsp_समय[1] = (अचिन्हित पूर्णांक)(*pc_समय) &  MASK_DSP_WORD;
पूर्ण

/*
 * vx_set_dअगरfered_समय - set the dअगरfered समय अगर specअगरied
 * @rmh: the rmh record to modअगरy
 * @pipe: the pipe to be checked
 *
 * अगर the pipe is programmed with the dअगरfered समय, set the DSP समय
 * on the rmh and changes its command length.
 *
 * वापसs the increase of the command length.
 */
अटल पूर्णांक vx_set_dअगरfered_समय(काष्ठा vx_core *chip, काष्ठा vx_rmh *rmh,
				काष्ठा vx_pipe *pipe)
अणु
	/* Update The length added to the RMH command by the बारtamp */
	अगर (! (pipe->dअगरfered_type & DC_DIFFERED_DELAY))
		वापस 0;
		
	/* Set the T bit */
	rmh->Cmd[0] |= DSP_DIFFERED_COMMAND_MASK;

	/* Time stamp is the 1st following parameter */
	vx_set_pcx_समय(chip, &pipe->pcx_समय, &rmh->Cmd[1]);

	/* Add the flags to a notअगरied dअगरfered command */
	अगर (pipe->dअगरfered_type & DC_NOTIFY_DELAY)
		rmh->Cmd[1] |= NOTIFY_MASK_TIME_HIGH ;

	/* Add the flags to a multiple dअगरfered command */
	अगर (pipe->dअगरfered_type & DC_MULTIPLE_DELAY)
		rmh->Cmd[1] |= MULTIPLE_MASK_TIME_HIGH;

	/* Add the flags to a stream-समय dअगरfered command */
	अगर (pipe->dअगरfered_type & DC_STREAM_TIME_DELAY)
		rmh->Cmd[1] |= STREAM_MASK_TIME_HIGH;
		
	rmh->LgCmd += 2;
	वापस 2;
पूर्ण

/*
 * vx_set_stream_क्रमmat - send the stream क्रमmat command
 * @pipe: the affected pipe
 * @data: क्रमmat biपंचांगask
 */
अटल पूर्णांक vx_set_stream_क्रमmat(काष्ठा vx_core *chip, काष्ठा vx_pipe *pipe,
				अचिन्हित पूर्णांक data)
अणु
	काष्ठा vx_rmh rmh;

	vx_init_rmh(&rmh, pipe->is_capture ?
		    CMD_FORMAT_STREAM_IN : CMD_FORMAT_STREAM_OUT);
	rmh.Cmd[0] |= pipe->number << FIELD_SIZE;

        /* Command might be दीर्घer since we may have to add a बारtamp */
	vx_set_dअगरfered_समय(chip, &rmh, pipe);

	rmh.Cmd[rmh.LgCmd] = (data & 0xFFFFFF00) >> 8;
	rmh.Cmd[rmh.LgCmd + 1] = (data & 0xFF) << 16 /*| (datal & 0xFFFF00) >> 8*/;
	rmh.LgCmd += 2;
    
	वापस vx_send_msg(chip, &rmh);
पूर्ण


/*
 * vx_set_क्रमmat - set the क्रमmat of a pipe
 * @pipe: the affected pipe
 * @runसमय: pcm runसमय instance to be referred
 *
 * वापसs 0 अगर successful, or a negative error code.
 */
अटल पूर्णांक vx_set_क्रमmat(काष्ठा vx_core *chip, काष्ठा vx_pipe *pipe,
			 काष्ठा snd_pcm_runसमय *runसमय)
अणु
	अचिन्हित पूर्णांक header = HEADER_FMT_BASE;

	अगर (runसमय->channels == 1)
		header |= HEADER_FMT_MONO;
	अगर (snd_pcm_क्रमmat_little_endian(runसमय->क्रमmat))
		header |= HEADER_FMT_INTEL;
	अगर (runसमय->rate < 32000 && runसमय->rate > 11025)
		header |= HEADER_FMT_UPTO32;
	अन्यथा अगर (runसमय->rate <= 11025)
		header |= HEADER_FMT_UPTO11;

	चयन (snd_pcm_क्रमmat_physical_width(runसमय->क्रमmat)) अणु
	// हाल 8: अवरोध;
	हाल 16: header |= HEADER_FMT_16BITS; अवरोध;
	हाल 24: header |= HEADER_FMT_24BITS; अवरोध;
	शेष : 
		snd_BUG();
		वापस -EINVAL;
	पूर्ण

	वापस vx_set_stream_क्रमmat(chip, pipe, header);
पूर्ण

/*
 * set / query the IBL size
 */
अटल पूर्णांक vx_set_ibl(काष्ठा vx_core *chip, काष्ठा vx_ibl_info *info)
अणु
	पूर्णांक err;
	काष्ठा vx_rmh rmh;

	vx_init_rmh(&rmh, CMD_IBL);
	rmh.Cmd[0] |= info->size & 0x03ffff;
	err = vx_send_msg(chip, &rmh);
	अगर (err < 0)
		वापस err;
	info->size = rmh.Stat[0];
	info->max_size = rmh.Stat[1];
	info->min_size = rmh.Stat[2];
	info->granularity = rmh.Stat[3];
	snd_prपूर्णांकdd(KERN_DEBUG "vx_set_ibl: size = %d, max = %d, min = %d, gran = %d\n",
		   info->size, info->max_size, info->min_size, info->granularity);
	वापस 0;
पूर्ण


/*
 * vx_get_pipe_state - get the state of a pipe
 * @pipe: the pipe to be checked
 * @state: the poपूर्णांकer क्रम the वापसed state
 *
 * checks the state of a given pipe, and stores the state (1 = running,
 * 0 = छोड़ोd) on the given poपूर्णांकer.
 *
 * called from trigger callback only
 */
अटल पूर्णांक vx_get_pipe_state(काष्ठा vx_core *chip, काष्ठा vx_pipe *pipe, पूर्णांक *state)
अणु
	पूर्णांक err;
	काष्ठा vx_rmh rmh;

	vx_init_rmh(&rmh, CMD_PIPE_STATE);
	vx_set_pipe_cmd_params(&rmh, pipe->is_capture, pipe->number, 0);
	err = vx_send_msg(chip, &rmh);
	अगर (! err)
		*state = (rmh.Stat[0] & (1 << pipe->number)) ? 1 : 0;
	वापस err;
पूर्ण


/*
 * vx_query_hbuffer_size - query available h-buffer size in bytes
 * @pipe: the pipe to be checked
 *
 * वापस the available size on h-buffer in bytes,
 * or a negative error code.
 *
 * NOTE: calling this function always चयनes to the stream mode.
 *       you'll need to disconnect the host to get back to the
 *       normal mode.
 */
अटल पूर्णांक vx_query_hbuffer_size(काष्ठा vx_core *chip, काष्ठा vx_pipe *pipe)
अणु
	पूर्णांक result;
	काष्ठा vx_rmh rmh;

	vx_init_rmh(&rmh, CMD_SIZE_HBUFFER);
	vx_set_pipe_cmd_params(&rmh, pipe->is_capture, pipe->number, 0);
	अगर (pipe->is_capture)
		rmh.Cmd[0] |= 0x00000001;
	result = vx_send_msg(chip, &rmh);
	अगर (! result)
		result = rmh.Stat[0] & 0xffff;
	वापस result;
पूर्ण


/*
 * vx_pipe_can_start - query whether a pipe is पढ़ोy क्रम start
 * @pipe: the pipe to be checked
 *
 * वापस 1 अगर पढ़ोy, 0 अगर not पढ़ोy, and negative value on error.
 *
 * called from trigger callback only
 */
अटल पूर्णांक vx_pipe_can_start(काष्ठा vx_core *chip, काष्ठा vx_pipe *pipe)
अणु
	पूर्णांक err;
	काष्ठा vx_rmh rmh;
        
	vx_init_rmh(&rmh, CMD_CAN_START_PIPE);
	vx_set_pipe_cmd_params(&rmh, pipe->is_capture, pipe->number, 0);
	rmh.Cmd[0] |= 1;

	err = vx_send_msg(chip, &rmh);
	अगर (! err) अणु
		अगर (rmh.Stat[0])
			err = 1;
	पूर्ण
	वापस err;
पूर्ण

/*
 * vx_conf_pipe - tell the pipe to stand by and रुको क्रम IRQA.
 * @pipe: the pipe to be configured
 */
अटल पूर्णांक vx_conf_pipe(काष्ठा vx_core *chip, काष्ठा vx_pipe *pipe)
अणु
	काष्ठा vx_rmh rmh;

	vx_init_rmh(&rmh, CMD_CONF_PIPE);
	अगर (pipe->is_capture)
		rmh.Cmd[0] |= COMMAND_RECORD_MASK;
	rmh.Cmd[1] = 1 << pipe->number;
	वापस vx_send_msg(chip, &rmh);
पूर्ण

/*
 * vx_send_irqa - trigger IRQA
 */
अटल पूर्णांक vx_send_irqa(काष्ठा vx_core *chip)
अणु
	काष्ठा vx_rmh rmh;

	vx_init_rmh(&rmh, CMD_SEND_IRQA);
	वापस vx_send_msg(chip, &rmh);
पूर्ण


#घोषणा MAX_WAIT_FOR_DSP        250
/*
 * vx boards करो not support पूर्णांकer-card sync, besides
 * only 126 samples require to be prepared beक्रमe a pipe can start
 */
#घोषणा CAN_START_DELAY         2	/* रुको 2ms only beक्रमe asking अगर the pipe is पढ़ोy*/
#घोषणा WAIT_STATE_DELAY        2	/* रुको 2ms after irqA was requested and check अगर the pipe state toggled*/

/*
 * vx_toggle_pipe - start / छोड़ो a pipe
 * @pipe: the pipe to be triggered
 * @state: start = 1, छोड़ो = 0
 *
 * called from trigger callback only
 *
 */
अटल पूर्णांक vx_toggle_pipe(काष्ठा vx_core *chip, काष्ठा vx_pipe *pipe, पूर्णांक state)
अणु
	पूर्णांक err, i, cur_state;

	/* Check the pipe is not alपढ़ोy in the requested state */
	अगर (vx_get_pipe_state(chip, pipe, &cur_state) < 0)
		वापस -EBADFD;
	अगर (state == cur_state)
		वापस 0;

	/* If a start is requested, ask the DSP to get prepared
	 * and रुको क्रम a positive acknowledge (when there are
	 * enough sound buffer क्रम this pipe)
	 */
	अगर (state) अणु
		क्रम (i = 0 ; i < MAX_WAIT_FOR_DSP; i++) अणु
			err = vx_pipe_can_start(chip, pipe);
			अगर (err > 0)
				अवरोध;
			/* Wait क्रम a few, beक्रमe asking again
			 * to aव्योम flooding the DSP with our requests
			 */
			mdelay(1);
		पूर्ण
	पूर्ण
    
	अगर ((err = vx_conf_pipe(chip, pipe)) < 0)
		वापस err;

	अगर ((err = vx_send_irqa(chip)) < 0)
		वापस err;
    
	/* If it completes successfully, रुको क्रम the pipes
	 * reaching the expected state beक्रमe वापसing
	 * Check one pipe only (since they are synchronous)
	 */
	क्रम (i = 0; i < MAX_WAIT_FOR_DSP; i++) अणु
		err = vx_get_pipe_state(chip, pipe, &cur_state);
		अगर (err < 0 || cur_state == state)
			अवरोध;
		err = -EIO;
		mdelay(1);
	पूर्ण
	वापस err < 0 ? -EIO : 0;
पूर्ण

    
/*
 * vx_stop_pipe - stop a pipe
 * @pipe: the pipe to be stopped
 *
 * called from trigger callback only
 */
अटल पूर्णांक vx_stop_pipe(काष्ठा vx_core *chip, काष्ठा vx_pipe *pipe)
अणु
	काष्ठा vx_rmh rmh;
	vx_init_rmh(&rmh, CMD_STOP_PIPE);
	vx_set_pipe_cmd_params(&rmh, pipe->is_capture, pipe->number, 0);
	वापस vx_send_msg(chip, &rmh);
पूर्ण


/*
 * vx_alloc_pipe - allocate a pipe and initialize the pipe instance
 * @capture: 0 = playback, 1 = capture operation
 * @audioid: the audio id to be asचिन्हित
 * @num_audio: number of audio channels
 * @pipep: the वापसed pipe instance
 *
 * वापस 0 on success, or a negative error code.
 */
अटल पूर्णांक vx_alloc_pipe(काष्ठा vx_core *chip, पूर्णांक capture,
			 पूर्णांक audioid, पूर्णांक num_audio,
			 काष्ठा vx_pipe **pipep)
अणु
	पूर्णांक err;
	काष्ठा vx_pipe *pipe;
	काष्ठा vx_rmh rmh;
	पूर्णांक data_mode;

	*pipep = शून्य;
	vx_init_rmh(&rmh, CMD_RES_PIPE);
	vx_set_pipe_cmd_params(&rmh, capture, audioid, num_audio);
#अगर 0	// NYI
	अगर (underrun_skip_sound)
		rmh.Cmd[0] |= BIT_SKIP_SOUND;
#पूर्ण_अगर	// NYI
	data_mode = (chip->uer_bits & IEC958_AES0_NONAUDIO) != 0;
	अगर (! capture && data_mode)
		rmh.Cmd[0] |= BIT_DATA_MODE;
	err = vx_send_msg(chip, &rmh);
	अगर (err < 0)
		वापस err;

	/* initialize the pipe record */
	pipe = kzalloc(माप(*pipe), GFP_KERNEL);
	अगर (! pipe) अणु
		/* release the pipe */
		vx_init_rmh(&rmh, CMD_FREE_PIPE);
		vx_set_pipe_cmd_params(&rmh, capture, audioid, 0);
		vx_send_msg(chip, &rmh);
		वापस -ENOMEM;
	पूर्ण

	/* the pipe index should be identical with the audio index */
	pipe->number = audioid;
	pipe->is_capture = capture;
	pipe->channels = num_audio;
	pipe->dअगरfered_type = 0;
	pipe->pcx_समय = 0;
	pipe->data_mode = data_mode;
	*pipep = pipe;

	वापस 0;
पूर्ण


/*
 * vx_मुक्त_pipe - release a pipe
 * @pipe: pipe to be released
 */
अटल पूर्णांक vx_मुक्त_pipe(काष्ठा vx_core *chip, काष्ठा vx_pipe *pipe)
अणु
	काष्ठा vx_rmh rmh;

	vx_init_rmh(&rmh, CMD_FREE_PIPE);
	vx_set_pipe_cmd_params(&rmh, pipe->is_capture, pipe->number, 0);
	vx_send_msg(chip, &rmh);

	kमुक्त(pipe);
	वापस 0;
पूर्ण


/*
 * vx_start_stream - start the stream
 *
 * called from trigger callback only
 */
अटल पूर्णांक vx_start_stream(काष्ठा vx_core *chip, काष्ठा vx_pipe *pipe)
अणु
	काष्ठा vx_rmh rmh;

	vx_init_rmh(&rmh, CMD_START_ONE_STREAM);
	vx_set_stream_cmd_params(&rmh, pipe->is_capture, pipe->number);
	vx_set_dअगरfered_समय(chip, &rmh, pipe);
	वापस vx_send_msg(chip, &rmh);
पूर्ण


/*
 * vx_stop_stream - stop the stream
 *
 * called from trigger callback only
 */
अटल पूर्णांक vx_stop_stream(काष्ठा vx_core *chip, काष्ठा vx_pipe *pipe)
अणु
	काष्ठा vx_rmh rmh;

	vx_init_rmh(&rmh, CMD_STOP_STREAM);
	vx_set_stream_cmd_params(&rmh, pipe->is_capture, pipe->number);
	वापस vx_send_msg(chip, &rmh);
पूर्ण


/*
 * playback hw inक्रमmation
 */

अटल स्थिर काष्ठा snd_pcm_hardware vx_pcm_playback_hw = अणु
	.info =			(SNDRV_PCM_INFO_MMAP | SNDRV_PCM_INFO_INTERLEAVED |
				 SNDRV_PCM_INFO_PAUSE | SNDRV_PCM_INFO_MMAP_VALID /*|*/
				 /*SNDRV_PCM_INFO_RESUME*/),
	.क्रमmats =		(/*SNDRV_PCM_FMTBIT_U8 |*/
				 SNDRV_PCM_FMTBIT_S16_LE | SNDRV_PCM_FMTBIT_S24_3LE),
	.rates =		SNDRV_PCM_RATE_CONTINUOUS | SNDRV_PCM_RATE_8000_48000,
	.rate_min =		5000,
	.rate_max =		48000,
	.channels_min =		1,
	.channels_max =		2,
	.buffer_bytes_max =	(128*1024),
	.period_bytes_min =	126,
	.period_bytes_max =	(128*1024),
	.periods_min =		2,
	.periods_max =		VX_MAX_PERIODS,
	.fअगरo_size =		126,
पूर्ण;


/*
 * vx_pcm_playback_खोलो - खोलो callback क्रम playback
 */
अटल पूर्णांक vx_pcm_playback_खोलो(काष्ठा snd_pcm_substream *subs)
अणु
	काष्ठा snd_pcm_runसमय *runसमय = subs->runसमय;
	काष्ठा vx_core *chip = snd_pcm_substream_chip(subs);
	काष्ठा vx_pipe *pipe = शून्य;
	अचिन्हित पूर्णांक audio;
	पूर्णांक err;

	अगर (chip->chip_status & VX_STAT_IS_STALE)
		वापस -EBUSY;

	audio = subs->pcm->device * 2;
	अगर (snd_BUG_ON(audio >= chip->audio_outs))
		वापस -EINVAL;
	
	/* playback pipe may have been alपढ़ोy allocated क्रम monitoring */
	pipe = chip->playback_pipes[audio];
	अगर (! pipe) अणु
		/* not allocated yet */
		err = vx_alloc_pipe(chip, 0, audio, 2, &pipe); /* stereo playback */
		अगर (err < 0)
			वापस err;
	पूर्ण
	/* खोलो क्रम playback */
	pipe->references++;

	pipe->substream = subs;
	chip->playback_pipes[audio] = pipe;

	runसमय->hw = vx_pcm_playback_hw;
	runसमय->hw.period_bytes_min = chip->ibl.size;
	runसमय->निजी_data = pipe;

	/* align to 4 bytes (otherwise will be problematic when 24bit is used) */ 
	snd_pcm_hw_स्थिरraपूर्णांक_step(runसमय, 0, SNDRV_PCM_HW_PARAM_BUFFER_BYTES, 4);
	snd_pcm_hw_स्थिरraपूर्णांक_step(runसमय, 0, SNDRV_PCM_HW_PARAM_PERIOD_BYTES, 4);

	वापस 0;
पूर्ण

/*
 * vx_pcm_playback_बंद - बंद callback क्रम playback
 */
अटल पूर्णांक vx_pcm_playback_बंद(काष्ठा snd_pcm_substream *subs)
अणु
	काष्ठा vx_core *chip = snd_pcm_substream_chip(subs);
	काष्ठा vx_pipe *pipe;

	अगर (! subs->runसमय->निजी_data)
		वापस -EINVAL;

	pipe = subs->runसमय->निजी_data;

	अगर (--pipe->references == 0) अणु
		chip->playback_pipes[pipe->number] = शून्य;
		vx_मुक्त_pipe(chip, pipe);
	पूर्ण

	वापस 0;

पूर्ण


/*
 * vx_notअगरy_end_of_buffer - send "end-of-buffer" notअगरier at the given pipe
 * @pipe: the pipe to notअगरy
 *
 * NB: call with a certain lock.
 */
अटल पूर्णांक vx_notअगरy_end_of_buffer(काष्ठा vx_core *chip, काष्ठा vx_pipe *pipe)
अणु
	पूर्णांक err;
	काष्ठा vx_rmh rmh;  /* use a temporary rmh here */

	/* Toggle Dsp Host Interface पूर्णांकo Message mode */
	vx_send_rih_nolock(chip, IRQ_PAUSE_START_CONNECT);
	vx_init_rmh(&rmh, CMD_NOTIFY_END_OF_BUFFER);
	vx_set_stream_cmd_params(&rmh, 0, pipe->number);
	err = vx_send_msg_nolock(chip, &rmh);
	अगर (err < 0)
		वापस err;
	/* Toggle Dsp Host Interface back to sound transfer mode */
	vx_send_rih_nolock(chip, IRQ_PAUSE_START_CONNECT);
	वापस 0;
पूर्ण

/*
 * vx_pcm_playback_transfer_chunk - transfer a single chunk
 * @subs: substream
 * @pipe: the pipe to transfer
 * @size: chunk size in bytes
 *
 * transfer a single buffer chunk.  EOB notअगरicaton is added after that.
 * called from the पूर्णांकerrupt handler, too.
 *
 * वापस 0 अगर ok.
 */
अटल पूर्णांक vx_pcm_playback_transfer_chunk(काष्ठा vx_core *chip,
					  काष्ठा snd_pcm_runसमय *runसमय,
					  काष्ठा vx_pipe *pipe, पूर्णांक size)
अणु
	पूर्णांक space, err = 0;

	space = vx_query_hbuffer_size(chip, pipe);
	अगर (space < 0) अणु
		/* disconnect the host, SIZE_HBUF command always चयनes to the stream mode */
		vx_send_rih(chip, IRQ_CONNECT_STREAM_NEXT);
		snd_prपूर्णांकd("error hbuffer\n");
		वापस space;
	पूर्ण
	अगर (space < size) अणु
		vx_send_rih(chip, IRQ_CONNECT_STREAM_NEXT);
		snd_prपूर्णांकd("no enough hbuffer space %d\n", space);
		वापस -EIO; /* XRUN */
	पूर्ण
		
	/* we करोn't need irqsave here, because this function
	 * is called from either trigger callback or irq handler
	 */
	mutex_lock(&chip->lock);
	vx_pseuकरो_dma_ग_लिखो(chip, runसमय, pipe, size);
	err = vx_notअगरy_end_of_buffer(chip, pipe);
	/* disconnect the host, SIZE_HBUF command always चयनes to the stream mode */
	vx_send_rih_nolock(chip, IRQ_CONNECT_STREAM_NEXT);
	mutex_unlock(&chip->lock);
	वापस err;
पूर्ण

/*
 * update the position of the given pipe.
 * pipe->position is updated and wrapped within the buffer size.
 * pipe->transferred is updated, too, but the size is not wrapped,
 * so that the caller can check the total transferred size later
 * (to call snd_pcm_period_elapsed).
 */
अटल पूर्णांक vx_update_pipe_position(काष्ठा vx_core *chip,
				   काष्ठा snd_pcm_runसमय *runसमय,
				   काष्ठा vx_pipe *pipe)
अणु
	काष्ठा vx_rmh rmh;
	पूर्णांक err, update;
	u64 count;

	vx_init_rmh(&rmh, CMD_STREAM_SAMPLE_COUNT);
	vx_set_pipe_cmd_params(&rmh, pipe->is_capture, pipe->number, 0);
	err = vx_send_msg(chip, &rmh);
	अगर (err < 0)
		वापस err;

	count = ((u64)(rmh.Stat[0] & 0xfffff) << 24) | (u64)rmh.Stat[1];
	update = (पूर्णांक)(count - pipe->cur_count);
	pipe->cur_count = count;
	pipe->position += update;
	अगर (pipe->position >= (पूर्णांक)runसमय->buffer_size)
		pipe->position %= runसमय->buffer_size;
	pipe->transferred += update;
	वापस 0;
पूर्ण

/*
 * transfer the pending playback buffer data to DSP
 * called from पूर्णांकerrupt handler
 */
अटल व्योम vx_pcm_playback_transfer(काष्ठा vx_core *chip,
				     काष्ठा snd_pcm_substream *subs,
				     काष्ठा vx_pipe *pipe, पूर्णांक nchunks)
अणु
	पूर्णांक i, err;
	काष्ठा snd_pcm_runसमय *runसमय = subs->runसमय;

	अगर (! pipe->prepared || (chip->chip_status & VX_STAT_IS_STALE))
		वापस;
	क्रम (i = 0; i < nchunks; i++) अणु
		अगर ((err = vx_pcm_playback_transfer_chunk(chip, runसमय, pipe,
							  chip->ibl.size)) < 0)
			वापस;
	पूर्ण
पूर्ण

/*
 * update the playback position and call snd_pcm_period_elapsed() अगर necessary
 * called from पूर्णांकerrupt handler
 */
अटल व्योम vx_pcm_playback_update(काष्ठा vx_core *chip,
				   काष्ठा snd_pcm_substream *subs,
				   काष्ठा vx_pipe *pipe)
अणु
	पूर्णांक err;
	काष्ठा snd_pcm_runसमय *runसमय = subs->runसमय;

	अगर (pipe->running && ! (chip->chip_status & VX_STAT_IS_STALE)) अणु
		अगर ((err = vx_update_pipe_position(chip, runसमय, pipe)) < 0)
			वापस;
		अगर (pipe->transferred >= (पूर्णांक)runसमय->period_size) अणु
			pipe->transferred %= runसमय->period_size;
			snd_pcm_period_elapsed(subs);
		पूर्ण
	पूर्ण
पूर्ण

/*
 * vx_pcm_playback_trigger - trigger callback क्रम playback
 */
अटल पूर्णांक vx_pcm_trigger(काष्ठा snd_pcm_substream *subs, पूर्णांक cmd)
अणु
	काष्ठा vx_core *chip = snd_pcm_substream_chip(subs);
	काष्ठा vx_pipe *pipe = subs->runसमय->निजी_data;
	पूर्णांक err;

	अगर (chip->chip_status & VX_STAT_IS_STALE)
		वापस -EBUSY;
		
	चयन (cmd) अणु
	हाल SNDRV_PCM_TRIGGER_START:
	हाल SNDRV_PCM_TRIGGER_RESUME:
		अगर (! pipe->is_capture)
			vx_pcm_playback_transfer(chip, subs, pipe, 2);
		err = vx_start_stream(chip, pipe);
		अगर (err < 0) अणु
			pr_debug("vx: cannot start stream\n");
			वापस err;
		पूर्ण
		err = vx_toggle_pipe(chip, pipe, 1);
		अगर (err < 0) अणु
			pr_debug("vx: cannot start pipe\n");
			vx_stop_stream(chip, pipe);
			वापस err;
		पूर्ण
		chip->pcm_running++;
		pipe->running = 1;
		अवरोध;
	हाल SNDRV_PCM_TRIGGER_STOP:
	हाल SNDRV_PCM_TRIGGER_SUSPEND:
		vx_toggle_pipe(chip, pipe, 0);
		vx_stop_pipe(chip, pipe);
		vx_stop_stream(chip, pipe);
		chip->pcm_running--;
		pipe->running = 0;
		अवरोध;
	हाल SNDRV_PCM_TRIGGER_PAUSE_PUSH:
		अगर ((err = vx_toggle_pipe(chip, pipe, 0)) < 0)
			वापस err;
		अवरोध;
	हाल SNDRV_PCM_TRIGGER_PAUSE_RELEASE:
		अगर ((err = vx_toggle_pipe(chip, pipe, 1)) < 0)
			वापस err;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण
	वापस 0;
पूर्ण

/*
 * vx_pcm_playback_poपूर्णांकer - poपूर्णांकer callback क्रम playback
 */
अटल snd_pcm_uframes_t vx_pcm_playback_poपूर्णांकer(काष्ठा snd_pcm_substream *subs)
अणु
	काष्ठा snd_pcm_runसमय *runसमय = subs->runसमय;
	काष्ठा vx_pipe *pipe = runसमय->निजी_data;
	वापस pipe->position;
पूर्ण

/*
 * vx_pcm_prepare - prepare callback क्रम playback and capture
 */
अटल पूर्णांक vx_pcm_prepare(काष्ठा snd_pcm_substream *subs)
अणु
	काष्ठा vx_core *chip = snd_pcm_substream_chip(subs);
	काष्ठा snd_pcm_runसमय *runसमय = subs->runसमय;
	काष्ठा vx_pipe *pipe = runसमय->निजी_data;
	पूर्णांक err, data_mode;
	// पूर्णांक max_size, nchunks;

	अगर (chip->chip_status & VX_STAT_IS_STALE)
		वापस -EBUSY;

	data_mode = (chip->uer_bits & IEC958_AES0_NONAUDIO) != 0;
	अगर (data_mode != pipe->data_mode && ! pipe->is_capture) अणु
		/* IEC958 status (raw-mode) was changed */
		/* we reखोलो the pipe */
		काष्ठा vx_rmh rmh;
		snd_prपूर्णांकdd(KERN_DEBUG "reopen the pipe with data_mode = %d\n", data_mode);
		vx_init_rmh(&rmh, CMD_FREE_PIPE);
		vx_set_pipe_cmd_params(&rmh, 0, pipe->number, 0);
		अगर ((err = vx_send_msg(chip, &rmh)) < 0)
			वापस err;
		vx_init_rmh(&rmh, CMD_RES_PIPE);
		vx_set_pipe_cmd_params(&rmh, 0, pipe->number, pipe->channels);
		अगर (data_mode)
			rmh.Cmd[0] |= BIT_DATA_MODE;
		अगर ((err = vx_send_msg(chip, &rmh)) < 0)
			वापस err;
		pipe->data_mode = data_mode;
	पूर्ण

	अगर (chip->pcm_running && chip->freq != runसमय->rate) अणु
		snd_prपूर्णांकk(KERN_ERR "vx: cannot set different clock %d "
			   "from the current %d\n", runसमय->rate, chip->freq);
		वापस -EINVAL;
	पूर्ण
	vx_set_घड़ी(chip, runसमय->rate);

	अगर ((err = vx_set_क्रमmat(chip, pipe, runसमय)) < 0)
		वापस err;

	अगर (vx_is_pcmcia(chip)) अणु
		pipe->align = 2; /* 16bit word */
	पूर्ण अन्यथा अणु
		pipe->align = 4; /* 32bit word */
	पूर्ण

	pipe->buffer_bytes = frames_to_bytes(runसमय, runसमय->buffer_size);
	pipe->period_bytes = frames_to_bytes(runसमय, runसमय->period_size);
	pipe->hw_ptr = 0;

	/* set the बारtamp */
	vx_update_pipe_position(chip, runसमय, pipe);
	/* clear again */
	pipe->transferred = 0;
	pipe->position = 0;

	pipe->prepared = 1;

	वापस 0;
पूर्ण


/*
 * चालकs क्रम PCM playback
 */
अटल स्थिर काष्ठा snd_pcm_ops vx_pcm_playback_ops = अणु
	.खोलो =		vx_pcm_playback_खोलो,
	.बंद =	vx_pcm_playback_बंद,
	.prepare =	vx_pcm_prepare,
	.trigger =	vx_pcm_trigger,
	.poपूर्णांकer =	vx_pcm_playback_poपूर्णांकer,
पूर्ण;


/*
 * playback hw inक्रमmation
 */

अटल स्थिर काष्ठा snd_pcm_hardware vx_pcm_capture_hw = अणु
	.info =			(SNDRV_PCM_INFO_MMAP | SNDRV_PCM_INFO_INTERLEAVED |
				 SNDRV_PCM_INFO_PAUSE | SNDRV_PCM_INFO_MMAP_VALID /*|*/
				 /*SNDRV_PCM_INFO_RESUME*/),
	.क्रमmats =		(/*SNDRV_PCM_FMTBIT_U8 |*/
				 SNDRV_PCM_FMTBIT_S16_LE | SNDRV_PCM_FMTBIT_S24_3LE),
	.rates =		SNDRV_PCM_RATE_CONTINUOUS | SNDRV_PCM_RATE_8000_48000,
	.rate_min =		5000,
	.rate_max =		48000,
	.channels_min =		1,
	.channels_max =		2,
	.buffer_bytes_max =	(128*1024),
	.period_bytes_min =	126,
	.period_bytes_max =	(128*1024),
	.periods_min =		2,
	.periods_max =		VX_MAX_PERIODS,
	.fअगरo_size =		126,
पूर्ण;


/*
 * vx_pcm_capture_खोलो - खोलो callback क्रम capture
 */
अटल पूर्णांक vx_pcm_capture_खोलो(काष्ठा snd_pcm_substream *subs)
अणु
	काष्ठा snd_pcm_runसमय *runसमय = subs->runसमय;
	काष्ठा vx_core *chip = snd_pcm_substream_chip(subs);
	काष्ठा vx_pipe *pipe;
	काष्ठा vx_pipe *pipe_out_monitoring = शून्य;
	अचिन्हित पूर्णांक audio;
	पूर्णांक err;

	अगर (chip->chip_status & VX_STAT_IS_STALE)
		वापस -EBUSY;

	audio = subs->pcm->device * 2;
	अगर (snd_BUG_ON(audio >= chip->audio_ins))
		वापस -EINVAL;
	err = vx_alloc_pipe(chip, 1, audio, 2, &pipe);
	अगर (err < 0)
		वापस err;
	pipe->substream = subs;
	chip->capture_pipes[audio] = pipe;

	/* check अगर monitoring is needed */
	अगर (chip->audio_monitor_active[audio]) अणु
		pipe_out_monitoring = chip->playback_pipes[audio];
		अगर (! pipe_out_monitoring) अणु
			/* allocate a pipe */
			err = vx_alloc_pipe(chip, 0, audio, 2, &pipe_out_monitoring);
			अगर (err < 0)
				वापस err;
			chip->playback_pipes[audio] = pipe_out_monitoring;
		पूर्ण
		pipe_out_monitoring->references++;
		/* 
		   अगर an output pipe is available, it's audios still may need to be 
		   unmuted. hence we'll have to call a mixer entry poपूर्णांक.
		*/
		vx_set_monitor_level(chip, audio, chip->audio_monitor[audio],
				     chip->audio_monitor_active[audio]);
		/* assuming stereo */
		vx_set_monitor_level(chip, audio+1, chip->audio_monitor[audio+1],
				     chip->audio_monitor_active[audio+1]); 
	पूर्ण

	pipe->monitoring_pipe = pipe_out_monitoring; /* शेष value शून्य */

	runसमय->hw = vx_pcm_capture_hw;
	runसमय->hw.period_bytes_min = chip->ibl.size;
	runसमय->निजी_data = pipe;

	/* align to 4 bytes (otherwise will be problematic when 24bit is used) */ 
	snd_pcm_hw_स्थिरraपूर्णांक_step(runसमय, 0, SNDRV_PCM_HW_PARAM_BUFFER_BYTES, 4);
	snd_pcm_hw_स्थिरraपूर्णांक_step(runसमय, 0, SNDRV_PCM_HW_PARAM_PERIOD_BYTES, 4);

	वापस 0;
पूर्ण

/*
 * vx_pcm_capture_बंद - बंद callback क्रम capture
 */
अटल पूर्णांक vx_pcm_capture_बंद(काष्ठा snd_pcm_substream *subs)
अणु
	काष्ठा vx_core *chip = snd_pcm_substream_chip(subs);
	काष्ठा vx_pipe *pipe;
	काष्ठा vx_pipe *pipe_out_monitoring;
	
	अगर (! subs->runसमय->निजी_data)
		वापस -EINVAL;
	pipe = subs->runसमय->निजी_data;
	chip->capture_pipes[pipe->number] = शून्य;

	pipe_out_monitoring = pipe->monitoring_pipe;

	/*
	  अगर an output pipe is attached to this input, 
	  check अगर it needs to be released.
	*/
	अगर (pipe_out_monitoring) अणु
		अगर (--pipe_out_monitoring->references == 0) अणु
			vx_मुक्त_pipe(chip, pipe_out_monitoring);
			chip->playback_pipes[pipe->number] = शून्य;
			pipe->monitoring_pipe = शून्य;
		पूर्ण
	पूर्ण
	
	vx_मुक्त_pipe(chip, pipe);
	वापस 0;
पूर्ण



#घोषणा DMA_READ_ALIGN	6	/* hardware alignment क्रम पढ़ो */

/*
 * vx_pcm_capture_update - update the capture buffer
 */
अटल व्योम vx_pcm_capture_update(काष्ठा vx_core *chip, काष्ठा snd_pcm_substream *subs,
				  काष्ठा vx_pipe *pipe)
अणु
	पूर्णांक size, space, count;
	काष्ठा snd_pcm_runसमय *runसमय = subs->runसमय;

	अगर (!pipe->running || (chip->chip_status & VX_STAT_IS_STALE))
		वापस;

	size = runसमय->buffer_size - snd_pcm_capture_avail(runसमय);
	अगर (! size)
		वापस;
	size = frames_to_bytes(runसमय, size);
	space = vx_query_hbuffer_size(chip, pipe);
	अगर (space < 0)
		जाओ _error;
	अगर (size > space)
		size = space;
	size = (size / 3) * 3; /* align to 3 bytes */
	अगर (size < DMA_READ_ALIGN)
		जाओ _error;

	/* keep the last 6 bytes, they will be पढ़ो after disconnection */
	count = size - DMA_READ_ALIGN;
	/* पढ़ो bytes until the current poपूर्णांकer reaches to the aligned position
	 * क्रम word-transfer
	 */
	जबतक (count > 0) अणु
		अगर ((pipe->hw_ptr % pipe->align) == 0)
			अवरोध;
		अगर (vx_रुको_क्रम_rx_full(chip) < 0)
			जाओ _error;
		vx_pcm_पढ़ो_per_bytes(chip, runसमय, pipe);
		count -= 3;
	पूर्ण
	अगर (count > 0) अणु
		/* ok, let's accelerate! */
		पूर्णांक align = pipe->align * 3;
		space = (count / align) * align;
		अगर (space > 0) अणु
			vx_pseuकरो_dma_पढ़ो(chip, runसमय, pipe, space);
			count -= space;
		पूर्ण
	पूर्ण
	/* पढ़ो the rest of bytes */
	जबतक (count > 0) अणु
		अगर (vx_रुको_क्रम_rx_full(chip) < 0)
			जाओ _error;
		vx_pcm_पढ़ो_per_bytes(chip, runसमय, pipe);
		count -= 3;
	पूर्ण
	/* disconnect the host, SIZE_HBUF command always चयनes to the stream mode */
	vx_send_rih(chip, IRQ_CONNECT_STREAM_NEXT);
	/* पढ़ो the last pending 6 bytes */
	count = DMA_READ_ALIGN;
	जबतक (count > 0) अणु
		vx_pcm_पढ़ो_per_bytes(chip, runसमय, pipe);
		count -= 3;
	पूर्ण
	/* update the position */
	pipe->transferred += size;
	अगर (pipe->transferred >= pipe->period_bytes) अणु
		pipe->transferred %= pipe->period_bytes;
		snd_pcm_period_elapsed(subs);
	पूर्ण
	वापस;

 _error:
	/* disconnect the host, SIZE_HBUF command always चयनes to the stream mode */
	vx_send_rih(chip, IRQ_CONNECT_STREAM_NEXT);
	वापस;
पूर्ण

/*
 * vx_pcm_capture_poपूर्णांकer - poपूर्णांकer callback क्रम capture
 */
अटल snd_pcm_uframes_t vx_pcm_capture_poपूर्णांकer(काष्ठा snd_pcm_substream *subs)
अणु
	काष्ठा snd_pcm_runसमय *runसमय = subs->runसमय;
	काष्ठा vx_pipe *pipe = runसमय->निजी_data;
	वापस bytes_to_frames(runसमय, pipe->hw_ptr);
पूर्ण

/*
 * चालकs क्रम PCM capture
 */
अटल स्थिर काष्ठा snd_pcm_ops vx_pcm_capture_ops = अणु
	.खोलो =		vx_pcm_capture_खोलो,
	.बंद =	vx_pcm_capture_बंद,
	.prepare =	vx_pcm_prepare,
	.trigger =	vx_pcm_trigger,
	.poपूर्णांकer =	vx_pcm_capture_poपूर्णांकer,
पूर्ण;


/*
 * पूर्णांकerrupt handler क्रम pcm streams
 */
व्योम vx_pcm_update_पूर्णांकr(काष्ठा vx_core *chip, अचिन्हित पूर्णांक events)
अणु
	अचिन्हित पूर्णांक i;
	काष्ठा vx_pipe *pipe;

#घोषणा EVENT_MASK	(END_OF_BUFFER_EVENTS_PENDING|ASYNC_EVENTS_PENDING)

	अगर (events & EVENT_MASK) अणु
		vx_init_rmh(&chip->irq_rmh, CMD_ASYNC);
		अगर (events & ASYNC_EVENTS_PENDING)
			chip->irq_rmh.Cmd[0] |= 0x00000001;	/* SEL_ASYNC_EVENTS */
		अगर (events & END_OF_BUFFER_EVENTS_PENDING)
			chip->irq_rmh.Cmd[0] |= 0x00000002;	/* SEL_END_OF_BUF_EVENTS */

		अगर (vx_send_msg(chip, &chip->irq_rmh) < 0) अणु
			snd_prपूर्णांकdd(KERN_ERR "msg send error!!\n");
			वापस;
		पूर्ण

		i = 1;
		जबतक (i < chip->irq_rmh.LgStat) अणु
			पूर्णांक p, buf, capture, eob;
			p = chip->irq_rmh.Stat[i] & MASK_FIRST_FIELD;
			capture = (chip->irq_rmh.Stat[i] & 0x400000) ? 1 : 0;
			eob = (chip->irq_rmh.Stat[i] & 0x800000) ? 1 : 0;
			i++;
			अगर (events & ASYNC_EVENTS_PENDING)
				i++;
			buf = 1; /* क्रमce to transfer */
			अगर (events & END_OF_BUFFER_EVENTS_PENDING) अणु
				अगर (eob)
					buf = chip->irq_rmh.Stat[i];
				i++;
			पूर्ण
			अगर (capture)
				जारी;
			अगर (snd_BUG_ON(p < 0 || p >= chip->audio_outs))
				जारी;
			pipe = chip->playback_pipes[p];
			अगर (pipe && pipe->substream) अणु
				vx_pcm_playback_update(chip, pipe->substream, pipe);
				vx_pcm_playback_transfer(chip, pipe->substream, pipe, buf);
			पूर्ण
		पूर्ण
	पूर्ण

	/* update the capture pcm poपूर्णांकers as frequently as possible */
	क्रम (i = 0; i < chip->audio_ins; i++) अणु
		pipe = chip->capture_pipes[i];
		अगर (pipe && pipe->substream)
			vx_pcm_capture_update(chip, pipe->substream, pipe);
	पूर्ण
पूर्ण


/*
 * vx_init_audio_io - check the available audio i/o and allocate pipe arrays
 */
अटल पूर्णांक vx_init_audio_io(काष्ठा vx_core *chip)
अणु
	काष्ठा vx_rmh rmh;
	पूर्णांक preferred;

	vx_init_rmh(&rmh, CMD_SUPPORTED);
	अगर (vx_send_msg(chip, &rmh) < 0) अणु
		snd_prपूर्णांकk(KERN_ERR "vx: cannot get the supported audio data\n");
		वापस -ENXIO;
	पूर्ण

	chip->audio_outs = rmh.Stat[0] & MASK_FIRST_FIELD;
	chip->audio_ins = (rmh.Stat[0] >> (FIELD_SIZE*2)) & MASK_FIRST_FIELD;
	chip->audio_info = rmh.Stat[1];

	/* allocate pipes */
	chip->playback_pipes = kसुस्मृति(chip->audio_outs, माप(काष्ठा vx_pipe *), GFP_KERNEL);
	अगर (!chip->playback_pipes)
		वापस -ENOMEM;
	chip->capture_pipes = kसुस्मृति(chip->audio_ins, माप(काष्ठा vx_pipe *), GFP_KERNEL);
	अगर (!chip->capture_pipes) अणु
		kमुक्त(chip->playback_pipes);
		वापस -ENOMEM;
	पूर्ण

	preferred = chip->ibl.size;
	chip->ibl.size = 0;
	vx_set_ibl(chip, &chip->ibl); /* query the info */
	अगर (preferred > 0) अणु
		chip->ibl.size = roundup(preferred, chip->ibl.granularity);
		अगर (chip->ibl.size > chip->ibl.max_size)
			chip->ibl.size = chip->ibl.max_size;
	पूर्ण अन्यथा
		chip->ibl.size = chip->ibl.min_size; /* set to the minimum */
	vx_set_ibl(chip, &chip->ibl);

	वापस 0;
पूर्ण


/*
 * मुक्त callback क्रम pcm
 */
अटल व्योम snd_vx_pcm_मुक्त(काष्ठा snd_pcm *pcm)
अणु
	काष्ठा vx_core *chip = pcm->निजी_data;
	chip->pcm[pcm->device] = शून्य;
	kमुक्त(chip->playback_pipes);
	chip->playback_pipes = शून्य;
	kमुक्त(chip->capture_pipes);
	chip->capture_pipes = शून्य;
पूर्ण

/*
 * snd_vx_pcm_new - create and initialize a pcm
 */
पूर्णांक snd_vx_pcm_new(काष्ठा vx_core *chip)
अणु
	काष्ठा snd_pcm *pcm;
	अचिन्हित पूर्णांक i;
	पूर्णांक err;

	अगर ((err = vx_init_audio_io(chip)) < 0)
		वापस err;

	क्रम (i = 0; i < chip->hw->num_codecs; i++) अणु
		अचिन्हित पूर्णांक outs, ins;
		outs = chip->audio_outs > i * 2 ? 1 : 0;
		ins = chip->audio_ins > i * 2 ? 1 : 0;
		अगर (! outs && ! ins)
			अवरोध;
		err = snd_pcm_new(chip->card, "VX PCM", i,
				  outs, ins, &pcm);
		अगर (err < 0)
			वापस err;
		अगर (outs)
			snd_pcm_set_ops(pcm, SNDRV_PCM_STREAM_PLAYBACK, &vx_pcm_playback_ops);
		अगर (ins)
			snd_pcm_set_ops(pcm, SNDRV_PCM_STREAM_CAPTURE, &vx_pcm_capture_ops);
		snd_pcm_set_managed_buffer_all(pcm, SNDRV_DMA_TYPE_VMALLOC,
					       snd_dma_continuous_data(GFP_KERNEL | GFP_DMA32),
					       0, 0);

		pcm->निजी_data = chip;
		pcm->निजी_मुक्त = snd_vx_pcm_मुक्त;
		pcm->info_flags = 0;
		pcm->nonatomic = true;
		म_नकल(pcm->name, chip->card->लघुname);
		chip->pcm[i] = pcm;
	पूर्ण

	वापस 0;
पूर्ण
