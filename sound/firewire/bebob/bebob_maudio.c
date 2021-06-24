<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * bebob_maudio.c - a part of driver क्रम BeBoB based devices
 *
 * Copyright (c) 2013-2014 Takashi Sakamoto
 */

#समावेश "./bebob.h"
#समावेश <sound/control.h>

/*
 * Just घातering on, Firewire 410/Audiophile/1814 and ProjectMix I/O रुको to
 * करोwnload firmware blob. To enable these devices, drivers should upload
 * firmware blob and send a command to initialize configuration to factory
 * settings when completing uploading. Then these devices generate bus reset
 * and are recognized as new devices with the firmware.
 *
 * But with firmware version 5058 or later, the firmware is stored to flash
 * memory in the device and drivers can tell bootloader to load the firmware
 * by sending a cue. This cue must be sent one समय.
 *
 * For streaming, both of output and input streams are needed क्रम Firewire 410
 * and Ozonic. The single stream is OK क्रम the other devices even अगर the घड़ी
 * source is not SYT-Match (I note no devices use SYT-Match).
 *
 * Without streaming, the devices except क्रम Firewire Audiophile can mix any
 * input and output. For this reason, Audiophile cannot be used as standalone
 * mixer.
 *
 * Firewire 1814 and ProjectMix I/O uses special firmware. It will be मुक्तzed
 * when receiving any commands which the firmware can't understand. These
 * devices utilize completely dअगरferent प्रणाली to control. It is some
 * ग_लिखो-transaction directly पूर्णांकo a certain address. All of addresses क्रम mixer
 * functionality is between 0xffc700700000 to 0xffc70070009c.
 */

/* Offset from inक्रमmation रेजिस्टर */
#घोषणा INFO_OFFSET_SW_DATE	0x20

/* Bootloader Protocol Version 1 */
#घोषणा MAUDIO_BOOTLOADER_CUE1	0x00000001
/*
 * Initializing configuration to factory settings (= 0x1101), (swapped in line),
 * Command code is zero (= 0x00),
 * the number of opeअक्रमs is zero (= 0x00)(at least signअगरicant byte)
 */
#घोषणा MAUDIO_BOOTLOADER_CUE2	0x01110000
/* padding */
#घोषणा MAUDIO_BOOTLOADER_CUE3	0x00000000

#घोषणा MAUDIO_SPECIFIC_ADDRESS	0xffc700000000ULL

#घोषणा METER_OFFSET		0x00600000

/* some device has sync info after metering data */
#घोषणा METER_SIZE_SPECIAL	84	/* with sync info */
#घोषणा METER_SIZE_FW410	76	/* with sync info */
#घोषणा METER_SIZE_AUDIOPHILE	60	/* with sync info */
#घोषणा METER_SIZE_SOLO		52	/* with sync info */
#घोषणा METER_SIZE_OZONIC	48
#घोषणा METER_SIZE_NRV10	80

/* labels क्रम metering */
#घोषणा ANA_IN		"Analog In"
#घोषणा ANA_OUT		"Analog Out"
#घोषणा DIG_IN		"Digital In"
#घोषणा SPDIF_IN	"S/PDIF In"
#घोषणा ADAT_IN		"ADAT In"
#घोषणा DIG_OUT		"Digital Out"
#घोषणा SPDIF_OUT	"S/PDIF Out"
#घोषणा ADAT_OUT	"ADAT Out"
#घोषणा STRM_IN		"Stream In"
#घोषणा AUX_OUT		"Aux Out"
#घोषणा HP_OUT		"HP Out"
/* क्रम NRV */
#घोषणा UNKNOWN_METER	"Unknown"

काष्ठा special_params अणु
	bool is1814;
	अचिन्हित पूर्णांक clk_src;
	अचिन्हित पूर्णांक dig_in_fmt;
	अचिन्हित पूर्णांक dig_out_fmt;
	अचिन्हित पूर्णांक clk_lock;
	काष्ठा snd_ctl_elem_id *ctl_id_sync;
पूर्ण;

/*
 * For some M-Audio devices, this module just send cue to load firmware. After
 * loading, the device generates bus reset and newly detected.
 *
 * If we make any transactions to load firmware, the operation may failed.
 */
