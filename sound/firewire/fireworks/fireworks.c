<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * fireworks.c - a part of driver क्रम Fireworks based devices
 *
 * Copyright (c) 2009-2010 Clemens Ladisch
 * Copyright (c) 2013-2014 Takashi Sakamoto
 */

/*
 * Fireworks is a board module which Echo Audio produced. This module consists
 * of three chipsets:
 *  - Communication chipset क्रम IEEE1394 PHY/Link and IEC 61883-1/6
 *  - DSP or/and FPGA क्रम संकेत processing
 *  - Flash Memory to store firmwares
 */

#समावेश "fireworks.h"

MODULE_DESCRIPTION("Echo Fireworks driver");
MODULE_AUTHOR("Takashi Sakamoto <o-takashi@sakamocchi.jp>");
MODULE_LICENSE("GPL v2");

अटल पूर्णांक index[SNDRV_CARDS]	= SNDRV_DEFAULT_IDX;
अटल अक्षर *id[SNDRV_CARDS]	= SNDRV_DEFAULT_STR;
अटल bool enable[SNDRV_CARDS]	= SNDRV_DEFAULT_ENABLE_PNP;
अचिन्हित पूर्णांक snd_efw_resp_buf_size	= 1024;
bool snd_efw_resp_buf_debug		= false;

module_param_array(index, पूर्णांक, शून्य, 0444);
MODULE_PARM_DESC(index, "card index");
module_param_array(id, अक्षरp, शून्य, 0444);
MODULE_PARM_DESC(id, "ID string");
module_param_array(enable, bool, शून्य, 0444);
MODULE_PARM_DESC(enable, "enable Fireworks sound card");
module_param_named(resp_buf_size, snd_efw_resp_buf_size, uपूर्णांक, 0444);
MODULE_PARM_DESC(resp_buf_size,
		 "response buffer size (max 4096, default 1024)");
module_param_named(resp_buf_debug, snd_efw_resp_buf_debug, bool, 0444);
MODULE_PARM_DESC(resp_buf_debug, "store all responses to buffer");

अटल DEFINE_MUTEX(devices_mutex);
अटल DECLARE_BITMAP(devices_used, SNDRV_CARDS);

#घोषणा VENDOR_LOUD			0x000ff2
#घोषणा  MODEL_MACKIE_400F		0x00400f
#घोषणा  MODEL_MACKIE_1200F		0x01200f

#घोषणा VENDOR_ECHO			0x001486
#घोषणा  MODEL_ECHO_AUDIOFIRE_12	0x00af12
#घोषणा  MODEL_ECHO_AUDIOFIRE_12HD	0x0af12d
#घोषणा  MODEL_ECHO_AUDIOFIRE_12_APPLE	0x0af12a
/* This is applied क्रम AudioFire8 (until 2009 July) */
#घोषणा  MODEL_ECHO_AUDIOFIRE_8		0x000af8
#घोषणा  MODEL_ECHO_AUDIOFIRE_2		0x000af2
#घोषणा  MODEL_ECHO_AUDIOFIRE_4		0x000af4
/* AudioFire9 is applied क्रम AudioFire8(since 2009 July) and AudioFirePre8 */
#घोषणा  MODEL_ECHO_AUDIOFIRE_9		0x000af9
/* unknown as product */
#घोषणा  MODEL_ECHO_FIREWORKS_8		0x0000f8
#घोषणा  MODEL_ECHO_FIREWORKS_HDMI	0x00afd1

#घोषणा VENDOR_GIBSON			0x00075b
/* क्रम Robot Interface Pack of Dark Fire, Dusk Tiger, Les Paul Standard 2010 */
#घोषणा  MODEL_GIBSON_RIP		0x00afb2
/* unknown as product */
#घोषणा  MODEL_GIBSON_GOLDTOP		0x00afb9

/* part of hardware capability flags */
#घोषणा FLAG_RESP_ADDR_CHANGABLE	0

