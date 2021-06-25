<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * असलtraction of the spi पूर्णांकerface of HopeRf rf69 radio module
 *
 * Copyright (C) 2016 Wolf-Entwicklungen
 *	Marcus Wolf <linux@wolf-entwicklungen.de>
 */

/* enable prosa debug info */
#अघोषित DEBUG
/* enable prपूर्णांक of values on reg access */
#अघोषित DEBUG_VALUES
/* enable prपूर्णांक of values on fअगरo access */
#अघोषित DEBUG_FIFO_ACCESS

#समावेश <linux/types.h>
#समावेश <linux/spi/spi.h>

#समावेश "rf69.h"
#समावेश "rf69_registers.h"

#घोषणा F_OSC	  32000000 /* in Hz */
#घोषणा FIFO_SIZE 66	   /* in byte */

/*-------------------------------------------------------------------------*/

अटल u8 rf69_पढ़ो_reg(काष्ठा spi_device *spi, u8 addr)
अणु
	पूर्णांक retval;

	retval = spi_w8r8(spi, addr);

#अगर_घोषित DEBUG_VALUES
	अगर (retval < 0)
		/*
		 * should never happen, since we alपढ़ोy checked,
		 * that module is connected. Thereक्रमe no error
		 * handling, just an optional error message...
		 */
		dev_dbg(&spi->dev, "read 0x%x FAILED\n", addr);
	अन्यथा
		dev_dbg(&spi->dev, "read 0x%x from reg 0x%x\n", retval, addr);
#पूर्ण_अगर

	वापस retval;
पूर्ण

अटल पूर्णांक rf69_ग_लिखो_reg(काष्ठा spi_device *spi, u8 addr, u8 value)
अणु
	पूर्णांक retval;
	अक्षर buffer[2];

	buffer[0] = addr | WRITE_BIT;
	buffer[1] = value;

	retval = spi_ग_लिखो(spi, &buffer, 2);

#अगर_घोषित DEBUG_VALUES
	अगर (retval < 0)
		/*
		 * should never happen, since we alपढ़ोy checked,
		 * that module is connected. Thereक्रमe no error
		 * handling, just an optional error message...
		 */
		dev_dbg(&spi->dev, "write 0x%x to 0x%x FAILED\n", value, addr);
	अन्यथा
		dev_dbg(&spi->dev, "wrote 0x%x to reg 0x%x\n", value, addr);
#पूर्ण_अगर

	वापस retval;
पूर्ण

/*-------------------------------------------------------------------------*/

अटल पूर्णांक rf69_set_bit(काष्ठा spi_device *spi, u8 reg, u8 mask)
अणु
	u8 पंचांगp;

	पंचांगp = rf69_पढ़ो_reg(spi, reg);
	पंचांगp = पंचांगp | mask;
	वापस rf69_ग_लिखो_reg(spi, reg, पंचांगp);
पूर्ण

अटल पूर्णांक rf69_clear_bit(काष्ठा spi_device *spi, u8 reg, u8 mask)
अणु
	u8 पंचांगp;

	पंचांगp = rf69_पढ़ो_reg(spi, reg);
	पंचांगp = पंचांगp & ~mask;
	वापस rf69_ग_लिखो_reg(spi, reg, पंचांगp);
पूर्ण

अटल अंतरभूत पूर्णांक rf69_पढ़ो_mod_ग_लिखो(काष्ठा spi_device *spi, u8 reg,
				      u8 mask, u8 value)
अणु
	u8 पंचांगp;

	पंचांगp = rf69_पढ़ो_reg(spi, reg);
	पंचांगp = (पंचांगp & ~mask) | value;
	वापस rf69_ग_लिखो_reg(spi, reg, पंचांगp);
पूर्ण

/*-------------------------------------------------------------------------*/

पूर्णांक rf69_set_mode(काष्ठा spi_device *spi, क्रमागत mode mode)
अणु
	अटल स्थिर u8 mode_map[] = अणु
		[transmit] = OPMODE_MODE_TRANSMIT,
		[receive] = OPMODE_MODE_RECEIVE,
		[synthesizer] = OPMODE_MODE_SYNTHESIZER,
		[standby] = OPMODE_MODE_STANDBY,
		[mode_sleep] = OPMODE_MODE_SLEEP,
	पूर्ण;

	अगर (unlikely(mode >= ARRAY_SIZE(mode_map))) अणु
		dev_dbg(&spi->dev, "set: illegal input param");
		वापस -EINVAL;
	पूर्ण

	वापस rf69_पढ़ो_mod_ग_लिखो(spi, REG_OPMODE, MASK_OPMODE_MODE,
				   mode_map[mode]);

	/*
	 * we are using packet mode, so this check is not really needed
	 * but रुकोing क्रम mode पढ़ोy is necessary when going from sleep
	 * because the FIFO may not be immediately available from previous mode
	 * जबतक (_mode == RF69_MODE_SLEEP && (READ_REG(REG_IRQFLAGS1) &
		  RF_IRQFLAGS1_MODEREADY) == 0x00); // Wait क्रम ModeReady
	 */
