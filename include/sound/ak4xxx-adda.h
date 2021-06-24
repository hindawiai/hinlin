<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
#अगर_अघोषित __SOUND_AK4XXX_ADDA_H
#घोषणा __SOUND_AK4XXX_ADDA_H

/*
 *   ALSA driver क्रम AK4524 / AK4528 / AK4529 / AK4355 / AK4381
 *   AD and DA converters
 *
 *	Copyright (c) 2000 Jaroslav Kysela <perex@perex.cz>
 */      

#अगर_अघोषित AK4XXX_MAX_CHIPS
#घोषणा AK4XXX_MAX_CHIPS	4
#पूर्ण_अगर

काष्ठा snd_akm4xxx;

काष्ठा snd_ak4xxx_ops अणु
	व्योम (*lock)(काष्ठा snd_akm4xxx *ak, पूर्णांक chip);
	व्योम (*unlock)(काष्ठा snd_akm4xxx *ak, पूर्णांक chip);
	व्योम (*ग_लिखो)(काष्ठा snd_akm4xxx *ak, पूर्णांक chip, अचिन्हित अक्षर reg,
		      अचिन्हित अक्षर val);
	व्योम (*set_rate_val)(काष्ठा snd_akm4xxx *ak, अचिन्हित पूर्णांक rate);
पूर्ण;

#घोषणा AK4XXX_IMAGE_SIZE	(AK4XXX_MAX_CHIPS * 16)	/* 64 bytes */

/* DAC label and channels */
काष्ठा snd_akm4xxx_dac_channel अणु
	अक्षर *name;		/* mixer volume name */
	अचिन्हित पूर्णांक num_channels;
	अक्षर *चयन_name;		/* mixer चयन*/
पूर्ण;

/* ADC labels and channels */
काष्ठा snd_akm4xxx_adc_channel अणु
	अक्षर *name;		/* capture gain volume label */
	अक्षर *चयन_name;	/* capture चयन */
	अचिन्हित पूर्णांक num_channels;
	अक्षर *selector_name;	/* capture source select label */
	स्थिर अक्षर **input_names; /* capture source names (शून्य terminated) */
पूर्ण;

काष्ठा snd_akm4xxx अणु
	काष्ठा snd_card *card;
	अचिन्हित पूर्णांक num_adcs;			/* AK4524 or AK4528 ADCs */
	अचिन्हित पूर्णांक num_dacs;			/* AK4524 or AK4528 DACs */
	अचिन्हित अक्षर images[AK4XXX_IMAGE_SIZE]; /* saved रेजिस्टर image */
	अचिन्हित अक्षर volumes[AK4XXX_IMAGE_SIZE]; /* saved volume values */
	अचिन्हित दीर्घ निजी_value[AK4XXX_MAX_CHIPS];	/* helper क्रम driver */
	व्योम *निजी_data[AK4XXX_MAX_CHIPS];		/* helper क्रम driver */
	/* ढाँचा should fill the following fields */
	अचिन्हित पूर्णांक idx_offset;		/* control index offset */
	क्रमागत अणु
		SND_AK4524, SND_AK4528, SND_AK4529,
		SND_AK4355, SND_AK4358, SND_AK4381,
		SND_AK5365, SND_AK4620,
	पूर्ण type;

	/* (array) inक्रमmation of combined codecs */
	स्थिर काष्ठा snd_akm4xxx_dac_channel *dac_info;
	स्थिर काष्ठा snd_akm4xxx_adc_channel *adc_info;

	काष्ठा snd_ak4xxx_ops ops;
	अचिन्हित पूर्णांक num_chips;
	अचिन्हित पूर्णांक total_regs;
	स्थिर अक्षर *name;
पूर्ण;

व्योम snd_akm4xxx_ग_लिखो(काष्ठा snd_akm4xxx *ak, पूर्णांक chip, अचिन्हित अक्षर reg,
		       अचिन्हित अक्षर val);
व्योम snd_akm4xxx_reset(काष्ठा snd_akm4xxx *ak, पूर्णांक state);
व्योम snd_akm4xxx_init(काष्ठा snd_akm4xxx *ak);
पूर्णांक snd_akm4xxx_build_controls(काष्ठा snd_akm4xxx *ak);

#घोषणा snd_akm4xxx_get(ak,chip,reg) \
	(ak)->images[(chip) * 16 + (reg)]
#घोषणा snd_akm4xxx_set(ak,chip,reg,val) \
	((ak)->images[(chip) * 16 + (reg)] = (val))
#घोषणा snd_akm4xxx_get_vol(ak,chip,reg) \
	(ak)->volumes[(chip) * 16 + (reg)]
#घोषणा snd_akm4xxx_set_vol(ak,chip,reg,val) \
	((ak)->volumes[(chip) * 16 + (reg)] = (val))

#पूर्ण_अगर /* __SOUND_AK4XXX_ADDA_H */
