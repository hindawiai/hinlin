<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *   ALSA sequencer Timer
 *   Copyright (c) 1998-1999 by Frank van de Pol <fvdpol@coil.demon.nl>
 *                              Jaroslav Kysela <perex@perex.cz>
 */

#समावेश <sound/core.h>
#समावेश <linux/slab.h>
#समावेश "seq_timer.h"
#समावेश "seq_queue.h"
#समावेश "seq_info.h"

/* allowed sequencer समयr frequencies, in Hz */
#घोषणा MIN_FREQUENCY		10
#घोषणा MAX_FREQUENCY		6250
#घोषणा DEFAULT_FREQUENCY	1000

#घोषणा SKEW_BASE	0x10000	/* 16bit shअगरt */

अटल व्योम snd_seq_समयr_set_tick_resolution(काष्ठा snd_seq_समयr *पंचांगr)
अणु
	अगर (पंचांगr->tempo < 1000000)
		पंचांगr->tick.resolution = (पंचांगr->tempo * 1000) / पंचांगr->ppq;
	अन्यथा अणु
		/* might overflow.. */
		अचिन्हित पूर्णांक s;
		s = पंचांगr->tempo % पंचांगr->ppq;
		s = (s * 1000) / पंचांगr->ppq;
		पंचांगr->tick.resolution = (पंचांगr->tempo / पंचांगr->ppq) * 1000;
		पंचांगr->tick.resolution += s;
	पूर्ण
	अगर (पंचांगr->tick.resolution <= 0)
		पंचांगr->tick.resolution = 1;
	snd_seq_समयr_update_tick(&पंचांगr->tick, 0);
पूर्ण

/* create new समयr (स्थिरructor) */
काष्ठा snd_seq_समयr *snd_seq_समयr_new(व्योम)
अणु
	काष्ठा snd_seq_समयr *पंचांगr;
	
	पंचांगr = kzalloc(माप(*पंचांगr), GFP_KERNEL);
	अगर (!पंचांगr)
		वापस शून्य;
	spin_lock_init(&पंचांगr->lock);

	/* reset setup to शेषs */
	snd_seq_समयr_शेषs(पंचांगr);
	
	/* reset समय */
	snd_seq_समयr_reset(पंचांगr);
	
	वापस पंचांगr;
पूर्ण

/* delete समयr (deकाष्ठाor) */
व्योम snd_seq_समयr_delete(काष्ठा snd_seq_समयr **पंचांगr)
अणु
	काष्ठा snd_seq_समयr *t = *पंचांगr;
	*पंचांगr = शून्य;

	अगर (t == शून्य) अणु
		pr_debug("ALSA: seq: snd_seq_timer_delete() called with NULL timer\n");
		वापस;
	पूर्ण
	t->running = 0;

	/* reset समय */
	snd_seq_समयr_stop(t);
	snd_seq_समयr_reset(t);

	kमुक्त(t);
पूर्ण

व्योम snd_seq_समयr_शेषs(काष्ठा snd_seq_समयr * पंचांगr)
अणु
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&पंचांगr->lock, flags);
	/* setup शेषs */
	पंचांगr->ppq = 96;		/* 96 PPQ */
	पंचांगr->tempo = 500000;	/* 120 BPM */
	snd_seq_समयr_set_tick_resolution(पंचांगr);
	पंचांगr->running = 0;

	पंचांगr->type = SNDRV_SEQ_TIMER_ALSA;
	पंचांगr->alsa_id.dev_class = seq_शेष_समयr_class;
	पंचांगr->alsa_id.dev_sclass = seq_शेष_समयr_sclass;
	पंचांगr->alsa_id.card = seq_शेष_समयr_card;
	पंचांगr->alsa_id.device = seq_शेष_समयr_device;
	पंचांगr->alsa_id.subdevice = seq_शेष_समयr_subdevice;
	पंचांगr->preferred_resolution = seq_शेष_समयr_resolution;

	पंचांगr->skew = पंचांगr->skew_base = SKEW_BASE;
	spin_unlock_irqrestore(&पंचांगr->lock, flags);
पूर्ण

अटल व्योम seq_समयr_reset(काष्ठा snd_seq_समयr *पंचांगr)
अणु
	/* reset समय & songposition */
	पंचांगr->cur_समय.tv_sec = 0;
	पंचांगr->cur_समय.tv_nsec = 0;

	पंचांगr->tick.cur_tick = 0;
	पंचांगr->tick.fraction = 0;
