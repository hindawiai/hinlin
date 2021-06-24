<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * card driver क्रम the Xonar DG/DGX
 *
 * Copyright (c) Clemens Ladisch <clemens@ladisch.de>
 * Copyright (c) Roman Volkov <v1ron@mail.ru>
 */

/*
 * Xonar DG/DGX
 * ------------
 *
 * CS4245 and CS4361 both will mute all outमाला_दो अगर any घड़ी ratio
 * is invalid.
 *
 * CMI8788:
 *
 *   SPI 0 -> CS4245
 *
 *   Playback:
 *   IतऑS 1 -> CS4245
 *   IतऑS 2 -> CS4361 (center/LFE)
 *   IतऑS 3 -> CS4361 (surround)
 *   IतऑS 4 -> CS4361 (front)
 *   Capture:
 *   IतऑS ADC 1 <- CS4245
 *
 *   GPIO 3 <- ?
 *   GPIO 4 <- headphone detect
 *   GPIO 5 -> enable ADC analog circuit क्रम the left channel
 *   GPIO 6 -> enable ADC analog circuit क्रम the right channel
 *   GPIO 7 -> चयन green rear output jack between CS4245 and the first
 *             channel of CS4361 (mechanical relay)
 *   GPIO 8 -> enable output to speakers
 *
 * CS4245:
 *
 *   input 0 <- mic
 *   input 1 <- aux
 *   input 2 <- front mic
 *   input 4 <- line
 *   DAC out -> headphones
 *   aux out -> front panel headphones
 */

#समावेश <linux/pci.h>
#समावेश <linux/delay.h>
#समावेश <sound/control.h>
#समावेश <sound/core.h>
#समावेश <sound/info.h>
#समावेश <sound/pcm.h>
#समावेश <sound/tlv.h>
#समावेश "oxygen.h"
#समावेश "xonar_dg.h"
#समावेश "cs4245.h"

पूर्णांक cs4245_ग_लिखो_spi(काष्ठा oxygen *chip, u8 reg)
अणु
	काष्ठा dg *data = chip->model_data;
	अचिन्हित पूर्णांक packet;

	packet = reg << 8;
	packet |= (CS4245_SPI_ADDRESS | CS4245_SPI_WRITE) << 16;
	packet |= data->cs4245_shaकरोw[reg];

	वापस oxygen_ग_लिखो_spi(chip, OXYGEN_SPI_TRIGGER |
				OXYGEN_SPI_DATA_LENGTH_3 |
				OXYGEN_SPI_CLOCK_1280 |
				(0 << OXYGEN_SPI_CODEC_SHIFT) |
				OXYGEN_SPI_CEN_LATCH_CLOCK_HI,
				packet);
पूर्ण

पूर्णांक cs4245_पढ़ो_spi(काष्ठा oxygen *chip, u8 addr)
अणु
	काष्ठा dg *data = chip->model_data;
	पूर्णांक ret;

	ret = oxygen_ग_लिखो_spi(chip, OXYGEN_SPI_TRIGGER |
		OXYGEN_SPI_DATA_LENGTH_2 |
		OXYGEN_SPI_CEN_LATCH_CLOCK_HI |
		OXYGEN_SPI_CLOCK_1280 | (0 << OXYGEN_SPI_CODEC_SHIFT),
		((CS4245_SPI_ADDRESS | CS4245_SPI_WRITE) << 8) | addr);
	अगर (ret < 0)
		वापस ret;

	ret = oxygen_ग_लिखो_spi(chip, OXYGEN_SPI_TRIGGER |
		OXYGEN_SPI_DATA_LENGTH_2 |
		OXYGEN_SPI_CEN_LATCH_CLOCK_HI |
		OXYGEN_SPI_CLOCK_1280 | (0 << OXYGEN_SPI_CODEC_SHIFT),
		(CS4245_SPI_ADDRESS | CS4245_SPI_READ) << 8);
	अगर (ret < 0)
		वापस ret;

	data->cs4245_shaकरोw[addr] = oxygen_पढ़ो8(chip, OXYGEN_SPI_DATA1);

	वापस 0;
पूर्ण

पूर्णांक cs4245_shaकरोw_control(काष्ठा oxygen *chip, क्रमागत cs4245_shaकरोw_operation op)
अणु
	काष्ठा dg *data = chip->model_data;
	अचिन्हित अक्षर addr;
	पूर्णांक ret;

	क्रम (addr = 1; addr < ARRAY_SIZE(data->cs4245_shaकरोw); addr++) अणु
		ret = (op == CS4245_SAVE_TO_SHADOW ?
			cs4245_पढ़ो_spi(chip, addr) :
			cs4245_ग_लिखो_spi(chip, addr));
		अगर (ret < 0)
			वापस ret;
	पूर्ण
	वापस 0;
पूर्ण

