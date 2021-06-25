<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
// ff-protocol-क्रमmer.c - a part of driver क्रम RME Fireface series
//
// Copyright (c) 2019 Takashi Sakamoto
//
// Licensed under the terms of the GNU General Public License, version 2.

#समावेश <linux/delay.h>

#समावेश "ff.h"

#घोषणा FORMER_REG_SYNC_STATUS		0x0000801c0000ull
/* For block ग_लिखो request. */
#घोषणा FORMER_REG_FETCH_PCM_FRAMES	0x0000801c0000ull
#घोषणा FORMER_REG_CLOCK_CONFIG		0x0000801c0004ull

अटल पूर्णांक parse_घड़ी_bits(u32 data, अचिन्हित पूर्णांक *rate,
			    क्रमागत snd_ff_घड़ी_src *src)
अणु
	अटल स्थिर काष्ठा अणु
		अचिन्हित पूर्णांक rate;
		u32 mask;
	पूर्ण *rate_entry, rate_entries[] = अणु
		अणु  32000, 0x00000002, पूर्ण,
		अणु  44100, 0x00000000, पूर्ण,
		अणु  48000, 0x00000006, पूर्ण,
		अणु  64000, 0x0000000a, पूर्ण,
		अणु  88200, 0x00000008, पूर्ण,
		अणु  96000, 0x0000000e, पूर्ण,
		अणु 128000, 0x00000012, पूर्ण,
		अणु 176400, 0x00000010, पूर्ण,
		अणु 192000, 0x00000016, पूर्ण,
	पूर्ण;
	अटल स्थिर काष्ठा अणु
		क्रमागत snd_ff_घड़ी_src src;
		u32 mask;
	पूर्ण *clk_entry, clk_entries[] = अणु
		अणु SND_FF_CLOCK_SRC_ADAT1,	0x00000000, पूर्ण,
		अणु SND_FF_CLOCK_SRC_ADAT2,	0x00000400, पूर्ण,
		अणु SND_FF_CLOCK_SRC_SPDIF,	0x00000c00, पूर्ण,
		अणु SND_FF_CLOCK_SRC_WORD,	0x00001000, पूर्ण,
		अणु SND_FF_CLOCK_SRC_LTC,		0x00001800, पूर्ण,
	पूर्ण;
	पूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(rate_entries); ++i) अणु
		rate_entry = rate_entries + i;
		अगर ((data & 0x0000001e) == rate_entry->mask) अणु
			*rate = rate_entry->rate;
			अवरोध;
		पूर्ण
	पूर्ण
	अगर (i == ARRAY_SIZE(rate_entries))
		वापस -EIO;

	अगर (data & 0x00000001) अणु
		*src = SND_FF_CLOCK_SRC_INTERNAL;
	पूर्ण अन्यथा अणु
		क्रम (i = 0; i < ARRAY_SIZE(clk_entries); ++i) अणु
			clk_entry = clk_entries + i;
			अगर ((data & 0x00001c00) == clk_entry->mask) अणु
				*src = clk_entry->src;
				अवरोध;
			पूर्ण
		पूर्ण
		अगर (i == ARRAY_SIZE(clk_entries))
			वापस -EIO;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक क्रमmer_get_घड़ी(काष्ठा snd_ff *ff, अचिन्हित पूर्णांक *rate,
			    क्रमागत snd_ff_घड़ी_src *src)
अणु
	__le32 reg;
	u32 data;
	पूर्णांक err;

	err = snd_fw_transaction(ff->unit, TCODE_READ_QUADLET_REQUEST,
				 FORMER_REG_CLOCK_CONFIG, &reg, माप(reg), 0);
	अगर (err < 0)
		वापस err;
	data = le32_to_cpu(reg);

	वापस parse_घड़ी_bits(data, rate, src);
पूर्ण

