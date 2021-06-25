<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * motu-protocol-v3.c - a part of driver क्रम MOTU FireWire series
 *
 * Copyright (c) 2015-2017 Takashi Sakamoto <o-takashi@sakamocchi.jp>
 */

#समावेश <linux/delay.h>
#समावेश "motu.h"

#घोषणा V3_CLOCK_STATUS_OFFSET		0x0b14
#घोषणा  V3_FETCH_PCM_FRAMES		0x02000000
#घोषणा  V3_CLOCK_RATE_MASK		0x0000ff00
#घोषणा  V3_CLOCK_RATE_SHIFT		8
#घोषणा  V3_CLOCK_SOURCE_MASK		0x000000ff

#घोषणा V3_OPT_IFACE_MODE_OFFSET	0x0c94
#घोषणा  V3_ENABLE_OPT_IN_IFACE_A	0x00000001
#घोषणा  V3_ENABLE_OPT_IN_IFACE_B	0x00000002
#घोषणा  V3_ENABLE_OPT_OUT_IFACE_A	0x00000100
#घोषणा  V3_ENABLE_OPT_OUT_IFACE_B	0x00000200
#घोषणा  V3_NO_ADAT_OPT_IN_IFACE_A	0x00010000
#घोषणा  V3_NO_ADAT_OPT_IN_IFACE_B	0x00100000
#घोषणा  V3_NO_ADAT_OPT_OUT_IFACE_A	0x00040000
#घोषणा  V3_NO_ADAT_OPT_OUT_IFACE_B	0x00400000

#घोषणा V3_MSG_FLAG_CLK_CHANGED		0x00000002
#घोषणा V3_CLK_WAIT_MSEC		4000

पूर्णांक snd_motu_protocol_v3_get_घड़ी_rate(काष्ठा snd_motu *motu,
					अचिन्हित पूर्णांक *rate)
अणु
	__be32 reg;
	u32 data;
	पूर्णांक err;

	err = snd_motu_transaction_पढ़ो(motu, V3_CLOCK_STATUS_OFFSET, &reg,
					माप(reg));
	अगर (err < 0)
		वापस err;
	data = be32_to_cpu(reg);

	data = (data & V3_CLOCK_RATE_MASK) >> V3_CLOCK_RATE_SHIFT;
	अगर (data >= ARRAY_SIZE(snd_motu_घड़ी_rates))
		वापस -EIO;

	*rate = snd_motu_घड़ी_rates[data];

	वापस 0;
पूर्ण

पूर्णांक snd_motu_protocol_v3_set_घड़ी_rate(काष्ठा snd_motu *motu,
					अचिन्हित पूर्णांक rate)
अणु
	__be32 reg;
	u32 data;
	bool need_to_रुको;
	पूर्णांक i, err;

	क्रम (i = 0; i < ARRAY_SIZE(snd_motu_घड़ी_rates); ++i) अणु
		अगर (snd_motu_घड़ी_rates[i] == rate)
			अवरोध;
	पूर्ण
	अगर (i == ARRAY_SIZE(snd_motu_घड़ी_rates))
		वापस -EINVAL;

	err = snd_motu_transaction_पढ़ो(motu, V3_CLOCK_STATUS_OFFSET, &reg,
					माप(reg));
	अगर (err < 0)
		वापस err;
	data = be32_to_cpu(reg);

	data &= ~(V3_CLOCK_RATE_MASK | V3_FETCH_PCM_FRAMES);
	data |= i << V3_CLOCK_RATE_SHIFT;

	need_to_रुको = data != be32_to_cpu(reg);

	reg = cpu_to_be32(data);
	err = snd_motu_transaction_ग_लिखो(motu, V3_CLOCK_STATUS_OFFSET, &reg,
					 माप(reg));
	अगर (err < 0)
		वापस err;

	अगर (need_to_रुको) अणु
		पूर्णांक result;

		motu->msg = 0;
		result = रुको_event_पूर्णांकerruptible_समयout(motu->hwdep_रुको,
					motu->msg & V3_MSG_FLAG_CLK_CHANGED,
					msecs_to_jअगरfies(V3_CLK_WAIT_MSEC));
		अगर (result < 0)
			वापस result;
		अगर (result == 0)
			वापस -ETIMEDOUT;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक detect_घड़ी_source_828mk3(काष्ठा snd_motu *motu, u32 data,
				      क्रमागत snd_motu_घड़ी_source *src)
