<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * fireworks.h - a part of driver क्रम Fireworks based devices
 *
 * Copyright (c) 2009-2010 Clemens Ladisch
 * Copyright (c) 2013-2014 Takashi Sakamoto
 */
#अगर_अघोषित SOUND_FIREWORKS_H_INCLUDED
#घोषणा SOUND_FIREWORKS_H_INCLUDED

#समावेश <linux/compat.h>
#समावेश <linux/device.h>
#समावेश <linux/firewire.h>
#समावेश <linux/firewire-स्थिरants.h>
#समावेश <linux/module.h>
#समावेश <linux/mod_devicetable.h>
#समावेश <linux/delay.h>
#समावेश <linux/slab.h>
#समावेश <linux/sched/संकेत.स>

#समावेश <sound/core.h>
#समावेश <sound/initval.h>
#समावेश <sound/pcm.h>
#समावेश <sound/info.h>
#समावेश <sound/rawmidi.h>
#समावेश <sound/pcm_params.h>
#समावेश <sound/firewire.h>
#समावेश <sound/hwdep.h>

#समावेश "../packets-buffer.h"
#समावेश "../iso-resources.h"
#समावेश "../amdtp-am824.h"
#समावेश "../cmp.h"
#समावेश "../lib.h"

#घोषणा SND_EFW_MAX_MIDI_OUT_PORTS	2
#घोषणा SND_EFW_MAX_MIDI_IN_PORTS	2

#घोषणा SND_EFW_MULTIPLIER_MODES	3
#घोषणा HWINFO_NAME_SIZE_BYTES		32
#घोषणा HWINFO_MAX_CAPS_GROUPS		8

/*
 * This should be greater than maximum bytes क्रम EFW response content.
 * Currently response against command क्रम isochronous channel mapping is
 * confirmed to be the maximum one. But क्रम flexibility, use maximum data
 * payload क्रम asynchronous primary packets at S100 (Cable base rate) in
 * IEEE Std 1394-1995.
 */
#घोषणा SND_EFW_RESPONSE_MAXIMUM_BYTES	0x200U

बाह्य अचिन्हित पूर्णांक snd_efw_resp_buf_size;
बाह्य bool snd_efw_resp_buf_debug;

काष्ठा snd_efw_phys_grp अणु
	u8 type;	/* see क्रमागत snd_efw_grp_type */
	u8 count;
पूर्ण __packed;

काष्ठा snd_efw अणु
	काष्ठा snd_card *card;
	काष्ठा fw_unit *unit;
	पूर्णांक card_index;

	काष्ठा mutex mutex;
	spinlock_t lock;

	bool रेजिस्टरed;
	काष्ठा delayed_work dwork;

	/* क्रम transaction */
	u32 seqnum;
	bool resp_addr_changable;

	/* क्रम quirks */
	bool is_af9;
	bool is_fireworks3;
	u32 firmware_version;

	अचिन्हित पूर्णांक midi_in_ports;
	अचिन्हित पूर्णांक midi_out_ports;

	अचिन्हित पूर्णांक supported_sampling_rate;
	अचिन्हित पूर्णांक pcm_capture_channels[SND_EFW_MULTIPLIER_MODES];
	अचिन्हित पूर्णांक pcm_playback_channels[SND_EFW_MULTIPLIER_MODES];

	काष्ठा amdtp_stream tx_stream;
	काष्ठा amdtp_stream rx_stream;
	काष्ठा cmp_connection out_conn;
	काष्ठा cmp_connection in_conn;
	अचिन्हित पूर्णांक substreams_counter;

	/* hardware metering parameters */
	अचिन्हित पूर्णांक phys_out;
	अचिन्हित पूर्णांक phys_in;
	अचिन्हित पूर्णांक phys_out_grp_count;
	अचिन्हित पूर्णांक phys_in_grp_count;
	काष्ठा snd_efw_phys_grp phys_out_grps[HWINFO_MAX_CAPS_GROUPS];
	काष्ठा snd_efw_phys_grp phys_in_grps[HWINFO_MAX_CAPS_GROUPS];

	/* क्रम uapi */
	पूर्णांक dev_lock_count;
	bool dev_lock_changed;
	रुको_queue_head_t hwdep_रुको;

	/* response queue */
	u8 *resp_buf;
	u8 *pull_ptr;
	u8 *push_ptr;

	काष्ठा amdtp_करोमुख्य करोमुख्य;
