<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Linux driver क्रम TerraTec DMX 6Fire USB
 *
 * Main routines and module definitions.
 *
 * Author:	Torsten Schenk <torsten.schenk@zoho.com>
 * Created:	Jan 01, 2011
 * Copyright:	(C) Torsten Schenk
 */

#समावेश "chip.h"
#समावेश "firmware.h"
#समावेश "pcm.h"
#समावेश "control.h"
#समावेश "comm.h"
#समावेश "midi.h"

#समावेश <linux/moduleparam.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/module.h>
#समावेश <linux/init.h>
#समावेश <linux/gfp.h>
#समावेश <sound/initval.h>

MODULE_AUTHOR("Torsten Schenk <torsten.schenk@zoho.com>");
MODULE_DESCRIPTION("TerraTec DMX 6Fire USB audio driver");
MODULE_LICENSE("GPL v2");

अटल पूर्णांक index[SNDRV_CARDS] = SNDRV_DEFAULT_IDX; /* Index 0-max */
अटल अक्षर *id[SNDRV_CARDS] = SNDRV_DEFAULT_STR; /* Id क्रम card */
अटल bool enable[SNDRV_CARDS] = SNDRV_DEFAULT_ENABLE_PNP; /* Enable card */
अटल काष्ठा sfire_chip *chips[SNDRV_CARDS] = SNDRV_DEFAULT_PTR;
अटल काष्ठा usb_device *devices[SNDRV_CARDS] = SNDRV_DEFAULT_PTR;

module_param_array(index, पूर्णांक, शून्य, 0444);
MODULE_PARM_DESC(index, "Index value for the 6fire sound device");
module_param_array(id, अक्षरp, शून्य, 0444);
MODULE_PARM_DESC(id, "ID string for the 6fire sound device.");
module_param_array(enable, bool, शून्य, 0444);
MODULE_PARM_DESC(enable, "Enable the 6fire sound device.");

अटल DEFINE_MUTEX(रेजिस्टर_mutex);

अटल व्योम usb6fire_chip_पात(काष्ठा sfire_chip *chip)
अणु
	अगर (chip) अणु
		अगर (chip->pcm)
			usb6fire_pcm_पात(chip);
		अगर (chip->midi)
			usb6fire_midi_पात(chip);
		अगर (chip->comm)
			usb6fire_comm_पात(chip);
		अगर (chip->control)
			usb6fire_control_पात(chip);
		अगर (chip->card) अणु
			snd_card_disconnect(chip->card);
			snd_card_मुक्त_when_बंदd(chip->card);
			chip->card = शून्य;
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम usb6fire_chip_destroy(काष्ठा sfire_chip *chip)
अणु
	अगर (chip) अणु
		अगर (chip->pcm)
			usb6fire_pcm_destroy(chip);
		अगर (chip->midi)
			usb6fire_midi_destroy(chip);
		अगर (chip->comm)
			usb6fire_comm_destroy(chip);
		अगर (chip->control)
			usb6fire_control_destroy(chip);
		अगर (chip->card)
			snd_card_मुक्त(chip->card);
	पूर्ण
पूर्ण

अटल पूर्णांक usb6fire_chip_probe(काष्ठा usb_पूर्णांकerface *पूर्णांकf,
			       स्थिर काष्ठा usb_device_id *usb_id)
