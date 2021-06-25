<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *  Digital Audio (PCM) असलtract layer
 *  Copyright (c) by Jaroslav Kysela <perex@perex.cz>
 */

#समावेश <linux/init.h>
#समावेश <linux/slab.h>
#समावेश <linux/module.h>
#समावेश <linux/समय.स>
#समावेश <linux/mutex.h>
#समावेश <linux/device.h>
#समावेश <linux/nospec.h>
#समावेश <sound/core.h>
#समावेश <sound/minors.h>
#समावेश <sound/pcm.h>
#समावेश <sound/समयr.h>
#समावेश <sound/control.h>
#समावेश <sound/info.h>

#समावेश "pcm_local.h"

MODULE_AUTHOR("Jaroslav Kysela <perex@perex.cz>, Abramo Bagnara <abramo@alsa-project.org>");
MODULE_DESCRIPTION("Midlevel PCM code for ALSA.");
MODULE_LICENSE("GPL");

अटल LIST_HEAD(snd_pcm_devices);
अटल DEFINE_MUTEX(रेजिस्टर_mutex);
#अगर IS_ENABLED(CONFIG_SND_PCM_OSS)
अटल LIST_HEAD(snd_pcm_notअगरy_list);
#पूर्ण_अगर

अटल पूर्णांक snd_pcm_मुक्त(काष्ठा snd_pcm *pcm);
अटल पूर्णांक snd_pcm_dev_मुक्त(काष्ठा snd_device *device);
अटल पूर्णांक snd_pcm_dev_रेजिस्टर(काष्ठा snd_device *device);
अटल पूर्णांक snd_pcm_dev_disconnect(काष्ठा snd_device *device);

अटल काष्ठा snd_pcm *snd_pcm_get(काष्ठा snd_card *card, पूर्णांक device)
अणु
	काष्ठा snd_pcm *pcm;

	list_क्रम_each_entry(pcm, &snd_pcm_devices, list) अणु
		अगर (pcm->card == card && pcm->device == device)
			वापस pcm;
	पूर्ण
	वापस शून्य;
पूर्ण

अटल पूर्णांक snd_pcm_next(काष्ठा snd_card *card, पूर्णांक device)
अणु
	काष्ठा snd_pcm *pcm;

	list_क्रम_each_entry(pcm, &snd_pcm_devices, list) अणु
		अगर (pcm->card == card && pcm->device > device)
			वापस pcm->device;
		अन्यथा अगर (pcm->card->number > card->number)
			वापस -1;
	पूर्ण
	वापस -1;
पूर्ण

अटल पूर्णांक snd_pcm_add(काष्ठा snd_pcm *newpcm)
अणु
	काष्ठा snd_pcm *pcm;

	अगर (newpcm->पूर्णांकernal)
		वापस 0;

	list_क्रम_each_entry(pcm, &snd_pcm_devices, list) अणु
		अगर (pcm->card == newpcm->card && pcm->device == newpcm->device)
			वापस -EBUSY;
		अगर (pcm->card->number > newpcm->card->number ||
				(pcm->card == newpcm->card &&
				pcm->device > newpcm->device)) अणु
			list_add(&newpcm->list, pcm->list.prev);
			वापस 0;
		पूर्ण
	पूर्ण
	list_add_tail(&newpcm->list, &snd_pcm_devices);
	वापस 0;
पूर्ण

अटल पूर्णांक snd_pcm_control_ioctl(काष्ठा snd_card *card,
				 काष्ठा snd_ctl_file *control,
				 अचिन्हित पूर्णांक cmd, अचिन्हित दीर्घ arg)
अणु
	चयन (cmd) अणु
	हाल SNDRV_CTL_IOCTL_PCM_NEXT_DEVICE:
		अणु
			पूर्णांक device;

			अगर (get_user(device, (पूर्णांक __user *)arg))
				वापस -EFAULT;
			mutex_lock(&रेजिस्टर_mutex);
			device = snd_pcm_next(card, device);
			mutex_unlock(&रेजिस्टर_mutex);
			अगर (put_user(device, (पूर्णांक __user *)arg))
				वापस -EFAULT;
			वापस 0;
		पूर्ण
	हाल SNDRV_CTL_IOCTL_PCM_INFO:
		अणु
			काष्ठा snd_pcm_info __user *info;
			अचिन्हित पूर्णांक device, subdevice;
			पूर्णांक stream;
			काष्ठा snd_pcm *pcm;
			काष्ठा snd_pcm_str *pstr;
			काष्ठा snd_pcm_substream *substream;
			पूर्णांक err;

			info = (काष्ठा snd_pcm_info __user *)arg;
			अगर (get_user(device, &info->device))
				वापस -EFAULT;
			अगर (get_user(stream, &info->stream))
				वापस -EFAULT;
			अगर (stream < 0 || stream > 1)
				वापस -EINVAL;
			stream = array_index_nospec(stream, 2);
			अगर (get_user(subdevice, &info->subdevice))
				वापस -EFAULT;
			mutex_lock(&रेजिस्टर_mutex);
			pcm = snd_pcm_get(card, device);
			अगर (pcm == शून्य) अणु
				err = -ENXIO;
				जाओ _error;
			पूर्ण
			pstr = &pcm->streams[stream];
			अगर (pstr->substream_count == 0) अणु
				err = -ENOENT;
				जाओ _error;
			पूर्ण
			अगर (subdevice >= pstr->substream_count) अणु
				err = -ENXIO;
				जाओ _error;
			पूर्ण
			क्रम (substream = pstr->substream; substream;
			     substream = substream->next)
				अगर (substream->number == (पूर्णांक)subdevice)
					अवरोध;
			अगर (substream == शून्य) अणु
				err = -ENXIO;
				जाओ _error;
			पूर्ण
			mutex_lock(&pcm->खोलो_mutex);
			err = snd_pcm_info_user(substream, info);
			mutex_unlock(&pcm->खोलो_mutex);
		_error:
			mutex_unlock(&रेजिस्टर_mutex);
			वापस err;
		पूर्ण
	हाल SNDRV_CTL_IOCTL_PCM_PREFER_SUBDEVICE:
		अणु
			पूर्णांक val;
			
			अगर (get_user(val, (पूर्णांक __user *)arg))
				वापस -EFAULT;
			control->preferred_subdevice[SND_CTL_SUBDEV_PCM] = val;
			वापस 0;
		पूर्ण
	पूर्ण
	वापस -ENOIOCTLCMD;
पूर्ण

#घोषणा FORMAT(v) [SNDRV_PCM_FORMAT_##v] = #v

