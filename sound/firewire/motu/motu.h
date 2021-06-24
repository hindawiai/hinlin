<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * motu.h - a part of driver क्रम MOTU FireWire series
 *
 * Copyright (c) 2015-2017 Takashi Sakamoto <o-takashi@sakamocchi.jp>
 */

#अगर_अघोषित SOUND_FIREWIRE_MOTU_H_INCLUDED
#घोषणा SOUND_FIREWIRE_MOTU_H_INCLUDED

#समावेश <linux/device.h>
#समावेश <linux/firewire.h>
#समावेश <linux/firewire-स्थिरants.h>
#समावेश <linux/module.h>
#समावेश <linux/mod_devicetable.h>
#समावेश <linux/mutex.h>
#समावेश <linux/slab.h>
#समावेश <linux/compat.h>
#समावेश <linux/sched/संकेत.स>

#समावेश <sound/control.h>
#समावेश <sound/core.h>
#समावेश <sound/pcm.h>
#समावेश <sound/info.h>
#समावेश <sound/rawmidi.h>
#समावेश <sound/firewire.h>
#समावेश <sound/hwdep.h>

#समावेश "../lib.h"
#समावेश "../amdtp-stream.h"
#समावेश "../iso-resources.h"

काष्ठा snd_motu_packet_क्रमmat अणु
	अचिन्हित अक्षर midi_flag_offset;
	अचिन्हित अक्षर midi_byte_offset;
	अचिन्हित अक्षर pcm_byte_offset;

	अचिन्हित अक्षर msg_chunks;
	अचिन्हित अक्षर pcm_chunks[3];
पूर्ण;

काष्ठा snd_motu अणु
	काष्ठा snd_card *card;
	काष्ठा fw_unit *unit;
	काष्ठा mutex mutex;
	spinlock_t lock;

	bool रेजिस्टरed;
	काष्ठा delayed_work dwork;

	/* Model dependent inक्रमmation. */
	स्थिर काष्ठा snd_motu_spec *spec;

	/* For packet streaming */
	काष्ठा snd_motu_packet_क्रमmat tx_packet_क्रमmats;
	काष्ठा snd_motu_packet_क्रमmat rx_packet_क्रमmats;
	काष्ठा amdtp_stream tx_stream;
	काष्ठा amdtp_stream rx_stream;
	काष्ठा fw_iso_resources tx_resources;
	काष्ठा fw_iso_resources rx_resources;
	अचिन्हित पूर्णांक substreams_counter;

	/* For notअगरication. */
	काष्ठा fw_address_handler async_handler;
	u32 msg;

	/* For uapi */
	पूर्णांक dev_lock_count;
	bool dev_lock_changed;
	रुको_queue_head_t hwdep_रुको;

	काष्ठा amdtp_करोमुख्य करोमुख्य;
पूर्ण;

क्रमागत snd_motu_spec_flags अणु
	SND_MOTU_SPEC_RX_MIDI_2ND_Q	= 0x0001,
	SND_MOTU_SPEC_RX_MIDI_3RD_Q	= 0x0002,
	SND_MOTU_SPEC_TX_MIDI_2ND_Q	= 0x0004,
	SND_MOTU_SPEC_TX_MIDI_3RD_Q	= 0x0008,
पूर्ण;

#घोषणा SND_MOTU_CLOCK_RATE_COUNT	6
बाह्य स्थिर अचिन्हित पूर्णांक snd_motu_घड़ी_rates[SND_MOTU_CLOCK_RATE_COUNT];

क्रमागत snd_motu_घड़ी_source अणु
	SND_MOTU_CLOCK_SOURCE_INTERNAL,
	SND_MOTU_CLOCK_SOURCE_ADAT_ON_DSUB,
	SND_MOTU_CLOCK_SOURCE_ADAT_ON_OPT,
	SND_MOTU_CLOCK_SOURCE_ADAT_ON_OPT_A,
	SND_MOTU_CLOCK_SOURCE_ADAT_ON_OPT_B,
	SND_MOTU_CLOCK_SOURCE_SPDIF_ON_OPT,
	SND_MOTU_CLOCK_SOURCE_SPDIF_ON_OPT_A,
	SND_MOTU_CLOCK_SOURCE_SPDIF_ON_OPT_B,
	SND_MOTU_CLOCK_SOURCE_SPDIF_ON_COAX,
	SND_MOTU_CLOCK_SOURCE_AESEBU_ON_XLR,
	SND_MOTU_CLOCK_SOURCE_WORD_ON_BNC,
	SND_MOTU_CLOCK_SOURCE_SPH,
	SND_MOTU_CLOCK_SOURCE_UNKNOWN,
