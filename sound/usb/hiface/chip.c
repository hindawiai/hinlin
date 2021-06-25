<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Linux driver क्रम M2Tech hiFace compatible devices
 *
 * Copyright 2012-2013 (C) M2TECH S.r.l and Amarula Solutions B.V.
 *
 * Authors:  Michael Trimarchi <michael@amarulasolutions.com>
 *           Antonio Ospite <ao2@amarulasolutions.com>
 *
 * The driver is based on the work करोne in TerraTec DMX 6Fire USB
 */

#समावेश <linux/module.h>
#समावेश <linux/slab.h>
#समावेश <sound/initval.h>

#समावेश "chip.h"
#समावेश "pcm.h"

MODULE_AUTHOR("Michael Trimarchi <michael@amarulasolutions.com>");
MODULE_AUTHOR("Antonio Ospite <ao2@amarulasolutions.com>");
MODULE_DESCRIPTION("M2Tech hiFace USB-SPDIF audio driver");
MODULE_LICENSE("GPL v2");

अटल पूर्णांक index[SNDRV_CARDS] = SNDRV_DEFAULT_IDX; /* Index 0-max */
अटल अक्षर *id[SNDRV_CARDS] = SNDRV_DEFAULT_STR; /* Id क्रम card */
अटल bool enable[SNDRV_CARDS] = SNDRV_DEFAULT_ENABLE_PNP; /* Enable this card */

#घोषणा DRIVER_NAME "snd-usb-hiface"
#घोषणा CARD_NAME "hiFace"

module_param_array(index, पूर्णांक, शून्य, 0444);
MODULE_PARM_DESC(index, "Index value for " CARD_NAME " soundcard.");
module_param_array(id, अक्षरp, शून्य, 0444);
MODULE_PARM_DESC(id, "ID string for " CARD_NAME " soundcard.");
module_param_array(enable, bool, शून्य, 0444);
MODULE_PARM_DESC(enable, "Enable " CARD_NAME " soundcard.");

अटल DEFINE_MUTEX(रेजिस्टर_mutex);

काष्ठा hअगरace_venकरोr_quirk अणु
	स्थिर अक्षर *device_name;
	u8 extra_freq;
पूर्ण;

अटल पूर्णांक hअगरace_chip_create(काष्ठा usb_पूर्णांकerface *पूर्णांकf,
			      काष्ठा usb_device *device, पूर्णांक idx,
			      स्थिर काष्ठा hअगरace_venकरोr_quirk *quirk,
			      काष्ठा hअगरace_chip **rchip)
अणु
	काष्ठा snd_card *card = शून्य;
	काष्ठा hअगरace_chip *chip;
	पूर्णांक ret;
	पूर्णांक len;

	*rchip = शून्य;

	/* अगर we are here, card can be रेजिस्टरed in alsa. */
	ret = snd_card_new(&पूर्णांकf->dev, index[idx], id[idx], THIS_MODULE,
			   माप(*chip), &card);
	अगर (ret < 0) अणु
		dev_err(&device->dev, "cannot create alsa card.\n");
		वापस ret;
	पूर्ण

	strscpy(card->driver, DRIVER_NAME, माप(card->driver));

	अगर (quirk && quirk->device_name)
		strscpy(card->लघुname, quirk->device_name, माप(card->लघुname));
	अन्यथा
		strscpy(card->लघुname, "M2Tech generic audio", माप(card->लघुname));

	strlcat(card->दीर्घname, card->लघुname, माप(card->दीर्घname));
	len = strlcat(card->दीर्घname, " at ", माप(card->दीर्घname));
	अगर (len < माप(card->दीर्घname))
		usb_make_path(device, card->दीर्घname + len,
			      माप(card->दीर्घname) - len);

	chip = card->निजी_data;
	chip->dev = device;
	chip->card = card;

	*rchip = chip;
	वापस 0;
पूर्ण

अटल पूर्णांक hअगरace_chip_probe(काष्ठा usb_पूर्णांकerface *पूर्णांकf,
			     स्थिर काष्ठा usb_device_id *usb_id)
