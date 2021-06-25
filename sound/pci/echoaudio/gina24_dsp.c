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


अटल पूर्णांक ग_लिखो_control_reg(काष्ठा echoaudio *chip, u32 value, अक्षर क्रमce);
अटल पूर्णांक set_input_घड़ी(काष्ठा echoaudio *chip, u16 घड़ी);
अटल पूर्णांक set_professional_spdअगर(काष्ठा echoaudio *chip, अक्षर prof);
अटल पूर्णांक set_digital_mode(काष्ठा echoaudio *chip, u8 mode);
अटल पूर्णांक load_asic_generic(काष्ठा echoaudio *chip, u32 cmd, लघु asic);
अटल पूर्णांक check_asic_status(काष्ठा echoaudio *chip);


अटल पूर्णांक init_hw(काष्ठा echoaudio *chip, u16 device_id, u16 subdevice_id)
अणु
	पूर्णांक err;

	अगर (snd_BUG_ON((subdevice_id & 0xfff0) != GINA24))
		वापस -ENODEV;

	अगर ((err = init_dsp_comm_page(chip))) अणु
		dev_err(chip->card->dev,
			"init_hw - could not initialize DSP comm page\n");
		वापस err;
	पूर्ण

	chip->device_id = device_id;
	chip->subdevice_id = subdevice_id;
	chip->bad_board = true;
	chip->input_घड़ी_प्रकारypes =
		ECHO_CLOCK_BIT_INTERNAL | ECHO_CLOCK_BIT_SPDIF |
		ECHO_CLOCK_BIT_ESYNC | ECHO_CLOCK_BIT_ESYNC96 |
		ECHO_CLOCK_BIT_ADAT;

	/* Gina24 comes in both '301 and '361 flavors */
	अगर (chip->device_id == DEVICE_ID_56361) अणु
		chip->dsp_code_to_load = FW_GINA24_361_DSP;
		chip->digital_modes =
			ECHOCAPS_HAS_DIGITAL_MODE_SPDIF_RCA |
			ECHOCAPS_HAS_DIGITAL_MODE_SPDIF_OPTICAL |
			ECHOCAPS_HAS_DIGITAL_MODE_ADAT;
	पूर्ण अन्यथा अणु
		chip->dsp_code_to_load = FW_GINA24_301_DSP;
		chip->digital_modes =
			ECHOCAPS_HAS_DIGITAL_MODE_SPDIF_RCA |
			ECHOCAPS_HAS_DIGITAL_MODE_SPDIF_OPTICAL |
			ECHOCAPS_HAS_DIGITAL_MODE_ADAT |
			ECHOCAPS_HAS_DIGITAL_MODE_SPDIF_CDROM;
	पूर्ण

	अगर ((err = load_firmware(chip)) < 0)
		वापस err;
	chip->bad_board = false;

	वापस err;
पूर्ण



अटल पूर्णांक set_mixer_शेषs(काष्ठा echoaudio *chip)
अणु
	chip->digital_mode = DIGITAL_MODE_SPDIF_RCA;
	chip->professional_spdअगर = false;
	chip->digital_in_स्वतःmute = true;
	वापस init_line_levels(chip);
पूर्ण



अटल u32 detect_input_घड़ीs(स्थिर काष्ठा echoaudio *chip)
अणु
	u32 घड़ीs_from_dsp, घड़ी_bits;

	/* Map the DSP घड़ी detect bits to the generic driver घड़ी
	   detect bits */
	घड़ीs_from_dsp = le32_to_cpu(chip->comm_page->status_घड़ीs);

	घड़ी_bits = ECHO_CLOCK_BIT_INTERNAL;

	अगर (घड़ीs_from_dsp & GML_CLOCK_DETECT_BIT_SPDIF)
		घड़ी_bits |= ECHO_CLOCK_BIT_SPDIF;

	अगर (घड़ीs_from_dsp & GML_CLOCK_DETECT_BIT_ADAT)
		घड़ी_bits |= ECHO_CLOCK_BIT_ADAT;

	अगर (घड़ीs_from_dsp & GML_CLOCK_DETECT_BIT_ESYNC)
		घड़ी_bits |= ECHO_CLOCK_BIT_ESYNC | ECHO_CLOCK_BIT_ESYNC96;

	वापस घड़ी_bits;
