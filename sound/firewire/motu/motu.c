<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * motu.c - a part of driver क्रम MOTU FireWire series
 *
 * Copyright (c) 2015-2017 Takashi Sakamoto <o-takashi@sakamocchi.jp>
 */

#समावेश "motu.h"

#घोषणा OUI_MOTU	0x0001f2

MODULE_DESCRIPTION("MOTU FireWire driver");
MODULE_AUTHOR("Takashi Sakamoto <o-takashi@sakamocchi.jp>");
MODULE_LICENSE("GPL v2");

स्थिर अचिन्हित पूर्णांक snd_motu_घड़ी_rates[SND_MOTU_CLOCK_RATE_COUNT] = अणु
	/* mode 0 */
	[0] =  44100,
	[1] =  48000,
	/* mode 1 */
	[2] =  88200,
	[3] =  96000,
	/* mode 2 */
	[4] = 176400,
	[5] = 192000,
पूर्ण;

अटल व्योम name_card(काष्ठा snd_motu *motu)
अणु
	काष्ठा fw_device *fw_dev = fw_parent_device(motu->unit);
	काष्ठा fw_csr_iterator it;
	पूर्णांक key, val;
	u32 version = 0;

	fw_csr_iterator_init(&it, motu->unit->directory);
	जबतक (fw_csr_iterator_next(&it, &key, &val)) अणु
		चयन (key) अणु
		हाल CSR_MODEL:
			version = val;
			अवरोध;
		पूर्ण
	पूर्ण

	म_नकल(motu->card->driver, "FW-MOTU");
	म_नकल(motu->card->लघुname, motu->spec->name);
	म_नकल(motu->card->mixername, motu->spec->name);
	snम_लिखो(motu->card->दीर्घname, माप(motu->card->दीर्घname),
		 "MOTU %s (version:%06x), GUID %08x%08x at %s, S%d",
		 motu->spec->name, version,
		 fw_dev->config_rom[3], fw_dev->config_rom[4],
		 dev_name(&motu->unit->device), 100 << fw_dev->max_speed);
पूर्ण

अटल व्योम motu_card_मुक्त(काष्ठा snd_card *card)
अणु
	काष्ठा snd_motu *motu = card->निजी_data;

	snd_motu_transaction_unरेजिस्टर(motu);
	snd_motu_stream_destroy_duplex(motu);
पूर्ण

