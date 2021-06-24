<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * OSS compatible sequencer driver
 *
 * पढ़ो/ग_लिखो/select पूर्णांकerface to device file
 *
 * Copyright (C) 1998,99 Takashi Iwai <tiwai@suse.de>
 */

#समावेश "seq_oss_device.h"
#समावेश "seq_oss_readq.h"
#समावेश "seq_oss_writeq.h"
#समावेश "seq_oss_synth.h"
#समावेश <sound/seq_oss_legacy.h>
#समावेश "seq_oss_event.h"
#समावेश "seq_oss_timer.h"
#समावेश "../seq_clientmgr.h"


/*
 * protoypes
 */
अटल पूर्णांक insert_queue(काष्ठा seq_oss_devinfo *dp, जोड़ evrec *rec, काष्ठा file *opt);


/*
 * पढ़ो पूर्णांकerface
 */

पूर्णांक
snd_seq_oss_पढ़ो(काष्ठा seq_oss_devinfo *dp, अक्षर __user *buf, पूर्णांक count)
अणु
	काष्ठा seq_oss_पढ़ोq *पढ़ोq = dp->पढ़ोq;
	पूर्णांक result = 0, err = 0;
	पूर्णांक ev_len;
	जोड़ evrec rec;
	अचिन्हित दीर्घ flags;

	अगर (पढ़ोq == शून्य || ! is_पढ़ो_mode(dp->file_mode))
		वापस -ENXIO;

	जबतक (count >= SHORT_EVENT_SIZE) अणु
		snd_seq_oss_पढ़ोq_lock(पढ़ोq, flags);
		err = snd_seq_oss_पढ़ोq_pick(पढ़ोq, &rec);
		अगर (err == -EAGAIN &&
		    !is_nonblock_mode(dp->file_mode) && result == 0) अणु
			snd_seq_oss_पढ़ोq_unlock(पढ़ोq, flags);
			snd_seq_oss_पढ़ोq_रुको(पढ़ोq);
			snd_seq_oss_पढ़ोq_lock(पढ़ोq, flags);
			अगर (संकेत_pending(current))
				err = -ERESTARTSYS;
			अन्यथा
				err = snd_seq_oss_पढ़ोq_pick(पढ़ोq, &rec);
		पूर्ण
		अगर (err < 0) अणु
			snd_seq_oss_पढ़ोq_unlock(पढ़ोq, flags);
			अवरोध;
		पूर्ण
		ev_len = ev_length(&rec);
		अगर (ev_len < count) अणु
			snd_seq_oss_पढ़ोq_unlock(पढ़ोq, flags);
			अवरोध;
		पूर्ण
		snd_seq_oss_पढ़ोq_मुक्त(पढ़ोq);
		snd_seq_oss_पढ़ोq_unlock(पढ़ोq, flags);
		अगर (copy_to_user(buf, &rec, ev_len)) अणु
			err = -EFAULT;
			अवरोध;
		पूर्ण
		result += ev_len;
		buf += ev_len;
		count -= ev_len;
	पूर्ण
	वापस result > 0 ? result : err;
पूर्ण


/*
 * ग_लिखो पूर्णांकerface
 */

