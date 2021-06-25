<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * This file is part of STM32 ADC driver
 *
 * Copyright (C) 2016, STMicroelectronics - All Rights Reserved
 * Author: Fabrice Gasnier <fabrice.gasnier@st.com>.
 */

#समावेश <linux/clk.h>
#समावेश <linux/delay.h>
#समावेश <linux/dma-mapping.h>
#समावेश <linux/dmaengine.h>
#समावेश <linux/iio/iपन.स>
#समावेश <linux/iio/buffer.h>
#समावेश <linux/iio/समयr/sपंचांग32-lptim-trigger.h>
#समावेश <linux/iio/समयr/sपंचांग32-समयr-trigger.h>
#समावेश <linux/iio/trigger.h>
#समावेश <linux/iio/trigger_consumer.h>
#समावेश <linux/iio/triggered_buffer.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/पन.स>
#समावेश <linux/iopoll.h>
#समावेश <linux/module.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/pm_runसमय.स>
#समावेश <linux/of.h>
#समावेश <linux/of_device.h>

#समावेश "stm32-adc-core.h"

/* Number of linear calibration shaकरोw रेजिस्टरs / LINCALRDYW control bits */
#घोषणा STM32H7_LINCALFACT_NUM		6

/* BOOST bit must be set on STM32H7 when ADC घड़ी is above 20MHz */
#घोषणा STM32H7_BOOST_CLKRATE		20000000UL

#घोषणा STM32_ADC_CH_MAX		20	/* max number of channels */
#घोषणा STM32_ADC_CH_SZ			10	/* max channel name size */
#घोषणा STM32_ADC_MAX_SQ		16	/* SQ1..SQ16 */
#घोषणा STM32_ADC_MAX_SMP		7	/* SMPx range is [0..7] */
#घोषणा STM32_ADC_TIMEOUT_US		100000
#घोषणा STM32_ADC_TIMEOUT	(msecs_to_jअगरfies(STM32_ADC_TIMEOUT_US / 1000))
#घोषणा STM32_ADC_HW_STOP_DELAY_MS	100

#घोषणा STM32_DMA_BUFFER_SIZE		PAGE_SIZE

/* External trigger enable */
क्रमागत sपंचांग32_adc_exten अणु
	STM32_EXTEN_SWTRIG,
	STM32_EXTEN_HWTRIG_RISING_EDGE,
	STM32_EXTEN_HWTRIG_FALLING_EDGE,
	STM32_EXTEN_HWTRIG_BOTH_EDGES,
पूर्ण;

/* extsel - trigger mux selection value */
क्रमागत sपंचांग32_adc_extsel अणु
	STM32_EXT0,
	STM32_EXT1,
	STM32_EXT2,
	STM32_EXT3,
	STM32_EXT4,
	STM32_EXT5,
	STM32_EXT6,
	STM32_EXT7,
	STM32_EXT8,
	STM32_EXT9,
	STM32_EXT10,
	STM32_EXT11,
	STM32_EXT12,
	STM32_EXT13,
	STM32_EXT14,
	STM32_EXT15,
	STM32_EXT16,
	STM32_EXT17,
	STM32_EXT18,
	STM32_EXT19,
	STM32_EXT20,
पूर्ण;

/**
 * काष्ठा sपंचांग32_adc_trig_info - ADC trigger info
 * @name:		name of the trigger, corresponding to its source
 * @extsel:		trigger selection
 */
काष्ठा sपंचांग32_adc_trig_info अणु
	स्थिर अक्षर *name;
	क्रमागत sपंचांग32_adc_extsel extsel;
पूर्ण;

/**
 * काष्ठा sपंचांग32_adc_calib - optional adc calibration data
 * @calfact_s: Calibration offset क्रम single ended channels
 * @calfact_d: Calibration offset in dअगरferential
 * @lincalfact: Linearity calibration factor
 * @calibrated: Indicates calibration status
 */
काष्ठा sपंचांग32_adc_calib अणु
	u32			calfact_s;
	u32			calfact_d;
	u32			lincalfact[STM32H7_LINCALFACT_NUM];
	bool			calibrated;
पूर्ण;

/**
 * काष्ठा sपंचांग32_adc_regs - sपंचांग32 ADC misc रेजिस्टरs & bitfield desc
 * @reg:		रेजिस्टर offset
 * @mask:		bitfield mask
 * @shअगरt:		left shअगरt
 */
काष्ठा sपंचांग32_adc_regs अणु
	पूर्णांक reg;
	पूर्णांक mask;
	पूर्णांक shअगरt;
पूर्ण;

/**
 * काष्ठा sपंचांग32_adc_regspec - sपंचांग32 रेजिस्टरs definition
 * @dr:			data रेजिस्टर offset
 * @ier_eoc:		पूर्णांकerrupt enable रेजिस्टर & eocie bitfield
 * @ier_ovr:		पूर्णांकerrupt enable रेजिस्टर & overrun bitfield
 * @isr_eoc:		पूर्णांकerrupt status रेजिस्टर & eoc bitfield
 * @isr_ovr:		पूर्णांकerrupt status रेजिस्टर & overrun bitfield
 * @sqr:		reference to sequence रेजिस्टरs array
 * @exten:		trigger control रेजिस्टर & bitfield
 * @extsel:		trigger selection रेजिस्टर & bitfield
 * @res:		resolution selection रेजिस्टर & bitfield
 * @smpr:		smpr1 & smpr2 रेजिस्टरs offset array
 * @smp_bits:		smpr1 & smpr2 index and bitfields
 */
काष्ठा sपंचांग32_adc_regspec अणु
	स्थिर u32 dr;
	स्थिर काष्ठा sपंचांग32_adc_regs ier_eoc;
	स्थिर काष्ठा sपंचांग32_adc_regs ier_ovr;
	स्थिर काष्ठा sपंचांग32_adc_regs isr_eoc;
	स्थिर काष्ठा sपंचांग32_adc_regs isr_ovr;
	स्थिर काष्ठा sपंचांग32_adc_regs *sqr;
	स्थिर काष्ठा sपंचांग32_adc_regs exten;
	स्थिर काष्ठा sपंचांग32_adc_regs extsel;
	स्थिर काष्ठा sपंचांग32_adc_regs res;
	स्थिर u32 smpr[2];
	स्थिर काष्ठा sपंचांग32_adc_regs *smp_bits;
पूर्ण;

काष्ठा sपंचांग32_adc;

/**
 * काष्ठा sपंचांग32_adc_cfg - sपंचांग32 compatible configuration data
 * @regs:		रेजिस्टरs descriptions
 * @adc_info:		per instance input channels definitions
 * @trigs:		बाह्यal trigger sources
 * @clk_required:	घड़ी is required
 * @has_vregपढ़ोy:	vregपढ़ोy status flag presence
 * @prepare:		optional prepare routine (घातer-up, enable)
 * @start_conv:		routine to start conversions
 * @stop_conv:		routine to stop conversions
 * @unprepare:		optional unprepare routine (disable, घातer-करोwn)
 * @irq_clear:		routine to clear irqs
 * @smp_cycles:		programmable sampling समय (ADC घड़ी cycles)
 */
काष्ठा sपंचांग32_adc_cfg अणु
	स्थिर काष्ठा sपंचांग32_adc_regspec	*regs;
	स्थिर काष्ठा sपंचांग32_adc_info	*adc_info;
	काष्ठा sपंचांग32_adc_trig_info	*trigs;
	bool clk_required;
	bool has_vregपढ़ोy;
	पूर्णांक (*prepare)(काष्ठा iio_dev *);
	व्योम (*start_conv)(काष्ठा iio_dev *, bool dma);
	व्योम (*stop_conv)(काष्ठा iio_dev *);
	व्योम (*unprepare)(काष्ठा iio_dev *);
	व्योम (*irq_clear)(काष्ठा iio_dev *indio_dev, u32 msk);
	स्थिर अचिन्हित पूर्णांक *smp_cycles;
पूर्ण;

/**
 * काष्ठा sपंचांग32_adc - निजी data of each ADC IIO instance
 * @common:		reference to ADC block common data
 * @offset:		ADC instance रेजिस्टर offset in ADC block
 * @cfg:		compatible configuration data
 * @completion:		end of single conversion completion
 * @buffer:		data buffer + 8 bytes क्रम बारtamp अगर enabled
 * @clk:		घड़ी क्रम this adc instance
 * @irq:		पूर्णांकerrupt क्रम this adc instance
 * @lock:		spinlock
 * @bufi:		data buffer index
 * @num_conv:		expected number of scan conversions
 * @res:		data resolution (e.g. RES bitfield value)
 * @trigger_polarity:	बाह्यal trigger polarity (e.g. exten)
 * @dma_chan:		dma channel
 * @rx_buf:		dma rx buffer cpu address
 * @rx_dma_buf:		dma rx buffer bus address
 * @rx_buf_sz:		dma rx buffer size
 * @dअगरsel:		biपंचांगask to set single-ended/dअगरferential channel
 * @pcsel:		biपंचांगask to preselect channels on some devices
 * @smpr_val:		sampling समय settings (e.g. smpr1 / smpr2)
 * @cal:		optional calibration data on some devices
 * @chan_name:		channel name array
 */
काष्ठा sपंचांग32_adc अणु
	काष्ठा sपंचांग32_adc_common	*common;
	u32			offset;
	स्थिर काष्ठा sपंचांग32_adc_cfg	*cfg;
	काष्ठा completion	completion;
	u16			buffer[STM32_ADC_MAX_SQ + 4] __aligned(8);
	काष्ठा clk		*clk;
	पूर्णांक			irq;
	spinlock_t		lock;		/* पूर्णांकerrupt lock */
	अचिन्हित पूर्णांक		bufi;
	अचिन्हित पूर्णांक		num_conv;
	u32			res;
	u32			trigger_polarity;
	काष्ठा dma_chan		*dma_chan;
	u8			*rx_buf;
	dma_addr_t		rx_dma_buf;
	अचिन्हित पूर्णांक		rx_buf_sz;
	u32			dअगरsel;
	u32			pcsel;
	u32			smpr_val[2];
	काष्ठा sपंचांग32_adc_calib	cal;
	अक्षर			chan_name[STM32_ADC_CH_MAX][STM32_ADC_CH_SZ];
पूर्ण;

काष्ठा sपंचांग32_adc_dअगरf_channel अणु
	u32 vinp;
	u32 vinn;
पूर्ण;

/**
 * काष्ठा sपंचांग32_adc_info - sपंचांग32 ADC, per instance config data
 * @max_channels:	Number of channels
 * @resolutions:	available resolutions
 * @num_res:		number of available resolutions
 */
काष्ठा sपंचांग32_adc_info अणु
	पूर्णांक max_channels;
	स्थिर अचिन्हित पूर्णांक *resolutions;
	स्थिर अचिन्हित पूर्णांक num_res;
पूर्ण;

अटल स्थिर अचिन्हित पूर्णांक sपंचांग32f4_adc_resolutions[] = अणु
	/* sorted values so the index matches RES[1:0] in STM32F4_ADC_CR1 */
	12, 10, 8, 6,
पूर्ण;

/* sपंचांग32f4 can have up to 16 channels */
अटल स्थिर काष्ठा sपंचांग32_adc_info sपंचांग32f4_adc_info = अणु
	.max_channels = 16,
	.resolutions = sपंचांग32f4_adc_resolutions,
	.num_res = ARRAY_SIZE(sपंचांग32f4_adc_resolutions),
पूर्ण;

अटल स्थिर अचिन्हित पूर्णांक sपंचांग32h7_adc_resolutions[] = अणु
	/* sorted values so the index matches RES[2:0] in STM32H7_ADC_CFGR */
	16, 14, 12, 10, 8,
पूर्ण;

/* sपंचांग32h7 can have up to 20 channels */
अटल स्थिर काष्ठा sपंचांग32_adc_info sपंचांग32h7_adc_info = अणु
	.max_channels = STM32_ADC_CH_MAX,
	.resolutions = sपंचांग32h7_adc_resolutions,
	.num_res = ARRAY_SIZE(sपंचांग32h7_adc_resolutions),
पूर्ण;

/*
 * sपंचांग32f4_sq - describe regular sequence रेजिस्टरs
 * - L: sequence len (रेजिस्टर & bit field)
 * - SQ1..SQ16: sequence entries (रेजिस्टर & bit field)
 */