पूर्णांक snd_bebob_maudio_load_firmware(काष्ठा fw_unit *unit)
अणु
	काष्ठा fw_device *device = fw_parent_device(unit);
	पूर्णांक err, rcode;
	u64 date;
	__le32 *cues;

	/* check date of software used to build */
	err = snd_bebob_पढ़ो_block(unit, INFO_OFFSET_SW_DATE,
				   &date, माप(u64));
	अगर (err < 0)
		वापस err;
	/*
	 * firmware version 5058 or later has date later than "20070401", but
	 * 'date' is not null-terminated.
	 */
	अगर (date < 0x3230303730343031LL) अणु
		dev_err(&unit->device,
			"Use firmware version 5058 or later\n");
		वापस -ENXIO;
	पूर्ण

	cues = kदो_स्मृति_array(3, माप(*cues), GFP_KERNEL);
	अगर (!cues)
		वापस -ENOMEM;

	cues[0] = cpu_to_le32(MAUDIO_BOOTLOADER_CUE1);
	cues[1] = cpu_to_le32(MAUDIO_BOOTLOADER_CUE2);
	cues[2] = cpu_to_le32(MAUDIO_BOOTLOADER_CUE3);

	rcode = fw_run_transaction(device->card, TCODE_WRITE_BLOCK_REQUEST,
				   device->node_id, device->generation,
				   device->max_speed, BEBOB_ADDR_REG_REQ,
				   cues, 3 * माप(*cues));
	kमुक्त(cues);
	अगर (rcode != RCODE_COMPLETE) अणु
		dev_err(&unit->device,
			"Failed to send a cue to load firmware\n");
		err = -EIO;
	पूर्ण

	वापस err;
पूर्ण

अटल अंतरभूत पूर्णांक
get_meter(काष्ठा snd_bebob *bebob, व्योम *buf, अचिन्हित पूर्णांक size)
अणु
	वापस snd_fw_transaction(bebob->unit, TCODE_READ_BLOCK_REQUEST,
				  MAUDIO_SPECIFIC_ADDRESS + METER_OFFSET,
				  buf, size, 0);
पूर्ण

अटल पूर्णांक
check_clk_sync(काष्ठा snd_bebob *bebob, अचिन्हित पूर्णांक size, bool *sync)
अणु
	पूर्णांक err;
	u8 *buf;

	buf = kदो_स्मृति(size, GFP_KERNEL);
	अगर (buf == शून्य)
		वापस -ENOMEM;

	err = get_meter(bebob, buf, size);
	अगर (err < 0)
		जाओ end;

	/* अगर synced, this value is the same as SFC of FDF in CIP header */
	*sync = (buf[size - 2] != 0xff);
end:
	kमुक्त(buf);
	वापस err;
पूर्ण

/*
 * dig_fmt: 0x00:S/PDIF, 0x01:ADAT
 * clk_lock: 0x00:unlock, 0x01:lock
 */
अटल पूर्णांक
avc_maudio_set_special_clk(काष्ठा snd_bebob *bebob, अचिन्हित पूर्णांक clk_src,
			   अचिन्हित पूर्णांक dig_in_fmt, अचिन्हित पूर्णांक dig_out_fmt,
			   अचिन्हित पूर्णांक clk_lock)
अणु
	काष्ठा special_params *params = bebob->maudio_special_quirk;
	पूर्णांक err;
	u8 *buf;

	अगर (amdtp_stream_running(&bebob->rx_stream) ||
	    amdtp_stream_running(&bebob->tx_stream))
		वापस -EBUSY;

	buf = kदो_स्मृति(12, GFP_KERNEL);
	अगर (buf == शून्य)
		वापस -ENOMEM;

	buf[0]  = 0x00;		/* CONTROL */
	buf[1]  = 0xff;		/* UNIT */
	buf[2]  = 0x00;		/* venकरोr dependent */
	buf[3]  = 0x04;		/* company ID high */
	buf[4]  = 0x00;		/* company ID middle */
	buf[5]  = 0x04;		/* company ID low */
	buf[6]  = 0xff & clk_src;	/* घड़ी source */
	buf[7]  = 0xff & dig_in_fmt;	/* input digital क्रमmat */
	buf[8]  = 0xff & dig_out_fmt;	/* output digital क्रमmat */
	buf[9]  = 0xff & clk_lock;	/* lock these settings */
	buf[10] = 0x00;		/* padding  */
	buf[11] = 0x00;		/* padding */

	err = fcp_avc_transaction(bebob->unit, buf, 12, buf, 12,
				  BIT(1) | BIT(2) | BIT(3) | BIT(4) |
				  BIT(5) | BIT(6) | BIT(7) | BIT(8) |
				  BIT(9));
	अगर ((err > 0) && (err < 10))
		err = -EIO;
	अन्यथा अगर (buf[0] == 0x08) /* NOT IMPLEMENTED */
		err = -ENOSYS;
	अन्यथा अगर (buf[0] == 0x0a) /* REJECTED */
		err = -EINVAL;
	अगर (err < 0)
		जाओ end;

	params->clk_src		= buf[6];
	params->dig_in_fmt	= buf[7];
	params->dig_out_fmt	= buf[8];
	params->clk_lock	= buf[9];

	अगर (params->ctl_id_sync)
		snd_ctl_notअगरy(bebob->card, SNDRV_CTL_EVENT_MASK_VALUE,
			       params->ctl_id_sync);

	err = 0;
