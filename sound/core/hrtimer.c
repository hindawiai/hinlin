<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * ALSA समयr back-end using hrसमयr
 * Copyright (C) 2008 Takashi Iwai
 */

#समावेश <linux/init.h>
#समावेश <linux/slab.h>
#समावेश <linux/module.h>
#समावेश <linux/moduleparam.h>
#समावेश <linux/hrसमयr.h>
#समावेश <sound/core.h>
#समावेश <sound/समयr.h>

MODULE_AUTHOR("Takashi Iwai <tiwai@suse.de>");
MODULE_DESCRIPTION("ALSA hrtimer backend");
MODULE_LICENSE("GPL");

MODULE_ALIAS("snd-timer-" __stringअगरy(SNDRV_TIMER_GLOBAL_HRTIMER));

#घोषणा न_अंकO_SEC	1000000000UL	/* 10^9 in sec */
अटल अचिन्हित पूर्णांक resolution;

काष्ठा snd_hrसमयr अणु
	काष्ठा snd_समयr *समयr;
	काष्ठा hrसमयr hrt;
	bool in_callback;
पूर्ण;

अटल क्रमागत hrसमयr_restart snd_hrसमयr_callback(काष्ठा hrसमयr *hrt)
अणु
	काष्ठा snd_hrसमयr *sसमय = container_of(hrt, काष्ठा snd_hrसमयr, hrt);
	काष्ठा snd_समयr *t = sसमय->समयr;
	kसमय_प्रकार delta;
	अचिन्हित दीर्घ ticks;
	क्रमागत hrसमयr_restart ret = HRTIMER_NORESTART;

	spin_lock(&t->lock);
	अगर (!t->running)
		जाओ out; /* fast path */
	sसमय->in_callback = true;
	ticks = t->sticks;
	spin_unlock(&t->lock);

	/* calculate the drअगरt */
	delta = kसमय_sub(hrt->base->get_समय(), hrसमयr_get_expires(hrt));
	अगर (delta > 0)
		ticks += kसमय_भागns(delta, ticks * resolution);

	snd_समयr_पूर्णांकerrupt(sसमय->समयr, ticks);

	spin_lock(&t->lock);
	अगर (t->running) अणु
		hrसमयr_add_expires_ns(hrt, t->sticks * resolution);
		ret = HRTIMER_RESTART;
	पूर्ण

	sसमय->in_callback = false;
 out:
	spin_unlock(&t->lock);
	वापस ret;
पूर्ण

अटल पूर्णांक snd_hrसमयr_खोलो(काष्ठा snd_समयr *t)
अणु
	काष्ठा snd_hrसमयr *sसमय;

	sसमय = kzalloc(माप(*sसमय), GFP_KERNEL);
	अगर (!sसमय)
		वापस -ENOMEM;
	hrसमयr_init(&sसमय->hrt, CLOCK_MONOTONIC, HRTIMER_MODE_REL);
	sसमय->समयr = t;
	sसमय->hrt.function = snd_hrसमयr_callback;
	t->निजी_data = sसमय;
	वापस 0;
पूर्ण

अटल पूर्णांक snd_hrसमयr_बंद(काष्ठा snd_समयr *t)
अणु
	काष्ठा snd_hrसमयr *sसमय = t->निजी_data;

	अगर (sसमय) अणु
		spin_lock_irq(&t->lock);
		t->running = 0; /* just to be sure */
		sसमय->in_callback = 1; /* skip start/stop */
		spin_unlock_irq(&t->lock);

		hrसमयr_cancel(&sसमय->hrt);
		kमुक्त(sसमय);
		t->निजी_data = शून्य;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक snd_hrसमयr_start(काष्ठा snd_समयr *t)
अणु
	काष्ठा snd_hrसमयr *sसमय = t->निजी_data;

	अगर (sसमय->in_callback)
		वापस 0;
	hrसमयr_start(&sसमय->hrt, ns_to_kसमय(t->sticks * resolution),
		      HRTIMER_MODE_REL);
	वापस 0;
पूर्ण

अटल पूर्णांक snd_hrसमयr_stop(काष्ठा snd_समयr *t)
अणु
	काष्ठा snd_hrसमयr *sसमय = t->निजी_data;

	अगर (sसमय->in_callback)
		वापस 0;
	hrसमयr_try_to_cancel(&sसमय->hrt);
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा snd_समयr_hardware hrसमयr_hw __initस्थिर = अणु
	.flags =	SNDRV_TIMER_HW_AUTO | SNDRV_TIMER_HW_WORK,
	.खोलो =		snd_hrसमयr_खोलो,
	.बंद =	snd_hrसमयr_बंद,
	.start =	snd_hrसमयr_start,
	.stop =		snd_hrसमयr_stop,
पूर्ण;

/*
 * entry functions
 */

अटल काष्ठा snd_समयr *myसमयr;

अटल पूर्णांक __init snd_hrसमयr_init(व्योम)
अणु
	काष्ठा snd_समयr *समयr;
	पूर्णांक err;

	resolution = hrसमयr_resolution;

	/* Create a new समयr and set up the fields */
	err = snd_समयr_global_new("hrtimer", SNDRV_TIMER_GLOBAL_HRTIMER,
				   &समयr);
	अगर (err < 0)
		वापस err;

	समयr->module = THIS_MODULE;
	म_नकल(समयr->name, "HR timer");
	समयr->hw = hrसमयr_hw;
	समयr->hw.resolution = resolution;
	समयr->hw.ticks = न_अंकO_SEC / resolution;
	समयr->max_instances = 100; /* lower the limit */

	err = snd_समयr_global_रेजिस्टर(समयr);
	अगर (err < 0) अणु
		snd_समयr_global_मुक्त(समयr);
		वापस err;
	पूर्ण
	myसमयr = समयr; /* remember this */

	वापस 0;
पूर्ण

अटल व्योम __निकास snd_hrसमयr_निकास(व्योम)
अणु
	अगर (myसमयr) अणु
		snd_समयr_global_मुक्त(myसमयr);
		myसमयr = शून्य;
	पूर्ण
पूर्ण

module_init(snd_hrसमयr_init);
module_निकास(snd_hrसमयr_निकास);
