<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Aपंचांगel ADC driver क्रम SAMA5D2 devices and compatible.
 *
 * Copyright (C) 2015 Aपंचांगel,
 *               2015 Luकरोvic Desroches <luकरोvic.desroches@aपंचांगel.com>
 */

#समावेश <linux/bitops.h>
#समावेश <linux/clk.h>
#समावेश <linux/delay.h>
#समावेश <linux/dma-mapping.h>
#समावेश <linux/dmaengine.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/पन.स>
#समावेश <linux/module.h>
#समावेश <linux/of_device.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/sched.h>
#समावेश <linux/रुको.h>
#समावेश <linux/iio/iपन.स>
#समावेश <linux/iio/sysfs.h>
#समावेश <linux/iio/buffer.h>
#समावेश <linux/iio/trigger.h>
#समावेश <linux/iio/trigger_consumer.h>
#समावेश <linux/iio/triggered_buffer.h>
#समावेश <linux/pinctrl/consumer.h>
#समावेश <linux/regulator/consumer.h>

/* Control Register */
#घोषणा AT91_SAMA5D2_CR		0x00
/* Software Reset */
#घोषणा	AT91_SAMA5D2_CR_SWRST		BIT(0)
/* Start Conversion */
#घोषणा	AT91_SAMA5D2_CR_START		BIT(1)
/* Touchscreen Calibration */
#घोषणा	AT91_SAMA5D2_CR_TSCALIB		BIT(2)
/* Comparison Restart */
#घोषणा	AT91_SAMA5D2_CR_CMPRST		BIT(4)

/* Mode Register */
#घोषणा AT91_SAMA5D2_MR		0x04
/* Trigger Selection */
#घोषणा	AT91_SAMA5D2_MR_TRGSEL(v)	((v) << 1)
/* ADTRG */
#घोषणा	AT91_SAMA5D2_MR_TRGSEL_TRIG0	0
/* TIOA0 */
#घोषणा	AT91_SAMA5D2_MR_TRGSEL_TRIG1	1
/* TIOA1 */
#घोषणा	AT91_SAMA5D2_MR_TRGSEL_TRIG2	2
/* TIOA2 */
#घोषणा	AT91_SAMA5D2_MR_TRGSEL_TRIG3	3
/* PWM event line 0 */
#घोषणा	AT91_SAMA5D2_MR_TRGSEL_TRIG4	4
/* PWM event line 1 */
#घोषणा	AT91_SAMA5D2_MR_TRGSEL_TRIG5	5
/* TIOA3 */
#घोषणा	AT91_SAMA5D2_MR_TRGSEL_TRIG6	6
/* RTCOUT0 */
#घोषणा	AT91_SAMA5D2_MR_TRGSEL_TRIG7	7
/* Sleep Mode */
#घोषणा	AT91_SAMA5D2_MR_SLEEP		BIT(5)
/* Fast Wake Up */
#घोषणा	AT91_SAMA5D2_MR_FWUP		BIT(6)
/* Prescaler Rate Selection */
#घोषणा	AT91_SAMA5D2_MR_PRESCAL(v)	((v) << AT91_SAMA5D2_MR_PRESCAL_OFFSET)
#घोषणा	AT91_SAMA5D2_MR_PRESCAL_OFFSET	8
#घोषणा	AT91_SAMA5D2_MR_PRESCAL_MAX	0xff
#घोषणा AT91_SAMA5D2_MR_PRESCAL_MASK	GENMASK(15, 8)
/* Startup Time */
#घोषणा	AT91_SAMA5D2_MR_STARTUP(v)	((v) << 16)
#घोषणा AT91_SAMA5D2_MR_STARTUP_MASK	GENMASK(19, 16)
/* Analog Change */
#घोषणा	AT91_SAMA5D2_MR_ANACH		BIT(23)
/* Tracking Time */
#घोषणा	AT91_SAMA5D2_MR_TRACKTIM(v)	((v) << 24)
#घोषणा	AT91_SAMA5D2_MR_TRACKTIM_MAX	0xff
/* Transfer Time */
#घोषणा	AT91_SAMA5D2_MR_TRANSFER(v)	((v) << 28)
#घोषणा	AT91_SAMA5D2_MR_TRANSFER_MAX	0x3
/* Use Sequence Enable */
#घोषणा	AT91_SAMA5D2_MR_USEQ		BIT(31)

/* Channel Sequence Register 1 */
#घोषणा AT91_SAMA5D2_SEQR1	0x08
/* Channel Sequence Register 2 */
#घोषणा AT91_SAMA5D2_SEQR2	0x0c
/* Channel Enable Register */
#घोषणा AT91_SAMA5D2_CHER	0x10
/* Channel Disable Register */
#घोषणा AT91_SAMA5D2_CHDR	0x14
/* Channel Status Register */
#घोषणा AT91_SAMA5D2_CHSR	0x18
/* Last Converted Data Register */
#घोषणा AT91_SAMA5D2_LCDR	0x20
/* Interrupt Enable Register */
#घोषणा AT91_SAMA5D2_IER	0x24
/* Interrupt Enable Register - TS X measurement पढ़ोy */
#घोषणा AT91_SAMA5D2_IER_XRDY   BIT(20)
/* Interrupt Enable Register - TS Y measurement पढ़ोy */
#घोषणा AT91_SAMA5D2_IER_YRDY   BIT(21)
/* Interrupt Enable Register - TS pressure measurement पढ़ोy */
#घोषणा AT91_SAMA5D2_IER_PRDY   BIT(22)
/* Interrupt Enable Register - Data पढ़ोy */
#घोषणा AT91_SAMA5D2_IER_DRDY   BIT(24)
/* Interrupt Enable Register - general overrun error */
#घोषणा AT91_SAMA5D2_IER_GOVRE BIT(25)
/* Interrupt Enable Register - Pen detect */
#घोषणा AT91_SAMA5D2_IER_PEN    BIT(29)
/* Interrupt Enable Register - No pen detect */
#घोषणा AT91_SAMA5D2_IER_NOPEN  BIT(30)
/* Interrupt Disable Register */
#घोषणा AT91_SAMA5D2_IDR	0x28
/* Interrupt Mask Register */
#घोषणा AT91_SAMA5D2_IMR	0x2c
/* Interrupt Status Register */
#घोषणा AT91_SAMA5D2_ISR	0x30
/* Interrupt Status Register - Pen touching sense status */
#घोषणा AT91_SAMA5D2_ISR_PENS   BIT(31)
/* Last Channel Trigger Mode Register */
#घोषणा AT91_SAMA5D2_LCTMR	0x34
/* Last Channel Compare Winकरोw Register */
#घोषणा AT91_SAMA5D2_LCCWR	0x38
/* Overrun Status Register */
#घोषणा AT91_SAMA5D2_OVER	0x3c
/* Extended Mode Register */
#घोषणा AT91_SAMA5D2_EMR	0x40
/* Extended Mode Register - Oversampling rate */
#घोषणा AT91_SAMA5D2_EMR_OSR(V)			((V) << 16)
#घोषणा AT91_SAMA5D2_EMR_OSR_MASK		GENMASK(17, 16)
#घोषणा AT91_SAMA5D2_EMR_OSR_1SAMPLES		0
#घोषणा AT91_SAMA5D2_EMR_OSR_4SAMPLES		1
#घोषणा AT91_SAMA5D2_EMR_OSR_16SAMPLES		2

/* Extended Mode Register - Averaging on single trigger event */
#घोषणा AT91_SAMA5D2_EMR_ASTE(V)		((V) << 20)
/* Compare Winकरोw Register */
#घोषणा AT91_SAMA5D2_CWR	0x44
/* Channel Gain Register */
#घोषणा AT91_SAMA5D2_CGR	0x48

/* Channel Offset Register */
#घोषणा AT91_SAMA5D2_COR	0x4c
#घोषणा AT91_SAMA5D2_COR_DIFF_OFFSET	16

/* Channel Data Register 0 */
#घोषणा AT91_SAMA5D2_CDR0	0x50
/* Analog Control Register */
#घोषणा AT91_SAMA5D2_ACR	0x94
/* Analog Control Register - Pen detect sensitivity mask */
#घोषणा AT91_SAMA5D2_ACR_PENDETSENS_MASK        GENMASK(1, 0)

/* Touchscreen Mode Register */
#घोषणा AT91_SAMA5D2_TSMR	0xb0
/* Touchscreen Mode Register - No touch mode */
#घोषणा AT91_SAMA5D2_TSMR_TSMODE_NONE           0
/* Touchscreen Mode Register - 4 wire screen, no pressure measurement */
#घोषणा AT91_SAMA5D2_TSMR_TSMODE_4WIRE_NO_PRESS 1
/* Touchscreen Mode Register - 4 wire screen, pressure measurement */
#घोषणा AT91_SAMA5D2_TSMR_TSMODE_4WIRE_PRESS    2
/* Touchscreen Mode Register - 5 wire screen */
#घोषणा AT91_SAMA5D2_TSMR_TSMODE_5WIRE          3
/* Touchscreen Mode Register - Average samples mask */
#घोषणा AT91_SAMA5D2_TSMR_TSAV_MASK             GENMASK(5, 4)
/* Touchscreen Mode Register - Average samples */
#घोषणा AT91_SAMA5D2_TSMR_TSAV(x)               ((x) << 4)
/* Touchscreen Mode Register - Touch/trigger frequency ratio mask */
#घोषणा AT91_SAMA5D2_TSMR_TSFREQ_MASK           GENMASK(11, 8)
/* Touchscreen Mode Register - Touch/trigger frequency ratio */
#घोषणा AT91_SAMA5D2_TSMR_TSFREQ(x)             ((x) << 8)
/* Touchscreen Mode Register - Pen Debounce Time mask */
#घोषणा AT91_SAMA5D2_TSMR_PENDBC_MASK           GENMASK(31, 28)
/* Touchscreen Mode Register - Pen Debounce Time */
#घोषणा AT91_SAMA5D2_TSMR_PENDBC(x)            ((x) << 28)
/* Touchscreen Mode Register - No DMA क्रम touch measurements */
#घोषणा AT91_SAMA5D2_TSMR_NOTSDMA               BIT(22)
/* Touchscreen Mode Register - Disable pen detection */
#घोषणा AT91_SAMA5D2_TSMR_PENDET_DIS            (0 << 24)
/* Touchscreen Mode Register - Enable pen detection */
#घोषणा AT91_SAMA5D2_TSMR_PENDET_ENA            BIT(24)

