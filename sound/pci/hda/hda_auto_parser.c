<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * BIOS स्वतः-parser helper functions क्रम HD-audio
 *
 * Copyright (c) 2012 Takashi Iwai <tiwai@suse.de>
 */

#समावेश <linux/slab.h>
#समावेश <linux/export.h>
#समावेश <linux/sort.h>
#समावेश <sound/core.h>
#समावेश <sound/hda_codec.h>
#समावेश "hda_local.h"
#समावेश "hda_auto_parser.h"

/*
 * Helper क्रम स्वतःmatic pin configuration
 */

अटल पूर्णांक is_in_nid_list(hda_nid_t nid, स्थिर hda_nid_t *list)
अणु
	क्रम (; *list; list++)
		अगर (*list == nid)
			वापस 1;
	वापस 0;
पूर्ण

/* a pair of input pin and its sequence */
काष्ठा स्वतः_out_pin अणु
	hda_nid_t pin;
	लघु seq;
पूर्ण;

अटल पूर्णांक compare_seq(स्थिर व्योम *ap, स्थिर व्योम *bp)
अणु
	स्थिर काष्ठा स्वतः_out_pin *a = ap;
	स्थिर काष्ठा स्वतः_out_pin *b = bp;
	वापस (पूर्णांक)(a->seq - b->seq);
पूर्ण

/*
 * Sort an associated group of pins according to their sequence numbers.
 * then store it to a pin array.
 */
अटल व्योम sort_pins_by_sequence(hda_nid_t *pins, काष्ठा स्वतः_out_pin *list,
				  पूर्णांक num_pins)
अणु
	पूर्णांक i;
	sort(list, num_pins, माप(list[0]), compare_seq, शून्य);
	क्रम (i = 0; i < num_pins; i++)
		pins[i] = list[i].pin;
पूर्ण


/* add the found input-pin to the cfg->inमाला_दो[] table */
अटल व्योम add_स्वतः_cfg_input_pin(काष्ठा hda_codec *codec, काष्ठा स्वतः_pin_cfg *cfg,
				   hda_nid_t nid, पूर्णांक type)
अणु
	अगर (cfg->num_inमाला_दो < AUTO_CFG_MAX_INS) अणु
		cfg->inमाला_दो[cfg->num_inमाला_दो].pin = nid;
		cfg->inमाला_दो[cfg->num_inमाला_दो].type = type;
		cfg->inमाला_दो[cfg->num_inमाला_दो].has_boost_on_pin =
			nid_has_volume(codec, nid, HDA_INPUT);
		cfg->num_inमाला_दो++;
	पूर्ण
पूर्ण

अटल पूर्णांक compare_input_type(स्थिर व्योम *ap, स्थिर व्योम *bp)
अणु
	स्थिर काष्ठा स्वतः_pin_cfg_item *a = ap;
	स्थिर काष्ठा स्वतः_pin_cfg_item *b = bp;
	अगर (a->type != b->type)
		वापस (पूर्णांक)(a->type - b->type);

	/* If has both hs_mic and hp_mic, pick the hs_mic ahead of hp_mic. */
	अगर (a->is_headset_mic && b->is_headphone_mic)
		वापस -1; /* करोn't swap */
	अन्यथा अगर (a->is_headphone_mic && b->is_headset_mic)
		वापस 1; /* swap */

	/* In हाल one has boost and the other one has not,
	   pick the one with boost first. */
	वापस (पूर्णांक)(b->has_boost_on_pin - a->has_boost_on_pin);
पूर्ण

/* Reorder the surround channels
 * ALSA sequence is front/surr/clfe/side
 * HDA sequence is:
 *    4-ch: front/surr  =>  OK as it is
 *    6-ch: front/clfe/surr
 *    8-ch: front/clfe/rear/side|fc
 */
अटल व्योम reorder_outमाला_दो(अचिन्हित पूर्णांक nums, hda_nid_t *pins)
अणु
	hda_nid_t nid;

	चयन (nums) अणु
	हाल 3:
	हाल 4:
		nid = pins[1];
		pins[1] = pins[2];
		pins[2] = nid;
		अवरोध;
	पूर्ण
पूर्ण

/* check whether the given pin has a proper pin I/O capability bit */
अटल bool check_pincap_validity(काष्ठा hda_codec *codec, hda_nid_t pin,
				  अचिन्हित पूर्णांक dev)
अणु
	अचिन्हित पूर्णांक pincap = snd_hda_query_pin_caps(codec, pin);

	/* some old hardware करोn't वापस the proper pincaps */
	अगर (!pincap)
		वापस true;

	चयन (dev) अणु
	हाल AC_JACK_LINE_OUT:
	हाल AC_JACK_SPEAKER:
	हाल AC_JACK_HP_OUT:
	हाल AC_JACK_SPDIF_OUT:
	हाल AC_JACK_DIG_OTHER_OUT:
		वापस !!(pincap & AC_PINCAP_OUT);
	शेष:
		वापस !!(pincap & AC_PINCAP_IN);
	पूर्ण
पूर्ण

अटल bool can_be_headset_mic(काष्ठा hda_codec *codec,
			       काष्ठा स्वतः_pin_cfg_item *item,
			       पूर्णांक seq_number)
अणु
	पूर्णांक attr;
	अचिन्हित पूर्णांक def_conf;
	अगर (item->type != AUTO_PIN_MIC)
		वापस false;

	अगर (item->is_headset_mic || item->is_headphone_mic)
		वापस false; /* Alपढ़ोy asचिन्हित */

	def_conf = snd_hda_codec_get_pincfg(codec, item->pin);
	attr = snd_hda_get_input_pin_attr(def_conf);
	अगर (attr <= INPUT_PIN_ATTR_DOCK)
		वापस false;

	अगर (seq_number >= 0) अणु
		पूर्णांक seq = get_defcfg_sequence(def_conf);
		अगर (seq != seq_number)
			वापस false;
	पूर्ण

	वापस true;
