<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 *  ALSA sequencer Timer
 *  Copyright (c) 1998-1999 by Frank van de Pol <fvdpol@coil.demon.nl>
 */
#अगर_अघोषित __SND_SEQ_TIMER_H
#घोषणा __SND_SEQ_TIMER_H

#समावेश <sound/समयr.h>
#समावेश <sound/seq_kernel.h>

काष्ठा snd_seq_समयr_tick अणु
	snd_seq_tick_समय_प्रकार	cur_tick;	/* current tick */
	अचिन्हित दीर्घ		resolution;	/* समय per tick in nsec */
	अचिन्हित दीर्घ		fraction;	/* current समय per tick in nsec */
पूर्ण;

काष्ठा snd_seq_समयr अणु
	/* ... tempo / offset / running state */

	अचिन्हित पूर्णांक		running:1,	/* running state of queue */	
				initialized:1;	/* समयr is initialized */

	अचिन्हित पूर्णांक		tempo;		/* current tempo, us/tick */
	पूर्णांक			ppq;		/* समय resolution, ticks/quarter */

	snd_seq_real_समय_प्रकार	cur_समय;	/* current समय */
	काष्ठा snd_seq_समयr_tick	tick;	/* current tick */
	पूर्णांक tick_updated;
	
	पूर्णांक			type;		/* समयr type */
	काष्ठा snd_समयr_id	alsa_id;	/* ALSA's समयr ID */
	काष्ठा snd_समयr_instance	*समयri;	/* समयr instance */
	अचिन्हित पूर्णांक		ticks;
	अचिन्हित दीर्घ		preferred_resolution; /* समयr resolution, ticks/sec */

	अचिन्हित पूर्णांक skew;
	अचिन्हित पूर्णांक skew_base;

	काष्ठा बारpec64	last_update;	 /* समय of last घड़ी update, used क्रम पूर्णांकerpolation */

	spinlock_t lock;
पूर्ण;


/* create new समयr (स्थिरructor) */
काष्ठा snd_seq_समयr *snd_seq_समयr_new(व्योम);

/* delete समयr (deकाष्ठाor) */
व्योम snd_seq_समयr_delete(काष्ठा snd_seq_समयr **पंचांगr);

/* */
अटल अंतरभूत व्योम snd_seq_समयr_update_tick(काष्ठा snd_seq_समयr_tick *tick,
					     अचिन्हित दीर्घ resolution)
अणु
	अगर (tick->resolution > 0) अणु
		tick->fraction += resolution;
		tick->cur_tick += (अचिन्हित पूर्णांक)(tick->fraction / tick->resolution);
		tick->fraction %= tick->resolution;
	पूर्ण
पूर्ण


/* compare बारtamp between events */
/* वापस 1 अगर a >= b; otherwise वापस 0 */
अटल अंतरभूत पूर्णांक snd_seq_compare_tick_समय(snd_seq_tick_समय_प्रकार *a, snd_seq_tick_समय_प्रकार *b)
अणु
	/* compare ticks */
	वापस (*a >= *b);
पूर्ण

अटल अंतरभूत पूर्णांक snd_seq_compare_real_समय(snd_seq_real_समय_प्रकार *a, snd_seq_real_समय_प्रकार *b)
अणु
	/* compare real समय */
	अगर (a->tv_sec > b->tv_sec)
		वापस 1;
	अगर ((a->tv_sec == b->tv_sec) && (a->tv_nsec >= b->tv_nsec))
		वापस 1;
	वापस 0;
पूर्ण


अटल अंतरभूत व्योम snd_seq_sanity_real_समय(snd_seq_real_समय_प्रकार *पंचांग)
अणु
	जबतक (पंचांग->tv_nsec >= 1000000000) अणु
		/* roll-over */
		पंचांग->tv_nsec -= 1000000000;
                पंचांग->tv_sec++;
        पूर्ण
पूर्ण


/* increment बारtamp */
अटल अंतरभूत व्योम snd_seq_inc_real_समय(snd_seq_real_समय_प्रकार *पंचांग, snd_seq_real_समय_प्रकार *inc)
अणु
	पंचांग->tv_sec  += inc->tv_sec;
	पंचांग->tv_nsec += inc->tv_nsec;
	snd_seq_sanity_real_समय(पंचांग);
पूर्ण

अटल अंतरभूत व्योम snd_seq_inc_समय_nsec(snd_seq_real_समय_प्रकार *पंचांग, अचिन्हित दीर्घ nsec)
अणु
	पंचांग->tv_nsec  += nsec;
	snd_seq_sanity_real_समय(पंचांग);
पूर्ण

/* called by समयr isr */
काष्ठा snd_seq_queue;
पूर्णांक snd_seq_समयr_खोलो(काष्ठा snd_seq_queue *q);
पूर्णांक snd_seq_समयr_बंद(काष्ठा snd_seq_queue *q);
पूर्णांक snd_seq_समयr_midi_खोलो(काष्ठा snd_seq_queue *q);
पूर्णांक snd_seq_समयr_midi_बंद(काष्ठा snd_seq_queue *q);
व्योम snd_seq_समयr_शेषs(काष्ठा snd_seq_समयr *पंचांगr);
व्योम snd_seq_समयr_reset(काष्ठा snd_seq_समयr *पंचांगr);
पूर्णांक snd_seq_समयr_stop(काष्ठा snd_seq_समयr *पंचांगr);
पूर्णांक snd_seq_समयr_start(काष्ठा snd_seq_समयr *पंचांगr);
पूर्णांक snd_seq_समयr_जारी(काष्ठा snd_seq_समयr *पंचांगr);
पूर्णांक snd_seq_समयr_set_tempo(काष्ठा snd_seq_समयr *पंचांगr, पूर्णांक tempo);
पूर्णांक snd_seq_समयr_set_tempo_ppq(काष्ठा snd_seq_समयr *पंचांगr, पूर्णांक tempo, पूर्णांक ppq);
पूर्णांक snd_seq_समयr_set_position_tick(काष्ठा snd_seq_समयr *पंचांगr, snd_seq_tick_समय_प्रकार position);
पूर्णांक snd_seq_समयr_set_position_समय(काष्ठा snd_seq_समयr *पंचांगr, snd_seq_real_समय_प्रकार position);
पूर्णांक snd_seq_समयr_set_skew(काष्ठा snd_seq_समयr *पंचांगr, अचिन्हित पूर्णांक skew, अचिन्हित पूर्णांक base);
snd_seq_real_समय_प्रकार snd_seq_समयr_get_cur_समय(काष्ठा snd_seq_समयr *पंचांगr,
					       bool adjust_kसमय);
snd_seq_tick_समय_प्रकार snd_seq_समयr_get_cur_tick(काष्ठा snd_seq_समयr *पंचांगr);

बाह्य पूर्णांक seq_शेष_समयr_class;
बाह्य पूर्णांक seq_शेष_समयr_sclass;
बाह्य पूर्णांक seq_शेष_समयr_card;
बाह्य पूर्णांक seq_शेष_समयr_device;
बाह्य पूर्णांक seq_शेष_समयr_subdevice;
बाह्य पूर्णांक seq_शेष_समयr_resolution;

#पूर्ण_अगर
