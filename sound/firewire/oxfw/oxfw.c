<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * oxfw.c - a part of driver क्रम OXFW970/971 based devices
 *
 * Copyright (c) Clemens Ladisch <clemens@ladisch.de>
 */

#समावेश "oxfw.h"

#घोषणा OXFORD_FIRMWARE_ID_ADDRESS	(CSR_REGISTER_BASE + 0x50000)
/* 0x970?vvvv or 0x971?vvvv, where vvvv = firmware version */

#घोषणा OXFORD_HARDWARE_ID_ADDRESS	(CSR_REGISTER_BASE + 0x90020)
#घोषणा OXFORD_HARDWARE_ID_OXFW970	0x39443841
#घोषणा OXFORD_HARDWARE_ID_OXFW971	0x39373100

#घोषणा VENDOR_LOUD		0x000ff2
#घोषणा VENDOR_GRIFFIN		0x001292
#घोषणा VENDOR_BEHRINGER	0x001564
#घोषणा VENDOR_LACIE		0x00d04b
#घोषणा VENDOR_TASCAM		0x00022e
#घोषणा OUI_STANTON		0x001260
#घोषणा OUI_APOGEE		0x0003db

#घोषणा MODEL_SATELLITE		0x00200f

#घोषणा SPECIFIER_1394TA	0x00a02d
#घोषणा VERSION_AVC		0x010001

MODULE_DESCRIPTION("Oxford Semiconductor FW970/971 driver");
MODULE_AUTHOR("Clemens Ladisch <clemens@ladisch.de>");
MODULE_LICENSE("GPL v2");
MODULE_ALIAS("snd-firewire-speakers");
MODULE_ALIAS("snd-scs1x");

काष्ठा compat_info अणु
	स्थिर अक्षर *driver_name;
	स्थिर अक्षर *venकरोr_name;
	स्थिर अक्षर *model_name;
पूर्ण;

अटल bool detect_loud_models(काष्ठा fw_unit *unit)
अणु
	स्थिर अक्षर *स्थिर models[] = अणु
		"Onyxi",
		"Onyx-i",
		"Onyx 1640i",
		"d.Pro",
		"Mackie Onyx Satellite",
		"Tapco LINK.firewire 4x6",
		"U.420"पूर्ण;
	अक्षर model[32];
	पूर्णांक err;

	err = fw_csr_string(unit->directory, CSR_MODEL,
			    model, माप(model));
	अगर (err < 0)
		वापस false;

	वापस match_string(models, ARRAY_SIZE(models), model) >= 0;
पूर्ण

अटल पूर्णांक name_card(काष्ठा snd_oxfw *oxfw)
अणु
	काष्ठा fw_device *fw_dev = fw_parent_device(oxfw->unit);
	स्थिर काष्ठा compat_info *info;
	अक्षर venकरोr[24];
	अक्षर model[32];
	स्थिर अक्षर *d, *v, *m;
	u32 firmware;
	पूर्णांक err;

	/* get venकरोr name from root directory */
	err = fw_csr_string(fw_dev->config_rom + 5, CSR_VENDOR,
			    venकरोr, माप(venकरोr));
	अगर (err < 0)
		जाओ end;

	/* get model name from unit directory */
	err = fw_csr_string(oxfw->unit->directory, CSR_MODEL,
			    model, माप(model));
	अगर (err < 0)
		जाओ end;

	err = snd_fw_transaction(oxfw->unit, TCODE_READ_QUADLET_REQUEST,
				 OXFORD_FIRMWARE_ID_ADDRESS, &firmware, 4, 0);
	अगर (err < 0)
		जाओ end;
	be32_to_cpus(&firmware);

	/* to apply card definitions */
	अगर (oxfw->entry->venकरोr_id == VENDOR_GRIFFIN ||
	    oxfw->entry->venकरोr_id == VENDOR_LACIE) अणु
		info = (स्थिर काष्ठा compat_info *)oxfw->entry->driver_data;
		d = info->driver_name;
		v = info->venकरोr_name;
		m = info->model_name;
	पूर्ण अन्यथा अणु
		d = "OXFW";
		v = venकरोr;
		m = model;
	पूर्ण

	म_नकल(oxfw->card->driver, d);
	म_नकल(oxfw->card->mixername, m);
	म_नकल(oxfw->card->लघुname, m);

	snम_लिखो(oxfw->card->दीर्घname, माप(oxfw->card->दीर्घname),
		 "%s %s (OXFW%x %04x), GUID %08x%08x at %s, S%d",
		 v, m, firmware >> 20, firmware & 0xffff,
		 fw_dev->config_rom[3], fw_dev->config_rom[4],
		 dev_name(&oxfw->unit->device), 100 << fw_dev->max_speed);
