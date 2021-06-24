<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Beep using pcm
 *
 * Copyright (c) by Takashi Iwai <tiwai@suse.de>
 */

#समावेश <linux/पन.स>
#समावेश <यंत्र/irq.h>
#समावेश <linux/init.h>
#समावेश <linux/slab.h>
#समावेश <linux/input.h>
#समावेश <linux/pci.h>
#समावेश <linux/dma-mapping.h>
#समावेश <sound/core.h>
#समावेश <sound/control.h>
#समावेश "pmac.h"

काष्ठा pmac_beep अणु
	पूर्णांक running;		/* boolean */
	पूर्णांक volume;		/* mixer volume: 0-100 */
	पूर्णांक volume_play;	/* currently playing volume */
	पूर्णांक hz;
	पूर्णांक nsamples;
	लघु *buf;		/* allocated wave buffer */
	dma_addr_t addr;	/* physical address of buffer */
	काष्ठा input_dev *dev;
पूर्ण;

/*
 * stop beep अगर running
 */
व्योम snd_pmac_beep_stop(काष्ठा snd_pmac *chip)
अणु
	काष्ठा pmac_beep *beep = chip->beep;
	अगर (beep && beep->running) अणु
		beep->running = 0;
		snd_pmac_beep_dma_stop(chip);
	पूर्ण
पूर्ण

/*
 * Stuff क्रम outputting a beep.  The values range from -327 to +327
 * so we can multiply by an amplitude in the range 0..100 to get a
 * चिन्हित लघु value to put in the output buffer.
 */
अटल स्थिर लघु beep_wक्रमm[256] = अणु
	0,	40,	79,	117,	153,	187,	218,	245,
	269,	288,	304,	316,	323,	327,	327,	324,
	318,	310,	299,	288,	275,	262,	249,	236,
	224,	213,	204,	196,	190,	186,	183,	182,
	182,	183,	186,	189,	192,	196,	200,	203,
	206,	208,	209,	209,	209,	207,	204,	201,
	197,	193,	188,	183,	179,	174,	170,	166,
	163,	161,	160,	159,	159,	160,	161,	162,
	164,	166,	168,	169,	171,	171,	171,	170,
	169,	167,	163,	159,	155,	150,	144,	139,
	133,	128,	122,	117,	113,	110,	107,	105,
	103,	103,	103,	103,	104,	104,	105,	105,
	105,	103,	101,	97,	92,	86,	78,	68,
	58,	45,	32,	18,	3,	-11,	-26,	-41,
	-55,	-68,	-79,	-88,	-95,	-100,	-102,	-102,
	-99,	-93,	-85,	-75,	-62,	-48,	-33,	-16,
	0,	16,	33,	48,	62,	75,	85,	93,
	99,	102,	102,	100,	95,	88,	79,	68,
	55,	41,	26,	11,	-3,	-18,	-32,	-45,
	-58,	-68,	-78,	-86,	-92,	-97,	-101,	-103,
	-105,	-105,	-105,	-104,	-104,	-103,	-103,	-103,
	-103,	-105,	-107,	-110,	-113,	-117,	-122,	-128,
	-133,	-139,	-144,	-150,	-155,	-159,	-163,	-167,
	-169,	-170,	-171,	-171,	-171,	-169,	-168,	-166,
	-164,	-162,	-161,	-160,	-159,	-159,	-160,	-161,
	-163,	-166,	-170,	-174,	-179,	-183,	-188,	-193,
	-197,	-201,	-204,	-207,	-209,	-209,	-209,	-208,
	-206,	-203,	-200,	-196,	-192,	-189,	-186,	-183,
	-182,	-182,	-183,	-186,	-190,	-196,	-204,	-213,
	-224,	-236,	-249,	-262,	-275,	-288,	-299,	-310,
	-318,	-324,	-327,	-327,	-323,	-316,	-304,	-288,
	-269,	-245,	-218,	-187,	-153,	-117,	-79,	-40,