पूर्ण;

क्रमागत snd_motu_protocol_version अणु
	SND_MOTU_PROTOCOL_V2,
	SND_MOTU_PROTOCOL_V3,
पूर्ण;

काष्ठा snd_motu_spec अणु
	स्थिर अक्षर *स्थिर name;
	क्रमागत snd_motu_protocol_version protocol_version;
	क्रमागत snd_motu_spec_flags flags;

	अचिन्हित अक्षर tx_fixed_pcm_chunks[3];
	अचिन्हित अक्षर rx_fixed_pcm_chunks[3];
पूर्ण;

बाह्य स्थिर काष्ठा snd_motu_spec snd_motu_spec_828mk2;
बाह्य स्थिर काष्ठा snd_motu_spec snd_motu_spec_traveler;
बाह्य स्थिर काष्ठा snd_motu_spec snd_motu_spec_ultralite;
बाह्य स्थिर काष्ठा snd_motu_spec snd_motu_spec_8pre;

बाह्य स्थिर काष्ठा snd_motu_spec snd_motu_spec_828mk3;
बाह्य स्थिर काष्ठा snd_motu_spec snd_motu_spec_ultralite_mk3;
बाह्य स्थिर काष्ठा snd_motu_spec snd_motu_spec_audio_express;
बाह्य स्थिर काष्ठा snd_motu_spec snd_motu_spec_4pre;

पूर्णांक amdtp_motu_init(काष्ठा amdtp_stream *s, काष्ठा fw_unit *unit,
		    क्रमागत amdtp_stream_direction dir,
		    स्थिर काष्ठा snd_motu_spec *spec);
पूर्णांक amdtp_motu_set_parameters(काष्ठा amdtp_stream *s, अचिन्हित पूर्णांक rate,
			      अचिन्हित पूर्णांक midi_ports,
			      काष्ठा snd_motu_packet_क्रमmat *क्रमmats);
पूर्णांक amdtp_motu_add_pcm_hw_स्थिरraपूर्णांकs(काष्ठा amdtp_stream *s,
				      काष्ठा snd_pcm_runसमय *runसमय);
व्योम amdtp_motu_midi_trigger(काष्ठा amdtp_stream *s, अचिन्हित पूर्णांक port,
			     काष्ठा snd_rawmidi_substream *midi);

पूर्णांक snd_motu_transaction_पढ़ो(काष्ठा snd_motu *motu, u32 offset, __be32 *reg,
			      माप_प्रकार size);
पूर्णांक snd_motu_transaction_ग_लिखो(काष्ठा snd_motu *motu, u32 offset, __be32 *reg,
			       माप_प्रकार size);
पूर्णांक snd_motu_transaction_रेजिस्टर(काष्ठा snd_motu *motu);
पूर्णांक snd_motu_transaction_reरेजिस्टर(काष्ठा snd_motu *motu);
व्योम snd_motu_transaction_unरेजिस्टर(काष्ठा snd_motu *motu);

पूर्णांक snd_motu_stream_init_duplex(काष्ठा snd_motu *motu);
व्योम snd_motu_stream_destroy_duplex(काष्ठा snd_motu *motu);
पूर्णांक snd_motu_stream_cache_packet_क्रमmats(काष्ठा snd_motu *motu);
पूर्णांक snd_motu_stream_reserve_duplex(काष्ठा snd_motu *motu, अचिन्हित पूर्णांक rate,
				   अचिन्हित पूर्णांक frames_per_period,
				   अचिन्हित पूर्णांक frames_per_buffer);
पूर्णांक snd_motu_stream_start_duplex(काष्ठा snd_motu *motu);
व्योम snd_motu_stream_stop_duplex(काष्ठा snd_motu *motu);
पूर्णांक snd_motu_stream_lock_try(काष्ठा snd_motu *motu);
व्योम snd_motu_stream_lock_release(काष्ठा snd_motu *motu);

व्योम snd_motu_proc_init(काष्ठा snd_motu *motu);

पूर्णांक snd_motu_create_pcm_devices(काष्ठा snd_motu *motu);

पूर्णांक snd_motu_create_midi_devices(काष्ठा snd_motu *motu);

पूर्णांक snd_motu_create_hwdep_device(काष्ठा snd_motu *motu);

पूर्णांक snd_motu_protocol_v2_get_घड़ी_rate(काष्ठा snd_motu *motu,
					अचिन्हित पूर्णांक *rate);
