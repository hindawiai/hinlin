<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * bebob_proc.c - a part of driver क्रम BeBoB based devices
 *
 * Copyright (c) 2013-2014 Takashi Sakamoto
 */

#समावेश "./bebob.h"

/* contents of inक्रमmation रेजिस्टर */
काष्ठा hw_info अणु
	u64 manufacturer;
	u32 protocol_ver;
	u32 bld_ver;
	u32 guid[2];
	u32 model_id;
	u32 model_rev;
	u64 fw_date;
	u64 fw_समय;
	u32 fw_id;
	u32 fw_ver;
	u32 base_addr;
	u32 max_size;
	u64 bld_date;
	u64 bld_समय;
/* may not used in product
	u64 dbg_date;
	u64 dbg_समय;
	u32 dbg_id;
	u32 dbg_version;
*/
पूर्ण __packed;

अटल व्योम
proc_पढ़ो_hw_info(काष्ठा snd_info_entry *entry,
		  काष्ठा snd_info_buffer *buffer)
अणु
	काष्ठा snd_bebob *bebob = entry->निजी_data;
	काष्ठा hw_info *info;

	info = kzalloc(माप(काष्ठा hw_info), GFP_KERNEL);
	अगर (info == शून्य)
		वापस;

	अगर (snd_bebob_पढ़ो_block(bebob->unit, 0,
				   info, माप(काष्ठा hw_info)) < 0)
		जाओ end;

	snd_iम_लिखो(buffer, "Manufacturer:\t%.8s\n",
		    (अक्षर *)&info->manufacturer);
	snd_iम_लिखो(buffer, "Protocol Ver:\t%d\n", info->protocol_ver);
	snd_iम_लिखो(buffer, "Build Ver:\t%d\n", info->bld_ver);
	snd_iम_लिखो(buffer, "GUID:\t\t0x%.8X%.8X\n",
		    info->guid[0], info->guid[1]);
	snd_iम_लिखो(buffer, "Model ID:\t0x%02X\n", info->model_id);
	snd_iम_लिखो(buffer, "Model Rev:\t%d\n", info->model_rev);
	snd_iम_लिखो(buffer, "Firmware Date:\t%.8s\n", (अक्षर *)&info->fw_date);
	snd_iम_लिखो(buffer, "Firmware Time:\t%.8s\n", (अक्षर *)&info->fw_समय);
	snd_iम_लिखो(buffer, "Firmware ID:\t0x%X\n", info->fw_id);
	snd_iम_लिखो(buffer, "Firmware Ver:\t%d\n", info->fw_ver);
	snd_iम_लिखो(buffer, "Base Addr:\t0x%X\n", info->base_addr);
	snd_iम_लिखो(buffer, "Max Size:\t%d\n", info->max_size);
	snd_iम_लिखो(buffer, "Loader Date:\t%.8s\n", (अक्षर *)&info->bld_date);
	snd_iम_लिखो(buffer, "Loader Time:\t%.8s\n", (अक्षर *)&info->bld_समय);

end:
	kमुक्त(info);
पूर्ण

अटल व्योम
proc_पढ़ो_meters(काष्ठा snd_info_entry *entry,
		 काष्ठा snd_info_buffer *buffer)
अणु
	काष्ठा snd_bebob *bebob = entry->निजी_data;
	स्थिर काष्ठा snd_bebob_meter_spec *spec = bebob->spec->meter;
	u32 *buf;
	अचिन्हित पूर्णांक i, c, channels, size;

	अगर (spec == शून्य)
		वापस;

	channels = spec->num * 2;
	size = channels * माप(u32);
	buf = kदो_स्मृति(size, GFP_KERNEL);
	अगर (buf == शून्य)
		वापस;

	अगर (spec->get(bebob, buf, size) < 0)
		जाओ end;

	क्रम (i = 0, c = 1; i < channels; i++) अणु
		snd_iम_लिखो(buffer, "%s %d:\t%d\n",
			    spec->labels[i / 2], c++, buf[i]);
		अगर ((i + 1 < channels - 1) &&
		    (म_भेद(spec->labels[i / 2],
			    spec->labels[(i + 1) / 2]) != 0))
			c = 1;
	पूर्ण
end:
	kमुक्त(buf);
