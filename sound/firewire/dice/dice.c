<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * TC Applied Technologies Digital Interface Communications Engine driver
 *
 * Copyright (c) Clemens Ladisch <clemens@ladisch.de>
 */

#समावेश "dice.h"

MODULE_DESCRIPTION("DICE driver");
MODULE_AUTHOR("Clemens Ladisch <clemens@ladisch.de>");
MODULE_LICENSE("GPL v2");

#घोषणा OUI_WEISS		0x001c6a
#घोषणा OUI_LOUD		0x000ff2
#घोषणा OUI_FOCUSRITE		0x00130e
#घोषणा OUI_TCELECTRONIC	0x000166
#घोषणा OUI_ALESIS		0x000595
#घोषणा OUI_MAUDIO		0x000d6c
#घोषणा OUI_MYTEK		0x001ee8
#घोषणा OUI_SSL			0x0050c2	// Actually ID reserved by IEEE.
#घोषणा OUI_PRESONUS		0x000a92
#घोषणा OUI_HARMAN		0x000fd7
#घोषणा OUI_AVID		0x00a07e

#घोषणा DICE_CATEGORY_ID	0x04
#घोषणा WEISS_CATEGORY_ID	0x00
#घोषणा LOUD_CATEGORY_ID	0x10
#घोषणा HARMAN_CATEGORY_ID	0x20

#घोषणा MODEL_ALESIS_IO_BOTH	0x000001

अटल पूर्णांक check_dice_category(काष्ठा fw_unit *unit)
अणु
	काष्ठा fw_device *device = fw_parent_device(unit);
	काष्ठा fw_csr_iterator it;
	पूर्णांक key, val, venकरोr = -1, model = -1;
	अचिन्हित पूर्णांक category;

	/*
	 * Check that GUID and unit directory are स्थिरructed according to DICE
	 * rules, i.e., that the specअगरier ID is the GUID's OUI, and that the
	 * GUID chip ID consists of the 8-bit category ID, the 10-bit product
	 * ID, and a 22-bit serial number.
	 */
	fw_csr_iterator_init(&it, unit->directory);
	जबतक (fw_csr_iterator_next(&it, &key, &val)) अणु
		चयन (key) अणु
		हाल CSR_SPECIFIER_ID:
			venकरोr = val;
			अवरोध;
		हाल CSR_MODEL:
			model = val;
			अवरोध;
		पूर्ण
	पूर्ण

	अगर (venकरोr == OUI_WEISS)
		category = WEISS_CATEGORY_ID;
	अन्यथा अगर (venकरोr == OUI_LOUD)
		category = LOUD_CATEGORY_ID;
	अन्यथा अगर (venकरोr == OUI_HARMAN)
		category = HARMAN_CATEGORY_ID;
	अन्यथा
		category = DICE_CATEGORY_ID;
	अगर (device->config_rom[3] != ((venकरोr << 8) | category) ||
	    device->config_rom[4] >> 22 != model)
		वापस -ENODEV;

	वापस 0;
पूर्ण

अटल पूर्णांक check_घड़ी_caps(काष्ठा snd_dice *dice)
अणु
	__be32 value;
	पूर्णांक err;

	/* some very old firmwares करोn't tell about their घड़ी support */
	अगर (dice->घड़ी_caps > 0) अणु
		err = snd_dice_transaction_पढ़ो_global(dice,
						GLOBAL_CLOCK_CAPABILITIES,
						&value, 4);
		अगर (err < 0)
			वापस err;
		dice->घड़ी_caps = be32_to_cpu(value);
	पूर्ण अन्यथा अणु
		/* this should be supported by any device */
		dice->घड़ी_caps = CLOCK_CAP_RATE_44100 |
				   CLOCK_CAP_RATE_48000 |
				   CLOCK_CAP_SOURCE_ARX1 |
				   CLOCK_CAP_SOURCE_INTERNAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम dice_card_strings(काष्ठा snd_dice *dice)
अणु
	काष्ठा snd_card *card = dice->card;
	काष्ठा fw_device *dev = fw_parent_device(dice->unit);
	अक्षर venकरोr[32], model[32];
	अचिन्हित पूर्णांक i;
	पूर्णांक err;

	म_नकल(card->driver, "DICE");

	म_नकल(card->लघुname, "DICE");
	BUILD_BUG_ON(NICK_NAME_SIZE < माप(card->लघुname));
	err = snd_dice_transaction_पढ़ो_global(dice, GLOBAL_NICK_NAME,
					       card->लघुname,
					       माप(card->लघुname));
	अगर (err >= 0) अणु
		/* DICE strings are वापसed in "always-wrong" endianness */
		BUILD_BUG_ON(माप(card->लघुname) % 4 != 0);
		क्रम (i = 0; i < माप(card->लघुname); i += 4)
			swab32s((u32 *)&card->लघुname[i]);
		card->लघुname[माप(card->लघुname) - 1] = '\0';
	पूर्ण

	म_नकल(venकरोr, "?");
	fw_csr_string(dev->config_rom + 5, CSR_VENDOR, venकरोr, माप(venकरोr));
	म_नकल(model, "?");
	fw_csr_string(dice->unit->directory, CSR_MODEL, model, माप(model));
	snम_लिखो(card->दीर्घname, माप(card->दीर्घname),
		 "%s %s (serial %u) at %s, S%d",
		 venकरोr, model, dev->config_rom[4] & 0x3fffff,
		 dev_name(&dice->unit->device), 100 << dev->max_speed);

	म_नकल(card->mixername, "DICE");