end:
	वापस err;
पूर्ण

अटल व्योम oxfw_card_मुक्त(काष्ठा snd_card *card)
अणु
	काष्ठा snd_oxfw *oxfw = card->निजी_data;

	अगर (oxfw->has_output || oxfw->has_input)
		snd_oxfw_stream_destroy_duplex(oxfw);
पूर्ण

अटल पूर्णांक detect_quirks(काष्ठा snd_oxfw *oxfw)
अणु
	काष्ठा fw_device *fw_dev = fw_parent_device(oxfw->unit);
	काष्ठा fw_csr_iterator it;
	पूर्णांक key, val;
	पूर्णांक venकरोr, model;

	/*
	 * Add ALSA control elements क्रम two models to keep compatibility to
	 * old firewire-speaker module.
	 */
	अगर (oxfw->entry->venकरोr_id == VENDOR_GRIFFIN)
		वापस snd_oxfw_add_spkr(oxfw, false);
	अगर (oxfw->entry->venकरोr_id == VENDOR_LACIE)
		वापस snd_oxfw_add_spkr(oxfw, true);

	/*
	 * Stanton models supports asynchronous transactions क्रम unique MIDI
	 * messages.
	 */
	अगर (oxfw->entry->venकरोr_id == OUI_STANTON) अणु
		/* No physical MIDI ports. */
		oxfw->midi_input_ports = 0;
		oxfw->midi_output_ports = 0;

		वापस snd_oxfw_scs1x_add(oxfw);
	पूर्ण

	/*
	 * TASCAM FireOne has physical control and requires a pair of additional
	 * MIDI ports.
	 */
	अगर (oxfw->entry->venकरोr_id == VENDOR_TASCAM) अणु
		oxfw->midi_input_ports++;
		oxfw->midi_output_ports++;
		वापस 0;
	पूर्ण

	/* Seek from Root Directory of Config ROM. */
	venकरोr = model = 0;
	fw_csr_iterator_init(&it, fw_dev->config_rom + 5);
	जबतक (fw_csr_iterator_next(&it, &key, &val)) अणु
		अगर (key == CSR_VENDOR)
			venकरोr = val;
		अन्यथा अगर (key == CSR_MODEL)
			model = val;
	पूर्ण

	/*
	 * Mackie Onyx Satellite with base station has a quirk to report a wrong
	 * value in 'dbs' field of CIP header against its क्रमmat inक्रमmation.
	 */
	अगर (venकरोr == VENDOR_LOUD && model == MODEL_SATELLITE)
		oxfw->wrong_dbs = true;

	वापस 0;
पूर्ण