पूर्ण

/*
 * Parse all pin widमाला_लो and store the useful pin nids to cfg
 *
 * The number of line-outs or any primary output is stored in line_outs,
 * and the corresponding output pins are asचिन्हित to line_out_pins[],
 * in the order of front, rear, CLFE, side, ...
 *
 * If more extra outमाला_दो (speaker and headphone) are found, the pins are
 * assisnged to hp_pins[] and speaker_pins[], respectively.  If no line-out jack
 * is detected, one of speaker of HP pins is asचिन्हित as the primary
 * output, i.e. to line_out_pins[0].  So, line_outs is always positive
 * अगर any analog output exists.
 *
 * The analog input pins are asचिन्हित to inमाला_दो array.
 * The digital input/output pins are asचिन्हित to dig_in_pin and dig_out_pin,
 * respectively.
 */
पूर्णांक snd_hda_parse_pin_defcfg(काष्ठा hda_codec *codec,
			     काष्ठा स्वतः_pin_cfg *cfg,
			     स्थिर hda_nid_t *ignore_nids,
			     अचिन्हित पूर्णांक cond_flags)
अणु
	hda_nid_t nid;
	लघु seq, assoc_line_out;
	काष्ठा स्वतः_out_pin line_out[ARRAY_SIZE(cfg->line_out_pins)];
	काष्ठा स्वतः_out_pin speaker_out[ARRAY_SIZE(cfg->speaker_pins)];
	काष्ठा स्वतः_out_pin hp_out[ARRAY_SIZE(cfg->hp_pins)];
	पूर्णांक i;

	अगर (!snd_hda_get_पूर्णांक_hपूर्णांक(codec, "parser_flags", &i))
		cond_flags = i;

	स_रखो(cfg, 0, माप(*cfg));

	स_रखो(line_out, 0, माप(line_out));
	स_रखो(speaker_out, 0, माप(speaker_out));
	स_रखो(hp_out, 0, माप(hp_out));
	assoc_line_out = 0;

	क्रम_each_hda_codec_node(nid, codec) अणु
		अचिन्हित पूर्णांक wid_caps = get_wcaps(codec, nid);
		अचिन्हित पूर्णांक wid_type = get_wcaps_type(wid_caps);
		अचिन्हित पूर्णांक def_conf;
		लघु assoc, loc, conn, dev;

		/* पढ़ो all शेष configuration क्रम pin complex */
		अगर (wid_type != AC_WID_PIN)
			जारी;
		/* ignore the given nids (e.g. pc-beep वापसs error) */
		अगर (ignore_nids && is_in_nid_list(nid, ignore_nids))
			जारी;

		def_conf = snd_hda_codec_get_pincfg(codec, nid);
		conn = get_defcfg_connect(def_conf);
		अगर (conn == AC_JACK_PORT_NONE)
			जारी;
		loc = get_defcfg_location(def_conf);
		dev = get_defcfg_device(def_conf);

		/* workaround क्रम buggy BIOS setups */
		अगर (dev == AC_JACK_LINE_OUT) अणु
			अगर (conn == AC_JACK_PORT_FIXED ||
			    conn == AC_JACK_PORT_BOTH)
				dev = AC_JACK_SPEAKER;
		पूर्ण

		अगर (!check_pincap_validity(codec, nid, dev))
			जारी;

		चयन (dev) अणु
		हाल AC_JACK_LINE_OUT:
			seq = get_defcfg_sequence(def_conf);
			assoc = get_defcfg_association(def_conf);

			अगर (!(wid_caps & AC_WCAP_STEREO))
				अगर (!cfg->mono_out_pin)
					cfg->mono_out_pin = nid;
			अगर (!assoc)
				जारी;
			अगर (!assoc_line_out)
				assoc_line_out = assoc;
			अन्यथा अगर (assoc_line_out != assoc) अणु
				codec_info(codec,
					   "ignore pin 0x%x with mismatching assoc# 0x%x vs 0x%x\n",
					   nid, assoc, assoc_line_out);
				जारी;
			पूर्ण
			अगर (cfg->line_outs >= ARRAY_SIZE(cfg->line_out_pins)) अणु
				codec_info(codec,
					   "ignore pin 0x%x, too many assigned pins\n",
					   nid);
				जारी;
			पूर्ण
			line_out[cfg->line_outs].pin = nid;
			line_out[cfg->line_outs].seq = seq;
			cfg->line_outs++;
			अवरोध;
		हाल AC_JACK_SPEAKER:
			seq = get_defcfg_sequence(def_conf);
			assoc = get_defcfg_association(def_conf);
			अगर (cfg->speaker_outs >= ARRAY_SIZE(cfg->speaker_pins)) अणु
				codec_info(codec,
					   "ignore pin 0x%x, too many assigned pins\n",
					   nid);
				जारी;
			पूर्ण
			speaker_out[cfg->speaker_outs].pin = nid;
			speaker_out[cfg->speaker_outs].seq = (assoc << 4) | seq;
			cfg->speaker_outs++;
			अवरोध;
		हाल AC_JACK_HP_OUT:
			seq = get_defcfg_sequence(def_conf);
			assoc = get_defcfg_association(def_conf);
			अगर (cfg->hp_outs >= ARRAY_SIZE(cfg->hp_pins)) अणु
				codec_info(codec,
					   "ignore pin 0x%x, too many assigned pins\n",
					   nid);
				जारी;
			पूर्ण
			hp_out[cfg->hp_outs].pin = nid;
			hp_out[cfg->hp_outs].seq = (assoc << 4) | seq;
			cfg->hp_outs++;
			अवरोध;
		हाल AC_JACK_MIC_IN:
			add_स्वतः_cfg_input_pin(codec, cfg, nid, AUTO_PIN_MIC);
			अवरोध;
		हाल AC_JACK_LINE_IN:
			add_स्वतः_cfg_input_pin(codec, cfg, nid, AUTO_PIN_LINE_IN);
			अवरोध;
		हाल AC_JACK_CD:
			add_स्वतः_cfg_input_pin(codec, cfg, nid, AUTO_PIN_CD);
			अवरोध;
		हाल AC_JACK_AUX:
			add_स्वतः_cfg_input_pin(codec, cfg, nid, AUTO_PIN_AUX);
			अवरोध;
		हाल AC_JACK_SPDIF_OUT:
		हाल AC_JACK_DIG_OTHER_OUT:
			अगर (cfg->dig_outs >= ARRAY_SIZE(cfg->dig_out_pins)) अणु
				codec_info(codec,
					   "ignore pin 0x%x, too many assigned pins\n",
					   nid);
				जारी;
			पूर्ण
			cfg->dig_out_pins[cfg->dig_outs] = nid;
			cfg->dig_out_type[cfg->dig_outs] =
				(loc == AC_JACK_LOC_HDMI) ?
				HDA_PCM_TYPE_HDMI : HDA_PCM_TYPE_SPDIF;
			cfg->dig_outs++;
			अवरोध;
		हाल AC_JACK_SPDIF_IN:
		हाल AC_JACK_DIG_OTHER_IN:
			cfg->dig_in_pin = nid;
			अगर (loc == AC_JACK_LOC_HDMI)
				cfg->dig_in_type = HDA_PCM_TYPE_HDMI;
			अन्यथा
				cfg->dig_in_type = HDA_PCM_TYPE_SPDIF;
			अवरोध;
		पूर्ण
	पूर्ण

	/* Find a pin that could be a headset or headphone mic */
	अगर (cond_flags & HDA_PINCFG_HEADSET_MIC || cond_flags & HDA_PINCFG_HEADPHONE_MIC) अणु
		bool hsmic = !!(cond_flags & HDA_PINCFG_HEADSET_MIC);
		bool hpmic = !!(cond_flags & HDA_PINCFG_HEADPHONE_MIC);
		क्रम (i = 0; (hsmic || hpmic) && (i < cfg->num_inमाला_दो); i++)
			अगर (hsmic && can_be_headset_mic(codec, &cfg->inमाला_दो[i], 0xc)) अणु
				cfg->inमाला_दो[i].is_headset_mic = 1;
				hsmic = false;
			पूर्ण अन्यथा अगर (hpmic && can_be_headset_mic(codec, &cfg->inमाला_दो[i], 0xd)) अणु
				cfg->inमाला_दो[i].is_headphone_mic = 1;
				hpmic = false;
			पूर्ण

		/* If we didn't find our sequence number mark, fall back to any sequence number */
		क्रम (i = 0; (hsmic || hpmic) && (i < cfg->num_inमाला_दो); i++) अणु
			अगर (!can_be_headset_mic(codec, &cfg->inमाला_दो[i], -1))
				जारी;
			अगर (hsmic) अणु
				cfg->inमाला_दो[i].is_headset_mic = 1;
				hsmic = false;
			पूर्ण अन्यथा अगर (hpmic) अणु
				cfg->inमाला_दो[i].is_headphone_mic = 1;
				hpmic = false;
			पूर्ण
		पूर्ण

		अगर (hsmic)
			codec_dbg(codec, "Told to look for a headset mic, but didn't find any.\n");
		अगर (hpmic)
			codec_dbg(codec, "Told to look for a headphone mic, but didn't find any.\n");
	पूर्ण

	/* FIX-UP:
	 * If no line-out is defined but multiple HPs are found,
	 * some of them might be the real line-outs.
	 */
	अगर (!cfg->line_outs && cfg->hp_outs > 1 &&
	    !(cond_flags & HDA_PINCFG_NO_HP_FIXUP)) अणु
		i = 0;
		जबतक (i < cfg->hp_outs) अणु
			/* The real HPs should have the sequence 0x0f */
			अगर ((hp_out[i].seq & 0x0f) == 0x0f) अणु
				i++;
				जारी;
			पूर्ण
			/* Move it to the line-out table */
			line_out[cfg->line_outs++] = hp_out[i];
			cfg->hp_outs--;
			स_हटाओ(hp_out + i, hp_out + i + 1,
				माप(hp_out[0]) * (cfg->hp_outs - i));
		पूर्ण
		स_रखो(hp_out + cfg->hp_outs, 0,
		       माप(hp_out[0]) * (AUTO_CFG_MAX_OUTS - cfg->hp_outs));
		अगर (!cfg->hp_outs)
			cfg->line_out_type = AUTO_PIN_HP_OUT;

	पूर्ण

	/* sort by sequence */
	sort_pins_by_sequence(cfg->line_out_pins, line_out, cfg->line_outs);
	sort_pins_by_sequence(cfg->speaker_pins, speaker_out,
			      cfg->speaker_outs);
	sort_pins_by_sequence(cfg->hp_pins, hp_out, cfg->hp_outs);

	/*
	 * FIX-UP: अगर no line-outs are detected, try to use speaker or HP pin
	 * as a primary output
	 */
	अगर (!cfg->line_outs &&
	    !(cond_flags & HDA_PINCFG_NO_LO_FIXUP)) अणु
		अगर (cfg->speaker_outs) अणु
			cfg->line_outs = cfg->speaker_outs;
			स_नकल(cfg->line_out_pins, cfg->speaker_pins,
			       माप(cfg->speaker_pins));
			cfg->speaker_outs = 0;
			स_रखो(cfg->speaker_pins, 0, माप(cfg->speaker_pins));
			cfg->line_out_type = AUTO_PIN_SPEAKER_OUT;
		पूर्ण अन्यथा अगर (cfg->hp_outs) अणु
			cfg->line_outs = cfg->hp_outs;
			स_नकल(cfg->line_out_pins, cfg->hp_pins,
			       माप(cfg->hp_pins));
			cfg->hp_outs = 0;
			स_रखो(cfg->hp_pins, 0, माप(cfg->hp_pins));
			cfg->line_out_type = AUTO_PIN_HP_OUT;
		पूर्ण
	पूर्ण

	reorder_outमाला_दो(cfg->line_outs, cfg->line_out_pins);
	reorder_outमाला_दो(cfg->hp_outs, cfg->hp_pins);
	reorder_outमाला_दो(cfg->speaker_outs, cfg->speaker_pins);

	/* sort inमाला_दो in the order of AUTO_PIN_* type */
	sort(cfg->inमाला_दो, cfg->num_inमाला_दो, माप(cfg->inमाला_दो[0]),
	     compare_input_type, शून्य);

	/*
	 * debug prपूर्णांकs of the parsed results
	 */
	codec_info(codec, "autoconfig for %s: line_outs=%d (0x%x/0x%x/0x%x/0x%x/0x%x) type:%s\n",
		   codec->core.chip_name, cfg->line_outs, cfg->line_out_pins[0],
		   cfg->line_out_pins[1], cfg->line_out_pins[2],
		   cfg->line_out_pins[3], cfg->line_out_pins[4],
		   cfg->line_out_type == AUTO_PIN_HP_OUT ? "hp" :
		   (cfg->line_out_type == AUTO_PIN_SPEAKER_OUT ?
		    "speaker" : "line"));
	codec_info(codec, "   speaker_outs=%d (0x%x/0x%x/0x%x/0x%x/0x%x)\n",
		   cfg->speaker_outs, cfg->speaker_pins[0],
		   cfg->speaker_pins[1], cfg->speaker_pins[2],
		   cfg->speaker_pins[3], cfg->speaker_pins[4]);
	codec_info(codec, "   hp_outs=%d (0x%x/0x%x/0x%x/0x%x/0x%x)\n",
		   cfg->hp_outs, cfg->hp_pins[0],
		   cfg->hp_pins[1], cfg->hp_pins[2],
		   cfg->hp_pins[3], cfg->hp_pins[4]);
	codec_info(codec, "   mono: mono_out=0x%x\n", cfg->mono_out_pin);
	अगर (cfg->dig_outs)
		codec_info(codec, "   dig-out=0x%x/0x%x\n",
			   cfg->dig_out_pins[0], cfg->dig_out_pins[1]);
	codec_info(codec, "   inputs:\n");
	क्रम (i = 0; i < cfg->num_inमाला_दो; i++) अणु
		codec_info(codec, "     %s=0x%x\n",
			    hda_get_स्वतःcfg_input_label(codec, cfg, i),
			    cfg->inमाला_दो[i].pin);
	पूर्ण
	अगर (cfg->dig_in_pin)
		codec_info(codec, "   dig-in=0x%x\n", cfg->dig_in_pin);

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(snd_hda_parse_pin_defcfg);

