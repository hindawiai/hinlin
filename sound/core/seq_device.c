<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *  ALSA sequencer device management
 *  Copyright (c) 1999 by Takashi Iwai <tiwai@suse.de>
 *
 *----------------------------------------------------------------
 *
 * This device handler separates the card driver module from sequencer
 * stuff (sequencer core, synth drivers, etc), so that user can aव्योम
 * to spend unnecessary resources e.g. अगर he needs only listening to
 * MP3s.
 *
 * The card (or lowlevel) driver creates a sequencer device entry
 * via snd_seq_device_new().  This is an entry poपूर्णांकer to communicate
 * with the sequencer device "driver", which is involved with the
 * actual part to communicate with the sequencer core.
 * Each sequencer device entry has an id string and the corresponding
 * driver with the same id is loaded when required.  For example,
 * lowlevel codes to access emu8000 chip on sbawe card are included in
 * emu8000-synth module.  To activate this module, the hardware
 * resources like i/o port are passed via snd_seq_device argument.
 */

#समावेश <linux/device.h>
#समावेश <linux/init.h>
#समावेश <linux/module.h>
#समावेश <sound/core.h>
#समावेश <sound/info.h>
#समावेश <sound/seq_device.h>
#समावेश <sound/seq_kernel.h>
#समावेश <sound/initval.h>
#समावेश <linux/kmod.h>
#समावेश <linux/slab.h>
#समावेश <linux/mutex.h>

MODULE_AUTHOR("Takashi Iwai <tiwai@suse.de>");
MODULE_DESCRIPTION("ALSA sequencer device management");
MODULE_LICENSE("GPL");

/*
 * bus definition
 */
अटल पूर्णांक snd_seq_bus_match(काष्ठा device *dev, काष्ठा device_driver *drv)
अणु
	काष्ठा snd_seq_device *sdev = to_seq_dev(dev);
	काष्ठा snd_seq_driver *sdrv = to_seq_drv(drv);

	वापस म_भेद(sdrv->id, sdev->id) == 0 &&
		sdrv->argsize == sdev->argsize;
पूर्ण

अटल काष्ठा bus_type snd_seq_bus_type = अणु
	.name = "snd_seq",
	.match = snd_seq_bus_match,
पूर्ण;

/*
 * proc पूर्णांकerface -- just क्रम compatibility
 */
#अगर_घोषित CONFIG_SND_PROC_FS
अटल काष्ठा snd_info_entry *info_entry;

अटल पूर्णांक prपूर्णांक_dev_info(काष्ठा device *dev, व्योम *data)
अणु
	काष्ठा snd_seq_device *sdev = to_seq_dev(dev);
	काष्ठा snd_info_buffer *buffer = data;

	snd_iम_लिखो(buffer, "snd-%s,%s,%d\n", sdev->id,
		    dev->driver ? "loaded" : "empty",
		    dev->driver ? 1 : 0);
	वापस 0;
पूर्ण

अटल व्योम snd_seq_device_info(काष्ठा snd_info_entry *entry,
				काष्ठा snd_info_buffer *buffer)
अणु
	bus_क्रम_each_dev(&snd_seq_bus_type, शून्य, buffer, prपूर्णांक_dev_info);
पूर्ण
#पूर्ण_अगर

/*
 * load all रेजिस्टरed drivers (called from seq_clienपंचांगgr.c)
 */

#अगर_घोषित CONFIG_MODULES
/* flag to block स्वतः-loading */
अटल atomic_t snd_seq_in_init = ATOMIC_INIT(1); /* blocked as शेष */

अटल पूर्णांक request_seq_drv(काष्ठा device *dev, व्योम *data)
अणु
	काष्ठा snd_seq_device *sdev = to_seq_dev(dev);

	अगर (!dev->driver)
		request_module("snd-%s", sdev->id);
	वापस 0;
पूर्ण

अटल व्योम स्वतःload_drivers(काष्ठा work_काष्ठा *work)
अणु
	/* aव्योम reentrance */
	अगर (atomic_inc_वापस(&snd_seq_in_init) == 1)
		bus_क्रम_each_dev(&snd_seq_bus_type, शून्य, शून्य,
				 request_seq_drv);
	atomic_dec(&snd_seq_in_init);
पूर्ण

अटल DECLARE_WORK(स्वतःload_work, स्वतःload_drivers);

अटल व्योम queue_स्वतःload_drivers(व्योम)
अणु
	schedule_work(&स्वतःload_work);
पूर्ण

व्योम snd_seq_स्वतःload_init(व्योम)
अणु
	atomic_dec(&snd_seq_in_init);
#अगर_घोषित CONFIG_SND_SEQUENCER_MODULE
	/* initial स्वतःload only when snd-seq is a module */
	queue_स्वतःload_drivers();
#पूर्ण_अगर
पूर्ण
EXPORT_SYMBOL(snd_seq_स्वतःload_init);

व्योम snd_seq_स्वतःload_निकास(व्योम)
अणु
	atomic_inc(&snd_seq_in_init);
पूर्ण
EXPORT_SYMBOL(snd_seq_स्वतःload_निकास);

व्योम snd_seq_device_load_drivers(व्योम)
अणु
	queue_स्वतःload_drivers();
	flush_work(&स्वतःload_work);
पूर्ण
EXPORT_SYMBOL(snd_seq_device_load_drivers);

अटल अंतरभूत व्योम cancel_स्वतःload_drivers(व्योम)
अणु
	cancel_work_sync(&स्वतःload_work);
पूर्ण
#अन्यथा
अटल अंतरभूत व्योम queue_स्वतःload_drivers(व्योम)
अणु
पूर्ण

अटल अंतरभूत व्योम cancel_स्वतःload_drivers(व्योम)
अणु
पूर्ण
#पूर्ण_अगर

