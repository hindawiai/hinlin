<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * ALSA SoC Texas Instruments TLV320DAC33 codec driver
 *
 * Author: Peter Ujfalusi <peter.ujfalusi@ti.com>
 *
 * Copyright:   (C) 2009 Nokia Corporation
 */

#अगर_अघोषित __TLV320DAC33_H
#घोषणा __TLV320DAC33_H

#घोषणा DAC33_PAGE_SELECT		0x00
#घोषणा DAC33_PWR_CTRL			0x01
#घोषणा DAC33_PLL_CTRL_A		0x02
#घोषणा DAC33_PLL_CTRL_B		0x03
#घोषणा DAC33_PLL_CTRL_C		0x04
#घोषणा DAC33_PLL_CTRL_D		0x05
#घोषणा DAC33_PLL_CTRL_E		0x06
#घोषणा DAC33_INT_OSC_CTRL		0x07
#घोषणा DAC33_INT_OSC_FREQ_RAT_A	0x08
#घोषणा DAC33_INT_OSC_FREQ_RAT_B	0x09
#घोषणा DAC33_INT_OSC_DAC_RATIO_SET	0x0A
#घोषणा DAC33_CALIB_TIME		0x0B
#घोषणा DAC33_INT_OSC_CTRL_B		0x0C
#घोषणा DAC33_INT_OSC_CTRL_C		0x0D
#घोषणा DAC33_INT_OSC_STATUS		0x0E
#घोषणा DAC33_INT_OSC_DAC_RATIO_READ	0x0F
#घोषणा DAC33_INT_OSC_FREQ_RAT_READ_A	0x10
#घोषणा DAC33_INT_OSC_FREQ_RAT_READ_B	0x11
#घोषणा DAC33_SER_AUDIOIF_CTRL_A	0x12
#घोषणा DAC33_SER_AUDIOIF_CTRL_B	0x13
#घोषणा DAC33_SER_AUDIOIF_CTRL_C	0x14
#घोषणा DAC33_FIFO_CTRL_A		0x15
#घोषणा DAC33_UTHR_MSB			0x16
#घोषणा DAC33_UTHR_LSB			0x17
#घोषणा DAC33_ATHR_MSB			0x18
#घोषणा DAC33_ATHR_LSB			0x19
#घोषणा DAC33_LTHR_MSB			0x1A
#घोषणा DAC33_LTHR_LSB			0x1B
#घोषणा DAC33_PREFILL_MSB		0x1C
#घोषणा DAC33_PREFILL_LSB		0x1D
#घोषणा DAC33_NSAMPLE_MSB		0x1E
#घोषणा DAC33_NSAMPLE_LSB		0x1F
#घोषणा DAC33_FIFO_WPTR_MSB		0x20
#घोषणा DAC33_FIFO_WPTR_LSB		0x21
#घोषणा DAC33_FIFO_RPTR_MSB		0x22
#घोषणा DAC33_FIFO_RPTR_LSB		0x23
#घोषणा DAC33_FIFO_DEPTH_MSB		0x24
#घोषणा DAC33_FIFO_DEPTH_LSB		0x25
#घोषणा DAC33_SAMPLES_REMAINING_MSB	0x26
#घोषणा DAC33_SAMPLES_REMAINING_LSB	0x27
#घोषणा DAC33_FIFO_IRQ_FLAG		0x28
#घोषणा DAC33_FIFO_IRQ_MASK		0x29
#घोषणा DAC33_FIFO_IRQ_MODE_A		0x2A
#घोषणा DAC33_FIFO_IRQ_MODE_B		0x2B
#घोषणा DAC33_DAC_CTRL_A		0x2C
#घोषणा DAC33_DAC_CTRL_B		0x2D
#घोषणा DAC33_DAC_CTRL_C		0x2E
#घोषणा DAC33_LDAC_DIG_VOL_CTRL		0x2F
#घोषणा DAC33_RDAC_DIG_VOL_CTRL		0x30
#घोषणा DAC33_DAC_STATUS_FLAGS		0x31
#घोषणा DAC33_ASRC_CTRL_A		0x32
#घोषणा DAC33_ASRC_CTRL_B		0x33
#घोषणा DAC33_SRC_REF_CLK_RATIO_A	0x34
#घोषणा DAC33_SRC_REF_CLK_RATIO_B	0x35
#घोषणा DAC33_SRC_EST_REF_CLK_RATIO_A	0x36
#घोषणा DAC33_SRC_EST_REF_CLK_RATIO_B	0x37
#घोषणा DAC33_INTP_CTRL_A		0x38
#घोषणा DAC33_INTP_CTRL_B		0x39
/* Registers 0x3A - 0x3F Reserved */
#घोषणा DAC33_LDAC_PWR_CTRL		0x40
#घोषणा DAC33_RDAC_PWR_CTRL		0x41
#घोषणा DAC33_OUT_AMP_CM_CTRL		0x42
#घोषणा DAC33_OUT_AMP_PWR_CTRL		0x43
#घोषणा DAC33_OUT_AMP_CTRL		0x44
#घोषणा DAC33_LINEL_TO_LLO_VOL		0x45
/* Registers 0x45 - 0x47 Reserved */
#घोषणा DAC33_LINER_TO_RLO_VOL		0x48
#घोषणा DAC33_ANA_VOL_SOFT_STEP_CTRL	0x49
#घोषणा DAC33_OSC_TRIM			0x4A
/* Registers 0x4B - 0x7C Reserved */
#घोषणा DAC33_DEVICE_ID_MSB		0x7D
#घोषणा DAC33_DEVICE_ID_LSB		0x7E
#घोषणा DAC33_DEVICE_REV_ID		0x7F

