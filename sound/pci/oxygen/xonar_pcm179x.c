<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * card driver क्रम models with PCM1796 DACs (Xonar D2/D2X/HDAV1.3/ST/STX)
 *
 * Copyright (c) Clemens Ladisch <clemens@ladisch.de>
 */

/*
 * Xonar D2/D2X
 * ------------
 *
 * CMI8788:
 *
 *   SPI 0 -> 1st PCM1796 (front)
 *   SPI 1 -> 2nd PCM1796 (surround)
 *   SPI 2 -> 3rd PCM1796 (center/LFE)
 *   SPI 4 -> 4th PCM1796 (back)
 *
 *   GPIO 2 -> M0 of CS5381
 *   GPIO 3 -> M1 of CS5381
 *   GPIO 5 <- बाह्यal घातer present (D2X only)
 *   GPIO 7 -> ALT
 *   GPIO 8 -> enable output to speakers
 *
 * CM9780:
 *
 *   LINE_OUT -> input of ADC
 *
 *   AUX_IN   <- aux
 *   VIDEO_IN <- CD
 *   FMIC_IN  <- mic
 *
 *   GPO 0 -> route line-in (0) or AC97 output (1) to CS5381 input
 */

/*
 * Xonar HDAV1.3 (Deluxe)
 * ----------------------
 *
 * CMI8788:
 *
 *   IतऑC <-> PCM1796 (addr 1001100) (front)
 *
 *   GPI 0 <- बाह्यal घातer present
 *
 *   GPIO 0 -> enable HDMI (0) or speaker (1) output
 *   GPIO 2 -> M0 of CS5381
 *   GPIO 3 -> M1 of CS5381
 *   GPIO 4 <- daughterboard detection
 *   GPIO 5 <- daughterboard detection
 *   GPIO 6 -> ?
 *   GPIO 7 -> ?
 *   GPIO 8 -> route input jack to line-in (0) or mic-in (1)
 *
 *   UART <-> HDMI controller
 *
 * CM9780:
 *
 *   LINE_OUT -> input of ADC
 *
 *   AUX_IN <- aux
 *   CD_IN  <- CD
 *   MIC_IN <- mic
 *
 *   GPO 0 -> route line-in (0) or AC97 output (1) to CS5381 input
 *
 * no daughterboard
 * ----------------
 *
 *   GPIO 4 <- 1
 *
 * H6 daughterboard
 * ----------------
 *
 *   GPIO 4 <- 0
 *   GPIO 5 <- 0
 *
 *   IतऑC <-> PCM1796 (addr 1001101) (surround)
 *       <-> PCM1796 (addr 1001110) (center/LFE)
 *       <-> PCM1796 (addr 1001111) (back)
 *
 * unknown daughterboard
 * ---------------------
 *
 *   GPIO 4 <- 0
 *   GPIO 5 <- 1
 *
 *   IतऑC <-> CS4362A (addr 0011000) (surround, center/LFE, back)
 */

/*
 * Xonar Essence ST (Deluxe)/STX (II)
 * ----------------------------------
 *
 * CMI8788:
 *
 *   IतऑC <-> PCM1792A (addr 1001100)
 *       <-> CS2000 (addr 1001110) (ST only)
 *
 *   ADC1 MCLK -> REF_CLK of CS2000 (ST only)
 *
 *   GPI 0 <- बाह्यal घातer present (STX only)
 *
 *   GPIO 0 -> enable output to speakers
 *   GPIO 1 -> route HP to front panel (0) or rear jack (1)
 *   GPIO 2 -> M0 of CS5381
 *   GPIO 3 -> M1 of CS5381
 *   GPIO 4 <- daughterboard detection
 *   GPIO 5 <- daughterboard detection
 *   GPIO 6 -> ?
 *   GPIO 7 -> route output to speaker jacks (0) or HP (1)
 *   GPIO 8 -> route input jack to line-in (0) or mic-in (1)
 *
 * PCM1792A:
 *
 *   SCK <- CLK_OUT of CS2000 (ST only)
 *
 * CM9780:
 *
 *   LINE_OUT -> input of ADC
 *
 *   AUX_IN <- aux
 *   MIC_IN <- mic
 *
 *   GPO 0 -> route line-in (0) or AC97 output (1) to CS5381 input
 *
 * H6 daughterboard
 * ----------------
 *
 * GPIO 4 <- 0
 * GPIO 5 <- 0
 */

/*
 * Xonar Xense
 * -----------
 *
 * CMI8788:
 *
 *   IतऑC <-> PCM1796 (addr 1001100) (front)
 *       <-> CS4362A (addr 0011000) (surround, center/LFE, back)
 *       <-> CS2000 (addr 1001110)
 *
 *   ADC1 MCLK -> REF_CLK of CS2000
 *
 *   GPI 0 <- बाह्यal घातer present
 *
 *   GPIO 0 -> enable output
 *   GPIO 1 -> route HP to front panel (0) or rear jack (1)
 *   GPIO 2 -> M0 of CS5381
 *   GPIO 3 -> M1 of CS5381
 *   GPIO 4 -> enable output
 *   GPIO 5 -> enable output
 *   GPIO 6 -> ?
 *   GPIO 7 -> route output to HP (0) or speaker (1)
 *   GPIO 8 -> route input jack to mic-in (0) or line-in (1)
 *
 * CM9780:
 *
 *   LINE_OUT -> input of ADC
 *
 *   AUX_IN   <- aux
 *   VIDEO_IN <- ?
 *   FMIC_IN  <- mic
 *
 *   GPO 0 -> route line-in (0) or AC97 output (1) to CS5381 input
 *   GPO 1 -> route mic-in from input jack (0) or front panel header (1)
 */

#समावेश <linux/pci.h>
#समावेश <linux/delay.h>
#समावेश <linux/mutex.h>
#समावेश <sound/ac97_codec.h>
#समावेश <sound/control.h>
#समावेश <sound/core.h>
#समावेश <sound/info.h>
#समावेश <sound/pcm.h>
#समावेश <sound/pcm_params.h>
#समावेश <sound/tlv.h>
#समावेश "xonar.h"
#समावेश "cm9780.h"
#समावेश "pcm1796.h"
#समावेश "cs2000.h"


#घोषणा GPIO_D2X_EXT_POWER	0x0020
#घोषणा GPIO_D2_ALT		0x0080
#घोषणा GPIO_D2_OUTPUT_ENABLE	0x0100

#घोषणा GPI_EXT_POWER		0x01
#घोषणा GPIO_INPUT_ROUTE	0x0100

#घोषणा GPIO_HDAV_OUTPUT_ENABLE	0x0001
#घोषणा GPIO_HDAV_MAGIC		0x00c0

#घोषणा GPIO_DB_MASK		0x0030
#घोषणा GPIO_DB_H6		0x0000

#घोषणा GPIO_ST_OUTPUT_ENABLE	0x0001
#घोषणा GPIO_ST_HP_REAR		0x0002
#घोषणा GPIO_ST_MAGIC		0x0040
#घोषणा GPIO_ST_HP		0x0080

#घोषणा GPIO_XENSE_OUTPUT_ENABLE	(0x0001 | 0x0010 | 0x0020)
#घोषणा GPIO_XENSE_SPEAKERS		0x0080

#घोषणा I2C_DEVICE_PCM1796(i)	(0x98 + ((i) << 1))	/* 10011, ii, /W=0 */
#घोषणा I2C_DEVICE_CS2000	0x9c			/* 100111, 0, /W=0 */

