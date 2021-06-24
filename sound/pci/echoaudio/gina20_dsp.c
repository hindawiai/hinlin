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


अटल पूर्णांक set_professional_spdअगर(काष्ठा echoaudio *chip, अक्षर prof);
अटल पूर्णांक update_flags(काष्ठा echoaudio *chip);


अटल पूर्णांक init_hw(काष्ठा echoaudio *chip, u16 device_id, u16 subdevice_id)
अणु
	पूर्णांक err;

	अगर (snd_BUG_ON((subdevice_id & 0xfff0) != GINA20))
		वापस -ENODEV;

	अगर ((err = init_dsp_comm_page(chip))) अणु
		dev_err(chip->card->dev,
			"init_hw - could not initialize DSP comm page\n");
		वापस err;
	पूर्ण

	chip->device_id = device_id;
	chip->subdevice_id = subdevice_id;
	chip->bad_board = true;
	chip->dsp_code_to_load = FW_GINA20_DSP;
	chip->spdअगर_status = GD_SPDIF_STATUS_UNDEF;
	chip->घड़ी_state = GD_CLOCK_UNDEF;
	/* Since this card has no ASIC, mark it as loaded so everything
	   works OK */
	chip->asic_loaded = true;
	chip->input_घड़ी_प्रकारypes = ECHO_CLOCK_BIT_INTERNAL |
		ECHO_CLOCK_BIT_SPDIF;

	अगर ((err = load_firmware(chip)) < 0)
		वापस err;
	chip->bad_board = false;

	वापस err;
पूर्ण



अटल पूर्णांक set_mixer_शेषs(काष्ठा echoaudio *chip)
अणु
	chip->professional_spdअगर = false;
	वापस init_line_levels(chip);
पूर्ण



अटल u32 detect_input_घड़ीs(स्थिर काष्ठा echoaudio *chip)
अणु
	u32 घड़ीs_from_dsp, घड़ी_bits;

	/* Map the DSP घड़ी detect bits to the generic driver घड़ी
	   detect bits */
	घड़ीs_from_dsp = le32_to_cpu(chip->comm_page->status_घड़ीs);

	घड़ी_bits = ECHO_CLOCK_BIT_INTERNAL;

	अगर (घड़ीs_from_dsp & GLDM_CLOCK_DETECT_BIT_SPDIF)
		घड़ी_bits |= ECHO_CLOCK_BIT_SPDIF;

	वापस घड़ी_bits;
पूर्ण



/* The Gina20 has no ASIC. Just करो nothing */
अटल पूर्णांक load_asic(काष्ठा echoaudio *chip)
अणु
	वापस 0;
पूर्ण



अटल पूर्णांक set_sample_rate(काष्ठा echoaudio *chip, u32 rate)
अणु
	u8 घड़ी_state, spdअगर_status;

	अगर (रुको_handshake(chip))
		वापस -EIO;

	चयन (rate) अणु
	हाल 44100:
		घड़ी_state = GD_CLOCK_44;
		spdअगर_status = GD_SPDIF_STATUS_44;
		अवरोध;
	हाल 48000:
		घड़ी_state = GD_CLOCK_48;
		spdअगर_status = GD_SPDIF_STATUS_48;
		अवरोध;
	शेष:
		घड़ी_state = GD_CLOCK_NOCHANGE;
		spdअगर_status = GD_SPDIF_STATUS_NOCHANGE;
		अवरोध;
	पूर्ण

	अगर (chip->घड़ी_state == घड़ी_state)
		घड़ी_state = GD_CLOCK_NOCHANGE;
	अगर (spdअगर_status == chip->spdअगर_status)
		spdअगर_status = GD_SPDIF_STATUS_NOCHANGE;

	chip->comm_page->sample_rate = cpu_to_le32(rate);
	chip->comm_page->gd_घड़ी_state = घड़ी_state;
	chip->comm_page->gd_spdअगर_status = spdअगर_status;
	chip->comm_page->gd_resampler_state = 3;	/* magic number - should always be 3 */

	/* Save the new audio state अगर it changed */
	अगर (घड़ी_state != GD_CLOCK_NOCHANGE)
		chip->घड़ी_state = घड़ी_state;
	अगर (spdअगर_status != GD_SPDIF_STATUS_NOCHANGE)
		chip->spdअगर_status = spdअगर_status;
	chip->sample_rate = rate;

	clear_handshake(chip);
	वापस send_vector(chip, DSP_VC_SET_GD_AUDIO_STATE);
पूर्ण



अटल पूर्णांक set_input_घड़ी(काष्ठा echoaudio *chip, u16 घड़ी)
अणु

	चयन (घड़ी) अणु
	हाल ECHO_CLOCK_INTERNAL:
		/* Reset the audio state to unknown (just in हाल) */
		chip->घड़ी_state = GD_CLOCK_UNDEF;
		chip->spdअगर_status = GD_SPDIF_STATUS_UNDEF;
		set_sample_rate(chip, chip->sample_rate);
		chip->input_घड़ी = घड़ी;
		अवरोध;
	हाल ECHO_CLOCK_SPDIF:
		chip->comm_page->gd_घड़ी_state = GD_CLOCK_SPDIFIN;
		chip->comm_page->gd_spdअगर_status = GD_SPDIF_STATUS_NOCHANGE;
		clear_handshake(chip);
		send_vector(chip, DSP_VC_SET_GD_AUDIO_STATE);
		chip->घड़ी_state = GD_CLOCK_SPDIFIN;
		chip->input_घड़ी = घड़ी;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण



/* Set input bus gain (one unit is 0.5dB !) */
अटल पूर्णांक set_input_gain(काष्ठा echoaudio *chip, u16 input, पूर्णांक gain)
अणु
	अगर (snd_BUG_ON(input >= num_busses_in(chip)))
		वापस -EINVAL;

	अगर (रुको_handshake(chip))
		वापस -EIO;

	chip->input_gain[input] = gain;
	gain += GL20_INPUT_GAIN_MAGIC_NUMBER;
	chip->comm_page->line_in_level[input] = gain;
	वापस 0;
पूर्ण



/* Tell the DSP to reपढ़ो the flags from the comm page */
अटल पूर्णांक update_flags(काष्ठा echoaudio *chip)
अणु
	अगर (रुको_handshake(chip))
		वापस -EIO;
	clear_handshake(chip);
	वापस send_vector(chip, DSP_VC_UPDATE_FLAGS);
पूर्ण



अटल पूर्णांक set_professional_spdअगर(काष्ठा echoaudio *chip, अक्षर prof)
अणु
	अगर (prof)
		chip->comm_page->flags |=
			cpu_to_le32(DSP_FLAG_PROFESSIONAL_SPDIF);
	अन्यथा
		chip->comm_page->flags &=
			~cpu_to_le32(DSP_FLAG_PROFESSIONAL_SPDIF);
	chip->professional_spdअगर = prof;
	वापस update_flags(chip);
पूर्ण