अटल पूर्णांक क्रमmer_चयन_fetching_mode(काष्ठा snd_ff *ff, bool enable)
अणु
	अचिन्हित पूर्णांक count;
	__le32 *reg;
	पूर्णांक i;
	पूर्णांक err;

	count = 0;
	क्रम (i = 0; i < SND_FF_STREAM_MODE_COUNT; ++i)
		count = max(count, ff->spec->pcm_playback_channels[i]);

	reg = kसुस्मृति(count, माप(__le32), GFP_KERNEL);
	अगर (!reg)
		वापस -ENOMEM;

	अगर (!enable) अणु
		/*
		 * Each quadlet is corresponding to data channels in a data
		 * blocks in reverse order. Precisely, quadlets क्रम available
		 * data channels should be enabled. Here, I take second best
		 * to fetch PCM frames from all of data channels regardless of
		 * stf.
		 */
		क्रम (i = 0; i < count; ++i)
			reg[i] = cpu_to_le32(0x00000001);
	पूर्ण

	err = snd_fw_transaction(ff->unit, TCODE_WRITE_BLOCK_REQUEST,
				 FORMER_REG_FETCH_PCM_FRAMES, reg,
				 माप(__le32) * count, 0);
	kमुक्त(reg);
	वापस err;
पूर्ण

अटल व्योम dump_घड़ी_config(काष्ठा snd_ff *ff, काष्ठा snd_info_buffer *buffer)
अणु
	__le32 reg;
	u32 data;
	अचिन्हित पूर्णांक rate;
	क्रमागत snd_ff_घड़ी_src src;
	स्थिर अक्षर *label;
	पूर्णांक err;

	err = snd_fw_transaction(ff->unit, TCODE_READ_BLOCK_REQUEST,
				 FORMER_REG_CLOCK_CONFIG, &reg, माप(reg), 0);
	अगर (err < 0)
		वापस;
	data = le32_to_cpu(reg);

	snd_iम_लिखो(buffer, "Output S/PDIF format: %s (Emphasis: %s)\n",
		    (data & 0x00000020) ? "Professional" : "Consumer",
		    (data & 0x00000040) ? "on" : "off");

	snd_iम_लिखो(buffer, "Optical output interface format: %s\n",
		    (data & 0x00000100) ? "S/PDIF" : "ADAT");

	snd_iम_लिखो(buffer, "Word output single speed: %s\n",
		    (data & 0x00002000) ? "on" : "off");

	snd_iम_लिखो(buffer, "S/PDIF input interface: %s\n",
		    (data & 0x00000200) ? "Optical" : "Coaxial");

	err = parse_घड़ी_bits(data, &rate, &src);
	अगर (err < 0)
		वापस;
	label = snd_ff_proc_get_clk_label(src);
	अगर (!label)
		वापस;

	snd_iम_लिखो(buffer, "Clock configuration: %d %s\n", rate, label);
पूर्ण