end:
	kमुक्त(buf);
	वापस err;
पूर्ण
अटल व्योम
special_stream_क्रमmation_set(काष्ठा snd_bebob *bebob)
अणु
	अटल स्थिर अचिन्हित पूर्णांक ch_table[2][2][3] = अणु
		/* AMDTP_OUT_STREAM */
		अणु अणु  6,  6,  4 पूर्ण,	/* SPDIF */
		  अणु 12,  8,  4 पूर्ण पूर्ण,	/* ADAT */
		/* AMDTP_IN_STREAM */
		अणु अणु 10, 10,  2 पूर्ण,	/* SPDIF */
		  अणु 16, 12,  2 पूर्ण पूर्ण	/* ADAT */
	पूर्ण;
	काष्ठा special_params *params = bebob->maudio_special_quirk;
	अचिन्हित पूर्णांक i, max;

	max = SND_BEBOB_STRM_FMT_ENTRIES - 1;
	अगर (!params->is1814)
		max -= 2;

	क्रम (i = 0; i < max; i++) अणु
		bebob->tx_stream_क्रमmations[i + 1].pcm =
			ch_table[AMDTP_IN_STREAM][params->dig_in_fmt][i / 2];
		bebob->tx_stream_क्रमmations[i + 1].midi = 1;

		bebob->rx_stream_क्रमmations[i + 1].pcm =
			ch_table[AMDTP_OUT_STREAM][params->dig_out_fmt][i / 2];
		bebob->rx_stream_क्रमmations[i + 1].midi = 1;
	पूर्ण
पूर्ण

अटल पूर्णांक add_special_controls(काष्ठा snd_bebob *bebob);
पूर्णांक
snd_bebob_maudio_special_discover(काष्ठा snd_bebob *bebob, bool is1814)
अणु
	काष्ठा special_params *params;
	पूर्णांक err;

	params = devm_kzalloc(&bebob->card->card_dev,
			      माप(काष्ठा special_params), GFP_KERNEL);
	अगर (!params)
		वापस -ENOMEM;

	mutex_lock(&bebob->mutex);

	bebob->maudio_special_quirk = (व्योम *)params;
	params->is1814 = is1814;

	/* initialize these parameters because driver is not allowed to ask */
	bebob->rx_stream.context = ERR_PTR(-1);
	bebob->tx_stream.context = ERR_PTR(-1);
	err = avc_maudio_set_special_clk(bebob, 0x03, 0x00, 0x00, 0x00);
	अगर (err < 0) अणु
		dev_err(&bebob->unit->device,
			"fail to initialize clock params: %d\n", err);
		जाओ end;
	पूर्ण

	err = add_special_controls(bebob);
	अगर (err < 0)
		जाओ end;

	special_stream_क्रमmation_set(bebob);

	अगर (params->is1814) अणु
		bebob->midi_input_ports = 1;
		bebob->midi_output_ports = 1;
	पूर्ण अन्यथा अणु
		bebob->midi_input_ports = 2;
		bebob->midi_output_ports = 2;
	पूर्ण
end:
	mutex_unlock(&bebob->mutex);
	वापस err;
पूर्ण

