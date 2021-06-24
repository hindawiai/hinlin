<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * comedi/drivers/cb_pcidas64.c
 * This is a driver क्रम the ComputerBoards/MeasurementComputing PCI-DAS
 * 64xx, 60xx, and 4020 cards.
 *
 * Author:  Frank Mori Hess <fmhess@users.sourceक्रमge.net>
 * Copyright (C) 2001, 2002 Frank Mori Hess
 *
 * Thanks also go to the following people:
 *
 * Steve Rosenbluth, क्रम providing the source code क्रम
 * his pci-das6402 driver, and source code क्रम working QNX pci-6402
 * drivers by Greg Laird and Mariusz Bogacz.  None of the code was
 * used directly here, but it was useful as an additional source of
 * करोcumentation on how to program the boards.
 *
 * John Sims, क्रम much testing and feedback on pcidas-4020 support.
 *
 * COMEDI - Linux Control and Measurement Device Interface
 * Copyright (C) 1997-8 David A. Schleef <ds@schleef.org>
 */

/*
 * Driver: cb_pcidas64
 * Description: MeasurementComputing PCI-DAS64xx, 60XX, and 4020 series
 *   with the PLX 9080 PCI controller
 * Author: Frank Mori Hess <fmhess@users.sourceक्रमge.net>
 * Status: works
 * Updated: Fri, 02 Nov 2012 18:58:55 +0000
 * Devices: [Measurement Computing] PCI-DAS6402/16 (cb_pcidas64),
 *   PCI-DAS6402/12, PCI-DAS64/M1/16, PCI-DAS64/M2/16,
 *   PCI-DAS64/M3/16, PCI-DAS6402/16/JR, PCI-DAS64/M1/16/JR,
 *   PCI-DAS64/M2/16/JR, PCI-DAS64/M3/16/JR, PCI-DAS64/M1/14,
 *   PCI-DAS64/M2/14, PCI-DAS64/M3/14, PCI-DAS6013, PCI-DAS6014,
 *   PCI-DAS6023, PCI-DAS6025, PCI-DAS6030,
 *   PCI-DAS6031, PCI-DAS6032, PCI-DAS6033, PCI-DAS6034,
 *   PCI-DAS6035, PCI-DAS6036, PCI-DAS6040, PCI-DAS6052,
 *   PCI-DAS6070, PCI-DAS6071, PCI-DAS4020/12
 *
 * Configuration options:
 *   None.
 *
 * Manual attachment of PCI cards with the comedi_config utility is not
 * supported by this driver; they are attached स्वतःmatically.
 *
 * These boards may be स्वतःcalibrated with the comedi_calibrate utility.
 *
 * To select the bnc trigger input on the 4020 (instead of the dio input),
 * specअगरy a nonzero channel in the chanspec.  If you wish to use an बाह्यal
 * master घड़ी on the 4020, you may करो so by setting the scan_begin_src
 * to TRIG_OTHER, and using an INSN_CONFIG_TIMER_1 configuration insn
 * to configure the भागisor to use क्रम the बाह्यal घड़ी.
 *
 * Some devices are not identअगरied because the PCI device IDs are not yet
 * known. If you have such a board, please let the मुख्यtainers know.
 */

/*
 * TODO:
 * make it वापस error अगर user attempts an ai command that uses the
 * बाह्यal queue, and an ao command simultaneously user counter subdevice
 * there are a number of boards this driver will support when they are
 * fully released, but करोes not yet since the pci device id numbers
 * are not yet available.
 *
 * support prescaled 100khz घड़ी क्रम slow pacing (not available on 6000
 * series?)
 *
 * make ao fअगरo size adjustable like ai fअगरo
 */

#समावेश <linux/module.h>
#समावेश <linux/delay.h>
#समावेश <linux/पूर्णांकerrupt.h>

#समावेश "../comedi_pci.h"

#समावेश "8255.h"
#समावेश "plx9080.h"

#घोषणा TIMER_BASE 25		/*  40MHz master घड़ी */
/*
 * 100kHz 'prescaled' घड़ी क्रम slow acquisition,
 * maybe I'll support this someday
 */
#घोषणा PRESCALED_TIMER_BASE	10000
#घोषणा DMA_BUFFER_SIZE		0x1000
#घोषणा DAC_FIFO_SIZE		0x2000

/* maximum value that can be loaded पूर्णांकo board's 24-bit counters */
अटल स्थिर पूर्णांक max_counter_value = 0xffffff;

/* PCI-DAS64xxx base addresses */

/* devpriv->मुख्य_iobase रेजिस्टरs */
क्रमागत ग_लिखो_only_रेजिस्टरs अणु
	INTR_ENABLE_REG = 0x0,		/* पूर्णांकerrupt enable रेजिस्टर */
	HW_CONFIG_REG = 0x2,		/* hardware config रेजिस्टर */
	DAQ_SYNC_REG = 0xc,
	DAQ_ATRIG_LOW_4020_REG = 0xc,
	ADC_CONTROL0_REG = 0x10,	/* adc control रेजिस्टर 0 */
	ADC_CONTROL1_REG = 0x12,	/* adc control रेजिस्टर 1 */
	CALIBRATION_REG = 0x14,
	/* lower 16 bits of adc sample पूर्णांकerval counter */
	ADC_SAMPLE_INTERVAL_LOWER_REG = 0x16,
	/* upper 8 bits of adc sample पूर्णांकerval counter */
	ADC_SAMPLE_INTERVAL_UPPER_REG = 0x18,
	/* lower 16 bits of delay पूर्णांकerval counter */
	ADC_DELAY_INTERVAL_LOWER_REG = 0x1a,
	/* upper 8 bits of delay पूर्णांकerval counter */
	ADC_DELAY_INTERVAL_UPPER_REG = 0x1c,
	/* lower 16 bits of hardware conversion/scan counter */
	ADC_COUNT_LOWER_REG = 0x1e,
	/* upper 8 bits of hardware conversion/scan counter */
	ADC_COUNT_UPPER_REG = 0x20,
	ADC_START_REG = 0x22,	/* software trigger to start acquisition */
	ADC_CONVERT_REG = 0x24,	/* initiates single conversion */
	ADC_QUEUE_CLEAR_REG = 0x26,	/* clears adc queue */
	ADC_QUEUE_LOAD_REG = 0x28,	/* loads adc queue */
	ADC_BUFFER_CLEAR_REG = 0x2a,
	/* high channel क्रम पूर्णांकernal queue, use adc_chan_bits() अंतरभूत above */
	ADC_QUEUE_HIGH_REG = 0x2c,
	DAC_CONTROL0_REG = 0x50,	/* dac control रेजिस्टर 0 */
	DAC_CONTROL1_REG = 0x52,	/* dac control रेजिस्टर 0 */
	/* lower 16 bits of dac sample पूर्णांकerval counter */
	DAC_SAMPLE_INTERVAL_LOWER_REG = 0x54,
	/* upper 8 bits of dac sample पूर्णांकerval counter */
	DAC_SAMPLE_INTERVAL_UPPER_REG = 0x56,
	DAC_SELECT_REG = 0x60,
	DAC_START_REG = 0x64,
	DAC_BUFFER_CLEAR_REG = 0x66,	/* clear dac buffer */
पूर्ण;

अटल अंतरभूत अचिन्हित पूर्णांक dac_convert_reg(अचिन्हित पूर्णांक channel)
अणु
	वापस 0x70 + (2 * (channel & 0x1));
पूर्ण

अटल अंतरभूत अचिन्हित पूर्णांक dac_lsb_4020_reg(अचिन्हित पूर्णांक channel)
अणु
	वापस 0x70 + (4 * (channel & 0x1));
पूर्ण

अटल अंतरभूत अचिन्हित पूर्णांक dac_msb_4020_reg(अचिन्हित पूर्णांक channel)
अणु
	वापस 0x72 + (4 * (channel & 0x1));
पूर्ण

क्रमागत पढ़ो_only_रेजिस्टरs अणु
	/*
	 * hardware status रेजिस्टर,
	 * पढ़ोing this apparently clears pending पूर्णांकerrupts as well
	 */
	HW_STATUS_REG = 0x0,
	PIPE1_READ_REG = 0x4,
	ADC_READ_PNTR_REG = 0x8,
	LOWER_XFER_REG = 0x10,
	ADC_WRITE_PNTR_REG = 0xc,
	PREPOST_REG = 0x14,
पूर्ण;

क्रमागत पढ़ो_ग_लिखो_रेजिस्टरs अणु
	I8255_4020_REG = 0x48,	/* 8255 offset, क्रम 4020 only */
	/* बाह्यal channel/gain queue, uses same bits as ADC_QUEUE_LOAD_REG */
	ADC_QUEUE_FIFO_REG = 0x100,
	ADC_FIFO_REG = 0x200,	/* adc data fअगरo */
	/* dac data fअगरo, has weird पूर्णांकeractions with बाह्यal channel queue */
	DAC_FIFO_REG = 0x300,
पूर्ण;

/* dev->mmio रेजिस्टरs */
क्रमागत dio_counter_रेजिस्टरs अणु
	DIO_8255_OFFSET = 0x0,
	DO_REG = 0x20,
	DI_REG = 0x28,
	DIO_सूचीECTION_60XX_REG = 0x40,
	DIO_DATA_60XX_REG = 0x48,
पूर्ण;

/* bit definitions क्रम ग_लिखो-only रेजिस्टरs */

क्रमागत पूर्णांकr_enable_contents अणु
	ADC_INTR_SRC_MASK = 0x3,	/* adc पूर्णांकerrupt source mask */
	ADC_INTR_QFULL_BITS = 0x0,	/* पूर्णांकerrupt fअगरo quarter full */
	ADC_INTR_EOC_BITS = 0x1,	/* पूर्णांकerrupt end of conversion */
	ADC_INTR_EOSCAN_BITS = 0x2,	/* पूर्णांकerrupt end of scan */
	ADC_INTR_EOSEQ_BITS = 0x3,	/* पूर्णांकerrupt end of sequence mask */
	EN_ADC_INTR_SRC_BIT = 0x4,	/* enable adc पूर्णांकerrupt source */
	EN_ADC_DONE_INTR_BIT = 0x8,	/* enable adc acquisition करोne पूर्णांकr */
	DAC_INTR_SRC_MASK = 0x30,
	DAC_INTR_QEMPTY_BITS = 0x0,
	DAC_INTR_HIGH_CHAN_BITS = 0x10,
	EN_DAC_INTR_SRC_BIT = 0x40,	/* enable dac पूर्णांकerrupt source */
	EN_DAC_DONE_INTR_BIT = 0x80,
	EN_ADC_ACTIVE_INTR_BIT = 0x200,	/* enable adc active पूर्णांकerrupt */
	EN_ADC_STOP_INTR_BIT = 0x400,	/* enable adc stop trigger पूर्णांकerrupt */
	EN_DAC_ACTIVE_INTR_BIT = 0x800,	/* enable dac active पूर्णांकerrupt */
	EN_DAC_UNDERRUN_BIT = 0x4000,	/* enable dac underrun status bit */
	EN_ADC_OVERRUN_BIT = 0x8000,	/* enable adc overrun status bit */
पूर्ण;

क्रमागत hw_config_contents अणु
	MASTER_CLOCK_4020_MASK = 0x3,	/* master घड़ी source mask क्रम 4020 */
	INTERNAL_CLOCK_4020_BITS = 0x1,	/* use 40 MHz पूर्णांकernal master घड़ी */
	BNC_CLOCK_4020_BITS = 0x2,	/* use BNC input क्रम master घड़ी */
	EXT_CLOCK_4020_BITS = 0x3,	/* use dio input क्रम master घड़ी */
	EXT_QUEUE_BIT = 0x200,		/* use बाह्यal channel/gain queue */
	/* use 225 nanosec strobe when loading dac instead of 50 nanosec */
	SLOW_DAC_BIT = 0x400,
	/*
	 * bit with unknown function yet given as शेष value in pci-das64
	 * manual
	 */
	HW_CONFIG_DUMMY_BITS = 0x2000,
	/* bit selects channels 1/0 क्रम analog input/output, otherwise 0/1 */
	DMA_CH_SELECT_BIT = 0x8000,
	FIFO_SIZE_REG = 0x4,		/* allows adjusपंचांगent of fअगरo sizes */
	DAC_FIFO_SIZE_MASK = 0xff00,	/* bits that set dac fअगरo size */
	DAC_FIFO_BITS = 0xf800,		/* 8k sample ao fअगरo */
पूर्ण;

क्रमागत daq_atrig_low_4020_contents अणु
	/* use trig/ext clk bnc input क्रम analog gate संकेत */
	EXT_AGATE_BNC_BIT = 0x8000,
	/* use trig/ext clk bnc input क्रम बाह्यal stop trigger संकेत */
	EXT_STOP_TRIG_BNC_BIT = 0x4000,
	/* use trig/ext clk bnc input क्रम बाह्यal start trigger संकेत */
	EXT_START_TRIG_BNC_BIT = 0x2000,
पूर्ण;

क्रमागत adc_control0_contents अणु
	ADC_GATE_SRC_MASK = 0x3,	/* bits that select gate */
	ADC_SOFT_GATE_BITS = 0x1,	/* software gate */
	ADC_EXT_GATE_BITS = 0x2,	/* बाह्यal digital gate */
	ADC_ANALOG_GATE_BITS = 0x3,	/* analog level gate */
	/* level-sensitive gate (क्रम digital) */
	ADC_GATE_LEVEL_BIT = 0x4,
	ADC_GATE_POLARITY_BIT = 0x8,	/* gate active low */
	ADC_START_TRIG_SOFT_BITS = 0x10,
	ADC_START_TRIG_EXT_BITS = 0x20,
	ADC_START_TRIG_ANALOG_BITS = 0x30,
	ADC_START_TRIG_MASK = 0x30,
	ADC_START_TRIG_FALLING_BIT = 0x40,	/* trig 1 uses falling edge */
	/* बाह्यal pacing uses falling edge */
	ADC_EXT_CONV_FALLING_BIT = 0x800,
	/* enable hardware scan counter */
	ADC_SAMPLE_COUNTER_EN_BIT = 0x1000,
	ADC_DMA_DISABLE_BIT = 0x4000,	/* disables dma */
	ADC_ENABLE_BIT = 0x8000,	/* master adc enable */
पूर्ण;

क्रमागत adc_control1_contents अणु
	/* should be set क्रम boards with > 16 channels */
	ADC_QUEUE_CONFIG_BIT = 0x1,
	CONVERT_POLARITY_BIT = 0x10,
	EOC_POLARITY_BIT = 0x20,
	ADC_SW_GATE_BIT = 0x40,		/* software gate of adc */
	ADC_DITHER_BIT = 0x200,		/* turn on extra noise क्रम dithering */
	RETRIGGER_BIT = 0x800,
	ADC_LO_CHANNEL_4020_MASK = 0x300,
	ADC_HI_CHANNEL_4020_MASK = 0xc00,
	TWO_CHANNEL_4020_BITS = 0x1000,		/* two channel mode क्रम 4020 */
	FOUR_CHANNEL_4020_BITS = 0x2000,	/* four channel mode क्रम 4020 */
	CHANNEL_MODE_4020_MASK = 0x3000,
	ADC_MODE_MASK = 0xf000,
पूर्ण;

अटल अंतरभूत u16 adc_lo_chan_4020_bits(अचिन्हित पूर्णांक channel)
अणु
	वापस (channel & 0x3) << 8;
पूर्ण;

अटल अंतरभूत u16 adc_hi_chan_4020_bits(अचिन्हित पूर्णांक channel)
अणु
	वापस (channel & 0x3) << 10;
पूर्ण;

अटल अंतरभूत u16 adc_mode_bits(अचिन्हित पूर्णांक mode)
अणु
	वापस (mode & 0xf) << 12;
पूर्ण;

क्रमागत calibration_contents अणु
	SELECT_8800_BIT = 0x1,
	SELECT_8402_64XX_BIT = 0x2,
	SELECT_1590_60XX_BIT = 0x2,
	CAL_EN_64XX_BIT = 0x40,		/* calibration enable क्रम 64xx series */
	SERIAL_DATA_IN_BIT = 0x80,
	SERIAL_CLOCK_BIT = 0x100,
	CAL_EN_60XX_BIT = 0x200,	/* calibration enable क्रम 60xx series */
	CAL_GAIN_BIT = 0x800,
पूर्ण;

/*
 * calibration sources क्रम 6025 are:
 *  0 : ground
 *  1 : 10V
 *  2 : 5V
 *  3 : 0.5V
 *  4 : 0.05V
 *  5 : ground
 *  6 : dac channel 0
 *  7 : dac channel 1
 */

अटल अंतरभूत u16 adc_src_bits(अचिन्हित पूर्णांक source)
अणु
	वापस (source & 0xf) << 3;
पूर्ण;

अटल अंतरभूत u16 adc_convert_chan_4020_bits(अचिन्हित पूर्णांक channel)
अणु
	वापस (channel & 0x3) << 8;
पूर्ण;

क्रमागत adc_queue_load_contents अणु
	UNIP_BIT = 0x800,		/* unipolar/bipolar bit */
	ADC_SE_DIFF_BIT = 0x1000,	/* single-ended/ dअगरferential bit */
	/* non-referenced single-ended (common-mode input) */
	ADC_COMMON_BIT = 0x2000,
	QUEUE_EOSEQ_BIT = 0x4000,	/* queue end of sequence */
	QUEUE_EOSCAN_BIT = 0x8000,	/* queue end of scan */
पूर्ण;

अटल अंतरभूत u16 adc_chan_bits(अचिन्हित पूर्णांक channel)
अणु
	वापस channel & 0x3f;
पूर्ण;

क्रमागत dac_control0_contents अणु
	DAC_ENABLE_BIT = 0x8000,	/* dac controller enable bit */
	DAC_CYCLIC_STOP_BIT = 0x4000,
	DAC_WAVEFORM_MODE_BIT = 0x100,
	DAC_EXT_UPDATE_FALLING_BIT = 0x80,
	DAC_EXT_UPDATE_ENABLE_BIT = 0x40,
	WAVEFORM_TRIG_MASK = 0x30,
	WAVEFORM_TRIG_DISABLED_BITS = 0x0,
	WAVEFORM_TRIG_SOFT_BITS = 0x10,
	WAVEFORM_TRIG_EXT_BITS = 0x20,
	WAVEFORM_TRIG_ADC1_BITS = 0x30,
	WAVEFORM_TRIG_FALLING_BIT = 0x8,
	WAVEFORM_GATE_LEVEL_BIT = 0x4,
	WAVEFORM_GATE_ENABLE_BIT = 0x2,
	WAVEFORM_GATE_SELECT_BIT = 0x1,
पूर्ण;

क्रमागत dac_control1_contents अणु
	DAC_WRITE_POLARITY_BIT = 0x800,	/* board-dependent setting */
	DAC1_EXT_REF_BIT = 0x200,
	DAC0_EXT_REF_BIT = 0x100,
	DAC_OUTPUT_ENABLE_BIT = 0x80,	/* dac output enable bit */
	DAC_UPDATE_POLARITY_BIT = 0x40,	/* board-dependent setting */
	DAC_SW_GATE_BIT = 0x20,
	DAC1_UNIPOLAR_BIT = 0x8,
	DAC0_UNIPOLAR_BIT = 0x2,
पूर्ण;

/* bit definitions क्रम पढ़ो-only रेजिस्टरs */
क्रमागत hw_status_contents अणु
	DAC_UNDERRUN_BIT = 0x1,
	ADC_OVERRUN_BIT = 0x2,
	DAC_ACTIVE_BIT = 0x4,
	ADC_ACTIVE_BIT = 0x8,
	DAC_INTR_PENDING_BIT = 0x10,
	ADC_INTR_PENDING_BIT = 0x20,
	DAC_DONE_BIT = 0x40,
	ADC_DONE_BIT = 0x80,
	EXT_INTR_PENDING_BIT = 0x100,
	ADC_STOP_BIT = 0x200,
पूर्ण;

अटल अंतरभूत u16 pipe_full_bits(u16 hw_status_bits)
अणु
	वापस (hw_status_bits >> 10) & 0x3;
पूर्ण;

अटल अंतरभूत अचिन्हित पूर्णांक dma_chain_flag_bits(u16 prepost_bits)
अणु
	वापस (prepost_bits >> 6) & 0x3;
पूर्ण

अटल अंतरभूत अचिन्हित पूर्णांक adc_upper_पढ़ो_ptr_code(u16 prepost_bits)
अणु
	वापस (prepost_bits >> 12) & 0x3;
पूर्ण

अटल अंतरभूत अचिन्हित पूर्णांक adc_upper_ग_लिखो_ptr_code(u16 prepost_bits)
अणु
	वापस (prepost_bits >> 14) & 0x3;
पूर्ण

/* I2C addresses क्रम 4020 */
क्रमागत i2c_addresses अणु
	RANGE_CAL_I2C_ADDR = 0x20,
	CALDAC0_I2C_ADDR = 0xc,
	CALDAC1_I2C_ADDR = 0xd,
पूर्ण;

क्रमागत range_cal_i2c_contents अणु
	/* bits that set what source the adc converter measures */
	ADC_SRC_4020_MASK = 0x70,
	/* make bnc trig/ext घड़ी threshold 0V instead of 2.5V */
	BNC_TRIG_THRESHOLD_0V_BIT = 0x80,
पूर्ण;

अटल अंतरभूत u8 adc_src_4020_bits(अचिन्हित पूर्णांक source)
अणु
	वापस (source << 4) & ADC_SRC_4020_MASK;
पूर्ण;

अटल अंतरभूत u8 attenuate_bit(अचिन्हित पूर्णांक channel)
अणु
	/* attenuate channel (+-5V input range) */
	वापस 1 << (channel & 0x3);
पूर्ण;

/* analog input ranges क्रम 64xx boards */
अटल स्थिर काष्ठा comedi_lrange ai_ranges_64xx = अणु
	8, अणु
		BIP_RANGE(10),
		BIP_RANGE(5),
		BIP_RANGE(2.5),
		BIP_RANGE(1.25),
		UNI_RANGE(10),
		UNI_RANGE(5),
		UNI_RANGE(2.5),
		UNI_RANGE(1.25)
	पूर्ण
पूर्ण;

अटल स्थिर u8 ai_range_code_64xx[8] = अणु
	0x0, 0x1, 0x2, 0x3,	/* bipolar 10, 5, 2,5, 1.25 */
	0x8, 0x9, 0xa, 0xb	/* unipolar 10, 5, 2.5, 1.25 */
पूर्ण;

/* analog input ranges क्रम 64-Mx boards */
अटल स्थिर काष्ठा comedi_lrange ai_ranges_64_mx = अणु
	7, अणु
		BIP_RANGE(5),
		BIP_RANGE(2.5),
		BIP_RANGE(1.25),
		BIP_RANGE(0.625),
		UNI_RANGE(5),
		UNI_RANGE(2.5),
		UNI_RANGE(1.25)
	पूर्ण
पूर्ण;