पूर्ण;

पूर्णांक snd_efw_transaction_cmd(काष्ठा fw_unit *unit,
			    स्थिर व्योम *cmd, अचिन्हित पूर्णांक size);
पूर्णांक snd_efw_transaction_run(काष्ठा fw_unit *unit,
			    स्थिर व्योम *cmd, अचिन्हित पूर्णांक cmd_size,
			    व्योम *resp, अचिन्हित पूर्णांक resp_size);
पूर्णांक snd_efw_transaction_रेजिस्टर(व्योम);
व्योम snd_efw_transaction_unरेजिस्टर(व्योम);
व्योम snd_efw_transaction_bus_reset(काष्ठा fw_unit *unit);
व्योम snd_efw_transaction_add_instance(काष्ठा snd_efw *efw);
व्योम snd_efw_transaction_हटाओ_instance(काष्ठा snd_efw *efw);

काष्ठा snd_efw_hwinfo अणु
	u32 flags;
	u32 guid_hi;
	u32 guid_lo;
	u32 type;
	u32 version;
	अक्षर venकरोr_name[HWINFO_NAME_SIZE_BYTES];
	अक्षर model_name[HWINFO_NAME_SIZE_BYTES];
	u32 supported_घड़ीs;
	u32 amdtp_rx_pcm_channels;
	u32 amdtp_tx_pcm_channels;
	u32 phys_out;
	u32 phys_in;
	u32 phys_out_grp_count;
	काष्ठा snd_efw_phys_grp phys_out_grps[HWINFO_MAX_CAPS_GROUPS];
	u32 phys_in_grp_count;
	काष्ठा snd_efw_phys_grp phys_in_grps[HWINFO_MAX_CAPS_GROUPS];
	u32 midi_out_ports;
	u32 midi_in_ports;
	u32 max_sample_rate;
	u32 min_sample_rate;
	u32 dsp_version;
	u32 arm_version;
	u32 mixer_playback_channels;
	u32 mixer_capture_channels;
	u32 fpga_version;
	u32 amdtp_rx_pcm_channels_2x;
	u32 amdtp_tx_pcm_channels_2x;
	u32 amdtp_rx_pcm_channels_4x;
	u32 amdtp_tx_pcm_channels_4x;
	u32 reserved[16];
पूर्ण __packed;
क्रमागत snd_efw_grp_type अणु
	SND_EFW_CH_TYPE_ANALOG			= 0,
	SND_EFW_CH_TYPE_SPDIF			= 1,
	SND_EFW_CH_TYPE_ADAT			= 2,
	SND_EFW_CH_TYPE_SPDIF_OR_ADAT		= 3,
	SND_EFW_CH_TYPE_ANALOG_MIRRORING	= 4,
	SND_EFW_CH_TYPE_HEADPHONES		= 5,
	SND_EFW_CH_TYPE_I2S			= 6,
	SND_EFW_CH_TYPE_GUITAR			= 7,
	SND_EFW_CH_TYPE_PIEZO_GUITAR		= 8,
	SND_EFW_CH_TYPE_GUITAR_STRING		= 9,
	SND_EFW_CH_TYPE_DUMMY
पूर्ण;
काष्ठा snd_efw_phys_meters अणु
	u32 status;	/* guitar state/midi संकेत/घड़ी input detect */
	u32 reserved0;
	u32 reserved1;
	u32 reserved2;
	u32 reserved3;
	u32 out_meters;
	u32 in_meters;
	u32 reserved4;
	u32 reserved5;
	u32 values[];
