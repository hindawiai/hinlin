<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *   32bit -> 64bit ioctl wrapper क्रम PCM API
 *   Copyright (c) by Takashi Iwai <tiwai@suse.de>
 */

/* This file included from pcm_native.c */

#समावेश <linux/compat.h>
#समावेश <linux/slab.h>

अटल पूर्णांक snd_pcm_ioctl_delay_compat(काष्ठा snd_pcm_substream *substream,
				      s32 __user *src)
अणु
	snd_pcm_sframes_t delay;
	पूर्णांक err;

	err = snd_pcm_delay(substream, &delay);
	अगर (err)
		वापस err;
	अगर (put_user(delay, src))
		वापस -EFAULT;
	वापस 0;
पूर्ण

अटल पूर्णांक snd_pcm_ioctl_शुरुआत_compat(काष्ठा snd_pcm_substream *substream,
				       u32 __user *src)
अणु
	snd_pcm_uframes_t frames;
	पूर्णांक err;

	अगर (get_user(frames, src))
		वापस -EFAULT;
	err = snd_pcm_शुरुआत(substream, frames);
	अगर (put_user(err, src))
		वापस -EFAULT;
	वापस err < 0 ? err : 0;
पूर्ण

अटल पूर्णांक snd_pcm_ioctl_क्रमward_compat(काष्ठा snd_pcm_substream *substream,
				       u32 __user *src)
अणु
	snd_pcm_uframes_t frames;
	पूर्णांक err;

	अगर (get_user(frames, src))
		वापस -EFAULT;
	err = snd_pcm_क्रमward(substream, frames);
	अगर (put_user(err, src))
		वापस -EFAULT;
	वापस err < 0 ? err : 0;
पूर्ण

काष्ठा snd_pcm_hw_params32 अणु
	u32 flags;
	काष्ठा snd_mask masks[SNDRV_PCM_HW_PARAM_LAST_MASK - SNDRV_PCM_HW_PARAM_FIRST_MASK + 1]; /* this must be identical */
	काष्ठा snd_mask mres[5];	/* reserved masks */
	काष्ठा snd_पूर्णांकerval पूर्णांकervals[SNDRV_PCM_HW_PARAM_LAST_INTERVAL - SNDRV_PCM_HW_PARAM_FIRST_INTERVAL + 1];
	काष्ठा snd_पूर्णांकerval ires[9];	/* reserved पूर्णांकervals */
	u32 rmask;
	u32 cmask;
	u32 info;
	u32 msbits;
	u32 rate_num;
	u32 rate_den;
	u32 fअगरo_size;
	अचिन्हित अक्षर reserved[64];
पूर्ण;

काष्ठा snd_pcm_sw_params32 अणु
	s32 tstamp_mode;
	u32 period_step;
	u32 sleep_min;
	u32 avail_min;
	u32 xfer_align;
	u32 start_threshold;
	u32 stop_threshold;
	u32 silence_threshold;
	u32 silence_size;
	u32 boundary;
	u32 proto;
	u32 tstamp_type;
	अचिन्हित अक्षर reserved[56];
पूर्ण;

अटल पूर्णांक snd_pcm_ioctl_sw_params_compat(काष्ठा snd_pcm_substream *substream,
					  काष्ठा snd_pcm_sw_params32 __user *src)