पूर्ण

पूर्णांक rf69_set_data_mode(काष्ठा spi_device *spi, u8 data_mode)
अणु
	वापस rf69_पढ़ो_mod_ग_लिखो(spi, REG_DATAMODUL, MASK_DATAMODUL_MODE,
				   data_mode);
पूर्ण

पूर्णांक rf69_set_modulation(काष्ठा spi_device *spi, क्रमागत modulation modulation)
अणु
	अटल स्थिर u8 modulation_map[] = अणु
		[OOK] = DATAMODUL_MODULATION_TYPE_OOK,
		[FSK] = DATAMODUL_MODULATION_TYPE_FSK,
	पूर्ण;

	अगर (unlikely(modulation >= ARRAY_SIZE(modulation_map))) अणु
		dev_dbg(&spi->dev, "set: illegal input param");
		वापस -EINVAL;
	पूर्ण

	वापस rf69_पढ़ो_mod_ग_लिखो(spi, REG_DATAMODUL,
				   MASK_DATAMODUL_MODULATION_TYPE,
				   modulation_map[modulation]);
पूर्ण

अटल क्रमागत modulation rf69_get_modulation(काष्ठा spi_device *spi)
अणु
	u8 modulation_reg;

	modulation_reg = rf69_पढ़ो_reg(spi, REG_DATAMODUL);

	चयन (modulation_reg & MASK_DATAMODUL_MODULATION_TYPE) अणु
	हाल DATAMODUL_MODULATION_TYPE_OOK:
		वापस OOK;
	हाल DATAMODUL_MODULATION_TYPE_FSK:
		वापस FSK;
	शेष:
		वापस UNDEF;
	पूर्ण
पूर्ण

पूर्णांक rf69_set_modulation_shaping(काष्ठा spi_device *spi,
				क्रमागत mod_shaping mod_shaping)
अणु
	चयन (rf69_get_modulation(spi)) अणु
	हाल FSK:
		चयन (mod_shaping) अणु
		हाल SHAPING_OFF:
			वापस rf69_पढ़ो_mod_ग_लिखो(spi, REG_DATAMODUL,
						   MASK_DATAMODUL_MODULATION_SHAPE,
						   DATAMODUL_MODULATION_SHAPE_NONE);
		हाल SHAPING_1_0:
			वापस rf69_पढ़ो_mod_ग_लिखो(spi, REG_DATAMODUL,
						   MASK_DATAMODUL_MODULATION_SHAPE,
						   DATAMODUL_MODULATION_SHAPE_1_0);
		हाल SHAPING_0_5:
			वापस rf69_पढ़ो_mod_ग_लिखो(spi, REG_DATAMODUL,
						   MASK_DATAMODUL_MODULATION_SHAPE,
						   DATAMODUL_MODULATION_SHAPE_0_5);
		हाल SHAPING_0_3:
			वापस rf69_पढ़ो_mod_ग_लिखो(spi, REG_DATAMODUL,
						   MASK_DATAMODUL_MODULATION_SHAPE,
						   DATAMODUL_MODULATION_SHAPE_0_3);
		शेष:
			dev_dbg(&spi->dev, "set: illegal input param");
			वापस -EINVAL;
		पूर्ण
	हाल OOK:
		चयन (mod_shaping) अणु
		हाल SHAPING_OFF:
			वापस rf69_पढ़ो_mod_ग_लिखो(spi, REG_DATAMODUL,
						   MASK_DATAMODUL_MODULATION_SHAPE,
						   DATAMODUL_MODULATION_SHAPE_NONE);
		हाल SHAPING_BR:
			वापस rf69_पढ़ो_mod_ग_लिखो(spi, REG_DATAMODUL,
						   MASK_DATAMODUL_MODULATION_SHAPE,
						   DATAMODUL_MODULATION_SHAPE_BR);
		हाल SHAPING_2BR:
			वापस rf69_पढ़ो_mod_ग_लिखो(spi, REG_DATAMODUL,
						   MASK_DATAMODUL_MODULATION_SHAPE,
						   DATAMODUL_MODULATION_SHAPE_2BR);
		शेष:
			dev_dbg(&spi->dev, "set: illegal input param");
			वापस -EINVAL;
		पूर्ण
	शेष:
		dev_dbg(&spi->dev, "set: modulation undefined");
		वापस -EINVAL;
	पूर्ण
पूर्ण

