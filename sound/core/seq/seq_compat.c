<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *   32bit -> 64bit ioctl wrapper क्रम sequencer API
 *   Copyright (c) by Takashi Iwai <tiwai@suse.de>
 */

/* This file included from seq.c */

#समावेश <linux/compat.h>
#समावेश <linux/slab.h>

काष्ठा snd_seq_port_info32 अणु
	काष्ठा snd_seq_addr addr;	/* client/port numbers */
	अक्षर name[64];			/* port name */

	u32 capability;	/* port capability bits */
	u32 type;		/* port type bits */
	s32 midi_channels;		/* channels per MIDI port */
	s32 midi_voices;		/* voices per MIDI port */
	s32 synth_voices;		/* voices per SYNTH port */

	s32 पढ़ो_use;			/* R/O: subscribers क्रम output (from this port) */
	s32 ग_लिखो_use;			/* R/O: subscribers क्रम input (to this port) */

	u32 kernel;			/* reserved क्रम kernel use (must be शून्य) */
	u32 flags;		/* misc. conditioning */
	अचिन्हित अक्षर समय_queue;	/* queue # क्रम बारtamping */
	अक्षर reserved[59];		/* क्रम future use */
पूर्ण;

अटल पूर्णांक snd_seq_call_port_info_ioctl(काष्ठा snd_seq_client *client, अचिन्हित पूर्णांक cmd,
					काष्ठा snd_seq_port_info32 __user *data32)
अणु
	पूर्णांक err = -EFAULT;
	काष्ठा snd_seq_port_info *data;

	data = kदो_स्मृति(माप(*data), GFP_KERNEL);
	अगर (!data)
		वापस -ENOMEM;

	अगर (copy_from_user(data, data32, माप(*data32)) ||
	    get_user(data->flags, &data32->flags) ||
	    get_user(data->समय_queue, &data32->समय_queue))
		जाओ error;
	data->kernel = शून्य;

	err = snd_seq_kernel_client_ctl(client->number, cmd, data);
	अगर (err < 0)
		जाओ error;

	अगर (copy_to_user(data32, data, माप(*data32)) ||
	    put_user(data->flags, &data32->flags) ||
	    put_user(data->समय_queue, &data32->समय_queue))
		err = -EFAULT;

 error:
	kमुक्त(data);
	वापस err;
पूर्ण



/*
 */

क्रमागत अणु
	SNDRV_SEQ_IOCTL_CREATE_PORT32 = _IOWR('S', 0x20, काष्ठा snd_seq_port_info32),
	SNDRV_SEQ_IOCTL_DELETE_PORT32 = _IOW ('S', 0x21, काष्ठा snd_seq_port_info32),
	SNDRV_SEQ_IOCTL_GET_PORT_INFO32 = _IOWR('S', 0x22, काष्ठा snd_seq_port_info32),
	SNDRV_SEQ_IOCTL_SET_PORT_INFO32 = _IOW ('S', 0x23, काष्ठा snd_seq_port_info32),
	SNDRV_SEQ_IOCTL_QUERY_NEXT_PORT32 = _IOWR('S', 0x52, काष्ठा snd_seq_port_info32),
पूर्ण;

अटल दीर्घ snd_seq_ioctl_compat(काष्ठा file *file, अचिन्हित पूर्णांक cmd, अचिन्हित दीर्घ arg)
अणु
	काष्ठा snd_seq_client *client = file->निजी_data;
	व्योम __user *argp = compat_ptr(arg);

	अगर (snd_BUG_ON(!client))
		वापस -ENXIO;

	चयन (cmd) अणु
	हाल SNDRV_SEQ_IOCTL_PVERSION:
	हाल SNDRV_SEQ_IOCTL_CLIENT_ID:
	हाल SNDRV_SEQ_IOCTL_SYSTEM_INFO:
	हाल SNDRV_SEQ_IOCTL_GET_CLIENT_INFO:
	हाल SNDRV_SEQ_IOCTL_SET_CLIENT_INFO:
	हाल SNDRV_SEQ_IOCTL_SUBSCRIBE_PORT:
	हाल SNDRV_SEQ_IOCTL_UNSUBSCRIBE_PORT:
	हाल SNDRV_SEQ_IOCTL_CREATE_QUEUE:
	हाल SNDRV_SEQ_IOCTL_DELETE_QUEUE:
	हाल SNDRV_SEQ_IOCTL_GET_QUEUE_INFO:
	हाल SNDRV_SEQ_IOCTL_SET_QUEUE_INFO:
	हाल SNDRV_SEQ_IOCTL_GET_NAMED_QUEUE:
	हाल SNDRV_SEQ_IOCTL_GET_QUEUE_STATUS:
	हाल SNDRV_SEQ_IOCTL_GET_QUEUE_TEMPO:
	हाल SNDRV_SEQ_IOCTL_SET_QUEUE_TEMPO:
	हाल SNDRV_SEQ_IOCTL_GET_QUEUE_TIMER:
	हाल SNDRV_SEQ_IOCTL_SET_QUEUE_TIMER:
	हाल SNDRV_SEQ_IOCTL_GET_QUEUE_CLIENT:
	हाल SNDRV_SEQ_IOCTL_SET_QUEUE_CLIENT:
	हाल SNDRV_SEQ_IOCTL_GET_CLIENT_POOL:
	हाल SNDRV_SEQ_IOCTL_SET_CLIENT_POOL:
	हाल SNDRV_SEQ_IOCTL_REMOVE_EVENTS:
	हाल SNDRV_SEQ_IOCTL_QUERY_SUBS:
	हाल SNDRV_SEQ_IOCTL_GET_SUBSCRIPTION:
	हाल SNDRV_SEQ_IOCTL_QUERY_NEXT_CLIENT:
	हाल SNDRV_SEQ_IOCTL_RUNNING_MODE:
		वापस snd_seq_ioctl(file, cmd, arg);
	हाल SNDRV_SEQ_IOCTL_CREATE_PORT32:
		वापस snd_seq_call_port_info_ioctl(client, SNDRV_SEQ_IOCTL_CREATE_PORT, argp);
	हाल SNDRV_SEQ_IOCTL_DELETE_PORT32:
		वापस snd_seq_call_port_info_ioctl(client, SNDRV_SEQ_IOCTL_DELETE_PORT, argp);
	हाल SNDRV_SEQ_IOCTL_GET_PORT_INFO32:
		वापस snd_seq_call_port_info_ioctl(client, SNDRV_SEQ_IOCTL_GET_PORT_INFO, argp);
	हाल SNDRV_SEQ_IOCTL_SET_PORT_INFO32:
		वापस snd_seq_call_port_info_ioctl(client, SNDRV_SEQ_IOCTL_SET_PORT_INFO, argp);
	हाल SNDRV_SEQ_IOCTL_QUERY_NEXT_PORT32:
		वापस snd_seq_call_port_info_ioctl(client, SNDRV_SEQ_IOCTL_QUERY_NEXT_PORT, argp);
	पूर्ण
	वापस -ENOIOCTLCMD;
पूर्ण
