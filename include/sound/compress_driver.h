<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0
 *
 *  compress_driver.h - compress offload driver definations
 *
 *  Copyright (C) 2011 Intel Corporation
 *  Authors:	Vinod Koul <vinod.koul@linux.पूर्णांकel.com>
 *		Pierre-Louis Bossart <pierre-louis.bossart@linux.पूर्णांकel.com>
 */

#अगर_अघोषित __COMPRESS_DRIVER_H
#घोषणा __COMPRESS_DRIVER_H

#समावेश <linux/types.h>
#समावेश <linux/sched.h>
#समावेश <sound/core.h>
#समावेश <sound/compress_offload.h>
#समावेश <sound/asound.h>
#समावेश <sound/pcm.h>

काष्ठा snd_compr_ops;

/**
 * काष्ठा snd_compr_runसमय: runसमय stream description
 * @state: stream state
 * @ops: poपूर्णांकer to DSP callbacks
 * @buffer: poपूर्णांकer to kernel buffer, valid only when not in mmap mode or
 *	DSP करोesn't implement copy
 * @buffer_size: size of the above buffer
 * @fragment_size: size of buffer fragment in bytes
 * @fragments: number of such fragments
 * @total_bytes_available: cumulative number of bytes made available in
 *	the ring buffer
 * @total_bytes_transferred: cumulative bytes transferred by offload DSP
 * @sleep: poll sleep
 * @निजी_data: driver निजी data poपूर्णांकer
 * @dma_area: भव buffer address
 * @dma_addr: physical buffer address (not accessible from मुख्य CPU)
 * @dma_bytes: size of DMA area
 * @dma_buffer_p: runसमय dma buffer poपूर्णांकer
 */
काष्ठा snd_compr_runसमय अणु
	snd_pcm_state_t state;
	काष्ठा snd_compr_ops *ops;
	व्योम *buffer;
	u64 buffer_size;
	u32 fragment_size;
	u32 fragments;
	u64 total_bytes_available;
	u64 total_bytes_transferred;
	रुको_queue_head_t sleep;
	व्योम *निजी_data;

	अचिन्हित अक्षर *dma_area;
	dma_addr_t dma_addr;
	माप_प्रकार dma_bytes;
	काष्ठा snd_dma_buffer *dma_buffer_p;
पूर्ण;

/**
 * काष्ठा snd_compr_stream: compressed stream
 * @name: device name
 * @ops: poपूर्णांकer to DSP callbacks
 * @runसमय: poपूर्णांकer to runसमय काष्ठाure
 * @device: device poपूर्णांकer
 * @error_work: delayed work used when closing the stream due to an error
 * @direction: stream direction, playback/recording
 * @metadata_set: metadata set flag, true when set
 * @next_track: has userspace संकेत next track transition, true when set
 * @partial_drain: undergoing partial_drain क्रम stream, true when set
 * @छोड़ो_in_draining: छोड़ोd during draining state, true when set
 * @निजी_data: poपूर्णांकer to DSP निजी data
 * @dma_buffer: allocated buffer अगर any
 */
काष्ठा snd_compr_stream अणु
	स्थिर अक्षर *name;
	काष्ठा snd_compr_ops *ops;
	काष्ठा snd_compr_runसमय *runसमय;
	काष्ठा snd_compr *device;
	काष्ठा delayed_work error_work;
	क्रमागत snd_compr_direction direction;
	bool metadata_set;
	bool next_track;
	bool partial_drain;
	bool छोड़ो_in_draining;
	व्योम *निजी_data;
	काष्ठा snd_dma_buffer dma_buffer;
पूर्ण;

/**
 * काष्ठा snd_compr_ops: compressed path DSP operations
 * @खोलो: Open the compressed stream
 * This callback is mandatory and shall keep dsp पढ़ोy to receive the stream
 * parameter
 * @मुक्त: Close the compressed stream, mandatory
 * @set_params: Sets the compressed stream parameters, mandatory
 * This can be called in during stream creation only to set codec params
 * and the stream properties
 * @get_params: retrieve the codec parameters, mandatory
 * @set_metadata: Set the metadata values क्रम a stream
 * @get_metadata: retrieves the requested metadata values from stream
 * @trigger: Trigger operations like start, छोड़ो, resume, drain, stop.
 * This callback is mandatory
 * @poपूर्णांकer: Retrieve current h/w poपूर्णांकer inक्रमmation. Mandatory
 * @copy: Copy the compressed data to/from userspace, Optional
 * Can't be implemented अगर DSP supports mmap
 * @mmap: DSP mmap method to mmap DSP memory
 * @ack: Ack क्रम DSP when data is written to audio buffer, Optional
 * Not valid अगर copy is implemented
 * @get_caps: Retrieve DSP capabilities, mandatory
 * @get_codec_caps: Retrieve capabilities क्रम a specअगरic codec, mandatory
 */
