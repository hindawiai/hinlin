<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * dice.h - a part of driver क्रम Dice based devices
 *
 * Copyright (c) Clemens Ladisch
 * Copyright (c) 2014 Takashi Sakamoto
 */

#अगर_अघोषित SOUND_DICE_H_INCLUDED
#घोषणा SOUND_DICE_H_INCLUDED

#समावेश <linux/compat.h>
#समावेश <linux/completion.h>
#समावेश <linux/delay.h>
#समावेश <linux/device.h>
#समावेश <linux/firewire.h>
#समावेश <linux/firewire-स्थिरants.h>
#समावेश <linux/jअगरfies.h>
#समावेश <linux/module.h>
#समावेश <linux/mod_devicetable.h>
#समावेश <linux/mutex.h>
#समावेश <linux/slab.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/रुको.h>
#समावेश <linux/sched/संकेत.स>

#समावेश <sound/control.h>
#समावेश <sound/core.h>
#समावेश <sound/firewire.h>
#समावेश <sound/hwdep.h>
#समावेश <sound/info.h>
#समावेश <sound/initval.h>
#समावेश <sound/pcm.h>
#समावेश <sound/pcm_params.h>
#समावेश <sound/rawmidi.h>

#समावेश "../amdtp-am824.h"
#समावेश "../iso-resources.h"
#समावेश "../lib.h"
#समावेश "dice-interface.h"

/*
 * This module support maximum 2 pairs of tx/rx isochronous streams क्रम
 * our convinience.
 *
 * In करोcuments क्रम ASICs called with a name of 'DICE':
 *  - ASIC क्रम DICE II:
 *   - Maximum 2 tx and 4 rx are supported.
 *   - A packet supports maximum 16 data channels.
 *  - TCD2210/2210-E (so-called 'Dice Mini'):
 *   - Maximum 2 tx and 2 rx are supported.
 *   - A packet supports maximum 16 data channels.
 *  - TCD2220/2220-E (so-called 'Dice Jr.')
 *   - 2 tx and 2 rx are supported.
 *   - A packet supports maximum 16 data channels.
 *  - TCD3070-CH (so-called 'Dice III')
 *   - Maximum 2 tx and 2 rx are supported.
 *   - A packet supports maximum 32 data channels.
 *
 * For the above, MIDI conक्रमmant data channel is just on the first isochronous
 * stream.
 */
#घोषणा MAX_STREAMS	2

क्रमागत snd_dice_rate_mode अणु
	SND_DICE_RATE_MODE_LOW = 0,
	SND_DICE_RATE_MODE_MIDDLE,
	SND_DICE_RATE_MODE_HIGH,
	SND_DICE_RATE_MODE_COUNT,
पूर्ण;

काष्ठा snd_dice;
प्रकार पूर्णांक (*snd_dice_detect_क्रमmats_t)(काष्ठा snd_dice *dice);

काष्ठा snd_dice अणु
	काष्ठा snd_card *card;
	काष्ठा fw_unit *unit;
	spinlock_t lock;
	काष्ठा mutex mutex;

	bool रेजिस्टरed;
	काष्ठा delayed_work dwork;

	/* Offsets क्रम sub-addresses */
	अचिन्हित पूर्णांक global_offset;
	अचिन्हित पूर्णांक rx_offset;
	अचिन्हित पूर्णांक tx_offset;
	अचिन्हित पूर्णांक sync_offset;
	अचिन्हित पूर्णांक rsrv_offset;

	अचिन्हित पूर्णांक घड़ी_caps;
	अचिन्हित पूर्णांक tx_pcm_chs[MAX_STREAMS][SND_DICE_RATE_MODE_COUNT];
	अचिन्हित पूर्णांक rx_pcm_chs[MAX_STREAMS][SND_DICE_RATE_MODE_COUNT];
	अचिन्हित पूर्णांक tx_midi_ports[MAX_STREAMS];
	अचिन्हित पूर्णांक rx_midi_ports[MAX_STREAMS];
	snd_dice_detect_क्रमmats_t detect_क्रमmats;

	काष्ठा fw_address_handler notअगरication_handler;
	पूर्णांक owner_generation;
	u32 notअगरication_bits;

	/* For uapi */
	पूर्णांक dev_lock_count; /* > 0 driver, < 0 userspace */
	bool dev_lock_changed;
	रुको_queue_head_t hwdep_रुको;

	/* For streaming */
	काष्ठा fw_iso_resources tx_resources[MAX_STREAMS];
	काष्ठा fw_iso_resources rx_resources[MAX_STREAMS];
	काष्ठा amdtp_stream tx_stream[MAX_STREAMS];
	काष्ठा amdtp_stream rx_stream[MAX_STREAMS];
	bool global_enabled:1;
	bool disable_द्विगुन_pcm_frames:1;
	काष्ठा completion घड़ी_accepted;
	अचिन्हित पूर्णांक substreams_counter;

	काष्ठा amdtp_करोमुख्य करोमुख्य;
