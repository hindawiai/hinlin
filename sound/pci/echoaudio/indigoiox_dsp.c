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

अटल पूर्णांक update_vmixer_level(काष्ठा echoaudio *chip);
अटल पूर्णांक set_vmixer_gain(काष्ठा echoaudio *chip, u16 output,
			   u16 pipe, पूर्णांक gain);


अटल पूर्णांक init_hw(काष्ठा echoaudio *chip, u16 device_id, u16 subdevice_id)
अणु
	पूर्णांक err;

	अगर (snd_BUG_ON((subdevice_id & 0xfff0) != INDIGO_IOX))
		वापस -ENODEV;

	err = init_dsp_comm_page(chip);
	अगर (err < 0) अणु
		dev_err(chip->card->dev,
			"init_hw - could not initialize DSP comm page\n");
		वापस err;
	पूर्ण

	chip->device_id = device_id;
	chip->subdevice_id = subdevice_id;
	chip->bad_board = true;
	chip->dsp_code_to_load = FW_INDIGO_IOX_DSP;
	/* Since this card has no ASIC, mark it as loaded so everything
	   works OK */
	chip->asic_loaded = true;
	chip->input_घड़ी_प्रकारypes = ECHO_CLOCK_BIT_INTERNAL;

	err = load_firmware(chip);
	अगर (err < 0)
		वापस err;
	chip->bad_board = false;

	वापस err;
पूर्ण



अटल पूर्णांक set_mixer_शेषs(काष्ठा echoaudio *chip)
अणु
	वापस init_line_levels(chip);
पूर्ण
