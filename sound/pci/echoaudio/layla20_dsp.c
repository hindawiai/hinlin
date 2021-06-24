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


अटल पूर्णांक पढ़ो_dsp(काष्ठा echoaudio *chip, u32 *data);
अटल पूर्णांक set_professional_spdअगर(काष्ठा echoaudio *chip, अक्षर prof);
अटल पूर्णांक load_asic_generic(काष्ठा echoaudio *chip, u32 cmd, लघु asic);
अटल पूर्णांक check_asic_status(काष्ठा echoaudio *chip);
अटल पूर्णांक update_flags(काष्ठा echoaudio *chip);


अटल पूर्णांक init_hw(काष्ठा echoaudio *chip, u16 device_id, u16 subdevice_id)
अणु
	पूर्णांक err;

	अगर (snd_BUG_ON((subdevice_id & 0xfff0) != LAYLA20))
		वापस -ENODEV;

	अगर ((err = init_dsp_comm_page(chip))) अणु
		dev_err(chip->card->dev,
			"init_hw - could not initialize DSP comm page\n");
		वापस err;
	पूर्ण

	chip->device_id = device_id;
	chip->subdevice_id = subdevice_id;
	chip->bad_board = true;
	chip->has_midi = true;
	chip->dsp_code_to_load = FW_LAYLA20_DSP;
	chip->input_घड़ी_प्रकारypes =
		ECHO_CLOCK_BIT_INTERNAL | ECHO_CLOCK_BIT_SPDIF |
		ECHO_CLOCK_BIT_WORD | ECHO_CLOCK_BIT_SUPER;
	chip->output_घड़ी_प्रकारypes =
		ECHO_CLOCK_BIT_WORD | ECHO_CLOCK_BIT_SUPER;

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

	/* Map the DSP घड़ी detect bits to the generic driver घड़ी detect bits */
	घड़ीs_from_dsp = le32_to_cpu(chip->comm_page->status_घड़ीs);

	घड़ी_bits = ECHO_CLOCK_BIT_INTERNAL;

	अगर (घड़ीs_from_dsp & GLDM_CLOCK_DETECT_BIT_SPDIF)
		घड़ी_bits |= ECHO_CLOCK_BIT_SPDIF;

	अगर (घड़ीs_from_dsp & GLDM_CLOCK_DETECT_BIT_WORD) अणु
		अगर (घड़ीs_from_dsp & GLDM_CLOCK_DETECT_BIT_SUPER)
			घड़ी_bits |= ECHO_CLOCK_BIT_SUPER;
		अन्यथा
			घड़ी_bits |= ECHO_CLOCK_BIT_WORD;
	पूर्ण

	वापस घड़ी_bits;
पूर्ण



/* ASIC status check - some cards have one or two ASICs that need to be
loaded.  Once that load is complete, this function is called to see अगर
the load was successful.
If this load fails, it करोes not necessarily mean that the hardware is
defective - the बाह्यal box may be disconnected or turned off.
This routine someबार fails क्रम Layla20; क्रम Layla20, the loop runs
5 बार and succeeds अगर it wins on three of the loops. */
अटल पूर्णांक check_asic_status(काष्ठा echoaudio *chip)
अणु
	u32 asic_status;
	पूर्णांक goodcnt, i;

	chip->asic_loaded = false;
	क्रम (i = goodcnt = 0; i < 5; i++) अणु
		send_vector(chip, DSP_VC_TEST_ASIC);

		/* The DSP will वापस a value to indicate whether or not
		   the ASIC is currently loaded */
		अगर (पढ़ो_dsp(chip, &asic_status) < 0) अणु
			dev_err(chip->card->dev,
				"check_asic_status: failed on read_dsp\n");
			वापस -EIO;
		पूर्ण

		अगर (asic_status == ASIC_ALREADY_LOADED) अणु
			अगर (++goodcnt == 3) अणु
				chip->asic_loaded = true;
				वापस 0;
			पूर्ण
		पूर्ण
	पूर्ण
	वापस -EIO;
