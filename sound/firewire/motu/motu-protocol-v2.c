<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * motu-protocol-v2.c - a part of driver क्रम MOTU FireWire series
 *
 * Copyright (c) 2015-2017 Takashi Sakamoto <o-takashi@sakamocchi.jp>
 */

#समावेश "motu.h"

#घोषणा V2_CLOCK_STATUS_OFFSET			0x0b14
#घोषणा  V2_CLOCK_RATE_MASK			0x00000038
#घोषणा  V2_CLOCK_RATE_SHIFT			3
#घोषणा  V2_CLOCK_SRC_MASK			0x00000007
#घोषणा  V2_CLOCK_SRC_SHIFT			0
#घोषणा  V2_CLOCK_FETCH_ENABLE			0x02000000
#घोषणा  V2_CLOCK_MODEL_SPECIFIC		0x04000000

#घोषणा V2_IN_OUT_CONF_OFFSET			0x0c04
#घोषणा  V2_OPT_OUT_IFACE_MASK			0x00000c00
#घोषणा  V2_OPT_OUT_IFACE_SHIFT			10
#घोषणा  V2_OPT_IN_IFACE_MASK			0x00000300
#घोषणा  V2_OPT_IN_IFACE_SHIFT			8
#घोषणा  V2_OPT_IFACE_MODE_NONE			0
#घोषणा  V2_OPT_IFACE_MODE_ADAT			1
#घोषणा  V2_OPT_IFACE_MODE_SPDIF		2

अटल पूर्णांक get_घड़ी_rate(u32 data, अचिन्हित पूर्णांक *rate)
अणु
	अचिन्हित पूर्णांक index = (data & V2_CLOCK_RATE_MASK) >> V2_CLOCK_RATE_SHIFT;
	अगर (index >= ARRAY_SIZE(snd_motu_घड़ी_rates))
		वापस -EIO;

	*rate = snd_motu_घड़ी_rates[index];

	वापस 0;
पूर्ण

पूर्णांक snd_motu_protocol_v2_get_घड़ी_rate(काष्ठा snd_motu *motu,
					अचिन्हित पूर्णांक *rate)
अणु
	__be32 reg;
	पूर्णांक err;

	err = snd_motu_transaction_पढ़ो(motu, V2_CLOCK_STATUS_OFFSET, &reg,
					माप(reg));
	अगर (err < 0)
		वापस err;

	वापस get_घड़ी_rate(be32_to_cpu(reg), rate);
पूर्ण

पूर्णांक snd_motu_protocol_v2_set_घड़ी_rate(काष्ठा snd_motu *motu,
					अचिन्हित पूर्णांक rate)
अणु
	__be32 reg;
	u32 data;
	पूर्णांक i;
	पूर्णांक err;

	क्रम (i = 0; i < ARRAY_SIZE(snd_motu_घड़ी_rates); ++i) अणु
		अगर (snd_motu_घड़ी_rates[i] == rate)
			अवरोध;
	पूर्ण
	अगर (i == ARRAY_SIZE(snd_motu_घड़ी_rates))
		वापस -EINVAL;

	err = snd_motu_transaction_पढ़ो(motu, V2_CLOCK_STATUS_OFFSET, &reg,
					माप(reg));
	अगर (err < 0)
		वापस err;
	data = be32_to_cpu(reg);

	data &= ~V2_CLOCK_RATE_MASK;
	data |= i << V2_CLOCK_RATE_SHIFT;

	reg = cpu_to_be32(data);
	वापस snd_motu_transaction_ग_लिखो(motu, V2_CLOCK_STATUS_OFFSET, &reg,
					  माप(reg));
पूर्ण

अटल पूर्णांक detect_घड़ी_source_optical_model(काष्ठा snd_motu *motu, u32 data,
					     क्रमागत snd_motu_घड़ी_source *src)