/* Touchscreen X Position Register */
#घोषणा AT91_SAMA5D2_XPOSR	0xb4
/* Touchscreen Y Position Register */
#घोषणा AT91_SAMA5D2_YPOSR	0xb8
/* Touchscreen Pressure Register */
#घोषणा AT91_SAMA5D2_PRESSR	0xbc
/* Trigger Register */
#घोषणा AT91_SAMA5D2_TRGR	0xc0
/* Mask क्रम TRGMOD field of TRGR रेजिस्टर */
#घोषणा AT91_SAMA5D2_TRGR_TRGMOD_MASK GENMASK(2, 0)
/* No trigger, only software trigger can start conversions */
#घोषणा AT91_SAMA5D2_TRGR_TRGMOD_NO_TRIGGER 0
/* Trigger Mode बाह्यal trigger rising edge */
#घोषणा AT91_SAMA5D2_TRGR_TRGMOD_EXT_TRIG_RISE 1
/* Trigger Mode बाह्यal trigger falling edge */
#घोषणा AT91_SAMA5D2_TRGR_TRGMOD_EXT_TRIG_FALL 2
/* Trigger Mode बाह्यal trigger any edge */
#घोषणा AT91_SAMA5D2_TRGR_TRGMOD_EXT_TRIG_ANY 3
/* Trigger Mode पूर्णांकernal periodic */
#घोषणा AT91_SAMA5D2_TRGR_TRGMOD_PERIODIC 5
/* Trigger Mode - trigger period mask */
#घोषणा AT91_SAMA5D2_TRGR_TRGPER_MASK           GENMASK(31, 16)
/* Trigger Mode - trigger period */
#घोषणा AT91_SAMA5D2_TRGR_TRGPER(x)             ((x) << 16)

/* Correction Select Register */
#घोषणा AT91_SAMA5D2_COSR	0xd0
/* Correction Value Register */
#घोषणा AT91_SAMA5D2_CVR	0xd4
/* Channel Error Correction Register */
#घोषणा AT91_SAMA5D2_CECR	0xd8
/* Write Protection Mode Register */
#घोषणा AT91_SAMA5D2_WPMR	0xe4
/* Write Protection Status Register */
#घोषणा AT91_SAMA5D2_WPSR	0xe8
/* Version Register */
#घोषणा AT91_SAMA5D2_VERSION	0xfc

#घोषणा AT91_SAMA5D2_HW_TRIG_CNT 3
#घोषणा AT91_SAMA5D2_SINGLE_CHAN_CNT 12
#घोषणा AT91_SAMA5D2_DIFF_CHAN_CNT 6

#घोषणा AT91_SAMA5D2_TIMESTAMP_CHAN_IDX (AT91_SAMA5D2_SINGLE_CHAN_CNT + \
					 AT91_SAMA5D2_DIFF_CHAN_CNT + 1)

#घोषणा AT91_SAMA5D2_TOUCH_X_CHAN_IDX (AT91_SAMA5D2_SINGLE_CHAN_CNT + \
					 AT91_SAMA5D2_DIFF_CHAN_CNT * 2)
#घोषणा AT91_SAMA5D2_TOUCH_Y_CHAN_IDX   (AT91_SAMA5D2_TOUCH_X_CHAN_IDX + 1)
#घोषणा AT91_SAMA5D2_TOUCH_P_CHAN_IDX   (AT91_SAMA5D2_TOUCH_Y_CHAN_IDX + 1)
#घोषणा AT91_SAMA5D2_MAX_CHAN_IDX	AT91_SAMA5D2_TOUCH_P_CHAN_IDX

#घोषणा AT91_SAMA5D2_TOUCH_SAMPLE_PERIOD_US          2000    /* 2ms */
#घोषणा AT91_SAMA5D2_TOUCH_PEN_DETECT_DEBOUNCE_US    200

#घोषणा AT91_SAMA5D2_XYZ_MASK		GENMASK(11, 0)

#घोषणा AT91_SAMA5D2_MAX_POS_BITS			12

/*
 * Maximum number of bytes to hold conversion from all channels
 * without the बारtamp.
 */
#घोषणा AT91_BUFFER_MAX_CONVERSION_BYTES ((AT91_SAMA5D2_SINGLE_CHAN_CNT + \
					 AT91_SAMA5D2_DIFF_CHAN_CNT) * 2)

/* This total must also include the बारtamp */
#घोषणा AT91_BUFFER_MAX_BYTES (AT91_BUFFER_MAX_CONVERSION_BYTES + 8)

#घोषणा AT91_BUFFER_MAX_HWORDS (AT91_BUFFER_MAX_BYTES / 2)

#घोषणा AT91_HWFIFO_MAX_SIZE_STR	"128"
#घोषणा AT91_HWFIFO_MAX_SIZE		128

/* Possible values क्रम oversampling ratio */
#घोषणा AT91_OSR_1SAMPLES		1
#घोषणा AT91_OSR_4SAMPLES		4
#घोषणा AT91_OSR_16SAMPLES		16

#घोषणा AT91_SAMA5D2_CHAN_SINGLE(num, addr)				\
	अणु								\
		.type = IIO_VOLTAGE,					\
		.channel = num,						\
		.address = addr,					\
		.scan_index = num,					\
		.scan_type = अणु						\
			.sign = 'u',					\
			.realbits = 14,					\
			.storagebits = 16,				\
		पूर्ण,							\
		.info_mask_separate = BIT(IIO_CHAN_INFO_RAW),		\
		.info_mask_shared_by_type = BIT(IIO_CHAN_INFO_SCALE),	\
		.info_mask_shared_by_all = BIT(IIO_CHAN_INFO_SAMP_FREQ)|\
				BIT(IIO_CHAN_INFO_OVERSAMPLING_RATIO),	\
		.datasheet_name = "CH"#num,				\
		.indexed = 1,						\
	पूर्ण

#घोषणा AT91_SAMA5D2_CHAN_DIFF(num, num2, addr)				\
	अणु								\
		.type = IIO_VOLTAGE,					\
		.dअगरferential = 1,					\
		.channel = num,						\
		.channel2 = num2,					\
		.address = addr,					\
		.scan_index = num + AT91_SAMA5D2_SINGLE_CHAN_CNT,	\
		.scan_type = अणु						\
			.sign = 's',					\
			.realbits = 14,					\
			.storagebits = 16,				\
		पूर्ण,							\
		.info_mask_separate = BIT(IIO_CHAN_INFO_RAW),		\
		.info_mask_shared_by_type = BIT(IIO_CHAN_INFO_SCALE),	\
		.info_mask_shared_by_all = BIT(IIO_CHAN_INFO_SAMP_FREQ)|\
				BIT(IIO_CHAN_INFO_OVERSAMPLING_RATIO),	\
		.datasheet_name = "CH"#num"-CH"#num2,			\
		.indexed = 1,						\
	पूर्ण

#घोषणा AT91_SAMA5D2_CHAN_TOUCH(num, name, mod)				\
	अणु								\
		.type = IIO_POSITIONRELATIVE,				\
		.modअगरied = 1,						\
		.channel = num,						\
		.channel2 = mod,					\
		.scan_index = num,					\
		.scan_type = अणु						\
			.sign = 'u',					\
			.realbits = 12,					\
			.storagebits = 16,				\
		पूर्ण,							\
		.info_mask_separate = BIT(IIO_CHAN_INFO_RAW),		\
		.info_mask_shared_by_all = BIT(IIO_CHAN_INFO_SAMP_FREQ)|\
				BIT(IIO_CHAN_INFO_OVERSAMPLING_RATIO),	\
		.datasheet_name = name,					\
	पूर्ण
#घोषणा AT91_SAMA5D2_CHAN_PRESSURE(num, name)				\
	अणु								\
		.type = IIO_PRESSURE,					\
		.channel = num,						\
		.scan_index = num,					\
		.scan_type = अणु						\
			.sign = 'u',					\
			.realbits = 12,					\
			.storagebits = 16,				\
		पूर्ण,							\
		.info_mask_separate = BIT(IIO_CHAN_INFO_RAW),		\
		.info_mask_shared_by_all = BIT(IIO_CHAN_INFO_SAMP_FREQ)|\
				BIT(IIO_CHAN_INFO_OVERSAMPLING_RATIO),	\
		.datasheet_name = name,					\
	पूर्ण

#घोषणा at91_adc_पढ़ोl(st, reg)		पढ़ोl_relaxed(st->base + reg)
#घोषणा at91_adc_ग_लिखोl(st, reg, val)	ग_लिखोl_relaxed(val, st->base + reg)

काष्ठा at91_adc_soc_info अणु
	अचिन्हित			startup_समय;
	अचिन्हित			min_sample_rate;
	अचिन्हित			max_sample_rate;
पूर्ण;

काष्ठा at91_adc_trigger अणु
	अक्षर				*name;
	अचिन्हित पूर्णांक			trgmod_value;
	अचिन्हित पूर्णांक			edge_type;
	bool				hw_trig;
पूर्ण;

/**
 * काष्ठा at91_adc_dma - at91-sama5d2 dma inक्रमmation काष्ठा
 * @dma_chan:		the dma channel acquired
 * @rx_buf:		dma coherent allocated area
 * @rx_dma_buf:		dma handler क्रम the buffer
 * @phys_addr:		physical address of the ADC base रेजिस्टर
 * @buf_idx:		index inside the dma buffer where पढ़ोing was last करोne
 * @rx_buf_sz:		size of buffer used by DMA operation
 * @watermark:		number of conversions to copy beक्रमe DMA triggers irq
 * @dma_ts:		hold the start बारtamp of dma operation
 */
काष्ठा at91_adc_dma अणु
	काष्ठा dma_chan			*dma_chan;
	u8				*rx_buf;
	dma_addr_t			rx_dma_buf;
	phys_addr_t			phys_addr;
	पूर्णांक				buf_idx;
	पूर्णांक				rx_buf_sz;
	पूर्णांक				watermark;
	s64				dma_ts;
पूर्ण;

/**
 * काष्ठा at91_adc_touch - at91-sama5d2 touchscreen inक्रमmation काष्ठा
 * @sample_period_val:		the value क्रम periodic trigger पूर्णांकerval
 * @touching:			is the pen touching the screen or not
 * @x_pos:			temporary placeholder क्रम pressure computation
 * @channels_biपंचांगask:		biपंचांगask with the touchscreen channels enabled
 * @workq:			workqueue क्रम buffer data pushing
 */
काष्ठा at91_adc_touch अणु
	u16				sample_period_val;
	bool				touching;
	u16				x_pos;
	अचिन्हित दीर्घ			channels_biपंचांगask;
	काष्ठा work_काष्ठा		workq;
पूर्ण;

काष्ठा at91_adc_state अणु
	व्योम __iomem			*base;
	पूर्णांक				irq;
	काष्ठा clk			*per_clk;
	काष्ठा regulator		*reg;
	काष्ठा regulator		*vref;
	पूर्णांक				vref_uv;
	अचिन्हित पूर्णांक			current_sample_rate;
	काष्ठा iio_trigger		*trig;
	स्थिर काष्ठा at91_adc_trigger	*selected_trig;
	स्थिर काष्ठा iio_chan_spec	*chan;
	bool				conversion_करोne;
	u32				conversion_value;
	अचिन्हित पूर्णांक			oversampling_ratio;
	काष्ठा at91_adc_soc_info	soc_info;
	रुको_queue_head_t		wq_data_available;
	काष्ठा at91_adc_dma		dma_st;
	काष्ठा at91_adc_touch		touch_st;
	काष्ठा iio_dev			*indio_dev;
	u16				buffer[AT91_BUFFER_MAX_HWORDS];
	/*
	 * lock to prevent concurrent 'single conversion' requests through
	 * sysfs.
	 */
	काष्ठा mutex			lock;
पूर्ण;