पूर्णांक rf69_set_bit_rate(काष्ठा spi_device *spi, u16 bit_rate)
अणु
	पूर्णांक retval;
	u32 bit_rate_min;
	u32 bit_rate_reg;
	u8 msb;
	u8 lsb;

	// check input value
	bit_rate_min = F_OSC / 8388608; // 8388608 = 2^23;
	अगर (bit_rate < bit_rate_min) अणु
		dev_dbg(&spi->dev, "setBitRate: illegal input param");
		वापस -EINVAL;
	पूर्ण

	// calculate reg settings
	bit_rate_reg = (F_OSC / bit_rate);

	msb = (bit_rate_reg & 0xff00) >> 8;
	lsb = (bit_rate_reg & 0xff);

	// transmit to RF 69
	retval = rf69_ग_लिखो_reg(spi, REG_BITRATE_MSB, msb);
	अगर (retval)
		वापस retval;
	retval = rf69_ग_लिखो_reg(spi, REG_BITRATE_LSB, lsb);
	अगर (retval)
		वापस retval;

	वापस 0;
पूर्ण

पूर्णांक rf69_set_deviation(काष्ठा spi_device *spi, u32 deviation)
अणु
	पूर्णांक retval;
	u64 f_reg;
	u64 f_step;
	u8 msb;
	u8 lsb;
	u64 factor = 1000000; // to improve precision of calculation

	// TODO: Dependency to bitrate
	अगर (deviation < 600 || deviation > 500000) अणु
		dev_dbg(&spi->dev, "set_deviation: illegal input param");
		वापस -EINVAL;
	पूर्ण

	// calculat f step
	f_step = F_OSC * factor;
	करो_भाग(f_step, 524288); //  524288 = 2^19

	// calculate रेजिस्टर settings
	f_reg = deviation * factor;
	करो_भाग(f_reg, f_step);

	msb = (f_reg & 0xff00) >> 8;
	lsb = (f_reg & 0xff);

	// check msb
	अगर (msb & ~FDEVMASB_MASK) अणु
		dev_dbg(&spi->dev, "set_deviation: err in calc of msb");
		वापस -EINVAL;
	पूर्ण

	// ग_लिखो to chip
	retval = rf69_ग_लिखो_reg(spi, REG_FDEV_MSB, msb);
	अगर (retval)
		वापस retval;
	retval = rf69_ग_लिखो_reg(spi, REG_FDEV_LSB, lsb);
	अगर (retval)
		वापस retval;

	वापस 0;
पूर्ण

पूर्णांक rf69_set_frequency(काष्ठा spi_device *spi, u32 frequency)
अणु
	पूर्णांक retval;
	u32 f_max;
	u64 f_reg;
	u64 f_step;
	u8 msb;
	u8 mid;
	u8 lsb;
	u64 factor = 1000000; // to improve precision of calculation

	// calculat f step
	f_step = F_OSC * factor;
	करो_भाग(f_step, 524288); //  524288 = 2^19

	// check input value
	f_max = भाग_u64(f_step * 8388608, factor);
	अगर (frequency > f_max) अणु
		dev_dbg(&spi->dev, "setFrequency: illegal input param");
		वापस -EINVAL;
	पूर्ण

	// calculate reg settings
	f_reg = frequency * factor;
	करो_भाग(f_reg, f_step);

	msb = (f_reg & 0xff0000) >> 16;
	mid = (f_reg & 0xff00)   >>  8;
	lsb = (f_reg & 0xff);

	// ग_लिखो to chip
	retval = rf69_ग_लिखो_reg(spi, REG_FRF_MSB, msb);
	अगर (retval)
		वापस retval;
	retval = rf69_ग_लिखो_reg(spi, REG_FRF_MID, mid);
	अगर (retval)
		वापस retval;
	retval = rf69_ग_लिखो_reg(spi, REG_FRF_LSB, lsb);
	अगर (retval)
		वापस retval;

	वापस 0;
पूर्ण

पूर्णांक rf69_enable_amplअगरier(काष्ठा spi_device *spi, u8 amplअगरier_mask)
अणु
	वापस rf69_set_bit(spi, REG_PALEVEL, amplअगरier_mask);
पूर्ण

पूर्णांक rf69_disable_amplअगरier(काष्ठा spi_device *spi, u8 amplअगरier_mask)
अणु
	वापस rf69_clear_bit(spi, REG_PALEVEL, amplअगरier_mask);
पूर्ण