/**
 * snd_hda_get_input_pin_attr - Get the input pin attribute from pin config
 * @def_conf: pin configuration value
 *
 * Guess the input pin attribute (INPUT_PIN_ATTR_XXX) from the given
 * शेष pin configuration value.
 */
पूर्णांक snd_hda_get_input_pin_attr(अचिन्हित पूर्णांक def_conf)
अणु
	अचिन्हित पूर्णांक loc = get_defcfg_location(def_conf);
	अचिन्हित पूर्णांक conn = get_defcfg_connect(def_conf);
	अगर (conn == AC_JACK_PORT_NONE)
		वापस INPUT_PIN_ATTR_UNUSED;
	/* Winकरोws may claim the पूर्णांकernal mic to be BOTH, too */
	अगर (conn == AC_JACK_PORT_FIXED || conn == AC_JACK_PORT_BOTH)
		वापस INPUT_PIN_ATTR_INT;
	अगर ((loc & 0x30) == AC_JACK_LOC_INTERNAL)
		वापस INPUT_PIN_ATTR_INT;
	अगर ((loc & 0x30) == AC_JACK_LOC_SEPARATE)
		वापस INPUT_PIN_ATTR_DOCK;
	अगर (loc == AC_JACK_LOC_REAR)
		वापस INPUT_PIN_ATTR_REAR;
	अगर (loc == AC_JACK_LOC_FRONT)
		वापस INPUT_PIN_ATTR_FRONT;
	वापस INPUT_PIN_ATTR_NORMAL;
