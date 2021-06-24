<शैली गुरु>
/****************************************************************************

   Copyright Echo Digital Audio Corporation (c) 1998 - 2004
   All rights reserved
   www.echoaudio.com

   This file is part of Echo Digital Audio's generic driver library.

   Echo Digital Audio's generic driver library is मुक्त software;
   you can redistribute it and/or modअगरy it under the terms of
   the GNU General Public License as published by the Free Software
   Foundation.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License क्रम more details.

   You should have received a copy of the GNU General Public License
   aदीर्घ with this program; अगर not, ग_लिखो to the Free Software
   Foundation, Inc., 59 Temple Place - Suite 330, Boston,
   MA  02111-1307, USA.

   *************************************************************************

 Translation from C++ and adaptation क्रम use in ALSA-Driver
 were made by Giuliano Pochini <pochini@shiny.it>

****************************************************************************/



/* These functions are common क्रम all "3G" cards */


अटल पूर्णांक check_asic_status(काष्ठा echoaudio *chip)
अणु
	u32 box_status;

	अगर (रुको_handshake(chip))
		वापस -EIO;

	chip->comm_page->ext_box_status = cpu_to_le32(E3G_ASIC_NOT_LOADED);
	chip->asic_loaded = false;
	clear_handshake(chip);
	send_vector(chip, DSP_VC_TEST_ASIC);

	अगर (रुको_handshake(chip)) अणु
		chip->dsp_code = शून्य;
		वापस -EIO;
	पूर्ण

	box_status = le32_to_cpu(chip->comm_page->ext_box_status);
	dev_dbg(chip->card->dev, "box_status=%x\n", box_status);
	अगर (box_status == E3G_ASIC_NOT_LOADED)
		वापस -ENODEV;

	chip->asic_loaded = true;
	वापस box_status & E3G_BOX_TYPE_MASK;
पूर्ण



अटल अंतरभूत u32 get_frq_reg(काष्ठा echoaudio *chip)
अणु
	वापस le32_to_cpu(chip->comm_page->e3g_frq_रेजिस्टर);
पूर्ण



/* Most configuration of 3G cards is accomplished by writing the control
रेजिस्टर. ग_लिखो_control_reg sends the new control रेजिस्टर value to the DSP. */
अटल पूर्णांक ग_लिखो_control_reg(काष्ठा echoaudio *chip, u32 ctl, u32 frq,
			     अक्षर क्रमce)
अणु
	__le32 ctl_reg, frq_reg;

	अगर (रुको_handshake(chip))
		वापस -EIO;

	dev_dbg(chip->card->dev,
		"WriteControlReg: Setting 0x%x, 0x%x\n", ctl, frq);

	ctl_reg = cpu_to_le32(ctl);
	frq_reg = cpu_to_le32(frq);

	अगर (ctl_reg != chip->comm_page->control_रेजिस्टर ||
	    frq_reg != chip->comm_page->e3g_frq_रेजिस्टर || क्रमce) अणु
		chip->comm_page->e3g_frq_रेजिस्टर = frq_reg;
		chip->comm_page->control_रेजिस्टर = ctl_reg;
		clear_handshake(chip);
		वापस send_vector(chip, DSP_VC_WRITE_CONTROL_REG);
	पूर्ण

	dev_dbg(chip->card->dev, "WriteControlReg: not written, no change\n");
	वापस 0;
पूर्ण



/* Set the digital mode - currently क्रम Gina24, Layla24, Mona, 3G */
अटल पूर्णांक set_digital_mode(काष्ठा echoaudio *chip, u8 mode)
अणु
	u8 previous_mode;
	पूर्णांक err, i, o;

	/* All audio channels must be बंदd beक्रमe changing the digital mode */
	अगर (snd_BUG_ON(chip->pipe_alloc_mask))
		वापस -EAGAIN;

	अगर (snd_BUG_ON(!(chip->digital_modes & (1 << mode))))
		वापस -EINVAL;

	previous_mode = chip->digital_mode;
	err = dsp_set_digital_mode(chip, mode);

	/* If we successfully changed the digital mode from or to ADAT,
	 * then make sure all output, input and monitor levels are
	 * updated by the DSP comm object. */
	अगर (err >= 0 && previous_mode != mode &&
	    (previous_mode == DIGITAL_MODE_ADAT || mode == DIGITAL_MODE_ADAT)) अणु
		spin_lock_irq(&chip->lock);
		क्रम (o = 0; o < num_busses_out(chip); o++)
			क्रम (i = 0; i < num_busses_in(chip); i++)
				set_monitor_gain(chip, o, i,
						 chip->monitor_gain[o][i]);