पूर्ण;

क्रमागत snd_dice_addr_type अणु
	SND_DICE_ADDR_TYPE_PRIVATE,
	SND_DICE_ADDR_TYPE_GLOBAL,
	SND_DICE_ADDR_TYPE_TX,
	SND_DICE_ADDR_TYPE_RX,
	SND_DICE_ADDR_TYPE_SYNC,
	SND_DICE_ADDR_TYPE_RSRV,
पूर्ण;

पूर्णांक snd_dice_transaction_ग_लिखो(काष्ठा snd_dice *dice,
			       क्रमागत snd_dice_addr_type type,
			       अचिन्हित पूर्णांक offset,
			       व्योम *buf, अचिन्हित पूर्णांक len);
पूर्णांक snd_dice_transaction_पढ़ो(काष्ठा snd_dice *dice,
			      क्रमागत snd_dice_addr_type type, अचिन्हित पूर्णांक offset,
			      व्योम *buf, अचिन्हित पूर्णांक len);

अटल अंतरभूत पूर्णांक snd_dice_transaction_ग_लिखो_global(काष्ठा snd_dice *dice,
						    अचिन्हित पूर्णांक offset,
						    व्योम *buf, अचिन्हित पूर्णांक len)
अणु
	वापस snd_dice_transaction_ग_लिखो(dice,
					  SND_DICE_ADDR_TYPE_GLOBAL, offset,
					  buf, len);
पूर्ण
अटल अंतरभूत पूर्णांक snd_dice_transaction_पढ़ो_global(काष्ठा snd_dice *dice,
						   अचिन्हित पूर्णांक offset,
						   व्योम *buf, अचिन्हित पूर्णांक len)
अणु
	वापस snd_dice_transaction_पढ़ो(dice,
					 SND_DICE_ADDR_TYPE_GLOBAL, offset,
					 buf, len);
पूर्ण
अटल अंतरभूत पूर्णांक snd_dice_transaction_ग_लिखो_tx(काष्ठा snd_dice *dice,
						अचिन्हित पूर्णांक offset,
						व्योम *buf, अचिन्हित पूर्णांक len)
अणु
	वापस snd_dice_transaction_ग_लिखो(dice, SND_DICE_ADDR_TYPE_TX, offset,
					  buf, len);
पूर्ण
अटल अंतरभूत पूर्णांक snd_dice_transaction_पढ़ो_tx(काष्ठा snd_dice *dice,
					       अचिन्हित पूर्णांक offset,
					       व्योम *buf, अचिन्हित पूर्णांक len)
अणु
	वापस snd_dice_transaction_पढ़ो(dice, SND_DICE_ADDR_TYPE_TX, offset,
					 buf, len);
पूर्ण
अटल अंतरभूत पूर्णांक snd_dice_transaction_ग_लिखो_rx(काष्ठा snd_dice *dice,
						अचिन्हित पूर्णांक offset,
						व्योम *buf, अचिन्हित पूर्णांक len)
अणु
	वापस snd_dice_transaction_ग_लिखो(dice, SND_DICE_ADDR_TYPE_RX, offset,
					  buf, len);
पूर्ण
अटल अंतरभूत पूर्णांक snd_dice_transaction_पढ़ो_rx(काष्ठा snd_dice *dice,
					       अचिन्हित पूर्णांक offset,
					       व्योम *buf, अचिन्हित पूर्णांक len)
अणु
	वापस snd_dice_transaction_पढ़ो(dice, SND_DICE_ADDR_TYPE_RX, offset,
					 buf, len);
