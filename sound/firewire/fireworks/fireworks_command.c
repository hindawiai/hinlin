<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * fireworks_command.c - a part of driver क्रम Fireworks based devices
 *
 * Copyright (c) 2013-2014 Takashi Sakamoto
 */

#समावेश "./fireworks.h"

/*
 * This driver uses transaction version 1 or later to use extended hardware
 * inक्रमmation. Then too old devices are not available.
 *
 * Each commands are not required to have continuous sequence numbers. This
 * number is just used to match command and response.
 *
 * This module support a part of commands. Please see FFADO अगर you want to see
 * whole commands. But there are some commands which FFADO करोn't implement.
 *
 * Fireworks also supports AV/C general commands and AV/C Stream Format
 * Inक्रमmation commands. But this module करोn't use them.
 */

#घोषणा KERNEL_SEQNUM_MIN	(SND_EFW_TRANSACTION_USER_SEQNUM_MAX + 2)
#घोषणा KERNEL_SEQNUM_MAX	((u32)~0)

/* क्रम घड़ी source and sampling rate */
काष्ठा efc_घड़ी अणु
	u32 source;
	u32 sampling_rate;
	u32 index;
पूर्ण;

/* command categories */
क्रमागत efc_category अणु
	EFC_CAT_HWINFO		= 0,
	EFC_CAT_TRANSPORT	= 2,
	EFC_CAT_HWCTL		= 3,
पूर्ण;

/* hardware info category commands */
क्रमागत efc_cmd_hwinfo अणु
	EFC_CMD_HWINFO_GET_CAPS		= 0,
	EFC_CMD_HWINFO_GET_POLLED	= 1,
	EFC_CMD_HWINFO_SET_RESP_ADDR	= 2
पूर्ण;

क्रमागत efc_cmd_transport अणु
	EFC_CMD_TRANSPORT_SET_TX_MODE	= 0
पूर्ण;

/* hardware control category commands */
क्रमागत efc_cmd_hwctl अणु
	EFC_CMD_HWCTL_SET_CLOCK		= 0,
	EFC_CMD_HWCTL_GET_CLOCK		= 1,
	EFC_CMD_HWCTL_IDENTIFY		= 5
पूर्ण;

/* वापस values in response */
क्रमागत efr_status अणु
	EFR_STATUS_OK			= 0,
	EFR_STATUS_BAD			= 1,
	EFR_STATUS_BAD_COMMAND		= 2,
	EFR_STATUS_COMM_ERR		= 3,
	EFR_STATUS_BAD_QUAD_COUNT	= 4,
	EFR_STATUS_UNSUPPORTED		= 5,
	EFR_STATUS_1394_TIMEOUT		= 6,
	EFR_STATUS_DSP_TIMEOUT		= 7,
	EFR_STATUS_BAD_RATE		= 8,
	EFR_STATUS_BAD_CLOCK		= 9,
	EFR_STATUS_BAD_CHANNEL		= 10,
	EFR_STATUS_BAD_PAN		= 11,
	EFR_STATUS_FLASH_BUSY		= 12,
	EFR_STATUS_BAD_MIRROR		= 13,
	EFR_STATUS_BAD_LED		= 14,
	EFR_STATUS_BAD_PARAMETER	= 15,
	EFR_STATUS_INCOMPLETE		= 0x80000000
पूर्ण;

अटल स्थिर अक्षर *स्थिर efr_status_names[] = अणु
	[EFR_STATUS_OK]			= "OK",
	[EFR_STATUS_BAD]		= "bad",
	[EFR_STATUS_BAD_COMMAND]	= "bad command",
	[EFR_STATUS_COMM_ERR]		= "comm err",
	[EFR_STATUS_BAD_QUAD_COUNT]	= "bad quad count",
	[EFR_STATUS_UNSUPPORTED]	= "unsupported",
	[EFR_STATUS_1394_TIMEOUT]	= "1394 timeout",
	[EFR_STATUS_DSP_TIMEOUT]	= "DSP timeout",
	[EFR_STATUS_BAD_RATE]		= "bad rate",
	[EFR_STATUS_BAD_CLOCK]		= "bad clock",
	[EFR_STATUS_BAD_CHANNEL]	= "bad channel",
	[EFR_STATUS_BAD_PAN]		= "bad pan",
	[EFR_STATUS_FLASH_BUSY]		= "flash busy",
	[EFR_STATUS_BAD_MIRROR]		= "bad mirror",
	[EFR_STATUS_BAD_LED]		= "bad LED",
	[EFR_STATUS_BAD_PARAMETER]	= "bad parameter",
	[EFR_STATUS_BAD_PARAMETER + 1]	= "incomplete"
