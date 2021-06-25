<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * tascam.h - a part of driver क्रम TASCAM FireWire series
 *
 * Copyright (c) 2015 Takashi Sakamoto
 */

#अगर_अघोषित SOUND_TASCAM_H_INCLUDED
#घोषणा SOUND_TASCAM_H_INCLUDED

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
#समावेश <sound/initval.h>
#समावेश <sound/info.h>
#समावेश <sound/pcm.h>
#समावेश <sound/pcm_params.h>
#समावेश <sound/firewire.h>
#समावेश <sound/hwdep.h>
#समावेश <sound/rawmidi.h>

#समावेश "../lib.h"
#समावेश "../amdtp-stream.h"
#समावेश "../iso-resources.h"

काष्ठा snd_tscm_spec अणु
	स्थिर अक्षर *स्थिर name;
	bool has_adat;
	bool has_spdअगर;
	अचिन्हित पूर्णांक pcm_capture_analog_channels;
	अचिन्हित पूर्णांक pcm_playback_analog_channels;
	अचिन्हित पूर्णांक midi_capture_ports;
	अचिन्हित पूर्णांक midi_playback_ports;
पूर्ण;

#घोषणा TSCM_MIDI_IN_PORT_MAX	4
#घोषणा TSCM_MIDI_OUT_PORT_MAX	4

काष्ठा snd_fw_async_midi_port अणु
	काष्ठा fw_device *parent;
	काष्ठा work_काष्ठा work;
	bool idling;
	kसमय_प्रकार next_kसमय;
	bool error;

	काष्ठा fw_transaction transaction;

	u8 buf[4];
	u8 running_status;
	bool on_sysex;

	काष्ठा snd_rawmidi_substream *substream;
	पूर्णांक consume_bytes;
पूर्ण;

#घोषणा SND_TSCM_QUEUE_COUNT	16

काष्ठा snd_tscm अणु
	काष्ठा snd_card *card;
	काष्ठा fw_unit *unit;

	काष्ठा mutex mutex;
	spinlock_t lock;

	bool रेजिस्टरed;
	काष्ठा delayed_work dwork;
	स्थिर काष्ठा snd_tscm_spec *spec;

	काष्ठा fw_iso_resources tx_resources;
	काष्ठा fw_iso_resources rx_resources;
	काष्ठा amdtp_stream tx_stream;
	काष्ठा amdtp_stream rx_stream;
	अचिन्हित पूर्णांक substreams_counter;

	पूर्णांक dev_lock_count;
	bool dev_lock_changed;
	रुको_queue_head_t hwdep_रुको;

	/* For MIDI message incoming transactions. */
	काष्ठा fw_address_handler async_handler;
	काष्ठा snd_rawmidi_substream *tx_midi_substreams[TSCM_MIDI_IN_PORT_MAX];

	/* For MIDI message outgoing transactions. */
	काष्ठा snd_fw_async_midi_port out_ports[TSCM_MIDI_OUT_PORT_MAX];

	// A cache of status inक्रमmation in tx isoc packets.
	__be32 state[SNDRV_FIREWIRE_TASCAM_STATE_COUNT];
	काष्ठा snd_hwdep *hwdep;
	काष्ठा snd_firewire_tascam_change queue[SND_TSCM_QUEUE_COUNT];
	अचिन्हित पूर्णांक pull_pos;
	अचिन्हित पूर्णांक push_pos;

	काष्ठा amdtp_करोमुख्य करोमुख्य;
पूर्ण;

#घोषणा TSCM_ADDR_BASE			0xffff00000000ull

#घोषणा TSCM_OFFSET_FIRMWARE_REGISTER	0x0000
#घोषणा TSCM_OFFSET_FIRMWARE_FPGA	0x0004
#घोषणा TSCM_OFFSET_FIRMWARE_ARM	0x0008
#घोषणा TSCM_OFFSET_FIRMWARE_HW		0x000c

#घोषणा TSCM_OFFSET_ISOC_TX_CH		0x0200
#घोषणा TSCM_OFFSET_UNKNOWN		0x0204
#घोषणा TSCM_OFFSET_START_STREAMING	0x0208
#घोषणा TSCM_OFFSET_ISOC_RX_CH		0x020c
#घोषणा TSCM_OFFSET_ISOC_RX_ON		0x0210	/* Little conviction. */
#घोषणा TSCM_OFFSET_TX_PCM_CHANNELS	0x0214
#घोषणा TSCM_OFFSET_RX_PCM_CHANNELS	0x0218
#घोषणा TSCM_OFFSET_MULTIPLEX_MODE	0x021c
#घोषणा TSCM_OFFSET_ISOC_TX_ON		0x0220
/* Unknown				0x0224 */
#घोषणा TSCM_OFFSET_CLOCK_STATUS	0x0228
#घोषणा TSCM_OFFSET_SET_OPTION		0x022c

#घोषणा TSCM_OFFSET_MIDI_TX_ON		0x0300
#घोषणा TSCM_OFFSET_MIDI_TX_ADDR_HI	0x0304
#घोषणा TSCM_OFFSET_MIDI_TX_ADDR_LO	0x0308

