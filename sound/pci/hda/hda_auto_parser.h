<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * BIOS स्वतः-parser helper functions क्रम HD-audio
 *
 * Copyright (c) 2012 Takashi Iwai <tiwai@suse.de>
 */

#अगर_अघोषित __SOUND_HDA_AUTO_PARSER_H
#घोषणा __SOUND_HDA_AUTO_PARSER_H

/*
 * Helper क्रम स्वतःmatic pin configuration
 */

क्रमागत अणु
	AUTO_PIN_MIC,
	AUTO_PIN_LINE_IN,
	AUTO_PIN_CD,
	AUTO_PIN_AUX,
	AUTO_PIN_LAST
पूर्ण;

क्रमागत अणु
	AUTO_PIN_LINE_OUT,
	AUTO_PIN_SPEAKER_OUT,
	AUTO_PIN_HP_OUT
पूर्ण;

#घोषणा AUTO_CFG_MAX_OUTS	HDA_MAX_OUTS
#घोषणा AUTO_CFG_MAX_INS	18

काष्ठा स्वतः_pin_cfg_item अणु
	hda_nid_t pin;
	पूर्णांक type;
	अचिन्हित पूर्णांक is_headset_mic:1;
	अचिन्हित पूर्णांक is_headphone_mic:1; /* Mic-only in headphone jack */
	अचिन्हित पूर्णांक has_boost_on_pin:1;
पूर्ण;

काष्ठा स्वतः_pin_cfg;
स्थिर अक्षर *hda_get_स्वतःcfg_input_label(काष्ठा hda_codec *codec,
					स्थिर काष्ठा स्वतः_pin_cfg *cfg,
					पूर्णांक input);
पूर्णांक snd_hda_get_pin_label(काष्ठा hda_codec *codec, hda_nid_t nid,
			  स्थिर काष्ठा स्वतः_pin_cfg *cfg,
			  अक्षर *label, पूर्णांक maxlen, पूर्णांक *indexp);

क्रमागत अणु
	INPUT_PIN_ATTR_UNUSED,	/* pin not connected */
	INPUT_PIN_ATTR_INT,	/* पूर्णांकernal mic/line-in */
	INPUT_PIN_ATTR_DOCK,	/* करोcking mic/line-in */
	INPUT_PIN_ATTR_NORMAL,	/* mic/line-in jack */
	INPUT_PIN_ATTR_REAR,	/* mic/line-in jack in rear */
	INPUT_PIN_ATTR_FRONT,	/* mic/line-in jack in front */
	INPUT_PIN_ATTR_LAST = INPUT_PIN_ATTR_FRONT,
पूर्ण;

पूर्णांक snd_hda_get_input_pin_attr(अचिन्हित पूर्णांक def_conf);

काष्ठा स्वतः_pin_cfg अणु
	पूर्णांक line_outs;
	/* sorted in the order of Front/Surr/CLFE/Side */
	hda_nid_t line_out_pins[AUTO_CFG_MAX_OUTS];
	पूर्णांक speaker_outs;
	hda_nid_t speaker_pins[AUTO_CFG_MAX_OUTS];
	पूर्णांक hp_outs;
	पूर्णांक line_out_type;	/* AUTO_PIN_XXX_OUT */
	hda_nid_t hp_pins[AUTO_CFG_MAX_OUTS];
	पूर्णांक num_inमाला_दो;
	काष्ठा स्वतः_pin_cfg_item inमाला_दो[AUTO_CFG_MAX_INS];
	पूर्णांक dig_outs;
	hda_nid_t dig_out_pins[2];
	hda_nid_t dig_in_pin;
	hda_nid_t mono_out_pin;
	पूर्णांक dig_out_type[2]; /* HDA_PCM_TYPE_XXX */
	पूर्णांक dig_in_type; /* HDA_PCM_TYPE_XXX */
पूर्ण;

/* bit-flags क्रम snd_hda_parse_pin_def_config() behavior */
#घोषणा HDA_PINCFG_NO_HP_FIXUP   (1 << 0) /* no HP-split */
#घोषणा HDA_PINCFG_NO_LO_FIXUP   (1 << 1) /* करोn't take other outs as LO */
#घोषणा HDA_PINCFG_HEADSET_MIC   (1 << 2) /* Try to find headset mic; mark seq number as 0xc to trigger */
#घोषणा HDA_PINCFG_HEADPHONE_MIC (1 << 3) /* Try to find headphone mic; mark seq number as 0xd to trigger */

पूर्णांक snd_hda_parse_pin_defcfg(काष्ठा hda_codec *codec,
			     काष्ठा स्वतः_pin_cfg *cfg,
			     स्थिर hda_nid_t *ignore_nids,
			     अचिन्हित पूर्णांक cond_flags);

/* older function */
#घोषणा snd_hda_parse_pin_def_config(codec, cfg, ignore) \
	snd_hda_parse_pin_defcfg(codec, cfg, ignore, 0)

अटल अंतरभूत पूर्णांक स्वतः_cfg_hp_outs(स्थिर काष्ठा स्वतः_pin_cfg *cfg)
अणु
	वापस (cfg->line_out_type == AUTO_PIN_HP_OUT) ?
	       cfg->line_outs : cfg->hp_outs;
पूर्ण
अटल अंतरभूत स्थिर hda_nid_t *स्वतः_cfg_hp_pins(स्थिर काष्ठा स्वतः_pin_cfg *cfg)
अणु
	वापस (cfg->line_out_type == AUTO_PIN_HP_OUT) ?
	       cfg->line_out_pins : cfg->hp_pins;
पूर्ण
अटल अंतरभूत पूर्णांक स्वतः_cfg_speaker_outs(स्थिर काष्ठा स्वतः_pin_cfg *cfg)
अणु
	वापस (cfg->line_out_type == AUTO_PIN_SPEAKER_OUT) ?
	       cfg->line_outs : cfg->speaker_outs;
पूर्ण
अटल अंतरभूत स्थिर hda_nid_t *स्वतः_cfg_speaker_pins(स्थिर काष्ठा स्वतः_pin_cfg *cfg)
अणु
	वापस (cfg->line_out_type == AUTO_PIN_SPEAKER_OUT) ?
	       cfg->line_out_pins : cfg->speaker_pins;
पूर्ण

#पूर्ण_अगर /* __SOUND_HDA_AUTO_PARSER_H */