#घोषणा PCM1796_REG_BASE	16


काष्ठा xonar_pcm179x अणु
	काष्ठा xonar_generic generic;
	अचिन्हित पूर्णांक dacs;
	u8 pcm1796_regs[4][5];
	अचिन्हित पूर्णांक current_rate;
	bool h6;
	bool hp_active;
	s8 hp_gain_offset;
	bool has_cs2000;
	u8 cs2000_regs[0x1f];
	bool broken_i2c;
पूर्ण;

काष्ठा xonar_hdav अणु
	काष्ठा xonar_pcm179x pcm179x;
	काष्ठा xonar_hdmi hdmi;
पूर्ण;


अटल अंतरभूत व्योम pcm1796_ग_लिखो_spi(काष्ठा oxygen *chip, अचिन्हित पूर्णांक codec,
				     u8 reg, u8 value)
अणु
	/* maps ALSA channel pair number to SPI output */
	अटल स्थिर u8 codec_map[4] = अणु
		0, 1, 2, 4
	पूर्ण;
	oxygen_ग_लिखो_spi(chip, OXYGEN_SPI_TRIGGER  |
			 OXYGEN_SPI_DATA_LENGTH_2 |
			 OXYGEN_SPI_CLOCK_160 |
			 (codec_map[codec] << OXYGEN_SPI_CODEC_SHIFT) |
			 OXYGEN_SPI_CEN_LATCH_CLOCK_HI,
			 (reg << 8) | value);
पूर्ण

अटल अंतरभूत व्योम pcm1796_ग_लिखो_i2c(काष्ठा oxygen *chip, अचिन्हित पूर्णांक codec,
				     u8 reg, u8 value)
अणु
	oxygen_ग_लिखो_i2c(chip, I2C_DEVICE_PCM1796(codec), reg, value);
पूर्ण

अटल व्योम pcm1796_ग_लिखो(काष्ठा oxygen *chip, अचिन्हित पूर्णांक codec,
			  u8 reg, u8 value)
अणु
	काष्ठा xonar_pcm179x *data = chip->model_data;

	अगर ((chip->model.function_flags & OXYGEN_FUNCTION_2WIRE_SPI_MASK) ==
	    OXYGEN_FUNCTION_SPI)
		pcm1796_ग_लिखो_spi(chip, codec, reg, value);
	अन्यथा
		pcm1796_ग_लिखो_i2c(chip, codec, reg, value);
	अगर ((अचिन्हित पूर्णांक)(reg - PCM1796_REG_BASE)
	    < ARRAY_SIZE(data->pcm1796_regs[codec]))
		data->pcm1796_regs[codec][reg - PCM1796_REG_BASE] = value;
पूर्ण

अटल व्योम pcm1796_ग_लिखो_cached(काष्ठा oxygen *chip, अचिन्हित पूर्णांक codec,
				 u8 reg, u8 value)
अणु
	काष्ठा xonar_pcm179x *data = chip->model_data;

	अगर (value != data->pcm1796_regs[codec][reg - PCM1796_REG_BASE])
		pcm1796_ग_लिखो(chip, codec, reg, value);
पूर्ण

अटल व्योम cs2000_ग_लिखो(काष्ठा oxygen *chip, u8 reg, u8 value)
अणु
	काष्ठा xonar_pcm179x *data = chip->model_data;

	oxygen_ग_लिखो_i2c(chip, I2C_DEVICE_CS2000, reg, value);
	data->cs2000_regs[reg] = value;
पूर्ण

अटल व्योम cs2000_ग_लिखो_cached(काष्ठा oxygen *chip, u8 reg, u8 value)
अणु
	काष्ठा xonar_pcm179x *data = chip->model_data;

	अगर (value != data->cs2000_regs[reg])
		cs2000_ग_लिखो(chip, reg, value);
पूर्ण

अटल व्योम pcm1796_रेजिस्टरs_init(काष्ठा oxygen *chip)
अणु
	काष्ठा xonar_pcm179x *data = chip->model_data;
	अचिन्हित पूर्णांक i;
	s8 gain_offset;

	msleep(1);
	gain_offset = data->hp_active ? data->hp_gain_offset : 0;
	क्रम (i = 0; i < data->dacs; ++i) अणु
		/* set ATLD beक्रमe ATL/ATR */
		pcm1796_ग_लिखो(chip, i, 18,
			      data->pcm1796_regs[0][18 - PCM1796_REG_BASE]);
		pcm1796_ग_लिखो(chip, i, 16, chip->dac_volume[i * 2]
			      + gain_offset);
		pcm1796_ग_लिखो(chip, i, 17, chip->dac_volume[i * 2 + 1]
			      + gain_offset);
		pcm1796_ग_लिखो(chip, i, 19,
			      data->pcm1796_regs[0][19 - PCM1796_REG_BASE]);
		pcm1796_ग_लिखो(chip, i, 20,
			      data->pcm1796_regs[0][20 - PCM1796_REG_BASE]);
		pcm1796_ग_लिखो(chip, i, 21, 0);
		gain_offset = 0;
	पूर्ण
पूर्ण

अटल व्योम pcm1796_init(काष्ठा oxygen *chip)
अणु
	काष्ठा xonar_pcm179x *data = chip->model_data;

	data->pcm1796_regs[0][18 - PCM1796_REG_BASE] =
		PCM1796_FMT_24_I2S | PCM1796_ATLD;
	अगर (!data->broken_i2c)
		data->pcm1796_regs[0][18 - PCM1796_REG_BASE] |= PCM1796_MUTE;
	data->pcm1796_regs[0][19 - PCM1796_REG_BASE] =
		PCM1796_FLT_SHARP | PCM1796_ATS_1;
	data->pcm1796_regs[0][20 - PCM1796_REG_BASE] =
		data->h6 ? PCM1796_OS_64 : PCM1796_OS_128;
	pcm1796_रेजिस्टरs_init(chip);
	data->current_rate = 48000;
पूर्ण

अटल व्योम xonar_d2_init(काष्ठा oxygen *chip)
अणु
	काष्ठा xonar_pcm179x *data = chip->model_data;

	data->generic.anti_pop_delay = 300;
	data->generic.output_enable_bit = GPIO_D2_OUTPUT_ENABLE;
	data->dacs = 4;

	pcm1796_init(chip);

	oxygen_set_bits16(chip, OXYGEN_GPIO_CONTROL, GPIO_D2_ALT);
	oxygen_clear_bits16(chip, OXYGEN_GPIO_DATA, GPIO_D2_ALT);

	oxygen_ac97_set_bits(chip, 0, CM9780_JACK, CM9780_FMIC2MIC);

	xonar_init_cs53x1(chip);
	xonar_enable_output(chip);

	snd_component_add(chip->card, "PCM1796");
	snd_component_add(chip->card, "CS5381");
पूर्ण

अटल व्योम xonar_d2x_init(काष्ठा oxygen *chip)
अणु
	काष्ठा xonar_pcm179x *data = chip->model_data;

	data->generic.ext_घातer_reg = OXYGEN_GPIO_DATA;
	data->generic.ext_घातer_पूर्णांक_reg = OXYGEN_GPIO_INTERRUPT_MASK;
	data->generic.ext_घातer_bit = GPIO_D2X_EXT_POWER;
	oxygen_clear_bits16(chip, OXYGEN_GPIO_CONTROL, GPIO_D2X_EXT_POWER);
	xonar_init_ext_घातer(chip);
	xonar_d2_init(chip);