पूर्ण;

अटल पूर्णांक
efw_transaction(काष्ठा snd_efw *efw, अचिन्हित पूर्णांक category,
		अचिन्हित पूर्णांक command,
		स्थिर __be32 *params, अचिन्हित पूर्णांक param_bytes,
		स्थिर __be32 *resp, अचिन्हित पूर्णांक resp_bytes)
अणु
	काष्ठा snd_efw_transaction *header;
	__be32 *buf;
	u32 seqnum;
	अचिन्हित पूर्णांक buf_bytes, cmd_bytes;
	पूर्णांक err;

	/* calculate buffer size*/
	buf_bytes = माप(काष्ठा snd_efw_transaction) +
		    max(param_bytes, resp_bytes);

	/* keep buffer */
	buf = kzalloc(buf_bytes, GFP_KERNEL);
	अगर (buf == शून्य)
		वापस -ENOMEM;

	/* to keep consistency of sequence number */
	spin_lock(&efw->lock);
	अगर ((efw->seqnum < KERNEL_SEQNUM_MIN) ||
	    (efw->seqnum >= KERNEL_SEQNUM_MAX - 2))
		efw->seqnum = KERNEL_SEQNUM_MIN;
	अन्यथा
		efw->seqnum += 2;
	seqnum = efw->seqnum;
	spin_unlock(&efw->lock);

	/* fill transaction header fields */
	cmd_bytes = माप(काष्ठा snd_efw_transaction) + param_bytes;
	header = (काष्ठा snd_efw_transaction *)buf;
	header->length	 = cpu_to_be32(cmd_bytes / माप(__be32));
	header->version	 = cpu_to_be32(1);
	header->seqnum	 = cpu_to_be32(seqnum);
	header->category = cpu_to_be32(category);
	header->command	 = cpu_to_be32(command);
	header->status	 = 0;

	/* fill transaction command parameters */
	स_नकल(header->params, params, param_bytes);

	err = snd_efw_transaction_run(efw->unit, buf, cmd_bytes,
				      buf, buf_bytes);
	अगर (err < 0)
		जाओ end;

	/* check transaction header fields */
	अगर ((be32_to_cpu(header->version) < 1) ||
	    (be32_to_cpu(header->category) != category) ||
	    (be32_to_cpu(header->command) != command) ||
	    (be32_to_cpu(header->status) != EFR_STATUS_OK)) अणु
		dev_err(&efw->unit->device, "EFW command failed [%u/%u]: %s\n",
			be32_to_cpu(header->category),
			be32_to_cpu(header->command),
			efr_status_names[be32_to_cpu(header->status)]);
		err = -EIO;
		जाओ end;
	पूर्ण

	अगर (resp == शून्य)
		जाओ end;

	/* fill transaction response parameters */
	स_रखो((व्योम *)resp, 0, resp_bytes);
	resp_bytes = min_t(अचिन्हित पूर्णांक, resp_bytes,
			   be32_to_cpu(header->length) * माप(__be32) -
				माप(काष्ठा snd_efw_transaction));
	स_नकल((व्योम *)resp, &buf[6], resp_bytes);
end:
	kमुक्त(buf);
	वापस err;
पूर्ण

/*
 * The address in host प्रणाली क्रम transaction response is changable when the
 * device supports. काष्ठा hwinfo.flags includes its flag. The शेष is
 * MEMORY_SPACE_EFW_RESPONSE.
 */