अटल व्योम करो_registration(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा snd_motu *motu = container_of(work, काष्ठा snd_motu, dwork.work);
	पूर्णांक err;

	अगर (motu->रेजिस्टरed)
		वापस;

	err = snd_card_new(&motu->unit->device, -1, शून्य, THIS_MODULE, 0,
			   &motu->card);
	अगर (err < 0)
		वापस;
	motu->card->निजी_मुक्त = motu_card_मुक्त;
	motu->card->निजी_data = motu;

	name_card(motu);

	err = snd_motu_transaction_रेजिस्टर(motu);
	अगर (err < 0)
		जाओ error;

	err = snd_motu_stream_init_duplex(motu);
	अगर (err < 0)
		जाओ error;

	snd_motu_proc_init(motu);

	err = snd_motu_create_pcm_devices(motu);
	अगर (err < 0)
		जाओ error;

	अगर ((motu->spec->flags & SND_MOTU_SPEC_RX_MIDI_2ND_Q) ||
	    (motu->spec->flags & SND_MOTU_SPEC_RX_MIDI_3RD_Q) ||
	    (motu->spec->flags & SND_MOTU_SPEC_TX_MIDI_2ND_Q) ||
	    (motu->spec->flags & SND_MOTU_SPEC_TX_MIDI_3RD_Q)) अणु
		err = snd_motu_create_midi_devices(motu);
		अगर (err < 0)
			जाओ error;
	पूर्ण

	err = snd_motu_create_hwdep_device(motu);
	अगर (err < 0)
		जाओ error;

	err = snd_card_रेजिस्टर(motu->card);
	अगर (err < 0)
		जाओ error;

	motu->रेजिस्टरed = true;

	वापस;
error:
	snd_card_मुक्त(motu->card);
	dev_info(&motu->unit->device,
		 "Sound card registration failed: %d\n", err);
पूर्ण

अटल पूर्णांक motu_probe(काष्ठा fw_unit *unit,
		      स्थिर काष्ठा ieee1394_device_id *entry)
अणु
	काष्ठा snd_motu *motu;

	/* Allocate this independently of sound card instance. */
	motu = devm_kzalloc(&unit->device, माप(काष्ठा snd_motu), GFP_KERNEL);
	अगर (!motu)
		वापस -ENOMEM;
	motu->unit = fw_unit_get(unit);
	dev_set_drvdata(&unit->device, motu);

	motu->spec = (स्थिर काष्ठा snd_motu_spec *)entry->driver_data;
	mutex_init(&motu->mutex);
	spin_lock_init(&motu->lock);
	init_रुकोqueue_head(&motu->hwdep_रुको);

	/* Allocate and रेजिस्टर this sound card later. */
	INIT_DEFERRABLE_WORK(&motu->dwork, करो_registration);
	snd_fw_schedule_registration(unit, &motu->dwork);

	वापस 0;
पूर्ण

अटल व्योम motu_हटाओ(काष्ठा fw_unit *unit)
अणु
	काष्ठा snd_motu *motu = dev_get_drvdata(&unit->device);

	/*
	 * Confirm to stop the work क्रम registration beक्रमe the sound card is
	 * going to be released. The work is not scheduled again because bus
	 * reset handler is not called anymore.
	 */
	cancel_delayed_work_sync(&motu->dwork);

	अगर (motu->रेजिस्टरed) अणु
		// Block till all of ALSA अक्षरacter devices are released.
		snd_card_मुक्त(motu->card);
	पूर्ण

	mutex_destroy(&motu->mutex);
	fw_unit_put(motu->unit);
पूर्ण

अटल व्योम motu_bus_update(काष्ठा fw_unit *unit)
अणु
	काष्ठा snd_motu *motu = dev_get_drvdata(&unit->device);

	/* Postpone a workqueue क्रम deferred registration. */
	अगर (!motu->रेजिस्टरed)
		snd_fw_schedule_registration(unit, &motu->dwork);

	/* The handler address रेजिस्टर becomes initialized. */
	snd_motu_transaction_reरेजिस्टर(motu);
पूर्ण

#घोषणा SND_MOTU_DEV_ENTRY(model, data)			\
अणु							\
	.match_flags	= IEEE1394_MATCH_VENDOR_ID |	\
			  IEEE1394_MATCH_SPECIFIER_ID |	\
			  IEEE1394_MATCH_VERSION,	\
	.venकरोr_id	= OUI_MOTU,			\
	.specअगरier_id	= OUI_MOTU,			\
	.version	= model,			\
	.driver_data	= (kernel_uदीर्घ_t)data,		\
पूर्ण

अटल स्थिर काष्ठा ieee1394_device_id motu_id_table[] = अणु
	SND_MOTU_DEV_ENTRY(0x000003, &snd_motu_spec_828mk2),
	SND_MOTU_DEV_ENTRY(0x000009, &snd_motu_spec_traveler),
	SND_MOTU_DEV_ENTRY(0x00000d, &snd_motu_spec_ultralite),
	SND_MOTU_DEV_ENTRY(0x00000f, &snd_motu_spec_8pre),
	SND_MOTU_DEV_ENTRY(0x000015, &snd_motu_spec_828mk3), // FireWire only.
	SND_MOTU_DEV_ENTRY(0x000019, &snd_motu_spec_ultralite_mk3), // FireWire only.
	SND_MOTU_DEV_ENTRY(0x000035, &snd_motu_spec_828mk3), // Hybrid.
	SND_MOTU_DEV_ENTRY(0x000033, &snd_motu_spec_audio_express),
	SND_MOTU_DEV_ENTRY(0x000045, &snd_motu_spec_4pre),
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(ieee1394, motu_id_table);

अटल काष्ठा fw_driver motu_driver = अणु
	.driver   = अणु
		.owner	= THIS_MODULE,
		.name	= KBUILD_MODNAME,
		.bus	= &fw_bus_type,
	पूर्ण,
	.probe    = motu_probe,
	.update   = motu_bus_update,
	.हटाओ   = motu_हटाओ,
	.id_table = motu_id_table,
पूर्ण;

अटल पूर्णांक __init alsa_motu_init(व्योम)
अणु
	वापस driver_रेजिस्टर(&motu_driver.driver);
पूर्ण

अटल व्योम __निकास alsa_motu_निकास(व्योम)
अणु
	driver_unरेजिस्टर(&motu_driver.driver);
पूर्ण

module_init(alsa_motu_init);
module_निकास(alsa_motu_निकास);
