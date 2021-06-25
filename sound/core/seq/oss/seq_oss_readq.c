<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * OSS compatible sequencer driver
 *
 * seq_oss_पढ़ोq.c - MIDI input queue
 *
 * Copyright (C) 1998,99 Takashi Iwai <tiwai@suse.de>
 */

#समावेश "seq_oss_readq.h"
#समावेश "seq_oss_event.h"
#समावेश <sound/seq_oss_legacy.h>
#समावेश "../seq_lock.h"
#समावेश <linux/रुको.h>
#समावेश <linux/slab.h>

/*
 * स्थिरants
 */
//#घोषणा SNDRV_SEQ_OSS_MAX_TIMEOUT	(अचिन्हित दीर्घ)(-1)
#घोषणा SNDRV_SEQ_OSS_MAX_TIMEOUT	(HZ * 3600)


/*
 * prototypes
 */


/*
 * create a पढ़ो queue
 */
काष्ठा seq_oss_पढ़ोq *
snd_seq_oss_पढ़ोq_new(काष्ठा seq_oss_devinfo *dp, पूर्णांक maxlen)
अणु
	काष्ठा seq_oss_पढ़ोq *q;

	q = kzalloc(माप(*q), GFP_KERNEL);
	अगर (!q)
		वापस शून्य;

	q->q = kसुस्मृति(maxlen, माप(जोड़ evrec), GFP_KERNEL);
	अगर (!q->q) अणु
		kमुक्त(q);
		वापस शून्य;
	पूर्ण

	q->maxlen = maxlen;
	q->qlen = 0;
	q->head = q->tail = 0;
	init_रुकोqueue_head(&q->midi_sleep);
	spin_lock_init(&q->lock);
	q->pre_event_समयout = SNDRV_SEQ_OSS_MAX_TIMEOUT;
	q->input_समय = (अचिन्हित दीर्घ)-1;

	वापस q;
पूर्ण

/*
 * delete the पढ़ो queue
 */
व्योम
snd_seq_oss_पढ़ोq_delete(काष्ठा seq_oss_पढ़ोq *q)
अणु
	अगर (q) अणु
		kमुक्त(q->q);
		kमुक्त(q);
	पूर्ण
पूर्ण

/*
 * reset the पढ़ो queue
 */
व्योम
snd_seq_oss_पढ़ोq_clear(काष्ठा seq_oss_पढ़ोq *q)
अणु
	अगर (q->qlen) अणु
		q->qlen = 0;
		q->head = q->tail = 0;
	पूर्ण
	/* अगर someone sleeping, wake'em up */
	wake_up(&q->midi_sleep);
	q->input_समय = (अचिन्हित दीर्घ)-1;
पूर्ण

/*
 * put a midi byte
 */
पूर्णांक
snd_seq_oss_पढ़ोq_माला_दो(काष्ठा seq_oss_पढ़ोq *q, पूर्णांक dev, अचिन्हित अक्षर *data, पूर्णांक len)
अणु
	जोड़ evrec rec;
	पूर्णांक result;

	स_रखो(&rec, 0, माप(rec));
	rec.c[0] = SEQ_MIDIPUTC;
	rec.c[2] = dev;

	जबतक (len-- > 0) अणु
		rec.c[1] = *data++;
		result = snd_seq_oss_पढ़ोq_put_event(q, &rec);
		अगर (result < 0)
			वापस result;
	पूर्ण
	वापस 0;
पूर्ण

/*
 * put MIDI sysex bytes; the event buffer may be chained, thus it has
 * to be expanded via snd_seq_dump_var_event().
 */
काष्ठा पढ़ोq_sysex_ctx अणु
	काष्ठा seq_oss_पढ़ोq *पढ़ोq;
	पूर्णांक dev;
पूर्ण;

अटल पूर्णांक पढ़ोq_dump_sysex(व्योम *ptr, व्योम *buf, पूर्णांक count)
अणु
	काष्ठा पढ़ोq_sysex_ctx *ctx = ptr;

	वापस snd_seq_oss_पढ़ोq_माला_दो(ctx->पढ़ोq, ctx->dev, buf, count);
पूर्ण

पूर्णांक snd_seq_oss_पढ़ोq_sysex(काष्ठा seq_oss_पढ़ोq *q, पूर्णांक dev,
			    काष्ठा snd_seq_event *ev)