पूर्णांक rf69_set_output_घातer_level(काष्ठा spi_device *spi, u8 घातer_level)
अणु
	u8 pa_level, ocp, test_pa1, test_pa2;
	bool pa0, pa1, pa2, high_घातer;
	u8 min_घातer_level;

	// check रेजिस्टर pa_level
	pa_level = rf69_पढ़ो_reg(spi, REG_PALEVEL);
	pa0 = pa_level & MASK_PALEVEL_PA0;
	pa1 = pa_level & MASK_PALEVEL_PA1;
	pa2 = pa_level & MASK_PALEVEL_PA2;

	// check high घातer mode
	ocp = rf69_पढ़ो_reg(spi, REG_OCP);
	test_pa1 = rf69_पढ़ो_reg(spi, REG_TESTPA1);
	test_pa2 = rf69_पढ़ो_reg(spi, REG_TESTPA2);
	high_घातer = (ocp == 0x0f) && (test_pa1 == 0x5d) && (test_pa2 == 0x7c);

	अगर (pa0 && !pa1 && !pa2) अणु
		घातer_level += 18;
		min_घातer_level = 0;
	पूर्ण अन्यथा अगर (!pa0 && pa1 && !pa2) अणु
		घातer_level += 18;
		min_घातer_level = 16;
	पूर्ण अन्यथा अगर (!pa0 && pa1 && pa2) अणु
		अगर (high_घातer)
			घातer_level += 11;
		अन्यथा
			घातer_level += 14;
		min_घातer_level = 16;
	पूर्ण अन्यथा अणु
		जाओ failed;
	पूर्ण

	// check input value
	अगर (घातer_level > 0x1f)
		जाओ failed;

	अगर (घातer_level < min_घातer_level)
		जाओ failed;

	// ग_लिखो value
	वापस rf69_पढ़ो_mod_ग_लिखो(spi, REG_PALEVEL, MASK_PALEVEL_OUTPUT_POWER,
				   घातer_level);
failed:
	dev_dbg(&spi->dev, "set: illegal input param");
	वापस -EINVAL;
पूर्ण

पूर्णांक rf69_set_pa_ramp(काष्ठा spi_device *spi, क्रमागत pa_ramp pa_ramp)
अणु
	अटल स्थिर u8 pa_ramp_map[] = अणु
		[ramp3400] = PARAMP_3400,
		[ramp2000] = PARAMP_2000,
		[ramp1000] = PARAMP_1000,
		[ramp500] = PARAMP_500,
		[ramp250] = PARAMP_250,
		[ramp125] = PARAMP_125,
		[ramp100] = PARAMP_100,
		[ramp62] = PARAMP_62,
		[ramp50] = PARAMP_50,
		[ramp40] = PARAMP_40,
		[ramp31] = PARAMP_31,
		[ramp25] = PARAMP_25,
		[ramp20] = PARAMP_20,
		[ramp15] = PARAMP_15,
		[ramp10] = PARAMP_10,
	पूर्ण;

	अगर (unlikely(pa_ramp >= ARRAY_SIZE(pa_ramp_map))) अणु
		dev_dbg(&spi->dev, "set: illegal input param");
		वापस -EINVAL;
	पूर्ण

	वापस rf69_ग_लिखो_reg(spi, REG_PARAMP, pa_ramp_map[pa_ramp]);
पूर्ण

पूर्णांक rf69_set_antenna_impedance(काष्ठा spi_device *spi,
			       क्रमागत antenna_impedance antenna_impedance)
अणु
	चयन (antenna_impedance) अणु
	हाल fअगरty_ohm:
		वापस rf69_clear_bit(spi, REG_LNA, MASK_LNA_ZIN);
	हाल two_hundred_ohm:
		वापस rf69_set_bit(spi, REG_LNA, MASK_LNA_ZIN);
	शेष:
		dev_dbg(&spi->dev, "set: illegal input param");
		वापस -EINVAL;
	पूर्ण
पूर्ण

पूर्णांक rf69_set_lna_gain(काष्ठा spi_device *spi, क्रमागत lna_gain lna_gain)
अणु
	अटल स्थिर u8 lna_gain_map[] = अणु
		[स्वतःmatic] = LNA_GAIN_AUTO,
		[max] = LNA_GAIN_MAX,
		[max_minus_6] = LNA_GAIN_MAX_MINUS_6,
		[max_minus_12] = LNA_GAIN_MAX_MINUS_12,
		[max_minus_24] = LNA_GAIN_MAX_MINUS_24,
		[max_minus_36] = LNA_GAIN_MAX_MINUS_36,
		[max_minus_48] = LNA_GAIN_MAX_MINUS_48,
	पूर्ण;

	अगर (unlikely(lna_gain >= ARRAY_SIZE(lna_gain_map))) अणु
		dev_dbg(&spi->dev, "set: illegal input param");
		वापस -EINVAL;
	पूर्ण

	वापस rf69_पढ़ो_mod_ग_लिखो(spi, REG_LNA, MASK_LNA_GAIN,
				   lna_gain_map[lna_gain]);
पूर्ण

अटल पूर्णांक rf69_set_bandwidth_पूर्णांकern(काष्ठा spi_device *spi, u8 reg,
				     क्रमागत mantisse mantisse, u8 exponent)