अटल स्थिर काष्ठा sपंचांग32_adc_regs sपंचांग32f4_sq[STM32_ADC_MAX_SQ + 1] = अणु
	/* L: len bit field description to be kept as first element */
	अणु STM32F4_ADC_SQR1, GENMASK(23, 20), 20 पूर्ण,
	/* SQ1..SQ16 रेजिस्टरs & bit fields (reg, mask, shअगरt) */
	अणु STM32F4_ADC_SQR3, GENMASK(4, 0), 0 पूर्ण,
	अणु STM32F4_ADC_SQR3, GENMASK(9, 5), 5 पूर्ण,
	अणु STM32F4_ADC_SQR3, GENMASK(14, 10), 10 पूर्ण,
	अणु STM32F4_ADC_SQR3, GENMASK(19, 15), 15 पूर्ण,
	अणु STM32F4_ADC_SQR3, GENMASK(24, 20), 20 पूर्ण,
	अणु STM32F4_ADC_SQR3, GENMASK(29, 25), 25 पूर्ण,
	अणु STM32F4_ADC_SQR2, GENMASK(4, 0), 0 पूर्ण,
	अणु STM32F4_ADC_SQR2, GENMASK(9, 5), 5 पूर्ण,
	अणु STM32F4_ADC_SQR2, GENMASK(14, 10), 10 पूर्ण,
	अणु STM32F4_ADC_SQR2, GENMASK(19, 15), 15 पूर्ण,
	अणु STM32F4_ADC_SQR2, GENMASK(24, 20), 20 पूर्ण,
	अणु STM32F4_ADC_SQR2, GENMASK(29, 25), 25 पूर्ण,
	अणु STM32F4_ADC_SQR1, GENMASK(4, 0), 0 पूर्ण,
	अणु STM32F4_ADC_SQR1, GENMASK(9, 5), 5 पूर्ण,
	अणु STM32F4_ADC_SQR1, GENMASK(14, 10), 10 पूर्ण,
	अणु STM32F4_ADC_SQR1, GENMASK(19, 15), 15 पूर्ण,
पूर्ण;

/* STM32F4 बाह्यal trigger sources क्रम all instances */
अटल काष्ठा sपंचांग32_adc_trig_info sपंचांग32f4_adc_trigs[] = अणु
	अणु TIM1_CH1, STM32_EXT0 पूर्ण,
	अणु TIM1_CH2, STM32_EXT1 पूर्ण,
	अणु TIM1_CH3, STM32_EXT2 पूर्ण,
	अणु TIM2_CH2, STM32_EXT3 पूर्ण,
	अणु TIM2_CH3, STM32_EXT4 पूर्ण,
	अणु TIM2_CH4, STM32_EXT5 पूर्ण,
	अणु TIM2_TRGO, STM32_EXT6 पूर्ण,
	अणु TIM3_CH1, STM32_EXT7 पूर्ण,
	अणु TIM3_TRGO, STM32_EXT8 पूर्ण,
	अणु TIM4_CH4, STM32_EXT9 पूर्ण,
	अणु TIM5_CH1, STM32_EXT10 पूर्ण,
	अणु TIM5_CH2, STM32_EXT11 पूर्ण,
	अणु TIM5_CH3, STM32_EXT12 पूर्ण,
	अणु TIM8_CH1, STM32_EXT13 पूर्ण,
	अणु TIM8_TRGO, STM32_EXT14 पूर्ण,
	अणुपूर्ण, /* sentinel */
पूर्ण;

/*
 * sपंचांग32f4_smp_bits[] - describe sampling समय रेजिस्टर index & bit fields
 * Sorted so it can be indexed by channel number.
 */
अटल स्थिर काष्ठा sपंचांग32_adc_regs sपंचांग32f4_smp_bits[] = अणु
	/* STM32F4_ADC_SMPR2: smpr[] index, mask, shअगरt क्रम SMP0 to SMP9 */
	अणु 1, GENMASK(2, 0), 0 पूर्ण,
	अणु 1, GENMASK(5, 3), 3 पूर्ण,
	अणु 1, GENMASK(8, 6), 6 पूर्ण,
	अणु 1, GENMASK(11, 9), 9 पूर्ण,
	अणु 1, GENMASK(14, 12), 12 पूर्ण,
	अणु 1, GENMASK(17, 15), 15 पूर्ण,
	अणु 1, GENMASK(20, 18), 18 पूर्ण,
	अणु 1, GENMASK(23, 21), 21 पूर्ण,
	अणु 1, GENMASK(26, 24), 24 पूर्ण,
	अणु 1, GENMASK(29, 27), 27 पूर्ण,
	/* STM32F4_ADC_SMPR1, smpr[] index, mask, shअगरt क्रम SMP10 to SMP18 */
	अणु 0, GENMASK(2, 0), 0 पूर्ण,
	अणु 0, GENMASK(5, 3), 3 पूर्ण,
	अणु 0, GENMASK(8, 6), 6 पूर्ण,
	अणु 0, GENMASK(11, 9), 9 पूर्ण,
	अणु 0, GENMASK(14, 12), 12 पूर्ण,
	अणु 0, GENMASK(17, 15), 15 पूर्ण,
	अणु 0, GENMASK(20, 18), 18 पूर्ण,
	अणु 0, GENMASK(23, 21), 21 पूर्ण,
	अणु 0, GENMASK(26, 24), 24 पूर्ण,
पूर्ण;

/* STM32F4 programmable sampling समय (ADC घड़ी cycles) */
अटल स्थिर अचिन्हित पूर्णांक sपंचांग32f4_adc_smp_cycles[STM32_ADC_MAX_SMP + 1] = अणु
	3, 15, 28, 56, 84, 112, 144, 480,
पूर्ण;

अटल स्थिर काष्ठा sपंचांग32_adc_regspec sपंचांग32f4_adc_regspec = अणु
	.dr = STM32F4_ADC_DR,
	.ier_eoc = अणु STM32F4_ADC_CR1, STM32F4_EOCIE पूर्ण,
	.ier_ovr = अणु STM32F4_ADC_CR1, STM32F4_OVRIE पूर्ण,
	.isr_eoc = अणु STM32F4_ADC_SR, STM32F4_EOC पूर्ण,
	.isr_ovr = अणु STM32F4_ADC_SR, STM32F4_OVR पूर्ण,
	.sqr = sपंचांग32f4_sq,
	.exten = अणु STM32F4_ADC_CR2, STM32F4_EXTEN_MASK, STM32F4_EXTEN_SHIFT पूर्ण,
	.extsel = अणु STM32F4_ADC_CR2, STM32F4_EXTSEL_MASK,
		    STM32F4_EXTSEL_SHIFT पूर्ण,
	.res = अणु STM32F4_ADC_CR1, STM32F4_RES_MASK, STM32F4_RES_SHIFT पूर्ण,
	.smpr = अणु STM32F4_ADC_SMPR1, STM32F4_ADC_SMPR2 पूर्ण,
	.smp_bits = sपंचांग32f4_smp_bits,
पूर्ण;

अटल स्थिर काष्ठा sपंचांग32_adc_regs sपंचांग32h7_sq[STM32_ADC_MAX_SQ + 1] = अणु
	/* L: len bit field description to be kept as first element */
	अणु STM32H7_ADC_SQR1, GENMASK(3, 0), 0 पूर्ण,
	/* SQ1..SQ16 रेजिस्टरs & bit fields (reg, mask, shअगरt) */
	अणु STM32H7_ADC_SQR1, GENMASK(10, 6), 6 पूर्ण,
	अणु STM32H7_ADC_SQR1, GENMASK(16, 12), 12 पूर्ण,
	अणु STM32H7_ADC_SQR1, GENMASK(22, 18), 18 पूर्ण,
	अणु STM32H7_ADC_SQR1, GENMASK(28, 24), 24 पूर्ण,
	अणु STM32H7_ADC_SQR2, GENMASK(4, 0), 0 पूर्ण,
	अणु STM32H7_ADC_SQR2, GENMASK(10, 6), 6 पूर्ण,
	अणु STM32H7_ADC_SQR2, GENMASK(16, 12), 12 पूर्ण,
	अणु STM32H7_ADC_SQR2, GENMASK(22, 18), 18 पूर्ण,
	अणु STM32H7_ADC_SQR2, GENMASK(28, 24), 24 पूर्ण,
	अणु STM32H7_ADC_SQR3, GENMASK(4, 0), 0 पूर्ण,
	अणु STM32H7_ADC_SQR3, GENMASK(10, 6), 6 पूर्ण,
	अणु STM32H7_ADC_SQR3, GENMASK(16, 12), 12 पूर्ण,
	अणु STM32H7_ADC_SQR3, GENMASK(22, 18), 18 पूर्ण,
	अणु STM32H7_ADC_SQR3, GENMASK(28, 24), 24 पूर्ण,
	अणु STM32H7_ADC_SQR4, GENMASK(4, 0), 0 पूर्ण,
	अणु STM32H7_ADC_SQR4, GENMASK(10, 6), 6 पूर्ण,
पूर्ण;

/* STM32H7 बाह्यal trigger sources क्रम all instances */
अटल काष्ठा sपंचांग32_adc_trig_info sपंचांग32h7_adc_trigs[] = अणु
	अणु TIM1_CH1, STM32_EXT0 पूर्ण,
	अणु TIM1_CH2, STM32_EXT1 पूर्ण,
	अणु TIM1_CH3, STM32_EXT2 पूर्ण,
	अणु TIM2_CH2, STM32_EXT3 पूर्ण,
	अणु TIM3_TRGO, STM32_EXT4 पूर्ण,
	अणु TIM4_CH4, STM32_EXT5 पूर्ण,
	अणु TIM8_TRGO, STM32_EXT7 पूर्ण,
	अणु TIM8_TRGO2, STM32_EXT8 पूर्ण,
	अणु TIM1_TRGO, STM32_EXT9 पूर्ण,
	अणु TIM1_TRGO2, STM32_EXT10 पूर्ण,
	अणु TIM2_TRGO, STM32_EXT11 पूर्ण,
	अणु TIM4_TRGO, STM32_EXT12 पूर्ण,
	अणु TIM6_TRGO, STM32_EXT13 पूर्ण,
	अणु TIM15_TRGO, STM32_EXT14 पूर्ण,
	अणु TIM3_CH4, STM32_EXT15 पूर्ण,
	अणु LPTIM1_OUT, STM32_EXT18 पूर्ण,
	अणु LPTIM2_OUT, STM32_EXT19 पूर्ण,
	अणु LPTIM3_OUT, STM32_EXT20 पूर्ण,
	अणुपूर्ण,
पूर्ण;

/*
 * sपंचांग32h7_smp_bits - describe sampling समय रेजिस्टर index & bit fields
 * Sorted so it can be indexed by channel number.
 */
अटल स्थिर काष्ठा sपंचांग32_adc_regs sपंचांग32h7_smp_bits[] = अणु
	/* STM32H7_ADC_SMPR1, smpr[] index, mask, shअगरt क्रम SMP0 to SMP9 */
	अणु 0, GENMASK(2, 0), 0 पूर्ण,
	अणु 0, GENMASK(5, 3), 3 पूर्ण,
	अणु 0, GENMASK(8, 6), 6 पूर्ण,
	अणु 0, GENMASK(11, 9), 9 पूर्ण,
	अणु 0, GENMASK(14, 12), 12 पूर्ण,
	अणु 0, GENMASK(17, 15), 15 पूर्ण,
	अणु 0, GENMASK(20, 18), 18 पूर्ण,
	अणु 0, GENMASK(23, 21), 21 पूर्ण,
	अणु 0, GENMASK(26, 24), 24 पूर्ण,
	अणु 0, GENMASK(29, 27), 27 पूर्ण,
	/* STM32H7_ADC_SMPR2, smpr[] index, mask, shअगरt क्रम SMP10 to SMP19 */
	अणु 1, GENMASK(2, 0), 0 पूर्ण,
	अणु 1, GENMASK(5, 3), 3 पूर्ण,
	अणु 1, GENMASK(8, 6), 6 पूर्ण,
	अणु 1, GENMASK(11, 9), 9 पूर्ण,
	अणु 1, GENMASK(14, 12), 12 पूर्ण,
	अणु 1, GENMASK(17, 15), 15 पूर्ण,
	अणु 1, GENMASK(20, 18), 18 पूर्ण,
	अणु 1, GENMASK(23, 21), 21 पूर्ण,
	अणु 1, GENMASK(26, 24), 24 पूर्ण,
	अणु 1, GENMASK(29, 27), 27 पूर्ण,
पूर्ण;

/* STM32H7 programmable sampling समय (ADC घड़ी cycles, rounded करोwn) */
अटल स्थिर अचिन्हित पूर्णांक sपंचांग32h7_adc_smp_cycles[STM32_ADC_MAX_SMP + 1] = अणु
	1, 2, 8, 16, 32, 64, 387, 810,
पूर्ण;