/* Input plug shows actual rate. Output plug is needless क्रम this purpose. */
अटल पूर्णांक special_get_rate(काष्ठा snd_bebob *bebob, अचिन्हित पूर्णांक *rate)
अणु
	पूर्णांक err, trials;

	trials = 0;
	करो अणु
		err = avc_general_get_sig_fmt(bebob->unit, rate,
					      AVC_GENERAL_PLUG_सूची_IN, 0);
	पूर्ण जबतक (err == -EAGAIN && ++trials < 3);

	वापस err;
पूर्ण
अटल पूर्णांक special_set_rate(काष्ठा snd_bebob *bebob, अचिन्हित पूर्णांक rate)
अणु
	काष्ठा special_params *params = bebob->maudio_special_quirk;
	पूर्णांक err;

	err = avc_general_set_sig_fmt(bebob->unit, rate,
				      AVC_GENERAL_PLUG_सूची_OUT, 0);
	अगर (err < 0)
		जाओ end;

	/*
	 * Just after changing sampling rate क्रम output, a followed command
	 * क्रम input is easy to fail. This is a workaround fot this issue.
	 */
	msleep(100);

	err = avc_general_set_sig_fmt(bebob->unit, rate,
				      AVC_GENERAL_PLUG_सूची_IN, 0);
	अगर (err < 0)
		जाओ end;

	अगर (params->ctl_id_sync)
		snd_ctl_notअगरy(bebob->card, SNDRV_CTL_EVENT_MASK_VALUE,
			       params->ctl_id_sync);
end:
	वापस err;
पूर्ण

/* Clock source control क्रम special firmware */
अटल स्थिर क्रमागत snd_bebob_घड़ी_प्रकारype special_clk_types[] = अणु
	SND_BEBOB_CLOCK_TYPE_INTERNAL,	/* With digital mute */
	SND_BEBOB_CLOCK_TYPE_EXTERNAL,	/* SPDIF/ADAT */
	SND_BEBOB_CLOCK_TYPE_EXTERNAL,	/* Word Clock */
	SND_BEBOB_CLOCK_TYPE_INTERNAL,
पूर्ण;
अटल पूर्णांक special_clk_get(काष्ठा snd_bebob *bebob, अचिन्हित पूर्णांक *id)
अणु
	काष्ठा special_params *params = bebob->maudio_special_quirk;
	*id = params->clk_src;
	वापस 0;
पूर्ण
अटल पूर्णांक special_clk_ctl_info(काष्ठा snd_kcontrol *kctl,
				काष्ठा snd_ctl_elem_info *einf)
अणु
	अटल स्थिर अक्षर *स्थिर special_clk_labels[] = अणु
		"Internal with Digital Mute",
		"Digital",
		"Word Clock",
		"Internal"
	पूर्ण;
	वापस snd_ctl_क्रमागत_info(einf, 1, ARRAY_SIZE(special_clk_types),
				 special_clk_labels);
पूर्ण
अटल पूर्णांक special_clk_ctl_get(काष्ठा snd_kcontrol *kctl,
			       काष्ठा snd_ctl_elem_value *uval)
अणु
	काष्ठा snd_bebob *bebob = snd_kcontrol_chip(kctl);
	काष्ठा special_params *params = bebob->maudio_special_quirk;
	uval->value.क्रमागतerated.item[0] = params->clk_src;
	वापस 0;
पूर्ण
अटल पूर्णांक special_clk_ctl_put(काष्ठा snd_kcontrol *kctl,
			       काष्ठा snd_ctl_elem_value *uval)
अणु
	काष्ठा snd_bebob *bebob = snd_kcontrol_chip(kctl);
	काष्ठा special_params *params = bebob->maudio_special_quirk;
	पूर्णांक err, id;

	id = uval->value.क्रमागतerated.item[0];
	अगर (id >= ARRAY_SIZE(special_clk_types))
		वापस -EINVAL;

	mutex_lock(&bebob->mutex);

	err = avc_maudio_set_special_clk(bebob, id,
					 params->dig_in_fmt,
					 params->dig_out_fmt,
					 params->clk_lock);
	mutex_unlock(&bebob->mutex);

	अगर (err >= 0)
		err = 1;

	वापस err;
पूर्ण
अटल स्थिर काष्ठा snd_kcontrol_new special_clk_ctl = अणु
	.name	= "Clock Source",
	.अगरace	= SNDRV_CTL_ELEM_IFACE_MIXER,
	.access	= SNDRV_CTL_ELEM_ACCESS_READWRITE,
	.info	= special_clk_ctl_info,
	.get	= special_clk_ctl_get,
	.put	= special_clk_ctl_put
