<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *  Copyright (c) by Jaroslav Kysela <perex@perex.cz>
 *  Universal पूर्णांकerface क्रम Audio Codec '97
 *
 *  For more details look to AC '97 component specअगरication revision 2.2
 *  by Intel Corporation (http://developer.पूर्णांकel.com) and to datasheets
 *  क्रम specअगरic codecs.
 */

#समावेश "ac97_local.h"
#समावेश "ac97_patch.h"

/*
 *  Forward declarations
 */

अटल काष्ठा snd_kcontrol *snd_ac97_find_mixer_ctl(काष्ठा snd_ac97 *ac97,
						    स्थिर अक्षर *name);
अटल पूर्णांक snd_ac97_add_vmaster(काष्ठा snd_ac97 *ac97, अक्षर *name,
				स्थिर अचिन्हित पूर्णांक *tlv,
				स्थिर अक्षर * स्थिर *followers);

/*
 *  Chip specअगरic initialization
 */

अटल पूर्णांक patch_build_controls(काष्ठा snd_ac97 * ac97, स्थिर काष्ठा snd_kcontrol_new *controls, पूर्णांक count)
अणु
	पूर्णांक idx, err;

	क्रम (idx = 0; idx < count; idx++)
		अगर ((err = snd_ctl_add(ac97->bus->card, snd_ac97_cnew(&controls[idx], ac97))) < 0)
			वापस err;
	वापस 0;
पूर्ण

/* replace with a new TLV */
अटल व्योम reset_tlv(काष्ठा snd_ac97 *ac97, स्थिर अक्षर *name,
		      स्थिर अचिन्हित पूर्णांक *tlv)
अणु
	काष्ठा snd_ctl_elem_id sid;
	काष्ठा snd_kcontrol *kctl;
	स_रखो(&sid, 0, माप(sid));
	म_नकल(sid.name, name);
	sid.अगरace = SNDRV_CTL_ELEM_IFACE_MIXER;
	kctl = snd_ctl_find_id(ac97->bus->card, &sid);
	अगर (kctl && kctl->tlv.p)
		kctl->tlv.p = tlv;
पूर्ण

/* set to the page, update bits and restore the page */
अटल पूर्णांक ac97_update_bits_page(काष्ठा snd_ac97 *ac97, अचिन्हित लघु reg, अचिन्हित लघु mask, अचिन्हित लघु value, अचिन्हित लघु page)
अणु
	अचिन्हित लघु page_save;
	पूर्णांक ret;

	mutex_lock(&ac97->page_mutex);
	page_save = snd_ac97_पढ़ो(ac97, AC97_INT_PAGING) & AC97_PAGE_MASK;
	snd_ac97_update_bits(ac97, AC97_INT_PAGING, AC97_PAGE_MASK, page);
	ret = snd_ac97_update_bits(ac97, reg, mask, value);
	snd_ac97_update_bits(ac97, AC97_INT_PAGING, AC97_PAGE_MASK, page_save);
	mutex_unlock(&ac97->page_mutex); /* unlock paging */
	वापस ret;
पूर्ण

/*
 * shared line-in/mic controls
 */
अटल पूर्णांक ac97_surround_jack_mode_info(काष्ठा snd_kcontrol *kcontrol, काष्ठा snd_ctl_elem_info *uinfo)
अणु
	अटल स्थिर अक्षर * स्थिर texts[] = अणु "Shared", "Independent" पूर्ण;

	वापस snd_ctl_क्रमागत_info(uinfo, 1, 2, texts);
पूर्ण

अटल पूर्णांक ac97_surround_jack_mode_get(काष्ठा snd_kcontrol *kcontrol, काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_ac97 *ac97 = snd_kcontrol_chip(kcontrol);

	ucontrol->value.क्रमागतerated.item[0] = ac97->indep_surround;
	वापस 0;
पूर्ण

अटल पूर्णांक ac97_surround_jack_mode_put(काष्ठा snd_kcontrol *kcontrol, काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_ac97 *ac97 = snd_kcontrol_chip(kcontrol);
	अचिन्हित अक्षर indep = !!ucontrol->value.क्रमागतerated.item[0];

	अगर (indep != ac97->indep_surround) अणु
		ac97->indep_surround = indep;
		अगर (ac97->build_ops->update_jacks)
			ac97->build_ops->update_jacks(ac97);
		वापस 1;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक ac97_channel_mode_info(काष्ठा snd_kcontrol *kcontrol, काष्ठा snd_ctl_elem_info *uinfo)
अणु
	अटल स्थिर अक्षर * स्थिर texts[] = अणु "2ch", "4ch", "6ch", "8ch" पूर्ण;

	वापस snd_ctl_क्रमागत_info(uinfo, 1, kcontrol->निजी_value, texts);
पूर्ण

अटल पूर्णांक ac97_channel_mode_get(काष्ठा snd_kcontrol *kcontrol, काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_ac97 *ac97 = snd_kcontrol_chip(kcontrol);

	ucontrol->value.क्रमागतerated.item[0] = ac97->channel_mode;
	वापस 0;
पूर्ण

अटल पूर्णांक ac97_channel_mode_put(काष्ठा snd_kcontrol *kcontrol, काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_ac97 *ac97 = snd_kcontrol_chip(kcontrol);
	अचिन्हित अक्षर mode = ucontrol->value.क्रमागतerated.item[0];

	अगर (mode >= kcontrol->निजी_value)
		वापस -EINVAL;

	अगर (mode != ac97->channel_mode) अणु
		ac97->channel_mode = mode;
		अगर (ac97->build_ops->update_jacks)
			ac97->build_ops->update_jacks(ac97);
		वापस 1;
	पूर्ण
	वापस 0;
पूर्ण

#घोषणा AC97_SURROUND_JACK_MODE_CTL \
	अणु \
		.अगरace	= SNDRV_CTL_ELEM_IFACE_MIXER, \
		.name	= "Surround Jack Mode", \
		.info = ac97_surround_jack_mode_info, \
		.get = ac97_surround_jack_mode_get, \
		.put = ac97_surround_jack_mode_put, \
	पूर्ण
/* 6ch */
#घोषणा AC97_CHANNEL_MODE_CTL \
	अणु \
		.अगरace	= SNDRV_CTL_ELEM_IFACE_MIXER, \
		.name	= "Channel Mode", \
		.info = ac97_channel_mode_info, \
		.get = ac97_channel_mode_get, \
		.put = ac97_channel_mode_put, \
		.निजी_value = 3, \
	पूर्ण
/* 4ch */
#घोषणा AC97_CHANNEL_MODE_4CH_CTL \
	अणु \
		.अगरace	= SNDRV_CTL_ELEM_IFACE_MIXER, \
		.name	= "Channel Mode", \
		.info = ac97_channel_mode_info, \
		.get = ac97_channel_mode_get, \
		.put = ac97_channel_mode_put, \
		.निजी_value = 2, \
	पूर्ण
/* 8ch */
#घोषणा AC97_CHANNEL_MODE_8CH_CTL \
	अणु \
		.अगरace  = SNDRV_CTL_ELEM_IFACE_MIXER, \
		.name   = "Channel Mode", \
		.info = ac97_channel_mode_info, \
		.get = ac97_channel_mode_get, \
		.put = ac97_channel_mode_put, \
		.निजी_value = 4, \
	पूर्ण

अटल अंतरभूत पूर्णांक is_surround_on(काष्ठा snd_ac97 *ac97)
अणु
	वापस ac97->channel_mode >= 1;
पूर्ण

अटल अंतरभूत पूर्णांक is_clfe_on(काष्ठा snd_ac97 *ac97)
अणु
	वापस ac97->channel_mode >= 2;
पूर्ण

/* प्रणाली has shared jacks with surround out enabled */
अटल अंतरभूत पूर्णांक is_shared_surrout(काष्ठा snd_ac97 *ac97)
अणु
	वापस !ac97->indep_surround && is_surround_on(ac97);
पूर्ण

/* प्रणाली has shared jacks with center/lfe out enabled */
अटल अंतरभूत पूर्णांक is_shared_clfeout(काष्ठा snd_ac97 *ac97)
अणु
	वापस !ac97->indep_surround && is_clfe_on(ac97);
पूर्ण

/* प्रणाली has shared jacks with line in enabled */
अटल अंतरभूत पूर्णांक is_shared_linein(काष्ठा snd_ac97 *ac97)
अणु
	वापस !ac97->indep_surround && !is_surround_on(ac97);
पूर्ण

/* प्रणाली has shared jacks with mic in enabled */
अटल अंतरभूत पूर्णांक is_shared_micin(काष्ठा snd_ac97 *ac97)
अणु
	वापस !ac97->indep_surround && !is_clfe_on(ac97);
पूर्ण

अटल अंतरभूत पूर्णांक alc850_is_aux_back_surround(काष्ठा snd_ac97 *ac97)
अणु
	वापस is_surround_on(ac97);
पूर्ण

/* The following snd_ac97_ymf753_... items added by David Shust (dshust@shustring.com) */
/* Modअगरied क्रम YMF743 by Keita Maehara <maehara@debian.org> */

/* It is possible to indicate to the Yamaha YMF7x3 the type of
   speakers being used. */

अटल पूर्णांक snd_ac97_ymf7x3_info_speaker(काष्ठा snd_kcontrol *kcontrol,
					काष्ठा snd_ctl_elem_info *uinfo)
अणु
	अटल स्थिर अक्षर * स्थिर texts[3] = अणु
		"Standard", "Small", "Smaller"
	पूर्ण;

	वापस snd_ctl_क्रमागत_info(uinfo, 1, 3, texts);
पूर्ण

अटल पूर्णांक snd_ac97_ymf7x3_get_speaker(काष्ठा snd_kcontrol *kcontrol,
				       काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_ac97 *ac97 = snd_kcontrol_chip(kcontrol);
	अचिन्हित लघु val;

	val = ac97->regs[AC97_YMF7X3_3D_MODE_SEL];
	val = (val >> 10) & 3;
	अगर (val > 0)    /* 0 = invalid */
		val--;
	ucontrol->value.क्रमागतerated.item[0] = val;
	वापस 0;
पूर्ण

अटल पूर्णांक snd_ac97_ymf7x3_put_speaker(काष्ठा snd_kcontrol *kcontrol,
				       काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_ac97 *ac97 = snd_kcontrol_chip(kcontrol);
	अचिन्हित लघु val;

	अगर (ucontrol->value.क्रमागतerated.item[0] > 2)
		वापस -EINVAL;
	val = (ucontrol->value.क्रमागतerated.item[0] + 1) << 10;
	वापस snd_ac97_update(ac97, AC97_YMF7X3_3D_MODE_SEL, val);
पूर्ण

अटल स्थिर काष्ठा snd_kcontrol_new snd_ac97_ymf7x3_controls_speaker =
अणु
	.अगरace  = SNDRV_CTL_ELEM_IFACE_MIXER,
	.name   = "3D Control - Speaker",
	.info   = snd_ac97_ymf7x3_info_speaker,
	.get    = snd_ac97_ymf7x3_get_speaker,
	.put    = snd_ac97_ymf7x3_put_speaker,
पूर्ण;

/* It is possible to indicate to the Yamaha YMF7x3 the source to
   direct to the S/PDIF output. */
अटल पूर्णांक snd_ac97_ymf7x3_spdअगर_source_info(काष्ठा snd_kcontrol *kcontrol,
					     काष्ठा snd_ctl_elem_info *uinfo)
अणु
	अटल स्थिर अक्षर * स्थिर texts[2] = अणु "AC-Link", "A/D Converter" पूर्ण;

	वापस snd_ctl_क्रमागत_info(uinfo, 1, 2, texts);
पूर्ण

अटल पूर्णांक snd_ac97_ymf7x3_spdअगर_source_get(काष्ठा snd_kcontrol *kcontrol,
					    काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_ac97 *ac97 = snd_kcontrol_chip(kcontrol);
	अचिन्हित लघु val;

	val = ac97->regs[AC97_YMF7X3_DIT_CTRL];
	ucontrol->value.क्रमागतerated.item[0] = (val >> 1) & 1;
	वापस 0;
पूर्ण

अटल पूर्णांक snd_ac97_ymf7x3_spdअगर_source_put(काष्ठा snd_kcontrol *kcontrol,
					    काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_ac97 *ac97 = snd_kcontrol_chip(kcontrol);
	अचिन्हित लघु val;

	अगर (ucontrol->value.क्रमागतerated.item[0] > 1)
		वापस -EINVAL;
	val = ucontrol->value.क्रमागतerated.item[0] << 1;
	वापस snd_ac97_update_bits(ac97, AC97_YMF7X3_DIT_CTRL, 0x0002, val);
पूर्ण

अटल पूर्णांक patch_yamaha_ymf7x3_3d(काष्ठा snd_ac97 *ac97)
अणु
	काष्ठा snd_kcontrol *kctl;
	पूर्णांक err;

	kctl = snd_ac97_cnew(&snd_ac97_controls_3d[0], ac97);
	err = snd_ctl_add(ac97->bus->card, kctl);
	अगर (err < 0)
		वापस err;
	म_नकल(kctl->id.name, "3D Control - Wide");
	kctl->निजी_value = AC97_SINGLE_VALUE(AC97_3D_CONTROL, 9, 7, 0);
	snd_ac97_ग_लिखो_cache(ac97, AC97_3D_CONTROL, 0x0000);
	err = snd_ctl_add(ac97->bus->card,
			  snd_ac97_cnew(&snd_ac97_ymf7x3_controls_speaker,
					ac97));
	अगर (err < 0)
		वापस err;
	snd_ac97_ग_लिखो_cache(ac97, AC97_YMF7X3_3D_MODE_SEL, 0x0c00);
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा snd_kcontrol_new snd_ac97_yamaha_ymf743_controls_spdअगर[3] =
अणु
	AC97_SINGLE(SNDRV_CTL_NAME_IEC958("", PLAYBACK, SWITCH),
		    AC97_YMF7X3_DIT_CTRL, 0, 1, 0),
	अणु
		.अगरace	= SNDRV_CTL_ELEM_IFACE_MIXER,
		.name	= SNDRV_CTL_NAME_IEC958("", PLAYBACK, NONE) "Source",
		.info	= snd_ac97_ymf7x3_spdअगर_source_info,
		.get	= snd_ac97_ymf7x3_spdअगर_source_get,
		.put	= snd_ac97_ymf7x3_spdअगर_source_put,
	पूर्ण,
	AC97_SINGLE(SNDRV_CTL_NAME_IEC958("", NONE, NONE) "Mute",
		    AC97_YMF7X3_DIT_CTRL, 2, 1, 1)
पूर्ण;

अटल पूर्णांक patch_yamaha_ymf743_build_spdअगर(काष्ठा snd_ac97 *ac97)
अणु
	पूर्णांक err;

	err = patch_build_controls(ac97, &snd_ac97_controls_spdअगर[0], 3);
	अगर (err < 0)
		वापस err;
	err = patch_build_controls(ac97,
				   snd_ac97_yamaha_ymf743_controls_spdअगर, 3);
	अगर (err < 0)
		वापस err;
	/* set शेष PCM S/PDIF params */
	/* PCM audio,no copyright,no preemphasis,PCM coder,original */
	snd_ac97_ग_लिखो_cache(ac97, AC97_YMF7X3_DIT_CTRL, 0xa201);
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा snd_ac97_build_ops patch_yamaha_ymf743_ops = अणु
	.build_spdअगर	= patch_yamaha_ymf743_build_spdअगर,
	.build_3d	= patch_yamaha_ymf7x3_3d,
पूर्ण;

अटल पूर्णांक patch_yamaha_ymf743(काष्ठा snd_ac97 *ac97)
अणु
	ac97->build_ops = &patch_yamaha_ymf743_ops;
	ac97->caps |= AC97_BC_BASS_TREBLE;
	ac97->caps |= 0x04 << 10; /* Yamaha 3D enhancement */
	ac97->rates[AC97_RATES_SPDIF] = SNDRV_PCM_RATE_48000; /* 48k only */
	ac97->ext_id |= AC97_EI_SPDIF; /* क्रमce the detection of spdअगर */
	वापस 0;
पूर्ण

/* The AC'97 spec states that the S/PDIF संकेत is to be output at pin 48.
   The YMF753 will output the S/PDIF संकेत to pin 43, 47 (EAPD), or 48.
   By शेष, no output pin is selected, and the S/PDIF संकेत is not output.
   There is also a bit to mute S/PDIF output in a venकरोr-specअगरic रेजिस्टर. */
अटल पूर्णांक snd_ac97_ymf753_spdअगर_output_pin_info(काष्ठा snd_kcontrol *kcontrol, काष्ठा snd_ctl_elem_info *uinfo)
अणु
	अटल स्थिर अक्षर * स्थिर texts[3] = अणु "Disabled", "Pin 43", "Pin 48" पूर्ण;

	वापस snd_ctl_क्रमागत_info(uinfo, 1, 3, texts);
पूर्ण

अटल पूर्णांक snd_ac97_ymf753_spdअगर_output_pin_get(काष्ठा snd_kcontrol *kcontrol, काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_ac97 *ac97 = snd_kcontrol_chip(kcontrol);
	अचिन्हित लघु val;

	val = ac97->regs[AC97_YMF7X3_DIT_CTRL];
	ucontrol->value.क्रमागतerated.item[0] = (val & 0x0008) ? 2 : (val & 0x0020) ? 1 : 0;
	वापस 0;
पूर्ण

अटल पूर्णांक snd_ac97_ymf753_spdअगर_output_pin_put(काष्ठा snd_kcontrol *kcontrol, काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_ac97 *ac97 = snd_kcontrol_chip(kcontrol);
	अचिन्हित लघु val;

	अगर (ucontrol->value.क्रमागतerated.item[0] > 2)
		वापस -EINVAL;
	val = (ucontrol->value.क्रमागतerated.item[0] == 2) ? 0x0008 :
	      (ucontrol->value.क्रमागतerated.item[0] == 1) ? 0x0020 : 0;
	वापस snd_ac97_update_bits(ac97, AC97_YMF7X3_DIT_CTRL, 0x0028, val);
	/* The following can be used to direct S/PDIF output to pin 47 (EAPD).
	   snd_ac97_ग_लिखो_cache(ac97, 0x62, snd_ac97_पढ़ो(ac97, 0x62) | 0x0008); */
पूर्ण

अटल स्थिर काष्ठा snd_kcontrol_new snd_ac97_ymf753_controls_spdअगर[3] = अणु
	अणु
		.अगरace	= SNDRV_CTL_ELEM_IFACE_MIXER,
		.name	= SNDRV_CTL_NAME_IEC958("",PLAYBACK,NONE) "Source",
		.info	= snd_ac97_ymf7x3_spdअगर_source_info,
		.get	= snd_ac97_ymf7x3_spdअगर_source_get,
		.put	= snd_ac97_ymf7x3_spdअगर_source_put,
	पूर्ण,
	अणु
		.अगरace	= SNDRV_CTL_ELEM_IFACE_MIXER,
		.name	= SNDRV_CTL_NAME_IEC958("",PLAYBACK,NONE) "Output Pin",
		.info	= snd_ac97_ymf753_spdअगर_output_pin_info,
		.get	= snd_ac97_ymf753_spdअगर_output_pin_get,
		.put	= snd_ac97_ymf753_spdअगर_output_pin_put,
	पूर्ण,
	AC97_SINGLE(SNDRV_CTL_NAME_IEC958("", NONE, NONE) "Mute",
		    AC97_YMF7X3_DIT_CTRL, 2, 1, 1)
पूर्ण;

अटल पूर्णांक patch_yamaha_ymf753_post_spdअगर(काष्ठा snd_ac97 * ac97)
अणु
	पूर्णांक err;

	अगर ((err = patch_build_controls(ac97, snd_ac97_ymf753_controls_spdअगर, ARRAY_SIZE(snd_ac97_ymf753_controls_spdअगर))) < 0)
		वापस err;
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा snd_ac97_build_ops patch_yamaha_ymf753_ops = अणु
	.build_3d	= patch_yamaha_ymf7x3_3d,
	.build_post_spdअगर = patch_yamaha_ymf753_post_spdअगर
पूर्ण;

अटल पूर्णांक patch_yamaha_ymf753(काष्ठा snd_ac97 * ac97)
अणु
	/* Patch क्रम Yamaha YMF753, Copyright (c) by David Shust, dshust@shustring.com.
	   This chip has nonstandard and extended behaviour with regard to its S/PDIF output.
	   The AC'97 spec states that the S/PDIF संकेत is to be output at pin 48.
	   The YMF753 will ouput the S/PDIF संकेत to pin 43, 47 (EAPD), or 48.
	   By शेष, no output pin is selected, and the S/PDIF संकेत is not output.
	   There is also a bit to mute S/PDIF output in a venकरोr-specअगरic रेजिस्टर.
	*/
	ac97->build_ops = &patch_yamaha_ymf753_ops;
	ac97->caps |= AC97_BC_BASS_TREBLE;
	ac97->caps |= 0x04 << 10; /* Yamaha 3D enhancement */
	वापस 0;
पूर्ण

/*
 * May 2, 2003 Liam Girdwood <lrg@slimlogic.co.uk>
 *  हटाओd broken wolfson00 patch.
 *  added support क्रम WM9705,WM9708,WM9709,WM9710,WM9711,WM9712 and WM9717.
 */

अटल स्थिर काष्ठा snd_kcontrol_new wm97xx_snd_ac97_controls[] = अणु
AC97_DOUBLE("Front Playback Volume", AC97_WM97XX_FMIXER_VOL, 8, 0, 31, 1),
AC97_SINGLE("Front Playback Switch", AC97_WM97XX_FMIXER_VOL, 15, 1, 1),
पूर्ण;

अटल पूर्णांक patch_wolfson_wm9703_specअगरic(काष्ठा snd_ac97 * ac97)
अणु
	/* This is known to work क्रम the ViewSonic ViewPad 1000
	 * Ranकरोlph Bentson <bentson@holmsjoen.com>
	 * WM9703/9707/9708/9717 
	 */
	पूर्णांक err, i;
	
	क्रम (i = 0; i < ARRAY_SIZE(wm97xx_snd_ac97_controls); i++) अणु
		अगर ((err = snd_ctl_add(ac97->bus->card, snd_ac97_cnew(&wm97xx_snd_ac97_controls[i], ac97))) < 0)
			वापस err;
	पूर्ण
	snd_ac97_ग_लिखो_cache(ac97,  AC97_WM97XX_FMIXER_VOL, 0x0808);
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा snd_ac97_build_ops patch_wolfson_wm9703_ops = अणु
	.build_specअगरic = patch_wolfson_wm9703_specअगरic,
पूर्ण;

अटल पूर्णांक patch_wolfson03(काष्ठा snd_ac97 * ac97)
अणु
	ac97->build_ops = &patch_wolfson_wm9703_ops;
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा snd_kcontrol_new wm9704_snd_ac97_controls[] = अणु
AC97_DOUBLE("Front Playback Volume", AC97_WM97XX_FMIXER_VOL, 8, 0, 31, 1),
AC97_SINGLE("Front Playback Switch", AC97_WM97XX_FMIXER_VOL, 15, 1, 1),
AC97_DOUBLE("Rear Playback Volume", AC97_WM9704_RMIXER_VOL, 8, 0, 31, 1),
AC97_SINGLE("Rear Playback Switch", AC97_WM9704_RMIXER_VOL, 15, 1, 1),
AC97_DOUBLE("Rear DAC Volume", AC97_WM9704_RPCM_VOL, 8, 0, 31, 1),
AC97_DOUBLE("Surround Volume", AC97_SURROUND_MASTER, 8, 0, 31, 1),
पूर्ण;

अटल पूर्णांक patch_wolfson_wm9704_specअगरic(काष्ठा snd_ac97 * ac97)
अणु
	पूर्णांक err, i;
	क्रम (i = 0; i < ARRAY_SIZE(wm9704_snd_ac97_controls); i++) अणु
		अगर ((err = snd_ctl_add(ac97->bus->card, snd_ac97_cnew(&wm9704_snd_ac97_controls[i], ac97))) < 0)
			वापस err;
	पूर्ण
	/* patch क्रम DVD noise */
	snd_ac97_ग_लिखो_cache(ac97, AC97_WM9704_TEST, 0x0200);
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा snd_ac97_build_ops patch_wolfson_wm9704_ops = अणु
	.build_specअगरic = patch_wolfson_wm9704_specअगरic,
पूर्ण;

अटल पूर्णांक patch_wolfson04(काष्ठा snd_ac97 * ac97)
अणु
	/* WM9704M/9704Q */
	ac97->build_ops = &patch_wolfson_wm9704_ops;
	वापस 0;
पूर्ण

अटल पूर्णांक patch_wolfson05(काष्ठा snd_ac97 * ac97)
अणु
	/* WM9705, WM9710 */
	ac97->build_ops = &patch_wolfson_wm9703_ops;
#अगर_घोषित CONFIG_TOUCHSCREEN_WM9705
	/* WM9705 touchscreen uses AUX and VIDEO क्रम touch */
	ac97->flags |= AC97_HAS_NO_VIDEO | AC97_HAS_NO_AUX;
#पूर्ण_अगर
	वापस 0;
पूर्ण

अटल स्थिर अक्षर* wm9711_alc_select[] = अणु"None", "Left", "Right", "Stereo"पूर्ण;
अटल स्थिर अक्षर* wm9711_alc_mix[] = अणु"Stereo", "Right", "Left", "None"पूर्ण;
अटल स्थिर अक्षर* wm9711_out3_src[] = अणु"Left", "VREF", "Left + Right", "Mono"पूर्ण;
अटल स्थिर अक्षर* wm9711_out3_lrsrc[] = अणु"Master Mix", "Headphone Mix"पूर्ण;
अटल स्थिर अक्षर* wm9711_rec_adc[] = अणु"Stereo", "Left", "Right", "Mute"पूर्ण;
अटल स्थिर अक्षर* wm9711_base[] = अणु"Linear Control", "Adaptive Boost"पूर्ण;
अटल स्थिर अक्षर* wm9711_rec_gain[] = अणु"+1.5dB Steps", "+0.75dB Steps"पूर्ण;
अटल स्थिर अक्षर* wm9711_mic[] = अणु"Mic 1", "Differential", "Mic 2", "Stereo"पूर्ण;
अटल स्थिर अक्षर* wm9711_rec_sel[] = 
	अणु"Mic 1", "NC", "NC", "Master Mix", "Line", "Headphone Mix", "Phone Mix", "Phone"पूर्ण;
अटल स्थिर अक्षर* wm9711_ng_type[] = अणु"Constant Gain", "Mute"पूर्ण;

अटल स्थिर काष्ठा ac97_क्रमागत wm9711_क्रमागत[] = अणु
AC97_ENUM_SINGLE(AC97_PCI_SVID, 14, 4, wm9711_alc_select),
AC97_ENUM_SINGLE(AC97_VIDEO, 10, 4, wm9711_alc_mix),
AC97_ENUM_SINGLE(AC97_AUX, 9, 4, wm9711_out3_src),
AC97_ENUM_SINGLE(AC97_AUX, 8, 2, wm9711_out3_lrsrc),
AC97_ENUM_SINGLE(AC97_REC_SEL, 12, 4, wm9711_rec_adc),
AC97_ENUM_SINGLE(AC97_MASTER_TONE, 15, 2, wm9711_base),
AC97_ENUM_DOUBLE(AC97_REC_GAIN, 14, 6, 2, wm9711_rec_gain),
AC97_ENUM_SINGLE(AC97_MIC, 5, 4, wm9711_mic),
AC97_ENUM_DOUBLE(AC97_REC_SEL, 8, 0, 8, wm9711_rec_sel),
AC97_ENUM_SINGLE(AC97_PCI_SVID, 5, 2, wm9711_ng_type),
पूर्ण;

अटल स्थिर काष्ठा snd_kcontrol_new wm9711_snd_ac97_controls[] = अणु
AC97_SINGLE("ALC Target Volume", AC97_CODEC_CLASS_REV, 12, 15, 0),
AC97_SINGLE("ALC Hold Time", AC97_CODEC_CLASS_REV, 8, 15, 0),
AC97_SINGLE("ALC Decay Time", AC97_CODEC_CLASS_REV, 4, 15, 0),
AC97_SINGLE("ALC Attack Time", AC97_CODEC_CLASS_REV, 0, 15, 0),
AC97_ENUM("ALC Function", wm9711_क्रमागत[0]),
AC97_SINGLE("ALC Max Volume", AC97_PCI_SVID, 11, 7, 1),
AC97_SINGLE("ALC ZC Timeout", AC97_PCI_SVID, 9, 3, 1),
AC97_SINGLE("ALC ZC Switch", AC97_PCI_SVID, 8, 1, 0),
AC97_SINGLE("ALC NG Switch", AC97_PCI_SVID, 7, 1, 0),
AC97_ENUM("ALC NG Type", wm9711_क्रमागत[9]),
AC97_SINGLE("ALC NG Threshold", AC97_PCI_SVID, 0, 31, 1),

AC97_SINGLE("Side Tone Switch", AC97_VIDEO, 15, 1, 1),
AC97_SINGLE("Side Tone Volume", AC97_VIDEO, 12, 7, 1),
AC97_ENUM("ALC Headphone Mux", wm9711_क्रमागत[1]),
AC97_SINGLE("ALC Headphone Volume", AC97_VIDEO, 7, 7, 1),

AC97_SINGLE("Out3 Switch", AC97_AUX, 15, 1, 1),
AC97_SINGLE("Out3 ZC Switch", AC97_AUX, 7, 1, 0),
AC97_ENUM("Out3 Mux", wm9711_क्रमागत[2]),
AC97_ENUM("Out3 LR Mux", wm9711_क्रमागत[3]),
AC97_SINGLE("Out3 Volume", AC97_AUX, 0, 31, 1),

AC97_SINGLE("Beep to Headphone Switch", AC97_PC_BEEP, 15, 1, 1),
AC97_SINGLE("Beep to Headphone Volume", AC97_PC_BEEP, 12, 7, 1),
AC97_SINGLE("Beep to Side Tone Switch", AC97_PC_BEEP, 11, 1, 1),
AC97_SINGLE("Beep to Side Tone Volume", AC97_PC_BEEP, 8, 7, 1),
AC97_SINGLE("Beep to Phone Switch", AC97_PC_BEEP, 7, 1, 1),
AC97_SINGLE("Beep to Phone Volume", AC97_PC_BEEP, 4, 7, 1),

AC97_SINGLE("Aux to Headphone Switch", AC97_CD, 15, 1, 1),
AC97_SINGLE("Aux to Headphone Volume", AC97_CD, 12, 7, 1),
AC97_SINGLE("Aux to Side Tone Switch", AC97_CD, 11, 1, 1),
AC97_SINGLE("Aux to Side Tone Volume", AC97_CD, 8, 7, 1),
AC97_SINGLE("Aux to Phone Switch", AC97_CD, 7, 1, 1),
AC97_SINGLE("Aux to Phone Volume", AC97_CD, 4, 7, 1),

AC97_SINGLE("Phone to Headphone Switch", AC97_PHONE, 15, 1, 1),
AC97_SINGLE("Phone to Master Switch", AC97_PHONE, 14, 1, 1),

AC97_SINGLE("Line to Headphone Switch", AC97_LINE, 15, 1, 1),
AC97_SINGLE("Line to Master Switch", AC97_LINE, 14, 1, 1),
AC97_SINGLE("Line to Phone Switch", AC97_LINE, 13, 1, 1),

AC97_SINGLE("PCM Playback to Headphone Switch", AC97_PCM, 15, 1, 1),
AC97_SINGLE("PCM Playback to Master Switch", AC97_PCM, 14, 1, 1),
AC97_SINGLE("PCM Playback to Phone Switch", AC97_PCM, 13, 1, 1),

AC97_SINGLE("Capture 20dB Boost Switch", AC97_REC_SEL, 14, 1, 0),
AC97_ENUM("Capture to Phone Mux", wm9711_क्रमागत[4]),
AC97_SINGLE("Capture to Phone 20dB Boost Switch", AC97_REC_SEL, 11, 1, 1),
AC97_ENUM("Capture Select", wm9711_क्रमागत[8]),

AC97_SINGLE("3D Upper Cut-off Switch", AC97_3D_CONTROL, 5, 1, 1),
AC97_SINGLE("3D Lower Cut-off Switch", AC97_3D_CONTROL, 4, 1, 1),

AC97_ENUM("Bass Control", wm9711_क्रमागत[5]),
AC97_SINGLE("Bass Cut-off Switch", AC97_MASTER_TONE, 12, 1, 1),
AC97_SINGLE("Tone Cut-off Switch", AC97_MASTER_TONE, 4, 1, 1),
AC97_SINGLE("Playback Attenuate (-6dB) Switch", AC97_MASTER_TONE, 6, 1, 0),

AC97_SINGLE("ADC Switch", AC97_REC_GAIN, 15, 1, 1),
AC97_ENUM("Capture Volume Steps", wm9711_क्रमागत[6]),
AC97_DOUBLE("Capture Volume", AC97_REC_GAIN, 8, 0, 63, 1),
AC97_SINGLE("Capture ZC Switch", AC97_REC_GAIN, 7, 1, 0),

AC97_SINGLE("Mic 1 to Phone Switch", AC97_MIC, 14, 1, 1),
AC97_SINGLE("Mic 2 to Phone Switch", AC97_MIC, 13, 1, 1),
AC97_ENUM("Mic Select Source", wm9711_क्रमागत[7]),
AC97_SINGLE("Mic 1 Volume", AC97_MIC, 8, 31, 1),
AC97_SINGLE("Mic 2 Volume", AC97_MIC, 0, 31, 1),
AC97_SINGLE("Mic 20dB Boost Switch", AC97_MIC, 7, 1, 0),

AC97_SINGLE("Master Left Inv Switch", AC97_MASTER, 6, 1, 0),
AC97_SINGLE("Master ZC Switch", AC97_MASTER, 7, 1, 0),
AC97_SINGLE("Headphone ZC Switch", AC97_HEADPHONE, 7, 1, 0),
AC97_SINGLE("Mono ZC Switch", AC97_MASTER_MONO, 7, 1, 0),
पूर्ण;

अटल पूर्णांक patch_wolfson_wm9711_specअगरic(काष्ठा snd_ac97 * ac97)
अणु
	पूर्णांक err, i;
	
	क्रम (i = 0; i < ARRAY_SIZE(wm9711_snd_ac97_controls); i++) अणु
		अगर ((err = snd_ctl_add(ac97->bus->card, snd_ac97_cnew(&wm9711_snd_ac97_controls[i], ac97))) < 0)
			वापस err;
	पूर्ण
	snd_ac97_ग_लिखो_cache(ac97,  AC97_CODEC_CLASS_REV, 0x0808);
	snd_ac97_ग_लिखो_cache(ac97,  AC97_PCI_SVID, 0x0808);
	snd_ac97_ग_लिखो_cache(ac97,  AC97_VIDEO, 0x0808);
	snd_ac97_ग_लिखो_cache(ac97,  AC97_AUX, 0x0808);
	snd_ac97_ग_लिखो_cache(ac97,  AC97_PC_BEEP, 0x0808);
	snd_ac97_ग_लिखो_cache(ac97,  AC97_CD, 0x0000);
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा snd_ac97_build_ops patch_wolfson_wm9711_ops = अणु
	.build_specअगरic = patch_wolfson_wm9711_specअगरic,
पूर्ण;

अटल पूर्णांक patch_wolfson11(काष्ठा snd_ac97 * ac97)
अणु
	/* WM9711, WM9712 */
	ac97->build_ops = &patch_wolfson_wm9711_ops;

	ac97->flags |= AC97_HAS_NO_REC_GAIN | AC97_STEREO_MUTES | AC97_HAS_NO_MIC |
		AC97_HAS_NO_PC_BEEP | AC97_HAS_NO_VIDEO | AC97_HAS_NO_CD;
	
	वापस 0;
पूर्ण

अटल स्थिर अक्षर* wm9713_mic_mixer[] = अणु"Stereo", "Mic 1", "Mic 2", "Mute"पूर्ण;
अटल स्थिर अक्षर* wm9713_rec_mux[] = अणु"Stereo", "Left", "Right", "Mute"पूर्ण;
अटल स्थिर अक्षर* wm9713_rec_src[] = 
	अणु"Mic 1", "Mic 2", "Line", "Mono In", "Headphone Mix", "Master Mix", 
	"Mono Mix", "Zh"पूर्ण;
अटल स्थिर अक्षर* wm9713_rec_gain[] = अणु"+1.5dB Steps", "+0.75dB Steps"पूर्ण;
अटल स्थिर अक्षर* wm9713_alc_select[] = अणु"None", "Left", "Right", "Stereo"पूर्ण;
अटल स्थिर अक्षर* wm9713_mono_pga[] = अणु"Vmid", "Zh", "Mono Mix", "Inv 1"पूर्ण;
अटल स्थिर अक्षर* wm9713_spk_pga[] = 
	अणु"Vmid", "Zh", "Headphone Mix", "Master Mix", "Inv", "NC", "NC", "NC"पूर्ण;
अटल स्थिर अक्षर* wm9713_hp_pga[] = अणु"Vmid", "Zh", "Headphone Mix", "NC"पूर्ण;
अटल स्थिर अक्षर* wm9713_out3_pga[] = अणु"Vmid", "Zh", "Inv 1", "NC"पूर्ण;
अटल स्थिर अक्षर* wm9713_out4_pga[] = अणु"Vmid", "Zh", "Inv 2", "NC"पूर्ण;
अटल स्थिर अक्षर* wm9713_dac_inv[] = 
	अणु"Off", "Mono Mix", "Master Mix", "Headphone Mix L", "Headphone Mix R", 
	"Headphone Mix Mono", "NC", "Vmid"पूर्ण;
अटल स्थिर अक्षर* wm9713_base[] = अणु"Linear Control", "Adaptive Boost"पूर्ण;
अटल स्थिर अक्षर* wm9713_ng_type[] = अणु"Constant Gain", "Mute"पूर्ण;

अटल स्थिर काष्ठा ac97_क्रमागत wm9713_क्रमागत[] = अणु
AC97_ENUM_SINGLE(AC97_LINE, 3, 4, wm9713_mic_mixer),
AC97_ENUM_SINGLE(AC97_VIDEO, 14, 4, wm9713_rec_mux),
AC97_ENUM_SINGLE(AC97_VIDEO, 9, 4, wm9713_rec_mux),
AC97_ENUM_DOUBLE(AC97_VIDEO, 3, 0, 8, wm9713_rec_src),
AC97_ENUM_DOUBLE(AC97_CD, 14, 6, 2, wm9713_rec_gain),
AC97_ENUM_SINGLE(AC97_PCI_SVID, 14, 4, wm9713_alc_select),
AC97_ENUM_SINGLE(AC97_REC_GAIN, 14, 4, wm9713_mono_pga),
AC97_ENUM_DOUBLE(AC97_REC_GAIN, 11, 8, 8, wm9713_spk_pga),
AC97_ENUM_DOUBLE(AC97_REC_GAIN, 6, 4, 4, wm9713_hp_pga),
AC97_ENUM_SINGLE(AC97_REC_GAIN, 2, 4, wm9713_out3_pga),
AC97_ENUM_SINGLE(AC97_REC_GAIN, 0, 4, wm9713_out4_pga),
AC97_ENUM_DOUBLE(AC97_REC_GAIN_MIC, 13, 10, 8, wm9713_dac_inv),
AC97_ENUM_SINGLE(AC97_GENERAL_PURPOSE, 15, 2, wm9713_base),
AC97_ENUM_SINGLE(AC97_PCI_SVID, 5, 2, wm9713_ng_type),
पूर्ण;

अटल स्थिर काष्ठा snd_kcontrol_new wm13_snd_ac97_controls[] = अणु
AC97_DOUBLE("Line In Volume", AC97_PC_BEEP, 8, 0, 31, 1),
AC97_SINGLE("Line In to Headphone Switch", AC97_PC_BEEP, 15, 1, 1),
AC97_SINGLE("Line In to Master Switch", AC97_PC_BEEP, 14, 1, 1),
AC97_SINGLE("Line In to Mono Switch", AC97_PC_BEEP, 13, 1, 1),

AC97_DOUBLE("PCM Playback Volume", AC97_PHONE, 8, 0, 31, 1),
AC97_SINGLE("PCM Playback to Headphone Switch", AC97_PHONE, 15, 1, 1),
AC97_SINGLE("PCM Playback to Master Switch", AC97_PHONE, 14, 1, 1),
AC97_SINGLE("PCM Playback to Mono Switch", AC97_PHONE, 13, 1, 1),

AC97_SINGLE("Mic 1 Volume", AC97_MIC, 8, 31, 1),
AC97_SINGLE("Mic 2 Volume", AC97_MIC, 0, 31, 1),
AC97_SINGLE("Mic 1 to Mono Switch", AC97_LINE, 7, 1, 1),
AC97_SINGLE("Mic 2 to Mono Switch", AC97_LINE, 6, 1, 1),
AC97_SINGLE("Mic Boost (+20dB) Switch", AC97_LINE, 5, 1, 0),
AC97_ENUM("Mic to Headphone Mux", wm9713_क्रमागत[0]),
AC97_SINGLE("Mic Headphone Mixer Volume", AC97_LINE, 0, 7, 1),

AC97_SINGLE("Capture Switch", AC97_CD, 15, 1, 1),
AC97_ENUM("Capture Volume Steps", wm9713_क्रमागत[4]),
AC97_DOUBLE("Capture Volume", AC97_CD, 8, 0, 15, 0),
AC97_SINGLE("Capture ZC Switch", AC97_CD, 7, 1, 0),

AC97_ENUM("Capture to Headphone Mux", wm9713_क्रमागत[1]),
AC97_SINGLE("Capture to Headphone Volume", AC97_VIDEO, 11, 7, 1),
AC97_ENUM("Capture to Mono Mux", wm9713_क्रमागत[2]),
AC97_SINGLE("Capture to Mono Boost (+20dB) Switch", AC97_VIDEO, 8, 1, 0),
AC97_SINGLE("Capture ADC Boost (+20dB) Switch", AC97_VIDEO, 6, 1, 0),
AC97_ENUM("Capture Select", wm9713_क्रमागत[3]),

AC97_SINGLE("ALC Target Volume", AC97_CODEC_CLASS_REV, 12, 15, 0),
AC97_SINGLE("ALC Hold Time", AC97_CODEC_CLASS_REV, 8, 15, 0),
AC97_SINGLE("ALC Decay Time ", AC97_CODEC_CLASS_REV, 4, 15, 0),
AC97_SINGLE("ALC Attack Time", AC97_CODEC_CLASS_REV, 0, 15, 0),
AC97_ENUM("ALC Function", wm9713_क्रमागत[5]),
AC97_SINGLE("ALC Max Volume", AC97_PCI_SVID, 11, 7, 0),
AC97_SINGLE("ALC ZC Timeout", AC97_PCI_SVID, 9, 3, 0),
AC97_SINGLE("ALC ZC Switch", AC97_PCI_SVID, 8, 1, 0),
AC97_SINGLE("ALC NG Switch", AC97_PCI_SVID, 7, 1, 0),
AC97_ENUM("ALC NG Type", wm9713_क्रमागत[13]),
AC97_SINGLE("ALC NG Threshold", AC97_PCI_SVID, 0, 31, 0),

AC97_DOUBLE("Master ZC Switch", AC97_MASTER, 14, 6, 1, 0),
AC97_DOUBLE("Headphone ZC Switch", AC97_HEADPHONE, 14, 6, 1, 0),
AC97_DOUBLE("Out3/4 ZC Switch", AC97_MASTER_MONO, 14, 6, 1, 0),
AC97_SINGLE("Master Right Switch", AC97_MASTER, 7, 1, 1),
AC97_SINGLE("Headphone Right Switch", AC97_HEADPHONE, 7, 1, 1),
AC97_SINGLE("Out3/4 Right Switch", AC97_MASTER_MONO, 7, 1, 1),

AC97_SINGLE("Mono In to Headphone Switch", AC97_MASTER_TONE, 15, 1, 1),
AC97_SINGLE("Mono In to Master Switch", AC97_MASTER_TONE, 14, 1, 1),
AC97_SINGLE("Mono In Volume", AC97_MASTER_TONE, 8, 31, 1),
AC97_SINGLE("Mono Switch", AC97_MASTER_TONE, 7, 1, 1),
AC97_SINGLE("Mono ZC Switch", AC97_MASTER_TONE, 6, 1, 0),
AC97_SINGLE("Mono Volume", AC97_MASTER_TONE, 0, 31, 1),

AC97_SINGLE("Beep to Headphone Switch", AC97_AUX, 15, 1, 1),
AC97_SINGLE("Beep to Headphone Volume", AC97_AUX, 12, 7, 1),
AC97_SINGLE("Beep to Master Switch", AC97_AUX, 11, 1, 1),
AC97_SINGLE("Beep to Master Volume", AC97_AUX, 8, 7, 1),
AC97_SINGLE("Beep to Mono Switch", AC97_AUX, 7, 1, 1),
AC97_SINGLE("Beep to Mono Volume", AC97_AUX, 4, 7, 1),

AC97_SINGLE("Voice to Headphone Switch", AC97_PCM, 15, 1, 1),
AC97_SINGLE("Voice to Headphone Volume", AC97_PCM, 12, 7, 1),
AC97_SINGLE("Voice to Master Switch", AC97_PCM, 11, 1, 1),
AC97_SINGLE("Voice to Master Volume", AC97_PCM, 8, 7, 1),
AC97_SINGLE("Voice to Mono Switch", AC97_PCM, 7, 1, 1),
AC97_SINGLE("Voice to Mono Volume", AC97_PCM, 4, 7, 1),

AC97_SINGLE("Aux to Headphone Switch", AC97_REC_SEL, 15, 1, 1),
AC97_SINGLE("Aux to Headphone Volume", AC97_REC_SEL, 12, 7, 1),
AC97_SINGLE("Aux to Master Switch", AC97_REC_SEL, 11, 1, 1),
AC97_SINGLE("Aux to Master Volume", AC97_REC_SEL, 8, 7, 1),
AC97_SINGLE("Aux to Mono Switch", AC97_REC_SEL, 7, 1, 1),
AC97_SINGLE("Aux to Mono Volume", AC97_REC_SEL, 4, 7, 1),

AC97_ENUM("Mono Input Mux", wm9713_क्रमागत[6]),
AC97_ENUM("Master Input Mux", wm9713_क्रमागत[7]),
AC97_ENUM("Headphone Input Mux", wm9713_क्रमागत[8]),
AC97_ENUM("Out 3 Input Mux", wm9713_क्रमागत[9]),
AC97_ENUM("Out 4 Input Mux", wm9713_क्रमागत[10]),

AC97_ENUM("Bass Control", wm9713_क्रमागत[12]),
AC97_SINGLE("Bass Cut-off Switch", AC97_GENERAL_PURPOSE, 12, 1, 1),
AC97_SINGLE("Tone Cut-off Switch", AC97_GENERAL_PURPOSE, 4, 1, 1),
AC97_SINGLE("Playback Attenuate (-6dB) Switch", AC97_GENERAL_PURPOSE, 6, 1, 0),
AC97_SINGLE("Bass Volume", AC97_GENERAL_PURPOSE, 8, 15, 1),
AC97_SINGLE("Tone Volume", AC97_GENERAL_PURPOSE, 0, 15, 1),
पूर्ण;

अटल स्थिर काष्ठा snd_kcontrol_new wm13_snd_ac97_controls_3d[] = अणु
AC97_ENUM("Inv Input Mux", wm9713_क्रमागत[11]),
AC97_SINGLE("3D Upper Cut-off Switch", AC97_REC_GAIN_MIC, 5, 1, 0),
AC97_SINGLE("3D Lower Cut-off Switch", AC97_REC_GAIN_MIC, 4, 1, 0),
AC97_SINGLE("3D Depth", AC97_REC_GAIN_MIC, 0, 15, 1),
पूर्ण;

अटल पूर्णांक patch_wolfson_wm9713_3d (काष्ठा snd_ac97 * ac97)
अणु
	पूर्णांक err, i;
    
	क्रम (i = 0; i < ARRAY_SIZE(wm13_snd_ac97_controls_3d); i++) अणु
		अगर ((err = snd_ctl_add(ac97->bus->card, snd_ac97_cnew(&wm13_snd_ac97_controls_3d[i], ac97))) < 0)
			वापस err;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक patch_wolfson_wm9713_specअगरic(काष्ठा snd_ac97 * ac97)
अणु
	पूर्णांक err, i;
	
	क्रम (i = 0; i < ARRAY_SIZE(wm13_snd_ac97_controls); i++) अणु
		अगर ((err = snd_ctl_add(ac97->bus->card, snd_ac97_cnew(&wm13_snd_ac97_controls[i], ac97))) < 0)
			वापस err;
	पूर्ण
	snd_ac97_ग_लिखो_cache(ac97, AC97_PC_BEEP, 0x0808);
	snd_ac97_ग_लिखो_cache(ac97, AC97_PHONE, 0x0808);
	snd_ac97_ग_लिखो_cache(ac97, AC97_MIC, 0x0808);
	snd_ac97_ग_लिखो_cache(ac97, AC97_LINE, 0x00da);
	snd_ac97_ग_लिखो_cache(ac97, AC97_CD, 0x0808);
	snd_ac97_ग_लिखो_cache(ac97, AC97_VIDEO, 0xd612);
	snd_ac97_ग_लिखो_cache(ac97, AC97_REC_GAIN, 0x1ba0);
	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_PM
अटल व्योम patch_wolfson_wm9713_suspend (काष्ठा snd_ac97 * ac97)
अणु
	snd_ac97_ग_लिखो_cache(ac97, AC97_EXTENDED_MID, 0xfeff);
	snd_ac97_ग_लिखो_cache(ac97, AC97_EXTENDED_MSTATUS, 0xffff);
पूर्ण

अटल व्योम patch_wolfson_wm9713_resume (काष्ठा snd_ac97 * ac97)
अणु
	snd_ac97_ग_लिखो_cache(ac97, AC97_EXTENDED_MID, 0xda00);
	snd_ac97_ग_लिखो_cache(ac97, AC97_EXTENDED_MSTATUS, 0x3810);
	snd_ac97_ग_लिखो_cache(ac97, AC97_POWERDOWN, 0x0);
पूर्ण
#पूर्ण_अगर

अटल स्थिर काष्ठा snd_ac97_build_ops patch_wolfson_wm9713_ops = अणु
	.build_specअगरic = patch_wolfson_wm9713_specअगरic,
	.build_3d = patch_wolfson_wm9713_3d,
#अगर_घोषित CONFIG_PM	
	.suspend = patch_wolfson_wm9713_suspend,
	.resume = patch_wolfson_wm9713_resume
#पूर्ण_अगर
पूर्ण;

अटल पूर्णांक patch_wolfson13(काष्ठा snd_ac97 * ac97)
अणु
	/* WM9713, WM9714 */
	ac97->build_ops = &patch_wolfson_wm9713_ops;

	ac97->flags |= AC97_HAS_NO_REC_GAIN | AC97_STEREO_MUTES | AC97_HAS_NO_PHONE |
		AC97_HAS_NO_PC_BEEP | AC97_HAS_NO_VIDEO | AC97_HAS_NO_CD | AC97_HAS_NO_TONE |
		AC97_HAS_NO_STD_PCM;
    	ac97->scaps &= ~AC97_SCAP_MODEM;

	snd_ac97_ग_लिखो_cache(ac97, AC97_EXTENDED_MID, 0xda00);
	snd_ac97_ग_लिखो_cache(ac97, AC97_EXTENDED_MSTATUS, 0x3810);
	snd_ac97_ग_लिखो_cache(ac97, AC97_POWERDOWN, 0x0);

	वापस 0;
पूर्ण

/*
 * Tritech codec
 */
अटल पूर्णांक patch_tritech_tr28028(काष्ठा snd_ac97 * ac97)
अणु
	snd_ac97_ग_लिखो_cache(ac97, 0x26, 0x0300);
	snd_ac97_ग_लिखो_cache(ac97, 0x26, 0x0000);
	snd_ac97_ग_लिखो_cache(ac97, AC97_SURROUND_MASTER, 0x0000);
	snd_ac97_ग_लिखो_cache(ac97, AC97_SPDIF, 0x0000);
	वापस 0;
पूर्ण

/*
 * Sigmatel STAC97xx codecs
 */
अटल पूर्णांक patch_sigmatel_stac9700_3d(काष्ठा snd_ac97 * ac97)
अणु
	काष्ठा snd_kcontrol *kctl;
	पूर्णांक err;

	अगर ((err = snd_ctl_add(ac97->bus->card, kctl = snd_ac97_cnew(&snd_ac97_controls_3d[0], ac97))) < 0)
		वापस err;
	म_नकल(kctl->id.name, "3D Control Sigmatel - Depth");
	kctl->निजी_value = AC97_SINGLE_VALUE(AC97_3D_CONTROL, 2, 3, 0);
	snd_ac97_ग_लिखो_cache(ac97, AC97_3D_CONTROL, 0x0000);
	वापस 0;
पूर्ण

अटल पूर्णांक patch_sigmatel_stac9708_3d(काष्ठा snd_ac97 * ac97)
अणु
	काष्ठा snd_kcontrol *kctl;
	पूर्णांक err;

	अगर ((err = snd_ctl_add(ac97->bus->card, kctl = snd_ac97_cnew(&snd_ac97_controls_3d[0], ac97))) < 0)
		वापस err;
	म_नकल(kctl->id.name, "3D Control Sigmatel - Depth");
	kctl->निजी_value = AC97_SINGLE_VALUE(AC97_3D_CONTROL, 0, 3, 0);
	अगर ((err = snd_ctl_add(ac97->bus->card, kctl = snd_ac97_cnew(&snd_ac97_controls_3d[0], ac97))) < 0)
		वापस err;
	म_नकल(kctl->id.name, "3D Control Sigmatel - Rear Depth");
	kctl->निजी_value = AC97_SINGLE_VALUE(AC97_3D_CONTROL, 2, 3, 0);
	snd_ac97_ग_लिखो_cache(ac97, AC97_3D_CONTROL, 0x0000);
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा snd_kcontrol_new snd_ac97_sigmatel_4speaker =
AC97_SINGLE("Sigmatel 4-Speaker Stereo Playback Switch",
		AC97_SIGMATEL_DAC2INVERT, 2, 1, 0);

/* "Sigmatel " हटाओd due to excessive name length: */
अटल स्थिर काष्ठा snd_kcontrol_new snd_ac97_sigmatel_phaseinvert =
AC97_SINGLE("Surround Phase Inversion Playback Switch",
		AC97_SIGMATEL_DAC2INVERT, 3, 1, 0);

अटल स्थिर काष्ठा snd_kcontrol_new snd_ac97_sigmatel_controls[] = अणु
AC97_SINGLE("Sigmatel DAC 6dB Attenuate", AC97_SIGMATEL_ANALOG, 1, 1, 0),
AC97_SINGLE("Sigmatel ADC 6dB Attenuate", AC97_SIGMATEL_ANALOG, 0, 1, 0)
पूर्ण;

अटल पूर्णांक patch_sigmatel_stac97xx_specअगरic(काष्ठा snd_ac97 * ac97)
अणु
	पूर्णांक err;

	snd_ac97_ग_लिखो_cache(ac97, AC97_SIGMATEL_ANALOG, snd_ac97_पढ़ो(ac97, AC97_SIGMATEL_ANALOG) & ~0x0003);
	अगर (snd_ac97_try_bit(ac97, AC97_SIGMATEL_ANALOG, 1))
		अगर ((err = patch_build_controls(ac97, &snd_ac97_sigmatel_controls[0], 1)) < 0)
			वापस err;
	अगर (snd_ac97_try_bit(ac97, AC97_SIGMATEL_ANALOG, 0))
		अगर ((err = patch_build_controls(ac97, &snd_ac97_sigmatel_controls[1], 1)) < 0)
			वापस err;
	अगर (snd_ac97_try_bit(ac97, AC97_SIGMATEL_DAC2INVERT, 2))
		अगर ((err = patch_build_controls(ac97, &snd_ac97_sigmatel_4speaker, 1)) < 0)
			वापस err;
	अगर (snd_ac97_try_bit(ac97, AC97_SIGMATEL_DAC2INVERT, 3))
		अगर ((err = patch_build_controls(ac97, &snd_ac97_sigmatel_phaseinvert, 1)) < 0)
			वापस err;
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा snd_ac97_build_ops patch_sigmatel_stac9700_ops = अणु
	.build_3d	= patch_sigmatel_stac9700_3d,
	.build_specअगरic	= patch_sigmatel_stac97xx_specअगरic
पूर्ण;

अटल पूर्णांक patch_sigmatel_stac9700(काष्ठा snd_ac97 * ac97)
अणु
	ac97->build_ops = &patch_sigmatel_stac9700_ops;
	वापस 0;
पूर्ण

अटल पूर्णांक snd_ac97_stac9708_put_bias(काष्ठा snd_kcontrol *kcontrol, काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_ac97 *ac97 = snd_kcontrol_chip(kcontrol);
	पूर्णांक err;

	mutex_lock(&ac97->page_mutex);
	snd_ac97_ग_लिखो(ac97, AC97_SIGMATEL_BIAS1, 0xabba);
	err = snd_ac97_update_bits(ac97, AC97_SIGMATEL_BIAS2, 0x0010,
				   (ucontrol->value.पूर्णांकeger.value[0] & 1) << 4);
	snd_ac97_ग_लिखो(ac97, AC97_SIGMATEL_BIAS1, 0);
	mutex_unlock(&ac97->page_mutex);
	वापस err;
पूर्ण

अटल स्थिर काष्ठा snd_kcontrol_new snd_ac97_stac9708_bias_control = अणु
	.अगरace = SNDRV_CTL_ELEM_IFACE_MIXER,
	.name = "Sigmatel Output Bias Switch",
	.info = snd_ac97_info_volsw,
	.get = snd_ac97_get_volsw,
	.put = snd_ac97_stac9708_put_bias,
	.निजी_value = AC97_SINGLE_VALUE(AC97_SIGMATEL_BIAS2, 4, 1, 0),
पूर्ण;

अटल पूर्णांक patch_sigmatel_stac9708_specअगरic(काष्ठा snd_ac97 *ac97)
अणु
	पूर्णांक err;

	/* the रेजिस्टर bit is writable, but the function is not implemented: */
	snd_ac97_हटाओ_ctl(ac97, "PCM Out Path & Mute", शून्य);

	snd_ac97_नाम_vol_ctl(ac97, "Headphone Playback", "Sigmatel Surround Playback");
	अगर ((err = patch_build_controls(ac97, &snd_ac97_stac9708_bias_control, 1)) < 0)
		वापस err;
	वापस patch_sigmatel_stac97xx_specअगरic(ac97);
पूर्ण

अटल स्थिर काष्ठा snd_ac97_build_ops patch_sigmatel_stac9708_ops = अणु
	.build_3d	= patch_sigmatel_stac9708_3d,
	.build_specअगरic	= patch_sigmatel_stac9708_specअगरic
पूर्ण;

अटल पूर्णांक patch_sigmatel_stac9708(काष्ठा snd_ac97 * ac97)
अणु
	अचिन्हित पूर्णांक codec72, codec6c;

	ac97->build_ops = &patch_sigmatel_stac9708_ops;
	ac97->caps |= 0x10;	/* HP (sigmatel surround) support */

	codec72 = snd_ac97_पढ़ो(ac97, AC97_SIGMATEL_BIAS2) & 0x8000;
	codec6c = snd_ac97_पढ़ो(ac97, AC97_SIGMATEL_ANALOG);

	अगर ((codec72==0) && (codec6c==0)) अणु
		snd_ac97_ग_लिखो_cache(ac97, AC97_SIGMATEL_CIC1, 0xabba);
		snd_ac97_ग_लिखो_cache(ac97, AC97_SIGMATEL_CIC2, 0x1000);
		snd_ac97_ग_लिखो_cache(ac97, AC97_SIGMATEL_BIAS1, 0xabba);
		snd_ac97_ग_लिखो_cache(ac97, AC97_SIGMATEL_BIAS2, 0x0007);
	पूर्ण अन्यथा अगर ((codec72==0x8000) && (codec6c==0)) अणु
		snd_ac97_ग_लिखो_cache(ac97, AC97_SIGMATEL_CIC1, 0xabba);
		snd_ac97_ग_लिखो_cache(ac97, AC97_SIGMATEL_CIC2, 0x1001);
		snd_ac97_ग_लिखो_cache(ac97, AC97_SIGMATEL_DAC2INVERT, 0x0008);
	पूर्ण अन्यथा अगर ((codec72==0x8000) && (codec6c==0x0080)) अणु
		/* nothing */
	पूर्ण
	snd_ac97_ग_लिखो_cache(ac97, AC97_SIGMATEL_MULTICHN, 0x0000);
	वापस 0;
पूर्ण

अटल पूर्णांक patch_sigmatel_stac9721(काष्ठा snd_ac97 * ac97)
अणु
	ac97->build_ops = &patch_sigmatel_stac9700_ops;
	अगर (snd_ac97_पढ़ो(ac97, AC97_SIGMATEL_ANALOG) == 0) अणु
		// patch क्रम SigmaTel
		snd_ac97_ग_लिखो_cache(ac97, AC97_SIGMATEL_CIC1, 0xabba);
		snd_ac97_ग_लिखो_cache(ac97, AC97_SIGMATEL_CIC2, 0x4000);
		snd_ac97_ग_लिखो_cache(ac97, AC97_SIGMATEL_BIAS1, 0xabba);
		snd_ac97_ग_लिखो_cache(ac97, AC97_SIGMATEL_BIAS2, 0x0002);
	पूर्ण
	snd_ac97_ग_लिखो_cache(ac97, AC97_SIGMATEL_MULTICHN, 0x0000);
	वापस 0;
पूर्ण

अटल पूर्णांक patch_sigmatel_stac9744(काष्ठा snd_ac97 * ac97)
अणु
	// patch क्रम SigmaTel
	ac97->build_ops = &patch_sigmatel_stac9700_ops;
	snd_ac97_ग_लिखो_cache(ac97, AC97_SIGMATEL_CIC1, 0xabba);
	snd_ac97_ग_लिखो_cache(ac97, AC97_SIGMATEL_CIC2, 0x0000);	/* is this correct? --jk */
	snd_ac97_ग_लिखो_cache(ac97, AC97_SIGMATEL_BIAS1, 0xabba);
	snd_ac97_ग_लिखो_cache(ac97, AC97_SIGMATEL_BIAS2, 0x0002);
	snd_ac97_ग_लिखो_cache(ac97, AC97_SIGMATEL_MULTICHN, 0x0000);
	वापस 0;
पूर्ण

अटल पूर्णांक patch_sigmatel_stac9756(काष्ठा snd_ac97 * ac97)
अणु
	// patch क्रम SigmaTel
	ac97->build_ops = &patch_sigmatel_stac9700_ops;
	snd_ac97_ग_लिखो_cache(ac97, AC97_SIGMATEL_CIC1, 0xabba);
	snd_ac97_ग_लिखो_cache(ac97, AC97_SIGMATEL_CIC2, 0x0000);	/* is this correct? --jk */
	snd_ac97_ग_लिखो_cache(ac97, AC97_SIGMATEL_BIAS1, 0xabba);
	snd_ac97_ग_लिखो_cache(ac97, AC97_SIGMATEL_BIAS2, 0x0002);
	snd_ac97_ग_लिखो_cache(ac97, AC97_SIGMATEL_MULTICHN, 0x0000);
	वापस 0;
पूर्ण

अटल पूर्णांक snd_ac97_stac9758_output_jack_info(काष्ठा snd_kcontrol *kcontrol, काष्ठा snd_ctl_elem_info *uinfo)
अणु
	अटल स्थिर अक्षर * स्थिर texts[5] = अणु
		"Input/Disabled", "Front Output",
		"Rear Output", "Center/LFE Output", "Mixer Output" पूर्ण;

	वापस snd_ctl_क्रमागत_info(uinfo, 1, 5, texts);
पूर्ण

अटल पूर्णांक snd_ac97_stac9758_output_jack_get(काष्ठा snd_kcontrol *kcontrol, काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_ac97 *ac97 = snd_kcontrol_chip(kcontrol);
	पूर्णांक shअगरt = kcontrol->निजी_value;
	अचिन्हित लघु val;

	val = ac97->regs[AC97_SIGMATEL_OUTSEL] >> shअगरt;
	अगर (!(val & 4))
		ucontrol->value.क्रमागतerated.item[0] = 0;
	अन्यथा
		ucontrol->value.क्रमागतerated.item[0] = 1 + (val & 3);
	वापस 0;
पूर्ण

अटल पूर्णांक snd_ac97_stac9758_output_jack_put(काष्ठा snd_kcontrol *kcontrol, काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_ac97 *ac97 = snd_kcontrol_chip(kcontrol);
	पूर्णांक shअगरt = kcontrol->निजी_value;
	अचिन्हित लघु val;

	अगर (ucontrol->value.क्रमागतerated.item[0] > 4)
		वापस -EINVAL;
	अगर (ucontrol->value.क्रमागतerated.item[0] == 0)
		val = 0;
	अन्यथा
		val = 4 | (ucontrol->value.क्रमागतerated.item[0] - 1);
	वापस ac97_update_bits_page(ac97, AC97_SIGMATEL_OUTSEL,
				     7 << shअगरt, val << shअगरt, 0);
पूर्ण

अटल पूर्णांक snd_ac97_stac9758_input_jack_info(काष्ठा snd_kcontrol *kcontrol, काष्ठा snd_ctl_elem_info *uinfo)
अणु
	अटल स्थिर अक्षर * स्थिर texts[7] = अणु
		"Mic2 Jack", "Mic1 Jack", "Line In Jack",
		"Front Jack", "Rear Jack", "Center/LFE Jack", "Mute" पूर्ण;

	वापस snd_ctl_क्रमागत_info(uinfo, 1, 7, texts);
पूर्ण

अटल पूर्णांक snd_ac97_stac9758_input_jack_get(काष्ठा snd_kcontrol *kcontrol, काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_ac97 *ac97 = snd_kcontrol_chip(kcontrol);
	पूर्णांक shअगरt = kcontrol->निजी_value;
	अचिन्हित लघु val;

	val = ac97->regs[AC97_SIGMATEL_INSEL];
	ucontrol->value.क्रमागतerated.item[0] = (val >> shअगरt) & 7;
	वापस 0;
पूर्ण

अटल पूर्णांक snd_ac97_stac9758_input_jack_put(काष्ठा snd_kcontrol *kcontrol, काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_ac97 *ac97 = snd_kcontrol_chip(kcontrol);
	पूर्णांक shअगरt = kcontrol->निजी_value;

	वापस ac97_update_bits_page(ac97, AC97_SIGMATEL_INSEL, 7 << shअगरt,
				     ucontrol->value.क्रमागतerated.item[0] << shअगरt, 0);
पूर्ण

अटल पूर्णांक snd_ac97_stac9758_phonesel_info(काष्ठा snd_kcontrol *kcontrol, काष्ठा snd_ctl_elem_info *uinfo)
अणु
	अटल स्थिर अक्षर * स्थिर texts[3] = अणु
		"None", "Front Jack", "Rear Jack"
	पूर्ण;

	वापस snd_ctl_क्रमागत_info(uinfo, 1, 3, texts);
पूर्ण

अटल पूर्णांक snd_ac97_stac9758_phonesel_get(काष्ठा snd_kcontrol *kcontrol, काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_ac97 *ac97 = snd_kcontrol_chip(kcontrol);

	ucontrol->value.क्रमागतerated.item[0] = ac97->regs[AC97_SIGMATEL_IOMISC] & 3;
	वापस 0;
पूर्ण

अटल पूर्णांक snd_ac97_stac9758_phonesel_put(काष्ठा snd_kcontrol *kcontrol, काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_ac97 *ac97 = snd_kcontrol_chip(kcontrol);

	वापस ac97_update_bits_page(ac97, AC97_SIGMATEL_IOMISC, 3,
				     ucontrol->value.क्रमागतerated.item[0], 0);
पूर्ण

#घोषणा STAC9758_OUTPUT_JACK(xname, shअगरt) \
अणु	.अगरace = SNDRV_CTL_ELEM_IFACE_MIXER, .name = xname, \
	.info = snd_ac97_stac9758_output_jack_info, \
	.get = snd_ac97_stac9758_output_jack_get, \
	.put = snd_ac97_stac9758_output_jack_put, \
	.निजी_value = shअगरt पूर्ण
#घोषणा STAC9758_INPUT_JACK(xname, shअगरt) \
अणु	.अगरace = SNDRV_CTL_ELEM_IFACE_MIXER, .name = xname, \
	.info = snd_ac97_stac9758_input_jack_info, \
	.get = snd_ac97_stac9758_input_jack_get, \
	.put = snd_ac97_stac9758_input_jack_put, \
	.निजी_value = shअगरt पूर्ण
अटल स्थिर काष्ठा snd_kcontrol_new snd_ac97_sigmatel_stac9758_controls[] = अणु
	STAC9758_OUTPUT_JACK("Mic1 Jack", 1),
	STAC9758_OUTPUT_JACK("LineIn Jack", 4),
	STAC9758_OUTPUT_JACK("Front Jack", 7),
	STAC9758_OUTPUT_JACK("Rear Jack", 10),
	STAC9758_OUTPUT_JACK("Center/LFE Jack", 13),
	STAC9758_INPUT_JACK("Mic Input Source", 0),
	STAC9758_INPUT_JACK("Line Input Source", 8),
	अणु
		.अगरace = SNDRV_CTL_ELEM_IFACE_MIXER,
		.name = "Headphone Amp",
		.info = snd_ac97_stac9758_phonesel_info,
		.get = snd_ac97_stac9758_phonesel_get,
		.put = snd_ac97_stac9758_phonesel_put
	पूर्ण,
	AC97_SINGLE("Exchange Center/LFE", AC97_SIGMATEL_IOMISC, 4, 1, 0),
	AC97_SINGLE("Headphone +3dB Boost", AC97_SIGMATEL_IOMISC, 8, 1, 0)
पूर्ण;

अटल पूर्णांक patch_sigmatel_stac9758_specअगरic(काष्ठा snd_ac97 *ac97)
अणु
	पूर्णांक err;

	err = patch_sigmatel_stac97xx_specअगरic(ac97);
	अगर (err < 0)
		वापस err;
	err = patch_build_controls(ac97, snd_ac97_sigmatel_stac9758_controls,
				   ARRAY_SIZE(snd_ac97_sigmatel_stac9758_controls));
	अगर (err < 0)
		वापस err;
	/* DAC-A direct */
	snd_ac97_नाम_vol_ctl(ac97, "Headphone Playback", "Front Playback");
	/* DAC-A to Mix = PCM */
	/* DAC-B direct = Surround */
	/* DAC-B to Mix */
	snd_ac97_नाम_vol_ctl(ac97, "Video Playback", "Surround Mix Playback");
	/* DAC-C direct = Center/LFE */

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा snd_ac97_build_ops patch_sigmatel_stac9758_ops = अणु
	.build_3d	= patch_sigmatel_stac9700_3d,
	.build_specअगरic	= patch_sigmatel_stac9758_specअगरic
पूर्ण;

अटल पूर्णांक patch_sigmatel_stac9758(काष्ठा snd_ac97 * ac97)
अणु
	अटल स्थिर अचिन्हित लघु regs[4] = अणु
		AC97_SIGMATEL_OUTSEL,
		AC97_SIGMATEL_IOMISC,
		AC97_SIGMATEL_INSEL,
		AC97_SIGMATEL_VARIOUS
	पूर्ण;
	अटल स्थिर अचिन्हित लघु def_regs[4] = अणु
		/* OUTSEL */ 0xd794, /* CL:CL, SR:SR, LO:MX, LI:DS, MI:DS */
		/* IOMISC */ 0x2001,
		/* INSEL */ 0x0201, /* LI:LI, MI:M1 */
		/* VARIOUS */ 0x0040
	पूर्ण;
	अटल स्थिर अचिन्हित लघु m675_regs[4] = अणु
		/* OUTSEL */ 0xfc70, /* CL:MX, SR:MX, LO:DS, LI:MX, MI:DS */
		/* IOMISC */ 0x2102, /* HP amp on */
		/* INSEL */ 0x0203, /* LI:LI, MI:FR */
		/* VARIOUS */ 0x0041 /* stereo mic */
	पूर्ण;
	स्थिर अचिन्हित लघु *pregs = def_regs;
	पूर्णांक i;

	/* Gateway M675 notebook */
	अगर (ac97->pci && 
	    ac97->subप्रणाली_venकरोr == 0x107b &&
	    ac97->subप्रणाली_device == 0x0601)
	    	pregs = m675_regs;

	// patch क्रम SigmaTel
	ac97->build_ops = &patch_sigmatel_stac9758_ops;
	/* FIXME: assume only page 0 क्रम writing cache */
	snd_ac97_update_bits(ac97, AC97_INT_PAGING, AC97_PAGE_MASK, AC97_PAGE_VENDOR);
	क्रम (i = 0; i < 4; i++)
		snd_ac97_ग_लिखो_cache(ac97, regs[i], pregs[i]);

	ac97->flags |= AC97_STEREO_MUTES;
	वापस 0;
पूर्ण

/*
 * Cirrus Logic CS42xx codecs
 */
अटल स्थिर काष्ठा snd_kcontrol_new snd_ac97_cirrus_controls_spdअगर[2] = अणु
	AC97_SINGLE(SNDRV_CTL_NAME_IEC958("",PLAYBACK,SWITCH), AC97_CSR_SPDIF, 15, 1, 0),
	AC97_SINGLE(SNDRV_CTL_NAME_IEC958("",PLAYBACK,NONE) "AC97-SPSA", AC97_CSR_ACMODE, 0, 3, 0)
पूर्ण;

अटल पूर्णांक patch_cirrus_build_spdअगर(काष्ठा snd_ac97 * ac97)
अणु
	पूर्णांक err;

	/* con mask, pro mask, शेष */
	अगर ((err = patch_build_controls(ac97, &snd_ac97_controls_spdअगर[0], 3)) < 0)
		वापस err;
	/* चयन, spsa */
	अगर ((err = patch_build_controls(ac97, &snd_ac97_cirrus_controls_spdअगर[0], 1)) < 0)
		वापस err;
	चयन (ac97->id & AC97_ID_CS_MASK) अणु
	हाल AC97_ID_CS4205:
		अगर ((err = patch_build_controls(ac97, &snd_ac97_cirrus_controls_spdअगर[1], 1)) < 0)
			वापस err;
		अवरोध;
	पूर्ण
	/* set शेष PCM S/PDIF params */
	/* consumer,PCM audio,no copyright,no preemphasis,PCM coder,original,48000Hz */
	snd_ac97_ग_लिखो_cache(ac97, AC97_CSR_SPDIF, 0x0a20);
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा snd_ac97_build_ops patch_cirrus_ops = अणु
	.build_spdअगर = patch_cirrus_build_spdअगर
पूर्ण;

अटल पूर्णांक patch_cirrus_spdअगर(काष्ठा snd_ac97 * ac97)
अणु
	/* Basically, the cs4201/cs4205/cs4297a has non-standard sp/dअगर रेजिस्टरs.
	   WHY CAN'T ANYONE FOLLOW THE BLOODY SPEC?  *sigh*
	   - sp/dअगर EA ID is not set, but sp/dअगर is always present.
	   - enable/disable is spdअगर रेजिस्टर bit 15.
	   - sp/dअगर control रेजिस्टर is 0x68.  dअगरfers from AC97:
	   - valid is bit 14 (vs 15)
	   - no DRS
	   - only 44.1/48k [00 = 48, 01=44,1] (AC97 is 00=44.1, 10=48)
	   - sp/dअगर ssource select is in 0x5e bits 0,1.
	*/

	ac97->build_ops = &patch_cirrus_ops;
	ac97->flags |= AC97_CS_SPDIF; 
	ac97->rates[AC97_RATES_SPDIF] &= ~SNDRV_PCM_RATE_32000;
        ac97->ext_id |= AC97_EI_SPDIF;	/* क्रमce the detection of spdअगर */
	snd_ac97_ग_लिखो_cache(ac97, AC97_CSR_ACMODE, 0x0080);
	वापस 0;
पूर्ण

अटल पूर्णांक patch_cirrus_cs4299(काष्ठा snd_ac97 * ac97)
अणु
	/* क्रमce the detection of PC Beep */
	ac97->flags |= AC97_HAS_PC_BEEP;
	
	वापस patch_cirrus_spdअगर(ac97);
पूर्ण

/*
 * Conexant codecs
 */
अटल स्थिर काष्ठा snd_kcontrol_new snd_ac97_conexant_controls_spdअगर[1] = अणु
	AC97_SINGLE(SNDRV_CTL_NAME_IEC958("",PLAYBACK,SWITCH), AC97_CXR_AUDIO_MISC, 3, 1, 0),
पूर्ण;

अटल पूर्णांक patch_conexant_build_spdअगर(काष्ठा snd_ac97 * ac97)
अणु
	पूर्णांक err;

	/* con mask, pro mask, शेष */
	अगर ((err = patch_build_controls(ac97, &snd_ac97_controls_spdअगर[0], 3)) < 0)
		वापस err;
	/* चयन */
	अगर ((err = patch_build_controls(ac97, &snd_ac97_conexant_controls_spdअगर[0], 1)) < 0)
		वापस err;
	/* set शेष PCM S/PDIF params */
	/* consumer,PCM audio,no copyright,no preemphasis,PCM coder,original,48000Hz */
	snd_ac97_ग_लिखो_cache(ac97, AC97_CXR_AUDIO_MISC,
			     snd_ac97_पढ़ो(ac97, AC97_CXR_AUDIO_MISC) & ~(AC97_CXR_SPDIFEN|AC97_CXR_COPYRGT|AC97_CXR_SPDIF_MASK));
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा snd_ac97_build_ops patch_conexant_ops = अणु
	.build_spdअगर = patch_conexant_build_spdअगर
पूर्ण;

अटल पूर्णांक patch_conexant(काष्ठा snd_ac97 * ac97)
अणु
	ac97->build_ops = &patch_conexant_ops;
	ac97->flags |= AC97_CX_SPDIF;
        ac97->ext_id |= AC97_EI_SPDIF;	/* क्रमce the detection of spdअगर */
	ac97->rates[AC97_RATES_SPDIF] = SNDRV_PCM_RATE_48000; /* 48k only */
	वापस 0;
पूर्ण

अटल पूर्णांक patch_cx20551(काष्ठा snd_ac97 *ac97)
अणु
	snd_ac97_update_bits(ac97, 0x5c, 0x01, 0x01);
	वापस 0;
पूर्ण

/*
 * Analog Devices AD18xx, AD19xx codecs
 */
#अगर_घोषित CONFIG_PM
अटल व्योम ad18xx_resume(काष्ठा snd_ac97 *ac97)
अणु
	अटल स्थिर अचिन्हित लघु setup_regs[] = अणु
		AC97_AD_MISC, AC97_AD_SERIAL_CFG, AC97_AD_JACK_SPDIF,
	पूर्ण;
	पूर्णांक i, codec;

	क्रम (i = 0; i < (पूर्णांक)ARRAY_SIZE(setup_regs); i++) अणु
		अचिन्हित लघु reg = setup_regs[i];
		अगर (test_bit(reg, ac97->reg_accessed)) अणु
			snd_ac97_ग_लिखो(ac97, reg, ac97->regs[reg]);
			snd_ac97_पढ़ो(ac97, reg);
		पूर्ण
	पूर्ण

	अगर (! (ac97->flags & AC97_AD_MULTI))
		/* normal restore */
		snd_ac97_restore_status(ac97);
	अन्यथा अणु
		/* restore the AD18xx codec configurations */
		क्रम (codec = 0; codec < 3; codec++) अणु
			अगर (! ac97->spec.ad18xx.id[codec])
				जारी;
			/* select single codec */
			snd_ac97_update_bits(ac97, AC97_AD_SERIAL_CFG, 0x7000,
					     ac97->spec.ad18xx.unchained[codec] | ac97->spec.ad18xx.chained[codec]);
			ac97->bus->ops->ग_लिखो(ac97, AC97_AD_CODEC_CFG, ac97->spec.ad18xx.codec_cfg[codec]);
		पूर्ण
		/* select all codecs */
		snd_ac97_update_bits(ac97, AC97_AD_SERIAL_CFG, 0x7000, 0x7000);

		/* restore status */
		क्रम (i = 2; i < 0x7c ; i += 2) अणु
			अगर (i == AC97_POWERDOWN || i == AC97_EXTENDED_ID)
				जारी;
			अगर (test_bit(i, ac97->reg_accessed)) अणु
				/* handle multi codecs क्रम AD18xx */
				अगर (i == AC97_PCM) अणु
					क्रम (codec = 0; codec < 3; codec++) अणु
						अगर (! ac97->spec.ad18xx.id[codec])
							जारी;
						/* select single codec */
						snd_ac97_update_bits(ac97, AC97_AD_SERIAL_CFG, 0x7000,
								     ac97->spec.ad18xx.unchained[codec] | ac97->spec.ad18xx.chained[codec]);
						/* update PCM bits */
						ac97->bus->ops->ग_लिखो(ac97, AC97_PCM, ac97->spec.ad18xx.pcmreg[codec]);
					पूर्ण
					/* select all codecs */
					snd_ac97_update_bits(ac97, AC97_AD_SERIAL_CFG, 0x7000, 0x7000);
					जारी;
				पूर्ण अन्यथा अगर (i == AC97_AD_TEST ||
					   i == AC97_AD_CODEC_CFG ||
					   i == AC97_AD_SERIAL_CFG)
					जारी; /* ignore */
			पूर्ण
			snd_ac97_ग_लिखो(ac97, i, ac97->regs[i]);
			snd_ac97_पढ़ो(ac97, i);
		पूर्ण
	पूर्ण

	snd_ac97_restore_iec958(ac97);
पूर्ण

अटल व्योम ad1888_resume(काष्ठा snd_ac97 *ac97)
अणु
	ad18xx_resume(ac97);
	snd_ac97_ग_लिखो_cache(ac97, AC97_CODEC_CLASS_REV, 0x8080);
पूर्ण

#पूर्ण_अगर

अटल स्थिर काष्ठा snd_ac97_res_table ad1819_restbl[] = अणु
	अणु AC97_PHONE, 0x9f1f पूर्ण,
	अणु AC97_MIC, 0x9f1f पूर्ण,
	अणु AC97_LINE, 0x9f1f पूर्ण,
	अणु AC97_CD, 0x9f1f पूर्ण,
	अणु AC97_VIDEO, 0x9f1f पूर्ण,
	अणु AC97_AUX, 0x9f1f पूर्ण,
	अणु AC97_PCM, 0x9f1f पूर्ण,
	अणु पूर्ण /* terminator */
पूर्ण;

अटल पूर्णांक patch_ad1819(काष्ठा snd_ac97 * ac97)
अणु
	अचिन्हित लघु scfg;

	// patch क्रम Analog Devices
	scfg = snd_ac97_पढ़ो(ac97, AC97_AD_SERIAL_CFG);
	snd_ac97_ग_लिखो_cache(ac97, AC97_AD_SERIAL_CFG, scfg | 0x7000); /* select all codecs */
	ac97->res_table = ad1819_restbl;
	वापस 0;
पूर्ण

अटल अचिन्हित लघु patch_ad1881_unchained(काष्ठा snd_ac97 * ac97, पूर्णांक idx, अचिन्हित लघु mask)
अणु
	अचिन्हित लघु val;

	// test क्रम unchained codec
	snd_ac97_update_bits(ac97, AC97_AD_SERIAL_CFG, 0x7000, mask);
	snd_ac97_ग_लिखो_cache(ac97, AC97_AD_CODEC_CFG, 0x0000);	/* ID0C, ID1C, SDIE = off */
	val = snd_ac97_पढ़ो(ac97, AC97_VENDOR_ID2);
	अगर ((val & 0xff40) != 0x5340)
		वापस 0;
	ac97->spec.ad18xx.unchained[idx] = mask;
	ac97->spec.ad18xx.id[idx] = val;
	ac97->spec.ad18xx.codec_cfg[idx] = 0x0000;
	वापस mask;
पूर्ण

अटल पूर्णांक patch_ad1881_chained1(काष्ठा snd_ac97 * ac97, पूर्णांक idx, अचिन्हित लघु codec_bits)
अणु
	अटल स्थिर पूर्णांक cfg_bits[3] = अणु 1<<12, 1<<14, 1<<13 पूर्ण;
	अचिन्हित लघु val;
	
	snd_ac97_update_bits(ac97, AC97_AD_SERIAL_CFG, 0x7000, cfg_bits[idx]);
	snd_ac97_ग_लिखो_cache(ac97, AC97_AD_CODEC_CFG, 0x0004);	// SDIE
	val = snd_ac97_पढ़ो(ac97, AC97_VENDOR_ID2);
	अगर ((val & 0xff40) != 0x5340)
		वापस 0;
	अगर (codec_bits)
		snd_ac97_ग_लिखो_cache(ac97, AC97_AD_CODEC_CFG, codec_bits);
	ac97->spec.ad18xx.chained[idx] = cfg_bits[idx];
	ac97->spec.ad18xx.id[idx] = val;
	ac97->spec.ad18xx.codec_cfg[idx] = codec_bits ? codec_bits : 0x0004;
	वापस 1;
पूर्ण

अटल व्योम patch_ad1881_chained(काष्ठा snd_ac97 * ac97, पूर्णांक unchained_idx, पूर्णांक cidx1, पूर्णांक cidx2)
अणु
	// alपढ़ोy detected?
	अगर (ac97->spec.ad18xx.unchained[cidx1] || ac97->spec.ad18xx.chained[cidx1])
		cidx1 = -1;
	अगर (ac97->spec.ad18xx.unchained[cidx2] || ac97->spec.ad18xx.chained[cidx2])
		cidx2 = -1;
	अगर (cidx1 < 0 && cidx2 < 0)
		वापस;
	// test क्रम chained codecs
	snd_ac97_update_bits(ac97, AC97_AD_SERIAL_CFG, 0x7000,
			     ac97->spec.ad18xx.unchained[unchained_idx]);
	snd_ac97_ग_लिखो_cache(ac97, AC97_AD_CODEC_CFG, 0x0002);		// ID1C
	ac97->spec.ad18xx.codec_cfg[unchained_idx] = 0x0002;
	अगर (cidx1 >= 0) अणु
		अगर (cidx2 < 0)
			patch_ad1881_chained1(ac97, cidx1, 0);
		अन्यथा अगर (patch_ad1881_chained1(ac97, cidx1, 0x0006))	// SDIE | ID1C
			patch_ad1881_chained1(ac97, cidx2, 0);
		अन्यथा अगर (patch_ad1881_chained1(ac97, cidx2, 0x0006))	// SDIE | ID1C
			patch_ad1881_chained1(ac97, cidx1, 0);
	पूर्ण अन्यथा अगर (cidx2 >= 0) अणु
		patch_ad1881_chained1(ac97, cidx2, 0);
	पूर्ण
पूर्ण

अटल स्थिर काष्ठा snd_ac97_build_ops patch_ad1881_build_ops = अणु
#अगर_घोषित CONFIG_PM
	.resume = ad18xx_resume
#पूर्ण_अगर
पूर्ण;

अटल पूर्णांक patch_ad1881(काष्ठा snd_ac97 * ac97)
अणु
	अटल स्थिर अक्षर cfg_idxs[3][2] = अणु
		अणु2, 1पूर्ण,
		अणु0, 2पूर्ण,
		अणु0, 1पूर्ण
	पूर्ण;
	
	// patch क्रम Analog Devices
	अचिन्हित लघु codecs[3];
	अचिन्हित लघु val;
	पूर्णांक idx, num;

	val = snd_ac97_पढ़ो(ac97, AC97_AD_SERIAL_CFG);
	snd_ac97_ग_लिखो_cache(ac97, AC97_AD_SERIAL_CFG, val);
	codecs[0] = patch_ad1881_unchained(ac97, 0, (1<<12));
	codecs[1] = patch_ad1881_unchained(ac97, 1, (1<<14));
	codecs[2] = patch_ad1881_unchained(ac97, 2, (1<<13));

	अगर (! (codecs[0] || codecs[1] || codecs[2]))
		जाओ __end;

	क्रम (idx = 0; idx < 3; idx++)
		अगर (ac97->spec.ad18xx.unchained[idx])
			patch_ad1881_chained(ac97, idx, cfg_idxs[idx][0], cfg_idxs[idx][1]);

	अगर (ac97->spec.ad18xx.id[1]) अणु
		ac97->flags |= AC97_AD_MULTI;
		ac97->scaps |= AC97_SCAP_SURROUND_DAC;
	पूर्ण
	अगर (ac97->spec.ad18xx.id[2]) अणु
		ac97->flags |= AC97_AD_MULTI;
		ac97->scaps |= AC97_SCAP_CENTER_LFE_DAC;
	पूर्ण

      __end:
	/* select all codecs */
	snd_ac97_update_bits(ac97, AC97_AD_SERIAL_CFG, 0x7000, 0x7000);
	/* check अगर only one codec is present */
	क्रम (idx = num = 0; idx < 3; idx++)
		अगर (ac97->spec.ad18xx.id[idx])
			num++;
	अगर (num == 1) अणु
		/* ok, deselect all ID bits */
		snd_ac97_ग_लिखो_cache(ac97, AC97_AD_CODEC_CFG, 0x0000);
		ac97->spec.ad18xx.codec_cfg[0] = 
			ac97->spec.ad18xx.codec_cfg[1] = 
			ac97->spec.ad18xx.codec_cfg[2] = 0x0000;
	पूर्ण
	/* required क्रम AD1886/AD1885 combination */
	ac97->ext_id = snd_ac97_पढ़ो(ac97, AC97_EXTENDED_ID);
	अगर (ac97->spec.ad18xx.id[0]) अणु
		ac97->id &= 0xffff0000;
		ac97->id |= ac97->spec.ad18xx.id[0];
	पूर्ण
	ac97->build_ops = &patch_ad1881_build_ops;
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा snd_kcontrol_new snd_ac97_controls_ad1885[] = अणु
	AC97_SINGLE("Digital Mono Direct", AC97_AD_MISC, 11, 1, 0),
	/* AC97_SINGLE("Digital Audio Mode", AC97_AD_MISC, 12, 1, 0), */ /* seems problematic */
	AC97_SINGLE("Low Power Mixer", AC97_AD_MISC, 14, 1, 0),
	AC97_SINGLE("Zero Fill DAC", AC97_AD_MISC, 15, 1, 0),
	AC97_SINGLE("Headphone Jack Sense", AC97_AD_JACK_SPDIF, 9, 1, 1), /* inverted */
	AC97_SINGLE("Line Jack Sense", AC97_AD_JACK_SPDIF, 8, 1, 1), /* inverted */
पूर्ण;

अटल स्थिर DECLARE_TLV_DB_SCALE(db_scale_6bit_6db_max, -8850, 150, 0);

अटल पूर्णांक patch_ad1885_specअगरic(काष्ठा snd_ac97 * ac97)
अणु
	पूर्णांक err;

	अगर ((err = patch_build_controls(ac97, snd_ac97_controls_ad1885, ARRAY_SIZE(snd_ac97_controls_ad1885))) < 0)
		वापस err;
	reset_tlv(ac97, "Headphone Playback Volume",
		  db_scale_6bit_6db_max);
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा snd_ac97_build_ops patch_ad1885_build_ops = अणु
	.build_specअगरic = &patch_ad1885_specअगरic,
#अगर_घोषित CONFIG_PM
	.resume = ad18xx_resume
#पूर्ण_अगर
पूर्ण;

अटल पूर्णांक patch_ad1885(काष्ठा snd_ac97 * ac97)
अणु
	patch_ad1881(ac97);
	/* This is required to deal with the Intel D815EEAL2 */
	/* i.e. Line out is actually headphone out from codec */

	/* set शेष */
	snd_ac97_ग_लिखो_cache(ac97, AC97_AD_MISC, 0x0404);

	ac97->build_ops = &patch_ad1885_build_ops;
	वापस 0;
पूर्ण

अटल पूर्णांक patch_ad1886_specअगरic(काष्ठा snd_ac97 * ac97)
अणु
	reset_tlv(ac97, "Headphone Playback Volume",
		  db_scale_6bit_6db_max);
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा snd_ac97_build_ops patch_ad1886_build_ops = अणु
	.build_specअगरic = &patch_ad1886_specअगरic,
#अगर_घोषित CONFIG_PM
	.resume = ad18xx_resume
#पूर्ण_अगर
पूर्ण;

अटल पूर्णांक patch_ad1886(काष्ठा snd_ac97 * ac97)
अणु
	patch_ad1881(ac97);
	/* Presario700 workaround */
	/* क्रम Jack Sense/SPDIF Register misetting causing */
	snd_ac97_ग_लिखो_cache(ac97, AC97_AD_JACK_SPDIF, 0x0010);
	ac97->build_ops = &patch_ad1886_build_ops;
	वापस 0;
पूर्ण

/* MISC bits (AD1888/AD1980/AD1985 रेजिस्टर 0x76) */
#घोषणा AC97_AD198X_MBC		0x0003	/* mic boost */
#घोषणा AC97_AD198X_MBC_20	0x0000	/* +20dB */
#घोषणा AC97_AD198X_MBC_10	0x0001	/* +10dB */
#घोषणा AC97_AD198X_MBC_30	0x0002	/* +30dB */
#घोषणा AC97_AD198X_VREFD	0x0004	/* VREF high-Z */
#घोषणा AC97_AD198X_VREFH	0x0008	/* 0=2.25V, 1=3.7V */
#घोषणा AC97_AD198X_VREF_0	0x000c	/* 0V (AD1985 only) */
#घोषणा AC97_AD198X_VREF_MASK	(AC97_AD198X_VREFH | AC97_AD198X_VREFD)
#घोषणा AC97_AD198X_VREF_SHIFT	2
#घोषणा AC97_AD198X_SRU		0x0010	/* sample rate unlock */
#घोषणा AC97_AD198X_LOSEL	0x0020	/* LINE_OUT amplअगरiers input select */
#घोषणा AC97_AD198X_2MIC	0x0040	/* 2-channel mic select */
#घोषणा AC97_AD198X_SPRD	0x0080	/* SPREAD enable */
#घोषणा AC97_AD198X_DMIX0	0x0100	/* करोwnmix mode: */
					/*  0 = 6-to-4, 1 = 6-to-2 करोwnmix */
#घोषणा AC97_AD198X_DMIX1	0x0200	/* करोwnmix mode: 1 = enabled */
#घोषणा AC97_AD198X_HPSEL	0x0400	/* headphone amplअगरier input select */
#घोषणा AC97_AD198X_CLDIS	0x0800	/* center/lfe disable */
#घोषणा AC97_AD198X_LODIS	0x1000	/* LINE_OUT disable */
#घोषणा AC97_AD198X_MSPLT	0x2000	/* mute split */
#घोषणा AC97_AD198X_AC97NC	0x4000	/* AC97 no compatible mode */
#घोषणा AC97_AD198X_DACZ	0x8000	/* DAC zero-fill mode */

/* MISC 1 bits (AD1986 रेजिस्टर 0x76) */
#घोषणा AC97_AD1986_MBC		0x0003	/* mic boost */
#घोषणा AC97_AD1986_MBC_20	0x0000	/* +20dB */
#घोषणा AC97_AD1986_MBC_10	0x0001	/* +10dB */
#घोषणा AC97_AD1986_MBC_30	0x0002	/* +30dB */
#घोषणा AC97_AD1986_LISEL0	0x0004	/* LINE_IN select bit 0 */
#घोषणा AC97_AD1986_LISEL1	0x0008	/* LINE_IN select bit 1 */
#घोषणा AC97_AD1986_LISEL_MASK	(AC97_AD1986_LISEL1 | AC97_AD1986_LISEL0)
#घोषणा AC97_AD1986_LISEL_LI	0x0000  /* LINE_IN pins as LINE_IN source */
#घोषणा AC97_AD1986_LISEL_SURR	0x0004  /* SURROUND pins as LINE_IN source */
#घोषणा AC97_AD1986_LISEL_MIC	0x0008  /* MIC_1/2 pins as LINE_IN source */
#घोषणा AC97_AD1986_SRU		0x0010	/* sample rate unlock */
#घोषणा AC97_AD1986_SOSEL	0x0020	/* SURROUND_OUT amplअगरiers input sel */
#घोषणा AC97_AD1986_2MIC	0x0040	/* 2-channel mic select */
#घोषणा AC97_AD1986_SPRD	0x0080	/* SPREAD enable */
#घोषणा AC97_AD1986_DMIX0	0x0100	/* करोwnmix mode: */
					/*  0 = 6-to-4, 1 = 6-to-2 करोwnmix */
#घोषणा AC97_AD1986_DMIX1	0x0200	/* करोwnmix mode: 1 = enabled */
#घोषणा AC97_AD1986_CLDIS	0x0800	/* center/lfe disable */
#घोषणा AC97_AD1986_SODIS	0x1000	/* SURROUND_OUT disable */
#घोषणा AC97_AD1986_MSPLT	0x2000	/* mute split (पढ़ो only 1) */
#घोषणा AC97_AD1986_AC97NC	0x4000	/* AC97 no compatible mode (r/o 1) */
#घोषणा AC97_AD1986_DACZ	0x8000	/* DAC zero-fill mode */

/* MISC 2 bits (AD1986 रेजिस्टर 0x70) */
#घोषणा AC97_AD_MISC2		0x70	/* Misc Control Bits 2 (AD1986) */

#घोषणा AC97_AD1986_CVREF0	0x0004	/* C/LFE VREF_OUT 2.25V */
#घोषणा AC97_AD1986_CVREF1	0x0008	/* C/LFE VREF_OUT 0V */
#घोषणा AC97_AD1986_CVREF2	0x0010	/* C/LFE VREF_OUT 3.7V */
#घोषणा AC97_AD1986_CVREF_MASK \
	(AC97_AD1986_CVREF2 | AC97_AD1986_CVREF1 | AC97_AD1986_CVREF0)
#घोषणा AC97_AD1986_JSMAP	0x0020	/* Jack Sense Mapping 1 = alternate */
#घोषणा AC97_AD1986_MMDIS	0x0080	/* Mono Mute Disable */
#घोषणा AC97_AD1986_MVREF0	0x0400	/* MIC VREF_OUT 2.25V */
#घोषणा AC97_AD1986_MVREF1	0x0800	/* MIC VREF_OUT 0V */
#घोषणा AC97_AD1986_MVREF2	0x1000	/* MIC VREF_OUT 3.7V */
#घोषणा AC97_AD1986_MVREF_MASK \
	(AC97_AD1986_MVREF2 | AC97_AD1986_MVREF1 | AC97_AD1986_MVREF0)

/* MISC 3 bits (AD1986 रेजिस्टर 0x7a) */
#घोषणा AC97_AD_MISC3		0x7a	/* Misc Control Bits 3 (AD1986) */

#घोषणा AC97_AD1986_MMIX	0x0004	/* Mic Mix, left/right */
#घोषणा AC97_AD1986_GPO		0x0008	/* General Purpose Out */
#घोषणा AC97_AD1986_LOHPEN	0x0010	/* LINE_OUT headphone drive */
#घोषणा AC97_AD1986_LVREF0	0x0100	/* LINE_OUT VREF_OUT 2.25V */
#घोषणा AC97_AD1986_LVREF1	0x0200	/* LINE_OUT VREF_OUT 0V */
#घोषणा AC97_AD1986_LVREF2	0x0400	/* LINE_OUT VREF_OUT 3.7V */
#घोषणा AC97_AD1986_LVREF_MASK \
	(AC97_AD1986_LVREF2 | AC97_AD1986_LVREF1 | AC97_AD1986_LVREF0)
#घोषणा AC97_AD1986_JSINVA	0x0800	/* Jack Sense Invert SENSE_A */
#घोषणा AC97_AD1986_LOSEL	0x1000	/* LINE_OUT amplअगरiers input select */
#घोषणा AC97_AD1986_HPSEL0	0x2000	/* Headphone amplअगरiers */
					/*   input select Surround DACs */
#घोषणा AC97_AD1986_HPSEL1	0x4000	/* Headphone amplअगरiers input */
					/*   select C/LFE DACs */
#घोषणा AC97_AD1986_JSINVB	0x8000	/* Jack Sense Invert SENSE_B */

/* Serial Config bits (AD1986 रेजिस्टर 0x74) (incomplete) */
#घोषणा AC97_AD1986_OMS0	0x0100	/* Optional Mic Selector bit 0 */
#घोषणा AC97_AD1986_OMS1	0x0200	/* Optional Mic Selector bit 1 */
#घोषणा AC97_AD1986_OMS2	0x0400	/* Optional Mic Selector bit 2 */
#घोषणा AC97_AD1986_OMS_MASK \
	(AC97_AD1986_OMS2 | AC97_AD1986_OMS1 | AC97_AD1986_OMS0)
#घोषणा AC97_AD1986_OMS_M	0x0000  /* MIC_1/2 pins are MIC sources */
#घोषणा AC97_AD1986_OMS_L	0x0100  /* LINE_IN pins are MIC sources */
#घोषणा AC97_AD1986_OMS_C	0x0200  /* Center/LFE pins are MCI sources */
#घोषणा AC97_AD1986_OMS_MC	0x0400  /* Mix of MIC and C/LFE pins */
					/*   are MIC sources */
#घोषणा AC97_AD1986_OMS_ML	0x0500  /* MIX of MIC and LINE_IN pins */
					/*   are MIC sources */
#घोषणा AC97_AD1986_OMS_LC	0x0600  /* MIX of LINE_IN and C/LFE pins */
					/*   are MIC sources */
#घोषणा AC97_AD1986_OMS_MLC	0x0700  /* MIX of MIC, LINE_IN, C/LFE pins */
					/*   are MIC sources */


अटल पूर्णांक snd_ac97_ad198x_spdअगर_source_info(काष्ठा snd_kcontrol *kcontrol, काष्ठा snd_ctl_elem_info *uinfo)
अणु
	अटल स्थिर अक्षर * स्थिर texts[2] = अणु "AC-Link", "A/D Converter" पूर्ण;

	वापस snd_ctl_क्रमागत_info(uinfo, 1, 2, texts);
पूर्ण

अटल पूर्णांक snd_ac97_ad198x_spdअगर_source_get(काष्ठा snd_kcontrol *kcontrol, काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_ac97 *ac97 = snd_kcontrol_chip(kcontrol);
	अचिन्हित लघु val;

	val = ac97->regs[AC97_AD_SERIAL_CFG];
	ucontrol->value.क्रमागतerated.item[0] = (val >> 2) & 1;
	वापस 0;
पूर्ण

अटल पूर्णांक snd_ac97_ad198x_spdअगर_source_put(काष्ठा snd_kcontrol *kcontrol, काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_ac97 *ac97 = snd_kcontrol_chip(kcontrol);
	अचिन्हित लघु val;

	अगर (ucontrol->value.क्रमागतerated.item[0] > 1)
		वापस -EINVAL;
	val = ucontrol->value.क्रमागतerated.item[0] << 2;
	वापस snd_ac97_update_bits(ac97, AC97_AD_SERIAL_CFG, 0x0004, val);
पूर्ण

अटल स्थिर काष्ठा snd_kcontrol_new snd_ac97_ad198x_spdअगर_source = अणु
	.अगरace	= SNDRV_CTL_ELEM_IFACE_MIXER,
	.name	= SNDRV_CTL_NAME_IEC958("",PLAYBACK,NONE) "Source",
	.info	= snd_ac97_ad198x_spdअगर_source_info,
	.get	= snd_ac97_ad198x_spdअगर_source_get,
	.put	= snd_ac97_ad198x_spdअगर_source_put,
पूर्ण;

अटल पूर्णांक patch_ad198x_post_spdअगर(काष्ठा snd_ac97 * ac97)
अणु
 	वापस patch_build_controls(ac97, &snd_ac97_ad198x_spdअगर_source, 1);
पूर्ण

अटल स्थिर काष्ठा snd_kcontrol_new snd_ac97_ad1981x_jack_sense[] = अणु
	AC97_SINGLE("Headphone Jack Sense", AC97_AD_JACK_SPDIF, 11, 1, 0),
	AC97_SINGLE("Line Jack Sense", AC97_AD_JACK_SPDIF, 12, 1, 0),
पूर्ण;

/* deny list to aव्योम HP/Line jack-sense controls
 * (SS venकरोr << 16 | device)
 */
अटल स्थिर अचिन्हित पूर्णांक ad1981_jacks_denylist[] = अणु
	0x10140523, /* Thinkpad R40 */
	0x10140534, /* Thinkpad X31 */
	0x10140537, /* Thinkpad T41p */
	0x1014053e, /* Thinkpad R40e */
	0x10140554, /* Thinkpad T42p/R50p */
	0x10140567, /* Thinkpad T43p 2668-G7U */
	0x10140581, /* Thinkpad X41-2527 */
	0x10280160, /* Dell Dimension 2400 */
	0x104380b0, /* Asus A7V8X-MX */
	0x11790241, /* Toshiba Satellite A-15 S127 */
	0x1179ff10, /* Toshiba P500 */
	0x144dc01a, /* Samsung NP-X20C004/SEG */
	0 /* end */
पूर्ण;

अटल पूर्णांक check_list(काष्ठा snd_ac97 *ac97, स्थिर अचिन्हित पूर्णांक *list)
अणु
	u32 subid = ((u32)ac97->subप्रणाली_venकरोr << 16) | ac97->subप्रणाली_device;
	क्रम (; *list; list++)
		अगर (*list == subid)
			वापस 1;
	वापस 0;
पूर्ण

अटल पूर्णांक patch_ad1981a_specअगरic(काष्ठा snd_ac97 * ac97)
अणु
	अगर (check_list(ac97, ad1981_jacks_denylist))
		वापस 0;
	वापस patch_build_controls(ac97, snd_ac97_ad1981x_jack_sense,
				    ARRAY_SIZE(snd_ac97_ad1981x_jack_sense));
पूर्ण

अटल स्थिर काष्ठा snd_ac97_build_ops patch_ad1981a_build_ops = अणु
	.build_post_spdअगर = patch_ad198x_post_spdअगर,
	.build_specअगरic = patch_ad1981a_specअगरic,
#अगर_घोषित CONFIG_PM
	.resume = ad18xx_resume
#पूर्ण_अगर
पूर्ण;

/* allow list to enable HP jack-sense bits
 * (SS venकरोr << 16 | device)
 */
अटल स्थिर अचिन्हित पूर्णांक ad1981_jacks_allowlist[] = अणु
	0x0e11005a, /* HP nc4000/4010 */
	0x103c0890, /* HP nc6000 */
	0x103c0938, /* HP nc4220 */
	0x103c099c, /* HP nx6110 */
	0x103c0944, /* HP nc6220 */
	0x103c0934, /* HP nc8220 */
	0x103c006d, /* HP nx9105 */
	0x103c300d, /* HP Compaq dc5100 SFF(PT003AW) */
	0x17340088, /* FSC Scenic-W */
	0 /* end */
पूर्ण;

अटल व्योम check_ad1981_hp_jack_sense(काष्ठा snd_ac97 *ac97)
अणु
	अगर (check_list(ac97, ad1981_jacks_allowlist))
		/* enable headphone jack sense */
		snd_ac97_update_bits(ac97, AC97_AD_JACK_SPDIF, 1<<11, 1<<11);
पूर्ण

अटल पूर्णांक patch_ad1981a(काष्ठा snd_ac97 *ac97)
अणु
	patch_ad1881(ac97);
	ac97->build_ops = &patch_ad1981a_build_ops;
	snd_ac97_update_bits(ac97, AC97_AD_MISC, AC97_AD198X_MSPLT, AC97_AD198X_MSPLT);
	ac97->flags |= AC97_STEREO_MUTES;
	check_ad1981_hp_jack_sense(ac97);
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा snd_kcontrol_new snd_ac97_ad198x_2cmic =
AC97_SINGLE("Stereo Mic", AC97_AD_MISC, 6, 1, 0);

अटल पूर्णांक patch_ad1981b_specअगरic(काष्ठा snd_ac97 *ac97)
अणु
	पूर्णांक err;

	अगर ((err = patch_build_controls(ac97, &snd_ac97_ad198x_2cmic, 1)) < 0)
		वापस err;
	अगर (check_list(ac97, ad1981_jacks_denylist))
		वापस 0;
	वापस patch_build_controls(ac97, snd_ac97_ad1981x_jack_sense,
				    ARRAY_SIZE(snd_ac97_ad1981x_jack_sense));
पूर्ण

अटल स्थिर काष्ठा snd_ac97_build_ops patch_ad1981b_build_ops = अणु
	.build_post_spdअगर = patch_ad198x_post_spdअगर,
	.build_specअगरic = patch_ad1981b_specअगरic,
#अगर_घोषित CONFIG_PM
	.resume = ad18xx_resume
#पूर्ण_अगर
पूर्ण;

अटल पूर्णांक patch_ad1981b(काष्ठा snd_ac97 *ac97)
अणु
	patch_ad1881(ac97);
	ac97->build_ops = &patch_ad1981b_build_ops;
	snd_ac97_update_bits(ac97, AC97_AD_MISC, AC97_AD198X_MSPLT, AC97_AD198X_MSPLT);
	ac97->flags |= AC97_STEREO_MUTES;
	check_ad1981_hp_jack_sense(ac97);
	वापस 0;
पूर्ण

#घोषणा snd_ac97_ad1888_lohpsel_info	snd_ctl_boolean_mono_info

अटल पूर्णांक snd_ac97_ad1888_lohpsel_get(काष्ठा snd_kcontrol *kcontrol, काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_ac97 *ac97 = snd_kcontrol_chip(kcontrol);
	अचिन्हित लघु val;

	val = ac97->regs[AC97_AD_MISC];
	ucontrol->value.पूर्णांकeger.value[0] = !(val & AC97_AD198X_LOSEL);
	अगर (ac97->spec.ad18xx.lo_as_master)
		ucontrol->value.पूर्णांकeger.value[0] =
			!ucontrol->value.पूर्णांकeger.value[0];
	वापस 0;
पूर्ण

अटल पूर्णांक snd_ac97_ad1888_lohpsel_put(काष्ठा snd_kcontrol *kcontrol, काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_ac97 *ac97 = snd_kcontrol_chip(kcontrol);
	अचिन्हित लघु val;

	val = !ucontrol->value.पूर्णांकeger.value[0];
	अगर (ac97->spec.ad18xx.lo_as_master)
		val = !val;
	val = val ? (AC97_AD198X_LOSEL | AC97_AD198X_HPSEL) : 0;
	वापस snd_ac97_update_bits(ac97, AC97_AD_MISC,
				    AC97_AD198X_LOSEL | AC97_AD198X_HPSEL, val);
पूर्ण

अटल पूर्णांक snd_ac97_ad1888_करोwnmix_info(काष्ठा snd_kcontrol *kcontrol, काष्ठा snd_ctl_elem_info *uinfo)
अणु
	अटल स्थिर अक्षर * स्थिर texts[3] = अणु"Off", "6 -> 4", "6 -> 2"पूर्ण;

	वापस snd_ctl_क्रमागत_info(uinfo, 1, 3, texts);
पूर्ण

अटल पूर्णांक snd_ac97_ad1888_करोwnmix_get(काष्ठा snd_kcontrol *kcontrol, काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_ac97 *ac97 = snd_kcontrol_chip(kcontrol);
	अचिन्हित लघु val;

	val = ac97->regs[AC97_AD_MISC];
	अगर (!(val & AC97_AD198X_DMIX1))
		ucontrol->value.क्रमागतerated.item[0] = 0;
	अन्यथा
		ucontrol->value.क्रमागतerated.item[0] = 1 + ((val >> 8) & 1);
	वापस 0;
पूर्ण

अटल पूर्णांक snd_ac97_ad1888_करोwnmix_put(काष्ठा snd_kcontrol *kcontrol, काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_ac97 *ac97 = snd_kcontrol_chip(kcontrol);
	अचिन्हित लघु val;

	अगर (ucontrol->value.क्रमागतerated.item[0] > 2)
		वापस -EINVAL;
	अगर (ucontrol->value.क्रमागतerated.item[0] == 0)
		val = 0;
	अन्यथा
		val = AC97_AD198X_DMIX1 |
			((ucontrol->value.क्रमागतerated.item[0] - 1) << 8);
	वापस snd_ac97_update_bits(ac97, AC97_AD_MISC,
				    AC97_AD198X_DMIX0 | AC97_AD198X_DMIX1, val);
पूर्ण

अटल व्योम ad1888_update_jacks(काष्ठा snd_ac97 *ac97)
अणु
	अचिन्हित लघु val = 0;
	/* clear LODIS अगर shared jack is to be used क्रम Surround out */
	अगर (!ac97->spec.ad18xx.lo_as_master && is_shared_linein(ac97))
		val |= (1 << 12);
	/* clear CLDIS अगर shared jack is to be used क्रम C/LFE out */
	अगर (is_shared_micin(ac97))
		val |= (1 << 11);
	/* shared Line-In */
	snd_ac97_update_bits(ac97, AC97_AD_MISC, (1 << 11) | (1 << 12), val);
पूर्ण

अटल स्थिर काष्ठा snd_kcontrol_new snd_ac97_ad1888_controls[] = अणु
	अणु
		.अगरace = SNDRV_CTL_ELEM_IFACE_MIXER,
		.name = "Exchange Front/Surround",
		.info = snd_ac97_ad1888_lohpsel_info,
		.get = snd_ac97_ad1888_lohpsel_get,
		.put = snd_ac97_ad1888_lohpsel_put
	पूर्ण,
	AC97_SINGLE("V_REFOUT Enable", AC97_AD_MISC, AC97_AD_VREFD_SHIFT, 1, 1),
	AC97_SINGLE("High Pass Filter Enable", AC97_AD_TEST2,
			AC97_AD_HPFD_SHIFT, 1, 1),
	AC97_SINGLE("Spread Front to Surround and Center/LFE", AC97_AD_MISC, 7, 1, 0),
	अणु
		.अगरace = SNDRV_CTL_ELEM_IFACE_MIXER,
		.name = "Downmix",
		.info = snd_ac97_ad1888_करोwnmix_info,
		.get = snd_ac97_ad1888_करोwnmix_get,
		.put = snd_ac97_ad1888_करोwnmix_put
	पूर्ण,
	AC97_SURROUND_JACK_MODE_CTL,
	AC97_CHANNEL_MODE_CTL,

	AC97_SINGLE("Headphone Jack Sense", AC97_AD_JACK_SPDIF, 10, 1, 0),
	AC97_SINGLE("Line Jack Sense", AC97_AD_JACK_SPDIF, 12, 1, 0),
पूर्ण;

अटल पूर्णांक patch_ad1888_specअगरic(काष्ठा snd_ac97 *ac97)
अणु
	अगर (!ac97->spec.ad18xx.lo_as_master) अणु
		/* नाम 0x04 as "Master" and 0x02 as "Master Surround" */
		snd_ac97_नाम_vol_ctl(ac97, "Master Playback",
					"Master Surround Playback");
		snd_ac97_नाम_vol_ctl(ac97, "Headphone Playback",
					"Master Playback");
	पूर्ण
	वापस patch_build_controls(ac97, snd_ac97_ad1888_controls, ARRAY_SIZE(snd_ac97_ad1888_controls));
पूर्ण

अटल स्थिर काष्ठा snd_ac97_build_ops patch_ad1888_build_ops = अणु
	.build_post_spdअगर = patch_ad198x_post_spdअगर,
	.build_specअगरic = patch_ad1888_specअगरic,
#अगर_घोषित CONFIG_PM
	.resume = ad1888_resume,
#पूर्ण_अगर
	.update_jacks = ad1888_update_jacks,
पूर्ण;

अटल पूर्णांक patch_ad1888(काष्ठा snd_ac97 * ac97)
अणु
	अचिन्हित लघु misc;
	
	patch_ad1881(ac97);
	ac97->build_ops = &patch_ad1888_build_ops;

	/*
	 * LO can be used as a real line-out on some devices,
	 * and we need to revert the front/surround mixer चयनes
	 */
	अगर (ac97->subप्रणाली_venकरोr == 0x1043 &&
	    ac97->subप्रणाली_device == 0x1193) /* ASUS A9T laptop */
		ac97->spec.ad18xx.lo_as_master = 1;

	misc = snd_ac97_पढ़ो(ac97, AC97_AD_MISC);
	/* AD-compatible mode */
	/* Stereo mutes enabled */
	misc |= AC97_AD198X_MSPLT | AC97_AD198X_AC97NC;
	अगर (!ac97->spec.ad18xx.lo_as_master)
		/* Switch FRONT/SURROUND LINE-OUT/HP-OUT शेष connection */
		/* it seems that most venकरोrs connect line-out connector to
		 * headphone out of AC'97
		 */
		misc |= AC97_AD198X_LOSEL | AC97_AD198X_HPSEL;

	snd_ac97_ग_लिखो_cache(ac97, AC97_AD_MISC, misc);
	ac97->flags |= AC97_STEREO_MUTES;
	वापस 0;
पूर्ण

अटल पूर्णांक patch_ad1980_specअगरic(काष्ठा snd_ac97 *ac97)
अणु
	पूर्णांक err;

	अगर ((err = patch_ad1888_specअगरic(ac97)) < 0)
		वापस err;
	वापस patch_build_controls(ac97, &snd_ac97_ad198x_2cmic, 1);
पूर्ण

अटल स्थिर काष्ठा snd_ac97_build_ops patch_ad1980_build_ops = अणु
	.build_post_spdअगर = patch_ad198x_post_spdअगर,
	.build_specअगरic = patch_ad1980_specअगरic,
#अगर_घोषित CONFIG_PM
	.resume = ad18xx_resume,
#पूर्ण_अगर
	.update_jacks = ad1888_update_jacks,
पूर्ण;

अटल पूर्णांक patch_ad1980(काष्ठा snd_ac97 * ac97)
अणु
	patch_ad1888(ac97);
	ac97->build_ops = &patch_ad1980_build_ops;
	वापस 0;
पूर्ण

अटल पूर्णांक snd_ac97_ad1985_vrefout_info(काष्ठा snd_kcontrol *kcontrol,
					काष्ठा snd_ctl_elem_info *uinfo)
अणु
	अटल स्थिर अक्षर * स्थिर texts[4] = अणु
		"High-Z", "3.7 V", "2.25 V", "0 V"
	पूर्ण;

	वापस snd_ctl_क्रमागत_info(uinfo, 1, 4, texts);
पूर्ण

अटल पूर्णांक snd_ac97_ad1985_vrefout_get(काष्ठा snd_kcontrol *kcontrol,
				       काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	अटल स्थिर पूर्णांक reg2ctrl[4] = अणु2, 0, 1, 3पूर्ण;
	काष्ठा snd_ac97 *ac97 = snd_kcontrol_chip(kcontrol);
	अचिन्हित लघु val;
	val = (ac97->regs[AC97_AD_MISC] & AC97_AD198X_VREF_MASK)
	      >> AC97_AD198X_VREF_SHIFT;
	ucontrol->value.क्रमागतerated.item[0] = reg2ctrl[val];
	वापस 0;
पूर्ण

अटल पूर्णांक snd_ac97_ad1985_vrefout_put(काष्ठा snd_kcontrol *kcontrol, 
				       काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	अटल स्थिर पूर्णांक ctrl2reg[4] = अणु1, 2, 0, 3पूर्ण;
	काष्ठा snd_ac97 *ac97 = snd_kcontrol_chip(kcontrol);
	अचिन्हित लघु val;

	अगर (ucontrol->value.क्रमागतerated.item[0] > 3)
		वापस -EINVAL;
	val = ctrl2reg[ucontrol->value.क्रमागतerated.item[0]]
	      << AC97_AD198X_VREF_SHIFT;
	वापस snd_ac97_update_bits(ac97, AC97_AD_MISC,
				    AC97_AD198X_VREF_MASK, val);
पूर्ण

अटल स्थिर काष्ठा snd_kcontrol_new snd_ac97_ad1985_controls[] = अणु
	AC97_SINGLE("Exchange Center/LFE", AC97_AD_SERIAL_CFG, 3, 1, 0),
	अणु
		.अगरace = SNDRV_CTL_ELEM_IFACE_MIXER,
		.name = "Exchange Front/Surround",
		.info = snd_ac97_ad1888_lohpsel_info,
		.get = snd_ac97_ad1888_lohpsel_get,
		.put = snd_ac97_ad1888_lohpsel_put
	पूर्ण,
	AC97_SINGLE("High Pass Filter Enable", AC97_AD_TEST2, 12, 1, 1),
	AC97_SINGLE("Spread Front to Surround and Center/LFE",
		    AC97_AD_MISC, 7, 1, 0),
	अणु
		.अगरace = SNDRV_CTL_ELEM_IFACE_MIXER,
		.name = "Downmix",
		.info = snd_ac97_ad1888_करोwnmix_info,
		.get = snd_ac97_ad1888_करोwnmix_get,
		.put = snd_ac97_ad1888_करोwnmix_put
	पूर्ण,
	अणु
		.अगरace = SNDRV_CTL_ELEM_IFACE_MIXER,
		.name = "V_REFOUT",
		.info = snd_ac97_ad1985_vrefout_info,
		.get = snd_ac97_ad1985_vrefout_get,
		.put = snd_ac97_ad1985_vrefout_put
	पूर्ण,
	AC97_SURROUND_JACK_MODE_CTL,
	AC97_CHANNEL_MODE_CTL,

	AC97_SINGLE("Headphone Jack Sense", AC97_AD_JACK_SPDIF, 10, 1, 0),
	AC97_SINGLE("Line Jack Sense", AC97_AD_JACK_SPDIF, 12, 1, 0),
पूर्ण;

अटल व्योम ad1985_update_jacks(काष्ठा snd_ac97 *ac97)
अणु
	ad1888_update_jacks(ac97);
	/* clear OMS अगर shared jack is to be used क्रम C/LFE out */
	snd_ac97_update_bits(ac97, AC97_AD_SERIAL_CFG, 1 << 9,
			     is_shared_micin(ac97) ? 1 << 9 : 0);
पूर्ण

अटल पूर्णांक patch_ad1985_specअगरic(काष्ठा snd_ac97 *ac97)
अणु
	पूर्णांक err;

	/* नाम 0x04 as "Master" and 0x02 as "Master Surround" */
	snd_ac97_नाम_vol_ctl(ac97, "Master Playback",
				"Master Surround Playback");
	snd_ac97_नाम_vol_ctl(ac97, "Headphone Playback", "Master Playback");

	अगर ((err = patch_build_controls(ac97, &snd_ac97_ad198x_2cmic, 1)) < 0)
		वापस err;

	वापस patch_build_controls(ac97, snd_ac97_ad1985_controls,
				    ARRAY_SIZE(snd_ac97_ad1985_controls));
पूर्ण

अटल स्थिर काष्ठा snd_ac97_build_ops patch_ad1985_build_ops = अणु
	.build_post_spdअगर = patch_ad198x_post_spdअगर,
	.build_specअगरic = patch_ad1985_specअगरic,
#अगर_घोषित CONFIG_PM
	.resume = ad18xx_resume,
#पूर्ण_अगर
	.update_jacks = ad1985_update_jacks,
पूर्ण;

अटल पूर्णांक patch_ad1985(काष्ठा snd_ac97 * ac97)
अणु
	अचिन्हित लघु misc;
	
	patch_ad1881(ac97);
	ac97->build_ops = &patch_ad1985_build_ops;
	misc = snd_ac97_पढ़ो(ac97, AC97_AD_MISC);
	/* चयन front/surround line-out/hp-out */
	/* AD-compatible mode */
	/* Stereo mutes enabled */
	snd_ac97_ग_लिखो_cache(ac97, AC97_AD_MISC, misc |
			     AC97_AD198X_LOSEL |
			     AC97_AD198X_HPSEL |
			     AC97_AD198X_MSPLT |
			     AC97_AD198X_AC97NC);
	ac97->flags |= AC97_STEREO_MUTES;

	/* update current jack configuration */
	ad1985_update_jacks(ac97);

	/* on AD1985 rev. 3, AC'97 revision bits are zero */
	ac97->ext_id = (ac97->ext_id & ~AC97_EI_REV_MASK) | AC97_EI_REV_23;
	वापस 0;
पूर्ण

#घोषणा snd_ac97_ad1986_bool_info	snd_ctl_boolean_mono_info

अटल पूर्णांक snd_ac97_ad1986_lososel_get(काष्ठा snd_kcontrol *kcontrol,
				       काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_ac97 *ac97 = snd_kcontrol_chip(kcontrol);
	अचिन्हित लघु val;

	val = ac97->regs[AC97_AD_MISC3];
	ucontrol->value.पूर्णांकeger.value[0] = (val & AC97_AD1986_LOSEL) != 0;
	वापस 0;
पूर्ण

अटल पूर्णांक snd_ac97_ad1986_lososel_put(काष्ठा snd_kcontrol *kcontrol,
				       काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_ac97 *ac97 = snd_kcontrol_chip(kcontrol);
	पूर्णांक ret0;
	पूर्णांक ret1;
	पूर्णांक sprd = (ac97->regs[AC97_AD_MISC] & AC97_AD1986_SPRD) != 0;

	ret0 = snd_ac97_update_bits(ac97, AC97_AD_MISC3, AC97_AD1986_LOSEL,
					ucontrol->value.पूर्णांकeger.value[0] != 0
				    ? AC97_AD1986_LOSEL : 0);
	अगर (ret0 < 0)
		वापस ret0;

	/* SOSEL is set to values of "Spread" or "Exchange F/S" controls */
	ret1 = snd_ac97_update_bits(ac97, AC97_AD_MISC, AC97_AD1986_SOSEL,
				    (ucontrol->value.पूर्णांकeger.value[0] != 0
				     || sprd)
				    ? AC97_AD1986_SOSEL : 0);
	अगर (ret1 < 0)
		वापस ret1;

	वापस (ret0 > 0 || ret1 > 0) ? 1 : 0;
पूर्ण

अटल पूर्णांक snd_ac97_ad1986_spपढ़ो_get(काष्ठा snd_kcontrol *kcontrol,
				      काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_ac97 *ac97 = snd_kcontrol_chip(kcontrol);
	अचिन्हित लघु val;

	val = ac97->regs[AC97_AD_MISC];
	ucontrol->value.पूर्णांकeger.value[0] = (val & AC97_AD1986_SPRD) != 0;
	वापस 0;
पूर्ण

अटल पूर्णांक snd_ac97_ad1986_spपढ़ो_put(काष्ठा snd_kcontrol *kcontrol,
				      काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_ac97 *ac97 = snd_kcontrol_chip(kcontrol);
	पूर्णांक ret0;
	पूर्णांक ret1;
	पूर्णांक sprd = (ac97->regs[AC97_AD_MISC3] & AC97_AD1986_LOSEL) != 0;

	ret0 = snd_ac97_update_bits(ac97, AC97_AD_MISC, AC97_AD1986_SPRD,
					ucontrol->value.पूर्णांकeger.value[0] != 0
				    ? AC97_AD1986_SPRD : 0);
	अगर (ret0 < 0)
		वापस ret0;

	/* SOSEL is set to values of "Spread" or "Exchange F/S" controls */
	ret1 = snd_ac97_update_bits(ac97, AC97_AD_MISC, AC97_AD1986_SOSEL,
				    (ucontrol->value.पूर्णांकeger.value[0] != 0
				     || sprd)
				    ? AC97_AD1986_SOSEL : 0);
	अगर (ret1 < 0)
		वापस ret1;

	वापस (ret0 > 0 || ret1 > 0) ? 1 : 0;
पूर्ण

अटल पूर्णांक snd_ac97_ad1986_miclisel_get(काष्ठा snd_kcontrol *kcontrol,
					काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_ac97 *ac97 = snd_kcontrol_chip(kcontrol);

	ucontrol->value.पूर्णांकeger.value[0] = ac97->spec.ad18xx.swap_mic_linein;
	वापस 0;
पूर्ण

अटल पूर्णांक snd_ac97_ad1986_miclisel_put(काष्ठा snd_kcontrol *kcontrol,
					काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_ac97 *ac97 = snd_kcontrol_chip(kcontrol);
	अचिन्हित अक्षर swap = ucontrol->value.पूर्णांकeger.value[0] != 0;

	अगर (swap != ac97->spec.ad18xx.swap_mic_linein) अणु
		ac97->spec.ad18xx.swap_mic_linein = swap;
		अगर (ac97->build_ops->update_jacks)
			ac97->build_ops->update_jacks(ac97);
		वापस 1;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक snd_ac97_ad1986_vrefout_get(काष्ठा snd_kcontrol *kcontrol,
				       काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	/* Use MIC_1/2 V_REFOUT as the "get" value */
	काष्ठा snd_ac97 *ac97 = snd_kcontrol_chip(kcontrol);
	अचिन्हित लघु val;
	अचिन्हित लघु reg = ac97->regs[AC97_AD_MISC2];
	अगर ((reg & AC97_AD1986_MVREF0) != 0)
		val = 2;
	अन्यथा अगर ((reg & AC97_AD1986_MVREF1) != 0)
		val = 3;
	अन्यथा अगर ((reg & AC97_AD1986_MVREF2) != 0)
		val = 1;
	अन्यथा
		val = 0;
	ucontrol->value.क्रमागतerated.item[0] = val;
	वापस 0;
पूर्ण

अटल पूर्णांक snd_ac97_ad1986_vrefout_put(काष्ठा snd_kcontrol *kcontrol,
				       काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_ac97 *ac97 = snd_kcontrol_chip(kcontrol);
	अचिन्हित लघु cval;
	अचिन्हित लघु lval;
	अचिन्हित लघु mval;
	पूर्णांक cret;
	पूर्णांक lret;
	पूर्णांक mret;

	चयन (ucontrol->value.क्रमागतerated.item[0])
	अणु
	हाल 0: /* High-Z */
		cval = 0;
		lval = 0;
		mval = 0;
		अवरोध;
	हाल 1: /* 3.7 V */
		cval = AC97_AD1986_CVREF2;
		lval = AC97_AD1986_LVREF2;
		mval = AC97_AD1986_MVREF2;
		अवरोध;
	हाल 2: /* 2.25 V */
		cval = AC97_AD1986_CVREF0;
		lval = AC97_AD1986_LVREF0;
		mval = AC97_AD1986_MVREF0;
		अवरोध;
	हाल 3: /* 0 V */
		cval = AC97_AD1986_CVREF1;
		lval = AC97_AD1986_LVREF1;
		mval = AC97_AD1986_MVREF1;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	cret = snd_ac97_update_bits(ac97, AC97_AD_MISC2,
				    AC97_AD1986_CVREF_MASK, cval);
	अगर (cret < 0)
		वापस cret;
	lret = snd_ac97_update_bits(ac97, AC97_AD_MISC3,
				    AC97_AD1986_LVREF_MASK, lval);
	अगर (lret < 0)
		वापस lret;
	mret = snd_ac97_update_bits(ac97, AC97_AD_MISC2,
				    AC97_AD1986_MVREF_MASK, mval);
	अगर (mret < 0)
		वापस mret;

	वापस (cret > 0 || lret > 0 || mret > 0) ? 1 : 0;
पूर्ण

अटल स्थिर काष्ठा snd_kcontrol_new snd_ac97_ad1986_controls[] = अणु
	AC97_SINGLE("Exchange Center/LFE", AC97_AD_SERIAL_CFG, 3, 1, 0),
	अणु
		.अगरace = SNDRV_CTL_ELEM_IFACE_MIXER,
		.name = "Exchange Front/Surround",
		.info = snd_ac97_ad1986_bool_info,
		.get = snd_ac97_ad1986_lososel_get,
		.put = snd_ac97_ad1986_lososel_put
	पूर्ण,
	अणु
		.अगरace = SNDRV_CTL_ELEM_IFACE_MIXER,
		.name = "Exchange Mic/Line In",
		.info = snd_ac97_ad1986_bool_info,
		.get = snd_ac97_ad1986_miclisel_get,
		.put = snd_ac97_ad1986_miclisel_put
	पूर्ण,
	अणु
		.अगरace = SNDRV_CTL_ELEM_IFACE_MIXER,
		.name = "Spread Front to Surround and Center/LFE",
		.info = snd_ac97_ad1986_bool_info,
		.get = snd_ac97_ad1986_spपढ़ो_get,
		.put = snd_ac97_ad1986_spपढ़ो_put
	पूर्ण,
	अणु
		.अगरace = SNDRV_CTL_ELEM_IFACE_MIXER,
		.name = "Downmix",
		.info = snd_ac97_ad1888_करोwnmix_info,
		.get = snd_ac97_ad1888_करोwnmix_get,
		.put = snd_ac97_ad1888_करोwnmix_put
	पूर्ण,
	अणु
		.अगरace = SNDRV_CTL_ELEM_IFACE_MIXER,
		.name = "V_REFOUT",
		.info = snd_ac97_ad1985_vrefout_info,
		.get = snd_ac97_ad1986_vrefout_get,
		.put = snd_ac97_ad1986_vrefout_put
	पूर्ण,
	AC97_SURROUND_JACK_MODE_CTL,
	AC97_CHANNEL_MODE_CTL,

	AC97_SINGLE("Headphone Jack Sense", AC97_AD_JACK_SPDIF, 10, 1, 0),
	AC97_SINGLE("Line Jack Sense", AC97_AD_JACK_SPDIF, 12, 1, 0)
पूर्ण;

अटल व्योम ad1986_update_jacks(काष्ठा snd_ac97 *ac97)
अणु
	अचिन्हित लघु misc_val = 0;
	अचिन्हित लघु ser_val;

	/* disable SURROUND and CENTER/LFE अगर not surround mode */
	अगर (!is_surround_on(ac97))
		misc_val |= AC97_AD1986_SODIS;
	अगर (!is_clfe_on(ac97))
		misc_val |= AC97_AD1986_CLDIS;

	/* select line input (शेष=LINE_IN, SURROUND or MIC_1/2) */
	अगर (is_shared_linein(ac97))
		misc_val |= AC97_AD1986_LISEL_SURR;
	अन्यथा अगर (ac97->spec.ad18xx.swap_mic_linein != 0)
		misc_val |= AC97_AD1986_LISEL_MIC;
	snd_ac97_update_bits(ac97, AC97_AD_MISC,
			     AC97_AD1986_SODIS | AC97_AD1986_CLDIS |
			     AC97_AD1986_LISEL_MASK,
			     misc_val);

	/* select microphone input (MIC_1/2, Center/LFE or LINE_IN) */
	अगर (is_shared_micin(ac97))
		ser_val = AC97_AD1986_OMS_C;
	अन्यथा अगर (ac97->spec.ad18xx.swap_mic_linein != 0)
		ser_val = AC97_AD1986_OMS_L;
	अन्यथा
		ser_val = AC97_AD1986_OMS_M;
	snd_ac97_update_bits(ac97, AC97_AD_SERIAL_CFG,
			     AC97_AD1986_OMS_MASK,
			     ser_val);
पूर्ण

अटल पूर्णांक patch_ad1986_specअगरic(काष्ठा snd_ac97 *ac97)
अणु
	पूर्णांक err;

	अगर ((err = patch_build_controls(ac97, &snd_ac97_ad198x_2cmic, 1)) < 0)
		वापस err;

	वापस patch_build_controls(ac97, snd_ac97_ad1986_controls,
				    ARRAY_SIZE(snd_ac97_ad1985_controls));
पूर्ण

अटल स्थिर काष्ठा snd_ac97_build_ops patch_ad1986_build_ops = अणु
	.build_post_spdअगर = patch_ad198x_post_spdअगर,
	.build_specअगरic = patch_ad1986_specअगरic,
#अगर_घोषित CONFIG_PM
	.resume = ad18xx_resume,
#पूर्ण_अगर
	.update_jacks = ad1986_update_jacks,
पूर्ण;

अटल पूर्णांक patch_ad1986(काष्ठा snd_ac97 * ac97)
अणु
	patch_ad1881(ac97);
	ac97->build_ops = &patch_ad1986_build_ops;
	ac97->flags |= AC97_STEREO_MUTES;

	/* update current jack configuration */
	ad1986_update_jacks(ac97);

	वापस 0;
पूर्ण

/*
 * realtek ALC203: use mono-out क्रम pin 37
 */
अटल पूर्णांक patch_alc203(काष्ठा snd_ac97 *ac97)
अणु
	snd_ac97_update_bits(ac97, 0x7a, 0x400, 0x400);
	वापस 0;
पूर्ण

/*
 * realtek ALC65x/850 codecs
 */
अटल व्योम alc650_update_jacks(काष्ठा snd_ac97 *ac97)
अणु
	पूर्णांक shared;
	
	/* shared Line-In / Surround Out */
	shared = is_shared_surrout(ac97);
	snd_ac97_update_bits(ac97, AC97_ALC650_MULTICH, 1 << 9,
			     shared ? (1 << 9) : 0);
	/* update shared Mic In / Center/LFE Out */
	shared = is_shared_clfeout(ac97);
	/* disable/enable vref */
	snd_ac97_update_bits(ac97, AC97_ALC650_CLOCK, 1 << 12,
			     shared ? (1 << 12) : 0);
	/* turn on/off center-on-mic */
	snd_ac97_update_bits(ac97, AC97_ALC650_MULTICH, 1 << 10,
			     shared ? (1 << 10) : 0);
	/* GPIO0 high क्रम mic */
	snd_ac97_update_bits(ac97, AC97_ALC650_GPIO_STATUS, 0x100,
			     shared ? 0 : 0x100);
पूर्ण

अटल पूर्णांक alc650_swap_surround_put(काष्ठा snd_kcontrol *kcontrol,
				    काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_ac97 *ac97 = snd_kcontrol_chip(kcontrol);
	काष्ठा snd_pcm_chmap *map = ac97->chmaps[SNDRV_PCM_STREAM_PLAYBACK];

	अगर (map) अणु
		अगर (ucontrol->value.पूर्णांकeger.value[0])
			map->chmap = snd_pcm_std_chmaps;
		अन्यथा
			map->chmap = snd_pcm_alt_chmaps;
	पूर्ण
	वापस snd_ac97_put_volsw(kcontrol, ucontrol);
पूर्ण

अटल स्थिर काष्ठा snd_kcontrol_new snd_ac97_controls_alc650[] = अणु
	AC97_SINGLE("Duplicate Front", AC97_ALC650_MULTICH, 0, 1, 0),
	AC97_SINGLE("Surround Down Mix", AC97_ALC650_MULTICH, 1, 1, 0),
	AC97_SINGLE("Center/LFE Down Mix", AC97_ALC650_MULTICH, 2, 1, 0),
	AC97_SINGLE("Exchange Center/LFE", AC97_ALC650_MULTICH, 3, 1, 0),
	/* 4: Analog Input To Surround */
	/* 5: Analog Input To Center/LFE */
	/* 6: Independent Master Volume Right */
	/* 7: Independent Master Volume Left */
	/* 8: reserved */
	/* 9: Line-In/Surround share */
	/* 10: Mic/CLFE share */
	/* 11-13: in IEC958 controls */
	अणु
		.अगरace = SNDRV_CTL_ELEM_IFACE_MIXER,
		.name = "Swap Surround Slot",
		.info = snd_ac97_info_volsw,
		.get = snd_ac97_get_volsw,
		.put = alc650_swap_surround_put,
		.निजी_value =  AC97_SINGLE_VALUE(AC97_ALC650_MULTICH, 14, 1, 0),
	पूर्ण,
#अगर 0 /* always set in patch_alc650 */
	AC97_SINGLE("IEC958 Input Clock Enable", AC97_ALC650_CLOCK, 0, 1, 0),
	AC97_SINGLE("IEC958 Input Pin Enable", AC97_ALC650_CLOCK, 1, 1, 0),
	AC97_SINGLE("Surround DAC Switch", AC97_ALC650_SURR_DAC_VOL, 15, 1, 1),
	AC97_DOUBLE("Surround DAC Volume", AC97_ALC650_SURR_DAC_VOL, 8, 0, 31, 1),
	AC97_SINGLE("Center/LFE DAC Switch", AC97_ALC650_LFE_DAC_VOL, 15, 1, 1),
	AC97_DOUBLE("Center/LFE DAC Volume", AC97_ALC650_LFE_DAC_VOL, 8, 0, 31, 1),
#पूर्ण_अगर
	AC97_SURROUND_JACK_MODE_CTL,
	AC97_CHANNEL_MODE_CTL,
पूर्ण;

अटल स्थिर काष्ठा snd_kcontrol_new snd_ac97_spdअगर_controls_alc650[] = अणु
        AC97_SINGLE(SNDRV_CTL_NAME_IEC958("",CAPTURE,SWITCH), AC97_ALC650_MULTICH, 11, 1, 0),
        AC97_SINGLE("Analog to IEC958 Output", AC97_ALC650_MULTICH, 12, 1, 0),
	/* disable this controls since it करोesn't work as expected */
	/* AC97_SINGLE("IEC958 Input Monitor", AC97_ALC650_MULTICH, 13, 1, 0), */
पूर्ण;

अटल स्थिर DECLARE_TLV_DB_SCALE(db_scale_5bit_3db_max, -4350, 150, 0);

अटल पूर्णांक patch_alc650_specअगरic(काष्ठा snd_ac97 * ac97)
अणु
	पूर्णांक err;

	अगर ((err = patch_build_controls(ac97, snd_ac97_controls_alc650, ARRAY_SIZE(snd_ac97_controls_alc650))) < 0)
		वापस err;
	अगर (ac97->ext_id & AC97_EI_SPDIF) अणु
		अगर ((err = patch_build_controls(ac97, snd_ac97_spdअगर_controls_alc650, ARRAY_SIZE(snd_ac97_spdअगर_controls_alc650))) < 0)
			वापस err;
	पूर्ण
	अगर (ac97->id != AC97_ID_ALC650F)
		reset_tlv(ac97, "Master Playback Volume",
			  db_scale_5bit_3db_max);
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा snd_ac97_build_ops patch_alc650_ops = अणु
	.build_specअगरic	= patch_alc650_specअगरic,
	.update_jacks = alc650_update_jacks
पूर्ण;

अटल पूर्णांक patch_alc650(काष्ठा snd_ac97 * ac97)
अणु
	अचिन्हित लघु val;

	ac97->build_ops = &patch_alc650_ops;

	/* determine the revision */
	val = snd_ac97_पढ़ो(ac97, AC97_ALC650_REVISION) & 0x3f;
	अगर (val < 3)
		ac97->id = 0x414c4720;          /* Old version */
	अन्यथा अगर (val < 0x10)
		ac97->id = 0x414c4721;          /* D version */
	अन्यथा अगर (val < 0x20)
		ac97->id = 0x414c4722;          /* E version */
	अन्यथा अगर (val < 0x30)
		ac97->id = 0x414c4723;          /* F version */

	/* revision E or F */
	/* FIXME: what about revision D ? */
	ac97->spec.dev_flags = (ac97->id == 0x414c4722 ||
				ac97->id == 0x414c4723);

	/* enable AC97_ALC650_GPIO_SETUP, AC97_ALC650_CLOCK क्रम R/W */
	snd_ac97_ग_लिखो_cache(ac97, AC97_ALC650_GPIO_STATUS, 
		snd_ac97_पढ़ो(ac97, AC97_ALC650_GPIO_STATUS) | 0x8000);

	/* Enable SPDIF-IN only on Rev.E and above */
	val = snd_ac97_पढ़ो(ac97, AC97_ALC650_CLOCK);
	/* SPDIF IN with pin 47 */
	अगर (ac97->spec.dev_flags &&
	    /* ASUS A6KM requires EAPD */
	    ! (ac97->subप्रणाली_venकरोr == 0x1043 &&
	       ac97->subप्रणाली_device == 0x1103))
		val |= 0x03; /* enable */
	अन्यथा
		val &= ~0x03; /* disable */
	snd_ac97_ग_लिखो_cache(ac97, AC97_ALC650_CLOCK, val);

	/* set शेष: slot 3,4,7,8,6,9
	   spdअगर-in monitor off, analog-spdअगर off, spdअगर-in off
	   center on mic off, surround on line-in off
	   करोwnmix off, duplicate front off
	*/
	snd_ac97_ग_लिखो_cache(ac97, AC97_ALC650_MULTICH, 0);

	/* set GPIO0 क्रम mic bias */
	/* GPIO0 pin output, no पूर्णांकerrupt, high */
	snd_ac97_ग_लिखो_cache(ac97, AC97_ALC650_GPIO_SETUP,
			     snd_ac97_पढ़ो(ac97, AC97_ALC650_GPIO_SETUP) | 0x01);
	snd_ac97_ग_लिखो_cache(ac97, AC97_ALC650_GPIO_STATUS,
			     (snd_ac97_पढ़ो(ac97, AC97_ALC650_GPIO_STATUS) | 0x100) & ~0x10);

	/* full DAC volume */
	snd_ac97_ग_लिखो_cache(ac97, AC97_ALC650_SURR_DAC_VOL, 0x0808);
	snd_ac97_ग_लिखो_cache(ac97, AC97_ALC650_LFE_DAC_VOL, 0x0808);
	वापस 0;
पूर्ण

अटल व्योम alc655_update_jacks(काष्ठा snd_ac97 *ac97)
अणु
	पूर्णांक shared;
	
	/* shared Line-In / Surround Out */
	shared = is_shared_surrout(ac97);
	ac97_update_bits_page(ac97, AC97_ALC650_MULTICH, 1 << 9,
			      shared ? (1 << 9) : 0, 0);
	/* update shared Mic In / Center/LFE Out */
	shared = is_shared_clfeout(ac97);
	/* misc control; vrefout disable */
	snd_ac97_update_bits(ac97, AC97_ALC650_CLOCK, 1 << 12,
			     shared ? (1 << 12) : 0);
	ac97_update_bits_page(ac97, AC97_ALC650_MULTICH, 1 << 10,
			      shared ? (1 << 10) : 0, 0);
पूर्ण

अटल स्थिर काष्ठा snd_kcontrol_new snd_ac97_controls_alc655[] = अणु
	AC97_PAGE_SINGLE("Duplicate Front", AC97_ALC650_MULTICH, 0, 1, 0, 0),
	AC97_SURROUND_JACK_MODE_CTL,
	AC97_CHANNEL_MODE_CTL,
पूर्ण;

अटल पूर्णांक alc655_iec958_route_info(काष्ठा snd_kcontrol *kcontrol, काष्ठा snd_ctl_elem_info *uinfo)
अणु
	अटल स्थिर अक्षर * स्थिर texts_655[3] = अणु
		"PCM", "Analog In", "IEC958 In"
	पूर्ण;
	अटल स्थिर अक्षर * स्थिर texts_658[4] = अणु
		"PCM", "Analog1 In", "Analog2 In", "IEC958 In"
	पूर्ण;
	काष्ठा snd_ac97 *ac97 = snd_kcontrol_chip(kcontrol);

	अगर (ac97->spec.dev_flags)
		वापस snd_ctl_क्रमागत_info(uinfo, 1, 4, texts_658);
	अन्यथा
		वापस snd_ctl_क्रमागत_info(uinfo, 1, 3, texts_655);
पूर्ण

अटल पूर्णांक alc655_iec958_route_get(काष्ठा snd_kcontrol *kcontrol, काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_ac97 *ac97 = snd_kcontrol_chip(kcontrol);
	अचिन्हित लघु val;

	val = ac97->regs[AC97_ALC650_MULTICH];
	val = (val >> 12) & 3;
	अगर (ac97->spec.dev_flags && val == 3)
		val = 0;
	ucontrol->value.क्रमागतerated.item[0] = val;
	वापस 0;
पूर्ण

अटल पूर्णांक alc655_iec958_route_put(काष्ठा snd_kcontrol *kcontrol, काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_ac97 *ac97 = snd_kcontrol_chip(kcontrol);

	वापस ac97_update_bits_page(ac97, AC97_ALC650_MULTICH, 3 << 12,
				     (अचिन्हित लघु)ucontrol->value.क्रमागतerated.item[0] << 12,
				     0);
पूर्ण

अटल स्थिर काष्ठा snd_kcontrol_new snd_ac97_spdअगर_controls_alc655[] = अणु
        AC97_PAGE_SINGLE(SNDRV_CTL_NAME_IEC958("",CAPTURE,SWITCH), AC97_ALC650_MULTICH, 11, 1, 0, 0),
	/* disable this controls since it करोesn't work as expected */
        /* AC97_PAGE_SINGLE("IEC958 Input Monitor", AC97_ALC650_MULTICH, 14, 1, 0, 0), */
	अणु
		.अगरace  = SNDRV_CTL_ELEM_IFACE_MIXER,
		.name   = SNDRV_CTL_NAME_IEC958("",PLAYBACK,NONE) "Source",
		.info   = alc655_iec958_route_info,
		.get    = alc655_iec958_route_get,
		.put    = alc655_iec958_route_put,
	पूर्ण,
पूर्ण;

अटल पूर्णांक patch_alc655_specअगरic(काष्ठा snd_ac97 * ac97)
अणु
	पूर्णांक err;

	अगर ((err = patch_build_controls(ac97, snd_ac97_controls_alc655, ARRAY_SIZE(snd_ac97_controls_alc655))) < 0)
		वापस err;
	अगर (ac97->ext_id & AC97_EI_SPDIF) अणु
		अगर ((err = patch_build_controls(ac97, snd_ac97_spdअगर_controls_alc655, ARRAY_SIZE(snd_ac97_spdअगर_controls_alc655))) < 0)
			वापस err;
	पूर्ण
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा snd_ac97_build_ops patch_alc655_ops = अणु
	.build_specअगरic	= patch_alc655_specअगरic,
	.update_jacks = alc655_update_jacks
पूर्ण;

अटल पूर्णांक patch_alc655(काष्ठा snd_ac97 * ac97)
अणु
	अचिन्हित पूर्णांक val;

	अगर (ac97->id == AC97_ID_ALC658) अणु
		ac97->spec.dev_flags = 1; /* ALC658 */
		अगर ((snd_ac97_पढ़ो(ac97, AC97_ALC650_REVISION) & 0x3f) == 2) अणु
			ac97->id = AC97_ID_ALC658D;
			ac97->spec.dev_flags = 2;
		पूर्ण
	पूर्ण

	ac97->build_ops = &patch_alc655_ops;

	/* assume only page 0 क्रम writing cache */
	snd_ac97_update_bits(ac97, AC97_INT_PAGING, AC97_PAGE_MASK, AC97_PAGE_VENDOR);

	/* adjust शेष values */
	val = snd_ac97_पढ़ो(ac97, 0x7a); /* misc control */
	अगर (ac97->spec.dev_flags) /* ALC658 */
		val &= ~(1 << 1); /* Pin 47 is spdअगर input pin */
	अन्यथा अणु /* ALC655 */
		अगर (ac97->subप्रणाली_venकरोr == 0x1462 &&
		    (ac97->subप्रणाली_device == 0x0131 || /* MSI S270 laptop */
		     ac97->subप्रणाली_device == 0x0161 || /* LG K1 Express */
		     ac97->subप्रणाली_device == 0x0351 || /* MSI L725 laptop */
		     ac97->subप्रणाली_device == 0x0471 || /* MSI L720 laptop */
		     ac97->subप्रणाली_device == 0x0061))  /* MSI S250 laptop */
			val &= ~(1 << 1); /* Pin 47 is EAPD (क्रम पूर्णांकernal speaker) */
		अन्यथा
			val |= (1 << 1); /* Pin 47 is spdअगर input pin */
		/* this seems missing on some hardwares */
		ac97->ext_id |= AC97_EI_SPDIF;
	पूर्ण
	val &= ~(1 << 12); /* vref enable */
	snd_ac97_ग_लिखो_cache(ac97, 0x7a, val);
	/* set शेष: spdअगर-in enabled,
	   spdअगर-in monitor off, spdअगर-in PCM off
	   center on mic off, surround on line-in off
	   duplicate front off
	*/
	snd_ac97_ग_लिखो_cache(ac97, AC97_ALC650_MULTICH, 1<<15);

	/* full DAC volume */
	snd_ac97_ग_लिखो_cache(ac97, AC97_ALC650_SURR_DAC_VOL, 0x0808);
	snd_ac97_ग_लिखो_cache(ac97, AC97_ALC650_LFE_DAC_VOL, 0x0808);

	/* update unकरोcumented bit... */
	अगर (ac97->id == AC97_ID_ALC658D)
		snd_ac97_update_bits(ac97, 0x74, 0x0800, 0x0800);

	वापस 0;
पूर्ण


#घोषणा AC97_ALC850_JACK_SELECT	0x76
#घोषणा AC97_ALC850_MISC1	0x7a
#घोषणा AC97_ALC850_MULTICH    0x6a

अटल व्योम alc850_update_jacks(काष्ठा snd_ac97 *ac97)
अणु
	पूर्णांक shared;
	पूर्णांक aux_is_back_surround;
	
	/* shared Line-In / Surround Out */
	shared = is_shared_surrout(ac97);
	/* SURR 1kOhm (bit4), Amp (bit5) */
	snd_ac97_update_bits(ac97, AC97_ALC850_MISC1, (1<<4)|(1<<5),
			     shared ? (1<<5) : (1<<4));
	/* LINE-IN = 0, SURROUND = 2 */
	snd_ac97_update_bits(ac97, AC97_ALC850_JACK_SELECT, 7 << 12,
			     shared ? (2<<12) : (0<<12));
	/* update shared Mic In / Center/LFE Out */
	shared = is_shared_clfeout(ac97);
	/* Vref disable (bit12), 1kOhm (bit13) */
	snd_ac97_update_bits(ac97, AC97_ALC850_MISC1, (1<<12)|(1<<13),
			     shared ? (1<<12) : (1<<13));
	/* MIC-IN = 1, CENTER-LFE = 5 */
	snd_ac97_update_bits(ac97, AC97_ALC850_JACK_SELECT, 7 << 4,
			     shared ? (5<<4) : (1<<4));

	aux_is_back_surround = alc850_is_aux_back_surround(ac97);
	/* Aux is Back Surround */
	snd_ac97_update_bits(ac97, AC97_ALC850_MULTICH, 1 << 10,
				 aux_is_back_surround ? (1<<10) : (0<<10));
पूर्ण

अटल स्थिर काष्ठा snd_kcontrol_new snd_ac97_controls_alc850[] = अणु
	AC97_PAGE_SINGLE("Duplicate Front", AC97_ALC650_MULTICH, 0, 1, 0, 0),
	AC97_SINGLE("Mic Front Input Switch", AC97_ALC850_JACK_SELECT, 15, 1, 1),
	AC97_SURROUND_JACK_MODE_CTL,
	AC97_CHANNEL_MODE_8CH_CTL,
पूर्ण;

अटल पूर्णांक patch_alc850_specअगरic(काष्ठा snd_ac97 *ac97)
अणु
	पूर्णांक err;

	अगर ((err = patch_build_controls(ac97, snd_ac97_controls_alc850, ARRAY_SIZE(snd_ac97_controls_alc850))) < 0)
		वापस err;
	अगर (ac97->ext_id & AC97_EI_SPDIF) अणु
		अगर ((err = patch_build_controls(ac97, snd_ac97_spdअगर_controls_alc655, ARRAY_SIZE(snd_ac97_spdअगर_controls_alc655))) < 0)
			वापस err;
	पूर्ण
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा snd_ac97_build_ops patch_alc850_ops = अणु
	.build_specअगरic	= patch_alc850_specअगरic,
	.update_jacks = alc850_update_jacks
पूर्ण;

अटल पूर्णांक patch_alc850(काष्ठा snd_ac97 *ac97)
अणु
	ac97->build_ops = &patch_alc850_ops;

	ac97->spec.dev_flags = 0; /* क्रम IEC958 playback route - ALC655 compatible */
	ac97->flags |= AC97_HAS_8CH;

	/* assume only page 0 क्रम writing cache */
	snd_ac97_update_bits(ac97, AC97_INT_PAGING, AC97_PAGE_MASK, AC97_PAGE_VENDOR);

	/* adjust शेष values */
	/* set शेष: spdअगर-in enabled,
	   spdअगर-in monitor off, spdअगर-in PCM off
	   center on mic off, surround on line-in off
	   duplicate front off
	   NB शेष bit 10=0 = Aux is Capture, not Back Surround
	*/
	snd_ac97_ग_लिखो_cache(ac97, AC97_ALC650_MULTICH, 1<<15);
	/* SURR_OUT: on, Surr 1kOhm: on, Surr Amp: off, Front 1kOhm: off
	 * Front Amp: on, Vref: enable, Center 1kOhm: on, Mix: on
	 */
	snd_ac97_ग_लिखो_cache(ac97, 0x7a, (1<<1)|(1<<4)|(0<<5)|(1<<6)|
			     (1<<7)|(0<<12)|(1<<13)|(0<<14));
	/* detection UIO2,3: all path भग्नing, UIO3: MIC, Vref2: disable,
	 * UIO1: FRONT, Vref3: disable, UIO3: LINE, Front-Mic: mute
	 */
	snd_ac97_ग_लिखो_cache(ac97, 0x76, (0<<0)|(0<<2)|(1<<4)|(1<<7)|(2<<8)|
			     (1<<11)|(0<<12)|(1<<15));

	/* full DAC volume */
	snd_ac97_ग_लिखो_cache(ac97, AC97_ALC650_SURR_DAC_VOL, 0x0808);
	snd_ac97_ग_लिखो_cache(ac97, AC97_ALC650_LFE_DAC_VOL, 0x0808);
	वापस 0;
पूर्ण

अटल पूर्णांक patch_aztech_azf3328_specअगरic(काष्ठा snd_ac97 *ac97)
अणु
	काष्ठा snd_kcontrol *kctl_3d_center =
		snd_ac97_find_mixer_ctl(ac97, "3D Control - Center");
	काष्ठा snd_kcontrol *kctl_3d_depth =
		snd_ac97_find_mixer_ctl(ac97, "3D Control - Depth");

	/*
	 * 3D रेजिस्टर is dअगरferent from AC97 standard layout
	 * (also करो some renaming, to resemble Winकरोws driver naming)
	 */
	अगर (kctl_3d_center) अणु
		kctl_3d_center->निजी_value =
			AC97_SINGLE_VALUE(AC97_3D_CONTROL, 1, 0x07, 0);
		snd_ac97_नाम_vol_ctl(ac97,
			"3D Control - Center", "3D Control - Width"
		);
	पूर्ण
	अगर (kctl_3d_depth)
		kctl_3d_depth->निजी_value =
			AC97_SINGLE_VALUE(AC97_3D_CONTROL, 8, 0x03, 0);

	/* Aztech Winकरोws driver calls the
	   equivalent control "Modem Playback", thus नाम it: */
	snd_ac97_नाम_vol_ctl(ac97,
		"Master Mono Playback", "Modem Playback"
	);
	snd_ac97_नाम_vol_ctl(ac97,
		"Headphone Playback", "FM Synth Playback"
	);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा snd_ac97_build_ops patch_aztech_azf3328_ops = अणु
	.build_specअगरic	= patch_aztech_azf3328_specअगरic
पूर्ण;

अटल पूर्णांक patch_aztech_azf3328(काष्ठा snd_ac97 *ac97)
अणु
	ac97->build_ops = &patch_aztech_azf3328_ops;
	वापस 0;
पूर्ण

/*
 * C-Media CM97xx codecs
 */
अटल व्योम cm9738_update_jacks(काष्ठा snd_ac97 *ac97)
अणु
	/* shared Line-In / Surround Out */
	snd_ac97_update_bits(ac97, AC97_CM9738_VENDOR_CTRL, 1 << 10,
			     is_shared_surrout(ac97) ? (1 << 10) : 0);
पूर्ण

अटल स्थिर काष्ठा snd_kcontrol_new snd_ac97_cm9738_controls[] = अणु
	AC97_SINGLE("Duplicate Front", AC97_CM9738_VENDOR_CTRL, 13, 1, 0),
	AC97_SURROUND_JACK_MODE_CTL,
	AC97_CHANNEL_MODE_4CH_CTL,
पूर्ण;

अटल पूर्णांक patch_cm9738_specअगरic(काष्ठा snd_ac97 * ac97)
अणु
	वापस patch_build_controls(ac97, snd_ac97_cm9738_controls, ARRAY_SIZE(snd_ac97_cm9738_controls));
पूर्ण

अटल स्थिर काष्ठा snd_ac97_build_ops patch_cm9738_ops = अणु
	.build_specअगरic	= patch_cm9738_specअगरic,
	.update_jacks = cm9738_update_jacks
पूर्ण;

अटल पूर्णांक patch_cm9738(काष्ठा snd_ac97 * ac97)
अणु
	ac97->build_ops = &patch_cm9738_ops;
	/* FIXME: can anyone confirm below? */
	/* CM9738 has no PCM volume although the रेजिस्टर reacts */
	ac97->flags |= AC97_HAS_NO_PCM_VOL;
	snd_ac97_ग_लिखो_cache(ac97, AC97_PCM, 0x8000);

	वापस 0;
पूर्ण

अटल पूर्णांक snd_ac97_cmedia_spdअगर_playback_source_info(काष्ठा snd_kcontrol *kcontrol, काष्ठा snd_ctl_elem_info *uinfo)
अणु
	अटल स्थिर अक्षर * स्थिर texts[] = अणु "Analog", "Digital" पूर्ण;

	वापस snd_ctl_क्रमागत_info(uinfo, 1, 2, texts);
पूर्ण

अटल पूर्णांक snd_ac97_cmedia_spdअगर_playback_source_get(काष्ठा snd_kcontrol *kcontrol, काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_ac97 *ac97 = snd_kcontrol_chip(kcontrol);
	अचिन्हित लघु val;

	val = ac97->regs[AC97_CM9739_SPDIF_CTRL];
	ucontrol->value.क्रमागतerated.item[0] = (val >> 1) & 0x01;
	वापस 0;
पूर्ण

अटल पूर्णांक snd_ac97_cmedia_spdअगर_playback_source_put(काष्ठा snd_kcontrol *kcontrol, काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_ac97 *ac97 = snd_kcontrol_chip(kcontrol);

	वापस snd_ac97_update_bits(ac97, AC97_CM9739_SPDIF_CTRL,
				    0x01 << 1, 
				    (ucontrol->value.क्रमागतerated.item[0] & 0x01) << 1);
पूर्ण

अटल स्थिर काष्ठा snd_kcontrol_new snd_ac97_cm9739_controls_spdअगर[] = अणु
	/* BIT 0: SPDI_EN - always true */
	अणु /* BIT 1: SPDIFS */
		.अगरace	= SNDRV_CTL_ELEM_IFACE_MIXER,
		.name	= SNDRV_CTL_NAME_IEC958("",PLAYBACK,NONE) "Source",
		.info	= snd_ac97_cmedia_spdअगर_playback_source_info,
		.get	= snd_ac97_cmedia_spdअगर_playback_source_get,
		.put	= snd_ac97_cmedia_spdअगर_playback_source_put,
	पूर्ण,
	/* BIT 2: IG_SPIV */
	AC97_SINGLE(SNDRV_CTL_NAME_IEC958("",CAPTURE,NONE) "Valid Switch", AC97_CM9739_SPDIF_CTRL, 2, 1, 0),
	/* BIT 3: SPI2F */
	AC97_SINGLE(SNDRV_CTL_NAME_IEC958("",CAPTURE,NONE) "Monitor", AC97_CM9739_SPDIF_CTRL, 3, 1, 0), 
	/* BIT 4: SPI2SDI */
	AC97_SINGLE(SNDRV_CTL_NAME_IEC958("",CAPTURE,SWITCH), AC97_CM9739_SPDIF_CTRL, 4, 1, 0),
	/* BIT 8: SPD32 - 32bit SPDIF - not supported yet */
पूर्ण;

अटल व्योम cm9739_update_jacks(काष्ठा snd_ac97 *ac97)
अणु
	/* shared Line-In / Surround Out */
	snd_ac97_update_bits(ac97, AC97_CM9739_MULTI_CHAN, 1 << 10,
			     is_shared_surrout(ac97) ? (1 << 10) : 0);
	/* shared Mic In / Center/LFE Out **/
	snd_ac97_update_bits(ac97, AC97_CM9739_MULTI_CHAN, 0x3000,
			     is_shared_clfeout(ac97) ? 0x1000 : 0x2000);
पूर्ण

अटल स्थिर काष्ठा snd_kcontrol_new snd_ac97_cm9739_controls[] = अणु
	AC97_SURROUND_JACK_MODE_CTL,
	AC97_CHANNEL_MODE_CTL,
पूर्ण;

अटल पूर्णांक patch_cm9739_specअगरic(काष्ठा snd_ac97 * ac97)
अणु
	वापस patch_build_controls(ac97, snd_ac97_cm9739_controls, ARRAY_SIZE(snd_ac97_cm9739_controls));
पूर्ण

अटल पूर्णांक patch_cm9739_post_spdअगर(काष्ठा snd_ac97 * ac97)
अणु
	वापस patch_build_controls(ac97, snd_ac97_cm9739_controls_spdअगर, ARRAY_SIZE(snd_ac97_cm9739_controls_spdअगर));
पूर्ण

अटल स्थिर काष्ठा snd_ac97_build_ops patch_cm9739_ops = अणु
	.build_specअगरic	= patch_cm9739_specअगरic,
	.build_post_spdअगर = patch_cm9739_post_spdअगर,
	.update_jacks = cm9739_update_jacks
पूर्ण;

अटल पूर्णांक patch_cm9739(काष्ठा snd_ac97 * ac97)
अणु
	अचिन्हित लघु val;

	ac97->build_ops = &patch_cm9739_ops;

	/* CM9739/A has no Master and PCM volume although the रेजिस्टर reacts */
	ac97->flags |= AC97_HAS_NO_MASTER_VOL | AC97_HAS_NO_PCM_VOL;
	snd_ac97_ग_लिखो_cache(ac97, AC97_MASTER, 0x8000);
	snd_ac97_ग_लिखो_cache(ac97, AC97_PCM, 0x8000);

	/* check spdअगर */
	val = snd_ac97_पढ़ो(ac97, AC97_EXTENDED_STATUS);
	अगर (val & AC97_EA_SPCV) अणु
		/* enable spdअगर in */
		snd_ac97_ग_लिखो_cache(ac97, AC97_CM9739_SPDIF_CTRL,
				     snd_ac97_पढ़ो(ac97, AC97_CM9739_SPDIF_CTRL) | 0x01);
		ac97->rates[AC97_RATES_SPDIF] = SNDRV_PCM_RATE_48000; /* 48k only */
	पूर्ण अन्यथा अणु
		ac97->ext_id &= ~AC97_EI_SPDIF; /* disable extended-id */
		ac97->rates[AC97_RATES_SPDIF] = 0;
	पूर्ण

	/* set-up multi channel */
	/* bit 14: 0 = SPDIF, 1 = EAPD */
	/* bit 13: enable पूर्णांकernal vref output क्रम mic */
	/* bit 12: disable center/lfe (चयनable) */
	/* bit 10: disable surround/line (चयनable) */
	/* bit 9: mix 2 surround off */
	/* bit 4: unकरोcumented; 0 mutes the CM9739A, which शेषs to 1 */
	/* bit 3: unकरोcumented; surround? */
	/* bit 0: dB */
	val = snd_ac97_पढ़ो(ac97, AC97_CM9739_MULTI_CHAN) & (1 << 4);
	val |= (1 << 3);
	val |= (1 << 13);
	अगर (! (ac97->ext_id & AC97_EI_SPDIF))
		val |= (1 << 14);
	snd_ac97_ग_लिखो_cache(ac97, AC97_CM9739_MULTI_CHAN, val);

	/* FIXME: set up GPIO */
	snd_ac97_ग_लिखो_cache(ac97, 0x70, 0x0100);
	snd_ac97_ग_लिखो_cache(ac97, 0x72, 0x0020);
	/* Special exception क्रम ASUS W1000/CMI9739. It करोes not have an SPDIF in. */
	अगर (ac97->pci &&
	     ac97->subप्रणाली_venकरोr == 0x1043 &&
	     ac97->subप्रणाली_device == 0x1843) अणु
		snd_ac97_ग_लिखो_cache(ac97, AC97_CM9739_SPDIF_CTRL,
			snd_ac97_पढ़ो(ac97, AC97_CM9739_SPDIF_CTRL) & ~0x01);
		snd_ac97_ग_लिखो_cache(ac97, AC97_CM9739_MULTI_CHAN,
			snd_ac97_पढ़ो(ac97, AC97_CM9739_MULTI_CHAN) | (1 << 14));
	पूर्ण

	वापस 0;
पूर्ण

#घोषणा AC97_CM9761_MULTI_CHAN	0x64
#घोषणा AC97_CM9761_FUNC	0x66
#घोषणा AC97_CM9761_SPDIF_CTRL	0x6c

अटल व्योम cm9761_update_jacks(काष्ठा snd_ac97 *ac97)
अणु
	/* FIXME: check the bits क्रम each model
	 *        model 83 is confirmed to work
	 */
	अटल स्थिर अचिन्हित लघु surr_on[3][2] = अणु
		अणु 0x0008, 0x0000 पूर्ण, /* 9761-78 & 82 */
		अणु 0x0000, 0x0008 पूर्ण, /* 9761-82 rev.B */
		अणु 0x0000, 0x0008 पूर्ण, /* 9761-83 */
	पूर्ण;
	अटल स्थिर अचिन्हित लघु clfe_on[3][2] = अणु
		अणु 0x0000, 0x1000 पूर्ण, /* 9761-78 & 82 */
		अणु 0x1000, 0x0000 पूर्ण, /* 9761-82 rev.B */
		अणु 0x0000, 0x1000 पूर्ण, /* 9761-83 */
	पूर्ण;
	अटल स्थिर अचिन्हित लघु surr_shared[3][2] = अणु
		अणु 0x0000, 0x0400 पूर्ण, /* 9761-78 & 82 */
		अणु 0x0000, 0x0400 पूर्ण, /* 9761-82 rev.B */
		अणु 0x0000, 0x0400 पूर्ण, /* 9761-83 */
	पूर्ण;
	अटल स्थिर अचिन्हित लघु clfe_shared[3][2] = अणु
		अणु 0x2000, 0x0880 पूर्ण, /* 9761-78 & 82 */
		अणु 0x0000, 0x2880 पूर्ण, /* 9761-82 rev.B */
		अणु 0x2000, 0x0800 पूर्ण, /* 9761-83 */
	पूर्ण;
	अचिन्हित लघु val = 0;

	val |= surr_on[ac97->spec.dev_flags][is_surround_on(ac97)];
	val |= clfe_on[ac97->spec.dev_flags][is_clfe_on(ac97)];
	val |= surr_shared[ac97->spec.dev_flags][is_shared_surrout(ac97)];
	val |= clfe_shared[ac97->spec.dev_flags][is_shared_clfeout(ac97)];

	snd_ac97_update_bits(ac97, AC97_CM9761_MULTI_CHAN, 0x3c88, val);
पूर्ण

अटल स्थिर काष्ठा snd_kcontrol_new snd_ac97_cm9761_controls[] = अणु
	AC97_SURROUND_JACK_MODE_CTL,
	AC97_CHANNEL_MODE_CTL,
पूर्ण;

अटल पूर्णांक cm9761_spdअगर_out_source_info(काष्ठा snd_kcontrol *kcontrol, काष्ठा snd_ctl_elem_info *uinfo)
अणु
	अटल स्थिर अक्षर * स्थिर texts[] = अणु "AC-Link", "ADC", "SPDIF-In" पूर्ण;

	वापस snd_ctl_क्रमागत_info(uinfo, 1, 3, texts);
पूर्ण

अटल पूर्णांक cm9761_spdअगर_out_source_get(काष्ठा snd_kcontrol *kcontrol, काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_ac97 *ac97 = snd_kcontrol_chip(kcontrol);

	अगर (ac97->regs[AC97_CM9761_FUNC] & 0x1)
		ucontrol->value.क्रमागतerated.item[0] = 2; /* SPDIF-loopback */
	अन्यथा अगर (ac97->regs[AC97_CM9761_SPDIF_CTRL] & 0x2)
		ucontrol->value.क्रमागतerated.item[0] = 1; /* ADC loopback */
	अन्यथा
		ucontrol->value.क्रमागतerated.item[0] = 0; /* AC-link */
	वापस 0;
पूर्ण

अटल पूर्णांक cm9761_spdअगर_out_source_put(काष्ठा snd_kcontrol *kcontrol, काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_ac97 *ac97 = snd_kcontrol_chip(kcontrol);

	अगर (ucontrol->value.क्रमागतerated.item[0] == 2)
		वापस snd_ac97_update_bits(ac97, AC97_CM9761_FUNC, 0x1, 0x1);
	snd_ac97_update_bits(ac97, AC97_CM9761_FUNC, 0x1, 0);
	वापस snd_ac97_update_bits(ac97, AC97_CM9761_SPDIF_CTRL, 0x2,
				    ucontrol->value.क्रमागतerated.item[0] == 1 ? 0x2 : 0);
पूर्ण

अटल स्थिर अक्षर * स्थिर cm9761_dac_घड़ी[] = अणु
	"AC-Link", "SPDIF-In", "Both"
पूर्ण;
अटल स्थिर काष्ठा ac97_क्रमागत cm9761_dac_घड़ी_क्रमागत =
	AC97_ENUM_SINGLE(AC97_CM9761_SPDIF_CTRL, 9, 3, cm9761_dac_घड़ी);

अटल स्थिर काष्ठा snd_kcontrol_new snd_ac97_cm9761_controls_spdअगर[] = अणु
	अणु /* BIT 1: SPDIFS */
		.अगरace	= SNDRV_CTL_ELEM_IFACE_MIXER,
		.name	= SNDRV_CTL_NAME_IEC958("",PLAYBACK,NONE) "Source",
		.info = cm9761_spdअगर_out_source_info,
		.get = cm9761_spdअगर_out_source_get,
		.put = cm9761_spdअगर_out_source_put,
	पूर्ण,
	/* BIT 2: IG_SPIV */
	AC97_SINGLE(SNDRV_CTL_NAME_IEC958("",CAPTURE,NONE) "Valid Switch", AC97_CM9761_SPDIF_CTRL, 2, 1, 0),
	/* BIT 3: SPI2F */
	AC97_SINGLE(SNDRV_CTL_NAME_IEC958("",CAPTURE,NONE) "Monitor", AC97_CM9761_SPDIF_CTRL, 3, 1, 0), 
	/* BIT 4: SPI2SDI */
	AC97_SINGLE(SNDRV_CTL_NAME_IEC958("",CAPTURE,SWITCH), AC97_CM9761_SPDIF_CTRL, 4, 1, 0),
	/* BIT 9-10: DAC_CTL */
	AC97_ENUM("DAC Clock Source", cm9761_dac_घड़ी_क्रमागत),
पूर्ण;

अटल पूर्णांक patch_cm9761_post_spdअगर(काष्ठा snd_ac97 * ac97)
अणु
	वापस patch_build_controls(ac97, snd_ac97_cm9761_controls_spdअगर, ARRAY_SIZE(snd_ac97_cm9761_controls_spdअगर));
पूर्ण

अटल पूर्णांक patch_cm9761_specअगरic(काष्ठा snd_ac97 * ac97)
अणु
	वापस patch_build_controls(ac97, snd_ac97_cm9761_controls, ARRAY_SIZE(snd_ac97_cm9761_controls));
पूर्ण

अटल स्थिर काष्ठा snd_ac97_build_ops patch_cm9761_ops = अणु
	.build_specअगरic	= patch_cm9761_specअगरic,
	.build_post_spdअगर = patch_cm9761_post_spdअगर,
	.update_jacks = cm9761_update_jacks
पूर्ण;

अटल पूर्णांक patch_cm9761(काष्ठा snd_ac97 *ac97)
अणु
	अचिन्हित लघु val;

	/* CM9761 has no PCM volume although the रेजिस्टर reacts */
	/* Master volume seems to have _some_ influence on the analog
	 * input sounds
	 */
	ac97->flags |= /*AC97_HAS_NO_MASTER_VOL |*/ AC97_HAS_NO_PCM_VOL;
	snd_ac97_ग_लिखो_cache(ac97, AC97_MASTER, 0x8808);
	snd_ac97_ग_लिखो_cache(ac97, AC97_PCM, 0x8808);

	ac97->spec.dev_flags = 0; /* 1 = model 82 revision B, 2 = model 83 */
	अगर (ac97->id == AC97_ID_CM9761_82) अणु
		अचिन्हित लघु पंचांगp;
		/* check page 1, reg 0x60 */
		val = snd_ac97_पढ़ो(ac97, AC97_INT_PAGING);
		snd_ac97_ग_लिखो_cache(ac97, AC97_INT_PAGING, (val & ~0x0f) | 0x01);
		पंचांगp = snd_ac97_पढ़ो(ac97, 0x60);
		ac97->spec.dev_flags = पंचांगp & 1; /* revision B? */
		snd_ac97_ग_लिखो_cache(ac97, AC97_INT_PAGING, val);
	पूर्ण अन्यथा अगर (ac97->id == AC97_ID_CM9761_83)
		ac97->spec.dev_flags = 2;

	ac97->build_ops = &patch_cm9761_ops;

	/* enable spdअगर */
	/* क्रमce the SPDIF bit in ext_id - codec करोesn't set this bit! */
        ac97->ext_id |= AC97_EI_SPDIF;
	/* to be sure: we overग_लिखो the ext status bits */
	snd_ac97_ग_लिखो_cache(ac97, AC97_EXTENDED_STATUS, 0x05c0);
	/* Don't set 0x0200 here.  This results in the silent analog output */
	snd_ac97_ग_लिखो_cache(ac97, AC97_CM9761_SPDIF_CTRL, 0x0001); /* enable spdअगर-in */
	ac97->rates[AC97_RATES_SPDIF] = SNDRV_PCM_RATE_48000; /* 48k only */

	/* set-up multi channel */
	/* bit 15: pc master beep off
	 * bit 14: pin47 = EAPD/SPDIF
	 * bit 13: vref ctl [= cm9739]
	 * bit 12: CLFE control (reverted on rev B)
	 * bit 11: Mic/center share (reverted on rev B)
	 * bit 10: sudकरोund/line share
	 * bit  9: Analog-in mix -> surround
	 * bit  8: Analog-in mix -> CLFE
	 * bit  7: Mic/LFE share (mic/center/lfe)
	 * bit  5: vref select (9761A)
	 * bit  4: front control
	 * bit  3: surround control (revereted with rev B)
	 * bit  2: front mic
	 * bit  1: stereo mic
	 * bit  0: mic boost level (0=20dB, 1=30dB)
	 */

#अगर 0
	अगर (ac97->spec.dev_flags)
		val = 0x0214;
	अन्यथा
		val = 0x321c;
#पूर्ण_अगर
	val = snd_ac97_पढ़ो(ac97, AC97_CM9761_MULTI_CHAN);
	val |= (1 << 4); /* front on */
	snd_ac97_ग_लिखो_cache(ac97, AC97_CM9761_MULTI_CHAN, val);

	/* FIXME: set up GPIO */
	snd_ac97_ग_लिखो_cache(ac97, 0x70, 0x0100);
	snd_ac97_ग_लिखो_cache(ac97, 0x72, 0x0020);

	वापस 0;
पूर्ण
       
#घोषणा AC97_CM9780_SIDE	0x60
#घोषणा AC97_CM9780_JACK	0x62
#घोषणा AC97_CM9780_MIXER	0x64
#घोषणा AC97_CM9780_MULTI_CHAN	0x66
#घोषणा AC97_CM9780_SPDIF	0x6c

अटल स्थिर अक्षर * स्थिर cm9780_ch_select[] = अणु
	"Front", "Side", "Center/LFE", "Rear"
पूर्ण;
अटल स्थिर काष्ठा ac97_क्रमागत cm9780_ch_select_क्रमागत =
	AC97_ENUM_SINGLE(AC97_CM9780_MULTI_CHAN, 6, 4, cm9780_ch_select);
अटल स्थिर काष्ठा snd_kcontrol_new cm9780_controls[] = अणु
	AC97_DOUBLE("Side Playback Switch", AC97_CM9780_SIDE, 15, 7, 1, 1),
	AC97_DOUBLE("Side Playback Volume", AC97_CM9780_SIDE, 8, 0, 31, 0),
	AC97_ENUM("Side Playback Route", cm9780_ch_select_क्रमागत),
पूर्ण;

अटल पूर्णांक patch_cm9780_specअगरic(काष्ठा snd_ac97 *ac97)
अणु
	वापस patch_build_controls(ac97, cm9780_controls, ARRAY_SIZE(cm9780_controls));
पूर्ण

अटल स्थिर काष्ठा snd_ac97_build_ops patch_cm9780_ops = अणु
	.build_specअगरic	= patch_cm9780_specअगरic,
	.build_post_spdअगर = patch_cm9761_post_spdअगर	/* identical with CM9761 */
पूर्ण;

अटल पूर्णांक patch_cm9780(काष्ठा snd_ac97 *ac97)
अणु
	अचिन्हित लघु val;

	ac97->build_ops = &patch_cm9780_ops;

	/* enable spdअगर */
	अगर (ac97->ext_id & AC97_EI_SPDIF) अणु
		ac97->rates[AC97_RATES_SPDIF] = SNDRV_PCM_RATE_48000; /* 48k only */
		val = snd_ac97_पढ़ो(ac97, AC97_CM9780_SPDIF);
		val |= 0x1; /* SPDI_EN */
		snd_ac97_ग_लिखो_cache(ac97, AC97_CM9780_SPDIF, val);
	पूर्ण

	वापस 0;
पूर्ण

/*
 * VIA VT1613 codec
 */
अटल स्थिर काष्ठा snd_kcontrol_new snd_ac97_controls_vt1613[] = अणु
AC97_SINGLE("DC Offset removal", 0x5a, 10, 1, 0),
पूर्ण;

अटल पूर्णांक patch_vt1613_specअगरic(काष्ठा snd_ac97 *ac97)
अणु
	वापस patch_build_controls(ac97, &snd_ac97_controls_vt1613[0],
				    ARRAY_SIZE(snd_ac97_controls_vt1613));
पूर्ण;

अटल स्थिर काष्ठा snd_ac97_build_ops patch_vt1613_ops = अणु
	.build_specअगरic	= patch_vt1613_specअगरic
पूर्ण;

अटल पूर्णांक patch_vt1613(काष्ठा snd_ac97 *ac97)
अणु
	ac97->build_ops = &patch_vt1613_ops;

	ac97->flags |= AC97_HAS_NO_VIDEO;
	ac97->caps |= AC97_BC_HEADPHONE;

	वापस 0;
पूर्ण

/*
 * VIA VT1616 codec
 */
अटल स्थिर काष्ठा snd_kcontrol_new snd_ac97_controls_vt1616[] = अणु
AC97_SINGLE("DC Offset removal", 0x5a, 10, 1, 0),
AC97_SINGLE("Alternate Level to Surround Out", 0x5a, 15, 1, 0),
AC97_SINGLE("Downmix LFE and Center to Front", 0x5a, 12, 1, 0),
AC97_SINGLE("Downmix Surround to Front", 0x5a, 11, 1, 0),
पूर्ण;

अटल स्थिर अक्षर * स्थिर follower_vols_vt1616[] = अणु
	"Front Playback Volume",
	"Surround Playback Volume",
	"Center Playback Volume",
	"LFE Playback Volume",
	शून्य
पूर्ण;

अटल स्थिर अक्षर * स्थिर follower_sws_vt1616[] = अणु
	"Front Playback Switch",
	"Surround Playback Switch",
	"Center Playback Switch",
	"LFE Playback Switch",
	शून्य
पूर्ण;

/* find a mixer control element with the given name */
अटल काष्ठा snd_kcontrol *snd_ac97_find_mixer_ctl(काष्ठा snd_ac97 *ac97,
						    स्थिर अक्षर *name)
अणु
	काष्ठा snd_ctl_elem_id id;
	स_रखो(&id, 0, माप(id));
	id.अगरace = SNDRV_CTL_ELEM_IFACE_MIXER;
	म_नकल(id.name, name);
	वापस snd_ctl_find_id(ac97->bus->card, &id);
पूर्ण

/* create a भव master control and add followers */
अटल पूर्णांक snd_ac97_add_vmaster(काष्ठा snd_ac97 *ac97, अक्षर *name,
				स्थिर अचिन्हित पूर्णांक *tlv,
				स्थिर अक्षर * स्थिर *followers)
अणु
	काष्ठा snd_kcontrol *kctl;
	स्थिर अक्षर * स्थिर *s;
	पूर्णांक err;

	kctl = snd_ctl_make_भव_master(name, tlv);
	अगर (!kctl)
		वापस -ENOMEM;
	err = snd_ctl_add(ac97->bus->card, kctl);
	अगर (err < 0)
		वापस err;

	क्रम (s = followers; *s; s++) अणु
		काष्ठा snd_kcontrol *sctl;

		sctl = snd_ac97_find_mixer_ctl(ac97, *s);
		अगर (!sctl) अणु
			dev_dbg(ac97->bus->card->dev,
				"Cannot find follower %s, skipped\n", *s);
			जारी;
		पूर्ण
		err = snd_ctl_add_follower(kctl, sctl);
		अगर (err < 0)
			वापस err;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक patch_vt1616_specअगरic(काष्ठा snd_ac97 * ac97)
अणु
	काष्ठा snd_kcontrol *kctl;
	पूर्णांक err;

	अगर (snd_ac97_try_bit(ac97, 0x5a, 9))
		अगर ((err = patch_build_controls(ac97, &snd_ac97_controls_vt1616[0], 1)) < 0)
			वापस err;
	अगर ((err = patch_build_controls(ac97, &snd_ac97_controls_vt1616[1], ARRAY_SIZE(snd_ac97_controls_vt1616) - 1)) < 0)
		वापस err;

	/* There is alपढ़ोy a misnamed master चयन.  Rename it.  */
	kctl = snd_ac97_find_mixer_ctl(ac97, "Master Playback Volume");
	अगर (!kctl)
		वापस -EINVAL;

	snd_ac97_नाम_vol_ctl(ac97, "Master Playback", "Front Playback");

	err = snd_ac97_add_vmaster(ac97, "Master Playback Volume",
				   kctl->tlv.p, follower_vols_vt1616);
	अगर (err < 0)
		वापस err;

	err = snd_ac97_add_vmaster(ac97, "Master Playback Switch",
				   शून्य, follower_sws_vt1616);
	अगर (err < 0)
		वापस err;

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा snd_ac97_build_ops patch_vt1616_ops = अणु
	.build_specअगरic	= patch_vt1616_specअगरic
पूर्ण;

अटल पूर्णांक patch_vt1616(काष्ठा snd_ac97 * ac97)
अणु
	ac97->build_ops = &patch_vt1616_ops;
	वापस 0;
पूर्ण

/*
 * VT1617A codec
 */

/*
 * unक्रमtunately, the vt1617a stashes the twiddlers required क्रम
 * noodling the i/o jacks on 2 dअगरferent regs. that means that we can't
 * use the easy way provided by AC97_ENUM_DOUBLE() we have to ग_लिखो
 * are own funcs.
 *
 * NB: this is असलolutely and utterly dअगरferent from the vt1618. dunno
 * about the 1616.
 */

/* copied from ac97_surround_jack_mode_info() */
अटल पूर्णांक snd_ac97_vt1617a_smart51_info(काष्ठा snd_kcontrol *kcontrol,
					 काष्ठा snd_ctl_elem_info *uinfo)
अणु
	/* ordering in this list reflects vt1617a करोcs क्रम Reg 20 and
	 * 7a and Table 6 that lays out the matrix NB WRT Table6: SM51
	 * is SM51EN *AND* it's Bit14, not Bit15 so the table is very
	 * counter-पूर्णांकuitive */ 

	अटल स्थिर अक्षर * स्थिर texts[] = अणु"LineIn Mic1", "LineIn Mic1 Mic3",
				       "Surr LFE/C Mic3", "LineIn LFE/C Mic3",
				       "LineIn Mic2", "LineIn Mic2 Mic1",
				       "Surr LFE Mic1", "Surr LFE Mic1 Mic2"पूर्ण;

	वापस snd_ctl_क्रमागत_info(uinfo, 1, 8, texts);
पूर्ण

अटल पूर्णांक snd_ac97_vt1617a_smart51_get(काष्ठा snd_kcontrol *kcontrol,
					काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	uलघु usSM51, usMS;  

	काष्ठा snd_ac97 *pac97;
	
	pac97 = snd_kcontrol_chip(kcontrol); /* grab codec handle */

	/* grab our desired bits, then mash them together in a manner
	 * consistent with Table 6 on page 17 in the 1617a करोcs */
 
	usSM51 = snd_ac97_पढ़ो(pac97, 0x7a) >> 14;
	usMS   = snd_ac97_पढ़ो(pac97, 0x20) >> 8;
  
	ucontrol->value.क्रमागतerated.item[0] = (usSM51 << 1) + usMS;

	वापस 0;
पूर्ण

अटल पूर्णांक snd_ac97_vt1617a_smart51_put(काष्ठा snd_kcontrol *kcontrol,
					काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	uलघु usSM51, usMS, usReg;  

	काष्ठा snd_ac97 *pac97;

	pac97 = snd_kcontrol_chip(kcontrol); /* grab codec handle */

	usSM51 = ucontrol->value.क्रमागतerated.item[0] >> 1;
	usMS   = ucontrol->value.क्रमागतerated.item[0] &  1;

	/* push our values पूर्णांकo the रेजिस्टर - consider that things will be left
	 * in a funky state अगर the ग_लिखो fails */

	usReg = snd_ac97_पढ़ो(pac97, 0x7a);
	snd_ac97_ग_लिखो_cache(pac97, 0x7a, (usReg & 0x3FFF) + (usSM51 << 14));
	usReg = snd_ac97_पढ़ो(pac97, 0x20);
	snd_ac97_ग_लिखो_cache(pac97, 0x20, (usReg & 0xFEFF) + (usMS   <<  8));

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा snd_kcontrol_new snd_ac97_controls_vt1617a[] = अणु

	AC97_SINGLE("Center/LFE Exchange", 0x5a, 8, 1, 0),
	/*
	 * These are used to enable/disable surround sound on motherboards
	 * that have 3 bidirectional analog jacks
	 */
	अणु
		.अगरace         = SNDRV_CTL_ELEM_IFACE_MIXER,
		.name          = "Smart 5.1 Select",
		.info          = snd_ac97_vt1617a_smart51_info,
		.get           = snd_ac97_vt1617a_smart51_get,
		.put           = snd_ac97_vt1617a_smart51_put,
	पूर्ण,
पूर्ण;

अटल पूर्णांक patch_vt1617a(काष्ठा snd_ac97 * ac97)
अणु
	पूर्णांक err = 0;
	पूर्णांक val;

	/* we choose to not fail out at this poपूर्णांक, but we tell the
	   caller when we वापस */

	err = patch_build_controls(ac97, &snd_ac97_controls_vt1617a[0],
				   ARRAY_SIZE(snd_ac97_controls_vt1617a));

	/* bring analog घातer consumption to normal by turning off the
	 * headphone amplअगरier, like WinXP driver क्रम EPIA SP
	 */
	/* We need to check the bit beक्रमe writing it.
	 * On some (many?) hardwares, setting bit actually clears it!
	 */
	val = snd_ac97_पढ़ो(ac97, 0x5c);
	अगर (!(val & 0x20))
		snd_ac97_ग_लिखो_cache(ac97, 0x5c, 0x20);

	ac97->ext_id |= AC97_EI_SPDIF;	/* क्रमce the detection of spdअगर */
	ac97->rates[AC97_RATES_SPDIF] = SNDRV_PCM_RATE_44100 | SNDRV_PCM_RATE_48000;
	ac97->build_ops = &patch_vt1616_ops;

	वापस err;
पूर्ण

/* VIA VT1618 8 CHANNEL AC97 CODEC
 *
 * VIA implements 'Smart 5.1' completely dअगरferently on the 1618 than
 * it करोes on the 1617a. awesome! They seem to have sourced this
 * particular revision of the technology from somebody अन्यथा, it's
 * called Universal Audio Jack and it shows up on some other folk's chips
 * as well.
 *
 * ordering in this list reflects vt1618 करोcs क्रम Reg 60h and
 * the block diagram, DACs are as follows:
 *
 *        OUT_O -> Front,
 *	  OUT_1 -> Surround,
 *	  OUT_2 -> C/LFE
 *
 * Unlike the 1617a, each OUT has a consistent set of mappings
 * क्रम all bitpatterns other than 00:
 *
 *        01       Unmixed Output
 *        10       Line In
 *        11       Mic  In
 *
 * Special Case of 00:
 *
 *        OUT_0    Mixed Output
 *        OUT_1    Reserved
 *        OUT_2    Reserved
 *
 * I have no idea what the hell Reserved करोes, but on an MSI
 * CN700T, i have to set it to get 5.1 output - YMMV, bad
 * shit may happen.
 *
 * If other chips use Universal Audio Jack, then this code might be applicable
 * to them.
 */

काष्ठा vt1618_uaj_item अणु
	अचिन्हित लघु mask;
	अचिन्हित लघु shअगरt;
	स्थिर अक्षर * स्थिर items[4];
पूर्ण;

/* This list reflects the vt1618 करोcs क्रम Venकरोr Defined Register 0x60. */

अटल स्थिर काष्ठा vt1618_uaj_item vt1618_uaj[3] = अणु
	अणु
		/* speaker jack */
		.mask  = 0x03,
		.shअगरt = 0,
		.items = अणु
			"Speaker Out", "DAC Unmixed Out", "Line In", "Mic In"
		पूर्ण
	पूर्ण,
	अणु
		/* line jack */
		.mask  = 0x0c,
		.shअगरt = 2,
		.items = अणु
			"Surround Out", "DAC Unmixed Out", "Line In", "Mic In"
		पूर्ण
	पूर्ण,
	अणु
		/* mic jack */
		.mask  = 0x30,
		.shअगरt = 4,
		.items = अणु
			"Center LFE Out", "DAC Unmixed Out", "Line In", "Mic In"
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल पूर्णांक snd_ac97_vt1618_UAJ_info(काष्ठा snd_kcontrol *kcontrol,
				    काष्ठा snd_ctl_elem_info *uinfo)
अणु
	वापस snd_ctl_क्रमागत_info(uinfo, 1, 4,
				 vt1618_uaj[kcontrol->निजी_value].items);
पूर्ण

/* All of the vt1618 Universal Audio Jack twiddlers are on
 * Venकरोr Defined Register 0x60, page 0. The bits, and thus
 * the mask, are the only thing that changes
 */
अटल पूर्णांक snd_ac97_vt1618_UAJ_get(काष्ठा snd_kcontrol *kcontrol,
				   काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	अचिन्हित लघु datpag, uaj;
	काष्ठा snd_ac97 *pac97 = snd_kcontrol_chip(kcontrol);

	mutex_lock(&pac97->page_mutex);

	datpag = snd_ac97_पढ़ो(pac97, AC97_INT_PAGING) & AC97_PAGE_MASK;
	snd_ac97_update_bits(pac97, AC97_INT_PAGING, AC97_PAGE_MASK, 0);

	uaj = snd_ac97_पढ़ो(pac97, 0x60) &
		vt1618_uaj[kcontrol->निजी_value].mask;

	snd_ac97_update_bits(pac97, AC97_INT_PAGING, AC97_PAGE_MASK, datpag);
	mutex_unlock(&pac97->page_mutex);

	ucontrol->value.क्रमागतerated.item[0] = uaj >>
		vt1618_uaj[kcontrol->निजी_value].shअगरt;

	वापस 0;
पूर्ण

अटल पूर्णांक snd_ac97_vt1618_UAJ_put(काष्ठा snd_kcontrol *kcontrol,
				   काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	वापस ac97_update_bits_page(snd_kcontrol_chip(kcontrol), 0x60,
				     vt1618_uaj[kcontrol->निजी_value].mask,
				     ucontrol->value.क्रमागतerated.item[0]<<
				     vt1618_uaj[kcontrol->निजी_value].shअगरt,
				     0);
पूर्ण

/* config aux in jack - not found on 3 jack motherboards or soundcards */

अटल पूर्णांक snd_ac97_vt1618_aux_info(काष्ठा snd_kcontrol *kcontrol,
				     काष्ठा snd_ctl_elem_info *uinfo)
अणु
	अटल स्थिर अक्षर * स्थिर txt_aux[] = अणु"Aux In", "Back Surr Out"पूर्ण;

	वापस snd_ctl_क्रमागत_info(uinfo, 1, 2, txt_aux);
पूर्ण

अटल पूर्णांक snd_ac97_vt1618_aux_get(काष्ठा snd_kcontrol *kcontrol,
				   काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	ucontrol->value.क्रमागतerated.item[0] =
		(snd_ac97_पढ़ो(snd_kcontrol_chip(kcontrol), 0x5c) & 0x0008)>>3;
	वापस 0;
पूर्ण

अटल पूर्णांक snd_ac97_vt1618_aux_put(काष्ठा snd_kcontrol *kcontrol,
				   काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	/* toggle surround rear dac घातer */

	snd_ac97_update_bits(snd_kcontrol_chip(kcontrol), 0x5c, 0x0008,
			     ucontrol->value.क्रमागतerated.item[0] << 3);

	/* toggle aux in surround rear out jack */

	वापस snd_ac97_update_bits(snd_kcontrol_chip(kcontrol), 0x76, 0x0008,
				    ucontrol->value.क्रमागतerated.item[0] << 3);
पूर्ण

अटल स्थिर काष्ठा snd_kcontrol_new snd_ac97_controls_vt1618[] = अणु
	AC97_SINGLE("Exchange Center/LFE", 0x5a,  8, 1,     0),
	AC97_SINGLE("DC Offset",           0x5a, 10, 1,     0),
	AC97_SINGLE("Soft Mute",           0x5c,  0, 1,     1),
	AC97_SINGLE("Headphone Amp",       0x5c,  5, 1,     1),
	AC97_DOUBLE("Back Surr Volume",    0x5e,  8, 0, 31, 1),
	AC97_SINGLE("Back Surr Switch",    0x5e, 15, 1,     1),
	अणु
		.अगरace         = SNDRV_CTL_ELEM_IFACE_MIXER,
		.name          = "Speaker Jack Mode",
		.info          = snd_ac97_vt1618_UAJ_info,
		.get           = snd_ac97_vt1618_UAJ_get,
		.put           = snd_ac97_vt1618_UAJ_put,
		.निजी_value = 0
	पूर्ण,
	अणु
		.अगरace         = SNDRV_CTL_ELEM_IFACE_MIXER,
		.name          = "Line Jack Mode",
		.info          = snd_ac97_vt1618_UAJ_info,
		.get           = snd_ac97_vt1618_UAJ_get,
		.put           = snd_ac97_vt1618_UAJ_put,
		.निजी_value = 1
	पूर्ण,
	अणु
		.अगरace         = SNDRV_CTL_ELEM_IFACE_MIXER,
		.name          = "Mic Jack Mode",
		.info          = snd_ac97_vt1618_UAJ_info,
		.get           = snd_ac97_vt1618_UAJ_get,
		.put           = snd_ac97_vt1618_UAJ_put,
		.निजी_value = 2
	पूर्ण,
	अणु
		.अगरace         = SNDRV_CTL_ELEM_IFACE_MIXER,
		.name          = "Aux Jack Mode",
		.info          = snd_ac97_vt1618_aux_info,
		.get           = snd_ac97_vt1618_aux_get,
		.put           = snd_ac97_vt1618_aux_put,
	पूर्ण
पूर्ण;

अटल पूर्णांक patch_vt1618(काष्ठा snd_ac97 *ac97)
अणु
	वापस patch_build_controls(ac97, snd_ac97_controls_vt1618,
				    ARRAY_SIZE(snd_ac97_controls_vt1618));
पूर्ण

/*
 */
अटल व्योम it2646_update_jacks(काष्ठा snd_ac97 *ac97)
अणु
	/* shared Line-In / Surround Out */
	snd_ac97_update_bits(ac97, 0x76, 1 << 9,
			     is_shared_surrout(ac97) ? (1<<9) : 0);
	/* shared Mic / Center/LFE Out */
	snd_ac97_update_bits(ac97, 0x76, 1 << 10,
			     is_shared_clfeout(ac97) ? (1<<10) : 0);
पूर्ण

अटल स्थिर काष्ठा snd_kcontrol_new snd_ac97_controls_it2646[] = अणु
	AC97_SURROUND_JACK_MODE_CTL,
	AC97_CHANNEL_MODE_CTL,
पूर्ण;

अटल स्थिर काष्ठा snd_kcontrol_new snd_ac97_spdअगर_controls_it2646[] = अणु
	AC97_SINGLE(SNDRV_CTL_NAME_IEC958("",CAPTURE,SWITCH), 0x76, 11, 1, 0),
	AC97_SINGLE("Analog to IEC958 Output", 0x76, 12, 1, 0),
	AC97_SINGLE("IEC958 Input Monitor", 0x76, 13, 1, 0),
पूर्ण;

अटल पूर्णांक patch_it2646_specअगरic(काष्ठा snd_ac97 * ac97)
अणु
	पूर्णांक err;
	अगर ((err = patch_build_controls(ac97, snd_ac97_controls_it2646, ARRAY_SIZE(snd_ac97_controls_it2646))) < 0)
		वापस err;
	अगर ((err = patch_build_controls(ac97, snd_ac97_spdअगर_controls_it2646, ARRAY_SIZE(snd_ac97_spdअगर_controls_it2646))) < 0)
		वापस err;
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा snd_ac97_build_ops patch_it2646_ops = अणु
	.build_specअगरic	= patch_it2646_specअगरic,
	.update_jacks = it2646_update_jacks
पूर्ण;

अटल पूर्णांक patch_it2646(काष्ठा snd_ac97 * ac97)
अणु
	ac97->build_ops = &patch_it2646_ops;
	/* full DAC volume */
	snd_ac97_ग_लिखो_cache(ac97, 0x5E, 0x0808);
	snd_ac97_ग_लिखो_cache(ac97, 0x7A, 0x0808);
	वापस 0;
पूर्ण

/*
 * Si3036 codec
 */

#घोषणा AC97_SI3036_CHIP_ID     0x5a
#घोषणा AC97_SI3036_LINE_CFG    0x5c

अटल स्थिर काष्ठा snd_kcontrol_new snd_ac97_controls_si3036[] = अणु
AC97_DOUBLE("Modem Speaker Volume", 0x5c, 14, 12, 3, 1)
पूर्ण;

अटल पूर्णांक patch_si3036_specअगरic(काष्ठा snd_ac97 * ac97)
अणु
	पूर्णांक idx, err;
	क्रम (idx = 0; idx < ARRAY_SIZE(snd_ac97_controls_si3036); idx++)
		अगर ((err = snd_ctl_add(ac97->bus->card, snd_ctl_new1(&snd_ac97_controls_si3036[idx], ac97))) < 0)
			वापस err;
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा snd_ac97_build_ops patch_si3036_ops = अणु
	.build_specअगरic	= patch_si3036_specअगरic,
पूर्ण;

अटल पूर्णांक mpatch_si3036(काष्ठा snd_ac97 * ac97)
अणु
	ac97->build_ops = &patch_si3036_ops;
	snd_ac97_ग_लिखो_cache(ac97, 0x5c, 0xf210 );
	snd_ac97_ग_लिखो_cache(ac97, 0x68, 0);
	वापस 0;
पूर्ण

/*
 * LM 4550 Codec
 *
 * We use a अटल resolution table since LM4550 codec cannot be
 * properly स्वतःprobed to determine the resolution via
 * check_volume_resolution().
 */

अटल स्थिर काष्ठा snd_ac97_res_table lm4550_restbl[] = अणु
	अणु AC97_MASTER, 0x1f1f पूर्ण,
	अणु AC97_HEADPHONE, 0x1f1f पूर्ण,
	अणु AC97_MASTER_MONO, 0x001f पूर्ण,
	अणु AC97_PC_BEEP, 0x001f पूर्ण,	/* LSB is ignored */
	अणु AC97_PHONE, 0x001f पूर्ण,
	अणु AC97_MIC, 0x001f पूर्ण,
	अणु AC97_LINE, 0x1f1f पूर्ण,
	अणु AC97_CD, 0x1f1f पूर्ण,
	अणु AC97_VIDEO, 0x1f1f पूर्ण,
	अणु AC97_AUX, 0x1f1f पूर्ण,
	अणु AC97_PCM, 0x1f1f पूर्ण,
	अणु AC97_REC_GAIN, 0x0f0f पूर्ण,
	अणु पूर्ण /* terminator */
पूर्ण;

अटल पूर्णांक patch_lm4550(काष्ठा snd_ac97 *ac97)
अणु
	ac97->res_table = lm4550_restbl;
	वापस 0;
पूर्ण

/* 
 *  UCB1400 codec (http://www.semiconductors.philips.com/acrobat_करोwnload/datasheets/UCB1400-02.pdf)
 */
अटल स्थिर काष्ठा snd_kcontrol_new snd_ac97_controls_ucb1400[] = अणु
/* enable/disable headphone driver which allows direct connection to
   stereo headphone without the use of बाह्यal DC blocking
   capacitors */
AC97_SINGLE("Headphone Driver", 0x6a, 6, 1, 0),
/* Filter used to compensate the DC offset is added in the ADC to हटाओ idle
   tones from the audio band. */
AC97_SINGLE("DC Filter", 0x6a, 4, 1, 0),
/* Control smart-low-घातer mode feature. Allows स्वतःmatic घातer करोwn
   of unused blocks in the ADC analog front end and the PLL. */
AC97_SINGLE("Smart Low Power Mode", 0x6c, 4, 3, 0),
पूर्ण;

अटल पूर्णांक patch_ucb1400_specअगरic(काष्ठा snd_ac97 * ac97)
अणु
	पूर्णांक idx, err;
	क्रम (idx = 0; idx < ARRAY_SIZE(snd_ac97_controls_ucb1400); idx++)
		अगर ((err = snd_ctl_add(ac97->bus->card, snd_ctl_new1(&snd_ac97_controls_ucb1400[idx], ac97))) < 0)
			वापस err;
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा snd_ac97_build_ops patch_ucb1400_ops = अणु
	.build_specअगरic	= patch_ucb1400_specअगरic,
पूर्ण;

अटल पूर्णांक patch_ucb1400(काष्ठा snd_ac97 * ac97)
अणु
	ac97->build_ops = &patch_ucb1400_ops;
	/* enable headphone driver and smart low घातer mode by शेष */
	snd_ac97_ग_लिखो_cache(ac97, 0x6a, 0x0050);
	snd_ac97_ग_लिखो_cache(ac97, 0x6c, 0x0030);
	वापस 0;
पूर्ण