अटल स्थिर काष्ठा sपंचांग32_adc_regspec sपंचांग32h7_adc_regspec = अणु
	.dr = STM32H7_ADC_DR,
	.ier_eoc = अणु STM32H7_ADC_IER, STM32H7_EOCIE पूर्ण,
	.ier_ovr = अणु STM32H7_ADC_IER, STM32H7_OVRIE पूर्ण,
	.isr_eoc = अणु STM32H7_ADC_ISR, STM32H7_EOC पूर्ण,
	.isr_ovr = अणु STM32H7_ADC_ISR, STM32H7_OVR पूर्ण,
	.sqr = sपंचांग32h7_sq,
	.exten = अणु STM32H7_ADC_CFGR, STM32H7_EXTEN_MASK, STM32H7_EXTEN_SHIFT पूर्ण,
	.extsel = अणु STM32H7_ADC_CFGR, STM32H7_EXTSEL_MASK,
		    STM32H7_EXTSEL_SHIFT पूर्ण,
	.res = अणु STM32H7_ADC_CFGR, STM32H7_RES_MASK, STM32H7_RES_SHIFT पूर्ण,
	.smpr = अणु STM32H7_ADC_SMPR1, STM32H7_ADC_SMPR2 पूर्ण,
	.smp_bits = sपंचांग32h7_smp_bits,
पूर्ण;

/**
 * STM32 ADC रेजिस्टरs access routines
 * @adc: sपंचांग32 adc instance
 * @reg: reg offset in adc instance
 *
 * Note: All instances share same base, with 0x0, 0x100 or 0x200 offset resp.
 * क्रम adc1, adc2 and adc3.
 */
अटल u32 sपंचांग32_adc_पढ़ोl(काष्ठा sपंचांग32_adc *adc, u32 reg)
अणु
	वापस पढ़ोl_relaxed(adc->common->base + adc->offset + reg);
पूर्ण

#घोषणा sपंचांग32_adc_पढ़ोl_addr(addr)	sपंचांग32_adc_पढ़ोl(adc, addr)

#घोषणा sपंचांग32_adc_पढ़ोl_poll_समयout(reg, val, cond, sleep_us, समयout_us) \
	पढ़ोx_poll_समयout(sपंचांग32_adc_पढ़ोl_addr, reg, val, \
			   cond, sleep_us, समयout_us)

अटल u16 sपंचांग32_adc_पढ़ोw(काष्ठा sपंचांग32_adc *adc, u32 reg)
अणु
	वापस पढ़ोw_relaxed(adc->common->base + adc->offset + reg);
पूर्ण

अटल व्योम sपंचांग32_adc_ग_लिखोl(काष्ठा sपंचांग32_adc *adc, u32 reg, u32 val)
अणु
	ग_लिखोl_relaxed(val, adc->common->base + adc->offset + reg);
पूर्ण

अटल व्योम sपंचांग32_adc_set_bits(काष्ठा sपंचांग32_adc *adc, u32 reg, u32 bits)
अणु
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&adc->lock, flags);
	sपंचांग32_adc_ग_लिखोl(adc, reg, sपंचांग32_adc_पढ़ोl(adc, reg) | bits);
	spin_unlock_irqrestore(&adc->lock, flags);
पूर्ण

अटल व्योम sपंचांग32_adc_clr_bits(काष्ठा sपंचांग32_adc *adc, u32 reg, u32 bits)
अणु
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&adc->lock, flags);
	sपंचांग32_adc_ग_लिखोl(adc, reg, sपंचांग32_adc_पढ़ोl(adc, reg) & ~bits);
	spin_unlock_irqrestore(&adc->lock, flags);
पूर्ण

/**
 * sपंचांग32_adc_conv_irq_enable() - Enable end of conversion पूर्णांकerrupt
 * @adc: sपंचांग32 adc instance
 */
अटल व्योम sपंचांग32_adc_conv_irq_enable(काष्ठा sपंचांग32_adc *adc)
अणु
	sपंचांग32_adc_set_bits(adc, adc->cfg->regs->ier_eoc.reg,
			   adc->cfg->regs->ier_eoc.mask);
पूर्ण;

/**
 * sपंचांग32_adc_conv_irq_disable() - Disable end of conversion पूर्णांकerrupt
 * @adc: sपंचांग32 adc instance
 */
अटल व्योम sपंचांग32_adc_conv_irq_disable(काष्ठा sपंचांग32_adc *adc)
अणु
	sपंचांग32_adc_clr_bits(adc, adc->cfg->regs->ier_eoc.reg,
			   adc->cfg->regs->ier_eoc.mask);
पूर्ण

अटल व्योम sपंचांग32_adc_ovr_irq_enable(काष्ठा sपंचांग32_adc *adc)
अणु
	sपंचांग32_adc_set_bits(adc, adc->cfg->regs->ier_ovr.reg,
			   adc->cfg->regs->ier_ovr.mask);
पूर्ण

अटल व्योम sपंचांग32_adc_ovr_irq_disable(काष्ठा sपंचांग32_adc *adc)
अणु
	sपंचांग32_adc_clr_bits(adc, adc->cfg->regs->ier_ovr.reg,
			   adc->cfg->regs->ier_ovr.mask);
पूर्ण

अटल व्योम sपंचांग32_adc_set_res(काष्ठा sपंचांग32_adc *adc)
अणु
	स्थिर काष्ठा sपंचांग32_adc_regs *res = &adc->cfg->regs->res;
	u32 val;

	val = sपंचांग32_adc_पढ़ोl(adc, res->reg);
	val = (val & ~res->mask) | (adc->res << res->shअगरt);
	sपंचांग32_adc_ग_लिखोl(adc, res->reg, val);
पूर्ण

अटल पूर्णांक sपंचांग32_adc_hw_stop(काष्ठा device *dev)
अणु
	काष्ठा iio_dev *indio_dev = dev_get_drvdata(dev);
	काष्ठा sपंचांग32_adc *adc = iio_priv(indio_dev);

	अगर (adc->cfg->unprepare)
		adc->cfg->unprepare(indio_dev);

	clk_disable_unprepare(adc->clk);

	वापस 0;
पूर्ण

अटल पूर्णांक sपंचांग32_adc_hw_start(काष्ठा device *dev)
अणु
	काष्ठा iio_dev *indio_dev = dev_get_drvdata(dev);
	काष्ठा sपंचांग32_adc *adc = iio_priv(indio_dev);
	पूर्णांक ret;

	ret = clk_prepare_enable(adc->clk);
	अगर (ret)
		वापस ret;

	sपंचांग32_adc_set_res(adc);

	अगर (adc->cfg->prepare) अणु
		ret = adc->cfg->prepare(indio_dev);
		अगर (ret)
			जाओ err_clk_dis;
	पूर्ण

	वापस 0;

err_clk_dis:
	clk_disable_unprepare(adc->clk);

	वापस ret;
पूर्ण

/**
 * sपंचांग32f4_adc_start_conv() - Start conversions क्रम regular channels.
 * @indio_dev: IIO device instance
 * @dma: use dma to transfer conversion result
 *
 * Start conversions क्रम regular channels.
 * Also take care of normal or DMA mode. Circular DMA may be used क्रम regular
 * conversions, in IIO buffer modes. Otherwise, use ADC पूर्णांकerrupt with direct
 * DR पढ़ो instead (e.g. पढ़ो_raw, or triggered buffer mode without DMA).
 */
अटल व्योम sपंचांग32f4_adc_start_conv(काष्ठा iio_dev *indio_dev, bool dma)
अणु
	काष्ठा sपंचांग32_adc *adc = iio_priv(indio_dev);

	sपंचांग32_adc_set_bits(adc, STM32F4_ADC_CR1, STM32F4_SCAN);

	अगर (dma)
		sपंचांग32_adc_set_bits(adc, STM32F4_ADC_CR2,
				   STM32F4_DMA | STM32F4_DDS);

	sपंचांग32_adc_set_bits(adc, STM32F4_ADC_CR2, STM32F4_EOCS | STM32F4_ADON);

	/* Wait क्रम Power-up समय (tSTAB from datasheet) */
	usleep_range(2, 3);

	/* Software start ? (e.g. trigger detection disabled ?) */
	अगर (!(sपंचांग32_adc_पढ़ोl(adc, STM32F4_ADC_CR2) & STM32F4_EXTEN_MASK))
		sपंचांग32_adc_set_bits(adc, STM32F4_ADC_CR2, STM32F4_SWSTART);
पूर्ण

अटल व्योम sपंचांग32f4_adc_stop_conv(काष्ठा iio_dev *indio_dev)
अणु
	काष्ठा sपंचांग32_adc *adc = iio_priv(indio_dev);

	sपंचांग32_adc_clr_bits(adc, STM32F4_ADC_CR2, STM32F4_EXTEN_MASK);
	sपंचांग32_adc_clr_bits(adc, STM32F4_ADC_SR, STM32F4_STRT);

	sपंचांग32_adc_clr_bits(adc, STM32F4_ADC_CR1, STM32F4_SCAN);
	sपंचांग32_adc_clr_bits(adc, STM32F4_ADC_CR2,
			   STM32F4_ADON | STM32F4_DMA | STM32F4_DDS);
पूर्ण

अटल व्योम sपंचांग32f4_adc_irq_clear(काष्ठा iio_dev *indio_dev, u32 msk)
अणु
	काष्ठा sपंचांग32_adc *adc = iio_priv(indio_dev);

	sपंचांग32_adc_clr_bits(adc, adc->cfg->regs->isr_eoc.reg, msk);
पूर्ण

अटल व्योम sपंचांग32h7_adc_start_conv(काष्ठा iio_dev *indio_dev, bool dma)
अणु
	काष्ठा sपंचांग32_adc *adc = iio_priv(indio_dev);
	क्रमागत sपंचांग32h7_adc_dmngt dmngt;
	अचिन्हित दीर्घ flags;
	u32 val;

	अगर (dma)
		dmngt = STM32H7_DMNGT_DMA_CIRC;
	अन्यथा
		dmngt = STM32H7_DMNGT_DR_ONLY;

	spin_lock_irqsave(&adc->lock, flags);
	val = sपंचांग32_adc_पढ़ोl(adc, STM32H7_ADC_CFGR);
	val = (val & ~STM32H7_DMNGT_MASK) | (dmngt << STM32H7_DMNGT_SHIFT);
	sपंचांग32_adc_ग_लिखोl(adc, STM32H7_ADC_CFGR, val);
	spin_unlock_irqrestore(&adc->lock, flags);

	sपंचांग32_adc_set_bits(adc, STM32H7_ADC_CR, STM32H7_ADSTART);
पूर्ण

अटल व्योम sपंचांग32h7_adc_stop_conv(काष्ठा iio_dev *indio_dev)
अणु
	काष्ठा sपंचांग32_adc *adc = iio_priv(indio_dev);
	पूर्णांक ret;
	u32 val;

	sपंचांग32_adc_set_bits(adc, STM32H7_ADC_CR, STM32H7_ADSTP);

	ret = sपंचांग32_adc_पढ़ोl_poll_समयout(STM32H7_ADC_CR, val,
					   !(val & (STM32H7_ADSTART)),
					   100, STM32_ADC_TIMEOUT_US);
	अगर (ret)
		dev_warn(&indio_dev->dev, "stop failed\n");

	sपंचांग32_adc_clr_bits(adc, STM32H7_ADC_CFGR, STM32H7_DMNGT_MASK);
पूर्ण

अटल व्योम sपंचांग32h7_adc_irq_clear(काष्ठा iio_dev *indio_dev, u32 msk)
अणु
	काष्ठा sपंचांग32_adc *adc = iio_priv(indio_dev);
	/* On STM32H7 IRQs are cleared by writing 1 पूर्णांकo ISR रेजिस्टर */
	sपंचांग32_adc_set_bits(adc, adc->cfg->regs->isr_eoc.reg, msk);
पूर्ण

अटल पूर्णांक sपंचांग32h7_adc_निकास_pwr_करोwn(काष्ठा iio_dev *indio_dev)
अणु
	काष्ठा sपंचांग32_adc *adc = iio_priv(indio_dev);
	पूर्णांक ret;
	u32 val;

	/* Exit deep घातer करोwn, then enable ADC voltage regulator */
	sपंचांग32_adc_clr_bits(adc, STM32H7_ADC_CR, STM32H7_DEEPPWD);
	sपंचांग32_adc_set_bits(adc, STM32H7_ADC_CR, STM32H7_ADVREGEN);

	अगर (adc->common->rate > STM32H7_BOOST_CLKRATE)
		sपंचांग32_adc_set_bits(adc, STM32H7_ADC_CR, STM32H7_BOOST);

	/* Wait क्रम startup समय */
	अगर (!adc->cfg->has_vregपढ़ोy) अणु
		usleep_range(10, 20);
		वापस 0;
	पूर्ण

	ret = sपंचांग32_adc_पढ़ोl_poll_समयout(STM32H7_ADC_ISR, val,
					   val & STM32MP1_VREGREADY, 100,
					   STM32_ADC_TIMEOUT_US);
	अगर (ret) अणु
		sपंचांग32_adc_set_bits(adc, STM32H7_ADC_CR, STM32H7_DEEPPWD);
		dev_err(&indio_dev->dev, "Failed to exit power down\n");
	पूर्ण

	वापस ret;
