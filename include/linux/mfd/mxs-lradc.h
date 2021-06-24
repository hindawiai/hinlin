<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * Freescale MXS Low Resolution Analog-to-Digital Converter driver
 *
 * Copyright (c) 2012 DENX Software Engineering, GmbH.
 * Copyright (c) 2016 Ksenija Stanojevic <ksenija.stanojevic@gmail.com>
 *
 * Author: Marek Vasut <marex@denx.de>
 */

#अगर_अघोषित __MFD_MXS_LRADC_H
#घोषणा __MFD_MXS_LRADC_H

#समावेश <linux/bitops.h>
#समावेश <linux/पन.स>
#समावेश <linux/sपंचांगp_device.h>

#घोषणा LRADC_MAX_DELAY_CHANS	4
#घोषणा LRADC_MAX_MAPPED_CHANS	8
#घोषणा LRADC_MAX_TOTAL_CHANS	16

#घोषणा LRADC_DELAY_TIMER_HZ	2000

#घोषणा LRADC_CTRL0				0x00
# define LRADC_CTRL0_MX28_TOUCH_DETECT_ENABLE	BIT(23)
# define LRADC_CTRL0_MX28_TOUCH_SCREEN_TYPE	BIT(22)
# define LRADC_CTRL0_MX28_YNNSW /* YM */	BIT(21)
# define LRADC_CTRL0_MX28_YPNSW /* YP */	BIT(20)
# define LRADC_CTRL0_MX28_YPPSW /* YP */	BIT(19)
# define LRADC_CTRL0_MX28_XNNSW /* XM */	BIT(18)
# define LRADC_CTRL0_MX28_XNPSW /* XM */	BIT(17)
# define LRADC_CTRL0_MX28_XPPSW /* XP */	BIT(16)

# define LRADC_CTRL0_MX23_TOUCH_DETECT_ENABLE	BIT(20)
# define LRADC_CTRL0_MX23_YM			BIT(19)
# define LRADC_CTRL0_MX23_XM			BIT(18)
# define LRADC_CTRL0_MX23_YP			BIT(17)
# define LRADC_CTRL0_MX23_XP			BIT(16)

# define LRADC_CTRL0_MX28_PLATE_MASK \
		(LRADC_CTRL0_MX28_TOUCH_DETECT_ENABLE | \
		LRADC_CTRL0_MX28_YNNSW | LRADC_CTRL0_MX28_YPNSW | \
		LRADC_CTRL0_MX28_YPPSW | LRADC_CTRL0_MX28_XNNSW | \
		LRADC_CTRL0_MX28_XNPSW | LRADC_CTRL0_MX28_XPPSW)

# define LRADC_CTRL0_MX23_PLATE_MASK \
		(LRADC_CTRL0_MX23_TOUCH_DETECT_ENABLE | \
		LRADC_CTRL0_MX23_YM | LRADC_CTRL0_MX23_XM | \
		LRADC_CTRL0_MX23_YP | LRADC_CTRL0_MX23_XP)

#घोषणा LRADC_CTRL1				0x10
#घोषणा LRADC_CTRL1_TOUCH_DETECT_IRQ_EN		BIT(24)
#घोषणा LRADC_CTRL1_LRADC_IRQ_EN(n)		(1 << ((n) + 16))
#घोषणा LRADC_CTRL1_MX28_LRADC_IRQ_EN_MASK	(0x1fff << 16)
#घोषणा LRADC_CTRL1_MX23_LRADC_IRQ_EN_MASK	(0x01ff << 16)
#घोषणा LRADC_CTRL1_LRADC_IRQ_EN_OFFSET		16
#घोषणा LRADC_CTRL1_TOUCH_DETECT_IRQ		BIT(8)
#घोषणा LRADC_CTRL1_LRADC_IRQ(n)		BIT(n)
#घोषणा LRADC_CTRL1_MX28_LRADC_IRQ_MASK		0x1fff
#घोषणा LRADC_CTRL1_MX23_LRADC_IRQ_MASK		0x01ff
#घोषणा LRADC_CTRL1_LRADC_IRQ_OFFSET		0

#घोषणा LRADC_CTRL2				0x20
#घोषणा LRADC_CTRL2_DIVIDE_BY_TWO_OFFSET	24
#घोषणा LRADC_CTRL2_TEMPSENSE_PWD		BIT(15)

#घोषणा LRADC_STATUS				0x40
#घोषणा LRADC_STATUS_TOUCH_DETECT_RAW		BIT(0)

#घोषणा LRADC_CH(n)				(0x50 + (0x10 * (n)))
#घोषणा LRADC_CH_ACCUMULATE			BIT(29)
#घोषणा LRADC_CH_NUM_SAMPLES_MASK		(0x1f << 24)
#घोषणा LRADC_CH_NUM_SAMPLES_OFFSET		24
#घोषणा LRADC_CH_NUM_SAMPLES(x) \
				((x) << LRADC_CH_NUM_SAMPLES_OFFSET)
#घोषणा LRADC_CH_VALUE_MASK			0x3ffff
#घोषणा LRADC_CH_VALUE_OFFSET			0

