<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0+ */
/*
 * Digital Beep Input Interface क्रम HD-audio codec
 *
 * Author: Matt Ranostay <matt.ranostay@konsulko.com>
 * Copyright (c) 2008 Embedded Alley Solutions Inc
 */

#अगर_अघोषित __SOUND_HDA_BEEP_H
#घोषणा __SOUND_HDA_BEEP_H

#समावेश <sound/hda_codec.h>

#घोषणा HDA_BEEP_MODE_OFF	0
#घोषणा HDA_BEEP_MODE_ON	1

/* beep inक्रमmation */
काष्ठा hda_beep अणु
	काष्ठा input_dev *dev;
	काष्ठा hda_codec *codec;
	अक्षर phys[32];
	पूर्णांक tone;
	hda_nid_t nid;
	अचिन्हित पूर्णांक रेजिस्टरed:1;
	अचिन्हित पूर्णांक enabled:1;
	अचिन्हित पूर्णांक linear_tone:1;	/* linear tone क्रम IDT/STAC codec */
	अचिन्हित पूर्णांक playing:1;
	काष्ठा work_काष्ठा beep_work; /* scheduled task क्रम beep event */
	काष्ठा mutex mutex;
	व्योम (*घातer_hook)(काष्ठा hda_beep *beep, bool on);
पूर्ण;

#अगर_घोषित CONFIG_SND_HDA_INPUT_BEEP
पूर्णांक snd_hda_enable_beep_device(काष्ठा hda_codec *codec, पूर्णांक enable);
पूर्णांक snd_hda_attach_beep_device(काष्ठा hda_codec *codec, पूर्णांक nid);
व्योम snd_hda_detach_beep_device(काष्ठा hda_codec *codec);
#अन्यथा
अटल अंतरभूत पूर्णांक snd_hda_attach_beep_device(काष्ठा hda_codec *codec, पूर्णांक nid)
अणु
	वापस 0;
पूर्ण
अटल अंतरभूत व्योम snd_hda_detach_beep_device(काष्ठा hda_codec *codec)
अणु
पूर्ण
#पूर्ण_अगर
#पूर्ण_अगर
