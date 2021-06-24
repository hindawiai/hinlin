<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *  Device management routines
 *  Copyright (c) by Jaroslav Kysela <perex@perex.cz>
 */

#समावेश <linux/slab.h>
#समावेश <linux/समय.स>
#समावेश <linux/export.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <sound/core.h>

/**
 * snd_device_new - create an ALSA device component
 * @card: the card instance
 * @type: the device type, SNDRV_DEV_XXX
 * @device_data: the data poपूर्णांकer of this device
 * @ops: the चालक table
 *
 * Creates a new device component क्रम the given data poपूर्णांकer.
 * The device will be asचिन्हित to the card and managed together
 * by the card.
 *
 * The data poपूर्णांकer plays a role as the identअगरier, too, so the
 * poपूर्णांकer address must be unique and unchanged.
 *
 * Return: Zero अगर successful, or a negative error code on failure.
 */
पूर्णांक snd_device_new(काष्ठा snd_card *card, क्रमागत snd_device_type type,
		   व्योम *device_data, स्थिर काष्ठा snd_device_ops *ops)
अणु
	काष्ठा snd_device *dev;
	काष्ठा list_head *p;

	अगर (snd_BUG_ON(!card || !device_data || !ops))
		वापस -ENXIO;
	dev = kzalloc(माप(*dev), GFP_KERNEL);
	अगर (!dev)
		वापस -ENOMEM;
	INIT_LIST_HEAD(&dev->list);
	dev->card = card;
	dev->type = type;
	dev->state = SNDRV_DEV_BUILD;
	dev->device_data = device_data;
	dev->ops = ops;

	/* insert the entry in an incrementally sorted list */
	list_क्रम_each_prev(p, &card->devices) अणु
		काष्ठा snd_device *pdev = list_entry(p, काष्ठा snd_device, list);
		अगर ((अचिन्हित पूर्णांक)pdev->type <= (अचिन्हित पूर्णांक)type)
			अवरोध;
	पूर्ण

	list_add(&dev->list, p);
	वापस 0;
पूर्ण
EXPORT_SYMBOL(snd_device_new);

अटल व्योम __snd_device_disconnect(काष्ठा snd_device *dev)
अणु
	अगर (dev->state == SNDRV_DEV_REGISTERED) अणु
		अगर (dev->ops->dev_disconnect &&
		    dev->ops->dev_disconnect(dev))
			dev_err(dev->card->dev, "device disconnect failure\n");
		dev->state = SNDRV_DEV_DISCONNECTED;
	पूर्ण
पूर्ण

अटल व्योम __snd_device_मुक्त(काष्ठा snd_device *dev)
अणु
	/* unlink */
	list_del(&dev->list);

	__snd_device_disconnect(dev);
	अगर (dev->ops->dev_मुक्त) अणु
		अगर (dev->ops->dev_मुक्त(dev))
			dev_err(dev->card->dev, "device free failure\n");
	पूर्ण
	kमुक्त(dev);
पूर्ण

अटल काष्ठा snd_device *look_क्रम_dev(काष्ठा snd_card *card, व्योम *device_data)
अणु
	काष्ठा snd_device *dev;

	list_क्रम_each_entry(dev, &card->devices, list)
		अगर (dev->device_data == device_data)
			वापस dev;

	वापस शून्य;
पूर्ण

/**
 * snd_device_disconnect - disconnect the device
 * @card: the card instance
 * @device_data: the data poपूर्णांकer to disconnect
 *
 * Turns the device पूर्णांकo the disconnection state, invoking
 * dev_disconnect callback, अगर the device was alपढ़ोy रेजिस्टरed.
 *
 * Usually called from snd_card_disconnect().
 *
 * Return: Zero अगर successful, or a negative error code on failure or अगर the
 * device not found.
 */
व्योम snd_device_disconnect(काष्ठा snd_card *card, व्योम *device_data)
अणु
	काष्ठा snd_device *dev;

	अगर (snd_BUG_ON(!card || !device_data))
		वापस;
	dev = look_क्रम_dev(card, device_data);
	अगर (dev)
		__snd_device_disconnect(dev);
	अन्यथा
		dev_dbg(card->dev, "device disconnect %p (from %pS), not found\n",
			device_data, __builtin_वापस_address(0));
पूर्ण
EXPORT_SYMBOL_GPL(snd_device_disconnect);

/**
 * snd_device_मुक्त - release the device from the card
 * @card: the card instance
 * @device_data: the data poपूर्णांकer to release
 *
 * Removes the device from the list on the card and invokes the
 * callbacks, dev_disconnect and dev_मुक्त, corresponding to the state.
 * Then release the device.
 */