पूर्ण



/* Gina24 has an ASIC on the PCI card which must be loaded क्रम anything
पूर्णांकeresting to happen. */
अटल पूर्णांक load_asic(काष्ठा echoaudio *chip)
अणु
	u32 control_reg;
	पूर्णांक err;
	लघु asic;

	अगर (chip->asic_loaded)
		वापस 1;

	/* Give the DSP a few milliseconds to settle करोwn */
	mdelay(10);

	/* Pick the correct ASIC क्रम '301 or '361 Gina24 */
	अगर (chip->device_id == DEVICE_ID_56361)
		asic = FW_GINA24_361_ASIC;
	अन्यथा
		asic = FW_GINA24_301_ASIC;

	err = load_asic_generic(chip, DSP_FNC_LOAD_GINA24_ASIC, asic);
	अगर (err < 0)
		वापस err;

	chip->asic_code = asic;

	/* Now give the new ASIC a little समय to set up */
	mdelay(10);
	/* See अगर it worked */
	err = check_asic_status(chip);

	/* Set up the control रेजिस्टर अगर the load succeeded -
	   48 kHz, पूर्णांकernal घड़ी, S/PDIF RCA mode */
	अगर (!err) अणु
		control_reg = GML_CONVERTER_ENABLE | GML_48KHZ;
		err = ग_लिखो_control_reg(chip, control_reg, true);
	पूर्ण
	वापस err;
पूर्ण



अटल पूर्णांक set_sample_rate(काष्ठा echoaudio *chip, u32 rate)
अणु
	u32 control_reg, घड़ी;

	अगर (snd_BUG_ON(rate >= 50000 &&
		       chip->digital_mode == DIGITAL_MODE_ADAT))
		वापस -EINVAL;

	/* Only set the घड़ी क्रम पूर्णांकernal mode. */
	अगर (chip->input_घड़ी != ECHO_CLOCK_INTERNAL) अणु
		dev_warn(chip->card->dev,
			 "Cannot set sample rate - clock not set to CLK_CLOCKININTERNAL\n");
		/* Save the rate anyhow */
		chip->comm_page->sample_rate = cpu_to_le32(rate);
		chip->sample_rate = rate;
		वापस 0;
	पूर्ण

	घड़ी = 0;

	control_reg = le32_to_cpu(chip->comm_page->control_रेजिस्टर);
	control_reg &= GML_CLOCK_CLEAR_MASK & GML_SPDIF_RATE_CLEAR_MASK;

	चयन (rate) अणु
	हाल 96000:
		घड़ी = GML_96KHZ;
		अवरोध;
	हाल 88200:
		घड़ी = GML_88KHZ;
		अवरोध;
	हाल 48000:
		घड़ी = GML_48KHZ | GML_SPDIF_SAMPLE_RATE1;
		अवरोध;
	हाल 44100:
		घड़ी = GML_44KHZ;
		/* Professional mode ? */
		अगर (control_reg & GML_SPDIF_PRO_MODE)
			घड़ी |= GML_SPDIF_SAMPLE_RATE0;
		अवरोध;
	हाल 32000:
		घड़ी = GML_32KHZ | GML_SPDIF_SAMPLE_RATE0 |
			GML_SPDIF_SAMPLE_RATE1;
		अवरोध;
	हाल 22050:
		घड़ी = GML_22KHZ;
		अवरोध;
	हाल 16000:
		घड़ी = GML_16KHZ;
		अवरोध;
	हाल 11025:
		घड़ी = GML_11KHZ;
		अवरोध;
	हाल 8000:
		घड़ी = GML_8KHZ;
		अवरोध;
	शेष:
		dev_err(chip->card->dev,
			"set_sample_rate: %d invalid!\n", rate);
		वापस -EINVAL;
	पूर्ण

	control_reg |= घड़ी;

	chip->comm_page->sample_rate = cpu_to_le32(rate);	/* ignored by the DSP */
	chip->sample_rate = rate;
	dev_dbg(chip->card->dev, "set_sample_rate: %d clock %d\n", rate, घड़ी);

	वापस ग_लिखो_control_reg(chip, control_reg, false);
पूर्ण



