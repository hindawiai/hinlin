<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * OSS compatible sequencer driver
 *
 * Timer control routines
 *
 * Copyright (C) 1998,99 Takashi Iwai <tiwai@suse.de>
 */

#समावेश "seq_oss_timer.h"
#समावेश "seq_oss_event.h"
#समावेश <sound/seq_oss_legacy.h>
#समावेश <linux/slab.h>

/*
 */
#घोषणा MIN_OSS_TEMPO		8
#घोषणा MAX_OSS_TEMPO		360
#घोषणा MIN_OSS_TIMEBASE	1
#घोषणा MAX_OSS_TIMEBASE	1000

/*
 */
अटल व्योम calc_alsa_tempo(काष्ठा seq_oss_समयr *समयr);
अटल पूर्णांक send_समयr_event(काष्ठा seq_oss_devinfo *dp, पूर्णांक type, पूर्णांक value);


/*
 * create and रेजिस्टर a new समयr.
 * अगर queue is not started yet, start it.
 */
काष्ठा seq_oss_समयr *
snd_seq_oss_समयr_new(काष्ठा seq_oss_devinfo *dp)
अणु
	काष्ठा seq_oss_समयr *rec;

	rec = kzalloc(माप(*rec), GFP_KERNEL);
	अगर (rec == शून्य)
		वापस शून्य;

	rec->dp = dp;
	rec->cur_tick = 0;
	rec->realसमय = 0;
	rec->running = 0;
	rec->oss_tempo = 60;
	rec->oss_समयbase = 100;
	calc_alsa_tempo(rec);

	वापस rec;
पूर्ण


/*
 * delete समयr.
 * अगर no more समयr exists, stop the queue.
 */
व्योम
snd_seq_oss_समयr_delete(काष्ठा seq_oss_समयr *rec)
अणु
	अगर (rec) अणु
		snd_seq_oss_समयr_stop(rec);
		kमुक्त(rec);
	पूर्ण
पूर्ण


/*
 * process one timing event
 * वापस 1 : event proceseed -- skip this event
 *        0 : not a समयr event -- enqueue this event
 */
पूर्णांक
snd_seq_oss_process_समयr_event(काष्ठा seq_oss_समयr *rec, जोड़ evrec *ev)
अणु
	असलसमय_प्रकार parm = ev->t.समय;

	अगर (ev->t.code == EV_TIMING) अणु
		चयन (ev->t.cmd) अणु
		हाल TMR_WAIT_REL:
			parm += rec->cur_tick;
			rec->realसमय = 0;
			fallthrough;
		हाल TMR_WAIT_ABS:
			अगर (parm == 0) अणु
				rec->realसमय = 1;
			पूर्ण अन्यथा अगर (parm >= rec->cur_tick) अणु
				rec->realसमय = 0;
				rec->cur_tick = parm;
			पूर्ण
			वापस 1;	/* skip this event */
			
		हाल TMR_START:
			snd_seq_oss_समयr_start(rec);
			वापस 1;

		पूर्ण
	पूर्ण अन्यथा अगर (ev->s.code == SEQ_WAIT) अणु
		/* समय = from 1 to 3 bytes */
		parm = (ev->echo >> 8) & 0xffffff;
		अगर (parm > rec->cur_tick) अणु
			/* set next event समय */
			rec->cur_tick = parm;
			rec->realसमय = 0;
		पूर्ण
		वापस 1;
	पूर्ण

	वापस 0;
पूर्ण


/*
 * convert tempo units
 */
अटल व्योम
calc_alsa_tempo(काष्ठा seq_oss_समयr *समयr)
अणु
	समयr->tempo = (60 * 1000000) / समयr->oss_tempo;
	समयr->ppq = समयr->oss_समयbase;
पूर्ण


/*
 * dispatch a समयr event
 */
अटल पूर्णांक
send_समयr_event(काष्ठा seq_oss_devinfo *dp, पूर्णांक type, पूर्णांक value)
अणु
	काष्ठा snd_seq_event ev;

	स_रखो(&ev, 0, माप(ev));
	ev.type = type;
	ev.source.client = dp->cseq;
	ev.source.port = 0;
	ev.dest.client = SNDRV_SEQ_CLIENT_SYSTEM;
	ev.dest.port = SNDRV_SEQ_PORT_SYSTEM_TIMER;
	ev.queue = dp->queue;
	ev.data.queue.queue = dp->queue;
	ev.data.queue.param.value = value;
	वापस snd_seq_kernel_client_dispatch(dp->cseq, &ev, 1, 0);