#घोषणा TSCM_OFFSET_LED_POWER		0x0404

#घोषणा TSCM_OFFSET_MIDI_RX_QUAD	0x4000

// Although FE-8 supports the above रेजिस्टरs, it has no I/O पूर्णांकerfaces क्रम
// audio samples and music messages. Otherwise it supports another notअगरication
// क्रम status and control message as well as LED brightening. The message
// consists of quadlet-aligned data up to 32 quadlets. The first byte of message
// is fixed to 0x40. The second byte is between 0x00 to 0x1f and represent each
// control:
//   fader:	0x00-0x07
//   button:	0x0d, 0x0e
//   knob:	0x14-0x1b
//   sensing:	0x0b
//
// The rest two bytes represent state of the controls; e.g. current value क्रम
// fader and knob, biपंचांगasks क्रम button and sensing.
// Just after turning on, 32 quadlets messages with 0x00-0x1f are immediately
// sent in one transaction. After, several quadlets are sent in one transaction.
//
// TSCM_OFFSET_FE8_CTL_TX_ON		0x0310
// TSCM_OFFSET_FE8_CTL_TX_ADDR_HI	0x0314
// TSCM_OFFSET_FE8_CTL_TX_ADDR_LO	0x0318

क्रमागत snd_tscm_घड़ी अणु
	SND_TSCM_CLOCK_INTERNAL = 0,
	SND_TSCM_CLOCK_WORD	= 1,
	SND_TSCM_CLOCK_SPDIF	= 2,
	SND_TSCM_CLOCK_ADAT	= 3,
पूर्ण;

पूर्णांक amdtp_tscm_init(काष्ठा amdtp_stream *s, काष्ठा fw_unit *unit,
		  क्रमागत amdtp_stream_direction dir, अचिन्हित पूर्णांक pcm_channels);
पूर्णांक amdtp_tscm_set_parameters(काष्ठा amdtp_stream *s, अचिन्हित पूर्णांक rate);
पूर्णांक amdtp_tscm_add_pcm_hw_स्थिरraपूर्णांकs(काष्ठा amdtp_stream *s,
				      काष्ठा snd_pcm_runसमय *runसमय);

पूर्णांक snd_tscm_stream_get_rate(काष्ठा snd_tscm *tscm, अचिन्हित पूर्णांक *rate);
पूर्णांक snd_tscm_stream_get_घड़ी(काष्ठा snd_tscm *tscm,
			      क्रमागत snd_tscm_घड़ी *घड़ी);
पूर्णांक snd_tscm_stream_init_duplex(काष्ठा snd_tscm *tscm);
व्योम snd_tscm_stream_update_duplex(काष्ठा snd_tscm *tscm);
व्योम snd_tscm_stream_destroy_duplex(काष्ठा snd_tscm *tscm);
पूर्णांक snd_tscm_stream_reserve_duplex(काष्ठा snd_tscm *tscm, अचिन्हित पूर्णांक rate,
				   अचिन्हित पूर्णांक frames_per_period,
				   अचिन्हित पूर्णांक frames_per_buffer);
पूर्णांक snd_tscm_stream_start_duplex(काष्ठा snd_tscm *tscm, अचिन्हित पूर्णांक rate);
व्योम snd_tscm_stream_stop_duplex(काष्ठा snd_tscm *tscm);

व्योम snd_tscm_stream_lock_changed(काष्ठा snd_tscm *tscm);
पूर्णांक snd_tscm_stream_lock_try(काष्ठा snd_tscm *tscm);
व्योम snd_tscm_stream_lock_release(काष्ठा snd_tscm *tscm);

व्योम snd_fw_async_midi_port_init(काष्ठा snd_fw_async_midi_port *port);

अटल अंतरभूत व्योम
snd_fw_async_midi_port_run(काष्ठा snd_fw_async_midi_port *port,
			   काष्ठा snd_rawmidi_substream *substream)
अणु
	अगर (!port->error) अणु
		port->substream = substream;
		schedule_work(&port->work);
	पूर्ण
पूर्ण

अटल अंतरभूत व्योम
snd_fw_async_midi_port_finish(काष्ठा snd_fw_async_midi_port *port)
अणु
	port->substream = शून्य;
	cancel_work_sync(&port->work);
	port->error = false;
पूर्ण

पूर्णांक snd_tscm_transaction_रेजिस्टर(काष्ठा snd_tscm *tscm);
पूर्णांक snd_tscm_transaction_reरेजिस्टर(काष्ठा snd_tscm *tscm);
व्योम snd_tscm_transaction_unरेजिस्टर(काष्ठा snd_tscm *tscm);

व्योम snd_tscm_proc_init(काष्ठा snd_tscm *tscm);

पूर्णांक snd_tscm_create_pcm_devices(काष्ठा snd_tscm *tscm);

पूर्णांक snd_tscm_create_midi_devices(काष्ठा snd_tscm *tscm);

पूर्णांक snd_tscm_create_hwdep_device(काष्ठा snd_tscm *tscm);

#पूर्ण_अगर