अटल स्थिर अक्षर * स्थिर snd_pcm_क्रमmat_names[] = अणु
	FORMAT(S8),
	FORMAT(U8),
	FORMAT(S16_LE),
	FORMAT(S16_BE),
	FORMAT(U16_LE),
	FORMAT(U16_BE),
	FORMAT(S24_LE),
	FORMAT(S24_BE),
	FORMAT(U24_LE),
	FORMAT(U24_BE),
	FORMAT(S32_LE),
	FORMAT(S32_BE),
	FORMAT(U32_LE),
	FORMAT(U32_BE),
	FORMAT(FLOAT_LE),
	FORMAT(FLOAT_BE),
	FORMAT(FLOAT64_LE),
	FORMAT(FLOAT64_BE),
	FORMAT(IEC958_SUBFRAME_LE),
	FORMAT(IEC958_SUBFRAME_BE),
	FORMAT(MU_LAW),
	FORMAT(A_LAW),
	FORMAT(IMA_ADPCM),
	FORMAT(MPEG),
	FORMAT(GSM),
	FORMAT(SPECIAL),
	FORMAT(S24_3LE),
	FORMAT(S24_3BE),
	FORMAT(U24_3LE),
	FORMAT(U24_3BE),
	FORMAT(S20_3LE),
	FORMAT(S20_3BE),
	FORMAT(U20_3LE),
	FORMAT(U20_3BE),
	FORMAT(S18_3LE),
	FORMAT(S18_3BE),
	FORMAT(U18_3LE),
	FORMAT(U18_3BE),
	FORMAT(G723_24),
	FORMAT(G723_24_1B),
	FORMAT(G723_40),
	FORMAT(G723_40_1B),
	FORMAT(DSD_U8),
	FORMAT(DSD_U16_LE),
	FORMAT(DSD_U32_LE),
	FORMAT(DSD_U16_BE),
	FORMAT(DSD_U32_BE),
पूर्ण;

/**
 * snd_pcm_क्रमmat_name - Return a name string क्रम the given PCM क्रमmat
 * @क्रमmat: PCM क्रमmat
 */
स्थिर अक्षर *snd_pcm_क्रमmat_name(snd_pcm_क्रमmat_t क्रमmat)
अणु
	अगर ((__क्रमce अचिन्हित पूर्णांक)क्रमmat >= ARRAY_SIZE(snd_pcm_क्रमmat_names))
		वापस "Unknown";
	वापस snd_pcm_क्रमmat_names[(__क्रमce अचिन्हित पूर्णांक)क्रमmat];
पूर्ण
EXPORT_SYMBOL_GPL(snd_pcm_क्रमmat_name);

#अगर_घोषित CONFIG_SND_VERBOSE_PROCFS

#घोषणा STATE(v) [SNDRV_PCM_STATE_##v] = #v
#घोषणा STREAM(v) [SNDRV_PCM_STREAM_##v] = #v
#घोषणा READY(v) [SNDRV_PCM_READY_##v] = #v
#घोषणा XRUN(v) [SNDRV_PCM_XRUN_##v] = #v
#घोषणा SILENCE(v) [SNDRV_PCM_SILENCE_##v] = #v
#घोषणा TSTAMP(v) [SNDRV_PCM_TSTAMP_##v] = #v
#घोषणा ACCESS(v) [SNDRV_PCM_ACCESS_##v] = #v
#घोषणा START(v) [SNDRV_PCM_START_##v] = #v
#घोषणा SUBFORMAT(v) [SNDRV_PCM_SUBFORMAT_##v] = #v 

अटल स्थिर अक्षर * स्थिर snd_pcm_stream_names[] = अणु
	STREAM(PLAYBACK),
	STREAM(CAPTURE),
पूर्ण;

अटल स्थिर अक्षर * स्थिर snd_pcm_state_names[] = अणु
	STATE(OPEN),
	STATE(SETUP),
	STATE(PREPARED),
	STATE(RUNNING),
	STATE(XRUN),
	STATE(DRAINING),
	STATE(PAUSED),
	STATE(SUSPENDED),
पूर्ण;

अटल स्थिर अक्षर * स्थिर snd_pcm_access_names[] = अणु
	ACCESS(MMAP_INTERLEAVED), 
	ACCESS(MMAP_NONINTERLEAVED),
	ACCESS(MMAP_COMPLEX),
	ACCESS(RW_INTERLEAVED),
	ACCESS(RW_NONINTERLEAVED),
पूर्ण;

अटल स्थिर अक्षर * स्थिर snd_pcm_subक्रमmat_names[] = अणु
	SUBFORMAT(STD), 
पूर्ण;

अटल स्थिर अक्षर * स्थिर snd_pcm_tstamp_mode_names[] = अणु
	TSTAMP(NONE),
	TSTAMP(ENABLE),
पूर्ण;

अटल स्थिर अक्षर *snd_pcm_stream_name(पूर्णांक stream)
अणु
	वापस snd_pcm_stream_names[stream];
पूर्ण

अटल स्थिर अक्षर *snd_pcm_access_name(snd_pcm_access_t access)
अणु
	वापस snd_pcm_access_names[(__क्रमce पूर्णांक)access];
पूर्ण

अटल स्थिर अक्षर *snd_pcm_subक्रमmat_name(snd_pcm_subक्रमmat_t subक्रमmat)
अणु
	वापस snd_pcm_subक्रमmat_names[(__क्रमce पूर्णांक)subक्रमmat];
पूर्ण

अटल स्थिर अक्षर *snd_pcm_tstamp_mode_name(पूर्णांक mode)
अणु
	वापस snd_pcm_tstamp_mode_names[mode];
पूर्ण

अटल स्थिर अक्षर *snd_pcm_state_name(snd_pcm_state_t state)
अणु
	वापस snd_pcm_state_names[(__क्रमce पूर्णांक)state];
पूर्ण

#अगर IS_ENABLED(CONFIG_SND_PCM_OSS)
#समावेश <linux/soundcard.h>

अटल स्थिर अक्षर *snd_pcm_oss_क्रमmat_name(पूर्णांक क्रमmat)
अणु
	चयन (क्रमmat) अणु
	हाल AFMT_MU_LAW:
		वापस "MU_LAW";
	हाल AFMT_A_LAW:
		वापस "A_LAW";
	हाल AFMT_IMA_ADPCM:
		वापस "IMA_ADPCM";
	हाल AFMT_U8:
		वापस "U8";
	हाल AFMT_S16_LE:
		वापस "S16_LE";
	हाल AFMT_S16_BE:
		वापस "S16_BE";
	हाल AFMT_S8:
		वापस "S8";
	हाल AFMT_U16_LE:
		वापस "U16_LE";
	हाल AFMT_U16_BE:
		वापस "U16_BE";
	हाल AFMT_MPEG:
		वापस "MPEG";
	शेष:
		वापस "unknown";
	पूर्ण
पूर्ण
#पूर्ण_अगर

अटल व्योम snd_pcm_proc_info_पढ़ो(काष्ठा snd_pcm_substream *substream,
				   काष्ठा snd_info_buffer *buffer)