#घोषणा DAC33_CACHEREGNUM               128

/* Bit definitions */

/* DAC33_PWR_CTRL (0x01) */
#घोषणा DAC33_DACRPDNB			(0x01 << 0)
#घोषणा DAC33_DACLPDNB			(0x01 << 1)
#घोषणा DAC33_OSCPDNB			(0x01 << 2)
#घोषणा DAC33_PLLPDNB			(0x01 << 3)
#घोषणा DAC33_PDNALLB			(0x01 << 4)
#घोषणा DAC33_SOFT_RESET		(0x01 << 7)

/* DAC33_INT_OSC_CTRL (0x07) */
#घोषणा DAC33_REFSEL			(0x01 << 1)

/* DAC33_INT_OSC_CTRL_B (0x0C) */
#घोषणा DAC33_ADJSTEP(x)		(x << 0)
#घोषणा DAC33_ADJTHRSHLD(x)		(x << 4)

/* DAC33_INT_OSC_CTRL_C (0x0D) */
#घोषणा DAC33_REFDIV(x)			(x << 4)

/* DAC33_INT_OSC_STATUS (0x0E) */
#घोषणा DAC33_OSCSTATUS_IDLE_CALIB	(0x00)
#घोषणा DAC33_OSCSTATUS_NORMAL		(0x01)
#घोषणा DAC33_OSCSTATUS_ADJUSTMENT	(0x03)
#घोषणा DAC33_OSCSTATUS_NOT_USED	(0x02)

/* DAC33_SER_AUDIOIF_CTRL_A (0x12) */
#घोषणा DAC33_MSWCLK			(0x01 << 0)
#घोषणा DAC33_MSBCLK			(0x01 << 1)
#घोषणा DAC33_AFMT_MASK			(0x03 << 2)
#घोषणा DAC33_AFMT_I2S			(0x00 << 2)
#घोषणा DAC33_AFMT_DSP			(0x01 << 2)
#घोषणा DAC33_AFMT_RIGHT_J		(0x02 << 2)
#घोषणा DAC33_AFMT_LEFT_J		(0x03 << 2)
#घोषणा DAC33_WLEN_MASK			(0x03 << 4)
#घोषणा DAC33_WLEN_16			(0x00 << 4)
#घोषणा DAC33_WLEN_20			(0x01 << 4)
#घोषणा DAC33_WLEN_24			(0x02 << 4)
#घोषणा DAC33_WLEN_32			(0x03 << 4)
#घोषणा DAC33_NCYCL_MASK		(0x03 << 6)
#घोषणा DAC33_NCYCL_16			(0x00 << 6)
#घोषणा DAC33_NCYCL_20			(0x01 << 6)
#घोषणा DAC33_NCYCL_24			(0x02 << 6)
#घोषणा DAC33_NCYCL_32			(0x03 << 6)

