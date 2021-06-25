<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Driver क्रम Digigram VX soundcards
 *
 * IEC958 stuff
 *
 * Copyright (c) 2002 by Takashi Iwai <tiwai@suse.de>
 */

#समावेश <linux/delay.h>
#समावेश <sound/core.h>
#समावेश <sound/vx_core.h>
#समावेश "vx_cmd.h"


/*
 * vx_modअगरy_board_घड़ी - tell the board that its घड़ी has been modअगरied
 * @sync: DSP needs to resynchronize its FIFO
 */
अटल पूर्णांक vx_modअगरy_board_घड़ी(काष्ठा vx_core *chip, पूर्णांक sync)
अणु
	काष्ठा vx_rmh rmh;

	vx_init_rmh(&rmh, CMD_MODIFY_CLOCK);
	/* Ask the DSP to resynchronize its FIFO. */
	अगर (sync)
		rmh.Cmd[0] |= CMD_MODIFY_CLOCK_S_BIT;
	वापस vx_send_msg(chip, &rmh);
पूर्ण

/*
 * vx_modअगरy_board_inमाला_दो - resync audio inमाला_दो
 */
अटल पूर्णांक vx_modअगरy_board_inमाला_दो(काष्ठा vx_core *chip)
अणु
	काष्ठा vx_rmh rmh;

	vx_init_rmh(&rmh, CMD_RESYNC_AUDIO_INPUTS);
        rmh.Cmd[0] |= 1 << 0; /* reference: AUDIO 0 */
	वापस vx_send_msg(chip, &rmh);
पूर्ण

/*
 * vx_पढ़ो_one_cbit - पढ़ो one bit from UER config
 * @index: the bit index
 * वापसs 0 or 1.
 */
अटल पूर्णांक vx_पढ़ो_one_cbit(काष्ठा vx_core *chip, पूर्णांक index)
अणु
	पूर्णांक val;

	mutex_lock(&chip->lock);
	अगर (chip->type >= VX_TYPE_VXPOCKET) अणु
		vx_outb(chip, CSUER, 1); /* पढ़ो */
		vx_outb(chip, RUER, index & XX_UER_CBITS_OFFSET_MASK);
		val = (vx_inb(chip, RUER) >> 7) & 0x01;
	पूर्ण अन्यथा अणु
		vx_outl(chip, CSUER, 1); /* पढ़ो */
		vx_outl(chip, RUER, index & XX_UER_CBITS_OFFSET_MASK);
		val = (vx_inl(chip, RUER) >> 7) & 0x01;
	पूर्ण
	mutex_unlock(&chip->lock);
	वापस val;
पूर्ण

/*
 * vx_ग_लिखो_one_cbit - ग_लिखो one bit to UER config
 * @index: the bit index
 * @val: bit value, 0 or 1
 */
अटल व्योम vx_ग_लिखो_one_cbit(काष्ठा vx_core *chip, पूर्णांक index, पूर्णांक val)
अणु
	val = !!val;	/* 0 or 1 */
	mutex_lock(&chip->lock);
	अगर (vx_is_pcmcia(chip)) अणु
		vx_outb(chip, CSUER, 0); /* ग_लिखो */
		vx_outb(chip, RUER, (val << 7) | (index & XX_UER_CBITS_OFFSET_MASK));
	पूर्ण अन्यथा अणु
		vx_outl(chip, CSUER, 0); /* ग_लिखो */
		vx_outl(chip, RUER, (val << 7) | (index & XX_UER_CBITS_OFFSET_MASK));
	पूर्ण
	mutex_unlock(&chip->lock);
पूर्ण

/*
 * vx_पढ़ो_uer_status - पढ़ो the current UER status
 * @mode: poपूर्णांकer to store the UER mode, VX_UER_MODE_XXX
 *
 * वापसs the frequency of UER, or 0 अगर not sync,
 * or a negative error code.
 */