अटल स्थिर u8 ai_range_code_64_mx[7] = अणु
	0x0, 0x1, 0x2, 0x3,	/* bipolar 5, 2.5, 1.25, 0.625 */
	0x9, 0xa, 0xb		/* unipolar 5, 2.5, 1.25 */
पूर्ण;

/* analog input ranges क्रम 60xx boards */
अटल स्थिर काष्ठा comedi_lrange ai_ranges_60xx = अणु
	4, अणु
		BIP_RANGE(10),
		BIP_RANGE(5),
		BIP_RANGE(0.5),
		BIP_RANGE(0.05)
	पूर्ण
पूर्ण;

अटल स्थिर u8 ai_range_code_60xx[4] = अणु
	0x0, 0x1, 0x4, 0x7	/* bipolar 10, 5, 0.5, 0.05 */
पूर्ण;

/* analog input ranges क्रम 6030, etc boards */
अटल स्थिर काष्ठा comedi_lrange ai_ranges_6030 = अणु
	14, अणु
		BIP_RANGE(10),
		BIP_RANGE(5),
		BIP_RANGE(2),
		BIP_RANGE(1),
		BIP_RANGE(0.5),
		BIP_RANGE(0.2),
		BIP_RANGE(0.1),
		UNI_RANGE(10),
		UNI_RANGE(5),
		UNI_RANGE(2),
		UNI_RANGE(1),
		UNI_RANGE(0.5),
		UNI_RANGE(0.2),
		UNI_RANGE(0.1)
	पूर्ण
पूर्ण;

अटल स्थिर u8 ai_range_code_6030[14] = अणु
	0x0, 0x1, 0x2, 0x3, 0x4, 0x5, 0x6, /* bip 10, 5, 2, 1, 0.5, 0.2, 0.1 */
	0x9, 0xa, 0xb, 0xc, 0xd, 0xe, 0xf  /* uni 10, 5, 2, 1, 0.5, 0.2, 0.1 */
पूर्ण;

/* analog input ranges क्रम 6052, etc boards */
अटल स्थिर काष्ठा comedi_lrange ai_ranges_6052 = अणु
	15, अणु
		BIP_RANGE(10),
		BIP_RANGE(5),
		BIP_RANGE(2.5),
		BIP_RANGE(1),
		BIP_RANGE(0.5),
		BIP_RANGE(0.25),
		BIP_RANGE(0.1),
		BIP_RANGE(0.05),
		UNI_RANGE(10),
		UNI_RANGE(5),
		UNI_RANGE(2),
		UNI_RANGE(1),
		UNI_RANGE(0.5),
		UNI_RANGE(0.2),
		UNI_RANGE(0.1)
	पूर्ण
पूर्ण;

अटल स्थिर u8 ai_range_code_6052[15] = अणु
	0x0, 0x1, 0x2, 0x3, 0x4, 0x5, 0x6, 0x7,	/* bipolar 10 ... 0.05 */
	0x9, 0xa, 0xb, 0xc, 0xd, 0xe, 0xf	/* unipolar 10 ... 0.1 */
पूर्ण;

/* analog input ranges क्रम 4020 board */
अटल स्थिर काष्ठा comedi_lrange ai_ranges_4020 = अणु
	2, अणु
		BIP_RANGE(5),
		BIP_RANGE(1)
	पूर्ण
पूर्ण;

/* analog output ranges */
अटल स्थिर काष्ठा comedi_lrange ao_ranges_64xx = अणु
	4, अणु
		BIP_RANGE(5),
		BIP_RANGE(10),
		UNI_RANGE(5),
		UNI_RANGE(10)
	पूर्ण
पूर्ण;

अटल स्थिर पूर्णांक ao_range_code_64xx[] = अणु
	0x0,
	0x1,
	0x2,
	0x3,
पूर्ण;

अटल स्थिर पूर्णांक ao_range_code_60xx[] = अणु
	0x0,
पूर्ण;

अटल स्थिर काष्ठा comedi_lrange ao_ranges_6030 = अणु
	2, अणु
		BIP_RANGE(10),
		UNI_RANGE(10)
	पूर्ण
पूर्ण;

अटल स्थिर पूर्णांक ao_range_code_6030[] = अणु
	0x0,
	0x2,
पूर्ण;

अटल स्थिर काष्ठा comedi_lrange ao_ranges_4020 = अणु
	2, अणु
		BIP_RANGE(5),
		BIP_RANGE(10)
	पूर्ण
पूर्ण;

अटल स्थिर पूर्णांक ao_range_code_4020[] = अणु
	0x1,
	0x0,
पूर्ण;

क्रमागत रेजिस्टर_layout अणु
	LAYOUT_60XX,
	LAYOUT_64XX,
	LAYOUT_4020,
पूर्ण;

काष्ठा hw_fअगरo_info अणु
	अचिन्हित पूर्णांक num_segments;
	अचिन्हित पूर्णांक max_segment_length;
	अचिन्हित पूर्णांक sample_packing_ratio;
	u16 fअगरo_size_reg_mask;
पूर्ण;

क्रमागत pcidas64_boardid अणु
	BOARD_PCIDAS6402_16,
	BOARD_PCIDAS6402_12,
	BOARD_PCIDAS64_M1_16,
	BOARD_PCIDAS64_M2_16,
	BOARD_PCIDAS64_M3_16,
	BOARD_PCIDAS6013,
	BOARD_PCIDAS6014,
	BOARD_PCIDAS6023,
	BOARD_PCIDAS6025,
	BOARD_PCIDAS6030,
	BOARD_PCIDAS6031,
	BOARD_PCIDAS6032,
	BOARD_PCIDAS6033,
	BOARD_PCIDAS6034,
	BOARD_PCIDAS6035,
	BOARD_PCIDAS6036,
	BOARD_PCIDAS6040,
	BOARD_PCIDAS6052,
	BOARD_PCIDAS6070,
	BOARD_PCIDAS6071,
	BOARD_PCIDAS4020_12,
	BOARD_PCIDAS6402_16_JR,
	BOARD_PCIDAS64_M1_16_JR,
	BOARD_PCIDAS64_M2_16_JR,
	BOARD_PCIDAS64_M3_16_JR,
	BOARD_PCIDAS64_M1_14,
	BOARD_PCIDAS64_M2_14,
	BOARD_PCIDAS64_M3_14,
पूर्ण;

काष्ठा pcidas64_board अणु
	स्थिर अक्षर *name;
	पूर्णांक ai_se_chans;	/* number of ai inमाला_दो in single-ended mode */
	पूर्णांक ai_bits;		/* analog input resolution */
	पूर्णांक ai_speed;		/* fastest conversion period in ns */
	स्थिर काष्ठा comedi_lrange *ai_range_table;
	स्थिर u8 *ai_range_code;
	पूर्णांक ao_nchan;		/* number of analog out channels */
	पूर्णांक ao_bits;		/* analog output resolution */
	पूर्णांक ao_scan_speed;	/* analog output scan speed */
	स्थिर काष्ठा comedi_lrange *ao_range_table;
	स्थिर पूर्णांक *ao_range_code;
	स्थिर काष्ठा hw_fअगरo_info *स्थिर ai_fअगरo;
	/* dअगरferent board families have slightly dअगरferent रेजिस्टरs */
	क्रमागत रेजिस्टर_layout layout;
	अचिन्हित has_8255:1;
पूर्ण;

अटल स्थिर काष्ठा hw_fअगरo_info ai_fअगरo_4020 = अणु
	.num_segments = 2,
	.max_segment_length = 0x8000,
	.sample_packing_ratio = 2,
	.fअगरo_size_reg_mask = 0x7f,
पूर्ण;

अटल स्थिर काष्ठा hw_fअगरo_info ai_fअगरo_64xx = अणु
	.num_segments = 4,
	.max_segment_length = 0x800,
	.sample_packing_ratio = 1,
	.fअगरo_size_reg_mask = 0x3f,
पूर्ण;

अटल स्थिर काष्ठा hw_fअगरo_info ai_fअगरo_60xx = अणु
	.num_segments = 4,
	.max_segment_length = 0x800,
	.sample_packing_ratio = 1,
	.fअगरo_size_reg_mask = 0x7f,
पूर्ण;

/*
 * maximum number of dma transfers we will chain together पूर्णांकo a ring
 * (and the maximum number of dma buffers we मुख्यtain)
 */
#घोषणा MAX_AI_DMA_RING_COUNT (0x80000 / DMA_BUFFER_SIZE)
#घोषणा MIN_AI_DMA_RING_COUNT (0x10000 / DMA_BUFFER_SIZE)
#घोषणा AO_DMA_RING_COUNT (0x10000 / DMA_BUFFER_SIZE)
अटल अंतरभूत अचिन्हित पूर्णांक ai_dma_ring_count(स्थिर काष्ठा pcidas64_board *board)
अणु
	अगर (board->layout == LAYOUT_4020)
		वापस MAX_AI_DMA_RING_COUNT;

	वापस MIN_AI_DMA_RING_COUNT;
पूर्ण

अटल स्थिर पूर्णांक bytes_in_sample = 2;

अटल स्थिर काष्ठा pcidas64_board pcidas64_boards[] = अणु
	[BOARD_PCIDAS6402_16] = अणु
		.name		= "pci-das6402/16",
		.ai_se_chans	= 64,
		.ai_bits	= 16,
		.ai_speed	= 5000,
		.ao_nchan	= 2,
		.ao_bits	= 16,
		.ao_scan_speed	= 10000,
		.layout		= LAYOUT_64XX,
		.ai_range_table	= &ai_ranges_64xx,
		.ai_range_code	= ai_range_code_64xx,
		.ao_range_table	= &ao_ranges_64xx,
		.ao_range_code	= ao_range_code_64xx,
		.ai_fअगरo	= &ai_fअगरo_64xx,
		.has_8255	= 1,
	पूर्ण,
	[BOARD_PCIDAS6402_12] = अणु
		.name		= "pci-das6402/12",	/* XXX check */
		.ai_se_chans	= 64,
		.ai_bits	= 12,
		.ai_speed	= 5000,
		.ao_nchan	= 2,
		.ao_bits	= 12,
		.ao_scan_speed	= 10000,
		.layout		= LAYOUT_64XX,
		.ai_range_table	= &ai_ranges_64xx,
		.ai_range_code	= ai_range_code_64xx,
		.ao_range_table	= &ao_ranges_64xx,
		.ao_range_code	= ao_range_code_64xx,
		.ai_fअगरo	= &ai_fअगरo_64xx,
		.has_8255	= 1,
	पूर्ण,
	[BOARD_PCIDAS64_M1_16] = अणु
		.name		= "pci-das64/m1/16",
		.ai_se_chans	= 64,
		.ai_bits	= 16,
		.ai_speed	= 1000,
		.ao_nchan	= 2,
		.ao_bits	= 16,
		.ao_scan_speed	= 10000,
		.layout		= LAYOUT_64XX,
		.ai_range_table	= &ai_ranges_64_mx,
		.ai_range_code	= ai_range_code_64_mx,
		.ao_range_table	= &ao_ranges_64xx,
		.ao_range_code	= ao_range_code_64xx,
		.ai_fअगरo	= &ai_fअगरo_64xx,
		.has_8255	= 1,
	पूर्ण,
	[BOARD_PCIDAS64_M2_16] = अणु
		.name = "pci-das64/m2/16",
		.ai_se_chans	= 64,
		.ai_bits	= 16,
		.ai_speed	= 500,
		.ao_nchan	= 2,
		.ao_bits	= 16,
		.ao_scan_speed	= 10000,
		.layout		= LAYOUT_64XX,
		.ai_range_table	= &ai_ranges_64_mx,
		.ai_range_code	= ai_range_code_64_mx,
		.ao_range_table	= &ao_ranges_64xx,
		.ao_range_code	= ao_range_code_64xx,
		.ai_fअगरo	= &ai_fअगरo_64xx,
		.has_8255	= 1,
	पूर्ण,
	[BOARD_PCIDAS64_M3_16] = अणु
		.name		= "pci-das64/m3/16",
		.ai_se_chans	= 64,
		.ai_bits	= 16,
		.ai_speed	= 333,
		.ao_nchan	= 2,
		.ao_bits	= 16,
		.ao_scan_speed	= 10000,
		.layout		= LAYOUT_64XX,
		.ai_range_table	= &ai_ranges_64_mx,
		.ai_range_code	= ai_range_code_64_mx,
		.ao_range_table	= &ao_ranges_64xx,
		.ao_range_code	= ao_range_code_64xx,
		.ai_fअगरo	= &ai_fअगरo_64xx,
		.has_8255	= 1,
	पूर्ण,
	[BOARD_PCIDAS6013] = अणु
		.name		= "pci-das6013",
		.ai_se_chans	= 16,
		.ai_bits	= 16,
		.ai_speed	= 5000,
		.ao_nchan	= 0,
		.ao_bits	= 16,
		.layout		= LAYOUT_60XX,
		.ai_range_table	= &ai_ranges_60xx,
		.ai_range_code	= ai_range_code_60xx,
		.ao_range_table	= &range_bipolar10,
		.ao_range_code	= ao_range_code_60xx,
		.ai_fअगरo	= &ai_fअगरo_60xx,
		.has_8255	= 0,
	पूर्ण,
	[BOARD_PCIDAS6014] = अणु
		.name		= "pci-das6014",
		.ai_se_chans	= 16,
		.ai_bits	= 16,
		.ai_speed	= 5000,
		.ao_nchan	= 2,
		.ao_bits	= 16,
		.ao_scan_speed	= 100000,
		.layout		= LAYOUT_60XX,
		.ai_range_table	= &ai_ranges_60xx,
		.ai_range_code	= ai_range_code_60xx,
		.ao_range_table	= &range_bipolar10,
		.ao_range_code	= ao_range_code_60xx,
		.ai_fअगरo	= &ai_fअगरo_60xx,
		.has_8255	= 0,
	पूर्ण,
	[BOARD_PCIDAS6023] = अणु
		.name		= "pci-das6023",
		.ai_se_chans	= 16,
		.ai_bits	= 12,
		.ai_speed	= 5000,
		.ao_nchan	= 0,
		.ao_scan_speed	= 100000,
		.layout		= LAYOUT_60XX,
		.ai_range_table	= &ai_ranges_60xx,
		.ai_range_code	= ai_range_code_60xx,
		.ao_range_table	= &range_bipolar10,
		.ao_range_code	= ao_range_code_60xx,
		.ai_fअगरo	= &ai_fअगरo_60xx,
		.has_8255	= 1,
	पूर्ण,
	[BOARD_PCIDAS6025] = अणु
		.name		= "pci-das6025",
		.ai_se_chans	= 16,
		.ai_bits	= 12,
		.ai_speed	= 5000,
		.ao_nchan	= 2,
		.ao_bits	= 12,
		.ao_scan_speed	= 100000,
		.layout		= LAYOUT_60XX,
		.ai_range_table	= &ai_ranges_60xx,
		.ai_range_code	= ai_range_code_60xx,
		.ao_range_table	= &range_bipolar10,
		.ao_range_code	= ao_range_code_60xx,
		.ai_fअगरo	= &ai_fअगरo_60xx,
		.has_8255	= 1,
	पूर्ण,
	[BOARD_PCIDAS6030] = अणु
		.name		= "pci-das6030",
		.ai_se_chans	= 16,
		.ai_bits	= 16,
		.ai_speed	= 10000,
		.ao_nchan	= 2,
		.ao_bits	= 16,
		.ao_scan_speed	= 10000,
		.layout		= LAYOUT_60XX,
		.ai_range_table	= &ai_ranges_6030,
		.ai_range_code	= ai_range_code_6030,
		.ao_range_table	= &ao_ranges_6030,
		.ao_range_code	= ao_range_code_6030,
		.ai_fअगरo	= &ai_fअगरo_60xx,
		.has_8255	= 0,
	पूर्ण,
	[BOARD_PCIDAS6031] = अणु
		.name		= "pci-das6031",
		.ai_se_chans	= 64,
		.ai_bits	= 16,
		.ai_speed	= 10000,
		.ao_nchan	= 2,
		.ao_bits	= 16,
		.ao_scan_speed	= 10000,
		.layout		= LAYOUT_60XX,
		.ai_range_table	= &ai_ranges_6030,
		.ai_range_code	= ai_range_code_6030,
		.ao_range_table	= &ao_ranges_6030,
		.ao_range_code	= ao_range_code_6030,
		.ai_fअगरo	= &ai_fअगरo_60xx,
		.has_8255	= 0,
	पूर्ण,
	[BOARD_PCIDAS6032] = अणु
		.name		= "pci-das6032",
		.ai_se_chans	= 16,
		.ai_bits	= 16,
		.ai_speed	= 10000,
		.ao_nchan	= 0,
		.layout		= LAYOUT_60XX,
		.ai_range_table	= &ai_ranges_6030,
		.ai_range_code	= ai_range_code_6030,
		.ai_fअगरo	= &ai_fअगरo_60xx,
		.has_8255	= 0,
	पूर्ण,
	[BOARD_PCIDAS6033] = अणु
		.name		= "pci-das6033",
		.ai_se_chans	= 64,
		.ai_bits	= 16,
		.ai_speed	= 10000,
		.ao_nchan	= 0,
		.layout		= LAYOUT_60XX,
		.ai_range_table	= &ai_ranges_6030,
		.ai_range_code	= ai_range_code_6030,
		.ai_fअगरo	= &ai_fअगरo_60xx,
		.has_8255	= 0,
	पूर्ण,
	[BOARD_PCIDAS6034] = अणु
		.name		= "pci-das6034",
		.ai_se_chans	= 16,
		.ai_bits	= 16,
		.ai_speed	= 5000,
		.ao_nchan	= 0,
		.ao_scan_speed	= 0,
		.layout		= LAYOUT_60XX,
		.ai_range_table	= &ai_ranges_60xx,
		.ai_range_code	= ai_range_code_60xx,
		.ai_fअगरo	= &ai_fअगरo_60xx,
		.has_8255	= 0,
	पूर्ण,
	[BOARD_PCIDAS6035] = अणु
		.name		= "pci-das6035",
		.ai_se_chans	= 16,
		.ai_bits	= 16,
		.ai_speed	= 5000,
		.ao_nchan	= 2,
		.ao_bits	= 12,
		.ao_scan_speed	= 100000,
		.layout		= LAYOUT_60XX,
		.ai_range_table	= &ai_ranges_60xx,
		.ai_range_code	= ai_range_code_60xx,
		.ao_range_table	= &range_bipolar10,
		.ao_range_code	= ao_range_code_60xx,
		.ai_fअगरo	= &ai_fअगरo_60xx,
		.has_8255	= 0,
	पूर्ण,
	[BOARD_PCIDAS6036] = अणु
		.name		= "pci-das6036",
		.ai_se_chans	= 16,
		.ai_bits	= 16,
		.ai_speed	= 5000,
		.ao_nchan	= 2,
		.ao_bits	= 16,
		.ao_scan_speed	= 100000,
		.layout		= LAYOUT_60XX,
		.ai_range_table	= &ai_ranges_60xx,
		.ai_range_code	= ai_range_code_60xx,
		.ao_range_table	= &range_bipolar10,
		.ao_range_code	= ao_range_code_60xx,
		.ai_fअगरo	= &ai_fअगरo_60xx,
		.has_8255	= 0,
	पूर्ण,
	[BOARD_PCIDAS6040] = अणु
		.name		= "pci-das6040",
		.ai_se_chans	= 16,
		.ai_bits	= 12,
		.ai_speed	= 2000,
		.ao_nchan	= 2,
		.ao_bits	= 12,
		.ao_scan_speed	= 1000,
		.layout		= LAYOUT_60XX,
		.ai_range_table	= &ai_ranges_6052,
		.ai_range_code	= ai_range_code_6052,
		.ao_range_table	= &ao_ranges_6030,
		.ao_range_code	= ao_range_code_6030,
		.ai_fअगरo	= &ai_fअगरo_60xx,
		.has_8255	= 0,
	पूर्ण,
	[BOARD_PCIDAS6052] = अणु
		.name		= "pci-das6052",
		.ai_se_chans	= 16,
		.ai_bits	= 16,
		.ai_speed	= 3333,
		.ao_nchan	= 2,
		.ao_bits	= 16,
		.ao_scan_speed	= 3333,
		.layout		= LAYOUT_60XX,
		.ai_range_table	= &ai_ranges_6052,
		.ai_range_code	= ai_range_code_6052,
		.ao_range_table	= &ao_ranges_6030,
		.ao_range_code	= ao_range_code_6030,
		.ai_fअगरo	= &ai_fअगरo_60xx,
		.has_8255	= 0,
	पूर्ण,
	[BOARD_PCIDAS6070] = अणु
		.name		= "pci-das6070",
		.ai_se_chans	= 16,
		.ai_bits	= 12,
		.ai_speed	= 800,
		.ao_nchan	= 2,
		.ao_bits	= 12,
		.ao_scan_speed	= 1000,
		.layout		= LAYOUT_60XX,
		.ai_range_table	= &ai_ranges_6052,
		.ai_range_code	= ai_range_code_6052,
		.ao_range_table	= &ao_ranges_6030,
		.ao_range_code	= ao_range_code_6030,
		.ai_fअगरo	= &ai_fअगरo_60xx,
		.has_8255	= 0,
	पूर्ण,
	[BOARD_PCIDAS6071] = अणु
		.name		= "pci-das6071",
		.ai_se_chans	= 64,
		.ai_bits	= 12,
		.ai_speed	= 800,
		.ao_nchan	= 2,
		.ao_bits	= 12,
		.ao_scan_speed	= 1000,
		.layout		= LAYOUT_60XX,
		.ai_range_table	= &ai_ranges_6052,
		.ai_range_code	= ai_range_code_6052,
		.ao_range_table	= &ao_ranges_6030,
		.ao_range_code	= ao_range_code_6030,
		.ai_fअगरo	= &ai_fअगरo_60xx,
		.has_8255	= 0,
	पूर्ण,
	[BOARD_PCIDAS4020_12] = अणु
		.name		= "pci-das4020/12",
		.ai_se_chans	= 4,
		.ai_bits	= 12,
		.ai_speed	= 50,
		.ao_bits	= 12,
		.ao_nchan	= 2,
		.ao_scan_speed	= 0,	/* no hardware pacing on ao */
		.layout		= LAYOUT_4020,
		.ai_range_table	= &ai_ranges_4020,
		.ao_range_table	= &ao_ranges_4020,
		.ao_range_code	= ao_range_code_4020,
		.ai_fअगरo	= &ai_fअगरo_4020,
		.has_8255	= 1,
	पूर्ण,