अटल व्योम dump_sync_status(काष्ठा snd_ff *ff, काष्ठा snd_info_buffer *buffer)
अणु
	अटल स्थिर काष्ठा अणु
		अक्षर *स्थिर label;
		u32 locked_mask;
		u32 synced_mask;
	पूर्ण *clk_entry, clk_entries[] = अणु
		अणु "WDClk",	0x40000000, 0x20000000, पूर्ण,
		अणु "S/PDIF",	0x00080000, 0x00040000, पूर्ण,
		अणु "ADAT1",	0x00000400, 0x00001000, पूर्ण,
		अणु "ADAT2",	0x00000800, 0x00002000, पूर्ण,
	पूर्ण;
	अटल स्थिर काष्ठा अणु
		अक्षर *स्थिर label;
		u32 mask;
	पूर्ण *referred_entry, referred_entries[] = अणु
		अणु "ADAT1",	0x00000000, पूर्ण,
		अणु "ADAT2",	0x00400000, पूर्ण,
		अणु "S/PDIF",	0x00c00000, पूर्ण,
		अणु "WDclk",	0x01000000, पूर्ण,
		अणु "TCO",	0x01400000, पूर्ण,
	पूर्ण;
	अटल स्थिर काष्ठा अणु
		अचिन्हित पूर्णांक rate;
		u32 mask;
	पूर्ण *rate_entry, rate_entries[] = अणु
		अणु 32000,	0x02000000, पूर्ण,
		अणु 44100,	0x04000000, पूर्ण,
		अणु 48000,	0x06000000, पूर्ण,
		अणु 64000,	0x08000000, पूर्ण,
		अणु 88200,	0x0a000000, पूर्ण,
		अणु 96000,	0x0c000000, पूर्ण,
		अणु 128000,	0x0e000000, पूर्ण,
		अणु 176400,	0x10000000, पूर्ण,
		अणु 192000,	0x12000000, पूर्ण,
	पूर्ण;
	__le32 reg[2];
	u32 data[2];
	पूर्णांक i;
	पूर्णांक err;

	err = snd_fw_transaction(ff->unit, TCODE_READ_BLOCK_REQUEST,
				 FORMER_REG_SYNC_STATUS, reg, माप(reg), 0);
	अगर (err < 0)
		वापस;
	data[0] = le32_to_cpu(reg[0]);
	data[1] = le32_to_cpu(reg[1]);

	snd_iम_लिखो(buffer, "External source detection:\n");

	क्रम (i = 0; i < ARRAY_SIZE(clk_entries); ++i) अणु
		स्थिर अक्षर *state;

		clk_entry = clk_entries + i;
		अगर (data[0] & clk_entry->locked_mask) अणु
			अगर (data[0] & clk_entry->synced_mask)
				state = "sync";
			अन्यथा
				state = "lock";
		पूर्ण अन्यथा अणु
			state = "none";
		पूर्ण

		snd_iम_लिखो(buffer, "%s: %s\n", clk_entry->label, state);
	पूर्ण

	snd_iम_लिखो(buffer, "Referred clock:\n");

	अगर (data[1] & 0x00000001) अणु
		snd_iम_लिखो(buffer, "Internal\n");
	पूर्ण अन्यथा अणु
		अचिन्हित पूर्णांक rate;
		स्थिर अक्षर *label;

		क्रम (i = 0; i < ARRAY_SIZE(referred_entries); ++i) अणु
			referred_entry = referred_entries + i;
			अगर ((data[0] & 0x1e0000) == referred_entry->mask) अणु
				label = referred_entry->label;
				अवरोध;
			पूर्ण
		पूर्ण
		अगर (i == ARRAY_SIZE(referred_entries))
			label = "none";

		क्रम (i = 0; i < ARRAY_SIZE(rate_entries); ++i) अणु
			rate_entry = rate_entries + i;
			अगर ((data[0] & 0x1e000000) == rate_entry->mask) अणु
				rate = rate_entry->rate;
				अवरोध;
			पूर्ण
		पूर्ण
		अगर (i == ARRAY_SIZE(rate_entries))
			rate = 0;

		snd_iम_लिखो(buffer, "%s %d\n", label, rate);
	पूर्ण
पूर्ण

अटल व्योम क्रमmer_dump_status(काष्ठा snd_ff *ff,
			       काष्ठा snd_info_buffer *buffer)
अणु
	dump_घड़ी_config(ff, buffer);
	dump_sync_status(ff, buffer);
पूर्ण

अटल पूर्णांक क्रमmer_fill_midi_msg(काष्ठा snd_ff *ff,
				काष्ठा snd_rawmidi_substream *substream,
				अचिन्हित पूर्णांक port)
अणु
	u8 *buf = (u8 *)ff->msg_buf[port];
	पूर्णांक len;
	पूर्णांक i;

	len = snd_rawmidi_transmit_peek(substream, buf,
					SND_FF_MAXIMIM_MIDI_QUADS);
	अगर (len <= 0)
		वापस len;

	// One quadlet includes one byte.
	क्रम (i = len - 1; i >= 0; --i)
		ff->msg_buf[port][i] = cpu_to_le32(buf[i]);
	ff->rx_bytes[port] = len;

	वापस len;
पूर्ण

#घोषणा FF800_STF		0x0000fc88f000
#घोषणा FF800_RX_PACKET_FORMAT	0x0000fc88f004
#घोषणा FF800_ALLOC_TX_STREAM	0x0000fc88f008
#घोषणा FF800_ISOC_COMM_START	0x0000fc88f00c
#घोषणा   FF800_TX_S800_FLAG	0x00000800
#घोषणा FF800_ISOC_COMM_STOP	0x0000fc88f010

#घोषणा FF800_TX_PACKET_ISOC_CH	0x0000801c0008