#अगर_घोषित ECHOCARD_HAS_INPUT_GAIN
		क्रम (i = 0; i < num_busses_in(chip); i++)
			set_input_gain(chip, i, chip->input_gain[i]);
		update_input_line_level(chip);
#पूर्ण_अगर

		क्रम (o = 0; o < num_busses_out(chip); o++)
			set_output_gain(chip, o, chip->output_gain[o]);
		update_output_line_level(chip);
		spin_unlock_irq(&chip->lock);
	पूर्ण

	वापस err;
पूर्ण



अटल u32 set_spdअगर_bits(काष्ठा echoaudio *chip, u32 control_reg, u32 rate)
अणु
	control_reg &= E3G_SPDIF_FORMAT_CLEAR_MASK;

	चयन (rate) अणु
	हाल 32000 :
		control_reg |= E3G_SPDIF_SAMPLE_RATE0 | E3G_SPDIF_SAMPLE_RATE1;
		अवरोध;
	हाल 44100 :
		अगर (chip->professional_spdअगर)
			control_reg |= E3G_SPDIF_SAMPLE_RATE0;
		अवरोध;
	हाल 48000 :
		control_reg |= E3G_SPDIF_SAMPLE_RATE1;
		अवरोध;
	पूर्ण

	अगर (chip->professional_spdअगर)
		control_reg |= E3G_SPDIF_PRO_MODE;

	अगर (chip->non_audio_spdअगर)
		control_reg |= E3G_SPDIF_NOT_AUDIO;

	control_reg |= E3G_SPDIF_24_BIT | E3G_SPDIF_TWO_CHANNEL |
		E3G_SPDIF_COPY_PERMIT;

	वापस control_reg;
पूर्ण



/* Set the S/PDIF output क्रमmat */
अटल पूर्णांक set_professional_spdअगर(काष्ठा echoaudio *chip, अक्षर prof)
अणु
	u32 control_reg;

	control_reg = le32_to_cpu(chip->comm_page->control_रेजिस्टर);
	chip->professional_spdअगर = prof;
	control_reg = set_spdअगर_bits(chip, control_reg, chip->sample_rate);
	वापस ग_लिखो_control_reg(chip, control_reg, get_frq_reg(chip), 0);
पूर्ण



/* detect_input_घड़ीs() वापसs a biपंचांगask consisting of all the input घड़ीs
currently connected to the hardware; this changes as the user connects and
disconnects घड़ी inमाला_दो. You should use this inक्रमmation to determine which
घड़ीs the user is allowed to select. */
अटल u32 detect_input_घड़ीs(स्थिर काष्ठा echoaudio *chip)
अणु
	u32 घड़ीs_from_dsp, घड़ी_bits;

	/* Map the DSP घड़ी detect bits to the generic driver घड़ी
	 * detect bits */
	घड़ीs_from_dsp = le32_to_cpu(chip->comm_page->status_घड़ीs);

	घड़ी_bits = ECHO_CLOCK_BIT_INTERNAL;

	अगर (घड़ीs_from_dsp & E3G_CLOCK_DETECT_BIT_WORD)
		घड़ी_bits |= ECHO_CLOCK_BIT_WORD;

	चयन(chip->digital_mode) अणु
	हाल DIGITAL_MODE_SPDIF_RCA:
	हाल DIGITAL_MODE_SPDIF_OPTICAL:
		अगर (घड़ीs_from_dsp & E3G_CLOCK_DETECT_BIT_SPDIF)
			घड़ी_bits |= ECHO_CLOCK_BIT_SPDIF;
		अवरोध;
	हाल DIGITAL_MODE_ADAT:
		अगर (घड़ीs_from_dsp & E3G_CLOCK_DETECT_BIT_ADAT)
			घड़ी_bits |= ECHO_CLOCK_BIT_ADAT;
		अवरोध;
	पूर्ण

	वापस घड़ी_bits;
पूर्ण