अणु
	चयन (data) अणु
	हाल 0:
		*src = SND_MOTU_CLOCK_SOURCE_INTERNAL;
		अवरोध;
	हाल 1:
	अणु
		__be32 reg;

		// To check the configuration of optical पूर्णांकerface.
		पूर्णांक err = snd_motu_transaction_पढ़ो(motu, V2_IN_OUT_CONF_OFFSET,
						    &reg, माप(reg));
		अगर (err < 0)
			वापस err;

		अगर (be32_to_cpu(reg) & 0x00000200)
			*src = SND_MOTU_CLOCK_SOURCE_SPDIF_ON_OPT;
		अन्यथा
			*src = SND_MOTU_CLOCK_SOURCE_ADAT_ON_OPT;
		अवरोध;
	पूर्ण
	हाल 2:
		*src = SND_MOTU_CLOCK_SOURCE_SPDIF_ON_COAX;
		अवरोध;
	हाल 3:
		*src = SND_MOTU_CLOCK_SOURCE_SPH;
		अवरोध;
	हाल 4:
		*src = SND_MOTU_CLOCK_SOURCE_WORD_ON_BNC;
		अवरोध;
	हाल 5:
		*src = SND_MOTU_CLOCK_SOURCE_ADAT_ON_DSUB;
		अवरोध;
	शेष:
		*src = SND_MOTU_CLOCK_SOURCE_UNKNOWN;
		अवरोध;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक v2_detect_घड़ी_source(काष्ठा snd_motu *motu, u32 data,
				  क्रमागत snd_motu_घड़ी_source *src)
अणु
	चयन (data) अणु
	हाल 0:
		*src = SND_MOTU_CLOCK_SOURCE_INTERNAL;
		अवरोध;
	हाल 2:
		*src = SND_MOTU_CLOCK_SOURCE_SPDIF_ON_COAX;
		अवरोध;
	हाल 3:
		*src = SND_MOTU_CLOCK_SOURCE_SPH;
		अवरोध;
	हाल 4:
		*src = SND_MOTU_CLOCK_SOURCE_WORD_ON_BNC;
		अवरोध;
	शेष:
		*src = SND_MOTU_CLOCK_SOURCE_UNKNOWN;
		अवरोध;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक get_घड़ी_source(काष्ठा snd_motu *motu, u32 data,
			    क्रमागत snd_motu_घड़ी_source *src)
अणु
	data &= V2_CLOCK_SRC_MASK;
	अगर (motu->spec == &snd_motu_spec_828mk2 ||
	    motu->spec == &snd_motu_spec_traveler)
		वापस detect_घड़ी_source_optical_model(motu, data, src);
	अन्यथा
		वापस v2_detect_घड़ी_source(motu, data, src);
पूर्ण

पूर्णांक snd_motu_protocol_v2_get_घड़ी_source(काष्ठा snd_motu *motu,
					  क्रमागत snd_motu_घड़ी_source *src)
अणु
	__be32 reg;
	पूर्णांक err;

	err = snd_motu_transaction_पढ़ो(motu, V2_CLOCK_STATUS_OFFSET, &reg,
					माप(reg));
	अगर (err < 0)
		वापस err;

	वापस get_घड़ी_source(motu, be32_to_cpu(reg), src);
पूर्ण

// Expected क्रम Traveler and 896HD, which implements Altera Cyclone EP1C3.
अटल पूर्णांक चयन_fetching_mode_cyclone(काष्ठा snd_motu *motu, u32 *data,
					bool enable)
अणु
	*data |= V2_CLOCK_MODEL_SPECIFIC;

	वापस 0;
पूर्ण

// For UltraLite and 8pre, which implements Xilinx Spartan XC3S200.
अटल पूर्णांक चयन_fetching_mode_spartan(काष्ठा snd_motu *motu, u32 *data,
					bool enable)