अणु
	काष्ठा snd_pcm_sw_params params;
	snd_pcm_uframes_t boundary;
	पूर्णांक err;

	स_रखो(&params, 0, माप(params));
	अगर (get_user(params.tstamp_mode, &src->tstamp_mode) ||
	    get_user(params.period_step, &src->period_step) ||
	    get_user(params.sleep_min, &src->sleep_min) ||
	    get_user(params.avail_min, &src->avail_min) ||
	    get_user(params.xfer_align, &src->xfer_align) ||
	    get_user(params.start_threshold, &src->start_threshold) ||
	    get_user(params.stop_threshold, &src->stop_threshold) ||
	    get_user(params.silence_threshold, &src->silence_threshold) ||
	    get_user(params.silence_size, &src->silence_size) ||
	    get_user(params.tstamp_type, &src->tstamp_type) ||
	    get_user(params.proto, &src->proto))
		वापस -EFAULT;
	/*
	 * Check silent_size parameter.  Since we have 64bit boundary,
	 * silence_size must be compared with the 32bit boundary.
	 */
	boundary = recalculate_boundary(substream->runसमय);
	अगर (boundary && params.silence_size >= boundary)
		params.silence_size = substream->runसमय->boundary;
	err = snd_pcm_sw_params(substream, &params);
	अगर (err < 0)
		वापस err;
	अगर (boundary && put_user(boundary, &src->boundary))
		वापस -EFAULT;
	वापस err;
पूर्ण

काष्ठा snd_pcm_channel_info32 अणु
	u32 channel;
	u32 offset;
	u32 first;
	u32 step;
पूर्ण;

अटल पूर्णांक snd_pcm_ioctl_channel_info_compat(काष्ठा snd_pcm_substream *substream,
					     काष्ठा snd_pcm_channel_info32 __user *src)
अणु
	काष्ठा snd_pcm_channel_info info;
	पूर्णांक err;

	अगर (get_user(info.channel, &src->channel) ||
	    get_user(info.offset, &src->offset) ||
	    get_user(info.first, &src->first) ||
	    get_user(info.step, &src->step))
		वापस -EFAULT;
	err = snd_pcm_channel_info(substream, &info);
	अगर (err < 0)
		वापस err;
	अगर (put_user(info.channel, &src->channel) ||
	    put_user(info.offset, &src->offset) ||
	    put_user(info.first, &src->first) ||
	    put_user(info.step, &src->step))
		वापस -EFAULT;
	वापस err;
पूर्ण

#अगर_घोषित CONFIG_X86_X32
/* X32 ABI has the same काष्ठा as x86-64 क्रम snd_pcm_channel_info */
अटल पूर्णांक snd_pcm_channel_info_user(काष्ठा snd_pcm_substream *substream,
				     काष्ठा snd_pcm_channel_info __user *src);
#घोषणा snd_pcm_ioctl_channel_info_x32(s, p)	\
	snd_pcm_channel_info_user(s, p)
#पूर्ण_अगर /* CONFIG_X86_X32 */

काष्ठा compat_snd_pcm_status64 अणु
	snd_pcm_state_t state;
	u8 rsvd[4]; /* alignment */
	s64 trigger_tstamp_sec;
	s64 trigger_tstamp_nsec;
	s64 tstamp_sec;
	s64 tstamp_nsec;
	u32 appl_ptr;
	u32 hw_ptr;
	s32 delay;
	u32 avail;
	u32 avail_max;
	u32 overrange;
	snd_pcm_state_t suspended_state;
	u32 audio_tstamp_data;
	s64 audio_tstamp_sec;
	s64 audio_tstamp_nsec;
	s64 driver_tstamp_sec;
	s64 driver_tstamp_nsec;
	u32 audio_tstamp_accuracy;
	अचिन्हित अक्षर reserved[52-4*माप(s64)];
पूर्ण __packed;

अटल पूर्णांक snd_pcm_status_user_compat64(काष्ठा snd_pcm_substream *substream,
					काष्ठा compat_snd_pcm_status64 __user *src,
					bool ext)