पूर्ण
अटल अंतरभूत पूर्णांक snd_dice_transaction_ग_लिखो_sync(काष्ठा snd_dice *dice,
						  अचिन्हित पूर्णांक offset,
						  व्योम *buf, अचिन्हित पूर्णांक len)
अणु
	वापस snd_dice_transaction_ग_लिखो(dice, SND_DICE_ADDR_TYPE_SYNC, offset,
					  buf, len);
पूर्ण
अटल अंतरभूत पूर्णांक snd_dice_transaction_पढ़ो_sync(काष्ठा snd_dice *dice,
						 अचिन्हित पूर्णांक offset,
						 व्योम *buf, अचिन्हित पूर्णांक len)
अणु
	वापस snd_dice_transaction_पढ़ो(dice, SND_DICE_ADDR_TYPE_SYNC, offset,
					 buf, len);
पूर्ण

पूर्णांक snd_dice_transaction_get_घड़ी_source(काष्ठा snd_dice *dice,
					  अचिन्हित पूर्णांक *source);
पूर्णांक snd_dice_transaction_get_rate(काष्ठा snd_dice *dice, अचिन्हित पूर्णांक *rate);
पूर्णांक snd_dice_transaction_set_enable(काष्ठा snd_dice *dice);
व्योम snd_dice_transaction_clear_enable(काष्ठा snd_dice *dice);
पूर्णांक snd_dice_transaction_init(काष्ठा snd_dice *dice);
पूर्णांक snd_dice_transaction_reinit(काष्ठा snd_dice *dice);
व्योम snd_dice_transaction_destroy(काष्ठा snd_dice *dice);

#घोषणा SND_DICE_RATES_COUNT	7
बाह्य स्थिर अचिन्हित पूर्णांक snd_dice_rates[SND_DICE_RATES_COUNT];

पूर्णांक snd_dice_stream_get_rate_mode(काष्ठा snd_dice *dice, अचिन्हित पूर्णांक rate,
				  क्रमागत snd_dice_rate_mode *mode);
पूर्णांक snd_dice_stream_start_duplex(काष्ठा snd_dice *dice);
व्योम snd_dice_stream_stop_duplex(काष्ठा snd_dice *dice);
पूर्णांक snd_dice_stream_init_duplex(काष्ठा snd_dice *dice);
व्योम snd_dice_stream_destroy_duplex(काष्ठा snd_dice *dice);
पूर्णांक snd_dice_stream_reserve_duplex(काष्ठा snd_dice *dice, अचिन्हित पूर्णांक rate,
				   अचिन्हित पूर्णांक events_per_period,
				   अचिन्हित पूर्णांक events_per_buffer);
व्योम snd_dice_stream_update_duplex(काष्ठा snd_dice *dice);
पूर्णांक snd_dice_stream_detect_current_क्रमmats(काष्ठा snd_dice *dice);

पूर्णांक snd_dice_stream_lock_try(काष्ठा snd_dice *dice);
व्योम snd_dice_stream_lock_release(काष्ठा snd_dice *dice);

पूर्णांक snd_dice_create_pcm(काष्ठा snd_dice *dice);

पूर्णांक snd_dice_create_hwdep(काष्ठा snd_dice *dice);

व्योम snd_dice_create_proc(काष्ठा snd_dice *dice);

पूर्णांक snd_dice_create_midi(काष्ठा snd_dice *dice);

पूर्णांक snd_dice_detect_tcelectronic_क्रमmats(काष्ठा snd_dice *dice);
पूर्णांक snd_dice_detect_alesis_क्रमmats(काष्ठा snd_dice *dice);
पूर्णांक snd_dice_detect_alesis_mastercontrol_क्रमmats(काष्ठा snd_dice *dice);
पूर्णांक snd_dice_detect_extension_क्रमmats(काष्ठा snd_dice *dice);
पूर्णांक snd_dice_detect_mytek_क्रमmats(काष्ठा snd_dice *dice);
पूर्णांक snd_dice_detect_presonus_क्रमmats(काष्ठा snd_dice *dice);
पूर्णांक snd_dice_detect_harman_क्रमmats(काष्ठा snd_dice *dice);

#पूर्ण_अगर
