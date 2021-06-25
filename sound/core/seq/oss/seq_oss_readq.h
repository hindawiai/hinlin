<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * OSS compatible sequencer driver
 * पढ़ो fअगरo queue
 *
 * Copyright (C) 1998,99 Takashi Iwai <tiwai@suse.de>
 */

#अगर_अघोषित __SEQ_OSS_READQ_H
#घोषणा __SEQ_OSS_READQ_H

#समावेश "seq_oss_device.h"


/*
 * definition of पढ़ो queue
 */
काष्ठा seq_oss_पढ़ोq अणु
	जोड़ evrec *q;
	पूर्णांक qlen;
	पूर्णांक maxlen;
	पूर्णांक head, tail;
	अचिन्हित दीर्घ pre_event_समयout;
	अचिन्हित दीर्घ input_समय;
	रुको_queue_head_t midi_sleep;
	spinlock_t lock;
पूर्ण;

काष्ठा seq_oss_पढ़ोq *snd_seq_oss_पढ़ोq_new(काष्ठा seq_oss_devinfo *dp, पूर्णांक maxlen);
व्योम snd_seq_oss_पढ़ोq_delete(काष्ठा seq_oss_पढ़ोq *q);
व्योम snd_seq_oss_पढ़ोq_clear(काष्ठा seq_oss_पढ़ोq *पढ़ोq);
अचिन्हित पूर्णांक snd_seq_oss_पढ़ोq_poll(काष्ठा seq_oss_पढ़ोq *पढ़ोq, काष्ठा file *file, poll_table *रुको);
पूर्णांक snd_seq_oss_पढ़ोq_माला_दो(काष्ठा seq_oss_पढ़ोq *पढ़ोq, पूर्णांक dev, अचिन्हित अक्षर *data, पूर्णांक len);
पूर्णांक snd_seq_oss_पढ़ोq_sysex(काष्ठा seq_oss_पढ़ोq *q, पूर्णांक dev,
			    काष्ठा snd_seq_event *ev);
पूर्णांक snd_seq_oss_पढ़ोq_put_event(काष्ठा seq_oss_पढ़ोq *पढ़ोq, जोड़ evrec *ev);
पूर्णांक snd_seq_oss_पढ़ोq_put_बारtamp(काष्ठा seq_oss_पढ़ोq *पढ़ोq, अचिन्हित दीर्घ curt, पूर्णांक seq_mode);
पूर्णांक snd_seq_oss_पढ़ोq_pick(काष्ठा seq_oss_पढ़ोq *q, जोड़ evrec *rec);
व्योम snd_seq_oss_पढ़ोq_रुको(काष्ठा seq_oss_पढ़ोq *q);
व्योम snd_seq_oss_पढ़ोq_मुक्त(काष्ठा seq_oss_पढ़ोq *q);

#घोषणा snd_seq_oss_पढ़ोq_lock(q, flags) spin_lock_irqsave(&(q)->lock, flags)
#घोषणा snd_seq_oss_पढ़ोq_unlock(q, flags) spin_unlock_irqrestore(&(q)->lock, flags)

#पूर्ण_अगर