अणु
	काष्ठा snd_pcm_status64 status;
	काष्ठा compat_snd_pcm_status64 compat_status64;
	पूर्णांक err;

	स_रखो(&status, 0, माप(status));
	स_रखो(&compat_status64, 0, माप(compat_status64));
	/*
	 * with extension, parameters are पढ़ो/ग_लिखो,
	 * get audio_tstamp_data from user,
	 * ignore rest of status काष्ठाure
	 */
	अगर (ext && get_user(status.audio_tstamp_data,
				(u32 __user *)(&src->audio_tstamp_data)))
		वापस -EFAULT;
	err = snd_pcm_status64(substream, &status);
	अगर (err < 0)
		वापस err;

	अगर (clear_user(src, माप(*src)))
		वापस -EFAULT;

	compat_status64 = (काष्ठा compat_snd_pcm_status64) अणु
		.state = status.state,
		.trigger_tstamp_sec = status.trigger_tstamp_sec,
		.trigger_tstamp_nsec = status.trigger_tstamp_nsec,
		.tstamp_sec = status.tstamp_sec,
		.tstamp_nsec = status.tstamp_nsec,
		.appl_ptr = status.appl_ptr,
		.hw_ptr = status.hw_ptr,
		.delay = status.delay,
		.avail = status.avail,
		.avail_max = status.avail_max,
		.overrange = status.overrange,
		.suspended_state = status.suspended_state,
		.audio_tstamp_data = status.audio_tstamp_data,
		.audio_tstamp_sec = status.audio_tstamp_sec,
		.audio_tstamp_nsec = status.audio_tstamp_nsec,
		.driver_tstamp_sec = status.audio_tstamp_sec,
		.driver_tstamp_nsec = status.audio_tstamp_nsec,
		.audio_tstamp_accuracy = status.audio_tstamp_accuracy,
	पूर्ण;

	अगर (copy_to_user(src, &compat_status64, माप(compat_status64)))
		वापस -EFAULT;

	वापस err;
पूर्ण

/* both क्रम HW_PARAMS and HW_REFINE */
अटल पूर्णांक snd_pcm_ioctl_hw_params_compat(काष्ठा snd_pcm_substream *substream,
					  पूर्णांक refine, 
					  काष्ठा snd_pcm_hw_params32 __user *data32)
अणु
	काष्ठा snd_pcm_hw_params *data;
	काष्ठा snd_pcm_runसमय *runसमय;
	पूर्णांक err;

	अगर (! (runसमय = substream->runसमय))
		वापस -ENOTTY;

	data = kदो_स्मृति(माप(*data), GFP_KERNEL);
	अगर (!data)
		वापस -ENOMEM;

	/* only fअगरo_size (RO from userspace) is dअगरferent, so just copy all */
	अगर (copy_from_user(data, data32, माप(*data32))) अणु
		err = -EFAULT;
		जाओ error;
	पूर्ण

	अगर (refine)
		err = snd_pcm_hw_refine(substream, data);
	अन्यथा
		err = snd_pcm_hw_params(substream, data);
	अगर (err < 0)
		जाओ error;
	अगर (copy_to_user(data32, data, माप(*data32)) ||
	    put_user(data->fअगरo_size, &data32->fअगरo_size)) अणु
		err = -EFAULT;
		जाओ error;
	पूर्ण

	अगर (! refine) अणु
		अचिन्हित पूर्णांक new_boundary = recalculate_boundary(runसमय);
		अगर (new_boundary)
			runसमय->boundary = new_boundary;
	पूर्ण
 error:
	kमुक्त(data);
	वापस err;
पूर्ण


/*
 */
काष्ठा snd_xferi32 अणु
	s32 result;
	u32 buf;
	u32 frames;
पूर्ण;

अटल पूर्णांक snd_pcm_ioctl_xferi_compat(काष्ठा snd_pcm_substream *substream,
				      पूर्णांक dir, काष्ठा snd_xferi32 __user *data32)