अणु
	काष्ठा snd_pcm_info *info;
	पूर्णांक err;

	अगर (! substream)
		वापस;

	info = kदो_स्मृति(माप(*info), GFP_KERNEL);
	अगर (!info)
		वापस;

	err = snd_pcm_info(substream, info);
	अगर (err < 0) अणु
		snd_iम_लिखो(buffer, "error %d\n", err);
		kमुक्त(info);
		वापस;
	पूर्ण
	snd_iम_लिखो(buffer, "card: %d\n", info->card);
	snd_iम_लिखो(buffer, "device: %d\n", info->device);
	snd_iम_लिखो(buffer, "subdevice: %d\n", info->subdevice);
	snd_iम_लिखो(buffer, "stream: %s\n", snd_pcm_stream_name(info->stream));
	snd_iम_लिखो(buffer, "id: %s\n", info->id);
	snd_iम_लिखो(buffer, "name: %s\n", info->name);
	snd_iम_लिखो(buffer, "subname: %s\n", info->subname);
	snd_iम_लिखो(buffer, "class: %d\n", info->dev_class);
	snd_iम_लिखो(buffer, "subclass: %d\n", info->dev_subclass);
	snd_iम_लिखो(buffer, "subdevices_count: %d\n", info->subdevices_count);
	snd_iम_लिखो(buffer, "subdevices_avail: %d\n", info->subdevices_avail);
	kमुक्त(info);
पूर्ण

अटल व्योम snd_pcm_stream_proc_info_पढ़ो(काष्ठा snd_info_entry *entry,
					  काष्ठा snd_info_buffer *buffer)
अणु
	snd_pcm_proc_info_पढ़ो(((काष्ठा snd_pcm_str *)entry->निजी_data)->substream,
			       buffer);
पूर्ण

अटल व्योम snd_pcm_substream_proc_info_पढ़ो(काष्ठा snd_info_entry *entry,
					     काष्ठा snd_info_buffer *buffer)
अणु
	snd_pcm_proc_info_पढ़ो(entry->निजी_data, buffer);
पूर्ण

अटल व्योम snd_pcm_substream_proc_hw_params_पढ़ो(काष्ठा snd_info_entry *entry,
						  काष्ठा snd_info_buffer *buffer)
अणु
	काष्ठा snd_pcm_substream *substream = entry->निजी_data;
	काष्ठा snd_pcm_runसमय *runसमय;

	mutex_lock(&substream->pcm->खोलो_mutex);
	runसमय = substream->runसमय;
	अगर (!runसमय) अणु
		snd_iम_लिखो(buffer, "closed\n");
		जाओ unlock;
	पूर्ण
	अगर (runसमय->status->state == SNDRV_PCM_STATE_OPEN) अणु
		snd_iम_लिखो(buffer, "no setup\n");
		जाओ unlock;
	पूर्ण
	snd_iम_लिखो(buffer, "access: %s\n", snd_pcm_access_name(runसमय->access));
	snd_iम_लिखो(buffer, "format: %s\n", snd_pcm_क्रमmat_name(runसमय->क्रमmat));
	snd_iम_लिखो(buffer, "subformat: %s\n", snd_pcm_subक्रमmat_name(runसमय->subक्रमmat));
	snd_iम_लिखो(buffer, "channels: %u\n", runसमय->channels);	
	snd_iम_लिखो(buffer, "rate: %u (%u/%u)\n", runसमय->rate, runसमय->rate_num, runसमय->rate_den);	
	snd_iम_लिखो(buffer, "period_size: %lu\n", runसमय->period_size);	
	snd_iम_लिखो(buffer, "buffer_size: %lu\n", runसमय->buffer_size);	
#अगर IS_ENABLED(CONFIG_SND_PCM_OSS)
	अगर (substream->oss.oss) अणु
		snd_iम_लिखो(buffer, "OSS format: %s\n", snd_pcm_oss_क्रमmat_name(runसमय->oss.क्रमmat));
		snd_iम_लिखो(buffer, "OSS channels: %u\n", runसमय->oss.channels);	
		snd_iम_लिखो(buffer, "OSS rate: %u\n", runसमय->oss.rate);
		snd_iम_लिखो(buffer, "OSS period bytes: %lu\n", (अचिन्हित दीर्घ)runसमय->oss.period_bytes);
		snd_iम_लिखो(buffer, "OSS periods: %u\n", runसमय->oss.periods);
		snd_iम_लिखो(buffer, "OSS period frames: %lu\n", (अचिन्हित दीर्घ)runसमय->oss.period_frames);
	पूर्ण
#पूर्ण_अगर
 unlock:
	mutex_unlock(&substream->pcm->खोलो_mutex);
पूर्ण

अटल व्योम snd_pcm_substream_proc_sw_params_पढ़ो(काष्ठा snd_info_entry *entry,
						  काष्ठा snd_info_buffer *buffer)
अणु
	काष्ठा snd_pcm_substream *substream = entry->निजी_data;
	काष्ठा snd_pcm_runसमय *runसमय;

	mutex_lock(&substream->pcm->खोलो_mutex);
	runसमय = substream->runसमय;
	अगर (!runसमय) अणु
		snd_iम_लिखो(buffer, "closed\n");
		जाओ unlock;
	पूर्ण
	अगर (runसमय->status->state == SNDRV_PCM_STATE_OPEN) अणु
		snd_iम_लिखो(buffer, "no setup\n");
		जाओ unlock;
	पूर्ण
	snd_iम_लिखो(buffer, "tstamp_mode: %s\n", snd_pcm_tstamp_mode_name(runसमय->tstamp_mode));
	snd_iम_लिखो(buffer, "period_step: %u\n", runसमय->period_step);
	snd_iम_लिखो(buffer, "avail_min: %lu\n", runसमय->control->avail_min);
	snd_iम_लिखो(buffer, "start_threshold: %lu\n", runसमय->start_threshold);
	snd_iम_लिखो(buffer, "stop_threshold: %lu\n", runसमय->stop_threshold);
	snd_iम_लिखो(buffer, "silence_threshold: %lu\n", runसमय->silence_threshold);
	snd_iम_लिखो(buffer, "silence_size: %lu\n", runसमय->silence_size);
	snd_iम_लिखो(buffer, "boundary: %lu\n", runसमय->boundary);
 unlock:
	mutex_unlock(&substream->pcm->खोलो_mutex);
पूर्ण

अटल व्योम snd_pcm_substream_proc_status_पढ़ो(काष्ठा snd_info_entry *entry,
					       काष्ठा snd_info_buffer *buffer)