पूर्ण



/* Layla20 has an ASIC in the बाह्यal box */
अटल पूर्णांक load_asic(काष्ठा echoaudio *chip)
अणु
	पूर्णांक err;

	अगर (chip->asic_loaded)
		वापस 0;

	err = load_asic_generic(chip, DSP_FNC_LOAD_LAYLA_ASIC,
				FW_LAYLA20_ASIC);
	अगर (err < 0)
		वापस err;

	/* Check अगर ASIC is alive and well. */
	वापस check_asic_status(chip);
पूर्ण



अटल पूर्णांक set_sample_rate(काष्ठा echoaudio *chip, u32 rate)
अणु
	अगर (snd_BUG_ON(rate < 8000 || rate > 50000))
		वापस -EINVAL;

	/* Only set the घड़ी क्रम पूर्णांकernal mode. Do not वापस failure,
	   simply treat it as a non-event. */
	अगर (chip->input_घड़ी != ECHO_CLOCK_INTERNAL) अणु
		dev_warn(chip->card->dev,
			 "Cannot set sample rate - clock not set to CLK_CLOCKININTERNAL\n");
		chip->comm_page->sample_rate = cpu_to_le32(rate);
		chip->sample_rate = rate;
		वापस 0;
	पूर्ण

	अगर (रुको_handshake(chip))
		वापस -EIO;

	dev_dbg(chip->card->dev, "set_sample_rate(%d)\n", rate);
	chip->sample_rate = rate;
	chip->comm_page->sample_rate = cpu_to_le32(rate);
	clear_handshake(chip);
	वापस send_vector(chip, DSP_VC_SET_LAYLA_SAMPLE_RATE);
पूर्ण



अटल पूर्णांक set_input_घड़ी(काष्ठा echoaudio *chip, u16 घड़ी_source)
अणु
	u16 घड़ी;
	u32 rate;

	rate = 0;
	चयन (घड़ी_source) अणु
	हाल ECHO_CLOCK_INTERNAL:
		rate = chip->sample_rate;
		घड़ी = LAYLA20_CLOCK_INTERNAL;
		अवरोध;
	हाल ECHO_CLOCK_SPDIF:
		घड़ी = LAYLA20_CLOCK_SPDIF;
		अवरोध;
	हाल ECHO_CLOCK_WORD:
		घड़ी = LAYLA20_CLOCK_WORD;
		अवरोध;
	हाल ECHO_CLOCK_SUPER:
		घड़ी = LAYLA20_CLOCK_SUPER;
		अवरोध;
	शेष:
		dev_err(chip->card->dev,
			"Input clock 0x%x not supported for Layla24\n",
			घड़ी_source);
		वापस -EINVAL;
	पूर्ण
	chip->input_घड़ी = घड़ी_source;

	chip->comm_page->input_घड़ी = cpu_to_le16(घड़ी);
	clear_handshake(chip);
	send_vector(chip, DSP_VC_UPDATE_CLOCKS);

	अगर (rate)
		set_sample_rate(chip, rate);

	वापस 0;
पूर्ण



अटल पूर्णांक set_output_घड़ी(काष्ठा echoaudio *chip, u16 घड़ी)
अणु
	चयन (घड़ी) अणु
	हाल ECHO_CLOCK_SUPER:
		घड़ी = LAYLA20_OUTPUT_CLOCK_SUPER;
		अवरोध;
	हाल ECHO_CLOCK_WORD:
		घड़ी = LAYLA20_OUTPUT_CLOCK_WORD;
		अवरोध;
	शेष:
		dev_err(chip->card->dev, "set_output_clock wrong clock\n");
		वापस -EINVAL;
	पूर्ण

	अगर (रुको_handshake(chip))
		वापस -EIO;

	chip->comm_page->output_घड़ी = cpu_to_le16(घड़ी);
	chip->output_घड़ी = घड़ी;
	clear_handshake(chip);
	वापस send_vector(chip, DSP_VC_UPDATE_CLOCKS);
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