पूर्ण
EXPORT_SYMBOL_GPL(snd_hda_get_input_pin_attr);

/**
 * hda_get_input_pin_label - Give a label क्रम the given input pin
 * @codec: the HDA codec
 * @item: ping config item to refer
 * @pin: the pin NID
 * @check_location: flag to add the jack location prefix
 *
 * When @check_location is true, the function checks the pin location
 * क्रम mic and line-in pins, and set an appropriate prefix like "Front",
 * "Rear", "Internal".
 */
अटल स्थिर अक्षर *hda_get_input_pin_label(काष्ठा hda_codec *codec,
					   स्थिर काष्ठा स्वतः_pin_cfg_item *item,
					   hda_nid_t pin, bool check_location)
अणु
	अचिन्हित पूर्णांक def_conf;
	अटल स्थिर अक्षर * स्थिर mic_names[] = अणु
		"Internal Mic", "Dock Mic", "Mic", "Rear Mic", "Front Mic"
	पूर्ण;
	पूर्णांक attr;

	def_conf = snd_hda_codec_get_pincfg(codec, pin);

	चयन (get_defcfg_device(def_conf)) अणु
	हाल AC_JACK_MIC_IN:
		अगर (item && item->is_headset_mic)
			वापस "Headset Mic";
		अगर (item && item->is_headphone_mic)
			वापस "Headphone Mic";
		अगर (!check_location)
			वापस "Mic";
		attr = snd_hda_get_input_pin_attr(def_conf);
		अगर (!attr)
			वापस "None";
		वापस mic_names[attr - 1];
	हाल AC_JACK_LINE_IN:
		अगर (!check_location)
			वापस "Line";
		attr = snd_hda_get_input_pin_attr(def_conf);
		अगर (!attr)
			वापस "None";
		अगर (attr == INPUT_PIN_ATTR_DOCK)
			वापस "Dock Line";
		वापस "Line";
	हाल AC_JACK_AUX:
		वापस "Aux";
	हाल AC_JACK_CD:
		वापस "CD";
	हाल AC_JACK_SPDIF_IN:
		वापस "SPDIF In";
	हाल AC_JACK_DIG_OTHER_IN:
		वापस "Digital In";
	हाल AC_JACK_HP_OUT:
		वापस "Headphone Mic";
	शेष:
		वापस "Misc";
	पूर्ण