अटल व्योम cs4245_init(काष्ठा oxygen *chip)
अणु
	काष्ठा dg *data = chip->model_data;

	/* save the initial state: codec version, रेजिस्टरs */
	cs4245_shaकरोw_control(chip, CS4245_SAVE_TO_SHADOW);

	/*
	 * Power up the CODEC पूर्णांकernals, enable soft ramp & zero cross, work in
	 * async. mode, enable aux output from DAC. Invert DAC output as in the
	 * Winकरोws driver.
	 */
	data->cs4245_shaकरोw[CS4245_POWER_CTRL] = 0;
	data->cs4245_shaकरोw[CS4245_SIGNAL_SEL] =
		CS4245_A_OUT_SEL_DAC | CS4245_ASYNCH;
	data->cs4245_shaकरोw[CS4245_DAC_CTRL_1] =
		CS4245_DAC_FM_SINGLE | CS4245_DAC_DIF_LJUST;
	data->cs4245_shaकरोw[CS4245_DAC_CTRL_2] =
		CS4245_DAC_SOFT | CS4245_DAC_ZERO | CS4245_INVERT_DAC;
	data->cs4245_shaकरोw[CS4245_ADC_CTRL] =
		CS4245_ADC_FM_SINGLE | CS4245_ADC_DIF_LJUST;
	data->cs4245_shaकरोw[CS4245_ANALOG_IN] =
		CS4245_PGA_SOFT | CS4245_PGA_ZERO;
	data->cs4245_shaकरोw[CS4245_PGA_B_CTRL] = 0;
	data->cs4245_shaकरोw[CS4245_PGA_A_CTRL] = 0;
	data->cs4245_shaकरोw[CS4245_DAC_A_CTRL] = 8;
	data->cs4245_shaकरोw[CS4245_DAC_B_CTRL] = 8;

	cs4245_shaकरोw_control(chip, CS4245_LOAD_FROM_SHADOW);
	snd_component_add(chip->card, "CS4245");
पूर्ण

व्योम dg_init(काष्ठा oxygen *chip)
अणु
	काष्ठा dg *data = chip->model_data;

	data->output_sel = PLAYBACK_DST_HP_FP;
	data->input_sel = CAPTURE_SRC_MIC;

	cs4245_init(chip);
	oxygen_ग_लिखो16(chip, OXYGEN_GPIO_CONTROL,
		       GPIO_OUTPUT_ENABLE | GPIO_HP_REAR | GPIO_INPUT_ROUTE);
	/* anti-pop delay, रुको some समय beक्रमe enabling the output */
	msleep(2500);
	oxygen_ग_लिखो16(chip, OXYGEN_GPIO_DATA,
		       GPIO_OUTPUT_ENABLE | GPIO_INPUT_ROUTE);
पूर्ण

व्योम dg_cleanup(काष्ठा oxygen *chip)
अणु
	oxygen_clear_bits16(chip, OXYGEN_GPIO_DATA, GPIO_OUTPUT_ENABLE);
पूर्ण

व्योम dg_suspend(काष्ठा oxygen *chip)
अणु
	dg_cleanup(chip);
पूर्ण

व्योम dg_resume(काष्ठा oxygen *chip)
अणु
	cs4245_shaकरोw_control(chip, CS4245_LOAD_FROM_SHADOW);
	msleep(2500);
	oxygen_set_bits16(chip, OXYGEN_GPIO_DATA, GPIO_OUTPUT_ENABLE);
पूर्ण

व्योम set_cs4245_dac_params(काष्ठा oxygen *chip,
				  काष्ठा snd_pcm_hw_params *params)
अणु
	काष्ठा dg *data = chip->model_data;
	अचिन्हित अक्षर dac_ctrl;
	अचिन्हित अक्षर mclk_freq;

	dac_ctrl = data->cs4245_shaकरोw[CS4245_DAC_CTRL_1] & ~CS4245_DAC_FM_MASK;
	mclk_freq = data->cs4245_shaकरोw[CS4245_MCLK_FREQ] & ~CS4245_MCLK1_MASK;
	अगर (params_rate(params) <= 50000) अणु
		dac_ctrl |= CS4245_DAC_FM_SINGLE;
		mclk_freq |= CS4245_MCLK_1 << CS4245_MCLK1_SHIFT;
	पूर्ण अन्यथा अगर (params_rate(params) <= 100000) अणु
		dac_ctrl |= CS4245_DAC_FM_DOUBLE;
		mclk_freq |= CS4245_MCLK_1 << CS4245_MCLK1_SHIFT;
	पूर्ण अन्यथा अणु
		dac_ctrl |= CS4245_DAC_FM_QUAD;
		mclk_freq |= CS4245_MCLK_2 << CS4245_MCLK1_SHIFT;
	पूर्ण
	data->cs4245_shaकरोw[CS4245_DAC_CTRL_1] = dac_ctrl;
	data->cs4245_shaकरोw[CS4245_MCLK_FREQ] = mclk_freq;
	cs4245_ग_लिखो_spi(chip, CS4245_DAC_CTRL_1);
	cs4245_ग_लिखो_spi(chip, CS4245_MCLK_FREQ);
