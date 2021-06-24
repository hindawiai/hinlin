<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
// ff-protocol-latter - a part of driver क्रम RME Fireface series
//
// Copyright (c) 2019 Takashi Sakamoto
//
// Licensed under the terms of the GNU General Public License, version 2.

#समावेश <linux/delay.h>

#समावेश "ff.h"

#घोषणा LATTER_STF		0xffff00000004ULL
#घोषणा LATTER_ISOC_CHANNELS	0xffff00000008ULL
#घोषणा LATTER_ISOC_START	0xffff0000000cULL
#घोषणा LATTER_FETCH_MODE	0xffff00000010ULL
#घोषणा LATTER_SYNC_STATUS	0x0000801c0000ULL

// The content of sync status रेजिस्टर dअगरfers between models.
//
// Fireface UCX:
//  0xf0000000: (unidentअगरied)
//  0x0f000000: effective rate of sampling घड़ी
//  0x00f00000: detected rate of word घड़ी on BNC पूर्णांकerface
//  0x000f0000: detected rate of ADAT or S/PDIF on optical पूर्णांकerface
//  0x0000f000: detected rate of S/PDIF on coaxial पूर्णांकerface
//  0x00000e00: effective source of sampling घड़ी
//    0x00000e00: Internal
//    0x00000800: (unidentअगरied)
//    0x00000600: Word घड़ी on BNC पूर्णांकerface
//    0x00000400: ADAT on optical पूर्णांकerface
//    0x00000200: S/PDIF on coaxial or optical पूर्णांकerface
//  0x00000100: Optical पूर्णांकerface is used क्रम ADAT संकेत
//  0x00000080: (unidentअगरied)
//  0x00000040: Synchronized to word घड़ी on BNC पूर्णांकerface
//  0x00000020: Synchronized to ADAT or S/PDIF on optical पूर्णांकerface
//  0x00000010: Synchronized to S/PDIF on coaxial पूर्णांकerface
//  0x00000008: (unidentअगरied)
//  0x00000004: Lock word घड़ी on BNC पूर्णांकerface
//  0x00000002: Lock ADAT or S/PDIF on optical पूर्णांकerface
//  0x00000001: Lock S/PDIF on coaxial पूर्णांकerface
//
// Fireface 802 (and perhaps UFX):
//   0xf0000000: effective rate of sampling घड़ी
//   0x0f000000: detected rate of ADAT-B on 2nd optical पूर्णांकerface
//   0x00f00000: detected rate of ADAT-A on 1st optical पूर्णांकerface
//   0x000f0000: detected rate of AES/EBU on XLR or coaxial पूर्णांकerface
//   0x0000f000: detected rate of word घड़ी on BNC पूर्णांकerface
//   0x00000e00: effective source of sampling घड़ी
//     0x00000e00: पूर्णांकernal
//     0x00000800: ADAT-B
//     0x00000600: ADAT-A
//     0x00000400: AES/EBU
//     0x00000200: Word घड़ी
//   0x00000080: Synchronized to ADAT-B on 2nd optical पूर्णांकerface
//   0x00000040: Synchronized to ADAT-A on 1st optical पूर्णांकerface
//   0x00000020: Synchronized to AES/EBU on XLR or 2nd optical पूर्णांकerface
//   0x00000010: Synchronized to word घड़ी on BNC पूर्णांकerface
//   0x00000008: Lock ADAT-B on 2nd optical पूर्णांकerface
//   0x00000004: Lock ADAT-A on 1st optical पूर्णांकerface
//   0x00000002: Lock AES/EBU on XLR or 2nd optical पूर्णांकerface
//   0x00000001: Lock word घड़ी on BNC पूर्णांकerface
//
// The pattern क्रम rate bits:
//   0x00: 32.0 kHz
//   0x01: 44.1 kHz
//   0x02: 48.0 kHz
//   0x04: 64.0 kHz
//   0x05: 88.2 kHz
//   0x06: 96.0 kHz
//   0x08: 128.0 kHz
//   0x09: 176.4 kHz
//   0x0a: 192.0 kHz
अटल पूर्णांक parse_घड़ी_bits(u32 data, अचिन्हित पूर्णांक *rate,
			    क्रमागत snd_ff_घड़ी_src *src,
			    क्रमागत snd_ff_unit_version unit_version)