पूर्ण

अटल व्योम sपंचांग32h7_adc_enter_pwr_करोwn(काष्ठा sपंचांग32_adc *adc)
अणु
	sपंचांग32_adc_clr_bits(adc, STM32H7_ADC_CR, STM32H7_BOOST);

	/* Setting DEEPPWD disables ADC vreg and clears ADVREGEN */
	sपंचांग32_adc_set_bits(adc, STM32H7_ADC_CR, STM32H7_DEEPPWD);
पूर्ण

अटल पूर्णांक sपंचांग32h7_adc_enable(काष्ठा iio_dev *indio_dev)
अणु
	काष्ठा sपंचांग32_adc *adc = iio_priv(indio_dev);
	पूर्णांक ret;
	u32 val;

	sपंचांग32_adc_set_bits(adc, STM32H7_ADC_CR, STM32H7_ADEN);

	/* Poll क्रम ADRDY to be set (after adc startup समय) */
	ret = sपंचांग32_adc_पढ़ोl_poll_समयout(STM32H7_ADC_ISR, val,
					   val & STM32H7_ADRDY,
					   100, STM32_ADC_TIMEOUT_US);
	अगर (ret) अणु
		sपंचांग32_adc_set_bits(adc, STM32H7_ADC_CR, STM32H7_ADDIS);
		dev_err(&indio_dev->dev, "Failed to enable ADC\n");
	पूर्ण अन्यथा अणु
		/* Clear ADRDY by writing one */
		sपंचांग32_adc_set_bits(adc, STM32H7_ADC_ISR, STM32H7_ADRDY);
	पूर्ण

	वापस ret;
पूर्ण

अटल व्योम sपंचांग32h7_adc_disable(काष्ठा iio_dev *indio_dev)
अणु
	काष्ठा sपंचांग32_adc *adc = iio_priv(indio_dev);
	पूर्णांक ret;
	u32 val;

	/* Disable ADC and रुको until it's effectively disabled */
	sपंचांग32_adc_set_bits(adc, STM32H7_ADC_CR, STM32H7_ADDIS);
	ret = sपंचांग32_adc_पढ़ोl_poll_समयout(STM32H7_ADC_CR, val,
					   !(val & STM32H7_ADEN), 100,
					   STM32_ADC_TIMEOUT_US);
	अगर (ret)
		dev_warn(&indio_dev->dev, "Failed to disable\n");
पूर्ण

/**
 * sपंचांग32h7_adc_पढ़ो_selfcalib() - पढ़ो calibration shaकरोw regs, save result
 * @indio_dev: IIO device instance
 * Note: Must be called once ADC is enabled, so LINCALRDYW[1..6] are writable
 */
अटल पूर्णांक sपंचांग32h7_adc_पढ़ो_selfcalib(काष्ठा iio_dev *indio_dev)
अणु
	काष्ठा sपंचांग32_adc *adc = iio_priv(indio_dev);
	पूर्णांक i, ret;
	u32 lincalrdyw_mask, val;

	/* Read linearity calibration */
	lincalrdyw_mask = STM32H7_LINCALRDYW6;
	क्रम (i = STM32H7_LINCALFACT_NUM - 1; i >= 0; i--) अणु
		/* Clear STM32H7_LINCALRDYW[6..1]: transfer calib to CALFACT2 */
		sपंचांग32_adc_clr_bits(adc, STM32H7_ADC_CR, lincalrdyw_mask);

		/* Poll: रुको calib data to be पढ़ोy in CALFACT2 रेजिस्टर */
		ret = sपंचांग32_adc_पढ़ोl_poll_समयout(STM32H7_ADC_CR, val,
						   !(val & lincalrdyw_mask),
						   100, STM32_ADC_TIMEOUT_US);
		अगर (ret) अणु
			dev_err(&indio_dev->dev, "Failed to read calfact\n");
			वापस ret;
		पूर्ण

		val = sपंचांग32_adc_पढ़ोl(adc, STM32H7_ADC_CALFACT2);
		adc->cal.lincalfact[i] = (val & STM32H7_LINCALFACT_MASK);
		adc->cal.lincalfact[i] >>= STM32H7_LINCALFACT_SHIFT;

		lincalrdyw_mask >>= 1;
	पूर्ण

	/* Read offset calibration */
	val = sपंचांग32_adc_पढ़ोl(adc, STM32H7_ADC_CALFACT);
	adc->cal.calfact_s = (val & STM32H7_CALFACT_S_MASK);
	adc->cal.calfact_s >>= STM32H7_CALFACT_S_SHIFT;
	adc->cal.calfact_d = (val & STM32H7_CALFACT_D_MASK);
	adc->cal.calfact_d >>= STM32H7_CALFACT_D_SHIFT;
	adc->cal.calibrated = true;

	वापस 0;
पूर्ण

/**
 * sपंचांग32h7_adc_restore_selfcalib() - Restore saved self-calibration result
 * @indio_dev: IIO device instance
 * Note: ADC must be enabled, with no on-going conversions.
 */
अटल पूर्णांक sपंचांग32h7_adc_restore_selfcalib(काष्ठा iio_dev *indio_dev)
अणु
	काष्ठा sपंचांग32_adc *adc = iio_priv(indio_dev);
	पूर्णांक i, ret;
	u32 lincalrdyw_mask, val;

	val = (adc->cal.calfact_s << STM32H7_CALFACT_S_SHIFT) |
		(adc->cal.calfact_d << STM32H7_CALFACT_D_SHIFT);
	sपंचांग32_adc_ग_लिखोl(adc, STM32H7_ADC_CALFACT, val);

	lincalrdyw_mask = STM32H7_LINCALRDYW6;
	क्रम (i = STM32H7_LINCALFACT_NUM - 1; i >= 0; i--) अणु
		/*
		 * Write saved calibration data to shaकरोw रेजिस्टरs:
		 * Write CALFACT2, and set LINCALRDYW[6..1] bit to trigger
		 * data ग_लिखो. Then poll to रुको क्रम complete transfer.
		 */
		val = adc->cal.lincalfact[i] << STM32H7_LINCALFACT_SHIFT;
		sपंचांग32_adc_ग_लिखोl(adc, STM32H7_ADC_CALFACT2, val);
		sपंचांग32_adc_set_bits(adc, STM32H7_ADC_CR, lincalrdyw_mask);
		ret = sपंचांग32_adc_पढ़ोl_poll_समयout(STM32H7_ADC_CR, val,
						   val & lincalrdyw_mask,
						   100, STM32_ADC_TIMEOUT_US);
		अगर (ret) अणु
			dev_err(&indio_dev->dev, "Failed to write calfact\n");
			वापस ret;
		पूर्ण

		/*
		 * Read back calibration data, has two effects:
		 * - It ensures bits LINCALRDYW[6..1] are kept cleared
		 *   क्रम next समय calibration needs to be restored.
		 * - BTW, bit clear triggers a पढ़ो, then check data has been
		 *   correctly written.
		 */
		sपंचांग32_adc_clr_bits(adc, STM32H7_ADC_CR, lincalrdyw_mask);
		ret = sपंचांग32_adc_पढ़ोl_poll_समयout(STM32H7_ADC_CR, val,
						   !(val & lincalrdyw_mask),
						   100, STM32_ADC_TIMEOUT_US);
		अगर (ret) अणु
			dev_err(&indio_dev->dev, "Failed to read calfact\n");
			वापस ret;
		पूर्ण
		val = sपंचांग32_adc_पढ़ोl(adc, STM32H7_ADC_CALFACT2);
		अगर (val != adc->cal.lincalfact[i] << STM32H7_LINCALFACT_SHIFT) अणु
			dev_err(&indio_dev->dev, "calfact not consistent\n");
			वापस -EIO;
		पूर्ण

		lincalrdyw_mask >>= 1;
	पूर्ण

	वापस 0;
पूर्ण

/**
 * Fixed समयout value क्रम ADC calibration.
 * worst हालs:
 * - low घड़ी frequency
 * - maximum prescalers
 * Calibration requires:
 * - 131,072 ADC घड़ी cycle क्रम the linear calibration
 * - 20 ADC घड़ी cycle क्रम the offset calibration
 *
 * Set to 100ms क्रम now
 */
#घोषणा STM32H7_ADC_CALIB_TIMEOUT_US		100000

/**
 * sपंचांग32h7_adc_selfcalib() - Procedure to calibrate ADC
 * @indio_dev: IIO device instance
 * Note: Must be called once ADC is out of घातer करोwn.
 */
अटल पूर्णांक sपंचांग32h7_adc_selfcalib(काष्ठा iio_dev *indio_dev)
अणु
	काष्ठा sपंचांग32_adc *adc = iio_priv(indio_dev);
	पूर्णांक ret;
	u32 val;

	अगर (adc->cal.calibrated)
		वापस true;

	/*
	 * Select calibration mode:
	 * - Offset calibration क्रम single ended inमाला_दो
	 * - No linearity calibration (करो it later, beक्रमe पढ़ोing it)
	 */
	sपंचांग32_adc_clr_bits(adc, STM32H7_ADC_CR, STM32H7_ADCALDIF);
	sपंचांग32_adc_clr_bits(adc, STM32H7_ADC_CR, STM32H7_ADCALLIN);

	/* Start calibration, then रुको क्रम completion */
	sपंचांग32_adc_set_bits(adc, STM32H7_ADC_CR, STM32H7_ADCAL);
	ret = sपंचांग32_adc_पढ़ोl_poll_समयout(STM32H7_ADC_CR, val,
					   !(val & STM32H7_ADCAL), 100,
					   STM32H7_ADC_CALIB_TIMEOUT_US);
	अगर (ret) अणु
		dev_err(&indio_dev->dev, "calibration failed\n");
		जाओ out;
	पूर्ण

	/*
	 * Select calibration mode, then start calibration:
	 * - Offset calibration क्रम dअगरferential input
	 * - Linearity calibration (needs to be करोne only once क्रम single/dअगरf)
	 *   will run simultaneously with offset calibration.
	 */
	sपंचांग32_adc_set_bits(adc, STM32H7_ADC_CR,
			   STM32H7_ADCALDIF | STM32H7_ADCALLIN);
	sपंचांग32_adc_set_bits(adc, STM32H7_ADC_CR, STM32H7_ADCAL);
	ret = sपंचांग32_adc_पढ़ोl_poll_समयout(STM32H7_ADC_CR, val,
					   !(val & STM32H7_ADCAL), 100,
					   STM32H7_ADC_CALIB_TIMEOUT_US);
	अगर (ret) अणु
		dev_err(&indio_dev->dev, "calibration failed\n");
		जाओ out;
	पूर्ण

out:
	sपंचांग32_adc_clr_bits(adc, STM32H7_ADC_CR,
			   STM32H7_ADCALDIF | STM32H7_ADCALLIN);

	वापस ret;
पूर्ण

/**
 * sपंचांग32h7_adc_prepare() - Leave घातer करोwn mode to enable ADC.
 * @indio_dev: IIO device instance
 * Leave घातer करोwn mode.
 * Configure channels as single ended or dअगरferential beक्रमe enabling ADC.
 * Enable ADC.
 * Restore calibration data.
 * Pre-select channels that may be used in PCSEL (required by input MUX / IO):
 * - Only one input is selected क्रम single ended (e.g. 'vinp')
 * - Two inमाला_दो are selected क्रम dअगरferential channels (e.g. 'vinp' & 'vinn')
 */
अटल पूर्णांक sपंचांग32h7_adc_prepare(काष्ठा iio_dev *indio_dev)
अणु
	काष्ठा sपंचांग32_adc *adc = iio_priv(indio_dev);
	पूर्णांक calib, ret;

	ret = sपंचांग32h7_adc_निकास_pwr_करोwn(indio_dev);
	अगर (ret)
		वापस ret;

	ret = sपंचांग32h7_adc_selfcalib(indio_dev);
	अगर (ret < 0)
		जाओ pwr_dwn;
	calib = ret;

	sपंचांग32_adc_ग_लिखोl(adc, STM32H7_ADC_DIFSEL, adc->dअगरsel);

	ret = sपंचांग32h7_adc_enable(indio_dev);
	अगर (ret)
		जाओ pwr_dwn;

	/* Either restore or पढ़ो calibration result क्रम future reference */
	अगर (calib)
		ret = sपंचांग32h7_adc_restore_selfcalib(indio_dev);
	अन्यथा
		ret = sपंचांग32h7_adc_पढ़ो_selfcalib(indio_dev);
	अगर (ret)
		जाओ disable;

	sपंचांग32_adc_ग_लिखोl(adc, STM32H7_ADC_PCSEL, adc->pcsel);

	वापस 0;