पूर्ण

अटल व्योम xonar_hdav_init(काष्ठा oxygen *chip)
अणु
	काष्ठा xonar_hdav *data = chip->model_data;

	oxygen_ग_लिखो16(chip, OXYGEN_2WIRE_BUS_STATUS,
		       OXYGEN_2WIRE_LENGTH_8 |
		       OXYGEN_2WIRE_INTERRUPT_MASK |
		       OXYGEN_2WIRE_SPEED_STANDARD);

	data->pcm179x.generic.anti_pop_delay = 100;
	data->pcm179x.generic.output_enable_bit = GPIO_HDAV_OUTPUT_ENABLE;
	data->pcm179x.generic.ext_घातer_reg = OXYGEN_GPI_DATA;
	data->pcm179x.generic.ext_घातer_पूर्णांक_reg = OXYGEN_GPI_INTERRUPT_MASK;
	data->pcm179x.generic.ext_घातer_bit = GPI_EXT_POWER;
	data->pcm179x.dacs = chip->model.dac_channels_mixer / 2;
	data->pcm179x.h6 = chip->model.dac_channels_mixer > 2;

	pcm1796_init(chip);

	oxygen_set_bits16(chip, OXYGEN_GPIO_CONTROL,
			  GPIO_HDAV_MAGIC | GPIO_INPUT_ROUTE);
	oxygen_clear_bits16(chip, OXYGEN_GPIO_DATA, GPIO_INPUT_ROUTE);

	xonar_init_cs53x1(chip);
	xonar_init_ext_घातer(chip);
	xonar_hdmi_init(chip, &data->hdmi);
	xonar_enable_output(chip);

	snd_component_add(chip->card, "PCM1796");
	snd_component_add(chip->card, "CS5381");
पूर्ण

अटल व्योम xonar_st_init_i2c(काष्ठा oxygen *chip)
अणु
	oxygen_ग_लिखो16(chip, OXYGEN_2WIRE_BUS_STATUS,
		       OXYGEN_2WIRE_LENGTH_8 |
		       OXYGEN_2WIRE_INTERRUPT_MASK |
		       OXYGEN_2WIRE_SPEED_STANDARD);
पूर्ण

अटल व्योम xonar_st_init_common(काष्ठा oxygen *chip)
अणु
	काष्ठा xonar_pcm179x *data = chip->model_data;

	data->generic.output_enable_bit = GPIO_ST_OUTPUT_ENABLE;
	data->dacs = chip->model.dac_channels_mixer / 2;
	data->h6 = chip->model.dac_channels_mixer > 2;
	data->hp_gain_offset = 2*-18;

	pcm1796_init(chip);

	oxygen_set_bits16(chip, OXYGEN_GPIO_CONTROL,
			  GPIO_INPUT_ROUTE | GPIO_ST_HP_REAR |
			  GPIO_ST_MAGIC | GPIO_ST_HP);
	oxygen_clear_bits16(chip, OXYGEN_GPIO_DATA,
			    GPIO_INPUT_ROUTE | GPIO_ST_HP_REAR | GPIO_ST_HP);

	xonar_init_cs53x1(chip);
	xonar_enable_output(chip);

	snd_component_add(chip->card, "PCM1792A");
	snd_component_add(chip->card, "CS5381");
पूर्ण

अटल व्योम cs2000_रेजिस्टरs_init(काष्ठा oxygen *chip)
अणु
	काष्ठा xonar_pcm179x *data = chip->model_data;

	cs2000_ग_लिखो(chip, CS2000_GLOBAL_CFG, CS2000_FREEZE);
	cs2000_ग_लिखो(chip, CS2000_DEV_CTRL, 0);
	cs2000_ग_लिखो(chip, CS2000_DEV_CFG_1,
		     CS2000_R_MOD_SEL_1 |
		     (0 << CS2000_R_SEL_SHIFT) |
		     CS2000_AUX_OUT_SRC_REF_CLK |
		     CS2000_EN_DEV_CFG_1);
	cs2000_ग_लिखो(chip, CS2000_DEV_CFG_2,
		     (0 << CS2000_LOCK_CLK_SHIFT) |
		     CS2000_FRAC_N_SRC_STATIC);
	cs2000_ग_लिखो(chip, CS2000_RATIO_0 + 0, 0x00); /* 1.0 */
	cs2000_ग_लिखो(chip, CS2000_RATIO_0 + 1, 0x10);
	cs2000_ग_लिखो(chip, CS2000_RATIO_0 + 2, 0x00);
	cs2000_ग_लिखो(chip, CS2000_RATIO_0 + 3, 0x00);
	cs2000_ग_लिखो(chip, CS2000_FUN_CFG_1,
		     data->cs2000_regs[CS2000_FUN_CFG_1]);
	cs2000_ग_लिखो(chip, CS2000_FUN_CFG_2, 0);
	cs2000_ग_लिखो(chip, CS2000_GLOBAL_CFG, CS2000_EN_DEV_CFG_2);
	msleep(3); /* PLL lock delay */
पूर्ण

अटल व्योम xonar_st_init(काष्ठा oxygen *chip)
अणु
	काष्ठा xonar_pcm179x *data = chip->model_data;

	data->generic.anti_pop_delay = 100;
	data->h6 = chip->model.dac_channels_mixer > 2;
	data->has_cs2000 = true;
	data->cs2000_regs[CS2000_FUN_CFG_1] = CS2000_REF_CLK_DIV_1;
	data->broken_i2c = true;

	oxygen_ग_लिखो16(chip, OXYGEN_I2S_A_FORMAT,
		       OXYGEN_RATE_48000 |
		       OXYGEN_I2S_FORMAT_I2S |
		       OXYGEN_I2S_MCLK(data->h6 ? MCLK_256 : MCLK_512) |
		       OXYGEN_I2S_BITS_16 |
		       OXYGEN_I2S_MASTER |
		       OXYGEN_I2S_BCLK_64);

	xonar_st_init_i2c(chip);
	cs2000_रेजिस्टरs_init(chip);
	xonar_st_init_common(chip);

	snd_component_add(chip->card, "CS2000");
पूर्ण

अटल व्योम xonar_stx_init(काष्ठा oxygen *chip)
अणु
	काष्ठा xonar_pcm179x *data = chip->model_data;

	xonar_st_init_i2c(chip);
	data->generic.anti_pop_delay = 800;
	data->generic.ext_घातer_reg = OXYGEN_GPI_DATA;
	data->generic.ext_घातer_पूर्णांक_reg = OXYGEN_GPI_INTERRUPT_MASK;
	data->generic.ext_घातer_bit = GPI_EXT_POWER;
	xonar_init_ext_घातer(chip);
	xonar_st_init_common(chip);
पूर्ण