पूर्ण

व्योम snd_seq_समयr_reset(काष्ठा snd_seq_समयr *पंचांगr)
अणु
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&पंचांगr->lock, flags);
	seq_समयr_reset(पंचांगr);
	spin_unlock_irqrestore(&पंचांगr->lock, flags);
पूर्ण


/* called by समयr पूर्णांकerrupt routine. the period समय since previous invocation is passed */
अटल व्योम snd_seq_समयr_पूर्णांकerrupt(काष्ठा snd_समयr_instance *समयri,
				    अचिन्हित दीर्घ resolution,
				    अचिन्हित दीर्घ ticks)
अणु
	अचिन्हित दीर्घ flags;
	काष्ठा snd_seq_queue *q = समयri->callback_data;
	काष्ठा snd_seq_समयr *पंचांगr;

	अगर (q == शून्य)
		वापस;
	पंचांगr = q->समयr;
	अगर (पंचांगr == शून्य)
		वापस;
	spin_lock_irqsave(&पंचांगr->lock, flags);
	अगर (!पंचांगr->running) अणु
		spin_unlock_irqrestore(&पंचांगr->lock, flags);
		वापस;
	पूर्ण

	resolution *= ticks;
	अगर (पंचांगr->skew != पंचांगr->skew_base) अणु
		/* FIXME: assuming skew_base = 0x10000 */
		resolution = (resolution >> 16) * पंचांगr->skew +
			(((resolution & 0xffff) * पंचांगr->skew) >> 16);
	पूर्ण

	/* update समयr */
	snd_seq_inc_समय_nsec(&पंचांगr->cur_समय, resolution);

	/* calculate current tick */
	snd_seq_समयr_update_tick(&पंचांगr->tick, resolution);

	/* रेजिस्टर actual समय of this समयr update */
	kसमय_get_ts64(&पंचांगr->last_update);

	spin_unlock_irqrestore(&पंचांगr->lock, flags);

	/* check queues and dispatch events */
	snd_seq_check_queue(q, 1, 0);
पूर्ण

/* set current tempo */
पूर्णांक snd_seq_समयr_set_tempo(काष्ठा snd_seq_समयr * पंचांगr, पूर्णांक tempo)
अणु
	अचिन्हित दीर्घ flags;

	अगर (snd_BUG_ON(!पंचांगr))
		वापस -EINVAL;
	अगर (tempo <= 0)
		वापस -EINVAL;
	spin_lock_irqsave(&पंचांगr->lock, flags);
	अगर ((अचिन्हित पूर्णांक)tempo != पंचांगr->tempo) अणु
		पंचांगr->tempo = tempo;
		snd_seq_समयr_set_tick_resolution(पंचांगr);
	पूर्ण
	spin_unlock_irqrestore(&पंचांगr->lock, flags);
	वापस 0;
पूर्ण

/* set current tempo and ppq in a shot */
पूर्णांक snd_seq_समयr_set_tempo_ppq(काष्ठा snd_seq_समयr *पंचांगr, पूर्णांक tempo, पूर्णांक ppq)
अणु
	पूर्णांक changed;
	अचिन्हित दीर्घ flags;

	अगर (snd_BUG_ON(!पंचांगr))
		वापस -EINVAL;
	अगर (tempo <= 0 || ppq <= 0)
		वापस -EINVAL;
	spin_lock_irqsave(&पंचांगr->lock, flags);
	अगर (पंचांगr->running && (ppq != पंचांगr->ppq)) अणु
		/* refuse to change ppq on running समयrs */
		/* because it will upset the song position (ticks) */
		spin_unlock_irqrestore(&पंचांगr->lock, flags);
		pr_debug("ALSA: seq: cannot change ppq of a running timer\n");
		वापस -EBUSY;
	पूर्ण
	changed = (tempo != पंचांगr->tempo) || (ppq != पंचांगr->ppq);
	पंचांगr->tempo = tempo;
	पंचांगr->ppq = ppq;
	अगर (changed)
		snd_seq_समयr_set_tick_resolution(पंचांगr);
	spin_unlock_irqrestore(&पंचांगr->lock, flags);
	वापस 0;
पूर्ण

