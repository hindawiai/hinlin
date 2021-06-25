<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * OSS compatible sequencer driver
 * ग_लिखो priority queue
 *
 * Copyright (C) 1998,99 Takashi Iwai <tiwai@suse.de>
 */

#अगर_अघोषित __SEQ_OSS_WRITEQ_H
#घोषणा __SEQ_OSS_WRITEQ_H

#समावेश "seq_oss_device.h"


काष्ठा seq_oss_ग_लिखोq अणु
	काष्ठा seq_oss_devinfo *dp;
	पूर्णांक maxlen;
	असलसमय_प्रकार sync_समय;
	पूर्णांक sync_event_put;
	रुको_queue_head_t sync_sleep;
	spinlock_t sync_lock;
पूर्ण;


/*
 * seq_oss_ग_लिखोq.c
 */
काष्ठा seq_oss_ग_लिखोq *snd_seq_oss_ग_लिखोq_new(काष्ठा seq_oss_devinfo *dp, पूर्णांक maxlen);
व्योम snd_seq_oss_ग_लिखोq_delete(काष्ठा seq_oss_ग_लिखोq *q);
व्योम snd_seq_oss_ग_लिखोq_clear(काष्ठा seq_oss_ग_लिखोq *q);
पूर्णांक snd_seq_oss_ग_लिखोq_sync(काष्ठा seq_oss_ग_लिखोq *q);
व्योम snd_seq_oss_ग_लिखोq_wakeup(काष्ठा seq_oss_ग_लिखोq *q, असलसमय_प्रकार समय);
पूर्णांक snd_seq_oss_ग_लिखोq_get_मुक्त_size(काष्ठा seq_oss_ग_लिखोq *q);
व्योम snd_seq_oss_ग_लिखोq_set_output(काष्ठा seq_oss_ग_लिखोq *q, पूर्णांक size);


#पूर्ण_अगर
