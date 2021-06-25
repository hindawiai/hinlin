<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * ff.c - a part of driver क्रम RME Fireface series
 *
 * Copyright (c) 2015-2017 Takashi Sakamoto
 */

#समावेश "ff.h"

#घोषणा OUI_RME	0x000a35

MODULE_DESCRIPTION("RME Fireface series Driver");
MODULE_AUTHOR("Takashi Sakamoto <o-takashi@sakamocchi.jp>");
MODULE_LICENSE("GPL v2");

अटल व्योम name_card(काष्ठा snd_ff *ff)
अणु
	काष्ठा fw_device *fw_dev = fw_parent_device(ff->unit);
	स्थिर अक्षर *स्थिर names[] = अणु
		[SND_FF_UNIT_VERSION_FF800]	= "Fireface800",
		[SND_FF_UNIT_VERSION_FF400]	= "Fireface400",
		[SND_FF_UNIT_VERSION_UFX]	= "FirefaceUFX",
		[SND_FF_UNIT_VERSION_UCX]	= "FirefaceUCX",
		[SND_FF_UNIT_VERSION_802]	= "Fireface802",
	पूर्ण;
	स्थिर अक्षर *name;

	name = names[ff->unit_version];

	म_नकल(ff->card->driver, "Fireface");
	म_नकल(ff->card->लघुname, name);
	म_नकल(ff->card->mixername, name);
	snम_लिखो(ff->card->दीर्घname, माप(ff->card->दीर्घname),
		 "RME %s, GUID %08x%08x at %s, S%d", name,
		 fw_dev->config_rom[3], fw_dev->config_rom[4],
		 dev_name(&ff->unit->device), 100 << fw_dev->max_speed);
पूर्ण

अटल व्योम ff_card_मुक्त(काष्ठा snd_card *card)
अणु
	काष्ठा snd_ff *ff = card->निजी_data;

	snd_ff_stream_destroy_duplex(ff);
	snd_ff_transaction_unरेजिस्टर(ff);
पूर्ण

