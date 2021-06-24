<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * Digital Beep Input Interface क्रम HD-audio codec
 *
 * Author: Matt Ranostay <matt.ranostay@konsulko.com>
 * Copyright (c) 2008 Embedded Alley Solutions Inc
 */

#समावेश <linux/input.h>
#समावेश <linux/slab.h>
#समावेश <linux/workqueue.h>
#समावेश <linux/export.h>
#समावेश <sound/core.h>
#समावेश "hda_beep.h"
#समावेश "hda_local.h"

क्रमागत अणु
	DIGBEEP_HZ_STEP = 46875,	/* 46.875 Hz */
	DIGBEEP_HZ_MIN = 93750,		/* 93.750 Hz */
	DIGBEEP_HZ_MAX = 12000000,	/* 12 KHz */
पूर्ण;

/* generate or stop tone */
अटल व्योम generate_tone(काष्ठा hda_beep *beep, पूर्णांक tone)
अणु
	काष्ठा hda_codec *codec = beep->codec;

	अगर (tone && !beep->playing) अणु
		snd_hda_घातer_up(codec);
		अगर (beep->घातer_hook)
			beep->घातer_hook(beep, true);
		beep->playing = 1;
	पूर्ण
	snd_hda_codec_ग_लिखो(codec, beep->nid, 0,
			    AC_VERB_SET_BEEP_CONTROL, tone);
	अगर (!tone && beep->playing) अणु
		beep->playing = 0;
		अगर (beep->घातer_hook)
			beep->घातer_hook(beep, false);
		snd_hda_घातer_करोwn(codec);
	पूर्ण
पूर्ण

