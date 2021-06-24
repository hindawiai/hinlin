<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * dice_proc.c - a part of driver क्रम Dice based devices
 *
 * Copyright (c) Clemens Ladisch
 * Copyright (c) 2014 Takashi Sakamoto
 */

#समावेश "dice.h"

अटल पूर्णांक dice_proc_पढ़ो_mem(काष्ठा snd_dice *dice, व्योम *buffer,
			      अचिन्हित पूर्णांक offset_q, अचिन्हित पूर्णांक quadlets)
अणु
	अचिन्हित पूर्णांक i;
	पूर्णांक err;

	err = snd_fw_transaction(dice->unit, TCODE_READ_BLOCK_REQUEST,
				 DICE_PRIVATE_SPACE + 4 * offset_q,
				 buffer, 4 * quadlets, 0);
	अगर (err < 0)
		वापस err;

	क्रम (i = 0; i < quadlets; ++i)
		be32_to_cpus(&((u32 *)buffer)[i]);

	वापस 0;
पूर्ण

अटल स्थिर अक्षर *str_from_array(स्थिर अक्षर *स्थिर strs[], अचिन्हित पूर्णांक count,
				  अचिन्हित पूर्णांक i)
अणु
	अगर (i < count)
		वापस strs[i];

	वापस "(unknown)";
पूर्ण

अटल व्योम dice_proc_fixup_string(अक्षर *s, अचिन्हित पूर्णांक size)
अणु
	अचिन्हित पूर्णांक i;

	क्रम (i = 0; i < size; i += 4)
		cpu_to_le32s((u32 *)(s + i));

	क्रम (i = 0; i < size - 2; ++i) अणु
		अगर (s[i] == '\0')
			वापस;
		अगर (s[i] == '\\' && s[i + 1] == '\\') अणु
			s[i + 2] = '\0';
			वापस;
		पूर्ण
	पूर्ण
	s[size - 1] = '\0';
पूर्ण

अटल व्योम dice_proc_पढ़ो(काष्ठा snd_info_entry *entry,
			   काष्ठा snd_info_buffer *buffer)