अटल पूर्णांक allocate_tx_resources(काष्ठा snd_ff *ff)
अणु
	__le32 reg;
	अचिन्हित पूर्णांक count;
	अचिन्हित पूर्णांक tx_isoc_channel;
	पूर्णांक err;

	reg = cpu_to_le32(ff->tx_stream.data_block_quadlets);
	err = snd_fw_transaction(ff->unit, TCODE_WRITE_QUADLET_REQUEST,
				 FF800_ALLOC_TX_STREAM, &reg, माप(reg), 0);
	अगर (err < 0)
		वापस err;

	// Wait till the क्रमmat of tx packet is available.
	count = 0;
	जबतक (count++ < 10) अणु
		u32 data;
		err = snd_fw_transaction(ff->unit, TCODE_READ_QUADLET_REQUEST,
				FF800_TX_PACKET_ISOC_CH, &reg, माप(reg), 0);
		अगर (err < 0)
			वापस err;

		data = le32_to_cpu(reg);
		अगर (data != 0xffffffff) अणु
			tx_isoc_channel = data;
			अवरोध;
		पूर्ण

		msleep(50);
	पूर्ण
	अगर (count >= 10)
		वापस -ETIMEDOUT;

	// NOTE: this is a makeshअगरt to start OHCI 1394 IR context in the
	// channel. On the other hand, 'struct fw_iso_resources.allocated' is
	// not true and it's not deallocated at stop.
	ff->tx_resources.channel = tx_isoc_channel;

	वापस 0;
पूर्ण

अटल पूर्णांक ff800_allocate_resources(काष्ठा snd_ff *ff, अचिन्हित पूर्णांक rate)
अणु
	u32 data;
	__le32 reg;
	पूर्णांक err;

	reg = cpu_to_le32(rate);
	err = snd_fw_transaction(ff->unit, TCODE_WRITE_QUADLET_REQUEST,
				 FF800_STF, &reg, माप(reg), 0);
	अगर (err < 0)
		वापस err;

	// If starting isochronous communication immediately, change of STF has
	// no effect. In this हाल, the communication runs based on क्रमmer STF.
	// Let's sleep क्रम a bit.
	msleep(100);

	// Controllers should allocate isochronous resources क्रम rx stream.
	err = fw_iso_resources_allocate(&ff->rx_resources,
				amdtp_stream_get_max_payload(&ff->rx_stream),
				fw_parent_device(ff->unit)->max_speed);
	अगर (err < 0)
		वापस err;

	// Set isochronous channel and the number of quadlets of rx packets.
	// This should be करोne beक्रमe the allocation of tx resources to aव्योम
	// periodical noise.
	data = ff->rx_stream.data_block_quadlets << 3;
	data = (data << 8) | ff->rx_resources.channel;
	reg = cpu_to_le32(data);
	err = snd_fw_transaction(ff->unit, TCODE_WRITE_QUADLET_REQUEST,
				 FF800_RX_PACKET_FORMAT, &reg, माप(reg), 0);
	अगर (err < 0)
		वापस err;

	वापस allocate_tx_resources(ff);
पूर्ण

अटल पूर्णांक ff800_begin_session(काष्ठा snd_ff *ff, अचिन्हित पूर्णांक rate)
अणु
	अचिन्हित पूर्णांक generation = ff->rx_resources.generation;
	__le32 reg;

	अगर (generation != fw_parent_device(ff->unit)->card->generation) अणु
		पूर्णांक err = fw_iso_resources_update(&ff->rx_resources);
		अगर (err < 0)
			वापस err;
	पूर्ण

	reg = cpu_to_le32(0x80000000);
	reg |= cpu_to_le32(ff->tx_stream.data_block_quadlets);
	अगर (fw_parent_device(ff->unit)->max_speed == SCODE_800)
		reg |= cpu_to_le32(FF800_TX_S800_FLAG);
	वापस snd_fw_transaction(ff->unit, TCODE_WRITE_QUADLET_REQUEST,
				 FF800_ISOC_COMM_START, &reg, माप(reg), 0);
पूर्ण

अटल व्योम ff800_finish_session(काष्ठा snd_ff *ff)
अणु
	__le32 reg;

	reg = cpu_to_le32(0x80000000);
	snd_fw_transaction(ff->unit, TCODE_WRITE_QUADLET_REQUEST,
			   FF800_ISOC_COMM_STOP, &reg, माप(reg), 0);
पूर्ण