अटल पूर्णांक load_asic(काष्ठा echoaudio *chip)
अणु
	पूर्णांक box_type, err;

	अगर (chip->asic_loaded)
		वापस 0;

	/* Give the DSP a few milliseconds to settle करोwn */
	mdelay(2);

	err = load_asic_generic(chip, DSP_FNC_LOAD_3G_ASIC, FW_3G_ASIC);
	अगर (err < 0)
		वापस err;

	chip->asic_code = FW_3G_ASIC;

	/* Now give the new ASIC some समय to set up */
	msleep(1000);
	/* See अगर it worked */
	box_type = check_asic_status(chip);

	/* Set up the control रेजिस्टर अगर the load succeeded -
	 * 48 kHz, पूर्णांकernal घड़ी, S/PDIF RCA mode */
	अगर (box_type >= 0) अणु
		err = ग_लिखो_control_reg(chip, E3G_48KHZ,
					E3G_FREQ_REG_DEFAULT, true);
		अगर (err < 0)
			वापस err;
	पूर्ण

	वापस box_type;
पूर्ण



अटल पूर्णांक set_sample_rate(काष्ठा echoaudio *chip, u32 rate)
अणु
	u32 control_reg, घड़ी, base_rate, frq_reg;

	/* Only set the घड़ी क्रम पूर्णांकernal mode. */
	अगर (chip->input_घड़ी != ECHO_CLOCK_INTERNAL) अणु
		dev_warn(chip->card->dev,
			 "Cannot set sample rate - clock not set to CLK_CLOCKININTERNAL\n");
		/* Save the rate anyhow */
		chip->comm_page->sample_rate = cpu_to_le32(rate);
		chip->sample_rate = rate;
		set_input_घड़ी(chip, chip->input_घड़ी);
		वापस 0;
	पूर्ण

	अगर (snd_BUG_ON(rate >= 50000 &&
		       chip->digital_mode == DIGITAL_MODE_ADAT))
		वापस -EINVAL;

	घड़ी = 0;
	control_reg = le32_to_cpu(chip->comm_page->control_रेजिस्टर);
	control_reg &= E3G_CLOCK_CLEAR_MASK;

	चयन (rate) अणु
	हाल 96000:
		घड़ी = E3G_96KHZ;
		अवरोध;
	हाल 88200:
		घड़ी = E3G_88KHZ;
		अवरोध;
	हाल 48000:
		घड़ी = E3G_48KHZ;
		अवरोध;
	हाल 44100:
		घड़ी = E3G_44KHZ;
		अवरोध;
	हाल 32000:
		घड़ी = E3G_32KHZ;
		अवरोध;
	शेष:
		घड़ी = E3G_CONTINUOUS_CLOCK;
		अगर (rate > 50000)
			घड़ी |= E3G_DOUBLE_SPEED_MODE;
		अवरोध;
	पूर्ण

	control_reg |= घड़ी;
	control_reg = set_spdअगर_bits(chip, control_reg, rate);

	base_rate = rate;
	अगर (base_rate > 50000)
		base_rate /= 2;
	अगर (base_rate < 32000)
		base_rate = 32000;

	frq_reg = E3G_MAGIC_NUMBER / base_rate - 2;
	अगर (frq_reg > E3G_FREQ_REG_MAX)
		frq_reg = E3G_FREQ_REG_MAX;

	chip->comm_page->sample_rate = cpu_to_le32(rate);	/* ignored by the DSP */
	chip->sample_rate = rate;
	dev_dbg(chip->card->dev,
		"SetSampleRate: %d clock %x\n", rate, control_reg);

	/* Tell the DSP about it - DSP पढ़ोs both control reg & freq reg */
	वापस ग_लिखो_control_reg(chip, control_reg, frq_reg, 0);
पूर्ण