अणु
	अचिन्हित पूर्णांक rate;
	क्रमागत snd_motu_घड़ी_source src;
	पूर्णांक err;

	err = get_घड़ी_source(motu, *data, &src);
	अगर (err < 0)
		वापस err;

	err = get_घड़ी_rate(*data, &rate);
	अगर (err < 0)
		वापस err;

	अगर (src == SND_MOTU_CLOCK_SOURCE_SPH && rate > 48000)
		*data |= V2_CLOCK_MODEL_SPECIFIC;

	वापस 0;
पूर्ण

पूर्णांक snd_motu_protocol_v2_चयन_fetching_mode(काष्ठा snd_motu *motu,
					      bool enable)
अणु
	अगर (motu->spec == &snd_motu_spec_828mk2) अणु
		// 828mkII implements Altera ACEX 1K EP1K30. Nothing to करो.
		वापस 0;
	पूर्ण अन्यथा अणु
		__be32 reg;
		u32 data;
		पूर्णांक err;

		err = snd_motu_transaction_पढ़ो(motu, V2_CLOCK_STATUS_OFFSET,
						&reg, माप(reg));
		अगर (err < 0)
			वापस err;
		data = be32_to_cpu(reg);

		data &= ~(V2_CLOCK_FETCH_ENABLE | V2_CLOCK_MODEL_SPECIFIC);
		अगर (enable)
			data |= V2_CLOCK_FETCH_ENABLE;

		अगर (motu->spec == &snd_motu_spec_traveler)
			err = चयन_fetching_mode_cyclone(motu, &data, enable);
		अन्यथा
			err = चयन_fetching_mode_spartan(motu, &data, enable);
		अगर (err < 0)
			वापस err;

		reg = cpu_to_be32(data);
		वापस snd_motu_transaction_ग_लिखो(motu, V2_CLOCK_STATUS_OFFSET,
						  &reg, माप(reg));
	पूर्ण
पूर्ण

अटल पूर्णांक detect_packet_क्रमmats_828mk2(काष्ठा snd_motu *motu, u32 data)
अणु
	अगर (((data & V2_OPT_IN_IFACE_MASK) >> V2_OPT_IN_IFACE_SHIFT) ==
	    V2_OPT_IFACE_MODE_ADAT) अणु
		motu->tx_packet_क्रमmats.pcm_chunks[0] += 8;
		motu->tx_packet_क्रमmats.pcm_chunks[1] += 4;
	पूर्ण

	अगर (((data & V2_OPT_OUT_IFACE_MASK) >> V2_OPT_OUT_IFACE_SHIFT) ==
	    V2_OPT_IFACE_MODE_ADAT) अणु
		motu->rx_packet_क्रमmats.pcm_chunks[0] += 8;
		motu->rx_packet_क्रमmats.pcm_chunks[1] += 4;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक detect_packet_क्रमmats_traveler(काष्ठा snd_motu *motu, u32 data)
अणु
	अगर (((data & V2_OPT_IN_IFACE_MASK) >> V2_OPT_IN_IFACE_SHIFT) ==
	    V2_OPT_IFACE_MODE_ADAT) अणु
		motu->tx_packet_क्रमmats.pcm_chunks[0] += 8;
		motu->tx_packet_क्रमmats.pcm_chunks[1] += 4;
	पूर्ण

	अगर (((data & V2_OPT_OUT_IFACE_MASK) >> V2_OPT_OUT_IFACE_SHIFT) ==
	    V2_OPT_IFACE_MODE_ADAT) अणु
		motu->rx_packet_क्रमmats.pcm_chunks[0] += 8;
		motu->rx_packet_क्रमmats.pcm_chunks[1] += 4;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक detect_packet_क्रमmats_8pre(काष्ठा snd_motu *motu, u32 data)