पूर्ण

अटल व्योम dice_card_मुक्त(काष्ठा snd_card *card)
अणु
	काष्ठा snd_dice *dice = card->निजी_data;

	snd_dice_stream_destroy_duplex(dice);
	snd_dice_transaction_destroy(dice);
पूर्ण

अटल व्योम करो_registration(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा snd_dice *dice = container_of(work, काष्ठा snd_dice, dwork.work);
	पूर्णांक err;

	अगर (dice->रेजिस्टरed)
		वापस;

	err = snd_card_new(&dice->unit->device, -1, शून्य, THIS_MODULE, 0,
			   &dice->card);
	अगर (err < 0)
		वापस;
	dice->card->निजी_मुक्त = dice_card_मुक्त;
	dice->card->निजी_data = dice;

	err = snd_dice_transaction_init(dice);
	अगर (err < 0)
		जाओ error;

	err = check_घड़ी_caps(dice);
	अगर (err < 0)
		जाओ error;

	dice_card_strings(dice);

	err = dice->detect_क्रमmats(dice);
	अगर (err < 0)
		जाओ error;

	err = snd_dice_stream_init_duplex(dice);
	अगर (err < 0)
		जाओ error;

	snd_dice_create_proc(dice);

	err = snd_dice_create_pcm(dice);
	अगर (err < 0)
		जाओ error;

	err = snd_dice_create_midi(dice);
	अगर (err < 0)
		जाओ error;

	err = snd_dice_create_hwdep(dice);
	अगर (err < 0)
		जाओ error;

	err = snd_card_रेजिस्टर(dice->card);
	अगर (err < 0)
		जाओ error;

	dice->रेजिस्टरed = true;

	वापस;
error:
	snd_card_मुक्त(dice->card);
	dev_info(&dice->unit->device,
		 "Sound card registration failed: %d\n", err);
पूर्ण

अटल पूर्णांक dice_probe(काष्ठा fw_unit *unit,
		      स्थिर काष्ठा ieee1394_device_id *entry)
अणु
	काष्ठा snd_dice *dice;
	पूर्णांक err;

	अगर (!entry->driver_data && entry->venकरोr_id != OUI_SSL) अणु
		err = check_dice_category(unit);
		अगर (err < 0)
			वापस -ENODEV;
	पूर्ण

	/* Allocate this independent of sound card instance. */
	dice = devm_kzalloc(&unit->device, माप(काष्ठा snd_dice), GFP_KERNEL);
	अगर (!dice)
		वापस -ENOMEM;
	dice->unit = fw_unit_get(unit);
	dev_set_drvdata(&unit->device, dice);

	अगर (!entry->driver_data) अणु
		dice->detect_क्रमmats = snd_dice_stream_detect_current_क्रमmats;
	पूर्ण अन्यथा अणु
		dice->detect_क्रमmats =
				(snd_dice_detect_क्रमmats_t)entry->driver_data;
	पूर्ण

	// Below models are compliant to IEC 61883-1/6 and have no quirk at high sampling transfer
	// frequency.
	// * Avid M-Box 3 Pro
	// * M-Audio Profire 610
	// * M-Audio Profire 2626
	अगर (entry->venकरोr_id == OUI_MAUDIO || entry->venकरोr_id == OUI_AVID)
		dice->disable_द्विगुन_pcm_frames = true;

	spin_lock_init(&dice->lock);
	mutex_init(&dice->mutex);
	init_completion(&dice->घड़ी_accepted);
	init_रुकोqueue_head(&dice->hwdep_रुको);

	/* Allocate and रेजिस्टर this sound card later. */
	INIT_DEFERRABLE_WORK(&dice->dwork, करो_registration);
	snd_fw_schedule_registration(unit, &dice->dwork);

	वापस 0;
पूर्ण

अटल व्योम dice_हटाओ(काष्ठा fw_unit *unit)
अणु
	काष्ठा snd_dice *dice = dev_get_drvdata(&unit->device);

	/*
	 * Confirm to stop the work क्रम registration beक्रमe the sound card is
	 * going to be released. The work is not scheduled again because bus
	 * reset handler is not called anymore.
	 */
	cancel_delayed_work_sync(&dice->dwork);

	अगर (dice->रेजिस्टरed) अणु
		// Block till all of ALSA अक्षरacter devices are released.
		snd_card_मुक्त(dice->card);
	पूर्ण

	mutex_destroy(&dice->mutex);
	fw_unit_put(dice->unit);
पूर्ण

अटल व्योम dice_bus_reset(काष्ठा fw_unit *unit)
अणु
	काष्ठा snd_dice *dice = dev_get_drvdata(&unit->device);

	/* Postpone a workqueue क्रम deferred registration. */
	अगर (!dice->रेजिस्टरed)
		snd_fw_schedule_registration(unit, &dice->dwork);

	/* The handler address रेजिस्टर becomes initialized. */
	snd_dice_transaction_reinit(dice);

	/*
	 * After registration, userspace can start packet streaming, then this
	 * code block works fine.
	 */
	अगर (dice->रेजिस्टरed) अणु
		mutex_lock(&dice->mutex);
		snd_dice_stream_update_duplex(dice);
		mutex_unlock(&dice->mutex);
	पूर्ण
पूर्ण

#घोषणा DICE_INTERFACE	0x000001

#घोषणा DICE_DEV_ENTRY_TYPICAL(venकरोr, model, data) \
	अणु \
		.match_flags	= IEEE1394_MATCH_VENDOR_ID | \
				  IEEE1394_MATCH_MODEL_ID | \
				  IEEE1394_MATCH_SPECIFIER_ID | \
				  IEEE1394_MATCH_VERSION, \
		.venकरोr_id	= (venकरोr), \
		.model_id	= (model), \
		.specअगरier_id	= (venकरोr), \
		.version	= DICE_INTERFACE, \
		.driver_data = (kernel_uदीर्घ_t)(data), \
	पूर्ण

अटल स्थिर काष्ठा ieee1394_device_id dice_id_table[] = अणु
	// Avid M-Box 3 Pro. To match in probe function.
	DICE_DEV_ENTRY_TYPICAL(OUI_AVID, 0x000004, snd_dice_detect_extension_क्रमmats),
	/* M-Audio Profire 2626 has a dअगरferent value in version field. */
	अणु
		.match_flags	= IEEE1394_MATCH_VENDOR_ID |
				  IEEE1394_MATCH_MODEL_ID,
		.venकरोr_id	= OUI_MAUDIO,
		.model_id	= 0x000010,
		.driver_data = (kernel_uदीर्घ_t)snd_dice_detect_extension_क्रमmats,
	पूर्ण,
	/* M-Audio Profire 610 has a dअगरferent value in version field. */
	अणु
		.match_flags	= IEEE1394_MATCH_VENDOR_ID |
				  IEEE1394_MATCH_MODEL_ID,
		.venकरोr_id	= OUI_MAUDIO,
		.model_id	= 0x000011,
		.driver_data = (kernel_uदीर्घ_t)snd_dice_detect_extension_क्रमmats,
	पूर्ण,
	/* TC Electronic Konnekt 24D. */
	अणु
		.match_flags	= IEEE1394_MATCH_VENDOR_ID |
				  IEEE1394_MATCH_MODEL_ID,
		.venकरोr_id	= OUI_TCELECTRONIC,
		.model_id	= 0x000020,
		.driver_data = (kernel_uदीर्घ_t)snd_dice_detect_tcelectronic_क्रमmats,
	पूर्ण,
	/* TC Electronic Konnekt 8. */
	अणु
		.match_flags	= IEEE1394_MATCH_VENDOR_ID |
				  IEEE1394_MATCH_MODEL_ID,
		.venकरोr_id	= OUI_TCELECTRONIC,
		.model_id	= 0x000021,
		.driver_data = (kernel_uदीर्घ_t)snd_dice_detect_tcelectronic_क्रमmats,
	पूर्ण,
	/* TC Electronic Studio Konnekt 48. */
	अणु
		.match_flags	= IEEE1394_MATCH_VENDOR_ID |
				  IEEE1394_MATCH_MODEL_ID,
		.venकरोr_id	= OUI_TCELECTRONIC,
		.model_id	= 0x000022,
		.driver_data = (kernel_uदीर्घ_t)snd_dice_detect_tcelectronic_क्रमmats,
	पूर्ण,
	/* TC Electronic Konnekt Live. */
	अणु
		.match_flags	= IEEE1394_MATCH_VENDOR_ID |
				  IEEE1394_MATCH_MODEL_ID,
		.venकरोr_id	= OUI_TCELECTRONIC,
		.model_id	= 0x000023,
		.driver_data = (kernel_uदीर्घ_t)snd_dice_detect_tcelectronic_क्रमmats,
	पूर्ण,
	/* TC Electronic Desktop Konnekt 6. */
	अणु
		.match_flags	= IEEE1394_MATCH_VENDOR_ID |
				  IEEE1394_MATCH_MODEL_ID,
		.venकरोr_id	= OUI_TCELECTRONIC,
		.model_id	= 0x000024,
		.driver_data = (kernel_uदीर्घ_t)snd_dice_detect_tcelectronic_क्रमmats,
	पूर्ण,
	/* TC Electronic Impact Twin. */
	अणु
		.match_flags	= IEEE1394_MATCH_VENDOR_ID |
				  IEEE1394_MATCH_MODEL_ID,
		.venकरोr_id	= OUI_TCELECTRONIC,
		.model_id	= 0x000027,
		.driver_data = (kernel_uदीर्घ_t)snd_dice_detect_tcelectronic_क्रमmats,
	पूर्ण,
	/* TC Electronic Digital Konnekt x32. */
	अणु
		.match_flags	= IEEE1394_MATCH_VENDOR_ID |
				  IEEE1394_MATCH_MODEL_ID,
		.venकरोr_id	= OUI_TCELECTRONIC,
		.model_id	= 0x000030,
		.driver_data = (kernel_uदीर्घ_t)snd_dice_detect_tcelectronic_क्रमmats,
	पूर्ण,
	/* Alesis iO14/iO26. */
	अणु
		.match_flags	= IEEE1394_MATCH_VENDOR_ID |
				  IEEE1394_MATCH_MODEL_ID,
		.venकरोr_id	= OUI_ALESIS,
		.model_id	= MODEL_ALESIS_IO_BOTH,
		.driver_data = (kernel_uदीर्घ_t)snd_dice_detect_alesis_क्रमmats,
	पूर्ण,
	// Alesis MasterControl.
	अणु
		.match_flags	= IEEE1394_MATCH_VENDOR_ID |
				  IEEE1394_MATCH_MODEL_ID,
		.venकरोr_id	= OUI_ALESIS,
		.model_id	= 0x000002,
		.driver_data = (kernel_uदीर्घ_t)snd_dice_detect_alesis_mastercontrol_क्रमmats,
	पूर्ण,
	/* Mytek Stereo 192 DSD-DAC. */
	अणु
		.match_flags	= IEEE1394_MATCH_VENDOR_ID |
				  IEEE1394_MATCH_MODEL_ID,
		.venकरोr_id	= OUI_MYTEK,
		.model_id	= 0x000002,
		.driver_data = (kernel_uदीर्घ_t)snd_dice_detect_mytek_क्रमmats,
	पूर्ण,
	// Solid State Logic, Duende Classic and Mini.
	// NOTE: each field of GUID in config ROM is not compliant to standard
	// DICE scheme.
	अणु
		.match_flags	= IEEE1394_MATCH_VENDOR_ID |
				  IEEE1394_MATCH_MODEL_ID,
		.venकरोr_id	= OUI_SSL,
		.model_id	= 0x000070,
	पूर्ण,
	// Presonus FireStudio.
	अणु
		.match_flags	= IEEE1394_MATCH_VENDOR_ID |
				  IEEE1394_MATCH_MODEL_ID,
		.venकरोr_id	= OUI_PRESONUS,
		.model_id	= 0x000008,
		.driver_data	= (kernel_uदीर्घ_t)snd_dice_detect_presonus_क्रमmats,
	पूर्ण,
	// Lexicon I-ONYX FW810S.
	अणु
		.match_flags	= IEEE1394_MATCH_VENDOR_ID |
				  IEEE1394_MATCH_MODEL_ID,
		.venकरोr_id	= OUI_HARMAN,
		.model_id	= 0x000001,
		.driver_data	= (kernel_uदीर्घ_t)snd_dice_detect_harman_क्रमmats,
	पूर्ण,
	अणु
		.match_flags = IEEE1394_MATCH_VERSION,
		.version     = DICE_INTERFACE,
	पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(ieee1394, dice_id_table);

अटल काष्ठा fw_driver dice_driver = अणु
	.driver   = अणु
		.owner	= THIS_MODULE,
		.name	= KBUILD_MODNAME,
		.bus	= &fw_bus_type,
	पूर्ण,
	.probe    = dice_probe,
	.update   = dice_bus_reset,
	.हटाओ   = dice_हटाओ,
	.id_table = dice_id_table,
पूर्ण;

अटल पूर्णांक __init alsa_dice_init(व्योम)
अणु
	वापस driver_रेजिस्टर(&dice_driver.driver);
पूर्ण

अटल व्योम __निकास alsa_dice_निकास(व्योम)
अणु
	driver_unरेजिस्टर(&dice_driver.driver);
पूर्ण

module_init(alsa_dice_init);
module_निकास(alsa_dice_निकास);