अटल स्थिर काष्ठा at91_adc_trigger at91_adc_trigger_list[] = अणु
	अणु
		.name = "external_rising",
		.trgmod_value = AT91_SAMA5D2_TRGR_TRGMOD_EXT_TRIG_RISE,
		.edge_type = IRQ_TYPE_EDGE_RISING,
		.hw_trig = true,
	पूर्ण,
	अणु
		.name = "external_falling",
		.trgmod_value = AT91_SAMA5D2_TRGR_TRGMOD_EXT_TRIG_FALL,
		.edge_type = IRQ_TYPE_EDGE_FALLING,
		.hw_trig = true,
	पूर्ण,
	अणु
		.name = "external_any",
		.trgmod_value = AT91_SAMA5D2_TRGR_TRGMOD_EXT_TRIG_ANY,
		.edge_type = IRQ_TYPE_EDGE_BOTH,
		.hw_trig = true,
	पूर्ण,
	अणु
		.name = "software",
		.trgmod_value = AT91_SAMA5D2_TRGR_TRGMOD_NO_TRIGGER,
		.edge_type = IRQ_TYPE_NONE,
		.hw_trig = false,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा iio_chan_spec at91_adc_channels[] = अणु
	AT91_SAMA5D2_CHAN_SINGLE(0, 0x50),
	AT91_SAMA5D2_CHAN_SINGLE(1, 0x54),
	AT91_SAMA5D2_CHAN_SINGLE(2, 0x58),
	AT91_SAMA5D2_CHAN_SINGLE(3, 0x5c),
	AT91_SAMA5D2_CHAN_SINGLE(4, 0x60),
	AT91_SAMA5D2_CHAN_SINGLE(5, 0x64),
	AT91_SAMA5D2_CHAN_SINGLE(6, 0x68),
	AT91_SAMA5D2_CHAN_SINGLE(7, 0x6c),
	AT91_SAMA5D2_CHAN_SINGLE(8, 0x70),
	AT91_SAMA5D2_CHAN_SINGLE(9, 0x74),
	AT91_SAMA5D2_CHAN_SINGLE(10, 0x78),
	AT91_SAMA5D2_CHAN_SINGLE(11, 0x7c),
	AT91_SAMA5D2_CHAN_DIFF(0, 1, 0x50),
	AT91_SAMA5D2_CHAN_DIFF(2, 3, 0x58),
	AT91_SAMA5D2_CHAN_DIFF(4, 5, 0x60),
	AT91_SAMA5D2_CHAN_DIFF(6, 7, 0x68),
	AT91_SAMA5D2_CHAN_DIFF(8, 9, 0x70),
	AT91_SAMA5D2_CHAN_DIFF(10, 11, 0x78),
	IIO_CHAN_SOFT_TIMESTAMP(AT91_SAMA5D2_TIMESTAMP_CHAN_IDX),
	AT91_SAMA5D2_CHAN_TOUCH(AT91_SAMA5D2_TOUCH_X_CHAN_IDX, "x", IIO_MOD_X),
	AT91_SAMA5D2_CHAN_TOUCH(AT91_SAMA5D2_TOUCH_Y_CHAN_IDX, "y", IIO_MOD_Y),
	AT91_SAMA5D2_CHAN_PRESSURE(AT91_SAMA5D2_TOUCH_P_CHAN_IDX, "pressure"),
पूर्ण;

अटल पूर्णांक at91_adc_chan_xlate(काष्ठा iio_dev *indio_dev, पूर्णांक chan)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < indio_dev->num_channels; i++) अणु
		अगर (indio_dev->channels[i].scan_index == chan)
			वापस i;
	पूर्ण
	वापस -EINVAL;
पूर्ण

अटल अंतरभूत काष्ठा iio_chan_spec स्थिर *
at91_adc_chan_get(काष्ठा iio_dev *indio_dev, पूर्णांक chan)
अणु
	पूर्णांक index = at91_adc_chan_xlate(indio_dev, chan);

	अगर (index < 0)
		वापस शून्य;
	वापस indio_dev->channels + index;
पूर्ण

अटल अंतरभूत पूर्णांक at91_adc_of_xlate(काष्ठा iio_dev *indio_dev,
				    स्थिर काष्ठा of_phandle_args *iiospec)
अणु
	वापस at91_adc_chan_xlate(indio_dev, iiospec->args[0]);
पूर्ण

अटल अचिन्हित पूर्णांक at91_adc_active_scan_mask_to_reg(काष्ठा iio_dev *indio_dev)
अणु
	u32 mask = 0;
	u8 bit;

	क्रम_each_set_bit(bit, indio_dev->active_scan_mask,
			 indio_dev->num_channels) अणु
		काष्ठा iio_chan_spec स्थिर *chan =
			 at91_adc_chan_get(indio_dev, bit);
		mask |= BIT(chan->channel);
	पूर्ण

	वापस mask & GENMASK(11, 0);
पूर्ण

अटल व्योम at91_adc_config_emr(काष्ठा at91_adc_state *st)
अणु
	/* configure the extended mode रेजिस्टर */
	अचिन्हित पूर्णांक emr = at91_adc_पढ़ोl(st, AT91_SAMA5D2_EMR);

	/* select oversampling per single trigger event */
	emr |= AT91_SAMA5D2_EMR_ASTE(1);

	/* delete leftover content अगर it's the हाल */
	emr &= ~AT91_SAMA5D2_EMR_OSR_MASK;

	/* select oversampling ratio from configuration */
	चयन (st->oversampling_ratio) अणु
	हाल AT91_OSR_1SAMPLES:
		emr |= AT91_SAMA5D2_EMR_OSR(AT91_SAMA5D2_EMR_OSR_1SAMPLES) &
		       AT91_SAMA5D2_EMR_OSR_MASK;
		अवरोध;
	हाल AT91_OSR_4SAMPLES:
		emr |= AT91_SAMA5D2_EMR_OSR(AT91_SAMA5D2_EMR_OSR_4SAMPLES) &
		       AT91_SAMA5D2_EMR_OSR_MASK;
		अवरोध;
	हाल AT91_OSR_16SAMPLES:
		emr |= AT91_SAMA5D2_EMR_OSR(AT91_SAMA5D2_EMR_OSR_16SAMPLES) &
		       AT91_SAMA5D2_EMR_OSR_MASK;
		अवरोध;
	पूर्ण

	at91_adc_ग_लिखोl(st, AT91_SAMA5D2_EMR, emr);
पूर्ण

अटल पूर्णांक at91_adc_adjust_val_osr(काष्ठा at91_adc_state *st, पूर्णांक *val)
अणु
	अगर (st->oversampling_ratio == AT91_OSR_1SAMPLES) अणु
		/*
		 * in this हाल we only have 12 bits of real data, but channel
		 * is रेजिस्टरed as 14 bits, so shअगरt left two bits
		 */
		*val <<= 2;
	पूर्ण अन्यथा अगर (st->oversampling_ratio == AT91_OSR_4SAMPLES) अणु
		/*
		 * in this हाल we have 13 bits of real data, but channel
		 * is रेजिस्टरed as 14 bits, so left shअगरt one bit
		 */
		*val <<= 1;
	पूर्ण

	वापस IIO_VAL_INT;
पूर्ण

अटल व्योम at91_adc_adjust_val_osr_array(काष्ठा at91_adc_state *st, व्योम *buf,
					  पूर्णांक len)
अणु
	पूर्णांक i = 0, val;
	u16 *buf_u16 = (u16 *) buf;

	/*
	 * We are converting each two bytes (each sample).
	 * First convert the byte based array to u16, and convert each sample
	 * separately.
	 * Each value is two bytes in an array of अक्षरs, so to not shअगरt
	 * more than we need, save the value separately.
	 * len is in bytes, so भागide by two to get number of samples.
	 */
	जबतक (i < len / 2) अणु
		val = buf_u16[i];
		at91_adc_adjust_val_osr(st, &val);
		buf_u16[i] = val;
		i++;
	पूर्ण
पूर्ण

अटल पूर्णांक at91_adc_configure_touch(काष्ठा at91_adc_state *st, bool state)
अणु
	u32 clk_khz = st->current_sample_rate / 1000;
	पूर्णांक i = 0;
	u16 pendbc;
	u32 tsmr, acr;

	अगर (!state) अणु
		/* disabling touch IRQs and setting mode to no touch enabled */
		at91_adc_ग_लिखोl(st, AT91_SAMA5D2_IDR,
				AT91_SAMA5D2_IER_PEN | AT91_SAMA5D2_IER_NOPEN);
		at91_adc_ग_लिखोl(st, AT91_SAMA5D2_TSMR, 0);
		वापस 0;
	पूर्ण
	/*
	 * debounce समय is in microseconds, we need it in milliseconds to
	 * multiply with kilohertz, so, भागide by 1000, but after the multiply.
	 * round up to make sure pendbc is at least 1
	 */
	pendbc = round_up(AT91_SAMA5D2_TOUCH_PEN_DETECT_DEBOUNCE_US *
			  clk_khz / 1000, 1);

	/* get the required exponent */
	जबतक (pendbc >> i++)
		;

	pendbc = i;

	tsmr = AT91_SAMA5D2_TSMR_TSMODE_4WIRE_PRESS;

	tsmr |= AT91_SAMA5D2_TSMR_TSAV(2) & AT91_SAMA5D2_TSMR_TSAV_MASK;
	tsmr |= AT91_SAMA5D2_TSMR_PENDBC(pendbc) &
		AT91_SAMA5D2_TSMR_PENDBC_MASK;
	tsmr |= AT91_SAMA5D2_TSMR_NOTSDMA;
	tsmr |= AT91_SAMA5D2_TSMR_PENDET_ENA;
	tsmr |= AT91_SAMA5D2_TSMR_TSFREQ(2) & AT91_SAMA5D2_TSMR_TSFREQ_MASK;

	at91_adc_ग_लिखोl(st, AT91_SAMA5D2_TSMR, tsmr);

	acr =  at91_adc_पढ़ोl(st, AT91_SAMA5D2_ACR);
	acr &= ~AT91_SAMA5D2_ACR_PENDETSENS_MASK;
	acr |= 0x02 & AT91_SAMA5D2_ACR_PENDETSENS_MASK;
	at91_adc_ग_लिखोl(st, AT91_SAMA5D2_ACR, acr);

	/* Sample Period Time = (TRGPER + 1) / ADCClock */
	st->touch_st.sample_period_val =
				 round_up((AT91_SAMA5D2_TOUCH_SAMPLE_PERIOD_US *
				 clk_khz / 1000) - 1, 1);
	/* enable pen detect IRQ */
	at91_adc_ग_लिखोl(st, AT91_SAMA5D2_IER, AT91_SAMA5D2_IER_PEN);

	वापस 0;
पूर्ण