अटल व्योम करो_registration(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा snd_ff *ff = container_of(work, काष्ठा snd_ff, dwork.work);
	पूर्णांक err;

	अगर (ff->रेजिस्टरed)
		वापस;

	err = snd_card_new(&ff->unit->device, -1, शून्य, THIS_MODULE, 0,
			   &ff->card);
	अगर (err < 0)
		वापस;
	ff->card->निजी_मुक्त = ff_card_मुक्त;
	ff->card->निजी_data = ff;

	err = snd_ff_transaction_रेजिस्टर(ff);
	अगर (err < 0)
		जाओ error;

	name_card(ff);

	err = snd_ff_stream_init_duplex(ff);
	अगर (err < 0)
		जाओ error;

	snd_ff_proc_init(ff);

	err = snd_ff_create_midi_devices(ff);
	अगर (err < 0)
		जाओ error;

	err = snd_ff_create_pcm_devices(ff);
	अगर (err < 0)
		जाओ error;

	err = snd_ff_create_hwdep_devices(ff);
	अगर (err < 0)
		जाओ error;

	err = snd_card_रेजिस्टर(ff->card);
	अगर (err < 0)
		जाओ error;

	ff->रेजिस्टरed = true;

	वापस;
error:
	snd_card_मुक्त(ff->card);
	dev_info(&ff->unit->device,
		 "Sound card registration failed: %d\n", err);
पूर्ण

अटल पूर्णांक snd_ff_probe(काष्ठा fw_unit *unit,
			   स्थिर काष्ठा ieee1394_device_id *entry)
अणु
	काष्ठा snd_ff *ff;

	ff = devm_kzalloc(&unit->device, माप(काष्ठा snd_ff), GFP_KERNEL);
	अगर (!ff)
		वापस -ENOMEM;
	ff->unit = fw_unit_get(unit);
	dev_set_drvdata(&unit->device, ff);

	mutex_init(&ff->mutex);
	spin_lock_init(&ff->lock);
	init_रुकोqueue_head(&ff->hwdep_रुको);

	ff->unit_version = entry->version;
	ff->spec = (स्थिर काष्ठा snd_ff_spec *)entry->driver_data;

	/* Register this sound card later. */
	INIT_DEFERRABLE_WORK(&ff->dwork, करो_registration);
	snd_fw_schedule_registration(unit, &ff->dwork);

	वापस 0;
पूर्ण

अटल व्योम snd_ff_update(काष्ठा fw_unit *unit)
अणु
	काष्ठा snd_ff *ff = dev_get_drvdata(&unit->device);

	/* Postpone a workqueue क्रम deferred registration. */
	अगर (!ff->रेजिस्टरed)
		snd_fw_schedule_registration(unit, &ff->dwork);

	snd_ff_transaction_reरेजिस्टर(ff);

	अगर (ff->रेजिस्टरed)
		snd_ff_stream_update_duplex(ff);
पूर्ण

अटल व्योम snd_ff_हटाओ(काष्ठा fw_unit *unit)
अणु
	काष्ठा snd_ff *ff = dev_get_drvdata(&unit->device);

	/*
	 * Confirm to stop the work क्रम registration beक्रमe the sound card is
	 * going to be released. The work is not scheduled again because bus
	 * reset handler is not called anymore.
	 */
	cancel_work_sync(&ff->dwork.work);

	अगर (ff->रेजिस्टरed) अणु
		// Block till all of ALSA अक्षरacter devices are released.
		snd_card_मुक्त(ff->card);
	पूर्ण

	mutex_destroy(&ff->mutex);
	fw_unit_put(ff->unit);
पूर्ण

अटल स्थिर काष्ठा snd_ff_spec spec_ff800 = अणु
	.pcm_capture_channels = अणु28, 20, 12पूर्ण,
	.pcm_playback_channels = अणु28, 20, 12पूर्ण,
	.midi_in_ports = 1,
	.midi_out_ports = 1,
	.protocol = &snd_ff_protocol_ff800,
	.midi_high_addr = 0x000200000320ull,
	.midi_addr_range = 12,
	.midi_rx_addrs = अणु0x000080180000ull, 0पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा snd_ff_spec spec_ff400 = अणु
	.pcm_capture_channels = अणु18, 14, 10पूर्ण,
	.pcm_playback_channels = अणु18, 14, 10पूर्ण,
	.midi_in_ports = 2,
	.midi_out_ports = 2,
	.protocol = &snd_ff_protocol_ff400,
	.midi_high_addr = 0x0000801003f4ull,
	.midi_addr_range = SND_FF_MAXIMIM_MIDI_QUADS * 4,
	.midi_rx_addrs = अणु0x000080180000ull, 0x000080190000ullपूर्ण,
पूर्ण;

अटल स्थिर काष्ठा snd_ff_spec spec_ucx = अणु
	.pcm_capture_channels = अणु18, 14, 12पूर्ण,
	.pcm_playback_channels = अणु18, 14, 12पूर्ण,
	.midi_in_ports = 2,
	.midi_out_ports = 2,
	.protocol = &snd_ff_protocol_latter,
	.midi_high_addr = 0xffff00000034ull,
	.midi_addr_range = 0x80,
	.midi_rx_addrs = अणु0xffff00000030ull, 0xffff00000030ullपूर्ण,
पूर्ण;

अटल स्थिर काष्ठा snd_ff_spec spec_ufx_802 = अणु
	.pcm_capture_channels = अणु30, 22, 14पूर्ण,
	.pcm_playback_channels = अणु30, 22, 14पूर्ण,
	.midi_in_ports = 1,
	.midi_out_ports = 1,
	.protocol = &snd_ff_protocol_latter,
	.midi_high_addr = 0xffff00000034ull,
	.midi_addr_range = 0x80,
	.midi_rx_addrs = अणु0xffff00000030ull, 0xffff00000030ullपूर्ण,
पूर्ण;

अटल स्थिर काष्ठा ieee1394_device_id snd_ff_id_table[] = अणु
	/* Fireface 800 */
	अणु
		.match_flags	= IEEE1394_MATCH_VENDOR_ID |
				  IEEE1394_MATCH_SPECIFIER_ID |
				  IEEE1394_MATCH_VERSION |
				  IEEE1394_MATCH_MODEL_ID,
		.venकरोr_id	= OUI_RME,
		.specअगरier_id	= OUI_RME,
		.version	= SND_FF_UNIT_VERSION_FF800,
		.model_id	= 0x101800,
		.driver_data	= (kernel_uदीर्घ_t)&spec_ff800,
	पूर्ण,
	/* Fireface 400 */
	अणु
		.match_flags	= IEEE1394_MATCH_VENDOR_ID |
				  IEEE1394_MATCH_SPECIFIER_ID |
				  IEEE1394_MATCH_VERSION |
				  IEEE1394_MATCH_MODEL_ID,
		.venकरोr_id	= OUI_RME,
		.specअगरier_id	= OUI_RME,
		.version	= SND_FF_UNIT_VERSION_FF400,
		.model_id	= 0x101800,
		.driver_data	= (kernel_uदीर्घ_t)&spec_ff400,
	पूर्ण,
	// Fireface UFX.
	अणु
		.match_flags	= IEEE1394_MATCH_VENDOR_ID |
				  IEEE1394_MATCH_SPECIFIER_ID |
				  IEEE1394_MATCH_VERSION |
				  IEEE1394_MATCH_MODEL_ID,
		.venकरोr_id	= OUI_RME,
		.specअगरier_id	= OUI_RME,
		.version	= SND_FF_UNIT_VERSION_UFX,
		.model_id	= 0x101800,
		.driver_data	= (kernel_uदीर्घ_t)&spec_ufx_802,
	पूर्ण,
	// Fireface UCX.
	अणु
		.match_flags	= IEEE1394_MATCH_VENDOR_ID |
				  IEEE1394_MATCH_SPECIFIER_ID |
				  IEEE1394_MATCH_VERSION |
				  IEEE1394_MATCH_MODEL_ID,
		.venकरोr_id	= OUI_RME,
		.specअगरier_id	= OUI_RME,
		.version	= SND_FF_UNIT_VERSION_UCX,
		.model_id	= 0x101800,
		.driver_data	= (kernel_uदीर्घ_t)&spec_ucx,
	पूर्ण,
	// Fireface 802.
	अणु
		.match_flags	= IEEE1394_MATCH_VENDOR_ID |
				  IEEE1394_MATCH_SPECIFIER_ID |
				  IEEE1394_MATCH_VERSION |
				  IEEE1394_MATCH_MODEL_ID,
		.venकरोr_id	= OUI_RME,
		.specअगरier_id	= OUI_RME,
		.version	= SND_FF_UNIT_VERSION_802,
		.model_id	= 0x101800,
		.driver_data	= (kernel_uदीर्घ_t)&spec_ufx_802,
	पूर्ण,
	अणुपूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(ieee1394, snd_ff_id_table);

अटल काष्ठा fw_driver ff_driver = अणु
	.driver = अणु
		.owner	= THIS_MODULE,
		.name	= KBUILD_MODNAME,
		.bus	= &fw_bus_type,
	पूर्ण,
	.probe    = snd_ff_probe,
	.update   = snd_ff_update,
	.हटाओ   = snd_ff_हटाओ,
	.id_table = snd_ff_id_table,
पूर्ण;

अटल पूर्णांक __init snd_ff_init(व्योम)
अणु
	वापस driver_रेजिस्टर(&ff_driver.driver);
पूर्ण

अटल व्योम __निकास snd_ff_निकास(व्योम)
अणु
	driver_unरेजिस्टर(&ff_driver.driver);
पूर्ण

module_init(snd_ff_init);
module_निकास(snd_ff_निकास);