अटल पूर्णांक vx_पढ़ो_uer_status(काष्ठा vx_core *chip, अचिन्हित पूर्णांक *mode)
अणु
	पूर्णांक val, freq;

	/* Default values */
	freq = 0;

	/* Read UER status */
	अगर (vx_is_pcmcia(chip))
	    val = vx_inb(chip, CSUER);
	अन्यथा
	    val = vx_inl(chip, CSUER);
	अगर (val < 0)
		वापस val;
	/* If घड़ी is present, पढ़ो frequency */
	अगर (val & VX_SUER_CLOCK_PRESENT_MASK) अणु
		चयन (val & VX_SUER_FREQ_MASK) अणु
		हाल VX_SUER_FREQ_32KHz_MASK:
			freq = 32000;
			अवरोध;
		हाल VX_SUER_FREQ_44KHz_MASK:
			freq = 44100;
			अवरोध;
		हाल VX_SUER_FREQ_48KHz_MASK:
			freq = 48000;
			अवरोध;
		पूर्ण
        पूर्ण
	अगर (val & VX_SUER_DATA_PRESENT_MASK)
		/* bit 0 corresponds to consumer/professional bit */
		*mode = vx_पढ़ो_one_cbit(chip, 0) ?
			VX_UER_MODE_PROFESSIONAL : VX_UER_MODE_CONSUMER;
	अन्यथा
		*mode = VX_UER_MODE_NOT_PRESENT;

	वापस freq;
पूर्ण


/*
 * compute the sample घड़ी value from frequency
 *
 * The क्रमmula is as follows:
 *
 *    HexFreq = (dword) ((द्विगुन) ((द्विगुन) 28224000 / (द्विगुन) Frequency))
 *    चयन ( HexFreq & 0x00000F00 )
 *    हाल 0x00000100: ;
 *    हाल 0x00000200:
 *    हाल 0x00000300: HexFreq -= 0x00000201 ;
 *    हाल 0x00000400:
 *    हाल 0x00000500:
 *    हाल 0x00000600:
 *    हाल 0x00000700: HexFreq = (dword) (((द्विगुन) 28224000 / (द्विगुन) (Frequency*2)) - 1)
 *    शेष        : HexFreq = (dword) ((द्विगुन) 28224000 / (द्विगुन) (Frequency*4)) - 0x000001FF
 */

अटल पूर्णांक vx_calc_घड़ी_from_freq(काष्ठा vx_core *chip, पूर्णांक freq)
अणु
	पूर्णांक hexfreq;

	अगर (snd_BUG_ON(freq <= 0))
		वापस 0;

	hexfreq = (28224000 * 10) / freq;
	hexfreq = (hexfreq + 5) / 10;

	/* max freq = 55125 Hz */
	अगर (snd_BUG_ON(hexfreq <= 0x00000200))
		वापस 0;

	अगर (hexfreq <= 0x03ff)
		वापस hexfreq - 0x00000201;
	अगर (hexfreq <= 0x07ff) 
		वापस (hexfreq / 2) - 1;
	अगर (hexfreq <= 0x0fff)
		वापस (hexfreq / 4) + 0x000001ff;

	वापस 0x5fe; 	/* min freq = 6893 Hz */
पूर्ण


/*
 * vx_change_घड़ी_source - change the घड़ी source
 * @source: the new source
 */
अटल व्योम vx_change_घड़ी_source(काष्ठा vx_core *chip, पूर्णांक source)
अणु
	/* we mute DAC to prevent clicks */
	vx_toggle_dac_mute(chip, 1);
	mutex_lock(&chip->lock);
	chip->ops->set_घड़ी_source(chip, source);
	chip->घड़ी_source = source;
	mutex_unlock(&chip->lock);
	/* unmute */
	vx_toggle_dac_mute(chip, 0);
पूर्ण


/*
 * set the पूर्णांकernal घड़ी
 */