अटल पूर्णांक set_input_घड़ी(काष्ठा echoaudio *chip, u16 घड़ी)
अणु
	u32 control_reg, घड़ीs_from_dsp;


	/* Mask off the घड़ी select bits */
	control_reg = le32_to_cpu(chip->comm_page->control_रेजिस्टर) &
		GML_CLOCK_CLEAR_MASK;
	घड़ीs_from_dsp = le32_to_cpu(chip->comm_page->status_घड़ीs);

	चयन (घड़ी) अणु
	हाल ECHO_CLOCK_INTERNAL:
		chip->input_घड़ी = ECHO_CLOCK_INTERNAL;
		वापस set_sample_rate(chip, chip->sample_rate);
	हाल ECHO_CLOCK_SPDIF:
		अगर (chip->digital_mode == DIGITAL_MODE_ADAT)
			वापस -EAGAIN;
		control_reg |= GML_SPDIF_CLOCK;
		अगर (घड़ीs_from_dsp & GML_CLOCK_DETECT_BIT_SPDIF96)
			control_reg |= GML_DOUBLE_SPEED_MODE;
		अन्यथा
			control_reg &= ~GML_DOUBLE_SPEED_MODE;
		अवरोध;
	हाल ECHO_CLOCK_ADAT:
		अगर (chip->digital_mode != DIGITAL_MODE_ADAT)
			वापस -EAGAIN;
		control_reg |= GML_ADAT_CLOCK;
		control_reg &= ~GML_DOUBLE_SPEED_MODE;
		अवरोध;
	हाल ECHO_CLOCK_ESYNC:
		control_reg |= GML_ESYNC_CLOCK;
		control_reg &= ~GML_DOUBLE_SPEED_MODE;
		अवरोध;
	हाल ECHO_CLOCK_ESYNC96:
		control_reg |= GML_ESYNC_CLOCK | GML_DOUBLE_SPEED_MODE;
		अवरोध;
	शेष:
		dev_err(chip->card->dev,
			"Input clock 0x%x not supported for Gina24\n", घड़ी);
		वापस -EINVAL;
	पूर्ण

	chip->input_घड़ी = घड़ी;
	वापस ग_लिखो_control_reg(chip, control_reg, true);
पूर्ण



अटल पूर्णांक dsp_set_digital_mode(काष्ठा echoaudio *chip, u8 mode)
अणु
	u32 control_reg;
	पूर्णांक err, incompatible_घड़ी;

	/* Set घड़ी to "internal" अगर it's not compatible with the new mode */
	incompatible_घड़ी = false;
	चयन (mode) अणु
	हाल DIGITAL_MODE_SPDIF_OPTICAL:
	हाल DIGITAL_MODE_SPDIF_CDROM:
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

	अगर (incompatible_घड़ी) अणु	/* Switch to 48KHz, पूर्णांकernal */
		chip->sample_rate = 48000;
		set_input_घड़ी(chip, ECHO_CLOCK_INTERNAL);
	पूर्ण

	/* Clear the current digital mode */
	control_reg = le32_to_cpu(chip->comm_page->control_रेजिस्टर);
	control_reg &= GML_DIGITAL_MODE_CLEAR_MASK;

	/* Tweak the control reg */
	चयन (mode) अणु
	हाल DIGITAL_MODE_SPDIF_OPTICAL:
		control_reg |= GML_SPDIF_OPTICAL_MODE;
		अवरोध;
	हाल DIGITAL_MODE_SPDIF_CDROM:
		/* '361 Gina24 cards करो not have the S/PDIF CD-ROM mode */
		अगर (chip->device_id == DEVICE_ID_56301)
			control_reg |= GML_SPDIF_CDROM_MODE;
		अवरोध;
	हाल DIGITAL_MODE_SPDIF_RCA:
		/* GML_SPDIF_OPTICAL_MODE bit cleared */
		अवरोध;
	हाल DIGITAL_MODE_ADAT:
		control_reg |= GML_ADAT_MODE;
		control_reg &= ~GML_DOUBLE_SPEED_MODE;
		अवरोध;
	पूर्ण

	err = ग_लिखो_control_reg(chip, control_reg, true);
	spin_unlock_irq(&chip->lock);
	अगर (err < 0)
		वापस err;
	chip->digital_mode = mode;

	dev_dbg(chip->card->dev,
		"set_digital_mode to %d\n", chip->digital_mode);
	वापस incompatible_घड़ी;
पूर्ण