पूर्ण

/*
 * set queue tempo and start queue
 */
पूर्णांक
snd_seq_oss_समयr_start(काष्ठा seq_oss_समयr *समयr)
अणु
	काष्ठा seq_oss_devinfo *dp = समयr->dp;
	काष्ठा snd_seq_queue_tempo पंचांगprec;

	अगर (समयr->running)
		snd_seq_oss_समयr_stop(समयr);

	स_रखो(&पंचांगprec, 0, माप(पंचांगprec));
	पंचांगprec.queue = dp->queue;
	पंचांगprec.ppq = समयr->ppq;
	पंचांगprec.tempo = समयr->tempo;
	snd_seq_set_queue_tempo(dp->cseq, &पंचांगprec);

	send_समयr_event(dp, SNDRV_SEQ_EVENT_START, 0);
	समयr->running = 1;
	समयr->cur_tick = 0;
	वापस 0;
पूर्ण


/*
 * stop queue
 */
पूर्णांक
snd_seq_oss_समयr_stop(काष्ठा seq_oss_समयr *समयr)
अणु
	अगर (! समयr->running)
		वापस 0;
	send_समयr_event(समयr->dp, SNDRV_SEQ_EVENT_STOP, 0);
	समयr->running = 0;
	वापस 0;
पूर्ण


/*
 * जारी queue
 */
पूर्णांक
snd_seq_oss_समयr_जारी(काष्ठा seq_oss_समयr *समयr)
अणु
	अगर (समयr->running)
		वापस 0;
	send_समयr_event(समयr->dp, SNDRV_SEQ_EVENT_CONTINUE, 0);
	समयr->running = 1;
	वापस 0;
पूर्ण


/*
 * change queue tempo
 */
पूर्णांक
snd_seq_oss_समयr_tempo(काष्ठा seq_oss_समयr *समयr, पूर्णांक value)
अणु
	अगर (value < MIN_OSS_TEMPO)
		value = MIN_OSS_TEMPO;
	अन्यथा अगर (value > MAX_OSS_TEMPO)
		value = MAX_OSS_TEMPO;
	समयr->oss_tempo = value;
	calc_alsa_tempo(समयr);
	अगर (समयr->running)
		send_समयr_event(समयr->dp, SNDRV_SEQ_EVENT_TEMPO, समयr->tempo);
	वापस 0;
पूर्ण


/*
 * ioctls
 */
पूर्णांक
snd_seq_oss_समयr_ioctl(काष्ठा seq_oss_समयr *समयr, अचिन्हित पूर्णांक cmd, पूर्णांक __user *arg)
अणु
	पूर्णांक value;

	अगर (cmd == SNDCTL_SEQ_CTRLRATE) अणु
		/* अगर *arg == 0, just वापस the current rate */
		अगर (get_user(value, arg))
			वापस -EFAULT;
		अगर (value)
			वापस -EINVAL;
		value = ((समयr->oss_tempo * समयr->oss_समयbase) + 30) / 60;
		वापस put_user(value, arg) ? -EFAULT : 0;
	पूर्ण

	अगर (समयr->dp->seq_mode == SNDRV_SEQ_OSS_MODE_SYNTH)
		वापस 0;

	चयन (cmd) अणु
	हाल SNDCTL_TMR_START:
		वापस snd_seq_oss_समयr_start(समयr);
	हाल SNDCTL_TMR_STOP:
		वापस snd_seq_oss_समयr_stop(समयr);
	हाल SNDCTL_TMR_CONTINUE:
		वापस snd_seq_oss_समयr_जारी(समयr);
	हाल SNDCTL_TMR_TEMPO:
		अगर (get_user(value, arg))
			वापस -EFAULT;
		वापस snd_seq_oss_समयr_tempo(समयr, value);
	हाल SNDCTL_TMR_TIMEBASE:
		अगर (get_user(value, arg))
			वापस -EFAULT;
		अगर (value < MIN_OSS_TIMEBASE)
			value = MIN_OSS_TIMEBASE;
		अन्यथा अगर (value > MAX_OSS_TIMEBASE)
			value = MAX_OSS_TIMEBASE;
		समयr->oss_समयbase = value;
		calc_alsa_tempo(समयr);
		वापस 0;

	हाल SNDCTL_TMR_METRONOME:
	हाल SNDCTL_TMR_SELECT:
	हाल SNDCTL_TMR_SOURCE:
		/* not supported */
		वापस 0;
	पूर्ण
	वापस 0;
पूर्ण