अणु
	अटल स्थिर काष्ठा अणु
		अचिन्हित पूर्णांक rate;
		u32 flag;
	पूर्ण *rate_entry, rate_entries[] = अणु
		अणु 32000,	0x00, पूर्ण,
		अणु 44100,	0x01, पूर्ण,
		अणु 48000,	0x02, पूर्ण,
		अणु 64000,	0x04, पूर्ण,
		अणु 88200,	0x05, पूर्ण,
		अणु 96000,	0x06, पूर्ण,
		अणु 128000,	0x08, पूर्ण,
		अणु 176400,	0x09, पूर्ण,
		अणु 192000,	0x0a, पूर्ण,
	पूर्ण;
	अटल स्थिर काष्ठा अणु
		क्रमागत snd_ff_घड़ी_src src;
		u32 flag;
	पूर्ण *clk_entry, *clk_entries, ucx_clk_entries[] = अणु
		अणु SND_FF_CLOCK_SRC_SPDIF,	0x00000200, पूर्ण,
		अणु SND_FF_CLOCK_SRC_ADAT1,	0x00000400, पूर्ण,
		अणु SND_FF_CLOCK_SRC_WORD,	0x00000600, पूर्ण,
		अणु SND_FF_CLOCK_SRC_INTERNAL,	0x00000e00, पूर्ण,
	पूर्ण, ufx_ff802_clk_entries[] = अणु
		अणु SND_FF_CLOCK_SRC_WORD,	0x00000200, पूर्ण,
		अणु SND_FF_CLOCK_SRC_SPDIF,	0x00000400, पूर्ण,
		अणु SND_FF_CLOCK_SRC_ADAT1,	0x00000600, पूर्ण,
		अणु SND_FF_CLOCK_SRC_ADAT2,	0x00000800, पूर्ण,
		अणु SND_FF_CLOCK_SRC_INTERNAL,	0x00000e00, पूर्ण,
	पूर्ण;
	u32 rate_bits;
	अचिन्हित पूर्णांक clk_entry_count;
	पूर्णांक i;

	अगर (unit_version == SND_FF_UNIT_VERSION_UCX) अणु
		rate_bits = (data & 0x0f000000) >> 24;
		clk_entries = ucx_clk_entries;
		clk_entry_count = ARRAY_SIZE(ucx_clk_entries);
	पूर्ण अन्यथा अणु
		rate_bits = (data & 0xf0000000) >> 28;
		clk_entries = ufx_ff802_clk_entries;
		clk_entry_count = ARRAY_SIZE(ufx_ff802_clk_entries);
	पूर्ण

	क्रम (i = 0; i < ARRAY_SIZE(rate_entries); ++i) अणु
		rate_entry = rate_entries + i;
		अगर (rate_bits == rate_entry->flag) अणु
			*rate = rate_entry->rate;
			अवरोध;
		पूर्ण
	पूर्ण
	अगर (i == ARRAY_SIZE(rate_entries))
		वापस -EIO;

	क्रम (i = 0; i < clk_entry_count; ++i) अणु
		clk_entry = clk_entries + i;
		अगर ((data & 0x000e00) == clk_entry->flag) अणु
			*src = clk_entry->src;
			अवरोध;
		पूर्ण
	पूर्ण
	अगर (i == clk_entry_count)
		वापस -EIO;

	वापस 0;
पूर्ण

अटल पूर्णांक latter_get_घड़ी(काष्ठा snd_ff *ff, अचिन्हित पूर्णांक *rate,
			   क्रमागत snd_ff_घड़ी_src *src)
अणु
	__le32 reg;
	u32 data;
	पूर्णांक err;

	err = snd_fw_transaction(ff->unit, TCODE_READ_QUADLET_REQUEST,
				 LATTER_SYNC_STATUS, &reg, माप(reg), 0);
	अगर (err < 0)
		वापस err;
	data = le32_to_cpu(reg);

	वापस parse_घड़ी_bits(data, rate, src, ff->unit_version);
पूर्ण

अटल पूर्णांक latter_चयन_fetching_mode(काष्ठा snd_ff *ff, bool enable)
अणु
	u32 data;
	__le32 reg;

	अगर (enable)
		data = 0x00000000;
	अन्यथा
		data = 0xffffffff;
	reg = cpu_to_le32(data);

	वापस snd_fw_transaction(ff->unit, TCODE_WRITE_QUADLET_REQUEST,
				  LATTER_FETCH_MODE, &reg, माप(reg), 0);
पूर्ण