पूर्णांक snd_efw_command_set_resp_addr(काष्ठा snd_efw *efw,
				  u16 addr_high, u32 addr_low)
अणु
	__be32 addr[2];

	addr[0] = cpu_to_be32(addr_high);
	addr[1] = cpu_to_be32(addr_low);

	अगर (!efw->resp_addr_changable)
		वापस -ENOSYS;

	वापस efw_transaction(efw, EFC_CAT_HWCTL,
			       EFC_CMD_HWINFO_SET_RESP_ADDR,
			       addr, माप(addr), शून्य, 0);
पूर्ण

/*
 * This is क्रम बारtamp processing. In Winकरोws mode, all 32bit fields of second
 * CIP header in AMDTP transmit packet is used क्रम 'presentation timestamp'. In
 * 'no data' packet the value of this field is 0x90ffffff.
 */
पूर्णांक snd_efw_command_set_tx_mode(काष्ठा snd_efw *efw,
				क्रमागत snd_efw_transport_mode mode)
अणु
	__be32 param = cpu_to_be32(mode);
	वापस efw_transaction(efw, EFC_CAT_TRANSPORT,
			       EFC_CMD_TRANSPORT_SET_TX_MODE,
			       &param, माप(param), शून्य, 0);
पूर्ण

पूर्णांक snd_efw_command_get_hwinfo(काष्ठा snd_efw *efw,
			       काष्ठा snd_efw_hwinfo *hwinfo)
अणु
	पूर्णांक err;

	err  = efw_transaction(efw, EFC_CAT_HWINFO,
			       EFC_CMD_HWINFO_GET_CAPS,
			       शून्य, 0, (__be32 *)hwinfo, माप(*hwinfo));
	अगर (err < 0)
		जाओ end;

	be32_to_cpus(&hwinfo->flags);
	be32_to_cpus(&hwinfo->guid_hi);
	be32_to_cpus(&hwinfo->guid_lo);
	be32_to_cpus(&hwinfo->type);
	be32_to_cpus(&hwinfo->version);
	be32_to_cpus(&hwinfo->supported_घड़ीs);
	be32_to_cpus(&hwinfo->amdtp_rx_pcm_channels);
	be32_to_cpus(&hwinfo->amdtp_tx_pcm_channels);
	be32_to_cpus(&hwinfo->phys_out);
	be32_to_cpus(&hwinfo->phys_in);
	be32_to_cpus(&hwinfo->phys_out_grp_count);
	be32_to_cpus(&hwinfo->phys_in_grp_count);
	be32_to_cpus(&hwinfo->midi_out_ports);
	be32_to_cpus(&hwinfo->midi_in_ports);
	be32_to_cpus(&hwinfo->max_sample_rate);
	be32_to_cpus(&hwinfo->min_sample_rate);
	be32_to_cpus(&hwinfo->dsp_version);
	be32_to_cpus(&hwinfo->arm_version);
	be32_to_cpus(&hwinfo->mixer_playback_channels);
	be32_to_cpus(&hwinfo->mixer_capture_channels);
	be32_to_cpus(&hwinfo->fpga_version);
	be32_to_cpus(&hwinfo->amdtp_rx_pcm_channels_2x);
	be32_to_cpus(&hwinfo->amdtp_tx_pcm_channels_2x);
	be32_to_cpus(&hwinfo->amdtp_rx_pcm_channels_4x);
	be32_to_cpus(&hwinfo->amdtp_tx_pcm_channels_4x);

	/* ensure terminated */
	hwinfo->venकरोr_name[HWINFO_NAME_SIZE_BYTES - 1] = '\0';
	hwinfo->model_name[HWINFO_NAME_SIZE_BYTES  - 1] = '\0';
end:
	वापस err;
पूर्ण

पूर्णांक snd_efw_command_get_phys_meters(काष्ठा snd_efw *efw,
				    काष्ठा snd_efw_phys_meters *meters,
				    अचिन्हित पूर्णांक len)