पूर्ण

/* Check whether the location prefix needs to be added to the label.
 * If all mic-jacks are in the same location (e.g. rear panel), we करोn't
 * have to put "Front" prefix to each label.  In such a हाल, वापसs false.
 */
अटल पूर्णांक check_mic_location_need(काष्ठा hda_codec *codec,
				   स्थिर काष्ठा स्वतः_pin_cfg *cfg,
				   पूर्णांक input)
अणु
	अचिन्हित पूर्णांक defc;
	पूर्णांक i, attr, attr2;

	defc = snd_hda_codec_get_pincfg(codec, cfg->inमाला_दो[input].pin);
	attr = snd_hda_get_input_pin_attr(defc);
	/* क्रम पूर्णांकernal or करोcking mics, we need locations */
	अगर (attr <= INPUT_PIN_ATTR_NORMAL)
		वापस 1;

	attr = 0;
	क्रम (i = 0; i < cfg->num_inमाला_दो; i++) अणु
		defc = snd_hda_codec_get_pincfg(codec, cfg->inमाला_दो[i].pin);
		attr2 = snd_hda_get_input_pin_attr(defc);
		अगर (attr2 >= INPUT_PIN_ATTR_NORMAL) अणु
			अगर (attr && attr != attr2)
				वापस 1; /* dअगरferent locations found */
			attr = attr2;
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण

/**
 * hda_get_स्वतःcfg_input_label - Get a label क्रम the given input
 * @codec: the HDA codec
 * @cfg: the parsed pin configuration
 * @input: the input index number
 *
 * Get a label क्रम the given input pin defined by the स्वतःcfg item.
 * Unlike hda_get_input_pin_label(), this function checks all inमाला_दो
 * defined in स्वतःcfg and aव्योमs the redundant mic/line prefix as much as
 * possible.
 */
स्थिर अक्षर *hda_get_स्वतःcfg_input_label(काष्ठा hda_codec *codec,
					स्थिर काष्ठा स्वतः_pin_cfg *cfg,
					पूर्णांक input)
अणु
	पूर्णांक type = cfg->inमाला_दो[input].type;
	पूर्णांक has_multiple_pins = 0;

	अगर ((input > 0 && cfg->inमाला_दो[input - 1].type == type) ||
	    (input < cfg->num_inमाला_दो - 1 && cfg->inमाला_दो[input + 1].type == type))
		has_multiple_pins = 1;
	अगर (has_multiple_pins && type == AUTO_PIN_MIC)
		has_multiple_pins &= check_mic_location_need(codec, cfg, input);
	has_multiple_pins |= codec->क्रमce_pin_prefix;
	वापस hda_get_input_pin_label(codec, &cfg->inमाला_दो[input],
				       cfg->inमाला_दो[input].pin,
				       has_multiple_pins);
पूर्ण
EXPORT_SYMBOL_GPL(hda_get_स्वतःcfg_input_label);

/* वापस the position of NID in the list, or -1 अगर not found */
अटल पूर्णांक find_idx_in_nid_list(hda_nid_t nid, स्थिर hda_nid_t *list, पूर्णांक nums)
अणु
	पूर्णांक i;
	क्रम (i = 0; i < nums; i++)
		अगर (list[i] == nid)
			वापस i;
	वापस -1;
पूर्ण

/* get a unique suffix or an index number */
अटल स्थिर अक्षर *check_output_sfx(hda_nid_t nid, स्थिर hda_nid_t *pins,
				    पूर्णांक num_pins, पूर्णांक *indexp)
अणु
	अटल स्थिर अक्षर * स्थिर channel_sfx[] = अणु
		" Front", " Surround", " CLFE", " Side"
	पूर्ण;
	पूर्णांक i;

	i = find_idx_in_nid_list(nid, pins, num_pins);
	अगर (i < 0)
		वापस शून्य;
	अगर (num_pins == 1)
		वापस "";
	अगर (num_pins > ARRAY_SIZE(channel_sfx)) अणु
		अगर (indexp)
			*indexp = i;
		वापस "";
	पूर्ण
	वापस channel_sfx[i];
पूर्ण

अटल स्थिर अक्षर *check_output_pfx(काष्ठा hda_codec *codec, hda_nid_t nid)
अणु
	अचिन्हित पूर्णांक def_conf = snd_hda_codec_get_pincfg(codec, nid);
	पूर्णांक attr = snd_hda_get_input_pin_attr(def_conf);

	/* check the location */
	चयन (attr) अणु
	हाल INPUT_PIN_ATTR_DOCK:
		वापस "Dock ";
	हाल INPUT_PIN_ATTR_FRONT:
		वापस "Front ";
	पूर्ण
	वापस "";
पूर्ण

अटल पूर्णांक get_hp_label_index(काष्ठा hda_codec *codec, hda_nid_t nid,
			      स्थिर hda_nid_t *pins, पूर्णांक num_pins)
