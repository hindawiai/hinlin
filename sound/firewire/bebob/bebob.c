<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * bebob.c - a part of driver क्रम BeBoB based devices
 *
 * Copyright (c) 2013-2014 Takashi Sakamoto
 */

/*
 * BeBoB is 'BridgeCo enhanced Breakout Box'. This is installed to firewire
 * devices with DM1000/DM1100/DM1500 chipset. It gives common way क्रम host
 * प्रणाली to handle BeBoB based devices.
 */

#समावेश "bebob.h"

MODULE_DESCRIPTION("BridgeCo BeBoB driver");
MODULE_AUTHOR("Takashi Sakamoto <o-takashi@sakamocchi.jp>");
MODULE_LICENSE("GPL v2");

अटल पूर्णांक index[SNDRV_CARDS]	= SNDRV_DEFAULT_IDX;
अटल अक्षर *id[SNDRV_CARDS]	= SNDRV_DEFAULT_STR;
अटल bool enable[SNDRV_CARDS]	= SNDRV_DEFAULT_ENABLE_PNP;

module_param_array(index, पूर्णांक, शून्य, 0444);
MODULE_PARM_DESC(index, "card index");
module_param_array(id, अक्षरp, शून्य, 0444);
MODULE_PARM_DESC(id, "ID string");
module_param_array(enable, bool, शून्य, 0444);
MODULE_PARM_DESC(enable, "enable BeBoB sound card");

अटल DEFINE_MUTEX(devices_mutex);
अटल DECLARE_BITMAP(devices_used, SNDRV_CARDS);

/* Offsets from inक्रमmation रेजिस्टर. */
#घोषणा INFO_OFFSET_BEBOB_VERSION	0x08
#घोषणा INFO_OFFSET_GUID		0x10
#घोषणा INFO_OFFSET_HW_MODEL_ID		0x18
#घोषणा INFO_OFFSET_HW_MODEL_REVISION	0x1c

#घोषणा VEN_EसूचीOL	0x000040ab
#घोषणा VEN_PRESONUS	0x00000a92
#घोषणा VEN_BRIDGECO	0x000007f5
#घोषणा VEN_MACKIE1	0x0000000f
#घोषणा VEN_MACKIE2	0x00000ff2
#घोषणा VEN_STANTON	0x00001260
#घोषणा VEN_TASCAM	0x0000022e
#घोषणा VEN_BEHRINGER	0x00001564
#घोषणा VEN_APOGEE	0x000003db
#घोषणा VEN_ESI		0x00000f1b
#घोषणा VEN_ACOUSTIC	0x00000002
#घोषणा VEN_CME		0x0000000a
#घोषणा VEN_PHONIC	0x00001496
#घोषणा VEN_LYNX	0x000019e5
#घोषणा VEN_ICON	0x00001a9e
#घोषणा VEN_PRISMSOUND	0x00001198
#घोषणा VEN_TERRATEC	0x00000aac
#घोषणा VEN_YAMAHA	0x0000a0de
#घोषणा VEN_FOCUSRITE	0x0000130e
#घोषणा VEN_MAUDIO1	0x00000d6c
#घोषणा VEN_MAUDIO2	0x000007f5
#घोषणा VEN_DIGIDESIGN	0x00a07e

#घोषणा MODEL_FOCUSRITE_SAFFIRE_BOTH	0x00000000
#घोषणा MODEL_MAUDIO_AUDIOPHILE_BOTH	0x00010060
#घोषणा MODEL_MAUDIO_FW1814		0x00010071
#घोषणा MODEL_MAUDIO_PROJECTMIX		0x00010091

