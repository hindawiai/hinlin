<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * digi00x.h - a part of driver क्रम Digidesign Digi 002/003 family
 *
 * Copyright (c) 2014-2015 Takashi Sakamoto
 */

#अगर_अघोषित SOUND_DIGI00X_H_INCLUDED
#घोषणा SOUND_DIGI00X_H_INCLUDED

#समावेश <linux/compat.h>
#समावेश <linux/device.h>
#समावेश <linux/firewire.h>
#समावेश <linux/module.h>
#समावेश <linux/mod_devicetable.h>
#समावेश <linux/delay.h>
#समावेश <linux/slab.h>
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
#समावेश "../iso-resources.h"
#समावेश "../amdtp-stream.h"

काष्ठा snd_dg00x अणु
	काष्ठा snd_card *card;
	काष्ठा fw_unit *unit;

	काष्ठा mutex mutex;
	spinlock_t lock;

	bool रेजिस्टरed;
	काष्ठा delayed_work dwork;

	काष्ठा amdtp_stream tx_stream;
	काष्ठा fw_iso_resources tx_resources;

	काष्ठा amdtp_stream rx_stream;
	काष्ठा fw_iso_resources rx_resources;

	अचिन्हित पूर्णांक substreams_counter;

	/* क्रम uapi */
	पूर्णांक dev_lock_count;
	bool dev_lock_changed;
	रुको_queue_head_t hwdep_रुको;

	/* For asynchronous messages. */
	काष्ठा fw_address_handler async_handler;
	u32 msg;

	/* Console models have additional MIDI ports क्रम control surface. */
	bool is_console;

	काष्ठा amdtp_करोमुख्य करोमुख्य;
पूर्ण;

#घोषणा DG00X_ADDR_BASE		0xffffe0000000ull

#घोषणा DG00X_OFFSET_STREAMING_STATE	0x0000
#घोषणा DG00X_OFFSET_STREAMING_SET	0x0004
/* unknown but address in host space	0x0008 */
/* For LSB of the address		0x000c */
/* unknown				0x0010 */
#घोषणा DG00X_OFFSET_MESSAGE_ADDR	0x0014
/* For LSB of the address		0x0018 */
/* unknown				0x001c */
/* unknown				0x0020 */
/* not used			0x0024--0x00ff */
#घोषणा DG00X_OFFSET_ISOC_CHANNELS	0x0100
/* unknown				0x0104 */
/* unknown				0x0108 */
/* unknown				0x010c */
#घोषणा DG00X_OFFSET_LOCAL_RATE		0x0110
#घोषणा DG00X_OFFSET_EXTERNAL_RATE	0x0114
#घोषणा DG00X_OFFSET_CLOCK_SOURCE	0x0118
#घोषणा DG00X_OFFSET_OPT_IFACE_MODE	0x011c
/* unknown				0x0120 */
/* Mixer control on/off			0x0124 */
/* unknown				0x0128 */
#घोषणा DG00X_OFFSET_DETECT_EXTERNAL	0x012c
/* unknown				0x0138 */
#घोषणा DG00X_OFFSET_MMC		0x0400

क्रमागत snd_dg00x_rate अणु
	SND_DG00X_RATE_44100 = 0,
	SND_DG00X_RATE_48000,
	SND_DG00X_RATE_88200,
	SND_DG00X_RATE_96000,
	SND_DG00X_RATE_COUNT,
पूर्ण;

क्रमागत snd_dg00x_घड़ी अणु
	SND_DG00X_CLOCK_INTERNAL = 0,
	SND_DG00X_CLOCK_SPDIF,
	SND_DG00X_CLOCK_ADAT,
	SND_DG00X_CLOCK_WORD,
	SND_DG00X_CLOCK_COUNT,
पूर्ण;

क्रमागत snd_dg00x_optical_mode अणु
	SND_DG00X_OPT_IFACE_MODE_ADAT = 0,
	SND_DG00X_OPT_IFACE_MODE_SPDIF,
	SND_DG00X_OPT_IFACE_MODE_COUNT,
पूर्ण;