// Fireface 800 करोesn't allow drivers to रेजिस्टर lower 4 bytes of destination
// address.
// A ग_लिखो transaction to clear रेजिस्टरed higher 4 bytes of destination address
// has an effect to suppress asynchronous transaction from device.
अटल व्योम ff800_handle_midi_msg(काष्ठा snd_ff *ff, अचिन्हित पूर्णांक offset,
				  __le32 *buf, माप_प्रकार length)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < length / 4; i++) अणु
		u8 byte = le32_to_cpu(buf[i]) & 0xff;
		काष्ठा snd_rawmidi_substream *substream;

		substream = READ_ONCE(ff->tx_midi_substreams[0]);
		अगर (substream)
			snd_rawmidi_receive(substream, &byte, 1);
	पूर्ण
पूर्ण

स्थिर काष्ठा snd_ff_protocol snd_ff_protocol_ff800 = अणु
	.handle_midi_msg	= ff800_handle_midi_msg,
	.fill_midi_msg		= क्रमmer_fill_midi_msg,
	.get_घड़ी		= क्रमmer_get_घड़ी,
	.चयन_fetching_mode	= क्रमmer_चयन_fetching_mode,
	.allocate_resources	= ff800_allocate_resources,
	.begin_session		= ff800_begin_session,
	.finish_session		= ff800_finish_session,
	.dump_status		= क्रमmer_dump_status,
पूर्ण;

#घोषणा FF400_STF		0x000080100500ull
#घोषणा FF400_RX_PACKET_FORMAT	0x000080100504ull
#घोषणा FF400_ISOC_COMM_START	0x000080100508ull
#घोषणा FF400_TX_PACKET_FORMAT	0x00008010050cull
#घोषणा FF400_ISOC_COMM_STOP	0x000080100510ull

// Fireface 400 manages isochronous channel number in 3 bit field. Thereक्रमe,
// we can allocate between 0 and 7 channel.
अटल पूर्णांक ff400_allocate_resources(काष्ठा snd_ff *ff, अचिन्हित पूर्णांक rate)
अणु
	__le32 reg;
	क्रमागत snd_ff_stream_mode mode;
	पूर्णांक i;
	पूर्णांक err;

	// Check whether the given value is supported or not.
	क्रम (i = 0; i < CIP_SFC_COUNT; i++) अणु
		अगर (amdtp_rate_table[i] == rate)
			अवरोध;
	पूर्ण
	अगर (i >= CIP_SFC_COUNT)
		वापस -EINVAL;

	// Set the number of data blocks transferred in a second.
	reg = cpu_to_le32(rate);
	err = snd_fw_transaction(ff->unit, TCODE_WRITE_QUADLET_REQUEST,
				 FF400_STF, &reg, माप(reg), 0);
	अगर (err < 0)
		वापस err;

	msleep(100);

	err = snd_ff_stream_get_multiplier_mode(i, &mode);
	अगर (err < 0)
		वापस err;

	// Keep resources क्रम in-stream.
	ff->tx_resources.channels_mask = 0x00000000000000ffuLL;
	err = fw_iso_resources_allocate(&ff->tx_resources,
			amdtp_stream_get_max_payload(&ff->tx_stream),
			fw_parent_device(ff->unit)->max_speed);
	अगर (err < 0)
		वापस err;

	// Keep resources क्रम out-stream.
	ff->rx_resources.channels_mask = 0x00000000000000ffuLL;
	err = fw_iso_resources_allocate(&ff->rx_resources,
			amdtp_stream_get_max_payload(&ff->rx_stream),
			fw_parent_device(ff->unit)->max_speed);
	अगर (err < 0)
		fw_iso_resources_मुक्त(&ff->tx_resources);

	वापस err;
पूर्ण