#अगर 0
	/* The device id क्रम these boards is unknown */

	[BOARD_PCIDAS6402_16_JR] = अणु
		.name		= "pci-das6402/16/jr",
		.ai_se_chans	= 64,
		.ai_bits	= 16,
		.ai_speed	= 5000,
		.ao_nchan	= 0,
		.ao_scan_speed	= 10000,
		.layout		= LAYOUT_64XX,
		.ai_range_table	= &ai_ranges_64xx,
		.ai_range_code	= ai_range_code_64xx,
		.ai_fअगरo	= ai_fअगरo_64xx,
		.has_8255	= 1,
	पूर्ण,
	[BOARD_PCIDAS64_M1_16_JR] = अणु
		.name		= "pci-das64/m1/16/jr",
		.ai_se_chans	= 64,
		.ai_bits	= 16,
		.ai_speed	= 1000,
		.ao_nchan	= 0,
		.ao_scan_speed	= 10000,
		.layout		= LAYOUT_64XX,
		.ai_range_table	= &ai_ranges_64_mx,
		.ai_range_code	= ai_range_code_64_mx,
		.ai_fअगरo	= ai_fअगरo_64xx,
		.has_8255	= 1,
	पूर्ण,
	[BOARD_PCIDAS64_M2_16_JR] = अणु
		.name = "pci-das64/m2/16/jr",
		.ai_se_chans	= 64,
		.ai_bits	= 16,
		.ai_speed	= 500,
		.ao_nchan	= 0,
		.ao_scan_speed	= 10000,
		.layout		= LAYOUT_64XX,
		.ai_range_table	= &ai_ranges_64_mx,
		.ai_range_code	= ai_range_code_64_mx,
		.ai_fअगरo	= ai_fअगरo_64xx,
		.has_8255	= 1,
	पूर्ण,
	[BOARD_PCIDAS64_M3_16_JR] = अणु
		.name		= "pci-das64/m3/16/jr",
		.ai_se_chans	= 64,
		.ai_bits	= 16,
		.ai_speed	= 333,
		.ao_nchan	= 0,
		.ao_scan_speed	= 10000,
		.layout		= LAYOUT_64XX,
		.ai_range_table	= &ai_ranges_64_mx,
		.ai_range_code	= ai_range_code_64_mx,
		.ai_fअगरo	= ai_fअगरo_64xx,
		.has_8255	= 1,
	पूर्ण,
	[BOARD_PCIDAS64_M1_14] = अणु
		.name		= "pci-das64/m1/14",
		.ai_se_chans	= 64,
		.ai_bits	= 14,
		.ai_speed	= 1000,
		.ao_nchan	= 2,
		.ao_scan_speed	= 10000,
		.layout		= LAYOUT_64XX,
		.ai_range_table	= &ai_ranges_64_mx,
		.ai_range_code	= ai_range_code_64_mx,
		.ai_fअगरo	= ai_fअगरo_64xx,
		.has_8255	= 1,
	पूर्ण,
	[BOARD_PCIDAS64_M2_14] = अणु
		.name		= "pci-das64/m2/14",
		.ai_se_chans	= 64,
		.ai_bits	= 14,
		.ai_speed	= 500,
		.ao_nchan	= 2,
		.ao_scan_speed	= 10000,
		.layout		= LAYOUT_64XX,
		.ai_range_table	= &ai_ranges_64_mx,
		.ai_range_code	= ai_range_code_64_mx,
		.ai_fअगरo	= ai_fअगरo_64xx,
		.has_8255	= 1,
	पूर्ण,
	[BOARD_PCIDAS64_M3_14] = अणु
		.name		= "pci-das64/m3/14",
		.ai_se_chans	= 64,
		.ai_bits	= 14,
		.ai_speed	= 333,
		.ao_nchan	= 2,
		.ao_scan_speed	= 10000,
		.layout		= LAYOUT_64XX,
		.ai_range_table	= &ai_ranges_64_mx,
		.ai_range_code	= ai_range_code_64_mx,
		.ai_fअगरo	= ai_fअगरo_64xx,
		.has_8255	= 1,
	पूर्ण,
#पूर्ण_अगर
पूर्ण;

अटल अंतरभूत अचिन्हित लघु se_dअगरf_bit_6xxx(काष्ठा comedi_device *dev,
					      पूर्णांक use_dअगरferential)
अणु
	स्थिर काष्ठा pcidas64_board *board = dev->board_ptr;

	अगर ((board->layout == LAYOUT_64XX && !use_dअगरferential) ||
	    (board->layout == LAYOUT_60XX && use_dअगरferential))
		वापस ADC_SE_DIFF_BIT;

	वापस 0;
पूर्ण

काष्ठा ext_घड़ी_info अणु
	/* master घड़ी भागisor to use क्रम scans with बाह्यal master घड़ी */
	अचिन्हित पूर्णांक भागisor;
	/* chanspec क्रम master घड़ी input when used as scan begin src */
	अचिन्हित पूर्णांक chanspec;
पूर्ण;

/* this काष्ठाure is क्रम data unique to this hardware driver. */
काष्ठा pcidas64_निजी अणु
	/* base addresses (physical) */
	resource_माप_प्रकार मुख्य_phys_iobase;
	resource_माप_प्रकार dio_counter_phys_iobase;
	/* base addresses (ioremapped) */
	व्योम __iomem *plx9080_iobase;
	व्योम __iomem *मुख्य_iobase;
	/* local address (used by dma controller) */
	u32 local0_iobase;
	u32 local1_iobase;
	/* dma buffers क्रम analog input */
	u16 *ai_buffer[MAX_AI_DMA_RING_COUNT];
	/* physical addresses of ai dma buffers */
	dma_addr_t ai_buffer_bus_addr[MAX_AI_DMA_RING_COUNT];
	/*
	 * array of ai dma descriptors पढ़ो by plx9080,
	 * allocated to get proper alignment
	 */
	काष्ठा plx_dma_desc *ai_dma_desc;
	/* physical address of ai dma descriptor array */
	dma_addr_t ai_dma_desc_bus_addr;
	/*
	 * index of the ai dma descriptor/buffer
	 * that is currently being used
	 */
	अचिन्हित पूर्णांक ai_dma_index;
	/* dma buffers क्रम analog output */
	u16 *ao_buffer[AO_DMA_RING_COUNT];
	/* physical addresses of ao dma buffers */
	dma_addr_t ao_buffer_bus_addr[AO_DMA_RING_COUNT];
	काष्ठा plx_dma_desc *ao_dma_desc;
	dma_addr_t ao_dma_desc_bus_addr;
	/* keeps track of buffer where the next ao sample should go */
	अचिन्हित पूर्णांक ao_dma_index;
	अचिन्हित पूर्णांक hw_revision;	/* stc chip hardware revision number */
	/* last bits sent to INTR_ENABLE_REG रेजिस्टर */
	अचिन्हित पूर्णांक पूर्णांकr_enable_bits;
	/* last bits sent to ADC_CONTROL1_REG रेजिस्टर */
	u16 adc_control1_bits;
	/* last bits sent to FIFO_SIZE_REG रेजिस्टर */
	u16 fअगरo_size_bits;
	/* last bits sent to HW_CONFIG_REG रेजिस्टर */
	u16 hw_config_bits;
	u16 dac_control1_bits;
	/* last bits written to plx9080 control रेजिस्टर */
	u32 plx_control_bits;
	/* last bits written to plx पूर्णांकerrupt control and status रेजिस्टर */
	u32 plx_पूर्णांकcsr_bits;
	/* index of calibration source पढ़ोable through ai ch0 */
	पूर्णांक calibration_source;
	/* bits written to i2c calibration/range रेजिस्टर */
	u8 i2c_cal_range_bits;
	/* configure digital triggers to trigger on falling edge */
	अचिन्हित पूर्णांक ext_trig_falling;
	लघु ai_cmd_running;
	अचिन्हित पूर्णांक ai_fअगरo_segment_length;
	काष्ठा ext_घड़ी_info ext_घड़ी;
	अचिन्हित लघु ao_bounce_buffer[DAC_FIFO_SIZE];
पूर्ण;

अटल अचिन्हित पूर्णांक ai_range_bits_6xxx(स्थिर काष्ठा comedi_device *dev,
				       अचिन्हित पूर्णांक range_index)
अणु
	स्थिर काष्ठा pcidas64_board *board = dev->board_ptr;

	वापस board->ai_range_code[range_index] << 8;
पूर्ण

अटल अचिन्हित पूर्णांक hw_revision(स्थिर काष्ठा comedi_device *dev,
				u16 hw_status_bits)
अणु
	स्थिर काष्ठा pcidas64_board *board = dev->board_ptr;

	अगर (board->layout == LAYOUT_4020)
		वापस (hw_status_bits >> 13) & 0x7;

	वापस (hw_status_bits >> 12) & 0xf;
पूर्ण

अटल व्योम set_dac_range_bits(काष्ठा comedi_device *dev,
			       u16 *bits, अचिन्हित पूर्णांक channel,
			       अचिन्हित पूर्णांक range)
अणु
	स्थिर काष्ठा pcidas64_board *board = dev->board_ptr;
	अचिन्हित पूर्णांक code = board->ao_range_code[range];

	अगर (channel > 1)
		dev_err(dev->class_dev, "bug! bad channel?\n");
	अगर (code & ~0x3)
		dev_err(dev->class_dev, "bug! bad range code?\n");

	*bits &= ~(0x3 << (2 * channel));
	*bits |= code << (2 * channel);
पूर्ण;

अटल अंतरभूत पूर्णांक ao_cmd_is_supported(स्थिर काष्ठा pcidas64_board *board)
अणु
	वापस board->ao_nchan && board->layout != LAYOUT_4020;
पूर्ण

अटल व्योम पात_dma(काष्ठा comedi_device *dev, अचिन्हित पूर्णांक channel)
अणु
	काष्ठा pcidas64_निजी *devpriv = dev->निजी;
	अचिन्हित दीर्घ flags;

	/* spinlock क्रम plx dma control/status reg */
	spin_lock_irqsave(&dev->spinlock, flags);

	plx9080_पात_dma(devpriv->plx9080_iobase, channel);

	spin_unlock_irqrestore(&dev->spinlock, flags);
पूर्ण

अटल व्योम disable_plx_पूर्णांकerrupts(काष्ठा comedi_device *dev)
अणु
	काष्ठा pcidas64_निजी *devpriv = dev->निजी;

	devpriv->plx_पूर्णांकcsr_bits = 0;
	ग_लिखोl(devpriv->plx_पूर्णांकcsr_bits,
	       devpriv->plx9080_iobase + PLX_REG_INTCSR);
पूर्ण

अटल व्योम disable_ai_पूर्णांकerrupts(काष्ठा comedi_device *dev)
अणु
	काष्ठा pcidas64_निजी *devpriv = dev->निजी;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&dev->spinlock, flags);
	devpriv->पूर्णांकr_enable_bits &=
		~EN_ADC_INTR_SRC_BIT & ~EN_ADC_DONE_INTR_BIT &
		~EN_ADC_ACTIVE_INTR_BIT & ~EN_ADC_STOP_INTR_BIT &
		~EN_ADC_OVERRUN_BIT & ~ADC_INTR_SRC_MASK;
	ग_लिखोw(devpriv->पूर्णांकr_enable_bits,
	       devpriv->मुख्य_iobase + INTR_ENABLE_REG);
	spin_unlock_irqrestore(&dev->spinlock, flags);
पूर्ण

अटल व्योम enable_ai_पूर्णांकerrupts(काष्ठा comedi_device *dev,
				 स्थिर काष्ठा comedi_cmd *cmd)
अणु
	स्थिर काष्ठा pcidas64_board *board = dev->board_ptr;
	काष्ठा pcidas64_निजी *devpriv = dev->निजी;
	u32 bits;
	अचिन्हित दीर्घ flags;

	bits = EN_ADC_OVERRUN_BIT | EN_ADC_DONE_INTR_BIT |
	       EN_ADC_ACTIVE_INTR_BIT | EN_ADC_STOP_INTR_BIT;
	/*
	 * Use pio transfer and पूर्णांकerrupt on end of conversion
	 * अगर CMDF_WAKE_EOS flag is set.
	 */
	अगर (cmd->flags & CMDF_WAKE_EOS) अणु
		/* 4020 करोesn't support pio transfers except क्रम fअगरo dregs */
		अगर (board->layout != LAYOUT_4020)
			bits |= ADC_INTR_EOSCAN_BITS | EN_ADC_INTR_SRC_BIT;
	पूर्ण
	spin_lock_irqsave(&dev->spinlock, flags);
	devpriv->पूर्णांकr_enable_bits |= bits;
	ग_लिखोw(devpriv->पूर्णांकr_enable_bits,
	       devpriv->मुख्य_iobase + INTR_ENABLE_REG);
	spin_unlock_irqrestore(&dev->spinlock, flags);
पूर्ण

/* initialize plx9080 chip */
अटल व्योम init_plx9080(काष्ठा comedi_device *dev)
अणु
	स्थिर काष्ठा pcidas64_board *board = dev->board_ptr;
	काष्ठा pcidas64_निजी *devpriv = dev->निजी;
	u32 bits;
	व्योम __iomem *plx_iobase = devpriv->plx9080_iobase;

	devpriv->plx_control_bits =
		पढ़ोl(devpriv->plx9080_iobase + PLX_REG_CNTRL);

#अगर_घोषित __BIG_ENDIAN
	bits = PLX_BIGEND_DMA0 | PLX_BIGEND_DMA1;
#अन्यथा
	bits = 0;
#पूर्ण_अगर
	ग_लिखोl(bits, devpriv->plx9080_iobase + PLX_REG_BIGEND);

	disable_plx_पूर्णांकerrupts(dev);

	पात_dma(dev, 0);
	पात_dma(dev, 1);

	/* configure dma0 mode */
	bits = 0;
	/* enable पढ़ोy input, not sure अगर this is necessary */
	bits |= PLX_DMAMODE_READYIEN;
	/* enable bterm, not sure अगर this is necessary */
	bits |= PLX_DMAMODE_BTERMIEN;
	/* enable dma chaining */
	bits |= PLX_DMAMODE_CHAINEN;
	/*
	 * enable पूर्णांकerrupt on dma करोne
	 * (probably करोn't need this, since chain never finishes)
	 */
	bits |= PLX_DMAMODE_DONEIEN;
	/*
	 * करोn't increment local address during transfers
	 * (we are transferring from a fixed fअगरo रेजिस्टर)
	 */
	bits |= PLX_DMAMODE_LACONST;
	/* route dma पूर्णांकerrupt to pci bus */
	bits |= PLX_DMAMODE_INTRPCI;
	/* enable demand mode */
	bits |= PLX_DMAMODE_DEMAND;
	/* enable local burst mode */
	bits |= PLX_DMAMODE_BURSTEN;
	/* 4020 uses 32 bit dma */
	अगर (board->layout == LAYOUT_4020)
		bits |= PLX_DMAMODE_WIDTH_32;
	अन्यथा				/* localspace0 bus is 16 bits wide */
		bits |= PLX_DMAMODE_WIDTH_16;
	ग_लिखोl(bits, plx_iobase + PLX_REG_DMAMODE1);
	अगर (ao_cmd_is_supported(board))
		ग_लिखोl(bits, plx_iobase + PLX_REG_DMAMODE0);

	/* enable पूर्णांकerrupts on plx 9080 */
	devpriv->plx_पूर्णांकcsr_bits |=
	    PLX_INTCSR_LSEABORTEN | PLX_INTCSR_LSEPARITYEN | PLX_INTCSR_PIEN |
	    PLX_INTCSR_PLIEN | PLX_INTCSR_PABORTIEN | PLX_INTCSR_LIOEN |
	    PLX_INTCSR_DMA0IEN | PLX_INTCSR_DMA1IEN;
	ग_लिखोl(devpriv->plx_पूर्णांकcsr_bits,
	       devpriv->plx9080_iobase + PLX_REG_INTCSR);
पूर्ण

अटल व्योम disable_ai_pacing(काष्ठा comedi_device *dev)
अणु
	काष्ठा pcidas64_निजी *devpriv = dev->निजी;
	अचिन्हित दीर्घ flags;

	disable_ai_पूर्णांकerrupts(dev);

	spin_lock_irqsave(&dev->spinlock, flags);
	devpriv->adc_control1_bits &= ~ADC_SW_GATE_BIT;
	ग_लिखोw(devpriv->adc_control1_bits,
	       devpriv->मुख्य_iobase + ADC_CONTROL1_REG);
	spin_unlock_irqrestore(&dev->spinlock, flags);

	/* disable pacing, triggering, etc */
	ग_लिखोw(ADC_DMA_DISABLE_BIT | ADC_SOFT_GATE_BITS | ADC_GATE_LEVEL_BIT,
	       devpriv->मुख्य_iobase + ADC_CONTROL0_REG);
पूर्ण

अटल पूर्णांक set_ai_fअगरo_segment_length(काष्ठा comedi_device *dev,
				      अचिन्हित पूर्णांक num_entries)
अणु
	स्थिर काष्ठा pcidas64_board *board = dev->board_ptr;
	काष्ठा pcidas64_निजी *devpriv = dev->निजी;
	अटल स्थिर पूर्णांक increment_size = 0x100;
	स्थिर काष्ठा hw_fअगरo_info *स्थिर fअगरo = board->ai_fअगरo;
	अचिन्हित पूर्णांक num_increments;
	u16 bits;

	अगर (num_entries < increment_size)
		num_entries = increment_size;
	अगर (num_entries > fअगरo->max_segment_length)
		num_entries = fअगरo->max_segment_length;

	/* 1 == 256 entries, 2 == 512 entries, etc */
	num_increments = DIV_ROUND_CLOSEST(num_entries, increment_size);

	bits = (~(num_increments - 1)) & fअगरo->fअगरo_size_reg_mask;
	devpriv->fअगरo_size_bits &= ~fअगरo->fअगरo_size_reg_mask;
	devpriv->fअगरo_size_bits |= bits;
	ग_लिखोw(devpriv->fअगरo_size_bits,
	       devpriv->मुख्य_iobase + FIFO_SIZE_REG);

	devpriv->ai_fअगरo_segment_length = num_increments * increment_size;

	वापस devpriv->ai_fअगरo_segment_length;
पूर्ण

/*
 * adjusts the size of hardware fअगरo (which determines block size क्रम dma xfers)
 */
अटल पूर्णांक set_ai_fअगरo_size(काष्ठा comedi_device *dev, अचिन्हित पूर्णांक num_samples)
अणु
	स्थिर काष्ठा pcidas64_board *board = dev->board_ptr;
	अचिन्हित पूर्णांक num_fअगरo_entries;
	पूर्णांक retval;
	स्थिर काष्ठा hw_fअगरo_info *स्थिर fअगरo = board->ai_fअगरo;

	num_fअगरo_entries = num_samples / fअगरo->sample_packing_ratio;

	retval = set_ai_fअगरo_segment_length(dev,
					    num_fअगरo_entries /
					    fअगरo->num_segments);
	अगर (retval < 0)
		वापस retval;

	वापस retval * fअगरo->num_segments * fअगरo->sample_packing_ratio;
पूर्ण

/* query length of fअगरo */
अटल अचिन्हित पूर्णांक ai_fअगरo_size(काष्ठा comedi_device *dev)
अणु
	स्थिर काष्ठा pcidas64_board *board = dev->board_ptr;
	काष्ठा pcidas64_निजी *devpriv = dev->निजी;

	वापस devpriv->ai_fअगरo_segment_length *
	       board->ai_fअगरo->num_segments *
	       board->ai_fअगरo->sample_packing_ratio;
पूर्ण

अटल व्योम init_stc_रेजिस्टरs(काष्ठा comedi_device *dev)
अणु
	स्थिर काष्ठा pcidas64_board *board = dev->board_ptr;
	काष्ठा pcidas64_निजी *devpriv = dev->निजी;
	u16 bits;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&dev->spinlock, flags);

	/*
	 * bit should be set क्रम 6025,
	 * although करोcs say boards with <= 16 chans should be cleared XXX
	 */
	अगर (1)
		devpriv->adc_control1_bits |= ADC_QUEUE_CONFIG_BIT;
	ग_लिखोw(devpriv->adc_control1_bits,
	       devpriv->मुख्य_iobase + ADC_CONTROL1_REG);

	/* 6402/16 manual says this रेजिस्टर must be initialized to 0xff? */
	ग_लिखोw(0xff, devpriv->मुख्य_iobase + ADC_SAMPLE_INTERVAL_UPPER_REG);

	bits = SLOW_DAC_BIT | DMA_CH_SELECT_BIT;
	अगर (board->layout == LAYOUT_4020)
		bits |= INTERNAL_CLOCK_4020_BITS;
	devpriv->hw_config_bits |= bits;
	ग_लिखोw(devpriv->hw_config_bits,
	       devpriv->मुख्य_iobase + HW_CONFIG_REG);

	ग_लिखोw(0, devpriv->मुख्य_iobase + DAQ_SYNC_REG);
	ग_लिखोw(0, devpriv->मुख्य_iobase + CALIBRATION_REG);

	spin_unlock_irqrestore(&dev->spinlock, flags);

	/* set fअगरos to maximum size */
	devpriv->fअगरo_size_bits |= DAC_FIFO_BITS;
	set_ai_fअगरo_segment_length(dev, board->ai_fअगरo->max_segment_length);

	devpriv->dac_control1_bits = DAC_OUTPUT_ENABLE_BIT;
	devpriv->पूर्णांकr_enable_bits =
		/* EN_DAC_INTR_SRC_BIT | DAC_INTR_QEMPTY_BITS | */
		EN_DAC_DONE_INTR_BIT | EN_DAC_UNDERRUN_BIT;
	ग_लिखोw(devpriv->पूर्णांकr_enable_bits,
	       devpriv->मुख्य_iobase + INTR_ENABLE_REG);

	disable_ai_pacing(dev);
पूर्ण;