disable:
	sपंचांग32h7_adc_disable(indio_dev);
pwr_dwn:
	sपंचांग32h7_adc_enter_pwr_करोwn(adc);

	वापस ret;
पूर्ण

अटल व्योम sपंचांग32h7_adc_unprepare(काष्ठा iio_dev *indio_dev)
अणु
	काष्ठा sपंचांग32_adc *adc = iio_priv(indio_dev);

	sपंचांग32h7_adc_disable(indio_dev);
	sपंचांग32h7_adc_enter_pwr_करोwn(adc);
पूर्ण

/**
 * sपंचांग32_adc_conf_scan_seq() - Build regular channels scan sequence
 * @indio_dev: IIO device
 * @scan_mask: channels to be converted
 *
 * Conversion sequence :
 * Apply sampling समय settings क्रम all channels.
 * Configure ADC scan sequence based on selected channels in scan_mask.
 * Add channels to SQR रेजिस्टरs, from scan_mask LSB to MSB, then
 * program sequence len.
 */
अटल पूर्णांक sपंचांग32_adc_conf_scan_seq(काष्ठा iio_dev *indio_dev,
				   स्थिर अचिन्हित दीर्घ *scan_mask)
अणु
	काष्ठा sपंचांग32_adc *adc = iio_priv(indio_dev);
	स्थिर काष्ठा sपंचांग32_adc_regs *sqr = adc->cfg->regs->sqr;
	स्थिर काष्ठा iio_chan_spec *chan;
	u32 val, bit;
	पूर्णांक i = 0;

	/* Apply sampling समय settings */
	sपंचांग32_adc_ग_लिखोl(adc, adc->cfg->regs->smpr[0], adc->smpr_val[0]);
	sपंचांग32_adc_ग_लिखोl(adc, adc->cfg->regs->smpr[1], adc->smpr_val[1]);

	क्रम_each_set_bit(bit, scan_mask, indio_dev->masklength) अणु
		chan = indio_dev->channels + bit;
		/*
		 * Assign one channel per SQ entry in regular
		 * sequence, starting with SQ1.
		 */
		i++;
		अगर (i > STM32_ADC_MAX_SQ)
			वापस -EINVAL;

		dev_dbg(&indio_dev->dev, "%s chan %d to SQ%d\n",
			__func__, chan->channel, i);

		val = sपंचांग32_adc_पढ़ोl(adc, sqr[i].reg);
		val &= ~sqr[i].mask;
		val |= chan->channel << sqr[i].shअगरt;
		sपंचांग32_adc_ग_लिखोl(adc, sqr[i].reg, val);
	पूर्ण

	अगर (!i)
		वापस -EINVAL;

	/* Sequence len */
	val = sपंचांग32_adc_पढ़ोl(adc, sqr[0].reg);
	val &= ~sqr[0].mask;
	val |= ((i - 1) << sqr[0].shअगरt);
	sपंचांग32_adc_ग_लिखोl(adc, sqr[0].reg, val);

	वापस 0;
पूर्ण

/**
 * sपंचांग32_adc_get_trig_extsel() - Get बाह्यal trigger selection
 * @indio_dev: IIO device काष्ठाure
 * @trig: trigger
 *
 * Returns trigger extsel value, अगर trig matches, -EINVAL otherwise.
 */
अटल पूर्णांक sपंचांग32_adc_get_trig_extsel(काष्ठा iio_dev *indio_dev,
				     काष्ठा iio_trigger *trig)
अणु
	काष्ठा sपंचांग32_adc *adc = iio_priv(indio_dev);
	पूर्णांक i;

	/* lookup triggers रेजिस्टरed by sपंचांग32 समयr trigger driver */
	क्रम (i = 0; adc->cfg->trigs[i].name; i++) अणु
		/**
		 * Checking both sपंचांग32 समयr trigger type and trig name
		 * should be safe against arbitrary trigger names.
		 */
		अगर ((is_sपंचांग32_समयr_trigger(trig) ||
		     is_sपंचांग32_lptim_trigger(trig)) &&
		    !म_भेद(adc->cfg->trigs[i].name, trig->name)) अणु
			वापस adc->cfg->trigs[i].extsel;
		पूर्ण
	पूर्ण

	वापस -EINVAL;
पूर्ण

/**
 * sपंचांग32_adc_set_trig() - Set a regular trigger
 * @indio_dev: IIO device
 * @trig: IIO trigger
 *
 * Set trigger source/polarity (e.g. SW, or HW with polarity) :
 * - अगर HW trigger disabled (e.g. trig == शून्य, conversion launched by sw)
 * - अगर HW trigger enabled, set source & polarity
 */
अटल पूर्णांक sपंचांग32_adc_set_trig(काष्ठा iio_dev *indio_dev,
			      काष्ठा iio_trigger *trig)
अणु
	काष्ठा sपंचांग32_adc *adc = iio_priv(indio_dev);
	u32 val, extsel = 0, exten = STM32_EXTEN_SWTRIG;
	अचिन्हित दीर्घ flags;
	पूर्णांक ret;

	अगर (trig) अणु
		ret = sपंचांग32_adc_get_trig_extsel(indio_dev, trig);
		अगर (ret < 0)
			वापस ret;

		/* set trigger source and polarity (शेष to rising edge) */
		extsel = ret;
		exten = adc->trigger_polarity + STM32_EXTEN_HWTRIG_RISING_EDGE;
	पूर्ण

	spin_lock_irqsave(&adc->lock, flags);
	val = sपंचांग32_adc_पढ़ोl(adc, adc->cfg->regs->exten.reg);
	val &= ~(adc->cfg->regs->exten.mask | adc->cfg->regs->extsel.mask);
	val |= exten << adc->cfg->regs->exten.shअगरt;
	val |= extsel << adc->cfg->regs->extsel.shअगरt;
	sपंचांग32_adc_ग_लिखोl(adc,  adc->cfg->regs->exten.reg, val);
	spin_unlock_irqrestore(&adc->lock, flags);

	वापस 0;
पूर्ण

अटल पूर्णांक sपंचांग32_adc_set_trig_pol(काष्ठा iio_dev *indio_dev,
				  स्थिर काष्ठा iio_chan_spec *chan,
				  अचिन्हित पूर्णांक type)
अणु
	काष्ठा sपंचांग32_adc *adc = iio_priv(indio_dev);

	adc->trigger_polarity = type;

	वापस 0;
पूर्ण

अटल पूर्णांक sपंचांग32_adc_get_trig_pol(काष्ठा iio_dev *indio_dev,
				  स्थिर काष्ठा iio_chan_spec *chan)
अणु
	काष्ठा sपंचांग32_adc *adc = iio_priv(indio_dev);

	वापस adc->trigger_polarity;
पूर्ण

अटल स्थिर अक्षर * स्थिर sपंचांग32_trig_pol_items[] = अणु
	"rising-edge", "falling-edge", "both-edges",
पूर्ण;

अटल स्थिर काष्ठा iio_क्रमागत sपंचांग32_adc_trig_pol = अणु
	.items = sपंचांग32_trig_pol_items,
	.num_items = ARRAY_SIZE(sपंचांग32_trig_pol_items),
	.get = sपंचांग32_adc_get_trig_pol,
	.set = sपंचांग32_adc_set_trig_pol,
पूर्ण;

/**
 * sपंचांग32_adc_single_conv() - Perक्रमms a single conversion
 * @indio_dev: IIO device
 * @chan: IIO channel
 * @res: conversion result
 *
 * The function perक्रमms a single conversion on a given channel:
 * - Apply sampling समय settings
 * - Program sequencer with one channel (e.g. in SQ1 with len = 1)
 * - Use SW trigger
 * - Start conversion, then रुको क्रम पूर्णांकerrupt completion.
 */
अटल पूर्णांक sपंचांग32_adc_single_conv(काष्ठा iio_dev *indio_dev,
				 स्थिर काष्ठा iio_chan_spec *chan,
				 पूर्णांक *res)
अणु
	काष्ठा sपंचांग32_adc *adc = iio_priv(indio_dev);
	काष्ठा device *dev = indio_dev->dev.parent;
	स्थिर काष्ठा sपंचांग32_adc_regspec *regs = adc->cfg->regs;
	दीर्घ समयout;
	u32 val;
	पूर्णांक ret;

	reinit_completion(&adc->completion);

	adc->bufi = 0;

	ret = pm_runसमय_get_sync(dev);
	अगर (ret < 0) अणु
		pm_runसमय_put_noidle(dev);
		वापस ret;
	पूर्ण

	/* Apply sampling समय settings */
	sपंचांग32_adc_ग_लिखोl(adc, regs->smpr[0], adc->smpr_val[0]);
	sपंचांग32_adc_ग_लिखोl(adc, regs->smpr[1], adc->smpr_val[1]);

	/* Program chan number in regular sequence (SQ1) */
	val = sपंचांग32_adc_पढ़ोl(adc, regs->sqr[1].reg);
	val &= ~regs->sqr[1].mask;
	val |= chan->channel << regs->sqr[1].shअगरt;
	sपंचांग32_adc_ग_लिखोl(adc, regs->sqr[1].reg, val);

	/* Set regular sequence len (0 क्रम 1 conversion) */
	sपंचांग32_adc_clr_bits(adc, regs->sqr[0].reg, regs->sqr[0].mask);

	/* Trigger detection disabled (conversion can be launched in SW) */
	sपंचांग32_adc_clr_bits(adc, regs->exten.reg, regs->exten.mask);

	sपंचांग32_adc_conv_irq_enable(adc);

	adc->cfg->start_conv(indio_dev, false);

	समयout = रुको_क्रम_completion_पूर्णांकerruptible_समयout(
					&adc->completion, STM32_ADC_TIMEOUT);
	अगर (समयout == 0) अणु
		ret = -ETIMEDOUT;
	पूर्ण अन्यथा अगर (समयout < 0) अणु
		ret = समयout;
	पूर्ण अन्यथा अणु
		*res = adc->buffer[0];
		ret = IIO_VAL_INT;
	पूर्ण

	adc->cfg->stop_conv(indio_dev);

	sपंचांग32_adc_conv_irq_disable(adc);

	pm_runसमय_mark_last_busy(dev);
	pm_runसमय_put_स्वतःsuspend(dev);

	वापस ret;
पूर्ण

अटल पूर्णांक sपंचांग32_adc_पढ़ो_raw(काष्ठा iio_dev *indio_dev,
			      काष्ठा iio_chan_spec स्थिर *chan,
			      पूर्णांक *val, पूर्णांक *val2, दीर्घ mask)
अणु
	काष्ठा sपंचांग32_adc *adc = iio_priv(indio_dev);
	पूर्णांक ret;

	चयन (mask) अणु
	हाल IIO_CHAN_INFO_RAW:
		ret = iio_device_claim_direct_mode(indio_dev);
		अगर (ret)
			वापस ret;
		अगर (chan->type == IIO_VOLTAGE)
			ret = sपंचांग32_adc_single_conv(indio_dev, chan, val);
		अन्यथा
			ret = -EINVAL;
		iio_device_release_direct_mode(indio_dev);
		वापस ret;

	हाल IIO_CHAN_INFO_SCALE:
		अगर (chan->dअगरferential) अणु
			*val = adc->common->vref_mv * 2;
			*val2 = chan->scan_type.realbits;
		पूर्ण अन्यथा अणु
			*val = adc->common->vref_mv;
			*val2 = chan->scan_type.realbits;
		पूर्ण
		वापस IIO_VAL_FRACTIONAL_LOG2;

	हाल IIO_CHAN_INFO_OFFSET:
		अगर (chan->dअगरferential)
			/* ADC_full_scale / 2 */
			*val = -((1 << chan->scan_type.realbits) / 2);
		अन्यथा
			*val = 0;
		वापस IIO_VAL_INT;

	शेष:
		वापस -EINVAL;
	पूर्ण
पूर्ण

अटल व्योम sपंचांग32_adc_irq_clear(काष्ठा iio_dev *indio_dev, u32 msk)
अणु
	काष्ठा sपंचांग32_adc *adc = iio_priv(indio_dev);

	adc->cfg->irq_clear(indio_dev, msk);
पूर्ण