अटल u16 at91_adc_touch_pos(काष्ठा at91_adc_state *st, पूर्णांक reg)
अणु
	u32 val;
	u32 scale, result, pos;

	/*
	 * to obtain the actual position we must भागide by scale
	 * and multiply with max, where
	 * max = 2^AT91_SAMA5D2_MAX_POS_BITS - 1
	 */
	/* first half of रेजिस्टर is the x or y, second half is the scale */
	val = at91_adc_पढ़ोl(st, reg);
	अगर (!val)
		dev_dbg(&st->indio_dev->dev, "pos is 0\n");

	pos = val & AT91_SAMA5D2_XYZ_MASK;
	result = (pos << AT91_SAMA5D2_MAX_POS_BITS) - pos;
	scale = (val >> 16) & AT91_SAMA5D2_XYZ_MASK;
	अगर (scale == 0) अणु
		dev_err(&st->indio_dev->dev, "scale is 0\n");
		वापस 0;
	पूर्ण
	result /= scale;

	वापस result;
पूर्ण

अटल u16 at91_adc_touch_x_pos(काष्ठा at91_adc_state *st)
अणु
	st->touch_st.x_pos = at91_adc_touch_pos(st, AT91_SAMA5D2_XPOSR);
	वापस st->touch_st.x_pos;
पूर्ण

अटल u16 at91_adc_touch_y_pos(काष्ठा at91_adc_state *st)
अणु
	वापस at91_adc_touch_pos(st, AT91_SAMA5D2_YPOSR);
पूर्ण

अटल u16 at91_adc_touch_pressure(काष्ठा at91_adc_state *st)
अणु
	u32 val;
	u32 z1, z2;
	u32 pres;
	u32 rxp = 1;
	u32 factor = 1000;

	/* calculate the pressure */
	val = at91_adc_पढ़ोl(st, AT91_SAMA5D2_PRESSR);
	z1 = val & AT91_SAMA5D2_XYZ_MASK;
	z2 = (val >> 16) & AT91_SAMA5D2_XYZ_MASK;

	अगर (z1 != 0)
		pres = rxp * (st->touch_st.x_pos * factor / 1024) *
			(z2 * factor / z1 - factor) /
			factor;
	अन्यथा
		pres = 0xFFFF;       /* no pen contact */

	/*
	 * The pressure from device grows करोwn, minimum is 0xFFFF, maximum 0x0.
	 * We compute it this way, but let's वापस it in the expected way,
	 * growing from 0 to 0xFFFF.
	 */
	वापस 0xFFFF - pres;
पूर्ण

अटल पूर्णांक at91_adc_पढ़ो_position(काष्ठा at91_adc_state *st, पूर्णांक chan, u16 *val)
अणु
	*val = 0;
	अगर (!st->touch_st.touching)
		वापस -ENODATA;
	अगर (chan == AT91_SAMA5D2_TOUCH_X_CHAN_IDX)
		*val = at91_adc_touch_x_pos(st);
	अन्यथा अगर (chan == AT91_SAMA5D2_TOUCH_Y_CHAN_IDX)
		*val = at91_adc_touch_y_pos(st);
	अन्यथा
		वापस -ENODATA;

	वापस IIO_VAL_INT;
पूर्ण

अटल पूर्णांक at91_adc_पढ़ो_pressure(काष्ठा at91_adc_state *st, पूर्णांक chan, u16 *val)
अणु
	*val = 0;
	अगर (!st->touch_st.touching)
		वापस -ENODATA;
	अगर (chan == AT91_SAMA5D2_TOUCH_P_CHAN_IDX)
		*val = at91_adc_touch_pressure(st);
	अन्यथा
		वापस -ENODATA;

	वापस IIO_VAL_INT;
पूर्ण

अटल पूर्णांक at91_adc_configure_trigger(काष्ठा iio_trigger *trig, bool state)
अणु
	काष्ठा iio_dev *indio = iio_trigger_get_drvdata(trig);
	काष्ठा at91_adc_state *st = iio_priv(indio);
	u32 status = at91_adc_पढ़ोl(st, AT91_SAMA5D2_TRGR);

	/* clear TRGMOD */
	status &= ~AT91_SAMA5D2_TRGR_TRGMOD_MASK;

	अगर (state)
		status |= st->selected_trig->trgmod_value;

	/* set/unset hw trigger */
	at91_adc_ग_लिखोl(st, AT91_SAMA5D2_TRGR, status);

	वापस 0;
पूर्ण

अटल व्योम at91_adc_reenable_trigger(काष्ठा iio_trigger *trig)
अणु
	काष्ठा iio_dev *indio = iio_trigger_get_drvdata(trig);
	काष्ठा at91_adc_state *st = iio_priv(indio);

	/* अगर we are using DMA, we must not reenable irq after each trigger */
	अगर (st->dma_st.dma_chan)
		वापस;

	enable_irq(st->irq);

	/* Needed to ACK the DRDY पूर्णांकerruption */
	at91_adc_पढ़ोl(st, AT91_SAMA5D2_LCDR);
पूर्ण

अटल स्थिर काष्ठा iio_trigger_ops at91_adc_trigger_ops = अणु
	.set_trigger_state = &at91_adc_configure_trigger,
	.reenable = &at91_adc_reenable_trigger,
	.validate_device = iio_trigger_validate_own_device,
पूर्ण;

अटल पूर्णांक at91_adc_dma_size_करोne(काष्ठा at91_adc_state *st)
अणु
	काष्ठा dma_tx_state state;
	क्रमागत dma_status status;
	पूर्णांक i, size;

	status = dmaengine_tx_status(st->dma_st.dma_chan,
				     st->dma_st.dma_chan->cookie,
				     &state);
	अगर (status != DMA_IN_PROGRESS)
		वापस 0;

	/* Transferred length is size in bytes from end of buffer */
	i = st->dma_st.rx_buf_sz - state.residue;

	/* Return available bytes */
	अगर (i >= st->dma_st.buf_idx)
		size = i - st->dma_st.buf_idx;
	अन्यथा
		size = st->dma_st.rx_buf_sz + i - st->dma_st.buf_idx;
	वापस size;
पूर्ण

अटल व्योम at91_dma_buffer_करोne(व्योम *data)
अणु
	काष्ठा iio_dev *indio_dev = data;

	iio_trigger_poll_chained(indio_dev->trig);
पूर्ण

अटल पूर्णांक at91_adc_dma_start(काष्ठा iio_dev *indio_dev)
अणु
	काष्ठा at91_adc_state *st = iio_priv(indio_dev);
	काष्ठा dma_async_tx_descriptor *desc;
	dma_cookie_t cookie;
	पूर्णांक ret;
	u8 bit;

	अगर (!st->dma_st.dma_chan)
		वापस 0;

	/* we start a new DMA, so set buffer index to start */
	st->dma_st.buf_idx = 0;

	/*
	 * compute buffer size w.r.t. watermark and enabled channels.
	 * scan_bytes is aligned so we need an exact size क्रम DMA
	 */
	st->dma_st.rx_buf_sz = 0;

	क्रम_each_set_bit(bit, indio_dev->active_scan_mask,
			 indio_dev->num_channels) अणु
		काष्ठा iio_chan_spec स्थिर *chan =
					 at91_adc_chan_get(indio_dev, bit);

		अगर (!chan)
			जारी;

		st->dma_st.rx_buf_sz += chan->scan_type.storagebits / 8;
	पूर्ण
	st->dma_st.rx_buf_sz *= st->dma_st.watermark;

	/* Prepare a DMA cyclic transaction */
	desc = dmaengine_prep_dma_cyclic(st->dma_st.dma_chan,
					 st->dma_st.rx_dma_buf,
					 st->dma_st.rx_buf_sz,
					 st->dma_st.rx_buf_sz / 2,
					 DMA_DEV_TO_MEM, DMA_PREP_INTERRUPT);

	अगर (!desc) अणु
		dev_err(&indio_dev->dev, "cannot prepare DMA cyclic\n");
		वापस -EBUSY;
	पूर्ण

	desc->callback = at91_dma_buffer_करोne;
	desc->callback_param = indio_dev;

	cookie = dmaengine_submit(desc);
	ret = dma_submit_error(cookie);
	अगर (ret) अणु
		dev_err(&indio_dev->dev, "cannot submit DMA cyclic\n");
		dmaengine_terminate_async(st->dma_st.dma_chan);
		वापस ret;
	पूर्ण

	/* enable general overrun error संकेतing */
	at91_adc_ग_लिखोl(st, AT91_SAMA5D2_IER, AT91_SAMA5D2_IER_GOVRE);
	/* Issue pending DMA requests */
	dma_async_issue_pending(st->dma_st.dma_chan);

	/* consider current समय as DMA start समय क्रम बारtamps */
	st->dma_st.dma_ts = iio_get_समय_ns(indio_dev);

	dev_dbg(&indio_dev->dev, "DMA cyclic started\n");

	वापस 0;
पूर्ण

अटल bool at91_adc_buffer_check_use_irq(काष्ठा iio_dev *indio,
					  काष्ठा at91_adc_state *st)
अणु
	/* अगर using DMA, we करो not use our own IRQ (we use DMA-controller) */
	अगर (st->dma_st.dma_chan)
		वापस false;
	/* अगर the trigger is not ours, then it has its own IRQ */
	अगर (iio_trigger_validate_own_device(indio->trig, indio))
		वापस false;
	वापस true;
पूर्ण

अटल bool at91_adc_current_chan_is_touch(काष्ठा iio_dev *indio_dev)
अणु
	काष्ठा at91_adc_state *st = iio_priv(indio_dev);

	वापस !!biपंचांगap_subset(indio_dev->active_scan_mask,
			       &st->touch_st.channels_biपंचांगask,
			       AT91_SAMA5D2_MAX_CHAN_IDX + 1);
पूर्ण

अटल पूर्णांक at91_adc_buffer_prepare(काष्ठा iio_dev *indio_dev)
अणु
	पूर्णांक ret;
	u8 bit;
	काष्ठा at91_adc_state *st = iio_priv(indio_dev);

	/* check अगर we are enabling triggered buffer or the touchscreen */
	अगर (at91_adc_current_chan_is_touch(indio_dev))
		वापस at91_adc_configure_touch(st, true);

	/* अगर we are not in triggered mode, we cannot enable the buffer. */
	अगर (!(indio_dev->currenपंचांगode & INDIO_ALL_TRIGGERED_MODES))
		वापस -EINVAL;

	/* we जारी with the triggered buffer */
	ret = at91_adc_dma_start(indio_dev);
	अगर (ret) अणु
		dev_err(&indio_dev->dev, "buffer prepare failed\n");
		वापस ret;
	पूर्ण

	क्रम_each_set_bit(bit, indio_dev->active_scan_mask,
			 indio_dev->num_channels) अणु
		काष्ठा iio_chan_spec स्थिर *chan =
					at91_adc_chan_get(indio_dev, bit);
		u32 cor;

		अगर (!chan)
			जारी;
		/* these channel types cannot be handled by this trigger */
		अगर (chan->type == IIO_POSITIONRELATIVE ||
		    chan->type == IIO_PRESSURE)
			जारी;

		cor = at91_adc_पढ़ोl(st, AT91_SAMA5D2_COR);

		अगर (chan->dअगरferential)
			cor |= (BIT(chan->channel) | BIT(chan->channel2)) <<
				AT91_SAMA5D2_COR_DIFF_OFFSET;
		अन्यथा
			cor &= ~(BIT(chan->channel) <<
			       AT91_SAMA5D2_COR_DIFF_OFFSET);

		at91_adc_ग_लिखोl(st, AT91_SAMA5D2_COR, cor);

		at91_adc_ग_लिखोl(st, AT91_SAMA5D2_CHER, BIT(chan->channel));
	पूर्ण

	अगर (at91_adc_buffer_check_use_irq(indio_dev, st))
		at91_adc_ग_लिखोl(st, AT91_SAMA5D2_IER, AT91_SAMA5D2_IER_DRDY);

	वापस 0;