अटल पूर्णांक latter_allocate_resources(काष्ठा snd_ff *ff, अचिन्हित पूर्णांक rate)
अणु
	क्रमागत snd_ff_stream_mode mode;
	अचिन्हित पूर्णांक code;
	__le32 reg;
	अचिन्हित पूर्णांक count;
	पूर्णांक i;
	पूर्णांक err;

	// Set the number of data blocks transferred in a second.
	अगर (rate % 48000 == 0)
		code = 0x04;
	अन्यथा अगर (rate % 44100 == 0)
		code = 0x02;
	अन्यथा अगर (rate % 32000 == 0)
		code = 0x00;
	अन्यथा
		वापस -EINVAL;

	अगर (rate >= 64000 && rate < 128000)
		code |= 0x08;
	अन्यथा अगर (rate >= 128000)
		code |= 0x10;

	reg = cpu_to_le32(code);
	err = snd_fw_transaction(ff->unit, TCODE_WRITE_QUADLET_REQUEST,
				 LATTER_STF, &reg, माप(reg), 0);
	अगर (err < 0)
		वापस err;

	// Confirm to shअगरt transmission घड़ी.
	count = 0;
	जबतक (count++ < 10) अणु
		अचिन्हित पूर्णांक curr_rate;
		क्रमागत snd_ff_घड़ी_src src;

		err = latter_get_घड़ी(ff, &curr_rate, &src);
		अगर (err < 0)
			वापस err;

		अगर (curr_rate == rate)
			अवरोध;
	पूर्ण
	अगर (count > 10)
		वापस -ETIMEDOUT;

	क्रम (i = 0; i < ARRAY_SIZE(amdtp_rate_table); ++i) अणु
		अगर (rate == amdtp_rate_table[i])
			अवरोध;
	पूर्ण
	अगर (i == ARRAY_SIZE(amdtp_rate_table))
		वापस -EINVAL;

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

अटल पूर्णांक latter_begin_session(काष्ठा snd_ff *ff, अचिन्हित पूर्णांक rate)
अणु
	अचिन्हित पूर्णांक generation = ff->rx_resources.generation;
	अचिन्हित पूर्णांक flag;
	u32 data;
	__le32 reg;
	पूर्णांक err;

	अगर (ff->unit_version == SND_FF_UNIT_VERSION_UCX) अणु
		// For Fireface UCX. Always use the maximum number of data
		// channels in data block of packet.
		अगर (rate >= 32000 && rate <= 48000)
			flag = 0x92;
		अन्यथा अगर (rate >= 64000 && rate <= 96000)
			flag = 0x8e;
		अन्यथा अगर (rate >= 128000 && rate <= 192000)
			flag = 0x8c;
		अन्यथा
			वापस -EINVAL;
	पूर्ण अन्यथा अणु
		// For Fireface UFX and 802. Due to bandwidth limitation on
		// IEEE 1394a (400 Mbps), Analog 1-12 and AES are available
		// without any ADAT at quadruple speed.
		अगर (rate >= 32000 && rate <= 48000)
			flag = 0x9e;
		अन्यथा अगर (rate >= 64000 && rate <= 96000)
			flag = 0x96;
		अन्यथा अगर (rate >= 128000 && rate <= 192000)
			flag = 0x8e;
		अन्यथा
			वापस -EINVAL;
	पूर्ण

	अगर (generation != fw_parent_device(ff->unit)->card->generation) अणु
		err = fw_iso_resources_update(&ff->tx_resources);
		अगर (err < 0)
			वापस err;

		err = fw_iso_resources_update(&ff->rx_resources);
		अगर (err < 0)
			वापस err;
	पूर्ण

	data = (ff->tx_resources.channel << 8) | ff->rx_resources.channel;
	reg = cpu_to_le32(data);
	err = snd_fw_transaction(ff->unit, TCODE_WRITE_QUADLET_REQUEST,
				 LATTER_ISOC_CHANNELS, &reg, माप(reg), 0);
	अगर (err < 0)
		वापस err;

	reg = cpu_to_le32(flag);
	वापस snd_fw_transaction(ff->unit, TCODE_WRITE_QUADLET_REQUEST,
				  LATTER_ISOC_START, &reg, माप(reg), 0);
पूर्ण

अटल व्योम latter_finish_session(काष्ठा snd_ff *ff)
अणु
	__le32 reg;

	reg = cpu_to_le32(0x00000000);
	snd_fw_transaction(ff->unit, TCODE_WRITE_QUADLET_REQUEST,
			   LATTER_ISOC_START, &reg, माप(reg), 0);
पूर्ण

