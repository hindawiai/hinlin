<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * tascam.c - a part of driver क्रम TASCAM FireWire series
 *
 * Copyright (c) 2015 Takashi Sakamoto
 */

#समावेश "tascam.h"

MODULE_DESCRIPTION("TASCAM FireWire series Driver");
MODULE_AUTHOR("Takashi Sakamoto <o-takashi@sakamocchi.jp>");
MODULE_LICENSE("GPL v2");

अटल स्थिर काष्ठा snd_tscm_spec model_specs[] = अणु
	अणु
		.name = "FW-1884",
		.has_adat = true,
		.has_spdअगर = true,
		.pcm_capture_analog_channels = 8,
		.pcm_playback_analog_channels = 8,
		.midi_capture_ports = 4,
		.midi_playback_ports = 4,
	पूर्ण,
	अणु
		.name = "FW-1082",
		.has_adat = false,
		.has_spdअगर = true,
		.pcm_capture_analog_channels = 8,
		.pcm_playback_analog_channels = 2,
		.midi_capture_ports = 2,
		.midi_playback_ports = 2,
	पूर्ण,
	अणु
		.name = "FW-1804",
		.has_adat = true,
		.has_spdअगर = true,
		.pcm_capture_analog_channels = 8,
		.pcm_playback_analog_channels = 2,
		.midi_capture_ports = 2,
		.midi_playback_ports = 4,
	पूर्ण,
पूर्ण;

अटल पूर्णांक identअगरy_model(काष्ठा snd_tscm *tscm)
अणु
	काष्ठा fw_device *fw_dev = fw_parent_device(tscm->unit);
	स्थिर u32 *config_rom = fw_dev->config_rom;
	अक्षर model[9];
	अचिन्हित पूर्णांक i;
	u8 c;

	अगर (fw_dev->config_rom_length < 30) अणु
		dev_err(&tscm->unit->device,
			"Configuration ROM is too short.\n");
		वापस -ENODEV;
	पूर्ण

	/* Pick up model name from certain addresses. */
	क्रम (i = 0; i < 8; i++) अणु
		c = config_rom[28 + i / 4] >> (24 - 8 * (i % 4));
		अगर (c == '\0')
			अवरोध;
		model[i] = c;
	पूर्ण
	model[i] = '\0';

	क्रम (i = 0; i < ARRAY_SIZE(model_specs); i++) अणु
		अगर (म_भेद(model, model_specs[i].name) == 0) अणु
			tscm->spec = &model_specs[i];
			अवरोध;
		पूर्ण
	पूर्ण
	अगर (tscm->spec == शून्य)
		वापस -ENODEV;

	म_नकल(tscm->card->driver, "FW-TASCAM");
	म_नकल(tscm->card->लघुname, model);
	म_नकल(tscm->card->mixername, model);
	snम_लिखो(tscm->card->दीर्घname, माप(tscm->card->दीर्घname),
		 "TASCAM %s, GUID %08x%08x at %s, S%d", model,
		 fw_dev->config_rom[3], fw_dev->config_rom[4],
		 dev_name(&tscm->unit->device), 100 << fw_dev->max_speed);

	वापस 0;
पूर्ण

अटल व्योम tscm_card_मुक्त(काष्ठा snd_card *card)
अणु
	काष्ठा snd_tscm *tscm = card->निजी_data;

	snd_tscm_transaction_unरेजिस्टर(tscm);
	snd_tscm_stream_destroy_duplex(tscm);
पूर्ण