पूर्णांक
snd_seq_oss_ग_लिखो(काष्ठा seq_oss_devinfo *dp, स्थिर अक्षर __user *buf, पूर्णांक count, काष्ठा file *opt)
अणु
	पूर्णांक result = 0, err = 0;
	पूर्णांक ev_size, fmt;
	जोड़ evrec rec;

	अगर (! is_ग_लिखो_mode(dp->file_mode) || dp->ग_लिखोq == शून्य)
		वापस -ENXIO;

	जबतक (count >= SHORT_EVENT_SIZE) अणु
		अगर (copy_from_user(&rec, buf, SHORT_EVENT_SIZE)) अणु
			err = -EFAULT;
			अवरोध;
		पूर्ण
		अगर (rec.s.code == SEQ_FULLSIZE) अणु
			/* load patch */
			अगर (result > 0) अणु
				err = -EINVAL;
				अवरोध;
			पूर्ण
			fmt = (*(अचिन्हित लघु *)rec.c) & 0xffff;
			/* FIXME the वापस value isn't correct */
			वापस snd_seq_oss_synth_load_patch(dp, rec.s.dev,
							    fmt, buf, 0, count);
		पूर्ण
		अगर (ev_is_दीर्घ(&rec)) अणु
			/* extended code */
			अगर (rec.s.code == SEQ_EXTENDED &&
			    dp->seq_mode == SNDRV_SEQ_OSS_MODE_MUSIC) अणु
				err = -EINVAL;
				अवरोध;
			पूर्ण
			ev_size = LONG_EVENT_SIZE;
			अगर (count < ev_size)
				अवरोध;
			/* copy the reset 4 bytes */
			अगर (copy_from_user(rec.c + SHORT_EVENT_SIZE,
					   buf + SHORT_EVENT_SIZE,
					   LONG_EVENT_SIZE - SHORT_EVENT_SIZE)) अणु
				err = -EFAULT;
				अवरोध;
			पूर्ण
		पूर्ण अन्यथा अणु
			/* old-type code */
			अगर (dp->seq_mode == SNDRV_SEQ_OSS_MODE_MUSIC) अणु
				err = -EINVAL;
				अवरोध;
			पूर्ण
			ev_size = SHORT_EVENT_SIZE;
		पूर्ण

		/* insert queue */
		अगर ((err = insert_queue(dp, &rec, opt)) < 0)
			अवरोध;

		result += ev_size;
		buf += ev_size;
		count -= ev_size;
	पूर्ण
	वापस result > 0 ? result : err;
पूर्ण


/*
 * insert event record to ग_लिखो queue
 * वापस: 0 = OK, non-zero = NG
 */
अटल पूर्णांक
insert_queue(काष्ठा seq_oss_devinfo *dp, जोड़ evrec *rec, काष्ठा file *opt)
अणु
	पूर्णांक rc = 0;
	काष्ठा snd_seq_event event;

	/* अगर this is a timing event, process the current समय */
	अगर (snd_seq_oss_process_समयr_event(dp->समयr, rec))
		वापस 0; /* no need to insert queue */

	/* parse this event */
	स_रखो(&event, 0, माप(event));
	/* set dummy -- to be sure */
	event.type = SNDRV_SEQ_EVENT_NOTखातापूर्णF;
	snd_seq_oss_fill_addr(dp, &event, dp->addr.client, dp->addr.port);

	अगर (snd_seq_oss_process_event(dp, rec, &event))
		वापस 0; /* invalid event - no need to insert queue */

	event.समय.tick = snd_seq_oss_समयr_cur_tick(dp->समयr);
	अगर (dp->समयr->realसमय || !dp->समयr->running)
		snd_seq_oss_dispatch(dp, &event, 0, 0);
	अन्यथा
		rc = snd_seq_kernel_client_enqueue(dp->cseq, &event, opt,
						   !is_nonblock_mode(dp->file_mode));
	वापस rc;
पूर्ण
		

/*
 * select / poll
 */
  
__poll_t
snd_seq_oss_poll(काष्ठा seq_oss_devinfo *dp, काष्ठा file *file, poll_table * रुको)
अणु
	__poll_t mask = 0;

	/* input */
	अगर (dp->पढ़ोq && is_पढ़ो_mode(dp->file_mode)) अणु
		अगर (snd_seq_oss_पढ़ोq_poll(dp->पढ़ोq, file, रुको))
			mask |= EPOLLIN | EPOLLRDNORM;
	पूर्ण

	/* output */
	अगर (dp->ग_लिखोq && is_ग_लिखो_mode(dp->file_mode)) अणु
		अगर (snd_seq_kernel_client_ग_लिखो_poll(dp->cseq, file, रुको))
			mask |= EPOLLOUT | EPOLLWRNORM;
	पूर्ण
	वापस mask;
पूर्ण