अणु
	पूर्णांक ret;
	पूर्णांक i;
	काष्ठा sfire_chip *chip = शून्य;
	काष्ठा usb_device *device = पूर्णांकerface_to_usbdev(पूर्णांकf);
	पूर्णांक regidx = -1; /* index in module parameter array */
	काष्ठा snd_card *card = शून्य;

	/* look अगर we alपढ़ोy serve this card and वापस अगर so */
	mutex_lock(&रेजिस्टर_mutex);
	क्रम (i = 0; i < SNDRV_CARDS; i++) अणु
		अगर (devices[i] == device) अणु
			अगर (chips[i])
				chips[i]->पूर्णांकf_count++;
			usb_set_पूर्णांकfdata(पूर्णांकf, chips[i]);
			mutex_unlock(&रेजिस्टर_mutex);
			वापस 0;
		पूर्ण अन्यथा अगर (!devices[i] && regidx < 0)
			regidx = i;
	पूर्ण
	अगर (regidx < 0) अणु
		mutex_unlock(&रेजिस्टर_mutex);
		dev_err(&पूर्णांकf->dev, "too many cards registered.\n");
		वापस -ENODEV;
	पूर्ण
	devices[regidx] = device;
	mutex_unlock(&रेजिस्टर_mutex);

	/* check, अगर firmware is present on device, upload it अगर not */
	ret = usb6fire_fw_init(पूर्णांकf);
	अगर (ret < 0)
		वापस ret;
	अन्यथा अगर (ret == FW_NOT_READY) /* firmware update perक्रमmed */
		वापस 0;

	/* अगर we are here, card can be रेजिस्टरed in alsa. */
	अगर (usb_set_पूर्णांकerface(device, 0, 0) != 0) अणु
		dev_err(&पूर्णांकf->dev, "can't set first interface.\n");
		वापस -EIO;
	पूर्ण
	ret = snd_card_new(&पूर्णांकf->dev, index[regidx], id[regidx],
			   THIS_MODULE, माप(काष्ठा sfire_chip), &card);
	अगर (ret < 0) अणु
		dev_err(&पूर्णांकf->dev, "cannot create alsa card.\n");
		वापस ret;
	पूर्ण
	म_नकल(card->driver, "6FireUSB");
	म_नकल(card->लघुname, "TerraTec DMX6FireUSB");
	प्र_लिखो(card->दीर्घname, "%s at %d:%d", card->लघुname,
			device->bus->busnum, device->devnum);

	chip = card->निजी_data;
	chips[regidx] = chip;
	chip->dev = device;
	chip->regidx = regidx;
	chip->पूर्णांकf_count = 1;
	chip->card = card;

	ret = usb6fire_comm_init(chip);
	अगर (ret < 0)
		जाओ destroy_chip;

	ret = usb6fire_midi_init(chip);
	अगर (ret < 0)
		जाओ destroy_chip;

	ret = usb6fire_pcm_init(chip);
	अगर (ret < 0)
		जाओ destroy_chip;

	ret = usb6fire_control_init(chip);
	अगर (ret < 0)
		जाओ destroy_chip;

	ret = snd_card_रेजिस्टर(card);
	अगर (ret < 0) अणु
		dev_err(&पूर्णांकf->dev, "cannot register card.");
		जाओ destroy_chip;
	पूर्ण
	usb_set_पूर्णांकfdata(पूर्णांकf, chip);
	वापस 0;

destroy_chip:
	usb6fire_chip_destroy(chip);
	वापस ret;
पूर्ण

अटल व्योम usb6fire_chip_disconnect(काष्ठा usb_पूर्णांकerface *पूर्णांकf)
अणु
	काष्ठा sfire_chip *chip;

	chip = usb_get_पूर्णांकfdata(पूर्णांकf);
	अगर (chip) अणु /* अगर !chip, fw upload has been perक्रमmed */
		chip->पूर्णांकf_count--;
		अगर (!chip->पूर्णांकf_count) अणु
			mutex_lock(&रेजिस्टर_mutex);
			devices[chip->regidx] = शून्य;
			chips[chip->regidx] = शून्य;
			mutex_unlock(&रेजिस्टर_mutex);

			chip->shutकरोwn = true;
			usb6fire_chip_पात(chip);
			usb6fire_chip_destroy(chip);
		पूर्ण
	पूर्ण
पूर्ण

अटल स्थिर काष्ठा usb_device_id device_table[] = अणु
	अणु
		.match_flags = USB_DEVICE_ID_MATCH_DEVICE,
		.idVenकरोr = 0x0ccd,
		.idProduct = 0x0080
	पूर्ण,
	अणुपूर्ण
पूर्ण;

MODULE_DEVICE_TABLE(usb, device_table);

अटल काष्ठा usb_driver usb_driver = अणु
	.name = "snd-usb-6fire",
	.probe = usb6fire_chip_probe,
	.disconnect = usb6fire_chip_disconnect,
	.id_table = device_table,
पूर्ण;

module_usb_driver(usb_driver);