/*
 * device management
 */
अटल पूर्णांक snd_seq_device_dev_मुक्त(काष्ठा snd_device *device)
अणु
	काष्ठा snd_seq_device *dev = device->device_data;

	cancel_स्वतःload_drivers();
	put_device(&dev->dev);
	वापस 0;
पूर्ण

अटल पूर्णांक snd_seq_device_dev_रेजिस्टर(काष्ठा snd_device *device)
अणु
	काष्ठा snd_seq_device *dev = device->device_data;
	पूर्णांक err;

	err = device_add(&dev->dev);
	अगर (err < 0)
		वापस err;
	अगर (!dev->dev.driver)
		queue_स्वतःload_drivers();
	वापस 0;
पूर्ण

अटल पूर्णांक snd_seq_device_dev_disconnect(काष्ठा snd_device *device)
अणु
	काष्ठा snd_seq_device *dev = device->device_data;

	device_del(&dev->dev);
	वापस 0;
पूर्ण

अटल व्योम snd_seq_dev_release(काष्ठा device *dev)
अणु
	काष्ठा snd_seq_device *sdev = to_seq_dev(dev);

	अगर (sdev->निजी_मुक्त)
		sdev->निजी_मुक्त(sdev);
	kमुक्त(sdev);
पूर्ण

/*
 * रेजिस्टर a sequencer device
 * card = card info
 * device = device number (अगर any)
 * id = id of driver
 * result = वापस poपूर्णांकer (शून्य allowed अगर unnecessary)
 */
पूर्णांक snd_seq_device_new(काष्ठा snd_card *card, पूर्णांक device, स्थिर अक्षर *id,
		       पूर्णांक argsize, काष्ठा snd_seq_device **result)
अणु
	काष्ठा snd_seq_device *dev;
	पूर्णांक err;
	अटल स्थिर काष्ठा snd_device_ops करोps = अणु
		.dev_मुक्त = snd_seq_device_dev_मुक्त,
		.dev_रेजिस्टर = snd_seq_device_dev_रेजिस्टर,
		.dev_disconnect = snd_seq_device_dev_disconnect,
	पूर्ण;

	अगर (result)
		*result = शून्य;

	अगर (snd_BUG_ON(!id))
		वापस -EINVAL;

	dev = kzalloc(माप(*dev) + argsize, GFP_KERNEL);
	अगर (!dev)
		वापस -ENOMEM;

	/* set up device info */
	dev->card = card;
	dev->device = device;
	dev->id = id;
	dev->argsize = argsize;

	device_initialize(&dev->dev);
	dev->dev.parent = &card->card_dev;
	dev->dev.bus = &snd_seq_bus_type;
	dev->dev.release = snd_seq_dev_release;
	dev_set_name(&dev->dev, "%s-%d-%d", dev->id, card->number, device);

	/* add this device to the list */
	err = snd_device_new(card, SNDRV_DEV_SEQUENCER, dev, &करोps);
	अगर (err < 0) अणु
		put_device(&dev->dev);
		वापस err;
	पूर्ण
	
	अगर (result)
		*result = dev;

	वापस 0;
पूर्ण
EXPORT_SYMBOL(snd_seq_device_new);

/*
 * driver registration
 */
पूर्णांक __snd_seq_driver_रेजिस्टर(काष्ठा snd_seq_driver *drv, काष्ठा module *mod)
अणु
	अगर (WARN_ON(!drv->driver.name || !drv->id))
		वापस -EINVAL;
	drv->driver.bus = &snd_seq_bus_type;
	drv->driver.owner = mod;
	वापस driver_रेजिस्टर(&drv->driver);
पूर्ण
EXPORT_SYMBOL_GPL(__snd_seq_driver_रेजिस्टर);

व्योम snd_seq_driver_unरेजिस्टर(काष्ठा snd_seq_driver *drv)
अणु
	driver_unरेजिस्टर(&drv->driver);
पूर्ण
EXPORT_SYMBOL_GPL(snd_seq_driver_unरेजिस्टर);

/*
 * module part
 */

अटल पूर्णांक __init seq_dev_proc_init(व्योम)
अणु
#अगर_घोषित CONFIG_SND_PROC_FS
	info_entry = snd_info_create_module_entry(THIS_MODULE, "drivers",
						  snd_seq_root);
	अगर (info_entry == शून्य)
		वापस -ENOMEM;
	info_entry->content = SNDRV_INFO_CONTENT_TEXT;
	info_entry->c.text.पढ़ो = snd_seq_device_info;
	अगर (snd_info_रेजिस्टर(info_entry) < 0) अणु
		snd_info_मुक्त_entry(info_entry);
		वापस -ENOMEM;
	पूर्ण
#पूर्ण_अगर
	वापस 0;
पूर्ण

अटल पूर्णांक __init alsa_seq_device_init(व्योम)
अणु
	पूर्णांक err;

	err = bus_रेजिस्टर(&snd_seq_bus_type);
	अगर (err < 0)
		वापस err;
	err = seq_dev_proc_init();
	अगर (err < 0)
		bus_unरेजिस्टर(&snd_seq_bus_type);
	वापस err;
पूर्ण

अटल व्योम __निकास alsa_seq_device_निकास(व्योम)
अणु
#अगर_घोषित CONFIG_MODULES
	cancel_work_sync(&स्वतःload_work);
#पूर्ण_अगर
#अगर_घोषित CONFIG_SND_PROC_FS
	snd_info_मुक्त_entry(info_entry);
#पूर्ण_अगर
	bus_unरेजिस्टर(&snd_seq_bus_type);
पूर्ण

subsys_initcall(alsa_seq_device_init)
module_निकास(alsa_seq_device_निकास)