पूर्ण;

/* Clock synchronization control क्रम special firmware */
अटल पूर्णांक special_sync_ctl_info(काष्ठा snd_kcontrol *kctl,
				 काष्ठा snd_ctl_elem_info *einf)
अणु
	einf->type = SNDRV_CTL_ELEM_TYPE_BOOLEAN;
	einf->count = 1;
	einf->value.पूर्णांकeger.min = 0;
	einf->value.पूर्णांकeger.max = 1;

	वापस 0;
पूर्ण
अटल पूर्णांक special_sync_ctl_get(काष्ठा snd_kcontrol *kctl,
				काष्ठा snd_ctl_elem_value *uval)
अणु
	काष्ठा snd_bebob *bebob = snd_kcontrol_chip(kctl);
	पूर्णांक err;
	bool synced = 0;

	err = check_clk_sync(bebob, METER_SIZE_SPECIAL, &synced);
	अगर (err >= 0)
		uval->value.पूर्णांकeger.value[0] = synced;

	वापस 0;
पूर्ण
अटल स्थिर काष्ठा snd_kcontrol_new special_sync_ctl = अणु
	.name	= "Sync Status",
	.अगरace	= SNDRV_CTL_ELEM_IFACE_MIXER,
	.access	= SNDRV_CTL_ELEM_ACCESS_READ,
	.info	= special_sync_ctl_info,
	.get	= special_sync_ctl_get,
पूर्ण;

/* Digital input पूर्णांकerface control क्रम special firmware */
अटल स्थिर अक्षर *स्थिर special_dig_in_अगरace_labels[] = अणु
	"S/PDIF Optical", "S/PDIF Coaxial", "ADAT Optical"
पूर्ण;
अटल पूर्णांक special_dig_in_अगरace_ctl_info(काष्ठा snd_kcontrol *kctl,
					 काष्ठा snd_ctl_elem_info *einf)
अणु
	वापस snd_ctl_क्रमागत_info(einf, 1,
				 ARRAY_SIZE(special_dig_in_अगरace_labels),
				 special_dig_in_अगरace_labels);
पूर्ण
अटल पूर्णांक special_dig_in_अगरace_ctl_get(काष्ठा snd_kcontrol *kctl,
					काष्ठा snd_ctl_elem_value *uval)
अणु
	काष्ठा snd_bebob *bebob = snd_kcontrol_chip(kctl);
	काष्ठा special_params *params = bebob->maudio_special_quirk;
	अचिन्हित पूर्णांक dig_in_अगरace;
	पूर्णांक err, val;

	mutex_lock(&bebob->mutex);

	err = avc_audio_get_selector(bebob->unit, 0x00, 0x04,
				     &dig_in_अगरace);
	अगर (err < 0) अणु
		dev_err(&bebob->unit->device,
			"fail to get digital input interface: %d\n", err);
		जाओ end;
	पूर्ण

	/* encoded id क्रम user value */
	val = (params->dig_in_fmt << 1) | (dig_in_अगरace & 0x01);

	/* क्रम ADAT Optical */
	अगर (val > 2)
		val = 2;

	uval->value.क्रमागतerated.item[0] = val;
end:
	mutex_unlock(&bebob->mutex);
	वापस err;
पूर्ण
अटल पूर्णांक special_dig_in_अगरace_ctl_set(काष्ठा snd_kcontrol *kctl,
					काष्ठा snd_ctl_elem_value *uval)
अणु
	काष्ठा snd_bebob *bebob = snd_kcontrol_chip(kctl);
	काष्ठा special_params *params = bebob->maudio_special_quirk;
	अचिन्हित पूर्णांक id, dig_in_fmt, dig_in_अगरace;
	पूर्णांक err;

	id = uval->value.क्रमागतerated.item[0];
	अगर (id >= ARRAY_SIZE(special_dig_in_अगरace_labels))
		वापस -EINVAL;

	/* decode user value */
	dig_in_fmt = (id >> 1) & 0x01;
	dig_in_अगरace = id & 0x01;

	mutex_lock(&bebob->mutex);

	err = avc_maudio_set_special_clk(bebob,
					 params->clk_src,
					 dig_in_fmt,
					 params->dig_out_fmt,
					 params->clk_lock);
	अगर (err < 0)
		जाओ end;

	/* For ADAT, optical पूर्णांकerface is only available. */
	अगर (params->dig_in_fmt > 0) अणु
		err = 1;
		जाओ end;
	पूर्ण

	/* For S/PDIF, optical/coaxial पूर्णांकerfaces are selectable. */
	err = avc_audio_set_selector(bebob->unit, 0x00, 0x04, dig_in_अगरace);
	अगर (err < 0)
		dev_err(&bebob->unit->device,
			"fail to set digital input interface: %d\n", err);
	err = 1;