अणु
	काष्ठा snd_pcm_substream *substream = entry->निजी_data;
	काष्ठा snd_pcm_runसमय *runसमय;
	काष्ठा snd_pcm_status64 status;
	पूर्णांक err;

	mutex_lock(&substream->pcm->खोलो_mutex);
	runसमय = substream->runसमय;
	अगर (!runसमय) अणु
		snd_iम_लिखो(buffer, "closed\n");
		जाओ unlock;
	पूर्ण
	स_रखो(&status, 0, माप(status));
	err = snd_pcm_status64(substream, &status);
	अगर (err < 0) अणु
		snd_iम_लिखो(buffer, "error %d\n", err);
		जाओ unlock;
	पूर्ण
	snd_iम_लिखो(buffer, "state: %s\n", snd_pcm_state_name(status.state));
	snd_iम_लिखो(buffer, "owner_pid   : %d\n", pid_vnr(substream->pid));
	snd_iम_लिखो(buffer, "trigger_time: %lld.%09lld\n",
		status.trigger_tstamp_sec, status.trigger_tstamp_nsec);
	snd_iम_लिखो(buffer, "tstamp      : %lld.%09lld\n",
		status.tstamp_sec, status.tstamp_nsec);
	snd_iम_लिखो(buffer, "delay       : %ld\n", status.delay);
	snd_iम_लिखो(buffer, "avail       : %ld\n", status.avail);
	snd_iम_लिखो(buffer, "avail_max   : %ld\n", status.avail_max);
	snd_iम_लिखो(buffer, "-----\n");
	snd_iम_लिखो(buffer, "hw_ptr      : %ld\n", runसमय->status->hw_ptr);
	snd_iम_लिखो(buffer, "appl_ptr    : %ld\n", runसमय->control->appl_ptr);
 unlock:
	mutex_unlock(&substream->pcm->खोलो_mutex);
पूर्ण

#अगर_घोषित CONFIG_SND_PCM_XRUN_DEBUG
अटल व्योम snd_pcm_xrun_injection_ग_लिखो(काष्ठा snd_info_entry *entry,
					 काष्ठा snd_info_buffer *buffer)
अणु
	काष्ठा snd_pcm_substream *substream = entry->निजी_data;

	snd_pcm_stop_xrun(substream);
पूर्ण

अटल व्योम snd_pcm_xrun_debug_पढ़ो(काष्ठा snd_info_entry *entry,
				    काष्ठा snd_info_buffer *buffer)
अणु
	काष्ठा snd_pcm_str *pstr = entry->निजी_data;
	snd_iम_लिखो(buffer, "%d\n", pstr->xrun_debug);
पूर्ण

अटल व्योम snd_pcm_xrun_debug_ग_लिखो(काष्ठा snd_info_entry *entry,
				     काष्ठा snd_info_buffer *buffer)
अणु
	काष्ठा snd_pcm_str *pstr = entry->निजी_data;
	अक्षर line[64];
	अगर (!snd_info_get_line(buffer, line, माप(line)))
		pstr->xrun_debug = simple_म_से_अदीर्घ(line, शून्य, 10);
पूर्ण
#पूर्ण_अगर

अटल पूर्णांक snd_pcm_stream_proc_init(काष्ठा snd_pcm_str *pstr)
अणु
	काष्ठा snd_pcm *pcm = pstr->pcm;
	काष्ठा snd_info_entry *entry;
	अक्षर name[16];

	प्र_लिखो(name, "pcm%i%c", pcm->device, 
		pstr->stream == SNDRV_PCM_STREAM_PLAYBACK ? 'p' : 'c');
	entry = snd_info_create_card_entry(pcm->card, name,
					   pcm->card->proc_root);
	अगर (!entry)
		वापस -ENOMEM;
	entry->mode = S_IFसूची | 0555;
	pstr->proc_root = entry;
	entry = snd_info_create_card_entry(pcm->card, "info", pstr->proc_root);
	अगर (entry)
		snd_info_set_text_ops(entry, pstr, snd_pcm_stream_proc_info_पढ़ो);
#अगर_घोषित CONFIG_SND_PCM_XRUN_DEBUG
	entry = snd_info_create_card_entry(pcm->card, "xrun_debug",
					   pstr->proc_root);
	अगर (entry) अणु
		snd_info_set_text_ops(entry, pstr, snd_pcm_xrun_debug_पढ़ो);
		entry->c.text.ग_लिखो = snd_pcm_xrun_debug_ग_लिखो;
		entry->mode |= 0200;
	पूर्ण
#पूर्ण_अगर
	वापस 0;
पूर्ण

अटल पूर्णांक snd_pcm_stream_proc_करोne(काष्ठा snd_pcm_str *pstr)
अणु
	snd_info_मुक्त_entry(pstr->proc_root);
	pstr->proc_root = शून्य;
	वापस 0;
पूर्ण

अटल काष्ठा snd_info_entry *
create_substream_info_entry(काष्ठा snd_pcm_substream *substream,
			    स्थिर अक्षर *name,
			    व्योम (*पढ़ो)(काष्ठा snd_info_entry *,
					 काष्ठा snd_info_buffer *))
अणु
	काष्ठा snd_info_entry *entry;

	entry = snd_info_create_card_entry(substream->pcm->card, name,
					   substream->proc_root);
	अगर (entry)
		snd_info_set_text_ops(entry, substream, पढ़ो);
	वापस entry;
पूर्ण

