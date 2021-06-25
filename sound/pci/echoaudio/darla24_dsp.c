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

	अगर (snd_BUG_ON((subdevice_id & 0xfff0) != DARLA24))
		वापस -ENODEV;

	अगर ((err = init_dsp_comm_page(chip))) अणु
		dev_err(chip->card->dev,
			"init_hw: could not initialize DSP comm page\n");
		वापस err;
	पूर्ण

	chip->device_id = device_id;
	chip->subdevice_id = subdevice_id;
	chip->bad_board = true;
	chip->dsp_code_to_load = FW_DARLA24_DSP;
	/* Since this card has no ASIC, mark it as loaded so everything
	   works OK */
	chip->asic_loaded = true;
	chip->input_घड़ी_प्रकारypes = ECHO_CLOCK_BIT_INTERNAL |
		ECHO_CLOCK_BIT_ESYNC;

	अगर ((err = load_firmware(chip)) < 0)
		वापस err;
	chip->bad_board = false;

	वापस err;
पूर्ण



अटल पूर्णांक set_mixer_शेषs(काष्ठा echoaudio *chip)
अणु
	वापस init_line_levels(chip);
पूर्ण



अटल u32 detect_input_घड़ीs(स्थिर काष्ठा echoaudio *chip)
अणु
	u32 घड़ीs_from_dsp, घड़ी_bits;

	/* Map the DSP घड़ी detect bits to the generic driver घड़ी
	   detect bits */
	घड़ीs_from_dsp = le32_to_cpu(chip->comm_page->status_घड़ीs);

	घड़ी_bits = ECHO_CLOCK_BIT_INTERNAL;

	अगर (घड़ीs_from_dsp & GLDM_CLOCK_DETECT_BIT_ESYNC)
		घड़ी_bits |= ECHO_CLOCK_BIT_ESYNC;

	वापस घड़ी_bits;
पूर्ण



/* The Darla24 has no ASIC. Just करो nothing */
अटल पूर्णांक load_asic(काष्ठा echoaudio *chip)
अणु
	वापस 0;
पूर्ण



अटल पूर्णांक set_sample_rate(काष्ठा echoaudio *chip, u32 rate)
अणु
	u8 घड़ी;

	चयन (rate) अणु
	हाल 96000:
		घड़ी = GD24_96000;
		अवरोध;
	हाल 88200:
		घड़ी = GD24_88200;
		अवरोध;
	हाल 48000:
		घड़ी = GD24_48000;
		अवरोध;
	हाल 44100:
		घड़ी = GD24_44100;
		अवरोध;
	हाल 32000:
		घड़ी = GD24_32000;
		अवरोध;
	हाल 22050:
		घड़ी = GD24_22050;
		अवरोध;
	हाल 16000:
		घड़ी = GD24_16000;
		अवरोध;
	हाल 11025:
		घड़ी = GD24_11025;
		अवरोध;
	हाल 8000:
		घड़ी = GD24_8000;
		अवरोध;
	शेष:
		dev_err(chip->card->dev,
			"set_sample_rate: Error, invalid sample rate %d\n",
			rate);
		वापस -EINVAL;
	पूर्ण

	अगर (रुको_handshake(chip))
		वापस -EIO;

	dev_dbg(chip->card->dev,
		"set_sample_rate: %d clock %d\n", rate, घड़ी);
	chip->sample_rate = rate;

	/* Override the sample rate अगर this card is set to Echo sync. */
	अगर (chip->input_घड़ी == ECHO_CLOCK_ESYNC)
		घड़ी = GD24_EXT_SYNC;

	chip->comm_page->sample_rate = cpu_to_le32(rate);	/* ignored by the DSP ? */
	chip->comm_page->gd_घड़ी_state = घड़ी;
	clear_handshake(chip);
	वापस send_vector(chip, DSP_VC_SET_GD_AUDIO_STATE);
पूर्ण



अटल पूर्णांक set_input_घड़ी(काष्ठा echoaudio *chip, u16 घड़ी)
अणु
	अगर (snd_BUG_ON(घड़ी != ECHO_CLOCK_INTERNAL &&
		       घड़ी != ECHO_CLOCK_ESYNC))
		वापस -EINVAL;
	chip->input_घड़ी = घड़ी;
	वापस set_sample_rate(chip, chip->sample_rate);
पूर्ण

