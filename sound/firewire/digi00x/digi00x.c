<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * digi00x.c - a part of driver क्रम Digidesign Digi 002/003 family
 *
 * Copyright (c) 2014-2015 Takashi Sakamoto
 */

#समावेश "digi00x.h"

MODULE_DESCRIPTION("Digidesign Digi 002/003 family Driver");
MODULE_AUTHOR("Takashi Sakamoto <o-takashi@sakamocchi.jp>");
MODULE_LICENSE("GPL v2");

#घोषणा VENDOR_DIGIDESIGN	0x00a07e
#घोषणा MODEL_CONSOLE		0x000001
#घोषणा MODEL_RACK		0x000002
#घोषणा SPEC_VERSION		0x000001

अटल पूर्णांक name_card(काष्ठा snd_dg00x *dg00x)
अणु
	काष्ठा fw_device *fw_dev = fw_parent_device(dg00x->unit);
	अक्षर name[32] = अणु0पूर्ण;
	अक्षर *model;
	पूर्णांक err;

	err = fw_csr_string(dg00x->unit->directory, CSR_MODEL, name,
			    माप(name));
	अगर (err < 0)
		वापस err;

	model = skip_spaces(name);

	म_नकल(dg00x->card->driver, "Digi00x");
	म_नकल(dg00x->card->लघुname, model);
	म_नकल(dg00x->card->mixername, model);
	snम_लिखो(dg00x->card->दीर्घname, माप(dg00x->card->दीर्घname),
		 "Digidesign %s, GUID %08x%08x at %s, S%d", model,
		 fw_dev->config_rom[3], fw_dev->config_rom[4],
		 dev_name(&dg00x->unit->device), 100 << fw_dev->max_speed);

	वापस 0;
पूर्ण

अटल व्योम dg00x_card_मुक्त(काष्ठा snd_card *card)
अणु
	काष्ठा snd_dg00x *dg00x = card->निजी_data;

	snd_dg00x_stream_destroy_duplex(dg00x);
	snd_dg00x_transaction_unरेजिस्टर(dg00x);
पूर्ण