अटल पूर्णांक snd_pcm_substream_proc_init(काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा snd_info_entry *entry;
	काष्ठा snd_card *card;
	अक्षर name[16];

	card = substream->pcm->card;

	प्र_लिखो(name, "sub%i", substream->number);
	entry = snd_info_create_card_entry(card, name,
					   substream->pstr->proc_root);
	अगर (!entry)
		वापस -ENOMEM;
	entry->mode = S_IFसूची | 0555;
	substream->proc_root = entry;

	create_substream_info_entry(substream, "info",
				    snd_pcm_substream_proc_info_पढ़ो);
	create_substream_info_entry(substream, "hw_params",
				    snd_pcm_substream_proc_hw_params_पढ़ो);
	create_substream_info_entry(substream, "sw_params",
				    snd_pcm_substream_proc_sw_params_पढ़ो);
	create_substream_info_entry(substream, "status",
				    snd_pcm_substream_proc_status_पढ़ो);

#अगर_घोषित CONFIG_SND_PCM_XRUN_DEBUG
	entry = create_substream_info_entry(substream, "xrun_injection", शून्य);
	अगर (entry) अणु
		entry->c.text.ग_लिखो = snd_pcm_xrun_injection_ग_लिखो;
		entry->mode = S_IFREG | 0200;
	पूर्ण
#पूर्ण_अगर /* CONFIG_SND_PCM_XRUN_DEBUG */

	वापस 0;
पूर्ण

#अन्यथा /* !CONFIG_SND_VERBOSE_PROCFS */
अटल अंतरभूत पूर्णांक snd_pcm_stream_proc_init(काष्ठा snd_pcm_str *pstr) अणु वापस 0; पूर्ण
अटल अंतरभूत पूर्णांक snd_pcm_stream_proc_करोne(काष्ठा snd_pcm_str *pstr) अणु वापस 0; पूर्ण
अटल अंतरभूत पूर्णांक snd_pcm_substream_proc_init(काष्ठा snd_pcm_substream *substream) अणु वापस 0; पूर्ण
#पूर्ण_अगर /* CONFIG_SND_VERBOSE_PROCFS */

अटल स्थिर काष्ठा attribute_group *pcm_dev_attr_groups[];

/*
 * PM callbacks: we need to deal only with suspend here, as the resume is
 * triggered either from user-space or the driver's resume callback
 */
#अगर_घोषित CONFIG_PM_SLEEP
अटल पूर्णांक करो_pcm_suspend(काष्ठा device *dev)
अणु
	काष्ठा snd_pcm_str *pstr = container_of(dev, काष्ठा snd_pcm_str, dev);

	अगर (!pstr->pcm->no_device_suspend)
		snd_pcm_suspend_all(pstr->pcm);
	वापस 0;
पूर्ण
#पूर्ण_अगर

अटल स्थिर काष्ठा dev_pm_ops pcm_dev_pm_ops = अणु
	SET_SYSTEM_SLEEP_PM_OPS(करो_pcm_suspend, शून्य)
पूर्ण;

/* device type क्रम PCM -- basically only क्रम passing PM callbacks */
अटल स्थिर काष्ठा device_type pcm_dev_type = अणु
	.name = "pcm",
	.pm = &pcm_dev_pm_ops,
पूर्ण;

/**
 * snd_pcm_new_stream - create a new PCM stream
 * @pcm: the pcm instance
 * @stream: the stream direction, SNDRV_PCM_STREAM_XXX
 * @substream_count: the number of substreams
 *
 * Creates a new stream क्रम the pcm.
 * The corresponding stream on the pcm must have been empty beक्रमe
 * calling this, i.e. zero must be given to the argument of
 * snd_pcm_new().
 *
 * Return: Zero अगर successful, or a negative error code on failure.
 */
पूर्णांक snd_pcm_new_stream(काष्ठा snd_pcm *pcm, पूर्णांक stream, पूर्णांक substream_count)
अणु
	पूर्णांक idx, err;
	काष्ठा snd_pcm_str *pstr = &pcm->streams[stream];
	काष्ठा snd_pcm_substream *substream, *prev;

#अगर IS_ENABLED(CONFIG_SND_PCM_OSS)
	mutex_init(&pstr->oss.setup_mutex);
#पूर्ण_अगर
	pstr->stream = stream;
	pstr->pcm = pcm;
	pstr->substream_count = substream_count;
	अगर (!substream_count)
		वापस 0;

	snd_device_initialize(&pstr->dev, pcm->card);
	pstr->dev.groups = pcm_dev_attr_groups;
	pstr->dev.type = &pcm_dev_type;
	dev_set_name(&pstr->dev, "pcmC%iD%i%c", pcm->card->number, pcm->device,
		     stream == SNDRV_PCM_STREAM_PLAYBACK ? 'p' : 'c');

	अगर (!pcm->पूर्णांकernal) अणु
		err = snd_pcm_stream_proc_init(pstr);
		अगर (err < 0) अणु
			pcm_err(pcm, "Error in snd_pcm_stream_proc_init\n");
			वापस err;
		पूर्ण
	पूर्ण
	prev = शून्य;
	क्रम (idx = 0, prev = शून्य; idx < substream_count; idx++) अणु
		substream = kzalloc(माप(*substream), GFP_KERNEL);
		अगर (!substream)
			वापस -ENOMEM;
		substream->pcm = pcm;
		substream->pstr = pstr;
		substream->number = idx;
		substream->stream = stream;
		प्र_लिखो(substream->name, "subdevice #%i", idx);
		substream->buffer_bytes_max = अच_पूर्णांक_उच्च;
		अगर (prev == शून्य)
			pstr->substream = substream;
		अन्यथा
			prev->next = substream;

		अगर (!pcm->पूर्णांकernal) अणु
			err = snd_pcm_substream_proc_init(substream);
			अगर (err < 0) अणु
				pcm_err(pcm,
					"Error in snd_pcm_stream_proc_init\n");
				अगर (prev == शून्य)
					pstr->substream = शून्य;
				अन्यथा
					prev->next = शून्य;
				kमुक्त(substream);
				वापस err;
			पूर्ण
		पूर्ण
		substream->group = &substream->self_group;
		snd_pcm_group_init(&substream->self_group);
		list_add_tail(&substream->link_list, &substream->self_group.substreams);
		atomic_set(&substream->mmap_count, 0);
		prev = substream;
	पूर्ण
	वापस 0;
पूर्ण				
EXPORT_SYMBOL(snd_pcm_new_stream);

अटल पूर्णांक _snd_pcm_new(काष्ठा snd_card *card, स्थिर अक्षर *id, पूर्णांक device,
		पूर्णांक playback_count, पूर्णांक capture_count, bool पूर्णांकernal,
		काष्ठा snd_pcm **rpcm)
अणु
	काष्ठा snd_pcm *pcm;
	पूर्णांक err;
	अटल स्थिर काष्ठा snd_device_ops ops = अणु
		.dev_मुक्त = snd_pcm_dev_मुक्त,
		.dev_रेजिस्टर =	snd_pcm_dev_रेजिस्टर,
		.dev_disconnect = snd_pcm_dev_disconnect,
	पूर्ण;
	अटल स्थिर काष्ठा snd_device_ops पूर्णांकernal_ops = अणु
		.dev_मुक्त = snd_pcm_dev_मुक्त,
	पूर्ण;

	अगर (snd_BUG_ON(!card))
		वापस -ENXIO;
	अगर (rpcm)
		*rpcm = शून्य;
	pcm = kzalloc(माप(*pcm), GFP_KERNEL);
	अगर (!pcm)
		वापस -ENOMEM;
	pcm->card = card;
	pcm->device = device;
	pcm->पूर्णांकernal = पूर्णांकernal;
	mutex_init(&pcm->खोलो_mutex);
	init_रुकोqueue_head(&pcm->खोलो_रुको);
	INIT_LIST_HEAD(&pcm->list);
	अगर (id)
		strscpy(pcm->id, id, माप(pcm->id));

	err = snd_pcm_new_stream(pcm, SNDRV_PCM_STREAM_PLAYBACK,
				 playback_count);
	अगर (err < 0)
		जाओ मुक्त_pcm;

	err = snd_pcm_new_stream(pcm, SNDRV_PCM_STREAM_CAPTURE, capture_count);
	अगर (err < 0)
		जाओ मुक्त_pcm;

	err = snd_device_new(card, SNDRV_DEV_PCM, pcm,
			     पूर्णांकernal ? &पूर्णांकernal_ops : &ops);
	अगर (err < 0)
		जाओ मुक्त_pcm;

	अगर (rpcm)
		*rpcm = pcm;
	वापस 0;

मुक्त_pcm:
	snd_pcm_मुक्त(pcm);
	वापस err;
पूर्ण

/**
 * snd_pcm_new - create a new PCM instance
 * @card: the card instance
 * @id: the id string
 * @device: the device index (zero based)
 * @playback_count: the number of substreams क्रम playback
 * @capture_count: the number of substreams क्रम capture
 * @rpcm: the poपूर्णांकer to store the new pcm instance
 *
 * Creates a new PCM instance.
 *
 * The pcm चालकs have to be set afterwards to the new instance
 * via snd_pcm_set_ops().
 *
 * Return: Zero अगर successful, or a negative error code on failure.
 */
पूर्णांक snd_pcm_new(काष्ठा snd_card *card, स्थिर अक्षर *id, पूर्णांक device,
		पूर्णांक playback_count, पूर्णांक capture_count, काष्ठा snd_pcm **rpcm)
अणु
	वापस _snd_pcm_new(card, id, device, playback_count, capture_count,
			false, rpcm);
पूर्ण
EXPORT_SYMBOL(snd_pcm_new);

/**
 * snd_pcm_new_पूर्णांकernal - create a new पूर्णांकernal PCM instance
 * @card: the card instance
 * @id: the id string
 * @device: the device index (zero based - shared with normal PCMs)
 * @playback_count: the number of substreams क्रम playback
 * @capture_count: the number of substreams क्रम capture
 * @rpcm: the poपूर्णांकer to store the new pcm instance
 *
 * Creates a new पूर्णांकernal PCM instance with no userspace device or procfs
 * entries. This is used by ASoC Back End PCMs in order to create a PCM that
 * will only be used पूर्णांकernally by kernel drivers. i.e. it cannot be खोलोed
 * by userspace. It provides existing ASoC components drivers with a substream
 * and access to any निजी data.
 *
 * The pcm चालकs have to be set afterwards to the new instance
 * via snd_pcm_set_ops().
 *
 * Return: Zero अगर successful, or a negative error code on failure.
 */
पूर्णांक snd_pcm_new_पूर्णांकernal(काष्ठा snd_card *card, स्थिर अक्षर *id, पूर्णांक device,
	पूर्णांक playback_count, पूर्णांक capture_count,
	काष्ठा snd_pcm **rpcm)
अणु
	वापस _snd_pcm_new(card, id, device, playback_count, capture_count,
			true, rpcm);
पूर्ण
EXPORT_SYMBOL(snd_pcm_new_पूर्णांकernal);

अटल व्योम मुक्त_chmap(काष्ठा snd_pcm_str *pstr)
अणु
	अगर (pstr->chmap_kctl) अणु
		snd_ctl_हटाओ(pstr->pcm->card, pstr->chmap_kctl);
		pstr->chmap_kctl = शून्य;
	पूर्ण
पूर्ण

अटल व्योम snd_pcm_मुक्त_stream(काष्ठा snd_pcm_str * pstr)
अणु
	काष्ठा snd_pcm_substream *substream, *substream_next;
#अगर IS_ENABLED(CONFIG_SND_PCM_OSS)
	काष्ठा snd_pcm_oss_setup *setup, *setupn;
#पूर्ण_अगर

	/* मुक्त all proc files under the stream */
	snd_pcm_stream_proc_करोne(pstr);

	substream = pstr->substream;
	जबतक (substream) अणु
		substream_next = substream->next;
		snd_pcm_समयr_करोne(substream);
		kमुक्त(substream);
		substream = substream_next;
	पूर्ण
#अगर IS_ENABLED(CONFIG_SND_PCM_OSS)
	क्रम (setup = pstr->oss.setup_list; setup; setup = setupn) अणु
		setupn = setup->next;
		kमुक्त(setup->task_name);
		kमुक्त(setup);
	पूर्ण
#पूर्ण_अगर
	मुक्त_chmap(pstr);
	अगर (pstr->substream_count)
		put_device(&pstr->dev);
पूर्ण

#अगर IS_ENABLED(CONFIG_SND_PCM_OSS)
#घोषणा pcm_call_notअगरy(pcm, call)					\
	करो अणु								\
		काष्ठा snd_pcm_notअगरy *_notअगरy;				\
		list_क्रम_each_entry(_notअगरy, &snd_pcm_notअगरy_list, list) \
			_notअगरy->call(pcm);				\
	पूर्ण जबतक (0)
#अन्यथा
#घोषणा pcm_call_notअगरy(pcm, call) करो अणुपूर्ण जबतक (0)
#पूर्ण_अगर

अटल पूर्णांक snd_pcm_मुक्त(काष्ठा snd_pcm *pcm)
अणु
	अगर (!pcm)
		वापस 0;
	अगर (!pcm->पूर्णांकernal)
		pcm_call_notअगरy(pcm, n_unरेजिस्टर);
	अगर (pcm->निजी_मुक्त)
		pcm->निजी_मुक्त(pcm);
	snd_pcm_lib_pपुनः_स्मृतिate_मुक्त_क्रम_all(pcm);
	snd_pcm_मुक्त_stream(&pcm->streams[SNDRV_PCM_STREAM_PLAYBACK]);
	snd_pcm_मुक्त_stream(&pcm->streams[SNDRV_PCM_STREAM_CAPTURE]);
	kमुक्त(pcm);
	वापस 0;
पूर्ण

अटल पूर्णांक snd_pcm_dev_मुक्त(काष्ठा snd_device *device)
अणु
	काष्ठा snd_pcm *pcm = device->device_data;
	वापस snd_pcm_मुक्त(pcm);
पूर्ण

पूर्णांक snd_pcm_attach_substream(काष्ठा snd_pcm *pcm, पूर्णांक stream,
			     काष्ठा file *file,
			     काष्ठा snd_pcm_substream **rsubstream)
अणु
	काष्ठा snd_pcm_str * pstr;
	काष्ठा snd_pcm_substream *substream;
	काष्ठा snd_pcm_runसमय *runसमय;
	काष्ठा snd_card *card;
	पूर्णांक prefer_subdevice;
	माप_प्रकार size;

	अगर (snd_BUG_ON(!pcm || !rsubstream))
		वापस -ENXIO;
	अगर (snd_BUG_ON(stream != SNDRV_PCM_STREAM_PLAYBACK &&
		       stream != SNDRV_PCM_STREAM_CAPTURE))
		वापस -EINVAL;
	*rsubstream = शून्य;
	pstr = &pcm->streams[stream];
	अगर (pstr->substream == शून्य || pstr->substream_count == 0)
		वापस -ENODEV;

	card = pcm->card;
	prefer_subdevice = snd_ctl_get_preferred_subdevice(card, SND_CTL_SUBDEV_PCM);

	अगर (pcm->info_flags & SNDRV_PCM_INFO_HALF_DUPLEX) अणु
		पूर्णांक opposite = !stream;

		क्रम (substream = pcm->streams[opposite].substream; substream;
		     substream = substream->next) अणु
			अगर (SUBSTREAM_BUSY(substream))
				वापस -EAGAIN;
		पूर्ण
	पूर्ण

	अगर (file->f_flags & O_APPEND) अणु
		अगर (prefer_subdevice < 0) अणु
			अगर (pstr->substream_count > 1)
				वापस -EINVAL; /* must be unique */
			substream = pstr->substream;
		पूर्ण अन्यथा अणु
			क्रम (substream = pstr->substream; substream;
			     substream = substream->next)
				अगर (substream->number == prefer_subdevice)
					अवरोध;
		पूर्ण
		अगर (! substream)
			वापस -ENODEV;
		अगर (! SUBSTREAM_BUSY(substream))
			वापस -EBADFD;
		substream->ref_count++;
		*rsubstream = substream;
		वापस 0;
	पूर्ण

	क्रम (substream = pstr->substream; substream; substream = substream->next) अणु
		अगर (!SUBSTREAM_BUSY(substream) &&
		    (prefer_subdevice == -1 ||
		     substream->number == prefer_subdevice))
			अवरोध;
	पूर्ण
	अगर (substream == शून्य)
		वापस -EAGAIN;

	runसमय = kzalloc(माप(*runसमय), GFP_KERNEL);
	अगर (runसमय == शून्य)
		वापस -ENOMEM;

	size = PAGE_ALIGN(माप(काष्ठा snd_pcm_mmap_status));
	runसमय->status = alloc_pages_exact(size, GFP_KERNEL);
	अगर (runसमय->status == शून्य) अणु
		kमुक्त(runसमय);
		वापस -ENOMEM;
	पूर्ण
	स_रखो(runसमय->status, 0, size);

	size = PAGE_ALIGN(माप(काष्ठा snd_pcm_mmap_control));
	runसमय->control = alloc_pages_exact(size, GFP_KERNEL);
	अगर (runसमय->control == शून्य) अणु
		मुक्त_pages_exact(runसमय->status,
			       PAGE_ALIGN(माप(काष्ठा snd_pcm_mmap_status)));
		kमुक्त(runसमय);
		वापस -ENOMEM;
	पूर्ण
	स_रखो(runसमय->control, 0, size);

	init_रुकोqueue_head(&runसमय->sleep);
	init_रुकोqueue_head(&runसमय->tsleep);

	runसमय->status->state = SNDRV_PCM_STATE_OPEN;

	substream->runसमय = runसमय;
	substream->निजी_data = pcm->निजी_data;
	substream->ref_count = 1;
	substream->f_flags = file->f_flags;
	substream->pid = get_pid(task_pid(current));
	pstr->substream_खोलोed++;
	*rsubstream = substream;
	वापस 0;
पूर्ण

व्योम snd_pcm_detach_substream(काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा snd_pcm_runसमय *runसमय;

	अगर (PCM_RUNTIME_CHECK(substream))
		वापस;
	runसमय = substream->runसमय;
	अगर (runसमय->निजी_मुक्त != शून्य)
		runसमय->निजी_मुक्त(runसमय);
	मुक्त_pages_exact(runसमय->status,
		       PAGE_ALIGN(माप(काष्ठा snd_pcm_mmap_status)));
	मुक्त_pages_exact(runसमय->control,
		       PAGE_ALIGN(माप(काष्ठा snd_pcm_mmap_control)));
	kमुक्त(runसमय->hw_स्थिरraपूर्णांकs.rules);
	/* Aव्योम concurrent access to runसमय via PCM समयr पूर्णांकerface */
	अगर (substream->समयr) अणु
		spin_lock_irq(&substream->समयr->lock);
		substream->runसमय = शून्य;
		spin_unlock_irq(&substream->समयr->lock);
	पूर्ण अन्यथा अणु
		substream->runसमय = शून्य;
	पूर्ण
	kमुक्त(runसमय);
	put_pid(substream->pid);
	substream->pid = शून्य;
	substream->pstr->substream_खोलोed--;
पूर्ण

अटल sमाप_प्रकार show_pcm_class(काष्ठा device *dev,
			      काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा snd_pcm_str *pstr = container_of(dev, काष्ठा snd_pcm_str, dev);
	काष्ठा snd_pcm *pcm = pstr->pcm;
	स्थिर अक्षर *str;
	अटल स्थिर अक्षर *strs[SNDRV_PCM_CLASS_LAST + 1] = अणु
		[SNDRV_PCM_CLASS_GENERIC] = "generic",
		[SNDRV_PCM_CLASS_MULTI] = "multi",
		[SNDRV_PCM_CLASS_MODEM] = "modem",
		[SNDRV_PCM_CLASS_DIGITIZER] = "digitizer",
	पूर्ण;

	अगर (pcm->dev_class > SNDRV_PCM_CLASS_LAST)
		str = "none";
	अन्यथा
		str = strs[pcm->dev_class];
	वापस प्र_लिखो(buf, "%s\n", str);
पूर्ण

अटल DEVICE_ATTR(pcm_class, 0444, show_pcm_class, शून्य);
अटल काष्ठा attribute *pcm_dev_attrs[] = अणु
	&dev_attr_pcm_class.attr,
	शून्य
पूर्ण;

अटल स्थिर काष्ठा attribute_group pcm_dev_attr_group = अणु
	.attrs	= pcm_dev_attrs,
पूर्ण;

अटल स्थिर काष्ठा attribute_group *pcm_dev_attr_groups[] = अणु
	&pcm_dev_attr_group,
	शून्य
पूर्ण;

अटल पूर्णांक snd_pcm_dev_रेजिस्टर(काष्ठा snd_device *device)
अणु
	पूर्णांक cidx, err;
	काष्ठा snd_pcm_substream *substream;
	काष्ठा snd_pcm *pcm;

	अगर (snd_BUG_ON(!device || !device->device_data))
		वापस -ENXIO;
	pcm = device->device_data;

	mutex_lock(&रेजिस्टर_mutex);
	err = snd_pcm_add(pcm);
	अगर (err)
		जाओ unlock;
	क्रम (cidx = 0; cidx < 2; cidx++) अणु
		पूर्णांक devtype = -1;
		अगर (pcm->streams[cidx].substream == शून्य)
			जारी;
		चयन (cidx) अणु
		हाल SNDRV_PCM_STREAM_PLAYBACK:
			devtype = SNDRV_DEVICE_TYPE_PCM_PLAYBACK;
			अवरोध;
		हाल SNDRV_PCM_STREAM_CAPTURE:
			devtype = SNDRV_DEVICE_TYPE_PCM_CAPTURE;
			अवरोध;
		पूर्ण
		/* रेजिस्टर pcm */
		err = snd_रेजिस्टर_device(devtype, pcm->card, pcm->device,
					  &snd_pcm_f_ops[cidx], pcm,
					  &pcm->streams[cidx].dev);
		अगर (err < 0) अणु
			list_del_init(&pcm->list);
			जाओ unlock;
		पूर्ण

		क्रम (substream = pcm->streams[cidx].substream; substream; substream = substream->next)
			snd_pcm_समयr_init(substream);
	पूर्ण

	pcm_call_notअगरy(pcm, n_रेजिस्टर);

 unlock:
	mutex_unlock(&रेजिस्टर_mutex);
	वापस err;
पूर्ण

अटल पूर्णांक snd_pcm_dev_disconnect(काष्ठा snd_device *device)
अणु
	काष्ठा snd_pcm *pcm = device->device_data;
	काष्ठा snd_pcm_substream *substream;
	पूर्णांक cidx;

	mutex_lock(&रेजिस्टर_mutex);
	mutex_lock(&pcm->खोलो_mutex);
	wake_up(&pcm->खोलो_रुको);
	list_del_init(&pcm->list);

	क्रम_each_pcm_substream(pcm, cidx, substream) अणु
		snd_pcm_stream_lock_irq(substream);
		अगर (substream->runसमय) अणु
			अगर (snd_pcm_running(substream))
				snd_pcm_stop(substream, SNDRV_PCM_STATE_DISCONNECTED);
			/* to be sure, set the state unconditionally */
			substream->runसमय->status->state = SNDRV_PCM_STATE_DISCONNECTED;
			wake_up(&substream->runसमय->sleep);
			wake_up(&substream->runसमय->tsleep);
		पूर्ण
		snd_pcm_stream_unlock_irq(substream);
	पूर्ण

	क्रम_each_pcm_substream(pcm, cidx, substream)
		snd_pcm_sync_stop(substream, false);

	pcm_call_notअगरy(pcm, n_disconnect);
	क्रम (cidx = 0; cidx < 2; cidx++) अणु
		snd_unरेजिस्टर_device(&pcm->streams[cidx].dev);
		मुक्त_chmap(&pcm->streams[cidx]);
	पूर्ण
	mutex_unlock(&pcm->खोलो_mutex);
	mutex_unlock(&रेजिस्टर_mutex);
	वापस 0;
पूर्ण

#अगर IS_ENABLED(CONFIG_SND_PCM_OSS)
/**
 * snd_pcm_notअगरy - Add/हटाओ the notअगरy list
 * @notअगरy: PCM notअगरy list
 * @nमुक्त: 0 = रेजिस्टर, 1 = unरेजिस्टर
 *
 * This adds the given notअगरier to the global list so that the callback is
 * called क्रम each रेजिस्टरed PCM devices.  This exists only क्रम PCM OSS
 * emulation, so far.
 */
पूर्णांक snd_pcm_notअगरy(काष्ठा snd_pcm_notअगरy *notअगरy, पूर्णांक nमुक्त)
अणु
	काष्ठा snd_pcm *pcm;

	अगर (snd_BUG_ON(!notअगरy ||
		       !notअगरy->n_रेजिस्टर ||
		       !notअगरy->n_unरेजिस्टर ||
		       !notअगरy->n_disconnect))
		वापस -EINVAL;
	mutex_lock(&रेजिस्टर_mutex);
	अगर (nमुक्त) अणु
		list_del(&notअगरy->list);
		list_क्रम_each_entry(pcm, &snd_pcm_devices, list)
			notअगरy->n_unरेजिस्टर(pcm);
	पूर्ण अन्यथा अणु
		list_add_tail(&notअगरy->list, &snd_pcm_notअगरy_list);
		list_क्रम_each_entry(pcm, &snd_pcm_devices, list)
			notअगरy->n_रेजिस्टर(pcm);
	पूर्ण
	mutex_unlock(&रेजिस्टर_mutex);
	वापस 0;
पूर्ण
EXPORT_SYMBOL(snd_pcm_notअगरy);
#पूर्ण_अगर /* CONFIG_SND_PCM_OSS */

#अगर_घोषित CONFIG_SND_PROC_FS
/*
 *  Info पूर्णांकerface
 */

अटल व्योम snd_pcm_proc_पढ़ो(काष्ठा snd_info_entry *entry,
			      काष्ठा snd_info_buffer *buffer)
अणु
	काष्ठा snd_pcm *pcm;

	mutex_lock(&रेजिस्टर_mutex);
	list_क्रम_each_entry(pcm, &snd_pcm_devices, list) अणु
		snd_iम_लिखो(buffer, "%02i-%02i: %s : %s",
			    pcm->card->number, pcm->device, pcm->id, pcm->name);
		अगर (pcm->streams[SNDRV_PCM_STREAM_PLAYBACK].substream)
			snd_iम_लिखो(buffer, " : playback %i",
				    pcm->streams[SNDRV_PCM_STREAM_PLAYBACK].substream_count);
		अगर (pcm->streams[SNDRV_PCM_STREAM_CAPTURE].substream)
			snd_iम_लिखो(buffer, " : capture %i",
				    pcm->streams[SNDRV_PCM_STREAM_CAPTURE].substream_count);
		snd_iम_लिखो(buffer, "\n");
	पूर्ण
	mutex_unlock(&रेजिस्टर_mutex);
पूर्ण

अटल काष्ठा snd_info_entry *snd_pcm_proc_entry;

अटल व्योम snd_pcm_proc_init(व्योम)
अणु
	काष्ठा snd_info_entry *entry;

	entry = snd_info_create_module_entry(THIS_MODULE, "pcm", शून्य);
	अगर (entry) अणु
		snd_info_set_text_ops(entry, शून्य, snd_pcm_proc_पढ़ो);
		अगर (snd_info_रेजिस्टर(entry) < 0) अणु
			snd_info_मुक्त_entry(entry);
			entry = शून्य;
		पूर्ण
	पूर्ण
	snd_pcm_proc_entry = entry;
पूर्ण

अटल व्योम snd_pcm_proc_करोne(व्योम)
अणु
	snd_info_मुक्त_entry(snd_pcm_proc_entry);
पूर्ण

#अन्यथा /* !CONFIG_SND_PROC_FS */
#घोषणा snd_pcm_proc_init()
#घोषणा snd_pcm_proc_करोne()
#पूर्ण_अगर /* CONFIG_SND_PROC_FS */


/*
 *  ENTRY functions
 */

अटल पूर्णांक __init alsa_pcm_init(व्योम)
अणु
	snd_ctl_रेजिस्टर_ioctl(snd_pcm_control_ioctl);
	snd_ctl_रेजिस्टर_ioctl_compat(snd_pcm_control_ioctl);
	snd_pcm_proc_init();
	वापस 0;
पूर्ण

अटल व्योम __निकास alsa_pcm_निकास(व्योम)
अणु
	snd_ctl_unरेजिस्टर_ioctl(snd_pcm_control_ioctl);
	snd_ctl_unरेजिस्टर_ioctl_compat(snd_pcm_control_ioctl);
	snd_pcm_proc_करोne();
पूर्ण

module_init(alsa_pcm_init)
module_निकास(alsa_pcm_निकास)