अटल पूर्णांक
get_hardware_info(काष्ठा snd_efw *efw)
अणु
	काष्ठा fw_device *fw_dev = fw_parent_device(efw->unit);
	काष्ठा snd_efw_hwinfo *hwinfo;
	अक्षर version[12] = अणु0पूर्ण;
	पूर्णांक err;

	hwinfo = kzalloc(माप(काष्ठा snd_efw_hwinfo), GFP_KERNEL);
	अगर (hwinfo == शून्य)
		वापस -ENOMEM;

	err = snd_efw_command_get_hwinfo(efw, hwinfo);
	अगर (err < 0)
		जाओ end;

	/* firmware version क्रम communication chipset */
	snम_लिखो(version, माप(version), "%u.%u",
		 (hwinfo->arm_version >> 24) & 0xff,
		 (hwinfo->arm_version >> 16) & 0xff);
	efw->firmware_version = hwinfo->arm_version;

	म_नकल(efw->card->driver, "Fireworks");
	म_नकल(efw->card->लघुname, hwinfo->model_name);
	म_नकल(efw->card->mixername, hwinfo->model_name);
	snम_लिखो(efw->card->दीर्घname, माप(efw->card->दीर्घname),
		 "%s %s v%s, GUID %08x%08x at %s, S%d",
		 hwinfo->venकरोr_name, hwinfo->model_name, version,
		 hwinfo->guid_hi, hwinfo->guid_lo,
		 dev_name(&efw->unit->device), 100 << fw_dev->max_speed);

	अगर (hwinfo->flags & BIT(FLAG_RESP_ADDR_CHANGABLE))
		efw->resp_addr_changable = true;

	efw->supported_sampling_rate = 0;
	अगर ((hwinfo->min_sample_rate <= 22050)
	 && (22050 <= hwinfo->max_sample_rate))
		efw->supported_sampling_rate |= SNDRV_PCM_RATE_22050;
	अगर ((hwinfo->min_sample_rate <= 32000)
	 && (32000 <= hwinfo->max_sample_rate))
		efw->supported_sampling_rate |= SNDRV_PCM_RATE_32000;
	अगर ((hwinfo->min_sample_rate <= 44100)
	 && (44100 <= hwinfo->max_sample_rate))
		efw->supported_sampling_rate |= SNDRV_PCM_RATE_44100;
	अगर ((hwinfo->min_sample_rate <= 48000)
	 && (48000 <= hwinfo->max_sample_rate))
		efw->supported_sampling_rate |= SNDRV_PCM_RATE_48000;
	अगर ((hwinfo->min_sample_rate <= 88200)
	 && (88200 <= hwinfo->max_sample_rate))
		efw->supported_sampling_rate |= SNDRV_PCM_RATE_88200;
	अगर ((hwinfo->min_sample_rate <= 96000)
	 && (96000 <= hwinfo->max_sample_rate))
		efw->supported_sampling_rate |= SNDRV_PCM_RATE_96000;
	अगर ((hwinfo->min_sample_rate <= 176400)
	 && (176400 <= hwinfo->max_sample_rate))
		efw->supported_sampling_rate |= SNDRV_PCM_RATE_176400;
	अगर ((hwinfo->min_sample_rate <= 192000)
	 && (192000 <= hwinfo->max_sample_rate))
		efw->supported_sampling_rate |= SNDRV_PCM_RATE_192000;

	/* the number of MIDI ports, not of MIDI conक्रमmant data channels */
	अगर (hwinfo->midi_out_ports > SND_EFW_MAX_MIDI_OUT_PORTS ||
	    hwinfo->midi_in_ports > SND_EFW_MAX_MIDI_IN_PORTS) अणु
		err = -EIO;
		जाओ end;
	पूर्ण
	efw->midi_out_ports = hwinfo->midi_out_ports;
	efw->midi_in_ports = hwinfo->midi_in_ports;

	अगर (hwinfo->amdtp_tx_pcm_channels    > AM824_MAX_CHANNELS_FOR_PCM ||
	    hwinfo->amdtp_tx_pcm_channels_2x > AM824_MAX_CHANNELS_FOR_PCM ||
	    hwinfo->amdtp_tx_pcm_channels_4x > AM824_MAX_CHANNELS_FOR_PCM ||
	    hwinfo->amdtp_rx_pcm_channels    > AM824_MAX_CHANNELS_FOR_PCM ||
	    hwinfo->amdtp_rx_pcm_channels_2x > AM824_MAX_CHANNELS_FOR_PCM ||
	    hwinfo->amdtp_rx_pcm_channels_4x > AM824_MAX_CHANNELS_FOR_PCM) अणु
		err = -ENOSYS;
		जाओ end;
	पूर्ण
	efw->pcm_capture_channels[0] = hwinfo->amdtp_tx_pcm_channels;
	efw->pcm_capture_channels[1] = hwinfo->amdtp_tx_pcm_channels_2x;
	efw->pcm_capture_channels[2] = hwinfo->amdtp_tx_pcm_channels_4x;
	efw->pcm_playback_channels[0] = hwinfo->amdtp_rx_pcm_channels;
	efw->pcm_playback_channels[1] = hwinfo->amdtp_rx_pcm_channels_2x;
	efw->pcm_playback_channels[2] = hwinfo->amdtp_rx_pcm_channels_4x;

	/* Hardware metering. */
	अगर (hwinfo->phys_in_grp_count  > HWINFO_MAX_CAPS_GROUPS ||
	    hwinfo->phys_out_grp_count > HWINFO_MAX_CAPS_GROUPS) अणु
		err = -EIO;
		जाओ end;
	पूर्ण
	efw->phys_in = hwinfo->phys_in;
	efw->phys_out = hwinfo->phys_out;
	efw->phys_in_grp_count = hwinfo->phys_in_grp_count;
	efw->phys_out_grp_count = hwinfo->phys_out_grp_count;
	स_नकल(&efw->phys_in_grps, hwinfo->phys_in_grps,
	       माप(काष्ठा snd_efw_phys_grp) * hwinfo->phys_in_grp_count);
	स_नकल(&efw->phys_out_grps, hwinfo->phys_out_grps,
	       माप(काष्ठा snd_efw_phys_grp) * hwinfo->phys_out_grp_count);

	/* AudioFire8 (since 2009) and AudioFirePre8 */
	अगर (hwinfo->type == MODEL_ECHO_AUDIOFIRE_9)
		efw->is_af9 = true;
	/* These models uses the same firmware. */
	अगर (hwinfo->type == MODEL_ECHO_AUDIOFIRE_2 ||
	    hwinfo->type == MODEL_ECHO_AUDIOFIRE_4 ||
	    hwinfo->type == MODEL_ECHO_AUDIOFIRE_9 ||
	    hwinfo->type == MODEL_GIBSON_RIP ||
	    hwinfo->type == MODEL_GIBSON_GOLDTOP)
		efw->is_fireworks3 = true;