अणु
	अटल स्थिर अक्षर *स्थिर section_names[5] = अणु
		"global", "tx", "rx", "ext_sync", "unused2"
	पूर्ण;
	अटल स्थिर अक्षर *स्थिर घड़ी_sources[] = अणु
		"aes1", "aes2", "aes3", "aes4", "aes", "adat", "tdif",
		"wc", "arx1", "arx2", "arx3", "arx4", "internal"
	पूर्ण;
	अटल स्थिर अक्षर *स्थिर rates[] = अणु
		"32000", "44100", "48000", "88200", "96000", "176400", "192000",
		"any low", "any mid", "any high", "none"
	पूर्ण;
	काष्ठा snd_dice *dice = entry->निजी_data;
	u32 sections[ARRAY_SIZE(section_names) * 2];
	काष्ठा अणु
		u32 number;
		u32 size;
	पूर्ण tx_rx_header;
	जोड़ अणु
		काष्ठा अणु
			u32 owner_hi, owner_lo;
			u32 notअगरication;
			अक्षर nick_name[NICK_NAME_SIZE];
			u32 घड़ी_select;
			u32 enable;
			u32 status;
			u32 extended_status;
			u32 sample_rate;
			u32 version;
			u32 घड़ी_caps;
			अक्षर घड़ी_source_names[CLOCK_SOURCE_NAMES_SIZE];
		पूर्ण global;
		काष्ठा अणु
			u32 iso;
			u32 number_audio;
			u32 number_midi;
			u32 speed;
			अक्षर names[TX_NAMES_SIZE];
			u32 ac3_caps;
			u32 ac3_enable;
		पूर्ण tx;
		काष्ठा अणु
			u32 iso;
			u32 seq_start;
			u32 number_audio;
			u32 number_midi;
			अक्षर names[RX_NAMES_SIZE];
			u32 ac3_caps;
			u32 ac3_enable;
		पूर्ण rx;
		काष्ठा अणु
			u32 घड़ी_source;
			u32 locked;
			u32 rate;
			u32 adat_user_data;
		पूर्ण ext_sync;
	पूर्ण buf;
	अचिन्हित पूर्णांक quadlets, stream, i;

	अगर (dice_proc_पढ़ो_mem(dice, sections, 0, ARRAY_SIZE(sections)) < 0)
		वापस;
	snd_iम_लिखो(buffer, "sections:\n");
	क्रम (i = 0; i < ARRAY_SIZE(section_names); ++i)
		snd_iम_लिखो(buffer, "  %s: offset %u, size %u\n",
			    section_names[i],
			    sections[i * 2], sections[i * 2 + 1]);

	quadlets = min_t(u32, sections[1], माप(buf.global) / 4);
	अगर (dice_proc_पढ़ो_mem(dice, &buf.global, sections[0], quadlets) < 0)
		वापस;
	snd_iम_लिखो(buffer, "global:\n");
	snd_iम_लिखो(buffer, "  owner: %04x:%04x%08x\n",
		    buf.global.owner_hi >> 16,
		    buf.global.owner_hi & 0xffff, buf.global.owner_lo);
	snd_iम_लिखो(buffer, "  notification: %08x\n", buf.global.notअगरication);
	dice_proc_fixup_string(buf.global.nick_name, NICK_NAME_SIZE);
	snd_iम_लिखो(buffer, "  nick name: %s\n", buf.global.nick_name);
	snd_iम_लिखो(buffer, "  clock select: %s %s\n",
		    str_from_array(घड़ी_sources, ARRAY_SIZE(घड़ी_sources),
				   buf.global.घड़ी_select & CLOCK_SOURCE_MASK),
		    str_from_array(rates, ARRAY_SIZE(rates),
				   (buf.global.घड़ी_select & CLOCK_RATE_MASK)
				   >> CLOCK_RATE_SHIFT));
	snd_iम_लिखो(buffer, "  enable: %u\n", buf.global.enable);
	snd_iम_लिखो(buffer, "  status: %slocked %s\n",
		    buf.global.status & STATUS_SOURCE_LOCKED ? "" : "un",
		    str_from_array(rates, ARRAY_SIZE(rates),
				   (buf.global.status &
				    STATUS_NOMINAL_RATE_MASK)
				   >> CLOCK_RATE_SHIFT));
	snd_iम_लिखो(buffer, "  ext status: %08x\n", buf.global.extended_status);
	snd_iम_लिखो(buffer, "  sample rate: %u\n", buf.global.sample_rate);
	अगर (quadlets >= 90) अणु
		snd_iम_लिखो(buffer, "  version: %u.%u.%u.%u\n",
			    (buf.global.version >> 24) & 0xff,
			    (buf.global.version >> 16) & 0xff,
			    (buf.global.version >>  8) & 0xff,
			    (buf.global.version >>  0) & 0xff);
		snd_iम_लिखो(buffer, "  clock caps:");
		क्रम (i = 0; i <= 6; ++i)
			अगर (buf.global.घड़ी_caps & (1 << i))
				snd_iम_लिखो(buffer, " %s", rates[i]);
		क्रम (i = 0; i <= 12; ++i)
			अगर (buf.global.घड़ी_caps & (1 << (16 + i)))
				snd_iम_लिखो(buffer, " %s", घड़ी_sources[i]);
		snd_iम_लिखो(buffer, "\n");
		dice_proc_fixup_string(buf.global.घड़ी_source_names,
				       CLOCK_SOURCE_NAMES_SIZE);
		snd_iम_लिखो(buffer, "  clock source names: %s\n",
			    buf.global.घड़ी_source_names);
	पूर्ण

	अगर (dice_proc_पढ़ो_mem(dice, &tx_rx_header, sections[2], 2) < 0)
		वापस;
	quadlets = min_t(u32, tx_rx_header.size, माप(buf.tx) / 4);
	क्रम (stream = 0; stream < tx_rx_header.number; ++stream) अणु
		अगर (dice_proc_पढ़ो_mem(dice, &buf.tx, sections[2] + 2 +
				       stream * tx_rx_header.size,
				       quadlets) < 0)
			अवरोध;
		snd_iम_लिखो(buffer, "tx %u:\n", stream);
		snd_iम_लिखो(buffer, "  iso channel: %d\n", (पूर्णांक)buf.tx.iso);
		snd_iम_लिखो(buffer, "  audio channels: %u\n",
			    buf.tx.number_audio);
		snd_iम_लिखो(buffer, "  midi ports: %u\n", buf.tx.number_midi);
		snd_iम_लिखो(buffer, "  speed: S%u\n", 100u << buf.tx.speed);
		अगर (quadlets >= 68) अणु
			dice_proc_fixup_string(buf.tx.names, TX_NAMES_SIZE);
			snd_iम_लिखो(buffer, "  names: %s\n", buf.tx.names);
		पूर्ण
		अगर (quadlets >= 70) अणु
			snd_iम_लिखो(buffer, "  ac3 caps: %08x\n",
				    buf.tx.ac3_caps);
			snd_iम_लिखो(buffer, "  ac3 enable: %08x\n",
				    buf.tx.ac3_enable);
		पूर्ण
	पूर्ण

	अगर (dice_proc_पढ़ो_mem(dice, &tx_rx_header, sections[4], 2) < 0)
		वापस;
	quadlets = min_t(u32, tx_rx_header.size, माप(buf.rx) / 4);
	क्रम (stream = 0; stream < tx_rx_header.number; ++stream) अणु
		अगर (dice_proc_पढ़ो_mem(dice, &buf.rx, sections[4] + 2 +
				       stream * tx_rx_header.size,
				       quadlets) < 0)
			अवरोध;
		snd_iम_लिखो(buffer, "rx %u:\n", stream);
		snd_iम_लिखो(buffer, "  iso channel: %d\n", (पूर्णांक)buf.rx.iso);
		snd_iम_लिखो(buffer, "  sequence start: %u\n", buf.rx.seq_start);
		snd_iम_लिखो(buffer, "  audio channels: %u\n",
			    buf.rx.number_audio);
		snd_iम_लिखो(buffer, "  midi ports: %u\n", buf.rx.number_midi);
		अगर (quadlets >= 68) अणु
			dice_proc_fixup_string(buf.rx.names, RX_NAMES_SIZE);
			snd_iम_लिखो(buffer, "  names: %s\n", buf.rx.names);
		पूर्ण
		अगर (quadlets >= 70) अणु
			snd_iम_लिखो(buffer, "  ac3 caps: %08x\n",
				    buf.rx.ac3_caps);
			snd_iम_लिखो(buffer, "  ac3 enable: %08x\n",
				    buf.rx.ac3_enable);
		पूर्ण
	पूर्ण

	quadlets = min_t(u32, sections[7], माप(buf.ext_sync) / 4);
	अगर (quadlets >= 4) अणु
		अगर (dice_proc_पढ़ो_mem(dice, &buf.ext_sync,
				       sections[6], 4) < 0)
			वापस;
		snd_iम_लिखो(buffer, "ext status:\n");
		snd_iम_लिखो(buffer, "  clock source: %s\n",
			    str_from_array(घड़ी_sources,
					   ARRAY_SIZE(घड़ी_sources),
					   buf.ext_sync.घड़ी_source));
		snd_iम_लिखो(buffer, "  locked: %u\n", buf.ext_sync.locked);
		snd_iम_लिखो(buffer, "  rate: %s\n",
			    str_from_array(rates, ARRAY_SIZE(rates),
					   buf.ext_sync.rate));
		snd_iम_लिखो(buffer, "  adat user data: ");
		अगर (buf.ext_sync.adat_user_data & ADAT_USER_DATA_NO_DATA)
			snd_iम_लिखो(buffer, "-\n");
		अन्यथा
			snd_iम_लिखो(buffer, "%x\n",
				    buf.ext_sync.adat_user_data);
	पूर्ण