अणु
	compat_caddr_t buf;
	u32 frames;
	पूर्णांक err;

	अगर (! substream->runसमय)
		वापस -ENOTTY;
	अगर (substream->stream != dir)
		वापस -EINVAL;
	अगर (substream->runसमय->status->state == SNDRV_PCM_STATE_OPEN)
		वापस -EBADFD;

	अगर (get_user(buf, &data32->buf) ||
	    get_user(frames, &data32->frames))
		वापस -EFAULT;

	अगर (dir == SNDRV_PCM_STREAM_PLAYBACK)
		err = snd_pcm_lib_ग_लिखो(substream, compat_ptr(buf), frames);
	अन्यथा
		err = snd_pcm_lib_पढ़ो(substream, compat_ptr(buf), frames);
	अगर (err < 0)
		वापस err;
	/* copy the result */
	अगर (put_user(err, &data32->result))
		वापस -EFAULT;
	वापस 0;
पूर्ण


/* snd_xfern needs remapping of bufs */
काष्ठा snd_xfern32 अणु
	s32 result;
	u32 bufs;  /* this is व्योम **; */
	u32 frames;
पूर्ण;

/*
 * xfern ioctl nees to copy (up to) 128 poपूर्णांकers on stack.
 * although we may pass the copied poपूर्णांकers through f_op->ioctl, but the ioctl
 * handler there expands again the same 128 poपूर्णांकers on stack, so it is better
 * to handle the function (calling pcm_पढ़ोv/ग_लिखोv) directly in this handler.
 */
अटल पूर्णांक snd_pcm_ioctl_xfern_compat(काष्ठा snd_pcm_substream *substream,
				      पूर्णांक dir, काष्ठा snd_xfern32 __user *data32)
अणु
	compat_caddr_t buf;
	compat_caddr_t __user *bufptr;
	u32 frames;
	व्योम __user **bufs;
	पूर्णांक err, ch, i;

	अगर (! substream->runसमय)
		वापस -ENOTTY;
	अगर (substream->stream != dir)
		वापस -EINVAL;
	अगर (substream->runसमय->status->state == SNDRV_PCM_STATE_OPEN)
		वापस -EBADFD;

	अगर ((ch = substream->runसमय->channels) > 128)
		वापस -EINVAL;
	अगर (get_user(buf, &data32->bufs) ||
	    get_user(frames, &data32->frames))
		वापस -EFAULT;
	bufptr = compat_ptr(buf);
	bufs = kदो_स्मृति_array(ch, माप(व्योम __user *), GFP_KERNEL);
	अगर (bufs == शून्य)
		वापस -ENOMEM;
	क्रम (i = 0; i < ch; i++) अणु
		u32 ptr;
		अगर (get_user(ptr, bufptr)) अणु
			kमुक्त(bufs);
			वापस -EFAULT;
		पूर्ण
		bufs[i] = compat_ptr(ptr);
		bufptr++;
	पूर्ण
	अगर (dir == SNDRV_PCM_STREAM_PLAYBACK)
		err = snd_pcm_lib_ग_लिखोv(substream, bufs, frames);
	अन्यथा
		err = snd_pcm_lib_पढ़ोv(substream, bufs, frames);
	अगर (err >= 0) अणु
		अगर (put_user(err, &data32->result))
			err = -EFAULT;
	पूर्ण
	kमुक्त(bufs);
	वापस err;
पूर्ण

#अगर_घोषित CONFIG_X86_X32
/* X32 ABI has 64bit बारpec and 64bit alignment */
काष्ठा snd_pcm_mmap_status_x32 अणु
	snd_pcm_state_t state;
	s32 pad1;
	u32 hw_ptr;
	u32 pad2; /* alignment */
	s64 tstamp_sec;
	s64 tstamp_nsec;
	snd_pcm_state_t suspended_state;
	s32 pad3;
	s64 audio_tstamp_sec;
	s64 audio_tstamp_nsec;
पूर्ण __packed;

काष्ठा snd_pcm_mmap_control_x32 अणु
	u32 appl_ptr;
	u32 avail_min;
पूर्ण;