अटल व्योम xonar_xense_init(काष्ठा oxygen *chip)
अणु
	काष्ठा xonar_pcm179x *data = chip->model_data;

	data->generic.ext_घातer_reg = OXYGEN_GPI_DATA;
	data->generic.ext_घातer_पूर्णांक_reg = OXYGEN_GPI_INTERRUPT_MASK;
	data->generic.ext_घातer_bit = GPI_EXT_POWER;
	xonar_init_ext_घातer(chip);

	data->generic.anti_pop_delay = 100;
	data->has_cs2000 = true;
	data->cs2000_regs[CS2000_FUN_CFG_1] = CS2000_REF_CLK_DIV_1;

	oxygen_ग_लिखो16(chip, OXYGEN_I2S_A_FORMAT,
		OXYGEN_RATE_48000 |
		OXYGEN_I2S_FORMAT_I2S |
		OXYGEN_I2S_MCLK(MCLK_512) |
		OXYGEN_I2S_BITS_16 |
		OXYGEN_I2S_MASTER |
		OXYGEN_I2S_BCLK_64);

	xonar_st_init_i2c(chip);
	cs2000_रेजिस्टरs_init(chip);

	data->generic.output_enable_bit = GPIO_XENSE_OUTPUT_ENABLE;
	data->dacs = 1;
	data->hp_gain_offset = 2*-18;

	pcm1796_init(chip);

	oxygen_set_bits16(chip, OXYGEN_GPIO_CONTROL,
		GPIO_INPUT_ROUTE | GPIO_ST_HP_REAR |
		GPIO_ST_MAGIC | GPIO_XENSE_SPEAKERS);
	oxygen_clear_bits16(chip, OXYGEN_GPIO_DATA,
		GPIO_INPUT_ROUTE | GPIO_ST_HP_REAR |
		GPIO_XENSE_SPEAKERS);

	xonar_init_cs53x1(chip);
	xonar_enable_output(chip);

	snd_component_add(chip->card, "PCM1796");
	snd_component_add(chip->card, "CS5381");
	snd_component_add(chip->card, "CS2000");
पूर्ण

अटल व्योम xonar_d2_cleanup(काष्ठा oxygen *chip)
अणु
	xonar_disable_output(chip);
पूर्ण

अटल व्योम xonar_hdav_cleanup(काष्ठा oxygen *chip)
अणु
	xonar_hdmi_cleanup(chip);
	xonar_disable_output(chip);
	msleep(2);
पूर्ण

अटल व्योम xonar_st_cleanup(काष्ठा oxygen *chip)
अणु
	xonar_disable_output(chip);
पूर्ण

अटल व्योम xonar_d2_suspend(काष्ठा oxygen *chip)
अणु
	xonar_d2_cleanup(chip);
पूर्ण

अटल व्योम xonar_hdav_suspend(काष्ठा oxygen *chip)
अणु
	xonar_hdav_cleanup(chip);
पूर्ण

अटल व्योम xonar_st_suspend(काष्ठा oxygen *chip)
अणु
	xonar_st_cleanup(chip);
पूर्ण

अटल व्योम xonar_d2_resume(काष्ठा oxygen *chip)
अणु
	pcm1796_रेजिस्टरs_init(chip);
	xonar_enable_output(chip);
पूर्ण

अटल व्योम xonar_hdav_resume(काष्ठा oxygen *chip)
अणु
	काष्ठा xonar_hdav *data = chip->model_data;

	pcm1796_रेजिस्टरs_init(chip);
	xonar_hdmi_resume(chip, &data->hdmi);
	xonar_enable_output(chip);
पूर्ण

अटल व्योम xonar_stx_resume(काष्ठा oxygen *chip)
अणु
	pcm1796_रेजिस्टरs_init(chip);
	xonar_enable_output(chip);
पूर्ण

अटल व्योम xonar_st_resume(काष्ठा oxygen *chip)
अणु
	cs2000_रेजिस्टरs_init(chip);
	xonar_stx_resume(chip);
पूर्ण

अटल व्योम update_pcm1796_oversampling(काष्ठा oxygen *chip)
अणु
	काष्ठा xonar_pcm179x *data = chip->model_data;
	अचिन्हित पूर्णांक i;
	u8 reg;

	अगर (data->current_rate <= 48000 && !data->h6)
		reg = PCM1796_OS_128;
	अन्यथा
		reg = PCM1796_OS_64;
	क्रम (i = 0; i < data->dacs; ++i)
		pcm1796_ग_लिखो_cached(chip, i, 20, reg);
पूर्ण

अटल व्योम update_pcm1796_deemph(काष्ठा oxygen *chip)
अणु
	काष्ठा xonar_pcm179x *data = chip->model_data;
	अचिन्हित पूर्णांक i;
	u8 reg;

	reg = data->pcm1796_regs[0][18 - PCM1796_REG_BASE] & ~PCM1796_DMF_MASK;
	अगर (data->current_rate == 48000)
		reg |= PCM1796_DMF_48;
	अन्यथा अगर (data->current_rate == 44100)
		reg |= PCM1796_DMF_441;
	अन्यथा अगर (data->current_rate == 32000)
		reg |= PCM1796_DMF_32;
	क्रम (i = 0; i < data->dacs; ++i)
		pcm1796_ग_लिखो_cached(chip, i, 18, reg);
पूर्ण

अटल व्योम set_pcm1796_params(काष्ठा oxygen *chip,
			       काष्ठा snd_pcm_hw_params *params)
अणु
	काष्ठा xonar_pcm179x *data = chip->model_data;

	msleep(1);
	data->current_rate = params_rate(params);
	update_pcm1796_oversampling(chip);
	update_pcm1796_deemph(chip);
पूर्ण

अटल व्योम update_pcm1796_volume(काष्ठा oxygen *chip)
अणु
	काष्ठा xonar_pcm179x *data = chip->model_data;
	अचिन्हित पूर्णांक i;
	s8 gain_offset;

	gain_offset = data->hp_active ? data->hp_gain_offset : 0;
	क्रम (i = 0; i < data->dacs; ++i) अणु
		pcm1796_ग_लिखो_cached(chip, i, 16, chip->dac_volume[i * 2]
				     + gain_offset);
		pcm1796_ग_लिखो_cached(chip, i, 17, chip->dac_volume[i * 2 + 1]
				     + gain_offset);
		gain_offset = 0;
	पूर्ण
पूर्ण

अटल व्योम update_pcm1796_mute(काष्ठा oxygen *chip)
अणु
	काष्ठा xonar_pcm179x *data = chip->model_data;
	अचिन्हित पूर्णांक i;
	u8 value;

	value = data->pcm1796_regs[0][18 - PCM1796_REG_BASE];
	अगर (chip->dac_mute)
		value |= PCM1796_MUTE;
	अन्यथा
		value &= ~PCM1796_MUTE;
	क्रम (i = 0; i < data->dacs; ++i)
		pcm1796_ग_लिखो_cached(chip, i, 18, value);
पूर्ण

अटल व्योम update_cs2000_rate(काष्ठा oxygen *chip, अचिन्हित पूर्णांक rate)
अणु
	काष्ठा xonar_pcm179x *data = chip->model_data;
	u8 rate_mclk, reg;

	चयन (rate) अणु
	हाल 32000:
	हाल 64000:
		rate_mclk = OXYGEN_RATE_32000;
		अवरोध;
	हाल 44100:
	हाल 88200:
	हाल 176400:
		rate_mclk = OXYGEN_RATE_44100;
		अवरोध;
	शेष:
	हाल 48000:
	हाल 96000:
	हाल 192000:
		rate_mclk = OXYGEN_RATE_48000;
		अवरोध;
	पूर्ण

	अगर (rate <= 96000 && (rate > 48000 || data->h6)) अणु
		rate_mclk |= OXYGEN_I2S_MCLK(MCLK_256);
		reg = CS2000_REF_CLK_DIV_1;
	पूर्ण अन्यथा अणु
		rate_mclk |= OXYGEN_I2S_MCLK(MCLK_512);
		reg = CS2000_REF_CLK_DIV_2;
	पूर्ण

	oxygen_ग_लिखो16_masked(chip, OXYGEN_I2S_A_FORMAT, rate_mclk,
			      OXYGEN_I2S_RATE_MASK | OXYGEN_I2S_MCLK_MASK);
	cs2000_ग_लिखो_cached(chip, CS2000_FUN_CFG_1, reg);
	msleep(3); /* PLL lock delay */