अणु
	u8 bandwidth;

	// check value क्रम mantisse and exponent
	अगर (exponent > 7) अणु
		dev_dbg(&spi->dev, "set: illegal input param");
		वापस -EINVAL;
	पूर्ण

	अगर ((mantisse != mantisse16) &&
	    (mantisse != mantisse20) &&
	    (mantisse != mantisse24)) अणु
		dev_dbg(&spi->dev, "set: illegal input param");
		वापस -EINVAL;
	पूर्ण

	// पढ़ो old value
	bandwidth = rf69_पढ़ो_reg(spi, reg);

	// "delete" mantisse and exponent = just keep the DCC setting
	bandwidth = bandwidth & MASK_BW_DCC_FREQ;

	// add new mantisse
	चयन (mantisse) अणु
	हाल mantisse16:
		bandwidth = bandwidth | BW_MANT_16;
		अवरोध;
	हाल mantisse20:
		bandwidth = bandwidth | BW_MANT_20;
		अवरोध;
	हाल mantisse24:
		bandwidth = bandwidth | BW_MANT_24;
		अवरोध;
	पूर्ण

	// add new exponent
	bandwidth = bandwidth | exponent;

	// ग_लिखो back
	वापस rf69_ग_लिखो_reg(spi, reg, bandwidth);
पूर्ण

पूर्णांक rf69_set_bandwidth(काष्ठा spi_device *spi, क्रमागत mantisse mantisse,
		       u8 exponent)
अणु
	वापस rf69_set_bandwidth_पूर्णांकern(spi, REG_RXBW, mantisse, exponent);
पूर्ण

पूर्णांक rf69_set_bandwidth_during_afc(काष्ठा spi_device *spi,
				  क्रमागत mantisse mantisse,
				  u8 exponent)
अणु
	वापस rf69_set_bandwidth_पूर्णांकern(spi, REG_AFCBW, mantisse, exponent);
पूर्ण

पूर्णांक rf69_set_ook_threshold_dec(काष्ठा spi_device *spi,
			       क्रमागत threshold_decrement threshold_decrement)
अणु
	अटल स्थिर u8 td_map[] = अणु
		[dec_every8th] = OOKPEAK_THRESHDEC_EVERY_8TH,
		[dec_every4th] = OOKPEAK_THRESHDEC_EVERY_4TH,
		[dec_every2nd] = OOKPEAK_THRESHDEC_EVERY_2ND,
		[dec_once] = OOKPEAK_THRESHDEC_ONCE,
		[dec_twice] = OOKPEAK_THRESHDEC_TWICE,
		[dec_4बार] = OOKPEAK_THRESHDEC_4_TIMES,
		[dec_8बार] = OOKPEAK_THRESHDEC_8_TIMES,
		[dec_16बार] = OOKPEAK_THRESHDEC_16_TIMES,
	पूर्ण;

	अगर (unlikely(threshold_decrement >= ARRAY_SIZE(td_map))) अणु
		dev_dbg(&spi->dev, "set: illegal input param");
		वापस -EINVAL;
	पूर्ण

	वापस rf69_पढ़ो_mod_ग_लिखो(spi, REG_OOKPEAK, MASK_OOKPEAK_THRESDEC,
				   td_map[threshold_decrement]);
पूर्ण

पूर्णांक rf69_set_dio_mapping(काष्ठा spi_device *spi, u8 dio_number, u8 value)
अणु
	u8 mask;
	u8 shअगरt;
	u8 dio_addr;
	u8 dio_value;

	चयन (dio_number) अणु
	हाल 0:
		mask = MASK_DIO0;
		shअगरt = SHIFT_DIO0;
		dio_addr = REG_DIOMAPPING1;
		अवरोध;
	हाल 1:
		mask = MASK_DIO1;
		shअगरt = SHIFT_DIO1;
		dio_addr = REG_DIOMAPPING1;
		अवरोध;
	हाल 2:
		mask = MASK_DIO2;
		shअगरt = SHIFT_DIO2;
		dio_addr = REG_DIOMAPPING1;
		अवरोध;
	हाल 3:
		mask = MASK_DIO3;
		shअगरt = SHIFT_DIO3;
		dio_addr = REG_DIOMAPPING1;
		अवरोध;
	हाल 4:
		mask = MASK_DIO4;
		shअगरt = SHIFT_DIO4;
		dio_addr = REG_DIOMAPPING2;
		अवरोध;
	हाल 5:
		mask = MASK_DIO5;
		shअगरt = SHIFT_DIO5;
		dio_addr = REG_DIOMAPPING2;
		अवरोध;
	शेष:
	dev_dbg(&spi->dev, "set: illegal input param");
		वापस -EINVAL;
	पूर्ण

	// पढ़ो reg
	dio_value = rf69_पढ़ो_reg(spi, dio_addr);
	// delete old value
	dio_value = dio_value & ~mask;
	// add new value
	dio_value = dio_value | value << shअगरt;
	// ग_लिखो back
	वापस rf69_ग_लिखो_reg(spi, dio_addr, dio_value);
पूर्ण