/* set current tick position */
पूर्णांक snd_seq_समयr_set_position_tick(काष्ठा snd_seq_समयr *पंचांगr,
				    snd_seq_tick_समय_प्रकार position)
अणु
	अचिन्हित दीर्घ flags;

	अगर (snd_BUG_ON(!पंचांगr))
		वापस -EINVAL;

	spin_lock_irqsave(&पंचांगr->lock, flags);
	पंचांगr->tick.cur_tick = position;
	पंचांगr->tick.fraction = 0;
	spin_unlock_irqrestore(&पंचांगr->lock, flags);
	वापस 0;
पूर्ण

/* set current real-समय position */
पूर्णांक snd_seq_समयr_set_position_समय(काष्ठा snd_seq_समयr *पंचांगr,
				    snd_seq_real_समय_प्रकार position)
अणु
	अचिन्हित दीर्घ flags;

	अगर (snd_BUG_ON(!पंचांगr))
		वापस -EINVAL;

	snd_seq_sanity_real_समय(&position);
	spin_lock_irqsave(&पंचांगr->lock, flags);
	पंचांगr->cur_समय = position;
	spin_unlock_irqrestore(&पंचांगr->lock, flags);
	वापस 0;
पूर्ण

/* set समयr skew */
पूर्णांक snd_seq_समयr_set_skew(काष्ठा snd_seq_समयr *पंचांगr, अचिन्हित पूर्णांक skew,
			   अचिन्हित पूर्णांक base)
अणु
	अचिन्हित दीर्घ flags;

	अगर (snd_BUG_ON(!पंचांगr))
		वापस -EINVAL;

	/* FIXME */
	अगर (base != SKEW_BASE) अणु
		pr_debug("ALSA: seq: invalid skew base 0x%x\n", base);
		वापस -EINVAL;
	पूर्ण
	spin_lock_irqsave(&पंचांगr->lock, flags);
	पंचांगr->skew = skew;
	spin_unlock_irqrestore(&पंचांगr->lock, flags);
	वापस 0;
पूर्ण

पूर्णांक snd_seq_समयr_खोलो(काष्ठा snd_seq_queue *q)
अणु
	काष्ठा snd_समयr_instance *t;
	काष्ठा snd_seq_समयr *पंचांगr;
	अक्षर str[32];
	पूर्णांक err;

	पंचांगr = q->समयr;
	अगर (snd_BUG_ON(!पंचांगr))
		वापस -EINVAL;
	अगर (पंचांगr->समयri)
		वापस -EBUSY;
	प्र_लिखो(str, "sequencer queue %i", q->queue);
	अगर (पंचांगr->type != SNDRV_SEQ_TIMER_ALSA)	/* standard ALSA समयr */
		वापस -EINVAL;
	अगर (पंचांगr->alsa_id.dev_class != SNDRV_TIMER_CLASS_SLAVE)
		पंचांगr->alsa_id.dev_sclass = SNDRV_TIMER_SCLASS_SEQUENCER;
	t = snd_समयr_instance_new(str);
	अगर (!t)
		वापस -ENOMEM;
	t->callback = snd_seq_समयr_पूर्णांकerrupt;
	t->callback_data = q;
	t->flags |= SNDRV_TIMER_IFLG_AUTO;
	err = snd_समयr_खोलो(t, &पंचांगr->alsa_id, q->queue);
	अगर (err < 0 && पंचांगr->alsa_id.dev_class != SNDRV_TIMER_CLASS_SLAVE) अणु
		अगर (पंचांगr->alsa_id.dev_class != SNDRV_TIMER_CLASS_GLOBAL ||
		    पंचांगr->alsa_id.device != SNDRV_TIMER_GLOBAL_SYSTEM) अणु
			काष्ठा snd_समयr_id tid;
			स_रखो(&tid, 0, माप(tid));
			tid.dev_class = SNDRV_TIMER_CLASS_GLOBAL;
			tid.dev_sclass = SNDRV_TIMER_SCLASS_SEQUENCER;
			tid.card = -1;
			tid.device = SNDRV_TIMER_GLOBAL_SYSTEM;
			err = snd_समयr_खोलो(t, &tid, q->queue);
		पूर्ण
	पूर्ण
	अगर (err < 0) अणु
		pr_err("ALSA: seq fatal error: cannot create timer (%i)\n", err);
		snd_समयr_instance_मुक्त(t);
		वापस err;
	पूर्ण
	spin_lock_irq(&पंचांगr->lock);
	अगर (पंचांगr->समयri)
		err = -EBUSY;
	अन्यथा
		पंचांगr->समयri = t;
	spin_unlock_irq(&पंचांगr->lock);
	अगर (err < 0) अणु
		snd_समयr_बंद(t);
		snd_समयr_instance_मुक्त(t);
		वापस err;
	पूर्ण
	वापस 0;
