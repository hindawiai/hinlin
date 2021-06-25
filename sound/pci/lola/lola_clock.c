<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *  Support क्रम Digigram Lola PCI-e boards
 *
 *  Copyright (c) 2011 Takashi Iwai <tiwai@suse.de>
 */

#समावेश <linux/kernel.h>
#समावेश <linux/init.h>
#समावेश <linux/delay.h>
#समावेश <sound/core.h>
#समावेश <sound/pcm.h>
#समावेश "lola.h"

अचिन्हित पूर्णांक lola_sample_rate_convert(अचिन्हित पूर्णांक coded)
अणु
	अचिन्हित पूर्णांक freq;

	/* base frequency */
	चयन (coded & 0x3) अणु
	हाल 0:     freq = 48000; अवरोध;
	हाल 1:     freq = 44100; अवरोध;
	हाल 2:     freq = 32000; अवरोध;
	शेष:    वापस 0;   /* error */
	पूर्ण

	/* multiplier / devisor */
	चयन (coded & 0x1c) अणु
	हाल (0 << 2):    अवरोध;
	हाल (4 << 2):    अवरोध;
	हाल (1 << 2):    freq *= 2; अवरोध;
	हाल (2 << 2):    freq *= 4; अवरोध;
	हाल (5 << 2):    freq /= 2; अवरोध;
	हाल (6 << 2):    freq /= 4; अवरोध;
	शेष:        वापस 0;   /* error */
	पूर्ण

	/* ajustement */
	चयन (coded & 0x60) अणु
	हाल (0 << 5):    अवरोध;
	हाल (1 << 5):    freq = (freq * 999) / 1000; अवरोध;
	हाल (2 << 5):    freq = (freq * 1001) / 1000; अवरोध;
	शेष:        वापस 0;   /* error */
	पूर्ण
	वापस freq;
पूर्ण

/*
 * Granualrity
 */

#घोषणा LOLA_MAXFREQ_AT_GRANULARITY_MIN         48000
#घोषणा LOLA_MAXFREQ_AT_GRANULARITY_BELOW_MAX   96000

अटल bool check_gran_घड़ी_compatibility(काष्ठा lola *chip,
					   अचिन्हित पूर्णांक val,
					   अचिन्हित पूर्णांक freq)
अणु
	अगर (!chip->granularity)
		वापस true;

	अगर (val < LOLA_GRANULARITY_MIN || val > LOLA_GRANULARITY_MAX ||
	    (val % LOLA_GRANULARITY_STEP) != 0)
		वापस false;

	अगर (val == LOLA_GRANULARITY_MIN) अणु
		अगर (freq > LOLA_MAXFREQ_AT_GRANULARITY_MIN)
			वापस false;
	पूर्ण अन्यथा अगर (val < LOLA_GRANULARITY_MAX) अणु
		अगर (freq > LOLA_MAXFREQ_AT_GRANULARITY_BELOW_MAX)
			वापस false;
	पूर्ण
	वापस true;
पूर्ण

पूर्णांक lola_set_granularity(काष्ठा lola *chip, अचिन्हित पूर्णांक val, bool क्रमce)
अणु
	पूर्णांक err;

	अगर (!क्रमce) अणु
		अगर (val == chip->granularity)
			वापस 0;
#अगर 0
		/* change Gran only अगर there are no streams allocated ! */
		अगर (chip->audio_in_alloc_mask || chip->audio_out_alloc_mask)
			वापस -EBUSY;
#पूर्ण_अगर
		अगर (!check_gran_घड़ी_compatibility(chip, val,
						    chip->घड़ी.cur_freq))
			वापस -EINVAL;
	पूर्ण

	chip->granularity = val;
	val /= LOLA_GRANULARITY_STEP;

	/* audio function group */
	err = lola_codec_ग_लिखो(chip, 1, LOLA_VERB_SET_GRANULARITY_STEPS,
			       val, 0);
	अगर (err < 0)
		वापस err;
	/* this can be a very slow function !!! */
	usleep_range(400 * val, 20000);
	वापस lola_codec_flush(chip);
पूर्ण

/*
 * Clock widget handling
 */