पूर्ण

व्योम set_cs4245_adc_params(काष्ठा oxygen *chip,
				  काष्ठा snd_pcm_hw_params *params)
अणु
	काष्ठा dg *data = chip->model_data;
	अचिन्हित अक्षर adc_ctrl;
	अचिन्हित अक्षर mclk_freq;

	adc_ctrl = data->cs4245_shaकरोw[CS4245_ADC_CTRL] & ~CS4245_ADC_FM_MASK;
	mclk_freq = data->cs4245_shaकरोw[CS4245_MCLK_FREQ] & ~CS4245_MCLK2_MASK;
	अगर (params_rate(params) <= 50000) अणु
		adc_ctrl |= CS4245_ADC_FM_SINGLE;
		mclk_freq |= CS4245_MCLK_1 << CS4245_MCLK2_SHIFT;
	पूर्ण अन्यथा अगर (params_rate(params) <= 100000) अणु
		adc_ctrl |= CS4245_ADC_FM_DOUBLE;
		mclk_freq |= CS4245_MCLK_1 << CS4245_MCLK2_SHIFT;
	पूर्ण अन्यथा अणु
		adc_ctrl |= CS4245_ADC_FM_QUAD;
		mclk_freq |= CS4245_MCLK_2 << CS4245_MCLK2_SHIFT;
	पूर्ण
	data->cs4245_shaकरोw[CS4245_ADC_CTRL] = adc_ctrl;
	data->cs4245_shaकरोw[CS4245_MCLK_FREQ] = mclk_freq;
	cs4245_ग_लिखो_spi(chip, CS4245_ADC_CTRL);
	cs4245_ग_लिखो_spi(chip, CS4245_MCLK_FREQ);
पूर्ण

अटल अंतरभूत अचिन्हित पूर्णांक shअगरt_bits(अचिन्हित पूर्णांक value,
				      अचिन्हित पूर्णांक shअगरt_from,
				      अचिन्हित पूर्णांक shअगरt_to,
				      अचिन्हित पूर्णांक mask)
अणु
	अगर (shअगरt_from < shअगरt_to)
		वापस (value << (shअगरt_to - shअगरt_from)) & mask;
	अन्यथा
		वापस (value >> (shअगरt_from - shअगरt_to)) & mask;
पूर्ण

अचिन्हित पूर्णांक adjust_dg_dac_routing(काष्ठा oxygen *chip,
					  अचिन्हित पूर्णांक play_routing)
अणु
	काष्ठा dg *data = chip->model_data;

	चयन (data->output_sel) अणु
	हाल PLAYBACK_DST_HP:
	हाल PLAYBACK_DST_HP_FP:
		oxygen_ग_लिखो8_masked(chip, OXYGEN_PLAY_ROUTING,
			OXYGEN_PLAY_MUTE23 | OXYGEN_PLAY_MUTE45 |
			OXYGEN_PLAY_MUTE67, OXYGEN_PLAY_MUTE_MASK);
		अवरोध;
	हाल PLAYBACK_DST_MULTICH:
		oxygen_ग_लिखो8_masked(chip, OXYGEN_PLAY_ROUTING,
			OXYGEN_PLAY_MUTE01, OXYGEN_PLAY_MUTE_MASK);
		अवरोध;
	पूर्ण
	वापस (play_routing & OXYGEN_PLAY_DAC0_SOURCE_MASK) |
	       shअगरt_bits(play_routing,
			  OXYGEN_PLAY_DAC2_SOURCE_SHIFT,
			  OXYGEN_PLAY_DAC1_SOURCE_SHIFT,
			  OXYGEN_PLAY_DAC1_SOURCE_MASK) |
	       shअगरt_bits(play_routing,
			  OXYGEN_PLAY_DAC1_SOURCE_SHIFT,
			  OXYGEN_PLAY_DAC2_SOURCE_SHIFT,
			  OXYGEN_PLAY_DAC2_SOURCE_MASK) |
	       shअगरt_bits(play_routing,
			  OXYGEN_PLAY_DAC0_SOURCE_SHIFT,
			  OXYGEN_PLAY_DAC3_SOURCE_SHIFT,
			  OXYGEN_PLAY_DAC3_SOURCE_MASK);
पूर्ण

व्योम dump_cs4245_रेजिस्टरs(काष्ठा oxygen *chip,
				  काष्ठा snd_info_buffer *buffer)
अणु
	काष्ठा dg *data = chip->model_data;
	अचिन्हित पूर्णांक addr;

	snd_iम_लिखो(buffer, "\nCS4245:");
	cs4245_पढ़ो_spi(chip, CS4245_INT_STATUS);
	क्रम (addr = 1; addr < ARRAY_SIZE(data->cs4245_shaकरोw); addr++)
		snd_iम_लिखो(buffer, " %02x", data->cs4245_shaकरोw[addr]);
	snd_iम_लिखो(buffer, "\n");
पूर्ण
