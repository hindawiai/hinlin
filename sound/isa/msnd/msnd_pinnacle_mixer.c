<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/***************************************************************************
			  msnd_pinnacle_mixer.c  -  description
			     -------------------
    begin		: Fre Jun 7 2002
    copyright 		: (C) 2002 by karsten wiese
    email		: annabellesgarden@yahoo.de
 ***************************************************************************/

/***************************************************************************
 *							      		   *
 *									   *
 ***************************************************************************/

#समावेश <linux/पन.स>
#समावेश <linux/export.h>

#समावेश <sound/core.h>
#समावेश <sound/control.h>
#समावेश "msnd.h"
#समावेश "msnd_pinnacle.h"


#घोषणा MSND_MIXER_VOLUME	0
#घोषणा MSND_MIXER_PCM		1
#घोषणा MSND_MIXER_AUX		2	/* Input source 1  (aux1) */
#घोषणा MSND_MIXER_IMIX		3	/*  Recording monitor  */
#घोषणा MSND_MIXER_SYNTH	4
#घोषणा MSND_MIXER_SPEAKER	5
#घोषणा MSND_MIXER_LINE		6
#घोषणा MSND_MIXER_MIC		7
#घोषणा MSND_MIXER_RECLEV	11	/* Recording level */
#घोषणा MSND_MIXER_IGAIN	12	/* Input gain */
#घोषणा MSND_MIXER_OGAIN	13	/* Output gain */
#घोषणा MSND_MIXER_DIGITAL	17	/* Digital (input) 1 */

/*	Device mask bits	*/

#घोषणा MSND_MASK_VOLUME	(1 << MSND_MIXER_VOLUME)
#घोषणा MSND_MASK_SYNTH		(1 << MSND_MIXER_SYNTH)
#घोषणा MSND_MASK_PCM		(1 << MSND_MIXER_PCM)
#घोषणा MSND_MASK_SPEAKER	(1 << MSND_MIXER_SPEAKER)
#घोषणा MSND_MASK_LINE		(1 << MSND_MIXER_LINE)
#घोषणा MSND_MASK_MIC		(1 << MSND_MIXER_MIC)
#घोषणा MSND_MASK_IMIX		(1 << MSND_MIXER_IMIX)
#घोषणा MSND_MASK_RECLEV	(1 << MSND_MIXER_RECLEV)
#घोषणा MSND_MASK_IGAIN		(1 << MSND_MIXER_IGAIN)
#घोषणा MSND_MASK_OGAIN		(1 << MSND_MIXER_OGAIN)
#घोषणा MSND_MASK_AUX		(1 << MSND_MIXER_AUX)
#घोषणा MSND_MASK_DIGITAL	(1 << MSND_MIXER_DIGITAL)

अटल पूर्णांक snd_msndmix_info_mux(काष्ठा snd_kcontrol *kcontrol,
				काष्ठा snd_ctl_elem_info *uinfo)
अणु
	अटल स्थिर अक्षर * स्थिर texts[3] = अणु
		"Analog", "MASS", "SPDIF",
	पूर्ण;
	काष्ठा snd_msnd *chip = snd_kcontrol_chip(kcontrol);
	अचिन्हित items = test_bit(F_HAVEDIGITAL, &chip->flags) ? 3 : 2;

	वापस snd_ctl_क्रमागत_info(uinfo, 1, items, texts);
पूर्ण