अटल पूर्णांक ff400_begin_session(काष्ठा snd_ff *ff, अचिन्हित पूर्णांक rate)
अणु
	अचिन्हित पूर्णांक generation = ff->rx_resources.generation;
	__le32 reg;
	पूर्णांक err;

	अगर (generation != fw_parent_device(ff->unit)->card->generation) अणु
		err = fw_iso_resources_update(&ff->tx_resources);
		अगर (err < 0)
			वापस err;

		err = fw_iso_resources_update(&ff->rx_resources);
		अगर (err < 0)
			वापस err;
	पूर्ण

	// Set isochronous channel and the number of quadlets of received
	// packets.
	reg = cpu_to_le32(((ff->rx_stream.data_block_quadlets << 3) << 8) |
			  ff->rx_resources.channel);
	err = snd_fw_transaction(ff->unit, TCODE_WRITE_QUADLET_REQUEST,
				 FF400_RX_PACKET_FORMAT, &reg, माप(reg), 0);
	अगर (err < 0)
		वापस err;

	// Set isochronous channel and the number of quadlets of transmitted
	// packet.
	// TODO: investigate the purpose of this 0x80.
	reg = cpu_to_le32((0x80 << 24) |
			  (ff->tx_resources.channel << 5) |
			  (ff->tx_stream.data_block_quadlets));
	err = snd_fw_transaction(ff->unit, TCODE_WRITE_QUADLET_REQUEST,
				 FF400_TX_PACKET_FORMAT, &reg, माप(reg), 0);
	अगर (err < 0)
		वापस err;

	// Allow to transmit packets.
	reg = cpu_to_le32(0x00000001);
	वापस snd_fw_transaction(ff->unit, TCODE_WRITE_QUADLET_REQUEST,
				 FF400_ISOC_COMM_START, &reg, माप(reg), 0);
पूर्ण

अटल व्योम ff400_finish_session(काष्ठा snd_ff *ff)
अणु
	__le32 reg;

	reg = cpu_to_le32(0x80000000);
	snd_fw_transaction(ff->unit, TCODE_WRITE_QUADLET_REQUEST,
			   FF400_ISOC_COMM_STOP, &reg, माप(reg), 0);
पूर्ण

// For Fireface 400, lower 4 bytes of destination address is configured by bit
// flag in quadlet रेजिस्टर (little endian) at 0x'0000'801'0051c. Drivers can
// select one of 4 options:
//
// bit flags: offset of destination address
//  - 0x04000000: 0x'....'....'0000'0000
//  - 0x08000000: 0x'....'....'0000'0080
//  - 0x10000000: 0x'....'....'0000'0100
//  - 0x20000000: 0x'....'....'0000'0180
//
// Drivers can suppress the device to transfer asynchronous transactions by
// using below 2 bits.
//  - 0x01000000: suppress transmission
//  - 0x02000000: suppress transmission
//
// Actually, the रेजिस्टर is ग_लिखो-only and includes the other options such as
// input attenuation. This driver allocates destination address with '0000'0000
// in its lower offset and expects userspace application to configure the
// रेजिस्टर क्रम it.
अटल व्योम ff400_handle_midi_msg(काष्ठा snd_ff *ff, अचिन्हित पूर्णांक offset,
				  __le32 *buf, माप_प्रकार length)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < length / 4; i++) अणु
		u32 quad = le32_to_cpu(buf[i]);
		u8 byte;
		अचिन्हित पूर्णांक index;
		काष्ठा snd_rawmidi_substream *substream;

		/* Message in first port. */
		/*
		 * This value may represent the index of this unit when the same
		 * units are on the same IEEE 1394 bus. This driver करोesn't use
		 * it.
		 */
		index = (quad >> 8) & 0xff;
		अगर (index > 0) अणु
			substream = READ_ONCE(ff->tx_midi_substreams[0]);
			अगर (substream != शून्य) अणु
				byte = quad & 0xff;
				snd_rawmidi_receive(substream, &byte, 1);
			पूर्ण
		पूर्ण

		/* Message in second port. */
		index = (quad >> 24) & 0xff;
		अगर (index > 0) अणु
			substream = READ_ONCE(ff->tx_midi_substreams[1]);
			अगर (substream != शून्य) अणु
				byte = (quad >> 16) & 0xff;
				snd_rawmidi_receive(substream, &byte, 1);
			पूर्ण
		पूर्ण
	पूर्ण
पूर्ण

स्थिर काष्ठा snd_ff_protocol snd_ff_protocol_ff400 = अणु
	.handle_midi_msg	= ff400_handle_midi_msg,
	.fill_midi_msg		= क्रमmer_fill_midi_msg,
	.get_घड़ी		= क्रमmer_get_घड़ी,
	.चयन_fetching_mode	= क्रमmer_चयन_fetching_mode,
	.allocate_resources	= ff400_allocate_resources,
	.begin_session		= ff400_begin_session,
	.finish_session		= ff400_finish_session,
	.dump_status		= क्रमmer_dump_status,
पूर्ण;