पूर्ण

अटल पूर्णांक at91_adc_buffer_postdisable(काष्ठा iio_dev *indio_dev)
अणु
	काष्ठा at91_adc_state *st = iio_priv(indio_dev);
	u8 bit;

	/* check अगर we are disabling triggered buffer or the touchscreen */
	अगर (at91_adc_current_chan_is_touch(indio_dev))
		वापस at91_adc_configure_touch(st, false);

	/* अगर we are not in triggered mode, nothing to करो here */
	अगर (!(indio_dev->currenपंचांगode & INDIO_ALL_TRIGGERED_MODES))
		वापस -EINVAL;

	/*
	 * For each enable channel we must disable it in hardware.
	 * In the हाल of DMA, we must पढ़ो the last converted value
	 * to clear EOC status and not get a possible पूर्णांकerrupt later.
	 * This value is being पढ़ो by DMA from LCDR anyway, so it's not lost.
	 */
	क्रम_each_set_bit(bit, indio_dev->active_scan_mask,
			 indio_dev->num_channels) अणु
		काष्ठा iio_chan_spec स्थिर *chan =
					at91_adc_chan_get(indio_dev, bit);

		अगर (!chan)
			जारी;
		/* these channel types are भव, no need to करो anything */
		अगर (chan->type == IIO_POSITIONRELATIVE ||
		    chan->type == IIO_PRESSURE)
			जारी;

		at91_adc_ग_लिखोl(st, AT91_SAMA5D2_CHDR, BIT(chan->channel));

		अगर (st->dma_st.dma_chan)
			at91_adc_पढ़ोl(st, chan->address);
	पूर्ण

	अगर (at91_adc_buffer_check_use_irq(indio_dev, st))
		at91_adc_ग_लिखोl(st, AT91_SAMA5D2_IDR, AT91_SAMA5D2_IER_DRDY);

	/* पढ़ो overflow रेजिस्टर to clear possible overflow status */
	at91_adc_पढ़ोl(st, AT91_SAMA5D2_OVER);

	/* अगर we are using DMA we must clear रेजिस्टरs and end DMA */
	अगर (st->dma_st.dma_chan)
		dmaengine_terminate_sync(st->dma_st.dma_chan);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा iio_buffer_setup_ops at91_buffer_setup_ops = अणु
	.postdisable = &at91_adc_buffer_postdisable,
पूर्ण;

अटल काष्ठा iio_trigger *at91_adc_allocate_trigger(काष्ठा iio_dev *indio,
						     अक्षर *trigger_name)
अणु
	काष्ठा iio_trigger *trig;
	पूर्णांक ret;

	trig = devm_iio_trigger_alloc(&indio->dev, "%s-dev%d-%s", indio->name,
				      indio->id, trigger_name);
	अगर (!trig)
		वापस शून्य;

	trig->dev.parent = indio->dev.parent;
	iio_trigger_set_drvdata(trig, indio);
	trig->ops = &at91_adc_trigger_ops;

	ret = devm_iio_trigger_रेजिस्टर(&indio->dev, trig);
	अगर (ret)
		वापस ERR_PTR(ret);

	वापस trig;
पूर्ण
अटल व्योम at91_adc_trigger_handler_nodma(काष्ठा iio_dev *indio_dev,
					   काष्ठा iio_poll_func *pf)
अणु
	काष्ठा at91_adc_state *st = iio_priv(indio_dev);
	पूर्णांक i = 0;
	पूर्णांक val;
	u8 bit;
	u32 mask = at91_adc_active_scan_mask_to_reg(indio_dev);
	अचिन्हित पूर्णांक समयout = 50;

	/*
	 * Check अगर the conversion is पढ़ोy. If not, रुको a little bit, and
	 * in हाल of समयout निकास with an error.
	 */
	जबतक ((at91_adc_पढ़ोl(st, AT91_SAMA5D2_ISR) & mask) != mask &&
	       समयout) अणु
		usleep_range(50, 100);
		समयout--;
	पूर्ण

	/* Cannot पढ़ो data, not पढ़ोy. Continue without reporting data */
	अगर (!समयout)
		वापस;

	क्रम_each_set_bit(bit, indio_dev->active_scan_mask,
			 indio_dev->num_channels) अणु
		काष्ठा iio_chan_spec स्थिर *chan =
					at91_adc_chan_get(indio_dev, bit);

		अगर (!chan)
			जारी;
		/*
		 * Our बाह्यal trigger only supports the voltage channels.
		 * In हाल someone requested a dअगरferent type of channel
		 * just put zeroes to buffer.
		 * This should not happen because we check the scan mode
		 * and scan mask when we enable the buffer, and we करोn't allow
		 * the buffer to start with a mixed mask (voltage and something
		 * अन्यथा).
		 * Thus, emit a warning.
		 */
		अगर (chan->type == IIO_VOLTAGE) अणु
			val = at91_adc_पढ़ोl(st, chan->address);
			at91_adc_adjust_val_osr(st, &val);
			st->buffer[i] = val;
		पूर्ण अन्यथा अणु
			st->buffer[i] = 0;
			WARN(true, "This trigger cannot handle this type of channel");
		पूर्ण
		i++;
	पूर्ण
	iio_push_to_buffers_with_बारtamp(indio_dev, st->buffer,
					   pf->बारtamp);
पूर्ण

अटल व्योम at91_adc_trigger_handler_dma(काष्ठा iio_dev *indio_dev)
अणु
	काष्ठा at91_adc_state *st = iio_priv(indio_dev);
	पूर्णांक transferred_len = at91_adc_dma_size_करोne(st);
	s64 ns = iio_get_समय_ns(indio_dev);
	s64 पूर्णांकerval;
	पूर्णांक sample_index = 0, sample_count, sample_size;

	u32 status = at91_adc_पढ़ोl(st, AT91_SAMA5D2_ISR);
	/* अगर we reached this poपूर्णांक, we cannot sample faster */
	अगर (status & AT91_SAMA5D2_IER_GOVRE)
		pr_info_ratelimited("%s: conversion overrun detected\n",
				    indio_dev->name);

	sample_size = भाग_s64(st->dma_st.rx_buf_sz, st->dma_st.watermark);

	sample_count = भाग_s64(transferred_len, sample_size);

	/*
	 * पूर्णांकerval between samples is total समय since last transfer handling
	 * भागided by the number of samples (total size भागided by sample size)
	 */
	पूर्णांकerval = भाग_s64((ns - st->dma_st.dma_ts), sample_count);

	जबतक (transferred_len >= sample_size) अणु
		/*
		 * क्रम all the values in the current sample,
		 * adjust the values inside the buffer क्रम oversampling
		 */
		at91_adc_adjust_val_osr_array(st,
					&st->dma_st.rx_buf[st->dma_st.buf_idx],
					sample_size);

		iio_push_to_buffers_with_बारtamp(indio_dev,
				(st->dma_st.rx_buf + st->dma_st.buf_idx),
				(st->dma_st.dma_ts + पूर्णांकerval * sample_index));
		/* adjust reमुख्यing length */
		transferred_len -= sample_size;
		/* adjust buffer index */
		st->dma_st.buf_idx += sample_size;
		/* in हाल of reaching end of buffer, reset index */
		अगर (st->dma_st.buf_idx >= st->dma_st.rx_buf_sz)
			st->dma_st.buf_idx = 0;
		sample_index++;
	पूर्ण
	/* adjust saved समय क्रम next transfer handling */
	st->dma_st.dma_ts = iio_get_समय_ns(indio_dev);
पूर्ण

अटल irqवापस_t at91_adc_trigger_handler(पूर्णांक irq, व्योम *p)
अणु
	काष्ठा iio_poll_func *pf = p;
	काष्ठा iio_dev *indio_dev = pf->indio_dev;
	काष्ठा at91_adc_state *st = iio_priv(indio_dev);

	/*
	 * If it's not our trigger, start a conversion now, as we are
	 * actually polling the trigger now.
	 */
	अगर (iio_trigger_validate_own_device(indio_dev->trig, indio_dev))
		at91_adc_ग_लिखोl(st, AT91_SAMA5D2_CR, AT91_SAMA5D2_CR_START);

	अगर (st->dma_st.dma_chan)
		at91_adc_trigger_handler_dma(indio_dev);
	अन्यथा
		at91_adc_trigger_handler_nodma(indio_dev, pf);

	iio_trigger_notअगरy_करोne(indio_dev->trig);

	वापस IRQ_HANDLED;
पूर्ण

अटल अचिन्हित at91_adc_startup_समय(अचिन्हित startup_समय_min,
				      अचिन्हित adc_clk_khz)
अणु
	अटल स्थिर अचिन्हित पूर्णांक startup_lookup[] = अणु
		  0,   8,  16,  24,
		 64,  80,  96, 112,
		512, 576, 640, 704,
		768, 832, 896, 960
		पूर्ण;
	अचिन्हित ticks_min, i;

	/*
	 * Since the adc frequency is checked beक्रमe, there is no reason
	 * to not meet the startup समय स्थिरraपूर्णांक.
	 */

	ticks_min = startup_समय_min * adc_clk_khz / 1000;
	क्रम (i = 0; i < ARRAY_SIZE(startup_lookup); i++)
		अगर (startup_lookup[i] > ticks_min)
			अवरोध;

	वापस i;
पूर्ण

अटल व्योम at91_adc_setup_samp_freq(काष्ठा iio_dev *indio_dev, अचिन्हित freq)
अणु
	काष्ठा at91_adc_state *st = iio_priv(indio_dev);
	अचिन्हित f_per, prescal, startup, mr;

	f_per = clk_get_rate(st->per_clk);
	prescal = (f_per / (2 * freq)) - 1;

	startup = at91_adc_startup_समय(st->soc_info.startup_समय,
					freq / 1000);

	mr = at91_adc_पढ़ोl(st, AT91_SAMA5D2_MR);
	mr &= ~(AT91_SAMA5D2_MR_STARTUP_MASK | AT91_SAMA5D2_MR_PRESCAL_MASK);
	mr |= AT91_SAMA5D2_MR_STARTUP(startup);
	mr |= AT91_SAMA5D2_MR_PRESCAL(prescal);
	at91_adc_ग_लिखोl(st, AT91_SAMA5D2_MR, mr);

	dev_dbg(&indio_dev->dev, "freq: %u, startup: %u, prescal: %u\n",
		freq, startup, prescal);
	st->current_sample_rate = freq;
पूर्ण

अटल अंतरभूत अचिन्हित at91_adc_get_sample_freq(काष्ठा at91_adc_state *st)
अणु
	वापस st->current_sample_rate;
पूर्ण

