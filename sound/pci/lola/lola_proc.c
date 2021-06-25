<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *  Support क्रम Digigram Lola PCI-e boards
 *
 *  Copyright (c) 2011 Takashi Iwai <tiwai@suse.de>
 */

#समावेश <linux/kernel.h>
#समावेश <linux/init.h>
#समावेश <linux/पन.स>
#समावेश <sound/core.h>
#समावेश <sound/info.h>
#समावेश <sound/pcm.h>
#समावेश "lola.h"

अटल व्योम prपूर्णांक_audio_widget(काष्ठा snd_info_buffer *buffer,
			       काष्ठा lola *chip, पूर्णांक nid, स्थिर अक्षर *name)
अणु
	अचिन्हित पूर्णांक val;

	lola_पढ़ो_param(chip, nid, LOLA_PAR_AUDIO_WIDGET_CAP, &val);
	snd_iम_लिखो(buffer, "Node 0x%02x %s wcaps 0x%x\n", nid, name, val);
	lola_पढ़ो_param(chip, nid, LOLA_PAR_STREAM_FORMATS, &val);
	snd_iम_लिखो(buffer, "  Formats: 0x%x\n", val);
पूर्ण

अटल व्योम prपूर्णांक_pin_widget(काष्ठा snd_info_buffer *buffer,
			     काष्ठा lola *chip, पूर्णांक nid, अचिन्हित पूर्णांक ampcap,
			     स्थिर अक्षर *name)
अणु
	अचिन्हित पूर्णांक val;

	lola_पढ़ो_param(chip, nid, LOLA_PAR_AUDIO_WIDGET_CAP, &val);
	snd_iम_लिखो(buffer, "Node 0x%02x %s wcaps 0x%x\n", nid, name, val);
	अगर (val == 0x00400200)
		वापस;
	lola_पढ़ो_param(chip, nid, ampcap, &val);
	snd_iम_लिखो(buffer, "  Amp-Caps: 0x%x\n", val);
	snd_iम_लिखो(buffer, "    mute=%d, step-size=%d, steps=%d, ofs=%d\n",
		    LOLA_AMP_MUTE_CAPABLE(val),
		    LOLA_AMP_STEP_SIZE(val),
		    LOLA_AMP_NUM_STEPS(val),
		    LOLA_AMP_OFFSET(val));
	lola_codec_पढ़ो(chip, nid, LOLA_VERB_GET_MAX_LEVEL, 0, 0, &val, शून्य);
	snd_iम_लिखो(buffer, "  Max-level: 0x%x\n", val);
पूर्ण

अटल व्योम prपूर्णांक_घड़ी_widget(काष्ठा snd_info_buffer *buffer,
			       काष्ठा lola *chip, पूर्णांक nid)
अणु
	पूर्णांक i, j, num_घड़ीs;
	अचिन्हित पूर्णांक val;

	lola_पढ़ो_param(chip, nid, LOLA_PAR_AUDIO_WIDGET_CAP, &val);
	snd_iम_लिखो(buffer, "Node 0x%02x [Clock] wcaps 0x%x\n", nid, val);
	num_घड़ीs = val & 0xff;
	क्रम (i = 0; i < num_घड़ीs; i += 4) अणु
		अचिन्हित पूर्णांक res_ex;
		अचिन्हित लघु items[4];
		स्थिर अक्षर *name;

		lola_codec_पढ़ो(chip, nid, LOLA_VERB_GET_CLOCK_LIST,
				i, 0, &val, &res_ex);
		items[0] = val & 0xfff;
		items[1] = (val >> 16) & 0xfff;
		items[2] = res_ex & 0xfff;
		items[3] = (res_ex >> 16) & 0xfff;
		क्रम (j = 0; j < 4; j++) अणु
			अचिन्हित अक्षर type = items[j] >> 8;
			अचिन्हित पूर्णांक freq = items[j] & 0xff;
			अगर (i + j >= num_घड़ीs)
				अवरोध;
			अगर (type == LOLA_CLOCK_TYPE_INTERNAL) अणु
				name = "Internal";
				freq = lola_sample_rate_convert(freq);
			पूर्ण अन्यथा अगर (type == LOLA_CLOCK_TYPE_VIDEO) अणु
				name = "Video";
				freq = lola_sample_rate_convert(freq);
			पूर्ण अन्यथा अणु
				name = "Other";
			पूर्ण
			snd_iम_लिखो(buffer, "  Clock %d: Type %d:%s, freq=%d\n",
				    i + j, type, name, freq);
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम prपूर्णांक_mixer_widget(काष्ठा snd_info_buffer *buffer,
			       काष्ठा lola *chip, पूर्णांक nid)
अणु
	अचिन्हित पूर्णांक val;

	lola_पढ़ो_param(chip, nid, LOLA_PAR_AUDIO_WIDGET_CAP, &val);
	snd_iम_लिखो(buffer, "Node 0x%02x [Mixer] wcaps 0x%x\n", nid, val);
पूर्ण

अटल व्योम lola_proc_codec_पढ़ो(काष्ठा snd_info_entry *entry,
				 काष्ठा snd_info_buffer *buffer)