अटल पूर्णांक
name_device(काष्ठा snd_bebob *bebob)
अणु
	काष्ठा fw_device *fw_dev = fw_parent_device(bebob->unit);
	अक्षर venकरोr[24] = अणु0पूर्ण;
	अक्षर model[32] = अणु0पूर्ण;
	u32 hw_id;
	u32 data[2] = अणु0पूर्ण;
	u32 revision;
	u32 version;
	पूर्णांक err;

	/* get venकरोr name from root directory */
	err = fw_csr_string(fw_dev->config_rom + 5, CSR_VENDOR,
			    venकरोr, माप(venकरोr));
	अगर (err < 0)
		जाओ end;

	/* get model name from unit directory */
	err = fw_csr_string(bebob->unit->directory, CSR_MODEL,
			    model, माप(model));
	अगर (err < 0)
		जाओ end;

	/* get hardware id */
	err = snd_bebob_पढ़ो_quad(bebob->unit, INFO_OFFSET_HW_MODEL_ID,
				  &hw_id);
	अगर (err < 0)
		जाओ end;

	/* get hardware revision */
	err = snd_bebob_पढ़ो_quad(bebob->unit, INFO_OFFSET_HW_MODEL_REVISION,
				  &revision);
	अगर (err < 0)
		जाओ end;

	/* get GUID */
	err = snd_bebob_पढ़ो_block(bebob->unit, INFO_OFFSET_GUID,
				   data, माप(data));
	अगर (err < 0)
		जाओ end;

	err = snd_bebob_पढ़ो_quad(bebob->unit, INFO_OFFSET_BEBOB_VERSION,
				  &version);
	अगर (err < 0)
		जाओ end;
	bebob->version = version;

	म_नकल(bebob->card->driver, "BeBoB");
	म_नकल(bebob->card->लघुname, model);
	म_नकल(bebob->card->mixername, model);
	snम_लिखो(bebob->card->दीर्घname, माप(bebob->card->दीर्घname),
		 "%s %s (id:%d, rev:%d), GUID %08x%08x at %s, S%d",
		 venकरोr, model, hw_id, revision,
		 data[0], data[1], dev_name(&bebob->unit->device),
		 100 << fw_dev->max_speed);
end:
	वापस err;
पूर्ण

अटल व्योम
bebob_card_मुक्त(काष्ठा snd_card *card)
अणु
	काष्ठा snd_bebob *bebob = card->निजी_data;

	mutex_lock(&devices_mutex);
	clear_bit(bebob->card_index, devices_used);
	mutex_unlock(&devices_mutex);

	snd_bebob_stream_destroy_duplex(bebob);
पूर्ण

अटल स्थिर काष्ठा snd_bebob_spec *
get_saffire_spec(काष्ठा fw_unit *unit)
अणु
	अक्षर name[24] = अणु0पूर्ण;

	अगर (fw_csr_string(unit->directory, CSR_MODEL, name, माप(name)) < 0)
		वापस शून्य;

	अगर (म_भेद(name, "SaffireLE") == 0)
		वापस &saffire_le_spec;
	अन्यथा
		वापस &saffire_spec;
पूर्ण

अटल bool
check_audiophile_booted(काष्ठा fw_unit *unit)
अणु
	अक्षर name[28] = अणु0पूर्ण;

	अगर (fw_csr_string(unit->directory, CSR_MODEL, name, माप(name)) < 0)
		वापस false;

	वापस म_भेदन(name, "FW Audiophile Bootloader", 24) != 0;
पूर्ण