bool rf69_get_flag(काष्ठा spi_device *spi, क्रमागत flag flag)
अणु
	चयन (flag) अणु
	हाल mode_चयन_completed:
		वापस (rf69_पढ़ो_reg(spi, REG_IRQFLAGS1) & MASK_IRQFLAGS1_MODE_READY);
	हाल पढ़ोy_to_receive:
		वापस (rf69_पढ़ो_reg(spi, REG_IRQFLAGS1) & MASK_IRQFLAGS1_RX_READY);
	हाल पढ़ोy_to_send:
		वापस (rf69_पढ़ो_reg(spi, REG_IRQFLAGS1) & MASK_IRQFLAGS1_TX_READY);
	हाल pll_locked:
		वापस (rf69_पढ़ो_reg(spi, REG_IRQFLAGS1) & MASK_IRQFLAGS1_PLL_LOCK);
	हाल rssi_exceeded_threshold:
		वापस (rf69_पढ़ो_reg(spi, REG_IRQFLAGS1) & MASK_IRQFLAGS1_RSSI);
	हाल समयout:
		वापस (rf69_पढ़ो_reg(spi, REG_IRQFLAGS1) & MASK_IRQFLAGS1_TIMEOUT);
	हाल स्वतःmode:
		वापस (rf69_पढ़ो_reg(spi, REG_IRQFLAGS1) & MASK_IRQFLAGS1_AUTOMODE);
	हाल sync_address_match:
		वापस (rf69_पढ़ो_reg(spi, REG_IRQFLAGS1) & MASK_IRQFLAGS1_SYNC_ADDRESS_MATCH);
	हाल fअगरo_full:
		वापस (rf69_पढ़ो_reg(spi, REG_IRQFLAGS2) & MASK_IRQFLAGS2_FIFO_FULL);
/*
 *	हाल fअगरo_not_empty:
 *		वापस (rf69_पढ़ो_reg(spi, REG_IRQFLAGS2) & MASK_IRQFLAGS2_FIFO_NOT_EMPTY);
 */
	हाल fअगरo_empty:
		वापस !(rf69_पढ़ो_reg(spi, REG_IRQFLAGS2) & MASK_IRQFLAGS2_FIFO_NOT_EMPTY);
	हाल fअगरo_level_below_threshold:
		वापस (rf69_पढ़ो_reg(spi, REG_IRQFLAGS2) & MASK_IRQFLAGS2_FIFO_LEVEL);
	हाल fअगरo_overrun:
		वापस (rf69_पढ़ो_reg(spi, REG_IRQFLAGS2) & MASK_IRQFLAGS2_FIFO_OVERRUN);
	हाल packet_sent:
		वापस (rf69_पढ़ो_reg(spi, REG_IRQFLAGS2) & MASK_IRQFLAGS2_PACKET_SENT);
	हाल payload_पढ़ोy:
		वापस (rf69_पढ़ो_reg(spi, REG_IRQFLAGS2) & MASK_IRQFLAGS2_PAYLOAD_READY);
	हाल crc_ok:
		वापस (rf69_पढ़ो_reg(spi, REG_IRQFLAGS2) & MASK_IRQFLAGS2_CRC_OK);
	हाल battery_low:
		वापस (rf69_पढ़ो_reg(spi, REG_IRQFLAGS2) & MASK_IRQFLAGS2_LOW_BAT);
	शेष:			 वापस false;
	पूर्ण
पूर्ण

पूर्णांक rf69_set_rssi_threshold(काष्ठा spi_device *spi, u8 threshold)
अणु
	/* no value check needed - u8 exactly matches रेजिस्टर size */

	वापस rf69_ग_लिखो_reg(spi, REG_RSSITHRESH, threshold);
पूर्ण

पूर्णांक rf69_set_preamble_length(काष्ठा spi_device *spi, u16 preamble_length)
अणु
	पूर्णांक retval;
	u8 msb, lsb;

	/* no value check needed - u16 exactly matches रेजिस्टर size */

	/* calculate reg settings */
	msb = (preamble_length & 0xff00) >> 8;
	lsb = (preamble_length & 0xff);

	/* transmit to chip */
	retval = rf69_ग_लिखो_reg(spi, REG_PREAMBLE_MSB, msb);
	अगर (retval)
		वापस retval;
	वापस rf69_ग_लिखो_reg(spi, REG_PREAMBLE_LSB, lsb);
पूर्ण

पूर्णांक rf69_enable_sync(काष्ठा spi_device *spi)
अणु
	वापस rf69_set_bit(spi, REG_SYNC_CONFIG, MASK_SYNC_CONFIG_SYNC_ON);
पूर्ण

पूर्णांक rf69_disable_sync(काष्ठा spi_device *spi)
अणु
	वापस rf69_clear_bit(spi, REG_SYNC_CONFIG, MASK_SYNC_CONFIG_SYNC_ON);
पूर्ण

पूर्णांक rf69_set_fअगरo_fill_condition(काष्ठा spi_device *spi,
				 क्रमागत fअगरo_fill_condition fअगरo_fill_condition)