अणु
	चयन (data) अणु
	हाल 0x00:
		*src = SND_MOTU_CLOCK_SOURCE_INTERNAL;
		अवरोध;
	हाल 0x01:
		*src = SND_MOTU_CLOCK_SOURCE_WORD_ON_BNC;
		अवरोध;
	हाल 0x02:
		*src = SND_MOTU_CLOCK_SOURCE_SPH;
		अवरोध;
	हाल 0x10:
		*src = SND_MOTU_CLOCK_SOURCE_SPDIF_ON_COAX;
		अवरोध;
	हाल 0x18:
	हाल 0x19:
	अणु
		__be32 reg;
		u32 options;
		पूर्णांक err;

		err = snd_motu_transaction_पढ़ो(motu,
				V3_OPT_IFACE_MODE_OFFSET, &reg, माप(reg));
		अगर (err < 0)
			वापस err;
		options = be32_to_cpu(reg);

		अगर (data == 0x18) अणु
			अगर (options & V3_NO_ADAT_OPT_IN_IFACE_A)
				*src = SND_MOTU_CLOCK_SOURCE_SPDIF_ON_OPT_A;
			अन्यथा
				*src = SND_MOTU_CLOCK_SOURCE_ADAT_ON_OPT_A;
		पूर्ण अन्यथा अणु
			अगर (options & V3_NO_ADAT_OPT_IN_IFACE_B)
				*src = SND_MOTU_CLOCK_SOURCE_SPDIF_ON_OPT_B;
			अन्यथा
				*src = SND_MOTU_CLOCK_SOURCE_ADAT_ON_OPT_B;
		पूर्ण

		अवरोध;
	पूर्ण
	शेष:
		*src = SND_MOTU_CLOCK_SOURCE_UNKNOWN;
		अवरोध;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक v3_detect_घड़ी_source(काष्ठा snd_motu *motu, u32 data,
				  क्रमागत snd_motu_घड़ी_source *src)
अणु
	चयन (data) अणु
	हाल 0x00:
		*src = SND_MOTU_CLOCK_SOURCE_INTERNAL;
		अवरोध;
	हाल 0x01:
		*src = SND_MOTU_CLOCK_SOURCE_WORD_ON_BNC;
		अवरोध;
	हाल 0x02:
		*src = SND_MOTU_CLOCK_SOURCE_SPH;
		अवरोध;
	हाल 0x10:
		*src = SND_MOTU_CLOCK_SOURCE_SPDIF_ON_COAX;
		अवरोध;
	शेष:
		*src = SND_MOTU_CLOCK_SOURCE_UNKNOWN;
		अवरोध;
	पूर्ण

	वापस 0;
पूर्ण

पूर्णांक snd_motu_protocol_v3_get_घड़ी_source(काष्ठा snd_motu *motu,
					  क्रमागत snd_motu_घड़ी_source *src)
अणु
	__be32 reg;
	u32 data;
	पूर्णांक err;

	err = snd_motu_transaction_पढ़ो(motu, V3_CLOCK_STATUS_OFFSET, &reg,
					माप(reg));
	अगर (err < 0)
		वापस err;
	data = be32_to_cpu(reg) & V3_CLOCK_SOURCE_MASK;

	अगर (motu->spec == &snd_motu_spec_828mk3)
		वापस detect_घड़ी_source_828mk3(motu, data, src);
	अन्यथा
		वापस v3_detect_घड़ी_source(motu, data, src);
पूर्ण

पूर्णांक snd_motu_protocol_v3_चयन_fetching_mode(काष्ठा snd_motu *motu,
					      bool enable)
अणु
	__be32 reg;
	u32 data;
	पूर्णांक err;

	err = snd_motu_transaction_पढ़ो(motu, V3_CLOCK_STATUS_OFFSET, &reg,
					माप(reg));
	अगर (err < 0)
		वापस 0;
	data = be32_to_cpu(reg);

	अगर (enable)
		data |= V3_FETCH_PCM_FRAMES;
	अन्यथा
		data &= ~V3_FETCH_PCM_FRAMES;

	reg = cpu_to_be32(data);
	वापस snd_motu_transaction_ग_लिखो(motu, V3_CLOCK_STATUS_OFFSET, &reg,
					  माप(reg));
पूर्ण