अणु
	काष्ठा lola *chip = entry->निजी_data;
	अचिन्हित पूर्णांक val;
	पूर्णांक i, nid;

	lola_पढ़ो_param(chip, 0, LOLA_PAR_VENDOR_ID, &val);
	snd_iम_लिखो(buffer, "Vendor: 0x%08x\n", val);
	lola_पढ़ो_param(chip, 1, LOLA_PAR_FUNCTION_TYPE, &val);
	snd_iम_लिखो(buffer, "Function Type: %d\n", val);
	lola_पढ़ो_param(chip, 1, LOLA_PAR_SPECIFIC_CAPS, &val);
	snd_iम_लिखो(buffer, "Specific-Caps: 0x%08x\n", val);
	snd_iम_लिखो(buffer, "  Pins-In %d, Pins-Out %d\n",
		    chip->pin[CAPT].num_pins, chip->pin[PLAY].num_pins);
	nid = 2;
	क्रम (i = 0; i < chip->pcm[CAPT].num_streams; i++, nid++)
		prपूर्णांक_audio_widget(buffer, chip, nid, "[Audio-In]");
	क्रम (i = 0; i < chip->pcm[PLAY].num_streams; i++, nid++)
		prपूर्णांक_audio_widget(buffer, chip, nid, "[Audio-Out]");
	क्रम (i = 0; i < chip->pin[CAPT].num_pins; i++, nid++)
		prपूर्णांक_pin_widget(buffer, chip, nid, LOLA_PAR_AMP_IN_CAP,
				 "[Pin-In]");
	क्रम (i = 0; i < chip->pin[PLAY].num_pins; i++, nid++)
		prपूर्णांक_pin_widget(buffer, chip, nid, LOLA_PAR_AMP_OUT_CAP,
				 "[Pin-Out]");
	अगर (LOLA_AFG_CLOCK_WIDGET_PRESENT(chip->lola_caps)) अणु
		prपूर्णांक_घड़ी_widget(buffer, chip, nid);
		nid++;
	पूर्ण
	अगर (LOLA_AFG_MIXER_WIDGET_PRESENT(chip->lola_caps)) अणु
		prपूर्णांक_mixer_widget(buffer, chip, nid);
		nid++;
	पूर्ण
पूर्ण

/* direct codec access क्रम debugging */
अटल व्योम lola_proc_codec_rw_ग_लिखो(काष्ठा snd_info_entry *entry,
				     काष्ठा snd_info_buffer *buffer)
अणु
	काष्ठा lola *chip = entry->निजी_data;
	अक्षर line[64];
	अचिन्हित पूर्णांक id, verb, data, extdata;
	जबतक (!snd_info_get_line(buffer, line, माप(line))) अणु
		अगर (माला_पूछो(line, "%u %u %u %u", &id, &verb, &data, &extdata) != 4)
			जारी;
		lola_codec_पढ़ो(chip, id, verb, data, extdata,
				&chip->debug_res,
				&chip->debug_res_ex);
	पूर्ण
पूर्ण

अटल व्योम lola_proc_codec_rw_पढ़ो(काष्ठा snd_info_entry *entry,
				    काष्ठा snd_info_buffer *buffer)
अणु
	काष्ठा lola *chip = entry->निजी_data;
	snd_iम_लिखो(buffer, "0x%x 0x%x\n", chip->debug_res, chip->debug_res_ex);
पूर्ण

/*
 * dump some रेजिस्टरs
 */
अटल व्योम lola_proc_regs_पढ़ो(काष्ठा snd_info_entry *entry,
				काष्ठा snd_info_buffer *buffer)
अणु
	काष्ठा lola *chip = entry->निजी_data;
	पूर्णांक i;

	क्रम (i = 0; i < 0x40; i += 4) अणु
		snd_iम_लिखो(buffer, "BAR0 %02x: %08x\n", i,
			    पढ़ोl(chip->bar[BAR0].remap_addr + i));
	पूर्ण
	snd_iम_लिखो(buffer, "\n");
	क्रम (i = 0; i < 0x30; i += 4) अणु
		snd_iम_लिखो(buffer, "BAR1 %02x: %08x\n", i,
			    पढ़ोl(chip->bar[BAR1].remap_addr + i));
	पूर्ण
	snd_iम_लिखो(buffer, "\n");
	क्रम (i = 0x80; i < 0xa0; i += 4) अणु
		snd_iम_लिखो(buffer, "BAR1 %02x: %08x\n", i,
			    पढ़ोl(chip->bar[BAR1].remap_addr + i));
	पूर्ण
	snd_iम_लिखो(buffer, "\n");
	क्रम (i = 0; i < 32; i++) अणु
		snd_iम_लिखो(buffer, "DSD %02x STS  %08x\n", i,
			    lola_dsd_पढ़ो(chip, i, STS));
		snd_iम_लिखो(buffer, "DSD %02x LPIB %08x\n", i,
			    lola_dsd_पढ़ो(chip, i, LPIB));
		snd_iम_लिखो(buffer, "DSD %02x CTL  %08x\n", i,
			    lola_dsd_पढ़ो(chip, i, CTL));
		snd_iम_लिखो(buffer, "DSD %02x LVIL %08x\n", i,
			    lola_dsd_पढ़ो(chip, i, LVI));
		snd_iम_लिखो(buffer, "DSD %02x BDPL %08x\n", i,
			    lola_dsd_पढ़ो(chip, i, BDPL));
		snd_iम_लिखो(buffer, "DSD %02x BDPU %08x\n", i,
			    lola_dsd_पढ़ो(chip, i, BDPU));
	पूर्ण
पूर्ण

व्योम lola_proc_debug_new(काष्ठा lola *chip)
अणु
	snd_card_ro_proc_new(chip->card, "codec", chip, lola_proc_codec_पढ़ो);
	snd_card_rw_proc_new(chip->card, "codec_rw", chip,
			     lola_proc_codec_rw_पढ़ो,
			     lola_proc_codec_rw_ग_लिखो);
	snd_card_ro_proc_new(chip->card, "regs", chip, lola_proc_regs_पढ़ो);
पूर्ण