पूर्ण

पूर्णांक snd_seq_समयr_बंद(काष्ठा snd_seq_queue *q)
अणु
	काष्ठा snd_seq_समयr *पंचांगr;
	काष्ठा snd_समयr_instance *t;
	
	पंचांगr = q->समयr;
	अगर (snd_BUG_ON(!पंचांगr))
		वापस -EINVAL;
	spin_lock_irq(&पंचांगr->lock);
	t = पंचांगr->समयri;
	पंचांगr->समयri = शून्य;
	spin_unlock_irq(&पंचांगr->lock);
	अगर (t) अणु
		snd_समयr_बंद(t);
		snd_समयr_instance_मुक्त(t);
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक seq_समयr_stop(काष्ठा snd_seq_समयr *पंचांगr)
अणु
	अगर (! पंचांगr->समयri)
		वापस -EINVAL;
	अगर (!पंचांगr->running)
		वापस 0;
	पंचांगr->running = 0;
	snd_समयr_छोड़ो(पंचांगr->समयri);
	वापस 0;
पूर्ण

पूर्णांक snd_seq_समयr_stop(काष्ठा snd_seq_समयr *पंचांगr)
अणु
	अचिन्हित दीर्घ flags;
	पूर्णांक err;

	spin_lock_irqsave(&पंचांगr->lock, flags);
	err = seq_समयr_stop(पंचांगr);
	spin_unlock_irqrestore(&पंचांगr->lock, flags);
	वापस err;
पूर्ण

अटल पूर्णांक initialize_समयr(काष्ठा snd_seq_समयr *पंचांगr)
अणु
	काष्ठा snd_समयr *t;
	अचिन्हित दीर्घ freq;

	t = पंचांगr->समयri->समयr;
	अगर (!t)
		वापस -EINVAL;

	freq = पंचांगr->preferred_resolution;
	अगर (!freq)
		freq = DEFAULT_FREQUENCY;
	अन्यथा अगर (freq < MIN_FREQUENCY)
		freq = MIN_FREQUENCY;
	अन्यथा अगर (freq > MAX_FREQUENCY)
		freq = MAX_FREQUENCY;

	पंचांगr->ticks = 1;
	अगर (!(t->hw.flags & SNDRV_TIMER_HW_SLAVE)) अणु
		अचिन्हित दीर्घ r = snd_समयr_resolution(पंचांगr->समयri);
		अगर (r) अणु
			पंचांगr->ticks = (अचिन्हित पूर्णांक)(1000000000uL / (r * freq));
			अगर (! पंचांगr->ticks)
				पंचांगr->ticks = 1;
		पूर्ण
	पूर्ण
	पंचांगr->initialized = 1;
	वापस 0;
पूर्ण

अटल पूर्णांक seq_समयr_start(काष्ठा snd_seq_समयr *पंचांगr)
अणु
	अगर (! पंचांगr->समयri)
		वापस -EINVAL;
	अगर (पंचांगr->running)
		seq_समयr_stop(पंचांगr);
	seq_समयr_reset(पंचांगr);
	अगर (initialize_समयr(पंचांगr) < 0)
		वापस -EINVAL;
	snd_समयr_start(पंचांगr->समयri, पंचांगr->ticks);
	पंचांगr->running = 1;
	kसमय_get_ts64(&पंचांगr->last_update);
	वापस 0;
पूर्ण

पूर्णांक snd_seq_समयr_start(काष्ठा snd_seq_समयr *पंचांगr)
अणु
	अचिन्हित दीर्घ flags;
	पूर्णांक err;

	spin_lock_irqsave(&पंचांगr->lock, flags);
	err = seq_समयr_start(पंचांगr);
	spin_unlock_irqrestore(&पंचांगr->lock, flags);
	वापस err;
पूर्ण