end:
	special_stream_क्रमmation_set(bebob);
	mutex_unlock(&bebob->mutex);
	वापस err;
पूर्ण
अटल स्थिर काष्ठा snd_kcontrol_new special_dig_in_अगरace_ctl = अणु
	.name	= "Digital Input Interface",
	.अगरace	= SNDRV_CTL_ELEM_IFACE_MIXER,
	.access	= SNDRV_CTL_ELEM_ACCESS_READWRITE,
	.info	= special_dig_in_अगरace_ctl_info,
	.get	= special_dig_in_अगरace_ctl_get,
	.put	= special_dig_in_अगरace_ctl_set
पूर्ण;

/* Digital output पूर्णांकerface control क्रम special firmware */
अटल स्थिर अक्षर *स्थिर special_dig_out_अगरace_labels[] = अणु
	"S/PDIF Optical and Coaxial", "ADAT Optical"
पूर्ण;
अटल पूर्णांक special_dig_out_अगरace_ctl_info(काष्ठा snd_kcontrol *kctl,
					  काष्ठा snd_ctl_elem_info *einf)
अणु
	वापस snd_ctl_क्रमागत_info(einf, 1,
				 ARRAY_SIZE(special_dig_out_अगरace_labels),
				 special_dig_out_अगरace_labels);
पूर्ण
अटल पूर्णांक special_dig_out_अगरace_ctl_get(काष्ठा snd_kcontrol *kctl,
					 काष्ठा snd_ctl_elem_value *uval)
अणु
	काष्ठा snd_bebob *bebob = snd_kcontrol_chip(kctl);
	काष्ठा special_params *params = bebob->maudio_special_quirk;
	mutex_lock(&bebob->mutex);
	uval->value.क्रमागतerated.item[0] = params->dig_out_fmt;
	mutex_unlock(&bebob->mutex);
	वापस 0;
पूर्ण
अटल पूर्णांक special_dig_out_अगरace_ctl_set(काष्ठा snd_kcontrol *kctl,
					 काष्ठा snd_ctl_elem_value *uval)
अणु
	काष्ठा snd_bebob *bebob = snd_kcontrol_chip(kctl);
	काष्ठा special_params *params = bebob->maudio_special_quirk;
	अचिन्हित पूर्णांक id;
	पूर्णांक err;

	id = uval->value.क्रमागतerated.item[0];
	अगर (id >= ARRAY_SIZE(special_dig_out_अगरace_labels))
		वापस -EINVAL;

	mutex_lock(&bebob->mutex);

	err = avc_maudio_set_special_clk(bebob,
					 params->clk_src,
					 params->dig_in_fmt,
					 id, params->clk_lock);
	अगर (err >= 0) अणु
		special_stream_क्रमmation_set(bebob);
		err = 1;
	पूर्ण

	mutex_unlock(&bebob->mutex);
	वापस err;
पूर्ण
अटल स्थिर काष्ठा snd_kcontrol_new special_dig_out_अगरace_ctl = अणु
	.name	= "Digital Output Interface",
	.अगरace	= SNDRV_CTL_ELEM_IFACE_MIXER,
	.access	= SNDRV_CTL_ELEM_ACCESS_READWRITE,
	.info	= special_dig_out_अगरace_ctl_info,
	.get	= special_dig_out_अगरace_ctl_get,
	.put	= special_dig_out_अगरace_ctl_set
पूर्ण;