व्योम vx_set_पूर्णांकernal_घड़ी(काष्ठा vx_core *chip, अचिन्हित पूर्णांक freq)
अणु
	पूर्णांक घड़ी;

	/* Get real घड़ी value */
	घड़ी = vx_calc_घड़ी_from_freq(chip, freq);
	snd_prपूर्णांकdd(KERN_DEBUG "set internal clock to 0x%x from freq %d\n", घड़ी, freq);
	mutex_lock(&chip->lock);
	अगर (vx_is_pcmcia(chip)) अणु
		vx_outb(chip, HIFREQ, (घड़ी >> 8) & 0x0f);
		vx_outb(chip, LOFREQ, घड़ी & 0xff);
	पूर्ण अन्यथा अणु
		vx_outl(chip, HIFREQ, (घड़ी >> 8) & 0x0f);
		vx_outl(chip, LOFREQ, घड़ी & 0xff);
	पूर्ण
	mutex_unlock(&chip->lock);
पूर्ण


/*
 * set the iec958 status bits
 * @bits: 32-bit status bits
 */
व्योम vx_set_iec958_status(काष्ठा vx_core *chip, अचिन्हित पूर्णांक bits)
अणु
	पूर्णांक i;

	अगर (chip->chip_status & VX_STAT_IS_STALE)
		वापस;

	क्रम (i = 0; i < 32; i++)
		vx_ग_लिखो_one_cbit(chip, i, bits & (1 << i));
पूर्ण


/*
 * vx_set_घड़ी - change the घड़ी and audio source अगर necessary
 */
पूर्णांक vx_set_घड़ी(काष्ठा vx_core *chip, अचिन्हित पूर्णांक freq)
अणु
	पूर्णांक src_changed = 0;

	अगर (chip->chip_status & VX_STAT_IS_STALE)
		वापस 0;

	/* change the audio source अगर possible */
	vx_sync_audio_source(chip);

	अगर (chip->घड़ी_mode == VX_CLOCK_MODE_EXTERNAL ||
	    (chip->घड़ी_mode == VX_CLOCK_MODE_AUTO &&
	     chip->audio_source == VX_AUDIO_SRC_DIGITAL)) अणु
		अगर (chip->घड़ी_source != UER_SYNC) अणु
			vx_change_घड़ी_source(chip, UER_SYNC);
			mdelay(6);
			src_changed = 1;
		पूर्ण
	पूर्ण अन्यथा अगर (chip->घड़ी_mode == VX_CLOCK_MODE_INTERNAL ||
		   (chip->घड़ी_mode == VX_CLOCK_MODE_AUTO &&
		    chip->audio_source != VX_AUDIO_SRC_DIGITAL)) अणु
		अगर (chip->घड़ी_source != INTERNAL_QUARTZ) अणु
			vx_change_घड़ी_source(chip, INTERNAL_QUARTZ);
			src_changed = 1;
		पूर्ण
		अगर (chip->freq == freq)
			वापस 0;
		vx_set_पूर्णांकernal_घड़ी(chip, freq);
		अगर (src_changed)
			vx_modअगरy_board_inमाला_दो(chip);
	पूर्ण
	अगर (chip->freq == freq)
		वापस 0;
	chip->freq = freq;
	vx_modअगरy_board_घड़ी(chip, 1);
	वापस 0;
पूर्ण


/*
 * vx_change_frequency - called from पूर्णांकerrupt handler
 */
पूर्णांक vx_change_frequency(काष्ठा vx_core *chip)
अणु
	पूर्णांक freq;

	अगर (chip->chip_status & VX_STAT_IS_STALE)
		वापस 0;

	अगर (chip->घड़ी_source == INTERNAL_QUARTZ)
		वापस 0;
	/*
	 * Read the real UER board frequency
	 */
	freq = vx_पढ़ो_uer_status(chip, &chip->uer_detected);
	अगर (freq < 0)
		वापस freq;
	/*
	 * The frequency computed by the DSP is good and
	 * is dअगरferent from the previous computed.
	 */
	अगर (freq == 48000 || freq == 44100 || freq == 32000)
		chip->freq_detected = freq;

	वापस 0;
पूर्ण
