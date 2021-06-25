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


/* These functions are common क्रम Gina24, Layla24 and Mona cards */


/* ASIC status check - some cards have one or two ASICs that need to be
loaded.  Once that load is complete, this function is called to see अगर
the load was successful.
If this load fails, it करोes not necessarily mean that the hardware is
defective - the बाह्यal box may be disconnected or turned off. */
अटल पूर्णांक check_asic_status(काष्ठा echoaudio *chip)
अणु
	u32 asic_status;

	send_vector(chip, DSP_VC_TEST_ASIC);

	/* The DSP will वापस a value to indicate whether or not the
	   ASIC is currently loaded */
	अगर (पढ़ो_dsp(chip, &asic_status) < 0) अणु
		dev_err(chip->card->dev,
			"check_asic_status: failed on read_dsp\n");
		chip->asic_loaded = false;
		वापस -EIO;
	पूर्ण

	chip->asic_loaded = (asic_status == ASIC_ALREADY_LOADED);
	वापस chip->asic_loaded ? 0 : -EIO;
पूर्ण



/* Most configuration of Gina24, Layla24, or Mona is accomplished by writing
the control रेजिस्टर.  ग_लिखो_control_reg sends the new control रेजिस्टर
value to the DSP. */
अटल पूर्णांक ग_लिखो_control_reg(काष्ठा echoaudio *chip, u32 value, अक्षर क्रमce)
अणु
	__le32 reg_value;

	/* Handle the digital input स्वतः-mute */
	अगर (chip->digital_in_स्वतःmute)
		value |= GML_DIGITAL_IN_AUTO_MUTE;
	अन्यथा
		value &= ~GML_DIGITAL_IN_AUTO_MUTE;

	dev_dbg(chip->card->dev, "write_control_reg: 0x%x\n", value);

	/* Write the control रेजिस्टर */
	reg_value = cpu_to_le32(value);
	अगर (reg_value != chip->comm_page->control_रेजिस्टर || क्रमce) अणु
		अगर (रुको_handshake(chip))
			वापस -EIO;
		chip->comm_page->control_रेजिस्टर = reg_value;
		clear_handshake(chip);
		वापस send_vector(chip, DSP_VC_WRITE_CONTROL_REG);
	पूर्ण
	वापस 0;
पूर्ण



/* Gina24, Layla24, and Mona support digital input स्वतः-mute.  If the digital
input स्वतः-mute is enabled, the DSP will only enable the digital inमाला_दो अगर
the card is syncing to a valid घड़ी on the ADAT or S/PDIF inमाला_दो.
If the स्वतः-mute is disabled, the digital inमाला_दो are enabled regardless of
what the input घड़ी is set or what is connected. */
अटल पूर्णांक set_input_स्वतः_mute(काष्ठा echoaudio *chip, पूर्णांक स्वतःmute)
अणु
	dev_dbg(chip->card->dev, "set_input_auto_mute %d\n", स्वतःmute);

	chip->digital_in_स्वतःmute = स्वतःmute;

	/* Re-set the input घड़ी to the current value - indirectly causes
	the स्वतः-mute flag to be sent to the DSP */
	वापस set_input_घड़ी(chip, chip->input_घड़ी);
पूर्ण



/* S/PDIF coax / S/PDIF optical / ADAT - चयन */
अटल पूर्णांक set_digital_mode(काष्ठा echoaudio *chip, u8 mode)
अणु
	u8 previous_mode;
	पूर्णांक err, i, o;

	अगर (chip->bad_board)
		वापस -EIO;

	/* All audio channels must be बंदd beक्रमe changing the digital mode */
	अगर (snd_BUG_ON(chip->pipe_alloc_mask))
		वापस -EAGAIN;

	अगर (snd_BUG_ON(!(chip->digital_modes & (1 << mode))))
		वापस -EINVAL;

	previous_mode = chip->digital_mode;
	err = dsp_set_digital_mode(chip, mode);

	/* If we successfully changed the digital mode from or to ADAT,
	   then make sure all output, input and monitor levels are
	   updated by the DSP comm object. */
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



/* Set the S/PDIF output क्रमmat */
अटल पूर्णांक set_professional_spdअगर(काष्ठा echoaudio *chip, अक्षर prof)
अणु
	u32 control_reg;
	पूर्णांक err;

	/* Clear the current S/PDIF flags */
	control_reg = le32_to_cpu(chip->comm_page->control_रेजिस्टर);
	control_reg &= GML_SPDIF_FORMAT_CLEAR_MASK;

	/* Set the new S/PDIF flags depending on the mode */
	control_reg |= GML_SPDIF_TWO_CHANNEL | GML_SPDIF_24_BIT |
		GML_SPDIF_COPY_PERMIT;
	अगर (prof) अणु
		/* Professional mode */
		control_reg |= GML_SPDIF_PRO_MODE;

		चयन (chip->sample_rate) अणु
		हाल 32000:
			control_reg |= GML_SPDIF_SAMPLE_RATE0 |
				GML_SPDIF_SAMPLE_RATE1;
			अवरोध;
		हाल 44100:
			control_reg |= GML_SPDIF_SAMPLE_RATE0;
			अवरोध;
		हाल 48000:
			control_reg |= GML_SPDIF_SAMPLE_RATE1;
			अवरोध;
		पूर्ण
	पूर्ण अन्यथा अणु
		/* Consumer mode */
		चयन (chip->sample_rate) अणु
		हाल 32000:
			control_reg |= GML_SPDIF_SAMPLE_RATE0 |
				GML_SPDIF_SAMPLE_RATE1;
			अवरोध;
		हाल 48000:
			control_reg |= GML_SPDIF_SAMPLE_RATE1;
			अवरोध;
		पूर्ण
	पूर्ण

	अगर ((err = ग_लिखो_control_reg(chip, control_reg, false)))
		वापस err;
	chip->professional_spdअगर = prof;
	dev_dbg(chip->card->dev, "set_professional_spdif to %s\n",
		prof ? "Professional" : "Consumer");
	वापस 0;
पूर्ण