अटल पूर्णांक alloc_and_init_dma_members(काष्ठा comedi_device *dev)
अणु
	स्थिर काष्ठा pcidas64_board *board = dev->board_ptr;
	काष्ठा pci_dev *pcidev = comedi_to_pci_dev(dev);
	काष्ठा pcidas64_निजी *devpriv = dev->निजी;
	पूर्णांक i;

	/* allocate pci dma buffers */
	क्रम (i = 0; i < ai_dma_ring_count(board); i++) अणु
		devpriv->ai_buffer[i] =
			dma_alloc_coherent(&pcidev->dev, DMA_BUFFER_SIZE,
					   &devpriv->ai_buffer_bus_addr[i],
					   GFP_KERNEL);
		अगर (!devpriv->ai_buffer[i])
			वापस -ENOMEM;
	पूर्ण
	क्रम (i = 0; i < AO_DMA_RING_COUNT; i++) अणु
		अगर (ao_cmd_is_supported(board)) अणु
			devpriv->ao_buffer[i] =
			    dma_alloc_coherent(&pcidev->dev,
					       DMA_BUFFER_SIZE,
					       &devpriv->ao_buffer_bus_addr[i],
					       GFP_KERNEL);
			अगर (!devpriv->ao_buffer[i])
				वापस -ENOMEM;
		पूर्ण
	पूर्ण
	/* allocate dma descriptors */
	devpriv->ai_dma_desc =
		dma_alloc_coherent(&pcidev->dev, माप(काष्ठा plx_dma_desc) *
				   ai_dma_ring_count(board),
				   &devpriv->ai_dma_desc_bus_addr, GFP_KERNEL);
	अगर (!devpriv->ai_dma_desc)
		वापस -ENOMEM;

	अगर (ao_cmd_is_supported(board)) अणु
		devpriv->ao_dma_desc =
			dma_alloc_coherent(&pcidev->dev,
					   माप(काष्ठा plx_dma_desc) *
					   AO_DMA_RING_COUNT,
					   &devpriv->ao_dma_desc_bus_addr,
					   GFP_KERNEL);
		अगर (!devpriv->ao_dma_desc)
			वापस -ENOMEM;
	पूर्ण
	/* initialize dma descriptors */
	क्रम (i = 0; i < ai_dma_ring_count(board); i++) अणु
		devpriv->ai_dma_desc[i].pci_start_addr =
			cpu_to_le32(devpriv->ai_buffer_bus_addr[i]);
		अगर (board->layout == LAYOUT_4020)
			devpriv->ai_dma_desc[i].local_start_addr =
				cpu_to_le32(devpriv->local1_iobase +
					    ADC_FIFO_REG);
		अन्यथा
			devpriv->ai_dma_desc[i].local_start_addr =
				cpu_to_le32(devpriv->local0_iobase +
					    ADC_FIFO_REG);
		devpriv->ai_dma_desc[i].transfer_size = cpu_to_le32(0);
		devpriv->ai_dma_desc[i].next =
			cpu_to_le32((devpriv->ai_dma_desc_bus_addr +
				     ((i + 1) % ai_dma_ring_count(board)) *
				     माप(devpriv->ai_dma_desc[0])) |
				    PLX_DMADPR_DESCPCI | PLX_DMADPR_TCINTR |
				    PLX_DMADPR_XFERL2P);
	पूर्ण
	अगर (ao_cmd_is_supported(board)) अणु
		क्रम (i = 0; i < AO_DMA_RING_COUNT; i++) अणु
			devpriv->ao_dma_desc[i].pci_start_addr =
				cpu_to_le32(devpriv->ao_buffer_bus_addr[i]);
			devpriv->ao_dma_desc[i].local_start_addr =
				cpu_to_le32(devpriv->local0_iobase +
					    DAC_FIFO_REG);
			devpriv->ao_dma_desc[i].transfer_size = cpu_to_le32(0);
			devpriv->ao_dma_desc[i].next =
				cpu_to_le32((devpriv->ao_dma_desc_bus_addr +
					     ((i + 1) % (AO_DMA_RING_COUNT)) *
					     माप(devpriv->ao_dma_desc[0])) |
					    PLX_DMADPR_DESCPCI |
					    PLX_DMADPR_TCINTR);
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण

अटल व्योम cb_pcidas64_मुक्त_dma(काष्ठा comedi_device *dev)
अणु
	स्थिर काष्ठा pcidas64_board *board = dev->board_ptr;
	काष्ठा pci_dev *pcidev = comedi_to_pci_dev(dev);
	काष्ठा pcidas64_निजी *devpriv = dev->निजी;
	पूर्णांक i;

	अगर (!devpriv)
		वापस;

	/* मुक्त pci dma buffers */
	क्रम (i = 0; i < ai_dma_ring_count(board); i++) अणु
		अगर (devpriv->ai_buffer[i])
			dma_मुक्त_coherent(&pcidev->dev,
					  DMA_BUFFER_SIZE,
					  devpriv->ai_buffer[i],
					  devpriv->ai_buffer_bus_addr[i]);
	पूर्ण
	क्रम (i = 0; i < AO_DMA_RING_COUNT; i++) अणु
		अगर (devpriv->ao_buffer[i])
			dma_मुक्त_coherent(&pcidev->dev,
					  DMA_BUFFER_SIZE,
					  devpriv->ao_buffer[i],
					  devpriv->ao_buffer_bus_addr[i]);
	पूर्ण
	/* मुक्त dma descriptors */
	अगर (devpriv->ai_dma_desc)
		dma_मुक्त_coherent(&pcidev->dev,
				  माप(काष्ठा plx_dma_desc) *
				  ai_dma_ring_count(board),
				  devpriv->ai_dma_desc,
				  devpriv->ai_dma_desc_bus_addr);
	अगर (devpriv->ao_dma_desc)
		dma_मुक्त_coherent(&pcidev->dev,
				  माप(काष्ठा plx_dma_desc) *
				  AO_DMA_RING_COUNT,
				  devpriv->ao_dma_desc,
				  devpriv->ao_dma_desc_bus_addr);
पूर्ण

अटल अंतरभूत व्योम warn_बाह्यal_queue(काष्ठा comedi_device *dev)
अणु
	dev_err(dev->class_dev,
		"AO command and AI external channel queue cannot be used simultaneously\n");
	dev_err(dev->class_dev,
		"Use internal AI channel queue (channels must be consecutive and use same range/aref)\n");
पूर्ण

/*
 * their i2c requires a huge delay on setting घड़ी or data high क्रम some reason
 */
अटल स्थिर पूर्णांक i2c_high_udelay = 1000;
अटल स्थिर पूर्णांक i2c_low_udelay = 10;

/* set i2c data line high or low */
अटल व्योम i2c_set_sda(काष्ठा comedi_device *dev, पूर्णांक state)
अणु
	काष्ठा pcidas64_निजी *devpriv = dev->निजी;
	अटल स्थिर पूर्णांक data_bit = PLX_CNTRL_EEWB;
	व्योम __iomem *plx_control_addr = devpriv->plx9080_iobase +
					 PLX_REG_CNTRL;

	अगर (state) अणु				/* set data line high */
		devpriv->plx_control_bits &= ~data_bit;
		ग_लिखोl(devpriv->plx_control_bits, plx_control_addr);
		udelay(i2c_high_udelay);
	पूर्ण अन्यथा अणु				/* set data line low */
		devpriv->plx_control_bits |= data_bit;
		ग_लिखोl(devpriv->plx_control_bits, plx_control_addr);
		udelay(i2c_low_udelay);
	पूर्ण
पूर्ण

/* set i2c घड़ी line high or low */
अटल व्योम i2c_set_scl(काष्ठा comedi_device *dev, पूर्णांक state)
अणु
	काष्ठा pcidas64_निजी *devpriv = dev->निजी;
	अटल स्थिर पूर्णांक घड़ी_bit = PLX_CNTRL_USERO;
	व्योम __iomem *plx_control_addr = devpriv->plx9080_iobase +
					 PLX_REG_CNTRL;

	अगर (state) अणु				/* set घड़ी line high */
		devpriv->plx_control_bits &= ~घड़ी_bit;
		ग_लिखोl(devpriv->plx_control_bits, plx_control_addr);
		udelay(i2c_high_udelay);
	पूर्ण अन्यथा अणु				/* set घड़ी line low */
		devpriv->plx_control_bits |= घड़ी_bit;
		ग_लिखोl(devpriv->plx_control_bits, plx_control_addr);
		udelay(i2c_low_udelay);
	पूर्ण
पूर्ण

अटल व्योम i2c_ग_लिखो_byte(काष्ठा comedi_device *dev, u8 byte)
अणु
	u8 bit;
	अचिन्हित पूर्णांक num_bits = 8;

	क्रम (bit = 1 << (num_bits - 1); bit; bit >>= 1) अणु
		i2c_set_scl(dev, 0);
		अगर ((byte & bit))
			i2c_set_sda(dev, 1);
		अन्यथा
			i2c_set_sda(dev, 0);
		i2c_set_scl(dev, 1);
	पूर्ण
पूर्ण

/* we can't really पढ़ो the lines, so fake it */
अटल पूर्णांक i2c_पढ़ो_ack(काष्ठा comedi_device *dev)
अणु
	i2c_set_scl(dev, 0);
	i2c_set_sda(dev, 1);
	i2c_set_scl(dev, 1);

	वापस 0;		/* वापस fake acknowledge bit */
पूर्ण

/* send start bit */
अटल व्योम i2c_start(काष्ठा comedi_device *dev)
अणु
	i2c_set_scl(dev, 1);
	i2c_set_sda(dev, 1);
	i2c_set_sda(dev, 0);
पूर्ण

/* send stop bit */
अटल व्योम i2c_stop(काष्ठा comedi_device *dev)
अणु
	i2c_set_scl(dev, 0);
	i2c_set_sda(dev, 0);
	i2c_set_scl(dev, 1);
	i2c_set_sda(dev, 1);
पूर्ण

अटल व्योम i2c_ग_लिखो(काष्ठा comedi_device *dev, अचिन्हित पूर्णांक address,
		      स्थिर u8 *data, अचिन्हित पूर्णांक length)
अणु
	काष्ठा pcidas64_निजी *devpriv = dev->निजी;
	अचिन्हित पूर्णांक i;
	u8 bitstream;
	अटल स्थिर पूर्णांक पढ़ो_bit = 0x1;

	/*
	 * XXX need mutex to prevent simultaneous attempts to access
	 * eeprom and i2c bus
	 */

	/* make sure we करोn't send anything to eeprom */
	devpriv->plx_control_bits &= ~PLX_CNTRL_EECS;

	i2c_stop(dev);
	i2c_start(dev);

	/* send address and ग_लिखो bit */
	bitstream = (address << 1) & ~पढ़ो_bit;
	i2c_ग_लिखो_byte(dev, bitstream);

	/* get acknowledge */
	अगर (i2c_पढ़ो_ack(dev) != 0) अणु
		dev_err(dev->class_dev, "failed: no acknowledge\n");
		i2c_stop(dev);
		वापस;
	पूर्ण
	/* ग_लिखो data bytes */
	क्रम (i = 0; i < length; i++) अणु
		i2c_ग_लिखो_byte(dev, data[i]);
		अगर (i2c_पढ़ो_ack(dev) != 0) अणु
			dev_err(dev->class_dev, "failed: no acknowledge\n");
			i2c_stop(dev);
			वापस;
		पूर्ण
	पूर्ण
	i2c_stop(dev);
पूर्ण

अटल पूर्णांक cb_pcidas64_ai_eoc(काष्ठा comedi_device *dev,
			      काष्ठा comedi_subdevice *s,
			      काष्ठा comedi_insn *insn,
			      अचिन्हित दीर्घ context)
अणु
	स्थिर काष्ठा pcidas64_board *board = dev->board_ptr;
	काष्ठा pcidas64_निजी *devpriv = dev->निजी;
	अचिन्हित पूर्णांक status;

	status = पढ़ोw(devpriv->मुख्य_iobase + HW_STATUS_REG);
	अगर (board->layout == LAYOUT_4020) अणु
		status = पढ़ोw(devpriv->मुख्य_iobase + ADC_WRITE_PNTR_REG);
		अगर (status)
			वापस 0;
	पूर्ण अन्यथा अणु
		अगर (pipe_full_bits(status))
			वापस 0;
	पूर्ण
	वापस -EBUSY;
पूर्ण

अटल पूर्णांक ai_rinsn(काष्ठा comedi_device *dev, काष्ठा comedi_subdevice *s,
		    काष्ठा comedi_insn *insn, अचिन्हित पूर्णांक *data)
अणु
	स्थिर काष्ठा pcidas64_board *board = dev->board_ptr;
	काष्ठा pcidas64_निजी *devpriv = dev->निजी;
	अचिन्हित पूर्णांक bits = 0, n;
	अचिन्हित पूर्णांक channel, range, aref;
	अचिन्हित दीर्घ flags;
	पूर्णांक ret;

	channel = CR_CHAN(insn->chanspec);
	range = CR_RANGE(insn->chanspec);
	aref = CR_AREF(insn->chanspec);

	/* disable card's analog input पूर्णांकerrupt sources and pacing */
	/* 4020 generates dac करोne पूर्णांकerrupts even though they are disabled */
	disable_ai_pacing(dev);

	spin_lock_irqsave(&dev->spinlock, flags);
	अगर (insn->chanspec & CR_ALT_FILTER)
		devpriv->adc_control1_bits |= ADC_DITHER_BIT;
	अन्यथा
		devpriv->adc_control1_bits &= ~ADC_DITHER_BIT;
	ग_लिखोw(devpriv->adc_control1_bits,
	       devpriv->मुख्य_iobase + ADC_CONTROL1_REG);
	spin_unlock_irqrestore(&dev->spinlock, flags);

	अगर (board->layout != LAYOUT_4020) अणु
		/* use पूर्णांकernal queue */
		devpriv->hw_config_bits &= ~EXT_QUEUE_BIT;
		ग_लिखोw(devpriv->hw_config_bits,
		       devpriv->मुख्य_iobase + HW_CONFIG_REG);

		/* ALT_SOURCE is पूर्णांकernal calibration reference */
		अगर (insn->chanspec & CR_ALT_SOURCE) अणु
			अचिन्हित पूर्णांक cal_en_bit;

			अगर (board->layout == LAYOUT_60XX)
				cal_en_bit = CAL_EN_60XX_BIT;
			अन्यथा
				cal_en_bit = CAL_EN_64XX_BIT;
			/*
			 * select पूर्णांकernal reference source to connect
			 * to channel 0
			 */
			ग_लिखोw(cal_en_bit |
			       adc_src_bits(devpriv->calibration_source),
			       devpriv->मुख्य_iobase + CALIBRATION_REG);
		पूर्ण अन्यथा अणु
			/*
			 * make sure पूर्णांकernal calibration source
			 * is turned off
			 */
			ग_लिखोw(0, devpriv->मुख्य_iobase + CALIBRATION_REG);
		पूर्ण
		/* load पूर्णांकernal queue */
		bits = 0;
		/* set gain */
		bits |= ai_range_bits_6xxx(dev, CR_RANGE(insn->chanspec));
		/* set single-ended / dअगरferential */
		bits |= se_dअगरf_bit_6xxx(dev, aref == AREF_DIFF);
		अगर (aref == AREF_COMMON)
			bits |= ADC_COMMON_BIT;
		bits |= adc_chan_bits(channel);
		/* set stop channel */
		ग_लिखोw(adc_chan_bits(channel),
		       devpriv->मुख्य_iobase + ADC_QUEUE_HIGH_REG);
		/* set start channel, and rest of settings */
		ग_लिखोw(bits, devpriv->मुख्य_iobase + ADC_QUEUE_LOAD_REG);
	पूर्ण अन्यथा अणु
		u8 old_cal_range_bits = devpriv->i2c_cal_range_bits;

		devpriv->i2c_cal_range_bits &= ~ADC_SRC_4020_MASK;
		अगर (insn->chanspec & CR_ALT_SOURCE) अणु
			devpriv->i2c_cal_range_bits |=
				adc_src_4020_bits(devpriv->calibration_source);
		पूर्ण अन्यथा अणु	/* select BNC inमाला_दो */
			devpriv->i2c_cal_range_bits |= adc_src_4020_bits(4);
		पूर्ण
		/* select range */
		अगर (range == 0)
			devpriv->i2c_cal_range_bits |= attenuate_bit(channel);
		अन्यथा
			devpriv->i2c_cal_range_bits &= ~attenuate_bit(channel);
		/*
		 * update calibration/range i2c रेजिस्टर only अगर necessary,
		 * as it is very slow
		 */
		अगर (old_cal_range_bits != devpriv->i2c_cal_range_bits) अणु
			u8 i2c_data = devpriv->i2c_cal_range_bits;

			i2c_ग_लिखो(dev, RANGE_CAL_I2C_ADDR, &i2c_data,
				  माप(i2c_data));
		पूर्ण

		/*
		 * 4020 manual asks that sample पूर्णांकerval रेजिस्टर to be set
		 * beक्रमe writing to convert रेजिस्टर.
		 * Using somewhat arbitrary setting of 4 master घड़ी ticks
		 * = 0.1 usec
		 */
		ग_लिखोw(0, devpriv->मुख्य_iobase + ADC_SAMPLE_INTERVAL_UPPER_REG);
		ग_लिखोw(2, devpriv->मुख्य_iobase + ADC_SAMPLE_INTERVAL_LOWER_REG);
	पूर्ण

	क्रम (n = 0; n < insn->n; n++) अणु
		/* clear adc buffer (inside loop क्रम 4020 sake) */
		ग_लिखोw(0, devpriv->मुख्य_iobase + ADC_BUFFER_CLEAR_REG);

		/* trigger conversion, bits sent only matter क्रम 4020 */
		ग_लिखोw(adc_convert_chan_4020_bits(CR_CHAN(insn->chanspec)),
		       devpriv->मुख्य_iobase + ADC_CONVERT_REG);

		/* रुको क्रम data */
		ret = comedi_समयout(dev, s, insn, cb_pcidas64_ai_eoc, 0);
		अगर (ret)
			वापस ret;

		अगर (board->layout == LAYOUT_4020)
			data[n] = पढ़ोl(dev->mmio + ADC_FIFO_REG) & 0xffff;
		अन्यथा
			data[n] = पढ़ोw(devpriv->मुख्य_iobase + PIPE1_READ_REG);
	पूर्ण

	वापस n;
पूर्ण

अटल पूर्णांक ai_config_calibration_source(काष्ठा comedi_device *dev,
					अचिन्हित पूर्णांक *data)
अणु
	स्थिर काष्ठा pcidas64_board *board = dev->board_ptr;
	काष्ठा pcidas64_निजी *devpriv = dev->निजी;
	अचिन्हित पूर्णांक source = data[1];
	पूर्णांक num_calibration_sources;

	अगर (board->layout == LAYOUT_60XX)
		num_calibration_sources = 16;
	अन्यथा
		num_calibration_sources = 8;
	अगर (source >= num_calibration_sources) अणु
		dev_dbg(dev->class_dev, "invalid calibration source: %i\n",
			source);
		वापस -EINVAL;
	पूर्ण

	devpriv->calibration_source = source;

	वापस 2;
पूर्ण

अटल पूर्णांक ai_config_block_size(काष्ठा comedi_device *dev, अचिन्हित पूर्णांक *data)
अणु
	स्थिर काष्ठा pcidas64_board *board = dev->board_ptr;
	पूर्णांक fअगरo_size;
	स्थिर काष्ठा hw_fअगरo_info *स्थिर fअगरo = board->ai_fअगरo;
	अचिन्हित पूर्णांक block_size, requested_block_size;
	पूर्णांक retval;

	requested_block_size = data[1];

	अगर (requested_block_size) अणु
		fअगरo_size = requested_block_size * fअगरo->num_segments /
			    bytes_in_sample;

		retval = set_ai_fअगरo_size(dev, fअगरo_size);
		अगर (retval < 0)
			वापस retval;
	पूर्ण

	block_size = ai_fअगरo_size(dev) / fअगरo->num_segments * bytes_in_sample;

	data[1] = block_size;

	वापस 2;
पूर्ण

अटल पूर्णांक ai_config_master_घड़ी_4020(काष्ठा comedi_device *dev,
				       अचिन्हित पूर्णांक *data)
अणु
	काष्ठा pcidas64_निजी *devpriv = dev->निजी;
	अचिन्हित पूर्णांक भागisor = data[4];
	पूर्णांक retval = 0;

	अगर (भागisor < 2) अणु
		भागisor = 2;
		retval = -EAGAIN;
	पूर्ण

	चयन (data[1]) अणु
	हाल COMEDI_EV_SCAN_BEGIN:
		devpriv->ext_घड़ी.भागisor = भागisor;
		devpriv->ext_घड़ी.chanspec = data[2];
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	data[4] = भागisor;

	वापस retval ? retval : 5;
पूर्ण

/* XXX could add support क्रम 60xx series */
अटल पूर्णांक ai_config_master_घड़ी(काष्ठा comedi_device *dev, अचिन्हित पूर्णांक *data)
अणु
	स्थिर काष्ठा pcidas64_board *board = dev->board_ptr;

	चयन (board->layout) अणु
	हाल LAYOUT_4020:
		वापस ai_config_master_घड़ी_4020(dev, data);
	शेष:
		वापस -EINVAL;
	पूर्ण

	वापस -EINVAL;
पूर्ण

अटल पूर्णांक ai_config_insn(काष्ठा comedi_device *dev, काष्ठा comedi_subdevice *s,
			  काष्ठा comedi_insn *insn, अचिन्हित पूर्णांक *data)
अणु
	पूर्णांक id = data[0];

	चयन (id) अणु
	हाल INSN_CONFIG_ALT_SOURCE:
		वापस ai_config_calibration_source(dev, data);
	हाल INSN_CONFIG_BLOCK_SIZE:
		वापस ai_config_block_size(dev, data);
	हाल INSN_CONFIG_TIMER_1:
		वापस ai_config_master_घड़ी(dev, data);
	शेष:
		वापस -EINVAL;
	पूर्ण
	वापस -EINVAL;
पूर्ण

/*
 * Gets nearest achievable timing given master घड़ी speed, करोes not
 * take पूर्णांकo account possible minimum/maximum भागisor values.  Used
 * by other timing checking functions.
 */
अटल अचिन्हित पूर्णांक get_भागisor(अचिन्हित पूर्णांक ns, अचिन्हित पूर्णांक flags)
अणु
	अचिन्हित पूर्णांक भागisor;

	चयन (flags & CMDF_ROUND_MASK) अणु
	हाल CMDF_ROUND_UP:
		भागisor = DIV_ROUND_UP(ns, TIMER_BASE);
		अवरोध;
	हाल CMDF_ROUND_DOWN:
		भागisor = ns / TIMER_BASE;
		अवरोध;
	हाल CMDF_ROUND_NEAREST:
	शेष:
		भागisor = DIV_ROUND_CLOSEST(ns, TIMER_BASE);
		अवरोध;
	पूर्ण
	वापस भागisor;
पूर्ण

/*
 * utility function that rounds desired timing to an achievable समय, and
 * sets cmd members appropriately.
 * adc paces conversions from master घड़ी by भागiding by (x + 3) where x is
 * 24 bit number
 */
अटल व्योम check_adc_timing(काष्ठा comedi_device *dev, काष्ठा comedi_cmd *cmd)
अणु
	स्थिर काष्ठा pcidas64_board *board = dev->board_ptr;
	अचिन्हित दीर्घ दीर्घ convert_भागisor = 0;
	अचिन्हित पूर्णांक scan_भागisor;
	अटल स्थिर पूर्णांक min_convert_भागisor = 3;
	अटल स्थिर पूर्णांक max_convert_भागisor =
		max_counter_value + min_convert_भागisor;
	अटल स्थिर पूर्णांक min_scan_भागisor_4020 = 2;
	अचिन्हित दीर्घ दीर्घ max_scan_भागisor, min_scan_भागisor;

	अगर (cmd->convert_src == TRIG_TIMER) अणु
		अगर (board->layout == LAYOUT_4020) अणु
			cmd->convert_arg = 0;
		पूर्ण अन्यथा अणु
			convert_भागisor = get_भागisor(cmd->convert_arg,
						      cmd->flags);
			अगर (convert_भागisor > max_convert_भागisor)
				convert_भागisor = max_convert_भागisor;
			अगर (convert_भागisor < min_convert_भागisor)
				convert_भागisor = min_convert_भागisor;
			cmd->convert_arg = convert_भागisor * TIMER_BASE;
		पूर्ण
	पूर्ण अन्यथा अगर (cmd->convert_src == TRIG_NOW) अणु
		cmd->convert_arg = 0;
	पूर्ण

	अगर (cmd->scan_begin_src == TRIG_TIMER) अणु
		scan_भागisor = get_भागisor(cmd->scan_begin_arg, cmd->flags);
		अगर (cmd->convert_src == TRIG_TIMER) अणु
			min_scan_भागisor = convert_भागisor * cmd->chanlist_len;
			max_scan_भागisor =
				(convert_भागisor * cmd->chanlist_len - 1) +
				max_counter_value;
		पूर्ण अन्यथा अणु
			min_scan_भागisor = min_scan_भागisor_4020;
			max_scan_भागisor = max_counter_value + min_scan_भागisor;
		पूर्ण
		अगर (scan_भागisor > max_scan_भागisor)
			scan_भागisor = max_scan_भागisor;
		अगर (scan_भागisor < min_scan_भागisor)
			scan_भागisor = min_scan_भागisor;
		cmd->scan_begin_arg = scan_भागisor * TIMER_BASE;
	पूर्ण
