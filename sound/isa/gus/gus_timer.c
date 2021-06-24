<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *  Routines क्रम Gravis UltraSound soundcards - Timers
 *  Copyright (c) by Jaroslav Kysela <perex@perex.cz>
 *
 *  GUS have similar समयrs as AdLib (OPL2/OPL3 chips).
 */

#समावेश <linux/समय.स>
#समावेश <sound/core.h>
#समावेश <sound/gus.h>

/*
 *  Timer 1 - 80us
 */

अटल पूर्णांक snd_gf1_समयr1_start(काष्ठा snd_समयr * समयr)
अणु
	अचिन्हित दीर्घ flags;
	अचिन्हित अक्षर पंचांगp;
	अचिन्हित पूर्णांक ticks;
	काष्ठा snd_gus_card *gus;

	gus = snd_समयr_chip(समयr);
	spin_lock_irqsave(&gus->reg_lock, flags);
	ticks = समयr->sticks;
	पंचांगp = (gus->gf1.समयr_enabled |= 4);
	snd_gf1_ग_लिखो8(gus, SNDRV_GF1_GB_ADLIB_TIMER_1, 256 - ticks);	/* समयr 1 count */
	snd_gf1_ग_लिखो8(gus, SNDRV_GF1_GB_SOUND_BLASTER_CONTROL, पंचांगp);	/* enable समयr 1 IRQ */
	snd_gf1_adlib_ग_लिखो(gus, 0x04, पंचांगp >> 2);	/* समयr 2 start */
	spin_unlock_irqrestore(&gus->reg_lock, flags);
	वापस 0;
पूर्ण

अटल पूर्णांक snd_gf1_समयr1_stop(काष्ठा snd_समयr * समयr)
अणु
	अचिन्हित दीर्घ flags;
	अचिन्हित अक्षर पंचांगp;
	काष्ठा snd_gus_card *gus;

	gus = snd_समयr_chip(समयr);
	spin_lock_irqsave(&gus->reg_lock, flags);
	पंचांगp = (gus->gf1.समयr_enabled &= ~4);
	snd_gf1_ग_लिखो8(gus, SNDRV_GF1_GB_SOUND_BLASTER_CONTROL, पंचांगp);	/* disable समयr #1 */
	spin_unlock_irqrestore(&gus->reg_lock, flags);
	वापस 0;
पूर्ण

/*
 *  Timer 2 - 320us
 */

अटल पूर्णांक snd_gf1_समयr2_start(काष्ठा snd_समयr * समयr)
अणु
	अचिन्हित दीर्घ flags;
	अचिन्हित अक्षर पंचांगp;
	अचिन्हित पूर्णांक ticks;
	काष्ठा snd_gus_card *gus;

	gus = snd_समयr_chip(समयr);
	spin_lock_irqsave(&gus->reg_lock, flags);
	ticks = समयr->sticks;
	पंचांगp = (gus->gf1.समयr_enabled |= 8);
	snd_gf1_ग_लिखो8(gus, SNDRV_GF1_GB_ADLIB_TIMER_2, 256 - ticks);	/* समयr 2 count */
	snd_gf1_ग_लिखो8(gus, SNDRV_GF1_GB_SOUND_BLASTER_CONTROL, पंचांगp);	/* enable समयr 2 IRQ */
	snd_gf1_adlib_ग_लिखो(gus, 0x04, पंचांगp >> 2);	/* समयr 2 start */
	spin_unlock_irqrestore(&gus->reg_lock, flags);
	वापस 0;
पूर्ण

अटल पूर्णांक snd_gf1_समयr2_stop(काष्ठा snd_समयr * समयr)
अणु
	अचिन्हित दीर्घ flags;
	अचिन्हित अक्षर पंचांगp;
	काष्ठा snd_gus_card *gus;

	gus = snd_समयr_chip(समयr);
	spin_lock_irqsave(&gus->reg_lock, flags);
	पंचांगp = (gus->gf1.समयr_enabled &= ~8);
	snd_gf1_ग_लिखो8(gus, SNDRV_GF1_GB_SOUND_BLASTER_CONTROL, पंचांगp);	/* disable समयr #1 */
	spin_unlock_irqrestore(&gus->reg_lock, flags);
	वापस 0;
पूर्ण

/*

 */

