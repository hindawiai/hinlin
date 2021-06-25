<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * OSS compatible sequencer driver
 *
 * seq_oss_ग_लिखोq.c - ग_लिखो queue and sync
 *
 * Copyright (C) 1998,99 Takashi Iwai <tiwai@suse.de>
 */

#समावेश "seq_oss_writeq.h"
#समावेश "seq_oss_event.h"
#समावेश "seq_oss_timer.h"
#समावेश <sound/seq_oss_legacy.h>
#समावेश "../seq_lock.h"
#समावेश "../seq_clientmgr.h"
#समावेश <linux/रुको.h>
#समावेश <linux/slab.h>
#समावेश <linux/sched/संकेत.स>


/*
 * create a ग_लिखो queue record
 */
काष्ठा seq_oss_ग_लिखोq *
snd_seq_oss_ग_लिखोq_new(काष्ठा seq_oss_devinfo *dp, पूर्णांक maxlen)
अणु
	काष्ठा seq_oss_ग_लिखोq *q;
	काष्ठा snd_seq_client_pool pool;

	अगर ((q = kzalloc(माप(*q), GFP_KERNEL)) == शून्य)
		वापस शून्य;
	q->dp = dp;
	q->maxlen = maxlen;
	spin_lock_init(&q->sync_lock);
	q->sync_event_put = 0;
	q->sync_समय = 0;
	init_रुकोqueue_head(&q->sync_sleep);

	स_रखो(&pool, 0, माप(pool));
	pool.client = dp->cseq;
	pool.output_pool = maxlen;
	pool.output_room = maxlen / 2;

	snd_seq_oss_control(dp, SNDRV_SEQ_IOCTL_SET_CLIENT_POOL, &pool);

	वापस q;
पूर्ण

/*
 * delete the ग_लिखो queue
 */
व्योम
snd_seq_oss_ग_लिखोq_delete(काष्ठा seq_oss_ग_लिखोq *q)
अणु
	अगर (q) अणु
		snd_seq_oss_ग_लिखोq_clear(q);	/* to be sure */
		kमुक्त(q);
	पूर्ण
पूर्ण


/*
 * reset the ग_लिखो queue
 */
व्योम
snd_seq_oss_ग_लिखोq_clear(काष्ठा seq_oss_ग_लिखोq *q)
अणु
	काष्ठा snd_seq_हटाओ_events reset;

	स_रखो(&reset, 0, माप(reset));
	reset.हटाओ_mode = SNDRV_SEQ_REMOVE_OUTPUT; /* हटाओ all */
	snd_seq_oss_control(q->dp, SNDRV_SEQ_IOCTL_REMOVE_EVENTS, &reset);

	/* wake up sleepers अगर any */
	snd_seq_oss_ग_लिखोq_wakeup(q, 0);
पूर्ण

/*
 * रुको until the ग_लिखो buffer has enough room
 */
पूर्णांक
snd_seq_oss_ग_लिखोq_sync(काष्ठा seq_oss_ग_लिखोq *q)
अणु
	काष्ठा seq_oss_devinfo *dp = q->dp;
	असलसमय_प्रकार समय;

	समय = snd_seq_oss_समयr_cur_tick(dp->समयr);
	अगर (q->sync_समय >= समय)
		वापस 0; /* alपढ़ोy finished */

	अगर (! q->sync_event_put) अणु
		काष्ठा snd_seq_event ev;
		जोड़ evrec *rec;

		/* put echoback event */
		स_रखो(&ev, 0, माप(ev));
		ev.flags = 0;
		ev.type = SNDRV_SEQ_EVENT_ECHO;
		ev.समय.tick = समय;
		/* echo back to itself */
		snd_seq_oss_fill_addr(dp, &ev, dp->addr.client, dp->addr.port);
		rec = (जोड़ evrec *)&ev.data;
		rec->t.code = SEQ_SYNCTIMER;
		rec->t.समय = समय;
		q->sync_event_put = 1;
		snd_seq_kernel_client_enqueue(dp->cseq, &ev, शून्य, true);
	पूर्ण

	रुको_event_पूर्णांकerruptible_समयout(q->sync_sleep, ! q->sync_event_put, HZ);
	अगर (संकेत_pending(current))
		/* पूर्णांकerrupted - वापस 0 to finish sync */
		q->sync_event_put = 0;
	अगर (! q->sync_event_put || q->sync_समय >= समय)
		वापस 0;
	वापस 1;
पूर्ण

/*
 * wake up sync - echo event was catched
 */
व्योम
snd_seq_oss_ग_लिखोq_wakeup(काष्ठा seq_oss_ग_लिखोq *q, असलसमय_प्रकार समय)
अणु
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&q->sync_lock, flags);
	q->sync_समय = समय;
	q->sync_event_put = 0;
	wake_up(&q->sync_sleep);
	spin_unlock_irqrestore(&q->sync_lock, flags);
पूर्ण


/*
 * वापस the unused pool size
 */
पूर्णांक
snd_seq_oss_ग_लिखोq_get_मुक्त_size(काष्ठा seq_oss_ग_लिखोq *q)
अणु
	काष्ठा snd_seq_client_pool pool;
	pool.client = q->dp->cseq;
	snd_seq_oss_control(q->dp, SNDRV_SEQ_IOCTL_GET_CLIENT_POOL, &pool);
	वापस pool.output_मुक्त;
पूर्ण


/*
 * set output threshold size from ioctl
 */
व्योम
snd_seq_oss_ग_लिखोq_set_output(काष्ठा seq_oss_ग_लिखोq *q, पूर्णांक val)
अणु
	काष्ठा snd_seq_client_pool pool;
	pool.client = q->dp->cseq;
	snd_seq_oss_control(q->dp, SNDRV_SEQ_IOCTL_GET_CLIENT_POOL, &pool);
	pool.output_room = val;
	snd_seq_oss_control(q->dp, SNDRV_SEQ_IOCTL_SET_CLIENT_POOL, &pool);
पूर्ण

