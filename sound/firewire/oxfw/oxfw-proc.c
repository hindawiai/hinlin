<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * oxfw_proc.c - a part of driver क्रम OXFW970/971 based devices
 *
 * Copyright (c) 2014 Takashi Sakamoto
 */

#समावेश "./oxfw.h"

अटल व्योम proc_पढ़ो_क्रमmation(काष्ठा snd_info_entry *entry,
				काष्ठा snd_info_buffer *buffer)
अणु
	काष्ठा snd_oxfw *oxfw = entry->निजी_data;
	काष्ठा snd_oxfw_stream_क्रमmation क्रमmation, curr;
	u8 *क्रमmat;
	अक्षर flag;
	पूर्णांक i, err;

	/* Show input. */
	err = snd_oxfw_stream_get_current_क्रमmation(oxfw,
						    AVC_GENERAL_PLUG_सूची_IN,
						    &curr);
	अगर (err < 0)
		वापस;

	snd_iम_लिखो(buffer, "Input Stream to device:\n");
	snd_iम_लिखो(buffer, "\tRate\tPCM\tMIDI\n");
	क्रम (i = 0; i < SND_OXFW_STREAM_FORMAT_ENTRIES; i++) अणु
		क्रमmat = oxfw->rx_stream_क्रमmats[i];
		अगर (क्रमmat == शून्य)
			जारी;

		err = snd_oxfw_stream_parse_क्रमmat(क्रमmat, &क्रमmation);
		अगर (err < 0)
			जारी;

		अगर (स_भेद(&क्रमmation, &curr, माप(curr)) == 0)
			flag = '*';
		अन्यथा
			flag = ' ';

		snd_iम_लिखो(buffer, "%c\t%d\t%d\t%d\n", flag,
			    क्रमmation.rate, क्रमmation.pcm, क्रमmation.midi);
	पूर्ण

	अगर (!oxfw->has_output)
		वापस;

	/* Show output. */
	err = snd_oxfw_stream_get_current_क्रमmation(oxfw,
						    AVC_GENERAL_PLUG_सूची_OUT,
						    &curr);
	अगर (err < 0)
		वापस;

	snd_iम_लिखो(buffer, "Output Stream from device:\n");
	snd_iम_लिखो(buffer, "\tRate\tPCM\tMIDI\n");
	क्रम (i = 0; i < SND_OXFW_STREAM_FORMAT_ENTRIES; i++) अणु
		क्रमmat = oxfw->tx_stream_क्रमmats[i];
		अगर (क्रमmat == शून्य)
			जारी;

		err = snd_oxfw_stream_parse_क्रमmat(क्रमmat, &क्रमmation);
		अगर (err < 0)
			जारी;

		अगर (स_भेद(&क्रमmation, &curr, माप(curr)) == 0)
			flag = '*';
		अन्यथा
			flag = ' ';

		snd_iम_लिखो(buffer, "%c\t%d\t%d\t%d\n", flag,
			    क्रमmation.rate, क्रमmation.pcm, क्रमmation.midi);
	पूर्ण
पूर्ण

अटल व्योम add_node(काष्ठा snd_oxfw *oxfw, काष्ठा snd_info_entry *root,
		     स्थिर अक्षर *name,
		     व्योम (*op)(काष्ठा snd_info_entry *e,
				काष्ठा snd_info_buffer *b))
अणु
	काष्ठा snd_info_entry *entry;

	entry = snd_info_create_card_entry(oxfw->card, name, root);
	अगर (entry)
		snd_info_set_text_ops(entry, oxfw, op);
पूर्ण

व्योम snd_oxfw_proc_init(काष्ठा snd_oxfw *oxfw)
अणु
	काष्ठा snd_info_entry *root;

	/*
	 * All nodes are स्वतःmatically हटाओd at snd_card_disconnect(),
	 * by following to link list.
	 */
	root = snd_info_create_card_entry(oxfw->card, "firewire",
					  oxfw->card->proc_root);
	अगर (root == शून्य)
		वापस;
	root->mode = S_IFसूची | 0555;

	add_node(oxfw, root, "formation", proc_पढ़ो_क्रमmation);
पूर्ण
