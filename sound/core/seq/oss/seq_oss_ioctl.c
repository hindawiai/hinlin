<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * OSS compatible sequencer driver
 *
 * OSS compatible i/o control
 *
 * Copyright (C) 1998,99 Takashi Iwai <tiwai@suse.de>
 */

#समावेश "seq_oss_device.h"
#समावेश "seq_oss_readq.h"
#समावेश "seq_oss_writeq.h"
#समावेश "seq_oss_timer.h"
#समावेश "seq_oss_synth.h"
#समावेश "seq_oss_midi.h"
#समावेश "seq_oss_event.h"

अटल पूर्णांक snd_seq_oss_synth_info_user(काष्ठा seq_oss_devinfo *dp, व्योम __user *arg)
अणु
	काष्ठा synth_info info;

	अगर (copy_from_user(&info, arg, माप(info)))
		वापस -EFAULT;
	अगर (snd_seq_oss_synth_make_info(dp, info.device, &info) < 0)
		वापस -EINVAL;
	अगर (copy_to_user(arg, &info, माप(info)))
		वापस -EFAULT;
	वापस 0;
पूर्ण

अटल पूर्णांक snd_seq_oss_midi_info_user(काष्ठा seq_oss_devinfo *dp, व्योम __user *arg)
अणु
	काष्ठा midi_info info;

	अगर (copy_from_user(&info, arg, माप(info)))
		वापस -EFAULT;
	अगर (snd_seq_oss_midi_make_info(dp, info.device, &info) < 0)
		वापस -EINVAL;
	अगर (copy_to_user(arg, &info, माप(info)))
		वापस -EFAULT;
	वापस 0;
पूर्ण

अटल पूर्णांक snd_seq_oss_oob_user(काष्ठा seq_oss_devinfo *dp, व्योम __user *arg)
अणु
	अचिन्हित अक्षर ev[8];
	काष्ठा snd_seq_event पंचांगpev;

	अगर (copy_from_user(ev, arg, 8))
		वापस -EFAULT;
	स_रखो(&पंचांगpev, 0, माप(पंचांगpev));
	snd_seq_oss_fill_addr(dp, &पंचांगpev, dp->addr.client, dp->addr.port);
	पंचांगpev.समय.tick = 0;
	अगर (! snd_seq_oss_process_event(dp, (जोड़ evrec *)ev, &पंचांगpev)) अणु
		snd_seq_oss_dispatch(dp, &पंचांगpev, 0, 0);
	पूर्ण
	वापस 0;
पूर्ण

