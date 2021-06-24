<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
#अगर_अघोषित __SOUND_JACK_H
#घोषणा __SOUND_JACK_H

/*
 *  Jack असलtraction layer
 *
 *  Copyright 2008 Wolfson Microelectronics plc
 */

#समावेश <sound/core.h>

काष्ठा input_dev;

/**
 * क्रमागत snd_jack_types - Jack types which can be reported
 * @SND_JACK_HEADPHONE: Headphone
 * @SND_JACK_MICROPHONE: Microphone
 * @SND_JACK_HEADSET: Headset
 * @SND_JACK_LINEOUT: Line out
 * @SND_JACK_MECHANICAL: Mechanical चयन
 * @SND_JACK_VIDEOOUT: Video out
 * @SND_JACK_AVOUT: AV (Audio Video) out
 * @SND_JACK_LINEIN:  Line in
 * @SND_JACK_BTN_0: Button 0
 * @SND_JACK_BTN_1: Button 1
 * @SND_JACK_BTN_2: Button 2
 * @SND_JACK_BTN_3: Button 3
 * @SND_JACK_BTN_4: Button 4
 * @SND_JACK_BTN_5: Button 5
 *
 * These values are used as a biपंचांगask.
 *
 * Note that this must be kept in sync with the lookup table in
 * sound/core/jack.c.
 */
क्रमागत snd_jack_types अणु
	SND_JACK_HEADPHONE	= 0x0001,
	SND_JACK_MICROPHONE	= 0x0002,
	SND_JACK_HEADSET	= SND_JACK_HEADPHONE | SND_JACK_MICROPHONE,
	SND_JACK_LINEOUT	= 0x0004,
	SND_JACK_MECHANICAL	= 0x0008, /* If detected separately */
	SND_JACK_VIDEOOUT	= 0x0010,
	SND_JACK_AVOUT		= SND_JACK_LINEOUT | SND_JACK_VIDEOOUT,
	SND_JACK_LINEIN		= 0x0020,

	/* Kept separate from चयनes to facilitate implementation */
	SND_JACK_BTN_0		= 0x4000,
	SND_JACK_BTN_1		= 0x2000,
	SND_JACK_BTN_2		= 0x1000,
	SND_JACK_BTN_3		= 0x0800,
	SND_JACK_BTN_4		= 0x0400,
	SND_JACK_BTN_5		= 0x0200,
पूर्ण;

/* Keep in sync with definitions above */
#घोषणा SND_JACK_SWITCH_TYPES 6

काष्ठा snd_jack अणु
	काष्ठा list_head kctl_list;
	काष्ठा snd_card *card;
	स्थिर अक्षर *id;
#अगर_घोषित CONFIG_SND_JACK_INPUT_DEV
	काष्ठा input_dev *input_dev;
	पूर्णांक रेजिस्टरed;
	पूर्णांक type;
	अक्षर name[100];
	अचिन्हित पूर्णांक key[6];   /* Keep in sync with definitions above */
#पूर्ण_अगर /* CONFIG_SND_JACK_INPUT_DEV */
	पूर्णांक hw_status_cache;
	व्योम *निजी_data;
	व्योम (*निजी_मुक्त)(काष्ठा snd_jack *);
पूर्ण;

#अगर_घोषित CONFIG_SND_JACK

पूर्णांक snd_jack_new(काष्ठा snd_card *card, स्थिर अक्षर *id, पूर्णांक type,
		 काष्ठा snd_jack **jack, bool initial_kctl, bool phantom_jack);
पूर्णांक snd_jack_add_new_kctl(काष्ठा snd_jack *jack, स्थिर अक्षर * name, पूर्णांक mask);
#अगर_घोषित CONFIG_SND_JACK_INPUT_DEV
व्योम snd_jack_set_parent(काष्ठा snd_jack *jack, काष्ठा device *parent);
पूर्णांक snd_jack_set_key(काष्ठा snd_jack *jack, क्रमागत snd_jack_types type,
		     पूर्णांक keytype);
#पूर्ण_अगर
व्योम snd_jack_report(काष्ठा snd_jack *jack, पूर्णांक status);

#अन्यथा
अटल अंतरभूत पूर्णांक snd_jack_new(काष्ठा snd_card *card, स्थिर अक्षर *id, पूर्णांक type,
			       काष्ठा snd_jack **jack, bool initial_kctl, bool phantom_jack)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक snd_jack_add_new_kctl(काष्ठा snd_jack *jack, स्थिर अक्षर * name, पूर्णांक mask)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत व्योम snd_jack_report(काष्ठा snd_jack *jack, पूर्णांक status)
अणु
पूर्ण

#पूर्ण_अगर

#अगर !defined(CONFIG_SND_JACK) || !defined(CONFIG_SND_JACK_INPUT_DEV)
अटल अंतरभूत व्योम snd_jack_set_parent(काष्ठा snd_jack *jack,
				       काष्ठा device *parent)
अणु
पूर्ण

अटल अंतरभूत पूर्णांक snd_jack_set_key(काष्ठा snd_jack *jack,
				   क्रमागत snd_jack_types type,
				   पूर्णांक keytype)
अणु
	वापस 0;
पूर्ण
#पूर्ण_अगर /* !CONFIG_SND_JACK || !CONFIG_SND_JACK_INPUT_DEV */

#पूर्ण_अगर