अणु
	पूर्णांक i, j, idx = 0;

	स्थिर अक्षर *pfx = check_output_pfx(codec, nid);

	i = find_idx_in_nid_list(nid, pins, num_pins);
	अगर (i < 0)
		वापस -1;
	क्रम (j = 0; j < i; j++)
		अगर (pfx == check_output_pfx(codec, pins[j]))
			idx++;

	वापस idx;
पूर्ण

अटल पूर्णांक fill_audio_out_name(काष्ठा hda_codec *codec, hda_nid_t nid,
			       स्थिर काष्ठा स्वतः_pin_cfg *cfg,
			       स्थिर अक्षर *name, अक्षर *label, पूर्णांक maxlen,
			       पूर्णांक *indexp)
अणु
	अचिन्हित पूर्णांक def_conf = snd_hda_codec_get_pincfg(codec, nid);
	पूर्णांक attr = snd_hda_get_input_pin_attr(def_conf);
	स्थिर अक्षर *pfx, *sfx = "";

	/* handle as a speaker अगर it's a fixed line-out */
	अगर (!म_भेद(name, "Line Out") && attr == INPUT_PIN_ATTR_INT)
		name = "Speaker";
	pfx = check_output_pfx(codec, nid);

	अगर (cfg) अणु
		/* try to give a unique suffix अगर needed */
		sfx = check_output_sfx(nid, cfg->line_out_pins, cfg->line_outs,
				       indexp);
		अगर (!sfx)
			sfx = check_output_sfx(nid, cfg->speaker_pins, cfg->speaker_outs,
					       indexp);
		अगर (!sfx) अणु
			/* करोn't add channel suffix क्रम Headphone controls */
			पूर्णांक idx = get_hp_label_index(codec, nid, cfg->hp_pins,
						     cfg->hp_outs);
			अगर (idx >= 0 && indexp)
				*indexp = idx;
			sfx = "";
		पूर्ण
	पूर्ण
	snम_लिखो(label, maxlen, "%s%s%s", pfx, name, sfx);
	वापस 1;
पूर्ण

#घोषणा is_hdmi_cfg(conf) \
	(get_defcfg_location(conf) == AC_JACK_LOC_HDMI)

/**
 * snd_hda_get_pin_label - Get a label क्रम the given I/O pin
 * @codec: the HDA codec
 * @nid: pin NID
 * @cfg: the parsed pin configuration
 * @label: the string buffer to store
 * @maxlen: the max length of string buffer (including termination)
 * @indexp: the poपूर्णांकer to वापस the index number (क्रम multiple ctls)
 *
 * Get a label क्रम the given pin.  This function works क्रम both input and
 * output pins.  When @cfg is given as non-शून्य, the function tries to get
 * an optimized label using hda_get_स्वतःcfg_input_label().
 *
 * This function tries to give a unique label string क्रम the pin as much as
 * possible.  For example, when the multiple line-outs are present, it adds
 * the channel suffix like "Front", "Surround", etc (only when @cfg is given).
 * If no unique name with a suffix is available and @indexp is non-शून्य, the
 * index number is stored in the poपूर्णांकer.
 */
पूर्णांक snd_hda_get_pin_label(काष्ठा hda_codec *codec, hda_nid_t nid,
			  स्थिर काष्ठा स्वतः_pin_cfg *cfg,
			  अक्षर *label, पूर्णांक maxlen, पूर्णांक *indexp)
अणु
	अचिन्हित पूर्णांक def_conf = snd_hda_codec_get_pincfg(codec, nid);
	स्थिर अक्षर *name = शून्य;
	पूर्णांक i;
	bool hdmi;

	अगर (indexp)
		*indexp = 0;
	अगर (get_defcfg_connect(def_conf) == AC_JACK_PORT_NONE)
		वापस 0;

	चयन (get_defcfg_device(def_conf)) अणु
	हाल AC_JACK_LINE_OUT:
		वापस fill_audio_out_name(codec, nid, cfg, "Line Out",
					   label, maxlen, indexp);
	हाल AC_JACK_SPEAKER:
		वापस fill_audio_out_name(codec, nid, cfg, "Speaker",
					   label, maxlen, indexp);
	हाल AC_JACK_HP_OUT:
		वापस fill_audio_out_name(codec, nid, cfg, "Headphone",
					   label, maxlen, indexp);
	हाल AC_JACK_SPDIF_OUT:
	हाल AC_JACK_DIG_OTHER_OUT:
		hdmi = is_hdmi_cfg(def_conf);
		name = hdmi ? "HDMI" : "SPDIF";
		अगर (cfg && indexp)
			क्रम (i = 0; i < cfg->dig_outs; i++) अणु
				hda_nid_t pin = cfg->dig_out_pins[i];
				अचिन्हित पूर्णांक c;
				अगर (pin == nid)
					अवरोध;
				c = snd_hda_codec_get_pincfg(codec, pin);
				अगर (hdmi == is_hdmi_cfg(c))
					(*indexp)++;
			पूर्ण
		अवरोध;
	शेष:
		अगर (cfg) अणु
			क्रम (i = 0; i < cfg->num_inमाला_दो; i++) अणु
				अगर (cfg->inमाला_दो[i].pin != nid)
					जारी;
				name = hda_get_स्वतःcfg_input_label(codec, cfg, i);
				अगर (name)
					अवरोध;
			पूर्ण
		पूर्ण
		अगर (!name)
			name = hda_get_input_pin_label(codec, शून्य, nid, true);
		अवरोध;
	पूर्ण
	अगर (!name)
		वापस 0;
	strscpy(label, name, maxlen);
	वापस 1;
पूर्ण
EXPORT_SYMBOL_GPL(snd_hda_get_pin_label);