पूर्ण

अटल पूर्णांक cb_pcidas64_ai_check_chanlist(काष्ठा comedi_device *dev,
					 काष्ठा comedi_subdevice *s,
					 काष्ठा comedi_cmd *cmd)
अणु
	स्थिर काष्ठा pcidas64_board *board = dev->board_ptr;
	अचिन्हित पूर्णांक aref0 = CR_AREF(cmd->chanlist[0]);
	पूर्णांक i;

	क्रम (i = 1; i < cmd->chanlist_len; i++) अणु
		अचिन्हित पूर्णांक aref = CR_AREF(cmd->chanlist[i]);

		अगर (aref != aref0) अणु
			dev_dbg(dev->class_dev,
				"all elements in chanlist must use the same analog reference\n");
			वापस -EINVAL;
		पूर्ण
	पूर्ण

	अगर (board->layout == LAYOUT_4020) अणु
		अचिन्हित पूर्णांक chan0 = CR_CHAN(cmd->chanlist[0]);

		क्रम (i = 1; i < cmd->chanlist_len; i++) अणु
			अचिन्हित पूर्णांक chan = CR_CHAN(cmd->chanlist[i]);

			अगर (chan != (chan0 + i)) अणु
				dev_dbg(dev->class_dev,
					"chanlist must use consecutive channels\n");
				वापस -EINVAL;
			पूर्ण
		पूर्ण
		अगर (cmd->chanlist_len == 3) अणु
			dev_dbg(dev->class_dev,
				"chanlist cannot be 3 channels long, use 1, 2, or 4 channels\n");
			वापस -EINVAL;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक ai_cmdtest(काष्ठा comedi_device *dev, काष्ठा comedi_subdevice *s,
		      काष्ठा comedi_cmd *cmd)
अणु
	स्थिर काष्ठा pcidas64_board *board = dev->board_ptr;
	पूर्णांक err = 0;
	अचिन्हित पूर्णांक पंचांगp_arg, पंचांगp_arg2;
	अचिन्हित पूर्णांक triggers;

	/* Step 1 : check अगर triggers are trivially valid */

	err |= comedi_check_trigger_src(&cmd->start_src, TRIG_NOW | TRIG_EXT);

	triggers = TRIG_TIMER;
	अगर (board->layout == LAYOUT_4020)
		triggers |= TRIG_OTHER;
	अन्यथा
		triggers |= TRIG_FOLLOW;
	err |= comedi_check_trigger_src(&cmd->scan_begin_src, triggers);

	triggers = TRIG_TIMER;
	अगर (board->layout == LAYOUT_4020)
		triggers |= TRIG_NOW;
	अन्यथा
		triggers |= TRIG_EXT;
	err |= comedi_check_trigger_src(&cmd->convert_src, triggers);
	err |= comedi_check_trigger_src(&cmd->scan_end_src, TRIG_COUNT);
	err |= comedi_check_trigger_src(&cmd->stop_src,
					TRIG_COUNT | TRIG_EXT | TRIG_NONE);

	अगर (err)
		वापस 1;

	/* Step 2a : make sure trigger sources are unique */

	err |= comedi_check_trigger_is_unique(cmd->start_src);
	err |= comedi_check_trigger_is_unique(cmd->scan_begin_src);
	err |= comedi_check_trigger_is_unique(cmd->convert_src);
	err |= comedi_check_trigger_is_unique(cmd->stop_src);

	/* Step 2b : and mutually compatible */

	अगर (cmd->convert_src == TRIG_EXT && cmd->scan_begin_src == TRIG_TIMER)
		err |= -EINVAL;

	अगर (err)
		वापस 2;

	/* Step 3: check अगर arguments are trivially valid */

	चयन (cmd->start_src) अणु
	हाल TRIG_NOW:
		err |= comedi_check_trigger_arg_is(&cmd->start_arg, 0);
		अवरोध;
	हाल TRIG_EXT:
		/*
		 * start_arg is the CR_CHAN | CR_INVERT of the
		 * बाह्यal trigger.
		 */
		अवरोध;
	पूर्ण

	अगर (cmd->convert_src == TRIG_TIMER) अणु
		अगर (board->layout == LAYOUT_4020) अणु
			err |= comedi_check_trigger_arg_is(&cmd->convert_arg,
							   0);
		पूर्ण अन्यथा अणु
			err |= comedi_check_trigger_arg_min(&cmd->convert_arg,
							    board->ai_speed);
			/*
			 * अगर scans are समयd faster than conversion rate
			 * allows
			 */
			अगर (cmd->scan_begin_src == TRIG_TIMER) अणु
				err |= comedi_check_trigger_arg_min(
						&cmd->scan_begin_arg,
						cmd->convert_arg *
						cmd->chanlist_len);
			पूर्ण
		पूर्ण
	पूर्ण

	err |= comedi_check_trigger_arg_min(&cmd->chanlist_len, 1);
	err |= comedi_check_trigger_arg_is(&cmd->scan_end_arg,
					   cmd->chanlist_len);

	चयन (cmd->stop_src) अणु
	हाल TRIG_EXT:
		अवरोध;
	हाल TRIG_COUNT:
		err |= comedi_check_trigger_arg_min(&cmd->stop_arg, 1);
		अवरोध;
	हाल TRIG_NONE:
		err |= comedi_check_trigger_arg_is(&cmd->stop_arg, 0);
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	अगर (err)
		वापस 3;

	/* step 4: fix up any arguments */

	अगर (cmd->convert_src == TRIG_TIMER) अणु
		पंचांगp_arg = cmd->convert_arg;
		पंचांगp_arg2 = cmd->scan_begin_arg;
		check_adc_timing(dev, cmd);
		अगर (पंचांगp_arg != cmd->convert_arg)
			err++;
		अगर (पंचांगp_arg2 != cmd->scan_begin_arg)
			err++;
	पूर्ण

	अगर (err)
		वापस 4;

	/* Step 5: check channel list अगर it exists */
	अगर (cmd->chanlist && cmd->chanlist_len > 0)
		err |= cb_pcidas64_ai_check_chanlist(dev, s, cmd);

	अगर (err)
		वापस 5;

	वापस 0;
पूर्ण

अटल पूर्णांक use_hw_sample_counter(काष्ठा comedi_cmd *cmd)
अणु
/* disable क्रम now until I work out a race */
	वापस 0;

	अगर (cmd->stop_src == TRIG_COUNT && cmd->stop_arg <= max_counter_value)
		वापस 1;

	वापस 0;
पूर्ण

अटल व्योम setup_sample_counters(काष्ठा comedi_device *dev,
				  काष्ठा comedi_cmd *cmd)
अणु
	काष्ठा pcidas64_निजी *devpriv = dev->निजी;

	/* load hardware conversion counter */
	अगर (use_hw_sample_counter(cmd)) अणु
		ग_लिखोw(cmd->stop_arg & 0xffff,
		       devpriv->मुख्य_iobase + ADC_COUNT_LOWER_REG);
		ग_लिखोw((cmd->stop_arg >> 16) & 0xff,
		       devpriv->मुख्य_iobase + ADC_COUNT_UPPER_REG);
	पूर्ण अन्यथा अणु
		ग_लिखोw(1, devpriv->मुख्य_iobase + ADC_COUNT_LOWER_REG);
	पूर्ण
पूर्ण

अटल अंतरभूत अचिन्हित पूर्णांक dma_transfer_size(काष्ठा comedi_device *dev)
अणु
	स्थिर काष्ठा pcidas64_board *board = dev->board_ptr;
	काष्ठा pcidas64_निजी *devpriv = dev->निजी;
	अचिन्हित पूर्णांक num_samples;

	num_samples = devpriv->ai_fअगरo_segment_length *
		      board->ai_fअगरo->sample_packing_ratio;
	अगर (num_samples > DMA_BUFFER_SIZE / माप(u16))
		num_samples = DMA_BUFFER_SIZE / माप(u16);

	वापस num_samples;
पूर्ण

अटल u32 ai_convert_counter_6xxx(स्थिर काष्ठा comedi_device *dev,
				   स्थिर काष्ठा comedi_cmd *cmd)
अणु
	/* supposed to load counter with desired भागisor minus 3 */
	वापस cmd->convert_arg / TIMER_BASE - 3;
पूर्ण

अटल u32 ai_scan_counter_6xxx(काष्ठा comedi_device *dev,
				काष्ठा comedi_cmd *cmd)
अणु
	u32 count;

	/* figure out how दीर्घ we need to delay at end of scan */
	चयन (cmd->scan_begin_src) अणु
	हाल TRIG_TIMER:
		count = (cmd->scan_begin_arg -
			 (cmd->convert_arg * (cmd->chanlist_len - 1))) /
			TIMER_BASE;
		अवरोध;
	हाल TRIG_FOLLOW:
		count = cmd->convert_arg / TIMER_BASE;
		अवरोध;
	शेष:
		वापस 0;
	पूर्ण
	वापस count - 3;
पूर्ण

अटल u32 ai_convert_counter_4020(काष्ठा comedi_device *dev,
				   काष्ठा comedi_cmd *cmd)
अणु
	काष्ठा pcidas64_निजी *devpriv = dev->निजी;
	अचिन्हित पूर्णांक भागisor;

	चयन (cmd->scan_begin_src) अणु
	हाल TRIG_TIMER:
		भागisor = cmd->scan_begin_arg / TIMER_BASE;
		अवरोध;
	हाल TRIG_OTHER:
		भागisor = devpriv->ext_घड़ी.भागisor;
		अवरोध;
	शेष:		/* should never happen */
		dev_err(dev->class_dev, "bug! failed to set ai pacing!\n");
		भागisor = 1000;
		अवरोध;
	पूर्ण

	/* supposed to load counter with desired भागisor minus 2 क्रम 4020 */
	वापस भागisor - 2;
पूर्ण

अटल व्योम select_master_घड़ी_4020(काष्ठा comedi_device *dev,
				     स्थिर काष्ठा comedi_cmd *cmd)
अणु
	काष्ठा pcidas64_निजी *devpriv = dev->निजी;

	/* select पूर्णांकernal/बाह्यal master घड़ी */
	devpriv->hw_config_bits &= ~MASTER_CLOCK_4020_MASK;
	अगर (cmd->scan_begin_src == TRIG_OTHER) अणु
		पूर्णांक chanspec = devpriv->ext_घड़ी.chanspec;

		अगर (CR_CHAN(chanspec))
			devpriv->hw_config_bits |= BNC_CLOCK_4020_BITS;
		अन्यथा
			devpriv->hw_config_bits |= EXT_CLOCK_4020_BITS;
	पूर्ण अन्यथा अणु
		devpriv->hw_config_bits |= INTERNAL_CLOCK_4020_BITS;
	पूर्ण
	ग_लिखोw(devpriv->hw_config_bits,
	       devpriv->मुख्य_iobase + HW_CONFIG_REG);
पूर्ण

अटल व्योम select_master_घड़ी(काष्ठा comedi_device *dev,
				स्थिर काष्ठा comedi_cmd *cmd)
अणु
	स्थिर काष्ठा pcidas64_board *board = dev->board_ptr;

	चयन (board->layout) अणु
	हाल LAYOUT_4020:
		select_master_घड़ी_4020(dev, cmd);
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण
पूर्ण

अटल अंतरभूत व्योम dma_start_sync(काष्ठा comedi_device *dev,
				  अचिन्हित पूर्णांक channel)
अणु
	काष्ठा pcidas64_निजी *devpriv = dev->निजी;
	अचिन्हित दीर्घ flags;

	/* spinlock क्रम plx dma control/status reg */
	spin_lock_irqsave(&dev->spinlock, flags);
	ग_लिखोb(PLX_DMACSR_ENABLE | PLX_DMACSR_START | PLX_DMACSR_CLEARINTR,
	       devpriv->plx9080_iobase + PLX_REG_DMACSR(channel));
	spin_unlock_irqrestore(&dev->spinlock, flags);
पूर्ण

अटल व्योम set_ai_pacing(काष्ठा comedi_device *dev, काष्ठा comedi_cmd *cmd)
अणु
	स्थिर काष्ठा pcidas64_board *board = dev->board_ptr;
	काष्ठा pcidas64_निजी *devpriv = dev->निजी;
	u32 convert_counter = 0, scan_counter = 0;

	check_adc_timing(dev, cmd);

	select_master_घड़ी(dev, cmd);

	अगर (board->layout == LAYOUT_4020) अणु
		convert_counter = ai_convert_counter_4020(dev, cmd);
	पूर्ण अन्यथा अणु
		convert_counter = ai_convert_counter_6xxx(dev, cmd);
		scan_counter = ai_scan_counter_6xxx(dev, cmd);
	पूर्ण

	/* load lower 16 bits of convert पूर्णांकerval */
	ग_लिखोw(convert_counter & 0xffff,
	       devpriv->मुख्य_iobase + ADC_SAMPLE_INTERVAL_LOWER_REG);
	/* load upper 8 bits of convert पूर्णांकerval */
	ग_लिखोw((convert_counter >> 16) & 0xff,
	       devpriv->मुख्य_iobase + ADC_SAMPLE_INTERVAL_UPPER_REG);
	/* load lower 16 bits of scan delay */
	ग_लिखोw(scan_counter & 0xffff,
	       devpriv->मुख्य_iobase + ADC_DELAY_INTERVAL_LOWER_REG);
	/* load upper 8 bits of scan delay */
	ग_लिखोw((scan_counter >> 16) & 0xff,
	       devpriv->मुख्य_iobase + ADC_DELAY_INTERVAL_UPPER_REG);
पूर्ण

अटल पूर्णांक use_पूर्णांकernal_queue_6xxx(स्थिर काष्ठा comedi_cmd *cmd)
अणु
	पूर्णांक i;

	क्रम (i = 0; i + 1 < cmd->chanlist_len; i++) अणु
		अगर (CR_CHAN(cmd->chanlist[i + 1]) !=
		    CR_CHAN(cmd->chanlist[i]) + 1)
			वापस 0;
		अगर (CR_RANGE(cmd->chanlist[i + 1]) !=
		    CR_RANGE(cmd->chanlist[i]))
			वापस 0;
		अगर (CR_AREF(cmd->chanlist[i + 1]) != CR_AREF(cmd->chanlist[i]))
			वापस 0;
	पूर्ण
	वापस 1;
पूर्ण

अटल पूर्णांक setup_channel_queue(काष्ठा comedi_device *dev,
			       स्थिर काष्ठा comedi_cmd *cmd)
अणु
	स्थिर काष्ठा pcidas64_board *board = dev->board_ptr;
	काष्ठा pcidas64_निजी *devpriv = dev->निजी;
	अचिन्हित लघु bits;
	पूर्णांक i;

	अगर (board->layout != LAYOUT_4020) अणु
		अगर (use_पूर्णांकernal_queue_6xxx(cmd)) अणु
			devpriv->hw_config_bits &= ~EXT_QUEUE_BIT;
			ग_लिखोw(devpriv->hw_config_bits,
			       devpriv->मुख्य_iobase + HW_CONFIG_REG);
			bits = 0;
			/* set channel */
			bits |= adc_chan_bits(CR_CHAN(cmd->chanlist[0]));
			/* set gain */
			bits |= ai_range_bits_6xxx(dev,
						   CR_RANGE(cmd->chanlist[0]));
			/* set single-ended / dअगरferential */
			bits |= se_dअगरf_bit_6xxx(dev,
						 CR_AREF(cmd->chanlist[0]) ==
						 AREF_DIFF);
			अगर (CR_AREF(cmd->chanlist[0]) == AREF_COMMON)
				bits |= ADC_COMMON_BIT;
			/* set stop channel */
			ग_लिखोw(adc_chan_bits
			       (CR_CHAN(cmd->chanlist[cmd->chanlist_len - 1])),
			       devpriv->मुख्य_iobase + ADC_QUEUE_HIGH_REG);
			/* set start channel, and rest of settings */
			ग_लिखोw(bits,
			       devpriv->मुख्य_iobase + ADC_QUEUE_LOAD_REG);
		पूर्ण अन्यथा अणु
			/* use बाह्यal queue */
			अगर (dev->ग_लिखो_subdev && dev->ग_लिखो_subdev->busy) अणु
				warn_बाह्यal_queue(dev);
				वापस -EBUSY;
			पूर्ण
			devpriv->hw_config_bits |= EXT_QUEUE_BIT;
			ग_लिखोw(devpriv->hw_config_bits,
			       devpriv->मुख्य_iobase + HW_CONFIG_REG);
			/* clear DAC buffer to prevent weird पूर्णांकeractions */
			ग_लिखोw(0,
			       devpriv->मुख्य_iobase + DAC_BUFFER_CLEAR_REG);
			/* clear queue poपूर्णांकer */
			ग_लिखोw(0, devpriv->मुख्य_iobase + ADC_QUEUE_CLEAR_REG);
			/* load बाह्यal queue */
			क्रम (i = 0; i < cmd->chanlist_len; i++) अणु
				अचिन्हित पूर्णांक chanspec = cmd->chanlist[i];
				पूर्णांक use_dअगरferential;

				bits = 0;
				/* set channel */
				bits |= adc_chan_bits(CR_CHAN(chanspec));
				/* set gain */
				bits |= ai_range_bits_6xxx(dev,
							   CR_RANGE(chanspec));
				/* set single-ended / dअगरferential */
				use_dअगरferential = 0;
				अगर (CR_AREF(chanspec) == AREF_DIFF)
					use_dअगरferential = 1;
				bits |= se_dअगरf_bit_6xxx(dev, use_dअगरferential);

				अगर (CR_AREF(cmd->chanlist[i]) == AREF_COMMON)
					bits |= ADC_COMMON_BIT;
				/* mark end of queue */
				अगर (i == cmd->chanlist_len - 1)
					bits |= QUEUE_EOSCAN_BIT |
						QUEUE_EOSEQ_BIT;
				ग_लिखोw(bits,
				       devpriv->मुख्य_iobase +
				       ADC_QUEUE_FIFO_REG);
			पूर्ण
			/*
			 * करोing a queue clear is not specअगरied in board करोcs,
			 * but required क्रम reliable operation
			 */
			ग_लिखोw(0, devpriv->मुख्य_iobase + ADC_QUEUE_CLEAR_REG);
			/* prime queue holding रेजिस्टर */
			ग_लिखोw(0, devpriv->मुख्य_iobase + ADC_QUEUE_LOAD_REG);
		पूर्ण
	पूर्ण अन्यथा अणु
		अचिन्हित लघु old_cal_range_bits = devpriv->i2c_cal_range_bits;

		devpriv->i2c_cal_range_bits &= ~ADC_SRC_4020_MASK;
		/* select BNC inमाला_दो */
		devpriv->i2c_cal_range_bits |= adc_src_4020_bits(4);
		/* select ranges */
		क्रम (i = 0; i < cmd->chanlist_len; i++) अणु
			अचिन्हित पूर्णांक channel = CR_CHAN(cmd->chanlist[i]);
			अचिन्हित पूर्णांक range = CR_RANGE(cmd->chanlist[i]);

			अगर (range == 0)
				devpriv->i2c_cal_range_bits |=
					attenuate_bit(channel);
			अन्यथा
				devpriv->i2c_cal_range_bits &=
					~attenuate_bit(channel);
		पूर्ण
		/*
		 * update calibration/range i2c रेजिस्टर only अगर necessary,
		 * as it is very slow
		 */
		अगर (old_cal_range_bits != devpriv->i2c_cal_range_bits) अणु
			u8 i2c_data = devpriv->i2c_cal_range_bits;

			i2c_ग_लिखो(dev, RANGE_CAL_I2C_ADDR, &i2c_data,
				  माप(i2c_data));
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण

अटल अंतरभूत व्योम load_first_dma_descriptor(काष्ठा comedi_device *dev,
					     अचिन्हित पूर्णांक dma_channel,
					     अचिन्हित पूर्णांक descriptor_bits)
अणु
	काष्ठा pcidas64_निजी *devpriv = dev->निजी;

	/*
	 * The transfer size, pci address, and local address रेजिस्टरs
	 * are supposedly unused during chained dma,
	 * but I have found that left over values from last operation
	 * occasionally cause problems with transfer of first dma
	 * block.  Initializing them to zero seems to fix the problem.
	 */
	अगर (dma_channel) अणु
		ग_लिखोl(0, devpriv->plx9080_iobase + PLX_REG_DMASIZ1);
		ग_लिखोl(0, devpriv->plx9080_iobase + PLX_REG_DMAPADR1);
		ग_लिखोl(0, devpriv->plx9080_iobase + PLX_REG_DMALADR1);
		ग_लिखोl(descriptor_bits,
		       devpriv->plx9080_iobase + PLX_REG_DMADPR1);
	पूर्ण अन्यथा अणु
		ग_लिखोl(0, devpriv->plx9080_iobase + PLX_REG_DMASIZ0);
		ग_लिखोl(0, devpriv->plx9080_iobase + PLX_REG_DMAPADR0);
		ग_लिखोl(0, devpriv->plx9080_iobase + PLX_REG_DMALADR0);
		ग_लिखोl(descriptor_bits,
		       devpriv->plx9080_iobase + PLX_REG_DMADPR0);
	पूर्ण
पूर्ण

