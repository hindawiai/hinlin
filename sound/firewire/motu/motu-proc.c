<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * motu-proc.c - a part of driver क्रम MOTU FireWire series
 *
 * Copyright (c) 2015-2017 Takashi Sakamoto <o-takashi@sakamocchi.jp>
 */

#समावेश "./motu.h"

अटल स्थिर अक्षर *स्थिर घड़ी_names[] = अणु
	[SND_MOTU_CLOCK_SOURCE_INTERNAL] = "Internal",
	[SND_MOTU_CLOCK_SOURCE_ADAT_ON_DSUB] = "ADAT on Dsub-9pin interface",
	[SND_MOTU_CLOCK_SOURCE_ADAT_ON_OPT] = "ADAT on optical interface",
	[SND_MOTU_CLOCK_SOURCE_ADAT_ON_OPT_A] = "ADAT on optical interface A",
	[SND_MOTU_CLOCK_SOURCE_ADAT_ON_OPT_B] = "ADAT on optical interface B",
	[SND_MOTU_CLOCK_SOURCE_SPDIF_ON_OPT] = "S/PDIF on optical interface",
	[SND_MOTU_CLOCK_SOURCE_SPDIF_ON_OPT_A] = "S/PDIF on optical interface A",
	[SND_MOTU_CLOCK_SOURCE_SPDIF_ON_OPT_B] = "S/PDIF on optical interface B",
	[SND_MOTU_CLOCK_SOURCE_SPDIF_ON_COAX] = "S/PDIF on coaxial interface",
	[SND_MOTU_CLOCK_SOURCE_AESEBU_ON_XLR] = "AESEBU on XLR interface",
	[SND_MOTU_CLOCK_SOURCE_WORD_ON_BNC] = "Word clock on BNC interface",
	[SND_MOTU_CLOCK_SOURCE_SPH] = "Source packet header",
	[SND_MOTU_CLOCK_SOURCE_UNKNOWN] = "Unknown",
पूर्ण;

अटल व्योम proc_पढ़ो_घड़ी(काष्ठा snd_info_entry *entry,
			    काष्ठा snd_info_buffer *buffer)
अणु

	काष्ठा snd_motu *motu = entry->निजी_data;
	अचिन्हित पूर्णांक rate;
	क्रमागत snd_motu_घड़ी_source source;

	अगर (snd_motu_protocol_get_घड़ी_rate(motu, &rate) < 0)
		वापस;
	अगर (snd_motu_protocol_get_घड़ी_source(motu, &source) < 0)
		वापस;

	snd_iम_लिखो(buffer, "Rate:\t%d\n", rate);
	snd_iम_लिखो(buffer, "Source:\t%s\n", घड़ी_names[source]);
पूर्ण

अटल व्योम proc_पढ़ो_क्रमmat(काष्ठा snd_info_entry *entry,
			     काष्ठा snd_info_buffer *buffer)
अणु
	काष्ठा snd_motu *motu = entry->निजी_data;
	अचिन्हित पूर्णांक mode;
	काष्ठा snd_motu_packet_क्रमmat *क्रमmats;
	पूर्णांक i;

	अगर (snd_motu_protocol_cache_packet_क्रमmats(motu) < 0)
		वापस;

	snd_iम_लिखो(buffer, "tx:\tmsg\tfixed\ttotal\n");
	क्रम (i = 0; i < SND_MOTU_CLOCK_RATE_COUNT; ++i) अणु
		mode = i >> 1;

		क्रमmats = &motu->tx_packet_क्रमmats;
		snd_iम_लिखो(buffer,
			    "%u:\t%u\t%u\t%u\n",
			    snd_motu_घड़ी_rates[i],
			    क्रमmats->msg_chunks,
			    motu->spec->tx_fixed_pcm_chunks[mode],
			    क्रमmats->pcm_chunks[mode]);
	पूर्ण

	snd_iम_लिखो(buffer, "rx:\tmsg\tfixed\ttotal\n");
	क्रम (i = 0; i < SND_MOTU_CLOCK_RATE_COUNT; ++i) अणु
		mode = i >> 1;

		क्रमmats = &motu->rx_packet_क्रमmats;
		snd_iम_लिखो(buffer,
			    "%u:\t%u\t%u\t%u\n",
			    snd_motu_घड़ी_rates[i],
			    क्रमmats->msg_chunks,
			    motu->spec->rx_fixed_pcm_chunks[mode],
			    क्रमmats->pcm_chunks[mode]);
	पूर्ण
पूर्ण

अटल व्योम add_node(काष्ठा snd_motu *motu, काष्ठा snd_info_entry *root,
		     स्थिर अक्षर *name,
		     व्योम (*op)(काष्ठा snd_info_entry *e,
				काष्ठा snd_info_buffer *b))
अणु
	काष्ठा snd_info_entry *entry;

	entry = snd_info_create_card_entry(motu->card, name, root);
	अगर (entry)
		snd_info_set_text_ops(entry, motu, op);
पूर्ण

व्योम snd_motu_proc_init(काष्ठा snd_motu *motu)
अणु
	काष्ठा snd_info_entry *root;

	/*
	 * All nodes are स्वतःmatically हटाओd at snd_card_disconnect(),
	 * by following to link list.
	 */
	root = snd_info_create_card_entry(motu->card, "firewire",
					  motu->card->proc_root);
	अगर (root == शून्य)
		वापस;
	root->mode = S_IFसूची | 0555;

	add_node(motu, root, "clock", proc_पढ़ो_घड़ी);
	add_node(motu, root, "format", proc_पढ़ो_क्रमmat);
पूर्ण
