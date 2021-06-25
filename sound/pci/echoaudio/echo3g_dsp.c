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

अटल पूर्णांक load_asic(काष्ठा echoaudio *chip);
अटल पूर्णांक dsp_set_digital_mode(काष्ठा echoaudio *chip, u8 mode);
अटल पूर्णांक set_digital_mode(काष्ठा echoaudio *chip, u8 mode);
अटल पूर्णांक check_asic_status(काष्ठा echoaudio *chip);
अटल पूर्णांक set_sample_rate(काष्ठा echoaudio *chip, u32 rate);
अटल पूर्णांक set_input_घड़ी(काष्ठा echoaudio *chip, u16 घड़ी);
अटल पूर्णांक set_professional_spdअगर(काष्ठा echoaudio *chip, अक्षर prof);
अटल पूर्णांक set_phantom_घातer(काष्ठा echoaudio *chip, अक्षर on);
अटल पूर्णांक ग_लिखो_control_reg(काष्ठा echoaudio *chip, u32 ctl, u32 frq,
			     अक्षर क्रमce);

#समावेश <linux/पूर्णांकerrupt.h>

अटल पूर्णांक init_hw(काष्ठा echoaudio *chip, u16 device_id, u16 subdevice_id)
अणु
	पूर्णांक err;

	local_irq_enable();
	अगर (snd_BUG_ON((subdevice_id & 0xfff0) != ECHO3G))
		वापस -ENODEV;

	अगर ((err = init_dsp_comm_page(chip))) अणु
		dev_err(chip->card->dev,
			"init_hw - could not initialize DSP comm page\n");
		वापस err;
	पूर्ण

	chip->comm_page->e3g_frq_रेजिस्टर =
		cpu_to_le32((E3G_MAGIC_NUMBER / 48000) - 2);
	chip->device_id = device_id;
	chip->subdevice_id = subdevice_id;
	chip->bad_board = true;
	chip->has_midi = true;
	chip->dsp_code_to_load = FW_ECHO3G_DSP;

	/* Load the DSP code and the ASIC on the PCI card and get
	what type of बाह्यal box is attached */
	err = load_firmware(chip);

	अगर (err < 0) अणु
		वापस err;
	पूर्ण अन्यथा अगर (err == E3G_GINA3G_BOX_TYPE) अणु
		chip->input_घड़ी_प्रकारypes =	ECHO_CLOCK_BIT_INTERNAL |
						ECHO_CLOCK_BIT_SPDIF |
						ECHO_CLOCK_BIT_ADAT;
		chip->card_name = "Gina3G";
		chip->px_digital_out = chip->bx_digital_out = 6;
		chip->px_analog_in = chip->bx_analog_in = 14;
		chip->px_digital_in = chip->bx_digital_in = 16;
		chip->px_num = chip->bx_num = 24;
		chip->has_phantom_घातer = true;
		chip->hasnt_input_nominal_level = true;
	पूर्ण अन्यथा अगर (err == E3G_LAYLA3G_BOX_TYPE) अणु
		chip->input_घड़ी_प्रकारypes =	ECHO_CLOCK_BIT_INTERNAL |
						ECHO_CLOCK_BIT_SPDIF |
						ECHO_CLOCK_BIT_ADAT |
						ECHO_CLOCK_BIT_WORD;
		chip->card_name = "Layla3G";
		chip->px_digital_out = chip->bx_digital_out = 8;
		chip->px_analog_in = chip->bx_analog_in = 16;
		chip->px_digital_in = chip->bx_digital_in = 24;
		chip->px_num = chip->bx_num = 32;
	पूर्ण अन्यथा अणु
		वापस -ENODEV;
	पूर्ण

	chip->digital_modes =	ECHOCAPS_HAS_DIGITAL_MODE_SPDIF_RCA |
				ECHOCAPS_HAS_DIGITAL_MODE_SPDIF_OPTICAL |
				ECHOCAPS_HAS_DIGITAL_MODE_ADAT;

	वापस err;
पूर्ण



अटल पूर्णांक set_mixer_शेषs(काष्ठा echoaudio *chip)
अणु
	chip->digital_mode = DIGITAL_MODE_SPDIF_RCA;
	chip->professional_spdअगर = false;
	chip->non_audio_spdअगर = false;
	chip->bad_board = false;
	chip->phantom_घातer = false;
	वापस init_line_levels(chip);
पूर्ण



अटल पूर्णांक set_phantom_घातer(काष्ठा echoaudio *chip, अक्षर on)
अणु
	u32 control_reg = le32_to_cpu(chip->comm_page->control_रेजिस्टर);

	अगर (on)
		control_reg |= E3G_PHANTOM_POWER;
	अन्यथा
		control_reg &= ~E3G_PHANTOM_POWER;

	chip->phantom_घातer = on;
	वापस ग_लिखो_control_reg(chip, control_reg,
				 le32_to_cpu(chip->comm_page->e3g_frq_रेजिस्टर),
				 0);
पूर्ण