अणु
	चयन (fअगरo_fill_condition) अणु
	हाल always:
		वापस rf69_set_bit(spi, REG_SYNC_CONFIG,
				    MASK_SYNC_CONFIG_FIFO_FILL_CONDITION);
	हाल after_sync_पूर्णांकerrupt:
		वापस rf69_clear_bit(spi, REG_SYNC_CONFIG,
				      MASK_SYNC_CONFIG_FIFO_FILL_CONDITION);
	शेष:
		dev_dbg(&spi->dev, "set: illegal input param");
		वापस -EINVAL;
	पूर्ण
पूर्ण

पूर्णांक rf69_set_sync_size(काष्ठा spi_device *spi, u8 sync_size)
अणु
	// check input value
	अगर (sync_size > 0x07) अणु
		dev_dbg(&spi->dev, "set: illegal input param");
		वापस -EINVAL;
	पूर्ण

	// ग_लिखो value
	वापस rf69_पढ़ो_mod_ग_लिखो(spi, REG_SYNC_CONFIG,
				   MASK_SYNC_CONFIG_SYNC_SIZE,
				   (sync_size << 3));
पूर्ण

पूर्णांक rf69_set_sync_values(काष्ठा spi_device *spi, u8 sync_values[8])
अणु
	पूर्णांक retval = 0;

	retval += rf69_ग_लिखो_reg(spi, REG_SYNCVALUE1, sync_values[0]);
	retval += rf69_ग_लिखो_reg(spi, REG_SYNCVALUE2, sync_values[1]);
	retval += rf69_ग_लिखो_reg(spi, REG_SYNCVALUE3, sync_values[2]);
	retval += rf69_ग_लिखो_reg(spi, REG_SYNCVALUE4, sync_values[3]);
	retval += rf69_ग_लिखो_reg(spi, REG_SYNCVALUE5, sync_values[4]);
	retval += rf69_ग_लिखो_reg(spi, REG_SYNCVALUE6, sync_values[5]);
	retval += rf69_ग_लिखो_reg(spi, REG_SYNCVALUE7, sync_values[6]);
	retval += rf69_ग_लिखो_reg(spi, REG_SYNCVALUE8, sync_values[7]);

	वापस retval;
पूर्ण

पूर्णांक rf69_set_packet_क्रमmat(काष्ठा spi_device *spi,
			   क्रमागत packet_क्रमmat packet_क्रमmat)
अणु
	चयन (packet_क्रमmat) अणु
	हाल packet_length_var:
		वापस rf69_set_bit(spi, REG_PACKETCONFIG1,
				    MASK_PACKETCONFIG1_PACKET_FORMAT_VARIABLE);
	हाल packet_length_fix:
		वापस rf69_clear_bit(spi, REG_PACKETCONFIG1,
				      MASK_PACKETCONFIG1_PACKET_FORMAT_VARIABLE);
	शेष:
		dev_dbg(&spi->dev, "set: illegal input param");
		वापस -EINVAL;
	पूर्ण
पूर्ण

पूर्णांक rf69_enable_crc(काष्ठा spi_device *spi)
अणु
	वापस rf69_set_bit(spi, REG_PACKETCONFIG1, MASK_PACKETCONFIG1_CRC_ON);
पूर्ण

पूर्णांक rf69_disable_crc(काष्ठा spi_device *spi)
अणु
	वापस rf69_clear_bit(spi, REG_PACKETCONFIG1, MASK_PACKETCONFIG1_CRC_ON);
पूर्ण

पूर्णांक rf69_set_address_filtering(काष्ठा spi_device *spi,
			       क्रमागत address_filtering address_filtering)
अणु
	अटल स्थिर u8 af_map[] = अणु
		[filtering_off] = PACKETCONFIG1_ADDRESSFILTERING_OFF,
		[node_address] = PACKETCONFIG1_ADDRESSFILTERING_NODE,
		[node_or_broadcast_address] =
			PACKETCONFIG1_ADDRESSFILTERING_NODEBROADCAST,
	पूर्ण;

	अगर (unlikely(address_filtering >= ARRAY_SIZE(af_map))) अणु
		dev_dbg(&spi->dev, "set: illegal input param");
		वापस -EINVAL;
	पूर्ण

	वापस rf69_पढ़ो_mod_ग_लिखो(spi, REG_PACKETCONFIG1,
				   MASK_PACKETCONFIG1_ADDRESSFILTERING,
				   af_map[address_filtering]);
पूर्ण

पूर्णांक rf69_set_payload_length(काष्ठा spi_device *spi, u8 payload_length)
अणु
	वापस rf69_ग_लिखो_reg(spi, REG_PAYLOAD_LENGTH, payload_length);
पूर्ण

पूर्णांक rf69_set_node_address(काष्ठा spi_device *spi, u8 node_address)
अणु
	वापस rf69_ग_लिखो_reg(spi, REG_NODEADRS, node_address);
पूर्ण