पूर्ण;

#घोषणा BEEP_SRATE	22050	/* 22050 Hz sample rate */
#घोषणा BEEP_BUFLEN	512
#घोषणा BEEP_VOLUME	15	/* 0 - 100 */

अटल पूर्णांक snd_pmac_beep_event(काष्ठा input_dev *dev, अचिन्हित पूर्णांक type,
			       अचिन्हित पूर्णांक code, पूर्णांक hz)
अणु
	काष्ठा snd_pmac *chip;
	काष्ठा pmac_beep *beep;
	अचिन्हित दीर्घ flags;
	पूर्णांक beep_speed = 0;
	पूर्णांक srate;
	पूर्णांक period, ncycles, nsamples;
	पूर्णांक i, j, f;
	लघु *p;

	अगर (type != EV_SND)
		वापस -1;

	चयन (code) अणु
	हाल SND_BELL: अगर (hz) hz = 1000;
	हाल SND_TONE: अवरोध;
	शेष: वापस -1;
	पूर्ण

	chip = input_get_drvdata(dev);
	अगर (! chip || (beep = chip->beep) == शून्य)
		वापस -1;

	अगर (! hz) अणु
		spin_lock_irqsave(&chip->reg_lock, flags);
		अगर (beep->running)
			snd_pmac_beep_stop(chip);
		spin_unlock_irqrestore(&chip->reg_lock, flags);
		वापस 0;
	पूर्ण

	beep_speed = snd_pmac_rate_index(chip, &chip->playback, BEEP_SRATE);
	srate = chip->freq_table[beep_speed];

	अगर (hz <= srate / BEEP_BUFLEN || hz > srate / 2)
		hz = 1000;

	spin_lock_irqsave(&chip->reg_lock, flags);
	अगर (chip->playback.running || chip->capture.running || beep->running) अणु
		spin_unlock_irqrestore(&chip->reg_lock, flags);
		वापस 0;
	पूर्ण
	beep->running = 1;
	spin_unlock_irqrestore(&chip->reg_lock, flags);

	अगर (hz == beep->hz && beep->volume == beep->volume_play) अणु
		nsamples = beep->nsamples;
	पूर्ण अन्यथा अणु
		period = srate * 256 / hz;	/* fixed poपूर्णांक */
		ncycles = BEEP_BUFLEN * 256 / period;
		nsamples = (period * ncycles) >> 8;
		f = ncycles * 65536 / nsamples;
		j = 0;
		p = beep->buf;
		क्रम (i = 0; i < nsamples; ++i, p += 2) अणु
			p[0] = p[1] = beep_wक्रमm[j >> 8] * beep->volume;
			j = (j + f) & 0xffff;
		पूर्ण
		beep->hz = hz;
		beep->volume_play = beep->volume;
		beep->nsamples = nsamples;
	पूर्ण

	spin_lock_irqsave(&chip->reg_lock, flags);
	snd_pmac_beep_dma_start(chip, beep->nsamples * 4, beep->addr, beep_speed);
	spin_unlock_irqrestore(&chip->reg_lock, flags);
	वापस 0;
पूर्ण

/*
 * beep volume mixer
 */

अटल पूर्णांक snd_pmac_info_beep(काष्ठा snd_kcontrol *kcontrol,
			      काष्ठा snd_ctl_elem_info *uinfo)
अणु
	uinfo->type = SNDRV_CTL_ELEM_TYPE_INTEGER;
	uinfo->count = 1;
	uinfo->value.पूर्णांकeger.min = 0;
	uinfo->value.पूर्णांकeger.max = 100;
	वापस 0;
पूर्ण

