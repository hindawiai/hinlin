<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *  Copyright (c) by Lee Revell <rlrevell@joe-job.com>
 *                   Clemens Ladisch <clemens@ladisch.de>
 *  Routines क्रम control of EMU10K1 chips
 *
 *  BUGS:
 *    --
 *
 *  TODO:
 *    --
 */

#समावेश <linux/समय.स>
#समावेश <sound/core.h>
#समावेश <sound/emu10k1.h>

अटल पूर्णांक snd_emu10k1_समयr_start(काष्ठा snd_समयr *समयr)
अणु
	काष्ठा snd_emu10k1 *emu;
	अचिन्हित दीर्घ flags;
	अचिन्हित पूर्णांक delay;

	emu = snd_समयr_chip(समयr);
	delay = समयr->sticks - 1;
	अगर (delay < 5 ) /* minimum समय is 5 ticks */
		delay = 5;
	spin_lock_irqsave(&emu->reg_lock, flags);
	snd_emu10k1_पूर्णांकr_enable(emu, INTE_INTERVALTIMERENB);
	outw(delay & TIMER_RATE_MASK, emu->port + TIMER);
	spin_unlock_irqrestore(&emu->reg_lock, flags);
	वापस 0;
पूर्ण

अटल पूर्णांक snd_emu10k1_समयr_stop(काष्ठा snd_समयr *समयr)
अणु
	काष्ठा snd_emu10k1 *emu;
	अचिन्हित दीर्घ flags;

	emu = snd_समयr_chip(समयr);
	spin_lock_irqsave(&emu->reg_lock, flags);
	snd_emu10k1_पूर्णांकr_disable(emu, INTE_INTERVALTIMERENB);
	spin_unlock_irqrestore(&emu->reg_lock, flags);
	वापस 0;
पूर्ण

अटल पूर्णांक snd_emu10k1_समयr_precise_resolution(काष्ठा snd_समयr *समयr,
					       अचिन्हित दीर्घ *num, अचिन्हित दीर्घ *den)
अणु
	*num = 1;
	*den = 48000;
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा snd_समयr_hardware snd_emu10k1_समयr_hw = अणु
	.flags = SNDRV_TIMER_HW_AUTO,
	.resolution = 20833, /* 1 sample @ 48KHZ = 20.833...us */
	.ticks = 1024,
	.start = snd_emu10k1_समयr_start,
	.stop = snd_emu10k1_समयr_stop,
	.precise_resolution = snd_emu10k1_समयr_precise_resolution,
पूर्ण;

पूर्णांक snd_emu10k1_समयr(काष्ठा snd_emu10k1 *emu, पूर्णांक device)
अणु
	काष्ठा snd_समयr *समयr = शून्य;
	काष्ठा snd_समयr_id tid;
	पूर्णांक err;

	tid.dev_class = SNDRV_TIMER_CLASS_CARD;
	tid.dev_sclass = SNDRV_TIMER_SCLASS_NONE;
	tid.card = emu->card->number;
	tid.device = device;
	tid.subdevice = 0;
	अगर ((err = snd_समयr_new(emu->card, "EMU10K1", &tid, &समयr)) >= 0) अणु
		म_नकल(समयr->name, "EMU10K1 timer");
		समयr->निजी_data = emu;
		समयr->hw = snd_emu10k1_समयr_hw;
	पूर्ण
	emu->समयr = समयr;
	वापस err;
पूर्ण