अटल irqवापस_t sपंचांग32_adc_thपढ़ोed_isr(पूर्णांक irq, व्योम *data)
अणु
	काष्ठा iio_dev *indio_dev = data;
	काष्ठा sपंचांग32_adc *adc = iio_priv(indio_dev);
	स्थिर काष्ठा sपंचांग32_adc_regspec *regs = adc->cfg->regs;
	u32 status = sपंचांग32_adc_पढ़ोl(adc, regs->isr_eoc.reg);
	u32 mask = sपंचांग32_adc_पढ़ोl(adc, regs->ier_eoc.reg);

	/* Check ovr status right now, as ovr mask should be alपढ़ोy disabled */
	अगर (status & regs->isr_ovr.mask) अणु
		/*
		 * Clear ovr bit to aव्योम subsequent calls to IRQ handler.
		 * This requires to stop ADC first. OVR bit state in ISR,
		 * is propaged to CSR रेजिस्टर by hardware.
		 */
		adc->cfg->stop_conv(indio_dev);
		sपंचांग32_adc_irq_clear(indio_dev, regs->isr_ovr.mask);
		dev_err(&indio_dev->dev, "Overrun, stopping: restart needed\n");
		वापस IRQ_HANDLED;
	पूर्ण

	अगर (!(status & mask))
		dev_err_ratelimited(&indio_dev->dev,
				    "Unexpected IRQ: IER=0x%08x, ISR=0x%08x\n",
				    mask, status);

	वापस IRQ_NONE;
पूर्ण

अटल irqवापस_t sपंचांग32_adc_isr(पूर्णांक irq, व्योम *data)
अणु
	काष्ठा iio_dev *indio_dev = data;
	काष्ठा sपंचांग32_adc *adc = iio_priv(indio_dev);
	स्थिर काष्ठा sपंचांग32_adc_regspec *regs = adc->cfg->regs;
	u32 status = sपंचांग32_adc_पढ़ोl(adc, regs->isr_eoc.reg);
	u32 mask = sपंचांग32_adc_पढ़ोl(adc, regs->ier_eoc.reg);

	अगर (!(status & mask))
		वापस IRQ_WAKE_THREAD;

	अगर (status & regs->isr_ovr.mask) अणु
		/*
		 * Overrun occurred on regular conversions: data क्रम wrong
		 * channel may be पढ़ो. Unconditionally disable पूर्णांकerrupts
		 * to stop processing data and prपूर्णांक error message.
		 * Restarting the capture can be करोne by disabling, then
		 * re-enabling it (e.g. ग_लिखो 0, then 1 to buffer/enable).
		 */
		sपंचांग32_adc_ovr_irq_disable(adc);
		sपंचांग32_adc_conv_irq_disable(adc);
		वापस IRQ_WAKE_THREAD;
	पूर्ण

	अगर (status & regs->isr_eoc.mask) अणु
		/* Reading DR also clears EOC status flag */
		adc->buffer[adc->bufi] = sपंचांग32_adc_पढ़ोw(adc, regs->dr);
		अगर (iio_buffer_enabled(indio_dev)) अणु
			adc->bufi++;
			अगर (adc->bufi >= adc->num_conv) अणु
				sपंचांग32_adc_conv_irq_disable(adc);
				iio_trigger_poll(indio_dev->trig);
			पूर्ण
		पूर्ण अन्यथा अणु
			complete(&adc->completion);
		पूर्ण
		वापस IRQ_HANDLED;
	पूर्ण

	वापस IRQ_NONE;
पूर्ण

/**
 * sपंचांग32_adc_validate_trigger() - validate trigger क्रम sपंचांग32 adc
 * @indio_dev: IIO device
 * @trig: new trigger
 *
 * Returns: 0 अगर trig matches one of the triggers रेजिस्टरed by sपंचांग32 adc
 * driver, -EINVAL otherwise.
 */
अटल पूर्णांक sपंचांग32_adc_validate_trigger(काष्ठा iio_dev *indio_dev,
				      काष्ठा iio_trigger *trig)
अणु
	वापस sपंचांग32_adc_get_trig_extsel(indio_dev, trig) < 0 ? -EINVAL : 0;
पूर्ण

अटल पूर्णांक sपंचांग32_adc_set_watermark(काष्ठा iio_dev *indio_dev, अचिन्हित पूर्णांक val)
अणु
	काष्ठा sपंचांग32_adc *adc = iio_priv(indio_dev);
	अचिन्हित पूर्णांक watermark = STM32_DMA_BUFFER_SIZE / 2;
	अचिन्हित पूर्णांक rx_buf_sz = STM32_DMA_BUFFER_SIZE;

	/*
	 * dma cyclic transfers are used, buffer is split पूर्णांकo two periods.
	 * There should be :
	 * - always one buffer (period) dma is working on
	 * - one buffer (period) driver can push data.
	 */
	watermark = min(watermark, val * (अचिन्हित)(माप(u16)));
	adc->rx_buf_sz = min(rx_buf_sz, watermark * 2 * adc->num_conv);

	वापस 0;
पूर्ण

अटल पूर्णांक sपंचांग32_adc_update_scan_mode(काष्ठा iio_dev *indio_dev,
				      स्थिर अचिन्हित दीर्घ *scan_mask)
अणु
	काष्ठा sपंचांग32_adc *adc = iio_priv(indio_dev);
	काष्ठा device *dev = indio_dev->dev.parent;
	पूर्णांक ret;

	ret = pm_runसमय_get_sync(dev);
	अगर (ret < 0) अणु
		pm_runसमय_put_noidle(dev);
		वापस ret;
	पूर्ण

	adc->num_conv = biपंचांगap_weight(scan_mask, indio_dev->masklength);

	ret = sपंचांग32_adc_conf_scan_seq(indio_dev, scan_mask);
	pm_runसमय_mark_last_busy(dev);
	pm_runसमय_put_स्वतःsuspend(dev);

	वापस ret;
पूर्ण

अटल पूर्णांक sपंचांग32_adc_of_xlate(काष्ठा iio_dev *indio_dev,
			      स्थिर काष्ठा of_phandle_args *iiospec)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < indio_dev->num_channels; i++)
		अगर (indio_dev->channels[i].channel == iiospec->args[0])
			वापस i;

	वापस -EINVAL;
पूर्ण

/**
 * sपंचांग32_adc_debugfs_reg_access - पढ़ो or ग_लिखो रेजिस्टर value
 * @indio_dev: IIO device काष्ठाure
 * @reg: रेजिस्टर offset
 * @ग_लिखोval: value to ग_लिखो
 * @पढ़ोval: value to पढ़ो
 *
 * To पढ़ो a value from an ADC रेजिस्टर:
 *   echo [ADC reg offset] > direct_reg_access
 *   cat direct_reg_access
 *
 * To ग_लिखो a value in a ADC रेजिस्टर:
 *   echo [ADC_reg_offset] [value] > direct_reg_access
 */
अटल पूर्णांक sपंचांग32_adc_debugfs_reg_access(काष्ठा iio_dev *indio_dev,
					अचिन्हित reg, अचिन्हित ग_लिखोval,
					अचिन्हित *पढ़ोval)
अणु
	काष्ठा sपंचांग32_adc *adc = iio_priv(indio_dev);
	काष्ठा device *dev = indio_dev->dev.parent;
	पूर्णांक ret;

	ret = pm_runसमय_get_sync(dev);
	अगर (ret < 0) अणु
		pm_runसमय_put_noidle(dev);
		वापस ret;
	पूर्ण

	अगर (!पढ़ोval)
		sपंचांग32_adc_ग_लिखोl(adc, reg, ग_लिखोval);
	अन्यथा
		*पढ़ोval = sपंचांग32_adc_पढ़ोl(adc, reg);

	pm_runसमय_mark_last_busy(dev);
	pm_runसमय_put_स्वतःsuspend(dev);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा iio_info sपंचांग32_adc_iio_info = अणु
	.पढ़ो_raw = sपंचांग32_adc_पढ़ो_raw,
	.validate_trigger = sपंचांग32_adc_validate_trigger,
	.hwfअगरo_set_watermark = sपंचांग32_adc_set_watermark,
	.update_scan_mode = sपंचांग32_adc_update_scan_mode,
	.debugfs_reg_access = sपंचांग32_adc_debugfs_reg_access,
	.of_xlate = sपंचांग32_adc_of_xlate,
पूर्ण;

अटल अचिन्हित पूर्णांक sपंचांग32_adc_dma_residue(काष्ठा sपंचांग32_adc *adc)
अणु
	काष्ठा dma_tx_state state;
	क्रमागत dma_status status;

	status = dmaengine_tx_status(adc->dma_chan,
				     adc->dma_chan->cookie,
				     &state);
	अगर (status == DMA_IN_PROGRESS) अणु
		/* Residue is size in bytes from end of buffer */
		अचिन्हित पूर्णांक i = adc->rx_buf_sz - state.residue;
		अचिन्हित पूर्णांक size;

		/* Return available bytes */
		अगर (i >= adc->bufi)
			size = i - adc->bufi;
		अन्यथा
			size = adc->rx_buf_sz + i - adc->bufi;

		वापस size;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम sपंचांग32_adc_dma_buffer_करोne(व्योम *data)
अणु
	काष्ठा iio_dev *indio_dev = data;
	काष्ठा sपंचांग32_adc *adc = iio_priv(indio_dev);
	पूर्णांक residue = sपंचांग32_adc_dma_residue(adc);

	/*
	 * In DMA mode the trigger services of IIO are not used
	 * (e.g. no call to iio_trigger_poll).
	 * Calling irq handler associated to the hardware trigger is not
	 * relevant as the conversions have alपढ़ोy been करोne. Data
	 * transfers are perक्रमmed directly in DMA callback instead.
	 * This implementation aव्योमs to call trigger irq handler that
	 * may sleep, in an atomic context (DMA irq handler context).
	 */
	dev_dbg(&indio_dev->dev, "%s bufi=%d\n", __func__, adc->bufi);

	जबतक (residue >= indio_dev->scan_bytes) अणु
		u16 *buffer = (u16 *)&adc->rx_buf[adc->bufi];

		iio_push_to_buffers(indio_dev, buffer);

		residue -= indio_dev->scan_bytes;
		adc->bufi += indio_dev->scan_bytes;
		अगर (adc->bufi >= adc->rx_buf_sz)
			adc->bufi = 0;
	पूर्ण
पूर्ण

अटल पूर्णांक sपंचांग32_adc_dma_start(काष्ठा iio_dev *indio_dev)
अणु
	काष्ठा sपंचांग32_adc *adc = iio_priv(indio_dev);
	काष्ठा dma_async_tx_descriptor *desc;
	dma_cookie_t cookie;
	पूर्णांक ret;

	अगर (!adc->dma_chan)
		वापस 0;

	dev_dbg(&indio_dev->dev, "%s size=%d watermark=%d\n", __func__,
		adc->rx_buf_sz, adc->rx_buf_sz / 2);

	/* Prepare a DMA cyclic transaction */
	desc = dmaengine_prep_dma_cyclic(adc->dma_chan,
					 adc->rx_dma_buf,
					 adc->rx_buf_sz, adc->rx_buf_sz / 2,
					 DMA_DEV_TO_MEM,
					 DMA_PREP_INTERRUPT);
	अगर (!desc)
		वापस -EBUSY;

	desc->callback = sपंचांग32_adc_dma_buffer_करोne;
	desc->callback_param = indio_dev;

	cookie = dmaengine_submit(desc);
	ret = dma_submit_error(cookie);
	अगर (ret) अणु
		dmaengine_terminate_sync(adc->dma_chan);
		वापस ret;
	पूर्ण

	/* Issue pending DMA requests */
	dma_async_issue_pending(adc->dma_chan);

	वापस 0;
पूर्ण

अटल पूर्णांक sपंचांग32_adc_buffer_postenable(काष्ठा iio_dev *indio_dev)
अणु
	काष्ठा sपंचांग32_adc *adc = iio_priv(indio_dev);
	काष्ठा device *dev = indio_dev->dev.parent;
	पूर्णांक ret;

	ret = pm_runसमय_get_sync(dev);
	अगर (ret < 0) अणु
		pm_runसमय_put_noidle(dev);
		वापस ret;
	पूर्ण

	ret = sपंचांग32_adc_set_trig(indio_dev, indio_dev->trig);
	अगर (ret) अणु
		dev_err(&indio_dev->dev, "Can't set trigger\n");
		जाओ err_pm_put;
	पूर्ण

	ret = sपंचांग32_adc_dma_start(indio_dev);
	अगर (ret) अणु
		dev_err(&indio_dev->dev, "Can't start dma\n");
		जाओ err_clr_trig;
	पूर्ण

	/* Reset adc buffer index */
	adc->bufi = 0;

	sपंचांग32_adc_ovr_irq_enable(adc);

	अगर (!adc->dma_chan)
		sपंचांग32_adc_conv_irq_enable(adc);

	adc->cfg->start_conv(indio_dev, !!adc->dma_chan);

	वापस 0;