/**
 * snd_hda_add_verbs - Add verbs to the init list
 * @codec: the HDA codec
 * @list: zero-terminated verb list to add
 *
 * Append the given verb list to the execution list.  The verbs will be
 * perक्रमmed at init and resume समय via snd_hda_apply_verbs().
 */
पूर्णांक snd_hda_add_verbs(काष्ठा hda_codec *codec,
		      स्थिर काष्ठा hda_verb *list)
अणु
	स्थिर काष्ठा hda_verb **v;
	v = snd_array_new(&codec->verbs);
	अगर (!v)
		वापस -ENOMEM;
	*v = list;
	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(snd_hda_add_verbs);

/**
 * snd_hda_apply_verbs - Execute the init verb lists
 * @codec: the HDA codec
 */
व्योम snd_hda_apply_verbs(काष्ठा hda_codec *codec)
अणु
	स्थिर काष्ठा hda_verb **v;
	पूर्णांक i;

	snd_array_क्रम_each(&codec->verbs, i, v)
		snd_hda_sequence_ग_लिखो(codec, *v);
पूर्ण
EXPORT_SYMBOL_GPL(snd_hda_apply_verbs);

/**
 * snd_hda_apply_pincfgs - Set each pin config in the given list
 * @codec: the HDA codec
 * @cfg: शून्य-terminated pin config table
 */
व्योम snd_hda_apply_pincfgs(काष्ठा hda_codec *codec,
			   स्थिर काष्ठा hda_pपूर्णांकbl *cfg)
अणु
	क्रम (; cfg->nid; cfg++)
		snd_hda_codec_set_pincfg(codec, cfg->nid, cfg->val);
पूर्ण
EXPORT_SYMBOL_GPL(snd_hda_apply_pincfgs);

अटल व्योम set_pin_tarमाला_लो(काष्ठा hda_codec *codec,
			    स्थिर काष्ठा hda_pपूर्णांकbl *cfg)
अणु
	क्रम (; cfg->nid; cfg++)
		snd_hda_set_pin_ctl_cache(codec, cfg->nid, cfg->val);
पूर्ण

अटल व्योम apply_fixup(काष्ठा hda_codec *codec, पूर्णांक id, पूर्णांक action, पूर्णांक depth)
अणु
	स्थिर अक्षर *modelname = codec->fixup_name;

	जबतक (id >= 0) अणु
		स्थिर काष्ठा hda_fixup *fix = codec->fixup_list + id;

		अगर (++depth > 10)
			अवरोध;
		अगर (fix->chained_beक्रमe)
			apply_fixup(codec, fix->chain_id, action, depth + 1);

		चयन (fix->type) अणु
		हाल HDA_FIXUP_PINS:
			अगर (action != HDA_FIXUP_ACT_PRE_PROBE || !fix->v.pins)
				अवरोध;
			codec_dbg(codec, "%s: Apply pincfg for %s\n",
				    codec->core.chip_name, modelname);
			snd_hda_apply_pincfgs(codec, fix->v.pins);
			अवरोध;
		हाल HDA_FIXUP_VERBS:
			अगर (action != HDA_FIXUP_ACT_PROBE || !fix->v.verbs)
				अवरोध;
			codec_dbg(codec, "%s: Apply fix-verbs for %s\n",
				    codec->core.chip_name, modelname);
			snd_hda_add_verbs(codec, fix->v.verbs);
			अवरोध;
		हाल HDA_FIXUP_FUNC:
			अगर (!fix->v.func)
				अवरोध;
			codec_dbg(codec, "%s: Apply fix-func for %s\n",
				    codec->core.chip_name, modelname);
			fix->v.func(codec, fix, action);
			अवरोध;
		हाल HDA_FIXUP_PINCTLS:
			अगर (action != HDA_FIXUP_ACT_PROBE || !fix->v.pins)
				अवरोध;
			codec_dbg(codec, "%s: Apply pinctl for %s\n",
				    codec->core.chip_name, modelname);
			set_pin_tarमाला_लो(codec, fix->v.pins);
			अवरोध;
		शेष:
			codec_err(codec, "%s: Invalid fixup type %d\n",
				   codec->core.chip_name, fix->type);
			अवरोध;
		पूर्ण
		अगर (!fix->chained || fix->chained_beक्रमe)
			अवरोध;
		id = fix->chain_id;
	पूर्ण
पूर्ण

/**
 * snd_hda_apply_fixup - Apply the fixup chain with the given action
 * @codec: the HDA codec
 * @action: fixup action (HDA_FIXUP_ACT_XXX)
 */
व्योम snd_hda_apply_fixup(काष्ठा hda_codec *codec, पूर्णांक action)
अणु
	अगर (codec->fixup_list)
		apply_fixup(codec, codec->fixup_id, action, 0);
पूर्ण
EXPORT_SYMBOL_GPL(snd_hda_apply_fixup);

#घोषणा IGNORE_SEQ_ASSOC (~(AC_DEFCFG_SEQUENCE | AC_DEFCFG_DEF_ASSOC))

अटल bool pin_config_match(काष्ठा hda_codec *codec,
			     स्थिर काष्ठा hda_pपूर्णांकbl *pins,
			     bool match_all_pins)
अणु
	स्थिर काष्ठा hda_pincfg *pin;
	पूर्णांक i;

	snd_array_क्रम_each(&codec->init_pins, i, pin) अणु
		hda_nid_t nid = pin->nid;
		u32 cfg = pin->cfg;
		स्थिर काष्ठा hda_pपूर्णांकbl *t_pins;
		पूर्णांक found;

		t_pins = pins;
		found = 0;
		क्रम (; t_pins->nid; t_pins++) अणु
			अगर (t_pins->nid == nid) अणु
				found = 1;
				अगर ((t_pins->val & IGNORE_SEQ_ASSOC) == (cfg & IGNORE_SEQ_ASSOC))
					अवरोध;
				अन्यथा अगर ((cfg & 0xf0000000) == 0x40000000 && (t_pins->val & 0xf0000000) == 0x40000000)
					अवरोध;
				अन्यथा
					वापस false;
			पूर्ण
		पूर्ण
		अगर (match_all_pins &&
		    !found && (cfg & 0xf0000000) != 0x40000000)
			वापस false;
	पूर्ण

	वापस true;
