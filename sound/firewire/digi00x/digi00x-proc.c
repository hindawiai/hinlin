<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * digi00x-proc.c - a part of driver क्रम Digidesign Digi 002/003 family
 *
 * Copyright (c) 2014-2015 Takashi Sakamoto
 */

#समावेश "digi00x.h"

अटल पूर्णांक get_optical_अगरace_mode(काष्ठा snd_dg00x *dg00x,
				  क्रमागत snd_dg00x_optical_mode *mode)
अणु
	__be32 data;
	पूर्णांक err;

	err = snd_fw_transaction(dg00x->unit, TCODE_READ_QUADLET_REQUEST,
				 DG00X_ADDR_BASE + DG00X_OFFSET_OPT_IFACE_MODE,
				 &data, माप(data), 0);
	अगर (err >= 0)
		*mode = be32_to_cpu(data) & 0x01;

	वापस err;
पूर्ण

अटल व्योम proc_पढ़ो_घड़ी(काष्ठा snd_info_entry *entry,
			    काष्ठा snd_info_buffer *buf)
अणु
	अटल स्थिर अक्षर *स्थिर source_name[] = अणु
		[SND_DG00X_CLOCK_INTERNAL] = "internal",
		[SND_DG00X_CLOCK_SPDIF] = "s/pdif",
		[SND_DG00X_CLOCK_ADAT] = "adat",
		[SND_DG00X_CLOCK_WORD] = "word clock",
	पूर्ण;
	अटल स्थिर अक्षर *स्थिर optical_name[] = अणु
		[SND_DG00X_OPT_IFACE_MODE_ADAT] = "adat",
		[SND_DG00X_OPT_IFACE_MODE_SPDIF] = "s/pdif",
	पूर्ण;
	काष्ठा snd_dg00x *dg00x = entry->निजी_data;
	क्रमागत snd_dg00x_optical_mode mode;
	अचिन्हित पूर्णांक rate;
	क्रमागत snd_dg00x_घड़ी घड़ी;
	bool detect;

	अगर (get_optical_अगरace_mode(dg00x, &mode) < 0)
		वापस;
	अगर (snd_dg00x_stream_get_local_rate(dg00x, &rate) < 0)
		वापस;
	अगर (snd_dg00x_stream_get_घड़ी(dg00x, &घड़ी) < 0)
		वापस;

	snd_iम_लिखो(buf, "Optical mode: %s\n", optical_name[mode]);
	snd_iम_लिखो(buf, "Sampling Rate: %d\n", rate);
	snd_iम_लिखो(buf, "Clock Source: %s\n", source_name[घड़ी]);

	अगर (घड़ी == SND_DG00X_CLOCK_INTERNAL)
		वापस;

	अगर (snd_dg00x_stream_check_बाह्यal_घड़ी(dg00x, &detect) < 0)
		वापस;
	snd_iम_लिखो(buf, "External source: %s\n", detect ? "detected" : "not");
	अगर (!detect)
		वापस;

	अगर (snd_dg00x_stream_get_बाह्यal_rate(dg00x, &rate) >= 0)
		snd_iम_लिखो(buf, "External sampling rate: %d\n", rate);
पूर्ण

व्योम snd_dg00x_proc_init(काष्ठा snd_dg00x *dg00x)
अणु
	काष्ठा snd_info_entry *root, *entry;

	/*
	 * All nodes are स्वतःmatically हटाओd at snd_card_disconnect(),
	 * by following to link list.
	 */
	root = snd_info_create_card_entry(dg00x->card, "firewire",
					  dg00x->card->proc_root);
	अगर (root == शून्य)
		वापस;

	root->mode = S_IFसूची | 0555;

	entry = snd_info_create_card_entry(dg00x->card, "clock", root);
	अगर (entry)
		snd_info_set_text_ops(entry, dg00x, proc_पढ़ो_घड़ी);
पूर्ण