पूर्ण

अटल व्योम
proc_पढ़ो_क्रमmation(काष्ठा snd_info_entry *entry,
		काष्ठा snd_info_buffer *buffer)
अणु
	काष्ठा snd_bebob *bebob = entry->निजी_data;
	काष्ठा snd_bebob_stream_क्रमmation *क्रमmation;
	अचिन्हित पूर्णांक i;

	snd_iम_लिखो(buffer, "Output Stream from device:\n");
	snd_iम_लिखो(buffer, "\tRate\tPCM\tMIDI\n");
	क्रमmation = bebob->tx_stream_क्रमmations;
	क्रम (i = 0; i < SND_BEBOB_STRM_FMT_ENTRIES; i++) अणु
		snd_iम_लिखो(buffer,
			    "\t%d\t%d\t%d\n", snd_bebob_rate_table[i],
			    क्रमmation[i].pcm, क्रमmation[i].midi);
	पूर्ण

	snd_iम_लिखो(buffer, "Input Stream to device:\n");
	snd_iम_लिखो(buffer, "\tRate\tPCM\tMIDI\n");
	क्रमmation = bebob->rx_stream_क्रमmations;
	क्रम (i = 0; i < SND_BEBOB_STRM_FMT_ENTRIES; i++) अणु
		snd_iम_लिखो(buffer,
			    "\t%d\t%d\t%d\n", snd_bebob_rate_table[i],
			    क्रमmation[i].pcm, क्रमmation[i].midi);
	पूर्ण
पूर्ण

अटल व्योम
proc_पढ़ो_घड़ी(काष्ठा snd_info_entry *entry,
		काष्ठा snd_info_buffer *buffer)
अणु
	अटल स्थिर अक्षर *स्थिर clk_labels[] = अणु
		"Internal",
		"External",
		"SYT-Match",
	पूर्ण;
	काष्ठा snd_bebob *bebob = entry->निजी_data;
	स्थिर काष्ठा snd_bebob_rate_spec *rate_spec = bebob->spec->rate;
	स्थिर काष्ठा snd_bebob_घड़ी_spec *clk_spec = bebob->spec->घड़ी;
	क्रमागत snd_bebob_घड़ी_प्रकारype src;
	अचिन्हित पूर्णांक rate;

	अगर (rate_spec->get(bebob, &rate) >= 0)
		snd_iम_लिखो(buffer, "Sampling rate: %d\n", rate);

	अगर (snd_bebob_stream_get_घड़ी_src(bebob, &src) >= 0) अणु
		अगर (clk_spec)
			snd_iम_लिखो(buffer, "Clock Source: %s\n",
				    clk_labels[src]);
		अन्यथा
			snd_iम_लिखो(buffer, "Clock Source: %s (MSU-dest: %d)\n",
				    clk_labels[src], bebob->sync_input_plug);
	पूर्ण
पूर्ण

अटल व्योम
add_node(काष्ठा snd_bebob *bebob, काष्ठा snd_info_entry *root, स्थिर अक्षर *name,
	 व्योम (*op)(काष्ठा snd_info_entry *e, काष्ठा snd_info_buffer *b))
अणु
	काष्ठा snd_info_entry *entry;

	entry = snd_info_create_card_entry(bebob->card, name, root);
	अगर (entry)
		snd_info_set_text_ops(entry, bebob, op);
पूर्ण

व्योम snd_bebob_proc_init(काष्ठा snd_bebob *bebob)
अणु
	काष्ठा snd_info_entry *root;

	/*
	 * All nodes are स्वतःmatically हटाओd at snd_card_disconnect(),
	 * by following to link list.
	 */
	root = snd_info_create_card_entry(bebob->card, "firewire",
					  bebob->card->proc_root);
	अगर (root == शून्य)
		वापस;
	root->mode = S_IFसूची | 0555;

	add_node(bebob, root, "clock", proc_पढ़ो_घड़ी);
	add_node(bebob, root, "firmware", proc_पढ़ो_hw_info);
	add_node(bebob, root, "formation", proc_पढ़ो_क्रमmation);

	अगर (bebob->spec->meter != शून्य)
		add_node(bebob, root, "meter", proc_पढ़ो_meters);
पूर्ण