अटल व्योम करो_registration(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा snd_dg00x *dg00x =
			container_of(work, काष्ठा snd_dg00x, dwork.work);
	पूर्णांक err;

	अगर (dg00x->रेजिस्टरed)
		वापस;

	err = snd_card_new(&dg00x->unit->device, -1, शून्य, THIS_MODULE, 0,
			   &dg00x->card);
	अगर (err < 0)
		वापस;
	dg00x->card->निजी_मुक्त = dg00x_card_मुक्त;
	dg00x->card->निजी_data = dg00x;

	err = name_card(dg00x);
	अगर (err < 0)
		जाओ error;

	err = snd_dg00x_stream_init_duplex(dg00x);
	अगर (err < 0)
		जाओ error;

	snd_dg00x_proc_init(dg00x);

	err = snd_dg00x_create_pcm_devices(dg00x);
	अगर (err < 0)
		जाओ error;

	err = snd_dg00x_create_midi_devices(dg00x);
	अगर (err < 0)
		जाओ error;

	err = snd_dg00x_create_hwdep_device(dg00x);
	अगर (err < 0)
		जाओ error;

	err = snd_dg00x_transaction_रेजिस्टर(dg00x);
	अगर (err < 0)
		जाओ error;

	err = snd_card_रेजिस्टर(dg00x->card);
	अगर (err < 0)
		जाओ error;

	dg00x->रेजिस्टरed = true;

	वापस;
error:
	snd_card_मुक्त(dg00x->card);
	dev_info(&dg00x->unit->device,
		 "Sound card registration failed: %d\n", err);
पूर्ण

अटल पूर्णांक snd_dg00x_probe(काष्ठा fw_unit *unit,
			   स्थिर काष्ठा ieee1394_device_id *entry)
अणु
	काष्ठा snd_dg00x *dg00x;

	/* Allocate this independent of sound card instance. */
	dg00x = devm_kzalloc(&unit->device, माप(काष्ठा snd_dg00x),
			     GFP_KERNEL);
	अगर (!dg00x)
		वापस -ENOMEM;

	dg00x->unit = fw_unit_get(unit);
	dev_set_drvdata(&unit->device, dg00x);

	mutex_init(&dg00x->mutex);
	spin_lock_init(&dg00x->lock);
	init_रुकोqueue_head(&dg00x->hwdep_रुको);

	dg00x->is_console = entry->model_id == MODEL_CONSOLE;

	/* Allocate and रेजिस्टर this sound card later. */
	INIT_DEFERRABLE_WORK(&dg00x->dwork, करो_registration);
	snd_fw_schedule_registration(unit, &dg00x->dwork);

	वापस 0;
पूर्ण

अटल व्योम snd_dg00x_update(काष्ठा fw_unit *unit)
अणु
	काष्ठा snd_dg00x *dg00x = dev_get_drvdata(&unit->device);

	/* Postpone a workqueue क्रम deferred registration. */
	अगर (!dg00x->रेजिस्टरed)
		snd_fw_schedule_registration(unit, &dg00x->dwork);

	snd_dg00x_transaction_reरेजिस्टर(dg00x);

	/*
	 * After registration, userspace can start packet streaming, then this
	 * code block works fine.
	 */
	अगर (dg00x->रेजिस्टरed) अणु
		mutex_lock(&dg00x->mutex);
		snd_dg00x_stream_update_duplex(dg00x);
		mutex_unlock(&dg00x->mutex);
	पूर्ण
पूर्ण

अटल व्योम snd_dg00x_हटाओ(काष्ठा fw_unit *unit)
अणु
	काष्ठा snd_dg00x *dg00x = dev_get_drvdata(&unit->device);

	/*
	 * Confirm to stop the work क्रम registration beक्रमe the sound card is
	 * going to be released. The work is not scheduled again because bus
	 * reset handler is not called anymore.
	 */
	cancel_delayed_work_sync(&dg00x->dwork);

	अगर (dg00x->रेजिस्टरed) अणु
		// Block till all of ALSA अक्षरacter devices are released.
		snd_card_मुक्त(dg00x->card);
	पूर्ण

	mutex_destroy(&dg00x->mutex);
	fw_unit_put(dg00x->unit);
पूर्ण

अटल स्थिर काष्ठा ieee1394_device_id snd_dg00x_id_table[] = अणु
	/* Both of 002/003 use the same ID. */
	अणु
		.match_flags = IEEE1394_MATCH_VENDOR_ID |
			       IEEE1394_MATCH_VERSION |
			       IEEE1394_MATCH_MODEL_ID,
		.venकरोr_id = VENDOR_DIGIDESIGN,
		.version = SPEC_VERSION,
		.model_id = MODEL_CONSOLE,
	पूर्ण,
	अणु
		.match_flags = IEEE1394_MATCH_VENDOR_ID |
			       IEEE1394_MATCH_VERSION |
			       IEEE1394_MATCH_MODEL_ID,
		.venकरोr_id = VENDOR_DIGIDESIGN,
		.version = SPEC_VERSION,
		.model_id = MODEL_RACK,
	पूर्ण,
	अणुपूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(ieee1394, snd_dg00x_id_table);

अटल काष्ठा fw_driver dg00x_driver = अणु
	.driver = अणु
		.owner = THIS_MODULE,
		.name = KBUILD_MODNAME,
		.bus = &fw_bus_type,
	पूर्ण,
	.probe    = snd_dg00x_probe,
	.update   = snd_dg00x_update,
	.हटाओ   = snd_dg00x_हटाओ,
	.id_table = snd_dg00x_id_table,
पूर्ण;

अटल पूर्णांक __init snd_dg00x_init(व्योम)
अणु
	वापस driver_रेजिस्टर(&dg00x_driver.driver);
पूर्ण

अटल व्योम __निकास snd_dg00x_निकास(व्योम)
अणु
	driver_unरेजिस्टर(&dg00x_driver.driver);
पूर्ण

module_init(snd_dg00x_init);
module_निकास(snd_dg00x_निकास);