अटल व्योम latter_dump_status(काष्ठा snd_ff *ff, काष्ठा snd_info_buffer *buffer)
अणु
	अटल स्थिर काष्ठा अणु
		अक्षर *स्थिर label;
		u32 locked_mask;
		u32 synced_mask;
	पूर्ण *clk_entry, *clk_entries, ucx_clk_entries[] = अणु
		अणु "S/PDIF",	0x00000001, 0x00000010, पूर्ण,
		अणु "ADAT",	0x00000002, 0x00000020, पूर्ण,
		अणु "WDClk",	0x00000004, 0x00000040, पूर्ण,
	पूर्ण, ufx_ff802_clk_entries[] = अणु
		अणु "WDClk",	0x00000001, 0x00000010, पूर्ण,
		अणु "AES/EBU",	0x00000002, 0x00000020, पूर्ण,
		अणु "ADAT-A",	0x00000004, 0x00000040, पूर्ण,
		अणु "ADAT-B",	0x00000008, 0x00000080, पूर्ण,
	पूर्ण;
	__le32 reg;
	u32 data;
	अचिन्हित पूर्णांक rate;
	क्रमागत snd_ff_घड़ी_src src;
	स्थिर अक्षर *label;
	अचिन्हित पूर्णांक clk_entry_count;
	पूर्णांक i;
	पूर्णांक err;

	err = snd_fw_transaction(ff->unit, TCODE_READ_QUADLET_REQUEST,
				 LATTER_SYNC_STATUS, &reg, माप(reg), 0);
	अगर (err < 0)
		वापस;
	data = le32_to_cpu(reg);

	snd_iम_लिखो(buffer, "External source detection:\n");

	अगर (ff->unit_version == SND_FF_UNIT_VERSION_UCX) अणु
		clk_entries = ucx_clk_entries;
		clk_entry_count = ARRAY_SIZE(ucx_clk_entries);
	पूर्ण अन्यथा अणु
		clk_entries = ufx_ff802_clk_entries;
		clk_entry_count = ARRAY_SIZE(ufx_ff802_clk_entries);
	पूर्ण

	क्रम (i = 0; i < clk_entry_count; ++i) अणु
		clk_entry = clk_entries + i;
		snd_iम_लिखो(buffer, "%s: ", clk_entry->label);
		अगर (data & clk_entry->locked_mask) अणु
			अगर (data & clk_entry->synced_mask)
				snd_iम_लिखो(buffer, "sync\n");
			अन्यथा
				snd_iम_लिखो(buffer, "lock\n");
		पूर्ण अन्यथा अणु
			snd_iम_लिखो(buffer, "none\n");
		पूर्ण
	पूर्ण

	err = parse_घड़ी_bits(data, &rate, &src, ff->unit_version);
	अगर (err < 0)
		वापस;
	label = snd_ff_proc_get_clk_label(src);
	अगर (!label)
		वापस;

	snd_iम_लिखो(buffer, "Referred clock: %s %d\n", label, rate);
पूर्ण

// NOTE: transactions are transferred within 0x00-0x7f in allocated range of
// address. This seems to be क्रम check of discontinuity in receiver side.
//
// Like Fireface 400, drivers can select one of 4 options क्रम lower 4 bytes of
// destination address by bit flags in quadlet रेजिस्टर (little endian) at
// 0x'ffff'0000'0014:
//
// bit flags: offset of destination address
// - 0x00002000: 0x'....'....'0000'0000
// - 0x00004000: 0x'....'....'0000'0080
// - 0x00008000: 0x'....'....'0000'0100
// - 0x00010000: 0x'....'....'0000'0180
//
// Drivers can suppress the device to transfer asynchronous transactions by
// clear these bit flags.
//
// Actually, the रेजिस्टर is ग_लिखो-only and includes the other settings such as
// input attenuation. This driver allocates क्रम the first option
// (0x'....'....'0000'0000) and expects userspace application to configure the
// रेजिस्टर क्रम it.
अटल व्योम latter_handle_midi_msg(काष्ठा snd_ff *ff, अचिन्हित पूर्णांक offset,
				   __le32 *buf, माप_प्रकार length)
अणु
	u32 data = le32_to_cpu(*buf);
	अचिन्हित पूर्णांक index = (data & 0x000000f0) >> 4;
	u8 byte[3];
	काष्ठा snd_rawmidi_substream *substream;
	अचिन्हित पूर्णांक len;

	अगर (index >= ff->spec->midi_in_ports)
		वापस;

	चयन (data & 0x0000000f) अणु
	हाल 0x00000008:
	हाल 0x00000009:
	हाल 0x0000000a:
	हाल 0x0000000b:
	हाल 0x0000000e:
		len = 3;
		अवरोध;
	हाल 0x0000000c:
	हाल 0x0000000d:
		len = 2;
		अवरोध;
	शेष:
		len = data & 0x00000003;
		अगर (len == 0)
			len = 3;
		अवरोध;
	पूर्ण

	byte[0] = (data & 0x0000ff00) >> 8;
	byte[1] = (data & 0x00ff0000) >> 16;
	byte[2] = (data & 0xff000000) >> 24;

	substream = READ_ONCE(ff->tx_midi_substreams[index]);
	अगर (substream)
		snd_rawmidi_receive(substream, byte, len);