अटल पूर्णांक ai_cmd(काष्ठा comedi_device *dev, काष्ठा comedi_subdevice *s)
अणु
	स्थिर काष्ठा pcidas64_board *board = dev->board_ptr;
	काष्ठा pcidas64_निजी *devpriv = dev->निजी;
	काष्ठा comedi_async *async = s->async;
	काष्ठा comedi_cmd *cmd = &async->cmd;
	u32 bits;
	अचिन्हित पूर्णांक i;
	अचिन्हित दीर्घ flags;
	पूर्णांक retval;

	disable_ai_pacing(dev);
	पात_dma(dev, 1);

	retval = setup_channel_queue(dev, cmd);
	अगर (retval < 0)
		वापस retval;

	/* make sure पूर्णांकernal calibration source is turned off */
	ग_लिखोw(0, devpriv->मुख्य_iobase + CALIBRATION_REG);

	set_ai_pacing(dev, cmd);

	setup_sample_counters(dev, cmd);

	enable_ai_पूर्णांकerrupts(dev, cmd);

	spin_lock_irqsave(&dev->spinlock, flags);
	/* set mode, allow conversions through software gate */
	devpriv->adc_control1_bits |= ADC_SW_GATE_BIT;
	devpriv->adc_control1_bits &= ~ADC_DITHER_BIT;
	अगर (board->layout != LAYOUT_4020) अणु
		devpriv->adc_control1_bits &= ~ADC_MODE_MASK;
		अगर (cmd->convert_src == TRIG_EXT)
			/* good old mode 13 */
			devpriv->adc_control1_bits |= adc_mode_bits(13);
		अन्यथा
			/* mode 8.  What अन्यथा could you need? */
			devpriv->adc_control1_bits |= adc_mode_bits(8);
	पूर्ण अन्यथा अणु
		devpriv->adc_control1_bits &= ~CHANNEL_MODE_4020_MASK;
		अगर (cmd->chanlist_len == 4)
			devpriv->adc_control1_bits |= FOUR_CHANNEL_4020_BITS;
		अन्यथा अगर (cmd->chanlist_len == 2)
			devpriv->adc_control1_bits |= TWO_CHANNEL_4020_BITS;
		devpriv->adc_control1_bits &= ~ADC_LO_CHANNEL_4020_MASK;
		devpriv->adc_control1_bits |=
			adc_lo_chan_4020_bits(CR_CHAN(cmd->chanlist[0]));
		devpriv->adc_control1_bits &= ~ADC_HI_CHANNEL_4020_MASK;
		devpriv->adc_control1_bits |=
			adc_hi_chan_4020_bits(CR_CHAN(cmd->chanlist
						      [cmd->chanlist_len - 1]));
	पूर्ण
	ग_लिखोw(devpriv->adc_control1_bits,
	       devpriv->मुख्य_iobase + ADC_CONTROL1_REG);
	spin_unlock_irqrestore(&dev->spinlock, flags);

	/* clear adc buffer */
	ग_लिखोw(0, devpriv->मुख्य_iobase + ADC_BUFFER_CLEAR_REG);

	अगर ((cmd->flags & CMDF_WAKE_EOS) == 0 ||
	    board->layout == LAYOUT_4020) अणु
		devpriv->ai_dma_index = 0;

		/* set dma transfer size */
		क्रम (i = 0; i < ai_dma_ring_count(board); i++)
			devpriv->ai_dma_desc[i].transfer_size =
				cpu_to_le32(dma_transfer_size(dev) *
					    माप(u16));

		/* give location of first dma descriptor */
		load_first_dma_descriptor(dev, 1,
					  devpriv->ai_dma_desc_bus_addr |
					  PLX_DMADPR_DESCPCI |
					  PLX_DMADPR_TCINTR |
					  PLX_DMADPR_XFERL2P);

		dma_start_sync(dev, 1);
	पूर्ण

	अगर (board->layout == LAYOUT_4020) अणु
		/* set source क्रम बाह्यal triggers */
		bits = 0;
		अगर (cmd->start_src == TRIG_EXT && CR_CHAN(cmd->start_arg))
			bits |= EXT_START_TRIG_BNC_BIT;
		अगर (cmd->stop_src == TRIG_EXT && CR_CHAN(cmd->stop_arg))
			bits |= EXT_STOP_TRIG_BNC_BIT;
		ग_लिखोw(bits, devpriv->मुख्य_iobase + DAQ_ATRIG_LOW_4020_REG);
	पूर्ण

	spin_lock_irqsave(&dev->spinlock, flags);

	/* enable pacing, triggering, etc */
	bits = ADC_ENABLE_BIT | ADC_SOFT_GATE_BITS | ADC_GATE_LEVEL_BIT;
	अगर (cmd->flags & CMDF_WAKE_EOS)
		bits |= ADC_DMA_DISABLE_BIT;
	/* set start trigger */
	अगर (cmd->start_src == TRIG_EXT) अणु
		bits |= ADC_START_TRIG_EXT_BITS;
		अगर (cmd->start_arg & CR_INVERT)
			bits |= ADC_START_TRIG_FALLING_BIT;
	पूर्ण अन्यथा अगर (cmd->start_src == TRIG_NOW) अणु
		bits |= ADC_START_TRIG_SOFT_BITS;
	पूर्ण
	अगर (use_hw_sample_counter(cmd))
		bits |= ADC_SAMPLE_COUNTER_EN_BIT;
	ग_लिखोw(bits, devpriv->मुख्य_iobase + ADC_CONTROL0_REG);

	devpriv->ai_cmd_running = 1;

	spin_unlock_irqrestore(&dev->spinlock, flags);

	/* start acquisition */
	अगर (cmd->start_src == TRIG_NOW)
		ग_लिखोw(0, devpriv->मुख्य_iobase + ADC_START_REG);

	वापस 0;
पूर्ण

/* पढ़ो num_samples from 16 bit wide ai fअगरo */
अटल व्योम pio_drain_ai_fअगरo_16(काष्ठा comedi_device *dev)
अणु
	काष्ठा pcidas64_निजी *devpriv = dev->निजी;
	काष्ठा comedi_subdevice *s = dev->पढ़ो_subdev;
	अचिन्हित पूर्णांक i;
	u16 prepost_bits;
	पूर्णांक पढ़ो_segment, पढ़ो_index, ग_लिखो_segment, ग_लिखो_index;
	पूर्णांक num_samples;

	करो अणु
		/* get least signअगरicant 15 bits */
		पढ़ो_index = पढ़ोw(devpriv->मुख्य_iobase + ADC_READ_PNTR_REG) &
			     0x7fff;
		ग_लिखो_index = पढ़ोw(devpriv->मुख्य_iobase + ADC_WRITE_PNTR_REG) &
			      0x7fff;
		/*
		 * Get most signअगरicant bits (grey code).
		 * Dअगरferent boards use dअगरferent code so use a scheme
		 * that करोesn't depend on encoding.  This पढ़ो must
		 * occur after पढ़ोing least signअगरicant 15 bits to aव्योम race
		 * with fअगरo चयनing to next segment.
		 */
		prepost_bits = पढ़ोw(devpriv->मुख्य_iobase + PREPOST_REG);

		/*
		 * अगर पढ़ो and ग_लिखो poपूर्णांकers are not on the same fअगरo segment,
		 * पढ़ो to the end of the पढ़ो segment
		 */
		पढ़ो_segment = adc_upper_पढ़ो_ptr_code(prepost_bits);
		ग_लिखो_segment = adc_upper_ग_लिखो_ptr_code(prepost_bits);

		अगर (पढ़ो_segment != ग_लिखो_segment)
			num_samples =
				devpriv->ai_fअगरo_segment_length - पढ़ो_index;
		अन्यथा
			num_samples = ग_लिखो_index - पढ़ो_index;
		अगर (num_samples < 0) अणु
			dev_err(dev->class_dev,
				"cb_pcidas64: bug! num_samples < 0\n");
			अवरोध;
		पूर्ण

		num_samples = comedi_nsamples_left(s, num_samples);
		अगर (num_samples == 0)
			अवरोध;

		क्रम (i = 0; i < num_samples; i++) अणु
			अचिन्हित लघु val;

			val = पढ़ोw(devpriv->मुख्य_iobase + ADC_FIFO_REG);
			comedi_buf_ग_लिखो_samples(s, &val, 1);
		पूर्ण

	पूर्ण जबतक (पढ़ो_segment != ग_लिखो_segment);
पूर्ण

/*
 * Read from 32 bit wide ai fअगरo of 4020 - deal with insane grey coding of
 * poपूर्णांकers.  The pci-4020 hardware only supports dma transfers (it only
 * supports the use of pio क्रम draining the last reमुख्यing poपूर्णांकs from the
 * fअगरo when a data acquisition operation has completed).
 */
अटल व्योम pio_drain_ai_fअगरo_32(काष्ठा comedi_device *dev)
अणु
	काष्ठा pcidas64_निजी *devpriv = dev->निजी;
	काष्ठा comedi_subdevice *s = dev->पढ़ो_subdev;
	अचिन्हित पूर्णांक nsamples;
	अचिन्हित पूर्णांक i;
	u32 fअगरo_data;
	पूर्णांक ग_लिखो_code =
		पढ़ोw(devpriv->मुख्य_iobase + ADC_WRITE_PNTR_REG) & 0x7fff;
	पूर्णांक पढ़ो_code =
		पढ़ोw(devpriv->मुख्य_iobase + ADC_READ_PNTR_REG) & 0x7fff;

	nsamples = comedi_nsamples_left(s, 100000);
	क्रम (i = 0; पढ़ो_code != ग_लिखो_code && i < nsamples;) अणु
		अचिन्हित लघु val;

		fअगरo_data = पढ़ोl(dev->mmio + ADC_FIFO_REG);
		val = fअगरo_data & 0xffff;
		comedi_buf_ग_लिखो_samples(s, &val, 1);
		i++;
		अगर (i < nsamples) अणु
			val = (fअगरo_data >> 16) & 0xffff;
			comedi_buf_ग_लिखो_samples(s, &val, 1);
			i++;
		पूर्ण
		पढ़ो_code = पढ़ोw(devpriv->मुख्य_iobase + ADC_READ_PNTR_REG) &
			    0x7fff;
	पूर्ण
पूर्ण

/* empty fअगरo */
अटल व्योम pio_drain_ai_fअगरo(काष्ठा comedi_device *dev)
अणु
	स्थिर काष्ठा pcidas64_board *board = dev->board_ptr;

	अगर (board->layout == LAYOUT_4020)
		pio_drain_ai_fअगरo_32(dev);
	अन्यथा
		pio_drain_ai_fअगरo_16(dev);
पूर्ण

अटल व्योम drain_dma_buffers(काष्ठा comedi_device *dev, अचिन्हित पूर्णांक channel)
अणु
	स्थिर काष्ठा pcidas64_board *board = dev->board_ptr;
	काष्ठा pcidas64_निजी *devpriv = dev->निजी;
	काष्ठा comedi_subdevice *s = dev->पढ़ो_subdev;
	u32 next_transfer_addr;
	पूर्णांक j;
	पूर्णांक num_samples = 0;
	व्योम __iomem *pci_addr_reg;

	pci_addr_reg = devpriv->plx9080_iobase + PLX_REG_DMAPADR(channel);

	/* loop until we have पढ़ो all the full buffers */
	क्रम (j = 0, next_transfer_addr = पढ़ोl(pci_addr_reg);
	     (next_transfer_addr <
	      devpriv->ai_buffer_bus_addr[devpriv->ai_dma_index] ||
	      next_transfer_addr >=
	      devpriv->ai_buffer_bus_addr[devpriv->ai_dma_index] +
	      DMA_BUFFER_SIZE) && j < ai_dma_ring_count(board); j++) अणु
		/* transfer data from dma buffer to comedi buffer */
		num_samples = comedi_nsamples_left(s, dma_transfer_size(dev));
		comedi_buf_ग_लिखो_samples(s,
				devpriv->ai_buffer[devpriv->ai_dma_index],
				num_samples);
		devpriv->ai_dma_index = (devpriv->ai_dma_index + 1) %
					ai_dma_ring_count(board);
	पूर्ण
	/*
	 * XXX check क्रम dma ring buffer overrun
	 * (use end-of-chain bit to mark last unused buffer)
	 */
पूर्ण

अटल व्योम handle_ai_पूर्णांकerrupt(काष्ठा comedi_device *dev,
				अचिन्हित लघु status,
				अचिन्हित पूर्णांक plx_status)
अणु
	स्थिर काष्ठा pcidas64_board *board = dev->board_ptr;
	काष्ठा pcidas64_निजी *devpriv = dev->निजी;
	काष्ठा comedi_subdevice *s = dev->पढ़ो_subdev;
	काष्ठा comedi_async *async = s->async;
	काष्ठा comedi_cmd *cmd = &async->cmd;
	u8 dma1_status;
	अचिन्हित दीर्घ flags;

	/* check क्रम fअगरo overrun */
	अगर (status & ADC_OVERRUN_BIT) अणु
		dev_err(dev->class_dev, "fifo overrun\n");
		async->events |= COMEDI_CB_ERROR;
	पूर्ण
	/* spin lock makes sure no one अन्यथा changes plx dma control reg */
	spin_lock_irqsave(&dev->spinlock, flags);
	dma1_status = पढ़ोb(devpriv->plx9080_iobase + PLX_REG_DMACSR1);
	अगर (plx_status & PLX_INTCSR_DMA1IA) अणु	/* dma chan 1 पूर्णांकerrupt */
		ग_लिखोb((dma1_status & PLX_DMACSR_ENABLE) | PLX_DMACSR_CLEARINTR,
		       devpriv->plx9080_iobase + PLX_REG_DMACSR1);

		अगर (dma1_status & PLX_DMACSR_ENABLE)
			drain_dma_buffers(dev, 1);
	पूर्ण
	spin_unlock_irqrestore(&dev->spinlock, flags);

	/* drain fअगरo with pio */
	अगर ((status & ADC_DONE_BIT) ||
	    ((cmd->flags & CMDF_WAKE_EOS) &&
	     (status & ADC_INTR_PENDING_BIT) &&
	     (board->layout != LAYOUT_4020))) अणु
		spin_lock_irqsave(&dev->spinlock, flags);
		अगर (devpriv->ai_cmd_running) अणु
			spin_unlock_irqrestore(&dev->spinlock, flags);
			pio_drain_ai_fअगरo(dev);
		पूर्ण अन्यथा अणु
			spin_unlock_irqrestore(&dev->spinlock, flags);
		पूर्ण
	पूर्ण
	/* अगर we are have all the data, then quit */
	अगर ((cmd->stop_src == TRIG_COUNT &&
	     async->scans_करोne >= cmd->stop_arg) ||
	    (cmd->stop_src == TRIG_EXT && (status & ADC_STOP_BIT)))
		async->events |= COMEDI_CB_EOA;

	comedi_handle_events(dev, s);
पूर्ण

अटल अंतरभूत अचिन्हित पूर्णांक prev_ao_dma_index(काष्ठा comedi_device *dev)
अणु
	काष्ठा pcidas64_निजी *devpriv = dev->निजी;
	अचिन्हित पूर्णांक buffer_index;

	अगर (devpriv->ao_dma_index == 0)
		buffer_index = AO_DMA_RING_COUNT - 1;
	अन्यथा
		buffer_index = devpriv->ao_dma_index - 1;
	वापस buffer_index;
पूर्ण

अटल पूर्णांक last_ao_dma_load_completed(काष्ठा comedi_device *dev)
अणु
	काष्ठा pcidas64_निजी *devpriv = dev->निजी;
	अचिन्हित पूर्णांक buffer_index;
	अचिन्हित पूर्णांक transfer_address;
	अचिन्हित लघु dma_status;

	buffer_index = prev_ao_dma_index(dev);
	dma_status = पढ़ोb(devpriv->plx9080_iobase + PLX_REG_DMACSR0);
	अगर ((dma_status & PLX_DMACSR_DONE) == 0)
		वापस 0;

	transfer_address =
		पढ़ोl(devpriv->plx9080_iobase + PLX_REG_DMAPADR0);
	अगर (transfer_address != devpriv->ao_buffer_bus_addr[buffer_index])
		वापस 0;

	वापस 1;
पूर्ण

अटल अंतरभूत पूर्णांक ao_dma_needs_restart(काष्ठा comedi_device *dev,
				       अचिन्हित लघु dma_status)
अणु
	अगर ((dma_status & PLX_DMACSR_DONE) == 0 ||
	    (dma_status & PLX_DMACSR_ENABLE) == 0)
		वापस 0;
	अगर (last_ao_dma_load_completed(dev))
		वापस 0;

	वापस 1;
पूर्ण

अटल व्योम restart_ao_dma(काष्ठा comedi_device *dev)
अणु
	काष्ठा pcidas64_निजी *devpriv = dev->निजी;
	अचिन्हित पूर्णांक dma_desc_bits;

	dma_desc_bits = पढ़ोl(devpriv->plx9080_iobase + PLX_REG_DMADPR0);
	dma_desc_bits &= ~PLX_DMADPR_CHAINEND;
	load_first_dma_descriptor(dev, 0, dma_desc_bits);

	dma_start_sync(dev, 0);
पूर्ण

अटल अचिन्हित पूर्णांक cb_pcidas64_ao_fill_buffer(काष्ठा comedi_device *dev,
					       काष्ठा comedi_subdevice *s,
					       अचिन्हित लघु *dest,
					       अचिन्हित पूर्णांक max_bytes)
अणु
	अचिन्हित पूर्णांक nsamples = comedi_bytes_to_samples(s, max_bytes);
	अचिन्हित पूर्णांक actual_bytes;

	nsamples = comedi_nsamples_left(s, nsamples);
	actual_bytes = comedi_buf_पढ़ो_samples(s, dest, nsamples);

	वापस comedi_bytes_to_samples(s, actual_bytes);
पूर्ण

अटल अचिन्हित पूर्णांक load_ao_dma_buffer(काष्ठा comedi_device *dev,
				       स्थिर काष्ठा comedi_cmd *cmd)
अणु
	काष्ठा pcidas64_निजी *devpriv = dev->निजी;
	काष्ठा comedi_subdevice *s = dev->ग_लिखो_subdev;
	अचिन्हित पूर्णांक buffer_index = devpriv->ao_dma_index;
	अचिन्हित पूर्णांक prev_buffer_index = prev_ao_dma_index(dev);
	अचिन्हित पूर्णांक nsamples;
	अचिन्हित पूर्णांक nbytes;
	अचिन्हित पूर्णांक next_bits;

	nsamples = cb_pcidas64_ao_fill_buffer(dev, s,
					      devpriv->ao_buffer[buffer_index],
					      DMA_BUFFER_SIZE);
	अगर (nsamples == 0)
		वापस 0;

	nbytes = comedi_samples_to_bytes(s, nsamples);
	devpriv->ao_dma_desc[buffer_index].transfer_size = cpu_to_le32(nbytes);
	/* set end of chain bit so we catch underruns */
	next_bits = le32_to_cpu(devpriv->ao_dma_desc[buffer_index].next);
	next_bits |= PLX_DMADPR_CHAINEND;
	devpriv->ao_dma_desc[buffer_index].next = cpu_to_le32(next_bits);
	/*
	 * clear end of chain bit on previous buffer now that we have set it
	 * क्रम the last buffer
	 */
	next_bits = le32_to_cpu(devpriv->ao_dma_desc[prev_buffer_index].next);
	next_bits &= ~PLX_DMADPR_CHAINEND;
	devpriv->ao_dma_desc[prev_buffer_index].next = cpu_to_le32(next_bits);

	devpriv->ao_dma_index = (buffer_index + 1) % AO_DMA_RING_COUNT;

	वापस nbytes;
पूर्ण

अटल व्योम load_ao_dma(काष्ठा comedi_device *dev, स्थिर काष्ठा comedi_cmd *cmd)
अणु
	काष्ठा pcidas64_निजी *devpriv = dev->निजी;
	अचिन्हित पूर्णांक num_bytes;
	अचिन्हित पूर्णांक next_transfer_addr;
	व्योम __iomem *pci_addr_reg = devpriv->plx9080_iobase + PLX_REG_DMAPADR0;
	अचिन्हित पूर्णांक buffer_index;

	करो अणु
		buffer_index = devpriv->ao_dma_index;
		/* करोn't overwrite data that hasn't been transferred yet */
		next_transfer_addr = पढ़ोl(pci_addr_reg);
		अगर (next_transfer_addr >=
		    devpriv->ao_buffer_bus_addr[buffer_index] &&
		    next_transfer_addr <
		    devpriv->ao_buffer_bus_addr[buffer_index] +
		    DMA_BUFFER_SIZE)
			वापस;
		num_bytes = load_ao_dma_buffer(dev, cmd);
	पूर्ण जबतक (num_bytes >= DMA_BUFFER_SIZE);
पूर्ण

अटल व्योम handle_ao_पूर्णांकerrupt(काष्ठा comedi_device *dev,
				अचिन्हित लघु status, अचिन्हित पूर्णांक plx_status)
अणु
	काष्ठा pcidas64_निजी *devpriv = dev->निजी;
	काष्ठा comedi_subdevice *s = dev->ग_लिखो_subdev;
	काष्ठा comedi_async *async;
	काष्ठा comedi_cmd *cmd;
	u8 dma0_status;
	अचिन्हित दीर्घ flags;

	/* board might not support ao, in which हाल ग_लिखो_subdev is शून्य */
	अगर (!s)
		वापस;
	async = s->async;
	cmd = &async->cmd;

	/* spin lock makes sure no one अन्यथा changes plx dma control reg */
	spin_lock_irqsave(&dev->spinlock, flags);
	dma0_status = पढ़ोb(devpriv->plx9080_iobase + PLX_REG_DMACSR0);
	अगर (plx_status & PLX_INTCSR_DMA0IA) अणु	/*  dma chan 0 पूर्णांकerrupt */
		अगर ((dma0_status & PLX_DMACSR_ENABLE) &&
		    !(dma0_status & PLX_DMACSR_DONE)) अणु
			ग_लिखोb(PLX_DMACSR_ENABLE | PLX_DMACSR_CLEARINTR,
			       devpriv->plx9080_iobase + PLX_REG_DMACSR0);
		पूर्ण अन्यथा अणु
			ग_लिखोb(PLX_DMACSR_CLEARINTR,
			       devpriv->plx9080_iobase + PLX_REG_DMACSR0);
		पूर्ण
		spin_unlock_irqrestore(&dev->spinlock, flags);
		अगर (dma0_status & PLX_DMACSR_ENABLE) अणु
			load_ao_dma(dev, cmd);
			/* try to recover from dma end-of-chain event */
			अगर (ao_dma_needs_restart(dev, dma0_status))
				restart_ao_dma(dev);
		पूर्ण
	पूर्ण अन्यथा अणु
		spin_unlock_irqrestore(&dev->spinlock, flags);
	पूर्ण

	अगर ((status & DAC_DONE_BIT)) अणु
		अगर ((cmd->stop_src == TRIG_COUNT &&
		     async->scans_करोne >= cmd->stop_arg) ||
		    last_ao_dma_load_completed(dev))
			async->events |= COMEDI_CB_EOA;
		अन्यथा
			async->events |= COMEDI_CB_ERROR;
	पूर्ण
	comedi_handle_events(dev, s);
पूर्ण

अटल irqवापस_t handle_पूर्णांकerrupt(पूर्णांक irq, व्योम *d)
अणु
	काष्ठा comedi_device *dev = d;
	काष्ठा pcidas64_निजी *devpriv = dev->निजी;
	अचिन्हित लघु status;
	u32 plx_status;
	u32 plx_bits;

	plx_status = पढ़ोl(devpriv->plx9080_iobase + PLX_REG_INTCSR);
	status = पढ़ोw(devpriv->मुख्य_iobase + HW_STATUS_REG);

	/*
	 * an पूर्णांकerrupt beक्रमe all the postconfig stuff माला_लो करोne could
	 * cause a शून्य dereference अगर we जारी through the
	 * पूर्णांकerrupt handler
	 */
	अगर (!dev->attached)
		वापस IRQ_HANDLED;

	handle_ai_पूर्णांकerrupt(dev, status, plx_status);
	handle_ao_पूर्णांकerrupt(dev, status, plx_status);

	/* clear possible plx9080 पूर्णांकerrupt sources */
	अगर (plx_status & PLX_INTCSR_LDBIA) अणु
		/* clear local करोorbell पूर्णांकerrupt */
		plx_bits = पढ़ोl(devpriv->plx9080_iobase + PLX_REG_L2PDBELL);
		ग_लिखोl(plx_bits, devpriv->plx9080_iobase + PLX_REG_L2PDBELL);
	पूर्ण

	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक ai_cancel(काष्ठा comedi_device *dev, काष्ठा comedi_subdevice *s)