पूर्ण

अटल व्योम set_st_params(काष्ठा oxygen *chip,
			  काष्ठा snd_pcm_hw_params *params)
अणु
	update_cs2000_rate(chip, params_rate(params));
	set_pcm1796_params(chip, params);
पूर्ण

अटल व्योम set_hdav_params(काष्ठा oxygen *chip,
			    काष्ठा snd_pcm_hw_params *params)
अणु
	काष्ठा xonar_hdav *data = chip->model_data;

	set_pcm1796_params(chip, params);
	xonar_set_hdmi_params(chip, &data->hdmi, params);
पूर्ण

अटल स्थिर काष्ठा snd_kcontrol_new alt_चयन = अणु
	.अगरace = SNDRV_CTL_ELEM_IFACE_MIXER,
	.name = "Analog Loopback Switch",
	.info = snd_ctl_boolean_mono_info,
	.get = xonar_gpio_bit_चयन_get,
	.put = xonar_gpio_bit_चयन_put,
	.निजी_value = GPIO_D2_ALT,
पूर्ण;

अटल पूर्णांक rolloff_info(काष्ठा snd_kcontrol *ctl,
			काष्ठा snd_ctl_elem_info *info)
अणु
	अटल स्थिर अक्षर *स्थिर names[2] = अणु
		"Sharp Roll-off", "Slow Roll-off"
	पूर्ण;

	वापस snd_ctl_क्रमागत_info(info, 1, 2, names);
पूर्ण

अटल पूर्णांक rolloff_get(काष्ठा snd_kcontrol *ctl,
		       काष्ठा snd_ctl_elem_value *value)
अणु
	काष्ठा oxygen *chip = ctl->निजी_data;
	काष्ठा xonar_pcm179x *data = chip->model_data;

	value->value.क्रमागतerated.item[0] =
		(data->pcm1796_regs[0][19 - PCM1796_REG_BASE] &
		 PCM1796_FLT_MASK) != PCM1796_FLT_SHARP;
	वापस 0;
पूर्ण

अटल पूर्णांक rolloff_put(काष्ठा snd_kcontrol *ctl,
		       काष्ठा snd_ctl_elem_value *value)
अणु
	काष्ठा oxygen *chip = ctl->निजी_data;
	काष्ठा xonar_pcm179x *data = chip->model_data;
	अचिन्हित पूर्णांक i;
	पूर्णांक changed;
	u8 reg;

	mutex_lock(&chip->mutex);
	reg = data->pcm1796_regs[0][19 - PCM1796_REG_BASE];
	reg &= ~PCM1796_FLT_MASK;
	अगर (!value->value.क्रमागतerated.item[0])
		reg |= PCM1796_FLT_SHARP;
	अन्यथा
		reg |= PCM1796_FLT_SLOW;
	changed = reg != data->pcm1796_regs[0][19 - PCM1796_REG_BASE];
	अगर (changed) अणु
		क्रम (i = 0; i < data->dacs; ++i)
			pcm1796_ग_लिखो(chip, i, 19, reg);
	पूर्ण
	mutex_unlock(&chip->mutex);
	वापस changed;
पूर्ण

अटल स्थिर काष्ठा snd_kcontrol_new rolloff_control = अणु
	.अगरace = SNDRV_CTL_ELEM_IFACE_MIXER,
	.name = "DAC Filter Playback Enum",
	.info = rolloff_info,
	.get = rolloff_get,
	.put = rolloff_put,
पूर्ण;

अटल पूर्णांक deemph_get(काष्ठा snd_kcontrol *ctl,
		       काष्ठा snd_ctl_elem_value *value)
अणु
	काष्ठा oxygen *chip = ctl->निजी_data;
	काष्ठा xonar_pcm179x *data = chip->model_data;

	value->value.पूर्णांकeger.value[0] =
		!!(data->pcm1796_regs[0][18 - PCM1796_REG_BASE] & PCM1796_DME);
	वापस 0;
पूर्ण

अटल पूर्णांक deemph_put(काष्ठा snd_kcontrol *ctl,
		       काष्ठा snd_ctl_elem_value *value)
अणु
	काष्ठा oxygen *chip = ctl->निजी_data;
	काष्ठा xonar_pcm179x *data = chip->model_data;
	अचिन्हित पूर्णांक i;
	पूर्णांक changed;
	u8 reg;

	mutex_lock(&chip->mutex);
	reg = data->pcm1796_regs[0][18 - PCM1796_REG_BASE];
	अगर (!value->value.पूर्णांकeger.value[0])
		reg &= ~PCM1796_DME;
	अन्यथा
		reg |= PCM1796_DME;
	changed = reg != data->pcm1796_regs[0][18 - PCM1796_REG_BASE];
	अगर (changed) अणु
		क्रम (i = 0; i < data->dacs; ++i)
			pcm1796_ग_लिखो(chip, i, 18, reg);
	पूर्ण
	mutex_unlock(&chip->mutex);
	वापस changed;
पूर्ण

अटल स्थिर काष्ठा snd_kcontrol_new deemph_control = अणु
	.अगरace = SNDRV_CTL_ELEM_IFACE_MIXER,
	.name = "De-emphasis Playback Switch",
	.info = snd_ctl_boolean_mono_info,
	.get = deemph_get,
	.put = deemph_put,
पूर्ण;

अटल स्थिर काष्ठा snd_kcontrol_new hdav_hdmi_control = अणु
	.अगरace = SNDRV_CTL_ELEM_IFACE_MIXER,
	.name = "HDMI Playback Switch",
	.info = snd_ctl_boolean_mono_info,
	.get = xonar_gpio_bit_चयन_get,
	.put = xonar_gpio_bit_चयन_put,
	.निजी_value = GPIO_HDAV_OUTPUT_ENABLE | XONAR_GPIO_BIT_INVERT,
पूर्ण;

अटल पूर्णांक st_output_चयन_info(काष्ठा snd_kcontrol *ctl,
				 काष्ठा snd_ctl_elem_info *info)
अणु
	अटल स्थिर अक्षर *स्थिर names[3] = अणु
		"Speakers", "Headphones", "FP Headphones"
	पूर्ण;

	वापस snd_ctl_क्रमागत_info(info, 1, 3, names);
पूर्ण

अटल पूर्णांक st_output_चयन_get(काष्ठा snd_kcontrol *ctl,
				काष्ठा snd_ctl_elem_value *value)
अणु
	काष्ठा oxygen *chip = ctl->निजी_data;
	u16 gpio;

	gpio = oxygen_पढ़ो16(chip, OXYGEN_GPIO_DATA);
	अगर (!(gpio & GPIO_ST_HP))
		value->value.क्रमागतerated.item[0] = 0;
	अन्यथा अगर (gpio & GPIO_ST_HP_REAR)
		value->value.क्रमागतerated.item[0] = 1;
	अन्यथा
		value->value.क्रमागतerated.item[0] = 2;
	वापस 0;