अटल पूर्णांक seq_समयr_जारी(काष्ठा snd_seq_समयr *पंचांगr)
अणु
	अगर (! पंचांगr->समयri)
		वापस -EINVAL;
	अगर (पंचांगr->running)
		वापस -EBUSY;
	अगर (! पंचांगr->initialized) अणु
		seq_समयr_reset(पंचांगr);
		अगर (initialize_समयr(पंचांगr) < 0)
			वापस -EINVAL;
	पूर्ण
	snd_समयr_start(पंचांगr->समयri, पंचांगr->ticks);
	पंचांगr->running = 1;
	kसमय_get_ts64(&पंचांगr->last_update);
	वापस 0;
पूर्ण

पूर्णांक snd_seq_समयr_जारी(काष्ठा snd_seq_समयr *पंचांगr)
अणु
	अचिन्हित दीर्घ flags;
	पूर्णांक err;

	spin_lock_irqsave(&पंचांगr->lock, flags);
	err = seq_समयr_जारी(पंचांगr);
	spin_unlock_irqrestore(&पंचांगr->lock, flags);
	वापस err;
पूर्ण

/* वापस current 'real' समय. use समयofday() to get better granularity. */
snd_seq_real_समय_प्रकार snd_seq_समयr_get_cur_समय(काष्ठा snd_seq_समयr *पंचांगr,
					       bool adjust_kसमय)
अणु
	snd_seq_real_समय_प्रकार cur_समय;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&पंचांगr->lock, flags);
	cur_समय = पंचांगr->cur_समय;
	अगर (adjust_kसमय && पंचांगr->running) अणु
		काष्ठा बारpec64 पंचांग;

		kसमय_get_ts64(&पंचांग);
		पंचांग = बारpec64_sub(पंचांग, पंचांगr->last_update);
		cur_समय.tv_nsec += पंचांग.tv_nsec;
		cur_समय.tv_sec += पंचांग.tv_sec;
		snd_seq_sanity_real_समय(&cur_समय);
	पूर्ण
	spin_unlock_irqrestore(&पंचांगr->lock, flags);
	वापस cur_समय;	
पूर्ण

/* TODO: use पूर्णांकerpolation on tick queue (will only be useful क्रम very
 high PPQ values) */
snd_seq_tick_समय_प्रकार snd_seq_समयr_get_cur_tick(काष्ठा snd_seq_समयr *पंचांगr)
अणु
	snd_seq_tick_समय_प्रकार cur_tick;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&पंचांगr->lock, flags);
	cur_tick = पंचांगr->tick.cur_tick;
	spin_unlock_irqrestore(&पंचांगr->lock, flags);
	वापस cur_tick;
पूर्ण


#अगर_घोषित CONFIG_SND_PROC_FS
/* exported to seq_info.c */
व्योम snd_seq_info_समयr_पढ़ो(काष्ठा snd_info_entry *entry,
			     काष्ठा snd_info_buffer *buffer)
अणु
	पूर्णांक idx;
	काष्ठा snd_seq_queue *q;
	काष्ठा snd_seq_समयr *पंचांगr;
	काष्ठा snd_समयr_instance *ti;
	अचिन्हित दीर्घ resolution;
	
	क्रम (idx = 0; idx < SNDRV_SEQ_MAX_QUEUES; idx++) अणु
		q = queueptr(idx);
		अगर (q == शून्य)
			जारी;
		mutex_lock(&q->समयr_mutex);
		पंचांगr = q->समयr;
		अगर (!पंचांगr)
			जाओ unlock;
		ti = पंचांगr->समयri;
		अगर (!ti)
			जाओ unlock;
		snd_iम_लिखो(buffer, "Timer for queue %i : %s\n", q->queue, ti->समयr->name);
		resolution = snd_समयr_resolution(ti) * पंचांगr->ticks;
		snd_iम_लिखो(buffer, "  Period time : %lu.%09lu\n", resolution / 1000000000, resolution % 1000000000);
		snd_iम_लिखो(buffer, "  Skew : %u / %u\n", पंचांगr->skew, पंचांगr->skew_base);
unlock:
		mutex_unlock(&q->समयr_mutex);
		queueमुक्त(q);
 	पूर्ण
पूर्ण
#पूर्ण_अगर /* CONFIG_SND_PROC_FS */

