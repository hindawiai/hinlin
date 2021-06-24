<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#समावेश <linux/kthपढ़ो.h>
#समावेश <linux/रुको.h>

#समावेश "spk_types.h"
#समावेश "speakup.h"
#समावेश "spk_priv.h"

DECLARE_WAIT_QUEUE_HEAD(speakup_event);
EXPORT_SYMBOL_GPL(speakup_event);

पूर्णांक speakup_thपढ़ो(व्योम *data)
अणु
	अचिन्हित दीर्घ flags;
	पूर्णांक should_अवरोध;
	काष्ठा bleep our_sound;

	our_sound.active = 0;
	our_sound.freq = 0;
	our_sound.jअगरfies = 0;

	mutex_lock(&spk_mutex);
	जबतक (1) अणु
		DEFINE_WAIT(रुको);

		जबतक (1) अणु
			spin_lock_irqsave(&speakup_info.spinlock, flags);
			our_sound = spk_unprocessed_sound;
			spk_unprocessed_sound.active = 0;
			prepare_to_रुको(&speakup_event, &रुको,
					TASK_INTERRUPTIBLE);
			should_अवरोध = kthपढ़ो_should_stop() ||
				our_sound.active ||
				(synth && synth->catch_up && synth->alive &&
					(speakup_info.flushing ||
					!synth_buffer_empty()));
			spin_unlock_irqrestore(&speakup_info.spinlock, flags);
			अगर (should_अवरोध)
				अवरोध;
			mutex_unlock(&spk_mutex);
			schedule();
			mutex_lock(&spk_mutex);
		पूर्ण
		finish_रुको(&speakup_event, &रुको);
		अगर (kthपढ़ो_should_stop())
			अवरोध;

		अगर (our_sound.active)
			kd_mksound(our_sound.freq, our_sound.jअगरfies);
		अगर (synth && synth->catch_up && synth->alive) अणु
			/*
			 * It is up to the callee to take the lock, so that it
			 * can sleep whenever it likes
			 */
			synth->catch_up(synth);
		पूर्ण

		speakup_start_ttys();
	पूर्ण
	mutex_unlock(&spk_mutex);
	वापस 0;
पूर्ण
