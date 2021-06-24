<शैली गुरु>
/***************************************************************************

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


अटल पूर्णांक init_hw(काष्ठा echoaudio *chip, u16 device_id, u16 subdevice_id)
अणु
	पूर्णांक err;

	अगर (snd_BUG_ON((subdevice_id & 0xfff0) != DARLA20))
		वापस -ENODEV;

	अगर ((err = init_dsp_comm_page(chip))) अणु
		dev_err(chip->card->dev,
			"init_hw: could not initialize DSP comm page\n");
		वापस err;
	पूर्ण

	chip->device_id = device_id;
	chip->subdevice_id = subdevice_id;
	chip->bad_board = true;
	chip->dsp_code_to_load = FW_DARLA20_DSP;
	chip->spdअगर_status = GD_SPDIF_STATUS_UNDEF;
	chip->घड़ी_state = GD_CLOCK_UNDEF;
	/* Since this card has no ASIC, mark it as loaded so everything
	   works OK */
	chip->asic_loaded = true;
	chip->input_घड़ी_प्रकारypes = ECHO_CLOCK_BIT_INTERNAL;

	अगर ((err = load_firmware(chip)) < 0)
		वापस err;
	chip->bad_board = false;

	वापस err;
पूर्ण



अटल पूर्णांक set_mixer_शेषs(काष्ठा echoaudio *chip)
अणु
	वापस init_line_levels(chip);
पूर्ण



/* The Darla20 has no बाह्यal घड़ी sources */
अटल u32 detect_input_घड़ीs(स्थिर काष्ठा echoaudio *chip)
अणु
	वापस ECHO_CLOCK_BIT_INTERNAL;
पूर्ण



/* The Darla20 has no ASIC. Just करो nothing */
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
