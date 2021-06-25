<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * ff.h - a part of driver क्रम RME Fireface series
 *
 * Copyright (c) 2015-2017 Takashi Sakamoto
 */

#अगर_अघोषित SOUND_FIREFACE_H_INCLUDED
#घोषणा SOUND_FIREFACE_H_INCLUDED

#समावेश <linux/device.h>
#समावेश <linux/firewire.h>
#समावेश <linux/firewire-स्थिरants.h>
#समावेश <linux/module.h>
#समावेश <linux/mod_devicetable.h>
#समावेश <linux/mutex.h>
#समावेश <linux/slab.h>
#समावेश <linux/compat.h>
#समावेश <linux/sched/संकेत.स>

#समावेश <sound/core.h>
#समावेश <sound/info.h>
#समावेश <sound/rawmidi.h>
#समावेश <sound/pcm.h>
#समावेश <sound/pcm_params.h>
#समावेश <sound/hwdep.h>
#समावेश <sound/firewire.h>

#समावेश "../lib.h"
#समावेश "../amdtp-stream.h"
#समावेश "../iso-resources.h"

#घोषणा SND_FF_MAXIMIM_MIDI_QUADS	9
#घोषणा SND_FF_IN_MIDI_PORTS		2
#घोषणा SND_FF_OUT_MIDI_PORTS		2

क्रमागत snd_ff_unit_version अणु
	SND_FF_UNIT_VERSION_FF800	= 0x000001,
	SND_FF_UNIT_VERSION_FF400	= 0x000002,
	SND_FF_UNIT_VERSION_UFX		= 0x000003,
	SND_FF_UNIT_VERSION_UCX		= 0x000004,
	SND_FF_UNIT_VERSION_802		= 0x000005,
पूर्ण;

क्रमागत snd_ff_stream_mode अणु
	SND_FF_STREAM_MODE_LOW = 0,
	SND_FF_STREAM_MODE_MID,
	SND_FF_STREAM_MODE_HIGH,
	SND_FF_STREAM_MODE_COUNT,
पूर्ण;

काष्ठा snd_ff_protocol;
काष्ठा snd_ff_spec अणु
	स्थिर अचिन्हित पूर्णांक pcm_capture_channels[SND_FF_STREAM_MODE_COUNT];
	स्थिर अचिन्हित पूर्णांक pcm_playback_channels[SND_FF_STREAM_MODE_COUNT];

	अचिन्हित पूर्णांक midi_in_ports;
	अचिन्हित पूर्णांक midi_out_ports;

	स्थिर काष्ठा snd_ff_protocol *protocol;
	u64 midi_high_addr;
	u8 midi_addr_range;
	u64 midi_rx_addrs[SND_FF_OUT_MIDI_PORTS];
पूर्ण;

काष्ठा snd_ff अणु
	काष्ठा snd_card *card;
	काष्ठा fw_unit *unit;
	काष्ठा mutex mutex;
	spinlock_t lock;

	bool रेजिस्टरed;
	काष्ठा delayed_work dwork;

	क्रमागत snd_ff_unit_version unit_version;
	स्थिर काष्ठा snd_ff_spec *spec;

	/* To handle MIDI tx. */
	काष्ठा snd_rawmidi_substream *tx_midi_substreams[SND_FF_IN_MIDI_PORTS];
	काष्ठा fw_address_handler async_handler;

	/* TO handle MIDI rx. */
	काष्ठा snd_rawmidi_substream *rx_midi_substreams[SND_FF_OUT_MIDI_PORTS];
	bool on_sysex[SND_FF_OUT_MIDI_PORTS];
	__le32 msg_buf[SND_FF_OUT_MIDI_PORTS][SND_FF_MAXIMIM_MIDI_QUADS];
	काष्ठा work_काष्ठा rx_midi_work[SND_FF_OUT_MIDI_PORTS];
	काष्ठा fw_transaction transactions[SND_FF_OUT_MIDI_PORTS];
	kसमय_प्रकार next_kसमय[SND_FF_OUT_MIDI_PORTS];
	bool rx_midi_error[SND_FF_OUT_MIDI_PORTS];
	अचिन्हित पूर्णांक rx_bytes[SND_FF_OUT_MIDI_PORTS];

	अचिन्हित पूर्णांक substreams_counter;
	काष्ठा amdtp_stream tx_stream;
	काष्ठा amdtp_stream rx_stream;
	काष्ठा fw_iso_resources tx_resources;
	काष्ठा fw_iso_resources rx_resources;

	पूर्णांक dev_lock_count;
	bool dev_lock_changed;
	रुको_queue_head_t hwdep_रुको;

	काष्ठा amdtp_करोमुख्य करोमुख्य;