अणु
	अगर (((data & V2_OPT_IN_IFACE_MASK) >> V2_OPT_IN_IFACE_SHIFT) ==
	    V2_OPT_IFACE_MODE_ADAT) अणु
		motu->tx_packet_क्रमmats.pcm_chunks[0] += 8;
		motu->tx_packet_क्रमmats.pcm_chunks[1] += 8;
	पूर्ण

	अगर (((data & V2_OPT_OUT_IFACE_MASK) >> V2_OPT_OUT_IFACE_SHIFT) ==
	    V2_OPT_IFACE_MODE_ADAT) अणु
		motu->rx_packet_क्रमmats.pcm_chunks[0] += 8;
		motu->rx_packet_क्रमmats.pcm_chunks[1] += 8;
	पूर्ण

	वापस 0;
पूर्ण

पूर्णांक snd_motu_protocol_v2_cache_packet_क्रमmats(काष्ठा snd_motu *motu)
अणु
	__be32 reg;
	u32 data;
	पूर्णांक err;

	motu->tx_packet_क्रमmats.pcm_byte_offset = 10;
	motu->rx_packet_क्रमmats.pcm_byte_offset = 10;

	motu->tx_packet_क्रमmats.msg_chunks = 2;
	motu->rx_packet_क्रमmats.msg_chunks = 2;

	err = snd_motu_transaction_पढ़ो(motu, V2_IN_OUT_CONF_OFFSET, &reg,
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

	अगर (motu->spec == &snd_motu_spec_828mk2)
		वापस detect_packet_क्रमmats_828mk2(motu, data);
	अन्यथा अगर (motu->spec == &snd_motu_spec_traveler)
		वापस detect_packet_क्रमmats_traveler(motu, data);
	अन्यथा अगर (motu->spec == &snd_motu_spec_8pre)
		वापस detect_packet_क्रमmats_8pre(motu, data);
	अन्यथा
		वापस 0;
पूर्ण

स्थिर काष्ठा snd_motu_spec snd_motu_spec_828mk2 = अणु
	.name = "828mk2",
	.protocol_version = SND_MOTU_PROTOCOL_V2,
	.flags = SND_MOTU_SPEC_RX_MIDI_2ND_Q |
		 SND_MOTU_SPEC_TX_MIDI_2ND_Q,
	.tx_fixed_pcm_chunks = अणु14, 14, 0पूर्ण,
	.rx_fixed_pcm_chunks = अणु14, 14, 0पूर्ण,
पूर्ण;

स्थिर काष्ठा snd_motu_spec snd_motu_spec_traveler = अणु
	.name = "Traveler",
	.protocol_version = SND_MOTU_PROTOCOL_V2,
	.flags = SND_MOTU_SPEC_RX_MIDI_2ND_Q |
		 SND_MOTU_SPEC_TX_MIDI_2ND_Q,
	.tx_fixed_pcm_chunks = अणु14, 14, 8पूर्ण,
	.rx_fixed_pcm_chunks = अणु14, 14, 8पूर्ण,
पूर्ण;

स्थिर काष्ठा snd_motu_spec snd_motu_spec_ultralite = अणु
	.name = "UltraLite",
	.protocol_version = SND_MOTU_PROTOCOL_V2,
	.flags = SND_MOTU_SPEC_RX_MIDI_2ND_Q |
		 SND_MOTU_SPEC_TX_MIDI_2ND_Q,
	.tx_fixed_pcm_chunks = अणु14, 14, 0पूर्ण,
	.rx_fixed_pcm_chunks = अणु14, 14, 0पूर्ण,
पूर्ण;

स्थिर काष्ठा snd_motu_spec snd_motu_spec_8pre = अणु
	.name = "8pre",
	.protocol_version = SND_MOTU_PROTOCOL_V2,
	.flags = SND_MOTU_SPEC_RX_MIDI_2ND_Q |
		 SND_MOTU_SPEC_TX_MIDI_2ND_Q,
	.tx_fixed_pcm_chunks = अणु10, 6, 0पूर्ण,
	.rx_fixed_pcm_chunks = अणु10, 6, 0पूर्ण,
पूर्ण;