काष्ठा snd_pcm_sync_ptr_x32 अणु
	u32 flags;
	u32 rsvd; /* alignment */
	जोड़ अणु
		काष्ठा snd_pcm_mmap_status_x32 status;
		अचिन्हित अक्षर reserved[64];
	पूर्ण s;
	जोड़ अणु
		काष्ठा snd_pcm_mmap_control_x32 control;
		अचिन्हित अक्षर reserved[64];
	पूर्ण c;
पूर्ण __packed;

अटल पूर्णांक snd_pcm_ioctl_sync_ptr_x32(काष्ठा snd_pcm_substream *substream,
				      काष्ठा snd_pcm_sync_ptr_x32 __user *src)
अणु
	काष्ठा snd_pcm_runसमय *runसमय = substream->runसमय;
	अस्थिर काष्ठा snd_pcm_mmap_status *status;
	अस्थिर काष्ठा snd_pcm_mmap_control *control;
	u32 sflags;
	काष्ठा snd_pcm_mmap_control scontrol;
	काष्ठा snd_pcm_mmap_status sstatus;
	snd_pcm_uframes_t boundary;
	पूर्णांक err;

	अगर (snd_BUG_ON(!runसमय))
		वापस -EINVAL;

	अगर (get_user(sflags, &src->flags) ||
	    get_user(scontrol.appl_ptr, &src->c.control.appl_ptr) ||
	    get_user(scontrol.avail_min, &src->c.control.avail_min))
		वापस -EFAULT;
	अगर (sflags & SNDRV_PCM_SYNC_PTR_HWSYNC) अणु
		err = snd_pcm_hwsync(substream);
		अगर (err < 0)
			वापस err;
	पूर्ण
	status = runसमय->status;
	control = runसमय->control;
	boundary = recalculate_boundary(runसमय);
	अगर (!boundary)
		boundary = 0x7fffffff;
	snd_pcm_stream_lock_irq(substream);
	/* FIXME: we should consider the boundary क्रम the sync from app */
	अगर (!(sflags & SNDRV_PCM_SYNC_PTR_APPL))
		control->appl_ptr = scontrol.appl_ptr;
	अन्यथा
		scontrol.appl_ptr = control->appl_ptr % boundary;
	अगर (!(sflags & SNDRV_PCM_SYNC_PTR_AVAIL_MIN))
		control->avail_min = scontrol.avail_min;
	अन्यथा
		scontrol.avail_min = control->avail_min;
	sstatus.state = status->state;
	sstatus.hw_ptr = status->hw_ptr % boundary;
	sstatus.tstamp = status->tstamp;
	sstatus.suspended_state = status->suspended_state;
	sstatus.audio_tstamp = status->audio_tstamp;
	snd_pcm_stream_unlock_irq(substream);
	अगर (put_user(sstatus.state, &src->s.status.state) ||
	    put_user(sstatus.hw_ptr, &src->s.status.hw_ptr) ||
	    put_user(sstatus.tstamp.tv_sec, &src->s.status.tstamp_sec) ||
	    put_user(sstatus.tstamp.tv_nsec, &src->s.status.tstamp_nsec) ||
	    put_user(sstatus.suspended_state, &src->s.status.suspended_state) ||
	    put_user(sstatus.audio_tstamp.tv_sec, &src->s.status.audio_tstamp_sec) ||
	    put_user(sstatus.audio_tstamp.tv_nsec, &src->s.status.audio_tstamp_nsec) ||
	    put_user(scontrol.appl_ptr, &src->c.control.appl_ptr) ||
	    put_user(scontrol.avail_min, &src->c.control.avail_min))
		वापस -EFAULT;

	वापस 0;
पूर्ण
#पूर्ण_अगर /* CONFIG_X86_X32 */

/*
 */