अटल व्योम करो_registration(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा snd_oxfw *oxfw = container_of(work, काष्ठा snd_oxfw, dwork.work);
	पूर्णांक err;

	अगर (oxfw->रेजिस्टरed)
		वापस;

	err = snd_card_new(&oxfw->unit->device, -1, शून्य, THIS_MODULE, 0,
			   &oxfw->card);
	अगर (err < 0)
		वापस;
	oxfw->card->निजी_मुक्त = oxfw_card_मुक्त;
	oxfw->card->निजी_data = oxfw;

	err = name_card(oxfw);
	अगर (err < 0)
		जाओ error;

	err = snd_oxfw_stream_discover(oxfw);
	अगर (err < 0)
		जाओ error;

	err = detect_quirks(oxfw);
	अगर (err < 0)
		जाओ error;

	अगर (oxfw->has_output || oxfw->has_input) अणु
		err = snd_oxfw_stream_init_duplex(oxfw);
		अगर (err < 0)
			जाओ error;

		err = snd_oxfw_create_pcm(oxfw);
		अगर (err < 0)
			जाओ error;

		snd_oxfw_proc_init(oxfw);

		err = snd_oxfw_create_midi(oxfw);
		अगर (err < 0)
			जाओ error;

		err = snd_oxfw_create_hwdep(oxfw);
		अगर (err < 0)
			जाओ error;
	पूर्ण

	err = snd_card_रेजिस्टर(oxfw->card);
	अगर (err < 0)
		जाओ error;

	oxfw->रेजिस्टरed = true;

	वापस;
error:
	snd_card_मुक्त(oxfw->card);
	dev_info(&oxfw->unit->device,
		 "Sound card registration failed: %d\n", err);
पूर्ण

अटल पूर्णांक oxfw_probe(काष्ठा fw_unit *unit,
		      स्थिर काष्ठा ieee1394_device_id *entry)
अणु
	काष्ठा snd_oxfw *oxfw;

	अगर (entry->venकरोr_id == VENDOR_LOUD && !detect_loud_models(unit))
		वापस -ENODEV;

	/* Allocate this independent of sound card instance. */
	oxfw = devm_kzalloc(&unit->device, माप(काष्ठा snd_oxfw), GFP_KERNEL);
	अगर (!oxfw)
		वापस -ENOMEM;
	oxfw->unit = fw_unit_get(unit);
	dev_set_drvdata(&unit->device, oxfw);

	oxfw->entry = entry;
	mutex_init(&oxfw->mutex);
	spin_lock_init(&oxfw->lock);
	init_रुकोqueue_head(&oxfw->hwdep_रुको);

	/* Allocate and रेजिस्टर this sound card later. */
	INIT_DEFERRABLE_WORK(&oxfw->dwork, करो_registration);
	snd_fw_schedule_registration(unit, &oxfw->dwork);

	वापस 0;
पूर्ण

अटल व्योम oxfw_bus_reset(काष्ठा fw_unit *unit)
अणु
	काष्ठा snd_oxfw *oxfw = dev_get_drvdata(&unit->device);

	अगर (!oxfw->रेजिस्टरed)
		snd_fw_schedule_registration(unit, &oxfw->dwork);

	fcp_bus_reset(oxfw->unit);

	अगर (oxfw->रेजिस्टरed) अणु
		अगर (oxfw->has_output || oxfw->has_input) अणु
			mutex_lock(&oxfw->mutex);
			snd_oxfw_stream_update_duplex(oxfw);
			mutex_unlock(&oxfw->mutex);
		पूर्ण

		अगर (oxfw->entry->venकरोr_id == OUI_STANTON)
			snd_oxfw_scs1x_update(oxfw);
	पूर्ण
पूर्ण

अटल व्योम oxfw_हटाओ(काष्ठा fw_unit *unit)
अणु
	काष्ठा snd_oxfw *oxfw = dev_get_drvdata(&unit->device);

	/*
	 * Confirm to stop the work क्रम registration beक्रमe the sound card is
	 * going to be released. The work is not scheduled again because bus
	 * reset handler is not called anymore.
	 */
	cancel_delayed_work_sync(&oxfw->dwork);

	अगर (oxfw->रेजिस्टरed) अणु
		// Block till all of ALSA अक्षरacter devices are released.
		snd_card_मुक्त(oxfw->card);
	पूर्ण

	mutex_destroy(&oxfw->mutex);
	fw_unit_put(oxfw->unit);
पूर्ण

अटल स्थिर काष्ठा compat_info grअगरfin_firewave = अणु
	.driver_name = "FireWave",
	.venकरोr_name = "Griffin",
	.model_name = "FireWave",
पूर्ण;

अटल स्थिर काष्ठा compat_info lacie_speakers = अणु
	.driver_name = "FWSpeakers",
	.venकरोr_name = "LaCie",
	.model_name = "FireWire Speakers",
पूर्ण;

अटल स्थिर काष्ठा ieee1394_device_id oxfw_id_table[] = अणु
	अणु
		.match_flags  = IEEE1394_MATCH_VENDOR_ID |
				IEEE1394_MATCH_MODEL_ID |
				IEEE1394_MATCH_SPECIFIER_ID |
				IEEE1394_MATCH_VERSION,
		.venकरोr_id    = VENDOR_GRIFFIN,
		.model_id     = 0x00f970,
		.specअगरier_id = SPECIFIER_1394TA,
		.version      = VERSION_AVC,
		.driver_data  = (kernel_uदीर्घ_t)&grअगरfin_firewave,
	पूर्ण,
	अणु
		.match_flags  = IEEE1394_MATCH_VENDOR_ID |
				IEEE1394_MATCH_MODEL_ID |
				IEEE1394_MATCH_SPECIFIER_ID |
				IEEE1394_MATCH_VERSION,
		.venकरोr_id    = VENDOR_LACIE,
		.model_id     = 0x00f970,
		.specअगरier_id = SPECIFIER_1394TA,
		.version      = VERSION_AVC,
		.driver_data  = (kernel_uदीर्घ_t)&lacie_speakers,
	पूर्ण,
	/* Behringer,F-Control Audio 202 */
	अणु
		.match_flags	= IEEE1394_MATCH_VENDOR_ID |
				  IEEE1394_MATCH_MODEL_ID,
		.venकरोr_id	= VENDOR_BEHRINGER,
		.model_id	= 0x00fc22,
	पूर्ण,
	/*
	 * Any Mackie(Loud) models (name string/model id):
	 *  Onyx-i series (क्रमmer models):	0x081216
	 *  Mackie Onyx Satellite:		0x00200f
	 *  Tapco LINK.firewire 4x6:		0x000460
	 *  d.4 pro:				Unknown
	 *  U.420:				Unknown
	 *  U.420d:				Unknown
	 */
	अणु
		.match_flags	= IEEE1394_MATCH_VENDOR_ID |
				  IEEE1394_MATCH_SPECIFIER_ID |
				  IEEE1394_MATCH_VERSION,
		.venकरोr_id	= VENDOR_LOUD,
		.specअगरier_id	= SPECIFIER_1394TA,
		.version	= VERSION_AVC,
	पूर्ण,
	/* TASCAM, FireOne */
	अणु
		.match_flags	= IEEE1394_MATCH_VENDOR_ID |
				  IEEE1394_MATCH_MODEL_ID,
		.venकरोr_id	= VENDOR_TASCAM,
		.model_id	= 0x800007,
	पूर्ण,
	/* Stanton, Stanton Controllers & Systems 1 Mixer (SCS.1m) */
	अणु
		.match_flags	= IEEE1394_MATCH_VENDOR_ID |
				  IEEE1394_MATCH_MODEL_ID,
		.venकरोr_id	= OUI_STANTON,
		.model_id	= 0x001000,
	पूर्ण,
	/* Stanton, Stanton Controllers & Systems 1 Deck (SCS.1d) */
	अणु
		.match_flags	= IEEE1394_MATCH_VENDOR_ID |
				  IEEE1394_MATCH_MODEL_ID,
		.venकरोr_id	= OUI_STANTON,
		.model_id	= 0x002000,
	पूर्ण,
	// APOGEE, duet FireWire
	अणु
		.match_flags	= IEEE1394_MATCH_VENDOR_ID |
				  IEEE1394_MATCH_MODEL_ID,
		.venकरोr_id	= OUI_APOGEE,
		.model_id	= 0x01dddd,
	पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(ieee1394, oxfw_id_table);

अटल काष्ठा fw_driver oxfw_driver = अणु
	.driver   = अणु
		.owner	= THIS_MODULE,
		.name	= KBUILD_MODNAME,
		.bus	= &fw_bus_type,
	पूर्ण,
	.probe    = oxfw_probe,
	.update   = oxfw_bus_reset,
	.हटाओ   = oxfw_हटाओ,
	.id_table = oxfw_id_table,
पूर्ण;

अटल पूर्णांक __init snd_oxfw_init(व्योम)
अणु
	वापस driver_रेजिस्टर(&oxfw_driver.driver);
पूर्ण

अटल व्योम __निकास snd_oxfw_निकास(व्योम)
अणु
	driver_unरेजिस्टर(&oxfw_driver.driver);
पूर्ण

module_init(snd_oxfw_init);
module_निकास(snd_oxfw_निकास);