अणु
	स्थिर काष्ठा hअगरace_venकरोr_quirk *quirk = (काष्ठा hअगरace_venकरोr_quirk *)usb_id->driver_info;
	पूर्णांक ret;
	पूर्णांक i;
	काष्ठा hअगरace_chip *chip;
	काष्ठा usb_device *device = पूर्णांकerface_to_usbdev(पूर्णांकf);

	ret = usb_set_पूर्णांकerface(device, 0, 0);
	अगर (ret != 0) अणु
		dev_err(&device->dev, "can't set first interface for " CARD_NAME " device.\n");
		वापस -EIO;
	पूर्ण

	/* check whether the card is alपढ़ोy रेजिस्टरed */
	chip = शून्य;
	mutex_lock(&रेजिस्टर_mutex);

	क्रम (i = 0; i < SNDRV_CARDS; i++)
		अगर (enable[i])
			अवरोध;

	अगर (i >= SNDRV_CARDS) अणु
		dev_err(&device->dev, "no available " CARD_NAME " audio device\n");
		ret = -ENODEV;
		जाओ err;
	पूर्ण

	ret = hअगरace_chip_create(पूर्णांकf, device, i, quirk, &chip);
	अगर (ret < 0)
		जाओ err;

	ret = hअगरace_pcm_init(chip, quirk ? quirk->extra_freq : 0);
	अगर (ret < 0)
		जाओ err_chip_destroy;

	ret = snd_card_रेजिस्टर(chip->card);
	अगर (ret < 0) अणु
		dev_err(&device->dev, "cannot register " CARD_NAME " card\n");
		जाओ err_chip_destroy;
	पूर्ण

	mutex_unlock(&रेजिस्टर_mutex);

	usb_set_पूर्णांकfdata(पूर्णांकf, chip);
	वापस 0;

err_chip_destroy:
	snd_card_मुक्त(chip->card);
err:
	mutex_unlock(&रेजिस्टर_mutex);
	वापस ret;
पूर्ण

अटल व्योम hअगरace_chip_disconnect(काष्ठा usb_पूर्णांकerface *पूर्णांकf)
अणु
	काष्ठा hअगरace_chip *chip;
	काष्ठा snd_card *card;

	chip = usb_get_पूर्णांकfdata(पूर्णांकf);
	अगर (!chip)
		वापस;

	card = chip->card;

	/* Make sure that the userspace cannot create new request */
	snd_card_disconnect(card);

	hअगरace_pcm_पात(chip);
	snd_card_मुक्त_when_बंदd(card);
पूर्ण