err_clr_trig:
	sपंचांग32_adc_set_trig(indio_dev, शून्य);
err_pm_put:
	pm_runसमय_mark_last_busy(dev);
	pm_runसमय_put_स्वतःsuspend(dev);

	वापस ret;
पूर्ण

अटल पूर्णांक sपंचांग32_adc_buffer_predisable(काष्ठा iio_dev *indio_dev)
अणु
	काष्ठा sपंचांग32_adc *adc = iio_priv(indio_dev);
	काष्ठा device *dev = indio_dev->dev.parent;

	adc->cfg->stop_conv(indio_dev);
	अगर (!adc->dma_chan)
		sपंचांग32_adc_conv_irq_disable(adc);

	sपंचांग32_adc_ovr_irq_disable(adc);

	अगर (adc->dma_chan)
		dmaengine_terminate_sync(adc->dma_chan);

	अगर (sपंचांग32_adc_set_trig(indio_dev, शून्य))
		dev_err(&indio_dev->dev, "Can't clear trigger\n");

	pm_runसमय_mark_last_busy(dev);
	pm_runसमय_put_स्वतःsuspend(dev);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा iio_buffer_setup_ops sपंचांग32_adc_buffer_setup_ops = अणु
	.postenable = &sपंचांग32_adc_buffer_postenable,
	.predisable = &sपंचांग32_adc_buffer_predisable,
पूर्ण;

अटल irqवापस_t sपंचांग32_adc_trigger_handler(पूर्णांक irq, व्योम *p)
अणु
	काष्ठा iio_poll_func *pf = p;
	काष्ठा iio_dev *indio_dev = pf->indio_dev;
	काष्ठा sपंचांग32_adc *adc = iio_priv(indio_dev);

	dev_dbg(&indio_dev->dev, "%s bufi=%d\n", __func__, adc->bufi);

	/* reset buffer index */
	adc->bufi = 0;
	iio_push_to_buffers_with_बारtamp(indio_dev, adc->buffer,
					   pf->बारtamp);
	iio_trigger_notअगरy_करोne(indio_dev->trig);

	/* re-enable eoc irq */
	sपंचांग32_adc_conv_irq_enable(adc);

	वापस IRQ_HANDLED;
पूर्ण

अटल स्थिर काष्ठा iio_chan_spec_ext_info sपंचांग32_adc_ext_info[] = अणु
	IIO_ENUM("trigger_polarity", IIO_SHARED_BY_ALL, &sपंचांग32_adc_trig_pol),
	अणु
		.name = "trigger_polarity_available",
		.shared = IIO_SHARED_BY_ALL,
		.पढ़ो = iio_क्रमागत_available_पढ़ो,
		.निजी = (uपूर्णांकptr_t)&sपंचांग32_adc_trig_pol,
	पूर्ण,
	अणुपूर्ण,
पूर्ण;

अटल पूर्णांक sपंचांग32_adc_of_get_resolution(काष्ठा iio_dev *indio_dev)
अणु
	काष्ठा device_node *node = indio_dev->dev.of_node;
	काष्ठा sपंचांग32_adc *adc = iio_priv(indio_dev);
	अचिन्हित पूर्णांक i;
	u32 res;

	अगर (of_property_पढ़ो_u32(node, "assigned-resolution-bits", &res))
		res = adc->cfg->adc_info->resolutions[0];

	क्रम (i = 0; i < adc->cfg->adc_info->num_res; i++)
		अगर (res == adc->cfg->adc_info->resolutions[i])
			अवरोध;
	अगर (i >= adc->cfg->adc_info->num_res) अणु
		dev_err(&indio_dev->dev, "Bad resolution: %u bits\n", res);
		वापस -EINVAL;
	पूर्ण

	dev_dbg(&indio_dev->dev, "Using %u bits resolution\n", res);
	adc->res = i;

	वापस 0;
पूर्ण

अटल व्योम sपंचांग32_adc_smpr_init(काष्ठा sपंचांग32_adc *adc, पूर्णांक channel, u32 smp_ns)
अणु
	स्थिर काष्ठा sपंचांग32_adc_regs *smpr = &adc->cfg->regs->smp_bits[channel];
	u32 period_ns, shअगरt = smpr->shअगरt, mask = smpr->mask;
	अचिन्हित पूर्णांक smp, r = smpr->reg;

	/* Determine sampling समय (ADC घड़ी cycles) */
	period_ns = NSEC_PER_SEC / adc->common->rate;
	क्रम (smp = 0; smp <= STM32_ADC_MAX_SMP; smp++)
		अगर ((period_ns * adc->cfg->smp_cycles[smp]) >= smp_ns)
			अवरोध;
	अगर (smp > STM32_ADC_MAX_SMP)
		smp = STM32_ADC_MAX_SMP;

	/* pre-build sampling समय रेजिस्टरs (e.g. smpr1, smpr2) */
	adc->smpr_val[r] = (adc->smpr_val[r] & ~mask) | (smp << shअगरt);
पूर्ण

अटल व्योम sपंचांग32_adc_chan_init_one(काष्ठा iio_dev *indio_dev,
				    काष्ठा iio_chan_spec *chan, u32 vinp,
				    u32 vinn, पूर्णांक scan_index, bool dअगरferential)
अणु
	काष्ठा sपंचांग32_adc *adc = iio_priv(indio_dev);
	अक्षर *name = adc->chan_name[vinp];

	chan->type = IIO_VOLTAGE;
	chan->channel = vinp;
	अगर (dअगरferential) अणु
		chan->dअगरferential = 1;
		chan->channel2 = vinn;
		snम_लिखो(name, STM32_ADC_CH_SZ, "in%d-in%d", vinp, vinn);
	पूर्ण अन्यथा अणु
		snम_लिखो(name, STM32_ADC_CH_SZ, "in%d", vinp);
	पूर्ण
	chan->datasheet_name = name;
	chan->scan_index = scan_index;
	chan->indexed = 1;
	chan->info_mask_separate = BIT(IIO_CHAN_INFO_RAW);
	chan->info_mask_shared_by_type = BIT(IIO_CHAN_INFO_SCALE) |
					 BIT(IIO_CHAN_INFO_OFFSET);
	chan->scan_type.sign = 'u';
	chan->scan_type.realbits = adc->cfg->adc_info->resolutions[adc->res];
	chan->scan_type.storagebits = 16;
	chan->ext_info = sपंचांग32_adc_ext_info;

	/* pre-build selected channels mask */
	adc->pcsel |= BIT(chan->channel);
	अगर (dअगरferential) अणु
		/* pre-build dअगरf channels mask */
		adc->dअगरsel |= BIT(chan->channel);
		/* Also add negative input to pre-selected channels */
		adc->pcsel |= BIT(chan->channel2);
	पूर्ण
पूर्ण

अटल पूर्णांक sपंचांग32_adc_chan_of_init(काष्ठा iio_dev *indio_dev, bool बारtamping)
अणु
	काष्ठा device_node *node = indio_dev->dev.of_node;
	काष्ठा sपंचांग32_adc *adc = iio_priv(indio_dev);
	स्थिर काष्ठा sपंचांग32_adc_info *adc_info = adc->cfg->adc_info;
	काष्ठा sपंचांग32_adc_dअगरf_channel dअगरf[STM32_ADC_CH_MAX];
	काष्ठा property *prop;
	स्थिर __be32 *cur;
	काष्ठा iio_chan_spec *channels;
	पूर्णांक scan_index = 0, num_channels = 0, num_dअगरf = 0, ret, i;
	u32 val, smp = 0;

	ret = of_property_count_u32_elems(node, "st,adc-channels");
	अगर (ret > adc_info->max_channels) अणु
		dev_err(&indio_dev->dev, "Bad st,adc-channels?\n");
		वापस -EINVAL;
	पूर्ण अन्यथा अगर (ret > 0) अणु
		num_channels += ret;
	पूर्ण

	ret = of_property_count_elems_of_size(node, "st,adc-diff-channels",
					      माप(*dअगरf));
	अगर (ret > adc_info->max_channels) अणु
		dev_err(&indio_dev->dev, "Bad st,adc-diff-channels?\n");
		वापस -EINVAL;
	पूर्ण अन्यथा अगर (ret > 0) अणु
		पूर्णांक size = ret * माप(*dअगरf) / माप(u32);

		num_dअगरf = ret;
		num_channels += ret;
		ret = of_property_पढ़ो_u32_array(node, "st,adc-diff-channels",
						 (u32 *)dअगरf, size);
		अगर (ret)
			वापस ret;
	पूर्ण

	अगर (!num_channels) अणु
		dev_err(&indio_dev->dev, "No channels configured\n");
		वापस -ENODATA;
	पूर्ण

	/* Optional sample समय is provided either क्रम each, or all channels */
	ret = of_property_count_u32_elems(node, "st,min-sample-time-nsecs");
	अगर (ret > 1 && ret != num_channels) अणु
		dev_err(&indio_dev->dev, "Invalid st,min-sample-time-nsecs\n");
		वापस -EINVAL;
	पूर्ण

	अगर (बारtamping)
		num_channels++;

	channels = devm_kसुस्मृति(&indio_dev->dev, num_channels,
				माप(काष्ठा iio_chan_spec), GFP_KERNEL);
	अगर (!channels)
		वापस -ENOMEM;

	of_property_क्रम_each_u32(node, "st,adc-channels", prop, cur, val) अणु
		अगर (val >= adc_info->max_channels) अणु
			dev_err(&indio_dev->dev, "Invalid channel %d\n", val);
			वापस -EINVAL;
		पूर्ण

		/* Channel can't be configured both as single-ended & dअगरf */
		क्रम (i = 0; i < num_dअगरf; i++) अणु
			अगर (val == dअगरf[i].vinp) अणु
				dev_err(&indio_dev->dev,
					"channel %d miss-configured\n",	val);
				वापस -EINVAL;
			पूर्ण
		पूर्ण
		sपंचांग32_adc_chan_init_one(indio_dev, &channels[scan_index], val,
					0, scan_index, false);
		scan_index++;
	पूर्ण

	क्रम (i = 0; i < num_dअगरf; i++) अणु
		अगर (dअगरf[i].vinp >= adc_info->max_channels ||
		    dअगरf[i].vinn >= adc_info->max_channels) अणु
			dev_err(&indio_dev->dev, "Invalid channel in%d-in%d\n",
				dअगरf[i].vinp, dअगरf[i].vinn);
			वापस -EINVAL;
		पूर्ण
		sपंचांग32_adc_chan_init_one(indio_dev, &channels[scan_index],
					dअगरf[i].vinp, dअगरf[i].vinn, scan_index,
					true);
		scan_index++;
	पूर्ण

	क्रम (i = 0; i < scan_index; i++) अणु
		/*
		 * Using of_property_पढ़ो_u32_index(), smp value will only be
		 * modअगरied अगर valid u32 value can be decoded. This allows to
		 * get either no value, 1 shared value क्रम all indexes, or one
		 * value per channel.
		 */
		of_property_पढ़ो_u32_index(node, "st,min-sample-time-nsecs",
					   i, &smp);
		/* Prepare sampling समय settings */
		sपंचांग32_adc_smpr_init(adc, channels[i].channel, smp);
	पूर्ण

	अगर (बारtamping) अणु
		काष्ठा iio_chan_spec *बारtamp = &channels[scan_index];

		बारtamp->type = IIO_TIMESTAMP;
		बारtamp->channel = -1;
		बारtamp->scan_index = scan_index;
		बारtamp->scan_type.sign = 's';
		बारtamp->scan_type.realbits = 64;
		बारtamp->scan_type.storagebits = 64;

		scan_index++;
	पूर्ण

	indio_dev->num_channels = scan_index;
	indio_dev->channels = channels;

	वापस 0;
पूर्ण

