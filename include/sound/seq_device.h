<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
#अगर_अघोषित __SOUND_SEQ_DEVICE_H
#घोषणा __SOUND_SEQ_DEVICE_H

/*
 *  ALSA sequencer device management
 *  Copyright (c) 1999 by Takashi Iwai <tiwai@suse.de>
 */

/*
 * रेजिस्टरed device inक्रमmation
 */

काष्ठा snd_seq_device अणु
	/* device info */
	काष्ठा snd_card *card;	/* sound card */
	पूर्णांक device;		/* device number */
	स्थिर अक्षर *id;		/* driver id */
	अक्षर name[80];		/* device name */
	पूर्णांक argsize;		/* size of the argument */
	व्योम *driver_data;	/* निजी data क्रम driver */
	व्योम *निजी_data;	/* निजी data क्रम the caller */
	व्योम (*निजी_मुक्त)(काष्ठा snd_seq_device *device);
	काष्ठा device dev;
पूर्ण;

#घोषणा to_seq_dev(_dev) \
	container_of(_dev, काष्ठा snd_seq_device, dev)

/* sequencer driver */

/* driver चालकs
 * probe:
 *	Initialize the device with given parameters.
 *	Typically,
 *		1. call snd_hwdep_new
 *		2. allocate निजी data and initialize it
 *		3. call snd_hwdep_रेजिस्टर
 *		4. store the instance to dev->driver_data poपूर्णांकer.
 *		
 * हटाओ:
 *	Release the निजी data.
 *	Typically, call snd_device_मुक्त(dev->card, dev->driver_data)
 */
काष्ठा snd_seq_driver अणु
	काष्ठा device_driver driver;
	अक्षर *id;
	पूर्णांक argsize;
पूर्ण;

#घोषणा to_seq_drv(_drv) \
	container_of(_drv, काष्ठा snd_seq_driver, driver)

/*
 * prototypes
 */
#अगर_घोषित CONFIG_MODULES
व्योम snd_seq_device_load_drivers(व्योम);
#अन्यथा
#घोषणा snd_seq_device_load_drivers()
#पूर्ण_अगर
पूर्णांक snd_seq_device_new(काष्ठा snd_card *card, पूर्णांक device, स्थिर अक्षर *id,
		       पूर्णांक argsize, काष्ठा snd_seq_device **result);

#घोषणा SNDRV_SEQ_DEVICE_ARGPTR(dev) (व्योम *)((अक्षर *)(dev) + माप(काष्ठा snd_seq_device))

पूर्णांक __must_check __snd_seq_driver_रेजिस्टर(काष्ठा snd_seq_driver *drv,
					   काष्ठा module *mod);
#घोषणा snd_seq_driver_रेजिस्टर(drv) \
	__snd_seq_driver_रेजिस्टर(drv, THIS_MODULE)
व्योम snd_seq_driver_unरेजिस्टर(काष्ठा snd_seq_driver *drv);

#घोषणा module_snd_seq_driver(drv) \
	module_driver(drv, snd_seq_driver_रेजिस्टर, snd_seq_driver_unरेजिस्टर)

/*
 * id strings क्रम generic devices
 */
#घोषणा SNDRV_SEQ_DEV_ID_MIDISYNTH	"seq-midi"
#घोषणा SNDRV_SEQ_DEV_ID_OPL3		"opl3-synth"

#पूर्ण_अगर /* __SOUND_SEQ_DEVICE_H */