पूर्ण

अटल व्योम dice_proc_पढ़ो_क्रमmation(काष्ठा snd_info_entry *entry,
				     काष्ठा snd_info_buffer *buffer)
अणु
	अटल स्थिर अक्षर *स्थिर rate_labels[] = अणु
		[SND_DICE_RATE_MODE_LOW]	= "low",
		[SND_DICE_RATE_MODE_MIDDLE]	= "middle",
		[SND_DICE_RATE_MODE_HIGH]	= "high",
	पूर्ण;
	काष्ठा snd_dice *dice = entry->निजी_data;
	पूर्णांक i, j;

	snd_iम_लिखो(buffer, "Output stream from unit:\n");
	क्रम (i = 0; i < SND_DICE_RATE_MODE_COUNT; ++i)
		snd_iम_लिखो(buffer, "\t%s", rate_labels[i]);
	snd_iम_लिखो(buffer, "\tMIDI\n");
	क्रम (i = 0; i < MAX_STREAMS; ++i) अणु
		snd_iम_लिखो(buffer, "Tx %u:", i);
		क्रम (j = 0; j < SND_DICE_RATE_MODE_COUNT; ++j)
			snd_iम_लिखो(buffer, "\t%u", dice->tx_pcm_chs[i][j]);
		snd_iम_लिखो(buffer, "\t%u\n", dice->tx_midi_ports[i]);
	पूर्ण

	snd_iम_लिखो(buffer, "Input stream to unit:\n");
	क्रम (i = 0; i < SND_DICE_RATE_MODE_COUNT; ++i)
		snd_iम_लिखो(buffer, "\t%s", rate_labels[i]);
	snd_iम_लिखो(buffer, "\n");
	क्रम (i = 0; i < MAX_STREAMS; ++i) अणु
		snd_iम_लिखो(buffer, "Rx %u:", i);
		क्रम (j = 0; j < SND_DICE_RATE_MODE_COUNT; ++j)
			snd_iम_लिखो(buffer, "\t%u", dice->rx_pcm_chs[i][j]);
		snd_iम_लिखो(buffer, "\t%u\n", dice->rx_midi_ports[i]);
	पूर्ण
पूर्ण

अटल व्योम add_node(काष्ठा snd_dice *dice, काष्ठा snd_info_entry *root,
		     स्थिर अक्षर *name,
		     व्योम (*op)(काष्ठा snd_info_entry *entry,
				काष्ठा snd_info_buffer *buffer))
अणु
	काष्ठा snd_info_entry *entry;

	entry = snd_info_create_card_entry(dice->card, name, root);
	अगर (entry)
		snd_info_set_text_ops(entry, dice, op);
पूर्ण

व्योम snd_dice_create_proc(काष्ठा snd_dice *dice)
अणु
	काष्ठा snd_info_entry *root;

	/*
	 * All nodes are स्वतःmatically हटाओd at snd_card_disconnect(),
	 * by following to link list.
	 */
	root = snd_info_create_card_entry(dice->card, "firewire",
					  dice->card->proc_root);
	अगर (!root)
		वापस;
	root->mode = S_IFसूची | 0555;

	add_node(dice, root, "dice", dice_proc_पढ़ो);
	add_node(dice, root, "formation", dice_proc_पढ़ो_क्रमmation);
पूर्ण
