<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *   32bit -> 64bit ioctl wrapper क्रम raw MIDI API
 *   Copyright (c) by Takashi Iwai <tiwai@suse.de>
 */

/* This file included from rawmidi.c */

#समावेश <linux/compat.h>

काष्ठा snd_rawmidi_params32 अणु
	s32 stream;
	u32 buffer_size;
	u32 avail_min;
	अचिन्हित पूर्णांक no_active_sensing; /* aव्योम bit-field */
	अचिन्हित अक्षर reserved[16];
पूर्ण __attribute__((packed));

अटल पूर्णांक snd_rawmidi_ioctl_params_compat(काष्ठा snd_rawmidi_file *rfile,
					   काष्ठा snd_rawmidi_params32 __user *src)
अणु
	काष्ठा snd_rawmidi_params params;
	अचिन्हित पूर्णांक val;

	अगर (get_user(params.stream, &src->stream) ||
	    get_user(params.buffer_size, &src->buffer_size) ||
	    get_user(params.avail_min, &src->avail_min) ||
	    get_user(val, &src->no_active_sensing))
		वापस -EFAULT;
	params.no_active_sensing = val;
	चयन (params.stream) अणु
	हाल SNDRV_RAWMIDI_STREAM_OUTPUT:
		अगर (!rfile->output)
			वापस -EINVAL;
		वापस snd_rawmidi_output_params(rfile->output, &params);
	हाल SNDRV_RAWMIDI_STREAM_INPUT:
		अगर (!rfile->input)
			वापस -EINVAL;
		वापस snd_rawmidi_input_params(rfile->input, &params);
	पूर्ण
	वापस -EINVAL;
पूर्ण

काष्ठा compat_snd_rawmidi_status64 अणु
	s32 stream;
	u8 rsvd[4]; /* alignment */
	s64 tstamp_sec;
	s64 tstamp_nsec;
	u32 avail;
	u32 xruns;
	अचिन्हित अक्षर reserved[16];
पूर्ण __attribute__((packed));

अटल पूर्णांक snd_rawmidi_ioctl_status_compat64(काष्ठा snd_rawmidi_file *rfile,
					     काष्ठा compat_snd_rawmidi_status64 __user *src)
अणु
	पूर्णांक err;
	काष्ठा snd_rawmidi_status64 status;
	काष्ठा compat_snd_rawmidi_status64 compat_status;

	अगर (get_user(status.stream, &src->stream))
		वापस -EFAULT;

	चयन (status.stream) अणु
	हाल SNDRV_RAWMIDI_STREAM_OUTPUT:
		अगर (!rfile->output)
			वापस -EINVAL;
		err = snd_rawmidi_output_status(rfile->output, &status);
		अवरोध;
	हाल SNDRV_RAWMIDI_STREAM_INPUT:
		अगर (!rfile->input)
			वापस -EINVAL;
		err = snd_rawmidi_input_status(rfile->input, &status);
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण
	अगर (err < 0)
		वापस err;

	compat_status = (काष्ठा compat_snd_rawmidi_status64) अणु
		.stream = status.stream,
		.tstamp_sec = status.tstamp_sec,
		.tstamp_nsec = status.tstamp_nsec,
		.avail = status.avail,
		.xruns = status.xruns,
	पूर्ण;

	अगर (copy_to_user(src, &compat_status, माप(*src)))
		वापस -EFAULT;

	वापस 0;
पूर्ण

क्रमागत अणु
	SNDRV_RAWMIDI_IOCTL_PARAMS32 = _IOWR('W', 0x10, काष्ठा snd_rawmidi_params32),
	SNDRV_RAWMIDI_IOCTL_STATUS_COMPAT32 = _IOWR('W', 0x20, काष्ठा snd_rawmidi_status32),
	SNDRV_RAWMIDI_IOCTL_STATUS_COMPAT64 = _IOWR('W', 0x20, काष्ठा compat_snd_rawmidi_status64),
पूर्ण;

अटल दीर्घ snd_rawmidi_ioctl_compat(काष्ठा file *file, अचिन्हित पूर्णांक cmd, अचिन्हित दीर्घ arg)
अणु
	काष्ठा snd_rawmidi_file *rfile;
	व्योम __user *argp = compat_ptr(arg);

	rfile = file->निजी_data;
	चयन (cmd) अणु
	हाल SNDRV_RAWMIDI_IOCTL_PVERSION:
	हाल SNDRV_RAWMIDI_IOCTL_INFO:
	हाल SNDRV_RAWMIDI_IOCTL_DROP:
	हाल SNDRV_RAWMIDI_IOCTL_DRAIN:
		वापस snd_rawmidi_ioctl(file, cmd, (अचिन्हित दीर्घ)argp);
	हाल SNDRV_RAWMIDI_IOCTL_PARAMS32:
		वापस snd_rawmidi_ioctl_params_compat(rfile, argp);
	हाल SNDRV_RAWMIDI_IOCTL_STATUS_COMPAT32:
		वापस snd_rawmidi_ioctl_status32(rfile, argp);
	हाल SNDRV_RAWMIDI_IOCTL_STATUS_COMPAT64:
		वापस snd_rawmidi_ioctl_status_compat64(rfile, argp);
	पूर्ण
	वापस -ENOIOCTLCMD;
पूर्ण