पूर्णांक
snd_seq_oss_ioctl(काष्ठा seq_oss_devinfo *dp, अचिन्हित पूर्णांक cmd, अचिन्हित दीर्घ carg)
अणु
	पूर्णांक dev, val;
	व्योम __user *arg = (व्योम __user *)carg;
	पूर्णांक __user *p = arg;

	चयन (cmd) अणु
	हाल SNDCTL_TMR_TIMEBASE:
	हाल SNDCTL_TMR_TEMPO:
	हाल SNDCTL_TMR_START:
	हाल SNDCTL_TMR_STOP:
	हाल SNDCTL_TMR_CONTINUE:
	हाल SNDCTL_TMR_METRONOME:
	हाल SNDCTL_TMR_SOURCE:
	हाल SNDCTL_TMR_SELECT:
	हाल SNDCTL_SEQ_CTRLRATE:
		वापस snd_seq_oss_समयr_ioctl(dp->समयr, cmd, arg);

	हाल SNDCTL_SEQ_PANIC:
		snd_seq_oss_reset(dp);
		वापस -EINVAL;

	हाल SNDCTL_SEQ_SYNC:
		अगर (! is_ग_लिखो_mode(dp->file_mode) || dp->ग_लिखोq == शून्य)
			वापस 0;
		जबतक (snd_seq_oss_ग_लिखोq_sync(dp->ग_लिखोq))
			;
		अगर (संकेत_pending(current))
			वापस -ERESTARTSYS;
		वापस 0;

	हाल SNDCTL_SEQ_RESET:
		snd_seq_oss_reset(dp);
		वापस 0;

	हाल SNDCTL_SEQ_TESTMIDI:
		अगर (get_user(dev, p))
			वापस -EFAULT;
		वापस snd_seq_oss_midi_खोलो(dp, dev, dp->file_mode);

	हाल SNDCTL_SEQ_GETINCOUNT:
		अगर (dp->पढ़ोq == शून्य || ! is_पढ़ो_mode(dp->file_mode))
			वापस 0;
		वापस put_user(dp->पढ़ोq->qlen, p) ? -EFAULT : 0;

	हाल SNDCTL_SEQ_GETOUTCOUNT:
		अगर (! is_ग_लिखो_mode(dp->file_mode) || dp->ग_लिखोq == शून्य)
			वापस 0;
		वापस put_user(snd_seq_oss_ग_लिखोq_get_मुक्त_size(dp->ग_लिखोq), p) ? -EFAULT : 0;

	हाल SNDCTL_SEQ_GETTIME:
		वापस put_user(snd_seq_oss_समयr_cur_tick(dp->समयr), p) ? -EFAULT : 0;

	हाल SNDCTL_SEQ_RESETSAMPLES:
		अगर (get_user(dev, p))
			वापस -EFAULT;
		वापस snd_seq_oss_synth_ioctl(dp, dev, cmd, carg);

	हाल SNDCTL_SEQ_NRSYNTHS:
		वापस put_user(dp->max_synthdev, p) ? -EFAULT : 0;

	हाल SNDCTL_SEQ_NRMIDIS:
		वापस put_user(dp->max_mididev, p) ? -EFAULT : 0;

	हाल SNDCTL_SYNTH_MEMAVL:
		अगर (get_user(dev, p))
			वापस -EFAULT;
		val = snd_seq_oss_synth_ioctl(dp, dev, cmd, carg);
		वापस put_user(val, p) ? -EFAULT : 0;

	हाल SNDCTL_FM_4OP_ENABLE:
		अगर (get_user(dev, p))
			वापस -EFAULT;
		snd_seq_oss_synth_ioctl(dp, dev, cmd, carg);
		वापस 0;

	हाल SNDCTL_SYNTH_INFO:
	हाल SNDCTL_SYNTH_ID:
		वापस snd_seq_oss_synth_info_user(dp, arg);

	हाल SNDCTL_SEQ_OUTOFBAND:
		वापस snd_seq_oss_oob_user(dp, arg);

	हाल SNDCTL_MIDI_INFO:
		वापस snd_seq_oss_midi_info_user(dp, arg);

	हाल SNDCTL_SEQ_THRESHOLD:
		अगर (! is_ग_लिखो_mode(dp->file_mode))
			वापस 0;
		अगर (get_user(val, p))
			वापस -EFAULT;
		अगर (val < 1)
			val = 1;
		अगर (val >= dp->ग_लिखोq->maxlen)
			val = dp->ग_लिखोq->maxlen - 1;
		snd_seq_oss_ग_लिखोq_set_output(dp->ग_लिखोq, val);
		वापस 0;

	हाल SNDCTL_MIDI_PRETIME:
		अगर (dp->पढ़ोq == शून्य || !is_पढ़ो_mode(dp->file_mode))
			वापस 0;
		अगर (get_user(val, p))
			वापस -EFAULT;
		अगर (val <= 0)
			val = -1;
		अन्यथा
			val = (HZ * val) / 10;
		dp->पढ़ोq->pre_event_समयout = val;
		वापस put_user(val, p) ? -EFAULT : 0;

	शेष:
		अगर (! is_ग_लिखो_mode(dp->file_mode))
			वापस -EIO;
		वापस snd_seq_oss_synth_ioctl(dp, 0, cmd, carg);
	पूर्ण
	वापस 0;
पूर्ण