/* Set the sample घड़ी source to पूर्णांकernal, S/PDIF, ADAT */
अटल पूर्णांक set_input_घड़ी(काष्ठा echoaudio *chip, u16 घड़ी)
अणु
	u32 control_reg, घड़ीs_from_dsp;


	/* Mask off the घड़ी select bits */
	control_reg = le32_to_cpu(chip->comm_page->control_रेजिस्टर) &
		E3G_CLOCK_CLEAR_MASK;
	घड़ीs_from_dsp = le32_to_cpu(chip->comm_page->status_घड़ीs);

	चयन (घड़ी) अणु
	हाल ECHO_CLOCK_INTERNAL:
		chip->input_घड़ी = ECHO_CLOCK_INTERNAL;
		वापस set_sample_rate(chip, chip->sample_rate);
	हाल ECHO_CLOCK_SPDIF:
		अगर (chip->digital_mode == DIGITAL_MODE_ADAT)
			वापस -EAGAIN;
		control_reg |= E3G_SPDIF_CLOCK;
		अगर (घड़ीs_from_dsp & E3G_CLOCK_DETECT_BIT_SPDIF96)
			control_reg |= E3G_DOUBLE_SPEED_MODE;
		अन्यथा
			control_reg &= ~E3G_DOUBLE_SPEED_MODE;
		अवरोध;
	हाल ECHO_CLOCK_ADAT:
		अगर (chip->digital_mode != DIGITAL_MODE_ADAT)
			वापस -EAGAIN;
		control_reg |= E3G_ADAT_CLOCK;
		control_reg &= ~E3G_DOUBLE_SPEED_MODE;
		अवरोध;
	हाल ECHO_CLOCK_WORD:
		control_reg |= E3G_WORD_CLOCK;
		अगर (घड़ीs_from_dsp & E3G_CLOCK_DETECT_BIT_WORD96)
			control_reg |= E3G_DOUBLE_SPEED_MODE;
		अन्यथा
			control_reg &= ~E3G_DOUBLE_SPEED_MODE;
		अवरोध;
	शेष:
		dev_err(chip->card->dev,
			"Input clock 0x%x not supported for Echo3G\n", घड़ी);
		वापस -EINVAL;
	पूर्ण

	chip->input_घड़ी = घड़ी;
	वापस ग_लिखो_control_reg(chip, control_reg, get_frq_reg(chip), 1);
पूर्ण



अटल पूर्णांक dsp_set_digital_mode(काष्ठा echoaudio *chip, u8 mode)
अणु
	u32 control_reg;
	पूर्णांक err, incompatible_घड़ी;

	/* Set घड़ी to "internal" अगर it's not compatible with the new mode */
	incompatible_घड़ी = false;
	चयन (mode) अणु
	हाल DIGITAL_MODE_SPDIF_OPTICAL:
	हाल DIGITAL_MODE_SPDIF_RCA:
		अगर (chip->input_घड़ी == ECHO_CLOCK_ADAT)
			incompatible_घड़ी = true;
		अवरोध;
	हाल DIGITAL_MODE_ADAT:
		अगर (chip->input_घड़ी == ECHO_CLOCK_SPDIF)
			incompatible_घड़ी = true;
		अवरोध;
	शेष:
		dev_err(chip->card->dev,
			"Digital mode not supported: %d\n", mode);
		वापस -EINVAL;
	पूर्ण

	spin_lock_irq(&chip->lock);

	अगर (incompatible_घड़ी) अणु
		chip->sample_rate = 48000;
		set_input_घड़ी(chip, ECHO_CLOCK_INTERNAL);
	पूर्ण

	/* Clear the current digital mode */
	control_reg = le32_to_cpu(chip->comm_page->control_रेजिस्टर);
	control_reg &= E3G_DIGITAL_MODE_CLEAR_MASK;

	/* Tweak the control reg */
	चयन (mode) अणु
	हाल DIGITAL_MODE_SPDIF_OPTICAL:
		control_reg |= E3G_SPDIF_OPTICAL_MODE;
		अवरोध;
	हाल DIGITAL_MODE_SPDIF_RCA:
		/* E3G_SPDIF_OPTICAL_MODE bit cleared */
		अवरोध;
	हाल DIGITAL_MODE_ADAT:
		control_reg |= E3G_ADAT_MODE;
		control_reg &= ~E3G_DOUBLE_SPEED_MODE;	/* @@ useless */
		अवरोध;
	पूर्ण

	err = ग_लिखो_control_reg(chip, control_reg, get_frq_reg(chip), 1);
	spin_unlock_irq(&chip->lock);
	अगर (err < 0)
		वापस err;
	chip->digital_mode = mode;

	dev_dbg(chip->card->dev, "set_digital_mode(%d)\n", chip->digital_mode);
	वापस incompatible_घड़ी;
पूर्ण