अणु
	काष्ठा pcidas64_निजी *devpriv = dev->निजी;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&dev->spinlock, flags);
	अगर (devpriv->ai_cmd_running == 0) अणु
		spin_unlock_irqrestore(&dev->spinlock, flags);
		वापस 0;
	पूर्ण
	devpriv->ai_cmd_running = 0;
	spin_unlock_irqrestore(&dev->spinlock, flags);

	disable_ai_pacing(dev);

	पात_dma(dev, 1);

	वापस 0;
पूर्ण

अटल पूर्णांक ao_winsn(काष्ठा comedi_device *dev, काष्ठा comedi_subdevice *s,
		    काष्ठा comedi_insn *insn, अचिन्हित पूर्णांक *data)
अणु
	स्थिर काष्ठा pcidas64_board *board = dev->board_ptr;
	काष्ठा pcidas64_निजी *devpriv = dev->निजी;
	अचिन्हित पूर्णांक chan = CR_CHAN(insn->chanspec);
	अचिन्हित पूर्णांक range = CR_RANGE(insn->chanspec);
	अचिन्हित पूर्णांक val = s->पढ़ोback[chan];
	अचिन्हित पूर्णांक i;

	/* करो some initializing */
	ग_लिखोw(0, devpriv->मुख्य_iobase + DAC_CONTROL0_REG);

	/* set range */
	set_dac_range_bits(dev, &devpriv->dac_control1_bits, chan, range);
	ग_लिखोw(devpriv->dac_control1_bits,
	       devpriv->मुख्य_iobase + DAC_CONTROL1_REG);

	क्रम (i = 0; i < insn->n; i++) अणु
		/* ग_लिखो to channel */
		val = data[i];
		अगर (board->layout == LAYOUT_4020) अणु
			ग_लिखोw(val & 0xff,
			       devpriv->मुख्य_iobase + dac_lsb_4020_reg(chan));
			ग_लिखोw((val >> 8) & 0xf,
			       devpriv->मुख्य_iobase + dac_msb_4020_reg(chan));
		पूर्ण अन्यथा अणु
			ग_लिखोw(val,
			       devpriv->मुख्य_iobase + dac_convert_reg(chan));
		पूर्ण
	पूर्ण

	/* remember last output value */
	s->पढ़ोback[chan] = val;

	वापस insn->n;
पूर्ण

अटल व्योम set_dac_control0_reg(काष्ठा comedi_device *dev,
				 स्थिर काष्ठा comedi_cmd *cmd)
अणु
	काष्ठा pcidas64_निजी *devpriv = dev->निजी;
	अचिन्हित पूर्णांक bits = DAC_ENABLE_BIT | WAVEFORM_GATE_LEVEL_BIT |
			    WAVEFORM_GATE_ENABLE_BIT | WAVEFORM_GATE_SELECT_BIT;

	अगर (cmd->start_src == TRIG_EXT) अणु
		bits |= WAVEFORM_TRIG_EXT_BITS;
		अगर (cmd->start_arg & CR_INVERT)
			bits |= WAVEFORM_TRIG_FALLING_BIT;
	पूर्ण अन्यथा अणु
		bits |= WAVEFORM_TRIG_SOFT_BITS;
	पूर्ण
	अगर (cmd->scan_begin_src == TRIG_EXT) अणु
		bits |= DAC_EXT_UPDATE_ENABLE_BIT;
		अगर (cmd->scan_begin_arg & CR_INVERT)
			bits |= DAC_EXT_UPDATE_FALLING_BIT;
	पूर्ण
	ग_लिखोw(bits, devpriv->मुख्य_iobase + DAC_CONTROL0_REG);
पूर्ण

अटल व्योम set_dac_control1_reg(काष्ठा comedi_device *dev,
				 स्थिर काष्ठा comedi_cmd *cmd)
अणु
	काष्ठा pcidas64_निजी *devpriv = dev->निजी;
	पूर्णांक i;

	क्रम (i = 0; i < cmd->chanlist_len; i++) अणु
		पूर्णांक channel, range;

		channel = CR_CHAN(cmd->chanlist[i]);
		range = CR_RANGE(cmd->chanlist[i]);
		set_dac_range_bits(dev, &devpriv->dac_control1_bits, channel,
				   range);
	पूर्ण
	devpriv->dac_control1_bits |= DAC_SW_GATE_BIT;
	ग_लिखोw(devpriv->dac_control1_bits,
	       devpriv->मुख्य_iobase + DAC_CONTROL1_REG);
पूर्ण

अटल व्योम set_dac_select_reg(काष्ठा comedi_device *dev,
			       स्थिर काष्ठा comedi_cmd *cmd)
अणु
	काष्ठा pcidas64_निजी *devpriv = dev->निजी;
	u16 bits;
	अचिन्हित पूर्णांक first_channel, last_channel;

	first_channel = CR_CHAN(cmd->chanlist[0]);
	last_channel = CR_CHAN(cmd->chanlist[cmd->chanlist_len - 1]);
	अगर (last_channel < first_channel)
		dev_err(dev->class_dev,
			"bug! last ao channel < first ao channel\n");

	bits = (first_channel & 0x7) | (last_channel & 0x7) << 3;

	ग_लिखोw(bits, devpriv->मुख्य_iobase + DAC_SELECT_REG);
पूर्ण

अटल अचिन्हित पूर्णांक get_ao_भागisor(अचिन्हित पूर्णांक ns, अचिन्हित पूर्णांक flags)
अणु
	वापस get_भागisor(ns, flags) - 2;
पूर्ण

अटल व्योम set_dac_पूर्णांकerval_regs(काष्ठा comedi_device *dev,
				  स्थिर काष्ठा comedi_cmd *cmd)
अणु
	काष्ठा pcidas64_निजी *devpriv = dev->निजी;
	अचिन्हित पूर्णांक भागisor;

	अगर (cmd->scan_begin_src != TRIG_TIMER)
		वापस;

	भागisor = get_ao_भागisor(cmd->scan_begin_arg, cmd->flags);
	अगर (भागisor > max_counter_value) अणु
		dev_err(dev->class_dev, "bug! ao divisor too big\n");
		भागisor = max_counter_value;
	पूर्ण
	ग_लिखोw(भागisor & 0xffff,
	       devpriv->मुख्य_iobase + DAC_SAMPLE_INTERVAL_LOWER_REG);
	ग_लिखोw((भागisor >> 16) & 0xff,
	       devpriv->मुख्य_iobase + DAC_SAMPLE_INTERVAL_UPPER_REG);
पूर्ण

अटल पूर्णांक prep_ao_dma(काष्ठा comedi_device *dev, स्थिर काष्ठा comedi_cmd *cmd)
अणु
	काष्ठा pcidas64_निजी *devpriv = dev->निजी;
	काष्ठा comedi_subdevice *s = dev->ग_लिखो_subdev;
	अचिन्हित पूर्णांक nsamples;
	अचिन्हित पूर्णांक nbytes;
	पूर्णांक i;

	/*
	 * clear queue poपूर्णांकer too, since बाह्यal queue has
	 * weird पूर्णांकeractions with ao fअगरo
	 */
	ग_लिखोw(0, devpriv->मुख्य_iobase + ADC_QUEUE_CLEAR_REG);
	ग_लिखोw(0, devpriv->मुख्य_iobase + DAC_BUFFER_CLEAR_REG);

	nsamples = cb_pcidas64_ao_fill_buffer(dev, s,
					      devpriv->ao_bounce_buffer,
					      DAC_FIFO_SIZE);
	अगर (nsamples == 0)
		वापस -1;

	क्रम (i = 0; i < nsamples; i++) अणु
		ग_लिखोw(devpriv->ao_bounce_buffer[i],
		       devpriv->मुख्य_iobase + DAC_FIFO_REG);
	पूर्ण

	अगर (cmd->stop_src == TRIG_COUNT &&
	    s->async->scans_करोne >= cmd->stop_arg)
		वापस 0;

	nbytes = load_ao_dma_buffer(dev, cmd);
	अगर (nbytes == 0)
		वापस -1;
	load_ao_dma(dev, cmd);

	dma_start_sync(dev, 0);

	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक बाह्यal_ai_queue_in_use(काष्ठा comedi_device *dev)
अणु
	स्थिर काष्ठा pcidas64_board *board = dev->board_ptr;

	अगर (!dev->पढ़ो_subdev->busy)
		वापस 0;
	अगर (board->layout == LAYOUT_4020)
		वापस 0;
	अन्यथा अगर (use_पूर्णांकernal_queue_6xxx(&dev->पढ़ो_subdev->async->cmd))
		वापस 0;
	वापस 1;
पूर्ण

अटल पूर्णांक ao_पूर्णांकtrig(काष्ठा comedi_device *dev, काष्ठा comedi_subdevice *s,
		      अचिन्हित पूर्णांक trig_num)
अणु
	काष्ठा pcidas64_निजी *devpriv = dev->निजी;
	काष्ठा comedi_cmd *cmd = &s->async->cmd;
	पूर्णांक retval;

	अगर (trig_num != cmd->start_arg)
		वापस -EINVAL;

	retval = prep_ao_dma(dev, cmd);
	अगर (retval < 0)
		वापस -EPIPE;

	set_dac_control0_reg(dev, cmd);

	अगर (cmd->start_src == TRIG_INT)
		ग_लिखोw(0, devpriv->मुख्य_iobase + DAC_START_REG);

	s->async->पूर्णांकtrig = शून्य;

	वापस 0;
पूर्ण

अटल पूर्णांक ao_cmd(काष्ठा comedi_device *dev, काष्ठा comedi_subdevice *s)
अणु
	काष्ठा pcidas64_निजी *devpriv = dev->निजी;
	काष्ठा comedi_cmd *cmd = &s->async->cmd;

	अगर (बाह्यal_ai_queue_in_use(dev)) अणु
		warn_बाह्यal_queue(dev);
		वापस -EBUSY;
	पूर्ण
	/* disable analog output प्रणाली during setup */
	ग_लिखोw(0x0, devpriv->मुख्य_iobase + DAC_CONTROL0_REG);

	devpriv->ao_dma_index = 0;

	set_dac_select_reg(dev, cmd);
	set_dac_पूर्णांकerval_regs(dev, cmd);
	load_first_dma_descriptor(dev, 0, devpriv->ao_dma_desc_bus_addr |
				  PLX_DMADPR_DESCPCI | PLX_DMADPR_TCINTR);

	set_dac_control1_reg(dev, cmd);
	s->async->पूर्णांकtrig = ao_पूर्णांकtrig;

	वापस 0;
पूर्ण

अटल पूर्णांक cb_pcidas64_ao_check_chanlist(काष्ठा comedi_device *dev,
					 काष्ठा comedi_subdevice *s,
					 काष्ठा comedi_cmd *cmd)
अणु
	अचिन्हित पूर्णांक chan0 = CR_CHAN(cmd->chanlist[0]);
	पूर्णांक i;

	क्रम (i = 1; i < cmd->chanlist_len; i++) अणु
		अचिन्हित पूर्णांक chan = CR_CHAN(cmd->chanlist[i]);

		अगर (chan != (chan0 + i)) अणु
			dev_dbg(dev->class_dev,
				"chanlist must use consecutive channels\n");
			वापस -EINVAL;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक ao_cmdtest(काष्ठा comedi_device *dev, काष्ठा comedi_subdevice *s,
		      काष्ठा comedi_cmd *cmd)
अणु
	स्थिर काष्ठा pcidas64_board *board = dev->board_ptr;
	पूर्णांक err = 0;
	अचिन्हित पूर्णांक पंचांगp_arg;

	/* Step 1 : check अगर triggers are trivially valid */

	err |= comedi_check_trigger_src(&cmd->start_src, TRIG_INT | TRIG_EXT);
	err |= comedi_check_trigger_src(&cmd->scan_begin_src,
					TRIG_TIMER | TRIG_EXT);
	err |= comedi_check_trigger_src(&cmd->convert_src, TRIG_NOW);
	err |= comedi_check_trigger_src(&cmd->scan_end_src, TRIG_COUNT);
	err |= comedi_check_trigger_src(&cmd->stop_src, TRIG_NONE);

	अगर (err)
		वापस 1;

	/* Step 2a : make sure trigger sources are unique */

	err |= comedi_check_trigger_is_unique(cmd->start_src);
	err |= comedi_check_trigger_is_unique(cmd->scan_begin_src);

	/* Step 2b : and mutually compatible */

	अगर (cmd->convert_src == TRIG_EXT && cmd->scan_begin_src == TRIG_TIMER)
		err |= -EINVAL;
	अगर (cmd->stop_src != TRIG_COUNT &&
	    cmd->stop_src != TRIG_NONE && cmd->stop_src != TRIG_EXT)
		err |= -EINVAL;

	अगर (err)
		वापस 2;

	/* Step 3: check अगर arguments are trivially valid */

	err |= comedi_check_trigger_arg_is(&cmd->start_arg, 0);

	अगर (cmd->scan_begin_src == TRIG_TIMER) अणु
		err |= comedi_check_trigger_arg_min(&cmd->scan_begin_arg,
						    board->ao_scan_speed);
		अगर (get_ao_भागisor(cmd->scan_begin_arg, cmd->flags) >
		    max_counter_value) अणु
			cmd->scan_begin_arg = (max_counter_value + 2) *
					      TIMER_BASE;
			err |= -EINVAL;
		पूर्ण
	पूर्ण

	err |= comedi_check_trigger_arg_min(&cmd->chanlist_len, 1);
	err |= comedi_check_trigger_arg_is(&cmd->scan_end_arg,
					   cmd->chanlist_len);

	अगर (err)
		वापस 3;

	/* step 4: fix up any arguments */

	अगर (cmd->scan_begin_src == TRIG_TIMER) अणु
		पंचांगp_arg = cmd->scan_begin_arg;
		cmd->scan_begin_arg = get_भागisor(cmd->scan_begin_arg,
						  cmd->flags) * TIMER_BASE;
		अगर (पंचांगp_arg != cmd->scan_begin_arg)
			err++;
	पूर्ण

	अगर (err)
		वापस 4;

	/* Step 5: check channel list अगर it exists */
	अगर (cmd->chanlist && cmd->chanlist_len > 0)
		err |= cb_pcidas64_ao_check_chanlist(dev, s, cmd);

	अगर (err)
		वापस 5;

	वापस 0;
पूर्ण

अटल पूर्णांक ao_cancel(काष्ठा comedi_device *dev, काष्ठा comedi_subdevice *s)
अणु
	काष्ठा pcidas64_निजी *devpriv = dev->निजी;

	ग_लिखोw(0x0, devpriv->मुख्य_iobase + DAC_CONTROL0_REG);
	पात_dma(dev, 0);
	वापस 0;
पूर्ण

अटल पूर्णांक dio_callback_4020(काष्ठा comedi_device *dev,
			     पूर्णांक dir, पूर्णांक port, पूर्णांक data, अचिन्हित दीर्घ iobase)
अणु
	काष्ठा pcidas64_निजी *devpriv = dev->निजी;

	अगर (dir) अणु
		ग_लिखोw(data, devpriv->मुख्य_iobase + iobase + 2 * port);
		वापस 0;
	पूर्ण
	वापस पढ़ोw(devpriv->मुख्य_iobase + iobase + 2 * port);
पूर्ण

अटल पूर्णांक di_rbits(काष्ठा comedi_device *dev, काष्ठा comedi_subdevice *s,
		    काष्ठा comedi_insn *insn, अचिन्हित पूर्णांक *data)
अणु
	अचिन्हित पूर्णांक bits;

	bits = पढ़ोb(dev->mmio + DI_REG);
	bits &= 0xf;
	data[1] = bits;
	data[0] = 0;

	वापस insn->n;
पूर्ण

अटल पूर्णांक करो_wbits(काष्ठा comedi_device *dev,
		    काष्ठा comedi_subdevice *s,
		    काष्ठा comedi_insn *insn,
		    अचिन्हित पूर्णांक *data)
अणु
	अगर (comedi_dio_update_state(s, data))
		ग_लिखोb(s->state, dev->mmio + DO_REG);

	data[1] = s->state;

	वापस insn->n;
पूर्ण

अटल पूर्णांक dio_60xx_config_insn(काष्ठा comedi_device *dev,
				काष्ठा comedi_subdevice *s,
				काष्ठा comedi_insn *insn,
				अचिन्हित पूर्णांक *data)
अणु
	पूर्णांक ret;

	ret = comedi_dio_insn_config(dev, s, insn, data, 0);
	अगर (ret)
		वापस ret;

	ग_लिखोb(s->io_bits, dev->mmio + DIO_सूचीECTION_60XX_REG);

	वापस insn->n;
पूर्ण

अटल पूर्णांक dio_60xx_wbits(काष्ठा comedi_device *dev,
			  काष्ठा comedi_subdevice *s,
			  काष्ठा comedi_insn *insn,
			  अचिन्हित पूर्णांक *data)
अणु
	अगर (comedi_dio_update_state(s, data))
		ग_लिखोb(s->state, dev->mmio + DIO_DATA_60XX_REG);

	data[1] = पढ़ोb(dev->mmio + DIO_DATA_60XX_REG);

	वापस insn->n;
पूर्ण

/*
 * pci-6025 8800 caldac:
 * address 0 == dac channel 0 offset
 * address 1 == dac channel 0 gain
 * address 2 == dac channel 1 offset
 * address 3 == dac channel 1 gain
 * address 4 == fine adc offset
 * address 5 == coarse adc offset
 * address 6 == coarse adc gain
 * address 7 == fine adc gain
 */
/*
 * pci-6402/16 uses all 8 channels क्रम dac:
 * address 0 == dac channel 0 fine gain
 * address 1 == dac channel 0 coarse gain
 * address 2 == dac channel 0 coarse offset
 * address 3 == dac channel 1 coarse offset
 * address 4 == dac channel 1 fine gain
 * address 5 == dac channel 1 coarse gain
 * address 6 == dac channel 0 fine offset
 * address 7 == dac channel 1 fine offset
 */

अटल पूर्णांक caldac_8800_ग_लिखो(काष्ठा comedi_device *dev, अचिन्हित पूर्णांक address,
			     u8 value)
अणु
	काष्ठा pcidas64_निजी *devpriv = dev->निजी;
	अटल स्थिर पूर्णांक num_caldac_channels = 8;
	अटल स्थिर पूर्णांक bitstream_length = 11;
	अचिन्हित पूर्णांक bitstream = ((address & 0x7) << 8) | value;
	अचिन्हित पूर्णांक bit, रेजिस्टर_bits;
	अटल स्थिर पूर्णांक caldac_8800_udelay = 1;

	अगर (address >= num_caldac_channels) अणु
		dev_err(dev->class_dev, "illegal caldac channel\n");
		वापस -1;
	पूर्ण
	क्रम (bit = 1 << (bitstream_length - 1); bit; bit >>= 1) अणु
		रेजिस्टर_bits = 0;
		अगर (bitstream & bit)
			रेजिस्टर_bits |= SERIAL_DATA_IN_BIT;
		udelay(caldac_8800_udelay);
		ग_लिखोw(रेजिस्टर_bits, devpriv->मुख्य_iobase + CALIBRATION_REG);
		रेजिस्टर_bits |= SERIAL_CLOCK_BIT;
		udelay(caldac_8800_udelay);
		ग_लिखोw(रेजिस्टर_bits, devpriv->मुख्य_iobase + CALIBRATION_REG);
	पूर्ण
	udelay(caldac_8800_udelay);
	ग_लिखोw(SELECT_8800_BIT, devpriv->मुख्य_iobase + CALIBRATION_REG);
	udelay(caldac_8800_udelay);
	ग_लिखोw(0, devpriv->मुख्य_iobase + CALIBRATION_REG);
	udelay(caldac_8800_udelay);
	वापस 0;
पूर्ण

/* 4020 caldacs */
अटल पूर्णांक caldac_i2c_ग_लिखो(काष्ठा comedi_device *dev,
			    अचिन्हित पूर्णांक caldac_channel, अचिन्हित पूर्णांक value)
अणु
	u8 serial_bytes[3];
	u8 i2c_addr;
	क्रमागत poपूर्णांकer_bits अणु
		/* manual has gain and offset bits चयनed */
		OFFSET_0_2 = 0x1,
		GAIN_0_2 = 0x2,
		OFFSET_1_3 = 0x4,
		GAIN_1_3 = 0x8,
	पूर्ण;
	क्रमागत data_bits अणु
		NOT_CLEAR_REGISTERS = 0x20,
	पूर्ण;

	चयन (caldac_channel) अणु
	हाल 0:					/* chan 0 offset */
		i2c_addr = CALDAC0_I2C_ADDR;
		serial_bytes[0] = OFFSET_0_2;
		अवरोध;
	हाल 1:					/* chan 1 offset */
		i2c_addr = CALDAC0_I2C_ADDR;
		serial_bytes[0] = OFFSET_1_3;
		अवरोध;
	हाल 2:					/* chan 2 offset */
		i2c_addr = CALDAC1_I2C_ADDR;
		serial_bytes[0] = OFFSET_0_2;
		अवरोध;
	हाल 3:					/* chan 3 offset */
		i2c_addr = CALDAC1_I2C_ADDR;
		serial_bytes[0] = OFFSET_1_3;
		अवरोध;
	हाल 4:					/* chan 0 gain */
		i2c_addr = CALDAC0_I2C_ADDR;
		serial_bytes[0] = GAIN_0_2;
		अवरोध;
	हाल 5:					/* chan 1 gain */
		i2c_addr = CALDAC0_I2C_ADDR;
		serial_bytes[0] = GAIN_1_3;
		अवरोध;
	हाल 6:					/* chan 2 gain */
		i2c_addr = CALDAC1_I2C_ADDR;
		serial_bytes[0] = GAIN_0_2;
		अवरोध;
	हाल 7:					/* chan 3 gain */
		i2c_addr = CALDAC1_I2C_ADDR;
		serial_bytes[0] = GAIN_1_3;
		अवरोध;
	शेष:
		dev_err(dev->class_dev, "invalid caldac channel\n");
		वापस -1;
	पूर्ण
	serial_bytes[1] = NOT_CLEAR_REGISTERS | ((value >> 8) & 0xf);
	serial_bytes[2] = value & 0xff;
	i2c_ग_लिखो(dev, i2c_addr, serial_bytes, 3);
	वापस 0;
पूर्ण

अटल व्योम caldac_ग_लिखो(काष्ठा comedi_device *dev, अचिन्हित पूर्णांक channel,
			 अचिन्हित पूर्णांक value)
अणु
	स्थिर काष्ठा pcidas64_board *board = dev->board_ptr;

	चयन (board->layout) अणु
	हाल LAYOUT_60XX:
	हाल LAYOUT_64XX:
		caldac_8800_ग_लिखो(dev, channel, value);
		अवरोध;
	हाल LAYOUT_4020:
		caldac_i2c_ग_लिखो(dev, channel, value);
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण
पूर्ण