पूर्णांक snd_motu_protocol_v2_set_घड़ी_rate(काष्ठा snd_motu *motu,
					अचिन्हित पूर्णांक rate);
पूर्णांक snd_motu_protocol_v2_get_घड़ी_source(काष्ठा snd_motu *motu,
					  क्रमागत snd_motu_घड़ी_source *src);
पूर्णांक snd_motu_protocol_v2_चयन_fetching_mode(काष्ठा snd_motu *motu,
					      bool enable);
पूर्णांक snd_motu_protocol_v2_cache_packet_क्रमmats(काष्ठा snd_motu *motu);

पूर्णांक snd_motu_protocol_v3_get_घड़ी_rate(काष्ठा snd_motu *motu,
					अचिन्हित पूर्णांक *rate);
पूर्णांक snd_motu_protocol_v3_set_घड़ी_rate(काष्ठा snd_motu *motu,
					अचिन्हित पूर्णांक rate);
पूर्णांक snd_motu_protocol_v3_get_घड़ी_source(काष्ठा snd_motu *motu,
					  क्रमागत snd_motu_घड़ी_source *src);
पूर्णांक snd_motu_protocol_v3_चयन_fetching_mode(काष्ठा snd_motu *motu,
					      bool enable);
पूर्णांक snd_motu_protocol_v3_cache_packet_क्रमmats(काष्ठा snd_motu *motu);

अटल अंतरभूत पूर्णांक snd_motu_protocol_get_घड़ी_rate(काष्ठा snd_motu *motu,
						   अचिन्हित पूर्णांक *rate)
अणु
	अगर (motu->spec->protocol_version == SND_MOTU_PROTOCOL_V2)
		वापस snd_motu_protocol_v2_get_घड़ी_rate(motu, rate);
	अन्यथा अगर (motu->spec->protocol_version == SND_MOTU_PROTOCOL_V3)
		वापस snd_motu_protocol_v3_get_घड़ी_rate(motu, rate);
	अन्यथा
		वापस -ENXIO;
पूर्ण

अटल अंतरभूत पूर्णांक snd_motu_protocol_set_घड़ी_rate(काष्ठा snd_motu *motu,
						   अचिन्हित पूर्णांक rate)
अणु
	अगर (motu->spec->protocol_version == SND_MOTU_PROTOCOL_V2)
		वापस snd_motu_protocol_v2_set_घड़ी_rate(motu, rate);
	अन्यथा अगर (motu->spec->protocol_version == SND_MOTU_PROTOCOL_V3)
		वापस snd_motu_protocol_v3_set_घड़ी_rate(motu, rate);
	अन्यथा
		वापस -ENXIO;
पूर्ण

अटल अंतरभूत पूर्णांक snd_motu_protocol_get_घड़ी_source(काष्ठा snd_motu *motu,
					क्रमागत snd_motu_घड़ी_source *source)
अणु
	अगर (motu->spec->protocol_version == SND_MOTU_PROTOCOL_V2)
		वापस snd_motu_protocol_v2_get_घड़ी_source(motu, source);
	अन्यथा अगर (motu->spec->protocol_version == SND_MOTU_PROTOCOL_V3)
		वापस snd_motu_protocol_v3_get_घड़ी_source(motu, source);
	अन्यथा
		वापस -ENXIO;
पूर्ण

अटल अंतरभूत पूर्णांक snd_motu_protocol_चयन_fetching_mode(काष्ठा snd_motu *motu,
							 bool enable)
अणु
	अगर (motu->spec->protocol_version == SND_MOTU_PROTOCOL_V2)
		वापस snd_motu_protocol_v2_चयन_fetching_mode(motu, enable);
	अन्यथा अगर (motu->spec->protocol_version == SND_MOTU_PROTOCOL_V3)
		वापस snd_motu_protocol_v3_चयन_fetching_mode(motu, enable);
	अन्यथा
		वापस -ENXIO;
पूर्ण

अटल अंतरभूत पूर्णांक snd_motu_protocol_cache_packet_क्रमmats(काष्ठा snd_motu *motu)
अणु
	अगर (motu->spec->protocol_version == SND_MOTU_PROTOCOL_V2)
		वापस snd_motu_protocol_v2_cache_packet_क्रमmats(motu);
	अन्यथा अगर (motu->spec->protocol_version == SND_MOTU_PROTOCOL_V3)
		वापस snd_motu_protocol_v3_cache_packet_क्रमmats(motu);
	अन्यथा
		वापस -ENXIO;
पूर्ण

#पूर्ण_अगर