अटल व्योम snd_hda_generate_beep(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा hda_beep *beep =
		container_of(work, काष्ठा hda_beep, beep_work);

	अगर (beep->enabled)
		generate_tone(beep, beep->tone);
पूर्ण

/* (non-standard) Linear beep tone calculation क्रम IDT/STAC codecs 
 *
 * The tone frequency of beep generator on IDT/STAC codecs is
 * defined from the 8bit tone parameter, in Hz,
 *    freq = 48000 * (257 - tone) / 1024
 * that is from 12kHz to 93.75Hz in steps of 46.875 Hz
 */
अटल पूर्णांक beep_linear_tone(काष्ठा hda_beep *beep, पूर्णांक hz)
अणु
	अगर (hz <= 0)
		वापस 0;
	hz *= 1000; /* fixed poपूर्णांक */
	hz = hz - DIGBEEP_HZ_MIN
		+ DIGBEEP_HZ_STEP / 2; /* round to nearest step */
	अगर (hz < 0)
		hz = 0; /* turn off PC beep*/
	अन्यथा अगर (hz >= (DIGBEEP_HZ_MAX - DIGBEEP_HZ_MIN))
		hz = 1; /* max frequency */
	अन्यथा अणु
		hz /= DIGBEEP_HZ_STEP;
		hz = 255 - hz;
	पूर्ण
	वापस hz;
पूर्ण

/* HD-audio standard beep tone parameter calculation
 *
 * The tone frequency in Hz is calculated as
 *   freq = 48000 / (tone * 4)
 * from 47Hz to 12kHz
 */
अटल पूर्णांक beep_standard_tone(काष्ठा hda_beep *beep, पूर्णांक hz)
अणु
	अगर (hz <= 0)
		वापस 0; /* disabled */
	hz = 12000 / hz;
	अगर (hz > 0xff)
		वापस 0xff;
	अगर (hz <= 0)
		वापस 1;
	वापस hz;
पूर्ण

अटल पूर्णांक snd_hda_beep_event(काष्ठा input_dev *dev, अचिन्हित पूर्णांक type,
				अचिन्हित पूर्णांक code, पूर्णांक hz)
अणु
	काष्ठा hda_beep *beep = input_get_drvdata(dev);

	चयन (code) अणु
	हाल SND_BELL:
		अगर (hz)
			hz = 1000;
		fallthrough;
	हाल SND_TONE:
		अगर (beep->linear_tone)
			beep->tone = beep_linear_tone(beep, hz);
		अन्यथा
			beep->tone = beep_standard_tone(beep, hz);
		अवरोध;
	शेष:
		वापस -1;
	पूर्ण

	/* schedule beep event */
	schedule_work(&beep->beep_work);
	वापस 0;
पूर्ण

अटल व्योम turn_off_beep(काष्ठा hda_beep *beep)
अणु
	cancel_work_sync(&beep->beep_work);
	अगर (beep->playing) अणु
		/* turn off beep */
		generate_tone(beep, 0);
	पूर्ण
पूर्ण

/**
 * snd_hda_enable_beep_device - Turn on/off beep sound
 * @codec: the HDA codec
 * @enable: flag to turn on/off
 */
पूर्णांक snd_hda_enable_beep_device(काष्ठा hda_codec *codec, पूर्णांक enable)
अणु
	काष्ठा hda_beep *beep = codec->beep;
	अगर (!beep)
		वापस 0;
	enable = !!enable;
	अगर (beep->enabled != enable) अणु
		beep->enabled = enable;
		अगर (!enable)
			turn_off_beep(beep);
		वापस 1;
	पूर्ण
	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(snd_hda_enable_beep_device);

अटल पूर्णांक beep_dev_रेजिस्टर(काष्ठा snd_device *device)
अणु
	काष्ठा hda_beep *beep = device->device_data;
	पूर्णांक err;

	err = input_रेजिस्टर_device(beep->dev);
	अगर (!err)
		beep->रेजिस्टरed = true;
	वापस err;
पूर्ण

अटल पूर्णांक beep_dev_disconnect(काष्ठा snd_device *device)
अणु
	काष्ठा hda_beep *beep = device->device_data;

	अगर (beep->रेजिस्टरed)
		input_unरेजिस्टर_device(beep->dev);
	अन्यथा
		input_मुक्त_device(beep->dev);
	turn_off_beep(beep);
	वापस 0;
पूर्ण

अटल पूर्णांक beep_dev_मुक्त(काष्ठा snd_device *device)
अणु
	काष्ठा hda_beep *beep = device->device_data;

	beep->codec->beep = शून्य;
	kमुक्त(beep);
	वापस 0;
पूर्ण

/**
 * snd_hda_attach_beep_device - Attach a beep input device
 * @codec: the HDA codec
 * @nid: beep NID
 *
 * Attach a beep object to the given widget.  If beep hपूर्णांक is turned off
 * explicitly or beep_mode of the codec is turned off, this करोesn't nothing.
 *
 * Currently, only one beep device is allowed to each codec.
 */
पूर्णांक snd_hda_attach_beep_device(काष्ठा hda_codec *codec, पूर्णांक nid)
अणु
	अटल स्थिर काष्ठा snd_device_ops ops = अणु
		.dev_रेजिस्टर = beep_dev_रेजिस्टर,
		.dev_disconnect = beep_dev_disconnect,
		.dev_मुक्त = beep_dev_मुक्त,
	पूर्ण;
	काष्ठा input_dev *input_dev;
	काष्ठा hda_beep *beep;
	पूर्णांक err;

	अगर (!snd_hda_get_bool_hपूर्णांक(codec, "beep"))
		वापस 0; /* disabled explicitly by hपूर्णांकs */
	अगर (codec->beep_mode == HDA_BEEP_MODE_OFF)
		वापस 0; /* disabled by module option */

	beep = kzalloc(माप(*beep), GFP_KERNEL);
	अगर (beep == शून्य)
		वापस -ENOMEM;
	snम_लिखो(beep->phys, माप(beep->phys),
		"card%d/codec#%d/beep0", codec->card->number, codec->addr);
	/* enable linear scale */
	snd_hda_codec_ग_लिखो_cache(codec, nid, 0,
		AC_VERB_SET_DIGI_CONVERT_2, 0x01);

	beep->nid = nid;
	beep->codec = codec;
	codec->beep = beep;

	INIT_WORK(&beep->beep_work, &snd_hda_generate_beep);
	mutex_init(&beep->mutex);

	input_dev = input_allocate_device();
	अगर (!input_dev) अणु
		err = -ENOMEM;
		जाओ err_मुक्त;
	पूर्ण

	/* setup digital beep device */
	input_dev->name = "HDA Digital PCBeep";
	input_dev->phys = beep->phys;
	input_dev->id.bustype = BUS_PCI;
	input_dev->dev.parent = &codec->card->card_dev;

	input_dev->id.venकरोr = codec->core.venकरोr_id >> 16;
	input_dev->id.product = codec->core.venकरोr_id & 0xffff;
	input_dev->id.version = 0x01;

	input_dev->evbit[0] = BIT_MASK(EV_SND);
	input_dev->sndbit[0] = BIT_MASK(SND_BELL) | BIT_MASK(SND_TONE);
	input_dev->event = snd_hda_beep_event;
	input_set_drvdata(input_dev, beep);

	beep->dev = input_dev;

	err = snd_device_new(codec->card, SNDRV_DEV_JACK, beep, &ops);
	अगर (err < 0)
		जाओ err_input;

	वापस 0;

 err_input:
	input_मुक्त_device(beep->dev);
 err_मुक्त:
	kमुक्त(beep);
	codec->beep = शून्य;
	वापस err;
पूर्ण
EXPORT_SYMBOL_GPL(snd_hda_attach_beep_device);

/**
 * snd_hda_detach_beep_device - Detach the beep device
 * @codec: the HDA codec
 */
व्योम snd_hda_detach_beep_device(काष्ठा hda_codec *codec)
अणु
	अगर (!codec->bus->shutकरोwn && codec->beep)
		snd_device_मुक्त(codec->card, codec->beep);
पूर्ण
EXPORT_SYMBOL_GPL(snd_hda_detach_beep_device);

अटल bool ctl_has_mute(काष्ठा snd_kcontrol *kcontrol)
अणु
	काष्ठा hda_codec *codec = snd_kcontrol_chip(kcontrol);
	वापस query_amp_caps(codec, get_amp_nid(kcontrol),
			      get_amp_direction(kcontrol)) & AC_AMPCAP_MUTE;
पूर्ण

/* get/put callbacks क्रम beep mute mixer चयनes */

/**
 * snd_hda_mixer_amp_चयन_get_beep - Get callback क्रम beep controls
 * @kcontrol: ctl element
 * @ucontrol: poपूर्णांकer to get/store the data
 */
पूर्णांक snd_hda_mixer_amp_चयन_get_beep(काष्ठा snd_kcontrol *kcontrol,
				      काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा hda_codec *codec = snd_kcontrol_chip(kcontrol);
	काष्ठा hda_beep *beep = codec->beep;
	पूर्णांक chs = get_amp_channels(kcontrol);

	अगर (beep && (!beep->enabled || !ctl_has_mute(kcontrol))) अणु
		अगर (chs & 1)
			ucontrol->value.पूर्णांकeger.value[0] = beep->enabled;
		अगर (chs & 2)
			ucontrol->value.पूर्णांकeger.value[1] = beep->enabled;
		वापस 0;
	पूर्ण
	वापस snd_hda_mixer_amp_चयन_get(kcontrol, ucontrol);
पूर्ण
EXPORT_SYMBOL_GPL(snd_hda_mixer_amp_चयन_get_beep);

/**
 * snd_hda_mixer_amp_चयन_put_beep - Put callback क्रम beep controls
 * @kcontrol: ctl element
 * @ucontrol: poपूर्णांकer to get/store the data
 */
पूर्णांक snd_hda_mixer_amp_चयन_put_beep(काष्ठा snd_kcontrol *kcontrol,
				      काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा hda_codec *codec = snd_kcontrol_chip(kcontrol);
	काष्ठा hda_beep *beep = codec->beep;
	अगर (beep) अणु
		u8 chs = get_amp_channels(kcontrol);
		पूर्णांक enable = 0;
		दीर्घ *valp = ucontrol->value.पूर्णांकeger.value;
		अगर (chs & 1) अणु
			enable |= *valp;
			valp++;
		पूर्ण
		अगर (chs & 2)
			enable |= *valp;
		snd_hda_enable_beep_device(codec, enable);
	पूर्ण
	अगर (!ctl_has_mute(kcontrol))
		वापस 0;
	वापस snd_hda_mixer_amp_चयन_put(kcontrol, ucontrol);
पूर्ण
EXPORT_SYMBOL_GPL(snd_hda_mixer_amp_चयन_put_beep);
