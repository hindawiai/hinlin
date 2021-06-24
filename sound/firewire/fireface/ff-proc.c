<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * ff-proc.c - a part of driver क्रम RME Fireface series
 *
 * Copyright (c) 2015-2017 Takashi Sakamoto
 */

#समावेश "./ff.h"

स्थिर अक्षर *snd_ff_proc_get_clk_label(क्रमागत snd_ff_घड़ी_src src)
अणु
	अटल स्थिर अक्षर *स्थिर labels[] = अणु
		"Internal",
		"S/PDIF",
		"ADAT1",
		"ADAT2",
		"Word",
		"LTC",
	पूर्ण;

	अगर (src >= ARRAY_SIZE(labels))
		वापस शून्य;

	वापस labels[src];
पूर्ण

अटल व्योम proc_dump_status(काष्ठा snd_info_entry *entry,
			     काष्ठा snd_info_buffer *buffer)
अणु
	काष्ठा snd_ff *ff = entry->निजी_data;

	ff->spec->protocol->dump_status(ff, buffer);
पूर्ण

अटल व्योम add_node(काष्ठा snd_ff *ff, काष्ठा snd_info_entry *root,
		     स्थिर अक्षर *name,
		     व्योम (*op)(काष्ठा snd_info_entry *e,
				काष्ठा snd_info_buffer *b))
अणु
	काष्ठा snd_info_entry *entry;

	entry = snd_info_create_card_entry(ff->card, name, root);
	अगर (entry)
		snd_info_set_text_ops(entry, ff, op);
पूर्ण

व्योम snd_ff_proc_init(काष्ठा snd_ff *ff)
अणु
	काष्ठा snd_info_entry *root;

	/*
	 * All nodes are स्वतःmatically हटाओd at snd_card_disconnect(),
	 * by following to link list.
	 */
	root = snd_info_create_card_entry(ff->card, "firewire",
					  ff->card->proc_root);
	अगर (root == शून्य)
		वापस;
	root->mode = S_IFसूची | 0555;

	add_node(ff, root, "status", proc_dump_status);
पूर्ण