पूर्ण

/*
 * When वापस minus value, given argument is not MIDI status.
 * When वापस 0, given argument is a beginning of प्रणाली exclusive.
 * When वापस the others, given argument is MIDI data.
 */
अटल अंतरभूत पूर्णांक calculate_message_bytes(u8 status)
अणु
	चयन (status) अणु
	हाल 0xf6:	/* Tune request. */
	हाल 0xf8:	/* Timing घड़ी. */
	हाल 0xfa:	/* Start. */
	हाल 0xfb:	/* Continue. */
	हाल 0xfc:	/* Stop. */
	हाल 0xfe:	/* Active sensing. */
	हाल 0xff:	/* System reset. */
		वापस 1;
	हाल 0xf1:	/* MIDI समय code quarter frame. */
	हाल 0xf3:	/* Song select. */
		वापस 2;
	हाल 0xf2:	/* Song position poपूर्णांकer. */
		वापस 3;
	हाल 0xf0:	/* Exclusive. */
		वापस 0;
	हाल 0xf7:	/* End of exclusive. */
		अवरोध;
	हाल 0xf4:	/* Undefined. */
	हाल 0xf5:	/* Undefined. */
	हाल 0xf9:	/* Undefined. */
	हाल 0xfd:	/* Undefined. */
		अवरोध;
	शेष:
		चयन (status & 0xf0) अणु
		हाल 0x80:	/* Note on. */
		हाल 0x90:	/* Note off. */
		हाल 0xa0:	/* Polyphonic key pressure. */
		हाल 0xb0:	/* Control change and Mode change. */
		हाल 0xe0:	/* Pitch bend change. */
			वापस 3;
		हाल 0xc0:	/* Program change. */
		हाल 0xd0:	/* Channel pressure. */
			वापस 2;
		शेष:
		अवरोध;
		पूर्ण
	अवरोध;
	पूर्ण

	वापस -EINVAL;
पूर्ण

अटल पूर्णांक latter_fill_midi_msg(काष्ठा snd_ff *ff,
				काष्ठा snd_rawmidi_substream *substream,
				अचिन्हित पूर्णांक port)
अणु
	u32 data = अणु0पूर्ण;
	u8 *buf = (u8 *)&data;
	पूर्णांक consumed;

	buf[0] = port << 4;
	consumed = snd_rawmidi_transmit_peek(substream, buf + 1, 3);
	अगर (consumed <= 0)
		वापस consumed;

	अगर (!ff->on_sysex[port]) अणु
		अगर (buf[1] != 0xf0) अणु
			अगर (consumed < calculate_message_bytes(buf[1]))
				वापस 0;
		पूर्ण अन्यथा अणु
			// The beginning of exclusives.
			ff->on_sysex[port] = true;
		पूर्ण

		buf[0] |= consumed;
	पूर्ण अन्यथा अणु
		अगर (buf[1] != 0xf7) अणु
			अगर (buf[2] == 0xf7 || buf[3] == 0xf7) अणु
				// Transfer end code at next समय.
				consumed -= 1;
			पूर्ण

			buf[0] |= consumed;
		पूर्ण अन्यथा अणु
			// The end of exclusives.
			ff->on_sysex[port] = false;
			consumed = 1;
			buf[0] |= 0x0f;
		पूर्ण
	पूर्ण

	ff->msg_buf[port][0] = cpu_to_le32(data);
	ff->rx_bytes[port] = consumed;

	वापस 1;
पूर्ण

स्थिर काष्ठा snd_ff_protocol snd_ff_protocol_latter = अणु
	.handle_midi_msg	= latter_handle_midi_msg,
	.fill_midi_msg		= latter_fill_midi_msg,
	.get_घड़ी		= latter_get_घड़ी,
	.चयन_fetching_mode	= latter_चयन_fetching_mode,
	.allocate_resources	= latter_allocate_resources,
	.begin_session		= latter_begin_session,
	.finish_session		= latter_finish_session,
	.dump_status		= latter_dump_status,
पूर्ण;