काष्ठा snd_compr_ops अणु
	पूर्णांक (*खोलो)(काष्ठा snd_compr_stream *stream);
	पूर्णांक (*मुक्त)(काष्ठा snd_compr_stream *stream);
	पूर्णांक (*set_params)(काष्ठा snd_compr_stream *stream,
			काष्ठा snd_compr_params *params);
	पूर्णांक (*get_params)(काष्ठा snd_compr_stream *stream,
			काष्ठा snd_codec *params);
	पूर्णांक (*set_metadata)(काष्ठा snd_compr_stream *stream,
			काष्ठा snd_compr_metadata *metadata);
	पूर्णांक (*get_metadata)(काष्ठा snd_compr_stream *stream,
			काष्ठा snd_compr_metadata *metadata);
	पूर्णांक (*trigger)(काष्ठा snd_compr_stream *stream, पूर्णांक cmd);
	पूर्णांक (*poपूर्णांकer)(काष्ठा snd_compr_stream *stream,
			काष्ठा snd_compr_tstamp *tstamp);
	पूर्णांक (*copy)(काष्ठा snd_compr_stream *stream, अक्षर __user *buf,
		       माप_प्रकार count);
	पूर्णांक (*mmap)(काष्ठा snd_compr_stream *stream,
			काष्ठा vm_area_काष्ठा *vma);
	पूर्णांक (*ack)(काष्ठा snd_compr_stream *stream, माप_प्रकार bytes);
	पूर्णांक (*get_caps) (काष्ठा snd_compr_stream *stream,
			काष्ठा snd_compr_caps *caps);
	पूर्णांक (*get_codec_caps) (काष्ठा snd_compr_stream *stream,
			काष्ठा snd_compr_codec_caps *codec);
पूर्ण;

/**
 * काष्ठा snd_compr: Compressed device
 * @name: DSP device name
 * @dev: associated device instance
 * @ops: poपूर्णांकer to DSP callbacks
 * @निजी_data: poपूर्णांकer to DSP pvt data
 * @card: sound card poपूर्णांकer
 * @direction: Playback or capture direction
 * @lock: device lock
 * @device: device id
 * @use_छोड़ो_in_draining: allow छोड़ो in draining, true when set
 */
काष्ठा snd_compr अणु
	स्थिर अक्षर *name;
	काष्ठा device dev;
	काष्ठा snd_compr_ops *ops;
	व्योम *निजी_data;
	काष्ठा snd_card *card;
	अचिन्हित पूर्णांक direction;
	काष्ठा mutex lock;
	पूर्णांक device;
	bool use_छोड़ो_in_draining;
#अगर_घोषित CONFIG_SND_VERBOSE_PROCFS
	/* निजी: */
	अक्षर id[64];
	काष्ठा snd_info_entry *proc_root;
	काष्ठा snd_info_entry *proc_info_entry;
#पूर्ण_अगर
पूर्ण;

/* compress device रेजिस्टर APIs */
पूर्णांक snd_compress_रेजिस्टर(काष्ठा snd_compr *device);
पूर्णांक snd_compress_deरेजिस्टर(काष्ठा snd_compr *device);
पूर्णांक snd_compress_new(काष्ठा snd_card *card, पूर्णांक device,
			पूर्णांक type, स्थिर अक्षर *id, काष्ठा snd_compr *compr);

/**
 * snd_compr_use_छोड़ो_in_draining - Allow छोड़ो and resume in draining state
 * @substream: compress substream to set
 *
 * Allow छोड़ो and resume in draining state.
 * Only HW driver supports this transition can call this API.
 */
अटल अंतरभूत व्योम snd_compr_use_छोड़ो_in_draining(काष्ठा snd_compr_stream *substream)
अणु
	substream->device->use_छोड़ो_in_draining = true;
पूर्ण

/* dsp driver callback apis
 * For playback: driver should call snd_compress_fragment_elapsed() to let the
 * framework know that a fragment has been consumed from the ring buffer
 *
 * For recording: we want to know when a frame is available or when
 * at least one frame is available so snd_compress_frame_elapsed()
 * callback should be called when a encodeded frame is available
 */
अटल अंतरभूत व्योम snd_compr_fragment_elapsed(काष्ठा snd_compr_stream *stream)
अणु
	wake_up(&stream->runसमय->sleep);
पूर्ण

अटल अंतरभूत व्योम snd_compr_drain_notअगरy(काष्ठा snd_compr_stream *stream)
अणु
	अगर (snd_BUG_ON(!stream))
		वापस;

	/* क्रम partial_drain हाल we are back to running state on success */
	अगर (stream->partial_drain) अणु
		stream->runसमय->state = SNDRV_PCM_STATE_RUNNING;
		stream->partial_drain = false; /* clear this flag as well */
	पूर्ण अन्यथा अणु
		stream->runसमय->state = SNDRV_PCM_STATE_SETUP;
	पूर्ण

	wake_up(&stream->runसमय->sleep);
पूर्ण

/**
 * snd_compr_set_runसमय_buffer - Set the Compress runसमय buffer
 * @stream: compress stream to set
 * @bufp: the buffer inक्रमmation, शून्य to clear
 *
 * Copy the buffer inक्रमmation to runसमय buffer when @bufp is non-शून्य.
 * Otherwise it clears the current buffer inक्रमmation.
 */
अटल अंतरभूत व्योम
snd_compr_set_runसमय_buffer(काष्ठा snd_compr_stream *stream,
			     काष्ठा snd_dma_buffer *bufp)
अणु
	काष्ठा snd_compr_runसमय *runसमय = stream->runसमय;

	अगर (bufp) अणु
		runसमय->dma_buffer_p = bufp;
		runसमय->dma_area = bufp->area;
		runसमय->dma_addr = bufp->addr;
		runसमय->dma_bytes = bufp->bytes;
	पूर्ण अन्यथा अणु
		runसमय->dma_buffer_p = शून्य;
		runसमय->dma_area = शून्य;
		runसमय->dma_addr = 0;
		runसमय->dma_bytes = 0;
	पूर्ण
पूर्ण

पूर्णांक snd_compr_दो_स्मृति_pages(काष्ठा snd_compr_stream *stream, माप_प्रकार size);
पूर्णांक snd_compr_मुक्त_pages(काष्ठा snd_compr_stream *stream);

पूर्णांक snd_compr_stop_error(काष्ठा snd_compr_stream *stream,
			 snd_pcm_state_t state);

#पूर्ण_अगर