अटल पूर्णांक snd_msndmix_get_mux(काष्ठा snd_kcontrol *kcontrol,
				काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_msnd *chip = snd_kcontrol_chip(kcontrol);
	/* MSND_MASK_IMIX is the शेष */
	ucontrol->value.क्रमागतerated.item[0] = 0;

	अगर (chip->recsrc & MSND_MASK_SYNTH) अणु
		ucontrol->value.क्रमागतerated.item[0] = 1;
	पूर्ण अन्यथा अगर ((chip->recsrc & MSND_MASK_DIGITAL) &&
		 test_bit(F_HAVEDIGITAL, &chip->flags)) अणु
		ucontrol->value.क्रमागतerated.item[0] = 2;
	पूर्ण


	वापस 0;
पूर्ण

अटल पूर्णांक snd_msndmix_set_mux(काष्ठा snd_msnd *chip, पूर्णांक val)
अणु
	अचिन्हित newrecsrc;
	पूर्णांक change;
	अचिन्हित अक्षर msndbyte;

	चयन (val) अणु
	हाल 0:
		newrecsrc = MSND_MASK_IMIX;
		msndbyte = HDEXAR_SET_ANA_IN;
		अवरोध;
	हाल 1:
		newrecsrc = MSND_MASK_SYNTH;
		msndbyte = HDEXAR_SET_SYNTH_IN;
		अवरोध;
	हाल 2:
		newrecsrc = MSND_MASK_DIGITAL;
		msndbyte = HDEXAR_SET_DAT_IN;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण
	change  = newrecsrc != chip->recsrc;
	अगर (change) अणु
		change = 0;
		अगर (!snd_msnd_send_word(chip, 0, 0, msndbyte))
			अगर (!snd_msnd_send_dsp_cmd(chip, HDEX_AUX_REQ)) अणु
				chip->recsrc = newrecsrc;
				change = 1;
			पूर्ण
	पूर्ण
	वापस change;
पूर्ण

अटल पूर्णांक snd_msndmix_put_mux(काष्ठा snd_kcontrol *kcontrol,
				काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_msnd *msnd = snd_kcontrol_chip(kcontrol);
	वापस snd_msndmix_set_mux(msnd, ucontrol->value.क्रमागतerated.item[0]);
पूर्ण


अटल पूर्णांक snd_msndmix_volume_info(काष्ठा snd_kcontrol *kcontrol,
				   काष्ठा snd_ctl_elem_info *uinfo)
अणु
	uinfo->type = SNDRV_CTL_ELEM_TYPE_INTEGER;
	uinfo->count = 2;
	uinfo->value.पूर्णांकeger.min = 0;
	uinfo->value.पूर्णांकeger.max = 100;
	वापस 0;
पूर्ण

अटल पूर्णांक snd_msndmix_volume_get(काष्ठा snd_kcontrol *kcontrol,
				  काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_msnd *msnd = snd_kcontrol_chip(kcontrol);
	पूर्णांक addr = kcontrol->निजी_value;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&msnd->mixer_lock, flags);
	ucontrol->value.पूर्णांकeger.value[0] = msnd->left_levels[addr] * 100;
	ucontrol->value.पूर्णांकeger.value[0] /= 0xFFFF;
	ucontrol->value.पूर्णांकeger.value[1] = msnd->right_levels[addr] * 100;
	ucontrol->value.पूर्णांकeger.value[1] /= 0xFFFF;
	spin_unlock_irqrestore(&msnd->mixer_lock, flags);
	वापस 0;
पूर्ण

#घोषणा update_volm(a, b)						\
	करो अणु								\
		ग_लिखोw((dev->left_levels[a] >> 1) *			\
		       पढ़ोw(dev->SMA + SMA_wCurrMastVolLeft) / 0xffff,	\
		       dev->SMA + SMA_##b##Left);			\
		ग_लिखोw((dev->right_levels[a] >> 1)  *			\
		       पढ़ोw(dev->SMA + SMA_wCurrMastVolRight) / 0xffff, \
		       dev->SMA + SMA_##b##Right);			\
	पूर्ण जबतक (0);

#घोषणा update_poपंचांग(d, s, ar)						\
	करो अणु								\
		ग_लिखोb((dev->left_levels[d] >> 8) *			\
		       पढ़ोw(dev->SMA + SMA_wCurrMastVolLeft) / 0xffff, \
		       dev->SMA + SMA_##s##Left);			\
		ग_लिखोb((dev->right_levels[d] >> 8) *			\
		       पढ़ोw(dev->SMA + SMA_wCurrMastVolRight) / 0xffff, \
		       dev->SMA + SMA_##s##Right);			\
		अगर (snd_msnd_send_word(dev, 0, 0, ar) == 0)		\
			snd_msnd_send_dsp_cmd(dev, HDEX_AUX_REQ);	\
	पूर्ण जबतक (0);

#घोषणा update_pot(d, s, ar)						\
	करो अणु								\
		ग_लिखोb(dev->left_levels[d] >> 8,			\
		       dev->SMA + SMA_##s##Left);			\
		ग_लिखोb(dev->right_levels[d] >> 8,			\
		       dev->SMA + SMA_##s##Right);			\
		अगर (snd_msnd_send_word(dev, 0, 0, ar) == 0)		\
			snd_msnd_send_dsp_cmd(dev, HDEX_AUX_REQ);	\
	पूर्ण जबतक (0);


अटल पूर्णांक snd_msndmix_set(काष्ठा snd_msnd *dev, पूर्णांक d, पूर्णांक left, पूर्णांक right)
अणु
	पूर्णांक bLeft, bRight;
	पूर्णांक wLeft, wRight;
	पूर्णांक updatemaster = 0;

	अगर (d >= LEVEL_ENTRIES)
		वापस -EINVAL;

	bLeft = left * 0xff / 100;
	wLeft = left * 0xffff / 100;

	bRight = right * 0xff / 100;
	wRight = right * 0xffff / 100;

	dev->left_levels[d] = wLeft;
	dev->right_levels[d] = wRight;

	चयन (d) अणु
		/* master volume unscaled controls */
	हाल MSND_MIXER_LINE:			/* line pot control */
		/* scaled by IMIX in digital mix */
		ग_लिखोb(bLeft, dev->SMA + SMA_bInPotPosLeft);
		ग_लिखोb(bRight, dev->SMA + SMA_bInPotPosRight);
		अगर (snd_msnd_send_word(dev, 0, 0, HDEXAR_IN_SET_POTS) == 0)
			snd_msnd_send_dsp_cmd(dev, HDEX_AUX_REQ);
		अवरोध;
	हाल MSND_MIXER_MIC:			/* mic pot control */
		अगर (dev->type == msndClassic)
			वापस -EINVAL;
		/* scaled by IMIX in digital mix */
		ग_लिखोb(bLeft, dev->SMA + SMA_bMicPotPosLeft);
		ग_लिखोb(bRight, dev->SMA + SMA_bMicPotPosRight);
		अगर (snd_msnd_send_word(dev, 0, 0, HDEXAR_MIC_SET_POTS) == 0)
			snd_msnd_send_dsp_cmd(dev, HDEX_AUX_REQ);
		अवरोध;
	हाल MSND_MIXER_VOLUME:		/* master volume */
		ग_लिखोw(wLeft, dev->SMA + SMA_wCurrMastVolLeft);
		ग_लिखोw(wRight, dev->SMA + SMA_wCurrMastVolRight);
		fallthrough;
	हाल MSND_MIXER_AUX:			/* aux pot control */
		/* scaled by master volume */

		/* digital controls */
	हाल MSND_MIXER_SYNTH:			/* synth vol (dsp mix) */
	हाल MSND_MIXER_PCM:			/* pcm vol (dsp mix) */
	हाल MSND_MIXER_IMIX:			/* input monitor (dsp mix) */
		/* scaled by master volume */
		updatemaster = 1;
		अवरोध;

	शेष:
		वापस -EINVAL;
	पूर्ण

	अगर (updatemaster) अणु
		/* update master volume scaled controls */
		update_volm(MSND_MIXER_PCM, wCurrPlayVol);
		update_volm(MSND_MIXER_IMIX, wCurrInVol);
		अगर (dev->type == msndPinnacle)
			update_volm(MSND_MIXER_SYNTH, wCurrMHdrVol);
		update_poपंचांग(MSND_MIXER_AUX, bAuxPotPos, HDEXAR_AUX_SET_POTS);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक snd_msndmix_volume_put(काष्ठा snd_kcontrol *kcontrol,
				  काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_msnd *msnd = snd_kcontrol_chip(kcontrol);
	पूर्णांक change, addr = kcontrol->निजी_value;
	पूर्णांक left, right;
	अचिन्हित दीर्घ flags;

	left = ucontrol->value.पूर्णांकeger.value[0] % 101;
	right = ucontrol->value.पूर्णांकeger.value[1] % 101;
	spin_lock_irqsave(&msnd->mixer_lock, flags);
	change = msnd->left_levels[addr] != left
		|| msnd->right_levels[addr] != right;
	snd_msndmix_set(msnd, addr, left, right);
	spin_unlock_irqrestore(&msnd->mixer_lock, flags);
	वापस change;
पूर्ण


#घोषणा DUMMY_VOLUME(xname, xindex, addr) \
अणु .अगरace = SNDRV_CTL_ELEM_IFACE_MIXER, .name = xname, .index = xindex, \
  .info = snd_msndmix_volume_info, \
  .get = snd_msndmix_volume_get, .put = snd_msndmix_volume_put, \
  .निजी_value = addr पूर्ण


अटल स्थिर काष्ठा snd_kcontrol_new snd_msnd_controls[] = अणु
DUMMY_VOLUME("Master Volume", 0, MSND_MIXER_VOLUME),
DUMMY_VOLUME("PCM Volume", 0, MSND_MIXER_PCM),
DUMMY_VOLUME("Aux Volume", 0, MSND_MIXER_AUX),
DUMMY_VOLUME("Line Volume", 0, MSND_MIXER_LINE),
DUMMY_VOLUME("Mic Volume", 0, MSND_MIXER_MIC),
DUMMY_VOLUME("Monitor",	0, MSND_MIXER_IMIX),
अणु
	.अगरace = SNDRV_CTL_ELEM_IFACE_MIXER,
	.name = "Capture Source",
	.info = snd_msndmix_info_mux,
	.get = snd_msndmix_get_mux,
	.put = snd_msndmix_put_mux,
पूर्ण
पूर्ण;


पूर्णांक snd_msndmix_new(काष्ठा snd_card *card)
अणु
	काष्ठा snd_msnd *chip = card->निजी_data;
	अचिन्हित पूर्णांक idx;
	पूर्णांक err;

	अगर (snd_BUG_ON(!chip))
		वापस -EINVAL;
	spin_lock_init(&chip->mixer_lock);
	म_नकल(card->mixername, "MSND Pinnacle Mixer");

	क्रम (idx = 0; idx < ARRAY_SIZE(snd_msnd_controls); idx++) अणु
		err = snd_ctl_add(card,
				  snd_ctl_new1(snd_msnd_controls + idx, chip));
		अगर (err < 0)
			वापस err;
	पूर्ण

	वापस 0;
पूर्ण
EXPORT_SYMBOL(snd_msndmix_new);

व्योम snd_msndmix_setup(काष्ठा snd_msnd *dev)
अणु
	update_pot(MSND_MIXER_LINE, bInPotPos, HDEXAR_IN_SET_POTS);
	update_poपंचांग(MSND_MIXER_AUX, bAuxPotPos, HDEXAR_AUX_SET_POTS);
	update_volm(MSND_MIXER_PCM, wCurrPlayVol);
	update_volm(MSND_MIXER_IMIX, wCurrInVol);
	अगर (dev->type == msndPinnacle) अणु
		update_pot(MSND_MIXER_MIC, bMicPotPos, HDEXAR_MIC_SET_POTS);
		update_volm(MSND_MIXER_SYNTH, wCurrMHdrVol);
	पूर्ण
पूर्ण
EXPORT_SYMBOL(snd_msndmix_setup);

पूर्णांक snd_msndmix_क्रमce_recsrc(काष्ठा snd_msnd *dev, पूर्णांक recsrc)
अणु
	dev->recsrc = -1;
	वापस snd_msndmix_set_mux(dev, recsrc);
पूर्ण
EXPORT_SYMBOL(snd_msndmix_क्रमce_recsrc);