अणु
	काष्ठा पढ़ोq_sysex_ctx ctx = अणु
		.पढ़ोq = q,
		.dev = dev
	पूर्ण;

	अगर ((ev->flags & SNDRV_SEQ_EVENT_LENGTH_MASK) != SNDRV_SEQ_EVENT_LENGTH_VARIABLE)
		वापस 0;
	वापस snd_seq_dump_var_event(ev, पढ़ोq_dump_sysex, &ctx);
पूर्ण

/*
 * copy an event to input queue:
 * वापस zero अगर enqueued
 */
पूर्णांक
snd_seq_oss_पढ़ोq_put_event(काष्ठा seq_oss_पढ़ोq *q, जोड़ evrec *ev)
अणु
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&q->lock, flags);
	अगर (q->qlen >= q->maxlen - 1) अणु
		spin_unlock_irqrestore(&q->lock, flags);
		वापस -ENOMEM;
	पूर्ण

	स_नकल(&q->q[q->tail], ev, माप(*ev));
	q->tail = (q->tail + 1) % q->maxlen;
	q->qlen++;

	/* wake up sleeper */
	wake_up(&q->midi_sleep);

	spin_unlock_irqrestore(&q->lock, flags);

	वापस 0;
पूर्ण


/*
 * pop queue
 * caller must hold lock
 */
पूर्णांक
snd_seq_oss_पढ़ोq_pick(काष्ठा seq_oss_पढ़ोq *q, जोड़ evrec *rec)
अणु
	अगर (q->qlen == 0)
		वापस -EAGAIN;
	स_नकल(rec, &q->q[q->head], माप(*rec));
	वापस 0;
पूर्ण

/*
 * sleep until पढ़ोy
 */
व्योम
snd_seq_oss_पढ़ोq_रुको(काष्ठा seq_oss_पढ़ोq *q)
अणु
	रुको_event_पूर्णांकerruptible_समयout(q->midi_sleep,
					 (q->qlen > 0 || q->head == q->tail),
					 q->pre_event_समयout);
पूर्ण

/*
 * drain one record
 * caller must hold lock
 */
व्योम
snd_seq_oss_पढ़ोq_मुक्त(काष्ठा seq_oss_पढ़ोq *q)
अणु
	अगर (q->qlen > 0) अणु
		q->head = (q->head + 1) % q->maxlen;
		q->qlen--;
	पूर्ण
पूर्ण

/*
 * polling/select:
 * वापस non-zero अगर पढ़ोq is not empty.
 */
अचिन्हित पूर्णांक
snd_seq_oss_पढ़ोq_poll(काष्ठा seq_oss_पढ़ोq *q, काष्ठा file *file, poll_table *रुको)
अणु
	poll_रुको(file, &q->midi_sleep, रुको);
	वापस q->qlen;
पूर्ण

/*
 * put a बारtamp
 */
पूर्णांक
snd_seq_oss_पढ़ोq_put_बारtamp(काष्ठा seq_oss_पढ़ोq *q, अचिन्हित दीर्घ curt, पूर्णांक seq_mode)
अणु
	अगर (curt != q->input_समय) अणु
		जोड़ evrec rec;
		स_रखो(&rec, 0, माप(rec));
		चयन (seq_mode) अणु
		हाल SNDRV_SEQ_OSS_MODE_SYNTH:
			rec.echo = (curt << 8) | SEQ_WAIT;
			snd_seq_oss_पढ़ोq_put_event(q, &rec);
			अवरोध;
		हाल SNDRV_SEQ_OSS_MODE_MUSIC:
			rec.t.code = EV_TIMING;
			rec.t.cmd = TMR_WAIT_ABS;
			rec.t.समय = curt;
			snd_seq_oss_पढ़ोq_put_event(q, &rec);
			अवरोध;
		पूर्ण
		q->input_समय = curt;
	पूर्ण
	वापस 0;
पूर्ण


#अगर_घोषित CONFIG_SND_PROC_FS
/*
 * proc पूर्णांकerface
 */
व्योम
snd_seq_oss_पढ़ोq_info_पढ़ो(काष्ठा seq_oss_पढ़ोq *q, काष्ठा snd_info_buffer *buf)
अणु
	snd_iम_लिखो(buf, "  read queue [%s] length = %d : tick = %ld\n",
		    (रुकोqueue_active(&q->midi_sleep) ? "sleeping":"running"),
		    q->qlen, q->input_समय);
पूर्ण
#पूर्ण_अगर /* CONFIG_SND_PROC_FS */