अटल पूर्णांक add_special_controls(काष्ठा snd_bebob *bebob)
अणु
	काष्ठा snd_kcontrol *kctl;
	काष्ठा special_params *params = bebob->maudio_special_quirk;
	पूर्णांक err;

	kctl = snd_ctl_new1(&special_clk_ctl, bebob);
	err = snd_ctl_add(bebob->card, kctl);
	अगर (err < 0)
		जाओ end;

	kctl = snd_ctl_new1(&special_sync_ctl, bebob);
	err = snd_ctl_add(bebob->card, kctl);
	अगर (err < 0)
		जाओ end;
	params->ctl_id_sync = &kctl->id;

	kctl = snd_ctl_new1(&special_dig_in_अगरace_ctl, bebob);
	err = snd_ctl_add(bebob->card, kctl);
	अगर (err < 0)
		जाओ end;

	kctl = snd_ctl_new1(&special_dig_out_अगरace_ctl, bebob);
	err = snd_ctl_add(bebob->card, kctl);
end:
	वापस err;
पूर्ण

/* Hardware metering क्रम special firmware */
अटल स्थिर अक्षर *स्थिर special_meter_labels[] = अणु
	ANA_IN, ANA_IN, ANA_IN, ANA_IN,
	SPDIF_IN,
	ADAT_IN, ADAT_IN, ADAT_IN, ADAT_IN,
	ANA_OUT, ANA_OUT,
	SPDIF_OUT,
	ADAT_OUT, ADAT_OUT, ADAT_OUT, ADAT_OUT,
	HP_OUT, HP_OUT,
	AUX_OUT
पूर्ण;
अटल पूर्णांक
special_meter_get(काष्ठा snd_bebob *bebob, u32 *target, अचिन्हित पूर्णांक size)
अणु
	__be16 *buf;
	अचिन्हित पूर्णांक i, c, channels;
	पूर्णांक err;

	channels = ARRAY_SIZE(special_meter_labels) * 2;
	अगर (size < channels * माप(u32))
		वापस -EINVAL;

	/* omit last 4 bytes because it's घड़ी info. */
	buf = kदो_स्मृति(METER_SIZE_SPECIAL - 4, GFP_KERNEL);
	अगर (buf == शून्य)
		वापस -ENOMEM;

	err = get_meter(bebob, (व्योम *)buf, METER_SIZE_SPECIAL - 4);
	अगर (err < 0)
		जाओ end;

	/* Its क्रमmat is u16 and some channels are unknown. */
	i = 0;
	क्रम (c = 2; c < channels + 2; c++)
		target[i++] = be16_to_cpu(buf[c]) << 16;
end:
	kमुक्त(buf);
	वापस err;
पूर्ण

/* last 4 bytes are omitted because it's घड़ी info. */
अटल स्थिर अक्षर *स्थिर fw410_meter_labels[] = अणु
	ANA_IN, DIG_IN,
	ANA_OUT, ANA_OUT, ANA_OUT, ANA_OUT, DIG_OUT,
	HP_OUT
पूर्ण;
अटल स्थिर अक्षर *स्थिर audiophile_meter_labels[] = अणु
	ANA_IN, DIG_IN,
	ANA_OUT, ANA_OUT, DIG_OUT,
	HP_OUT, AUX_OUT,
पूर्ण;
अटल स्थिर अक्षर *स्थिर solo_meter_labels[] = अणु
	ANA_IN, DIG_IN,
	STRM_IN, STRM_IN,
	ANA_OUT, DIG_OUT
पूर्ण;

/* no घड़ी info */
अटल स्थिर अक्षर *स्थिर ozonic_meter_labels[] = अणु
	ANA_IN, ANA_IN,
	STRM_IN, STRM_IN,
	ANA_OUT, ANA_OUT
पूर्ण;
/* TODO: need testers. these positions are based on authour's assumption */
अटल स्थिर अक्षर *स्थिर nrv10_meter_labels[] = अणु
	ANA_IN, ANA_IN, ANA_IN, ANA_IN,
	DIG_IN,
	ANA_OUT, ANA_OUT, ANA_OUT, ANA_OUT,
	DIG_IN
पूर्ण;
अटल पूर्णांक
normal_meter_get(काष्ठा snd_bebob *bebob, u32 *buf, अचिन्हित पूर्णांक size)
अणु
	स्थिर काष्ठा snd_bebob_meter_spec *spec = bebob->spec->meter;
	अचिन्हित पूर्णांक c, channels;
	पूर्णांक err;

	channels = spec->num * 2;
	अगर (size < channels * माप(u32))
		वापस -EINVAL;

	err = get_meter(bebob, (व्योम *)buf, size);
	अगर (err < 0)
		जाओ end;

	क्रम (c = 0; c < channels; c++)
		be32_to_cpus(&buf[c]);

	/* swap stream channels because inverted */
	अगर (spec->labels == solo_meter_labels) अणु
		swap(buf[4], buf[6]);
		swap(buf[5], buf[7]);
	पूर्ण