क्रमागत अणु
	SNDRV_PCM_IOCTL_HW_REFINE32 = _IOWR('A', 0x10, काष्ठा snd_pcm_hw_params32),
	SNDRV_PCM_IOCTL_HW_PARAMS32 = _IOWR('A', 0x11, काष्ठा snd_pcm_hw_params32),
	SNDRV_PCM_IOCTL_SW_PARAMS32 = _IOWR('A', 0x13, काष्ठा snd_pcm_sw_params32),
	SNDRV_PCM_IOCTL_STATUS_COMPAT32 = _IOR('A', 0x20, काष्ठा snd_pcm_status32),
	SNDRV_PCM_IOCTL_STATUS_EXT_COMPAT32 = _IOWR('A', 0x24, काष्ठा snd_pcm_status32),
	SNDRV_PCM_IOCTL_DELAY32 = _IOR('A', 0x21, s32),
	SNDRV_PCM_IOCTL_CHANNEL_INFO32 = _IOR('A', 0x32, काष्ठा snd_pcm_channel_info32),
	SNDRV_PCM_IOCTL_REWIND32 = _IOW('A', 0x46, u32),
	SNDRV_PCM_IOCTL_FORWARD32 = _IOW('A', 0x49, u32),
	SNDRV_PCM_IOCTL_WRITEI_FRAMES32 = _IOW('A', 0x50, काष्ठा snd_xferi32),
	SNDRV_PCM_IOCTL_READI_FRAMES32 = _IOR('A', 0x51, काष्ठा snd_xferi32),
	SNDRV_PCM_IOCTL_WRITEN_FRAMES32 = _IOW('A', 0x52, काष्ठा snd_xfern32),
	SNDRV_PCM_IOCTL_READN_FRAMES32 = _IOR('A', 0x53, काष्ठा snd_xfern32),
	SNDRV_PCM_IOCTL_STATUS_COMPAT64 = _IOR('A', 0x20, काष्ठा compat_snd_pcm_status64),
	SNDRV_PCM_IOCTL_STATUS_EXT_COMPAT64 = _IOWR('A', 0x24, काष्ठा compat_snd_pcm_status64),
#अगर_घोषित CONFIG_X86_X32
	SNDRV_PCM_IOCTL_CHANNEL_INFO_X32 = _IOR('A', 0x32, काष्ठा snd_pcm_channel_info),
	SNDRV_PCM_IOCTL_SYNC_PTR_X32 = _IOWR('A', 0x23, काष्ठा snd_pcm_sync_ptr_x32),
#पूर्ण_अगर /* CONFIG_X86_X32 */
पूर्ण;

अटल दीर्घ snd_pcm_ioctl_compat(काष्ठा file *file, अचिन्हित पूर्णांक cmd, अचिन्हित दीर्घ arg)
अणु
	काष्ठा snd_pcm_file *pcm_file;
	काष्ठा snd_pcm_substream *substream;
	व्योम __user *argp = compat_ptr(arg);

	pcm_file = file->निजी_data;
	अगर (! pcm_file)
		वापस -ENOTTY;
	substream = pcm_file->substream;
	अगर (! substream)
		वापस -ENOTTY;

	/*
	 * When PCM is used on 32bit mode, we need to disable
	 * mmap of the old PCM status/control records because
	 * of the size incompatibility.
	 */
	pcm_file->no_compat_mmap = 1;

	चयन (cmd) अणु
	हाल SNDRV_PCM_IOCTL_PVERSION:
	हाल SNDRV_PCM_IOCTL_INFO:
	हाल SNDRV_PCM_IOCTL_TSTAMP:
	हाल SNDRV_PCM_IOCTL_TTSTAMP:
	हाल SNDRV_PCM_IOCTL_USER_PVERSION:
	हाल SNDRV_PCM_IOCTL_HWSYNC:
	हाल SNDRV_PCM_IOCTL_PREPARE:
	हाल SNDRV_PCM_IOCTL_RESET:
	हाल SNDRV_PCM_IOCTL_START:
	हाल SNDRV_PCM_IOCTL_DROP:
	हाल SNDRV_PCM_IOCTL_DRAIN:
	हाल SNDRV_PCM_IOCTL_PAUSE:
	हाल SNDRV_PCM_IOCTL_HW_FREE:
	हाल SNDRV_PCM_IOCTL_RESUME:
	हाल SNDRV_PCM_IOCTL_XRUN:
	हाल SNDRV_PCM_IOCTL_LINK:
	हाल SNDRV_PCM_IOCTL_UNLINK:
	हाल __SNDRV_PCM_IOCTL_SYNC_PTR32:
		वापस snd_pcm_common_ioctl(file, substream, cmd, argp);
	हाल __SNDRV_PCM_IOCTL_SYNC_PTR64:
#अगर_घोषित CONFIG_X86_X32
		अगर (in_x32_syscall())
			वापस snd_pcm_ioctl_sync_ptr_x32(substream, argp);
#पूर्ण_अगर /* CONFIG_X86_X32 */
		वापस snd_pcm_common_ioctl(file, substream, cmd, argp);
	हाल SNDRV_PCM_IOCTL_HW_REFINE32:
		वापस snd_pcm_ioctl_hw_params_compat(substream, 1, argp);
	हाल SNDRV_PCM_IOCTL_HW_PARAMS32:
		वापस snd_pcm_ioctl_hw_params_compat(substream, 0, argp);
	हाल SNDRV_PCM_IOCTL_SW_PARAMS32:
		वापस snd_pcm_ioctl_sw_params_compat(substream, argp);
	हाल SNDRV_PCM_IOCTL_STATUS_COMPAT32:
		वापस snd_pcm_status_user32(substream, argp, false);
	हाल SNDRV_PCM_IOCTL_STATUS_EXT_COMPAT32:
		वापस snd_pcm_status_user32(substream, argp, true);
	हाल SNDRV_PCM_IOCTL_CHANNEL_INFO32:
		वापस snd_pcm_ioctl_channel_info_compat(substream, argp);
	हाल SNDRV_PCM_IOCTL_WRITEI_FRAMES32:
		वापस snd_pcm_ioctl_xferi_compat(substream, SNDRV_PCM_STREAM_PLAYBACK, argp);
	हाल SNDRV_PCM_IOCTL_READI_FRAMES32:
		वापस snd_pcm_ioctl_xferi_compat(substream, SNDRV_PCM_STREAM_CAPTURE, argp);
	हाल SNDRV_PCM_IOCTL_WRITEN_FRAMES32:
		वापस snd_pcm_ioctl_xfern_compat(substream, SNDRV_PCM_STREAM_PLAYBACK, argp);
	हाल SNDRV_PCM_IOCTL_READN_FRAMES32:
		वापस snd_pcm_ioctl_xfern_compat(substream, SNDRV_PCM_STREAM_CAPTURE, argp);
	हाल SNDRV_PCM_IOCTL_DELAY32:
		वापस snd_pcm_ioctl_delay_compat(substream, argp);
	हाल SNDRV_PCM_IOCTL_REWIND32:
		वापस snd_pcm_ioctl_शुरुआत_compat(substream, argp);
	हाल SNDRV_PCM_IOCTL_FORWARD32:
		वापस snd_pcm_ioctl_क्रमward_compat(substream, argp);
	हाल SNDRV_PCM_IOCTL_STATUS_COMPAT64:
		वापस snd_pcm_status_user_compat64(substream, argp, false);
	हाल SNDRV_PCM_IOCTL_STATUS_EXT_COMPAT64:
		वापस snd_pcm_status_user_compat64(substream, argp, true);
#अगर_घोषित CONFIG_X86_X32
	हाल SNDRV_PCM_IOCTL_CHANNEL_INFO_X32:
		वापस snd_pcm_ioctl_channel_info_x32(substream, argp);
#पूर्ण_अगर /* CONFIG_X86_X32 */
	पूर्ण

	वापस -ENOIOCTLCMD;
पूर्ण