/* DAC33_SER_AUDIOIF_CTRL_B (0x13) */
#घोषणा DAC33_DATA_DELAY_MASK		(0x03 << 2)
#घोषणा DAC33_DATA_DELAY(x)		(x << 2)
#घोषणा DAC33_BCLKON			(0x01 << 5)

/* DAC33_FIFO_CTRL_A (0x15) */
#घोषणा DAC33_WIDTH				(0x01 << 0)
#घोषणा DAC33_FBYPAS				(0x01 << 1)
#घोषणा DAC33_FAUTO				(0x01 << 2)
#घोषणा DAC33_FIFOFLUSH			(0x01 << 3)

/*
 * UTHR, ATHR, LTHR, PREFILL, NSAMPLE (0x16 - 0x1F)
 * 13-bit values
*/
#घोषणा DAC33_THRREG(x)			(((x) & 0x1FFF) << 3)

/* DAC33_FIFO_IRQ_MASK (0x29) */
#घोषणा DAC33_MNS			(0x01 << 0)
#घोषणा DAC33_MPS			(0x01 << 1)
#घोषणा DAC33_MAT			(0x01 << 2)
#घोषणा DAC33_MLT			(0x01 << 3)
#घोषणा DAC33_MUT			(0x01 << 4)
#घोषणा DAC33_MUF			(0x01 << 5)
#घोषणा DAC33_MOF			(0x01 << 6)

#घोषणा DAC33_FIFO_IRQ_MODE_MASK	(0x03)
#घोषणा DAC33_FIFO_IRQ_MODE_RISING	(0x00)
#घोषणा DAC33_FIFO_IRQ_MODE_FALLING	(0x01)
#घोषणा DAC33_FIFO_IRQ_MODE_LEVEL	(0x02)
#घोषणा DAC33_FIFO_IRQ_MODE_EDGE	(0x03)

/* DAC33_FIFO_IRQ_MODE_A (0x2A) */
#घोषणा DAC33_UTM(x)			(x << 0)
#घोषणा DAC33_UFM(x)			(x << 2)
#घोषणा DAC33_OFM(x)			(x << 4)

/* DAC33_FIFO_IRQ_MODE_B (0x2B) */
#घोषणा DAC33_NSM(x)			(x << 0)
#घोषणा DAC33_PSM(x)			(x << 2)
#घोषणा DAC33_ATM(x)			(x << 4)
#घोषणा DAC33_LTM(x)			(x << 6)

/* DAC33_DAC_CTRL_A (0x2C) */
#घोषणा DAC33_DACRATE(x)		(x << 0)
#घोषणा DAC33_DACDUAL			(0x01 << 4)
#घोषणा DAC33_DACLKSEL_MASK		(0x03 << 5)
#घोषणा DAC33_DACLKSEL_INTSOC		(0x00 << 5)
#घोषणा DAC33_DACLKSEL_PLL		(0x01 << 5)
#घोषणा DAC33_DACLKSEL_MCLK		(0x02 << 5)
#घोषणा DAC33_DACLKSEL_BCLK		(0x03 << 5)