पूर्ण;

क्रमागत snd_ff_घड़ी_src अणु
	SND_FF_CLOCK_SRC_INTERNAL,
	SND_FF_CLOCK_SRC_SPDIF,
	SND_FF_CLOCK_SRC_ADAT1,
	SND_FF_CLOCK_SRC_ADAT2,
	SND_FF_CLOCK_SRC_WORD,
	SND_FF_CLOCK_SRC_LTC,
	/* TODO: perhaps TCO exists. */
पूर्ण;

काष्ठा snd_ff_protocol अणु
	व्योम (*handle_midi_msg)(काष्ठा snd_ff *ff, अचिन्हित पूर्णांक offset,
				__le32 *buf, माप_प्रकार length);
	पूर्णांक (*fill_midi_msg)(काष्ठा snd_ff *ff,
			     काष्ठा snd_rawmidi_substream *substream,
			     अचिन्हित पूर्णांक port);
	पूर्णांक (*get_घड़ी)(काष्ठा snd_ff *ff, अचिन्हित पूर्णांक *rate,
			 क्रमागत snd_ff_घड़ी_src *src);
	पूर्णांक (*चयन_fetching_mode)(काष्ठा snd_ff *ff, bool enable);
	पूर्णांक (*allocate_resources)(काष्ठा snd_ff *ff, अचिन्हित पूर्णांक rate);
	पूर्णांक (*begin_session)(काष्ठा snd_ff *ff, अचिन्हित पूर्णांक rate);
	व्योम (*finish_session)(काष्ठा snd_ff *ff);
	व्योम (*dump_status)(काष्ठा snd_ff *ff, काष्ठा snd_info_buffer *buffer);
पूर्ण;

बाह्य स्थिर काष्ठा snd_ff_protocol snd_ff_protocol_ff800;
बाह्य स्थिर काष्ठा snd_ff_protocol snd_ff_protocol_ff400;
बाह्य स्थिर काष्ठा snd_ff_protocol snd_ff_protocol_latter;

पूर्णांक snd_ff_transaction_रेजिस्टर(काष्ठा snd_ff *ff);
पूर्णांक snd_ff_transaction_reरेजिस्टर(काष्ठा snd_ff *ff);
व्योम snd_ff_transaction_unरेजिस्टर(काष्ठा snd_ff *ff);

पूर्णांक amdtp_ff_set_parameters(काष्ठा amdtp_stream *s, अचिन्हित पूर्णांक rate,
			    अचिन्हित पूर्णांक pcm_channels);
पूर्णांक amdtp_ff_add_pcm_hw_स्थिरraपूर्णांकs(काष्ठा amdtp_stream *s,
				    काष्ठा snd_pcm_runसमय *runसमय);
पूर्णांक amdtp_ff_init(काष्ठा amdtp_stream *s, काष्ठा fw_unit *unit,
		  क्रमागत amdtp_stream_direction dir);

पूर्णांक snd_ff_stream_get_multiplier_mode(क्रमागत cip_sfc sfc,
				      क्रमागत snd_ff_stream_mode *mode);
पूर्णांक snd_ff_stream_init_duplex(काष्ठा snd_ff *ff);
व्योम snd_ff_stream_destroy_duplex(काष्ठा snd_ff *ff);
पूर्णांक snd_ff_stream_reserve_duplex(काष्ठा snd_ff *ff, अचिन्हित पूर्णांक rate,
				 अचिन्हित पूर्णांक frames_per_period,
				 अचिन्हित पूर्णांक frames_per_buffer);
पूर्णांक snd_ff_stream_start_duplex(काष्ठा snd_ff *ff, अचिन्हित पूर्णांक rate);
व्योम snd_ff_stream_stop_duplex(काष्ठा snd_ff *ff);
व्योम snd_ff_stream_update_duplex(काष्ठा snd_ff *ff);

व्योम snd_ff_stream_lock_changed(काष्ठा snd_ff *ff);
पूर्णांक snd_ff_stream_lock_try(काष्ठा snd_ff *ff);
व्योम snd_ff_stream_lock_release(काष्ठा snd_ff *ff);

व्योम snd_ff_proc_init(काष्ठा snd_ff *ff);
स्थिर अक्षर *snd_ff_proc_get_clk_label(क्रमागत snd_ff_घड़ी_src src);

पूर्णांक snd_ff_create_midi_devices(काष्ठा snd_ff *ff);

पूर्णांक snd_ff_create_pcm_devices(काष्ठा snd_ff *ff);

पूर्णांक snd_ff_create_hwdep_devices(काष्ठा snd_ff *ff);

#पूर्ण_अगर
