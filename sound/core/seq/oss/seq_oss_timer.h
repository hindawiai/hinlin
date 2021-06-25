<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * OSS compatible sequencer driver
 * समयr handling routines
 *
 * Copyright (C) 1998,99 Takashi Iwai <tiwai@suse.de>
 */

#अगर_अघोषित __SEQ_OSS_TIMER_H
#घोषणा __SEQ_OSS_TIMER_H

#समावेश "seq_oss_device.h"

/*
 * समयr inक्रमmation definition
 */
काष्ठा seq_oss_समयr अणु
	काष्ठा seq_oss_devinfo *dp;
	relसमय_प्रकार cur_tick;
	पूर्णांक realसमय;
	पूर्णांक running;
	पूर्णांक tempo, ppq;	/* ALSA queue */
	पूर्णांक oss_tempo, oss_समयbase;
पूर्ण;	


काष्ठा seq_oss_समयr *snd_seq_oss_समयr_new(काष्ठा seq_oss_devinfo *dp);
व्योम snd_seq_oss_समयr_delete(काष्ठा seq_oss_समयr *dp);

पूर्णांक snd_seq_oss_समयr_start(काष्ठा seq_oss_समयr *समयr);
पूर्णांक snd_seq_oss_समयr_stop(काष्ठा seq_oss_समयr *समयr);
पूर्णांक snd_seq_oss_समयr_जारी(काष्ठा seq_oss_समयr *समयr);
पूर्णांक snd_seq_oss_समयr_tempo(काष्ठा seq_oss_समयr *समयr, पूर्णांक value);
#घोषणा snd_seq_oss_समयr_reset  snd_seq_oss_समयr_start

पूर्णांक snd_seq_oss_समयr_ioctl(काष्ठा seq_oss_समयr *समयr, अचिन्हित पूर्णांक cmd, पूर्णांक __user *arg);

/*
 * get current processed समय
 */
अटल अंतरभूत असलसमय_प्रकार
snd_seq_oss_समयr_cur_tick(काष्ठा seq_oss_समयr *समयr)
अणु
	वापस समयr->cur_tick;
पूर्ण

#पूर्ण_अगर