/* DAC33_DAC_CTRL_B (0x2D) */
#घोषणा DAC33_DACSRCR_MASK		(0x03 << 0)
#घोषणा DAC33_DACSRCR_MUTE		(0x00 << 0)
#घोषणा DAC33_DACSRCR_RIGHT		(0x01 << 0)
#घोषणा DAC33_DACSRCR_LEFT		(0x02 << 0)
#घोषणा DAC33_DACSRCR_MONOMIX		(0x03 << 0)
#घोषणा DAC33_DACSRCL_MASK		(0x03 << 2)
#घोषणा DAC33_DACSRCL_MUTE		(0x00 << 2)
#घोषणा DAC33_DACSRCL_LEFT		(0x01 << 2)
#घोषणा DAC33_DACSRCL_RIGHT		(0x02 << 2)
#घोषणा DAC33_DACSRCL_MONOMIX		(0x03 << 2)
#घोषणा DAC33_DVOLSTEP_MASK		(0x03 << 4)
#घोषणा DAC33_DVOLSTEP_SS_PERFS		(0x00 << 4)
#घोषणा DAC33_DVOLSTEP_SS_PER2FS	(0x01 << 4)
#घोषणा DAC33_DVOLSTEP_SS_DISABLED	(0x02 << 4)
#घोषणा DAC33_DVOLCTRL_MASK		(0x03 << 6)
#घोषणा DAC33_DVOLCTRL_LR_INDEPENDENT1	(0x00 << 6)
#घोषणा DAC33_DVOLCTRL_LR_RIGHT_CONTROL	(0x01 << 6)
#घोषणा DAC33_DVOLCTRL_LR_LEFT_CONTROL	(0x02 << 6)
#घोषणा DAC33_DVOLCTRL_LR_INDEPENDENT2	(0x03 << 6)

/* DAC33_DAC_CTRL_C (0x2E) */
#घोषणा DAC33_DEEMENR			(0x01 << 0)
#घोषणा DAC33_EFFENR			(0x01 << 1)
#घोषणा DAC33_DEEMENL			(0x01 << 2)
#घोषणा DAC33_EFFENL			(0x01 << 3)
#घोषणा DAC33_EN3D			(0x01 << 4)
#घोषणा DAC33_RESYNMUTE			(0x01 << 5)
#घोषणा DAC33_RESYNEN			(0x01 << 6)

/* DAC33_ASRC_CTRL_A (0x32) */
#घोषणा DAC33_SRCBYP			(0x01 << 0)
#घोषणा DAC33_SRCLKSEL_MASK		(0x03 << 1)
#घोषणा DAC33_SRCLKSEL_INTSOC		(0x00 << 1)
#घोषणा DAC33_SRCLKSEL_PLL		(0x01 << 1)
#घोषणा DAC33_SRCLKSEL_MCLK		(0x02 << 1)
#घोषणा DAC33_SRCLKSEL_BCLK		(0x03 << 1)
#घोषणा DAC33_SRCLKDIV(x)		(x << 3)

/* DAC33_ASRC_CTRL_B (0x33) */
#घोषणा DAC33_SRCSETUP(x)		(x << 0)
#घोषणा DAC33_SRCREFSEL			(0x01 << 4)
#घोषणा DAC33_SRCREFDIV(x)		(x << 5)

/* DAC33_INTP_CTRL_A (0x38) */
#घोषणा DAC33_INTPSEL			(0x01 << 0)
#घोषणा DAC33_INTPM_MASK		(0x03 << 1)
#घोषणा DAC33_INTPM_ALOW_OPENDRAIN	(0x00 << 1)
#घोषणा DAC33_INTPM_ALOW		(0x01 << 1)
#घोषणा DAC33_INTPM_AHIGH		(0x02 << 1)

/* DAC33_LDAC_PWR_CTRL (0x40) */
/* DAC33_RDAC_PWR_CTRL (0x41) */
#घोषणा DAC33_DACLRNUM			(0x01 << 2)
#घोषणा DAC33_LROUT_GAIN(x)		(x << 0)

/* DAC33_ANA_VOL_SOFT_STEP_CTRL (0x49) */
#घोषणा DAC33_VOLCLKSEL			(0x01 << 0)
#घोषणा DAC33_VOLCLKEN			(0x01 << 1)
#घोषणा DAC33_VOLBYPASS			(0x01 << 2)

#घोषणा TLV320DAC33_MCLK		0
#घोषणा TLV320DAC33_SLEEPCLK		1

#पूर्ण_अगर /* __TLV320DAC33_H */
