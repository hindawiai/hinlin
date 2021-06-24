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


अटल पूर्णांक set_vmixer_gain(काष्ठा echoaudio *chip, u16 output, u16 pipe,
			   पूर्णांक gain);
अटल पूर्णांक update_vmixer_level(काष्ठा echoaudio *chip);


अटल पूर्णांक init_hw(काष्ठा echoaudio *chip, u16 device_id, u16 subdevice_id)
अणु
	पूर्णांक err;

	अगर (snd_BUG_ON((subdevice_id & 0xfff0) != INDIGO_DJ))
		वापस -ENODEV;

	अगर ((err = init_dsp_comm_page(chip))) अणु
		dev_err(chip->card->dev,
			"init_hw - could not initialize DSP comm page\n");
		वापस err;
	पूर्ण

	chip->device_id = device_id;
	chip->subdevice_id = subdevice_id;
	chip->bad_board = true;
	chip->dsp_code_to_load = FW_INDIGO_DJ_DSP;
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



अटल u32 detect_input_घड़ीs(स्थिर काष्ठा echoaudio *chip)
अणु
	वापस ECHO_CLOCK_BIT_INTERNAL;
पूर्ण



/* The IndigoDJ has no ASIC. Just करो nothing */
अटल पूर्णांक load_asic(काष्ठा echoaudio *chip)
अणु
	वापस 0;
पूर्ण



अटल पूर्णांक set_sample_rate(काष्ठा echoaudio *chip, u32 rate)
अणु
	u32 control_reg;

	चयन (rate) अणु
	हाल 96000:
		control_reg = MIA_96000;
		अवरोध;
	हाल 88200:
		control_reg = MIA_88200;
		अवरोध;
	हाल 48000:
		control_reg = MIA_48000;
		अवरोध;
	हाल 44100:
		control_reg = MIA_44100;
		अवरोध;
	हाल 32000:
		control_reg = MIA_32000;
		अवरोध;
	शेष:
		dev_err(chip->card->dev,
			"set_sample_rate: %d invalid!\n", rate);
		वापस -EINVAL;
	पूर्ण

	/* Set the control रेजिस्टर अगर it has changed */
	अगर (control_reg != le32_to_cpu(chip->comm_page->control_रेजिस्टर)) अणु
		अगर (रुको_handshake(chip))
			वापस -EIO;

		chip->comm_page->sample_rate = cpu_to_le32(rate);	/* ignored by the DSP */
		chip->comm_page->control_रेजिस्टर = cpu_to_le32(control_reg);
		chip->sample_rate = rate;

		clear_handshake(chip);
		वापस send_vector(chip, DSP_VC_UPDATE_CLOCKS);
	पूर्ण
	वापस 0;
पूर्ण



/* This function routes the sound from a भव channel to a real output */
अटल पूर्णांक set_vmixer_gain(काष्ठा echoaudio *chip, u16 output, u16 pipe,
			   पूर्णांक gain)
अणु
	पूर्णांक index;

	अगर (snd_BUG_ON(pipe >= num_pipes_out(chip) ||
		       output >= num_busses_out(chip)))
		वापस -EINVAL;

	अगर (रुको_handshake(chip))
		वापस -EIO;

	chip->vmixer_gain[output][pipe] = gain;
	index = output * num_pipes_out(chip) + pipe;
	chip->comm_page->vmixer[index] = gain;

	dev_dbg(chip->card->dev,
		"set_vmixer_gain: pipe %d, out %d = %d\n", pipe, output, gain);
	वापस 0;
पूर्ण



/* Tell the DSP to पढ़ो and update भव mixer levels in comm page. */
अटल पूर्णांक update_vmixer_level(काष्ठा echoaudio *chip)
अणु
	अगर (रुको_handshake(chip))
		वापस -EIO;
	clear_handshake(chip);
	वापस send_vector(chip, DSP_VC_SET_VMIXER_GAIN);
पूर्ण