अटल व्योम at91_adc_touch_data_handler(काष्ठा iio_dev *indio_dev)
अणु
	काष्ठा at91_adc_state *st = iio_priv(indio_dev);
	u8 bit;
	u16 val;
	पूर्णांक i = 0;

	क्रम_each_set_bit(bit, indio_dev->active_scan_mask,
			 AT91_SAMA5D2_MAX_CHAN_IDX + 1) अणु
		काष्ठा iio_chan_spec स्थिर *chan =
					 at91_adc_chan_get(indio_dev, bit);

		अगर (chan->type == IIO_POSITIONRELATIVE)
			at91_adc_पढ़ो_position(st, chan->channel, &val);
		अन्यथा अगर (chan->type == IIO_PRESSURE)
			at91_adc_पढ़ो_pressure(st, chan->channel, &val);
		अन्यथा
			जारी;
		st->buffer[i] = val;
		i++;
	पूर्ण
	/*
	 * Schedule work to push to buffers.
	 * This is पूर्णांकended to push to the callback buffer that another driver
	 * रेजिस्टरed. We are still in a handler from our IRQ. If we push
	 * directly, it means the other driver has it's callback called
	 * from our IRQ context. Which is something we better aव्योम.
	 * Let's schedule it after our IRQ is completed.
	 */
	schedule_work(&st->touch_st.workq);
पूर्ण

अटल व्योम at91_adc_pen_detect_पूर्णांकerrupt(काष्ठा at91_adc_state *st)
अणु
	at91_adc_ग_लिखोl(st, AT91_SAMA5D2_IDR, AT91_SAMA5D2_IER_PEN);
	at91_adc_ग_लिखोl(st, AT91_SAMA5D2_IER, AT91_SAMA5D2_IER_NOPEN |
			AT91_SAMA5D2_IER_XRDY | AT91_SAMA5D2_IER_YRDY |
			AT91_SAMA5D2_IER_PRDY);
	at91_adc_ग_लिखोl(st, AT91_SAMA5D2_TRGR,
			AT91_SAMA5D2_TRGR_TRGMOD_PERIODIC |
			AT91_SAMA5D2_TRGR_TRGPER(st->touch_st.sample_period_val));
	st->touch_st.touching = true;
पूर्ण

अटल व्योम at91_adc_no_pen_detect_पूर्णांकerrupt(काष्ठा iio_dev *indio_dev)
अणु
	काष्ठा at91_adc_state *st = iio_priv(indio_dev);

	at91_adc_ग_लिखोl(st, AT91_SAMA5D2_TRGR,
			AT91_SAMA5D2_TRGR_TRGMOD_NO_TRIGGER);
	at91_adc_ग_लिखोl(st, AT91_SAMA5D2_IDR, AT91_SAMA5D2_IER_NOPEN |
			AT91_SAMA5D2_IER_XRDY | AT91_SAMA5D2_IER_YRDY |
			AT91_SAMA5D2_IER_PRDY);
	st->touch_st.touching = false;

	at91_adc_touch_data_handler(indio_dev);

	at91_adc_ग_लिखोl(st, AT91_SAMA5D2_IER, AT91_SAMA5D2_IER_PEN);
पूर्ण

अटल व्योम at91_adc_workq_handler(काष्ठा work_काष्ठा *workq)
अणु
	काष्ठा at91_adc_touch *touch_st = container_of(workq,
					काष्ठा at91_adc_touch, workq);
	काष्ठा at91_adc_state *st = container_of(touch_st,
					काष्ठा at91_adc_state, touch_st);
	काष्ठा iio_dev *indio_dev = st->indio_dev;

	iio_push_to_buffers(indio_dev, st->buffer);
पूर्ण

अटल irqवापस_t at91_adc_पूर्णांकerrupt(पूर्णांक irq, व्योम *निजी)
अणु
	काष्ठा iio_dev *indio = निजी;
	काष्ठा at91_adc_state *st = iio_priv(indio);
	u32 status = at91_adc_पढ़ोl(st, AT91_SAMA5D2_ISR);
	u32 imr = at91_adc_पढ़ोl(st, AT91_SAMA5D2_IMR);
	u32 rdy_mask = AT91_SAMA5D2_IER_XRDY | AT91_SAMA5D2_IER_YRDY |
			AT91_SAMA5D2_IER_PRDY;

	अगर (!(status & imr))
		वापस IRQ_NONE;
	अगर (status & AT91_SAMA5D2_IER_PEN) अणु
		/* pen detected IRQ */
		at91_adc_pen_detect_पूर्णांकerrupt(st);
	पूर्ण अन्यथा अगर ((status & AT91_SAMA5D2_IER_NOPEN)) अणु
		/* nखोलो detected IRQ */
		at91_adc_no_pen_detect_पूर्णांकerrupt(indio);
	पूर्ण अन्यथा अगर ((status & AT91_SAMA5D2_ISR_PENS) &&
		   ((status & rdy_mask) == rdy_mask)) अणु
		/* periodic trigger IRQ - during pen sense */
		at91_adc_touch_data_handler(indio);
	पूर्ण अन्यथा अगर (status & AT91_SAMA5D2_ISR_PENS) अणु
		/*
		 * touching, but the measurements are not पढ़ोy yet.
		 * पढ़ो and ignore.
		 */
		status = at91_adc_पढ़ोl(st, AT91_SAMA5D2_XPOSR);
		status = at91_adc_पढ़ोl(st, AT91_SAMA5D2_YPOSR);
		status = at91_adc_पढ़ोl(st, AT91_SAMA5D2_PRESSR);
	पूर्ण अन्यथा अगर (iio_buffer_enabled(indio) &&
		   (status & AT91_SAMA5D2_IER_DRDY)) अणु
		/* triggered buffer without DMA */
		disable_irq_nosync(irq);
		iio_trigger_poll(indio->trig);
	पूर्ण अन्यथा अगर (iio_buffer_enabled(indio) && st->dma_st.dma_chan) अणु
		/* triggered buffer with DMA - should not happen */
		disable_irq_nosync(irq);
		WARN(true, "Unexpected irq occurred\n");
	पूर्ण अन्यथा अगर (!iio_buffer_enabled(indio)) अणु
		/* software requested conversion */
		st->conversion_value = at91_adc_पढ़ोl(st, st->chan->address);
		st->conversion_करोne = true;
		wake_up_पूर्णांकerruptible(&st->wq_data_available);
	पूर्ण
	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक at91_adc_पढ़ो_info_raw(काष्ठा iio_dev *indio_dev,
				  काष्ठा iio_chan_spec स्थिर *chan, पूर्णांक *val)
अणु
	काष्ठा at91_adc_state *st = iio_priv(indio_dev);
	u32 cor = 0;
	u16 पंचांगp_val;
	पूर्णांक ret;

	/*
	 * Keep in mind that we cannot use software trigger or touchscreen
	 * अगर बाह्यal trigger is enabled
	 */
	अगर (chan->type == IIO_POSITIONRELATIVE) अणु
		ret = iio_device_claim_direct_mode(indio_dev);
		अगर (ret)
			वापस ret;
		mutex_lock(&st->lock);

		ret = at91_adc_पढ़ो_position(st, chan->channel,
					     &पंचांगp_val);
		*val = पंचांगp_val;
		mutex_unlock(&st->lock);
		iio_device_release_direct_mode(indio_dev);

		वापस at91_adc_adjust_val_osr(st, val);
	पूर्ण
	अगर (chan->type == IIO_PRESSURE) अणु
		ret = iio_device_claim_direct_mode(indio_dev);
		अगर (ret)
			वापस ret;
		mutex_lock(&st->lock);

		ret = at91_adc_पढ़ो_pressure(st, chan->channel,
					     &पंचांगp_val);
		*val = पंचांगp_val;
		mutex_unlock(&st->lock);
		iio_device_release_direct_mode(indio_dev);

		वापस at91_adc_adjust_val_osr(st, val);
	पूर्ण

	/* in this हाल we have a voltage channel */

	ret = iio_device_claim_direct_mode(indio_dev);
	अगर (ret)
		वापस ret;
	mutex_lock(&st->lock);

	st->chan = chan;

	अगर (chan->dअगरferential)
		cor = (BIT(chan->channel) | BIT(chan->channel2)) <<
		      AT91_SAMA5D2_COR_DIFF_OFFSET;

	at91_adc_ग_लिखोl(st, AT91_SAMA5D2_COR, cor);
	at91_adc_ग_लिखोl(st, AT91_SAMA5D2_CHER, BIT(chan->channel));
	at91_adc_ग_लिखोl(st, AT91_SAMA5D2_IER, BIT(chan->channel));
	at91_adc_ग_लिखोl(st, AT91_SAMA5D2_CR, AT91_SAMA5D2_CR_START);

	ret = रुको_event_पूर्णांकerruptible_समयout(st->wq_data_available,
					       st->conversion_करोne,
					       msecs_to_jअगरfies(1000));
	अगर (ret == 0)
		ret = -ETIMEDOUT;

	अगर (ret > 0) अणु
		*val = st->conversion_value;
		ret = at91_adc_adjust_val_osr(st, val);
		अगर (chan->scan_type.sign == 's')
			*val = sign_extend32(*val, 11);
		st->conversion_करोne = false;
	पूर्ण

	at91_adc_ग_लिखोl(st, AT91_SAMA5D2_IDR, BIT(chan->channel));
	at91_adc_ग_लिखोl(st, AT91_SAMA5D2_CHDR, BIT(chan->channel));

	/* Needed to ACK the DRDY पूर्णांकerruption */
	at91_adc_पढ़ोl(st, AT91_SAMA5D2_LCDR);

	mutex_unlock(&st->lock);

	iio_device_release_direct_mode(indio_dev);
	वापस ret;
पूर्ण

अटल पूर्णांक at91_adc_पढ़ो_raw(काष्ठा iio_dev *indio_dev,
			     काष्ठा iio_chan_spec स्थिर *chan,
			     पूर्णांक *val, पूर्णांक *val2, दीर्घ mask)
अणु
	काष्ठा at91_adc_state *st = iio_priv(indio_dev);

	चयन (mask) अणु
	हाल IIO_CHAN_INFO_RAW:
		वापस at91_adc_पढ़ो_info_raw(indio_dev, chan, val);
	हाल IIO_CHAN_INFO_SCALE:
		*val = st->vref_uv / 1000;
		अगर (chan->dअगरferential)
			*val *= 2;
		*val2 = chan->scan_type.realbits;
		वापस IIO_VAL_FRACTIONAL_LOG2;

	हाल IIO_CHAN_INFO_SAMP_FREQ:
		*val = at91_adc_get_sample_freq(st);
		वापस IIO_VAL_INT;

	हाल IIO_CHAN_INFO_OVERSAMPLING_RATIO:
		*val = st->oversampling_ratio;
		वापस IIO_VAL_INT;

	शेष:
		वापस -EINVAL;
	पूर्ण
पूर्ण

अटल पूर्णांक at91_adc_ग_लिखो_raw(काष्ठा iio_dev *indio_dev,
			      काष्ठा iio_chan_spec स्थिर *chan,
			      पूर्णांक val, पूर्णांक val2, दीर्घ mask)