अटल पूर्णांक snd_pmac_get_beep(काष्ठा snd_kcontrol *kcontrol,
			     काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_pmac *chip = snd_kcontrol_chip(kcontrol);
	अगर (snd_BUG_ON(!chip->beep))
		वापस -ENXIO;
	ucontrol->value.पूर्णांकeger.value[0] = chip->beep->volume;
	वापस 0;
पूर्ण

अटल पूर्णांक snd_pmac_put_beep(काष्ठा snd_kcontrol *kcontrol,
			     काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_pmac *chip = snd_kcontrol_chip(kcontrol);
	अचिन्हित पूर्णांक oval, nval;
	अगर (snd_BUG_ON(!chip->beep))
		वापस -ENXIO;
	oval = chip->beep->volume;
	nval = ucontrol->value.पूर्णांकeger.value[0];
	अगर (nval > 100)
		वापस -EINVAL;
	chip->beep->volume = nval;
	वापस oval != chip->beep->volume;
पूर्ण

अटल स्थिर काष्ठा snd_kcontrol_new snd_pmac_beep_mixer = अणु
	.अगरace = SNDRV_CTL_ELEM_IFACE_MIXER,
	.name = "Beep Playback Volume",
	.info = snd_pmac_info_beep,
	.get = snd_pmac_get_beep,
	.put = snd_pmac_put_beep,
पूर्ण;

/* Initialize beep stuff */
पूर्णांक snd_pmac_attach_beep(काष्ठा snd_pmac *chip)
अणु
	काष्ठा pmac_beep *beep;
	काष्ठा input_dev *input_dev;
	काष्ठा snd_kcontrol *beep_ctl;
	व्योम *dmabuf;
	पूर्णांक err = -ENOMEM;

	beep = kzalloc(माप(*beep), GFP_KERNEL);
	अगर (! beep)
		वापस -ENOMEM;
	dmabuf = dma_alloc_coherent(&chip->pdev->dev, BEEP_BUFLEN * 4,
				    &beep->addr, GFP_KERNEL);
	input_dev = input_allocate_device();
	अगर (! dmabuf || ! input_dev)
		जाओ fail1;

	/* FIXME: set more better values */
	input_dev->name = "PowerMac Beep";
	input_dev->phys = "powermac/beep";
	input_dev->id.bustype = BUS_ADB;
	input_dev->id.venकरोr = 0x001f;
	input_dev->id.product = 0x0001;
	input_dev->id.version = 0x0100;

	input_dev->evbit[0] = BIT_MASK(EV_SND);
	input_dev->sndbit[0] = BIT_MASK(SND_BELL) | BIT_MASK(SND_TONE);
	input_dev->event = snd_pmac_beep_event;
	input_dev->dev.parent = &chip->pdev->dev;
	input_set_drvdata(input_dev, chip);

	beep->dev = input_dev;
	beep->buf = dmabuf;
	beep->volume = BEEP_VOLUME;
	beep->running = 0;

	beep_ctl = snd_ctl_new1(&snd_pmac_beep_mixer, chip);
	err = snd_ctl_add(chip->card, beep_ctl);
	अगर (err < 0)
		जाओ fail1;

	chip->beep = beep;

	err = input_रेजिस्टर_device(beep->dev);
	अगर (err)
		जाओ fail2;
 
 	वापस 0;
 
 fail2:	snd_ctl_हटाओ(chip->card, beep_ctl);
 fail1:	input_मुक्त_device(input_dev);
	अगर (dmabuf)
		dma_मुक्त_coherent(&chip->pdev->dev, BEEP_BUFLEN * 4,
				  dmabuf, beep->addr);
	kमुक्त(beep);
	वापस err;
पूर्ण

व्योम snd_pmac_detach_beep(काष्ठा snd_pmac *chip)
अणु
	अगर (chip->beep) अणु
		input_unरेजिस्टर_device(chip->beep->dev);
		dma_मुक्त_coherent(&chip->pdev->dev, BEEP_BUFLEN * 4,
				  chip->beep->buf, chip->beep->addr);
		kमुक्त(chip->beep);
		chip->beep = शून्य;
	पूर्ण
पूर्ण