अणु
	u32 *buf = (u32 *)meters;
	अचिन्हित पूर्णांक i;
	पूर्णांक err;

	err = efw_transaction(efw, EFC_CAT_HWINFO,
			      EFC_CMD_HWINFO_GET_POLLED,
			      शून्य, 0, (__be32 *)meters, len);
	अगर (err >= 0)
		क्रम (i = 0; i < len / माप(u32); i++)
			be32_to_cpus(&buf[i]);

	वापस err;
पूर्ण

अटल पूर्णांक
command_get_घड़ी(काष्ठा snd_efw *efw, काष्ठा efc_घड़ी *घड़ी)
अणु
	पूर्णांक err;

	err = efw_transaction(efw, EFC_CAT_HWCTL,
			      EFC_CMD_HWCTL_GET_CLOCK,
			      शून्य, 0,
			      (__be32 *)घड़ी, माप(काष्ठा efc_घड़ी));
	अगर (err >= 0) अणु
		be32_to_cpus(&घड़ी->source);
		be32_to_cpus(&घड़ी->sampling_rate);
		be32_to_cpus(&घड़ी->index);
	पूर्ण

	वापस err;
पूर्ण

/* give अच_पूर्णांक_उच्च अगर set nothing */
अटल पूर्णांक
command_set_घड़ी(काष्ठा snd_efw *efw,
		  अचिन्हित पूर्णांक source, अचिन्हित पूर्णांक rate)
अणु
	काष्ठा efc_घड़ी घड़ी = अणु0पूर्ण;
	पूर्णांक err;

	/* check arguments */
	अगर ((source == अच_पूर्णांक_उच्च) && (rate == अच_पूर्णांक_उच्च)) अणु
		err = -EINVAL;
		जाओ end;
	पूर्ण

	/* get current status */
	err = command_get_घड़ी(efw, &घड़ी);
	अगर (err < 0)
		जाओ end;

	/* no need */
	अगर ((घड़ी.source == source) && (घड़ी.sampling_rate == rate))
		जाओ end;

	/* set params */
	अगर ((source != अच_पूर्णांक_उच्च) && (घड़ी.source != source))
		घड़ी.source = source;
	अगर ((rate != अच_पूर्णांक_उच्च) && (घड़ी.sampling_rate != rate))
		घड़ी.sampling_rate = rate;
	घड़ी.index = 0;

	cpu_to_be32s(&घड़ी.source);
	cpu_to_be32s(&घड़ी.sampling_rate);
	cpu_to_be32s(&घड़ी.index);

	err = efw_transaction(efw, EFC_CAT_HWCTL,
			      EFC_CMD_HWCTL_SET_CLOCK,
			      (__be32 *)&घड़ी, माप(काष्ठा efc_घड़ी),
			      शून्य, 0);
	अगर (err < 0)
		जाओ end;

	/*
	 * With firmware version 5.8, just after changing घड़ी state, these
	 * parameters are not immediately retrieved by get command. In my
	 * trial, there needs to be 100msec to get changed parameters.
	 */
	msleep(150);
end:
	वापस err;
पूर्ण

पूर्णांक snd_efw_command_get_घड़ी_source(काष्ठा snd_efw *efw,
				     क्रमागत snd_efw_घड़ी_source *source)
अणु
	पूर्णांक err;
	काष्ठा efc_घड़ी घड़ी = अणु0पूर्ण;

	err = command_get_घड़ी(efw, &घड़ी);
	अगर (err >= 0)
		*source = घड़ी.source;

	वापस err;
पूर्ण

पूर्णांक snd_efw_command_get_sampling_rate(काष्ठा snd_efw *efw, अचिन्हित पूर्णांक *rate)
अणु
	पूर्णांक err;
	काष्ठा efc_घड़ी घड़ी = अणु0पूर्ण;

	err = command_get_घड़ी(efw, &घड़ी);
	अगर (err >= 0)
		*rate = घड़ी.sampling_rate;

	वापस err;
पूर्ण

पूर्णांक snd_efw_command_set_sampling_rate(काष्ठा snd_efw *efw, अचिन्हित पूर्णांक rate)
अणु
	वापस command_set_घड़ी(efw, अच_पूर्णांक_उच्च, rate);
पूर्ण