अणु
	काष्ठा at91_adc_state *st = iio_priv(indio_dev);

	चयन (mask) अणु
	हाल IIO_CHAN_INFO_OVERSAMPLING_RATIO:
		अगर ((val != AT91_OSR_1SAMPLES) && (val != AT91_OSR_4SAMPLES) &&
		    (val != AT91_OSR_16SAMPLES))
			वापस -EINVAL;
		/* अगर no change, optimize out */
		अगर (val == st->oversampling_ratio)
			वापस 0;
		st->oversampling_ratio = val;
		/* update ratio */
		at91_adc_config_emr(st);
		वापस 0;
	हाल IIO_CHAN_INFO_SAMP_FREQ:
		अगर (val < st->soc_info.min_sample_rate ||
		    val > st->soc_info.max_sample_rate)
			वापस -EINVAL;

		at91_adc_setup_samp_freq(indio_dev, val);
		वापस 0;
	शेष:
		वापस -EINVAL;
	पूर्ण
पूर्ण

अटल व्योम at91_adc_dma_init(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा iio_dev *indio_dev = platक्रमm_get_drvdata(pdev);
	काष्ठा at91_adc_state *st = iio_priv(indio_dev);
	काष्ठा dma_slave_config config = अणु0पूर्ण;
	/*
	 * We make the buffer द्विगुन the size of the fअगरo,
	 * such that DMA uses one half of the buffer (full fअगरo size)
	 * and the software uses the other half to पढ़ो/ग_लिखो.
	 */
	अचिन्हित पूर्णांक pages = DIV_ROUND_UP(AT91_HWFIFO_MAX_SIZE *
					  AT91_BUFFER_MAX_CONVERSION_BYTES * 2,
					  PAGE_SIZE);

	अगर (st->dma_st.dma_chan)
		वापस;

	st->dma_st.dma_chan = dma_request_chan(&pdev->dev, "rx");
	अगर (IS_ERR(st->dma_st.dma_chan))  अणु
		dev_info(&pdev->dev, "can't get DMA channel\n");
		st->dma_st.dma_chan = शून्य;
		जाओ dma_निकास;
	पूर्ण

	st->dma_st.rx_buf = dma_alloc_coherent(st->dma_st.dma_chan->device->dev,
					       pages * PAGE_SIZE,
					       &st->dma_st.rx_dma_buf,
					       GFP_KERNEL);
	अगर (!st->dma_st.rx_buf) अणु
		dev_info(&pdev->dev, "can't allocate coherent DMA area\n");
		जाओ dma_chan_disable;
	पूर्ण

	/* Configure DMA channel to पढ़ो data रेजिस्टर */
	config.direction = DMA_DEV_TO_MEM;
	config.src_addr = (phys_addr_t)(st->dma_st.phys_addr
			  + AT91_SAMA5D2_LCDR);
	config.src_addr_width = DMA_SLAVE_BUSWIDTH_2_BYTES;
	config.src_maxburst = 1;
	config.dst_maxburst = 1;

	अगर (dmaengine_slave_config(st->dma_st.dma_chan, &config)) अणु
		dev_info(&pdev->dev, "can't configure DMA slave\n");
		जाओ dma_मुक्त_area;
	पूर्ण

	dev_info(&pdev->dev, "using %s for rx DMA transfers\n",
		 dma_chan_name(st->dma_st.dma_chan));

	वापस;

dma_मुक्त_area:
	dma_मुक्त_coherent(st->dma_st.dma_chan->device->dev, pages * PAGE_SIZE,
			  st->dma_st.rx_buf, st->dma_st.rx_dma_buf);
dma_chan_disable:
	dma_release_channel(st->dma_st.dma_chan);
	st->dma_st.dma_chan = शून्य;
dma_निकास:
	dev_info(&pdev->dev, "continuing without DMA support\n");
पूर्ण

अटल व्योम at91_adc_dma_disable(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा iio_dev *indio_dev = platक्रमm_get_drvdata(pdev);
	काष्ठा at91_adc_state *st = iio_priv(indio_dev);
	अचिन्हित पूर्णांक pages = DIV_ROUND_UP(AT91_HWFIFO_MAX_SIZE *
					  AT91_BUFFER_MAX_CONVERSION_BYTES * 2,
					  PAGE_SIZE);

	/* अगर we are not using DMA, just वापस */
	अगर (!st->dma_st.dma_chan)
		वापस;

	/* रुको क्रम all transactions to be terminated first*/
	dmaengine_terminate_sync(st->dma_st.dma_chan);

	dma_मुक्त_coherent(st->dma_st.dma_chan->device->dev, pages * PAGE_SIZE,
			  st->dma_st.rx_buf, st->dma_st.rx_dma_buf);
	dma_release_channel(st->dma_st.dma_chan);
	st->dma_st.dma_chan = शून्य;

	dev_info(&pdev->dev, "continuing without DMA support\n");
पूर्ण

अटल पूर्णांक at91_adc_set_watermark(काष्ठा iio_dev *indio_dev, अचिन्हित पूर्णांक val)
अणु
	काष्ठा at91_adc_state *st = iio_priv(indio_dev);
	पूर्णांक ret;

	अगर (val > AT91_HWFIFO_MAX_SIZE)
		वापस -EINVAL;

	अगर (!st->selected_trig->hw_trig) अणु
		dev_dbg(&indio_dev->dev, "we need hw trigger for DMA\n");
		वापस 0;
	पूर्ण

	dev_dbg(&indio_dev->dev, "new watermark is %u\n", val);
	st->dma_st.watermark = val;

	/*
	 * The logic here is: अगर we have watermark 1, it means we करो
	 * each conversion with it's own IRQ, thus we don't need DMA.
	 * If the watermark is higher, we करो DMA to करो all the transfers in bulk
	 */

	अगर (val == 1)
		at91_adc_dma_disable(to_platक्रमm_device(&indio_dev->dev));
	अन्यथा अगर (val > 1)
		at91_adc_dma_init(to_platक्रमm_device(&indio_dev->dev));

	/*
	 * We can start the DMA only after setting the watermark and
	 * having the DMA initialization completed
	 */
	ret = at91_adc_buffer_prepare(indio_dev);
	अगर (ret)
		at91_adc_dma_disable(to_platक्रमm_device(&indio_dev->dev));

	वापस ret;
पूर्ण

अटल पूर्णांक at91_adc_update_scan_mode(काष्ठा iio_dev *indio_dev,
				     स्थिर अचिन्हित दीर्घ *scan_mask)
अणु
	काष्ठा at91_adc_state *st = iio_priv(indio_dev);

	अगर (biपंचांगap_subset(scan_mask, &st->touch_st.channels_biपंचांगask,
			  AT91_SAMA5D2_MAX_CHAN_IDX + 1))
		वापस 0;
	/*
	 * अगर the new biपंचांगap is a combination of touchscreen and regular
	 * channels, then we are not fine
	 */
	अगर (biपंचांगap_पूर्णांकersects(&st->touch_st.channels_biपंचांगask, scan_mask,
			      AT91_SAMA5D2_MAX_CHAN_IDX + 1))
		वापस -EINVAL;
	वापस 0;
पूर्ण

अटल व्योम at91_adc_hw_init(काष्ठा iio_dev *indio_dev)
अणु
	काष्ठा at91_adc_state *st = iio_priv(indio_dev);

	at91_adc_ग_लिखोl(st, AT91_SAMA5D2_CR, AT91_SAMA5D2_CR_SWRST);
	at91_adc_ग_लिखोl(st, AT91_SAMA5D2_IDR, 0xffffffff);
	/*
	 * Transfer field must be set to 2 according to the datasheet and
	 * allows dअगरferent analog settings क्रम each channel.
	 */
	at91_adc_ग_लिखोl(st, AT91_SAMA5D2_MR,
			AT91_SAMA5D2_MR_TRANSFER(2) | AT91_SAMA5D2_MR_ANACH);

	at91_adc_setup_samp_freq(indio_dev, st->soc_info.min_sample_rate);

	/* configure extended mode रेजिस्टर */
	at91_adc_config_emr(st);
पूर्ण

अटल sमाप_प्रकार at91_adc_get_fअगरo_state(काष्ठा device *dev,
				       काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा iio_dev *indio_dev = dev_get_drvdata(dev);
	काष्ठा at91_adc_state *st = iio_priv(indio_dev);

	वापस scnम_लिखो(buf, PAGE_SIZE, "%d\n", !!st->dma_st.dma_chan);
पूर्ण

अटल sमाप_प्रकार at91_adc_get_watermark(काष्ठा device *dev,
				      काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा iio_dev *indio_dev = dev_get_drvdata(dev);
	काष्ठा at91_adc_state *st = iio_priv(indio_dev);

	वापस scnम_लिखो(buf, PAGE_SIZE, "%d\n", st->dma_st.watermark);
पूर्ण

अटल IIO_DEVICE_ATTR(hwfअगरo_enabled, 0444,
		       at91_adc_get_fअगरo_state, शून्य, 0);
अटल IIO_DEVICE_ATTR(hwfअगरo_watermark, 0444,
		       at91_adc_get_watermark, शून्य, 0);

अटल IIO_CONST_ATTR(hwfअगरo_watermark_min, "2");
अटल IIO_CONST_ATTR(hwfअगरo_watermark_max, AT91_HWFIFO_MAX_SIZE_STR);

अटल IIO_CONST_ATTR(oversampling_ratio_available,
		      __stringअगरy(AT91_OSR_1SAMPLES) " "
		      __stringअगरy(AT91_OSR_4SAMPLES) " "
		      __stringअगरy(AT91_OSR_16SAMPLES));

अटल काष्ठा attribute *at91_adc_attributes[] = अणु
	&iio_स्थिर_attr_oversampling_ratio_available.dev_attr.attr,
	शून्य,
पूर्ण;

अटल स्थिर काष्ठा attribute_group at91_adc_attribute_group = अणु
	.attrs = at91_adc_attributes,
पूर्ण;

अटल स्थिर काष्ठा attribute *at91_adc_fअगरo_attributes[] = अणु
	&iio_स्थिर_attr_hwfअगरo_watermark_min.dev_attr.attr,
	&iio_स्थिर_attr_hwfअगरo_watermark_max.dev_attr.attr,
	&iio_dev_attr_hwfअगरo_watermark.dev_attr.attr,
	&iio_dev_attr_hwfअगरo_enabled.dev_attr.attr,
	शून्य,
पूर्ण;

अटल स्थिर काष्ठा iio_info at91_adc_info = अणु
	.attrs = &at91_adc_attribute_group,
	.पढ़ो_raw = &at91_adc_पढ़ो_raw,
	.ग_लिखो_raw = &at91_adc_ग_लिखो_raw,
	.update_scan_mode = &at91_adc_update_scan_mode,
	.of_xlate = &at91_adc_of_xlate,
	.hwfअगरo_set_watermark = &at91_adc_set_watermark,
पूर्ण;

अटल पूर्णांक at91_adc_buffer_and_trigger_init(काष्ठा device *dev,
					    काष्ठा iio_dev *indio)
अणु
	काष्ठा at91_adc_state *st = iio_priv(indio);
	स्थिर काष्ठा attribute **fअगरo_attrs;
	पूर्णांक ret;

	अगर (st->selected_trig->hw_trig)
		fअगरo_attrs = at91_adc_fअगरo_attributes;
	अन्यथा
		fअगरo_attrs = शून्य;

	ret = devm_iio_triggered_buffer_setup_ext(&indio->dev, indio,
		&iio_pollfunc_store_समय,
		&at91_adc_trigger_handler, &at91_buffer_setup_ops, fअगरo_attrs);
	अगर (ret < 0) अणु
		dev_err(dev, "couldn't initialize the buffer.\n");
		वापस ret;
	पूर्ण

	अगर (!st->selected_trig->hw_trig)
		वापस 0;

	st->trig = at91_adc_allocate_trigger(indio, st->selected_trig->name);
	अगर (IS_ERR(st->trig)) अणु
		dev_err(dev, "could not allocate trigger\n");
		वापस PTR_ERR(st->trig);
	पूर्ण

	/*
	 * Initially the iio buffer has a length of 2 and
	 * a watermark of 1
	 */
	st->dma_st.watermark = 1;

	वापस 0;
पूर्ण

अटल पूर्णांक at91_adc_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा iio_dev *indio_dev;
	काष्ठा at91_adc_state *st;
	काष्ठा resource	*res;
	पूर्णांक ret, i;
	u32 edge_type = IRQ_TYPE_NONE;

	indio_dev = devm_iio_device_alloc(&pdev->dev, माप(*st));
	अगर (!indio_dev)
		वापस -ENOMEM;

	indio_dev->name = dev_name(&pdev->dev);
	indio_dev->modes = INDIO_सूचीECT_MODE | INDIO_BUFFER_SOFTWARE;
	indio_dev->info = &at91_adc_info;
	indio_dev->channels = at91_adc_channels;
	indio_dev->num_channels = ARRAY_SIZE(at91_adc_channels);

	st = iio_priv(indio_dev);
	st->indio_dev = indio_dev;

	biपंचांगap_set(&st->touch_st.channels_biपंचांगask,
		   AT91_SAMA5D2_TOUCH_X_CHAN_IDX, 1);
	biपंचांगap_set(&st->touch_st.channels_biपंचांगask,
		   AT91_SAMA5D2_TOUCH_Y_CHAN_IDX, 1);
	biपंचांगap_set(&st->touch_st.channels_biपंचांगask,
		   AT91_SAMA5D2_TOUCH_P_CHAN_IDX, 1);

	st->oversampling_ratio = AT91_OSR_1SAMPLES;

	ret = of_property_पढ़ो_u32(pdev->dev.of_node,
				   "atmel,min-sample-rate-hz",
				   &st->soc_info.min_sample_rate);
	अगर (ret) अणु
		dev_err(&pdev->dev,
			"invalid or missing value for atmel,min-sample-rate-hz\n");
		वापस ret;
	पूर्ण

	ret = of_property_पढ़ो_u32(pdev->dev.of_node,
				   "atmel,max-sample-rate-hz",
				   &st->soc_info.max_sample_rate);
	अगर (ret) अणु
		dev_err(&pdev->dev,
			"invalid or missing value for atmel,max-sample-rate-hz\n");
		वापस ret;
	पूर्ण

	ret = of_property_पढ़ो_u32(pdev->dev.of_node, "atmel,startup-time-ms",
				   &st->soc_info.startup_समय);
	अगर (ret) अणु
		dev_err(&pdev->dev,
			"invalid or missing value for atmel,startup-time-ms\n");
		वापस ret;
	पूर्ण

	ret = of_property_पढ़ो_u32(pdev->dev.of_node,
				   "atmel,trigger-edge-type", &edge_type);
	अगर (ret) अणु
		dev_dbg(&pdev->dev,
			"atmel,trigger-edge-type not specified, only software trigger available\n");
	पूर्ण

	st->selected_trig = शून्य;

	/* find the right trigger, or no trigger at all */
	क्रम (i = 0; i < AT91_SAMA5D2_HW_TRIG_CNT + 1; i++)
		अगर (at91_adc_trigger_list[i].edge_type == edge_type) अणु
			st->selected_trig = &at91_adc_trigger_list[i];
			अवरोध;
		पूर्ण

	अगर (!st->selected_trig) अणु
		dev_err(&pdev->dev, "invalid external trigger edge value\n");
		वापस -EINVAL;
	पूर्ण

	init_रुकोqueue_head(&st->wq_data_available);
	mutex_init(&st->lock);
	INIT_WORK(&st->touch_st.workq, at91_adc_workq_handler);

	st->base = devm_platक्रमm_get_and_ioremap_resource(pdev, 0, &res);
	अगर (IS_ERR(st->base))
		वापस PTR_ERR(st->base);

	/* अगर we plan to use DMA, we need the physical address of the regs */
	st->dma_st.phys_addr = res->start;

	st->irq = platक्रमm_get_irq(pdev, 0);
	अगर (st->irq <= 0) अणु
		अगर (!st->irq)
			st->irq = -ENXIO;

		वापस st->irq;
	पूर्ण

	st->per_clk = devm_clk_get(&pdev->dev, "adc_clk");
	अगर (IS_ERR(st->per_clk))
		वापस PTR_ERR(st->per_clk);

	st->reg = devm_regulator_get(&pdev->dev, "vddana");
	अगर (IS_ERR(st->reg))
		वापस PTR_ERR(st->reg);

	st->vref = devm_regulator_get(&pdev->dev, "vref");
	अगर (IS_ERR(st->vref))
		वापस PTR_ERR(st->vref);

	ret = devm_request_irq(&pdev->dev, st->irq, at91_adc_पूर्णांकerrupt, 0,
			       pdev->dev.driver->name, indio_dev);
	अगर (ret)
		वापस ret;

	ret = regulator_enable(st->reg);
	अगर (ret)
		वापस ret;

	ret = regulator_enable(st->vref);
	अगर (ret)
		जाओ reg_disable;

	st->vref_uv = regulator_get_voltage(st->vref);
	अगर (st->vref_uv <= 0) अणु
		ret = -EINVAL;
		जाओ vref_disable;
	पूर्ण

	at91_adc_hw_init(indio_dev);

	ret = clk_prepare_enable(st->per_clk);
	अगर (ret)
		जाओ vref_disable;

	platक्रमm_set_drvdata(pdev, indio_dev);

	ret = at91_adc_buffer_and_trigger_init(&pdev->dev, indio_dev);
	अगर (ret < 0)
		जाओ per_clk_disable_unprepare;

	अगर (dma_coerce_mask_and_coherent(&indio_dev->dev, DMA_BIT_MASK(32)))
		dev_info(&pdev->dev, "cannot set DMA mask to 32-bit\n");

	ret = iio_device_रेजिस्टर(indio_dev);
	अगर (ret < 0)
		जाओ dma_disable;

	अगर (st->selected_trig->hw_trig)
		dev_info(&pdev->dev, "setting up trigger as %s\n",
			 st->selected_trig->name);

	dev_info(&pdev->dev, "version: %x\n",
		 पढ़ोl_relaxed(st->base + AT91_SAMA5D2_VERSION));

	वापस 0;

dma_disable:
	at91_adc_dma_disable(pdev);
per_clk_disable_unprepare:
	clk_disable_unprepare(st->per_clk);
vref_disable:
	regulator_disable(st->vref);
reg_disable:
	regulator_disable(st->reg);
	वापस ret;
पूर्ण

अटल पूर्णांक at91_adc_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा iio_dev *indio_dev = platक्रमm_get_drvdata(pdev);
	काष्ठा at91_adc_state *st = iio_priv(indio_dev);

	iio_device_unरेजिस्टर(indio_dev);

	at91_adc_dma_disable(pdev);

	clk_disable_unprepare(st->per_clk);

	regulator_disable(st->vref);
	regulator_disable(st->reg);

	वापस 0;
पूर्ण

अटल __maybe_unused पूर्णांक at91_adc_suspend(काष्ठा device *dev)
अणु
	काष्ठा iio_dev *indio_dev = dev_get_drvdata(dev);
	काष्ठा at91_adc_state *st = iio_priv(indio_dev);

	/*
	 * Do a sofware reset of the ADC beक्रमe we go to suspend.
	 * this will ensure that all pins are मुक्त from being muxed by the ADC
	 * and can be used by क्रम other devices.
	 * Otherwise, ADC will hog them and we can't go to suspend mode.
	 */
	at91_adc_ग_लिखोl(st, AT91_SAMA5D2_CR, AT91_SAMA5D2_CR_SWRST);

	clk_disable_unprepare(st->per_clk);
	regulator_disable(st->vref);
	regulator_disable(st->reg);

	वापस pinctrl_pm_select_sleep_state(dev);
पूर्ण

अटल __maybe_unused पूर्णांक at91_adc_resume(काष्ठा device *dev)
अणु
	काष्ठा iio_dev *indio_dev = dev_get_drvdata(dev);
	काष्ठा at91_adc_state *st = iio_priv(indio_dev);
	पूर्णांक ret;

	ret = pinctrl_pm_select_शेष_state(dev);
	अगर (ret)
		जाओ resume_failed;

	ret = regulator_enable(st->reg);
	अगर (ret)
		जाओ resume_failed;

	ret = regulator_enable(st->vref);
	अगर (ret)
		जाओ reg_disable_resume;

	ret = clk_prepare_enable(st->per_clk);
	अगर (ret)
		जाओ vref_disable_resume;

	at91_adc_hw_init(indio_dev);

	/* reconfiguring trigger hardware state */
	अगर (!iio_buffer_enabled(indio_dev))
		वापस 0;

	/* check अगर we are enabling triggered buffer or the touchscreen */
	अगर (at91_adc_current_chan_is_touch(indio_dev))
		वापस at91_adc_configure_touch(st, true);
	अन्यथा
		वापस at91_adc_configure_trigger(st->trig, true);

	/* not needed but more explicit */
	वापस 0;

vref_disable_resume:
	regulator_disable(st->vref);
reg_disable_resume:
	regulator_disable(st->reg);
resume_failed:
	dev_err(&indio_dev->dev, "failed to resume\n");
	वापस ret;
पूर्ण

अटल SIMPLE_DEV_PM_OPS(at91_adc_pm_ops, at91_adc_suspend, at91_adc_resume);

अटल स्थिर काष्ठा of_device_id at91_adc_dt_match[] = अणु
	अणु
		.compatible = "atmel,sama5d2-adc",
	पूर्ण, अणु
		/* sentinel */
	पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, at91_adc_dt_match);

अटल काष्ठा platक्रमm_driver at91_adc_driver = अणु
	.probe = at91_adc_probe,
	.हटाओ = at91_adc_हटाओ,
	.driver = अणु
		.name = "at91-sama5d2_adc",
		.of_match_table = at91_adc_dt_match,
		.pm = &at91_adc_pm_ops,
	पूर्ण,
पूर्ण;
module_platक्रमm_driver(at91_adc_driver)

MODULE_AUTHOR("Ludovic Desroches <ludovic.desroches@atmel.com>");
MODULE_DESCRIPTION("Atmel AT91 SAMA5D2 ADC");
MODULE_LICENSE("GPL v2");