अटल पूर्णांक detect_packet_क्रमmats_828mk3(काष्ठा snd_motu *motu, u32 data)
अणु
	अगर (data & V3_ENABLE_OPT_IN_IFACE_A) अणु
		अगर (data & V3_NO_ADAT_OPT_IN_IFACE_A) अणु
			motu->tx_packet_क्रमmats.pcm_chunks[0] += 4;
			motu->tx_packet_क्रमmats.pcm_chunks[1] += 4;
		पूर्ण अन्यथा अणु
			motu->tx_packet_क्रमmats.pcm_chunks[0] += 8;
			motu->tx_packet_क्रमmats.pcm_chunks[1] += 4;
		पूर्ण
	पूर्ण

	अगर (data & V3_ENABLE_OPT_IN_IFACE_B) अणु
		अगर (data & V3_NO_ADAT_OPT_IN_IFACE_B) अणु
			motu->tx_packet_क्रमmats.pcm_chunks[0] += 4;
			motu->tx_packet_क्रमmats.pcm_chunks[1] += 4;
		पूर्ण अन्यथा अणु
			motu->tx_packet_क्रमmats.pcm_chunks[0] += 8;
			motu->tx_packet_क्रमmats.pcm_chunks[1] += 4;
		पूर्ण
	पूर्ण

	अगर (data & V3_ENABLE_OPT_OUT_IFACE_A) अणु
		अगर (data & V3_NO_ADAT_OPT_OUT_IFACE_A) अणु
			motu->rx_packet_क्रमmats.pcm_chunks[0] += 4;
			motu->rx_packet_क्रमmats.pcm_chunks[1] += 4;
		पूर्ण अन्यथा अणु
			motu->rx_packet_क्रमmats.pcm_chunks[0] += 8;
			motu->rx_packet_क्रमmats.pcm_chunks[1] += 4;
		पूर्ण
	पूर्ण

	अगर (data & V3_ENABLE_OPT_OUT_IFACE_B) अणु
		अगर (data & V3_NO_ADAT_OPT_OUT_IFACE_B) अणु
			motu->rx_packet_क्रमmats.pcm_chunks[0] += 4;
			motu->rx_packet_क्रमmats.pcm_chunks[1] += 4;
		पूर्ण अन्यथा अणु
			motu->rx_packet_क्रमmats.pcm_chunks[0] += 8;
			motu->rx_packet_क्रमmats.pcm_chunks[1] += 4;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

पूर्णांक snd_motu_protocol_v3_cache_packet_क्रमmats(काष्ठा snd_motu *motu)
अणु
	__be32 reg;
	u32 data;
	पूर्णांक err;

	motu->tx_packet_क्रमmats.pcm_byte_offset = 10;
	motu->rx_packet_क्रमmats.pcm_byte_offset = 10;

	motu->tx_packet_क्रमmats.msg_chunks = 2;
	motu->rx_packet_क्रमmats.msg_chunks = 2;

	err = snd_motu_transaction_पढ़ो(motu, V3_OPT_IFACE_MODE_OFFSET, &reg,
					माप(reg));
	अगर (err < 0)
		वापस err;
	data = be32_to_cpu(reg);

	स_नकल(motu->tx_packet_क्रमmats.pcm_chunks,
	       motu->spec->tx_fixed_pcm_chunks,
	       माप(motu->tx_packet_क्रमmats.pcm_chunks));
	स_नकल(motu->rx_packet_क्रमmats.pcm_chunks,
	       motu->spec->rx_fixed_pcm_chunks,
	       माप(motu->rx_packet_क्रमmats.pcm_chunks));

	अगर (motu->spec == &snd_motu_spec_828mk3)
		वापस detect_packet_क्रमmats_828mk3(motu, data);
	अन्यथा
		वापस 0;
पूर्ण


स्थिर काष्ठा snd_motu_spec snd_motu_spec_828mk3 = अणु
	.name = "828mk3",
	.protocol_version = SND_MOTU_PROTOCOL_V3,
	.flags = SND_MOTU_SPEC_RX_MIDI_3RD_Q |
		 SND_MOTU_SPEC_TX_MIDI_3RD_Q,
	.tx_fixed_pcm_chunks = अणु18, 18, 14पूर्ण,
	.rx_fixed_pcm_chunks = अणु14, 14, 10पूर्ण,
पूर्ण;

स्थिर काष्ठा snd_motu_spec snd_motu_spec_ultralite_mk3 = अणु
	.name = "UltraLiteMk3",
	.protocol_version = SND_MOTU_PROTOCOL_V3,
	.flags = SND_MOTU_SPEC_RX_MIDI_3RD_Q |
		 SND_MOTU_SPEC_TX_MIDI_3RD_Q,
	.tx_fixed_pcm_chunks = अणु18, 14, 10पूर्ण,
	.rx_fixed_pcm_chunks = अणु14, 14, 14पूर्ण,
पूर्ण;

स्थिर काष्ठा snd_motu_spec snd_motu_spec_audio_express = अणु
	.name = "AudioExpress",
	.protocol_version = SND_MOTU_PROTOCOL_V3,
	.flags = SND_MOTU_SPEC_RX_MIDI_2ND_Q |
		 SND_MOTU_SPEC_TX_MIDI_3RD_Q,
	.tx_fixed_pcm_chunks = अणु10, 10, 0पूर्ण,
	.rx_fixed_pcm_chunks = अणु10, 10, 0पूर्ण,
पूर्ण;

स्थिर काष्ठा snd_motu_spec snd_motu_spec_4pre = अणु
	.name = "4pre",
	.protocol_version = SND_MOTU_PROTOCOL_V3,
	.tx_fixed_pcm_chunks = अणु10, 10, 0पूर्ण,
	.rx_fixed_pcm_chunks = अणु10, 10, 0पूर्ण,
पूर्ण;