पूर्ण

/**
 * snd_hda_pick_pin_fixup - Pick up a fixup matching with the pin quirk list
 * @codec: the HDA codec
 * @pin_quirk: zero-terminated pin quirk list
 * @fixlist: the fixup list
 * @match_all_pins: all valid pins must match with the table entries
 */
व्योम snd_hda_pick_pin_fixup(काष्ठा hda_codec *codec,
			    स्थिर काष्ठा snd_hda_pin_quirk *pin_quirk,
			    स्थिर काष्ठा hda_fixup *fixlist,
			    bool match_all_pins)
अणु
	स्थिर काष्ठा snd_hda_pin_quirk *pq;

	अगर (codec->fixup_id != HDA_FIXUP_ID_NOT_SET)
		वापस;

	क्रम (pq = pin_quirk; pq->subvenकरोr; pq++) अणु
		अगर ((codec->core.subप्रणाली_id & 0xffff0000) != (pq->subvenकरोr << 16))
			जारी;
		अगर (codec->core.venकरोr_id != pq->codec)
			जारी;
		अगर (pin_config_match(codec, pq->pins, match_all_pins)) अणु
			codec->fixup_id = pq->value;
#अगर_घोषित CONFIG_SND_DEBUG_VERBOSE
			codec->fixup_name = pq->name;
			codec_dbg(codec, "%s: picked fixup %s (pin match)\n",
				  codec->core.chip_name, codec->fixup_name);
#पूर्ण_अगर
			codec->fixup_list = fixlist;
			वापस;
		पूर्ण
	पूर्ण
पूर्ण
EXPORT_SYMBOL_GPL(snd_hda_pick_pin_fixup);

/**
 * snd_hda_pick_fixup - Pick up a fixup matching with PCI/codec SSID or model string
 * @codec: the HDA codec
 * @models: शून्य-terminated model string list
 * @quirk: zero-terminated PCI/codec SSID quirk list
 * @fixlist: the fixup list
 *
 * Pick up a fixup entry matching with the given model string or SSID.
 * If a fixup was alपढ़ोy set beक्रमehand, the function करोesn't करो anything.
 * When a special model string "nofixup" is given, also no fixup is applied.
 *
 * The function tries to find the matching model name at first, अगर given.
 * If nothing matched, try to look up the PCI SSID.
 * If still nothing matched, try to look up the codec SSID.
 */
व्योम snd_hda_pick_fixup(काष्ठा hda_codec *codec,
			स्थिर काष्ठा hda_model_fixup *models,
			स्थिर काष्ठा snd_pci_quirk *quirk,
			स्थिर काष्ठा hda_fixup *fixlist)
अणु
	स्थिर काष्ठा snd_pci_quirk *q;
	पूर्णांक id = HDA_FIXUP_ID_NOT_SET;
	स्थिर अक्षर *name = शून्य;

	अगर (codec->fixup_id != HDA_FIXUP_ID_NOT_SET)
		वापस;

	/* when model=nofixup is given, करोn't pick up any fixups */
	अगर (codec->modelname && !म_भेद(codec->modelname, "nofixup")) अणु
		codec->fixup_list = शून्य;
		codec->fixup_name = शून्य;
		codec->fixup_id = HDA_FIXUP_ID_NO_FIXUP;
		codec_dbg(codec, "%s: picked no fixup (nofixup specified)\n",
			  codec->core.chip_name);
		वापस;
	पूर्ण

	अगर (codec->modelname && models) अणु
		जबतक (models->name) अणु
			अगर (!म_भेद(codec->modelname, models->name)) अणु
				codec->fixup_id = models->id;
				codec->fixup_name = models->name;
				codec->fixup_list = fixlist;
				codec_dbg(codec, "%s: picked fixup %s (model specified)\n",
					  codec->core.chip_name, codec->fixup_name);
				वापस;
			पूर्ण
			models++;
		पूर्ण
	पूर्ण
	अगर (quirk) अणु
		q = snd_pci_quirk_lookup(codec->bus->pci, quirk);
		अगर (q) अणु
			id = q->value;
#अगर_घोषित CONFIG_SND_DEBUG_VERBOSE
			name = q->name;
			codec_dbg(codec, "%s: picked fixup %s (PCI SSID%s)\n",
				  codec->core.chip_name, name, q->subdevice_mask ? "" : " - vendor generic");
#पूर्ण_अगर
		पूर्ण
	पूर्ण
	अगर (id < 0 && quirk) अणु
		क्रम (q = quirk; q->subvenकरोr || q->subdevice; q++) अणु
			अचिन्हित पूर्णांक venकरोrid =
				q->subdevice | (q->subvenकरोr << 16);
			अचिन्हित पूर्णांक mask = 0xffff0000 | q->subdevice_mask;
			अगर ((codec->core.subप्रणाली_id & mask) == (venकरोrid & mask)) अणु
				id = q->value;
#अगर_घोषित CONFIG_SND_DEBUG_VERBOSE
				name = q->name;
				codec_dbg(codec, "%s: picked fixup %s (codec SSID)\n",
					  codec->core.chip_name, name);
#पूर्ण_अगर
				अवरोध;
			पूर्ण
		पूर्ण
	पूर्ण

	codec->fixup_id = id;
	अगर (id >= 0) अणु
		codec->fixup_list = fixlist;
		codec->fixup_name = name;
	पूर्ण
पूर्ण
EXPORT_SYMBOL_GPL(snd_hda_pick_fixup);
