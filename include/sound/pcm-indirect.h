<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * Helper functions क्रम indirect PCM data transfer
 *
 *  Copyright (c) by Takashi Iwai <tiwai@suse.de>
 *                   Jaroslav Kysela <perex@perex.cz>
 */

#अगर_अघोषित __SOUND_PCM_INसूचीECT_H
#घोषणा __SOUND_PCM_INसूचीECT_H

#समावेश <sound/pcm.h>

काष्ठा snd_pcm_indirect अणु
	अचिन्हित पूर्णांक hw_buffer_size;	/* Byte size of hardware buffer */
	अचिन्हित पूर्णांक hw_queue_size;	/* Max queue size of hw buffer (0 = buffer size) */
	अचिन्हित पूर्णांक hw_data;	/* Offset to next dst (or src) in hw ring buffer */
	अचिन्हित पूर्णांक hw_io;	/* Ring buffer hw poपूर्णांकer */
	पूर्णांक hw_पढ़ोy;		/* Bytes पढ़ोy क्रम play (or captured) in hw ring buffer */
	अचिन्हित पूर्णांक sw_buffer_size;	/* Byte size of software buffer */
	अचिन्हित पूर्णांक sw_data;	/* Offset to next dst (or src) in sw ring buffer */
	अचिन्हित पूर्णांक sw_io;	/* Current software poपूर्णांकer in bytes */
	पूर्णांक sw_पढ़ोy;		/* Bytes पढ़ोy to be transferred to/from hw */
	snd_pcm_uframes_t appl_ptr;	/* Last seen appl_ptr */
पूर्ण;

प्रकार व्योम (*snd_pcm_indirect_copy_t)(काष्ठा snd_pcm_substream *substream,
					काष्ठा snd_pcm_indirect *rec, माप_प्रकार bytes);

/*
 * helper function क्रम playback ack callback
 */
अटल अंतरभूत पूर्णांक
snd_pcm_indirect_playback_transfer(काष्ठा snd_pcm_substream *substream,
				   काष्ठा snd_pcm_indirect *rec,
				   snd_pcm_indirect_copy_t copy)
अणु
	काष्ठा snd_pcm_runसमय *runसमय = substream->runसमय;
	snd_pcm_uframes_t appl_ptr = runसमय->control->appl_ptr;
	snd_pcm_sframes_t dअगरf = appl_ptr - rec->appl_ptr;
	पूर्णांक qsize;

	अगर (dअगरf) अणु
		अगर (dअगरf < -(snd_pcm_sframes_t) (runसमय->boundary / 2))
			dअगरf += runसमय->boundary;
		अगर (dअगरf < 0)
			वापस -EINVAL;
		rec->sw_पढ़ोy += (पूर्णांक)frames_to_bytes(runसमय, dअगरf);
		rec->appl_ptr = appl_ptr;
	पूर्ण
	qsize = rec->hw_queue_size ? rec->hw_queue_size : rec->hw_buffer_size;
	जबतक (rec->hw_पढ़ोy < qsize && rec->sw_पढ़ोy > 0) अणु
		अचिन्हित पूर्णांक hw_to_end = rec->hw_buffer_size - rec->hw_data;
		अचिन्हित पूर्णांक sw_to_end = rec->sw_buffer_size - rec->sw_data;
		अचिन्हित पूर्णांक bytes = qsize - rec->hw_पढ़ोy;
		अगर (rec->sw_पढ़ोy < (पूर्णांक)bytes)
			bytes = rec->sw_पढ़ोy;
		अगर (hw_to_end < bytes)
			bytes = hw_to_end;
		अगर (sw_to_end < bytes)
			bytes = sw_to_end;
		अगर (! bytes)
			अवरोध;
		copy(substream, rec, bytes);
		rec->hw_data += bytes;
		अगर (rec->hw_data == rec->hw_buffer_size)
			rec->hw_data = 0;
		rec->sw_data += bytes;
		अगर (rec->sw_data == rec->sw_buffer_size)
			rec->sw_data = 0;
		rec->hw_पढ़ोy += bytes;
		rec->sw_पढ़ोy -= bytes;
	पूर्ण
	वापस 0;
पूर्ण

/*
 * helper function क्रम playback poपूर्णांकer callback
 * ptr = current byte poपूर्णांकer
 */