end:
	kमुक्त(hwinfo);
	वापस err;
पूर्ण

अटल व्योम
efw_card_मुक्त(काष्ठा snd_card *card)
अणु
	काष्ठा snd_efw *efw = card->निजी_data;

	mutex_lock(&devices_mutex);
	clear_bit(efw->card_index, devices_used);
	mutex_unlock(&devices_mutex);

	snd_efw_stream_destroy_duplex(efw);
	snd_efw_transaction_हटाओ_instance(efw);
पूर्ण

अटल व्योम
करो_registration(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा snd_efw *efw = container_of(work, काष्ठा snd_efw, dwork.work);
	अचिन्हित पूर्णांक card_index;
	पूर्णांक err;

	अगर (efw->रेजिस्टरed)
		वापस;

	/* check रेजिस्टरed cards */
	mutex_lock(&devices_mutex);
	क्रम (card_index = 0; card_index < SNDRV_CARDS; ++card_index) अणु
		अगर (!test_bit(card_index, devices_used) && enable[card_index])
			अवरोध;
	पूर्ण
	अगर (card_index >= SNDRV_CARDS) अणु
		mutex_unlock(&devices_mutex);
		वापस;
	पूर्ण

	err = snd_card_new(&efw->unit->device, index[card_index],
			   id[card_index], THIS_MODULE, 0, &efw->card);
	अगर (err < 0) अणु
		mutex_unlock(&devices_mutex);
		वापस;
	पूर्ण
	set_bit(card_index, devices_used);
	mutex_unlock(&devices_mutex);

	efw->card->निजी_मुक्त = efw_card_मुक्त;
	efw->card->निजी_data = efw;

	/* prepare response buffer */
	snd_efw_resp_buf_size = clamp(snd_efw_resp_buf_size,
				      SND_EFW_RESPONSE_MAXIMUM_BYTES, 4096U);
	efw->resp_buf = devm_kzalloc(&efw->card->card_dev,
				     snd_efw_resp_buf_size, GFP_KERNEL);
	अगर (!efw->resp_buf) अणु
		err = -ENOMEM;
		जाओ error;
	पूर्ण
	efw->pull_ptr = efw->push_ptr = efw->resp_buf;
	snd_efw_transaction_add_instance(efw);

	err = get_hardware_info(efw);
	अगर (err < 0)
		जाओ error;

	err = snd_efw_stream_init_duplex(efw);
	अगर (err < 0)
		जाओ error;

	snd_efw_proc_init(efw);

	अगर (efw->midi_out_ports || efw->midi_in_ports) अणु
		err = snd_efw_create_midi_devices(efw);
		अगर (err < 0)
			जाओ error;
	पूर्ण

	err = snd_efw_create_pcm_devices(efw);
	अगर (err < 0)
		जाओ error;

	err = snd_efw_create_hwdep_device(efw);
	अगर (err < 0)
		जाओ error;

	err = snd_card_रेजिस्टर(efw->card);
	अगर (err < 0)
		जाओ error;

	efw->रेजिस्टरed = true;

	वापस;
error:
	snd_card_मुक्त(efw->card);
	dev_info(&efw->unit->device,
		 "Sound card registration failed: %d\n", err);
पूर्ण

अटल पूर्णांक
efw_probe(काष्ठा fw_unit *unit, स्थिर काष्ठा ieee1394_device_id *entry)
अणु
	काष्ठा snd_efw *efw;

	efw = devm_kzalloc(&unit->device, माप(काष्ठा snd_efw), GFP_KERNEL);
	अगर (efw == शून्य)
		वापस -ENOMEM;
	efw->unit = fw_unit_get(unit);
	dev_set_drvdata(&unit->device, efw);

	mutex_init(&efw->mutex);
	spin_lock_init(&efw->lock);
	init_रुकोqueue_head(&efw->hwdep_रुको);

	/* Allocate and रेजिस्टर this sound card later. */
	INIT_DEFERRABLE_WORK(&efw->dwork, करो_registration);
	snd_fw_schedule_registration(unit, &efw->dwork);

	वापस 0;
पूर्ण

अटल व्योम efw_update(काष्ठा fw_unit *unit)
अणु
	काष्ठा snd_efw *efw = dev_get_drvdata(&unit->device);

	/* Postpone a workqueue क्रम deferred registration. */
	अगर (!efw->रेजिस्टरed)
		snd_fw_schedule_registration(unit, &efw->dwork);

	snd_efw_transaction_bus_reset(efw->unit);

	/*
	 * After registration, userspace can start packet streaming, then this
	 * code block works fine.
	 */
	अगर (efw->रेजिस्टरed) अणु
		mutex_lock(&efw->mutex);
		snd_efw_stream_update_duplex(efw);
		mutex_unlock(&efw->mutex);
	पूर्ण
पूर्ण

अटल व्योम efw_हटाओ(काष्ठा fw_unit *unit)
अणु
	काष्ठा snd_efw *efw = dev_get_drvdata(&unit->device);

	/*
	 * Confirm to stop the work क्रम registration beक्रमe the sound card is
	 * going to be released. The work is not scheduled again because bus
	 * reset handler is not called anymore.
	 */
	cancel_delayed_work_sync(&efw->dwork);

	अगर (efw->रेजिस्टरed) अणु
		// Block till all of ALSA अक्षरacter devices are released.
		snd_card_मुक्त(efw->card);
	पूर्ण

	mutex_destroy(&efw->mutex);
	fw_unit_put(efw->unit);
पूर्ण

अटल स्थिर काष्ठा ieee1394_device_id efw_id_table[] = अणु
	SND_EFW_DEV_ENTRY(VENDOR_LOUD, MODEL_MACKIE_400F),
	SND_EFW_DEV_ENTRY(VENDOR_LOUD, MODEL_MACKIE_1200F),
	SND_EFW_DEV_ENTRY(VENDOR_ECHO, MODEL_ECHO_AUDIOFIRE_8),
	SND_EFW_DEV_ENTRY(VENDOR_ECHO, MODEL_ECHO_AUDIOFIRE_12),
	SND_EFW_DEV_ENTRY(VENDOR_ECHO, MODEL_ECHO_AUDIOFIRE_12HD),
	SND_EFW_DEV_ENTRY(VENDOR_ECHO, MODEL_ECHO_AUDIOFIRE_12_APPLE),
	SND_EFW_DEV_ENTRY(VENDOR_ECHO, MODEL_ECHO_AUDIOFIRE_2),
	SND_EFW_DEV_ENTRY(VENDOR_ECHO, MODEL_ECHO_AUDIOFIRE_4),
	SND_EFW_DEV_ENTRY(VENDOR_ECHO, MODEL_ECHO_AUDIOFIRE_9),
	SND_EFW_DEV_ENTRY(VENDOR_ECHO, MODEL_ECHO_FIREWORKS_8),
	SND_EFW_DEV_ENTRY(VENDOR_ECHO, MODEL_ECHO_FIREWORKS_HDMI),
	SND_EFW_DEV_ENTRY(VENDOR_GIBSON, MODEL_GIBSON_RIP),
	SND_EFW_DEV_ENTRY(VENDOR_GIBSON, MODEL_GIBSON_GOLDTOP),
	अणुपूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(ieee1394, efw_id_table);

अटल काष्ठा fw_driver efw_driver = अणु
	.driver = अणु
		.owner = THIS_MODULE,
		.name = KBUILD_MODNAME,
		.bus = &fw_bus_type,
	पूर्ण,
	.probe    = efw_probe,
	.update   = efw_update,
	.हटाओ   = efw_हटाओ,
	.id_table = efw_id_table,
पूर्ण;

अटल पूर्णांक __init snd_efw_init(व्योम)
अणु
	पूर्णांक err;

	err = snd_efw_transaction_रेजिस्टर();
	अगर (err < 0)
		जाओ end;

	err = driver_रेजिस्टर(&efw_driver.driver);
	अगर (err < 0)
		snd_efw_transaction_unरेजिस्टर();

end:
	वापस err;
पूर्ण

अटल व्योम __निकास snd_efw_निकास(व्योम)
अणु
	snd_efw_transaction_unरेजिस्टर();
	driver_unरेजिस्टर(&efw_driver.driver);
पूर्ण

module_init(snd_efw_init);
module_निकास(snd_efw_निकास);