अटल व्योम करो_registration(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा snd_tscm *tscm = container_of(work, काष्ठा snd_tscm, dwork.work);
	पूर्णांक err;

	err = snd_card_new(&tscm->unit->device, -1, शून्य, THIS_MODULE, 0,
			   &tscm->card);
	अगर (err < 0)
		वापस;
	tscm->card->निजी_मुक्त = tscm_card_मुक्त;
	tscm->card->निजी_data = tscm;

	err = identअगरy_model(tscm);
	अगर (err < 0)
		जाओ error;

	err = snd_tscm_transaction_रेजिस्टर(tscm);
	अगर (err < 0)
		जाओ error;

	err = snd_tscm_stream_init_duplex(tscm);
	अगर (err < 0)
		जाओ error;

	snd_tscm_proc_init(tscm);

	err = snd_tscm_create_pcm_devices(tscm);
	अगर (err < 0)
		जाओ error;

	err = snd_tscm_create_midi_devices(tscm);
	अगर (err < 0)
		जाओ error;

	err = snd_tscm_create_hwdep_device(tscm);
	अगर (err < 0)
		जाओ error;

	err = snd_card_रेजिस्टर(tscm->card);
	अगर (err < 0)
		जाओ error;

	tscm->रेजिस्टरed = true;

	वापस;
error:
	snd_card_मुक्त(tscm->card);
	dev_info(&tscm->unit->device,
		 "Sound card registration failed: %d\n", err);
पूर्ण

अटल पूर्णांक snd_tscm_probe(काष्ठा fw_unit *unit,
			   स्थिर काष्ठा ieee1394_device_id *entry)
अणु
	काष्ठा snd_tscm *tscm;

	/* Allocate this independent of sound card instance. */
	tscm = devm_kzalloc(&unit->device, माप(काष्ठा snd_tscm), GFP_KERNEL);
	अगर (!tscm)
		वापस -ENOMEM;
	tscm->unit = fw_unit_get(unit);
	dev_set_drvdata(&unit->device, tscm);

	mutex_init(&tscm->mutex);
	spin_lock_init(&tscm->lock);
	init_रुकोqueue_head(&tscm->hwdep_रुको);

	/* Allocate and रेजिस्टर this sound card later. */
	INIT_DEFERRABLE_WORK(&tscm->dwork, करो_registration);
	snd_fw_schedule_registration(unit, &tscm->dwork);

	वापस 0;
पूर्ण

अटल व्योम snd_tscm_update(काष्ठा fw_unit *unit)
अणु
	काष्ठा snd_tscm *tscm = dev_get_drvdata(&unit->device);

	/* Postpone a workqueue क्रम deferred registration. */
	अगर (!tscm->रेजिस्टरed)
		snd_fw_schedule_registration(unit, &tscm->dwork);

	snd_tscm_transaction_reरेजिस्टर(tscm);

	/*
	 * After registration, userspace can start packet streaming, then this
	 * code block works fine.
	 */
	अगर (tscm->रेजिस्टरed) अणु
		mutex_lock(&tscm->mutex);
		snd_tscm_stream_update_duplex(tscm);
		mutex_unlock(&tscm->mutex);
	पूर्ण
पूर्ण

अटल व्योम snd_tscm_हटाओ(काष्ठा fw_unit *unit)
अणु
	काष्ठा snd_tscm *tscm = dev_get_drvdata(&unit->device);

	/*
	 * Confirm to stop the work क्रम registration beक्रमe the sound card is
	 * going to be released. The work is not scheduled again because bus
	 * reset handler is not called anymore.
	 */
	cancel_delayed_work_sync(&tscm->dwork);

	अगर (tscm->रेजिस्टरed) अणु
		// Block till all of ALSA अक्षरacter devices are released.
		snd_card_मुक्त(tscm->card);
	पूर्ण

	mutex_destroy(&tscm->mutex);
	fw_unit_put(tscm->unit);
पूर्ण

अटल स्थिर काष्ठा ieee1394_device_id snd_tscm_id_table[] = अणु
	// Tascam, FW-1884.
	अणु
		.match_flags = IEEE1394_MATCH_VENDOR_ID |
			       IEEE1394_MATCH_SPECIFIER_ID |
			       IEEE1394_MATCH_VERSION,
		.venकरोr_id = 0x00022e,
		.specअगरier_id = 0x00022e,
		.version = 0x800000,
	पूर्ण,
	// Tascam, FE-8 (.version = 0x800001)
	// This kernel module करोesn't support FE-8 because the most of features
	// can be implemented in userspace without any specअगरic support of this
	// module.
	//
	// .version = 0x800002 is unknown.
	//
	// Tascam, FW-1082.
	अणु
		.match_flags = IEEE1394_MATCH_VENDOR_ID |
			       IEEE1394_MATCH_SPECIFIER_ID |
			       IEEE1394_MATCH_VERSION,
		.venकरोr_id = 0x00022e,
		.specअगरier_id = 0x00022e,
		.version = 0x800003,
	पूर्ण,
	// Tascam, FW-1804.
	अणु
		.match_flags = IEEE1394_MATCH_VENDOR_ID |
			       IEEE1394_MATCH_SPECIFIER_ID |
			       IEEE1394_MATCH_VERSION,
		.venकरोr_id = 0x00022e,
		.specअगरier_id = 0x00022e,
		.version = 0x800004,
	पूर्ण,
	अणुपूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(ieee1394, snd_tscm_id_table);

अटल काष्ठा fw_driver tscm_driver = अणु
	.driver = अणु
		.owner = THIS_MODULE,
		.name = KBUILD_MODNAME,
		.bus = &fw_bus_type,
	पूर्ण,
	.probe    = snd_tscm_probe,
	.update   = snd_tscm_update,
	.हटाओ   = snd_tscm_हटाओ,
	.id_table = snd_tscm_id_table,
पूर्ण;

अटल पूर्णांक __init snd_tscm_init(व्योम)
अणु
	वापस driver_रेजिस्टर(&tscm_driver.driver);
पूर्ण

अटल व्योम __निकास snd_tscm_निकास(व्योम)
अणु
	driver_unरेजिस्टर(&tscm_driver.driver);
पूर्ण

module_init(snd_tscm_init);
module_निकास(snd_tscm_निकास);