पूर्ण


अटल पूर्णांक st_output_चयन_put(काष्ठा snd_kcontrol *ctl,
				काष्ठा snd_ctl_elem_value *value)
अणु
	काष्ठा oxygen *chip = ctl->निजी_data;
	काष्ठा xonar_pcm179x *data = chip->model_data;
	u16 gpio_old, gpio;

	mutex_lock(&chip->mutex);
	gpio_old = oxygen_पढ़ो16(chip, OXYGEN_GPIO_DATA);
	gpio = gpio_old;
	चयन (value->value.क्रमागतerated.item[0]) अणु
	हाल 0:
		gpio &= ~(GPIO_ST_HP | GPIO_ST_HP_REAR);
		अवरोध;
	हाल 1:
		gpio |= GPIO_ST_HP | GPIO_ST_HP_REAR;
		अवरोध;
	हाल 2:
		gpio = (gpio | GPIO_ST_HP) & ~GPIO_ST_HP_REAR;
		अवरोध;
	पूर्ण
	oxygen_ग_लिखो16(chip, OXYGEN_GPIO_DATA, gpio);
	data->hp_active = gpio & GPIO_ST_HP;
	update_pcm1796_volume(chip);
	mutex_unlock(&chip->mutex);
	वापस gpio != gpio_old;
पूर्ण

अटल पूर्णांक st_hp_volume_offset_info(काष्ठा snd_kcontrol *ctl,
				    काष्ठा snd_ctl_elem_info *info)
अणु
	अटल स्थिर अक्षर *स्थिर names[4] = अणु
		"< 32 ohms", "32-64 ohms", "64-300 ohms", "300-600 ohms"
	पूर्ण;

	वापस snd_ctl_क्रमागत_info(info, 1, 4, names);
पूर्ण

अटल पूर्णांक st_hp_volume_offset_get(काष्ठा snd_kcontrol *ctl,
				   काष्ठा snd_ctl_elem_value *value)
अणु
	काष्ठा oxygen *chip = ctl->निजी_data;
	काष्ठा xonar_pcm179x *data = chip->model_data;

	mutex_lock(&chip->mutex);
	अगर (data->hp_gain_offset < 2*-12)
		value->value.क्रमागतerated.item[0] = 0;
	अन्यथा अगर (data->hp_gain_offset < 2*-6)
		value->value.क्रमागतerated.item[0] = 1;
	अन्यथा अगर (data->hp_gain_offset < 0)
		value->value.क्रमागतerated.item[0] = 2;
	अन्यथा
		value->value.क्रमागतerated.item[0] = 3;
	mutex_unlock(&chip->mutex);
	वापस 0;
पूर्ण


अटल पूर्णांक st_hp_volume_offset_put(काष्ठा snd_kcontrol *ctl,
				   काष्ठा snd_ctl_elem_value *value)
अणु
	अटल स्थिर s8 offsets[] = अणु 2*-18, 2*-12, 2*-6, 0 पूर्ण;
	काष्ठा oxygen *chip = ctl->निजी_data;
	काष्ठा xonar_pcm179x *data = chip->model_data;
	s8 offset;
	पूर्णांक changed;

	अगर (value->value.क्रमागतerated.item[0] > 3)
		वापस -EINVAL;
	offset = offsets[value->value.क्रमागतerated.item[0]];
	mutex_lock(&chip->mutex);
	changed = offset != data->hp_gain_offset;
	अगर (changed) अणु
		data->hp_gain_offset = offset;
		update_pcm1796_volume(chip);
	पूर्ण
	mutex_unlock(&chip->mutex);
	वापस changed;
पूर्ण

अटल स्थिर काष्ठा snd_kcontrol_new st_controls[] = अणु
	अणु
		.अगरace = SNDRV_CTL_ELEM_IFACE_MIXER,
		.name = "Analog Output",
		.info = st_output_चयन_info,
		.get = st_output_चयन_get,
		.put = st_output_चयन_put,
	पूर्ण,
	अणु
		.अगरace = SNDRV_CTL_ELEM_IFACE_MIXER,
		.name = "Headphones Impedance Playback Enum",
		.info = st_hp_volume_offset_info,
		.get = st_hp_volume_offset_get,
		.put = st_hp_volume_offset_put,
	पूर्ण,
पूर्ण;

अटल पूर्णांक xense_output_चयन_get(काष्ठा snd_kcontrol *ctl,
				   काष्ठा snd_ctl_elem_value *value)
अणु
	काष्ठा oxygen *chip = ctl->निजी_data;
	u16 gpio;

	gpio = oxygen_पढ़ो16(chip, OXYGEN_GPIO_DATA);
	अगर (gpio & GPIO_XENSE_SPEAKERS)
		value->value.क्रमागतerated.item[0] = 0;
	अन्यथा अगर (!(gpio & GPIO_XENSE_SPEAKERS) && (gpio & GPIO_ST_HP_REAR))
		value->value.क्रमागतerated.item[0] = 1;
	अन्यथा
		value->value.क्रमागतerated.item[0] = 2;
	वापस 0;
पूर्ण

अटल पूर्णांक xense_output_चयन_put(काष्ठा snd_kcontrol *ctl,
				   काष्ठा snd_ctl_elem_value *value)
अणु
	काष्ठा oxygen *chip = ctl->निजी_data;
	काष्ठा xonar_pcm179x *data = chip->model_data;
	u16 gpio_old, gpio;

	mutex_lock(&chip->mutex);
	gpio_old = oxygen_पढ़ो16(chip, OXYGEN_GPIO_DATA);
	gpio = gpio_old;
	चयन (value->value.क्रमागतerated.item[0]) अणु
	हाल 0:
		gpio |= GPIO_XENSE_SPEAKERS | GPIO_ST_HP_REAR;
		अवरोध;
	हाल 1:
		gpio = (gpio | GPIO_ST_HP_REAR) & ~GPIO_XENSE_SPEAKERS;
		अवरोध;
	हाल 2:
		gpio &= ~(GPIO_XENSE_SPEAKERS | GPIO_ST_HP_REAR);
		अवरोध;
	पूर्ण
	oxygen_ग_लिखो16(chip, OXYGEN_GPIO_DATA, gpio);
	data->hp_active = !(gpio & GPIO_XENSE_SPEAKERS);
	update_pcm1796_volume(chip);
	mutex_unlock(&chip->mutex);
	वापस gpio != gpio_old;
पूर्ण

अटल स्थिर काष्ठा snd_kcontrol_new xense_controls[] = अणु
	अणु
		.अगरace = SNDRV_CTL_ELEM_IFACE_MIXER,
		.name = "Analog Output",
		.info = st_output_चयन_info,
		.get = xense_output_चयन_get,
		.put = xense_output_चयन_put,
	पूर्ण,
	अणु
		.अगरace = SNDRV_CTL_ELEM_IFACE_MIXER,
		.name = "Headphones Impedance Playback Enum",
		.info = st_hp_volume_offset_info,
		.get = st_hp_volume_offset_get,
		.put = st_hp_volume_offset_put,
	पूर्ण,
पूर्ण;

अटल व्योम xonar_line_mic_ac97_चयन(काष्ठा oxygen *chip,
				       अचिन्हित पूर्णांक reg, अचिन्हित पूर्णांक mute)