#घोषणा LRADC_DELAY(n)				(0xd0 + (0x10 * (n)))
#घोषणा LRADC_DELAY_TRIGGER_LRADCS_MASK		(0xffUL << 24)
#घोषणा LRADC_DELAY_TRIGGER_LRADCS_OFFSET	24
#घोषणा LRADC_DELAY_TRIGGER(x) \
				(((x) << LRADC_DELAY_TRIGGER_LRADCS_OFFSET) & \
				LRADC_DELAY_TRIGGER_LRADCS_MASK)
#घोषणा LRADC_DELAY_KICK			BIT(20)
#घोषणा LRADC_DELAY_TRIGGER_DELAYS_MASK		(0xf << 16)
#घोषणा LRADC_DELAY_TRIGGER_DELAYS_OFFSET	16
#घोषणा LRADC_DELAY_TRIGGER_DELAYS(x) \
				(((x) << LRADC_DELAY_TRIGGER_DELAYS_OFFSET) & \
				LRADC_DELAY_TRIGGER_DELAYS_MASK)
#घोषणा LRADC_DELAY_LOOP_COUNT_MASK		(0x1f << 11)
#घोषणा LRADC_DELAY_LOOP_COUNT_OFFSET		11
#घोषणा LRADC_DELAY_LOOP(x) \
				(((x) << LRADC_DELAY_LOOP_COUNT_OFFSET) & \
				LRADC_DELAY_LOOP_COUNT_MASK)
#घोषणा LRADC_DELAY_DELAY_MASK			0x7ff
#घोषणा LRADC_DELAY_DELAY_OFFSET		0
#घोषणा LRADC_DELAY_DELAY(x) \
				(((x) << LRADC_DELAY_DELAY_OFFSET) & \
				LRADC_DELAY_DELAY_MASK)

#घोषणा LRADC_CTRL4				0x140
#घोषणा LRADC_CTRL4_LRADCSELECT_MASK(n)		(0xf << ((n) * 4))
#घोषणा LRADC_CTRL4_LRADCSELECT_OFFSET(n)	((n) * 4)
#घोषणा LRADC_CTRL4_LRADCSELECT(n, x) \
				(((x) << LRADC_CTRL4_LRADCSELECT_OFFSET(n)) & \
				LRADC_CTRL4_LRADCSELECT_MASK(n))

#घोषणा LRADC_RESOLUTION			12
#घोषणा LRADC_SINGLE_SAMPLE_MASK		((1 << LRADC_RESOLUTION) - 1)

#घोषणा BUFFER_VCHANS_LIMITED		0x3f
#घोषणा BUFFER_VCHANS_ALL		0xff

	/*
	 * Certain LRADC channels are shared between touchscreen
	 * and/or touch-buttons and generic LRADC block. Thereक्रमe when using
	 * either of these, these channels are not available क्रम the regular
	 * sampling. The shared channels are as follows:
	 *
	 * CH0 -- Touch button #0
	 * CH1 -- Touch button #1
	 * CH2 -- Touch screen XPUL
	 * CH3 -- Touch screen YPLL
	 * CH4 -- Touch screen XNUL
	 * CH5 -- Touch screen YNLR
	 * CH6 -- Touch screen WIPER (5-wire only)
	 *
	 * The bit fields below represents which parts of the LRADC block are
	 * चयनed पूर्णांकo special mode of operation. These channels can not
	 * be sampled as regular LRADC channels. The driver will refuse any
	 * attempt to sample these channels.
	 */
#घोषणा CHAN_MASK_TOUCHBUTTON		(BIT(1) | BIT(0))
#घोषणा CHAN_MASK_TOUCHSCREEN_4WIRE	(0xf << 2)
#घोषणा CHAN_MASK_TOUCHSCREEN_5WIRE	(0x1f << 2)

क्रमागत mxs_lradc_id अणु
	IMX23_LRADC,
	IMX28_LRADC,
पूर्ण;

क्रमागत mxs_lradc_ts_wires अणु
	MXS_LRADC_TOUCHSCREEN_NONE = 0,
	MXS_LRADC_TOUCHSCREEN_4WIRE,
	MXS_LRADC_TOUCHSCREEN_5WIRE,
पूर्ण;

/**
 * काष्ठा mxs_lradc
 * @soc: soc type (IMX23 or IMX28)
 * @clk: 2 kHz घड़ी क्रम delay units
 * @buffer_vchans: channels that can be used during buffered capture
 * @touchscreen_wire: touchscreen type (4-wire or 5-wire)
 * @use_touchbutton: button state (on or off)
 */
काष्ठा mxs_lradc अणु
	क्रमागत mxs_lradc_id	soc;
	काष्ठा clk		*clk;
	u8			buffer_vchans;

	क्रमागत mxs_lradc_ts_wires	touchscreen_wire;
	bool			use_touchbutton;
पूर्ण;

अटल अंतरभूत u32 mxs_lradc_irq_mask(काष्ठा mxs_lradc *lradc)
अणु
	चयन (lradc->soc) अणु
	हाल IMX23_LRADC:
		वापस LRADC_CTRL1_MX23_LRADC_IRQ_MASK;
	हाल IMX28_LRADC:
		वापस LRADC_CTRL1_MX28_LRADC_IRQ_MASK;
	शेष:
		वापस 0;
	पूर्ण
पूर्ण

#पूर्ण_अगर /* __MXS_LRADC_H */