पूर्णांक rf69_set_broadcast_address(काष्ठा spi_device *spi, u8 broadcast_address)
अणु
	वापस rf69_ग_लिखो_reg(spi, REG_BROADCASTADRS, broadcast_address);
पूर्ण

पूर्णांक rf69_set_tx_start_condition(काष्ठा spi_device *spi,
				क्रमागत tx_start_condition tx_start_condition)
अणु
	चयन (tx_start_condition) अणु
	हाल fअगरo_level:
		वापस rf69_clear_bit(spi, REG_FIFO_THRESH,
				      MASK_FIFO_THRESH_TXSTART);
	हाल fअगरo_not_empty:
		वापस rf69_set_bit(spi, REG_FIFO_THRESH,
				    MASK_FIFO_THRESH_TXSTART);
	शेष:
		dev_dbg(&spi->dev, "set: illegal input param");
		वापस -EINVAL;
	पूर्ण
पूर्ण

पूर्णांक rf69_set_fअगरo_threshold(काष्ठा spi_device *spi, u8 threshold)
अणु
	पूर्णांक retval;

	/* check input value */
	अगर (threshold & 0x80) अणु
		dev_dbg(&spi->dev, "set: illegal input param");
		वापस -EINVAL;
	पूर्ण

	/* ग_लिखो value */
	retval = rf69_पढ़ो_mod_ग_लिखो(spi, REG_FIFO_THRESH,
				     MASK_FIFO_THRESH_VALUE,
				     threshold);
	अगर (retval)
		वापस retval;

	/*
	 * access the fअगरo to activate new threshold
	 * retval (mis-) used as buffer here
	 */
	वापस rf69_पढ़ो_fअगरo(spi, (u8 *)&retval, 1);
पूर्ण

पूर्णांक rf69_set_dagc(काष्ठा spi_device *spi, क्रमागत dagc dagc)
अणु
	अटल स्थिर u8 dagc_map[] = अणु
		[normal_mode] = DAGC_NORMAL,
		[improve] = DAGC_IMPROVED_LOWBETA0,
		[improve_क्रम_low_modulation_index] = DAGC_IMPROVED_LOWBETA1,
	पूर्ण;

	अगर (unlikely(dagc >= ARRAY_SIZE(dagc_map))) अणु
		dev_dbg(&spi->dev, "set: illegal input param");
		वापस -EINVAL;
	पूर्ण

	वापस rf69_ग_लिखो_reg(spi, REG_TESTDAGC, dagc_map[dagc]);
पूर्ण

/*-------------------------------------------------------------------------*/

पूर्णांक rf69_पढ़ो_fअगरo(काष्ठा spi_device *spi, u8 *buffer, अचिन्हित पूर्णांक size)
अणु
#अगर_घोषित DEBUG_FIFO_ACCESS
	पूर्णांक i;
#पूर्ण_अगर
	काष्ठा spi_transfer transfer;
	u8 local_buffer[FIFO_SIZE + 1];
	पूर्णांक retval;

	अगर (size > FIFO_SIZE) अणु
		dev_dbg(&spi->dev,
			"read fifo: passed in buffer bigger then internal buffer\n");
		वापस -EMSGSIZE;
	पूर्ण

	/* prepare a bidirectional transfer */
	local_buffer[0] = REG_FIFO;
	स_रखो(&transfer, 0, माप(transfer));
	transfer.tx_buf = local_buffer;
	transfer.rx_buf = local_buffer;
	transfer.len	= size + 1;

	retval = spi_sync_transfer(spi, &transfer, 1);

#अगर_घोषित DEBUG_FIFO_ACCESS
	क्रम (i = 0; i < size; i++)
		dev_dbg(&spi->dev, "%d - 0x%x\n", i, local_buffer[i + 1]);
#पूर्ण_अगर

	स_नकल(buffer, &local_buffer[1], size);

	वापस retval;
पूर्ण

पूर्णांक rf69_ग_लिखो_fअगरo(काष्ठा spi_device *spi, u8 *buffer, अचिन्हित पूर्णांक size)
अणु
#अगर_घोषित DEBUG_FIFO_ACCESS
	पूर्णांक i;
#पूर्ण_अगर
	u8 local_buffer[FIFO_SIZE + 1];

	अगर (size > FIFO_SIZE) अणु
		dev_dbg(&spi->dev,
			"read fifo: passed in buffer bigger then internal buffer\n");
		वापस -EMSGSIZE;
	पूर्ण

	local_buffer[0] = REG_FIFO | WRITE_BIT;
	स_नकल(&local_buffer[1], buffer, size);

#अगर_घोषित DEBUG_FIFO_ACCESS
	क्रम (i = 0; i < size; i++)
		dev_dbg(&spi->dev, "0x%x\n", buffer[i]);
#पूर्ण_अगर

	वापस spi_ग_लिखो(spi, local_buffer, size + 1);
पूर्ण

