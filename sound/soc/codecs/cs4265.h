<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * cs4265.h -- CS4265 ALSA SoC audio driver
 *
 * Copyright 2014 Cirrus Logic, Inc.
 *
 * Author: Paul Handrigan <paul.handrigan@cirrus.com>
 */

#अगर_अघोषित __CS4265_H__
#घोषणा __CS4265_H__

#घोषणा CS4265_CHIP_ID				0x1
#घोषणा CS4265_CHIP_ID_VAL			0xD0
#घोषणा CS4265_CHIP_ID_MASK			0xF0
#घोषणा CS4265_REV_ID_MASK			0x0F

#घोषणा CS4265_PWRCTL				0x02
#घोषणा CS4265_PWRCTL_PDN			1

#घोषणा CS4265_DAC_CTL				0x3
#घोषणा CS4265_DAC_CTL_MUTE			(1 << 2)
#घोषणा CS4265_DAC_CTL_DIF			(3 << 4)

#घोषणा CS4265_ADC_CTL				0x4
#घोषणा CS4265_ADC_MASTER			1
#घोषणा CS4265_ADC_DIF				(1 << 4)
#घोषणा CS4265_ADC_FM				(3 << 6)

#घोषणा CS4265_MCLK_FREQ			0x5
#घोषणा CS4265_MCLK_FREQ_MASK			(7 << 4)

#घोषणा CS4265_SIG_SEL				0x6
#घोषणा CS4265_SIG_SEL_LOOP			(1 << 1)

#घोषणा CS4265_CHB_PGA_CTL			0x7
#घोषणा CS4265_CHA_PGA_CTL			0x8

#घोषणा CS4265_ADC_CTL2				0x9

#घोषणा CS4265_DAC_CHA_VOL			0xA
#घोषणा CS4265_DAC_CHB_VOL			0xB

#घोषणा CS4265_DAC_CTL2				0xC

#घोषणा CS4265_INT_STATUS			0xD
#घोषणा CS4265_INT_MASK				0xE
#घोषणा CS4265_STATUS_MODE_MSB			0xF
#घोषणा CS4265_STATUS_MODE_LSB			0x10

#घोषणा CS4265_SPDIF_CTL1			0x11

#घोषणा CS4265_SPDIF_CTL2			0x12
#घोषणा CS4265_SPDIF_CTL2_MUTE			(1 << 4)
#घोषणा CS4265_SPDIF_CTL2_DIF			(3 << 6)

#घोषणा CS4265_C_DATA_BUFF			0x13
#घोषणा CS4265_MAX_REGISTER			0x2A

#पूर्ण_अगर