पूर्णांक lola_init_घड़ी_widget(काष्ठा lola *chip, पूर्णांक nid)
अणु
	अचिन्हित पूर्णांक val;
	पूर्णांक i, j, nitems, nb_verbs, idx, idx_list;
	पूर्णांक err;

	err = lola_पढ़ो_param(chip, nid, LOLA_PAR_AUDIO_WIDGET_CAP, &val);
	अगर (err < 0) अणु
		dev_err(chip->card->dev, "Can't read wcaps for 0x%x\n", nid);
		वापस err;
	पूर्ण

	अगर ((val & 0xfff00000) != 0x01f00000) अणु /* test SubType and Type */
		dev_dbg(chip->card->dev, "No valid clock widget\n");
		वापस 0;
	पूर्ण

	chip->घड़ी.nid = nid;
	chip->घड़ी.items = val & 0xff;
	dev_dbg(chip->card->dev, "clock_list nid=%x, entries=%d\n", nid,
		    chip->घड़ी.items);
	अगर (chip->घड़ी.items > MAX_SAMPLE_CLOCK_COUNT) अणु
		dev_err(chip->card->dev, "CLOCK_LIST too big: %d\n",
		       chip->घड़ी.items);
		वापस -EINVAL;
	पूर्ण

	nitems = chip->घड़ी.items;
	nb_verbs = DIV_ROUND_UP(nitems, 4);
	idx = 0;
	idx_list = 0;
	क्रम (i = 0; i < nb_verbs; i++) अणु
		अचिन्हित पूर्णांक res_ex;
		अचिन्हित लघु items[4];

		err = lola_codec_पढ़ो(chip, nid, LOLA_VERB_GET_CLOCK_LIST,
				      idx, 0, &val, &res_ex);
		अगर (err < 0) अणु
			dev_err(chip->card->dev, "Can't read CLOCK_LIST\n");
			वापस -EINVAL;
		पूर्ण

		items[0] = val & 0xfff;
		items[1] = (val >> 16) & 0xfff;
		items[2] = res_ex & 0xfff;
		items[3] = (res_ex >> 16) & 0xfff;

		क्रम (j = 0; j < 4; j++) अणु
			अचिन्हित अक्षर type = items[j] >> 8;
			अचिन्हित पूर्णांक freq = items[j] & 0xff;
			पूर्णांक क्रमmat = LOLA_CLOCK_FORMAT_NONE;
			bool add_घड़ी = true;
			अगर (type == LOLA_CLOCK_TYPE_INTERNAL) अणु
				freq = lola_sample_rate_convert(freq);
				अगर (freq < chip->sample_rate_min)
					add_घड़ी = false;
				अन्यथा अगर (freq == 48000) अणु
					chip->घड़ी.cur_index = idx_list;
					chip->घड़ी.cur_freq = 48000;
					chip->घड़ी.cur_valid = true;
				पूर्ण
			पूर्ण अन्यथा अगर (type == LOLA_CLOCK_TYPE_VIDEO) अणु
				freq = lola_sample_rate_convert(freq);
				अगर (freq < chip->sample_rate_min)
					add_घड़ी = false;
				/* video घड़ी has a क्रमmat (0:NTSC, 1:PAL)*/
				अगर (items[j] & 0x80)
					क्रमmat = LOLA_CLOCK_FORMAT_NTSC;
				अन्यथा
					क्रमmat = LOLA_CLOCK_FORMAT_PAL;
			पूर्ण
			अगर (add_घड़ी) अणु
				काष्ठा lola_sample_घड़ी *sc;
				sc = &chip->घड़ी.sample_घड़ी[idx_list];
				sc->type = type;
				sc->क्रमmat = क्रमmat;
				sc->freq = freq;
				/* keep the index used with the board */
				chip->घड़ी.idx_lookup[idx_list] = idx;
				idx_list++;
			पूर्ण अन्यथा अणु
				chip->घड़ी.items--;
			पूर्ण
			अगर (++idx >= nitems)
				अवरोध;
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण

/* enable unsolicited events of the घड़ी widget */
पूर्णांक lola_enable_घड़ी_events(काष्ठा lola *chip)
अणु
	अचिन्हित पूर्णांक res;
	पूर्णांक err;

	err = lola_codec_पढ़ो(chip, chip->घड़ी.nid,
			      LOLA_VERB_SET_UNSOLICITED_ENABLE,
			      LOLA_UNSOLICITED_ENABLE | LOLA_UNSOLICITED_TAG,
			      0, &res, शून्य);
	अगर (err < 0)
		वापस err;
	अगर (res) अणु
		dev_warn(chip->card->dev, "error in enable_clock_events %d\n",
		       res);
		वापस -EINVAL;
	पूर्ण
	वापस 0;
पूर्ण

पूर्णांक lola_set_घड़ी_index(काष्ठा lola *chip, अचिन्हित पूर्णांक idx)
अणु
	अचिन्हित पूर्णांक res;
	पूर्णांक err;

	err = lola_codec_पढ़ो(chip, chip->घड़ी.nid,
			      LOLA_VERB_SET_CLOCK_SELECT,
			      chip->घड़ी.idx_lookup[idx],
			      0, &res, शून्य);
	अगर (err < 0)
		वापस err;
	अगर (res) अणु
		dev_warn(chip->card->dev, "error in set_clock %d\n", res);
		वापस -EINVAL;
	पूर्ण
	वापस 0;
पूर्ण

bool lola_update_ext_घड़ी_freq(काष्ठा lola *chip, अचिन्हित पूर्णांक val)
अणु
	अचिन्हित पूर्णांक tag;

	/* the current EXTERNAL घड़ी inक्रमmation माला_लो updated by पूर्णांकerrupt
	 * with an unsolicited response
	 */
	अगर (!val)
		वापस false;
	tag = (val >> LOLA_UNSOL_RESP_TAG_OFFSET) & LOLA_UNSOLICITED_TAG_MASK;
	अगर (tag != LOLA_UNSOLICITED_TAG)
		वापस false;

	/* only क्रम current = बाह्यal घड़ीs */
	अगर (chip->घड़ी.sample_घड़ी[chip->घड़ी.cur_index].type !=
	    LOLA_CLOCK_TYPE_INTERNAL) अणु
		chip->घड़ी.cur_freq = lola_sample_rate_convert(val & 0x7f);
		chip->घड़ी.cur_valid = (val & 0x100) != 0;
	पूर्ण
	वापस true;
पूर्ण

पूर्णांक lola_set_घड़ी(काष्ठा lola *chip, पूर्णांक idx)
अणु
	पूर्णांक freq = 0;
	bool valid = false;

	अगर (idx == chip->घड़ी.cur_index) अणु
		/* current घड़ी is allowed */
		freq = chip->घड़ी.cur_freq;
		valid = chip->घड़ी.cur_valid;
	पूर्ण अन्यथा अगर (chip->घड़ी.sample_घड़ी[idx].type ==
		   LOLA_CLOCK_TYPE_INTERNAL) अणु
		/* पूर्णांकernal घड़ीs allowed */
		freq = chip->घड़ी.sample_घड़ी[idx].freq;
		valid = true;
	पूर्ण

	अगर (!freq || !valid)
		वापस -EINVAL;

	अगर (!check_gran_घड़ी_compatibility(chip, chip->granularity, freq))
		वापस -EINVAL;

	अगर (idx != chip->घड़ी.cur_index) अणु
		पूर्णांक err = lola_set_घड़ी_index(chip, idx);
		अगर (err < 0)
			वापस err;
		/* update new settings */
		chip->घड़ी.cur_index = idx;
		chip->घड़ी.cur_freq = freq;
		chip->घड़ी.cur_valid = true;
	पूर्ण
	वापस 0;
पूर्ण

पूर्णांक lola_set_sample_rate(काष्ठा lola *chip, पूर्णांक rate)
अणु
	पूर्णांक i;

	अगर (chip->घड़ी.cur_freq == rate && chip->घड़ी.cur_valid)
		वापस 0;
	/* search क्रम new dwClockIndex */
	क्रम (i = 0; i < chip->घड़ी.items; i++) अणु
		अगर (chip->घड़ी.sample_घड़ी[i].type == LOLA_CLOCK_TYPE_INTERNAL &&
		    chip->घड़ी.sample_घड़ी[i].freq == rate)
			अवरोध;
	पूर्ण
	अगर (i >= chip->घड़ी.items)
		वापस -EINVAL;
	वापस lola_set_घड़ी(chip, i);
पूर्ण

