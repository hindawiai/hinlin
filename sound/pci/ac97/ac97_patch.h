<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 *  Copyright (c) by Jaroslav Kysela <perex@perex.cz>
 *  Universal पूर्णांकerface क्रम Audio Codec '97
 *
 *  For more details look to AC '97 component specअगरication revision 2.2
 *  by Intel Corporation (http://developer.पूर्णांकel.com).
 */

#घोषणा AC97_SINGLE_VALUE(reg,shअगरt,mask,invert) \
	((reg) | ((shअगरt) << 8) | ((shअगरt) << 12) | ((mask) << 16) | \
	 ((invert) << 24))
#घोषणा AC97_PAGE_SINGLE_VALUE(reg,shअगरt,mask,invert,page) \
	(AC97_SINGLE_VALUE(reg,shअगरt,mask,invert) | (1<<25) | ((page) << 26))
#घोषणा AC97_SINGLE(xname, reg, shअगरt, mask, invert) \
अणु .अगरace = SNDRV_CTL_ELEM_IFACE_MIXER, .name = xname, \
  .info = snd_ac97_info_volsw,		\
  .get = snd_ac97_get_volsw, .put = snd_ac97_put_volsw, \
  .निजी_value =  AC97_SINGLE_VALUE(reg, shअगरt, mask, invert) पूर्ण
#घोषणा AC97_PAGE_SINGLE(xname, reg, shअगरt, mask, invert, page)		\
अणु .अगरace = SNDRV_CTL_ELEM_IFACE_MIXER, .name = xname, \
  .info = snd_ac97_info_volsw,		\
  .get = snd_ac97_get_volsw, .put = snd_ac97_put_volsw, \
  .निजी_value =  AC97_PAGE_SINGLE_VALUE(reg, shअगरt, mask, invert, page) पूर्ण
#घोषणा AC97_DOUBLE(xname, reg, shअगरt_left, shअगरt_right, mask, invert) \
अणु .अगरace = SNDRV_CTL_ELEM_IFACE_MIXER, .name = (xname), \
  .info = snd_ac97_info_volsw,		\
  .get = snd_ac97_get_volsw, .put = snd_ac97_put_volsw, \
  .निजी_value = (reg) | ((shअगरt_left) << 8) | ((shअगरt_right) << 12) | ((mask) << 16) | ((invert) << 24) पूर्ण

/* क्रमागत control */
काष्ठा ac97_क्रमागत अणु
	अचिन्हित अक्षर reg;
	अचिन्हित अक्षर shअगरt_l;
	अचिन्हित अक्षर shअगरt_r;
	अचिन्हित लघु mask;
	स्थिर अक्षर * स्थिर *texts;
पूर्ण;

#घोषणा AC97_ENUM_DOUBLE(xreg, xshअगरt_l, xshअगरt_r, xmask, xtexts) \
अणु .reg = xreg, .shअगरt_l = xshअगरt_l, .shअगरt_r = xshअगरt_r, \
  .mask = xmask, .texts = xtexts पूर्ण
#घोषणा AC97_ENUM_SINGLE(xreg, xshअगरt, xmask, xtexts) \
	AC97_ENUM_DOUBLE(xreg, xshअगरt, xshअगरt, xmask, xtexts)
#घोषणा AC97_ENUM(xname, xक्रमागत) \
अणु .अगरace = SNDRV_CTL_ELEM_IFACE_MIXER, .name = xname, \
  .info = snd_ac97_info_क्रमागत_द्विगुन,		    \
  .get = snd_ac97_get_क्रमागत_द्विगुन, .put = snd_ac97_put_क्रमागत_द्विगुन, \
  .निजी_value = (अचिन्हित दीर्घ)&xक्रमागत पूर्ण

/* ac97_codec.c */
अटल स्थिर काष्ठा snd_kcontrol_new snd_ac97_controls_3d[];
अटल स्थिर काष्ठा snd_kcontrol_new snd_ac97_controls_spdअगर[];
अटल काष्ठा snd_kcontrol *snd_ac97_cnew(स्थिर काष्ठा snd_kcontrol_new *_ढाँचा,
					  काष्ठा snd_ac97 * ac97);
अटल पूर्णांक snd_ac97_info_volsw(काष्ठा snd_kcontrol *kcontrol,
			       काष्ठा snd_ctl_elem_info *uinfo);
अटल पूर्णांक snd_ac97_get_volsw(काष्ठा snd_kcontrol *kcontrol,
			      काष्ठा snd_ctl_elem_value *ucontrol);
अटल पूर्णांक snd_ac97_put_volsw(काष्ठा snd_kcontrol *kcontrol,
			      काष्ठा snd_ctl_elem_value *ucontrol);
अटल पूर्णांक snd_ac97_try_bit(काष्ठा snd_ac97 * ac97, पूर्णांक reg, पूर्णांक bit);
अटल पूर्णांक snd_ac97_हटाओ_ctl(काष्ठा snd_ac97 *ac97, स्थिर अक्षर *name,
			       स्थिर अक्षर *suffix);
अटल पूर्णांक snd_ac97_नाम_ctl(काष्ठा snd_ac97 *ac97, स्थिर अक्षर *src,
			       स्थिर अक्षर *dst, स्थिर अक्षर *suffix);
अटल पूर्णांक snd_ac97_swap_ctl(काष्ठा snd_ac97 *ac97, स्थिर अक्षर *s1,
			     स्थिर अक्षर *s2, स्थिर अक्षर *suffix);
अटल व्योम snd_ac97_नाम_vol_ctl(काष्ठा snd_ac97 *ac97, स्थिर अक्षर *src,
				    स्थिर अक्षर *dst);
#अगर_घोषित CONFIG_PM
अटल व्योम snd_ac97_restore_status(काष्ठा snd_ac97 *ac97);
अटल व्योम snd_ac97_restore_iec958(काष्ठा snd_ac97 *ac97);
#पूर्ण_अगर
अटल पूर्णांक snd_ac97_info_क्रमागत_द्विगुन(काष्ठा snd_kcontrol *kcontrol,
				     काष्ठा snd_ctl_elem_info *uinfo);
अटल पूर्णांक snd_ac97_get_क्रमागत_द्विगुन(काष्ठा snd_kcontrol *kcontrol,
				    काष्ठा snd_ctl_elem_value *ucontrol);
अटल पूर्णांक snd_ac97_put_क्रमागत_द्विगुन(काष्ठा snd_kcontrol *kcontrol,
				    काष्ठा snd_ctl_elem_value *ucontrol);