अटल व्योम
करो_registration(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा snd_bebob *bebob =
			container_of(work, काष्ठा snd_bebob, dwork.work);
	अचिन्हित पूर्णांक card_index;
	पूर्णांक err;

	अगर (bebob->रेजिस्टरed)
		वापस;

	mutex_lock(&devices_mutex);
	क्रम (card_index = 0; card_index < SNDRV_CARDS; card_index++) अणु
		अगर (!test_bit(card_index, devices_used) && enable[card_index])
			अवरोध;
	पूर्ण
	अगर (card_index >= SNDRV_CARDS) अणु
		mutex_unlock(&devices_mutex);
		वापस;
	पूर्ण

	err = snd_card_new(&bebob->unit->device, index[card_index],
			   id[card_index], THIS_MODULE, 0, &bebob->card);
	अगर (err < 0) अणु
		mutex_unlock(&devices_mutex);
		वापस;
	पूर्ण
	set_bit(card_index, devices_used);
	mutex_unlock(&devices_mutex);

	bebob->card->निजी_मुक्त = bebob_card_मुक्त;
	bebob->card->निजी_data = bebob;

	err = name_device(bebob);
	अगर (err < 0)
		जाओ error;

	अगर (bebob->spec == &maudio_special_spec) अणु
		अगर (bebob->entry->model_id == MODEL_MAUDIO_FW1814)
			err = snd_bebob_maudio_special_discover(bebob, true);
		अन्यथा
			err = snd_bebob_maudio_special_discover(bebob, false);
	पूर्ण अन्यथा अणु
		err = snd_bebob_stream_discover(bebob);
	पूर्ण
	अगर (err < 0)
		जाओ error;

	err = snd_bebob_stream_init_duplex(bebob);
	अगर (err < 0)
		जाओ error;

	snd_bebob_proc_init(bebob);

	अगर (bebob->midi_input_ports > 0 || bebob->midi_output_ports > 0) अणु
		err = snd_bebob_create_midi_devices(bebob);
		अगर (err < 0)
			जाओ error;
	पूर्ण

	err = snd_bebob_create_pcm_devices(bebob);
	अगर (err < 0)
		जाओ error;

	err = snd_bebob_create_hwdep_device(bebob);
	अगर (err < 0)
		जाओ error;

	err = snd_card_रेजिस्टर(bebob->card);
	अगर (err < 0)
		जाओ error;

	bebob->रेजिस्टरed = true;

	वापस;
error:
	snd_card_मुक्त(bebob->card);
	dev_info(&bebob->unit->device,
		 "Sound card registration failed: %d\n", err);
पूर्ण

अटल पूर्णांक
bebob_probe(काष्ठा fw_unit *unit, स्थिर काष्ठा ieee1394_device_id *entry)
अणु
	काष्ठा snd_bebob *bebob;
	स्थिर काष्ठा snd_bebob_spec *spec;

	अगर (entry->venकरोr_id == VEN_FOCUSRITE &&
	    entry->model_id == MODEL_FOCUSRITE_SAFFIRE_BOTH)
		spec = get_saffire_spec(unit);
	अन्यथा अगर (entry->venकरोr_id == VEN_MAUDIO1 &&
		 entry->model_id == MODEL_MAUDIO_AUDIOPHILE_BOTH &&
		 !check_audiophile_booted(unit))
		spec = शून्य;
	अन्यथा
		spec = (स्थिर काष्ठा snd_bebob_spec *)entry->driver_data;

	अगर (spec == शून्य) अणु
		अगर (entry->venकरोr_id == VEN_MAUDIO1 ||
		    entry->venकरोr_id == VEN_MAUDIO2)
			वापस snd_bebob_maudio_load_firmware(unit);
		अन्यथा
			वापस -ENODEV;
	पूर्ण

	/* Allocate this independent of sound card instance. */
	bebob = devm_kzalloc(&unit->device, माप(काष्ठा snd_bebob),
			     GFP_KERNEL);
	अगर (!bebob)
		वापस -ENOMEM;
	bebob->unit = fw_unit_get(unit);
	dev_set_drvdata(&unit->device, bebob);

	bebob->entry = entry;
	bebob->spec = spec;
	mutex_init(&bebob->mutex);
	spin_lock_init(&bebob->lock);
	init_रुकोqueue_head(&bebob->hwdep_रुको);

	/* Allocate and रेजिस्टर this sound card later. */
	INIT_DEFERRABLE_WORK(&bebob->dwork, करो_registration);

	अगर (entry->venकरोr_id != VEN_MAUDIO1 ||
	    (entry->model_id != MODEL_MAUDIO_FW1814 &&
	     entry->model_id != MODEL_MAUDIO_PROJECTMIX)) अणु
		snd_fw_schedule_registration(unit, &bebob->dwork);
	पूर्ण अन्यथा अणु
		/*
		 * This is a workaround. This bus reset seems to have an effect
		 * to make devices correctly handling transactions. Without
		 * this, the devices have gap_count mismatch. This causes much
		 * failure of transaction.
		 *
		 * Just after registration, user-land application receive
		 * संकेतs from dbus and starts I/Os. To aव्योम I/Os till the
		 * future bus reset, registration is करोne in next update().
		 */
		fw_schedule_bus_reset(fw_parent_device(bebob->unit)->card,
				      false, true);
	पूर्ण

	वापस 0;
पूर्ण

/*
 * This driver करोesn't update streams in bus reset handler.
 *
 * DM1000/ DM1100/DM1500 chipsets with BeBoB firmware transfer packets with
 * disजारीd counter at bus reset. This discontinuity is immediately
 * detected in packet streaming layer, then it sets XRUN to PCM substream.
 *
 * ALSA PCM applications can know the XRUN by getting -EPIPE from PCM operation.
 * Then, they can recover the PCM substream by executing ioctl(2) with
 * SNDRV_PCM_IOCTL_PREPARE. 'struct snd_pcm_ops.prepare' is called and drivers
 * restart packet streaming.
 *
 * The above processing may be executed beक्रमe this bus-reset handler is
 * executed. When this handler updates streams with current isochronous
 * channels, the streams alपढ़ोy have the current ones.
 */
अटल व्योम
bebob_update(काष्ठा fw_unit *unit)
अणु
	काष्ठा snd_bebob *bebob = dev_get_drvdata(&unit->device);

	अगर (bebob == शून्य)
		वापस;

	/* Postpone a workqueue क्रम deferred registration. */
	अगर (!bebob->रेजिस्टरed)
		snd_fw_schedule_registration(unit, &bebob->dwork);
	अन्यथा
		fcp_bus_reset(bebob->unit);
पूर्ण

अटल व्योम bebob_हटाओ(काष्ठा fw_unit *unit)
अणु
	काष्ठा snd_bebob *bebob = dev_get_drvdata(&unit->device);

	अगर (bebob == शून्य)
		वापस;

	/*
	 * Confirm to stop the work क्रम registration beक्रमe the sound card is
	 * going to be released. The work is not scheduled again because bus
	 * reset handler is not called anymore.
	 */
	cancel_delayed_work_sync(&bebob->dwork);

	अगर (bebob->रेजिस्टरed) अणु
		// Block till all of ALSA अक्षरacter devices are released.
		snd_card_मुक्त(bebob->card);
	पूर्ण

	mutex_destroy(&bebob->mutex);
	fw_unit_put(bebob->unit);
पूर्ण

अटल स्थिर काष्ठा snd_bebob_rate_spec normal_rate_spec = अणु
	.get	= &snd_bebob_stream_get_rate,
	.set	= &snd_bebob_stream_set_rate
पूर्ण;
अटल स्थिर काष्ठा snd_bebob_spec spec_normal = अणु
	.घड़ी	= शून्य,
	.rate	= &normal_rate_spec,
	.meter	= शून्य
पूर्ण;

अटल स्थिर काष्ठा ieee1394_device_id bebob_id_table[] = अणु
	/* Edirol, FA-66 */
	SND_BEBOB_DEV_ENTRY(VEN_EसूचीOL, 0x00010049, &spec_normal),
	/* Edirol, FA-101 */
	SND_BEBOB_DEV_ENTRY(VEN_EसूचीOL, 0x00010048, &spec_normal),
	/* Presonus, FIREBOX */
	SND_BEBOB_DEV_ENTRY(VEN_PRESONUS, 0x00010000, &spec_normal),
	/* PreSonus, FIREPOD/FP10 */
	SND_BEBOB_DEV_ENTRY(VEN_PRESONUS, 0x00010066, &spec_normal),
	/* PreSonus, Inspire1394 */
	SND_BEBOB_DEV_ENTRY(VEN_PRESONUS, 0x00010001, &spec_normal),
	/* BridgeCo, RDAudio1 */
	SND_BEBOB_DEV_ENTRY(VEN_BRIDGECO, 0x00010048, &spec_normal),
	/* BridgeCo, Audio5 */
	SND_BEBOB_DEV_ENTRY(VEN_BRIDGECO, 0x00010049, &spec_normal),
	/* Mackie, Onyx 1220/1620/1640 (Firewire I/O Card) */
	SND_BEBOB_DEV_ENTRY(VEN_MACKIE2, 0x00010065, &spec_normal),
	// Mackie, d.2 (Firewire option card) and d.2 Pro (the card is built-in).
	SND_BEBOB_DEV_ENTRY(VEN_MACKIE1, 0x00010067, &spec_normal),
	/* Stanton, ScratchAmp */
	SND_BEBOB_DEV_ENTRY(VEN_STANTON, 0x00000001, &spec_normal),
	/* Tascam, IF-FW DM */
	SND_BEBOB_DEV_ENTRY(VEN_TASCAM, 0x00010067, &spec_normal),
	/* Behringer, XENIX UFX 1204 */
	SND_BEBOB_DEV_ENTRY(VEN_BEHRINGER, 0x00001204, &spec_normal),
	/* Behringer, XENIX UFX 1604 */
	SND_BEBOB_DEV_ENTRY(VEN_BEHRINGER, 0x00001604, &spec_normal),
	/* Behringer, Digital Mixer X32 series (X-UF Card) */
	SND_BEBOB_DEV_ENTRY(VEN_BEHRINGER, 0x00000006, &spec_normal),
	/*  Behringer, F-Control Audio 1616 */
	SND_BEBOB_DEV_ENTRY(VEN_BEHRINGER, 0x001616, &spec_normal),
	/*  Behringer, F-Control Audio 610 */
	SND_BEBOB_DEV_ENTRY(VEN_BEHRINGER, 0x000610, &spec_normal),
	/* Apogee Electronics, Rosetta 200/400 (X-FireWire card) */
	/* Apogee Electronics, DA/AD/DD-16X (X-FireWire card) */
	SND_BEBOB_DEV_ENTRY(VEN_APOGEE, 0x00010048, &spec_normal),
	/* Apogee Electronics, Ensemble */
	SND_BEBOB_DEV_ENTRY(VEN_APOGEE, 0x01eeee, &spec_normal),
	/* ESI, Quatafire610 */
	SND_BEBOB_DEV_ENTRY(VEN_ESI, 0x00010064, &spec_normal),
	/* AcousticReality, eARMasterOne */
	SND_BEBOB_DEV_ENTRY(VEN_ACOUSTIC, 0x00000002, &spec_normal),
	/* CME, MatrixKFW */
	SND_BEBOB_DEV_ENTRY(VEN_CME, 0x00030000, &spec_normal),
	/* Phonic, Helix Board 12 MkII */
	SND_BEBOB_DEV_ENTRY(VEN_PHONIC, 0x00050000, &spec_normal),
	/* Phonic, Helix Board 18 MkII */
	SND_BEBOB_DEV_ENTRY(VEN_PHONIC, 0x00060000, &spec_normal),
	/* Phonic, Helix Board 24 MkII */
	SND_BEBOB_DEV_ENTRY(VEN_PHONIC, 0x00070000, &spec_normal),
	/* Phonic, Helix Board 12 Universal/18 Universal/24 Universal */
	SND_BEBOB_DEV_ENTRY(VEN_PHONIC, 0x00000000, &spec_normal),
	/* Lynx, Aurora 8/16 (LT-FW) */
	SND_BEBOB_DEV_ENTRY(VEN_LYNX, 0x00000001, &spec_normal),
	/* ICON, FireXon */
	SND_BEBOB_DEV_ENTRY(VEN_ICON, 0x00000001, &spec_normal),
	/* PrismSound, Orpheus */
	SND_BEBOB_DEV_ENTRY(VEN_PRISMSOUND, 0x00010048, &spec_normal),
	/* PrismSound, ADA-8XR */
	SND_BEBOB_DEV_ENTRY(VEN_PRISMSOUND, 0x0000ada8, &spec_normal),
	/* TerraTec Electronic GmbH, PHASE 88 Rack FW */
	SND_BEBOB_DEV_ENTRY(VEN_TERRATEC, 0x00000003, &phase88_rack_spec),
	/* TerraTec Electronic GmbH, PHASE 24 FW */
	SND_BEBOB_DEV_ENTRY(VEN_TERRATEC, 0x00000004, &yamaha_terratec_spec),
	/* TerraTec Electronic GmbH, Phase X24 FW */
	SND_BEBOB_DEV_ENTRY(VEN_TERRATEC, 0x00000007, &yamaha_terratec_spec),
	/* TerraTec Electronic GmbH, EWS MIC2/MIC8 */
	SND_BEBOB_DEV_ENTRY(VEN_TERRATEC, 0x00000005, &spec_normal),
	/* Terratec Electronic GmbH, Aureon 7.1 Firewire */
	SND_BEBOB_DEV_ENTRY(VEN_TERRATEC, 0x00000002, &spec_normal),
	/* Yamaha, GO44 */
	SND_BEBOB_DEV_ENTRY(VEN_YAMAHA, 0x0010000b, &yamaha_terratec_spec),
	/* YAMAHA, GO46 */
	SND_BEBOB_DEV_ENTRY(VEN_YAMAHA, 0x0010000c, &yamaha_terratec_spec),
	/* Focusrite, SaffirePro 26 I/O */
	SND_BEBOB_DEV_ENTRY(VEN_FOCUSRITE, 0x00000003, &saffirepro_26_spec),
	/* Focusrite, SaffirePro 10 I/O */
	अणु
		// The combination of venकरोr_id and model_id is the same as the
		// same as the one of Liquid Saffire 56.
		.match_flags	= IEEE1394_MATCH_VENDOR_ID |
				  IEEE1394_MATCH_MODEL_ID |
				  IEEE1394_MATCH_SPECIFIER_ID |
				  IEEE1394_MATCH_VERSION,
		.venकरोr_id	= VEN_FOCUSRITE,
		.model_id	= 0x000006,
		.specअगरier_id	= 0x00a02d,
		.version	= 0x010001,
		.driver_data	= (kernel_uदीर्घ_t)&saffirepro_10_spec,
	पूर्ण,
	/* Focusrite, Saffire(no label and LE) */
	SND_BEBOB_DEV_ENTRY(VEN_FOCUSRITE, MODEL_FOCUSRITE_SAFFIRE_BOTH,
			    &saffire_spec),
	/* M-Audio, Firewire 410 */
	SND_BEBOB_DEV_ENTRY(VEN_MAUDIO2, 0x00010058, शून्य),	/* bootloader */
	SND_BEBOB_DEV_ENTRY(VEN_MAUDIO2, 0x00010046, &maudio_fw410_spec),
	/* M-Audio, Firewire Audiophile */
	SND_BEBOB_DEV_ENTRY(VEN_MAUDIO1, MODEL_MAUDIO_AUDIOPHILE_BOTH,
			    &maudio_audiophile_spec),
	/* M-Audio, Firewire Solo */
	SND_BEBOB_DEV_ENTRY(VEN_MAUDIO1, 0x00010062, &maudio_solo_spec),
	/* M-Audio, Ozonic */
	SND_BEBOB_DEV_ENTRY(VEN_MAUDIO1, 0x0000000a, &maudio_ozonic_spec),
	/* M-Audio NRV10 */
	SND_BEBOB_DEV_ENTRY(VEN_MAUDIO1, 0x00010081, &maudio_nrv10_spec),
	/* M-Audio, ProFireLightbridge */
	SND_BEBOB_DEV_ENTRY(VEN_MAUDIO1, 0x000100a1, &spec_normal),
	/* Firewire 1814 */
	SND_BEBOB_DEV_ENTRY(VEN_MAUDIO1, 0x00010070, शून्य),	/* bootloader */
	SND_BEBOB_DEV_ENTRY(VEN_MAUDIO1, MODEL_MAUDIO_FW1814,
			    &maudio_special_spec),
	/* M-Audio ProjectMix */
	SND_BEBOB_DEV_ENTRY(VEN_MAUDIO1, MODEL_MAUDIO_PROJECTMIX,
			    &maudio_special_spec),
	/* Digidesign Mbox 2 Pro */
	SND_BEBOB_DEV_ENTRY(VEN_DIGIDESIGN, 0x0000a9, &spec_normal),
	/* IDs are unknown but able to be supported */
	/*  Apogee, Mini-ME Firewire */
	/*  Apogee, Mini-DAC Firewire */
	/*  Cakawalk, Sonar Power Studio 66 */
	/*  CME, UF400e */
	/*  ESI, Quotafire XL */
	/*  Infrasonic, DewX */
	/*  Infrasonic, Windy6 */
	/*  Mackie, Digital X Bus x.200 */
	/*  Mackie, Digital X Bus x.400 */
	/*  Phonic, HB 12 */
	/*  Phonic, HB 24 */
	/*  Phonic, HB 18 */
	/*  Phonic, FireFly 202 */
	/*  Phonic, FireFly 302 */
	/*  Rolf Spuler, Firewire Guitar */
	अणुपूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(ieee1394, bebob_id_table);

अटल काष्ठा fw_driver bebob_driver = अणु
	.driver = अणु
		.owner	= THIS_MODULE,
		.name	= KBUILD_MODNAME,
		.bus	= &fw_bus_type,
	पूर्ण,
	.probe    = bebob_probe,
	.update	  = bebob_update,
	.हटाओ   = bebob_हटाओ,
	.id_table = bebob_id_table,
पूर्ण;

अटल पूर्णांक __init
snd_bebob_init(व्योम)
अणु
	वापस driver_रेजिस्टर(&bebob_driver.driver);
पूर्ण

अटल व्योम __निकास
snd_bebob_निकास(व्योम)
अणु
	driver_unरेजिस्टर(&bebob_driver.driver);
पूर्ण

module_init(snd_bebob_init);
module_निकास(snd_bebob_निकास);