अटल अंतरभूत snd_pcm_uframes_t
snd_pcm_indirect_playback_poपूर्णांकer(काष्ठा snd_pcm_substream *substream,
				  काष्ठा snd_pcm_indirect *rec, अचिन्हित पूर्णांक ptr)
अणु
	पूर्णांक bytes = ptr - rec->hw_io;
	अगर (bytes < 0)
		bytes += rec->hw_buffer_size;
	rec->hw_io = ptr;
	rec->hw_पढ़ोy -= bytes;
	rec->sw_io += bytes;
	अगर (rec->sw_io >= rec->sw_buffer_size)
		rec->sw_io -= rec->sw_buffer_size;
	अगर (substream->ops->ack)
		substream->ops->ack(substream);
	वापस bytes_to_frames(substream->runसमय, rec->sw_io);
पूर्ण


/*
 * helper function क्रम capture ack callback
 */
अटल अंतरभूत पूर्णांक
snd_pcm_indirect_capture_transfer(काष्ठा snd_pcm_substream *substream,
				  काष्ठा snd_pcm_indirect *rec,
				  snd_pcm_indirect_copy_t copy)
अणु
	काष्ठा snd_pcm_runसमय *runसमय = substream->runसमय;
	snd_pcm_uframes_t appl_ptr = runसमय->control->appl_ptr;
	snd_pcm_sframes_t dअगरf = appl_ptr - rec->appl_ptr;

	अगर (dअगरf) अणु
		अगर (dअगरf < -(snd_pcm_sframes_t) (runसमय->boundary / 2))
			dअगरf += runसमय->boundary;
		अगर (dअगरf < 0)
			वापस -EINVAL;
		rec->sw_पढ़ोy -= frames_to_bytes(runसमय, dअगरf);
		rec->appl_ptr = appl_ptr;
	पूर्ण
	जबतक (rec->hw_पढ़ोy > 0 && 
	       rec->sw_पढ़ोy < (पूर्णांक)rec->sw_buffer_size) अणु
		माप_प्रकार hw_to_end = rec->hw_buffer_size - rec->hw_data;
		माप_प्रकार sw_to_end = rec->sw_buffer_size - rec->sw_data;
		माप_प्रकार bytes = rec->sw_buffer_size - rec->sw_पढ़ोy;
		अगर (rec->hw_पढ़ोy < (पूर्णांक)bytes)
			bytes = rec->hw_पढ़ोy;
		अगर (hw_to_end < bytes)
			bytes = hw_to_end;
		अगर (sw_to_end < bytes)
			bytes = sw_to_end;
		अगर (! bytes)
			अवरोध;
		copy(substream, rec, bytes);
		rec->hw_data += bytes;
		अगर ((पूर्णांक)rec->hw_data == rec->hw_buffer_size)
			rec->hw_data = 0;
		rec->sw_data += bytes;
		अगर (rec->sw_data == rec->sw_buffer_size)
			rec->sw_data = 0;
		rec->hw_पढ़ोy -= bytes;
		rec->sw_पढ़ोy += bytes;
	पूर्ण
	वापस 0;
पूर्ण

/*
 * helper function क्रम capture poपूर्णांकer callback,
 * ptr = current byte poपूर्णांकer
 */
अटल अंतरभूत snd_pcm_uframes_t
snd_pcm_indirect_capture_poपूर्णांकer(काष्ठा snd_pcm_substream *substream,
				 काष्ठा snd_pcm_indirect *rec, अचिन्हित पूर्णांक ptr)
अणु
	पूर्णांक qsize;
	पूर्णांक bytes = ptr - rec->hw_io;
	अगर (bytes < 0)
		bytes += rec->hw_buffer_size;
	rec->hw_io = ptr;
	rec->hw_पढ़ोy += bytes;
	qsize = rec->hw_queue_size ? rec->hw_queue_size : rec->hw_buffer_size;
	अगर (rec->hw_पढ़ोy > qsize)
		वापस SNDRV_PCM_POS_XRUN;
	rec->sw_io += bytes;
	अगर (rec->sw_io >= rec->sw_buffer_size)
		rec->sw_io -= rec->sw_buffer_size;
	अगर (substream->ops->ack)
		substream->ops->ack(substream);
	वापस bytes_to_frames(substream->runसमय, rec->sw_io);
पूर्ण

#पूर्ण_अगर /* __SOUND_PCM_INसूचीECT_H */