पूर्ण __packed;
क्रमागत snd_efw_घड़ी_source अणु
	SND_EFW_CLOCK_SOURCE_INTERNAL	= 0,
	SND_EFW_CLOCK_SOURCE_SYTMATCH	= 1,
	SND_EFW_CLOCK_SOURCE_WORDCLOCK	= 2,
	SND_EFW_CLOCK_SOURCE_SPDIF	= 3,
	SND_EFW_CLOCK_SOURCE_ADAT_1	= 4,
	SND_EFW_CLOCK_SOURCE_ADAT_2	= 5,
	SND_EFW_CLOCK_SOURCE_CONTINUOUS	= 6	/* पूर्णांकernal variable घड़ी */
पूर्ण;
क्रमागत snd_efw_transport_mode अणु
	SND_EFW_TRANSPORT_MODE_WINDOWS	= 0,
	SND_EFW_TRANSPORT_MODE_IEC61883	= 1,
पूर्ण;
पूर्णांक snd_efw_command_set_resp_addr(काष्ठा snd_efw *efw,
				  u16 addr_high, u32 addr_low);
पूर्णांक snd_efw_command_set_tx_mode(काष्ठा snd_efw *efw,
				क्रमागत snd_efw_transport_mode mode);
पूर्णांक snd_efw_command_get_hwinfo(काष्ठा snd_efw *efw,
			       काष्ठा snd_efw_hwinfo *hwinfo);
पूर्णांक snd_efw_command_get_phys_meters(काष्ठा snd_efw *efw,
				    काष्ठा snd_efw_phys_meters *meters,
				    अचिन्हित पूर्णांक len);
पूर्णांक snd_efw_command_get_घड़ी_source(काष्ठा snd_efw *efw,
				     क्रमागत snd_efw_घड़ी_source *source);
पूर्णांक snd_efw_command_get_sampling_rate(काष्ठा snd_efw *efw, अचिन्हित पूर्णांक *rate);
पूर्णांक snd_efw_command_set_sampling_rate(काष्ठा snd_efw *efw, अचिन्हित पूर्णांक rate);

पूर्णांक snd_efw_stream_init_duplex(काष्ठा snd_efw *efw);
पूर्णांक snd_efw_stream_reserve_duplex(काष्ठा snd_efw *efw, अचिन्हित पूर्णांक rate,
				  अचिन्हित पूर्णांक frames_per_period,
				  अचिन्हित पूर्णांक frames_per_buffer);
पूर्णांक snd_efw_stream_start_duplex(काष्ठा snd_efw *efw);
व्योम snd_efw_stream_stop_duplex(काष्ठा snd_efw *efw);
व्योम snd_efw_stream_update_duplex(काष्ठा snd_efw *efw);
व्योम snd_efw_stream_destroy_duplex(काष्ठा snd_efw *efw);
व्योम snd_efw_stream_lock_changed(काष्ठा snd_efw *efw);
पूर्णांक snd_efw_stream_lock_try(काष्ठा snd_efw *efw);
व्योम snd_efw_stream_lock_release(काष्ठा snd_efw *efw);

व्योम snd_efw_proc_init(काष्ठा snd_efw *efw);

पूर्णांक snd_efw_create_midi_devices(काष्ठा snd_efw *efw);

पूर्णांक snd_efw_create_pcm_devices(काष्ठा snd_efw *efw);
पूर्णांक snd_efw_get_multiplier_mode(अचिन्हित पूर्णांक sampling_rate, अचिन्हित पूर्णांक *mode);

पूर्णांक snd_efw_create_hwdep_device(काष्ठा snd_efw *efw);

#घोषणा SND_EFW_DEV_ENTRY(venकरोr, model) \
अणु \
	.match_flags	= IEEE1394_MATCH_VENDOR_ID | \
			  IEEE1394_MATCH_MODEL_ID, \
	.venकरोr_id	= venकरोr,\
	.model_id	= model \
पूर्ण

#पूर्ण_अगर