अटल व्योम snd_gf1_पूर्णांकerrupt_समयr1(काष्ठा snd_gus_card * gus)
अणु
	काष्ठा snd_समयr *समयr = gus->gf1.समयr1;

	अगर (समयr == शून्य)
		वापस;
	snd_समयr_पूर्णांकerrupt(समयr, समयr->sticks);
पूर्ण

अटल व्योम snd_gf1_पूर्णांकerrupt_समयr2(काष्ठा snd_gus_card * gus)
अणु
	काष्ठा snd_समयr *समयr = gus->gf1.समयr2;

	अगर (समयr == शून्य)
		वापस;
	snd_समयr_पूर्णांकerrupt(समयr, समयr->sticks);
पूर्ण

/*

 */

अटल स्थिर काष्ठा snd_समयr_hardware snd_gf1_समयr1 =
अणु
	.flags =	SNDRV_TIMER_HW_STOP,
	.resolution =	80000,
	.ticks =	256,
	.start =	snd_gf1_समयr1_start,
	.stop =		snd_gf1_समयr1_stop,
पूर्ण;

अटल स्थिर काष्ठा snd_समयr_hardware snd_gf1_समयr2 =
अणु
	.flags =	SNDRV_TIMER_HW_STOP,
	.resolution =	320000,
	.ticks =	256,
	.start =	snd_gf1_समयr2_start,
	.stop =		snd_gf1_समयr2_stop,
पूर्ण;

अटल व्योम snd_gf1_समयr1_मुक्त(काष्ठा snd_समयr *समयr)
अणु
	काष्ठा snd_gus_card *gus = समयr->निजी_data;
	gus->gf1.समयr1 = शून्य;
पूर्ण

अटल व्योम snd_gf1_समयr2_मुक्त(काष्ठा snd_समयr *समयr)
अणु
	काष्ठा snd_gus_card *gus = समयr->निजी_data;
	gus->gf1.समयr2 = शून्य;
पूर्ण

व्योम snd_gf1_समयrs_init(काष्ठा snd_gus_card * gus)
अणु
	काष्ठा snd_समयr *समयr;
	काष्ठा snd_समयr_id tid;

	अगर (gus->gf1.समयr1 != शून्य || gus->gf1.समयr2 != शून्य)
		वापस;

	gus->gf1.पूर्णांकerrupt_handler_समयr1 = snd_gf1_पूर्णांकerrupt_समयr1;
	gus->gf1.पूर्णांकerrupt_handler_समयr2 = snd_gf1_पूर्णांकerrupt_समयr2;

	tid.dev_class = SNDRV_TIMER_CLASS_CARD;
	tid.dev_sclass = SNDRV_TIMER_SCLASS_NONE;
	tid.card = gus->card->number;
	tid.device = gus->समयr_dev;
	tid.subdevice = 0;

	अगर (snd_समयr_new(gus->card, "GF1 timer", &tid, &समयr) >= 0) अणु
		म_नकल(समयr->name, "GF1 timer #1");
		समयr->निजी_data = gus;
		समयr->निजी_मुक्त = snd_gf1_समयr1_मुक्त;
		समयr->hw = snd_gf1_समयr1;
	पूर्ण
	gus->gf1.समयr1 = समयr;

	tid.device++;

	अगर (snd_समयr_new(gus->card, "GF1 timer", &tid, &समयr) >= 0) अणु
		म_नकल(समयr->name, "GF1 timer #2");
		समयr->निजी_data = gus;
		समयr->निजी_मुक्त = snd_gf1_समयr2_मुक्त;
		समयr->hw = snd_gf1_समयr2;
	पूर्ण
	gus->gf1.समयr2 = समयr;
पूर्ण

व्योम snd_gf1_समयrs_करोne(काष्ठा snd_gus_card * gus)
अणु
	snd_gf1_set_शेष_handlers(gus, SNDRV_GF1_HANDLER_TIMER1 | SNDRV_GF1_HANDLER_TIMER2);
	अगर (gus->gf1.समयr1) अणु
		snd_device_मुक्त(gus->card, gus->gf1.समयr1);
		gus->gf1.समयr1 = शून्य;
	पूर्ण
	अगर (gus->gf1.समयr2) अणु
		snd_device_मुक्त(gus->card, gus->gf1.समयr2);
		gus->gf1.समयr2 = शून्य;
	पूर्ण
पूर्ण