end:
	वापस err;
पूर्ण

/* क्रम special customized devices */
अटल स्थिर काष्ठा snd_bebob_rate_spec special_rate_spec = अणु
	.get	= &special_get_rate,
	.set	= &special_set_rate,
पूर्ण;
अटल स्थिर काष्ठा snd_bebob_घड़ी_spec special_clk_spec = अणु
	.num	= ARRAY_SIZE(special_clk_types),
	.types	= special_clk_types,
	.get	= &special_clk_get,
पूर्ण;
अटल स्थिर काष्ठा snd_bebob_meter_spec special_meter_spec = अणु
	.num	= ARRAY_SIZE(special_meter_labels),
	.labels	= special_meter_labels,
	.get	= &special_meter_get
पूर्ण;
स्थिर काष्ठा snd_bebob_spec maudio_special_spec = अणु
	.घड़ी	= &special_clk_spec,
	.rate	= &special_rate_spec,
	.meter	= &special_meter_spec
पूर्ण;

/* Firewire 410 specअगरication */
अटल स्थिर काष्ठा snd_bebob_rate_spec usual_rate_spec = अणु
	.get	= &snd_bebob_stream_get_rate,
	.set	= &snd_bebob_stream_set_rate,
पूर्ण;
अटल स्थिर काष्ठा snd_bebob_meter_spec fw410_meter_spec = अणु
	.num	= ARRAY_SIZE(fw410_meter_labels),
	.labels	= fw410_meter_labels,
	.get	= &normal_meter_get
पूर्ण;
स्थिर काष्ठा snd_bebob_spec maudio_fw410_spec = अणु
	.घड़ी	= शून्य,
	.rate	= &usual_rate_spec,
	.meter	= &fw410_meter_spec
पूर्ण;

/* Firewire Audiophile specअगरication */
अटल स्थिर काष्ठा snd_bebob_meter_spec audiophile_meter_spec = अणु
	.num	= ARRAY_SIZE(audiophile_meter_labels),
	.labels	= audiophile_meter_labels,
	.get	= &normal_meter_get
पूर्ण;
स्थिर काष्ठा snd_bebob_spec maudio_audiophile_spec = अणु
	.घड़ी	= शून्य,
	.rate	= &usual_rate_spec,
	.meter	= &audiophile_meter_spec
पूर्ण;

/* Firewire Solo specअगरication */
अटल स्थिर काष्ठा snd_bebob_meter_spec solo_meter_spec = अणु
	.num	= ARRAY_SIZE(solo_meter_labels),
	.labels	= solo_meter_labels,
	.get	= &normal_meter_get
पूर्ण;
स्थिर काष्ठा snd_bebob_spec maudio_solo_spec = अणु
	.घड़ी	= शून्य,
	.rate	= &usual_rate_spec,
	.meter	= &solo_meter_spec
पूर्ण;

/* Ozonic specअगरication */
अटल स्थिर काष्ठा snd_bebob_meter_spec ozonic_meter_spec = अणु
	.num	= ARRAY_SIZE(ozonic_meter_labels),
	.labels	= ozonic_meter_labels,
	.get	= &normal_meter_get
पूर्ण;
स्थिर काष्ठा snd_bebob_spec maudio_ozonic_spec = अणु
	.घड़ी	= शून्य,
	.rate	= &usual_rate_spec,
	.meter	= &ozonic_meter_spec
पूर्ण;

/* NRV10 specअगरication */
अटल स्थिर काष्ठा snd_bebob_meter_spec nrv10_meter_spec = अणु
	.num	= ARRAY_SIZE(nrv10_meter_labels),
	.labels	= nrv10_meter_labels,
	.get	= &normal_meter_get
पूर्ण;
स्थिर काष्ठा snd_bebob_spec maudio_nrv10_spec = अणु
	.घड़ी	= शून्य,
	.rate	= &usual_rate_spec,
	.meter	= &nrv10_meter_spec
पूर्ण;
