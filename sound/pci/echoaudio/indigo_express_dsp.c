<शैली गुरु>
/************************************************************************

This file is part of Echo Digital Audio's generic driver library.
Copyright Echo Digital Audio Corporation (c) 1998 - 2005
All rights reserved
www.echoaudio.com

This library is मुक्त software; you can redistribute it and/or
modअगरy it under the terms of the GNU Lesser General Public
License as published by the Free Software Foundation; either
version 2.1 of the License, or (at your option) any later version.

This library is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
Lesser General Public License क्रम more details.

You should have received a copy of the GNU Lesser General Public
License aदीर्घ with this library; अगर not, ग_लिखो to the Free Software
Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA

*************************************************************************

 Translation from C++ and adaptation क्रम use in ALSA-Driver
 were made by Giuliano Pochini <pochini@shiny.it>

*************************************************************************/

अटल पूर्णांक set_sample_rate(काष्ठा echoaudio *chip, u32 rate)
अणु
	u32 घड़ी, control_reg, old_control_reg;

	अगर (रुको_handshake(chip))
		वापस -EIO;

	old_control_reg = le32_to_cpu(chip->comm_page->control_रेजिस्टर);
	control_reg = old_control_reg & ~INDIGO_EXPRESS_CLOCK_MASK;

	चयन (rate) अणु
	हाल 32000:
		घड़ी = INDIGO_EXPRESS_32000;
		अवरोध;
	हाल 44100:
		घड़ी = INDIGO_EXPRESS_44100;
		अवरोध;
	हाल 48000:
		घड़ी = INDIGO_EXPRESS_48000;
		अवरोध;
	हाल 64000:
		घड़ी = INDIGO_EXPRESS_32000|INDIGO_EXPRESS_DOUBLE_SPEED;
		अवरोध;
	हाल 88200:
		घड़ी = INDIGO_EXPRESS_44100|INDIGO_EXPRESS_DOUBLE_SPEED;
		अवरोध;
	हाल 96000:
		घड़ी = INDIGO_EXPRESS_48000|INDIGO_EXPRESS_DOUBLE_SPEED;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	control_reg |= घड़ी;
	अगर (control_reg != old_control_reg) अणु
		dev_dbg(chip->card->dev,
			"set_sample_rate: %d clock %d\n", rate, घड़ी);
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



अटल u32 detect_input_घड़ीs(स्थिर काष्ठा echoaudio *chip)
अणु
	वापस ECHO_CLOCK_BIT_INTERNAL;
पूर्ण



/* The IndigoIO has no ASIC. Just करो nothing */
अटल पूर्णांक load_asic(काष्ठा echoaudio *chip)
अणु
	वापस 0;
पूर्ण