अटल स्थिर काष्ठा usb_device_id device_table[] = अणु
	अणु
		USB_DEVICE(0x04b4, 0x0384),
		.driver_info = (अचिन्हित दीर्घ)&(स्थिर काष्ठा hअगरace_venकरोr_quirk) अणु
			.device_name = "Young",
			.extra_freq = 1,
		पूर्ण
	पूर्ण,
	अणु
		USB_DEVICE(0x04b4, 0x930b),
		.driver_info = (अचिन्हित दीर्घ)&(स्थिर काष्ठा hअगरace_venकरोr_quirk) अणु
			.device_name = "hiFace",
		पूर्ण
	पूर्ण,
	अणु
		USB_DEVICE(0x04b4, 0x931b),
		.driver_info = (अचिन्हित दीर्घ)&(स्थिर काष्ठा hअगरace_venकरोr_quirk) अणु
			.device_name = "North Star",
		पूर्ण
	पूर्ण,
	अणु
		USB_DEVICE(0x04b4, 0x931c),
		.driver_info = (अचिन्हित दीर्घ)&(स्थिर काष्ठा hअगरace_venकरोr_quirk) अणु
			.device_name = "W4S Young",
		पूर्ण
	पूर्ण,
	अणु
		USB_DEVICE(0x04b4, 0x931d),
		.driver_info = (अचिन्हित दीर्घ)&(स्थिर काष्ठा hअगरace_venकरोr_quirk) अणु
			.device_name = "Corrson",
		पूर्ण
	पूर्ण,
	अणु
		USB_DEVICE(0x04b4, 0x931e),
		.driver_info = (अचिन्हित दीर्घ)&(स्थिर काष्ठा hअगरace_venकरोr_quirk) अणु
			.device_name = "AUDIA",
		पूर्ण
	पूर्ण,
	अणु
		USB_DEVICE(0x04b4, 0x931f),
		.driver_info = (अचिन्हित दीर्घ)&(स्थिर काष्ठा hअगरace_venकरोr_quirk) अणु
			.device_name = "SL Audio",
		पूर्ण
	पूर्ण,
	अणु
		USB_DEVICE(0x04b4, 0x9320),
		.driver_info = (अचिन्हित दीर्घ)&(स्थिर काष्ठा hअगरace_venकरोr_quirk) अणु
			.device_name = "Empirical",
		पूर्ण
	पूर्ण,
	अणु
		USB_DEVICE(0x04b4, 0x9321),
		.driver_info = (अचिन्हित दीर्घ)&(स्थिर काष्ठा hअगरace_venकरोr_quirk) अणु
			.device_name = "Rockna",
		पूर्ण
	पूर्ण,
	अणु
		USB_DEVICE(0x249c, 0x9001),
		.driver_info = (अचिन्हित दीर्घ)&(स्थिर काष्ठा hअगरace_venकरोr_quirk) अणु
			.device_name = "Pathos",
		पूर्ण
	पूर्ण,
	अणु
		USB_DEVICE(0x249c, 0x9002),
		.driver_info = (अचिन्हित दीर्घ)&(स्थिर काष्ठा hअगरace_venकरोr_quirk) अणु
			.device_name = "Metronome",
		पूर्ण
	पूर्ण,
	अणु
		USB_DEVICE(0x249c, 0x9006),
		.driver_info = (अचिन्हित दीर्घ)&(स्थिर काष्ठा hअगरace_venकरोr_quirk) अणु
			.device_name = "CAD",
		पूर्ण
	पूर्ण,
	अणु
		USB_DEVICE(0x249c, 0x9008),
		.driver_info = (अचिन्हित दीर्घ)&(स्थिर काष्ठा hअगरace_venकरोr_quirk) अणु
			.device_name = "Audio Esclusive",
		पूर्ण
	पूर्ण,
	अणु
		USB_DEVICE(0x249c, 0x931c),
		.driver_info = (अचिन्हित दीर्घ)&(स्थिर काष्ठा hअगरace_venकरोr_quirk) अणु
			.device_name = "Rotel",
		पूर्ण
	पूर्ण,
	अणु
		USB_DEVICE(0x249c, 0x932c),
		.driver_info = (अचिन्हित दीर्घ)&(स्थिर काष्ठा hअगरace_venकरोr_quirk) अणु
			.device_name = "Eeaudio",
		पूर्ण
	पूर्ण,
	अणु
		USB_DEVICE(0x245f, 0x931c),
		.driver_info = (अचिन्हित दीर्घ)&(स्थिर काष्ठा hअगरace_venकरोr_quirk) अणु
			.device_name = "CHORD",
		पूर्ण
	पूर्ण,
	अणु
		USB_DEVICE(0x25c6, 0x9002),
		.driver_info = (अचिन्हित दीर्घ)&(स्थिर काष्ठा hअगरace_venकरोr_quirk) अणु
			.device_name = "Vitus",
		पूर्ण
	पूर्ण,
	अणुपूर्ण
पूर्ण;

MODULE_DEVICE_TABLE(usb, device_table);

अटल काष्ठा usb_driver hअगरace_usb_driver = अणु
	.name = DRIVER_NAME,
	.probe = hअगरace_chip_probe,
	.disconnect = hअगरace_chip_disconnect,
	.id_table = device_table,
पूर्ण;

module_usb_driver(hअगरace_usb_driver);