व्योम snd_device_मुक्त(काष्ठा snd_card *card, व्योम *device_data)
अणु
	काष्ठा snd_device *dev;
	
	अगर (snd_BUG_ON(!card || !device_data))
		वापस;
	dev = look_क्रम_dev(card, device_data);
	अगर (dev)
		__snd_device_मुक्त(dev);
	अन्यथा
		dev_dbg(card->dev, "device free %p (from %pS), not found\n",
			device_data, __builtin_वापस_address(0));
पूर्ण
EXPORT_SYMBOL(snd_device_मुक्त);

अटल पूर्णांक __snd_device_रेजिस्टर(काष्ठा snd_device *dev)
अणु
	अगर (dev->state == SNDRV_DEV_BUILD) अणु
		अगर (dev->ops->dev_रेजिस्टर) अणु
			पूर्णांक err = dev->ops->dev_रेजिस्टर(dev);
			अगर (err < 0)
				वापस err;
		पूर्ण
		dev->state = SNDRV_DEV_REGISTERED;
	पूर्ण
	वापस 0;
पूर्ण

/**
 * snd_device_रेजिस्टर - रेजिस्टर the device
 * @card: the card instance
 * @device_data: the data poपूर्णांकer to रेजिस्टर
 *
 * Registers the device which was alपढ़ोy created via
 * snd_device_new().  Usually this is called from snd_card_रेजिस्टर(),
 * but it can be called later अगर any new devices are created after
 * invocation of snd_card_रेजिस्टर().
 *
 * Return: Zero अगर successful, or a negative error code on failure or अगर the
 * device not found.
 */
पूर्णांक snd_device_रेजिस्टर(काष्ठा snd_card *card, व्योम *device_data)
अणु
	काष्ठा snd_device *dev;

	अगर (snd_BUG_ON(!card || !device_data))
		वापस -ENXIO;
	dev = look_क्रम_dev(card, device_data);
	अगर (dev)
		वापस __snd_device_रेजिस्टर(dev);
	snd_BUG();
	वापस -ENXIO;
पूर्ण
EXPORT_SYMBOL(snd_device_रेजिस्टर);

/*
 * रेजिस्टर all the devices on the card.
 * called from init.c
 */
पूर्णांक snd_device_रेजिस्टर_all(काष्ठा snd_card *card)
अणु
	काष्ठा snd_device *dev;
	पूर्णांक err;
	
	अगर (snd_BUG_ON(!card))
		वापस -ENXIO;
	list_क्रम_each_entry(dev, &card->devices, list) अणु
		err = __snd_device_रेजिस्टर(dev);
		अगर (err < 0)
			वापस err;
	पूर्ण
	वापस 0;
पूर्ण

/*
 * disconnect all the devices on the card.
 * called from init.c
 */
व्योम snd_device_disconnect_all(काष्ठा snd_card *card)
अणु
	काष्ठा snd_device *dev;

	अगर (snd_BUG_ON(!card))
		वापस;
	list_क्रम_each_entry_reverse(dev, &card->devices, list)
		__snd_device_disconnect(dev);
पूर्ण

/*
 * release all the devices on the card.
 * called from init.c
 */
व्योम snd_device_मुक्त_all(काष्ठा snd_card *card)
अणु
	काष्ठा snd_device *dev, *next;

	अगर (snd_BUG_ON(!card))
		वापस;
	list_क्रम_each_entry_safe_reverse(dev, next, &card->devices, list) अणु
		/* exception: मुक्त ctl and lowlevel stuff later */
		अगर (dev->type == SNDRV_DEV_CONTROL ||
		    dev->type == SNDRV_DEV_LOWLEVEL)
			जारी;
		__snd_device_मुक्त(dev);
	पूर्ण

	/* मुक्त all */
	list_क्रम_each_entry_safe_reverse(dev, next, &card->devices, list)
		__snd_device_मुक्त(dev);
पूर्ण

/**
 * snd_device_get_state - Get the current state of the given device
 * @card: the card instance
 * @device_data: the data poपूर्णांकer to release
 *
 * Returns the current state of the given device object.  For the valid
 * device, either @SNDRV_DEV_BUILD, @SNDRV_DEV_REGISTERED or
 * @SNDRV_DEV_DISCONNECTED is वापसed.
 * Or क्रम a non-existing device, -1 is वापसed as an error.
 */
पूर्णांक snd_device_get_state(काष्ठा snd_card *card, व्योम *device_data)
अणु
	काष्ठा snd_device *dev;

	dev = look_क्रम_dev(card, device_data);
	अगर (dev)
		वापस dev->state;
	वापस -1;
पूर्ण
EXPORT_SYMBOL_GPL(snd_device_get_state);