अटल पूर्णांक cb_pcidas64_calib_insn_ग_लिखो(काष्ठा comedi_device *dev,
					काष्ठा comedi_subdevice *s,
					काष्ठा comedi_insn *insn,
					अचिन्हित पूर्णांक *data)
अणु
	अचिन्हित पूर्णांक chan = CR_CHAN(insn->chanspec);

	/*
	 * Programming the calib device is slow. Only ग_लिखो the
	 * last data value अगर the value has changed.
	 */
	अगर (insn->n) अणु
		अचिन्हित पूर्णांक val = data[insn->n - 1];

		अगर (s->पढ़ोback[chan] != val) अणु
			caldac_ग_लिखो(dev, chan, val);
			s->पढ़ोback[chan] = val;
		पूर्ण
	पूर्ण

	वापस insn->n;
पूर्ण

अटल व्योम ad8402_ग_लिखो(काष्ठा comedi_device *dev, अचिन्हित पूर्णांक channel,
			 अचिन्हित पूर्णांक value)
अणु
	काष्ठा pcidas64_निजी *devpriv = dev->निजी;
	अटल स्थिर पूर्णांक bitstream_length = 10;
	अचिन्हित पूर्णांक bit, रेजिस्टर_bits;
	अचिन्हित पूर्णांक bitstream = ((channel & 0x3) << 8) | (value & 0xff);
	अटल स्थिर पूर्णांक ad8402_udelay = 1;

	रेजिस्टर_bits = SELECT_8402_64XX_BIT;
	udelay(ad8402_udelay);
	ग_लिखोw(रेजिस्टर_bits, devpriv->मुख्य_iobase + CALIBRATION_REG);

	क्रम (bit = 1 << (bitstream_length - 1); bit; bit >>= 1) अणु
		अगर (bitstream & bit)
			रेजिस्टर_bits |= SERIAL_DATA_IN_BIT;
		अन्यथा
			रेजिस्टर_bits &= ~SERIAL_DATA_IN_BIT;
		udelay(ad8402_udelay);
		ग_लिखोw(रेजिस्टर_bits, devpriv->मुख्य_iobase + CALIBRATION_REG);
		udelay(ad8402_udelay);
		ग_लिखोw(रेजिस्टर_bits | SERIAL_CLOCK_BIT,
		       devpriv->मुख्य_iobase + CALIBRATION_REG);
	पूर्ण

	udelay(ad8402_udelay);
	ग_लिखोw(0, devpriv->मुख्य_iobase + CALIBRATION_REG);
पूर्ण

/* क्रम pci-das6402/16, channel 0 is analog input gain and channel 1 is offset */
अटल पूर्णांक cb_pcidas64_ad8402_insn_ग_लिखो(काष्ठा comedi_device *dev,
					 काष्ठा comedi_subdevice *s,
					 काष्ठा comedi_insn *insn,
					 अचिन्हित पूर्णांक *data)
अणु
	अचिन्हित पूर्णांक chan = CR_CHAN(insn->chanspec);

	/*
	 * Programming the calib device is slow. Only ग_लिखो the
	 * last data value अगर the value has changed.
	 */
	अगर (insn->n) अणु
		अचिन्हित पूर्णांक val = data[insn->n - 1];

		अगर (s->पढ़ोback[chan] != val) अणु
			ad8402_ग_लिखो(dev, chan, val);
			s->पढ़ोback[chan] = val;
		पूर्ण
	पूर्ण

	वापस insn->n;
पूर्ण

अटल u16 पढ़ो_eeprom(काष्ठा comedi_device *dev, u8 address)
अणु
	काष्ठा pcidas64_निजी *devpriv = dev->निजी;
	अटल स्थिर पूर्णांक bitstream_length = 11;
	अटल स्थिर पूर्णांक पढ़ो_command = 0x6;
	अचिन्हित पूर्णांक bitstream = (पढ़ो_command << 8) | address;
	अचिन्हित पूर्णांक bit;
	व्योम __iomem * स्थिर plx_control_addr =
		devpriv->plx9080_iobase + PLX_REG_CNTRL;
	u16 value;
	अटल स्थिर पूर्णांक value_length = 16;
	अटल स्थिर पूर्णांक eeprom_udelay = 1;

	udelay(eeprom_udelay);
	devpriv->plx_control_bits &= ~PLX_CNTRL_EESK & ~PLX_CNTRL_EECS;
	/* make sure we करोn't send anything to the i2c bus on 4020 */
	devpriv->plx_control_bits |= PLX_CNTRL_USERO;
	ग_लिखोl(devpriv->plx_control_bits, plx_control_addr);
	/* activate serial eeprom */
	udelay(eeprom_udelay);
	devpriv->plx_control_bits |= PLX_CNTRL_EECS;
	ग_लिखोl(devpriv->plx_control_bits, plx_control_addr);

	/* ग_लिखो पढ़ो command and desired memory address */
	क्रम (bit = 1 << (bitstream_length - 1); bit; bit >>= 1) अणु
		/* set bit to be written */
		udelay(eeprom_udelay);
		अगर (bitstream & bit)
			devpriv->plx_control_bits |= PLX_CNTRL_EEWB;
		अन्यथा
			devpriv->plx_control_bits &= ~PLX_CNTRL_EEWB;
		ग_लिखोl(devpriv->plx_control_bits, plx_control_addr);
		/* घड़ी in bit */
		udelay(eeprom_udelay);
		devpriv->plx_control_bits |= PLX_CNTRL_EESK;
		ग_लिखोl(devpriv->plx_control_bits, plx_control_addr);
		udelay(eeprom_udelay);
		devpriv->plx_control_bits &= ~PLX_CNTRL_EESK;
		ग_लिखोl(devpriv->plx_control_bits, plx_control_addr);
	पूर्ण
	/* पढ़ो back value from eeprom memory location */
	value = 0;
	क्रम (bit = 1 << (value_length - 1); bit; bit >>= 1) अणु
		/* घड़ी out bit */
		udelay(eeprom_udelay);
		devpriv->plx_control_bits |= PLX_CNTRL_EESK;
		ग_लिखोl(devpriv->plx_control_bits, plx_control_addr);
		udelay(eeprom_udelay);
		devpriv->plx_control_bits &= ~PLX_CNTRL_EESK;
		ग_लिखोl(devpriv->plx_control_bits, plx_control_addr);
		udelay(eeprom_udelay);
		अगर (पढ़ोl(plx_control_addr) & PLX_CNTRL_EERB)
			value |= bit;
	पूर्ण

	/* deactivate eeprom serial input */
	udelay(eeprom_udelay);
	devpriv->plx_control_bits &= ~PLX_CNTRL_EECS;
	ग_लिखोl(devpriv->plx_control_bits, plx_control_addr);

	वापस value;
पूर्ण

अटल पूर्णांक eeprom_पढ़ो_insn(काष्ठा comedi_device *dev,
			    काष्ठा comedi_subdevice *s,
			    काष्ठा comedi_insn *insn, अचिन्हित पूर्णांक *data)
अणु
	अचिन्हित पूर्णांक val;
	अचिन्हित पूर्णांक i;

	अगर (insn->n) अणु
		/* No poपूर्णांक पढ़ोing the same EEPROM location more than once. */
		val = पढ़ो_eeprom(dev, CR_CHAN(insn->chanspec));
		क्रम (i = 0; i < insn->n; i++)
			data[i] = val;
	पूर्ण

	वापस insn->n;
पूर्ण

/* Allocate and initialize the subdevice काष्ठाures. */
अटल पूर्णांक setup_subdevices(काष्ठा comedi_device *dev)
अणु
	स्थिर काष्ठा pcidas64_board *board = dev->board_ptr;
	काष्ठा pcidas64_निजी *devpriv = dev->निजी;
	काष्ठा comedi_subdevice *s;
	पूर्णांक i;
	पूर्णांक ret;

	ret = comedi_alloc_subdevices(dev, 10);
	अगर (ret)
		वापस ret;

	s = &dev->subdevices[0];
	/* analog input subdevice */
	dev->पढ़ो_subdev = s;
	s->type = COMEDI_SUBD_AI;
	s->subdev_flags = SDF_READABLE | SDF_GROUND | SDF_DITHER | SDF_CMD_READ;
	अगर (board->layout == LAYOUT_60XX)
		s->subdev_flags |= SDF_COMMON | SDF_DIFF;
	अन्यथा अगर (board->layout == LAYOUT_64XX)
		s->subdev_flags |= SDF_DIFF;
	/* XXX Number of inमाला_दो in dअगरferential mode is ignored */
	s->n_chan = board->ai_se_chans;
	s->len_chanlist = 0x2000;
	s->maxdata = (1 << board->ai_bits) - 1;
	s->range_table = board->ai_range_table;
	s->insn_पढ़ो = ai_rinsn;
	s->insn_config = ai_config_insn;
	s->करो_cmd = ai_cmd;
	s->करो_cmdtest = ai_cmdtest;
	s->cancel = ai_cancel;
	अगर (board->layout == LAYOUT_4020) अणु
		u8 data;
		/*
		 * set adc to पढ़ो from inमाला_दो
		 * (not पूर्णांकernal calibration sources)
		 */
		devpriv->i2c_cal_range_bits = adc_src_4020_bits(4);
		/* set channels to +-5 volt input ranges */
		क्रम (i = 0; i < s->n_chan; i++)
			devpriv->i2c_cal_range_bits |= attenuate_bit(i);
		data = devpriv->i2c_cal_range_bits;
		i2c_ग_लिखो(dev, RANGE_CAL_I2C_ADDR, &data, माप(data));
	पूर्ण

	/* analog output subdevice */
	s = &dev->subdevices[1];
	अगर (board->ao_nchan) अणु
		s->type = COMEDI_SUBD_AO;
		s->subdev_flags = SDF_READABLE | SDF_WRITABLE |
				  SDF_GROUND | SDF_CMD_WRITE;
		s->n_chan = board->ao_nchan;
		s->maxdata = (1 << board->ao_bits) - 1;
		s->range_table = board->ao_range_table;
		s->insn_ग_लिखो = ao_winsn;

		ret = comedi_alloc_subdev_पढ़ोback(s);
		अगर (ret)
			वापस ret;

		अगर (ao_cmd_is_supported(board)) अणु
			dev->ग_लिखो_subdev = s;
			s->करो_cmdtest = ao_cmdtest;
			s->करो_cmd = ao_cmd;
			s->len_chanlist = board->ao_nchan;
			s->cancel = ao_cancel;
		पूर्ण
	पूर्ण अन्यथा अणु
		s->type = COMEDI_SUBD_UNUSED;
	पूर्ण

	/* digital input */
	s = &dev->subdevices[2];
	अगर (board->layout == LAYOUT_64XX) अणु
		s->type = COMEDI_SUBD_DI;
		s->subdev_flags = SDF_READABLE;
		s->n_chan = 4;
		s->maxdata = 1;
		s->range_table = &range_digital;
		s->insn_bits = di_rbits;
	पूर्ण अन्यथा अणु
		s->type = COMEDI_SUBD_UNUSED;
	पूर्ण

	/* digital output */
	अगर (board->layout == LAYOUT_64XX) अणु
		s = &dev->subdevices[3];
		s->type = COMEDI_SUBD_DO;
		s->subdev_flags = SDF_WRITABLE;
		s->n_chan = 4;
		s->maxdata = 1;
		s->range_table = &range_digital;
		s->insn_bits = करो_wbits;
	पूर्ण अन्यथा अणु
		s->type = COMEDI_SUBD_UNUSED;
	पूर्ण

	/* 8255 */
	s = &dev->subdevices[4];
	अगर (board->has_8255) अणु
		अगर (board->layout == LAYOUT_4020) अणु
			ret = subdev_8255_init(dev, s, dio_callback_4020,
					       I8255_4020_REG);
		पूर्ण अन्यथा अणु
			ret = subdev_8255_mm_init(dev, s, शून्य,
						  DIO_8255_OFFSET);
		पूर्ण
		अगर (ret)
			वापस ret;
	पूर्ण अन्यथा अणु
		s->type = COMEDI_SUBD_UNUSED;
	पूर्ण

	/* 8 channel dio क्रम 60xx */
	s = &dev->subdevices[5];
	अगर (board->layout == LAYOUT_60XX) अणु
		s->type = COMEDI_SUBD_DIO;
		s->subdev_flags = SDF_WRITABLE | SDF_READABLE;
		s->n_chan = 8;
		s->maxdata = 1;
		s->range_table = &range_digital;
		s->insn_config = dio_60xx_config_insn;
		s->insn_bits = dio_60xx_wbits;
	पूर्ण अन्यथा अणु
		s->type = COMEDI_SUBD_UNUSED;
	पूर्ण

	/* caldac */
	s = &dev->subdevices[6];
	s->type = COMEDI_SUBD_CALIB;
	s->subdev_flags = SDF_READABLE | SDF_WRITABLE | SDF_INTERNAL;
	s->n_chan = 8;
	अगर (board->layout == LAYOUT_4020)
		s->maxdata = 0xfff;
	अन्यथा
		s->maxdata = 0xff;
	s->insn_ग_लिखो = cb_pcidas64_calib_insn_ग_लिखो;

	ret = comedi_alloc_subdev_पढ़ोback(s);
	अगर (ret)
		वापस ret;

	क्रम (i = 0; i < s->n_chan; i++) अणु
		caldac_ग_लिखो(dev, i, s->maxdata / 2);
		s->पढ़ोback[i] = s->maxdata / 2;
	पूर्ण

	/* 2 channel ad8402 potentiometer */
	s = &dev->subdevices[7];
	अगर (board->layout == LAYOUT_64XX) अणु
		s->type = COMEDI_SUBD_CALIB;
		s->subdev_flags = SDF_READABLE | SDF_WRITABLE | SDF_INTERNAL;
		s->n_chan = 2;
		s->maxdata = 0xff;
		s->insn_ग_लिखो = cb_pcidas64_ad8402_insn_ग_लिखो;

		ret = comedi_alloc_subdev_पढ़ोback(s);
		अगर (ret)
			वापस ret;

		क्रम (i = 0; i < s->n_chan; i++) अणु
			ad8402_ग_लिखो(dev, i, s->maxdata / 2);
			s->पढ़ोback[i] = s->maxdata / 2;
		पूर्ण
	पूर्ण अन्यथा अणु
		s->type = COMEDI_SUBD_UNUSED;
	पूर्ण

	/* serial EEPROM, अगर present */
	s = &dev->subdevices[8];
	अगर (पढ़ोl(devpriv->plx9080_iobase + PLX_REG_CNTRL) &
	    PLX_CNTRL_EEPRESENT) अणु
		s->type = COMEDI_SUBD_MEMORY;
		s->subdev_flags = SDF_READABLE | SDF_INTERNAL;
		s->n_chan = 128;
		s->maxdata = 0xffff;
		s->insn_पढ़ो = eeprom_पढ़ो_insn;
	पूर्ण अन्यथा अणु
		s->type = COMEDI_SUBD_UNUSED;
	पूर्ण

	/* user counter subd XXX */
	s = &dev->subdevices[9];
	s->type = COMEDI_SUBD_UNUSED;

	वापस 0;
पूर्ण

अटल पूर्णांक स्वतः_attach(काष्ठा comedi_device *dev,
		       अचिन्हित दीर्घ context)
अणु
	काष्ठा pci_dev *pcidev = comedi_to_pci_dev(dev);
	स्थिर काष्ठा pcidas64_board *board = शून्य;
	काष्ठा pcidas64_निजी *devpriv;
	u32 local_range, local_decode;
	पूर्णांक retval;

	अगर (context < ARRAY_SIZE(pcidas64_boards))
		board = &pcidas64_boards[context];
	अगर (!board)
		वापस -ENODEV;
	dev->board_ptr = board;

	devpriv = comedi_alloc_devpriv(dev, माप(*devpriv));
	अगर (!devpriv)
		वापस -ENOMEM;

	retval = comedi_pci_enable(dev);
	अगर (retval)
		वापस retval;
	pci_set_master(pcidev);

	/* Initialize dev->board_name */
	dev->board_name = board->name;

	devpriv->मुख्य_phys_iobase = pci_resource_start(pcidev, 2);
	devpriv->dio_counter_phys_iobase = pci_resource_start(pcidev, 3);

	devpriv->plx9080_iobase = pci_ioremap_bar(pcidev, 0);
	devpriv->मुख्य_iobase = pci_ioremap_bar(pcidev, 2);
	dev->mmio = pci_ioremap_bar(pcidev, 3);

	अगर (!devpriv->plx9080_iobase || !devpriv->मुख्य_iobase || !dev->mmio) अणु
		dev_warn(dev->class_dev, "failed to remap io memory\n");
		वापस -ENOMEM;
	पूर्ण

	/* figure out what local addresses are */
	local_range = पढ़ोl(devpriv->plx9080_iobase + PLX_REG_LAS0RR) &
		      PLX_LASRR_MEM_MASK;
	local_decode = पढ़ोl(devpriv->plx9080_iobase + PLX_REG_LAS0BA) &
		       local_range & PLX_LASBA_MEM_MASK;
	devpriv->local0_iobase = ((u32)devpriv->मुख्य_phys_iobase &
				  ~local_range) | local_decode;
	local_range = पढ़ोl(devpriv->plx9080_iobase + PLX_REG_LAS1RR) &
		      PLX_LASRR_MEM_MASK;
	local_decode = पढ़ोl(devpriv->plx9080_iobase + PLX_REG_LAS1BA) &
		       local_range & PLX_LASBA_MEM_MASK;
	devpriv->local1_iobase = ((u32)devpriv->dio_counter_phys_iobase &
				  ~local_range) | local_decode;

	retval = alloc_and_init_dma_members(dev);
	अगर (retval < 0)
		वापस retval;

	devpriv->hw_revision =
		hw_revision(dev, पढ़ोw(devpriv->मुख्य_iobase + HW_STATUS_REG));
	dev_dbg(dev->class_dev, "stc hardware revision %i\n",
		devpriv->hw_revision);
	init_plx9080(dev);
	init_stc_रेजिस्टरs(dev);

	retval = request_irq(pcidev->irq, handle_पूर्णांकerrupt, IRQF_SHARED,
			     "cb_pcidas64", dev);
	अगर (retval) अणु
		dev_dbg(dev->class_dev, "unable to allocate irq %u\n",
			pcidev->irq);
		वापस retval;
	पूर्ण
	dev->irq = pcidev->irq;
	dev_dbg(dev->class_dev, "irq %u\n", dev->irq);

	retval = setup_subdevices(dev);
	अगर (retval < 0)
		वापस retval;

	वापस 0;
पूर्ण

अटल व्योम detach(काष्ठा comedi_device *dev)
अणु
	काष्ठा pcidas64_निजी *devpriv = dev->निजी;

	अगर (dev->irq)
		मुक्त_irq(dev->irq, dev);
	अगर (devpriv) अणु
		अगर (devpriv->plx9080_iobase) अणु
			disable_plx_पूर्णांकerrupts(dev);
			iounmap(devpriv->plx9080_iobase);
		पूर्ण
		अगर (devpriv->मुख्य_iobase)
			iounmap(devpriv->मुख्य_iobase);
		अगर (dev->mmio)
			iounmap(dev->mmio);
	पूर्ण
	comedi_pci_disable(dev);
	cb_pcidas64_मुक्त_dma(dev);
पूर्ण

अटल काष्ठा comedi_driver cb_pcidas64_driver = अणु
	.driver_name	= "cb_pcidas64",
	.module		= THIS_MODULE,
	.स्वतः_attach	= स्वतः_attach,
	.detach		= detach,
पूर्ण;

अटल पूर्णांक cb_pcidas64_pci_probe(काष्ठा pci_dev *dev,
				 स्थिर काष्ठा pci_device_id *id)
अणु
	वापस comedi_pci_स्वतः_config(dev, &cb_pcidas64_driver,
				      id->driver_data);
पूर्ण

अटल स्थिर काष्ठा pci_device_id cb_pcidas64_pci_table[] = अणु
	अणु PCI_VDEVICE(CB, 0x001d), BOARD_PCIDAS6402_16 पूर्ण,
	अणु PCI_VDEVICE(CB, 0x001e), BOARD_PCIDAS6402_12 पूर्ण,
	अणु PCI_VDEVICE(CB, 0x0035), BOARD_PCIDAS64_M1_16 पूर्ण,
	अणु PCI_VDEVICE(CB, 0x0036), BOARD_PCIDAS64_M2_16 पूर्ण,
	अणु PCI_VDEVICE(CB, 0x0037), BOARD_PCIDAS64_M3_16 पूर्ण,
	अणु PCI_VDEVICE(CB, 0x0052), BOARD_PCIDAS4020_12 पूर्ण,
	अणु PCI_VDEVICE(CB, 0x005d), BOARD_PCIDAS6023 पूर्ण,
	अणु PCI_VDEVICE(CB, 0x005e), BOARD_PCIDAS6025 पूर्ण,
	अणु PCI_VDEVICE(CB, 0x005f), BOARD_PCIDAS6030 पूर्ण,
	अणु PCI_VDEVICE(CB, 0x0060), BOARD_PCIDAS6031 पूर्ण,
	अणु PCI_VDEVICE(CB, 0x0061), BOARD_PCIDAS6032 पूर्ण,
	अणु PCI_VDEVICE(CB, 0x0062), BOARD_PCIDAS6033 पूर्ण,
	अणु PCI_VDEVICE(CB, 0x0063), BOARD_PCIDAS6034 पूर्ण,
	अणु PCI_VDEVICE(CB, 0x0064), BOARD_PCIDAS6035 पूर्ण,
	अणु PCI_VDEVICE(CB, 0x0065), BOARD_PCIDAS6040 पूर्ण,
	अणु PCI_VDEVICE(CB, 0x0066), BOARD_PCIDAS6052 पूर्ण,
	अणु PCI_VDEVICE(CB, 0x0067), BOARD_PCIDAS6070 पूर्ण,
	अणु PCI_VDEVICE(CB, 0x0068), BOARD_PCIDAS6071 पूर्ण,
	अणु PCI_VDEVICE(CB, 0x006f), BOARD_PCIDAS6036 पूर्ण,
	अणु PCI_VDEVICE(CB, 0x0078), BOARD_PCIDAS6013 पूर्ण,
	अणु PCI_VDEVICE(CB, 0x0079), BOARD_PCIDAS6014 पूर्ण,
	अणु 0 पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(pci, cb_pcidas64_pci_table);

अटल काष्ठा pci_driver cb_pcidas64_pci_driver = अणु
	.name		= "cb_pcidas64",
	.id_table	= cb_pcidas64_pci_table,
	.probe		= cb_pcidas64_pci_probe,
	.हटाओ		= comedi_pci_स्वतः_unconfig,
पूर्ण;
module_comedi_pci_driver(cb_pcidas64_driver, cb_pcidas64_pci_driver);

MODULE_AUTHOR("Comedi https://www.comedi.org");
MODULE_DESCRIPTION("Comedi low-level driver");
MODULE_LICENSE("GPL");
