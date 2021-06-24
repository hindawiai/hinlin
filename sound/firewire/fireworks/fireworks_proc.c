<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * fireworks_proc.c - a part of driver क्रम Fireworks based devices
 *
 * Copyright (c) 2009-2010 Clemens Ladisch
 * Copyright (c) 2013-2014 Takashi Sakamoto
 */

#समावेश "./fireworks.h"

अटल अंतरभूत स्थिर अक्षर*
get_phys_name(काष्ठा snd_efw_phys_grp *grp, bool input)
अणु
	अटल स्थिर अक्षर *स्थिर ch_type[] = अणु
		"Analog", "S/PDIF", "ADAT", "S/PDIF or ADAT", "Mirroring",
		"Headphones", "I2S", "Guitar", "Pirzo Guitar", "Guitar String",
	पूर्ण;

	अगर (grp->type < ARRAY_SIZE(ch_type))
		वापस ch_type[grp->type];
	अन्यथा अगर (input)
		वापस "Input";
	अन्यथा
		वापस "Output";
पूर्ण

अटल व्योम
proc_पढ़ो_hwinfo(काष्ठा snd_info_entry *entry, काष्ठा snd_info_buffer *buffer)
अणु
	काष्ठा snd_efw *efw = entry->निजी_data;
	अचिन्हित लघु i;
	काष्ठा snd_efw_hwinfo *hwinfo;

	hwinfo = kदो_स्मृति(माप(काष्ठा snd_efw_hwinfo), GFP_KERNEL);
	अगर (hwinfo == शून्य)
		वापस;

	अगर (snd_efw_command_get_hwinfo(efw, hwinfo) < 0)
		जाओ end;

	snd_iम_लिखो(buffer, "guid_hi: 0x%X\n", hwinfo->guid_hi);
	snd_iम_लिखो(buffer, "guid_lo: 0x%X\n", hwinfo->guid_lo);
	snd_iम_लिखो(buffer, "type: 0x%X\n", hwinfo->type);
	snd_iम_लिखो(buffer, "version: 0x%X\n", hwinfo->version);
	snd_iम_लिखो(buffer, "vendor_name: %s\n", hwinfo->venकरोr_name);
	snd_iम_लिखो(buffer, "model_name: %s\n", hwinfo->model_name);

	snd_iम_लिखो(buffer, "dsp_version: 0x%X\n", hwinfo->dsp_version);
	snd_iम_लिखो(buffer, "arm_version: 0x%X\n", hwinfo->arm_version);
	snd_iम_लिखो(buffer, "fpga_version: 0x%X\n", hwinfo->fpga_version);

	snd_iम_लिखो(buffer, "flags: 0x%X\n", hwinfo->flags);

	snd_iम_लिखो(buffer, "max_sample_rate: 0x%X\n", hwinfo->max_sample_rate);
	snd_iम_लिखो(buffer, "min_sample_rate: 0x%X\n", hwinfo->min_sample_rate);
	snd_iम_लिखो(buffer, "supported_clock: 0x%X\n",
		    hwinfo->supported_घड़ीs);

	snd_iम_लिखो(buffer, "phys out: 0x%X\n", hwinfo->phys_out);
	snd_iम_लिखो(buffer, "phys in: 0x%X\n", hwinfo->phys_in);

	snd_iम_लिखो(buffer, "phys in grps: 0x%X\n",
		    hwinfo->phys_in_grp_count);
	क्रम (i = 0; i < hwinfo->phys_in_grp_count; i++) अणु
		snd_iम_लिखो(buffer,
			    "phys in grp[%d]: type 0x%X, count 0x%X\n",
			    i, hwinfo->phys_out_grps[i].type,
			    hwinfo->phys_out_grps[i].count);
	पूर्ण

	snd_iम_लिखो(buffer, "phys out grps: 0x%X\n",
		    hwinfo->phys_out_grp_count);
	क्रम (i = 0; i < hwinfo->phys_out_grp_count; i++) अणु
		snd_iम_लिखो(buffer,
			    "phys out grps[%d]: type 0x%X, count 0x%X\n",
			    i, hwinfo->phys_out_grps[i].type,
			    hwinfo->phys_out_grps[i].count);
	पूर्ण

	snd_iम_लिखो(buffer, "amdtp rx pcm channels 1x: 0x%X\n",
		    hwinfo->amdtp_rx_pcm_channels);
	snd_iम_लिखो(buffer, "amdtp tx pcm channels 1x: 0x%X\n",
		    hwinfo->amdtp_tx_pcm_channels);
	snd_iम_लिखो(buffer, "amdtp rx pcm channels 2x: 0x%X\n",
		    hwinfo->amdtp_rx_pcm_channels_2x);
	snd_iम_लिखो(buffer, "amdtp tx pcm channels 2x: 0x%X\n",
		    hwinfo->amdtp_tx_pcm_channels_2x);
	snd_iम_लिखो(buffer, "amdtp rx pcm channels 4x: 0x%X\n",
		    hwinfo->amdtp_rx_pcm_channels_4x);
	snd_iम_लिखो(buffer, "amdtp tx pcm channels 4x: 0x%X\n",
		    hwinfo->amdtp_tx_pcm_channels_4x);

	snd_iम_लिखो(buffer, "midi out ports: 0x%X\n", hwinfo->midi_out_ports);
	snd_iम_लिखो(buffer, "midi in ports: 0x%X\n", hwinfo->midi_in_ports);

	snd_iम_लिखो(buffer, "mixer playback channels: 0x%X\n",
		    hwinfo->mixer_playback_channels);
	snd_iम_लिखो(buffer, "mixer capture channels: 0x%X\n",
		    hwinfo->mixer_capture_channels);