अणु
	अगर (reg == AC97_LINE) अणु
		spin_lock_irq(&chip->reg_lock);
		oxygen_ग_लिखो16_masked(chip, OXYGEN_GPIO_DATA,
				      mute ? GPIO_INPUT_ROUTE : 0,
				      GPIO_INPUT_ROUTE);
		spin_unlock_irq(&chip->reg_lock);
	पूर्ण
पूर्ण

अटल स्थिर DECLARE_TLV_DB_SCALE(pcm1796_db_scale, -6000, 50, 0);

अटल पूर्णांक xonar_d2_control_filter(काष्ठा snd_kcontrol_new *ढाँचा)
अणु
	अगर (!म_भेदन(ढाँचा->name, "CD Capture ", 11))
		/* CD in is actually connected to the video in pin */
		ढाँचा->निजी_value ^= AC97_CD ^ AC97_VIDEO;
	वापस 0;
पूर्ण

अटल पूर्णांक xonar_st_h6_control_filter(काष्ठा snd_kcontrol_new *ढाँचा)
अणु
	अगर (!म_भेदन(ढाँचा->name, "Master Playback ", 16))
		/* no volume/mute, as IतऑC to the third DAC करोes not work */
		वापस 1;
	वापस 0;
पूर्ण

अटल पूर्णांक add_pcm1796_controls(काष्ठा oxygen *chip)
अणु
	काष्ठा xonar_pcm179x *data = chip->model_data;
	पूर्णांक err;

	अगर (!data->broken_i2c) अणु
		err = snd_ctl_add(chip->card,
				  snd_ctl_new1(&rolloff_control, chip));
		अगर (err < 0)
			वापस err;
		err = snd_ctl_add(chip->card,
				  snd_ctl_new1(&deemph_control, chip));
		अगर (err < 0)
			वापस err;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक xonar_d2_mixer_init(काष्ठा oxygen *chip)
अणु
	पूर्णांक err;

	err = snd_ctl_add(chip->card, snd_ctl_new1(&alt_चयन, chip));
	अगर (err < 0)
		वापस err;
	err = add_pcm1796_controls(chip);
	अगर (err < 0)
		वापस err;
	वापस 0;
पूर्ण

अटल पूर्णांक xonar_hdav_mixer_init(काष्ठा oxygen *chip)
अणु
	पूर्णांक err;

	err = snd_ctl_add(chip->card, snd_ctl_new1(&hdav_hdmi_control, chip));
	अगर (err < 0)
		वापस err;
	err = add_pcm1796_controls(chip);
	अगर (err < 0)
		वापस err;
	वापस 0;
पूर्ण

अटल पूर्णांक xonar_st_mixer_init(काष्ठा oxygen *chip)
अणु
	अचिन्हित पूर्णांक i;
	पूर्णांक err;

	क्रम (i = 0; i < ARRAY_SIZE(st_controls); ++i) अणु
		err = snd_ctl_add(chip->card,
				  snd_ctl_new1(&st_controls[i], chip));
		अगर (err < 0)
			वापस err;
	पूर्ण
	err = add_pcm1796_controls(chip);
	अगर (err < 0)
		वापस err;
	वापस 0;
पूर्ण

अटल पूर्णांक xonar_xense_mixer_init(काष्ठा oxygen *chip)
अणु
	अचिन्हित पूर्णांक i;
	पूर्णांक err;

	क्रम (i = 0; i < ARRAY_SIZE(xense_controls); ++i) अणु
		err = snd_ctl_add(chip->card,
		snd_ctl_new1(&xense_controls[i], chip));
		अगर (err < 0)
			वापस err;
	पूर्ण
	err = add_pcm1796_controls(chip);
	अगर (err < 0)
		वापस err;
	वापस 0;
पूर्ण

अटल व्योम dump_pcm1796_रेजिस्टरs(काष्ठा oxygen *chip,
				   काष्ठा snd_info_buffer *buffer)
अणु
	काष्ठा xonar_pcm179x *data = chip->model_data;
	अचिन्हित पूर्णांक dac, i;

	क्रम (dac = 0; dac < data->dacs; ++dac) अणु
		snd_iम_लिखो(buffer, "\nPCM1796 %u:", dac + 1);
		क्रम (i = 0; i < 5; ++i)
			snd_iम_लिखो(buffer, " %02x",
				    data->pcm1796_regs[dac][i]);
	पूर्ण
	snd_iम_लिखो(buffer, "\n");
पूर्ण

अटल व्योम dump_cs2000_रेजिस्टरs(काष्ठा oxygen *chip,
				  काष्ठा snd_info_buffer *buffer)
अणु
	काष्ठा xonar_pcm179x *data = chip->model_data;
	अचिन्हित पूर्णांक i;

	अगर (data->has_cs2000) अणु
		snd_iम_लिखो(buffer, "\nCS2000:\n00:   ");
		क्रम (i = 1; i < 0x10; ++i)
			snd_iम_लिखो(buffer, " %02x", data->cs2000_regs[i]);
		snd_iम_लिखो(buffer, "\n10:");
		क्रम (i = 0x10; i < 0x1f; ++i)
			snd_iम_लिखो(buffer, " %02x", data->cs2000_regs[i]);
		snd_iम_लिखो(buffer, "\n");
	पूर्ण
पूर्ण

अटल व्योम dump_st_रेजिस्टरs(काष्ठा oxygen *chip,
			      काष्ठा snd_info_buffer *buffer)
अणु
	dump_pcm1796_रेजिस्टरs(chip, buffer);
	dump_cs2000_रेजिस्टरs(chip, buffer);
पूर्ण

अटल स्थिर काष्ठा oxygen_model model_xonar_d2 = अणु
	.दीर्घname = "Asus Virtuoso 200",
	.chip = "AV200",
	.init = xonar_d2_init,
	.control_filter = xonar_d2_control_filter,
	.mixer_init = xonar_d2_mixer_init,
	.cleanup = xonar_d2_cleanup,
	.suspend = xonar_d2_suspend,
	.resume = xonar_d2_resume,
	.set_dac_params = set_pcm1796_params,
	.set_adc_params = xonar_set_cs53x1_params,
	.update_dac_volume = update_pcm1796_volume,
	.update_dac_mute = update_pcm1796_mute,
	.dump_रेजिस्टरs = dump_pcm1796_रेजिस्टरs,
	.dac_tlv = pcm1796_db_scale,
	.model_data_size = माप(काष्ठा xonar_pcm179x),
	.device_config = PLAYBACK_0_TO_I2S |
			 PLAYBACK_1_TO_SPDIF |
			 CAPTURE_0_FROM_I2S_2 |
			 CAPTURE_1_FROM_SPDIF |
			 MIDI_OUTPUT |
			 MIDI_INPUT |
			 AC97_CD_INPUT,
	.dac_channels_pcm = 8,
	.dac_channels_mixer = 8,
	.dac_volume_min = 255 - 2*60,
	.dac_volume_max = 255,
	.misc_flags = OXYGEN_MISC_MIDI,
	.function_flags = OXYGEN_FUNCTION_SPI |
			  OXYGEN_FUNCTION_ENABLE_SPI_4_5,
	.dac_mclks = OXYGEN_MCLKS(512, 128, 128),
	.adc_mclks = OXYGEN_MCLKS(256, 128, 128),
	.dac_i2s_क्रमmat = OXYGEN_I2S_FORMAT_I2S,
	.adc_i2s_क्रमmat = OXYGEN_I2S_FORMAT_LJUST,