#घोषणा DOT_MIDI_IN_PORTS	1
#घोषणा DOT_MIDI_OUT_PORTS	2

पूर्णांक amdtp_करोt_init(काष्ठा amdtp_stream *s, काष्ठा fw_unit *unit,
		   क्रमागत amdtp_stream_direction dir);
पूर्णांक amdtp_करोt_set_parameters(काष्ठा amdtp_stream *s, अचिन्हित पूर्णांक rate,
			     अचिन्हित पूर्णांक pcm_channels);
व्योम amdtp_करोt_reset(काष्ठा amdtp_stream *s);
पूर्णांक amdtp_करोt_add_pcm_hw_स्थिरraपूर्णांकs(काष्ठा amdtp_stream *s,
				     काष्ठा snd_pcm_runसमय *runसमय);
व्योम amdtp_करोt_midi_trigger(काष्ठा amdtp_stream *s, अचिन्हित पूर्णांक port,
			  काष्ठा snd_rawmidi_substream *midi);

पूर्णांक snd_dg00x_transaction_रेजिस्टर(काष्ठा snd_dg00x *dg00x);
पूर्णांक snd_dg00x_transaction_reरेजिस्टर(काष्ठा snd_dg00x *dg00x);
व्योम snd_dg00x_transaction_unरेजिस्टर(काष्ठा snd_dg00x *dg00x);

बाह्य स्थिर अचिन्हित पूर्णांक snd_dg00x_stream_rates[SND_DG00X_RATE_COUNT];
बाह्य स्थिर अचिन्हित पूर्णांक snd_dg00x_stream_pcm_channels[SND_DG00X_RATE_COUNT];
पूर्णांक snd_dg00x_stream_get_बाह्यal_rate(काष्ठा snd_dg00x *dg00x,
				       अचिन्हित पूर्णांक *rate);
पूर्णांक snd_dg00x_stream_get_local_rate(काष्ठा snd_dg00x *dg00x,
				    अचिन्हित पूर्णांक *rate);
पूर्णांक snd_dg00x_stream_set_local_rate(काष्ठा snd_dg00x *dg00x, अचिन्हित पूर्णांक rate);
पूर्णांक snd_dg00x_stream_get_घड़ी(काष्ठा snd_dg00x *dg00x,
			       क्रमागत snd_dg00x_घड़ी *घड़ी);
पूर्णांक snd_dg00x_stream_check_बाह्यal_घड़ी(काष्ठा snd_dg00x *dg00x,
					  bool *detect);
पूर्णांक snd_dg00x_stream_init_duplex(काष्ठा snd_dg00x *dg00x);
पूर्णांक snd_dg00x_stream_reserve_duplex(काष्ठा snd_dg00x *dg00x, अचिन्हित पूर्णांक rate,
				    अचिन्हित पूर्णांक frames_per_period,
				    अचिन्हित पूर्णांक frames_per_buffer);
पूर्णांक snd_dg00x_stream_start_duplex(काष्ठा snd_dg00x *dg00x);
व्योम snd_dg00x_stream_stop_duplex(काष्ठा snd_dg00x *dg00x);
व्योम snd_dg00x_stream_update_duplex(काष्ठा snd_dg00x *dg00x);
व्योम snd_dg00x_stream_destroy_duplex(काष्ठा snd_dg00x *dg00x);

व्योम snd_dg00x_stream_lock_changed(काष्ठा snd_dg00x *dg00x);
पूर्णांक snd_dg00x_stream_lock_try(काष्ठा snd_dg00x *dg00x);
व्योम snd_dg00x_stream_lock_release(काष्ठा snd_dg00x *dg00x);

व्योम snd_dg00x_proc_init(काष्ठा snd_dg00x *dg00x);

पूर्णांक snd_dg00x_create_pcm_devices(काष्ठा snd_dg00x *dg00x);

पूर्णांक snd_dg00x_create_midi_devices(काष्ठा snd_dg00x *dg00x);

पूर्णांक snd_dg00x_create_hwdep_device(काष्ठा snd_dg00x *dg00x);
#पूर्ण_अगर