अटल पूर्णांक sपंचांग32_adc_dma_request(काष्ठा device *dev, काष्ठा iio_dev *indio_dev)
अणु
	काष्ठा sपंचांग32_adc *adc = iio_priv(indio_dev);
	काष्ठा dma_slave_config config;
	पूर्णांक ret;

	adc->dma_chan = dma_request_chan(dev, "rx");
	अगर (IS_ERR(adc->dma_chan)) अणु
		ret = PTR_ERR(adc->dma_chan);
		अगर (ret != -ENODEV)
			वापस dev_err_probe(dev, ret,
					     "DMA channel request failed with\n");

		/* DMA is optional: fall back to IRQ mode */
		adc->dma_chan = शून्य;
		वापस 0;
	पूर्ण

	adc->rx_buf = dma_alloc_coherent(adc->dma_chan->device->dev,
					 STM32_DMA_BUFFER_SIZE,
					 &adc->rx_dma_buf, GFP_KERNEL);
	अगर (!adc->rx_buf) अणु
		ret = -ENOMEM;
		जाओ err_release;
	पूर्ण

	/* Configure DMA channel to पढ़ो data रेजिस्टर */
	स_रखो(&config, 0, माप(config));
	config.src_addr = (dma_addr_t)adc->common->phys_base;
	config.src_addr += adc->offset + adc->cfg->regs->dr;
	config.src_addr_width = DMA_SLAVE_BUSWIDTH_2_BYTES;

	ret = dmaengine_slave_config(adc->dma_chan, &config);
	अगर (ret)
		जाओ err_मुक्त;

	वापस 0;

err_मुक्त:
	dma_मुक्त_coherent(adc->dma_chan->device->dev, STM32_DMA_BUFFER_SIZE,
			  adc->rx_buf, adc->rx_dma_buf);
err_release:
	dma_release_channel(adc->dma_chan);

	वापस ret;
पूर्ण

अटल पूर्णांक sपंचांग32_adc_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा iio_dev *indio_dev;
	काष्ठा device *dev = &pdev->dev;
	irqवापस_t (*handler)(पूर्णांक irq, व्योम *p) = शून्य;
	काष्ठा sपंचांग32_adc *adc;
	bool बारtamping = false;
	पूर्णांक ret;

	अगर (!pdev->dev.of_node)
		वापस -ENODEV;

	indio_dev = devm_iio_device_alloc(&pdev->dev, माप(*adc));
	अगर (!indio_dev)
		वापस -ENOMEM;

	adc = iio_priv(indio_dev);
	adc->common = dev_get_drvdata(pdev->dev.parent);
	spin_lock_init(&adc->lock);
	init_completion(&adc->completion);
	adc->cfg = (स्थिर काष्ठा sपंचांग32_adc_cfg *)
		of_match_device(dev->driver->of_match_table, dev)->data;

	indio_dev->name = dev_name(&pdev->dev);
	indio_dev->dev.of_node = pdev->dev.of_node;
	indio_dev->info = &sपंचांग32_adc_iio_info;
	indio_dev->modes = INDIO_सूचीECT_MODE | INDIO_HARDWARE_TRIGGERED;

	platक्रमm_set_drvdata(pdev, indio_dev);

	ret = of_property_पढ़ो_u32(pdev->dev.of_node, "reg", &adc->offset);
	अगर (ret != 0) अणु
		dev_err(&pdev->dev, "missing reg property\n");
		वापस -EINVAL;
	पूर्ण

	adc->irq = platक्रमm_get_irq(pdev, 0);
	अगर (adc->irq < 0)
		वापस adc->irq;

	ret = devm_request_thपढ़ोed_irq(&pdev->dev, adc->irq, sपंचांग32_adc_isr,
					sपंचांग32_adc_thपढ़ोed_isr,
					0, pdev->name, indio_dev);
	अगर (ret) अणु
		dev_err(&pdev->dev, "failed to request IRQ\n");
		वापस ret;
	पूर्ण

	adc->clk = devm_clk_get(&pdev->dev, शून्य);
	अगर (IS_ERR(adc->clk)) अणु
		ret = PTR_ERR(adc->clk);
		अगर (ret == -ENOENT && !adc->cfg->clk_required) अणु
			adc->clk = शून्य;
		पूर्ण अन्यथा अणु
			dev_err(&pdev->dev, "Can't get clock\n");
			वापस ret;
		पूर्ण
	पूर्ण

	ret = sपंचांग32_adc_of_get_resolution(indio_dev);
	अगर (ret < 0)
		वापस ret;

	ret = sपंचांग32_adc_dma_request(dev, indio_dev);
	अगर (ret < 0)
		वापस ret;

	अगर (!adc->dma_chan) अणु
		/* For PIO mode only, iio_pollfunc_store_समय stores a बारtamp
		 * in the primary trigger IRQ handler and sपंचांग32_adc_trigger_handler
		 * runs in the IRQ thपढ़ो to push out buffer aदीर्घ with बारtamp.
		 */
		handler = &sपंचांग32_adc_trigger_handler;
		बारtamping = true;
	पूर्ण

	ret = sपंचांग32_adc_chan_of_init(indio_dev, बारtamping);
	अगर (ret < 0)
		जाओ err_dma_disable;

	ret = iio_triggered_buffer_setup(indio_dev,
					 &iio_pollfunc_store_समय, handler,
					 &sपंचांग32_adc_buffer_setup_ops);
	अगर (ret) अणु
		dev_err(&pdev->dev, "buffer setup failed\n");
		जाओ err_dma_disable;
	पूर्ण

	/* Get sपंचांग32-adc-core PM online */
	pm_runसमय_get_noresume(dev);
	pm_runसमय_set_active(dev);
	pm_runसमय_set_स्वतःsuspend_delay(dev, STM32_ADC_HW_STOP_DELAY_MS);
	pm_runसमय_use_स्वतःsuspend(dev);
	pm_runसमय_enable(dev);

	ret = sपंचांग32_adc_hw_start(dev);
	अगर (ret)
		जाओ err_buffer_cleanup;

	ret = iio_device_रेजिस्टर(indio_dev);
	अगर (ret) अणु
		dev_err(&pdev->dev, "iio dev register failed\n");
		जाओ err_hw_stop;
	पूर्ण

	pm_runसमय_mark_last_busy(dev);
	pm_runसमय_put_स्वतःsuspend(dev);

	वापस 0;

err_hw_stop:
	sपंचांग32_adc_hw_stop(dev);

err_buffer_cleanup:
	pm_runसमय_disable(dev);
	pm_runसमय_set_suspended(dev);
	pm_runसमय_put_noidle(dev);
	iio_triggered_buffer_cleanup(indio_dev);

err_dma_disable:
	अगर (adc->dma_chan) अणु
		dma_मुक्त_coherent(adc->dma_chan->device->dev,
				  STM32_DMA_BUFFER_SIZE,
				  adc->rx_buf, adc->rx_dma_buf);
		dma_release_channel(adc->dma_chan);
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक sपंचांग32_adc_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा iio_dev *indio_dev = platक्रमm_get_drvdata(pdev);
	काष्ठा sपंचांग32_adc *adc = iio_priv(indio_dev);

	pm_runसमय_get_sync(&pdev->dev);
	iio_device_unरेजिस्टर(indio_dev);
	sपंचांग32_adc_hw_stop(&pdev->dev);
	pm_runसमय_disable(&pdev->dev);
	pm_runसमय_set_suspended(&pdev->dev);
	pm_runसमय_put_noidle(&pdev->dev);
	iio_triggered_buffer_cleanup(indio_dev);
	अगर (adc->dma_chan) अणु
		dma_मुक्त_coherent(adc->dma_chan->device->dev,
				  STM32_DMA_BUFFER_SIZE,
				  adc->rx_buf, adc->rx_dma_buf);
		dma_release_channel(adc->dma_chan);
	पूर्ण

	वापस 0;
पूर्ण

#अगर defined(CONFIG_PM_SLEEP)
अटल पूर्णांक sपंचांग32_adc_suspend(काष्ठा device *dev)
अणु
	काष्ठा iio_dev *indio_dev = dev_get_drvdata(dev);

	अगर (iio_buffer_enabled(indio_dev))
		sपंचांग32_adc_buffer_predisable(indio_dev);

	वापस pm_runसमय_क्रमce_suspend(dev);
पूर्ण

अटल पूर्णांक sपंचांग32_adc_resume(काष्ठा device *dev)
अणु
	काष्ठा iio_dev *indio_dev = dev_get_drvdata(dev);
	पूर्णांक ret;

	ret = pm_runसमय_क्रमce_resume(dev);
	अगर (ret < 0)
		वापस ret;

	अगर (!iio_buffer_enabled(indio_dev))
		वापस 0;

	ret = sपंचांग32_adc_update_scan_mode(indio_dev,
					 indio_dev->active_scan_mask);
	अगर (ret < 0)
		वापस ret;

	वापस sपंचांग32_adc_buffer_postenable(indio_dev);
पूर्ण
#पूर्ण_अगर

#अगर defined(CONFIG_PM)
अटल पूर्णांक sपंचांग32_adc_runसमय_suspend(काष्ठा device *dev)
अणु
	वापस sपंचांग32_adc_hw_stop(dev);
पूर्ण

अटल पूर्णांक sपंचांग32_adc_runसमय_resume(काष्ठा device *dev)
अणु
	वापस sपंचांग32_adc_hw_start(dev);
पूर्ण
#पूर्ण_अगर

अटल स्थिर काष्ठा dev_pm_ops sपंचांग32_adc_pm_ops = अणु
	SET_SYSTEM_SLEEP_PM_OPS(sपंचांग32_adc_suspend, sपंचांग32_adc_resume)
	SET_RUNTIME_PM_OPS(sपंचांग32_adc_runसमय_suspend, sपंचांग32_adc_runसमय_resume,
			   शून्य)
पूर्ण;

अटल स्थिर काष्ठा sपंचांग32_adc_cfg sपंचांग32f4_adc_cfg = अणु
	.regs = &sपंचांग32f4_adc_regspec,
	.adc_info = &sपंचांग32f4_adc_info,
	.trigs = sपंचांग32f4_adc_trigs,
	.clk_required = true,
	.start_conv = sपंचांग32f4_adc_start_conv,
	.stop_conv = sपंचांग32f4_adc_stop_conv,
	.smp_cycles = sपंचांग32f4_adc_smp_cycles,
	.irq_clear = sपंचांग32f4_adc_irq_clear,
पूर्ण;

अटल स्थिर काष्ठा sपंचांग32_adc_cfg sपंचांग32h7_adc_cfg = अणु
	.regs = &sपंचांग32h7_adc_regspec,
	.adc_info = &sपंचांग32h7_adc_info,
	.trigs = sपंचांग32h7_adc_trigs,
	.start_conv = sपंचांग32h7_adc_start_conv,
	.stop_conv = sपंचांग32h7_adc_stop_conv,
	.prepare = sपंचांग32h7_adc_prepare,
	.unprepare = sपंचांग32h7_adc_unprepare,
	.smp_cycles = sपंचांग32h7_adc_smp_cycles,
	.irq_clear = sपंचांग32h7_adc_irq_clear,
पूर्ण;

अटल स्थिर काष्ठा sपंचांग32_adc_cfg sपंचांग32mp1_adc_cfg = अणु
	.regs = &sपंचांग32h7_adc_regspec,
	.adc_info = &sपंचांग32h7_adc_info,
	.trigs = sपंचांग32h7_adc_trigs,
	.has_vregपढ़ोy = true,
	.start_conv = sपंचांग32h7_adc_start_conv,
	.stop_conv = sपंचांग32h7_adc_stop_conv,
	.prepare = sपंचांग32h7_adc_prepare,
	.unprepare = sपंचांग32h7_adc_unprepare,
	.smp_cycles = sपंचांग32h7_adc_smp_cycles,
	.irq_clear = sपंचांग32h7_adc_irq_clear,
पूर्ण;

अटल स्थिर काष्ठा of_device_id sपंचांग32_adc_of_match[] = अणु
	अणु .compatible = "st,stm32f4-adc", .data = (व्योम *)&sपंचांग32f4_adc_cfg पूर्ण,
	अणु .compatible = "st,stm32h7-adc", .data = (व्योम *)&sपंचांग32h7_adc_cfg पूर्ण,
	अणु .compatible = "st,stm32mp1-adc", .data = (व्योम *)&sपंचांग32mp1_adc_cfg पूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, sपंचांग32_adc_of_match);

अटल काष्ठा platक्रमm_driver sपंचांग32_adc_driver = अणु
	.probe = sपंचांग32_adc_probe,
	.हटाओ = sपंचांग32_adc_हटाओ,
	.driver = अणु
		.name = "stm32-adc",
		.of_match_table = sपंचांग32_adc_of_match,
		.pm = &sपंचांग32_adc_pm_ops,
	पूर्ण,
पूर्ण;
module_platक्रमm_driver(sपंचांग32_adc_driver);

MODULE_AUTHOR("Fabrice Gasnier <fabrice.gasnier@st.com>");
MODULE_DESCRIPTION("STMicroelectronics STM32 ADC IIO driver");
MODULE_LICENSE("GPL v2");
MODULE_ALIAS("platform:stm32-adc");