end:
	kमुक्त(hwinfo);
पूर्ण

अटल व्योम
proc_पढ़ो_घड़ी(काष्ठा snd_info_entry *entry, काष्ठा snd_info_buffer *buffer)
अणु
	काष्ठा snd_efw *efw = entry->निजी_data;
	क्रमागत snd_efw_घड़ी_source घड़ी_source;
	अचिन्हित पूर्णांक sampling_rate;

	अगर (snd_efw_command_get_घड़ी_source(efw, &घड़ी_source) < 0)
		वापस;

	अगर (snd_efw_command_get_sampling_rate(efw, &sampling_rate) < 0)
		वापस;

	snd_iम_लिखो(buffer, "Clock Source: %d\n", घड़ी_source);
	snd_iम_लिखो(buffer, "Sampling Rate: %d\n", sampling_rate);
पूर्ण

/*
 * NOTE:
 *  dB = 20 * log10(linear / 0x01000000)
 *  -144.0 dB when linear is 0
 */
अटल व्योम
proc_पढ़ो_phys_meters(काष्ठा snd_info_entry *entry,
		      काष्ठा snd_info_buffer *buffer)
अणु
	काष्ठा snd_efw *efw = entry->निजी_data;
	काष्ठा snd_efw_phys_meters *meters;
	अचिन्हित पूर्णांक g, c, m, max, size;
	स्थिर अक्षर *name;
	u32 *linear;
	पूर्णांक err;

	size = माप(काष्ठा snd_efw_phys_meters) +
	       (efw->phys_in + efw->phys_out) * माप(u32);
	meters = kzalloc(size, GFP_KERNEL);
	अगर (meters == शून्य)
		वापस;

	err = snd_efw_command_get_phys_meters(efw, meters, size);
	अगर (err < 0)
		जाओ end;

	snd_iम_लिखो(buffer, "Physical Meters:\n");

	m = 0;
	max = min(efw->phys_out, meters->out_meters);
	linear = meters->values;
	snd_iम_लिखो(buffer, " %d Outputs:\n", max);
	क्रम (g = 0; g < efw->phys_out_grp_count; g++) अणु
		name = get_phys_name(&efw->phys_out_grps[g], false);
		क्रम (c = 0; c < efw->phys_out_grps[g].count; c++) अणु
			अगर (m < max)
				snd_iम_लिखो(buffer, "\t%s [%d]: %d\n",
					    name, c, linear[m++]);
		पूर्ण
	पूर्ण

	m = 0;
	max = min(efw->phys_in, meters->in_meters);
	linear = meters->values + meters->out_meters;
	snd_iम_लिखो(buffer, " %d Inputs:\n", max);
	क्रम (g = 0; g < efw->phys_in_grp_count; g++) अणु
		name = get_phys_name(&efw->phys_in_grps[g], true);
		क्रम (c = 0; c < efw->phys_in_grps[g].count; c++)
			अगर (m < max)
				snd_iम_लिखो(buffer, "\t%s [%d]: %d\n",
					    name, c, linear[m++]);
	पूर्ण
end:
	kमुक्त(meters);
पूर्ण

अटल व्योम
proc_पढ़ो_queues_state(काष्ठा snd_info_entry *entry,
		       काष्ठा snd_info_buffer *buffer)
अणु
	काष्ठा snd_efw *efw = entry->निजी_data;
	अचिन्हित पूर्णांक consumed;

	अगर (efw->pull_ptr > efw->push_ptr)
		consumed = snd_efw_resp_buf_size -
			   (अचिन्हित पूर्णांक)(efw->pull_ptr - efw->push_ptr);
	अन्यथा
		consumed = (अचिन्हित पूर्णांक)(efw->push_ptr - efw->pull_ptr);

	snd_iम_लिखो(buffer, "%d/%d\n",
		    consumed, snd_efw_resp_buf_size);
पूर्ण

अटल व्योम
add_node(काष्ठा snd_efw *efw, काष्ठा snd_info_entry *root, स्थिर अक्षर *name,
	 व्योम (*op)(काष्ठा snd_info_entry *e, काष्ठा snd_info_buffer *b))
अणु
	काष्ठा snd_info_entry *entry;

	entry = snd_info_create_card_entry(efw->card, name, root);
	अगर (entry)
		snd_info_set_text_ops(entry, efw, op);
पूर्ण

व्योम snd_efw_proc_init(काष्ठा snd_efw *efw)
अणु
	काष्ठा snd_info_entry *root;

	/*
	 * All nodes are स्वतःmatically हटाओd at snd_card_disconnect(),
	 * by following to link list.
	 */
	root = snd_info_create_card_entry(efw->card, "firewire",
					  efw->card->proc_root);
	अगर (root == शून्य)
		वापस;
	root->mode = S_IFसूची | 0555;

	add_node(efw, root, "clock", proc_पढ़ो_घड़ी);
	add_node(efw, root, "firmware", proc_पढ़ो_hwinfo);
	add_node(efw, root, "meters", proc_पढ़ो_phys_meters);
	add_node(efw, root, "queues", proc_पढ़ो_queues_state);
पूर्ण