पूर्ण;

अटल स्थिर काष्ठा oxygen_model model_xonar_hdav = अणु
	.दीर्घname = "Asus Virtuoso 200",
	.chip = "AV200",
	.init = xonar_hdav_init,
	.mixer_init = xonar_hdav_mixer_init,
	.cleanup = xonar_hdav_cleanup,
	.suspend = xonar_hdav_suspend,
	.resume = xonar_hdav_resume,
	.pcm_hardware_filter = xonar_hdmi_pcm_hardware_filter,
	.set_dac_params = set_hdav_params,
	.set_adc_params = xonar_set_cs53x1_params,
	.update_dac_volume = update_pcm1796_volume,
	.update_dac_mute = update_pcm1796_mute,
	.uart_input = xonar_hdmi_uart_input,
	.ac97_चयन = xonar_line_mic_ac97_चयन,
	.dump_रेजिस्टरs = dump_pcm1796_रेजिस्टरs,
	.dac_tlv = pcm1796_db_scale,
	.model_data_size = माप(काष्ठा xonar_hdav),
	.device_config = PLAYBACK_0_TO_I2S |
			 PLAYBACK_1_TO_SPDIF |
			 CAPTURE_0_FROM_I2S_2 |
			 CAPTURE_1_FROM_SPDIF,
	.dac_channels_pcm = 8,
	.dac_channels_mixer = 2,
	.dac_volume_min = 255 - 2*60,
	.dac_volume_max = 255,
	.misc_flags = OXYGEN_MISC_MIDI,
	.function_flags = OXYGEN_FUNCTION_2WIRE,
	.dac_mclks = OXYGEN_MCLKS(512, 128, 128),
	.adc_mclks = OXYGEN_MCLKS(256, 128, 128),
	.dac_i2s_क्रमmat = OXYGEN_I2S_FORMAT_I2S,
	.adc_i2s_क्रमmat = OXYGEN_I2S_FORMAT_LJUST,
पूर्ण;

अटल स्थिर काष्ठा oxygen_model model_xonar_st = अणु
	.दीर्घname = "Asus Virtuoso 100",
	.chip = "AV200",
	.init = xonar_st_init,
	.mixer_init = xonar_st_mixer_init,
	.cleanup = xonar_st_cleanup,
	.suspend = xonar_st_suspend,
	.resume = xonar_st_resume,
	.set_dac_params = set_st_params,
	.set_adc_params = xonar_set_cs53x1_params,
	.update_dac_volume = update_pcm1796_volume,
	.update_dac_mute = update_pcm1796_mute,
	.ac97_चयन = xonar_line_mic_ac97_चयन,
	.dump_रेजिस्टरs = dump_st_रेजिस्टरs,
	.dac_tlv = pcm1796_db_scale,
	.model_data_size = माप(काष्ठा xonar_pcm179x),
	.device_config = PLAYBACK_0_TO_I2S |
			 PLAYBACK_1_TO_SPDIF |
			 CAPTURE_0_FROM_I2S_2 |
			 CAPTURE_1_FROM_SPDIF |
			 AC97_FMIC_SWITCH,
	.dac_channels_pcm = 2,
	.dac_channels_mixer = 2,
	.dac_volume_min = 255 - 2*60,
	.dac_volume_max = 255,
	.function_flags = OXYGEN_FUNCTION_2WIRE,
	.dac_mclks = OXYGEN_MCLKS(512, 128, 128),
	.adc_mclks = OXYGEN_MCLKS(256, 128, 128),
	.dac_i2s_क्रमmat = OXYGEN_I2S_FORMAT_I2S,
	.adc_i2s_क्रमmat = OXYGEN_I2S_FORMAT_LJUST,
पूर्ण;

पूर्णांक get_xonar_pcm179x_model(काष्ठा oxygen *chip,
			    स्थिर काष्ठा pci_device_id *id)
अणु
	चयन (id->subdevice) अणु
	हाल 0x8269:
		chip->model = model_xonar_d2;
		chip->model.लघुname = "Xonar D2";
		अवरोध;
	हाल 0x82b7:
		chip->model = model_xonar_d2;
		chip->model.लघुname = "Xonar D2X";
		chip->model.init = xonar_d2x_init;
		अवरोध;
	हाल 0x8314:
		chip->model = model_xonar_hdav;
		oxygen_clear_bits16(chip, OXYGEN_GPIO_CONTROL, GPIO_DB_MASK);
		चयन (oxygen_पढ़ो16(chip, OXYGEN_GPIO_DATA) & GPIO_DB_MASK) अणु
		शेष:
			chip->model.लघुname = "Xonar HDAV1.3";
			अवरोध;
		हाल GPIO_DB_H6:
			chip->model.लघुname = "Xonar HDAV1.3+H6";
			chip->model.dac_channels_mixer = 8;
			chip->model.dac_mclks = OXYGEN_MCLKS(256, 128, 128);
			अवरोध;
		पूर्ण
		अवरोध;
	हाल 0x835d:
		chip->model = model_xonar_st;
		oxygen_clear_bits16(chip, OXYGEN_GPIO_CONTROL, GPIO_DB_MASK);
		चयन (oxygen_पढ़ो16(chip, OXYGEN_GPIO_DATA) & GPIO_DB_MASK) अणु
		शेष:
			chip->model.लघुname = "Xonar ST";
			अवरोध;
		हाल GPIO_DB_H6:
			chip->model.लघुname = "Xonar ST+H6";
			chip->model.control_filter = xonar_st_h6_control_filter;
			chip->model.dac_channels_pcm = 8;
			chip->model.dac_channels_mixer = 8;
			chip->model.dac_volume_min = 255;
			chip->model.dac_mclks = OXYGEN_MCLKS(256, 128, 128);
			अवरोध;
		पूर्ण
		अवरोध;
	हाल 0x835c:
		chip->model = model_xonar_st;
		chip->model.लघुname = "Xonar STX";
		chip->model.init = xonar_stx_init;
		chip->model.resume = xonar_stx_resume;
		chip->model.set_dac_params = set_pcm1796_params;
		अवरोध;
	हाल 0x85f4:
		chip->model = model_xonar_st;
		oxygen_clear_bits16(chip, OXYGEN_GPIO_CONTROL, GPIO_DB_MASK);
		चयन (oxygen_पढ़ो16(chip, OXYGEN_GPIO_DATA) & GPIO_DB_MASK) अणु
		शेष:
			chip->model.लघुname = "Xonar STX II";
			अवरोध;
		हाल GPIO_DB_H6:
			chip->model.लघुname = "Xonar STX II+H6";
			chip->model.dac_channels_pcm = 8;
			chip->model.dac_channels_mixer = 8;
			chip->model.dac_mclks = OXYGEN_MCLKS(256, 128, 128);
			अवरोध;
		पूर्ण
		chip->model.init = xonar_stx_init;
		chip->model.resume = xonar_stx_resume;
		chip->model.set_dac_params = set_pcm1796_params;
		अवरोध;
	हाल 0x8428:
		chip->model = model_xonar_st;
		chip->model.लघुname = "Xonar Xense";
		chip->model.chip = "AV100";
		chip->model.init = xonar_xense_init;
		chip->model.mixer_init = xonar_xense_mixer_init;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण
	वापस 0;
पूर्ण
